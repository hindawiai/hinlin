<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL8723E_HAL_BT_COEXIST_H__
#घोषणा __RTL8723E_HAL_BT_COEXIST_H__

#समावेश "../wifi.h"

/* The reg define is क्रम 8723 */
#घोषणा	REG_HIGH_PRIORITY_TXRX			0x770
#घोषणा	REG_LOW_PRIORITY_TXRX			0x774

#घोषणा BT_FW_COEX_THRESH_TOL			6
#घोषणा BT_FW_COEX_THRESH_20			20
#घोषणा BT_FW_COEX_THRESH_23			23
#घोषणा BT_FW_COEX_THRESH_25			25
#घोषणा BT_FW_COEX_THRESH_30			30
#घोषणा BT_FW_COEX_THRESH_35			35
#घोषणा BT_FW_COEX_THRESH_40			40
#घोषणा BT_FW_COEX_THRESH_45			45
#घोषणा BT_FW_COEX_THRESH_47			47
#घोषणा BT_FW_COEX_THRESH_50			50
#घोषणा BT_FW_COEX_THRESH_55			55

#घोषणा BT_COEX_STATE_BT30			BIT(0)
#घोषणा BT_COEX_STATE_WIFI_HT20			BIT(1)
#घोषणा BT_COEX_STATE_WIFI_HT40			BIT(2)
#घोषणा BT_COEX_STATE_WIFI_LEGACY		BIT(3)

#घोषणा BT_COEX_STATE_WIFI_RSSI_LOW		BIT(4)
#घोषणा BT_COEX_STATE_WIFI_RSSI_MEDIUM	BIT(5)
#घोषणा BT_COEX_STATE_WIFI_RSSI_HIGH	BIT(6)
#घोषणा BT_COEX_STATE_DEC_BT_POWER		BIT(7)

#घोषणा BT_COEX_STATE_WIFI_IDLE			BIT(8)
#घोषणा BT_COEX_STATE_WIFI_UPLINK		BIT(9)
#घोषणा BT_COEX_STATE_WIFI_DOWNLINK		BIT(10)

#घोषणा BT_COEX_STATE_BT_INQ_PAGE		BIT(11)
#घोषणा BT_COEX_STATE_BT_IDLE			BIT(12)
#घोषणा BT_COEX_STATE_BT_UPLINK			BIT(13)
#घोषणा BT_COEX_STATE_BT_DOWNLINK		BIT(14)

#घोषणा BT_COEX_STATE_HOLD_FOR_BT_OPERATION	BIT(15)
#घोषणा BT_COEX_STATE_BT_RSSI_LOW		BIT(19)

#घोषणा BT_COEX_STATE_PROखाता_HID		BIT(20)
#घोषणा BT_COEX_STATE_PROखाता_A2DP		BIT(21)
#घोषणा BT_COEX_STATE_PROखाता_PAN		BIT(22)
#घोषणा BT_COEX_STATE_PROखाता_SCO		BIT(23)

#घोषणा BT_COEX_STATE_WIFI_RSSI_1_LOW		BIT(24)
#घोषणा BT_COEX_STATE_WIFI_RSSI_1_MEDIUM	BIT(25)
#घोषणा BT_COEX_STATE_WIFI_RSSI_1_HIGH		BIT(26)

#घोषणा BT_COEX_STATE_BTINFO_COMMON			BIT(30)
#घोषणा BT_COEX_STATE_BTINFO_B_HID_SCOESCO	BIT(31)
#घोषणा BT_COEX_STATE_BTINFO_B_FTP_A2DP		BIT(29)

#घोषणा BT_COEX_STATE_BT_CNT_LEVEL_0		BIT(0)
#घोषणा BT_COEX_STATE_BT_CNT_LEVEL_1		BIT(1)
#घोषणा BT_COEX_STATE_BT_CNT_LEVEL_2		BIT(2)
#घोषणा BT_COEX_STATE_BT_CNT_LEVEL_3		BIT(3)

