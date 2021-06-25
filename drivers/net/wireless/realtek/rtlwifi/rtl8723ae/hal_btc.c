<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "hal_btc.h"
#समावेश "../pci.h"
#समावेश "phy.h"
#समावेश "fw.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "../rtl8723com/phy_common.h"

अटल काष्ठा bt_coexist_8723 hal_coex_8723;

व्योम rtl8723e_dm_bt_turn_off_bt_coexist_beक्रमe_enter_lps(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	अगर (!rtlpriv->btcoexist.bt_coexistence)
		वापस;

	अगर (ppsc->inactiveps) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BT][DM], Before enter IPS, turn off all Coexist DM\n");
		rtlpriv->btcoexist.cstate = 0;
		rtlpriv->btcoexist.previous_state = 0;
		rtlpriv->btcoexist.cstate_h = 0;
		rtlpriv->btcoexist.previous_state_h = 0;
		rtl8723e_btdm_coex_all_off(hw);
	पूर्ण
पूर्ण

अटल क्रमागत rt_media_status mgnt_link_status_query(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	क्रमागत rt_media_status    m_status = RT_MEDIA_DISCONNECT;
	u8 bibss = (mac->opmode == NL80211_IFTYPE_ADHOC) ? 1 : 0;
	अगर (bibss || rtlpriv->mac80211.link_state >= MAC80211_LINKED)
		m_status = RT_MEDIA_CONNECT;

	वापस m_status;
पूर्ण

व्योम rtl_8723e_bt_wअगरi_media_status_notअगरy(काष्ठा ieee80211_hw *hw,
						bool mstatus)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 h2c_parameter[3] = अणु0पूर्ण;
	u8 chnl;

	अगर (!rtlpriv->btcoexist.bt_coexistence)
		वापस;

	अगर (RT_MEDIA_CONNECT == mstatus)
		h2c_parameter[0] = 0x1; /* 0: disconnected, 1:connected */
	अन्यथा
		h2c_parameter[0] = 0x0;

	अगर (mgnt_link_status_query(hw))	अणु
		chnl = rtlphy->current_channel;
		h2c_parameter[1] = chnl;
	पूर्ण

	अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40)
		h2c_parameter[2] = 0x30;
	अन्यथा
		h2c_parameter[2] = 0x20;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], FW write 0x19=0x%x\n",
		h2c_parameter[0] << 16 | h2c_parameter[1] << 8 |
		h2c_parameter[2]);

	rtl8723e_fill_h2c_cmd(hw, 0x19, 3, h2c_parameter);
पूर्ण

अटल bool rtl8723e_dm_bt_is_wअगरi_busy(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अगर (rtlpriv->link_info.busytraffic ||
		rtlpriv->link_info.rx_busy_traffic ||
		rtlpriv->link_info.tx_busy_traffic)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_fw_3a(काष्ठा ieee80211_hw *hw,
				     u8 byte1, u8 byte2, u8 byte3, u8 byte4,
				     u8 byte5)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[5];

	h2c_parameter[0] = byte1;
	h2c_parameter[1] = byte2;
	h2c_parameter[2] = byte3;
	h2c_parameter[3] = byte4;
	h2c_parameter[4] = byte5;
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], FW write 0x3a(4bytes)=0x%x%8x\n",
		h2c_parameter[0], h2c_parameter[1]<<24 |
		h2c_parameter[2]<<16 | h2c_parameter[3]<<8 |
		h2c_parameter[4]);
	rtl8723e_fill_h2c_cmd(hw, 0x3a, 5, h2c_parameter);
पूर्ण

अटल bool rtl8723e_dm_bt_need_to_dec_bt_pwr(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (mgnt_link_status_query(hw) == RT_MEDIA_CONNECT) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"Need to decrease bt power\n");
		rtlpriv->btcoexist.cstate |=
		BT_COEX_STATE_DEC_BT_POWER;
		वापस true;
	पूर्ण

	rtlpriv->btcoexist.cstate &= ~BT_COEX_STATE_DEC_BT_POWER;
	वापस false;
पूर्ण

अटल bool rtl8723e_dm_bt_is_same_coexist_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर ((rtlpriv->btcoexist.previous_state ==
	     rtlpriv->btcoexist.cstate) &&
	    (rtlpriv->btcoexist.previous_state_h ==
	     rtlpriv->btcoexist.cstate_h)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[DM][BT], Coexist state do not change!!\n");
		वापस true;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[DM][BT], Coexist state changed!!\n");
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_coex_table(काष्ठा ieee80211_hw *hw,
					  u32 val_0x6c0, u32 val_0x6c8,
					  u32 val_0x6cc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"set coex table, set 0x6c0=0x%x\n", val_0x6c0);
	rtl_ग_लिखो_dword(rtlpriv, 0x6c0, val_0x6c0);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"set coex table, set 0x6c8=0x%x\n", val_0x6c8);
	rtl_ग_लिखो_dword(rtlpriv, 0x6c8, val_0x6c8);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"set coex table, set 0x6cc=0x%x\n", val_0x6cc);
	rtl_ग_लिखो_byte(rtlpriv, 0x6cc, val_0x6cc);
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_hw_pta_mode(काष्ठा ieee80211_hw *hw, bool b_mode)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (BT_PTA_MODE_ON == b_mode) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE, "PTA mode on\n");
		/*  Enable GPIO 0/1/2/3/8 pins क्रम bt */
		rtl_ग_लिखो_byte(rtlpriv, 0x40, 0x20);
		rtlpriv->btcoexist.hw_coexist_all_off = false;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE, "PTA mode off\n");
		rtl_ग_लिखो_byte(rtlpriv, 0x40, 0x0);
	पूर्ण
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_sw_rf_rx_lpf_corner(काष्ठा ieee80211_hw *hw,
						   u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (BT_RF_RX_LPF_CORNER_SHRINK == type) अणु
		/* Shrink RF Rx LPF corner, 0x1e[7:4]=1111 ==> [11:4] */
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"Shrink RF Rx LPF corner!!\n");
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A, 0x1e,
					0xfffff, 0xf0ff7);
		rtlpriv->btcoexist.sw_coexist_all_off = false;
	पूर्ण अन्यथा अगर (BT_RF_RX_LPF_CORNER_RESUME == type) अणु
		/*Resume RF Rx LPF corner*/
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"Resume RF Rx LPF corner!!\n");
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A, 0x1e, 0xfffff,
					rtlpriv->btcoexist.bt_rfreg_origin_1e);
	पूर्ण
पूर्ण

अटल व्योम dm_bt_set_sw_penalty_tx_rate_adapt(काष्ठा ieee80211_hw *hw,
					       u8 ra_type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp_u1;

	पंचांगp_u1 = rtl_पढ़ो_byte(rtlpriv, 0x4fd);
	पंचांगp_u1 |= BIT(0);
	अगर (BT_TX_RATE_ADAPTIVE_LOW_PENALTY == ra_type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"Tx rate adaptive, set low penalty!!\n");
		पंचांगp_u1 &= ~BIT(2);
		rtlpriv->btcoexist.sw_coexist_all_off = false;
	पूर्ण अन्यथा अगर (BT_TX_RATE_ADAPTIVE_NORMAL == ra_type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"Tx rate adaptive, set normal!!\n");
		पंचांगp_u1 |= BIT(2);
	पूर्ण

	rtl_ग_लिखो_byte(rtlpriv, 0x4fd, पंचांगp_u1);
पूर्ण

अटल व्योम rtl8723e_dm_bt_btdm_काष्ठाure_reload(काष्ठा ieee80211_hw *hw,
						 काष्ठा btdm_8723 *btdm)
अणु
	btdm->all_off = false;
	btdm->agc_table_en = false;
	btdm->adc_back_off_on = false;
	btdm->b2_ant_hid_en = false;
	btdm->low_penalty_rate_adaptive = false;
	btdm->rf_rx_lpf_shrink = false;
	btdm->reject_aggre_pkt = false;

	btdm->tdma_on = false;
	btdm->tdma_ant = TDMA_2ANT;
	btdm->tdma_nav = TDMA_NAV_OFF;
	btdm->tdma_dac_swing = TDMA_DAC_SWING_OFF;
	btdm->fw_dac_swing_lvl = 0x20;

	btdm->tra_tdma_on = false;
	btdm->tra_tdma_ant = TDMA_2ANT;
	btdm->tra_tdma_nav = TDMA_NAV_OFF;
	btdm->ignore_wlan_act = false;

	btdm->ps_tdma_on = false;
	btdm->ps_tdma_byte[0] = 0x0;
	btdm->ps_tdma_byte[1] = 0x0;
	btdm->ps_tdma_byte[2] = 0x0;
	btdm->ps_tdma_byte[3] = 0x8;
	btdm->ps_tdma_byte[4] = 0x0;

	btdm->pta_on = true;
	btdm->val_0x6c0 = 0x5a5aaaaa;
	btdm->val_0x6c8 = 0xcc;
	btdm->val_0x6cc = 0x3;

	btdm->sw_dac_swing_on = false;
	btdm->sw_dac_swing_lvl = 0xc0;
	btdm->wlan_act_hi = 0x20;
	btdm->wlan_act_lo = 0x10;
	btdm->bt_retry_index = 2;

	btdm->dec_bt_pwr = false;
पूर्ण

अटल व्योम rtl8723e_dm_bt_btdm_काष्ठाure_reload_all_off(काष्ठा ieee80211_hw *hw,
							 काष्ठा btdm_8723 *btdm)
अणु
	rtl8723e_dm_bt_btdm_काष्ठाure_reload(hw, btdm);
	btdm->all_off = true;
	btdm->pta_on = false;
	btdm->wlan_act_hi = 0x10;
पूर्ण

अटल bool rtl8723e_dm_bt_is_2_ant_common_action(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा btdm_8723 btdm8723;
	bool b_common = false;

	rtl8723e_dm_bt_btdm_काष्ठाure_reload(hw, &btdm8723);

	अगर (!rtl8723e_dm_bt_is_wअगरi_busy(hw) &&
	    !rtlpriv->btcoexist.bt_busy) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"Wifi idle + Bt idle, bt coex mechanism always off!!\n");
		rtl8723e_dm_bt_btdm_काष्ठाure_reload_all_off(hw, &btdm8723);
		b_common = true;
	पूर्ण अन्यथा अगर (rtl8723e_dm_bt_is_wअगरi_busy(hw) &&
		   !rtlpriv->btcoexist.bt_busy) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"Wifi non-idle + Bt disabled/idle!!\n");
		btdm8723.low_penalty_rate_adaptive = true;
		btdm8723.rf_rx_lpf_shrink = false;
		btdm8723.reject_aggre_pkt = false;

		/* sw mechanism */
		btdm8723.agc_table_en = false;
		btdm8723.adc_back_off_on = false;
		btdm8723.sw_dac_swing_on = false;

		btdm8723.pta_on = true;
		btdm8723.val_0x6c0 = 0x5a5aaaaa;
		btdm8723.val_0x6c8 = 0xcccc;
		btdm8723.val_0x6cc = 0x3;

		btdm8723.tdma_on = false;
		btdm8723.tdma_dac_swing = TDMA_DAC_SWING_OFF;
		btdm8723.b2_ant_hid_en = false;

		b_common = true;
	पूर्ण अन्यथा अगर (rtlpriv->btcoexist.bt_busy) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"Bt non-idle!\n");
		अगर (mgnt_link_status_query(hw) == RT_MEDIA_CONNECT) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi connection exist\n");
			b_common = false;
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"No Wifi connection!\n");
			btdm8723.rf_rx_lpf_shrink = true;
			btdm8723.low_penalty_rate_adaptive = false;
			btdm8723.reject_aggre_pkt = false;

			/* sw mechanism */
			btdm8723.agc_table_en = false;
			btdm8723.adc_back_off_on = false;
			btdm8723.sw_dac_swing_on = false;

			btdm8723.pta_on = true;
			btdm8723.val_0x6c0 = 0x55555555;
			btdm8723.val_0x6c8 = 0x0000ffff;
			btdm8723.val_0x6cc = 0x3;

			btdm8723.tdma_on = false;
			btdm8723.tdma_dac_swing = TDMA_DAC_SWING_OFF;
			btdm8723.b2_ant_hid_en = false;

			b_common = true;
		पूर्ण
	पूर्ण

	अगर (rtl8723e_dm_bt_need_to_dec_bt_pwr(hw))
		btdm8723.dec_bt_pwr = true;

	अगर (b_common)
		rtlpriv->btcoexist.cstate |=
			BT_COEX_STATE_BTINFO_COMMON;

	अगर (b_common && rtl8723e_dm_bt_is_coexist_state_changed(hw))
		rtl8723e_dm_bt_set_bt_dm(hw, &btdm8723);

	वापस b_common;
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_sw_full_समय_dac_swing(
		काष्ठा ieee80211_hw *hw,
		bool sw_dac_swing_on,
		u32 sw_dac_swing_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (sw_dac_swing_on) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], SwDacSwing = 0x%x\n", sw_dac_swing_lvl);
		rtl8723_phy_set_bb_reg(hw, 0x880, 0xff000000,
				       sw_dac_swing_lvl);
		rtlpriv->btcoexist.sw_coexist_all_off = false;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], SwDacSwing Off!\n");
		rtl8723_phy_set_bb_reg(hw, 0x880, 0xff000000, 0xc0);
	पूर्ण
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_fw_dec_bt_pwr(
		काष्ठा ieee80211_hw *hw, bool dec_bt_pwr)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[1] = अणु0पूर्ण;

	h2c_parameter[0] = 0;

	अगर (dec_bt_pwr) अणु
		h2c_parameter[0] |= BIT(1);
		rtlpriv->btcoexist.fw_coexist_all_off = false;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], decrease Bt Power : %s, write 0x21=0x%x\n",
		(dec_bt_pwr ? "Yes!!" : "No!!"), h2c_parameter[0]);

	rtl8723e_fill_h2c_cmd(hw, 0x21, 1, h2c_parameter);
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_fw_2_ant_hid(काष्ठा ieee80211_hw *hw,
					    bool b_enable, bool b_dac_swing_on)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[1] = अणु0पूर्ण;

	अगर (b_enable) अणु
		h2c_parameter[0] |= BIT(0);
		rtlpriv->btcoexist.fw_coexist_all_off = false;
	पूर्ण
	अगर (b_dac_swing_on)
		h2c_parameter[0] |= BIT(1); /* Dac Swing शेष enable */

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], turn 2-Ant+HID mode %s, DACSwing:%s, write 0x15=0x%x\n",
		(b_enable ? "ON!!" : "OFF!!"), (b_dac_swing_on ? "ON" : "OFF"),
		h2c_parameter[0]);

	rtl8723e_fill_h2c_cmd(hw, 0x15, 1, h2c_parameter);
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_fw_tdma_ctrl(काष्ठा ieee80211_hw *hw,
					    bool b_enable, u8 ant_num,
					    u8 nav_en, u8 dac_swing_en)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[1] = अणु0पूर्ण;
	u8 h2c_parameter1[1] = अणु0पूर्ण;

	h2c_parameter[0] = 0;
	h2c_parameter1[0] = 0;

	अगर (b_enable) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], set BT PTA update manager to trigger update!!\n");
		h2c_parameter1[0] |= BIT(0);

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], turn TDMA mode ON!!\n");
		h2c_parameter[0] |= BIT(0);		/* function enable */
		अगर (TDMA_1ANT == ant_num) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], TDMA_1ANT\n");
			h2c_parameter[0] |= BIT(1);
		पूर्ण अन्यथा अगर (TDMA_2ANT == ant_num) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], TDMA_2ANT\n");
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], Unknown Ant\n");
		पूर्ण

		अगर (TDMA_NAV_OFF == nav_en) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], TDMA_NAV_OFF\n");
		पूर्ण अन्यथा अगर (TDMA_NAV_ON == nav_en) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], TDMA_NAV_ON\n");
			h2c_parameter[0] |= BIT(2);
		पूर्ण

		अगर (TDMA_DAC_SWING_OFF == dac_swing_en) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], TDMA_DAC_SWING_OFF\n");
		पूर्ण अन्यथा अगर (TDMA_DAC_SWING_ON == dac_swing_en) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], TDMA_DAC_SWING_ON\n");
			h2c_parameter[0] |= BIT(4);
		पूर्ण
		rtlpriv->btcoexist.fw_coexist_all_off = false;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], set BT PTA update manager to no update!!\n");
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], turn TDMA mode OFF!!\n");
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], FW2AntTDMA, write 0x26=0x%x\n",
		h2c_parameter1[0]);
	rtl8723e_fill_h2c_cmd(hw, 0x26, 1, h2c_parameter1);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], FW2AntTDMA, write 0x14=0x%x\n",
		h2c_parameter[0]);
	rtl8723e_fill_h2c_cmd(hw, 0x14, 1, h2c_parameter);
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_fw_ignore_wlan_act(काष्ठा ieee80211_hw *hw,
						  bool b_enable)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[1] = अणु0पूर्ण;

	अगर (b_enable) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], BT Ignore Wlan_Act !!\n");
		h2c_parameter[0] |= BIT(0);		/* function enable */
		rtlpriv->btcoexist.fw_coexist_all_off = false;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], BT don't ignore Wlan_Act !!\n");
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], set FW for BT Ignore Wlan_Act, write 0x25=0x%x\n",
		h2c_parameter[0]);

	rtl8723e_fill_h2c_cmd(hw, 0x25, 1, h2c_parameter);
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_fw_tra_tdma_ctrl(काष्ठा ieee80211_hw *hw,
						bool b_enable, u8 ant_num,
						u8 nav_en)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	u8 h2c_parameter[2] = अणु0पूर्ण;

	/* Only 8723 B cut should करो this */
	अगर (IS_VENDOR_8723_A_CUT(rtlhal->version)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], not 8723B cut, don't set Traditional TDMA!!\n");
		वापस;
	पूर्ण

	अगर (b_enable) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], turn TTDMA mode ON!!\n");
		h2c_parameter[0] |= BIT(0);	/* function enable */
		अगर (TDMA_1ANT == ant_num) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], TTDMA_1ANT\n");
			h2c_parameter[0] |= BIT(1);
		पूर्ण अन्यथा अगर (TDMA_2ANT == ant_num) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], TTDMA_2ANT\n");
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], Unknown Ant\n");
		पूर्ण

		अगर (TDMA_NAV_OFF == nav_en) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], TTDMA_NAV_OFF\n");
		पूर्ण अन्यथा अगर (TDMA_NAV_ON == nav_en) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[BTCoex], TTDMA_NAV_ON\n");
			h2c_parameter[1] |= BIT(0);
		पूर्ण

		rtlpriv->btcoexist.fw_coexist_all_off = false;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], turn TTDMA mode OFF!!\n");
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], FW Traditional TDMA, write 0x33=0x%x\n",
		h2c_parameter[0] << 8 | h2c_parameter[1]);

	rtl8723e_fill_h2c_cmd(hw, 0x33, 2, h2c_parameter);
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_fw_dac_swing_level(काष्ठा ieee80211_hw *hw,
						  u8 dac_swing_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[1] = अणु0पूर्ण;
	h2c_parameter[0] = dac_swing_lvl;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], Set Dac Swing Level=0x%x\n", dac_swing_lvl);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], write 0x29=0x%x\n", h2c_parameter[0]);

	rtl8723e_fill_h2c_cmd(hw, 0x29, 1, h2c_parameter);
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_fw_bt_hid_info(काष्ठा ieee80211_hw *hw,
					      bool b_enable)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[1] = अणु0पूर्ण;
	h2c_parameter[0] = 0;

	अगर (b_enable) अणु
		h2c_parameter[0] |= BIT(0);
		rtlpriv->btcoexist.fw_coexist_all_off = false;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], Set BT HID information=0x%x\n", b_enable);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], write 0x24=0x%x\n", h2c_parameter[0]);

	rtl8723e_fill_h2c_cmd(hw, 0x24, 1, h2c_parameter);
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_fw_bt_retry_index(काष्ठा ieee80211_hw *hw,
						 u8 retry_index)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[1] = अणु0पूर्ण;
	h2c_parameter[0] = retry_index;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], Set BT Retry Index=%d\n", retry_index);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], write 0x23=0x%x\n", h2c_parameter[0]);

	rtl8723e_fill_h2c_cmd(hw, 0x23, 1, h2c_parameter);
