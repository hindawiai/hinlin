<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2010  Realtek Corporation.*/

#अगर_अघोषित __RTL8821AE_HW_H__
#घोषणा __RTL8821AE_HW_H__

व्योम rtl8821ae_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
व्योम rtl8821ae_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw);

व्योम rtl8821ae_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				    काष्ठा rtl_पूर्णांक *पूर्णांक_vec);
पूर्णांक rtl8821ae_hw_init(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_card_disable(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
पूर्णांक rtl8821ae_set_network_type(काष्ठा ieee80211_hw *hw,
			       क्रमागत nl80211_अगरtype type);
व्योम rtl8821ae_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid);
व्योम rtl8821ae_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci);
व्योम rtl8821ae_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
				     u32 add_msr, u32 rm_msr);
व्योम rtl8821ae_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
व्योम rtl8821ae_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_sta *sta,
				   u8 rssi_level, bool update_bw);
व्योम rtl8821ae_update_channel_access_setting(काष्ठा ieee80211_hw *hw);
bool rtl8821ae_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid);
व्योम rtl8821ae_enable_hw_security_config(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
		       u8 *p_macaddr, bool is_group, u8 enc_algo,
		       bool is_wepkey, bool clear_all);

व्योम rtl8821ae_bt_reg_init(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_bt_hw_init(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_suspend(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_resume(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_allow_all_destaddr(काष्ठा ieee80211_hw *hw,
				  bool allow_all_da,
				  bool ग_लिखो_पूर्णांकo_reg);
व्योम _rtl8821ae_stop_tx_beacon(काष्ठा ieee80211_hw *hw);
व्योम _rtl8821ae_resume_tx_beacon(काष्ठा ieee80211_hw *hw);
व्योम rtl8821ae_add_wowlan_pattern(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_wow_pattern *rtl_pattern,
				  u8 index);

#पूर्ण_अगर
