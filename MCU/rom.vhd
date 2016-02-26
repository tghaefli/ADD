-------------------------------------------------------------------------------
-- Entity: rom
-- Author: Waj
-- Date  : 11-May-13, 26-May-13
-------------------------------------------------------------------------------
-- Description: (ECS Uebung 9)
-- Program memory for simple von-Neumann MCU with registerd read data output.
-------------------------------------------------------------------------------
-- Total # of FFs: DW
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.mcu_pkg.all;

entity rom is
  port(clk     : in    std_logic;
       -- ROM bus signals
       bus_in  : in  t_bus2ros;
       bus_out : out t_ros2bus
       );
end rom;

architecture rtl of rom is

  type t_rom is array (0 to 2**AWL-1) of std_logic_vector(DW-1 downto 0);
  constant rom_table : t_rom := (
    ---------------------------------------------------------------------------
    -- program code -----------------------------------------------------------
    ---------------------------------------------------------------------------
    -- addr    Opcode     Rdest    Rsrc1    Rsrc2              description
    ---------------------------------------------------------------------------
	 16#00# => OPC(xori)  & reg(4) & reg(1) & reg(0) & "--",		-- r4 = r0 xor r1
	 16#01# => OPC(xori)  & reg(5) & reg(4) & reg(2) & "--",		-- r4 = r4 xor r2
	 16#02# => OPC(xori)  & reg(6) & reg(5) & reg(3) & "--",		-- r4 = r4 xor r3
	 16#03# => OPC(xori)  & reg(7) & reg(6) & reg(0) & "--",		-- r7 = r4 xor r0

    others => OPC(nop)   & "-----------"
    );
  
begin

  -----------------------------------------------------------------------------
  -- sequential process: ROM table with registerd output
  -----------------------------------------------------------------------------  
  P_rom: process(clk)
  begin
    if rising_edge(clk) then
      bus_out.data <= rom_table(to_integer(unsigned(bus_in.addr)));
    end if;
  end process;
  
end rtl;
