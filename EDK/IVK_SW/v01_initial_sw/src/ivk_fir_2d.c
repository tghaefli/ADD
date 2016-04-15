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
// Module Name:         fir_2d.c
// Project Name:        IVK
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-DVI/DP
//
// Tool versions:       ISE 11.4
//
// Description:         RGB 2D FIR Menu
//                      - based on fir_2d.c
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
// Filename            : fir_2d.c
// $Revision:: 4460   $: Revision of last commit
// $Date:: 2008-11-06#$: Date of last commit
// Description         : C file for RGB 2D FIR Menu
//******************************************************************************/

#include "ivk_fir_2d.h"

void ivk_fir_2d_help(void);

static Xint8 * fir_2d_coef_name[10]=
{
 "Identity" 
,"Edge Detect"
,"Sobel X"   
,"Sobel Y"  
,"Sobel XY"   
,"Blur"  
,"Smooth"  
,"Sharpen"   
,"Gaussian"
,"User Defined"  
};


static Xint32 coef[9][5][5] = 
{ // Identity
  0,  0,  0,  0,  0
 ,0,  0,  0,  0,  0
 ,0,  0,  1,  0,  0
 ,0,  0,  0,  0,  0
 ,0,  0,  0,  0,  0

  //Edge
 ,0,  0,  0,  0,  0
 ,0, -1, -1, -1,  0
 ,0, -1,  8, -1,  0
 ,0, -1, -1, -1,  0
 ,0,  0,  0,  0,  0

  // Sobel X
 ,0,  0,  0,  0,  0
 ,0, -1,  0,  1,  0
 ,0, -2,  0,  2,  0
 ,0, -1,  0,  1,  0
 ,0,  0,  0,  0,  0

  // Sobel Y
 ,0,  0,  0,  0,  0
 ,0,  1,  2,  1,  0
 ,0,  0,  0,  0,  0
 ,0, -1, -2, -1,  0
 ,0,  0,  0,  0,  0

  //Sobel XY
 ,0,  0,  0,  0,  0
 ,0,  0, -1, -1,  0
 ,0,  1,  0, -1,  0
 ,0,  1,  1,  0,  0
 ,0,  0,  0,  0,  0

  // Blur
 ,1,  1,  1,  1,  1
 ,1,  0,  0,  0,  1
 ,1,  0,  0,  0,  1
 ,1,  0,  0,  0,  1
 ,1,  1,  1,  1,  1

  // Smooth
 ,1,  1,  1,  1,  1
 ,1,  5,  5,  5,  1
 ,1,  5, 44,  5,  1
 ,1,  5,  5,  5,  1
 ,1,  1,  1,  1,  1

  // Sharpen
 ,0,  0,  0,  0,  0
 ,0, -2, -2, -2,  0
 ,0, -2, 32, -2,  0
 ,0, -2, -2, -2,  0
 ,0,  0,  0,  0,  0

  // Gaussian
 ,1,  1,  2,  1,  1
 ,1,  2,  4,  2,  1
 ,2,  4,  8,  4,  2
 ,1,  2,  4,  2,  1
 ,1,  1,  2,  1,  1
};

//double gain[9] = { 1, 1, 1, 1, 1, 1/16, 1/100, 1/16, 1/52 };
static Xuint32 gain[9] = { 131072,  131072, 131072, 131072, 
                         131072, 8192, 1310, 8192, 2521 };


