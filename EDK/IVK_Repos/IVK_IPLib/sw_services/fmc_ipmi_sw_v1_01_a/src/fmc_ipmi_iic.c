//----------------------------------------------------------------
//      _____
//     /     \
//    /____   \____
//   / \===\   \==/
//  /___\===\___\/  AVNET
//       \======/
//        \====/    
//---------------------------------------------------------------
//
// This design is the property of Avnet.  Publication of this
// design is not authorized without written consent from Avnet.
// 
// Please direct any questions to:  technical.support@avnet.com
//
// Disclaimer:
//    Avnet, Inc. makes no warranty for the use of this code or design.
//    This code is provided  "As Is". Avnet, Inc assumes no responsibility for
//    any errors, which may appear in this code, nor does it make a commitment
//    to update the information contained herein. Avnet, Inc specifically
//    disclaims any implied warranties of fitness for a particular purpose.
//                     Copyright(c) 2010 Avnet, Inc.
//                             All rights reserved.
//
//----------------------------------------------------------------
//
// Create Date:         Nov 11, 2009
// Design Name:         FMC IPMI
// Module Name:         fmc_ipmi_iic.c
// Project Name:        FMC IPMI
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-IMAGEOV, FMC-DVI/DP, FMC-ISM
//
// Tool versions:       ISE 11.4
//
// Description:         FMC IPMI IIC driver
//
// Dependencies:        
//
// Revision:            Nov 11, 2009: 1.00 Initial version
//
//----------------------------------------------------------------

#include <stdio.h>

// Located in: microblaze_0/include/
#include "xparameters.h"
#include "xstatus.h"

#include "fmc_ipmi_iic.h"

////////////////////////////////////////////////////////////////////////
// I2C Functions
////////////////////////////////////////////////////////////////////////

#include "xiic.h"
#include "xio.h"
   
/*
 * The page size determines how much data should be written at a time.
 * The write function should be called with this as a maximum byte count.
 */
#define PAGE_SIZE   2

/******************************************************************************
* This function initializes the IIC controller.
*
* @param    CoreAddress contains the address of the IIC core.
*
* @return   If successfull, returns 1.  Otherwise, returns 0.
*
* @note     None.
*
******************************************************************************/
int fmc_ipmi_iic_init( Xuint32 CoreAddress )
{
   XStatus Status;

   /*
    * Initialize the IIC Core.
    */
   Status = XIic_DynInit(CoreAddress);
   if(Status != XST_SUCCESS)
   {
      xil_printf("Failed to initialize I2C chain\n\r" );
      return 0;
   }
   
   return 1;
}


/******************************************************************************
* This function writes a buffer of bytes to the IIC chip.
*
* @param    CoreAddress contains the address of the IIC core.
* @param    ChipAddress contains the address of the chip.
* @param    RegAddress contains the address of the register to write to.
* @param    BufferPtr contains the address of the data to write.
* @param    ByteCount contains the number of bytes in the buffer to be written.
*           Note that this should not exceed the page size as noted by the 
*           constant PAGE_SIZE.
*
* @return   The number of bytes written, a value less than that which was
*           specified as an input indicates an error.
*
* @note     None.
*
******************************************************************************/
int fmc_ipmi_iic_write(Xuint32 CoreAddress, Xuint8 ChipAddress, Xuint8 RegAddress, 
                       Xuint8 *BufferPtr, Xuint8 ByteCount)
{
  Xuint8 SentByteCount;
  Xuint8 WriteBuffer[PAGE_SIZE + 1];
  Xuint8 Index;
  Xuint8 StatusReg;

  // Make sure all the Fifo's are cleared and Bus is Not busy.
  do
  {
    StatusReg = XIo_In8(CoreAddress + XIIC_SR_REG_OFFSET);
    //xil_printf("[fmc_imageov_iic_write] XIo_In8(CoreAddress + XIIC_SR_REG_OFFSET) => 0x%02X\n\r", StatusReg );
    StatusReg = StatusReg & (XIIC_SR_RX_FIFO_EMPTY_MASK |
                             XIIC_SR_TX_FIFO_EMPTY_MASK |
                             XIIC_SR_BUS_BUSY_MASK);
  } while (StatusReg != (XIIC_SR_RX_FIFO_EMPTY_MASK |
			                XIIC_SR_TX_FIFO_EMPTY_MASK));

  /*
   * A temporary write buffer must be used which contains both the address
   * and the data to be written, put the address in first 
   */
  WriteBuffer[0] = RegAddress;

  /*
   * Put the data in the write buffer following the address.
   */
  for (Index = 0; Index < ByteCount; Index++)
  {
    WriteBuffer[Index + 1] = BufferPtr[Index];
  }

  /*
   * Write data at the specified address.
   */
  SentByteCount = XIic_DynSend(CoreAddress, ChipAddress, WriteBuffer,
                               ByteCount + 1, XIIC_STOP);
  if (SentByteCount < 1) { SentByteCount = 1; }
                               
  // Return the number of bytes written.
  return SentByteCount - 1;
}


/******************************************************************************
* This function reads a number of bytes from an IIC chip into a
* specified buffer.
*
* @param    CoreAddress contains the address of the IIC core.
* @param    ChipAddress contains the address of the IIC core.
* @param    RegAddress contains the address of the register to write to.
* @param    BufferPtr contains the address of the data buffer to be filled.
* @param    ByteCount contains the number of bytes in the buffer to be read.
*           This value is constrained by the page size of the device such
*           that up to 64K may be read in one call.
*
* @return   The number of bytes read. A value less than the specified input
*           value indicates an error.
*
* @note     None.
*
******************************************************************************/
int fmc_ipmi_iic_read(Xuint32 CoreAddress, Xuint8 ChipAddress, Xuint8 RegAddress, 
                      Xuint8 *BufferPtr, Xuint8 ByteCount)
{
  Xuint8 ReceivedByteCount = 0;
  Xuint8 SentByteCount = 0;
  Xuint8 StatusReg;
  XStatus TestStatus=XST_FAILURE;
  int cnt = 0;

  // Make sure all the Fifo's are cleared and Bus is Not busy.
  do
  {
    StatusReg = XIo_In8(CoreAddress + XIIC_SR_REG_OFFSET);
    //xil_printf("[fmc_imageov_iic_read] XIo_In8(CoreAddress + XIIC_SR_REG_OFFSET) => 0x%02X\n\r", StatusReg );
    StatusReg = StatusReg & (XIIC_SR_RX_FIFO_EMPTY_MASK |
	                          XIIC_SR_TX_FIFO_EMPTY_MASK |
                             XIIC_SR_BUS_BUSY_MASK);
  } while (StatusReg != (XIIC_SR_RX_FIFO_EMPTY_MASK |
			                XIIC_SR_TX_FIFO_EMPTY_MASK));

  // Position the Read pointer to specific location.
  do
  {
    StatusReg = XIo_In8(CoreAddress + XIIC_SR_REG_OFFSET);
    //xil_printf("[fmc_imageov_iic_read] XIo_In8(CoreAddress + XIIC_SR_REG_OFFSET) => 0x%02X\n\r", StatusReg );
    if(!(StatusReg & XIIC_SR_BUS_BUSY_MASK))
    {
      SentByteCount = XIic_DynSend(CoreAddress, ChipAddress, 
                                  (Xuint8 *)&RegAddress, 1,
    								        XIIC_REPEATED_START);
    }
    cnt++;
  }while(SentByteCount != 1 && (cnt < 100000));
  
  // Error writing chip address so return SentByteCount
  if (SentByteCount < 1) { return SentByteCount; }

  // Receive the data.
  ReceivedByteCount = XIic_DynRecv(CoreAddress, ChipAddress, BufferPtr, 
                                   ByteCount);

  // Return the number of bytes received.
  return ReceivedByteCount;
}

