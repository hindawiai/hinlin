<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "stats.h"
#समावेश <linux/export.h>

u8 rtl_query_rxpwrpercentage(s8 antघातer)
अणु
	अगर ((antघातer <= -100) || (antघातer >= 20))
		वापस 0;
	अन्यथा अगर (antघातer >= 0)
		वापस 100;
	अन्यथा
		वापस 100 + antघातer;
पूर्ण
EXPORT_SYMBOL(rtl_query_rxpwrpercentage);

u8 rtl_evm_db_to_percentage(s8 value)
अणु
	s8 ret_val = clamp(-value, 0, 33) * 3;

	अगर (ret_val == 99)
		ret_val = 100;

	वापस ret_val;
पूर्ण
EXPORT_SYMBOL(rtl_evm_db_to_percentage);

अटल दीर्घ rtl_translate_todbm(काष्ठा ieee80211_hw *hw,
			 u8 संकेत_strength_index)
अणु
	दीर्घ संकेत_घातer;

	संकेत_घातer = (दीर्घ)((संकेत_strength_index + 1) >> 1);
	संकेत_घातer -= 95;
	वापस संकेत_घातer;
पूर्ण

दीर्घ rtl_संकेत_scale_mapping(काष्ठा ieee80211_hw *hw, दीर्घ currsig)
अणु
	दीर्घ retsig;

	अगर (currsig >= 61 && currsig <= 100)
		retsig = 90 + ((currsig - 60) / 4);
	अन्यथा अगर (currsig >= 41 && currsig <= 60)
		retsig = 78 + ((currsig - 40) / 2);
	अन्यथा अगर (currsig >= 31 && currsig <= 40)
		retsig = 66 + (currsig - 30);
	अन्यथा अगर (currsig >= 21 && currsig <= 30)
		retsig = 54 + (currsig - 20);
	अन्यथा अगर (currsig >= 5 && currsig <= 20)
		retsig = 42 + (((currsig - 5) * 2) / 3);
	अन्यथा अगर (currsig == 4)
		retsig = 36;
	अन्यथा अगर (currsig == 3)
		retsig = 27;
	अन्यथा अगर (currsig == 2)
		retsig = 18;
	अन्यथा अगर (currsig == 1)
		retsig = 9;
	अन्यथा
		retsig = currsig;

	वापस retsig;
पूर्ण
EXPORT_SYMBOL(rtl_संकेत_scale_mapping);

अटल व्योम rtl_process_ui_rssi(काष्ठा ieee80211_hw *hw,
				काष्ठा rtl_stats *pstatus)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 rfpath;
	u32 last_rssi, पंचांगpval;

	अगर (!pstatus->packet_toself && !pstatus->packet_beacon)
		वापस;

	rtlpriv->stats.pwdb_all_cnt += pstatus->rx_pwdb_all;
	rtlpriv->stats.rssi_calculate_cnt++;

	अगर (rtlpriv->stats.ui_rssi.total_num++ >= PHY_RSSI_SLID_WIN_MAX) अणु
		rtlpriv->stats.ui_rssi.total_num = PHY_RSSI_SLID_WIN_MAX;
		last_rssi = rtlpriv->stats.ui_rssi.elements[
			rtlpriv->stats.ui_rssi.index];
		rtlpriv->stats.ui_rssi.total_val -= last_rssi;
	पूर्ण
	rtlpriv->stats.ui_rssi.total_val += pstatus->संकेतstrength;
	rtlpriv->stats.ui_rssi.elements[rtlpriv->stats.ui_rssi.index++] =
	    pstatus->संकेतstrength;
	अगर (rtlpriv->stats.ui_rssi.index >= PHY_RSSI_SLID_WIN_MAX)
		rtlpriv->stats.ui_rssi.index = 0;
	पंचांगpval = rtlpriv->stats.ui_rssi.total_val /
		rtlpriv->stats.ui_rssi.total_num;
	rtlpriv->stats.संकेत_strength = rtl_translate_todbm(hw,
		(u8) पंचांगpval);
	pstatus->rssi = rtlpriv->stats.संकेत_strength;

	अगर (pstatus->is_cck)
		वापस;

	क्रम (rfpath = RF90_PATH_A; rfpath < rtlphy->num_total_rfpath;
	     rfpath++) अणु
		अगर (rtlpriv->stats.rx_rssi_percentage[rfpath] == 0) अणु
			rtlpriv->stats.rx_rssi_percentage[rfpath] =
			    pstatus->rx_mimo_संकेतstrength[rfpath];

		पूर्ण
		अगर (pstatus->rx_mimo_संकेतstrength[rfpath] >
		    rtlpriv->stats.rx_rssi_percentage[rfpath]) अणु
			rtlpriv->stats.rx_rssi_percentage[rfpath] =
			    ((rtlpriv->stats.rx_rssi_percentage[rfpath] *
			      (RX_SMOOTH_FACTOR - 1)) +
			     (pstatus->rx_mimo_संकेतstrength[rfpath])) /
			    (RX_SMOOTH_FACTOR);
			rtlpriv->stats.rx_rssi_percentage[rfpath] =
			    rtlpriv->stats.rx_rssi_percentage[rfpath] + 1;
		पूर्ण अन्यथा अणु
			rtlpriv->stats.rx_rssi_percentage[rfpath] =
			    ((rtlpriv->stats.rx_rssi_percentage[rfpath] *
			      (RX_SMOOTH_FACTOR - 1)) +
			     (pstatus->rx_mimo_संकेतstrength[rfpath])) /
			    (RX_SMOOTH_FACTOR);
		पूर्ण
		rtlpriv->stats.rx_snr_db[rfpath] = pstatus->rx_snr[rfpath];
		rtlpriv->stats.rx_evm_dbm[rfpath] =
					pstatus->rx_mimo_evm_dbm[rfpath];
		rtlpriv->stats.rx_cfo_लघु[rfpath] =
					pstatus->cfo_लघु[rfpath];
		rtlpriv->stats.rx_cfo_tail[rfpath] = pstatus->cfo_tail[rfpath];
	पूर्ण
पूर्ण

अटल व्योम rtl_update_rxसंकेतstatistics(काष्ठा ieee80211_hw *hw,
					  काष्ठा rtl_stats *pstatus)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक weighting = 0;

	अगर (rtlpriv->stats.recv_संकेत_घातer == 0)
		rtlpriv->stats.recv_संकेत_घातer = pstatus->recvसंकेतघातer;
	अगर (pstatus->recvसंकेतघातer > rtlpriv->stats.recv_संकेत_घातer)
		weighting = 5;
	अन्यथा अगर (pstatus->recvसंकेतघातer < rtlpriv->stats.recv_संकेत_घातer)
		weighting = (-5);
	rtlpriv->stats.recv_संकेत_घातer = (rtlpriv->stats.recv_संकेत_घातer *
		5 + pstatus->recvसंकेतघातer + weighting) / 6;
पूर्ण

