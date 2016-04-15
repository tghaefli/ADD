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
// Create Date:         Dec 03, 2009
// Design Name:         IVK
// Module Name:         ivk_video_gen.c
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
// Revision:            Dec 03, 2009: 1.00 Initial Version
//
// ----------------------------------------------------------------


/***************************** Include Files *******************************/

#include "ivk_video_gen.h"

/************************** Function Definitions ***************************/

/**
 *
 * Write the video timing settings. 
 *
 * @param   BaseAddress is the base address of the DE_GEN device.
 *
 * @param   pConfig : pointer to video_timing_t data structure containing:
 *          - h_active    : Horizontal active region
 *          - h_fporch    : Horizontal front porch
 *          - h_syncpol   : Horizontal synchronization polarity
 *          - h_syncwidth : Horizontal synchronization pulse width
 *          - h_bporch    : Horizontal back porch
 *          - v_active    : Vertical   active region
 *          - v_fporch    : Vertical   front porch
 *          - v_syncpol   : Vertical   synchronization polarity
 *          - v_syncwidth : Vertical   synchronization pulse width
 *          - v_bporch    : Vertical   back porch
 *
 * @return  None.
 *
 * @note
 *
 */
void write_IVK_VIDEO_GEN_video_timing(Xuint32 BaseAddress, video_timing_t *pConfig )
{
   Xuint32 h_active;
   Xuint32 h_fporch;
   Xuint32 h_syncpol;
   Xuint32 h_syncwidth;
   Xuint32 h_bporch;
   Xuint32 v_active;
   Xuint32 v_fporch;
   Xuint32 v_syncpol;
   Xuint32 v_syncwidth;
   Xuint32 v_bporch;
   
   h_active    = pConfig->h_active;
   h_fporch    = pConfig->h_fporch;
   h_syncpol   = pConfig->h_syncpol;
   h_syncwidth = pConfig->h_syncwidth;
   h_bporch    = pConfig->h_bporch;
   v_active    = pConfig->v_active;
   v_fporch    = pConfig->v_fporch;
   v_syncpol   = pConfig->v_syncpol;
   v_syncwidth = pConfig->v_syncwidth;
   v_bporch    = pConfig->v_bporch;

   // Horizontal settings
   IVK_VIDEO_GEN_mWriteSlaveReg0(BaseAddress, 0,                      (h_active)<<16 | (h_fporch) );
   IVK_VIDEO_GEN_mWriteSlaveReg1(BaseAddress, 0, (h_syncpol)<<31 | (h_syncwidth)<<16 | (h_bporch) );
   // Vertical settings
   IVK_VIDEO_GEN_mWriteSlaveReg2(BaseAddress, 0,                     (v_active )<<16 | (v_fporch) );
   IVK_VIDEO_GEN_mWriteSlaveReg3(BaseAddress, 0, (v_syncpol)<<31 | (v_syncwidth)<<16 | (v_bporch) );
}

