<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../base.h"
#समावेश "../pci.h"
#समावेश "../core.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "dm.h"
#समावेश "../rtl8723com/dm_common.h"
#समावेश "fw.h"
#समावेश "hal_btc.h"

अटल u8 rtl8723e_dm_initial_gain_min_pwdb(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);
	दीर्घ rssi_val_min = 0;

	अगर (mac->link_state == MAC80211_LINKED &&
	    mac->opmode == NL80211_IFTYPE_STATION &&
	    rtlpriv->link_info.bcn_rx_inperiod == 0)
		वापस 0;

	अगर ((dm_digtable->curmultista_cstate == DIG_MULTISTA_CONNECT) &&
	    (dm_digtable->cursta_cstate == DIG_STA_CONNECT)) अणु
		अगर (rtlpriv->dm.entry_min_undec_sm_pwdb != 0)
			rssi_val_min =
			    (rtlpriv->dm.entry_min_undec_sm_pwdb >
			     rtlpriv->dm.undec_sm_pwdb) ?
			    rtlpriv->dm.undec_sm_pwdb :
			    rtlpriv->dm.entry_min_undec_sm_pwdb;
		अन्यथा
			rssi_val_min = rtlpriv->dm.undec_sm_pwdb;
	पूर्ण अन्यथा अगर (dm_digtable->cursta_cstate == DIG_STA_CONNECT ||
		   dm_digtable->cursta_cstate == DIG_STA_BEFORE_CONNECT) अणु
		rssi_val_min = rtlpriv->dm.undec_sm_pwdb;
	पूर्ण अन्यथा अगर (dm_digtable->curmultista_cstate ==
		DIG_MULTISTA_CONNECT) अणु
		rssi_val_min = rtlpriv->dm.entry_min_undec_sm_pwdb;
	पूर्ण

	वापस (u8) rssi_val_min;
पूर्ण

अटल व्योम rtl8723e_dm_false_alarm_counter_statistics(काष्ठा ieee80211_hw *hw)
अणु
	u32 ret_value;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER1, MASKDWORD);
	falsealm_cnt->cnt_parity_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER2, MASKDWORD);
	falsealm_cnt->cnt_rate_illegal = (ret_value & 0xffff);
	falsealm_cnt->cnt_crc8_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER3, MASKDWORD);
	falsealm_cnt->cnt_mcs_fail = (ret_value & 0xffff);
	falsealm_cnt->cnt_ofdm_fail = falsealm_cnt->cnt_parity_fail +
	    falsealm_cnt->cnt_rate_illegal +
	    falsealm_cnt->cnt_crc8_fail + falsealm_cnt->cnt_mcs_fail;

	rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, BIT(14), 1);
	ret_value = rtl_get_bbreg(hw, RCCK0_FACOUNTERLOWER, MASKBYTE0);
	falsealm_cnt->cnt_cck_fail = ret_value;

	ret_value = rtl_get_bbreg(hw, RCCK0_FACOUNTERUPPER, MASKBYTE3);
	falsealm_cnt->cnt_cck_fail += (ret_value & 0xff) << 8;
	falsealm_cnt->cnt_all = (falsealm_cnt->cnt_parity_fail +
				 falsealm_cnt->cnt_rate_illegal +
				 falsealm_cnt->cnt_crc8_fail +
				 falsealm_cnt->cnt_mcs_fail +
				 falsealm_cnt->cnt_cck_fail);

	rtl_set_bbreg(hw, ROFDM1_LSTF, 0x08000000, 1);
	rtl_set_bbreg(hw, ROFDM1_LSTF, 0x08000000, 0);
	rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, 0x0000c000, 0);
	rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, 0x0000c000, 2);

	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"cnt_parity_fail = %d, cnt_rate_illegal = %d, cnt_crc8_fail = %d, cnt_mcs_fail = %d\n",
		falsealm_cnt->cnt_parity_fail,
		falsealm_cnt->cnt_rate_illegal,
		falsealm_cnt->cnt_crc8_fail, falsealm_cnt->cnt_mcs_fail);

	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"cnt_ofdm_fail = %x, cnt_cck_fail = %x, cnt_all = %x\n",
		falsealm_cnt->cnt_ofdm_fail,
		falsealm_cnt->cnt_cck_fail, falsealm_cnt->cnt_all);
