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
// Create Date:         Nov 11, 2009
// Design Name:         FMC IPMI
// Module Name:         fmc_ipmi_iic.h
// Project Name:        FMC IPMI
// Target Devices:      Spartan-6
// Avnet Boards:        FMC-IMAGEOV, FMC-DVI/DP, FMC-ISM
//
// Tool versions:       ISE 11.4
//
// Description:         FMC IPMI IIC driver
//
// Dependencies:        
//
// Revision:            Nov 11, 2009: 1.00 Initial version
//
//----------------------------------------------------------------

#ifndef __FMC_IPMI_IIC_H__
#define __FMC_IPMI_IIC_H__

#include <stdio.h>

// I2C Functions
int fmc_ipmi_iic_init( Xuint32 CoreAddress );
int fmc_ipmi_iic_write(Xuint32 CoreAddress, Xuint8 ChipAddress, Xuint8 RegAddress, 
                       Xuint8 *BufferPtr, Xuint8 ByteCount);
int fmc_ipmi_iic_read (Xuint32 CoreAddress, Xuint8 ChipAddress, Xuint8 RegAddress, 
                       Xuint8 *BufferPtr, Xuint8 ByteCount);

#endif // __FMC_IPMI_IIC_H__
