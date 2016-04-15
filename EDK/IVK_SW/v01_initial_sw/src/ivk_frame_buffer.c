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
// Create Date:         Feb 11, 2010
// Design Name:         IVK Frame Buffer
// Module Name:         ivk_frame_buffer.c
// Project Name:        IVK
// Target Devices:      Spartan-6
// Avnet Boards:        IVK
//
// Tool versions:       ISE 11.4
//
// Description:         IVK Frame Buffer Control
//                      - using the Xilinx VideoDMA LogiCore
//
// Dependencies:        
//
// Revision:            Feb 11, 2010: 1.00 Initial version
//                      Sep 14, 2010: 1.01 Added "#include <string.h>"
//                                         for memset() declaration
//
//----------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Located in: microblaze_0/include/
#include "xbasic_types.h"
#include "xutil.h"
#include "xparameters.h"
#include "xstatus.h"

#include "ivk_frame_buffer.h"
#include "ivk_video_resolution.h"


#include "xvdma.h"

/*
 * Device related constants. Defined in xparameters.h
 */
#define DMA_WRITE_DEVICE_ID  XPAR_VDMA_0_DEVICE_ID
#define DMA_READ_DEVICE_ID   XPAR_VDMA_1_DEVICE_ID

/*
 * Frame buffer constants
 */
#define FRAME_BUFFER_ADDR    0x11000000
#define FSTORE_NUM_FRAMES    3
#define FSTORE_DATA_WIDTH    32
#define C_DATA_WIDTH         32

/*
 * DMA transfer direction definitions
 */
#define WRITE                1
#define READ                 0

/*
 * VDMA Device related data structures
 */
XVDma VDmaWrite;             /* VDMA In Device driver instance */
XVDma VDmaRead;              /* VDMA Out Device driver instance */
XVDma_Config *VDmaCfgPtr;    /* DMA device configuration pointer */


/*
 * Function prototypes
 */
static int  VDmaInit(int VDma_Write_Dev_Id, int VDma_Read_Dev_Id);
static void VDmaStart(XVDma *VDmaPtr, int FrameNum,
                      int BlockWidth, int BlockHeight,
                      int HoriOffset, int VertOffset,
                      int FrameWidth, int FrameHeight,
                      int FirstFrameAddress,
                      int Circular, int SyncEnable,
                      int Direction);



Xuint32 ivk_fb_init(void)
{
   static int bVDmaInitialized = 0;
   
   if ( !bVDmaInitialized )
   {
      VDmaInit(DMA_WRITE_DEVICE_ID,DMA_READ_DEVICE_ID);
      bVDmaInitialized = 1;
   }
}

/* Set Input Video Resolution
 * Returns 0 if params were sent successfully, otherwise not 
 */
Xuint32 ivk_fb_set_input_resolution(Xuint32 resolutionId, Xuint32 enable)
{
   Xuint32 Width  = ivk_vres_get_width(resolutionId);
   Xuint32 Height = ivk_vres_get_height(resolutionId);

   if ( enable )
   {   
      VDmaStart(
         &VDmaWrite,        // VDmaPtr 
         FSTORE_NUM_FRAMES, // FrameNum
         Width,             // BlockWidth
         Height,            // BlockHeight
         0,                 // HoriOffset
         0,                 // VertOffset
         Width,             // FrameWidth
         Height,            // FrameHeight
         FRAME_BUFFER_ADDR, // FirstFrameAddress
         1,                 // Circular
         1,                 // SyncEnable
         WRITE              // Direction
      );
   }              
   else
   {
      Xuint32 reg;
      reg = XVDma_ReadReg(VDmaWrite.Config.BaseAddress, XVDMA_CTL);
      reg = 0x00000000;
      XVDma_WriteReg( VDmaWrite.Config.BaseAddress, XVDMA_CTL, reg );
   }
   return 0;
}

/* Set Output Video Resolution
 * Returns 0 if params were sent successfully, otherwise not 
 */
Xuint32 ivk_fb_set_output_resolution(Xuint32 resolutionId, Xuint32 enable)
{
   Xuint32 Width  = ivk_vres_get_width(resolutionId);
   Xuint32 Height = ivk_vres_get_height(resolutionId);

   if ( enable )
   {   
      VDmaStart(
         &VDmaRead,         // VDmaPtr 
         FSTORE_NUM_FRAMES, // FrameNum
         Width,             // BlockWidth
         Height,            // BlockHeight
         0,                 // HoriOffset
         0,                 // VertOffset
         Width,             // FrameWidth
         Height,            // FrameHeight
         FRAME_BUFFER_ADDR, // FirstFrameAddress
         1,                 // Circular
         1,                 // SyncEnable
         READ               // Direction
      );
   }
   else
   {
      Xuint32 reg;
      reg = XVDma_ReadReg(VDmaRead.Config.BaseAddress, XVDMA_CTL);
      reg = 0x00000000;
      XVDma_WriteReg( VDmaRead.Config.BaseAddress, XVDMA_CTL, reg );
   }
   
   return 0;
}

Xuint32 ivk_fb_get_width(Xuint32 resolutionId)
{
   return ivk_vres_get_width(resolutionId);
}

Xuint32 ivk_fb_get_height(Xuint32 resolutionId)
{
   return ivk_vres_get_height(resolutionId);
}

Xuint32 ivk_fb_get_stride(Xuint32 resolutionId)
{
   Xuint32 Width  = ivk_vres_get_width(resolutionId);
   Xuint32 Stride = (Width * 4);
   
   return Stride;
}

Xuint32 ivk_fb_get_offset(Xuint32 resolutionId)
{
   return 0;
}

Xuint32 ivk_fb_get_current_frame_index( void )
{
   Xuint32 StatusFrameStore = XVDma_ReadReg(VDmaRead.Config.BaseAddress, XVDMA_SFS );
   Xuint32 FrameIndex       = (StatusFrameStore & 0x000000F0) >> 4;
   
   return FrameIndex;
}

Xuint32 ivk_fb_get_current_frame_address( void )
{
   Xuint32 FrameIndex = ivk_fb_get_current_frame_index();
   Xuint32 FrameAddress;
   
   switch (FrameIndex)
   {
   case 0:
      FrameAddress = XVDma_ReadReg(VDmaRead.Config.BaseAddress, XVDMA_CRSA00 );
      break;
   case 1:
      FrameAddress = XVDma_ReadReg(VDmaRead.Config.BaseAddress, XVDMA_CRSA01 );
      break;
   case 2:
      FrameAddress = XVDma_ReadReg(VDmaRead.Config.BaseAddress, XVDMA_CRSA02 );
      break;
   default:
      FrameAddress = XVDma_ReadReg(VDmaRead.Config.BaseAddress, XVDMA_CRSA00 );
      break;
   }
   
   xil_printf( "FrameAddress = 0x%08X\n\r", FrameAddress );
   
   return FrameAddress;
}

Xuint32 ivk_fb_clear_memory( void )
{
   // Clear start of external memory (video buffers and BSS)
   memset((void *)FRAME_BUFFER_ADDR, 0, (1<<23)*FSTORE_NUM_FRAMES); 

   return 0;
}

