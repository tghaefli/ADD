///////////////////////////////////////////////////////////////-*-C-*-
//
// Copyright (c) 2010 Xilinx, Inc.  All rights reserved.
//
// Xilinx, Inc.  XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION
// "AS IS" AS  A COURTESY TO YOU.  BY PROVIDING  THIS DESIGN, CODE, OR
// INFORMATION  AS  ONE   POSSIBLE  IMPLEMENTATION  OF  THIS  FEATURE,
// APPLICATION OR  STANDARD, XILINX  IS MAKING NO  REPRESENTATION THAT
// THIS IMPLEMENTATION  IS FREE FROM  ANY CLAIMS OF  INFRINGEMENT, AND
// YOU ARE  RESPONSIBLE FOR OBTAINING  ANY RIGHTS YOU MAY  REQUIRE FOR
// YOUR  IMPLEMENTATION.   XILINX  EXPRESSLY  DISCLAIMS  ANY  WARRANTY
// WHATSOEVER  WITH RESPECT  TO  THE ADEQUACY  OF THE  IMPLEMENTATION,
// INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR REPRESENTATIONS THAT
// THIS IMPLEMENTATION  IS FREE  FROM CLAIMS OF  INFRINGEMENT, IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
// 
//////////////////////////////////////////////////////////////////////

#ifndef __XL_SG_2D_FIR_PLBW_H__
#define __XL_SG_2D_FIR_PLBW_H__

#include "xbasic_types.h"
#include "xstatus.h"
#include "xcope.h"

typedef struct {
    uint32_t version;
    // Pointers to low-level functions
    xc_status_t (*xc_create)(xc_iface_t **, void *);
    xc_status_t (*xc_release)(xc_iface_t **);
    xc_status_t (*xc_open)(xc_iface_t *);
    xc_status_t (*xc_close)(xc_iface_t *);
    xc_status_t (*xc_read)(xc_iface_t *, xc_r_addr_t, uint32_t *);
    xc_status_t (*xc_write)(xc_iface_t *, xc_w_addr_t, const uint32_t);
    xc_status_t (*xc_get_shmem)(xc_iface_t *, const char *, void **shmem);
    // Optional parameters
    // (empty)
    // Memory map information
    uint32_t coef_update;
    uint32_t coef_update_n_bits;
    uint32_t coef_update_bin_pt;
    // uint32_t coef_update_attr;
    uint32_t coef_gain;
    uint32_t coef_gain_n_bits;
    uint32_t coef_gain_bin_pt;
    // uint32_t coef_gain_attr;
    uint32_t coef_buffer;
    // uint32_t coef_buffer_grant;
    // uint32_t coef_buffer_req;
    uint32_t coef_buffer_n_bits;
    uint32_t coef_buffer_bin_pt;
    uint32_t coef_buffer_depth;
    // uint32_t coef_buffer_attr;
    // XPS parameters
    Xuint16  DeviceId;
    uint32_t  BaseAddr;
} SG_2D_FIR_PLBW_Config;

extern SG_2D_FIR_PLBW_Config SG_2D_FIR_PLBW_ConfigTable[];

// forward declaration of low-level functions
xc_status_t xc_sg_2d_fir_plbw_create(xc_iface_t **iface, void *config_table);
xc_status_t xc_sg_2d_fir_plbw_release(xc_iface_t **iface) ;
xc_status_t xc_sg_2d_fir_plbw_open(xc_iface_t *iface);
xc_status_t xc_sg_2d_fir_plbw_close(xc_iface_t *iface);
xc_status_t xc_sg_2d_fir_plbw_read(xc_iface_t *iface, xc_r_addr_t addr, uint32_t *value);
xc_status_t xc_sg_2d_fir_plbw_write(xc_iface_t *iface, xc_w_addr_t addr, const uint32_t value);
xc_status_t xc_sg_2d_fir_plbw_getshmem(xc_iface_t *iface, const char *name, void **shmem);

#endif

