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
*       FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DIVDMAAIMS ANY
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
* @file xvdma.c
*
* This is main code of Xilinx MVI Video DMA device driver. The DMA device
* transfers video frames from the source to destination buffer. Please see
* xvdma.h for more details of the driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a xd   05/06/09 First release
* </pre>
*
******************************************************************************/


/***************************** Include Files *********************************/

#include "xvdma.h"
#include "xenv.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

static void StubCallBack(void *CallBackRef);
static void StubErrCallBack(void *CallBackRef, u32 ErrorMask);


/************************** Function Definition ******************************/

/*****************************************************************************/
/**
 * This function initializes a VDMA device.  This function must be called
 * prior to using a VDMA device. Initialization of a VDMA includes setting
 * up the instance data, and ensuring the hardware is in a quiescent state.
 *
 * @param  InstancePtr is a pointer to the VDMA device instance to be worked
 *         on.
 * @param  CfgPtr points to the configuration structure associated with the
 *         VDMA device.
 * @param  EffectiveAddr is the base address of the VDMA device. If address
 *         translation is being used, then this parameter must
 *         reflect the virtual base address. Otherwise, the physical address
 *         should be used.
 * @return XST_SUCCESS
 *
 *****************************************************************************/
int XVDma_CfgInitialize(XVDma *InstancePtr, XVDma_Config *CfgPtr,
              u32 EffectiveAddr)
{
    /* Verify arguments */
    XASSERT_NONVOID(InstancePtr != NULL);
    XASSERT_NONVOID(CfgPtr != NULL);
    XASSERT_NONVOID(CfgPtr->MaxFrameStoreNum <= XVDMA_MAX_FRAMESTORE);

    /* Setup the instance */
    memset((void *)InstancePtr, 0, sizeof(XVDma));
    memcpy((void *)&(InstancePtr->Config), (const void *)CfgPtr,
               sizeof(XVDma_Config));
    InstancePtr->Config.BaseAddress = EffectiveAddr;

    /* Set all handlers to stub values, let user configure this data later */
    InstancePtr->WriteFrameCallBack = (XVDma_CallBack) StubCallBack;
    InstancePtr->ReadFrameCallBack = (XVDma_CallBack) StubCallBack;
    InstancePtr->ErrCallBack = (XVDma_ErrorCallBack) StubErrCallBack;

    /* Reset the hardware and set the flag to indicate the driver is ready */
    XVDma_Reset(InstancePtr);
    InstancePtr->IsReady = XCOMPONENT_IS_READY;

    return XST_SUCCESS;
}

/*****************************************************************************/
/**
 * This function launches a DMA Write Frame operation.
 *
 * @param  InstancePtr is a pointer to the DMA device instance to be worked on.
 * @param  DmaSetupPtr points to the configuration structure associated with
 *         the DMA Write Frame operation.
 * @return XST_SUCCESS
 *
 *****************************************************************************/
int XVDma_StartWriteFrame(XVDma *InstancePtr, XVDma_DmaSetup *DmaSetupPtr)
{
    /* Validate parameters */
    XASSERT_NONVOID(InstancePtr != NULL);
    XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
    XASSERT_NONVOID(InstancePtr->Config.MaxFrameStoreNum <=
                        XVDMA_MAX_FRAMESTORE);
    XASSERT_NONVOID(DmaSetupPtr != NULL);

    /* Set up configuration for the Write Frame operation */
    XVDma_DmaConfig(InstancePtr, XVDMA_WRITE, DmaSetupPtr);

    /* Set up frame buffer adderesses */
    XVDma_DmaSetBufferAddr(InstancePtr, XVDMA_WRITE,
                               DmaSetupPtr->FrameStoreStartAddr);

    /* Kick off the Write Frame operation */
    XVDma_DmaStart(InstancePtr, XVDMA_WRITE);

    return XST_SUCCESS;
}

/*****************************************************************************/
/**
 * This function launches a DMA Read Frame operation.
 *
 * @param  InstancePtr is a pointer to the DMA device instance to be worked on.
 * @param  DmaSetupPtr points to the configuration structure associated with
 *         the DMA Read Frame operation.
 * @return XST_SUCCESS
 *
 *****************************************************************************/
int XVDma_StartReadFrame(XVDma *InstancePtr, XVDma_DmaSetup *DmaSetupPtr)
{
    /* Validate parameters */
    XASSERT_NONVOID(InstancePtr != NULL);
    XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
    XASSERT_NONVOID(InstancePtr->Config.MaxFrameStoreNum <=
                        XVDMA_MAX_FRAMESTORE);
    XASSERT_NONVOID(DmaSetupPtr != NULL);

    /* Set up configuration for the Read Frame operation */
    XVDma_DmaConfig(InstancePtr, XVDMA_READ, DmaSetupPtr);

    /* Set up frame buffer adderesses */
    XVDma_DmaSetBufferAddr(InstancePtr, XVDMA_READ,
                               DmaSetupPtr->FrameStoreStartAddr);

    /* Kick off the Read Frame operation */
    XVDma_DmaStart(InstancePtr, XVDMA_READ);

    return XST_SUCCESS;
}