अटल व्योम rtl_process_pwdb(काष्ठा ieee80211_hw *hw, काष्ठा rtl_stats *pstatus)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_sta_info *drv_priv = शून्य;
	काष्ठा ieee80211_sta *sta = शून्य;
	दीर्घ undec_sm_pwdb;

	rcu_पढ़ो_lock();
	अगर (rtlpriv->mac80211.opmode != NL80211_IFTYPE_STATION)
		sta = rtl_find_sta(hw, pstatus->psaddr);

	/* adhoc or ap mode */
	अगर (sta) अणु
		drv_priv = (काष्ठा rtl_sta_info *) sta->drv_priv;
		undec_sm_pwdb = drv_priv->rssi_stat.undec_sm_pwdb;
	पूर्ण अन्यथा अणु
		undec_sm_pwdb = rtlpriv->dm.undec_sm_pwdb;
	पूर्ण

	अगर (undec_sm_pwdb < 0)
		undec_sm_pwdb = pstatus->rx_pwdb_all;
	अगर (pstatus->rx_pwdb_all > (u32) undec_sm_pwdb) अणु
		undec_sm_pwdb = (((undec_sm_pwdb) *
		      (RX_SMOOTH_FACTOR - 1)) +
		     (pstatus->rx_pwdb_all)) / (RX_SMOOTH_FACTOR);
		undec_sm_pwdb = undec_sm_pwdb + 1;
	पूर्ण अन्यथा अणु
		undec_sm_pwdb = (((undec_sm_pwdb) *
		      (RX_SMOOTH_FACTOR - 1)) +
		     (pstatus->rx_pwdb_all)) / (RX_SMOOTH_FACTOR);
	पूर्ण

	अगर (sta) अणु
		drv_priv->rssi_stat.undec_sm_pwdb = undec_sm_pwdb;
	पूर्ण अन्यथा अणु
		rtlpriv->dm.undec_sm_pwdb = undec_sm_pwdb;
	पूर्ण
	rcu_पढ़ो_unlock();

	rtl_update_rxसंकेतstatistics(hw, pstatus);
पूर्ण

अटल व्योम rtl_process_ui_link_quality(काष्ठा ieee80211_hw *hw,
					काष्ठा rtl_stats *pstatus)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 last_evm, n_stream, पंचांगpval;

	अगर (pstatus->संकेतquality == 0)
		वापस;

	अगर (rtlpriv->stats.ui_link_quality.total_num++ >=
	    PHY_LINKQUALITY_SLID_WIN_MAX) अणु
		rtlpriv->stats.ui_link_quality.total_num =
		    PHY_LINKQUALITY_SLID_WIN_MAX;
		last_evm = rtlpriv->stats.ui_link_quality.elements[
			rtlpriv->stats.ui_link_quality.index];
		rtlpriv->stats.ui_link_quality.total_val -= last_evm;
	पूर्ण
	rtlpriv->stats.ui_link_quality.total_val += pstatus->संकेतquality;
	rtlpriv->stats.ui_link_quality.elements[
		rtlpriv->stats.ui_link_quality.index++] =
							pstatus->संकेतquality;
	अगर (rtlpriv->stats.ui_link_quality.index >=
	    PHY_LINKQUALITY_SLID_WIN_MAX)
		rtlpriv->stats.ui_link_quality.index = 0;
	पंचांगpval = rtlpriv->stats.ui_link_quality.total_val /
	    rtlpriv->stats.ui_link_quality.total_num;
	rtlpriv->stats.संकेत_quality = पंचांगpval;
	rtlpriv->stats.last_sigstrength_inpercent = पंचांगpval;
	क्रम (n_stream = 0; n_stream < 2; n_stream++) अणु
		अगर (pstatus->rx_mimo_sig_qual[n_stream] != -1) अणु
			अगर (rtlpriv->stats.rx_evm_percentage[n_stream] == 0) अणु
				rtlpriv->stats.rx_evm_percentage[n_stream] =
				    pstatus->rx_mimo_sig_qual[n_stream];
			पूर्ण
			rtlpriv->stats.rx_evm_percentage[n_stream] =
			    ((rtlpriv->stats.rx_evm_percentage[n_stream]
			      * (RX_SMOOTH_FACTOR - 1)) +
			     (pstatus->rx_mimo_sig_qual[n_stream] * 1)) /
			    (RX_SMOOTH_FACTOR);
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl_process_phyinfo(काष्ठा ieee80211_hw *hw, u8 *buffer,
			 काष्ठा rtl_stats *pstatus)
अणु

	अगर (!pstatus->packet_matchbssid)
		वापस;

	rtl_process_ui_rssi(hw, pstatus);
	rtl_process_pwdb(hw, pstatus);
	rtl_process_ui_link_quality(hw, pstatus);
पूर्ण
EXPORT_SYMBOL(rtl_process_phyinfo);
