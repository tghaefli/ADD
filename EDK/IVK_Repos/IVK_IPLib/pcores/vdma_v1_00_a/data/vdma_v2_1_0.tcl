#############################################################################
##
## Copyright (c) 2007 Xilinx, Inc. All Rights Reserved.
##
## mpmc_v2_1_0.tcl
##
#############################################################################

## @BEGIN_CHANGELOG EDK_J_SP2 
##
## - init 1.00.a version
##
## @END_CHANGELOG




#***--------------------------------***-----------------------------------***
#
#			     CORE_LEVEL_CONSTRAINTS
#
#***--------------------------------***-----------------------------------***


proc generate_corelevel_ucf {mhsinst} {

    set  filePath [xget_ncf_dir $mhsinst]

    file mkdir    $filePath

    # specify file name
    set    instname   [xget_hw_parameter_value $mhsinst "INSTANCE"]
    set    ipname     [xget_hw_option_value    $mhsinst "IPNAME"]
    set    name_lower [string   tolower   $instname]
    set    fileName   $name_lower
    append fileName   "_wrapper.ucf"
    append filePath   $fileName

    # Open a file for writing
    set    outputFile [open $filePath "w"]

    set C_FAMILY [xget_hw_parameter_value $mhsinst "C_FAMILY"]
    set C_DMA_TYPE [xget_hw_parameter_value $mhsinst "C_DMA_TYPE"]
    set C_WRITE_GENLOCK_MODE [xget_hw_parameter_value $mhsinst "C_WRITE_GENLOCK_MODE"]
    set C_READ_GENLOCK_MODE [xget_hw_parameter_value $mhsinst "C_READ_GENLOCK_MODE"]

    ##############################################################################
    # Write
    ##############################################################################
    if {[string compare -nocase $C_DMA_TYPE "READ_ONLY"] != 0 && [string compare -nocase $C_WRITE_GENLOCK_MODE "SLAVE"] == 0} { 
 
      set vdma_wd_clk_port [xget_hw_port_handle $mhsinst "vdma_wd_clk"]
      set vdma_wd_clk_frequency [xget_hw_subproperty_value $vdma_wd_clk_port "CLK_FREQ_HZ"]
      
      if {[string length $vdma_wd_clk_frequency] == 0} {
          set vdma_wd_clk_frequency 148500000
        
          if {[string match -nocase *virtex4* $C_FAMILY]} {
            set vdma_wd_clk_frequency 200000000
          } elseif {[string match -nocase *virtex5* $C_FAMILY]} {
            set vdma_wd_clk_frequency 266666666
          }
  
          set vdma_wd_clk_period_ps [expr 1000000000000/${vdma_wd_clk_frequency}]   
          puts "vdma (${instname}): Setting Clock Period to Default $vdma_wd_clk_period_ps ps "     
      } else {
        set vdma_wd_clk_period_ps [expr 1000000000000/${vdma_wd_clk_frequency}]   
        puts "vdma (${instname}): Setting Clock Period to $vdma_wd_clk_period_ps ps via CLK_FREQ_HZ Property"     
      }


      #puts $outputFile "NET \"*${instname}/*/*wd_frame_ptr_in_sync*\" TNM = \"${instname}_wd_gen_lock_dest_grp\";"
      #puts $outputFile "TIMESPEC \"TS_${instname}_wd_gen_lock_grp\" = FROM FFS to \"${instname}_wd_gen_lock_dest_grp\" ${vdma_wd_clk_period_ps} ps DATAPATHONLY;"
      
      puts $outputFile "NET \"*${instname}/USER_LOGIC_I/VDMA_TOP_I/wd_frame_ptr_in_sync<0>*\" TNM = \"${instname}_wd_gen_lock_dest_grp\";"
      #puts $outputFile "TIMESPEC \"TS_${instname}_wd_gen_lock_grp\" = FROM FFS to \"${instname}_wd_gen_lock_dest_grp\" [expr ${vdma_wd_clk_period_ps}*2] ps;"
      puts $outputFile "TIMESPEC \"TS_${instname}_wd_gen_lock_grp\" = FROM FFS to \"${instname}_wd_gen_lock_dest_grp\" ${vdma_wd_clk_period_ps} ps;"
      
    } 
    ##############################################################################
    # Read
    ##############################################################################
    if {[string compare -nocase $C_DMA_TYPE "WRITE_ONLY"] != 0 && [string compare -nocase $C_READ_GENLOCK_MODE "SLAVE"] == 0} { 
      set vdma_rd_clk_port [xget_hw_port_handle $mhsinst "vdma_rd_clk"]
      set vdma_rd_clk_frequency [xget_hw_subproperty_value $vdma_rd_clk_port "CLK_FREQ_HZ"]
      
      if {[string length $vdma_rd_clk_frequency] == 0} {
          set vdma_rd_clk_frequency 148500000
        
          if {[string match -nocase *virtex4* $C_FAMILY]} {
            set vdma_rd_clk_frequency 200000000
          } elseif {[string match -nocase *virtex5* $C_FAMILY]} {
            set vdma_rd_clk_frequency 266666666
          }
  
          set vdma_rd_clk_period_ps [expr 1000000000000/${vdma_rd_clk_frequency}]   
          puts "vdma (${instname}): Setting Clock Period to Default $vdma_rd_clk_period_ps ps "     
      } else {
        set vdma_rd_clk_period_ps [expr 1000000000000/${vdma_rd_clk_frequency}]   
        puts "vdma (${instname}): Setting Clock Period to $vdma_rd_clk_period_ps ps via CLK_FREQ_HZ Property"     
      }

      #puts $outputFile "NET \"*${instname}/*/*rd_frame_ptr_in_sync*\" TNM = \"${instname}_rd_gen_lock_dest_grp\";"
      #puts $outputFile "TIMESPEC \"TS_${instname}_rd_gen_lock_grp\" = FROM FFS to \"${instname}_rd_gen_lock_dest_grp\" ${vdma_rd_clk_period_ps} DATAPATHONLY;"
      puts $outputFile "NET \"*${instname}/USER_LOGIC_I/VDMA_TOP_I/rd_frame_ptr_in_sync<0>*\" TNM = \"${instname}_rd_gen_lock_dest_grp\";"
      puts $outputFile "TIMESPEC \"TS_${instname}_rd_gen_lock_grp\" = FROM FFS to \"${instname}_rd_gen_lock_dest_grp\" ${vdma_rd_clk_period_ps};"
    } 

    # Close the file
    close $outputFile
    #puts  [xget_ncf_loc_info $mhsinst]

}


