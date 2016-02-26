-------------------------------------------------------------------------------
-- Entity: cpu_ctrl
-- Author: Waj
-------------------------------------------------------------------------------
-- Description:
-- Control unit without instruction pipelining for the RISC-CPU of the
-- von-Neuman MCU.
-------------------------------------------------------------------------------
-- Total # of FFs: ... tbd ...
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.mcu_pkg.all;

entity cpu_ctrl is
  port(rst      : in std_logic;
       clk      : in std_logic;
       -- bus interface signals
       data_in  : in std_logic_vector(DW-1 downto 0);
       addr     : out std_logic_vector(AW-1 downto 0);
       data_out : out std_logic_vector(DW-1 downto 0);
       wr_enb   : out std_logic;
       rd_enb   : out std_logic;
       -- CPU internal interfaces
       reg_in   : in  t_reg2ctr;
       reg_out  : out t_ctr2reg;
       prc_in   : in  t_prc2ctr;
       prc_out  : out t_ctr2prc;
       alu_in   : in  t_alu2ctr;
       alu_out  : out t_ctr2alu
       );
end cpu_ctrl;

architecture rtl of cpu_ctrl is

  -- FSM signals
  type state is (s_if, s_id, s_ex, s_ma, s_rw);
  signal c_st, n_st : state;
  -- Instruction register & decoding
  signal instr_reg : std_logic_vector(DW-1 downto 0);
  signal instr_enb : std_logic;
  signal opcode    : natural range 0 to 2**OPCW-1;
  
begin

  -----------------------------------------------------------------------------
  -- Bus Interface
  -----------------------------------------------------------------------------
  data_out <= reg_in.data;

  -----------------------------------------------------------------------------
  -- Register Block Interface
  -----------------------------------------------------------------------------
  reg_out.data <= data_in;

  -----------------------------------------------------------------------------
  -- PC Interface
  -----------------------------------------------------------------------------
  prc_out.addr <= instr_reg(AW-1 downto 0); 
  
  -----------------------------------------------------------------------------
  -- Instruction register 
  -----------------------------------------------------------------------------
  P_ir: process(clk)
  begin
    if rising_edge(clk) then
      -- instruction register
      if instr_enb = '1' then
        instr_reg <= data_in;
      end if;
    end if;
  end process;
  -- Instruction register decoding
  opcode       <= to_integer(unsigned(instr_reg(DW-1 downto DW-OPCW)));  
  alu_out.op   <= instr_reg(DW-1-(OPCW-OPAW) downto DW-OPCW);
  alu_out.imm  <= instr_reg(IOWW-1 downto 0);
  reg_out.dest <= instr_reg(10 downto 8);
  reg_out.src1 <= instr_reg(10 downto 8) when (opcode = 12 or opcode = 13) else
                  instr_reg( 7 downto 5);
  reg_out.src2 <= instr_reg( 4 downto 2);

  -----------------------------------------------------------------------------
  -- FSM: Mealy-type
  -----------------------------------------------------------------------------
  -- memoryless process
  p_fsm_com: process (c_st, opcode, alu_in, reg_in, prc_in)
  begin
    -- default assignments for all outputs
    n_st                  <= c_st; -- remain in current state
    rd_enb                <= '0';  
    wr_enb                <= '0';  
    instr_enb             <= '0';
    reg_out.enb_res       <= '0';
    reg_out.enb_data_low  <= '0';  
    reg_out.enb_data_high <= '0';
    alu_out.enb           <= '0';
    prc_out.enb           <= '0';
    prc_out.mode          <= linear;
    addr                  <= (others => '1');  -- reset vector
    -- specific assignments
    case c_st is
      when s_if =>
        -- instruction fetch
        if prc_in.exc = no_err then
          -- normal fetch if no exception, otherwise go to reset vector
          addr <= prc_in.pc;
        end if;
        n_st <= s_id;
      when s_id =>
        -- instruction decode
        instr_enb <= '1';
        n_st      <= s_ex;
      when s_ex =>
        -- instruction execute
        if opcode <= 7 or opcode = 12 or opcode = 13 then
          -- reg/reg-instruction or addil/h instruction
          -- increase PC, store result/flags from ALU, start next instr. cycle 
          prc_out.enb     <= '1';  
          reg_out.enb_res <= '1';  
          alu_out.enb     <= '1';
          n_st            <= s_if; 
        elsif opcode = 17 then
          -- To be continued.... !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
          wr_enb <= '1'; -- temporal, to avoid optimizations. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        else
          -- NOP instruction
          prc_out.enb  <= '1';  
          n_st         <= s_if;        
        end if;
      when s_ma =>
        -- memory access
        n_st <= s_rw;
      when s_rw =>
        -- register write-back
        n_st <= s_if;
      when others =>
        n_st <= s_if; -- handle parasitic states
    end case;
  end process;
  ----------------------------------------------------------------------------- 
  -- sequential process
  -- # of FFs: 3 (assuming binary state encoding)
  P_fsm_seq: process(rst, clk)
  begin
    if rst = '1' then
      c_st <= s_if;
    elsif rising_edge(clk) then
      c_st <= n_st;
    end if;
  end process;

    
end rtl;
