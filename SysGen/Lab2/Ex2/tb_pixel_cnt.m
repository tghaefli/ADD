%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DSVB RT-Lab
% Lab2: Video Processing Design with SysGen
%   v0: Tutorial Example
%       Demonstrates SysGen features such as counting pixel indexes
%       which will be usefull in realizing the lens-correction algorithm.
%       Note that this model uses simplified hsync/vsync control
%       signals, which are active with the last pixel of each 
%       row/frame, instead of XSVI signals.
%
% Waj, HSLU-T&A
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all; close all;

%% Read in the test image (==> enable one of the lines  below <==)
ImgIn = repmat([0 0 1 1 1 1 1]',4,50);
%ImgIn = imread('ActualImage.bmp');

%% Calculate image constants
SizeI = size(ImgIn);
ImgY = SizeI(1);
ImgX = SizeI(2);
Npxl = ImgY * ImgX;

%% Pre-Calculate the radius matrix
XVal = ones(ImgY,1)*([1:ImgX]-ImgX/2);  %difference of x from image center
YVal = ([1:ImgY]-ImgY/2)'*ones(1,ImgX); %difference of y from image center
Radius = sqrt(XVal.*XVal+YVal.*YVal);
Radius_ROM = Radius';     
% transpose for row-wise addressing
% Implement ROM in FPGA using Block RAM
open('sg_pixel_cnt');
set_param('sg_pixel_cnt/sg_pixel_cnt/Radius ROM',...
          'distributed_mem','Block RAM')
% Note: Available dialog parameters can be displayed with
get_param('sg_pixel_cnt/sg_pixel_cnt/Radius ROM','DialogParameters');

%% Form input stream and run Simulink simulation
ImgStrmIn = ImgIn';                % transpose for row-wise streaming
sim('sg_pixel_cnt')

%% Form result image from output stream using Hsync/Vsync signals
idfp=min(find([HsyncStrmOut & VsyncStrmOut]))+1; % index of first pixel in frame
ImgOut = vec2mat(ImgStrmOut(idfp:idfp+Npxl-1),ImgX);

%% Plot input and output image
figure(1);subplot(1,2,1);
imshow(ImgIn);
title('original image');
subplot(1,2,2);
imshow(ImgOut);
title('output image');
