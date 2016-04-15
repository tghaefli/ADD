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
-- Create Date:         Dec 03, 2009
-- Design Name:         IVK
-- Module Name:         ivk_video_gen\colorbargen.vhd
-- Project Name:        IVK
-- Target Devices:      Spartan-6
-- Avnet Boards:        IVK
--
-- Tool versions:       ISE 11.4
--
-- Description:         Color Bar Generator
--
-- Dependencies:        
--
-- Revision:            Dec 03, 2009: 1.00 Initial version
--
------------------------------------------------------------------

library ieee;
   use ieee.std_logic_1164.all;
   use ieee.numeric_std.all;
   
-- NOTES : Generate 8 color bars
--
--  R   G   B  => Color
-- === === ===    ===========
-- 000 000 000 => K (black)
-- 000 000 255 => B (blue)
-- 000 255 000 => G (green)
-- 000 255 255 => C (cyan)
-- 255 000 000 => R (red)
-- 255 000 255 => M (magenta)
-- 255 255 000 => Y (yellow)
-- 255 255 255 => W (white)
--
-- Suggested Color Bar order : WYCGMRKB
--

entity ColorBarGen is
   generic (
      HWidth_g                   : integer := 16;
      VWidth_g                   : integer := 16
   );

   port (
      -- Global Reset
      i_clk_p                    : in std_logic;
      i_Reset_p                  : in std_logic;
      
      -- Image Size
      iv_HActive_p               : in std_logic_vector(HWidth_g-1 downto 0);
      iv_VActive_p               : in std_logic_vector(VWidth_g-1 downto 0);

      -- Data Request strobe (1 cycle in advance of synchronization signals)
      iv_HCount_p                : in std_logic_vector(HWidth_g-1 downto 0);
      iv_VCount_p                : in std_logic_vector(VWidth_g-1 downto 0);
      i_PixelRequest_p           : in std_logic;
      
      -- Pixel Output
      o_PixelValid_p             : out std_logic;
      ov8_RPixel_p               : out std_logic_vector(7 downto 0);
      ov8_GPixel_p               : out std_logic_vector(7 downto 0);
      ov8_BPixel_p               : out std_logic_vector(7 downto 0)
   );
end entity ColorBarGen;

architecture Rtl of ColorBarGen is

   --
   -- Intermediate signals for output ports
   --
   
   -- Pixel Output
   signal PixelValid_s              : std_logic;
   signal v8_RPixel_s               : std_logic_vector(7 downto 0);
   signal v8_GPixel_s               : std_logic_vector(7 downto 0);
   signal v8_BPixel_s               : std_logic_vector(7 downto 0);

   --
   -- Color Bar Generation
   --
   type ColorState_t is (
      White_c,  
      Yellow_c,
      Cyan_c,
      Green_c,
      Magenta_c,
      Red_c,
      Black_c,
      Blue_c      

   );
   signal ColorState_s              : ColorState_t;

   attribute fsm_encoding           : string;
   attribute fsm_encoding of ColorState_s
                                    : signal is "sequential";
   attribute safe_implementation    : string;
   attribute safe_implementation of ColorState_s
                                    : signal is "yes";
                                    
                                    
   alias v_HActiveDiv8_a : std_logic_vector(HWidth_g-4 downto 0) is iv_HActive_p(HWidth_g-1 downto 3);

      
begin

   --
   -- Output port assignments
   --

   -- Pixel Output
   o_PixelValid_p                   <= PixelValid_s;
   ov8_RPixel_p                     <= v8_RPixel_s;
   ov8_GPixel_p                     <= v8_GPixel_s;
   ov8_BPixel_p                     <= v8_BPixel_s;
   
   --
   -- Color Bar Generation
   --
   
   ColorBar_l : process( i_Clk_p, i_Reset_p )
   begin
      if ( i_Reset_p = '1' ) then
         PixelValid_s <= '0';
         v8_RPixel_s  <= (others => '0');
         v8_GPixel_s  <= (others => '0');
         v8_BPixel_s  <= (others => '0');
         ColorState_s <= White_c;
      elsif rising_edge( i_Clk_p ) then
         -- Default values
         PixelValid_s <= '0';
         v8_RPixel_s  <= (others => '0');
         v8_GPixel_s  <= (others => '0');
         v8_BPixel_s  <= (others => '0');
         
         -- Active Video
         if ( i_PixelRequest_p = '1' ) then
            
            PixelValid_s <= '1';
            
            case ColorState_s is
            
               when White_c =>
                  if unsigned(iv_HCount_p) >= (unsigned(v_HActiveDiv8_a)-1) then
                     ColorState_s <= Yellow_c;
                  end if;                  
                  v8_RPixel_s  <= X"FF";
                  v8_GPixel_s  <= X"FF";
                  v8_BPixel_s  <= X"FF";
                  
               when Yellow_c =>
                  if unsigned(iv_HCount_p) >= (2*unsigned(v_HActiveDiv8_a)-1) then
                     ColorState_s <= Cyan_c;
                  end if;                  
                  v8_RPixel_s  <= X"FF";
                  v8_GPixel_s  <= X"FF";
                  v8_BPixel_s  <= (others => '0');
               
               when Cyan_c =>
                  if unsigned(iv_HCount_p) >= (3*unsigned(v_HActiveDiv8_a)-1) then
                     ColorState_s <= Green_c;
                  end if;                  
                  v8_RPixel_s  <= (others => '0');
                  v8_GPixel_s  <= X"FF";
                  v8_BPixel_s  <= X"FF";
                  
               when Green_c =>
                  if unsigned(iv_HCount_p) >= (4*unsigned(v_HActiveDiv8_a)-1) then
                     ColorState_s <= Magenta_c;
                  end if;                  
                  v8_RPixel_s  <= (others => '0');
                  v8_GPixel_s  <= X"FF";
                  v8_BPixel_s  <= (others => '0');
                  
               when Magenta_c =>
                  if unsigned(iv_HCount_p) >= (5*unsigned(v_HActiveDiv8_a)-1) then
                     ColorState_s <= Red_c;
                  end if;                  
                  v8_RPixel_s  <= X"FF";
                  v8_GPixel_s  <= (others => '0');
                  v8_BPixel_s  <= X"FF";
                  
               when Red_c =>
                  if unsigned(iv_HCount_p) >= (6*unsigned(v_HActiveDiv8_a)-1) then
                     ColorState_s <= Black_c;
                  end if;                  
                  v8_RPixel_s  <= X"FF";
                  v8_GPixel_s  <= (others => '0');
                  v8_BPixel_s  <= (others => '0');
                  
               when Black_c =>
                  if unsigned(iv_HCount_p) >= (7*unsigned(v_HActiveDiv8_a)-1) then
                     ColorState_s <= Blue_c;
                  end if;                  
                  v8_RPixel_s  <= (others => '0');
                  v8_GPixel_s  <= (others => '0');
                  v8_BPixel_s  <= (others => '0');
                  
               when Blue_c =>
                  if unsigned(iv_HCount_p) >= (unsigned(iv_HActive_p)-1) then
                     ColorState_s <= White_c;
                  end if;                  
                  v8_RPixel_s  <= (others => '0');
                  v8_GPixel_s  <= (others => '0');
                  v8_BPixel_s  <= X"FF";
                  
               when others =>
                  PixelValid_s <= '0';
                  v8_RPixel_s  <= (others => '0');
                  v8_GPixel_s  <= (others => '0');
                  v8_BPixel_s  <= (others => '0');   
                  ColorState_s <= White_c;
            
            end case;
         end if;
      end if;
   end process ColorBar_l;
   
end architecture Rtl;