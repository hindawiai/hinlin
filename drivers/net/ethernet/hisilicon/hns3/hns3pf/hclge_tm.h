<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
// Copyright (c) 2016-2017 Hisilicon Limited.

#अगर_अघोषित __HCLGE_TM_H
#घोषणा __HCLGE_TM_H

#समावेश <linux/types.h>

/* MAC Pause */
#घोषणा HCLGE_TX_MAC_PAUSE_EN_MSK	BIT(0)
#घोषणा HCLGE_RX_MAC_PAUSE_EN_MSK	BIT(1)

#घोषणा HCLGE_TM_PORT_BASE_MODE_MSK	BIT(0)

#घोषणा HCLGE_DEFAULT_PAUSE_TRANS_GAP	0x7F
#घोषणा HCLGE_DEFAULT_PAUSE_TRANS_TIME	0xFFFF

/* SP or DWRR */
#घोषणा HCLGE_TM_TX_SCHD_DWRR_MSK	BIT(0)
#घोषणा HCLGE_TM_TX_SCHD_SP_MSK		0xFE

#घोषणा HCLGE_ETHER_MAX_RATE	100000

#घोषणा HCLGE_TM_PF_MAX_PRI_NUM		8
#घोषणा HCLGE_TM_PF_MAX_QSET_NUM	8

काष्ठा hclge_pg_to_pri_link_cmd अणु
	u8 pg_id;
	u8 rsvd1[3];
	u8 pri_bit_map;
पूर्ण;

काष्ठा hclge_qs_to_pri_link_cmd अणु
	__le16 qs_id;
	__le16 rsvd;
	u8 priority;
#घोषणा HCLGE_TM_QS_PRI_LINK_VLD_MSK	BIT(0)
	u8 link_vld;
पूर्ण;

काष्ठा hclge_nq_to_qs_link_cmd अणु
	__le16 nq_id;
	__le16 rsvd;
#घोषणा HCLGE_TM_Q_QS_LINK_VLD_MSK	BIT(10)
#घोषणा HCLGE_TM_QS_ID_L_MSK		GENMASK(9, 0)
#घोषणा HCLGE_TM_QS_ID_L_S		0
#घोषणा HCLGE_TM_QS_ID_H_MSK		GENMASK(14, 10)
#घोषणा HCLGE_TM_QS_ID_H_S		10
#घोषणा HCLGE_TM_QS_ID_H_EXT_S		11
#घोषणा HCLGE_TM_QS_ID_H_EXT_MSK	GENMASK(15, 11)
	__le16 qset_id;
पूर्ण;

काष्ठा hclge_tqp_tx_queue_tc_cmd अणु
	__le16 queue_id;
	__le16 rsvd;
	u8 tc_id;
	u8 rev[3];
पूर्ण;

काष्ठा hclge_pg_weight_cmd अणु
	u8 pg_id;
	u8 dwrr;
पूर्ण;

काष्ठा hclge_priority_weight_cmd अणु
	u8 pri_id;
	u8 dwrr;
पूर्ण;

काष्ठा hclge_pri_sch_mode_cfg_cmd अणु
	u8 pri_id;
	u8 rsvd[3];
	u8 sch_mode;
पूर्ण;

काष्ठा hclge_qs_sch_mode_cfg_cmd अणु
	__le16 qs_id;
	u8 rsvd[2];
	u8 sch_mode;
पूर्ण;

काष्ठा hclge_qs_weight_cmd अणु
	__le16 qs_id;
	u8 dwrr;
पूर्ण;

काष्ठा hclge_ets_tc_weight_cmd अणु
	u8 tc_weight[HNAE3_MAX_TC];
	u8 weight_offset;
	u8 rsvd[15];
पूर्ण;

#घोषणा HCLGE_TM_SHAP_IR_B_MSK  GENMASK(7, 0)
#घोषणा HCLGE_TM_SHAP_IR_B_LSH	0
#घोषणा HCLGE_TM_SHAP_IR_U_MSK  GENMASK(11, 8)
#घोषणा HCLGE_TM_SHAP_IR_U_LSH	8
#घोषणा HCLGE_TM_SHAP_IR_S_MSK  GENMASK(15, 12)
#घोषणा HCLGE_TM_SHAP_IR_S_LSH	12
#घोषणा HCLGE_TM_SHAP_BS_B_MSK  GENMASK(20, 16)
#घोषणा HCLGE_TM_SHAP_BS_B_LSH	16
#घोषणा HCLGE_TM_SHAP_BS_S_MSK  GENMASK(25, 21)
#घोषणा HCLGE_TM_SHAP_BS_S_LSH	21

क्रमागत hclge_shap_bucket अणु
	HCLGE_TM_SHAP_C_BUCKET = 0,
	HCLGE_TM_SHAP_P_BUCKET,
पूर्ण;

/* set bit HCLGE_TM_RATE_VLD to 1 means use 'rate' to config shaping */
#घोषणा HCLGE_TM_RATE_VLD	0

काष्ठा hclge_pri_shapping_cmd अणु
	u8 pri_id;
	u8 rsvd[3];
	__le32 pri_shapping_para;
	u8 flag;
	u8 rsvd1[3];
	__le32 pri_rate;
पूर्ण;

काष्ठा hclge_pg_shapping_cmd अणु
	u8 pg_id;
	u8 rsvd[3];
	__le32 pg_shapping_para;
	u8 flag;
	u8 rsvd1[3];
	__le32 pg_rate;
पूर्ण;

काष्ठा hclge_qs_shapping_cmd अणु
	__le16 qs_id;
	u8 rsvd[2];
	__le32 qs_shapping_para;
	u8 flag;
	u8 rsvd1[3];
	__le32 qs_rate;
पूर्ण;

#घोषणा HCLGE_BP_GRP_NUM		32
#घोषणा HCLGE_BP_SUB_GRP_ID_S		0
#घोषणा HCLGE_BP_SUB_GRP_ID_M		GENMASK(4, 0)
#घोषणा HCLGE_BP_GRP_ID_S		5
#घोषणा HCLGE_BP_GRP_ID_M		GENMASK(9, 5)

#घोषणा HCLGE_BP_EXT_GRP_NUM		40
#घोषणा HCLGE_BP_EXT_GRP_ID_S		5
#घोषणा HCLGE_BP_EXT_GRP_ID_M		GENMASK(10, 5)

काष्ठा hclge_bp_to_qs_map_cmd अणु
	u8 tc_id;
	u8 rsvd[2];
	u8 qs_group_id;
	__le32 qs_bit_map;
	u32 rsvd1;
पूर्ण;

काष्ठा hclge_pfc_en_cmd अणु
	u8 tx_rx_en_biपंचांगap;
	u8 pri_en_biपंचांगap;
पूर्ण;

काष्ठा hclge_cfg_छोड़ो_param_cmd अणु
	u8 mac_addr[ETH_ALEN];
	u8 छोड़ो_trans_gap;
	u8 rsvd;
	__le16 छोड़ो_trans_समय;
	u8 rsvd1[6];
	/* extra mac address to करो द्विगुन check क्रम छोड़ो frame */
	u8 mac_addr_extra[ETH_ALEN];
	u16 rsvd2;
पूर्ण;

काष्ठा hclge_pfc_stats_cmd अणु
	__le64 pkt_num[3];
पूर्ण;

काष्ठा hclge_port_shapping_cmd अणु
	__le32 port_shapping_para;
	u8 flag;
	u8 rsvd[3];
	__le32 port_rate;
पूर्ण;

काष्ठा hclge_shaper_ir_para अणु
	u8 ir_b; /* IR_B parameter of IR shaper */
	u8 ir_u; /* IR_U parameter of IR shaper */
	u8 ir_s; /* IR_S parameter of IR shaper */
पूर्ण;

काष्ठा hclge_पंचांग_nodes_cmd अणु
	u8 pg_base_id;
	u8 pri_base_id;
	__le16 qset_base_id;
	__le16 queue_base_id;
	u8 pg_num;
	u8 pri_num;
	__le16 qset_num;
	__le16 queue_num;
पूर्ण;

काष्ठा hclge_pri_shaper_para अणु
	u8 ir_b;
	u8 ir_u;
	u8 ir_s;
	u8 bs_b;
	u8 bs_s;
	u8 flag;
	u32 rate;
पूर्ण;

#घोषणा hclge_पंचांग_set_field(dest, string, val) \
			   hnae3_set_field((dest), \
			   (HCLGE_TM_SHAP_##string##_MSK), \
			   (HCLGE_TM_SHAP_##string##_LSH), val)
#घोषणा hclge_पंचांग_get_field(src, string) \
			hnae3_get_field((src), HCLGE_TM_SHAP_##string##_MSK, \
					HCLGE_TM_SHAP_##string##_LSH)

पूर्णांक hclge_पंचांग_schd_init(काष्ठा hclge_dev *hdev);
पूर्णांक hclge_पंचांग_vport_map_update(काष्ठा hclge_dev *hdev);
पूर्णांक hclge_छोड़ो_setup_hw(काष्ठा hclge_dev *hdev, bool init);
पूर्णांक hclge_पंचांग_schd_setup_hw(काष्ठा hclge_dev *hdev);
व्योम hclge_पंचांग_prio_tc_info_update(काष्ठा hclge_dev *hdev, u8 *prio_tc);
व्योम hclge_पंचांग_schd_info_update(काष्ठा hclge_dev *hdev, u8 num_tc);
व्योम hclge_पंचांग_pfc_info_update(काष्ठा hclge_dev *hdev);
पूर्णांक hclge_पंचांग_dwrr_cfg(काष्ठा hclge_dev *hdev);
पूर्णांक hclge_पंचांग_init_hw(काष्ठा hclge_dev *hdev, bool init);
पूर्णांक hclge_mac_छोड़ो_en_cfg(काष्ठा hclge_dev *hdev, bool tx, bool rx);
पूर्णांक hclge_छोड़ो_addr_cfg(काष्ठा hclge_dev *hdev, स्थिर u8 *mac_addr);
पूर्णांक hclge_pfc_rx_stats_get(काष्ठा hclge_dev *hdev, u64 *stats);
पूर्णांक hclge_pfc_tx_stats_get(काष्ठा hclge_dev *hdev, u64 *stats);
पूर्णांक hclge_पंचांग_qs_shaper_cfg(काष्ठा hclge_vport *vport, पूर्णांक max_tx_rate);
पूर्णांक hclge_पंचांग_get_qset_num(काष्ठा hclge_dev *hdev, u16 *qset_num);
पूर्णांक hclge_पंचांग_get_pri_num(काष्ठा hclge_dev *hdev, u8 *pri_num);
पूर्णांक hclge_पंचांग_get_qset_map_pri(काष्ठा hclge_dev *hdev, u16 qset_id, u8 *priority,
			      u8 *link_vld);
पूर्णांक hclge_पंचांग_get_qset_sch_mode(काष्ठा hclge_dev *hdev, u16 qset_id, u8 *mode);
पूर्णांक hclge_पंचांग_get_qset_weight(काष्ठा hclge_dev *hdev, u16 qset_id, u8 *weight);
पूर्णांक hclge_पंचांग_get_pri_sch_mode(काष्ठा hclge_dev *hdev, u8 pri_id, u8 *mode);
पूर्णांक hclge_पंचांग_get_pri_weight(काष्ठा hclge_dev *hdev, u8 pri_id, u8 *weight);
पूर्णांक hclge_पंचांग_get_pri_shaper(काष्ठा hclge_dev *hdev, u8 pri_id,
			    क्रमागत hclge_opcode_type cmd,
			    काष्ठा hclge_pri_shaper_para *para);
#पूर्ण_अगर
