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
    OPC(nop)   & "-----------",                        -- NOP
    -- while-execution = for-loop init
    OPC(setil) & reg(0) & n2slv(16#0A#, DW/2),         -- setil r0, 0x0A
    OPC(setih) & reg(0) & n2slv(16#00#, DW/2),         -- setih r0, 0x00
    -- for-loop execution
    OPC(nop)   & "-----------",                        -- NOP
    OPC(nop)   & "-----------",                        -- NOP
    -- for-loop condition
    OPC(addil) & reg(0) & n2slv(16#FF#, DW/2),         -- addil r0, 0xFF
    OPC(bne)   & "---" & n2slv(16#FD#, DW/2),          -- bne 0xFC
    -- while-condition == 1
    OPC(jmp)   & "---" & n2slv(16#01#, DW/2),          -- jmp 0x01
    ---------------------------------------------------------------------------
    others => OPC(nop)  & "-----------"                -- NOP
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
