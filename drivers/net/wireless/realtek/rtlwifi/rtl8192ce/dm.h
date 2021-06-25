<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित	__RTL92C_DM_H__
#घोषणा __RTL92C_DM_H__

#घोषणा HAL_DM_DIG_DISABLE			BIT(0)
#घोषणा HAL_DM_HIPWR_DISABLE			BIT(1)

#घोषणा OFDM_TABLE_LENGTH			37
#घोषणा CCK_TABLE_LENGTH			33

#घोषणा OFDM_TABLE_SIZE				37
#घोषणा CCK_TABLE_SIZE				33

#घोषणा BW_AUTO_SWITCH_HIGH_LOW			25
#घोषणा BW_AUTO_SWITCH_LOW_HIGH			30

#घोषणा DM_DIG_FA_UPPER				0x32
#घोषणा DM_DIG_FA_LOWER				0x20
#घोषणा DM_DIG_FA_TH0				0x20
#घोषणा DM_DIG_FA_TH1				0x100
#घोषणा DM_DIG_FA_TH2				0x200

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

व्योम rtl92c_dm_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_dm_watchकरोg(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_dm_ग_लिखो_dig(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_dm_init_edca_turbo(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_dm_check_txघातer_tracking(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_dm_init_rate_adaptive_mask(काष्ठा ieee80211_hw *hw);
व्योम rtl92c_dm_rf_saving(काष्ठा ieee80211_hw *hw, u8 bक्रमce_in_normal);
व्योम rtl92c_dm_bt_coexist(काष्ठा ieee80211_hw *hw);
व्योम rtl92ce_dm_dynamic_txघातer(काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर
