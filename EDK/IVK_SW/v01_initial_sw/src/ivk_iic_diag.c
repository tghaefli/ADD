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
// Module Name:         ivk_iic_diag.c
// Project Name:        IVK_IIC_DIAG
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-IMAGEOV
//
// Tool versions:       ISE 11.4
//
// Description:         IVK IIC Diagnostics Menu
//                      - based on vsk_iic_diag.c
//                      - modified as follows:
//                         - renamed to ivk_iic_diag
//                         - 
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
// Filename            : vsk_iic_diag.c
// $Revision:: 3121   $: Revision of last commit
// $Date:: 2008-07-29#$: Date of last commit
// Description         : VSK IIC Diagnostics Menu
//******************************************************************************/

#include "ivk_iic_diag.h"

#include "fmc_imageov.h"
extern fmc_imageov_t fmc_imageov;

#define OV9710_IIC_ADDR  0x30 // 0x60/0x61


static Xint8 * iic_device[MAX_IIC_DEV]=
{
  "iic_dvi_out (TFP410)"  
 ,"iic_clk_gen (CDCE925)"
 ,"iic_fmc_mux (PCA9546)"
 ,"iic_camera_1 (OV9710)"
 ,"iic_camera_2 (OV9710)"
 ,"iic_edid_dvi_out"
} ;

static Xint8 iic_addr[MAX_IIC_DEV]=
{
  FMC_IMAGEOV_TFP410_ADDR 
 ,FMC_IMAGEOV_CDCE925_ADDR
 ,FMC_IMAGEOV_I2C_MUX_ADDR
 ,OV9710_IIC_ADDR
 ,OV9710_IIC_ADDR
 ,FMC_IMAGEOV_DDCEDID_ADDR
} ;


void ivk_iic_diag_help(void);
Xuint8 get_camera_addr( fmc_imageov_t *pModule, Xint32 camera );


/*****************************************************************************
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
Xint32 ivk_iic_diag_main ( fmc_imageov_t *pModule )
{ 
  Xint32 inchar;
  Xint32 i;
  static Xint32  data=0, addr=0, device=0;
  Xuint8 xdata[2];
  Xint8 mux_data;
  Xuint8  num_bytes;

  Xuint8 camera1_addr = 0xFF; // Not a valid address. 
  Xuint8 camera2_addr = 0xFF; // Means the camera has not been checked for.

  xdata[1] = 0; xdata[0] = 0;

  ivk_iic_diag_help();

  while (1)
  {
    print(">");

    inchar = inbyte();

    if(inchar != 0x1b) { xil_printf("%c\n\r",inchar); }
    else               { print("esc\n\r"); }

    switch (inchar)
    {
      case '?' : 
      {
        ivk_iic_diag_help(); 
        break;
      }          

      case 0x1b :
      {
        xil_printf("- exit menu -\n\n\r");
        return(0);
        break;
      }

	  // scan
	  case 's' :
      {
        Xuint8 iic_mux;
        Xuint8 iic_addr;
        Xuint8 iic_data;
        Xuint8 num_bytes;

        // Scan for devices
        xil_printf( "Scanning for I2C devices on FMC-IMAGEOV module ...\n\r" );
        for ( iic_mux = FMC_IMAGEOV_I2C_MIN; iic_mux <= FMC_IMAGEOV_I2C_MAX; iic_mux++ )
        {
          xil_printf( "\tMux Select = %d\n\r", iic_mux );
          fmc_imageov_iic_mux( pModule, iic_mux );
          for ( iic_addr = 0; iic_addr < 128; iic_addr++ )
          {
            num_bytes = pModule->pIIC->fpIicRead( pModule->pIIC, iic_addr, 0, &iic_data, 1); 
            if ( num_bytes > 0 )
            {
              xil_printf( "\t\tFound device at address 0x%02X\n\r", iic_addr );
            }
          }
        }
        break;
      }

      // device 
      case '=' :
      {
        device++; 
        if(device>MAX_IIC_DEV-1){ device=MAX_IIC_DEV-1; }
        xil_printf("device[%x]:IIC(0x%x):<%s> regs\n \r", device ,iic_addr[device],iic_device[device]);
        break;
      }
        
      case '-' :
      {
        device--; 
        if(device<0) { device=0; }
        xil_printf("device[%x]:IIC(0x%x):<%s> regs,  \n \r", device ,iic_addr[device],iic_device[device]);
        break;
      }

      // addr
      case ']' :
      {
        addr++; 
        if(addr>0xff){ addr=0xff; }
        xil_printf("IIC_reg[%x][%x] = <%s>\n\r",device, addr, iic_device[device]);
        break;
      }

      case '[' :
      {
        addr--; 
        if(addr<0){ addr=0; }
        xil_printf("IIC_reg[%x][%x] = <%s>\n\r",device, addr, iic_device[device]);      
        break;
      }
      
      case '}' :
      {
        addr+=0x10; 
        if(addr>0xff){ addr=0xff; }
        xil_printf("IIC_reg[%x][%x] = <%s>\n\r",device, addr, iic_device[device]);
        break;
      }

      case '{' :
      {
        addr-=0x10; 
        if(addr<0){ addr=0; }
        xil_printf("IIC_reg[%x][%x] = <%s>\n\r",device, addr, iic_device[device]);      
        break;
      }

      // data
      case '\'' :
      {
        data++;  
        xdata[1] = (Xint8)(data & 0xFF);
        xdata[0] = (Xint8)((data>>8) & 0xFF);        
        xil_printf("data=0x%x\n\r",data);
//        xil_printf("xdata=0x%x %x\n\r",xdata[0],xdata[1]);
        break;
      }
        
      case ';' :
      {
        data--;
        xdata[1] = (Xint8)(data & 0xFF);
        xdata[0] = (Xint8)((data>>8) & 0xFF);        
        xil_printf("data=0x%x\n\r",data);
//        xil_printf("xdata=0x%x %x\n\r",xdata[0],xdata[1]);
        break;
      }

      case '\"' :
      {
        data=data+0x100;  
        xdata[1] = (Xint8)(data & 0xFF);
        xdata[0] = (Xint8)((data>>8) & 0xFF);        
        xil_printf("data=0x%x\n\r",data);
//        xil_printf("xdata=0x%x %x\n\r",xdata[0],xdata[1]);
        break;
      }

      case ':' :
      {
        data=data-0x100;
        xdata[1] = (Xint8)(data & 0xFF);
        xdata[0] = (Xint8)((data>>8) & 0xFF);        
        xil_printf("data=0x%x\n\r",data);
//        xil_printf("xdata=0x%x %x\n\r",xdata[0],xdata[1]);
        break;
      }

      // write register
      case '.' : 
      {
        num_bytes = 1;
        if(device ==IIC_DVI_OUT)
        {
          fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_TFP410 );
          num_bytes = pModule->pIIC->fpIicWrite( pModule->pIIC, iic_addr[device], 
                                                 addr, &xdata[1], 1); 
        }
        else if(device ==IIC_CLK_GEN)
        {
          fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CDCE925 );
          num_bytes = pModule->pIIC->fpIicWrite( pModule->pIIC, iic_addr[device], 
                                                 addr, &xdata[1], 1); 
        }
        else if(device ==IIC_CAMERA_1) 
        { 
          if (camera1_addr == 0xFF || camera1_addr == 0x00)
          {
            camera1_addr = get_camera_addr( pModule, 1 );
          }
          if (camera1_addr != 0)
          {
            fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
            num_bytes = pModule->pIIC->fpIicWrite( pModule->pIIC, iic_addr[device], 
                                                   addr, &xdata[1], 1); 
          }
          else { print("Camera #1 is not present.\r\n"); break; }        
        }
        else if(device ==IIC_CAMERA_2) 
        { 
          if (camera2_addr == 0xFF || camera2_addr == 0x00)
          {
            camera2_addr = get_camera_addr( pModule, 2 );
          }
          if (camera2_addr != 0)
          {
            fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
            num_bytes = pModule->pIIC->fpIicWrite( pModule->pIIC, iic_addr[device], 
                                                   addr, &xdata[1], 1); 
          }
          else  { print("Camera #2 is not present.\r\n"); break; }
        }
        else if(device ==IIC_EDID_DVI_OUT)
        {
          fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_EDID );
          num_bytes = pModule->pIIC->fpIicWrite( pModule->pIIC, iic_addr[device], 
                                                 addr, &xdata[1], 1); 
        }
        
        else 
        { 
          num_bytes = pModule->pIIC->fpIicWrite( pModule->pIIC, iic_addr[device], 
                                                 addr, &xdata[1], 1); 
        }

        if (num_bytes < 1) 
        {
          xil_printf("\r\nError writing to device<%s> = %d \r\n\r\n",iic_device[device],num_bytes);
        }
        else
        {
          if (device ==IIC_CAMERA_1 || device ==IIC_CAMERA_2)
          {
            xil_printf("write IIC_reg[0x%x][0x%x]=0x%x (%d) \n\r",iic_addr[device],addr,data,data);
          }
          else
          {
            xil_printf("write IIC_reg[0x%x][0x%x]=0x%x (%d) \n\r",iic_addr[device],addr,(data&0xFF),(data&0xFF));
          }                  
        }

        break;
      }
     
      // read register
      case ',' : 
      {
        num_bytes = 1;
        if(device ==IIC_DVI_OUT)
        {
          fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_TFP410 );
          num_bytes = pModule->pIIC->fpIicRead( pModule->pIIC, iic_addr[device], 
                                                addr, &xdata[1], 1);
          data = (int)xdata[1];                                                        
        }
        else if(device ==IIC_CLK_GEN)
        {
          fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CDCE925 );
          num_bytes = pModule->pIIC->fpIicRead( pModule->pIIC, iic_addr[device], 
                                                addr, &xdata[1], 1);
          data = (int)xdata[1];                                                        
        }
        else if(device ==IIC_CAMERA_1) 
        { 
          if (camera1_addr == 0xFF || camera1_addr == 0x00)
          {
            camera1_addr = get_camera_addr( pModule, 1 );
          }
          if (camera1_addr != 0)
          {
            fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
            num_bytes = pModule->pIIC->fpIicRead( pModule->pIIC, iic_addr[device], 
                                                  addr, &xdata[1], 1);
            data = (int)xdata[1];
          }            
          else  { print("Camera #1 is not present.\r\n"); break; }
        }
        else if(device ==IIC_CAMERA_2) 
        { 
          if (camera2_addr == 0xFF || camera2_addr == 0x00)
          {
            camera2_addr = get_camera_addr( pModule, 2 );
          }
          if (camera2_addr != 0)
          {
            fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
            num_bytes = pModule->pIIC->fpIicRead( pModule->pIIC, iic_addr[device], 
                                                  addr, &xdata[1], 1);
            data = (int)xdata[1];
          }            
          else  { print("Camera #2 is not present.\r\n"); break; }
        }
        else if(device ==IIC_EDID_DVI_OUT)
        {
          fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_EDID );
          num_bytes = pModule->pIIC->fpIicRead( pModule->pIIC, iic_addr[device], 
                                                addr, &xdata[1], 1);
          data = (int)xdata[1];                                                        
        }
        else 
        { 
          num_bytes = pModule->pIIC->fpIicRead( pModule->pIIC, iic_addr[device], 
                                                addr, &xdata[1], 1);
          data = (int)xdata[1]; 
        }

        if (num_bytes < 1) 
        {
          xil_printf("\r\nError reading from device<%s> = %d \r\n\r\n",iic_device[device],num_bytes);
        }
        else
        {        
          if (device ==IIC_CAMERA_1 || device ==IIC_CAMERA_2)
          {
            xil_printf("read IIC_reg[0x%x][0x%x]=0x%x (%d) \n\r",iic_addr[device],addr,data,data);
          }
          else
          {
            xil_printf("read IIC_reg[0x%x][0x%x]=0x%x (%d) \n\r",iic_addr[device],addr,(data&0xFF),(data&0xFF));
          }                  
        }
        
        break;
      }
      
      // Dump All Device Registers
      case 'd' : 
      {
        num_bytes = 1;
        xil_printf("display device memory: device[%x]=<%s>\r\n\r\n",device, 
                    iic_device[device]); 

        // Setup the FMC IIC MUX if needed
        if(device ==IIC_DVI_OUT)
        {
          fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_TFP410 );
        }
        else if(device ==IIC_CLK_GEN)
        {
          fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CDCE925 );
        }
        else if(device ==IIC_CAMERA_1) 
        {
          if (camera1_addr == 0xFF || camera1_addr == 0x00)
          {
            camera1_addr = get_camera_addr( pModule, 1 );
          }
          if (camera1_addr != 0)
          {
            fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
          }
          else  { print("Camera #1 is not present.\r\n"); break; }          
        }
        else if(device ==IIC_CAMERA_2) 
        {
          if (camera2_addr == 0xFF || camera2_addr == 0x00)
          {
            camera2_addr = get_camera_addr( pModule, 2 );
          }
          if (camera2_addr != 0)
          {
            fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
          }
          else  { print("Camera #2 is not present.\r\n"); break; }          
        }
        else if(device ==IIC_EDID_DVI_OUT)
        {
          fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_EDID );
        }
        

        // Read registers 0x00 - 0xFF
        for(i=0; i<=0xFF; i++) 
        {
          addr = (Xuint8)i;
          num_bytes = pModule->pIIC->fpIicRead( pModule->pIIC, iic_addr[device], 
                                                addr, &xdata[1], 1);
          data = (int)xdata[1];
          
          if (num_bytes < 1) 
          {
            xil_printf("\r\nError reading from device<%s> \r\n\r\n",iic_device[device]);
            break;
          }
          else
          {        
            xil_printf("read IIC_reg[%x][%x]=0x%x (%d) \n\r",device,i,data,data);  
          }          
        }

        break;
      }      
    }
  }
}


void ivk_iic_diag_help(void)
{
  print("\n\r");
  print("----------------------------\n\r");
  print("--  IIC Diagnostics Menu  --\r\n");
  print("----------------------------\n\r");
  print("key(s)  description               \n\r");
  print("----------------------------\n\r");
  print(" s =  scan for devices\n\r");
  print(" - =  select device   \n\r");
  print(" [ ]  select register \n\r");
  print(" ; \'  data -/+ 0x001 \n\r");
  print(" : \"  data -/+ 0x100 \n\r");
  print("  .   write device[register]=data \n\r");
  print("  ,   read  device[register]\n\r");
  print("\n\r");
  print("  d   display device regs  \n\r");
  print("\n\r");
  print(" esc quit \n\r");
  print("  ?   help \n\r");
  print("----------------------------\n\r");
}


/*********************************************************************
**
* This function gets the addr of the specified camera.
*
* @param    camera port to check.
*            1 = Camera 1
*            2 = Camera 2
*
* @return   I2C address of the camera
*            I2C address of the camera = Source Present
*            0 = Source Not Present
*
* @note None.
*
**********************************************************************
*/
Xuint8 get_camera_addr( fmc_imageov_t *pModule, Xint32 camera )
{
  Xuint8 iic_data;
  Xuint8 num_bytes;
  Xuint8 camera_addr;

  if ( camera == 1 )
  {
    fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CAMERA1 );
  }
  else
  {
    fmc_imageov_iic_mux( pModule, FMC_IMAGEOV_I2C_SELECT_CAMERA2 );
  }

  // Check for presence of OV9710 image sensor
  num_bytes = pModule->pIIC->fpIicRead( pModule->pIIC, OV9710_IIC_ADDR, 0, &iic_data, 1); 
  if ( num_bytes > 0 )
  {
    return OV9710_IIC_ADDR;
  }
  else
  {
    return 0;
  }
  
  return camera_addr;
}

