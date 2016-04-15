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
// Module Name:         ivk_frame_buffer.h
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
//
//----------------------------------------------------------------

#ifndef __IVK_FRAME_BUFFER_H__
#define __IVK_FRAME_BUFFER_H__

// Located in: microblaze_0/include/
#include "xbasic_types.h"
#include "xutil.h"
#include "xparameters.h"
#include "xstatus.h"

Xuint32 ivk_fb_init(void);
Xuint32 ivk_fb_set_input_resolution(Xuint32 resolutionId, Xuint32 enable);
Xuint32 ivk_fb_set_output_resolution(Xuint32 resolutionId, Xuint32 enable);
Xuint32 ivk_fb_get_width(Xuint32 resolutionId);
Xuint32 ivk_fb_get_height(Xuint32 resolutionId);
Xuint32 ivk_fb_get_stride(Xuint32 resolutionId);
Xuint32 ivk_fb_get_offset(Xuint32 resolutionId);
Xuint32 ivk_fb_get_current_frame_index();
Xuint32 ivk_fb_get_current_frame_address();

Xuint32 ivk_fb_clear_memory( void );

void ivk_fb_disp_colorbar(Xuint32 x_size, Xuint32 y_size, Xuint32 frameAdr, Xuint32 stride);

#endif // __IVK_FRAME_BUFFER_H__
