/* $Id: */
/******************************************************************************
*
* (c) Copyright 2009 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file example.c
 *
 * This file demonstrates how to use Xilinx Video DMA (VDMA) driver on Xilinx
 * MVI Video DMA devices. 1 VDMA device is set to transfer the video frames to
 * the memory, while another VDMA device is set to transfer the frames from the
 * same memory location.
 *
 * This code makes the following assumptions:
 *
 * -Caching is disabled. Flushing and Invalidation operations for data buffer
 *  need to be added to this code if it is not the case.
 *
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -------------------------------------------------------
 * 1.00a xd   05/07/09 First release
 * </pre>
 *
 * ****************************************************************************
 */

#include "xvdma.h"
#include "xparameters.h"

/*
 * Device related constants. Defined in xparameters.h
 */
#define DMA_IN_DEVICE_ID     XPAR_VDMA_1_DEVICE_ID
#define DMA_OUT_DEVICE_ID    XPAR_VDMA_0_DEVICE_ID

/*
 * Frame buffer constants
 */
#define FRAME_BUFFER_ADDR    0x18000000
#define FSTORE_DATA_WIDTH    16
#define C_DATA_WIDTH         16

/*
 * DMA transfer direction definitions
 */
#define WRITE                1
#define READ                 2

/*
 * VDMA Device related data structures
 */
XVDma VDmaIn;                /* VDMA In Device driver instance */
XVDma VDmaOut;               /* VDMA Out Device driver instance */
XVDma_Config *VDmaCfgPtr;    /* DMA device configuration pointer */

int FrameNum;                /* The number of frames to transfer */
int FrameWidth;              /* Frame width */
int FrameHeight;             /* Frame height */
int BlockWidth;              /* Width of the block to transfer */
int BlockHeight;             /* Height of the block to transfer */
int HoriOffset;              /* The horizontal offset of block to transfer from
                                the top-left corner of the frame */
int VertOffset;              /* The vertical offset of block to transfer from
                                the top-left corner of the frame */
int Circular;                /* Keep DMA going in circular way */
int SyncEnable;              /* Enable the sync between the VDma In and Out
                                devices */

/*
 * Function prototypes
 */
static int  VDmaExample(int VDma_In_Dev_Id, int VDma_Out_Dev_Id);
static int  VDmaInit(int VDma_In_Dev_Id, int VDma_Out_Dev_Id);
static void VDmaStart(XVDma *VDmaPtr, int FrameNum,
                      int BlockWidth, int BlockHeight,
                      int HoriOffset, int VertOffset,
                      int FrameWidth, int FrameHeight,
                      int FirstFrameAddress,
                      int Circular, int SyncEnable,
                      int Direction);

/*****************************************************************************/
/**
*
* This is the main function for the VDMA example.
*
* @param    None.
*
* @return   0 to indicate success, otherwise 1.
*
* @note     None.
*
******************************************************************************/
int main(void)
{
    int Status;

    /*
     * Call the VDMA example, use the Device IDs generated in xparameters.h
     */
    Status = VDmaExample(DMA_IN_DEVICE_ID, DMA_OUT_DEVICE_ID);
    if (Status != 0) {
        return 1;
    }

    return 0;
}

/*****************************************************************************/
/**
*
* This function is the entry of the feature demonstrations on MVI Video DMA
* core. It initializes the VDMA devices, then start the VDMA devices for video
* frame transfer.
*
* @param    VDma_In_Dev_Id is the device ID of the VDMA In device.
*
* @param    VDma_Out_Dev_Id is the device ID of the VDMA Out device.
*
* @return   0 if all tests pass, 1 otherwise.
*
* @note     None.
*
******************************************************************************/
static int VDmaExample(int VDma_In_Dev_Id, int VDma_Out_Dev_Id)
{
    int Status;

    /* Initialize the VDMA instances */

    Status = VDmaInit(VDma_In_Dev_Id, VDma_Out_Dev_Id);
    if (Status != XST_SUCCESS) {
        return 1;
    }

	/* Start the VDMA devices */

    FrameNum = 5;
    FrameWidth = 1280;
    FrameHeight = 720;
    BlockWidth = 1280;
    BlockHeight = 720;
    HoriOffset = 0;
    VertOffset = 0;
    Circular = 1;
    SyncEnable = 1;

	VDmaStart(&VDmaIn,  FrameNum, BlockWidth, BlockHeight, HoriOffset,
	          VertOffset, FrameWidth, FrameHeight, FRAME_BUFFER_ADDR, Circular,
	          SyncEnable, WRITE);

	VDmaStart(&VDmaOut, FrameNum, BlockWidth, BlockHeight, HoriOffset,
	          VertOffset, FrameWidth, FrameHeight, FRAME_BUFFER_ADDR, Circular,
	          SyncEnable, READ);

    /* Return success */

    return 0;
}

