/* $Id: */

/******************************************************************************
*
*       XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
*       AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
*       SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
*       OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
*       APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
*       THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
*       AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
*       FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
*       WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
*       IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
*       REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
*       INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*       FOR A PARTICULAR PURPOSE.
*
*       (c) Copyright 2008 Xilinx Inc.
*       All rights reserved.
*
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xvdma_hw.h
*
* This header file contains identifiers and register-level driver functions (or
* macros) that can be used to access the Xilinx MVI Video DMA device.
*
* For more information about the operation of this device, see the hardware
* specification and documentation in the higher level driver xvdma.h source
* code file.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a xd   05/16/08 First release
* </pre>
*
******************************************************************************/

#ifndef XVDMA_HW_H      /* prevent circular inclusions */
#define XVDMA_HW_H      /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xio.h"

/************************** Constant Definitions *****************************/

/**
 * Register Offsets
 */
#define XVDMA_CTL            0x000    /**< Control */
#define XVDMA_CC             0x00C    /**< Control Counters */
#define XVDMA_SC             0x010    /**< Status Counters */
#define XVDMA_SFS            0x014    /**< Status Frame Store */
#define XVDMA_SV             0x018    /**< Status Version */
#define XVDMA_CWFS           0x020    /**< Control Write Frame Size */
#define XVDMA_CWS            0x024    /**< Control Write Stride */
#define XVDMA_CRFS           0x028    /**< Control Read Frame Size */
#define XVDMA_CRS            0x02C    /**< Control Read Stride */

#define XVDMA_CWSA00         0x030    /**< DMA Write Start Address of Frame
                                        *  Store 00 */
#define XVDMA_CWSA01         0x034    /**< DMA Write Start Address of Frame
                                        *  Store 01 */
#define XVDMA_CWSA02         0x038    /**< DMA Write Start Address of Frame
                                        *  Store 02 */
#define XVDMA_CWSA03         0x03C    /**< DMA Write Start Address of Frame
                                        *  Store 03 */
#define XVDMA_CWSA04         0x040    /**< DMA Write Start Address of Frame
                                        *  Store 04 */
#define XVDMA_CWSA05         0x044    /**< DMA Write Start Address of Frame
                                        *  Store 05 */
#define XVDMA_CWSA06         0x048    /**< DMA Write Start Address of Frame
                                        *  Store 06 */
#define XVDMA_CWSA07         0x04C    /**< DMA Write Start Address of Frame
                                        *  Store 07 */
#define XVDMA_CWSA08         0x050    /**< DMA Write Start Address of Frame
                                        *  Store 08 */
#define XVDMA_CWSA09         0x054    /**< DMA Write Start Address of Frame
                                        *  Store 09 */
#define XVDMA_CWSA10         0x058    /**< DMA Write Start Address of Frame
                                        *  Store 10 */
#define XVDMA_CWSA11         0x05C    /**< DMA Write Start Address of Frame
                                        *  Store 11 */
#define XVDMA_CWSA12         0x060    /**< DMA Write Start Address of Frame
                                        *  Store 12 */
#define XVDMA_CWSA13         0x064    /**< DMA Write Start Address of Frame
                                        *  Store 13 */
#define XVDMA_CWSA14         0x068    /**< DMA Write Start Address of Frame
                                        *  Store 14 */
#define XVDMA_CWSA15         0x06C    /**< DMA Write Start Address of Frame
                                        *  Store 15 */

#define XVDMA_CRSA00         0x070    /**< DMA Read Start Address of Frame
                                        *  Store 00 */
#define XVDMA_CRSA01         0x074    /**< DMA Read Start Address of Frame
                                        *  Store 01 */
#define XVDMA_CRSA02         0x078    /**< DMA Read Start Address of Frame
                                        *  Store 02 */
#define XVDMA_CRSA03         0x07C    /**< DMA Read Start Address of Frame
                                        *  Store 03 */
#define XVDMA_CRSA04         0x080    /**< DMA Read Start Address of Frame
                                        *  Store 04 */
#define XVDMA_CRSA05         0x084    /**< DMA Read Start Address of Frame
                                        *  Store 05 */
#define XVDMA_CRSA06         0x088    /**< DMA Read Start Address of Frame
                                        *  Store 06 */
#define XVDMA_CRSA07         0x08C    /**< DMA Read Start Address of Frame
                                        *  Store 07 */
