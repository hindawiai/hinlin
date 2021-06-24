<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92CE_HW_H__
#घोषणा __RTL92CE_HW_H__

अटल अंतरभूत u8 rtl92c_get_chnl_group(u8 chnl)
अणु
	u8 group;

	अगर (chnl < 3)
		group = 0;
	अन्यथा अगर (chnl < 9)
		group = 1;
	अन्यथा
		group = 2;
	वापस group;
पूर्ण

व्योम rtl92ce_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
व्योम rtl92ce_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw);
व्योम rtl92ce_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_पूर्णांक *पूर्णांक_vec);
पूर्णांक rtl92ce_hw_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92ce_card_disable(काष्ठा ieee80211_hw *hw);
व्योम rtl92ce_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
व्योम rtl92ce_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
पूर्णांक rtl92ce_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type);
व्योम rtl92ce_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid);
व्योम rtl92ce_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci);
व्योम rtl92ce_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw);
व्योम rtl92ce_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw);
व्योम rtl92ce_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
				   u32 add_msr, u32 rm_msr);
व्योम rtl92ce_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
व्योम rtl92ce_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_sta *sta, u8 rssi_level,
				 bool update_bw);
व्योम rtl92ce_update_channel_access_setting(काष्ठा ieee80211_hw *hw);
bool rtl92ce_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid);
व्योम rtl92ce_enable_hw_security_config(काष्ठा ieee80211_hw *hw);
व्योम rtl92ce_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
		     u8 *p_macaddr, bool is_group, u8 enc_algo,
		     bool is_wepkey, bool clear_all);

व्योम rtl8192ce_पढ़ो_bt_coexist_info_from_hwpg(काष्ठा ieee80211_hw *hw,
			bool स्वतःload_fail, u8 *hwinfo);
व्योम rtl8192ce_bt_reg_init(काष्ठा ieee80211_hw *hw);
व्योम rtl8192ce_bt_hw_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92ce_suspend(काष्ठा ieee80211_hw *hw);
व्योम rtl92ce_resume(काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर
