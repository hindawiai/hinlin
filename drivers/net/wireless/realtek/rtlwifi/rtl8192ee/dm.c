<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../base.h"
#समावेश "../pci.h"
#समावेश "../core.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "dm.h"
#समावेश "fw.h"
#समावेश "trx.h"

अटल व्योम rtl92ee_dm_false_alarm_counter_statistics(काष्ठा ieee80211_hw *hw)
अणु
	u32 ret_value;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा false_alarm_statistics *falsealm_cnt = &rtlpriv->falsealm_cnt;

	rtl_set_bbreg(hw, DM_REG_OFDM_FA_HOLDC_11N, BIT(31), 1);
	rtl_set_bbreg(hw, DM_REG_OFDM_FA_RSTD_11N, BIT(31), 1);

	ret_value = rtl_get_bbreg(hw, DM_REG_OFDM_FA_TYPE1_11N, MASKDWORD);
	falsealm_cnt->cnt_fast_fsync_fail = (ret_value & 0xffff);
	falsealm_cnt->cnt_sb_search_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, DM_REG_OFDM_FA_TYPE2_11N, MASKDWORD);
	falsealm_cnt->cnt_ofdm_cca = (ret_value & 0xffff);
	falsealm_cnt->cnt_parity_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, DM_REG_OFDM_FA_TYPE3_11N, MASKDWORD);
	falsealm_cnt->cnt_rate_illegal = (ret_value & 0xffff);
	falsealm_cnt->cnt_crc8_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, DM_REG_OFDM_FA_TYPE4_11N, MASKDWORD);
	falsealm_cnt->cnt_mcs_fail = (ret_value & 0xffff);

	falsealm_cnt->cnt_ofdm_fail = falsealm_cnt->cnt_parity_fail +
				      falsealm_cnt->cnt_rate_illegal +
				      falsealm_cnt->cnt_crc8_fail +
				      falsealm_cnt->cnt_mcs_fail +
				      falsealm_cnt->cnt_fast_fsync_fail +
				      falsealm_cnt->cnt_sb_search_fail;

	ret_value = rtl_get_bbreg(hw, DM_REG_SC_CNT_11N, MASKDWORD);
	falsealm_cnt->cnt_bw_lsc = (ret_value & 0xffff);
	falsealm_cnt->cnt_bw_usc = ((ret_value & 0xffff0000) >> 16);

	rtl_set_bbreg(hw, DM_REG_CCK_FA_RST_11N, BIT(12), 1);
	rtl_set_bbreg(hw, DM_REG_CCK_FA_RST_11N, BIT(14), 1);

	ret_value = rtl_get_bbreg(hw, DM_REG_CCK_FA_LSB_11N, MASKBYTE0);
	falsealm_cnt->cnt_cck_fail = ret_value;

	ret_value = rtl_get_bbreg(hw, DM_REG_CCK_FA_MSB_11N, MASKBYTE3);
	falsealm_cnt->cnt_cck_fail += (ret_value & 0xff) << 8;

	ret_value = rtl_get_bbreg(hw, DM_REG_CCK_CCA_CNT_11N, MASKDWORD);
	falsealm_cnt->cnt_cck_cca = ((ret_value & 0xff) << 8) |
				    ((ret_value & 0xFF00) >> 8);

	falsealm_cnt->cnt_all = falsealm_cnt->cnt_fast_fsync_fail +
				falsealm_cnt->cnt_sb_search_fail +
				falsealm_cnt->cnt_parity_fail +
				falsealm_cnt->cnt_rate_illegal +
				falsealm_cnt->cnt_crc8_fail +
				falsealm_cnt->cnt_mcs_fail +
				falsealm_cnt->cnt_cck_fail;

	falsealm_cnt->cnt_cca_all = falsealm_cnt->cnt_ofdm_cca +
				    falsealm_cnt->cnt_cck_cca;

	/*reset false alarm counter रेजिस्टरs*/
	rtl_set_bbreg(hw, DM_REG_OFDM_FA_RSTC_11N, BIT(31), 1);
	rtl_set_bbreg(hw, DM_REG_OFDM_FA_RSTC_11N, BIT(31), 0);
	rtl_set_bbreg(hw, DM_REG_OFDM_FA_RSTD_11N, BIT(27), 1);
	rtl_set_bbreg(hw, DM_REG_OFDM_FA_RSTD_11N, BIT(27), 0);
	/*update ofdm counter*/
	rtl_set_bbreg(hw, DM_REG_OFDM_FA_HOLDC_11N, BIT(31), 0);
	rtl_set_bbreg(hw, DM_REG_OFDM_FA_RSTD_11N, BIT(31), 0);
	/*reset CCK CCA counter*/
	rtl_set_bbreg(hw, DM_REG_CCK_FA_RST_11N, BIT(13) | BIT(12), 0);
	rtl_set_bbreg(hw, DM_REG_CCK_FA_RST_11N, BIT(13) | BIT(12), 2);
	/*reset CCK FA counter*/
	rtl_set_bbreg(hw, DM_REG_CCK_FA_RST_11N, BIT(15) | BIT(14), 0);
	rtl_set_bbreg(hw, DM_REG_CCK_FA_RST_11N, BIT(15) | BIT(14), 2);

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

अटल व्योम rtl92ee_dm_cck_packet_detection_thresh(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_dig = &rtlpriv->dm_digtable;
	u8 cur_cck_cca_thresh;

	अगर (rtlpriv->mac80211.link_state >= MAC80211_LINKED) अणु
		अगर (dm_dig->rssi_val_min > 25) अणु
			cur_cck_cca_thresh = 0xcd;
		पूर्ण अन्यथा अगर ((dm_dig->rssi_val_min <= 25) &&
			   (dm_dig->rssi_val_min > 10)) अणु
			cur_cck_cca_thresh = 0x83;
		पूर्ण अन्यथा अणु
			अगर (rtlpriv->falsealm_cnt.cnt_cck_fail > 1000)
				cur_cck_cca_thresh = 0x83;
			अन्यथा
				cur_cck_cca_thresh = 0x40;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rtlpriv->falsealm_cnt.cnt_cck_fail > 1000)
			cur_cck_cca_thresh = 0x83;
		अन्यथा
			cur_cck_cca_thresh = 0x40;
	पूर्ण
	rtl92ee_dm_ग_लिखो_cck_cca_thres(hw, cur_cck_cca_thresh);
पूर्ण

अटल व्योम rtl92ee_dm_dig(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा dig_t *dm_dig = &rtlpriv->dm_digtable;
	u8 dig_min_0, dig_maxofmin;
	bool bfirstconnect , bfirstdisconnect;
	u8 dm_dig_max, dm_dig_min;
	u8 current_igi = dm_dig->cur_igvalue;
	u8 offset;

	/* AP,BT */
	अगर (mac->act_scanning)
		वापस;

	dig_min_0 = dm_dig->dig_min_0;
	bfirstconnect = (mac->link_state >= MAC80211_LINKED) &&
			!dm_dig->media_connect_0;
	bfirstdisconnect = (mac->link_state < MAC80211_LINKED) &&
			   dm_dig->media_connect_0;

	dm_dig_max = 0x5a;
	dm_dig_min = DM_DIG_MIN;
	dig_maxofmin = DM_DIG_MAX_AP;

	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर ((dm_dig->rssi_val_min + 10) > dm_dig_max)
			dm_dig->rx_gain_max = dm_dig_max;
		अन्यथा अगर ((dm_dig->rssi_val_min + 10) < dm_dig_min)
			dm_dig->rx_gain_max = dm_dig_min;
		अन्यथा
			dm_dig->rx_gain_max = dm_dig->rssi_val_min + 10;

		अगर (rtlpriv->dm.one_entry_only) अणु
			offset = 0;
			अगर (dm_dig->rssi_val_min - offset < dm_dig_min)
				dig_min_0 = dm_dig_min;
			अन्यथा अगर (dm_dig->rssi_val_min - offset >
				 dig_maxofmin)
				dig_min_0 = dig_maxofmin;
			अन्यथा
				dig_min_0 = dm_dig->rssi_val_min - offset;
		पूर्ण अन्यथा अणु
			dig_min_0 = dm_dig_min;
		पूर्ण

	पूर्ण अन्यथा अणु
		dm_dig->rx_gain_max = dm_dig_max;
		dig_min_0 = dm_dig_min;
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "no link\n");
	पूर्ण

	अगर (rtlpriv->falsealm_cnt.cnt_all > 10000) अणु
		अगर (dm_dig->large_fa_hit != 3)
			dm_dig->large_fa_hit++;
		अगर (dm_dig->क्रमbidden_igi < current_igi) अणु
			dm_dig->क्रमbidden_igi = current_igi;
			dm_dig->large_fa_hit = 1;
		पूर्ण

		अगर (dm_dig->large_fa_hit >= 3) अणु
			अगर (dm_dig->क्रमbidden_igi + 1 > dm_dig->rx_gain_max)
				dm_dig->rx_gain_min =
						dm_dig->rx_gain_max;
			अन्यथा
				dm_dig->rx_gain_min =
						dm_dig->क्रमbidden_igi + 1;
			dm_dig->recover_cnt = 3600;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dm_dig->recover_cnt != 0) अणु
			dm_dig->recover_cnt--;
		पूर्ण अन्यथा अणु
			अगर (dm_dig->large_fa_hit < 3) अणु
				अगर ((dm_dig->क्रमbidden_igi - 1) <
				    dig_min_0) अणु
					dm_dig->क्रमbidden_igi = dig_min_0;
					dm_dig->rx_gain_min =
								dig_min_0;
				पूर्ण अन्यथा अणु
					dm_dig->क्रमbidden_igi--;
					dm_dig->rx_gain_min =
						dm_dig->क्रमbidden_igi + 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				dm_dig->large_fa_hit = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rtlpriv->dm.dbginfo.num_qry_beacon_pkt < 5)
		dm_dig->rx_gain_min = dm_dig_min;

	अगर (dm_dig->rx_gain_min > dm_dig->rx_gain_max)
		dm_dig->rx_gain_min = dm_dig->rx_gain_max;

	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (bfirstconnect) अणु
			अगर (dm_dig->rssi_val_min <= dig_maxofmin)
				current_igi = dm_dig->rssi_val_min;
			अन्यथा
				current_igi = dig_maxofmin;

			dm_dig->large_fa_hit = 0;
		पूर्ण अन्यथा अणु
			अगर (rtlpriv->falsealm_cnt.cnt_all > DM_DIG_FA_TH2)
				current_igi += 4;
			अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all > DM_DIG_FA_TH1)
				current_igi += 2;
			अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH0)
				current_igi -= 2;

			अगर (rtlpriv->dm.dbginfo.num_qry_beacon_pkt < 5 &&
			    rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH1)
				current_igi = dm_dig->rx_gain_min;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bfirstdisconnect) अणु
			current_igi = dm_dig->rx_gain_min;
		पूर्ण अन्यथा अणु
			अगर (rtlpriv->falsealm_cnt.cnt_all > 10000)
				current_igi += 4;
			अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all > 8000)
				current_igi += 2;
			अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all < 500)
				current_igi -= 2;
		पूर्ण
	पूर्ण

	अगर (current_igi > dm_dig->rx_gain_max)
		current_igi = dm_dig->rx_gain_max;
	अगर (current_igi < dm_dig->rx_gain_min)
		current_igi = dm_dig->rx_gain_min;

	rtl92ee_dm_ग_लिखो_dig(hw , current_igi);
	dm_dig->media_connect_0 = ((mac->link_state >= MAC80211_LINKED) ?
				   true : false);
	dm_dig->dig_min_0 = dig_min_0;
