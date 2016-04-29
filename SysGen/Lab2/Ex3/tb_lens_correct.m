%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DSVB RT-Lab
% Lab2 Ex 3: SysGen model for correction of lens distortion effect.
%       v1 : Standalone Model with dual-port ping-pong buffer
%            Because of the buffer size required, this model can not 
%            be used for the streaming environment with its original
%            HDTV resolution.
%            This version has only the "nearest neighbor" interpolation 
%            method implemented. However, the architecture in principle 
%            is prepared to add linear interpolation as well.
% Waj, HSLU-T&A
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all; close all;

%% HW-Model Parameters
% Lens correction factor
K = 0.00004;
% Interpolation method for new row/col-index
% 0 = nearest neighbor; 1 = linear interpolation
IPM = 0;
% Latency in # of cc
LT_AdrGen = 1;
LT_IdxCalc = 9;
LT_IdxInpol = 3;
LT_PingPong = 2;
LT_PxlInpol = 1;
% Resolution for distorted x/y index
RES_DIST_XY = 4;

%% Read in the test image (==> enable one of the lines  below <==)
ImgIn = repmat([255 255 255 255 0 0 255 255 255 255]',6,100);
%ImgIn = imread('im3.bmp'); %ImgIn = rgb2gray(ImgIn);

%% Calculate image constants
SizeI = size(ImgIn);
ImgY = SizeI(1);
ImgX = SizeI(2);
Npxl = ImgY * ImgX;
Ycent = (ImgY-1)/2; % center of row index
Xcent = (ImgX-1)/2; % center of col index

%% Pre-Calculate the radius matrix
Xcorr = ones(ImgY,1)*([0:ImgX-1]-Xcent);  % difference of x from image center 
Ycorr = ([0:ImgY-1]-Ycent)'*ones(1,ImgX); % difference of y from image center
Radius = (Xcorr.*Xcorr+Ycorr.*Ycorr);
Radius_ROM = Radius';                     % transpose for row-wise addressing

%% Distort Image
ImgDist=zeros(size(ImgIn));
for y=1:ImgY
    for x=1:ImgX
        t=1-K*Radius(y,x);
        xd = max(ceil(((x-Xcent)*t)+Xcent),1);
        yd = max(ceil(((y-Ycent)*t)+Ycent),1);
        ImgDist(yd,xd) = ImgIn(y,x);
    end
end

%% Form input stream and run Simulink simulation
%ImgStrmIn = ImgIn';               % process original input image
ImgStrmIn = ImgDist';              % process distorted input image
sim('sg_lens_correct')

%% Form result image from output stream using Hsync/Vsync signals
idfp=min(find([HsyncStrmOut & VsyncStrmOut]))+1; % index of first pixel in frame
ImgOut = vec2mat(ImgStrmOut(idfp:idfp+Npxl-1),ImgX);

%% get expected response from golden model
Xdist = Xcorr.*(1-K*Radius);
Ydist = Ycorr.*(1-K*Radius);
%do the interpolation, as Xnew and Ynew are not integer values
ImgExp = interp2(Xcorr, Ycorr, ImgStrmIn', Xdist, Ydist, 'nearest');
%ImgExp = interp2(Xcorr, Ycorr, ImgStrmIn', Xdist, Ydist, 'linear');

%% Plot input and output image
figure(1);
subplot(2,2,1);
imshow(ImgIn,[0 255]);
title('original image');
subplot(2,2,2);
imshow(ImgDist,[0 255]);
title('distorted image');
subplot(2,2,3);
imshow(ImgOut,[0 255]);
title('corrected image HW');
subplot(2,2,4);
imshow(ImgExp,[0 255]);
title('corrected image GM');

%% Print # of pixel mismatches
Number_of_Pixel_Mismatches = length(find(ImgOut-ImgExp))
