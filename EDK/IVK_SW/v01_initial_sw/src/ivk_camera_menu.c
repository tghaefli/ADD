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
// Design Name:         IVK_CAMERA_MENU
// Module Name:         ivk_camera_menu.c
// Project Name:        IVK
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-IMAGEOV
//
// Tool versions:       ISE 11.4
//
// Description:         IVK Camera Menu
//                      - based on vsk_camera_menu
//                      - modified as follows:
//                         - renamed to ivk_camera_menu
//                         - remove high-dynamic range mode
//                         - remove auto noise correction
//
// Dependencies:        
//
// Revision:            Jan 18, 2010: 1.00 Initial version
//                      Apr 15, 2010: 1.05 Add control for black level calibration (BLC)
//                      Apr 27, 2010: 1.06 Add control for lens correction, AWB
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
// Filename            : vsk_camera_menu.c
// $Revision:: 3621   $: Revision of last commit
// $Date:: 2008-09-10#$: Date of last commit
// Description         : Menu of commands for configuring VSK camera
//******************************************************************************/

#include "ivk_camera_menu.h"
#include "ivk_camera_menu_l.h"

 
Xint32 ivk_camera_menu( Xuint32 camera_select ) {
  Xint32 inchar;
  Xint32 phase = 0;
  Xuint32 tmp;
  static Xint32 testpat = 0, exp = 1, agc = 1, noise = 0, mode = 0;
  static Xint32 blc = 0, lenc = 1, awb = 1;
  Xint32 ret = 0;
  
  ivk_camera_menu_help();

  while (!ret)
  {
    print(">");
    
    //inchar = inbyte();
    
    xil_printf("%c\n\r",inchar);

    switch (inchar){
		case 'r' : 
      {
        if ( camera_select == 1) {
          ivk_camera1_config(OV9710_CONFIG_720P30);
			 // Reset state of all camera configurables
			 testpat = 0;
			 exp = 1;
			 agc = 1; 
			 noise = 0;
			 mode = 0;
        }
        else {
          ivk_camera2_config(OV9710_CONFIG_720P30);
			 // Reset state of all camera configurables
			 testpat = 0;
			 exp = 1;
			 agc = 1; 
			 noise = 0;
			 mode = 0;
        }
		  break;
      }
		case 't' : 
      {
        testpat = (testpat + 1) % 5;
        xil_printf("Configuring camera test pattern %d\r\n", testpat);
        ivk_camera_test_pattern_config(camera_select, testpat);
        break;
      }
     
		case 'x' : 
      {
        exp = ~exp & 0x1;
        xil_printf("Configuring camera auto exposure %s\r\n", (exp==0 ? "off" : "on"));
        ivk_camera_auto_exposure_config(camera_select, exp);
        break;
      }
		case 'g' : 
      {
        agc = ~agc & 0x1;
        xil_printf("Configuring camera auto gain %s\r\n", (agc==0 ? "off" : "on"));
        ivk_camera_auto_gain_config(camera_select, agc);
        break;
      }
      case 'b' :
      {
        blc = (blc + 1) % 2;
        xil_printf("Configuring black level calibration to %s\r\n", blc?"Electrical BLC":"Optical BLC" );
        ivk_camera_blc_config(camera_select, blc);
        break;
      }
		case 'l' : 
      {
        lenc = ~lenc & 0x1;
        xil_printf("Configuring camera lens correction %s\r\n", (lenc==0 ? "off" : "on"));
        ivk_camera_lenc_config(camera_select, lenc);
        break;
      }
		case 'w' : 
      {
        awb = ~awb & 0x1;
        xil_printf("Configuring camera auto white balance %s\r\n", (awb==0 ? "off" : "on"));
        ivk_camera_awb_config(camera_select, awb);
        break;
      }
		case '?' : 
      {
        ivk_camera_menu_help(); 
        break;
      }
      case 0x1b :
      {
        xil_printf("- exit menu -\n\n\r");
        ret = 1;
        break;
      }
    }
  }
  return 0;
}

static void ivk_camera_menu_help(void)
{
  print("\n\rCamera Menu\n\r");
  print("----------------------------------\n\r");
  print("key(s)  description               \n\r");
  print("----------------------------------\n\r");
  print(" t   Test pattern generation select\r\n");
  print(" x   Auto exposure control on/off\r\n");
  print(" g   Auto gain control on/off\r\n");
  print(" b   Black level calibration (BLC) select (0=electrical, 1=optical)\r\n" );
  print(" l   Lens correction on/off\r\n");
  print(" w   Auto white balance on/off\r\n");
  print(" r   Reset camera defaults\r\n");
  print(" esc Exit back to the Top-Level menu\r\n");
  print(" ?   help \n\r");
  print("---------------------------------\n\r");
}
                                                
   
