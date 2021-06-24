<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_FW_H_
#घोषणा __RTW_FW_H_

#घोषणा H2C_PKT_SIZE		32
#घोषणा H2C_PKT_HDR_SIZE	8

/* FW bin inक्रमmation */
#घोषणा FW_HDR_SIZE			64
#घोषणा FW_HDR_CHKSUM_SIZE		8

#घोषणा FW_NLO_INFO_CHECK_SIZE		4

#घोषणा FIFO_PAGE_SIZE_SHIFT		12
#घोषणा FIFO_PAGE_SIZE			4096
#घोषणा FIFO_DUMP_ADDR			0x8000

#घोषणा DLFW_PAGE_SIZE_SHIFT_LEGACY	12
#घोषणा DLFW_PAGE_SIZE_LEGACY		0x1000
#घोषणा DLFW_BLK_SIZE_SHIFT_LEGACY	2
#घोषणा DLFW_BLK_SIZE_LEGACY		4
#घोषणा FW_START_ADDR_LEGACY		0x1000

क्रमागत rtw_c2h_cmd_id अणु
	C2H_CCX_TX_RPT = 0x03,
	C2H_BT_INFO = 0x09,
	C2H_BT_MP_INFO = 0x0b,
	C2H_RA_RPT = 0x0c,
	C2H_HW_FEATURE_REPORT = 0x19,
	C2H_WLAN_INFO = 0x27,
	C2H_WLAN_RFON = 0x32,
	C2H_HW_FEATURE_DUMP = 0xfd,
	C2H_HALMAC = 0xff,
पूर्ण;

क्रमागत rtw_c2h_cmd_id_ext अणु
	C2H_CCX_RPT = 0x0f,
पूर्ण;

काष्ठा rtw_c2h_cmd अणु
	u8 id;
	u8 seq;
	u8 payload[];
पूर्ण __packed;

क्रमागत rtw_rsvd_packet_type अणु
	RSVD_BEACON,
	RSVD_DUMMY,
	RSVD_PS_POLL,
	RSVD_PROBE_RESP,
	RSVD_शून्य,
	RSVD_QOS_शून्य,
	RSVD_LPS_PG_DPK,
	RSVD_LPS_PG_INFO,
	RSVD_PROBE_REQ,
	RSVD_NLO_INFO,
	RSVD_CH_INFO,
पूर्ण;

क्रमागत rtw_fw_rf_type अणु
	FW_RF_1T2R = 0,
	FW_RF_2T4R = 1,
	FW_RF_2T2R = 2,
	FW_RF_2T3R = 3,
	FW_RF_1T1R = 4,
	FW_RF_2T2R_GREEN = 5,
	FW_RF_3T3R = 6,
	FW_RF_3T4R = 7,
	FW_RF_4T4R = 8,
	FW_RF_MAX_TYPE = 0xF,
पूर्ण;

क्रमागत rtw_fw_feature अणु
	FW_FEATURE_SIG = BIT(0),
	FW_FEATURE_LPS_C2H = BIT(1),
	FW_FEATURE_LCLK = BIT(2),
	FW_FEATURE_PG = BIT(3),
	FW_FEATURE_MAX = BIT(31),
पूर्ण;

काष्ठा rtw_coex_info_req अणु
	u8 seq;
	u8 op_code;
	u8 para1;
	u8 para2;
	u8 para3;
पूर्ण;

काष्ठा rtw_iqk_para अणु
	u8 clear;
	u8 segment_iqk;
पूर्ण;

काष्ठा rtw_lps_pg_dpk_hdr अणु
	u16 dpk_path_ok;
	u8 dpk_txagc[2];
	u16 dpk_gs[2];
	u32 coef[2][20];
	u8 dpk_ch;
पूर्ण __packed;

काष्ठा rtw_lps_pg_info_hdr अणु
	u8 macid;
	u8 mbssid;
	u8 pattern_count;
	u8 mu_tab_group_id;
	u8 sec_cam_count;
	u8 tx_bu_page_count;
	u16 rsvd;
	u8 sec_cam[MAX_PG_CAM_BACKUP_NUM];
पूर्ण __packed;

काष्ठा rtw_rsvd_page अणु
	/* associated with each vअगर */
	काष्ठा list_head vअगर_list;
	काष्ठा rtw_vअगर *rtwvअगर;

	/* associated when build rsvd page */
	काष्ठा list_head build_list;

	काष्ठा sk_buff *skb;
	क्रमागत rtw_rsvd_packet_type type;
	u8 page;
	bool add_txdesc;
	काष्ठा cfg80211_ssid *ssid;
