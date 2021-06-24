<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित	__RTL92C_DM_H__
#घोषणा __RTL92C_DM_H__

#घोषणा HAL_DM_DIG_DISABLE			BIT(0)
#घोषणा HAL_DM_HIPWR_DISABLE			BIT(1)

#घोषणा OFDM_TABLE_LENGTH			37
#घोषणा OFDM_TABLE_SIZE_92D			43
#घोषणा CCK_TABLE_LENGTH			33

#घोषणा CCK_TABLE_SIZE				33

#घोषणा BW_AUTO_SWITCH_HIGH_LOW			25
#घोषणा BW_AUTO_SWITCH_LOW_HIGH			30

#घोषणा DM_DIG_FA_UPPER				0x32
#घोषणा DM_DIG_FA_LOWER				0x20
#घोषणा DM_DIG_FA_TH0				0x100
#घोषणा DM_DIG_FA_TH1				0x400
#घोषणा DM_DIG_FA_TH2				0x600

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
#घोषणा INDEX_MAPPING_NUM			13

काष्ठा swat अणु
	u8 failure_cnt;
	u8 try_flag;
	u8 stop_trying;
	दीर्घ pre_rssi;
	दीर्घ trying_threshold;
	u8 cur_antenna;
	u8 pre_antenna;
पूर्ण;

क्रमागत tag_dynamic_init_gain_operation_type_definition अणु
	DIG_TYPE_THRESH_HIGH = 0,
	DIG_TYPE_THRESH_LOW = 1,
	DIG_TYPE_BACKOFF = 2,
	DIG_TYPE_RX_GAIN_MIN = 3,
	DIG_TYPE_RX_GAIN_MAX = 4,
	DIG_TYPE_ENABLE = 5,
	DIG_TYPE_DISABLE = 6,
	DIG_OP_TYPE_MAX
पूर्ण;

क्रमागत dm_1r_cca अणु
	CCA_1R = 0,
	CCA_2R = 1,
	CCA_MAX = 2,
पूर्ण;

क्रमागत dm_rf अणु
	RF_SAVE = 0,
	RF_NORMAL = 1,
	RF_MAX = 2,
पूर्ण;

क्रमागत dm_sw_ant_चयन अणु
	ANS_ANTENNA_B = 1,
	ANS_ANTENNA_A = 2,
	ANS_ANTENNA_MAX = 3,
पूर्ण;

व्योम rtl92d_dm_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_dm_watchकरोg(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_dm_init_edca_turbo(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_dm_ग_लिखो_dig(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_dm_check_txघातer_tracking_thermal_meter(काष्ठा ieee80211_hw *hw);
व्योम rtl92d_dm_init_rate_adaptive_mask(काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर
