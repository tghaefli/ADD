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
	 
	 
	 
	 OPC(nop)   & "-----------"
	 OPC(setil) & reg(0) & n2slv(16#0A#, DW/2),
	 OPC(setih) & reg(0) & n2slv(16#00#, DW/2),
	 OPC(nop)   & "-----------"
	 OPC(nop)   & "-----------"
	 OPC(addil) & reg(0) & n2slv(16#FF#, DW/2),					-- decrement
	 OPC(bne)   & "---"  & n2slv(16#FD#, DW/2),
	 OPC(jmp)   & "---"  & n2slv(16#01#, DW/2),
	 
	 
	 
	 
    ---------------------------------------------------------------------------
    -- Flag-testing with ADD/SUB commands
    ---------------------------------------------------------------------------
    -- set registers r0...r3 to RAM addresses 0x00...0x03
    -- (only low-byte needed, high-byte for testing)
    OPC(setil) & reg(0) & n2slv(16#40#, DW/2),         -- setil r0, 0x40
    OPC(setih) & reg(0) & n2slv(16#80#, DW/2),         -- setih r0, 0x80
    OPC(setil) & reg(1) & n2slv(16#41#, DW/2),         -- setil r1, 0x41
    OPC(setih) & reg(1) & n2slv(16#81#, DW/2),         -- setih r1, 0x81
    OPC(setil) & reg(2) & n2slv(16#42#, DW/2),         -- setil r2, 0x42
    OPC(setih) & reg(2) & n2slv(16#82#, DW/2),         -- setih r2, 0x82
    OPC(setil) & reg(3) & n2slv(16#43#, DW/2),         -- setil r3, 0x43
    OPC(setih) & reg(3) & n2slv(16#83#, DW/2),         -- setih r3, 0x83
    ---------------------------------------------------------------------------
    -- load operands from RAM addresses 0x00...0x03 into registers r4...r7
    OPC(ld)    & reg(4) & reg(0) & "-----",            -- ld r4, r0
    OPC(ld)    & reg(5) & reg(1) & "-----",            -- ld r5, r1
    OPC(ld)    & reg(6) & reg(2) & "-----",            -- ld r6, r2
    OPC(ld)    & reg(7) & reg(3) & "-----",            -- ld r7, r3
    ---------------------------------------------------------------------------
    -- perform arithmetic operations to force flags being updated
    OPC(add)   & reg(0) & reg(5) & reg(4) & "--",      -- add r0, r5, r4
    OPC(st)    & reg(0) & reg(1) & "-----",            -- st r0, r1
    OPC(sub)   & reg(0) & reg(5) & reg(4) & "--",      -- sub r0, r5, r4
    OPC(st)    & reg(0) & reg(2) & "-----",            -- st r0, r2
    OPC(add)   & reg(0) & reg(7) & reg(6) & "--",      -- add r0, r7, r6
    OPC(st)    & reg(0) & reg(3) & "-----",            -- st r0, r3
    OPC(sub)   & reg(0) & reg(7) & reg(6) & "--",      -- sub r0, r7, r6
    OPC(addil) & reg(0) & n2slv(16#41#, DW/2),         -- addil r0, 0x41
    OPC(st)    & reg(0) & reg(0) & "-----",            -- st r0, r0
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