void ivk_fir_2d_main (void) 
{
#if 1
  Xint32 inchar;
  Xint32 fir_2d_mode = 0;
  //-----------NEW------------
  Xint32 ret = 0;
  //--------------------------

  ivk_fir_2d_help();

  while (!ret) // <-- NEW: Break statement "ret"
  {
    print(">");
    inchar = inbyte(); 
    
    if(inchar != 0x1b) {
	   xil_printf("%c\n\r",inchar);
    }
	 else {
      print("esc\n\r");
    }

    switch (inchar){
      case '?' : ivk_fir_2d_help(); break;

      case 0x1b :  	xil_printf("- exit menu -\n\n\r"); 
							//---------NEW----------
							ret = 1;
							//----------------------
							break;

      // Load FIR 2D Coefficients - Identity
      case '1' : 
      {
        fir_2d_mode = 0;
        ivk_load_fir_2d(fir_2d_mode);
        break;
      }   
      // Load FIR 2D Coefficients - Edge
      case '2' : 
      {
        fir_2d_mode = 1;
        ivk_load_fir_2d(fir_2d_mode);
        break;
      }   
      // Load FIR 2D Coefficients - Sobel X
      case '3' : 
      {
        fir_2d_mode = 2; 
        ivk_load_fir_2d(fir_2d_mode);
        break;
      }   
      // Load FIR 2D Coefficients - Sobel Y
      case '4' : 
      {
        fir_2d_mode = 3;
        ivk_load_fir_2d(fir_2d_mode);
        break;
      }   
      // Load FIR 2D Coefficients - Sobel XY
      case '5' : 
      {
        fir_2d_mode = 4;
        ivk_load_fir_2d(fir_2d_mode);
        break;
      }   
      // Load FIR 2D Coefficients - Blur
      case '6' : 
      {
        fir_2d_mode = 5;
        ivk_load_fir_2d(fir_2d_mode);
        break;
      }   
      // Load FIR 2D Coefficients - Smooth
      case '7' : 
      {
        fir_2d_mode = 6;
        ivk_load_fir_2d(fir_2d_mode);
        break;
      }   
      // Load FIR 2D Coefficients - Sharpen
      case '8' : 
      {
        fir_2d_mode = 7;
        ivk_load_fir_2d(fir_2d_mode);
        break;
      }   
      // Load FIR 2D Coefficients - Gaussian
      case '9' : 
      {
        fir_2d_mode = 8;
        ivk_load_fir_2d(fir_2d_mode);
        break;
      }   
      // Create FIR 2D Coefficients - User Defined
      case '0' : 
      {
        fir_2d_mode = 9;
        ivk_set_fir_2d_coefficients();
        break;
      }   

      // Increment the 2D FIR Gain
      case '\'' : 
      {
        ivk_disable_fir_2d_coef_update();
        ivk_step_fir_2d_gain(10000);
        ivk_enable_fir_2d_coef_update();

        break;
      }   
      // Decrement the 2D FIR Gain
      case ';' : 
      {
        ivk_disable_fir_2d_coef_update();
        ivk_step_fir_2d_gain(-10000);
        ivk_enable_fir_2d_coef_update();
        break;
      }   

      // Read FIR 2D Coefficients
      case 'c' : 
      {
        print("\n\r 2D FIR Coefficients :\n\r");
        ivk_read_fir_2d_coefficients(27); 
        break;
      }
      // Read FIR 2D Gain
      case 'g' : 
      {
        ivk_read_fir_2d_gain(); 
        break;
      }
      // FIR 2D Status
      case 's' : 
      {
        xil_printf("\n\r The 2D FIR contains %s Coefficients\n\r\n\r",fir_2d_coef_name[fir_2d_mode]);
        break;
      }   
    }
  }
#endif
}

void ivk_fir_2d_help(void)
{
  print("\n\r");
  print("-----------------------------------------------------\n\r");
  print("-- 2D-FIR Video Processing Menu                    --\n\r");
  print("-----------------------------------------------------\n\r");
  print("\n\r");
  print(" Modify the 2D FIR Coefficients \n\r");
  print(" 1 = Identity \n\r");
  print(" 2 = Edge \n\r");
  print(" 3 = Sobel X \n\r");
  print(" 4 = Sobel Y \n\r");
  print(" 5 = Sobel XY \n\r");
  print(" 6 = Blur \n\r");
  print(" 7 = Smooth \n\r");
  print(" 8 = Sharpen \n\r");
  print(" 9 = Gaussian \n\r");
  print(" 0 = User Defined \n\r");
  print("\n\r");
  print(" Modify the 2D FIR Gain \n\r");
  print(" ' = Increment the 2D FIR Gain \n\r");
  print(" ; = Decrement the 2D FIR Gain \n\r");
  print("\n\r");
  print(" Status of the 2D FIR \n\r");
  print(" c = Read 2D FIR Coefficients \n\r");
  print(" g = Read 2D FIR Gain \n\r");
  print(" s = Status 2D FIR \n\r");
  print("\n\r");
  print("esc = exit \n\r");
  print(" ?  = help \n\r");
  print("-----------------------------------------------------\n\r");
}

                                               
void ivk_load_fir_2d(Xint32 mode)
{
  ivk_disable_fir_2d_coef_update();
  ivk_load_fir_2d_coefficients(mode);
  ivk_read_fir_2d_coefficients(27);
  ivk_load_fir_2d_gain(mode);
  ivk_enable_fir_2d_coef_update();
}


void ivk_load_fir_2d_coefficients(Xint32 mode)
{
  Xuint32 i;
  Xuint32 j;

  xc_status_t status;
  static xc_iface_t *iface;
  static xc_shram_t *shram; // coef_buffer
  static int init_done = 0;

  // initialize the software driver
	if (!init_done)
	{
		xc_create(&iface, &SG_2D_FIR_PLBW_ConfigTable[SG_2D_FIR_ID]);

		// obtain the memory location for storing the settings of shared memories
		xc_get_shmem(iface, "coef_buffer", (void **) &shram);
		init_done = 1;
	}

  status = XC_FAILURE;
  for(i=0; i<5; i++)
  {
    for(j=0; j<5; j++)
    {      
      // write value to the shared memory
      status = xc_write(iface, xc_get_addr(shram->addr, i*5+j), (const unsigned) coef[mode][i][j]); 
      if(status == XC_FAILURE) { print("Error Writing to RGB_2D_FIR/COEF_BUFFER\n\r"); return; }
    }
  }

  xil_printf("Loaded 2D FIR with %s Coefficients \n\r",fir_2d_coef_name[mode]);
}


void ivk_set_fir_2d_coefficients(void)
{
  Xint8 buf[INPUTBUFSIZE];
  Xint32 i,j,k;
  Xint32 val;
  
  xc_status_t status = XC_FAILURE;
  static xc_iface_t *iface;
  static xc_shram_t *shram; // coef_buffer
  static int init_done = 0;

  // initialize the software driver
	if (!init_done)
	{
		xc_create(&iface, &SG_2D_FIR_PLBW_ConfigTable[SG_2D_FIR_ID]);

		// obtain the memory location for storing the settings of shared memory
		xc_get_shmem(iface, "coef_buffer", (void **) &shram);
		init_done = 1;
	}

  print("Enter Integer Coefficients (in the range 63 >= x >= -64), Enter 'x' to exit:\n\r");
  for (i=0;i<5;i++){
    for (j=4;j>=0;j--){
      k = i*5+j;
      ivk_read_fir_2d_coefficients(k);
      print("Coef] ");
      getString(buf);
      val = atoi(buf);
      if (buf[0]=='x') {
    	  print("\r\n Exit 2D FIR Coefficient Definition\n\r");
    	  return;
      }
      if (val || (buf[0]==48)) {
        // Disable the update to the core
        ivk_disable_fir_2d_coef_update();
        // write value to the shared memory
        status = xc_write(iface, xc_get_addr(shram->addr, k), (const unsigned) val); 
        if(status == XC_FAILURE) { print("Error Writing to 2D FIR Coefficients\n\r"); return; }
        // Trigger the update to the core
        ivk_enable_fir_2d_coef_update();
      }
    }
  }
  print("\r\n Loaded 2D FIR with User Defined Coefficients\n\r");
  ivk_read_fir_2d_coefficients(27);
}


void ivk_read_fir_2d_coefficients(Xint32 highlight)
{
  Xuint32 i, j;

  xc_status_t status = XC_FAILURE;
  uint32_t value;
  static xc_iface_t *iface;
  static xc_shram_t *shram; // coef_buffer
  static int init_done = 0;

  // initialize the software driver
	if (!init_done)
	{
		xc_create(&iface, &SG_2D_FIR_PLBW_ConfigTable[SG_2D_FIR_ID]);

		// obtain the memory location for storing the settings of shared memory "shram1"
		xc_get_shmem(iface, "coef_buffer", (void **) &shram);
		init_done = 1;
	}

  print("\n\r");
  for(i=0; i<5; i++)
  { 
    for(j=0; j<5; j++)
    {            
      // read data from the shared memory "shram" and store at value
      status = xc_read(iface, xc_get_addr(shram->addr, i*5+j), &value);
      if(status == XC_FAILURE) { xil_printf("Error Reading from RGB_2D_FIR_COEF_BUFFER (%d)\n\r",status); return; }
      else if ((i*5+j) == highlight) { xil_printf("[%3d] ",signExtInt(value,XPAR_SG_2D_FIR_PLBW_0_MEMMAP_COEF_BUFFER_N_BITS)); }
      else                           { xil_printf(" %3d, ",signExtInt(value,XPAR_SG_2D_FIR_PLBW_0_MEMMAP_COEF_BUFFER_N_BITS)); }
    }
    print("\n\r");
  }
  print("\n\r");
}


void ivk_load_fir_2d_gain(Xint32 mode)
{
  xc_status_t status = XC_FAILURE;
  static xc_iface_t *iface;
  static xc_to_reg_t *cg_reg; // coef_gain
  static int init_done = 0;

  // initialize the software driver, assuming the Pcore device ID is 0
	if (!init_done)
	{
		xc_create(&iface, &SG_2D_FIR_PLBW_ConfigTable[SG_2D_FIR_ID]);

		// obtain the memory location for storing the settings of the to-regs
		xc_get_shmem(iface, "coef_gain", (void **) &cg_reg);
		init_done = 1;
	}
  
  // write value to the "din" port of the to-reg
  status = xc_write(iface, cg_reg->din, gain[mode]); 
  if(status == XC_FAILURE) { print("Error Writing to RGB_2D_FIR_COEF_GAIN\n\r"); return; }

  print("Loaded 2D FIR Gain with ");
  print_UFix20_17((Xuint32)gain[mode]);
  print("\n\r");
}


void ivk_step_fir_2d_gain(Xint32 delta)
{
  uint32_t new_gain;

  xc_status_t status = XC_FAILURE;
  uint32_t value;
  static xc_iface_t *iface;
  static xc_to_reg_t *cg_reg; // coef_gain
  static int init_done = 0;

  // initialize the software driver, assuming the Pcore device ID is 0
	if (!init_done)
	{
		xc_create(&iface, &SG_2D_FIR_PLBW_ConfigTable[SG_2D_FIR_ID]);

		// obtain the memory location for storing the settings of the to-reg
		xc_get_shmem(iface, "coef_gain", (void **) &cg_reg);
		init_done = 1;
	}

  // read data from coef_gain
  status = xc_read(iface, cg_reg->din, &value); 
  if(status == XC_FAILURE) { xil_printf("Error Reading from RGB_2D_FIR/COEF_GAIN (%d)\n\r",status); return; }

  new_gain = (uint32_t) (value + delta);
  if(delta < 0 && value < -delta) new_gain = value;
  else if (new_gain > 1048575) new_gain = 1048575;

  // write value to coef_gain
  status = xc_write(iface, cg_reg->din, (const unsigned) new_gain); 
  if(status == XC_FAILURE) { print("Error Writing to RGB_2D_FIR/COEF_GAIN\n\r"); return; }

  print("\n\r Loaded 2D FIR Gain with ");
  print_UFix20_17((Xuint32)new_gain);
  print("\n\r\n\r");
}


void ivk_read_fir_2d_gain(void)
{
  xc_status_t status = XC_FAILURE;
  uint32_t value;
  static xc_iface_t *iface;
  static xc_to_reg_t *cg_reg;
  static int init_done = 0;

  // initialize the software driver, assuming the Pcore device ID is 0
	if (!init_done)
	{
		xc_create(&iface, &SG_2D_FIR_PLBW_ConfigTable[SG_2D_FIR_ID]);

		// obtain the memory location for storing the settings of the to-reg
		xc_get_shmem(iface, "coef_gain", (void **) &cg_reg);
		init_done = 1;
	}
  
  // read data from the "dout" port of the to-reg and store at value
  status = xc_read(iface, cg_reg->din, &value); 
  if(status == XC_FAILURE) { xil_printf("Error Reading from RGB_2D_FIR/COEF_GAIN (%d)\n\r",status); return; }

  print("\n\r 2D FIR Gain : ");
  print_UFix20_17((Xuint32)value);
  print("\n\r\n\r");
}

void ivk_disable_fir_2d_coef_update(void)
{
  xc_status_t status = XC_FAILURE;
  static xc_iface_t *iface;
  static xc_to_reg_t *cu_reg; // coef_update
  static int init_done = 0;

  // initialize the software driver, assuming the Pcore device ID is 0
	if (!init_done)
	{
		xc_create(&iface, &SG_2D_FIR_PLBW_ConfigTable[SG_2D_FIR_ID]);

		// obtain the memory location for coef_update
		xc_get_shmem(iface, "coef_update", (void **) &cu_reg);
		init_done = 1;
	}

  // Disable update
  status = xc_write(iface, cu_reg->din, 0); 
  if(status == XC_FAILURE) { print("Error Writing to RGB_2D_FIR/COEF_UPDATE\n\r"); return; }
}


void ivk_enable_fir_2d_coef_update(void)
{
  xc_status_t status = XC_FAILURE;
  static xc_iface_t *iface;
  static xc_to_reg_t *cu_reg; // coef_update
  static int init_done = 0;

  // initialize the software driver, assuming the Pcore device ID is 0
	if (!init_done)
	{
		xc_create(&iface, &SG_2D_FIR_PLBW_ConfigTable[SG_2D_FIR_ID]);

		// obtain the memory location for coef_update
		xc_get_shmem(iface, "coef_update", (void **) &cu_reg);
		init_done = 1;
	}

  // Enable update
  status = xc_write(iface, cu_reg->din, 1); 
  if(status == XC_FAILURE) { print("Error Writing to RGB_2D_FIR/COEF_UPDATE\n\r"); return; }
}


//////////////////////////////////////////////////////////////////////////////
// Utilities
//////////////////////////////////////////////////////////////////////////////

Xfloat64 UFix20_17_to_double(Xuint32 val)
{
  Xfloat64 out;
  Xfloat64 temp;
  temp = 131072.0;
  out = temp/131072.0;
  return out;
}

Xuint32 double_to_UFix20_17(Xfloat64 val) 
{
 	// Convert float to xfix, and compute the reciprocal
	// 2^17 = 131072
	Xuint32 out;
	out = val*131072;
	return out;
}

// Scaled by 1000000, used to convert ufix20_17 to string 7 sig fig.
static const Xuint32 binptLut[17] = {
  5000000, 2500000, 1250000, 625000, 312500, 156250, 
  78125, 39062, 19531, 9765, 4882, 2441, 1220, 610,
  305, 152, 76};
static const Xuint32 VOPMSB = 0x80000000;
static const Xuint32 VOPBINPTMASK=0xFFFE0000; 

void print_UFix20_17(Xuint32 i){
  Xint32 l;
  Xint32 x = 1000000;
  Xuint32 t;
  Xuint32 binpt;	
  binpt = i << 15;
  t=0;
  for (l=0;l<16;l++){
    if ((VOPMSB & binpt)!=0) {
      t = t + binptLut[l];
      }
    binpt = binpt << 1;
  }
  xil_printf("%d.",(VOPBINPTMASK & i)>>17); 
  if(t>0) { while (t < x) { print("0"); x=x/10; } }
  xil_printf("%d",t);  
}

//---- sign exted a val to a given width
Xint32 signExtInt(Xint32 val,Xint32 width) 
{
  Xint32 pad;
  Xint32 mask;
  Xint32 out;
  mask = 1 << (width-1);
  if ((mask & val) > 0) {
    pad = 0xFFFFFFFF << width;
    out = (val | pad);
  } else {
    out = val;
  }
  return out;
}

/*
 * Gets a string from stdin. Max length of string is 
 * INPUTBUFSIZE chars. Terminated with carriage return.
 * String is null terminated.
 */
void getString(Xuint8* s)
{
  Xint8 c;
  Xint32 idx;
  idx=0;
  c=0;
  while ((c!=13) && (c!=10)){
    if (idx>((INPUTBUFSIZE*4)-2))  idx=0;
    c=inbyte(); 
    xil_printf("%c",c);
    s[idx++]=c;
    // If backspace was pressed ...
    if (c==8)
    { 
      idx--;
      if (idx<0); idx=0;
    }
  }
  print("\n\r");
  s[idx]=0;
}
