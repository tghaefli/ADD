%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DSVB RT-Lab
% Teamprojekt: WP1 Downsampling & Upsampling
%    Note:
%    =====
%    Before exporting the SysGen Model for HW integration, make sure
%    the SysGen model has been configured corresponding to the maximum 
%    frame size being used on the FPGA-platform! To do so, set No_Sim = 1
%    in order to avoid excessive simulation runtimes.
%
% Waj 2-May-2012, HSLU-T&A
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all; close all;

%% Parameters for HW Model
% Simulation or HW Generation
No_Sim = 0; % 0 = perform simulation; 1 = configure HW-Model only 
DS_on = 1;  % downsampling by 2: ON = 1; OFF = 0
US_on = 1;  % upsampling by 2  : ON = 1; OFF = 0

if No_Sim == 0
    % Simulation settings
    HFP = 2;   % Horizontal Front Porch        [pixel] (VGA: 16)
    HSW = 3;   % Horizontal Sync Pulse Width   [pixel] (VGA: 96)
    HBP = 2;   % Horizontal Back Porch         [pixel] (VGA: 48)
else
    % Syntesis settings
    HFP = 16;  % Horizontal Front Porch        [pixel] (VGA: 16)
    HSW = 96;  % Horizontal Sync Pulse Width   [pixel] (VGA: 96)
    HBP = 48;  % Horizontal Back Porch         [pixel] (VGA: 48)
end
HBH = HFP+HSW+HBP;    % hblanc high        [pixel] (VGA: 160)

mdl_ds = 'sg_ds'; % Downsample
mdl_us = 'sg_us'; % Upsample
hw_mdl_ds = '/sg_ds/'; % Downsample
hw_mdl_us = '/sg_us/'; % Upsample

% define output/input variables between ds/us-unit to prevent
% errors when compiling us_unit without simulation
vsync_o_ds = 0; vblank_o_ds = 0; hsync_o_ds = 0; hblank_o_ds = 0;
active_video_o_ds = 0; vd_o_ds = 0;


