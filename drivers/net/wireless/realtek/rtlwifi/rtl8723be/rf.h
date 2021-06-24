<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित __RTL8723BE_RF_H__
#घोषणा __RTL8723BE_RF_H__

#घोषणा RF6052_MAX_TX_PWR		0x3F

व्योम rtl8723be_phy_rf6052_set_bandwidth(काष्ठा ieee80211_hw *hw,
					u8 bandwidth);
व्योम rtl8723be_phy_rf6052_set_cck_txघातer(काष्ठा ieee80211_hw *hw,
					  u8 *pघातerlevel);
व्योम rtl8723be_phy_rf6052_set_ofdm_txघातer(काष्ठा ieee80211_hw *hw,
					   u8 *pघातerlevel_ofdm,
					   u8 *pघातerlevel_bw20,
					   u8 *pघातerlevel_bw40,
					   u8 channel);
bool rtl8723be_phy_rf6052_config(काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर
