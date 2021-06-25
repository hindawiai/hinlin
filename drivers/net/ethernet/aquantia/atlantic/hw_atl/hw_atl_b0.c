<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File hw_atl_b0.c: Definition of Atlantic hardware specअगरic functions. */

#समावेश "../aq_hw.h"
#समावेश "../aq_hw_utils.h"
#समावेश "../aq_ring.h"
#समावेश "../aq_nic.h"
#समावेश "../aq_phy.h"
#समावेश "hw_atl_b0.h"
#समावेश "hw_atl_utils.h"
#समावेश "hw_atl_llh.h"
#समावेश "hw_atl_b0_internal.h"
#समावेश "hw_atl_llh_internal.h"

#घोषणा DEFAULT_B0_BOARD_BASIC_CAPABILITIES \
	.is_64_dma = true,		  \
	.op64bit = false,		  \
	.msix_irqs = 8U,		  \
	.irq_mask = ~0U,		  \
	.vecs = HW_ATL_B0_RSS_MAX,	  \
	.tcs_max = HW_ATL_B0_TC_MAX,	  \
	.rxd_alignment = 1U,		  \
	.rxd_size = HW_ATL_B0_RXD_SIZE,   \
	.rxds_max = HW_ATL_B0_MAX_RXD,    \
	.rxds_min = HW_ATL_B0_MIN_RXD,    \
	.txd_alignment = 1U,		  \
	.txd_size = HW_ATL_B0_TXD_SIZE,   \
	.txds_max = HW_ATL_B0_MAX_TXD,    \
	.txds_min = HW_ATL_B0_MIN_TXD,    \
	.txhwb_alignment = 4096U,	  \
	.tx_rings = HW_ATL_B0_TX_RINGS,   \
	.rx_rings = HW_ATL_B0_RX_RINGS,   \
	.hw_features = NETIF_F_HW_CSUM |  \
			NETIF_F_RXCSUM |  \
			NETIF_F_RXHASH |  \
			NETIF_F_SG |      \
			NETIF_F_TSO |     \
			NETIF_F_TSO6 |    \
			NETIF_F_LRO |     \
			NETIF_F_NTUPLE |  \
			NETIF_F_HW_VLAN_CTAG_FILTER | \
			NETIF_F_HW_VLAN_CTAG_RX |     \
			NETIF_F_HW_VLAN_CTAG_TX |     \
			NETIF_F_GSO_UDP_L4      |     \
			NETIF_F_GSO_PARTIAL |         \
			NETIF_F_HW_TC,                \
	.hw_priv_flags = IFF_UNICAST_FLT, \
	.flow_control = true,		  \
	.mtu = HW_ATL_B0_MTU_JUMBO,	  \
	.mac_regs_count = 88,		  \
	.hw_alive_check_addr = 0x10U

स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc100 = अणु
	DEFAULT_B0_BOARD_BASIC_CAPABILITIES,
	.media_type = AQ_HW_MEDIA_TYPE_FIBRE,
	.link_speed_msk = AQ_NIC_RATE_10G |
			  AQ_NIC_RATE_5G |
			  AQ_NIC_RATE_2G5 |
			  AQ_NIC_RATE_1G |
			  AQ_NIC_RATE_100M,
पूर्ण;

स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc107 = अणु
	DEFAULT_B0_BOARD_BASIC_CAPABILITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.link_speed_msk = AQ_NIC_RATE_10G |
			  AQ_NIC_RATE_5G |
			  AQ_NIC_RATE_2G5 |
			  AQ_NIC_RATE_1G |
			  AQ_NIC_RATE_100M,
पूर्ण;

स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc108 = अणु
	DEFAULT_B0_BOARD_BASIC_CAPABILITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.link_speed_msk = AQ_NIC_RATE_5G |
			  AQ_NIC_RATE_2G5 |
			  AQ_NIC_RATE_1G |
			  AQ_NIC_RATE_100M,
पूर्ण;

स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc109 = अणु
	DEFAULT_B0_BOARD_BASIC_CAPABILITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.link_speed_msk = AQ_NIC_RATE_2G5 |
			  AQ_NIC_RATE_1G |
			  AQ_NIC_RATE_100M,
पूर्ण;

स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc111 = अणु
	DEFAULT_B0_BOARD_BASIC_CAPABILITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.link_speed_msk = AQ_NIC_RATE_5G |
			  AQ_NIC_RATE_2G5 |
			  AQ_NIC_RATE_1G |
			  AQ_NIC_RATE_100M,
	.quirks = AQ_NIC_QUIRK_BAD_PTP,
पूर्ण;

स्थिर काष्ठा aq_hw_caps_s hw_atl_b0_caps_aqc112 = अणु
	DEFAULT_B0_BOARD_BASIC_CAPABILITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.link_speed_msk = AQ_NIC_RATE_2G5 |
			  AQ_NIC_RATE_1G  |
			  AQ_NIC_RATE_100M,
	.quirks = AQ_NIC_QUIRK_BAD_PTP,
पूर्ण;

अटल पूर्णांक hw_atl_b0_hw_reset(काष्ठा aq_hw_s *self)
अणु
	पूर्णांक err = 0;

	err = hw_atl_utils_soft_reset(self);
	अगर (err)
		वापस err;

	self->aq_fw_ops->set_state(self, MPI_RESET);

	err = aq_hw_err_from_flags(self);

	वापस err;
पूर्ण

पूर्णांक hw_atl_b0_set_fc(काष्ठा aq_hw_s *self, u32 fc, u32 tc)
अणु
	hw_atl_rpb_rx_xoff_en_per_tc_set(self, !!(fc & AQ_NIC_FC_RX), tc);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_atl_b0_tc_ptp_set(काष्ठा aq_hw_s *self)
अणु
	/* Init TC2 क्रम PTP_TX */
	hw_atl_tpb_tx_pkt_buff_size_per_tc_set(self, HW_ATL_B0_PTP_TXBUF_SIZE,
					       AQ_HW_PTP_TC);

	/* Init TC2 क्रम PTP_RX */
	hw_atl_rpb_rx_pkt_buff_size_per_tc_set(self, HW_ATL_B0_PTP_RXBUF_SIZE,
					       AQ_HW_PTP_TC);
	/* No flow control क्रम PTP */
	hw_atl_rpb_rx_xoff_en_per_tc_set(self, 0U, AQ_HW_PTP_TC);

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_qos_set(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;
	u32 tx_buff_size = HW_ATL_B0_TXBUF_MAX;
	u32 rx_buff_size = HW_ATL_B0_RXBUF_MAX;
	अचिन्हित पूर्णांक prio = 0U;
	u32 tc = 0U;

	अगर (cfg->is_ptp) अणु
		tx_buff_size -= HW_ATL_B0_PTP_TXBUF_SIZE;
		rx_buff_size -= HW_ATL_B0_PTP_RXBUF_SIZE;
	पूर्ण

	/* TPS Descriptor rate init */
	hw_atl_tps_tx_pkt_shed_desc_rate_curr_समय_res_set(self, 0x0U);
	hw_atl_tps_tx_pkt_shed_desc_rate_lim_set(self, 0xA);

	/* TPS VM init */
	hw_atl_tps_tx_pkt_shed_desc_vm_arb_mode_set(self, 0U);

	tx_buff_size /= cfg->tcs;
	rx_buff_size /= cfg->tcs;
	क्रम (tc = 0; tc < cfg->tcs; tc++) अणु
		u32 threshold = 0U;

		/* Tx buf size TC0 */
		hw_atl_tpb_tx_pkt_buff_size_per_tc_set(self, tx_buff_size, tc);

		threshold = (tx_buff_size * (1024 / 32U) * 66U) / 100U;
		hw_atl_tpb_tx_buff_hi_threshold_per_tc_set(self, threshold, tc);

		threshold = (tx_buff_size * (1024 / 32U) * 50U) / 100U;
		hw_atl_tpb_tx_buff_lo_threshold_per_tc_set(self, threshold, tc);

		/* QoS Rx buf size per TC */
		hw_atl_rpb_rx_pkt_buff_size_per_tc_set(self, rx_buff_size, tc);

		threshold = (rx_buff_size * (1024U / 32U) * 66U) / 100U;
		hw_atl_rpb_rx_buff_hi_threshold_per_tc_set(self, threshold, tc);

		threshold = (rx_buff_size * (1024U / 32U) * 50U) / 100U;
		hw_atl_rpb_rx_buff_lo_threshold_per_tc_set(self, threshold, tc);

		hw_atl_b0_set_fc(self, self->aq_nic_cfg->fc.req, tc);
	पूर्ण

	अगर (cfg->is_ptp)
		hw_atl_b0_tc_ptp_set(self);

	/* QoS 802.1p priority -> TC mapping */
	क्रम (prio = 0; prio < 8; ++prio)
		hw_atl_rpf_rpb_user_priority_tc_map_set(self, prio,
							cfg->prio_tc_map[prio]);

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_rss_hash_set(काष्ठा aq_hw_s *self,
			      काष्ठा aq_rss_parameters *rss_params)
अणु
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;
	अचिन्हित पूर्णांक addr = 0U;
	अचिन्हित पूर्णांक i = 0U;
	पूर्णांक err = 0;
	u32 val;

	क्रम (i = 10, addr = 0U; i--; ++addr) अणु
		u32 key_data = cfg->is_rss ?
			__swab32(rss_params->hash_secret_key[i]) : 0U;
		hw_atl_rpf_rss_key_wr_data_set(self, key_data);
		hw_atl_rpf_rss_key_addr_set(self, addr);
		hw_atl_rpf_rss_key_wr_en_set(self, 1U);
		err = पढ़ोx_poll_समयout_atomic(hw_atl_rpf_rss_key_wr_en_get,
						self, val, val == 0,
						1000U, 10000U);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण

	err = aq_hw_err_from_flags(self);

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_rss_set(काष्ठा aq_hw_s *self,
				काष्ठा aq_rss_parameters *rss_params)
अणु
	u32 num_rss_queues = max(1U, self->aq_nic_cfg->num_rss_queues);
	u8 *indirection_table =	rss_params->indirection_table;
	u16 bitary[1 + (HW_ATL_B0_RSS_REसूचीECTION_MAX *
		   HW_ATL_B0_RSS_REसूचीECTION_BITS / 16U)];
	पूर्णांक err = 0;
	u32 i = 0U;
	u32 val;

	स_रखो(bitary, 0, माप(bitary));

	क्रम (i = HW_ATL_B0_RSS_REसूचीECTION_MAX; i--;) अणु
		(*(u32 *)(bitary + ((i * 3U) / 16U))) |=
			((indirection_table[i] % num_rss_queues) <<
			((i * 3U) & 0xFU));
	पूर्ण

	क्रम (i = ARRAY_SIZE(bitary); i--;) अणु
		hw_atl_rpf_rss_redir_tbl_wr_data_set(self, bitary[i]);
		hw_atl_rpf_rss_redir_tbl_addr_set(self, i);
		hw_atl_rpf_rss_redir_wr_en_set(self, 1U);
		err = पढ़ोx_poll_समयout_atomic(hw_atl_rpf_rss_redir_wr_en_get,
						self, val, val == 0,
						1000U, 10000U);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण

	err = aq_hw_err_from_flags(self);

err_निकास:
	वापस err;
पूर्ण

पूर्णांक hw_atl_b0_hw_offload_set(काष्ठा aq_hw_s *self,
			     काष्ठा aq_nic_cfg_s *aq_nic_cfg)
अणु
	u64 rxcsum = !!(aq_nic_cfg->features & NETIF_F_RXCSUM);
	अचिन्हित पूर्णांक i;

	/* TX checksums offloads*/
	hw_atl_tpo_ipv4header_crc_offload_en_set(self, 1);
	hw_atl_tpo_tcp_udp_crc_offload_en_set(self, 1);

	/* RX checksums offloads*/
	hw_atl_rpo_ipv4header_crc_offload_en_set(self, rxcsum);
	hw_atl_rpo_tcp_udp_crc_offload_en_set(self, rxcsum);

	/* LSO offloads*/
	hw_atl_tdm_large_send_offload_en_set(self, 0xFFFFFFFFU);

	/* Outer VLAN tag offload */
	hw_atl_rpo_outer_vlan_tag_mode_set(self, 1U);

	/* LRO offloads */
	अणु
		अचिन्हित पूर्णांक val = (8U < HW_ATL_B0_LRO_RXD_MAX) ? 0x3U :
			((4U < HW_ATL_B0_LRO_RXD_MAX) ? 0x2U :
			((2U < HW_ATL_B0_LRO_RXD_MAX) ? 0x1U : 0x0));

		क्रम (i = 0; i < HW_ATL_B0_RINGS_MAX; i++)
			hw_atl_rpo_lro_max_num_of_descriptors_set(self, val, i);

		hw_atl_rpo_lro_समय_base_भागider_set(self, 0x61AU);
		hw_atl_rpo_lro_inactive_पूर्णांकerval_set(self, 0);
		/* the LRO समयbase भागider is 5 uS (0x61a),
		 * which is multiplied by 50(0x32)
		 * to get a maximum coalescing पूर्णांकerval of 250 uS,
		 * which is the शेष value
		 */
		hw_atl_rpo_lro_max_coalescing_पूर्णांकerval_set(self, 50);

		hw_atl_rpo_lro_qsessions_lim_set(self, 1U);

		hw_atl_rpo_lro_total_desc_lim_set(self, 2U);

		hw_atl_rpo_lro_patch_optimization_en_set(self, 1U);

		hw_atl_rpo_lro_min_pay_of_first_pkt_set(self, 10U);

		hw_atl_rpo_lro_pkt_lim_set(self, 1U);

		hw_atl_rpo_lro_en_set(self,
				      aq_nic_cfg->is_lro ? 0xFFFFFFFFU : 0U);
		hw_atl_itr_rsc_en_set(self,
				      aq_nic_cfg->is_lro ? 0xFFFFFFFFU : 0U);

		hw_atl_itr_rsc_delay_set(self, 1U);
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_init_tx_tc_rate_limit(काष्ठा aq_hw_s *self)
अणु
	अटल स्थिर u32 max_weight = BIT(HW_ATL_TPS_DATA_TCTWEIGHT_WIDTH) - 1;
	/* Scale factor is based on the number of bits in fractional portion */
	अटल स्थिर u32 scale = BIT(HW_ATL_TPS_DESC_RATE_Y_WIDTH);
	अटल स्थिर u32 frac_msk = HW_ATL_TPS_DESC_RATE_Y_MSK >>
				    HW_ATL_TPS_DESC_RATE_Y_SHIFT;
	स्थिर u32 link_speed = self->aq_link_status.mbps;
	काष्ठा aq_nic_cfg_s *nic_cfg = self->aq_nic_cfg;
	अचिन्हित दीर्घ num_min_rated_tcs = 0;
	u32 tc_weight[AQ_CFG_TCS_MAX];
	u32 fixed_max_credit;
	u8 min_rate_msk = 0;
	u32 sum_weight = 0;
	पूर्णांक tc;

	/* By शेष max_credit is based upon MTU (in unit of 64b) */
	fixed_max_credit = nic_cfg->aq_hw_caps->mtu / 64;

	अगर (link_speed) अणु
		min_rate_msk = nic_cfg->tc_min_rate_msk &
			       (BIT(nic_cfg->tcs) - 1);
		num_min_rated_tcs = hweight8(min_rate_msk);
	पूर्ण

	/* First, calculate weights where min_rate is specअगरied */
	अगर (num_min_rated_tcs) अणु
		क्रम (tc = 0; tc != nic_cfg->tcs; tc++) अणु
			अगर (!nic_cfg->tc_min_rate[tc]) अणु
				tc_weight[tc] = 0;
				जारी;
			पूर्ण

			tc_weight[tc] = (-1L + link_speed +
					 nic_cfg->tc_min_rate[tc] *
					 max_weight) /
					link_speed;
			tc_weight[tc] = min(tc_weight[tc], max_weight);
			sum_weight += tc_weight[tc];
		पूर्ण
	पूर्ण

	/* WSP, अगर min_rate is set क्रम at least one TC.
	 * RR otherwise.
	 *
	 * NB! MAC FW sets arb mode itself अगर PTP is enabled. We shouldn't
	 * overग_लिखो it here in that हाल.
	 */
	अगर (!nic_cfg->is_ptp)
		hw_atl_tps_tx_pkt_shed_data_arb_mode_set(self, min_rate_msk ? 1U : 0U);

	/* Data TC Arbiter takes precedence over Descriptor TC Arbiter,
	 * leave Descriptor TC Arbiter as RR.
	 */
	hw_atl_tps_tx_pkt_shed_desc_tc_arb_mode_set(self, 0U);

	hw_atl_tps_tx_desc_rate_mode_set(self, nic_cfg->is_qos ? 1U : 0U);

	क्रम (tc = 0; tc != nic_cfg->tcs; tc++) अणु
		स्थिर u32 en = (nic_cfg->tc_max_rate[tc] != 0) ? 1U : 0U;
		स्थिर u32 desc = AQ_NIC_CFG_TCVEC2RING(nic_cfg, tc, 0);
		u32 weight, max_credit;

		hw_atl_tps_tx_pkt_shed_desc_tc_max_credit_set(self, tc,
							      fixed_max_credit);
		hw_atl_tps_tx_pkt_shed_desc_tc_weight_set(self, tc, 0x1E);

		अगर (num_min_rated_tcs) अणु
			weight = tc_weight[tc];

			अगर (!weight && sum_weight < max_weight)
				weight = (max_weight - sum_weight) /
					 (nic_cfg->tcs - num_min_rated_tcs);
			अन्यथा अगर (!weight)
				weight = 0x64;

			max_credit = max(8 * weight, fixed_max_credit);
		पूर्ण अन्यथा अणु
			weight = 0x64;
			max_credit = 0xFFF;
		पूर्ण

		hw_atl_tps_tx_pkt_shed_tc_data_weight_set(self, tc, weight);
		hw_atl_tps_tx_pkt_shed_tc_data_max_credit_set(self, tc,
							      max_credit);

		hw_atl_tps_tx_desc_rate_en_set(self, desc, en);

		अगर (en) अणु
			/* Nominal rate is always 10G */
			स्थिर u32 rate = 10000U * scale /
					 nic_cfg->tc_max_rate[tc];
			स्थिर u32 rate_पूर्णांक = rate >>
					     HW_ATL_TPS_DESC_RATE_Y_WIDTH;
			स्थिर u32 rate_frac = rate & frac_msk;

			hw_atl_tps_tx_desc_rate_x_set(self, desc, rate_पूर्णांक);
			hw_atl_tps_tx_desc_rate_y_set(self, desc, rate_frac);
		पूर्ण अन्यथा अणु
			/* A value of 1 indicates the queue is not
			 * rate controlled.
			 */
			hw_atl_tps_tx_desc_rate_x_set(self, desc, 1U);
			hw_atl_tps_tx_desc_rate_y_set(self, desc, 0U);
		पूर्ण
	पूर्ण
	क्रम (tc = nic_cfg->tcs; tc != AQ_CFG_TCS_MAX; tc++) अणु
		स्थिर u32 desc = AQ_NIC_CFG_TCVEC2RING(nic_cfg, tc, 0);

		hw_atl_tps_tx_desc_rate_en_set(self, desc, 0U);
		hw_atl_tps_tx_desc_rate_x_set(self, desc, 1U);
		hw_atl_tps_tx_desc_rate_y_set(self, desc, 0U);
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_init_tx_path(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_nic_cfg_s *nic_cfg = self->aq_nic_cfg;

	/* Tx TC/Queue number config */
	hw_atl_tpb_tps_tx_tc_mode_set(self, nic_cfg->tc_mode);

	hw_atl_thm_lso_tcp_flag_of_first_pkt_set(self, 0x0FF6U);
	hw_atl_thm_lso_tcp_flag_of_middle_pkt_set(self, 0x0FF6U);
	hw_atl_thm_lso_tcp_flag_of_last_pkt_set(self, 0x0F7FU);

	/* Tx पूर्णांकerrupts */
	hw_atl_tdm_tx_desc_wr_wb_irq_en_set(self, 1U);

	/* misc */
	aq_hw_ग_लिखो_reg(self, 0x00007040U, ATL_HW_IS_CHIP_FEATURE(self, TPO2) ?
			0x00010000U : 0x00000000U);
	hw_atl_tdm_tx_dca_en_set(self, 0U);
	hw_atl_tdm_tx_dca_mode_set(self, 0U);

	hw_atl_tpb_tx_path_scp_ins_en_set(self, 1U);

	वापस aq_hw_err_from_flags(self);
पूर्ण

व्योम hw_atl_b0_hw_init_rx_rss_ctrl1(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;
	u32 rss_ctrl1 = HW_ATL_RSS_DISABLED;

	अगर (cfg->is_rss)
		rss_ctrl1 = (cfg->tc_mode == AQ_TC_MODE_8TCS) ?
			    HW_ATL_RSS_ENABLED_8TCS_2INDEX_BITS :
			    HW_ATL_RSS_ENABLED_4TCS_3INDEX_BITS;

	hw_atl_reg_rx_flr_rss_control1set(self, rss_ctrl1);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_init_rx_path(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;
	पूर्णांक i;

	/* Rx TC/RSS number config */
	hw_atl_rpb_rpf_rx_traf_class_mode_set(self, cfg->tc_mode);

	/* Rx flow control */
	hw_atl_rpb_rx_flow_ctl_mode_set(self, 1U);

	/* RSS Ring selection */
	hw_atl_b0_hw_init_rx_rss_ctrl1(self);

	/* Multicast filters */
	क्रम (i = HW_ATL_B0_MAC_MAX; i--;) अणु
		hw_atl_rpfl2_uc_flr_en_set(self, (i == 0U) ? 1U : 0U, i);
		hw_atl_rpfl2unicast_flr_act_set(self, 1U, i);
	पूर्ण

	hw_atl_reg_rx_flr_mcst_flr_msk_set(self, 0x00000000U);
	hw_atl_reg_rx_flr_mcst_flr_set(self, 0x00010FFFU, 0U);

	/* Vlan filters */
	hw_atl_rpf_vlan_outer_etht_set(self, 0x88A8U);
	hw_atl_rpf_vlan_inner_etht_set(self, 0x8100U);

	hw_atl_rpf_vlan_prom_mode_en_set(self, 1);

	// Always accept untagged packets
	hw_atl_rpf_vlan_accept_untagged_packets_set(self, 1U);
	hw_atl_rpf_vlan_untagged_act_set(self, 1U);

	/* Rx Interrupts */
	hw_atl_rdm_rx_desc_wr_wb_irq_en_set(self, 1U);

	/* misc */
	aq_hw_ग_लिखो_reg(self, 0x00005040U, ATL_HW_IS_CHIP_FEATURE(self, RPF2) ?
			0x000F0000U : 0x00000000U);

	hw_atl_rpfl2broadcast_flr_act_set(self, 1U);
	hw_atl_rpfl2broadcast_count_threshold_set(self, 0xFFFFU & (~0U / 256U));

	hw_atl_rdm_rx_dca_en_set(self, 0U);
	hw_atl_rdm_rx_dca_mode_set(self, 0U);

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_mac_addr_set(काष्ठा aq_hw_s *self, u8 *mac_addr)
अणु
	अचिन्हित पूर्णांक h = 0U;
	अचिन्हित पूर्णांक l = 0U;
	पूर्णांक err = 0;

	अगर (!mac_addr) अणु
		err = -EINVAL;
		जाओ err_निकास;
	पूर्ण
	h = (mac_addr[0] << 8) | (mac_addr[1]);
	l = (mac_addr[2] << 24) | (mac_addr[3] << 16) |
		(mac_addr[4] << 8) | mac_addr[5];

	hw_atl_rpfl2_uc_flr_en_set(self, 0U, HW_ATL_B0_MAC);
	hw_atl_rpfl2unicast_dest_addresslsw_set(self, l, HW_ATL_B0_MAC);
	hw_atl_rpfl2unicast_dest_addressmsw_set(self, h, HW_ATL_B0_MAC);
	hw_atl_rpfl2_uc_flr_en_set(self, 1U, HW_ATL_B0_MAC);

	err = aq_hw_err_from_flags(self);

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_init(काष्ठा aq_hw_s *self, u8 *mac_addr)
अणु
	अटल u32 aq_hw_atl_igcr_table_[4][2] = अणु
		[AQ_HW_IRQ_INVALID] = अणु 0x20000000U, 0x20000000U पूर्ण,
		[AQ_HW_IRQ_LEGACY]  = अणु 0x20000080U, 0x20000080U पूर्ण,
		[AQ_HW_IRQ_MSI]     = अणु 0x20000021U, 0x20000025U पूर्ण,
		[AQ_HW_IRQ_MSIX]    = अणु 0x20000022U, 0x20000026U पूर्ण,
	पूर्ण;
	काष्ठा aq_nic_cfg_s *aq_nic_cfg = self->aq_nic_cfg;
	पूर्णांक err = 0;
	u32 val;


	hw_atl_b0_hw_init_tx_path(self);
	hw_atl_b0_hw_init_rx_path(self);

	hw_atl_b0_hw_mac_addr_set(self, mac_addr);

	self->aq_fw_ops->set_link_speed(self, aq_nic_cfg->link_speed_msk);
	self->aq_fw_ops->set_state(self, MPI_INIT);

	hw_atl_b0_hw_qos_set(self);
	hw_atl_b0_hw_rss_set(self, &aq_nic_cfg->aq_rss);
	hw_atl_b0_hw_rss_hash_set(self, &aq_nic_cfg->aq_rss);

	/* Force limit MRRS on RDM/TDM to 2K */
	val = aq_hw_पढ़ो_reg(self, HW_ATL_PCI_REG_CONTROL6_ADR);
	aq_hw_ग_लिखो_reg(self, HW_ATL_PCI_REG_CONTROL6_ADR,
			(val & ~0x707) | 0x404);

	/* TX DMA total request limit. B0 hardware is not capable to
	 * handle more than (8K-MRRS) incoming DMA data.
	 * Value 24 in 256byte units
	 */
	aq_hw_ग_लिखो_reg(self, HW_ATL_TX_DMA_TOTAL_REQ_LIMIT_ADR, 24);

	/* Reset link status and पढ़ो out initial hardware counters */
	self->aq_link_status.mbps = 0;
	self->aq_fw_ops->update_stats(self);

	err = aq_hw_err_from_flags(self);
	अगर (err < 0)
		जाओ err_निकास;

	/* Interrupts */
	hw_atl_reg_irq_glb_ctl_set(self,
				   aq_hw_atl_igcr_table_[aq_nic_cfg->irq_type]
						 [(aq_nic_cfg->vecs > 1U) ?
						 1 : 0]);

	hw_atl_itr_irq_स्वतः_masklsw_set(self, aq_nic_cfg->aq_hw_caps->irq_mask);

	/* Interrupts */
	hw_atl_reg_gen_irq_map_set(self,
				   ((HW_ATL_B0_ERR_INT << 0x18) |
				    (1U << 0x1F)) |
				   ((HW_ATL_B0_ERR_INT << 0x10) |
				    (1U << 0x17)), 0U);

	/* Enable link पूर्णांकerrupt */
	अगर (aq_nic_cfg->link_irq_vec)
		hw_atl_reg_gen_irq_map_set(self, BIT(7) |
					   aq_nic_cfg->link_irq_vec, 3U);

	hw_atl_b0_hw_offload_set(self, aq_nic_cfg);

err_निकास:
	वापस err;
पूर्ण

पूर्णांक hw_atl_b0_hw_ring_tx_start(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring)
अणु
	hw_atl_tdm_tx_desc_en_set(self, 1, ring->idx);

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_ring_rx_start(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring)
अणु
	hw_atl_rdm_rx_desc_en_set(self, 1, ring->idx);

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_start(काष्ठा aq_hw_s *self)
अणु
	hw_atl_tpb_tx_buff_en_set(self, 1);
	hw_atl_rpb_rx_buff_en_set(self, 1);

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_tx_ring_tail_update(काष्ठा aq_hw_s *self,
					    काष्ठा aq_ring_s *ring)
अणु
	hw_atl_reg_tx_dma_desc_tail_ptr_set(self, ring->sw_tail, ring->idx);

	वापस 0;
पूर्ण

पूर्णांक hw_atl_b0_hw_ring_tx_xmit(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring,
			      अचिन्हित पूर्णांक frags)
अणु
	काष्ठा aq_ring_buff_s *buff = शून्य;
	काष्ठा hw_atl_txd_s *txd = शून्य;
	अचिन्हित पूर्णांक buff_pa_len = 0U;
	अचिन्हित पूर्णांक frag_count = 0U;
	अचिन्हित पूर्णांक pkt_len = 0U;
	bool is_vlan = false;
	bool is_gso = false;

	buff = &ring->buff_ring[ring->sw_tail];
	pkt_len = (buff->is_eop && buff->is_sop) ? buff->len : buff->len_pkt;

	क्रम (frag_count = 0; frag_count < frags; frag_count++) अणु
		txd = (काष्ठा hw_atl_txd_s *)&ring->dx_ring[ring->sw_tail *
						HW_ATL_B0_TXD_SIZE];
		txd->ctl = 0;
		txd->ctl2 = 0;
		txd->buf_addr = 0;

		buff = &ring->buff_ring[ring->sw_tail];

		अगर (buff->is_gso_tcp || buff->is_gso_udp) अणु
			अगर (buff->is_gso_tcp)
				txd->ctl |= HW_ATL_B0_TXD_CTL_CMD_TCP;
			txd->ctl |= HW_ATL_B0_TXD_CTL_DESC_TYPE_TXC;
			txd->ctl |= (buff->len_l3 << 31) |
				    (buff->len_l2 << 24);
			txd->ctl2 |= (buff->mss << 16);
			is_gso = true;

			pkt_len -= (buff->len_l4 +
				    buff->len_l3 +
				    buff->len_l2);
			अगर (buff->is_ipv6)
				txd->ctl |= HW_ATL_B0_TXD_CTL_CMD_IPV6;
			txd->ctl2 |= (buff->len_l4 << 8) |
				     (buff->len_l3 >> 1);
		पूर्ण
		अगर (buff->is_vlan) अणु
			txd->ctl |= HW_ATL_B0_TXD_CTL_DESC_TYPE_TXC;
			txd->ctl |= buff->vlan_tx_tag << 4;
			is_vlan = true;
		पूर्ण
		अगर (!buff->is_gso_tcp && !buff->is_gso_udp && !buff->is_vlan) अणु
			buff_pa_len = buff->len;

			txd->buf_addr = buff->pa;
			txd->ctl |= (HW_ATL_B0_TXD_CTL_BLEN &
						((u32)buff_pa_len << 4));
			txd->ctl |= HW_ATL_B0_TXD_CTL_DESC_TYPE_TXD;

			/* PAY_LEN */
			txd->ctl2 |= HW_ATL_B0_TXD_CTL2_LEN & (pkt_len << 14);

			अगर (is_gso || is_vlan) अणु
				/* enable tx context */
				txd->ctl2 |= HW_ATL_B0_TXD_CTL2_CTX_EN;
			पूर्ण
			अगर (is_gso)
				txd->ctl |= HW_ATL_B0_TXD_CTL_CMD_LSO;

			/* Tx checksum offloads */
			अगर (buff->is_ip_cso)
				txd->ctl |= HW_ATL_B0_TXD_CTL_CMD_IPCSO;

			अगर (buff->is_udp_cso || buff->is_tcp_cso)
				txd->ctl |= HW_ATL_B0_TXD_CTL_CMD_TUCSO;

			अगर (is_vlan)
				txd->ctl |= HW_ATL_B0_TXD_CTL_CMD_VLAN;

			अगर (unlikely(buff->is_eop)) अणु
				txd->ctl |= HW_ATL_B0_TXD_CTL_EOP;
				txd->ctl |= HW_ATL_B0_TXD_CTL_CMD_WB;
				is_gso = false;
				is_vlan = false;
			पूर्ण
		पूर्ण
		ring->sw_tail = aq_ring_next_dx(ring, ring->sw_tail);
	पूर्ण

	hw_atl_b0_hw_tx_ring_tail_update(self, ring);

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_ring_rx_init(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *aq_ring,
			      काष्ठा aq_ring_param_s *aq_ring_param)
अणु
	u32 dma_desc_addr_msw = (u32)(((u64)aq_ring->dx_ring_pa) >> 32);
	u32 vlan_rx_stripping = self->aq_nic_cfg->is_vlan_rx_strip;
	u32 dma_desc_addr_lsw = (u32)aq_ring->dx_ring_pa;

	hw_atl_rdm_rx_desc_en_set(self, false, aq_ring->idx);

	hw_atl_rdm_rx_desc_head_splitting_set(self, 0U, aq_ring->idx);

	hw_atl_reg_rx_dma_desc_base_addresslswset(self, dma_desc_addr_lsw,
						  aq_ring->idx);

	hw_atl_reg_rx_dma_desc_base_addressmswset(self,
						  dma_desc_addr_msw, aq_ring->idx);

	hw_atl_rdm_rx_desc_len_set(self, aq_ring->size / 8U, aq_ring->idx);

	hw_atl_rdm_rx_desc_data_buff_size_set(self,
					      AQ_CFG_RX_FRAME_MAX / 1024U,
				       aq_ring->idx);

	hw_atl_rdm_rx_desc_head_buff_size_set(self, 0U, aq_ring->idx);
	hw_atl_rdm_rx_desc_head_splitting_set(self, 0U, aq_ring->idx);
	hw_atl_rpo_rx_desc_vlan_stripping_set(self, !!vlan_rx_stripping,
					      aq_ring->idx);

	/* Rx ring set mode */

	/* Mapping पूर्णांकerrupt vector */
	hw_atl_itr_irq_map_rx_set(self, aq_ring_param->vec_idx, aq_ring->idx);
	hw_atl_itr_irq_map_en_rx_set(self, true, aq_ring->idx);

	hw_atl_rdm_cpu_id_set(self, aq_ring_param->cpu, aq_ring->idx);
	hw_atl_rdm_rx_desc_dca_en_set(self, 0U, aq_ring->idx);
	hw_atl_rdm_rx_head_dca_en_set(self, 0U, aq_ring->idx);
	hw_atl_rdm_rx_pld_dca_en_set(self, 0U, aq_ring->idx);

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_ring_tx_init(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *aq_ring,
			      काष्ठा aq_ring_param_s *aq_ring_param)
अणु
	u32 dma_desc_msw_addr = (u32)(((u64)aq_ring->dx_ring_pa) >> 32);
	u32 dma_desc_lsw_addr = (u32)aq_ring->dx_ring_pa;

	hw_atl_reg_tx_dma_desc_base_addresslswset(self, dma_desc_lsw_addr,
						  aq_ring->idx);

	hw_atl_reg_tx_dma_desc_base_addressmswset(self, dma_desc_msw_addr,
						  aq_ring->idx);

	hw_atl_tdm_tx_desc_len_set(self, aq_ring->size / 8U, aq_ring->idx);

	hw_atl_b0_hw_tx_ring_tail_update(self, aq_ring);

	/* Set Tx threshold */
	hw_atl_tdm_tx_desc_wr_wb_threshold_set(self, 0U, aq_ring->idx);

	/* Mapping पूर्णांकerrupt vector */
	hw_atl_itr_irq_map_tx_set(self, aq_ring_param->vec_idx, aq_ring->idx);
	hw_atl_itr_irq_map_en_tx_set(self, true, aq_ring->idx);

	hw_atl_tdm_cpu_id_set(self, aq_ring_param->cpu, aq_ring->idx);
	hw_atl_tdm_tx_desc_dca_en_set(self, 0U, aq_ring->idx);

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_ring_rx_fill(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring,
			      अचिन्हित पूर्णांक sw_tail_old)
अणु
	क्रम (; sw_tail_old != ring->sw_tail;
		sw_tail_old = aq_ring_next_dx(ring, sw_tail_old)) अणु
		काष्ठा hw_atl_rxd_s *rxd =
			(काष्ठा hw_atl_rxd_s *)&ring->dx_ring[sw_tail_old *
							HW_ATL_B0_RXD_SIZE];

		काष्ठा aq_ring_buff_s *buff = &ring->buff_ring[sw_tail_old];

		rxd->buf_addr = buff->pa;
		rxd->hdr_addr = 0U;
	पूर्ण

	hw_atl_reg_rx_dma_desc_tail_ptr_set(self, sw_tail_old, ring->idx);

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_ring_hwts_rx_fill(काष्ठा aq_hw_s *self,
					  काष्ठा aq_ring_s *ring)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = aq_ring_avail_dx(ring); i--;
			ring->sw_tail = aq_ring_next_dx(ring, ring->sw_tail)) अणु
		काष्ठा hw_atl_rxd_s *rxd =
			(काष्ठा hw_atl_rxd_s *)
			&ring->dx_ring[ring->sw_tail * HW_ATL_B0_RXD_SIZE];

		rxd->buf_addr = ring->dx_ring_pa + ring->size * ring->dx_size;
		rxd->hdr_addr = 0U;
	पूर्ण
	/* Make sure descriptors are updated beक्रमe bump tail*/
	wmb();

	hw_atl_reg_rx_dma_desc_tail_ptr_set(self, ring->sw_tail, ring->idx);

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_ring_hwts_rx_receive(काष्ठा aq_hw_s *self,
					     काष्ठा aq_ring_s *ring)
अणु
	जबतक (ring->hw_head != ring->sw_tail) अणु
		काष्ठा hw_atl_rxd_hwts_wb_s *hwts_wb =
			(काष्ठा hw_atl_rxd_hwts_wb_s *)
			(ring->dx_ring + (ring->hw_head * HW_ATL_B0_RXD_SIZE));

		/* RxD is not करोne */
		अगर (!(hwts_wb->sec_lw0 & 0x1U))
			अवरोध;

		ring->hw_head = aq_ring_next_dx(ring, ring->hw_head);
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_ring_tx_head_update(काष्ठा aq_hw_s *self,
				     काष्ठा aq_ring_s *ring)
अणु
	अचिन्हित पूर्णांक hw_head_;
	पूर्णांक err = 0;

	hw_head_ = hw_atl_tdm_tx_desc_head_ptr_get(self, ring->idx);

	अगर (aq_utils_obj_test(&self->flags, AQ_HW_FLAG_ERR_UNPLUG)) अणु
		err = -ENXIO;
		जाओ err_निकास;
	पूर्ण
	ring->hw_head = hw_head_;
	err = aq_hw_err_from_flags(self);

err_निकास:
	वापस err;
पूर्ण

पूर्णांक hw_atl_b0_hw_ring_rx_receive(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring)
अणु
	क्रम (; ring->hw_head != ring->sw_tail;
		ring->hw_head = aq_ring_next_dx(ring, ring->hw_head)) अणु
		काष्ठा aq_ring_buff_s *buff = शून्य;
		काष्ठा hw_atl_rxd_wb_s *rxd_wb = (काष्ठा hw_atl_rxd_wb_s *)
			&ring->dx_ring[ring->hw_head * HW_ATL_B0_RXD_SIZE];

		अचिन्हित पूर्णांक is_rx_check_sum_enabled = 0U;
		अचिन्हित पूर्णांक pkt_type = 0U;
		u8 rx_stat = 0U;

		अगर (!(rxd_wb->status & 0x1U)) अणु /* RxD is not करोne */
			अवरोध;
		पूर्ण

		buff = &ring->buff_ring[ring->hw_head];

		buff->flags = 0U;
		buff->is_hash_l4 = 0U;

		rx_stat = (0x0000003CU & rxd_wb->status) >> 2;

		is_rx_check_sum_enabled = (rxd_wb->type >> 19) & 0x3U;

		pkt_type = (rxd_wb->type & HW_ATL_B0_RXD_WB_STAT_PKTTYPE) >>
			   HW_ATL_B0_RXD_WB_STAT_PKTTYPE_SHIFT;

		अगर (is_rx_check_sum_enabled & BIT(0) &&
		    (0x0U == (pkt_type & 0x3U)))
			buff->is_ip_cso = (rx_stat & BIT(1)) ? 0U : 1U;

		अगर (is_rx_check_sum_enabled & BIT(1)) अणु
			अगर (0x4U == (pkt_type & 0x1CU))
				buff->is_udp_cso = (rx_stat & BIT(2)) ? 0U :
						   !!(rx_stat & BIT(3));
			अन्यथा अगर (0x0U == (pkt_type & 0x1CU))
				buff->is_tcp_cso = (rx_stat & BIT(2)) ? 0U :
						   !!(rx_stat & BIT(3));
		पूर्ण
		buff->is_cso_err = !!(rx_stat & 0x6);
		/* Checksum offload workaround क्रम small packets */
		अगर (unlikely(rxd_wb->pkt_len <= 60)) अणु
			buff->is_ip_cso = 0U;
			buff->is_cso_err = 0U;
		पूर्ण

		अगर (self->aq_nic_cfg->is_vlan_rx_strip &&
		    ((pkt_type & HW_ATL_B0_RXD_WB_PKTTYPE_VLAN) ||
		     (pkt_type & HW_ATL_B0_RXD_WB_PKTTYPE_VLAN_DOUBLE))) अणु
			buff->is_vlan = 1;
			buff->vlan_rx_tag = le16_to_cpu(rxd_wb->vlan);
		पूर्ण

		अगर ((rx_stat & BIT(0)) || rxd_wb->type & 0x1000U) अणु
			/* MAC error or DMA error */
			buff->is_error = 1U;
		पूर्ण
		अगर (self->aq_nic_cfg->is_rss) अणु
			/* last 4 byte */
			u16 rss_type = rxd_wb->type & 0xFU;

			अगर (rss_type && rss_type < 0x8U) अणु
				buff->is_hash_l4 = (rss_type == 0x4 ||
				rss_type == 0x5);
				buff->rss_hash = rxd_wb->rss_hash;
			पूर्ण
		पूर्ण

		buff->is_lro = !!(HW_ATL_B0_RXD_WB_STAT2_RSCCNT &
				  rxd_wb->status);
		अगर (HW_ATL_B0_RXD_WB_STAT2_EOP & rxd_wb->status) अणु
			buff->len = rxd_wb->pkt_len %
				AQ_CFG_RX_FRAME_MAX;
			buff->len = buff->len ?
				buff->len : AQ_CFG_RX_FRAME_MAX;
			buff->next = 0U;
			buff->is_eop = 1U;
		पूर्ण अन्यथा अणु
			buff->len =
				rxd_wb->pkt_len > AQ_CFG_RX_FRAME_MAX ?
				AQ_CFG_RX_FRAME_MAX : rxd_wb->pkt_len;

			अगर (buff->is_lro) अणु
				/* LRO */
				buff->next = rxd_wb->next_desc_ptr;
				++ring->stats.rx.lro_packets;
			पूर्ण अन्यथा अणु
				/* jumbo */
				buff->next =
					aq_ring_next_dx(ring,
							ring->hw_head);
				++ring->stats.rx.jumbo_packets;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_irq_enable(काष्ठा aq_hw_s *self, u64 mask)
अणु
	hw_atl_itr_irq_msk_setlsw_set(self, LODWORD(mask));

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_irq_disable(काष्ठा aq_hw_s *self, u64 mask)
अणु
	hw_atl_itr_irq_msk_clearlsw_set(self, LODWORD(mask));
	hw_atl_itr_irq_status_clearlsw_set(self, LODWORD(mask));

	atomic_inc(&self->dpc);

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_irq_पढ़ो(काष्ठा aq_hw_s *self, u64 *mask)
अणु
	*mask = hw_atl_itr_irq_statuslsw_get(self);

	वापस aq_hw_err_from_flags(self);
पूर्ण

#घोषणा IS_FILTER_ENABLED(_F_) ((packet_filter & (_F_)) ? 1U : 0U)

पूर्णांक hw_atl_b0_hw_packet_filter_set(काष्ठा aq_hw_s *self,
				   अचिन्हित पूर्णांक packet_filter)
अणु
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;
	अचिन्हित पूर्णांक i = 0U;
	u32 vlan_promisc;
	u32 l2_promisc;

	l2_promisc = IS_FILTER_ENABLED(IFF_PROMISC) ||
		     !!(cfg->priv_flags & BIT(AQ_HW_LOOPBACK_DMA_NET));
	vlan_promisc = l2_promisc || cfg->is_vlan_क्रमce_promisc;

	hw_atl_rpfl2promiscuous_mode_en_set(self, l2_promisc);

	hw_atl_rpf_vlan_prom_mode_en_set(self, vlan_promisc);

	hw_atl_rpfl2multicast_flr_en_set(self,
					 IS_FILTER_ENABLED(IFF_ALLMULTI) &&
					 IS_FILTER_ENABLED(IFF_MULTICAST), 0);

	hw_atl_rpfl2_accept_all_mc_packets_set(self,
					      IS_FILTER_ENABLED(IFF_ALLMULTI) &&
					      IS_FILTER_ENABLED(IFF_MULTICAST));

	hw_atl_rpfl2broadcast_en_set(self, IS_FILTER_ENABLED(IFF_BROADCAST));


	क्रम (i = HW_ATL_B0_MAC_MIN; i < HW_ATL_B0_MAC_MAX; ++i)
		hw_atl_rpfl2_uc_flr_en_set(self,
					   (cfg->is_mc_list_enabled &&
					    (i <= cfg->mc_list_count)) ?
					   1U : 0U, i);

	वापस aq_hw_err_from_flags(self);
पूर्ण

#अघोषित IS_FILTER_ENABLED

अटल पूर्णांक hw_atl_b0_hw_multicast_list_set(काष्ठा aq_hw_s *self,
					   u8 ar_mac
					   [AQ_HW_MULTICAST_ADDRESS_MAX]
					   [ETH_ALEN],
					   u32 count)
अणु
	पूर्णांक err = 0;
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;

	अगर (count > (HW_ATL_B0_MAC_MAX - HW_ATL_B0_MAC_MIN)) अणु
		err = -EBADRQC;
		जाओ err_निकास;
	पूर्ण
	क्रम (cfg->mc_list_count = 0U;
			cfg->mc_list_count < count;
			++cfg->mc_list_count) अणु
		u32 i = cfg->mc_list_count;
		u32 h = (ar_mac[i][0] << 8) | (ar_mac[i][1]);
		u32 l = (ar_mac[i][2] << 24) | (ar_mac[i][3] << 16) |
					(ar_mac[i][4] << 8) | ar_mac[i][5];

		hw_atl_rpfl2_uc_flr_en_set(self, 0U, HW_ATL_B0_MAC_MIN + i);

		hw_atl_rpfl2unicast_dest_addresslsw_set(self, l,
							HW_ATL_B0_MAC_MIN + i);

		hw_atl_rpfl2unicast_dest_addressmsw_set(self, h,
							HW_ATL_B0_MAC_MIN + i);

		hw_atl_rpfl2_uc_flr_en_set(self,
					   (cfg->is_mc_list_enabled),
					   HW_ATL_B0_MAC_MIN + i);
	पूर्ण

	err = aq_hw_err_from_flags(self);

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_पूर्णांकerrupt_moderation_set(काष्ठा aq_hw_s *self)
अणु
	अचिन्हित पूर्णांक i = 0U;
	u32 itr_tx = 2U;
	u32 itr_rx = 2U;

	चयन (self->aq_nic_cfg->itr) अणु
	हाल  AQ_CFG_INTERRUPT_MODERATION_ON:
	हाल  AQ_CFG_INTERRUPT_MODERATION_AUTO:
		hw_atl_tdm_tx_desc_wr_wb_irq_en_set(self, 0U);
		hw_atl_tdm_tdm_पूर्णांकr_moder_en_set(self, 1U);
		hw_atl_rdm_rx_desc_wr_wb_irq_en_set(self, 0U);
		hw_atl_rdm_rdm_पूर्णांकr_moder_en_set(self, 1U);

		अगर (self->aq_nic_cfg->itr == AQ_CFG_INTERRUPT_MODERATION_ON) अणु
			/* HW समयrs are in 2us units */
			पूर्णांक tx_max_समयr = self->aq_nic_cfg->tx_itr / 2;
			पूर्णांक tx_min_समयr = tx_max_समयr / 2;

			पूर्णांक rx_max_समयr = self->aq_nic_cfg->rx_itr / 2;
			पूर्णांक rx_min_समयr = rx_max_समयr / 2;

			tx_max_समयr = min(HW_ATL_INTR_MODER_MAX, tx_max_समयr);
			tx_min_समयr = min(HW_ATL_INTR_MODER_MIN, tx_min_समयr);
			rx_max_समयr = min(HW_ATL_INTR_MODER_MAX, rx_max_समयr);
			rx_min_समयr = min(HW_ATL_INTR_MODER_MIN, rx_min_समयr);

			itr_tx |= tx_min_समयr << 0x8U;
			itr_tx |= tx_max_समयr << 0x10U;
			itr_rx |= rx_min_समयr << 0x8U;
			itr_rx |= rx_max_समयr << 0x10U;
		पूर्ण अन्यथा अणु
			अटल अचिन्हित पूर्णांक hw_atl_b0_समयrs_table_tx_[][2] = अणु
				अणु0xfU, 0xffUपूर्ण, /* 10Gbit */
				अणु0xfU, 0x1ffUपूर्ण, /* 5Gbit */
				अणु0xfU, 0x1ffUपूर्ण, /* 5Gbit 5GS */
				अणु0xfU, 0x1ffUपूर्ण, /* 2.5Gbit */
				अणु0xfU, 0x1ffUपूर्ण, /* 1Gbit */
				अणु0xfU, 0x1ffUपूर्ण, /* 100Mbit */
			पूर्ण;

			अटल अचिन्हित पूर्णांक hw_atl_b0_समयrs_table_rx_[][2] = अणु
				अणु0x6U, 0x38Uपूर्ण,/* 10Gbit */
				अणु0xCU, 0x70Uपूर्ण,/* 5Gbit */
				अणु0xCU, 0x70Uपूर्ण,/* 5Gbit 5GS */
				अणु0x18U, 0xE0Uपूर्ण,/* 2.5Gbit */
				अणु0x30U, 0x80Uपूर्ण,/* 1Gbit */
				अणु0x4U, 0x50Uपूर्ण,/* 100Mbit */
			पूर्ण;

			अचिन्हित पूर्णांक speed_index =
					hw_atl_utils_mbps_2_speed_index(
						self->aq_link_status.mbps);

			/* Update user visible ITR settings */
			self->aq_nic_cfg->tx_itr = hw_atl_b0_समयrs_table_tx_
							[speed_index][1] * 2;
			self->aq_nic_cfg->rx_itr = hw_atl_b0_समयrs_table_rx_
							[speed_index][1] * 2;

			itr_tx |= hw_atl_b0_समयrs_table_tx_
						[speed_index][0] << 0x8U;
			itr_tx |= hw_atl_b0_समयrs_table_tx_
						[speed_index][1] << 0x10U;

			itr_rx |= hw_atl_b0_समयrs_table_rx_
						[speed_index][0] << 0x8U;
			itr_rx |= hw_atl_b0_समयrs_table_rx_
						[speed_index][1] << 0x10U;
		पूर्ण
		अवरोध;
	हाल AQ_CFG_INTERRUPT_MODERATION_OFF:
		hw_atl_tdm_tx_desc_wr_wb_irq_en_set(self, 1U);
		hw_atl_tdm_tdm_पूर्णांकr_moder_en_set(self, 0U);
		hw_atl_rdm_rx_desc_wr_wb_irq_en_set(self, 1U);
		hw_atl_rdm_rdm_पूर्णांकr_moder_en_set(self, 0U);
		itr_tx = 0U;
		itr_rx = 0U;
		अवरोध;
	पूर्ण

	क्रम (i = HW_ATL_B0_RINGS_MAX; i--;) अणु
		hw_atl_reg_tx_पूर्णांकr_moder_ctrl_set(self, itr_tx, i);
		hw_atl_reg_rx_पूर्णांकr_moder_ctrl_set(self, itr_rx, i);
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_stop(काष्ठा aq_hw_s *self)
अणु
	पूर्णांक err;
	u32 val;

	hw_atl_b0_hw_irq_disable(self, HW_ATL_B0_INT_MASK);

	/* Invalidate Descriptor Cache to prevent writing to the cached
	 * descriptors and to the data poपूर्णांकer of those descriptors
	 */
	hw_atl_rdm_rx_dma_desc_cache_init_tgl(self);

	err = aq_hw_err_from_flags(self);

	अगर (err)
		जाओ err_निकास;

	पढ़ोx_poll_समयout_atomic(hw_atl_rdm_rx_dma_desc_cache_init_करोne_get,
				  self, val, val == 1, 1000U, 10000U);

err_निकास:
	वापस err;
पूर्ण

पूर्णांक hw_atl_b0_hw_ring_tx_stop(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring)
अणु
	hw_atl_tdm_tx_desc_en_set(self, 0U, ring->idx);

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_hw_ring_rx_stop(काष्ठा aq_hw_s *self, काष्ठा aq_ring_s *ring)
अणु
	hw_atl_rdm_rx_desc_en_set(self, 0U, ring->idx);

	वापस aq_hw_err_from_flags(self);
पूर्ण

#घोषणा get_ptp_ts_val_u64(self, indx) \
	((u64)(hw_atl_pcs_ptp_घड़ी_get(self, indx) & 0xffff))

अटल व्योम hw_atl_b0_get_ptp_ts(काष्ठा aq_hw_s *self, u64 *stamp)
अणु
	u64 ns;

	hw_atl_pcs_ptp_घड़ी_पढ़ो_enable(self, 1);
	hw_atl_pcs_ptp_घड़ी_पढ़ो_enable(self, 0);
	ns = (get_ptp_ts_val_u64(self, 0) +
	      (get_ptp_ts_val_u64(self, 1) << 16)) * NSEC_PER_SEC +
	     (get_ptp_ts_val_u64(self, 3) +
	      (get_ptp_ts_val_u64(self, 4) << 16));

	*stamp = ns + self->ptp_clk_offset;
पूर्ण

अटल व्योम hw_atl_b0_adj_params_get(u64 freq, s64 adj, u32 *ns, u32 *fns)
अणु
	/* For accuracy, the digit is extended */
	s64 base_ns = ((adj + NSEC_PER_SEC) * NSEC_PER_SEC);
	u64 nsi_frac = 0;
	u64 nsi;

	base_ns = भाग64_s64(base_ns, freq);
	nsi = भाग64_u64(base_ns, NSEC_PER_SEC);

	अगर (base_ns != nsi * NSEC_PER_SEC) अणु
		s64 भागisor = भाग64_s64((s64)NSEC_PER_SEC * NSEC_PER_SEC,
					base_ns - nsi * NSEC_PER_SEC);
		nsi_frac = भाग64_s64(AQ_FRAC_PER_NS * NSEC_PER_SEC, भागisor);
	पूर्ण

	*ns = (u32)nsi;
	*fns = (u32)nsi_frac;
पूर्ण

अटल व्योम
hw_atl_b0_mac_adj_param_calc(काष्ठा hw_fw_request_ptp_adj_freq *ptp_adj_freq,
			     u64 phyfreq, u64 macfreq)
अणु
	s64 adj_fns_val;
	s64 fns_in_sec_phy = phyfreq * (ptp_adj_freq->fns_phy +
					AQ_FRAC_PER_NS * ptp_adj_freq->ns_phy);
	s64 fns_in_sec_mac = macfreq * (ptp_adj_freq->fns_mac +
					AQ_FRAC_PER_NS * ptp_adj_freq->ns_mac);
	s64 fault_in_sec_phy = AQ_FRAC_PER_NS * NSEC_PER_SEC - fns_in_sec_phy;
	s64 fault_in_sec_mac = AQ_FRAC_PER_NS * NSEC_PER_SEC - fns_in_sec_mac;
	/* MAC MCP counter freq is macfreq / 4 */
	s64 dअगरf_in_mcp_overflow = (fault_in_sec_mac - fault_in_sec_phy) *
				   4 * AQ_FRAC_PER_NS;

	dअगरf_in_mcp_overflow = भाग64_s64(dअगरf_in_mcp_overflow,
					 AQ_HW_MAC_COUNTER_HZ);
	adj_fns_val = (ptp_adj_freq->fns_mac + AQ_FRAC_PER_NS *
		       ptp_adj_freq->ns_mac) + dअगरf_in_mcp_overflow;

	ptp_adj_freq->mac_ns_adj = भाग64_s64(adj_fns_val, AQ_FRAC_PER_NS);
	ptp_adj_freq->mac_fns_adj = adj_fns_val - ptp_adj_freq->mac_ns_adj *
				    AQ_FRAC_PER_NS;
पूर्ण

अटल पूर्णांक hw_atl_b0_adj_sys_घड़ी(काष्ठा aq_hw_s *self, s64 delta)
अणु
	self->ptp_clk_offset += delta;

	self->aq_fw_ops->adjust_ptp(self, self->ptp_clk_offset);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_atl_b0_set_sys_घड़ी(काष्ठा aq_hw_s *self, u64 समय, u64 ts)
अणु
	s64 delta = समय - (self->ptp_clk_offset + ts);

	वापस hw_atl_b0_adj_sys_घड़ी(self, delta);
पूर्ण

अटल पूर्णांक hw_atl_b0_ts_to_sys_घड़ी(काष्ठा aq_hw_s *self, u64 ts, u64 *समय)
अणु
	*समय = self->ptp_clk_offset + ts;
	वापस 0;
पूर्ण

अटल पूर्णांक hw_atl_b0_adj_घड़ी_freq(काष्ठा aq_hw_s *self, s32 ppb)
अणु
	काष्ठा hw_fw_request_अगरace fwreq;
	माप_प्रकार size;

	स_रखो(&fwreq, 0, माप(fwreq));

	fwreq.msg_id = HW_AQ_FW_REQUEST_PTP_ADJ_FREQ;
	hw_atl_b0_adj_params_get(AQ_HW_MAC_COUNTER_HZ, ppb,
				 &fwreq.ptp_adj_freq.ns_mac,
				 &fwreq.ptp_adj_freq.fns_mac);
	hw_atl_b0_adj_params_get(AQ_HW_PHY_COUNTER_HZ, ppb,
				 &fwreq.ptp_adj_freq.ns_phy,
				 &fwreq.ptp_adj_freq.fns_phy);
	hw_atl_b0_mac_adj_param_calc(&fwreq.ptp_adj_freq,
				     AQ_HW_PHY_COUNTER_HZ,
				     AQ_HW_MAC_COUNTER_HZ);

	size = माप(fwreq.msg_id) + माप(fwreq.ptp_adj_freq);
	वापस self->aq_fw_ops->send_fw_request(self, &fwreq, size);
पूर्ण

अटल पूर्णांक hw_atl_b0_gpio_pulse(काष्ठा aq_hw_s *self, u32 index,
				u64 start, u32 period)
अणु
	काष्ठा hw_fw_request_अगरace fwreq;
	माप_प्रकार size;

	स_रखो(&fwreq, 0, माप(fwreq));

	fwreq.msg_id = HW_AQ_FW_REQUEST_PTP_GPIO_CTRL;
	fwreq.ptp_gpio_ctrl.index = index;
	fwreq.ptp_gpio_ctrl.period = period;
	/* Apply समय offset */
	fwreq.ptp_gpio_ctrl.start = start;

	size = माप(fwreq.msg_id) + माप(fwreq.ptp_gpio_ctrl);
	वापस self->aq_fw_ops->send_fw_request(self, &fwreq, size);
पूर्ण

अटल पूर्णांक hw_atl_b0_extts_gpio_enable(काष्ठा aq_hw_s *self, u32 index,
				       u32 enable)
अणु
	/* Enable/disable Sync1588 GPIO Timestamping */
	aq_phy_ग_लिखो_reg(self, MDIO_MMD_PCS, 0xc611, enable ? 0x71 : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_atl_b0_get_sync_ts(काष्ठा aq_hw_s *self, u64 *ts)
अणु
	u64 sec_l;
	u64 sec_h;
	u64 nsec_l;
	u64 nsec_h;

	अगर (!ts)
		वापस -1;

	/* PTP बाह्यal GPIO घड़ी seconds count 15:0 */
	sec_l = aq_phy_पढ़ो_reg(self, MDIO_MMD_PCS, 0xc914);
	/* PTP बाह्यal GPIO घड़ी seconds count 31:16 */
	sec_h = aq_phy_पढ़ो_reg(self, MDIO_MMD_PCS, 0xc915);
	/* PTP बाह्यal GPIO घड़ी nanoseconds count 15:0 */
	nsec_l = aq_phy_पढ़ो_reg(self, MDIO_MMD_PCS, 0xc916);
	/* PTP बाह्यal GPIO घड़ी nanoseconds count 31:16 */
	nsec_h = aq_phy_पढ़ो_reg(self, MDIO_MMD_PCS, 0xc917);

	*ts = (nsec_h << 16) + nsec_l + ((sec_h << 16) + sec_l) * NSEC_PER_SEC;

	वापस 0;
पूर्ण

अटल u16 hw_atl_b0_rx_extract_ts(काष्ठा aq_hw_s *self, u8 *p,
				   अचिन्हित पूर्णांक len, u64 *बारtamp)
अणु
	अचिन्हित पूर्णांक offset = 14;
	काष्ठा ethhdr *eth;
	__be64 sec;
	__be32 ns;
	u8 *ptr;

	अगर (len <= offset || !बारtamp)
		वापस 0;

	/* The TIMESTAMP in the end of package has following क्रमmat:
	 * (big-endian)
	 *   काष्ठा अणु
	 *     uपूर्णांक64_t sec;
	 *     uपूर्णांक32_t ns;
	 *     uपूर्णांक16_t stream_id;
	 *   पूर्ण;
	 */
	ptr = p + (len - offset);
	स_नकल(&sec, ptr, माप(sec));
	ptr += माप(sec);
	स_नकल(&ns, ptr, माप(ns));

	*बारtamp = (be64_to_cpu(sec) & 0xffffffffffffllu) * NSEC_PER_SEC +
		     be32_to_cpu(ns) + self->ptp_clk_offset;

	eth = (काष्ठा ethhdr *)p;

	वापस (eth->h_proto == htons(ETH_P_1588)) ? 12 : 14;
पूर्ण

अटल पूर्णांक hw_atl_b0_extract_hwts(काष्ठा aq_hw_s *self, u8 *p, अचिन्हित पूर्णांक len,
				  u64 *बारtamp)
अणु
	काष्ठा hw_atl_rxd_hwts_wb_s *hwts_wb = (काष्ठा hw_atl_rxd_hwts_wb_s *)p;
	u64 पंचांगp, sec, ns;

	sec = 0;
	पंचांगp = (hwts_wb->sec_lw0 >> 2) & 0x3ff;
	sec += पंचांगp;
	पंचांगp = (u64)((hwts_wb->sec_lw1 >> 16) & 0xffff) << 10;
	sec += पंचांगp;
	पंचांगp = (u64)(hwts_wb->sec_hw & 0xfff) << 26;
	sec += पंचांगp;
	पंचांगp = (u64)((hwts_wb->sec_hw >> 22) & 0x3ff) << 38;
	sec += पंचांगp;
	ns = sec * NSEC_PER_SEC + hwts_wb->ns;
	अगर (बारtamp)
		*बारtamp = ns + self->ptp_clk_offset;
	वापस 0;
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_fl3l4_clear(काष्ठा aq_hw_s *self,
				    काष्ठा aq_rx_filter_l3l4 *data)
अणु
	u8 location = data->location;

	अगर (!data->is_ipv6) अणु
		hw_atl_rpfl3l4_cmd_clear(self, location);
		hw_atl_rpf_l4_spd_set(self, 0U, location);
		hw_atl_rpf_l4_dpd_set(self, 0U, location);
		hw_atl_rpfl3l4_ipv4_src_addr_clear(self, location);
		hw_atl_rpfl3l4_ipv4_dest_addr_clear(self, location);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < HW_ATL_RX_CNT_REG_ADDR_IPV6; ++i) अणु
			hw_atl_rpfl3l4_cmd_clear(self, location + i);
			hw_atl_rpf_l4_spd_set(self, 0U, location + i);
			hw_atl_rpf_l4_dpd_set(self, 0U, location + i);
		पूर्ण
		hw_atl_rpfl3l4_ipv6_src_addr_clear(self, location);
		hw_atl_rpfl3l4_ipv6_dest_addr_clear(self, location);
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_fl3l4_set(काष्ठा aq_hw_s *self,
				  काष्ठा aq_rx_filter_l3l4 *data)
अणु
	u8 location = data->location;

	hw_atl_b0_hw_fl3l4_clear(self, data);

	अगर (data->cmd & (HW_ATL_RX_ENABLE_CMP_DEST_ADDR_L3 |
			 HW_ATL_RX_ENABLE_CMP_SRC_ADDR_L3)) अणु
		अगर (!data->is_ipv6) अणु
			hw_atl_rpfl3l4_ipv4_dest_addr_set(self,
							  location,
							  data->ip_dst[0]);
			hw_atl_rpfl3l4_ipv4_src_addr_set(self,
							 location,
							 data->ip_src[0]);
		पूर्ण अन्यथा अणु
			hw_atl_rpfl3l4_ipv6_dest_addr_set(self,
							  location,
							  data->ip_dst);
			hw_atl_rpfl3l4_ipv6_src_addr_set(self,
							 location,
							 data->ip_src);
		पूर्ण
	पूर्ण

	अगर (data->cmd & (HW_ATL_RX_ENABLE_CMP_DEST_PORT_L4 |
			 HW_ATL_RX_ENABLE_CMP_SRC_PORT_L4)) अणु
		hw_atl_rpf_l4_dpd_set(self, data->p_dst, location);
		hw_atl_rpf_l4_spd_set(self, data->p_src, location);
	पूर्ण

	hw_atl_rpfl3l4_cmd_set(self, location, data->cmd);

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_fl2_set(काष्ठा aq_hw_s *self,
				काष्ठा aq_rx_filter_l2 *data)
अणु
	hw_atl_rpf_etht_flr_en_set(self, 1U, data->location);
	hw_atl_rpf_etht_flr_set(self, data->ethertype, data->location);
	hw_atl_rpf_etht_user_priority_en_set(self,
					     !!data->user_priority_en,
					     data->location);
	अगर (data->user_priority_en)
		hw_atl_rpf_etht_user_priority_set(self,
						  data->user_priority,
						  data->location);

	अगर (data->queue < 0) अणु
		hw_atl_rpf_etht_flr_act_set(self, 0U, data->location);
		hw_atl_rpf_etht_rx_queue_en_set(self, 0U, data->location);
	पूर्ण अन्यथा अणु
		hw_atl_rpf_etht_flr_act_set(self, 1U, data->location);
		hw_atl_rpf_etht_rx_queue_en_set(self, 1U, data->location);
		hw_atl_rpf_etht_rx_queue_set(self, data->queue, data->location);
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_fl2_clear(काष्ठा aq_hw_s *self,
				  काष्ठा aq_rx_filter_l2 *data)
अणु
	hw_atl_rpf_etht_flr_en_set(self, 0U, data->location);
	hw_atl_rpf_etht_flr_set(self, 0U, data->location);
	hw_atl_rpf_etht_user_priority_en_set(self, 0U, data->location);

	वापस aq_hw_err_from_flags(self);
पूर्ण

/*
 * @brief Set VLAN filter table
 * @details Configure VLAN filter table to accept (and assign the queue) traffic
 *  क्रम the particular vlan ids.
 * Note: use this function under vlan promisc mode not to lost the traffic
 *
 * @param aq_hw_s
 * @param aq_rx_filter_vlan VLAN filter configuration
 * @वापस 0 - OK, <0 - error
 */
अटल पूर्णांक hw_atl_b0_hw_vlan_set(काष्ठा aq_hw_s *self,
				 काष्ठा aq_rx_filter_vlan *aq_vlans)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AQ_VLAN_MAX_FILTERS; i++) अणु
		hw_atl_rpf_vlan_flr_en_set(self, 0U, i);
		hw_atl_rpf_vlan_rxq_en_flr_set(self, 0U, i);
		अगर (aq_vlans[i].enable) अणु
			hw_atl_rpf_vlan_id_flr_set(self,
						   aq_vlans[i].vlan_id,
						   i);
			hw_atl_rpf_vlan_flr_act_set(self, 1U, i);
			hw_atl_rpf_vlan_flr_en_set(self, 1U, i);
			अगर (aq_vlans[i].queue != 0xFF) अणु
				hw_atl_rpf_vlan_rxq_flr_set(self,
							    aq_vlans[i].queue,
							    i);
				hw_atl_rpf_vlan_rxq_en_flr_set(self, 1U, i);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl_b0_hw_vlan_ctrl(काष्ठा aq_hw_s *self, bool enable)
अणु
	/* set promisc in हाल of disabing the vland filter */
	hw_atl_rpf_vlan_prom_mode_en_set(self, !enable);

	वापस aq_hw_err_from_flags(self);
पूर्ण

पूर्णांक hw_atl_b0_set_loopback(काष्ठा aq_hw_s *self, u32 mode, bool enable)
अणु
	चयन (mode) अणु
	हाल AQ_HW_LOOPBACK_DMA_SYS:
		hw_atl_tpb_tx_dma_sys_lbk_en_set(self, enable);
		hw_atl_rpb_dma_sys_lbk_set(self, enable);
		अवरोध;
	हाल AQ_HW_LOOPBACK_PKT_SYS:
		hw_atl_tpo_tx_pkt_sys_lbk_en_set(self, enable);
		hw_atl_rpf_tpo_to_rpf_sys_lbk_set(self, enable);
		अवरोध;
	हाल AQ_HW_LOOPBACK_DMA_NET:
		hw_atl_rpf_vlan_prom_mode_en_set(self, enable);
		hw_atl_rpfl2promiscuous_mode_en_set(self, enable);
		hw_atl_tpb_tx_tx_clk_gate_en_set(self, !enable);
		hw_atl_tpb_tx_dma_net_lbk_en_set(self, enable);
		hw_atl_rpb_dma_net_lbk_set(self, enable);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 hw_atl_b0_ts_पढ़ोy_and_latch_high_get(काष्ठा aq_hw_s *self)
अणु
	अगर (hw_atl_ts_पढ़ोy_get(self) && hw_atl_ts_पढ़ोy_latch_high_get(self))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक hw_atl_b0_get_mac_temp(काष्ठा aq_hw_s *self, u32 *temp)
अणु
	bool ts_disabled;
	पूर्णांक err;
	u32 val;
	u32 ts;

	ts_disabled = (hw_atl_ts_घातer_करोwn_get(self) == 1U);

	अगर (ts_disabled) अणु
		// Set AFE Temperature Sensor to on (off by शेष)
		hw_atl_ts_घातer_करोwn_set(self, 0U);

		// Reset पूर्णांकernal capacitors, biasing, and counters
		hw_atl_ts_reset_set(self, 1);
		hw_atl_ts_reset_set(self, 0);
	पूर्ण

	err = पढ़ोx_poll_समयout(hw_atl_b0_ts_पढ़ोy_and_latch_high_get, self,
				 val, val == 1, 10000U, 500000U);
	अगर (err)
		वापस err;

	ts = hw_atl_ts_data_get(self);
	*temp = ts * ts * 16 / 100000 + 60 * ts - 83410;

	अगर (ts_disabled) अणु
		// Set AFE Temperature Sensor back to off
		hw_atl_ts_घातer_करोwn_set(self, 1U);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा aq_hw_ops hw_atl_ops_b0 = अणु
	.hw_soft_reset        = hw_atl_utils_soft_reset,
	.hw_prepare           = hw_atl_utils_initfw,
	.hw_set_mac_address   = hw_atl_b0_hw_mac_addr_set,
	.hw_init              = hw_atl_b0_hw_init,
	.hw_reset             = hw_atl_b0_hw_reset,
	.hw_start             = hw_atl_b0_hw_start,
	.hw_ring_tx_start     = hw_atl_b0_hw_ring_tx_start,
	.hw_ring_tx_stop      = hw_atl_b0_hw_ring_tx_stop,
	.hw_ring_rx_start     = hw_atl_b0_hw_ring_rx_start,
	.hw_ring_rx_stop      = hw_atl_b0_hw_ring_rx_stop,
	.hw_stop              = hw_atl_b0_hw_stop,

	.hw_ring_tx_xmit         = hw_atl_b0_hw_ring_tx_xmit,
	.hw_ring_tx_head_update  = hw_atl_b0_hw_ring_tx_head_update,

	.hw_ring_rx_receive      = hw_atl_b0_hw_ring_rx_receive,
	.hw_ring_rx_fill         = hw_atl_b0_hw_ring_rx_fill,

	.hw_irq_enable           = hw_atl_b0_hw_irq_enable,
	.hw_irq_disable          = hw_atl_b0_hw_irq_disable,
	.hw_irq_पढ़ो             = hw_atl_b0_hw_irq_पढ़ो,

	.hw_ring_rx_init             = hw_atl_b0_hw_ring_rx_init,
	.hw_ring_tx_init             = hw_atl_b0_hw_ring_tx_init,
	.hw_packet_filter_set        = hw_atl_b0_hw_packet_filter_set,
	.hw_filter_l2_set            = hw_atl_b0_hw_fl2_set,
	.hw_filter_l2_clear          = hw_atl_b0_hw_fl2_clear,
	.hw_filter_l3l4_set          = hw_atl_b0_hw_fl3l4_set,
	.hw_filter_vlan_set          = hw_atl_b0_hw_vlan_set,
	.hw_filter_vlan_ctrl         = hw_atl_b0_hw_vlan_ctrl,
	.hw_multicast_list_set       = hw_atl_b0_hw_multicast_list_set,
	.hw_पूर्णांकerrupt_moderation_set = hw_atl_b0_hw_पूर्णांकerrupt_moderation_set,
	.hw_rss_set                  = hw_atl_b0_hw_rss_set,
	.hw_rss_hash_set             = hw_atl_b0_hw_rss_hash_set,
	.hw_tc_rate_limit_set        = hw_atl_b0_hw_init_tx_tc_rate_limit,
	.hw_get_regs                 = hw_atl_utils_hw_get_regs,
	.hw_get_hw_stats             = hw_atl_utils_get_hw_stats,
	.hw_get_fw_version           = hw_atl_utils_get_fw_version,

	.hw_ring_hwts_rx_fill        = hw_atl_b0_hw_ring_hwts_rx_fill,
	.hw_ring_hwts_rx_receive     = hw_atl_b0_hw_ring_hwts_rx_receive,

	.hw_get_ptp_ts           = hw_atl_b0_get_ptp_ts,
	.hw_adj_sys_घड़ी        = hw_atl_b0_adj_sys_घड़ी,
	.hw_set_sys_घड़ी        = hw_atl_b0_set_sys_घड़ी,
	.hw_ts_to_sys_घड़ी      = hw_atl_b0_ts_to_sys_घड़ी,
	.hw_adj_घड़ी_freq       = hw_atl_b0_adj_घड़ी_freq,
	.hw_gpio_pulse           = hw_atl_b0_gpio_pulse,
	.hw_extts_gpio_enable    = hw_atl_b0_extts_gpio_enable,
	.hw_get_sync_ts          = hw_atl_b0_get_sync_ts,
	.rx_extract_ts           = hw_atl_b0_rx_extract_ts,
	.extract_hwts            = hw_atl_b0_extract_hwts,
	.hw_set_offload          = hw_atl_b0_hw_offload_set,
	.hw_set_loopback         = hw_atl_b0_set_loopback,
	.hw_set_fc               = hw_atl_b0_set_fc,

	.hw_get_mac_temp         = hw_atl_b0_get_mac_temp,
पूर्ण;
