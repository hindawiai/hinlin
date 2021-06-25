<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __CSI_RX_GLOBAL_H_INCLUDED__
#घोषणा __CSI_RX_GLOBAL_H_INCLUDED__

#समावेश <type_support.h>

प्रकार क्रमागत अणु
	CSI_MIPI_PACKET_TYPE_UNDEFINED = 0,
	CSI_MIPI_PACKET_TYPE_LONG,
	CSI_MIPI_PACKET_TYPE_SHORT,
	CSI_MIPI_PACKET_TYPE_RESERVED,
	N_CSI_MIPI_PACKET_TYPE
पूर्ण csi_mipi_packet_type_t;

प्रकार काष्ठा csi_rx_backend_lut_entry_s	csi_rx_backend_lut_entry_t;
काष्ठा csi_rx_backend_lut_entry_s अणु
	u32	दीर्घ_packet_entry;
	u32	लघु_packet_entry;
पूर्ण;

प्रकार काष्ठा csi_rx_backend_cfg_s csi_rx_backend_cfg_t;
काष्ठा csi_rx_backend_cfg_s अणु
	/* LUT entry क्रम the packet */
	csi_rx_backend_lut_entry_t lut_entry;

	/* can be derived from the Data Type */
	csi_mipi_packet_type_t csi_mipi_packet_type;

	काष्ठा अणु
		bool     comp_enable;
		u32 भव_channel;
		u32 data_type;
		u32 comp_scheme;
		u32 comp_predictor;
		u32 comp_bit_idx;
	पूर्ण csi_mipi_cfg;
पूर्ण;

प्रकार काष्ठा csi_rx_frontend_cfg_s csi_rx_frontend_cfg_t;
काष्ठा csi_rx_frontend_cfg_s अणु
	u32 active_lanes;
पूर्ण;

बाह्य स्थिर u32 N_SHORT_PACKET_LUT_ENTRIES[N_CSI_RX_BACKEND_ID];
बाह्य स्थिर u32 N_LONG_PACKET_LUT_ENTRIES[N_CSI_RX_BACKEND_ID];
बाह्य स्थिर u32 N_CSI_RX_FE_CTRL_DLANES[N_CSI_RX_FRONTEND_ID];
/* sid_width क्रम CSI_RX_BACKEND<N>_ID */
बाह्य स्थिर u32 N_CSI_RX_BE_SID_WIDTH[N_CSI_RX_BACKEND_ID];

#पूर्ण_अगर /* __CSI_RX_GLOBAL_H_INCLUDED__ */
