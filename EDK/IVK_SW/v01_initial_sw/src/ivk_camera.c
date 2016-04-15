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
// Create Date:         Jan 18, 2010
// Design Name:         IVK_CAMERA
// Module Name:         ivk_camera.c
// Project Name:        IVK_CAMERA
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-IMAGEOV
//
// Tool versions:       ISE 11.4
//
// Description:         IVK Camera Configuration Routines
//                      The OV9715 image sensor is configure for 1280x721 to account
//                      for a line being dropped in the fmc_imageov_camera_in PCORE.
//
//                      The OV9715 image sensor is configured to generate CCIR656 codes.
//                      - VREF is used as VSYNC
//                      - HREF is used as HSYNC
//                      - The following signals are generated from the CCIR656 codes:
//                         - ACTIVE_VIDEO (DE)
//                         - HBLANK
//                         - VBLANK
//
//                      Observations with ChipScope reveils that the first active line
//                      has unusual CCIR656 codes, which results in line 1 being dropped.
//                      
//                      Case             Code  Y[9:0] => 1  F  V  H P3 P2 P1 P0 -- --
//                      =============================================================
//                      ACTIVE LINE 1     FS   0x2AC     1  0  1  0  1  0  1  1  0  0
//                                        LE   0x274     1  0  0  1  1  1  0  1  0  0
//                      -------------------------------------------------------------
//                      ACTIVE LINES 2-N  LS   0x200     1  0  0  0  0  0  0  0  0  0
//                                        LE   0x274     1  0  0  1  1  1  0  1  0  0
//                      -------------------------------------------------------------
//                      INACTIVE LINES    FS   0x2AC     1  0  1  0  1  0  1  1  0  0
//                                        FE   0x2D8     1  0  1  1  0  1  1  0  0  0
//                      =============================================================
//
// Dependencies:        
//
// Revision:            Jan 18, 2010: 1.00 Initial version
//                      Feb 11, 2010: 1.01 Add ivk_camera_flip_image routine
//                      Feb 16, 2010: 1.02 Add ivk_camera_auto_exposure_config
//                                         and ivk_camera_auto_gain_config
//                      Mar 17, 2010: 1.03 Configure OV9715 for 1280x721
//                      Apr 08, 2010: 1.04 Place extra line in 1280x721 config before
//                                         desired 1280x720 region (instead of after).
//                                         This line will get dropped by FPGA logic
//                      Apr 15, 2010: 1.05 Add control for black level calibration (BLC)
//                      Apr 27, 2010: 1.06 Add control for lens correction, AWB
//
//----------------------------------------------------------------

#include "fmc_imageov.h"
extern fmc_imageov_t fmc_imageov;

#include "ov9710_config.h"

#include "ivk_camera.h"


#define OV9710_VSYNC_POLARITY_QTY 1
static Xuint8 ov9710_vsync_negative[OV9710_VSYNC_POLARITY_QTY][2]=
{
   // Digital Video Port Control
   0xC2, 0x81, // DVP_CTRL_00 [7:6] VSYNC options : 2 = vsync3
               //               [5] pclk_gate_en  : 0
               //               [4] vsync_gate    : 0
               //               [3] vsync3_w_sel  : 0
               //               [2] pclk_pol      : 0
               //               [1] href_pol      : 0
               //               [0] vsync_pol     : 1 (VSYNC=0 is frame blanking)
};
static Xuint8 ov9710_vsync_positive[OV9710_VSYNC_POLARITY_QTY][2]=
{
   // Digital Video Port Control
   0xC2, 0x80, // DVP_CTRL_00 [7:6] VSYNC options : 2 = vsync3
               //               [5] pclk_gate_en  : 0
               //               [4] vsync_gate    : 0
               //               [3] vsync3_w_sel  : 0
               //               [2] pclk_pol      : 0
               //               [1] href_pol      : 0
               //               [0] vsync_pol     : 0 (VSYNC=1 is frame blanking)
};

