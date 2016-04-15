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
-- Module Name:         ivk_video_gen\user_logic.vhd
-- Project Name:        IVK
-- Target Devices:      Spartan-6
-- Avnet Boards:        IVK
--
-- Tool versions:       ISE 12.1
--
-- Description:         
--
-- Dependencies:        
--
-- Revision:            Dec 03, 2009: 1.00 Initial version
--                      Feb 01, 2010: 1.02 Add selectable video interface
--                      Feb 10, 2010: 1.02b Fix XSVI video_data ordering:
--                                          [23:16] = red
--                                          [15: 8] = blue
--                                          [ 7: 0] = green
--                      Mar 02, 2010: 1.03 Add optionnal VDMA Write Port
--                      Mar 10, 2010: 1.04 Force FSYNC to active high polarity
--                      Apr 12, 2010: 1.05 Fix VBlank/HBlank outputs
--                      Apr 13, 2010: 1.06 Add support for 16bit data width on XSVI input
--                      May 14, 2010: 2.01 Update for 12.1
--
------------------------------------------------------------------

-- DO NOT EDIT BELOW THIS LINE --------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library proc_common_v3_00_a;
use proc_common_v3_00_a.proc_common_pkg.all;

-- DO NOT EDIT ABOVE THIS LINE --------------------

--USER libraries added here

------------------------------------------------------------------------------
-- Entity section
------------------------------------------------------------------------------
-- Definition of Generics:
--   C_SLV_DWIDTH                 -- Slave interface data bus width
--   C_NUM_REG                    -- Number of software accessible registers
--
-- Definition of Ports:
--   Bus2IP_Clk                   -- Bus to IP clock
--   Bus2IP_Reset                 -- Bus to IP reset
--   Bus2IP_Data                  -- Bus to IP data bus
--   Bus2IP_BE                    -- Bus to IP byte enables
--   Bus2IP_RdCE                  -- Bus to IP read chip enable
--   Bus2IP_WrCE                  -- Bus to IP write chip enable
--   IP2Bus_Data                  -- IP to Bus data bus
--   IP2Bus_RdAck                 -- IP to Bus read transfer acknowledgement
--   IP2Bus_WrAck                 -- IP to Bus write transfer acknowledgement
--   IP2Bus_Error                 -- IP to Bus error response
------------------------------------------------------------------------------

entity user_logic is
  generic
  (
    -- ADD USER GENERICS BELOW THIS LINE ---------------
    C_GEN_FSYNC                    : integer              := 0; 
    C_GEN_RD_VDMA                  : integer              := 0; 
    C_VIDEO_INTERFACE              : integer              := 2;
    C_XSVI_DATA_WIDTH              : integer              := 24;
    C_VDMA_DATA_WIDTH              : integer              := 32;
    -- ADD USER GENERICS ABOVE THIS LINE ---------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol parameters, do not add to or delete
    C_SLV_DWIDTH                   : integer              := 32;
    C_NUM_REG                      : integer              := 4;
    C_FAMILY                       : string               := "spartan6"
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );
  port
  (
    -- ADD USER PORTS BELOW THIS LINE ------------------
    -- Global Reset (asynchronous)
    reset                     : in std_logic;
    clk                       : in std_logic;
      -- Camera Port
      camera_frame_valid_o : out  std_logic;
      camera_line_valid_o  : out  std_logic;
      camera_data_o        : out  std_logic_vector((C_XSVI_DATA_WIDTH-1) downto 0);
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
      xsvi_video_data_o    : out  std_logic_vector((C_XSVI_DATA_WIDTH-1) downto 0);
      -- VDMA Read Port
    --vdma_rcmd_clk        : out std_logic;
      vdma_rd_clk          : out std_logic;
      vdma_rd_read         : out std_logic;
      vdma_rd_data         : in std_logic_vector((C_VDMA_DATA_WIDTH-1) downto 0);
      -- Frame Sync Output Port
      fsync_o              : out std_logic;
    -- ADD USER PORTS ABOVE THIS LINE ------------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol ports, do not add to or delete
    Bus2IP_Clk                     : in  std_logic;
    Bus2IP_Reset                   : in  std_logic;
    Bus2IP_Data                    : in  std_logic_vector(0 to C_SLV_DWIDTH-1);
    Bus2IP_BE                      : in  std_logic_vector(0 to C_SLV_DWIDTH/8-1);
    Bus2IP_RdCE                    : in  std_logic_vector(0 to C_NUM_REG-1);
    Bus2IP_WrCE                    : in  std_logic_vector(0 to C_NUM_REG-1);
    IP2Bus_Data                    : out std_logic_vector(0 to C_SLV_DWIDTH-1);
    IP2Bus_RdAck                   : out std_logic;
    IP2Bus_WrAck                   : out std_logic;
    IP2Bus_Error                   : out std_logic
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );

  attribute SIGIS : string;
  attribute SIGIS of Bus2IP_Clk    : signal is "CLK";
  attribute SIGIS of Bus2IP_Reset  : signal is "RST";

