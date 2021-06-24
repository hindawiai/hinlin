<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#अगर_अघोषित HW_ATL2_LLH_H
#घोषणा HW_ATL2_LLH_H

#समावेश <linux/types.h>

काष्ठा aq_hw_s;

/* Set TX Interrupt Moderation Control Register */
व्योम hw_atl2_reg_tx_पूर्णांकr_moder_ctrl_set(काष्ठा aq_hw_s *aq_hw,
					u32 tx_पूर्णांकr_moderation_ctl,
					u32 queue);

/* Set Redirection Table 2 Select */
व्योम hw_atl2_rpf_redirection_table2_select_set(काष्ठा aq_hw_s *aq_hw,
					       u32 select);

/** Set RSS HASH type */
व्योम hw_atl2_rpf_rss_hash_type_set(काष्ठा aq_hw_s *aq_hw, u32 rss_hash_type);

/* set new RPF enable */
व्योम hw_atl2_rpf_new_enable_set(काष्ठा aq_hw_s *aq_hw, u32 enable);

/* set l2 unicast filter tag */
व्योम hw_atl2_rpfl2_uc_flr_tag_set(काष्ठा aq_hw_s *aq_hw, u32 tag, u32 filter);

/* set l2 broadcast filter tag */
व्योम hw_atl2_rpfl2_bc_flr_tag_set(काष्ठा aq_hw_s *aq_hw, u32 tag);

/* set new rss redirection table */
व्योम hw_atl2_new_rpf_rss_redir_set(काष्ठा aq_hw_s *aq_hw, u32 tc, u32 index,
				   u32 queue);

/* Set VLAN filter tag */
व्योम hw_atl2_rpf_vlan_flr_tag_set(काष्ठा aq_hw_s *aq_hw, u32 tag, u32 filter);

/* set tx अक्रमom TC-queue mapping enable bit */
व्योम hw_atl2_tpb_tx_tc_q_अक्रम_map_en_set(काष्ठा aq_hw_s *aq_hw,
					 स्थिर u32 tc_q_अक्रम_map_en);

/* set tx buffer घड़ी gate enable */
व्योम hw_atl2_tpb_tx_buf_clk_gate_en_set(काष्ठा aq_hw_s *aq_hw, u32 clk_gate_en);

व्योम hw_atl2_tps_tx_pkt_shed_data_arb_mode_set(काष्ठा aq_hw_s *aq_hw,
					       स्थिर u32 data_arb_mode);

/* set tx packet scheduler tc data max credit */
व्योम hw_atl2_tps_tx_pkt_shed_tc_data_max_credit_set(काष्ठा aq_hw_s *aq_hw,
						    स्थिर u32 tc,
						    स्थिर u32 max_credit);

/* set tx packet scheduler tc data weight */
व्योम hw_atl2_tps_tx_pkt_shed_tc_data_weight_set(काष्ठा aq_hw_s *aq_hw,
						स्थिर u32 tc,
						स्थिर u32 weight);

u32 hw_atl2_get_hw_version(काष्ठा aq_hw_s *aq_hw);

व्योम hw_atl2_init_launchसमय(काष्ठा aq_hw_s *aq_hw);

/* set action resolver record */
व्योम hw_atl2_rpf_act_rslvr_record_set(काष्ठा aq_hw_s *aq_hw, u8 location,
				      u32 tag, u32 mask, u32 action);

/* set enable action resolver section */
व्योम hw_atl2_rpf_act_rslvr_section_en_set(काष्ठा aq_hw_s *aq_hw, u32 sections);

/* get data from firmware shared input buffer */
व्योम hw_atl2_mअगर_shared_buf_get(काष्ठा aq_hw_s *aq_hw, पूर्णांक offset, u32 *data,
				पूर्णांक len);

/* set data पूर्णांकo firmware shared input buffer */
व्योम hw_atl2_mअगर_shared_buf_ग_लिखो(काष्ठा aq_hw_s *aq_hw, पूर्णांक offset, u32 *data,
				  पूर्णांक len);

/* get data from firmware shared output buffer */
व्योम hw_atl2_mअगर_shared_buf_पढ़ो(काष्ठा aq_hw_s *aq_hw, पूर्णांक offset, u32 *data,
				 पूर्णांक len);

/* set host finished ग_लिखो shared buffer indication */
व्योम hw_atl2_mअगर_host_finished_ग_लिखो_set(काष्ठा aq_hw_s *aq_hw, u32 finish);

/* get mcp finished पढ़ो shared buffer indication */
u32 hw_atl2_mअगर_mcp_finished_पढ़ो_get(काष्ठा aq_hw_s *aq_hw);

/* get mcp boot रेजिस्टर */
u32 hw_atl2_mअगर_mcp_boot_reg_get(काष्ठा aq_hw_s *aq_hw);

/* set mcp boot रेजिस्टर */
व्योम hw_atl2_mअगर_mcp_boot_reg_set(काष्ठा aq_hw_s *aq_hw, u32 val);

/* get host पूर्णांकerrupt request */
u32 hw_atl2_mअगर_host_req_पूर्णांक_get(काष्ठा aq_hw_s *aq_hw);

/* clear host पूर्णांकerrupt request */
व्योम hw_atl2_mअगर_host_req_पूर्णांक_clr(काष्ठा aq_hw_s *aq_hw, u32 val);

#पूर्ण_अगर /* HW_ATL2_LLH_H */
