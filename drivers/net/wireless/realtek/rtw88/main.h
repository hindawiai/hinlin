<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTK_MAIN_H_
#घोषणा __RTK_MAIN_H_

#समावेश <net/mac80211.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/firmware.h>
#समावेश <linux/average.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>

#समावेश "util.h"

#घोषणा RTW_NAPI_WEIGHT_NUM		64
#घोषणा RTW_MAX_MAC_ID_NUM		32
#घोषणा RTW_MAX_SEC_CAM_NUM		32
#घोषणा MAX_PG_CAM_BACKUP_NUM		8

#घोषणा RTW_MAX_PATTERN_NUM		12
#घोषणा RTW_MAX_PATTERN_MASK_SIZE	16
#घोषणा RTW_MAX_PATTERN_SIZE		128

#घोषणा RTW_WATCH_DOG_DELAY_TIME	round_jअगरfies_relative(HZ * 2)

#घोषणा RFREG_MASK			0xfffff
#घोषणा INV_RF_DATA			0xffffffff
#घोषणा TX_PAGE_SIZE_SHIFT		7

#घोषणा RTW_CHANNEL_WIDTH_MAX		3
#घोषणा RTW_RF_PATH_MAX			4
#घोषणा HW_FEATURE_LEN			13

#घोषणा RTW_TP_SHIFT			18 /* bytes/2s --> Mbps */

बाह्य bool rtw_bf_support;
बाह्य bool rtw_disable_lps_deep_mode;
बाह्य अचिन्हित पूर्णांक rtw_debug_mask;
बाह्य स्थिर काष्ठा ieee80211_ops rtw_ops;

#घोषणा RTW_MAX_CHANNEL_NUM_2G 14
#घोषणा RTW_MAX_CHANNEL_NUM_5G 49

काष्ठा rtw_dev;

क्रमागत rtw_hci_type अणु
	RTW_HCI_TYPE_PCIE,
	RTW_HCI_TYPE_USB,
	RTW_HCI_TYPE_SDIO,

	RTW_HCI_TYPE_UNDEFINE,
पूर्ण;

काष्ठा rtw_hci अणु
	काष्ठा rtw_hci_ops *ops;
	क्रमागत rtw_hci_type type;

	u32 rpwm_addr;
	u32 cpwm_addr;

	u8 bulkout_num;
पूर्ण;

#घोषणा IS_CH_5G_BAND_1(channel) ((channel) >= 36 && (channel <= 48))
#घोषणा IS_CH_5G_BAND_2(channel) ((channel) >= 52 && (channel <= 64))
#घोषणा IS_CH_5G_BAND_3(channel) ((channel) >= 100 && (channel <= 144))
#घोषणा IS_CH_5G_BAND_4(channel) ((channel) >= 149 && (channel <= 177))

#घोषणा IS_CH_5G_BAND_MID(channel) \
	(IS_CH_5G_BAND_2(channel) || IS_CH_5G_BAND_3(channel))

#घोषणा IS_CH_2G_BAND(channel) ((channel) <= 14)
#घोषणा IS_CH_5G_BAND(channel) \
	(IS_CH_5G_BAND_1(channel) || IS_CH_5G_BAND_2(channel) || \
	 IS_CH_5G_BAND_3(channel) || IS_CH_5G_BAND_4(channel))

क्रमागत rtw_supported_band अणु
	RTW_BAND_2G = 1 << 0,
	RTW_BAND_5G = 1 << 1,
	RTW_BAND_60G = 1 << 2,

	RTW_BAND_MAX,
पूर्ण;

/* now, support upto 80M bw */
#घोषणा RTW_MAX_CHANNEL_WIDTH RTW_CHANNEL_WIDTH_80

क्रमागत rtw_bandwidth अणु
	RTW_CHANNEL_WIDTH_20	= 0,
	RTW_CHANNEL_WIDTH_40	= 1,
	RTW_CHANNEL_WIDTH_80	= 2,
	RTW_CHANNEL_WIDTH_160	= 3,
	RTW_CHANNEL_WIDTH_80_80	= 4,
	RTW_CHANNEL_WIDTH_5	= 5,
	RTW_CHANNEL_WIDTH_10	= 6,
पूर्ण;

क्रमागत rtw_sc_offset अणु
	RTW_SC_DONT_CARE	= 0,
	RTW_SC_20_UPPER		= 1,
	RTW_SC_20_LOWER		= 2,
	RTW_SC_20_UPMOST	= 3,
	RTW_SC_20_LOWEST	= 4,
	RTW_SC_40_UPPER		= 9,
	RTW_SC_40_LOWER		= 10,
पूर्ण;

क्रमागत rtw_net_type अणु
	RTW_NET_NO_LINK		= 0,
	RTW_NET_AD_HOC		= 1,
	RTW_NET_MGD_LINKED	= 2,
	RTW_NET_AP_MODE		= 3,
पूर्ण;

क्रमागत rtw_rf_type अणु
	RF_1T1R			= 0,
	RF_1T2R			= 1,
	RF_2T2R			= 2,
	RF_2T3R			= 3,
	RF_2T4R			= 4,
	RF_3T3R			= 5,
	RF_3T4R			= 6,
	RF_4T4R			= 7,
	RF_TYPE_MAX,
पूर्ण;

क्रमागत rtw_rf_path अणु
	RF_PATH_A = 0,
	RF_PATH_B = 1,
	RF_PATH_C = 2,
	RF_PATH_D = 3,
पूर्ण;

क्रमागत rtw_bb_path अणु
	BB_PATH_A = BIT(0),
	BB_PATH_B = BIT(1),
	BB_PATH_C = BIT(2),
	BB_PATH_D = BIT(3),

	BB_PATH_AB = (BB_PATH_A | BB_PATH_B),
	BB_PATH_AC = (BB_PATH_A | BB_PATH_C),
	BB_PATH_AD = (BB_PATH_A | BB_PATH_D),
	BB_PATH_BC = (BB_PATH_B | BB_PATH_C),
	BB_PATH_BD = (BB_PATH_B | BB_PATH_D),
	BB_PATH_CD = (BB_PATH_C | BB_PATH_D),

	BB_PATH_ABC = (BB_PATH_A | BB_PATH_B | BB_PATH_C),
	BB_PATH_ABD = (BB_PATH_A | BB_PATH_B | BB_PATH_D),
	BB_PATH_ACD = (BB_PATH_A | BB_PATH_C | BB_PATH_D),
	BB_PATH_BCD = (BB_PATH_B | BB_PATH_C | BB_PATH_D),

	BB_PATH_ABCD = (BB_PATH_A | BB_PATH_B | BB_PATH_C | BB_PATH_D),
पूर्ण;

क्रमागत rtw_rate_section अणु
	RTW_RATE_SECTION_CCK = 0,
	RTW_RATE_SECTION_OFDM,
	RTW_RATE_SECTION_HT_1S,
	RTW_RATE_SECTION_HT_2S,
	RTW_RATE_SECTION_VHT_1S,
	RTW_RATE_SECTION_VHT_2S,

	/* keep last */
	RTW_RATE_SECTION_MAX,
पूर्ण;

क्रमागत rtw_wireless_set अणु
	WIRELESS_CCK	= 0x00000001,
	WIRELESS_OFDM	= 0x00000002,
	WIRELESS_HT	= 0x00000004,
	WIRELESS_VHT	= 0x00000008,
पूर्ण;

#घोषणा HT_STBC_EN	BIT(0)
#घोषणा VHT_STBC_EN	BIT(1)
#घोषणा HT_LDPC_EN	BIT(0)
#घोषणा VHT_LDPC_EN	BIT(1)

क्रमागत rtw_chip_type अणु
	RTW_CHIP_TYPE_8822B,
	RTW_CHIP_TYPE_8822C,
	RTW_CHIP_TYPE_8723D,
	RTW_CHIP_TYPE_8821C,
पूर्ण;

क्रमागत rtw_tx_queue_type अणु
	/* the order of AC queues matters */
	RTW_TX_QUEUE_BK = 0x0,
	RTW_TX_QUEUE_BE = 0x1,
	RTW_TX_QUEUE_VI = 0x2,
	RTW_TX_QUEUE_VO = 0x3,

	RTW_TX_QUEUE_BCN = 0x4,
	RTW_TX_QUEUE_MGMT = 0x5,
	RTW_TX_QUEUE_HI0 = 0x6,
	RTW_TX_QUEUE_H2C = 0x7,
	/* keep it last */
	RTK_MAX_TX_QUEUE_NUM
पूर्ण;

क्रमागत rtw_rx_queue_type अणु
	RTW_RX_QUEUE_MPDU = 0x0,
	RTW_RX_QUEUE_C2H = 0x1,
	/* keep it last */
	RTK_MAX_RX_QUEUE_NUM
पूर्ण;

क्रमागत rtw_fw_type अणु
	RTW_NORMAL_FW = 0x0,
	RTW_WOWLAN_FW = 0x1,
पूर्ण;

क्रमागत rtw_rate_index अणु
	RTW_RATEID_BGN_40M_2SS	= 0,
	RTW_RATEID_BGN_40M_1SS	= 1,
	RTW_RATEID_BGN_20M_2SS	= 2,
	RTW_RATEID_BGN_20M_1SS	= 3,
	RTW_RATEID_GN_N2SS	= 4,
	RTW_RATEID_GN_N1SS	= 5,
	RTW_RATEID_BG		= 6,
	RTW_RATEID_G		= 7,
	RTW_RATEID_B_20M	= 8,
	RTW_RATEID_ARFR0_AC_2SS	= 9,
	RTW_RATEID_ARFR1_AC_1SS	= 10,
	RTW_RATEID_ARFR2_AC_2G_1SS = 11,
	RTW_RATEID_ARFR3_AC_2G_2SS = 12,
	RTW_RATEID_ARFR4_AC_3SS	= 13,
	RTW_RATEID_ARFR5_N_3SS	= 14,
	RTW_RATEID_ARFR7_N_4SS	= 15,
	RTW_RATEID_ARFR6_AC_4SS	= 16
पूर्ण;

क्रमागत rtw_trx_desc_rate अणु
	DESC_RATE1M	= 0x00,
	DESC_RATE2M	= 0x01,
	DESC_RATE5_5M	= 0x02,
	DESC_RATE11M	= 0x03,

	DESC_RATE6M	= 0x04,
	DESC_RATE9M	= 0x05,
	DESC_RATE12M	= 0x06,
	DESC_RATE18M	= 0x07,
	DESC_RATE24M	= 0x08,
	DESC_RATE36M	= 0x09,
	DESC_RATE48M	= 0x0a,
	DESC_RATE54M	= 0x0b,

	DESC_RATEMCS0	= 0x0c,
	DESC_RATEMCS1	= 0x0d,
	DESC_RATEMCS2	= 0x0e,
	DESC_RATEMCS3	= 0x0f,
	DESC_RATEMCS4	= 0x10,
	DESC_RATEMCS5	= 0x11,
	DESC_RATEMCS6	= 0x12,
	DESC_RATEMCS7	= 0x13,
	DESC_RATEMCS8	= 0x14,
	DESC_RATEMCS9	= 0x15,
	DESC_RATEMCS10	= 0x16,
	DESC_RATEMCS11	= 0x17,
	DESC_RATEMCS12	= 0x18,
	DESC_RATEMCS13	= 0x19,
	DESC_RATEMCS14	= 0x1a,
	DESC_RATEMCS15	= 0x1b,
	DESC_RATEMCS16	= 0x1c,
	DESC_RATEMCS17	= 0x1d,
	DESC_RATEMCS18	= 0x1e,
	DESC_RATEMCS19	= 0x1f,
	DESC_RATEMCS20	= 0x20,
	DESC_RATEMCS21	= 0x21,
	DESC_RATEMCS22	= 0x22,
	DESC_RATEMCS23	= 0x23,
	DESC_RATEMCS24	= 0x24,
	DESC_RATEMCS25	= 0x25,
	DESC_RATEMCS26	= 0x26,
	DESC_RATEMCS27	= 0x27,
	DESC_RATEMCS28	= 0x28,
	DESC_RATEMCS29	= 0x29,
	DESC_RATEMCS30	= 0x2a,
	DESC_RATEMCS31	= 0x2b,

	DESC_RATEVHT1SS_MCS0	= 0x2c,
	DESC_RATEVHT1SS_MCS1	= 0x2d,
	DESC_RATEVHT1SS_MCS2	= 0x2e,
	DESC_RATEVHT1SS_MCS3	= 0x2f,
	DESC_RATEVHT1SS_MCS4	= 0x30,
	DESC_RATEVHT1SS_MCS5	= 0x31,
	DESC_RATEVHT1SS_MCS6	= 0x32,
	DESC_RATEVHT1SS_MCS7	= 0x33,
	DESC_RATEVHT1SS_MCS8	= 0x34,
	DESC_RATEVHT1SS_MCS9	= 0x35,

	DESC_RATEVHT2SS_MCS0	= 0x36,
	DESC_RATEVHT2SS_MCS1	= 0x37,
	DESC_RATEVHT2SS_MCS2	= 0x38,
	DESC_RATEVHT2SS_MCS3	= 0x39,
	DESC_RATEVHT2SS_MCS4	= 0x3a,
	DESC_RATEVHT2SS_MCS5	= 0x3b,
	DESC_RATEVHT2SS_MCS6	= 0x3c,
	DESC_RATEVHT2SS_MCS7	= 0x3d,
	DESC_RATEVHT2SS_MCS8	= 0x3e,
	DESC_RATEVHT2SS_MCS9	= 0x3f,

	DESC_RATEVHT3SS_MCS0	= 0x40,
	DESC_RATEVHT3SS_MCS1	= 0x41,
	DESC_RATEVHT3SS_MCS2	= 0x42,
	DESC_RATEVHT3SS_MCS3	= 0x43,
	DESC_RATEVHT3SS_MCS4	= 0x44,
	DESC_RATEVHT3SS_MCS5	= 0x45,
	DESC_RATEVHT3SS_MCS6	= 0x46,
	DESC_RATEVHT3SS_MCS7	= 0x47,
	DESC_RATEVHT3SS_MCS8	= 0x48,
	DESC_RATEVHT3SS_MCS9	= 0x49,

	DESC_RATEVHT4SS_MCS0	= 0x4a,
	DESC_RATEVHT4SS_MCS1	= 0x4b,
	DESC_RATEVHT4SS_MCS2	= 0x4c,
	DESC_RATEVHT4SS_MCS3	= 0x4d,
	DESC_RATEVHT4SS_MCS4	= 0x4e,
	DESC_RATEVHT4SS_MCS5	= 0x4f,
	DESC_RATEVHT4SS_MCS6	= 0x50,
	DESC_RATEVHT4SS_MCS7	= 0x51,
	DESC_RATEVHT4SS_MCS8	= 0x52,
	DESC_RATEVHT4SS_MCS9	= 0x53,

	DESC_RATE_MAX,
पूर्ण;

क्रमागत rtw_regulatory_करोमुख्यs अणु
	RTW_REGD_FCC		= 0,
	RTW_REGD_MKK		= 1,
	RTW_REGD_ETSI		= 2,
	RTW_REGD_IC		= 3,
	RTW_REGD_KCC		= 4,
	RTW_REGD_ACMA		= 5,
	RTW_REGD_CHILE		= 6,
	RTW_REGD_UKRAINE	= 7,
	RTW_REGD_MEXICO		= 8,
	RTW_REGD_CN		= 9,
	RTW_REGD_WW,

	RTW_REGD_MAX
पूर्ण;

क्रमागत rtw_txq_flags अणु
	RTW_TXQ_AMPDU,
	RTW_TXQ_BLOCK_BA,
पूर्ण;

क्रमागत rtw_flags अणु
	RTW_FLAG_RUNNING,
	RTW_FLAG_FW_RUNNING,
	RTW_FLAG_SCANNING,
	RTW_FLAG_INACTIVE_PS,
	RTW_FLAG_LEISURE_PS,
	RTW_FLAG_LEISURE_PS_DEEP,
	RTW_FLAG_DIG_DISABLE,
	RTW_FLAG_BUSY_TRAFFIC,
	RTW_FLAG_WOWLAN,
	RTW_FLAG_RESTARTING,

	NUM_OF_RTW_FLAGS,
पूर्ण;

क्रमागत rtw_evm अणु
	RTW_EVM_OFDM = 0,
	RTW_EVM_1SS,
	RTW_EVM_2SS_A,
	RTW_EVM_2SS_B,
	/* keep it last */
	RTW_EVM_NUM
पूर्ण;

क्रमागत rtw_snr अणु
	RTW_SNR_OFDM_A = 0,
	RTW_SNR_OFDM_B,
	RTW_SNR_OFDM_C,
	RTW_SNR_OFDM_D,
	RTW_SNR_1SS_A,
	RTW_SNR_1SS_B,
	RTW_SNR_1SS_C,
	RTW_SNR_1SS_D,
	RTW_SNR_2SS_A,
	RTW_SNR_2SS_B,
	RTW_SNR_2SS_C,
	RTW_SNR_2SS_D,
	/* keep it last */
	RTW_SNR_NUM
पूर्ण;

क्रमागत rtw_wow_flags अणु
	RTW_WOW_FLAG_EN_MAGIC_PKT,
	RTW_WOW_FLAG_EN_REKEY_PKT,
	RTW_WOW_FLAG_EN_DISCONNECT,

	/* keep it last */
	RTW_WOW_FLAG_MAX,
पूर्ण;

/* the घातer index is represented by dअगरferences, which cck-1s & ht40-1s are
 * the base values, so क्रम 1s's dअगरferences, there are only ht20 & ofdm
 */
काष्ठा rtw_2g_1s_pwr_idx_dअगरf अणु
#अगर_घोषित __LITTLE_ENDIAN
	s8 ofdm:4;
	s8 bw20:4;
#अन्यथा
	s8 bw20:4;
	s8 ofdm:4;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा rtw_2g_ns_pwr_idx_dअगरf अणु
#अगर_घोषित __LITTLE_ENDIAN
	s8 bw20:4;
	s8 bw40:4;
	s8 cck:4;
	s8 ofdm:4;
#अन्यथा
	s8 ofdm:4;
	s8 cck:4;
	s8 bw40:4;
	s8 bw20:4;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा rtw_2g_txpwr_idx अणु
	u8 cck_base[6];
	u8 bw40_base[5];
	काष्ठा rtw_2g_1s_pwr_idx_dअगरf ht_1s_dअगरf;
	काष्ठा rtw_2g_ns_pwr_idx_dअगरf ht_2s_dअगरf;
	काष्ठा rtw_2g_ns_pwr_idx_dअगरf ht_3s_dअगरf;
	काष्ठा rtw_2g_ns_pwr_idx_dअगरf ht_4s_dअगरf;
पूर्ण;

काष्ठा rtw_5g_ht_1s_pwr_idx_dअगरf अणु
#अगर_घोषित __LITTLE_ENDIAN
	s8 ofdm:4;
	s8 bw20:4;
#अन्यथा
	s8 bw20:4;
	s8 ofdm:4;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा rtw_5g_ht_ns_pwr_idx_dअगरf अणु
#अगर_घोषित __LITTLE_ENDIAN
	s8 bw20:4;
	s8 bw40:4;
#अन्यथा
	s8 bw40:4;
	s8 bw20:4;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा rtw_5g_ofdm_ns_pwr_idx_dअगरf अणु
#अगर_घोषित __LITTLE_ENDIAN
	s8 ofdm_3s:4;
	s8 ofdm_2s:4;
	s8 ofdm_4s:4;
	s8 res:4;
#अन्यथा
	s8 res:4;
	s8 ofdm_4s:4;
	s8 ofdm_2s:4;
	s8 ofdm_3s:4;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा rtw_5g_vht_ns_pwr_idx_dअगरf अणु
#अगर_घोषित __LITTLE_ENDIAN
	s8 bw160:4;
	s8 bw80:4;
#अन्यथा
	s8 bw80:4;
	s8 bw160:4;
#पूर्ण_अगर
पूर्ण __packed;

काष्ठा rtw_5g_txpwr_idx अणु
	u8 bw40_base[14];
	काष्ठा rtw_5g_ht_1s_pwr_idx_dअगरf ht_1s_dअगरf;
	काष्ठा rtw_5g_ht_ns_pwr_idx_dअगरf ht_2s_dअगरf;
	काष्ठा rtw_5g_ht_ns_pwr_idx_dअगरf ht_3s_dअगरf;
	काष्ठा rtw_5g_ht_ns_pwr_idx_dअगरf ht_4s_dअगरf;
	काष्ठा rtw_5g_ofdm_ns_pwr_idx_dअगरf ofdm_dअगरf;
	काष्ठा rtw_5g_vht_ns_pwr_idx_dअगरf vht_1s_dअगरf;
	काष्ठा rtw_5g_vht_ns_pwr_idx_dअगरf vht_2s_dअगरf;
	काष्ठा rtw_5g_vht_ns_pwr_idx_dअगरf vht_3s_dअगरf;
	काष्ठा rtw_5g_vht_ns_pwr_idx_dअगरf vht_4s_dअगरf;
पूर्ण;

काष्ठा rtw_txpwr_idx अणु
	काष्ठा rtw_2g_txpwr_idx pwr_idx_2g;
	काष्ठा rtw_5g_txpwr_idx pwr_idx_5g;
पूर्ण;

काष्ठा rtw_समयr_list अणु
	काष्ठा समयr_list समयr;
	व्योम (*function)(व्योम *data);
	व्योम *args;
पूर्ण;

काष्ठा rtw_channel_params अणु
	u8 center_chan;
	u8 bandwidth;
	u8 primary_chan_idx;
	/* center channel by dअगरferent available bandwidth,
	 * val of (bw > current bandwidth) is invalid
	 */
	u8 cch_by_bw[RTW_MAX_CHANNEL_WIDTH + 1];
पूर्ण;

काष्ठा rtw_hw_reg अणु
	u32 addr;
	u32 mask;
पूर्ण;

काष्ठा rtw_ltecoex_addr अणु
	u32 ctrl;
	u32 wdata;
	u32 rdata;
पूर्ण;

काष्ठा rtw_reg_करोमुख्य अणु
	u32 addr;
	u32 mask;
#घोषणा RTW_REG_DOMAIN_MAC32	0
#घोषणा RTW_REG_DOMAIN_MAC16	1
#घोषणा RTW_REG_DOMAIN_MAC8	2
#घोषणा RTW_REG_DOMAIN_RF_A	3
#घोषणा RTW_REG_DOMAIN_RF_B	4
#घोषणा RTW_REG_DOMAIN_NL	0xFF
	u8 करोमुख्य;
पूर्ण;

काष्ठा rtw_rf_sipi_addr अणु
	u32 hssi_1;
	u32 hssi_2;
	u32 lssi_पढ़ो;
	u32 lssi_पढ़ो_pi;
पूर्ण;

काष्ठा rtw_backup_info अणु
	u8 len;
	u32 reg;
	u32 val;
पूर्ण;

क्रमागत rtw_vअगर_port_set अणु
	PORT_SET_MAC_ADDR	= BIT(0),
	PORT_SET_BSSID		= BIT(1),
	PORT_SET_NET_TYPE	= BIT(2),
	PORT_SET_AID		= BIT(3),
	PORT_SET_BCN_CTRL	= BIT(4),
पूर्ण;

काष्ठा rtw_vअगर_port अणु
	काष्ठा rtw_hw_reg mac_addr;
	काष्ठा rtw_hw_reg bssid;
	काष्ठा rtw_hw_reg net_type;
	काष्ठा rtw_hw_reg aid;
	काष्ठा rtw_hw_reg bcn_ctrl;
पूर्ण;

काष्ठा rtw_tx_pkt_info अणु
	u32 tx_pkt_size;
	u8 offset;
	u8 pkt_offset;
	u8 mac_id;
	u8 rate_id;
	u8 rate;
	u8 qsel;
	u8 bw;
	u8 sec_type;
	u8 sn;
	bool ampdu_en;
	u8 ampdu_factor;
	u8 ampdu_density;
	u16 seq;
	bool stbc;
	bool ldpc;
	bool dis_rate_fallback;
	bool bmc;
	bool use_rate;
	bool ls;
	bool fs;
	bool लघु_gi;
	bool report;
	bool rts;
	bool dis_qsअन्यथाq;
	bool en_hwseq;
	u8 hw_ssn_sel;
	bool nav_use_hdr;
	bool bt_null;
पूर्ण;

काष्ठा rtw_rx_pkt_stat अणु
	bool phy_status;
	bool icv_err;
	bool crc_err;
	bool decrypted;
	bool is_c2h;

	s32 संकेत_घातer;
	u16 pkt_len;
	u8 bw;
	u8 drv_info_sz;
	u8 shअगरt;
	u8 rate;
	u8 mac_id;
	u8 cam_id;
	u8 ppdu_cnt;
	u32 tsf_low;
	s8 rx_घातer[RTW_RF_PATH_MAX];
	u8 rssi;
	u8 rxsc;
	s8 rx_snr[RTW_RF_PATH_MAX];
	u8 rx_evm[RTW_RF_PATH_MAX];
	s8 cfo_tail[RTW_RF_PATH_MAX];

	काष्ठा rtw_sta_info *si;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ieee80211_hdr *hdr;
पूर्ण;

DECLARE_EWMA(tp, 10, 2);

काष्ठा rtw_traffic_stats अणु
	/* units in bytes */
	u64 tx_unicast;
	u64 rx_unicast;

	/* count क्रम packets */
	u64 tx_cnt;
	u64 rx_cnt;

	/* units in Mbps */
	u32 tx_throughput;
	u32 rx_throughput;
	काष्ठा ewma_tp tx_ewma_tp;
	काष्ठा ewma_tp rx_ewma_tp;
पूर्ण;

क्रमागत rtw_lps_mode अणु
	RTW_MODE_ACTIVE	= 0,
	RTW_MODE_LPS	= 1,
	RTW_MODE_WMM_PS	= 2,
पूर्ण;

क्रमागत rtw_lps_deep_mode अणु
	LPS_DEEP_MODE_NONE	= 0,
	LPS_DEEP_MODE_LCLK	= 1,
	LPS_DEEP_MODE_PG	= 2,
पूर्ण;

क्रमागत rtw_pwr_state अणु
	RTW_RF_OFF	= 0x0,
	RTW_RF_ON	= 0x4,
	RTW_ALL_ON	= 0xc,
पूर्ण;

काष्ठा rtw_lps_conf अणु
	क्रमागत rtw_lps_mode mode;
	क्रमागत rtw_lps_deep_mode deep_mode;
	क्रमागत rtw_lps_deep_mode wow_deep_mode;
	क्रमागत rtw_pwr_state state;
	u8 awake_पूर्णांकerval;
	u8 rlbm;
	u8 smart_ps;
	u8 port_id;
	bool sec_cam_backup;
	bool pattern_cam_backup;
पूर्ण;

क्रमागत rtw_hw_key_type अणु
	RTW_CAM_NONE	= 0,
	RTW_CAM_WEP40	= 1,
	RTW_CAM_TKIP	= 2,
	RTW_CAM_AES	= 4,
	RTW_CAM_WEP104	= 5,
पूर्ण;

काष्ठा rtw_cam_entry अणु
	bool valid;
	bool group;
	u8 addr[ETH_ALEN];
	u8 hw_key_type;
	काष्ठा ieee80211_key_conf *key;
पूर्ण;

काष्ठा rtw_sec_desc अणु
	/* search strategy */
	bool शेष_key_search;

	u32 total_cam_num;
	काष्ठा rtw_cam_entry cam_table[RTW_MAX_SEC_CAM_NUM];
	DECLARE_BITMAP(cam_map, RTW_MAX_SEC_CAM_NUM);
पूर्ण;

काष्ठा rtw_tx_report अणु
	/* protect the tx report queue */
	spinlock_t q_lock;
	काष्ठा sk_buff_head queue;
	atomic_t sn;
	काष्ठा समयr_list purge_समयr;
पूर्ण;

काष्ठा rtw_ra_report अणु
	काष्ठा rate_info txrate;
	u32 bit_rate;
	u8 desc_rate;
पूर्ण;

काष्ठा rtw_txq अणु
	काष्ठा list_head list;

	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ last_push;
पूर्ण;

#घोषणा RTW_BC_MC_MACID 1
DECLARE_EWMA(rssi, 10, 16);

काष्ठा rtw_sta_info अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_vअगर *vअगर;

	काष्ठा ewma_rssi avg_rssi;
	u8 rssi_level;

	u8 mac_id;
	u8 rate_id;
	क्रमागत rtw_bandwidth bw_mode;
	क्रमागत rtw_rf_type rf_type;
	क्रमागत rtw_wireless_set wireless_set;
	u8 stbc_en:2;
	u8 ldpc_en:2;
	bool sgi_enable;
	bool vht_enable;
	bool updated;
	u8 init_ra_lv;
	u64 ra_mask;

	DECLARE_BITMAP(tid_ba, IEEE80211_NUM_TIDS);

	काष्ठा rtw_ra_report ra_report;

	bool use_cfg_mask;
	काष्ठा cfg80211_bitrate_mask *mask;
पूर्ण;

क्रमागत rtw_bfee_role अणु
	RTW_BFEE_NONE,
	RTW_BFEE_SU,
	RTW_BFEE_MU
पूर्ण;

काष्ठा rtw_bfee अणु
	क्रमागत rtw_bfee_role role;

	u16 p_aid;
	u8 g_id;
	u8 mac_addr[ETH_ALEN];
	u8 sound_dim;

	/* SU-MIMO */
	u8 su_reg_index;

	/* MU-MIMO */
	u16 aid;
पूर्ण;

काष्ठा rtw_bf_info अणु
	u8 bfer_mu_cnt;
	u8 bfer_su_cnt;
	DECLARE_BITMAP(bfer_su_reg_maping, 2);
	u8 cur_csi_rpt_rate;
पूर्ण;

काष्ठा rtw_vअगर अणु
	क्रमागत rtw_net_type net_type;
	u16 aid;
	u8 mac_addr[ETH_ALEN];
	u8 bssid[ETH_ALEN];
	u8 port;
	u8 bcn_ctrl;
	काष्ठा list_head rsvd_page_list;
	काष्ठा ieee80211_tx_queue_params tx_params[IEEE80211_NUM_ACS];
	स्थिर काष्ठा rtw_vअगर_port *conf;

	काष्ठा rtw_traffic_stats stats;

	काष्ठा rtw_bfee bfee;
पूर्ण;

काष्ठा rtw_regulatory अणु
	अक्षर alpha2[2];
	u8 chplan;
	u8 txpwr_regd;
पूर्ण;

काष्ठा rtw_chip_ops अणु
	पूर्णांक (*mac_init)(काष्ठा rtw_dev *rtwdev);
	व्योम (*dump_fw_crash)(काष्ठा rtw_dev *rtwdev);
	व्योम (*shutकरोwn)(काष्ठा rtw_dev *rtwdev);
	पूर्णांक (*पढ़ो_efuse)(काष्ठा rtw_dev *rtwdev, u8 *map);
	व्योम (*phy_set_param)(काष्ठा rtw_dev *rtwdev);
	व्योम (*set_channel)(काष्ठा rtw_dev *rtwdev, u8 channel,
			    u8 bandwidth, u8 primary_chan_idx);
	व्योम (*query_rx_desc)(काष्ठा rtw_dev *rtwdev, u8 *rx_desc,
			      काष्ठा rtw_rx_pkt_stat *pkt_stat,
			      काष्ठा ieee80211_rx_status *rx_status);
	u32 (*पढ़ो_rf)(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
		       u32 addr, u32 mask);
	bool (*ग_लिखो_rf)(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_rf_path rf_path,
			 u32 addr, u32 mask, u32 data);
	व्योम (*set_tx_घातer_index)(काष्ठा rtw_dev *rtwdev);
	पूर्णांक (*rsvd_page_dump)(काष्ठा rtw_dev *rtwdev, u8 *buf, u32 offset,
			      u32 size);
	पूर्णांक (*set_antenna)(काष्ठा rtw_dev *rtwdev,
			   u32 antenna_tx,
			   u32 antenna_rx);
	व्योम (*cfg_lकरो25)(काष्ठा rtw_dev *rtwdev, bool enable);
	व्योम (*efuse_grant)(काष्ठा rtw_dev *rtwdev, bool enable);
	व्योम (*false_alarm_statistics)(काष्ठा rtw_dev *rtwdev);
	व्योम (*phy_calibration)(काष्ठा rtw_dev *rtwdev);
	व्योम (*dpk_track)(काष्ठा rtw_dev *rtwdev);
	व्योम (*cck_pd_set)(काष्ठा rtw_dev *rtwdev, u8 level);
	व्योम (*pwr_track)(काष्ठा rtw_dev *rtwdev);
	व्योम (*config_bfee)(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
			    काष्ठा rtw_bfee *bfee, bool enable);
	व्योम (*set_gid_table)(काष्ठा rtw_dev *rtwdev,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_bss_conf *conf);
	व्योम (*cfg_csi_rate)(काष्ठा rtw_dev *rtwdev, u8 rssi, u8 cur_rate,
			     u8 fixrate_en, u8 *new_rate);
	व्योम (*cfo_init)(काष्ठा rtw_dev *rtwdev);
	व्योम (*cfo_track)(काष्ठा rtw_dev *rtwdev);

	/* क्रम coex */
	व्योम (*coex_set_init)(काष्ठा rtw_dev *rtwdev);
	व्योम (*coex_set_ant_चयन)(काष्ठा rtw_dev *rtwdev,
				    u8 ctrl_type, u8 pos_type);
	व्योम (*coex_set_gnt_fix)(काष्ठा rtw_dev *rtwdev);
	व्योम (*coex_set_gnt_debug)(काष्ठा rtw_dev *rtwdev);
	व्योम (*coex_set_rfe_type)(काष्ठा rtw_dev *rtwdev);
	व्योम (*coex_set_wl_tx_घातer)(काष्ठा rtw_dev *rtwdev, u8 wl_pwr);
	व्योम (*coex_set_wl_rx_gain)(काष्ठा rtw_dev *rtwdev, bool low_gain);
पूर्ण;

#घोषणा RTW_PWR_POLLING_CNT	20000

#घोषणा RTW_PWR_CMD_READ	0x00
#घोषणा RTW_PWR_CMD_WRITE	0x01
#घोषणा RTW_PWR_CMD_POLLING	0x02
#घोषणा RTW_PWR_CMD_DELAY	0x03
#घोषणा RTW_PWR_CMD_END		0x04

/* define the base address of each block */
#घोषणा RTW_PWR_ADDR_MAC	0x00
#घोषणा RTW_PWR_ADDR_USB	0x01
#घोषणा RTW_PWR_ADDR_PCIE	0x02
#घोषणा RTW_PWR_ADDR_SDIO	0x03

#घोषणा RTW_PWR_INTF_SDIO_MSK	BIT(0)
#घोषणा RTW_PWR_INTF_USB_MSK	BIT(1)
#घोषणा RTW_PWR_INTF_PCI_MSK	BIT(2)
#घोषणा RTW_PWR_INTF_ALL_MSK	(BIT(0) | BIT(1) | BIT(2) | BIT(3))

#घोषणा RTW_PWR_CUT_TEST_MSK	BIT(0)
#घोषणा RTW_PWR_CUT_A_MSK	BIT(1)
#घोषणा RTW_PWR_CUT_B_MSK	BIT(2)
#घोषणा RTW_PWR_CUT_C_MSK	BIT(3)
#घोषणा RTW_PWR_CUT_D_MSK	BIT(4)
#घोषणा RTW_PWR_CUT_E_MSK	BIT(5)
#घोषणा RTW_PWR_CUT_F_MSK	BIT(6)
#घोषणा RTW_PWR_CUT_G_MSK	BIT(7)
#घोषणा RTW_PWR_CUT_ALL_MSK	0xFF

क्रमागत rtw_pwr_seq_cmd_delay_unit अणु
	RTW_PWR_DELAY_US,
	RTW_PWR_DELAY_MS,
पूर्ण;

काष्ठा rtw_pwr_seq_cmd अणु
	u16 offset;
	u8 cut_mask;
	u8 पूर्णांकf_mask;
	u8 base:4;
	u8 cmd:4;
	u8 mask;
	u8 value;
पूर्ण;

क्रमागत rtw_chip_ver अणु
	RTW_CHIP_VER_CUT_A = 0x00,
	RTW_CHIP_VER_CUT_B = 0x01,
	RTW_CHIP_VER_CUT_C = 0x02,
	RTW_CHIP_VER_CUT_D = 0x03,
	RTW_CHIP_VER_CUT_E = 0x04,
	RTW_CHIP_VER_CUT_F = 0x05,
	RTW_CHIP_VER_CUT_G = 0x06,
पूर्ण;

#घोषणा RTW_INTF_PHY_PLATFORM_ALL 0

क्रमागत rtw_पूर्णांकf_phy_cut अणु
	RTW_INTF_PHY_CUT_A = BIT(0),
	RTW_INTF_PHY_CUT_B = BIT(1),
	RTW_INTF_PHY_CUT_C = BIT(2),
	RTW_INTF_PHY_CUT_D = BIT(3),
	RTW_INTF_PHY_CUT_E = BIT(4),
	RTW_INTF_PHY_CUT_F = BIT(5),
	RTW_INTF_PHY_CUT_G = BIT(6),
	RTW_INTF_PHY_CUT_ALL = 0xFFFF,
पूर्ण;

क्रमागत rtw_ip_sel अणु
	RTW_IP_SEL_PHY = 0,
	RTW_IP_SEL_MAC = 1,
	RTW_IP_SEL_DBI = 2,

	RTW_IP_SEL_UNDEF = 0xFFFF
पूर्ण;

क्रमागत rtw_pq_map_id अणु
	RTW_PQ_MAP_VO = 0x0,
	RTW_PQ_MAP_VI = 0x1,
	RTW_PQ_MAP_BE = 0x2,
	RTW_PQ_MAP_BK = 0x3,
	RTW_PQ_MAP_MG = 0x4,
	RTW_PQ_MAP_HI = 0x5,
	RTW_PQ_MAP_NUM = 0x6,

	RTW_PQ_MAP_UNDEF,
पूर्ण;

क्रमागत rtw_dma_mapping अणु
	RTW_DMA_MAPPING_EXTRA	= 0,
	RTW_DMA_MAPPING_LOW	= 1,
	RTW_DMA_MAPPING_NORMAL	= 2,
	RTW_DMA_MAPPING_HIGH	= 3,

	RTW_DMA_MAPPING_MAX,
	RTW_DMA_MAPPING_UNDEF,
पूर्ण;

काष्ठा rtw_rqpn अणु
	क्रमागत rtw_dma_mapping dma_map_vo;
	क्रमागत rtw_dma_mapping dma_map_vi;
	क्रमागत rtw_dma_mapping dma_map_be;
	क्रमागत rtw_dma_mapping dma_map_bk;
	क्रमागत rtw_dma_mapping dma_map_mg;
	क्रमागत rtw_dma_mapping dma_map_hi;
पूर्ण;

काष्ठा rtw_prioq_addr अणु
	u32 rsvd;
	u32 avail;
पूर्ण;

काष्ठा rtw_prioq_addrs अणु
	काष्ठा rtw_prioq_addr prio[RTW_DMA_MAPPING_MAX];
	bool wsize;
पूर्ण;

काष्ठा rtw_page_table अणु
	u16 hq_num;
	u16 nq_num;
	u16 lq_num;
	u16 exq_num;
	u16 gapq_num;
पूर्ण;

काष्ठा rtw_पूर्णांकf_phy_para अणु
	u16 offset;
	u16 value;
	u16 ip_sel;
	u16 cut_mask;
	u16 platक्रमm;
पूर्ण;

काष्ठा rtw_wow_pattern अणु
	u16 crc;
	u8 type;
	u8 valid;
	u8 mask[RTW_MAX_PATTERN_MASK_SIZE];
पूर्ण;

काष्ठा rtw_pno_request अणु
	bool inited;
	u32 match_set_cnt;
	काष्ठा cfg80211_match_set *match_sets;
	u8 channel_cnt;
	काष्ठा ieee80211_channel *channels;
	काष्ठा cfg80211_sched_scan_plan scan_plan;
पूर्ण;

काष्ठा rtw_wow_param अणु
	काष्ठा ieee80211_vअगर *wow_vअगर;
	DECLARE_BITMAP(flags, RTW_WOW_FLAG_MAX);
	u8 txछोड़ो;
	u8 pattern_cnt;
	काष्ठा rtw_wow_pattern patterns[RTW_MAX_PATTERN_NUM];

	bool ips_enabled;
	काष्ठा rtw_pno_request pno_req;
पूर्ण;

काष्ठा rtw_पूर्णांकf_phy_para_table अणु
	स्थिर काष्ठा rtw_पूर्णांकf_phy_para *usb2_para;
	स्थिर काष्ठा rtw_पूर्णांकf_phy_para *usb3_para;
	स्थिर काष्ठा rtw_पूर्णांकf_phy_para *gen1_para;
	स्थिर काष्ठा rtw_पूर्णांकf_phy_para *gen2_para;
	u8 n_usb2_para;
	u8 n_usb3_para;
	u8 n_gen1_para;
	u8 n_gen2_para;
पूर्ण;

काष्ठा rtw_table अणु
	स्थिर व्योम *data;
	स्थिर u32 size;
	व्योम (*parse)(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl);
	व्योम (*करो_cfg)(काष्ठा rtw_dev *rtwdev, स्थिर काष्ठा rtw_table *tbl,
		       u32 addr, u32 data);
	क्रमागत rtw_rf_path rf_path;
पूर्ण;

अटल अंतरभूत व्योम rtw_load_table(काष्ठा rtw_dev *rtwdev,
				  स्थिर काष्ठा rtw_table *tbl)
अणु
	(*tbl->parse)(rtwdev, tbl);
पूर्ण

क्रमागत rtw_rfe_fem अणु
	RTW_RFE_IFEM,
	RTW_RFE_EFEM,
	RTW_RFE_IFEM2G_EFEM5G,
	RTW_RFE_NUM,
पूर्ण;

काष्ठा rtw_rfe_def अणु
	स्थिर काष्ठा rtw_table *phy_pg_tbl;
	स्थिर काष्ठा rtw_table *txpwr_lmt_tbl;
	स्थिर काष्ठा rtw_table *agc_btg_tbl;
पूर्ण;

#घोषणा RTW_DEF_RFE(chip, bb_pg, pwrlmt) अणु				  \
	.phy_pg_tbl = &rtw ## chip ## _bb_pg_type ## bb_pg ## _tbl,	  \
	.txpwr_lmt_tbl = &rtw ## chip ## _txpwr_lmt_type ## pwrlmt ## _tbl, \
	पूर्ण

#घोषणा RTW_DEF_RFE_EXT(chip, bb_pg, pwrlmt, btg) अणु			  \
	.phy_pg_tbl = &rtw ## chip ## _bb_pg_type ## bb_pg ## _tbl,	  \
	.txpwr_lmt_tbl = &rtw ## chip ## _txpwr_lmt_type ## pwrlmt ## _tbl, \
	.agc_btg_tbl = &rtw ## chip ## _agc_btg_type ## btg ## _tbl, \
	पूर्ण

#घोषणा RTW_PWR_TRK_5G_1		0
#घोषणा RTW_PWR_TRK_5G_2		1
#घोषणा RTW_PWR_TRK_5G_3		2
#घोषणा RTW_PWR_TRK_5G_NUM		3

#घोषणा RTW_PWR_TRK_TBL_SZ		30

/* This table stores the values of TX घातer that will be adjusted by घातer
 * tracking.
 *
 * For 5G bands, there are 3 dअगरferent settings.
 * For 2G there are cck rate and ofdm rate with dअगरferent settings.
 */
काष्ठा rtw_pwr_track_tbl अणु
	स्थिर u8 *pwrtrk_5gb_n[RTW_PWR_TRK_5G_NUM];
	स्थिर u8 *pwrtrk_5gb_p[RTW_PWR_TRK_5G_NUM];
	स्थिर u8 *pwrtrk_5ga_n[RTW_PWR_TRK_5G_NUM];
	स्थिर u8 *pwrtrk_5ga_p[RTW_PWR_TRK_5G_NUM];
	स्थिर u8 *pwrtrk_2gb_n;
	स्थिर u8 *pwrtrk_2gb_p;
	स्थिर u8 *pwrtrk_2ga_n;
	स्थिर u8 *pwrtrk_2ga_p;
	स्थिर u8 *pwrtrk_2g_cckb_n;
	स्थिर u8 *pwrtrk_2g_cckb_p;
	स्थिर u8 *pwrtrk_2g_ccka_n;
	स्थिर u8 *pwrtrk_2g_ccka_p;
	स्थिर s8 *pwrtrk_xtal_n;
	स्थिर s8 *pwrtrk_xtal_p;
पूर्ण;

क्रमागत rtw_wlan_cpu अणु
	RTW_WCPU_11AC,
	RTW_WCPU_11N,
पूर्ण;

क्रमागत rtw_fw_fअगरo_sel अणु
	RTW_FW_FIFO_SEL_TX,
	RTW_FW_FIFO_SEL_RX,
	RTW_FW_FIFO_SEL_RSVD_PAGE,
	RTW_FW_FIFO_SEL_REPORT,
	RTW_FW_FIFO_SEL_LLT,
	RTW_FW_FIFO_SEL_RXBUF_FW,

	RTW_FW_FIFO_MAX,
पूर्ण;

/* hardware configuration क्रम each IC */
काष्ठा rtw_chip_info अणु
	काष्ठा rtw_chip_ops *ops;
	u8 id;

	स्थिर अक्षर *fw_name;
	क्रमागत rtw_wlan_cpu wlan_cpu;
	u8 tx_pkt_desc_sz;
	u8 tx_buf_desc_sz;
	u8 rx_pkt_desc_sz;
	u8 rx_buf_desc_sz;
	u32 phy_efuse_size;
	u32 log_efuse_size;
	u32 ptct_efuse_size;
	u32 txff_size;
	u32 rxff_size;
	u32 fw_rxff_size;
	u8 band;
	u8 page_size;
	u8 csi_buf_pg_num;
	u8 dig_max;
	u8 dig_min;
	u8 txgi_factor;
	bool is_pwr_by_rate_dec;
	bool rx_ldpc;
	u8 max_घातer_index;

	u16 fw_fअगरo_addr[RTW_FW_FIFO_MAX];

	bool ht_supported;
	bool vht_supported;
	u8 lps_deep_mode_supported;

	/* init values */
	u8 sys_func_en;
	स्थिर काष्ठा rtw_pwr_seq_cmd **pwr_on_seq;
	स्थिर काष्ठा rtw_pwr_seq_cmd **pwr_off_seq;
	स्थिर काष्ठा rtw_rqpn *rqpn_table;
	स्थिर काष्ठा rtw_prioq_addrs *prioq_addrs;
	स्थिर काष्ठा rtw_page_table *page_table;
	स्थिर काष्ठा rtw_पूर्णांकf_phy_para_table *पूर्णांकf_table;

	स्थिर काष्ठा rtw_hw_reg *dig;
	स्थिर काष्ठा rtw_hw_reg *dig_cck;
	u32 rf_base_addr[2];
	u32 rf_sipi_addr[2];
	स्थिर काष्ठा rtw_rf_sipi_addr *rf_sipi_पढ़ो_addr;
	u8 fix_rf_phy_num;
	स्थिर काष्ठा rtw_ltecoex_addr *ltecoex_addr;

	स्थिर काष्ठा rtw_table *mac_tbl;
	स्थिर काष्ठा rtw_table *agc_tbl;
	स्थिर काष्ठा rtw_table *bb_tbl;
	स्थिर काष्ठा rtw_table *rf_tbl[RTW_RF_PATH_MAX];
	स्थिर काष्ठा rtw_table *rfk_init_tbl;

	स्थिर काष्ठा rtw_rfe_def *rfe_defs;
	u32 rfe_defs_size;

	bool en_dis_dpd;
	u16 dpd_ratemask;
	u8 iqk_threshold;
	u8 lck_threshold;
	स्थिर काष्ठा rtw_pwr_track_tbl *pwr_track_tbl;

	u8 bfer_su_max_num;
	u8 bfer_mu_max_num;

	स्थिर अक्षर *wow_fw_name;
	स्थिर काष्ठा wiphy_wowlan_support *wowlan_stub;
	स्थिर u8 max_sched_scan_ssids;

	/* क्रम 8821c set channel */
	u32 ch_param[3];

	/* coex paras */
	u32 coex_para_ver;
	u8 bt_desired_ver;
	bool scbd_support;
	bool new_scbd10_def; /* true: fix 2M(8822c) */
	bool ble_hid_profile_support;
	u8 pstdma_type; /* 0: LPSoff, 1:LPSon */
	u8 bt_rssi_type;
	u8 ant_isolation;
	u8 rssi_tolerance;
	u8 table_sant_num;
	u8 table_nsant_num;
	u8 tdma_sant_num;
	u8 tdma_nsant_num;
	u8 bt_afh_span_bw20;
	u8 bt_afh_span_bw40;
	u8 afh_5g_num;
	u8 wl_rf_para_num;
	u8 coex_info_hw_regs_num;
	स्थिर u8 *bt_rssi_step;
	स्थिर u8 *wl_rssi_step;
	स्थिर काष्ठा coex_table_para *table_nsant;
	स्थिर काष्ठा coex_table_para *table_sant;
	स्थिर काष्ठा coex_tdma_para *tdma_sant;
	स्थिर काष्ठा coex_tdma_para *tdma_nsant;
	स्थिर काष्ठा coex_rf_para *wl_rf_para_tx;
	स्थिर काष्ठा coex_rf_para *wl_rf_para_rx;
	स्थिर काष्ठा coex_5g_afh_map *afh_5g;
	स्थिर काष्ठा rtw_hw_reg *btg_reg;
	स्थिर काष्ठा rtw_reg_करोमुख्य *coex_info_hw_regs;
	u32 wl_fw_desired_ver;
पूर्ण;

क्रमागत rtw_coex_bt_state_cnt अणु
	COEX_CNT_BT_RETRY,
	COEX_CNT_BT_REINIT,
	COEX_CNT_BT_REENABLE,
	COEX_CNT_BT_POPEVENT,
	COEX_CNT_BT_SETUPLINK,
	COEX_CNT_BT_IGNWLANACT,
	COEX_CNT_BT_INQ,
	COEX_CNT_BT_PAGE,
	COEX_CNT_BT_ROLESWITCH,
	COEX_CNT_BT_AFHUPDATE,
	COEX_CNT_BT_INFOUPDATE,
	COEX_CNT_BT_IQK,
	COEX_CNT_BT_IQKFAIL,

	COEX_CNT_BT_MAX
पूर्ण;

क्रमागत rtw_coex_wl_state_cnt अणु
	COEX_CNT_WL_SCANAP,
	COEX_CNT_WL_CONNPKT,
	COEX_CNT_WL_COEXRUN,
	COEX_CNT_WL_NOISY0,
	COEX_CNT_WL_NOISY1,
	COEX_CNT_WL_NOISY2,
	COEX_CNT_WL_5MS_NOEXTEND,
	COEX_CNT_WL_FW_NOTIFY,

	COEX_CNT_WL_MAX
पूर्ण;

काष्ठा rtw_coex_rfe अणु
	bool ant_चयन_exist;
	bool ant_चयन_भागersity;
	bool ant_चयन_with_bt;
	u8 rfe_module_type;
	u8 ant_चयन_polarity;

	/* true अगर WLG at BTG, अन्यथा at WLAG */
	bool wlg_at_btg;
पूर्ण;

#घोषणा COEX_WL_TDMA_PARA_LENGTH	5

काष्ठा rtw_coex_dm अणु
	bool cur_ps_tdma_on;
	bool cur_wl_rx_low_gain_en;
	bool ignore_wl_act;

	u8 reason;
	u8 bt_rssi_state[4];
	u8 wl_rssi_state[4];
	u8 wl_ch_info[3];
	u8 cur_ps_tdma;
	u8 cur_table;
	u8 ps_tdma_para[5];
	u8 cur_bt_pwr_lvl;
	u8 cur_bt_lna_lvl;
	u8 cur_wl_pwr_lvl;
	u8 bt_status;
	u32 cur_ant_pos_type;
	u32 cur_चयन_status;
	u32 setting_tdma;
	u8 fw_tdma_para[COEX_WL_TDMA_PARA_LENGTH];
पूर्ण;

#घोषणा COEX_BTINFO_SRC_WL_FW	0x0
#घोषणा COEX_BTINFO_SRC_BT_RSP	0x1
#घोषणा COEX_BTINFO_SRC_BT_ACT	0x2
#घोषणा COEX_BTINFO_SRC_BT_IQK	0x3
#घोषणा COEX_BTINFO_SRC_BT_SCBD	0x4
#घोषणा COEX_BTINFO_SRC_H2C60	0x5
#घोषणा COEX_BTINFO_SRC_MAX	0x6

#घोषणा COEX_INFO_FTP		BIT(7)
#घोषणा COEX_INFO_A2DP		BIT(6)
#घोषणा COEX_INFO_HID		BIT(5)
#घोषणा COEX_INFO_SCO_BUSY	BIT(4)
#घोषणा COEX_INFO_ACL_BUSY	BIT(3)
#घोषणा COEX_INFO_INQ_PAGE	BIT(2)
#घोषणा COEX_INFO_SCO_ESCO	BIT(1)
#घोषणा COEX_INFO_CONNECTION	BIT(0)
#घोषणा COEX_BTINFO_LENGTH_MAX	10
#घोषणा COEX_BTINFO_LENGTH	7

काष्ठा rtw_coex_stat अणु
	bool bt_disabled;
	bool bt_disabled_pre;
	bool bt_link_exist;
	bool bt_whck_test;
	bool bt_inq_page;
	bool bt_inq_reमुख्य;
	bool bt_inq;
	bool bt_page;
	bool bt_ble_voice;
	bool bt_ble_exist;
	bool bt_hfp_exist;
	bool bt_a2dp_exist;
	bool bt_hid_exist;
	bool bt_pan_exist; /* PAN or OPP */
	bool bt_opp_exist; /* OPP only */
	bool bt_acl_busy;
	bool bt_fix_2M;
	bool bt_setup_link;
	bool bt_multi_link;
	bool bt_multi_link_pre;
	bool bt_multi_link_reमुख्य;
	bool bt_a2dp_sink;
	bool bt_a2dp_active;
	bool bt_reenable;
	bool bt_ble_scan_en;
	bool bt_init_scan;
	bool bt_slave;
	bool bt_418_hid_exist;
	bool bt_ble_hid_exist;
	bool bt_mailbox_reply;

	bool wl_under_lps;
	bool wl_under_ips;
	bool wl_hi_pri_task1;
	bool wl_hi_pri_task2;
	bool wl_क्रमce_lps_ctrl;
	bool wl_gl_busy;
	bool wl_linkscan_proc;
	bool wl_ps_state_fail;
	bool wl_tx_limit_en;
	bool wl_ampdu_limit_en;
	bool wl_connected;
	bool wl_slot_extend;
	bool wl_cck_lock;
	bool wl_cck_lock_pre;
	bool wl_cck_lock_ever;
	bool wl_connecting;
	bool wl_slot_toggle;
	bool wl_slot_toggle_change; /* अगर toggle to no-toggle */

	u32 bt_supported_version;
	u32 bt_supported_feature;
	u32 hi_pri_tx;
	u32 hi_pri_rx;
	u32 lo_pri_tx;
	u32 lo_pri_rx;
	u32 patch_ver;
	u16 bt_reg_venकरोr_ae;
	u16 bt_reg_venकरोr_ac;
	s8 bt_rssi;
	u8 kt_ver;
	u8 gnt_workaround_state;
	u8 tdma_समयr_base;
	u8 bt_profile_num;
	u8 bt_info_c2h[COEX_BTINFO_SRC_MAX][COEX_BTINFO_LENGTH_MAX];
	u8 bt_info_lb2;
	u8 bt_info_lb3;
	u8 bt_info_hb0;
	u8 bt_info_hb1;
	u8 bt_info_hb2;
	u8 bt_info_hb3;
	u8 bt_ble_scan_type;
	u8 bt_hid_pair_num;
	u8 bt_hid_slot;
	u8 bt_a2dp_bitpool;
	u8 bt_iqk_state;

	u16 wl_beacon_पूर्णांकerval;
	u8 wl_noisy_level;
	u8 wl_fw_dbg_info[10];
	u8 wl_fw_dbg_info_pre[10];
	u8 wl_rx_rate;
	u8 wl_tx_rate;
	u8 wl_rts_rx_rate;
	u8 wl_coex_mode;
	u8 wl_iot_peer;
	u8 ampdu_max_समय;
	u8 wl_tput_dir;

	u8 wl_toggle_para[6];
	u8 wl_toggle_पूर्णांकerval;

	u16 score_board;
	u16 retry_limit;

	/* counters to record bt states */
	u32 cnt_bt[COEX_CNT_BT_MAX];

	/* counters to record wअगरi states */
	u32 cnt_wl[COEX_CNT_WL_MAX];

	/* counters to record bt c2h data */
	u32 cnt_bt_info_c2h[COEX_BTINFO_SRC_MAX];

	u32 darfrc;
	u32 darfrch;
पूर्ण;

काष्ठा rtw_coex अणु
	/* protects coex info request section */
	काष्ठा mutex mutex;
	काष्ठा sk_buff_head queue;
	रुको_queue_head_t रुको;

	bool under_5g;
	bool stop_dm;
	bool मुक्तze;
	bool मुक्तrun;
	bool wl_rf_off;
	bool manual_control;

	काष्ठा rtw_coex_stat stat;
	काष्ठा rtw_coex_dm dm;
	काष्ठा rtw_coex_rfe rfe;

	काष्ठा delayed_work bt_relink_work;
	काष्ठा delayed_work bt_reenable_work;
	काष्ठा delayed_work deमुक्तze_work;
	काष्ठा delayed_work wl_reमुख्य_work;
	काष्ठा delayed_work bt_reमुख्य_work;
	काष्ठा delayed_work wl_connecting_work;
	काष्ठा delayed_work bt_multi_link_reमुख्य_work;
	काष्ठा delayed_work wl_ccklock_work;

पूर्ण;

#घोषणा DPK_RF_REG_NUM 7
#घोषणा DPK_RF_PATH_NUM 2
#घोषणा DPK_BB_REG_NUM 18
#घोषणा DPK_CHANNEL_WIDTH_80 1

DECLARE_EWMA(thermal, 10, 4);

काष्ठा rtw_dpk_info अणु
	bool is_dpk_pwr_on;
	bool is_reload;

	DECLARE_BITMAP(dpk_path_ok, DPK_RF_PATH_NUM);

	u8 thermal_dpk[DPK_RF_PATH_NUM];
	काष्ठा ewma_thermal avg_thermal[DPK_RF_PATH_NUM];

	u32 gnt_control;
	u32 gnt_value;

	u8 result[RTW_RF_PATH_MAX];
	u8 dpk_txagc[RTW_RF_PATH_MAX];
	u32 coef[RTW_RF_PATH_MAX][20];
	u16 dpk_gs[RTW_RF_PATH_MAX];
	u8 thermal_dpk_delta[RTW_RF_PATH_MAX];
	u8 pre_pwsf[RTW_RF_PATH_MAX];

	u8 dpk_band;
	u8 dpk_ch;
	u8 dpk_bw;
पूर्ण;

काष्ठा rtw_phy_cck_pd_reg अणु
	u32 reg_pd;
	u32 mask_pd;
	u32 reg_cs;
	u32 mask_cs;
पूर्ण;

#घोषणा DACK_MSBK_BACKUP_NUM	0xf
#घोषणा DACK_DCK_BACKUP_NUM	0x2

काष्ठा rtw_swing_table अणु
	स्थिर u8 *p[RTW_RF_PATH_MAX];
	स्थिर u8 *n[RTW_RF_PATH_MAX];
पूर्ण;

काष्ठा rtw_pkt_count अणु
	u16 num_bcn_pkt;
	u16 num_qry_pkt[DESC_RATE_MAX];
पूर्ण;

DECLARE_EWMA(evm, 10, 4);
DECLARE_EWMA(snr, 10, 4);

काष्ठा rtw_iqk_info अणु
	bool करोne;
	काष्ठा अणु
		u32 s1_x;
		u32 s1_y;
		u32 s0_x;
		u32 s0_y;
	पूर्ण result;
पूर्ण;

क्रमागत rtw_rf_band अणु
	RF_BAND_2G_CCK,
	RF_BAND_2G_OFDM,
	RF_BAND_5G_L,
	RF_BAND_5G_M,
	RF_BAND_5G_H,
	RF_BAND_MAX
पूर्ण;

#घोषणा RF_GAIN_NUM 11
#घोषणा RF_HW_OFFSET_NUM 10

काष्ठा rtw_gapk_info अणु
	u32 rf3f_bp[RF_BAND_MAX][RF_GAIN_NUM][RTW_RF_PATH_MAX];
	u32 rf3f_fs[RTW_RF_PATH_MAX][RF_GAIN_NUM];
	bool txgapk_bp_करोne;
	s8 offset[RF_GAIN_NUM][RTW_RF_PATH_MAX];
	s8 fianl_offset[RF_GAIN_NUM][RTW_RF_PATH_MAX];
	u8 पढ़ो_txgain;
	u8 channel;
पूर्ण;

काष्ठा rtw_cfo_track अणु
	bool is_adjust;
	u8 crystal_cap;
	s32 cfo_tail[RTW_RF_PATH_MAX];
	s32 cfo_cnt[RTW_RF_PATH_MAX];
	u32 packet_count;
	u32 packet_count_pre;
पूर्ण;

#घोषणा RRSR_INIT_2G 0x15f
#घोषणा RRSR_INIT_5G 0x150

क्रमागत rtw_dm_cap अणु
	RTW_DM_CAP_NA,
	RTW_DM_CAP_TXGAPK,
	RTW_DM_CAP_NUM
पूर्ण;

काष्ठा rtw_dm_info अणु
	u32 cck_fa_cnt;
	u32 ofdm_fa_cnt;
	u32 total_fa_cnt;
	u32 cck_cca_cnt;
	u32 ofdm_cca_cnt;
	u32 total_cca_cnt;

	u32 cck_ok_cnt;
	u32 cck_err_cnt;
	u32 ofdm_ok_cnt;
	u32 ofdm_err_cnt;
	u32 ht_ok_cnt;
	u32 ht_err_cnt;
	u32 vht_ok_cnt;
	u32 vht_err_cnt;

	u8 min_rssi;
	u8 pre_min_rssi;
	u16 fa_history[4];
	u8 igi_history[4];
	u8 igi_biपंचांगap;
	bool damping;
	u8 damping_cnt;
	u8 damping_rssi;

	u8 cck_gi_u_bnd;
	u8 cck_gi_l_bnd;

	u8 tx_rate;
	u32 rrsr_val_init;
	u32 rrsr_mask_min;
	u8 thermal_avg[RTW_RF_PATH_MAX];
	u8 thermal_meter_k;
	u8 thermal_meter_lck;
	s8 delta_घातer_index[RTW_RF_PATH_MAX];
	s8 delta_घातer_index_last[RTW_RF_PATH_MAX];
	u8 शेष_ofdm_index;
	bool pwr_trk_triggered;
	bool pwr_trk_init_trigger;
	काष्ठा ewma_thermal avg_thermal[RTW_RF_PATH_MAX];
	s8 txagc_remnant_cck;
	s8 txagc_remnant_ofdm;

	/* backup dack results क्रम each path and I/Q */
	u32 dack_adck[RTW_RF_PATH_MAX];
	u16 dack_msbk[RTW_RF_PATH_MAX][2][DACK_MSBK_BACKUP_NUM];
	u8 dack_dck[RTW_RF_PATH_MAX][2][DACK_DCK_BACKUP_NUM];

	काष्ठा rtw_dpk_info dpk_info;
	काष्ठा rtw_cfo_track cfo_track;

	/* [bandwidth 0:20M/1:40M][number of path] */
	u8 cck_pd_lv[2][RTW_RF_PATH_MAX];
	u32 cck_fa_avg;
	u8 cck_pd_शेष;

	/* save the last rx phy status क्रम debug */
	s8 rx_snr[RTW_RF_PATH_MAX];
	u8 rx_evm_dbm[RTW_RF_PATH_MAX];
	s16 cfo_tail[RTW_RF_PATH_MAX];
	u8 rssi[RTW_RF_PATH_MAX];
	u8 curr_rx_rate;
	काष्ठा rtw_pkt_count cur_pkt_count;
	काष्ठा rtw_pkt_count last_pkt_count;
	काष्ठा ewma_evm ewma_evm[RTW_EVM_NUM];
	काष्ठा ewma_snr ewma_snr[RTW_SNR_NUM];

	u32 dm_flags; /* क्रमागत rtw_dm_cap */
	काष्ठा rtw_iqk_info iqk;
	काष्ठा rtw_gapk_info gapk;
	bool is_bt_iqk_समयout;
पूर्ण;

काष्ठा rtw_efuse अणु
	u32 size;
	u32 physical_size;
	u32 logical_size;
	u32 protect_size;

	u8 addr[ETH_ALEN];
	u8 channel_plan;
	u8 country_code[2];
	u8 rf_board_option;
	u8 rfe_option;
	u8 घातer_track_type;
	u8 thermal_meter[RTW_RF_PATH_MAX];
	u8 thermal_meter_k;
	u8 crystal_cap;
	u8 ant_भाग_cfg;
	u8 ant_भाग_प्रकारype;
	u8 regd;
	u8 afe;

	u8 lna_type_2g;
	u8 lna_type_5g;
	u8 glna_type;
	u8 alna_type;
	bool ext_lna_2g;
	bool ext_lna_5g;
	u8 pa_type_2g;
	u8 pa_type_5g;
	u8 gpa_type;
	u8 apa_type;
	bool ext_pa_2g;
	bool ext_pa_5g;
	u8 tx_bb_swing_setting_2g;
	u8 tx_bb_swing_setting_5g;

	bool btcoex;
	/* bt share antenna with wअगरi */
	bool share_ant;
	u8 bt_setting;

	काष्ठा अणु
		u8 hci;
		u8 bw;
		u8 ptcl;
		u8 nss;
		u8 ant_num;
	पूर्ण hw_cap;

	काष्ठा rtw_txpwr_idx txpwr_idx_table[4];
पूर्ण;

काष्ठा rtw_phy_cond अणु
#अगर_घोषित __LITTLE_ENDIAN
	u32 rfe:8;
	u32 पूर्णांकf:4;
	u32 pkg:4;
	u32 plat:4;
	u32 पूर्णांकf_rsvd:4;
	u32 cut:4;
	u32 branch:2;
	u32 neg:1;
	u32 pos:1;
#अन्यथा
	u32 pos:1;
	u32 neg:1;
	u32 branch:2;
	u32 cut:4;
	u32 पूर्णांकf_rsvd:4;
	u32 plat:4;
	u32 pkg:4;
	u32 पूर्णांकf:4;
	u32 rfe:8;
#पूर्ण_अगर
	/* क्रम पूर्णांकf:4 */
	#घोषणा INTF_PCIE	BIT(0)
	#घोषणा INTF_USB	BIT(1)
	#घोषणा INTF_SDIO	BIT(2)
	/* क्रम branch:2 */
	#घोषणा BRANCH_IF	0
	#घोषणा BRANCH_ELIF	1
	#घोषणा BRANCH_ELSE	2
	#घोषणा BRANCH_ENDIF	3
पूर्ण;

काष्ठा rtw_fअगरo_conf अणु
	/* tx fअगरo inक्रमmation */
	u16 rsvd_boundary;
	u16 rsvd_pg_num;
	u16 rsvd_drv_pg_num;
	u16 txff_pg_num;
	u16 acq_pg_num;
	u16 rsvd_drv_addr;
	u16 rsvd_h2c_info_addr;
	u16 rsvd_h2c_sta_info_addr;
	u16 rsvd_h2cq_addr;
	u16 rsvd_cpu_instr_addr;
	u16 rsvd_fw_txbuf_addr;
	u16 rsvd_csibuf_addr;
	स्थिर काष्ठा rtw_rqpn *rqpn;
पूर्ण;

#घोषणा FW_CD_TYPE 0xffff
#घोषणा FW_CD_LEN 4
#घोषणा FW_CD_VAL 0xaabbccdd
काष्ठा rtw_fw_state अणु
	स्थिर काष्ठा firmware *firmware;
	काष्ठा rtw_dev *rtwdev;
	काष्ठा completion completion;
	u16 version;
	u8 sub_version;
	u8 sub_index;
	u16 h2c_version;
	u8 prev_dump_seq;
	u32 feature;
