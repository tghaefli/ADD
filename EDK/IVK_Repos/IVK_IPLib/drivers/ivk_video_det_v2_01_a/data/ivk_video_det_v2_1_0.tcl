## ----------------------------------------------------------------
##      _____
##     /     \
##    /____   \____
##   / \===\   \==/
##  /___\===\___\/  AVNET
##       \======/
##        \====/    
## ----------------------------------------------------------------
##
## This design is the property of Avnet.  Publication of this
## design is not authorized without written consent from Avnet.
## 
## Please direct any questions to:  technical.support@avnet.com
##
## Disclaimer:
##    Avnet, Inc. makes no warranty for the use of this code or design.
##    This code is provided  "As Is". Avnet, Inc assumes no responsibility for
##    any errors, which may appear in this code, nor does it make a commitment
##    to update the information contained herein. Avnet, Inc specifically
##    disclaims any implied warranties of fitness for a particular purpose.
##                     Copyright(c) 2010 Avnet, Inc.
##                             All rights reserved.
##
## ----------------------------------------------------------------
##
## Create Date:         Feb 18, 2010
## Design Name:         IVK
## Module Name:         ivk_video_det
## Project Name:        IVK
## Target Devices:      Spartan-6
## Avnet Boards:        IVK
##
## Tool versions:       ISE 11.4
##
## Description:         TCL
##
## Dependencies:        
##
## Revision:            Feb 18, 2010: 1.00 Initial Version
##
## ----------------------------------------------------------------

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "ivk_video_det" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