पूर्ण

व्योम rtl92ee_dm_ग_लिखो_cck_cca_thres(काष्ठा ieee80211_hw *hw, u8 cur_thres)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_dig = &rtlpriv->dm_digtable;

	अगर (dm_dig->cur_cck_cca_thres != cur_thres)
		rtl_ग_लिखो_byte(rtlpriv, DM_REG_CCK_CCA_11N, cur_thres);

	dm_dig->pre_cck_cca_thres = dm_dig->cur_cck_cca_thres;
	dm_dig->cur_cck_cca_thres = cur_thres;
पूर्ण

व्योम rtl92ee_dm_ग_लिखो_dig(काष्ठा ieee80211_hw *hw, u8 current_igi)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_dig = &rtlpriv->dm_digtable;

	अगर (dm_dig->stop_dig)
		वापस;

	अगर (dm_dig->cur_igvalue != current_igi) अणु
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, 0x7f, current_igi);
		अगर (rtlpriv->phy.rf_type != RF_1T1R)
			rtl_set_bbreg(hw, ROFDM0_XBAGCCORE1, 0x7f, current_igi);
	पूर्ण
	dm_dig->pre_igvalue = dm_dig->cur_igvalue;
	dm_dig->cur_igvalue = current_igi;
पूर्ण

अटल व्योम rtl92ee_rssi_dump_to_रेजिस्टर(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, RA_RSSIDUMP,
		       rtlpriv->stats.rx_rssi_percentage[0]);
	rtl_ग_लिखो_byte(rtlpriv, RB_RSSIDUMP,
		       rtlpriv->stats.rx_rssi_percentage[1]);
	/*It seems the following values are not initialized.
	  *According to Winकरोws code,
	  *these value will only be valid with JAGUAR chips
	  */
	/* Rx EVM */
	rtl_ग_लिखो_byte(rtlpriv, RS1_RXEVMDUMP, rtlpriv->stats.rx_evm_dbm[0]);
	rtl_ग_लिखो_byte(rtlpriv, RS2_RXEVMDUMP, rtlpriv->stats.rx_evm_dbm[1]);
	/* Rx SNR */
	rtl_ग_लिखो_byte(rtlpriv, RA_RXSNRDUMP,
		       (u8)(rtlpriv->stats.rx_snr_db[0]));
	rtl_ग_लिखो_byte(rtlpriv, RB_RXSNRDUMP,
		       (u8)(rtlpriv->stats.rx_snr_db[1]));
	/* Rx Cfo_Short */
	rtl_ग_लिखो_word(rtlpriv, RA_CFOSHORTDUMP,
		       rtlpriv->stats.rx_cfo_लघु[0]);
	rtl_ग_लिखो_word(rtlpriv, RB_CFOSHORTDUMP,
		       rtlpriv->stats.rx_cfo_लघु[1]);
	/* Rx Cfo_Tail */
	rtl_ग_लिखो_word(rtlpriv, RA_CFOLONGDUMP, rtlpriv->stats.rx_cfo_tail[0]);
	rtl_ग_लिखो_word(rtlpriv, RB_CFOLONGDUMP, rtlpriv->stats.rx_cfo_tail[1]);
पूर्ण

अटल व्योम rtl92ee_dm_find_minimum_rssi(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *rtl_dm_dig = &rtlpriv->dm_digtable;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);

	/* Determine the minimum RSSI  */
	अगर ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) अणु
		rtl_dm_dig->min_undec_pwdb_क्रम_dm = 0;
		rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
			"Not connected to any\n");
	पूर्ण
	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (mac->opmode == NL80211_IFTYPE_AP ||
		    mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			rtl_dm_dig->min_undec_pwdb_क्रम_dm =
				rtlpriv->dm.entry_min_undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
				"AP Client PWDB = 0x%lx\n",
				rtlpriv->dm.entry_min_undec_sm_pwdb);
		पूर्ण अन्यथा अणु
			rtl_dm_dig->min_undec_pwdb_क्रम_dm =
			    rtlpriv->dm.undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
				"STA Default Port PWDB = 0x%x\n",
				rtl_dm_dig->min_undec_pwdb_क्रम_dm);
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dm_dig->min_undec_pwdb_क्रम_dm =
			rtlpriv->dm.entry_min_undec_sm_pwdb;
		rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
			"AP Ext Port or disconnect PWDB = 0x%x\n",
			rtl_dm_dig->min_undec_pwdb_क्रम_dm);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"MinUndecoratedPWDBForDM =%d\n",
		rtl_dm_dig->min_undec_pwdb_क्रम_dm);
पूर्ण

