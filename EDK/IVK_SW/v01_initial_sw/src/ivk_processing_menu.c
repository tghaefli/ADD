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
// Module Name:         ivk_processing_menu.c
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
// Filename            : vsk_processing_menu.c
// $Revision:: 3621   $: Revision of last commit
// $Date:: 2008-09-10#$: Date of last commit
// Description         : Menu of commands for configuring camera processing
//******************************************************************************/
 
#include "ivk_processing_menu.h"
#include "ivk_processing_menu_l.h"

Xint32 ivk_processing_menu (void) {
  Xint32 inchar;
  Xint32 phase = 0;
//  static Xuint8 color = COL_RED;
  static Xuint32 gamma = VOP_GAMMA_BYPASS;
  static Xuint32 bayer_phase = 0; //, spc_thresh = 96, spc_on = 1;
//  xc_iface_t *spc_iface;
//  xc_iface_t *bc_iface;
//  xc_iface_t *cc_iface;
//  xc_iface_t *stats_iface;
// Waj: added for RGB_Mixer
  xc_iface_t *mixer_iface;

  xc_to_reg_t *to_reg;
  Xint32 ret = 0;
  static Xint8 r_offset, g_offset, b_offset = 0;
  const Xint8 delta_offset = 10;
  const Xint8 max_offset = 127;
  
  // initialize the software driver
//  xc_create(&spc_iface, &SPC_PLBW_ConfigTable[XPAR_SPC_PLBW_0_DEVICE_ID]);
//  xc_create(&bc_iface, &BC_PLBW_ConfigTable[XPAR_BC_PLBW_0_DEVICE_ID]);
//  xc_create(&cc_iface, &CC_PLBW_ConfigTable[XPAR_CC_PLBW_0_DEVICE_ID]);
//  xc_create(&stats_iface, &STATS_PLBW_ConfigTable[XPAR_STATS_PLBW_0_DEVICE_ID]);
// Waj: added for RGB_Mixer
//XC_CfgInitialize(&mixer_iface, &SG_RGB_MIXER_PLBW_ConfigTable[0]);



  ivk_processing_menu_help();

  while (!ret)
  {
    print(">");
    
    inchar = inbyte(); 
    
    xil_printf("%c\n\r",inchar);

    switch (inchar){
            case '?' : 
      {
        ivk_processing_menu_help(); 
        break;
      }
      case 0x1b :
      {
        xil_printf("- exit menu -\n\n\r");
		  ret = 1;
        break;
      }
      // Waj: added for RGB_Mixer
      case 'R' :
      {
    	  // Get reference to register
    	  xc_get_shmem(mixer_iface, "mix_red", (void **) &to_reg);
    	  // increase value when max not reached yet
    	  if (r_offset < max_offset-delta_offset){
    		  r_offset += delta_offset;
    	  } else {
    		  r_offset = max_offset;
    	  }
    	  xc_write(mixer_iface, to_reg->din, (const unsigned) r_offset);
    	  break;
      }
      case 'r' :
      {
    	  // Get reference to register
    	  xc_get_shmem(mixer_iface, "mix_red", (void **) &to_reg);
    	  // decrease value when min not reached yet
    	  if (r_offset > -max_offset+delta_offset){
    		  r_offset -= delta_offset;
    	  } else {
    		  r_offset = -max_offset;
    	  }
    	  xc_write(mixer_iface, to_reg->din, (const unsigned) r_offset);
    	  break;
      }
      case 'G' :
      {
    	  // Get reference to register
    	  xc_get_shmem(mixer_iface, "mix_green", (void **) &to_reg);
    	  // increase value when max not reached yet
    	  if (g_offset < max_offset-delta_offset){
    		  g_offset += delta_offset;
    	  } else {
    		  g_offset = max_offset;
    	  }
    	  xc_write(mixer_iface, to_reg->din, (const unsigned) g_offset);
    	  break;
      }
      case 'g' :
      {
    	  // Get reference to register
    	  xc_get_shmem(mixer_iface, "mix_green", (void **) &to_reg);
    	  // decrease value when min not reached yet
    	  if (g_offset > -max_offset+delta_offset){
    		  g_offset -= delta_offset;
    	  } else {
    		  g_offset = -max_offset;
    	  }
    	  xc_write(mixer_iface, to_reg->din, (const unsigned) g_offset);
    	  break;
      }
      case 'B' :
      {
    	  // Get reference to register
    	  xc_get_shmem(mixer_iface, "mix_blue", (void **) &to_reg);
    	  // increase value when max not reached yet
    	  if (b_offset < max_offset-delta_offset){
    		  b_offset += delta_offset;
    	  } else {
    		  b_offset = max_offset;
    	  }
    	  xc_write(mixer_iface, to_reg->din, (const unsigned) b_offset);
    	  break;
      }
      case 'b' :
      {
    	  // Get reference to register
    	  xc_get_shmem(mixer_iface, "mix_blue", (void **) &to_reg);
    	  // decrease value when min not reached yet
    	  if (b_offset > -max_offset+delta_offset){
    		  b_offset -= delta_offset;
    	  } else {
    		  b_offset = -max_offset;
    	  }
    	  xc_write(mixer_iface, to_reg->din, (const unsigned) b_offset);
    	  break;
      }


		/*
      case 'p' :
      {
        // Get reference to register
	     xc_get_shmem(spc_iface, "spc_thresh", (void **) &to_reg);
		  if(spc_on == 1) {
				tmp = 0xFFF; // set to max for off
				spc_on = 0;
				printf("Stuck pixel correction is off\r\n");
			} else {
				spc_on = 1;
				tmp = spc_thresh;
				printf("Stuck pixel correction is on\r\n");
			}
		  xc_write(spc_iface, to_reg->din, (const unsigned)tmp);
        break;
		}		
      case '.' :
      {
        // Get reference to register
	     xc_get_shmem(spc_iface, "spc_thresh", (void **) &to_reg);
        if (spc_thresh < 0xFFF) spc_thresh = spc_thresh + 16;
        if (spc_thresh > 0xFFF) spc_thresh = 0xFFF; // clamp to max
        xc_write(spc_iface, to_reg->din, (const unsigned)spc_thresh);
		  xil_printf("Stuck pixel threshold set to %d\r\n", spc_thresh);
		  spc_on = 1; // Make sure software has correct state
        break;
		}
      case ',' :
      {
        // Get reference to register
	     xc_get_shmem(spc_iface, "spc_thresh", (void **) &to_reg);
        if (spc_thresh == 0xFFF) spc_thresh = spc_thresh + 1; // boundary condition
		  if (spc_thresh > 0) spc_thresh = spc_thresh - 16;
        xc_write(spc_iface, to_reg->din, (const unsigned)spc_thresh);
		  xil_printf("Stuck pixel threshold set to %d\r\n", spc_thresh);
		  spc_on = 1; // Make sure software has correct state
        break;
		}	
		*/
      /*
		case 'y' :
		{
		  if(bayer_phase < 3) bayer_phase++;
		  else bayer_phase = 0;
		  ivk_processing_bayer(bayer_phase);
		  xil_printf("Bayer phase set to %d\r\n", bayer_phase);
		  break;
		}
      */
		/*
		case 'h' : //Brightness on/off
		{
			xc_get_shmem(bc_iface, "bc_ctrl", (void **) &to_reg);
			xc_read(bc_iface, to_reg->din, &tmp); 
			if(tmp & VOP_BC_BRIGHT_EN) 
			{
			   tmp &= ~VOP_BC_BRIGHT_EN;
				print("Brightness control off\r\n");
			} 
			else
			{
				tmp |= VOP_BC_BRIGHT_EN;
				print("Brightness control on\r\n");
			}
			xc_write(bc_iface, to_reg->din, (const unsigned)tmp);	
			break;
		}
		case 'n' : //Contrast on/off
		{
	     xc_get_shmem(bc_iface, "bc_ctrl", (void **) &to_reg);
	     xc_read(bc_iface, to_reg->din, &tmp); 
			if(tmp & VOP_BC_CONT_EN) 
			{
			   tmp &= ~VOP_BC_CONT_EN;
				print("Contrast control off\r\n");
			} 
			else
			{
				tmp |= VOP_BC_CONT_EN;
				print("Contrast control on\r\n");
			}
			xc_write(bc_iface, to_reg->din, (const unsigned)tmp);	
			break;
		}
		case 'c' : //Color balance on/off
		{
			xc_get_shmem(cc_iface, "bal_ctrl", (void **) &to_reg);
			xc_read(cc_iface, to_reg->din, &tmp); 
			if(tmp & VOP_BAL_EN) 
			{
			   tmp &= ~VOP_BAL_EN;
				print("Color balance control off\r\n");
			} 
			else
			{
				tmp |= VOP_BAL_EN;
				print("Color balance control on\r\n");
			}
			xc_write(cc_iface, to_reg->din, (const unsigned)tmp);	
			break;
		}
		case '-' : //Brighness decrease
		{
			xc_get_shmem(bc_iface, "brightness", (void **) &to_reg);
			xc_read(bc_iface, to_reg->din, &tmp); 
			//Sign extend if necessary
			if (tmp & 0x100) tmp |= ~0xFF;
			if ((Xint32)tmp > -255) (Xint32)tmp--;
			xc_write(bc_iface, to_reg->din, (const unsigned)tmp);	
			xil_printf("Brightness=%d\r\n", (Xint32)tmp);
			break;
		}
		case '=' : //Brighness increase
		{
			xc_get_shmem(bc_iface, "brightness", (void **) &to_reg);
			xc_read(bc_iface, to_reg->din, &tmp); 
			//Sign extend if necessary
			if (tmp & 0x100) tmp |= ~0xFF;
			if ((Xint32)tmp < 255) (Xint32)tmp++;
			xc_write(bc_iface, to_reg->din, (const unsigned)tmp);	
			xil_printf("Brightness=%d\r\n", (Xint32)tmp);
			break;
		}
		*/
		/*
		case 's' : //Show image stats
		{
			//First disabe stats so values read out are frame coherent
			xc_get_shmem(stats_iface, "stat_ctrl", (void **) &to_reg);
			xc_write(stats_iface, to_reg->din, ~VOP_STAT_EN);	
			//Read out stats
			//Red
			xc_get_shmem(stats_iface, "r_min_val", (void **) &to_reg);
			xc_read(stats_iface, to_reg->din, &tmp); 
			xil_printf("Red:\tMin:\t%d", tmp);
			xc_get_shmem(stats_iface, "r_max_val", (void **) &to_reg);
			xc_read(stats_iface, to_reg->din, &tmp); 
			xil_printf("\tMax:\t%d\r\n", tmp);
			//Green
			xc_get_shmem(stats_iface, "g_min_val", (void **) &to_reg);
			xc_read(stats_iface, to_reg->din, &tmp); 
			xil_printf("Green:\tMin:\t%d", tmp);
			xc_get_shmem(stats_iface, "g_max_val", (void **) &to_reg);
			xc_read(stats_iface, to_reg->din, &tmp); 
			xil_printf("\tMax:\t%d\r\n", tmp);
			//Blue
			xc_get_shmem(stats_iface, "b_min_val", (void **) &to_reg);
			xc_read(stats_iface, to_reg->din, &tmp); 
			xil_printf("Blue:\tMin:\t%d", tmp);
			xc_get_shmem(stats_iface, "b_max_val", (void **) &to_reg);
			xc_read(stats_iface, to_reg->din, &tmp); 
			xil_printf("\tMax:\t%d\r\n", tmp);
			//Re-enable stats so they will continue to calculate
			xc_get_shmem(stats_iface, "stat_ctrl", (void **) &to_reg);
			xc_write(stats_iface, to_reg->din, VOP_STAT_EN);	
			break;
		}
		*/
		/*
		case '[' : //Contrast decrease
		{
			xc_get_shmem(bc_iface, "contrast", (void **) &to_reg);
			xc_read(bc_iface, to_reg->din, &tmp); 
			if (tmp > 0) tmp--;
			xc_write(bc_iface, to_reg->din, (const unsigned)tmp);	
			xil_printf("Contrast=%d.%03d\r\n", tmp>>to_reg->bin_pt, 
				(Xint32)((float)((tmp & ((1<<to_reg->bin_pt)-1))*1000)/(float)(1<<to_reg->bin_pt)));
			break;
		}
		case ']' : //Contrast increase
		{
			xc_get_shmem(bc_iface, "contrast", (void **) &to_reg);
			xc_read(bc_iface, to_reg->din, &tmp); 
			if (tmp < 255) tmp++;
			xc_write(bc_iface, to_reg->din, (const unsigned)tmp);	
			xil_printf("Contrast=%d.%03d\r\n", tmp>>to_reg->bin_pt, 
				(Xint32)((float)((tmp & ((1<<to_reg->bin_pt)-1))*1000)/(float)(1<<to_reg->bin_pt)));
			break;
		}
		case 'r' : //Select color red
		{
			color = COL_RED;
			print("Red color selected\r\n");
			break;
		}
		case 'g' : //Select color green
		{
			color = COL_GRN;
			print("Green color selected\r\n");
			break;
		}
		case 'b' : //Select color blue
		{
			color = COL_BLU;
			print("Blue color selected\r\n");
			break;
		}
		case ';' : //Color gain decrease
		{
			xc_get_shmem(cc_iface, VopGainInfo[color].sm_name, (void **) &to_reg);
			xc_read(cc_iface, to_reg->din, &tmp); 
			if (tmp > 0) tmp--;
			xc_write(cc_iface, to_reg->din, (const unsigned)tmp);	
			xil_printf("%s Gain=%d.%03d\r\n", VopGainInfo[color].name, tmp>>to_reg->bin_pt, 
				(Xint32)((float)((tmp & ((1<<to_reg->bin_pt)-1))*1000)/(float)(1<<to_reg->bin_pt)));		
			break;
		}
		case '\'' : //Color gain increase
		{
			xc_get_shmem(cc_iface, VopGainInfo[color].sm_name, (void **) &to_reg);
			xc_read(cc_iface, to_reg->din, &tmp); 
			if (tmp < 255) tmp++;
			xc_write(cc_iface, to_reg->din, (const unsigned)tmp);	
			xil_printf("%s Gain=%d.%03d\r\n", VopGainInfo[color].name, tmp>>to_reg->bin_pt, 
				(Xint32)((float)((tmp & ((1<<to_reg->bin_pt)-1))*1000)/(float)(1<<to_reg->bin_pt)));		
			break;
		}
		*/
		case 'o' : // Gamma enable/disable
		{
			if(gamma == VOP_GAMMA_BYPASS) 
			{
				gamma = VOP_GAMMA_R709; // flip gamma setting
				print("Gamma configured per Rec. 709.\r\n");
			}
			else
			{
				gamma = VOP_GAMMA_BYPASS; // flip gamma setting
				print("Gamma configured as pass-through.\r\n");
			}
			//ivk_processing_gamma(gamma);
			break;
		}
		case 'i' : // Restore defaults
		{
			if (ivk_processing_init() == 0) {
				print("Processing settings successfully initialized.\r\n");
			} else {
				print("An error occurred while trying to initialize processing settings.\r\n");
			}	
			break;
		}
    }
  }
  return 0;
}