end entity user_logic;

------------------------------------------------------------------------------
-- Architecture section
------------------------------------------------------------------------------

architecture rtl of user_logic is


	function toLittleEndian (a : std_logic_vector) return std_logic_vector is
		variable result : std_logic_vector(a'length-1 downto 0);
	begin
		for i in result'RANGE loop
			result(i) := a(a'length-1-i);
		end loop;
		return result;
	end;

	function toBigEndian (a: std_logic_vector) return std_logic_vector is
		variable result : std_logic_vector(0 to a'length-1);
	begin
		for i in result'RANGE loop
			result(i) := a(a'length-1-i);
		end loop;
		return result;
	end;
	
  ------------------------------------------
  -- Signals for user logic slave model s/w accessible register example
  ------------------------------------------
  signal slv_reg0                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg1                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg2                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg3                      : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg_write_sel             : std_logic_vector(0 to 3);
  signal slv_reg_read_sel              : std_logic_vector(0 to 3);
  signal slv_ip2bus_data               : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_read_ack                  : std_logic;
  signal slv_write_ack                 : std_logic;

  signal rd_hsync1_reg                 : std_logic_vector(31 downto 0);
  signal rd_hsync2_reg                 : std_logic_vector(31 downto 0);
  signal rd_vsync1_reg                 : std_logic_vector(31 downto 0);
  signal rd_vsync2_reg                 : std_logic_vector(31 downto 0);

   --
   -- Video Synchronization Generator
   --

   constant HWidth_c                : integer := 16;
   constant VWidth_c                : integer := 16; 
   
   component VideoSyncGen
      generic (
         HWidth_g                   : integer := 16;
         VWidth_g                   : integer := 16 
      );
      port (
         -- Global Reset
         i_Clk_p                    : in std_logic;
         i_Reset_p                  : in std_logic;

         -- Video Configuration
         iv16_VidHActive_p          : in std_logic_vector(15 downto 0);
         iv16_VidHFPorch_p          : in std_logic_vector(15 downto 0);
         iv16_VidHSync_p            : in std_logic_vector(15 downto 0);
         iv16_VidHBPorch_p          : in std_logic_vector(15 downto 0);
         --
         iv16_VidVActive_p          : in std_logic_vector(15 downto 0);
         iv16_VidVFPorch_p          : in std_logic_vector(15 downto 0);
         iv16_VidVSync_p            : in std_logic_vector(15 downto 0);
         iv16_VidVBPorch_p          : in std_logic_vector(15 downto 0);
         
         -- Video Synchronization Signals
         o_HBlank_p                 : out std_logic;
         o_VBlank_p                 : out std_logic;
         o_HSync_p                  : out std_logic;
         o_VSync_p                  : out std_logic;
         o_De_p                     : out std_logic;

         -- Data Request strobe (1 cycle in advance of synchronization signals)
         ov_HCount_p                : out std_logic_vector(HWidth_g-1 downto 0);
         ov_VCount_p                : out std_logic_vector(VWidth_g-1 downto 0);
         o_PixelRequest_p           : out std_logic
      );
   end component;

   -- Video Configuration
   signal v16_VidHActive_s          : std_logic_vector(15 downto 0);
   signal v16_VidHFPorch_s          : std_logic_vector(15 downto 0);
   signal v16_VidHSync_s            : std_logic_vector(15 downto 0);
   signal v16_VidHBPorch_s          : std_logic_vector(15 downto 0);
   --
   signal v16_VidVActive_s          : std_logic_vector(15 downto 0);
   signal v16_VidVFPorch_s          : std_logic_vector(15 downto 0);
   signal v16_VidVSync_s            : std_logic_vector(15 downto 0);
   signal v16_VidVBPorch_s          : std_logic_vector(15 downto 0);
   
   -- Video Synchronization Signals
   signal RdVideoHBlank_s           : std_logic;
   signal RdVideoVBlank_s           : std_logic;
   signal RdVideoHSync_s            : std_logic;
   signal RdVideoVSync_s            : std_logic;
   signal RdVideoDe_s               : std_logic;
   signal RdVideoDeA1_s             : std_logic; -- 1 cycle in advance of VideoDe_s

   -- Data Request strobe (1 cycle in advance of synchronization signals)
   signal v_RdVideoHCount_s         : std_logic_vector(HWidth_c-1 downto 0);
   signal v_RdVideoVCount_s         : std_logic_vector(VWidth_c-1 downto 0);
-- signal RdVideoPixelRequest_s     : std_logic;

   --
   -- Color Bar Generator
   --
   
   component ColorBarGen
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
   end component;

   signal ColorBarValid_s           : std_logic;
   signal v8_ColorBarRed_s          : std_logic_vector(7 downto 0);
   signal v8_ColorBarGreen_s        : std_logic_vector(7 downto 0);
   signal v8_ColorBarBlue_s         : std_logic_vector(7 downto 0);
   
   --
   -- Vsync Polarity Detection
   --

   signal vsync_polarity            : std_logic;

begin

  --USER logic implementation added here

  ------------------------------------------
  -- Example code to read/write user logic slave model s/w accessible registers
  -- 
  -- Note:
  -- The example code presented here is to show you one way of reading/writing
  -- software accessible registers implemented in the user logic slave model.
  -- Each bit of the Bus2IP_WrCE/Bus2IP_RdCE signals is configured to correspond
  -- to one software accessible register by the top level template. For example,
  -- if you have four 32 bit software accessible registers in the user logic,
  -- you are basically operating on the following memory mapped registers:
  -- 
  --    Bus2IP_WrCE/Bus2IP_RdCE   Memory Mapped Register
  --                 "10000000"   C_BASEADDR + 0x00
  --                 "01000000"   C_BASEADDR + 0x04
  --                 "00100000"   C_BASEADDR + 0x08
  --                 "00010000"   C_BASEADDR + 0x0C
  --                 "00001000"   C_BASEADDR + 0x10
  --                 "00000100"   C_BASEADDR + 0x14
  --                 "00000010"   C_BASEADDR + 0x18
  --                 "00000001"   C_BASEADDR + 0x1C
  -- 
  ------------------------------------------
  slv_reg_write_sel <= Bus2IP_WrCE(0 to C_NUM_REG-1);
  slv_reg_read_sel  <= Bus2IP_RdCE(0 to C_NUM_REG-1);
  slv_write_ack     <= Bus2IP_WrCE(0) or Bus2IP_WrCE(1) or Bus2IP_WrCE(2) or Bus2IP_WrCE(3);
  slv_read_ack      <= Bus2IP_RdCE(0) or Bus2IP_RdCE(1) or Bus2IP_RdCE(2) or Bus2IP_RdCE(3);

  -- implement slave model software accessible register(s)
  SLAVE_REG_WRITE_PROC : process( Bus2IP_Clk ) is
  begin

    if Bus2IP_Clk'event and Bus2IP_Clk = '1' then
      if Bus2IP_Reset = '1' then
        slv_reg0 <= (others => '0');
        slv_reg1 <= (others => '0');
        slv_reg2 <= (others => '0');
        slv_reg3 <= (others => '0');
      else
        case slv_reg_write_sel is
          when "1000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg0(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0100" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg1(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0010" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg2(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0001" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg3(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when others => null;
        end case;
      end if;
    end if;

  end process SLAVE_REG_WRITE_PROC;

  -- implement slave model software accessible register(s) read mux
  SLAVE_REG_READ_PROC : process( slv_reg_read_sel ) is
  begin

    case slv_reg_read_sel is
      when "1000" => slv_ip2bus_data <= slv_reg0;
      when "0100" => slv_ip2bus_data <= slv_reg1;
      when "0010" => slv_ip2bus_data <= slv_reg2;
      when "0001" => slv_ip2bus_data <= slv_reg3;
      when others => slv_ip2bus_data <= (others => '0');
    end case;

  end process SLAVE_REG_READ_PROC;

  IP_REG_PROC : process(clk) is
    begin
      if rising_edge(clk) then
        rd_hsync1_reg	<= toLittleEndian(slv_reg0);
        rd_hsync2_reg	<= toLittleEndian(slv_reg1);
        rd_vsync1_reg	<= toLittleEndian(slv_reg2);
        rd_vsync2_reg	<= toLittleEndian(slv_reg3);
    end if;
  end process IP_REG_PROC;

  v16_VidHActive_s  <= rd_hsync1_reg(31 downto 16);
  v16_VidHFPorch_s  <= rd_hsync1_reg(15 downto  0);
  v16_VidHSync_s    <= rd_hsync2_reg(31 downto 16);
  v16_VidHBPorch_s  <= rd_hsync2_reg(15 downto  0);
  v16_VidVActive_s  <= rd_vsync1_reg(31 downto 16);
  v16_VidVFPorch_s  <= rd_vsync1_reg(15 downto  0);
  v16_VidVSync_s    <= rd_vsync2_reg(31 downto 16);
  v16_VidVBPorch_s  <= rd_vsync2_reg(15 downto  0);
   
  ------------------------------------------
  -- Example code to drive IP to Bus signals
  ------------------------------------------
  IP2Bus_Data  <= slv_ip2bus_data when slv_read_ack = '1' else
                  (others => '0');

  IP2Bus_WrAck <= slv_write_ack;
  IP2Bus_RdAck <= slv_read_ack;
  IP2Bus_Error <= '0';


   --
   -- Video Synchronization Generator
   --
   
   VideoSyncGen_l : VideoSyncGen
      generic map (
         HWidth_g                   => HWidth_c,
         VWidth_g                   => VWidth_c
      )
      port map (
         -- Global Reset
         i_Clk_p                    => clk,
         i_Reset_p                  => reset,

         -- Video Configuration
         iv16_VidHActive_p          => v16_VidHActive_s,
         iv16_VidHFPorch_p          => v16_VidHFPorch_s,
         iv16_VidHSync_p            => v16_VidHSync_s,
         iv16_VidHBPorch_p          => v16_VidHBPorch_s,
         --
         iv16_VidVActive_p          => v16_VidVActive_s,
         iv16_VidVFPorch_p          => v16_VidVFPorch_s,
         iv16_VidVSync_p            => v16_VidVSync_s,
         iv16_VidVBPorch_p          => v16_VidVBPorch_s,
         
         -- Video Synchronization Signals
         o_HBlank_p                 => RdVideoHBlank_s,
         o_VBlank_p                 => RdVideoVBlank_s,
         o_HSync_p                  => RdVideoHSync_s,
         o_VSync_p                  => RdVideoVSync_s,
         o_De_p                     => RdVideoDe_s,

         -- Data Request strobe (1 cycle in advance of synchronization signals)
         ov_HCount_p                => v_RdVideoHCount_s,
         ov_VCount_p                => v_RdVideoVCount_s,
         o_PixelRequest_p           => RdVideoDeA1_s
      );


   --
   -- Color Bar Generator
   --

   PIXELS_FROM_COLORBARGEN : if ( C_GEN_RD_VDMA = 0 ) generate
      ColorBarGen_l : ColorBarGen
      generic map (
         HWidth_g                   => HWidth_c,
         VWidth_g                   => VWidth_c
      )
      port map (
         -- Global Reset
         i_clk_p                    => clk,
         i_Reset_p                  => reset,
         
         -- Image Size
         iv_HActive_p               => v16_VidHActive_s,
         iv_VActive_p               => v16_VidVActive_s,

         -- Data Request strobe (1 cycle in advance of synchronization signals)
         iv_HCount_p                => v_RdVideoHCount_s,
         iv_VCount_p                => v_RdVideoVCount_s,
         i_PixelRequest_p           => RdVideoDeA1_s,
         
         -- Pixel Output
         o_PixelValid_p             => ColorBarValid_s,
         ov8_RPixel_p               => v8_ColorBarRed_s,
         ov8_GPixel_p               => v8_ColorBarGreen_s,
         ov8_BPixel_p               => v8_ColorBarBlue_s
      );
   end generate PIXELS_FROM_COLORBARGEN;

   --
   -- VDMA Read Port
   --

 --vdma_rcmd_clk             <= clk;
   vdma_rd_clk               <= clk;
   vdma_rd_read              <= RdVideoDeA1_s;

   PIXELS_FROM_RD_VDMA : if ( C_GEN_RD_VDMA = 1 ) generate
      VDMA_DATA_8BIT_GEN : if (C_VDMA_DATA_WIDTH = 8) generate
         v8_ColorBarRed_s           <= X"00";
         v8_ColorBarGreen_s         <= vdma_rd_data( 7 downto  0);
         v8_ColorBarBlue_s          <= X"00";
      end generate VDMA_DATA_8BIT_GEN;
      VDMA_DATA_16BIT_GEN : if (C_VDMA_DATA_WIDTH = 16) generate
         v8_ColorBarRed_s           <= X"00";
         v8_ColorBarGreen_s         <= vdma_rd_data( 7 downto  0);
         v8_ColorBarBlue_s          <= vdma_rd_data(15 downto  8);
      end generate VDMA_DATA_16BIT_GEN;
      VDMA_DATA_32BIT_GEN : if (C_VDMA_DATA_WIDTH = 32) generate
         v8_ColorBarRed_s           <= vdma_rd_data(23 downto 16);
         v8_ColorBarGreen_s         <= vdma_rd_data( 7 downto  0);
         v8_ColorBarBlue_s          <= vdma_rd_data(15 downto  8);
      end generate VDMA_DATA_32BIT_GEN;
   end generate PIXELS_FROM_RD_VDMA;
   
   --
   -- Camera Port
   -- 

   CAMERA_OPORT_GEN : if (C_VIDEO_INTERFACE = 0) generate
      CAMERA_8BIT_GEN : if (C_XSVI_DATA_WIDTH = 8) generate
         camera_8bit_oregs_l : process (clk)
         begin
            if rising_edge( clk ) then
               camera_frame_valid_o <= RdVideoVSync_s;
               camera_line_valid_o  <= RdVideoDe_s;
               camera_data_o        <= v8_ColorBarRed_s;
            end if;
         end process;
      end generate CAMERA_8BIT_GEN;
      CAMERA_10BIT_GEN : if (C_XSVI_DATA_WIDTH = 10) generate
         camera_10bit_oregs_l : process (clk)
         begin
            if rising_edge( clk ) then
               camera_frame_valid_o <= RdVideoVSync_s;
               camera_line_valid_o  <= RdVideoDe_s;
               camera_data_o        <= v8_ColorBarRed_s & "00";
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
            dvi_vsync_o <= RdVideoVSync_s;
            dvi_hsync_o <= RdVideoHSync_s;
            dvi_de_o    <= RdVideoDe_s;
            dvi_red_o   <= v8_ColorBarRed_s;
            dvi_green_o <= v8_ColorBarGreen_s;
            dvi_blue_o  <= v8_ColorBarBlue_s;
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
      XSVI_8BIT_GEN : if (C_XSVI_DATA_WIDTH = 8) generate
         xsvi_8bit_oregs_l : process (clk)
            begin
            if rising_edge( clk ) then
               xsvi_vsync_o        <= RdVideoVSync_s;
               xsvi_hsync_o        <= RdVideoHSync_s;
               xsvi_vblank_o       <= RdVideoVBlank_s;
               xsvi_hblank_o       <= RdVideoHBlank_s;
               xsvi_active_video_o <= RdVideoDe_s;
               xsvi_video_data_o   <= v8_ColorBarRed_s;
            end if;
         end process;
      end generate XSVI_8BIT_GEN;
      XSVI_10BIT_GEN : if (C_XSVI_DATA_WIDTH = 10) generate
         xsvi_10bit_oregs_l : process (clk)
            begin
            if rising_edge( clk ) then
               xsvi_vsync_o        <= RdVideoVSync_s;
               xsvi_hsync_o        <= RdVideoHSync_s;
               xsvi_vblank_o       <= RdVideoVBlank_s;
               xsvi_hblank_o       <= RdVideoHBlank_s;
               xsvi_active_video_o <= RdVideoDe_s;
               xsvi_video_data_o   <= v8_ColorBarRed_s & "00";
            end if;
         end process;
      end generate XSVI_10BIT_GEN;
      XSVI_16BIT_GEN : if (C_XSVI_DATA_WIDTH = 16) generate
         xsvi_16bit_oregs_l : process (clk)
            begin
            if rising_edge( clk ) then
               xsvi_vsync_o        <= RdVideoVSync_s;
               xsvi_hsync_o        <= RdVideoHSync_s;
               xsvi_vblank_o       <= RdVideoVBlank_s;
               xsvi_hblank_o       <= RdVideoHBlank_s;
               xsvi_active_video_o <= RdVideoDe_s;
               xsvi_video_data_o   <= v8_ColorBarBlue_s & v8_ColorBarGreen_s;
            end if;
         end process;
      end generate XSVI_16BIT_GEN;
      XSVI_24BIT_GEN : if (C_XSVI_DATA_WIDTH = 24) generate
         xsvi_24bit_oregs_l : process (clk)
            begin
            if rising_edge( clk ) then
               xsvi_vsync_o        <= RdVideoVSync_s;
               xsvi_hsync_o        <= RdVideoHSync_s;
               xsvi_vblank_o       <= RdVideoVBlank_s;
               xsvi_hblank_o       <= RdVideoHBlank_s;
               xsvi_active_video_o <= RdVideoDe_s;
               xsvi_video_data_o   <= v8_ColorBarRed_s & v8_ColorBarBlue_s & v8_ColorBarGreen_s;
            end if;
         end process;
      end generate XSVI_24BIT_GEN;
      XSVI_32BIT_GEN : if (C_XSVI_DATA_WIDTH = 32) generate
         xsvi_24bit_oregs_l : process (clk)
            begin
            if rising_edge( clk ) then
               xsvi_vsync_o        <= RdVideoVSync_s;
               xsvi_hsync_o        <= RdVideoHSync_s;
               xsvi_vblank_o       <= RdVideoVBlank_s;
               xsvi_hblank_o       <= RdVideoHBlank_s;
               xsvi_active_video_o <= RdVideoDe_s;
               xsvi_video_data_o   <= "00000000" & v8_ColorBarRed_s & v8_ColorBarBlue_s & v8_ColorBarGreen_s;
            end if;
         end process;
      end generate XSVI_32BIT_GEN;
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
   -- Vsync Polarity Detection
   --

   vsync_polarity_l : process (clk)
   begin
      if rising_edge( clk ) then
         if ( RdVideoDe_s = '1' ) then
            vsync_polarity   <= not RdVideoVSync_s;
         end if;
      end if;
   end process;

   --
   -- Frame Sync Output Port
   --

   fsync_l : process (clk)
   begin
      if rising_edge( clk ) then
         if ( vsync_polarity = '1' ) then
            fsync_o          <= RdVideoVSync_s;
         else
            fsync_o          <= not RdVideoVSync_s;
         end if;
      end if;
   end process;
   
end rtl;
