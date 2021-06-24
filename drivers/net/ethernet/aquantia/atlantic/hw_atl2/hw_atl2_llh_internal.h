<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#अगर_अघोषित HW_ATL2_LLH_INTERNAL_H
#घोषणा HW_ATL2_LLH_INTERNAL_H

/* RX pअगर_rpf_redir_2_en_i Bitfield Definitions
 * PORT="pif_rpf_redir_2_en_i"
 */
#घोषणा HW_ATL2_RPF_PIF_RPF_REसूची2_ENI_ADR 0x000054C8
#घोषणा HW_ATL2_RPF_PIF_RPF_REसूची2_ENI_MSK 0x00001000
#घोषणा HW_ATL2_RPF_PIF_RPF_REसूची2_ENI_MSKN 0xFFFFEFFF
#घोषणा HW_ATL2_RPF_PIF_RPF_REसूची2_ENI_SHIFT 12
#घोषणा HW_ATL2_RPF_PIF_RPF_REसूची2_ENI_WIDTH 1
#घोषणा HW_ATL2_RPF_PIF_RPF_REसूची2_ENI_DEFAULT 0x0

/* RX pअगर_rpf_rss_hash_type_i Bitfield Definitions
 */
#घोषणा HW_ATL2_RPF_PIF_RPF_RSS_HASH_TYPEI_ADR 0x000054C8
#घोषणा HW_ATL2_RPF_PIF_RPF_RSS_HASH_TYPEI_MSK 0x000001FF
#घोषणा HW_ATL2_RPF_PIF_RPF_RSS_HASH_TYPEI_MSKN 0xFFFFFE00
#घोषणा HW_ATL2_RPF_PIF_RPF_RSS_HASH_TYPEI_SHIFT 0
#घोषणा HW_ATL2_RPF_PIF_RPF_RSS_HASH_TYPEI_WIDTH 9

/* rx rpf_new_rpf_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "rpf_new_rpf_en_i".
 * port="pअगर_rpf_new_rpf_en_i
 */

/* रेजिस्टर address क्रम bitfield rpf_new_rpf_en */
#घोषणा HW_ATL2_RPF_NEW_EN_ADR 0x00005104
/* biपंचांगask क्रम bitfield rpf_new_rpf_en */
#घोषणा HW_ATL2_RPF_NEW_EN_MSK 0x00000800
/* inverted biपंचांगask क्रम bitfield rpf_new_rpf_en */
#घोषणा HW_ATL2_RPF_NEW_EN_MSKN 0xfffff7ff
/* lower bit position of bitfield rpf_new_rpf_en */
#घोषणा HW_ATL2_RPF_NEW_EN_SHIFT 11
/* width of bitfield rpf_new_rpf_en */
#घोषणा HW_ATL2_RPF_NEW_EN_WIDTH 1
/* शेष value of bitfield rpf_new_rpf_en */
#घोषणा HW_ATL2_RPF_NEW_EN_DEFAULT 0x0

/* rx l2_uc_req_tag0अणुfपूर्ण[5:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "l2_uc_req_tag0{f}[7:0]".
 * parameter: filter अणुfपूर्ण | stride size 0x8 | range [0, 37]
 * port="pif_rpf_l2_uc_req_tag0[5:0]"
 */

/* रेजिस्टर address क्रम bitfield l2_uc_req_tag0अणुfपूर्ण[2:0] */
#घोषणा HW_ATL2_RPFL2UC_TAG_ADR(filter) (0x00005114 + (filter) * 0x8)
/* biपंचांगask क्रम bitfield l2_uc_req_tag0अणुfपूर्ण[2:0] */
#घोषणा HW_ATL2_RPFL2UC_TAG_MSK 0x0FC00000
/* inverted biपंचांगask क्रम bitfield l2_uc_req_tag0अणुfपूर्ण[2:0] */
#घोषणा HW_ATL2_RPFL2UC_TAG_MSKN 0xF03FFFFF
/* lower bit position of bitfield l2_uc_req_tag0अणुfपूर्ण[2:0] */
#घोषणा HW_ATL2_RPFL2UC_TAG_SHIFT 22
/* width of bitfield l2_uc_req_tag0अणुfपूर्ण[2:0] */
#घोषणा HW_ATL2_RPFL2UC_TAG_WIDTH 6
/* शेष value of bitfield l2_uc_req_tag0अणुfपूर्ण[2:0] */
#घोषणा HW_ATL2_RPFL2UC_TAG_DEFAULT 0x0

/* rpf_l2_bc_req_tag[5:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "rpf_l2_bc_req_tag[5:0]".
 * port="pifrpf_l2_bc_req_tag_i[5:0]"
 */

/* रेजिस्टर address क्रम bitfield rpf_l2_bc_req_tag */
#घोषणा HW_ATL2_RPF_L2_BC_TAG_ADR 0x000050F0
/* biपंचांगask क्रम bitfield rpf_l2_bc_req_tag */
#घोषणा HW_ATL2_RPF_L2_BC_TAG_MSK 0x0000003F
/* inverted biपंचांगask क्रम bitfield rpf_l2_bc_req_tag */
#घोषणा HW_ATL2_RPF_L2_BC_TAG_MSKN 0xffffffc0
/* lower bit position of bitfield rpf_l2_bc_req_tag */
#घोषणा HW_ATL2_RPF_L2_BC_TAG_SHIFT 0
/* width of bitfield rpf_l2_bc_req_tag */
#घोषणा HW_ATL2_RPF_L2_BC_TAG_WIDTH 6
/* शेष value of bitfield rpf_l2_bc_req_tag */
#घोषणा HW_ATL2_RPF_L2_BC_TAG_DEFAULT 0x0

/* rx rpf_rss_red1_data_[4:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "rpf_rss_red1_data[4:0]".
 * port="pif_rpf_rss_red1_data_i[4:0]"
 */

/* रेजिस्टर address क्रम bitfield rpf_rss_red1_data[4:0] */
#घोषणा HW_ATL2_RPF_RSS_REसूची_ADR(TC, INDEX) (0x00006200 + \
					(0x100 * !!((TC) > 3)) + (INDEX) * 4)
/* biपंचांगask क्रम bitfield rpf_rss_red1_data[4:0] */
#घोषणा HW_ATL2_RPF_RSS_REसूची_MSK(TC)  (0x00000001F << (5 * ((TC) % 4)))
/* lower bit position of bitfield rpf_rss_red1_data[4:0] */
#घोषणा HW_ATL2_RPF_RSS_REसूची_SHIFT(TC) (5 * ((TC) % 4))
/* width of bitfield rpf_rss_red1_data[4:0] */
#घोषणा HW_ATL2_RPF_RSS_REसूची_WIDTH 5
/* शेष value of bitfield rpf_rss_red1_data[4:0] */
#घोषणा HW_ATL2_RPF_RSS_REसूची_DEFAULT 0x0

/* rx vlan_req_tag0अणुfपूर्ण[3:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "vlan_req_tag0{f}[3:0]".
 * parameter: filter अणुfपूर्ण | stride size 0x4 | range [0, 15]
 * port="pif_rpf_vlan_req_tag0[3:0]"
 */

/* रेजिस्टर address क्रम bitfield vlan_req_tag0अणुfपूर्ण[3:0] */
#घोषणा HW_ATL2_RPF_VL_TAG_ADR(filter) (0x00005290 + (filter) * 0x4)
/* biपंचांगask क्रम bitfield vlan_req_tag0अणुfपूर्ण[3:0] */
#घोषणा HW_ATL2_RPF_VL_TAG_MSK 0x0000F000
/* inverted biपंचांगask क्रम bitfield vlan_req_tag0अणुfपूर्ण[3:0] */
#घोषणा HW_ATL2_RPF_VL_TAG_MSKN 0xFFFF0FFF
/* lower bit position of bitfield vlan_req_tag0अणुfपूर्ण[3:0] */
#घोषणा HW_ATL2_RPF_VL_TAG_SHIFT 12
/* width of bitfield vlan_req_tag0अणुfपूर्ण[3:0] */
#घोषणा HW_ATL2_RPF_VL_TAG_WIDTH 4
/* शेष value of bitfield vlan_req_tag0अणुfपूर्ण[3:0] */
#घोषणा HW_ATL2_RPF_VL_TAG_DEFAULT 0x0

/* RX rx_qअणुQपूर्ण_tc_map[2:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "rx_q{Q}_tc_map[2:0]".
 * Parameter: Queue अणुQपूर्ण | bit-level stride | range [0, 31]
 * PORT="pif_rx_q0_tc_map_i[2:0]"
 */

/* Register address क्रम bitfield rx_qअणुQपूर्ण_tc_map[2:0] */
#घोषणा HW_ATL2_RX_Q_TC_MAP_ADR(queue) \
	(((queue) < 32) ? 0x00005900 + ((queue) / 8) * 4 : 0)
/* Lower bit position of bitfield rx_qअणुQपूर्ण_tc_map[2:0] */
#घोषणा HW_ATL2_RX_Q_TC_MAP_SHIFT(queue) \
	(((queue) < 32) ? ((queue) * 4) % 32 : 0)
/* Width of bitfield rx_qअणुQपूर्ण_tc_map[2:0] */
#घोषणा HW_ATL2_RX_Q_TC_MAP_WIDTH 3
/* Default value of bitfield rx_qअणुQपूर्ण_tc_map[2:0] */
#घोषणा HW_ATL2_RX_Q_TC_MAP_DEFAULT 0x0

/* tx tx_tc_q_अक्रम_map_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx_tc_q_rand_map_en".
 * port="pif_tpb_tx_tc_q_rand_map_en_i"
 */

/* रेजिस्टर address क्रम bitfield tx_tc_q_अक्रम_map_en */
#घोषणा HW_ATL2_TPB_TX_TC_Q_RAND_MAP_EN_ADR 0x00007900
/* biपंचांगask क्रम bitfield tx_tc_q_अक्रम_map_en */
#घोषणा HW_ATL2_TPB_TX_TC_Q_RAND_MAP_EN_MSK 0x00000200
/* inverted biपंचांगask क्रम bitfield tx_tc_q_अक्रम_map_en */
#घोषणा HW_ATL2_TPB_TX_TC_Q_RAND_MAP_EN_MSKN 0xFFFFFDFF
/* lower bit position of bitfield tx_tc_q_अक्रम_map_en */
#घोषणा HW_ATL2_TPB_TX_TC_Q_RAND_MAP_EN_SHIFT 9
/* width of bitfield tx_tc_q_अक्रम_map_en */
#घोषणा HW_ATL2_TPB_TX_TC_Q_RAND_MAP_EN_WIDTH 1
/* शेष value of bitfield tx_tc_q_अक्रम_map_en */
#घोषणा HW_ATL2_TPB_TX_TC_Q_RAND_MAP_EN_DEFAULT 0x0

/* tx tx_buffer_clk_gate_en bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx_buffer_clk_gate_en".
 * port="pif_tpb_tx_buffer_clk_gate_en_i"
 */

/* रेजिस्टर address क्रम bitfield tx_buffer_clk_gate_en */
#घोषणा HW_ATL2_TPB_TX_BUF_CLK_GATE_EN_ADR 0x00007900
/* biपंचांगask क्रम bitfield tx_buffer_clk_gate_en */
#घोषणा HW_ATL2_TPB_TX_BUF_CLK_GATE_EN_MSK 0x00000020
/* inverted biपंचांगask क्रम bitfield tx_buffer_clk_gate_en */
#घोषणा HW_ATL2_TPB_TX_BUF_CLK_GATE_EN_MSKN 0xffffffdf
/* lower bit position of bitfield tx_buffer_clk_gate_en */
#घोषणा HW_ATL2_TPB_TX_BUF_CLK_GATE_EN_SHIFT 5
/* width of bitfield tx_buffer_clk_gate_en */
#घोषणा HW_ATL2_TPB_TX_BUF_CLK_GATE_EN_WIDTH 1
/* शेष value of bitfield tx_buffer_clk_gate_en */
#घोषणा HW_ATL2_TPB_TX_BUF_CLK_GATE_EN_DEFAULT 0x0

/* tx tx_q_tc_mapअणुqपूर्ण bitfield definitions
 * preprocessor definitions क्रम the bitfield "tx_q_tc_map{q}".
 * parameter: queue अणुqपूर्ण | bit-level stride | range [0, 31]
 * port="pif_tpb_tx_q_tc_map0_i[2:0]"
 */

/* रेजिस्टर address क्रम bitfield tx_q_tc_mapअणुqपूर्ण */
#घोषणा HW_ATL2_TX_Q_TC_MAP_ADR(queue) \
	(((queue) < 32) ? 0x0000799C + ((queue) / 4) * 4 : 0)
/* lower bit position of bitfield tx_q_tc_mapअणुqपूर्ण */
#घोषणा HW_ATL2_TX_Q_TC_MAP_SHIFT(queue) \
	(((queue) < 32) ? ((queue) * 8) % 32 : 0)
