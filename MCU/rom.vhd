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
    -- addr  Opcode       Rdest    Rsrc1    Rsrc2              description
    ---------------------------------------------------------------------------
    -- Flag-testing with ADD/SUB commands
    16#0# => OPC(ld)    & reg(4) & reg(0) & "-----",            -- ld r4, r0
    16#1# => OPC(ld)    & reg(5) & reg(1) & "-----",            -- ld r5, r1
    16#2# => OPC(ld)    & reg(6) & reg(2) & "-----",            -- ld r6, r2
    16#3# => OPC(ld)    & reg(7) & reg(3) & "-----",            -- ld r7, r3
    16#4# => OPC(add)   & reg(0) & reg(5) & reg(4) & "--",      -- add r0, r5, r4
    16#5# => OPC(st)    & reg(0) & reg(1) & "-----",            -- st r0, r1
    16#6# => OPC(sub)   & reg(0) & reg(5) & reg(4) & "--",      -- sub r0, r5, r4
    16#7# => OPC(st)    & reg(0) & reg(2) & "-----",            -- st r0, r2
    16#8# => OPC(add)   & reg(0) & reg(7) & reg(6) & "--",      -- add r0, r7, r6
    16#9# => OPC(st)    & reg(0) & reg(3) & "-----",            -- st r0, r3
    16#A# => OPC(sub)   & reg(0) & reg(7) & reg(6) & "--",      -- sub r0, r7, r6
    16#B# => OPC(addil) & reg(0) & "01000001",                  -- addil r0, 0x41
    16#C# => OPC(st)    & reg(0) & reg(0) & "-----",            -- st r0, r0
    others => OPC(nop)  & "-----------"                         -- NOP
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
