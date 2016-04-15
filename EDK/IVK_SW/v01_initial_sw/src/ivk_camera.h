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
// Module Name:         ivk_camera.h
// Project Name:        IVK_CAMERA
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-IMAGEOV
//
// Tool versions:       ISE 11.4
//
// Description:         IVK Camera Configuration Routines
//
// Dependencies:        
//
// Revision:            Jan 18, 2010: 1.00 Initial version
//                      Feb 11, 2010: 1.01 Add ivk_camera_flip_image routine
//                      Feb 16, 2010: 1.02 Add ivk_camera_auto_exposure_config
//                                         and ivk_camera_auto_gain_config
//                      Apr 15, 2010: 1.05 Add control for black level calibration (BLC)
//                      Apr 27, 2010: 1.06 Add control for lens correction, AWB
//
//----------------------------------------------------------------

#ifndef __IVK_CAMERA_H__
#define __IVK_CAMERA_H__


#include "ivk_camera.h"


#define OV9710_CONFIG_720P30  1
#define OV9710_CONFIG_VGAP30  2


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
void ivk_camera1_config(Xint32 mode);


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
void ivk_camera2_config(Xint32 mode);


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
Xuint8 ivk_camera_present(Xint32 camera, Xint32 message);


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
Xint32 ivk_camera_test_pattern_config(Xint32 camera, Xint32 mode);


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
Xint32 ivk_camera_flip_image(Xint32 camera, Xint32 vflip, Xint32 hflip);


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
Xint32 ivk_camera_auto_exposure_config(Xint32 camera, Xint32 mode);


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
Xint32 ivk_camera_auto_gain_config(Xint32 camera, Xint32 mode);


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
Xint32 ivk_camera_blc_config(Xint32 camera, Xint32 blc);

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
Xint32 ivk_camera_lenc_config(Xint32 camera, Xint32 lenc);

/*********************************************************************
*
* This function configures the auto white balance (AWB) mode of the camera
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
Xint32 ivk_camera_awb_config(Xint32 camera, Xint32 awb);

#endif // __IVK_CAMERA_H__