पूर्ण;

क्रमागत rtw_keep_alive_pkt_type अणु
	KEEP_ALIVE_शून्य_PKT = 0,
	KEEP_ALIVE_ARP_RSP = 1,
पूर्ण;

काष्ठा rtw_nlo_info_hdr अणु
	u8 nlo_count;
	u8 hidden_ap_count;
	u8 rsvd1[2];
	u8 pattern_check[FW_NLO_INFO_CHECK_SIZE];
	u8 rsvd2[8];
	u8 ssid_len[16];
	u8 chiper[16];
	u8 rsvd3[16];
	u8 location[8];
पूर्ण __packed;

क्रमागत rtw_packet_type अणु
	RTW_PACKET_PROBE_REQ = 0x00,

	RTW_PACKET_UNDEFINE = 0x7FFFFFFF,
पूर्ण;

काष्ठा rtw_fw_wow_keep_alive_para अणु
	bool aकरोpt;
	u8 pkt_type;
	u8 period;		/* unit: sec */
पूर्ण;

काष्ठा rtw_fw_wow_disconnect_para अणु
	bool aकरोpt;
	u8 period;		/* unit: sec */
	u8 retry_count;
पूर्ण;

काष्ठा rtw_ch_चयन_option अणु
	u8 periodic_option;
	u32 tsf_high;
	u32 tsf_low;
	u8 dest_ch_en;
	u8 असलolute_समय_en;
	u8 dest_ch;
	u8 normal_period;
	u8 normal_period_sel;
	u8 normal_cycle;
	u8 slow_period;
	u8 slow_period_sel;
	u8 nlo_en;
पूर्ण;

काष्ठा rtw_fw_hdr अणु
	__le16 signature;
	u8 category;
	u8 function;
	__le16 version;		/* 0x04 */
	u8 subversion;
	u8 subindex;
	__le32 rsvd;		/* 0x08 */
	__le32 feature;		/* 0x0C */
	u8 month;		/* 0x10 */
	u8 day;
	u8 hour;
	u8 min;
	__le16 year;		/* 0x14 */
	__le16 rsvd3;
	u8 mem_usage;		/* 0x18 */
	u8 rsvd4[3];
	__le16 h2c_fmt_ver;	/* 0x1C */
	__le16 rsvd5;
	__le32 dmem_addr;	/* 0x20 */
	__le32 dmem_size;
	__le32 rsvd6;
	__le32 rsvd7;
	__le32 imem_size;	/* 0x30 */
	__le32 emem_size;
	__le32 emem_addr;
	__le32 imem_addr;
पूर्ण __packed;

काष्ठा rtw_fw_hdr_legacy अणु
	__le16 signature;
	u8 category;
	u8 function;
	__le16 version;	/* 0x04 */
	u8 subversion1;
	u8 subversion2;
	u8 month;	/* 0x08 */
	u8 day;
	u8 hour;
	u8 minute;
	__le16 size;
	__le16 rsvd2;
	__le32 idx;	/* 0x10 */
	__le32 rsvd3;
	__le32 rsvd4;	/* 0x18 */
	__le32 rsvd5;
पूर्ण __packed;

/* C2H */
#घोषणा GET_CCX_REPORT_SEQNUM_V0(c2h_payload)	(c2h_payload[6] & 0xfc)
#घोषणा GET_CCX_REPORT_STATUS_V0(c2h_payload)	(c2h_payload[0] & 0xc0)
#घोषणा GET_CCX_REPORT_SEQNUM_V1(c2h_payload)	(c2h_payload[8] & 0xfc)
#घोषणा GET_CCX_REPORT_STATUS_V1(c2h_payload)	(c2h_payload[9] & 0xc0)

#घोषणा GET_RA_REPORT_RATE(c2h_payload)		(c2h_payload[0] & 0x7f)
#घोषणा GET_RA_REPORT_SGI(c2h_payload)		((c2h_payload[0] & 0x80) >> 7)
#घोषणा GET_RA_REPORT_BW(c2h_payload)		(c2h_payload[6])
#घोषणा GET_RA_REPORT_MACID(c2h_payload)	(c2h_payload[1])

/* PKT H2C */
#घोषणा H2C_PKT_CMD_ID 0xFF
#घोषणा H2C_PKT_CATEGORY 0x01

#घोषणा H2C_PKT_GENERAL_INFO 0x0D
#घोषणा H2C_PKT_PHYDM_INFO 0x11
#घोषणा H2C_PKT_IQK 0x0E

#घोषणा H2C_PKT_CH_SWITCH 0x02
#घोषणा H2C_PKT_UPDATE_PKT 0x0C

#घोषणा H2C_PKT_CH_SWITCH_LEN 0x20
#घोषणा H2C_PKT_UPDATE_PKT_LEN 0x4

#घोषणा SET_PKT_H2C_CATEGORY(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(6, 0))
#घोषणा SET_PKT_H2C_CMD_ID(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#घोषणा SET_PKT_H2C_SUB_CMD_ID(h2c_pkt, value)                                 \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 16))
#घोषणा SET_PKT_H2C_TOTAL_LEN(h2c_pkt, value)                                  \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(15, 0))

अटल अंतरभूत व्योम rtw_h2c_pkt_set_header(u8 *h2c_pkt, u8 sub_id)
अणु
	SET_PKT_H2C_CATEGORY(h2c_pkt, H2C_PKT_CATEGORY);
	SET_PKT_H2C_CMD_ID(h2c_pkt, H2C_PKT_CMD_ID);
	SET_PKT_H2C_SUB_CMD_ID(h2c_pkt, sub_id);
पूर्ण

#घोषणा FW_OFFLOAD_H2C_SET_SEQ_NUM(h2c_pkt, value)                             \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(31, 16))
#घोषणा GENERAL_INFO_SET_FW_TX_BOUNDARY(h2c_pkt, value)                        \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(23, 16))

#घोषणा PHYDM_INFO_SET_REF_TYPE(h2c_pkt, value)                                \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(7, 0))
#घोषणा PHYDM_INFO_SET_RF_TYPE(h2c_pkt, value)                                 \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(15, 8))
#घोषणा PHYDM_INFO_SET_CUT_VER(h2c_pkt, value)                                 \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(23, 16))
#घोषणा PHYDM_INFO_SET_RX_ANT_STATUS(h2c_pkt, value)                           \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(27, 24))
#घोषणा PHYDM_INFO_SET_TX_ANT_STATUS(h2c_pkt, value)                           \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(31, 28))
#घोषणा IQK_SET_CLEAR(h2c_pkt, value)                                          \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, BIT(0))
#घोषणा IQK_SET_SEGMENT_IQK(h2c_pkt, value)                                    \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, BIT(1))

#घोषणा CHSW_INFO_SET_CH(pkt, value)					       \
	le32p_replace_bits((__le32 *)(pkt) + 0x00, value, GENMASK(7, 0))
#घोषणा CHSW_INFO_SET_PRI_CH_IDX(pkt, value)				       \
	le32p_replace_bits((__le32 *)(pkt) + 0x00, value, GENMASK(11, 8))
#घोषणा CHSW_INFO_SET_BW(pkt, value)					       \
	le32p_replace_bits((__le32 *)(pkt) + 0x00, value, GENMASK(15, 12))
#घोषणा CHSW_INFO_SET_TIMEOUT(pkt, value)				       \
	le32p_replace_bits((__le32 *)(pkt) + 0x00, value, GENMASK(23, 16))
#घोषणा CHSW_INFO_SET_ACTION_ID(pkt, value)				       \
	le32p_replace_bits((__le32 *)(pkt) + 0x00, value, GENMASK(30, 24))

#घोषणा UPDATE_PKT_SET_SIZE(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(15, 0))
#घोषणा UPDATE_PKT_SET_PKT_ID(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(23, 16))
#घोषणा UPDATE_PKT_SET_LOCATION(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(31, 24))

#घोषणा CH_SWITCH_SET_START(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, BIT(0))
#घोषणा CH_SWITCH_SET_DEST_CH_EN(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, BIT(1))
#घोषणा CH_SWITCH_SET_ABSOLUTE_TIME(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, BIT(2))
#घोषणा CH_SWITCH_SET_PERIODIC_OPT(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(4, 3))
#घोषणा CH_SWITCH_SET_INFO_LOC(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(15, 8))
#घोषणा CH_SWITCH_SET_CH_NUM(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(23, 16))
#घोषणा CH_SWITCH_SET_PRI_CH_IDX(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x02, value, GENMASK(27, 24))
#घोषणा CH_SWITCH_SET_DEST_CH(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x03, value, GENMASK(7, 0))
#घोषणा CH_SWITCH_SET_NORMAL_PERIOD(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x03, value, GENMASK(13, 8))
#घोषणा CH_SWITCH_SET_NORMAL_PERIOD_SEL(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x03, value, GENMASK(15, 14))
#घोषणा CH_SWITCH_SET_SLOW_PERIOD(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x03, value, GENMASK(21, 16))
#घोषणा CH_SWITCH_SET_SLOW_PERIOD_SEL(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x03, value, GENMASK(23, 22))
#घोषणा CH_SWITCH_SET_NORMAL_CYCLE(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x03, value, GENMASK(31, 24))
#घोषणा CH_SWITCH_SET_TSF_HIGH(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x04, value, GENMASK(31, 0))
#घोषणा CH_SWITCH_SET_TSF_LOW(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x05, value, GENMASK(31, 0))
#घोषणा CH_SWITCH_SET_INFO_SIZE(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x06, value, GENMASK(15, 0))

/* Command H2C */
#घोषणा H2C_CMD_RSVD_PAGE		0x0
#घोषणा H2C_CMD_MEDIA_STATUS_RPT	0x01
#घोषणा H2C_CMD_SET_PWR_MODE		0x20
#घोषणा H2C_CMD_LPS_PG_INFO		0x2b
#घोषणा H2C_CMD_RA_INFO			0x40
#घोषणा H2C_CMD_RSSI_MONITOR		0x42
#घोषणा H2C_CMD_WL_PHY_INFO		0x58

#घोषणा H2C_CMD_COEX_TDMA_TYPE		0x60
#घोषणा H2C_CMD_QUERY_BT_INFO		0x61
#घोषणा H2C_CMD_FORCE_BT_TX_POWER	0x62
#घोषणा H2C_CMD_IGNORE_WLAN_ACTION	0x63
#घोषणा H2C_CMD_WL_CH_INFO		0x66
#घोषणा H2C_CMD_QUERY_BT_MP_INFO	0x67
#घोषणा H2C_CMD_BT_WIFI_CONTROL		0x69
#घोषणा H2C_CMD_WIFI_CALIBRATION	0x6d

#घोषणा H2C_CMD_KEEP_ALIVE		0x03
#घोषणा H2C_CMD_DISCONNECT_DECISION	0x04
#घोषणा H2C_CMD_WOWLAN			0x80
#घोषणा H2C_CMD_REMOTE_WAKE_CTRL	0x81
#घोषणा H2C_CMD_AOAC_GLOBAL_INFO	0x82
#घोषणा H2C_CMD_NLO_INFO		0x8C

#घोषणा SET_H2C_CMD_ID_CLASS(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(7, 0))

#घोषणा MEDIA_STATUS_RPT_SET_OP_MODE(h2c_pkt, value)                           \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
#घोषणा MEDIA_STATUS_RPT_SET_MACID(h2c_pkt, value)                             \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))

#घोषणा SET_WL_PHY_INFO_TX_TP(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(17, 8))
#घोषणा SET_WL_PHY_INFO_RX_TP(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(27, 18))
#घोषणा SET_WL_PHY_INFO_TX_RATE_DESC(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(7, 0))
#घोषणा SET_WL_PHY_INFO_RX_RATE_DESC(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(15, 8))
#घोषणा SET_WL_PHY_INFO_RX_EVM(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(23, 16))