/* width of bitfield tx_q_tc_mapअणुqपूर्ण */
#घोषणा HW_ATL2_TX_Q_TC_MAP_WIDTH 3
/* शेष value of bitfield tx_q_tc_mapअणुqपूर्ण */
#घोषणा HW_ATL2_TX_Q_TC_MAP_DEFAULT 0x0

/* tx data_tc_arb_mode bitfield definitions
 * preprocessor definitions क्रम the bitfield "data_tc_arb_mode".
 * port="pif_tps_data_tc_arb_mode_i"
 */

/* रेजिस्टर address क्रम bitfield data_tc_arb_mode */
#घोषणा HW_ATL2_TPS_DATA_TC_ARB_MODE_ADR 0x00007100
/* biपंचांगask क्रम bitfield data_tc_arb_mode */
#घोषणा HW_ATL2_TPS_DATA_TC_ARB_MODE_MSK 0x00000003
/* inverted biपंचांगask क्रम bitfield data_tc_arb_mode */
#घोषणा HW_ATL2_TPS_DATA_TC_ARB_MODE_MSKN 0xfffffffc
/* lower bit position of bitfield data_tc_arb_mode */
#घोषणा HW_ATL2_TPS_DATA_TC_ARB_MODE_SHIFT 0
/* width of bitfield data_tc_arb_mode */
#घोषणा HW_ATL2_TPS_DATA_TC_ARB_MODE_WIDTH 2
/* शेष value of bitfield data_tc_arb_mode */
#घोषणा HW_ATL2_TPS_DATA_TC_ARB_MODE_DEFAULT 0x0

/* tx data_tcअणुtपूर्ण_credit_max[f:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "data_tc{t}_credit_max[f:0]".
 * parameter: tc अणुtपूर्ण | stride size 0x4 | range [0, 7]
 * port="pif_tps_data_tc0_credit_max_i[15:0]"
 */

/* रेजिस्टर address क्रम bitfield data_tcअणुtपूर्ण_credit_max[f:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTCREDIT_MAX_ADR(tc) (0x00007110 + (tc) * 0x4)
/* biपंचांगask क्रम bitfield data_tcअणुtपूर्ण_credit_max[f:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTCREDIT_MAX_MSK 0xffff0000
/* inverted biपंचांगask क्रम bitfield data_tcअणुtपूर्ण_credit_max[f:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTCREDIT_MAX_MSKN 0x0000ffff
/* lower bit position of bitfield data_tcअणुtपूर्ण_credit_max[f:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTCREDIT_MAX_SHIFT 16
/* width of bitfield data_tcअणुtपूर्ण_credit_max[f:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTCREDIT_MAX_WIDTH 16
/* शेष value of bitfield data_tcअणुtपूर्ण_credit_max[f:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTCREDIT_MAX_DEFAULT 0x0

/* tx data_tcअणुtपूर्ण_weight[e:0] bitfield definitions
 * preprocessor definitions क्रम the bitfield "data_tc{t}_weight[e:0]".
 * parameter: tc अणुtपूर्ण | stride size 0x4 | range [0, 7]
 * port="pif_tps_data_tc0_weight_i[14:0]"
 */

/* रेजिस्टर address क्रम bitfield data_tcअणुtपूर्ण_weight[e:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTWEIGHT_ADR(tc) (0x00007110 + (tc) * 0x4)
/* biपंचांगask क्रम bitfield data_tcअणुtपूर्ण_weight[e:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTWEIGHT_MSK 0x00007fff
/* inverted biपंचांगask क्रम bitfield data_tcअणुtपूर्ण_weight[e:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTWEIGHT_MSKN 0xffff8000
/* lower bit position of bitfield data_tcअणुtपूर्ण_weight[e:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTWEIGHT_SHIFT 0
/* width of bitfield data_tcअणुtपूर्ण_weight[e:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTWEIGHT_WIDTH 15
/* शेष value of bitfield data_tcअणुtपूर्ण_weight[e:0] */
#घोषणा HW_ATL2_TPS_DATA_TCTWEIGHT_DEFAULT 0x0

/* tx पूर्णांकerrupt moderation control रेजिस्टर definitions
 * Preprocessor definitions क्रम TX Interrupt Moderation Control Register
 * Base Address: 0x00007c28
 * Parameter: queue अणुQपूर्ण | stride size 0x4 | range [0, 31]
 */

#घोषणा HW_ATL2_TX_INTR_MODERATION_CTL_ADR(queue) (0x00007c28u + (queue) * 0x40)

/* Launch समय control रेजिस्टर */
#घोषणा HW_ATL2_LT_CTRL_ADR 0x00007a1c

#घोषणा HW_ATL2_LT_CTRL_AVB_LEN_CMP_TRSHLD_MSK 0xFFFF0000
#घोषणा HW_ATL2_LT_CTRL_AVB_LEN_CMP_TRSHLD_SHIFT 16

#घोषणा HW_ATL2_LT_CTRL_CLK_RATIO_MSK 0x0000FF00
#घोषणा HW_ATL2_LT_CTRL_CLK_RATIO_SHIFT 8
#घोषणा HW_ATL2_LT_CTRL_CLK_RATIO_QUATER_SPEED 4
#घोषणा HW_ATL2_LT_CTRL_CLK_RATIO_HALF_SPEED 2
#घोषणा HW_ATL2_LT_CTRL_CLK_RATIO_FULL_SPEED 1

#घोषणा HW_ATL2_LT_CTRL_25G_MODE_SUPPORT_MSK 0x00000008
#घोषणा HW_ATL2_LT_CTRL_25G_MODE_SUPPORT_SHIFT 3

#घोषणा HW_ATL2_LT_CTRL_LINK_SPEED_MSK 0x00000007
#घोषणा HW_ATL2_LT_CTRL_LINK_SPEED_SHIFT 0

/* FPGA VER रेजिस्टर */
#घोषणा HW_ATL2_FPGA_VER_ADR 0x000000f4
#घोषणा HW_ATL2_FPGA_VER_U32(mj, mi, bl, rv) \
	((((mj) & 0xff) << 24) | \
	 (((mi) & 0xff) << 16) | \
	 (((bl) & 0xff) << 8) | \
	 (((rv) & 0xff) << 0))

/* ahb_mem_addrअणुfपूर्ण[31:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "ahb_mem_addr{f}[31:0]".
 * Parameter: filter अणुfपूर्ण | stride size 0x10 | range [0, 127]
 * PORT="ahb_mem_addr{f}[31:0]"
 */

/* Register address क्रम bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_REQ_TAG_ADR(filter) \
	(0x00014000u + (filter) * 0x10)
/* Biपंचांगask क्रम bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_REQ_TAG_MSK 0xFFFFFFFFu
/* Inverted biपंचांगask क्रम bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_REQ_TAG_MSKN 0x00000000u
/* Lower bit position of bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_REQ_TAG_SHIFT 0
/* Width of bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_REQ_TAG_WIDTH 31
/* Default value of bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_REQ_TAG_DEFAULT 0x0

/* Register address क्रम bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_TAG_MASK_ADR(filter) \
	(0x00014004u + (filter) * 0x10)
/* Biपंचांगask क्रम bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_TAG_MASK_MSK 0xFFFFFFFFu
/* Inverted biपंचांगask क्रम bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_TAG_MASK_MSKN 0x00000000u
/* Lower bit position of bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_TAG_MASK_SHIFT 0
/* Width of bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_TAG_MASK_WIDTH 31
/* Default value of bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_TAG_MASK_DEFAULT 0x0

/* Register address क्रम bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_ACTN_ADR(filter) \
	(0x00014008u + (filter) * 0x10)
/* Biपंचांगask क्रम bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_ACTN_MSK 0x000007FFu
/* Inverted biपंचांगask क्रम bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_ACTN_MSKN 0xFFFFF800u
/* Lower bit position of bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_ACTN_SHIFT 0
/* Width of bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_ACTN_WIDTH 10
/* Default value of bitfield ahb_mem_addrअणुfपूर्ण[31:0] */
#घोषणा HW_ATL2_RPF_ACT_RSLVR_ACTN_DEFAULT 0x0

/* rpf_rec_tab_en[15:0] Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "rpf_rec_tab_en[15:0]".
 * PORT="pif_rpf_rec_tab_en[15:0]"
 */
/* Register address क्रम bitfield rpf_rec_tab_en[15:0] */
#घोषणा HW_ATL2_RPF_REC_TAB_EN_ADR 0x00006ff0u
/* Biपंचांगask क्रम bitfield rpf_rec_tab_en[15:0] */
#घोषणा HW_ATL2_RPF_REC_TAB_EN_MSK 0x0000FFFFu
/* Inverted biपंचांगask क्रम bitfield rpf_rec_tab_en[15:0] */
#घोषणा HW_ATL2_RPF_REC_TAB_EN_MSKN 0xFFFF0000u
/* Lower bit position of bitfield rpf_rec_tab_en[15:0] */
#घोषणा HW_ATL2_RPF_REC_TAB_EN_SHIFT 0
/* Width of bitfield rpf_rec_tab_en[15:0] */
#घोषणा HW_ATL2_RPF_REC_TAB_EN_WIDTH 16
/* Default value of bitfield rpf_rec_tab_en[15:0] */
#घोषणा HW_ATL2_RPF_REC_TAB_EN_DEFAULT 0x0

/* Register address क्रम firmware shared input buffer */
#घोषणा HW_ATL2_MIF_SHARED_BUFFER_IN_ADR(dword) (0x00012000U + (dword) * 0x4U)
/* Register address क्रम firmware shared output buffer */
#घोषणा HW_ATL2_MIF_SHARED_BUFFER_OUT_ADR(dword) (0x00013000U + (dword) * 0x4U)

/* pअगर_host_finished_buf_wr_i Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "pif_host_finished_buf_wr_i".
 * PORT="pif_host_finished_buf_wr_i"
 */
/* Register address क्रम bitfield rpअगर_host_finished_buf_wr_i */
#घोषणा HW_ATL2_MIF_HOST_FINISHED_WRITE_ADR 0x00000e00u
/* Biपंचांगask क्रम bitfield pअगर_host_finished_buf_wr_i */
#घोषणा HW_ATL2_MIF_HOST_FINISHED_WRITE_MSK 0x00000001u
/* Inverted biपंचांगask क्रम bitfield pअगर_host_finished_buf_wr_i */
#घोषणा HW_ATL2_MIF_HOST_FINISHED_WRITE_MSKN 0xFFFFFFFEu
/* Lower bit position of bitfield pअगर_host_finished_buf_wr_i */
#घोषणा HW_ATL2_MIF_HOST_FINISHED_WRITE_SHIFT 0
/* Width of bitfield pअगर_host_finished_buf_wr_i */
#घोषणा HW_ATL2_MIF_HOST_FINISHED_WRITE_WIDTH 1
/* Default value of bitfield pअगर_host_finished_buf_wr_i */
#घोषणा HW_ATL2_MIF_HOST_FINISHED_WRITE_DEFAULT 0x0

/* pअगर_mcp_finished_buf_rd_i Bitfield Definitions
 * Preprocessor definitions क्रम the bitfield "pif_mcp_finished_buf_rd_i".
 * PORT="pif_mcp_finished_buf_rd_i"
 */
/* Register address क्रम bitfield pअगर_mcp_finished_buf_rd_i */
#घोषणा HW_ATL2_MIF_MCP_FINISHED_READ_ADR 0x00000e04u
/* Biपंचांगask क्रम bitfield pअगर_mcp_finished_buf_rd_i */
#घोषणा HW_ATL2_MIF_MCP_FINISHED_READ_MSK 0x00000001u
/* Inverted biपंचांगask क्रम bitfield pअगर_mcp_finished_buf_rd_i */
#घोषणा HW_ATL2_MIF_MCP_FINISHED_READ_MSKN 0xFFFFFFFEu
/* Lower bit position of bitfield pअगर_mcp_finished_buf_rd_i */
#घोषणा HW_ATL2_MIF_MCP_FINISHED_READ_SHIFT 0
/* Width of bitfield pअगर_mcp_finished_buf_rd_i */
#घोषणा HW_ATL2_MIF_MCP_FINISHED_READ_WIDTH 1
/* Default value of bitfield pअगर_mcp_finished_buf_rd_i */
#घोषणा HW_ATL2_MIF_MCP_FINISHED_READ_DEFAULT 0x0

/* Register address क्रम bitfield pअगर_mcp_boot_reg */
#घोषणा HW_ATL2_MIF_BOOT_REG_ADR 0x00003040u

#घोषणा HW_ATL2_MCP_HOST_REQ_INT_READY BIT(0)

#घोषणा HW_ATL2_MCP_HOST_REQ_INT_ADR 0x00000F00u
#घोषणा HW_ATL2_MCP_HOST_REQ_INT_SET_ADR 0x00000F04u
#घोषणा HW_ATL2_MCP_HOST_REQ_INT_CLR_ADR 0x00000F08u

#पूर्ण_अगर /* HW_ATL2_LLH_INTERNAL_H */
