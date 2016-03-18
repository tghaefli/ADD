-------------------------------------------------------------------------------
-- Entity: ram
-- Author: Waj
-------------------------------------------------------------------------------
-- Description: (ECS Uebung 9)
-- GPIO block for simple von-Neumann MCU.
-------------------------------------------------------------------------------
-- Total # of FFs: ... tbd ...
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.mcu_pkg.all;

entity gpio is
  port(rst     : in    std_logic;
       clk     : in    std_logic;
       -- GPIO bus signals
       bus_in  : in  t_bus2rws;
       bus_out : out t_rws2bus;
       -- GPIO pin signals
       gpio_in      : in  std_logic_vector(DW-1 downto 0);
       gpio_out     : out std_logic_vector(DW-1 downto 0);
       gpio_out_enb : out std_logic_vector(DW-1 downto 0)
       );
end gpio;

architecture rtl of gpio is
  
  
begin

  -----------------------------------------------------------------------------
  -- ToDo...........................
  -----------------------------------------------------------------------------  
  P_dummy: process(rst, clk)
  begin
    if rst = '1' then
      bus_out.data <= (others => '0');
    elsif rising_edge(clk) then
      if bus_in.wr_enb = '1' then
        if unsigned(bus_in.addr) >= 0 then
          bus_out.data  <= gpio_in;
          gpio_out      <= bus_in.data;
          gpio_out_enb  <= bus_in.data;
        end if;
      end if;
    end if;
  end process;

end rtl;
