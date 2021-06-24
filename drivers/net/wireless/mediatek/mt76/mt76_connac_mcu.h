<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/* Copyright (C) 2020 MediaTek Inc. */

#अगर_अघोषित __MT76_CONNAC_MCU_H
#घोषणा __MT76_CONNAC_MCU_H

#समावेश "mt76_connac.h"

काष्ठा tlv अणु
	__le16 tag;
	__le16 len;
पूर्ण __packed;

/* sta_rec */

काष्ठा sta_ntlv_hdr अणु
	u8 rsv[2];
	__le16 tlv_num;
पूर्ण __packed;

काष्ठा sta_req_hdr अणु
	u8 bss_idx;
	u8 wlan_idx_lo;
	__le16 tlv_num;
	u8 is_tlv_append;
	u8 muar_idx;
	u8 wlan_idx_hi;
	u8 rsv;
पूर्ण __packed;

काष्ठा sta_rec_basic अणु
	__le16 tag;
	__le16 len;
	__le32 conn_type;
	u8 conn_state;
	u8 qos;
	__le16 aid;
	u8 peer_addr[ETH_ALEN];
#घोषणा EXTRA_INFO_VER	BIT(0)
#घोषणा EXTRA_INFO_NEW	BIT(1)
	__le16 extra_info;
पूर्ण __packed;

काष्ठा sta_rec_ht अणु
	__le16 tag;
	__le16 len;
	__le16 ht_cap;
	u16 rsv;
पूर्ण __packed;

काष्ठा sta_rec_vht अणु
	__le16 tag;
	__le16 len;
	__le32 vht_cap;
	__le16 vht_rx_mcs_map;
	__le16 vht_tx_mcs_map;
	/* mt7921 */
	u8 rts_bw_sig;
	u8 rsv[3];
पूर्ण __packed;

काष्ठा sta_rec_uapsd अणु
	__le16 tag;
	__le16 len;
	u8 dac_map;
	u8 tac_map;
	u8 max_sp;
	u8 rsv0;
	__le16 listen_पूर्णांकerval;
	u8 rsv1[2];
पूर्ण __packed;

काष्ठा sta_rec_ba अणु
	__le16 tag;
	__le16 len;
	u8 tid;
	u8 ba_type;
	u8 amsdu;
	u8 ba_en;
	__le16 ssn;
	__le16 winsize;
पूर्ण __packed;

काष्ठा sta_rec_he अणु
	__le16 tag;
	__le16 len;

	__le32 he_cap;

	u8 t_frame_dur;
	u8 max_ampdu_exp;
	u8 bw_set;
	u8 device_class;
	u8 dcm_tx_mode;
	u8 dcm_tx_max_nss;
	u8 dcm_rx_mode;
	u8 dcm_rx_max_nss;
	u8 dcm_max_ru;
	u8 punc_pream_rx;
	u8 pkt_ext;
	u8 rsv1;

	__le16 max_nss_mcs[CMD_HE_MCS_BW_NUM];

	u8 rsv2[2];
पूर्ण __packed;

काष्ठा sta_rec_amsdu अणु
	__le16 tag;
	__le16 len;
	u8 max_amsdu_num;
	u8 max_mpdu_size;
	u8 amsdu_en;
	u8 rsv;
पूर्ण __packed;

काष्ठा sta_rec_state अणु
	__le16 tag;
	__le16 len;
	__le32 flags;
	u8 state;
	u8 vht_opmode;
	u8 action;
	u8 rsv[1];
पूर्ण __packed;

#घोषणा HT_MCS_MASK_NUM 10
काष्ठा sta_rec_ra_info अणु
	__le16 tag;
	__le16 len;
	__le16 legacy;
	u8 rx_mcs_biपंचांगask[HT_MCS_MASK_NUM];
पूर्ण __packed;

काष्ठा sta_rec_phy अणु
	__le16 tag;
	__le16 len;
	__le16 basic_rate;
	u8 phy_type;
	u8 ampdu;
	u8 rts_policy;
	u8 rcpi;
	u8 rsv[2];
पूर्ण __packed;

/* wtbl_rec */

काष्ठा wtbl_req_hdr अणु
	u8 wlan_idx_lo;
	u8 operation;
	__le16 tlv_num;
	u8 wlan_idx_hi;
	u8 rsv[3];
पूर्ण __packed;

काष्ठा wtbl_generic अणु
	__le16 tag;
	__le16 len;
	u8 peer_addr[ETH_ALEN];
	u8 muar_idx;
	u8 skip_tx;
	u8 cf_ack;
	u8 qos;
	u8 mesh;
	u8 adm;
	__le16 partial_aid;
	u8 baf_en;
	u8 aad_om;
पूर्ण __packed;

काष्ठा wtbl_rx अणु
	__le16 tag;
	__le16 len;
	u8 rcid;
	u8 rca1;
	u8 rca2;
	u8 rv;
	u8 rsv[4];
पूर्ण __packed;

काष्ठा wtbl_ht अणु
	__le16 tag;
	__le16 len;
	u8 ht;
	u8 ldpc;
	u8 af;
	u8 mm;
	u8 rsv[4];
पूर्ण __packed;

काष्ठा wtbl_vht अणु
	__le16 tag;
	__le16 len;
	u8 ldpc;
	u8 dyn_bw;
	u8 vht;
	u8 txop_ps;
	u8 rsv[4];
पूर्ण __packed;

काष्ठा wtbl_tx_ps अणु
	__le16 tag;
	__le16 len;
	u8 txps;
	u8 rsv[3];
पूर्ण __packed;

काष्ठा wtbl_hdr_trans अणु
	__le16 tag;
	__le16 len;
	u8 to_ds;
	u8 from_ds;
	u8 no_rx_trans;
	u8 rsv;
पूर्ण __packed;

काष्ठा wtbl_ba अणु
	__le16 tag;
	__le16 len;
	/* common */
	u8 tid;
	u8 ba_type;
	u8 rsv0[2];
	/* originator only */
	__le16 sn;
	u8 ba_en;
	u8 ba_winsize_idx;
	__le16 ba_winsize;
	/* recipient only */
	u8 peer_addr[ETH_ALEN];
	u8 rst_ba_tid;
	u8 rst_ba_sel;
	u8 rst_ba_sb;
	u8 band_idx;
	u8 rsv1[4];
पूर्ण __packed;

काष्ठा wtbl_smps अणु
	__le16 tag;
	__le16 len;
	u8 smps;
	u8 rsv[3];
पूर्ण __packed;

/* mt7615 only */

काष्ठा wtbl_bf अणु
	__le16 tag;
	__le16 len;
	u8 ibf;
	u8 ebf;
	u8 ibf_vht;
	u8 ebf_vht;
	u8 gid;
	u8 pfmu_idx;
	u8 rsv[2];
पूर्ण __packed;

काष्ठा wtbl_pn अणु
	__le16 tag;
	__le16 len;
	u8 pn[6];
	u8 rsv[2];
पूर्ण __packed;

काष्ठा wtbl_spe अणु
	__le16 tag;
	__le16 len;
	u8 spe_idx;
	u8 rsv[3];
पूर्ण __packed;

काष्ठा wtbl_raw अणु
	__le16 tag;
	__le16 len;
	u8 wtbl_idx;
	u8 dw;
	u8 rsv[2];
	__le32 msk;
	__le32 val;
पूर्ण __packed;

#घोषणा MT76_CONNAC_WTBL_UPDATE_MAX_SIZE (माप(काष्ठा wtbl_req_hdr) +	\
					  माप(काष्ठा wtbl_generic) +	\
					  माप(काष्ठा wtbl_rx) +	\
					  माप(काष्ठा wtbl_ht) +	\
					  माप(काष्ठा wtbl_vht) +	\
					  माप(काष्ठा wtbl_tx_ps) +	\
					  माप(काष्ठा wtbl_hdr_trans) +\
					  माप(काष्ठा wtbl_ba) +	\
					  माप(काष्ठा wtbl_bf) +	\
					  माप(काष्ठा wtbl_smps) +	\
					  माप(काष्ठा wtbl_pn) +	\
					  माप(काष्ठा wtbl_spe))

#घोषणा MT76_CONNAC_STA_UPDATE_MAX_SIZE	(माप(काष्ठा sta_req_hdr) +	\
					 माप(काष्ठा sta_rec_basic) +	\
					 माप(काष्ठा sta_rec_ht) +	\
					 माप(काष्ठा sta_rec_he) +	\
					 माप(काष्ठा sta_rec_ba) +	\
					 माप(काष्ठा sta_rec_vht) +	\
					 माप(काष्ठा sta_rec_uapsd) + \
					 माप(काष्ठा sta_rec_amsdu) +	\
					 माप(काष्ठा tlv) +		\
					 MT76_CONNAC_WTBL_UPDATE_MAX_SIZE)

क्रमागत अणु
	STA_REC_BASIC,
	STA_REC_RA,
	STA_REC_RA_CMM_INFO,
	STA_REC_RA_UPDATE,
	STA_REC_BF,
	STA_REC_AMSDU,
	STA_REC_BA,
	STA_REC_STATE,
	STA_REC_TX_PROC,	/* क्रम hdr trans and CSO in CR4 */
	STA_REC_HT,
	STA_REC_VHT,
	STA_REC_APPS,
	STA_REC_KEY,
	STA_REC_WTBL,
	STA_REC_HE,
	STA_REC_HW_AMSDU,
	STA_REC_WTBL_AADOM,
	STA_REC_KEY_V2,
	STA_REC_MURU,
	STA_REC_MUEDCA,
	STA_REC_BFEE,
	STA_REC_PHY = 0x15,
	STA_REC_MAX_NUM
पूर्ण;

क्रमागत अणु
	WTBL_GENERIC,
	WTBL_RX,
	WTBL_HT,
	WTBL_VHT,
	WTBL_PEER_PS,		/* not used */
	WTBL_TX_PS,
	WTBL_HDR_TRANS,
	WTBL_SEC_KEY,
	WTBL_BA,
	WTBL_RDG,		/* obsoleted */
	WTBL_PROTECT,		/* not used */
	WTBL_CLEAR,		/* not used */
	WTBL_BF,
	WTBL_SMPS,
	WTBL_RAW_DATA,		/* debug only */
	WTBL_PN,
	WTBL_SPE,
	WTBL_MAX_NUM
पूर्ण;

#घोषणा STA_TYPE_STA			BIT(0)
#घोषणा STA_TYPE_AP			BIT(1)
#घोषणा STA_TYPE_ADHOC			BIT(2)
#घोषणा STA_TYPE_WDS			BIT(4)
#घोषणा STA_TYPE_BC			BIT(5)

#घोषणा NETWORK_INFRA			BIT(16)
#घोषणा NETWORK_P2P			BIT(17)
#घोषणा NETWORK_IBSS			BIT(18)
#घोषणा NETWORK_WDS			BIT(21)

#घोषणा SCAN_FUNC_RANDOM_MAC		BIT(0)
#घोषणा SCAN_FUNC_SPLIT_SCAN		BIT(5)

#घोषणा CONNECTION_INFRA_STA		(STA_TYPE_STA | NETWORK_INFRA)
#घोषणा CONNECTION_INFRA_AP		(STA_TYPE_AP | NETWORK_INFRA)
#घोषणा CONNECTION_P2P_GC		(STA_TYPE_STA | NETWORK_P2P)
#घोषणा CONNECTION_P2P_GO		(STA_TYPE_AP | NETWORK_P2P)
#घोषणा CONNECTION_IBSS_ADHOC		(STA_TYPE_ADHOC | NETWORK_IBSS)
#घोषणा CONNECTION_WDS			(STA_TYPE_WDS | NETWORK_WDS)
#घोषणा CONNECTION_INFRA_BC		(STA_TYPE_BC | NETWORK_INFRA)

#घोषणा CONN_STATE_DISCONNECT		0
#घोषणा CONN_STATE_CONNECT		1
#घोषणा CONN_STATE_PORT_SECURE		2

/* HE MAC */
#घोषणा STA_REC_HE_CAP_HTC			BIT(0)
#घोषणा STA_REC_HE_CAP_BQR			BIT(1)
#घोषणा STA_REC_HE_CAP_BSR			BIT(2)
#घोषणा STA_REC_HE_CAP_OM			BIT(3)
#घोषणा STA_REC_HE_CAP_AMSDU_IN_AMPDU		BIT(4)
/* HE PHY */
#घोषणा STA_REC_HE_CAP_DUAL_BAND		BIT(5)
#घोषणा STA_REC_HE_CAP_LDPC			BIT(6)
#घोषणा STA_REC_HE_CAP_TRIG_CQI_FK		BIT(7)
#घोषणा STA_REC_HE_CAP_PARTIAL_BW_EXT_RANGE	BIT(8)
/* STBC */
#घोषणा STA_REC_HE_CAP_LE_EQ_80M_TX_STBC	BIT(9)
#घोषणा STA_REC_HE_CAP_LE_EQ_80M_RX_STBC	BIT(10)
#घोषणा STA_REC_HE_CAP_GT_80M_TX_STBC		BIT(11)
#घोषणा STA_REC_HE_CAP_GT_80M_RX_STBC		BIT(12)
/* GI */
#घोषणा STA_REC_HE_CAP_SU_PPDU_1LTF_8US_GI	BIT(13)
#घोषणा STA_REC_HE_CAP_SU_MU_PPDU_4LTF_8US_GI	BIT(14)
#घोषणा STA_REC_HE_CAP_ER_SU_PPDU_1LTF_8US_GI	BIT(15)
#घोषणा STA_REC_HE_CAP_ER_SU_PPDU_4LTF_8US_GI	BIT(16)
#घोषणा STA_REC_HE_CAP_NDP_4LTF_3DOT2MS_GI	BIT(17)
/* 242 TONE */
#घोषणा STA_REC_HE_CAP_BW20_RU242_SUPPORT	BIT(18)
#घोषणा STA_REC_HE_CAP_TX_1024QAM_UNDER_RU242	BIT(19)
#घोषणा STA_REC_HE_CAP_RX_1024QAM_UNDER_RU242	BIT(20)

#घोषणा PHY_MODE_A				BIT(0)
#घोषणा PHY_MODE_B				BIT(1)
#घोषणा PHY_MODE_G				BIT(2)
#घोषणा PHY_MODE_GN				BIT(3)
#घोषणा PHY_MODE_AN				BIT(4)
#घोषणा PHY_MODE_AC				BIT(5)
#घोषणा PHY_MODE_AX_24G				BIT(6)
#घोषणा PHY_MODE_AX_5G				BIT(7)
#घोषणा PHY_MODE_AX_6G				BIT(8)

#घोषणा MODE_CCK				BIT(0)
#घोषणा MODE_OFDM				BIT(1)
#घोषणा MODE_HT					BIT(2)
#घोषणा MODE_VHT				BIT(3)
#घोषणा MODE_HE					BIT(4)

क्रमागत अणु
	PHY_TYPE_HR_DSSS_INDEX = 0,
	PHY_TYPE_ERP_INDEX,
	PHY_TYPE_ERP_P2P_INDEX,
	PHY_TYPE_OFDM_INDEX,
	PHY_TYPE_HT_INDEX,
	PHY_TYPE_VHT_INDEX,
	PHY_TYPE_HE_INDEX,
	PHY_TYPE_INDEX_NUM
पूर्ण;

#घोषणा PHY_TYPE_BIT_HR_DSSS			BIT(PHY_TYPE_HR_DSSS_INDEX)
#घोषणा PHY_TYPE_BIT_ERP			BIT(PHY_TYPE_ERP_INDEX)
#घोषणा PHY_TYPE_BIT_OFDM			BIT(PHY_TYPE_OFDM_INDEX)
#घोषणा PHY_TYPE_BIT_HT				BIT(PHY_TYPE_HT_INDEX)
#घोषणा PHY_TYPE_BIT_VHT			BIT(PHY_TYPE_VHT_INDEX)
#घोषणा PHY_TYPE_BIT_HE				BIT(PHY_TYPE_HE_INDEX)

#घोषणा MT_WTBL_RATE_TX_MODE			GENMASK(9, 6)
#घोषणा MT_WTBL_RATE_MCS			GENMASK(5, 0)
#घोषणा MT_WTBL_RATE_NSS			GENMASK(12, 10)
#घोषणा MT_WTBL_RATE_HE_GI			GENMASK(7, 4)
#घोषणा MT_WTBL_RATE_GI				GENMASK(3, 0)

#घोषणा MT_WTBL_W5_CHANGE_BW_RATE		GENMASK(7, 5)
#घोषणा MT_WTBL_W5_SHORT_GI_20			BIT(8)
#घोषणा MT_WTBL_W5_SHORT_GI_40			BIT(9)
#घोषणा MT_WTBL_W5_SHORT_GI_80			BIT(10)
#घोषणा MT_WTBL_W5_SHORT_GI_160			BIT(11)
#घोषणा MT_WTBL_W5_BW_CAP			GENMASK(13, 12)
#घोषणा MT_WTBL_W5_MPDU_FAIL_COUNT		GENMASK(25, 23)
#घोषणा MT_WTBL_W5_MPDU_OK_COUNT		GENMASK(28, 26)
#घोषणा MT_WTBL_W5_RATE_IDX			GENMASK(31, 29)

क्रमागत अणु
	WTBL_RESET_AND_SET = 1,
	WTBL_SET,
	WTBL_QUERY,
	WTBL_RESET_ALL
पूर्ण;

क्रमागत अणु
	MT_BA_TYPE_INVALID,
	MT_BA_TYPE_ORIGINATOR,
	MT_BA_TYPE_RECIPIENT
पूर्ण;

क्रमागत अणु
	RST_BA_MAC_TID_MATCH,
	RST_BA_MAC_MATCH,
	RST_BA_NO_MATCH
पूर्ण;

क्रमागत अणु
	DEV_INFO_ACTIVE,
	DEV_INFO_MAX_NUM
पूर्ण;

#घोषणा MCU_CMD_ACK				BIT(0)
#घोषणा MCU_CMD_UNI				BIT(1)
#घोषणा MCU_CMD_QUERY				BIT(2)

#घोषणा MCU_CMD_UNI_EXT_ACK			(MCU_CMD_ACK | MCU_CMD_UNI | \
						 MCU_CMD_QUERY)

#घोषणा MCU_FW_PREFIX				BIT(31)
#घोषणा MCU_UNI_PREFIX				BIT(30)
#घोषणा MCU_CE_PREFIX				BIT(29)
#घोषणा MCU_QUERY_PREFIX			BIT(28)
#घोषणा MCU_CMD_MASK				~(MCU_FW_PREFIX | MCU_UNI_PREFIX |	\
						  MCU_CE_PREFIX | MCU_QUERY_PREFIX)

#घोषणा MCU_QUERY_MASK				BIT(16)

क्रमागत अणु
	MCU_EXT_CMD_EFUSE_ACCESS = 0x01,
	MCU_EXT_CMD_RF_REG_ACCESS = 0x02,
	MCU_EXT_CMD_PM_STATE_CTRL = 0x07,
	MCU_EXT_CMD_CHANNEL_SWITCH = 0x08,
	MCU_EXT_CMD_SET_TX_POWER_CTRL = 0x11,
	MCU_EXT_CMD_FW_LOG_2_HOST = 0x13,
	MCU_EXT_CMD_EFUSE_BUFFER_MODE = 0x21,
	MCU_EXT_CMD_STA_REC_UPDATE = 0x25,
	MCU_EXT_CMD_BSS_INFO_UPDATE = 0x26,
	MCU_EXT_CMD_EDCA_UPDATE = 0x27,
	MCU_EXT_CMD_DEV_INFO_UPDATE = 0x2A,
	MCU_EXT_CMD_GET_TEMP = 0x2c,
	MCU_EXT_CMD_WTBL_UPDATE = 0x32,
	MCU_EXT_CMD_SET_RDD_CTRL = 0x3a,
	MCU_EXT_CMD_ATE_CTRL = 0x3d,
	MCU_EXT_CMD_PROTECT_CTRL = 0x3e,
	MCU_EXT_CMD_DBDC_CTRL = 0x45,
	MCU_EXT_CMD_MAC_INIT_CTRL = 0x46,
	MCU_EXT_CMD_RX_HDR_TRANS = 0x47,
	MCU_EXT_CMD_MUAR_UPDATE = 0x48,
	MCU_EXT_CMD_BCN_OFFLOAD = 0x49,
	MCU_EXT_CMD_SET_RX_PATH = 0x4e,
	MCU_EXT_CMD_TX_POWER_FEATURE_CTRL = 0x58,
	MCU_EXT_CMD_RXDCOC_CAL = 0x59,
	MCU_EXT_CMD_TXDPD_CAL = 0x60,
	MCU_EXT_CMD_SET_RDD_TH = 0x7c,
	MCU_EXT_CMD_SET_RDD_PATTERN = 0x7d,
पूर्ण;

क्रमागत अणु
	MCU_UNI_CMD_DEV_INFO_UPDATE = MCU_UNI_PREFIX | 0x01,
	MCU_UNI_CMD_BSS_INFO_UPDATE = MCU_UNI_PREFIX | 0x02,
	MCU_UNI_CMD_STA_REC_UPDATE = MCU_UNI_PREFIX | 0x03,
	MCU_UNI_CMD_SUSPEND = MCU_UNI_PREFIX | 0x05,
	MCU_UNI_CMD_OFFLOAD = MCU_UNI_PREFIX | 0x06,
	MCU_UNI_CMD_HIF_CTRL = MCU_UNI_PREFIX | 0x07,
पूर्ण;

क्रमागत अणु
	MCU_CMD_TARGET_ADDRESS_LEN_REQ = MCU_FW_PREFIX | 0x01,
	MCU_CMD_FW_START_REQ = MCU_FW_PREFIX | 0x02,
	MCU_CMD_INIT_ACCESS_REG = 0x3,
	MCU_CMD_NIC_POWER_CTRL = MCU_FW_PREFIX | 0x4,
	MCU_CMD_PATCH_START_REQ = MCU_FW_PREFIX | 0x05,
	MCU_CMD_PATCH_FINISH_REQ = MCU_FW_PREFIX | 0x07,
	MCU_CMD_PATCH_SEM_CONTROL = MCU_FW_PREFIX | 0x10,
	MCU_CMD_EXT_CID = 0xed,
	MCU_CMD_FW_SCATTER = MCU_FW_PREFIX | 0xee,
	MCU_CMD_RESTART_DL_REQ = MCU_FW_PREFIX | 0xef,
पूर्ण;

/* offload mcu commands */
क्रमागत अणु
	MCU_CMD_START_HW_SCAN = MCU_CE_PREFIX | 0x03,
	MCU_CMD_SET_PS_PROखाता = MCU_CE_PREFIX | 0x05,
	MCU_CMD_SET_CHAN_DOMAIN = MCU_CE_PREFIX | 0x0f,
	MCU_CMD_SET_BSS_CONNECTED = MCU_CE_PREFIX | 0x16,
	MCU_CMD_SET_BSS_ABORT = MCU_CE_PREFIX | 0x17,
	MCU_CMD_CANCEL_HW_SCAN = MCU_CE_PREFIX | 0x1b,
	MCU_CMD_SET_ROC = MCU_CE_PREFIX | 0x1d,
	MCU_CMD_SET_P2P_OPPPS = MCU_CE_PREFIX | 0x33,
	MCU_CMD_SET_RATE_TX_POWER = MCU_CE_PREFIX | 0x5d,
	MCU_CMD_SCHED_SCAN_ENABLE = MCU_CE_PREFIX | 0x61,
	MCU_CMD_SCHED_SCAN_REQ = MCU_CE_PREFIX | 0x62,
	MCU_CMD_REG_WRITE = MCU_CE_PREFIX | 0xc0,
	MCU_CMD_REG_READ = MCU_CE_PREFIX | MCU_QUERY_MASK | 0xc0,
	MCU_CMD_CHIP_CONFIG = MCU_CE_PREFIX | 0xca,
	MCU_CMD_FWLOG_2_HOST = MCU_CE_PREFIX | 0xc5,
	MCU_CMD_GET_WTBL = MCU_CE_PREFIX | 0xcd,
	MCU_CMD_GET_TXPWR = MCU_CE_PREFIX | 0xd0,
पूर्ण;

क्रमागत अणु
	PATCH_SEM_RELEASE,
	PATCH_SEM_GET
पूर्ण;

क्रमागत अणु
	UNI_BSS_INFO_BASIC = 0,
	UNI_BSS_INFO_RLM = 2,
	UNI_BSS_INFO_HE_BASIC = 5,
	UNI_BSS_INFO_BCN_CONTENT = 7,
	UNI_BSS_INFO_QBSS = 15,
	UNI_BSS_INFO_UAPSD = 19,
	UNI_BSS_INFO_PS = 21,
	UNI_BSS_INFO_BCNFT = 22,
पूर्ण;

क्रमागत अणु
	UNI_OFFLOAD_OFFLOAD_ARP,
	UNI_OFFLOAD_OFFLOAD_ND,
	UNI_OFFLOAD_OFFLOAD_GTK_REKEY,
	UNI_OFFLOAD_OFFLOAD_BMC_RPY_DETECT,
पूर्ण;

क्रमागत अणु
	UNI_SUSPEND_MODE_SETTING,
	UNI_SUSPEND_WOW_CTRL,
	UNI_SUSPEND_WOW_GPIO_PARAM,
	UNI_SUSPEND_WOW_WAKEUP_PORT,
	UNI_SUSPEND_WOW_PATTERN,
पूर्ण;

क्रमागत अणु
	WOW_USB = 1,
	WOW_PCIE = 2,
	WOW_GPIO = 3,
पूर्ण;

काष्ठा mt76_connac_bss_basic_tlv अणु
	__le16 tag;
	__le16 len;
	u8 active;
	u8 omac_idx;
	u8 hw_bss_idx;
	u8 band_idx;
	__le32 conn_type;
	u8 conn_state;
	u8 wmm_idx;
	u8 bssid[ETH_ALEN];
	__le16 bmc_tx_wlan_idx;
	__le16 bcn_पूर्णांकerval;
	u8 dtim_period;
	u8 phymode; /* bit(0): A
		     * bit(1): B
		     * bit(2): G
		     * bit(3): GN
		     * bit(4): AN
		     * bit(5): AC
		     */
	__le16 sta_idx;
	u8 nonht_basic_phy;
	u8 pad[3];
पूर्ण __packed;

काष्ठा mt76_connac_bss_qos_tlv अणु
	__le16 tag;
	__le16 len;
	u8 qos;
	u8 pad[3];
पूर्ण __packed;

काष्ठा mt76_connac_beacon_loss_event अणु
	u8 bss_idx;
	u8 reason;
	u8 pad[2];
पूर्ण __packed;

काष्ठा mt76_connac_mcu_bss_event अणु
	u8 bss_idx;
	u8 is_असलent;
	u8 मुक्त_quota;
	u8 pad;
पूर्ण __packed;

काष्ठा mt76_connac_mcu_scan_ssid अणु
	__le32 ssid_len;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
पूर्ण __packed;

काष्ठा mt76_connac_mcu_scan_channel अणु
	u8 band; /* 1: 2.4GHz
		  * 2: 5.0GHz
		  * Others: Reserved
		  */
	u8 channel_num;
पूर्ण __packed;

काष्ठा mt76_connac_mcu_scan_match अणु
	__le32 rssi_th;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 ssid_len;
	u8 rsv[3];
पूर्ण __packed;

काष्ठा mt76_connac_hw_scan_req अणु
	u8 seq_num;
	u8 bss_idx;
	u8 scan_type; /* 0: PASSIVE SCAN
		       * 1: ACTIVE SCAN
		       */
	u8 ssid_type; /* BIT(0) wildcard SSID
		       * BIT(1) P2P wildcard SSID
		       * BIT(2) specअगरied SSID + wildcard SSID
		       * BIT(2) + ssid_type_ext BIT(0) specअगरied SSID only
		       */
	u8 ssids_num;
	u8 probe_req_num; /* Number of probe request क्रम each SSID */
	u8 scan_func; /* BIT(0) Enable अक्रमom MAC scan
		       * BIT(1) Disable DBDC scan type 1~3.
		       * BIT(2) Use DBDC scan type 3 (dedicated one RF to scan).
		       */
	u8 version; /* 0: Not support fields after ies.
		     * 1: Support fields after ies.
		     */
	काष्ठा mt76_connac_mcu_scan_ssid ssids[4];
	__le16 probe_delay_समय;
	__le16 channel_dwell_समय; /* channel Dwell पूर्णांकerval */
	__le16 समयout_value;
	u8 channel_type; /* 0: Full channels
			  * 1: Only 2.4GHz channels
			  * 2: Only 5GHz channels
			  * 3: P2P social channel only (channel #1, #6 and #11)
			  * 4: Specअगरied channels
			  * Others: Reserved
			  */
	u8 channels_num; /* valid when channel_type is 4 */
	/* valid when channels_num is set */
	काष्ठा mt76_connac_mcu_scan_channel channels[32];
	__le16 ies_len;
	u8 ies[MT76_CONNAC_SCAN_IE_LEN];
	/* following fields are valid अगर version > 0 */
	u8 ext_channels_num;
	u8 ext_ssids_num;
	__le16 channel_min_dwell_समय;
	काष्ठा mt76_connac_mcu_scan_channel ext_channels[32];
	काष्ठा mt76_connac_mcu_scan_ssid ext_ssids[6];
	u8 bssid[ETH_ALEN];
	u8 अक्रमom_mac[ETH_ALEN]; /* valid when BIT(1) in scan_func is set. */
	u8 pad[63];
	u8 ssid_type_ext;
पूर्ण __packed;

#घोषणा MT76_CONNAC_SCAN_DONE_EVENT_MAX_CHANNEL_NUM		64

काष्ठा mt76_connac_hw_scan_करोne अणु
	u8 seq_num;
	u8 sparse_channel_num;
	काष्ठा mt76_connac_mcu_scan_channel sparse_channel;
	u8 complete_channel_num;
	u8 current_state;
	u8 version;
	u8 pad;
	__le32 beacon_scan_num;
	u8 pno_enabled;
	u8 pad2[3];
	u8 sparse_channel_valid_num;
	u8 pad3[3];
	u8 channel_num[MT76_CONNAC_SCAN_DONE_EVENT_MAX_CHANNEL_NUM];
	/* idle क्रमmat क्रम channel_idle_समय
	 * 0: first bytes: idle समय(ms) 2nd byte: dwell समय(ms)
	 * 1: first bytes: idle समय(8ms) 2nd byte: dwell समय(8ms)
	 * 2: dwell समय (16us)
	 */
	__le16 channel_idle_समय[MT76_CONNAC_SCAN_DONE_EVENT_MAX_CHANNEL_NUM];
	/* beacon and probe response count */
	u8 beacon_probe_num[MT76_CONNAC_SCAN_DONE_EVENT_MAX_CHANNEL_NUM];
	u8 mdrdy_count[MT76_CONNAC_SCAN_DONE_EVENT_MAX_CHANNEL_NUM];
	__le32 beacon_2g_num;
	__le32 beacon_5g_num;
पूर्ण __packed;

काष्ठा mt76_connac_sched_scan_req अणु
	u8 version;
	u8 seq_num;
	u8 stop_on_match;
	u8 ssids_num;
	u8 match_num;
	u8 pad;
	__le16 ie_len;
	काष्ठा mt76_connac_mcu_scan_ssid ssids[MT76_CONNAC_MAX_SCHED_SCAN_SSID];
	काष्ठा mt76_connac_mcu_scan_match match[MT76_CONNAC_MAX_SCAN_MATCH];
	u8 channel_type;
	u8 channels_num;
	u8 पूर्णांकervals_num;
	u8 scan_func; /* MT7663: BIT(0) eable अक्रमom mac address */
	काष्ठा mt76_connac_mcu_scan_channel channels[64];
	__le16 पूर्णांकervals[MT76_CONNAC_MAX_SCHED_SCAN_INTERVAL];
	जोड़ अणु
		काष्ठा अणु
			u8 अक्रमom_mac[ETH_ALEN];
			u8 pad2[58];
		पूर्ण mt7663;
		काष्ठा अणु
			u8 bss_idx;
			u8 pad2[63];
		पूर्ण mt7921;
	पूर्ण;
पूर्ण __packed;

काष्ठा mt76_connac_sched_scan_करोne अणु
	u8 seq_num;
	u8 status; /* 0: ssid found */
	__le16 pad;
पूर्ण __packed;

काष्ठा bss_info_uni_he अणु
	__le16 tag;
	__le16 len;
	__le16 he_rts_thres;
	u8 he_pe_duration;
	u8 su_disable;
	__le16 max_nss_mcs[CMD_HE_MCS_BW_NUM];
	u8 rsv[2];
पूर्ण __packed;

काष्ठा mt76_connac_gtk_rekey_tlv अणु
	__le16 tag;
	__le16 len;
	u8 kek[NL80211_KEK_LEN];
	u8 kck[NL80211_KCK_LEN];
	u8 replay_ctr[NL80211_REPLAY_CTR_LEN];
	u8 rekey_mode; /* 0: rekey offload enable
			* 1: rekey offload disable
			* 2: rekey update
			*/
	u8 keyid;
	u8 pad[2];
	__le32 proto; /* WPA-RSN-WAPI-OPSN */
	__le32 pairwise_cipher;
	__le32 group_cipher;
	__le32 key_mgmt; /* NONE-PSK-IEEE802.1X */
	__le32 mgmt_group_cipher;
	u8 option; /* 1: rekey data update without enabling offload */
	u8 reserverd[3];
पूर्ण __packed;

#घोषणा MT76_CONNAC_WOW_MASK_MAX_LEN			16
#घोषणा MT76_CONNAC_WOW_PATTEN_MAX_LEN			128

काष्ठा mt76_connac_wow_pattern_tlv अणु
	__le16 tag;
	__le16 len;
	u8 index; /* pattern index */
	u8 enable; /* 0: disable
		    * 1: enable
		    */
	u8 data_len; /* pattern length */
	u8 pad;
	u8 mask[MT76_CONNAC_WOW_MASK_MAX_LEN];
	u8 pattern[MT76_CONNAC_WOW_PATTEN_MAX_LEN];
	u8 rsv[4];
पूर्ण __packed;

काष्ठा mt76_connac_wow_ctrl_tlv अणु
	__le16 tag;
	__le16 len;
	u8 cmd; /* 0x1: PM_WOWLAN_REQ_START
		 * 0x2: PM_WOWLAN_REQ_STOP
		 * 0x3: PM_WOWLAN_PARAM_CLEAR
		 */
	u8 trigger; /* 0: NONE
		     * BIT(0): NL80211_WOWLAN_TRIG_MAGIC_PKT
		     * BIT(1): NL80211_WOWLAN_TRIG_ANY
		     * BIT(2): NL80211_WOWLAN_TRIG_DISCONNECT
		     * BIT(3): NL80211_WOWLAN_TRIG_GTK_REKEY_FAILURE
		     * BIT(4): BEACON_LOST
		     * BIT(5): NL80211_WOWLAN_TRIG_NET_DETECT
		     */
	u8 wakeup_hअगर; /* 0x0: HIF_SDIO
			* 0x1: HIF_USB
			* 0x2: HIF_PCIE
			* 0x3: HIF_GPIO
			*/
	u8 pad;
	u8 rsv[4];
पूर्ण __packed;

काष्ठा mt76_connac_wow_gpio_param_tlv अणु
	__le16 tag;
	__le16 len;
	u8 gpio_pin;
	u8 trigger_lvl;
	u8 pad[2];
	__le32 gpio_पूर्णांकerval;
	u8 rsv[4];
पूर्ण __packed;

काष्ठा mt76_connac_arpns_tlv अणु
	__le16 tag;
	__le16 len;
	u8 mode;
	u8 ips_num;
	u8 option;
	u8 pad[1];
पूर्ण __packed;

काष्ठा mt76_connac_suspend_tlv अणु
	__le16 tag;
	__le16 len;
	u8 enable; /* 0: suspend mode disabled
		    * 1: suspend mode enabled
		    */
	u8 mdtim; /* LP parameter */
	u8 wow_suspend; /* 0: update by origin policy
			 * 1: update by wow dtim
			 */
	u8 pad[5];
पूर्ण __packed;

काष्ठा mt76_sta_cmd_info अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा mt76_wcid *wcid;

	काष्ठा ieee80211_vअगर *vअगर;

	bool enable;
	पूर्णांक cmd;
	u8 rcpi;
पूर्ण;

#घोषणा MT_SKU_POWER_LIMIT	161

काष्ठा mt76_connac_sku_tlv अणु
	u8 channel;
	s8 pwr_limit[MT_SKU_POWER_LIMIT];
पूर्ण __packed;

काष्ठा mt76_connac_tx_घातer_limit_tlv अणु
	/* DW0 - common info*/
	u8 ver;
	u8 pad0;
	__le16 len;
	/* DW1 - cmd hपूर्णांक */
	u8 n_chan; /* # channel */
	u8 band; /* 2.4GHz - 5GHz */
	u8 last_msg;
	u8 pad1;
	/* DW3 */
	u8 alpha2[4]; /* regulatory_request.alpha2 */
	u8 pad2[32];
पूर्ण __packed;

काष्ठा mt76_connac_config अणु
	__le16 id;
	u8 type;
	u8 resp_type;
	__le16 data_size;
	__le16 resv;
	u8 data[320];
पूर्ण __packed;

#घोषणा to_wcid_lo(id)		FIELD_GET(GENMASK(7, 0), (u16)id)
#घोषणा to_wcid_hi(id)		FIELD_GET(GENMASK(9, 8), (u16)id)

अटल अंतरभूत व्योम
mt76_connac_mcu_get_wlan_idx(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid,
			     u8 *wlan_idx_lo, u8 *wlan_idx_hi)
अणु
	*wlan_idx_hi = 0;

	अगर (is_mt7921(dev)) अणु
		*wlan_idx_lo = wcid ? to_wcid_lo(wcid->idx) : 0;
		*wlan_idx_hi = wcid ? to_wcid_hi(wcid->idx) : 0;
	पूर्ण अन्यथा अणु
		*wlan_idx_lo = wcid ? wcid->idx : 0;
	पूर्ण
पूर्ण

काष्ठा sk_buff *
mt76_connac_mcu_alloc_sta_req(काष्ठा mt76_dev *dev, काष्ठा mt76_vअगर *mvअगर,
			      काष्ठा mt76_wcid *wcid);
काष्ठा wtbl_req_hdr *
mt76_connac_mcu_alloc_wtbl_req(काष्ठा mt76_dev *dev, काष्ठा mt76_wcid *wcid,
			       पूर्णांक cmd, व्योम *sta_wtbl, काष्ठा sk_buff **skb);
काष्ठा tlv *mt76_connac_mcu_add_nested_tlv(काष्ठा sk_buff *skb, पूर्णांक tag,
					   पूर्णांक len, व्योम *sta_ntlv,
					   व्योम *sta_wtbl);
अटल अंतरभूत काष्ठा tlv *
mt76_connac_mcu_add_tlv(काष्ठा sk_buff *skb, पूर्णांक tag, पूर्णांक len)
अणु
	वापस mt76_connac_mcu_add_nested_tlv(skb, tag, len, skb->data, शून्य);
पूर्ण

पूर्णांक mt76_connac_mcu_set_channel_करोमुख्य(काष्ठा mt76_phy *phy);
पूर्णांक mt76_connac_mcu_set_vअगर_ps(काष्ठा mt76_dev *dev, काष्ठा ieee80211_vअगर *vअगर);
व्योम mt76_connac_mcu_sta_basic_tlv(काष्ठा sk_buff *skb,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta, bool enable);
व्योम mt76_connac_mcu_wtbl_generic_tlv(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta, व्योम *sta_wtbl,
				      व्योम *wtbl_tlv);
व्योम mt76_connac_mcu_wtbl_hdr_trans_tlv(काष्ठा sk_buff *skb,
					काष्ठा mt76_wcid *wcid,
					व्योम *sta_wtbl, व्योम *wtbl_tlv);
व्योम mt76_connac_mcu_sta_tlv(काष्ठा mt76_phy *mphy, काष्ठा sk_buff *skb,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा ieee80211_vअगर *vअगर,
			     u8 rcpi);
व्योम mt76_connac_mcu_wtbl_ht_tlv(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
				 काष्ठा ieee80211_sta *sta, व्योम *sta_wtbl,
				 व्योम *wtbl_tlv);
व्योम mt76_connac_mcu_wtbl_ba_tlv(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
				 काष्ठा ieee80211_ampdu_params *params,
				 bool enable, bool tx, व्योम *sta_wtbl,
				 व्योम *wtbl_tlv);
व्योम mt76_connac_mcu_sta_ba_tlv(काष्ठा sk_buff *skb,
				काष्ठा ieee80211_ampdu_params *params,
				bool enable, bool tx);
पूर्णांक mt76_connac_mcu_uni_add_dev(काष्ठा mt76_phy *phy,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा mt76_wcid *wcid,
				bool enable);
पूर्णांक mt76_connac_mcu_sta_ba(काष्ठा mt76_dev *dev, काष्ठा mt76_vअगर *mvअगर,
			   काष्ठा ieee80211_ampdu_params *params,
			   bool enable, bool tx);
पूर्णांक mt76_connac_mcu_uni_add_bss(काष्ठा mt76_phy *phy,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा mt76_wcid *wcid,
				bool enable);
पूर्णांक mt76_connac_mcu_add_sta_cmd(काष्ठा mt76_phy *phy,
				काष्ठा mt76_sta_cmd_info *info);
व्योम mt76_connac_mcu_beacon_loss_iter(व्योम *priv, u8 *mac,
				      काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक mt76_connac_mcu_set_rts_thresh(काष्ठा mt76_dev *dev, u32 val, u8 band);
पूर्णांक mt76_connac_mcu_set_mac_enable(काष्ठा mt76_dev *dev, पूर्णांक band, bool enable,
				   bool hdr_trans);
पूर्णांक mt76_connac_mcu_init_करोwnload(काष्ठा mt76_dev *dev, u32 addr, u32 len,
				  u32 mode);
पूर्णांक mt76_connac_mcu_start_patch(काष्ठा mt76_dev *dev);
पूर्णांक mt76_connac_mcu_patch_sem_ctrl(काष्ठा mt76_dev *dev, bool get);
पूर्णांक mt76_connac_mcu_start_firmware(काष्ठा mt76_dev *dev, u32 addr, u32 option);

पूर्णांक mt76_connac_mcu_hw_scan(काष्ठा mt76_phy *phy, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_scan_request *scan_req);
पूर्णांक mt76_connac_mcu_cancel_hw_scan(काष्ठा mt76_phy *phy,
				   काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक mt76_connac_mcu_sched_scan_req(काष्ठा mt76_phy *phy,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा cfg80211_sched_scan_request *sreq);
पूर्णांक mt76_connac_mcu_sched_scan_enable(काष्ठा mt76_phy *phy,
				      काष्ठा ieee80211_vअगर *vअगर,
				      bool enable);
पूर्णांक mt76_connac_mcu_update_arp_filter(काष्ठा mt76_dev *dev,
				      काष्ठा mt76_vअगर *vअगर,
				      काष्ठा ieee80211_bss_conf *info);
पूर्णांक mt76_connac_mcu_update_gtk_rekey(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा cfg80211_gtk_rekey_data *key);
पूर्णांक mt76_connac_mcu_set_hअगर_suspend(काष्ठा mt76_dev *dev, bool suspend);
व्योम mt76_connac_mcu_set_suspend_iter(व्योम *priv, u8 *mac,
				      काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक mt76_connac_mcu_chip_config(काष्ठा mt76_dev *dev);
पूर्णांक mt76_connac_mcu_set_deep_sleep(काष्ठा mt76_dev *dev, bool enable);
व्योम mt76_connac_mcu_coredump_event(काष्ठा mt76_dev *dev, काष्ठा sk_buff *skb,
				    काष्ठा mt76_connac_coredump *coredump);
पूर्णांक mt76_connac_mcu_set_rate_txघातer(काष्ठा mt76_phy *phy);
#पूर्ण_अगर /* __MT76_CONNAC_MCU_H */
