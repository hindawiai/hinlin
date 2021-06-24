<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#समावेश "aq_hw.h"
#समावेश "aq_hw_utils.h"
#समावेश "aq_ring.h"
#समावेश "aq_nic.h"
#समावेश "hw_atl/hw_atl_b0.h"
#समावेश "hw_atl/hw_atl_utils.h"
#समावेश "hw_atl/hw_atl_llh.h"
#समावेश "hw_atl/hw_atl_llh_internal.h"
#समावेश "hw_atl2_utils.h"
#समावेश "hw_atl2_llh.h"
#समावेश "hw_atl2_internal.h"
#समावेश "hw_atl2_llh_internal.h"

अटल पूर्णांक hw_atl2_act_rslvr_table_set(काष्ठा aq_hw_s *self, u8 location,
				       u32 tag, u32 mask, u32 action);

#घोषणा DEFAULT_BOARD_BASIC_CAPABILITIES \
	.is_64_dma = true,		  \
	.op64bit = true,		  \
	.msix_irqs = 8U,		  \
	.irq_mask = ~0U,		  \
	.vecs = HW_ATL2_RSS_MAX,	  \
	.tcs_max = HW_ATL2_TC_MAX,	  \
	.rxd_alignment = 1U,		  \
	.rxd_size = HW_ATL2_RXD_SIZE,   \
	.rxds_max = HW_ATL2_MAX_RXD,    \
	.rxds_min = HW_ATL2_MIN_RXD,    \
	.txd_alignment = 1U,		  \
	.txd_size = HW_ATL2_TXD_SIZE,   \
	.txds_max = HW_ATL2_MAX_TXD,    \
	.txds_min = HW_ATL2_MIN_TXD,    \
	.txhwb_alignment = 4096U,	  \
	.tx_rings = HW_ATL2_TX_RINGS,   \
	.rx_rings = HW_ATL2_RX_RINGS,   \
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
			NETIF_F_GSO_PARTIAL     |     \
			NETIF_F_HW_TC,                \
	.hw_priv_flags = IFF_UNICAST_FLT, \
	.flow_control = true,		  \
	.mtu = HW_ATL2_MTU_JUMBO,	  \
	.mac_regs_count = 72,		  \
	.hw_alive_check_addr = 0x10U,     \
	.priv_data_len = माप(काष्ठा hw_atl2_priv)

स्थिर काष्ठा aq_hw_caps_s hw_atl2_caps_aqc113 = अणु
	DEFAULT_BOARD_BASIC_CAPABILITIES,
	.media_type = AQ_HW_MEDIA_TYPE_TP,
	.link_speed_msk = AQ_NIC_RATE_10G |
			  AQ_NIC_RATE_5G  |
			  AQ_NIC_RATE_2G5 |
			  AQ_NIC_RATE_1G  |
			  AQ_NIC_RATE_1G_HALF   |
			  AQ_NIC_RATE_100M      |
			  AQ_NIC_RATE_100M_HALF |
			  AQ_NIC_RATE_10M       |
			  AQ_NIC_RATE_10M_HALF,
पूर्ण;

अटल u32 hw_atl2_sem_act_rslvr_get(काष्ठा aq_hw_s *self)
अणु
	वापस hw_atl_reg_glb_cpu_sem_get(self, HW_ATL2_FW_SM_ACT_RSLVR);
पूर्ण

अटल पूर्णांक hw_atl2_hw_reset(काष्ठा aq_hw_s *self)
अणु
	काष्ठा hw_atl2_priv *priv = (काष्ठा hw_atl2_priv *)self->priv;
	पूर्णांक err;

	err = hw_atl2_utils_soft_reset(self);
	अगर (err)
		वापस err;

	स_रखो(priv, 0, माप(*priv));

	self->aq_fw_ops->set_state(self, MPI_RESET);

	err = aq_hw_err_from_flags(self);

	वापस err;
पूर्ण

