The Memory Initialization Files (.mif) in this folder can be used for testing.
###############################################################################

===============================================================================
Simulation
===============================================================================

fmc_rom_0.mif 
#############
This file specifies 4 tones of high frequency and short durations, such that the
step/direction outputs can be observed toggling in simuation. The 5th tone specifies
EOF (wraparound of address).
In simulation 300 ms must be simulated to see the first changing on the direction output.

fmc_rom_1.mif
#############
Similar to fmc_rom_0.mif but with slighly higher tone frequencies, such that the
direction output can be seen to toggle sooner.


===============================================================================
HW Testing
===============================================================================

fmc_rom_3a.mif
#############
The first  enttries are as follows
0: 00010000000000110000  # 1 sec tone 48 (415,3 Hz)
1: 00010000000000100000  # 1 sec tone 32 (164,8 Hz)
2: 00100000000000000000  # 2 sec pause
3: 00010000000000001000  # 1 sec tone 16 (65,4 Hz)
4: 00010000000000000010  # 1 sec tone  2 (29,1 Hz) 
5: 11111111111111111111  # EOF (wraparound)
The outputs step/direction/enable of FMC channel 3 can be measuread with an LA
on connecter J4 of the S3E-Board.

fmc_rom_3b.mif
#############
Endless tone of 165 Hz (Tone number 32)

fmc_rom_3c.mif
#############
Endless tone of 440 Hz (Kammerton a, number 49)
