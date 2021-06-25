<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2016-2017 Hisilicon Limited.

#समावेश <linux/etherdevice.h>

#समावेश "hclge_cmd.h"
#समावेश "hclge_main.h"
#समावेश "hclge_tm.h"

क्रमागत hclge_shaper_level अणु
	HCLGE_SHAPER_LVL_PRI	= 0,
	HCLGE_SHAPER_LVL_PG	= 1,
	HCLGE_SHAPER_LVL_PORT	= 2,
	HCLGE_SHAPER_LVL_QSET	= 3,
	HCLGE_SHAPER_LVL_CNT	= 4,
	HCLGE_SHAPER_LVL_VF	= 0,
	HCLGE_SHAPER_LVL_PF	= 1,
पूर्ण;

#घोषणा HCLGE_TM_PFC_PKT_GET_CMD_NUM	3
#घोषणा HCLGE_TM_PFC_NUM_GET_PER_CMD	3

#घोषणा HCLGE_SHAPER_BS_U_DEF	5
#घोषणा HCLGE_SHAPER_BS_S_DEF	20

/* hclge_shaper_para_calc: calculate ir parameter क्रम the shaper
 * @ir: Rate to be config, its unit is Mbps
 * @shaper_level: the shaper level. eg: port, pg, priority, queueset
 * @ir_para: parameters of IR shaper
 * @max_पंचांग_rate: max पंचांग rate is available to config
 *
 * the क्रमmula:
 *
 *		IR_b * (2 ^ IR_u) * 8
 * IR(Mbps) = -------------------------  *  CLOCK(1000Mbps)
 *		Tick * (2 ^ IR_s)
 *
 * @वापस: 0: calculate sucessful, negative: fail
 */
अटल पूर्णांक hclge_shaper_para_calc(u32 ir, u8 shaper_level,
				  काष्ठा hclge_shaper_ir_para *ir_para,
				  u32 max_पंचांग_rate)
अणु
#घोषणा DEFAULT_SHAPER_IR_B	126
#घोषणा DIVISOR_CLK		(1000 * 8)
#घोषणा DEFAULT_DIVISOR_IR_B	(DEFAULT_SHAPER_IR_B * DIVISOR_CLK)

	अटल स्थिर u16 tick_array[HCLGE_SHAPER_LVL_CNT] = अणु
		6 * 256,        /* Prioriy level */
		6 * 32,         /* Prioriy group level */
		6 * 8,          /* Port level */
		6 * 256         /* Qset level */
	पूर्ण;
	u8 ir_u_calc = 0;
	u8 ir_s_calc = 0;
	u32 ir_calc;
	u32 tick;

	/* Calc tick */
	अगर (shaper_level >= HCLGE_SHAPER_LVL_CNT ||
	    ir > max_पंचांग_rate)
		वापस -EINVAL;

	tick = tick_array[shaper_level];

	/**
	 * Calc the speed अगर ir_b = 126, ir_u = 0 and ir_s = 0
	 * the क्रमmula is changed to:
	 *		126 * 1 * 8
	 * ir_calc = ---------------- * 1000
	 *		tick * 1
	 */
	ir_calc = (DEFAULT_DIVISOR_IR_B + (tick >> 1) - 1) / tick;

	अगर (ir_calc == ir) अणु
		ir_para->ir_b = DEFAULT_SHAPER_IR_B;
		ir_para->ir_u = 0;
		ir_para->ir_s = 0;

		वापस 0;
	पूर्ण अन्यथा अगर (ir_calc > ir) अणु
		/* Increasing the denominator to select ir_s value */
		जबतक (ir_calc >= ir && ir) अणु
			ir_s_calc++;
			ir_calc = DEFAULT_DIVISOR_IR_B /
				  (tick * (1 << ir_s_calc));
		पूर्ण

		ir_para->ir_b = (ir * tick * (1 << ir_s_calc) +
				(DIVISOR_CLK >> 1)) / DIVISOR_CLK;
	पूर्ण अन्यथा अणु
		/* Increasing the numerator to select ir_u value */
		u32 numerator;

		जबतक (ir_calc < ir) अणु
			ir_u_calc++;
			numerator = DEFAULT_DIVISOR_IR_B * (1 << ir_u_calc);
			ir_calc = (numerator + (tick >> 1)) / tick;
		पूर्ण

		अगर (ir_calc == ir) अणु
			ir_para->ir_b = DEFAULT_SHAPER_IR_B;
		पूर्ण अन्यथा अणु
			u32 denominator = DIVISOR_CLK * (1 << --ir_u_calc);
			ir_para->ir_b = (ir * tick + (denominator >> 1)) /
					denominator;
		पूर्ण
	पूर्ण

	ir_para->ir_u = ir_u_calc;
	ir_para->ir_s = ir_s_calc;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_pfc_stats_get(काष्ठा hclge_dev *hdev,
			       क्रमागत hclge_opcode_type opcode, u64 *stats)
अणु
	काष्ठा hclge_desc desc[HCLGE_TM_PFC_PKT_GET_CMD_NUM];
	पूर्णांक ret, i, j;

	अगर (!(opcode == HCLGE_OPC_QUERY_PFC_RX_PKT_CNT ||
	      opcode == HCLGE_OPC_QUERY_PFC_TX_PKT_CNT))
		वापस -EINVAL;

	क्रम (i = 0; i < HCLGE_TM_PFC_PKT_GET_CMD_NUM - 1; i++) अणु
		hclge_cmd_setup_basic_desc(&desc[i], opcode, true);
		desc[i].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	पूर्ण

	hclge_cmd_setup_basic_desc(&desc[i], opcode, true);

	ret = hclge_cmd_send(&hdev->hw, desc, HCLGE_TM_PFC_PKT_GET_CMD_NUM);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < HCLGE_TM_PFC_PKT_GET_CMD_NUM; i++) अणु
		काष्ठा hclge_pfc_stats_cmd *pfc_stats =
				(काष्ठा hclge_pfc_stats_cmd *)desc[i].data;

		क्रम (j = 0; j < HCLGE_TM_PFC_NUM_GET_PER_CMD; j++) अणु
			u32 index = i * HCLGE_TM_PFC_PKT_GET_CMD_NUM + j;

			अगर (index < HCLGE_MAX_TC_NUM)
				stats[index] =
					le64_to_cpu(pfc_stats->pkt_num[j]);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक hclge_pfc_rx_stats_get(काष्ठा hclge_dev *hdev, u64 *stats)
अणु
	वापस hclge_pfc_stats_get(hdev, HCLGE_OPC_QUERY_PFC_RX_PKT_CNT, stats);
पूर्ण

पूर्णांक hclge_pfc_tx_stats_get(काष्ठा hclge_dev *hdev, u64 *stats)
अणु
	वापस hclge_pfc_stats_get(hdev, HCLGE_OPC_QUERY_PFC_TX_PKT_CNT, stats);
पूर्ण

पूर्णांक hclge_mac_छोड़ो_en_cfg(काष्ठा hclge_dev *hdev, bool tx, bool rx)
अणु
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_MAC_PAUSE_EN, false);

	desc.data[0] = cpu_to_le32((tx ? HCLGE_TX_MAC_PAUSE_EN_MSK : 0) |
		(rx ? HCLGE_RX_MAC_PAUSE_EN_MSK : 0));

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_pfc_छोड़ो_en_cfg(काष्ठा hclge_dev *hdev, u8 tx_rx_biपंचांगap,
				  u8 pfc_biपंचांगap)
अणु
	काष्ठा hclge_desc desc;
	काष्ठा hclge_pfc_en_cmd *pfc = (काष्ठा hclge_pfc_en_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_PFC_PAUSE_EN, false);

	pfc->tx_rx_en_biपंचांगap = tx_rx_biपंचांगap;
	pfc->pri_en_biपंचांगap = pfc_biपंचांगap;

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_छोड़ो_param_cfg(काष्ठा hclge_dev *hdev, स्थिर u8 *addr,
				 u8 छोड़ो_trans_gap, u16 छोड़ो_trans_समय)
अणु
	काष्ठा hclge_cfg_छोड़ो_param_cmd *छोड़ो_param;
	काष्ठा hclge_desc desc;

	छोड़ो_param = (काष्ठा hclge_cfg_छोड़ो_param_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_MAC_PARA, false);

	ether_addr_copy(छोड़ो_param->mac_addr, addr);
	ether_addr_copy(छोड़ो_param->mac_addr_extra, addr);
	छोड़ो_param->छोड़ो_trans_gap = छोड़ो_trans_gap;
	छोड़ो_param->छोड़ो_trans_समय = cpu_to_le16(छोड़ो_trans_समय);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

पूर्णांक hclge_छोड़ो_addr_cfg(काष्ठा hclge_dev *hdev, स्थिर u8 *mac_addr)
अणु
	काष्ठा hclge_cfg_छोड़ो_param_cmd *छोड़ो_param;
	काष्ठा hclge_desc desc;
	u16 trans_समय;
	u8 trans_gap;
	पूर्णांक ret;

	छोड़ो_param = (काष्ठा hclge_cfg_छोड़ो_param_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_MAC_PARA, true);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret)
		वापस ret;

	trans_gap = छोड़ो_param->छोड़ो_trans_gap;
	trans_समय = le16_to_cpu(छोड़ो_param->छोड़ो_trans_समय);

	वापस hclge_छोड़ो_param_cfg(hdev, mac_addr, trans_gap, trans_समय);
पूर्ण

अटल पूर्णांक hclge_fill_pri_array(काष्ठा hclge_dev *hdev, u8 *pri, u8 pri_id)
अणु
	u8 tc;

	tc = hdev->पंचांग_info.prio_tc[pri_id];

	अगर (tc >= hdev->पंचांग_info.num_tc)
		वापस -EINVAL;

	/**
	 * the रेजिस्टर क्रम priority has four bytes, the first bytes includes
	 *  priority0 and priority1, the higher 4bit stands क्रम priority1
	 *  जबतक the lower 4bit stands क्रम priority0, as below:
	 * first byte:	| pri_1 | pri_0 |
	 * second byte:	| pri_3 | pri_2 |
	 * third byte:	| pri_5 | pri_4 |
	 * fourth byte:	| pri_7 | pri_6 |
	 */
	pri[pri_id >> 1] |= tc << ((pri_id & 1) * 4);

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_up_to_tc_map(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_desc desc;
	u8 *pri = (u8 *)desc.data;
	u8 pri_id;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_PRI_TO_TC_MAPPING, false);

	क्रम (pri_id = 0; pri_id < HNAE3_MAX_USER_PRIO; pri_id++) अणु
		ret = hclge_fill_pri_array(hdev, pri, pri_id);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_pg_to_pri_map_cfg(काष्ठा hclge_dev *hdev,
				      u8 pg_id, u8 pri_bit_map)
अणु
	काष्ठा hclge_pg_to_pri_link_cmd *map;
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PG_TO_PRI_LINK, false);

	map = (काष्ठा hclge_pg_to_pri_link_cmd *)desc.data;

	map->pg_id = pg_id;
	map->pri_bit_map = pri_bit_map;

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_qs_to_pri_map_cfg(काष्ठा hclge_dev *hdev,
				      u16 qs_id, u8 pri)
अणु
	काष्ठा hclge_qs_to_pri_link_cmd *map;
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_QS_TO_PRI_LINK, false);

	map = (काष्ठा hclge_qs_to_pri_link_cmd *)desc.data;

	map->qs_id = cpu_to_le16(qs_id);
	map->priority = pri;
	map->link_vld = HCLGE_TM_QS_PRI_LINK_VLD_MSK;

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_q_to_qs_map_cfg(काष्ठा hclge_dev *hdev,
				    u16 q_id, u16 qs_id)
अणु
	काष्ठा hclge_nq_to_qs_link_cmd *map;
	काष्ठा hclge_desc desc;
	u16 qs_id_l;
	u16 qs_id_h;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_NQ_TO_QS_LINK, false);

	map = (काष्ठा hclge_nq_to_qs_link_cmd *)desc.data;

	map->nq_id = cpu_to_le16(q_id);

	/* convert qs_id to the following क्रमmat to support qset_id >= 1024
	 * qs_id: | 15 | 14 ~ 10 |  9 ~ 0   |
	 *            /         / \         \
	 *           /         /   \         \
	 * qset_id: | 15 ~ 11 |  10 |  9 ~ 0  |
	 *          | qs_id_h | vld | qs_id_l |
	 */
	qs_id_l = hnae3_get_field(qs_id, HCLGE_TM_QS_ID_L_MSK,
				  HCLGE_TM_QS_ID_L_S);
	qs_id_h = hnae3_get_field(qs_id, HCLGE_TM_QS_ID_H_MSK,
				  HCLGE_TM_QS_ID_H_S);
	hnae3_set_field(qs_id, HCLGE_TM_QS_ID_L_MSK, HCLGE_TM_QS_ID_L_S,
			qs_id_l);
	hnae3_set_field(qs_id, HCLGE_TM_QS_ID_H_EXT_MSK, HCLGE_TM_QS_ID_H_EXT_S,
			qs_id_h);
	map->qset_id = cpu_to_le16(qs_id | HCLGE_TM_Q_QS_LINK_VLD_MSK);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_pg_weight_cfg(काष्ठा hclge_dev *hdev, u8 pg_id,
				  u8 dwrr)
अणु
	काष्ठा hclge_pg_weight_cmd *weight;
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PG_WEIGHT, false);

	weight = (काष्ठा hclge_pg_weight_cmd *)desc.data;

	weight->pg_id = pg_id;
	weight->dwrr = dwrr;

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_weight_cfg(काष्ठा hclge_dev *hdev, u8 pri_id,
				   u8 dwrr)
अणु
	काष्ठा hclge_priority_weight_cmd *weight;
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PRI_WEIGHT, false);

	weight = (काष्ठा hclge_priority_weight_cmd *)desc.data;

	weight->pri_id = pri_id;
	weight->dwrr = dwrr;

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_qs_weight_cfg(काष्ठा hclge_dev *hdev, u16 qs_id,
				  u8 dwrr)
अणु
	काष्ठा hclge_qs_weight_cmd *weight;
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_QS_WEIGHT, false);

	weight = (काष्ठा hclge_qs_weight_cmd *)desc.data;

	weight->qs_id = cpu_to_le16(qs_id);
	weight->dwrr = dwrr;

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल u32 hclge_पंचांग_get_shapping_para(u8 ir_b, u8 ir_u, u8 ir_s,
				      u8 bs_b, u8 bs_s)
अणु
	u32 shapping_para = 0;

	hclge_पंचांग_set_field(shapping_para, IR_B, ir_b);
	hclge_पंचांग_set_field(shapping_para, IR_U, ir_u);
	hclge_पंचांग_set_field(shapping_para, IR_S, ir_s);
	hclge_पंचांग_set_field(shapping_para, BS_B, bs_b);
	hclge_पंचांग_set_field(shapping_para, BS_S, bs_s);

	वापस shapping_para;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pg_shapping_cfg(काष्ठा hclge_dev *hdev,
				    क्रमागत hclge_shap_bucket bucket, u8 pg_id,
				    u32 shapping_para, u32 rate)
अणु
	काष्ठा hclge_pg_shapping_cmd *shap_cfg_cmd;
	क्रमागत hclge_opcode_type opcode;
	काष्ठा hclge_desc desc;

	opcode = bucket ? HCLGE_OPC_TM_PG_P_SHAPPING :
		 HCLGE_OPC_TM_PG_C_SHAPPING;
	hclge_cmd_setup_basic_desc(&desc, opcode, false);

	shap_cfg_cmd = (काष्ठा hclge_pg_shapping_cmd *)desc.data;

	shap_cfg_cmd->pg_id = pg_id;

	shap_cfg_cmd->pg_shapping_para = cpu_to_le32(shapping_para);

	hnae3_set_bit(shap_cfg_cmd->flag, HCLGE_TM_RATE_VLD, 1);

	shap_cfg_cmd->pg_rate = cpu_to_le32(rate);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_port_shaper_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_port_shapping_cmd *shap_cfg_cmd;
	काष्ठा hclge_shaper_ir_para ir_para;
	काष्ठा hclge_desc desc;
	u32 shapping_para;
	पूर्णांक ret;

	ret = hclge_shaper_para_calc(hdev->hw.mac.speed, HCLGE_SHAPER_LVL_PORT,
				     &ir_para,
				     hdev->ae_dev->dev_specs.max_पंचांग_rate);
	अगर (ret)
		वापस ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PORT_SHAPPING, false);
	shap_cfg_cmd = (काष्ठा hclge_port_shapping_cmd *)desc.data;

	shapping_para = hclge_पंचांग_get_shapping_para(ir_para.ir_b, ir_para.ir_u,
						   ir_para.ir_s,
						   HCLGE_SHAPER_BS_U_DEF,
						   HCLGE_SHAPER_BS_S_DEF);

	shap_cfg_cmd->port_shapping_para = cpu_to_le32(shapping_para);

	hnae3_set_bit(shap_cfg_cmd->flag, HCLGE_TM_RATE_VLD, 1);

	shap_cfg_cmd->port_rate = cpu_to_le32(hdev->hw.mac.speed);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_shapping_cfg(काष्ठा hclge_dev *hdev,
				     क्रमागत hclge_shap_bucket bucket, u8 pri_id,
				     u32 shapping_para, u32 rate)
अणु
	काष्ठा hclge_pri_shapping_cmd *shap_cfg_cmd;
	क्रमागत hclge_opcode_type opcode;
	काष्ठा hclge_desc desc;

	opcode = bucket ? HCLGE_OPC_TM_PRI_P_SHAPPING :
		 HCLGE_OPC_TM_PRI_C_SHAPPING;

	hclge_cmd_setup_basic_desc(&desc, opcode, false);

	shap_cfg_cmd = (काष्ठा hclge_pri_shapping_cmd *)desc.data;

	shap_cfg_cmd->pri_id = pri_id;

	shap_cfg_cmd->pri_shapping_para = cpu_to_le32(shapping_para);

	hnae3_set_bit(shap_cfg_cmd->flag, HCLGE_TM_RATE_VLD, 1);

	shap_cfg_cmd->pri_rate = cpu_to_le32(rate);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_pg_schd_mode_cfg(काष्ठा hclge_dev *hdev, u8 pg_id)
अणु
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PG_SCH_MODE_CFG, false);

	अगर (hdev->पंचांग_info.pg_info[pg_id].pg_sch_mode == HCLGE_SCH_MODE_DWRR)
		desc.data[1] = cpu_to_le32(HCLGE_TM_TX_SCHD_DWRR_MSK);
	अन्यथा
		desc.data[1] = 0;

	desc.data[0] = cpu_to_le32(pg_id);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_schd_mode_cfg(काष्ठा hclge_dev *hdev, u8 pri_id)
अणु
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PRI_SCH_MODE_CFG, false);

	अगर (hdev->पंचांग_info.tc_info[pri_id].tc_sch_mode == HCLGE_SCH_MODE_DWRR)
		desc.data[1] = cpu_to_le32(HCLGE_TM_TX_SCHD_DWRR_MSK);
	अन्यथा
		desc.data[1] = 0;

	desc.data[0] = cpu_to_le32(pri_id);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_qs_schd_mode_cfg(काष्ठा hclge_dev *hdev, u16 qs_id, u8 mode)
अणु
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_QS_SCH_MODE_CFG, false);

	अगर (mode == HCLGE_SCH_MODE_DWRR)
		desc.data[1] = cpu_to_le32(HCLGE_TM_TX_SCHD_DWRR_MSK);
	अन्यथा
		desc.data[1] = 0;

	desc.data[0] = cpu_to_le32(qs_id);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_qs_bp_cfg(काष्ठा hclge_dev *hdev, u8 tc, u8 grp_id,
			      u32 bit_map)
अणु
	काष्ठा hclge_bp_to_qs_map_cmd *bp_to_qs_map_cmd;
	काष्ठा hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_BP_TO_QSET_MAPPING,
				   false);

	bp_to_qs_map_cmd = (काष्ठा hclge_bp_to_qs_map_cmd *)desc.data;

	bp_to_qs_map_cmd->tc_id = tc;
	bp_to_qs_map_cmd->qs_group_id = grp_id;
	bp_to_qs_map_cmd->qs_bit_map = cpu_to_le32(bit_map);

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

