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
// Module Name:         ivk_top.c
// Project Name:        IVK
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-DVI/DP
//
// Tool versions:       ISE 11.4
//
// Description:         IVK Top Level Menu
//                      - based on vsk_top.c
//                      - modified as follows:
//                         - renamed to ivk_top
//                         - modified for IVK hardware
//
// Dependencies:        
//
// Revision:            Jan 18, 2010: 1.00 Initial version
//                      Mar 17, 2010: 1.02 Add arguments to tfp410 config routines
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
// Filename            : vsk_top.c
// $Revision:: 3839   $: Revision of last commit
// $Date:: 2008-09-23#$: Date of last commit
// Description         : Camera Frame Buffer Demo top-level menu
//******************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Located in: microblaze_0/include/
#include "xbasic_types.h"
#include "xutil.h"
#include "xparameters.h"
#include "xstatus.h"
#include "mb_interface.h"

#include "ivk_iic_diag.h"
#include "ivk_camera.h"
#include "ivk_frame_buffer.h"
#include "ivk_video_resolution.h"
#include "ivk_camera_menu.h"
#include "ivk_processing_menu.h"

//--------------NEW---------------
#include "ivk_fir_2d.h"
//--------------------------------

#include "fmc_iic.h"
fmc_iic_t fmc_ipmi_iic;
fmc_iic_t fmc_imageov_iic;

#include "fmc_ipmi.h"

#if defined(XPAR_SG_I2C_CONTROLLER_S6_PLBW_NUM_INSTANCES)
#include "sg_i2c_controller_s6_plbw.h"
#define SG_I2C_CONTROLLER_PLBW_ConfigTable SG_I2C_CONTROLLER_S6_PLBW_ConfigTable
#endif

#include "fmc_imageov.h"
fmc_imageov_t fmc_imageov;

static void help_top(void);

// Define video resolution
#define CAMERA_RESOLUTION  VIDEO_RESOLUTION_VGA
//#define CAMERA_RESOLUTION  VIDEO_RESOLUTION_720P

// Functions copied from vsk_util.c
void usec_wait(Xint32 delay);
void set_dcm_0_reset();
void release_dcm_0_reset();

