<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL92C_RF_H__
#घोषणा __RTL92C_RF_H__

#घोषणा RF6052_MAX_TX_PWR		0x3F
#घोषणा RF6052_MAX_PATH			2

व्योम rtl92ce_phy_rf6052_set_bandwidth(काष्ठा ieee80211_hw *hw, u8 bandwidth);
व्योम rtl92ce_phy_rf6052_set_cck_txघातer(काष्ठा ieee80211_hw *hw,
					u8 *pघातerlevel);
व्योम rtl92ce_phy_rf6052_set_ofdm_txघातer(काष्ठा ieee80211_hw *hw,
					 u8 *pघातerlevel, u8 channel);
bool rtl92ce_phy_rf6052_config(काष्ठा ieee80211_hw *hw);
#पूर्ण_अगर
