<शैली गुरु>
/*
 * Copyright (c) 2015-2016, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __MLX5_EN_STATS_H__
#घोषणा __MLX5_EN_STATS_H__

#घोषणा MLX5E_READ_CTR64_CPU(ptr, dsc, i) \
	(*(u64 *)((अक्षर *)ptr + dsc[i].offset))
#घोषणा MLX5E_READ_CTR64_BE(ptr, dsc, i) \
	be64_to_cpu(*(__be64 *)((अक्षर *)ptr + dsc[i].offset))
#घोषणा MLX5E_READ_CTR32_CPU(ptr, dsc, i) \
	(*(u32 *)((अक्षर *)ptr + dsc[i].offset))
#घोषणा MLX5E_READ_CTR32_BE(ptr, dsc, i) \
	be32_to_cpu(*(__be32 *)((अक्षर *)ptr + dsc[i].offset))

#घोषणा MLX5E_DECLARE_STAT(type, fld) #fld, दुरत्व(type, fld)
#घोषणा MLX5E_DECLARE_RX_STAT(type, fld) "rx%d_"#fld, दुरत्व(type, fld)
#घोषणा MLX5E_DECLARE_TX_STAT(type, fld) "tx%d_"#fld, दुरत्व(type, fld)
#घोषणा MLX5E_DECLARE_XDPSQ_STAT(type, fld) "tx%d_xdp_"#fld, दुरत्व(type, fld)
#घोषणा MLX5E_DECLARE_RQ_XDPSQ_STAT(type, fld) "rx%d_xdp_tx_"#fld, दुरत्व(type, fld)
#घोषणा MLX5E_DECLARE_XSKRQ_STAT(type, fld) "rx%d_xsk_"#fld, दुरत्व(type, fld)
#घोषणा MLX5E_DECLARE_XSKSQ_STAT(type, fld) "tx%d_xsk_"#fld, दुरत्व(type, fld)
#घोषणा MLX5E_DECLARE_CH_STAT(type, fld) "ch%d_"#fld, दुरत्व(type, fld)

#घोषणा MLX5E_DECLARE_PTP_TX_STAT(type, fld) "ptp_tx%d_"#fld, दुरत्व(type, fld)
#घोषणा MLX5E_DECLARE_PTP_CH_STAT(type, fld) "ptp_ch_"#fld, दुरत्व(type, fld)
#घोषणा MLX5E_DECLARE_PTP_CQ_STAT(type, fld) "ptp_cq%d_"#fld, दुरत्व(type, fld)
#घोषणा MLX5E_DECLARE_PTP_RQ_STAT(type, fld) "ptp_rq%d_"#fld, दुरत्व(type, fld)

#घोषणा MLX5E_DECLARE_QOS_TX_STAT(type, fld) "qos_tx%d_"#fld, दुरत्व(type, fld)

काष्ठा counter_desc अणु
	अक्षर		क्रमmat[ETH_GSTRING_LEN];
	माप_प्रकार		offset; /* Byte offset */
पूर्ण;

क्रमागत अणु
	MLX5E_NDO_UPDATE_STATS = BIT(0x1),
पूर्ण;

काष्ठा mlx5e_priv;
काष्ठा mlx5e_stats_grp अणु
	u16 update_stats_mask;
	पूर्णांक (*get_num_stats)(काष्ठा mlx5e_priv *priv);
	पूर्णांक (*fill_strings)(काष्ठा mlx5e_priv *priv, u8 *data, पूर्णांक idx);
	पूर्णांक (*fill_stats)(काष्ठा mlx5e_priv *priv, u64 *data, पूर्णांक idx);
	व्योम (*update_stats)(काष्ठा mlx5e_priv *priv);
पूर्ण;

प्रकार स्थिर काष्ठा mlx5e_stats_grp *स्थिर mlx5e_stats_grp_t;

#घोषणा MLX5E_STATS_GRP_OP(grp, name) mlx5e_stats_grp_ ## grp ## _ ## name

#घोषणा MLX5E_DECLARE_STATS_GRP_OP_NUM_STATS(grp) \
	पूर्णांक MLX5E_STATS_GRP_OP(grp, num_stats)(काष्ठा mlx5e_priv *priv)

#घोषणा MLX5E_DECLARE_STATS_GRP_OP_UPDATE_STATS(grp) \
	व्योम MLX5E_STATS_GRP_OP(grp, update_stats)(काष्ठा mlx5e_priv *priv)

