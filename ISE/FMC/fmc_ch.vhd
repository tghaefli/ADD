-------------------------------------------------------------------------------
-- Entity: fmc_ch
-- Author: Sandro Arnold
-------------------------------------------------------------------------------
-- Description: Testatbung Floppy Music Controller
-- FMC_CH Channel of Floppy Music Controller
-------------------------------------------------------------------------------
-- Total # of FFs: ... tbd ...
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.mcu_pkg.all;

entity fmc_ch is
  generic(N : natural := 0 -- channel number
			); 
  port( rst     : in    std_logic;
        clk     : in    std_logic;
		    -- FMC_CH FMC_TOP signals
        tick_dur  				: in  std_logic;	--period = 1ms
		    tick_nco				: in  std_logic; 	--period = 1us
        enb		 		 		: in  std_logic;
		    fmc_ch_out_enb		: out std_logic;
        fmc_chn_out_step      : out std_logic;
        fmc_chn_out_dir 		: out std_logic
  );
end fmc_ch;

architecture rtl of fmc_ch is

   -- Address
	signal addr : std_logic_vector(FMC_ROM_AW-1 downto 0);
	signal rom_data : std_logic_vector(FMC_ROM_DW-1 downto 0);

 -- signal duration_cnt, tone_duration: unsigned(FMC_DUR_WW-1 downto 0);
  signal tone_number : std_logic_vector(FMC_TON_WW-1 downto 0);
 
  -- LUT: tone number ==> NCO seed
  type t_nco_lut is array (2**FMC_TON_WW-1 downto 0) of natural;
  constant nco_lut : t_nco_lut := (
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,7382,6968,6577,6207,5859,5530,5220,4927,4650,4389,4143,3910,3691,
    3484,3288,3104,2930,2765,2610,2463,2325,2195,2071,1955,1845,1742,1644,1552,1465,1383,1305,1232,
    1163,1097,1036,978,923,871,822,776,732,691,652,616,581,549,518,489,461,0);
  
  -- Tone oscillator signals
  signal seed    : unsigned(12 downto 0); -- 13 bit seed
  signal osc_cnt : unsigned(23 downto 0); -- 24 bit NCO
  
  -- Step counter signals for changing direction
  signal stp_cnt 	: integer range 0 to 80 := 0;
  -- signal stp_cnt   : unsigned(6 downto 0);  --  7 bit step counter
  signal dir		: std_logic;
  signal stp_log  : std_logic;
  
  -- Wait during tone ist playing signals
  signal wait_cnt			: unsigned(FMC_DUR_WW-1 downto 0);
  signal tone_duration	: unsigned(FMC_DUR_WW-1 downto 0);
  signal next_tone_enb 	:std_logic;

begin

  -- output assignment
  fmc_chn_out_step <= osc_cnt(23);
  fmc_chn_out_dir	 <= dir;
  --fmc_ch_out_enb	 <= enb;  
  fmc_ch_out_enb <= '1' when to_integer(unsigned(tone_number)) = 0 else '0';

  -----------------------------------------------------------------------------
  -- Direction changing
  -----------------------------------------------------------------------------  
  P_dir_change: process(clk, rst)
  begin
    if rst = '1' then
      stp_cnt <= 0;
		dir <= '0';
    elsif rising_edge(clk) then
	 stp_log <= osc_cnt(23);								--rising edge
	 if (stp_log = '0' AND osc_cnt(23) = '1') then	--rising edge
			stp_cnt <= stp_cnt + 1;
	 end if;
	 
	 --if (stp_cnt = 79) then
	 if (stp_cnt = 2) then
			dir <= not dir;
			stp_cnt <= 0;
	 end if;
	end if;
  end process;

  -----------------------------------------------------------------------------
  -- wait during tone is playing 
  -----------------------------------------------------------------------------  
  P_wait: process(clk, rst)
  begin
    if rst = '1' then
      wait_cnt <= (others => '0');
		addr <= (others => '0');
		next_tone_enb <= '0';
    elsif rising_edge(clk) then
		--default assignemt
	  	next_tone_enb <= '0';
		--wait for next tone 
		if tick_dur = '1' then	
            if (wait_cnt = tone_duration-1) then
					 wait_cnt <= (others => '0');  -- decode next tone
					 next_tone_enb <='1';					 
            else
					 wait_cnt <= wait_cnt + 1;
					 --next_tone_enb <='0';
            end if;
		end if;
		
		if tone_duration = FMC_LAST_TONE then
			addr <= (others => '0');
		elsif next_tone_enb = '1' then
				addr <= std_logic_vector(unsigned(addr)+1);
		end if;
    end if;
  end process;

  -----------------------------------------------------------------------------
  -- count address for tone playing next
  -----------------------------------------------------------------------------  
--  P_next_tone: process(rst, clk)
--  begin
--	if rst = '1' then
--		addr <= (others => '0');
--	elsif rising_edge(clk) then	
--		if next_tone_enb = '1' then
--			if tone_duration = FMC_LAST_TONE then
--				-- restart playing from 1st tone
--				addr <= (others => '0');
--			else
--				addr <= std_logic_vector(unsigned(addr)+1);
--			end if;
--		end if;
--    end if;
--  end process;

  -----------------------------------------------------------------------------
  -- Tone frequency Oscillator
  -----------------------------------------------------------------------------  
  P_tone_osc: process(clk, rst)
  begin
    if rst = '1' then
	   seed    <= (others => '0');
      osc_cnt <= (others => '0');
    elsif rising_edge(clk) then
		  if(tick_nco = '1') then		--f_clk_enb = 1MHz
			 seed    <= to_unsigned(nco_lut(to_integer(unsigned(tone_number))),13);
			 osc_cnt <= osc_cnt + seed;
		  end if;
    end if;
  end process;
  
  -----------------------------------------------------------------------------
  -- channel number dependent FMC ROM instance
  -----------------------------------------------------------------------------  
  rom : entity work.fmc_rom
  generic map(N => N)
    port map (clk  => clk,
              addr => addr,
              data => rom_data
              );
				  
  tone_duration <= unsigned(rom_data(FMC_DUR_WW+FMC_TON_WW-1 downto FMC_TON_WW));
  tone_number   <= rom_data(FMC_TON_WW-1 downto 0);

end rtl;