#घोषणा SET_PWR_MODE_SET_MODE(h2c_pkt, value)                                  \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(14, 8))
#घोषणा SET_PWR_MODE_SET_RLBM(h2c_pkt, value)                                  \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(19, 16))
#घोषणा SET_PWR_MODE_SET_SMART_PS(h2c_pkt, value)                              \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 20))
#घोषणा SET_PWR_MODE_SET_AWAKE_INTERVAL(h2c_pkt, value)                        \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 24))
#घोषणा SET_PWR_MODE_SET_PORT_ID(h2c_pkt, value)                               \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(7, 5))
#घोषणा SET_PWR_MODE_SET_PWR_STATE(h2c_pkt, value)                             \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(15, 8))
#घोषणा LPS_PG_INFO_LOC(h2c_pkt, value)                                        \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))
#घोषणा LPS_PG_DPK_LOC(h2c_pkt, value)                                         \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 24))
#घोषणा LPS_PG_SEC_CAM_EN(h2c_pkt, value)                                      \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
#घोषणा LPS_PG_PATTERN_CAM_EN(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(10))
#घोषणा SET_RSSI_INFO_MACID(h2c_pkt, value)                                    \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#घोषणा SET_RSSI_INFO_RSSI(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 24))
#घोषणा SET_RSSI_INFO_STBC(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, BIT(1))
#घोषणा SET_RA_INFO_MACID(h2c_pkt, value)                                      \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#घोषणा SET_RA_INFO_RATE_ID(h2c_pkt, value)                                    \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(20, 16))
#घोषणा SET_RA_INFO_INIT_RA_LVL(h2c_pkt, value)                                \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(22, 21))
#घोषणा SET_RA_INFO_SGI_EN(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(23))
#घोषणा SET_RA_INFO_BW_MODE(h2c_pkt, value)                                    \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(25, 24))
#घोषणा SET_RA_INFO_LDPC(h2c_pkt, value)                                       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(26))
#घोषणा SET_RA_INFO_NO_UPDATE(h2c_pkt, value)                                  \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(27))
#घोषणा SET_RA_INFO_VHT_EN(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(29, 28))
#घोषणा SET_RA_INFO_DIS_PT(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(30))
#घोषणा SET_RA_INFO_RA_MASK0(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(7, 0))
#घोषणा SET_RA_INFO_RA_MASK1(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(15, 8))
#घोषणा SET_RA_INFO_RA_MASK2(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(23, 16))
#घोषणा SET_RA_INFO_RA_MASK3(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(31, 24))
#घोषणा SET_QUERY_BT_INFO(h2c_pkt, value)                                      \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
#घोषणा SET_WL_CH_INFO_LINK(h2c_pkt, value)                                    \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#घोषणा SET_WL_CH_INFO_CHNL(h2c_pkt, value)                                    \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))
#घोषणा SET_WL_CH_INFO_BW(h2c_pkt, value)                                      \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 24))
#घोषणा SET_BT_MP_INFO_SEQ(h2c_pkt, value)                                     \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 12))
#घोषणा SET_BT_MP_INFO_OP_CODE(h2c_pkt, value)                                 \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))
#घोषणा SET_BT_MP_INFO_PARA1(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 24))
#घोषणा SET_BT_MP_INFO_PARA2(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(7, 0))
#घोषणा SET_BT_MP_INFO_PARA3(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(15, 8))
#घोषणा SET_BT_TX_POWER_INDEX(h2c_pkt, value)                                  \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#घोषणा SET_IGNORE_WLAN_ACTION_EN(h2c_pkt, value)                              \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
#घोषणा SET_COEX_TDMA_TYPE_PARA1(h2c_pkt, value)                               \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#घोषणा SET_COEX_TDMA_TYPE_PARA2(h2c_pkt, value)                               \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))
#घोषणा SET_COEX_TDMA_TYPE_PARA3(h2c_pkt, value)                               \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 24))
#घोषणा SET_COEX_TDMA_TYPE_PARA4(h2c_pkt, value)                               \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(7, 0))
#घोषणा SET_COEX_TDMA_TYPE_PARA5(h2c_pkt, value)                               \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(15, 8))
#घोषणा SET_BT_WIFI_CONTROL_OP_CODE(h2c_pkt, value)                            \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#घोषणा SET_BT_WIFI_CONTROL_DATA1(h2c_pkt, value)                              \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))
#घोषणा SET_BT_WIFI_CONTROL_DATA2(h2c_pkt, value)                              \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 24))
#घोषणा SET_BT_WIFI_CONTROL_DATA3(h2c_pkt, value)                              \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(7, 0))
#घोषणा SET_BT_WIFI_CONTROL_DATA4(h2c_pkt, value)                              \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(15, 8))
#घोषणा SET_BT_WIFI_CONTROL_DATA5(h2c_pkt, value)                              \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x01, value, GENMASK(23, 16))

#घोषणा SET_KEEP_ALIVE_ENABLE(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
#घोषणा SET_KEEP_ALIVE_ADOPT(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(9))
#घोषणा SET_KEEP_ALIVE_PKT_TYPE(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(10))
#घोषणा SET_KEEP_ALIVE_CHECK_PERIOD(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))

#घोषणा SET_DISCONNECT_DECISION_ENABLE(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
#घोषणा SET_DISCONNECT_DECISION_ADOPT(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(9))
#घोषणा SET_DISCONNECT_DECISION_CHECK_PERIOD(h2c_pkt, value)		       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))
#घोषणा SET_DISCONNECT_DECISION_TRY_PKT_NUM(h2c_pkt, value)		       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(31, 24))

#घोषणा SET_WOWLAN_FUNC_ENABLE(h2c_pkt, value)				       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
#घोषणा SET_WOWLAN_PATTERN_MATCH_ENABLE(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(9))
#घोषणा SET_WOWLAN_MAGIC_PKT_ENABLE(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(10))
#घोषणा SET_WOWLAN_UNICAST_PKT_ENABLE(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(11))
#घोषणा SET_WOWLAN_REKEY_WAKEUP_ENABLE(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(14))
#घोषणा SET_WOWLAN_DEAUTH_WAKEUP_ENABLE(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(15))

#घोषणा SET_REMOTE_WAKECTRL_ENABLE(h2c_pkt, value)			       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
#घोषणा SET_REMOTE_WAKE_CTRL_NLO_OFFLOAD_EN(h2c_pkt, value)		       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(12))

#घोषणा SET_AOAC_GLOBAL_INFO_PAIRWISE_ENC_ALG(h2c_pkt, value)		       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(15, 8))
#घोषणा SET_AOAC_GLOBAL_INFO_GROUP_ENC_ALG(h2c_pkt, value)		       \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))

#घोषणा SET_NLO_FUN_EN(h2c_pkt, value)                                         \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
#घोषणा SET_NLO_PS_32K(h2c_pkt, value)                                         \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(9))
#घोषणा SET_NLO_IGNORE_SECURITY(h2c_pkt, value)                                \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(10))
#घोषणा SET_NLO_LOC_NLO_INFO(h2c_pkt, value)                                   \
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, GENMASK(23, 16))

#घोषणा GET_FW_DUMP_LEN(_header)					\
	le32_get_bits(*((__le32 *)(_header) + 0x00), GENMASK(15, 0))
#घोषणा GET_FW_DUMP_SEQ(_header)					\
	le32_get_bits(*((__le32 *)(_header) + 0x00), GENMASK(22, 16))
#घोषणा GET_FW_DUMP_MORE(_header)					\
	le32_get_bits(*((__le32 *)(_header) + 0x00), BIT(23))
#घोषणा GET_FW_DUMP_VERSION(_header)					\
	le32_get_bits(*((__le32 *)(_header) + 0x00), GENMASK(31, 24))
#घोषणा GET_FW_DUMP_TLV_TYPE(_header)					\
	le32_get_bits(*((__le32 *)(_header) + 0x01), GENMASK(15, 0))
#घोषणा GET_FW_DUMP_TLV_LEN(_header)					\
	le32_get_bits(*((__le32 *)(_header) + 0x01), GENMASK(31, 16))
#घोषणा GET_FW_DUMP_TLV_VAL(_header)					\
	le32_get_bits(*((__le32 *)(_header) + 0x02), GENMASK(31, 0))

#घोषणा RFK_SET_INFORM_START(h2c_pkt, value)				\
	le32p_replace_bits((__le32 *)(h2c_pkt) + 0x00, value, BIT(8))
अटल अंतरभूत काष्ठा rtw_c2h_cmd *get_c2h_from_skb(काष्ठा sk_buff *skb)
अणु
	u32 pkt_offset;

	pkt_offset = *((u32 *)skb->cb);
	वापस (काष्ठा rtw_c2h_cmd *)(skb->data + pkt_offset);
पूर्ण

व्योम rtw_fw_c2h_cmd_rx_irqsafe(काष्ठा rtw_dev *rtwdev, u32 pkt_offset,
			       काष्ठा sk_buff *skb);
व्योम rtw_fw_c2h_cmd_handle(काष्ठा rtw_dev *rtwdev, काष्ठा sk_buff *skb);
व्योम rtw_fw_send_general_info(काष्ठा rtw_dev *rtwdev);
व्योम rtw_fw_send_phydm_info(काष्ठा rtw_dev *rtwdev);

