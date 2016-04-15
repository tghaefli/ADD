------------------------------------------------------------------
--      _____
--     /     \
--    /____   \____
--   / \===\   \==/
--  /___\===\___\/  AVNET
--       \======/
--        \====/    
-----------------------------------------------------------------
--
-- This design is the property of Avnet.  Publication of this
-- design is not authorized without written consent from Avnet.
-- 
-- Please direct any questions to:  technical.support@avnet.com
--
-- Disclaimer:
--    Avnet, Inc. makes no warranty for the use of this code or design.
--    This code is provided  "As Is". Avnet, Inc assumes no responsibility for
--    any errors, which may appear in this code, nor does it make a commitment
--    to update the information contained herein. Avnet, Inc specifically
--    disclaims any implied warranties of fitness for a particular purpose.
--                     Copyright(c) 2010 Avnet, Inc.
--                             All rights reserved.
--
------------------------------------------------------------------
--
-- Create Date:         Jul 03, 2009
-- Design Name:         FMC-IMAGEOV
-- Module Name:         fmc_imageov_dvi_out.vhd
-- Project Name:        FMC-IMAGEOV
-- Target Devices:      Spartan-6
-- Avnet Boards:        FMC-IMAGEOV
--
-- Tool versions:       ISE 11.4
--
-- Description:         FMC-IMAGEOV DVI output interface.
--                      Based on VSK dvi_out.vhd and modified as follows:
--                      - rename dvi_out to fmc_imageov_dvi_out
--                      - replace dvi_clk_p/dvi_clk_n by single-ended dvi_clk
--                      - add support for more devices via C_FAMILY generic:
--                         - spartan3adsp
--                         - spartan6
--
-- Dependencies:        
--
-- Revision:            Jul 03, 2009: 1.00 Initial version
--                      Jan 15, 2010: 1.01 Add a second set of regs
--                                         Add an output enable port
--                                         Add oe and reset to debug port
--                      Feb 01, 2010: 1.02 Add selectable video interface
--                      Feb 10, 2010: 1.02b Fix XSVI video_data ordering:
--                                          [23:16] = red
--                                          [15: 8] = blue
--                                          [ 7: 0] = green
--                      May 12, 2010: 1.02c Add V6 support
--
------------------------------------------------------------------


-- DISCLAIMER OF LIABILITY
-- 
-- This text/file contains proprietary, confidential
-- information of Xilinx, Inc., is distributed under license
-- from Xilinx, Inc., and may be used, copied and/or
-- disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc. Xilinx hereby grants you a 
-- license to use this text/file solely for design, simulation, 
-- implementation and creation of design files limited 
-- to Xilinx devices or technologies. Use with non-Xilinx 
-- devices or technologies is expressly prohibited and 
-- immediately terminates your license unless covered by
-- a separate agreement.
--
-- Xilinx is providing this design, code, or information 
-- "as-is" solely for use in developing programs and 
-- solutions for Xilinx devices, with no obligation on the 
-- part of Xilinx to provide support. By providing this design, 
-- code, or information as one possible implementation of 
-- this feature, application or standard, Xilinx is making no 
-- representation that this implementation is free from any 
-- claims of infringement. You are responsible for 
-- obtaining any rights you may require for your implementation. 
-- Xilinx expressly disclaims any warranty whatsoever with 
-- respect to the adequacy of the implementation, including 
-- but not limited to any warranties or representations that this
-- implementation is free from claims of infringement, implied 
-- warranties of merchantability or fitness for a particular 
-- purpose.
--
-- Xilinx products are not intended for use in life support
-- appliances, devices, or systems. Use in such applications is
-- expressly prohibited.
--
-- Any modifications that are made to the Source Code are 
-- done at the user’s sole risk and will be unsupported.
--
--
-- Copyright (c) 2007, 2008 Xilinx, Inc. All rights reserved.
--
-- This copyright and support notice must be retained as part 
-- of this text at all times. 
--
------------------------------------------------------------------------------
-- Filename            : dvi_out.vhd
-- $Revision:: 2433   $: Revision of last commit
-- $Date:: 2008-05-27#$: Date of last commit
-- Description         : DVI Output Hardware Interface
------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
library UNISIM;
use UNISIM.VComponents.all;

entity fmc_imageov_dvi_out is
   Generic
   (
      C_VIDEO_INTERFACE  : integer := 2;
      C_DATA_WIDTH       : integer := 8;
      C_FAMILY           : string  := "spartan6"
   );
   Port
   (
      clk                : in  std_logic;
      reset              : in  std_logic;
      ce                 : in  std_logic;
      oe                 : in  std_logic;
      -- DVI Input Port
      dvi_de_i           : in  std_logic;
      dvi_vsync_i        : in  std_logic;
      dvi_hsync_i        : in  std_logic;
      dvi_red_i          : in  std_logic_vector(7 downto 0);
      dvi_green_i        : in  std_logic_vector(7 downto 0);
      dvi_blue_i         : in  std_logic_vector(7 downto 0);
      -- XSVI Input Port
      xsvi_vsync_i       : in  std_logic;
      xsvi_hsync_i       : in  std_logic;
      xsvi_active_video_i: in  std_logic;
      xsvi_video_data_i  : in  std_logic_vector((C_DATA_WIDTH-1) downto 0);
      -- I/O pins
      io_dvi_de          : out std_logic;
      io_dvi_vsync       : out std_logic;
      io_dvi_hsync       : out std_logic;
      io_dvi_data        : out std_logic_vector(11 downto 0);
      io_dvi_clk         : out std_logic;
      io_dvi_reset_n     : out std_logic;
      -- Debug Port
      debug_o            : out std_logic_vector(28 downto 0)
   );
end fmc_imageov_dvi_out;

architecture rtl of fmc_imageov_dvi_out is

   signal clk_n          : std_logic;
   signal net0           : std_logic;
   signal net1           : std_logic;

   signal de_r           : std_logic;
   signal vsync_r        : std_logic;
   signal hsync_r        : std_logic;
   signal red_r          : std_logic_vector(7 downto 0);
   signal green_r        : std_logic_vector(7 downto 0);
   signal blue_r         : std_logic_vector(7 downto 0);
   
   signal d1             : std_logic_vector(11 downto 0);
   signal d2             : std_logic_vector(11 downto 0);
   signal d2_r           : std_logic_vector(11 downto 0);
   
   signal oe_n           : std_logic;

   signal dvi_de_o       : std_logic;
   signal dvi_vsync_o    : std_logic;
   signal dvi_hsync_o    : std_logic;
   signal dvi_data_o     : std_logic_vector(11 downto 0);
   signal dvi_clk_o      : std_logic;
   signal dvi_reset_n_o  : std_logic;

   signal dvi_de_t       : std_logic;
   signal dvi_vsync_t    : std_logic;
   signal dvi_hsync_t    : std_logic;
   signal dvi_data_t     : std_logic_vector(11 downto 0);
   signal dvi_clk_t      : std_logic;
   signal dvi_reset_n_t  : std_logic;

begin

   clk_n <= not clk;
   net0 <= '0';
   net1 <= '1';

   dvi_reset_n_o <= not reset;
   dvi_reset_n_t <= not oe;
   

   DVI_IPORT_GEN : if (C_VIDEO_INTERFACE = 1) generate
      dvi_iregs_l : process (clk)
      begin
         if Rising_Edge(clk) then
            de_r    <= dvi_de_i;
            vsync_r <= dvi_vsync_i;
            hsync_r <= dvi_hsync_i;
            red_r   <= dvi_red_i;
            green_r <= dvi_green_i;
            blue_r  <= dvi_blue_i;
         end if;
      end process;
   end generate DVI_IPORT_GEN;

   XSVI_IPORT_GEN : if (C_VIDEO_INTERFACE = 2) generate
      XSVI_8BIT_GEN : if (C_DATA_WIDTH = 8) generate
         xsvi_8bit_iregs_l : process (clk)
         begin
            if Rising_Edge(clk) then
               de_r    <= xsvi_active_video_i;
               vsync_r <= xsvi_vsync_i;
               hsync_r <= xsvi_hsync_i;
               red_r   <= xsvi_video_data_i(7 downto 0);
               green_r <= xsvi_video_data_i(7 downto 0);
               blue_r  <= xsvi_video_data_i(7 downto 0);
            end if;
         end process;
      end generate XSVI_8BIT_GEN;
      XSVI_24BIT_GEN : if (C_DATA_WIDTH = 24) generate
         xsvi_24bit_iregs_l : process (clk)
         begin
            if Rising_Edge(clk) then
               de_r    <= xsvi_active_video_i;
               vsync_r <= xsvi_vsync_i;
               hsync_r <= xsvi_hsync_i;
               red_r   <= xsvi_video_data_i(23 downto 16);
               blue_r <= xsvi_video_data_i( 7 downto  0);
               green_r  <= xsvi_video_data_i(15 downto  8);
            end if;
         end process;
      end generate XSVI_24BIT_GEN;
      XSVI_30BIT_GEN : if (C_DATA_WIDTH = 30) generate
         xsvi_20bit_iregs_l : process (clk)
         begin
            if Rising_Edge(clk) then
               de_r    <= xsvi_active_video_i;
               vsync_r <= xsvi_vsync_i;
               hsync_r <= xsvi_hsync_i;
               red_r   <= xsvi_video_data_i(29 downto 22);
               green_r <= xsvi_video_data_i( 9 downto  2);
               blue_r  <= xsvi_video_data_i(19 downto 12);
            end if;
         end process;
      end generate XSVI_30BIT_GEN;
   end generate XSVI_IPORT_GEN;
   
   d1    <= green_r(3 downto 0) & blue_r;
   d2    <= red_r & green_r(7 downto 4);
   
   oe_n  <= not oe;

   OUT_Reg : process (clk)
   begin
      if Rising_Edge(clk) then
         dvi_de_o      <= de_r;
         dvi_vsync_o   <= vsync_r;
         dvi_hsync_o   <= hsync_r;
         --
         dvi_de_t      <= oe_n;
         dvi_vsync_t   <= oe_n;
         dvi_hsync_t   <= oe_n;
      end if;
   end process;

   S3ADSP_GEN : if (C_FAMILY = "spartan3adsp") generate

      Delay_Reg : process (clk)
      begin
         if (clk'event and (clk = '1')) then
            d2_r <= d2;
         end if;
      end process;

      O1: for I in 0 to 11 generate
         ODDR_dvi_data_o : ODDR2 
           generic map (
              DDR_ALIGNMENT => "NONE", -- "NONE", "C0" or "C1" 
              INIT => '1',             -- Sets initial state of Q  
              SRTYPE => "ASYNC")       -- Reset type
            port map (
               Q  => dvi_data_o(I),
               C0 => clk,
               C1 => clk_n,
               CE => net1,
               D0 => d1(I), 
               D1 => d2_r(I), 
               R  => net0, 
               S  => net0);
      end generate O1;

      ODDR_dvi_clk_o : ODDR2 
         generic map (
            DDR_ALIGNMENT => "NONE", -- "NONE", "C0" or "C1" 
            INIT => '1',             -- Sets initial state of Q  
            SRTYPE => "ASYNC")       -- Reset type     
         port map (
            Q  => dvi_clk_o,
            C0 => clk,
            C1 => clk_n,
            CE => net1,
            D0 => net0, 
            D1 => net1, 
            R  => net0, 
            S  => net0);

      T1: for I in 0 to 11 generate
         ODDR_dvi_data_t : ODDR2 
           generic map (
              DDR_ALIGNMENT => "NONE", -- "NONE", "C0" or "C1" 
              INIT => '1',             -- Sets initial state of Q  
              SRTYPE => "ASYNC")       -- Reset type
            port map (
               Q  => dvi_data_t(I),
               C0 => clk,
               C1 => clk_n,
               CE => net1,
               D0 => oe_n, 
               D1 => oe_n, 
               R  => net0, 
               S  => net0);
      end generate T1;

      ODDR_dvi_clk_t : ODDR2 
         generic map (
            DDR_ALIGNMENT => "NONE", -- "NONE", "C0" or "C1" 
            INIT => '1',             -- Sets initial state of Q  
            SRTYPE => "ASYNC")       -- Reset type     
         port map (
            Q  => dvi_clk_t,
            C0 => clk,
            C1 => clk_n,
            CE => net1,
            D0 => oe_n, 
            D1 => oe_n, 
            R  => net0, 
            S  => net0);

   end generate S3ADSP_GEN;

   S6_GEN : if (C_FAMILY = "spartan6") generate

      O1: for I in 0 to 11 generate
         ODDR_dvi_data_o : ODDR2 
           generic map (
              DDR_ALIGNMENT => "C0", -- "NONE", "C0" or "C1" 
              INIT => '1',             -- Sets initial state of Q  
              SRTYPE => "ASYNC")       -- Reset type
            port map (
               Q  => dvi_data_o(I),
               C0 => clk,
               C1 => clk_n,
               CE => net1,
               D0 => d1(I), 
               D1 => d2(I), 
               R  => net0,
               S  => net0);
      end generate O1;

      ODDR_dvi_clk_o : ODDR2 
         generic map (
            DDR_ALIGNMENT => "C0", -- "NONE", "C0" or "C1" 
            INIT => '1',             -- Sets initial state of Q  
            SRTYPE => "ASYNC")       -- Reset type     
         port map (
            Q  => dvi_clk_o,
            C0 => clk,
            C1 => clk_n,
            CE => net1,
            D0 => net0,
            D1 => net1,
            R  => net0,
            S  => net0);

      T1: for I in 0 to 11 generate
         ODDR_dvi_data_t : ODDR2 
           generic map (
              DDR_ALIGNMENT => "C0", -- "NONE", "C0" or "C1" 
              INIT => '1',             -- Sets initial state of Q  
              SRTYPE => "ASYNC")       -- Reset type
            port map (
               Q  => dvi_data_t(I),
               C0 => clk,
               C1 => clk_n,
               CE => net1,
               D0 => oe_n, 
               D1 => oe_n, 
               R  => net0, 
               S  => net0);
      end generate T1;

      ODDR_dvi_clk_t : ODDR2 
         generic map (
            DDR_ALIGNMENT => "C0", -- "NONE", "C0" or "C1" 
            INIT => '1',             -- Sets initial state of Q  
            SRTYPE => "ASYNC")       -- Reset type     
         port map (
            Q  => dvi_clk_t,
            C0 => clk,
            C1 => clk_n,
            CE => net1,
            D0 => oe_n, 
            D1 => oe_n, 
            R  => net0, 
            S  => net0);

   end generate S6_GEN;

   V6_GEN : if (C_FAMILY = "virtex6") generate

      O1: for I in 0 to 11 generate
         ODDR_dvi_data_o : ODDR 
           generic map (
              DDR_CLK_EDGE => "SAME_EDGE")
            port map (
               Q  => dvi_data_o(I),
               C  => clk,
               CE => net1,
               D1 => d1(I), 
               D2 => d2(I), 
               R  => net0,
               S  => net0);
      end generate O1;

      ODDR_dvi_clk_o : ODDR
         generic map (
              DDR_CLK_EDGE => "SAME_EDGE")
         port map (
            Q  => dvi_clk_o,
            C  => clk,
            CE => net1,
            D1 => net0,
            D2 => net1,
            R  => net0,
            S  => net0);

      T1: for I in 0 to 11 generate
         ODDR_dvi_data_t : ODDR 
           generic map (
              DDR_CLK_EDGE => "SAME_EDGE")
            port map (
               Q  => dvi_data_t(I),
               C  => clk,
               CE => net1,
               D1 => oe_n, 
               D2 => oe_n, 
               R  => net0, 
               S  => net0);
      end generate T1;

      ODDR_dvi_clk_t : ODDR 
         generic map (
              DDR_CLK_EDGE => "SAME_EDGE")
         port map (
            Q  => dvi_clk_t,
            C  => clk,
            CE => net1,
            D1 => oe_n, 
            D2 => oe_n, 
            R  => net0, 
            S  => net0);

   end generate V6_GEN;

   --
   -- Tri-stateable outputs
   --    Can be used to disable outputs to FMC connector
   --    until FMC module is correctly identified.
   -- 

   OBUFT_dvi_de : OBUFT
   port map (
      O => io_dvi_de,
      I => dvi_de_o,
      T => dvi_de_t
   );

   OBUFT_dvi_vsync : OBUFT
   port map (
      O => io_dvi_vsync,
      I => dvi_vsync_o,
      T => dvi_vsync_t
   );

   OBUFT_dvi_hsync : OBUFT
   port map (
      O => io_dvi_hsync,
      I => dvi_hsync_o,
      T => dvi_hsync_t
   );

   IO1: for I in 0 to 11 generate
      OBUFT_dvi_data : OBUFT
      port map (
         O => io_dvi_data(I),
         I => dvi_data_o(I),
         T => dvi_data_t(I)
      );
   end generate IO1;
   
   OBUFT_dvi_clk : OBUFT
   port map (
      O => io_dvi_clk,
      I => dvi_clk_o,
      T => dvi_clk_t
   );

   OBUFT_dvi_reset_n : OBUFT
   port map (
      O => io_dvi_reset_n,
      I => dvi_reset_n_o,
      T => dvi_reset_n_t
   );

   --
   -- Debug Port
   --    Can be used to connect to ChipScope for debugging.
   --    Having a port makes these signals accessible for debug via EDK.
   -- 

   debug_l : process (clk)
   begin
      if Rising_Edge(clk) then
         debug_o( 7 downto  0) <= blue_r;
         debug_o(15 downto  8) <= green_r;
         debug_o(23 downto 16) <= red_r;
         debug_o(          24) <= de_r;
         debug_o(          25) <= hsync_r;
         debug_o(          26) <= vsync_r;
         debug_o(          27) <= oe;
         debug_o(          28) <= reset;
      end if;
   end process;

        
end rtl;