%% Read in the test image (==> enable one of the lines  below <==)
if No_Sim == 0
    % simulation settings
    ImgIn = [ repmat([10 10 10 50 50 50 80 80 80 110 110 110 140 140 140 160 160 160 200 200 230 230 230 250],16,1) ;  ...
              repmat([10 10 10 50 50 50 80 80 80 110 110 110 140 140 140 160 160 160 200 200 230 230 230 250]',1,24) ] ;
    %ImgIn = repmat([0 50 100 150 200 250],6,1); 
    %ImgIn = imread('ActualImage.bmp');
else
    % synthesis settings
    ImgIn = repmat([50 50 100 100 150 150]',80,640); % use 80,640 for VGA resolution
end
%% Calculate image constants
SizeI = size(ImgIn);
ImgY = SizeI(1); % 480 = # of rows in VGA resolution on HW-platform
ImgX = SizeI(2); % 640 = # of cols in VGA resolution on HW-platform
Npxl = ImgY * ImgX;

%% Form expected output images  (golden model of required functionality)
% Note that Matlab indexes matrix elements column-wise, while in the 
% HW-implementation pixels are streamed row-wise!
if No_Sim == 0
% downsampling    
r_ImgExp = downsample(downsample(ImgIn,DS_on+1)',DS_on+1)'; 
g_ImgExp = downsample(downsample(ImgIn,DS_on+1)',DS_on+1)'; 
b_ImgExp = downsample(downsample(ImgIn,DS_on+1)',DS_on+1)'; 
% upsampling
if US_on == 1
    r_ImgExp = (upsample(r_ImgExp',2))'+circshift(upsample(r_ImgExp',2)',[0 1]);
    r_ImgExp = upsample(r_ImgExp,2) + circshift(upsample(r_ImgExp,2),1);
    g_ImgExp = (upsample(g_ImgExp',2))'+circshift(upsample(g_ImgExp',2)',[0 1]);
    g_ImgExp = upsample(g_ImgExp,2) + circshift(upsample(g_ImgExp,2),1);
    b_ImgExp = (upsample(b_ImgExp',2))'+circshift(upsample(b_ImgExp',2)',[0 1]);
    b_ImgExp = upsample(b_ImgExp,2) + circshift(upsample(b_ImgExp,2),1);
end
end % No_Sim
%% Set XSVI length parameter and construct XSVI-input signals
VFP = 1;   % Vertical Front Porch          [rows]  (VGA: 10)
VSW = 1;   % Horizontal Sync Pulse Width   [rows]  (VGA: 2)
VBP = 1;   % Horizontal Back Porch         [rows]  (VGA: 33)

VBH = VFP+VSW+VBP;           % vblank high        [rows]   (VGA: 45)
TFL = (HBH+ImgX)*(ImgY+VBH); % total frame length [pixel]

% form VSVI signals
if No_Sim == 0

vsync_i = [ones(1,HSW+HBP+ImgX+HFP) repmat(ones(1,ImgX+HBH),1,ImgY+VFP-1) ...
           repmat(zeros(1,ImgX+HBH),1,VSW)  ...
           repmat(ones(1,ImgX+HBH),1,VBP)];
vblank_i = [zeros(1,HSW+HBP+ImgX+HFP) repmat(zeros(1,ImgX+HBH),1,ImgY-1) ...
            repmat(ones(1,ImgX+HBH),1,VBH)];
hsync_i  = repmat([zeros(1,HSW) ones(1,ImgX+HFP+HBP)],1,TFL);
hblank_i = [ones(1,HSW+HBP) repmat([zeros(1,ImgX) ones(1,HBH)],1,TFL-1) ...
            zeros(1,ImgX) ones(1,HFP)];
actvid_i = [zeros(1,HSW+HBP) repmat([ones(1,ImgX) zeros(1,HBH)],1,ImgY) ...
            zeros(1,(ImgX+HBH)*(VBH-1)+ImgX+HFP)];
        

else % No_Sim
    
    vsync_i =  0;
    vblank_i = 0;
    hsync_i  = 0;
    hblank_i = 0;
    actvid_i = 0;
 
end % No_Sim

%% Form input data stream using XSVI control signals
if No_Sim == 0
    
    data_i = ones(1,TFL); % default pixel value
    for r=1:ImgY
        idx = (r-1)*(ImgX+HBH) + HSW + HBP + 1; % +1 because of Matlab indexing
        data_i(idx:idx+ImgX-1) = ImgIn(r,:);
    end
    vd_i = data_i*2^16 + data_i*2^8 + data_i; % red + green + blue channel

else % No_Sim
    
    vd_i = 0;

end % No_Sim

%% Configure and Simulate HW-Model
load_system(mdl_ds);
load_system(mdl_us);
Tsim = 2*TFL+(HBH+ImgX)*(VBH); % simulation length
%get_param(strcat(mdl,mdl_hw,'Cfg_Reg_Pxl_Idx'),'DialogParameters')

set_param(strcat(mdl_ds,hw_mdl_ds,'reg_bypass'),'init',int2str(abs(DS_on-1)));
set_param(strcat(mdl_us,hw_mdl_us,'reg_bypass'),'init',int2str(abs(US_on-1)));
% start simulation only when required
if No_Sim == 0
    sim(mdl_ds);
    sim(mdl_us);
end
    
%% Form result image from output stream using XSVI-output signals
if No_Sim == 0
% first falling edge detection on vblank
i1 = min(find([~[vblank_o;1] & [0;vblank_o]]));
% offset to linear pixel index 0 (first pixel in frame)
i1 = i1 + HSW + HBP + (1-US_on)*DS_on*ImgX/2;
% consistency check with all XSVI output signals
if ~vsync_o(i1) | vblank_o(i1) | ~hsync_o(i1) | hblank_o(i1) | ~active_video_o(i1)
  disp('ERROR: XSVI output signals not consistent!!!');
end;
% form RGB streams
r_stream = zeros(1,(Npxl/(DS_on+1)^2)*(US_on+1)^2);
g_stream = zeros(1,(Npxl/(DS_on+1)^2)*(US_on+1)^2);
b_stream = zeros(1,(Npxl/(DS_on+1)^2)*(US_on+1)^2);
for r = 1:(ImgY/(DS_on+1))*(US_on+1)
    % extract one row of 24-bit data pixels from output video stream
    row_rgb = vd_o(i1:i1+(ImgX/(DS_on+1))*(US_on+1)-1);
    % extract 3 x 8-bit RGB-values from 24-bit data pixels 
    row_b = floor(rem(row_rgb,2^8));
    row_g = floor(rem(row_rgb/2^8,2^8));
    row_r = floor(row_rgb/2^16);
    % add row of RGB-values to corresponding stream
    i2 = (r-1)*(US_on+1)*ImgX/(DS_on+1) + 1;% +1 because of Matlab i
    b_stream(i2:i2+(ImgX/(DS_on+1))*(US_on+1)-1) = row_b;
    g_stream(i2:i2+(ImgX/(DS_on+1))*(US_on+1)-1) = row_g;
    r_stream(i2:i2+(ImgX/(DS_on+1))*(US_on+1)-1) = row_r;
    % calculate index of next valid pixel in out video stream
    i1 = i1 + (DS_on+1)*(ImgX + HBH)/(US_on+1);
end
% convert RGB streams to 3 output images
r_ImgOut = vec2mat(r_stream,(US_on+1)*ImgX/(DS_on+1));
g_ImgOut = vec2mat(g_stream,(US_on+1)*ImgX/(DS_on+1));
b_ImgOut = vec2mat(b_stream,(US_on+1)*ImgX/(DS_on+1));
end % No_Sim

%% Plot images per color channel for visual comparison of expected and actual outputs
if No_Sim == 0
% input images
subplot(3,3,1); imshow(ImgIn,[0 255]); title('original input image (red)');
subplot(3,3,2); imshow(ImgIn,[0 255]); title('original input image (green)');
subplot(3,3,3); imshow(ImgIn,[0 255]); title('original input image (blue)');
% expected output images
subplot(3,3,4); imshow(r_ImgExp,[0 255]); title('expected output image (red)');
subplot(3,3,5); imshow(g_ImgExp,[0 255]); title('expected output image (green)');
subplot(3,3,6); imshow(b_ImgExp,[0 255]); title('expected output image (blue)');
%actual output images
subplot(3,3,7); imshow(r_ImgOut,[0 255]); title('actual output image (red)');
subplot(3,3,8); imshow(g_ImgOut,[0 255]); title('actual output image (green)');
subplot(3,3,9); imshow(b_ImgOut,[0 255]); title('actual output image (blue)');
end % No_Sim