<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित	__RTL92E_DM_H__
#घोषणा __RTL92E_DM_H__

#घोषणा	OFDMCCA_TH				500
#घोषणा	BW_IND_BIAS				500
#घोषणा	MF_USC					2
#घोषणा	MF_LSC					1
#घोषणा	MF_USC_LSC				0
#घोषणा	MONITOR_TIME				30

#घोषणा	MAIN_ANT				0
#घोषणा	AUX_ANT					1
#घोषणा	MAIN_ANT_CG_TRX				1
#घोषणा	AUX_ANT_CG_TRX				0
#घोषणा	MAIN_ANT_CGCS_RX			0
#घोषणा	AUX_ANT_CGCS_RX				1

/*RF REG LIST*/
#घोषणा	DM_REG_RF_MODE_11N			0x00
#घोषणा	DM_REG_RF_0B_11N			0x0B
#घोषणा	DM_REG_CHNBW_11N			0x18
#घोषणा	DM_REG_T_METER_11N			0x24
#घोषणा	DM_REG_RF_25_11N			0x25
#घोषणा	DM_REG_RF_26_11N			0x26
#घोषणा	DM_REG_RF_27_11N			0x27
#घोषणा	DM_REG_RF_2B_11N			0x2B
#घोषणा	DM_REG_RF_2C_11N			0x2C
#घोषणा	DM_REG_RXRF_A3_11N			0x3C
#घोषणा	DM_REG_T_METER_92D_11N			0x42
#घोषणा	DM_REG_T_METER_92E_11N			0x42

/*BB REG LIST*/
/*PAGE 8 */
#घोषणा	DM_REG_BB_CTRL_11N			0x800
#घोषणा	DM_REG_RF_PIN_11N			0x804
#घोषणा	DM_REG_PSD_CTRL_11N			0x808
#घोषणा	DM_REG_TX_ANT_CTRL_11N			0x80C
#घोषणा	DM_REG_BB_PWR_SAV5_11N			0x818
#घोषणा	DM_REG_CCK_RPT_FORMAT_11N		0x824
#घोषणा	DM_REG_RX_DEFUALT_A_11N			0x858
#घोषणा	DM_REG_RX_DEFUALT_B_11N			0x85A
#घोषणा	DM_REG_BB_PWR_SAV3_11N			0x85C
#घोषणा	DM_REG_ANTSEL_CTRL_11N			0x860
#घोषणा	DM_REG_RX_ANT_CTRL_11N			0x864
#घोषणा	DM_REG_PIN_CTRL_11N			0x870
#घोषणा	DM_REG_BB_PWR_SAV1_11N			0x874
#घोषणा	DM_REG_ANTSEL_PATH_11N			0x878
#घोषणा	DM_REG_BB_3WIRE_11N			0x88C
#घोषणा	DM_REG_SC_CNT_11N			0x8C4
#घोषणा	DM_REG_PSD_DATA_11N			0x8B4
/*PAGE 9*/
#घोषणा	DM_REG_ANT_MAPPING1_11N			0x914
#घोषणा	DM_REG_ANT_MAPPING2_11N			0x918
/*PAGE A*/
#घोषणा	DM_REG_CCK_ANTDIV_PARA1_11N		0xA00
#घोषणा	DM_REG_CCK_CCA_11N			0xA0A
#घोषणा	DM_REG_CCK_ANTDIV_PARA2_11N		0xA0C
#घोषणा	DM_REG_CCK_ANTDIV_PARA3_11N		0xA10
#घोषणा	DM_REG_CCK_ANTDIV_PARA4_11N		0xA14
#घोषणा	DM_REG_CCK_FILTER_PARA1_11N		0xA22
#घोषणा	DM_REG_CCK_FILTER_PARA2_11N		0xA23
#घोषणा	DM_REG_CCK_FILTER_PARA3_11N		0xA24
#घोषणा	DM_REG_CCK_FILTER_PARA4_11N		0xA25
#घोषणा	DM_REG_CCK_FILTER_PARA5_11N		0xA26
#घोषणा	DM_REG_CCK_FILTER_PARA6_11N		0xA27
#घोषणा	DM_REG_CCK_FILTER_PARA7_11N		0xA28
#घोषणा	DM_REG_CCK_FILTER_PARA8_11N		0xA29
#घोषणा	DM_REG_CCK_FA_RST_11N			0xA2C
#घोषणा	DM_REG_CCK_FA_MSB_11N			0xA58
#घोषणा	DM_REG_CCK_FA_LSB_11N			0xA5C
#घोषणा	DM_REG_CCK_CCA_CNT_11N			0xA60
#घोषणा	DM_REG_BB_PWR_SAV4_11N			0xA74
/*PAGE B */
#घोषणा	DM_REG_LNA_SWITCH_11N			0xB2C
#घोषणा	DM_REG_PATH_SWITCH_11N			0xB30
#घोषणा	DM_REG_RSSI_CTRL_11N			0xB38
#घोषणा	DM_REG_CONFIG_ANTA_11N			0xB68
#घोषणा	DM_REG_RSSI_BT_11N			0xB9C
/*PAGE C */
#घोषणा	DM_REG_OFDM_FA_HOLDC_11N		0xC00
#घोषणा	DM_REG_RX_PATH_11N			0xC04
#घोषणा	DM_REG_TRMUX_11N			0xC08
#घोषणा	DM_REG_OFDM_FA_RSTC_11N			0xC0C
#घोषणा	DM_REG_RXIQI_MATRIX_11N			0xC14
#घोषणा	DM_REG_TXIQK_MATRIX_LSB1_11N		0xC4C
#घोषणा	DM_REG_IGI_A_11N			0xC50
#घोषणा	DM_REG_ANTDIV_PARA2_11N			0xC54
#घोषणा	DM_REG_IGI_B_11N			0xC58
#घोषणा	DM_REG_ANTDIV_PARA3_11N			0xC5C
#घोषणा DM_REG_L1SBD_PD_CH_11N			0XC6C
#घोषणा	DM_REG_BB_PWR_SAV2_11N			0xC70
#घोषणा	DM_REG_RX_OFF_11N			0xC7C
#घोषणा	DM_REG_TXIQK_MATRIXA_11N		0xC80
#घोषणा	DM_REG_TXIQK_MATRIXB_11N		0xC88
#घोषणा	DM_REG_TXIQK_MATRIXA_LSB2_11N		0xC94
#घोषणा	DM_REG_TXIQK_MATRIXB_LSB2_11N		0xC9C
#घोषणा	DM_REG_RXIQK_MATRIX_LSB_11N		0xCA0
#घोषणा	DM_REG_ANTDIV_PARA1_11N			0xCA4
#घोषणा	DM_REG_OFDM_FA_TYPE1_11N		0xCF0
/*PAGE D */
#घोषणा	DM_REG_OFDM_FA_RSTD_11N			0xD00
#घोषणा	DM_REG_OFDM_FA_TYPE2_11N		0xDA0
#घोषणा	DM_REG_OFDM_FA_TYPE3_11N		0xDA4
#घोषणा	DM_REG_OFDM_FA_TYPE4_11N		0xDA8
/*PAGE E */
#घोषणा	DM_REG_TXAGC_A_6_18_11N			0xE00
#घोषणा	DM_REG_TXAGC_A_24_54_11N		0xE04
#घोषणा	DM_REG_TXAGC_A_1_MCS32_11N		0xE08
#घोषणा	DM_REG_TXAGC_A_MCS0_3_11N		0xE10
#घोषणा	DM_REG_TXAGC_A_MCS4_7_11N		0xE14
#घोषणा	DM_REG_TXAGC_A_MCS8_11_11N		0xE18
#घोषणा	DM_REG_TXAGC_A_MCS12_15_11N		0xE1C
#घोषणा	DM_REG_FPGA0_IQK_11N			0xE28
#घोषणा	DM_REG_TXIQK_TONE_A_11N			0xE30
#घोषणा	DM_REG_RXIQK_TONE_A_11N			0xE34
#घोषणा	DM_REG_TXIQK_PI_A_11N			0xE38
#घोषणा	DM_REG_RXIQK_PI_A_11N			0xE3C
#घोषणा	DM_REG_TXIQK_11N			0xE40
#घोषणा	DM_REG_RXIQK_11N			0xE44
#घोषणा	DM_REG_IQK_AGC_PTS_11N			0xE48
#घोषणा	DM_REG_IQK_AGC_RSP_11N			0xE4C
#घोषणा	DM_REG_BLUETOOTH_11N			0xE6C
#घोषणा	DM_REG_RX_WAIT_CCA_11N			0xE70
#घोषणा	DM_REG_TX_CCK_RFON_11N			0xE74
#घोषणा	DM_REG_TX_CCK_BBON_11N			0xE78
#घोषणा	DM_REG_OFDM_RFON_11N			0xE7C
#घोषणा	DM_REG_OFDM_BBON_11N			0xE80
#घोषणा		DM_REG_TX2RX_11N		0xE84
#घोषणा	DM_REG_TX2TX_11N			0xE88
#घोषणा	DM_REG_RX_CCK_11N			0xE8C
#घोषणा	DM_REG_RX_OFDM_11N			0xED0
#घोषणा	DM_REG_RX_WAIT_RIFS_11N			0xED4
#घोषणा	DM_REG_RX2RX_11N			0xED8
#घोषणा	DM_REG_STANDBY_11N			0xEDC
#घोषणा	DM_REG_SLEEP_11N			0xEE0
#घोषणा	DM_REG_PMPD_ANAEN_11N			0xEEC

/*MAC REG LIST*/
#घोषणा	DM_REG_BB_RST_11N			0x02
#घोषणा	DM_REG_ANTSEL_PIN_11N			0x4C
#घोषणा	DM_REG_EARLY_MODE_11N			0x4D0
#घोषणा	DM_REG_RSSI_MONITOR_11N			0x4FE
#घोषणा	DM_REG_EDCA_VO_11N			0x500
#घोषणा	DM_REG_EDCA_VI_11N			0x504
#घोषणा	DM_REG_EDCA_BE_11N			0x508
#घोषणा	DM_REG_EDCA_BK_11N			0x50C
#घोषणा	DM_REG_TXPAUSE_11N			0x522
#घोषणा	DM_REG_RESP_TX_11N			0x6D8
#घोषणा	DM_REG_ANT_TRAIN_PARA1_11N		0x7b0
#घोषणा	DM_REG_ANT_TRAIN_PARA2_11N		0x7b4

/*DIG Related*/
#घोषणा	DM_BIT_IGI_11N				0x0000007F

#घोषणा HAL_DM_DIG_DISABLE			BIT(0)
#घोषणा HAL_DM_HIPWR_DISABLE			BIT(1)

#घोषणा OFDM_TABLE_LENGTH			43
#घोषणा CCK_TABLE_LENGTH			33

#घोषणा OFDM_TABLE_SIZE				43
#घोषणा CCK_TABLE_SIZE				33

#घोषणा BW_AUTO_SWITCH_HIGH_LOW			25
#घोषणा BW_AUTO_SWITCH_LOW_HIGH			30

#घोषणा DM_DIG_FA_UPPER				0x3e
#घोषणा DM_DIG_FA_LOWER				0x1e
#घोषणा DM_DIG_FA_TH0				0x200
#घोषणा DM_DIG_FA_TH1				0x300
#घोषणा DM_DIG_FA_TH2				0x400

#घोषणा RXPATHSELECTION_SS_TH_LOW		30
#घोषणा RXPATHSELECTION_DIFF_TH			18

#घोषणा DM_RATR_STA_INIT			0
#घोषणा DM_RATR_STA_HIGH			1
#घोषणा DM_RATR_STA_MIDDLE			2
#घोषणा DM_RATR_STA_LOW				3

#घोषणा CTS2SELF_THVAL				30
#घोषणा REGC38_TH				20

#घोषणा WAIOTTHVAL				25

#घोषणा TXHIGHPWRLEVEL_NORMAL			0
#घोषणा TXHIGHPWRLEVEL_LEVEL1			1
#घोषणा TXHIGHPWRLEVEL_LEVEL2			2
#घोषणा TXHIGHPWRLEVEL_BT1			3
#घोषणा TXHIGHPWRLEVEL_BT2			4

#घोषणा DM_TYPE_BYFW				0
#घोषणा DM_TYPE_BYDRIVER			1

#घोषणा TX_POWER_NEAR_FIELD_THRESH_LVL2		74
#घोषणा TX_POWER_NEAR_FIELD_THRESH_LVL1		67
#घोषणा TXPWRTRACK_MAX_IDX			6

/* Dynamic ATC चयन */
#घोषणा ATC_STATUS_OFF				0x0	/* enable */
#घोषणा	ATC_STATUS_ON				0x1	/* disable */
#घोषणा	CFO_THRESHOLD_XTAL			10	/* kHz */
#घोषणा	CFO_THRESHOLD_ATC			80	/* kHz */

/* RSSI Dump Message */
#घोषणा RA_RSSIDUMP				0xcb0
#घोषणा RB_RSSIDUMP				0xcb1
#घोषणा RS1_RXEVMDUMP				0xcb2
#घोषणा RS2_RXEVMDUMP				0xcb3
#घोषणा RA_RXSNRDUMP				0xcb4
#घोषणा RB_RXSNRDUMP				0xcb5
#घोषणा RA_CFOSHORTDUMP				0xcb6
#घोषणा RB_CFOSHORTDUMP				0xcb8
#घोषणा RA_CFOLONGDUMP				0xcba
#घोषणा RB_CFOLONGDUMP				0xcbc

व्योम rtl92ee_dm_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_dm_watchकरोg(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_dm_ग_लिखो_cck_cca_thres(काष्ठा ieee80211_hw *hw,
				    u8 cur_thres);
व्योम rtl92ee_dm_ग_लिखो_dig(काष्ठा ieee80211_hw *hw, u8 current_igi);
व्योम rtl92ee_dm_init_edca_turbo(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_dm_init_rate_adaptive_mask(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_dm_dynamic_arfb_select(काष्ठा ieee80211_hw *hw,
				    u8 rate, bool collision_state);
#पूर्ण_अगर
