<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * spectrum management
 *
 * Copyright 2003, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2006-2007  Jiri Benc <jbenc@suse.cz>
 * Copyright 2007, Michael Wu <flamingice@sourmilk.net>
 * Copyright 2007-2008, Intel Corporation
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright (C) 2018, 2020 Intel Corporation
 */

#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "sta_info.h"
#समावेश "wme.h"

पूर्णांक ieee80211_parse_ch_चयन_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा ieee802_11_elems *elems,
				 क्रमागत nl80211_band current_band,
				 u32 vht_cap_info,
				 u32 sta_flags, u8 *bssid,
				 काष्ठा ieee80211_csa_ie *csa_ie)
अणु
	क्रमागत nl80211_band new_band = current_band;
	पूर्णांक new_freq;
	u8 new_chan_no;
	काष्ठा ieee80211_channel *new_chan;
	काष्ठा cfg80211_chan_def new_vht_chandef = अणुपूर्ण;
	स्थिर काष्ठा ieee80211_sec_chan_offs_ie *sec_chan_offs;
	स्थिर काष्ठा ieee80211_wide_bw_chansw_ie *wide_bw_chansw_ie;
	पूर्णांक secondary_channel_offset = -1;

	स_रखो(csa_ie, 0, माप(*csa_ie));

	sec_chan_offs = elems->sec_chan_offs;
	wide_bw_chansw_ie = elems->wide_bw_chansw_ie;

	अगर (sta_flags & (IEEE80211_STA_DISABLE_HT |
			 IEEE80211_STA_DISABLE_40MHZ)) अणु
		sec_chan_offs = शून्य;
		wide_bw_chansw_ie = शून्य;
	पूर्ण

	अगर (sta_flags & IEEE80211_STA_DISABLE_VHT)
		wide_bw_chansw_ie = शून्य;

	अगर (elems->ext_chansw_ie) अणु
		अगर (!ieee80211_operating_class_to_band(
				elems->ext_chansw_ie->new_operating_class,
				&new_band)) अणु
			sdata_info(sdata,
				   "cannot understand ECSA IE operating class, %d, ignoring\n",
				   elems->ext_chansw_ie->new_operating_class);
		पूर्ण
		new_chan_no = elems->ext_chansw_ie->new_ch_num;
		csa_ie->count = elems->ext_chansw_ie->count;
		csa_ie->mode = elems->ext_chansw_ie->mode;
	पूर्ण अन्यथा अगर (elems->ch_चयन_ie) अणु
		new_chan_no = elems->ch_चयन_ie->new_ch_num;
		csa_ie->count = elems->ch_चयन_ie->count;
		csa_ie->mode = elems->ch_चयन_ie->mode;
	पूर्ण अन्यथा अणु
		/* nothing here we understand */
		वापस 1;
	पूर्ण

	/* Mesh Channel Switch Parameters Element */
	अगर (elems->mesh_chansw_params_ie) अणु
		csa_ie->ttl = elems->mesh_chansw_params_ie->mesh_ttl;
		csa_ie->mode = elems->mesh_chansw_params_ie->mesh_flags;
		csa_ie->pre_value = le16_to_cpu(
				elems->mesh_chansw_params_ie->mesh_pre_value);

		अगर (elems->mesh_chansw_params_ie->mesh_flags &
				WLAN_EID_CHAN_SWITCH_PARAM_REASON)
			csa_ie->reason_code = le16_to_cpu(
				elems->mesh_chansw_params_ie->mesh_reason);
	पूर्ण

	new_freq = ieee80211_channel_to_frequency(new_chan_no, new_band);
	new_chan = ieee80211_get_channel(sdata->local->hw.wiphy, new_freq);
	अगर (!new_chan || new_chan->flags & IEEE80211_CHAN_DISABLED) अणु
		sdata_info(sdata,
			   "BSS %pM switches to unsupported channel (%d MHz), disconnecting\n",
			   bssid, new_freq);
		वापस -EINVAL;
	पूर्ण

	अगर (sec_chan_offs) अणु
		secondary_channel_offset = sec_chan_offs->sec_chan_offs;
	पूर्ण अन्यथा अगर (!(sta_flags & IEEE80211_STA_DISABLE_HT)) अणु
		/* If the secondary channel offset IE is not present,
		 * we can't know what's the post-CSA offset, so the
		 * best we can करो is use 20MHz.
		*/
		secondary_channel_offset = IEEE80211_HT_PARAM_CHA_SEC_NONE;
	पूर्ण

	चयन (secondary_channel_offset) अणु
	शेष:
		/* secondary_channel_offset was present but is invalid */
	हाल IEEE80211_HT_PARAM_CHA_SEC_NONE:
		cfg80211_chandef_create(&csa_ie->chandef, new_chan,
					NL80211_CHAN_HT20);
		अवरोध;
	हाल IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
		cfg80211_chandef_create(&csa_ie->chandef, new_chan,
					NL80211_CHAN_HT40PLUS);
		अवरोध;
	हाल IEEE80211_HT_PARAM_CHA_SEC_BELOW:
		cfg80211_chandef_create(&csa_ie->chandef, new_chan,
					NL80211_CHAN_HT40MINUS);
		अवरोध;
	हाल -1:
		cfg80211_chandef_create(&csa_ie->chandef, new_chan,
					NL80211_CHAN_NO_HT);
		/* keep width क्रम 5/10 MHz channels */
		चयन (sdata->vअगर.bss_conf.chandef.width) अणु
		हाल NL80211_CHAN_WIDTH_5:
		हाल NL80211_CHAN_WIDTH_10:
			csa_ie->chandef.width =
				sdata->vअगर.bss_conf.chandef.width;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (wide_bw_chansw_ie) अणु
		u8 new_seg1 = wide_bw_chansw_ie->new_center_freq_seg1;
		काष्ठा ieee80211_vht_operation vht_oper = अणु
			.chan_width =
				wide_bw_chansw_ie->new_channel_width,
			.center_freq_seg0_idx =
				wide_bw_chansw_ie->new_center_freq_seg0,
			.center_freq_seg1_idx = new_seg1,
			/* .basic_mcs_set करोesn't matter */
		पूर्ण;
		काष्ठा ieee80211_ht_operation ht_oper = अणु
			.operation_mode =
				cpu_to_le16(new_seg1 <<
					    IEEE80211_HT_OP_MODE_CCFS2_SHIFT),
		पूर्ण;

		/* शेष, क्रम the हाल of IEEE80211_VHT_CHANWIDTH_USE_HT,
		 * to the previously parsed chandef
		 */
		new_vht_chandef = csa_ie->chandef;

		/* ignore अगर parsing fails */
		अगर (!ieee80211_chandef_vht_oper(&sdata->local->hw,
						vht_cap_info,
						&vht_oper, &ht_oper,
						&new_vht_chandef))
			new_vht_chandef.chan = शून्य;

		अगर (sta_flags & IEEE80211_STA_DISABLE_80P80MHZ &&
		    new_vht_chandef.width == NL80211_CHAN_WIDTH_80P80)
			ieee80211_chandef_करोwngrade(&new_vht_chandef);
		अगर (sta_flags & IEEE80211_STA_DISABLE_160MHZ &&
		    new_vht_chandef.width == NL80211_CHAN_WIDTH_160)
			ieee80211_chandef_करोwngrade(&new_vht_chandef);
	पूर्ण

	/* अगर VHT data is there validate & use it */
	अगर (new_vht_chandef.chan) अणु
		अगर (!cfg80211_chandef_compatible(&new_vht_chandef,
						 &csa_ie->chandef)) अणु
			sdata_info(sdata,
				   "BSS %pM: CSA has inconsistent channel data, disconnecting\n",
				   bssid);
			वापस -EINVAL;
		पूर्ण
		csa_ie->chandef = new_vht_chandef;
	पूर्ण

	अगर (elems->max_channel_चयन_समय)
		csa_ie->max_चयन_समय =
			(elems->max_channel_चयन_समय[0] << 0) |
			(elems->max_channel_चयन_समय[1] <<  8) |
			(elems->max_channel_चयन_समय[2] << 16);

	वापस 0;
पूर्ण

अटल व्योम ieee80211_send_refuse_measurement_request(काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा ieee80211_msrment_ie *request_ie,
					स्थिर u8 *da, स्थिर u8 *bssid,
					u8 dialog_token)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *msr_report;

	skb = dev_alloc_skb(माप(*msr_report) + local->hw.extra_tx_headroom +
				माप(काष्ठा ieee80211_msrment_ie));
	अगर (!skb)
		वापस;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	msr_report = skb_put_zero(skb, 24);
	स_नकल(msr_report->da, da, ETH_ALEN);
	स_नकल(msr_report->sa, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(msr_report->bssid, bssid, ETH_ALEN);
	msr_report->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						IEEE80211_STYPE_ACTION);

	skb_put(skb, 1 + माप(msr_report->u.action.u.measurement));
	msr_report->u.action.category = WLAN_CATEGORY_SPECTRUM_MGMT;
	msr_report->u.action.u.measurement.action_code =
				WLAN_ACTION_SPCT_MSR_RPRT;
	msr_report->u.action.u.measurement.dialog_token = dialog_token;

	msr_report->u.action.u.measurement.element_id = WLAN_EID_MEASURE_REPORT;
	msr_report->u.action.u.measurement.length =
			माप(काष्ठा ieee80211_msrment_ie);

	स_रखो(&msr_report->u.action.u.measurement.msr_elem, 0,
		माप(काष्ठा ieee80211_msrment_ie));
	msr_report->u.action.u.measurement.msr_elem.token = request_ie->token;
	msr_report->u.action.u.measurement.msr_elem.mode |=
			IEEE80211_SPCT_MSR_RPRT_MODE_REFUSED;
	msr_report->u.action.u.measurement.msr_elem.type = request_ie->type;

	ieee80211_tx_skb(sdata, skb);
पूर्ण

व्योम ieee80211_process_measurement_req(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211_mgmt *mgmt,
				       माप_प्रकार len)
अणु
	/*
	 * Ignoring measurement request is spec violation.
	 * Mandatory measurements must be reported optional
	 * measurements might be refused or reported incapable
	 * For now just refuse
	 * TODO: Answer basic measurement as unmeasured
	 */
	ieee80211_send_refuse_measurement_request(sdata,
			&mgmt->u.action.u.measurement.msr_elem,
			mgmt->sa, mgmt->bssid,
			mgmt->u.action.u.measurement.dialog_token);
पूर्ण
