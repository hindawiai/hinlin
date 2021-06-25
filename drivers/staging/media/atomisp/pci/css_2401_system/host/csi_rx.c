<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "system_global.h"
#समावेश "csi_rx_global.h"

स्थिर u32 N_SHORT_PACKET_LUT_ENTRIES[N_CSI_RX_BACKEND_ID] = अणु
	4,	/* 4 entries at CSI_RX_BACKEND0_ID*/
	4,	/* 4 entries at CSI_RX_BACKEND1_ID*/
	4	/* 4 entries at CSI_RX_BACKEND2_ID*/
पूर्ण;

स्थिर u32 N_LONG_PACKET_LUT_ENTRIES[N_CSI_RX_BACKEND_ID] = अणु
	8,	/* 8 entries at CSI_RX_BACKEND0_ID*/
	4,	/* 4 entries at CSI_RX_BACKEND1_ID*/
	4	/* 4 entries at CSI_RX_BACKEND2_ID*/
पूर्ण;

स्थिर u32 N_CSI_RX_FE_CTRL_DLANES[N_CSI_RX_FRONTEND_ID] = अणु
	N_CSI_RX_DLANE_ID,	/* 4 dlanes क्रम CSI_RX_FR0NTEND0_ID */
	N_CSI_RX_DLANE_ID,	/* 4 dlanes क्रम CSI_RX_FR0NTEND1_ID */
	N_CSI_RX_DLANE_ID	/* 4 dlanes क्रम CSI_RX_FR0NTEND2_ID */
पूर्ण;

/* sid_width क्रम CSI_RX_BACKEND<N>_ID */
स्थिर u32 N_CSI_RX_BE_SID_WIDTH[N_CSI_RX_BACKEND_ID] = अणु
	3,
	2,
	2
पूर्ण;
