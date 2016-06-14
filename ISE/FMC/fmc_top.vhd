-------------------------------------------------------------------------------
-- Entity: fmc_top
-- Author: Sandro Arnold
-------------------------------------------------------------------------------
-- Description: Testatbung FMC Controller
-- FMC_TOP Top Level Entity of Floppy Music Controller
-------------------------------------------------------------------------------
-- Total # of FFs: ... tbd ...
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.mcu_pkg.all;

entity fmc_top is
  port(rst     : in    std_logic;
       clk     : in    std_logic;
       -- FMC_TOP bus signals
       bus_in  : in  t_bus2rws;
       bus_out : out t_rws2bus;
       -- FMC_TOP pin signals
       fmc_top_out_enb		: out std_logic_vector(N_FMC-1 downto 0);
       fmc_top_out_step    : out std_logic_vector(N_FMC-1 downto 0);
       fmc_top_out_dir 		: out std_logic_vector(N_FMC-1 downto 0)
       );
end fmc_top;

architecture rtl of fmc_top is

  -- address select signal
  signal addr_sel : t_fmc_addr_sel;
  
  -- prescaler signals
  signal tick_dur  : std_logic;
  signal tick_nco  : std_logic;
  signal dur_cnt 	: integer range 0 to DUR_SCALE/2 := 0; -- toggling frequency = 2*f_tick_dur
  signal nco_cnt 	: integer range 0 to NCO_SCALE/2 := 0; -- toggling frequency = 2*f_tick_nco
  -- peripheral registers
  signal chn_enb_reg  	: std_logic_vector(DW-1 downto 0);
  signal spd_fac_reg 	: std_logic_vector(DW-1 downto 0);
 
begin

  -----------------------------------------------------------------------------
  -- Instantiation of top-level components (assumed to be in library work)
  -----------------------------------------------------------------------------
  
 -- FMC_CH ---------------------------------------------------------------------
  gen_i_fmc_ch: for k in 0 to N_FMC-1 generate	 
	  i_fmc_ch: entity work.fmc_ch
		 generic map(N => k)
		 port map(
			rst          		=> rst,
			clk          		=> clk,
			enb					=> chn_enb_reg(k),
			tick_dur				=> tick_dur,
			tick_nco				=> tick_nco,
			fmc_ch_out_enb		=> fmc_top_out_enb(k),
			fmc_chn_out_step  => fmc_top_out_step(k),
			fmc_chn_out_dir 	=>	fmc_top_out_dir(k)			
			);  
  end generate gen_i_fmc_ch;

  -----------------------------------------------------------------------------
  -- Address Decoding (combinationally)
  -----------------------------------------------------------------------------  
  process(bus_in.addr)
  begin
    case bus_in.addr is
      -- Port 1 addresses -----------------------------------------------------
      when c_addr_fmc_chn_enb  => addr_sel <= fmc_chn_enb;
      when c_addr_fmc_tmp_ctrl => addr_sel <= fmc_tmp_ctrl;
      -- unused addresses -----------------------------------------------------
      when others              => addr_sel <= none;
    end case;       
  end process;

  -----------------------------------------------------------------------------
  -- Read Access (R and R/W registers)
  -----------------------------------------------------------------------------  
  P_read: process(clk)
  begin
    if rising_edge(clk) then
      -- default assignment
      bus_out.data <= (others => '0');
      -- use address select signal
      case addr_sel is
        when fmc_chn_enb  => bus_out.data <= chn_enb_reg;
        when fmc_tmp_ctrl => bus_out.data <= spd_fac_reg;
        when others        => null;
      end case;       
    end if;
  end process;

  -----------------------------------------------------------------------------
  -- Write Access (R/W regsiters only)
  -----------------------------------------------------------------------------  
  P_write: process(clk, rst)
  begin
    if rst = '1' then
      chn_enb_reg <= (others => '0');
      spd_fac_reg  <= (others => '0');  -- output disabled per default
    elsif rising_edge(clk) then
      if bus_in.wr_enb = '1' then
        -- use address select signal
        case addr_sel is
          when fmc_chn_enb 	=> chn_enb_reg <= bus_in.data;
          when fmc_tmp_ctrl  	=> spd_fac_reg  <= bus_in.data;
          when others        	=> null;
        end case;       
      end if;
    end if;
  end process;
  
  -----------------------------------------------------------------------------
  -- tick_dur
  -----------------------------------------------------------------------------  
    tick_duration: process (rst, clk) begin
        if (rst = '1') then
            tick_dur <= '0';
            dur_cnt <= 0;
        elsif rising_edge(clk) then
            if (tick_dur = '1') then
					tick_dur <= '0';
				end if;
				
				if (dur_cnt = DUR_SCALE-1) then
                tick_dur <= not tick_dur;
					 dur_cnt <= 0;
            else
                dur_cnt <= dur_cnt + 1;
            end if;
        end if;
    end process;
 
   -----------------------------------------------------------------------------
  -- tick_nco
  -----------------------------------------------------------------------------  
    tick_ncoscillator: process (rst, clk) begin
        if (rst = '1') then
            tick_nco <= '0';
            nco_cnt <= 0;
        elsif rising_edge(clk) then
				if (tick_nco = '1') then
					tick_nco <= '0';
				end if;
				
            if (nco_cnt = NCO_SCALE-1) then
                tick_nco <= '1';
					 nco_cnt <= 0;
            else
                nco_cnt <= nco_cnt + 1;
            end if;
        end if;
    end process;
	 
end rtl;
