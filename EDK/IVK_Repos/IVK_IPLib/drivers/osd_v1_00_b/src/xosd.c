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
* @file xosd.c
*
* This is main code of Xilinx MVI Video On-Screen-Display (OSD) device driver.
* Please see xosd.h for more details of the driver.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00a xd   08/18/08 First release
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xosd.h"
#include "xenv.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

static void PopulateLayerProperty(XOSD *InstancePtr, XOSD_Config *CfgPtr);
static void StubCallBack(void *CallBackRef);
static void StubErrCallBack(void *CallBackRef, u32 ErrorMask);

/************************** Function Definition ******************************/

/*****************************************************************************/
/**
 * This function initializes an OSD device.  This function must be called
 * prior to using an OSD device. Initialization of an OSD includes
 * setting up the instance data, and ensuring the hardware is in a quiescent
 * state.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be worked on.
 * @param  CfgPtr points to the configuration structure associated with the
 *         OSD device.
 * @param  EffectiveAddr is the base address of the device. If address
 *         translation is being used, then this parameter must reflect the
 *         virtual base address. Otherwise, the physical address should be
 *         used.
 * @return XST_SUCCESS
 *
 *****************************************************************************/
int XOSD_CfgInitialize(XOSD *InstancePtr, XOSD_Config *CfgPtr,
                            u32 EffectiveAddr)
{
	/* Verify arguments */
	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(CfgPtr != NULL);
	XASSERT_NONVOID(CfgPtr->LayerNum <= XOSD_MAX_NUM_OF_LAYERS);
	XASSERT_NONVOID(EffectiveAddr != NULL);

	/* Setup the instance */
	memset((void *)InstancePtr, 0, sizeof(XOSD));

	memcpy((void *)&(InstancePtr->Config), (const void *)CfgPtr,
			sizeof(XOSD_Config));
	InstancePtr->Config.BaseAddress = EffectiveAddr;

	/* Reset to use instruction from the OSD internal buffer */
	InstancePtr->InstructionInExternalMem = 0;

	/* Set all handlers to stub values, let user configure this data later */
	InstancePtr->VbiStartCallBack = (XOSD_CallBack) StubCallBack;
	InstancePtr->VbiEndCallBack = (XOSD_CallBack) StubCallBack;
	InstancePtr->FrameDoneCallBack = (XOSD_CallBack) StubCallBack;
	InstancePtr->ErrCallBack = (XOSD_ErrorCallBack) StubErrCallBack;

	/* Populate the layer properties into a array to help easy fetch later */
	PopulateLayerProperty(InstancePtr, CfgPtr);

	/* Reset the hardware and set the flag to indicate the driver is ready */
	XOSD_Reset(InstancePtr);
	InstancePtr->IsReady = XCOMPONENT_IS_READY;

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
 * This function chooses the type of Vertical and Horizontal Blank Input
 * Polarities.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  VerticalBlankPolarity indicates the type of vertical blank input
 *         polarity. Use any non-0 value for Active High and 0 for Active Low.
 * @param  HorizontalBlankPolarity indicates the type of horizontal blank input
 *         polarity. Use any non-0 value for Active High and 0 for Active Low.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_SetBlankPolarity(XOSD *InstancePtr, int VerticalBlankPolarity,
                           int HorizontalBlankPolarity)
{
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);


	/* Read control register and clear the current polarity setup leftover */
	RegValue = XOSD_ReadReg(InstancePtr->Config.BaseAddress, XOSD_CTL);
	RegValue &= ~(XOSD_CTL_VBP_MASK | XOSD_CTL_HBP_MASK);

	/* Set up new blank polarities */
	if (VerticalBlankPolarity) {
		RegValue |= XOSD_CTL_VBP_MASK;
	}
	if (HorizontalBlankPolarity) {
		RegValue |= XOSD_CTL_HBP_MASK;
	}
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_CTL, RegValue);

	return;
}

/*****************************************************************************/
/**
 * This function sets the screen size of the OSD Output.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  Width defines the width of the OSD output
 * @param  Height defines the height of the OSD output
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_SetScreenSize(XOSD *InstancePtr, u32 Width, u32 Height)
{
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(Width > 0);
	XASSERT_VOID(Height > 0);
	XASSERT_VOID(Width <= XOSD_SS_XSIZE_MASK);
	XASSERT_VOID(Height <= (XOSD_SS_YSIZE_MASK >> XOSD_SS_YSIZE_SHIFT));

	/* Save the dimension info in the driver instance for error handling */
	InstancePtr->ScreenWidth = Width;
	InstancePtr->ScreenHeight = Height;

	/* Update the Screen Size register */
	RegValue = Width;
	RegValue |= (Height << XOSD_SS_YSIZE_SHIFT) & XOSD_SS_YSIZE_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_SS, RegValue);

	return;
}

/*****************************************************************************/
/**
 * This function gets the screen size of the OSD Output.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  WidthPtr will point to the width of the OSD output after this
 *         function returns.
 * @param  HeightPtr will point to the height of the OSD output after this
 *         function returns.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_GetScreenSize(XOSD *InstancePtr, u32 *WidthPtr, u32 *HeightPtr)
{
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(WidthPtr != NULL);
	XASSERT_VOID(HeightPtr != NULL);

	/* Get the screen size info */
	RegValue = 	XOSD_ReadReg(InstancePtr->Config.BaseAddress, XOSD_SS);
	*WidthPtr = RegValue & XOSD_SS_XSIZE_MASK;
	*HeightPtr = (RegValue & XOSD_SS_YSIZE_MASK) >> XOSD_SS_YSIZE_SHIFT;

	return;
}

/*****************************************************************************/
/**
 * This function sets the Background color used by the OSD output.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  Red indicates the red value used in the background color.
 * @param  Blue indicates the blue value used in the background color.
 * @param  Green indicates the green value used in the background color.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_SetBackgroundColor(XOSD *InstancePtr, u8 Red, u8 Blue, u8 Green)
{
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);

	/* Update the Background Color register */
	RegValue = Green & XOSD_BC0_YG_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_BC0, RegValue);

	RegValue = Blue & XOSD_BC1_UCBB_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_BC1, RegValue);

	RegValue = Red & XOSD_BC2_VCRR_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_BC2, RegValue);

	return;
}

/*****************************************************************************/
/**
 * This function gets the Background color used by the OSD output.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  RedPtr will point to the red value used in the background color
 *         after this function returns.
 * @param  BluePtr will point to the blue value used in the background color
 *         after this function returns.
 * @param  GreenPtr will point to the green value used in the background color
 *         after this function returns.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_GetBackgroundColor(XOSD *InstancePtr, u8 *RedPtr, u8 *BluePtr,
                             u8 *GreenPtr)
{
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(RedPtr != NULL);
	XASSERT_VOID(BluePtr != NULL);
	XASSERT_VOID(GreenPtr != NULL);

	/* Get the background color */
	RegValue = XOSD_ReadReg((InstancePtr)->Config.BaseAddress, XOSD_BC0);
	*GreenPtr = (u8)(RegValue & XOSD_BC0_YG_MASK);

	RegValue = XOSD_ReadReg((InstancePtr)->Config.BaseAddress, XOSD_BC1);
	*BluePtr = (u8)(RegValue & XOSD_BC1_UCBB_MASK);

	RegValue = XOSD_ReadReg((InstancePtr)->Config.BaseAddress, XOSD_BC2);
	*RedPtr = (u8)(RegValue & XOSD_BC2_VCRR_MASK);

	return;
}

/*****************************************************************************/
/**
 * This function sets the start position and size of an OSD layer.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be worked on.
 * @param  LayerIndex indicates which layer to be worked on. Valid value range
 *         is from 0 to (the number of layers implemented in the device - 1).
 * @param  XStart indicates the Horizontal start pixel of origin of the layer.
 * @param  YStart indicates the Vertical start line of origin of the layer.
 * @param  XSize indicates the Horizontal Size of the layer.
 * @param  YSize indicates the Vertical Size of the layer.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_SetLayerDimension(XOSD *InstancePtr, u8 LayerIndex, u16 XStart,
							u16 YStart, u16 XSize, u16 YSize)
{
	u32 LayerBaseRegAddr;
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(LayerIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[LayerIndex].LayerType != \
					XOSD_LAYER_TYPE_DISABLE);
	XASSERT_VOID(XSize > 0);
	XASSERT_VOID(YSize > 0);
	XASSERT_VOID((XStart + XSize) <= InstancePtr->ScreenWidth);
	XASSERT_VOID((YStart + YSize) <= InstancePtr->ScreenHeight);

	/* Calculate the base register address of the layer to work on */
	LayerBaseRegAddr = XOSD_L0C + (LayerIndex * XOSD_LAYER_SIZE);

	/* Set the origin of the layer */
	RegValue = XStart & XOSD_LXP_XSTART_MASK;
	RegValue |= (((u32)YStart) << XOSD_LXP_YSTART_SHIFT) &
					XOSD_LXP_YSTART_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, LayerBaseRegAddr + XOSD_LXP,
					RegValue);

	/* Set the size of the layer */
	RegValue = XSize & XOSD_LXS_XSIZE_MASK;
	RegValue |= (((u32)YSize) << XOSD_LXS_YSIZE_SHIFT) & XOSD_LXS_YSIZE_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, LayerBaseRegAddr + XOSD_LXS,
					RegValue);

	return;
}

/*****************************************************************************/
/**
 * This function gets the start position and size of an OSD layer.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  LayerIndex indicates which layer to be worked on. Valid value range
 *         is from 0 to (the number of layers implemented in the device - 1).
 * @param  XStartPtr will point to the Horizontal start pixel value of origin
 *         of the layer after this function returns.
 * @param  YStartPtr will point to the Vertical start line of origin of the
 *         layer after this function returns.
 * @param  XSizePtr will point to the Horizontal Size value of the layer after
 *         this function returns.
 * @param  YSizePtr will point to the Vertical Size value of the layer after
 *         this function returns.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_GetLayerDimension(XOSD *InstancePtr, u8 LayerIndex, u16 *XStartPtr,
						u16 *YStartPtr, u16 *XSizePtr, u16 *YSizePtr)
{
	u32 LayerBaseRegAddr;
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(LayerIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[LayerIndex].LayerType != \
					XOSD_LAYER_TYPE_DISABLE);
	XASSERT_VOID(XStartPtr != NULL);
	XASSERT_VOID(YStartPtr != NULL);
	XASSERT_VOID(XSizePtr != NULL);
	XASSERT_VOID(YSizePtr != NULL);

	/* Calculate the base register address of the layer to work on */
	LayerBaseRegAddr = XOSD_L0C + (LayerIndex * XOSD_LAYER_SIZE);

	/* Get the origin of the layer */
	RegValue = XOSD_ReadReg(InstancePtr->Config.BaseAddress,
							LayerBaseRegAddr + XOSD_LXP);
	*XStartPtr = (u16) (RegValue & XOSD_LXP_XSTART_MASK);
	*YStartPtr = (u16) ((RegValue & XOSD_LXP_YSTART_MASK) >>
							XOSD_LXP_YSTART_SHIFT);

	/* Get the size of the layer */
	RegValue = XOSD_ReadReg(InstancePtr->Config.BaseAddress,
							LayerBaseRegAddr + XOSD_LXS);
	*XSizePtr = (u16) (RegValue & XOSD_LXS_XSIZE_MASK);
	*YSizePtr = (u16) ((RegValue & XOSD_LXS_YSIZE_MASK) >>
							XOSD_LXS_YSIZE_SHIFT);

	return;
}

