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
// Design Name:         IVK
// Module Name:         fir_2d.h
// Project Name:        IVK
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-DVI/DP
//
// Tool versions:       ISE 11.4
//
// Description:         RGB 2D FIR Menu
//                      - based on fir_2d.h
//                      - modified as follows:
//                         - renamed vsk_* to ivk_*
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
// Filename            : fir_2d.h
// $Revision:: 3507   $: Revision of last commit
// $Date:: 2008-09-04#$: Date of last commit
// Description         : Header file of constants for RGB 2D FIR Menu
//******************************************************************************/

#ifndef __ivk_fir_2d__
#define __ivk_fir_2d__
 
#include <stdio.h>

// Located in: microblaze_0/include/
#include "xutil.h"
#include "xparameters.h"

#if defined(XPAR_SG_2D_FIR_PLBW_NUM_INSTANCES)
 #include "sg_2d_fir_plbw.h"
 #define SG_2D_FIR_PLBW_ConfigTable SG_2D_FIR_PLBW_ConfigTable
#endif

#define SG_2D_FIR_ID XPAR_SG_2D_FIR_PLBW_0_DEVICE_ID

void ivk_load_fir_2d(Xint32);

void ivk_load_fir_2d_coefficients(Xint32);
void ivk_set_fir_2d_coefficients(void);
void ivk_read_fir_2d_coefficients(Xint32);

void ivk_load_fir_2d_gain(Xint32);
void ivk_step_fir_2d_gain(Xint32);
void ivk_read_fir_2d_gain(void);

void ivk_disable_fir_2d_coef_update(void);
void ivk_enable_fir_2d_coef_update(void);

void ivk_fir_2d_main (void);

Xfloat64 UFix20_17_to_double(Xuint32);
Xuint32 double_to_UFix20_17(Xfloat64);
void print_UFix20_17(Xuint32);
 
Xint32 signExtInt(Xint32,Xint32);

#define INPUTBUFSIZE 24
void getString(Xuint8*);

#endif