void ivk_processing_menu_help(void)
{
  print("\n\rProcessing Menu\n\r");
  print("----------------------------------\n\r");
  print("key(s)  description               \n\r");
  print("----------------------------------\n\r");
  /*
  print(" p   Stuck pixel correction on/off\r\n");
  print(" ,   Stuck pixel threshold decrease\r\n");
  print(" .   Stuck pixel threshold increase\r\n");
  print(" h   Brightness control on/off\r\n");
  print(" -   Brightness setting decrease\r\n");
  print(" =   Brightness setting increase\r\n");
  print(" n   Contrast control on/off\r\n");
  print(" [   Contrast setting decrease\r\n");
  print(" ]   Contrast setting increase\r\n");
  print(" c   Color balance control on/off\r\n");
  print(" r   Color balance select red\r\n");
  print(" g   Color balance select green\r\n");
  print(" b   Color balance select blue\r\n");
  print(" ;   Color balance gain decrease (selected color)\r\n");
  print(" '   Color balance gain increase (selected color)\r\n");
  */
  print(" o   Gamma control on/off\r\n");
  print(" R   RGB Mixer - Increase RED gain \r\n");
  print(" r   RGB Mixer - Decrease RED gain \r\n");
  print(" G   RGB Mixer - Increase GREEN gain \r\n");
  print(" g   RGB Mixer - Decrease GREEN gain \r\n");
  print(" B   RGB Mixer - Increase BLUE gain \r\n");
  print(" b   RGB Mixer - Decrease BLUE gain \r\n");

//  print(" s   Show image statistics (red, green, blue min/max)\r\n");
  print(" i   Init processing settings to defaults\r\n");
  print(" esc Exit back to the Top-Level menu\r\n");
  print(" ?   help \n\r");
  print("---------------------------------\n\r");
}
                                                