const BORDER = 10;
void ivk_fb_disp_colorbar(Xuint32 x_size, Xuint32 y_size, Xuint32 frameAdr, Xuint32 stride)
{
#if (C_DATA_WIDTH == 32)
	Xuint32 i,j;
	Xuint32 startAdr;
	Xuint32 writeData, readData, expectData;

   // Data in memory corresponds to XSVI pixel data ordering:
   // [31:24] Green
   // [23:16] Blue
   // [15: 8] Red
   // [ 7: 0] ---
	
	for (j=0; j<y_size; j++)
	{
		startAdr = frameAdr + (j*stride);	
		for (i=0; i<x_size; i++)
		{
                        // Horizontal Ramp
			if((j >= ((y_size>>1)-40)) && (j < ((y_size>>1)-20)))
			{
				writeData = ((i&0xff) << 8) | ((i&0xff) << 16) | (i&0xff) << 24; // W (R+G+B)
			}
			else if((j >= ((y_size>>1)-20) ) && (j < (y_size>>1) ))
			{
				writeData = ((i&0xff) << 8); // R
			}
			else if((j >= (y_size>>1) ) && (j < ((y_size>>1)+20)))
			{
				writeData = ((i&0xff) << 24 ); // G
			}
			else if((j >= ((y_size>>1)+20)) && (j < ((y_size>>1)+40) ))
			{
				writeData = (i&0xff) << 16; // B
			}
			else
			{
            // Color Bar
				if( i < x_size/8 )
				{
					writeData = 0xFFFFFF00; // W (R+G+B)
				}
				else if(i < x_size*2/8)
				{
					writeData = 0xFF00FF00; // Y (R+G)
				}
				else if(i < x_size*3/8)
				{
					writeData = 0xFFFF0000; // C (G+B)
				}
				else if(i < x_size*4/8)
				{
					writeData = 0xFF000000; // G
				}
				else if(i < x_size*5/8)
				{
					writeData = 0x00FFFF00; // M (R+B)
				}
				else if(i < x_size*6/8)
				{
					writeData = 0x0000FF00; // R
				}
				else if(i < x_size*7/8)
				{
					writeData = 0x00FF0000; // B
				}
				else
				{
					writeData = 0x00000000; // K
				}
			}
         // Inverse Color Border 
			if((i == (BORDER-1)) || (i == (x_size-BORDER)) || (j == (BORDER-1)) || (j == (y_size-BORDER))) 
			{
				writeData = writeData ^ 0xFFFFFF00;
			}
			* (volatile unsigned long *) (startAdr + i*4) = writeData;
		}
	}
#endif

#if (C_DATA_WIDTH == 16)
	Xuint32 i,j;
	Xuint32 startAdr;
   Xuint16 Y, Cb, Cr;

   // Data in memory corresponds to XSVI pixel data ordering:
   // [15: 8] Luma
   // [ 7: 0] Chroma
   	
	for (j=0; j<y_size; j++)
	{
		startAdr = frameAdr + (j*stride);	
		for (i=0; i<x_size; i += 2)
		{
         // Horizontal Ramp => TODO (for now, experimental ...)
			if((j >= ((y_size>>1)-40)) && (j < ((y_size>>1)-20)))
			{
            // Gray ramp
            Y  = (i&0xFF);
            Cr = 0x7F;
            Cb = 0x7F;
			}
			else if((j >= ((y_size>>1)-20) ) && (j < (y_size>>1) ))
			{
            // ?? ramp
            Y  = 0xFF;
            Cr = (i&0xFF);
            Cb = 0x7F;
			}
			else if((j >= (y_size>>1) ) && (j < ((y_size>>1)+20)))
			{
            // ?? ramp
            Y  = 0xFF;
            Cr = 0x7F;
            Cb = (i&0xFF);
			}
			else if((j >= ((y_size>>1)+20)) && (j < ((y_size>>1)+40) ))
			{
            // ?? ramp
            Y  = 0xFF;
            Cr = (i&0xFF);
            Cb = (i&0xFF);
			}
			else
			{
            // Color Bars
				if( i < x_size/8 )
				{
               // White
               Y  = 0xFF;
               Cr = 0x7F;
               Cb = 0x7F;
				}
				else if(i < x_size*2/8)
				{
               // Yellow
               Y  = 0xE2;
               Cr = 0x94;
               Cb = 0x00;
				}
				else if(i < x_size*3/8)
				{
               // Cyan
               Y  = 0xB3;
               Cr = 0x00;
               Cb = 0xAB;
				}
				else if(i < x_size*4/8)
				{
               // Green
               Y  = 0x95;
               Cr = 0x11;
               Cb = 0x28;
				}
				else if(i < x_size*5/8)
				{
               // Magenta
               Y  = 0x69;
               Cr = 0xED;
               Cb = 0xD6;
				}
				else if(i < x_size*6/8)
				{
					// Red
               Y  = 0x4C;
               Cr = 0xFF;
               Cb = 0x53;
				}
				else if(i < x_size*7/8)
				{
               // Blue
               Y  = 0x1D;
               Cr = 0x6A;
               Cb = 0xFF;
				}
				else
				{
               // Black
               Y  = 0x00;
               Cr = 0x7F;
               Cb = 0x7F;
				}
			}
         // Inverse Color Border => Inverse Luma only
			if((i == (BORDER-1)) || (i == (x_size-BORDER)) || (j == (BORDER-1)) || (j == (y_size-BORDER))) 
			{
				Y  = Y  ^ 0xFF;
				Cr = Cr ^ 0xFF;
				Cb = Cb ^ 0xFF;
			}
			* (volatile unsigned short *) (startAdr + (i+0)*2) = (Y << 8) | Cr;
			* (volatile unsigned short *) (startAdr + (i+1)*2) = (Y << 8) | Cb;
		}
	}
#endif
   
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
int VDmaInit(int VDma_Write_Dev_Id, int VDma_Read_Dev_Id)
{
   int Status;

   /* Initialize the Video DMA instances */

   VDmaCfgPtr = XVDma_LookupConfig(VDma_Write_Dev_Id);
   if (VDmaCfgPtr == NULL) {
      print("XVDma_LookupConfig failed!\r\n");
      return 1;
   }    
   Status = XVDma_CfgInitialize(&VDmaWrite, VDmaCfgPtr, VDmaCfgPtr->BaseAddress);
   if (Status != XST_SUCCESS) {
      print("XVDma_CfgInitialize failed!\r\n");
      return 1;
   }

   VDmaCfgPtr = XVDma_LookupConfig(VDma_Read_Dev_Id);
   if (VDmaCfgPtr == NULL) {
      print("XVDma_LookupConfig failed!\r\n");
      return 1;
   }    
   Status = XVDma_CfgInitialize(&VDmaRead, VDmaCfgPtr, VDmaCfgPtr->BaseAddress);
   if (Status != XST_SUCCESS) {
      print("XVDma_CfgInitialize failed!\r\n");
      return 1;
   }

   /* Reset the devices */

   XVDma_Reset(&VDmaWrite);
   XVDma_Reset(&VDmaRead);

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