#घोषणा MLX5E_DECLARE_STATS_GRP_OP_FILL_STRS(grp) \
	पूर्णांक MLX5E_STATS_GRP_OP(grp, fill_strings)(काष्ठा mlx5e_priv *priv, u8 *data, पूर्णांक idx)

#घोषणा MLX5E_DECLARE_STATS_GRP_OP_FILL_STATS(grp) \
	पूर्णांक MLX5E_STATS_GRP_OP(grp, fill_stats)(काष्ठा mlx5e_priv *priv, u64 *data, पूर्णांक idx)

#घोषणा MLX5E_STATS_GRP(grp) mlx5e_stats_grp_ ## grp

#घोषणा MLX5E_DECLARE_STATS_GRP(grp) \
	स्थिर काष्ठा mlx5e_stats_grp MLX5E_STATS_GRP(grp)

#घोषणा MLX5E_DEFINE_STATS_GRP(grp, mask) \
MLX5E_DECLARE_STATS_GRP(grp) = अणु \
	.get_num_stats = MLX5E_STATS_GRP_OP(grp, num_stats), \
	.fill_stats    = MLX5E_STATS_GRP_OP(grp, fill_stats), \
	.fill_strings  = MLX5E_STATS_GRP_OP(grp, fill_strings), \
	.update_stats  = MLX5E_STATS_GRP_OP(grp, update_stats), \
	.update_stats_mask = mask, \
पूर्ण

अचिन्हित पूर्णांक mlx5e_stats_total_num(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_stats_update(काष्ठा mlx5e_priv *priv);
व्योम mlx5e_stats_fill(काष्ठा mlx5e_priv *priv, u64 *data, पूर्णांक idx);
व्योम mlx5e_stats_fill_strings(काष्ठा mlx5e_priv *priv, u8 *data);
व्योम mlx5e_stats_update_nकरो_stats(काष्ठा mlx5e_priv *priv);

व्योम mlx5e_stats_छोड़ो_get(काष्ठा mlx5e_priv *priv,
			   काष्ठा ethtool_छोड़ो_stats *छोड़ो_stats);
व्योम mlx5e_stats_fec_get(काष्ठा mlx5e_priv *priv,
			 काष्ठा ethtool_fec_stats *fec_stats);

व्योम mlx5e_stats_eth_phy_get(काष्ठा mlx5e_priv *priv,
			     काष्ठा ethtool_eth_phy_stats *phy_stats);
व्योम mlx5e_stats_eth_mac_get(काष्ठा mlx5e_priv *priv,
			     काष्ठा ethtool_eth_mac_stats *mac_stats);
व्योम mlx5e_stats_eth_ctrl_get(काष्ठा mlx5e_priv *priv,
			      काष्ठा ethtool_eth_ctrl_stats *ctrl_stats);
व्योम mlx5e_stats_rmon_get(काष्ठा mlx5e_priv *priv,
			  काष्ठा ethtool_rmon_stats *rmon,
			  स्थिर काष्ठा ethtool_rmon_hist_range **ranges);

/* Concrete NIC Stats */

काष्ठा mlx5e_sw_stats अणु
	u64 rx_packets;
	u64 rx_bytes;
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_tso_packets;
	u64 tx_tso_bytes;
	u64 tx_tso_inner_packets;
	u64 tx_tso_inner_bytes;
	u64 tx_added_vlan_packets;
	u64 tx_nop;
	u64 tx_mpwqe_blks;
	u64 tx_mpwqe_pkts;
	u64 rx_lro_packets;
	u64 rx_lro_bytes;
	u64 rx_mcast_packets;
	u64 rx_ecn_mark;
	u64 rx_हटाओd_vlan_packets;
	u64 rx_csum_unnecessary;
	u64 rx_csum_none;
	u64 rx_csum_complete;
	u64 rx_csum_complete_tail;
	u64 rx_csum_complete_tail_slow;
	u64 rx_csum_unnecessary_inner;
	u64 rx_xdp_drop;
	u64 rx_xdp_redirect;
	u64 rx_xdp_tx_xmit;
	u64 rx_xdp_tx_mpwqe;
	u64 rx_xdp_tx_inlnw;
	u64 rx_xdp_tx_nops;
	u64 rx_xdp_tx_full;
	u64 rx_xdp_tx_err;
	u64 rx_xdp_tx_cqe;
	u64 tx_csum_none;
	u64 tx_csum_partial;
	u64 tx_csum_partial_inner;
	u64 tx_queue_stopped;
	u64 tx_queue_dropped;
	u64 tx_xmit_more;
	u64 tx_recover;
	u64 tx_cqes;
	u64 tx_queue_wake;
	u64 tx_cqe_err;
	u64 tx_xdp_xmit;
	u64 tx_xdp_mpwqe;
	u64 tx_xdp_inlnw;
	u64 tx_xdp_nops;
	u64 tx_xdp_full;
	u64 tx_xdp_err;
	u64 tx_xdp_cqes;
	u64 rx_wqe_err;
	u64 rx_mpwqe_filler_cqes;
	u64 rx_mpwqe_filler_strides;
	u64 rx_oversize_pkts_sw_drop;
	u64 rx_buff_alloc_err;
	u64 rx_cqe_compress_blks;
	u64 rx_cqe_compress_pkts;
	u64 rx_cache_reuse;
	u64 rx_cache_full;
	u64 rx_cache_empty;
	u64 rx_cache_busy;
	u64 rx_cache_waive;
	u64 rx_congst_umr;
	u64 rx_arfs_err;
	u64 rx_recover;
	u64 ch_events;
	u64 ch_poll;
	u64 ch_arm;
	u64 ch_aff_change;
	u64 ch_क्रमce_irq;
	u64 ch_eq_rearm;

#अगर_घोषित CONFIG_MLX5_EN_TLS
	u64 tx_tls_encrypted_packets;
	u64 tx_tls_encrypted_bytes;
	u64 tx_tls_ooo;
	u64 tx_tls_dump_packets;
	u64 tx_tls_dump_bytes;
	u64 tx_tls_resync_bytes;
	u64 tx_tls_skip_no_sync_data;
	u64 tx_tls_drop_no_sync_data;
	u64 tx_tls_drop_bypass_req;

	u64 rx_tls_decrypted_packets;
	u64 rx_tls_decrypted_bytes;
	u64 rx_tls_resync_req_pkt;
	u64 rx_tls_resync_req_start;
	u64 rx_tls_resync_req_end;
	u64 rx_tls_resync_req_skip;
	u64 rx_tls_resync_res_ok;
	u64 rx_tls_resync_res_retry;
	u64 rx_tls_resync_res_skip;
	u64 rx_tls_err;
#पूर्ण_अगर

	u64 rx_xsk_packets;
	u64 rx_xsk_bytes;
	u64 rx_xsk_csum_complete;
	u64 rx_xsk_csum_unnecessary;
	u64 rx_xsk_csum_unnecessary_inner;
	u64 rx_xsk_csum_none;
	u64 rx_xsk_ecn_mark;
	u64 rx_xsk_हटाओd_vlan_packets;
	u64 rx_xsk_xdp_drop;
	u64 rx_xsk_xdp_redirect;
	u64 rx_xsk_wqe_err;
	u64 rx_xsk_mpwqe_filler_cqes;
	u64 rx_xsk_mpwqe_filler_strides;
	u64 rx_xsk_oversize_pkts_sw_drop;
	u64 rx_xsk_buff_alloc_err;
	u64 rx_xsk_cqe_compress_blks;
	u64 rx_xsk_cqe_compress_pkts;
	u64 rx_xsk_congst_umr;
	u64 rx_xsk_arfs_err;
	u64 tx_xsk_xmit;
	u64 tx_xsk_mpwqe;
	u64 tx_xsk_inlnw;
	u64 tx_xsk_full;
	u64 tx_xsk_err;
	u64 tx_xsk_cqes;
पूर्ण;

काष्ठा mlx5e_qcounter_stats अणु
	u32 rx_out_of_buffer;
	u32 rx_अगर_करोwn_packets;
पूर्ण;

काष्ठा mlx5e_vnic_env_stats अणु
	__be64 query_vnic_env_out[MLX5_ST_SZ_QW(query_vnic_env_out)];
पूर्ण;

#घोषणा VPORT_COUNTER_GET(vstats, c) MLX5_GET64(query_vport_counter_out, \
						vstats->query_vport_out, c)

काष्ठा mlx5e_vport_stats अणु
	__be64 query_vport_out[MLX5_ST_SZ_QW(query_vport_counter_out)];
पूर्ण;