/*****************************************************************************/
/**
 * This function sets the Alpha value and mode of an OSD layer.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  LayerIndex indicates which layer to be worked on. Valid value range
 *         is from 0 to (the number of layers implemented in the device - 1).
 * @param  GlobalAlphaEnble indicates whether to enable the global Alpha. Use
 *         any non-0 value to enable the global Alpha, and 0 to disable it.
 * @param  GlobalAlphaValue indicates the transparent level. 0 for 100%
 *         transparent, 255 for 0% transparent (100% opaque). This argument
 *         will be ignored if parameter GlobalAlphaEnble has value 0.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_SetLayerAlpha(XOSD *InstancePtr, u8 LayerIndex, u8 GlobalAlphaEnble,
						u8 GlobalAlphaValue)
{
	u32 LayerBaseRegAddr;
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(LayerIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[LayerIndex].LayerType != \
					XOSD_LAYER_TYPE_DISABLE);

	/* Calculate the base register address of the layer to work on */
	LayerBaseRegAddr = XOSD_L0C + (LayerIndex * XOSD_LAYER_SIZE);

	/* Read the current Layer Control register value */
	RegValue = 	XOSD_ReadReg(InstancePtr->Config.BaseAddress,
								LayerBaseRegAddr + XOSD_LXC);

	/* Update the Global Alpha Enable and the Global Alpha Value fields */
	if (GlobalAlphaEnble) {
		RegValue |= XOSD_LXC_GALPHAEN_MASK;
	}
	else {
		RegValue &= ~XOSD_LXC_GALPHAEN_MASK;
	}
	RegValue &= ~XOSD_LXC_ALPHA_MASK;
	RegValue |= (((u32)GlobalAlphaValue) << XOSD_LXC_ALPHA_SHIFT) &
					XOSD_LXC_ALPHA_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress,
					LayerBaseRegAddr + XOSD_LXC, RegValue);

	return;
}

/*****************************************************************************/
/**
 * This function gets the Alpha value and mode of an OSD layer.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  LayerIndex indicates which layer to be worked on. Valid value range
 *         is from 0 to (the number of layers implemented in the device - 1).
 * @param  GlobalAlphaEnblePtr will point to a flag indicating whether the
 *         global Alpha is enabled on a layer after this function returns.
 *         Flag 1 indicates that the global Alpha is enabled, 0 indicates that
 *         it is not.
 * @param  GlobalAlphaValuePtr will point to the transparent level after this
 *         function returns. 0 for 100% transparent, 255 for 0% transparent
 *         (100% opaque).
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_GetLayerAlpha(XOSD *InstancePtr, u8 LayerIndex, u8 *GlobalAlphaEnblePtr,
					u8 *GlobalAlphaValuePtr)
{
	u32 LayerBaseRegAddr;
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(LayerIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[LayerIndex].LayerType != \
					XOSD_LAYER_TYPE_DISABLE);
	XASSERT_VOID(GlobalAlphaEnblePtr != NULL);
	XASSERT_VOID(GlobalAlphaValuePtr != NULL);

	/* Calculate the base register address of the layer to work on */
	LayerBaseRegAddr = XOSD_L0C + (LayerIndex * XOSD_LAYER_SIZE);

	/* Read the current Layer Control register value */
	RegValue = 	XOSD_ReadReg(InstancePtr->Config.BaseAddress,
								LayerBaseRegAddr + XOSD_LXC);

	/* Get the info of the Global Alpha Enable and the Global Alpha Value
	 * fields
	 */
	*GlobalAlphaEnblePtr = (u8) ((RegValue & XOSD_LXC_GALPHAEN_MASK) ? 1 : 0);
	*GlobalAlphaValuePtr = (u8) ((RegValue & XOSD_LXC_ALPHA_MASK) >>
									XOSD_LXC_ALPHA_SHIFT);

	return;
}

/*****************************************************************************/
/**
 * This function sets the priority of an OSD layer.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  LayerIndex indicates which layer to be worked on. Valid value range
 *         is from 0 to (the number of layers implemented in the device - 1).
 * @param  Priority indicates the priority to be applied on the layer. Use
 *         one of XOSD_LAYER_PRIORITY_0 (the lowest priority) through
 *         XOSD_LAYER_PRIORITY_7 (the highest priority) defined in xosd_hw.h
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_SetLayerPriority(XOSD *InstancePtr, u8 LayerIndex, u8 Priority)
{
	u32 LayerBaseRegAddr;
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(LayerIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[LayerIndex].LayerType != \
					XOSD_LAYER_TYPE_DISABLE);
	XASSERT_VOID(Priority <= XOSD_LAYER_PRIORITY_7);

	/* Calculate the base register address of the layer to work on */
	LayerBaseRegAddr = XOSD_L0C + (LayerIndex * XOSD_LAYER_SIZE);

	/* Read the current Layer Control register value */
	RegValue = 	XOSD_ReadReg(InstancePtr->Config.BaseAddress,
								LayerBaseRegAddr + XOSD_LXC);

	/* Update the Priority field */
	RegValue &= ~XOSD_LXC_PRIORITY_MASK;
	RegValue |= (((u32)Priority) << XOSD_LXC_PRIORITY_SHIFT)
					& XOSD_LXC_PRIORITY_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress,
					LayerBaseRegAddr + XOSD_LXC, RegValue);

	return;
}

/*****************************************************************************/
/**
 * This function gets the priority of an OSD layer.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  LayerIndex indicates which layer to be worked on. Valid value range
 *         is from 0 to (the number of layers implemented in the device - 1).
 * @param  PriorityPtr will point to the priority used on the layer after this
 *         function returns. Use XOSD_LAYER_PRIORITY_... defined in xosd_hw.h
 *         to interpret the value.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_GetLayerPriority(XOSD *InstancePtr, u8 LayerIndex, u8 *PriorityPtr)
{
	u32 LayerBaseRegAddr;
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(LayerIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[LayerIndex].LayerType != \
					XOSD_LAYER_TYPE_DISABLE);
	XASSERT_VOID(PriorityPtr != NULL);

	/* Calculate the base register address of the layer to work on */
	LayerBaseRegAddr = XOSD_L0C + (LayerIndex * XOSD_LAYER_SIZE);

	/* Read the current Layer Control register value */
	RegValue = 	XOSD_ReadReg(InstancePtr->Config.BaseAddress,
								LayerBaseRegAddr + XOSD_LXC);

	/* Get the Priority field */
	*PriorityPtr = (u8)((RegValue & XOSD_LXC_PRIORITY_MASK) >>
						XOSD_LXC_PRIORITY_SHIFT);

	return;
}

/*****************************************************************************/
/**
 * This function enables an OSD layer.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  LayerIndex indicates which layer to be worked on. Valid value range
 *         is from 0 to (the number of layers implemented in the device - 1).
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_EnableLayer(XOSD *InstancePtr, u8 LayerIndex)
{
	u32 LayerBaseRegAddr;
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(LayerIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[LayerIndex].LayerType != \
					XOSD_LAYER_TYPE_DISABLE);

	/* Calculate the base register address of the layer to work on */
	LayerBaseRegAddr = XOSD_L0C + (LayerIndex * XOSD_LAYER_SIZE);

	/* Read the current Layer Control register value */
	RegValue = 	XOSD_ReadReg(InstancePtr->Config.BaseAddress,
								LayerBaseRegAddr + XOSD_LXC);

	/* Set the Layer Enable field */
	RegValue |= XOSD_LXC_EN_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, LayerBaseRegAddr + XOSD_LXC,
					RegValue);

	return;
}

/*****************************************************************************/
/**
 * This function disables an OSD layer.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  LayerIndex indicates which layer to be worked on. Valid value range
 *         is from 0 to (the number of layers implemented in the device - 1).
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_DisableLayer(XOSD *InstancePtr, u8 LayerIndex)
{
	u32 LayerBaseRegAddr;
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(LayerIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[LayerIndex].LayerType != \
					XOSD_LAYER_TYPE_DISABLE);

	/* Calculate the base register address of the layer to work on */
	LayerBaseRegAddr = XOSD_L0C + (LayerIndex * XOSD_LAYER_SIZE);

	/* Read the current Layer Control register value */
	RegValue = 	XOSD_ReadReg(InstancePtr->Config.BaseAddress,
								LayerBaseRegAddr + XOSD_LXC);

	/* Clear the Layer Enable field */
	RegValue &= ~XOSD_LXC_EN_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, LayerBaseRegAddr + XOSD_LXC,
					RegValue);
}

/*****************************************************************************/
/**
 * This function loads color LUT data into an OSD Graphics Controller Bank.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  GcIndex indicates which Graphics Controller to work on. Valid value
 *         range is from 0 to (The Number of Layers) - 1. The layer's type must
 *         be set to XOSD_LAYER_TYPE_GPU (defined in xosd_hw.h) for this
 *         function to work properly.
 * @param  BankIndex indicates which GC Bank to be worked on. Valid value range
 *         is from 0 to XOSD_GC_BANK_NUM - 1.
 * @param  ColorData points to the color LUT data to be loaded.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_LoadColorLUTBank(XOSD *InstancePtr, u8 GcIndex, u8 BankIndex,
							u32 *ColorData)
{
	u32 i;
	u32 RegValue;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(GcIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[GcIndex].LayerType == XOSD_LAYER_TYPE_GPU);
	XASSERT_VOID(BankIndex < XOSD_GC_BANK_NUM);
	XASSERT_VOID(ColorData != NULL);

	/* Choose which bank to be loaded */
	RegValue = (((u32)BankIndex) + XOSD_GCWBA_COL0) & XOSD_GCWBA_BANK_MASK;
	RegValue |= (((u32)GcIndex) << XOSD_GCWBA_GCNUM_SHIFT)
					& XOSD_GCWBA_GCNUM_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCWBA, RegValue);

	/* Load color data */
	for(i = 0;
		i < (InstancePtr->Layers[GcIndex].ColorLutSize * XOSD_COLOR_ENTRY_SIZE)
				/ sizeof(u32);
		i++) {
		XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCD, ColorData[i]);
	}

	/* Set the active color LUT bank */
	RegValue = XOSD_ReadReg(InstancePtr->Config.BaseAddress, XOSD_GCABA);
	RegValue &= ~(1 << (XOSD_GCABA_COL_SHIFT + GcIndex));
	RegValue |= ((u32)BankIndex) << (XOSD_GCABA_COL_SHIFT + (u32)GcIndex);
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCABA, RegValue);

	return;
}

/*****************************************************************************/
/**
 * This function loads Character Set data (font) into an OSD Graphics
 * Controller Bank.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  GcIndex indicates which Graphics Controller to work on. Valid value
 *         range is from 0 to (The Number of Layers) - 1. The layer's type must
 *         be set to XOSD_LAYER_TYPE_GPU (defined in xosd_hw.h) for this
 *         function to work properly.
 * @param  BankIndex indicates which GC Bank to be worked on. Valid value range
 *         is from 0 to XOSD_GC_BANK_NUM - 1.
 * @param  CharSetData points to the Character Set data to be loaded.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_LoadCharacterSetBank(XOSD *InstancePtr, u8 GcIndex, u8 BankIndex,
								u32 *CharSetData)
{
	u32 RegValue;
	u32 FontWriteNum;
	u32 i;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(GcIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[GcIndex].LayerType == XOSD_LAYER_TYPE_GPU);
	XASSERT_VOID(BankIndex < XOSD_GC_BANK_NUM);
	XASSERT_VOID(CharSetData != NULL);

	/* Choose which bank to be loaded */
	RegValue = (((u32)BankIndex) + XOSD_GCWBA_CHR0) & XOSD_GCWBA_BANK_MASK;
	RegValue |= (((u32)GcIndex) << XOSD_GCWBA_GCNUM_SHIFT)
					& XOSD_GCWBA_GCNUM_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCWBA, RegValue);

	/* Calculate the number of write to load the whole font data set */
	FontWriteNum = ((u32)InstancePtr->Layers[GcIndex].FontWidth) *
					((u32)InstancePtr->Layers[GcIndex].FontHeight) *
					((u32)InstancePtr->Layers[GcIndex].FontBitsPerPixel);
	FontWriteNum /= XOSD_FONT_BIT_TO_BYTE;
	FontWriteNum *= ((u32)InstancePtr->Layers[GcIndex].FontNumChars);
	FontWriteNum /= sizeof(u32);

	/* Load the font data */
	for (i = 0; i < FontWriteNum; i++)
	{
		XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCD,
						CharSetData[i]);
	}

	/* Set the bank to be active so the font is used by the core */
	RegValue = XOSD_ReadReg(InstancePtr->Config.BaseAddress, XOSD_GCABA);
	RegValue &= ~(1 << (XOSD_GCABA_CHR_SHIFT + GcIndex));
	RegValue |= ((u32)BankIndex) << (XOSD_GCABA_CHR_SHIFT + (u32)GcIndex);
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCABA, RegValue);
}

/*****************************************************************************/
/**
 * This function loads Text data into an OSD Graphics Controller Bank.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  GcIndex indicates which Graphics Controller to work on. Valid value
 *         range is from 0 to (The Number of Layers) - 1. The layer's type must
 *         be set to XOSD_LAYER_TYPE_GPU (defined in xosd_hw.h) for this
 *         function to work properly.
 * @param  BankIndex indicates which GC Bank to be worked on. Valid value range
 *         is from 0 to XOSD_GC_BANK_NUM - 1.
 * @param  TextData points to the Text data to be loaded.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_LoadTextBank(XOSD *InstancePtr, u8 GcIndex, u8 BankIndex,
						u32 *TextData)
{
	u32 i;
	u32 RegValue;
	u32 EndianConvert;
	u32 Data;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(GcIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[GcIndex].LayerType == XOSD_LAYER_TYPE_GPU);
	XASSERT_VOID(BankIndex < XOSD_GC_BANK_NUM);
	XASSERT_VOID(TextData != NULL);

	/* Choose which bank to be loaded */
	RegValue = (((u32)BankIndex) + XOSD_GCWBA_TXT0) & XOSD_GCWBA_BANK_MASK;
	RegValue |= (((u32)GcIndex) << XOSD_GCWBA_GCNUM_SHIFT)
					& XOSD_GCWBA_GCNUM_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCWBA, RegValue);

    /*
     * Convert endian until the h/w does the conversion for GCD register
     */
	EndianConvert = 1;

	for(i = 0;
		i < (u32)(InstancePtr->Layers[GcIndex].TextNumStrings) *
			(u32)(InstancePtr->Layers[GcIndex].TextMaxStringLength) /
			sizeof(u32);
		i++) {
		if (EndianConvert) {
			Data = TextData[i];
			XIo_FromLittleEndian32(Data, &Data);
			XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCD, Data);
		}
		else {
			XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCD,
							TextData[i]);
		}
	}

	/* Set the active text bank */
	RegValue = XOSD_ReadReg(InstancePtr->Config.BaseAddress, XOSD_GCABA);
	RegValue &= ~(1 << (XOSD_GCABA_TXT_SHIFT + GcIndex));
	RegValue |= ((u32)BankIndex) << (XOSD_GCABA_TXT_SHIFT + (u32)GcIndex);
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCABA, RegValue);

	return;
}

/*****************************************************************************/
/**
 * This function chooses active banks for a GC in an OSD device.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  GcIndex indicates which Graphics Controller to work on. Valid value
 *         range is from 0 to (The Number of Layers) - 1. The layer's type must
 *         be set to XOSD_LAYER_TYPE_GPU (defined in xosd_hw.h) for this
 *         function to work properly.
 * @param  ColorBankIndex indicates the Color LUT bank to be choose as active.
 * @param  CharBankIndex indicates the Character Set bank to be choose as
 *         active.
 * @param  TextBankIndex indicates the Text Data bank to be choose as active.
 * @param  InstructionBankIndex indicates the Instruction bank to be choose as
 *         active.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_SetActiveBank(XOSD *InstancePtr, u8 GcIndex, u8 ColorBankIndex,
							u8 CharBankIndex, u8 TextBankIndex,
							u8 InstructionBankIndex)
{
	u32 RegValue;

    /* Verify arguments */
    XASSERT_VOID(InstancePtr != NULL);
    XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(GcIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[GcIndex].LayerType == XOSD_LAYER_TYPE_GPU);
    XASSERT_VOID(ColorBankIndex < XOSD_GC_BANK_NUM);
    XASSERT_VOID(CharBankIndex < XOSD_GC_BANK_NUM);
    XASSERT_VOID(TextBankIndex < XOSD_GC_BANK_NUM);
    XASSERT_VOID(InstructionBankIndex < XOSD_GC_BANK_NUM);

	/* Clear the current active bank setting first */
	RegValue = XOSD_ReadReg(InstancePtr->Config.BaseAddress, XOSD_GCABA);
	RegValue &= ~(1 << GcIndex) & XOSD_GCABA_INS_MASK;
	RegValue &= ~(1 << (XOSD_GCABA_COL_SHIFT + GcIndex)) & XOSD_GCABA_COL_MASK;
	RegValue &= ~(1 << (XOSD_GCABA_TXT_SHIFT + GcIndex)) & XOSD_GCABA_TXT_MASK;
	RegValue &= ~(1 << (XOSD_GCABA_CHR_SHIFT + GcIndex)) & XOSD_GCABA_CHR_MASK;

	/* Choose the active banks */
	RegValue |= (((u32)InstructionBankIndex) << GcIndex) & XOSD_GCABA_INS_MASK;
	RegValue |= (((u32)ColorBankIndex) << (XOSD_GCABA_COL_SHIFT + GcIndex)) &
					XOSD_GCABA_COL_MASK;
	RegValue |= (((u32)TextBankIndex) << (XOSD_GCABA_TXT_SHIFT + GcIndex)) &
					XOSD_GCABA_TXT_MASK;
	RegValue |= (((u32)CharBankIndex) << (XOSD_GCABA_CHR_SHIFT + GcIndex)) &
					XOSD_GCABA_CHR_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCABA, RegValue);

	return;
}

/*****************************************************************************/
/**
 * This function creates an instruction for an OSD.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  InstructionPtr is a pointer to the instruction buffer to be
 *         populated with the instruction to be created. The upper level
 *         application is responsible for allocating this instruction buffer.
 * @param  GcIndex indicates the Graphics Controller that will consume the
 *         instruction. Valid value range is from 0 to
 *         (The Number of Layers) - 1. The layer's type must
 *         be set to XOSD_LAYER_TYPE_GPU (defined in xosd_hw.h) for this
 *         function to work properly.
 * @param  ObjType indicates the type of object to draw. Use
 *         one of XOSD_INS_OPCODE_... constants defined in xosd_hw.h.
 * @param  ObjSize indicates line width of boxes and lines and the text scale
 *         factor for text boxes.
 * @param  XStart indicates the horizontal start pixel of the Object.
 * @param  YStart indicates the vertical start line of the Object.
 * @param  XEnd indicates the horizontal end pixel of the Object.
 * @param  YEnd indicates the vertical end line of the Object.
 * @param  TextIndex indicates the string index.
 * @param  ColorIndex indicates the color index.
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_CreateInstruction(XOSD *InstancePtr, u32 *InstructionPtr,
                            u8 GcIndex, u16 ObjType, u8 ObjSize,
                            u16 XStart, u16 YStart, u16 XEnd, u16 YEnd,
                            u8 TextIndex, u8 ColorIndex)
{
	u32 Value;

    /* Verify arguments */
    XASSERT_VOID(InstancePtr != NULL);
    XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
    XASSERT_VOID(InstructionPtr != NULL);
	XASSERT_VOID(GcIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[GcIndex].LayerType == XOSD_LAYER_TYPE_GPU);
    XASSERT_VOID((ObjType == XOSD_INS_OPCODE_END) ||
    			 (ObjType == XOSD_INS_OPCODE_NOP) ||
    			 (ObjType == XOSD_INS_OPCODE_BOX) ||
    			 (ObjType == XOSD_INS_OPCODE_LINE) ||
    			 (ObjType == XOSD_INS_OPCODE_TXT) ||
    			 (ObjType == XOSD_INS_OPCODE_BOXTXT));
    XASSERT_VOID(XEnd < InstancePtr->ScreenWidth);
    XASSERT_VOID(YEnd < InstancePtr->ScreenHeight);
    XASSERT_VOID(TextIndex < InstancePtr->Layers[GcIndex].TextNumStrings);
    XASSERT_VOID(ColorIndex < InstancePtr->Layers[GcIndex].ColorLutSize);

    /* Clear the whole instruction first */
    memset((void *)InstructionPtr, 0, XOSD_INS_SIZE * sizeof(u32));

    /* Populate instruction word 0 fields */
    Value = ((u32)XStart) & XOSD_INS0_XSTART_MASK;
    Value |= (((u32)XEnd) << XOSD_INS0_XEND_SHIFT) & XOSD_INS0_XEND_MASK;
    Value |= (((u32)GcIndex) << XOSD_INS0_GCNUM_SHIFT) & XOSD_INS0_GCNUM_MASK;
    Value |= (((u32)ObjType) << XOSD_INS0_OPCODE_SHIFT)
				& XOSD_INS0_OPCODE_MASK;
    InstructionPtr[XOSD_INS0] = Value;

    /* Populate instruction word 1 fields */
    Value = ((u32)TextIndex) & XOSD_INS1_TXTINDEX_MASK;
    InstructionPtr[XOSD_INS1] = Value;

    /* Populate instruction word 2 fields */
    Value = ((u32)YStart) & XOSD_INS2_YSTART_MASK;
    Value |= (((u32)YEnd) << XOSD_INS2_YEND_SHIFT) & XOSD_INS2_YEND_MASK;
    Value |= (((u32)ObjSize) << XOSD_INS2_OBJSIZE_SHIFT)
				& XOSD_INS2_OBJSIZE_MASK;
    InstructionPtr[XOSD_INS2] = Value;

    /* Populate instruction word 3 fields */
    Value = ((u32)ColorIndex) & XOSD_INS3_COL_MASK;
    InstructionPtr[XOSD_INS3] = Value;

    return;
}

/*****************************************************************************/
/**
 * This function load an instruction list to be used by an Graphic Controller
 * in an OSD device.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be
 *         worked on.
 * @param  GcIndex indicates which Graphics Controller to work on. Valid value
 *         range is from 0 to (The Number of Layers) - 1. The layer's type must
 *         be set to XOSD_LAYER_TYPE_GPU (defined in xosd_hw.h) for this
 *         function to work properly.
 * @param  BankIndex indicates which GC Bank to be worked on. Valid value range
 *         is from 0 to XOSD_GC_BANK_NUM.
 * @param  InstSetPtr is a pointer to the start of the instruction list to load
 *         into the OSD device. The last instruction in the list must has
 *         XOSD_INS_OPCODE_END type.
 * @param  InstNum indicates the number of the instructions in the list to load.
 *         Valid value range is from 1 to the half of the size of the instruction
 *         memory created for the Graphic Controller
 * @return NONE.
 *
 *****************************************************************************/
void XOSD_LoadInstructionList(XOSD *InstancePtr, u8 GcIndex, u8 BankIndex,
								u32 *InstSetPtr, u32 InstNum)
{
	u32 RegValue;
	u32 i;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(InstancePtr->IsReady == XCOMPONENT_IS_READY);
	XASSERT_VOID(GcIndex < InstancePtr->Config.LayerNum);
	XASSERT_VOID(InstancePtr->Layers[GcIndex].LayerType == XOSD_LAYER_TYPE_GPU);
	XASSERT_VOID(BankIndex < XOSD_GC_BANK_NUM);
	XASSERT_VOID(InstSetPtr != NULL);
	XASSERT_VOID(InstNum <= InstancePtr->Layers[GcIndex].InstructionNum);

	/* Choose which bank to be loaded */
	RegValue = (((u32)BankIndex) + XOSD_GCWBA_INS0) & XOSD_GCWBA_BANK_MASK;
	RegValue |= (((u32)GcIndex) << XOSD_GCWBA_GCNUM_SHIFT)
					& XOSD_GCWBA_GCNUM_MASK;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCWBA, RegValue);

	for (i = 0; i < InstNum * XOSD_INS_SIZE; i++) {
		XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCD,
						InstSetPtr[i]);
	}

	/*
	 * Notify OSD this is the end of the instruction list by adding an END
	 * instruction
	 */
	if (InstNum < InstancePtr->Layers[GcIndex].InstructionNum) {
		for (i = 0; i < XOSD_INS_SIZE; i++) {
			XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCD, 0);
		}
	}

	/* Set the active instruction bank */
	RegValue = XOSD_ReadReg(InstancePtr->Config.BaseAddress, XOSD_GCABA);
	RegValue &= ~(1 << GcIndex);
	RegValue |= BankIndex << GcIndex;
	XOSD_WriteReg(InstancePtr->Config.BaseAddress, XOSD_GCABA, RegValue);

	return;
}

/*****************************************************************************/
/*
 * This function populates the Layer array in the OSD driver instance with
 * the properties of all layers. This is to help fetch the info faster later.
 *
 * @param  InstancePtr is a pointer to the OSD device instance to be worked on.
 * @param  CfgPtr points to the configuration structure associated with the
 *         OSD device.
 * @return None
 *
 *****************************************************************************/