पूर्ण

अटल व्योम rtl8723e_dm_bt_set_fw_wlan_act(काष्ठा ieee80211_hw *hw,
					   u8 wlan_act_hi, u8 wlan_act_lo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter_hi[1] = अणु0पूर्ण;
	u8 h2c_parameter_lo[1] = अणु0पूर्ण;
	h2c_parameter_hi[0] = wlan_act_hi;
	h2c_parameter_lo[0] = wlan_act_lo;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], Set WLAN_ACT Hi:Lo=0x%x/0x%x\n",
		wlan_act_hi, wlan_act_lo);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], write 0x22=0x%x\n", h2c_parameter_hi[0]);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[BTCoex], write 0x11=0x%x\n", h2c_parameter_lo[0]);

	/* WLAN_ACT = High duration, unit:ms */
	rtl8723e_fill_h2c_cmd(hw, 0x22, 1, h2c_parameter_hi);
	/*  WLAN_ACT = Low duration, unit:3*625us */
	rtl8723e_fill_h2c_cmd(hw, 0x11, 1, h2c_parameter_lo);
पूर्ण

व्योम rtl8723e_dm_bt_set_bt_dm(काष्ठा ieee80211_hw *hw,
			      काष्ठा btdm_8723 *btdm)
अणु
	काष्ठा rtl_priv	*rtlpriv = rtl_priv(hw);
	काष्ठा btdm_8723 *btdm_8723 = &hal_coex_8723.btdm;
	u8 i;

	bool fw_current_inpsmode = false;
	bool fw_ps_awake = true;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
					      (u8 *)(&fw_current_inpsmode));
	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FWLPS_RF_ON,
					      (u8 *)(&fw_ps_awake));

	/* check new setting is dअगरferent with the old one, */
	/* अगर all the same, करोn't करो the setting again. */
	अगर (स_भेद(btdm_8723, btdm, माप(काष्ठा btdm_8723)) == 0) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], the same coexist setting, return!!\n");
		वापस;
	पूर्ण अन्यथा अणु	/* save the new coexist setting */
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], UPDATE TO NEW COEX SETTING!!\n");
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new bAllOff=0x%x/ 0x%x\n",
			btdm_8723->all_off, btdm->all_off);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new agc_table_en=0x%x/ 0x%x\n",
			btdm_8723->agc_table_en, btdm->agc_table_en);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new adc_back_off_on=0x%x/ 0x%x\n",
			btdm_8723->adc_back_off_on,
			btdm->adc_back_off_on);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new b2_ant_hid_en=0x%x/ 0x%x\n",
			btdm_8723->b2_ant_hid_en, btdm->b2_ant_hid_en);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new bLowPenaltyRateAdaptive=0x%x/ 0x%x\n",
			btdm_8723->low_penalty_rate_adaptive,
			btdm->low_penalty_rate_adaptive);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new bRfRxLpfShrink=0x%x/ 0x%x\n",
			btdm_8723->rf_rx_lpf_shrink,
			btdm->rf_rx_lpf_shrink);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new bRejectAggrePkt=0x%x/ 0x%x\n",
			btdm_8723->reject_aggre_pkt,
			btdm->reject_aggre_pkt);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new tdma_on=0x%x/ 0x%x\n",
			btdm_8723->tdma_on, btdm->tdma_on);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new tdmaAnt=0x%x/ 0x%x\n",
			btdm_8723->tdma_ant, btdm->tdma_ant);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new tdmaNav=0x%x/ 0x%x\n",
			btdm_8723->tdma_nav, btdm->tdma_nav);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new tdma_dac_swing=0x%x/ 0x%x\n",
			btdm_8723->tdma_dac_swing, btdm->tdma_dac_swing);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new fw_dac_swing_lvl=0x%x/ 0x%x\n",
			btdm_8723->fw_dac_swing_lvl,
			btdm->fw_dac_swing_lvl);

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new bTraTdmaOn=0x%x/ 0x%x\n",
			btdm_8723->tra_tdma_on, btdm->tra_tdma_on);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new traTdmaAnt=0x%x/ 0x%x\n",
			btdm_8723->tra_tdma_ant, btdm->tra_tdma_ant);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new traTdmaNav=0x%x/ 0x%x\n",
			btdm_8723->tra_tdma_nav, btdm->tra_tdma_nav);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new bPsTdmaOn=0x%x/ 0x%x\n",
			btdm_8723->ps_tdma_on, btdm->ps_tdma_on);
		क्रम (i = 0; i < 5; i++) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], original/new psTdmaByte[i]=0x%x/ 0x%x\n",
				btdm_8723->ps_tdma_byte[i],
				btdm->ps_tdma_byte[i]);
		पूर्ण
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new bIgnoreWlanAct=0x%x/ 0x%x\n",
			btdm_8723->ignore_wlan_act,
			btdm->ignore_wlan_act);


		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new bPtaOn=0x%x/ 0x%x\n",
			btdm_8723->pta_on, btdm->pta_on);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new val_0x6c0=0x%x/ 0x%x\n",
			btdm_8723->val_0x6c0, btdm->val_0x6c0);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new val_0x6c8=0x%x/ 0x%x\n",
			btdm_8723->val_0x6c8, btdm->val_0x6c8);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new val_0x6cc=0x%x/ 0x%x\n",
			btdm_8723->val_0x6cc, btdm->val_0x6cc);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new sw_dac_swing_on=0x%x/ 0x%x\n",
			btdm_8723->sw_dac_swing_on,
			btdm->sw_dac_swing_on);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new sw_dac_swing_lvl=0x%x/ 0x%x\n",
			btdm_8723->sw_dac_swing_lvl,
			btdm->sw_dac_swing_lvl);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new wlanActHi=0x%x/ 0x%x\n",
			btdm_8723->wlan_act_hi, btdm->wlan_act_hi);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new wlanActLo=0x%x/ 0x%x\n",
			btdm_8723->wlan_act_lo, btdm->wlan_act_lo);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], original/new btRetryIndex=0x%x/ 0x%x\n",
			btdm_8723->bt_retry_index, btdm->bt_retry_index);

		स_नकल(btdm_8723, btdm, माप(काष्ठा btdm_8723));
	पूर्ण
	/* Here we only consider when Bt Operation
	 * inquiry/paging/pairing is ON
	 * we only need to turn off TDMA
	 */

	अगर (rtlpriv->btcoexist.hold_क्रम_bt_operation) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], set to ignore wlanAct for BT OP!!\n");
		rtl8723e_dm_bt_set_fw_ignore_wlan_act(hw, true);
		वापस;
	पूर्ण

	अगर (btdm->all_off) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], disable all coexist mechanism !!\n");
		rtl8723e_btdm_coex_all_off(hw);
		वापस;
	पूर्ण

	rtl8723e_dm_bt_reject_ap_aggregated_packet(hw, btdm->reject_aggre_pkt);

	अगर (btdm->low_penalty_rate_adaptive)
		dm_bt_set_sw_penalty_tx_rate_adapt(hw, BT_TX_RATE_ADAPTIVE_LOW_PENALTY);
	अन्यथा
		dm_bt_set_sw_penalty_tx_rate_adapt(hw,
						   BT_TX_RATE_ADAPTIVE_NORMAL);

	अगर (btdm->rf_rx_lpf_shrink)
		rtl8723e_dm_bt_set_sw_rf_rx_lpf_corner(hw,
				BT_RF_RX_LPF_CORNER_SHRINK);
	अन्यथा
		rtl8723e_dm_bt_set_sw_rf_rx_lpf_corner(hw,
				BT_RF_RX_LPF_CORNER_RESUME);

	अगर (btdm->agc_table_en)
		rtl8723e_dm_bt_agc_table(hw, BT_AGCTABLE_ON);
	अन्यथा
		rtl8723e_dm_bt_agc_table(hw, BT_AGCTABLE_OFF);

	अगर (btdm->adc_back_off_on)
		rtl8723e_dm_bt_bb_back_off_level(hw, BT_BB_BACKOFF_ON);
	अन्यथा
		rtl8723e_dm_bt_bb_back_off_level(hw, BT_BB_BACKOFF_OFF);

	rtl8723e_dm_bt_set_fw_bt_retry_index(hw, btdm->bt_retry_index);

	rtl8723e_dm_bt_set_fw_dac_swing_level(hw, btdm->fw_dac_swing_lvl);
	rtl8723e_dm_bt_set_fw_wlan_act(hw, btdm->wlan_act_hi,
				       btdm->wlan_act_lo);

	rtl8723e_dm_bt_set_coex_table(hw, btdm->val_0x6c0,
				      btdm->val_0x6c8, btdm->val_0x6cc);
	rtl8723e_dm_bt_set_hw_pta_mode(hw, btdm->pta_on);

	/* Note: There is a स्थिरraपूर्णांक between TDMA and 2AntHID
	 * Only one of 2AntHid and tdma can be turn on
	 * We should turn off those mechanisms should be turned off first
	 * and then turn on those mechanisms should be turned on.
	*/
	अगर (btdm->b2_ant_hid_en) अणु
		/* turn off tdma */
		rtl8723e_dm_bt_set_fw_tra_tdma_ctrl(hw, btdm->tra_tdma_on,
						    btdm->tra_tdma_ant,
						    btdm->tra_tdma_nav);
		rtl8723e_dm_bt_set_fw_tdma_ctrl(hw, false, btdm->tdma_ant,
						btdm->tdma_nav,
						btdm->tdma_dac_swing);

		/* turn off Pstdma */
		rtl8723e_dm_bt_set_fw_ignore_wlan_act(hw,
						      btdm->ignore_wlan_act);
		/* Antenna control by PTA, 0x870 = 0x300. */
		rtl8723e_dm_bt_set_fw_3a(hw, 0x0, 0x0, 0x0, 0x8, 0x0);

		/* turn on 2AntHid */
		rtl8723e_dm_bt_set_fw_bt_hid_info(hw, true);
		rtl8723e_dm_bt_set_fw_2_ant_hid(hw, true, true);
	पूर्ण अन्यथा अगर (btdm->tdma_on) अणु
		/* turn off 2AntHid */
		rtl8723e_dm_bt_set_fw_bt_hid_info(hw, false);
		rtl8723e_dm_bt_set_fw_2_ant_hid(hw, false, false);

		/* turn off pstdma */
		rtl8723e_dm_bt_set_fw_ignore_wlan_act(hw,
						      btdm->ignore_wlan_act);
		/* Antenna control by PTA, 0x870 = 0x300. */
		rtl8723e_dm_bt_set_fw_3a(hw, 0x0, 0x0, 0x0, 0x8, 0x0);

		/* turn on tdma */
		rtl8723e_dm_bt_set_fw_tra_tdma_ctrl(hw, btdm->tra_tdma_on,
						    btdm->tra_tdma_ant,
						    btdm->tra_tdma_nav);
		rtl8723e_dm_bt_set_fw_tdma_ctrl(hw, true, btdm->tdma_ant,
						btdm->tdma_nav,
						btdm->tdma_dac_swing);
	पूर्ण अन्यथा अगर (btdm->ps_tdma_on) अणु
		/* turn off 2AntHid */
		rtl8723e_dm_bt_set_fw_bt_hid_info(hw, false);
		rtl8723e_dm_bt_set_fw_2_ant_hid(hw, false, false);

		/* turn off tdma */
		rtl8723e_dm_bt_set_fw_tra_tdma_ctrl(hw, btdm->tra_tdma_on,
						    btdm->tra_tdma_ant,
						    btdm->tra_tdma_nav);
		rtl8723e_dm_bt_set_fw_tdma_ctrl(hw, false, btdm->tdma_ant,
						btdm->tdma_nav,
						btdm->tdma_dac_swing);

		/* turn on pstdma */
		rtl8723e_dm_bt_set_fw_ignore_wlan_act(hw,
						      btdm->ignore_wlan_act);
		rtl8723e_dm_bt_set_fw_3a(hw, btdm->ps_tdma_byte[0],
					 btdm->ps_tdma_byte[1],
					 btdm->ps_tdma_byte[2],
					 btdm->ps_tdma_byte[3],
					 btdm->ps_tdma_byte[4]);
	पूर्ण अन्यथा अणु
		/* turn off 2AntHid */
		rtl8723e_dm_bt_set_fw_bt_hid_info(hw, false);
		rtl8723e_dm_bt_set_fw_2_ant_hid(hw, false, false);

		/* turn off tdma */
		rtl8723e_dm_bt_set_fw_tra_tdma_ctrl(hw, btdm->tra_tdma_on,
						    btdm->tra_tdma_ant,
						    btdm->tra_tdma_nav);
		rtl8723e_dm_bt_set_fw_tdma_ctrl(hw, false, btdm->tdma_ant,
						btdm->tdma_nav,
						btdm->tdma_dac_swing);

		/* turn off pstdma */
		rtl8723e_dm_bt_set_fw_ignore_wlan_act(hw,
						btdm->ignore_wlan_act);
		/* Antenna control by PTA, 0x870 = 0x300. */
		rtl8723e_dm_bt_set_fw_3a(hw, 0x0, 0x0, 0x0, 0x8, 0x0);
	पूर्ण

	/* Note:
	 * We should add delay क्रम making sure
	 *	sw DacSwing can be set sucessfully.
	 * because of that rtl8723e_dm_bt_set_fw_2_ant_hid()
	 *	and rtl8723e_dm_bt_set_fw_tdma_ctrl()
	 * will overग_लिखो the reg 0x880.
	*/
	mdelay(30);
	rtl8723e_dm_bt_set_sw_full_समय_dac_swing(hw, btdm->sw_dac_swing_on,
						  btdm->sw_dac_swing_lvl);
	rtl8723e_dm_bt_set_fw_dec_bt_pwr(hw, btdm->dec_bt_pwr);
