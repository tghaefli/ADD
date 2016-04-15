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
* @file xvdma.h
*
* This is the Xilinx MVI Video DMA device driver. The DMA device transfers
* frames from input VFBC Bus or to output VFBC Bus.
*
* The VDMA has four bus standards:
*
* 1. VFBC Bus Standard to connect to the VFBC Command FIFO, Write Data FIFO and
*    Read Data FIFO.
* 2. VDMA Bus Standard to allow Video IP to connect to either the Write Data
*    FIFO or the Read Data FIFO, or both, of the VFBC.  The use of the Command
*    FIFO is optional and is used only if the hardware needs to control DMA
*    operations.
* 3. PLB Bus Standard.
* 4. Gen-Lock Bus Standard for synchronizing the Frame Store operations between
*    two video IP blocks.  This is an asynchronous interface as the two video
*    IP blocks could be running from two separate clocks.
*
* For a full description of Video DMA features, please see the hardware spec.
*
* <b>Interrupt Service </b>
*
* The VDMA supports 3 group of interrupts:
* - Write Frame Interrupt: A write frame operation is done.
* - Read Frame Interrupt: A read frame operation is done.
* - Error Interrupt: An error just happened.
*
* The application is responsible for the interrupt system setup and installing
* the application level callbacks to handle the interrupts by calling
* XVDma_SetCallBack(). The callback that handles the Error interrupt should
* save the current setting, reset the device and recovers the setting saved.
*
* The callbacks do not need to clear any pending interrupt as this is done by
* the interrupt handler, XVDma_IntrHandler(), already.
*
* <b>Software Initialization </b>
*
* The application needs to do following steps in order for preparing the
* Video DMA to be ready to process DMA transfer requests from the application
*
* 1. Call XVDma_LookupConfig() to find the device configuration given a device
*    ID.
* 2. Call XVDma_CfgInitialize() to initialize the VDMA device and the driver
*    instance, using the device configuration found in step 1.
* 3. If interrupt handling is desired, call XVDma_SetFrameCounter() to set up
*    interrupt coalescing.
* 4. If interrupt handling is desired, call XVDma_SetCallBack() one or more
*    times to install the callbacks.
* 5. If interrupt handling is desired, call XVDma_IntrEnable() to enable
*    the interrupt type that the callbacks installed in step 4 handle.
* 6. If interrupt handling is desired, call XVDma_IntrEnableGlobal() to enable
*    the device global interrupt.
*
*
* <b>How to start DMA transactions </b>
*
* There are two ways to start DMA transactions:
*
* 1. Invoke XVDma_StartWriteFrame() or XVDma_StartReadFrame() to start DMA
*    operation, depending on the purpose of the VDMA (Write or Read)
*
* 2. Or, call the phased functions below.
*    - Call XVDma_DmaConfig() to set up DMA operation configuration
*    - Call XVDma_DmaSetBufferAddr() to set up the DMA buffers
*    - Call XVDma_DmaStart() to kick off the DMA operation
*
* Note a Read VDMA could work with multiple Write VDMA instances and visa
* versa. To choose which Write VDMA instance to work with, set PointNum
* properly in structure XVDma_DmaSetup instance that is passed into
* XVDma_StartReadFrame().
*
* <b> Examples </b>
*
* One example is provided with this driver to demonstrate the driver usage.
*
* <b>Cache Coherency</b>
*
* This driver does not handle any cache coherency. The application is
* responsible for handling cache coherency, if the cache is enabled.
*
* <b>Alignment</b>
*
* The VDMA supports any buffer alignment when the Horizontal Cropping is
* enabled by using XVDma_HoriCropEnable(). If the Horizontal Cropping is
* disabled by calling XVDma_HoriCropDisable(), VDMA ONLY supports 128-bytes
* aligned buffers.
*
* <b>Limitations</b>
*
* - The current VDMA does NOT support full-duplex DMA operation.
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

#ifndef XVDMA_H     /* prevent circular inclusions */
#define XVDMA_H     /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xvdma_hw.h"
#include "xvdma_i.h"
#include "xstatus.h"

/************************** Constant Definitions *****************************/

/**
 * Interrupt type for setting up callback
 */
#define XVDMA_HANDLER_WRITE     1        /**< Write Frame Interrupt Type */
#define XVDMA_HANDLER_READ      2        /**< Read Frame Interrupt Type */
#define XVDMA_HANDLER_ERROR     3        /**< Error Interrupt Type */

/**
 * Maximum number of the frame store
 */
#define XVDMA_MAX_FRAMESTORE    16       /**< Maximum # of the frame store */

/**
 * VDMA data transfer direction
 */
#define XVDMA_WRITE		        1        /**< DMA transfer into memory */
#define XVDMA_READ		        2        /**< DMA transfer from memory */

/**************************** Type Definitions *******************************/

/**
 * This typedef contains configuration information for a VDMA device.
 * Each VDMA device should have a configuration structure associated
 */
typedef struct {
    u16 DeviceId;         /**< DeviceId is the unique ID  of the device */
    u32 BaseAddress;      /**< BaseAddress is the physical base address of the
                            *  device's registers */
    u16 MaxFrameStoreNum; /**< The maximum number of Frame Stores */
} XVDma_Config;

/**
 * Callback type for Write/Read Frame interrupts
 *
 * @param   CallBackRef is a callback reference passed in by the upper layer
 *          when installing the callback functions, and passed back to the
 *          upper layer when the callback is invoked.
 * @param   InterruptTypes indicates the detailed type(s) of the interrupt.
 *          Its value equals 'OR'ing one or more XVDMA_IXR_* values defined
 *          in xvdma_hw.h
 */
typedef void (*XVDma_CallBack) (void *CallBackRef, u32 InterruptTypes);

/**
 * Callback type for Error interrupt.
 *
 * @param   CallBackRef is a callback reference passed in by the upper layer
 *          when setting the callback function, and passed back to the
 *          upper layer when the callback is invoked.
 * @param   ErrorMask is a bit mask indicating the cause of the error. Its
 *          value equals 'OR'ing one or more XVDMA_IXR_* values defined in
 *          xvdma_hw.h
 */
typedef void (*XVDma_ErrorCallBack) (void *CallBackRef, u32 ErrorMask);

/**
 * The XVDma driver instance data. An instance must be allocated for each
 * DMA device in use.
 */
typedef struct {
    XVDma_Config Config;               /**< hardware configuration */
    u32 IsReady;                       /**< Device and the driver instance
                                         *  are initialized */
    XVDma_CallBack WriteFrameCallBack; /**< Call back for Write Frame
                                         *  interrupt */
    void *WriteFrameRef;               /**< To be passed to the Write Frame
                                         *  interrupt callback */

    XVDma_CallBack ReadFrameCallBack;  /**< Call back for Read Frame interrupt
                                         */
    void *ReadFrameRef;                /**< To be passed to the Read Frame
                                         *  interrupt callback */

    XVDma_ErrorCallBack ErrCallBack;   /**< Call back for Error interrupt */
    void *ErrRef;                      /**< To be passed to the Error interrupt
                                         *  callback */

} XVDma;

/**
 * The XVDma_DmaSetup structure contains all configuration information to start a
 * Write Frame or a Read Frame operation.
 */
typedef struct {
    u32 VertSizeInput;  	/**< Vertical size input */
    u32 HoriSizeInput;  	/**< Horizontal size input */
    u32 Stride;     		/**< Stride */
    u32 FrameDelay;			/**< Frame Delay */

    int EnableCircularBuf;  /**< Should we use Circular buffer? If set, the
                                 next buffer in FrameStoreStartAddr[] will be
                                 worked on after the current buffer is
                                 finished. If not, the buffer whose index is
                                 specified by FixedFrameStoreAddr the only one
                                 the VDMA will transfer to/from. */
    int EnableSync;			/**< compare current frame store address pointer to
                                 incoming frame store address pointer? */
    u32 PointNum;			/**< Source/Destination pointer to use for Gen-Lock
    							 frame pointer comparisons. Used to choose
    							 which partner VDMA instance to pair with for
    							 current VDMA. */
    int EnableFrameCounter; /**< Frame Counter Enable. If set, will transfer
                                 a number of frames specified using
                                 XVDma_SetFrameCounter(). If cleared, the DMA
                                 transfer keeps running forever. */
    u32 FrameStoreStartAddr[XVDMA_MAX_FRAMESTORE];
                            /**< Start Addresses of Frame Store Buffers. */
    u32 FixedFrameStoreAddr;/**< Fixed Frame Store Address index. Specify which
                                 buffer in FrameStoreStartAddr[] is the ONLY
                                 one to work on. This index is used only if the
                                 EnableCircularBuf flag is FALSE. When
                                 EnableCircularBuf has value TRUE, all
                                 buffers in FrameStoreStartAddr[] will be
                                 worked on one by one, 1st one first, 2nd one
                                 second, and etc. */
} XVDma_DmaSetup;

/**
 * The XVDmaFrameCounter structure contains all frame counters and delay timer
 * counters for interrupt coalescing and the number of frames to read/write
 * when EnableFrameCounter in XVDma_DmaSetup, which handles bit "Frame count
 * Enable" in VDMA control register, is set.
 */
typedef struct {
    u8 ReadFrameCount;      /**< Send interrupt after this number of frames
                              *  have been read */
    u8 ReadDelayTimerCount; /**< Send interrupt after this number of delay
                              *  counter ticks */
    u8 WriteFrameCount;     /**< Send interrupt after this number of frames
                              *  have been written */
    u8 WriteDelayTimerCount;/**< Send interrupt after this number of delay
                              *  counter ticks */
} XVDmaFrameCounter;

/***************** Macros (Inline Functions) Definitions *********************/

/*****************************************************************************/
/**
*
* This macro resets a VDMA device.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return None
*
* @note
* C-style signature:
*    void XVDma_Reset(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_Reset(InstancePtr) \
    { \
        XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_RESET, \
                           XVDMA_RESET_RESET); \
    }

/*****************************************************************************/
/**
*
* This macro checks if a VDMA device is busy doing DMA operation
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return TRUE if the VDMA is busy doing DMA operation; FALSE otherwise.
*
* @note
* C-style signature:
*    boolean XVDma_IsBusy(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_IsBusy(InstancePtr) \
        ((XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_SFS) & \
            XVDMA_SFS_VDMA_BUSY) ? TRUE : FALSE)

/*****************************************************************************/
/**
*
* This macro disables the command interface of a VDMA. All commands from the
* Command Interface will be ignored
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return None
*
* @note
* C-style signature:
*    void XVDma_CmdInerfaceDisable(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_CmdInerfaceDisable(InstancePtr) \
        (XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL, \
            (XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL) | \
                XVDMA_CTL_HW_LOCKOUT)))

/*****************************************************************************/
/**
*
* This macro enables the command interface of a VDMA. The user IP of the VDMA
* can issue commands to the VDMA through the command interface.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return None
*
* @note
* C-style signature:
*    void XVDma_CmdInerfaceEnable(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_CmdInerfaceEnable(InstancePtr) \
        (XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL, \
            (XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL) & \
                ~XVDMA_CTL_HW_LOCKOUT)))

/*****************************************************************************/
/**
*
* This macro disables the full duplex mode of a VDMA device.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return None
*
* @note
*
* This macro does not work now and is a place holder for future VDMA device
* that will support the full duplex mode.
*
* C-style signature:
*    void XVDma_FullDuplexDisable(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_FullDuplexDisable(InstancePtr) \
        (XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL, \
            (XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL) & \
                ~XVDMA_CTL_DUPLEX)))

/*****************************************************************************/
/**
*
* This macro enables the full duplex mode of a VDMA device. This enables
* the VDMA to use any buffer alignment.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return None
*
* @note
*
* This macro does not work now and is a place holder for future VDMA device
* that will support the full duplex mode.
*
* C-style signature:
*    void XVDma_FullDuplexEnable(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_FullDuplexEnable(InstancePtr) \
        (XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL, \
            (XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL) | \
                XVDMA_CTL_DUPLEX)))

/*****************************************************************************/
/**
*
* This macro disables the horizontal cropping of a VDMA device. After this
* macro returns, the VDMA only supports 128-byte aligned buffers.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return None
*
* @note
*
* C-style signature:
*    void XVDma_HoriCropDisable(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_HoriCropDisable(InstancePtr) \
        (XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL, \
            (XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL) & \
                ~XVDMA_CTL_H_CROP_EN)))

/*****************************************************************************/
/**
*
* This macro enables the horizontal cropping of a VDMA device.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return None
*
* @note
*
* C-style signature:
*    void XVDma_HoriCropEnable(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_HoriCropEnable(InstancePtr) \
        (XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL, \
            (XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL) | \
                XVDMA_CTL_H_CROP_EN)))

/*****************************************************************************/
/**
*
* This macro returns the current Frame Store status of a VDMA device.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return The current frame store status of the VDMA device. Use XVDMA_SFS_*
*         defined in xvdma_hw.h to interpret this value.
*
* @note
*
* C-style signature:
*    u32 XVDma_CurrFrameStore(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_CurrFrameStore(InstancePtr) \
        XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_SFS)

/*****************************************************************************/
/**
*
* This macro returns the version of a VDMA device.
*
* @param  InstancePtr is a pointer to the DMA device instance to be worked on.
*
* @return The version of the VDMA device. Use XVDMA_SV_* defined in xvdma_hw.h
*         to interpret this value.
*
* @note
*
* C-style signature:
*    u32 XVDma_GetVersion(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_GetVersion(InstancePtr) \
        XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_SV)

/*****************************************************************************/
/**
*
* This macro enables the global interrupt on a VDMA device.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return None.
*
* @note
* C-style signature:
*    void XVDma_IntrEnableGlobal(XVDma *InstancePtr);
*
******************************************************************************/
#define XVDma_IntrEnableGlobal(InstancePtr) \
        XVDma_WriteReg((InstancePtr)->Config.BaseAddress, XVDMA_GIER, \
                          XVDMA_GIER_GIE_MASK)

/*****************************************************************************/
/**
*
* This macro disables the global interrupt on a VDMA device.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return None.
*
* @note
* C-style signature:
*    void XVDma_IntrDisableGlobal(XVDma *InstancePtr);
*
******************************************************************************/
#define XVDma_IntrDisableGlobal(InstancePtr) \
        XVDma_WriteReg((InstancePtr)->Config.BaseAddress, XVDMA_GIER, 0)

/*****************************************************************************/
/**
*
* This macro enables interrupts of a VDMA device.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @param  IntrType is the type of the interrupts to enable. Use OR'ing of
*         XVDMA_IXR_* constants defined in xvdma_hw.h to create this parameter
*         value.
*
* @return None
*
* @note
*
* The existing enabled interrupt(s) will remain enabled.
*
* C-style signature:
*    void XVDma_IntrEnable(XVDma *InstancePtr, u32 IntrType)
*
******************************************************************************/
#define XVDma_IntrEnable(InstancePtr, IntrType) \
        XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_IER, \
            XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_IER) | \
            ((IntrType) & XVDMA_IXR_ALLINTR))

/*****************************************************************************/
/**
*
* This macro disables interrupts of a VDMA device.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @param  IntrType is the type of the interrupts to disable. Use OR'ing of
*         XVDMA_IXR_* constants defined in xvdma_hw.h to create this parameter
*         value.
*
* @return None
*
* @note
*
* Any other interrupt not covered by parameter IntrType, if enabled before
* this macro is called, will remain enabled.
*
* C-style signature:
*    void XVDma_IntrDisable(XVDma *InstancePtr, u32 IntrType)
*
******************************************************************************/
#define XVDma_IntrDisable(InstancePtr, IntrType) \
        XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_IER, \
            XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_IER) & \
            (~(IntrType)) & XVDMA_IXR_ALLINTR)

/*****************************************************************************/
/**
*
* This macro returns the pending interrupts of a VDMA device.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @return The pending interrupts of the VDMA. Use XVDMA_IXR_* constants
*         defined in xvdma_hw.h to interpret this value.
*
* @note
*
* C-style signature:
*    u32 XVDma_IntrGetPending(XVDma *InstancePtr)
*
******************************************************************************/
#define XVDma_IntrGetPending(InstancePtr) \
        (XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_IER) & \
         XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_ISR) & \
         XVDMA_IXR_ALLINTR)

/*****************************************************************************/
/**
*
* This macro clears/acknowledges pending interrupts of a VDMA device.
*
* @param  InstancePtr is a pointer to the VDMA device instance to be worked on.
*
* @param  IntrType is the pending interrupts to clear/acknowledge. Use OR'ing
*         of XVDMA_IXR_* constants defined in xvdma_hw.h to create this
*         parameter value.
*
* @return None
*
* @note
*
* C-style signature:
*    void XVDma_IntrClear(XVDma *InstancePtr, u32 IntrType)
*
******************************************************************************/
#define XVDma_IntrClear(InstancePtr, IntrType) \
        XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_ISR, \
            (IntrType) & XVDma_IntrGetPending(InstancePtr))

/************************** Function Prototypes ******************************/

/*
 * Initialization and control functions in xvdma.c
 */

/* Initialization */
int XVDma_CfgInitialize(XVDma *InstancePtr, XVDma_Config *CfgPtr,
              u32 EffectiveAddr);

int XVDma_StartWriteFrame(XVDma *InstancePtr, XVDma_DmaSetup *FramePtr);
int XVDma_StartReadFrame(XVDma *InstancePtr, XVDma_DmaSetup *FramePtr);

void XVDma_DmaConfig(XVDma *InstancePtr, u16 Direction,
                     XVDma_DmaSetup *DmaConfigPtr);
void XVDma_DmaSetBufferAddr(XVDma *InstancePtr, u16 Direction,
                            u32 *BufferAddrSet);
void XVDma_DmaStart(XVDma *InstancePtr, u16 Direction);

int XVDma_SetFrameCounter(XVDma *InstancePtr,
                          XVDmaFrameCounter *FrameCounterCfgPtr);
void XVDma_GetFrameCounter(XVDma *InstancePtr,
                           XVDmaFrameCounter *FrameCounterCfgPtr);

/*
 * Initialization functions in xvdma_sinit.c
 */
XVDma_Config *XVDma_LookupConfig(u16 DeviceId);

/*
 * Interrupt related functions in xvdma_intr.c
 */
void XVDma_IntrHandler(void * InstancePtr);
int XVDma_SetCallBack(XVDma * InstancePtr, u32 IntrType, void *CallBackFunc,
                      void *CallBackRef);

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */
