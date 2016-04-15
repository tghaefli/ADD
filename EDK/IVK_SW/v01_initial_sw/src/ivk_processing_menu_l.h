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
// Design Name:         IVK_PROCESSING_MENU
// Module Name:         ivk_processing_menu_l.h
// Project Name:        IVK
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-IMAGEOV
//
// Tool versions:       ISE 11.4
//
// Description:         IVK Video Processing Menu
//                      - based on vsk_processing_menu
//                      - modified as follows:
//                         - renamed to ivk_processing_menu
//                         - vsk_camera_vop pcore is replaced by
//                            - sg_spc   (stuck pixel correction)
//                            - sg_bc    (brightness & contrast)
//                            - sg_cfa   (CFA interpolation)
//                            - sg_cc    (color correction)
//                            - sg_stats (image statistics)
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
// done at the user's sole risk and will be unsupported.
//
//
// Copyright (c) 2008 Xilinx, Inc. All rights reserved.
//
// This copyright and support notice must be retained as part 
// of this text at all times. 
//
//******************************************************************************/
// Filename            : vsk_processing_menu_l.h
// $Revision:: 3621   $: Revision of last commit
// $Date:: 2008-09-10#$: Date of last commit
// Description         : Local include file for vsk_processing_menu.c
//******************************************************************************/

#include <stdio.h>

// Located in: microblaze_0/include/
#include "xbasic_types.h"
#include "xutil.h"
#include "xparameters.h"
#include "ivk_camera_menu.h"

#include "fmc_imageov.h"

#if defined(XPAR_SG_SPC_S6_PLBW_NUM_INSTANCES)
 #include "sg_spc_s6_plbw.h"
 #define SPC_PLBW_ConfigTable SG_SPC_S6_PLBW_ConfigTable
#endif
#if defined(XPAR_SG_BC_S6_PLBW_NUM_INSTANCES)
 #include "sg_bc_s6_plbw.h"
 #define BC_PLBW_ConfigTable SG_BC_S6_PLBW_ConfigTable
#endif
#if defined(XPAR_SG_CFA_GAMMA_PLBW_NUM_INSTANCES)
 #include "sg_cfa_gamma_plbw.h"
 #define CFA_PLBW_ConfigTable SG_CFA_GAMMA_PLBW_ConfigTable
#endif
#if defined(XPAR_SG_CC_S6_PLBW_NUM_INSTANCES)
 #include "sg_cc_s6_plbw.h"
 #define CC_PLBW_ConfigTable SG_CC_S6_PLBW_ConfigTable
#endif
#if defined(XPAR_SG_STATS_S6_PLBW_NUM_INSTANCES)
 #include "sg_stats_s6_plbw.h"
 #define STATS_PLBW_ConfigTable SG_STATS_S6_PLBW_ConfigTable
#endif
#if defined(XPAR_SG_GAMMA_S6_PLBW_NUM_INSTANCES)
 #include "sg_gamma_s6_plbw.h"
 #define GAMMA_PLBW_ConfigTable SG_GAMMA_S6_PLBW_ConfigTable
#endif
#if defined(XPAR_SG_RGB_MIXER_PLBW_NUM_INSTANCES)
 #include "sg_rgb_mixer_plbw.h"
#endif




#define VOP_DR_8B_N10B_EN 		0x1 	// When set dynamic range is 8-bit, else 10-bit
#define VOP_DR_PT_NCOMP_EN 	0x2	// When set dynamic range is unchanged, else 12-bit companding
#define VOP_BC_BRIGHT_EN 		0x1
#define VOP_BC_CONT_EN 			0x2
#define VOP_BAL_EN 				0x1
#define VOP_STAT_EN 				0x1

#define COL_RED 0
#define COL_GRN 1
#define COL_BLU 2

typedef struct {
	Xint8 *sm_name;
	Xint8 *name;
} VopGainStr;

static VopGainStr VopGainInfo[3] = {
	// COL_RED
	{
		"r_bal",
		"Red"
	},
	// COL_GRN
	{
		"g_bal",
		"Green"
	},
	// COL_BLU
	{
		"b_bal",
		"Blue"
	}
};

static Xuint8 gammaR709[256] = {
// ITU Recommendation 709 settings
	  0,   5,   9,  14,  18,  23,  27,  30,
	 34,  37,  40,  43,  46,  48,  51,  53,
	 55,  58,  60,  62,  64,  66,  68,  70,
	 72,  73,  75,  77,  78,  80,  82,  83,
	 85,  86,  88,  89,  91,  92,  94,  95,
	 97,  98,  99, 101, 102, 103, 104, 106,
	107, 108, 109, 111, 112, 113, 114, 115,
	116, 118, 119, 120, 121, 122, 123, 124,
	125, 126, 127, 128, 129, 130, 131, 132,
	133, 134, 135, 136, 137, 138, 139, 140,
	141, 142, 143, 144, 145, 146, 147, 147,
	148, 149, 150, 151, 152, 153, 154, 154,
	155, 156, 157, 158, 159, 159, 160, 161,
	162, 163, 164, 164, 165, 166, 167, 168,
	168, 169, 170, 171, 171, 172, 173, 174,
	174, 175, 176, 177, 177, 178, 179, 180,
	180, 181, 182, 182, 183, 184, 185, 185,
	186, 187, 187, 188, 189, 189, 190, 191,
	191, 192, 193, 193, 194, 195, 195, 196,
	197, 197, 198, 199, 199, 200, 201, 201,
	202, 203, 203, 204, 205, 205, 206, 206,
	207, 208, 208, 209, 209, 210, 211, 211,
	212, 213, 213, 214, 214, 215, 216, 216,
	217, 217, 218, 218, 219, 220, 220, 221,
	221, 222, 223, 223, 224, 224, 225, 225,
	226, 227, 227, 228, 228, 229, 229, 230,
	230, 231, 232, 232, 233, 233, 234, 234,
	235, 235, 236, 236, 237, 238, 238, 239,
	239, 240, 240, 241, 241, 242, 242, 243,
	243, 244, 244, 245, 245, 246, 246, 247,
	247, 248, 248, 249, 249, 250, 251, 251,
	252, 252, 253, 253, 254, 254, 255, 255
};		

/* Default values for processing pipleine:
 *		spc_thresh = 	0x60
 *		bc_ctrl = 		0x3
 *		brightness = 	0x0
 *		contrast = 		0x80
 *		bal_ctrl = 		0x1
 *		r_bal = 			0x80
 *		g_bal = 			0x80
 *		b_bal = 			0x80
 */
typedef struct {
	Xint8 *sm_name;
	Xuint32 val;
} DEF_PROC_PARAMS ;

#define NUM_DEF_PROC_PARAMS 9
static DEF_PROC_PARAMS defProcParams[NUM_DEF_PROC_PARAMS] = {
	"spc_thresh", 		0x60,
	"bc_ctrl", 			VOP_BC_BRIGHT_EN | VOP_BC_CONT_EN,
	"brightness", 		0x0,
	"contrast", 		0x80,
	"bal_ctrl",			VOP_BAL_EN,
	"r_bal",				0x80,
	"g_bal",				0x80,
	"b_bal",				0x80,
	"stat_ctrl",		VOP_STAT_EN
};

 
static void ivk_processing_menu_help(void);