पूर्ण;

काष्ठा rtw_hal अणु
	u32 rcr;

	u32 chip_version;
	u8 cut_version;
	u8 mp_chip;
	u8 oem_id;
	काष्ठा rtw_phy_cond phy_cond;

	u8 ps_mode;
	u8 current_channel;
	u8 current_band_width;
	u8 current_band_type;

	/* center channel क्रम dअगरferent available bandwidth,
	 * val of (bw > current_band_width) is invalid
	 */
	u8 cch_by_bw[RTW_MAX_CHANNEL_WIDTH + 1];

	u8 sec_ch_offset;
	u8 rf_type;
	u8 rf_path_num;
	u8 rf_phy_num;
	u32 antenna_tx;
	u32 antenna_rx;
	u8 bfee_sts_cap;

	/* protect tx घातer section */
	काष्ठा mutex tx_घातer_mutex;
	s8 tx_pwr_by_rate_offset_2g[RTW_RF_PATH_MAX]
				   [DESC_RATE_MAX];
	s8 tx_pwr_by_rate_offset_5g[RTW_RF_PATH_MAX]
				   [DESC_RATE_MAX];
	s8 tx_pwr_by_rate_base_2g[RTW_RF_PATH_MAX]
				 [RTW_RATE_SECTION_MAX];
	s8 tx_pwr_by_rate_base_5g[RTW_RF_PATH_MAX]
				 [RTW_RATE_SECTION_MAX];
	s8 tx_pwr_limit_2g[RTW_REGD_MAX]
			  [RTW_CHANNEL_WIDTH_MAX]
			  [RTW_RATE_SECTION_MAX]
			  [RTW_MAX_CHANNEL_NUM_2G];
	s8 tx_pwr_limit_5g[RTW_REGD_MAX]
			  [RTW_CHANNEL_WIDTH_MAX]
			  [RTW_RATE_SECTION_MAX]
			  [RTW_MAX_CHANNEL_NUM_5G];
	s8 tx_pwr_tbl[RTW_RF_PATH_MAX]
		     [DESC_RATE_MAX];
पूर्ण;

काष्ठा rtw_dev अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा device *dev;

	काष्ठा rtw_hci hci;

	काष्ठा rtw_chip_info *chip;
	काष्ठा rtw_hal hal;
	काष्ठा rtw_fअगरo_conf fअगरo;
	काष्ठा rtw_fw_state fw;
	काष्ठा rtw_efuse efuse;
	काष्ठा rtw_sec_desc sec;
	काष्ठा rtw_traffic_stats stats;
	काष्ठा rtw_regulatory regd;
	काष्ठा rtw_bf_info bf_info;

	काष्ठा rtw_dm_info dm_info;
	काष्ठा rtw_coex coex;

	/* ensures exclusive access from mac80211 callbacks */
	काष्ठा mutex mutex;

	/* पढ़ो/ग_लिखो rf रेजिस्टर */
	spinlock_t rf_lock;

	/* watch करोg every 2 sec */
	काष्ठा delayed_work watch_करोg_work;
	u32 watch_करोg_cnt;

	काष्ठा list_head rsvd_page_list;

	/* c2h cmd queue & handler work */
	काष्ठा sk_buff_head c2h_queue;
	काष्ठा work_काष्ठा c2h_work;
	काष्ठा work_काष्ठा fw_recovery_work;

	/* used to protect txqs list */
	spinlock_t txq_lock;
	काष्ठा list_head txqs;
	काष्ठा workqueue_काष्ठा *tx_wq;
	काष्ठा work_काष्ठा tx_work;
	काष्ठा work_काष्ठा ba_work;

	काष्ठा rtw_tx_report tx_report;

	काष्ठा अणु
		/* incicate the mail box to use with fw */
		u8 last_box_num;
		/* protect to send h2c to fw */
		spinlock_t lock;
		u32 seq;
	पूर्ण h2c;

	/* lps घातer state & handler work */
	काष्ठा rtw_lps_conf lps_conf;
	bool ps_enabled;
	काष्ठा completion lps_leave_check;

	काष्ठा dentry *debugfs;

	u8 sta_cnt;
	u32 rts_threshold;

	DECLARE_BITMAP(mac_id_map, RTW_MAX_MAC_ID_NUM);
	DECLARE_BITMAP(flags, NUM_OF_RTW_FLAGS);

	u8 mp_mode;

	काष्ठा rtw_fw_state wow_fw;
	काष्ठा rtw_wow_param wow;

	bool need_rfk;

	/* hci related data, must be last */
	u8 priv[] __aligned(माप(व्योम *));
पूर्ण;

#समावेश "hci.h"

अटल अंतरभूत bool rtw_is_assoc(काष्ठा rtw_dev *rtwdev)
अणु
	वापस !!rtwdev->sta_cnt;
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_txq *rtwtxq_to_txq(काष्ठा rtw_txq *rtwtxq)
अणु
	व्योम *p = rtwtxq;

	वापस container_of(p, काष्ठा ieee80211_txq, drv_priv);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_vअगर *rtwvअगर_to_vअगर(काष्ठा rtw_vअगर *rtwvअगर)
अणु
	व्योम *p = rtwvअगर;

	वापस container_of(p, काष्ठा ieee80211_vअगर, drv_priv);
पूर्ण

अटल अंतरभूत bool rtw_ssid_equal(काष्ठा cfg80211_ssid *a,
				  काष्ठा cfg80211_ssid *b)
अणु
	अगर (!a || !b || a->ssid_len != b->ssid_len)
		वापस false;

	अगर (स_भेद(a->ssid, b->ssid, a->ssid_len))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत व्योम rtw_chip_efuse_grant_on(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (rtwdev->chip->ops->efuse_grant)
		rtwdev->chip->ops->efuse_grant(rtwdev, true);
पूर्ण

अटल अंतरभूत व्योम rtw_chip_efuse_grant_off(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (rtwdev->chip->ops->efuse_grant)
		rtwdev->chip->ops->efuse_grant(rtwdev, false);
पूर्ण

अटल अंतरभूत bool rtw_chip_wcpu_11n(काष्ठा rtw_dev *rtwdev)
अणु
	वापस rtwdev->chip->wlan_cpu == RTW_WCPU_11N;
पूर्ण

अटल अंतरभूत bool rtw_chip_wcpu_11ac(काष्ठा rtw_dev *rtwdev)
अणु
	वापस rtwdev->chip->wlan_cpu == RTW_WCPU_11AC;
पूर्ण

अटल अंतरभूत bool rtw_chip_has_rx_ldpc(काष्ठा rtw_dev *rtwdev)
अणु
	वापस rtwdev->chip->rx_ldpc;
पूर्ण

अटल अंतरभूत व्योम rtw_release_macid(काष्ठा rtw_dev *rtwdev, u8 mac_id)
अणु
	clear_bit(mac_id, rtwdev->mac_id_map);
पूर्ण

अटल अंतरभूत व्योम rtw_chip_dump_fw_crash(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (rtwdev->chip->ops->dump_fw_crash)
		rtwdev->chip->ops->dump_fw_crash(rtwdev);
पूर्ण

व्योम rtw_get_channel_params(काष्ठा cfg80211_chan_def *chandef,
			    काष्ठा rtw_channel_params *ch_param);
bool check_hw_पढ़ोy(काष्ठा rtw_dev *rtwdev, u32 addr, u32 mask, u32 target);
bool ltecoex_पढ़ो_reg(काष्ठा rtw_dev *rtwdev, u16 offset, u32 *val);
bool ltecoex_reg_ग_लिखो(काष्ठा rtw_dev *rtwdev, u16 offset, u32 value);
व्योम rtw_restore_reg(काष्ठा rtw_dev *rtwdev,
		     काष्ठा rtw_backup_info *bckp, u32 num);
व्योम rtw_desc_to_mcsrate(u16 rate, u8 *mcs, u8 *nss);
व्योम rtw_set_channel(काष्ठा rtw_dev *rtwdev);
व्योम rtw_chip_prepare_tx(काष्ठा rtw_dev *rtwdev);
व्योम rtw_vअगर_port_config(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *rtwvअगर,
			 u32 config);
व्योम rtw_tx_report_purge_समयr(काष्ठा समयr_list *t);
व्योम rtw_update_sta_info(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_sta_info *si);
पूर्णांक rtw_core_start(काष्ठा rtw_dev *rtwdev);
व्योम rtw_core_stop(काष्ठा rtw_dev *rtwdev);
पूर्णांक rtw_chip_info_setup(काष्ठा rtw_dev *rtwdev);
पूर्णांक rtw_core_init(काष्ठा rtw_dev *rtwdev);
व्योम rtw_core_deinit(काष्ठा rtw_dev *rtwdev);
पूर्णांक rtw_रेजिस्टर_hw(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_hw *hw);
व्योम rtw_unरेजिस्टर_hw(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_hw *hw);
u16 rtw_desc_to_bitrate(u8 desc_rate);
व्योम rtw_vअगर_assoc_changed(काष्ठा rtw_vअगर *rtwvअगर,
			   काष्ठा ieee80211_bss_conf *conf);
पूर्णांक rtw_sta_add(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_sta *sta,
		काष्ठा ieee80211_vअगर *vअगर);
व्योम rtw_sta_हटाओ(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_sta *sta,
		    bool fw_exist);
व्योम rtw_fw_recovery(काष्ठा rtw_dev *rtwdev);
पूर्णांक rtw_dump_fw(काष्ठा rtw_dev *rtwdev, स्थिर u32 ocp_src, u32 size,
		स्थिर अक्षर *prefix_str);
पूर्णांक rtw_dump_reg(काष्ठा rtw_dev *rtwdev, स्थिर u32 addr, स्थिर u32 size,
		 स्थिर अक्षर *prefix_str);

#पूर्ण_अगर
