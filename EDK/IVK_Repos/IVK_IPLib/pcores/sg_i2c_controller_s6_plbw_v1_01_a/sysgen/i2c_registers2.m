function [in_port, reset_dcm_o, sda_o, scl_o, cmd_get, cmd_rsp, cmd_ack] = i2c_registers2(out_port, port_id, rs, ws, sda_i, cmd_req, cmd_rdy)

% Declare persistent variables
persistent reset_dcm_reg; reset_dcm_reg = xl_state(false, {xlBoolean});
persistent sda_reg;       sda_reg       = xl_state(false, {xlBoolean});
persistent scl_reg;       scl_reg       = xl_state(false, {xlBoolean});
persistent cmd_get_reg;   cmd_get_reg   = xl_state(false, {xlBoolean});
persistent cmd_ack_reg;   cmd_ack_reg   = xl_state(false, {xlBoolean});
persistent cmd_rsp0_reg;  cmd_rsp0_reg  = xl_state(0, {xlUnsigned,8,0});
persistent cmd_rsp1_reg;  cmd_rsp1_reg  = xl_state(0, {xlUnsigned,8,0});
persistent cmd_rsp2_reg;  cmd_rsp2_reg  = xl_state(0, {xlUnsigned,8,0});
persistent cmd_rsp3_reg;  cmd_rsp3_reg  = xl_state(0, {xlUnsigned,8,0});

% Address Decodes
reset_sel = false;
i2c_sel   = false;
cmd_ctrl_sel = false;
cmd_dat0_sel  = false;
cmd_dat1_sel  = false;
cmd_dat2_sel  = false;
cmd_dat3_sel  = false;
if ( port_id == 0 ),
    reset_sel = true;
elseif ( port_id == 1 ),
    i2c_sel = true;
elseif ( port_id == 3 ),
    cmd_ctrl_sel = true;
elseif ( port_id == 4 ),
    cmd_dat0_sel = true;
elseif ( port_id == 5 ),
    cmd_dat1_sel = true;
elseif ( port_id == 6 ),
    cmd_dat2_sel = true;
elseif ( port_id == 7 ),
    cmd_dat3_sel = true;
end

% Write Enable Strobes
reset_we    = xl_and( reset_sel   , ws );
i2c_we      = xl_and( i2c_sel     , ws );
cmd_ctrl_we = xl_and( cmd_ctrl_sel, ws );
cmd_dat0_we = xl_and( cmd_dat0_sel, ws );
cmd_dat1_we = xl_and( cmd_dat1_sel, ws );
cmd_dat2_we = xl_and( cmd_dat2_sel, ws );
cmd_dat3_we = xl_and( cmd_dat3_sel, ws );

% reset_dcm
if ( reset_we == true ),
    reset_dcm_ = xfix({xlBoolean},xl_slice(out_port,0,0));
else
    reset_dcm_ = reset_dcm_reg;
end

% sda
if ( xl_and( i2c_we, xfix({xlBoolean},xl_slice(out_port,1,1)) ) == true ),
    sda_ = xfix({xlBoolean},xl_slice(out_port,0,0));
else
    sda_ = sda_reg;
end

% scl
if (xl_and( i2c_we, xfix({xlBoolean},xl_slice(out_port,3,3)) ) == true ),
    scl_ = xfix({xlBoolean},xl_slice(out_port,2,2));
else
    scl_ = scl_reg;
end

% cmd_*
if ( cmd_ctrl_we == true ),
    cmd_get_ = xfix({xlBoolean},xl_slice(out_port,1,1));
    cmd_ack_ = xfix({xlBoolean},xl_slice(out_port,0,0));
else
    cmd_get_ = false; % force back to 0 to create pulse
    cmd_ack_ = false; % force back to 0 to create pulse
end
if ( cmd_dat0_we == true ),
    cmd_rsp0_ = out_port;
else
    cmd_rsp0_ = cmd_rsp0_reg;
end
if ( cmd_dat1_we == true ),
    cmd_rsp1_ = out_port;
else
    cmd_rsp1_ = cmd_rsp1_reg;
end
if ( cmd_dat2_we == true ),
    cmd_rsp2_ = out_port;
else
    cmd_rsp2_ = cmd_rsp2_reg;
end
if ( cmd_dat3_we == true ),
    cmd_rsp3_ = out_port;
else
    cmd_rsp3_ = cmd_rsp3_reg;
end

% in_port (ie. read back data)
if ( i2c_sel == true ),
    in_port = xl_concat( xfix({xlUnsigned,7,0},0), xfix({xlUnsigned,1,0},sda_i) );
elseif ( cmd_ctrl_sel == true ),
    in_port = xl_concat( xfix({xlUnsigned,7,0},0), xfix({xlUnsigned,1,0},cmd_rdy) );
elseif ( cmd_dat0_sel == true ),
    in_port = xl_slice( cmd_req,  7,  0 );
elseif ( cmd_dat1_sel == true ),
    in_port = xl_slice( cmd_req, 15,  8 );
elseif ( cmd_dat2_sel == true ),
    in_port = xl_slice( cmd_req, 23, 16 );
elseif ( cmd_dat3_sel == true ),
    in_port = xl_slice( cmd_req, 31, 24 );
else
    in_port = xfix({xlUnsigned,8,0},0);
end

% Output ports
reset_dcm_o = reset_dcm_reg;
sda_o       = sda_reg;
scl_o       = scl_reg;
cmd_rsp     = xl_concat(cmd_rsp3_reg,cmd_rsp2_reg,cmd_rsp1_reg,cmd_rsp0_reg);
cmd_get     = cmd_get_reg;
cmd_ack     = cmd_ack_reg;

% Update persistent variables
reset_dcm_reg = reset_dcm_;
sda_reg       = sda_;
scl_reg       = scl_;
cmd_get_reg   = cmd_get_;
cmd_ack_reg   = cmd_ack_;
cmd_rsp0_reg  = cmd_rsp0_;
cmd_rsp1_reg  = cmd_rsp1_;
cmd_rsp2_reg  = cmd_rsp2_;
cmd_rsp3_reg  = cmd_rsp3_;