पूर्ण

/* ============================================================ */
/* बाह्य function start with BTDM_ */
/* ============================================================i
 */
अटल u32 rtl8723e_dm_bt_tx_rx_couter_h(काष्ठा ieee80211_hw *hw)
अणु
	u32	counters = 0;

	counters = hal_coex_8723.high_priority_tx +
			hal_coex_8723.high_priority_rx;
	वापस counters;
पूर्ण

अटल u32 rtl8723e_dm_bt_tx_rx_couter_l(काष्ठा ieee80211_hw *hw)
अणु
	u32 counters = 0;

	counters = hal_coex_8723.low_priority_tx +
			hal_coex_8723.low_priority_rx;
	वापस counters;
पूर्ण

अटल u8 rtl8723e_dm_bt_bt_tx_rx_counter_level(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32	bt_tx_rx_cnt = 0;
	u8	bt_tx_rx_cnt_lvl = 0;

	bt_tx_rx_cnt = rtl8723e_dm_bt_tx_rx_couter_h(hw)
				+ rtl8723e_dm_bt_tx_rx_couter_l(hw);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT TxRx Counters = %d\n", bt_tx_rx_cnt);

	rtlpriv->btcoexist.cstate_h &= ~
		 (BT_COEX_STATE_BT_CNT_LEVEL_0 | BT_COEX_STATE_BT_CNT_LEVEL_1|
		  BT_COEX_STATE_BT_CNT_LEVEL_2);

	अगर (bt_tx_rx_cnt >= BT_TXRX_CNT_THRES_3) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], BT TxRx Counters at level 3\n");
		bt_tx_rx_cnt_lvl = BT_TXRX_CNT_LEVEL_3;
		rtlpriv->btcoexist.cstate_h |=
			BT_COEX_STATE_BT_CNT_LEVEL_3;
	पूर्ण अन्यथा अगर (bt_tx_rx_cnt >= BT_TXRX_CNT_THRES_2) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], BT TxRx Counters at level 2\n");
		bt_tx_rx_cnt_lvl = BT_TXRX_CNT_LEVEL_2;
		rtlpriv->btcoexist.cstate_h |=
			BT_COEX_STATE_BT_CNT_LEVEL_2;
	पूर्ण अन्यथा अगर (bt_tx_rx_cnt >= BT_TXRX_CNT_THRES_1) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], BT TxRx Counters at level 1\n");
		bt_tx_rx_cnt_lvl = BT_TXRX_CNT_LEVEL_1;
		rtlpriv->btcoexist.cstate_h  |=
			BT_COEX_STATE_BT_CNT_LEVEL_1;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], BT TxRx Counters at level 0\n");
		bt_tx_rx_cnt_lvl = BT_TXRX_CNT_LEVEL_0;
		rtlpriv->btcoexist.cstate_h |=
			BT_COEX_STATE_BT_CNT_LEVEL_0;
	पूर्ण
	वापस bt_tx_rx_cnt_lvl;
पूर्ण

अटल व्योम rtl8723e_dm_bt_2_ant_hid_sco_esco(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा btdm_8723 btdm8723;
	u8 bt_rssi_state, bt_rssi_state1;
	u8	bt_tx_rx_cnt_lvl = 0;

	rtl8723e_dm_bt_btdm_काष्ठाure_reload(hw, &btdm8723);

	btdm8723.rf_rx_lpf_shrink = true;
	btdm8723.low_penalty_rate_adaptive = true;
	btdm8723.reject_aggre_pkt = false;

	bt_tx_rx_cnt_lvl = rtl8723e_dm_bt_bt_tx_rx_counter_level(hw);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT TxRx Counters = %d\n", bt_tx_rx_cnt_lvl);

	अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG, "HT40\n");
		/* coex table */
		btdm8723.val_0x6c0 = 0x55555555;
		btdm8723.val_0x6c8 = 0xffff;
		btdm8723.val_0x6cc = 0x3;

		/* sw mechanism */
		btdm8723.agc_table_en = false;
		btdm8723.adc_back_off_on = false;
		btdm8723.sw_dac_swing_on = false;

		/* fw mechanism */
		btdm8723.ps_tdma_on = true;
		अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_2) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT TxRx Counters >= 1400\n");
			btdm8723.ps_tdma_byte[0] = 0xa3;
			btdm8723.ps_tdma_byte[1] = 0x5;
			btdm8723.ps_tdma_byte[2] = 0x5;
			btdm8723.ps_tdma_byte[3] = 0x2;
			btdm8723.ps_tdma_byte[4] = 0x80;
		पूर्ण अन्यथा अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_1) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT TxRx Counters >= 1200 && < 1400\n");
			btdm8723.ps_tdma_byte[0] = 0xa3;
			btdm8723.ps_tdma_byte[1] = 0xa;
			btdm8723.ps_tdma_byte[2] = 0xa;
			btdm8723.ps_tdma_byte[3] = 0x2;
			btdm8723.ps_tdma_byte[4] = 0x80;
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT TxRx Counters < 1200\n");
			btdm8723.ps_tdma_byte[0] = 0xa3;
			btdm8723.ps_tdma_byte[1] = 0xf;
			btdm8723.ps_tdma_byte[2] = 0xf;
			btdm8723.ps_tdma_byte[3] = 0x2;
			btdm8723.ps_tdma_byte[4] = 0x80;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"HT20 or Legacy\n");
		bt_rssi_state =
		  rtl8723e_dm_bt_check_coex_rssi_state(hw, 2, 47, 0);
		bt_rssi_state1 =
		  rtl8723e_dm_bt_check_coex_rssi_state1(hw, 2, 27, 0);

		/* coex table */
		btdm8723.val_0x6c0 = 0x55555555;
		btdm8723.val_0x6c8 = 0xffff;
		btdm8723.val_0x6cc = 0x3;

		/* sw mechanism */
		अगर ((bt_rssi_state == BT_RSSI_STATE_HIGH) ||
			(bt_rssi_state == BT_RSSI_STATE_STAY_HIGH)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi rssi high\n");
			btdm8723.agc_table_en = true;
			btdm8723.adc_back_off_on = true;
			btdm8723.sw_dac_swing_on = false;
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi rssi low\n");
			btdm8723.agc_table_en = false;
			btdm8723.adc_back_off_on = false;
			btdm8723.sw_dac_swing_on = false;
		पूर्ण

		/* fw mechanism */
		btdm8723.ps_tdma_on = true;
		अगर ((bt_rssi_state1 == BT_RSSI_STATE_HIGH) ||
			(bt_rssi_state1 == BT_RSSI_STATE_STAY_HIGH)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi rssi-1 high\n");
			/* only rssi high we need to करो this, */
			/* when rssi low, the value will modअगरied by fw */
			rtl_ग_लिखो_byte(rtlpriv, 0x883, 0x40);
			अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_2) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x83;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_1) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters>= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x83;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x83;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi rssi-1 low\n");
			अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_2) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x2;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_1) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x2;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x2;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rtl8723e_dm_bt_need_to_dec_bt_pwr(hw))
		btdm8723.dec_bt_pwr = true;

	/* Always ignore WlanAct अगर bHid|bSCOBusy|bSCOeSCO */

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT btInqPageStartTime = 0x%x, btTxRxCntLvl = %d\n",
		hal_coex_8723.bt_inq_page_start_समय, bt_tx_rx_cnt_lvl);
	अगर ((hal_coex_8723.bt_inq_page_start_समय) ||
	    (BT_TXRX_CNT_LEVEL_3 == bt_tx_rx_cnt_lvl)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], Set BT inquiry / page scan 0x3a setting\n");
		btdm8723.ps_tdma_on = true;
		btdm8723.ps_tdma_byte[0] = 0xa3;
		btdm8723.ps_tdma_byte[1] = 0x5;
		btdm8723.ps_tdma_byte[2] = 0x5;
		btdm8723.ps_tdma_byte[3] = 0x2;
		btdm8723.ps_tdma_byte[4] = 0x80;
	पूर्ण

	अगर (rtl8723e_dm_bt_is_coexist_state_changed(hw))
		rtl8723e_dm_bt_set_bt_dm(hw, &btdm8723);

