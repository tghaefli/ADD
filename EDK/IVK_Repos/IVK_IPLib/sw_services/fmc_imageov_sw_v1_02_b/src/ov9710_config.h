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
//                     Copyright(c) 2009 Avnet, Inc.
//                             All rights reserved.
//
//----------------------------------------------------------------
//
// Create Date:         Jul 29, 2009
// Design Name:         FMC-IMAGEOV
// Module Name:         ov9710_config.h
// Project Name:        FMC-IMAGEOV
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-IMAGEOV
//
// Tool versions:       ISE 11.2
//
// Description:         OV9710 Configuration I2C sequences.
//
// Dependencies:        
//
// Revision:            Jul 29, 2009: 1.00 Initial version
//
//----------------------------------------------------------------

#ifndef __OV9710_CONFIG_H__
#define __OV9710_CONFIG_H__

#include <stdio.h>

#define OV9710_IIC_ADDR  0x30 // 0x60/0x61

////////////////////////////////////////////////////////////////////////
// Soft Reset
////////////////////////////////////////////////////////////////////////

Xuint8 ov9710_soft_reset[1][2]=
{
   // Soft Reset
   0x12, 0x80, // COM7    [7] SRST : soft reset => 1
};

////////////////////////////////////////////////////////////////////////
// Flip
////////////////////////////////////////////////////////////////////////

Xuint8 ov9710_flip_none[1][2]=
{
   // No Flip
   0x04, 0x00  // REG04 : [7] Mirror = OFF
               //         [6] Flip   = OFF
};
Xuint8 ov9710_flip_horizontal[1][2]=
{
   // No Flip
   0x04, 0x80  // REG04 : [7] Mirror = ON
               //         [6] Flip   = OFF
};
Xuint8 ov9710_flip_vertical[1][2]=
{
   // No Flip
   0x04, 0x40  // REG04 : [7] Mirror = OFF
               //         [6] Flip   = ON
};
Xuint8 ov9710_flip_both[1][2]=
{
   // No Flip
   0x04, 0xC0  // REG04 : [7] Mirror = ON
               //         [6] Flip   = ON
};

////////////////////////////////////////////////////////////////////////
// Test Pattern
////////////////////////////////////////////////////////////////////////

Xuint8 ov9710_testpattern_off[1][2]=
{
   // Test Pattern (off)
   0x97, 0x00  // DSP_CTRL_1   [7] smph_mean   : 0
               //            [6:4] rsvd
               //              [3] bar_en      : 1
               //              [2] sht_neg     : 0
               //            [1:0] bar_style   : 0
};

Xuint8 ov9710_testpattern_on1[1][2]=
{
   // Test Pattern (on)
   0x97, 0x08  // DSP_CTRL_1   [7] smph_mean   : 0
               //            [6:4] rsvd
               //              [3] bar_en      : 1
               //              [2] sht_neg     : 0
               //            [1:0] bar_style   : 0
};
Xuint8 ov9710_testpattern_on2[1][2]=
{
   // Test Pattern (on)
   0x97, 0x09  // DSP_CTRL_1   [7] smph_mean   : 0
               //            [6:4] rsvd
               //              [3] bar_en      : 1
               //              [2] sht_neg     : 0
               //            [1:0] bar_style   : 1
};
Xuint8 ov9710_testpattern_on3[1][2]=
{
   // Test Pattern (on)
   0x97, 0x0A  // DSP_CTRL_1   [7] smph_mean   : 0
               //            [6:4] rsvd
               //              [3] bar_en      : 1
               //              [2] sht_neg     : 0
               //            [1:0] bar_style   : 2
};
Xuint8 ov9710_testpattern_on4[1][2]=
{
   // Test Pattern (on)
   0x97, 0x0B  // DSP_CTRL_1   [7] smph_mean   : 0
               //            [6:4] rsvd
               //              [3] bar_en      : 1
               //              [2] sht_neg     : 0
               //            [1:0] bar_style   : 3
};

////////////////////////////////////////////////////////////////////////
// Auto Light Adjustments
////////////////////////////////////////////////////////////////////////

// auto-adjustments on
Xuint8 ov9710_autoadjustments_on[2][2]=
{
   0x13, 0x85, // COM8         [7] AEC speed selection : 1 (faster AEC adjustment)
	           //              [6] AEC step selection  : 0
			   //              [5] Banding filter sel. : 0 (OFF)
			   //              [4] rsvd
			   //              [3] LAEC select         : 0 (OFF)
			   //              [2] AGC control         : 1 (AUTO)
			   //              [1] rsvd
			   //              [0] Exposure control    : 1 (AUTO)
   // DSP
   0x96, 0xF1  // DSP_CTRL_0   [7] black_en    : 1
               //              [6] white_en    : 1
               //              [5] awbg_en     : 1
               //              [4] awb_en      : 1
               //              [3] lenc_en     : 0
               //              [2] lenc_det_en : 0
               //              [1] rsvd
               //              [0] isp_en      : 1
};

// auto-adjustments off
Xuint8 ov9710_autoadjustments_off[2][2]=
{
   0x13, 0x00, // COM8         [7] AEC speed selection : 0 (normal)
	           //              [6] AEC step selection  : 0
			   //              [5] Banding filter sel. : 0 (OFF)
			   //              [4] rsvd
			   //              [3] LAEC select         : 0 (OFF)
			   //              [2] AGC control         : 0 (MANUAL)
			   //              [1] rsvd
			   //              [0] Exposure control    : 0 (MANUAL)
   // DSP
   0x96, 0x00  // DSP_CTRL_0   [7] black_en    : 0
               //              [6] white_en    : 0
               //              [5] awbg_en     : 0
               //              [4] awb_en      : 0
               //              [3] lenc_en     : 0
               //              [2] lenc_det_en : 0
               //              [1] rsvd
               //              [0] isp_en      : 0
};

////////////////////////////////////////////////////////////////////////
// Video Resolutions
////////////////////////////////////////////////////////////////////////

// 1280x800 Full Resolution
Xuint8 ov9710_1280x800_full[18][2]=
{
   // 1280x800
   0x17, 0x25, // HSTART => [7:0] = HSTART[10:3]
   0x18, 0xA2, // AHsize => [7:0] = AHsize[10:3]
   0x19, 0x01, // VSTART => [7:0] = VSTART[9:2]
   0x1A, 0xCA, // AVsize => [7:0] = AVsize[9:2]
   0x03, 0x0A, // REG03  => [3:2] = AVsize[1:0]
               //           [1:0] = VSTART[1:0]
               //   VSTART[9:0] = 0x006 =   6
               //   AVsize[9:0] = 0x32A = 810
   0x32, 0x07, // REG32  => [2:0] = HSTART[2:0]
               //           [5:3] = AHsize[2:0]
               //   HSTART[10:0] = 0x12F =  303 (?)
               //   AHsize[10:0] = 0x510 = 1296 (?)
   0x98, 0x00, // DSP_CTRL_2 => [7:0] = pre_out_hoff[7:0]
   0x99, 0x00, // DSP_CTRL_3 => [7:0] = pre_out_voff[7:0]
   0x9A, 0x00, // DSP_CTRL_4 => [5:4] = pre_out_voff[9:8]
               //               [2:0] = pre_out_hoff[10:8]
               //   pre_out_voff[ 9:0] = 0x000 = 0
               //   pre_out_hoff[10:0] = 0x000 = 0
   
   0x57, 0x00, // REG57 => [4:2] = HSIZE[2:0]
               //          [1:0] = VSIZE[1:0]
   0x58, 0xC8, // REG58 => [7:0] = VSIZE[9:2]
   0x59, 0xA0, // REG69 => [7:0] = HSIZE[10:3]
               //   VSIZE[ 9:0] = 0x320 =  800
               //   HSIZE[10:0] = 0x500 = 1280
   0x4C, 0x13, // RSVD  => ??
   0x4B, 0x36, // RSVD  => ??
   0x3D, 0x3C, // RENDL => 
   0x3E, 0x03, // RENDH => 
               //   REND = 0x033C = 828
   0xBD, 0xA0, // YAVG_CTRL_0 => [7:0] = yavg_winh = 160
   0xBE, 0xC8  // YAVG_CTRL_1 => [7:0] = yavg_winv = 200
};

// 1280x720 Cropped
Xuint8 ov9710_1280x720_cropped[18][2]=
{
   // 1280x720 (cropped)               
   0x17, 0x25, // HSTART => [7:0] = HSTART[10:3]
   0x18, 0xA2, // AHsize => [7:0] = AHsize[10:3]
   0x19, 0x01, // VSTART => [7:0] = VSTART[9:2]
   0x1A, 0xCA, // AVsize => [7:0] = AVsize[9:2]
   0x03, 0x0A, // REG03  => [3:2] = AVsize[1:0]
               //           [1:0] = VSTART[1:0]
               //   VSTART[9:0] = 0x006 =   6
               //   AVsize[9:0] = 0x32A = 810
   0x32, 0x07, // REG32 => [2:0] = HSTART[2:0]
               //          [5:3] = AHsize[2:0]
               //   HSTART[10:0] = 0x12F =  303 (?)
               //   AHsize[10:0] = 0x510 = 1296 (?)
   0x98, 0x00, // DSP_CTRL_2 => [7:0] = pre_out_hoff[7:0]
   0x99, 0x28, // DSP_CTRL_3 => [7:0] = pre_out_voff[7:0]
   0x9A, 0x00, // DSP_CTRL_4 => [5:4] = pre_out_voff[9:8]
               //               [2:0] = pre_out_hoff[10:8]
               //   pre_out_voff[ 9:0] = 0x000 = 0
               //   pre_out_hoff[10:0] = 0x028 = 40
   0x57, 0x00, // REG57 => [4:2] = HSIZE[2:0]
               //          [1:0] = VSIZE[1:0]
   0x58, 0xB4, // REG58 => [7:0] = VSIZE[9:2]
   0x59, 0xA0, // REG69 => [7:0] = HSIZE[10:3]
               //   VSIZE[ 9:0] = 0x2D0 =  720
               //   HSIZE[10:0] = 0x500 = 1280
   0x4C, 0x13, // RSVD  => ??
   0x4B, 0x36, // RSVD  => ??
   0x3D, 0x3C, // RENDL => 
   0x3E, 0x03, // RENDH => 
               //   REND = 0x033C = 828
   0xBD, 0xA0, // YAVG_CTRL_0 => [7:0] = yavg_winh = 160
   0xBE, 0xB4  // YAVG_CTRL_1 => [7:0] = yavg_winv = 180
};

// 640x480 Cropped
Xuint8 ov9710_640x480_cropped[18][2]=
{
   // 640x480 (cropped)               
   0x17, 0x25, // HSTART => [7:0] = HSTART[10:3]
   0x18, 0xA2, // AHsize => [7:0] = AHsize[10:3]
   0x19, 0x01, // VSTART => [7:0] = VSTART[9:2]
   0x1A, 0xCA, // AVsize => [7:0] = AVsize[9:2]
   0x03, 0x0A, // REG03  => [3:2] = AVsize[1:0]
               //           [1:0] = VSTART[1:0]
               //   VSTART[9:0] = 0x006 =   6
               //   AVsize[9:0] = 0x32A = 810
   0x32, 0x07, // REG32 => [2:0] = HSTART[2:0]
               //          [5:3] = AHsize[2:0]
               //   HSTART[10:0] = 0x12F =  303 (?)
               //   AHsize[10:0] = 0x510 = 1296 (?)
   0x98, 0x40, // DSP_CTRL_2 => [7:0] = pre_out_hoff[7:0]
   0x99, 0xA0, // DSP_CTRL_3 => [7:0] = pre_out_voff[7:0]
   0x9A, 0x01, // DSP_CTRL_4 => [5:4] = pre_out_voff[9:8]
               //               [2:0] = pre_out_hoff[10:8]
               //   pre_out_voff[ 9:0] = 0x0A0 = 160
               //   pre_out_hoff[10:0] = 0x140 = 320
   
   0x57, 0x00, // REG57 => [4:2] = HSIZE[2:0]
               //          [1:0] = VSIZE[1:0]
   0x58, 0x78, // REG58 => [7:0] = VSIZE[9:2]
   0x59, 0x50, // REG69 => [7:0] = HSIZE[10:3]
               //   VSIZE[ 9:0] = 0x1E0 = 480
               //   HSIZE[10:0] = 0x280 = 640
   0x4C, 0x13, // RSVD  => ??
   0x4B, 0x36, // RSVD  => ??
   0x3D, 0x3C, // RENDL => 
   0x3E, 0x03, // RENDH => 
               //   REND = 0x033C = 828
   0xBD, 0x50, // YAVG_CTRL_0 => [7:0] = yavg_winh =  80
   0xBE, 0x78  // YAVG_CTRL_1 => [7:0] = yavg_winv = 120
};

