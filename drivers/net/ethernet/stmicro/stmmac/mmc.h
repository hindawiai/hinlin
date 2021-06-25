<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************
  MMC Header file

  Copyright (C) 2011  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#अगर_अघोषित __MMC_H__
#घोषणा __MMC_H__

/* MMC control रेजिस्टर */
/* When set, all counter are reset */
#घोषणा MMC_CNTRL_COUNTER_RESET		0x1
/* When set, करो not roll over zero after reaching the max value*/
#घोषणा MMC_CNTRL_COUNTER_STOP_ROLLOVER	0x2
#घोषणा MMC_CNTRL_RESET_ON_READ		0x4	/* Reset after पढ़ोing */
#घोषणा MMC_CNTRL_COUNTER_FREEZER	0x8	/* Freeze counter values to the
						 * current value.*/
#घोषणा MMC_CNTRL_PRESET		0x10
#घोषणा MMC_CNTRL_FULL_HALF_PRESET	0x20

#घोषणा MMC_GMAC4_OFFSET		0x700
#घोषणा MMC_GMAC3_X_OFFSET		0x100
#घोषणा MMC_XGMAC_OFFSET		0x800

काष्ठा sपंचांगmac_counters अणु
	अचिन्हित पूर्णांक mmc_tx_octetcount_gb;
	अचिन्हित पूर्णांक mmc_tx_framecount_gb;
	अचिन्हित पूर्णांक mmc_tx_broadcastframe_g;
	अचिन्हित पूर्णांक mmc_tx_multicastframe_g;
	अचिन्हित पूर्णांक mmc_tx_64_octets_gb;
	अचिन्हित पूर्णांक mmc_tx_65_to_127_octets_gb;
	अचिन्हित पूर्णांक mmc_tx_128_to_255_octets_gb;
	अचिन्हित पूर्णांक mmc_tx_256_to_511_octets_gb;
	अचिन्हित पूर्णांक mmc_tx_512_to_1023_octets_gb;
	अचिन्हित पूर्णांक mmc_tx_1024_to_max_octets_gb;
	अचिन्हित पूर्णांक mmc_tx_unicast_gb;
	अचिन्हित पूर्णांक mmc_tx_multicast_gb;
	अचिन्हित पूर्णांक mmc_tx_broadcast_gb;
	अचिन्हित पूर्णांक mmc_tx_underflow_error;
	अचिन्हित पूर्णांक mmc_tx_singlecol_g;
	अचिन्हित पूर्णांक mmc_tx_multicol_g;
	अचिन्हित पूर्णांक mmc_tx_deferred;
	अचिन्हित पूर्णांक mmc_tx_latecol;
	अचिन्हित पूर्णांक mmc_tx_exesscol;
	अचिन्हित पूर्णांक mmc_tx_carrier_error;
	अचिन्हित पूर्णांक mmc_tx_octetcount_g;
	अचिन्हित पूर्णांक mmc_tx_framecount_g;
	अचिन्हित पूर्णांक mmc_tx_excessdef;
	अचिन्हित पूर्णांक mmc_tx_छोड़ो_frame;
	अचिन्हित पूर्णांक mmc_tx_vlan_frame_g;

	/* MMC RX counter रेजिस्टरs */
	अचिन्हित पूर्णांक mmc_rx_framecount_gb;
	अचिन्हित पूर्णांक mmc_rx_octetcount_gb;
	अचिन्हित पूर्णांक mmc_rx_octetcount_g;
	अचिन्हित पूर्णांक mmc_rx_broadcastframe_g;
	अचिन्हित पूर्णांक mmc_rx_multicastframe_g;
	अचिन्हित पूर्णांक mmc_rx_crc_error;
	अचिन्हित पूर्णांक mmc_rx_align_error;
	अचिन्हित पूर्णांक mmc_rx_run_error;
	अचिन्हित पूर्णांक mmc_rx_jabber_error;
	अचिन्हित पूर्णांक mmc_rx_undersize_g;
	अचिन्हित पूर्णांक mmc_rx_oversize_g;
	अचिन्हित पूर्णांक mmc_rx_64_octets_gb;
	अचिन्हित पूर्णांक mmc_rx_65_to_127_octets_gb;
	अचिन्हित पूर्णांक mmc_rx_128_to_255_octets_gb;
	अचिन्हित पूर्णांक mmc_rx_256_to_511_octets_gb;
	अचिन्हित पूर्णांक mmc_rx_512_to_1023_octets_gb;
	अचिन्हित पूर्णांक mmc_rx_1024_to_max_octets_gb;
	अचिन्हित पूर्णांक mmc_rx_unicast_g;
	अचिन्हित पूर्णांक mmc_rx_length_error;
	अचिन्हित पूर्णांक mmc_rx_स्वतःfrangetype;
	अचिन्हित पूर्णांक mmc_rx_छोड़ो_frames;
	अचिन्हित पूर्णांक mmc_rx_fअगरo_overflow;
	अचिन्हित पूर्णांक mmc_rx_vlan_frames_gb;
	अचिन्हित पूर्णांक mmc_rx_watchकरोg_error;
	/* IPC */
	अचिन्हित पूर्णांक mmc_rx_ipc_पूर्णांकr_mask;
	अचिन्हित पूर्णांक mmc_rx_ipc_पूर्णांकr;
	/* IPv4 */
	अचिन्हित पूर्णांक mmc_rx_ipv4_gd;
	अचिन्हित पूर्णांक mmc_rx_ipv4_hderr;
	अचिन्हित पूर्णांक mmc_rx_ipv4_nopay;
	अचिन्हित पूर्णांक mmc_rx_ipv4_frag;
	अचिन्हित पूर्णांक mmc_rx_ipv4_udsbl;

	अचिन्हित पूर्णांक mmc_rx_ipv4_gd_octets;
	अचिन्हित पूर्णांक mmc_rx_ipv4_hderr_octets;
	अचिन्हित पूर्णांक mmc_rx_ipv4_nopay_octets;
	अचिन्हित पूर्णांक mmc_rx_ipv4_frag_octets;
	अचिन्हित पूर्णांक mmc_rx_ipv4_udsbl_octets;

	/* IPV6 */
	अचिन्हित पूर्णांक mmc_rx_ipv6_gd_octets;
	अचिन्हित पूर्णांक mmc_rx_ipv6_hderr_octets;
	अचिन्हित पूर्णांक mmc_rx_ipv6_nopay_octets;

	अचिन्हित पूर्णांक mmc_rx_ipv6_gd;
	अचिन्हित पूर्णांक mmc_rx_ipv6_hderr;
	अचिन्हित पूर्णांक mmc_rx_ipv6_nopay;

	/* Protocols */
	अचिन्हित पूर्णांक mmc_rx_udp_gd;
	अचिन्हित पूर्णांक mmc_rx_udp_err;
	अचिन्हित पूर्णांक mmc_rx_tcp_gd;
	अचिन्हित पूर्णांक mmc_rx_tcp_err;
	अचिन्हित पूर्णांक mmc_rx_icmp_gd;
	अचिन्हित पूर्णांक mmc_rx_icmp_err;

	अचिन्हित पूर्णांक mmc_rx_udp_gd_octets;
	अचिन्हित पूर्णांक mmc_rx_udp_err_octets;
	अचिन्हित पूर्णांक mmc_rx_tcp_gd_octets;
	अचिन्हित पूर्णांक mmc_rx_tcp_err_octets;
	अचिन्हित पूर्णांक mmc_rx_icmp_gd_octets;
	अचिन्हित पूर्णांक mmc_rx_icmp_err_octets;

	/* FPE */
	अचिन्हित पूर्णांक mmc_tx_fpe_fragment_cntr;
	अचिन्हित पूर्णांक mmc_tx_hold_req_cntr;
	अचिन्हित पूर्णांक mmc_rx_packet_assembly_err_cntr;
	अचिन्हित पूर्णांक mmc_rx_packet_smd_err_cntr;
	अचिन्हित पूर्णांक mmc_rx_packet_assembly_ok_cntr;
	अचिन्हित पूर्णांक mmc_rx_fpe_fragment_cntr;
पूर्ण;

#पूर्ण_अगर /* __MMC_H__ */
