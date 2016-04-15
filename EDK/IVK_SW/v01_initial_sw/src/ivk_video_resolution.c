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
// Module Name:         ivk_video_resolution.c
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

#include "ivk_video_resolution.h"

// Located in: microblaze_0/include/
#include "xbasic_types.h"
#include "xutil.h"
#include "xparameters.h"
#include "xstatus.h"

#if defined(XPAR_IVK_VIDEO_DET_NUM_INSTANCES)
#include "ivk_video_det.h"
#endif
#if defined(XPAR_IVK_VIDEO_GEN_NUM_INSTANCES)
#include "ivk_video_gen.h"
#endif


#define NUM_VIDEO_TIMING_PARAMS 10
static Xint8 *pVideoTimingParamNames[NUM_VIDEO_TIMING_PARAMS] = {
	"vav", // Vertical Active Video
   "vfp", // Vertical Front Porch
   "vsw", // Vertical Sync Width
   "vbp", // Vertical Back Porch
   "vsp", // Vertical Sync Polarity
	"hav", // Horizontal Active Video
   "hfp", // Horizontal Front Porch
   "hsw", // Horizontal Sync Width
   "hbp", // Horizontal Back Porch
   "hsp"  // Horizontal Sync Polarity
};

static Xuint16 pVideoTimingParamValues[NUM_VIDEO_RESOLUTIONS][NUM_VIDEO_TIMING_PARAMS] = {
   // vav,  vfp,  vsw,  vbp,  vsp,  hav,  hfp,  hsw,  hbp,  hsp
   {  480,   10,    2,   33,    0,  640,   16,   96,   48,    0 }, // VIDEO_RESOLUTION_VGA
   {  480,    9,    6,   30,    0,  720,   16,   62,   60,    0 }, // VIDEO_RESOLUTION_NTSC
   {  600,    1,    4,   23,    1,  800,   40,  128,   88,    1 }, // VIDEO_RESOLUTION_SVGA
   {  768,    3,    6,   29,    0, 1024,   24,  136,  160,    0 }, // VIDEO_RESOLUTION_XGA
   {  720,    5,    5,   20,    1, 1280,  110,   40,  220,    1 }, // VIDEO_RESOLUTION_720P
   { 1024,    1,    3,   26,    0, 1280,   48,  184,  200,    0 }, // VIDEO_RESOLUTION_SXGA
   { 1080,    4,    5,   36,    1, 1920,   88,   44,  148,    1 }, // VIDEO_RESOLUTION_1080P
   { 1200,    1,    3,   46,    0, 1600,   64,  192,  304,    0 }  // VIDEO_RESOLUTION_UXGA
};

static char *pVideoTimingNames[NUM_VIDEO_RESOLUTIONS] = {
   "VGA",   // VIDEO_RESOLUTION_VGA
   "NTSC",  // VIDEO_RESOLUTION_NTSC
   "SVGA",  // VIDEO_RESOLUTION_SVGA
   "XGA",   // VIDEO_RESOLUTION_XGA
   "720P",  // VIDEO_RESOLUTION_720P
   "SXGA",  // VIDEO_RESOLUTION_SXGA
   "1080P", // VIDEO_RESOLUTION_1080P
   "UXGA"   // VIDEO_RESOLUTION_UXGA
};


char *ivk_vres_get_name(Xuint32 resolutionId)
{
   if ( resolutionId < NUM_VIDEO_RESOLUTIONS )
   {
      return pVideoTimingNames[resolutionId];
   }
   else
   {
      return "{UNKNOWN}";
   }
}

Xuint32 ivk_vres_get_width(Xuint32 resolutionId)
{
   return pVideoTimingParamValues[resolutionId][5]; // horizontal active
}

Xuint32 ivk_vres_get_height(Xuint32 resolutionId)
{
   return pVideoTimingParamValues[resolutionId][0]; // vertical active
}


Xint32 ivk_vres_detect( void )
{
#if defined(XPAR_IVK_VIDEO_DET_NUM_INSTANCES)
  Xuint32 hsize;
  Xuint32 vsize;
  Xint32 resolution = -1;
  int i;
  
  read_IVK_VIDEO_DET_video_dimensions( XPAR_IVK_VIDEO_DET_0_BASEADDR, &hsize, &vsize );
  xil_printf( "Detected Video Dimensions = %d x %d\r\n", hsize, vsize );

  for ( i = 0; i < NUM_VIDEO_RESOLUTIONS; i++ )
  {
     if ( hsize == ivk_vres_get_width(i) && vsize == ivk_vres_get_height(i) )
     {
        xil_printf( "Detected Video Resolution = %s\r\n", ivk_vres_get_name(i) );
        resolution = i;
        break;
     }
  }  
  
  if ( resolution == -1 )
  {
     xil_printf( "Unknown Video Resolution !\r\n" );
  }
  
  return resolution;
#endif
}

Xuint32 ivk_vres_generate( Xuint32 resolutionId )
{
#if defined(XPAR_IVK_VIDEO_GEN_NUM_INSTANCES)
   video_timing_t config;
   config.h_active    = pVideoTimingParamValues[resolutionId][5]; // horizontal active
   config.h_fporch    = pVideoTimingParamValues[resolutionId][6]; // horizontal front porch
   config.h_syncpol   = pVideoTimingParamValues[resolutionId][9]; // horizontal sync polarity
   config.h_syncwidth = pVideoTimingParamValues[resolutionId][7]; // horizontal sync width
   config.h_bporch    = pVideoTimingParamValues[resolutionId][8]; // horizontal back porch
   config.v_active    = pVideoTimingParamValues[resolutionId][0]; // vertical active
   config.v_fporch    = pVideoTimingParamValues[resolutionId][1]; // vertical front porch
   config.v_syncpol   = pVideoTimingParamValues[resolutionId][4]; // vertical sync polarity
   config.v_syncwidth = pVideoTimingParamValues[resolutionId][2]; // vertical sync width
   config.v_bporch    = pVideoTimingParamValues[resolutionId][3]; // vertical back porch
   write_IVK_VIDEO_GEN_video_timing( XPAR_IVK_VIDEO_GEN_0_BASEADDR, &config );
#endif   
}