static void PopulateLayerProperty(XOSD *InstancePtr, XOSD_Config *CfgPtr)
{
	XOSD *IP;

	/* Verify arguments */
	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(CfgPtr != NULL);

	/* Use a short variable name to keep the lines in this function shorter */
	IP = InstancePtr;

	/* Layer #0 */
	IP->Layers[0].LayerType             = CfgPtr->Layer0Type;
	IP->Layers[0].InstructionNum        = CfgPtr->Layer0InstructionMemSize;
	IP->Layers[0].InstructionBoxEnable  = CfgPtr->Layer0InstructionBoxEnable;
	IP->Layers[0].InstructionLineEnable = CfgPtr->Layer0InstructionLineEnable;
	IP->Layers[0].InstructionTextEnable = CfgPtr->Layer0InstructionTextEnable;
	IP->Layers[0].ColorLutSize          = CfgPtr->Layer0ColorLutSize;
	IP->Layers[0].ColorLutMemoryType    = CfgPtr->Layer0ColorLutMemoryType;
	IP->Layers[0].FontNumChars          = CfgPtr->Layer0FontNumChars;
	IP->Layers[0].FontWidth		        = CfgPtr->Layer0FontWidth;
	IP->Layers[0].FontHeight			= CfgPtr->Layer0FontHeight;
	IP->Layers[0].FontBitsPerPixel      = CfgPtr->Layer0FontBitsPerPixel;
	IP->Layers[0].FontAsciiOffset       = CfgPtr->Layer0FontAsciiOffset;
	IP->Layers[0].TextNumStrings        = CfgPtr->Layer0TextNumStrings;
	IP->Layers[0].TextMaxStringLength   = CfgPtr->Layer0TextMaxStringLength;

	/* Layer #1 */
	IP->Layers[1].LayerType             = CfgPtr->Layer1Type;
	IP->Layers[1].InstructionNum        = CfgPtr->Layer1InstructionMemSize;
	IP->Layers[1].InstructionBoxEnable  = CfgPtr->Layer1InstructionBoxEnable;
	IP->Layers[1].InstructionLineEnable = CfgPtr->Layer1InstructionLineEnable;
	IP->Layers[1].InstructionTextEnable = CfgPtr->Layer1InstructionTextEnable;
	IP->Layers[1].ColorLutSize          = CfgPtr->Layer1ColorLutSize;
	IP->Layers[1].ColorLutMemoryType    = CfgPtr->Layer1ColorLutMemoryType;
	IP->Layers[1].FontNumChars          = CfgPtr->Layer1FontNumChars;
	IP->Layers[1].FontWidth		        = CfgPtr->Layer1FontWidth;
	IP->Layers[1].FontHeight			= CfgPtr->Layer1FontHeight;
	IP->Layers[1].FontBitsPerPixel      = CfgPtr->Layer1FontBitsPerPixel;
	IP->Layers[1].FontAsciiOffset       = CfgPtr->Layer1FontAsciiOffset;
	IP->Layers[1].TextNumStrings        = CfgPtr->Layer1TextNumStrings;
	IP->Layers[1].TextMaxStringLength   = CfgPtr->Layer1TextMaxStringLength;

	/* Layer #2 */
	IP->Layers[2].LayerType             = CfgPtr->Layer2Type;
	IP->Layers[2].InstructionNum        = CfgPtr->Layer2InstructionMemSize;
	IP->Layers[2].InstructionBoxEnable  = CfgPtr->Layer2InstructionBoxEnable;
	IP->Layers[2].InstructionLineEnable = CfgPtr->Layer2InstructionLineEnable;
	IP->Layers[2].InstructionTextEnable = CfgPtr->Layer2InstructionTextEnable;
	IP->Layers[2].ColorLutSize          = CfgPtr->Layer2ColorLutSize;
	IP->Layers[2].ColorLutMemoryType    = CfgPtr->Layer2ColorLutMemoryType;
	IP->Layers[2].FontNumChars          = CfgPtr->Layer2FontNumChars;
	IP->Layers[2].FontWidth		        = CfgPtr->Layer2FontWidth;
	IP->Layers[2].FontHeight			= CfgPtr->Layer2FontHeight;
	IP->Layers[2].FontBitsPerPixel      = CfgPtr->Layer2FontBitsPerPixel;
	IP->Layers[2].FontAsciiOffset       = CfgPtr->Layer2FontAsciiOffset;
	IP->Layers[2].TextNumStrings        = CfgPtr->Layer2TextNumStrings;
	IP->Layers[2].TextMaxStringLength   = CfgPtr->Layer2TextMaxStringLength;

	/* Layer #3 */
	IP->Layers[3].LayerType             = CfgPtr->Layer3Type;
	IP->Layers[3].InstructionNum        = CfgPtr->Layer3InstructionMemSize;
	IP->Layers[3].InstructionBoxEnable  = CfgPtr->Layer3InstructionBoxEnable;
	IP->Layers[3].InstructionLineEnable = CfgPtr->Layer3InstructionLineEnable;
	IP->Layers[3].InstructionTextEnable = CfgPtr->Layer3InstructionTextEnable;
	IP->Layers[3].ColorLutSize          = CfgPtr->Layer3ColorLutSize;
	IP->Layers[3].ColorLutMemoryType    = CfgPtr->Layer3ColorLutMemoryType;
	IP->Layers[3].FontNumChars          = CfgPtr->Layer3FontNumChars;
	IP->Layers[3].FontWidth		        = CfgPtr->Layer3FontWidth;
	IP->Layers[3].FontHeight			= CfgPtr->Layer3FontHeight;
	IP->Layers[3].FontBitsPerPixel      = CfgPtr->Layer3FontBitsPerPixel;
	IP->Layers[3].FontAsciiOffset       = CfgPtr->Layer3FontAsciiOffset;
	IP->Layers[3].TextNumStrings        = CfgPtr->Layer3TextNumStrings;
	IP->Layers[3].TextMaxStringLength   = CfgPtr->Layer3TextMaxStringLength;

	/* Layer #4 */
	IP->Layers[4].LayerType             = CfgPtr->Layer4Type;
	IP->Layers[4].InstructionNum        = CfgPtr->Layer4InstructionMemSize;
	IP->Layers[4].InstructionBoxEnable  = CfgPtr->Layer4InstructionBoxEnable;
	IP->Layers[4].InstructionLineEnable = CfgPtr->Layer4InstructionLineEnable;
	IP->Layers[4].InstructionTextEnable = CfgPtr->Layer4InstructionTextEnable;
	IP->Layers[4].ColorLutSize          = CfgPtr->Layer4ColorLutSize;
	IP->Layers[4].ColorLutMemoryType    = CfgPtr->Layer4ColorLutMemoryType;
	IP->Layers[4].FontNumChars          = CfgPtr->Layer4FontNumChars;
	IP->Layers[4].FontWidth		        = CfgPtr->Layer4FontWidth;
	IP->Layers[4].FontHeight			= CfgPtr->Layer4FontHeight;
	IP->Layers[4].FontBitsPerPixel      = CfgPtr->Layer4FontBitsPerPixel;
	IP->Layers[4].FontAsciiOffset       = CfgPtr->Layer4FontAsciiOffset;
	IP->Layers[4].TextNumStrings        = CfgPtr->Layer4TextNumStrings;
	IP->Layers[4].TextMaxStringLength   = CfgPtr->Layer4TextMaxStringLength;

	/* Layer #5 */
	IP->Layers[5].LayerType             = CfgPtr->Layer5Type;
	IP->Layers[5].InstructionNum        = CfgPtr->Layer5InstructionMemSize;
	IP->Layers[5].InstructionBoxEnable  = CfgPtr->Layer5InstructionBoxEnable;
	IP->Layers[5].InstructionLineEnable = CfgPtr->Layer5InstructionLineEnable;
	IP->Layers[5].InstructionTextEnable = CfgPtr->Layer5InstructionTextEnable;
	IP->Layers[5].ColorLutSize          = CfgPtr->Layer5ColorLutSize;
	IP->Layers[5].ColorLutMemoryType    = CfgPtr->Layer5ColorLutMemoryType;
	IP->Layers[5].FontNumChars          = CfgPtr->Layer5FontNumChars;
	IP->Layers[5].FontWidth		        = CfgPtr->Layer5FontWidth;
	IP->Layers[5].FontHeight			= CfgPtr->Layer5FontHeight;
	IP->Layers[5].FontBitsPerPixel      = CfgPtr->Layer5FontBitsPerPixel;
	IP->Layers[5].FontAsciiOffset       = CfgPtr->Layer5FontAsciiOffset;
	IP->Layers[5].TextNumStrings        = CfgPtr->Layer5TextNumStrings;
	IP->Layers[5].TextMaxStringLength   = CfgPtr->Layer5TextMaxStringLength;

	/* Layer #6 */
	IP->Layers[6].LayerType             = CfgPtr->Layer6Type;
	IP->Layers[6].InstructionNum        = CfgPtr->Layer6InstructionMemSize;
	IP->Layers[6].InstructionBoxEnable  = CfgPtr->Layer6InstructionBoxEnable;
	IP->Layers[6].InstructionLineEnable = CfgPtr->Layer6InstructionLineEnable;
	IP->Layers[6].InstructionTextEnable = CfgPtr->Layer6InstructionTextEnable;
	IP->Layers[6].ColorLutSize          = CfgPtr->Layer6ColorLutSize;
	IP->Layers[6].ColorLutMemoryType    = CfgPtr->Layer6ColorLutMemoryType;
	IP->Layers[6].FontNumChars          = CfgPtr->Layer6FontNumChars;
	IP->Layers[6].FontWidth		        = CfgPtr->Layer6FontWidth;
	IP->Layers[6].FontHeight			= CfgPtr->Layer6FontHeight;
	IP->Layers[6].FontBitsPerPixel      = CfgPtr->Layer6FontBitsPerPixel;
	IP->Layers[6].FontAsciiOffset       = CfgPtr->Layer6FontAsciiOffset;
	IP->Layers[6].TextNumStrings        = CfgPtr->Layer6TextNumStrings;
	IP->Layers[6].TextMaxStringLength   = CfgPtr->Layer6TextMaxStringLength;

	/* Layer #7 */
	IP->Layers[7].LayerType             = CfgPtr->Layer7Type;
	IP->Layers[7].InstructionNum        = CfgPtr->Layer7InstructionMemSize;
	IP->Layers[7].InstructionBoxEnable  = CfgPtr->Layer7InstructionBoxEnable;
	IP->Layers[7].InstructionLineEnable = CfgPtr->Layer7InstructionLineEnable;
	IP->Layers[7].InstructionTextEnable = CfgPtr->Layer7InstructionTextEnable;
	IP->Layers[7].ColorLutSize          = CfgPtr->Layer7ColorLutSize;
	IP->Layers[7].ColorLutMemoryType    = CfgPtr->Layer7ColorLutMemoryType;
	IP->Layers[7].FontNumChars          = CfgPtr->Layer7FontNumChars;
	IP->Layers[7].FontWidth		        = CfgPtr->Layer7FontWidth;
	IP->Layers[7].FontHeight			= CfgPtr->Layer7FontHeight;
	IP->Layers[7].FontBitsPerPixel      = CfgPtr->Layer7FontBitsPerPixel;
	IP->Layers[7].FontAsciiOffset       = CfgPtr->Layer7FontAsciiOffset;
	IP->Layers[7].TextNumStrings        = CfgPtr->Layer7TextNumStrings;
	IP->Layers[7].TextMaxStringLength   = CfgPtr->Layer7TextMaxStringLength;

	/* Convert instruction memory sizes into the maximum numbers of
	 * instructions supported
	 */
	IP->Layers[0].InstructionNum       /= XOSD_INS_MEM_SIZE_TO_NUM;
	IP->Layers[1].InstructionNum       /= XOSD_INS_MEM_SIZE_TO_NUM;
	IP->Layers[2].InstructionNum       /= XOSD_INS_MEM_SIZE_TO_NUM;
	IP->Layers[3].InstructionNum       /= XOSD_INS_MEM_SIZE_TO_NUM;
	IP->Layers[4].InstructionNum       /= XOSD_INS_MEM_SIZE_TO_NUM;
	IP->Layers[5].InstructionNum       /= XOSD_INS_MEM_SIZE_TO_NUM;
	IP->Layers[6].InstructionNum       /= XOSD_INS_MEM_SIZE_TO_NUM;
	IP->Layers[7].InstructionNum       /= XOSD_INS_MEM_SIZE_TO_NUM;
	return;
}

/******************************************************************************/
/*
 * This routine is a stub for the asynchronous callbacks. The stub is here in
 * case the upper layer forgot to set the handlers. On initialization, All
 * handlers except error handler are set to this callback. It is considered an
 * error for this handler to be invoked.
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