/* Set Bayer filter phase
 * Returns 0 if phase was set successfully, otherwise not 
 */
Xint32 ivk_processing_bayer(Xuint32 phase) {
	xc_status_t status = XC_FAILURE;
	xc_iface_t *cfa_iface;
	xc_to_reg_t *cfa_reg;
   Xuint32 cfa_value;
	
    // initialize the software driver
    xc_create(&cfa_iface, &CFA_PLBW_ConfigTable[XPAR_SG_CFA_GAMMA_PLBW_0_DEVICE_ID]);
   
	// Get reference to register
	xc_get_shmem(cfa_iface, "bayer_ctrl", (void **) &cfa_reg);

	switch(phase) {
		case 0:
			cfa_value = VOP_BAYER_PHASE0;
			break;
		case 1:
			cfa_value = VOP_BAYER_PHASE1;
			break;
		case 2:
			cfa_value = VOP_BAYER_PHASE2;
			break;
		case 3:
			cfa_value = VOP_BAYER_PHASE3;
			break;
      case 4:
         cfa_value = VOP_BAYER_BYPASS;
         break;
	}

	status = xc_write(cfa_iface, cfa_reg->din, (const unsigned) cfa_value); 
#ifdef DEBUG
	if(status == XC_FAILURE) { print("Error Writing to CFA_PLBW_0/Bayer_Ctrl\n\r"); }
   else { xil_printf("Param[%s] = 0x%x\r\n", "bayer_ctrl", cfa_value); } 
#endif
	

	return (status == XC_FAILURE ? 1 : 0);
}