#define XVDMA_CRSA08         0x090    /**< DMA Read Start Address of Frame
                                        *  Store 08 */
#define XVDMA_CRSA09         0x094    /**< DMA Read Start Address of Frame
                                        *  Store 09 */
#define XVDMA_CRSA10         0x098    /**< DMA Read Start Address of Frame
                                        *  Store 10 */
#define XVDMA_CRSA11         0x09C    /**< DMA Read Start Address of Frame
                                        *  Store 11 */
#define XVDMA_CRSA12         0x0A0    /**< DMA Read Start Address of Frame
                                        *  Store 12 */
#define XVDMA_CRSA13         0x0A4    /**< DMA Read Start Address of Frame
                                        *  Store 13 */
#define XVDMA_CRSA14         0x0A8    /**< DMA Read Start Address of Frame
                                        *  Store 14 */
#define XVDMA_CRSA15         0x0AC    /**< DMA Read Start Address of Frame
                                        *  Store 15 */

#define XVDMA_RESET          0x100    /**< Reset Register */
#define XVDMA_GIER           0x21C    /**< Global Interrupt Enable Register */
#define XVDMA_ISR            0x220    /**< Interrupt Status Register */
#define XVDMA_IER            0x228    /**< Interrupt Enable Register */

/**
 * Control Register bit definition
 */
#define XVDMA_CTL_WDMA_RST   0x40000000 /**< Clear Write DMA Command and Flush
                                          *  Write Data */
#define XVDMA_CTL_RDMA_RST   0x20000000 /**< Clear Read DMA Command and Flush
                                          *  Read Data */
#define XVDMA_CTL_WFIFO_RST  0x10000000 /**< Flush Write Data */
#define XVDMA_CTL_RFIFO_RST  0x08000000 /**< Flush Read Data */
#define XVDMA_CTL_RFRAME_PTR 0x00F00000 /**< Read Frame Store Pointer */
#define XVDMA_CTL_RFRAME_SHIFT 20       /**< Read Frame Store Pointer Shift */
#define XVDMA_CTL_WFRAME_PTR 0x000F0000 /**< Write Frame Store Pointer */
#define XVDMA_CTL_WFRAME_SHIFT 16       /**< Write Frame Store Pointer Shift */
#define XVDMA_CTL_RP_NUM     0x0000F000 /**< Source pointer for Gen-Lock
                                          *  comparisons */
#define XVDMA_CTL_RP_NUM_SHIFT 12       /**< Source pointer field Shift */
#define XVDMA_CTL_WP_NUM     0x00000F00 /**< Destination pointer for Gen-Lock
                                          *  comparisons */
#define XVDMA_CTL_WP_NUM_SHIFT 8        /**< Destination pointer field Shift */
#define XVDMA_CTL_FRMCNT_EN  0x00000080 /**< Frame Counter Enable */
#define XVDMA_CTL_HW_LOCKOUT 0x00000040 /**< Disable Hardware from writing
                                          *  command interface */
#define XVDMA_CTL_DUPLEX     0x00000020 /**< Duplex: 0=Half duplex; 1=Full
                                          *  duplex */
#define XVDMA_CTL_H_CROP_EN  0x00000010 /**< Horizontal Cropping Enable */
#define XVDMA_CTL_SYNC_EN    0x00000008 /**< compare current frame store
                                          *  address pointer to incoming frame
                                          *  store address pointer */
#define XVDMA_CTL_CIR_BUF_EN 0x00000004 /**< Circular Buffer Enable */
#define XVDMA_CTL_RDMA_EN    0x00000002 /**< DMA Read Enable */
#define XVDMA_CTL_WDMA_EN    0x00000001 /**< DMA Write Enable */

/**
 * Control Counter Register
 */
#define XVDMA_CC_R_FRAMECNT         0xFF000000 /**< Read Frame Counter Value */
#define XVDMA_CC_R_FRAMECNT_SHIFT   24         /**< Read Frame Counter Value
                                                 *  Shift */
#define XVDMA_CC_R_DELAYTIMER       0x00FF0000 /**< Read Delay Timer Value */
#define XVDMA_CC_R_DELAYTIMER_SHIFT 16         /**< Read Delay Timer Value
                                                 *  Shift */
#define XVDMA_CC_W_FRAMECNT         0x0000FF00 /**< Write Frame Counter Value
                                                 */
#define XVDMA_CC_W_FRAMECNT_SHIFT   8          /**< Write Frame Counter Value
                                                 *  Shift */
#define XVDMA_CC_W_DELAYTIMER       0x000000FF /**< Write Delay Timer Value */

/**
 * Status Counters
 */
#define XVDMA_SC_R_FRAMECNT         0xFF000000 /**< Read Frame Counter Value */
#define XVDMA_SC_R_DELAYTIMER       0x00FF0000 /**< Read Delay Timer Value */
#define XVDMA_SC_W_FRAMECNT         0x0000FF00 /**< Write Frame Counter Value
                                                 */
#define XVDMA_SC_W_DELAYTIMER       0x000000FF /**< Write Delay Timer Value */

/**
 * Status Frame Store
 */
#define XVDMA_SFS_VDMA_BUSY    0X80000000 /**< DMA transaction in progress */
#define XVDMA_SFS_CMD_FULL     0X40000000 /**< Command FIFO full */
#define XVDMA_SFS_CMD_AFULL    0X20000000 /**< Command FIFO almost full */
#define XVDMA_SFS_WFIFO_FULL   0X10000000 /**< Write FIFO full */
#define XVDMA_SFS_WFIFO_AFULL  0X08000000 /**< Write FIFO almost full */
#define XVDMA_SFS_RFIFO_EMPTY  0X04000000 /**< Read FIFO full */
#define XVDMA_SFS_RFIFO_AEMPTY 0X02000000 /**< Read FIFO almost full */
#define XVDMA_SFS_CFIFO_ACT    0X01000000 /**< Active Command FIFO */
#define XVDMA_SFS_WFIFO_ACT    0X00800000 /**< Active Write FIFO */
#define XVDMA_SFS_RFIFO_ACT    0X00400000 /**< Active Read FIFO */
#define XVDMA_SFS_MAX_FRAME    0X000F0000 /**< The index of the last valid
                                            *  Frame Store */
#define XVDMA_SFS_CUR_RFRAME   0x000000F0 /**< Current Read Frame Store */
#define XVDMA_SFS_CUR_WFRAME   0x0000000F /**< Current Write Frame Store */

/**
 * Status Version
 */
#define XVDMA_SV_MAJOR       0xF0000000 /**< Version Major */
#define XVDMA_SV_MINOR       0x0FF00000 /**< Version Minor */
#define XVDMA_SV_REV         0x000F0000 /**< Version Revision */
#define XVDMA_SV_NUM         0x0000FFFF /**< Revision Number */

/**
 * Control Write Frame Size
 */
#define XVDMA_CWFS_V_SIZE    0x0FFF0000 /**< Write DMA Vertical size input */
#define XVDMA_CWFS_V_SHIFT   16         /**< Write DMA Vertical size input
                                          *  shift */
#define XVDMA_CWFS_H_SIZE    0x00000FFF /**< Write DMA Horizontal size input */

/**
 * Control Write Stride
 */
#define XVDMA_CWS_WF_DELAY   0x000F0000 /**< Write Frame Delay */
#define XVDMA_CWS_WF_DELAY_SHIFT 16		/**< Write Frame Delay field shift */
#define XVDMA_CWS_W_STRIDE   0x00000FFF /**< Write DMA Stride */

/**
 * Control Read Frame Size
 */
#define XVDMA_CRFS_V_SIZE    0x0FFF0000 /**< Read DMA Vertical size input */
#define XVDMA_CRFS_V_SHIFT   16         /**< Read DMA Vertical size input shift
                                          */
#define XVDMA_CRFS_H_SIZE    0x00000FFF /**< Read DMA Horizontal size input */

/**
 * Control Read Stride
 */
#define XVDMA_CRS_RF_DELAY   0x000F0000 /**< Read Frame Delay */
#define XVDMA_CRS_RF_DELAY_SHIFT 16		/**< Read Frame Delay field shift */
#define XVDMA_CRS_R_STRIDE   0x00000FFF /**< Read DMA Stride */

/**
 * Reset Register bit definition
 */
#define XVDMA_RESET_RESET    0x0000000A /**< Software Reset */

/**
 * Global Interrupt Enable Register bit definition
 */
#define XVDMA_GIER_GIE_MASK	  0x80000000 /**< Global interrupt enable */

/**
 * Interrupt Status/Enable Register bit definition
 */