/*****************************************************************************/
/**
*
* This function initializes the VDMA devices and driver instances so they are
* ready to do the DMA transfer operations.
*
* @param    VDma_In_Dev_Id is the device ID of the VDMA In device.
*
* @param    VDma_Out_Dev_Id is the device ID of the VDMA Out device.
*
* @return   0 if the initialization is successful; 1 otherwise.
*
* @note     None.
*
******************************************************************************/
int VDmaInit(int VDma_In_Dev_Id, int VDma_Out_Dev_Id)
{
    int Status;

    /* Initialize the Video DMA instances */

    VDmaCfgPtr = XVDma_LookupConfig(VDma_In_Dev_Id);
    Status = XVDma_CfgInitialize(&VDmaIn, VDmaCfgPtr, VDmaCfgPtr->BaseAddress);
    if (Status != XST_SUCCESS) {
        return 1;
    }

    VDmaCfgPtr = XVDma_LookupConfig(VDma_Out_Dev_Id);
    Status = XVDma_CfgInitialize(&VDmaOut, VDmaCfgPtr, VDmaCfgPtr->BaseAddress);
    if (Status != XST_SUCCESS) {
        return 1;
    }

    /* Reset the devices */

    XVDma_Reset(&VDmaIn);
    XVDma_Reset(&VDmaOut);

    return 0;
}

/*****************************************************************************/
/**
*
* This function launches a DMA transfer operation
*
* @param    VDmaPtr points to the VDMA device instance to work on.
*
* @param    FrameNum is the number of the frames to transfer
*
* @param    BlockWidth is the Width of block to transfer in the frame.
*
* @param    BlockHeight is the Height of block to transfer in the frame.
*
* @param    HoriOffset is the horizontal offset of block to transfer from
*           the top-left corner in the frame.
*
* @param    VertOffset is the vertical offset of block to transfer from
*           the top-left corner in the frame.
*
* @param    FrameWidth is the width of the frame.
*
* @param    FrameHeight is the height of the frame.
*
* @param    FirstFrameAddress is the address of the 1st frame. The addresses
*           of the other frames are calculated using this parameter and
*           the dimension of the frame (see previous 2 parameters)
*
* @param    Circular indicates if the DMA operation should keep going after
*           the last frame was transferred by jumping to the 1st frame.
*
* @pamam    SyncEnable indicates if to use the sync between the VDMA In and
*           Out devices.
*
* @pamam    Direction indicates the direction the DMA transfer. Use WRITE
*           for transfer towards the memory, and READ for transfer from
*           the memory.
*
* @return   0 if the initialization is successful; 1 otherwise.
*
* @note     None.
*
******************************************************************************/
static void VDmaStart(XVDma *VDmaPtr, int FrameNum,
                      int BlockWidth, int BlockHeight,
                      int HoriOffset, int VertOffset,
                      int FrameWidth, int FrameHeight,
                      int FirstFrameAddress,
                      int Circular, int SyncEnable,
                      int Direction)
{
    XVDmaFrameCounter FrameCounterCfg;
    XVDma_DmaSetup DmaSetup;
    int FrameSize;
    int BlockOffset;
    int i;

    /* Setup Frame Count */

    FrameCounterCfg.WriteFrameCount = FrameNum & 0xff;
    FrameCounterCfg.ReadFrameCount = FrameNum & 0xff;
    FrameCounterCfg.WriteDelayTimerCount = 0;
    FrameCounterCfg.ReadDelayTimerCount = 0;

    XVDma_SetFrameCounter(VDmaPtr, &FrameCounterCfg);

    /* Calculate the frame size */

    FrameSize = (FrameWidth * FSTORE_DATA_WIDTH / 8) * FrameHeight;

    /*
     * Calculate the offset of the block to transfer from the top-left corner
     * of the frame
     */

    BlockOffset = (FrameWidth * FSTORE_DATA_WIDTH / 8) * VertOffset;
    BlockOffset += (HoriOffset * FSTORE_DATA_WIDTH / 8);

    /* Set up the DMA operation configuration */

	memset(&DmaSetup, 0, sizeof(DmaSetup));

    DmaSetup.VertSizeInput = BlockHeight - 1;
    DmaSetup.HoriSizeInput = BlockWidth;
    DmaSetup.Stride = FrameWidth * FSTORE_DATA_WIDTH / C_DATA_WIDTH;
    DmaSetup.FrameDelay = 0;
    DmaSetup.EnableCircularBuf = Circular ? TRUE : FALSE;
    DmaSetup.EnableSync = SyncEnable ? TRUE : FALSE;
    DmaSetup.PointNum = 0;
    DmaSetup.EnableFrameCounter = FALSE;

    for(i = 0; i < VDmaPtr->Config.MaxFrameStoreNum; i++) {
        DmaSetup.FrameStoreStartAddr[i] = FirstFrameAddress + i * FrameSize
                                             + BlockOffset;
    }
    DmaSetup.FixedFrameStoreAddr = 0;

    /* Kick off DMA transfer */

    if(Direction == WRITE) {
        XVDma_StartWriteFrame(VDmaPtr, &DmaSetup);
    }
    else {
        XVDma_StartReadFrame(VDmaPtr, &DmaSetup);
    }
}