#घोषणा BT_RSSI_STATE_HIGH			0
#घोषणा BT_RSSI_STATE_MEDIUM			1
#घोषणा BT_RSSI_STATE_LOW			2
#घोषणा BT_RSSI_STATE_STAY_HIGH			3
#घोषणा BT_RSSI_STATE_STAY_MEDIUM		4
#घोषणा BT_RSSI_STATE_STAY_LOW			5

#घोषणा	BT_AGCTABLE_OFF				0
#घोषणा	BT_AGCTABLE_ON				1
#घोषणा	BT_BB_BACKOFF_OFF			0
#घोषणा	BT_BB_BACKOFF_ON			1
#घोषणा	BT_FW_NAV_OFF				0
#घोषणा	BT_FW_NAV_ON				1

#घोषणा	BT_COEX_MECH_NONE			0
#घोषणा	BT_COEX_MECH_SCO			1
#घोषणा	BT_COEX_MECH_HID			2
#घोषणा	BT_COEX_MECH_A2DP			3
#घोषणा	BT_COEX_MECH_PAN			4
#घोषणा	BT_COEX_MECH_HID_A2DP			5
#घोषणा	BT_COEX_MECH_HID_PAN			6
#घोषणा	BT_COEX_MECH_PAN_A2DP			7
#घोषणा	BT_COEX_MECH_HID_SCO_ESCO		8
#घोषणा	BT_COEX_MECH_FTP_A2DP			9
#घोषणा	BT_COEX_MECH_COMMON			10
#घोषणा	BT_COEX_MECH_MAX			11

#घोषणा	BT_DBG_PROखाता_NONE			0
#घोषणा	BT_DBG_PROखाता_SCO			1
#घोषणा	BT_DBG_PROखाता_HID			2
#घोषणा	BT_DBG_PROखाता_A2DP			3
#घोषणा	BT_DBG_PROखाता_PAN			4
#घोषणा	BT_DBG_PROखाता_HID_A2DP			5
#घोषणा	BT_DBG_PROखाता_HID_PAN			6
#घोषणा	BT_DBG_PROखाता_PAN_A2DP			7
#घोषणा	BT_DBG_PROखाता_MAX			9

#घोषणा	BTINFO_B_FTP				BIT(7)
#घोषणा	BTINFO_B_A2DP				BIT(6)
#घोषणा	BTINFO_B_HID				BIT(5)
#घोषणा	BTINFO_B_SCO_BUSY			BIT(4)
#घोषणा	BTINFO_B_ACL_BUSY			BIT(3)
#घोषणा	BTINFO_B_INQ_PAGE			BIT(2)
#घोषणा	BTINFO_B_SCO_ESCO			BIT(1)
#घोषणा	BTINFO_B_CONNECTION			BIT(0)

व्योम rtl8723e_btdm_coex_all_off(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_dm_bt_fw_coex_all_off(काष्ठा ieee80211_hw *hw);

व्योम rtl8723e_dm_bt_sw_coex_all_off(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_dm_bt_hw_coex_all_off(काष्ठा ieee80211_hw *hw);
दीर्घ rtl8723e_dm_bt_get_rx_ss(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_dm_bt_balance(काष्ठा ieee80211_hw *hw,
			    bool balance_on, u8 ms0, u8 ms1);
व्योम rtl8723e_dm_bt_agc_table(काष्ठा ieee80211_hw *hw, u8 tyep);
व्योम rtl8723e_dm_bt_bb_back_off_level(काष्ठा ieee80211_hw *hw, u8 type);
u8 rtl8723e_dm_bt_check_coex_rssi_state(काष्ठा ieee80211_hw *hw,
					u8 level_num, u8 rssi_thresh,
					u8 rssi_thresh1);
u8 rtl8723e_dm_bt_check_coex_rssi_state1(काष्ठा ieee80211_hw *hw,
					 u8 level_num, u8 rssi_thresh,
					 u8 rssi_thresh1);
व्योम _rtl8723_dm_bt_check_wअगरi_state(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_dm_bt_reject_ap_aggregated_packet(काष्ठा ieee80211_hw *hw,
						bool b_reject);
bool rtl8723e_dm_bt_is_coexist_state_changed(काष्ठा ieee80211_hw *hw);
bool rtl8723e_dm_bt_is_wअगरi_up_link(काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर
