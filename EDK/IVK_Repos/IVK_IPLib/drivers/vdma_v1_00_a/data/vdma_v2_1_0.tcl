###############################################################
# Copyright (c) 2008 Xilinx, Inc. All Rights Reserved.
# You may copy and modify these files for your own internal use solely with
# Xilinx programmable logic devices and  Xilinx EDK system or create IP
# modules solely for Xilinx programmable logic devices and Xilinx EDK system.
# No rights are granted to distribute any files unless they are distributed in
# Xilinx programmable logic devices.
###############################################################
#uses "xillib.tcl"

proc generate {drv_handle} {
    xdefine_include_file $drv_handle "xparameters.h" "XVDma" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" "C_NUM_FSTORES"
    local_xdefine_config_file $drv_handle "xvdma_g.c" "XVDma" "DEVICE_ID" "C_BASEADDR" "C_NUM_FSTORES"
    xdefine_canonical_xpars $drv_handle "xparameters.h" "VDma" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" "C_NUM_FSTORES"
}

#
# Create configuration C file as required by Xilinx  drivers
# Temporary fix until 11.1

proc local_xdefine_config_file {drv_handle file_name drv_string args} {
    set filename [file join "src" $file_name] 
    file delete $filename
    set config_file [open $filename w]
    xprint_generated_header $config_file "Driver configuration"    
    puts $config_file "#include \"xparameters.h\""
    puts $config_file "#include \"[string tolower $drv_string].h\""
    puts $config_file "\n/*"
    puts $config_file "* The configuration table for devices"
    puts $config_file "*/\n"
    puts $config_file [format "%s_Config %s_ConfigTable\[\] =" $drv_string $drv_string]
    puts $config_file "\{"
    set periphs [xget_periphs $drv_handle]     
    set start_comma ""
    foreach periph $periphs {
	puts $config_file [format "%s\t\{" $start_comma]
	set comma ""
	foreach arg $args {
            puts "Handling $arg"
	    # Check if this is a driver parameter or a peripheral parameter
	    set value [xget_value $drv_handle "PARAMETER" $arg]
	    if {[llength $value] == 0} {
		set p2p_name [xget_p2p_name $periph $arg]
                # puts "p2p_name is: $p2p_name"
                set p2p_name ""

		if { [string compare -nocase $p2p_name ""] == 0} { 
		    puts -nonewline $config_file [format "%s\t\t%s" $comma [xget_name $periph $arg]]
		} else {
		    puts -nonewline $config_file [format "%s\t\t%s" $comma $p2p_name]
		}
	    } else {
		puts -nonewline $config_file [format "%s\t\t%s" $comma [xget_dname $drv_string $arg]]
	    }
	    set comma ",\n"
	}
	puts -nonewline $config_file "\n\t\}"
	set start_comma ",\n"
    }
    puts $config_file "\n\};"

    puts $config_file "\n";

    close $config_file
}

#
# Given a list of arguments, define each as a canonical constant name, using
# the driver name, in an include file.
#
proc xdefine_canonical_xpars {drv_handle file_name drv_string args} {
    # Open include file
    set file_handle [xopen_include_file $file_name]

    # Get all the peripherals connected to this driver
    set periphs [xget_periphs $drv_handle]

    # Get the names of all the peripherals connected to this driver
    foreach periph $periphs {
        set peripheral_name [string toupper [xget_hw_name $periph]]
        lappend peripherals $peripheral_name
    }

    # Get possible canonical names for all the peripherals connected to this driver
    set device_id 0
    foreach periph $periphs {
        set canonical_name [string toupper [format "%s_%s" $drv_string $device_id]]
        lappend canonicals $canonical_name
        
        # Create a list of IDs of the peripherals whose hardware instance name
        # doesn't match the canonical name. These IDs can be used later to
        # generate canonical definitions
        if { [lsearch $peripherals $canonical_name] < 0 } {
            lappend indices $device_id
        }
        incr device_id
    }

    set i 0
    foreach periph $periphs {
        set periph_name [string toupper [xget_hw_name $periph]]

        # Generate canonical definitions only for the peripherals whose
        # canonical name is not the same as hardware instance name
        if { [lsearch $canonicals $periph_name] < 0 } {
            puts $file_handle "/* Canonical definitions for peripheral $periph_name */"
            set canonical_name [format "%s_%s" $drv_string [lindex $indices $i]]

            foreach arg $args {
                set lvalue [xget_dname $canonical_name $arg]

    # The commented out rvalue is the name of the instance-specific constant
    #           set rvalue [xget_name $periph $arg]

                # The rvalue set below is the actual value of the parameter
                set rvalue [xget_param_value $periph $arg]
                if {[llength $rvalue] == 0} {
                    set rvalue 0
                }
                set rvalue [xformat_addr_string $rvalue $arg]
    
                puts $file_handle "#define $lvalue $rvalue"

            }
            puts $file_handle ""
            incr i
        }
    }

    puts $file_handle "\n/******************************************************************/\n"
    close $file_handle
}
