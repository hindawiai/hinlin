<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "base.h"
#समावेश "rc.h"

/*
 *Finds the highest rate index we can use
 *अगर skb is special data like DHCP/EAPOL, we set should
 *it to lowest rate CCK_1M, otherwise we set rate to
 *highest rate based on wireless mode used क्रम iwconfig
 *show Tx rate.
 */
अटल u8 _rtl_rc_get_highest_rix(काष्ठा rtl_priv *rtlpriv,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा sk_buff *skb, bool not_data)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u16 wireless_mode = 0;
	u8 nss;
	काष्ठा ieee80211_tx_rate rate;

	चयन (get_rf_type(rtlphy)) अणु
	हाल RF_4T4R:
		nss = 4;
		अवरोध;
	हाल RF_3T3R:
		nss = 3;
		अवरोध;
	हाल RF_2T2R:
		nss = 2;
		अवरोध;
	शेष:
		nss = 1;
		अवरोध;
	पूर्ण

	/*
	 *this rate is no use क्रम true rate, firmware
	 *will control rate at all it just used क्रम
	 *1.show in iwconfig in B/G mode
	 *2.in rtl_get_tcb_desc when we check rate is
	 *      1M we will not use FW rate but user rate.
	 */

	अगर (sta) अणु
		sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
		wireless_mode = sta_entry->wireless_mode;
	पूर्ण

	अगर (rtl_is_special_data(rtlpriv->mac80211.hw, skb, true, false) ||
	    not_data) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
			अगर (wireless_mode == WIRELESS_MODE_B) अणु
				वापस B_MODE_MAX_RIX;
			पूर्ण अन्यथा अगर (wireless_mode == WIRELESS_MODE_G) अणु
				वापस G_MODE_MAX_RIX;
			पूर्ण अन्यथा अगर (wireless_mode == WIRELESS_MODE_N_24G) अणु
				अगर (nss == 1)
					वापस N_MODE_MCS7_RIX;
				अन्यथा
					वापस N_MODE_MCS15_RIX;
			पूर्ण अन्यथा अगर (wireless_mode == WIRELESS_MODE_AC_24G) अणु
				अगर (sta->bandwidth == IEEE80211_STA_RX_BW_20) अणु
					ieee80211_rate_set_vht(&rate,
							       AC_MODE_MCS8_RIX,
							       nss);
					जाओ out;
				पूर्ण अन्यथा अणु
					ieee80211_rate_set_vht(&rate,
							       AC_MODE_MCS9_RIX,
							       nss);
					जाओ out;
				पूर्ण
			पूर्ण
			वापस 0;
		पूर्ण अन्यथा अणु
			अगर (wireless_mode == WIRELESS_MODE_A) अणु
				वापस A_MODE_MAX_RIX;
			पूर्ण अन्यथा अगर (wireless_mode == WIRELESS_MODE_N_5G) अणु
				अगर (nss == 1)
					वापस N_MODE_MCS7_RIX;
				अन्यथा
					वापस N_MODE_MCS15_RIX;
			पूर्ण अन्यथा अगर (wireless_mode == WIRELESS_MODE_AC_5G) अणु
				अगर (sta->bandwidth == IEEE80211_STA_RX_BW_20) अणु
					ieee80211_rate_set_vht(&rate,
							       AC_MODE_MCS8_RIX,
							       nss);
					जाओ out;
				पूर्ण अन्यथा अणु
					ieee80211_rate_set_vht(&rate,
							       AC_MODE_MCS9_RIX,
							       nss);
					जाओ out;
				पूर्ण
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण

out:
	वापस rate.idx;
पूर्ण

अटल व्योम _rtl_rc_rate_set_series(काष्ठा rtl_priv *rtlpriv,
				    काष्ठा ieee80211_sta *sta,
				    काष्ठा ieee80211_tx_rate *rate,
				    काष्ठा ieee80211_tx_rate_control *txrc,
				    u8 tries, s8 rix, पूर्णांक rtsctsenable,
				    bool not_data)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u16 wireless_mode = 0;
	u8 sgi_20 = 0, sgi_40 = 0, sgi_80 = 0;

	अगर (sta) अणु
		sgi_20 = sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20;
		sgi_40 = sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40;
		sgi_80 = sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_80;
		sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
		wireless_mode = sta_entry->wireless_mode;
	पूर्ण
	rate->count = tries;
	rate->idx = rix >= 0x00 ? rix : 0x00;

	अगर (!not_data) अणु
		अगर (txrc->लघु_preamble)
			rate->flags |= IEEE80211_TX_RC_USE_SHORT_PREAMBLE;
		अगर (mac->opmode == NL80211_IFTYPE_AP ||
			mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			अगर (sta && (sta->ht_cap.cap &
				    IEEE80211_HT_CAP_SUP_WIDTH_20_40))
				rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
			अगर (sta && sta->vht_cap.vht_supported)
				rate->flags |= IEEE80211_TX_RC_80_MHZ_WIDTH;
		पूर्ण अन्यथा अणु
			अगर (mac->bw_80)
				rate->flags |= IEEE80211_TX_RC_80_MHZ_WIDTH;
			अन्यथा अगर (mac->bw_40)
				rate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
		पूर्ण

		अगर (sgi_20 || sgi_40 || sgi_80)
			rate->flags |= IEEE80211_TX_RC_SHORT_GI;
		अगर (sta && sta->ht_cap.ht_supported &&
		    (wireless_mode == WIRELESS_MODE_N_5G ||
		     wireless_mode == WIRELESS_MODE_N_24G))
			rate->flags |= IEEE80211_TX_RC_MCS;
		अगर (sta && sta->vht_cap.vht_supported &&
		    (wireless_mode == WIRELESS_MODE_AC_5G ||
		     wireless_mode == WIRELESS_MODE_AC_24G ||
		     wireless_mode == WIRELESS_MODE_AC_ONLY))
			rate->flags |= IEEE80211_TX_RC_VHT_MCS;
	पूर्ण
पूर्ण

अटल व्योम rtl_get_rate(व्योम *ppriv, काष्ठा ieee80211_sta *sta,
			 व्योम *priv_sta,
			 काष्ठा ieee80211_tx_rate_control *txrc)
अणु
	काष्ठा rtl_priv *rtlpriv = ppriv;
	काष्ठा sk_buff *skb = txrc->skb;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_tx_rate *rates = tx_info->control.rates;
	__le16 fc = rtl_get_fc(skb);
	u8 try_per_rate, i, rix;
	bool not_data = !ieee80211_is_data(fc);

	rix = _rtl_rc_get_highest_rix(rtlpriv, sta, skb, not_data);
	try_per_rate = 1;
	_rtl_rc_rate_set_series(rtlpriv, sta, &rates[0], txrc,
				try_per_rate, rix, 1, not_data);

	अगर (!not_data) अणु
		क्रम (i = 1; i < 4; i++)
			_rtl_rc_rate_set_series(rtlpriv, sta, &rates[i],
						txrc, i, (rix - i), 1,
						not_data);
	पूर्ण
पूर्ण

अटल bool _rtl_tx_aggr_check(काष्ठा rtl_priv *rtlpriv,
			       काष्ठा rtl_sta_info *sta_entry, u16 tid)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);

	अगर (mac->act_scanning)
		वापस false;

	अगर (mac->opmode == NL80211_IFTYPE_STATION &&
	    mac->cnt_after_linked < 3)
		वापस false;

	अगर (sta_entry->tids[tid].agg.agg_state == RTL_AGG_STOP)
		वापस true;

	वापस false;
पूर्ण

/*mac80211 Rate Control callbacks*/
अटल व्योम rtl_tx_status(व्योम *ppriv,
			  काष्ठा ieee80211_supported_band *sband,
			  काष्ठा ieee80211_sta *sta, व्योम *priv_sta,
			  काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = ppriv;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);
	काष्ठा ieee80211_hdr *hdr = rtl_get_hdr(skb);
	__le16 fc = rtl_get_fc(skb);
	काष्ठा rtl_sta_info *sta_entry;

	अगर (!priv_sta || !ieee80211_is_data(fc))
		वापस;

	अगर (rtl_is_special_data(mac->hw, skb, true, true))
		वापस;

	अगर (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr)))
		वापस;

	अगर (sta) अणु
		/* Check अगर aggregation has to be enabled क्रम this tid */
		sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
		अगर (sta->ht_cap.ht_supported &&
		    !(skb->protocol == cpu_to_be16(ETH_P_PAE))) अणु
			अगर (ieee80211_is_data_qos(fc)) अणु
				u8 tid = rtl_get_tid(skb);

				अगर (_rtl_tx_aggr_check(rtlpriv, sta_entry,
						       tid)) अणु
					sta_entry->tids[tid].agg.agg_state =
						RTL_AGG_PROGRESS;
					ieee80211_start_tx_ba_session(sta, tid,
								      5000);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl_rate_init(व्योम *ppriv,
			  काष्ठा ieee80211_supported_band *sband,
			  काष्ठा cfg80211_chan_def *chandef,
			  काष्ठा ieee80211_sta *sta, व्योम *priv_sta)
अणु
पूर्ण

अटल व्योम rtl_rate_update(व्योम *ppriv,
			    काष्ठा ieee80211_supported_band *sband,
			    काष्ठा cfg80211_chan_def *chandef,
			    काष्ठा ieee80211_sta *sta, व्योम *priv_sta,
			    u32 changed)
अणु
पूर्ण

अटल व्योम *rtl_rate_alloc(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	वापस rtlpriv;
पूर्ण

अटल व्योम rtl_rate_मुक्त(व्योम *rtlpriv)
अणु
	वापस;
पूर्ण

अटल व्योम *rtl_rate_alloc_sta(व्योम *ppriv,
				काष्ठा ieee80211_sta *sta, gfp_t gfp)
अणु
	काष्ठा rtl_priv *rtlpriv = ppriv;
	काष्ठा rtl_rate_priv *rate_priv;

	rate_priv = kzalloc(माप(*rate_priv), gfp);
	अगर (!rate_priv)
		वापस शून्य;

	rtlpriv->rate_priv = rate_priv;

	वापस rate_priv;
पूर्ण

अटल व्योम rtl_rate_मुक्त_sta(व्योम *rtlpriv,
			      काष्ठा ieee80211_sta *sta, व्योम *priv_sta)
अणु
	काष्ठा rtl_rate_priv *rate_priv = priv_sta;

	kमुक्त(rate_priv);
पूर्ण

अटल स्थिर काष्ठा rate_control_ops rtl_rate_ops = अणु
	.name = "rtl_rc",
	.alloc = rtl_rate_alloc,
	.मुक्त = rtl_rate_मुक्त,
	.alloc_sta = rtl_rate_alloc_sta,
	.मुक्त_sta = rtl_rate_मुक्त_sta,
	.rate_init = rtl_rate_init,
	.rate_update = rtl_rate_update,
	.tx_status = rtl_tx_status,
	.get_rate = rtl_get_rate,
पूर्ण;

पूर्णांक rtl_rate_control_रेजिस्टर(व्योम)
अणु
	वापस ieee80211_rate_control_रेजिस्टर(&rtl_rate_ops);
पूर्ण

व्योम rtl_rate_control_unरेजिस्टर(व्योम)
अणु
	ieee80211_rate_control_unरेजिस्टर(&rtl_rate_ops);
पूर्ण
