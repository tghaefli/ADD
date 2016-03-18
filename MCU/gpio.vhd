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

  -- Relative Register Addresses
  constant c_addr_gpio_data_in  : std_logic_vector(AWL-1 downto 0) := n2slv( 0, AWL);
  constant c_addr_gpio_data_out : std_logic_vector(AWL-1 downto 0) := n2slv( 1, AWL);
  constant c_addr_gpio_out_enb  : std_logic_vector(AWL-1 downto 0) := n2slv( 2, AWL);
  type t_gpio_addr_sel is (none, gpio_data_in, gpio_data_out, gpio_enb);
  -- address select signal
  signal addr_sel : t_gpio_addr_sel;
  -- peripheral registers
  signal data_in_reg  : std_logic_vector(DW-1 downto 0);
  signal data_out_reg : std_logic_vector(DW-1 downto 0);
  signal out_enb_reg  : std_logic_vector(DW-1 downto 0);
  
begin

  -----------------------------------------------------------------------------
  -- Adress Decoding (combinationally)
  -----------------------------------------------------------------------------  
  process(bus_in.addr)
  begin
    case bus_in.addr is
      -- Port 1 addresses -----------------------------------------------------
      when c_addr_gpio_data_in  => addr_sel <= gpio_data_in;
      when c_addr_gpio_data_out => addr_sel <= gpio_data_out;
      when c_addr_gpio_out_enb  => addr_sel <= gpio_enb;
      -- unused addresses -----------------------------------------------------
      when others               => addr_sel <= none;
    end case;       
  end process;

  -----------------------------------------------------------------------------
  -- Read Access
  -----------------------------------------------------------------------------  
  P_read: process(clk)
  begin
    if rising_edge(clk) then
      -- default assignment
      bus_out.data <= (others => '0');
      -- use address select signal
      case addr_sel is
        when gpio_data_in  => bus_out.data <= data_in_reg;
        when gpio_data_out => bus_out.data <= data_out_reg;
        when gpio_enb      => bus_out.data <= out_enb_reg;
        when others        => null;
      end case;       
    end if;
  end process;

  -----------------------------------------------------------------------------
  -- ToDo...........................
  -----------------------------------------------------------------------------  
  --P_dummy: process(rst, clk)
  --begin
  --  if rst = '1' then
  --    bus_out.data <= (others => '0');
  --  elsif rising_edge(clk) then
  --    if bus_in.wr_enb = '1' then
  --      if unsigned(bus_in.addr) >= 0 then
  --        bus_out.data  <= gpio_in;
  --        gpio_out      <= bus_in.data;
  --        gpio_out_enb  <= bus_in.data;
  --      end if;
  --    end if;
  --  end if;
  --end process;

end rtl;
