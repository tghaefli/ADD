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
// Create Date:         Mar 05, 2010
// Design Name:         IVK Video Resolution
// Module Name:         ivk_video_resolution.h
// Project Name:        IVK
// Target Devices:      Spartan-6
// Avnet Boards:        IVK
//
// Tool versions:       ISE 11.4
//
// Description:         IVK Video Resolution
//                      - video timing definitions
//                      - video resolution detection (using ivk_video_det pcore)
//                      - video timing generation (using ivk_video_gen pcore)
//
// Dependencies:        
//
// Revision:            Mar 05, 2010: 1.00 Initial version
//
//----------------------------------------------------------------

#ifndef __IVK_VIDEO_RESOLUTION_H__
#define __IVK_VIDEO_RESOLUTION_H__

// Located in: microblaze_0/include/
#include "xbasic_types.h"
#include "xutil.h"
#include "xparameters.h"
#include "xstatus.h"

// Video Pattern Generator - Video Resolution values
#define VIDEO_RESOLUTION_VGA       0
#define VIDEO_RESOLUTION_NTSC      1
#define VIDEO_RESOLUTION_SVGA      2
#define VIDEO_RESOLUTION_XGA       3
#define VIDEO_RESOLUTION_720P      4
#define VIDEO_RESOLUTION_SXGA      5
#define VIDEO_RESOLUTION_1080P     6
#define VIDEO_RESOLUTION_UXGA      7
#define NUM_VIDEO_RESOLUTIONS      8

char *  ivk_vres_get_name(Xuint32 resolutionId);
Xuint32 ivk_vres_get_width(Xuint32 resolutionId);
Xuint32 ivk_vres_get_height(Xuint32 resolutionId);

Xint32 ivk_vres_detect( void );

#endif // __IVK_VIDEO_RESOLUTION_H__
