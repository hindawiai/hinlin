<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mac80211 TDLS handling code
 *
 * Copyright 2006-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2014, Intel Corporation
 * Copyright 2014  Intel Mobile Communications GmbH
 * Copyright 2015 - 2016 Intel Deutschland GmbH
 * Copyright (C) 2019 Intel Corporation
 */

#समावेश <linux/ieee80211.h>
#समावेश <linux/log2.h>
#समावेश <net/cfg80211.h>
#समावेश <linux/rtnetlink.h>
#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "rate.h"
#समावेश "wme.h"

/* give usermode some समय क्रम retries in setting up the TDLS session */
#घोषणा TDLS_PEER_SETUP_TIMEOUT	(15 * HZ)

व्योम ieee80211_tdls_peer_del_work(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_local *local;

	sdata = container_of(wk, काष्ठा ieee80211_sub_अगर_data,
			     u.mgd.tdls_peer_del_work.work);
	local = sdata->local;

	mutex_lock(&local->mtx);
	अगर (!is_zero_ether_addr(sdata->u.mgd.tdls_peer)) अणु
		tdls_dbg(sdata, "TDLS del peer %pM\n", sdata->u.mgd.tdls_peer);
		sta_info_destroy_addr(sdata, sdata->u.mgd.tdls_peer);
		eth_zero_addr(sdata->u.mgd.tdls_peer);
	पूर्ण
	mutex_unlock(&local->mtx);
पूर्ण

अटल व्योम ieee80211_tdls_add_ext_capab(काष्ठा ieee80211_sub_अगर_data *sdata,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	bool chan_चयन = local->hw.wiphy->features &
			   NL80211_FEATURE_TDLS_CHANNEL_SWITCH;
	bool wider_band = ieee80211_hw_check(&local->hw, TDLS_WIDER_BW) &&
			  !अगरmgd->tdls_wider_bw_prohibited;
	bool buffer_sta = ieee80211_hw_check(&local->hw,
					     SUPPORTS_TDLS_BUFFER_STA);
	काष्ठा ieee80211_supported_band *sband = ieee80211_get_sband(sdata);
	bool vht = sband && sband->vht_cap.vht_supported;
	u8 *pos = skb_put(skb, 10);

	*pos++ = WLAN_EID_EXT_CAPABILITY;
	*pos++ = 8; /* len */
	*pos++ = 0x0;
	*pos++ = 0x0;
	*pos++ = 0x0;
	*pos++ = (chan_चयन ? WLAN_EXT_CAPA4_TDLS_CHAN_SWITCH : 0) |
		 (buffer_sta ? WLAN_EXT_CAPA4_TDLS_BUFFER_STA : 0);
	*pos++ = WLAN_EXT_CAPA5_TDLS_ENABLED;
	*pos++ = 0;
	*pos++ = 0;
	*pos++ = (vht && wider_band) ? WLAN_EXT_CAPA8_TDLS_WIDE_BW_ENABLED : 0;
पूर्ण

अटल u8
ieee80211_tdls_add_subband(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा sk_buff *skb, u16 start, u16 end,
			   u16 spacing)
अणु
	u8 subband_cnt = 0, ch_cnt = 0;
	काष्ठा ieee80211_channel *ch;
	काष्ठा cfg80211_chan_def chandef;
	पूर्णांक i, subband_start;
	काष्ठा wiphy *wiphy = sdata->local->hw.wiphy;

	क्रम (i = start; i <= end; i += spacing) अणु
		अगर (!ch_cnt)
			subband_start = i;

		ch = ieee80211_get_channel(sdata->local->hw.wiphy, i);
		अगर (ch) अणु
			/* we will be active on the channel */
			cfg80211_chandef_create(&chandef, ch,
						NL80211_CHAN_NO_HT);
			अगर (cfg80211_reg_can_beacon_relax(wiphy, &chandef,
							  sdata->wdev.अगरtype)) अणु
				ch_cnt++;
				/*
				 * check अगर the next channel is also part of
				 * this allowed range
				 */
				जारी;
			पूर्ण
		पूर्ण

		/*
		 * we've reached the end of a range, with allowed channels
		 * found
		 */
		अगर (ch_cnt) अणु
			u8 *pos = skb_put(skb, 2);
			*pos++ = ieee80211_frequency_to_channel(subband_start);
			*pos++ = ch_cnt;

			subband_cnt++;
			ch_cnt = 0;
		पूर्ण
	पूर्ण

	/* all channels in the requested range are allowed - add them here */
	अगर (ch_cnt) अणु
		u8 *pos = skb_put(skb, 2);
		*pos++ = ieee80211_frequency_to_channel(subband_start);
		*pos++ = ch_cnt;

		subband_cnt++;
	पूर्ण

	वापस subband_cnt;
पूर्ण

अटल व्योम
ieee80211_tdls_add_supp_channels(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sk_buff *skb)
अणु
	/*
	 * Add possible channels क्रम TDLS. These are channels that are allowed
	 * to be active.
	 */
	u8 subband_cnt;
	u8 *pos = skb_put(skb, 2);

	*pos++ = WLAN_EID_SUPPORTED_CHANNELS;

	/*
	 * 5GHz and 2GHz channels numbers can overlap. Ignore this क्रम now, as
	 * this करोesn't happen in real world scenarios.
	 */

	/* 2GHz, with 5MHz spacing */
	subband_cnt = ieee80211_tdls_add_subband(sdata, skb, 2412, 2472, 5);

	/* 5GHz, with 20MHz spacing */
	subband_cnt += ieee80211_tdls_add_subband(sdata, skb, 5000, 5825, 20);

	/* length */
	*pos = 2 * subband_cnt;
पूर्ण

अटल व्योम ieee80211_tdls_add_oper_classes(काष्ठा ieee80211_sub_अगर_data *sdata,
					    काष्ठा sk_buff *skb)
अणु
	u8 *pos;
	u8 op_class;

	अगर (!ieee80211_chandef_to_operating_class(&sdata->vअगर.bss_conf.chandef,
						  &op_class))
		वापस;

	pos = skb_put(skb, 4);
	*pos++ = WLAN_EID_SUPPORTED_REGULATORY_CLASSES;
	*pos++ = 2; /* len */

	*pos++ = op_class;
	*pos++ = op_class; /* give current operating class as alternate too */
पूर्ण

अटल व्योम ieee80211_tdls_add_bss_coex_ie(काष्ठा sk_buff *skb)
अणु
	u8 *pos = skb_put(skb, 3);

	*pos++ = WLAN_EID_BSS_COEX_2040;
	*pos++ = 1; /* len */

	*pos++ = WLAN_BSS_COEX_INFORMATION_REQUEST;
पूर्ण

अटल u16 ieee80211_get_tdls_sta_capab(काष्ठा ieee80211_sub_अगर_data *sdata,
					u16 status_code)
अणु
	काष्ठा ieee80211_supported_band *sband;

	/* The capability will be 0 when sending a failure code */
	अगर (status_code != 0)
		वापस 0;

	sband = ieee80211_get_sband(sdata);
	अगर (sband && sband->band == NL80211_BAND_2GHZ) अणु
		वापस WLAN_CAPABILITY_SHORT_SLOT_TIME |
		       WLAN_CAPABILITY_SHORT_PREAMBLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ieee80211_tdls_add_link_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा sk_buff *skb, स्थिर u8 *peer,
				       bool initiator)
अणु
	काष्ठा ieee80211_tdls_lnkie *lnkid;
	स्थिर u8 *init_addr, *rsp_addr;

	अगर (initiator) अणु
		init_addr = sdata->vअगर.addr;
		rsp_addr = peer;
	पूर्ण अन्यथा अणु
		init_addr = peer;
		rsp_addr = sdata->vअगर.addr;
	पूर्ण

	lnkid = skb_put(skb, माप(काष्ठा ieee80211_tdls_lnkie));

	lnkid->ie_type = WLAN_EID_LINK_ID;
	lnkid->ie_len = माप(काष्ठा ieee80211_tdls_lnkie) - 2;

	स_नकल(lnkid->bssid, sdata->u.mgd.bssid, ETH_ALEN);
	स_नकल(lnkid->init_sta, init_addr, ETH_ALEN);
	स_नकल(lnkid->resp_sta, rsp_addr, ETH_ALEN);
पूर्ण

अटल व्योम
ieee80211_tdls_add_aid(काष्ठा ieee80211_sub_अगर_data *sdata, काष्ठा sk_buff *skb)
अणु
	u8 *pos = skb_put(skb, 4);

	*pos++ = WLAN_EID_AID;
	*pos++ = 2; /* len */
	put_unaligned_le16(sdata->vअगर.bss_conf.aid, pos);
पूर्ण

/* translate numbering in the WMM parameter IE to the mac80211 notation */
अटल क्रमागत ieee80211_ac_numbers ieee80211_ac_from_wmm(पूर्णांक ac)
अणु
	चयन (ac) अणु
	शेष:
		WARN_ON_ONCE(1);
		fallthrough;
	हाल 0:
		वापस IEEE80211_AC_BE;
	हाल 1:
		वापस IEEE80211_AC_BK;
	हाल 2:
		वापस IEEE80211_AC_VI;
	हाल 3:
		वापस IEEE80211_AC_VO;
	पूर्ण
पूर्ण

अटल u8 ieee80211_wmm_aci_aअगरsn(पूर्णांक aअगरsn, bool acm, पूर्णांक aci)
अणु
	u8 ret;

	ret = aअगरsn & 0x0f;
	अगर (acm)
		ret |= 0x10;
	ret |= (aci << 5) & 0x60;
	वापस ret;
पूर्ण

अटल u8 ieee80211_wmm_ecw(u16 cw_min, u16 cw_max)
अणु
	वापस ((ilog2(cw_min + 1) << 0x0) & 0x0f) |
	       ((ilog2(cw_max + 1) << 0x4) & 0xf0);
पूर्ण

अटल व्योम ieee80211_tdls_add_wmm_param_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_wmm_param_ie *wmm;
	काष्ठा ieee80211_tx_queue_params *txq;
	पूर्णांक i;

	wmm = skb_put_zero(skb, माप(*wmm));

	wmm->element_id = WLAN_EID_VENDOR_SPECIFIC;
	wmm->len = माप(*wmm) - 2;

	wmm->oui[0] = 0x00; /* Microsoft OUI 00:50:F2 */
	wmm->oui[1] = 0x50;
	wmm->oui[2] = 0xf2;
	wmm->oui_type = 2; /* WME */
	wmm->oui_subtype = 1; /* WME param */
	wmm->version = 1; /* WME ver */
	wmm->qos_info = 0; /* U-APSD not in use */

	/*
	 * Use the EDCA parameters defined क्रम the BSS, or शेष अगर the AP
	 * करोesn't support it, as mandated by 802.11-2012 section 10.22.4
	 */
	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		txq = &sdata->tx_conf[ieee80211_ac_from_wmm(i)];
		wmm->ac[i].aci_aअगरsn = ieee80211_wmm_aci_aअगरsn(txq->aअगरs,
							       txq->acm, i);
		wmm->ac[i].cw = ieee80211_wmm_ecw(txq->cw_min, txq->cw_max);
		wmm->ac[i].txop_limit = cpu_to_le16(txq->txop);
	पूर्ण
पूर्ण

अटल व्योम
ieee80211_tdls_chandef_vht_upgrade(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sta_info *sta)
अणु
	/* IEEE802.11ac-2013 Table E-4 */
	u16 centers_80mhz[] = अणु 5210, 5290, 5530, 5610, 5690, 5775 पूर्ण;
	काष्ठा cfg80211_chan_def uc = sta->tdls_chandef;
	क्रमागत nl80211_chan_width max_width = ieee80211_sta_cap_chan_bw(sta);
	पूर्णांक i;

	/* only support upgrading non-narrow channels up to 80Mhz */
	अगर (max_width == NL80211_CHAN_WIDTH_5 ||
	    max_width == NL80211_CHAN_WIDTH_10)
		वापस;

	अगर (max_width > NL80211_CHAN_WIDTH_80)
		max_width = NL80211_CHAN_WIDTH_80;

	अगर (uc.width >= max_width)
		वापस;
	/*
	 * Channel usage स्थिरrains in the IEEE802.11ac-2013 specअगरication only
	 * allow expanding a 20MHz channel to 80MHz in a single way. In
	 * addition, there are no 40MHz allowed channels that are not part of
	 * the allowed 80MHz range in the 5GHz spectrum (the relevant one here).
	 */
	क्रम (i = 0; i < ARRAY_SIZE(centers_80mhz); i++)
		अगर (असल(uc.chan->center_freq - centers_80mhz[i]) <= 30) अणु
			uc.center_freq1 = centers_80mhz[i];
			uc.center_freq2 = 0;
			uc.width = NL80211_CHAN_WIDTH_80;
			अवरोध;
		पूर्ण

	अगर (!uc.center_freq1)
		वापस;

	/* proceed to करोwngrade the chandef until usable or the same as AP BW */
	जबतक (uc.width > max_width ||
	       (uc.width > sta->tdls_chandef.width &&
		!cfg80211_reg_can_beacon_relax(sdata->local->hw.wiphy, &uc,
					       sdata->wdev.अगरtype)))
		ieee80211_chandef_करोwngrade(&uc);

	अगर (!cfg80211_chandef_identical(&uc, &sta->tdls_chandef)) अणु
		tdls_dbg(sdata, "TDLS ch width upgraded %d -> %d\n",
			 sta->tdls_chandef.width, uc.width);

		/*
		 * the station is not yet authorized when BW upgrade is करोne,
		 * locking is not required
		 */
		sta->tdls_chandef = uc;
	पूर्ण
पूर्ण

अटल व्योम
ieee80211_tdls_add_setup_start_ies(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sk_buff *skb, स्थिर u8 *peer,
				   u8 action_code, bool initiator,
				   स्थिर u8 *extra_ies, माप_प्रकार extra_ies_len)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_sta_ht_cap ht_cap;
	काष्ठा ieee80211_sta_vht_cap vht_cap;
	काष्ठा sta_info *sta = शून्य;
	माप_प्रकार offset = 0, noffset;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस;

	ieee80211_add_srates_ie(sdata, skb, false, sband->band);
	ieee80211_add_ext_srates_ie(sdata, skb, false, sband->band);
	ieee80211_tdls_add_supp_channels(sdata, skb);

	/* add any custom IEs that go beक्रमe Extended Capabilities */
	अगर (extra_ies_len) अणु
		अटल स्थिर u8 beक्रमe_ext_cap[] = अणु
			WLAN_EID_SUPP_RATES,
			WLAN_EID_COUNTRY,
			WLAN_EID_EXT_SUPP_RATES,
			WLAN_EID_SUPPORTED_CHANNELS,
			WLAN_EID_RSN,
		पूर्ण;
		noffset = ieee80211_ie_split(extra_ies, extra_ies_len,
					     beक्रमe_ext_cap,
					     ARRAY_SIZE(beक्रमe_ext_cap),
					     offset);
		skb_put_data(skb, extra_ies + offset, noffset - offset);
		offset = noffset;
	पूर्ण

	ieee80211_tdls_add_ext_capab(sdata, skb);

	/* add the QoS element अगर we support it */
	अगर (local->hw.queues >= IEEE80211_NUM_ACS &&
	    action_code != WLAN_PUB_ACTION_TDLS_DISCOVER_RES)
		ieee80211_add_wmm_info_ie(skb_put(skb, 9), 0); /* no U-APSD */

	/* add any custom IEs that go beक्रमe HT capabilities */
	अगर (extra_ies_len) अणु
		अटल स्थिर u8 beक्रमe_ht_cap[] = अणु
			WLAN_EID_SUPP_RATES,
			WLAN_EID_COUNTRY,
			WLAN_EID_EXT_SUPP_RATES,
			WLAN_EID_SUPPORTED_CHANNELS,
			WLAN_EID_RSN,
			WLAN_EID_EXT_CAPABILITY,
			WLAN_EID_QOS_CAPA,
			WLAN_EID_FAST_BSS_TRANSITION,
			WLAN_EID_TIMEOUT_INTERVAL,
			WLAN_EID_SUPPORTED_REGULATORY_CLASSES,
		पूर्ण;
		noffset = ieee80211_ie_split(extra_ies, extra_ies_len,
					     beक्रमe_ht_cap,
					     ARRAY_SIZE(beक्रमe_ht_cap),
					     offset);
		skb_put_data(skb, extra_ies + offset, noffset - offset);
		offset = noffset;
	पूर्ण

	mutex_lock(&local->sta_mtx);

	/* we should have the peer STA अगर we're alपढ़ोy responding */
	अगर (action_code == WLAN_TDLS_SETUP_RESPONSE) अणु
		sta = sta_info_get(sdata, peer);
		अगर (WARN_ON_ONCE(!sta)) अणु
			mutex_unlock(&local->sta_mtx);
			वापस;
		पूर्ण

		sta->tdls_chandef = sdata->vअगर.bss_conf.chandef;
	पूर्ण

	ieee80211_tdls_add_oper_classes(sdata, skb);

	/*
	 * with TDLS we can चयन channels, and HT-caps are not necessarily
	 * the same on all bands. The specअगरication limits the setup to a
	 * single HT-cap, so use the current band क्रम now.
	 */
	स_नकल(&ht_cap, &sband->ht_cap, माप(ht_cap));

	अगर ((action_code == WLAN_TDLS_SETUP_REQUEST ||
	     action_code == WLAN_PUB_ACTION_TDLS_DISCOVER_RES) &&
	    ht_cap.ht_supported) अणु
		ieee80211_apply_htcap_overrides(sdata, &ht_cap);

		/* disable SMPS in TDLS initiator */
		ht_cap.cap |= WLAN_HT_CAP_SM_PS_DISABLED
				<< IEEE80211_HT_CAP_SM_PS_SHIFT;

		pos = skb_put(skb, माप(काष्ठा ieee80211_ht_cap) + 2);
		ieee80211_ie_build_ht_cap(pos, &ht_cap, ht_cap.cap);
	पूर्ण अन्यथा अगर (action_code == WLAN_TDLS_SETUP_RESPONSE &&
		   ht_cap.ht_supported && sta->sta.ht_cap.ht_supported) अणु
		/* the peer caps are alपढ़ोy पूर्णांकersected with our own */
		स_नकल(&ht_cap, &sta->sta.ht_cap, माप(ht_cap));

		pos = skb_put(skb, माप(काष्ठा ieee80211_ht_cap) + 2);
		ieee80211_ie_build_ht_cap(pos, &ht_cap, ht_cap.cap);
	पूर्ण

	अगर (ht_cap.ht_supported &&
	    (ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40))
		ieee80211_tdls_add_bss_coex_ie(skb);

	ieee80211_tdls_add_link_ie(sdata, skb, peer, initiator);

	/* add any custom IEs that go beक्रमe VHT capabilities */
	अगर (extra_ies_len) अणु
		अटल स्थिर u8 beक्रमe_vht_cap[] = अणु
			WLAN_EID_SUPP_RATES,
			WLAN_EID_COUNTRY,
			WLAN_EID_EXT_SUPP_RATES,
			WLAN_EID_SUPPORTED_CHANNELS,
			WLAN_EID_RSN,
			WLAN_EID_EXT_CAPABILITY,
			WLAN_EID_QOS_CAPA,
			WLAN_EID_FAST_BSS_TRANSITION,
			WLAN_EID_TIMEOUT_INTERVAL,
			WLAN_EID_SUPPORTED_REGULATORY_CLASSES,
			WLAN_EID_MULTI_BAND,
		पूर्ण;
		noffset = ieee80211_ie_split(extra_ies, extra_ies_len,
					     beक्रमe_vht_cap,
					     ARRAY_SIZE(beक्रमe_vht_cap),
					     offset);
		skb_put_data(skb, extra_ies + offset, noffset - offset);
		offset = noffset;
	पूर्ण

	/* build the VHT-cap similarly to the HT-cap */
	स_नकल(&vht_cap, &sband->vht_cap, माप(vht_cap));
	अगर ((action_code == WLAN_TDLS_SETUP_REQUEST ||
	     action_code == WLAN_PUB_ACTION_TDLS_DISCOVER_RES) &&
	    vht_cap.vht_supported) अणु
		ieee80211_apply_vhtcap_overrides(sdata, &vht_cap);

		/* the AID is present only when VHT is implemented */
		अगर (action_code == WLAN_TDLS_SETUP_REQUEST)
			ieee80211_tdls_add_aid(sdata, skb);

		pos = skb_put(skb, माप(काष्ठा ieee80211_vht_cap) + 2);
		ieee80211_ie_build_vht_cap(pos, &vht_cap, vht_cap.cap);
	पूर्ण अन्यथा अगर (action_code == WLAN_TDLS_SETUP_RESPONSE &&
		   vht_cap.vht_supported && sta->sta.vht_cap.vht_supported) अणु
		/* the peer caps are alपढ़ोy पूर्णांकersected with our own */
		स_नकल(&vht_cap, &sta->sta.vht_cap, माप(vht_cap));

		/* the AID is present only when VHT is implemented */
		ieee80211_tdls_add_aid(sdata, skb);

		pos = skb_put(skb, माप(काष्ठा ieee80211_vht_cap) + 2);
		ieee80211_ie_build_vht_cap(pos, &vht_cap, vht_cap.cap);

		/*
		 * अगर both peers support WIDER_BW, we can expand the chandef to
		 * a wider compatible one, up to 80MHz
		 */
		अगर (test_sta_flag(sta, WLAN_STA_TDLS_WIDER_BW))
			ieee80211_tdls_chandef_vht_upgrade(sdata, sta);
	पूर्ण

	mutex_unlock(&local->sta_mtx);

	/* add any reमुख्यing IEs */
	अगर (extra_ies_len) अणु
		noffset = extra_ies_len;
		skb_put_data(skb, extra_ies + offset, noffset - offset);
	पूर्ण

पूर्ण

अटल व्योम
ieee80211_tdls_add_setup_cfm_ies(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sk_buff *skb, स्थिर u8 *peer,
				 bool initiator, स्थिर u8 *extra_ies,
				 माप_प्रकार extra_ies_len)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	माप_प्रकार offset = 0, noffset;
	काष्ठा sta_info *sta, *ap_sta;
	काष्ठा ieee80211_supported_band *sband;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस;

	mutex_lock(&local->sta_mtx);

	sta = sta_info_get(sdata, peer);
	ap_sta = sta_info_get(sdata, अगरmgd->bssid);
	अगर (WARN_ON_ONCE(!sta || !ap_sta)) अणु
		mutex_unlock(&local->sta_mtx);
		वापस;
	पूर्ण

	sta->tdls_chandef = sdata->vअगर.bss_conf.chandef;

	/* add any custom IEs that go beक्रमe the QoS IE */
	अगर (extra_ies_len) अणु
		अटल स्थिर u8 beक्रमe_qos[] = अणु
			WLAN_EID_RSN,
		पूर्ण;
		noffset = ieee80211_ie_split(extra_ies, extra_ies_len,
					     beक्रमe_qos,
					     ARRAY_SIZE(beक्रमe_qos),
					     offset);
		skb_put_data(skb, extra_ies + offset, noffset - offset);
		offset = noffset;
	पूर्ण

	/* add the QoS param IE अगर both the peer and we support it */
	अगर (local->hw.queues >= IEEE80211_NUM_ACS && sta->sta.wme)
		ieee80211_tdls_add_wmm_param_ie(sdata, skb);

	/* add any custom IEs that go beक्रमe HT operation */
	अगर (extra_ies_len) अणु
		अटल स्थिर u8 beक्रमe_ht_op[] = अणु
			WLAN_EID_RSN,
			WLAN_EID_QOS_CAPA,
			WLAN_EID_FAST_BSS_TRANSITION,
			WLAN_EID_TIMEOUT_INTERVAL,
		पूर्ण;
		noffset = ieee80211_ie_split(extra_ies, extra_ies_len,
					     beक्रमe_ht_op,
					     ARRAY_SIZE(beक्रमe_ht_op),
					     offset);
		skb_put_data(skb, extra_ies + offset, noffset - offset);
		offset = noffset;
	पूर्ण

	/*
	 * अगर HT support is only added in TDLS, we need an HT-operation IE.
	 * add the IE as required by IEEE802.11-2012 9.23.3.2.
	 */
	अगर (!ap_sta->sta.ht_cap.ht_supported && sta->sta.ht_cap.ht_supported) अणु
		u16 prot = IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED |
			   IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT |
			   IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT;

		pos = skb_put(skb, 2 + माप(काष्ठा ieee80211_ht_operation));
		ieee80211_ie_build_ht_oper(pos, &sta->sta.ht_cap,
					   &sdata->vअगर.bss_conf.chandef, prot,
					   true);
	पूर्ण

	ieee80211_tdls_add_link_ie(sdata, skb, peer, initiator);

	/* only include VHT-operation अगर not on the 2.4GHz band */
	अगर (sband->band != NL80211_BAND_2GHZ &&
	    sta->sta.vht_cap.vht_supported) अणु
		/*
		 * अगर both peers support WIDER_BW, we can expand the chandef to
		 * a wider compatible one, up to 80MHz
		 */
		अगर (test_sta_flag(sta, WLAN_STA_TDLS_WIDER_BW))
			ieee80211_tdls_chandef_vht_upgrade(sdata, sta);

		pos = skb_put(skb, 2 + माप(काष्ठा ieee80211_vht_operation));
		ieee80211_ie_build_vht_oper(pos, &sta->sta.vht_cap,
					    &sta->tdls_chandef);
	पूर्ण

	mutex_unlock(&local->sta_mtx);

	/* add any reमुख्यing IEs */
	अगर (extra_ies_len) अणु
		noffset = extra_ies_len;
		skb_put_data(skb, extra_ies + offset, noffset - offset);
	पूर्ण
पूर्ण

अटल व्योम
ieee80211_tdls_add_chan_चयन_req_ies(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा sk_buff *skb, स्थिर u8 *peer,
				       bool initiator, स्थिर u8 *extra_ies,
				       माप_प्रकार extra_ies_len, u8 oper_class,
				       काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_tdls_data *tf;
	माप_प्रकार offset = 0, noffset;

	अगर (WARN_ON_ONCE(!chandef))
		वापस;

	tf = (व्योम *)skb->data;
	tf->u.chan_चयन_req.target_channel =
		ieee80211_frequency_to_channel(chandef->chan->center_freq);
	tf->u.chan_चयन_req.oper_class = oper_class;

	अगर (extra_ies_len) अणु
		अटल स्थिर u8 beक्रमe_lnkie[] = अणु
			WLAN_EID_SECONDARY_CHANNEL_OFFSET,
		पूर्ण;
		noffset = ieee80211_ie_split(extra_ies, extra_ies_len,
					     beक्रमe_lnkie,
					     ARRAY_SIZE(beक्रमe_lnkie),
					     offset);
		skb_put_data(skb, extra_ies + offset, noffset - offset);
		offset = noffset;
	पूर्ण

	ieee80211_tdls_add_link_ie(sdata, skb, peer, initiator);

	/* add any reमुख्यing IEs */
	अगर (extra_ies_len) अणु
		noffset = extra_ies_len;
		skb_put_data(skb, extra_ies + offset, noffset - offset);
	पूर्ण
पूर्ण

अटल व्योम
ieee80211_tdls_add_chan_चयन_resp_ies(काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा sk_buff *skb, स्थिर u8 *peer,
					u16 status_code, bool initiator,
					स्थिर u8 *extra_ies,
					माप_प्रकार extra_ies_len)
अणु
	अगर (status_code == 0)
		ieee80211_tdls_add_link_ie(sdata, skb, peer, initiator);

	अगर (extra_ies_len)
		skb_put_data(skb, extra_ies, extra_ies_len);
पूर्ण

अटल व्योम ieee80211_tdls_add_ies(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sk_buff *skb, स्थिर u8 *peer,
				   u8 action_code, u16 status_code,
				   bool initiator, स्थिर u8 *extra_ies,
				   माप_प्रकार extra_ies_len, u8 oper_class,
				   काष्ठा cfg80211_chan_def *chandef)
अणु
	चयन (action_code) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
	हाल WLAN_TDLS_SETUP_RESPONSE:
	हाल WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		अगर (status_code == 0)
			ieee80211_tdls_add_setup_start_ies(sdata, skb, peer,
							   action_code,
							   initiator,
							   extra_ies,
							   extra_ies_len);
		अवरोध;
	हाल WLAN_TDLS_SETUP_CONFIRM:
		अगर (status_code == 0)
			ieee80211_tdls_add_setup_cfm_ies(sdata, skb, peer,
							 initiator, extra_ies,
							 extra_ies_len);
		अवरोध;
	हाल WLAN_TDLS_TEARDOWN:
	हाल WLAN_TDLS_DISCOVERY_REQUEST:
		अगर (extra_ies_len)
			skb_put_data(skb, extra_ies, extra_ies_len);
		अगर (status_code == 0 || action_code == WLAN_TDLS_TEARDOWN)
			ieee80211_tdls_add_link_ie(sdata, skb, peer, initiator);
		अवरोध;
	हाल WLAN_TDLS_CHANNEL_SWITCH_REQUEST:
		ieee80211_tdls_add_chan_चयन_req_ies(sdata, skb, peer,
						       initiator, extra_ies,
						       extra_ies_len,
						       oper_class, chandef);
		अवरोध;
	हाल WLAN_TDLS_CHANNEL_SWITCH_RESPONSE:
		ieee80211_tdls_add_chan_चयन_resp_ies(sdata, skb, peer,
							status_code,
							initiator, extra_ies,
							extra_ies_len);
		अवरोध;
	पूर्ण

पूर्ण

अटल पूर्णांक
ieee80211_prep_tdls_encap_data(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       स्थिर u8 *peer, u8 action_code, u8 dialog_token,
			       u16 status_code, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_tdls_data *tf;

	tf = skb_put(skb, दुरत्व(काष्ठा ieee80211_tdls_data, u));

	स_नकल(tf->da, peer, ETH_ALEN);
	स_नकल(tf->sa, sdata->vअगर.addr, ETH_ALEN);
	tf->ether_type = cpu_to_be16(ETH_P_TDLS);
	tf->payload_type = WLAN_TDLS_SNAP_RFTYPE;

	/* network header is after the ethernet header */
	skb_set_network_header(skb, ETH_HLEN);

	चयन (action_code) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_SETUP_REQUEST;

		skb_put(skb, माप(tf->u.setup_req));
		tf->u.setup_req.dialog_token = dialog_token;
		tf->u.setup_req.capability =
			cpu_to_le16(ieee80211_get_tdls_sta_capab(sdata,
								 status_code));
		अवरोध;
	हाल WLAN_TDLS_SETUP_RESPONSE:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_SETUP_RESPONSE;

		skb_put(skb, माप(tf->u.setup_resp));
		tf->u.setup_resp.status_code = cpu_to_le16(status_code);
		tf->u.setup_resp.dialog_token = dialog_token;
		tf->u.setup_resp.capability =
			cpu_to_le16(ieee80211_get_tdls_sta_capab(sdata,
								 status_code));
		अवरोध;
	हाल WLAN_TDLS_SETUP_CONFIRM:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_SETUP_CONFIRM;

		skb_put(skb, माप(tf->u.setup_cfm));
		tf->u.setup_cfm.status_code = cpu_to_le16(status_code);
		tf->u.setup_cfm.dialog_token = dialog_token;
		अवरोध;
	हाल WLAN_TDLS_TEARDOWN:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_TEARDOWN;

		skb_put(skb, माप(tf->u.tearकरोwn));
		tf->u.tearकरोwn.reason_code = cpu_to_le16(status_code);
		अवरोध;
	हाल WLAN_TDLS_DISCOVERY_REQUEST:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_DISCOVERY_REQUEST;

		skb_put(skb, माप(tf->u.discover_req));
		tf->u.discover_req.dialog_token = dialog_token;
		अवरोध;
	हाल WLAN_TDLS_CHANNEL_SWITCH_REQUEST:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_CHANNEL_SWITCH_REQUEST;

		skb_put(skb, माप(tf->u.chan_चयन_req));
		अवरोध;
	हाल WLAN_TDLS_CHANNEL_SWITCH_RESPONSE:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_CHANNEL_SWITCH_RESPONSE;

		skb_put(skb, माप(tf->u.chan_चयन_resp));
		tf->u.chan_चयन_resp.status_code = cpu_to_le16(status_code);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ieee80211_prep_tdls_direct(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   स्थिर u8 *peer, u8 action_code, u8 dialog_token,
			   u16 status_code, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_mgmt *mgmt;

	mgmt = skb_put_zero(skb, 24);
	स_नकल(mgmt->da, peer, ETH_ALEN);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(mgmt->bssid, sdata->u.mgd.bssid, ETH_ALEN);

	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	चयन (action_code) अणु
	हाल WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		skb_put(skb, 1 + माप(mgmt->u.action.u.tdls_discover_resp));
		mgmt->u.action.category = WLAN_CATEGORY_PUBLIC;
		mgmt->u.action.u.tdls_discover_resp.action_code =
			WLAN_PUB_ACTION_TDLS_DISCOVER_RES;
		mgmt->u.action.u.tdls_discover_resp.dialog_token =
			dialog_token;
		mgmt->u.action.u.tdls_discover_resp.capability =
			cpu_to_le16(ieee80211_get_tdls_sta_capab(sdata,
								 status_code));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *
ieee80211_tdls_build_mgmt_packet_data(काष्ठा ieee80211_sub_अगर_data *sdata,
				      स्थिर u8 *peer, u8 action_code,
				      u8 dialog_token, u16 status_code,
				      bool initiator, स्थिर u8 *extra_ies,
				      माप_प्रकार extra_ies_len, u8 oper_class,
				      काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = netdev_alloc_skb(sdata->dev,
			       local->hw.extra_tx_headroom +
			       max(माप(काष्ठा ieee80211_mgmt),
				   माप(काष्ठा ieee80211_tdls_data)) +
			       50 + /* supported rates */
			       10 + /* ext capab */
			       26 + /* max(WMM-info, WMM-param) */
			       2 + max(माप(काष्ठा ieee80211_ht_cap),
				       माप(काष्ठा ieee80211_ht_operation)) +
			       2 + max(माप(काष्ठा ieee80211_vht_cap),
				       माप(काष्ठा ieee80211_vht_operation)) +
			       50 + /* supported channels */
			       3 + /* 40/20 BSS coex */
			       4 + /* AID */
			       4 + /* oper classes */
			       extra_ies_len +
			       माप(काष्ठा ieee80211_tdls_lnkie));
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	चयन (action_code) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
	हाल WLAN_TDLS_SETUP_RESPONSE:
	हाल WLAN_TDLS_SETUP_CONFIRM:
	हाल WLAN_TDLS_TEARDOWN:
	हाल WLAN_TDLS_DISCOVERY_REQUEST:
	हाल WLAN_TDLS_CHANNEL_SWITCH_REQUEST:
	हाल WLAN_TDLS_CHANNEL_SWITCH_RESPONSE:
		ret = ieee80211_prep_tdls_encap_data(local->hw.wiphy,
						     sdata->dev, peer,
						     action_code, dialog_token,
						     status_code, skb);
		अवरोध;
	हाल WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		ret = ieee80211_prep_tdls_direct(local->hw.wiphy, sdata->dev,
						 peer, action_code,
						 dialog_token, status_code,
						 skb);
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		अवरोध;
	पूर्ण

	अगर (ret < 0)
		जाओ fail;

	ieee80211_tdls_add_ies(sdata, skb, peer, action_code, status_code,
			       initiator, extra_ies, extra_ies_len, oper_class,
			       chandef);
	वापस skb;

fail:
	dev_kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
ieee80211_tdls_prep_mgmt_packet(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				स्थिर u8 *peer, u8 action_code, u8 dialog_token,
				u16 status_code, u32 peer_capability,
				bool initiator, स्थिर u8 *extra_ies,
				माप_प्रकार extra_ies_len, u8 oper_class,
				काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा sta_info *sta;
	u32 flags = 0;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, peer);

	/* infer the initiator अगर we can, to support old userspace */
	चयन (action_code) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
		अगर (sta) अणु
			set_sta_flag(sta, WLAN_STA_TDLS_INITIATOR);
			sta->sta.tdls_initiator = false;
		पूर्ण
		fallthrough;
	हाल WLAN_TDLS_SETUP_CONFIRM:
	हाल WLAN_TDLS_DISCOVERY_REQUEST:
		initiator = true;
		अवरोध;
	हाल WLAN_TDLS_SETUP_RESPONSE:
		/*
		 * In some testing scenarios, we send a request and response.
		 * Make the last packet sent take effect क्रम the initiator
		 * value.
		 */
		अगर (sta) अणु
			clear_sta_flag(sta, WLAN_STA_TDLS_INITIATOR);
			sta->sta.tdls_initiator = true;
		पूर्ण
		fallthrough;
	हाल WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		initiator = false;
		अवरोध;
	हाल WLAN_TDLS_TEARDOWN:
	हाल WLAN_TDLS_CHANNEL_SWITCH_REQUEST:
	हाल WLAN_TDLS_CHANNEL_SWITCH_RESPONSE:
		/* any value is ok */
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		अवरोध;
	पूर्ण

	अगर (sta && test_sta_flag(sta, WLAN_STA_TDLS_INITIATOR))
		initiator = true;

	rcu_पढ़ो_unlock();
	अगर (ret < 0)
		जाओ fail;

	skb = ieee80211_tdls_build_mgmt_packet_data(sdata, peer, action_code,
						    dialog_token, status_code,
						    initiator, extra_ies,
						    extra_ies_len, oper_class,
						    chandef);
	अगर (!skb) अणु
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	अगर (action_code == WLAN_PUB_ACTION_TDLS_DISCOVER_RES) अणु
		ieee80211_tx_skb(sdata, skb);
		वापस 0;
	पूर्ण

	/*
	 * According to 802.11z: Setup req/resp are sent in AC_BK, otherwise
	 * we should शेष to AC_VI.
	 */
	चयन (action_code) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
	हाल WLAN_TDLS_SETUP_RESPONSE:
		skb->priority = 256 + 2;
		अवरोध;
	शेष:
		skb->priority = 256 + 5;
		अवरोध;
	पूर्ण
	skb_set_queue_mapping(skb, ieee80211_select_queue(sdata, skb));

	/*
	 * Set the WLAN_TDLS_TEARDOWN flag to indicate a tearकरोwn in progress.
	 * Later, अगर no ACK is वापसed from peer, we will re-send the tearकरोwn
	 * packet through the AP.
	 */
	अगर ((action_code == WLAN_TDLS_TEARDOWN) &&
	    ieee80211_hw_check(&sdata->local->hw, REPORTS_TX_ACK_STATUS)) अणु
		bool try_resend; /* Should we keep skb क्रम possible resend */

		/* If not sending directly to peer - no poपूर्णांक in keeping skb */
		rcu_पढ़ो_lock();
		sta = sta_info_get(sdata, peer);
		try_resend = sta && test_sta_flag(sta, WLAN_STA_TDLS_PEER_AUTH);
		rcu_पढ़ो_unlock();

		spin_lock_bh(&sdata->u.mgd.tearकरोwn_lock);
		अगर (try_resend && !sdata->u.mgd.tearकरोwn_skb) अणु
			/* Mark it as requiring TX status callback  */
			flags |= IEEE80211_TX_CTL_REQ_TX_STATUS |
				 IEEE80211_TX_INTFL_MLME_CONN_TX;

			/*
			 * skb is copied since mac80211 will later set
			 * properties that might not be the same as the AP,
			 * such as encryption, QoS, addresses, etc.
			 *
			 * No problem अगर skb_copy() fails, so no need to check.
			 */
			sdata->u.mgd.tearकरोwn_skb = skb_copy(skb, GFP_ATOMIC);
			sdata->u.mgd.orig_tearकरोwn_skb = skb;
		पूर्ण
		spin_unlock_bh(&sdata->u.mgd.tearकरोwn_lock);
	पूर्ण

	/* disable bottom halves when entering the Tx path */
	local_bh_disable();
	__ieee80211_subअगर_start_xmit(skb, dev, flags, 0, शून्य);
	local_bh_enable();

	वापस ret;

fail:
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक
ieee80211_tdls_mgmt_setup(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  स्थिर u8 *peer, u8 action_code, u8 dialog_token,
			  u16 status_code, u32 peer_capability, bool initiator,
			  स्थिर u8 *extra_ies, माप_प्रकार extra_ies_len)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	क्रमागत ieee80211_smps_mode smps_mode = sdata->u.mgd.driver_smps_mode;
	पूर्णांक ret;

	/* करोn't support setup with forced SMPS mode that's not off */
	अगर (smps_mode != IEEE80211_SMPS_AUTOMATIC &&
	    smps_mode != IEEE80211_SMPS_OFF) अणु
		tdls_dbg(sdata, "Aborting TDLS setup due to SMPS mode %d\n",
			 smps_mode);
		वापस -ENOTSUPP;
	पूर्ण

	mutex_lock(&local->mtx);

	/* we करोn't support concurrent TDLS peer setups */
	अगर (!is_zero_ether_addr(sdata->u.mgd.tdls_peer) &&
	    !ether_addr_equal(sdata->u.mgd.tdls_peer, peer)) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	/*
	 * make sure we have a STA representing the peer so we drop or buffer
	 * non-TDLS-setup frames to the peer. We can't send other packets
	 * during setup through the AP path.
	 * Allow error packets to be sent - someबार we करोn't even add a STA
	 * beक्रमe failing the setup.
	 */
	अगर (status_code == 0) अणु
		rcu_पढ़ो_lock();
		अगर (!sta_info_get(sdata, peer)) अणु
			rcu_पढ़ो_unlock();
			ret = -ENOLINK;
			जाओ out_unlock;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	ieee80211_flush_queues(local, sdata, false);
	स_नकल(sdata->u.mgd.tdls_peer, peer, ETH_ALEN);
	mutex_unlock(&local->mtx);

	/* we cannot take the mutex जबतक preparing the setup packet */
	ret = ieee80211_tdls_prep_mgmt_packet(wiphy, dev, peer, action_code,
					      dialog_token, status_code,
					      peer_capability, initiator,
					      extra_ies, extra_ies_len, 0,
					      शून्य);
	अगर (ret < 0) अणु
		mutex_lock(&local->mtx);
		eth_zero_addr(sdata->u.mgd.tdls_peer);
		mutex_unlock(&local->mtx);
		वापस ret;
	पूर्ण

	ieee80211_queue_delayed_work(&sdata->local->hw,
				     &sdata->u.mgd.tdls_peer_del_work,
				     TDLS_PEER_SETUP_TIMEOUT);
	वापस 0;

out_unlock:
	mutex_unlock(&local->mtx);
	वापस ret;
पूर्ण

अटल पूर्णांक
ieee80211_tdls_mgmt_tearकरोwn(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     स्थिर u8 *peer, u8 action_code, u8 dialog_token,
			     u16 status_code, u32 peer_capability,
			     bool initiator, स्थिर u8 *extra_ies,
			     माप_प्रकार extra_ies_len)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	पूर्णांक ret;

	/*
	 * No packets can be transmitted to the peer via the AP during setup -
	 * the STA is set as a TDLS peer, but is not authorized.
	 * During tearकरोwn, we prevent direct transmissions by stopping the
	 * queues and flushing all direct packets.
	 */
	ieee80211_stop_vअगर_queues(local, sdata,
				  IEEE80211_QUEUE_STOP_REASON_TDLS_TEARDOWN);
	ieee80211_flush_queues(local, sdata, false);

	ret = ieee80211_tdls_prep_mgmt_packet(wiphy, dev, peer, action_code,
					      dialog_token, status_code,
					      peer_capability, initiator,
					      extra_ies, extra_ies_len, 0,
					      शून्य);
	अगर (ret < 0)
		sdata_err(sdata, "Failed sending TDLS teardown packet %d\n",
			  ret);

	/*
	 * Remove the STA AUTH flag to क्रमce further traffic through the AP. If
	 * the STA was unreachable, it was alपढ़ोy हटाओd.
	 */
	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, peer);
	अगर (sta)
		clear_sta_flag(sta, WLAN_STA_TDLS_PEER_AUTH);
	rcu_पढ़ो_unlock();

	ieee80211_wake_vअगर_queues(local, sdata,
				  IEEE80211_QUEUE_STOP_REASON_TDLS_TEARDOWN);

	वापस 0;
पूर्ण

पूर्णांक ieee80211_tdls_mgmt(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			स्थिर u8 *peer, u8 action_code, u8 dialog_token,
			u16 status_code, u32 peer_capability,
			bool initiator, स्थिर u8 *extra_ies,
			माप_प्रकार extra_ies_len)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	पूर्णांक ret;

	अगर (!(wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS))
		वापस -ENOTSUPP;

	/* make sure we are in managed mode, and associated */
	अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION ||
	    !sdata->u.mgd.associated)
		वापस -EINVAL;

	चयन (action_code) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
	हाल WLAN_TDLS_SETUP_RESPONSE:
		ret = ieee80211_tdls_mgmt_setup(wiphy, dev, peer, action_code,
						dialog_token, status_code,
						peer_capability, initiator,
						extra_ies, extra_ies_len);
		अवरोध;
	हाल WLAN_TDLS_TEARDOWN:
		ret = ieee80211_tdls_mgmt_tearकरोwn(wiphy, dev, peer,
						   action_code, dialog_token,
						   status_code,
						   peer_capability, initiator,
						   extra_ies, extra_ies_len);
		अवरोध;
	हाल WLAN_TDLS_DISCOVERY_REQUEST:
		/*
		 * Protect the discovery so we can hear the TDLS discovery
		 * response frame. It is transmitted directly and not buffered
		 * by the AP.
		 */
		drv_mgd_protect_tdls_discover(sdata->local, sdata);
		fallthrough;
	हाल WLAN_TDLS_SETUP_CONFIRM:
	हाल WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		/* no special handling */
		ret = ieee80211_tdls_prep_mgmt_packet(wiphy, dev, peer,
						      action_code,
						      dialog_token,
						      status_code,
						      peer_capability,
						      initiator, extra_ies,
						      extra_ies_len, 0, शून्य);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	tdls_dbg(sdata, "TDLS mgmt action %d peer %pM status %d\n",
		 action_code, peer, ret);
	वापस ret;
पूर्ण

अटल व्योम iee80211_tdls_recalc_chanctx(काष्ठा ieee80211_sub_अगर_data *sdata,
					 काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *conf;
	काष्ठा ieee80211_chanctx *ctx;
	क्रमागत nl80211_chan_width width;
	काष्ठा ieee80211_supported_band *sband;

	mutex_lock(&local->chanctx_mtx);
	conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					 lockdep_is_held(&local->chanctx_mtx));
	अगर (conf) अणु
		width = conf->def.width;
		sband = local->hw.wiphy->bands[conf->def.chan->band];
		ctx = container_of(conf, काष्ठा ieee80211_chanctx, conf);
		ieee80211_recalc_chanctx_chantype(local, ctx);

		/* अगर width changed and a peer is given, update its BW */
		अगर (width != conf->def.width && sta &&
		    test_sta_flag(sta, WLAN_STA_TDLS_WIDER_BW)) अणु
			क्रमागत ieee80211_sta_rx_bandwidth bw;

			bw = ieee80211_chan_width_to_rx_bw(conf->def.width);
			bw = min(bw, ieee80211_sta_cap_rx_bw(sta));
			अगर (bw != sta->sta.bandwidth) अणु
				sta->sta.bandwidth = bw;
				rate_control_rate_update(local, sband, sta,
							 IEEE80211_RC_BW_CHANGED);
				/*
				 * अगर a TDLS peer BW was updated, we need to
				 * recalc the chandef width again, to get the
				 * correct chanctx min_def
				 */
				ieee80211_recalc_chanctx_chantype(local, ctx);
			पूर्ण
		पूर्ण

	पूर्ण
	mutex_unlock(&local->chanctx_mtx);
पूर्ण

अटल पूर्णांक iee80211_tdls_have_ht_peers(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा sta_info *sta;
	bool result = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &sdata->local->sta_list, list) अणु
		अगर (!sta->sta.tdls || sta->sdata != sdata || !sta->uploaded ||
		    !test_sta_flag(sta, WLAN_STA_AUTHORIZED) ||
		    !test_sta_flag(sta, WLAN_STA_TDLS_PEER_AUTH) ||
		    !sta->sta.ht_cap.ht_supported)
			जारी;
		result = true;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस result;
पूर्ण

अटल व्योम
iee80211_tdls_recalc_ht_protection(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	bool tdls_ht;
	u16 protection = IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED |
			 IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT |
			 IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT;
	u16 opmode;

	/* Nothing to करो अगर the BSS connection uses HT */
	अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_HT))
		वापस;

	tdls_ht = (sta && sta->sta.ht_cap.ht_supported) ||
		  iee80211_tdls_have_ht_peers(sdata);

	opmode = sdata->vअगर.bss_conf.ht_operation_mode;

	अगर (tdls_ht)
		opmode |= protection;
	अन्यथा
		opmode &= ~protection;

	अगर (opmode == sdata->vअगर.bss_conf.ht_operation_mode)
		वापस;

	sdata->vअगर.bss_conf.ht_operation_mode = opmode;
	ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_HT);
पूर्ण

पूर्णांक ieee80211_tdls_oper(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			स्थिर u8 *peer, क्रमागत nl80211_tdls_operation oper)
अणु
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक ret;

	अगर (!(wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS))
		वापस -ENOTSUPP;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस -EINVAL;

	चयन (oper) अणु
	हाल NL80211_TDLS_ENABLE_LINK:
	हाल NL80211_TDLS_DISABLE_LINK:
		अवरोध;
	हाल NL80211_TDLS_TEARDOWN:
	हाल NL80211_TDLS_SETUP:
	हाल NL80211_TDLS_DISCOVERY_REQ:
		/* We करोn't support in-driver setup/tearकरोwn/discovery */
		वापस -ENOTSUPP;
	पूर्ण

	/* protect possible bss_conf changes and aव्योम concurrency in
	 * ieee80211_bss_info_change_notअगरy()
	 */
	sdata_lock(sdata);
	mutex_lock(&local->mtx);
	tdls_dbg(sdata, "TDLS oper %d peer %pM\n", oper, peer);

	चयन (oper) अणु
	हाल NL80211_TDLS_ENABLE_LINK:
		अगर (sdata->vअगर.csa_active) अणु
			tdls_dbg(sdata, "TDLS: disallow link during CSA\n");
			ret = -EBUSY;
			अवरोध;
		पूर्ण

		mutex_lock(&local->sta_mtx);
		sta = sta_info_get(sdata, peer);
		अगर (!sta) अणु
			mutex_unlock(&local->sta_mtx);
			ret = -ENOLINK;
			अवरोध;
		पूर्ण

		iee80211_tdls_recalc_chanctx(sdata, sta);
		iee80211_tdls_recalc_ht_protection(sdata, sta);

		set_sta_flag(sta, WLAN_STA_TDLS_PEER_AUTH);
		mutex_unlock(&local->sta_mtx);

		WARN_ON_ONCE(is_zero_ether_addr(sdata->u.mgd.tdls_peer) ||
			     !ether_addr_equal(sdata->u.mgd.tdls_peer, peer));
		ret = 0;
		अवरोध;
	हाल NL80211_TDLS_DISABLE_LINK:
		/*
		 * The tearकरोwn message in ieee80211_tdls_mgmt_tearकरोwn() was
		 * created जबतक the queues were stopped, so it might still be
		 * pending. Beक्रमe flushing the queues we need to be sure the
		 * message is handled by the tasklet handling pending messages,
		 * otherwise we might start destroying the station beक्रमe
		 * sending the tearकरोwn packet.
		 * Note that this only क्रमces the tasklet to flush pendings -
		 * not to stop the tasklet from rescheduling itself.
		 */
		tasklet_समाप्त(&local->tx_pending_tasklet);
		/* flush a potentially queued tearकरोwn packet */
		ieee80211_flush_queues(local, sdata, false);

		ret = sta_info_destroy_addr(sdata, peer);

		mutex_lock(&local->sta_mtx);
		iee80211_tdls_recalc_ht_protection(sdata, शून्य);
		mutex_unlock(&local->sta_mtx);

		iee80211_tdls_recalc_chanctx(sdata, शून्य);
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		अवरोध;
	पूर्ण

	अगर (ret == 0 && ether_addr_equal(sdata->u.mgd.tdls_peer, peer)) अणु
		cancel_delayed_work(&sdata->u.mgd.tdls_peer_del_work);
		eth_zero_addr(sdata->u.mgd.tdls_peer);
	पूर्ण

	अगर (ret == 0)
		ieee80211_queue_work(&sdata->local->hw,
				     &sdata->u.mgd.request_smps_work);

	mutex_unlock(&local->mtx);
	sdata_unlock(sdata);
	वापस ret;
पूर्ण

व्योम ieee80211_tdls_oper_request(काष्ठा ieee80211_vअगर *vअगर, स्थिर u8 *peer,
				 क्रमागत nl80211_tdls_operation oper,
				 u16 reason_code, gfp_t gfp)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	अगर (vअगर->type != NL80211_IFTYPE_STATION || !vअगर->bss_conf.assoc) अणु
		sdata_err(sdata, "Discarding TDLS oper %d - not STA or disconnected\n",
			  oper);
		वापस;
	पूर्ण

	cfg80211_tdls_oper_request(sdata->dev, peer, oper, reason_code, gfp);
पूर्ण
EXPORT_SYMBOL(ieee80211_tdls_oper_request);

अटल व्योम
iee80211_tdls_add_ch_चयन_timing(u8 *buf, u16 चयन_समय, u16 चयन_समयout)
अणु
	काष्ठा ieee80211_ch_चयन_timing *ch_sw;

	*buf++ = WLAN_EID_CHAN_SWITCH_TIMING;
	*buf++ = माप(काष्ठा ieee80211_ch_चयन_timing);

	ch_sw = (व्योम *)buf;
	ch_sw->चयन_समय = cpu_to_le16(चयन_समय);
	ch_sw->चयन_समयout = cpu_to_le16(चयन_समयout);
पूर्ण

/* find चयन timing IE in SKB पढ़ोy क्रम Tx */
अटल स्थिर u8 *ieee80211_tdls_find_sw_timing_ie(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tdls_data *tf;
	स्थिर u8 *ie_start;

	/*
	 * Get the offset क्रम the new location of the चयन timing IE.
	 * The SKB network header will now poपूर्णांक to the "payload_type"
	 * element of the TDLS data frame काष्ठा.
	 */
	tf = container_of(skb->data + skb_network_offset(skb),
			  काष्ठा ieee80211_tdls_data, payload_type);
	ie_start = tf->u.chan_चयन_req.variable;
	वापस cfg80211_find_ie(WLAN_EID_CHAN_SWITCH_TIMING, ie_start,
				skb->len - (ie_start - skb->data));
पूर्ण

अटल काष्ठा sk_buff *
ieee80211_tdls_ch_sw_पंचांगpl_get(काष्ठा sta_info *sta, u8 oper_class,
			      काष्ठा cfg80211_chan_def *chandef,
			      u32 *ch_sw_पंचांग_ie_offset)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	u8 extra_ies[2 + माप(काष्ठा ieee80211_sec_chan_offs_ie) +
		     2 + माप(काष्ठा ieee80211_ch_चयन_timing)];
	पूर्णांक extra_ies_len = 2 + माप(काष्ठा ieee80211_ch_चयन_timing);
	u8 *pos = extra_ies;
	काष्ठा sk_buff *skb;

	/*
	 * अगर chandef poपूर्णांकs to a wide channel add a Secondary-Channel
	 * Offset inक्रमmation element
	 */
	अगर (chandef->width == NL80211_CHAN_WIDTH_40) अणु
		काष्ठा ieee80211_sec_chan_offs_ie *sec_chan_ie;
		bool ht40plus;

		*pos++ = WLAN_EID_SECONDARY_CHANNEL_OFFSET;
		*pos++ = माप(*sec_chan_ie);
		sec_chan_ie = (व्योम *)pos;

		ht40plus = cfg80211_get_chandef_type(chandef) ==
							NL80211_CHAN_HT40PLUS;
		sec_chan_ie->sec_chan_offs = ht40plus ?
					     IEEE80211_HT_PARAM_CHA_SEC_ABOVE :
					     IEEE80211_HT_PARAM_CHA_SEC_BELOW;
		pos += माप(*sec_chan_ie);

		extra_ies_len += 2 + माप(काष्ठा ieee80211_sec_chan_offs_ie);
	पूर्ण

	/* just set the values to 0, this is a ढाँचा */
	iee80211_tdls_add_ch_चयन_timing(pos, 0, 0);

	skb = ieee80211_tdls_build_mgmt_packet_data(sdata, sta->sta.addr,
					      WLAN_TDLS_CHANNEL_SWITCH_REQUEST,
					      0, 0, !sta->sta.tdls_initiator,
					      extra_ies, extra_ies_len,
					      oper_class, chandef);
	अगर (!skb)
		वापस शून्य;

	skb = ieee80211_build_data_ढाँचा(sdata, skb, 0);
	अगर (IS_ERR(skb)) अणु
		tdls_dbg(sdata, "Failed building TDLS channel switch frame\n");
		वापस शून्य;
	पूर्ण

	अगर (ch_sw_पंचांग_ie_offset) अणु
		स्थिर u8 *पंचांग_ie = ieee80211_tdls_find_sw_timing_ie(skb);

		अगर (!पंचांग_ie) अणु
			tdls_dbg(sdata, "No switch timing IE in TDLS switch\n");
			dev_kमुक्त_skb_any(skb);
			वापस शून्य;
		पूर्ण

		*ch_sw_पंचांग_ie_offset = पंचांग_ie - skb->data;
	पूर्ण

	tdls_dbg(sdata,
		 "TDLS channel switch request template for %pM ch %d width %d\n",
		 sta->sta.addr, chandef->chan->center_freq, chandef->width);
	वापस skb;
पूर्ण

पूर्णांक
ieee80211_tdls_channel_चयन(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      स्थिर u8 *addr, u8 oper_class,
			      काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	काष्ठा sk_buff *skb = शून्य;
	u32 ch_sw_पंचांग_ie;
	पूर्णांक ret;

	अगर (chandef->chan->freq_offset)
		/* this may work, but is untested */
		वापस -EOPNOTSUPP;

	mutex_lock(&local->sta_mtx);
	sta = sta_info_get(sdata, addr);
	अगर (!sta) अणु
		tdls_dbg(sdata,
			 "Invalid TDLS peer %pM for channel switch request\n",
			 addr);
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (!test_sta_flag(sta, WLAN_STA_TDLS_CHAN_SWITCH)) अणु
		tdls_dbg(sdata, "TDLS channel switch unsupported by %pM\n",
			 addr);
		ret = -ENOTSUPP;
		जाओ out;
	पूर्ण

	skb = ieee80211_tdls_ch_sw_पंचांगpl_get(sta, oper_class, chandef,
					    &ch_sw_पंचांग_ie);
	अगर (!skb) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = drv_tdls_channel_चयन(local, sdata, &sta->sta, oper_class,
				      chandef, skb, ch_sw_पंचांग_ie);
	अगर (!ret)
		set_sta_flag(sta, WLAN_STA_TDLS_OFF_CHANNEL);

out:
	mutex_unlock(&local->sta_mtx);
	dev_kमुक्त_skb_any(skb);
	वापस ret;
पूर्ण

व्योम
ieee80211_tdls_cancel_channel_चयन(काष्ठा wiphy *wiphy,
				     काष्ठा net_device *dev,
				     स्थिर u8 *addr)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;

	mutex_lock(&local->sta_mtx);
	sta = sta_info_get(sdata, addr);
	अगर (!sta) अणु
		tdls_dbg(sdata,
			 "Invalid TDLS peer %pM for channel switch cancel\n",
			 addr);
		जाओ out;
	पूर्ण

	अगर (!test_sta_flag(sta, WLAN_STA_TDLS_OFF_CHANNEL)) अणु
		tdls_dbg(sdata, "TDLS channel switch not initiated by %pM\n",
			 addr);
		जाओ out;
	पूर्ण

	drv_tdls_cancel_channel_चयन(local, sdata, &sta->sta);
	clear_sta_flag(sta, WLAN_STA_TDLS_OFF_CHANNEL);

out:
	mutex_unlock(&local->sta_mtx);
पूर्ण

अटल काष्ठा sk_buff *
ieee80211_tdls_ch_sw_resp_पंचांगpl_get(काष्ठा sta_info *sta,
				   u32 *ch_sw_पंचांग_ie_offset)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा sk_buff *skb;
	u8 extra_ies[2 + माप(काष्ठा ieee80211_ch_चयन_timing)];

	/* initial timing are always zero in the ढाँचा */
	iee80211_tdls_add_ch_चयन_timing(extra_ies, 0, 0);

	skb = ieee80211_tdls_build_mgmt_packet_data(sdata, sta->sta.addr,
					WLAN_TDLS_CHANNEL_SWITCH_RESPONSE,
					0, 0, !sta->sta.tdls_initiator,
					extra_ies, माप(extra_ies), 0, शून्य);
	अगर (!skb)
		वापस शून्य;

	skb = ieee80211_build_data_ढाँचा(sdata, skb, 0);
	अगर (IS_ERR(skb)) अणु
		tdls_dbg(sdata,
			 "Failed building TDLS channel switch resp frame\n");
		वापस शून्य;
	पूर्ण

	अगर (ch_sw_पंचांग_ie_offset) अणु
		स्थिर u8 *पंचांग_ie = ieee80211_tdls_find_sw_timing_ie(skb);

		अगर (!पंचांग_ie) अणु
			tdls_dbg(sdata,
				 "No switch timing IE in TDLS switch resp\n");
			dev_kमुक्त_skb_any(skb);
			वापस शून्य;
		पूर्ण

		*ch_sw_पंचांग_ie_offset = पंचांग_ie - skb->data;
	पूर्ण

	tdls_dbg(sdata, "TDLS get channel switch response template for %pM\n",
		 sta->sta.addr);
	वापस skb;
पूर्ण

अटल पूर्णांक
ieee80211_process_tdls_channel_चयन_resp(काष्ठा ieee80211_sub_अगर_data *sdata,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee802_11_elems elems;
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_tdls_data *tf = (व्योम *)skb->data;
	bool local_initiator;
	काष्ठा ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	पूर्णांक baselen = दुरत्व(typeof(*tf), u.chan_चयन_resp.variable);
	काष्ठा ieee80211_tdls_ch_sw_params params = अणुपूर्ण;
	पूर्णांक ret;

	params.action_code = WLAN_TDLS_CHANNEL_SWITCH_RESPONSE;
	params.बारtamp = rx_status->device_बारtamp;

	अगर (skb->len < baselen) अणु
		tdls_dbg(sdata, "TDLS channel switch resp too short: %d\n",
			 skb->len);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&local->sta_mtx);
	sta = sta_info_get(sdata, tf->sa);
	अगर (!sta || !test_sta_flag(sta, WLAN_STA_TDLS_PEER_AUTH)) अणु
		tdls_dbg(sdata, "TDLS chan switch from non-peer sta %pM\n",
			 tf->sa);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	params.sta = &sta->sta;
	params.status = le16_to_cpu(tf->u.chan_चयन_resp.status_code);
	अगर (params.status != 0) अणु
		ret = 0;
		जाओ call_drv;
	पूर्ण

	ieee802_11_parse_elems(tf->u.chan_चयन_resp.variable,
			       skb->len - baselen, false, &elems,
			       शून्य, शून्य);
	अगर (elems.parse_error) अणु
		tdls_dbg(sdata, "Invalid IEs in TDLS channel switch resp\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!elems.ch_sw_timing || !elems.lnk_id) अणु
		tdls_dbg(sdata, "TDLS channel switch resp - missing IEs\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* validate the initiator is set correctly */
	local_initiator =
		!स_भेद(elems.lnk_id->init_sta, sdata->vअगर.addr, ETH_ALEN);
	अगर (local_initiator == sta->sta.tdls_initiator) अणु
		tdls_dbg(sdata, "TDLS chan switch invalid lnk-id initiator\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	params.चयन_समय = le16_to_cpu(elems.ch_sw_timing->चयन_समय);
	params.चयन_समयout = le16_to_cpu(elems.ch_sw_timing->चयन_समयout);

	params.पंचांगpl_skb =
		ieee80211_tdls_ch_sw_resp_पंचांगpl_get(sta, &params.ch_sw_पंचांग_ie);
	अगर (!params.पंचांगpl_skb) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ret = 0;
call_drv:
	drv_tdls_recv_channel_चयन(sdata->local, sdata, &params);

	tdls_dbg(sdata,
		 "TDLS channel switch response received from %pM status %d\n",
		 tf->sa, params.status);

out:
	mutex_unlock(&local->sta_mtx);
	dev_kमुक्त_skb_any(params.पंचांगpl_skb);
	वापस ret;
पूर्ण

अटल पूर्णांक
ieee80211_process_tdls_channel_चयन_req(काष्ठा ieee80211_sub_अगर_data *sdata,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee802_11_elems elems;
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा ieee80211_channel *chan;
	क्रमागत nl80211_channel_type chan_type;
	पूर्णांक freq;
	u8 target_channel, oper_class;
	bool local_initiator;
	काष्ठा sta_info *sta;
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_tdls_data *tf = (व्योम *)skb->data;
	काष्ठा ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	पूर्णांक baselen = दुरत्व(typeof(*tf), u.chan_चयन_req.variable);
	काष्ठा ieee80211_tdls_ch_sw_params params = अणुपूर्ण;
	पूर्णांक ret = 0;

	params.action_code = WLAN_TDLS_CHANNEL_SWITCH_REQUEST;
	params.बारtamp = rx_status->device_बारtamp;

	अगर (skb->len < baselen) अणु
		tdls_dbg(sdata, "TDLS channel switch req too short: %d\n",
			 skb->len);
		वापस -EINVAL;
	पूर्ण

	target_channel = tf->u.chan_चयन_req.target_channel;
	oper_class = tf->u.chan_चयन_req.oper_class;

	/*
	 * We can't easily infer the channel band. The operating class is
	 * ambiguous - there are multiple tables (US/Europe/JP/Global). The
	 * solution here is to treat channels with number >14 as 5GHz ones,
	 * and specअगरically check क्रम the (oper_class, channel) combinations
	 * where this करोesn't hold. These are thankfully unique according to
	 * IEEE802.11-2012.
	 * We consider only the 2GHz and 5GHz bands and 20MHz+ channels as
	 * valid here.
	 */
	अगर ((oper_class == 112 || oper_class == 2 || oper_class == 3 ||
	     oper_class == 4 || oper_class == 5 || oper_class == 6) &&
	     target_channel < 14)
		band = NL80211_BAND_5GHZ;
	अन्यथा
		band = target_channel < 14 ? NL80211_BAND_2GHZ :
					     NL80211_BAND_5GHZ;

	freq = ieee80211_channel_to_frequency(target_channel, band);
	अगर (freq == 0) अणु
		tdls_dbg(sdata, "Invalid channel in TDLS chan switch: %d\n",
			 target_channel);
		वापस -EINVAL;
	पूर्ण

	chan = ieee80211_get_channel(sdata->local->hw.wiphy, freq);
	अगर (!chan) अणु
		tdls_dbg(sdata,
			 "Unsupported channel for TDLS chan switch: %d\n",
			 target_channel);
		वापस -EINVAL;
	पूर्ण

	ieee802_11_parse_elems(tf->u.chan_चयन_req.variable,
			       skb->len - baselen, false, &elems, शून्य, शून्य);
	अगर (elems.parse_error) अणु
		tdls_dbg(sdata, "Invalid IEs in TDLS channel switch req\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!elems.ch_sw_timing || !elems.lnk_id) अणु
		tdls_dbg(sdata, "TDLS channel switch req - missing IEs\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!elems.sec_chan_offs) अणु
		chan_type = NL80211_CHAN_HT20;
	पूर्ण अन्यथा अणु
		चयन (elems.sec_chan_offs->sec_chan_offs) अणु
		हाल IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
			chan_type = NL80211_CHAN_HT40PLUS;
			अवरोध;
		हाल IEEE80211_HT_PARAM_CHA_SEC_BELOW:
			chan_type = NL80211_CHAN_HT40MINUS;
			अवरोध;
		शेष:
			chan_type = NL80211_CHAN_HT20;
			अवरोध;
		पूर्ण
	पूर्ण

	cfg80211_chandef_create(&chandef, chan, chan_type);

	/* we will be active on the TDLS link */
	अगर (!cfg80211_reg_can_beacon_relax(sdata->local->hw.wiphy, &chandef,
					   sdata->wdev.अगरtype)) अणु
		tdls_dbg(sdata, "TDLS chan switch to forbidden channel\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&local->sta_mtx);
	sta = sta_info_get(sdata, tf->sa);
	अगर (!sta || !test_sta_flag(sta, WLAN_STA_TDLS_PEER_AUTH)) अणु
		tdls_dbg(sdata, "TDLS chan switch from non-peer sta %pM\n",
			 tf->sa);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	params.sta = &sta->sta;

	/* validate the initiator is set correctly */
	local_initiator =
		!स_भेद(elems.lnk_id->init_sta, sdata->vअगर.addr, ETH_ALEN);
	अगर (local_initiator == sta->sta.tdls_initiator) अणु
		tdls_dbg(sdata, "TDLS chan switch invalid lnk-id initiator\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* peer should have known better */
	अगर (!sta->sta.ht_cap.ht_supported && elems.sec_chan_offs &&
	    elems.sec_chan_offs->sec_chan_offs) अणु
		tdls_dbg(sdata, "TDLS chan switch - wide chan unsupported\n");
		ret = -ENOTSUPP;
		जाओ out;
	पूर्ण

	params.chandef = &chandef;
	params.चयन_समय = le16_to_cpu(elems.ch_sw_timing->चयन_समय);
	params.चयन_समयout = le16_to_cpu(elems.ch_sw_timing->चयन_समयout);

	params.पंचांगpl_skb =
		ieee80211_tdls_ch_sw_resp_पंचांगpl_get(sta,
						   &params.ch_sw_पंचांग_ie);
	अगर (!params.पंचांगpl_skb) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	drv_tdls_recv_channel_चयन(sdata->local, sdata, &params);

	tdls_dbg(sdata,
		 "TDLS ch switch request received from %pM ch %d width %d\n",
		 tf->sa, params.chandef->chan->center_freq,
		 params.chandef->width);
out:
	mutex_unlock(&local->sta_mtx);
	dev_kमुक्त_skb_any(params.पंचांगpl_skb);
	वापस ret;
पूर्ण

अटल व्योम
ieee80211_process_tdls_channel_चयन(काष्ठा ieee80211_sub_अगर_data *sdata,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tdls_data *tf = (व्योम *)skb->data;
	काष्ठा wiphy *wiphy = sdata->local->hw.wiphy;

	lockdep_निश्चित_wiphy(wiphy);

	/* make sure the driver supports it */
	अगर (!(wiphy->features & NL80211_FEATURE_TDLS_CHANNEL_SWITCH))
		वापस;

	/* we want to access the entire packet */
	अगर (skb_linearize(skb))
		वापस;
	/*
	 * The packet/size was alपढ़ोy validated by mac80211 Rx path, only look
	 * at the action type.
	 */
	चयन (tf->action_code) अणु
	हाल WLAN_TDLS_CHANNEL_SWITCH_REQUEST:
		ieee80211_process_tdls_channel_चयन_req(sdata, skb);
		अवरोध;
	हाल WLAN_TDLS_CHANNEL_SWITCH_RESPONSE:
		ieee80211_process_tdls_channel_चयन_resp(sdata, skb);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण
पूर्ण

व्योम ieee80211_tearकरोwn_tdls_peers(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा sta_info *sta;
	u16 reason = WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &sdata->local->sta_list, list) अणु
		अगर (!sta->sta.tdls || sta->sdata != sdata || !sta->uploaded ||
		    !test_sta_flag(sta, WLAN_STA_AUTHORIZED))
			जारी;

		ieee80211_tdls_oper_request(&sdata->vअगर, sta->sta.addr,
					    NL80211_TDLS_TEARDOWN, reason,
					    GFP_ATOMIC);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम ieee80211_tdls_chsw_work(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा ieee80211_local *local =
		container_of(wk, काष्ठा ieee80211_local, tdls_chsw_work);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tdls_data *tf;

	wiphy_lock(local->hw.wiphy);
	जबतक ((skb = skb_dequeue(&local->skb_queue_tdls_chsw))) अणु
		tf = (काष्ठा ieee80211_tdls_data *)skb->data;
		list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
			अगर (!ieee80211_sdata_running(sdata) ||
			    sdata->vअगर.type != NL80211_IFTYPE_STATION ||
			    !ether_addr_equal(tf->da, sdata->vअगर.addr))
				जारी;

			ieee80211_process_tdls_channel_चयन(sdata, skb);
			अवरोध;
		पूर्ण

		kमुक्त_skb(skb);
	पूर्ण
	wiphy_unlock(local->hw.wiphy);
पूर्ण

व्योम ieee80211_tdls_handle_disconnect(काष्ठा ieee80211_sub_अगर_data *sdata,
				      स्थिर u8 *peer, u16 reason)
अणु
	काष्ठा ieee80211_sta *sta;

	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta(&sdata->vअगर, peer);
	अगर (!sta || !sta->tdls) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();

	tdls_dbg(sdata, "disconnected from TDLS peer %pM (Reason: %u=%s)\n",
		 peer, reason,
		 ieee80211_get_reason_code_string(reason));

	ieee80211_tdls_oper_request(&sdata->vअगर, peer,
				    NL80211_TDLS_TEARDOWN,
				    WLAN_REASON_TDLS_TEARDOWN_UNREACHABLE,
				    GFP_ATOMIC);
पूर्ण