#if 0
/* Sets gamma table for red, green, and blue components
 * When input VOP_GAMMA_BYPASS, gamma is set for 1-1 mapping
 * When input VOP_GAMMA_R709, gamma is set using pre-calculated table
 * Returns 0 on success, 
 */
Xint32 ivk_processing_gamma(Xuint32 mode) {
  Xuint32 i;
  Xuint32 val;
  Xuint32 address;
  double x;
  Xint32 retval = 1;
  uint32_t current_buf;
  uint32_t next_buf;
  xc_status_t status;
  xc_shram_t *shram_r;
  xc_shram_t *shram_g;
  xc_shram_t *shram_b;
  xc_to_reg_t *gb_reg;
  xc_iface_t *gamma_iface;
  
  // initialize the software driver
  xc_create(&gamma_iface, &GAMMA_PLBW_ConfigTable[XPAR_GAMMA_PLBW_0_DEVICE_ID]);
  
  // obtain the memory location for storing the settings of the shared memory
  xc_get_shmem(gamma_iface, "gamma_r", (void **) &shram_r);
  xc_get_shmem(gamma_iface, "gamma_g", (void **) &shram_g);
  xc_get_shmem(gamma_iface, "gamma_b", (void **) &shram_b);
  xc_get_shmem(gamma_iface, "gamma_buffer", (void **) &gb_reg);

  status = xc_read(gamma_iface, gb_reg->din, &current_buf); 
  if(status == XC_FAILURE) { 
		xil_printf("Error Reading from GAMMA_PLBW_0/Gamma_Buffer (%d)\n\r",status); 
  } else {
	  next_buf = (current_buf==0) ? 1 : 0;

	  if (mode == VOP_GAMMA_BYPASS)
	  {
		 status = XC_FAILURE;
		 for(i=0; i<256; i++)
		 {  
			address = (next_buf<<8) + i; // Push next_buf to bit location 9    
			status = xc_write(gamma_iface, xc_get_addr(shram_r->addr, address), (const unsigned) i);
			if(status == XC_FAILURE) { 
				print("Error Writing to GAMMA_PLBW_0/GAMMA_R\n\r"); 
				break; 
			}
			status = xc_write(gamma_iface, xc_get_addr(shram_g->addr, address), (const unsigned) i);
			if(status == XC_FAILURE) { 
				print("Error Writing to GAMMA_PLBW_0/GAMMA_G\n\r"); 
				break; 
			}
			status = xc_write(gamma_iface, xc_get_addr(shram_b->addr, address), (const unsigned) i);
			if(status == XC_FAILURE) { 
				print("Error Writing to GAMMA_PLBW_0/GAMMA_B\n\r"); 
				break; 
			}
		 }
	  }
	  else if (mode == VOP_GAMMA_R709)
	  {
		 status = XC_FAILURE;
		 for(i=0; i<256; i++)
		 {
			address = (next_buf<<8) + i; // Push next_buf to bit location 9    
			val = gammaR709[i];
			status = xc_write(gamma_iface, xc_get_addr(shram_r->addr, address), (const unsigned) val);
			if(status == XC_FAILURE) { 
				print("Error Writing to GAMMA_PLBW_0/GAMMA_R\n\r"); 
				break; 
			}
			status = xc_write(gamma_iface, xc_get_addr(shram_g->addr, address), (const unsigned) val);
			if(status == XC_FAILURE) { 
				print("Error Writing to GAMMA_PLBW_0/GAMMA_G\n\r"); 
				break; 
			}
			status = xc_write(gamma_iface, xc_get_addr(shram_b->addr, address), (const unsigned) val);
			if(status == XC_FAILURE) { 
				print("Error Writing to GAMMA_PLBW_0/GAMMA_B\n\r"); 
				break; 
			}
		 }
	  }
	  if (status != XC_FAILURE) {
		  status = xc_write(gamma_iface, gb_reg->din, (const unsigned) next_buf); 
		  if(status == XC_FAILURE) { 
				print("Error Writing to GAMMA_PLBW_0/Gamma_Buffer\n\r"); 
		  } else {
				retval = 0; // Success
		  }
	  }
	}
	return retval;
}
#endif

/* Initialize processing pipeline 
	return 0 on success, 1 on error
 */
Xint32 ivk_processing_init() {
  Xint32 i;
//  xc_iface_t *spc_iface;
//  xc_iface_t *bc_iface;
//  xc_iface_t *cc_iface;
//  xc_iface_t *stats_iface;
  xc_to_reg_t *to_reg;
  Xint32 retval = 0;
/*
   if (xc_create(&spc_iface, &SPC_PLBW_ConfigTable[XPAR_SPC_PLBW_0_DEVICE_ID]) != XC_FAILURE) {
		for(i=0; i<NUM_DEF_PROC_PARAMS; i++) {
			if (xc_get_shmem(spc_iface, defProcParams[i].sm_name, (void **) &to_reg) != XC_FAILURE) {
				if (xc_write(spc_iface, to_reg->din, (const unsigned)defProcParams[i].val) != XC_FAILURE) {	
#ifdef DEBUG
					xil_printf("SPC Param[%s] = 0x%x\r\n", defProcParams[i].sm_name, defProcParams[i].val); 
#endif
					retval = 0;
				}
			}
		}
	}
   
   if (xc_create(&bc_iface, &BC_PLBW_ConfigTable[XPAR_BC_PLBW_0_DEVICE_ID]) != XC_FAILURE) {
		for(i=0; i<NUM_DEF_PROC_PARAMS; i++) {
			if (xc_get_shmem(bc_iface, defProcParams[i].sm_name, (void **) &to_reg) != XC_FAILURE) {
				if (xc_write(bc_iface, to_reg->din, (const unsigned)defProcParams[i].val) != XC_FAILURE) {	
#ifdef DEBUG
					xil_printf("   BC Param[%s] = 0x%x\r\n", defProcParams[i].sm_name, defProcParams[i].val); 
#endif
					retval = 0;
				}
			}
		}
	}

   if (xc_create(&cc_iface, &CC_PLBW_ConfigTable[XPAR_CC_PLBW_0_DEVICE_ID]) != XC_FAILURE) {
		for(i=0; i<NUM_DEF_PROC_PARAMS; i++) {
			if (xc_get_shmem(cc_iface, defProcParams[i].sm_name, (void **) &to_reg) != XC_FAILURE) {
				if (xc_write(cc_iface, to_reg->din, (const unsigned)defProcParams[i].val) != XC_FAILURE) {	
#ifdef DEBUG
					xil_printf("   CC Param[%s] = 0x%x\r\n", defProcParams[i].sm_name, defProcParams[i].val); 
#endif
					retval = 0;
				}
			}
		}
	}

   if (xc_create(&stats_iface, &STATS_PLBW_ConfigTable[XPAR_STATS_PLBW_0_DEVICE_ID]) != XC_FAILURE) {
		for(i=0; i<NUM_DEF_PROC_PARAMS; i++) {
			if (xc_get_shmem(stats_iface, defProcParams[i].sm_name, (void **) &to_reg) != XC_FAILURE) {
				if (xc_write(stats_iface, to_reg->din, (const unsigned)defProcParams[i].val) != XC_FAILURE) {	
#ifdef DEBUG
					xil_printf("STATS Param[%s] = 0x%x\r\n", defProcParams[i].sm_name, defProcParams[i].val); 
#endif
					retval = 0;
				}
			}
		}
	}*/
   
	return retval;
}