अटल व्योम rtl92ee_dm_check_rssi_monitor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_dig = &rtlpriv->dm_digtable;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);
	काष्ठा rtl_dm *dm = rtl_dm(rtlpriv);
	काष्ठा rtl_sta_info *drv_priv;
	u8 h2c[4] = अणु 0 पूर्ण;
	दीर्घ max = 0, min = 0xff;
	u8 i = 0;

	अगर (mac->opmode == NL80211_IFTYPE_AP ||
	    mac->opmode == NL80211_IFTYPE_ADHOC ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		/* AP & ADHOC & MESH */
		spin_lock_bh(&rtlpriv->locks.entry_list_lock);
		list_क्रम_each_entry(drv_priv, &rtlpriv->entry_list, list) अणु
			काष्ठा rssi_sta *stat = &drv_priv->rssi_stat;

			अगर (stat->undec_sm_pwdb < min)
				min = stat->undec_sm_pwdb;
			अगर (stat->undec_sm_pwdb > max)
				max = stat->undec_sm_pwdb;

			h2c[3] = 0;
			h2c[2] = (u8)(dm->undec_sm_pwdb & 0xFF);
			h2c[1] = 0x20;
			h2c[0] = ++i;
			rtl92ee_fill_h2c_cmd(hw, H2C_92E_RSSI_REPORT, 4, h2c);
		पूर्ण
		spin_unlock_bh(&rtlpriv->locks.entry_list_lock);

		/* If associated entry is found */
		अगर (max != 0) अणु
			dm->entry_max_undec_sm_pwdb = max;
			RTPRINT(rtlpriv, FDM, DM_PWDB,
				"EntryMaxPWDB = 0x%lx(%ld)\n", max, max);
		पूर्ण अन्यथा अणु
			dm->entry_max_undec_sm_pwdb = 0;
		पूर्ण
		/* If associated entry is found */
		अगर (min != 0xff) अणु
			dm->entry_min_undec_sm_pwdb = min;
			RTPRINT(rtlpriv, FDM, DM_PWDB,
				"EntryMinPWDB = 0x%lx(%ld)\n", min, min);
		पूर्ण अन्यथा अणु
			dm->entry_min_undec_sm_pwdb = 0;
		पूर्ण
	पूर्ण

	/* Indicate Rx संकेत strength to FW. */
	अगर (dm->useramask) अणु
		h2c[3] = 0;
		h2c[2] = (u8)(dm->undec_sm_pwdb & 0xFF);
		h2c[1] = 0x20;
		h2c[0] = 0;
		rtl92ee_fill_h2c_cmd(hw, H2C_92E_RSSI_REPORT, 4, h2c);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, 0x4fe, dm->undec_sm_pwdb);
	पूर्ण
	rtl92ee_rssi_dump_to_रेजिस्टर(hw);
	rtl92ee_dm_find_minimum_rssi(hw);
	dm_dig->rssi_val_min = rtlpriv->dm_digtable.min_undec_pwdb_क्रम_dm;
पूर्ण

अटल व्योम rtl92ee_dm_init_primary_cca_check(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा dynamic_primary_cca *primarycca = &rtlpriv->primarycca;

	rtlhal->rts_en = 0;
	primarycca->dup_rts_flag = 0;
	primarycca->पूर्णांकf_flag = 0;
	primarycca->पूर्णांकf_type = 0;
	primarycca->monitor_flag = 0;
	primarycca->ch_offset = 0;
	primarycca->mf_state = 0;
पूर्ण

अटल bool rtl92ee_dm_is_edca_turbo_disable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->mac80211.mode == WIRELESS_MODE_B)
		वापस true;

	वापस false;
पूर्ण

व्योम rtl92ee_dm_init_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.current_turbo_edca = false;
	rtlpriv->dm.is_cur_rdlstate = false;
	rtlpriv->dm.is_any_nonbepkts = false;
पूर्ण

अटल व्योम rtl92ee_dm_check_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अटल u64 last_txok_cnt;
	अटल u64 last_rxok_cnt;
	u64 cur_txok_cnt = 0;
	u64 cur_rxok_cnt = 0;
	u32 edca_be_ul = 0x5ea42b;
	u32 edca_be_dl = 0x5ea42b; /*not sure*/
	u32 edca_be = 0x5ea42b;
	bool is_cur_rdlstate;
	bool b_edca_turbo_on = false;

	अगर (rtlpriv->dm.dbginfo.num_non_be_pkt > 0x100)
		rtlpriv->dm.is_any_nonbepkts = true;
	rtlpriv->dm.dbginfo.num_non_be_pkt = 0;

	cur_txok_cnt = rtlpriv->stats.txbytesunicast - last_txok_cnt;
	cur_rxok_cnt = rtlpriv->stats.rxbytesunicast - last_rxok_cnt;

	/*b_bias_on_rx = false;*/
	b_edca_turbo_on = ((!rtlpriv->dm.is_any_nonbepkts) &&
			   (!rtlpriv->dm.disable_framebursting)) ?
			  true : false;

	अगर (rtl92ee_dm_is_edca_turbo_disable(hw))
		जाओ check_निकास;

	अगर (b_edca_turbo_on) अणु
		is_cur_rdlstate = (cur_rxok_cnt > cur_txok_cnt * 4) ?
				    true : false;

		edca_be = is_cur_rdlstate ? edca_be_dl : edca_be_ul;
		rtl_ग_लिखो_dword(rtlpriv , REG_EDCA_BE_PARAM , edca_be);
		rtlpriv->dm.is_cur_rdlstate = is_cur_rdlstate;
		rtlpriv->dm.current_turbo_edca = true;
	पूर्ण अन्यथा अणु
		अगर (rtlpriv->dm.current_turbo_edca) अणु
			u8 पंचांगp = AC0_BE;

			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM,
						      (u8 *)(&पंचांगp));
		पूर्ण
		rtlpriv->dm.current_turbo_edca = false;
	पूर्ण

check_निकास:
	rtlpriv->dm.is_any_nonbepkts = false;
	last_txok_cnt = rtlpriv->stats.txbytesunicast;
	last_rxok_cnt = rtlpriv->stats.rxbytesunicast;
पूर्ण

अटल व्योम rtl92ee_dm_dynamic_edcca(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 reg_c50 , reg_c58;
	bool fw_current_in_ps_mode = false;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				      (u8 *)(&fw_current_in_ps_mode));
	अगर (fw_current_in_ps_mode)
		वापस;

	reg_c50 = rtl_get_bbreg(hw, ROFDM0_XAAGCCORE1, MASKBYTE0);
	reg_c58 = rtl_get_bbreg(hw, ROFDM0_XBAGCCORE1, MASKBYTE0);

	अगर (reg_c50 > 0x28 && reg_c58 > 0x28) अणु
		अगर (!rtlpriv->rtlhal.pre_edcca_enable) अणु
			rtl_ग_लिखो_byte(rtlpriv, ROFDM0_ECCATHRESHOLD, 0x03);
			rtl_ग_लिखो_byte(rtlpriv, ROFDM0_ECCATHRESHOLD + 2, 0x00);
			rtlpriv->rtlhal.pre_edcca_enable = true;
		पूर्ण
	पूर्ण अन्यथा अगर (reg_c50 < 0x25 && reg_c58 < 0x25) अणु
		अगर (rtlpriv->rtlhal.pre_edcca_enable) अणु
			rtl_ग_लिखो_byte(rtlpriv, ROFDM0_ECCATHRESHOLD, 0x7f);
			rtl_ग_लिखो_byte(rtlpriv, ROFDM0_ECCATHRESHOLD + 2, 0x7f);
			rtlpriv->rtlhal.pre_edcca_enable = false;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl92ee_dm_adaptivity(काष्ठा ieee80211_hw *hw)
अणु
	rtl92ee_dm_dynamic_edcca(hw);
पूर्ण

अटल व्योम rtl92ee_dm_ग_लिखो_dynamic_cca(काष्ठा ieee80211_hw *hw,
					 u8 cur_mf_state)
अणु
	काष्ठा dynamic_primary_cca *primarycca = &rtl_priv(hw)->primarycca;

	अगर (primarycca->mf_state != cur_mf_state)
		rtl_set_bbreg(hw, DM_REG_L1SBD_PD_CH_11N, BIT(8) | BIT(7),
			      cur_mf_state);

	primarycca->mf_state = cur_mf_state;
पूर्ण

अटल व्योम rtl92ee_dm_dynamic_primary_cca_ckeck(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा false_alarm_statistics *falsealm_cnt = &rtlpriv->falsealm_cnt;
	काष्ठा dynamic_primary_cca *primarycca = &rtlpriv->primarycca;
	bool is40mhz = false;
	u64 ofdm_cca, ofdm_fa, bw_usc_cnt, bw_lsc_cnt;
	u8 sec_ch_offset;
	u8 cur_mf_state;
	अटल u8 count_करोwn = MONITOR_TIME;

	ofdm_cca = falsealm_cnt->cnt_ofdm_cca;
	ofdm_fa = falsealm_cnt->cnt_ofdm_fail;
	bw_usc_cnt = falsealm_cnt->cnt_bw_usc;
	bw_lsc_cnt = falsealm_cnt->cnt_bw_lsc;
	is40mhz = rtlpriv->mac80211.bw_40;
	sec_ch_offset = rtlpriv->mac80211.cur_40_prime_sc;
	/* NIC: 2: sec is below,  1: sec is above */

	अगर (rtlpriv->mac80211.opmode == NL80211_IFTYPE_AP) अणु
		cur_mf_state = MF_USC_LSC;
		rtl92ee_dm_ग_लिखो_dynamic_cca(hw, cur_mf_state);
		वापस;
	पूर्ण

	अगर (rtlpriv->mac80211.link_state < MAC80211_LINKED)
		वापस;

	अगर (is40mhz)
		वापस;

	अगर (primarycca->pricca_flag == 0) अणु
		/* Primary channel is above
		 * NOTE: duplicate CTS can हटाओ this condition
		 */
		अगर (sec_ch_offset == 2) अणु
			अगर ((ofdm_cca > OFDMCCA_TH) &&
			    (bw_lsc_cnt > (bw_usc_cnt + BW_IND_BIAS)) &&
			    (ofdm_fa > (ofdm_cca >> 1))) अणु
				primarycca->पूर्णांकf_type = 1;
				primarycca->पूर्णांकf_flag = 1;
				cur_mf_state = MF_USC;
				rtl92ee_dm_ग_लिखो_dynamic_cca(hw, cur_mf_state);
				primarycca->pricca_flag = 1;
			पूर्ण अन्यथा अगर ((ofdm_cca > OFDMCCA_TH) &&
				   (bw_lsc_cnt > (bw_usc_cnt + BW_IND_BIAS)) &&
				   (ofdm_fa < (ofdm_cca >> 1))) अणु
				primarycca->पूर्णांकf_type = 2;
				primarycca->पूर्णांकf_flag = 1;
				cur_mf_state = MF_USC;
				rtl92ee_dm_ग_लिखो_dynamic_cca(hw, cur_mf_state);
				primarycca->pricca_flag = 1;
				primarycca->dup_rts_flag = 1;
				rtlpriv->rtlhal.rts_en = 1;
			पूर्ण अन्यथा अणु
				primarycca->पूर्णांकf_type = 0;
				primarycca->पूर्णांकf_flag = 0;
				cur_mf_state = MF_USC_LSC;
				rtl92ee_dm_ग_लिखो_dynamic_cca(hw, cur_mf_state);
				rtlpriv->rtlhal.rts_en = 0;
				primarycca->dup_rts_flag = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (sec_ch_offset == 1) अणु
			अगर ((ofdm_cca > OFDMCCA_TH) &&
			    (bw_usc_cnt > (bw_lsc_cnt + BW_IND_BIAS)) &&
			    (ofdm_fa > (ofdm_cca >> 1))) अणु
				primarycca->पूर्णांकf_type = 1;
				primarycca->पूर्णांकf_flag = 1;
				cur_mf_state = MF_LSC;
				rtl92ee_dm_ग_लिखो_dynamic_cca(hw, cur_mf_state);
				primarycca->pricca_flag = 1;
			पूर्ण अन्यथा अगर ((ofdm_cca > OFDMCCA_TH) &&
				   (bw_usc_cnt > (bw_lsc_cnt + BW_IND_BIAS)) &&
				   (ofdm_fa < (ofdm_cca >> 1))) अणु
				primarycca->पूर्णांकf_type = 2;
				primarycca->पूर्णांकf_flag = 1;
				cur_mf_state = MF_LSC;
				rtl92ee_dm_ग_लिखो_dynamic_cca(hw, cur_mf_state);
				primarycca->pricca_flag = 1;
				primarycca->dup_rts_flag = 1;
				rtlpriv->rtlhal.rts_en = 1;
			पूर्ण अन्यथा अणु
				primarycca->पूर्णांकf_type = 0;
				primarycca->पूर्णांकf_flag = 0;
				cur_mf_state = MF_USC_LSC;
				rtl92ee_dm_ग_लिखो_dynamic_cca(hw, cur_mf_state);
				rtlpriv->rtlhal.rts_en = 0;
				primarycca->dup_rts_flag = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु/* PrimaryCCA->PriCCA_flag==1 */
		count_करोwn--;
		अगर (count_करोwn == 0) अणु
			count_करोwn = MONITOR_TIME;
			primarycca->pricca_flag = 0;
			cur_mf_state = MF_USC_LSC;
			/* शेष */
			rtl92ee_dm_ग_लिखो_dynamic_cca(hw, cur_mf_state);
			rtlpriv->rtlhal.rts_en = 0;
			primarycca->dup_rts_flag = 0;
			primarycca->पूर्णांकf_type = 0;
			primarycca->पूर्णांकf_flag = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl92ee_dm_dynamic_atc_चयन(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	u8 crystal_cap;
	u32 packet_count;
	पूर्णांक cfo_khz_a , cfo_khz_b , cfo_ave = 0, adjust_xtal = 0;
	पूर्णांक cfo_ave_dअगरf;

	अगर (rtlpriv->mac80211.link_state < MAC80211_LINKED) अणु
		अगर (rtldm->atc_status == ATC_STATUS_OFF) अणु
			rtl_set_bbreg(hw, ROFDM1_CFOTRACKING, BIT(11),
				      ATC_STATUS_ON);
			rtldm->atc_status = ATC_STATUS_ON;
		पूर्ण
		/* Disable CFO tracking क्रम BT */
		अगर (rtlpriv->cfg->ops->get_btc_status()) अणु
			अगर (!rtlpriv->btcoexist.btc_ops->
			    btc_is_bt_disabled(rtlpriv)) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"odm_DynamicATCSwitch(): Disable CFO tracking for BT!!\n");
				वापस;
			पूर्ण
		पूर्ण
		/* Reset Crystal Cap */
		अगर (rtldm->crystal_cap != rtlpriv->efuse.crystalcap) अणु
			rtldm->crystal_cap = rtlpriv->efuse.crystalcap;
			crystal_cap = rtldm->crystal_cap & 0x3f;
			rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0xFFF000,
				      (crystal_cap | (crystal_cap << 6)));
		पूर्ण
	पूर्ण अन्यथा अणु
		cfo_khz_a = (पूर्णांक)(rtldm->cfo_tail[0] * 3125) / 1280;
		cfo_khz_b = (पूर्णांक)(rtldm->cfo_tail[1] * 3125) / 1280;
		packet_count = rtldm->packet_count;

		अगर (packet_count == rtldm->packet_count_pre)
			वापस;

		rtldm->packet_count_pre = packet_count;

		अगर (rtlpriv->phy.rf_type == RF_1T1R)
			cfo_ave = cfo_khz_a;
		अन्यथा
			cfo_ave = (पूर्णांक)(cfo_khz_a + cfo_khz_b) >> 1;

		cfo_ave_dअगरf = (rtldm->cfo_ave_pre >= cfo_ave) ?
			       (rtldm->cfo_ave_pre - cfo_ave) :
			       (cfo_ave - rtldm->cfo_ave_pre);

		अगर (cfo_ave_dअगरf > 20 && !rtldm->large_cfo_hit) अणु
			rtldm->large_cfo_hit = true;
			वापस;
		पूर्ण
		rtldm->large_cfo_hit = false;

		rtldm->cfo_ave_pre = cfo_ave;

		अगर (cfo_ave >= -rtldm->cfo_threshold &&
		    cfo_ave <= rtldm->cfo_threshold && rtldm->is_मुक्तze == 0) अणु
			अगर (rtldm->cfo_threshold == CFO_THRESHOLD_XTAL) अणु
				rtldm->cfo_threshold = CFO_THRESHOLD_XTAL + 10;
				rtldm->is_मुक्तze = 1;
			पूर्ण अन्यथा अणु
				rtldm->cfo_threshold = CFO_THRESHOLD_XTAL;
			पूर्ण
		पूर्ण

		अगर (cfo_ave > rtldm->cfo_threshold && rtldm->crystal_cap < 0x3f)
			adjust_xtal = ((cfo_ave - CFO_THRESHOLD_XTAL) >> 2) + 1;
		अन्यथा अगर ((cfo_ave < -rtlpriv->dm.cfo_threshold) &&
			 rtlpriv->dm.crystal_cap > 0)
			adjust_xtal = ((cfo_ave + CFO_THRESHOLD_XTAL) >> 2) - 1;

		अगर (adjust_xtal != 0) अणु
			rtldm->is_मुक्तze = 0;
			rtldm->crystal_cap += adjust_xtal;

			अगर (rtldm->crystal_cap > 0x3f)
				rtldm->crystal_cap = 0x3f;
			अन्यथा अगर (rtldm->crystal_cap < 0)
				rtldm->crystal_cap = 0;

			crystal_cap = rtldm->crystal_cap & 0x3f;
			rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0xFFF000,
				      (crystal_cap | (crystal_cap << 6)));
		पूर्ण

		अगर (cfo_ave < CFO_THRESHOLD_ATC &&
		    cfo_ave > -CFO_THRESHOLD_ATC) अणु
			अगर (rtldm->atc_status == ATC_STATUS_ON) अणु
				rtl_set_bbreg(hw, ROFDM1_CFOTRACKING, BIT(11),
					      ATC_STATUS_OFF);
				rtldm->atc_status = ATC_STATUS_OFF;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (rtldm->atc_status == ATC_STATUS_OFF) अणु
				rtl_set_bbreg(hw, ROFDM1_CFOTRACKING, BIT(11),
					      ATC_STATUS_ON);
				rtldm->atc_status = ATC_STATUS_ON;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl92ee_dm_init_txघातer_tracking(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_dm *dm = rtl_dm(rtlpriv);
	u8 path;

	dm->txघातer_tracking = true;
	dm->शेष_ofdm_index = 30;
	dm->शेष_cck_index = 20;

	dm->swing_idx_cck_base = dm->शेष_cck_index;
	dm->cck_index = dm->शेष_cck_index;

	क्रम (path = RF90_PATH_A; path < MAX_RF_PATH; path++) अणु
		dm->swing_idx_ofdm_base[path] = dm->शेष_ofdm_index;
		dm->ofdm_index[path] = dm->शेष_ofdm_index;
		dm->delta_घातer_index[path] = 0;
		dm->delta_घातer_index_last[path] = 0;
		dm->घातer_index_offset[path] = 0;
	पूर्ण
पूर्ण

व्योम rtl92ee_dm_init_rate_adaptive_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rate_adaptive *p_ra = &rtlpriv->ra;

	p_ra->ratr_state = DM_RATR_STA_INIT;
	p_ra->pre_ratr_state = DM_RATR_STA_INIT;

	अगर (rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER)
		rtlpriv->dm.useramask = true;
	अन्यथा
		rtlpriv->dm.useramask = false;

	p_ra->ldpc_thres = 35;
	p_ra->use_ldpc = false;
	p_ra->high_rssi_thresh_क्रम_ra = 50;
	p_ra->low_rssi_thresh_क्रम_ra40m = 20;
पूर्ण

अटल bool _rtl92ee_dm_ra_state_check(काष्ठा ieee80211_hw *hw,
				       s32 rssi, u8 *ratr_state)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rate_adaptive *p_ra = &rtlpriv->ra;
	स्थिर u8 go_up_gap = 5;
	u32 high_rssithresh_क्रम_ra = p_ra->high_rssi_thresh_क्रम_ra;
	u32 low_rssithresh_क्रम_ra = p_ra->low_rssi_thresh_क्रम_ra40m;
	u8 state;

	/* Threshold Adjusपंचांगent:
	 * when RSSI state trends to go up one or two levels,
	 * make sure RSSI is high enough.
	 * Here GoUpGap is added to solve
	 * the boundary's level alternation issue.
	 */
	चयन (*ratr_state) अणु
	हाल DM_RATR_STA_INIT:
	हाल DM_RATR_STA_HIGH:
		अवरोध;
	हाल DM_RATR_STA_MIDDLE:
		high_rssithresh_क्रम_ra += go_up_gap;
		अवरोध;
	हाल DM_RATR_STA_LOW:
		high_rssithresh_क्रम_ra += go_up_gap;
		low_rssithresh_क्रम_ra += go_up_gap;
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
			"wrong rssi level setting %d !\n", *ratr_state);
		अवरोध;
	पूर्ण

	/* Decide RATRState by RSSI. */
	अगर (rssi > high_rssithresh_क्रम_ra)
		state = DM_RATR_STA_HIGH;
	अन्यथा अगर (rssi > low_rssithresh_क्रम_ra)
		state = DM_RATR_STA_MIDDLE;
	अन्यथा
		state = DM_RATR_STA_LOW;

	अगर (*ratr_state != state) अणु
		*ratr_state = state;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम rtl92ee_dm_refresh_rate_adaptive_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rate_adaptive *p_ra = &rtlpriv->ra;
	काष्ठा ieee80211_sta *sta = शून्य;

	अगर (is_hal_stop(rtlhal)) अणु
		rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
			"driver is going to unload\n");
		वापस;
	पूर्ण

	अगर (!rtlpriv->dm.useramask) अणु
		rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
			"driver does not control rate adaptive mask\n");
		वापस;
	पूर्ण

	अगर (mac->link_state == MAC80211_LINKED &&
	    mac->opmode == NL80211_IFTYPE_STATION) अणु
		अगर (rtlpriv->dm.undec_sm_pwdb < p_ra->ldpc_thres) अणु
			p_ra->use_ldpc = true;
			p_ra->lower_rts_rate = true;
		पूर्ण अन्यथा अगर (rtlpriv->dm.undec_sm_pwdb >
			   (p_ra->ldpc_thres - 5)) अणु
			p_ra->use_ldpc = false;
			p_ra->lower_rts_rate = false;
		पूर्ण
		अगर (_rtl92ee_dm_ra_state_check(hw, rtlpriv->dm.undec_sm_pwdb,
					       &p_ra->ratr_state)) अणु
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