////////////////////////////////////////////////////////////////////////
// PCLK Configuration (with respect to XCLK)
////////////////////////////////////////////////////////////////////////

// Generate 40MHz PCLK from 12MHz XCLK (ie. 30 Fps)
Xuint8 ov9710_xclk12_pclk40[3][2]=
{
   // Clock (Fin=12MHz, Fout=40MHz => 30Fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x19, // CLK1 = 12.0000 MHz / 1 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 25) = 84.0000 MHz
   0x5D, 0x00, // CLK3 = 84.0000 MHz / (0 + 1) = 84.0000 MHz
               // [5:4] = Output drive capability control = 0 (1x)
   0x11, 0x00  // SYSCLK = 84.0000 MHz / ((0 + 1) * 2) = 42.0000 MHz
};

// Generate 32MHz PCLK from 12MHz XCLK (ie. 24 Fps)
Xuint8 ov9710_xclk12_pclk32[3][2]=
{
   // Clock (Fin=12MHz, Fout=32MHz => 24Fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x18, // CLK1 = 12.0000 MHz / 1 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 24) = 64.0000 MHz
   0x5D, 0x00, // CLK3 = 64.0000 MHz / (0 + 1) = 64.0000 MHz
   0x11, 0x00  // SYSCLK = 64.0000 MHz / ((0 + 1) * 2) = 32.0000 MHz
};

// Generate 20MHz PCLK from 12MHz XCLK (ie. 15 Fps)
Xuint8 ov9710_xclk12_pclk20[3][2]=
{
   // Clock (Fin=12MHz, Fout=20MHz => 15Fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x19, // CLK1 = 12.0000 MHz / 1 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 25) = 84.0000 MHz
   0x5D, 0x00, // CLK3 = 84.0000 MHz / (0 + 1) = 84.0000 MHz
   0x11, 0x01  // SYSCLK = 84.0000 MHz / ((1 + 1) * 2) = 21.0000 MHz
};

// Generate 40MHz PCLK from 24MHz XCLK (ie. 30 Fps)
Xuint8 ov9710_xclk24_pclk40[3][2]=
{
   // Clock (Fin=24MHz, Fout=40MHz => 30Fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x59, // CLK1 = 24.0000 MHz / 2 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 25) = 84.0000 MHz
   0x5D, 0x00, // CLK3 = 84.0000 MHz / (0 + 1) = 84.0000 MHz
   0x11, 0x00  // SYSCLK = 84.0000 MHz / ((0 + 1) * 2) = 42.0000 MHz
};

// Generate 36MHz PCLK from 24MHz XCLK (ie. 26 Fps)
Xuint8 ov9710_xclk24_pclk36[3][2]=
{
   // Clock (Fin=24MHz, Fout=36MHz => 26Fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x5A, // CLK1 = 24.0000 MHz / 2 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 26) = 72.0000 MHz
   0x5D, 0x00, // CLK3 = 72.0000 MHz / (0 + 1) = 72.0000 MHz
   0x11, 0x00  // SYSCLK = 72.0000 MHz / ((0 + 1) * 2) = 36.0000 MHz
};

// Generate 21MHz PCLK from 24MHz XCLK (ie. 15 Fps)
Xuint8 ov9710_xclk24_pclk21[3][2]=
{
   // Clock (Fin=24MHz, Fout=18MHz => 13fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x59, // CLK1 = 24.0000 MHz / 2 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 25) = 84.0000 MHz
   0x5D, 0x00, // CLK3 = 84.0000 MHz / (0 + 1) = 84.0000 MHz
   0x11, 0x01  // SYSCLK = 84.0000 MHz / ((1 + 1) * 2) = 21.0000 MHz
};

// OV9710 configuration for 720P resolution
#define OV9710_CROP_720P_QTY 51
static Xuint8 ov9710_crop_720p[OV9710_CROP_720P_QTY][2]=
{
   // Reset
   0x12, 0x80, // COM7    [7] SRST : soft reset => 1
   
   // Core Settings
   0x1E, 0x07, // COM11 [7:0] Reserved : ??
   0x5F, 0x18, // RSVD  [7:0] Reserved : ??
   0x69, 0x04, // RSVD  [7:0] Reserved : ??
   0x65, 0x2A, // RSVD  [7:0] Reserved : ??
   0x68, 0x0A, // RSVD  [7:0] Reserved : ??
   0x39, 0x28, // RSVD  [7:0] Reserved : ??
   0x4D, 0x90, // RSVD  [7:0] Reserved : ??
   0xC1, 0x80, // YAVG_CTRL_4   [7] yavg_win_man = 1
               //             [5:4] yavg_winofv[ 9:8] = 0
               //             [2:0] yavg_winofv[10:8] = 0
   0x0C, 0x30, // COM3  [7:1] Reserved : ??
               //         [0] Single Frame Output
   
   // DSP
   0x96, 0xF1, // DSP_CTRL_0   [7] black_en    : 1
               //              [6] white_en    : 1
               //              [5] awbg_en     : 1
               //              [4] awb_en      : 1
               //              [3] lenc_en     : 0
               //              [2] lenc_det_en : 0
               //              [1] rsvd
               //              [0] isp_en      : 1
   0xBC, 0x68, // WBC_CTRL_0 [7:0] Reserved    : ??

   // Resolution and Format
   0x12, 0x00,
   0x3B, 0x00, // DSP downsample
   0x97, 0x80, //   [7] smph_mean
               //   [6] reserved
               // [5:5] smph_drop
               
   // Digital Video Port Control
   0xC2, 0x81, // DVP_CTRL_00 [7:6] VSYNC options : 2 = vsync3
               //               [5] pclk_gate_en  : 0
               //               [4] vsync_gate    : 0
               //               [3] vsync3_w_sel  : 0
               //               [2] pclk_pol      : 0
               //               [1] href_pol      : 0
               //               [0] vsync_pol     : 1 (VSYNC=0 is frame blanking)

#if 1
   // Test Pattern (off)
   0x97, 0x00, // DSP_CTRL_1   [7] smph_mean   : 0
               //            [6:4] rsvd
               //              [3] bar_en      : 1
               //              [2] sht_neg     : 0
               //            [1:0] bar_style   : 0
#else
   // Test Pattern (on)
   0x97, 0x08, // DSP_CTRL_1   [7] smph_mean   : 0
               //            [6:4] rsvd
               //              [3] bar_en      : 1
               //              [2] sht_neg     : 0
               //            [1:0] bar_style   : 0
#endif

#if 0 
   // 1280x800
   0x17, 0x25, // HSTART => [7:0] = HSTART[10:3]
   0x18, 0xA2, // AHsize => [7:0] = AHsize[10:3]
   0x19, 0x01, // VSTART => [7:0] = VSTART[9:2]
   0x1A, 0xCA, // AVsize => [7:0] = AVsize[9:2]
   0x03, 0x0A, // REG03  => [3:2] = AVsize[1:0]
               //           [1:0] = VSTART[1:0]
               //   VSTART[9:0] = 0x006 =   6
               //   AVsize[9:0] = 0x32A = 810
   0x32, 0x07, // REG32  => [2:0] = HSTART[2:0]
               //           [5:3] = AHsize[2:0]
               //   HSTART[10:0] = 0x12F =  303 (?)
               //   AHsize[10:0] = 0x510 = 1296 (?)
   0x98, 0x00, // DSP_CTRL_2 => [7:0] = pre_out_hoff[7:0]
   0x99, 0x00, // DSP_CTRL_3 => [7:0] = pre_out_voff[7:0]
   0x9A, 0x00, // DSP_CTRL_4 => [5:4] = pre_out_voff[9:8]
               //               [2:0] = pre_out_hoff[10:8]
               //   pre_out_voff[ 9:0] = 0x000 = 0
               //   pre_out_hoff[10:0] = 0x000 = 0
   
   0x57, 0x00, // REG57 => [4:2] = HSIZE[2:0]
               //          [1:0] = VSIZE[1:0]
   0x58, 0xC8, // REG58 => [7:0] = VSIZE[9:2]
   0x59, 0xA0, // REG69 => [7:0] = HSIZE[10:3]
               //   VSIZE[ 9:0] = 0x320 =  800
               //   HSIZE[10:0] = 0x500 = 1280
   0x4C, 0x13, // RSVD  => ??
   0x4B, 0x36, // RSVD  => ??
   0x3D, 0x3C, // RENDL => 
   0x3E, 0x03, // RENDH => 
               //   REND = 0x033C = 828
   0xBD, 0xA0, // YAVG_CTRL_0 => [7:0] = yavg_winh = 160
   0xBE, 0xC8, // YAVG_CTRL_1 => [7:0] = yavg_winv = 200
#elif 1
   // 1280x720 (cropped)               
   0x17, 0x25, // HSTART => [7:0] = HSTART[10:3]
   0x18, 0xA2, // AHsize => [7:0] = AHsize[10:3]
   0x19, 0x01, // VSTART => [7:0] = VSTART[9:2]
   0x1A, 0xCA, // AVsize => [7:0] = AVsize[9:2]
   0x03, 0x0A, // REG03  => [3:2] = AVsize[1:0]
               //           [1:0] = VSTART[1:0]
               //   VSTART[9:0] = 0x006 =   6
               //   AVsize[9:0] = 0x32A = 810
   0x32, 0x07, // REG32 => [2:0] = HSTART[2:0]
               //          [5:3] = AHsize[2:0]
               //   HSTART[10:0] = 0x12F =  303 (?)
               //   AHsize[10:0] = 0x510 = 1296 (?)
   0x98, 0x00, // DSP_CTRL_2 => [7:0] = pre_out_hoff[7:0]
   0x99, 0x28, // DSP_CTRL_3 => [7:0] = pre_out_voff[7:0]
   0x9A, 0x00, // DSP_CTRL_4 => [5:4] = pre_out_voff[9:8]
               //               [2:0] = pre_out_hoff[10:8]
               //   pre_out_voff[ 9:0] = 0x000 = 0
               //   pre_out_hoff[10:0] = 0x028 = 40
   0x57, 0x00, // REG57 => [4:2] = HSIZE[2:0]
               //          [1:0] = VSIZE[1:0]
   0x58, 0xB4, // REG58 => [7:0] = VSIZE[9:2]
   0x59, 0xA0, // REG69 => [7:0] = HSIZE[10:3]
               //   VSIZE[ 9:0] = 0x2D0 =  720
               //   HSIZE[10:0] = 0x500 = 1280
   0x4C, 0x13, // RSVD  => ??
   0x4B, 0x36, // RSVD  => ??
   0x3D, 0x3C, // RENDL => 
   0x3E, 0x03, // RENDH => 
               //   REND = 0x033C = 828
   0xBD, 0xA0, // YAVG_CTRL_0 => [7:0] = yavg_winh = 160
   0xBE, 0xB4, // YAVG_CTRL_1 => [7:0] = yavg_winv = 180
#elif 0
   // 640x480 (cropped)               
   0x17, 0x25, // HSTART => [7:0] = HSTART[10:3]
   0x18, 0xA2, // AHsize => [7:0] = AHsize[10:3]
   0x19, 0x01, // VSTART => [7:0] = VSTART[9:2]
   0x1A, 0xCA, // AVsize => [7:0] = AVsize[9:2]
   0x03, 0x0A, // REG03  => [3:2] = AVsize[1:0]
               //           [1:0] = VSTART[1:0]
               //   VSTART[9:0] = 0x006 =   6
               //   AVsize[9:0] = 0x32A = 810
   0x32, 0x07, // REG32 => [2:0] = HSTART[2:0]
               //          [5:3] = AHsize[2:0]
               //   HSTART[10:0] = 0x12F =  303 (?)
               //   AHsize[10:0] = 0x510 = 1296 (?)
   0x98, 0x40, // DSP_CTRL_2 => [7:0] = pre_out_hoff[7:0]
   0x99, 0xA0, // DSP_CTRL_3 => [7:0] = pre_out_voff[7:0]
   0x9A, 0x01, // DSP_CTRL_4 => [5:4] = pre_out_voff[9:8]
               //               [2:0] = pre_out_hoff[10:8]
               //   pre_out_voff[ 9:0] = 0x0A0 = 160
               //   pre_out_hoff[10:0] = 0x140 = 320
   
   0x57, 0x00, // REG57 => [4:2] = HSIZE[2:0]
               //          [1:0] = VSIZE[1:0]
   0x58, 0x78, // REG58 => [7:0] = VSIZE[9:2]
   0x59, 0x50, // REG69 => [7:0] = HSIZE[10:3]
               //   VSIZE[ 9:0] = 0x1E0 = 480
               //   HSIZE[10:0] = 0x280 = 640
   0x4C, 0x13, // RSVD  => ??
   0x4B, 0x36, // RSVD  => ??
   0x3D, 0x3C, // RENDL => 
   0x3E, 0x03, // RENDH => 
               //   REND = 0x033C = 828
   0xBD, 0x50, // YAVG_CTRL_0 => [7:0] = yavg_winh =  80
   0xBE, 0x78, // YAVG_CTRL_1 => [7:0] = yavg_winv = 120
#endif

   // YAVG
   0x4E, 0x55, // average
   0x4F, 0x55, // average
   0x50, 0x55, // average
   0x51, 0x55, // average
   
   0x24, 0x55, // exposure window
   0x25, 0x40,
   0x26, 0xA1,

#if 1
   // Clock (Fin=12MHz, Fout=40MHz => 30Fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x19, // CLK1 = 12.0000 MHz / 1 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 25) = 84.0000 MHz
   0x5D, 0x00, // CLK3 = 84.0000 MHz / (0 + 1) = 84.0000 MHz
               // [5:4] = Output drive capability control = 0 (1x)
   0x11, 0x00, // SYSCLK = 84.0000 MHz / ((0 + 1) * 2) = 42.0000 MHz
#elif 0
   // Clock (Fin=12MHz, Fout=32MHz => 24Fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x18, // CLK1 = 12.0000 MHz / 1 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 24) = 64.0000 MHz
   0x5D, 0x00, // CLK3 = 64.0000 MHz / (0 + 1) = 64.0000 MHz
   0x11, 0x00, // SYSCLK = 64.0000 MHz / ((0 + 1) * 2) = 32.0000 MHz
#elif 0
   // Clock (Fin=12MHz, Fout=20MHz => 15Fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x19, // CLK1 = 12.0000 MHz / 1 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 25) = 84.0000 MHz
   0x5D, 0x00, // CLK3 = 84.0000 MHz / (0 + 1) = 84.0000 MHz
   0x11, 0x01, // SYSCLK = 84.0000 MHz / ((1 + 1) * 2) = 21.0000 MHz
#elif 0
   // Clock (Fin=24MHz, Fout=40MHz => 30Fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x59, // CLK1 = 24.0000 MHz / 2 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 25) = 84.0000 MHz
   0x5D, 0x00, // CLK3 = 84.0000 MHz / (0 + 1) = 84.0000 MHz
   0x11, 0x00, // SYSCLK = 84.0000 MHz / ((0 + 1) * 2) = 42.0000 MHz
#elif 0
   // Clock (Fin=24MHz, Fout=36MHz => 26Fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x5A, // CLK1 = 24.0000 MHz / 2 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 26) = 72.0000 MHz
   0x5D, 0x00, // CLK3 = 72.0000 MHz / (0 + 1) = 72.0000 MHz
   0x11, 0x00, // SYSCLK = 72.0000 MHz / ((0 + 1) * 2) = 36.0000 MHz
#elif 0
   // Clock (Fin=24MHz, Fout=18MHz => 13fps)
   //    CLK1 = XCLK / REG5C[6:5]
   //    CLK2 = CLK1 * (32 - REG5C[4:0])
   //    CLK3 = CLK2 / (REG5D[3:2] + 1)
   //    SYSCLK = CLK3 / ((REG11[5:0] + 1) * 2)
   0x5C, 0x59, // CLK1 = 24.0000 MHz / 2 = 12.0000 MHz
               // CLK2 = 12.0000 MHz * (32 - 25) = 84.0000 MHz
   0x5D, 0x00, // CLK3 = 84.0000 MHz / (0 + 1) = 84.0000 MHz
   0x11, 0x01, // SYSCLK = 84.0000 MHz / ((1 + 1) * 2) = 21.0000 MHz
#endif

   // Horizontal Tp Counter End Point
   0x2B, 0x06,
   0x2A, 0x9C,
   
   // Automatically Inserted Dummy Lines in Night Mode
   0x2D, 0x00,
   0x2E, 0x00,
   
   // General,
   0x13, 0x85,
   0x14, 0x40  // Gain ceiling 8X
               
};


#endif // __OV9710_CONFIG_H__
