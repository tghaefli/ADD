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
 * @file xvdma_sinit.c
 *
 * This file contains static initialization methods for Xilinx MVI Video DMA
 * device driver.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- ---- -------- -------------------------------------------------------
 * 1.00a xd   05/06/08 First release
 * </pre>
 *
 ******************************************************************************/

/***************************** Include Files *********************************/

#include "xvdma.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

/*****************************************************************************/
/**
 * XVDma_LookupConfig returns a reference to an XVDma_Config structure based
 * on the unique device id, <i>DeviceId</i>. The return value will refer to
 * an entry in the device configuration table defined in the xvdma_g.c file.
 *
 * @param DeviceId is the unique device ID of the device for the lookup
 *        operation.
 *
 * @return XVDma_LookupConfig returns a reference to a configuration record in
 *         the configuration table (in xvdma_g.c) corresponding to
 *         <i>DeviceId</i>, or NULL if no match is found.
 *
 ******************************************************************************/
XVDma_Config *XVDma_LookupConfig(u16 DeviceId)
{
	extern XVDma_Config XVDma_ConfigTable[];
	XVDma_Config *CfgPtr = NULL;
	int i;

	for (i = 0; i < XPAR_XVDMA_NUM_INSTANCES; i++) {
		if (XVDma_ConfigTable[i].DeviceId == DeviceId) {
			CfgPtr = &XVDma_ConfigTable[i];
			break;
		}
	}

	return (CfgPtr);
}