/*****************************************************************************/
/**
 * This function configures the setting to be used by a DMA operation.
 *
 * @param  InstancePtr is a pointer to the DMA device instance to be worked on.
 * @param  Direction indicates the direction of the DMA operation. Use
 *         XVDMA_WRITE for write DMA and XVDMA_READ for read DMA.
 * @param  DmaSetupPtr points to the configuration structure associated with
 *         the DMA operation.
 * @return None.
 *
 *****************************************************************************/
void XVDma_DmaConfig(XVDma *InstancePtr, u16 Direction,
						XVDma_DmaSetup *DmaSetupPtr)
{
    u32 FrameSize;
    u32 ControlRegValue;
    u32 CrsValue;
    u32 CwsValue;

    /* Validate parameters */
    XASSERT_VOID(InstancePtr != NULL);
    XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
    XASSERT_VOID(InstancePtr->Config.MaxFrameStoreNum <= XVDMA_MAX_FRAMESTORE);
    XASSERT_VOID((Direction == XVDMA_WRITE) || (Direction == XVDMA_READ));
    XASSERT_VOID(DmaSetupPtr != NULL);

	/* Read the current VDMA control register value */
	ControlRegValue = XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL);

	if (Direction == XVDMA_WRITE) {

		/* Configure the DMA core with the size and stride info */
		FrameSize = (DmaSetupPtr->VertSizeInput << XVDMA_CWFS_V_SHIFT)
						& XVDMA_CWFS_V_SIZE;
		FrameSize |= DmaSetupPtr->HoriSizeInput & XVDMA_CWFS_H_SIZE;
		XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CWFS, FrameSize);

		/* Set up the Control Write Stride register w/ stride & frame delay */
		CwsValue = DmaSetupPtr->Stride & XVDMA_CWS_W_STRIDE;
		CwsValue |= (DmaSetupPtr->FrameDelay << XVDMA_CWS_WF_DELAY_SHIFT) &
						XVDMA_CWS_WF_DELAY;
		XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CWS, CwsValue);

		/* Set up Write Pointer Number */
		ControlRegValue &= ~XVDMA_CTL_WP_NUM;
		ControlRegValue |= (DmaSetupPtr->PointNum << XVDMA_CTL_WP_NUM_SHIFT) &
								XVDMA_CTL_WP_NUM;

		/* Set up Circular buffer flag and Fixed Frame Store Address Index */
		ControlRegValue &= ~XVDMA_CTL_WFRAME_PTR;
		if (DmaSetupPtr->EnableCircularBuf) {
			ControlRegValue |= XVDMA_CTL_CIR_BUF_EN;
		} else {
			ControlRegValue &= ~XVDMA_CTL_CIR_BUF_EN;
			ControlRegValue |= (DmaSetupPtr->FixedFrameStoreAddr <<
								   XVDMA_CTL_WFRAME_SHIFT) &
								   XVDMA_CTL_WFRAME_PTR;
		}
	}
	else {

		/* Configure the DMA core with the size and stride info */
		FrameSize = (DmaSetupPtr->VertSizeInput << XVDMA_CRFS_V_SHIFT)
						& XVDMA_CRFS_V_SIZE;
		FrameSize |= DmaSetupPtr->HoriSizeInput & XVDMA_CRFS_H_SIZE;
		XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CRFS, FrameSize);

		/* Set up the Control Read Stride register w/ stride and frame delay */
		CrsValue = DmaSetupPtr->Stride & XVDMA_CRS_R_STRIDE;
		CrsValue |= (DmaSetupPtr->FrameDelay << XVDMA_CRS_RF_DELAY_SHIFT) &
						XVDMA_CRS_RF_DELAY;
		XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CRS, CrsValue);

		/* Set up Read Pointer Number */
		ControlRegValue &= ~XVDMA_CTL_RP_NUM;
		ControlRegValue |= (DmaSetupPtr->PointNum << XVDMA_CTL_RP_NUM_SHIFT) &
								XVDMA_CTL_RP_NUM;

		/* Set up Circular buffer flag and Fixed Frame Store Address Index */
		ControlRegValue &= ~XVDMA_CTL_RFRAME_PTR;
		if (DmaSetupPtr->EnableCircularBuf) {
			ControlRegValue |= XVDMA_CTL_CIR_BUF_EN;
		} else {
			ControlRegValue &= ~XVDMA_CTL_CIR_BUF_EN;
			ControlRegValue |= (DmaSetupPtr->FixedFrameStoreAddr <<
								   XVDMA_CTL_RFRAME_SHIFT) &
								   XVDMA_CTL_RFRAME_PTR;
		}
	}

	/* Set up Frame Counter enable flag */
	if (DmaSetupPtr->EnableFrameCounter) {
		ControlRegValue |= XVDMA_CTL_FRMCNT_EN;
	} else {
		ControlRegValue &= ~XVDMA_CTL_FRMCNT_EN;
	}

	/* Set up Sync Enable flag */
	if (DmaSetupPtr->EnableSync) {
		ControlRegValue |= XVDMA_CTL_SYNC_EN;
	} else {
		ControlRegValue &= ~XVDMA_CTL_SYNC_EN;
	}

    /* Stop current Write/Read operation, if running */
    ControlRegValue &= ~(XVDMA_CTL_RDMA_EN | XVDMA_CTL_WDMA_EN);

	/* Write the control value back */
	XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL, ControlRegValue);

	return;
}

/*****************************************************************************/
/**
 * This function sets up the buffer addresses to be used by a DMA operation.
 *
 * @param  InstancePtr is a pointer to the DMA device instance to be worked on.
 * @param  Direction indicates the direction of the DMA operation. Use
 *         XVDMA_WRITE for write DMA and XVDMA_READ for read DMA.
 * @param  BufferAddrSet points to the first of the buffer address set
 * @return None.
 *
 *****************************************************************************/
void XVDma_DmaSetBufferAddr(XVDma *InstancePtr, u16 Direction,
                            u32 *BufferAddrSet)
{
    u16 MaxFrameStoreNum;
    u32 CxsaOffset;
    int i;

    /* Validate parameters */
    XASSERT_VOID(InstancePtr != NULL);
    XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
    XASSERT_VOID(InstancePtr->Config.MaxFrameStoreNum <= XVDMA_MAX_FRAMESTORE);
    XASSERT_VOID((Direction == XVDMA_WRITE) || (Direction == XVDMA_READ));
    XASSERT_VOID(BufferAddrSet != NULL);

	if (Direction == XVDMA_WRITE) {
		CxsaOffset = XVDMA_CWSA00;
	}
	else {
		CxsaOffset = XVDMA_CRSA00;
	}

	/* Set up the buffer addresses */
	MaxFrameStoreNum = InstancePtr->Config.MaxFrameStoreNum;
	for (i = 0; i<MaxFrameStoreNum; i++) {
		XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), CxsaOffset,
						BufferAddrSet[i]);
		CxsaOffset += 4;
	}
}

/*****************************************************************************/
/**
 * This function kicks off a DMA operation.
 *
 * @param  InstancePtr is a pointer to the DMA device instance to be worked on.
 * @param  Direction indicates the direction of the DMA operation. Use
 *         XVDMA_WRITE for write DMA and XVDMA_READ for read DMA.
 * @return None.
 *
 *****************************************************************************/
void XVDma_DmaStart(XVDma *InstancePtr, u16 Direction)
{
    u32 ControlRegValue;

    /* Validate parameters */
    XASSERT_VOID(InstancePtr != NULL);
    XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
    XASSERT_VOID(InstancePtr->Config.MaxFrameStoreNum <= XVDMA_MAX_FRAMESTORE);
    XASSERT_VOID((Direction == XVDMA_WRITE) || (Direction == XVDMA_READ));

    /* Read the current VDMA control register value */
	ControlRegValue = XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL);

	if (Direction == XVDMA_WRITE) {

		/* Kick off the Write Frame operation by clearing and setting the Write
		 * DMA Enable bit
		 */
		XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL,
		                   ControlRegValue & (~XVDMA_CTL_WDMA_EN));
		XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL,
		                   ControlRegValue | XVDMA_CTL_WDMA_EN);
	}
	else {

	    /* Kick off the Read Frame operation by clearing and setting the Read
	     * DMA Enable bit
	     */
	    XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL,
	                       ControlRegValue & (~XVDMA_CTL_RDMA_EN));
	    XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CTL,
	                       ControlRegValue | XVDMA_CTL_RDMA_EN);
	}
}

/*****************************************************************************/
/**
 * This function sets control counter register for
 * 1. interrupt coalescing, and/or
 * 2. DMA transfer frame control when bit Frame count Enable in VDMA control
 *    register is set.
 *
 * @param  InstancePtr is a pointer to the VDMA device instance to be worked
 *         on.
 * @param  FrameCounterCfgPtr points to the frame counter configuration
 *         structure.
 * @return XST_SUCCESS if coalescing is set up properly. XST_INVALID_PARAM if
 *         the parameter value are invalid.
 *
 *****************************************************************************/
int XVDma_SetFrameCounter(XVDma *InstancePtr,
                          XVDmaFrameCounter *FrameCounterCfgPtr)
{
    u32 RegValue;
    XVDmaFrameCounter *CfgPtr = FrameCounterCfgPtr;

    /* Validate parameters */
    XASSERT_NONVOID(InstancePtr != NULL);
    XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
    XASSERT_NONVOID(FrameCounterCfgPtr != NULL);
    if ((FrameCounterCfgPtr->ReadFrameCount == 0) &&
            (FrameCounterCfgPtr->ReadDelayTimerCount == 0))
    {
        return XST_INVALID_PARAM;
    }
    if ((FrameCounterCfgPtr->WriteFrameCount == 0) &&
            (FrameCounterCfgPtr->WriteDelayTimerCount == 0))
    {
        return XST_INVALID_PARAM;
    }

    /* Calculate the value to write to the Control Counter register */
    RegValue = ((u32)(CfgPtr->WriteDelayTimerCount)) & XVDMA_CC_W_DELAYTIMER;
    RegValue |= (((u32)(CfgPtr->WriteFrameCount)) << XVDMA_CC_W_FRAMECNT_SHIFT)
                & XVDMA_CC_W_FRAMECNT;
    RegValue |= (((u32)(CfgPtr->ReadDelayTimerCount)) <<
                    XVDMA_CC_R_DELAYTIMER_SHIFT) & XVDMA_CC_R_DELAYTIMER;
    RegValue |= (((u32)(CfgPtr->ReadFrameCount)) << XVDMA_CC_R_FRAMECNT_SHIFT)
                & XVDMA_CC_R_FRAMECNT;

    /* Set up the coalescing */
    XVDma_WriteReg(XVDma_BaseAddr(InstancePtr), XVDMA_CC, RegValue);

    return XST_SUCCESS;
}

/*****************************************************************************/
/**
 * This function gets the current control counter setting.
 *
 * @param  InstancePtr is a pointer to the VDMA device instance to be worked
 *         on.
 * @param  FrameCounterCfgPtr points to the frame counter configuration
 *         structure to hold the current setting after this function returns.
 * @return None.
 *
 *****************************************************************************/
void XVDma_GetFrameCounter(XVDma *InstancePtr,
                           XVDmaFrameCounter *FrameCounterCfgPtr)
{
    u32 RegValue;
    XVDmaFrameCounter *CfgPtr = FrameCounterCfgPtr;

    /* Validate parameters */
    XASSERT_VOID(InstancePtr != NULL);
    XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
    XASSERT_VOID(FrameCounterCfgPtr != NULL);

    /* Get the coalescing setting */
    RegValue = XVDma_ReadReg(XVDma_BaseAddr(InstancePtr), XVDMA_CC);

    /* Parse the setting and populate the coalescing setting structure */
    CfgPtr->WriteDelayTimerCount = (u8)(RegValue & XVDMA_CC_W_DELAYTIMER);
    CfgPtr->WriteFrameCount = (u8)((RegValue & XVDMA_CC_W_FRAMECNT)
                                >> XVDMA_CC_W_FRAMECNT_SHIFT);
    CfgPtr->ReadDelayTimerCount = (u8)((RegValue & XVDMA_CC_R_DELAYTIMER)
                                >> XVDMA_CC_R_DELAYTIMER_SHIFT);
    CfgPtr->ReadFrameCount = (u8)((RegValue & XVDMA_CC_R_FRAMECNT_SHIFT)
                                >> XVDMA_CC_R_FRAMECNT_SHIFT);
    return;
}

/******************************************************************************/
/*
 * This routine is a stub for the asynchronous write/read frame callbacks. The
 * stub is here in case the upper layer forgot to set the handler(s). On
 * initialization, All handlers except error handler are set to this callback.
 * It is considered an error for this handler to be invoked.
 *
 ******************************************************************************/
static void StubCallBack(void *CallBackRef)
{
    XASSERT_VOID_ALWAYS();
}

/******************************************************************************/
/*
 * This routine is a stub for the asynchronous error interrupt callback. The
 * stub is here in case the upper layer forgot to set the handler. On
 * initialization, Error interrupt handler is set to this callback. It is
 * considered an error for this handler to be invoked.
 *
 ******************************************************************************/
static void StubErrCallBack(void *CallBackRef, u32 ErrorMask)
{
    XASSERT_VOID_ALWAYS();
}
