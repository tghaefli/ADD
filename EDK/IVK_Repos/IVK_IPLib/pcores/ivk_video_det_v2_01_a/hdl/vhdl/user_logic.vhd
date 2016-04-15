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
-- Create Date:         Feb 18, 2010
-- Design Name:         IVK
-- Module Name:         ivk_video_det\user_logic.vhd
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
-- Revision:            Feb 18, 2010: 1.01 Initial version
--                      Mar 02, 2010: 1.02 Add optionnal VDMA Write Port
--                      Mar 10, 2010: 1.04 Force FSYNC to active high polarity
--                      Apr 13, 2010: 1.05 Add support for 16bit data width on XSVI input
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
    C_GEN_FSYNC                      : integer              := 0; 
    C_GEN_XSVI_OUT                   : integer              := 1; 
    C_GEN_WD_VDMA                    : integer              := 0; 
    --C_VIDEO_INTERFACE              : integer              := 0; 
    C_XSVII_DATA_WIDTH               : integer              := 24;
    C_XSVIO_DATA_WIDTH               : integer              := 24;
    C_VDMA_DATA_WIDTH                : integer              := 32;
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
      -- XSVI Input Port
      xsvi_vsync_i         : in std_logic;
      xsvi_hsync_i         : in std_logic;
      xsvi_vblank_i        : in std_logic;
      xsvi_hblank_i        : in std_logic;
      xsvi_active_video_i  : in std_logic;
      xsvi_video_data_i    : in std_logic_vector((C_XSVII_DATA_WIDTH-1) downto 0);
      -- XSVI Output Port
      xsvi_vsync_o         : out std_logic;
      xsvi_hsync_o         : out std_logic;
      xsvi_vblank_o        : out std_logic;
      xsvi_hblank_o        : out std_logic;
      xsvi_active_video_o  : out std_logic;
      xsvi_video_data_o    : out std_logic_vector((C_XSVIO_DATA_WIDTH-1) downto 0);
      -- VDMA Write Port
    --vdma_wcmd_clk        : out std_logic;
      vdma_wd_clk          : out std_logic;
      vdma_wd_write        : out std_logic;
      vdma_wd_data         : out std_logic_vector((C_VDMA_DATA_WIDTH-1) downto 0);
      vdma_wd_data_be      : out std_logic_vector(((C_VDMA_DATA_WIDTH/8)-1) downto 0);
      -- Frame Sync Output Port
      fsync_o              : out std_logic;
      -- Debug Ports
      debug1_o             : out std_logic_vector((5+C_XSVII_DATA_WIDTH-1) downto 0);
      debug2_o             : out std_logic_vector(31 downto 0);
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

--  signal dummy1_reg                    : std_logic_vector(31 downto 0);
--  signal dummy2_reg                    : std_logic_vector(31 downto 0);
--  signal dummy3_reg                    : std_logic_vector(31 downto 0);
--  signal dummy4_reg                    : std_logic_vector(31 downto 0);

   --
   -- XSVI Input Registers
   --
   
   signal xsvi_vsync_r                 : std_logic;
   signal xsvi_hsync_r                 : std_logic;
   signal xsvi_vblank_r                : std_logic;
   signal xsvi_hblank_r                : std_logic;
   signal xsvi_active_video_r          : std_logic;
   signal xsvi_video_data_r            : std_logic_vector((C_XSVII_DATA_WIDTH-1) downto 0);
   
   --
   -- Video Dimension Counters
   --

   signal active_video_d1              : std_logic;   
   signal active_video_d2              : std_logic;   
   --
   signal vsync_d1                     : std_logic;   
   signal vsync_d2                     : std_logic;   
   --
   signal width_counter                : unsigned(15 downto 0);
   signal height_counter               : unsigned(15 downto 0);
   signal video_width                  : std_logic_vector(15 downto 0);
   signal video_height                 : std_logic_vector(15 downto 0);

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
--      when "1000" => slv_ip2bus_data <= toBigEndian(X"0000" & video_width);
--      when "0100" => slv_ip2bus_data <= toBigEndian(X"0000" & video_height);
      when "1000" => slv_ip2bus_data <= X"0000" & video_width;
      when "0100" => slv_ip2bus_data <= X"0000" & video_height;
      when "0010" => slv_ip2bus_data <= slv_reg2;
      when "0001" => slv_ip2bus_data <= slv_reg3;
      when others => slv_ip2bus_data <= (others => '0');
    end case;

  end process SLAVE_REG_READ_PROC;

  IP_REG_PROC : process(clk) is
    begin
      if rising_edge(clk) then
