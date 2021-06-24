<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#समावेश "hw_atl2_llh.h"
#समावेश "hw_atl2_llh_internal.h"
#समावेश "aq_hw_utils.h"

व्योम hw_atl2_rpf_redirection_table2_select_set(काष्ठा aq_hw_s *aq_hw,
					       u32 select)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_RPF_PIF_RPF_REसूची2_ENI_ADR,
			    HW_ATL2_RPF_PIF_RPF_REसूची2_ENI_MSK,
			    HW_ATL2_RPF_PIF_RPF_REसूची2_ENI_SHIFT, select);
पूर्ण

व्योम hw_atl2_rpf_rss_hash_type_set(काष्ठा aq_hw_s *aq_hw, u32 rss_hash_type)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_RPF_PIF_RPF_RSS_HASH_TYPEI_ADR,
			    HW_ATL2_RPF_PIF_RPF_RSS_HASH_TYPEI_MSK,
			    HW_ATL2_RPF_PIF_RPF_RSS_HASH_TYPEI_SHIFT,
			    rss_hash_type);
पूर्ण

/* rpf */

व्योम hw_atl2_rpf_new_enable_set(काष्ठा aq_hw_s *aq_hw, u32 enable)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_RPF_NEW_EN_ADR,
			    HW_ATL2_RPF_NEW_EN_MSK,
			    HW_ATL2_RPF_NEW_EN_SHIFT,
			    enable);
पूर्ण

व्योम hw_atl2_rpfl2_uc_flr_tag_set(काष्ठा aq_hw_s *aq_hw, u32 tag, u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_RPFL2UC_TAG_ADR(filter),
			    HW_ATL2_RPFL2UC_TAG_MSK,
			    HW_ATL2_RPFL2UC_TAG_SHIFT,
			    tag);
पूर्ण

व्योम hw_atl2_rpfl2_bc_flr_tag_set(काष्ठा aq_hw_s *aq_hw, u32 tag)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_RPF_L2_BC_TAG_ADR,
			    HW_ATL2_RPF_L2_BC_TAG_MSK,
			    HW_ATL2_RPF_L2_BC_TAG_SHIFT,
			    tag);
पूर्ण

व्योम hw_atl2_new_rpf_rss_redir_set(काष्ठा aq_hw_s *aq_hw, u32 tc, u32 index,
				   u32 queue)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_RPF_RSS_REसूची_ADR(tc, index),
			    HW_ATL2_RPF_RSS_REसूची_MSK(tc),
			    HW_ATL2_RPF_RSS_REसूची_SHIFT(tc),
			    queue);
पूर्ण

व्योम hw_atl2_rpf_vlan_flr_tag_set(काष्ठा aq_hw_s *aq_hw, u32 tag, u32 filter)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_RPF_VL_TAG_ADR(filter),
			    HW_ATL2_RPF_VL_TAG_MSK,
			    HW_ATL2_RPF_VL_TAG_SHIFT,
			    tag);
पूर्ण

/* TX */

व्योम hw_atl2_tpb_tx_tc_q_अक्रम_map_en_set(काष्ठा aq_hw_s *aq_hw,
					 स्थिर u32 tc_q_अक्रम_map_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_TPB_TX_TC_Q_RAND_MAP_EN_ADR,
			    HW_ATL2_TPB_TX_TC_Q_RAND_MAP_EN_MSK,
			    HW_ATL2_TPB_TX_TC_Q_RAND_MAP_EN_SHIFT,
			    tc_q_अक्रम_map_en);
पूर्ण

व्योम hw_atl2_tpb_tx_buf_clk_gate_en_set(काष्ठा aq_hw_s *aq_hw, u32 clk_gate_en)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_TPB_TX_BUF_CLK_GATE_EN_ADR,
			    HW_ATL2_TPB_TX_BUF_CLK_GATE_EN_MSK,
			    HW_ATL2_TPB_TX_BUF_CLK_GATE_EN_SHIFT,
			    clk_gate_en);
पूर्ण

व्योम hw_atl2_reg_tx_पूर्णांकr_moder_ctrl_set(काष्ठा aq_hw_s *aq_hw,
					u32 tx_पूर्णांकr_moderation_ctl,
					u32 queue)
अणु
	aq_hw_ग_लिखो_reg(aq_hw, HW_ATL2_TX_INTR_MODERATION_CTL_ADR(queue),
			tx_पूर्णांकr_moderation_ctl);
पूर्ण

व्योम hw_atl2_tps_tx_pkt_shed_data_arb_mode_set(काष्ठा aq_hw_s *aq_hw,
					       स्थिर u32 data_arb_mode)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_TPS_DATA_TC_ARB_MODE_ADR,
			    HW_ATL2_TPS_DATA_TC_ARB_MODE_MSK,
			    HW_ATL2_TPS_DATA_TC_ARB_MODE_SHIFT,
			    data_arb_mode);
पूर्ण

व्योम hw_atl2_tps_tx_pkt_shed_tc_data_max_credit_set(काष्ठा aq_hw_s *aq_hw,
						    स्थिर u32 tc,
						    स्थिर u32 max_credit)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_TPS_DATA_TCTCREDIT_MAX_ADR(tc),
			    HW_ATL2_TPS_DATA_TCTCREDIT_MAX_MSK,
			    HW_ATL2_TPS_DATA_TCTCREDIT_MAX_SHIFT,
			    max_credit);
पूर्ण

व्योम hw_atl2_tps_tx_pkt_shed_tc_data_weight_set(काष्ठा aq_hw_s *aq_hw,
						स्थिर u32 tc,
						स्थिर u32 weight)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_TPS_DATA_TCTWEIGHT_ADR(tc),
			    HW_ATL2_TPS_DATA_TCTWEIGHT_MSK,
			    HW_ATL2_TPS_DATA_TCTWEIGHT_SHIFT,
			    weight);
पूर्ण

u32 hw_atl2_get_hw_version(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL2_FPGA_VER_ADR);
पूर्ण

व्योम hw_atl2_init_launchसमय(काष्ठा aq_hw_s *aq_hw)
अणु
	u32 hw_ver = hw_atl2_get_hw_version(aq_hw);

	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_LT_CTRL_ADR,
			    HW_ATL2_LT_CTRL_CLK_RATIO_MSK,
			    HW_ATL2_LT_CTRL_CLK_RATIO_SHIFT,
			    hw_ver  < HW_ATL2_FPGA_VER_U32(1, 0, 0, 0) ?
			    HW_ATL2_LT_CTRL_CLK_RATIO_FULL_SPEED :
			    hw_ver >= HW_ATL2_FPGA_VER_U32(1, 0, 85, 2) ?
			    HW_ATL2_LT_CTRL_CLK_RATIO_HALF_SPEED :
			    HW_ATL2_LT_CTRL_CLK_RATIO_QUATER_SPEED);
पूर्ण

/* set action resolver record */
व्योम hw_atl2_rpf_act_rslvr_record_set(काष्ठा aq_hw_s *aq_hw, u8 location,
				      u32 tag, u32 mask, u32 action)
अणु
	aq_hw_ग_लिखो_reg(aq_hw,
			HW_ATL2_RPF_ACT_RSLVR_REQ_TAG_ADR(location),
			tag);
	aq_hw_ग_लिखो_reg(aq_hw,
			HW_ATL2_RPF_ACT_RSLVR_TAG_MASK_ADR(location),
			mask);
	aq_hw_ग_लिखो_reg(aq_hw,
			HW_ATL2_RPF_ACT_RSLVR_ACTN_ADR(location),
			action);
पूर्ण

व्योम hw_atl2_rpf_act_rslvr_section_en_set(काष्ठा aq_hw_s *aq_hw, u32 sections)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_RPF_REC_TAB_EN_ADR,
			    HW_ATL2_RPF_REC_TAB_EN_MSK,
			    HW_ATL2_RPF_REC_TAB_EN_SHIFT,
			    sections);
पूर्ण

व्योम hw_atl2_mअगर_shared_buf_get(काष्ठा aq_hw_s *aq_hw, पूर्णांक offset, u32 *data,
				पूर्णांक len)
अणु
	पूर्णांक j = 0;
	पूर्णांक i;

	क्रम (i = offset; i < offset + len; i++, j++)
		data[j] = aq_hw_पढ़ो_reg(aq_hw,
					 HW_ATL2_MIF_SHARED_BUFFER_IN_ADR(i));
पूर्ण

व्योम hw_atl2_mअगर_shared_buf_ग_लिखो(काष्ठा aq_hw_s *aq_hw, पूर्णांक offset, u32 *data,
				  पूर्णांक len)
अणु
	पूर्णांक j = 0;
	पूर्णांक i;

	क्रम (i = offset; i < offset + len; i++, j++)
		aq_hw_ग_लिखो_reg(aq_hw, HW_ATL2_MIF_SHARED_BUFFER_IN_ADR(i),
				data[j]);
पूर्ण

व्योम hw_atl2_mअगर_shared_buf_पढ़ो(काष्ठा aq_hw_s *aq_hw, पूर्णांक offset, u32 *data,
				 पूर्णांक len)
अणु
	पूर्णांक j = 0;
	पूर्णांक i;

	क्रम (i = offset; i < offset + len; i++, j++)
		data[j] = aq_hw_पढ़ो_reg(aq_hw,
					 HW_ATL2_MIF_SHARED_BUFFER_OUT_ADR(i));
पूर्ण

व्योम hw_atl2_mअगर_host_finished_ग_लिखो_set(काष्ठा aq_hw_s *aq_hw, u32 finish)
अणु
	aq_hw_ग_लिखो_reg_bit(aq_hw, HW_ATL2_MIF_HOST_FINISHED_WRITE_ADR,
			    HW_ATL2_MIF_HOST_FINISHED_WRITE_MSK,
			    HW_ATL2_MIF_HOST_FINISHED_WRITE_SHIFT,
			    finish);
पूर्ण

u32 hw_atl2_mअगर_mcp_finished_पढ़ो_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg_bit(aq_hw, HW_ATL2_MIF_MCP_FINISHED_READ_ADR,
				  HW_ATL2_MIF_MCP_FINISHED_READ_MSK,
				  HW_ATL2_MIF_MCP_FINISHED_READ_SHIFT);
पूर्ण

u32 hw_atl2_mअगर_mcp_boot_reg_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL2_MIF_BOOT_REG_ADR);
पूर्ण

व्योम hw_atl2_mअगर_mcp_boot_reg_set(काष्ठा aq_hw_s *aq_hw, u32 val)
अणु
	वापस aq_hw_ग_लिखो_reg(aq_hw, HW_ATL2_MIF_BOOT_REG_ADR, val);
पूर्ण

u32 hw_atl2_mअगर_host_req_पूर्णांक_get(काष्ठा aq_hw_s *aq_hw)
अणु
	वापस aq_hw_पढ़ो_reg(aq_hw, HW_ATL2_MCP_HOST_REQ_INT_ADR);
पूर्ण

व्योम hw_atl2_mअगर_host_req_पूर्णांक_clr(काष्ठा aq_hw_s *aq_hw, u32 val)
अणु
	वापस aq_hw_ग_लिखो_reg(aq_hw, HW_ATL2_MCP_HOST_REQ_INT_CLR_ADR,
			       val);
पूर्ण
