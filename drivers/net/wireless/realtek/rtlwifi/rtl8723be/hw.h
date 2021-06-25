<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित __RTL8723BE_HW_H__
#घोषणा __RTL8723BE_HW_H__

व्योम rtl8723be_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
व्योम rtl8723be_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw);

व्योम rtl8723be_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				    काष्ठा rtl_पूर्णांक *पूर्णांक_vec);
पूर्णांक rtl8723be_hw_init(काष्ठा ieee80211_hw *hw);
व्योम rtl8723be_card_disable(काष्ठा ieee80211_hw *hw);
व्योम rtl8723be_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
व्योम rtl8723be_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
पूर्णांक rtl8723be_set_network_type(काष्ठा ieee80211_hw *hw,
			       क्रमागत nl80211_अगरtype type);
व्योम rtl8723be_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid);
व्योम rtl8723be_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci);
व्योम rtl8723be_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw);
व्योम rtl8723be_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw);
व्योम rtl8723be_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
				     u32 add_msr, u32 rm_msr);
व्योम rtl8723be_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
व्योम rtl8723be_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_sta *sta,
				   u8 rssi_level, bool update_bw);
व्योम rtl8723be_update_channel_access_setting(काष्ठा ieee80211_hw *hw);
bool rtl8723be_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid);
व्योम rtl8723be_enable_hw_security_config(काष्ठा ieee80211_hw *hw);
व्योम rtl8723be_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
		       u8 *p_macaddr, bool is_group, u8 enc_algo,
		       bool is_wepkey, bool clear_all);
व्योम rtl8723be_पढ़ो_bt_coexist_info_from_hwpg(काष्ठा ieee80211_hw *hw,
					      bool स्वतःload_fail, u8 *hwinfo);
व्योम rtl8723be_bt_reg_init(काष्ठा ieee80211_hw *hw);
व्योम rtl8723be_bt_hw_init(काष्ठा ieee80211_hw *hw);
व्योम rtl8723be_suspend(काष्ठा ieee80211_hw *hw);
व्योम rtl8723be_resume(काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर
