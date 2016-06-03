-------------------------------------------------------------------------------
-- Entity: fmc_rom
-- Author: Waj
-------------------------------------------------------------------------------
-- Description:
-- ROM for Floppy-Music Controller (channel-dependent content)
-- NOTE:
-- Since XST does not support the 'val attribute, the following cannot be used
-- to form the channel-number dependent MIF file name:
-- "fmc_rom_" & character'val(N+48) & ".mif"
-- As a workaround, a wrapper unit with conditional generate statements is
-- used. 
-------------------------------------------------------------------------------
-- Total # of FFs: FMC_ROM_DW
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-- FMC ROM core unit
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use std.textio.all;
use work.mcu_pkg.all;

entity fmc_rom_core is
  generic(MIF : string := "rom.mif" -- ROM init file
          ); 
  port(clk  : in std_logic;
       addr : in  std_logic_vector(FMC_ROM_AW-1 downto 0);
       data : out std_logic_vector(FMC_ROM_DW-1 downto 0)
       );
end fmc_rom_core;

architecture rtl of fmc_rom_core is

  type t_rom is array (0 to 2**FMC_ROM_AW-1) of std_logic_vector(FMC_ROM_DW-1 downto 0);

  impure function f_assign_mif(file_name : in string) return t_rom is       
     FILE     f : text open read_mode is file_name;                   
     variable l : line;
     variable s : string(FMC_ROM_DW downto 1);
     variable r : t_rom;                                      
  begin                                                        
    for i in t_rom'range loop
      if not endfile(f) then
        -- Note: The last row in .mif should have no CR
        readline(f,l);                             
        read(l,s);
        for k in s'range loop
          if s(k) = '1' then
            r(i)(k-1) := '1';
          else
            r(i)(k-1) := '0';
          end if;
        end loop;
      end if;
    end loop;                                                    
    return r;                                                  
  end function;

  signal rom_table : t_rom := f_assign_mif(MIF);
  signal data_reg  : std_logic_vector(FMC_ROM_DW-1 downto 0);

begin

  -----------------------------------------------------------------------------
  -- Behavioral description of ROM with latency of 2 cc
  -----------------------------------------------------------------------------  
  P_rom: process(clk)
  begin
    if rising_edge(clk) then
      data_reg <= rom_table(to_integer(unsigned(addr)));
      data     <= data_reg;
    end if;
  end process;

end rtl;


-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-- Wrapper Unit (workaround)
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.mcu_pkg.all;

entity fmc_rom is
  generic(N : natural := 0 -- channel number
          ); 
  port(clk  : in std_logic;
       addr : in  std_logic_vector(FMC_ROM_AW-1 downto 0);
       data : out std_logic_vector(FMC_ROM_DW-1 downto 0)
       );
end fmc_rom;

architecture rtl of fmc_rom is

begin
  -- ROM 0 ------------------------------------
  rom_0: if N = 0 generate
    rom_core : entity work.fmc_rom_core
      generic map(MIF => "fmc_rom_0.mif")
      port map (clk  => clk,
                addr => addr,
                data => data
                );
  end generate;
  -- ROM 1 ------------------------------------
  rom_1: if N = 1 generate
    rom_core : entity work.fmc_rom_core
      generic map(MIF => "fmc_rom_1.mif")
      port map (clk  => clk,
                addr => addr,
                data => data
                );
  end generate;
  -- ROM 2 ------------------------------------
  rom_2: if N = 2 generate
    rom_core : entity work.fmc_rom_core
      generic map(MIF => "fmc_rom_2.mif")
      port map (clk  => clk,
                addr => addr,
                data => data
                );
  end generate;
  -- ROM 3 ------------------------------------
  rom_3: if N = 3 generate
    rom_core : entity work.fmc_rom_core
      generic map(MIF => "fmc_rom_3.mif")
      port map (clk  => clk,
                addr => addr,
                data => data
                );
  end generate;
  -- ROM 4 ------------------------------------
  rom_4: if N = 4 generate
    rom_core : entity work.fmc_rom_core
      generic map(MIF => "fmc_rom_4.mif")
      port map (clk  => clk,
                addr => addr,
                data => data
                );
  end generate;
  -- ROM 5 ------------------------------------
  rom_5: if N = 5 generate
    rom_core : entity work.fmc_rom_core
      generic map(MIF => "fmc_rom_5.mif")
      port map (clk  => clk,
                addr => addr,
                data => data
                );
  end generate;
  -- ROM 6 ------------------------------------
  rom_6: if N = 6 generate
    rom_core : entity work.fmc_rom_core
      generic map(MIF => "fmc_rom_6.mif")
      port map (clk  => clk,
                addr => addr,
                data => data
                );
  end generate;
  -- ROM 7 ------------------------------------
  rom_7: if N = 7 generate
    rom_core : entity work.fmc_rom_core
      generic map(MIF => "fmc_rom_7.mif")
      port map (clk  => clk,
                addr => addr,
                data => data
                );
  end generate;

end rtl;