पूर्णांक hclge_पंचांग_qs_shaper_cfg(काष्ठा hclge_vport *vport, पूर्णांक max_tx_rate)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hclge_qs_shapping_cmd *shap_cfg_cmd;
	काष्ठा hclge_shaper_ir_para ir_para;
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_desc desc;
	u32 shaper_para;
	पूर्णांक ret, i;

	अगर (!max_tx_rate)
		max_tx_rate = hdev->ae_dev->dev_specs.max_पंचांग_rate;

	ret = hclge_shaper_para_calc(max_tx_rate, HCLGE_SHAPER_LVL_QSET,
				     &ir_para,
				     hdev->ae_dev->dev_specs.max_पंचांग_rate);
	अगर (ret)
		वापस ret;

	shaper_para = hclge_पंचांग_get_shapping_para(ir_para.ir_b, ir_para.ir_u,
						 ir_para.ir_s,
						 HCLGE_SHAPER_BS_U_DEF,
						 HCLGE_SHAPER_BS_S_DEF);

	क्रम (i = 0; i < kinfo->tc_info.num_tc; i++) अणु
		hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_QCN_SHAPPING_CFG,
					   false);

		shap_cfg_cmd = (काष्ठा hclge_qs_shapping_cmd *)desc.data;
		shap_cfg_cmd->qs_id = cpu_to_le16(vport->qs_offset + i);
		shap_cfg_cmd->qs_shapping_para = cpu_to_le32(shaper_para);

		hnae3_set_bit(shap_cfg_cmd->flag, HCLGE_TM_RATE_VLD, 1);
		shap_cfg_cmd->qs_rate = cpu_to_le32(max_tx_rate);

		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		अगर (ret) अणु
			dev_err(&hdev->pdev->dev,
				"vf%u, qs%u failed to set tx_rate:%d, ret=%d\n",
				vport->vport_id, shap_cfg_cmd->qs_id,
				max_tx_rate, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 hclge_vport_get_max_rss_size(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hnae3_tc_info *tc_info = &kinfo->tc_info;
	काष्ठा hclge_dev *hdev = vport->back;
	u16 max_rss_size = 0;
	पूर्णांक i;

	अगर (!tc_info->mqprio_active)
		वापस vport->alloc_tqps / tc_info->num_tc;

	क्रम (i = 0; i < HNAE3_MAX_TC; i++) अणु
		अगर (!(hdev->hw_tc_map & BIT(i)) || i >= tc_info->num_tc)
			जारी;
		अगर (max_rss_size < tc_info->tqp_count[i])
			max_rss_size = tc_info->tqp_count[i];
	पूर्ण

	वापस max_rss_size;
पूर्ण

अटल u16 hclge_vport_get_tqp_num(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hnae3_tc_info *tc_info = &kinfo->tc_info;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक sum = 0;
	पूर्णांक i;

	अगर (!tc_info->mqprio_active)
		वापस kinfo->rss_size * tc_info->num_tc;

	क्रम (i = 0; i < HNAE3_MAX_TC; i++) अणु
		अगर (hdev->hw_tc_map & BIT(i) && i < tc_info->num_tc)
			sum += tc_info->tqp_count[i];
	पूर्ण

	वापस sum;
पूर्ण

अटल व्योम hclge_पंचांग_update_kinfo_rss_size(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hclge_dev *hdev = vport->back;
	u16 vport_max_rss_size;
	u16 max_rss_size;

	/* TC configuration is shared by PF/VF in one port, only allow
	 * one tc क्रम VF क्रम simplicity. VF's vport_id is non zero.
	 */
	अगर (vport->vport_id) अणु
		kinfo->tc_info.num_tc = 1;
		vport->qs_offset = HNAE3_MAX_TC +
				   vport->vport_id - HCLGE_VF_VPORT_START_NUM;
		vport_max_rss_size = hdev->vf_rss_size_max;
	पूर्ण अन्यथा अणु
		kinfo->tc_info.num_tc =
			min_t(u16, vport->alloc_tqps, hdev->पंचांग_info.num_tc);
		vport->qs_offset = 0;
		vport_max_rss_size = hdev->pf_rss_size_max;
	पूर्ण

	max_rss_size = min_t(u16, vport_max_rss_size,
			     hclge_vport_get_max_rss_size(vport));

	/* Set to user value, no larger than max_rss_size. */
	अगर (kinfo->req_rss_size != kinfo->rss_size && kinfo->req_rss_size &&
	    kinfo->req_rss_size <= max_rss_size) अणु
		dev_info(&hdev->pdev->dev, "rss changes from %u to %u\n",
			 kinfo->rss_size, kinfo->req_rss_size);
		kinfo->rss_size = kinfo->req_rss_size;
	पूर्ण अन्यथा अगर (kinfo->rss_size > max_rss_size ||
		   (!kinfo->req_rss_size && kinfo->rss_size < max_rss_size)) अणु
		/* Set to the maximum specअगरication value (max_rss_size). */
		kinfo->rss_size = max_rss_size;
	पूर्ण
पूर्ण

अटल व्योम hclge_पंचांग_vport_tc_info_update(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hclge_dev *hdev = vport->back;
	u8 i;

	hclge_पंचांग_update_kinfo_rss_size(vport);
	kinfo->num_tqps = hclge_vport_get_tqp_num(vport);
	vport->dwrr = 100;  /* 100 percent as init */
	vport->alloc_rss_size = kinfo->rss_size;
	vport->bw_limit = hdev->पंचांग_info.pg_info[0].bw_limit;

	/* when enable mqprio, the tc_info has been updated. */
	अगर (kinfo->tc_info.mqprio_active)
		वापस;

	क्रम (i = 0; i < HNAE3_MAX_TC; i++) अणु
		अगर (hdev->hw_tc_map & BIT(i) && i < kinfo->tc_info.num_tc) अणु
			set_bit(i, &kinfo->tc_info.tc_en);
			kinfo->tc_info.tqp_offset[i] = i * kinfo->rss_size;
			kinfo->tc_info.tqp_count[i] = kinfo->rss_size;
		पूर्ण अन्यथा अणु
			/* Set to शेष queue अगर TC is disable */
			clear_bit(i, &kinfo->tc_info.tc_en);
			kinfo->tc_info.tqp_offset[i] = 0;
			kinfo->tc_info.tqp_count[i] = 1;
		पूर्ण
	पूर्ण

	स_नकल(kinfo->tc_info.prio_tc, hdev->पंचांग_info.prio_tc,
	       माप_field(काष्ठा hnae3_tc_info, prio_tc));
पूर्ण

अटल व्योम hclge_पंचांग_vport_info_update(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	u32 i;

	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		hclge_पंचांग_vport_tc_info_update(vport);

		vport++;
	पूर्ण
पूर्ण

अटल व्योम hclge_पंचांग_tc_info_init(काष्ठा hclge_dev *hdev)
अणु
	u8 i;

	क्रम (i = 0; i < hdev->पंचांग_info.num_tc; i++) अणु
		hdev->पंचांग_info.tc_info[i].tc_id = i;
		hdev->पंचांग_info.tc_info[i].tc_sch_mode = HCLGE_SCH_MODE_DWRR;
		hdev->पंचांग_info.tc_info[i].pgid = 0;
		hdev->पंचांग_info.tc_info[i].bw_limit =
			hdev->पंचांग_info.pg_info[0].bw_limit;
	पूर्ण

	क्रम (i = 0; i < HNAE3_MAX_USER_PRIO; i++)
		hdev->पंचांग_info.prio_tc[i] =
			(i >= hdev->पंचांग_info.num_tc) ? 0 : i;

	/* DCB is enabled अगर we have more than 1 TC or pfc_en is
	 * non-zero.
	 */
	अगर (hdev->पंचांग_info.num_tc > 1 || hdev->पंचांग_info.pfc_en)
		hdev->flag |= HCLGE_FLAG_DCB_ENABLE;
	अन्यथा
		hdev->flag &= ~HCLGE_FLAG_DCB_ENABLE;
पूर्ण

अटल व्योम hclge_पंचांग_pg_info_init(काष्ठा hclge_dev *hdev)
अणु
#घोषणा BW_PERCENT	100

	u8 i;

	क्रम (i = 0; i < hdev->पंचांग_info.num_pg; i++) अणु
		पूर्णांक k;

		hdev->पंचांग_info.pg_dwrr[i] = i ? 0 : BW_PERCENT;

		hdev->पंचांग_info.pg_info[i].pg_id = i;
		hdev->पंचांग_info.pg_info[i].pg_sch_mode = HCLGE_SCH_MODE_DWRR;

		hdev->पंचांग_info.pg_info[i].bw_limit =
					hdev->ae_dev->dev_specs.max_पंचांग_rate;

		अगर (i != 0)
			जारी;

		hdev->पंचांग_info.pg_info[i].tc_bit_map = hdev->hw_tc_map;
		क्रम (k = 0; k < hdev->पंचांग_info.num_tc; k++)
			hdev->पंचांग_info.pg_info[i].tc_dwrr[k] = BW_PERCENT;
	पूर्ण
पूर्ण

अटल व्योम hclge_update_fc_mode_by_dcb_flag(काष्ठा hclge_dev *hdev)
अणु
	अगर (!(hdev->flag & HCLGE_FLAG_DCB_ENABLE)) अणु
		अगर (hdev->fc_mode_last_समय == HCLGE_FC_PFC)
			dev_warn(&hdev->pdev->dev,
				 "DCB is disable, but last mode is FC_PFC\n");

		hdev->पंचांग_info.fc_mode = hdev->fc_mode_last_समय;
	पूर्ण अन्यथा अगर (hdev->पंचांग_info.fc_mode != HCLGE_FC_PFC) अणु
		/* fc_mode_last_समय record the last fc_mode when
		 * DCB is enabled, so that fc_mode can be set to
		 * the correct value when DCB is disabled.
		 */
		hdev->fc_mode_last_समय = hdev->पंचांग_info.fc_mode;
		hdev->पंचांग_info.fc_mode = HCLGE_FC_PFC;
	पूर्ण
पूर्ण

अटल व्योम hclge_update_fc_mode(काष्ठा hclge_dev *hdev)
अणु
	अगर (!hdev->पंचांग_info.pfc_en) अणु
		hdev->पंचांग_info.fc_mode = hdev->fc_mode_last_समय;
		वापस;
	पूर्ण

	अगर (hdev->पंचांग_info.fc_mode != HCLGE_FC_PFC) अणु
		hdev->fc_mode_last_समय = hdev->पंचांग_info.fc_mode;
		hdev->पंचांग_info.fc_mode = HCLGE_FC_PFC;
	पूर्ण
पूर्ण

अटल व्योम hclge_pfc_info_init(काष्ठा hclge_dev *hdev)
अणु
	अगर (hdev->ae_dev->dev_version >= HNAE3_DEVICE_VERSION_V3)
		hclge_update_fc_mode(hdev);
	अन्यथा
		hclge_update_fc_mode_by_dcb_flag(hdev);
पूर्ण

अटल व्योम hclge_पंचांग_schd_info_init(काष्ठा hclge_dev *hdev)
अणु
	hclge_पंचांग_pg_info_init(hdev);

	hclge_पंचांग_tc_info_init(hdev);

	hclge_पंचांग_vport_info_update(hdev);

	hclge_pfc_info_init(hdev);
पूर्ण

अटल पूर्णांक hclge_पंचांग_pg_to_pri_map(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;
	u32 i;

	अगर (hdev->tx_sch_mode != HCLGE_FLAG_TC_BASE_SCH_MODE)
		वापस 0;

	क्रम (i = 0; i < hdev->पंचांग_info.num_pg; i++) अणु
		/* Cfg mapping */
		ret = hclge_पंचांग_pg_to_pri_map_cfg(
			hdev, i, hdev->पंचांग_info.pg_info[i].tc_bit_map);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pg_shaper_cfg(काष्ठा hclge_dev *hdev)
अणु
	u32 max_पंचांग_rate = hdev->ae_dev->dev_specs.max_पंचांग_rate;
	काष्ठा hclge_shaper_ir_para ir_para;
	u32 shaper_para;
	पूर्णांक ret;
	u32 i;

	/* Cfg pg schd */
	अगर (hdev->tx_sch_mode != HCLGE_FLAG_TC_BASE_SCH_MODE)
		वापस 0;

	/* Pg to pri */
	क्रम (i = 0; i < hdev->पंचांग_info.num_pg; i++) अणु
		u32 rate = hdev->पंचांग_info.pg_info[i].bw_limit;

		/* Calc shaper para */
		ret = hclge_shaper_para_calc(rate, HCLGE_SHAPER_LVL_PG,
					     &ir_para, max_पंचांग_rate);
		अगर (ret)
			वापस ret;

		shaper_para = hclge_पंचांग_get_shapping_para(0, 0, 0,
							 HCLGE_SHAPER_BS_U_DEF,
							 HCLGE_SHAPER_BS_S_DEF);
		ret = hclge_पंचांग_pg_shapping_cfg(hdev,
					       HCLGE_TM_SHAP_C_BUCKET, i,
					       shaper_para, rate);
		अगर (ret)
			वापस ret;

		shaper_para = hclge_पंचांग_get_shapping_para(ir_para.ir_b,
							 ir_para.ir_u,
							 ir_para.ir_s,
							 HCLGE_SHAPER_BS_U_DEF,
							 HCLGE_SHAPER_BS_S_DEF);
		ret = hclge_पंचांग_pg_shapping_cfg(hdev,
					       HCLGE_TM_SHAP_P_BUCKET, i,
					       shaper_para, rate);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pg_dwrr_cfg(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;
	u32 i;

	/* cfg pg schd */
	अगर (hdev->tx_sch_mode != HCLGE_FLAG_TC_BASE_SCH_MODE)
		वापस 0;

	/* pg to prio */
	क्रम (i = 0; i < hdev->पंचांग_info.num_pg; i++) अणु
		/* Cfg dwrr */
		ret = hclge_पंचांग_pg_weight_cfg(hdev, i, hdev->पंचांग_info.pg_dwrr[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_vport_q_to_qs_map(काष्ठा hclge_dev *hdev,
				   काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hnae3_tc_info *tc_info = &kinfo->tc_info;
	काष्ठा hnae3_queue **tqp = kinfo->tqp;
	u32 i, j;
	पूर्णांक ret;

	क्रम (i = 0; i < tc_info->num_tc; i++) अणु
		क्रम (j = 0; j < tc_info->tqp_count[i]; j++) अणु
			काष्ठा hnae3_queue *q = tqp[tc_info->tqp_offset[i] + j];

			ret = hclge_पंचांग_q_to_qs_map_cfg(hdev,
						       hclge_get_queue_id(q),
						       vport->qs_offset + i);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_q_qs_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	पूर्णांक ret;
	u32 i, k;

	अगर (hdev->tx_sch_mode == HCLGE_FLAG_TC_BASE_SCH_MODE) अणु
		/* Cfg qs -> pri mapping, one by one mapping */
		क्रम (k = 0; k < hdev->num_alloc_vport; k++) अणु
			काष्ठा hnae3_knic_निजी_info *kinfo =
				&vport[k].nic.kinfo;

			क्रम (i = 0; i < kinfo->tc_info.num_tc; i++) अणु
				ret = hclge_पंचांग_qs_to_pri_map_cfg(
					hdev, vport[k].qs_offset + i, i);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (hdev->tx_sch_mode == HCLGE_FLAG_VNET_BASE_SCH_MODE) अणु
		/* Cfg qs -> pri mapping,  qs = tc, pri = vf, 8 qs -> 1 pri */
		क्रम (k = 0; k < hdev->num_alloc_vport; k++)
			क्रम (i = 0; i < HNAE3_MAX_TC; i++) अणु
				ret = hclge_पंचांग_qs_to_pri_map_cfg(
					hdev, vport[k].qs_offset + i, k);
				अगर (ret)
					वापस ret;
			पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* Cfg q -> qs mapping */
	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		ret = hclge_vport_q_to_qs_map(hdev, vport);
		अगर (ret)
			वापस ret;

		vport++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_tc_base_shaper_cfg(काष्ठा hclge_dev *hdev)
अणु
	u32 max_पंचांग_rate = hdev->ae_dev->dev_specs.max_पंचांग_rate;
	काष्ठा hclge_shaper_ir_para ir_para;
	u32 shaper_para;
	पूर्णांक ret;
	u32 i;

	क्रम (i = 0; i < hdev->पंचांग_info.num_tc; i++) अणु
		u32 rate = hdev->पंचांग_info.tc_info[i].bw_limit;

		ret = hclge_shaper_para_calc(rate, HCLGE_SHAPER_LVL_PRI,
					     &ir_para, max_पंचांग_rate);
		अगर (ret)
			वापस ret;

		shaper_para = hclge_पंचांग_get_shapping_para(0, 0, 0,
							 HCLGE_SHAPER_BS_U_DEF,
							 HCLGE_SHAPER_BS_S_DEF);
		ret = hclge_पंचांग_pri_shapping_cfg(hdev, HCLGE_TM_SHAP_C_BUCKET, i,
						shaper_para, rate);
		अगर (ret)
			वापस ret;

		shaper_para = hclge_पंचांग_get_shapping_para(ir_para.ir_b,
							 ir_para.ir_u,
							 ir_para.ir_s,
							 HCLGE_SHAPER_BS_U_DEF,
							 HCLGE_SHAPER_BS_S_DEF);
		ret = hclge_पंचांग_pri_shapping_cfg(hdev, HCLGE_TM_SHAP_P_BUCKET, i,
						shaper_para, rate);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_vnet_base_shaper_pri_cfg(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hclge_dev *hdev = vport->back;
	काष्ठा hclge_shaper_ir_para ir_para;
	u32 shaper_para;
	पूर्णांक ret;

	ret = hclge_shaper_para_calc(vport->bw_limit, HCLGE_SHAPER_LVL_VF,
				     &ir_para,
				     hdev->ae_dev->dev_specs.max_पंचांग_rate);
	अगर (ret)
		वापस ret;

	shaper_para = hclge_पंचांग_get_shapping_para(0, 0, 0,
						 HCLGE_SHAPER_BS_U_DEF,
						 HCLGE_SHAPER_BS_S_DEF);
	ret = hclge_पंचांग_pri_shapping_cfg(hdev, HCLGE_TM_SHAP_C_BUCKET,
					vport->vport_id, shaper_para,
					vport->bw_limit);
	अगर (ret)
		वापस ret;

	shaper_para = hclge_पंचांग_get_shapping_para(ir_para.ir_b, ir_para.ir_u,
						 ir_para.ir_s,
						 HCLGE_SHAPER_BS_U_DEF,
						 HCLGE_SHAPER_BS_S_DEF);
	ret = hclge_पंचांग_pri_shapping_cfg(hdev, HCLGE_TM_SHAP_P_BUCKET,
					vport->vport_id, shaper_para,
					vport->bw_limit);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_vnet_base_shaper_qs_cfg(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hclge_dev *hdev = vport->back;
	u32 max_पंचांग_rate = hdev->ae_dev->dev_specs.max_पंचांग_rate;
	काष्ठा hclge_shaper_ir_para ir_para;
	u32 i;
	पूर्णांक ret;

	क्रम (i = 0; i < kinfo->tc_info.num_tc; i++) अणु
		ret = hclge_shaper_para_calc(hdev->पंचांग_info.tc_info[i].bw_limit,
					     HCLGE_SHAPER_LVL_QSET,
					     &ir_para, max_पंचांग_rate);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_vnet_base_shaper_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	पूर्णांक ret;
	u32 i;

	/* Need config vport shaper */
	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		ret = hclge_पंचांग_pri_vnet_base_shaper_pri_cfg(vport);
		अगर (ret)
			वापस ret;

		ret = hclge_पंचांग_pri_vnet_base_shaper_qs_cfg(vport);
		अगर (ret)
			वापस ret;

		vport++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_shaper_cfg(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	अगर (hdev->tx_sch_mode == HCLGE_FLAG_TC_BASE_SCH_MODE) अणु
		ret = hclge_पंचांग_pri_tc_base_shaper_cfg(hdev);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = hclge_पंचांग_pri_vnet_base_shaper_cfg(hdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_tc_base_dwrr_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	काष्ठा hclge_pg_info *pg_info;
	u8 dwrr;
	पूर्णांक ret;
	u32 i, k;

	क्रम (i = 0; i < hdev->पंचांग_info.num_tc; i++) अणु
		pg_info =
			&hdev->पंचांग_info.pg_info[hdev->पंचांग_info.tc_info[i].pgid];
		dwrr = pg_info->tc_dwrr[i];

		ret = hclge_पंचांग_pri_weight_cfg(hdev, i, dwrr);
		अगर (ret)
			वापस ret;

		क्रम (k = 0; k < hdev->num_alloc_vport; k++) अणु
			ret = hclge_पंचांग_qs_weight_cfg(
				hdev, vport[k].qs_offset + i,
				vport[k].dwrr);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_ets_tc_dwrr_cfg(काष्ठा hclge_dev *hdev)
अणु
#घोषणा DEFAULT_TC_WEIGHT	1
#घोषणा DEFAULT_TC_OFFSET	14

	काष्ठा hclge_ets_tc_weight_cmd *ets_weight;
	काष्ठा hclge_desc desc;
	अचिन्हित पूर्णांक i;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_ETS_TC_WEIGHT, false);
	ets_weight = (काष्ठा hclge_ets_tc_weight_cmd *)desc.data;

	क्रम (i = 0; i < HNAE3_MAX_TC; i++) अणु
		काष्ठा hclge_pg_info *pg_info;

		ets_weight->tc_weight[i] = DEFAULT_TC_WEIGHT;

		अगर (!(hdev->hw_tc_map & BIT(i)))
			जारी;

		pg_info =
			&hdev->पंचांग_info.pg_info[hdev->पंचांग_info.tc_info[i].pgid];
		ets_weight->tc_weight[i] = pg_info->tc_dwrr[i];
	पूर्ण

	ets_weight->weight_offset = DEFAULT_TC_OFFSET;

	वापस hclge_cmd_send(&hdev->hw, &desc, 1);
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_vnet_base_dwrr_pri_cfg(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;
	u8 i;

	/* Vf dwrr */
	ret = hclge_पंचांग_pri_weight_cfg(hdev, vport->vport_id, vport->dwrr);
	अगर (ret)
		वापस ret;

	/* Qset dwrr */
	क्रम (i = 0; i < kinfo->tc_info.num_tc; i++) अणु
		ret = hclge_पंचांग_qs_weight_cfg(
			hdev, vport->qs_offset + i,
			hdev->पंचांग_info.pg_info[0].tc_dwrr[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_vnet_base_dwrr_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	पूर्णांक ret;
	u32 i;

	क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
		ret = hclge_पंचांग_pri_vnet_base_dwrr_pri_cfg(vport);
		अगर (ret)
			वापस ret;

		vport++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_pri_dwrr_cfg(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	अगर (hdev->tx_sch_mode == HCLGE_FLAG_TC_BASE_SCH_MODE) अणु
		ret = hclge_पंचांग_pri_tc_base_dwrr_cfg(hdev);
		अगर (ret)
			वापस ret;

		अगर (!hnae3_dev_dcb_supported(hdev))
			वापस 0;

		ret = hclge_पंचांग_ets_tc_dwrr_cfg(hdev);
		अगर (ret == -EOPNOTSUPP) अणु
			dev_warn(&hdev->pdev->dev,
				 "fw %08x does't support ets tc weight cmd\n",
				 hdev->fw_version);
			ret = 0;
		पूर्ण

		वापस ret;
	पूर्ण अन्यथा अणु
		ret = hclge_पंचांग_pri_vnet_base_dwrr_cfg(hdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_map_cfg(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_up_to_tc_map(hdev);
	अगर (ret)
		वापस ret;

	ret = hclge_पंचांग_pg_to_pri_map(hdev);
	अगर (ret)
		वापस ret;

	वापस hclge_पंचांग_pri_q_qs_cfg(hdev);
पूर्ण

अटल पूर्णांक hclge_पंचांग_shaper_cfg(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_पंचांग_port_shaper_cfg(hdev);
	अगर (ret)
		वापस ret;

	ret = hclge_पंचांग_pg_shaper_cfg(hdev);
	अगर (ret)
		वापस ret;

	वापस hclge_पंचांग_pri_shaper_cfg(hdev);
पूर्ण

पूर्णांक hclge_पंचांग_dwrr_cfg(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_पंचांग_pg_dwrr_cfg(hdev);
	अगर (ret)
		वापस ret;

	वापस hclge_पंचांग_pri_dwrr_cfg(hdev);
पूर्ण

अटल पूर्णांक hclge_पंचांग_lvl2_schd_mode_cfg(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;
	u8 i;

	/* Only being config on TC-Based scheduler mode */
	अगर (hdev->tx_sch_mode == HCLGE_FLAG_VNET_BASE_SCH_MODE)
		वापस 0;

	क्रम (i = 0; i < hdev->पंचांग_info.num_pg; i++) अणु
		ret = hclge_पंचांग_pg_schd_mode_cfg(hdev, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_schd_mode_vnet_base_cfg(काष्ठा hclge_vport *vport)
अणु
	काष्ठा hnae3_knic_निजी_info *kinfo = &vport->nic.kinfo;
	काष्ठा hclge_dev *hdev = vport->back;
	पूर्णांक ret;
	u8 i;

	अगर (vport->vport_id >= HNAE3_MAX_TC)
		वापस -EINVAL;

	ret = hclge_पंचांग_pri_schd_mode_cfg(hdev, vport->vport_id);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < kinfo->tc_info.num_tc; i++) अणु
		u8 sch_mode = hdev->पंचांग_info.tc_info[i].tc_sch_mode;

		ret = hclge_पंचांग_qs_schd_mode_cfg(hdev, vport->qs_offset + i,
						sch_mode);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_lvl34_schd_mode_cfg(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	पूर्णांक ret;
	u8 i, k;

	अगर (hdev->tx_sch_mode == HCLGE_FLAG_TC_BASE_SCH_MODE) अणु
		क्रम (i = 0; i < hdev->पंचांग_info.num_tc; i++) अणु
			ret = hclge_पंचांग_pri_schd_mode_cfg(hdev, i);
			अगर (ret)
				वापस ret;

			क्रम (k = 0; k < hdev->num_alloc_vport; k++) अणु
				ret = hclge_पंचांग_qs_schd_mode_cfg(
					hdev, vport[k].qs_offset + i,
					HCLGE_SCH_MODE_DWRR);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < hdev->num_alloc_vport; i++) अणु
			ret = hclge_पंचांग_schd_mode_vnet_base_cfg(vport);
			अगर (ret)
				वापस ret;

			vport++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_पंचांग_schd_mode_hw(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	ret = hclge_पंचांग_lvl2_schd_mode_cfg(hdev);
	अगर (ret)
		वापस ret;

	वापस hclge_पंचांग_lvl34_schd_mode_cfg(hdev);
पूर्ण

पूर्णांक hclge_पंचांग_schd_setup_hw(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;

	/* Cfg पंचांग mapping  */
	ret = hclge_पंचांग_map_cfg(hdev);
	अगर (ret)
		वापस ret;

	/* Cfg पंचांग shaper */
	ret = hclge_पंचांग_shaper_cfg(hdev);
	अगर (ret)
		वापस ret;

	/* Cfg dwrr */
	ret = hclge_पंचांग_dwrr_cfg(hdev);
	अगर (ret)
		वापस ret;

	/* Cfg schd mode क्रम each level schd */
	वापस hclge_पंचांग_schd_mode_hw(hdev);
पूर्ण

अटल पूर्णांक hclge_छोड़ो_param_setup_hw(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_mac *mac = &hdev->hw.mac;

	वापस hclge_छोड़ो_param_cfg(hdev, mac->mac_addr,
				     HCLGE_DEFAULT_PAUSE_TRANS_GAP,
				     HCLGE_DEFAULT_PAUSE_TRANS_TIME);
पूर्ण

अटल पूर्णांक hclge_pfc_setup_hw(काष्ठा hclge_dev *hdev)
अणु
	u8 enable_biपंचांगap = 0;

	अगर (hdev->पंचांग_info.fc_mode == HCLGE_FC_PFC)
		enable_biपंचांगap = HCLGE_TX_MAC_PAUSE_EN_MSK |
				HCLGE_RX_MAC_PAUSE_EN_MSK;

	वापस hclge_pfc_छोड़ो_en_cfg(hdev, enable_biपंचांगap,
				      hdev->पंचांग_info.pfc_en);
पूर्ण

/* क्रम the queues that use क्रम backpress, भागides to several groups,
 * each group contains 32 queue sets, which can be represented by u32 biपंचांगap.
 */
अटल पूर्णांक hclge_bp_setup_hw(काष्ठा hclge_dev *hdev, u8 tc)
अणु
	u16 grp_id_shअगरt = HCLGE_BP_GRP_ID_S;
	u16 grp_id_mask = HCLGE_BP_GRP_ID_M;
	u8 grp_num = HCLGE_BP_GRP_NUM;
	पूर्णांक i;

	अगर (hdev->num_tqps > HCLGE_TQP_MAX_SIZE_DEV_V2) अणु
		grp_num = HCLGE_BP_EXT_GRP_NUM;
		grp_id_mask = HCLGE_BP_EXT_GRP_ID_M;
		grp_id_shअगरt = HCLGE_BP_EXT_GRP_ID_S;
	पूर्ण

	क्रम (i = 0; i < grp_num; i++) अणु
		u32 qs_biपंचांगap = 0;
		पूर्णांक k, ret;

		क्रम (k = 0; k < hdev->num_alloc_vport; k++) अणु
			काष्ठा hclge_vport *vport = &hdev->vport[k];
			u16 qs_id = vport->qs_offset + tc;
			u8 grp, sub_grp;

			grp = hnae3_get_field(qs_id, grp_id_mask, grp_id_shअगरt);
			sub_grp = hnae3_get_field(qs_id, HCLGE_BP_SUB_GRP_ID_M,
						  HCLGE_BP_SUB_GRP_ID_S);
			अगर (i == grp)
				qs_biपंचांगap |= (1 << sub_grp);
		पूर्ण

		ret = hclge_पंचांग_qs_bp_cfg(hdev, tc, i, qs_biपंचांगap);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hclge_mac_छोड़ो_setup_hw(काष्ठा hclge_dev *hdev)
अणु
	bool tx_en, rx_en;

	चयन (hdev->पंचांग_info.fc_mode) अणु
	हाल HCLGE_FC_NONE:
		tx_en = false;
		rx_en = false;
		अवरोध;
	हाल HCLGE_FC_RX_PAUSE:
		tx_en = false;
		rx_en = true;
		अवरोध;
	हाल HCLGE_FC_TX_PAUSE:
		tx_en = true;
		rx_en = false;
		अवरोध;
	हाल HCLGE_FC_FULL:
		tx_en = true;
		rx_en = true;
		अवरोध;
	हाल HCLGE_FC_PFC:
		tx_en = false;
		rx_en = false;
		अवरोध;
	शेष:
		tx_en = true;
		rx_en = true;
	पूर्ण

	वापस hclge_mac_छोड़ो_en_cfg(hdev, tx_en, rx_en);
पूर्ण

अटल पूर्णांक hclge_पंचांग_bp_setup(काष्ठा hclge_dev *hdev)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < hdev->पंचांग_info.num_tc; i++) अणु
		ret = hclge_bp_setup_hw(hdev, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hclge_छोड़ो_setup_hw(काष्ठा hclge_dev *hdev, bool init)
अणु
	पूर्णांक ret;

	ret = hclge_छोड़ो_param_setup_hw(hdev);
	अगर (ret)
		वापस ret;

	ret = hclge_mac_छोड़ो_setup_hw(hdev);
	अगर (ret)
		वापस ret;

	/* Only DCB-supported dev supports qset back pressure and pfc cmd */
	अगर (!hnae3_dev_dcb_supported(hdev))
		वापस 0;

	/* GE MAC करोes not support PFC, when driver is initializing and MAC
	 * is in GE Mode, ignore the error here, otherwise initialization
	 * will fail.
	 */
	ret = hclge_pfc_setup_hw(hdev);
	अगर (init && ret == -EOPNOTSUPP)
		dev_warn(&hdev->pdev->dev, "GE MAC does not support pfc\n");
	अन्यथा अगर (ret) अणु
		dev_err(&hdev->pdev->dev, "config pfc failed! ret = %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस hclge_पंचांग_bp_setup(hdev);
पूर्ण

व्योम hclge_पंचांग_prio_tc_info_update(काष्ठा hclge_dev *hdev, u8 *prio_tc)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	काष्ठा hnae3_knic_निजी_info *kinfo;
	u32 i, k;

	क्रम (i = 0; i < HNAE3_MAX_USER_PRIO; i++) अणु
		hdev->पंचांग_info.prio_tc[i] = prio_tc[i];

		क्रम (k = 0;  k < hdev->num_alloc_vport; k++) अणु
			kinfo = &vport[k].nic.kinfo;
			kinfo->tc_info.prio_tc[i] = prio_tc[i];
		पूर्ण
	पूर्ण
पूर्ण

व्योम hclge_पंचांग_schd_info_update(काष्ठा hclge_dev *hdev, u8 num_tc)
अणु
	u8 bit_map = 0;
	u8 i;

	hdev->पंचांग_info.num_tc = num_tc;

	क्रम (i = 0; i < hdev->पंचांग_info.num_tc; i++)
		bit_map |= BIT(i);

	अगर (!bit_map) अणु
		bit_map = 1;
		hdev->पंचांग_info.num_tc = 1;
	पूर्ण

	hdev->hw_tc_map = bit_map;

	hclge_पंचांग_schd_info_init(hdev);
पूर्ण

व्योम hclge_पंचांग_pfc_info_update(काष्ठा hclge_dev *hdev)
अणु
	/* DCB is enabled अगर we have more than 1 TC or pfc_en is
	 * non-zero.
	 */
	अगर (hdev->पंचांग_info.num_tc > 1 || hdev->पंचांग_info.pfc_en)
		hdev->flag |= HCLGE_FLAG_DCB_ENABLE;
	अन्यथा
		hdev->flag &= ~HCLGE_FLAG_DCB_ENABLE;

	hclge_pfc_info_init(hdev);
पूर्ण

पूर्णांक hclge_पंचांग_init_hw(काष्ठा hclge_dev *hdev, bool init)
अणु
	पूर्णांक ret;

	अगर ((hdev->tx_sch_mode != HCLGE_FLAG_TC_BASE_SCH_MODE) &&
	    (hdev->tx_sch_mode != HCLGE_FLAG_VNET_BASE_SCH_MODE))
		वापस -ENOTSUPP;

	ret = hclge_पंचांग_schd_setup_hw(hdev);
	अगर (ret)
		वापस ret;

	ret = hclge_छोड़ो_setup_hw(hdev, init);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक hclge_पंचांग_schd_init(काष्ठा hclge_dev *hdev)
अणु
	/* fc_mode is HCLGE_FC_FULL on reset */
	hdev->पंचांग_info.fc_mode = HCLGE_FC_FULL;
	hdev->fc_mode_last_समय = hdev->पंचांग_info.fc_mode;

	अगर (hdev->tx_sch_mode != HCLGE_FLAG_TC_BASE_SCH_MODE &&
	    hdev->पंचांग_info.num_pg != 1)
		वापस -EINVAL;

	hclge_पंचांग_schd_info_init(hdev);

	वापस hclge_पंचांग_init_hw(hdev, true);
पूर्ण

पूर्णांक hclge_पंचांग_vport_map_update(काष्ठा hclge_dev *hdev)
अणु
	काष्ठा hclge_vport *vport = hdev->vport;
	पूर्णांक ret;

	hclge_पंचांग_vport_tc_info_update(vport);

	ret = hclge_vport_q_to_qs_map(hdev, vport);
	अगर (ret)
		वापस ret;

	अगर (!(hdev->flag & HCLGE_FLAG_DCB_ENABLE))
		वापस 0;

	वापस hclge_पंचांग_bp_setup(hdev);
पूर्ण

पूर्णांक hclge_पंचांग_get_qset_num(काष्ठा hclge_dev *hdev, u16 *qset_num)
अणु
	काष्ठा hclge_पंचांग_nodes_cmd *nodes;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	अगर (hdev->ae_dev->dev_version <= HNAE3_DEVICE_VERSION_V2) अणु
		/* Each PF has 8 qsets and each VF has 1 qset */
		*qset_num = HCLGE_TM_PF_MAX_QSET_NUM + pci_num_vf(hdev->pdev);
		वापस 0;
	पूर्ण

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_NODES, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get qset num, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	nodes = (काष्ठा hclge_पंचांग_nodes_cmd *)desc.data;
	*qset_num = le16_to_cpu(nodes->qset_num);
	वापस 0;
पूर्ण

पूर्णांक hclge_पंचांग_get_pri_num(काष्ठा hclge_dev *hdev, u8 *pri_num)
अणु
	काष्ठा hclge_पंचांग_nodes_cmd *nodes;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	अगर (hdev->ae_dev->dev_version <= HNAE3_DEVICE_VERSION_V2) अणु
		*pri_num = HCLGE_TM_PF_MAX_PRI_NUM;
		वापस 0;
	पूर्ण

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_NODES, true);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get pri num, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	nodes = (काष्ठा hclge_पंचांग_nodes_cmd *)desc.data;
	*pri_num = nodes->pri_num;
	वापस 0;
पूर्ण

पूर्णांक hclge_पंचांग_get_qset_map_pri(काष्ठा hclge_dev *hdev, u16 qset_id, u8 *priority,
			      u8 *link_vld)
अणु
	काष्ठा hclge_qs_to_pri_link_cmd *map;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_QS_TO_PRI_LINK, true);
	map = (काष्ठा hclge_qs_to_pri_link_cmd *)desc.data;
	map->qs_id = cpu_to_le16(qset_id);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get qset map priority, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	*priority = map->priority;
	*link_vld = map->link_vld;
	वापस 0;
पूर्ण

पूर्णांक hclge_पंचांग_get_qset_sch_mode(काष्ठा hclge_dev *hdev, u16 qset_id, u8 *mode)
अणु
	काष्ठा hclge_qs_sch_mode_cfg_cmd *qs_sch_mode;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_QS_SCH_MODE_CFG, true);
	qs_sch_mode = (काष्ठा hclge_qs_sch_mode_cfg_cmd *)desc.data;
	qs_sch_mode->qs_id = cpu_to_le16(qset_id);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get qset sch mode, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	*mode = qs_sch_mode->sch_mode;
	वापस 0;
पूर्ण

पूर्णांक hclge_पंचांग_get_qset_weight(काष्ठा hclge_dev *hdev, u16 qset_id, u8 *weight)
अणु
	काष्ठा hclge_qs_weight_cmd *qs_weight;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_QS_WEIGHT, true);
	qs_weight = (काष्ठा hclge_qs_weight_cmd *)desc.data;
	qs_weight->qs_id = cpu_to_le16(qset_id);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get qset weight, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	*weight = qs_weight->dwrr;
	वापस 0;
पूर्ण

पूर्णांक hclge_पंचांग_get_pri_sch_mode(काष्ठा hclge_dev *hdev, u8 pri_id, u8 *mode)
अणु
	काष्ठा hclge_pri_sch_mode_cfg_cmd *pri_sch_mode;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PRI_SCH_MODE_CFG, true);
	pri_sch_mode = (काष्ठा hclge_pri_sch_mode_cfg_cmd *)desc.data;
	pri_sch_mode->pri_id = pri_id;
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get priority sch mode, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	*mode = pri_sch_mode->sch_mode;
	वापस 0;
पूर्ण

पूर्णांक hclge_पंचांग_get_pri_weight(काष्ठा hclge_dev *hdev, u8 pri_id, u8 *weight)
अणु
	काष्ठा hclge_priority_weight_cmd *priority_weight;
	काष्ठा hclge_desc desc;
	पूर्णांक ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PRI_WEIGHT, true);
	priority_weight = (काष्ठा hclge_priority_weight_cmd *)desc.data;
	priority_weight->pri_id = pri_id;
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get priority weight, ret = %d\n", ret);
		वापस ret;
	पूर्ण

	*weight = priority_weight->dwrr;
	वापस 0;
पूर्ण

पूर्णांक hclge_पंचांग_get_pri_shaper(काष्ठा hclge_dev *hdev, u8 pri_id,
			    क्रमागत hclge_opcode_type cmd,
			    काष्ठा hclge_pri_shaper_para *para)
अणु
	काष्ठा hclge_pri_shapping_cmd *shap_cfg_cmd;
	काष्ठा hclge_desc desc;
	u32 shapping_para;
	पूर्णांक ret;

	अगर (cmd != HCLGE_OPC_TM_PRI_C_SHAPPING &&
	    cmd != HCLGE_OPC_TM_PRI_P_SHAPPING)
		वापस -EINVAL;

	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	shap_cfg_cmd = (काष्ठा hclge_pri_shapping_cmd *)desc.data;
	shap_cfg_cmd->pri_id = pri_id;
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	अगर (ret) अणु
		dev_err(&hdev->pdev->dev,
			"failed to get priority shaper(%#x), ret = %d\n",
			cmd, ret);
		वापस ret;
	पूर्ण

	shapping_para = le32_to_cpu(shap_cfg_cmd->pri_shapping_para);
	para->ir_b = hclge_पंचांग_get_field(shapping_para, IR_B);
	para->ir_u = hclge_पंचांग_get_field(shapping_para, IR_U);
	para->ir_s = hclge_पंचांग_get_field(shapping_para, IR_S);
	para->bs_b = hclge_पंचांग_get_field(shapping_para, BS_B);
	para->bs_s = hclge_पंचांग_get_field(shapping_para, BS_S);
	para->flag = shap_cfg_cmd->flag;
	para->rate = le32_to_cpu(shap_cfg_cmd->pri_rate);
	वापस 0;
पूर्ण
