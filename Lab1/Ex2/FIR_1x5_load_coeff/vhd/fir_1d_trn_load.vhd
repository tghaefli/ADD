-------------------------------------------------------------------------------
-- Company    :  HSLU
-- Engineer   :  Gai, Waj
-- 
-- Create Date:  19-May-11, 21-Mar-14
-- Project    :  RT Video Lab 1: Exercise 2
-- Description:  5-tap FIR filter in transposed form with loadable coefficients
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.numeric_std.all;
use ieee.math_real.all;

entity fir_1d_trn_load is
  generic
    (IN_DW   : integer := 8;            -- Input word width
     OUT_DW  : integer := 19;           -- Output word width
     COEF_DW : integer := 7;            -- coefficient word width
     TAPS    : integer := 5;            -- # of taps + 1 output register
     DELAY   : integer := 8);           -- output delay line
                                        -- (to adapt latency to system architecture)
  port
    (ce_1     : in  std_logic;          -- clock enable
     clk_1    : in  std_logic;          -- clock
     load     : in  std_logic;          -- load coeff pulse
     coef     : in  std_logic_vector(COEF_DW-1 downto 0); 
     din      : in  std_logic_vector(IN_DW-1 downto 0);
     out_data : out std_logic_vector(OUT_DW-1 downto 0)
     );
end fir_1d_trn_load;

architecture Behavioral of fir_1d_trn_load is

  -- type declarations
  type STAGE_TYPE is array(TAPS-1 downto 0) of signed(OUT_DW-1 downto 0);
  type DELAY_TYPE is array(DELAY  downto 0) of signed(IN_DW-1 downto 0);
  type COEFF_TYPE is array(TAPS-1 downto 0) of signed(COEF_DW-1 downto 0);
  
  type COEFF_BUF_TYPE is array(1 downto 0) of COEFF_TYPE;

  -- signal declarations (init values for simulation only!!!)
  signal inreg    : signed(OUT_DW-COEF_DW-1 downto 0) := (others => '0');
  signal stage    : STAGE_TYPE := (others => (others => '0'));
  signal del_line : DELAY_TYPE := (others => (others => '0'));  
  signal coef_reg : COEFF_BUF_TYPE := (others => (others => (others => '0')));
  signal reload_coef, store_coef, load_reg : std_logic;
  signal cnt      : unsigned(integer(log2(real(TAPS-1))) downto 0);
  
begin
  
  -- comb. output assignment (output register already from stage(0))
  out_data <= std_logic_vector(stage(0));

  -- sequential process: 1D FIR filtering
  -- (without reset, because SysGen uses FIR-Compiler without reset signal)
  p0_FIR : process(clk_1)
  begin
    if rising_edge(clk_1) then
      if ce_1 = '1' then
        -- input delay line
        del_line(DELAY)             <= signed(din);
        del_line(DELAY-1 downto 0) <= del_line(DELAY downto 1);
        -- extend width of input sample
        inreg(OUT_DW-COEF_DW-1 downto IN_DW) <= (others => '0');
        inreg(IN_DW-1          downto 0)     <= del_line(0);      
        -- compute filter taps
        stage(TAPS-1) <= inreg * coef_reg(0)(TAPS-1);
        for k in TAPS-2 downto 0 loop
          stage(k) <= (inreg * coef_reg(0)(k)) + stage(k+1);
        end loop;
      end if;
    end if;
  end process;

  -- sequential process: coefficient loading
  -- NOTE: Order of coefficients loaded is b4, b3, ..., b0. 
  p1_Load : process(clk_1)
  begin
    if rising_edge(clk_1) then
      if ce_1 = '1' then
        -- register load input for edge detection
        load_reg <= load;
        -- default asignments
        reload_coef <= '0';
        store_coef  <= '0';
        cnt <= to_unsigned(TAPS-1, integer(log2(real(TAPS-1)))+1);
        -- handle load sequence (implicit, one-hot encoded FSM)
        if load = '1' and load_reg = '0' then
          -- rising edge detected on load, (re-)start load sequence
          reload_coef <= '1';
        elsif reload_coef = '1' then
          -- load sequence ongoing
          coef_reg(1)(to_integer(cnt)) <= signed(coef);
          if cnt = 0 then
            store_coef  <= '1';
          else
           reload_coef <= '1';
           cnt <= cnt - 1;             
          end if;
        elsif store_coef = '1' then
          -- load sequence complete, take over new coefficient set
          coef_reg(0) <= coef_reg(1);
        end if;
      end if;
    end if;
  end process;


 end Behavioral;
