<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL8723E_HAL_BTC_H__
#घोषणा __RTL8723E_HAL_BTC_H__

#समावेश "../wifi.h"
#समावेश "btc.h"
#समावेश "hal_bt_coexist.h"

#घोषणा	BT_TXRX_CNT_THRES_1			1200
#घोषणा	BT_TXRX_CNT_THRES_2			1400
#घोषणा	BT_TXRX_CNT_THRES_3			3000
/* < 1200 */
#घोषणा	BT_TXRX_CNT_LEVEL_0			0
/* >= 1200 && < 1400 */
#घोषणा	BT_TXRX_CNT_LEVEL_1			1
/* >= 1400 */
#घोषणा	BT_TXRX_CNT_LEVEL_2			2
#घोषणा	BT_TXRX_CNT_LEVEL_3			3

#घोषणा	BT_COEX_DISABLE			0
#घोषणा	BT_Q_PKT_OFF			0
#घोषणा	BT_Q_PKT_ON			1

#घोषणा	BT_TX_PWR_OFF			0
#घोषणा	BT_TX_PWR_ON			1

/* TDMA mode definition */
#घोषणा	TDMA_2ANT			0
#घोषणा	TDMA_1ANT			1
#घोषणा	TDMA_NAV_OFF			0
#घोषणा	TDMA_NAV_ON			1
#घोषणा	TDMA_DAC_SWING_OFF		0
#घोषणा	TDMA_DAC_SWING_ON		1

/* PTA mode related definition */
#घोषणा	BT_PTA_MODE_OFF		0
#घोषणा	BT_PTA_MODE_ON		1

/* Penalty Tx Rate Adaptive */
#घोषणा	BT_TX_RATE_ADAPTIVE_NORMAL	0
#घोषणा	BT_TX_RATE_ADAPTIVE_LOW_PENALTY	1

/* RF Corner */
#घोषणा	BT_RF_RX_LPF_CORNER_RESUME	0
#घोषणा	BT_RF_RX_LPF_CORNER_SHRINK	1

#घोषणा C2H_EVT_HOST_CLOSE		0x00
#घोषणा C2H_EVT_FW_CLOSE		0xFF

क्रमागत bt_traffic_mode अणु
	BT_MOTOR_EXT_BE = 0x00,
	BT_MOTOR_EXT_GUL = 0x01,
	BT_MOTOR_EXT_GUB = 0x02,
	BT_MOTOR_EXT_GULB = 0x03
पूर्ण;

क्रमागत bt_traffic_mode_profile अणु
	BT_PROखाता_NONE,
	BT_PROखाता_A2DP,
	BT_PROखाता_PAN,
	BT_PROखाता_HID,
	BT_PROखाता_SCO
पूर्ण;

/*
क्रमागत hci_ext_bt_operation अणु
	HCI_BT_OP_NONE = 0x0,
	HCI_BT_OP_INQUIRE_START	= 0x1,
	HCI_BT_OP_INQUIRE_FINISH = 0x2,
	HCI_BT_OP_PAGING_START = 0x3,
	HCI_BT_OP_PAGING_SUCCESS = 0x4,
	HCI_BT_OP_PAGING_UNSUCCESS = 0x5,
	HCI_BT_OP_PAIRING_START = 0x6,
	HCI_BT_OP_PAIRING_FINISH = 0x7,
	HCI_BT_OP_BT_DEV_ENABLE = 0x8,
	HCI_BT_OP_BT_DEV_DISABLE = 0x9,
	HCI_BT_OP_MAX,
पूर्ण;
*/

क्रमागत bt_spec अणु
	BT_SPEC_1_0_b = 0x00,
	BT_SPEC_1_1 = 0x01,
	BT_SPEC_1_2 = 0x02,
	BT_SPEC_2_0_EDR = 0x03,
	BT_SPEC_2_1_EDR = 0x04,
	BT_SPEC_3_0_HS = 0x05,
	BT_SPEC_4_0 = 0x06
पूर्ण;

काष्ठा c2h_evt_hdr अणु
	u8 cmd_id;
	u8 cmd_len;
	u8 cmd_seq;
पूर्ण;

क्रमागत bt_state अणु
	BT_INFO_STATE_DISABLED = 0,
	BT_INFO_STATE_NO_CONNECTION = 1,
	BT_INFO_STATE_CONNECT_IDLE = 2,
	BT_INFO_STATE_INQ_OR_PAG = 3,
	BT_INFO_STATE_ACL_ONLY_BUSY = 4,
	BT_INFO_STATE_SCO_ONLY_BUSY = 5,
	BT_INFO_STATE_ACL_SCO_BUSY = 6,
	BT_INFO_STATE_HID_BUSY = 7,
	BT_INFO_STATE_HID_SCO_BUSY = 8,
	BT_INFO_STATE_MAX = 7
पूर्ण;

क्रमागत rtl8723e_c2h_evt_v0 अणु
	C2H_V0_DBG = 0,
	C2H_V0_TSF = 1,
	C2H_V0_AP_RPT_RSP = 2,
	/* The FW notअगरy the report of the specअगरic tx packet. */
	C2H_V0_CCX_TX_RPT = 3,
	C2H_V0_BT_RSSI = 4,
	C2H_V0_BT_OP_MODE = 5,
	C2H_V0_HW_INFO_EXCH = 10,
	C2H_V0_C2H_H2C_TEST = 11,
	C2H_V0_BT_INFO = 12,
	MAX_C2HEVENT
पूर्ण;

व्योम rtl8723e_dm_bt_fw_coex_all_off_8723a(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_dm_bt_sw_coex_all_off_8723a(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_dm_bt_hw_coex_all_off_8723a(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_dm_bt_coexist_8723(काष्ठा ieee80211_hw *hw);
व्योम rtl8723e_dm_bt_set_bt_dm(काष्ठा ieee80211_hw *hw,
			      काष्ठा btdm_8723 *p_btdm);
व्योम rtl_8723e_c2h_command_handle(काष्ठा ieee80211_hw *hw);
व्योम rtl_8723e_bt_wअगरi_media_status_notअगरy(काष्ठा ieee80211_hw *hw,
					bool mstatus);
व्योम rtl8723e_dm_bt_turn_off_bt_coexist_beक्रमe_enter_lps(
				काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर
