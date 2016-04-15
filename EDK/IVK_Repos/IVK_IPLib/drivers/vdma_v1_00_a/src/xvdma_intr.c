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
* @file xvdma_intr.c
*
* This code contains interrupt related functions of Xilinx MVI Video DMA
* device driver. The DMA device transfers frames from source to destination.
* Please see xvdma.h for more details of the driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a xd   05/05/08 First release
* </pre>
*
******************************************************************************/

#include "xvdma.h"

/*****************************************************************************/
/**
*
* This function is the interrupt handler for the Video DMA driver.
*
* This handler reads the pending interrupt from the IER/ISR, determines the
* source of the interrupts, calls according callbacks, and finally clears the
* interrupts.
*
* The application is responsible for connecting this function to the interrupt
* system. Application beyond this driver is also responsible for providing
* callbacks to handle interrupts and installing the callbacks using
* XVDma_SetCallBack() during initialization phase. An example delivered with
* this driver demonstrates how this could be done.
*
* @param   InstancePtr is a pointer to the XVDma instance that just
*          interrupted.
* @return  None.
* @note    None.
*
******************************************************************************/
void XVDma_IntrHandler(void *InstancePtr)
{
	u32 PendingIntr;
	u32 ErrorStatus;
	XVDma *XVDmaPtr;

	XVDmaPtr = (XVDma *) InstancePtr;

	/* Validate parameters */
	XASSERT_VOID(XVDmaPtr != NULL);
	XASSERT_VOID(XVDmaPtr->IsReady == XCOMPONENT_IS_READY);

	/* Get pending interrupts */
	PendingIntr = XVDma_IntrGetPending(XVDmaPtr);

	/* Clear pending interrupt(s) */
	XVDma_IntrClear(XVDmaPtr, PendingIntr);

	/* Error interrupt is occurring or spurious interrupt */
	if ((0 == (PendingIntr & XVDMA_IXR_ALLINTR))
			|| (PendingIntr & XVDMA_IXR_ERR_ALLINTR)) {
		XVDmaPtr->ErrCallBack(XVDmaPtr->ErrRef,
			PendingIntr & XVDMA_IXR_ERR_ALLINTR);

		/* The error callback should reset the device. There is no
		 * need to handle other interrupts in this function.
		 */
		return;
	}

	/* A write frame interrupt happened */
	if ((PendingIntr & XVDMA_IXR_W_ALLINTR)) {
		XVDmaPtr->WriteFrameCallBack(XVDmaPtr->WriteFrameRef,
			PendingIntr & XVDMA_IXR_W_ALLINTR);
	}

	/* A read frame interrupt happened */
	if ((PendingIntr & XVDMA_IXR_R_ALLINTR)) {
		XVDmaPtr->ReadFrameCallBack(XVDmaPtr->ReadFrameRef,
			PendingIntr & XVDMA_IXR_R_ALLINTR);
	}
}


/*****************************************************************************/
/**
*
* This routine installs an asynchronous callback function for the given
* HandlerType:
*
* <pre>
* HandlerType              Callback Function Type
* -----------------------  ---------------------------
* XVDMA_HANDLER_WRITE      XVDma_CallBack
* XVDMA_HANDLER_READ       XVDma_CallBack
* XVDMA_HANDLER_ERROR      XVDma_ErrorCallBack
*
* HandlerType              Invoked by this driver when:
* -----------------------  --------------------------------------------------
* XVDMA_HANDLER_WRITE      A write frame operation is done.
* XVDMA_HANDLER_READ       A read frame operation is done.
* XVDMA_HANDLER_ERROR      An error just happened.
*
* </pre>
*
* @param	InstancePtr is a pointer to the XVDma instance to be worked on.
* @param	HandlerType specifies which callback is to be attached.
* @param	CallbackFunc is the address of the callback function.
* @param	CallbackRef is a user data item that will be passed to the
*           callback function when it is invoked.
*
* @return
*		- XST_SUCCESS when handler is installed.
*		- XST_INVALID_PARAM when HandlerType is invalid.
*
* @note
* Invoking this function for a handler that already has been installed replaces
* it with the new handler.
*
******************************************************************************/
int XVDma_SetCallBack(XVDma * InstancePtr, u32 HandlerType,
                        void *CallBackFunc, void *CallBackRef)
{
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	switch (HandlerType) {
	case XVDMA_HANDLER_WRITE:
		InstancePtr->WriteFrameCallBack = (XVDma_CallBack) CallBackFunc;
		InstancePtr->WriteFrameRef = CallBackRef;
		break;

	case XVDMA_HANDLER_READ:
		InstancePtr->ReadFrameCallBack = (XVDma_CallBack) CallBackFunc;
		InstancePtr->ReadFrameRef = CallBackRef;
		break;

	case XVDMA_HANDLER_ERROR:
		InstancePtr->ErrCallBack = (XVDma_ErrorCallBack) CallBackFunc;
		InstancePtr->ErrRef = CallBackRef;
		break;

	default:
		return (XST_INVALID_PARAM);

	}
	return (XST_SUCCESS);
}