अटल पूर्णांक hw_atl2_hw_queue_to_tc_map_set(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;
	अचिन्हित पूर्णांक tcs, q_per_tc;
	अचिन्हित पूर्णांक tc, q;
	u32 rx_map = 0;
	u32 tx_map = 0;

	hw_atl2_tpb_tx_tc_q_अक्रम_map_en_set(self, 1U);

	चयन (cfg->tc_mode) अणु
	हाल AQ_TC_MODE_8TCS:
		tcs = 8;
		q_per_tc = 4;
		अवरोध;
	हाल AQ_TC_MODE_4TCS:
		tcs = 4;
		q_per_tc = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (tc = 0; tc != tcs; tc++) अणु
		अचिन्हित पूर्णांक tc_q_offset = tc * q_per_tc;

		क्रम (q = tc_q_offset; q != tc_q_offset + q_per_tc; q++) अणु
			rx_map |= tc << HW_ATL2_RX_Q_TC_MAP_SHIFT(q);
			अगर (HW_ATL2_RX_Q_TC_MAP_ADR(q) !=
			    HW_ATL2_RX_Q_TC_MAP_ADR(q + 1)) अणु
				aq_hw_ग_लिखो_reg(self,
						HW_ATL2_RX_Q_TC_MAP_ADR(q),
						rx_map);
				rx_map = 0;
			पूर्ण

			tx_map |= tc << HW_ATL2_TX_Q_TC_MAP_SHIFT(q);
			अगर (HW_ATL2_TX_Q_TC_MAP_ADR(q) !=
			    HW_ATL2_TX_Q_TC_MAP_ADR(q + 1)) अणु
				aq_hw_ग_लिखो_reg(self,
						HW_ATL2_TX_Q_TC_MAP_ADR(q),
						tx_map);
				tx_map = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl2_hw_qos_set(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;
	u32 tx_buff_size = HW_ATL2_TXBUF_MAX;
	u32 rx_buff_size = HW_ATL2_RXBUF_MAX;
	अचिन्हित पूर्णांक prio = 0U;
	u32 tc = 0U;

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

	/* QoS 802.1p priority -> TC mapping */
	क्रम (prio = 0; prio < 8; ++prio)
		hw_atl_rpf_rpb_user_priority_tc_map_set(self, prio,
							cfg->prio_tc_map[prio]);

	/* ATL2 Apply ring to TC mapping */
	hw_atl2_hw_queue_to_tc_map_set(self);

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl2_hw_rss_set(काष्ठा aq_hw_s *self,
			      काष्ठा aq_rss_parameters *rss_params)
अणु
	u8 *indirection_table = rss_params->indirection_table;
	स्थिर u32 num_tcs = aq_hw_num_tcs(self);
	u32 rpf_redir2_enable;
	पूर्णांक tc;
	पूर्णांक i;

	rpf_redir2_enable = num_tcs > 4 ? 1 : 0;

	hw_atl2_rpf_redirection_table2_select_set(self, rpf_redir2_enable);

	क्रम (i = HW_ATL2_RSS_REसूचीECTION_MAX; i--;) अणु
		क्रम (tc = 0; tc != num_tcs; tc++) अणु
			hw_atl2_new_rpf_rss_redir_set(self, tc, i,
						      tc *
						      aq_hw_q_per_tc(self) +
						      indirection_table[i]);
		पूर्ण
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl2_hw_init_tx_tc_rate_limit(काष्ठा aq_hw_s *self)
अणु
	अटल स्थिर u32 max_weight = BIT(HW_ATL2_TPS_DATA_TCTWEIGHT_WIDTH) - 1;
	/* Scale factor is based on the number of bits in fractional portion */
	अटल स्थिर u32 scale = BIT(HW_ATL_TPS_DESC_RATE_Y_WIDTH);
	अटल स्थिर u32 frac_msk = HW_ATL_TPS_DESC_RATE_Y_MSK >>
				    HW_ATL_TPS_DESC_RATE_Y_SHIFT;
	स्थिर u32 link_speed = self->aq_link_status.mbps;
	काष्ठा aq_nic_cfg_s *nic_cfg = self->aq_nic_cfg;
	अचिन्हित दीर्घ num_min_rated_tcs = 0;
	u32 tc_weight[AQ_CFG_TCS_MAX];
	u32 fixed_max_credit_4b;
	u32 fixed_max_credit;
	u8 min_rate_msk = 0;
	u32 sum_weight = 0;
	पूर्णांक tc;

	/* By शेष max_credit is based upon MTU (in unit of 64b) */
	fixed_max_credit = nic_cfg->aq_hw_caps->mtu / 64;
	/* in unit of 4b */
	fixed_max_credit_4b = nic_cfg->aq_hw_caps->mtu / 4;

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
	 */
	hw_atl2_tps_tx_pkt_shed_data_arb_mode_set(self, min_rate_msk ? 1U : 0U);
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
				weight = 0x640;

			max_credit = max(2 * weight, fixed_max_credit_4b);
		पूर्ण अन्यथा अणु
			weight = 0x640;
			max_credit = 0xFFF0;
		पूर्ण

		hw_atl2_tps_tx_pkt_shed_tc_data_weight_set(self, tc, weight);
		hw_atl2_tps_tx_pkt_shed_tc_data_max_credit_set(self, tc,
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

अटल पूर्णांक hw_atl2_hw_init_tx_path(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_nic_cfg_s *nic_cfg = self->aq_nic_cfg;

	/* Tx TC/RSS number config */
	hw_atl_tpb_tps_tx_tc_mode_set(self, nic_cfg->tc_mode);

	hw_atl_thm_lso_tcp_flag_of_first_pkt_set(self, 0x0FF6U);
	hw_atl_thm_lso_tcp_flag_of_middle_pkt_set(self, 0x0FF6U);
	hw_atl_thm_lso_tcp_flag_of_last_pkt_set(self, 0x0F7FU);

	/* Tx पूर्णांकerrupts */
	hw_atl_tdm_tx_desc_wr_wb_irq_en_set(self, 1U);

	/* misc */
	hw_atl_tdm_tx_dca_en_set(self, 0U);
	hw_atl_tdm_tx_dca_mode_set(self, 0U);

	hw_atl_tpb_tx_path_scp_ins_en_set(self, 1U);

	hw_atl2_tpb_tx_buf_clk_gate_en_set(self, 0U);

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल व्योम hw_atl2_hw_init_new_rx_filters(काष्ठा aq_hw_s *self)
अणु
	काष्ठा hw_atl2_priv *priv = (काष्ठा hw_atl2_priv *)self->priv;
	u8 *prio_tc_map = self->aq_nic_cfg->prio_tc_map;
	u16 action;
	u8 index;
	पूर्णांक i;

	/* Action Resolver Table (ART) is used by RPF to decide which action
	 * to take with a packet based upon input tag and tag mask, where:
	 *  - input tag is a combination of 3-bit VLan Prio (PTP) and
	 *    29-bit concatenation of all tags from filter block;
	 *  - tag mask is a mask used क्रम matching against input tag.
	 * The input_tag is compared with the all the Requested_tags in the
	 * Record table to find a match. Action field of the selected matched
	 * REC entry is used क्रम further processing. If multiple entries match,
	 * the lowest REC entry, Action field will be selected.
	 */
	hw_atl2_rpf_act_rslvr_section_en_set(self, 0xFFFF);
	hw_atl2_rpfl2_uc_flr_tag_set(self, HW_ATL2_RPF_TAG_BASE_UC,
				     HW_ATL2_MAC_UC);
	hw_atl2_rpfl2_bc_flr_tag_set(self, HW_ATL2_RPF_TAG_BASE_UC);

	/* FW reserves the beginning of ART, thus all driver entries must
	 * start from the offset specअगरied in FW caps.
	 */
	index = priv->art_base_index + HW_ATL2_RPF_L2_PROMISC_OFF_INDEX;
	hw_atl2_act_rslvr_table_set(self, index, 0,
				    HW_ATL2_RPF_TAG_UC_MASK |
					HW_ATL2_RPF_TAG_ALLMC_MASK,
				    HW_ATL2_ACTION_DROP);

	index = priv->art_base_index + HW_ATL2_RPF_VLAN_PROMISC_OFF_INDEX;
	hw_atl2_act_rslvr_table_set(self, index, 0,
				    HW_ATL2_RPF_TAG_VLAN_MASK |
					HW_ATL2_RPF_TAG_UNTAG_MASK,
				    HW_ATL2_ACTION_DROP);

	/* Configure ART to map given VLan Prio (PCP) to the TC index क्रम
	 * RSS redirection table.
	 */
	क्रम (i = 0; i < 8; i++) अणु
		action = HW_ATL2_ACTION_ASSIGN_TC(prio_tc_map[i]);

		index = priv->art_base_index + HW_ATL2_RPF_PCP_TO_TC_INDEX + i;
		hw_atl2_act_rslvr_table_set(self, index,
					    i << HW_ATL2_RPF_TAG_PCP_OFFSET,
					    HW_ATL2_RPF_TAG_PCP_MASK, action);
	पूर्ण
पूर्ण

अटल व्योम hw_atl2_hw_new_rx_filter_vlan_promisc(काष्ठा aq_hw_s *self,
						  bool promisc)
अणु
	u16 off_action = (!promisc &&
			  !hw_atl_rpfl2promiscuous_mode_en_get(self)) ?
				HW_ATL2_ACTION_DROP : HW_ATL2_ACTION_DISABLE;
	काष्ठा hw_atl2_priv *priv = (काष्ठा hw_atl2_priv *)self->priv;
	u8 index;

	index = priv->art_base_index + HW_ATL2_RPF_VLAN_PROMISC_OFF_INDEX;
	hw_atl2_act_rslvr_table_set(self, index, 0,
				    HW_ATL2_RPF_TAG_VLAN_MASK |
				    HW_ATL2_RPF_TAG_UNTAG_MASK, off_action);
पूर्ण

अटल व्योम hw_atl2_hw_new_rx_filter_promisc(काष्ठा aq_hw_s *self, bool promisc)
अणु
	u16 off_action = promisc ? HW_ATL2_ACTION_DISABLE : HW_ATL2_ACTION_DROP;
	काष्ठा hw_atl2_priv *priv = (काष्ठा hw_atl2_priv *)self->priv;
	bool vlan_promisc_enable;
	u8 index;

	index = priv->art_base_index + HW_ATL2_RPF_L2_PROMISC_OFF_INDEX;
	hw_atl2_act_rslvr_table_set(self, index, 0,
				    HW_ATL2_RPF_TAG_UC_MASK |
				    HW_ATL2_RPF_TAG_ALLMC_MASK,
				    off_action);

	/* turn VLAN promisc mode too */
	vlan_promisc_enable = hw_atl_rpf_vlan_prom_mode_en_get(self);
	hw_atl2_hw_new_rx_filter_vlan_promisc(self, promisc |
					      vlan_promisc_enable);
पूर्ण

अटल पूर्णांक hw_atl2_act_rslvr_table_set(काष्ठा aq_hw_s *self, u8 location,
				       u32 tag, u32 mask, u32 action)
अणु
	u32 val;
	पूर्णांक err;

	err = पढ़ोx_poll_समयout_atomic(hw_atl2_sem_act_rslvr_get,
					self, val, val == 1,
					1, 10000U);
	अगर (err)
		वापस err;

	hw_atl2_rpf_act_rslvr_record_set(self, location, tag, mask,
					 action);

	hw_atl_reg_glb_cpu_sem_set(self, 1, HW_ATL2_FW_SM_ACT_RSLVR);

	वापस err;
पूर्ण

अटल पूर्णांक hw_atl2_hw_init_rx_path(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;
	पूर्णांक i;

	/* Rx TC/RSS number config */
	hw_atl_rpb_rpf_rx_traf_class_mode_set(self, cfg->tc_mode);

	/* Rx flow control */
	hw_atl_rpb_rx_flow_ctl_mode_set(self, 1U);

	hw_atl2_rpf_rss_hash_type_set(self, HW_ATL2_RPF_RSS_HASH_TYPE_ALL);

	/* RSS Ring selection */
	hw_atl_b0_hw_init_rx_rss_ctrl1(self);

	/* Multicast filters */
	क्रम (i = HW_ATL2_MAC_MAX; i--;) अणु
		hw_atl_rpfl2_uc_flr_en_set(self, (i == 0U) ? 1U : 0U, i);
		hw_atl_rpfl2unicast_flr_act_set(self, 1U, i);
	पूर्ण

	hw_atl_reg_rx_flr_mcst_flr_msk_set(self, 0x00000000U);
	hw_atl_reg_rx_flr_mcst_flr_set(self, HW_ATL_MCAST_FLT_ANY_TO_HOST, 0U);

	/* Vlan filters */
	hw_atl_rpf_vlan_outer_etht_set(self, ETH_P_8021AD);
	hw_atl_rpf_vlan_inner_etht_set(self, ETH_P_8021Q);

	hw_atl_rpf_vlan_prom_mode_en_set(self, 1);

	/* Always accept untagged packets */
	hw_atl_rpf_vlan_accept_untagged_packets_set(self, 1U);
	hw_atl_rpf_vlan_untagged_act_set(self, 1U);

	hw_atl2_hw_init_new_rx_filters(self);

	/* Rx Interrupts */
	hw_atl_rdm_rx_desc_wr_wb_irq_en_set(self, 1U);

	hw_atl_rpfl2broadcast_flr_act_set(self, 1U);
	hw_atl_rpfl2broadcast_count_threshold_set(self, 0xFFFFU & (~0U / 256U));

	hw_atl_rdm_rx_dca_en_set(self, 0U);
	hw_atl_rdm_rx_dca_mode_set(self, 0U);

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl2_hw_init(काष्ठा aq_hw_s *self, u8 *mac_addr)
अणु
	अटल u32 aq_hw_atl2_igcr_table_[4][2] = अणु
		[AQ_HW_IRQ_INVALID] = अणु 0x20000000U, 0x20000000U पूर्ण,
		[AQ_HW_IRQ_LEGACY]  = अणु 0x20000080U, 0x20000080U पूर्ण,
		[AQ_HW_IRQ_MSI]     = अणु 0x20000021U, 0x20000025U पूर्ण,
		[AQ_HW_IRQ_MSIX]    = अणु 0x20000022U, 0x20000026U पूर्ण,
	पूर्ण;

	काष्ठा hw_atl2_priv *priv = (काष्ठा hw_atl2_priv *)self->priv;
	काष्ठा aq_nic_cfg_s *aq_nic_cfg = self->aq_nic_cfg;
	u8 base_index, count;
	पूर्णांक err;

	err = hw_atl2_utils_get_action_resolve_table_caps(self, &base_index,
							  &count);
	अगर (err)
		वापस err;

	priv->art_base_index = 8 * base_index;

	hw_atl2_init_launchसमय(self);

	hw_atl2_hw_init_tx_path(self);
	hw_atl2_hw_init_rx_path(self);

	hw_atl_b0_hw_mac_addr_set(self, mac_addr);

	self->aq_fw_ops->set_link_speed(self, aq_nic_cfg->link_speed_msk);
	self->aq_fw_ops->set_state(self, MPI_INIT);

	hw_atl2_hw_qos_set(self);
	hw_atl2_hw_rss_set(self, &aq_nic_cfg->aq_rss);
	hw_atl_b0_hw_rss_hash_set(self, &aq_nic_cfg->aq_rss);

	hw_atl2_rpf_new_enable_set(self, 1);

	/* Reset link status and पढ़ो out initial hardware counters */
	self->aq_link_status.mbps = 0;
	self->aq_fw_ops->update_stats(self);

	err = aq_hw_err_from_flags(self);
	अगर (err < 0)
		जाओ err_निकास;

	/* Interrupts */
	hw_atl_reg_irq_glb_ctl_set(self,
				   aq_hw_atl2_igcr_table_[aq_nic_cfg->irq_type]
						 [(aq_nic_cfg->vecs > 1U) ?
						  1 : 0]);

	hw_atl_itr_irq_स्वतः_masklsw_set(self, aq_nic_cfg->aq_hw_caps->irq_mask);

	/* Interrupts */
	hw_atl_reg_gen_irq_map_set(self,
				   ((HW_ATL2_ERR_INT << 0x18) |
				    (1U << 0x1F)) |
				   ((HW_ATL2_ERR_INT << 0x10) |
				    (1U << 0x17)), 0U);

	hw_atl_b0_hw_offload_set(self, aq_nic_cfg);

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक hw_atl2_hw_ring_rx_init(काष्ठा aq_hw_s *self,
				   काष्ठा aq_ring_s *aq_ring,
				   काष्ठा aq_ring_param_s *aq_ring_param)
अणु
	वापस hw_atl_b0_hw_ring_rx_init(self, aq_ring, aq_ring_param);
पूर्ण

अटल पूर्णांक hw_atl2_hw_ring_tx_init(काष्ठा aq_hw_s *self,
				   काष्ठा aq_ring_s *aq_ring,
				   काष्ठा aq_ring_param_s *aq_ring_param)
अणु
	वापस hw_atl_b0_hw_ring_tx_init(self, aq_ring, aq_ring_param);
पूर्ण

#घोषणा IS_FILTER_ENABLED(_F_) ((packet_filter & (_F_)) ? 1U : 0U)

अटल पूर्णांक hw_atl2_hw_packet_filter_set(काष्ठा aq_hw_s *self,
					अचिन्हित पूर्णांक packet_filter)
अणु
	hw_atl2_hw_new_rx_filter_promisc(self, IS_FILTER_ENABLED(IFF_PROMISC));

	वापस hw_atl_b0_hw_packet_filter_set(self, packet_filter);
पूर्ण

#अघोषित IS_FILTER_ENABLED

अटल पूर्णांक hw_atl2_hw_multicast_list_set(काष्ठा aq_hw_s *self,
					 u8 ar_mac
					 [AQ_HW_MULTICAST_ADDRESS_MAX]
					 [ETH_ALEN],
					 u32 count)
अणु
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;
	पूर्णांक err = 0;

	अगर (count > (HW_ATL2_MAC_MAX - HW_ATL2_MAC_MIN)) अणु
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

		hw_atl_rpfl2_uc_flr_en_set(self, 0U, HW_ATL2_MAC_MIN + i);

		hw_atl_rpfl2unicast_dest_addresslsw_set(self, l,
							HW_ATL2_MAC_MIN + i);

		hw_atl_rpfl2unicast_dest_addressmsw_set(self, h,
							HW_ATL2_MAC_MIN + i);

		hw_atl2_rpfl2_uc_flr_tag_set(self, 1, HW_ATL2_MAC_MIN + i);

		hw_atl_rpfl2_uc_flr_en_set(self, (cfg->is_mc_list_enabled),
					   HW_ATL2_MAC_MIN + i);
	पूर्ण

	err = aq_hw_err_from_flags(self);

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक hw_atl2_hw_पूर्णांकerrupt_moderation_set(काष्ठा aq_hw_s *self)
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

			tx_max_समयr = min(HW_ATL2_INTR_MODER_MAX,
					   tx_max_समयr);
			tx_min_समयr = min(HW_ATL2_INTR_MODER_MIN,
					   tx_min_समयr);
			rx_max_समयr = min(HW_ATL2_INTR_MODER_MAX,
					   rx_max_समयr);
			rx_min_समयr = min(HW_ATL2_INTR_MODER_MIN,
					   rx_min_समयr);

			itr_tx |= tx_min_समयr << 0x8U;
			itr_tx |= tx_max_समयr << 0x10U;
			itr_rx |= rx_min_समयr << 0x8U;
			itr_rx |= rx_max_समयr << 0x10U;
		पूर्ण अन्यथा अणु
			अटल अचिन्हित पूर्णांक hw_atl2_समयrs_table_tx_[][2] = अणु
				अणु0xfU, 0xffUपूर्ण, /* 10Gbit */
				अणु0xfU, 0x1ffUपूर्ण, /* 5Gbit */
				अणु0xfU, 0x1ffUपूर्ण, /* 5Gbit 5GS */
				अणु0xfU, 0x1ffUपूर्ण, /* 2.5Gbit */
				अणु0xfU, 0x1ffUपूर्ण, /* 1Gbit */
				अणु0xfU, 0x1ffUपूर्ण, /* 100Mbit */
			पूर्ण;
			अटल अचिन्हित पूर्णांक hw_atl2_समयrs_table_rx_[][2] = अणु
				अणु0x6U, 0x38Uपूर्ण,/* 10Gbit */
				अणु0xCU, 0x70Uपूर्ण,/* 5Gbit */
				अणु0xCU, 0x70Uपूर्ण,/* 5Gbit 5GS */
				अणु0x18U, 0xE0Uपूर्ण,/* 2.5Gbit */
				अणु0x30U, 0x80Uपूर्ण,/* 1Gbit */
				अणु0x4U, 0x50Uपूर्ण,/* 100Mbit */
			पूर्ण;
			अचिन्हित पूर्णांक mbps = self->aq_link_status.mbps;
			अचिन्हित पूर्णांक speed_index;

			speed_index = hw_atl_utils_mbps_2_speed_index(mbps);

			/* Update user visible ITR settings */
			self->aq_nic_cfg->tx_itr = hw_atl2_समयrs_table_tx_
							[speed_index][1] * 2;
			self->aq_nic_cfg->rx_itr = hw_atl2_समयrs_table_rx_
							[speed_index][1] * 2;

			itr_tx |= hw_atl2_समयrs_table_tx_
						[speed_index][0] << 0x8U;
			itr_tx |= hw_atl2_समयrs_table_tx_
						[speed_index][1] << 0x10U;

			itr_rx |= hw_atl2_समयrs_table_rx_
						[speed_index][0] << 0x8U;
			itr_rx |= hw_atl2_समयrs_table_rx_
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

	क्रम (i = HW_ATL2_RINGS_MAX; i--;) अणु
		hw_atl2_reg_tx_पूर्णांकr_moder_ctrl_set(self, itr_tx, i);
		hw_atl_reg_rx_पूर्णांकr_moder_ctrl_set(self, itr_rx, i);
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl2_hw_stop(काष्ठा aq_hw_s *self)
अणु
	hw_atl_b0_hw_irq_disable(self, HW_ATL2_INT_MASK);

	वापस 0;
पूर्ण

अटल काष्ठा aq_stats_s *hw_atl2_utils_get_hw_stats(काष्ठा aq_hw_s *self)
अणु
	वापस &self->curr_stats;
पूर्ण

अटल पूर्णांक hw_atl2_hw_vlan_set(काष्ठा aq_hw_s *self,
			       काष्ठा aq_rx_filter_vlan *aq_vlans)
अणु
	काष्ठा hw_atl2_priv *priv = (काष्ठा hw_atl2_priv *)self->priv;
	u32 queue;
	u8 index;
	पूर्णांक i;

	hw_atl_rpf_vlan_prom_mode_en_set(self, 1U);

	क्रम (i = 0; i < HW_ATL_VLAN_MAX_FILTERS; i++) अणु
		queue = HW_ATL2_ACTION_ASSIGN_QUEUE(aq_vlans[i].queue);

		hw_atl_rpf_vlan_flr_en_set(self, 0U, i);
		hw_atl_rpf_vlan_rxq_en_flr_set(self, 0U, i);
		index = priv->art_base_index + HW_ATL2_RPF_VLAN_USER_INDEX + i;
		hw_atl2_act_rslvr_table_set(self, index, 0, 0,
					    HW_ATL2_ACTION_DISABLE);
		अगर (aq_vlans[i].enable) अणु
			hw_atl_rpf_vlan_id_flr_set(self,
						   aq_vlans[i].vlan_id, i);
			hw_atl_rpf_vlan_flr_act_set(self, 1U, i);
			hw_atl_rpf_vlan_flr_en_set(self, 1U, i);

			अगर (aq_vlans[i].queue != 0xFF) अणु
				hw_atl_rpf_vlan_rxq_flr_set(self,
							    aq_vlans[i].queue,
							    i);
				hw_atl_rpf_vlan_rxq_en_flr_set(self, 1U, i);

				hw_atl2_rpf_vlan_flr_tag_set(self, i + 2, i);

				index = priv->art_base_index +
					HW_ATL2_RPF_VLAN_USER_INDEX + i;
				hw_atl2_act_rslvr_table_set(self, index,
					(i + 2) << HW_ATL2_RPF_TAG_VLAN_OFFSET,
					HW_ATL2_RPF_TAG_VLAN_MASK, queue);
			पूर्ण अन्यथा अणु
				hw_atl2_rpf_vlan_flr_tag_set(self, 1, i);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस aq_hw_err_from_flags(self);
पूर्ण

अटल पूर्णांक hw_atl2_hw_vlan_ctrl(काष्ठा aq_hw_s *self, bool enable)
अणु
	/* set promisc in हाल of disabing the vlan filter */
	hw_atl_rpf_vlan_prom_mode_en_set(self, !enable);
	hw_atl2_hw_new_rx_filter_vlan_promisc(self, !enable);

	वापस aq_hw_err_from_flags(self);
पूर्ण

स्थिर काष्ठा aq_hw_ops hw_atl2_ops = अणु
	.hw_soft_reset        = hw_atl2_utils_soft_reset,
	.hw_prepare           = hw_atl2_utils_initfw,
	.hw_set_mac_address   = hw_atl_b0_hw_mac_addr_set,
	.hw_init              = hw_atl2_hw_init,
	.hw_reset             = hw_atl2_hw_reset,
	.hw_start             = hw_atl_b0_hw_start,
	.hw_ring_tx_start     = hw_atl_b0_hw_ring_tx_start,
	.hw_ring_tx_stop      = hw_atl_b0_hw_ring_tx_stop,
	.hw_ring_rx_start     = hw_atl_b0_hw_ring_rx_start,
	.hw_ring_rx_stop      = hw_atl_b0_hw_ring_rx_stop,
	.hw_stop              = hw_atl2_hw_stop,

	.hw_ring_tx_xmit         = hw_atl_b0_hw_ring_tx_xmit,
	.hw_ring_tx_head_update  = hw_atl_b0_hw_ring_tx_head_update,

	.hw_ring_rx_receive      = hw_atl_b0_hw_ring_rx_receive,
	.hw_ring_rx_fill         = hw_atl_b0_hw_ring_rx_fill,

	.hw_irq_enable           = hw_atl_b0_hw_irq_enable,
	.hw_irq_disable          = hw_atl_b0_hw_irq_disable,
	.hw_irq_पढ़ो             = hw_atl_b0_hw_irq_पढ़ो,

	.hw_ring_rx_init             = hw_atl2_hw_ring_rx_init,
	.hw_ring_tx_init             = hw_atl2_hw_ring_tx_init,
	.hw_packet_filter_set        = hw_atl2_hw_packet_filter_set,
	.hw_filter_vlan_set          = hw_atl2_hw_vlan_set,
	.hw_filter_vlan_ctrl         = hw_atl2_hw_vlan_ctrl,
	.hw_multicast_list_set       = hw_atl2_hw_multicast_list_set,
	.hw_पूर्णांकerrupt_moderation_set = hw_atl2_hw_पूर्णांकerrupt_moderation_set,
	.hw_rss_set                  = hw_atl2_hw_rss_set,
	.hw_rss_hash_set             = hw_atl_b0_hw_rss_hash_set,
	.hw_tc_rate_limit_set        = hw_atl2_hw_init_tx_tc_rate_limit,
	.hw_get_hw_stats             = hw_atl2_utils_get_hw_stats,
	.hw_get_fw_version           = hw_atl2_utils_get_fw_version,
	.hw_set_offload              = hw_atl_b0_hw_offload_set,
	.hw_set_loopback             = hw_atl_b0_set_loopback,
	.hw_set_fc                   = hw_atl_b0_set_fc,
पूर्ण;