पूर्ण

अटल व्योम rtl92c_dm_ctrl_initgain_by_fa(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	u8 value_igi = dm_digtable->cur_igvalue;

	अगर (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH0)
		value_igi--;
	अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH1)
		value_igi += 0;
	अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH2)
		value_igi++;
	अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all >= DM_DIG_FA_TH2)
		value_igi += 2;
	अगर (value_igi > DM_DIG_FA_UPPER)
		value_igi = DM_DIG_FA_UPPER;
	अन्यथा अगर (value_igi < DM_DIG_FA_LOWER)
		value_igi = DM_DIG_FA_LOWER;
	अगर (rtlpriv->falsealm_cnt.cnt_all > 10000)
		value_igi = 0x32;

	dm_digtable->cur_igvalue = value_igi;
	rtl8723e_dm_ग_लिखो_dig(hw);
पूर्ण

अटल व्योम rtl92c_dm_ctrl_initgain_by_rssi(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	अगर (rtlpriv->falsealm_cnt.cnt_all > dm_digtable->fa_highthresh) अणु
		अगर ((dm_digtable->back_val - 2) <
		    dm_digtable->back_range_min)
			dm_digtable->back_val =
			    dm_digtable->back_range_min;
		अन्यथा
			dm_digtable->back_val -= 2;
	पूर्ण अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all < dm_digtable->fa_lowthresh) अणु
		अगर ((dm_digtable->back_val + 2) >
		    dm_digtable->back_range_max)
			dm_digtable->back_val =
			    dm_digtable->back_range_max;
		अन्यथा
			dm_digtable->back_val += 2;
	पूर्ण

	अगर ((dm_digtable->rssi_val_min + 10 - dm_digtable->back_val) >
	    dm_digtable->rx_gain_max)
		dm_digtable->cur_igvalue = dm_digtable->rx_gain_max;
	अन्यथा अगर ((dm_digtable->rssi_val_min + 10 -
		  dm_digtable->back_val) < dm_digtable->rx_gain_min)
		dm_digtable->cur_igvalue = dm_digtable->rx_gain_min;
	अन्यथा
		dm_digtable->cur_igvalue = dm_digtable->rssi_val_min + 10 -
		    dm_digtable->back_val;

	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"rssi_val_min = %x back_val %x\n",
		dm_digtable->rssi_val_min, dm_digtable->back_val);

	rtl8723e_dm_ग_लिखो_dig(hw);
पूर्ण

अटल व्योम rtl8723e_dm_initial_gain_multi_sta(काष्ठा ieee80211_hw *hw)
अणु
	अटल u8 binitialized;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	दीर्घ rssi_strength = rtlpriv->dm.entry_min_undec_sm_pwdb;
	bool multi_sta = false;

	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		multi_sta = true;

	अगर (!multi_sta || (dm_digtable->cursta_cstate != DIG_STA_DISCONNECT)) अणु
		binitialized = false;
		dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_MAX;
		वापस;
	पूर्ण अन्यथा अगर (!binitialized) अणु
		binitialized = true;
		dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_0;
		dm_digtable->cur_igvalue = 0x20;
		rtl8723e_dm_ग_लिखो_dig(hw);
	पूर्ण

	अगर (dm_digtable->curmultista_cstate == DIG_MULTISTA_CONNECT) अणु
		अगर ((rssi_strength < dm_digtable->rssi_lowthresh) &&
		    (dm_digtable->dig_ext_port_stage != DIG_EXT_PORT_STAGE_1)) अणु

			अगर (dm_digtable->dig_ext_port_stage ==
			    DIG_EXT_PORT_STAGE_2) अणु
				dm_digtable->cur_igvalue = 0x20;
				rtl8723e_dm_ग_लिखो_dig(hw);
			पूर्ण

			dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_1;
		पूर्ण अन्यथा अगर (rssi_strength > dm_digtable->rssi_highthresh) अणु
			dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_2;
			rtl92c_dm_ctrl_initgain_by_fa(hw);
		पूर्ण
	पूर्ण अन्यथा अगर (dm_digtable->dig_ext_port_stage != DIG_EXT_PORT_STAGE_0) अणु
		dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_0;
		dm_digtable->cur_igvalue = 0x20;
		rtl8723e_dm_ग_लिखो_dig(hw);
	पूर्ण

	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"curmultista_cstate = %x dig_ext_port_stage %x\n",
		dm_digtable->curmultista_cstate,
		dm_digtable->dig_ext_port_stage);
पूर्ण

अटल व्योम rtl8723e_dm_initial_gain_sta(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"presta_cstate = %x, cursta_cstate = %x\n",
		dm_digtable->presta_cstate,
		dm_digtable->cursta_cstate);

	अगर (dm_digtable->presta_cstate == dm_digtable->cursta_cstate ||
	    dm_digtable->cursta_cstate == DIG_STA_BEFORE_CONNECT ||
	    dm_digtable->cursta_cstate == DIG_STA_CONNECT) अणु
		अगर (dm_digtable->cursta_cstate != DIG_STA_DISCONNECT) अणु
			dm_digtable->rssi_val_min =
			    rtl8723e_dm_initial_gain_min_pwdb(hw);
			rtl92c_dm_ctrl_initgain_by_rssi(hw);
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_digtable->rssi_val_min = 0;
		dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_MAX;
		dm_digtable->back_val = DM_DIG_BACKOFF_DEFAULT;
		dm_digtable->cur_igvalue = 0x20;
		dm_digtable->pre_igvalue = 0;
		rtl8723e_dm_ग_लिखो_dig(hw);
	पूर्ण
पूर्ण

अटल व्योम rtl8723e_dm_cck_packet_detection_thresh(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	अगर (dm_digtable->cursta_cstate == DIG_STA_CONNECT) अणु
		dm_digtable->rssi_val_min = rtl8723e_dm_initial_gain_min_pwdb(hw);

		अगर (dm_digtable->pre_cck_pd_state == CCK_PD_STAGE_LOWRSSI) अणु
			अगर (dm_digtable->rssi_val_min <= 25)
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_LOWRSSI;
			अन्यथा
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_HIGHRSSI;
		पूर्ण अन्यथा अणु
			अगर (dm_digtable->rssi_val_min <= 20)
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_LOWRSSI;
			अन्यथा
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_HIGHRSSI;
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_digtable->cur_cck_pd_state = CCK_PD_STAGE_MAX;
	पूर्ण

	अगर (dm_digtable->pre_cck_pd_state != dm_digtable->cur_cck_pd_state) अणु
		अगर (dm_digtable->cur_cck_pd_state == CCK_PD_STAGE_LOWRSSI) अणु
			अगर (rtlpriv->falsealm_cnt.cnt_cck_fail > 800)
				dm_digtable->cur_cck_fa_state =
				    CCK_FA_STAGE_HIGH;
			अन्यथा
				dm_digtable->cur_cck_fa_state =
				    CCK_FA_STAGE_LOW;
			अगर (dm_digtable->pre_cck_fa_state !=
			    dm_digtable->cur_cck_fa_state) अणु
				अगर (dm_digtable->cur_cck_fa_state ==
				    CCK_FA_STAGE_LOW)
					rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2,
						      0x83);
				अन्यथा
					rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2,
						      0xcd);

				dm_digtable->pre_cck_fa_state =
				    dm_digtable->cur_cck_fa_state;
			पूर्ण

			rtl_set_bbreg(hw, RCCK0_SYSTEM, MASKBYTE1, 0x40);

		पूर्ण अन्यथा अणु
			rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0xcd);
			rtl_set_bbreg(hw, RCCK0_SYSTEM, MASKBYTE1, 0x47);
			dm_digtable->pre_cck_fa_state = 0;
			dm_digtable->cur_cck_fa_state = 0;

		पूर्ण
		dm_digtable->pre_cck_pd_state = dm_digtable->cur_cck_pd_state;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"CCKPDStage=%x\n", dm_digtable->cur_cck_pd_state);

पूर्ण

अटल व्योम rtl8723e_dm_ctrl_initgain_by_twoport(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	अगर (mac->act_scanning)
		वापस;

	अगर (mac->link_state >= MAC80211_LINKED)
		dm_digtable->cursta_cstate = DIG_STA_CONNECT;
	अन्यथा
		dm_digtable->cursta_cstate = DIG_STA_DISCONNECT;

	rtl8723e_dm_initial_gain_sta(hw);
	rtl8723e_dm_initial_gain_multi_sta(hw);
	rtl8723e_dm_cck_packet_detection_thresh(hw);

	dm_digtable->presta_cstate = dm_digtable->cursta_cstate;

पूर्ण

अटल व्योम rtl8723e_dm_dig(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	अगर (!rtlpriv->dm.dm_initialgain_enable)
		वापस;
	अगर (!dm_digtable->dig_enable_flag)
		वापस;

	rtl8723e_dm_ctrl_initgain_by_twoport(hw);

पूर्ण

अटल व्योम rtl8723e_dm_dynamic_txघातer(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	दीर्घ undec_sm_pwdb;

	अगर (!rtlpriv->dm.dynamic_txघातer_enable)
		वापस;

	अगर (rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
		वापस;
	पूर्ण

	अगर ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
			"Not connected to any\n");

		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;

		rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
		वापस;
	पूर्ण

	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			undec_sm_pwdb =
			    rtlpriv->dm.entry_min_undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"AP Client PWDB = 0x%lx\n",
				undec_sm_pwdb);
		पूर्ण अन्यथा अणु
			undec_sm_pwdb =
			    rtlpriv->dm.undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"STA Default Port PWDB = 0x%lx\n",
				undec_sm_pwdb);
		पूर्ण
	पूर्ण अन्यथा अणु
		undec_sm_pwdb =
		    rtlpriv->dm.entry_min_undec_sm_pwdb;

		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"AP Ext Port PWDB = 0x%lx\n",
			undec_sm_pwdb);
	पूर्ण

	अगर (undec_sm_pwdb >= TX_POWER_NEAR_FIELD_THRESH_LVL2) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_LEVEL1;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x0)\n");
	पूर्ण अन्यथा अगर ((undec_sm_pwdb <
		    (TX_POWER_NEAR_FIELD_THRESH_LVL2 - 3)) &&
		   (undec_sm_pwdb >=
		    TX_POWER_NEAR_FIELD_THRESH_LVL1)) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_LEVEL1;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x10)\n");
	पूर्ण अन्यथा अगर (undec_sm_pwdb <
		   (TX_POWER_NEAR_FIELD_THRESH_LVL1 - 5)) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"TXHIGHPWRLEVEL_NORMAL\n");
	पूर्ण

	अगर (rtlpriv->dm.dynamic_txhighघातer_lvl != rtlpriv->dm.last_dtp_lvl) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"PHY_SetTxPowerLevel8192S() Channel = %d\n",
			rtlphy->current_channel);
		rtl8723e_phy_set_txघातer_level(hw, rtlphy->current_channel);
	पूर्ण

	rtlpriv->dm.last_dtp_lvl = rtlpriv->dm.dynamic_txhighघातer_lvl;
पूर्ण

व्योम rtl8723e_dm_ग_लिखो_dig(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"cur_igvalue = 0x%x, pre_igvalue = 0x%x, back_val = %d\n",
		dm_digtable->cur_igvalue, dm_digtable->pre_igvalue,
		dm_digtable->back_val);

	अगर (dm_digtable->pre_igvalue != dm_digtable->cur_igvalue) अणु
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, 0x7f,
			      dm_digtable->cur_igvalue);
		rtl_set_bbreg(hw, ROFDM0_XBAGCCORE1, 0x7f,
			      dm_digtable->cur_igvalue);

		dm_digtable->pre_igvalue = dm_digtable->cur_igvalue;
	पूर्ण
पूर्ण

अटल व्योम rtl8723e_dm_pwdb_monitor(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण

अटल व्योम rtl8723e_dm_check_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	अटल u64 last_txok_cnt;
	अटल u64 last_rxok_cnt;
	अटल u32 last_bt_edca_ul;
	अटल u32 last_bt_edca_dl;
	u64 cur_txok_cnt = 0;
	u64 cur_rxok_cnt = 0;
	u32 edca_be_ul = 0x5ea42b;
	u32 edca_be_dl = 0x5ea42b;
	bool bt_change_edca = false;

	अगर ((last_bt_edca_ul != rtlpriv->btcoexist.bt_edca_ul) ||
	    (last_bt_edca_dl != rtlpriv->btcoexist.bt_edca_dl)) अणु
		rtlpriv->dm.current_turbo_edca = false;
		last_bt_edca_ul = rtlpriv->btcoexist.bt_edca_ul;
		last_bt_edca_dl = rtlpriv->btcoexist.bt_edca_dl;
	पूर्ण

	अगर (rtlpriv->btcoexist.bt_edca_ul != 0) अणु
		edca_be_ul = rtlpriv->btcoexist.bt_edca_ul;
		bt_change_edca = true;
	पूर्ण

	अगर (rtlpriv->btcoexist.bt_edca_dl != 0) अणु
		edca_be_ul = rtlpriv->btcoexist.bt_edca_dl;
		bt_change_edca = true;
	पूर्ण

	अगर (mac->link_state != MAC80211_LINKED) अणु
		rtlpriv->dm.current_turbo_edca = false;
		वापस;
	पूर्ण
	अगर ((bt_change_edca) || ((!rtlpriv->dm.is_any_nonbepkts) &&
	     (!rtlpriv->dm.disable_framebursting))) अणु

		cur_txok_cnt = rtlpriv->stats.txbytesunicast - last_txok_cnt;
		cur_rxok_cnt = rtlpriv->stats.rxbytesunicast - last_rxok_cnt;

		अगर (cur_rxok_cnt > 4 * cur_txok_cnt) अणु
			अगर (!rtlpriv->dm.is_cur_rdlstate ||
			    !rtlpriv->dm.current_turbo_edca) अणु
				rtl_ग_लिखो_dword(rtlpriv,
						REG_EDCA_BE_PARAM,
						edca_be_dl);
				rtlpriv->dm.is_cur_rdlstate = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (rtlpriv->dm.is_cur_rdlstate ||
			    !rtlpriv->dm.current_turbo_edca) अणु
				rtl_ग_लिखो_dword(rtlpriv,
						REG_EDCA_BE_PARAM,
						edca_be_ul);
				rtlpriv->dm.is_cur_rdlstate = false;
			पूर्ण
		पूर्ण
		rtlpriv->dm.current_turbo_edca = true;
	पूर्ण अन्यथा अणु
		अगर (rtlpriv->dm.current_turbo_edca) अणु
			u8 पंचांगp = AC0_BE;
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_AC_PARAM,
						      (u8 *)(&पंचांगp));
			rtlpriv->dm.current_turbo_edca = false;
		पूर्ण
	पूर्ण

	rtlpriv->dm.is_any_nonbepkts = false;
	last_txok_cnt = rtlpriv->stats.txbytesunicast;
	last_rxok_cnt = rtlpriv->stats.rxbytesunicast;
पूर्ण

अटल व्योम rtl8723e_dm_initialize_txघातer_tracking_thermalmeter(
				काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.txघातer_tracking = true;
	rtlpriv->dm.txघातer_trackinginit = false;

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"pMgntInfo->txpower_tracking = %d\n",
		rtlpriv->dm.txघातer_tracking);
पूर्ण

अटल व्योम rtl8723e_dm_initialize_txघातer_tracking(काष्ठा ieee80211_hw *hw)
अणु
	rtl8723e_dm_initialize_txघातer_tracking_thermalmeter(hw);
पूर्ण

व्योम rtl8723e_dm_check_txघातer_tracking(काष्ठा ieee80211_hw *hw)
अणु
	वापस;
पूर्ण

व्योम rtl8723e_dm_init_rate_adaptive_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rate_adaptive *p_ra = &rtlpriv->ra;

	p_ra->ratr_state = DM_RATR_STA_INIT;
	p_ra->pre_ratr_state = DM_RATR_STA_INIT;

	अगर (rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER)
		rtlpriv->dm.useramask = true;
	अन्यथा
		rtlpriv->dm.useramask = false;

पूर्ण

अटल व्योम rtl8723e_dm_refresh_rate_adaptive_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rate_adaptive *p_ra = &rtlpriv->ra;
	u32 low_rssithresh_क्रम_ra, high_rssithresh_क्रम_ra;
	काष्ठा ieee80211_sta *sta = शून्य;

	अगर (is_hal_stop(rtlhal)) अणु
		rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
			" driver is going to unload\n");
		वापस;
	पूर्ण

	अगर (!rtlpriv->dm.useramask) अणु
		rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
			" driver does not control rate adaptive mask\n");
		वापस;
	पूर्ण

	अगर (mac->link_state == MAC80211_LINKED &&
	    mac->opmode == NL80211_IFTYPE_STATION) अणु
		चयन (p_ra->pre_ratr_state) अणु
		हाल DM_RATR_STA_HIGH:
			high_rssithresh_क्रम_ra = 50;
			low_rssithresh_क्रम_ra = 20;
			अवरोध;
		हाल DM_RATR_STA_MIDDLE:
			high_rssithresh_क्रम_ra = 55;
			low_rssithresh_क्रम_ra = 20;
			अवरोध;
		हाल DM_RATR_STA_LOW:
			high_rssithresh_क्रम_ra = 60;
			low_rssithresh_क्रम_ra = 25;
			अवरोध;
		शेष:
			high_rssithresh_क्रम_ra = 50;
			low_rssithresh_क्रम_ra = 20;
			अवरोध;
		पूर्ण

		अगर (rtlpriv->link_info.bcn_rx_inperiod == 0)
			चयन (p_ra->pre_ratr_state) अणु
			हाल DM_RATR_STA_HIGH:
			शेष:
				p_ra->ratr_state = DM_RATR_STA_MIDDLE;
				अवरोध;
			हाल DM_RATR_STA_MIDDLE:
			हाल DM_RATR_STA_LOW:
				p_ra->ratr_state = DM_RATR_STA_LOW;
				अवरोध;
			पूर्ण
		अन्यथा अगर (rtlpriv->dm.undec_sm_pwdb > high_rssithresh_क्रम_ra)
			p_ra->ratr_state = DM_RATR_STA_HIGH;
		अन्यथा अगर (rtlpriv->dm.undec_sm_pwdb > low_rssithresh_क्रम_ra)
			p_ra->ratr_state = DM_RATR_STA_MIDDLE;
		अन्यथा
			p_ra->ratr_state = DM_RATR_STA_LOW;

		अगर (p_ra->pre_ratr_state != p_ra->ratr_state) अणु
			rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
				"RSSI = %ld\n",
				rtlpriv->dm.undec_sm_pwdb);
			rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
				"RSSI_LEVEL = %d\n", p_ra->ratr_state);
			rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
				"PreState = %d, CurState = %d\n",
				p_ra->pre_ratr_state, p_ra->ratr_state);

			rcu_पढ़ो_lock();
			sta = rtl_find_sta(hw, mac->bssid);
			अगर (sta)
				rtlpriv->cfg->ops->update_rate_tbl(hw, sta,
							   p_ra->ratr_state,
								      true);
			rcu_पढ़ो_unlock();

			p_ra->pre_ratr_state = p_ra->ratr_state;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl8723e_dm_rf_saving(काष्ठा ieee80211_hw *hw, u8 bक्रमce_in_normal)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ps_t *dm_pstable = &rtlpriv->dm_pstable;
	अटल u8 initialize;
	अटल u32 reg_874, reg_c70, reg_85c, reg_a74;

	अगर (initialize == 0) अणु
		reg_874 = (rtl_get_bbreg(hw, RFPGA0_XCD_RFINTERFACESW,
					 MASKDWORD) & 0x1CC000) >> 14;

		reg_c70 = (rtl_get_bbreg(hw, ROFDM0_AGCPARAMETER1,
					 MASKDWORD) & BIT(3)) >> 3;

		reg_85c = (rtl_get_bbreg(hw, RFPGA0_XCD_SWITCHCONTROL,
					 MASKDWORD) & 0xFF000000) >> 24;

		reg_a74 = (rtl_get_bbreg(hw, 0xa74, MASKDWORD) & 0xF000) >> 12;

		initialize = 1;
	पूर्ण

	अगर (!bक्रमce_in_normal) अणु
		अगर (dm_pstable->rssi_val_min != 0) अणु
			अगर (dm_pstable->pre_rख_स्थितिe == RF_NORMAL) अणु
				अगर (dm_pstable->rssi_val_min >= 30)
					dm_pstable->cur_rख_स्थितिe = RF_SAVE;
				अन्यथा
					dm_pstable->cur_rख_स्थितिe = RF_NORMAL;
			पूर्ण अन्यथा अणु
				अगर (dm_pstable->rssi_val_min <= 25)
					dm_pstable->cur_rख_स्थितिe = RF_NORMAL;
				अन्यथा
					dm_pstable->cur_rख_स्थितिe = RF_SAVE;
			पूर्ण
		पूर्ण अन्यथा अणु
			dm_pstable->cur_rख_स्थितिe = RF_MAX;
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_pstable->cur_rख_स्थितिe = RF_NORMAL;
	पूर्ण

	अगर (dm_pstable->pre_rख_स्थितिe != dm_pstable->cur_rख_स्थितिe) अणु
		अगर (dm_pstable->cur_rख_स्थितिe == RF_SAVE) अणु
			rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW,
				      BIT(5), 0x1);
			rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW,
				      0x1C0000, 0x2);
			rtl_set_bbreg(hw, ROFDM0_AGCPARAMETER1, BIT(3), 0);
			rtl_set_bbreg(hw, RFPGA0_XCD_SWITCHCONTROL,
				      0xFF000000, 0x63);
			rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW,
				      0xC000, 0x2);
			rtl_set_bbreg(hw, 0xa74, 0xF000, 0x3);
			rtl_set_bbreg(hw, 0x818, BIT(28), 0x0);
			rtl_set_bbreg(hw, 0x818, BIT(28), 0x1);
		पूर्ण अन्यथा अणु
			rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW,
				      0x1CC000, reg_874);
			rtl_set_bbreg(hw, ROFDM0_AGCPARAMETER1, BIT(3),
				      reg_c70);
			rtl_set_bbreg(hw, RFPGA0_XCD_SWITCHCONTROL, 0xFF000000,
				      reg_85c);
			rtl_set_bbreg(hw, 0xa74, 0xF000, reg_a74);
			rtl_set_bbreg(hw, 0x818, BIT(28), 0x0);
			rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW,
				      BIT(5), 0x0);
		पूर्ण

		dm_pstable->pre_rख_स्थितिe = dm_pstable->cur_rख_स्थितिe;
	पूर्ण
पूर्ण

अटल व्योम rtl8723e_dm_dynamic_bb_घातersaving(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा ps_t *dm_pstable = &rtlpriv->dm_pstable;

	अगर (((mac->link_state == MAC80211_NOLINK)) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) अणु
		dm_pstable->rssi_val_min = 0;
		rtl_dbg(rtlpriv, DBG_LOUD, DBG_LOUD,
			"Not connected to any\n");
	पूर्ण

	अगर (mac->link_state == MAC80211_LINKED) अणु
		अगर (mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			dm_pstable->rssi_val_min =
			    rtlpriv->dm.entry_min_undec_sm_pwdb;
			rtl_dbg(rtlpriv, DBG_LOUD, DBG_LOUD,
				"AP Client PWDB = 0x%lx\n",
				dm_pstable->rssi_val_min);
		पूर्ण अन्यथा अणु
			dm_pstable->rssi_val_min =
			    rtlpriv->dm.undec_sm_pwdb;
			rtl_dbg(rtlpriv, DBG_LOUD, DBG_LOUD,
				"STA Default Port PWDB = 0x%lx\n",
				dm_pstable->rssi_val_min);
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_pstable->rssi_val_min =
		    rtlpriv->dm.entry_min_undec_sm_pwdb;

		rtl_dbg(rtlpriv, DBG_LOUD, DBG_LOUD,
			"AP Ext Port PWDB = 0x%lx\n",
			dm_pstable->rssi_val_min);
	पूर्ण

	rtl8723e_dm_rf_saving(hw, false);
पूर्ण

व्योम rtl8723e_dm_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;
	rtl_dm_diginit(hw, 0x20);
	rtl8723_dm_init_dynamic_txघातer(hw);
	rtl8723_dm_init_edca_turbo(hw);
	rtl8723e_dm_init_rate_adaptive_mask(hw);
	rtl8723e_dm_initialize_txघातer_tracking(hw);
	rtl8723_dm_init_dynamic_bb_घातersaving(hw);
पूर्ण

व्योम rtl8723e_dm_watchकरोg(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool fw_current_inpsmode = false;
	bool fw_ps_awake = true;
	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				      (u8 *)(&fw_current_inpsmode));
	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FWLPS_RF_ON,
				      (u8 *)(&fw_ps_awake));

	अगर (ppsc->p2p_ps_info.p2p_ps_mode)
		fw_ps_awake = false;

	spin_lock(&rtlpriv->locks.rf_ps_lock);
	अगर ((ppsc->rfpwr_state == ERFON) &&
	    ((!fw_current_inpsmode) && fw_ps_awake) &&
	    (!ppsc->rfchange_inprogress)) अणु
		rtl8723e_dm_pwdb_monitor(hw);
		rtl8723e_dm_dig(hw);
		rtl8723e_dm_false_alarm_counter_statistics(hw);
		rtl8723e_dm_dynamic_bb_घातersaving(hw);
		rtl8723e_dm_dynamic_txघातer(hw);
		rtl8723e_dm_check_txघातer_tracking(hw);
		rtl8723e_dm_refresh_rate_adaptive_mask(hw);
		rtl8723e_dm_bt_coexist(hw);
		rtl8723e_dm_check_edca_turbo(hw);
	पूर्ण
	spin_unlock(&rtlpriv->locks.rf_ps_lock);
	अगर (rtlpriv->btcoexist.init_set)
		rtl_ग_लिखो_byte(rtlpriv, 0x76e, 0xc);
पूर्ण

अटल व्योम rtl8723e_dm_init_bt_coexist(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->btcoexist.bt_rfreg_origin_1e
		= rtl_get_rfreg(hw, (क्रमागत radio_path)0, RF_RCK1, 0xfffff);
	rtlpriv->btcoexist.bt_rfreg_origin_1f
		= rtl_get_rfreg(hw, (क्रमागत radio_path)0, RF_RCK2, 0xf0);

	rtlpriv->btcoexist.cstate = 0;
	rtlpriv->btcoexist.previous_state = 0;
	rtlpriv->btcoexist.cstate_h = 0;
	rtlpriv->btcoexist.previous_state_h = 0;
	rtlpriv->btcoexist.lps_counter = 0;

	/*  Enable counter statistics */
	rtl_ग_लिखो_byte(rtlpriv, 0x76e, 0x4);
	rtl_ग_लिखो_byte(rtlpriv, 0x778, 0x3);
	rtl_ग_लिखो_byte(rtlpriv, 0x40, 0x20);

	rtlpriv->btcoexist.init_set = true;
पूर्ण

व्योम rtl8723e_dm_bt_coexist(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगp_byte = 0;
	अगर (!rtlpriv->btcoexist.bt_coexistence) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[DM]{BT], BT not exist!!\n");
		वापस;
	पूर्ण

	अगर (!rtlpriv->btcoexist.init_set) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[DM][BT], %s\n", __func__);
		rtl8723e_dm_init_bt_coexist(hw);
	पूर्ण

	पंचांगp_byte = rtl_पढ़ो_byte(rtlpriv, 0x40);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[DM][BT], 0x40 is 0x%x\n", पंचांगp_byte);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"[DM][BT], bt_dm_coexist start\n");
	rtl8723e_dm_bt_coexist_8723(hw);
पूर्ण