XStatus main (void)
{
   Xint32 inchar;
   
   Xuint32 camera_select = 1;
   Xuint32 frameWriteEn = 1;
   Xuint32 width, height, stride, offset;
   Xint32 resolution = CAMERA_RESOLUTION;
   Xuint32 bayer_phase = 3, vertical_flip = 0, horizontal_flip = 0;

	/* Initialize ICache */
	microblaze_disable_icache();
	microblaze_init_icache_range(XPAR_MICROBLAZE_0_ICACHE_BASEADDR, XPAR_MICROBLAZE_0_CACHE_BYTE_SIZE);
	microblaze_enable_icache ();
	/* Initialize DCache */
	microblaze_disable_dcache();
	microblaze_init_dcache_range(XPAR_MICROBLAZE_0_DCACHE_BASEADDR, XPAR_MICROBLAZE_0_DCACHE_BYTE_SIZE);
	microblaze_enable_dcache ();

  
  // Use white on black for terminal color scheme
  print("\x1b[?5l\x1b[0m\x1b[H\x1b[J");
  
  // FMC-IIC Initialization
  if ( !fmc_iic_xps_init( &fmc_ipmi_iic,  "FMC_IPMI_I2C_CONTROLLER", XPAR_XPS_IIC_0_BASEADDR ) )
  {
     exit(0);
  }
#if defined(XPAR_SG_I2C_CONTROLLER_S6_PLBW_NUM_INSTANCES)
  if ( !fmc_iic_sg_init( &fmc_imageov_iic, "FMC_IMAGEOV_I2C_CONTROLLER", &SG_I2C_CONTROLLER_PLBW_ConfigTable[0], 10 ) )
#else
  if ( !fmc_iic_xps_init( &fmc_imageov_iic, "FMC_IMAGEOV_I2C_CONTROLLER", XPAR_XPS_IIC_1_BASEADDR ) )
#endif
  {
    exit(0);
  }

  // Enable FMC Module
  fmc_ipmi_enable( &fmc_ipmi_iic, FMC_ID_SLOT1 );

  // Reset and Initialize the FMC devices
  xil_printf("Reset and Initialize the FMC devices ...\n\r" );
  fmc_imageov_init( &fmc_imageov, "FMC-IMAGEOV", &fmc_imageov_iic );
  fmc_imageov_iic_mux_reset( &fmc_imageov );   
  fmc_imageov_config_cdce925( &fmc_imageov );
  fmc_imageov_config_cdce925_y4y5_freq( &fmc_imageov, FMC_IMAGEOV_FREQ_12_000_000);
  fmc_imageov_reset_tfp410( &fmc_imageov );
  fmc_imageov_config_tfp410( &fmc_imageov, FMC_IMAGEOV_TFP410_ENABLED, FMC_IMAGEOV_TFP410_DESKEW_n1400ps );

  // Check for and initialize Camera #2
  if (ivk_camera_present(2, 0) == 1) {
  	 print("Camera 2 detected.\r\n"); 
#if (CAMERA_RESOLUTION == VIDEO_RESOLUTION_720P)
    ivk_camera2_config(OV9710_CONFIG_720P30);
#else    
    ivk_camera2_config(OV9710_CONFIG_VGAP30);
#endif    
    camera_select = 2;
  } else {
    print("Error: Camera 2 not found.\r\n");
    exit(0);
  }
  
  // set video resolution for display domain
  ivk_vres_generate( resolution );
  if ( resolution == VIDEO_RESOLUTION_720P )
  {
     fmc_imageov_config_cdce925_y1_freq( &fmc_imageov, FMC_IMAGEOV_FREQ_74_250_000);
     print("Clock generator set to 74.25 MHz.\r\n");
  }
  else if ( resolution == VIDEO_RESOLUTION_VGA )
  {
	 fmc_imageov_config_cdce925_y1_freq( &fmc_imageov, FMC_IMAGEOV_FREQ_25_175_000);
     print("Clock generator set to 25.175 MHz.\r\n");
  }
   
  // Reset input clock DCM
  set_dcm_0_reset();
  usec_wait(200000);
  release_dcm_0_reset();

  // Initialize processing  
  ivk_processing_init();
  ivk_processing_bayer(bayer_phase);
  
  // Initialize the 2-D FIR
  ivk_disable_fir_2d_coef_update();
  ivk_load_fir_2d_gain(0);          // unity gain
  ivk_load_fir_2d_coefficients(0);  // identity filter
  ivk_enable_fir_2d_coef_update();

  // Initialize frame buffer resolution
  ivk_fb_init();
  ivk_fb_clear_memory();
  ivk_fb_set_input_resolution( resolution, 1 );
  ivk_fb_set_output_resolution( resolution, 1 );

  help_top();

  while (1)
  {
    print(">");
    
    inchar = inbyte(); 
    
    xil_printf("%c\n\r",inchar);

    switch (inchar){
      // Help Screen
      case '?' : 
      {
        help_top(); 
        break;
      }
	  // 2D FIR menu
      case 'f' :
      {
        ivk_fir_2d_main();
        help_top();
        break;
      }
      // Enter Processing Menu
      case 'p' :
      {
        ivk_processing_menu();
        help_top();
        break;
      }
	  // Video Resolution
     case 'r':
     {

        ivk_fb_set_input_resolution( resolution, 0 );
        ivk_fb_set_output_resolution( resolution, 0 );

        if ( resolution == VIDEO_RESOLUTION_720P )
        {
           resolution = VIDEO_RESOLUTION_VGA;
           ivk_camera2_config(OV9710_CONFIG_VGAP30);
           ivk_vres_generate( resolution );
      	   fmc_imageov_config_cdce925_y1_freq( &fmc_imageov, FMC_IMAGEOV_FREQ_25_175_000);
        }
        else
        {
           resolution = VIDEO_RESOLUTION_720P;
           ivk_camera2_config(OV9710_CONFIG_720P30);
           ivk_vres_generate( resolution );
           fmc_imageov_config_cdce925_y1_freq( &fmc_imageov, FMC_IMAGEOV_FREQ_74_250_000);
        }
        //usec_wait(100000);
        ivk_fb_init();
        ivk_fb_clear_memory();
        ivk_fb_set_input_resolution( resolution, 1 );
        ivk_fb_set_output_resolution( resolution, 1 );
        resolution = ivk_vres_detect();
        break;
      }
      // Test Pattern toggle
      case 't' :
      {
        Xuint32 frameAddress;
        frameWriteEn = ~frameWriteEn & 0x1;
        ivk_fb_set_input_resolution( resolution, frameWriteEn );
        usec_wait(100000);
        if (!frameWriteEn)
        {
          width = ivk_fb_get_width(resolution);
          height = ivk_fb_get_height(resolution);
          stride = ivk_fb_get_stride(resolution);
          offset = ivk_fb_get_offset(resolution);
          frameAddress = ivk_fb_get_current_frame_address();
          ivk_fb_disp_colorbar(width,height,frameAddress,stride);
        }
        xil_printf("Test Pattern mode: %s\r\n", (frameWriteEn==0 ? "on" : "off"));
        break;
      }
      // CFA Bayer Phase
	  case 'y' :
	  {
		if(bayer_phase < 3) bayer_phase++;
		else bayer_phase = 0;

		ivk_fb_set_input_resolution( resolution, 0 );
		usec_wait(500000);
		ivk_processing_bayer(bayer_phase);
		ivk_fb_clear_memory();
		ivk_fb_set_input_resolution( resolution, 1 );
		
		xil_printf("Bayer phase set to %d\r\n", bayer_phase);
		break;
	  }
      // Vertical Flip
	  case 'v' :
	  {
		vertical_flip = !vertical_flip;

        ivk_fb_set_input_resolution( resolution, 0 );
        usec_wait(500000);
		ivk_camera_flip_image(camera_select, vertical_flip, horizontal_flip);
        ivk_fb_clear_memory();
        ivk_fb_set_input_resolution( resolution, 1 );
		xil_printf("Vertical Flip set to %s\r\n", vertical_flip?"on":"off" );
		break;
	  }
      // Horizontal Flip
      case 'h' :
      {
		horizontal_flip = !horizontal_flip;

        ivk_fb_set_input_resolution( resolution, 0 );
        usec_wait(500000);
        ivk_camera_flip_image(camera_select, vertical_flip, horizontal_flip);
        ivk_fb_clear_memory();
        ivk_fb_set_input_resolution( resolution, 1 );
		
        xil_printf("Horizontal Flip set to %s\r\n", horizontal_flip?"on":"off" );
        break;
	  }
    }
  }
}

static void help_top(void)
{
  print("\n\r");
  print("-----------------------------------------------------\n\r");
  print("--    Spartan-6 Industrial Video Processing Kit    --\n\r");
  print("--  Camera Video Processing and Frame Buffer Demo  --\n\r");
  print("-----------------------------------------------------\n\r");
  print("\n\r");
  print(" f = 2D FIR Menu \n\r");
  print(" p = Processing Menu\r\n");
  print(" r = Video Resolution (toggle VGA/720p)\n\r" );
  print(" t = Test Pattern (toggle on/off) \n\r");
  print(" y = CFA Bayer Phase (toggle 0/1/2/3)\r\n");
  print(" v = Vertical flip (toggle on/off)\r\n");
  print(" h = Horizontal flip (toggle on/off)\r\n");
  print(" ?   Print the Top-Level menu Help Screen \n\r");
  print("------------------------------------------------------\n\r");
}


/***********************************************************************
* Wait the specified number of microseconds
*
* @param    None.
*
* @return   None. 
*
* @note     Calibrated at 100MHz CPU clock using scope, 
*            should work for any CPU speed
*
***********************************************************************/
void usec_wait(Xint32 delay) {
	Xint32 val = delay * (Xint32)( (XPAR_MICROBLAZE_CORE_CLOCK_FREQ_HZ * 17) / 100000000 );
	while(val--) 
		asm("nop");
}

/***********************************************************************
* This function puts the DCM_0 PCORE into reset
*
* @param    None.
*
* @return   None. 
*
* @note     None.
*
***********************************************************************/
void set_dcm_0_reset( void )
{
   Xuint32 value;

   fmc_ipmi_iic.fpGpoRead( &fmc_ipmi_iic, &value );
   value = value | 0x00000004; // Force bit 2 to 1
   fmc_ipmi_iic.fpGpoWrite( &fmc_ipmi_iic, value );
}

/***********************************************************************
* This function releases the DCM_0 PCORE from reset
*
* @param    None.
*
* @return   None. 
*
* @note     None.
*
***********************************************************************/
void release_dcm_0_reset( void )
{
   Xuint32 value;

   fmc_ipmi_iic.fpGpoRead( &fmc_ipmi_iic, &value );
   value = value & ~0x00000004; // Force bit 2 to 0
   fmc_ipmi_iic.fpGpoWrite( &fmc_ipmi_iic, value );
}