पूर्ण

अटल व्योम rtl8723e_dm_bt_2_ant_ftp_a2dp(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा btdm_8723 btdm8723;

	u8 bt_rssi_state, bt_rssi_state1;
	u32 bt_tx_rx_cnt_lvl = 0;

	rtl8723e_dm_bt_btdm_काष्ठाure_reload(hw, &btdm8723);

	btdm8723.rf_rx_lpf_shrink = true;
	btdm8723.low_penalty_rate_adaptive = true;
	btdm8723.reject_aggre_pkt = false;

	bt_tx_rx_cnt_lvl = rtl8723e_dm_bt_bt_tx_rx_counter_level(hw);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT TxRx Counters = %d\n", bt_tx_rx_cnt_lvl);

	अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG, "HT40\n");
		bt_rssi_state =
		  rtl8723e_dm_bt_check_coex_rssi_state(hw, 2, 37, 0);

		/* coex table */
		btdm8723.val_0x6c0 = 0x55555555;
		btdm8723.val_0x6c8 = 0xffff;
		btdm8723.val_0x6cc = 0x3;

		/* sw mechanism */
		btdm8723.agc_table_en = false;
		btdm8723.adc_back_off_on = true;
		btdm8723.sw_dac_swing_on = false;

		/* fw mechanism */
		btdm8723.ps_tdma_on = true;
		अगर ((bt_rssi_state == BT_RSSI_STATE_HIGH) ||
			(bt_rssi_state == BT_RSSI_STATE_STAY_HIGH)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi rssi high\n");
			अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_2) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_1) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi rssi low\n");
			अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_2) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अगर (bt_tx_rx_cnt_lvl ==
				BT_TXRX_CNT_LEVEL_1) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"HT20 or Legacy\n");
		bt_rssi_state =
		  rtl8723e_dm_bt_check_coex_rssi_state(hw, 2, 47, 0);
		bt_rssi_state1 =
		  rtl8723e_dm_bt_check_coex_rssi_state1(hw, 2, 27, 0);

		/* coex table */
		btdm8723.val_0x6c0 = 0x55555555;
		btdm8723.val_0x6c8 = 0xffff;
		btdm8723.val_0x6cc = 0x3;

		/* sw mechanism */
		अगर ((bt_rssi_state == BT_RSSI_STATE_HIGH) ||
			(bt_rssi_state == BT_RSSI_STATE_STAY_HIGH)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi rssi high\n");
			btdm8723.agc_table_en = true;
			btdm8723.adc_back_off_on = true;
			btdm8723.sw_dac_swing_on = false;
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi rssi low\n");
			btdm8723.agc_table_en = false;
			btdm8723.adc_back_off_on = false;
			btdm8723.sw_dac_swing_on = false;
		पूर्ण

		/* fw mechanism */
		btdm8723.ps_tdma_on = true;
		अगर ((bt_rssi_state1 == BT_RSSI_STATE_HIGH) ||
			(bt_rssi_state1 == BT_RSSI_STATE_STAY_HIGH)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi rssi-1 high\n");
			/* only rssi high we need to करो this, */
			/* when rssi low, the value will modअगरied by fw */
			rtl_ग_लिखो_byte(rtlpriv, 0x883, 0x40);
			अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_2) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_1) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x81;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"Wifi rssi-1 low\n");
			अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_2) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0x5;
				btdm8723.ps_tdma_byte[2] = 0x5;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अगर (bt_tx_rx_cnt_lvl == BT_TXRX_CNT_LEVEL_1) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters >= 1200 && < 1400\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xa;
				btdm8723.ps_tdma_byte[2] = 0xa;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BT TxRx Counters < 1200\n");
				btdm8723.ps_tdma_byte[0] = 0xa3;
				btdm8723.ps_tdma_byte[1] = 0xf;
				btdm8723.ps_tdma_byte[2] = 0xf;
				btdm8723.ps_tdma_byte[3] = 0x0;
				btdm8723.ps_tdma_byte[4] = 0x80;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rtl8723e_dm_bt_need_to_dec_bt_pwr(hw))
		btdm8723.dec_bt_pwr = true;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT btInqPageStartTime = 0x%x, btTxRxCntLvl = %d\n",
		hal_coex_8723.bt_inq_page_start_समय, bt_tx_rx_cnt_lvl);

	अगर ((hal_coex_8723.bt_inq_page_start_समय) ||
	    (BT_TXRX_CNT_LEVEL_3 == bt_tx_rx_cnt_lvl)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], Set BT inquiry / page scan 0x3a setting\n");
		btdm8723.ps_tdma_on = true;
		btdm8723.ps_tdma_byte[0] = 0xa3;
		btdm8723.ps_tdma_byte[1] = 0x5;
		btdm8723.ps_tdma_byte[2] = 0x5;
		btdm8723.ps_tdma_byte[3] = 0x83;
		btdm8723.ps_tdma_byte[4] = 0x80;
	पूर्ण

	अगर (rtl8723e_dm_bt_is_coexist_state_changed(hw))
		rtl8723e_dm_bt_set_bt_dm(hw, &btdm8723);

पूर्ण

अटल व्योम rtl8723e_dm_bt_inq_page_monitor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 cur_समय;

	cur_समय = jअगरfies;
	अगर (hal_coex_8723.c2h_bt_inquiry_page) अणु
		/* bt inquiry or page is started. */
		अगर (hal_coex_8723.bt_inq_page_start_समय == 0) अणु
			rtlpriv->btcoexist.cstate  |=
			BT_COEX_STATE_BT_INQ_PAGE;
			hal_coex_8723.bt_inq_page_start_समय = cur_समय;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT Inquiry/page is started at time : 0x%x\n",
				hal_coex_8723.bt_inq_page_start_समय);
		पूर्ण
	पूर्ण
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex], BT Inquiry/page started time : 0x%x, cur_time : 0x%x\n",
		hal_coex_8723.bt_inq_page_start_समय, cur_समय);

	अगर (hal_coex_8723.bt_inq_page_start_समय) अणु
		अगर ((((दीर्घ)cur_समय -
			(दीर्घ)hal_coex_8723.bt_inq_page_start_समय) / HZ)
			>= 10) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
				"[BTCoex], BT Inquiry/page >= 10sec!!!\n");
			hal_coex_8723.bt_inq_page_start_समय = 0;
			rtlpriv->btcoexist.cstate &=
				~BT_COEX_STATE_BT_INQ_PAGE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl8723e_dm_bt_reset_action_profile_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->btcoexist.cstate &= ~
		(BT_COEX_STATE_PROखाता_HID | BT_COEX_STATE_PROखाता_A2DP|
		BT_COEX_STATE_PROखाता_PAN | BT_COEX_STATE_PROखाता_SCO);

	rtlpriv->btcoexist.cstate &= ~
		(BT_COEX_STATE_BTINFO_COMMON |
		BT_COEX_STATE_BTINFO_B_HID_SCOESCO|
		BT_COEX_STATE_BTINFO_B_FTP_A2DP);
पूर्ण

अटल व्योम _rtl8723e_dm_bt_coexist_2_ant(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_info_original;
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"[BTCoex] Get bt info by fw!!\n");

	_rtl8723_dm_bt_check_wअगरi_state(hw);

	अगर (hal_coex_8723.c2h_bt_info_req_sent) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex] c2h for bt_info not rcvd yet!!\n");
	पूर्ण

	bt_info_original = hal_coex_8723.c2h_bt_info_original;

	/* when bt inquiry or page scan, we have to set h2c 0x25 */
	/* ignore wlanact क्रम continuous 4x2secs */
	rtl8723e_dm_bt_inq_page_monitor(hw);
	rtl8723e_dm_bt_reset_action_profile_state(hw);

	अगर (rtl8723e_dm_bt_is_2_ant_common_action(hw)) अणु
		rtlpriv->btcoexist.bt_profile_हाल = BT_COEX_MECH_COMMON;
		rtlpriv->btcoexist.bt_profile_action = BT_COEX_MECH_COMMON;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"Action 2-Ant common.\n");
	पूर्ण अन्यथा अणु
		अगर ((bt_info_original & BTINFO_B_HID) ||
			(bt_info_original & BTINFO_B_SCO_BUSY) ||
			(bt_info_original & BTINFO_B_SCO_ESCO)) अणु
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_BTINFO_B_HID_SCOESCO;
				rtlpriv->btcoexist.bt_profile_हाल =
					BT_COEX_MECH_HID_SCO_ESCO;
				rtlpriv->btcoexist.bt_profile_action =
					BT_COEX_MECH_HID_SCO_ESCO;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BTInfo: bHid|bSCOBusy|bSCOeSCO\n");
				rtl8723e_dm_bt_2_ant_hid_sco_esco(hw);
		पूर्ण अन्यथा अगर ((bt_info_original & BTINFO_B_FTP) ||
				(bt_info_original & BTINFO_B_A2DP)) अणु
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_BTINFO_B_FTP_A2DP;
				rtlpriv->btcoexist.bt_profile_हाल =
					BT_COEX_MECH_FTP_A2DP;
				rtlpriv->btcoexist.bt_profile_action =
					BT_COEX_MECH_FTP_A2DP;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"BTInfo: bFTP|bA2DP\n");
				rtl8723e_dm_bt_2_ant_ftp_a2dp(hw);
		पूर्ण अन्यथा अणु
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_BTINFO_B_HID_SCOESCO;
				rtlpriv->btcoexist.bt_profile_हाल =
					BT_COEX_MECH_NONE;
				rtlpriv->btcoexist.bt_profile_action =
					BT_COEX_MECH_NONE;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
					"[BTCoex], BTInfo: undefined case!!!!\n");
				rtl8723e_dm_bt_2_ant_hid_sco_esco(hw);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl8723e_dm_bt_coexist_1_ant(काष्ठा ieee80211_hw *hw)
अणु
	वापस;
पूर्ण

व्योम rtl8723e_dm_bt_hw_coex_all_off_8723a(काष्ठा ieee80211_hw *hw)
अणु
	rtl8723e_dm_bt_set_coex_table(hw, 0x5a5aaaaa, 0xcc, 0x3);
	rtl8723e_dm_bt_set_hw_pta_mode(hw, true);
पूर्ण

व्योम rtl8723e_dm_bt_fw_coex_all_off_8723a(काष्ठा ieee80211_hw *hw)
अणु
	rtl8723e_dm_bt_set_fw_ignore_wlan_act(hw, false);
	rtl8723e_dm_bt_set_fw_3a(hw, 0x0, 0x0, 0x0, 0x8, 0x0);
	rtl8723e_dm_bt_set_fw_2_ant_hid(hw, false, false);
	rtl8723e_dm_bt_set_fw_tra_tdma_ctrl(hw, false, TDMA_2ANT,
					    TDMA_NAV_OFF);
	rtl8723e_dm_bt_set_fw_tdma_ctrl(hw, false, TDMA_2ANT, TDMA_NAV_OFF,
					TDMA_DAC_SWING_OFF);
	rtl8723e_dm_bt_set_fw_dac_swing_level(hw, 0);
	rtl8723e_dm_bt_set_fw_bt_hid_info(hw, false);
	rtl8723e_dm_bt_set_fw_bt_retry_index(hw, 2);
	rtl8723e_dm_bt_set_fw_wlan_act(hw, 0x10, 0x10);
	rtl8723e_dm_bt_set_fw_dec_bt_pwr(hw, false);
पूर्ण

व्योम rtl8723e_dm_bt_sw_coex_all_off_8723a(काष्ठा ieee80211_hw *hw)
अणु
	rtl8723e_dm_bt_agc_table(hw, BT_AGCTABLE_OFF);
	rtl8723e_dm_bt_bb_back_off_level(hw, BT_BB_BACKOFF_OFF);
	rtl8723e_dm_bt_reject_ap_aggregated_packet(hw, false);

	dm_bt_set_sw_penalty_tx_rate_adapt(hw, BT_TX_RATE_ADAPTIVE_NORMAL);
	rtl8723e_dm_bt_set_sw_rf_rx_lpf_corner(hw, BT_RF_RX_LPF_CORNER_RESUME);
	rtl8723e_dm_bt_set_sw_full_समय_dac_swing(hw, false, 0xc0);
पूर्ण

अटल व्योम rtl8723e_dm_bt_query_bt_inक्रमmation(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[1] = अणु0पूर्ण;

	hal_coex_8723.c2h_bt_info_req_sent = true;

	h2c_parameter[0] |=  BIT(0);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"Query Bt information, write 0x38=0x%x\n", h2c_parameter[0]);

	rtl8723e_fill_h2c_cmd(hw, 0x38, 1, h2c_parameter);
पूर्ण

अटल व्योम rtl8723e_dm_bt_bt_hw_counters_monitor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 reg_hp_tx_rx, reg_lp_tx_rx, u32_पंचांगp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0, reg_lp_tx = 0, reg_lp_rx = 0;

	reg_hp_tx_rx = REG_HIGH_PRIORITY_TXRX;
	reg_lp_tx_rx = REG_LOW_PRIORITY_TXRX;

	u32_पंचांगp = rtl_पढ़ो_dword(rtlpriv, reg_hp_tx_rx);
	reg_hp_tx = u32_पंचांगp & MASKLWORD;
	reg_hp_rx = (u32_पंचांगp & MASKHWORD)>>16;

	u32_पंचांगp = rtl_पढ़ो_dword(rtlpriv, reg_lp_tx_rx);
	reg_lp_tx = u32_पंचांगp & MASKLWORD;
	reg_lp_rx = (u32_पंचांगp & MASKHWORD)>>16;

	अगर (rtlpriv->btcoexist.lps_counter > 1) अणु
		reg_hp_tx %= rtlpriv->btcoexist.lps_counter;
		reg_hp_rx %= rtlpriv->btcoexist.lps_counter;
		reg_lp_tx %= rtlpriv->btcoexist.lps_counter;
		reg_lp_rx %= rtlpriv->btcoexist.lps_counter;
	पूर्ण

	hal_coex_8723.high_priority_tx = reg_hp_tx;
	hal_coex_8723.high_priority_rx = reg_hp_rx;
	hal_coex_8723.low_priority_tx = reg_lp_tx;
	hal_coex_8723.low_priority_rx = reg_lp_rx;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"High Priority Tx/Rx (reg 0x%x)=%x(%d)/%x(%d)\n",
		reg_hp_tx_rx, reg_hp_tx, reg_hp_tx, reg_hp_rx, reg_hp_rx);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"Low Priority Tx/Rx (reg 0x%x)=%x(%d)/%x(%d)\n",
		reg_lp_tx_rx, reg_lp_tx, reg_lp_tx, reg_lp_rx, reg_lp_rx);
	rtlpriv->btcoexist.lps_counter = 0;
	/* rtl_ग_लिखो_byte(rtlpriv, 0x76e, 0xc); */
पूर्ण

अटल व्योम rtl8723e_dm_bt_bt_enable_disable_check(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	bool bt_alअगरe = true;

	अगर (hal_coex_8723.high_priority_tx == 0 &&
	    hal_coex_8723.high_priority_rx == 0 &&
	    hal_coex_8723.low_priority_tx == 0 &&
	    hal_coex_8723.low_priority_rx == 0) अणु
		bt_alअगरe = false;
	पूर्ण
	अगर (hal_coex_8723.high_priority_tx == 0xeaea &&
	    hal_coex_8723.high_priority_rx == 0xeaea &&
	    hal_coex_8723.low_priority_tx == 0xeaea &&
	    hal_coex_8723.low_priority_rx == 0xeaea) अणु
		bt_alअगरe = false;
	पूर्ण
	अगर (hal_coex_8723.high_priority_tx == 0xffff &&
	    hal_coex_8723.high_priority_rx == 0xffff &&
	    hal_coex_8723.low_priority_tx == 0xffff &&
	    hal_coex_8723.low_priority_rx == 0xffff) अणु
		bt_alअगरe = false;
	पूर्ण
	अगर (bt_alअगरe) अणु
		rtlpriv->btcoexist.bt_active_zero_cnt = 0;
		rtlpriv->btcoexist.cur_bt_disabled = false;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"8723A BT is enabled !!\n");
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.bt_active_zero_cnt++;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"8723A bt all counters=0, %d times!!\n",
			rtlpriv->btcoexist.bt_active_zero_cnt);
		अगर (rtlpriv->btcoexist.bt_active_zero_cnt >= 2) अणु
			rtlpriv->btcoexist.cur_bt_disabled = true;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"8723A BT is disabled !!\n");
		पूर्ण
	पूर्ण
	अगर (rtlpriv->btcoexist.pre_bt_disabled !=
		rtlpriv->btcoexist.cur_bt_disabled) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST,
			DBG_TRACE, "8723A BT is from %s to %s!!\n",
			(rtlpriv->btcoexist.pre_bt_disabled ?
				"disabled" : "enabled"),
			(rtlpriv->btcoexist.cur_bt_disabled ?
				"disabled" : "enabled"));
		rtlpriv->btcoexist.pre_bt_disabled
			= rtlpriv->btcoexist.cur_bt_disabled;
	पूर्ण
पूर्ण


व्योम rtl8723e_dm_bt_coexist_8723(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl8723e_dm_bt_query_bt_inक्रमmation(hw);
	rtl8723e_dm_bt_bt_hw_counters_monitor(hw);
	rtl8723e_dm_bt_bt_enable_disable_check(hw);

	अगर (rtlpriv->btcoexist.bt_ant_num == ANT_X2) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], 2 Ant mechanism\n");
		_rtl8723e_dm_bt_coexist_2_ant(hw);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BTCoex], 1 Ant mechanism\n");
		_rtl8723e_dm_bt_coexist_1_ant(hw);
	पूर्ण

	अगर (!rtl8723e_dm_bt_is_same_coexist_state(hw)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTCoex], Coexist State[bitMap] change from 0x%x%8x to 0x%x%8x\n",
			rtlpriv->btcoexist.previous_state_h,
			rtlpriv->btcoexist.previous_state,
			rtlpriv->btcoexist.cstate_h,
			rtlpriv->btcoexist.cstate);
		rtlpriv->btcoexist.previous_state
			= rtlpriv->btcoexist.cstate;
		rtlpriv->btcoexist.previous_state_h
			= rtlpriv->btcoexist.cstate_h;
	पूर्ण
पूर्ण

अटल व्योम rtl8723e_dm_bt_parse_bt_info(काष्ठा ieee80211_hw *hw,
					 u8 *पंचांगp_buf, u8 len)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_info;
	u8 i;

	hal_coex_8723.c2h_bt_info_req_sent = false;
	hal_coex_8723.bt_retry_cnt = 0;
	क्रम (i = 0; i < len; i++) अणु
		अगर (i == 0)
			hal_coex_8723.c2h_bt_info_original = पंचांगp_buf[i];
		अन्यथा अगर (i == 1)
			hal_coex_8723.bt_retry_cnt = पंचांगp_buf[i];
		अगर (i == len-1)
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"0x%2x]", पंचांगp_buf[i]);
		अन्यथा
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"0x%2x, ", पंचांगp_buf[i]);

	पूर्ण
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"BT info bt_info (Data)= 0x%x\n",
			hal_coex_8723.c2h_bt_info_original);
	bt_info = hal_coex_8723.c2h_bt_info_original;

	अगर (bt_info & BIT(2))
		hal_coex_8723.c2h_bt_inquiry_page = true;
	अन्यथा
		hal_coex_8723.c2h_bt_inquiry_page = false;


	अगर (bt_info & BTINFO_B_CONNECTION) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTC2H], BTInfo: bConnect=true\n");
		rtlpriv->btcoexist.bt_busy = true;
		rtlpriv->btcoexist.cstate &= ~BT_COEX_STATE_BT_IDLE;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"[BTC2H], BTInfo: bConnect=false\n");
		rtlpriv->btcoexist.bt_busy = false;
		rtlpriv->btcoexist.cstate |= BT_COEX_STATE_BT_IDLE;
	पूर्ण
पूर्ण
व्योम rtl_8723e_c2h_command_handle(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा c2h_evt_hdr c2h_event;
	u8 *pपंचांगp_buf = शून्य;
	u8 index = 0;
	u8 u1b_पंचांगp = 0;
	स_रखो(&c2h_event, 0, माप(c2h_event));
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_C2HEVT_MSG_NORMAL);
	rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
		"&&&&&&: REG_C2HEVT_MSG_NORMAL is 0x%x\n", u1b_पंचांगp);
	c2h_event.cmd_id = u1b_पंचांगp & 0xF;
	c2h_event.cmd_len = (u1b_पंचांगp & 0xF0) >> 4;
	c2h_event.cmd_seq = rtl_पढ़ो_byte(rtlpriv, REG_C2HEVT_MSG_NORMAL + 1);
	rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG,
		"cmd_id: %d, cmd_len: %d, cmd_seq: %d\n",
		c2h_event.cmd_id, c2h_event.cmd_len, c2h_event.cmd_seq);
	u1b_पंचांगp = rtl_पढ़ो_byte(rtlpriv, 0x01AF);
	अगर (u1b_पंचांगp == C2H_EVT_HOST_CLOSE) अणु
		वापस;
	पूर्ण अन्यथा अगर (u1b_पंचांगp != C2H_EVT_FW_CLOSE) अणु
		rtl_ग_लिखो_byte(rtlpriv, 0x1AF, 0x00);
		वापस;
	पूर्ण
	pपंचांगp_buf = kzalloc(c2h_event.cmd_len, GFP_KERNEL);
	अगर (pपंचांगp_buf == शून्य) अणु
		rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE,
			"malloc cmd buf failed\n");
		वापस;
	पूर्ण

	/* Read the content */
	क्रम (index = 0; index < c2h_event.cmd_len; index++)
		pपंचांगp_buf[index] = rtl_पढ़ो_byte(rtlpriv,
					REG_C2HEVT_MSG_NORMAL + 2 + index);


	चयन (c2h_event.cmd_id) अणु
	हाल C2H_V0_BT_RSSI:
			अवरोध;

	हाल C2H_V0_BT_OP_MODE:
			अवरोध;

	हाल C2H_V0_BT_INFO:
		rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE,
			"BT info Byte[0] (ID) is 0x%x\n",
			c2h_event.cmd_id);
		rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE,
			"BT info Byte[1] (Seq) is 0x%x\n",
			c2h_event.cmd_seq);
		rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE,
			"BT info Byte[2] (Data)= 0x%x\n", pपंचांगp_buf[0]);

		rtl8723e_dm_bt_parse_bt_info(hw, pपंचांगp_buf, c2h_event.cmd_len);

		अगर (rtlpriv->cfg->ops->get_btc_status())
			rtlpriv->btcoexist.btc_ops->btc_periodical(rtlpriv);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	kमुक्त(pपंचांगp_buf);

	rtl_ग_लिखो_byte(rtlpriv, 0x01AF, C2H_EVT_HOST_CLOSE);
पूर्ण
