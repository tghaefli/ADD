// ----------------------------------------------------------------
//      _____
//     /     \
//    /____   \____
//   / \===\   \==/
//  /___\===\___\/  AVNET
//       \======/
//        \====/    
// ----------------------------------------------------------------
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
// ----------------------------------------------------------------
//
// Create Date:         Feb 18, 2010
// Design Name:         IVK
// Module Name:         ivk_video_det.c
// Project Name:        IVK
// Target Devices:      Spartan-6
// Avnet Boards:        IVK
//
// Tool versions:       ISE 11.4
//
// Description:         Driver
//
// Dependencies:        
//
// Revision:            Feb 18, 2010: 1.00 Initial Version
//
// ----------------------------------------------------------------


/***************************** Include Files *******************************/

#include "ivk_video_det.h"

/************************** Function Definitions ***************************/

/**
 *
 * Read the detected video dimensions.
 *
 * @param   BaseAddress is the base address of the DE_GEN device.
 *
 * @param   pWidth  : pointer to response for video width (horizontal active region)
 *
 * @param   pHeight : pointer to response for video height (vertical active region)
 *
 * @return  None.
 *
 * @note
 *
 */
void read_IVK_VIDEO_DET_video_dimensions(Xuint32 BaseAddress, Xuint32 *pWidth, Xuint32 *pHeight )
{
   *pWidth  = IVK_VIDEO_DET_mReadSlaveReg0(BaseAddress, 0 );
   *pHeight = IVK_VIDEO_DET_mReadSlaveReg1(BaseAddress, 0 );

   return;
}