अटल व्योम rtl92ee_dm_init_dynamic_atc_चयन(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.crystal_cap = rtlpriv->efuse.crystalcap;

	rtlpriv->dm.atc_status = rtl_get_bbreg(hw, ROFDM1_CFOTRACKING, BIT(11));
	rtlpriv->dm.cfo_threshold = CFO_THRESHOLD_XTAL;
पूर्ण

व्योम rtl92ee_dm_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 cur_igvalue = rtl_get_bbreg(hw, DM_REG_IGI_A_11N, DM_BIT_IGI_11N);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;

	rtl_dm_diginit(hw, cur_igvalue);
	rtl92ee_dm_init_rate_adaptive_mask(hw);
	rtl92ee_dm_init_primary_cca_check(hw);
	rtl92ee_dm_init_edca_turbo(hw);
	rtl92ee_dm_init_txघातer_tracking(hw);
	rtl92ee_dm_init_dynamic_atc_चयन(hw);
पूर्ण

अटल व्योम rtl92ee_dm_common_info_self_update(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_sta_info *drv_priv;
	u8 cnt = 0;

	rtlpriv->dm.one_entry_only = false;

	अगर (rtlpriv->mac80211.opmode == NL80211_IFTYPE_STATION &&
	    rtlpriv->mac80211.link_state >= MAC80211_LINKED) अणु
		rtlpriv->dm.one_entry_only = true;
		वापस;
	पूर्ण

	अगर (rtlpriv->mac80211.opmode == NL80211_IFTYPE_AP ||
	    rtlpriv->mac80211.opmode == NL80211_IFTYPE_ADHOC ||
	    rtlpriv->mac80211.opmode == NL80211_IFTYPE_MESH_POINT) अणु
		spin_lock_bh(&rtlpriv->locks.entry_list_lock);
		list_क्रम_each_entry(drv_priv, &rtlpriv->entry_list, list) अणु
			cnt++;
		पूर्ण
		spin_unlock_bh(&rtlpriv->locks.entry_list_lock);

		अगर (cnt == 1)
			rtlpriv->dm.one_entry_only = true;
	पूर्ण
पूर्ण

व्योम rtl92ee_dm_dynamic_arfb_select(काष्ठा ieee80211_hw *hw,
				    u8 rate, bool collision_state)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rate >= DESC92C_RATEMCS8  && rate <= DESC92C_RATEMCS12) अणु
		अगर (collision_state == 1) अणु
			अगर (rate == DESC92C_RATEMCS12) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC, 0x0);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x07060501);
			पूर्ण अन्यथा अगर (rate == DESC92C_RATEMCS11) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC, 0x0);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x07070605);
			पूर्ण अन्यथा अगर (rate == DESC92C_RATEMCS10) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC, 0x0);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x08080706);
			पूर्ण अन्यथा अगर (rate == DESC92C_RATEMCS9) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC, 0x0);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x08080707);
			पूर्ण अन्यथा अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC, 0x0);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x09090808);
			पूर्ण
		पूर्ण अन्यथा अणु   /* collision_state == 0 */
			अगर (rate == DESC92C_RATEMCS12) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x05010000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x09080706);
			पूर्ण अन्यथा अगर (rate == DESC92C_RATEMCS11) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x06050000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x09080807);
			पूर्ण अन्यथा अगर (rate == DESC92C_RATEMCS10) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x07060000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x0a090908);
			पूर्ण अन्यथा अगर (rate == DESC92C_RATEMCS9) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x07070000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x0a090808);
			पूर्ण अन्यथा अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x08080000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x0b0a0909);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु  /* MCS13~MCS15,  1SS, G-mode */
		अगर (collision_state == 1) अणु
			अगर (rate == DESC92C_RATEMCS15) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x00000000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x05040302);
			पूर्ण अन्यथा अगर (rate == DESC92C_RATEMCS14) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x00000000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x06050302);
			पूर्ण अन्यथा अगर (rate == DESC92C_RATEMCS13) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x00000000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x07060502);
			पूर्ण अन्यथा अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x00000000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x06050402);
			पूर्ण
		पूर्ण अन्यथाअणु   /* collision_state == 0 */
			अगर (rate == DESC92C_RATEMCS15) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x03020000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x07060504);
			पूर्ण अन्यथा अगर (rate == DESC92C_RATEMCS14) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x03020000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x08070605);
			पूर्ण अन्यथा अगर (rate == DESC92C_RATEMCS13) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x05020000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x09080706);
			पूर्ण अन्यथा अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC,
						0x04020000);
				rtl_ग_लिखो_dword(rtlpriv, REG_DARFRC + 4,
						0x08070605);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl92ee_dm_watchकरोg(काष्ठा ieee80211_hw *hw)
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
		rtl92ee_dm_common_info_self_update(hw);
		rtl92ee_dm_false_alarm_counter_statistics(hw);
		rtl92ee_dm_check_rssi_monitor(hw);
		rtl92ee_dm_dig(hw);
		rtl92ee_dm_adaptivity(hw);
		rtl92ee_dm_cck_packet_detection_thresh(hw);
		rtl92ee_dm_refresh_rate_adaptive_mask(hw);
		rtl92ee_dm_check_edca_turbo(hw);
		rtl92ee_dm_dynamic_atc_चयन(hw);
		rtl92ee_dm_dynamic_primary_cca_ckeck(hw);
	पूर्ण
	spin_unlock(&rtlpriv->locks.rf_ps_lock);
पूर्ण
