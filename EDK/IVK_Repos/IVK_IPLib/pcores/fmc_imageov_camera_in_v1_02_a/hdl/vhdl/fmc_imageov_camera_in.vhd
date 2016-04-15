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
-- Description:         FMC-IMAGEOV Camera input interface.
--                      Based on VSK camera.vhd and modified as follows:
--                      - rename camera to fmc_imageov_camera_in
--                      - add support for more devices via C_FAMILY generic:
--                         - spartan3adsp
--                         - spartan6
--
--                      The OV9715 image sensor is configured to generate CCIR656 codes.
--                      - VREF is used as VSYNC
--                      - HREF is used as HSYNC
--                      - The following signals are generated from the CCIR656 codes:
--                         - ACTIVE_VIDEO (DE)
--                         - HBLANK
--                         - VBLANK
--
--                      Observations with ChipScope reveils that the first active line
--                      has unusual CCIR656 codes, which results in line 1 being dropped.
--                      
--                      Case             Code  Y[9:0] => 1  F  V  H P3 P2 P1 P0 -- --
--                      =============================================================
--                      ACTIVE LINE 1     FS   0x2AC     1  0  1  0  1  0  1  1  0  0
--                                        LE   0x274     1  0  0  1  1  1  0  1  0  0
--                      -------------------------------------------------------------
--                      ACTIVE LINES 2-N  LS   0x200     1  0  0  0  0  0  0  0  0  0
--                                        LE   0x274     1  0  0  1  1  1  0  1  0  0
--                      -------------------------------------------------------------
--                      INACTIVE LINES    FS   0x2AC     1  0  1  0  1  0  1  1  0  0
--                                        FE   0x2D8     1  0  1  1  0  1  1  0  0  0
--                      =============================================================
--
-- Dependencies:        
--
-- Revision:            Jul 03, 2009: 1.00 Initial version
--                      Dec 01, 2009: 1.01 Increase CAMERA_VIDEO_OUT data width to 10 bits
--                      Feb 01, 2010: 1.02 Add selectable video interface
--
------------------------------------------------------------------


-- DISCLAIMER OF LIABILITY
-- 
-- This text/file contains proprietary, confidential
-- information of Xilinx, Inc., is distributed under license
-- from Xilinx, Inc., and may be used, copied and/or
-- disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc. Xilinx hereby grants you 
-- a license to use this text/file solely for design, simulation, 
-- implementation and creation of design files limited 
-- to Xilinx devices or technologies. Use with non-Xilinx 
-- devices or technologies is expressly prohibited and 
-- immediately terminates your license unless covered by
-- a separate agreement.
--
-- Xilinx is providing this design, code, or information 
-- "as-is" solely for use in developing programs and 
-- solutions for Xilinx devices. By providing this design, 
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
--
-- Copyright (c) 2007, 2008 Xilinx, Inc. All rights reserved.
--
-- This copyright and support notice must be retained as part 
-- of this text at all times. 
--
------------------------------------------------------------------------------
-- Filename            : camera.vhd
-- $Revision:: 2433   $: Revision of last commit
-- $Date:: 2008-05-27#$: Date of last commit
-- Description         : Camera VHDL Hardware Interface
------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity fmc_imageov_camera_in is
   Generic
   (
      C_VIDEO_INTERFACE    : integer := 2; 
      C_DATA_WIDTH         : integer := 8;
      C_FAMILY             : string := "spartan6"
   );
   Port
   (
      clk                  : in  std_logic;
      ce                   : in  std_logic;
      -- IO Pins
      io_frame_valid_i     : in  std_logic;
      io_line_valid_i      : in  std_logic;
      io_data_i            : in  std_logic_vector(9 downto 0);
      -- Camera Port
      camera_frame_valid_o : out  std_logic;
      camera_line_valid_o  : out  std_logic;
      camera_data_o        : out  std_logic_vector((C_DATA_WIDTH-1) downto 0);
      -- DVI Port
      dvi_vsync_o          : out  std_logic;
      dvi_hsync_o          : out  std_logic;
      dvi_de_o             : out  std_logic;
      dvi_red_o            : out  std_logic_vector(7 downto 0);
      dvi_green_o          : out  std_logic_vector(7 downto 0);
      dvi_blue_o           : out  std_logic_vector(7 downto 0);
      -- XSVI Port
      xsvi_vsync_o         : out  std_logic;
      xsvi_hsync_o         : out  std_logic;
      xsvi_vblank_o        : out  std_logic;
      xsvi_hblank_o        : out  std_logic;
      xsvi_active_video_o  : out  std_logic;
      xsvi_video_data_o    : out  std_logic_vector((C_DATA_WIDTH-1) downto 0);
      -- Debug Ports
      debug_o              : out  std_logic_vector(14 downto 0)
   );
end fmc_imageov_camera_in;

architecture rtl of fmc_imageov_camera_in is

   signal frame_valid_r  : std_logic;
   signal line_valid_r   : std_logic;
   signal data_r         : std_logic_vector(9 downto 0);

   --
   -- Input Delay
   -- 
   
   signal data_d1        : std_logic_vector(9 downto 0);
   signal data_d2        : std_logic_vector(9 downto 0);
   signal data_d3        : std_logic_vector(9 downto 0);
   signal data_d4        : std_logic_vector(9 downto 0);
   signal frame_valid_d1 : std_logic;
   signal frame_valid_d2 : std_logic;
   signal frame_valid_d3 : std_logic;
   signal frame_valid_d4 : std_logic;
   signal line_valid_d1  : std_logic;
   signal line_valid_d2  : std_logic;
   signal line_valid_d3  : std_logic;
   signal line_valid_d4  : std_logic;
   
   --
   -- CCIR656 Decode Logic
   -- 
   
   signal sav            : std_logic; 
   signal eav            : std_logic; 
   signal siv            : std_logic; 
   signal eiv            : std_logic; 
   signal sav_d1         : std_logic;
   signal sav_d2         : std_logic;
   signal sav_d3         : std_logic;
   signal sav_d4         : std_logic;
   signal siv_d1         : std_logic;
   signal siv_d2         : std_logic;
   signal siv_d3         : std_logic;
   signal siv_d4         : std_logic;
   
   signal vblank         : std_logic;
   signal hblank         : std_logic;
   signal active_video   : std_logic;

begin
   
   In_Reg : process (clk)
   begin
      if Rising_Edge(clk) then
         frame_valid_r  <= io_frame_valid_i;
         line_valid_r   <= io_line_valid_i;
         data_r         <= io_data_i;
      end if;
   end process;

   --
   -- Input Delay
   -- 
   
   input_delay_l : process (clk)
   begin
      if Rising_Edge(clk) then
         -- Delay DATA by 4 cycles to have a 4 cycle view of data
         data_d1        <= data_r;
         data_d2        <= data_d1;
         data_d3        <= data_d2;
         data_d4        <= data_d3;
         --
         frame_valid_d1 <= frame_valid_r;
         frame_valid_d2 <= frame_valid_d1;
         frame_valid_d3 <= frame_valid_d2;
         frame_valid_d4 <= frame_valid_d3;
         --
         line_valid_d1  <= line_valid_r;
         line_valid_d2  <= line_valid_d1;
         line_valid_d3  <= line_valid_d2;
         line_valid_d4  <= line_valid_d3;
      end if;
   end process;


   --
   -- CCIR656 Decode Logic
   -- 
   
   ccir656_decode_l : process ( data_r, data_d1, data_d2, data_d3, data_d4 )
   begin
      -- Start of Active Video (H=0, V=0)
      sav               <= '0';
      if ( (data_d3 = X"3FF") and (data_d2 = X"000") and (data_d1 = X"000") and (data_r = X"200") ) then
         sav            <= '1';
      end if;
      
      -- End of Active Video (H=1, V=0)
      eav               <= '0';
      if ( (data_d3 = X"3FF") and (data_d2 = X"000") and (data_d1 = X"000") and (data_r = X"274") ) then
         eav            <= '1';
      end if;

      -- Start of Inactive Video (H=0, V=1)
      siv               <= '0';
      if ( (data_d3 = X"3FF") and (data_d2 = X"000") and (data_d1 = X"000") and (data_r = X"2AC") ) then
         siv            <= '1';
      end if;
      
      -- End of Inactive Video (H=1, V=1)
      eiv               <= '0';
      if ( (data_d3 = X"3FF") and (data_d2 = X"000") and (data_d2 = X"000") and (data_r = X"2D8") ) then
         eiv            <= '1';
      end if;
      
   end process;

   ccir656_syncgen_l : process (clk)
   begin
      if Rising_Edge(clk) then
         -- Delay DATA by 4 cycles to have a 4 cycle view of data
         data_d1        <= data_r;
         data_d2        <= data_d1;
         data_d3        <= data_d2;
         data_d4        <= data_d3;

         -- Delay SAV by 4 cycles
         sav_d1         <= sav;
         sav_d2         <= sav_d1;
         sav_d3         <= sav_d2;
         sav_d4         <= sav_d3;

         -- Delay SIV by 4 cycles
         siv_d1         <= siv;
         siv_d2         <= siv_d1;
         siv_d3         <= siv_d2;
         siv_d4         <= siv_d3;

         -- Create Active Video strobe based on SAV/EAV events         
         if ( sav_d4 = '1' ) then
            active_video<= '1';
         end if;
         if ( eav = '1' ) then
            active_video<= '0';
         end if;

         -- Create VBLANK strobes based on SIV/SAV events
         if ( siv = '1' ) then
            vblank      <= '1';
         end if;
         if ( sav = '1' ) then
            vblank      <= '0';
         end if;
         
         -- Create HBLANK strobes based on SAV/EAV/SIV/EIV events
         if ( sav_d4 = '1' or siv_d4 = '1' ) then
            hblank      <= '0';
         end if;
         if ( eav = '1' or eiv = '1' ) then
            hblank      <= '1';
         end if;
         
      end if;
   end process;

   --
   -- Camera Port
   -- 

   CAMERA_OPORT_GEN : if (C_VIDEO_INTERFACE = 0) generate
      CAMERA_8BIT_GEN : if (C_DATA_WIDTH = 8) generate
         camera_8bit_oregs_l : process (clk)
         begin
            if rising_edge( clk ) then
               camera_frame_valid_o <= frame_valid_r;
               camera_line_valid_o  <= line_valid_r;
               camera_data_o        <= data_r(9 downto 2);
            end if;
         end process;
      end generate CAMERA_8BIT_GEN;
      CAMERA_10BIT_GEN : if (C_DATA_WIDTH = 10) generate
         camera_10bit_oregs_l : process (clk)
         begin
            if rising_edge( clk ) then
               camera_frame_valid_o <= frame_valid_r;
               camera_line_valid_o  <= line_valid_r;
               camera_data_o        <= data_r(9 downto 0);
            end if;
         end process;
      end generate CAMERA_10BIT_GEN;
      --
      dvi_vsync_o          <= '0';
      dvi_hsync_o          <= '0';
      dvi_de_o             <= '0';
      dvi_red_o            <= (others => '0');
      dvi_green_o          <= (others => '0');
      dvi_blue_o           <= (others => '0');
      --
      xsvi_vsync_o         <= '0';
      xsvi_hsync_o         <= '0';
      xsvi_vblank_o        <= '0';
      xsvi_hblank_o        <= '0';
      xsvi_active_video_o  <= '0';
      xsvi_video_data_o    <= (others => '0');
   end generate CAMERA_OPORT_GEN;

   --
   -- DVI Port
   -- 

   DVI_OPORT_GEN : if (C_VIDEO_INTERFACE = 1) generate
      dvi_oregs_l : process (clk)
      begin
         if rising_edge( clk ) then
            dvi_vsync_o <= frame_valid_d4;
            dvi_hsync_o <= line_valid_d4;
            dvi_de_o    <= active_video;
            dvi_red_o   <= data_d4(9 downto 2);
            dvi_green_o <= data_d4(9 downto 2);
            dvi_blue_o  <= data_d4(9 downto 2);
         end if;
      end process;
      --
      camera_frame_valid_o <= '0';
      camera_line_valid_o  <= '0';
      camera_data_o        <= (others => '0');
      --
      xsvi_vsync_o         <= '0';
      xsvi_hsync_o         <= '0';
      xsvi_vblank_o        <= '0';
      xsvi_hblank_o        <= '0';
      xsvi_active_video_o  <= '0';
      xsvi_video_data_o    <= (others => '0');
   end generate DVI_OPORT_GEN;

   --
   -- XSVI Port
   -- 

   XSVI_OPORT_GEN : if (C_VIDEO_INTERFACE = 2) generate
      XSVI_8BIT_GEN : if (C_DATA_WIDTH = 8) generate
         xsvi_8bit_oregs_l : process (clk)
            begin
            if rising_edge( clk ) then
               xsvi_vsync_o        <= frame_valid_d4;
               xsvi_hsync_o        <= line_valid_d4;
               xsvi_vblank_o       <= vblank;
               xsvi_hblank_o       <= hblank;
               xsvi_active_video_o <= active_video;
               xsvi_video_data_o   <= data_d4(9 downto 2);
            end if;
         end process;
      end generate XSVI_8BIT_GEN;
      XSVI_10BIT_GEN : if (C_DATA_WIDTH = 10) generate
         xsvi_10bit_oregs_l : process (clk)
            begin
            if rising_edge( clk ) then
               xsvi_vsync_o        <= frame_valid_d4;
               xsvi_hsync_o        <= line_valid_d4;
               xsvi_vblank_o       <= vblank;
               xsvi_hblank_o       <= hblank;
               xsvi_active_video_o <= active_video;
               xsvi_video_data_o   <= data_d4(9 downto 0);
            end if;
         end process;
      end generate XSVI_10BIT_GEN;
      --
      camera_frame_valid_o <= '0';
      camera_line_valid_o  <= '0';
      camera_data_o        <= (others => '0');
      --
      dvi_vsync_o          <= '0';
      dvi_hsync_o          <= '0';
      dvi_de_o             <= '0';
      dvi_red_o            <= (others => '0');
      dvi_green_o          <= (others => '0');
      dvi_blue_o           <= (others => '0');
   end generate XSVI_OPORT_GEN;

   --
   -- Debug Port
   --    Can be used to connect to ChipScope for debugging.
   --    Having a port makes these signals accessible for debug via EDK.
   -- 

   debug_l : process (clk)
   begin
      if rising_edge( clk ) then
         debug_o        <= vblank & hblank & active_video & frame_valid_d4 & line_valid_d4 & data_d4;
      end if;
   end process;

         
end rtl;