#define OV9710_DVP_CONFIG_QTY 3
static Xuint8 ov9710_dvp_config_default[OV9710_DVP_CONFIG_QTY][2]=
{
   // Digital Video Port Control
   0xC2, 0x80, // DVP_CTRL_00 [7:6] VSYNC options : 2 = vsync3
               //               [5] pclk_gate_en  : 0
               //               [4] vsync_gate    : 0
               //               [3] vsync3_w_sel  : 0
               //               [2] pclk_pol      : 0
               //               [1] href_pol      : 0
               //               [0] vsync_pol     : 0 (VSYNC=1 is frame blanking)
   0xCB, 0x22, // DVP_CTRL_09   [7] soft_rst_en   : 0
               //             [6:5] chg_sel       : 01 (select auto detect chg and man chg)
               //               [4] hsync_en      : 0 (disable HSYNC mode)
               //               [3] hsync_dvp_en  : 0
               //               [2] hsync_1st_en  : 0
               //             [1:0] line_len_sel  : 10 (select line_length_auto)
   0xC3, 0x21  // DVP_CTRL_01   [7] ccir656_en    : 0 (CCIR656 disabled)
               //               [6] sync_code_sel : 0 (auto generate sync code for CCIR656)
               //               [5] blk_656       : 1 (CCIR656 data is 0x000 when blanking)
               //               [4] eav_first     : 0 (CCIR656 DOES NOT sends EAV first)
               //             [3:1] dvp_data_seq  : 000 (Y9,Y8,Y7,Y6,Y5,Y4,Y3,Y2,Y2,Y1,Y0)
               //               [0] chg_flag      : 1 (update)
};
static Xuint8 ov9710_dvp_config_ccir656[OV9710_DVP_CONFIG_QTY][2]=
{
   // Digital Video Port Control
   0xC2, 0x00, // DVP_CTRL_00 [7:6] VSYNC options : 0 = vsync_old
               //               [5] pclk_gate_en  : 0
               //               [4] vsync_gate    : 0
               //               [3] vsync3_w_sel  : 0
               //               [2] pclk_pol      : 0
               //               [1] href_pol      : 0
               //               [0] vsync_pol     : 0 (VSYNC=1 is frame blanking)
   0xCB, 0x32, // DVP_CTRL_09   [7] soft_rst_en   : 0
               //             [6:5] chg_sel       : 01 (select auto detect chg and man chg)
               //               [4] hsync_en      : 1 (enable HSYNC mode)
               //               [3] hsync_dvp_en  : 0
               //               [2] hsync_1st_en  : 0
               //             [1:0] line_len_sel  : 10 (select line_length_auto)
   0xC3, 0xA1  // DVP_CTRL_01   [7] ccir656_en    : 1 (CCIR656 enabled)
               //               [6] sync_code_sel : 0 (auto generate sync code for CCIR656)
               //               [5] blk_656       : 1 (CCIR656 data is 0x000 when blanking)
               //               [4] eav_first     : 0 (CCIR656 DOES NOT sends EAV first)
               //             [3:1] dvp_data_seq  : 000 (Y9,Y8,Y7,Y6,Y5,Y4,Y3,Y2,Y2,Y1,Y0)
               //               [0] chg_flag      : 1 (update)
};

// 1280x721 Cropped
// - extra line is placed BEFORE the desired 1280x720 region
// - this extra line will be dropped by the FPGA logic (fmc_imageov_camera_in)
Xuint8 ov9710_1280x721_cropped[18][2]=
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
   0x99, 0x27, // DSP_CTRL_3 => [7:0] = pre_out_voff[7:0]
   0x9A, 0x00, // DSP_CTRL_4 => [5:4] = pre_out_voff[9:8]
               //               [2:0] = pre_out_hoff[10:8]
               //   pre_out_hoff[10:0] = 0x000 = 0
               //   pre_out_voff[ 9:0] = 0x027 = 39 (ie. 40 - 1)
   0x57, 0x01, // REG57 => [4:2] = HSIZE[2:0]
               //          [1:0] = VSIZE[1:0]
   0x58, 0xB4, // REG58 => [7:0] = VSIZE[9:2]
   0x59, 0xA0, // REG69 => [7:0] = HSIZE[10:3]
               //   VSIZE[ 9:0] = 0x2D1 =  721
               //   HSIZE[10:0] = 0x500 = 1280
   0x4C, 0x13, // RSVD  => ??
   0x4B, 0x36, // RSVD  => ??
   0x3D, 0x3C, // RENDL => 
   0x3E, 0x03, // RENDH => 
               //   REND = 0x033C = 828
   0xBD, 0xA0, // YAVG_CTRL_0 => [7:0] = yavg_winh = 160
   0xBE, 0xB4  // YAVG_CTRL_1 => [7:0] = yavg_winv = 180
};

// 640x481 Cropped
// - extra line is placed BEFORE the desired 1280x720 region
// - this extra line will be dropped by the FPGA logic (fmc_imageov_camera_in)
Xuint8 ov9710_640x481_cropped[18][2]=
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
   0x99, 0x9F, // DSP_CTRL_3 => [7:0] = pre_out_voff[7:0]
   0x9A, 0x01, // DSP_CTRL_4 => [5:4] = pre_out_voff[9:8]
               //               [2:0] = pre_out_hoff[10:8]
               //   pre_out_hoff[10:0] = 0x140 = 320
               //   pre_out_voff[ 9:0] = 0x09F = 159 (ie. 160 - 1)
   
   0x57, 0x01, // REG57 => [4:2] = HSIZE[2:0]
               //          [1:0] = VSIZE[1:0]
   0x58, 0x78, // REG58 => [7:0] = VSIZE[9:2]
   0x59, 0x50, // REG69 => [7:0] = HSIZE[10:3]
               //   VSIZE[ 9:0] = 0x1E0 = 481
               //   HSIZE[10:0] = 0x280 = 640
   0x4C, 0x13, // RSVD  => ??
   0x4B, 0x36, // RSVD  => ??
   0x3D, 0x3C, // RENDL => 
   0x3E, 0x03, // RENDH => 
               //   REND = 0x033C = 828
   0xBD, 0x50, // YAVG_CTRL_0 => [7:0] = yavg_winh =  80
   0xBE, 0x78  // YAVG_CTRL_1 => [7:0] = yavg_winv = 120
};

Xuint8 ov9710_undocumented[1][2]=
{
   0x6D, 0x02  // This register is not document,
               //    but clearing bit [7] removes some vertical artifacts
};

/******************************************************************************
* This function initializes the operating mode of camera port #1.
*
* @param    mode contains the selected mode that the camera port is to be 
*           programmed.
*
* @return   None.
*
* @note     None.
*
******************************************************************************/
void ivk_camera1_config(Xint32 mode)
{
   if ( mode == OV9710_CONFIG_720P30)
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_soft_reset         , sizeof(ov9710_soft_reset         )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_autoadjustments_off, sizeof(ov9710_autoadjustments_on )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_xclk12_pclk40      , sizeof(ov9710_xclk12_pclk40      )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_1280x721_cropped   , sizeof(ov9710_1280x721_cropped   )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_flip_none          , sizeof(ov9710_flip_none          )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_undocumented       , sizeof(ov9710_undocumented       )>>1 );
   }
   if ( mode == OV9710_CONFIG_VGAP30)
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_soft_reset         , sizeof(ov9710_soft_reset         )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_autoadjustments_off, sizeof(ov9710_autoadjustments_on )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_xclk12_pclk40      , sizeof(ov9710_xclk12_pclk40      )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_640x481_cropped    , sizeof(ov9710_640x481_cropped    )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_flip_none          , sizeof(ov9710_flip_none          )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_undocumented       , sizeof(ov9710_undocumented       )>>1 );
   }
   fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_dvp_config_ccir656 , sizeof(ov9710_dvp_config_ccir656 )>>1 );
}


/******************************************************************************
* This function initializes the operating mode of camera port #2.
*
* @param    mode contains the selected mode that the camera port is to be 
*           programmed.
*
* @return   None.
*
* @note     None.
*
******************************************************************************/
void ivk_camera2_config(Xint32 mode)
{
   if ( mode == OV9710_CONFIG_720P30)
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_soft_reset         , sizeof(ov9710_soft_reset         )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_autoadjustments_off, sizeof(ov9710_autoadjustments_on )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_xclk12_pclk40      , sizeof(ov9710_xclk12_pclk40      )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_1280x721_cropped   , sizeof(ov9710_1280x721_cropped   )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_flip_none          , sizeof(ov9710_flip_none          )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_undocumented       , sizeof(ov9710_undocumented       )>>1 );
   }
   if ( mode == OV9710_CONFIG_VGAP30)
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_soft_reset         , sizeof(ov9710_soft_reset         )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_autoadjustments_off, sizeof(ov9710_autoadjustments_on )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_xclk12_pclk40      , sizeof(ov9710_xclk12_pclk40      )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_640x481_cropped    , sizeof(ov9710_640x481_cropped    )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_flip_none          , sizeof(ov9710_flip_none          )>>1 );
      fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_undocumented       , sizeof(ov9710_undocumented       )>>1 );
   }
   fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_dvp_config_ccir656 , sizeof(ov9710_dvp_config_ccir656 )>>1 );
}


/*********************************************************************
**
* This function checks to see if a camera is connected to the specified
* Camera port.
*
* @param    camera port to check.
*            1 = Camera 1
*            2 = Camera 2
*
* @param    message specifies whether or not to print the warning message.
*             1 - print message
*             0 - do not print message
*
* @return   I2C address of the camera
*            I2C address of the camera = Source Present
*            0 = Source Not Present
*
* @note None.
*
*********************************************************************/
Xuint8 ivk_camera_present(Xint32 camera, Xint32 message)
{
   Xuint8 iic_data;
   Xuint8 num_bytes;
   
   if ( camera == 1 )
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
   }
   else
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
   }

   // Check for presence of OV9710 image sensor
   num_bytes = fmc_imageov.pIIC->fpIicRead( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0, &iic_data, 1); 
   if ( num_bytes > 0 )
   {
      return 1;
   }
   else
   {
      return 0;
   }
   
}


/*********************************************************************
*
* This function configures the test pattern that is displayed by the camera
*
* @param The camera port to check.
* 1 = Camera 1
* 2 = Camera 2
*
* @param The test pattern to configure the camera to.
* 0 = None
* 1 = Color Bars (uniform intensity)
* 2 = Color Bars (varying intensity)
* 3 = Color Bars (varying & uniform intensity)
* 4 = Color Bars (uniform intensity)
*
* @return the success of the result
* 1 = successful
* 0 = fail
*
* @note None.
*
*********************************************************************/
Xint32 ivk_camera_test_pattern_config(Xint32 camera, Xint32 mode)
{
   if ( camera == 1 )
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
   }
   else
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
   }

   switch (mode)
   {
      case 0:
         fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_testpattern_off, sizeof(ov9710_testpattern_off)>>1 );
         break;
      case 1:
         fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_testpattern_on1, sizeof(ov9710_testpattern_on1)>>1 );
         break;
      case 2:
         fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_testpattern_on2, sizeof(ov9710_testpattern_on2)>>1 );
         break;
      case 3:
         fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_testpattern_on3, sizeof(ov9710_testpattern_on3)>>1 );
         break;
      case 4:
         fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_testpattern_on4, sizeof(ov9710_testpattern_on4)>>1 );
         break;
   }
}

/*********************************************************************
*
* This function configures the image sensor for vertical/horizontal flip
*
* @param The camera port to check.
* 1 = Camera 1
* 2 = Camera 2
*
* @param The vertical flip mode.
* 0 = None
* 1 = Vertical flip
*
* @param The horizontal flip mode.
* 0 = None
* 1 = Horizontal flip
*
* @return the success of the result
* 1 = successful
* 0 = fail
*
* @note None.
*
*********************************************************************/
Xint32 ivk_camera_flip_image(Xint32 camera, Xint32 vflip, Xint32 hflip)
{
   Xint32 mode;
   
   if ( camera == 1 )
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
   }
   else
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
   }

   mode = 0;
   if ( vflip ) mode |= 0x10;
   if ( hflip ) mode |= 0x01;
   
   switch (mode)
   {
      case 0x00:
         fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_flip_none, sizeof(ov9710_flip_none)>>1 );
         break;
      case 0x10:
         fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_flip_vertical, sizeof(ov9710_flip_vertical)>>1 );
         break;
      case 0x01:
         fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_flip_horizontal, sizeof(ov9710_flip_horizontal)>>1 );
         break;
      case 0x11:
         fmc_imageov_iic_config( &fmc_imageov, OV9710_IIC_ADDR, ov9710_flip_both, sizeof(ov9710_flip_both)>>1 );
         break;
   }
}


/*********************************************************************
*
* This function configures the automatic exposure control of the camera
*
* @param The camera to configure.
* 1 = Camera 1
* 2 = Camera 2
*
* @param The auto exposure control
* 1 = on
* 0 = off
*
* @return the success of the result
* 1 = successful
* 0 = fail
*
* @note None.
*
*********************************************************************/
Xint32 ivk_camera_auto_exposure_config(Xint32 camera, Xint32 mode)
{
   Xuint8 iic_data;

   if ( camera == 1 )
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
   }
   else
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
   }

   fmc_imageov.pIIC->fpIicRead( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x13, &iic_data, 1); 
   //xil_printf( "OV9710[0x13] => 0x%02X\r\n", iic_data );
   
   if (mode)
   {
      iic_data |=  0x01; // [0] Exposure Control = 1 (AUTO)
   }
   else
   {
      iic_data &= ~0x01; // [0] Exposure Control = 0 (MANUAL)
   }
   
   //xil_printf( "OV9710[0x13] <= 0x%02X\r\n", iic_data );
   fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x13, &iic_data, 1); 
   
   return 1;
}


/*********************************************************************
*
* This function configures the automatic gain control of the camera
*
* @param The camera to configure.
* 1 = Camera 1
* 2 = Camera 2
*
* @param The auto gain control
* 1 = on
* 0 = off
*
* @return the success of the result
* 1 = successful
* 0 = fail
*
* @note None.
*
*********************************************************************/
Xint32 ivk_camera_auto_gain_config(Xint32 camera, Xint32 mode)
{
   Xuint8 iic_data;
   
   if ( camera == 1 )
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
   }
   else
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
   }

   fmc_imageov.pIIC->fpIicRead( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x13, &iic_data, 1); 
   //xil_printf( "OV9710[0x13] => 0x%02X\r\n", iic_data );
   
   if (mode)
   {
      iic_data |=  0x04; // [2] AGC Control = 1 (AUTO)
   }
   else
   {
      iic_data &= ~0x04; // [2] AGC Control = 0 (MANUAL)
   }

   //xil_printf( "OV9710[0x13] <= 0x%02X\r\n", iic_data );
   fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x13, &iic_data, 1); 
   
   return 1;
}


/*********************************************************************
*
* This function configures the black level calibration (BLC) mode of the camera
*
* @param The camera port to check.
* 1 = Camera 1
* 2 = Camera 2
*
* @param The BLC mode.
* 0 = Electrical BLC
* 1 = Optical BLC
*
* @return the success of the result
* 1 = successful
* 0 = fail
*
* @note None.
*
*********************************************************************/
Xint32 ivk_camera_blc_config(Xint32 camera, Xint32 blc)
{
   Xuint8 iic_data;
   
   if ( camera == 1 )
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
   }
   else
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
   }

   fmc_imageov.pIIC->fpIicRead( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x0E, &iic_data, 1); 
   //xil_printf( "OV9710[0x0E] => 0x%02X\r\n", iic_data );
   
   if (blc)
   {
      iic_data |=  0x40; // [6] BLC line selection = 1 (Optical BLC)
   }
   else
   {
      iic_data &= ~0x40; // [6] BLC line selection = 0 (Electrical BLC)
   }

   //xil_printf( "OV9710[0x0E] <= 0x%02X\r\n", iic_data );
   fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x0E, &iic_data, 1); 
   
   return 1;
}

/*********************************************************************
*
* This function configures the lens correction (LENC) mode of the camera
*
* @param The camera port to check.
* 1 = Camera 1
* 2 = Camera 2
*
* @param The LENC mode.
* 0 = disabled
* 1 = enabled (automatic)
*
* @return the success of the result
* 1 = successful
* 0 = fail
*
* @note None.
*
*********************************************************************/
Xint32 ivk_camera_lenc_config(Xint32 camera, Xint32 lenc)
{
   Xuint8 iic_data;
   
   if ( camera == 1 )
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
   }
   else
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
   }

   fmc_imageov.pIIC->fpIicRead( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x96, &iic_data, 1); 
   //xil_printf( "OV9710[0x0E] => 0x%02X\r\n", iic_data );
   
   if (lenc)
   {
      iic_data |=  0x08; // [3] LENC function enable = 1 (enabled)
   }
   else
   {
      iic_data &= ~0x08; // [3] LENC function enable = 0 (disabled)
   }

   //xil_printf( "OV9710[0x0E] <= 0x%02X\r\n", iic_data );
   fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x96, &iic_data, 1); 
   
   return 1;
}

/*********************************************************************
*
* This function configures the auto white balance (AWB) mode of the camera
*
* @param The camera port to check.
* 1 = Camera 1
* 2 = Camera 2
*
* @param The AWB mode.
* 0 = disabled
* 1 = enabled (automatic)
*
* @return the success of the result
* 1 = successful
* 0 = fail
*
* @note None.
*
*********************************************************************/
Xint32 ivk_camera_awb_config(Xint32 camera, Xint32 awb)
{
   Xuint8 iic_data;
   
   if ( camera == 1 )
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
   }
   else
   {
      fmc_imageov_iic_mux( &fmc_imageov, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
   }

   if (awb)
   {
      fmc_imageov.pIIC->fpIicRead( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x38, &iic_data, 1); 
      iic_data |= 0x10; // COM25[4] AWB gain mode = 1 (automatic)
      fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x38, &iic_data, 1); 
   
      fmc_imageov.pIIC->fpIicRead( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x96, &iic_data, 1); 
      iic_data |=  0x10; // DSP_CTRL_0[4] AWB function enable = 1 (enabled)
      fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x96, &iic_data, 1); 
   }
   else
   {
      fmc_imageov.pIIC->fpIicRead( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x38, &iic_data, 1); 
      iic_data &= ~0x10; // COM25[4] AWB gain mode = 0 (manual)
      fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x38, &iic_data, 1); 
   
      fmc_imageov.pIIC->fpIicRead( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x96, &iic_data, 1); 
      iic_data &= ~0x10; // DSP_CTRL_0[4] AWB function enable = 0 (disabled)
      fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x96, &iic_data, 1); 
      
      iic_data = 0x40; // BLUE[7:0] = 0x40
      fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x01, &iic_data, 1); 
      iic_data = 0x40; // RED[7:0] = 0x40
      fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x02, &iic_data, 1); 
      iic_data = 0x00; // BRL[7:4] = 0, BRL[3:0] = 0
      fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x06, &iic_data, 1); 
      iic_data = 0x40; // GREEN[7:0] = 0x40
      fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x05, &iic_data, 1); 
      iic_data = 0x00; // BRL[7:4] = 0, GL[3:0] = 0
      fmc_imageov.pIIC->fpIicWrite( fmc_imageov.pIIC, OV9710_IIC_ADDR, 0x07, &iic_data, 1); 
   }
   
   return 1;
}

