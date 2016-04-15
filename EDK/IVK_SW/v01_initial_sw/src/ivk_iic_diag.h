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
// Design Name:         IVK_IIC_DIAG
// Module Name:         ivk_iic_diag.h
// Project Name:        IVK_IIC_DIAG
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-IMAGEOV
//
// Tool versions:       ISE 11.4
//
// Description:         IVK IIC Diagnostics Menu
//                      - based on vsk_iic_diag.h
//
// Dependencies:        
//
// Revision:            Jan 18, 2010: 1.00 Initial version
//
//----------------------------------------------------------------


// DISCLAIMER OF LIABILITY
// 
// This text/file contains proprietary, confidential
// information of Xilinx, Inc., is distributed under license
// from Xilinx, Inc., and may be used, copied and/or
// disclosed only pursuant to the terms of a valid license
// agreement with Xilinx, Inc. Xilinx hereby grants you a 
// license to use this text/file solely for design, simulation, 
// implementation and creation of design files limited 
// to Xilinx devices or technologies. Use with non-Xilinx 
// devices or technologies is expressly prohibited and 
// immediately terminates your license unless covered by
// a separate agreement.
//
// Xilinx is providing this design, code, or information 
// "as-is" solely for use in developing programs and 
// solutions for Xilinx devices, with no obligation on the 
// part of Xilinx to provide support. By providing this design, 
// code, or information as one possible implementation of 
// this feature, application or standard, Xilinx is making no 
// representation that this implementation is free from any 
// claims of infringement. You are responsible for 
// obtaining any rights you may require for your implementation. 
// Xilinx expressly disclaims any warranty whatsoever with 
// respect to the adequacy of the implementation, including 
// but not limited to any warranties or representations that this
// implementation is free from claims of infringement, implied 
// warranties of merchantability or fitness for a particular 
// purpose.
//
// Xilinx products are not intended for use in life support
// appliances, devices, or systems. Use in such applications is
// expressly prohibited.
//
// Any modifications that are made to the Source Code are 
// done at the user’s sole risk and will be unsupported.
//
//
// Copyright (c) 2007, 2008 Xilinx, Inc. All rights reserved.
//
// This copyright and support notice must be retained as part 
// of this text at all times. 
//
//******************************************************************************/
// Filename            : vsk_iic_diag.h
// $Revision:: 2239   $: Revision of last commit
// $Date:: 2008-05-09#$: Date of last commit
// Description         : VSK IIC Diagnostics Menu header file
//******************************************************************************/

#ifndef __IVK_IIC_DIAG_H__
#define __IVK_IIC_DIAG_H__
 
#include "xutil.h"
#include "fmc_iic.h"
#include "fmc_imageov.h"


#define MAX_IIC_DEV        6
#define IIC_DVI_OUT        0
#define IIC_CLK_GEN        1
#define IIC_FMC_MUX        2
#define IIC_CAMERA_1       3
#define IIC_CAMERA_2       4
#define IIC_EDID_DVI_OUT   5

/******************************************************************************
* This function creates a menu structure that allows the user the ability to 
*  read and write the IIC registers of the chips in the VSK in real-time.
*
* @param    pContext contains a pointer to the FMC-IMAGEOV instance's context.
*
* @return   Returns '0' when it exits successfully.
*
* @note     None.
*
******************************************************************************/
Xint32 ivk_iic_diag_main ( fmc_imageov_t *pModule );

#endif // __IVK_IIC_DIAG_H__
