% This script can be used to convert data for one MIDI channel perpared in csv
% format into a .mif file for ROM initialization.
% NOTE: The CR at the end of the last line in the generated .mif file
%       must be removed manually!!
%
% .csv format: col_1        col_2
%              tone_number  absolute time         
% .mif format: 
%         Bit: 19   ...    6 5   ...   0
%              tone_duration tone_number
%                   [ms]     [MIDI key #]

% read in csv file for Channel 0
csv0 = dlmread('Pirate_ch0.csv');
% format csv data for .mif file generation
f0 = zeros(size(csv0,1),1);
for i=1:size(csv0,1)-1
    f0(i)= (csv0(i+1,2)-csv0(i,2))*(2^6) + csv0(i,1);
end
% write .mif file in binary format
write(table(dec2bin(f0,20)), 'fmc_rom_0.mif', 'FileType', 'text', 'WriteVariableNames', false);