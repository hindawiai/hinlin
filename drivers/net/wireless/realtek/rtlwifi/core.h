<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL_CORE_H__
#घोषणा __RTL_CORE_H__

#घोषणा RTL_SUPPORTED_FILTERS		\
	(FIF_ALLMULTI | FIF_CONTROL | \
	FIF_OTHER_BSS | \
	FIF_FCSFAIL | \
	FIF_BCN_PRBRESP_PROMISC)

#घोषणा DM_DIG_THRESH_HIGH		40
#घोषणा DM_DIG_THRESH_LOW		35
#घोषणा DM_FALSEALARM_THRESH_LOW	400
#घोषणा DM_FALSEALARM_THRESH_HIGH	1000

#घोषणा DM_DIG_MAX			0x3e
#घोषणा DM_DIG_MIN			0x1e
#घोषणा DM_DIG_MAX_AP			0x32
#घोषणा DM_DIG_BACKOFF_MAX		12
#घोषणा DM_DIG_BACKOFF_MIN		-4
#घोषणा DM_DIG_BACKOFF_DEFAULT		10

क्रमागत cck_packet_detection_threshold अणु
	CCK_PD_STAGE_LOWRSSI = 0,
	CCK_PD_STAGE_HIGHRSSI = 1,
	CCK_FA_STAGE_LOW = 2,
	CCK_FA_STAGE_HIGH = 3,
	CCK_PD_STAGE_MAX = 4,
पूर्ण;

क्रमागत dm_dig_ext_port_alg_e अणु
	DIG_EXT_PORT_STAGE_0 = 0,
	DIG_EXT_PORT_STAGE_1 = 1,
	DIG_EXT_PORT_STAGE_2 = 2,
	DIG_EXT_PORT_STAGE_3 = 3,
	DIG_EXT_PORT_STAGE_MAX = 4,
पूर्ण;

क्रमागत dm_dig_connect_e अणु
	DIG_STA_DISCONNECT,
	DIG_STA_CONNECT,
	DIG_STA_BEFORE_CONNECT,
	DIG_MULTISTA_DISCONNECT,
	DIG_MULTISTA_CONNECT,
	DIG_AP_DISCONNECT,
	DIG_AP_CONNECT,
	DIG_AP_ADD_STATION,
	DIG_CONNECT_MAX
पूर्ण;

बाह्य स्थिर काष्ठा ieee80211_ops rtl_ops;
व्योम rtl_fw_cb(स्थिर काष्ठा firmware *firmware, व्योम *context);
व्योम rtl_wowlan_fw_cb(स्थिर काष्ठा firmware *firmware, व्योम *context);
व्योम rtl_addr_delay(u32 addr);
व्योम rtl_rfreg_delay(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath, u32 addr,
		     u32 mask, u32 data);
व्योम rtl_bb_delay(काष्ठा ieee80211_hw *hw, u32 addr, u32 data);
bool rtl_cmd_send_packet(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb);
bool rtl_btc_status_false(व्योम);
व्योम rtl_dm_diginit(काष्ठा ieee80211_hw *hw, u32 cur_igval);
व्योम rtl_update_beacon_work_callback(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर
