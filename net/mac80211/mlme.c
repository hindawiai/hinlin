<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BSS client mode implementation
 * Copyright 2003-2008, Jouni Malinen <j@w1.fi>
 * Copyright 2004, Instant802 Networks, Inc.
 * Copyright 2005, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007, Michael Wu <flamingice@sourmilk.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright (C) 2015 - 2017 Intel Deutschland GmbH
 * Copyright (C) 2018 - 2020 Intel Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/fips.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/mac80211.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "rate.h"
#समावेश "led.h"
#समावेश "fils_aead.h"

#घोषणा IEEE80211_AUTH_TIMEOUT		(HZ / 5)
#घोषणा IEEE80211_AUTH_TIMEOUT_LONG	(HZ / 2)
#घोषणा IEEE80211_AUTH_TIMEOUT_SHORT	(HZ / 10)
#घोषणा IEEE80211_AUTH_TIMEOUT_SAE	(HZ * 2)
#घोषणा IEEE80211_AUTH_MAX_TRIES	3
#घोषणा IEEE80211_AUTH_WAIT_ASSOC	(HZ * 5)
#घोषणा IEEE80211_ASSOC_TIMEOUT		(HZ / 5)
#घोषणा IEEE80211_ASSOC_TIMEOUT_LONG	(HZ / 2)
#घोषणा IEEE80211_ASSOC_TIMEOUT_SHORT	(HZ / 10)
#घोषणा IEEE80211_ASSOC_MAX_TRIES	3

अटल पूर्णांक max_nullfunc_tries = 2;
module_param(max_nullfunc_tries, पूर्णांक, 0644);
MODULE_PARM_DESC(max_nullfunc_tries,
		 "Maximum nullfunc tx tries before disconnecting (reason 4).");

अटल पूर्णांक max_probe_tries = 5;
module_param(max_probe_tries, पूर्णांक, 0644);
MODULE_PARM_DESC(max_probe_tries,
		 "Maximum probe tries before disconnecting (reason 4).");

/*
 * Beacon loss समयout is calculated as N frames बार the
 * advertised beacon पूर्णांकerval.  This may need to be somewhat
 * higher than what hardware might detect to account क्रम
 * delays in the host processing frames. But since we also
 * probe on beacon miss beक्रमe declaring the connection lost
 * शेष to what we want.
 */
अटल पूर्णांक beacon_loss_count = 7;
module_param(beacon_loss_count, पूर्णांक, 0644);
MODULE_PARM_DESC(beacon_loss_count,
		 "Number of beacon intervals before we decide beacon was lost.");

/*
 * Time the connection can be idle beक्रमe we probe
 * it to see अगर we can still talk to the AP.
 */
#घोषणा IEEE80211_CONNECTION_IDLE_TIME	(30 * HZ)
/*
 * Time we रुको क्रम a probe response after sending
 * a probe request because of beacon loss or क्रम
 * checking the connection still works.
 */
अटल पूर्णांक probe_रुको_ms = 500;
module_param(probe_रुको_ms, पूर्णांक, 0644);
MODULE_PARM_DESC(probe_रुको_ms,
		 "Maximum time(ms) to wait for probe response"
		 " before disconnecting (reason 4).");

/*
 * How many Beacon frames need to have been used in average संकेत strength
 * beक्रमe starting to indicate संकेत change events.
 */
#घोषणा IEEE80211_SIGNAL_AVE_MIN_COUNT	4

/*
 * We can have multiple work items (and connection probing)
 * scheduling this समयr, but we need to take care to only
 * reschedule it when it should fire _earlier_ than it was
 * asked क्रम beक्रमe, or अगर it's not pending right now. This
 * function ensures that. Note that it then is required to
 * run this function क्रम all समयouts after the first one
 * has happened -- the work that runs from this समयr will
 * करो that.
 */
अटल व्योम run_again(काष्ठा ieee80211_sub_अगर_data *sdata,
		      अचिन्हित दीर्घ समयout)
अणु
	sdata_निश्चित_lock(sdata);

	अगर (!समयr_pending(&sdata->u.mgd.समयr) ||
	    समय_beक्रमe(समयout, sdata->u.mgd.समयr.expires))
		mod_समयr(&sdata->u.mgd.समयr, समयout);
पूर्ण

व्योम ieee80211_sta_reset_beacon_monitor(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (sdata->vअगर.driver_flags & IEEE80211_VIF_BEACON_FILTER)
		वापस;

	अगर (ieee80211_hw_check(&sdata->local->hw, CONNECTION_MONITOR))
		वापस;

	mod_समयr(&sdata->u.mgd.bcn_mon_समयr,
		  round_jअगरfies_up(jअगरfies + sdata->u.mgd.beacon_समयout));
पूर्ण

व्योम ieee80211_sta_reset_conn_monitor(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	अगर (unlikely(!अगरmgd->associated))
		वापस;

	अगर (अगरmgd->probe_send_count)
		अगरmgd->probe_send_count = 0;

	अगर (ieee80211_hw_check(&sdata->local->hw, CONNECTION_MONITOR))
		वापस;

	mod_समयr(&अगरmgd->conn_mon_समयr,
		  round_jअगरfies_up(jअगरfies + IEEE80211_CONNECTION_IDLE_TIME));
पूर्ण

अटल पूर्णांक ecw2cw(पूर्णांक ecw)
अणु
	वापस (1 << ecw) - 1;
पूर्ण

अटल u32
ieee80211_determine_chantype(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा ieee80211_supported_band *sband,
			     काष्ठा ieee80211_channel *channel,
			     u32 vht_cap_info,
			     स्थिर काष्ठा ieee80211_ht_operation *ht_oper,
			     स्थिर काष्ठा ieee80211_vht_operation *vht_oper,
			     स्थिर काष्ठा ieee80211_he_operation *he_oper,
			     स्थिर काष्ठा ieee80211_s1g_oper_ie *s1g_oper,
			     काष्ठा cfg80211_chan_def *chandef, bool tracking)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा cfg80211_chan_def vht_chandef;
	काष्ठा ieee80211_sta_ht_cap sta_ht_cap;
	u32 ht_cfreq, ret;

	स_रखो(chandef, 0, माप(काष्ठा cfg80211_chan_def));
	chandef->chan = channel;
	chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
	chandef->center_freq1 = channel->center_freq;
	chandef->freq1_offset = channel->freq_offset;

	अगर (channel->band == NL80211_BAND_6GHZ) अणु
		अगर (!ieee80211_chandef_he_6ghz_oper(sdata, he_oper, chandef))
			ret = IEEE80211_STA_DISABLE_HT |
			      IEEE80211_STA_DISABLE_VHT |
			      IEEE80211_STA_DISABLE_HE;
		अन्यथा
			ret = 0;
		vht_chandef = *chandef;
		जाओ out;
	पूर्ण अन्यथा अगर (sband->band == NL80211_BAND_S1GHZ) अणु
		अगर (!ieee80211_chandef_s1g_oper(s1g_oper, chandef)) अणु
			sdata_info(sdata,
				   "Missing S1G Operation Element? Trying operating == primary\n");
			chandef->width = ieee80211_s1g_channel_width(channel);
		पूर्ण

		ret = IEEE80211_STA_DISABLE_HT | IEEE80211_STA_DISABLE_40MHZ |
		      IEEE80211_STA_DISABLE_VHT |
		      IEEE80211_STA_DISABLE_80P80MHZ |
		      IEEE80211_STA_DISABLE_160MHZ;
		जाओ out;
	पूर्ण

	स_नकल(&sta_ht_cap, &sband->ht_cap, माप(sta_ht_cap));
	ieee80211_apply_htcap_overrides(sdata, &sta_ht_cap);

	अगर (!ht_oper || !sta_ht_cap.ht_supported) अणु
		ret = IEEE80211_STA_DISABLE_HT |
		      IEEE80211_STA_DISABLE_VHT |
		      IEEE80211_STA_DISABLE_HE;
		जाओ out;
	पूर्ण

	chandef->width = NL80211_CHAN_WIDTH_20;

	ht_cfreq = ieee80211_channel_to_frequency(ht_oper->primary_chan,
						  channel->band);
	/* check that channel matches the right operating channel */
	अगर (!tracking && channel->center_freq != ht_cfreq) अणु
		/*
		 * It's possible that some APs are confused here;
		 * Netgear WNDR3700 someबार reports 4 higher than
		 * the actual channel in association responses, but
		 * since we look at probe response/beacon data here
		 * it should be OK.
		 */
		sdata_info(sdata,
			   "Wrong control channel: center-freq: %d ht-cfreq: %d ht->primary_chan: %d band: %d - Disabling HT\n",
			   channel->center_freq, ht_cfreq,
			   ht_oper->primary_chan, channel->band);
		ret = IEEE80211_STA_DISABLE_HT |
		      IEEE80211_STA_DISABLE_VHT |
		      IEEE80211_STA_DISABLE_HE;
		जाओ out;
	पूर्ण

	/* check 40 MHz support, अगर we have it */
	अगर (sta_ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) अणु
		ieee80211_chandef_ht_oper(ht_oper, chandef);
	पूर्ण अन्यथा अणु
		/* 40 MHz (and 80 MHz) must be supported क्रम VHT */
		ret = IEEE80211_STA_DISABLE_VHT;
		/* also mark 40 MHz disabled */
		ret |= IEEE80211_STA_DISABLE_40MHZ;
		जाओ out;
	पूर्ण

	अगर (!vht_oper || !sband->vht_cap.vht_supported) अणु
		ret = IEEE80211_STA_DISABLE_VHT;
		जाओ out;
	पूर्ण

	vht_chandef = *chandef;
	अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_HE) && he_oper &&
	    (le32_to_cpu(he_oper->he_oper_params) &
	     IEEE80211_HE_OPERATION_VHT_OPER_INFO)) अणु
		काष्ठा ieee80211_vht_operation he_oper_vht_cap;

		/*
		 * Set only first 3 bytes (other 2 aren't used in
		 * ieee80211_chandef_vht_oper() anyway)
		 */
		स_नकल(&he_oper_vht_cap, he_oper->optional, 3);
		he_oper_vht_cap.basic_mcs_set = cpu_to_le16(0);

		अगर (!ieee80211_chandef_vht_oper(&sdata->local->hw, vht_cap_info,
						&he_oper_vht_cap, ht_oper,
						&vht_chandef)) अणु
			अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_HE))
				sdata_info(sdata,
					   "HE AP VHT information is invalid, disable HE\n");
			ret = IEEE80211_STA_DISABLE_HE;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (!ieee80211_chandef_vht_oper(&sdata->local->hw,
					       vht_cap_info,
					       vht_oper, ht_oper,
					       &vht_chandef)) अणु
		अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT))
			sdata_info(sdata,
				   "AP VHT information is invalid, disable VHT\n");
		ret = IEEE80211_STA_DISABLE_VHT;
		जाओ out;
	पूर्ण

	अगर (!cfg80211_chandef_valid(&vht_chandef)) अणु
		अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT))
			sdata_info(sdata,
				   "AP VHT information is invalid, disable VHT\n");
		ret = IEEE80211_STA_DISABLE_VHT;
		जाओ out;
	पूर्ण

	अगर (cfg80211_chandef_identical(chandef, &vht_chandef)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (!cfg80211_chandef_compatible(chandef, &vht_chandef)) अणु
		अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT))
			sdata_info(sdata,
				   "AP VHT information doesn't match HT, disable VHT\n");
		ret = IEEE80211_STA_DISABLE_VHT;
		जाओ out;
	पूर्ण

	*chandef = vht_chandef;

	ret = 0;

out:
	/*
	 * When tracking the current AP, करोn't करो any further checks अगर the
	 * new chandef is identical to the one we're currently using क्रम the
	 * connection. This keeps us from playing ping-pong with regulatory,
	 * without it the following can happen (क्रम example):
	 *  - connect to an AP with 80 MHz, world regकरोm allows 80 MHz
	 *  - AP advertises regकरोm US
	 *  - CRDA loads regकरोm US with 80 MHz prohibited (old database)
	 *  - the code below detects an unsupported channel, करोwngrades, and
	 *    we disconnect from the AP in the caller
	 *  - disconnect causes CRDA to reload world regकरोमुख्य and the game
	 *    starts anew.
	 * (see https://bugzilla.kernel.org/show_bug.cgi?id=70881)
	 *
	 * It seems possible that there are still scenarios with CSA or real
	 * bandwidth changes where a this could happen, but those हालs are
	 * less common and wouldn't completely prevent using the AP.
	 */
	अगर (tracking &&
	    cfg80211_chandef_identical(chandef, &sdata->vअगर.bss_conf.chandef))
		वापस ret;

	/* करोn't prपूर्णांक the message below क्रम VHT mismatch अगर VHT is disabled */
	अगर (ret & IEEE80211_STA_DISABLE_VHT)
		vht_chandef = *chandef;

	/*
	 * Ignore the DISABLED flag when we're alपढ़ोy connected and only
	 * tracking the APs beacon क्रम bandwidth changes - otherwise we
	 * might get disconnected here अगर we connect to an AP, update our
	 * regulatory inक्रमmation based on the AP's country IE and the
	 * inक्रमmation we have is wrong/outdated and disables the channel
	 * that we're actually using क्रम the connection to the AP.
	 */
	जबतक (!cfg80211_chandef_usable(sdata->local->hw.wiphy, chandef,
					tracking ? 0 :
						   IEEE80211_CHAN_DISABLED)) अणु
		अगर (WARN_ON(chandef->width == NL80211_CHAN_WIDTH_20_NOHT)) अणु
			ret = IEEE80211_STA_DISABLE_HT |
			      IEEE80211_STA_DISABLE_VHT |
			      IEEE80211_STA_DISABLE_HE;
			अवरोध;
		पूर्ण

		ret |= ieee80211_chandef_करोwngrade(chandef);
	पूर्ण

	अगर (!he_oper || !cfg80211_chandef_usable(sdata->wdev.wiphy, chandef,
						 IEEE80211_CHAN_NO_HE))
		ret |= IEEE80211_STA_DISABLE_HE;

	अगर (chandef->width != vht_chandef.width && !tracking)
		sdata_info(sdata,
			   "capabilities/regulatory prevented using AP HT/VHT configuration, downgraded\n");

	WARN_ON_ONCE(!cfg80211_chandef_valid(chandef));
	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_config_bw(काष्ठा ieee80211_sub_अगर_data *sdata,
			       काष्ठा sta_info *sta,
			       स्थिर काष्ठा ieee80211_ht_cap *ht_cap,
			       स्थिर काष्ठा ieee80211_vht_cap *vht_cap,
			       स्थिर काष्ठा ieee80211_ht_operation *ht_oper,
			       स्थिर काष्ठा ieee80211_vht_operation *vht_oper,
			       स्थिर काष्ठा ieee80211_he_operation *he_oper,
			       स्थिर काष्ठा ieee80211_s1g_oper_ie *s1g_oper,
			       स्थिर u8 *bssid, u32 *changed)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_channel *chan = sdata->vअगर.bss_conf.chandef.chan;
	काष्ठा ieee80211_supported_band *sband =
		local->hw.wiphy->bands[chan->band];
	काष्ठा cfg80211_chan_def chandef;
	u16 ht_opmode;
	u32 flags;
	क्रमागत ieee80211_sta_rx_bandwidth new_sta_bw;
	u32 vht_cap_info = 0;
	पूर्णांक ret;

	/* अगर HT was/is disabled, करोn't track any bandwidth changes */
	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_HT || !ht_oper)
		वापस 0;

	/* करोn't check VHT अगर we associated as non-VHT station */
	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_VHT)
		vht_oper = शून्य;

	/* करोn't check HE अगर we associated as non-HE station */
	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_HE ||
	    !ieee80211_get_he_sta_cap(sband))
		he_oper = शून्य;

	अगर (WARN_ON_ONCE(!sta))
		वापस -EINVAL;

	/*
	 * अगर bss configuration changed store the new one -
	 * this may be applicable even अगर channel is identical
	 */
	ht_opmode = le16_to_cpu(ht_oper->operation_mode);
	अगर (sdata->vअगर.bss_conf.ht_operation_mode != ht_opmode) अणु
		*changed |= BSS_CHANGED_HT;
		sdata->vअगर.bss_conf.ht_operation_mode = ht_opmode;
	पूर्ण

	अगर (vht_cap)
		vht_cap_info = le32_to_cpu(vht_cap->vht_cap_info);

	/* calculate new channel (type) based on HT/VHT/HE operation IEs */
	flags = ieee80211_determine_chantype(sdata, sband, chan, vht_cap_info,
					     ht_oper, vht_oper, he_oper,
					     s1g_oper, &chandef, true);

	/*
	 * Downgrade the new channel अगर we associated with restricted
	 * capabilities. For example, अगर we associated as a 20 MHz STA
	 * to a 40 MHz AP (due to regulatory, capabilities or config
	 * reasons) then चयनing to a 40 MHz channel now won't करो us
	 * any good -- we couldn't use it with the AP.
	 */
	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_80P80MHZ &&
	    chandef.width == NL80211_CHAN_WIDTH_80P80)
		flags |= ieee80211_chandef_करोwngrade(&chandef);
	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_160MHZ &&
	    chandef.width == NL80211_CHAN_WIDTH_160)
		flags |= ieee80211_chandef_करोwngrade(&chandef);
	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_40MHZ &&
	    chandef.width > NL80211_CHAN_WIDTH_20)
		flags |= ieee80211_chandef_करोwngrade(&chandef);

	अगर (cfg80211_chandef_identical(&chandef, &sdata->vअगर.bss_conf.chandef))
		वापस 0;

	sdata_info(sdata,
		   "AP %pM changed bandwidth, new config is %d.%03d MHz, "
		   "width %d (%d.%03d/%d MHz)\n",
		   अगरmgd->bssid, chandef.chan->center_freq,
		   chandef.chan->freq_offset, chandef.width,
		   chandef.center_freq1, chandef.freq1_offset,
		   chandef.center_freq2);

	अगर (flags != (अगरmgd->flags & (IEEE80211_STA_DISABLE_HT |
				      IEEE80211_STA_DISABLE_VHT |
				      IEEE80211_STA_DISABLE_HE |
				      IEEE80211_STA_DISABLE_40MHZ |
				      IEEE80211_STA_DISABLE_80P80MHZ |
				      IEEE80211_STA_DISABLE_160MHZ)) ||
	    !cfg80211_chandef_valid(&chandef)) अणु
		sdata_info(sdata,
			   "AP %pM changed bandwidth in a way we can't support - disconnect\n",
			   अगरmgd->bssid);
		वापस -EINVAL;
	पूर्ण

	चयन (chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
		new_sta_bw = IEEE80211_STA_RX_BW_20;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		new_sta_bw = IEEE80211_STA_RX_BW_40;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		new_sta_bw = IEEE80211_STA_RX_BW_80;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_160:
		new_sta_bw = IEEE80211_STA_RX_BW_160;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (new_sta_bw > sta->cur_max_bandwidth)
		new_sta_bw = sta->cur_max_bandwidth;

	अगर (new_sta_bw < sta->sta.bandwidth) अणु
		sta->sta.bandwidth = new_sta_bw;
		rate_control_rate_update(local, sband, sta,
					 IEEE80211_RC_BW_CHANGED);
	पूर्ण

	ret = ieee80211_vअगर_change_bandwidth(sdata, &chandef, changed);
	अगर (ret) अणु
		sdata_info(sdata,
			   "AP %pM changed bandwidth to incompatible one - disconnect\n",
			   अगरmgd->bssid);
		वापस ret;
	पूर्ण

	अगर (new_sta_bw > sta->sta.bandwidth) अणु
		sta->sta.bandwidth = new_sta_bw;
		rate_control_rate_update(local, sband, sta,
					 IEEE80211_RC_BW_CHANGED);
	पूर्ण

	वापस 0;
पूर्ण

/* frame sending functions */

अटल व्योम ieee80211_add_ht_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा sk_buff *skb, u8 ap_ht_param,
				काष्ठा ieee80211_supported_band *sband,
				काष्ठा ieee80211_channel *channel,
				क्रमागत ieee80211_smps_mode smps)
अणु
	u8 *pos;
	u32 flags = channel->flags;
	u16 cap;
	काष्ठा ieee80211_sta_ht_cap ht_cap;

	BUILD_BUG_ON(माप(ht_cap) != माप(sband->ht_cap));

	स_नकल(&ht_cap, &sband->ht_cap, माप(ht_cap));
	ieee80211_apply_htcap_overrides(sdata, &ht_cap);

	/* determine capability flags */
	cap = ht_cap.cap;

	चयन (ap_ht_param & IEEE80211_HT_PARAM_CHA_SEC_OFFSET) अणु
	हाल IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
		अगर (flags & IEEE80211_CHAN_NO_HT40PLUS) अणु
			cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
			cap &= ~IEEE80211_HT_CAP_SGI_40;
		पूर्ण
		अवरोध;
	हाल IEEE80211_HT_PARAM_CHA_SEC_BELOW:
		अगर (flags & IEEE80211_CHAN_NO_HT40MINUS) अणु
			cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
			cap &= ~IEEE80211_HT_CAP_SGI_40;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * If 40 MHz was disabled associate as though we weren't
	 * capable of 40 MHz -- some broken APs will never fall
	 * back to trying to transmit in 20 MHz.
	 */
	अगर (sdata->u.mgd.flags & IEEE80211_STA_DISABLE_40MHZ) अणु
		cap &= ~IEEE80211_HT_CAP_SUP_WIDTH_20_40;
		cap &= ~IEEE80211_HT_CAP_SGI_40;
	पूर्ण

	/* set SM PS mode properly */
	cap &= ~IEEE80211_HT_CAP_SM_PS;
	चयन (smps) अणु
	हाल IEEE80211_SMPS_AUTOMATIC:
	हाल IEEE80211_SMPS_NUM_MODES:
		WARN_ON(1);
		fallthrough;
	हाल IEEE80211_SMPS_OFF:
		cap |= WLAN_HT_CAP_SM_PS_DISABLED <<
			IEEE80211_HT_CAP_SM_PS_SHIFT;
		अवरोध;
	हाल IEEE80211_SMPS_STATIC:
		cap |= WLAN_HT_CAP_SM_PS_STATIC <<
			IEEE80211_HT_CAP_SM_PS_SHIFT;
		अवरोध;
	हाल IEEE80211_SMPS_DYNAMIC:
		cap |= WLAN_HT_CAP_SM_PS_DYNAMIC <<
			IEEE80211_HT_CAP_SM_PS_SHIFT;
		अवरोध;
	पूर्ण

	/* reserve and fill IE */
	pos = skb_put(skb, माप(काष्ठा ieee80211_ht_cap) + 2);
	ieee80211_ie_build_ht_cap(pos, &ht_cap, cap);
पूर्ण

/* This function determines vht capability flags क्रम the association
 * and builds the IE.
 * Note - the function may set the owner of the MU-MIMO capability
 */
अटल व्योम ieee80211_add_vht_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sk_buff *skb,
				 काष्ठा ieee80211_supported_band *sband,
				 काष्ठा ieee80211_vht_cap *ap_vht_cap)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	u8 *pos;
	u32 cap;
	काष्ठा ieee80211_sta_vht_cap vht_cap;
	u32 mask, ap_bf_sts, our_bf_sts;

	BUILD_BUG_ON(माप(vht_cap) != माप(sband->vht_cap));

	स_नकल(&vht_cap, &sband->vht_cap, माप(vht_cap));
	ieee80211_apply_vhtcap_overrides(sdata, &vht_cap);

	/* determine capability flags */
	cap = vht_cap.cap;

	अगर (sdata->u.mgd.flags & IEEE80211_STA_DISABLE_80P80MHZ) अणु
		u32 bw = cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;

		cap &= ~IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;
		अगर (bw == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ ||
		    bw == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ)
			cap |= IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ;
	पूर्ण

	अगर (sdata->u.mgd.flags & IEEE80211_STA_DISABLE_160MHZ) अणु
		cap &= ~IEEE80211_VHT_CAP_SHORT_GI_160;
		cap &= ~IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;
	पूर्ण

	/*
	 * Some APs apparently get confused अगर our capabilities are better
	 * than theirs, so restrict what we advertise in the assoc request.
	 */
	अगर (!(ap_vht_cap->vht_cap_info &
			cpu_to_le32(IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE)))
		cap &= ~(IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
			 IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE);
	अन्यथा अगर (!(ap_vht_cap->vht_cap_info &
			cpu_to_le32(IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)))
		cap &= ~IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE;

	/*
	 * If some other vअगर is using the MU-MIMO capablity we cannot associate
	 * using MU-MIMO - this will lead to contradictions in the group-id
	 * mechanism.
	 * Ownership is defined since association request, in order to aव्योम
	 * simultaneous associations with MU-MIMO.
	 */
	अगर (cap & IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE) अणु
		bool disable_mu_mimo = false;
		काष्ठा ieee80211_sub_अगर_data *other;

		list_क्रम_each_entry_rcu(other, &local->पूर्णांकerfaces, list) अणु
			अगर (other->vअगर.mu_mimo_owner) अणु
				disable_mu_mimo = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (disable_mu_mimo)
			cap &= ~IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE;
		अन्यथा
			sdata->vअगर.mu_mimo_owner = true;
	पूर्ण

	mask = IEEE80211_VHT_CAP_BEAMFORMEE_STS_MASK;

	ap_bf_sts = le32_to_cpu(ap_vht_cap->vht_cap_info) & mask;
	our_bf_sts = cap & mask;

	अगर (ap_bf_sts < our_bf_sts) अणु
		cap &= ~mask;
		cap |= ap_bf_sts;
	पूर्ण

	/* reserve and fill IE */
	pos = skb_put(skb, माप(काष्ठा ieee80211_vht_cap) + 2);
	ieee80211_ie_build_vht_cap(pos, &vht_cap, cap);
पूर्ण

/* This function determines HE capability flags क्रम the association
 * and builds the IE.
 */
अटल व्योम ieee80211_add_he_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा sk_buff *skb,
				काष्ठा ieee80211_supported_band *sband)
अणु
	u8 *pos;
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap = शून्य;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	u8 he_cap_size;
	bool reg_cap = false;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (!WARN_ON_ONCE(!chanctx_conf))
		reg_cap = cfg80211_chandef_usable(sdata->wdev.wiphy,
						  &chanctx_conf->def,
						  IEEE80211_CHAN_NO_HE);

	rcu_पढ़ो_unlock();

	he_cap = ieee80211_get_he_sta_cap(sband);
	अगर (!he_cap || !reg_cap)
		वापस;

	/*
	 * TODO: the 1 added is because this temporarily is under the EXTENSION
	 * IE. Get rid of it when it moves.
	 */
	he_cap_size =
		2 + 1 + माप(he_cap->he_cap_elem) +
		ieee80211_he_mcs_nss_size(&he_cap->he_cap_elem) +
		ieee80211_he_ppe_size(he_cap->ppe_thres[0],
				      he_cap->he_cap_elem.phy_cap_info);
	pos = skb_put(skb, he_cap_size);
	ieee80211_ie_build_he_cap(pos, he_cap, pos + he_cap_size);

	ieee80211_ie_build_he_6ghz_cap(sdata, skb);
पूर्ण

अटल व्योम ieee80211_send_assoc(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_mgd_assoc_data *assoc_data = अगरmgd->assoc_data;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *mgmt;
	u8 *pos, qos_info, *ie_start;
	माप_प्रकार offset = 0, noffset;
	पूर्णांक i, count, rates_len, supp_rates_len, shअगरt;
	u16 capab;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_channel *chan;
	u32 rates = 0;
	__le16 listen_पूर्णांक;
	काष्ठा element *ext_capa = शून्य;

	/* we know it's writable, cast away the स्थिर */
	अगर (assoc_data->ie_len)
		ext_capa = (व्योम *)cfg80211_find_elem(WLAN_EID_EXT_CAPABILITY,
						      assoc_data->ie,
						      assoc_data->ie_len);

	sdata_निश्चित_lock(sdata);

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (WARN_ON(!chanctx_conf)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	chan = chanctx_conf->def.chan;
	rcu_पढ़ो_unlock();
	sband = local->hw.wiphy->bands[chan->band];
	shअगरt = ieee80211_vअगर_get_shअगरt(&sdata->vअगर);

	अगर (assoc_data->supp_rates_len) अणु
		/*
		 * Get all rates supported by the device and the AP as
		 * some APs करोn't like getting a superset of their rates
		 * in the association request (e.g. D-Link DAP 1353 in
		 * b-only mode)...
		 */
		rates_len = ieee80211_parse_bitrates(&chanctx_conf->def, sband,
						     assoc_data->supp_rates,
						     assoc_data->supp_rates_len,
						     &rates);
	पूर्ण अन्यथा अणु
		/*
		 * In हाल AP not provide any supported rates inक्रमmation
		 * beक्रमe association, we send inक्रमmation element(s) with
		 * all rates that we support.
		 */
		rates_len = 0;
		क्रम (i = 0; i < sband->n_bitrates; i++) अणु
			rates |= BIT(i);
			rates_len++;
		पूर्ण
	पूर्ण

	skb = alloc_skb(local->hw.extra_tx_headroom +
			माप(*mgmt) + /* bit too much but करोesn't matter */
			2 + assoc_data->ssid_len + /* SSID */
			4 + rates_len + /* (extended) rates */
			4 + /* घातer capability */
			2 + 2 * sband->n_channels + /* supported channels */
			2 + माप(काष्ठा ieee80211_ht_cap) + /* HT */
			2 + माप(काष्ठा ieee80211_vht_cap) + /* VHT */
			2 + 1 + माप(काष्ठा ieee80211_he_cap_elem) + /* HE */
				माप(काष्ठा ieee80211_he_mcs_nss_supp) +
				IEEE80211_HE_PPE_THRES_MAX_LEN +
			2 + 1 + माप(काष्ठा ieee80211_he_6ghz_capa) +
			assoc_data->ie_len + /* extra IEs */
			(assoc_data->fils_kek_len ? 16 /* AES-SIV */ : 0) +
			9, /* WMM */
			GFP_KERNEL);
	अगर (!skb)
		वापस;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	capab = WLAN_CAPABILITY_ESS;

	अगर (sband->band == NL80211_BAND_2GHZ) अणु
		capab |= WLAN_CAPABILITY_SHORT_SLOT_TIME;
		capab |= WLAN_CAPABILITY_SHORT_PREAMBLE;
	पूर्ण

	अगर (assoc_data->capability & WLAN_CAPABILITY_PRIVACY)
		capab |= WLAN_CAPABILITY_PRIVACY;

	अगर ((assoc_data->capability & WLAN_CAPABILITY_SPECTRUM_MGMT) &&
	    ieee80211_hw_check(&local->hw, SPECTRUM_MGMT))
		capab |= WLAN_CAPABILITY_SPECTRUM_MGMT;

	अगर (अगरmgd->flags & IEEE80211_STA_ENABLE_RRM)
		capab |= WLAN_CAPABILITY_RADIO_MEASURE;

	mgmt = skb_put_zero(skb, 24);
	स_नकल(mgmt->da, assoc_data->bss->bssid, ETH_ALEN);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(mgmt->bssid, assoc_data->bss->bssid, ETH_ALEN);

	listen_पूर्णांक = cpu_to_le16(sband->band == NL80211_BAND_S1GHZ ?
			ieee80211_encode_usf(local->hw.conf.listen_पूर्णांकerval) :
			local->hw.conf.listen_पूर्णांकerval);
	अगर (!is_zero_ether_addr(assoc_data->prev_bssid)) अणु
		skb_put(skb, 10);
		mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						  IEEE80211_STYPE_REASSOC_REQ);
		mgmt->u.reassoc_req.capab_info = cpu_to_le16(capab);
		mgmt->u.reassoc_req.listen_पूर्णांकerval = listen_पूर्णांक;
		स_नकल(mgmt->u.reassoc_req.current_ap, assoc_data->prev_bssid,
		       ETH_ALEN);
	पूर्ण अन्यथा अणु
		skb_put(skb, 4);
		mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						  IEEE80211_STYPE_ASSOC_REQ);
		mgmt->u.assoc_req.capab_info = cpu_to_le16(capab);
		mgmt->u.assoc_req.listen_पूर्णांकerval = listen_पूर्णांक;
	पूर्ण

	/* SSID */
	pos = skb_put(skb, 2 + assoc_data->ssid_len);
	ie_start = pos;
	*pos++ = WLAN_EID_SSID;
	*pos++ = assoc_data->ssid_len;
	स_नकल(pos, assoc_data->ssid, assoc_data->ssid_len);

	अगर (sband->band == NL80211_BAND_S1GHZ)
		जाओ skip_rates;

	/* add all rates which were marked to be used above */
	supp_rates_len = rates_len;
	अगर (supp_rates_len > 8)
		supp_rates_len = 8;

	pos = skb_put(skb, supp_rates_len + 2);
	*pos++ = WLAN_EID_SUPP_RATES;
	*pos++ = supp_rates_len;

	count = 0;
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर (BIT(i) & rates) अणु
			पूर्णांक rate = DIV_ROUND_UP(sband->bitrates[i].bitrate,
						5 * (1 << shअगरt));
			*pos++ = (u8) rate;
			अगर (++count == 8)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (rates_len > count) अणु
		pos = skb_put(skb, rates_len - count + 2);
		*pos++ = WLAN_EID_EXT_SUPP_RATES;
		*pos++ = rates_len - count;

		क्रम (i++; i < sband->n_bitrates; i++) अणु
			अगर (BIT(i) & rates) अणु
				पूर्णांक rate;
				rate = DIV_ROUND_UP(sband->bitrates[i].bitrate,
						    5 * (1 << shअगरt));
				*pos++ = (u8) rate;
			पूर्ण
		पूर्ण
	पूर्ण

skip_rates:
	अगर (capab & WLAN_CAPABILITY_SPECTRUM_MGMT ||
	    capab & WLAN_CAPABILITY_RADIO_MEASURE) अणु
		pos = skb_put(skb, 4);
		*pos++ = WLAN_EID_PWR_CAPABILITY;
		*pos++ = 2;
		*pos++ = 0; /* min tx घातer */
		 /* max tx घातer */
		*pos++ = ieee80211_chandef_max_घातer(&chanctx_conf->def);
	पूर्ण

	/*
	 * Per spec, we shouldn't include the list of channels अगर we advertise
	 * support क्रम extended channel चयनing, but we've always करोne that;
	 * (क्रम now?) apply this restriction only on the (new) 6 GHz band.
	 */
	अगर (capab & WLAN_CAPABILITY_SPECTRUM_MGMT &&
	    (sband->band != NL80211_BAND_6GHZ ||
	     !ext_capa || ext_capa->datalen < 1 ||
	     !(ext_capa->data[0] & WLAN_EXT_CAPA1_EXT_CHANNEL_SWITCHING))) अणु
		/* TODO: get this in reg करोमुख्य क्रमmat */
		pos = skb_put(skb, 2 * sband->n_channels + 2);
		*pos++ = WLAN_EID_SUPPORTED_CHANNELS;
		*pos++ = 2 * sband->n_channels;
		क्रम (i = 0; i < sband->n_channels; i++) अणु
			*pos++ = ieee80211_frequency_to_channel(
					sband->channels[i].center_freq);
			*pos++ = 1; /* one channel in the subband*/
		पूर्ण
	पूर्ण

	/* Set MBSSID support क्रम HE AP अगर needed */
	अगर (ieee80211_hw_check(&local->hw, SUPPORTS_ONLY_HE_MULTI_BSSID) &&
	    !(अगरmgd->flags & IEEE80211_STA_DISABLE_HE) && assoc_data->ie_len &&
	    ext_capa && ext_capa->datalen >= 3)
		ext_capa->data[2] |= WLAN_EXT_CAPA3_MULTI_BSSID_SUPPORT;

	/* अगर present, add any custom IEs that go beक्रमe HT */
	अगर (assoc_data->ie_len) अणु
		अटल स्थिर u8 beक्रमe_ht[] = अणु
			WLAN_EID_SSID,
			WLAN_EID_SUPP_RATES,
			WLAN_EID_EXT_SUPP_RATES,
			WLAN_EID_PWR_CAPABILITY,
			WLAN_EID_SUPPORTED_CHANNELS,
			WLAN_EID_RSN,
			WLAN_EID_QOS_CAPA,
			WLAN_EID_RRM_ENABLED_CAPABILITIES,
			WLAN_EID_MOBILITY_DOMAIN,
			WLAN_EID_FAST_BSS_TRANSITION,	/* reassoc only */
			WLAN_EID_RIC_DATA,		/* reassoc only */
			WLAN_EID_SUPPORTED_REGULATORY_CLASSES,
		पूर्ण;
		अटल स्थिर u8 after_ric[] = अणु
			WLAN_EID_SUPPORTED_REGULATORY_CLASSES,
			WLAN_EID_HT_CAPABILITY,
			WLAN_EID_BSS_COEX_2040,
			/* luckily this is almost always there */
			WLAN_EID_EXT_CAPABILITY,
			WLAN_EID_QOS_TRAFFIC_CAPA,
			WLAN_EID_TIM_BCAST_REQ,
			WLAN_EID_INTERWORKING,
			/* 60 GHz (Multi-band, DMG, MMS) can't happen */
			WLAN_EID_VHT_CAPABILITY,
			WLAN_EID_OPMODE_NOTIF,
		पूर्ण;

		noffset = ieee80211_ie_split_ric(assoc_data->ie,
						 assoc_data->ie_len,
						 beक्रमe_ht,
						 ARRAY_SIZE(beक्रमe_ht),
						 after_ric,
						 ARRAY_SIZE(after_ric),
						 offset);
		skb_put_data(skb, assoc_data->ie + offset, noffset - offset);
		offset = noffset;
	पूर्ण

	अगर (WARN_ON_ONCE((अगरmgd->flags & IEEE80211_STA_DISABLE_HT) &&
			 !(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT)))
		अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT;

	अगर (sband->band != NL80211_BAND_6GHZ &&
	    !(अगरmgd->flags & IEEE80211_STA_DISABLE_HT))
		ieee80211_add_ht_ie(sdata, skb, assoc_data->ap_ht_param,
				    sband, chan, sdata->smps_mode);

	/* अगर present, add any custom IEs that go beक्रमe VHT */
	अगर (assoc_data->ie_len) अणु
		अटल स्थिर u8 beक्रमe_vht[] = अणु
			/*
			 * no need to list the ones split off beक्रमe HT
			 * or generated here
			 */
			WLAN_EID_BSS_COEX_2040,
			WLAN_EID_EXT_CAPABILITY,
			WLAN_EID_QOS_TRAFFIC_CAPA,
			WLAN_EID_TIM_BCAST_REQ,
			WLAN_EID_INTERWORKING,
			/* 60 GHz (Multi-band, DMG, MMS) can't happen */
		पूर्ण;

		/* RIC alपढ़ोy taken above, so no need to handle here anymore */
		noffset = ieee80211_ie_split(assoc_data->ie, assoc_data->ie_len,
					     beक्रमe_vht, ARRAY_SIZE(beक्रमe_vht),
					     offset);
		skb_put_data(skb, assoc_data->ie + offset, noffset - offset);
		offset = noffset;
	पूर्ण

	/* अगर present, add any custom IEs that go beक्रमe HE */
	अगर (assoc_data->ie_len) अणु
		अटल स्थिर u8 beक्रमe_he[] = अणु
			/*
			 * no need to list the ones split off beक्रमe VHT
			 * or generated here
			 */
			WLAN_EID_OPMODE_NOTIF,
			WLAN_EID_EXTENSION, WLAN_EID_EXT_FUTURE_CHAN_GUIDANCE,
			/* 11ai elements */
			WLAN_EID_EXTENSION, WLAN_EID_EXT_FILS_SESSION,
			WLAN_EID_EXTENSION, WLAN_EID_EXT_FILS_PUBLIC_KEY,
			WLAN_EID_EXTENSION, WLAN_EID_EXT_FILS_KEY_CONFIRM,
			WLAN_EID_EXTENSION, WLAN_EID_EXT_FILS_HLP_CONTAINER,
			WLAN_EID_EXTENSION, WLAN_EID_EXT_FILS_IP_ADDR_ASSIGN,
			/* TODO: add 11ah/11aj/11ak elements */
		पूर्ण;

		/* RIC alपढ़ोy taken above, so no need to handle here anymore */
		noffset = ieee80211_ie_split(assoc_data->ie, assoc_data->ie_len,
					     beक्रमe_he, ARRAY_SIZE(beक्रमe_he),
					     offset);
		pos = skb_put(skb, noffset - offset);
		स_नकल(pos, assoc_data->ie + offset, noffset - offset);
		offset = noffset;
	पूर्ण

	अगर (sband->band != NL80211_BAND_6GHZ &&
	    !(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT))
		ieee80211_add_vht_ie(sdata, skb, sband,
				     &assoc_data->ap_vht_cap);

	/*
	 * If AP करोesn't support HT, mark HE as disabled.
	 * If on the 5GHz band, make sure it supports VHT.
	 */
	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_HT ||
	    (sband->band == NL80211_BAND_5GHZ &&
	     अगरmgd->flags & IEEE80211_STA_DISABLE_VHT))
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HE;

	अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_HE))
		ieee80211_add_he_ie(sdata, skb, sband);

	/* अगर present, add any custom non-venकरोr IEs that go after HE */
	अगर (assoc_data->ie_len) अणु
		noffset = ieee80211_ie_split_venकरोr(assoc_data->ie,
						    assoc_data->ie_len,
						    offset);
		skb_put_data(skb, assoc_data->ie + offset, noffset - offset);
		offset = noffset;
	पूर्ण

	अगर (assoc_data->wmm) अणु
		अगर (assoc_data->uapsd) अणु
			qos_info = अगरmgd->uapsd_queues;
			qos_info |= (अगरmgd->uapsd_max_sp_len <<
				     IEEE80211_WMM_IE_STA_QOSINFO_SP_SHIFT);
		पूर्ण अन्यथा अणु
			qos_info = 0;
		पूर्ण

		pos = ieee80211_add_wmm_info_ie(skb_put(skb, 9), qos_info);
	पूर्ण

	अगर (sband->band == NL80211_BAND_S1GHZ) अणु
		ieee80211_add_aid_request_ie(sdata, skb);
		ieee80211_add_s1g_capab_ie(sdata, &sband->s1g_cap, skb);
	पूर्ण

	/* add any reमुख्यing custom (i.e. venकरोr specअगरic here) IEs */
	अगर (assoc_data->ie_len) अणु
		noffset = assoc_data->ie_len;
		skb_put_data(skb, assoc_data->ie + offset, noffset - offset);
	पूर्ण

	अगर (assoc_data->fils_kek_len &&
	    fils_encrypt_assoc_req(skb, assoc_data) < 0) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	pos = skb_tail_poपूर्णांकer(skb);
	kमुक्त(अगरmgd->assoc_req_ies);
	अगरmgd->assoc_req_ies = kmemdup(ie_start, pos - ie_start, GFP_ATOMIC);
	अगरmgd->assoc_req_ies_len = pos - ie_start;

	drv_mgd_prepare_tx(local, sdata, 0);

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT;
	अगर (ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS))
		IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_CTL_REQ_TX_STATUS |
						IEEE80211_TX_INTFL_MLME_CONN_TX;
	ieee80211_tx_skb(sdata, skb);
पूर्ण

व्योम ieee80211_send_pspoll(काष्ठा ieee80211_local *local,
			   काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_pspoll *pspoll;
	काष्ठा sk_buff *skb;

	skb = ieee80211_pspoll_get(&local->hw, &sdata->vअगर);
	अगर (!skb)
		वापस;

	pspoll = (काष्ठा ieee80211_pspoll *) skb->data;
	pspoll->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT;
	ieee80211_tx_skb(sdata, skb);
पूर्ण

व्योम ieee80211_send_nullfunc(काष्ठा ieee80211_local *local,
			     काष्ठा ieee80211_sub_अगर_data *sdata,
			     bool घातersave)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr_3addr *nullfunc;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	/* Don't send NDPs when STA is connected HE */
	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
	    !(अगरmgd->flags & IEEE80211_STA_DISABLE_HE))
		वापस;

	skb = ieee80211_nullfunc_get(&local->hw, &sdata->vअगर,
		!ieee80211_hw_check(&local->hw, DOESNT_SUPPORT_QOS_NDP));
	अगर (!skb)
		वापस;

	nullfunc = (काष्ठा ieee80211_hdr_3addr *) skb->data;
	अगर (घातersave)
		nullfunc->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT |
					IEEE80211_TX_INTFL_OFFCHAN_TX_OK;

	अगर (ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS))
		IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_CTL_REQ_TX_STATUS;

	अगर (अगरmgd->flags & IEEE80211_STA_CONNECTION_POLL)
		IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_CTL_USE_MINRATE;

	ieee80211_tx_skb(sdata, skb);
पूर्ण

अटल व्योम ieee80211_send_4addr_nullfunc(काष्ठा ieee80211_local *local,
					  काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *nullfunc;
	__le16 fc;

	अगर (WARN_ON(sdata->vअगर.type != NL80211_IFTYPE_STATION))
		वापस;

	/* Don't send NDPs when connected HE */
	अगर (!(sdata->u.mgd.flags & IEEE80211_STA_DISABLE_HE))
		वापस;

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + 30);
	अगर (!skb)
		वापस;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	nullfunc = skb_put_zero(skb, 30);
	fc = cpu_to_le16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_शून्यFUNC |
			 IEEE80211_FCTL_FROMDS | IEEE80211_FCTL_TODS);
	nullfunc->frame_control = fc;
	स_नकल(nullfunc->addr1, sdata->u.mgd.bssid, ETH_ALEN);
	स_नकल(nullfunc->addr2, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(nullfunc->addr3, sdata->u.mgd.bssid, ETH_ALEN);
	स_नकल(nullfunc->addr4, sdata->vअगर.addr, ETH_ALEN);

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT;
	ieee80211_tx_skb(sdata, skb);
पूर्ण

/* spectrum management related things */
अटल व्योम ieee80211_chचयन_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		container_of(work, काष्ठा ieee80211_sub_अगर_data, u.mgd.chचयन_work);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	पूर्णांक ret;

	अगर (!ieee80211_sdata_running(sdata))
		वापस;

	sdata_lock(sdata);
	mutex_lock(&local->mtx);
	mutex_lock(&local->chanctx_mtx);

	अगर (!अगरmgd->associated)
		जाओ out;

	अगर (!sdata->vअगर.csa_active)
		जाओ out;

	/*
	 * using reservation isn't immediate as it may be deferred until later
	 * with multi-vअगर. once reservation is complete it will re-schedule the
	 * work with no reserved_chanctx so verअगरy chandef to check अगर it
	 * completed successfully
	 */

	अगर (sdata->reserved_chanctx) अणु
		काष्ठा ieee80211_supported_band *sband = शून्य;
		काष्ठा sta_info *mgd_sta = शून्य;
		क्रमागत ieee80211_sta_rx_bandwidth bw = IEEE80211_STA_RX_BW_20;

		/*
		 * with multi-vअगर csa driver may call ieee80211_csa_finish()
		 * many बार जबतक रुकोing क्रम other पूर्णांकerfaces to use their
		 * reservations
		 */
		अगर (sdata->reserved_पढ़ोy)
			जाओ out;

		अगर (sdata->vअगर.bss_conf.chandef.width !=
		    sdata->csa_chandef.width) अणु
			/*
			 * For managed पूर्णांकerface, we need to also update the AP
			 * station bandwidth and align the rate scale algorithm
			 * on the bandwidth change. Here we only consider the
			 * bandwidth of the new channel definition (as channel
			 * चयन flow करोes not have the full HT/VHT/HE
			 * inक्रमmation), assuming that अगर additional changes are
			 * required they would be करोne as part of the processing
			 * of the next beacon from the AP.
			 */
			चयन (sdata->csa_chandef.width) अणु
			हाल NL80211_CHAN_WIDTH_20_NOHT:
			हाल NL80211_CHAN_WIDTH_20:
			शेष:
				bw = IEEE80211_STA_RX_BW_20;
				अवरोध;
			हाल NL80211_CHAN_WIDTH_40:
				bw = IEEE80211_STA_RX_BW_40;
				अवरोध;
			हाल NL80211_CHAN_WIDTH_80:
				bw = IEEE80211_STA_RX_BW_80;
				अवरोध;
			हाल NL80211_CHAN_WIDTH_80P80:
			हाल NL80211_CHAN_WIDTH_160:
				bw = IEEE80211_STA_RX_BW_160;
				अवरोध;
			पूर्ण

			mgd_sta = sta_info_get(sdata, अगरmgd->bssid);
			sband =
				local->hw.wiphy->bands[sdata->csa_chandef.chan->band];
		पूर्ण

		अगर (sdata->vअगर.bss_conf.chandef.width >
		    sdata->csa_chandef.width) अणु
			mgd_sta->sta.bandwidth = bw;
			rate_control_rate_update(local, sband, mgd_sta,
						 IEEE80211_RC_BW_CHANGED);
		पूर्ण

		ret = ieee80211_vअगर_use_reserved_context(sdata);
		अगर (ret) अणु
			sdata_info(sdata,
				   "failed to use reserved channel context, disconnecting (err=%d)\n",
				   ret);
			ieee80211_queue_work(&sdata->local->hw,
					     &अगरmgd->csa_connection_drop_work);
			जाओ out;
		पूर्ण

		अगर (sdata->vअगर.bss_conf.chandef.width <
		    sdata->csa_chandef.width) अणु
			mgd_sta->sta.bandwidth = bw;
			rate_control_rate_update(local, sband, mgd_sta,
						 IEEE80211_RC_BW_CHANGED);
		पूर्ण

		जाओ out;
	पूर्ण

	अगर (!cfg80211_chandef_identical(&sdata->vअगर.bss_conf.chandef,
					&sdata->csa_chandef)) अणु
		sdata_info(sdata,
			   "failed to finalize channel switch, disconnecting\n");
		ieee80211_queue_work(&sdata->local->hw,
				     &अगरmgd->csa_connection_drop_work);
		जाओ out;
	पूर्ण

	अगरmgd->csa_रुकोing_bcn = true;

	ieee80211_sta_reset_beacon_monitor(sdata);
	ieee80211_sta_reset_conn_monitor(sdata);

out:
	mutex_unlock(&local->chanctx_mtx);
	mutex_unlock(&local->mtx);
	sdata_unlock(sdata);
पूर्ण

अटल व्योम ieee80211_chचयन_post_beacon(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	पूर्णांक ret;

	sdata_निश्चित_lock(sdata);

	WARN_ON(!sdata->vअगर.csa_active);

	अगर (sdata->csa_block_tx) अणु
		ieee80211_wake_vअगर_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);
		sdata->csa_block_tx = false;
	पूर्ण

	sdata->vअगर.csa_active = false;
	अगरmgd->csa_रुकोing_bcn = false;
	/*
	 * If the CSA IE is still present on the beacon after the चयन,
	 * we need to consider it as a new CSA (possibly to self).
	 */
	अगरmgd->beacon_crc_valid = false;

	ret = drv_post_channel_चयन(sdata);
	अगर (ret) अणु
		sdata_info(sdata,
			   "driver post channel switch failed, disconnecting\n");
		ieee80211_queue_work(&local->hw,
				     &अगरmgd->csa_connection_drop_work);
		वापस;
	पूर्ण

	cfg80211_ch_चयन_notअगरy(sdata->dev, &sdata->reserved_chandef);
पूर्ण

व्योम ieee80211_chचयन_करोne(काष्ठा ieee80211_vअगर *vअगर, bool success)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	trace_api_chचयन_करोne(sdata, success);
	अगर (!success) अणु
		sdata_info(sdata,
			   "driver channel switch failed, disconnecting\n");
		ieee80211_queue_work(&sdata->local->hw,
				     &अगरmgd->csa_connection_drop_work);
	पूर्ण अन्यथा अणु
		ieee80211_queue_work(&sdata->local->hw, &अगरmgd->chचयन_work);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ieee80211_chचयन_करोne);

अटल व्योम ieee80211_chचयन_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		from_समयr(sdata, t, u.mgd.chचयन_समयr);

	ieee80211_queue_work(&sdata->local->hw, &sdata->u.mgd.chचयन_work);
पूर्ण

अटल व्योम
ieee80211_sta_पात_chanचयन(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;

	अगर (!local->ops->पात_channel_चयन)
		वापस;

	mutex_lock(&local->mtx);

	mutex_lock(&local->chanctx_mtx);
	ieee80211_vअगर_unreserve_chanctx(sdata);
	mutex_unlock(&local->chanctx_mtx);

	अगर (sdata->csa_block_tx)
		ieee80211_wake_vअगर_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);

	sdata->csa_block_tx = false;
	sdata->vअगर.csa_active = false;

	mutex_unlock(&local->mtx);

	drv_पात_channel_चयन(sdata);
पूर्ण

अटल व्योम
ieee80211_sta_process_chanचयन(काष्ठा ieee80211_sub_अगर_data *sdata,
				 u64 बारtamp, u32 device_बारtamp,
				 काष्ठा ieee802_11_elems *elems,
				 bool beacon)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा cfg80211_bss *cbss = अगरmgd->associated;
	काष्ठा ieee80211_chanctx_conf *conf;
	काष्ठा ieee80211_chanctx *chanctx;
	क्रमागत nl80211_band current_band;
	काष्ठा ieee80211_csa_ie csa_ie;
	काष्ठा ieee80211_channel_चयन ch_चयन;
	काष्ठा ieee80211_bss *bss;
	पूर्णांक res;

	sdata_निश्चित_lock(sdata);

	अगर (!cbss)
		वापस;

	अगर (local->scanning)
		वापस;

	current_band = cbss->channel->band;
	bss = (व्योम *)cbss->priv;
	res = ieee80211_parse_ch_चयन_ie(sdata, elems, current_band,
					   bss->vht_cap_info,
					   अगरmgd->flags,
					   अगरmgd->associated->bssid, &csa_ie);

	अगर (!res) अणु
		ch_चयन.बारtamp = बारtamp;
		ch_चयन.device_बारtamp = device_बारtamp;
		ch_चयन.block_tx = csa_ie.mode;
		ch_चयन.chandef = csa_ie.chandef;
		ch_चयन.count = csa_ie.count;
		ch_चयन.delay = csa_ie.max_चयन_समय;
	पूर्ण

	अगर (res < 0)
		जाओ lock_and_drop_connection;

	अगर (beacon && sdata->vअगर.csa_active && !अगरmgd->csa_रुकोing_bcn) अणु
		अगर (res)
			ieee80211_sta_पात_chanचयन(sdata);
		अन्यथा
			drv_channel_चयन_rx_beacon(sdata, &ch_चयन);
		वापस;
	पूर्ण अन्यथा अगर (sdata->vअगर.csa_active || res) अणु
		/* disregard subsequent announcements अगर alपढ़ोy processing */
		वापस;
	पूर्ण

	अगर (sdata->vअगर.bss_conf.chandef.chan->band !=
	    csa_ie.chandef.chan->band) अणु
		sdata_info(sdata,
			   "AP %pM switches to different band (%d MHz, width:%d, CF1/2: %d/%d MHz), disconnecting\n",
			   अगरmgd->associated->bssid,
			   csa_ie.chandef.chan->center_freq,
			   csa_ie.chandef.width, csa_ie.chandef.center_freq1,
			   csa_ie.chandef.center_freq2);
		जाओ lock_and_drop_connection;
	पूर्ण

	अगर (!cfg80211_chandef_usable(local->hw.wiphy, &csa_ie.chandef,
				     IEEE80211_CHAN_DISABLED)) अणु
		sdata_info(sdata,
			   "AP %pM switches to unsupported channel "
			   "(%d.%03d MHz, width:%d, CF1/2: %d.%03d/%d MHz), "
			   "disconnecting\n",
			   अगरmgd->associated->bssid,
			   csa_ie.chandef.chan->center_freq,
			   csa_ie.chandef.chan->freq_offset,
			   csa_ie.chandef.width, csa_ie.chandef.center_freq1,
			   csa_ie.chandef.freq1_offset,
			   csa_ie.chandef.center_freq2);
		जाओ lock_and_drop_connection;
	पूर्ण

	अगर (cfg80211_chandef_identical(&csa_ie.chandef,
				       &sdata->vअगर.bss_conf.chandef) &&
	    (!csa_ie.mode || !beacon)) अणु
		अगर (अगरmgd->csa_ignored_same_chan)
			वापस;
		sdata_info(sdata,
			   "AP %pM tries to chanswitch to same channel, ignore\n",
			   अगरmgd->associated->bssid);
		अगरmgd->csa_ignored_same_chan = true;
		वापस;
	पूर्ण

	/*
	 * Drop all TDLS peers - either we disconnect or move to a dअगरferent
	 * channel from this poपूर्णांक on. There's no telling what our peer will करो.
	 * The TDLS WIDER_BW scenario is also problematic, as peers might now
	 * have an incompatible wider chandef.
	 */
	ieee80211_tearकरोwn_tdls_peers(sdata);

	mutex_lock(&local->mtx);
	mutex_lock(&local->chanctx_mtx);
	conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					 lockdep_is_held(&local->chanctx_mtx));
	अगर (!conf) अणु
		sdata_info(sdata,
			   "no channel context assigned to vif?, disconnecting\n");
		जाओ drop_connection;
	पूर्ण

	chanctx = container_of(conf, काष्ठा ieee80211_chanctx, conf);

	अगर (local->use_chanctx &&
	    !ieee80211_hw_check(&local->hw, CHANCTX_STA_CSA)) अणु
		sdata_info(sdata,
			   "driver doesn't support chan-switch with channel contexts\n");
		जाओ drop_connection;
	पूर्ण

	अगर (drv_pre_channel_चयन(sdata, &ch_चयन)) अणु
		sdata_info(sdata,
			   "preparing for channel switch failed, disconnecting\n");
		जाओ drop_connection;
	पूर्ण

	res = ieee80211_vअगर_reserve_chanctx(sdata, &csa_ie.chandef,
					    chanctx->mode, false);
	अगर (res) अणु
		sdata_info(sdata,
			   "failed to reserve channel context for channel switch, disconnecting (err=%d)\n",
			   res);
		जाओ drop_connection;
	पूर्ण
	mutex_unlock(&local->chanctx_mtx);

	sdata->vअगर.csa_active = true;
	sdata->csa_chandef = csa_ie.chandef;
	sdata->csa_block_tx = csa_ie.mode;
	अगरmgd->csa_ignored_same_chan = false;
	अगरmgd->beacon_crc_valid = false;

	अगर (sdata->csa_block_tx)
		ieee80211_stop_vअगर_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);
	mutex_unlock(&local->mtx);

	cfg80211_ch_चयन_started_notअगरy(sdata->dev, &csa_ie.chandef,
					  csa_ie.count, csa_ie.mode);

	अगर (local->ops->channel_चयन) अणु
		/* use driver's channel चयन callback */
		drv_channel_चयन(local, sdata, &ch_चयन);
		वापस;
	पूर्ण

	/* channel चयन handled in software */
	अगर (csa_ie.count <= 1)
		ieee80211_queue_work(&local->hw, &अगरmgd->chचयन_work);
	अन्यथा
		mod_समयr(&अगरmgd->chचयन_समयr,
			  TU_TO_EXP_TIME((csa_ie.count - 1) *
					 cbss->beacon_पूर्णांकerval));
	वापस;
 lock_and_drop_connection:
	mutex_lock(&local->mtx);
	mutex_lock(&local->chanctx_mtx);
 drop_connection:
	/*
	 * This is just so that the disconnect flow will know that
	 * we were trying to चयन channel and failed. In हाल the
	 * mode is 1 (we are not allowed to Tx), we will know not to
	 * send a deauthentication frame. Those two fields will be
	 * reset when the disconnection worker runs.
	 */
	sdata->vअगर.csa_active = true;
	sdata->csa_block_tx = csa_ie.mode;

	ieee80211_queue_work(&local->hw, &अगरmgd->csa_connection_drop_work);
	mutex_unlock(&local->chanctx_mtx);
	mutex_unlock(&local->mtx);
पूर्ण

अटल bool
ieee80211_find_80211h_pwr_स्थिरr(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा ieee80211_channel *channel,
				 स्थिर u8 *country_ie, u8 country_ie_len,
				 स्थिर u8 *pwr_स्थिरr_elem,
				 पूर्णांक *chan_pwr, पूर्णांक *pwr_reduction)
अणु
	काष्ठा ieee80211_country_ie_triplet *triplet;
	पूर्णांक chan = ieee80211_frequency_to_channel(channel->center_freq);
	पूर्णांक i, chan_increment;
	bool have_chan_pwr = false;

	/* Invalid IE */
	अगर (country_ie_len % 2 || country_ie_len < IEEE80211_COUNTRY_IE_MIN_LEN)
		वापस false;

	triplet = (व्योम *)(country_ie + 3);
	country_ie_len -= 3;

	चयन (channel->band) अणु
	शेष:
		WARN_ON_ONCE(1);
		fallthrough;
	हाल NL80211_BAND_2GHZ:
	हाल NL80211_BAND_60GHZ:
		chan_increment = 1;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		chan_increment = 4;
		अवरोध;
	हाल NL80211_BAND_6GHZ:
		/*
		 * In the 6 GHz band, the "maximum transmit power level"
		 * field in the triplets is reserved, and thus will be
		 * zero and we shouldn't use it to control TX घातer.
		 * The actual TX घातer will be given in the transmit
		 * घातer envelope element instead.
		 */
		वापस false;
	पूर्ण

	/* find channel */
	जबतक (country_ie_len >= 3) अणु
		u8 first_channel = triplet->chans.first_channel;

		अगर (first_channel >= IEEE80211_COUNTRY_EXTENSION_ID)
			जाओ next;

		क्रम (i = 0; i < triplet->chans.num_channels; i++) अणु
			अगर (first_channel + i * chan_increment == chan) अणु
				have_chan_pwr = true;
				*chan_pwr = triplet->chans.max_घातer;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (have_chan_pwr)
			अवरोध;

 next:
		triplet++;
		country_ie_len -= 3;
	पूर्ण

	अगर (have_chan_pwr && pwr_स्थिरr_elem)
		*pwr_reduction = *pwr_स्थिरr_elem;
	अन्यथा
		*pwr_reduction = 0;

	वापस have_chan_pwr;
पूर्ण

अटल व्योम ieee80211_find_cisco_dtpc(काष्ठा ieee80211_sub_अगर_data *sdata,
				      काष्ठा ieee80211_channel *channel,
				      स्थिर u8 *cisco_dtpc_ie,
				      पूर्णांक *pwr_level)
अणु
	/* From practical testing, the first data byte of the DTPC element
	 * seems to contain the requested dBm level, and the CLI on Cisco
	 * APs clearly state the range is -127 to 127 dBm, which indicates
	 * a चिन्हित byte, although it seemingly never actually goes negative.
	 * The other byte seems to always be zero.
	 */
	*pwr_level = (__s8)cisco_dtpc_ie[4];
पूर्ण

अटल u32 ieee80211_handle_pwr_स्थिरr(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211_channel *channel,
				       काष्ठा ieee80211_mgmt *mgmt,
				       स्थिर u8 *country_ie, u8 country_ie_len,
				       स्थिर u8 *pwr_स्थिरr_ie,
				       स्थिर u8 *cisco_dtpc_ie)
अणु
	bool has_80211h_pwr = false, has_cisco_pwr = false;
	पूर्णांक chan_pwr = 0, pwr_reduction_80211h = 0;
	पूर्णांक pwr_level_cisco, pwr_level_80211h;
	पूर्णांक new_ap_level;
	__le16 capab = mgmt->u.probe_resp.capab_info;

	अगर (ieee80211_is_s1g_beacon(mgmt->frame_control))
		वापस 0;	/* TODO */

	अगर (country_ie &&
	    (capab & cpu_to_le16(WLAN_CAPABILITY_SPECTRUM_MGMT) ||
	     capab & cpu_to_le16(WLAN_CAPABILITY_RADIO_MEASURE))) अणु
		has_80211h_pwr = ieee80211_find_80211h_pwr_स्थिरr(
			sdata, channel, country_ie, country_ie_len,
			pwr_स्थिरr_ie, &chan_pwr, &pwr_reduction_80211h);
		pwr_level_80211h =
			max_t(पूर्णांक, 0, chan_pwr - pwr_reduction_80211h);
	पूर्ण

	अगर (cisco_dtpc_ie) अणु
		ieee80211_find_cisco_dtpc(
			sdata, channel, cisco_dtpc_ie, &pwr_level_cisco);
		has_cisco_pwr = true;
	पूर्ण

	अगर (!has_80211h_pwr && !has_cisco_pwr)
		वापस 0;

	/* If we have both 802.11h and Cisco DTPC, apply both limits
	 * by picking the smallest of the two घातer levels advertised.
	 */
	अगर (has_80211h_pwr &&
	    (!has_cisco_pwr || pwr_level_80211h <= pwr_level_cisco)) अणु
		new_ap_level = pwr_level_80211h;

		अगर (sdata->ap_घातer_level == new_ap_level)
			वापस 0;

		sdata_dbg(sdata,
			  "Limiting TX power to %d (%d - %d) dBm as advertised by %pM\n",
			  pwr_level_80211h, chan_pwr, pwr_reduction_80211h,
			  sdata->u.mgd.bssid);
	पूर्ण अन्यथा अणु  /* has_cisco_pwr is always true here. */
		new_ap_level = pwr_level_cisco;

		अगर (sdata->ap_घातer_level == new_ap_level)
			वापस 0;

		sdata_dbg(sdata,
			  "Limiting TX power to %d dBm as advertised by %pM\n",
			  pwr_level_cisco, sdata->u.mgd.bssid);
	पूर्ण

	sdata->ap_घातer_level = new_ap_level;
	अगर (__ieee80211_recalc_txघातer(sdata))
		वापस BSS_CHANGED_TXPOWER;
	वापस 0;
पूर्ण

/* घातersave */
अटल व्योम ieee80211_enable_ps(काष्ठा ieee80211_local *local,
				काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_conf *conf = &local->hw.conf;

	/*
	 * If we are scanning right now then the parameters will
	 * take effect when scan finishes.
	 */
	अगर (local->scanning)
		वापस;

	अगर (conf->dynamic_ps_समयout > 0 &&
	    !ieee80211_hw_check(&local->hw, SUPPORTS_DYNAMIC_PS)) अणु
		mod_समयr(&local->dynamic_ps_समयr, jअगरfies +
			  msecs_to_jअगरfies(conf->dynamic_ps_समयout));
	पूर्ण अन्यथा अणु
		अगर (ieee80211_hw_check(&local->hw, PS_शून्यFUNC_STACK))
			ieee80211_send_nullfunc(local, sdata, true);

		अगर (ieee80211_hw_check(&local->hw, PS_शून्यFUNC_STACK) &&
		    ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS))
			वापस;

		conf->flags |= IEEE80211_CONF_PS;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);
	पूर्ण
पूर्ण

अटल व्योम ieee80211_change_ps(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_conf *conf = &local->hw.conf;

	अगर (local->ps_sdata) अणु
		ieee80211_enable_ps(local, local->ps_sdata);
	पूर्ण अन्यथा अगर (conf->flags & IEEE80211_CONF_PS) अणु
		conf->flags &= ~IEEE80211_CONF_PS;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);
		del_समयr_sync(&local->dynamic_ps_समयr);
		cancel_work_sync(&local->dynamic_ps_enable_work);
	पूर्ण
पूर्ण

अटल bool ieee80211_घातersave_allowed(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_managed *mgd = &sdata->u.mgd;
	काष्ठा sta_info *sta = शून्य;
	bool authorized = false;

	अगर (!mgd->घातersave)
		वापस false;

	अगर (mgd->broken_ap)
		वापस false;

	अगर (!mgd->associated)
		वापस false;

	अगर (mgd->flags & IEEE80211_STA_CONNECTION_POLL)
		वापस false;

	अगर (!mgd->have_beacon)
		वापस false;

	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, mgd->bssid);
	अगर (sta)
		authorized = test_sta_flag(sta, WLAN_STA_AUTHORIZED);
	rcu_पढ़ो_unlock();

	वापस authorized;
पूर्ण

/* need to hold RTNL or पूर्णांकerface lock */
व्योम ieee80211_recalc_ps(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata, *found = शून्य;
	पूर्णांक count = 0;
	पूर्णांक समयout;

	अगर (!ieee80211_hw_check(&local->hw, SUPPORTS_PS)) अणु
		local->ps_sdata = शून्य;
		वापस;
	पूर्ण

	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(sdata))
			जारी;
		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
			/* If an AP vअगर is found, then disable PS
			 * by setting the count to zero thereby setting
			 * ps_sdata to शून्य.
			 */
			count = 0;
			अवरोध;
		पूर्ण
		अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
			जारी;
		found = sdata;
		count++;
	पूर्ण

	अगर (count == 1 && ieee80211_घातersave_allowed(found)) अणु
		u8 dtimper = found->u.mgd.dtim_period;

		समयout = local->dynamic_ps_क्रमced_समयout;
		अगर (समयout < 0)
			समयout = 100;
		local->hw.conf.dynamic_ps_समयout = समयout;

		/* If the TIM IE is invalid, pretend the value is 1 */
		अगर (!dtimper)
			dtimper = 1;

		local->hw.conf.ps_dtim_period = dtimper;
		local->ps_sdata = found;
	पूर्ण अन्यथा अणु
		local->ps_sdata = शून्य;
	पूर्ण

	ieee80211_change_ps(local);
पूर्ण

व्योम ieee80211_recalc_ps_vअगर(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	bool ps_allowed = ieee80211_घातersave_allowed(sdata);

	अगर (sdata->vअगर.bss_conf.ps != ps_allowed) अणु
		sdata->vअगर.bss_conf.ps = ps_allowed;
		ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_PS);
	पूर्ण
पूर्ण

व्योम ieee80211_dynamic_ps_disable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local =
		container_of(work, काष्ठा ieee80211_local,
			     dynamic_ps_disable_work);

	अगर (local->hw.conf.flags & IEEE80211_CONF_PS) अणु
		local->hw.conf.flags &= ~IEEE80211_CONF_PS;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);
	पूर्ण

	ieee80211_wake_queues_by_reason(&local->hw,
					IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_PS,
					false);
पूर्ण

व्योम ieee80211_dynamic_ps_enable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local =
		container_of(work, काष्ठा ieee80211_local,
			     dynamic_ps_enable_work);
	काष्ठा ieee80211_sub_अगर_data *sdata = local->ps_sdata;
	काष्ठा ieee80211_अगर_managed *अगरmgd;
	अचिन्हित दीर्घ flags;
	पूर्णांक q;

	/* can only happen when PS was just disabled anyway */
	अगर (!sdata)
		वापस;

	अगरmgd = &sdata->u.mgd;

	अगर (local->hw.conf.flags & IEEE80211_CONF_PS)
		वापस;

	अगर (local->hw.conf.dynamic_ps_समयout > 0) अणु
		/* करोn't enter PS अगर TX frames are pending */
		अगर (drv_tx_frames_pending(local)) अणु
			mod_समयr(&local->dynamic_ps_समयr, jअगरfies +
				  msecs_to_jअगरfies(
				  local->hw.conf.dynamic_ps_समयout));
			वापस;
		पूर्ण

		/*
		 * transmission can be stopped by others which leads to
		 * dynamic_ps_समयr expiry. Postpone the ps समयr अगर it
		 * is not the actual idle state.
		 */
		spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
		क्रम (q = 0; q < local->hw.queues; q++) अणु
			अगर (local->queue_stop_reasons[q]) अणु
				spin_unlock_irqrestore(&local->queue_stop_reason_lock,
						       flags);
				mod_समयr(&local->dynamic_ps_समयr, jअगरfies +
					  msecs_to_jअगरfies(
					  local->hw.conf.dynamic_ps_समयout));
				वापस;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
	पूर्ण

	अगर (ieee80211_hw_check(&local->hw, PS_शून्यFUNC_STACK) &&
	    !(अगरmgd->flags & IEEE80211_STA_शून्यFUNC_ACKED)) अणु
		अगर (drv_tx_frames_pending(local)) अणु
			mod_समयr(&local->dynamic_ps_समयr, jअगरfies +
				  msecs_to_jअगरfies(
				  local->hw.conf.dynamic_ps_समयout));
		पूर्ण अन्यथा अणु
			ieee80211_send_nullfunc(local, sdata, true);
			/* Flush to get the tx status of nullfunc frame */
			ieee80211_flush_queues(local, sdata, false);
		पूर्ण
	पूर्ण

	अगर (!(ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS) &&
	      ieee80211_hw_check(&local->hw, PS_शून्यFUNC_STACK)) ||
	    (अगरmgd->flags & IEEE80211_STA_शून्यFUNC_ACKED)) अणु
		अगरmgd->flags &= ~IEEE80211_STA_शून्यFUNC_ACKED;
		local->hw.conf.flags |= IEEE80211_CONF_PS;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);
	पूर्ण
पूर्ण

व्योम ieee80211_dynamic_ps_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_local *local = from_समयr(local, t, dynamic_ps_समयr);

	ieee80211_queue_work(&local->hw, &local->dynamic_ps_enable_work);
पूर्ण

व्योम ieee80211_dfs_cac_समयr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा ieee80211_sub_अगर_data *sdata =
		container_of(delayed_work, काष्ठा ieee80211_sub_अगर_data,
			     dfs_cac_समयr_work);
	काष्ठा cfg80211_chan_def chandef = sdata->vअगर.bss_conf.chandef;

	mutex_lock(&sdata->local->mtx);
	अगर (sdata->wdev.cac_started) अणु
		ieee80211_vअगर_release_channel(sdata);
		cfg80211_cac_event(sdata->dev, &chandef,
				   NL80211_RADAR_CAC_FINISHED,
				   GFP_KERNEL);
	पूर्ण
	mutex_unlock(&sdata->local->mtx);
पूर्ण

अटल bool
__ieee80211_sta_handle_tspec_ac_params(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	bool ret = false;
	पूर्णांक ac;

	अगर (local->hw.queues < IEEE80211_NUM_ACS)
		वापस false;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		काष्ठा ieee80211_sta_tx_tspec *tx_tspec = &अगरmgd->tx_tspec[ac];
		पूर्णांक non_acm_ac;
		अचिन्हित दीर्घ now = jअगरfies;

		अगर (tx_tspec->action == TX_TSPEC_ACTION_NONE &&
		    tx_tspec->admitted_समय &&
		    समय_after(now, tx_tspec->समय_slice_start + HZ)) अणु
			tx_tspec->consumed_tx_समय = 0;
			tx_tspec->समय_slice_start = now;

			अगर (tx_tspec->करोwngraded)
				tx_tspec->action =
					TX_TSPEC_ACTION_STOP_DOWNGRADE;
		पूर्ण

		चयन (tx_tspec->action) अणु
		हाल TX_TSPEC_ACTION_STOP_DOWNGRADE:
			/* take the original parameters */
			अगर (drv_conf_tx(local, sdata, ac, &sdata->tx_conf[ac]))
				sdata_err(sdata,
					  "failed to set TX queue parameters for queue %d\n",
					  ac);
			tx_tspec->action = TX_TSPEC_ACTION_NONE;
			tx_tspec->करोwngraded = false;
			ret = true;
			अवरोध;
		हाल TX_TSPEC_ACTION_DOWNGRADE:
			अगर (समय_after(now, tx_tspec->समय_slice_start + HZ)) अणु
				tx_tspec->action = TX_TSPEC_ACTION_NONE;
				ret = true;
				अवरोध;
			पूर्ण
			/* करोwngrade next lower non-ACM AC */
			क्रम (non_acm_ac = ac + 1;
			     non_acm_ac < IEEE80211_NUM_ACS;
			     non_acm_ac++)
				अगर (!(sdata->wmm_acm & BIT(7 - 2 * non_acm_ac)))
					अवरोध;
			/* Usually the loop will result in using BK even अगर it
			 * requires admission control, but such a configuration
			 * makes no sense and we have to transmit somehow - the
			 * AC selection करोes the same thing.
			 * If we started out trying to करोwngrade from BK, then
			 * the extra condition here might be needed.
			 */
			अगर (non_acm_ac >= IEEE80211_NUM_ACS)
				non_acm_ac = IEEE80211_AC_BK;
			अगर (drv_conf_tx(local, sdata, ac,
					&sdata->tx_conf[non_acm_ac]))
				sdata_err(sdata,
					  "failed to set TX queue parameters for queue %d\n",
					  ac);
			tx_tspec->action = TX_TSPEC_ACTION_NONE;
			ret = true;
			schedule_delayed_work(&अगरmgd->tx_tspec_wk,
				tx_tspec->समय_slice_start + HZ - now + 1);
			अवरोध;
		हाल TX_TSPEC_ACTION_NONE:
			/* nothing now */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम ieee80211_sta_handle_tspec_ac_params(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (__ieee80211_sta_handle_tspec_ac_params(sdata))
		ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_QOS);
पूर्ण

अटल व्योम ieee80211_sta_handle_tspec_ac_params_wk(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	sdata = container_of(work, काष्ठा ieee80211_sub_अगर_data,
			     u.mgd.tx_tspec_wk.work);
	ieee80211_sta_handle_tspec_ac_params(sdata);
पूर्ण

/* MLME */
अटल bool
ieee80211_sta_wmm_params(काष्ठा ieee80211_local *local,
			 काष्ठा ieee80211_sub_अगर_data *sdata,
			 स्थिर u8 *wmm_param, माप_प्रकार wmm_param_len,
			 स्थिर काष्ठा ieee80211_mu_edca_param_set *mu_edca)
अणु
	काष्ठा ieee80211_tx_queue_params params[IEEE80211_NUM_ACS];
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	माप_प्रकार left;
	पूर्णांक count, mu_edca_count, ac;
	स्थिर u8 *pos;
	u8 uapsd_queues = 0;

	अगर (!local->ops->conf_tx)
		वापस false;

	अगर (local->hw.queues < IEEE80211_NUM_ACS)
		वापस false;

	अगर (!wmm_param)
		वापस false;

	अगर (wmm_param_len < 8 || wmm_param[5] /* version */ != 1)
		वापस false;

	अगर (अगरmgd->flags & IEEE80211_STA_UAPSD_ENABLED)
		uapsd_queues = अगरmgd->uapsd_queues;

	count = wmm_param[6] & 0x0f;
	/* -1 is the initial value of अगरmgd->mu_edca_last_param_set.
	 * अगर mu_edca was preset beक्रमe and now it disappeared tell
	 * the driver about it.
	 */
	mu_edca_count = mu_edca ? mu_edca->mu_qos_info & 0x0f : -1;
	अगर (count == अगरmgd->wmm_last_param_set &&
	    mu_edca_count == अगरmgd->mu_edca_last_param_set)
		वापस false;
	अगरmgd->wmm_last_param_set = count;
	अगरmgd->mu_edca_last_param_set = mu_edca_count;

	pos = wmm_param + 8;
	left = wmm_param_len - 8;

	स_रखो(&params, 0, माप(params));

	sdata->wmm_acm = 0;
	क्रम (; left >= 4; left -= 4, pos += 4) अणु
		पूर्णांक aci = (pos[0] >> 5) & 0x03;
		पूर्णांक acm = (pos[0] >> 4) & 0x01;
		bool uapsd = false;

		चयन (aci) अणु
		हाल 1: /* AC_BK */
			ac = IEEE80211_AC_BK;
			अगर (acm)
				sdata->wmm_acm |= BIT(1) | BIT(2); /* BK/- */
			अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK)
				uapsd = true;
			params[ac].mu_edca = !!mu_edca;
			अगर (mu_edca)
				params[ac].mu_edca_param_rec = mu_edca->ac_bk;
			अवरोध;
		हाल 2: /* AC_VI */
			ac = IEEE80211_AC_VI;
			अगर (acm)
				sdata->wmm_acm |= BIT(4) | BIT(5); /* CL/VI */
			अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI)
				uapsd = true;
			params[ac].mu_edca = !!mu_edca;
			अगर (mu_edca)
				params[ac].mu_edca_param_rec = mu_edca->ac_vi;
			अवरोध;
		हाल 3: /* AC_VO */
			ac = IEEE80211_AC_VO;
			अगर (acm)
				sdata->wmm_acm |= BIT(6) | BIT(7); /* VO/NC */
			अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO)
				uapsd = true;
			params[ac].mu_edca = !!mu_edca;
			अगर (mu_edca)
				params[ac].mu_edca_param_rec = mu_edca->ac_vo;
			अवरोध;
		हाल 0: /* AC_BE */
		शेष:
			ac = IEEE80211_AC_BE;
			अगर (acm)
				sdata->wmm_acm |= BIT(0) | BIT(3); /* BE/EE */
			अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE)
				uapsd = true;
			params[ac].mu_edca = !!mu_edca;
			अगर (mu_edca)
				params[ac].mu_edca_param_rec = mu_edca->ac_be;
			अवरोध;
		पूर्ण

		params[ac].aअगरs = pos[0] & 0x0f;

		अगर (params[ac].aअगरs < 2) अणु
			sdata_info(sdata,
				   "AP has invalid WMM params (AIFSN=%d for ACI %d), will use 2\n",
				   params[ac].aअगरs, aci);
			params[ac].aअगरs = 2;
		पूर्ण
		params[ac].cw_max = ecw2cw((pos[1] & 0xf0) >> 4);
		params[ac].cw_min = ecw2cw(pos[1] & 0x0f);
		params[ac].txop = get_unaligned_le16(pos + 2);
		params[ac].acm = acm;
		params[ac].uapsd = uapsd;

		अगर (params[ac].cw_min == 0 ||
		    params[ac].cw_min > params[ac].cw_max) अणु
			sdata_info(sdata,
				   "AP has invalid WMM params (CWmin/max=%d/%d for ACI %d), using defaults\n",
				   params[ac].cw_min, params[ac].cw_max, aci);
			वापस false;
		पूर्ण
		ieee80211_regulatory_limit_wmm_params(sdata, &params[ac], ac);
	पूर्ण

	/* WMM specअगरication requires all 4 ACIs. */
	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		अगर (params[ac].cw_min == 0) अणु
			sdata_info(sdata,
				   "AP has invalid WMM params (missing AC %d), using defaults\n",
				   ac);
			वापस false;
		पूर्ण
	पूर्ण

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		mlme_dbg(sdata,
			 "WMM AC=%d acm=%d aifs=%d cWmin=%d cWmax=%d txop=%d uapsd=%d, downgraded=%d\n",
			 ac, params[ac].acm,
			 params[ac].aअगरs, params[ac].cw_min, params[ac].cw_max,
			 params[ac].txop, params[ac].uapsd,
			 अगरmgd->tx_tspec[ac].करोwngraded);
		sdata->tx_conf[ac] = params[ac];
		अगर (!अगरmgd->tx_tspec[ac].करोwngraded &&
		    drv_conf_tx(local, sdata, ac, &params[ac]))
			sdata_err(sdata,
				  "failed to set TX queue parameters for AC %d\n",
				  ac);
	पूर्ण

	/* enable WMM or activate new settings */
	sdata->vअगर.bss_conf.qos = true;
	वापस true;
पूर्ण

अटल व्योम __ieee80211_stop_poll(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	lockdep_निश्चित_held(&sdata->local->mtx);

	sdata->u.mgd.flags &= ~IEEE80211_STA_CONNECTION_POLL;
	ieee80211_run_deferred_scan(sdata->local);
पूर्ण

अटल व्योम ieee80211_stop_poll(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	mutex_lock(&sdata->local->mtx);
	__ieee80211_stop_poll(sdata);
	mutex_unlock(&sdata->local->mtx);
पूर्ण

अटल u32 ieee80211_handle_bss_capability(काष्ठा ieee80211_sub_अगर_data *sdata,
					   u16 capab, bool erp_valid, u8 erp)
अणु
	काष्ठा ieee80211_bss_conf *bss_conf = &sdata->vअगर.bss_conf;
	काष्ठा ieee80211_supported_band *sband;
	u32 changed = 0;
	bool use_protection;
	bool use_लघु_preamble;
	bool use_लघु_slot;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस changed;

	अगर (erp_valid) अणु
		use_protection = (erp & WLAN_ERP_USE_PROTECTION) != 0;
		use_लघु_preamble = (erp & WLAN_ERP_BARKER_PREAMBLE) == 0;
	पूर्ण अन्यथा अणु
		use_protection = false;
		use_लघु_preamble = !!(capab & WLAN_CAPABILITY_SHORT_PREAMBLE);
	पूर्ण

	use_लघु_slot = !!(capab & WLAN_CAPABILITY_SHORT_SLOT_TIME);
	अगर (sband->band == NL80211_BAND_5GHZ ||
	    sband->band == NL80211_BAND_6GHZ)
		use_लघु_slot = true;

	अगर (use_protection != bss_conf->use_cts_prot) अणु
		bss_conf->use_cts_prot = use_protection;
		changed |= BSS_CHANGED_ERP_CTS_PROT;
	पूर्ण

	अगर (use_लघु_preamble != bss_conf->use_लघु_preamble) अणु
		bss_conf->use_लघु_preamble = use_लघु_preamble;
		changed |= BSS_CHANGED_ERP_PREAMBLE;
	पूर्ण

	अगर (use_लघु_slot != bss_conf->use_लघु_slot) अणु
		bss_conf->use_लघु_slot = use_लघु_slot;
		changed |= BSS_CHANGED_ERP_SLOT;
	पूर्ण

	वापस changed;
पूर्ण

अटल व्योम ieee80211_set_associated(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा cfg80211_bss *cbss,
				     u32 bss_info_changed)
अणु
	काष्ठा ieee80211_bss *bss = (व्योम *)cbss->priv;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_bss_conf *bss_conf = &sdata->vअगर.bss_conf;

	bss_info_changed |= BSS_CHANGED_ASSOC;
	bss_info_changed |= ieee80211_handle_bss_capability(sdata,
		bss_conf->assoc_capability, bss->has_erp_value, bss->erp_value);

	sdata->u.mgd.beacon_समयout = usecs_to_jअगरfies(ieee80211_tu_to_usec(
		beacon_loss_count * bss_conf->beacon_पूर्णांक));

	sdata->u.mgd.associated = cbss;
	स_नकल(sdata->u.mgd.bssid, cbss->bssid, ETH_ALEN);

	ieee80211_check_rate_mask(sdata);

	sdata->u.mgd.flags |= IEEE80211_STA_RESET_SIGNAL_AVE;

	अगर (sdata->vअगर.p2p ||
	    sdata->vअगर.driver_flags & IEEE80211_VIF_GET_NOA_UPDATE) अणु
		स्थिर काष्ठा cfg80211_bss_ies *ies;

		rcu_पढ़ो_lock();
		ies = rcu_dereference(cbss->ies);
		अगर (ies) अणु
			पूर्णांक ret;

			ret = cfg80211_get_p2p_attr(
					ies->data, ies->len,
					IEEE80211_P2P_ATTR_ABSENCE_NOTICE,
					(u8 *) &bss_conf->p2p_noa_attr,
					माप(bss_conf->p2p_noa_attr));
			अगर (ret >= 2) अणु
				sdata->u.mgd.p2p_noa_index =
					bss_conf->p2p_noa_attr.index;
				bss_info_changed |= BSS_CHANGED_P2P_PS;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	/* just to be sure */
	ieee80211_stop_poll(sdata);

	ieee80211_led_assoc(local, 1);

	अगर (sdata->u.mgd.have_beacon) अणु
		/*
		 * If the AP is buggy we may get here with no DTIM period
		 * known, so assume it's 1 which is the only safe assumption
		 * in that हाल, although अगर the TIM IE is broken घातersave
		 * probably just won't work at all.
		 */
		bss_conf->dtim_period = sdata->u.mgd.dtim_period ?: 1;
		bss_conf->beacon_rate = bss->beacon_rate;
		bss_info_changed |= BSS_CHANGED_BEACON_INFO;
	पूर्ण अन्यथा अणु
		bss_conf->beacon_rate = शून्य;
		bss_conf->dtim_period = 0;
	पूर्ण

	bss_conf->assoc = 1;

	/* Tell the driver to monitor connection quality (अगर supported) */
	अगर (sdata->vअगर.driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI &&
	    bss_conf->cqm_rssi_thold)
		bss_info_changed |= BSS_CHANGED_CQM;

	/* Enable ARP filtering */
	अगर (bss_conf->arp_addr_cnt)
		bss_info_changed |= BSS_CHANGED_ARP_FILTER;

	ieee80211_bss_info_change_notअगरy(sdata, bss_info_changed);

	mutex_lock(&local->अगरlist_mtx);
	ieee80211_recalc_ps(local);
	mutex_unlock(&local->अगरlist_mtx);

	ieee80211_recalc_smps(sdata);
	ieee80211_recalc_ps_vअगर(sdata);

	netअगर_carrier_on(sdata->dev);
पूर्ण

अटल व्योम ieee80211_set_disassoc(काष्ठा ieee80211_sub_अगर_data *sdata,
				   u16 stype, u16 reason, bool tx,
				   u8 *frame_buf)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_local *local = sdata->local;
	u32 changed = 0;

	sdata_निश्चित_lock(sdata);

	अगर (WARN_ON_ONCE(tx && !frame_buf))
		वापस;

	अगर (WARN_ON(!अगरmgd->associated))
		वापस;

	ieee80211_stop_poll(sdata);

	अगरmgd->associated = शून्य;
	netअगर_carrier_off(sdata->dev);

	/*
	 * अगर we want to get out of ps beक्रमe disassoc (why?) we have
	 * to करो it beक्रमe sending disassoc, as otherwise the null-packet
	 * won't be valid.
	 */
	अगर (local->hw.conf.flags & IEEE80211_CONF_PS) अणु
		local->hw.conf.flags &= ~IEEE80211_CONF_PS;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);
	पूर्ण
	local->ps_sdata = शून्य;

	/* disable per-vअगर ps */
	ieee80211_recalc_ps_vअगर(sdata);

	/* make sure ongoing transmission finishes */
	synchronize_net();

	/*
	 * drop any frame beक्रमe deauth/disassoc, this can be data or
	 * management frame. Since we are disconnecting, we should not
	 * insist sending these frames which can take समय and delay
	 * the disconnection and possible the roaming.
	 */
	अगर (tx)
		ieee80211_flush_queues(local, sdata, true);

	/* deauthenticate/disassociate now */
	अगर (tx || frame_buf) अणु
		/*
		 * In multi channel scenarios guarantee that the भव
		 * पूर्णांकerface is granted immediate airसमय to transmit the
		 * deauthentication frame by calling mgd_prepare_tx, अगर the
		 * driver requested so.
		 */
		अगर (ieee80211_hw_check(&local->hw, DEAUTH_NEED_MGD_TX_PREP) &&
		    !अगरmgd->have_beacon)
			drv_mgd_prepare_tx(sdata->local, sdata, 0);

		ieee80211_send_deauth_disassoc(sdata, अगरmgd->bssid,
					       अगरmgd->bssid, stype, reason,
					       tx, frame_buf);
	पूर्ण

	/* flush out frame - make sure the deauth was actually sent */
	अगर (tx)
		ieee80211_flush_queues(local, sdata, false);

	/* clear bssid only after building the needed mgmt frames */
	eth_zero_addr(अगरmgd->bssid);

	sdata->vअगर.bss_conf.ssid_len = 0;

	/* हटाओ AP and TDLS peers */
	sta_info_flush(sdata);

	/* finally reset all BSS / config parameters */
	changed |= ieee80211_reset_erp_info(sdata);

	ieee80211_led_assoc(local, 0);
	changed |= BSS_CHANGED_ASSOC;
	sdata->vअगर.bss_conf.assoc = false;

	अगरmgd->p2p_noa_index = -1;
	स_रखो(&sdata->vअगर.bss_conf.p2p_noa_attr, 0,
	       माप(sdata->vअगर.bss_conf.p2p_noa_attr));

	/* on the next assoc, re-program HT/VHT parameters */
	स_रखो(&अगरmgd->ht_capa, 0, माप(अगरmgd->ht_capa));
	स_रखो(&अगरmgd->ht_capa_mask, 0, माप(अगरmgd->ht_capa_mask));
	स_रखो(&अगरmgd->vht_capa, 0, माप(अगरmgd->vht_capa));
	स_रखो(&अगरmgd->vht_capa_mask, 0, माप(अगरmgd->vht_capa_mask));

	/* reset MU-MIMO ownership and group data */
	स_रखो(sdata->vअगर.bss_conf.mu_group.membership, 0,
	       माप(sdata->vअगर.bss_conf.mu_group.membership));
	स_रखो(sdata->vअगर.bss_conf.mu_group.position, 0,
	       माप(sdata->vअगर.bss_conf.mu_group.position));
	changed |= BSS_CHANGED_MU_GROUPS;
	sdata->vअगर.mu_mimo_owner = false;

	sdata->ap_घातer_level = IEEE80211_UNSET_POWER_LEVEL;

	del_समयr_sync(&local->dynamic_ps_समयr);
	cancel_work_sync(&local->dynamic_ps_enable_work);

	/* Disable ARP filtering */
	अगर (sdata->vअगर.bss_conf.arp_addr_cnt)
		changed |= BSS_CHANGED_ARP_FILTER;

	sdata->vअगर.bss_conf.qos = false;
	changed |= BSS_CHANGED_QOS;

	/* The BSSID (not really पूर्णांकeresting) and HT changed */
	changed |= BSS_CHANGED_BSSID | BSS_CHANGED_HT;
	ieee80211_bss_info_change_notअगरy(sdata, changed);

	/* disassociated - set to शेषs now */
	ieee80211_set_wmm_शेष(sdata, false, false);

	del_समयr_sync(&sdata->u.mgd.conn_mon_समयr);
	del_समयr_sync(&sdata->u.mgd.bcn_mon_समयr);
	del_समयr_sync(&sdata->u.mgd.समयr);
	del_समयr_sync(&sdata->u.mgd.chचयन_समयr);

	sdata->vअगर.bss_conf.dtim_period = 0;
	sdata->vअगर.bss_conf.beacon_rate = शून्य;

	अगरmgd->have_beacon = false;

	अगरmgd->flags = 0;
	mutex_lock(&local->mtx);
	ieee80211_vअगर_release_channel(sdata);

	sdata->vअगर.csa_active = false;
	अगरmgd->csa_रुकोing_bcn = false;
	अगरmgd->csa_ignored_same_chan = false;
	अगर (sdata->csa_block_tx) अणु
		ieee80211_wake_vअगर_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);
		sdata->csa_block_tx = false;
	पूर्ण
	mutex_unlock(&local->mtx);

	/* existing TX TSPEC sessions no दीर्घer exist */
	स_रखो(अगरmgd->tx_tspec, 0, माप(अगरmgd->tx_tspec));
	cancel_delayed_work_sync(&अगरmgd->tx_tspec_wk);

	sdata->encrypt_headroom = IEEE80211_ENCRYPT_HEADROOM;
पूर्ण

अटल व्योम ieee80211_reset_ap_probe(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_local *local = sdata->local;

	mutex_lock(&local->mtx);
	अगर (!(अगरmgd->flags & IEEE80211_STA_CONNECTION_POLL))
		जाओ out;

	__ieee80211_stop_poll(sdata);

	mutex_lock(&local->अगरlist_mtx);
	ieee80211_recalc_ps(local);
	mutex_unlock(&local->अगरlist_mtx);

	अगर (ieee80211_hw_check(&sdata->local->hw, CONNECTION_MONITOR))
		जाओ out;

	/*
	 * We've received a probe response, but are not sure whether
	 * we have or will be receiving any beacons or data, so let's
	 * schedule the समयrs again, just in हाल.
	 */
	ieee80211_sta_reset_beacon_monitor(sdata);

	mod_समयr(&अगरmgd->conn_mon_समयr,
		  round_jअगरfies_up(jअगरfies +
				   IEEE80211_CONNECTION_IDLE_TIME));
out:
	mutex_unlock(&local->mtx);
पूर्ण

अटल व्योम ieee80211_sta_tx_wmm_ac_notअगरy(काष्ठा ieee80211_sub_अगर_data *sdata,
					   काष्ठा ieee80211_hdr *hdr,
					   u16 tx_समय)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	u16 tid = ieee80211_get_tid(hdr);
	पूर्णांक ac = ieee80211_ac_from_tid(tid);
	काष्ठा ieee80211_sta_tx_tspec *tx_tspec = &अगरmgd->tx_tspec[ac];
	अचिन्हित दीर्घ now = jअगरfies;

	अगर (likely(!tx_tspec->admitted_समय))
		वापस;

	अगर (समय_after(now, tx_tspec->समय_slice_start + HZ)) अणु
		tx_tspec->consumed_tx_समय = 0;
		tx_tspec->समय_slice_start = now;

		अगर (tx_tspec->करोwngraded) अणु
			tx_tspec->action = TX_TSPEC_ACTION_STOP_DOWNGRADE;
			schedule_delayed_work(&अगरmgd->tx_tspec_wk, 0);
		पूर्ण
	पूर्ण

	अगर (tx_tspec->करोwngraded)
		वापस;

	tx_tspec->consumed_tx_समय += tx_समय;

	अगर (tx_tspec->consumed_tx_समय >= tx_tspec->admitted_समय) अणु
		tx_tspec->करोwngraded = true;
		tx_tspec->action = TX_TSPEC_ACTION_DOWNGRADE;
		schedule_delayed_work(&अगरmgd->tx_tspec_wk, 0);
	पूर्ण
पूर्ण

व्योम ieee80211_sta_tx_notअगरy(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा ieee80211_hdr *hdr, bool ack, u16 tx_समय)
अणु
	ieee80211_sta_tx_wmm_ac_notअगरy(sdata, hdr, tx_समय);

	अगर (!ieee80211_is_any_nullfunc(hdr->frame_control) ||
	    !sdata->u.mgd.probe_send_count)
		वापस;

	अगर (ack)
		sdata->u.mgd.probe_send_count = 0;
	अन्यथा
		sdata->u.mgd.nullfunc_failed = true;
	ieee80211_queue_work(&sdata->local->hw, &sdata->work);
पूर्ण

अटल व्योम ieee80211_mlme_send_probe_req(काष्ठा ieee80211_sub_अगर_data *sdata,
					  स्थिर u8 *src, स्थिर u8 *dst,
					  स्थिर u8 *ssid, माप_प्रकार ssid_len,
					  काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा sk_buff *skb;

	skb = ieee80211_build_probe_req(sdata, src, dst, (u32)-1, channel,
					ssid, ssid_len, शून्य, 0,
					IEEE80211_PROBE_FLAG_सूचीECTED);
	अगर (skb)
		ieee80211_tx_skb(sdata, skb);
पूर्ण

अटल व्योम ieee80211_mgd_probe_ap_send(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	स्थिर u8 *ssid;
	u8 *dst = अगरmgd->associated->bssid;
	u8 unicast_limit = max(1, max_probe_tries - 3);
	काष्ठा sta_info *sta;

	/*
	 * Try sending broadcast probe requests क्रम the last three
	 * probe requests after the first ones failed since some
	 * buggy APs only support broadcast probe requests.
	 */
	अगर (अगरmgd->probe_send_count >= unicast_limit)
		dst = शून्य;

	/*
	 * When the hardware reports an accurate Tx ACK status, it's
	 * better to send a nullfunc frame instead of a probe request,
	 * as it will kick us off the AP quickly अगर we aren't associated
	 * anymore. The समयout will be reset अगर the frame is ACKed by
	 * the AP.
	 */
	अगरmgd->probe_send_count++;

	अगर (dst) अणु
		mutex_lock(&sdata->local->sta_mtx);
		sta = sta_info_get(sdata, dst);
		अगर (!WARN_ON(!sta))
			ieee80211_check_fast_rx(sta);
		mutex_unlock(&sdata->local->sta_mtx);
	पूर्ण

	अगर (ieee80211_hw_check(&sdata->local->hw, REPORTS_TX_ACK_STATUS)) अणु
		अगरmgd->nullfunc_failed = false;
		अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_HE))
			अगरmgd->probe_send_count--;
		अन्यथा
			ieee80211_send_nullfunc(sdata->local, sdata, false);
	पूर्ण अन्यथा अणु
		पूर्णांक ssid_len;

		rcu_पढ़ो_lock();
		ssid = ieee80211_bss_get_ie(अगरmgd->associated, WLAN_EID_SSID);
		अगर (WARN_ON_ONCE(ssid == शून्य))
			ssid_len = 0;
		अन्यथा
			ssid_len = ssid[1];

		ieee80211_mlme_send_probe_req(sdata, sdata->vअगर.addr, dst,
					      ssid + 2, ssid_len,
					      अगरmgd->associated->channel);
		rcu_पढ़ो_unlock();
	पूर्ण

	अगरmgd->probe_समयout = jअगरfies + msecs_to_jअगरfies(probe_रुको_ms);
	run_again(sdata, अगरmgd->probe_समयout);
पूर्ण

अटल व्योम ieee80211_mgd_probe_ap(काष्ठा ieee80211_sub_अगर_data *sdata,
				   bool beacon)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	bool alपढ़ोy = false;

	अगर (!ieee80211_sdata_running(sdata))
		वापस;

	sdata_lock(sdata);

	अगर (!अगरmgd->associated)
		जाओ out;

	mutex_lock(&sdata->local->mtx);

	अगर (sdata->local->पंचांगp_channel || sdata->local->scanning) अणु
		mutex_unlock(&sdata->local->mtx);
		जाओ out;
	पूर्ण

	अगर (beacon) अणु
		mlme_dbg_ratelimited(sdata,
				     "detected beacon loss from AP (missed %d beacons) - probing\n",
				     beacon_loss_count);

		ieee80211_cqm_beacon_loss_notअगरy(&sdata->vअगर, GFP_KERNEL);
	पूर्ण

	/*
	 * The driver/our work has alपढ़ोy reported this event or the
	 * connection monitoring has kicked in and we have alपढ़ोy sent
	 * a probe request. Or maybe the AP died and the driver keeps
	 * reporting until we disassociate...
	 *
	 * In either हाल we have to ignore the current call to this
	 * function (except क्रम setting the correct probe reason bit)
	 * because otherwise we would reset the समयr every समय and
	 * never check whether we received a probe response!
	 */
	अगर (अगरmgd->flags & IEEE80211_STA_CONNECTION_POLL)
		alपढ़ोy = true;

	अगरmgd->flags |= IEEE80211_STA_CONNECTION_POLL;

	mutex_unlock(&sdata->local->mtx);

	अगर (alपढ़ोy)
		जाओ out;

	mutex_lock(&sdata->local->अगरlist_mtx);
	ieee80211_recalc_ps(sdata->local);
	mutex_unlock(&sdata->local->अगरlist_mtx);

	अगरmgd->probe_send_count = 0;
	ieee80211_mgd_probe_ap_send(sdata);
 out:
	sdata_unlock(sdata);
पूर्ण

काष्ठा sk_buff *ieee80211_ap_probereq_get(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा cfg80211_bss *cbss;
	काष्ठा sk_buff *skb;
	स्थिर u8 *ssid;
	पूर्णांक ssid_len;

	अगर (WARN_ON(sdata->vअगर.type != NL80211_IFTYPE_STATION))
		वापस शून्य;

	sdata_निश्चित_lock(sdata);

	अगर (अगरmgd->associated)
		cbss = अगरmgd->associated;
	अन्यथा अगर (अगरmgd->auth_data)
		cbss = अगरmgd->auth_data->bss;
	अन्यथा अगर (अगरmgd->assoc_data)
		cbss = अगरmgd->assoc_data->bss;
	अन्यथा
		वापस शून्य;

	rcu_पढ़ो_lock();
	ssid = ieee80211_bss_get_ie(cbss, WLAN_EID_SSID);
	अगर (WARN_ONCE(!ssid || ssid[1] > IEEE80211_MAX_SSID_LEN,
		      "invalid SSID element (len=%d)", ssid ? ssid[1] : -1))
		ssid_len = 0;
	अन्यथा
		ssid_len = ssid[1];

	skb = ieee80211_build_probe_req(sdata, sdata->vअगर.addr, cbss->bssid,
					(u32) -1, cbss->channel,
					ssid + 2, ssid_len,
					शून्य, 0, IEEE80211_PROBE_FLAG_सूचीECTED);
	rcu_पढ़ो_unlock();

	वापस skb;
पूर्ण
EXPORT_SYMBOL(ieee80211_ap_probereq_get);

अटल व्योम ieee80211_report_disconnect(काष्ठा ieee80211_sub_अगर_data *sdata,
					स्थिर u8 *buf, माप_प्रकार len, bool tx,
					u16 reason, bool reconnect)
अणु
	काष्ठा ieee80211_event event = अणु
		.type = MLME_EVENT,
		.u.mlme.data = tx ? DEAUTH_TX_EVENT : DEAUTH_RX_EVENT,
		.u.mlme.reason = reason,
	पूर्ण;

	अगर (tx)
		cfg80211_tx_mlme_mgmt(sdata->dev, buf, len, reconnect);
	अन्यथा
		cfg80211_rx_mlme_mgmt(sdata->dev, buf, len);

	drv_event_callback(sdata->local, sdata, &event);
पूर्ण

अटल व्योम __ieee80211_disconnect(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];
	bool tx;

	sdata_lock(sdata);
	अगर (!अगरmgd->associated) अणु
		sdata_unlock(sdata);
		वापस;
	पूर्ण

	tx = !sdata->csa_block_tx;

	अगर (!अगरmgd->driver_disconnect) अणु
		/*
		 * AP is probably out of range (or not reachable क्रम another
		 * reason) so हटाओ the bss काष्ठा क्रम that AP.
		 */
		cfg80211_unlink_bss(local->hw.wiphy, अगरmgd->associated);
	पूर्ण

	ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH,
			       अगरmgd->driver_disconnect ?
					WLAN_REASON_DEAUTH_LEAVING :
					WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY,
			       tx, frame_buf);
	mutex_lock(&local->mtx);
	sdata->vअगर.csa_active = false;
	अगरmgd->csa_रुकोing_bcn = false;
	अगर (sdata->csa_block_tx) अणु
		ieee80211_wake_vअगर_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);
		sdata->csa_block_tx = false;
	पूर्ण
	mutex_unlock(&local->mtx);

	ieee80211_report_disconnect(sdata, frame_buf, माप(frame_buf), tx,
				    WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY,
				    अगरmgd->reconnect);
	अगरmgd->reconnect = false;

	sdata_unlock(sdata);
पूर्ण

अटल व्योम ieee80211_beacon_connection_loss_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		container_of(work, काष्ठा ieee80211_sub_अगर_data,
			     u.mgd.beacon_connection_loss_work);
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	अगर (अगरmgd->associated)
		अगरmgd->beacon_loss_count++;

	अगर (अगरmgd->connection_loss) अणु
		sdata_info(sdata, "Connection to AP %pM lost\n",
			   अगरmgd->bssid);
		__ieee80211_disconnect(sdata);
		अगरmgd->connection_loss = false;
	पूर्ण अन्यथा अगर (अगरmgd->driver_disconnect) अणु
		sdata_info(sdata,
			   "Driver requested disconnection from AP %pM\n",
			   अगरmgd->bssid);
		__ieee80211_disconnect(sdata);
		अगरmgd->driver_disconnect = false;
	पूर्ण अन्यथा अणु
		ieee80211_mgd_probe_ap(sdata, true);
	पूर्ण
पूर्ण

अटल व्योम ieee80211_csa_connection_drop_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		container_of(work, काष्ठा ieee80211_sub_अगर_data,
			     u.mgd.csa_connection_drop_work);

	__ieee80211_disconnect(sdata);
पूर्ण

व्योम ieee80211_beacon_loss(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_hw *hw = &sdata->local->hw;

	trace_api_beacon_loss(sdata);

	sdata->u.mgd.connection_loss = false;
	ieee80211_queue_work(hw, &sdata->u.mgd.beacon_connection_loss_work);
पूर्ण
EXPORT_SYMBOL(ieee80211_beacon_loss);

व्योम ieee80211_connection_loss(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_hw *hw = &sdata->local->hw;

	trace_api_connection_loss(sdata);

	sdata->u.mgd.connection_loss = true;
	ieee80211_queue_work(hw, &sdata->u.mgd.beacon_connection_loss_work);
पूर्ण
EXPORT_SYMBOL(ieee80211_connection_loss);

व्योम ieee80211_disconnect(काष्ठा ieee80211_vअगर *vअगर, bool reconnect)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_hw *hw = &sdata->local->hw;

	trace_api_disconnect(sdata, reconnect);

	अगर (WARN_ON(sdata->vअगर.type != NL80211_IFTYPE_STATION))
		वापस;

	sdata->u.mgd.driver_disconnect = true;
	sdata->u.mgd.reconnect = reconnect;
	ieee80211_queue_work(hw, &sdata->u.mgd.beacon_connection_loss_work);
पूर्ण
EXPORT_SYMBOL(ieee80211_disconnect);

अटल व्योम ieee80211_destroy_auth_data(काष्ठा ieee80211_sub_अगर_data *sdata,
					bool assoc)
अणु
	काष्ठा ieee80211_mgd_auth_data *auth_data = sdata->u.mgd.auth_data;

	sdata_निश्चित_lock(sdata);

	अगर (!assoc) अणु
		/*
		 * we are not authenticated yet, the only समयr that could be
		 * running is the समयout क्रम the authentication response which
		 * which is not relevant anymore.
		 */
		del_समयr_sync(&sdata->u.mgd.समयr);
		sta_info_destroy_addr(sdata, auth_data->bss->bssid);

		eth_zero_addr(sdata->u.mgd.bssid);
		ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_BSSID);
		sdata->u.mgd.flags = 0;
		mutex_lock(&sdata->local->mtx);
		ieee80211_vअगर_release_channel(sdata);
		mutex_unlock(&sdata->local->mtx);
	पूर्ण

	cfg80211_put_bss(sdata->local->hw.wiphy, auth_data->bss);
	kमुक्त(auth_data);
	sdata->u.mgd.auth_data = शून्य;
पूर्ण

अटल व्योम ieee80211_destroy_assoc_data(काष्ठा ieee80211_sub_अगर_data *sdata,
					 bool assoc, bool abanकरोn)
अणु
	काष्ठा ieee80211_mgd_assoc_data *assoc_data = sdata->u.mgd.assoc_data;

	sdata_निश्चित_lock(sdata);

	अगर (!assoc) अणु
		/*
		 * we are not associated yet, the only समयr that could be
		 * running is the समयout क्रम the association response which
		 * which is not relevant anymore.
		 */
		del_समयr_sync(&sdata->u.mgd.समयr);
		sta_info_destroy_addr(sdata, assoc_data->bss->bssid);

		eth_zero_addr(sdata->u.mgd.bssid);
		ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_BSSID);
		sdata->u.mgd.flags = 0;
		sdata->vअगर.mu_mimo_owner = false;

		mutex_lock(&sdata->local->mtx);
		ieee80211_vअगर_release_channel(sdata);
		mutex_unlock(&sdata->local->mtx);

		अगर (abanकरोn)
			cfg80211_abanकरोn_assoc(sdata->dev, assoc_data->bss);
	पूर्ण

	kमुक्त(assoc_data);
	sdata->u.mgd.assoc_data = शून्य;
पूर्ण

अटल व्योम ieee80211_auth_challenge(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_mgd_auth_data *auth_data = sdata->u.mgd.auth_data;
	u8 *pos;
	काष्ठा ieee802_11_elems elems;
	u32 tx_flags = 0;

	pos = mgmt->u.auth.variable;
	ieee802_11_parse_elems(pos, len - (pos - (u8 *)mgmt), false, &elems,
			       mgmt->bssid, auth_data->bss->bssid);
	अगर (!elems.challenge)
		वापस;
	auth_data->expected_transaction = 4;
	drv_mgd_prepare_tx(sdata->local, sdata, 0);
	अगर (ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS))
		tx_flags = IEEE80211_TX_CTL_REQ_TX_STATUS |
			   IEEE80211_TX_INTFL_MLME_CONN_TX;
	ieee80211_send_auth(sdata, 3, auth_data->algorithm, 0,
			    elems.challenge - 2, elems.challenge_len + 2,
			    auth_data->bss->bssid, auth_data->bss->bssid,
			    auth_data->key, auth_data->key_len,
			    auth_data->key_idx, tx_flags);
पूर्ण

अटल bool ieee80211_mark_sta_auth(काष्ठा ieee80211_sub_अगर_data *sdata,
				    स्थिर u8 *bssid)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा sta_info *sta;
	bool result = true;

	sdata_info(sdata, "authenticated\n");
	अगरmgd->auth_data->करोne = true;
	अगरmgd->auth_data->समयout = jअगरfies + IEEE80211_AUTH_WAIT_ASSOC;
	अगरmgd->auth_data->समयout_started = true;
	run_again(sdata, अगरmgd->auth_data->समयout);

	/* move station state to auth */
	mutex_lock(&sdata->local->sta_mtx);
	sta = sta_info_get(sdata, bssid);
	अगर (!sta) अणु
		WARN_ONCE(1, "%s: STA %pM not found", sdata->name, bssid);
		result = false;
		जाओ out;
	पूर्ण
	अगर (sta_info_move_state(sta, IEEE80211_STA_AUTH)) अणु
		sdata_info(sdata, "failed moving %pM to auth\n", bssid);
		result = false;
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&sdata->local->sta_mtx);
	वापस result;
पूर्ण

अटल व्योम ieee80211_rx_mgmt_auth(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	u8 bssid[ETH_ALEN];
	u16 auth_alg, auth_transaction, status_code;
	काष्ठा ieee80211_event event = अणु
		.type = MLME_EVENT,
		.u.mlme.data = AUTH_EVENT,
	पूर्ण;

	sdata_निश्चित_lock(sdata);

	अगर (len < 24 + 6)
		वापस;

	अगर (!अगरmgd->auth_data || अगरmgd->auth_data->करोne)
		वापस;

	स_नकल(bssid, अगरmgd->auth_data->bss->bssid, ETH_ALEN);

	अगर (!ether_addr_equal(bssid, mgmt->bssid))
		वापस;

	auth_alg = le16_to_cpu(mgmt->u.auth.auth_alg);
	auth_transaction = le16_to_cpu(mgmt->u.auth.auth_transaction);
	status_code = le16_to_cpu(mgmt->u.auth.status_code);

	अगर (auth_alg != अगरmgd->auth_data->algorithm ||
	    (auth_alg != WLAN_AUTH_SAE &&
	     auth_transaction != अगरmgd->auth_data->expected_transaction) ||
	    (auth_alg == WLAN_AUTH_SAE &&
	     (auth_transaction < अगरmgd->auth_data->expected_transaction ||
	      auth_transaction > 2))) अणु
		sdata_info(sdata, "%pM unexpected authentication state: alg %d (expected %d) transact %d (expected %d)\n",
			   mgmt->sa, auth_alg, अगरmgd->auth_data->algorithm,
			   auth_transaction,
			   अगरmgd->auth_data->expected_transaction);
		वापस;
	पूर्ण

	अगर (status_code != WLAN_STATUS_SUCCESS) अणु
		cfg80211_rx_mlme_mgmt(sdata->dev, (u8 *)mgmt, len);

		अगर (auth_alg == WLAN_AUTH_SAE &&
		    (status_code == WLAN_STATUS_ANTI_CLOG_REQUIRED ||
		     (auth_transaction == 1 &&
		      (status_code == WLAN_STATUS_SAE_HASH_TO_ELEMENT ||
		       status_code == WLAN_STATUS_SAE_PK))))
			वापस;

		sdata_info(sdata, "%pM denied authentication (status %d)\n",
			   mgmt->sa, status_code);
		ieee80211_destroy_auth_data(sdata, false);
		event.u.mlme.status = MLME_DENIED;
		event.u.mlme.reason = status_code;
		drv_event_callback(sdata->local, sdata, &event);
		वापस;
	पूर्ण

	चयन (अगरmgd->auth_data->algorithm) अणु
	हाल WLAN_AUTH_OPEN:
	हाल WLAN_AUTH_LEAP:
	हाल WLAN_AUTH_FT:
	हाल WLAN_AUTH_SAE:
	हाल WLAN_AUTH_FILS_SK:
	हाल WLAN_AUTH_FILS_SK_PFS:
	हाल WLAN_AUTH_FILS_PK:
		अवरोध;
	हाल WLAN_AUTH_SHARED_KEY:
		अगर (अगरmgd->auth_data->expected_transaction != 4) अणु
			ieee80211_auth_challenge(sdata, mgmt, len);
			/* need another frame */
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		WARN_ONCE(1, "invalid auth alg %d",
			  अगरmgd->auth_data->algorithm);
		वापस;
	पूर्ण

	event.u.mlme.status = MLME_SUCCESS;
	drv_event_callback(sdata->local, sdata, &event);
	अगर (अगरmgd->auth_data->algorithm != WLAN_AUTH_SAE ||
	    (auth_transaction == 2 &&
	     अगरmgd->auth_data->expected_transaction == 2)) अणु
		अगर (!ieee80211_mark_sta_auth(sdata, bssid))
			वापस; /* ignore frame -- रुको क्रम समयout */
	पूर्ण अन्यथा अगर (अगरmgd->auth_data->algorithm == WLAN_AUTH_SAE &&
		   auth_transaction == 2) अणु
		sdata_info(sdata, "SAE peer confirmed\n");
		अगरmgd->auth_data->peer_confirmed = true;
	पूर्ण

	cfg80211_rx_mlme_mgmt(sdata->dev, (u8 *)mgmt, len);
पूर्ण

#घोषणा हाल_WLAN(type) \
	हाल WLAN_REASON_##type: वापस #type

स्थिर अक्षर *ieee80211_get_reason_code_string(u16 reason_code)
अणु
	चयन (reason_code) अणु
	हाल_WLAN(UNSPECIFIED);
	हाल_WLAN(PREV_AUTH_NOT_VALID);
	हाल_WLAN(DEAUTH_LEAVING);
	हाल_WLAN(DISASSOC_DUE_TO_INACTIVITY);
	हाल_WLAN(DISASSOC_AP_BUSY);
	हाल_WLAN(CLASS2_FRAME_FROM_NONAUTH_STA);
	हाल_WLAN(CLASS3_FRAME_FROM_NONASSOC_STA);
	हाल_WLAN(DISASSOC_STA_HAS_LEFT);
	हाल_WLAN(STA_REQ_ASSOC_WITHOUT_AUTH);
	हाल_WLAN(DISASSOC_BAD_POWER);
	हाल_WLAN(DISASSOC_BAD_SUPP_CHAN);
	हाल_WLAN(INVALID_IE);
	हाल_WLAN(MIC_FAILURE);
	हाल_WLAN(4WAY_HANDSHAKE_TIMEOUT);
	हाल_WLAN(GROUP_KEY_HANDSHAKE_TIMEOUT);
	हाल_WLAN(IE_DIFFERENT);
	हाल_WLAN(INVALID_GROUP_CIPHER);
	हाल_WLAN(INVALID_PAIRWISE_CIPHER);
	हाल_WLAN(INVALID_AKMP);
	हाल_WLAN(UNSUPP_RSN_VERSION);
	हाल_WLAN(INVALID_RSN_IE_CAP);
	हाल_WLAN(IEEE8021X_FAILED);
	हाल_WLAN(CIPHER_SUITE_REJECTED);
	हाल_WLAN(DISASSOC_UNSPECIFIED_QOS);
	हाल_WLAN(DISASSOC_QAP_NO_BANDWIDTH);
	हाल_WLAN(DISASSOC_LOW_ACK);
	हाल_WLAN(DISASSOC_QAP_EXCEED_TXOP);
	हाल_WLAN(QSTA_LEAVE_QBSS);
	हाल_WLAN(QSTA_NOT_USE);
	हाल_WLAN(QSTA_REQUIRE_SETUP);
	हाल_WLAN(QSTA_TIMEOUT);
	हाल_WLAN(QSTA_CIPHER_NOT_SUPP);
	हाल_WLAN(MESH_PEER_CANCELED);
	हाल_WLAN(MESH_MAX_PEERS);
	हाल_WLAN(MESH_CONFIG);
	हाल_WLAN(MESH_CLOSE);
	हाल_WLAN(MESH_MAX_RETRIES);
	हाल_WLAN(MESH_CONFIRM_TIMEOUT);
	हाल_WLAN(MESH_INVALID_GTK);
	हाल_WLAN(MESH_INCONSISTENT_PARAM);
	हाल_WLAN(MESH_INVALID_SECURITY);
	हाल_WLAN(MESH_PATH_ERROR);
	हाल_WLAN(MESH_PATH_NOFORWARD);
	हाल_WLAN(MESH_PATH_DEST_UNREACHABLE);
	हाल_WLAN(MAC_EXISTS_IN_MBSS);
	हाल_WLAN(MESH_CHAN_REGULATORY);
	हाल_WLAN(MESH_CHAN);
	शेष: वापस "<unknown>";
	पूर्ण
पूर्ण

अटल व्योम ieee80211_rx_mgmt_deauth(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	u16 reason_code = le16_to_cpu(mgmt->u.deauth.reason_code);

	sdata_निश्चित_lock(sdata);

	अगर (len < 24 + 2)
		वापस;

	अगर (!ether_addr_equal(mgmt->bssid, mgmt->sa)) अणु
		ieee80211_tdls_handle_disconnect(sdata, mgmt->sa, reason_code);
		वापस;
	पूर्ण

	अगर (अगरmgd->associated &&
	    ether_addr_equal(mgmt->bssid, अगरmgd->associated->bssid)) अणु
		स्थिर u8 *bssid = अगरmgd->associated->bssid;

		sdata_info(sdata, "deauthenticated from %pM (Reason: %u=%s)\n",
			   bssid, reason_code,
			   ieee80211_get_reason_code_string(reason_code));

		ieee80211_set_disassoc(sdata, 0, 0, false, शून्य);

		ieee80211_report_disconnect(sdata, (u8 *)mgmt, len, false,
					    reason_code, false);
		वापस;
	पूर्ण

	अगर (अगरmgd->assoc_data &&
	    ether_addr_equal(mgmt->bssid, अगरmgd->assoc_data->bss->bssid)) अणु
		स्थिर u8 *bssid = अगरmgd->assoc_data->bss->bssid;

		sdata_info(sdata,
			   "deauthenticated from %pM while associating (Reason: %u=%s)\n",
			   bssid, reason_code,
			   ieee80211_get_reason_code_string(reason_code));

		ieee80211_destroy_assoc_data(sdata, false, true);

		cfg80211_rx_mlme_mgmt(sdata->dev, (u8 *)mgmt, len);
		वापस;
	पूर्ण
पूर्ण


अटल व्योम ieee80211_rx_mgmt_disassoc(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	u16 reason_code;

	sdata_निश्चित_lock(sdata);

	अगर (len < 24 + 2)
		वापस;

	अगर (!अगरmgd->associated ||
	    !ether_addr_equal(mgmt->bssid, अगरmgd->associated->bssid))
		वापस;

	reason_code = le16_to_cpu(mgmt->u.disassoc.reason_code);

	अगर (!ether_addr_equal(mgmt->bssid, mgmt->sa)) अणु
		ieee80211_tdls_handle_disconnect(sdata, mgmt->sa, reason_code);
		वापस;
	पूर्ण

	sdata_info(sdata, "disassociated from %pM (Reason: %u=%s)\n",
		   mgmt->sa, reason_code,
		   ieee80211_get_reason_code_string(reason_code));

	ieee80211_set_disassoc(sdata, 0, 0, false, शून्य);

	ieee80211_report_disconnect(sdata, (u8 *)mgmt, len, false, reason_code,
				    false);
पूर्ण

अटल व्योम ieee80211_get_rates(काष्ठा ieee80211_supported_band *sband,
				u8 *supp_rates, अचिन्हित पूर्णांक supp_rates_len,
				u32 *rates, u32 *basic_rates,
				bool *have_higher_than_11mbit,
				पूर्णांक *min_rate, पूर्णांक *min_rate_index,
				पूर्णांक shअगरt)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < supp_rates_len; i++) अणु
		पूर्णांक rate = supp_rates[i] & 0x7f;
		bool is_basic = !!(supp_rates[i] & 0x80);

		अगर ((rate * 5 * (1 << shअगरt)) > 110)
			*have_higher_than_11mbit = true;

		/*
		 * Skip HT, VHT, HE and SAE H2E only BSS membership selectors
		 * since they're not rates.
		 *
		 * Note: Even though the membership selector and the basic
		 *	 rate flag share the same bit, they are not exactly
		 *	 the same.
		 */
		अगर (supp_rates[i] == (0x80 | BSS_MEMBERSHIP_SELECTOR_HT_PHY) ||
		    supp_rates[i] == (0x80 | BSS_MEMBERSHIP_SELECTOR_VHT_PHY) ||
		    supp_rates[i] == (0x80 | BSS_MEMBERSHIP_SELECTOR_HE_PHY) ||
		    supp_rates[i] == (0x80 | BSS_MEMBERSHIP_SELECTOR_SAE_H2E))
			जारी;

		क्रम (j = 0; j < sband->n_bitrates; j++) अणु
			काष्ठा ieee80211_rate *br;
			पूर्णांक brate;

			br = &sband->bitrates[j];

			brate = DIV_ROUND_UP(br->bitrate, (1 << shअगरt) * 5);
			अगर (brate == rate) अणु
				*rates |= BIT(j);
				अगर (is_basic)
					*basic_rates |= BIT(j);
				अगर ((rate * 5) < *min_rate) अणु
					*min_rate = rate * 5;
					*min_rate_index = j;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल bool ieee80211_twt_req_supported(स्थिर काष्ठा sta_info *sta,
					स्थिर काष्ठा ieee802_11_elems *elems)
अणु
	अगर (elems->ext_capab_len < 10)
		वापस false;

	अगर (!(elems->ext_capab[9] & WLAN_EXT_CAPA10_TWT_RESPONDER_SUPPORT))
		वापस false;

	वापस sta->sta.he_cap.he_cap_elem.mac_cap_info[0] &
		IEEE80211_HE_MAC_CAP0_TWT_RES;
पूर्ण

अटल पूर्णांक ieee80211_recalc_twt_req(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा sta_info *sta,
				    काष्ठा ieee802_11_elems *elems)
अणु
	bool twt = ieee80211_twt_req_supported(sta, elems);

	अगर (sdata->vअगर.bss_conf.twt_requester != twt) अणु
		sdata->vअगर.bss_conf.twt_requester = twt;
		वापस BSS_CHANGED_TWT;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool ieee80211_assoc_success(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा cfg80211_bss *cbss,
				    काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
				    काष्ठा ieee802_11_elems *elems)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा sta_info *sta;
	u16 capab_info, aid;
	काष्ठा ieee80211_bss_conf *bss_conf = &sdata->vअगर.bss_conf;
	स्थिर काष्ठा cfg80211_bss_ies *bss_ies = शून्य;
	काष्ठा ieee80211_mgd_assoc_data *assoc_data = अगरmgd->assoc_data;
	bool is_6ghz = cbss->channel->band == NL80211_BAND_6GHZ;
	bool is_s1g = cbss->channel->band == NL80211_BAND_S1GHZ;
	u32 changed = 0;
	u8 *pos;
	पूर्णांक err;
	bool ret;

	/* AssocResp and ReassocResp have identical काष्ठाure */

	pos = mgmt->u.assoc_resp.variable;
	aid = le16_to_cpu(mgmt->u.assoc_resp.aid);
	अगर (is_s1g) अणु
		pos = (u8 *) mgmt->u.s1g_assoc_resp.variable;
		aid = 0; /* TODO */
	पूर्ण
	capab_info = le16_to_cpu(mgmt->u.assoc_resp.capab_info);
	ieee802_11_parse_elems(pos, len - (pos - (u8 *)mgmt), false, elems,
			       mgmt->bssid, assoc_data->bss->bssid);

	अगर (elems->aid_resp)
		aid = le16_to_cpu(elems->aid_resp->aid);

	/*
	 * The 5 MSB of the AID field are reserved
	 * (802.11-2016 9.4.1.8 AID field)
	 */
	aid &= 0x7ff;

	अगरmgd->broken_ap = false;

	अगर (aid == 0 || aid > IEEE80211_MAX_AID) अणु
		sdata_info(sdata, "invalid AID value %d (out of range), turn off PS\n",
			   aid);
		aid = 0;
		अगरmgd->broken_ap = true;
	पूर्ण

	अगर (!is_s1g && !elems->supp_rates) अणु
		sdata_info(sdata, "no SuppRates element in AssocResp\n");
		वापस false;
	पूर्ण

	sdata->vअगर.bss_conf.aid = aid;
	अगरmgd->tdls_chan_चयन_prohibited =
		elems->ext_capab && elems->ext_capab_len >= 5 &&
		(elems->ext_capab[4] & WLAN_EXT_CAPA5_TDLS_CH_SW_PROHIBITED);

	/*
	 * Some APs are erroneously not including some inक्रमmation in their
	 * (re)association response frames. Try to recover by using the data
	 * from the beacon or probe response. This seems to afflict mobile
	 * 2G/3G/4G wअगरi routers, reported models include the "Onda PN51T",
	 * "Vodafone PocketWiFi 2", "ZTE MF60" and a similar T-Mobile device.
	 */
	अगर (!is_6ghz &&
	    ((assoc_data->wmm && !elems->wmm_param) ||
	     (!(अगरmgd->flags & IEEE80211_STA_DISABLE_HT) &&
	      (!elems->ht_cap_elem || !elems->ht_operation)) ||
	     (!(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT) &&
	      (!elems->vht_cap_elem || !elems->vht_operation)))) अणु
		स्थिर काष्ठा cfg80211_bss_ies *ies;
		काष्ठा ieee802_11_elems bss_elems;

		rcu_पढ़ो_lock();
		ies = rcu_dereference(cbss->ies);
		अगर (ies)
			bss_ies = kmemdup(ies, माप(*ies) + ies->len,
					  GFP_ATOMIC);
		rcu_पढ़ो_unlock();
		अगर (!bss_ies)
			वापस false;

		ieee802_11_parse_elems(bss_ies->data, bss_ies->len,
				       false, &bss_elems,
				       mgmt->bssid,
				       assoc_data->bss->bssid);
		अगर (assoc_data->wmm &&
		    !elems->wmm_param && bss_elems.wmm_param) अणु
			elems->wmm_param = bss_elems.wmm_param;
			sdata_info(sdata,
				   "AP bug: WMM param missing from AssocResp\n");
		पूर्ण

		/*
		 * Also check अगर we requested HT/VHT, otherwise the AP करोesn't
		 * have to include the IEs in the (re)association response.
		 */
		अगर (!elems->ht_cap_elem && bss_elems.ht_cap_elem &&
		    !(अगरmgd->flags & IEEE80211_STA_DISABLE_HT)) अणु
			elems->ht_cap_elem = bss_elems.ht_cap_elem;
			sdata_info(sdata,
				   "AP bug: HT capability missing from AssocResp\n");
		पूर्ण
		अगर (!elems->ht_operation && bss_elems.ht_operation &&
		    !(अगरmgd->flags & IEEE80211_STA_DISABLE_HT)) अणु
			elems->ht_operation = bss_elems.ht_operation;
			sdata_info(sdata,
				   "AP bug: HT operation missing from AssocResp\n");
		पूर्ण
		अगर (!elems->vht_cap_elem && bss_elems.vht_cap_elem &&
		    !(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT)) अणु
			elems->vht_cap_elem = bss_elems.vht_cap_elem;
			sdata_info(sdata,
				   "AP bug: VHT capa missing from AssocResp\n");
		पूर्ण
		अगर (!elems->vht_operation && bss_elems.vht_operation &&
		    !(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT)) अणु
			elems->vht_operation = bss_elems.vht_operation;
			sdata_info(sdata,
				   "AP bug: VHT operation missing from AssocResp\n");
		पूर्ण
	पूर्ण

	/*
	 * We previously checked these in the beacon/probe response, so
	 * they should be present here. This is just a safety net.
	 */
	अगर (!is_6ghz && !(अगरmgd->flags & IEEE80211_STA_DISABLE_HT) &&
	    (!elems->wmm_param || !elems->ht_cap_elem || !elems->ht_operation)) अणु
		sdata_info(sdata,
			   "HT AP is missing WMM params or HT capability/operation\n");
		ret = false;
		जाओ out;
	पूर्ण

	अगर (!is_6ghz && !(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT) &&
	    (!elems->vht_cap_elem || !elems->vht_operation)) अणु
		sdata_info(sdata,
			   "VHT AP is missing VHT capability/operation\n");
		ret = false;
		जाओ out;
	पूर्ण

	अगर (is_6ghz && !(अगरmgd->flags & IEEE80211_STA_DISABLE_HE) &&
	    !elems->he_6ghz_capa) अणु
		sdata_info(sdata,
			   "HE 6 GHz AP is missing HE 6 GHz band capability\n");
		ret = false;
		जाओ out;
	पूर्ण

	mutex_lock(&sdata->local->sta_mtx);
	/*
	 * station info was alपढ़ोy allocated and inserted beक्रमe
	 * the association and should be available to us
	 */
	sta = sta_info_get(sdata, cbss->bssid);
	अगर (WARN_ON(!sta)) अणु
		mutex_unlock(&sdata->local->sta_mtx);
		ret = false;
		जाओ out;
	पूर्ण

	sband = ieee80211_get_sband(sdata);
	अगर (!sband) अणु
		mutex_unlock(&sdata->local->sta_mtx);
		ret = false;
		जाओ out;
	पूर्ण

	अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_HE) &&
	    (!elems->he_cap || !elems->he_operation)) अणु
		mutex_unlock(&sdata->local->sta_mtx);
		sdata_info(sdata,
			   "HE AP is missing HE capability/operation\n");
		ret = false;
		जाओ out;
	पूर्ण

	/* Set up पूर्णांकernal HT/VHT capabilities */
	अगर (elems->ht_cap_elem && !(अगरmgd->flags & IEEE80211_STA_DISABLE_HT))
		ieee80211_ht_cap_ie_to_sta_ht_cap(sdata, sband,
						  elems->ht_cap_elem, sta);

	अगर (elems->vht_cap_elem && !(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT))
		ieee80211_vht_cap_ie_to_sta_vht_cap(sdata, sband,
						    elems->vht_cap_elem, sta);

	अगर (elems->he_operation && !(अगरmgd->flags & IEEE80211_STA_DISABLE_HE) &&
	    elems->he_cap) अणु
		ieee80211_he_cap_ie_to_sta_he_cap(sdata, sband,
						  elems->he_cap,
						  elems->he_cap_len,
						  elems->he_6ghz_capa,
						  sta);

		bss_conf->he_support = sta->sta.he_cap.has_he;
		अगर (elems->rsnx && elems->rsnx_len &&
		    (elems->rsnx[0] & WLAN_RSNX_CAPA_PROTECTED_TWT) &&
		    wiphy_ext_feature_isset(local->hw.wiphy,
					    NL80211_EXT_FEATURE_PROTECTED_TWT))
			bss_conf->twt_रक्षित = true;
		अन्यथा
			bss_conf->twt_रक्षित = false;

		changed |= ieee80211_recalc_twt_req(sdata, sta, elems);
	पूर्ण अन्यथा अणु
		bss_conf->he_support = false;
		bss_conf->twt_requester = false;
		bss_conf->twt_रक्षित = false;
	पूर्ण

	अगर (bss_conf->he_support) अणु
		bss_conf->he_bss_color.color =
			le32_get_bits(elems->he_operation->he_oper_params,
				      IEEE80211_HE_OPERATION_BSS_COLOR_MASK);
		bss_conf->he_bss_color.partial =
			le32_get_bits(elems->he_operation->he_oper_params,
				      IEEE80211_HE_OPERATION_PARTIAL_BSS_COLOR);
		bss_conf->he_bss_color.enabled =
			!le32_get_bits(elems->he_operation->he_oper_params,
				       IEEE80211_HE_OPERATION_BSS_COLOR_DISABLED);

		अगर (bss_conf->he_bss_color.enabled)
			changed |= BSS_CHANGED_HE_BSS_COLOR;

		bss_conf->htc_trig_based_pkt_ext =
			le32_get_bits(elems->he_operation->he_oper_params,
			      IEEE80211_HE_OPERATION_DFLT_PE_DURATION_MASK);
		bss_conf->frame_समय_rts_th =
			le32_get_bits(elems->he_operation->he_oper_params,
			      IEEE80211_HE_OPERATION_RTS_THRESHOLD_MASK);

		bss_conf->uora_exists = !!elems->uora_element;
		अगर (elems->uora_element)
			bss_conf->uora_ocw_range = elems->uora_element[0];

		ieee80211_he_op_ie_to_bss_conf(&sdata->vअगर, elems->he_operation);
		ieee80211_he_spr_ie_to_bss_conf(&sdata->vअगर, elems->he_spr);
		/* TODO: OPEN: what happens अगर BSS color disable is set? */
	पूर्ण

	अगर (cbss->transmitted_bss) अणु
		bss_conf->nontransmitted = true;
		ether_addr_copy(bss_conf->transmitter_bssid,
				cbss->transmitted_bss->bssid);
		bss_conf->bssid_indicator = cbss->max_bssid_indicator;
		bss_conf->bssid_index = cbss->bssid_index;
	पूर्ण

	/*
	 * Some APs, e.g. Netgear WNDR3700, report invalid HT operation data
	 * in their association response, so ignore that data क्रम our own
	 * configuration. If it changed since the last beacon, we'll get the
	 * next beacon and update then.
	 */

	/*
	 * If an operating mode notअगरication IE is present, override the
	 * NSS calculation (that would be करोne in rate_control_rate_init())
	 * and use the # of streams from that element.
	 */
	अगर (elems->opmode_notअगर &&
	    !(*elems->opmode_notअगर & IEEE80211_OPMODE_NOTIF_RX_NSS_TYPE_BF)) अणु
		u8 nss;

		nss = *elems->opmode_notअगर & IEEE80211_OPMODE_NOTIF_RX_NSS_MASK;
		nss >>= IEEE80211_OPMODE_NOTIF_RX_NSS_SHIFT;
		nss += 1;
		sta->sta.rx_nss = nss;
	पूर्ण

	rate_control_rate_init(sta);

	अगर (अगरmgd->flags & IEEE80211_STA_MFP_ENABLED) अणु
		set_sta_flag(sta, WLAN_STA_MFP);
		sta->sta.mfp = true;
	पूर्ण अन्यथा अणु
		sta->sta.mfp = false;
	पूर्ण

	sta->sta.wme = (elems->wmm_param || elems->s1g_capab) &&
		       local->hw.queues >= IEEE80211_NUM_ACS;

	err = sta_info_move_state(sta, IEEE80211_STA_ASSOC);
	अगर (!err && !(अगरmgd->flags & IEEE80211_STA_CONTROL_PORT))
		err = sta_info_move_state(sta, IEEE80211_STA_AUTHORIZED);
	अगर (err) अणु
		sdata_info(sdata,
			   "failed to move station %pM to desired state\n",
			   sta->sta.addr);
		WARN_ON(__sta_info_destroy(sta));
		mutex_unlock(&sdata->local->sta_mtx);
		ret = false;
		जाओ out;
	पूर्ण

	अगर (sdata->wdev.use_4addr)
		drv_sta_set_4addr(local, sdata, &sta->sta, true);

	mutex_unlock(&sdata->local->sta_mtx);

	/*
	 * Always handle WMM once after association regardless
	 * of the first value the AP uses. Setting -1 here has
	 * that effect because the AP values is an अचिन्हित
	 * 4-bit value.
	 */
	अगरmgd->wmm_last_param_set = -1;
	अगरmgd->mu_edca_last_param_set = -1;

	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_WMM) अणु
		ieee80211_set_wmm_शेष(sdata, false, false);
	पूर्ण अन्यथा अगर (!ieee80211_sta_wmm_params(local, sdata, elems->wmm_param,
					     elems->wmm_param_len,
					     elems->mu_edca_param_set)) अणु
		/* still enable QoS since we might have HT/VHT */
		ieee80211_set_wmm_शेष(sdata, false, true);
		/* set the disable-WMM flag in this हाल to disable
		 * tracking WMM parameter changes in the beacon अगर
		 * the parameters weren't actually valid. Doing so
		 * aव्योमs changing parameters very strangely when
		 * the AP is going back and क्रमth between valid and
		 * invalid parameters.
		 */
		अगरmgd->flags |= IEEE80211_STA_DISABLE_WMM;
	पूर्ण
	changed |= BSS_CHANGED_QOS;

	अगर (elems->max_idle_period_ie) अणु
		bss_conf->max_idle_period =
			le16_to_cpu(elems->max_idle_period_ie->max_idle_period);
		bss_conf->रक्षित_keep_alive =
			!!(elems->max_idle_period_ie->idle_options &
			   WLAN_IDLE_OPTIONS_PROTECTED_KEEP_ALIVE);
		changed |= BSS_CHANGED_KEEP_ALIVE;
	पूर्ण अन्यथा अणु
		bss_conf->max_idle_period = 0;
		bss_conf->रक्षित_keep_alive = false;
	पूर्ण

	/* set assoc capability (AID was alपढ़ोy set earlier),
	 * ieee80211_set_associated() will tell the driver */
	bss_conf->assoc_capability = capab_info;
	ieee80211_set_associated(sdata, cbss, changed);

	/*
	 * If we're using 4-addr mode, let the AP know that we're
	 * करोing so, so that it can create the STA VLAN on its side
	 */
	अगर (अगरmgd->use_4addr)
		ieee80211_send_4addr_nullfunc(local, sdata);

	/*
	 * Start समयr to probe the connection to the AP now.
	 * Also start the समयr that will detect beacon loss.
	 */
	ieee80211_sta_reset_beacon_monitor(sdata);
	ieee80211_sta_reset_conn_monitor(sdata);

	ret = true;
 out:
	kमुक्त(bss_ies);
	वापस ret;
पूर्ण

अटल व्योम ieee80211_rx_mgmt_assoc_resp(काष्ठा ieee80211_sub_अगर_data *sdata,
					 काष्ठा ieee80211_mgmt *mgmt,
					 माप_प्रकार len)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_mgd_assoc_data *assoc_data = अगरmgd->assoc_data;
	u16 capab_info, status_code, aid;
	काष्ठा ieee802_11_elems elems;
	पूर्णांक ac, uapsd_queues = -1;
	u8 *pos;
	bool reassoc;
	काष्ठा cfg80211_bss *cbss;
	काष्ठा ieee80211_event event = अणु
		.type = MLME_EVENT,
		.u.mlme.data = ASSOC_EVENT,
	पूर्ण;

	sdata_निश्चित_lock(sdata);

	अगर (!assoc_data)
		वापस;

	अगर (!ether_addr_equal(assoc_data->bss->bssid, mgmt->bssid))
		वापस;

	cbss = assoc_data->bss;

	/*
	 * AssocResp and ReassocResp have identical काष्ठाure, so process both
	 * of them in this function.
	 */

	अगर (len < 24 + 6)
		वापस;

	reassoc = ieee80211_is_reassoc_resp(mgmt->frame_control);
	capab_info = le16_to_cpu(mgmt->u.assoc_resp.capab_info);
	status_code = le16_to_cpu(mgmt->u.assoc_resp.status_code);
	pos = mgmt->u.assoc_resp.variable;
	aid = le16_to_cpu(mgmt->u.assoc_resp.aid);
	अगर (cbss->channel->band == NL80211_BAND_S1GHZ) अणु
		pos = (u8 *) mgmt->u.s1g_assoc_resp.variable;
		aid = 0; /* TODO */
	पूर्ण

	sdata_info(sdata,
		   "RX %sssocResp from %pM (capab=0x%x status=%d aid=%d)\n",
		   reassoc ? "Rea" : "A", mgmt->sa,
		   capab_info, status_code, (u16)(aid & ~(BIT(15) | BIT(14))));

	अगर (assoc_data->fils_kek_len &&
	    fils_decrypt_assoc_resp(sdata, (u8 *)mgmt, &len, assoc_data) < 0)
		वापस;

	ieee802_11_parse_elems(pos, len - (pos - (u8 *)mgmt), false, &elems,
			       mgmt->bssid, assoc_data->bss->bssid);

	अगर (status_code == WLAN_STATUS_ASSOC_REJECTED_TEMPORARILY &&
	    elems.समयout_पूर्णांक &&
	    elems.समयout_पूर्णांक->type == WLAN_TIMEOUT_ASSOC_COMEBACK) अणु
		u32 tu, ms;
		tu = le32_to_cpu(elems.समयout_पूर्णांक->value);
		ms = tu * 1024 / 1000;
		sdata_info(sdata,
			   "%pM rejected association temporarily; comeback duration %u TU (%u ms)\n",
			   mgmt->sa, tu, ms);
		assoc_data->समयout = jअगरfies + msecs_to_jअगरfies(ms);
		assoc_data->समयout_started = true;
		अगर (ms > IEEE80211_ASSOC_TIMEOUT)
			run_again(sdata, assoc_data->समयout);
		वापस;
	पूर्ण

	अगर (status_code != WLAN_STATUS_SUCCESS) अणु
		sdata_info(sdata, "%pM denied association (code=%d)\n",
			   mgmt->sa, status_code);
		ieee80211_destroy_assoc_data(sdata, false, false);
		event.u.mlme.status = MLME_DENIED;
		event.u.mlme.reason = status_code;
		drv_event_callback(sdata->local, sdata, &event);
	पूर्ण अन्यथा अणु
		अगर (!ieee80211_assoc_success(sdata, cbss, mgmt, len, &elems)) अणु
			/* oops -- पूर्णांकernal error -- send समयout क्रम now */
			ieee80211_destroy_assoc_data(sdata, false, false);
			cfg80211_assoc_समयout(sdata->dev, cbss);
			वापस;
		पूर्ण
		event.u.mlme.status = MLME_SUCCESS;
		drv_event_callback(sdata->local, sdata, &event);
		sdata_info(sdata, "associated\n");

		/*
		 * destroy assoc_data afterwards, as otherwise an idle
		 * recalc after assoc_data is शून्य but beक्रमe associated
		 * is set can cause the पूर्णांकerface to go idle
		 */
		ieee80211_destroy_assoc_data(sdata, true, false);

		/* get uapsd queues configuration */
		uapsd_queues = 0;
		क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			अगर (sdata->tx_conf[ac].uapsd)
				uapsd_queues |= ieee80211_ac_to_qos_mask[ac];
	पूर्ण

	cfg80211_rx_assoc_resp(sdata->dev, cbss, (u8 *)mgmt, len, uapsd_queues,
			       अगरmgd->assoc_req_ies, अगरmgd->assoc_req_ies_len);
पूर्ण

अटल व्योम ieee80211_rx_bss_info(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
				  काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_bss *bss;
	काष्ठा ieee80211_channel *channel;

	sdata_निश्चित_lock(sdata);

	channel = ieee80211_get_channel_khz(local->hw.wiphy,
					ieee80211_rx_status_to_khz(rx_status));
	अगर (!channel)
		वापस;

	bss = ieee80211_bss_info_update(local, rx_status, mgmt, len, channel);
	अगर (bss) अणु
		sdata->vअगर.bss_conf.beacon_rate = bss->beacon_rate;
		ieee80211_rx_bss_put(local, bss);
	पूर्ण
पूर्ण


अटल व्योम ieee80211_rx_mgmt_probe_resp(काष्ठा ieee80211_sub_अगर_data *sdata,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)skb->data;
	काष्ठा ieee80211_अगर_managed *अगरmgd;
	काष्ठा ieee80211_rx_status *rx_status = (व्योम *) skb->cb;
	काष्ठा ieee80211_channel *channel;
	माप_प्रकार baselen, len = skb->len;

	अगरmgd = &sdata->u.mgd;

	sdata_निश्चित_lock(sdata);

	/*
	 * According to Draft P802.11ax D6.0 clause 26.17.2.3.2:
	 * "If a 6 GHz AP receives a Probe Request frame  and responds with
	 * a Probe Response frame [..], the Address 1 field of the Probe
	 * Response frame shall be set to the broadcast address [..]"
	 * So, on 6GHz band we should also accept broadcast responses.
	 */
	channel = ieee80211_get_channel(sdata->local->hw.wiphy,
					rx_status->freq);
	अगर (!channel)
		वापस;

	अगर (!ether_addr_equal(mgmt->da, sdata->vअगर.addr) &&
	    (channel->band != NL80211_BAND_6GHZ ||
	     !is_broadcast_ether_addr(mgmt->da)))
		वापस; /* ignore ProbeResp to क्रमeign address */

	baselen = (u8 *) mgmt->u.probe_resp.variable - (u8 *) mgmt;
	अगर (baselen > len)
		वापस;

	ieee80211_rx_bss_info(sdata, mgmt, len, rx_status);

	अगर (अगरmgd->associated &&
	    ether_addr_equal(mgmt->bssid, अगरmgd->associated->bssid))
		ieee80211_reset_ap_probe(sdata);
पूर्ण

/*
 * This is the canonical list of inक्रमmation elements we care about,
 * the filter code also gives us all changes to the Microsoft OUI
 * (00:50:F2) venकरोr IE which is used क्रम WMM which we need to track,
 * as well as the DTPC IE (part of the Cisco OUI) used क्रम संकेतing
 * changes to requested client घातer.
 *
 * We implement beacon filtering in software since that means we can
 * aव्योम processing the frame here and in cfg80211, and userspace
 * will not be able to tell whether the hardware supports it or not.
 *
 * XXX: This list needs to be dynamic -- userspace needs to be able to
 *	add items it requires. It also needs to be able to tell us to
 *	look out क्रम other venकरोr IEs.
 */
अटल स्थिर u64 care_about_ies =
	(1ULL << WLAN_EID_COUNTRY) |
	(1ULL << WLAN_EID_ERP_INFO) |
	(1ULL << WLAN_EID_CHANNEL_SWITCH) |
	(1ULL << WLAN_EID_PWR_CONSTRAINT) |
	(1ULL << WLAN_EID_HT_CAPABILITY) |
	(1ULL << WLAN_EID_HT_OPERATION) |
	(1ULL << WLAN_EID_EXT_CHANSWITCH_ANN);

अटल व्योम ieee80211_handle_beacon_sig(काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा ieee80211_अगर_managed *अगरmgd,
					काष्ठा ieee80211_bss_conf *bss_conf,
					काष्ठा ieee80211_local *local,
					काष्ठा ieee80211_rx_status *rx_status)
अणु
	/* Track average RSSI from the Beacon frames of the current AP */

	अगर (अगरmgd->flags & IEEE80211_STA_RESET_SIGNAL_AVE) अणु
		अगरmgd->flags &= ~IEEE80211_STA_RESET_SIGNAL_AVE;
		ewma_beacon_संकेत_init(&अगरmgd->ave_beacon_संकेत);
		अगरmgd->last_cqm_event_संकेत = 0;
		अगरmgd->count_beacon_संकेत = 1;
		अगरmgd->last_ave_beacon_संकेत = 0;
	पूर्ण अन्यथा अणु
		अगरmgd->count_beacon_संकेत++;
	पूर्ण

	ewma_beacon_संकेत_add(&अगरmgd->ave_beacon_संकेत, -rx_status->संकेत);

	अगर (अगरmgd->rssi_min_thold != अगरmgd->rssi_max_thold &&
	    अगरmgd->count_beacon_संकेत >= IEEE80211_SIGNAL_AVE_MIN_COUNT) अणु
		पूर्णांक sig = -ewma_beacon_संकेत_पढ़ो(&अगरmgd->ave_beacon_संकेत);
		पूर्णांक last_sig = अगरmgd->last_ave_beacon_संकेत;
		काष्ठा ieee80211_event event = अणु
			.type = RSSI_EVENT,
		पूर्ण;

		/*
		 * अगर संकेत crosses either of the boundaries, invoke callback
		 * with appropriate parameters
		 */
		अगर (sig > अगरmgd->rssi_max_thold &&
		    (last_sig <= अगरmgd->rssi_min_thold || last_sig == 0)) अणु
			अगरmgd->last_ave_beacon_संकेत = sig;
			event.u.rssi.data = RSSI_EVENT_HIGH;
			drv_event_callback(local, sdata, &event);
		पूर्ण अन्यथा अगर (sig < अगरmgd->rssi_min_thold &&
			   (last_sig >= अगरmgd->rssi_max_thold ||
			   last_sig == 0)) अणु
			अगरmgd->last_ave_beacon_संकेत = sig;
			event.u.rssi.data = RSSI_EVENT_LOW;
			drv_event_callback(local, sdata, &event);
		पूर्ण
	पूर्ण

	अगर (bss_conf->cqm_rssi_thold &&
	    अगरmgd->count_beacon_संकेत >= IEEE80211_SIGNAL_AVE_MIN_COUNT &&
	    !(sdata->vअगर.driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI)) अणु
		पूर्णांक sig = -ewma_beacon_संकेत_पढ़ो(&अगरmgd->ave_beacon_संकेत);
		पूर्णांक last_event = अगरmgd->last_cqm_event_संकेत;
		पूर्णांक thold = bss_conf->cqm_rssi_thold;
		पूर्णांक hyst = bss_conf->cqm_rssi_hyst;

		अगर (sig < thold &&
		    (last_event == 0 || sig < last_event - hyst)) अणु
			अगरmgd->last_cqm_event_संकेत = sig;
			ieee80211_cqm_rssi_notअगरy(
				&sdata->vअगर,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
				sig, GFP_KERNEL);
		पूर्ण अन्यथा अगर (sig > thold &&
			   (last_event == 0 || sig > last_event + hyst)) अणु
			अगरmgd->last_cqm_event_संकेत = sig;
			ieee80211_cqm_rssi_notअगरy(
				&sdata->vअगर,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
				sig, GFP_KERNEL);
		पूर्ण
	पूर्ण

	अगर (bss_conf->cqm_rssi_low &&
	    अगरmgd->count_beacon_संकेत >= IEEE80211_SIGNAL_AVE_MIN_COUNT) अणु
		पूर्णांक sig = -ewma_beacon_संकेत_पढ़ो(&अगरmgd->ave_beacon_संकेत);
		पूर्णांक last_event = अगरmgd->last_cqm_event_संकेत;
		पूर्णांक low = bss_conf->cqm_rssi_low;
		पूर्णांक high = bss_conf->cqm_rssi_high;

		अगर (sig < low &&
		    (last_event == 0 || last_event >= low)) अणु
			अगरmgd->last_cqm_event_संकेत = sig;
			ieee80211_cqm_rssi_notअगरy(
				&sdata->vअगर,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
				sig, GFP_KERNEL);
		पूर्ण अन्यथा अगर (sig > high &&
			   (last_event == 0 || last_event <= high)) अणु
			अगरmgd->last_cqm_event_संकेत = sig;
			ieee80211_cqm_rssi_notअगरy(
				&sdata->vअगर,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
				sig, GFP_KERNEL);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool ieee80211_rx_our_beacon(स्थिर u8 *tx_bssid,
				    काष्ठा cfg80211_bss *bss)
अणु
	अगर (ether_addr_equal(tx_bssid, bss->bssid))
		वापस true;
	अगर (!bss->transmitted_bss)
		वापस false;
	वापस ether_addr_equal(tx_bssid, bss->transmitted_bss->bssid);
पूर्ण

अटल व्योम ieee80211_rx_mgmt_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा ieee80211_hdr *hdr, माप_प्रकार len,
				     काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_bss_conf *bss_conf = &sdata->vअगर.bss_conf;
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *) hdr;
	माप_प्रकार baselen;
	काष्ठा ieee802_11_elems elems;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_channel *chan;
	काष्ठा sta_info *sta;
	u32 changed = 0;
	bool erp_valid;
	u8 erp_value = 0;
	u32 ncrc = 0;
	u8 *bssid, *variable = mgmt->u.beacon.variable;
	u8 deauth_buf[IEEE80211_DEAUTH_FRAME_LEN];

	sdata_निश्चित_lock(sdata);

	/* Process beacon from the current BSS */
	bssid = ieee80211_get_bssid(hdr, len, sdata->vअगर.type);
	अगर (ieee80211_is_s1g_beacon(mgmt->frame_control)) अणु
		काष्ठा ieee80211_ext *ext = (व्योम *) mgmt;

		अगर (ieee80211_is_s1g_लघु_beacon(ext->frame_control))
			variable = ext->u.s1g_लघु_beacon.variable;
		अन्यथा
			variable = ext->u.s1g_beacon.variable;
	पूर्ण

	baselen = (u8 *) variable - (u8 *) mgmt;
	अगर (baselen > len)
		वापस;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (!chanctx_conf) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	अगर (ieee80211_rx_status_to_khz(rx_status) !=
	    ieee80211_channel_to_khz(chanctx_conf->def.chan)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	chan = chanctx_conf->def.chan;
	rcu_पढ़ो_unlock();

	अगर (अगरmgd->assoc_data && अगरmgd->assoc_data->need_beacon &&
	    ieee80211_rx_our_beacon(bssid, अगरmgd->assoc_data->bss)) अणु
		ieee802_11_parse_elems(variable,
				       len - baselen, false, &elems,
				       bssid,
				       अगरmgd->assoc_data->bss->bssid);

		ieee80211_rx_bss_info(sdata, mgmt, len, rx_status);

		अगर (elems.dtim_period)
			अगरmgd->dtim_period = elems.dtim_period;
		अगरmgd->have_beacon = true;
		अगरmgd->assoc_data->need_beacon = false;
		अगर (ieee80211_hw_check(&local->hw, TIMING_BEACON_ONLY)) अणु
			sdata->vअगर.bss_conf.sync_tsf =
				le64_to_cpu(mgmt->u.beacon.बारtamp);
			sdata->vअगर.bss_conf.sync_device_ts =
				rx_status->device_बारtamp;
			sdata->vअगर.bss_conf.sync_dtim_count = elems.dtim_count;
		पूर्ण

		अगर (elems.mbssid_config_ie)
			bss_conf->profile_periodicity =
				elems.mbssid_config_ie->profile_periodicity;
		अन्यथा
			bss_conf->profile_periodicity = 0;

		अगर (elems.ext_capab_len >= 11 &&
		    (elems.ext_capab[10] & WLAN_EXT_CAPA11_EMA_SUPPORT))
			bss_conf->ema_ap = true;
		अन्यथा
			bss_conf->ema_ap = false;

		/* जारी assoc process */
		अगरmgd->assoc_data->समयout = jअगरfies;
		अगरmgd->assoc_data->समयout_started = true;
		run_again(sdata, अगरmgd->assoc_data->समयout);
		वापस;
	पूर्ण

	अगर (!अगरmgd->associated ||
	    !ieee80211_rx_our_beacon(bssid,  अगरmgd->associated))
		वापस;
	bssid = अगरmgd->associated->bssid;

	अगर (!(rx_status->flag & RX_FLAG_NO_SIGNAL_VAL))
		ieee80211_handle_beacon_sig(sdata, अगरmgd, bss_conf,
					    local, rx_status);

	अगर (अगरmgd->flags & IEEE80211_STA_CONNECTION_POLL) अणु
		mlme_dbg_ratelimited(sdata,
				     "cancelling AP probe due to a received beacon\n");
		ieee80211_reset_ap_probe(sdata);
	पूर्ण

	/*
	 * Push the beacon loss detection पूर्णांकo the future since
	 * we are processing a beacon from the AP just now.
	 */
	ieee80211_sta_reset_beacon_monitor(sdata);

	/* TODO: CRC urrently not calculated on S1G Beacon Compatibility
	 * element (which carries the beacon पूर्णांकerval). Don't क्रमget to add a
	 * bit to care_about_ies[] above अगर mac80211 is पूर्णांकerested in a
	 * changing S1G element.
	 */
	अगर (!ieee80211_is_s1g_beacon(hdr->frame_control))
		ncrc = crc32_be(0, (व्योम *)&mgmt->u.beacon.beacon_पूर्णांक, 4);
	ncrc = ieee802_11_parse_elems_crc(variable,
					  len - baselen, false, &elems,
					  care_about_ies, ncrc,
					  mgmt->bssid, bssid);

	अगर (ieee80211_hw_check(&local->hw, PS_शून्यFUNC_STACK) &&
	    ieee80211_check_tim(elems.tim, elems.tim_len, bss_conf->aid)) अणु
		अगर (local->hw.conf.dynamic_ps_समयout > 0) अणु
			अगर (local->hw.conf.flags & IEEE80211_CONF_PS) अणु
				local->hw.conf.flags &= ~IEEE80211_CONF_PS;
				ieee80211_hw_config(local,
						    IEEE80211_CONF_CHANGE_PS);
			पूर्ण
			ieee80211_send_nullfunc(local, sdata, false);
		पूर्ण अन्यथा अगर (!local->pspolling && sdata->u.mgd.घातersave) अणु
			local->pspolling = true;

			/*
			 * Here is assumed that the driver will be
			 * able to send ps-poll frame and receive a
			 * response even though घातer save mode is
			 * enabled, but some drivers might require
			 * to disable घातer save here. This needs
			 * to be investigated.
			 */
			ieee80211_send_pspoll(local, sdata);
		पूर्ण
	पूर्ण

	अगर (sdata->vअगर.p2p ||
	    sdata->vअगर.driver_flags & IEEE80211_VIF_GET_NOA_UPDATE) अणु
		काष्ठा ieee80211_p2p_noa_attr noa = अणुपूर्ण;
		पूर्णांक ret;

		ret = cfg80211_get_p2p_attr(variable,
					    len - baselen,
					    IEEE80211_P2P_ATTR_ABSENCE_NOTICE,
					    (u8 *) &noa, माप(noa));
		अगर (ret >= 2) अणु
			अगर (sdata->u.mgd.p2p_noa_index != noa.index) अणु
				/* valid noa_attr and index changed */
				sdata->u.mgd.p2p_noa_index = noa.index;
				स_नकल(&bss_conf->p2p_noa_attr, &noa, माप(noa));
				changed |= BSS_CHANGED_P2P_PS;
				/*
				 * make sure we update all inक्रमmation, the CRC
				 * mechanism करोesn't look at P2P attributes.
				 */
				अगरmgd->beacon_crc_valid = false;
			पूर्ण
		पूर्ण अन्यथा अगर (sdata->u.mgd.p2p_noa_index != -1) अणु
			/* noa_attr not found and we had valid noa_attr beक्रमe */
			sdata->u.mgd.p2p_noa_index = -1;
			स_रखो(&bss_conf->p2p_noa_attr, 0, माप(bss_conf->p2p_noa_attr));
			changed |= BSS_CHANGED_P2P_PS;
			अगरmgd->beacon_crc_valid = false;
		पूर्ण
	पूर्ण

	अगर (अगरmgd->csa_रुकोing_bcn)
		ieee80211_chचयन_post_beacon(sdata);

	/*
	 * Update beacon timing and dtim count on every beacon appearance. This
	 * will allow the driver to use the most updated values. Do it beक्रमe
	 * comparing this one with last received beacon.
	 * IMPORTANT: These parameters would possibly be out of sync by the समय
	 * the driver will use them. The synchronized view is currently
	 * guaranteed only in certain callbacks.
	 */
	अगर (ieee80211_hw_check(&local->hw, TIMING_BEACON_ONLY) &&
	    !ieee80211_is_s1g_beacon(hdr->frame_control)) अणु
		sdata->vअगर.bss_conf.sync_tsf =
			le64_to_cpu(mgmt->u.beacon.बारtamp);
		sdata->vअगर.bss_conf.sync_device_ts =
			rx_status->device_बारtamp;
		sdata->vअगर.bss_conf.sync_dtim_count = elems.dtim_count;
	पूर्ण

	अगर ((ncrc == अगरmgd->beacon_crc && अगरmgd->beacon_crc_valid) ||
	    ieee80211_is_s1g_लघु_beacon(mgmt->frame_control))
		वापस;
	अगरmgd->beacon_crc = ncrc;
	अगरmgd->beacon_crc_valid = true;

	ieee80211_rx_bss_info(sdata, mgmt, len, rx_status);

	ieee80211_sta_process_chanचयन(sdata, rx_status->maस_समय,
					 rx_status->device_बारtamp,
					 &elems, true);

	अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_WMM) &&
	    ieee80211_sta_wmm_params(local, sdata, elems.wmm_param,
				     elems.wmm_param_len,
				     elems.mu_edca_param_set))
		changed |= BSS_CHANGED_QOS;

	/*
	 * If we haven't had a beacon beक्रमe, tell the driver about the
	 * DTIM period (and beacon timing अगर desired) now.
	 */
	अगर (!अगरmgd->have_beacon) अणु
		/* a few bogus AP send dtim_period = 0 or no TIM IE */
		bss_conf->dtim_period = elems.dtim_period ?: 1;

		changed |= BSS_CHANGED_BEACON_INFO;
		अगरmgd->have_beacon = true;

		mutex_lock(&local->अगरlist_mtx);
		ieee80211_recalc_ps(local);
		mutex_unlock(&local->अगरlist_mtx);

		ieee80211_recalc_ps_vअगर(sdata);
	पूर्ण

	अगर (elems.erp_info) अणु
		erp_valid = true;
		erp_value = elems.erp_info[0];
	पूर्ण अन्यथा अणु
		erp_valid = false;
	पूर्ण

	अगर (!ieee80211_is_s1g_beacon(hdr->frame_control))
		changed |= ieee80211_handle_bss_capability(sdata,
				le16_to_cpu(mgmt->u.beacon.capab_info),
				erp_valid, erp_value);

	mutex_lock(&local->sta_mtx);
	sta = sta_info_get(sdata, bssid);

	changed |= ieee80211_recalc_twt_req(sdata, sta, &elems);

	अगर (ieee80211_config_bw(sdata, sta, elems.ht_cap_elem,
				elems.vht_cap_elem, elems.ht_operation,
				elems.vht_operation, elems.he_operation,
				elems.s1g_oper, bssid, &changed)) अणु
		mutex_unlock(&local->sta_mtx);
		sdata_info(sdata,
			   "failed to follow AP %pM bandwidth change, disconnect\n",
			   bssid);
		ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH,
				       WLAN_REASON_DEAUTH_LEAVING,
				       true, deauth_buf);
		ieee80211_report_disconnect(sdata, deauth_buf,
					    माप(deauth_buf), true,
					    WLAN_REASON_DEAUTH_LEAVING,
					    false);
		वापस;
	पूर्ण

	अगर (sta && elems.opmode_notअगर)
		ieee80211_vht_handle_opmode(sdata, sta, *elems.opmode_notअगर,
					    rx_status->band);
	mutex_unlock(&local->sta_mtx);

	changed |= ieee80211_handle_pwr_स्थिरr(sdata, chan, mgmt,
					       elems.country_elem,
					       elems.country_elem_len,
					       elems.pwr_स्थिरr_elem,
					       elems.cisco_dtpc_elem);

	ieee80211_bss_info_change_notअगरy(sdata, changed);
पूर्ण

व्योम ieee80211_sta_rx_queued_ext(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *rx_status;
	काष्ठा ieee80211_hdr *hdr;
	u16 fc;

	rx_status = (काष्ठा ieee80211_rx_status *) skb->cb;
	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	fc = le16_to_cpu(hdr->frame_control);

	sdata_lock(sdata);
	चयन (fc & IEEE80211_FCTL_STYPE) अणु
	हाल IEEE80211_STYPE_S1G_BEACON:
		ieee80211_rx_mgmt_beacon(sdata, hdr, skb->len, rx_status);
		अवरोध;
	पूर्ण
	sdata_unlock(sdata);
पूर्ण

व्योम ieee80211_sta_rx_queued_mgmt(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *rx_status;
	काष्ठा ieee80211_mgmt *mgmt;
	u16 fc;
	काष्ठा ieee802_11_elems elems;
	पूर्णांक ies_len;

	rx_status = (काष्ठा ieee80211_rx_status *) skb->cb;
	mgmt = (काष्ठा ieee80211_mgmt *) skb->data;
	fc = le16_to_cpu(mgmt->frame_control);

	sdata_lock(sdata);

	चयन (fc & IEEE80211_FCTL_STYPE) अणु
	हाल IEEE80211_STYPE_BEACON:
		ieee80211_rx_mgmt_beacon(sdata, (व्योम *)mgmt,
					 skb->len, rx_status);
		अवरोध;
	हाल IEEE80211_STYPE_PROBE_RESP:
		ieee80211_rx_mgmt_probe_resp(sdata, skb);
		अवरोध;
	हाल IEEE80211_STYPE_AUTH:
		ieee80211_rx_mgmt_auth(sdata, mgmt, skb->len);
		अवरोध;
	हाल IEEE80211_STYPE_DEAUTH:
		ieee80211_rx_mgmt_deauth(sdata, mgmt, skb->len);
		अवरोध;
	हाल IEEE80211_STYPE_DISASSOC:
		ieee80211_rx_mgmt_disassoc(sdata, mgmt, skb->len);
		अवरोध;
	हाल IEEE80211_STYPE_ASSOC_RESP:
	हाल IEEE80211_STYPE_REASSOC_RESP:
		ieee80211_rx_mgmt_assoc_resp(sdata, mgmt, skb->len);
		अवरोध;
	हाल IEEE80211_STYPE_ACTION:
		अगर (mgmt->u.action.category == WLAN_CATEGORY_SPECTRUM_MGMT) अणु
			ies_len = skb->len -
				  दुरत्व(काष्ठा ieee80211_mgmt,
					   u.action.u.chan_चयन.variable);

			अगर (ies_len < 0)
				अवरोध;

			/* CSA IE cannot be overridden, no need क्रम BSSID */
			ieee802_11_parse_elems(
				mgmt->u.action.u.chan_चयन.variable,
				ies_len, true, &elems, mgmt->bssid, शून्य);

			अगर (elems.parse_error)
				अवरोध;

			ieee80211_sta_process_chanचयन(sdata,
						 rx_status->maस_समय,
						 rx_status->device_बारtamp,
						 &elems, false);
		पूर्ण अन्यथा अगर (mgmt->u.action.category == WLAN_CATEGORY_PUBLIC) अणु
			ies_len = skb->len -
				  दुरत्व(काष्ठा ieee80211_mgmt,
					   u.action.u.ext_chan_चयन.variable);

			अगर (ies_len < 0)
				अवरोध;

			/*
			 * extended CSA IE can't be overridden, no need क्रम
			 * BSSID
			 */
			ieee802_11_parse_elems(
				mgmt->u.action.u.ext_chan_चयन.variable,
				ies_len, true, &elems, mgmt->bssid, शून्य);

			अगर (elems.parse_error)
				अवरोध;

			/* क्रम the handling code pretend this was also an IE */
			elems.ext_chansw_ie =
				&mgmt->u.action.u.ext_chan_चयन.data;

			ieee80211_sta_process_chanचयन(sdata,
						 rx_status->maस_समय,
						 rx_status->device_बारtamp,
						 &elems, false);
		पूर्ण
		अवरोध;
	पूर्ण
	sdata_unlock(sdata);
पूर्ण

अटल व्योम ieee80211_sta_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		from_समयr(sdata, t, u.mgd.समयr);

	ieee80211_queue_work(&sdata->local->hw, &sdata->work);
पूर्ण

व्योम ieee80211_sta_connection_lost(काष्ठा ieee80211_sub_अगर_data *sdata,
				   u8 *bssid, u8 reason, bool tx)
अणु
	u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];

	ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH, reason,
			       tx, frame_buf);

	ieee80211_report_disconnect(sdata, frame_buf, माप(frame_buf), true,
				    reason, false);
पूर्ण

अटल पूर्णांक ieee80211_auth(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_mgd_auth_data *auth_data = अगरmgd->auth_data;
	u32 tx_flags = 0;
	u16 trans = 1;
	u16 status = 0;
	u16 prepare_tx_duration = 0;

	sdata_निश्चित_lock(sdata);

	अगर (WARN_ON_ONCE(!auth_data))
		वापस -EINVAL;

	auth_data->tries++;

	अगर (auth_data->tries > IEEE80211_AUTH_MAX_TRIES) अणु
		sdata_info(sdata, "authentication with %pM timed out\n",
			   auth_data->bss->bssid);

		/*
		 * Most likely AP is not in the range so हटाओ the
		 * bss काष्ठा क्रम that AP.
		 */
		cfg80211_unlink_bss(local->hw.wiphy, auth_data->bss);

		वापस -ETIMEDOUT;
	पूर्ण

	अगर (auth_data->algorithm == WLAN_AUTH_SAE)
		prepare_tx_duration =
			jअगरfies_to_msecs(IEEE80211_AUTH_TIMEOUT_SAE);

	drv_mgd_prepare_tx(local, sdata, prepare_tx_duration);

	sdata_info(sdata, "send auth to %pM (try %d/%d)\n",
		   auth_data->bss->bssid, auth_data->tries,
		   IEEE80211_AUTH_MAX_TRIES);

	auth_data->expected_transaction = 2;

	अगर (auth_data->algorithm == WLAN_AUTH_SAE) अणु
		trans = auth_data->sae_trans;
		status = auth_data->sae_status;
		auth_data->expected_transaction = trans;
	पूर्ण

	अगर (ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS))
		tx_flags = IEEE80211_TX_CTL_REQ_TX_STATUS |
			   IEEE80211_TX_INTFL_MLME_CONN_TX;

	ieee80211_send_auth(sdata, trans, auth_data->algorithm, status,
			    auth_data->data, auth_data->data_len,
			    auth_data->bss->bssid,
			    auth_data->bss->bssid, शून्य, 0, 0,
			    tx_flags);

	अगर (tx_flags == 0) अणु
		अगर (auth_data->algorithm == WLAN_AUTH_SAE)
			auth_data->समयout = jअगरfies +
				IEEE80211_AUTH_TIMEOUT_SAE;
		अन्यथा
			auth_data->समयout = jअगरfies + IEEE80211_AUTH_TIMEOUT;
	पूर्ण अन्यथा अणु
		auth_data->समयout =
			round_jअगरfies_up(jअगरfies + IEEE80211_AUTH_TIMEOUT_LONG);
	पूर्ण

	auth_data->समयout_started = true;
	run_again(sdata, auth_data->समयout);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_करो_assoc(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_mgd_assoc_data *assoc_data = sdata->u.mgd.assoc_data;
	काष्ठा ieee80211_local *local = sdata->local;

	sdata_निश्चित_lock(sdata);

	assoc_data->tries++;
	अगर (assoc_data->tries > IEEE80211_ASSOC_MAX_TRIES) अणु
		sdata_info(sdata, "association with %pM timed out\n",
			   assoc_data->bss->bssid);

		/*
		 * Most likely AP is not in the range so हटाओ the
		 * bss काष्ठा क्रम that AP.
		 */
		cfg80211_unlink_bss(local->hw.wiphy, assoc_data->bss);

		वापस -ETIMEDOUT;
	पूर्ण

	sdata_info(sdata, "associate with %pM (try %d/%d)\n",
		   assoc_data->bss->bssid, assoc_data->tries,
		   IEEE80211_ASSOC_MAX_TRIES);
	ieee80211_send_assoc(sdata);

	अगर (!ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS)) अणु
		assoc_data->समयout = jअगरfies + IEEE80211_ASSOC_TIMEOUT;
		assoc_data->समयout_started = true;
		run_again(sdata, assoc_data->समयout);
	पूर्ण अन्यथा अणु
		assoc_data->समयout =
			round_jअगरfies_up(jअगरfies +
					 IEEE80211_ASSOC_TIMEOUT_LONG);
		assoc_data->समयout_started = true;
		run_again(sdata, assoc_data->समयout);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ieee80211_mgd_conn_tx_status(काष्ठा ieee80211_sub_अगर_data *sdata,
				  __le16 fc, bool acked)
अणु
	काष्ठा ieee80211_local *local = sdata->local;

	sdata->u.mgd.status_fc = fc;
	sdata->u.mgd.status_acked = acked;
	sdata->u.mgd.status_received = true;

	ieee80211_queue_work(&local->hw, &sdata->work);
पूर्ण

व्योम ieee80211_sta_work(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	sdata_lock(sdata);

	अगर (अगरmgd->status_received) अणु
		__le16 fc = अगरmgd->status_fc;
		bool status_acked = अगरmgd->status_acked;

		अगरmgd->status_received = false;
		अगर (अगरmgd->auth_data && ieee80211_is_auth(fc)) अणु
			अगर (status_acked) अणु
				अगर (अगरmgd->auth_data->algorithm ==
				    WLAN_AUTH_SAE)
					अगरmgd->auth_data->समयout =
						jअगरfies +
						IEEE80211_AUTH_TIMEOUT_SAE;
				अन्यथा
					अगरmgd->auth_data->समयout =
						jअगरfies +
						IEEE80211_AUTH_TIMEOUT_SHORT;
				run_again(sdata, अगरmgd->auth_data->समयout);
			पूर्ण अन्यथा अणु
				अगरmgd->auth_data->समयout = jअगरfies - 1;
			पूर्ण
			अगरmgd->auth_data->समयout_started = true;
		पूर्ण अन्यथा अगर (अगरmgd->assoc_data &&
			   (ieee80211_is_assoc_req(fc) ||
			    ieee80211_is_reassoc_req(fc))) अणु
			अगर (status_acked) अणु
				अगरmgd->assoc_data->समयout =
					jअगरfies + IEEE80211_ASSOC_TIMEOUT_SHORT;
				run_again(sdata, अगरmgd->assoc_data->समयout);
			पूर्ण अन्यथा अणु
				अगरmgd->assoc_data->समयout = jअगरfies - 1;
			पूर्ण
			अगरmgd->assoc_data->समयout_started = true;
		पूर्ण
	पूर्ण

	अगर (अगरmgd->auth_data && अगरmgd->auth_data->समयout_started &&
	    समय_after(jअगरfies, अगरmgd->auth_data->समयout)) अणु
		अगर (अगरmgd->auth_data->करोne) अणु
			/*
			 * ok ... we रुकोed क्रम assoc but userspace didn't,
			 * so let's just समाप्त the auth data
			 */
			ieee80211_destroy_auth_data(sdata, false);
		पूर्ण अन्यथा अगर (ieee80211_auth(sdata)) अणु
			u8 bssid[ETH_ALEN];
			काष्ठा ieee80211_event event = अणु
				.type = MLME_EVENT,
				.u.mlme.data = AUTH_EVENT,
				.u.mlme.status = MLME_TIMEOUT,
			पूर्ण;

			स_नकल(bssid, अगरmgd->auth_data->bss->bssid, ETH_ALEN);

			ieee80211_destroy_auth_data(sdata, false);

			cfg80211_auth_समयout(sdata->dev, bssid);
			drv_event_callback(sdata->local, sdata, &event);
		पूर्ण
	पूर्ण अन्यथा अगर (अगरmgd->auth_data && अगरmgd->auth_data->समयout_started)
		run_again(sdata, अगरmgd->auth_data->समयout);

	अगर (अगरmgd->assoc_data && अगरmgd->assoc_data->समयout_started &&
	    समय_after(jअगरfies, अगरmgd->assoc_data->समयout)) अणु
		अगर ((अगरmgd->assoc_data->need_beacon && !अगरmgd->have_beacon) ||
		    ieee80211_करो_assoc(sdata)) अणु
			काष्ठा cfg80211_bss *bss = अगरmgd->assoc_data->bss;
			काष्ठा ieee80211_event event = अणु
				.type = MLME_EVENT,
				.u.mlme.data = ASSOC_EVENT,
				.u.mlme.status = MLME_TIMEOUT,
			पूर्ण;

			ieee80211_destroy_assoc_data(sdata, false, false);
			cfg80211_assoc_समयout(sdata->dev, bss);
			drv_event_callback(sdata->local, sdata, &event);
		पूर्ण
	पूर्ण अन्यथा अगर (अगरmgd->assoc_data && अगरmgd->assoc_data->समयout_started)
		run_again(sdata, अगरmgd->assoc_data->समयout);

	अगर (अगरmgd->flags & IEEE80211_STA_CONNECTION_POLL &&
	    अगरmgd->associated) अणु
		u8 bssid[ETH_ALEN];
		पूर्णांक max_tries;

		स_नकल(bssid, अगरmgd->associated->bssid, ETH_ALEN);

		अगर (ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS))
			max_tries = max_nullfunc_tries;
		अन्यथा
			max_tries = max_probe_tries;

		/* ACK received क्रम nullfunc probing frame */
		अगर (!अगरmgd->probe_send_count)
			ieee80211_reset_ap_probe(sdata);
		अन्यथा अगर (अगरmgd->nullfunc_failed) अणु
			अगर (अगरmgd->probe_send_count < max_tries) अणु
				mlme_dbg(sdata,
					 "No ack for nullfunc frame to AP %pM, try %d/%i\n",
					 bssid, अगरmgd->probe_send_count,
					 max_tries);
				ieee80211_mgd_probe_ap_send(sdata);
			पूर्ण अन्यथा अणु
				mlme_dbg(sdata,
					 "No ack for nullfunc frame to AP %pM, disconnecting.\n",
					 bssid);
				ieee80211_sta_connection_lost(sdata, bssid,
					WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY,
					false);
			पूर्ण
		पूर्ण अन्यथा अगर (समय_is_after_jअगरfies(अगरmgd->probe_समयout))
			run_again(sdata, अगरmgd->probe_समयout);
		अन्यथा अगर (ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS)) अणु
			mlme_dbg(sdata,
				 "Failed to send nullfunc to AP %pM after %dms, disconnecting\n",
				 bssid, probe_रुको_ms);
			ieee80211_sta_connection_lost(sdata, bssid,
				WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY, false);
		पूर्ण अन्यथा अगर (अगरmgd->probe_send_count < max_tries) अणु
			mlme_dbg(sdata,
				 "No probe response from AP %pM after %dms, try %d/%i\n",
				 bssid, probe_रुको_ms,
				 अगरmgd->probe_send_count, max_tries);
			ieee80211_mgd_probe_ap_send(sdata);
		पूर्ण अन्यथा अणु
			/*
			 * We actually lost the connection ... or did we?
			 * Let's make sure!
			 */
			mlme_dbg(sdata,
				 "No probe response from AP %pM after %dms, disconnecting.\n",
				 bssid, probe_रुको_ms);

			ieee80211_sta_connection_lost(sdata, bssid,
				WLAN_REASON_DISASSOC_DUE_TO_INACTIVITY, false);
		पूर्ण
	पूर्ण

	sdata_unlock(sdata);
पूर्ण

अटल व्योम ieee80211_sta_bcn_mon_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		from_समयr(sdata, t, u.mgd.bcn_mon_समयr);
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	अगर (sdata->vअगर.csa_active && !अगरmgd->csa_रुकोing_bcn)
		वापस;

	अगर (sdata->vअगर.driver_flags & IEEE80211_VIF_BEACON_FILTER)
		वापस;

	sdata->u.mgd.connection_loss = false;
	ieee80211_queue_work(&sdata->local->hw,
			     &sdata->u.mgd.beacon_connection_loss_work);
पूर्ण

अटल व्योम ieee80211_sta_conn_mon_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		from_समयr(sdata, t, u.mgd.conn_mon_समयr);
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	अचिन्हित दीर्घ समयout;

	अगर (sdata->vअगर.csa_active && !अगरmgd->csa_रुकोing_bcn)
		वापस;

	sta = sta_info_get(sdata, अगरmgd->bssid);
	अगर (!sta)
		वापस;

	समयout = sta->status_stats.last_ack;
	अगर (समय_beक्रमe(sta->status_stats.last_ack, sta->rx_stats.last_rx))
		समयout = sta->rx_stats.last_rx;
	समयout += IEEE80211_CONNECTION_IDLE_TIME;

	/* If समयout is after now, then update समयr to fire at
	 * the later date, but करो not actually probe at this समय.
	 */
	अगर (समय_is_after_jअगरfies(समयout)) अणु
		mod_समयr(&अगरmgd->conn_mon_समयr, round_jअगरfies_up(समयout));
		वापस;
	पूर्ण

	ieee80211_queue_work(&local->hw, &अगरmgd->monitor_work);
पूर्ण

अटल व्योम ieee80211_sta_monitor_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		container_of(work, काष्ठा ieee80211_sub_अगर_data,
			     u.mgd.monitor_work);

	ieee80211_mgd_probe_ap(sdata, false);
पूर्ण

अटल व्योम ieee80211_restart_sta_समयr(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION) अणु
		__ieee80211_stop_poll(sdata);

		/* let's probe the connection once */
		अगर (!ieee80211_hw_check(&sdata->local->hw, CONNECTION_MONITOR))
			ieee80211_queue_work(&sdata->local->hw,
					     &sdata->u.mgd.monitor_work);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
व्योम ieee80211_mgd_quiesce(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];

	sdata_lock(sdata);

	अगर (अगरmgd->auth_data || अगरmgd->assoc_data) अणु
		स्थिर u8 *bssid = अगरmgd->auth_data ?
				अगरmgd->auth_data->bss->bssid :
				अगरmgd->assoc_data->bss->bssid;

		/*
		 * If we are trying to authenticate / associate जबतक suspending,
		 * cfg80211 won't know and won't actually पात those attempts,
		 * thus we need to करो that ourselves.
		 */
		ieee80211_send_deauth_disassoc(sdata, bssid, bssid,
					       IEEE80211_STYPE_DEAUTH,
					       WLAN_REASON_DEAUTH_LEAVING,
					       false, frame_buf);
		अगर (अगरmgd->assoc_data)
			ieee80211_destroy_assoc_data(sdata, false, true);
		अगर (अगरmgd->auth_data)
			ieee80211_destroy_auth_data(sdata, false);
		cfg80211_tx_mlme_mgmt(sdata->dev, frame_buf,
				      IEEE80211_DEAUTH_FRAME_LEN,
				      false);
	पूर्ण

	/* This is a bit of a hack - we should find a better and more generic
	 * solution to this. Normally when suspending, cfg80211 will in fact
	 * deauthenticate. However, it करोesn't (and cannot) stop an ongoing
	 * auth (not so important) or assoc (this is the problem) process.
	 *
	 * As a consequence, it can happen that we are in the process of both
	 * associating and suspending, and receive an association response
	 * after cfg80211 has checked अगर it needs to disconnect, but beक्रमe
	 * we actually set the flag to drop incoming frames. This will then
	 * cause the workqueue flush to process the association response in
	 * the suspend, resulting in a successful association just beक्रमe it
	 * tries to हटाओ the पूर्णांकerface from the driver, which now though
	 * has a channel context asचिन्हित ... this results in issues.
	 *
	 * To work around this (क्रम now) simply deauth here again अगर we're
	 * now connected.
	 */
	अगर (अगरmgd->associated && !sdata->local->wowlan) अणु
		u8 bssid[ETH_ALEN];
		काष्ठा cfg80211_deauth_request req = अणु
			.reason_code = WLAN_REASON_DEAUTH_LEAVING,
			.bssid = bssid,
		पूर्ण;

		स_नकल(bssid, अगरmgd->associated->bssid, ETH_ALEN);
		ieee80211_mgd_deauth(sdata, &req);
	पूर्ण

	sdata_unlock(sdata);
पूर्ण

व्योम ieee80211_sta_restart(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	sdata_lock(sdata);
	अगर (!अगरmgd->associated) अणु
		sdata_unlock(sdata);
		वापस;
	पूर्ण

	अगर (sdata->flags & IEEE80211_SDATA_DISCONNECT_RESUME) अणु
		sdata->flags &= ~IEEE80211_SDATA_DISCONNECT_RESUME;
		mlme_dbg(sdata, "driver requested disconnect after resume\n");
		ieee80211_sta_connection_lost(sdata,
					      अगरmgd->associated->bssid,
					      WLAN_REASON_UNSPECIFIED,
					      true);
		sdata_unlock(sdata);
		वापस;
	पूर्ण
	sdata_unlock(sdata);
पूर्ण
#पूर्ण_अगर

/* पूर्णांकerface setup */
व्योम ieee80211_sta_setup_sdata(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd;

	अगरmgd = &sdata->u.mgd;
	INIT_WORK(&अगरmgd->monitor_work, ieee80211_sta_monitor_work);
	INIT_WORK(&अगरmgd->chचयन_work, ieee80211_chचयन_work);
	INIT_WORK(&अगरmgd->beacon_connection_loss_work,
		  ieee80211_beacon_connection_loss_work);
	INIT_WORK(&अगरmgd->csa_connection_drop_work,
		  ieee80211_csa_connection_drop_work);
	INIT_WORK(&अगरmgd->request_smps_work, ieee80211_request_smps_mgd_work);
	INIT_DELAYED_WORK(&अगरmgd->tdls_peer_del_work,
			  ieee80211_tdls_peer_del_work);
	समयr_setup(&अगरmgd->समयr, ieee80211_sta_समयr, 0);
	समयr_setup(&अगरmgd->bcn_mon_समयr, ieee80211_sta_bcn_mon_समयr, 0);
	समयr_setup(&अगरmgd->conn_mon_समयr, ieee80211_sta_conn_mon_समयr, 0);
	समयr_setup(&अगरmgd->chचयन_समयr, ieee80211_chचयन_समयr, 0);
	INIT_DELAYED_WORK(&अगरmgd->tx_tspec_wk,
			  ieee80211_sta_handle_tspec_ac_params_wk);

	अगरmgd->flags = 0;
	अगरmgd->घातersave = sdata->wdev.ps;
	अगरmgd->uapsd_queues = sdata->local->hw.uapsd_queues;
	अगरmgd->uapsd_max_sp_len = sdata->local->hw.uapsd_max_sp_len;
	अगरmgd->p2p_noa_index = -1;

	अगर (sdata->local->hw.wiphy->features & NL80211_FEATURE_DYNAMIC_SMPS)
		अगरmgd->req_smps = IEEE80211_SMPS_AUTOMATIC;
	अन्यथा
		अगरmgd->req_smps = IEEE80211_SMPS_OFF;

	/* Setup TDLS data */
	spin_lock_init(&अगरmgd->tearकरोwn_lock);
	अगरmgd->tearकरोwn_skb = शून्य;
	अगरmgd->orig_tearकरोwn_skb = शून्य;
पूर्ण

/* scan finished notअगरication */
व्योम ieee80211_mlme_notअगरy_scan_completed(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	/* Restart STA समयrs */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (ieee80211_sdata_running(sdata))
			ieee80211_restart_sta_समयr(sdata);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल u8 ieee80211_ht_vht_rx_chains(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा cfg80211_bss *cbss)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	स्थिर u8 *ht_cap_ie, *vht_cap_ie;
	स्थिर काष्ठा ieee80211_ht_cap *ht_cap;
	स्थिर काष्ठा ieee80211_vht_cap *vht_cap;
	u8 chains = 1;

	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_HT)
		वापस chains;

	ht_cap_ie = ieee80211_bss_get_ie(cbss, WLAN_EID_HT_CAPABILITY);
	अगर (ht_cap_ie && ht_cap_ie[1] >= माप(*ht_cap)) अणु
		ht_cap = (व्योम *)(ht_cap_ie + 2);
		chains = ieee80211_mcs_to_chains(&ht_cap->mcs);
		/*
		 * TODO: use "Tx Maximum Number Spatial Streams Supported" and
		 *	 "Tx Unequal Modulation Supported" fields.
		 */
	पूर्ण

	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_VHT)
		वापस chains;

	vht_cap_ie = ieee80211_bss_get_ie(cbss, WLAN_EID_VHT_CAPABILITY);
	अगर (vht_cap_ie && vht_cap_ie[1] >= माप(*vht_cap)) अणु
		u8 nss;
		u16 tx_mcs_map;

		vht_cap = (व्योम *)(vht_cap_ie + 2);
		tx_mcs_map = le16_to_cpu(vht_cap->supp_mcs.tx_mcs_map);
		क्रम (nss = 8; nss > 0; nss--) अणु
			अगर (((tx_mcs_map >> (2 * (nss - 1))) & 3) !=
					IEEE80211_VHT_MCS_NOT_SUPPORTED)
				अवरोध;
		पूर्ण
		/* TODO: use "Tx Highest Supported Long GI Data Rate" field? */
		chains = max(chains, nss);
	पूर्ण

	वापस chains;
पूर्ण

अटल bool
ieee80211_verअगरy_sta_he_mcs_support(काष्ठा ieee80211_supported_band *sband,
				    स्थिर काष्ठा ieee80211_he_operation *he_op)
अणु
	स्थिर काष्ठा ieee80211_sta_he_cap *sta_he_cap =
		ieee80211_get_he_sta_cap(sband);
	u16 ap_min_req_set;
	पूर्णांक i;

	अगर (!sta_he_cap || !he_op)
		वापस false;

	ap_min_req_set = le16_to_cpu(he_op->he_mcs_nss_set);

	/* Need to go over क्रम 80MHz, 160MHz and क्रम 80+80 */
	क्रम (i = 0; i < 3; i++) अणु
		स्थिर काष्ठा ieee80211_he_mcs_nss_supp *sta_mcs_nss_supp =
			&sta_he_cap->he_mcs_nss_supp;
		u16 sta_mcs_map_rx =
			le16_to_cpu(((__le16 *)sta_mcs_nss_supp)[2 * i]);
		u16 sta_mcs_map_tx =
			le16_to_cpu(((__le16 *)sta_mcs_nss_supp)[2 * i + 1]);
		u8 nss;
		bool verअगरied = true;

		/*
		 * For each band there is a maximum of 8 spatial streams
		 * possible. Each of the sta_mcs_map_* is a 16-bit काष्ठा built
		 * of 2 bits per NSS (1-8), with the values defined in क्रमागत
		 * ieee80211_he_mcs_support. Need to make sure STA TX and RX
		 * capabilities aren't less than the AP's minimum requirements
		 * क्रम this HE BSS per SS.
		 * It is enough to find one such band that meets the reqs.
		 */
		क्रम (nss = 8; nss > 0; nss--) अणु
			u8 sta_rx_val = (sta_mcs_map_rx >> (2 * (nss - 1))) & 3;
			u8 sta_tx_val = (sta_mcs_map_tx >> (2 * (nss - 1))) & 3;
			u8 ap_val = (ap_min_req_set >> (2 * (nss - 1))) & 3;

			अगर (ap_val == IEEE80211_HE_MCS_NOT_SUPPORTED)
				जारी;

			/*
			 * Make sure the HE AP करोesn't require MCSs that aren't
			 * supported by the client
			 */
			अगर (sta_rx_val == IEEE80211_HE_MCS_NOT_SUPPORTED ||
			    sta_tx_val == IEEE80211_HE_MCS_NOT_SUPPORTED ||
			    (ap_val > sta_rx_val) || (ap_val > sta_tx_val)) अणु
				verअगरied = false;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (verअगरied)
			वापस true;
	पूर्ण

	/* If here, STA करोesn't meet AP's HE min requirements */
	वापस false;
पूर्ण

अटल पूर्णांक ieee80211_prep_channel(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा cfg80211_bss *cbss)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	स्थिर काष्ठा ieee80211_ht_cap *ht_cap = शून्य;
	स्थिर काष्ठा ieee80211_ht_operation *ht_oper = शून्य;
	स्थिर काष्ठा ieee80211_vht_operation *vht_oper = शून्य;
	स्थिर काष्ठा ieee80211_he_operation *he_oper = शून्य;
	स्थिर काष्ठा ieee80211_s1g_oper_ie *s1g_oper = शून्य;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा cfg80211_chan_def chandef;
	bool is_6ghz = cbss->channel->band == NL80211_BAND_6GHZ;
	bool is_5ghz = cbss->channel->band == NL80211_BAND_5GHZ;
	काष्ठा ieee80211_bss *bss = (व्योम *)cbss->priv;
	पूर्णांक ret;
	u32 i;
	bool have_80mhz;

	sband = local->hw.wiphy->bands[cbss->channel->band];

	अगरmgd->flags &= ~(IEEE80211_STA_DISABLE_40MHZ |
			  IEEE80211_STA_DISABLE_80P80MHZ |
			  IEEE80211_STA_DISABLE_160MHZ);

	/* disable HT/VHT/HE अगर we करोn't support them */
	अगर (!sband->ht_cap.ht_supported && !is_6ghz) अणु
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HT;
		अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT;
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HE;
	पूर्ण

	अगर (!sband->vht_cap.vht_supported && is_5ghz) अणु
		अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT;
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HE;
	पूर्ण

	अगर (!ieee80211_get_he_sta_cap(sband))
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HE;

	rcu_पढ़ो_lock();

	अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_HT) && !is_6ghz) अणु
		स्थिर u8 *ht_oper_ie, *ht_cap_ie;

		ht_oper_ie = ieee80211_bss_get_ie(cbss, WLAN_EID_HT_OPERATION);
		अगर (ht_oper_ie && ht_oper_ie[1] >= माप(*ht_oper))
			ht_oper = (व्योम *)(ht_oper_ie + 2);

		ht_cap_ie = ieee80211_bss_get_ie(cbss, WLAN_EID_HT_CAPABILITY);
		अगर (ht_cap_ie && ht_cap_ie[1] >= माप(*ht_cap))
			ht_cap = (व्योम *)(ht_cap_ie + 2);

		अगर (!ht_cap) अणु
			अगरmgd->flags |= IEEE80211_STA_DISABLE_HT;
			ht_oper = शून्य;
		पूर्ण
	पूर्ण

	अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT) && !is_6ghz) अणु
		स्थिर u8 *vht_oper_ie, *vht_cap;

		vht_oper_ie = ieee80211_bss_get_ie(cbss,
						   WLAN_EID_VHT_OPERATION);
		अगर (vht_oper_ie && vht_oper_ie[1] >= माप(*vht_oper))
			vht_oper = (व्योम *)(vht_oper_ie + 2);
		अगर (vht_oper && !ht_oper) अणु
			vht_oper = शून्य;
			sdata_info(sdata,
				   "AP advertised VHT without HT, disabling HT/VHT/HE\n");
			अगरmgd->flags |= IEEE80211_STA_DISABLE_HT;
			अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT;
			अगरmgd->flags |= IEEE80211_STA_DISABLE_HE;
		पूर्ण

		vht_cap = ieee80211_bss_get_ie(cbss, WLAN_EID_VHT_CAPABILITY);
		अगर (!vht_cap || vht_cap[1] < माप(काष्ठा ieee80211_vht_cap)) अणु
			अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT;
			vht_oper = शून्य;
		पूर्ण
	पूर्ण

	अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_HE)) अणु
		स्थिर काष्ठा cfg80211_bss_ies *ies;
		स्थिर u8 *he_oper_ie;

		ies = rcu_dereference(cbss->ies);
		he_oper_ie = cfg80211_find_ext_ie(WLAN_EID_EXT_HE_OPERATION,
						  ies->data, ies->len);
		अगर (he_oper_ie &&
		    he_oper_ie[1] >= ieee80211_he_oper_size(&he_oper_ie[3]))
			he_oper = (व्योम *)(he_oper_ie + 3);
		अन्यथा
			he_oper = शून्य;

		अगर (!ieee80211_verअगरy_sta_he_mcs_support(sband, he_oper))
			अगरmgd->flags |= IEEE80211_STA_DISABLE_HE;
	पूर्ण

	/* Allow VHT अगर at least one channel on the sband supports 80 MHz */
	have_80mhz = false;
	क्रम (i = 0; i < sband->n_channels; i++) अणु
		अगर (sband->channels[i].flags & (IEEE80211_CHAN_DISABLED |
						IEEE80211_CHAN_NO_80MHZ))
			जारी;

		have_80mhz = true;
		अवरोध;
	पूर्ण

	अगर (!have_80mhz)
		अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT;

	अगर (sband->band == NL80211_BAND_S1GHZ) अणु
		स्थिर u8 *s1g_oper_ie;

		s1g_oper_ie = ieee80211_bss_get_ie(cbss,
						   WLAN_EID_S1G_OPERATION);
		अगर (s1g_oper_ie && s1g_oper_ie[1] >= माप(*s1g_oper))
			s1g_oper = (व्योम *)(s1g_oper_ie + 2);
		अन्यथा
			sdata_info(sdata,
				   "AP missing S1G operation element?\n");
	पूर्ण

	अगरmgd->flags |= ieee80211_determine_chantype(sdata, sband,
						     cbss->channel,
						     bss->vht_cap_info,
						     ht_oper, vht_oper, he_oper,
						     s1g_oper,
						     &chandef, false);

	sdata->needed_rx_chains = min(ieee80211_ht_vht_rx_chains(sdata, cbss),
				      local->rx_chains);

	rcu_पढ़ो_unlock();

	अगर (अगरmgd->flags & IEEE80211_STA_DISABLE_HE && is_6ghz) अणु
		sdata_info(sdata, "Rejecting non-HE 6/7 GHz connection");
		वापस -EINVAL;
	पूर्ण

	/* will change later अगर needed */
	sdata->smps_mode = IEEE80211_SMPS_OFF;

	mutex_lock(&local->mtx);
	/*
	 * If this fails (possibly due to channel context sharing
	 * on incompatible channels, e.g. 80+80 and 160 sharing the
	 * same control channel) try to use a smaller bandwidth.
	 */
	ret = ieee80211_vअगर_use_channel(sdata, &chandef,
					IEEE80211_CHANCTX_SHARED);

	/* करोn't करोwngrade क्रम 5 and 10 MHz channels, though. */
	अगर (chandef.width == NL80211_CHAN_WIDTH_5 ||
	    chandef.width == NL80211_CHAN_WIDTH_10)
		जाओ out;

	जबतक (ret && chandef.width != NL80211_CHAN_WIDTH_20_NOHT) अणु
		अगरmgd->flags |= ieee80211_chandef_करोwngrade(&chandef);
		ret = ieee80211_vअगर_use_channel(sdata, &chandef,
						IEEE80211_CHANCTX_SHARED);
	पूर्ण
 out:
	mutex_unlock(&local->mtx);
	वापस ret;
पूर्ण

अटल bool ieee80211_get_dtim(स्थिर काष्ठा cfg80211_bss_ies *ies,
			       u8 *dtim_count, u8 *dtim_period)
अणु
	स्थिर u8 *tim_ie = cfg80211_find_ie(WLAN_EID_TIM, ies->data, ies->len);
	स्थिर u8 *idx_ie = cfg80211_find_ie(WLAN_EID_MULTI_BSSID_IDX, ies->data,
					 ies->len);
	स्थिर काष्ठा ieee80211_tim_ie *tim = शून्य;
	स्थिर काष्ठा ieee80211_bssid_index *idx;
	bool valid = tim_ie && tim_ie[1] >= 2;

	अगर (valid)
		tim = (व्योम *)(tim_ie + 2);

	अगर (dtim_count)
		*dtim_count = valid ? tim->dtim_count : 0;

	अगर (dtim_period)
		*dtim_period = valid ? tim->dtim_period : 0;

	/* Check अगर value is overridden by non-transmitted profile */
	अगर (!idx_ie || idx_ie[1] < 3)
		वापस valid;

	idx = (व्योम *)(idx_ie + 2);

	अगर (dtim_count)
		*dtim_count = idx->dtim_count;

	अगर (dtim_period)
		*dtim_period = idx->dtim_period;

	वापस true;
पूर्ण

अटल पूर्णांक ieee80211_prep_connection(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा cfg80211_bss *cbss, bool assoc,
				     bool override)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_bss *bss = (व्योम *)cbss->priv;
	काष्ठा sta_info *new_sta = शून्य;
	काष्ठा ieee80211_supported_band *sband;
	bool have_sta = false;
	पूर्णांक err;

	sband = local->hw.wiphy->bands[cbss->channel->band];

	अगर (WARN_ON(!अगरmgd->auth_data && !अगरmgd->assoc_data))
		वापस -EINVAL;

	/* If a reconfig is happening, bail out */
	अगर (local->in_reconfig)
		वापस -EBUSY;

	अगर (assoc) अणु
		rcu_पढ़ो_lock();
		have_sta = sta_info_get(sdata, cbss->bssid);
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (!have_sta) अणु
		new_sta = sta_info_alloc(sdata, cbss->bssid, GFP_KERNEL);
		अगर (!new_sta)
			वापस -ENOMEM;
	पूर्ण

	/*
	 * Set up the inक्रमmation क्रम the new channel beक्रमe setting the
	 * new channel. We can't - completely race-मुक्त - change the basic
	 * rates biपंचांगap and the channel (sband) that it refers to, but अगर
	 * we set it up beक्रमe we at least aव्योम calling पूर्णांकo the driver's
	 * bss_info_changed() method with invalid inक्रमmation (since we करो
	 * call that from changing the channel - only क्रम IDLE and perhaps
	 * some others, but ...).
	 *
	 * So to aव्योम that, just set up all the new inक्रमmation beक्रमe the
	 * channel, but tell the driver to apply it only afterwards, since
	 * it might need the new channel क्रम that.
	 */
	अगर (new_sta) अणु
		u32 rates = 0, basic_rates = 0;
		bool have_higher_than_11mbit;
		पूर्णांक min_rate = पूर्णांक_उच्च, min_rate_index = -1;
		स्थिर काष्ठा cfg80211_bss_ies *ies;
		पूर्णांक shअगरt = ieee80211_vअगर_get_shअगरt(&sdata->vअगर);

		/* TODO: S1G Basic Rate Set is expressed अन्यथाwhere */
		अगर (cbss->channel->band == NL80211_BAND_S1GHZ) अणु
			ieee80211_s1g_sta_rate_init(new_sta);
			जाओ skip_rates;
		पूर्ण

		ieee80211_get_rates(sband, bss->supp_rates,
				    bss->supp_rates_len,
				    &rates, &basic_rates,
				    &have_higher_than_11mbit,
				    &min_rate, &min_rate_index,
				    shअगरt);

		/*
		 * This used to be a workaround क्रम basic rates missing
		 * in the association response frame. Now that we no
		 * दीर्घer use the basic rates from there, it probably
		 * करोesn't happen any more, but keep the workaround so
		 * in हाल some *other* APs are buggy in dअगरferent ways
		 * we can connect -- with a warning.
		 * Allow this workaround only in हाल the AP provided at least
		 * one rate.
		 */
		अगर (min_rate_index < 0) अणु
			sdata_info(sdata,
				   "No legacy rates in association response\n");

			sta_info_मुक्त(local, new_sta);
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (!basic_rates) अणु
			sdata_info(sdata,
				   "No basic rates, using min rate instead\n");
			basic_rates = BIT(min_rate_index);
		पूर्ण

		अगर (rates)
			new_sta->sta.supp_rates[cbss->channel->band] = rates;
		अन्यथा
			sdata_info(sdata,
				   "No rates found, keeping mandatory only\n");

		sdata->vअगर.bss_conf.basic_rates = basic_rates;

		/* cf. IEEE 802.11 9.2.12 */
		अगर (cbss->channel->band == NL80211_BAND_2GHZ &&
		    have_higher_than_11mbit)
			sdata->flags |= IEEE80211_SDATA_OPERATING_GMODE;
		अन्यथा
			sdata->flags &= ~IEEE80211_SDATA_OPERATING_GMODE;

skip_rates:
		स_नकल(अगरmgd->bssid, cbss->bssid, ETH_ALEN);

		/* set timing inक्रमmation */
		sdata->vअगर.bss_conf.beacon_पूर्णांक = cbss->beacon_पूर्णांकerval;
		rcu_पढ़ो_lock();
		ies = rcu_dereference(cbss->beacon_ies);
		अगर (ies) अणु
			sdata->vअगर.bss_conf.sync_tsf = ies->tsf;
			sdata->vअगर.bss_conf.sync_device_ts =
				bss->device_ts_beacon;

			ieee80211_get_dtim(ies,
					   &sdata->vअगर.bss_conf.sync_dtim_count,
					   शून्य);
		पूर्ण अन्यथा अगर (!ieee80211_hw_check(&sdata->local->hw,
					       TIMING_BEACON_ONLY)) अणु
			ies = rcu_dereference(cbss->proberesp_ies);
			/* must be non-शून्य since beacon IEs were शून्य */
			sdata->vअगर.bss_conf.sync_tsf = ies->tsf;
			sdata->vअगर.bss_conf.sync_device_ts =
				bss->device_ts_presp;
			sdata->vअगर.bss_conf.sync_dtim_count = 0;
		पूर्ण अन्यथा अणु
			sdata->vअगर.bss_conf.sync_tsf = 0;
			sdata->vअगर.bss_conf.sync_device_ts = 0;
			sdata->vअगर.bss_conf.sync_dtim_count = 0;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (new_sta || override) अणु
		err = ieee80211_prep_channel(sdata, cbss);
		अगर (err) अणु
			अगर (new_sta)
				sta_info_मुक्त(local, new_sta);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (new_sta) अणु
		/*
		 * tell driver about BSSID, basic rates and timing
		 * this was set up above, beक्रमe setting the channel
		 */
		ieee80211_bss_info_change_notअगरy(sdata,
			BSS_CHANGED_BSSID | BSS_CHANGED_BASIC_RATES |
			BSS_CHANGED_BEACON_INT);

		अगर (assoc)
			sta_info_pre_move_state(new_sta, IEEE80211_STA_AUTH);

		err = sta_info_insert(new_sta);
		new_sta = शून्य;
		अगर (err) अणु
			sdata_info(sdata,
				   "failed to insert STA entry for the AP (error %d)\n",
				   err);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा
		WARN_ON_ONCE(!ether_addr_equal(अगरmgd->bssid, cbss->bssid));

	/* Cancel scan to ensure that nothing पूर्णांकerferes with connection */
	अगर (local->scanning)
		ieee80211_scan_cancel(local);

	वापस 0;
पूर्ण

/* config hooks */
पूर्णांक ieee80211_mgd_auth(काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा cfg80211_auth_request *req)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_mgd_auth_data *auth_data;
	u16 auth_alg;
	पूर्णांक err;
	bool cont_auth;

	/* prepare auth data काष्ठाure */

	चयन (req->auth_type) अणु
	हाल NL80211_AUTHTYPE_OPEN_SYSTEM:
		auth_alg = WLAN_AUTH_OPEN;
		अवरोध;
	हाल NL80211_AUTHTYPE_SHARED_KEY:
		अगर (fips_enabled)
			वापस -EOPNOTSUPP;
		auth_alg = WLAN_AUTH_SHARED_KEY;
		अवरोध;
	हाल NL80211_AUTHTYPE_FT:
		auth_alg = WLAN_AUTH_FT;
		अवरोध;
	हाल NL80211_AUTHTYPE_NETWORK_EAP:
		auth_alg = WLAN_AUTH_LEAP;
		अवरोध;
	हाल NL80211_AUTHTYPE_SAE:
		auth_alg = WLAN_AUTH_SAE;
		अवरोध;
	हाल NL80211_AUTHTYPE_FILS_SK:
		auth_alg = WLAN_AUTH_FILS_SK;
		अवरोध;
	हाल NL80211_AUTHTYPE_FILS_SK_PFS:
		auth_alg = WLAN_AUTH_FILS_SK_PFS;
		अवरोध;
	हाल NL80211_AUTHTYPE_FILS_PK:
		auth_alg = WLAN_AUTH_FILS_PK;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (अगरmgd->assoc_data)
		वापस -EBUSY;

	auth_data = kzalloc(माप(*auth_data) + req->auth_data_len +
			    req->ie_len, GFP_KERNEL);
	अगर (!auth_data)
		वापस -ENOMEM;

	auth_data->bss = req->bss;

	अगर (req->auth_data_len >= 4) अणु
		अगर (req->auth_type == NL80211_AUTHTYPE_SAE) अणु
			__le16 *pos = (__le16 *) req->auth_data;

			auth_data->sae_trans = le16_to_cpu(pos[0]);
			auth_data->sae_status = le16_to_cpu(pos[1]);
		पूर्ण
		स_नकल(auth_data->data, req->auth_data + 4,
		       req->auth_data_len - 4);
		auth_data->data_len += req->auth_data_len - 4;
	पूर्ण

	/* Check अगर continuing authentication or trying to authenticate with the
	 * same BSS that we were in the process of authenticating with and aव्योम
	 * removal and re-addition of the STA entry in
	 * ieee80211_prep_connection().
	 */
	cont_auth = अगरmgd->auth_data && req->bss == अगरmgd->auth_data->bss;

	अगर (req->ie && req->ie_len) अणु
		स_नकल(&auth_data->data[auth_data->data_len],
		       req->ie, req->ie_len);
		auth_data->data_len += req->ie_len;
	पूर्ण

	अगर (req->key && req->key_len) अणु
		auth_data->key_len = req->key_len;
		auth_data->key_idx = req->key_idx;
		स_नकल(auth_data->key, req->key, req->key_len);
	पूर्ण

	auth_data->algorithm = auth_alg;

	/* try to authenticate/probe */

	अगर (अगरmgd->auth_data) अणु
		अगर (cont_auth && req->auth_type == NL80211_AUTHTYPE_SAE) अणु
			auth_data->peer_confirmed =
				अगरmgd->auth_data->peer_confirmed;
		पूर्ण
		ieee80211_destroy_auth_data(sdata, cont_auth);
	पूर्ण

	/* prep auth_data so we करोn't go पूर्णांकo idle on disassoc */
	अगरmgd->auth_data = auth_data;

	/* If this is continuation of an ongoing SAE authentication exchange
	 * (i.e., request to send SAE Confirm) and the peer has alपढ़ोy
	 * confirmed, mark authentication completed since we are about to send
	 * out SAE Confirm.
	 */
	अगर (cont_auth && req->auth_type == NL80211_AUTHTYPE_SAE &&
	    auth_data->peer_confirmed && auth_data->sae_trans == 2)
		ieee80211_mark_sta_auth(sdata, req->bss->bssid);

	अगर (अगरmgd->associated) अणु
		u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];

		sdata_info(sdata,
			   "disconnect from AP %pM for new auth to %pM\n",
			   अगरmgd->associated->bssid, req->bss->bssid);
		ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH,
				       WLAN_REASON_UNSPECIFIED,
				       false, frame_buf);

		ieee80211_report_disconnect(sdata, frame_buf,
					    माप(frame_buf), true,
					    WLAN_REASON_UNSPECIFIED,
					    false);
	पूर्ण

	sdata_info(sdata, "authenticate with %pM\n", req->bss->bssid);

	err = ieee80211_prep_connection(sdata, req->bss, cont_auth, false);
	अगर (err)
		जाओ err_clear;

	err = ieee80211_auth(sdata);
	अगर (err) अणु
		sta_info_destroy_addr(sdata, req->bss->bssid);
		जाओ err_clear;
	पूर्ण

	/* hold our own reference */
	cfg80211_ref_bss(local->hw.wiphy, auth_data->bss);
	वापस 0;

 err_clear:
	eth_zero_addr(अगरmgd->bssid);
	ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_BSSID);
	अगरmgd->auth_data = शून्य;
	mutex_lock(&sdata->local->mtx);
	ieee80211_vअगर_release_channel(sdata);
	mutex_unlock(&sdata->local->mtx);
	kमुक्त(auth_data);
	वापस err;
पूर्ण

पूर्णांक ieee80211_mgd_assoc(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा cfg80211_assoc_request *req)
अणु
	bool is_6ghz = req->bss->channel->band == NL80211_BAND_6GHZ;
	bool is_5ghz = req->bss->channel->band == NL80211_BAND_5GHZ;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_bss *bss = (व्योम *)req->bss->priv;
	काष्ठा ieee80211_mgd_assoc_data *assoc_data;
	स्थिर काष्ठा cfg80211_bss_ies *beacon_ies;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_bss_conf *bss_conf = &sdata->vअगर.bss_conf;
	स्थिर u8 *ssidie, *ht_ie, *vht_ie;
	पूर्णांक i, err;
	bool override = false;

	assoc_data = kzalloc(माप(*assoc_data) + req->ie_len, GFP_KERNEL);
	अगर (!assoc_data)
		वापस -ENOMEM;

	rcu_पढ़ो_lock();
	ssidie = ieee80211_bss_get_ie(req->bss, WLAN_EID_SSID);
	अगर (!ssidie || ssidie[1] > माप(assoc_data->ssid)) अणु
		rcu_पढ़ो_unlock();
		kमुक्त(assoc_data);
		वापस -EINVAL;
	पूर्ण
	स_नकल(assoc_data->ssid, ssidie + 2, ssidie[1]);
	assoc_data->ssid_len = ssidie[1];
	स_नकल(bss_conf->ssid, assoc_data->ssid, assoc_data->ssid_len);
	bss_conf->ssid_len = assoc_data->ssid_len;
	rcu_पढ़ो_unlock();

	अगर (अगरmgd->associated) अणु
		u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];

		sdata_info(sdata,
			   "disconnect from AP %pM for new assoc to %pM\n",
			   अगरmgd->associated->bssid, req->bss->bssid);
		ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH,
				       WLAN_REASON_UNSPECIFIED,
				       false, frame_buf);

		ieee80211_report_disconnect(sdata, frame_buf,
					    माप(frame_buf), true,
					    WLAN_REASON_UNSPECIFIED,
					    false);
	पूर्ण

	अगर (अगरmgd->auth_data && !अगरmgd->auth_data->करोne) अणु
		err = -EBUSY;
		जाओ err_मुक्त;
	पूर्ण

	अगर (अगरmgd->assoc_data) अणु
		err = -EBUSY;
		जाओ err_मुक्त;
	पूर्ण

	अगर (अगरmgd->auth_data) अणु
		bool match;

		/* keep sta info, bssid अगर matching */
		match = ether_addr_equal(अगरmgd->bssid, req->bss->bssid);
		ieee80211_destroy_auth_data(sdata, match);
	पूर्ण

	/* prepare assoc data */

	अगरmgd->beacon_crc_valid = false;

	assoc_data->wmm = bss->wmm_used &&
			  (local->hw.queues >= IEEE80211_NUM_ACS);

	/*
	 * IEEE802.11n करोes not allow TKIP/WEP as pairwise ciphers in HT mode.
	 * We still associate in non-HT mode (11a/b/g) अगर any one of these
	 * ciphers is configured as pairwise.
	 * We can set this to true क्रम non-11n hardware, that'll be checked
	 * separately aदीर्घ with the peer capabilities.
	 */
	क्रम (i = 0; i < req->crypto.n_ciphers_pairwise; i++) अणु
		अगर (req->crypto.ciphers_pairwise[i] == WLAN_CIPHER_SUITE_WEP40 ||
		    req->crypto.ciphers_pairwise[i] == WLAN_CIPHER_SUITE_TKIP ||
		    req->crypto.ciphers_pairwise[i] == WLAN_CIPHER_SUITE_WEP104) अणु
			अगरmgd->flags |= IEEE80211_STA_DISABLE_HT;
			अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT;
			अगरmgd->flags |= IEEE80211_STA_DISABLE_HE;
			netdev_info(sdata->dev,
				    "disabling HT/VHT/HE due to WEP/TKIP use\n");
		पूर्ण
	पूर्ण

	sband = local->hw.wiphy->bands[req->bss->channel->band];

	/* also disable HT/VHT/HE अगर the AP करोesn't use WMM */
	अगर (!bss->wmm_used) अणु
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HT;
		अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT;
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HE;
		netdev_info(sdata->dev,
			    "disabling HT/VHT/HE as WMM/QoS is not supported by the AP\n");
	पूर्ण

	स_नकल(&अगरmgd->ht_capa, &req->ht_capa, माप(अगरmgd->ht_capa));
	स_नकल(&अगरmgd->ht_capa_mask, &req->ht_capa_mask,
	       माप(अगरmgd->ht_capa_mask));

	स_नकल(&अगरmgd->vht_capa, &req->vht_capa, माप(अगरmgd->vht_capa));
	स_नकल(&अगरmgd->vht_capa_mask, &req->vht_capa_mask,
	       माप(अगरmgd->vht_capa_mask));

	स_नकल(&अगरmgd->s1g_capa, &req->s1g_capa, माप(अगरmgd->s1g_capa));
	स_नकल(&अगरmgd->s1g_capa_mask, &req->s1g_capa_mask,
	       माप(अगरmgd->s1g_capa_mask));

	अगर (req->ie && req->ie_len) अणु
		स_नकल(assoc_data->ie, req->ie, req->ie_len);
		assoc_data->ie_len = req->ie_len;
	पूर्ण

	अगर (req->fils_kek) अणु
		/* should alपढ़ोy be checked in cfg80211 - so warn */
		अगर (WARN_ON(req->fils_kek_len > FILS_MAX_KEK_LEN)) अणु
			err = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण
		स_नकल(assoc_data->fils_kek, req->fils_kek,
		       req->fils_kek_len);
		assoc_data->fils_kek_len = req->fils_kek_len;
	पूर्ण

	अगर (req->fils_nonces)
		स_नकल(assoc_data->fils_nonces, req->fils_nonces,
		       2 * FILS_NONCE_LEN);

	assoc_data->bss = req->bss;

	अगर (अगरmgd->req_smps == IEEE80211_SMPS_AUTOMATIC) अणु
		अगर (अगरmgd->घातersave)
			sdata->smps_mode = IEEE80211_SMPS_DYNAMIC;
		अन्यथा
			sdata->smps_mode = IEEE80211_SMPS_OFF;
	पूर्ण अन्यथा
		sdata->smps_mode = अगरmgd->req_smps;

	assoc_data->capability = req->bss->capability;
	assoc_data->supp_rates = bss->supp_rates;
	assoc_data->supp_rates_len = bss->supp_rates_len;

	rcu_पढ़ो_lock();
	ht_ie = ieee80211_bss_get_ie(req->bss, WLAN_EID_HT_OPERATION);
	अगर (ht_ie && ht_ie[1] >= माप(काष्ठा ieee80211_ht_operation))
		assoc_data->ap_ht_param =
			((काष्ठा ieee80211_ht_operation *)(ht_ie + 2))->ht_param;
	अन्यथा अगर (!is_6ghz)
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HT;
	vht_ie = ieee80211_bss_get_ie(req->bss, WLAN_EID_VHT_CAPABILITY);
	अगर (vht_ie && vht_ie[1] >= माप(काष्ठा ieee80211_vht_cap))
		स_नकल(&assoc_data->ap_vht_cap, vht_ie + 2,
		       माप(काष्ठा ieee80211_vht_cap));
	अन्यथा अगर (is_5ghz)
		अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT |
				IEEE80211_STA_DISABLE_HE;
	rcu_पढ़ो_unlock();

	अगर (WARN((sdata->vअगर.driver_flags & IEEE80211_VIF_SUPPORTS_UAPSD) &&
		 ieee80211_hw_check(&local->hw, PS_शून्यFUNC_STACK),
	     "U-APSD not supported with HW_PS_NULLFUNC_STACK\n"))
		sdata->vअगर.driver_flags &= ~IEEE80211_VIF_SUPPORTS_UAPSD;

	अगर (bss->wmm_used && bss->uapsd_supported &&
	    (sdata->vअगर.driver_flags & IEEE80211_VIF_SUPPORTS_UAPSD)) अणु
		assoc_data->uapsd = true;
		अगरmgd->flags |= IEEE80211_STA_UAPSD_ENABLED;
	पूर्ण अन्यथा अणु
		assoc_data->uapsd = false;
		अगरmgd->flags &= ~IEEE80211_STA_UAPSD_ENABLED;
	पूर्ण

	अगर (req->prev_bssid)
		स_नकल(assoc_data->prev_bssid, req->prev_bssid, ETH_ALEN);

	अगर (req->use_mfp) अणु
		अगरmgd->mfp = IEEE80211_MFP_REQUIRED;
		अगरmgd->flags |= IEEE80211_STA_MFP_ENABLED;
	पूर्ण अन्यथा अणु
		अगरmgd->mfp = IEEE80211_MFP_DISABLED;
		अगरmgd->flags &= ~IEEE80211_STA_MFP_ENABLED;
	पूर्ण

	अगर (req->flags & ASSOC_REQ_USE_RRM)
		अगरmgd->flags |= IEEE80211_STA_ENABLE_RRM;
	अन्यथा
		अगरmgd->flags &= ~IEEE80211_STA_ENABLE_RRM;

	अगर (req->crypto.control_port)
		अगरmgd->flags |= IEEE80211_STA_CONTROL_PORT;
	अन्यथा
		अगरmgd->flags &= ~IEEE80211_STA_CONTROL_PORT;

	sdata->control_port_protocol = req->crypto.control_port_ethertype;
	sdata->control_port_no_encrypt = req->crypto.control_port_no_encrypt;
	sdata->control_port_over_nl80211 =
					req->crypto.control_port_over_nl80211;
	sdata->control_port_no_preauth = req->crypto.control_port_no_preauth;
	sdata->encrypt_headroom = ieee80211_cs_headroom(local, &req->crypto,
							sdata->vअगर.type);

	/* kick off associate process */

	अगरmgd->assoc_data = assoc_data;
	अगरmgd->dtim_period = 0;
	अगरmgd->have_beacon = false;

	/* override HT/VHT configuration only अगर the AP and we support it */
	अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_HT)) अणु
		काष्ठा ieee80211_sta_ht_cap sta_ht_cap;

		अगर (req->flags & ASSOC_REQ_DISABLE_HT)
			override = true;

		स_नकल(&sta_ht_cap, &sband->ht_cap, माप(sta_ht_cap));
		ieee80211_apply_htcap_overrides(sdata, &sta_ht_cap);

		/* check क्रम 40 MHz disable override */
		अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_40MHZ) &&
		    sband->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 &&
		    !(sta_ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40))
			override = true;

		अगर (!(अगरmgd->flags & IEEE80211_STA_DISABLE_VHT) &&
		    req->flags & ASSOC_REQ_DISABLE_VHT)
			override = true;
	पूर्ण

	अगर (req->flags & ASSOC_REQ_DISABLE_HT) अणु
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HT;
		अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT;
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HE;
	पूर्ण

	अगर (req->flags & ASSOC_REQ_DISABLE_VHT)
		अगरmgd->flags |= IEEE80211_STA_DISABLE_VHT;

	अगर (req->flags & ASSOC_REQ_DISABLE_HE)
		अगरmgd->flags |= IEEE80211_STA_DISABLE_HE;

	err = ieee80211_prep_connection(sdata, req->bss, true, override);
	अगर (err)
		जाओ err_clear;

	rcu_पढ़ो_lock();
	beacon_ies = rcu_dereference(req->bss->beacon_ies);

	अगर (ieee80211_hw_check(&sdata->local->hw, NEED_DTIM_BEFORE_ASSOC) &&
	    !beacon_ies) अणु
		/*
		 * Wait up to one beacon पूर्णांकerval ...
		 * should this be more अगर we miss one?
		 */
		sdata_info(sdata, "waiting for beacon from %pM\n",
			   अगरmgd->bssid);
		assoc_data->समयout = TU_TO_EXP_TIME(req->bss->beacon_पूर्णांकerval);
		assoc_data->समयout_started = true;
		assoc_data->need_beacon = true;
	पूर्ण अन्यथा अगर (beacon_ies) अणु
		स्थिर काष्ठा element *elem;
		u8 dtim_count = 0;

		ieee80211_get_dtim(beacon_ies, &dtim_count,
				   &अगरmgd->dtim_period);

		अगरmgd->have_beacon = true;
		assoc_data->समयout = jअगरfies;
		assoc_data->समयout_started = true;

		अगर (ieee80211_hw_check(&local->hw, TIMING_BEACON_ONLY)) अणु
			sdata->vअगर.bss_conf.sync_tsf = beacon_ies->tsf;
			sdata->vअगर.bss_conf.sync_device_ts =
				bss->device_ts_beacon;
			sdata->vअगर.bss_conf.sync_dtim_count = dtim_count;
		पूर्ण

		elem = cfg80211_find_ext_elem(WLAN_EID_EXT_MULTIPLE_BSSID_CONFIGURATION,
					      beacon_ies->data, beacon_ies->len);
		अगर (elem && elem->datalen >= 3)
			sdata->vअगर.bss_conf.profile_periodicity = elem->data[2];
		अन्यथा
			sdata->vअगर.bss_conf.profile_periodicity = 0;

		elem = cfg80211_find_elem(WLAN_EID_EXT_CAPABILITY,
					  beacon_ies->data, beacon_ies->len);
		अगर (elem && elem->datalen >= 11 &&
		    (elem->data[10] & WLAN_EXT_CAPA11_EMA_SUPPORT))
			sdata->vअगर.bss_conf.ema_ap = true;
		अन्यथा
			sdata->vअगर.bss_conf.ema_ap = false;
	पूर्ण अन्यथा अणु
		assoc_data->समयout = jअगरfies;
		assoc_data->समयout_started = true;
	पूर्ण
	rcu_पढ़ो_unlock();

	run_again(sdata, assoc_data->समयout);

	अगर (bss->corrupt_data) अणु
		अक्षर *corrupt_type = "data";
		अगर (bss->corrupt_data & IEEE80211_BSS_CORRUPT_BEACON) अणु
			अगर (bss->corrupt_data &
					IEEE80211_BSS_CORRUPT_PROBE_RESP)
				corrupt_type = "beacon and probe response";
			अन्यथा
				corrupt_type = "beacon";
		पूर्ण अन्यथा अगर (bss->corrupt_data & IEEE80211_BSS_CORRUPT_PROBE_RESP)
			corrupt_type = "probe response";
		sdata_info(sdata, "associating with AP with corrupt %s\n",
			   corrupt_type);
	पूर्ण

	वापस 0;
 err_clear:
	eth_zero_addr(अगरmgd->bssid);
	ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_BSSID);
	अगरmgd->assoc_data = शून्य;
 err_मुक्त:
	kमुक्त(assoc_data);
	वापस err;
पूर्ण

पूर्णांक ieee80211_mgd_deauth(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा cfg80211_deauth_request *req)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];
	bool tx = !req->local_state_change;

	अगर (अगरmgd->auth_data &&
	    ether_addr_equal(अगरmgd->auth_data->bss->bssid, req->bssid)) अणु
		sdata_info(sdata,
			   "aborting authentication with %pM by local choice (Reason: %u=%s)\n",
			   req->bssid, req->reason_code,
			   ieee80211_get_reason_code_string(req->reason_code));

		drv_mgd_prepare_tx(sdata->local, sdata, 0);
		ieee80211_send_deauth_disassoc(sdata, req->bssid, req->bssid,
					       IEEE80211_STYPE_DEAUTH,
					       req->reason_code, tx,
					       frame_buf);
		ieee80211_destroy_auth_data(sdata, false);
		ieee80211_report_disconnect(sdata, frame_buf,
					    माप(frame_buf), true,
					    req->reason_code, false);

		वापस 0;
	पूर्ण

	अगर (अगरmgd->assoc_data &&
	    ether_addr_equal(अगरmgd->assoc_data->bss->bssid, req->bssid)) अणु
		sdata_info(sdata,
			   "aborting association with %pM by local choice (Reason: %u=%s)\n",
			   req->bssid, req->reason_code,
			   ieee80211_get_reason_code_string(req->reason_code));

		drv_mgd_prepare_tx(sdata->local, sdata, 0);
		ieee80211_send_deauth_disassoc(sdata, req->bssid, req->bssid,
					       IEEE80211_STYPE_DEAUTH,
					       req->reason_code, tx,
					       frame_buf);
		ieee80211_destroy_assoc_data(sdata, false, true);
		ieee80211_report_disconnect(sdata, frame_buf,
					    माप(frame_buf), true,
					    req->reason_code, false);
		वापस 0;
	पूर्ण

	अगर (अगरmgd->associated &&
	    ether_addr_equal(अगरmgd->associated->bssid, req->bssid)) अणु
		sdata_info(sdata,
			   "deauthenticating from %pM by local choice (Reason: %u=%s)\n",
			   req->bssid, req->reason_code,
			   ieee80211_get_reason_code_string(req->reason_code));

		ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DEAUTH,
				       req->reason_code, tx, frame_buf);
		ieee80211_report_disconnect(sdata, frame_buf,
					    माप(frame_buf), true,
					    req->reason_code, false);
		वापस 0;
	पूर्ण

	वापस -ENOTCONN;
पूर्ण

पूर्णांक ieee80211_mgd_disassoc(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा cfg80211_disassoc_request *req)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	u8 bssid[ETH_ALEN];
	u8 frame_buf[IEEE80211_DEAUTH_FRAME_LEN];

	/*
	 * cfg80211 should catch this ... but it's racy since
	 * we can receive a disassoc frame, process it, hand it
	 * to cfg80211 जबतक that's in a locked section alपढ़ोy
	 * trying to tell us that the user wants to disconnect.
	 */
	अगर (अगरmgd->associated != req->bss)
		वापस -ENOLINK;

	sdata_info(sdata,
		   "disassociating from %pM by local choice (Reason: %u=%s)\n",
		   req->bss->bssid, req->reason_code, ieee80211_get_reason_code_string(req->reason_code));

	स_नकल(bssid, req->bss->bssid, ETH_ALEN);
	ieee80211_set_disassoc(sdata, IEEE80211_STYPE_DISASSOC,
			       req->reason_code, !req->local_state_change,
			       frame_buf);

	ieee80211_report_disconnect(sdata, frame_buf, माप(frame_buf), true,
				    req->reason_code, false);

	वापस 0;
पूर्ण

व्योम ieee80211_mgd_stop(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;

	/*
	 * Make sure some work items will not run after this,
	 * they will not करो anything but might not have been
	 * cancelled when disconnecting.
	 */
	cancel_work_sync(&अगरmgd->monitor_work);
	cancel_work_sync(&अगरmgd->beacon_connection_loss_work);
	cancel_work_sync(&अगरmgd->request_smps_work);
	cancel_work_sync(&अगरmgd->csa_connection_drop_work);
	cancel_work_sync(&अगरmgd->chचयन_work);
	cancel_delayed_work_sync(&अगरmgd->tdls_peer_del_work);

	sdata_lock(sdata);
	अगर (अगरmgd->assoc_data) अणु
		काष्ठा cfg80211_bss *bss = अगरmgd->assoc_data->bss;
		ieee80211_destroy_assoc_data(sdata, false, false);
		cfg80211_assoc_समयout(sdata->dev, bss);
	पूर्ण
	अगर (अगरmgd->auth_data)
		ieee80211_destroy_auth_data(sdata, false);
	spin_lock_bh(&अगरmgd->tearकरोwn_lock);
	अगर (अगरmgd->tearकरोwn_skb) अणु
		kमुक्त_skb(अगरmgd->tearकरोwn_skb);
		अगरmgd->tearकरोwn_skb = शून्य;
		अगरmgd->orig_tearकरोwn_skb = शून्य;
	पूर्ण
	kमुक्त(अगरmgd->assoc_req_ies);
	अगरmgd->assoc_req_ies = शून्य;
	अगरmgd->assoc_req_ies_len = 0;
	spin_unlock_bh(&अगरmgd->tearकरोwn_lock);
	del_समयr_sync(&अगरmgd->समयr);
	sdata_unlock(sdata);
पूर्ण

व्योम ieee80211_cqm_rssi_notअगरy(काष्ठा ieee80211_vअगर *vअगर,
			       क्रमागत nl80211_cqm_rssi_threshold_event rssi_event,
			       s32 rssi_level,
			       gfp_t gfp)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	trace_api_cqm_rssi_notअगरy(sdata, rssi_event, rssi_level);

	cfg80211_cqm_rssi_notअगरy(sdata->dev, rssi_event, rssi_level, gfp);
पूर्ण
EXPORT_SYMBOL(ieee80211_cqm_rssi_notअगरy);

व्योम ieee80211_cqm_beacon_loss_notअगरy(काष्ठा ieee80211_vअगर *vअगर, gfp_t gfp)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	trace_api_cqm_beacon_loss_notअगरy(sdata->local, sdata);

	cfg80211_cqm_beacon_loss_notअगरy(sdata->dev, gfp);
पूर्ण
EXPORT_SYMBOL(ieee80211_cqm_beacon_loss_notअगरy);