#define XVDMA_IXR_W_FIFO_ERR  0x00040000 /**< Write FIFO error Interrupt */
#define XVDMA_IXR_W_CFIFO_ERR 0x00020000 /**< Write Command FIFO error
                                           *  Interrupt */
#define XVDMA_IXR_W_FRAME_CNT 0x00010000 /**< Write Frame Count Interrupt */
#define XVDMA_IXR_W_DELAY_CNT 0x00008000 /**< Write Delay Count Interrupt */
#define XVDMA_IXR_W_REPEAT    0x00004000 /**< Write Frame Repeat Interrupt */
#define XVDMA_IXR_W_SKIP      0x00002000 /**< Write Frame Skip Interrupt */
#define XVDMA_IXR_W_DMA_DONE  0x00001000 /**< Write DMA Done Interrupt */
#define XVDMA_IXR_R_FIFO_ERR  0x00000400 /**< Read FIFO error Interrupt */
#define XVDMA_IXR_R_CFIFO_ERR 0x00000200 /**< Read Command FIFO error Interrupt
                                */
#define XVDMA_IXR_R_FRAME_CNT 0x00000100 /**< Read Frame Count Interrupt */
#define XVDMA_IXR_R_DELAY_CNT 0x00000080 /**< Read Delay Count Interrupt */
#define XVDMA_IXR_R_REPEAT    0x00000040 /**< Read Frame Repeat Interrupt */
#define XVDMA_IXR_R_SKIP      0x00000020 /**< Read Frame Skip Interrupt */
#define XVDMA_IXR_R_DMA_DONE  0x00000010 /**< Read DMA Done Interrupt */
#define XVDMA_IXR_ADDR_ERR    0x00000002 /**< Address Error Interrupt */
#define XVDMA_IXR_WBUSY_ERR   0x00000001 /**< Write Busy Error Interrupt */

#define XVDMA_IXR_W_ALLINTR   (XVDMA_IXR_W_FRAME_CNT | XVDMA_IXR_W_DELAY_CNT \
                               | XVDMA_IXR_W_REPEAT | XVDMA_IXR_W_SKIP \
                               | XVDMA_IXR_W_DMA_DONE) /**< Mask for all Write
                                                         *  interrupts */
#define XVDMA_IXR_R_ALLINTR   (XVDMA_IXR_R_FRAME_CNT | XVDMA_IXR_R_DELAY_CNT \
                               | XVDMA_IXR_R_REPEAT | XVDMA_IXR_R_SKIP \
                               | XVDMA_IXR_R_DMA_DONE) /**< Mask for all Read
                                                         *  interrupts */
#define XVDMA_IXR_ERR_ALLINTR (XVDMA_IXR_ADDR_ERR | XVDMA_IXR_WBUSY_ERR \
                   | XVDMA_IXR_W_FIFO_ERR | XVDMA_IXR_W_CFIFO_ERR \
                   | XVDMA_IXR_R_FIFO_ERR | XVDMA_IXR_R_CFIFO_ERR) /**< Mask
                                                                     *  for all
                                                                     *  error
                                                                     *  intr */
#define XVDMA_IXR_ALLINTR     (XVDMA_IXR_W_ALLINTR | XVDMA_IXR_R_ALLINTR \
                               | XVDMA_IXR_ERR_ALLINTR) /**< Mask for all
                                                          *  interrupts */

/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/

#define XVDma_In32  XIo_In32
#define XVDma_Out32 XIo_Out32

/*****************************************************************************/
/**
*
* Read the given register.
*
* @param    BaseAddress is the base address of the device
* @param    RegOffset is the register offset to be read
*
* @return   The 32-bit value of the register
*
* @note
* C-style signature:
*    u32 XVDma_ReadReg(u32 BaseAddress, u32 RegOffset)
*
******************************************************************************/
#define XVDma_ReadReg(BaseAddress, RegOffset)             \
    XVDma_In32((BaseAddress) + (RegOffset))

/*****************************************************************************/
/**
*
* Write the given register.
*
* @param    BaseAddress is the base address of the device
* @param    RegOffset is the register offset to be written
* @param    Data is the 32-bit value to write to the register
*
* @return   None.
*
* @note
* C-style signature:
*    void XVDma_WriteReg(u32 BaseAddress, u32 RegOffset, u32 Data)
*
******************************************************************************/
#define XVDma_WriteReg(BaseAddress, RegOffset, Data)          \
    XVDma_Out32((BaseAddress) + (RegOffset), (Data))

/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */
