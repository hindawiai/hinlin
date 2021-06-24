<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IBSS mode implementation
 * Copyright 2003-2008, Jouni Malinen <j@w1.fi>
 * Copyright 2004, Instant802 Networks, Inc.
 * Copyright 2005, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007, Michael Wu <flamingice@sourmilk.net>
 * Copyright 2009, Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright(c) 2016 Intel Deutschland GmbH
 * Copyright(c) 2018-2020 Intel Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/mac80211.h>

#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "rate.h"

#घोषणा IEEE80211_SCAN_INTERVAL (2 * HZ)
#घोषणा IEEE80211_IBSS_JOIN_TIMEOUT (7 * HZ)

#घोषणा IEEE80211_IBSS_MERGE_INTERVAL (30 * HZ)
#घोषणा IEEE80211_IBSS_INACTIVITY_LIMIT (60 * HZ)
#घोषणा IEEE80211_IBSS_RSN_INACTIVITY_LIMIT (10 * HZ)

#घोषणा IEEE80211_IBSS_MAX_STA_ENTRIES 128

अटल काष्ठा beacon_data *
ieee80211_ibss_build_presp(काष्ठा ieee80211_sub_अगर_data *sdata,
			   स्थिर पूर्णांक beacon_पूर्णांक, स्थिर u32 basic_rates,
			   स्थिर u16 capability, u64 tsf,
			   काष्ठा cfg80211_chan_def *chandef,
			   bool *have_higher_than_11mbit,
			   काष्ठा cfg80211_csa_settings *csa_settings)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक rates_n = 0, i, ri;
	काष्ठा ieee80211_mgmt *mgmt;
	u8 *pos;
	काष्ठा ieee80211_supported_band *sband;
	u32 rate_flags, rates = 0, rates_added = 0;
	काष्ठा beacon_data *presp;
	पूर्णांक frame_len;
	पूर्णांक shअगरt;

	/* Build IBSS probe response */
	frame_len = माप(काष्ठा ieee80211_hdr_3addr) +
		    12 /* काष्ठा ieee80211_mgmt.u.beacon */ +
		    2 + IEEE80211_MAX_SSID_LEN /* max SSID */ +
		    2 + 8 /* max Supported Rates */ +
		    3 /* max DS params */ +
		    4 /* IBSS params */ +
		    5 /* Channel Switch Announcement */ +
		    2 + (IEEE80211_MAX_SUPP_RATES - 8) +
		    2 + माप(काष्ठा ieee80211_ht_cap) +
		    2 + माप(काष्ठा ieee80211_ht_operation) +
		    2 + माप(काष्ठा ieee80211_vht_cap) +
		    2 + माप(काष्ठा ieee80211_vht_operation) +
		    अगरibss->ie_len;
	presp = kzalloc(माप(*presp) + frame_len, GFP_KERNEL);
	अगर (!presp)
		वापस शून्य;

	presp->head = (व्योम *)(presp + 1);

	mgmt = (व्योम *) presp->head;
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_PROBE_RESP);
	eth_broadcast_addr(mgmt->da);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(mgmt->bssid, अगरibss->bssid, ETH_ALEN);
	mgmt->u.beacon.beacon_पूर्णांक = cpu_to_le16(beacon_पूर्णांक);
	mgmt->u.beacon.बारtamp = cpu_to_le64(tsf);
	mgmt->u.beacon.capab_info = cpu_to_le16(capability);

	pos = (u8 *)mgmt + दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);

	*pos++ = WLAN_EID_SSID;
	*pos++ = अगरibss->ssid_len;
	स_नकल(pos, अगरibss->ssid, अगरibss->ssid_len);
	pos += अगरibss->ssid_len;

	sband = local->hw.wiphy->bands[chandef->chan->band];
	rate_flags = ieee80211_chandef_rate_flags(chandef);
	shअगरt = ieee80211_chandef_get_shअगरt(chandef);
	rates_n = 0;
	अगर (have_higher_than_11mbit)
		*have_higher_than_11mbit = false;

	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			जारी;
		अगर (sband->bitrates[i].bitrate > 110 &&
		    have_higher_than_11mbit)
			*have_higher_than_11mbit = true;

		rates |= BIT(i);
		rates_n++;
	पूर्ण

	*pos++ = WLAN_EID_SUPP_RATES;
	*pos++ = min_t(पूर्णांक, 8, rates_n);
	क्रम (ri = 0; ri < sband->n_bitrates; ri++) अणु
		पूर्णांक rate = DIV_ROUND_UP(sband->bitrates[ri].bitrate,
					5 * (1 << shअगरt));
		u8 basic = 0;
		अगर (!(rates & BIT(ri)))
			जारी;

		अगर (basic_rates & BIT(ri))
			basic = 0x80;
		*pos++ = basic | (u8) rate;
		अगर (++rates_added == 8) अणु
			ri++; /* जारी at next rate क्रम EXT_SUPP_RATES */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (sband->band == NL80211_BAND_2GHZ) अणु
		*pos++ = WLAN_EID_DS_PARAMS;
		*pos++ = 1;
		*pos++ = ieee80211_frequency_to_channel(
				chandef->chan->center_freq);
	पूर्ण

	*pos++ = WLAN_EID_IBSS_PARAMS;
	*pos++ = 2;
	/* FIX: set ATIM winकरोw based on scan results */
	*pos++ = 0;
	*pos++ = 0;

	अगर (csa_settings) अणु
		*pos++ = WLAN_EID_CHANNEL_SWITCH;
		*pos++ = 3;
		*pos++ = csa_settings->block_tx ? 1 : 0;
		*pos++ = ieee80211_frequency_to_channel(
				csa_settings->chandef.chan->center_freq);
		presp->cntdwn_counter_offsets[0] = (pos - presp->head);
		*pos++ = csa_settings->count;
		presp->cntdwn_current_counter = csa_settings->count;
	पूर्ण

	/* put the reमुख्यing rates in WLAN_EID_EXT_SUPP_RATES */
	अगर (rates_n > 8) अणु
		*pos++ = WLAN_EID_EXT_SUPP_RATES;
		*pos++ = rates_n - 8;
		क्रम (; ri < sband->n_bitrates; ri++) अणु
			पूर्णांक rate = DIV_ROUND_UP(sband->bitrates[ri].bitrate,
						5 * (1 << shअगरt));
			u8 basic = 0;
			अगर (!(rates & BIT(ri)))
				जारी;

			अगर (basic_rates & BIT(ri))
				basic = 0x80;
			*pos++ = basic | (u8) rate;
		पूर्ण
	पूर्ण

	अगर (अगरibss->ie_len) अणु
		स_नकल(pos, अगरibss->ie, अगरibss->ie_len);
		pos += अगरibss->ie_len;
	पूर्ण

	/* add HT capability and inक्रमmation IEs */
	अगर (chandef->width != NL80211_CHAN_WIDTH_20_NOHT &&
	    chandef->width != NL80211_CHAN_WIDTH_5 &&
	    chandef->width != NL80211_CHAN_WIDTH_10 &&
	    sband->ht_cap.ht_supported) अणु
		काष्ठा ieee80211_sta_ht_cap ht_cap;

		स_नकल(&ht_cap, &sband->ht_cap, माप(ht_cap));
		ieee80211_apply_htcap_overrides(sdata, &ht_cap);

		pos = ieee80211_ie_build_ht_cap(pos, &ht_cap, ht_cap.cap);
		/*
		 * Note: According to 802.11n-2009 9.13.3.1, HT Protection
		 * field and RIFS Mode are reserved in IBSS mode, thereक्रमe
		 * keep them at 0
		 */
		pos = ieee80211_ie_build_ht_oper(pos, &sband->ht_cap,
						 chandef, 0, false);

		/* add VHT capability and inक्रमmation IEs */
		अगर (chandef->width != NL80211_CHAN_WIDTH_20 &&
		    chandef->width != NL80211_CHAN_WIDTH_40 &&
		    sband->vht_cap.vht_supported) अणु
			pos = ieee80211_ie_build_vht_cap(pos, &sband->vht_cap,
							 sband->vht_cap.cap);
			pos = ieee80211_ie_build_vht_oper(pos, &sband->vht_cap,
							  chandef);
		पूर्ण
	पूर्ण

	अगर (local->hw.queues >= IEEE80211_NUM_ACS)
		pos = ieee80211_add_wmm_info_ie(pos, 0); /* U-APSD not in use */

	presp->head_len = pos - presp->head;
	अगर (WARN_ON(presp->head_len > frame_len))
		जाओ error;

	वापस presp;
error:
	kमुक्त(presp);
	वापस शून्य;
पूर्ण

अटल व्योम __ieee80211_sta_join_ibss(काष्ठा ieee80211_sub_अगर_data *sdata,
				      स्थिर u8 *bssid, स्थिर पूर्णांक beacon_पूर्णांक,
				      काष्ठा cfg80211_chan_def *req_chandef,
				      स्थिर u32 basic_rates,
				      स्थिर u16 capability, u64 tsf,
				      bool creator)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा cfg80211_bss *bss;
	u32 bss_change;
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा ieee80211_channel *chan;
	काष्ठा beacon_data *presp;
	काष्ठा cfg80211_inक्रमm_bss bss_meta = अणुपूर्ण;
	bool have_higher_than_11mbit;
	bool radar_required;
	पूर्णांक err;

	sdata_निश्चित_lock(sdata);

	/* Reset own TSF to allow समय synchronization work. */
	drv_reset_tsf(local, sdata);

	अगर (!ether_addr_equal(अगरibss->bssid, bssid))
		sta_info_flush(sdata);

	/* अगर merging, indicate to driver that we leave the old IBSS */
	अगर (sdata->vअगर.bss_conf.ibss_joined) अणु
		sdata->vअगर.bss_conf.ibss_joined = false;
		sdata->vअगर.bss_conf.ibss_creator = false;
		sdata->vअगर.bss_conf.enable_beacon = false;
		netअगर_carrier_off(sdata->dev);
		ieee80211_bss_info_change_notअगरy(sdata,
						 BSS_CHANGED_IBSS |
						 BSS_CHANGED_BEACON_ENABLED);
		drv_leave_ibss(local, sdata);
	पूर्ण

	presp = rcu_dereference_रक्षित(अगरibss->presp,
					  lockdep_is_held(&sdata->wdev.mtx));
	RCU_INIT_POINTER(अगरibss->presp, शून्य);
	अगर (presp)
		kमुक्त_rcu(presp, rcu_head);

	/* make a copy of the chandef, it could be modअगरied below. */
	chandef = *req_chandef;
	chan = chandef.chan;
	अगर (!cfg80211_reg_can_beacon(local->hw.wiphy, &chandef,
				     NL80211_IFTYPE_ADHOC)) अणु
		अगर (chandef.width == NL80211_CHAN_WIDTH_5 ||
		    chandef.width == NL80211_CHAN_WIDTH_10 ||
		    chandef.width == NL80211_CHAN_WIDTH_20_NOHT ||
		    chandef.width == NL80211_CHAN_WIDTH_20) अणु
			sdata_info(sdata,
				   "Failed to join IBSS, beacons forbidden\n");
			वापस;
		पूर्ण
		chandef.width = NL80211_CHAN_WIDTH_20;
		chandef.center_freq1 = chan->center_freq;
		/* check again क्रम करोwngraded chandef */
		अगर (!cfg80211_reg_can_beacon(local->hw.wiphy, &chandef,
					     NL80211_IFTYPE_ADHOC)) अणु
			sdata_info(sdata,
				   "Failed to join IBSS, beacons forbidden\n");
			वापस;
		पूर्ण
	पूर्ण

	err = cfg80211_chandef_dfs_required(sdata->local->hw.wiphy,
					    &chandef, NL80211_IFTYPE_ADHOC);
	अगर (err < 0) अणु
		sdata_info(sdata,
			   "Failed to join IBSS, invalid chandef\n");
		वापस;
	पूर्ण
	अगर (err > 0 && !अगरibss->userspace_handles_dfs) अणु
		sdata_info(sdata,
			   "Failed to join IBSS, DFS channel without control program\n");
		वापस;
	पूर्ण

	radar_required = err;

	mutex_lock(&local->mtx);
	अगर (ieee80211_vअगर_use_channel(sdata, &chandef,
				      अगरibss->fixed_channel ?
					IEEE80211_CHANCTX_SHARED :
					IEEE80211_CHANCTX_EXCLUSIVE)) अणु
		sdata_info(sdata, "Failed to join IBSS, no channel context\n");
		mutex_unlock(&local->mtx);
		वापस;
	पूर्ण
	sdata->radar_required = radar_required;
	mutex_unlock(&local->mtx);

	स_नकल(अगरibss->bssid, bssid, ETH_ALEN);

	presp = ieee80211_ibss_build_presp(sdata, beacon_पूर्णांक, basic_rates,
					   capability, tsf, &chandef,
					   &have_higher_than_11mbit, शून्य);
	अगर (!presp)
		वापस;

	rcu_assign_poपूर्णांकer(अगरibss->presp, presp);
	mgmt = (व्योम *)presp->head;

	sdata->vअगर.bss_conf.enable_beacon = true;
	sdata->vअगर.bss_conf.beacon_पूर्णांक = beacon_पूर्णांक;
	sdata->vअगर.bss_conf.basic_rates = basic_rates;
	sdata->vअगर.bss_conf.ssid_len = अगरibss->ssid_len;
	स_नकल(sdata->vअगर.bss_conf.ssid, अगरibss->ssid, अगरibss->ssid_len);
	bss_change = BSS_CHANGED_BEACON_INT;
	bss_change |= ieee80211_reset_erp_info(sdata);
	bss_change |= BSS_CHANGED_BSSID;
	bss_change |= BSS_CHANGED_BEACON;
	bss_change |= BSS_CHANGED_BEACON_ENABLED;
	bss_change |= BSS_CHANGED_BASIC_RATES;
	bss_change |= BSS_CHANGED_HT;
	bss_change |= BSS_CHANGED_IBSS;
	bss_change |= BSS_CHANGED_SSID;

	/*
	 * In 5 GHz/802.11a, we can always use लघु slot समय.
	 * (IEEE 802.11-2012 18.3.8.7)
	 *
	 * In 2.4GHz, we must always use दीर्घ slots in IBSS क्रम compatibility
	 * reasons.
	 * (IEEE 802.11-2012 19.4.5)
	 *
	 * HT follows these specअगरications (IEEE 802.11-2012 20.3.18)
	 */
	sdata->vअगर.bss_conf.use_लघु_slot = chan->band == NL80211_BAND_5GHZ;
	bss_change |= BSS_CHANGED_ERP_SLOT;

	/* cf. IEEE 802.11 9.2.12 */
	अगर (chan->band == NL80211_BAND_2GHZ && have_higher_than_11mbit)
		sdata->flags |= IEEE80211_SDATA_OPERATING_GMODE;
	अन्यथा
		sdata->flags &= ~IEEE80211_SDATA_OPERATING_GMODE;

	ieee80211_set_wmm_शेष(sdata, true, false);

	sdata->vअगर.bss_conf.ibss_joined = true;
	sdata->vअगर.bss_conf.ibss_creator = creator;

	err = drv_join_ibss(local, sdata);
	अगर (err) अणु
		sdata->vअगर.bss_conf.ibss_joined = false;
		sdata->vअगर.bss_conf.ibss_creator = false;
		sdata->vअगर.bss_conf.enable_beacon = false;
		sdata->vअगर.bss_conf.ssid_len = 0;
		RCU_INIT_POINTER(अगरibss->presp, शून्य);
		kमुक्त_rcu(presp, rcu_head);
		mutex_lock(&local->mtx);
		ieee80211_vअगर_release_channel(sdata);
		mutex_unlock(&local->mtx);
		sdata_info(sdata, "Failed to join IBSS, driver failure: %d\n",
			   err);
		वापस;
	पूर्ण

	ieee80211_bss_info_change_notअगरy(sdata, bss_change);

	अगरibss->state = IEEE80211_IBSS_MLME_JOINED;
	mod_समयr(&अगरibss->समयr,
		  round_jअगरfies(jअगरfies + IEEE80211_IBSS_MERGE_INTERVAL));

	bss_meta.chan = chan;
	bss_meta.scan_width = cfg80211_chandef_to_scan_width(&chandef);
	bss = cfg80211_inक्रमm_bss_frame_data(local->hw.wiphy, &bss_meta, mgmt,
					     presp->head_len, GFP_KERNEL);

	cfg80211_put_bss(local->hw.wiphy, bss);
	netअगर_carrier_on(sdata->dev);
	cfg80211_ibss_joined(sdata->dev, अगरibss->bssid, chan, GFP_KERNEL);
पूर्ण

अटल व्योम ieee80211_sta_join_ibss(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_bss *bss)
अणु
	काष्ठा cfg80211_bss *cbss =
		container_of((व्योम *)bss, काष्ठा cfg80211_bss, priv);
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा cfg80211_chan_def chandef;
	u32 basic_rates;
	पूर्णांक i, j;
	u16 beacon_पूर्णांक = cbss->beacon_पूर्णांकerval;
	स्थिर काष्ठा cfg80211_bss_ies *ies;
	क्रमागत nl80211_channel_type chan_type;
	u64 tsf;
	u32 rate_flags;
	पूर्णांक shअगरt;

	sdata_निश्चित_lock(sdata);

	अगर (beacon_पूर्णांक < 10)
		beacon_पूर्णांक = 10;

	चयन (sdata->u.ibss.chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
	हाल NL80211_CHAN_WIDTH_40:
		chan_type = cfg80211_get_chandef_type(&sdata->u.ibss.chandef);
		cfg80211_chandef_create(&chandef, cbss->channel, chan_type);
		अवरोध;
	हाल NL80211_CHAN_WIDTH_5:
	हाल NL80211_CHAN_WIDTH_10:
		cfg80211_chandef_create(&chandef, cbss->channel,
					NL80211_CHAN_NO_HT);
		chandef.width = sdata->u.ibss.chandef.width;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_160:
		chandef = sdata->u.ibss.chandef;
		chandef.chan = cbss->channel;
		अवरोध;
	शेष:
		/* fall back to 20 MHz क्रम unsupported modes */
		cfg80211_chandef_create(&chandef, cbss->channel,
					NL80211_CHAN_NO_HT);
		अवरोध;
	पूर्ण

	sband = sdata->local->hw.wiphy->bands[cbss->channel->band];
	rate_flags = ieee80211_chandef_rate_flags(&sdata->u.ibss.chandef);
	shअगरt = ieee80211_vअगर_get_shअगरt(&sdata->vअगर);

	basic_rates = 0;

	क्रम (i = 0; i < bss->supp_rates_len; i++) अणु
		पूर्णांक rate = bss->supp_rates[i] & 0x7f;
		bool is_basic = !!(bss->supp_rates[i] & 0x80);

		क्रम (j = 0; j < sband->n_bitrates; j++) अणु
			पूर्णांक brate;
			अगर ((rate_flags & sband->bitrates[j].flags)
			    != rate_flags)
				जारी;

			brate = DIV_ROUND_UP(sband->bitrates[j].bitrate,
					     5 * (1 << shअगरt));
			अगर (brate == rate) अणु
				अगर (is_basic)
					basic_rates |= BIT(j);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	rcu_पढ़ो_lock();
	ies = rcu_dereference(cbss->ies);
	tsf = ies->tsf;
	rcu_पढ़ो_unlock();

	__ieee80211_sta_join_ibss(sdata, cbss->bssid,
				  beacon_पूर्णांक,
				  &chandef,
				  basic_rates,
				  cbss->capability,
				  tsf, false);
पूर्ण

पूर्णांक ieee80211_ibss_csa_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा cfg80211_csa_settings *csa_settings)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा beacon_data *presp, *old_presp;
	काष्ठा cfg80211_bss *cbss;
	स्थिर काष्ठा cfg80211_bss_ies *ies;
	u16 capability = WLAN_CAPABILITY_IBSS;
	u64 tsf;
	पूर्णांक ret = 0;

	sdata_निश्चित_lock(sdata);

	अगर (अगरibss->privacy)
		capability |= WLAN_CAPABILITY_PRIVACY;

	cbss = cfg80211_get_bss(sdata->local->hw.wiphy, अगरibss->chandef.chan,
				अगरibss->bssid, अगरibss->ssid,
				अगरibss->ssid_len, IEEE80211_BSS_TYPE_IBSS,
				IEEE80211_PRIVACY(अगरibss->privacy));

	अगर (WARN_ON(!cbss)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	rcu_पढ़ो_lock();
	ies = rcu_dereference(cbss->ies);
	tsf = ies->tsf;
	rcu_पढ़ो_unlock();
	cfg80211_put_bss(sdata->local->hw.wiphy, cbss);

	old_presp = rcu_dereference_रक्षित(अगरibss->presp,
					  lockdep_is_held(&sdata->wdev.mtx));

	presp = ieee80211_ibss_build_presp(sdata,
					   sdata->vअगर.bss_conf.beacon_पूर्णांक,
					   sdata->vअगर.bss_conf.basic_rates,
					   capability, tsf, &अगरibss->chandef,
					   शून्य, csa_settings);
	अगर (!presp) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	rcu_assign_poपूर्णांकer(अगरibss->presp, presp);
	अगर (old_presp)
		kमुक्त_rcu(old_presp, rcu_head);

	वापस BSS_CHANGED_BEACON;
 out:
	वापस ret;
पूर्ण

पूर्णांक ieee80211_ibss_finish_csa(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा cfg80211_bss *cbss;

	sdata_निश्चित_lock(sdata);

	/* update cfg80211 bss inक्रमmation with the new channel */
	अगर (!is_zero_ether_addr(अगरibss->bssid)) अणु
		cbss = cfg80211_get_bss(sdata->local->hw.wiphy,
					अगरibss->chandef.chan,
					अगरibss->bssid, अगरibss->ssid,
					अगरibss->ssid_len,
					IEEE80211_BSS_TYPE_IBSS,
					IEEE80211_PRIVACY(अगरibss->privacy));
		/* XXX: should not really modअगरy cfg80211 data */
		अगर (cbss) अणु
			cbss->channel = sdata->csa_chandef.chan;
			cfg80211_put_bss(sdata->local->hw.wiphy, cbss);
		पूर्ण
	पूर्ण

	अगरibss->chandef = sdata->csa_chandef;

	/* generate the beacon */
	वापस ieee80211_ibss_csa_beacon(sdata, शून्य);
पूर्ण

व्योम ieee80211_ibss_stop(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;

	cancel_work_sync(&अगरibss->csa_connection_drop_work);
पूर्ण

अटल काष्ठा sta_info *ieee80211_ibss_finish_sta(काष्ठा sta_info *sta)
	__acquires(RCU)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	u8 addr[ETH_ALEN];

	स_नकल(addr, sta->sta.addr, ETH_ALEN);

	ibss_dbg(sdata, "Adding new IBSS station %pM\n", addr);

	sta_info_pre_move_state(sta, IEEE80211_STA_AUTH);
	sta_info_pre_move_state(sta, IEEE80211_STA_ASSOC);
	/* authorize the station only अगर the network is not RSN रक्षित. If
	 * not रुको क्रम the userspace to authorize it */
	अगर (!sta->sdata->u.ibss.control_port)
		sta_info_pre_move_state(sta, IEEE80211_STA_AUTHORIZED);

	rate_control_rate_init(sta);

	/* If it fails, maybe we raced another insertion? */
	अगर (sta_info_insert_rcu(sta))
		वापस sta_info_get(sdata, addr);
	वापस sta;
पूर्ण

अटल काष्ठा sta_info *
ieee80211_ibss_add_sta(काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर u8 *bssid,
		       स्थिर u8 *addr, u32 supp_rates)
	__acquires(RCU)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_supported_band *sband;
	क्रमागत nl80211_bss_scan_width scan_width;
	पूर्णांक band;

	/*
	 * XXX: Consider removing the least recently used entry and
	 * 	allow new one to be added.
	 */
	अगर (local->num_sta >= IEEE80211_IBSS_MAX_STA_ENTRIES) अणु
		net_info_ratelimited("%s: No room for a new IBSS STA entry %pM\n",
				    sdata->name, addr);
		rcu_पढ़ो_lock();
		वापस शून्य;
	पूर्ण

	अगर (अगरibss->state == IEEE80211_IBSS_MLME_SEARCH) अणु
		rcu_पढ़ो_lock();
		वापस शून्य;
	पूर्ण

	अगर (!ether_addr_equal(bssid, sdata->u.ibss.bssid)) अणु
		rcu_पढ़ो_lock();
		वापस शून्य;
	पूर्ण

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (WARN_ON_ONCE(!chanctx_conf))
		वापस शून्य;
	band = chanctx_conf->def.chan->band;
	scan_width = cfg80211_chandef_to_scan_width(&chanctx_conf->def);
	rcu_पढ़ो_unlock();

	sta = sta_info_alloc(sdata, addr, GFP_KERNEL);
	अगर (!sta) अणु
		rcu_पढ़ो_lock();
		वापस शून्य;
	पूर्ण

	/* make sure mandatory rates are always added */
	sband = local->hw.wiphy->bands[band];
	sta->sta.supp_rates[band] = supp_rates |
			ieee80211_mandatory_rates(sband, scan_width);

	वापस ieee80211_ibss_finish_sta(sta);
पूर्ण

अटल पूर्णांक ieee80211_sta_active_ibss(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक active = 0;
	काष्ठा sta_info *sta;

	sdata_निश्चित_lock(sdata);

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		अचिन्हित दीर्घ last_active = ieee80211_sta_last_active(sta);

		अगर (sta->sdata == sdata &&
		    समय_is_after_jअगरfies(last_active +
					  IEEE80211_IBSS_MERGE_INTERVAL)) अणु
			active++;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस active;
पूर्ण

अटल व्योम ieee80211_ibss_disconnect(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा cfg80211_bss *cbss;
	काष्ठा beacon_data *presp;
	काष्ठा sta_info *sta;

	अगर (!is_zero_ether_addr(अगरibss->bssid)) अणु
		cbss = cfg80211_get_bss(local->hw.wiphy, अगरibss->chandef.chan,
					अगरibss->bssid, अगरibss->ssid,
					अगरibss->ssid_len,
					IEEE80211_BSS_TYPE_IBSS,
					IEEE80211_PRIVACY(अगरibss->privacy));

		अगर (cbss) अणु
			cfg80211_unlink_bss(local->hw.wiphy, cbss);
			cfg80211_put_bss(sdata->local->hw.wiphy, cbss);
		पूर्ण
	पूर्ण

	अगरibss->state = IEEE80211_IBSS_MLME_SEARCH;

	sta_info_flush(sdata);

	spin_lock_bh(&अगरibss->incomplete_lock);
	जबतक (!list_empty(&अगरibss->incomplete_stations)) अणु
		sta = list_first_entry(&अगरibss->incomplete_stations,
				       काष्ठा sta_info, list);
		list_del(&sta->list);
		spin_unlock_bh(&अगरibss->incomplete_lock);

		sta_info_मुक्त(local, sta);
		spin_lock_bh(&अगरibss->incomplete_lock);
	पूर्ण
	spin_unlock_bh(&अगरibss->incomplete_lock);

	netअगर_carrier_off(sdata->dev);

	sdata->vअगर.bss_conf.ibss_joined = false;
	sdata->vअगर.bss_conf.ibss_creator = false;
	sdata->vअगर.bss_conf.enable_beacon = false;
	sdata->vअगर.bss_conf.ssid_len = 0;

	/* हटाओ beacon */
	presp = rcu_dereference_रक्षित(अगरibss->presp,
					  lockdep_is_held(&sdata->wdev.mtx));
	RCU_INIT_POINTER(sdata->u.ibss.presp, शून्य);
	अगर (presp)
		kमुक्त_rcu(presp, rcu_head);

	clear_bit(SDATA_STATE_OFFCHANNEL_BEACON_STOPPED, &sdata->state);
	ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_BEACON_ENABLED |
						BSS_CHANGED_IBSS);
	drv_leave_ibss(local, sdata);
	mutex_lock(&local->mtx);
	ieee80211_vअगर_release_channel(sdata);
	mutex_unlock(&local->mtx);
पूर्ण

अटल व्योम ieee80211_csa_connection_drop_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		container_of(work, काष्ठा ieee80211_sub_अगर_data,
			     u.ibss.csa_connection_drop_work);

	sdata_lock(sdata);

	ieee80211_ibss_disconnect(sdata);
	synchronize_rcu();
	skb_queue_purge(&sdata->skb_queue);

	/* trigger a scan to find another IBSS network to join */
	ieee80211_queue_work(&sdata->local->hw, &sdata->work);

	sdata_unlock(sdata);
पूर्ण

अटल व्योम ieee80211_ibss_csa_mark_radar(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	पूर्णांक err;

	/* अगर the current channel is a DFS channel, mark the channel as
	 * unavailable.
	 */
	err = cfg80211_chandef_dfs_required(sdata->local->hw.wiphy,
					    &अगरibss->chandef,
					    NL80211_IFTYPE_ADHOC);
	अगर (err > 0)
		cfg80211_radar_event(sdata->local->hw.wiphy, &अगरibss->chandef,
				     GFP_ATOMIC);
पूर्ण

अटल bool
ieee80211_ibss_process_chanचयन(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा ieee802_11_elems *elems,
				  bool beacon)
अणु
	काष्ठा cfg80211_csa_settings params;
	काष्ठा ieee80211_csa_ie csa_ie;
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	क्रमागत nl80211_channel_type ch_type;
	पूर्णांक err;
	u32 sta_flags;
	u32 vht_cap_info = 0;

	sdata_निश्चित_lock(sdata);

	sta_flags = IEEE80211_STA_DISABLE_VHT;
	चयन (अगरibss->chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_5:
	हाल NL80211_CHAN_WIDTH_10:
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		sta_flags |= IEEE80211_STA_DISABLE_HT;
		fallthrough;
	हाल NL80211_CHAN_WIDTH_20:
		sta_flags |= IEEE80211_STA_DISABLE_40MHZ;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (elems->vht_cap_elem)
		vht_cap_info = le32_to_cpu(elems->vht_cap_elem->vht_cap_info);

	स_रखो(&params, 0, माप(params));
	err = ieee80211_parse_ch_चयन_ie(sdata, elems,
					   अगरibss->chandef.chan->band,
					   vht_cap_info,
					   sta_flags, अगरibss->bssid, &csa_ie);
	/* can't चयन to destination channel, fail */
	अगर (err < 0)
		जाओ disconnect;

	/* did not contain a CSA */
	अगर (err)
		वापस false;

	/* channel चयन is not supported, disconnect */
	अगर (!(sdata->local->hw.wiphy->flags & WIPHY_FLAG_HAS_CHANNEL_SWITCH))
		जाओ disconnect;

	params.count = csa_ie.count;
	params.chandef = csa_ie.chandef;

	चयन (अगरibss->chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
	हाल NL80211_CHAN_WIDTH_40:
		/* keep our current HT mode (HT20/HT40+/HT40-), even अगर
		 * another mode  has been announced. The mode is not aकरोpted
		 * within the beacon जबतक करोing CSA and we should thereक्रमe
		 * keep the mode which we announce.
		 */
		ch_type = cfg80211_get_chandef_type(&अगरibss->chandef);
		cfg80211_chandef_create(&params.chandef, params.chandef.chan,
					ch_type);
		अवरोध;
	हाल NL80211_CHAN_WIDTH_5:
	हाल NL80211_CHAN_WIDTH_10:
		अगर (params.chandef.width != अगरibss->chandef.width) अणु
			sdata_info(sdata,
				   "IBSS %pM received channel switch from incompatible channel width (%d MHz, width:%d, CF1/2: %d/%d MHz), disconnecting\n",
				   अगरibss->bssid,
				   params.chandef.chan->center_freq,
				   params.chandef.width,
				   params.chandef.center_freq1,
				   params.chandef.center_freq2);
			जाओ disconnect;
		पूर्ण
		अवरोध;
	शेष:
		/* should not happen, sta_flags should prevent VHT modes. */
		WARN_ON(1);
		जाओ disconnect;
	पूर्ण

	अगर (!cfg80211_reg_can_beacon(sdata->local->hw.wiphy, &params.chandef,
				     NL80211_IFTYPE_ADHOC)) अणु
		sdata_info(sdata,
			   "IBSS %pM switches to unsupported channel (%d MHz, width:%d, CF1/2: %d/%d MHz), disconnecting\n",
			   अगरibss->bssid,
			   params.chandef.chan->center_freq,
			   params.chandef.width,
			   params.chandef.center_freq1,
			   params.chandef.center_freq2);
		जाओ disconnect;
	पूर्ण

	err = cfg80211_chandef_dfs_required(sdata->local->hw.wiphy,
					    &params.chandef,
					    NL80211_IFTYPE_ADHOC);
	अगर (err < 0)
		जाओ disconnect;
	अगर (err > 0 && !अगरibss->userspace_handles_dfs) अणु
		/* IBSS-DFS only allowed with a control program */
		जाओ disconnect;
	पूर्ण

	params.radar_required = err;

	अगर (cfg80211_chandef_identical(&params.chandef,
				       &sdata->vअगर.bss_conf.chandef)) अणु
		ibss_dbg(sdata,
			 "received csa with an identical chandef, ignoring\n");
		वापस true;
	पूर्ण

	/* all checks करोne, now perक्रमm the channel चयन. */
	ibss_dbg(sdata,
		 "received channel switch announcement to go to channel %d MHz\n",
		 params.chandef.chan->center_freq);

	params.block_tx = !!csa_ie.mode;

	अगर (ieee80211_channel_चयन(sdata->local->hw.wiphy, sdata->dev,
				     &params))
		जाओ disconnect;

	ieee80211_ibss_csa_mark_radar(sdata);

	वापस true;
disconnect:
	ibss_dbg(sdata, "Can't handle channel switch, disconnect\n");
	ieee80211_queue_work(&sdata->local->hw,
			     &अगरibss->csa_connection_drop_work);

	ieee80211_ibss_csa_mark_radar(sdata);

	वापस true;
पूर्ण

अटल व्योम
ieee80211_rx_mgmt_spectrum_mgmt(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
				काष्ठा ieee80211_rx_status *rx_status,
				काष्ठा ieee802_11_elems *elems)
अणु
	पूर्णांक required_len;

	अगर (len < IEEE80211_MIN_ACTION_SIZE + 1)
		वापस;

	/* CSA is the only action we handle क्रम now */
	अगर (mgmt->u.action.u.measurement.action_code !=
	    WLAN_ACTION_SPCT_CHL_SWITCH)
		वापस;

	required_len = IEEE80211_MIN_ACTION_SIZE +
		       माप(mgmt->u.action.u.chan_चयन);
	अगर (len < required_len)
		वापस;

	अगर (!sdata->vअगर.csa_active)
		ieee80211_ibss_process_chanचयन(sdata, elems, false);
पूर्ण

अटल व्योम ieee80211_rx_mgmt_deauth_ibss(काष्ठा ieee80211_sub_अगर_data *sdata,
					  काष्ठा ieee80211_mgmt *mgmt,
					  माप_प्रकार len)
अणु
	u16 reason = le16_to_cpu(mgmt->u.deauth.reason_code);

	अगर (len < IEEE80211_DEAUTH_FRAME_LEN)
		वापस;

	ibss_dbg(sdata, "RX DeAuth SA=%pM DA=%pM\n", mgmt->sa, mgmt->da);
	ibss_dbg(sdata, "\tBSSID=%pM (reason: %d)\n", mgmt->bssid, reason);
	sta_info_destroy_addr(sdata, mgmt->sa);
पूर्ण

अटल व्योम ieee80211_rx_mgmt_auth_ibss(काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा ieee80211_mgmt *mgmt,
					माप_प्रकार len)
अणु
	u16 auth_alg, auth_transaction;

	sdata_निश्चित_lock(sdata);

	अगर (len < 24 + 6)
		वापस;

	auth_alg = le16_to_cpu(mgmt->u.auth.auth_alg);
	auth_transaction = le16_to_cpu(mgmt->u.auth.auth_transaction);

	ibss_dbg(sdata, "RX Auth SA=%pM DA=%pM\n", mgmt->sa, mgmt->da);
	ibss_dbg(sdata, "\tBSSID=%pM (auth_transaction=%d)\n",
		 mgmt->bssid, auth_transaction);

	अगर (auth_alg != WLAN_AUTH_OPEN || auth_transaction != 1)
		वापस;

	/*
	 * IEEE 802.11 standard करोes not require authentication in IBSS
	 * networks and most implementations करो not seem to use it.
	 * However, try to reply to authentication attempts अगर someone
	 * has actually implemented this.
	 */
	ieee80211_send_auth(sdata, 2, WLAN_AUTH_OPEN, 0, शून्य, 0,
			    mgmt->sa, sdata->u.ibss.bssid, शून्य, 0, 0, 0);
पूर्ण

अटल व्योम ieee80211_update_sta_info(काष्ठा ieee80211_sub_अगर_data *sdata,
				      काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
				      काष्ठा ieee80211_rx_status *rx_status,
				      काष्ठा ieee802_11_elems *elems,
				      काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा sta_info *sta;
	क्रमागत nl80211_band band = rx_status->band;
	क्रमागत nl80211_bss_scan_width scan_width;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_supported_band *sband;
	bool rates_updated = false;
	u32 supp_rates = 0;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_ADHOC)
		वापस;

	अगर (!ether_addr_equal(mgmt->bssid, sdata->u.ibss.bssid))
		वापस;

	sband = local->hw.wiphy->bands[band];
	अगर (WARN_ON(!sband))
		वापस;

	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, mgmt->sa);

	अगर (elems->supp_rates) अणु
		supp_rates = ieee80211_sta_get_rates(sdata, elems,
						     band, शून्य);
		अगर (sta) अणु
			u32 prev_rates;

			prev_rates = sta->sta.supp_rates[band];
			/* make sure mandatory rates are always added */
			scan_width = NL80211_BSS_CHAN_WIDTH_20;
			अगर (rx_status->bw == RATE_INFO_BW_5)
				scan_width = NL80211_BSS_CHAN_WIDTH_5;
			अन्यथा अगर (rx_status->bw == RATE_INFO_BW_10)
				scan_width = NL80211_BSS_CHAN_WIDTH_10;

			sta->sta.supp_rates[band] = supp_rates |
				ieee80211_mandatory_rates(sband, scan_width);
			अगर (sta->sta.supp_rates[band] != prev_rates) अणु
				ibss_dbg(sdata,
					 "updated supp_rates set for %pM based on beacon/probe_resp (0x%x -> 0x%x)\n",
					 sta->sta.addr, prev_rates,
					 sta->sta.supp_rates[band]);
				rates_updated = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			rcu_पढ़ो_unlock();
			sta = ieee80211_ibss_add_sta(sdata, mgmt->bssid,
						     mgmt->sa, supp_rates);
		पूर्ण
	पूर्ण

	अगर (sta && !sta->sta.wme &&
	    (elems->wmm_info || elems->s1g_capab) &&
	    local->hw.queues >= IEEE80211_NUM_ACS) अणु
		sta->sta.wme = true;
		ieee80211_check_fast_xmit(sta);
	पूर्ण

	अगर (sta && elems->ht_operation && elems->ht_cap_elem &&
	    sdata->u.ibss.chandef.width != NL80211_CHAN_WIDTH_20_NOHT &&
	    sdata->u.ibss.chandef.width != NL80211_CHAN_WIDTH_5 &&
	    sdata->u.ibss.chandef.width != NL80211_CHAN_WIDTH_10) अणु
		/* we both use HT */
		काष्ठा ieee80211_ht_cap htcap_ie;
		काष्ठा cfg80211_chan_def chandef;
		क्रमागत ieee80211_sta_rx_bandwidth bw = sta->sta.bandwidth;

		cfg80211_chandef_create(&chandef, channel, NL80211_CHAN_NO_HT);
		ieee80211_chandef_ht_oper(elems->ht_operation, &chandef);

		स_नकल(&htcap_ie, elems->ht_cap_elem, माप(htcap_ie));
		rates_updated |= ieee80211_ht_cap_ie_to_sta_ht_cap(sdata, sband,
								   &htcap_ie,
								   sta);

		अगर (elems->vht_operation && elems->vht_cap_elem &&
		    sdata->u.ibss.chandef.width != NL80211_CHAN_WIDTH_20 &&
		    sdata->u.ibss.chandef.width != NL80211_CHAN_WIDTH_40) अणु
			/* we both use VHT */
			काष्ठा ieee80211_vht_cap cap_ie;
			काष्ठा ieee80211_sta_vht_cap cap = sta->sta.vht_cap;
			u32 vht_cap_info =
				le32_to_cpu(elems->vht_cap_elem->vht_cap_info);

			ieee80211_chandef_vht_oper(&local->hw, vht_cap_info,
						   elems->vht_operation,
						   elems->ht_operation,
						   &chandef);
			स_नकल(&cap_ie, elems->vht_cap_elem, माप(cap_ie));
			ieee80211_vht_cap_ie_to_sta_vht_cap(sdata, sband,
							    &cap_ie, sta);
			अगर (स_भेद(&cap, &sta->sta.vht_cap, माप(cap)))
				rates_updated |= true;
		पूर्ण

		अगर (bw != sta->sta.bandwidth)
			rates_updated |= true;

		अगर (!cfg80211_chandef_compatible(&sdata->u.ibss.chandef,
						 &chandef))
			WARN_ON_ONCE(1);
	पूर्ण

	अगर (sta && rates_updated) अणु
		u32 changed = IEEE80211_RC_SUPP_RATES_CHANGED;
		u8 rx_nss = sta->sta.rx_nss;

		/* Force rx_nss recalculation */
		sta->sta.rx_nss = 0;
		rate_control_rate_init(sta);
		अगर (sta->sta.rx_nss != rx_nss)
			changed |= IEEE80211_RC_NSS_CHANGED;

		drv_sta_rc_update(local, sdata, &sta->sta, changed);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ieee80211_rx_bss_info(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
				  काष्ठा ieee80211_rx_status *rx_status,
				  काष्ठा ieee802_11_elems *elems)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा cfg80211_bss *cbss;
	काष्ठा ieee80211_bss *bss;
	काष्ठा ieee80211_channel *channel;
	u64 beacon_बारtamp, rx_बारtamp;
	u32 supp_rates = 0;
	क्रमागत nl80211_band band = rx_status->band;

	channel = ieee80211_get_channel(local->hw.wiphy, rx_status->freq);
	अगर (!channel)
		वापस;

	ieee80211_update_sta_info(sdata, mgmt, len, rx_status, elems, channel);

	bss = ieee80211_bss_info_update(local, rx_status, mgmt, len, channel);
	अगर (!bss)
		वापस;

	cbss = container_of((व्योम *)bss, काष्ठा cfg80211_bss, priv);

	/* same क्रम beacon and probe response */
	beacon_बारtamp = le64_to_cpu(mgmt->u.beacon.बारtamp);

	/* check अगर we need to merge IBSS */

	/* not an IBSS */
	अगर (!(cbss->capability & WLAN_CAPABILITY_IBSS))
		जाओ put_bss;

	/* dअगरferent channel */
	अगर (sdata->u.ibss.fixed_channel &&
	    sdata->u.ibss.chandef.chan != cbss->channel)
		जाओ put_bss;

	/* dअगरferent SSID */
	अगर (elems->ssid_len != sdata->u.ibss.ssid_len ||
	    स_भेद(elems->ssid, sdata->u.ibss.ssid,
				sdata->u.ibss.ssid_len))
		जाओ put_bss;

	/* process channel चयन */
	अगर (sdata->vअगर.csa_active ||
	    ieee80211_ibss_process_chanचयन(sdata, elems, true))
		जाओ put_bss;

	/* same BSSID */
	अगर (ether_addr_equal(cbss->bssid, sdata->u.ibss.bssid))
		जाओ put_bss;

	/* we use a fixed BSSID */
	अगर (sdata->u.ibss.fixed_bssid)
		जाओ put_bss;

	अगर (ieee80211_have_rx_बारtamp(rx_status)) अणु
		/* समय when बारtamp field was received */
		rx_बारtamp =
			ieee80211_calculate_rx_बारtamp(local, rx_status,
							 len + FCS_LEN, 24);
	पूर्ण अन्यथा अणु
		/*
		 * second best option: get current TSF
		 * (will वापस -1 अगर not supported)
		 */
		rx_बारtamp = drv_get_tsf(local, sdata);
	पूर्ण

	ibss_dbg(sdata, "RX beacon SA=%pM BSSID=%pM TSF=0x%llx\n",
		 mgmt->sa, mgmt->bssid,
		 (अचिन्हित दीर्घ दीर्घ)rx_बारtamp);
	ibss_dbg(sdata, "\tBCN=0x%llx diff=%lld @%lu\n",
		 (अचिन्हित दीर्घ दीर्घ)beacon_बारtamp,
		 (अचिन्हित दीर्घ दीर्घ)(rx_बारtamp - beacon_बारtamp),
		 jअगरfies);

	अगर (beacon_बारtamp > rx_बारtamp) अणु
		ibss_dbg(sdata,
			 "beacon TSF higher than local TSF - IBSS merge with BSSID %pM\n",
			 mgmt->bssid);
		ieee80211_sta_join_ibss(sdata, bss);
		supp_rates = ieee80211_sta_get_rates(sdata, elems, band, शून्य);
		ieee80211_ibss_add_sta(sdata, mgmt->bssid, mgmt->sa,
				       supp_rates);
		rcu_पढ़ो_unlock();
	पूर्ण

 put_bss:
	ieee80211_rx_bss_put(local, bss);
पूर्ण

व्योम ieee80211_ibss_rx_no_sta(काष्ठा ieee80211_sub_अगर_data *sdata,
			      स्थिर u8 *bssid, स्थिर u8 *addr,
			      u32 supp_rates)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_supported_band *sband;
	क्रमागत nl80211_bss_scan_width scan_width;
	पूर्णांक band;

	/*
	 * XXX: Consider removing the least recently used entry and
	 * 	allow new one to be added.
	 */
	अगर (local->num_sta >= IEEE80211_IBSS_MAX_STA_ENTRIES) अणु
		net_info_ratelimited("%s: No room for a new IBSS STA entry %pM\n",
				    sdata->name, addr);
		वापस;
	पूर्ण

	अगर (अगरibss->state == IEEE80211_IBSS_MLME_SEARCH)
		वापस;

	अगर (!ether_addr_equal(bssid, sdata->u.ibss.bssid))
		वापस;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (WARN_ON_ONCE(!chanctx_conf)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	band = chanctx_conf->def.chan->band;
	scan_width = cfg80211_chandef_to_scan_width(&chanctx_conf->def);
	rcu_पढ़ो_unlock();

	sta = sta_info_alloc(sdata, addr, GFP_ATOMIC);
	अगर (!sta)
		वापस;

	/* make sure mandatory rates are always added */
	sband = local->hw.wiphy->bands[band];
	sta->sta.supp_rates[band] = supp_rates |
			ieee80211_mandatory_rates(sband, scan_width);

	spin_lock(&अगरibss->incomplete_lock);
	list_add(&sta->list, &अगरibss->incomplete_stations);
	spin_unlock(&अगरibss->incomplete_lock);
	ieee80211_queue_work(&local->hw, &sdata->work);
पूर्ण

अटल व्योम ieee80211_ibss_sta_expire(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta, *पंचांगp;
	अचिन्हित दीर्घ exp_समय = IEEE80211_IBSS_INACTIVITY_LIMIT;
	अचिन्हित दीर्घ exp_rsn = IEEE80211_IBSS_RSN_INACTIVITY_LIMIT;

	mutex_lock(&local->sta_mtx);

	list_क्रम_each_entry_safe(sta, पंचांगp, &local->sta_list, list) अणु
		अचिन्हित दीर्घ last_active = ieee80211_sta_last_active(sta);

		अगर (sdata != sta->sdata)
			जारी;

		अगर (समय_is_beक्रमe_jअगरfies(last_active + exp_समय) ||
		    (समय_is_beक्रमe_jअगरfies(last_active + exp_rsn) &&
		     sta->sta_state != IEEE80211_STA_AUTHORIZED)) अणु
			u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];

			sta_dbg(sta->sdata, "expiring inactive %sSTA %pM\n",
				sta->sta_state != IEEE80211_STA_AUTHORIZED ?
				"not authorized " : "", sta->sta.addr);

			ieee80211_send_deauth_disassoc(sdata, sta->sta.addr,
						       अगरibss->bssid,
						       IEEE80211_STYPE_DEAUTH,
						       WLAN_REASON_DEAUTH_LEAVING,
						       true, frame_buf);
			WARN_ON(__sta_info_destroy(sta));
		पूर्ण
	पूर्ण

	mutex_unlock(&local->sta_mtx);
पूर्ण

/*
 * This function is called with state == IEEE80211_IBSS_MLME_JOINED
 */

अटल व्योम ieee80211_sta_merge_ibss(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	क्रमागत nl80211_bss_scan_width scan_width;

	sdata_निश्चित_lock(sdata);

	mod_समयr(&अगरibss->समयr,
		  round_jअगरfies(jअगरfies + IEEE80211_IBSS_MERGE_INTERVAL));

	ieee80211_ibss_sta_expire(sdata);

	अगर (समय_beक्रमe(jअगरfies, अगरibss->last_scan_completed +
		       IEEE80211_IBSS_MERGE_INTERVAL))
		वापस;

	अगर (ieee80211_sta_active_ibss(sdata))
		वापस;

	अगर (अगरibss->fixed_channel)
		वापस;

	sdata_info(sdata,
		   "No active IBSS STAs - trying to scan for other IBSS networks with same SSID (merge)\n");

	scan_width = cfg80211_chandef_to_scan_width(&अगरibss->chandef);
	ieee80211_request_ibss_scan(sdata, अगरibss->ssid, अगरibss->ssid_len,
				    शून्य, 0, scan_width);
पूर्ण

अटल व्योम ieee80211_sta_create_ibss(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	u8 bssid[ETH_ALEN];
	u16 capability;
	पूर्णांक i;

	sdata_निश्चित_lock(sdata);

	अगर (अगरibss->fixed_bssid) अणु
		स_नकल(bssid, अगरibss->bssid, ETH_ALEN);
	पूर्ण अन्यथा अणु
		/* Generate अक्रमom, not broadcast, locally administered BSSID. Mix in
		 * own MAC address to make sure that devices that करो not have proper
		 * अक्रमom number generator get dअगरferent BSSID. */
		get_अक्रमom_bytes(bssid, ETH_ALEN);
		क्रम (i = 0; i < ETH_ALEN; i++)
			bssid[i] ^= sdata->vअगर.addr[i];
		bssid[0] &= ~0x01;
		bssid[0] |= 0x02;
	पूर्ण

	sdata_info(sdata, "Creating new IBSS network, BSSID %pM\n", bssid);

	capability = WLAN_CAPABILITY_IBSS;

	अगर (अगरibss->privacy)
		capability |= WLAN_CAPABILITY_PRIVACY;

	__ieee80211_sta_join_ibss(sdata, bssid, sdata->vअगर.bss_conf.beacon_पूर्णांक,
				  &अगरibss->chandef, अगरibss->basic_rates,
				  capability, 0, true);
पूर्ण

अटल अचिन्हित ibss_setup_channels(काष्ठा wiphy *wiphy,
				    काष्ठा ieee80211_channel **channels,
				    अचिन्हित पूर्णांक channels_max,
				    u32 center_freq, u32 width)
अणु
	काष्ठा ieee80211_channel *chan = शून्य;
	अचिन्हित पूर्णांक n_chan = 0;
	u32 start_freq, end_freq, freq;

	अगर (width <= 20) अणु
		start_freq = center_freq;
		end_freq = center_freq;
	पूर्ण अन्यथा अणु
		start_freq = center_freq - width / 2 + 10;
		end_freq = center_freq + width / 2 - 10;
	पूर्ण

	क्रम (freq = start_freq; freq <= end_freq; freq += 20) अणु
		chan = ieee80211_get_channel(wiphy, freq);
		अगर (!chan)
			जारी;
		अगर (n_chan >= channels_max)
			वापस n_chan;

		channels[n_chan] = chan;
		n_chan++;
	पूर्ण

	वापस n_chan;
पूर्ण

अटल अचिन्हित पूर्णांक
ieee80211_ibss_setup_scan_channels(काष्ठा wiphy *wiphy,
				   स्थिर काष्ठा cfg80211_chan_def *chandef,
				   काष्ठा ieee80211_channel **channels,
				   अचिन्हित पूर्णांक channels_max)
अणु
	अचिन्हित पूर्णांक n_chan = 0;
	u32 width, cf1, cf2 = 0;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_40:
		width = 40;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
		cf2 = chandef->center_freq2;
		fallthrough;
	हाल NL80211_CHAN_WIDTH_80:
		width = 80;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		width = 160;
		अवरोध;
	शेष:
		width = 20;
		अवरोध;
	पूर्ण

	cf1 = chandef->center_freq1;

	n_chan = ibss_setup_channels(wiphy, channels, channels_max, cf1, width);

	अगर (cf2)
		n_chan += ibss_setup_channels(wiphy, &channels[n_chan],
					      channels_max - n_chan, cf2,
					      width);

	वापस n_chan;
पूर्ण

/*
 * This function is called with state == IEEE80211_IBSS_MLME_SEARCH
 */

अटल व्योम ieee80211_sta_find_ibss(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा cfg80211_bss *cbss;
	काष्ठा ieee80211_channel *chan = शून्य;
	स्थिर u8 *bssid = शून्य;
	क्रमागत nl80211_bss_scan_width scan_width;
	पूर्णांक active_ibss;

	sdata_निश्चित_lock(sdata);

	active_ibss = ieee80211_sta_active_ibss(sdata);
	ibss_dbg(sdata, "sta_find_ibss (active_ibss=%d)\n", active_ibss);

	अगर (active_ibss)
		वापस;

	अगर (अगरibss->fixed_bssid)
		bssid = अगरibss->bssid;
	अगर (अगरibss->fixed_channel)
		chan = अगरibss->chandef.chan;
	अगर (!is_zero_ether_addr(अगरibss->bssid))
		bssid = अगरibss->bssid;
	cbss = cfg80211_get_bss(local->hw.wiphy, chan, bssid,
				अगरibss->ssid, अगरibss->ssid_len,
				IEEE80211_BSS_TYPE_IBSS,
				IEEE80211_PRIVACY(अगरibss->privacy));

	अगर (cbss) अणु
		काष्ठा ieee80211_bss *bss;

		bss = (व्योम *)cbss->priv;
		ibss_dbg(sdata,
			 "sta_find_ibss: selected %pM current %pM\n",
			 cbss->bssid, अगरibss->bssid);
		sdata_info(sdata,
			   "Selected IBSS BSSID %pM based on configured SSID\n",
			   cbss->bssid);

		ieee80211_sta_join_ibss(sdata, bss);
		ieee80211_rx_bss_put(local, bss);
		वापस;
	पूर्ण

	/* अगर a fixed bssid and a fixed freq have been provided create the IBSS
	 * directly and करो not waste समय scanning
	 */
	अगर (अगरibss->fixed_bssid && अगरibss->fixed_channel) अणु
		sdata_info(sdata, "Created IBSS using preconfigured BSSID %pM\n",
			   bssid);
		ieee80211_sta_create_ibss(sdata);
		वापस;
	पूर्ण


	ibss_dbg(sdata, "sta_find_ibss: did not try to join ibss\n");

	/* Selected IBSS not found in current scan results - try to scan */
	अगर (समय_after(jअगरfies, अगरibss->last_scan_completed +
					IEEE80211_SCAN_INTERVAL)) अणु
		काष्ठा ieee80211_channel *channels[8];
		अचिन्हित पूर्णांक num;

		sdata_info(sdata, "Trigger new scan to find an IBSS to join\n");

		scan_width = cfg80211_chandef_to_scan_width(&अगरibss->chandef);

		अगर (अगरibss->fixed_channel) अणु
			num = ieee80211_ibss_setup_scan_channels(local->hw.wiphy,
								 &अगरibss->chandef,
								 channels,
								 ARRAY_SIZE(channels));
			ieee80211_request_ibss_scan(sdata, अगरibss->ssid,
						    अगरibss->ssid_len, channels,
						    num, scan_width);
		पूर्ण अन्यथा अणु
			ieee80211_request_ibss_scan(sdata, अगरibss->ssid,
						    अगरibss->ssid_len, शून्य,
						    0, scan_width);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक पूर्णांकerval = IEEE80211_SCAN_INTERVAL;

		अगर (समय_after(jअगरfies, अगरibss->ibss_join_req +
			       IEEE80211_IBSS_JOIN_TIMEOUT))
			ieee80211_sta_create_ibss(sdata);

		mod_समयr(&अगरibss->समयr,
			  round_jअगरfies(jअगरfies + पूर्णांकerval));
	पूर्ण
पूर्ण

अटल व्योम ieee80211_rx_mgmt_probe_req(काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा sk_buff *req)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)req->data;
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक tx_last_beacon, len = req->len;
	काष्ठा sk_buff *skb;
	काष्ठा beacon_data *presp;
	u8 *pos, *end;

	sdata_निश्चित_lock(sdata);

	presp = rcu_dereference_रक्षित(अगरibss->presp,
					  lockdep_is_held(&sdata->wdev.mtx));

	अगर (अगरibss->state != IEEE80211_IBSS_MLME_JOINED ||
	    len < 24 + 2 || !presp)
		वापस;

	tx_last_beacon = drv_tx_last_beacon(local);

	ibss_dbg(sdata, "RX ProbeReq SA=%pM DA=%pM\n", mgmt->sa, mgmt->da);
	ibss_dbg(sdata, "\tBSSID=%pM (tx_last_beacon=%d)\n",
		 mgmt->bssid, tx_last_beacon);

	अगर (!tx_last_beacon && is_multicast_ether_addr(mgmt->da))
		वापस;

	अगर (!ether_addr_equal(mgmt->bssid, अगरibss->bssid) &&
	    !is_broadcast_ether_addr(mgmt->bssid))
		वापस;

	end = ((u8 *) mgmt) + len;
	pos = mgmt->u.probe_req.variable;
	अगर (pos[0] != WLAN_EID_SSID ||
	    pos + 2 + pos[1] > end) अणु
		ibss_dbg(sdata, "Invalid SSID IE in ProbeReq from %pM\n",
			 mgmt->sa);
		वापस;
	पूर्ण
	अगर (pos[1] != 0 &&
	    (pos[1] != अगरibss->ssid_len ||
	     स_भेद(pos + 2, अगरibss->ssid, अगरibss->ssid_len))) अणु
		/* Ignore ProbeReq क्रम क्रमeign SSID */
		वापस;
	पूर्ण

	/* Reply with ProbeResp */
	skb = dev_alloc_skb(local->tx_headroom + presp->head_len);
	अगर (!skb)
		वापस;

	skb_reserve(skb, local->tx_headroom);
	skb_put_data(skb, presp->head, presp->head_len);

	स_नकल(((काष्ठा ieee80211_mgmt *) skb->data)->da, mgmt->sa, ETH_ALEN);
	ibss_dbg(sdata, "Sending ProbeResp to %pM\n", mgmt->sa);
	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT;

	/* aव्योम excessive retries क्रम probe request to wildcard SSIDs */
	अगर (pos[1] == 0)
		IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_CTL_NO_ACK;

	ieee80211_tx_skb(sdata, skb);
पूर्ण

अटल
व्योम ieee80211_rx_mgmt_probe_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
				    काष्ठा ieee80211_rx_status *rx_status)
अणु
	माप_प्रकार baselen;
	काष्ठा ieee802_11_elems elems;

	BUILD_BUG_ON(दुरत्व(typeof(mgmt->u.probe_resp), variable) !=
		     दुरत्व(typeof(mgmt->u.beacon), variable));

	/*
	 * either beacon or probe_resp but the variable field is at the
	 * same offset
	 */
	baselen = (u8 *) mgmt->u.probe_resp.variable - (u8 *) mgmt;
	अगर (baselen > len)
		वापस;

	ieee802_11_parse_elems(mgmt->u.probe_resp.variable, len - baselen,
			       false, &elems, mgmt->bssid, शून्य);

	ieee80211_rx_bss_info(sdata, mgmt, len, rx_status, &elems);
पूर्ण

व्योम ieee80211_ibss_rx_queued_mgmt(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *rx_status;
	काष्ठा ieee80211_mgmt *mgmt;
	u16 fc;
	काष्ठा ieee802_11_elems elems;
	पूर्णांक ies_len;

	rx_status = IEEE80211_SKB_RXCB(skb);
	mgmt = (काष्ठा ieee80211_mgmt *) skb->data;
	fc = le16_to_cpu(mgmt->frame_control);

	sdata_lock(sdata);

	अगर (!sdata->u.ibss.ssid_len)
		जाओ mgmt_out; /* not पढ़ोy to merge yet */

	चयन (fc & IEEE80211_FCTL_STYPE) अणु
	हाल IEEE80211_STYPE_PROBE_REQ:
		ieee80211_rx_mgmt_probe_req(sdata, skb);
		अवरोध;
	हाल IEEE80211_STYPE_PROBE_RESP:
	हाल IEEE80211_STYPE_BEACON:
		ieee80211_rx_mgmt_probe_beacon(sdata, mgmt, skb->len,
					       rx_status);
		अवरोध;
	हाल IEEE80211_STYPE_AUTH:
		ieee80211_rx_mgmt_auth_ibss(sdata, mgmt, skb->len);
		अवरोध;
	हाल IEEE80211_STYPE_DEAUTH:
		ieee80211_rx_mgmt_deauth_ibss(sdata, mgmt, skb->len);
		अवरोध;
	हाल IEEE80211_STYPE_ACTION:
		चयन (mgmt->u.action.category) अणु
		हाल WLAN_CATEGORY_SPECTRUM_MGMT:
			ies_len = skb->len -
				  दुरत्व(काष्ठा ieee80211_mgmt,
					   u.action.u.chan_चयन.variable);

			अगर (ies_len < 0)
				अवरोध;

			ieee802_11_parse_elems(
				mgmt->u.action.u.chan_चयन.variable,
				ies_len, true, &elems, mgmt->bssid, शून्य);

			अगर (elems.parse_error)
				अवरोध;

			ieee80211_rx_mgmt_spectrum_mgmt(sdata, mgmt, skb->len,
							rx_status, &elems);
			अवरोध;
		पूर्ण
	पूर्ण

 mgmt_out:
	sdata_unlock(sdata);
पूर्ण

व्योम ieee80211_ibss_work(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;
	काष्ठा sta_info *sta;

	sdata_lock(sdata);

	/*
	 * Work could be scheduled after scan or similar
	 * when we aren't even joined (or trying) with a
	 * network.
	 */
	अगर (!अगरibss->ssid_len)
		जाओ out;

	spin_lock_bh(&अगरibss->incomplete_lock);
	जबतक (!list_empty(&अगरibss->incomplete_stations)) अणु
		sta = list_first_entry(&अगरibss->incomplete_stations,
				       काष्ठा sta_info, list);
		list_del(&sta->list);
		spin_unlock_bh(&अगरibss->incomplete_lock);

		ieee80211_ibss_finish_sta(sta);
		rcu_पढ़ो_unlock();
		spin_lock_bh(&अगरibss->incomplete_lock);
	पूर्ण
	spin_unlock_bh(&अगरibss->incomplete_lock);

	चयन (अगरibss->state) अणु
	हाल IEEE80211_IBSS_MLME_SEARCH:
		ieee80211_sta_find_ibss(sdata);
		अवरोध;
	हाल IEEE80211_IBSS_MLME_JOINED:
		ieee80211_sta_merge_ibss(sdata);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

 out:
	sdata_unlock(sdata);
पूर्ण

अटल व्योम ieee80211_ibss_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		from_समयr(sdata, t, u.ibss.समयr);

	ieee80211_queue_work(&sdata->local->hw, &sdata->work);
पूर्ण

व्योम ieee80211_ibss_setup_sdata(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;

	समयr_setup(&अगरibss->समयr, ieee80211_ibss_समयr, 0);
	INIT_LIST_HEAD(&अगरibss->incomplete_stations);
	spin_lock_init(&अगरibss->incomplete_lock);
	INIT_WORK(&अगरibss->csa_connection_drop_work,
		  ieee80211_csa_connection_drop_work);
पूर्ण

/* scan finished notअगरication */
व्योम ieee80211_ibss_notअगरy_scan_completed(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	mutex_lock(&local->अगरlist_mtx);
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(sdata))
			जारी;
		अगर (sdata->vअगर.type != NL80211_IFTYPE_ADHOC)
			जारी;
		sdata->u.ibss.last_scan_completed = jअगरfies;
	पूर्ण
	mutex_unlock(&local->अगरlist_mtx);
पूर्ण

पूर्णांक ieee80211_ibss_join(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा cfg80211_ibss_params *params)
अणु
	u32 changed = 0;
	u32 rate_flags;
	काष्ठा ieee80211_supported_band *sband;
	क्रमागत ieee80211_chanctx_mode chanmode;
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक radar_detect_width = 0;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (params->chandef.chan->freq_offset) अणु
		/* this may work, but is untested */
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = cfg80211_chandef_dfs_required(local->hw.wiphy,
					    &params->chandef,
					    sdata->wdev.अगरtype);
	अगर (ret < 0)
		वापस ret;

	अगर (ret > 0) अणु
		अगर (!params->userspace_handles_dfs)
			वापस -EINVAL;
		radar_detect_width = BIT(params->chandef.width);
	पूर्ण

	chanmode = (params->channel_fixed && !ret) ?
		IEEE80211_CHANCTX_SHARED : IEEE80211_CHANCTX_EXCLUSIVE;

	mutex_lock(&local->chanctx_mtx);
	ret = ieee80211_check_combinations(sdata, &params->chandef, chanmode,
					   radar_detect_width);
	mutex_unlock(&local->chanctx_mtx);
	अगर (ret < 0)
		वापस ret;

	अगर (params->bssid) अणु
		स_नकल(sdata->u.ibss.bssid, params->bssid, ETH_ALEN);
		sdata->u.ibss.fixed_bssid = true;
	पूर्ण अन्यथा
		sdata->u.ibss.fixed_bssid = false;

	sdata->u.ibss.privacy = params->privacy;
	sdata->u.ibss.control_port = params->control_port;
	sdata->u.ibss.userspace_handles_dfs = params->userspace_handles_dfs;
	sdata->u.ibss.basic_rates = params->basic_rates;
	sdata->u.ibss.last_scan_completed = jअगरfies;

	/* fix basic_rates अगर channel करोes not support these rates */
	rate_flags = ieee80211_chandef_rate_flags(&params->chandef);
	sband = local->hw.wiphy->bands[params->chandef.chan->band];
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			sdata->u.ibss.basic_rates &= ~BIT(i);
	पूर्ण
	स_नकल(sdata->vअगर.bss_conf.mcast_rate, params->mcast_rate,
	       माप(params->mcast_rate));

	sdata->vअगर.bss_conf.beacon_पूर्णांक = params->beacon_पूर्णांकerval;

	sdata->u.ibss.chandef = params->chandef;
	sdata->u.ibss.fixed_channel = params->channel_fixed;

	अगर (params->ie) अणु
		sdata->u.ibss.ie = kmemdup(params->ie, params->ie_len,
					   GFP_KERNEL);
		अगर (sdata->u.ibss.ie)
			sdata->u.ibss.ie_len = params->ie_len;
	पूर्ण

	sdata->u.ibss.state = IEEE80211_IBSS_MLME_SEARCH;
	sdata->u.ibss.ibss_join_req = jअगरfies;

	स_नकल(sdata->u.ibss.ssid, params->ssid, params->ssid_len);
	sdata->u.ibss.ssid_len = params->ssid_len;

	स_नकल(&sdata->u.ibss.ht_capa, &params->ht_capa,
	       माप(sdata->u.ibss.ht_capa));
	स_नकल(&sdata->u.ibss.ht_capa_mask, &params->ht_capa_mask,
	       माप(sdata->u.ibss.ht_capa_mask));

	/*
	 * 802.11n-2009 9.13.3.1: In an IBSS, the HT Protection field is
	 * reserved, but an HT STA shall protect HT transmissions as though
	 * the HT Protection field were set to non-HT mixed mode.
	 *
	 * In an IBSS, the RIFS Mode field of the HT Operation element is
	 * also reserved, but an HT STA shall operate as though this field
	 * were set to 1.
	 */

	sdata->vअगर.bss_conf.ht_operation_mode |=
		  IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED
		| IEEE80211_HT_PARAM_RIFS_MODE;

	changed |= BSS_CHANGED_HT | BSS_CHANGED_MCAST_RATE;
	ieee80211_bss_info_change_notअगरy(sdata, changed);

	sdata->smps_mode = IEEE80211_SMPS_OFF;
	sdata->needed_rx_chains = local->rx_chains;
	sdata->control_port_over_nl80211 = params->control_port_over_nl80211;

	ieee80211_queue_work(&local->hw, &sdata->work);

	वापस 0;
पूर्ण

पूर्णांक ieee80211_ibss_leave(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ibss *अगरibss = &sdata->u.ibss;

	ieee80211_ibss_disconnect(sdata);
	अगरibss->ssid_len = 0;
	eth_zero_addr(अगरibss->bssid);

	/* हटाओ beacon */
	kमुक्त(sdata->u.ibss.ie);
	sdata->u.ibss.ie = शून्य;
	sdata->u.ibss.ie_len = 0;

	/* on the next join, re-program HT parameters */
	स_रखो(&अगरibss->ht_capa, 0, माप(अगरibss->ht_capa));
	स_रखो(&अगरibss->ht_capa_mask, 0, माप(अगरibss->ht_capa_mask));

	synchronize_rcu();

	skb_queue_purge(&sdata->skb_queue);

	del_समयr_sync(&sdata->u.ibss.समयr);

	वापस 0;
पूर्ण