--        dummy1_reg	<= toLittleEndian(slv_reg0);
--        dummy2_reg	<= toLittleEndian(slv_reg1);
--        dummy3_reg	<= toLittleEndian(slv_reg2);
--        dummy4_reg	<= toLittleEndian(slv_reg3);
    end if;
  end process IP_REG_PROC;

   
  ------------------------------------------
  -- Example code to drive IP to Bus signals
  ------------------------------------------
  IP2Bus_Data  <= slv_ip2bus_data when slv_read_ack = '1' else
                  (others => '0');

  IP2Bus_WrAck <= slv_write_ack;
  IP2Bus_RdAck <= slv_read_ack;
  IP2Bus_Error <= '0';


   --
   -- XSVI Input Registers
   -- 

   xsvi_iregs_l : process (clk)
   begin
      if rising_edge( clk ) then
         xsvi_vsync_r        <= xsvi_vsync_i;
         xsvi_hsync_r        <= xsvi_hsync_i;
         xsvi_vblank_r       <= xsvi_vblank_i;
         xsvi_hblank_r       <= xsvi_hblank_i;
         xsvi_active_video_r <= xsvi_active_video_i;
         xsvi_video_data_r   <= xsvi_video_data_i;
      end if;
   end process;
   
   --
   -- Video Dimension Counters
   --
   
   video_det_l : process (clk, reset)
   begin
      if ( reset = '1' ) then
         active_video_d1     <= '0'; 
         active_video_d2     <= '0'; 
         --
         vsync_d1            <= '0'; 
         vsync_d2            <= '0'; 
         --
         width_counter       <= (others => '0');
         height_counter      <= (others => '0');
         video_width         <= (others => '0');
         video_height        <= (others => '0');
      elsif rising_edge( clk ) then
      
         -- Horizontal Counter
         --    - increment during active_video
         --    - latch result and clear at falling edge of active_video
         active_video_d1     <= xsvi_active_video_r;
         active_video_d2     <= active_video_d1;
         if ( xsvi_active_video_r = '1' ) then
            width_counter    <= width_counter + 1;
         end if;
         if ( active_video_d1 = '0' and active_video_d2 = '1' ) then
            video_width      <= std_logic_vector(width_counter);
            width_counter    <= (others => '0');
         end if;

         -- Vertical Counter
         --    - increment at falling edge of active_video
         --    - latch result and clear at rising_edge of vsync
         vsync_d1            <= xsvi_vsync_r;
         vsync_d2            <= vsync_d1;
         if ( active_video_d1 = '0' and active_video_d2 = '1' ) then
            height_counter   <= height_counter + 1;
         end if;
         if ( vsync_d1 = '1' and vsync_d2 = '0' ) then
            video_height     <= std_logic_vector(height_counter);
            height_counter   <= (others => '0');
         end if;
         
      end if;
   end process;

   --
   -- XSVI Output Port
   -- 

   xsvi_output_l : process (clk)
   begin
      if rising_edge( clk ) then
         -- default values
         xsvi_video_data_o   <= (others => '0');

         xsvi_vsync_o        <= xsvi_vsync_r;
         xsvi_hsync_o        <= xsvi_hsync_r;
         xsvi_vblank_o       <= xsvi_vblank_r;
         xsvi_hblank_o       <= xsvi_hblank_r;
         xsvi_active_video_o <= xsvi_active_video_r;
         xsvi_video_data_o(C_XSVII_DATA_WIDTH-1 downto 0)
                             <= xsvi_video_data_r;
      end if;
   end process;
   

   --
   -- VDMA Write Port
   --

 --vdma_wcmd_clk             <= clk;
   vdma_wd_clk               <= clk;

   vdma_write_l : process (clk)
   begin
      if rising_edge( clk ) then
         -- default values
         vdma_wd_data        <= (others => '0');

         vdma_wd_write       <= xsvi_active_video_r;
         vdma_wd_data(C_XSVII_DATA_WIDTH-1 downto 0)
                             <= xsvi_video_data_r; 
         vdma_wd_data_be     <= (others => '1');
      end if;
   end process;

   --
   -- Vsync Polarity Detection
   --

   vsync_polarity_l : process (clk)
   begin
      if rising_edge( clk ) then
         if ( xsvi_active_video_r = '1' ) then
            vsync_polarity   <= not xsvi_vsync_r;
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
            fsync_o          <= xsvi_vsync_r;
         else
            fsync_o          <= not xsvi_vsync_r;
         end if;
      end if;
   end process;

   --
   -- Debug Ports
   --

   debug_l : process (clk)
   begin
      if rising_edge( clk ) then
         debug1_o               <= xsvi_vsync_r & xsvi_hsync_r &
                                   xsvi_vblank_r & xsvi_hblank_r & 
                                   xsvi_active_video_r &
                                   xsvi_video_data_r;
         debug2_o(31 downto 16) <= std_logic_vector(width_counter);
         debug2_o(15 downto  0) <= std_logic_vector(height_counter);
      end if;
   end process;
   
end rtl;