#घोषणा PPORT_802_3_GET(pstats, c) \
	MLX5_GET64(ppcnt_reg, pstats->IEEE_802_3_counters, \
		   counter_set.eth_802_3_cntrs_grp_data_layout.c##_high)
#घोषणा PPORT_2863_GET(pstats, c) \
	MLX5_GET64(ppcnt_reg, pstats->RFC_2863_counters, \
		   counter_set.eth_2863_cntrs_grp_data_layout.c##_high)
#घोषणा PPORT_2819_GET(pstats, c) \
	MLX5_GET64(ppcnt_reg, pstats->RFC_2819_counters, \
		   counter_set.eth_2819_cntrs_grp_data_layout.c##_high)
#घोषणा PPORT_PHY_STATISTICAL_GET(pstats, c) \
	MLX5_GET64(ppcnt_reg, (pstats)->phy_statistical_counters, \
		   counter_set.phys_layer_statistical_cntrs.c##_high)
#घोषणा PPORT_PER_PRIO_GET(pstats, prio, c) \
	MLX5_GET64(ppcnt_reg, pstats->per_prio_counters[prio], \
		   counter_set.eth_per_prio_grp_data_layout.c##_high)
#घोषणा NUM_PPORT_PRIO				8
#घोषणा PPORT_ETH_EXT_GET(pstats, c) \
	MLX5_GET64(ppcnt_reg, (pstats)->eth_ext_counters, \
		   counter_set.eth_extended_cntrs_grp_data_layout.c##_high)

काष्ठा mlx5e_pport_stats अणु
	__be64 IEEE_802_3_counters[MLX5_ST_SZ_QW(ppcnt_reg)];
	__be64 RFC_2863_counters[MLX5_ST_SZ_QW(ppcnt_reg)];
	__be64 RFC_2819_counters[MLX5_ST_SZ_QW(ppcnt_reg)];
	__be64 per_prio_counters[NUM_PPORT_PRIO][MLX5_ST_SZ_QW(ppcnt_reg)];
	__be64 phy_counters[MLX5_ST_SZ_QW(ppcnt_reg)];
	__be64 phy_statistical_counters[MLX5_ST_SZ_QW(ppcnt_reg)];
	__be64 eth_ext_counters[MLX5_ST_SZ_QW(ppcnt_reg)];
	__be64 per_tc_prio_counters[NUM_PPORT_PRIO][MLX5_ST_SZ_QW(ppcnt_reg)];
	__be64 per_tc_congest_prio_counters[NUM_PPORT_PRIO][MLX5_ST_SZ_QW(ppcnt_reg)];
पूर्ण;

#घोषणा PCIE_PERF_GET(pcie_stats, c) \
	MLX5_GET(mpcnt_reg, (pcie_stats)->pcie_perf_counters, \
		 counter_set.pcie_perf_cntrs_grp_data_layout.c)

#घोषणा PCIE_PERF_GET64(pcie_stats, c) \
	MLX5_GET64(mpcnt_reg, (pcie_stats)->pcie_perf_counters, \
		   counter_set.pcie_perf_cntrs_grp_data_layout.c##_high)

काष्ठा mlx5e_pcie_stats अणु
	__be64 pcie_perf_counters[MLX5_ST_SZ_QW(mpcnt_reg)];
पूर्ण;

काष्ठा mlx5e_rq_stats अणु
	u64 packets;
	u64 bytes;
	u64 csum_complete;
	u64 csum_complete_tail;
	u64 csum_complete_tail_slow;
	u64 csum_unnecessary;
	u64 csum_unnecessary_inner;
	u64 csum_none;
	u64 lro_packets;
	u64 lro_bytes;
	u64 mcast_packets;
	u64 ecn_mark;
	u64 हटाओd_vlan_packets;
	u64 xdp_drop;
	u64 xdp_redirect;
	u64 wqe_err;
	u64 mpwqe_filler_cqes;
	u64 mpwqe_filler_strides;
	u64 oversize_pkts_sw_drop;
	u64 buff_alloc_err;
	u64 cqe_compress_blks;
	u64 cqe_compress_pkts;
	u64 cache_reuse;
	u64 cache_full;
	u64 cache_empty;
	u64 cache_busy;
	u64 cache_waive;
	u64 congst_umr;
	u64 arfs_err;
	u64 recover;
#अगर_घोषित CONFIG_MLX5_EN_TLS
	u64 tls_decrypted_packets;
	u64 tls_decrypted_bytes;
	u64 tls_resync_req_pkt;
	u64 tls_resync_req_start;
	u64 tls_resync_req_end;
	u64 tls_resync_req_skip;
	u64 tls_resync_res_ok;
	u64 tls_resync_res_retry;
	u64 tls_resync_res_skip;
	u64 tls_err;
#पूर्ण_अगर
पूर्ण;

काष्ठा mlx5e_sq_stats अणु
	/* commonly accessed in data path */
	u64 packets;
	u64 bytes;
	u64 xmit_more;
	u64 tso_packets;
	u64 tso_bytes;
	u64 tso_inner_packets;
	u64 tso_inner_bytes;
	u64 csum_partial;
	u64 csum_partial_inner;
	u64 added_vlan_packets;
	u64 nop;
	u64 mpwqe_blks;
	u64 mpwqe_pkts;
#अगर_घोषित CONFIG_MLX5_EN_TLS
	u64 tls_encrypted_packets;
	u64 tls_encrypted_bytes;
	u64 tls_ooo;
	u64 tls_dump_packets;
	u64 tls_dump_bytes;
	u64 tls_resync_bytes;
	u64 tls_skip_no_sync_data;
	u64 tls_drop_no_sync_data;
	u64 tls_drop_bypass_req;
#पूर्ण_अगर
	/* less likely accessed in data path */
	u64 csum_none;
	u64 stopped;
	u64 dropped;
	u64 recover;
	/* dirtied @completion */
	u64 cqes ____cacheline_aligned_in_smp;
	u64 wake;
	u64 cqe_err;
पूर्ण;

काष्ठा mlx5e_xdpsq_stats अणु
	u64 xmit;
	u64 mpwqe;
	u64 inlnw;
	u64 nops;
	u64 full;
	u64 err;
	/* dirtied @completion */
	u64 cqes ____cacheline_aligned_in_smp;
पूर्ण;

काष्ठा mlx5e_ch_stats अणु
	u64 events;
	u64 poll;
	u64 arm;
	u64 aff_change;
	u64 क्रमce_irq;
	u64 eq_rearm;
पूर्ण;

काष्ठा mlx5e_ptp_cq_stats अणु
	u64 cqe;
	u64 err_cqe;
	u64 पात;
	u64 पात_असल_dअगरf_ns;
पूर्ण;

काष्ठा mlx5e_stats अणु
	काष्ठा mlx5e_sw_stats sw;
	काष्ठा mlx5e_qcounter_stats qcnt;
	काष्ठा mlx5e_vnic_env_stats vnic;
	काष्ठा mlx5e_vport_stats vport;
	काष्ठा mlx5e_pport_stats pport;
	काष्ठा rtnl_link_stats64 vf_vport;
	काष्ठा mlx5e_pcie_stats pcie;
पूर्ण;

बाह्य mlx5e_stats_grp_t mlx5e_nic_stats_grps[];
अचिन्हित पूर्णांक mlx5e_nic_stats_grps_num(काष्ठा mlx5e_priv *priv);

बाह्य MLX5E_DECLARE_STATS_GRP(sw);
बाह्य MLX5E_DECLARE_STATS_GRP(qcnt);
बाह्य MLX5E_DECLARE_STATS_GRP(vnic_env);
बाह्य MLX5E_DECLARE_STATS_GRP(vport);
बाह्य MLX5E_DECLARE_STATS_GRP(802_3);
बाह्य MLX5E_DECLARE_STATS_GRP(2863);
बाह्य MLX5E_DECLARE_STATS_GRP(2819);
बाह्य MLX5E_DECLARE_STATS_GRP(phy);
बाह्य MLX5E_DECLARE_STATS_GRP(eth_ext);
बाह्य MLX5E_DECLARE_STATS_GRP(pcie);
बाह्य MLX5E_DECLARE_STATS_GRP(per_prio);
बाह्य MLX5E_DECLARE_STATS_GRP(pme);
बाह्य MLX5E_DECLARE_STATS_GRP(channels);
बाह्य MLX5E_DECLARE_STATS_GRP(per_port_buff_congest);
बाह्य MLX5E_DECLARE_STATS_GRP(ipsec_hw);
बाह्य MLX5E_DECLARE_STATS_GRP(ipsec_sw);

#पूर्ण_अगर /* __MLX5_EN_STATS_H__ */
