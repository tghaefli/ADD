--------------------------------------------------------------------------------
--     This file is owned and controlled by Xilinx and must be used           --
--     solely for design, simulation, implementation and creation of          --
--     design files limited to Xilinx devices or technologies. Use            --
--     with non-Xilinx devices or technologies is expressly prohibited        --
--     and immediately terminates your license.                               --
--                                                                            --
--     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"          --
--     SOLELY FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR                --
--     XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION        --
--     AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE, APPLICATION            --
--     OR STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS              --
--     IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,                --
--     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE       --
--     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY               --
--     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE                --
--     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR         --
--     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF        --
--     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS        --
--     FOR A PARTICULAR PURPOSE.                                              --
--                                                                            --
--     Xilinx products are not intended for use in life support               --
--     appliances, devices, or systems. Use in such applications are          --
--     expressly prohibited.                                                  --
--                                                                            --
--     (c) Copyright 1995-2009 Xilinx, Inc.                                   --
--     All rights reserved.                                                   --
--------------------------------------------------------------------------------
-- You must compile the wrapper file bmg_41_99d18de731b34188.vhd when simulating
-- the core, bmg_41_99d18de731b34188. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
Library XilinxCoreLib;
-- synthesis translate_on
ENTITY bmg_41_99d18de731b34188 IS
	port (
	clka: IN std_logic;
	ena: IN std_logic;
	addra: IN std_logic_VECTOR(9 downto 0);
	douta: OUT std_logic_VECTOR(17 downto 0));
END bmg_41_99d18de731b34188;

ARCHITECTURE bmg_41_99d18de731b34188_a OF bmg_41_99d18de731b34188 IS
-- synthesis translate_off
component wrapped_bmg_41_99d18de731b34188
	port (
	clka: IN std_logic;
	ena: IN std_logic;
	addra: IN std_logic_VECTOR(9 downto 0);
	douta: OUT std_logic_VECTOR(17 downto 0));
end component;

-- Configuration specification 
	for all : wrapped_bmg_41_99d18de731b34188 use entity XilinxCoreLib.blk_mem_gen_v4_1(behavioral)
		generic map(
			c_has_regceb => 0,
			c_has_regcea => 0,
			c_mem_type => 3,
			c_rstram_b => 0,
			c_rstram_a => 0,
			c_has_injecterr => 0,
			c_rst_type => "SYNC",
			c_prim_type => 1,
			c_read_width_b => 18,
			c_initb_val => "0",
			c_family => "spartan6",
			c_read_width_a => 18,
			c_disable_warn_bhv_coll => 0,
			c_use_softecc => 0,
			c_write_mode_b => "WRITE_FIRST",
			c_init_file_name => "bmg_41_99d18de731b34188.mif",
			c_write_mode_a => "WRITE_FIRST",
			c_mux_pipeline_stages => 0,
			c_has_softecc_output_regs_b => 0,
			c_has_softecc_output_regs_a => 0,
			c_has_mem_output_regs_b => 0,
			c_has_mem_output_regs_a => 0,
			c_load_init_file => 1,
			c_xdevicefamily => "spartan6",
			c_write_depth_b => 1024,
			c_write_depth_a => 1024,
			c_has_rstb => 0,
			c_has_rsta => 0,
			c_has_mux_output_regs_b => 0,
			c_inita_val => "0",
			c_has_mux_output_regs_a => 0,
			c_addra_width => 10,
			c_has_softecc_input_regs_b => 0,
			c_has_softecc_input_regs_a => 0,
			c_addrb_width => 10,
			c_default_data => "0",
			c_use_ecc => 0,
			c_algorithm => 1,
			c_disable_warn_bhv_range => 0,
			c_write_width_b => 18,
			c_write_width_a => 18,
			c_read_depth_b => 1024,
			c_read_depth_a => 1024,
			c_byte_size => 9,
			c_sim_collision_check => "ALL",
			c_common_clk => 0,
			c_wea_width => 1,
			c_has_enb => 0,
			c_web_width => 1,
			c_has_ena => 1,
			c_use_byte_web => 0,
			c_use_byte_wea => 0,
			c_rst_priority_b => "CE",
			c_rst_priority_a => "CE",
			c_use_default_data => 0);
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_bmg_41_99d18de731b34188
		port map (
			clka => clka,
			ena => ena,
			addra => addra,
			douta => douta);
-- synthesis translate_on

END bmg_41_99d18de731b34188_a;


-------------------------------------------------------------------
-- System Generator version 12.1 VHDL source file.
--
-- Copyright(C) 2010 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2010 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
package conv_pkg is
    constant simulating : boolean := false
      -- synopsys translate_off
        or true
      -- synopsys translate_on
    ;
    constant xlUnsigned : integer := 1;
    constant xlSigned : integer := 2;
    constant xlWrap : integer := 1;
    constant xlSaturate : integer := 2;
    constant xlTruncate : integer := 1;
    constant xlRound : integer := 2;
    constant xlRoundBanker : integer := 3;
    constant xlAddMode : integer := 1;
    constant xlSubMode : integer := 2;
    attribute black_box : boolean;
    attribute syn_black_box : boolean;
    attribute fpga_dont_touch: string;
    attribute box_type :  string;
    attribute keep : string;
    attribute syn_keep : boolean;
    function std_logic_vector_to_unsigned(inp : std_logic_vector) return unsigned;
    function unsigned_to_std_logic_vector(inp : unsigned) return std_logic_vector;
    function std_logic_vector_to_signed(inp : std_logic_vector) return signed;
    function signed_to_std_logic_vector(inp : signed) return std_logic_vector;
    function unsigned_to_signed(inp : unsigned) return signed;
    function signed_to_unsigned(inp : signed) return unsigned;
    function pos(inp : std_logic_vector; arith : INTEGER) return boolean;
    function all_same(inp: std_logic_vector) return boolean;
    function all_zeros(inp: std_logic_vector) return boolean;
    function is_point_five(inp: std_logic_vector) return boolean;
    function all_ones(inp: std_logic_vector) return boolean;
    function convert_type (inp : std_logic_vector; old_width, old_bin_pt,
                           old_arith, new_width, new_bin_pt, new_arith,
                           quantization, overflow : INTEGER)
        return std_logic_vector;
    function cast (inp : std_logic_vector; old_bin_pt,
                   new_width, new_bin_pt, new_arith : INTEGER)
        return std_logic_vector;
    function vec_slice (inp : std_logic_vector; upper, lower : INTEGER)
        return std_logic_vector;
    function s2u_slice (inp : signed; upper, lower : INTEGER)
        return unsigned;
    function u2u_slice (inp : unsigned; upper, lower : INTEGER)
        return unsigned;
    function s2s_cast (inp : signed; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return signed;
    function u2s_cast (inp : unsigned; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return signed;
    function s2u_cast (inp : signed; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return unsigned;
    function u2u_cast (inp : unsigned; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return unsigned;
    function u2v_cast (inp : unsigned; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return std_logic_vector;
    function s2v_cast (inp : signed; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return std_logic_vector;
    function trunc (inp : std_logic_vector; old_width, old_bin_pt, old_arith,
                    new_width, new_bin_pt, new_arith : INTEGER)
        return std_logic_vector;
    function round_towards_inf (inp : std_logic_vector; old_width, old_bin_pt,
                                old_arith, new_width, new_bin_pt,
                                new_arith : INTEGER) return std_logic_vector;
    function round_towards_even (inp : std_logic_vector; old_width, old_bin_pt,
                                old_arith, new_width, new_bin_pt,
                                new_arith : INTEGER) return std_logic_vector;
    function max_signed(width : INTEGER) return std_logic_vector;
    function min_signed(width : INTEGER) return std_logic_vector;
    function saturation_arith(inp:  std_logic_vector;  old_width, old_bin_pt,
                              old_arith, new_width, new_bin_pt, new_arith
                              : INTEGER) return std_logic_vector;
    function wrap_arith(inp:  std_logic_vector;  old_width, old_bin_pt,
                        old_arith, new_width, new_bin_pt, new_arith : INTEGER)
                        return std_logic_vector;
    function fractional_bits(a_bin_pt, b_bin_pt: INTEGER) return INTEGER;
    function integer_bits(a_width, a_bin_pt, b_width, b_bin_pt: INTEGER)
        return INTEGER;
    function sign_ext(inp : std_logic_vector; new_width : INTEGER)
        return std_logic_vector;
    function zero_ext(inp : std_logic_vector; new_width : INTEGER)
        return std_logic_vector;
    function zero_ext(inp : std_logic; new_width : INTEGER)
        return std_logic_vector;
    function extend_MSB(inp : std_logic_vector; new_width, arith : INTEGER)
        return std_logic_vector;
    function align_input(inp : std_logic_vector; old_width, delta, new_arith,
                          new_width: INTEGER)
        return std_logic_vector;
    function pad_LSB(inp : std_logic_vector; new_width: integer)
        return std_logic_vector;
    function pad_LSB(inp : std_logic_vector; new_width, arith : integer)
        return std_logic_vector;
    function max(L, R: INTEGER) return INTEGER;
    function min(L, R: INTEGER) return INTEGER;
    function "="(left,right: STRING) return boolean;
    function boolean_to_signed (inp : boolean; width: integer)
        return signed;
    function boolean_to_unsigned (inp : boolean; width: integer)
        return unsigned;
    function boolean_to_vector (inp : boolean)
        return std_logic_vector;
    function std_logic_to_vector (inp : std_logic)
        return std_logic_vector;
    function integer_to_std_logic_vector (inp : integer;  width, arith : integer)
        return std_logic_vector;
    function std_logic_vector_to_integer (inp : std_logic_vector;  arith : integer)
        return integer;
    function std_logic_to_integer(constant inp : std_logic := '0')
        return integer;
    function bin_string_element_to_std_logic_vector (inp : string;  width, index : integer)
        return std_logic_vector;
    function bin_string_to_std_logic_vector (inp : string)
        return std_logic_vector;
    function hex_string_to_std_logic_vector (inp : string; width : integer)
        return std_logic_vector;
    function makeZeroBinStr (width : integer) return STRING;
    function and_reduce(inp: std_logic_vector) return std_logic;
    -- synopsys translate_off
    function is_binary_string_invalid (inp : string)
        return boolean;
    function is_binary_string_undefined (inp : string)
        return boolean;
    function is_XorU(inp : std_logic_vector)
        return boolean;
    function to_real(inp : std_logic_vector; bin_pt : integer; arith : integer)
        return real;
    function std_logic_to_real(inp : std_logic; bin_pt : integer; arith : integer)
        return real;
    function real_to_std_logic_vector (inp : real;  width, bin_pt, arith : integer)
        return std_logic_vector;
    function real_string_to_std_logic_vector (inp : string;  width, bin_pt, arith : integer)
        return std_logic_vector;
    constant display_precision : integer := 20;
    function real_to_string (inp : real) return string;
    function valid_bin_string(inp : string) return boolean;
    function std_logic_vector_to_bin_string(inp : std_logic_vector) return string;
    function std_logic_to_bin_string(inp : std_logic) return string;
    function std_logic_vector_to_bin_string_w_point(inp : std_logic_vector; bin_pt : integer)
        return string;
    function real_to_bin_string(inp : real;  width, bin_pt, arith : integer)
        return string;
    type stdlogic_to_char_t is array(std_logic) of character;
    constant to_char : stdlogic_to_char_t := (
        'U' => 'U',
        'X' => 'X',
        '0' => '0',
        '1' => '1',
        'Z' => 'Z',
        'W' => 'W',
        'L' => 'L',
        'H' => 'H',
        '-' => '-');
    -- synopsys translate_on
end conv_pkg;
package body conv_pkg is
    function std_logic_vector_to_unsigned(inp : std_logic_vector)
        return unsigned
    is
    begin
        return unsigned (inp);
    end;
    function unsigned_to_std_logic_vector(inp : unsigned)
        return std_logic_vector
    is
    begin
        return std_logic_vector(inp);
    end;
    function std_logic_vector_to_signed(inp : std_logic_vector)
        return signed
    is
    begin
        return  signed (inp);
    end;
    function signed_to_std_logic_vector(inp : signed)
        return std_logic_vector
    is
    begin
        return std_logic_vector(inp);
    end;
    function unsigned_to_signed (inp : unsigned)
        return signed
    is
    begin
        return signed(std_logic_vector(inp));
    end;
    function signed_to_unsigned (inp : signed)
        return unsigned
    is
    begin
        return unsigned(std_logic_vector(inp));
    end;
    function pos(inp : std_logic_vector; arith : INTEGER)
        return boolean
    is
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
    begin
        vec := inp;
        if arith = xlUnsigned then
            return true;
        else
            if vec(width-1) = '0' then
                return true;
            else
                return false;
            end if;
        end if;
        return true;
    end;
    function max_signed(width : INTEGER)
        return std_logic_vector
    is
        variable ones : std_logic_vector(width-2 downto 0);
        variable result : std_logic_vector(width-1 downto 0);
    begin
        ones := (others => '1');
        result(width-1) := '0';
        result(width-2 downto 0) := ones;
        return result;
    end;
    function min_signed(width : INTEGER)
        return std_logic_vector
    is
        variable zeros : std_logic_vector(width-2 downto 0);
        variable result : std_logic_vector(width-1 downto 0);
    begin
        zeros := (others => '0');
        result(width-1) := '1';
        result(width-2 downto 0) := zeros;
        return result;
    end;
    function and_reduce(inp: std_logic_vector) return std_logic
    is
        variable result: std_logic;
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
    begin
        vec := inp;
        result := vec(0);
        if width > 1 then
            for i in 1 to width-1 loop
                result := result and vec(i);
            end loop;
        end if;
        return result;
    end;
    function all_same(inp: std_logic_vector) return boolean
    is
        variable result: boolean;
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
    begin
        vec := inp;
        result := true;
        if width > 0 then
            for i in 1 to width-1 loop
                if vec(i) /= vec(0) then
                    result := false;
                end if;
            end loop;
        end if;
        return result;
    end;
    function all_zeros(inp: std_logic_vector)
        return boolean
    is
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
        variable zero : std_logic_vector(width-1 downto 0);
        variable result : boolean;
    begin
        zero := (others => '0');
        vec := inp;
        -- synopsys translate_off
        if (is_XorU(vec)) then
            return false;
        end if;
         -- synopsys translate_on
        if (std_logic_vector_to_unsigned(vec) = std_logic_vector_to_unsigned(zero)) then
            result := true;
        else
            result := false;
        end if;
        return result;
    end;
    function is_point_five(inp: std_logic_vector)
        return boolean
    is
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
        variable result : boolean;
    begin
        vec := inp;
        -- synopsys translate_off
        if (is_XorU(vec)) then
            return false;
        end if;
         -- synopsys translate_on
        if (width > 1) then
           if ((vec(width-1) = '1') and (all_zeros(vec(width-2 downto 0)) = true)) then
               result := true;
           else
               result := false;
           end if;
        else
           if (vec(width-1) = '1') then
               result := true;
           else
               result := false;
           end if;
        end if;
        return result;
    end;
    function all_ones(inp: std_logic_vector)
        return boolean
    is
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
        variable one : std_logic_vector(width-1 downto 0);
        variable result : boolean;
    begin
        one := (others => '1');
        vec := inp;
        -- synopsys translate_off
        if (is_XorU(vec)) then
            return false;
        end if;
         -- synopsys translate_on
        if (std_logic_vector_to_unsigned(vec) = std_logic_vector_to_unsigned(one)) then
            result := true;
        else
            result := false;
        end if;
        return result;
    end;
    function full_precision_num_width(quantization, overflow, old_width,
                                      old_bin_pt, old_arith,
                                      new_width, new_bin_pt, new_arith : INTEGER)
        return integer
    is
        variable result : integer;
    begin
        result := old_width + 2;
        return result;
    end;
    function quantized_num_width(quantization, overflow, old_width, old_bin_pt,
                                 old_arith, new_width, new_bin_pt, new_arith
                                 : INTEGER)
        return integer
    is
        variable right_of_dp, left_of_dp, result : integer;
    begin
        right_of_dp := max(new_bin_pt, old_bin_pt);
        left_of_dp := max((new_width - new_bin_pt), (old_width - old_bin_pt));
        result := (old_width + 2) + (new_bin_pt - old_bin_pt);
        return result;
    end;
    function convert_type (inp : std_logic_vector; old_width, old_bin_pt,
                           old_arith, new_width, new_bin_pt, new_arith,
                           quantization, overflow : INTEGER)
        return std_logic_vector
    is
        constant fp_width : integer :=
            full_precision_num_width(quantization, overflow, old_width,
                                     old_bin_pt, old_arith, new_width,
                                     new_bin_pt, new_arith);
        constant fp_bin_pt : integer := old_bin_pt;
        constant fp_arith : integer := old_arith;
        variable full_precision_result : std_logic_vector(fp_width-1 downto 0);
        constant q_width : integer :=
            quantized_num_width(quantization, overflow, old_width, old_bin_pt,
                                old_arith, new_width, new_bin_pt, new_arith);
        constant q_bin_pt : integer := new_bin_pt;
        constant q_arith : integer := old_arith;
        variable quantized_result : std_logic_vector(q_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        result := (others => '0');
        full_precision_result := cast(inp, old_bin_pt, fp_width, fp_bin_pt,
                                      fp_arith);
        if (quantization = xlRound) then
            quantized_result := round_towards_inf(full_precision_result,
                                                  fp_width, fp_bin_pt,
                                                  fp_arith, q_width, q_bin_pt,
                                                  q_arith);
        elsif (quantization = xlRoundBanker) then
            quantized_result := round_towards_even(full_precision_result,
                                                  fp_width, fp_bin_pt,
                                                  fp_arith, q_width, q_bin_pt,
                                                  q_arith);
        else
            quantized_result := trunc(full_precision_result, fp_width, fp_bin_pt,
                                      fp_arith, q_width, q_bin_pt, q_arith);
        end if;
        if (overflow = xlSaturate) then
            result := saturation_arith(quantized_result, q_width, q_bin_pt,
                                       q_arith, new_width, new_bin_pt, new_arith);
        else
             result := wrap_arith(quantized_result, q_width, q_bin_pt, q_arith,
                                  new_width, new_bin_pt, new_arith);
        end if;
        return result;
    end;
    function cast (inp : std_logic_vector; old_bin_pt, new_width,
                   new_bin_pt, new_arith : INTEGER)
        return std_logic_vector
    is
        constant old_width : integer := inp'length;
        constant left_of_dp : integer := (new_width - new_bin_pt)
                                         - (old_width - old_bin_pt);
        constant right_of_dp : integer := (new_bin_pt - old_bin_pt);
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
        variable j   : integer;
    begin
        vec := inp;
        for i in new_width-1 downto 0 loop
            j := i - right_of_dp;
            if ( j > old_width-1) then
                if (new_arith = xlUnsigned) then
                    result(i) := '0';
                else
                    result(i) := vec(old_width-1);
                end if;
            elsif ( j >= 0) then
                result(i) := vec(j);
            else
                result(i) := '0';
            end if;
        end loop;
        return result;
    end;
    function vec_slice (inp : std_logic_vector; upper, lower : INTEGER)
      return std_logic_vector
    is
    begin
        return inp(upper downto lower);
    end;
    function s2u_slice (inp : signed; upper, lower : INTEGER)
      return unsigned
    is
    begin
        return unsigned(vec_slice(std_logic_vector(inp), upper, lower));
    end;
    function u2u_slice (inp : unsigned; upper, lower : INTEGER)
      return unsigned
    is
    begin
        return unsigned(vec_slice(std_logic_vector(inp), upper, lower));
    end;
    function s2s_cast (inp : signed; old_bin_pt, new_width, new_bin_pt : INTEGER)
        return signed
    is
    begin
        return signed(cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlSigned));
    end;
    function s2u_cast (inp : signed; old_bin_pt, new_width,
                   new_bin_pt : INTEGER)
        return unsigned
    is
    begin
        return unsigned(cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlSigned));
    end;
    function u2s_cast (inp : unsigned; old_bin_pt, new_width,
                   new_bin_pt : INTEGER)
        return signed
    is
    begin
        return signed(cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlUnsigned));
    end;
    function u2u_cast (inp : unsigned; old_bin_pt, new_width,
                   new_bin_pt : INTEGER)
        return unsigned
    is
    begin
        return unsigned(cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlUnsigned));
    end;
    function u2v_cast (inp : unsigned; old_bin_pt, new_width,
                   new_bin_pt : INTEGER)
        return std_logic_vector
    is
    begin
        return cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlUnsigned);
    end;
    function s2v_cast (inp : signed; old_bin_pt, new_width,
                   new_bin_pt : INTEGER)
        return std_logic_vector
    is
    begin
        return cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlSigned);
    end;
    function boolean_to_signed (inp : boolean; width : integer)
        return signed
    is
        variable result : signed(width - 1 downto 0);
    begin
        result := (others => '0');
        if inp then
          result(0) := '1';
        else
          result(0) := '0';
        end if;
        return result;
    end;
    function boolean_to_unsigned (inp : boolean; width : integer)
        return unsigned
    is
        variable result : unsigned(width - 1 downto 0);
    begin
        result := (others => '0');
        if inp then
          result(0) := '1';
        else
          result(0) := '0';
        end if;
        return result;
    end;
    function boolean_to_vector (inp : boolean)
        return std_logic_vector
    is
        variable result : std_logic_vector(1 - 1 downto 0);
    begin
        result := (others => '0');
        if inp then
          result(0) := '1';
        else
          result(0) := '0';
        end if;
        return result;
    end;
    function std_logic_to_vector (inp : std_logic)
        return std_logic_vector
    is
        variable result : std_logic_vector(1 - 1 downto 0);
    begin
        result(0) := inp;
        return result;
    end;
    function trunc (inp : std_logic_vector; old_width, old_bin_pt, old_arith,
                                new_width, new_bin_pt, new_arith : INTEGER)
        return std_logic_vector
    is
        constant right_of_dp : integer := (old_bin_pt - new_bin_pt);
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if right_of_dp >= 0 then
            if new_arith = xlUnsigned then
                result := zero_ext(vec(old_width-1 downto right_of_dp), new_width);
            else
                result := sign_ext(vec(old_width-1 downto right_of_dp), new_width);
            end if;
        else
            if new_arith = xlUnsigned then
                result := zero_ext(pad_LSB(vec, old_width +
                                           abs(right_of_dp)), new_width);
            else
                result := sign_ext(pad_LSB(vec, old_width +
                                           abs(right_of_dp)), new_width);
            end if;
        end if;
        return result;
    end;
    function round_towards_inf (inp : std_logic_vector; old_width, old_bin_pt,
                                old_arith, new_width, new_bin_pt, new_arith
                                : INTEGER)
        return std_logic_vector
    is
        constant right_of_dp : integer := (old_bin_pt - new_bin_pt);
        constant expected_new_width : integer :=  old_width - right_of_dp  + 1;
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable one_or_zero : std_logic_vector(new_width-1 downto 0);
        variable truncated_val : std_logic_vector(new_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if right_of_dp >= 0 then
            if new_arith = xlUnsigned then
                truncated_val := zero_ext(vec(old_width-1 downto right_of_dp),
                                          new_width);
            else
                truncated_val := sign_ext(vec(old_width-1 downto right_of_dp),
                                          new_width);
            end if;
        else
            if new_arith = xlUnsigned then
                truncated_val := zero_ext(pad_LSB(vec, old_width +
                                                  abs(right_of_dp)), new_width);
            else
                truncated_val := sign_ext(pad_LSB(vec, old_width +
                                                  abs(right_of_dp)), new_width);
            end if;
        end if;
        one_or_zero := (others => '0');
        if (new_arith = xlSigned) then
            if (vec(old_width-1) = '0') then
                one_or_zero(0) := '1';
            end if;
            if (right_of_dp >= 2) and (right_of_dp <= old_width) then
                if (all_zeros(vec(right_of_dp-2 downto 0)) = false) then
                    one_or_zero(0) := '1';
                end if;
            end if;
            if (right_of_dp >= 1) and (right_of_dp <= old_width) then
                if vec(right_of_dp-1) = '0' then
                    one_or_zero(0) := '0';
                end if;
            else
                one_or_zero(0) := '0';
            end if;
        else
            if (right_of_dp >= 1) and (right_of_dp <= old_width) then
                one_or_zero(0) :=  vec(right_of_dp-1);
            end if;
        end if;
        if new_arith = xlSigned then
            result := signed_to_std_logic_vector(std_logic_vector_to_signed(truncated_val) +
                                                 std_logic_vector_to_signed(one_or_zero));
        else
            result := unsigned_to_std_logic_vector(std_logic_vector_to_unsigned(truncated_val) +
                                                  std_logic_vector_to_unsigned(one_or_zero));
        end if;
        return result;
    end;
    function round_towards_even (inp : std_logic_vector; old_width, old_bin_pt,
                                old_arith, new_width, new_bin_pt, new_arith
                                : INTEGER)
        return std_logic_vector
    is
        constant right_of_dp : integer := (old_bin_pt - new_bin_pt);
        constant expected_new_width : integer :=  old_width - right_of_dp  + 1;
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable one_or_zero : std_logic_vector(new_width-1 downto 0);
        variable truncated_val : std_logic_vector(new_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if right_of_dp >= 0 then
            if new_arith = xlUnsigned then
                truncated_val := zero_ext(vec(old_width-1 downto right_of_dp),
                                          new_width);
            else
                truncated_val := sign_ext(vec(old_width-1 downto right_of_dp),
                                          new_width);
            end if;
        else
            if new_arith = xlUnsigned then
                truncated_val := zero_ext(pad_LSB(vec, old_width +
                                                  abs(right_of_dp)), new_width);
            else
                truncated_val := sign_ext(pad_LSB(vec, old_width +
                                                  abs(right_of_dp)), new_width);
            end if;
        end if;
        one_or_zero := (others => '0');
        if (right_of_dp >= 1) and (right_of_dp <= old_width) then
            if (is_point_five(vec(right_of_dp-1 downto 0)) = false) then
                one_or_zero(0) :=  vec(right_of_dp-1);
            else
                one_or_zero(0) :=  vec(right_of_dp);
            end if;
        end if;
        if new_arith = xlSigned then
            result := signed_to_std_logic_vector(std_logic_vector_to_signed(truncated_val) +
                                                 std_logic_vector_to_signed(one_or_zero));
        else
            result := unsigned_to_std_logic_vector(std_logic_vector_to_unsigned(truncated_val) +
                                                  std_logic_vector_to_unsigned(one_or_zero));
        end if;
        return result;
    end;
    function saturation_arith(inp:  std_logic_vector;  old_width, old_bin_pt,
                              old_arith, new_width, new_bin_pt, new_arith
                              : INTEGER)
        return std_logic_vector
    is
        constant left_of_dp : integer := (old_width - old_bin_pt) -
                                         (new_width - new_bin_pt);
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
        variable overflow : boolean;
    begin
        vec := inp;
        overflow := true;
        result := (others => '0');
        if (new_width >= old_width) then
            overflow := false;
        end if;
        if ((old_arith = xlSigned and new_arith = xlSigned) and (old_width > new_width)) then
            if all_same(vec(old_width-1 downto new_width-1)) then
                overflow := false;
            end if;
        end if;
        if (old_arith = xlSigned and new_arith = xlUnsigned) then
            if (old_width > new_width) then
                if all_zeros(vec(old_width-1 downto new_width)) then
                    overflow := false;
                end if;
            else
                if (old_width = new_width) then
                    if (vec(new_width-1) = '0') then
                        overflow := false;
                    end if;
                end if;
            end if;
        end if;
        if (old_arith = xlUnsigned and new_arith = xlUnsigned) then
            if (old_width > new_width) then
                if all_zeros(vec(old_width-1 downto new_width)) then
                    overflow := false;
                end if;
            else
                if (old_width = new_width) then
                    overflow := false;
                end if;
            end if;
        end if;
        if ((old_arith = xlUnsigned and new_arith = xlSigned) and (old_width > new_width)) then
            if all_same(vec(old_width-1 downto new_width-1)) then
                overflow := false;
            end if;
        end if;
        if overflow then
            if new_arith = xlSigned then
                if vec(old_width-1) = '0' then
                    result := max_signed(new_width);
                else
                    result := min_signed(new_width);
                end if;
            else
                if ((old_arith = xlSigned) and vec(old_width-1) = '1') then
                    result := (others => '0');
                else
                    result := (others => '1');
                end if;
            end if;
        else
            if (old_arith = xlSigned) and (new_arith = xlUnsigned) then
                if (vec(old_width-1) = '1') then
                    vec := (others => '0');
                end if;
            end if;
            if new_width <= old_width then
                result := vec(new_width-1 downto 0);
            else
                if new_arith = xlUnsigned then
                    result := zero_ext(vec, new_width);
                else
                    result := sign_ext(vec, new_width);
                end if;
            end if;
        end if;
        return result;
    end;
   function wrap_arith(inp:  std_logic_vector;  old_width, old_bin_pt,
                       old_arith, new_width, new_bin_pt, new_arith : INTEGER)
        return std_logic_vector
    is
        variable result : std_logic_vector(new_width-1 downto 0);
        variable result_arith : integer;
    begin
        if (old_arith = xlSigned) and (new_arith = xlUnsigned) then
            result_arith := xlSigned;
        end if;
        result := cast(inp, old_bin_pt, new_width, new_bin_pt, result_arith);
        return result;
    end;
    function fractional_bits(a_bin_pt, b_bin_pt: INTEGER) return INTEGER is
    begin
        return max(a_bin_pt, b_bin_pt);
    end;
    function integer_bits(a_width, a_bin_pt, b_width, b_bin_pt: INTEGER)
        return INTEGER is
    begin
        return  max(a_width - a_bin_pt, b_width - b_bin_pt);
    end;
    function pad_LSB(inp : std_logic_vector; new_width: integer)
        return STD_LOGIC_VECTOR
    is
        constant orig_width : integer := inp'length;
        variable vec : std_logic_vector(orig_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
        variable pos : integer;
        constant pad_pos : integer := new_width - orig_width - 1;
    begin
        vec := inp;
        pos := new_width-1;
        if (new_width >= orig_width) then
            for i in orig_width-1 downto 0 loop
                result(pos) := vec(i);
                pos := pos - 1;
            end loop;
            if pad_pos >= 0 then
                for i in pad_pos downto 0 loop
                    result(i) := '0';
                end loop;
            end if;
        end if;
        return result;
    end;
    function sign_ext(inp : std_logic_vector; new_width : INTEGER)
        return std_logic_vector
    is
        constant old_width : integer := inp'length;
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if new_width >= old_width then
            result(old_width-1 downto 0) := vec;
            if new_width-1 >= old_width then
                for i in new_width-1 downto old_width loop
                    result(i) := vec(old_width-1);
                end loop;
            end if;
        else
            result(new_width-1 downto 0) := vec(new_width-1 downto 0);
        end if;
        return result;
    end;
    function zero_ext(inp : std_logic_vector; new_width : INTEGER)
        return std_logic_vector
    is
        constant old_width : integer := inp'length;
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if new_width >= old_width then
            result(old_width-1 downto 0) := vec;
            if new_width-1 >= old_width then
                for i in new_width-1 downto old_width loop
                    result(i) := '0';
                end loop;
            end if;
        else
            result(new_width-1 downto 0) := vec(new_width-1 downto 0);
        end if;
        return result;
    end;
    function zero_ext(inp : std_logic; new_width : INTEGER)
        return std_logic_vector
    is
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        result(0) := inp;
        for i in new_width-1 downto 1 loop
            result(i) := '0';
        end loop;
        return result;
    end;
    function extend_MSB(inp : std_logic_vector; new_width, arith : INTEGER)
        return std_logic_vector
    is
        constant orig_width : integer := inp'length;
        variable vec : std_logic_vector(orig_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if arith = xlUnsigned then
            result := zero_ext(vec, new_width);
        else
            result := sign_ext(vec, new_width);
        end if;
        return result;
    end;
    function pad_LSB(inp : std_logic_vector; new_width, arith: integer)
        return STD_LOGIC_VECTOR
    is
        constant orig_width : integer := inp'length;
        variable vec : std_logic_vector(orig_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
        variable pos : integer;
    begin
        vec := inp;
        pos := new_width-1;
        if (arith = xlUnsigned) then
            result(pos) := '0';
            pos := pos - 1;
        else
            result(pos) := vec(orig_width-1);
            pos := pos - 1;
        end if;
        if (new_width >= orig_width) then
            for i in orig_width-1 downto 0 loop
                result(pos) := vec(i);
                pos := pos - 1;
            end loop;
            if pos >= 0 then
                for i in pos downto 0 loop
                    result(i) := '0';
                end loop;
            end if;
        end if;
        return result;
    end;
    function align_input(inp : std_logic_vector; old_width, delta, new_arith,
                         new_width: INTEGER)
        return std_logic_vector
    is
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable padded_inp : std_logic_vector((old_width + delta)-1  downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if delta > 0 then
            padded_inp := pad_LSB(vec, old_width+delta);
            result := extend_MSB(padded_inp, new_width, new_arith);
        else
            result := extend_MSB(vec, new_width, new_arith);
        end if;
        return result;
    end;
    function max(L, R: INTEGER) return INTEGER is
    begin
        if L > R then
            return L;
        else
            return R;
        end if;
    end;
    function min(L, R: INTEGER) return INTEGER is
    begin
        if L < R then
            return L;
        else
            return R;
        end if;
    end;
    function "="(left,right: STRING) return boolean is
    begin
        if (left'length /= right'length) then
            return false;
        else
            test : for i in 1 to left'length loop
                if left(i) /= right(i) then
                    return false;
                end if;
            end loop test;
            return true;
        end if;
    end;
    -- synopsys translate_off
    function is_binary_string_invalid (inp : string)
        return boolean
    is
        variable vec : string(1 to inp'length);
        variable result : boolean;
    begin
        vec := inp;
        result := false;
        for i in 1 to vec'length loop
            if ( vec(i) = 'X' ) then
                result := true;
            end if;
        end loop;
        return result;
    end;
    function is_binary_string_undefined (inp : string)
        return boolean
    is
        variable vec : string(1 to inp'length);
        variable result : boolean;
    begin
        vec := inp;
        result := false;
        for i in 1 to vec'length loop
            if ( vec(i) = 'U' ) then
                result := true;
            end if;
        end loop;
        return result;
    end;
    function is_XorU(inp : std_logic_vector)
        return boolean
    is
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
        variable result : boolean;
    begin
        vec := inp;
        result := false;
        for i in 0 to width-1 loop
            if (vec(i) = 'U') or (vec(i) = 'X') then
                result := true;
            end if;
        end loop;
        return result;
    end;
    function to_real(inp : std_logic_vector; bin_pt : integer; arith : integer)
        return real
    is
        variable  vec : std_logic_vector(inp'length-1 downto 0);
        variable result, shift_val, undefined_real : real;
        variable neg_num : boolean;
    begin
        vec := inp;
        result := 0.0;
        neg_num := false;
        if vec(inp'length-1) = '1' then
            neg_num := true;
        end if;
        for i in 0 to inp'length-1 loop
            if  vec(i) = 'U' or vec(i) = 'X' then
                return undefined_real;
            end if;
            if arith = xlSigned then
                if neg_num then
                    if vec(i) = '0' then
                        result := result + 2.0**i;
                    end if;
                else
                    if vec(i) = '1' then
                        result := result + 2.0**i;
                    end if;
                end if;
            else
                if vec(i) = '1' then
                    result := result + 2.0**i;
                end if;
            end if;
        end loop;
        if arith = xlSigned then
            if neg_num then
                result := result + 1.0;
                result := result * (-1.0);
            end if;
        end if;
        shift_val := 2.0**(-1*bin_pt);
        result := result * shift_val;
        return result;
    end;
    function std_logic_to_real(inp : std_logic; bin_pt : integer; arith : integer)
        return real
    is
        variable result : real := 0.0;
    begin
        if inp = '1' then
            result := 1.0;
        end if;
        if arith = xlSigned then
            assert false
                report "It doesn't make sense to convert a 1 bit number to a signed real.";
        end if;
        return result;
    end;
    -- synopsys translate_on
    function integer_to_std_logic_vector (inp : integer;  width, arith : integer)
        return std_logic_vector
    is
        variable result : std_logic_vector(width-1 downto 0);
        variable unsigned_val : unsigned(width-1 downto 0);
        variable signed_val : signed(width-1 downto 0);
    begin
        if (arith = xlSigned) then
            signed_val := to_signed(inp, width);
            result := signed_to_std_logic_vector(signed_val);
        else
            unsigned_val := to_unsigned(inp, width);
            result := unsigned_to_std_logic_vector(unsigned_val);
        end if;
        return result;
    end;
    function std_logic_vector_to_integer (inp : std_logic_vector;  arith : integer)
        return integer
    is
        constant width : integer := inp'length;
        variable unsigned_val : unsigned(width-1 downto 0);
        variable signed_val : signed(width-1 downto 0);
        variable result : integer;
    begin
        if (arith = xlSigned) then
            signed_val := std_logic_vector_to_signed(inp);
            result := to_integer(signed_val);
        else
            unsigned_val := std_logic_vector_to_unsigned(inp);
            result := to_integer(unsigned_val);
        end if;
        return result;
    end;
    function std_logic_to_integer(constant inp : std_logic := '0')
        return integer
    is
    begin
        if inp = '1' then
            return 1;
        else
            return 0;
        end if;
    end;
    function makeZeroBinStr (width : integer) return STRING is
        variable result : string(1 to width+3);
    begin
        result(1) := '0';
        result(2) := 'b';
        for i in 3 to width+2 loop
            result(i) := '0';
        end loop;
        result(width+3) := '.';
        return result;
    end;
    -- synopsys translate_off
    function real_string_to_std_logic_vector (inp : string;  width, bin_pt, arith : integer)
        return std_logic_vector
    is
        variable result : std_logic_vector(width-1 downto 0);
    begin
        result := (others => '0');
        return result;
    end;
    function real_to_std_logic_vector (inp : real;  width, bin_pt, arith : integer)
        return std_logic_vector
    is
        variable real_val : real;
        variable int_val : integer;
        variable result : std_logic_vector(width-1 downto 0) := (others => '0');
        variable unsigned_val : unsigned(width-1 downto 0) := (others => '0');
        variable signed_val : signed(width-1 downto 0) := (others => '0');
    begin
        real_val := inp;
        int_val := integer(real_val * 2.0**(bin_pt));
        if (arith = xlSigned) then
            signed_val := to_signed(int_val, width);
            result := signed_to_std_logic_vector(signed_val);
        else
            unsigned_val := to_unsigned(int_val, width);
            result := unsigned_to_std_logic_vector(unsigned_val);
        end if;
        return result;
    end;
    -- synopsys translate_on
    function valid_bin_string (inp : string)
        return boolean
    is
        variable vec : string(1 to inp'length);
    begin
        vec := inp;
        if (vec(1) = '0' and vec(2) = 'b') then
            return true;
        else
            return false;
        end if;
    end;
    function hex_string_to_std_logic_vector(inp: string; width : integer)
        return std_logic_vector is
        constant strlen       : integer := inp'LENGTH;
        variable result       : std_logic_vector(width-1 downto 0);
        variable bitval       : std_logic_vector((strlen*4)-1 downto 0);
        variable posn         : integer;
        variable ch           : character;
        variable vec          : string(1 to strlen);
    begin
        vec := inp;
        result := (others => '0');
        posn := (strlen*4)-1;
        for i in 1 to strlen loop
            ch := vec(i);
            case ch is
                when '0' => bitval(posn downto posn-3) := "0000";
                when '1' => bitval(posn downto posn-3) := "0001";
                when '2' => bitval(posn downto posn-3) := "0010";
                when '3' => bitval(posn downto posn-3) := "0011";
                when '4' => bitval(posn downto posn-3) := "0100";
                when '5' => bitval(posn downto posn-3) := "0101";
                when '6' => bitval(posn downto posn-3) := "0110";
                when '7' => bitval(posn downto posn-3) := "0111";
                when '8' => bitval(posn downto posn-3) := "1000";
                when '9' => bitval(posn downto posn-3) := "1001";
                when 'A' | 'a' => bitval(posn downto posn-3) := "1010";
                when 'B' | 'b' => bitval(posn downto posn-3) := "1011";
                when 'C' | 'c' => bitval(posn downto posn-3) := "1100";
                when 'D' | 'd' => bitval(posn downto posn-3) := "1101";
                when 'E' | 'e' => bitval(posn downto posn-3) := "1110";
                when 'F' | 'f' => bitval(posn downto posn-3) := "1111";
                when others => bitval(posn downto posn-3) := "XXXX";
                               -- synopsys translate_off
                               ASSERT false
                                   REPORT "Invalid hex value" SEVERITY ERROR;
                               -- synopsys translate_on
            end case;
            posn := posn - 4;
        end loop;
        if (width <= strlen*4) then
            result :=  bitval(width-1 downto 0);
        else
            result((strlen*4)-1 downto 0) := bitval;
        end if;
        return result;
    end;
    function bin_string_to_std_logic_vector (inp : string)
        return std_logic_vector
    is
        variable pos : integer;
        variable vec : string(1 to inp'length);
        variable result : std_logic_vector(inp'length-1 downto 0);
    begin
        vec := inp;
        pos := inp'length-1;
        result := (others => '0');
        for i in 1 to vec'length loop
            -- synopsys translate_off
            if (pos < 0) and (vec(i) = '0' or vec(i) = '1' or vec(i) = 'X' or vec(i) = 'U')  then
                assert false
                    report "Input string is larger than output std_logic_vector. Truncating output.";
                return result;
            end if;
            -- synopsys translate_on
            if vec(i) = '0' then
                result(pos) := '0';
                pos := pos - 1;
            end if;
            if vec(i) = '1' then
                result(pos) := '1';
                pos := pos - 1;
            end if;
            -- synopsys translate_off
            if (vec(i) = 'X' or vec(i) = 'U') then
                result(pos) := 'U';
                pos := pos - 1;
            end if;
            -- synopsys translate_on
        end loop;
        return result;
    end;
    function bin_string_element_to_std_logic_vector (inp : string;  width, index : integer)
        return std_logic_vector
    is
        constant str_width : integer := width + 4;
        constant inp_len : integer := inp'length;
        constant num_elements : integer := (inp_len + 1)/str_width;
        constant reverse_index : integer := (num_elements-1) - index;
        variable left_pos : integer;
        variable right_pos : integer;
        variable vec : string(1 to inp'length);
        variable result : std_logic_vector(width-1 downto 0);
    begin
        vec := inp;
        result := (others => '0');
        if (reverse_index = 0) and (reverse_index < num_elements) and (inp_len-3 >= width) then
            left_pos := 1;
            right_pos := width + 3;
            result := bin_string_to_std_logic_vector(vec(left_pos to right_pos));
        end if;
        if (reverse_index > 0) and (reverse_index < num_elements) and (inp_len-3 >= width) then
            left_pos := (reverse_index * str_width) + 1;
            right_pos := left_pos + width + 2;
            result := bin_string_to_std_logic_vector(vec(left_pos to right_pos));
        end if;
        return result;
    end;
   -- synopsys translate_off
    function std_logic_vector_to_bin_string(inp : std_logic_vector)
        return string
    is
        variable vec : std_logic_vector(1 to inp'length);
        variable result : string(vec'range);
    begin
        vec := inp;
        for i in vec'range loop
            result(i) := to_char(vec(i));
        end loop;
        return result;
    end;
    function std_logic_to_bin_string(inp : std_logic)
        return string
    is
        variable result : string(1 to 3);
    begin
        result(1) := '0';
        result(2) := 'b';
        result(3) := to_char(inp);
        return result;
    end;
    function std_logic_vector_to_bin_string_w_point(inp : std_logic_vector; bin_pt : integer)
        return string
    is
        variable width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
        variable str_pos : integer;
        variable result : string(1 to width+3);
    begin
        vec := inp;
        str_pos := 1;
        result(str_pos) := '0';
        str_pos := 2;
        result(str_pos) := 'b';
        str_pos := 3;
        for i in width-1 downto 0  loop
            if (((width+3) - bin_pt) = str_pos) then
                result(str_pos) := '.';
                str_pos := str_pos + 1;
            end if;
            result(str_pos) := to_char(vec(i));
            str_pos := str_pos + 1;
        end loop;
        if (bin_pt = 0) then
            result(str_pos) := '.';
        end if;
        return result;
    end;
    function real_to_bin_string(inp : real;  width, bin_pt, arith : integer)
        return string
    is
        variable result : string(1 to width);
        variable vec : std_logic_vector(width-1 downto 0);
    begin
        vec := real_to_std_logic_vector(inp, width, bin_pt, arith);
        result := std_logic_vector_to_bin_string(vec);
        return result;
    end;
    function real_to_string (inp : real) return string
    is
        variable result : string(1 to display_precision) := (others => ' ');
    begin
        result(real'image(inp)'range) := real'image(inp);
        return result;
    end;
    -- synopsys translate_on
end conv_pkg;

-------------------------------------------------------------------
-- System Generator version 12.1 VHDL source file.
--
-- Copyright(C) 2010 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2010 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
-- synopsys translate_off
library unisim;
use unisim.vcomponents.all;
-- synopsys translate_on
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity srl17e is
    generic (width : integer:=16;
             latency : integer :=8);
    port (clk   : in std_logic;
          ce    : in std_logic;
          d     : in std_logic_vector(width-1 downto 0);
          q     : out std_logic_vector(width-1 downto 0));
end srl17e;
architecture structural of srl17e is
    component SRL16E
        port (D   : in STD_ULOGIC;
              CE  : in STD_ULOGIC;
              CLK : in STD_ULOGIC;
              A0  : in STD_ULOGIC;
              A1  : in STD_ULOGIC;
              A2  : in STD_ULOGIC;
              A3  : in STD_ULOGIC;
              Q   : out STD_ULOGIC);
    end component;
    attribute syn_black_box of SRL16E : component is true;
    attribute fpga_dont_touch of SRL16E : component is "true";
    component FDE
        port(
            Q  :        out   STD_ULOGIC;
            D  :        in    STD_ULOGIC;
            C  :        in    STD_ULOGIC;
            CE :        in    STD_ULOGIC);
    end component;
    attribute syn_black_box of FDE : component is true;
    attribute fpga_dont_touch of FDE : component is "true";
    constant a : std_logic_vector(4 downto 0) :=
        integer_to_std_logic_vector(latency-2,5,xlSigned);
    signal d_delayed : std_logic_vector(width-1 downto 0);
    signal srl16_out : std_logic_vector(width-1 downto 0);
begin
    d_delayed <= d after 200 ps;
    reg_array : for i in 0 to width-1 generate
        srl16_used: if latency > 1 generate
            u1 : srl16e port map(clk => clk,
                                 d => d_delayed(i),
                                 q => srl16_out(i),
                                 ce => ce,
                                 a0 => a(0),
                                 a1 => a(1),
                                 a2 => a(2),
                                 a3 => a(3));
        end generate;
        srl16_not_used: if latency <= 1 generate
            srl16_out(i) <= d_delayed(i);
        end generate;
        fde_used: if latency /= 0  generate
            u2 : fde port map(c => clk,
                              d => srl16_out(i),
                              q => q(i),
                              ce => ce);
        end generate;
        fde_not_used: if latency = 0  generate
            q(i) <= srl16_out(i);
        end generate;
    end generate;
 end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity synth_reg is
    generic (width           : integer := 8;
             latency         : integer := 1);
    port (i       : in std_logic_vector(width-1 downto 0);
          ce      : in std_logic;
          clr     : in std_logic;
          clk     : in std_logic;
          o       : out std_logic_vector(width-1 downto 0));
end synth_reg;
architecture structural of synth_reg is
    component srl17e
        generic (width : integer:=16;
                 latency : integer :=8);
        port (clk : in std_logic;
              ce  : in std_logic;
              d   : in std_logic_vector(width-1 downto 0);
              q   : out std_logic_vector(width-1 downto 0));
    end component;
    function calc_num_srl17es (latency : integer)
        return integer
    is
        variable remaining_latency : integer;
        variable result : integer;
    begin
        result := latency / 17;
        remaining_latency := latency - (result * 17);
        if (remaining_latency /= 0) then
            result := result + 1;
        end if;
        return result;
    end;
    constant complete_num_srl17es : integer := latency / 17;
    constant num_srl17es : integer := calc_num_srl17es(latency);
    constant remaining_latency : integer := latency - (complete_num_srl17es * 17);
    type register_array is array (num_srl17es downto 0) of
        std_logic_vector(width-1 downto 0);
    signal z : register_array;
begin
    z(0) <= i;
    complete_ones : if complete_num_srl17es > 0 generate
        srl17e_array: for i in 0 to complete_num_srl17es-1 generate
            delay_comp : srl17e
                generic map (width => width,
                             latency => 17)
                port map (clk => clk,
                          ce  => ce,
                          d       => z(i),
                          q       => z(i+1));
        end generate;
    end generate;
    partial_one : if remaining_latency > 0 generate
        last_srl17e : srl17e
            generic map (width => width,
                         latency => remaining_latency)
            port map (clk => clk,
                      ce  => ce,
                      d   => z(num_srl17es-1),
                      q   => z(num_srl17es));
    end generate;
    o <= z(num_srl17es);
end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity synth_reg_reg is
    generic (width           : integer := 8;
             latency         : integer := 1);
    port (i       : in std_logic_vector(width-1 downto 0);
          ce      : in std_logic;
          clr     : in std_logic;
          clk     : in std_logic;
          o       : out std_logic_vector(width-1 downto 0));
end synth_reg_reg;
architecture behav of synth_reg_reg is
  type reg_array_type is array (latency-1 downto 0) of std_logic_vector(width -1 downto 0);
  signal reg_bank : reg_array_type := (others => (others => '0'));
  signal reg_bank_in : reg_array_type := (others => (others => '0'));
  attribute syn_allow_retiming : boolean;
  attribute syn_srlstyle : string;
  attribute syn_allow_retiming of reg_bank : signal is true;
  attribute syn_allow_retiming of reg_bank_in : signal is true;
  attribute syn_srlstyle of reg_bank : signal is "registers";
  attribute syn_srlstyle of reg_bank_in : signal is "registers";
begin
  latency_eq_0: if latency = 0 generate
    o <= i;
  end generate latency_eq_0;
  latency_gt_0: if latency >= 1 generate
    o <= reg_bank(latency-1);
    reg_bank_in(0) <= i;
    loop_gen: for idx in latency-2 downto 0 generate
      reg_bank_in(idx+1) <= reg_bank(idx);
    end generate loop_gen;
    sync_loop: for sync_idx in latency-1 downto 0 generate
      sync_proc: process (clk)
      begin
        if clk'event and clk = '1' then
          if ce = '1'  then
            reg_bank(sync_idx) <= reg_bank_in(sync_idx);
          end if;
        end if;
      end process sync_proc;
    end generate sync_loop;
  end generate latency_gt_0;
end behav;

-------------------------------------------------------------------
-- System Generator version 12.1 VHDL source file.
--
-- Copyright(C) 2010 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2010 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
-- synopsys translate_off
library unisim;
use unisim.vcomponents.all;
-- synopsys translate_on
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity single_reg_w_init is
  generic (
    width: integer := 8;
    init_index: integer := 0;
    init_value: bit_vector := b"0000"
  );
  port (
    i: in std_logic_vector(width - 1 downto 0);
    ce: in std_logic;
    clr: in std_logic;
    clk: in std_logic;
    o: out std_logic_vector(width - 1 downto 0)
  );
end single_reg_w_init;
architecture structural of single_reg_w_init is
  function build_init_const(width: integer;
                            init_index: integer;
                            init_value: bit_vector)
    return std_logic_vector
  is
    variable result: std_logic_vector(width - 1 downto 0);
  begin
    if init_index = 0 then
      result := (others => '0');
    elsif init_index = 1 then
      result := (others => '0');
      result(0) := '1';
    else
      result := to_stdlogicvector(init_value);
    end if;
    return result;
  end;
  component fdre
    port (
      q: out std_ulogic;
      d: in  std_ulogic;
      c: in  std_ulogic;
      ce: in  std_ulogic;
      r: in  std_ulogic
    );
  end component;
  attribute syn_black_box of fdre: component is true;
  attribute fpga_dont_touch of fdre: component is "true";
  component fdse
    port (
      q: out std_ulogic;
      d: in  std_ulogic;
      c: in  std_ulogic;
      ce: in  std_ulogic;
      s: in  std_ulogic
    );
  end component;
  attribute syn_black_box of fdse: component is true;
  attribute fpga_dont_touch of fdse: component is "true";
  constant init_const: std_logic_vector(width - 1 downto 0)
    := build_init_const(width, init_index, init_value);
begin
  fd_prim_array: for index in 0 to width - 1 generate
    bit_is_0: if (init_const(index) = '0') generate
      fdre_comp: fdre
        port map (
          c => clk,
          d => i(index),
          q => o(index),
          ce => ce,
          r => clr
        );
    end generate;
    bit_is_1: if (init_const(index) = '1') generate
      fdse_comp: fdse
        port map (
          c => clk,
          d => i(index),
          q => o(index),
          ce => ce,
          s => clr
        );
    end generate;
  end generate;
end architecture structural;
-- synopsys translate_off
library unisim;
use unisim.vcomponents.all;
-- synopsys translate_on
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity synth_reg_w_init is
  generic (
    width: integer := 8;
    init_index: integer := 0;
    init_value: bit_vector := b"0000";
    latency: integer := 1
  );
  port (
    i: in std_logic_vector(width - 1 downto 0);
    ce: in std_logic;
    clr: in std_logic;
    clk: in std_logic;
    o: out std_logic_vector(width - 1 downto 0)
  );
end synth_reg_w_init;
architecture structural of synth_reg_w_init is
  component single_reg_w_init
    generic (
      width: integer := 8;
      init_index: integer := 0;
      init_value: bit_vector := b"0000"
    );
    port (
      i: in std_logic_vector(width - 1 downto 0);
      ce: in std_logic;
      clr: in std_logic;
      clk: in std_logic;
      o: out std_logic_vector(width - 1 downto 0)
    );
  end component;
  signal dly_i: std_logic_vector((latency + 1) * width - 1 downto 0);
  signal dly_clr: std_logic;
begin
  latency_eq_0: if (latency = 0) generate
    o <= i;
  end generate;
  latency_gt_0: if (latency >= 1) generate
    dly_i((latency + 1) * width - 1 downto latency * width) <= i
      after 200 ps;
    dly_clr <= clr after 200 ps;
    fd_array: for index in latency downto 1 generate
       reg_comp: single_reg_w_init
          generic map (
            width => width,
            init_index => init_index,
            init_value => init_value
          )
          port map (
            clk => clk,
            i => dly_i((index + 1) * width - 1 downto index * width),
            o => dly_i(index * width - 1 downto (index - 1) * width),
            ce => ce,
            clr => dly_clr
          );
    end generate;
    o <= dly_i(width - 1 downto 0);
  end generate;
end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_963ed6358a is
  port (
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_963ed6358a;


architecture behavior of constant_963ed6358a is
begin
  op <= "0";
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mcode_block_f4d0462e0e is
  port (
    plbrst : in std_logic_vector((1 - 1) downto 0);
    plbabus : in std_logic_vector((32 - 1) downto 0);
    plbpavalid : in std_logic_vector((1 - 1) downto 0);
    plbrnw : in std_logic_vector((1 - 1) downto 0);
    plbwrdbus : in std_logic_vector((32 - 1) downto 0);
    rddata : in std_logic_vector((32 - 1) downto 0);
    addrpref : in std_logic_vector((20 - 1) downto 0);
    wrdbusreg : out std_logic_vector((32 - 1) downto 0);
    addrack : out std_logic_vector((1 - 1) downto 0);
    rdcomp : out std_logic_vector((1 - 1) downto 0);
    wrdack : out std_logic_vector((1 - 1) downto 0);
    bankaddr : out std_logic_vector((2 - 1) downto 0);
    rnwreg : out std_logic_vector((1 - 1) downto 0);
    rddack : out std_logic_vector((1 - 1) downto 0);
    rddbus : out std_logic_vector((32 - 1) downto 0);
    linearaddr : out std_logic_vector((8 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mcode_block_f4d0462e0e;


architecture behavior of mcode_block_f4d0462e0e is
  signal plbrst_1_110: unsigned((1 - 1) downto 0);
  signal plbabus_1_118: unsigned((32 - 1) downto 0);
  signal plbpavalid_1_127: unsigned((1 - 1) downto 0);
  signal plbrnw_1_139: unsigned((1 - 1) downto 0);
  signal plbwrdbus_1_147: unsigned((32 - 1) downto 0);
  signal rddata_1_158: unsigned((32 - 1) downto 0);
  signal addrpref_1_166: unsigned((20 - 1) downto 0);
  signal plbrstreg_12_24_next: boolean;
  signal plbrstreg_12_24: boolean := false;
  signal plbabusreg_13_25_next: unsigned((32 - 1) downto 0);
  signal plbabusreg_13_25: unsigned((32 - 1) downto 0) := "00000000000000000000000000000000";
  signal plbpavalidreg_14_28_next: boolean;
  signal plbpavalidreg_14_28: boolean := false;
  signal plbrnwreg_15_24_next: unsigned((1 - 1) downto 0);
  signal plbrnwreg_15_24: unsigned((1 - 1) downto 0) := "0";
  signal plbwrdbusreg_16_27_next: unsigned((32 - 1) downto 0);
  signal plbwrdbusreg_16_27: unsigned((32 - 1) downto 0) := "00000000000000000000000000000000";
  signal avalidreg_28_23_next: boolean;
  signal avalidreg_28_23: boolean := false;
  signal ps1reg_39_20_next: boolean;
  signal ps1reg_39_20: boolean := false;
  signal psreg_47_19_next: boolean;
  signal psreg_47_19: boolean := false;
  type array_type_rdcompdelay_58_25 is array (0 to (3 - 1)) of unsigned((1 - 1) downto 0);
  signal rdcompdelay_58_25: array_type_rdcompdelay_58_25 := (
    "0",
    "0",
    "0");
  signal rdcompdelay_58_25_front_din: unsigned((1 - 1) downto 0);
  signal rdcompdelay_58_25_back: unsigned((1 - 1) downto 0);
  signal rdcompdelay_58_25_push_front_pop_back_en: std_logic;
  signal rdcompreg_62_23_next: unsigned((1 - 1) downto 0);
  signal rdcompreg_62_23: unsigned((1 - 1) downto 0) := "0";
  signal rddackreg_66_23_next: unsigned((1 - 1) downto 0);
  signal rddackreg_66_23: unsigned((1 - 1) downto 0) := "0";
  signal wrdackreg_70_23_next: unsigned((1 - 1) downto 0);
  signal wrdackreg_70_23: unsigned((1 - 1) downto 0) := "0";
  signal rddbusreg_84_23_next: unsigned((32 - 1) downto 0);
  signal rddbusreg_84_23: unsigned((32 - 1) downto 0) := "00000000000000000000000000000000";
  signal bankaddr_20_1_slice: unsigned((2 - 1) downto 0);
  signal linearaddr_21_1_slice: unsigned((8 - 1) downto 0);
  signal addrpref_in_32_1_slice: unsigned((20 - 1) downto 0);
  signal rel_33_4: boolean;
  signal ps1_join_33_1: boolean;
  signal ps_42_1_bit: boolean;
  signal bitnot_49_49: boolean;
  signal bitnot_49_73: boolean;
  signal bit_49_49: boolean;
  signal addrack_49_1_convert: unsigned((1 - 1) downto 0);
  signal bit_55_43: unsigned((1 - 1) downto 0);
  signal bitnot_72_35: unsigned((1 - 1) downto 0);
  signal wrdackreg_72_1_bit: unsigned((1 - 1) downto 0);
  signal rdsel_76_1_bit: unsigned((1 - 1) downto 0);
  signal rel_78_4: boolean;
  signal rddbus1_join_78_1: unsigned((32 - 1) downto 0);
  signal plbwrdbusreg_97_1_slice: unsigned((32 - 1) downto 0);
  signal plbrstreg_12_24_next_x_000000: boolean;
  signal plbpavalidreg_14_28_next_x_000000: boolean;
begin
  plbrst_1_110 <= std_logic_vector_to_unsigned(plbrst);
  plbabus_1_118 <= std_logic_vector_to_unsigned(plbabus);
  plbpavalid_1_127 <= std_logic_vector_to_unsigned(plbpavalid);
  plbrnw_1_139 <= std_logic_vector_to_unsigned(plbrnw);
  plbwrdbus_1_147 <= std_logic_vector_to_unsigned(plbwrdbus);
  rddata_1_158 <= std_logic_vector_to_unsigned(rddata);
  addrpref_1_166 <= std_logic_vector_to_unsigned(addrpref);
  proc_plbrstreg_12_24: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        plbrstreg_12_24 <= plbrstreg_12_24_next;
      end if;
    end if;
  end process proc_plbrstreg_12_24;
  proc_plbabusreg_13_25: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        plbabusreg_13_25 <= plbabusreg_13_25_next;
      end if;
    end if;
  end process proc_plbabusreg_13_25;
  proc_plbpavalidreg_14_28: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        plbpavalidreg_14_28 <= plbpavalidreg_14_28_next;
      end if;
    end if;
  end process proc_plbpavalidreg_14_28;
  proc_plbrnwreg_15_24: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        plbrnwreg_15_24 <= plbrnwreg_15_24_next;
      end if;
    end if;
  end process proc_plbrnwreg_15_24;
  proc_plbwrdbusreg_16_27: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        plbwrdbusreg_16_27 <= plbwrdbusreg_16_27_next;
      end if;
    end if;
  end process proc_plbwrdbusreg_16_27;
  proc_avalidreg_28_23: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        avalidreg_28_23 <= avalidreg_28_23_next;
      end if;
    end if;
  end process proc_avalidreg_28_23;
  proc_ps1reg_39_20: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        ps1reg_39_20 <= ps1reg_39_20_next;
      end if;
    end if;
  end process proc_ps1reg_39_20;
  proc_psreg_47_19: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        psreg_47_19 <= psreg_47_19_next;
      end if;
    end if;
  end process proc_psreg_47_19;
  rdcompdelay_58_25_back <= rdcompdelay_58_25(2);
  proc_rdcompdelay_58_25: process (clk)
  is
    variable i: integer;
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (rdcompdelay_58_25_push_front_pop_back_en = '1')) then
        for i in 2 downto 1 loop 
          rdcompdelay_58_25(i) <= rdcompdelay_58_25(i-1);
        end loop;
        rdcompdelay_58_25(0) <= rdcompdelay_58_25_front_din;
      end if;
    end if;
  end process proc_rdcompdelay_58_25;
  proc_rdcompreg_62_23: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        rdcompreg_62_23 <= rdcompreg_62_23_next;
      end if;
    end if;
  end process proc_rdcompreg_62_23;
  proc_rddackreg_66_23: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        rddackreg_66_23 <= rddackreg_66_23_next;
      end if;
    end if;
  end process proc_rddackreg_66_23;
  proc_wrdackreg_70_23: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        wrdackreg_70_23 <= wrdackreg_70_23_next;
      end if;
    end if;
  end process proc_wrdackreg_70_23;
  proc_rddbusreg_84_23: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        rddbusreg_84_23 <= rddbusreg_84_23_next;
      end if;
    end if;
  end process proc_rddbusreg_84_23;
  bankaddr_20_1_slice <= u2u_slice(plbabusreg_13_25, 11, 10);
  linearaddr_21_1_slice <= u2u_slice(plbabusreg_13_25, 9, 2);
  addrpref_in_32_1_slice <= u2u_slice(plbabusreg_13_25, 31, 12);
  rel_33_4 <= addrpref_in_32_1_slice = addrpref_1_166;
  proc_if_33_1: process (rel_33_4)
  is
  begin
    if rel_33_4 then
      ps1_join_33_1 <= true;
    else 
      ps1_join_33_1 <= false;
    end if;
  end process proc_if_33_1;
  ps_42_1_bit <= ((boolean_to_vector(ps1_join_33_1) and boolean_to_vector(plbpavalidreg_14_28)) = "1");
  bitnot_49_49 <= ((not boolean_to_vector(plbrstreg_12_24)) = "1");
  bitnot_49_73 <= ((not boolean_to_vector(psreg_47_19)) = "1");
  bit_49_49 <= ((boolean_to_vector(bitnot_49_49) and boolean_to_vector(ps_42_1_bit) and boolean_to_vector(bitnot_49_73)) = "1");
  addrack_49_1_convert <= u2u_cast(std_logic_vector_to_unsigned(boolean_to_vector(bit_49_49)), 0, 1, 0);
  bit_55_43 <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(addrack_49_1_convert) and unsigned_to_std_logic_vector(plbrnwreg_15_24));
  bitnot_72_35 <= std_logic_vector_to_unsigned(not unsigned_to_std_logic_vector(plbrnwreg_15_24));
  wrdackreg_72_1_bit <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(addrack_49_1_convert) and unsigned_to_std_logic_vector(bitnot_72_35));
  rdsel_76_1_bit <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(rdcompdelay_58_25_back) or unsigned_to_std_logic_vector(rdcompreg_62_23));
  rel_78_4 <= rdsel_76_1_bit = std_logic_vector_to_unsigned("1");
  proc_if_78_1: process (rddata_1_158, rel_78_4)
  is
  begin
    if rel_78_4 then
      rddbus1_join_78_1 <= rddata_1_158;
    else 
      rddbus1_join_78_1 <= std_logic_vector_to_unsigned("00000000000000000000000000000000");
    end if;
  end process proc_if_78_1;
  plbwrdbusreg_97_1_slice <= u2u_slice(plbwrdbus_1_147, 31, 0);
  plbrstreg_12_24_next_x_000000 <= (plbrst_1_110 /= "0");
  plbrstreg_12_24_next <= plbrstreg_12_24_next_x_000000;
  plbabusreg_13_25_next <= plbabus_1_118;
  plbpavalidreg_14_28_next_x_000000 <= (plbpavalid_1_127 /= "0");
  plbpavalidreg_14_28_next <= plbpavalidreg_14_28_next_x_000000;
  plbrnwreg_15_24_next <= plbrnw_1_139;
  plbwrdbusreg_16_27_next <= plbwrdbusreg_97_1_slice;
  avalidreg_28_23_next <= plbpavalidreg_14_28;
  ps1reg_39_20_next <= ps1_join_33_1;
  psreg_47_19_next <= ps_42_1_bit;
  rdcompdelay_58_25_front_din <= bit_55_43;
  rdcompdelay_58_25_push_front_pop_back_en <= '1';
  rdcompreg_62_23_next <= rdcompdelay_58_25_back;
  rddackreg_66_23_next <= rdcompreg_62_23;
  wrdackreg_70_23_next <= wrdackreg_72_1_bit;
  rddbusreg_84_23_next <= rddbus1_join_78_1;
  wrdbusreg <= unsigned_to_std_logic_vector(plbwrdbusreg_16_27);
  addrack <= unsigned_to_std_logic_vector(addrack_49_1_convert);
  rdcomp <= unsigned_to_std_logic_vector(rdcompreg_62_23);
  wrdack <= unsigned_to_std_logic_vector(wrdackreg_70_23);
  bankaddr <= unsigned_to_std_logic_vector(bankaddr_20_1_slice);
  rnwreg <= unsigned_to_std_logic_vector(plbrnwreg_15_24);
  rddack <= unsigned_to_std_logic_vector(rddackreg_66_23);
  rddbus <= unsigned_to_std_logic_vector(rddbusreg_84_23);
  linearaddr <= unsigned_to_std_logic_vector(linearaddr_21_1_slice);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mcode_block_57a988c97d is
  port (
    wrdbus : in std_logic_vector((32 - 1) downto 0);
    bankaddr : in std_logic_vector((2 - 1) downto 0);
    linearaddr : in std_logic_vector((8 - 1) downto 0);
    rnwreg : in std_logic_vector((1 - 1) downto 0);
    addrack : in std_logic_vector((1 - 1) downto 0);
    sm_gpio_out8 : in std_logic_vector((8 - 1) downto 0);
    sm_cmd_response : in std_logic_vector((32 - 1) downto 0);
    sm_cmd_response_pfull : in std_logic_vector((1 - 1) downto 0);
    sm_cmd_response_empty : in std_logic_vector((1 - 1) downto 0);
    sm_cmd_request_pfull : in std_logic_vector((1 - 1) downto 0);
    sm_cmd_request_full : in std_logic_vector((1 - 1) downto 0);
    read_bank_out : out std_logic_vector((32 - 1) downto 0);
    sm_gpio_out8_din : out std_logic_vector((8 - 1) downto 0);
    sm_gpio_out8_en : out std_logic_vector((1 - 1) downto 0);
    sm_cmd_response_re : out std_logic_vector((1 - 1) downto 0);
    sm_cmd_request_din : out std_logic_vector((32 - 1) downto 0);
    sm_cmd_request_we : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mcode_block_57a988c97d;


architecture behavior of mcode_block_57a988c97d is
  signal wrdbus_1_133: unsigned((32 - 1) downto 0);
  signal bankaddr_1_141: unsigned((2 - 1) downto 0);
  signal linearaddr_1_151: unsigned((8 - 1) downto 0);
  signal rnwreg_1_163: unsigned((1 - 1) downto 0);
  signal addrack_1_171: unsigned((1 - 1) downto 0);
  signal sm_gpio_out8_1_180: unsigned((8 - 1) downto 0);
  signal sm_cmd_response_1_194: unsigned((32 - 1) downto 0);
  signal sm_cmd_response_pfull_1_211: unsigned((1 - 1) downto 0);
  signal sm_cmd_response_empty_1_234: boolean;
  signal sm_cmd_request_pfull_1_257: unsigned((1 - 1) downto 0);
  signal sm_cmd_request_full_1_279: boolean;
  signal reg_bank_out_reg_31_30_next: unsigned((32 - 1) downto 0);
  signal reg_bank_out_reg_31_30: unsigned((32 - 1) downto 0) := "00000000000000000000000000000000";
  signal fifo_bank_out_reg_40_31_next: unsigned((32 - 1) downto 0);
  signal fifo_bank_out_reg_40_31: unsigned((32 - 1) downto 0) := "00000000000000000000000000000000";
  signal read_bank_out_reg_111_31_next: unsigned((32 - 1) downto 0);
  signal read_bank_out_reg_111_31: unsigned((32 - 1) downto 0) := "00000000000000000000000000000000";
  signal bankaddr_reg_114_26_next: unsigned((2 - 1) downto 0);
  signal bankaddr_reg_114_26: unsigned((2 - 1) downto 0) := "00";
  signal sm_cmd_response_empty_bus_18_1_convert: unsigned((32 - 1) downto 0);
  signal sm_cmd_request_full_bus_24_1_convert: unsigned((32 - 1) downto 0);
  signal rel_43_4: boolean;
  signal rel_45_8: boolean;
  signal rel_47_8: boolean;
  signal rel_49_8: boolean;
  signal rel_51_8: boolean;
  signal fifo_bank_out_reg_join_43_1: unsigned((32 - 1) downto 0);
  signal opcode_55_1_concat: unsigned((12 - 1) downto 0);
  signal rel_73_4: boolean;
  signal sm_cmd_response_re_join_73_1: boolean;
  signal rel_82_4: boolean;
  signal sm_gpio_out8_en_join_82_1: boolean;
  signal slice_91_39: unsigned((32 - 1) downto 0);
  signal rel_97_4: boolean;
  signal sm_cmd_request_we_join_97_1: boolean;
  signal slice_106_37: unsigned((8 - 1) downto 0);
  signal rel_116_4: boolean;
  signal rel_119_8: boolean;
  signal rel_122_8: boolean;
  signal rel_125_8: boolean;
  signal read_bank_out_reg_join_116_1: unsigned((32 - 1) downto 0);
  signal cast_reg_bank_out_reg_31_30_next: unsigned((32 - 1) downto 0);
begin
  wrdbus_1_133 <= std_logic_vector_to_unsigned(wrdbus);
  bankaddr_1_141 <= std_logic_vector_to_unsigned(bankaddr);
  linearaddr_1_151 <= std_logic_vector_to_unsigned(linearaddr);
  rnwreg_1_163 <= std_logic_vector_to_unsigned(rnwreg);
  addrack_1_171 <= std_logic_vector_to_unsigned(addrack);
  sm_gpio_out8_1_180 <= std_logic_vector_to_unsigned(sm_gpio_out8);
  sm_cmd_response_1_194 <= std_logic_vector_to_unsigned(sm_cmd_response);
  sm_cmd_response_pfull_1_211 <= std_logic_vector_to_unsigned(sm_cmd_response_pfull);
  sm_cmd_response_empty_1_234 <= ((sm_cmd_response_empty) = "1");
  sm_cmd_request_pfull_1_257 <= std_logic_vector_to_unsigned(sm_cmd_request_pfull);
  sm_cmd_request_full_1_279 <= ((sm_cmd_request_full) = "1");
  proc_reg_bank_out_reg_31_30: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        reg_bank_out_reg_31_30 <= reg_bank_out_reg_31_30_next;
      end if;
    end if;
  end process proc_reg_bank_out_reg_31_30;
  proc_fifo_bank_out_reg_40_31: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        fifo_bank_out_reg_40_31 <= fifo_bank_out_reg_40_31_next;
      end if;
    end if;
  end process proc_fifo_bank_out_reg_40_31;
  proc_read_bank_out_reg_111_31: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        read_bank_out_reg_111_31 <= read_bank_out_reg_111_31_next;
      end if;
    end if;
  end process proc_read_bank_out_reg_111_31;
  proc_bankaddr_reg_114_26: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        bankaddr_reg_114_26 <= bankaddr_reg_114_26_next;
      end if;
    end if;
  end process proc_bankaddr_reg_114_26;
  sm_cmd_response_empty_bus_18_1_convert <= u2u_cast(std_logic_vector_to_unsigned(boolean_to_vector(sm_cmd_response_empty_1_234)), 0, 32, 0);
  sm_cmd_request_full_bus_24_1_convert <= u2u_cast(std_logic_vector_to_unsigned(boolean_to_vector(sm_cmd_request_full_1_279)), 0, 32, 0);
  rel_43_4 <= linearaddr_1_151 = std_logic_vector_to_unsigned("00000000");
  rel_45_8 <= linearaddr_1_151 = std_logic_vector_to_unsigned("00000001");
  rel_47_8 <= linearaddr_1_151 = std_logic_vector_to_unsigned("00000010");
  rel_49_8 <= linearaddr_1_151 = std_logic_vector_to_unsigned("00000011");
  rel_51_8 <= linearaddr_1_151 = std_logic_vector_to_unsigned("00000100");
  proc_if_43_1: process (fifo_bank_out_reg_40_31, rel_43_4, rel_45_8, rel_47_8, rel_49_8, rel_51_8, sm_cmd_request_full_bus_24_1_convert, sm_cmd_request_pfull_1_257, sm_cmd_response_1_194, sm_cmd_response_empty_bus_18_1_convert, sm_cmd_response_pfull_1_211)
  is
  begin
    if rel_43_4 then
      fifo_bank_out_reg_join_43_1 <= sm_cmd_response_1_194;
    elsif rel_45_8 then
      fifo_bank_out_reg_join_43_1 <= u2u_cast(sm_cmd_response_pfull_1_211, 0, 32, 0);
    elsif rel_47_8 then
      fifo_bank_out_reg_join_43_1 <= sm_cmd_response_empty_bus_18_1_convert;
    elsif rel_49_8 then
      fifo_bank_out_reg_join_43_1 <= u2u_cast(sm_cmd_request_pfull_1_257, 0, 32, 0);
    elsif rel_51_8 then
      fifo_bank_out_reg_join_43_1 <= sm_cmd_request_full_bus_24_1_convert;
    else 
      fifo_bank_out_reg_join_43_1 <= fifo_bank_out_reg_40_31;
    end if;
  end process proc_if_43_1;
  opcode_55_1_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(addrack_1_171) & unsigned_to_std_logic_vector(rnwreg_1_163) & unsigned_to_std_logic_vector(bankaddr_1_141) & unsigned_to_std_logic_vector(linearaddr_1_151));
  rel_73_4 <= opcode_55_1_concat = std_logic_vector_to_unsigned("110100000000");
  proc_if_73_1: process (rel_73_4)
  is
  begin
    if rel_73_4 then
      sm_cmd_response_re_join_73_1 <= true;
    else 
      sm_cmd_response_re_join_73_1 <= false;
    end if;
  end process proc_if_73_1;
  rel_82_4 <= opcode_55_1_concat = std_logic_vector_to_unsigned("101000000000");
  proc_if_82_1: process (rel_82_4)
  is
  begin
    if rel_82_4 then
      sm_gpio_out8_en_join_82_1 <= true;
    else 
      sm_gpio_out8_en_join_82_1 <= false;
    end if;
  end process proc_if_82_1;
  slice_91_39 <= u2u_slice(wrdbus_1_133, 31, 0);
  rel_97_4 <= opcode_55_1_concat = std_logic_vector_to_unsigned("100100000000");
  proc_if_97_1: process (rel_97_4)
  is
  begin
    if rel_97_4 then
      sm_cmd_request_we_join_97_1 <= true;
    else 
      sm_cmd_request_we_join_97_1 <= false;
    end if;
  end process proc_if_97_1;
  slice_106_37 <= u2u_slice(wrdbus_1_133, 7, 0);
  rel_116_4 <= bankaddr_reg_114_26 = std_logic_vector_to_unsigned("00");
  rel_119_8 <= bankaddr_reg_114_26 = std_logic_vector_to_unsigned("01");
  rel_122_8 <= bankaddr_reg_114_26 = std_logic_vector_to_unsigned("10");
  rel_125_8 <= bankaddr_reg_114_26 = std_logic_vector_to_unsigned("11");
  proc_if_116_1: process (fifo_bank_out_reg_40_31, read_bank_out_reg_111_31, reg_bank_out_reg_31_30, rel_116_4, rel_119_8, rel_122_8, rel_125_8)
  is
  begin
    if rel_116_4 then
      read_bank_out_reg_join_116_1 <= std_logic_vector_to_unsigned("00000000000000000000000000000000");
    elsif rel_119_8 then
      read_bank_out_reg_join_116_1 <= fifo_bank_out_reg_40_31;
    elsif rel_122_8 then
      read_bank_out_reg_join_116_1 <= reg_bank_out_reg_31_30;
    elsif rel_125_8 then
      read_bank_out_reg_join_116_1 <= std_logic_vector_to_unsigned("00000000000000000000000000000000");
    else 
      read_bank_out_reg_join_116_1 <= read_bank_out_reg_111_31;
    end if;
  end process proc_if_116_1;
  cast_reg_bank_out_reg_31_30_next <= u2u_cast(sm_gpio_out8_1_180, 0, 32, 0);
  reg_bank_out_reg_31_30_next <= cast_reg_bank_out_reg_31_30_next;
  fifo_bank_out_reg_40_31_next <= fifo_bank_out_reg_join_43_1;
  read_bank_out_reg_111_31_next <= read_bank_out_reg_join_116_1;
  bankaddr_reg_114_26_next <= bankaddr_1_141;
  read_bank_out <= unsigned_to_std_logic_vector(read_bank_out_reg_111_31);
  sm_gpio_out8_din <= unsigned_to_std_logic_vector(slice_106_37);
  sm_gpio_out8_en <= boolean_to_vector(sm_gpio_out8_en_join_82_1);
  sm_cmd_response_re <= boolean_to_vector(sm_cmd_response_re_join_73_1);
  sm_cmd_request_din <= unsigned_to_std_logic_vector(slice_91_39);
  sm_cmd_request_we <= boolean_to_vector(sm_cmd_request_we_join_97_1);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity inverter_e5b38cca3b is
  port (
    ip : in std_logic_vector((1 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end inverter_e5b38cca3b;


architecture behavior of inverter_e5b38cca3b is
  signal ip_1_26: boolean;
  type array_type_op_mem_22_20 is array (0 to (1 - 1)) of boolean;
  signal op_mem_22_20: array_type_op_mem_22_20 := (
    0 => false);
  signal op_mem_22_20_front_din: boolean;
  signal op_mem_22_20_back: boolean;
  signal op_mem_22_20_push_front_pop_back_en: std_logic;
  signal internal_ip_12_1_bitnot: boolean;
begin
  ip_1_26 <= ((ip) = "1");
  op_mem_22_20_back <= op_mem_22_20(0);
  proc_op_mem_22_20: process (clk)
  is
    variable i: integer;
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (op_mem_22_20_push_front_pop_back_en = '1')) then
        op_mem_22_20(0) <= op_mem_22_20_front_din;
      end if;
    end if;
  end process proc_op_mem_22_20;
  internal_ip_12_1_bitnot <= ((not boolean_to_vector(ip_1_26)) = "1");
  op_mem_22_20_push_front_pop_back_en <= '0';
  op <= boolean_to_vector(internal_ip_12_1_bitnot);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mcode_block_f21d0469ad is
  port (
    out_port : in std_logic_vector((8 - 1) downto 0);
    port_id : in std_logic_vector((8 - 1) downto 0);
    rs : in std_logic_vector((1 - 1) downto 0);
    ws : in std_logic_vector((1 - 1) downto 0);
    sda_i : in std_logic_vector((1 - 1) downto 0);
    cmd_req : in std_logic_vector((32 - 1) downto 0);
    cmd_rdy : in std_logic_vector((1 - 1) downto 0);
    in_port : out std_logic_vector((8 - 1) downto 0);
    reset_dcm_o : out std_logic_vector((1 - 1) downto 0);
    sda_o : out std_logic_vector((1 - 1) downto 0);
    scl_o : out std_logic_vector((1 - 1) downto 0);
    cmd_get : out std_logic_vector((1 - 1) downto 0);
    cmd_rsp : out std_logic_vector((32 - 1) downto 0);
    cmd_ack : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mcode_block_f21d0469ad;


architecture behavior of mcode_block_f21d0469ad is
  signal out_port_1_91: unsigned((8 - 1) downto 0);
  signal port_id_1_101: unsigned((8 - 1) downto 0);
  signal rs_1_110: boolean;
  signal ws_1_114: boolean;
  signal sda_i_1_118: boolean;
  signal cmd_req_1_125: unsigned((32 - 1) downto 0);
  signal cmd_rdy_1_134: boolean;
  signal reset_dcm_reg_4_27_next: boolean;
  signal reset_dcm_reg_4_27: boolean := false;
  signal reset_dcm_reg_4_27_en: std_logic;
  signal sda_reg_5_27_next: boolean;
  signal sda_reg_5_27: boolean := false;
  signal sda_reg_5_27_en: std_logic;
  signal scl_reg_6_27_next: boolean;
  signal scl_reg_6_27: boolean := false;
  signal scl_reg_6_27_en: std_logic;
  signal cmd_get_reg_7_27_next: boolean;
  signal cmd_get_reg_7_27: boolean := false;
  signal cmd_ack_reg_8_27_next: boolean;
  signal cmd_ack_reg_8_27: boolean := false;
  signal cmd_rsp0_reg_9_27_next: unsigned((8 - 1) downto 0);
  signal cmd_rsp0_reg_9_27: unsigned((8 - 1) downto 0) := "00000000";
  signal cmd_rsp0_reg_9_27_en: std_logic;
  signal cmd_rsp1_reg_10_27_next: unsigned((8 - 1) downto 0);
  signal cmd_rsp1_reg_10_27: unsigned((8 - 1) downto 0) := "00000000";
  signal cmd_rsp1_reg_10_27_en: std_logic;
  signal cmd_rsp2_reg_11_27_next: unsigned((8 - 1) downto 0);
  signal cmd_rsp2_reg_11_27: unsigned((8 - 1) downto 0) := "00000000";
  signal cmd_rsp2_reg_11_27_en: std_logic;
  signal cmd_rsp3_reg_12_27_next: unsigned((8 - 1) downto 0);
  signal cmd_rsp3_reg_12_27: unsigned((8 - 1) downto 0) := "00000000";
  signal cmd_rsp3_reg_12_27_en: std_logic;
  signal rel_22_6: boolean;
  signal rel_24_10: boolean;
  signal rel_26_10: boolean;
  signal rel_28_10: boolean;
  signal rel_30_10: boolean;
  signal rel_32_10: boolean;
  signal rel_34_10: boolean;
  signal reset_sel_join_22_1: boolean;
  signal i2c_sel_join_22_1: boolean;
  signal cmd_ctrl_sel_join_22_1: boolean;
  signal cmd_dat0_sel_join_22_1: boolean;
  signal cmd_dat1_sel_join_22_1: boolean;
  signal cmd_dat2_sel_join_22_1: boolean;
  signal cmd_dat3_sel_join_22_1: boolean;
  signal reset_we_39_1_bit: boolean;
  signal i2c_we_40_1_bit: boolean;
  signal cmd_ctrl_we_41_1_bit: boolean;
  signal cmd_dat0_we_42_1_bit: boolean;
  signal cmd_dat1_we_43_1_bit: boolean;
  signal cmd_dat2_we_44_1_bit: boolean;
  signal cmd_dat3_we_45_1_bit: boolean;
  signal slice_49_43: unsigned((1 - 1) downto 0);
  signal reset_dcm_49_5_convert: boolean;
  signal rel_48_6: boolean;
  signal reset_dcm_join_48_1: boolean;
  signal reset_dcm_join_48_1_en: std_logic;
  signal slice_56_37: unsigned((1 - 1) downto 0);
  signal sda_56_5_convert: boolean;
  signal slice_55_47: unsigned((1 - 1) downto 0);
  signal convert_55_26: boolean;
  signal bit_55_14: boolean;
  signal rel_55_12: boolean;
  signal sda_join_55_1: boolean;
  signal sda_join_55_1_en: std_logic;
  signal slice_63_37: unsigned((1 - 1) downto 0);
  signal scl_63_5_convert: boolean;
  signal slice_62_46: unsigned((1 - 1) downto 0);
  signal convert_62_25: boolean;
  signal bit_62_13: boolean;
  signal rel_62_11: boolean;
  signal scl_join_62_1: boolean;
  signal scl_join_62_1_en: std_logic;
  signal slice_70_41: unsigned((1 - 1) downto 0);
  signal cmd_get_70_5_convert: boolean;
  signal slice_71_41: unsigned((1 - 1) downto 0);
  signal cmd_ack_71_5_convert: boolean;
  signal rel_69_6: boolean;
  signal cmd_ack_join_69_1: boolean;
  signal cmd_get_join_69_1: boolean;
  signal rel_76_6: boolean;
  signal cmd_rsp0_join_76_1: unsigned((8 - 1) downto 0);
  signal cmd_rsp0_join_76_1_en: std_logic;
  signal rel_81_6: boolean;
  signal cmd_rsp1_join_81_1: unsigned((8 - 1) downto 0);
  signal cmd_rsp1_join_81_1_en: std_logic;
  signal rel_86_6: boolean;
  signal cmd_rsp2_join_86_1: unsigned((8 - 1) downto 0);
  signal cmd_rsp2_join_86_1_en: std_logic;
  signal rel_91_6: boolean;
  signal cmd_rsp3_join_91_1: unsigned((8 - 1) downto 0);
  signal cmd_rsp3_join_91_1_en: std_logic;
  signal convert_99_56: unsigned((1 - 1) downto 0);
  signal in_port_99_5_concat: unsigned((8 - 1) downto 0);
  signal convert_101_56: unsigned((1 - 1) downto 0);
  signal in_port_101_5_concat: unsigned((8 - 1) downto 0);
  signal in_port_103_5_slice: unsigned((8 - 1) downto 0);
  signal in_port_105_5_slice: unsigned((8 - 1) downto 0);
  signal in_port_107_5_slice: unsigned((8 - 1) downto 0);
  signal in_port_109_5_slice: unsigned((8 - 1) downto 0);
  signal rel_98_6: boolean;
  signal rel_100_10: boolean;
  signal rel_102_10: boolean;
  signal rel_104_10: boolean;
  signal rel_106_10: boolean;
  signal rel_108_10: boolean;
  signal in_port_join_98_1: unsigned((8 - 1) downto 0);
  signal cmd_rsp_118_1_concat: unsigned((32 - 1) downto 0);
begin
  out_port_1_91 <= std_logic_vector_to_unsigned(out_port);
  port_id_1_101 <= std_logic_vector_to_unsigned(port_id);
  rs_1_110 <= ((rs) = "1");
  ws_1_114 <= ((ws) = "1");
  sda_i_1_118 <= ((sda_i) = "1");
  cmd_req_1_125 <= std_logic_vector_to_unsigned(cmd_req);
  cmd_rdy_1_134 <= ((cmd_rdy) = "1");
  proc_reset_dcm_reg_4_27: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (reset_dcm_reg_4_27_en = '1')) then
        reset_dcm_reg_4_27 <= reset_dcm_reg_4_27_next;
      end if;
    end if;
  end process proc_reset_dcm_reg_4_27;
  proc_sda_reg_5_27: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (sda_reg_5_27_en = '1')) then
        sda_reg_5_27 <= sda_reg_5_27_next;
      end if;
    end if;
  end process proc_sda_reg_5_27;
  proc_scl_reg_6_27: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (scl_reg_6_27_en = '1')) then
        scl_reg_6_27 <= scl_reg_6_27_next;
      end if;
    end if;
  end process proc_scl_reg_6_27;
  proc_cmd_get_reg_7_27: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        cmd_get_reg_7_27 <= cmd_get_reg_7_27_next;
      end if;
    end if;
  end process proc_cmd_get_reg_7_27;
  proc_cmd_ack_reg_8_27: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if (ce = '1') then
        cmd_ack_reg_8_27 <= cmd_ack_reg_8_27_next;
      end if;
    end if;
  end process proc_cmd_ack_reg_8_27;
  proc_cmd_rsp0_reg_9_27: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (cmd_rsp0_reg_9_27_en = '1')) then
        cmd_rsp0_reg_9_27 <= cmd_rsp0_reg_9_27_next;
      end if;
    end if;
  end process proc_cmd_rsp0_reg_9_27;
  proc_cmd_rsp1_reg_10_27: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (cmd_rsp1_reg_10_27_en = '1')) then
        cmd_rsp1_reg_10_27 <= cmd_rsp1_reg_10_27_next;
      end if;
    end if;
  end process proc_cmd_rsp1_reg_10_27;
  proc_cmd_rsp2_reg_11_27: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (cmd_rsp2_reg_11_27_en = '1')) then
        cmd_rsp2_reg_11_27 <= cmd_rsp2_reg_11_27_next;
      end if;
    end if;
  end process proc_cmd_rsp2_reg_11_27;
  proc_cmd_rsp3_reg_12_27: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (cmd_rsp3_reg_12_27_en = '1')) then
        cmd_rsp3_reg_12_27 <= cmd_rsp3_reg_12_27_next;
      end if;
    end if;
  end process proc_cmd_rsp3_reg_12_27;
  rel_22_6 <= port_id_1_101 = std_logic_vector_to_unsigned("00000000");
  rel_24_10 <= port_id_1_101 = std_logic_vector_to_unsigned("00000001");
  rel_26_10 <= port_id_1_101 = std_logic_vector_to_unsigned("00000011");
  rel_28_10 <= port_id_1_101 = std_logic_vector_to_unsigned("00000100");
  rel_30_10 <= port_id_1_101 = std_logic_vector_to_unsigned("00000101");
  rel_32_10 <= port_id_1_101 = std_logic_vector_to_unsigned("00000110");
  rel_34_10 <= port_id_1_101 = std_logic_vector_to_unsigned("00000111");
  proc_if_22_1: process (rel_22_6, rel_24_10, rel_26_10, rel_28_10, rel_30_10, rel_32_10, rel_34_10)
  is
  begin
    if rel_22_6 then
      reset_sel_join_22_1 <= true;
      i2c_sel_join_22_1 <= false;
      cmd_ctrl_sel_join_22_1 <= false;
      cmd_dat0_sel_join_22_1 <= false;
      cmd_dat1_sel_join_22_1 <= false;
      cmd_dat2_sel_join_22_1 <= false;
      cmd_dat3_sel_join_22_1 <= false;
    elsif rel_24_10 then
      reset_sel_join_22_1 <= false;
      i2c_sel_join_22_1 <= true;
      cmd_ctrl_sel_join_22_1 <= false;
      cmd_dat0_sel_join_22_1 <= false;
      cmd_dat1_sel_join_22_1 <= false;
      cmd_dat2_sel_join_22_1 <= false;
      cmd_dat3_sel_join_22_1 <= false;
    elsif rel_26_10 then
      reset_sel_join_22_1 <= false;
      i2c_sel_join_22_1 <= false;
      cmd_ctrl_sel_join_22_1 <= true;
      cmd_dat0_sel_join_22_1 <= false;
      cmd_dat1_sel_join_22_1 <= false;
      cmd_dat2_sel_join_22_1 <= false;
      cmd_dat3_sel_join_22_1 <= false;
    elsif rel_28_10 then
      reset_sel_join_22_1 <= false;
      i2c_sel_join_22_1 <= false;
      cmd_ctrl_sel_join_22_1 <= false;
      cmd_dat0_sel_join_22_1 <= true;
      cmd_dat1_sel_join_22_1 <= false;
      cmd_dat2_sel_join_22_1 <= false;
      cmd_dat3_sel_join_22_1 <= false;
    elsif rel_30_10 then
      reset_sel_join_22_1 <= false;
      i2c_sel_join_22_1 <= false;
      cmd_ctrl_sel_join_22_1 <= false;
      cmd_dat0_sel_join_22_1 <= false;
      cmd_dat1_sel_join_22_1 <= true;
      cmd_dat2_sel_join_22_1 <= false;
      cmd_dat3_sel_join_22_1 <= false;
    elsif rel_32_10 then
      reset_sel_join_22_1 <= false;
      i2c_sel_join_22_1 <= false;
      cmd_ctrl_sel_join_22_1 <= false;
      cmd_dat0_sel_join_22_1 <= false;
      cmd_dat1_sel_join_22_1 <= false;
      cmd_dat2_sel_join_22_1 <= true;
      cmd_dat3_sel_join_22_1 <= false;
    elsif rel_34_10 then
      reset_sel_join_22_1 <= false;
      i2c_sel_join_22_1 <= false;
      cmd_ctrl_sel_join_22_1 <= false;
      cmd_dat0_sel_join_22_1 <= false;
      cmd_dat1_sel_join_22_1 <= false;
      cmd_dat2_sel_join_22_1 <= false;
      cmd_dat3_sel_join_22_1 <= true;
    else 
      reset_sel_join_22_1 <= false;
      i2c_sel_join_22_1 <= false;
      cmd_ctrl_sel_join_22_1 <= false;
      cmd_dat0_sel_join_22_1 <= false;
      cmd_dat1_sel_join_22_1 <= false;
      cmd_dat2_sel_join_22_1 <= false;
      cmd_dat3_sel_join_22_1 <= false;
    end if;
  end process proc_if_22_1;
  reset_we_39_1_bit <= ((boolean_to_vector(reset_sel_join_22_1) and boolean_to_vector(ws_1_114)) = "1");
  i2c_we_40_1_bit <= ((boolean_to_vector(i2c_sel_join_22_1) and boolean_to_vector(ws_1_114)) = "1");
  cmd_ctrl_we_41_1_bit <= ((boolean_to_vector(cmd_ctrl_sel_join_22_1) and boolean_to_vector(ws_1_114)) = "1");
  cmd_dat0_we_42_1_bit <= ((boolean_to_vector(cmd_dat0_sel_join_22_1) and boolean_to_vector(ws_1_114)) = "1");
  cmd_dat1_we_43_1_bit <= ((boolean_to_vector(cmd_dat1_sel_join_22_1) and boolean_to_vector(ws_1_114)) = "1");
  cmd_dat2_we_44_1_bit <= ((boolean_to_vector(cmd_dat2_sel_join_22_1) and boolean_to_vector(ws_1_114)) = "1");
  cmd_dat3_we_45_1_bit <= ((boolean_to_vector(cmd_dat3_sel_join_22_1) and boolean_to_vector(ws_1_114)) = "1");
  slice_49_43 <= u2u_slice(out_port_1_91, 0, 0);
  reset_dcm_49_5_convert <= (slice_49_43 /= "0");
  rel_48_6 <= reset_we_39_1_bit = true;
  proc_if_48_1: process (rel_48_6, reset_dcm_49_5_convert)
  is
  begin
    if rel_48_6 then
      reset_dcm_join_48_1_en <= '1';
    else 
      reset_dcm_join_48_1_en <= '0';
    end if;
    reset_dcm_join_48_1 <= reset_dcm_49_5_convert;
  end process proc_if_48_1;
  slice_56_37 <= u2u_slice(out_port_1_91, 0, 0);
  sda_56_5_convert <= (slice_56_37 /= "0");
  slice_55_47 <= u2u_slice(out_port_1_91, 1, 1);
  convert_55_26 <= (slice_55_47 /= "0");
  bit_55_14 <= ((boolean_to_vector(i2c_we_40_1_bit) and boolean_to_vector(convert_55_26)) = "1");
  rel_55_12 <= bit_55_14 = true;
  proc_if_55_1: process (rel_55_12, sda_56_5_convert)
  is
  begin
    if rel_55_12 then
      sda_join_55_1_en <= '1';
    else 
      sda_join_55_1_en <= '0';
    end if;
    sda_join_55_1 <= sda_56_5_convert;
  end process proc_if_55_1;
  slice_63_37 <= u2u_slice(out_port_1_91, 2, 2);
  scl_63_5_convert <= (slice_63_37 /= "0");
  slice_62_46 <= u2u_slice(out_port_1_91, 3, 3);
  convert_62_25 <= (slice_62_46 /= "0");
  bit_62_13 <= ((boolean_to_vector(i2c_we_40_1_bit) and boolean_to_vector(convert_62_25)) = "1");
  rel_62_11 <= bit_62_13 = true;
  proc_if_62_1: process (rel_62_11, scl_63_5_convert)
  is
  begin
    if rel_62_11 then
      scl_join_62_1_en <= '1';
    else 
      scl_join_62_1_en <= '0';
    end if;
    scl_join_62_1 <= scl_63_5_convert;
  end process proc_if_62_1;
  slice_70_41 <= u2u_slice(out_port_1_91, 1, 1);
  cmd_get_70_5_convert <= (slice_70_41 /= "0");
  slice_71_41 <= u2u_slice(out_port_1_91, 0, 0);
  cmd_ack_71_5_convert <= (slice_71_41 /= "0");
  rel_69_6 <= cmd_ctrl_we_41_1_bit = true;
  proc_if_69_1: process (cmd_ack_71_5_convert, cmd_get_70_5_convert, rel_69_6)
  is
  begin
    if rel_69_6 then
      cmd_ack_join_69_1 <= cmd_ack_71_5_convert;
      cmd_get_join_69_1 <= cmd_get_70_5_convert;
    else 
      cmd_ack_join_69_1 <= false;
      cmd_get_join_69_1 <= false;
    end if;
  end process proc_if_69_1;
  rel_76_6 <= cmd_dat0_we_42_1_bit = true;
  proc_if_76_1: process (out_port_1_91, rel_76_6)
  is
  begin
    if rel_76_6 then
      cmd_rsp0_join_76_1_en <= '1';
    else 
      cmd_rsp0_join_76_1_en <= '0';
    end if;
    cmd_rsp0_join_76_1 <= out_port_1_91;
  end process proc_if_76_1;
  rel_81_6 <= cmd_dat1_we_43_1_bit = true;
  proc_if_81_1: process (out_port_1_91, rel_81_6)
  is
  begin
    if rel_81_6 then
      cmd_rsp1_join_81_1_en <= '1';
    else 
      cmd_rsp1_join_81_1_en <= '0';
    end if;
    cmd_rsp1_join_81_1 <= out_port_1_91;
  end process proc_if_81_1;
  rel_86_6 <= cmd_dat2_we_44_1_bit = true;
  proc_if_86_1: process (out_port_1_91, rel_86_6)
  is
  begin
    if rel_86_6 then
      cmd_rsp2_join_86_1_en <= '1';
    else 
      cmd_rsp2_join_86_1_en <= '0';
    end if;
    cmd_rsp2_join_86_1 <= out_port_1_91;
  end process proc_if_86_1;
  rel_91_6 <= cmd_dat3_we_45_1_bit = true;
  proc_if_91_1: process (out_port_1_91, rel_91_6)
  is
  begin
    if rel_91_6 then
      cmd_rsp3_join_91_1_en <= '1';
    else 
      cmd_rsp3_join_91_1_en <= '0';
    end if;
    cmd_rsp3_join_91_1 <= out_port_1_91;
  end process proc_if_91_1;
  convert_99_56 <= u2u_cast(std_logic_vector_to_unsigned(boolean_to_vector(sda_i_1_118)), 0, 1, 0);
  in_port_99_5_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(std_logic_vector_to_unsigned("0000000")) & unsigned_to_std_logic_vector(convert_99_56));
  convert_101_56 <= u2u_cast(std_logic_vector_to_unsigned(boolean_to_vector(cmd_rdy_1_134)), 0, 1, 0);
  in_port_101_5_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(std_logic_vector_to_unsigned("0000000")) & unsigned_to_std_logic_vector(convert_101_56));
  in_port_103_5_slice <= u2u_slice(cmd_req_1_125, 7, 0);
  in_port_105_5_slice <= u2u_slice(cmd_req_1_125, 15, 8);
  in_port_107_5_slice <= u2u_slice(cmd_req_1_125, 23, 16);
  in_port_109_5_slice <= u2u_slice(cmd_req_1_125, 31, 24);
  rel_98_6 <= i2c_sel_join_22_1 = true;
  rel_100_10 <= cmd_ctrl_sel_join_22_1 = true;
  rel_102_10 <= cmd_dat0_sel_join_22_1 = true;
  rel_104_10 <= cmd_dat1_sel_join_22_1 = true;
  rel_106_10 <= cmd_dat2_sel_join_22_1 = true;
  rel_108_10 <= cmd_dat3_sel_join_22_1 = true;
  proc_if_98_1: process (in_port_101_5_concat, in_port_103_5_slice, in_port_105_5_slice, in_port_107_5_slice, in_port_109_5_slice, in_port_99_5_concat, rel_100_10, rel_102_10, rel_104_10, rel_106_10, rel_108_10, rel_98_6)
  is
  begin
    if rel_98_6 then
      in_port_join_98_1 <= in_port_99_5_concat;
    elsif rel_100_10 then
      in_port_join_98_1 <= in_port_101_5_concat;
    elsif rel_102_10 then
      in_port_join_98_1 <= in_port_103_5_slice;
    elsif rel_104_10 then
      in_port_join_98_1 <= in_port_105_5_slice;
    elsif rel_106_10 then
      in_port_join_98_1 <= in_port_107_5_slice;
    elsif rel_108_10 then
      in_port_join_98_1 <= in_port_109_5_slice;
    else 
      in_port_join_98_1 <= std_logic_vector_to_unsigned("00000000");
    end if;
  end process proc_if_98_1;
  cmd_rsp_118_1_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(cmd_rsp3_reg_12_27) & unsigned_to_std_logic_vector(cmd_rsp2_reg_11_27) & unsigned_to_std_logic_vector(cmd_rsp1_reg_10_27) & unsigned_to_std_logic_vector(cmd_rsp0_reg_9_27));
  reset_dcm_reg_4_27_next <= reset_dcm_49_5_convert;
  reset_dcm_reg_4_27_en <= reset_dcm_join_48_1_en;
  sda_reg_5_27_next <= sda_56_5_convert;
  sda_reg_5_27_en <= sda_join_55_1_en;
  scl_reg_6_27_next <= scl_63_5_convert;
  scl_reg_6_27_en <= scl_join_62_1_en;
  cmd_get_reg_7_27_next <= cmd_get_join_69_1;
  cmd_ack_reg_8_27_next <= cmd_ack_join_69_1;
  cmd_rsp0_reg_9_27_next <= out_port_1_91;
  cmd_rsp0_reg_9_27_en <= cmd_rsp0_join_76_1_en;
  cmd_rsp1_reg_10_27_next <= out_port_1_91;
  cmd_rsp1_reg_10_27_en <= cmd_rsp1_join_81_1_en;
  cmd_rsp2_reg_11_27_next <= out_port_1_91;
  cmd_rsp2_reg_11_27_en <= cmd_rsp2_join_86_1_en;
  cmd_rsp3_reg_12_27_next <= out_port_1_91;
  cmd_rsp3_reg_12_27_en <= cmd_rsp3_join_91_1_en;
  in_port <= unsigned_to_std_logic_vector(in_port_join_98_1);
  reset_dcm_o <= boolean_to_vector(reset_dcm_reg_4_27);
  sda_o <= boolean_to_vector(sda_reg_5_27);
  scl_o <= boolean_to_vector(scl_reg_6_27);
  cmd_get <= boolean_to_vector(cmd_get_reg_7_27);
  cmd_rsp <= unsigned_to_std_logic_vector(cmd_rsp_118_1_concat);
  cmd_ack <= boolean_to_vector(cmd_ack_reg_8_27);
end behavior;


-------------------------------------------------------------------
-- System Generator version 12.1 VHDL source file.
--
-- Copyright(C) 2010 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2010 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use work.conv_pkg.all;
entity xlsprom is
  generic (
    core_name0: string := "";
    c_width: integer := 12;
    c_address_width: integer := 4;
    latency: integer := 1
  );
  port (
    addr: in std_logic_vector(c_address_width - 1 downto 0);
    en: in std_logic_vector(0 downto 0);
    rst: in std_logic_vector(0 downto 0);
    ce: in std_logic;
    clk: in std_logic;
    data: out std_logic_vector(c_width - 1 downto 0)
  );
end xlsprom ;
architecture behavior of xlsprom is
  component synth_reg
    generic (
      width: integer;
      latency: integer
    );
    port (
      i: in std_logic_vector(width - 1 downto 0);
      ce: in std_logic;
      clr: in std_logic;
      clk: in std_logic;
      o: out std_logic_vector(width - 1 downto 0)
    );
  end component;
  signal core_addr: std_logic_vector(c_address_width - 1 downto 0);
  signal core_data_out: std_logic_vector(c_width - 1 downto 0);
  signal core_ce, sinit: std_logic;
  component bmg_41_99d18de731b34188
    port (
                              addra: in std_logic_vector(c_address_width - 1 downto 0);
      clka: in std_logic;
      ena: in std_logic;
      douta: out std_logic_vector(c_width - 1 downto 0)
    );
  end component;
  attribute syn_black_box of bmg_41_99d18de731b34188:
    component is true;
  attribute fpga_dont_touch of bmg_41_99d18de731b34188:
    component is "true";
  attribute box_type of bmg_41_99d18de731b34188:
    component  is "black_box";
begin
  core_addr <= addr;
  core_ce <= ce and en(0);
  sinit <= rst(0) and ce;
  comp0: if ((core_name0 = "bmg_41_99d18de731b34188")) generate
    core_instance0: bmg_41_99d18de731b34188
      port map (
        addra => core_addr,
        clka => clk,
        ena => core_ce,
        douta => core_data_out
                        );
  end generate;
  latency_test: if (latency > 1) generate
    reg: synth_reg
      generic map (
        width => c_width,
        latency => latency - 1
      )
      port map (
        i => core_data_out,
        ce => core_ce,
        clr => '0',
        clk => clk,
        o => data
      );
  end generate;
  latency_1: if (latency <= 1) generate
    data <= core_data_out;
  end generate;
end  behavior;

-------------------------------------------------------------------
-- System Generator version 12.1 VHDL source file.
--
-- Copyright(C) 2010 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2010 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
library unisim;
use unisim.vcomponents.all;
entity kcpsm3 is
    Port (      address : out std_logic_vector(9 downto 0);
            instruction : in std_logic_vector(17 downto 0);
                port_id : out std_logic_vector(7 downto 0);
           write_strobe : out std_logic;
               out_port : out std_logic_vector(7 downto 0);
            read_strobe : out std_logic;
                in_port : in std_logic_vector(7 downto 0);
              interrupt : in std_logic;
          interrupt_ack : out std_logic;
                  reset : in std_logic;
                    clk : in std_logic);
    end kcpsm3;
architecture low_level_definition of kcpsm3 is
signal t_state                : std_logic;
signal not_t_state            : std_logic;
signal internal_reset         : std_logic;
signal reset_delay            : std_logic;
signal move_group             : std_logic;
signal condition_met          : std_logic;
signal normal_count           : std_logic;
signal call_type              : std_logic;
signal push_or_pop_type       : std_logic;
signal valid_to_move          : std_logic;
signal flag_type              : std_logic;
signal flag_write             : std_logic;
signal flag_enable            : std_logic;
signal zero_flag              : std_logic;
signal sel_shadow_zero        : std_logic;
signal low_zero               : std_logic;
signal high_zero              : std_logic;
signal low_zero_carry         : std_logic;
signal high_zero_carry        : std_logic;
signal zero_carry             : std_logic;
signal zero_fast_route        : std_logic;
signal low_parity             : std_logic;
signal high_parity            : std_logic;
signal parity_carry           : std_logic;
signal parity                 : std_logic;
signal carry_flag             : std_logic;
signal sel_parity             : std_logic;
signal sel_arith_carry        : std_logic;
signal sel_shift_carry        : std_logic;
signal sel_shadow_carry       : std_logic;
signal sel_carry              : std_logic_vector(3 downto 0);
signal carry_fast_route       : std_logic;
signal active_interrupt       : std_logic;
signal int_pulse              : std_logic;
signal clean_int              : std_logic;
signal shadow_carry           : std_logic;
signal shadow_zero            : std_logic;
signal int_enable             : std_logic;
signal int_update_enable      : std_logic;
signal int_enable_value       : std_logic;
signal interrupt_ack_internal : std_logic;
signal pc                     : std_logic_vector(9 downto 0);
signal pc_vector              : std_logic_vector(9 downto 0);
signal pc_vector_carry        : std_logic_vector(8 downto 0);
signal inc_pc_vector          : std_logic_vector(9 downto 0);
signal pc_value               : std_logic_vector(9 downto 0);
signal pc_value_carry         : std_logic_vector(8 downto 0);
signal inc_pc_value           : std_logic_vector(9 downto 0);
signal pc_enable              : std_logic;
signal sx                     : std_logic_vector(7 downto 0);
signal sy                     : std_logic_vector(7 downto 0);
signal register_type          : std_logic;
signal register_write         : std_logic;
signal register_enable        : std_logic;
signal second_operand         : std_logic_vector(7 downto 0);
signal memory_data            : std_logic_vector(7 downto 0);
signal store_data             : std_logic_vector(7 downto 0);
signal memory_type            : std_logic;
signal memory_write           : std_logic;
signal memory_enable          : std_logic;
signal stack_pop_data         : std_logic_vector(9 downto 0);
signal stack_ram_data         : std_logic_vector(9 downto 0);
signal stack_address          : std_logic_vector(4 downto 0);
signal half_stack_address     : std_logic_vector(4 downto 0);
signal stack_address_carry    : std_logic_vector(3 downto 0);
signal next_stack_address     : std_logic_vector(4 downto 0);
signal stack_write_enable     : std_logic;
signal not_active_interrupt   : std_logic;
signal logical_result         : std_logic_vector(7 downto 0);
signal logical_value          : std_logic_vector(7 downto 0);
signal sel_logical            : std_logic;
signal shift_result           : std_logic_vector(7 downto 0);
signal shift_value            : std_logic_vector(7 downto 0);
signal sel_shift              : std_logic;
signal high_shift_in          : std_logic;
signal low_shift_in           : std_logic;
signal shift_in               : std_logic;
signal shift_carry            : std_logic;
signal shift_carry_value      : std_logic;
signal arith_result           : std_logic_vector(7 downto 0);
signal arith_value            : std_logic_vector(7 downto 0);
signal half_arith             : std_logic_vector(7 downto 0);
signal arith_internal_carry   : std_logic_vector(7 downto 0);
signal sel_arith_carry_in     : std_logic;
signal arith_carry_in         : std_logic;
signal invert_arith_carry     : std_logic;
signal arith_carry_out        : std_logic;
signal sel_arith              : std_logic;
signal arith_carry            : std_logic;
signal input_fetch_type       : std_logic;
signal sel_group              : std_logic;
signal alu_group              : std_logic_vector(7 downto 0);
signal input_group            : std_logic_vector(7 downto 0);
signal alu_result             : std_logic_vector(7 downto 0);
signal io_initial_decode      : std_logic;
signal write_active           : std_logic;
signal read_active            : std_logic;
attribute INIT : string;
attribute INIT of t_state_lut           : label is "1";
attribute INIT of int_pulse_lut         : label is "0080";
attribute INIT of int_update_lut        : label is "EAAA";
attribute INIT of int_value_lut         : label is "04";
attribute INIT of move_group_lut        : label is "7400";
attribute INIT of condition_met_lut     : label is "5A3C";
attribute INIT of normal_count_lut      : label is "2F";
attribute INIT of call_type_lut         : label is "1000";
attribute INIT of push_pop_lut          : label is "5400";
attribute INIT of valid_move_lut        : label is "D";
attribute INIT of flag_type_lut         : label is "41FC";
attribute INIT of flag_enable_lut       : label is "8";
attribute INIT of low_zero_lut          : label is "0001";
attribute INIT of high_zero_lut         : label is "0001";
attribute INIT of sel_shadow_zero_lut   : label is "3F";
attribute INIT of low_parity_lut        : label is "6996";
attribute INIT of high_parity_lut       : label is "6996";
attribute INIT of sel_parity_lut        : label is "F3FF";
attribute INIT of sel_arith_carry_lut   : label is "F3";
attribute INIT of sel_shift_carry_lut   : label is "C";
attribute INIT of sel_shadow_carry_lut  : label is "3";
attribute INIT of register_type_lut     : label is "0145";
attribute INIT of register_enable_lut   : label is "8";
attribute INIT of memory_type_lut       : label is "0400";
attribute INIT of memory_enable_lut     : label is "8000";
attribute INIT of sel_logical_lut       : label is "FFE2";
attribute INIT of low_shift_in_lut      : label is "E4";
attribute INIT of high_shift_in_lut     : label is "E4";
attribute INIT of shift_carry_lut       : label is "E4";
attribute INIT of sel_arith_lut         : label is "1F";
attribute INIT of input_fetch_type_lut  : label is "0002";
attribute INIT of io_decode_lut         : label is "0010";
attribute INIT of write_active_lut      : label is "4000";
attribute INIT of read_active_lut       : label is "0100";
begin
  t_state_lut: LUT1
    generic map (INIT => "01")
  port map( I0 => t_state,
             O => not_t_state );
  toggle_flop: FDR
  port map ( D => not_t_state,
             Q => t_state,
             R => internal_reset,
             C => clk);
  reset_flop1: FDS
  port map ( D => '0',
             Q => reset_delay,
             S => reset,
             C => clk);
  reset_flop2: FDS
  port map ( D => reset_delay,
             Q => internal_reset,
             S => reset,
             C => clk);
  int_capture_flop: FDR
  port map ( D => interrupt,
             Q => clean_int,
             R => internal_reset,
             C => clk);
  int_pulse_lut: LUT4
    generic map (INIT => X"0080")
  port map( I0 => t_state,
            I1 => clean_int,
            I2 => int_enable,
            I3 => active_interrupt,
             O => int_pulse );
  int_flop: FDR
  port map ( D => int_pulse,
             Q => active_interrupt,
             R => internal_reset,
             C => clk);
  ack_flop: FD
  port map ( D => active_interrupt,
             Q => interrupt_ack_internal,
             C => clk);
  interrupt_ack <= interrupt_ack_internal;
  shadow_carry_flop: FDE
  port map ( D => carry_flag,
             Q => shadow_carry,
            CE => active_interrupt,
             C => clk);
  shadow_zero_flop: FDE
  port map ( D => zero_flag,
             Q => shadow_zero,
            CE => active_interrupt,
             C => clk);
  int_update_lut: LUT4
    generic map (INIT => X"EAAA")
  port map( I0 => active_interrupt,
            I1 => instruction(15),
            I2 => instruction(16),
            I3 => instruction(17),
             O => int_update_enable );
  int_value_lut: LUT3
    generic map (INIT => X"04")
  port map( I0 => active_interrupt,
            I1 => instruction(0),
            I2 => interrupt_ack_internal,
             O => int_enable_value );
  int_enable_flop: FDRE
  port map ( D => int_enable_value,
             Q => int_enable,
            CE => int_update_enable,
             R => internal_reset,
             C => clk);
  move_group_lut: LUT4
    generic map (INIT => X"7400")
  port map( I0 => instruction(14),
            I1 => instruction(15),
            I2 => instruction(16),
            I3 => instruction(17),
             O => move_group );
  condition_met_lut: LUT4
    generic map (INIT => X"5A3C")
  port map( I0 => carry_flag,
            I1 => zero_flag,
            I2 => instruction(10),
            I3 => instruction(11),
             O => condition_met );
  normal_count_lut: LUT3
    generic map (INIT => X"2F")
  port map( I0 => instruction(12),
            I1 => condition_met,
            I2 => move_group,
             O => normal_count );
  call_type_lut: LUT4
    generic map (INIT => X"1000")
  port map( I0 => instruction(14),
            I1 => instruction(15),
            I2 => instruction(16),
            I3 => instruction(17),
             O => call_type );
  push_pop_lut: LUT4
    generic map (INIT => X"5400")
  port map( I0 => instruction(14),
            I1 => instruction(15),
            I2 => instruction(16),
            I3 => instruction(17),
             O => push_or_pop_type );
  valid_move_lut: LUT2
    generic map (INIT => X"D")
  port map( I0 => instruction(12),
            I1 => condition_met,
             O => valid_to_move );
  flag_type_lut: LUT4
    generic map (INIT => X"41FC")
  port map( I0 => instruction(14),
            I1 => instruction(15),
            I2 => instruction(16),
            I3 => instruction(17),
             O => flag_type );
  flag_write_flop: FD
  port map ( D => flag_type,
             Q => flag_write,
             C => clk);
  flag_enable_lut: LUT2
    generic map (INIT => X"8")
  port map( I0 => t_state,
            I1 => flag_write,
             O => flag_enable );
  low_zero_lut: LUT4
    generic map (INIT => X"0001")
  port map( I0 => alu_result(0),
            I1 => alu_result(1),
            I2 => alu_result(2),
            I3 => alu_result(3),
             O => low_zero );
  high_zero_lut: LUT4
    generic map (INIT => X"0001")
  port map( I0 => alu_result(4),
            I1 => alu_result(5),
            I2 => alu_result(6),
            I3 => alu_result(7),
             O => high_zero );
  low_zero_muxcy: MUXCY
  port map( DI => '0',
            CI => '1',
             S => low_zero,
             O => low_zero_carry );
  high_zero_cymux: MUXCY
  port map( DI => '0',
            CI => low_zero_carry,
             S => high_zero,
             O => high_zero_carry );
  sel_shadow_zero_lut: LUT3
    generic map (INIT => X"3F")
  port map( I0 => shadow_zero,
            I1 => instruction(16),
            I2 => instruction(17),
             O => sel_shadow_zero );
  zero_cymux: MUXCY
  port map( DI => shadow_zero,
            CI => high_zero_carry,
             S => sel_shadow_zero,
             O => zero_carry );
  zero_xor: XORCY
  port map( LI => '0',
            CI => zero_carry,
             O => zero_fast_route);
  zero_flag_flop: FDRE
  port map ( D => zero_fast_route,
             Q => zero_flag,
            CE => flag_enable,
             R => internal_reset,
             C => clk);
  low_parity_lut: LUT4
    generic map (INIT => X"6996")
  port map( I0 => logical_result(0),
            I1 => logical_result(1),
            I2 => logical_result(2),
            I3 => logical_result(3),
             O => low_parity );
  high_parity_lut: LUT4
    generic map (INIT => X"6996")
  port map( I0 => logical_result(4),
            I1 => logical_result(5),
            I2 => logical_result(6),
            I3 => logical_result(7),
             O => high_parity );
  parity_muxcy: MUXCY
  port map( DI => '0',
            CI => '1',
             S => low_parity,
             O => parity_carry );
  parity_xor: XORCY
  port map( LI => high_parity,
            CI => parity_carry,
             O => parity);
  sel_parity_lut: LUT4
    generic map (INIT => X"F3FF")
  port map( I0 => parity,
            I1 => instruction(13),
            I2 => instruction(15),
            I3 => instruction(16),
             O => sel_parity );
  sel_arith_carry_lut: LUT3
    generic map (INIT => X"F3")
  port map( I0 => arith_carry,
            I1 => instruction(16),
            I2 => instruction(17),
             O => sel_arith_carry );
  sel_shift_carry_lut: LUT2
    generic map (INIT => X"C")
  port map( I0 => shift_carry,
            I1 => instruction(15),
             O => sel_shift_carry );
  sel_shadow_carry_lut: LUT2
    generic map (INIT => X"3")
  port map( I0 => shadow_carry,
            I1 => instruction(17),
             O => sel_shadow_carry );
  sel_shadow_muxcy: MUXCY
  port map( DI => shadow_carry,
            CI => '0',
             S => sel_shadow_carry,
             O => sel_carry(0) );
  sel_shift_muxcy: MUXCY
  port map( DI => shift_carry,
            CI => sel_carry(0),
             S => sel_shift_carry,
             O => sel_carry(1) );
  sel_arith_muxcy: MUXCY
  port map( DI => arith_carry,
            CI => sel_carry(1),
             S => sel_arith_carry,
             O => sel_carry(2) );
  sel_parity_muxcy: MUXCY
  port map( DI => parity,
            CI => sel_carry(2),
             S => sel_parity,
             O => sel_carry(3) );
  carry_xor: XORCY
  port map( LI => '0',
            CI => sel_carry(3),
             O => carry_fast_route);
  carry_flag_flop: FDRE
  port map ( D => carry_fast_route,
             Q => carry_flag,
            CE => flag_enable,
             R => internal_reset,
             C => clk);
  invert_enable: INV
  port map(  I => t_state,
             O => pc_enable);
  pc_loop: for i in 0 to 9 generate
  attribute INIT : string;
  attribute INIT of vector_select_mux : label is "E4";
  attribute INIT of value_select_mux  : label is "E4";
  begin
    vector_select_mux: LUT3
      generic map (INIT => X"E4")
    port map( I0 => instruction(15),
              I1 => instruction(i),
              I2 => stack_pop_data(i),
               O => pc_vector(i) );
    value_select_mux: LUT3
      generic map (INIT => X"E4")
    port map( I0 => normal_count,
              I1 => inc_pc_vector(i),
              I2 => pc(i),
               O => pc_value(i) );
     register_bit: FDRSE
     port map ( D => inc_pc_value(i),
                Q => pc(i),
                R => internal_reset,
                S => active_interrupt,
               CE => pc_enable,
                C => clk);
     pc_lsb_carry: if i=0 generate
       begin
         pc_vector_muxcy: MUXCY
         port map( DI => '0',
                   CI => instruction(13),
                    S => pc_vector(i),
                    O => pc_vector_carry(i));
         pc_vector_xor: XORCY
         port map( LI => pc_vector(i),
                   CI => instruction(13),
                    O => inc_pc_vector(i));
         pc_value_muxcy: MUXCY
         port map( DI => '0',
                   CI => normal_count,
                    S => pc_value(i),
                    O => pc_value_carry(i));
         pc_value_xor: XORCY
         port map( LI => pc_value(i),
                   CI => normal_count,
                    O => inc_pc_value(i));
       end generate pc_lsb_carry;
     pc_mid_carry: if i>0 and i<9 generate
         begin
         pc_vector_muxcy: MUXCY
         port map( DI => '0',
                   CI => pc_vector_carry(i-1),
                    S => pc_vector(i),
                    O => pc_vector_carry(i));
         pc_vector_xor: XORCY
         port map( LI => pc_vector(i),
                   CI => pc_vector_carry(i-1),
                    O => inc_pc_vector(i));
         pc_value_muxcy: MUXCY
         port map( DI => '0',
                   CI => pc_value_carry(i-1),
                    S => pc_value(i),
                    O => pc_value_carry(i));
         pc_value_xor: XORCY
         port map( LI => pc_value(i),
                   CI => pc_value_carry(i-1),
                    O => inc_pc_value(i));
       end generate pc_mid_carry;
     pc_msb_carry: if i=9 generate
       begin
         pc_vector_xor: XORCY
         port map( LI => pc_vector(i),
                   CI => pc_vector_carry(i-1),
                    O => inc_pc_vector(i));
          pc_value_xor: XORCY
         port map( LI => pc_value(i),
                   CI => pc_value_carry(i-1),
                    O => inc_pc_value(i));
       end generate pc_msb_carry;
  end generate pc_loop;
  address <= pc;
  register_type_lut: LUT4
    generic map (INIT => X"0145")
  port map( I0 => active_interrupt,
            I1 => instruction(15),
            I2 => instruction(16),
            I3 => instruction(17),
             O => register_type );
  register_write_flop: FD
  port map ( D => register_type,
             Q => register_write,
             C => clk);
  register_enable_lut: LUT2
    generic map (INIT => X"8")
  port map( I0 => t_state,
            I1 => register_write,
             O => register_enable );
  reg_loop: for i in 0 to 7 generate
  attribute INIT : string;
  attribute INIT of register_bit       : label is "0000";
  attribute INIT of operand_select_mux : label is "E4";
  begin
    register_bit: RAM16X1D
    generic map(INIT => X"0000")
    port map (       D => alu_result(i),
                    WE => register_enable,
                  WCLK => clk,
                    A0 => instruction(8),
                    A1 => instruction(9),
                    A2 => instruction(10),
                    A3 => instruction(11),
                 DPRA0 => instruction(4),
                 DPRA1 => instruction(5),
                 DPRA2 => instruction(6),
                 DPRA3 => instruction(7),
                   SPO => sx(i),
                   DPO => sy(i));
    operand_select_mux: LUT3
      generic map (INIT => X"E4")
    port map( I0 => instruction(12),
              I1 => instruction(i),
              I2 => sy(i),
               O => second_operand(i) );
  end generate reg_loop;
  out_port <= sx;
  port_id <= second_operand;
  memory_type_lut: LUT4
    generic map (INIT => X"0400")
  port map( I0 => active_interrupt,
            I1 => instruction(15),
            I2 => instruction(16),
            I3 => instruction(17),
             O => memory_type );
  memory_write_flop: FD
  port map ( D => memory_type,
             Q => memory_write,
             C => clk);
  memory_enable_lut: LUT4
    generic map (INIT => X"8000")
  port map( I0 => t_state,
            I1 => instruction(13),
            I2 => instruction(14),
            I3 => memory_write,
             O => memory_enable );
  store_loop: for i in 0 to 7 generate
  attribute INIT : string;
  attribute INIT of memory_bit : label is "0000000000000000";
  begin
    memory_bit: RAM64X1S
    generic map(INIT => X"0000000000000000")
    port map (       D => sx(i),
                    WE => memory_enable,
                  WCLK => clk,
                    A0 => second_operand(0),
                    A1 => second_operand(1),
                    A2 => second_operand(2),
                    A3 => second_operand(3),
                    A4 => second_operand(4),
                    A5 => second_operand(5),
                     O => memory_data(i));
    store_flop: FD
    port map ( D => memory_data(i),
               Q => store_data(i),
               C => clk);
  end generate store_loop;
  sel_logical_lut: LUT4
    generic map (INIT => X"FFE2")
  port map( I0 => instruction(14),
            I1 => instruction(15),
            I2 => instruction(16),
            I3 => instruction(17),
             O => sel_logical );
  logical_loop: for i in 0 to 7 generate
  attribute INIT : string;
  attribute INIT of logical_lut : label is "6E8A";
  begin
    logical_lut: LUT4
    generic map (INIT => X"6E8A")
    port map( I0 => second_operand(i),
              I1 => sx(i),
              I2 => instruction(13),
              I3 => instruction(14),
               O => logical_value(i));
    logical_flop: FDR
    port map ( D => logical_value(i),
               Q => logical_result(i),
               R => sel_logical,
               C => clk);
  end generate logical_loop;
  sel_shift_inv: INV
  port map(  I => instruction(17),
             O => sel_shift);
  high_shift_in_lut: LUT3
    generic map (INIT => X"E4")
  port map( I0 => instruction(1),
            I1 => sx(0),
            I2 => instruction(0),
             O => high_shift_in );
  low_shift_in_lut: LUT3
    generic map (INIT => X"E4")
  port map( I0 => instruction(1),
            I1 => carry_flag,
            I2 => sx(7),
             O => low_shift_in );
  shift_in_muxf5: MUXF5
  port map(  I1 => high_shift_in,
             I0 => low_shift_in,
              S => instruction(2),
              O => shift_in );
  shift_carry_lut: LUT3
    generic map (INIT => X"E4")
  port map( I0 => instruction(3),
            I1 => sx(7),
            I2 => sx(0),
             O => shift_carry_value );
  pipeline_bit: FD
  port map ( D => shift_carry_value,
             Q => shift_carry,
             C => clk);
  shift_loop: for i in 0 to 7 generate
  begin
    lsb_shift: if i=0 generate
    attribute INIT : string;
    attribute INIT of shift_mux_lut : label is "E4";
    begin
      shift_mux_lut: LUT3
        generic map (INIT => X"E4")
      port map( I0 => instruction(3),
                I1 => shift_in,
                I2 => sx(i+1),
                 O => shift_value(i) );
    end generate lsb_shift;
    mid_shift: if i>0 and i<7 generate
    attribute INIT : string;
    attribute INIT of shift_mux_lut : label is "E4";
    begin
      shift_mux_lut: LUT3
        generic map (INIT => X"E4")
      port map( I0 => instruction(3),
                I1 => sx(i-1),
                I2 => sx(i+1),
                 O => shift_value(i) );
    end generate mid_shift;
    msb_shift: if i=7 generate
    attribute INIT : string;
    attribute INIT of shift_mux_lut : label is "E4";
    begin
      shift_mux_lut: LUT3
        generic map (INIT => X"E4")
      port map( I0 => instruction(3),
                I1 => sx(i-1),
                I2 => shift_in,
                 O => shift_value(i) );
    end generate msb_shift;
    shift_flop: FDR
    port map ( D => shift_value(i),
               Q => shift_result(i),
               R => sel_shift,
               C => clk);
  end generate shift_loop;
  sel_arith_lut: LUT3
    generic map (INIT => X"1F")
  port map( I0 => instruction(14),
            I1 => instruction(15),
            I2 => instruction(16),
             O => sel_arith );
  arith_loop: for i in 0 to 7 generate
  attribute INIT : string;
  attribute INIT of arith_lut : label is "96";
  begin
    lsb_arith: if i=0 generate
    attribute INIT : string;
    attribute INIT of arith_carry_in_lut : label is "6C";
    begin
      arith_carry_in_lut: LUT3
        generic map (INIT => X"6C")
      port map( I0 => instruction(13),
                I1 => instruction(14),
                I2 => carry_flag,
                 O => sel_arith_carry_in );
      arith_carry_in_muxcy: MUXCY
      port map( DI => '0',
                CI => '1',
                 S => sel_arith_carry_in,
                 O => arith_carry_in);
      arith_muxcy: MUXCY
      port map( DI => sx(i),
                CI => arith_carry_in,
                 S => half_arith(i),
                 O => arith_internal_carry(i));
      arith_xor: XORCY
      port map( LI => half_arith(i),
                CI => arith_carry_in,
                 O => arith_value(i));
    end generate lsb_arith;
    mid_arith: if i>0 and i<7 generate
    begin
      arith_muxcy: MUXCY
      port map( DI => sx(i),
                CI => arith_internal_carry(i-1),
                 S => half_arith(i),
                 O => arith_internal_carry(i));
      arith_xor: XORCY
      port map( LI => half_arith(i),
                CI => arith_internal_carry(i-1),
                 O => arith_value(i));
    end generate mid_arith;
    msb_arith: if i=7 generate
    attribute INIT : string;
    attribute INIT of arith_carry_out_lut : label is "2";
    begin
      arith_muxcy: MUXCY
      port map( DI => sx(i),
                CI => arith_internal_carry(i-1),
                 S => half_arith(i),
                 O => arith_internal_carry(i));
      arith_xor: XORCY
      port map( LI => half_arith(i),
                CI => arith_internal_carry(i-1),
                 O => arith_value(i));
      arith_carry_out_lut: LUT1
        generic map (INIT => "10")
      port map( I0 => instruction(14),
                 O => invert_arith_carry );
      arith_carry_out_xor: XORCY
      port map( LI => invert_arith_carry,
                CI => arith_internal_carry(i),
                 O => arith_carry_out);
      arith_carry_flop: FDR
      port map ( D => arith_carry_out,
                 Q => arith_carry,
                 R => sel_arith,
                 C => clk);
    end generate msb_arith;
    arith_lut: LUT3
    generic map (INIT => X"96")
    port map( I0 => sx(i),
              I1 => second_operand(i),
              I2 => instruction(14),
               O => half_arith(i));
    arith_flop: FDR
    port map ( D => arith_value(i),
               Q => arith_result(i),
               R => sel_arith,
               C => clk);
  end generate arith_loop;
  input_fetch_type_lut: LUT4
    generic map (INIT => X"0002")
  port map( I0 => instruction(14),
            I1 => instruction(15),
            I2 => instruction(16),
            I3 => instruction(17),
             O => input_fetch_type );
  sel_group_flop: FD
  port map ( D => input_fetch_type,
             Q => sel_group,
             C => clk);
  alu_mux_loop: for i in 0 to 7 generate
  attribute INIT : string;
  attribute INIT of or_lut  : label is "FE";
  attribute INIT of mux_lut : label is "E4";
  begin
    or_lut: LUT3
    generic map (INIT => X"FE")
    port map( I0 => logical_result(i),
              I1 => arith_result(i),
              I2 => shift_result(i),
               O => alu_group(i));
    mux_lut: LUT3
    generic map (INIT => X"E4")
    port map( I0 => instruction(13),
              I1 => in_port(i),
              I2 => store_data(i),
               O => input_group(i));
    shift_in_muxf5: MUXF5
    port map(  I1 => input_group(i),
               I0 => alu_group(i),
                S => sel_group,
                O => alu_result(i) );
  end generate alu_mux_loop;
  io_decode_lut: LUT4
    generic map (INIT => X"0010")
  port map( I0 => active_interrupt,
            I1 => instruction(13),
            I2 => instruction(14),
            I3 => instruction(16),
             O => io_initial_decode );
  write_active_lut: LUT4
    generic map (INIT => X"4000")
  port map( I0 => t_state,
            I1 => instruction(15),
            I2 => instruction(17),
            I3 => io_initial_decode,
             O => write_active );
  write_strobe_flop: FDR
  port map ( D => write_active,
             Q => write_strobe,
             R => internal_reset,
             C => clk);
  read_active_lut: LUT4
    generic map (INIT => X"0100")
  port map( I0 => t_state,
            I1 => instruction(15),
            I2 => instruction(17),
            I3 => io_initial_decode,
             O => read_active );
  read_strobe_flop: FDR
  port map ( D => read_active,
             Q => read_strobe,
             R => internal_reset,
             C => clk);
  stack_ram_inv: INV
  port map(  I => t_state,
             O => stack_write_enable);
  stack_ram_loop: for i in 0 to 9 generate
  attribute INIT : string;
  attribute INIT of stack_bit : label is "00000000";
  begin
    stack_bit: RAM32X1S
    generic map(INIT => X"00000000")
    port map (       D => pc(i),
                    WE => stack_write_enable,
                  WCLK => clk,
                    A0 => stack_address(0),
                    A1 => stack_address(1),
                    A2 => stack_address(2),
                    A3 => stack_address(3),
                    A4 => stack_address(4),
                     O => stack_ram_data(i));
    stack_flop: FD
    port map ( D => stack_ram_data(i),
               Q => stack_pop_data(i),
               C => clk);
  end generate stack_ram_loop;
  stack_count_inv: INV
  port map(  I => active_interrupt,
             O => not_active_interrupt);
  stack_count_loop: for i in 0 to 4 generate
  begin
    register_bit: FDRE
    port map ( D => next_stack_address(i),
               Q => stack_address(i),
               R => internal_reset,
              CE => not_active_interrupt,
               C => clk);
    lsb_stack_count: if i=0 generate
    attribute INIT : string;
    attribute INIT of count_lut : label is "6555";
    begin
      count_lut: LUT4
      generic map (INIT => X"6555")
      port map( I0 => stack_address(i),
                I1 => t_state,
                I2 => valid_to_move,
                I3 => push_or_pop_type,
                 O => half_stack_address(i) );
      count_muxcy: MUXCY
      port map( DI => stack_address(i),
                CI => '0',
                 S => half_stack_address(i),
                 O => stack_address_carry(i));
      count_xor: XORCY
      port map( LI => half_stack_address(i),
                CI => '0',
                 O => next_stack_address(i));
    end generate lsb_stack_count;
    mid_stack_count: if i>0 and i<4 generate
    attribute INIT : string;
    attribute INIT of count_lut : label is "A999";
    begin
      count_lut: LUT4
      generic map (INIT => X"A999")
      port map( I0 => stack_address(i),
                I1 => t_state,
                I2 => valid_to_move,
                I3 => call_type,
                 O => half_stack_address(i) );
      count_muxcy: MUXCY
      port map( DI => stack_address(i),
                CI => stack_address_carry(i-1),
                 S => half_stack_address(i),
                 O => stack_address_carry(i));
      count_xor: XORCY
      port map( LI => half_stack_address(i),
                CI => stack_address_carry(i-1),
                 O => next_stack_address(i));
    end generate mid_stack_count;
    msb_stack_count: if i=4 generate
    attribute INIT : string;
    attribute INIT of count_lut : label is "A999";
    begin
      count_lut: LUT4
      generic map (INIT => X"A999")
      port map( I0 => stack_address(i),
                I1 => t_state,
                I2 => valid_to_move,
                I3 => call_type,
                 O => half_stack_address(i) );
      count_xor: XORCY
      port map( LI => half_stack_address(i),
                CI => stack_address_carry(i-1),
                 O => next_stack_address(i));
    end generate msb_stack_count;
  end generate stack_count_loop;
  simulation: process (clk, instruction)
  variable kcpsm3_opcode : string(1 to 19);
  variable kcpsm3_status : string(1 to 13):= "NZ, NC, Reset";
  variable s0_contents : std_logic_vector(7 downto 0):=X"00";
  variable s1_contents : std_logic_vector(7 downto 0):=X"00";
  variable s2_contents : std_logic_vector(7 downto 0):=X"00";
  variable s3_contents : std_logic_vector(7 downto 0):=X"00";
  variable s4_contents : std_logic_vector(7 downto 0):=X"00";
  variable s5_contents : std_logic_vector(7 downto 0):=X"00";
  variable s6_contents : std_logic_vector(7 downto 0):=X"00";
  variable s7_contents : std_logic_vector(7 downto 0):=X"00";
  variable s8_contents : std_logic_vector(7 downto 0):=X"00";
  variable s9_contents : std_logic_vector(7 downto 0):=X"00";
  variable sa_contents : std_logic_vector(7 downto 0):=X"00";
  variable sb_contents : std_logic_vector(7 downto 0):=X"00";
  variable sc_contents : std_logic_vector(7 downto 0):=X"00";
  variable sd_contents : std_logic_vector(7 downto 0):=X"00";
  variable se_contents : std_logic_vector(7 downto 0):=X"00";
  variable sf_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm00_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm01_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm02_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm03_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm04_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm05_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm06_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm07_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm08_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm09_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm0a_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm0b_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm0c_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm0d_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm0e_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm0f_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm10_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm11_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm12_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm13_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm14_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm15_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm16_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm17_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm18_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm19_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm1a_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm1b_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm1c_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm1d_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm1e_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm1f_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm20_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm21_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm22_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm23_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm24_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm25_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm26_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm27_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm28_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm29_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm2a_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm2b_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm2c_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm2d_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm2e_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm2f_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm30_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm31_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm32_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm33_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm34_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm35_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm36_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm37_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm38_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm39_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm3a_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm3b_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm3c_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm3d_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm3e_contents : std_logic_vector(7 downto 0):=X"00";
  variable spm3f_contents : std_logic_vector(7 downto 0):=X"00";
  variable     sx_decode : string(1 to 2);
  variable     sy_decode : string(1 to 2);
  variable     kk_decode : string(1 to 2);
  variable    aaa_decode : string(1 to 3);
  function hexcharacter (nibble: std_logic_vector(3 downto 0))
  return character is
  variable hex: character;
  begin
    case nibble is
      when "0000" => hex := '0';
      when "0001" => hex := '1';
      when "0010" => hex := '2';
      when "0011" => hex := '3';
      when "0100" => hex := '4';
      when "0101" => hex := '5';
      when "0110" => hex := '6';
      when "0111" => hex := '7';
      when "1000" => hex := '8';
      when "1001" => hex := '9';
      when "1010" => hex := 'A';
      when "1011" => hex := 'B';
      when "1100" => hex := 'C';
      when "1101" => hex := 'D';
      when "1110" => hex := 'E';
      when "1111" => hex := 'F';
      when others => hex := 'x';
    end case;
    return hex;
  end hexcharacter;
  begin
    sx_decode(1) := 's';
    sx_decode(2) := hexcharacter(instruction(11 downto 8));
    sy_decode(1) := 's';
    sy_decode(2) := hexcharacter(instruction(7 downto 4));
    kk_decode(1) := hexcharacter(instruction(7 downto 4));
    kk_decode(2) := hexcharacter(instruction(3 downto 0));
    aaa_decode(1) := hexcharacter("00" & instruction(9 downto 8));
    aaa_decode(2) := hexcharacter(instruction(7 downto 4));
    aaa_decode(3) := hexcharacter(instruction(3 downto 0));
    case instruction(17 downto 12) is
      when "000000" => kcpsm3_opcode := "LOAD " & sx_decode & ',' & kk_decode & "         ";
      when "000001" => kcpsm3_opcode := "LOAD " & sx_decode & ',' & sy_decode & "         ";
      when "001010" => kcpsm3_opcode := "AND " & sx_decode & ',' & kk_decode & "          ";
      when "001011" => kcpsm3_opcode := "AND " & sx_decode & ',' & sy_decode & "          ";
      when "001100" => kcpsm3_opcode := "OR " & sx_decode & ',' & kk_decode & "           ";
      when "001101" => kcpsm3_opcode := "OR " & sx_decode & ',' & sy_decode & "           ";
      when "001110" => kcpsm3_opcode := "XOR " & sx_decode & ',' & kk_decode & "          ";
      when "001111" => kcpsm3_opcode := "XOR " & sx_decode & ',' & sy_decode & "          ";
      when "010010" => kcpsm3_opcode := "TEST " & sx_decode & ',' & kk_decode & "         ";
      when "010011" => kcpsm3_opcode := "TEST " & sx_decode & ',' & sy_decode & "         ";
      when "011000" => kcpsm3_opcode := "ADD " & sx_decode & ',' & kk_decode & "          ";
      when "011001" => kcpsm3_opcode := "ADD " & sx_decode & ',' & sy_decode & "          ";
      when "011010" => kcpsm3_opcode := "ADDCY " & sx_decode & ',' & kk_decode & "        ";
      when "011011" => kcpsm3_opcode := "ADDCY " & sx_decode & ',' & sy_decode & "        ";
      when "011100" => kcpsm3_opcode := "SUB " & sx_decode & ',' & kk_decode & "          ";
      when "011101" => kcpsm3_opcode := "SUB " & sx_decode & ',' & sy_decode & "          ";
      when "011110" => kcpsm3_opcode := "SUBCY " & sx_decode & ',' & kk_decode & "        ";
      when "011111" => kcpsm3_opcode := "SUBCY " & sx_decode & ',' & sy_decode & "        ";
      when "010100" => kcpsm3_opcode := "COMPARE " & sx_decode & ',' & kk_decode & "      ";
      when "010101" => kcpsm3_opcode := "COMPARE " & sx_decode & ',' & sy_decode & "      ";
      when "100000" =>
        case instruction(3 downto 0) is
          when "0110" => kcpsm3_opcode := "SL0 " & sx_decode & "             ";
          when "0111" => kcpsm3_opcode := "SL1 " & sx_decode & "             ";
          when "0100" => kcpsm3_opcode := "SLX " & sx_decode & "             ";
          when "0000" => kcpsm3_opcode := "SLA " & sx_decode & "             ";
          when "0010" => kcpsm3_opcode := "RL " & sx_decode & "              ";
          when "1110" => kcpsm3_opcode := "SR0 " & sx_decode & "             ";
          when "1111" => kcpsm3_opcode := "SR1 " & sx_decode & "             ";
          when "1010" => kcpsm3_opcode := "SRX " & sx_decode & "             ";
          when "1000" => kcpsm3_opcode := "SRA " & sx_decode & "             ";
          when "1100" => kcpsm3_opcode := "RR " & sx_decode & "              ";
          when others => kcpsm3_opcode := "Invalid Instruction";
        end case;
      when "101100" => kcpsm3_opcode := "OUTPUT " & sx_decode & ',' & kk_decode & "       ";
      when "101101" => kcpsm3_opcode := "OUTPUT " & sx_decode & ",(" & sy_decode & ")     ";
      when "000100" => kcpsm3_opcode := "INPUT " & sx_decode & ',' & kk_decode & "        ";
      when "000101" => kcpsm3_opcode := "INPUT " & sx_decode & ",(" & sy_decode & ")      ";
      when "101110" => kcpsm3_opcode := "STORE " & sx_decode & ',' & kk_decode & "        ";
      when "101111" => kcpsm3_opcode := "STORE " & sx_decode & ",(" & sy_decode & ")      ";
      when "000110" => kcpsm3_opcode := "FETCH " & sx_decode & ',' & kk_decode & "        ";
      when "000111" => kcpsm3_opcode := "FETCH " & sx_decode & ",(" & sy_decode & ")      ";
      when "110100" => kcpsm3_opcode := "JUMP " & aaa_decode & "           ";
      when "110101" =>
        case instruction(11 downto 10) is
          when "00" => kcpsm3_opcode := "JUMP Z," & aaa_decode & "         ";
          when "01" => kcpsm3_opcode := "JUMP NZ," & aaa_decode & "        ";
          when "10" => kcpsm3_opcode := "JUMP C," & aaa_decode & "         ";
          when "11" => kcpsm3_opcode := "JUMP NC," & aaa_decode & "        ";
          when others => kcpsm3_opcode := "Invalid Instruction";
        end case;
      when "110000" => kcpsm3_opcode := "CALL " & aaa_decode & "           ";
      when "110001" =>
        case instruction(11 downto 10) is
          when "00" => kcpsm3_opcode := "CALL Z," & aaa_decode & "         ";
          when "01" => kcpsm3_opcode := "CALL NZ," & aaa_decode & "        ";
          when "10" => kcpsm3_opcode := "CALL C," & aaa_decode & "         ";
          when "11" => kcpsm3_opcode := "CALL NC," & aaa_decode & "        ";
          when others => kcpsm3_opcode := "Invalid Instruction";
        end case;
      when "101010" => kcpsm3_opcode := "RETURN             ";
      when "101011" =>
        case instruction(11 downto 10) is
          when "00" => kcpsm3_opcode := "RETURN Z           ";
          when "01" => kcpsm3_opcode := "RETURN NZ          ";
          when "10" => kcpsm3_opcode := "RETURN C           ";
          when "11" => kcpsm3_opcode := "RETURN NC          ";
          when others => kcpsm3_opcode := "Invalid Instruction";
        end case;
      when "111000" =>
        case instruction(0) is
          when '0' => kcpsm3_opcode := "RETURNI DISABLE    ";
          when '1' => kcpsm3_opcode := "RETURNI ENABLE     ";
          when others => kcpsm3_opcode := "Invalid Instruction";
        end case;
      when "111100" =>
        case instruction(0) is
          when '0' => kcpsm3_opcode := "DISABLE INTERRUPT  ";
          when '1' => kcpsm3_opcode := "ENABLE INTERRUPT   ";
          when others => kcpsm3_opcode := "Invalid Instruction";
        end case;
      when others => kcpsm3_opcode := "Invalid Instruction";
    end case;
    if clk'event and clk='1' then
      if reset='1' or reset_delay='1' then
        kcpsm3_status := "NZ, NC, Reset";
       else
        kcpsm3_status(7 to 13) := "       ";
        if flag_enable='1' then
          if zero_carry='1' then
            kcpsm3_status(1 to 4) := " Z, ";
           else
            kcpsm3_status(1 to 4) := "NZ, ";
          end if;
          if sel_carry(3)='1' then
            kcpsm3_status(5 to 6) := " C";
           else
            kcpsm3_status(5 to 6) := "NC";
          end if;
        end if;
      end if;
      if register_enable='1' then
        case instruction(11 downto 8) is
          when "0000" => s0_contents := alu_result;
          when "0001" => s1_contents := alu_result;
          when "0010" => s2_contents := alu_result;
          when "0011" => s3_contents := alu_result;
          when "0100" => s4_contents := alu_result;
          when "0101" => s5_contents := alu_result;
          when "0110" => s6_contents := alu_result;
          when "0111" => s7_contents := alu_result;
          when "1000" => s8_contents := alu_result;
          when "1001" => s9_contents := alu_result;
          when "1010" => sa_contents := alu_result;
          when "1011" => sb_contents := alu_result;
          when "1100" => sc_contents := alu_result;
          when "1101" => sd_contents := alu_result;
          when "1110" => se_contents := alu_result;
          when "1111" => sf_contents := alu_result;
          when others => null;
        end case;
      end if;
      if memory_enable='1' then
        case second_operand(5 downto 0) is
          when "000000" => spm00_contents := sx;
          when "000001" => spm01_contents := sx;
          when "000010" => spm02_contents := sx;
          when "000011" => spm03_contents := sx;
          when "000100" => spm04_contents := sx;
          when "000101" => spm05_contents := sx;
          when "000110" => spm06_contents := sx;
          when "000111" => spm07_contents := sx;
          when "001000" => spm08_contents := sx;
          when "001001" => spm09_contents := sx;
          when "001010" => spm0a_contents := sx;
          when "001011" => spm0b_contents := sx;
          when "001100" => spm0c_contents := sx;
          when "001101" => spm0d_contents := sx;
          when "001110" => spm0e_contents := sx;
          when "001111" => spm0f_contents := sx;
          when "010000" => spm10_contents := sx;
          when "010001" => spm11_contents := sx;
          when "010010" => spm12_contents := sx;
          when "010011" => spm13_contents := sx;
          when "010100" => spm14_contents := sx;
          when "010101" => spm15_contents := sx;
          when "010110" => spm16_contents := sx;
          when "010111" => spm17_contents := sx;
          when "011000" => spm18_contents := sx;
          when "011001" => spm19_contents := sx;
          when "011010" => spm1a_contents := sx;
          when "011011" => spm1b_contents := sx;
          when "011100" => spm1c_contents := sx;
          when "011101" => spm1d_contents := sx;
          when "011110" => spm1e_contents := sx;
          when "011111" => spm1f_contents := sx;
          when "100000" => spm20_contents := sx;
          when "100001" => spm21_contents := sx;
          when "100010" => spm22_contents := sx;
          when "100011" => spm23_contents := sx;
          when "100100" => spm24_contents := sx;
          when "100101" => spm25_contents := sx;
          when "100110" => spm26_contents := sx;
          when "100111" => spm27_contents := sx;
          when "101000" => spm28_contents := sx;
          when "101001" => spm29_contents := sx;
          when "101010" => spm2a_contents := sx;
          when "101011" => spm2b_contents := sx;
          when "101100" => spm2c_contents := sx;
          when "101101" => spm2d_contents := sx;
          when "101110" => spm2e_contents := sx;
          when "101111" => spm2f_contents := sx;
          when "110000" => spm30_contents := sx;
          when "110001" => spm31_contents := sx;
          when "110010" => spm32_contents := sx;
          when "110011" => spm33_contents := sx;
          when "110100" => spm34_contents := sx;
          when "110101" => spm35_contents := sx;
          when "110110" => spm36_contents := sx;
          when "110111" => spm37_contents := sx;
          when "111000" => spm38_contents := sx;
          when "111001" => spm39_contents := sx;
          when "111010" => spm3a_contents := sx;
          when "111011" => spm3b_contents := sx;
          when "111100" => spm3c_contents := sx;
          when "111101" => spm3d_contents := sx;
          when "111110" => spm3e_contents := sx;
          when "111111" => spm3f_contents := sx;
          when others => null;
        end case;
      end if;
    end if;
  end process simulation;
end low_level_definition;

-------------------------------------------------------------------
-- System Generator version 12.1 VHDL source file.
--
-- Copyright(C) 2010 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2010 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
entity xlpb3 is
  port (
     in_port:            in  std_logic_vector(7 downto 0);
     interrupt:          in  std_logic_vector(0 downto 0);
     reset:              in  std_logic_vector(0 downto 0);
     instruction:        in  std_logic_vector(17 downto 0);
     clk:                in  std_logic;
     ce:                 in  std_logic;
     out_port:           out std_logic_vector(7 downto 0);
     port_id:            out std_logic_vector(7 downto 0);
     read_strobe:        out std_logic_vector(0 downto 0);
     write_strobe:       out std_logic_vector(0 downto 0);
     interrupt_ack:      out std_logic_vector(0 downto 0);
     address:            out std_logic_vector(9 downto 0)
  );
end xlpb3;
architecture behavior of xlpb3 is
 component kcpsm3
    Port (
      address       : out std_logic_vector(9 downto 0);
      instruction   : in std_logic_vector(17 downto 0);
      port_id       : out std_logic_vector(7 downto 0);
      write_strobe  : out std_logic;
      out_port      : out std_logic_vector(7 downto 0);
      read_strobe   : out std_logic;
      in_port       : in std_logic_vector(7 downto 0);
      interrupt     : in std_logic;
      interrupt_ack : out std_logic;
      reset         : in std_logic;
      clk           : in std_logic);
 end component;
begin
    proc_inst: kcpsm3
      port map (
        address => address,
        clk => clk,
        in_port => in_port,
        instruction => instruction,
        interrupt => interrupt(0),
        out_port => out_port,
        port_id => port_id,
        read_strobe => read_strobe(0),
        reset => reset(0),
        interrupt_ack => interrupt_ack(0),
        write_strobe => write_strobe(0)
      );
end architecture behavior;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "sg_i2c_controller_s6/EDK Processor"

entity edk_processor_entity_f7392c68af is
  port (
    from_fifo: in std_logic_vector(31 downto 0); 
    from_fifo_x0: in std_logic; 
    from_fifo_x1: in std_logic; 
    plb_abus: in std_logic_vector(31 downto 0); 
    plb_ce_1: in std_logic; 
    plb_clk_1: in std_logic; 
    plb_pavalid: in std_logic; 
    plb_rnw: in std_logic; 
    plb_wrdbus: in std_logic_vector(31 downto 0); 
    sg_plb_addrpref: in std_logic_vector(19 downto 0); 
    splb_rst: in std_logic; 
    to_fifo: in std_logic; 
    to_fifo_x0: in std_logic; 
    to_register: in std_logic_vector(7 downto 0); 
    constant5_x0: out std_logic; 
    plb_decode_x0: out std_logic; 
    plb_decode_x1: out std_logic; 
    plb_decode_x2: out std_logic; 
    plb_decode_x3: out std_logic; 
    plb_decode_x4: out std_logic_vector(31 downto 0); 
    plb_memmap_x0: out std_logic_vector(7 downto 0); 
    plb_memmap_x1: out std_logic; 
    plb_memmap_x2: out std_logic; 
    plb_memmap_x3: out std_logic_vector(31 downto 0); 
    plb_memmap_x4: out std_logic
  );
end edk_processor_entity_f7392c68af;

architecture structural of edk_processor_entity_f7392c68af is
  signal bankaddr: std_logic_vector(1 downto 0);
  signal cmd_request_din_x0: std_logic_vector(31 downto 0);
  signal cmd_request_full_x0: std_logic;
  signal cmd_request_pfull_x0: std_logic;
  signal cmd_request_we_x0: std_logic;
  signal cmd_response_dout_x0: std_logic_vector(31 downto 0);
  signal cmd_response_empty_x0: std_logic;
  signal cmd_response_pfull_x0: std_logic;
  signal cmd_response_re_x0: std_logic;
  signal gpio_out8_din_x0: std_logic_vector(7 downto 0);
  signal gpio_out8_dout_x0: std_logic_vector(7 downto 0);
  signal gpio_out8_en_x0: std_logic;
  signal linearaddr: std_logic_vector(7 downto 0);
  signal plb_abus_net_x0: std_logic_vector(31 downto 0);
  signal plb_ce_1_sg_x0: std_logic;
  signal plb_clk_1_sg_x0: std_logic;
  signal plb_pavalid_net_x0: std_logic;
  signal plb_rnw_net_x0: std_logic;
  signal plb_wrdbus_net_x0: std_logic_vector(31 downto 0);
  signal rddata: std_logic_vector(31 downto 0);
  signal rnwreg: std_logic;
  signal sg_plb_addrpref_net_x0: std_logic_vector(19 downto 0);
  signal sl_addrack_x0: std_logic;
  signal sl_rdcomp_x0: std_logic;
  signal sl_rddack_x0: std_logic;
  signal sl_rddbus_x0: std_logic_vector(31 downto 0);
  signal sl_wait_x0: std_logic;
  signal sl_wrdack_x0: std_logic;
  signal splb_rst_net_x0: std_logic;
  signal wrdbusreg: std_logic_vector(31 downto 0);

begin
  cmd_response_dout_x0 <= from_fifo;
  cmd_response_pfull_x0 <= from_fifo_x0;
  cmd_response_empty_x0 <= from_fifo_x1;
  plb_abus_net_x0 <= plb_abus;
  plb_ce_1_sg_x0 <= plb_ce_1;
  plb_clk_1_sg_x0 <= plb_clk_1;
  plb_pavalid_net_x0 <= plb_pavalid;
  plb_rnw_net_x0 <= plb_rnw;
  plb_wrdbus_net_x0 <= plb_wrdbus;
  sg_plb_addrpref_net_x0 <= sg_plb_addrpref;
  splb_rst_net_x0 <= splb_rst;
  cmd_request_pfull_x0 <= to_fifo;
  cmd_request_full_x0 <= to_fifo_x0;
  gpio_out8_dout_x0 <= to_register;
  constant5_x0 <= sl_wait_x0;
  plb_decode_x0 <= sl_addrack_x0;
  plb_decode_x1 <= sl_rdcomp_x0;
  plb_decode_x2 <= sl_wrdack_x0;
  plb_decode_x3 <= sl_rddack_x0;
  plb_decode_x4 <= sl_rddbus_x0;
  plb_memmap_x0 <= gpio_out8_din_x0;
  plb_memmap_x1 <= gpio_out8_en_x0;
  plb_memmap_x2 <= cmd_response_re_x0;
  plb_memmap_x3 <= cmd_request_din_x0;
  plb_memmap_x4 <= cmd_request_we_x0;

  constant5: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => sl_wait_x0
    );

  plb_decode: entity work.mcode_block_f4d0462e0e
    port map (
      addrpref => sg_plb_addrpref_net_x0,
      ce => plb_ce_1_sg_x0,
      clk => plb_clk_1_sg_x0,
      clr => '0',
      plbabus => plb_abus_net_x0,
      plbpavalid(0) => plb_pavalid_net_x0,
      plbrnw(0) => plb_rnw_net_x0,
      plbrst(0) => splb_rst_net_x0,
      plbwrdbus => plb_wrdbus_net_x0,
      rddata => rddata,
      addrack(0) => sl_addrack_x0,
      bankaddr => bankaddr,
      linearaddr => linearaddr,
      rdcomp(0) => sl_rdcomp_x0,
      rddack(0) => sl_rddack_x0,
      rddbus => sl_rddbus_x0,
      rnwreg(0) => rnwreg,
      wrdack(0) => sl_wrdack_x0,
      wrdbusreg => wrdbusreg
    );

  plb_memmap: entity work.mcode_block_57a988c97d
    port map (
      addrack(0) => sl_addrack_x0,
      bankaddr => bankaddr,
      ce => plb_ce_1_sg_x0,
      clk => plb_clk_1_sg_x0,
      clr => '0',
      linearaddr => linearaddr,
      rnwreg(0) => rnwreg,
      sm_cmd_request_full(0) => cmd_request_full_x0,
      sm_cmd_request_pfull(0) => cmd_request_pfull_x0,
      sm_cmd_response => cmd_response_dout_x0,
      sm_cmd_response_empty(0) => cmd_response_empty_x0,
      sm_cmd_response_pfull(0) => cmd_response_pfull_x0,
      sm_gpio_out8 => gpio_out8_dout_x0,
      wrdbus => wrdbusreg,
      read_bank_out => rddata,
      sm_cmd_request_din => cmd_request_din_x0,
      sm_cmd_request_we(0) => cmd_request_we_x0,
      sm_cmd_response_re(0) => cmd_response_re_x0,
      sm_gpio_out8_din => gpio_out8_din_x0,
      sm_gpio_out8_en(0) => gpio_out8_en_x0
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "sg_i2c_controller_s6/i2c_controller"

entity i2c_controller_entity_e098cd9e07 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    cmd_req_x0: in std_logic_vector(31 downto 0); 
    from_fifo: in std_logic; 
    sda_i: in std_logic; 
    mcode_x0: out std_logic; 
    mcode_x1: out std_logic_vector(31 downto 0); 
    mcode_x2: out std_logic; 
    scl_o_x0: out std_logic; 
    sda_o_x0: out std_logic
  );
end i2c_controller_entity_e098cd9e07;

architecture structural of i2c_controller_entity_e098cd9e07 is
  signal ce_1_sg_x0: std_logic;
  signal clk_1_sg_x0: std_logic;
  signal cmd_ack_x0: std_logic;
  signal cmd_get_x0: std_logic;
  signal cmd_rdy: std_logic;
  signal cmd_req_x1: std_logic_vector(31 downto 0);
  signal cmd_rsp_x0: std_logic_vector(31 downto 0);
  signal constant10_op_net: std_logic;
  signal constant1_op_net: std_logic;
  signal from_fifo_empty_net_x0: std_logic;
  signal i2c_sda_i_net_x0: std_logic;
  signal in_port: std_logic_vector(7 downto 0);
  signal out_port: std_logic_vector(7 downto 0);
  signal picoblaze_microcontroller_address_net: std_logic_vector(9 downto 0);
  signal picoblaze_rom_data_net: std_logic_vector(17 downto 0);
  signal port_id: std_logic_vector(7 downto 0);
  signal rs: std_logic;
  signal scl_o_x1: std_logic;
  signal sda_o_x1: std_logic;
  signal ws: std_logic;

begin
  ce_1_sg_x0 <= ce_1;
  clk_1_sg_x0 <= clk_1;
  cmd_req_x1 <= cmd_req_x0;
  from_fifo_empty_net_x0 <= from_fifo;
  i2c_sda_i_net_x0 <= sda_i;
  mcode_x0 <= cmd_get_x0;
  mcode_x1 <= cmd_rsp_x0;
  mcode_x2 <= cmd_ack_x0;
  scl_o_x0 <= scl_o_x1;
  sda_o_x0 <= sda_o_x1;

  constant1: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant1_op_net
    );

  constant10: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant10_op_net
    );

  inverter: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      ip(0) => from_fifo_empty_net_x0,
      op(0) => cmd_rdy
    );

  mcode: entity work.mcode_block_f21d0469ad
    port map (
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      cmd_rdy(0) => cmd_rdy,
      cmd_req => cmd_req_x1,
      out_port => out_port,
      port_id => port_id,
      rs(0) => rs,
      sda_i(0) => i2c_sda_i_net_x0,
      ws(0) => ws,
      cmd_ack(0) => cmd_ack_x0,
      cmd_get(0) => cmd_get_x0,
      cmd_rsp => cmd_rsp_x0,
      in_port => in_port,
      scl_o(0) => scl_o_x1,
      sda_o(0) => sda_o_x1
    );

  picoblaze_microcontroller: entity work.xlpb3
    port map (
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      in_port => in_port,
      instruction => picoblaze_rom_data_net,
      interrupt(0) => constant1_op_net,
      reset(0) => constant10_op_net,
      address => picoblaze_microcontroller_address_net,
      out_port => out_port,
      port_id => port_id,
      read_strobe(0) => rs,
      write_strobe(0) => ws
    );

  picoblaze_rom: entity work.xlsprom
    generic map (
      c_address_width => 10,
      c_width => 18,
      core_name0 => "bmg_41_99d18de731b34188",
      latency => 1
    )
    port map (
      addr => picoblaze_microcontroller_address_net,
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      en => "1",
      rst => "0",
      data => picoblaze_rom_data_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "sg_i2c_controller_s6"

entity sg_i2c_controller_s6 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    data_out: in std_logic_vector(7 downto 0); 
    data_out_x0: in std_logic_vector(31 downto 0); 
    data_out_x1: in std_logic_vector(31 downto 0); 
    dout: in std_logic_vector(7 downto 0); 
    empty: in std_logic; 
    empty_x0: in std_logic; 
    full: in std_logic; 
    i2c_sda_i: in std_logic; 
    percent_full: in std_logic; 
    percent_full_x0: in std_logic; 
    plb_abus: in std_logic_vector(31 downto 0); 
    plb_ce_1: in std_logic; 
    plb_clk_1: in std_logic; 
    plb_pavalid: in std_logic; 
    plb_rnw: in std_logic; 
    plb_wrdbus: in std_logic_vector(31 downto 0); 
    sg_plb_addrpref: in std_logic_vector(19 downto 0); 
    splb_rst: in std_logic; 
    data_in: out std_logic_vector(7 downto 0); 
    data_in_x0: out std_logic_vector(31 downto 0); 
    data_in_x1: out std_logic_vector(31 downto 0); 
    en: out std_logic; 
    gpio_out8_o: out std_logic_vector(7 downto 0); 
    i2c_scl: out std_logic; 
    i2c_sda_o: out std_logic; 
    i2c_sda_t: out std_logic; 
    re: out std_logic; 
    re_x0: out std_logic; 
    sl_addrack: out std_logic; 
    sl_rdcomp: out std_logic; 
    sl_rddack: out std_logic; 
    sl_rddbus: out std_logic_vector(31 downto 0); 
    sl_wait: out std_logic; 
    sl_wrcomp: out std_logic; 
    sl_wrdack: out std_logic; 
    we: out std_logic; 
    we_x0: out std_logic
  );
end sg_i2c_controller_s6;

architecture structural of sg_i2c_controller_s6 is
  attribute core_generation_info: string;
  attribute core_generation_info of structural : architecture is "sg_i2c_controller_s6,sysgen_core,{clock_period=10.00000000,clocking=Clock_Enables,compilation=Export_as_a_pcore_to_EDK,sample_periods=1.00000000000 1.00000000000,testbench=0,total_blocks=73,xilinx_constant_block_block=4,xilinx_edk_processor_block=1,xilinx_gateway_in_block=7,xilinx_gateway_out_block=11,xilinx_inverter_block=1,xilinx_mcode_block_block=3,xilinx_picoblaze_microcontroller_block=1,xilinx_shared_memory_based_from_fifo_block=2,xilinx_shared_memory_based_from_register_block=1,xilinx_shared_memory_based_to_fifo_block=2,xilinx_shared_memory_based_to_register_block=1,xilinx_single_port_read_only_memory_block=1,xilinx_system_generator_block=1,}";

  signal ce_1_sg_x1: std_logic;
  signal clk_1_sg_x1: std_logic;
  signal data_in_net: std_logic_vector(7 downto 0);
  signal data_in_x0_net: std_logic_vector(31 downto 0);
  signal data_in_x1_net: std_logic_vector(31 downto 0);
  signal data_out_x0_net: std_logic_vector(31 downto 0);
  signal data_out_x1_net: std_logic_vector(31 downto 0);
  signal dout_net: std_logic_vector(7 downto 0);
  signal empty_net: std_logic;
  signal empty_x0_net: std_logic;
  signal en_net: std_logic;
  signal from_register_data_out_net: std_logic_vector(7 downto 0);
  signal full_net: std_logic;
  signal i2c_scl_net: std_logic;
  signal i2c_sda_i_net: std_logic;
  signal i2c_sda_o_net: std_logic;
  signal i2c_sda_t_net: std_logic;
  signal percent_full_net: std_logic;
  signal percent_full_x0_net: std_logic;
  signal plb_abus_net: std_logic_vector(31 downto 0);
  signal plb_ce_1_sg_x1: std_logic;
  signal plb_clk_1_sg_x1: std_logic;
  signal plb_pavalid_net: std_logic;
  signal plb_rnw_net: std_logic;
  signal plb_wrdbus_net: std_logic_vector(31 downto 0);
  signal re_net: std_logic;
  signal re_x0_net: std_logic;
  signal sg_plb_addrpref_net: std_logic_vector(19 downto 0);
  signal sl_addrack_net: std_logic;
  signal sl_rdcomp_net: std_logic;
  signal sl_rddack_net: std_logic;
  signal sl_rddbus_net: std_logic_vector(31 downto 0);
  signal sl_wait_net: std_logic;
  signal sl_wrdack_x1: std_logic;
  signal splb_rst_net: std_logic;
  signal we_net: std_logic;
  signal we_x0_net: std_logic;

begin
  ce_1_sg_x1 <= ce_1;
  clk_1_sg_x1 <= clk_1;
  from_register_data_out_net <= data_out;
  data_out_x0_net <= data_out_x0;
  data_out_x1_net <= data_out_x1;
  dout_net <= dout;
  empty_net <= empty;
  empty_x0_net <= empty_x0;
  full_net <= full;
  i2c_sda_i_net <= i2c_sda_i;
  percent_full_net <= percent_full;
  percent_full_x0_net <= percent_full_x0;
  plb_abus_net <= plb_abus;
  plb_ce_1_sg_x1 <= plb_ce_1;
  plb_clk_1_sg_x1 <= plb_clk_1;
  plb_pavalid_net <= plb_pavalid;
  plb_rnw_net <= plb_rnw;
  plb_wrdbus_net <= plb_wrdbus;
  sg_plb_addrpref_net <= sg_plb_addrpref;
  splb_rst_net <= splb_rst;
  data_in <= data_in_net;
  data_in_x0 <= data_in_x0_net;
  data_in_x1 <= data_in_x1_net;
  en <= en_net;
  gpio_out8_o <= from_register_data_out_net;
  i2c_scl <= i2c_scl_net;
  i2c_sda_o <= i2c_sda_o_net;
  i2c_sda_t <= i2c_sda_t_net;
  re <= re_net;
  re_x0 <= re_x0_net;
  sl_addrack <= sl_addrack_net;
  sl_rdcomp <= sl_rdcomp_net;
  sl_rddack <= sl_rddack_net;
  sl_rddbus <= sl_rddbus_net;
  sl_wait <= sl_wait_net;
  sl_wrcomp <= sl_wrdack_x1;
  sl_wrdack <= sl_wrdack_x1;
  we <= we_net;
  we_x0 <= we_x0_net;

  constant1: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => i2c_sda_o_net
    );

  edk_processor_f7392c68af: entity work.edk_processor_entity_f7392c68af
    port map (
      from_fifo => data_out_x0_net,
      from_fifo_x0 => percent_full_net,
      from_fifo_x1 => empty_net,
      plb_abus => plb_abus_net,
      plb_ce_1 => plb_ce_1_sg_x1,
      plb_clk_1 => plb_clk_1_sg_x1,
      plb_pavalid => plb_pavalid_net,
      plb_rnw => plb_rnw_net,
      plb_wrdbus => plb_wrdbus_net,
      sg_plb_addrpref => sg_plb_addrpref_net,
      splb_rst => splb_rst_net,
      to_fifo => percent_full_x0_net,
      to_fifo_x0 => full_net,
      to_register => dout_net,
      constant5_x0 => sl_wait_net,
      plb_decode_x0 => sl_addrack_net,
      plb_decode_x1 => sl_rdcomp_net,
      plb_decode_x2 => sl_wrdack_x1,
      plb_decode_x3 => sl_rddack_net,
      plb_decode_x4 => sl_rddbus_net,
      plb_memmap_x0 => data_in_net,
      plb_memmap_x1 => en_net,
      plb_memmap_x2 => re_net,
      plb_memmap_x3 => data_in_x0_net,
      plb_memmap_x4 => we_net
    );

  i2c_controller_e098cd9e07: entity work.i2c_controller_entity_e098cd9e07
    port map (
      ce_1 => ce_1_sg_x1,
      clk_1 => clk_1_sg_x1,
      cmd_req_x0 => data_out_x1_net,
      from_fifo => empty_x0_net,
      sda_i => i2c_sda_i_net,
      mcode_x0 => re_x0_net,
      mcode_x1 => data_in_x1_net,
      mcode_x2 => we_x0_net,
      scl_o_x0 => i2c_scl_net,
      sda_o_x0 => i2c_sda_t_net
    );

end structural;
