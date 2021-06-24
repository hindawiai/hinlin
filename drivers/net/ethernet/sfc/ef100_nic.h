<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 * Copyright 2019-2020 Xilinx Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#समावेश "net_driver.h"
#समावेश "nic_common.h"

बाह्य स्थिर काष्ठा efx_nic_type ef100_pf_nic_type;
बाह्य स्थिर काष्ठा efx_nic_type ef100_vf_nic_type;

पूर्णांक ef100_probe_pf(काष्ठा efx_nic *efx);
पूर्णांक ef100_probe_vf(काष्ठा efx_nic *efx);
व्योम ef100_हटाओ(काष्ठा efx_nic *efx);

क्रमागत अणु
	EF100_STAT_port_tx_bytes = GENERIC_STAT_COUNT,
	EF100_STAT_port_tx_packets,
	EF100_STAT_port_tx_छोड़ो,
	EF100_STAT_port_tx_unicast,
	EF100_STAT_port_tx_multicast,
	EF100_STAT_port_tx_broadcast,
	EF100_STAT_port_tx_lt64,
	EF100_STAT_port_tx_64,
	EF100_STAT_port_tx_65_to_127,
	EF100_STAT_port_tx_128_to_255,
	EF100_STAT_port_tx_256_to_511,
	EF100_STAT_port_tx_512_to_1023,
	EF100_STAT_port_tx_1024_to_15xx,
	EF100_STAT_port_tx_15xx_to_jumbo,
	EF100_STAT_port_rx_bytes,
	EF100_STAT_port_rx_packets,
	EF100_STAT_port_rx_good,
	EF100_STAT_port_rx_bad,
	EF100_STAT_port_rx_छोड़ो,
	EF100_STAT_port_rx_unicast,
	EF100_STAT_port_rx_multicast,
	EF100_STAT_port_rx_broadcast,
	EF100_STAT_port_rx_lt64,
	EF100_STAT_port_rx_64,
	EF100_STAT_port_rx_65_to_127,
	EF100_STAT_port_rx_128_to_255,
	EF100_STAT_port_rx_256_to_511,
	EF100_STAT_port_rx_512_to_1023,
	EF100_STAT_port_rx_1024_to_15xx,
	EF100_STAT_port_rx_15xx_to_jumbo,
	EF100_STAT_port_rx_gtjumbo,
	EF100_STAT_port_rx_bad_gtjumbo,
	EF100_STAT_port_rx_align_error,
	EF100_STAT_port_rx_length_error,
	EF100_STAT_port_rx_overflow,
	EF100_STAT_port_rx_nodesc_drops,
	EF100_STAT_COUNT
पूर्ण;

काष्ठा ef100_nic_data अणु
	काष्ठा efx_nic *efx;
	काष्ठा efx_buffer mcdi_buf;
	u32 datapath_caps;
	u32 datapath_caps2;
	u32 datapath_caps3;
	अचिन्हित पूर्णांक pf_index;
	u16 warm_boot_count;
	u8 port_id[ETH_ALEN];
	DECLARE_BITMAP(evq_phases, EFX_MAX_CHANNELS);
	u64 stats[EF100_STAT_COUNT];
	u16 tso_max_hdr_len;
	u16 tso_max_payload_num_segs;
	u16 tso_max_frames;
	अचिन्हित पूर्णांक tso_max_payload_len;
पूर्ण;

#घोषणा efx_ef100_has_cap(caps, flag) \
	(!!((caps) & BIT_ULL(MC_CMD_GET_CAPABILITIES_V4_OUT_ ## flag ## _LBN)))