व्योम rtw_fw_करो_iqk(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_iqk_para *para);
व्योम rtw_fw_inक्रमm_rfk_status(काष्ठा rtw_dev *rtwdev, bool start);
व्योम rtw_fw_set_pwr_mode(काष्ठा rtw_dev *rtwdev);
व्योम rtw_fw_set_pg_info(काष्ठा rtw_dev *rtwdev);
व्योम rtw_fw_query_bt_info(काष्ठा rtw_dev *rtwdev);
व्योम rtw_fw_wl_ch_info(काष्ठा rtw_dev *rtwdev, u8 link, u8 ch, u8 bw);
व्योम rtw_fw_query_bt_mp_info(काष्ठा rtw_dev *rtwdev,
			     काष्ठा rtw_coex_info_req *req);
व्योम rtw_fw_क्रमce_bt_tx_घातer(काष्ठा rtw_dev *rtwdev, u8 bt_pwr_dec_lvl);
व्योम rtw_fw_bt_ignore_wlan_action(काष्ठा rtw_dev *rtwdev, bool enable);
व्योम rtw_fw_coex_tdma_type(काष्ठा rtw_dev *rtwdev,
			   u8 para1, u8 para2, u8 para3, u8 para4, u8 para5);
व्योम rtw_fw_bt_wअगरi_control(काष्ठा rtw_dev *rtwdev, u8 op_code, u8 *data);
व्योम rtw_fw_send_rssi_info(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_sta_info *si);
व्योम rtw_fw_send_ra_info(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_sta_info *si);
व्योम rtw_fw_media_status_report(काष्ठा rtw_dev *rtwdev, u8 mac_id, bool conn);
व्योम rtw_fw_update_wl_phy_info(काष्ठा rtw_dev *rtwdev);
पूर्णांक rtw_fw_ग_लिखो_data_rsvd_page(काष्ठा rtw_dev *rtwdev, u16 pg_addr,
				u8 *buf, u32 size);
व्योम rtw_हटाओ_rsvd_page(काष्ठा rtw_dev *rtwdev,
			  काष्ठा rtw_vअगर *rtwvअगर);
व्योम rtw_add_rsvd_page_bcn(काष्ठा rtw_dev *rtwdev,
			   काष्ठा rtw_vअगर *rtwvअगर);
व्योम rtw_add_rsvd_page_pno(काष्ठा rtw_dev *rtwdev,
			   काष्ठा rtw_vअगर *rtwvअगर);
व्योम rtw_add_rsvd_page_sta(काष्ठा rtw_dev *rtwdev,
			   काष्ठा rtw_vअगर *rtwvअगर);
पूर्णांक rtw_fw_करोwnload_rsvd_page(काष्ठा rtw_dev *rtwdev);
व्योम rtw_send_rsvd_page_h2c(काष्ठा rtw_dev *rtwdev);
पूर्णांक rtw_dump_drv_rsvd_page(काष्ठा rtw_dev *rtwdev,
			   u32 offset, u32 size, u32 *buf);
व्योम rtw_fw_set_remote_wake_ctrl_cmd(काष्ठा rtw_dev *rtwdev, bool enable);
व्योम rtw_fw_set_wowlan_ctrl_cmd(काष्ठा rtw_dev *rtwdev, bool enable);
व्योम rtw_fw_set_keep_alive_cmd(काष्ठा rtw_dev *rtwdev, bool enable);
व्योम rtw_fw_set_disconnect_decision_cmd(काष्ठा rtw_dev *rtwdev, bool enable);
व्योम rtw_fw_set_aoac_global_info_cmd(काष्ठा rtw_dev *rtwdev,
				     u8 pairwise_key_enc,
				     u8 group_key_enc);

व्योम rtw_fw_set_nlo_info(काष्ठा rtw_dev *rtwdev, bool enable);
व्योम rtw_fw_update_pkt_probe_req(काष्ठा rtw_dev *rtwdev,
				 काष्ठा cfg80211_ssid *ssid);
व्योम rtw_fw_channel_चयन(काष्ठा rtw_dev *rtwdev, bool enable);
व्योम rtw_fw_h2c_cmd_dbg(काष्ठा rtw_dev *rtwdev, u8 *h2c);
व्योम rtw_fw_c2h_cmd_isr(काष्ठा rtw_dev *rtwdev);
पूर्णांक rtw_fw_dump_fअगरo(काष्ठा rtw_dev *rtwdev, u8 fअगरo_sel, u32 addr, u32 size,
		     u32 *buffer);

#पूर्ण_अगर
