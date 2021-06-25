<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Scanning implementation
 *
 * Copyright 2003, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright 2004, Instant802 Networks, Inc.
 * Copyright 2005, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007, Michael Wu <flamingice@sourmilk.net>
 * Copyright 2013-2015  Intel Mobile Communications GmbH
 * Copyright 2016-2017  Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */

#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/sch_generic.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/अक्रमom.h>
#समावेश <net/mac80211.h>

#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "mesh.h"

#घोषणा IEEE80211_PROBE_DELAY (HZ / 33)
#घोषणा IEEE80211_CHANNEL_TIME (HZ / 33)
#घोषणा IEEE80211_PASSIVE_CHANNEL_TIME (HZ / 9)

व्योम ieee80211_rx_bss_put(काष्ठा ieee80211_local *local,
			  काष्ठा ieee80211_bss *bss)
अणु
	अगर (!bss)
		वापस;
	cfg80211_put_bss(local->hw.wiphy,
			 container_of((व्योम *)bss, काष्ठा cfg80211_bss, priv));
पूर्ण

अटल bool is_uapsd_supported(काष्ठा ieee802_11_elems *elems)
अणु
	u8 qos_info;

	अगर (elems->wmm_info && elems->wmm_info_len == 7
	    && elems->wmm_info[5] == 1)
		qos_info = elems->wmm_info[6];
	अन्यथा अगर (elems->wmm_param && elems->wmm_param_len == 24
		 && elems->wmm_param[5] == 1)
		qos_info = elems->wmm_param[6];
	अन्यथा
		/* no valid wmm inक्रमmation or parameter element found */
		वापस false;

	वापस qos_info & IEEE80211_WMM_IE_AP_QOSINFO_UAPSD;
पूर्ण

अटल व्योम
ieee80211_update_bss_from_elems(काष्ठा ieee80211_local *local,
				काष्ठा ieee80211_bss *bss,
				काष्ठा ieee802_11_elems *elems,
				काष्ठा ieee80211_rx_status *rx_status,
				bool beacon)
अणु
	पूर्णांक clen, srlen;

	अगर (beacon)
		bss->device_ts_beacon = rx_status->device_बारtamp;
	अन्यथा
		bss->device_ts_presp = rx_status->device_बारtamp;

	अगर (elems->parse_error) अणु
		अगर (beacon)
			bss->corrupt_data |= IEEE80211_BSS_CORRUPT_BEACON;
		अन्यथा
			bss->corrupt_data |= IEEE80211_BSS_CORRUPT_PROBE_RESP;
	पूर्ण अन्यथा अणु
		अगर (beacon)
			bss->corrupt_data &= ~IEEE80211_BSS_CORRUPT_BEACON;
		अन्यथा
			bss->corrupt_data &= ~IEEE80211_BSS_CORRUPT_PROBE_RESP;
	पूर्ण

	/* save the ERP value so that it is available at association समय */
	अगर (elems->erp_info && (!elems->parse_error ||
				!(bss->valid_data & IEEE80211_BSS_VALID_ERP))) अणु
		bss->erp_value = elems->erp_info[0];
		bss->has_erp_value = true;
		अगर (!elems->parse_error)
			bss->valid_data |= IEEE80211_BSS_VALID_ERP;
	पूर्ण

	/* replace old supported rates अगर we get new values */
	अगर (!elems->parse_error ||
	    !(bss->valid_data & IEEE80211_BSS_VALID_RATES)) अणु
		srlen = 0;
		अगर (elems->supp_rates) अणु
			clen = IEEE80211_MAX_SUPP_RATES;
			अगर (clen > elems->supp_rates_len)
				clen = elems->supp_rates_len;
			स_नकल(bss->supp_rates, elems->supp_rates, clen);
			srlen += clen;
		पूर्ण
		अगर (elems->ext_supp_rates) अणु
			clen = IEEE80211_MAX_SUPP_RATES - srlen;
			अगर (clen > elems->ext_supp_rates_len)
				clen = elems->ext_supp_rates_len;
			स_नकल(bss->supp_rates + srlen, elems->ext_supp_rates,
			       clen);
			srlen += clen;
		पूर्ण
		अगर (srlen) अणु
			bss->supp_rates_len = srlen;
			अगर (!elems->parse_error)
				bss->valid_data |= IEEE80211_BSS_VALID_RATES;
		पूर्ण
	पूर्ण

	अगर (!elems->parse_error ||
	    !(bss->valid_data & IEEE80211_BSS_VALID_WMM)) अणु
		bss->wmm_used = elems->wmm_param || elems->wmm_info;
		bss->uapsd_supported = is_uapsd_supported(elems);
		अगर (!elems->parse_error)
			bss->valid_data |= IEEE80211_BSS_VALID_WMM;
	पूर्ण

	अगर (beacon) अणु
		काष्ठा ieee80211_supported_band *sband =
			local->hw.wiphy->bands[rx_status->band];
		अगर (!(rx_status->encoding == RX_ENC_HT) &&
		    !(rx_status->encoding == RX_ENC_VHT))
			bss->beacon_rate =
				&sband->bitrates[rx_status->rate_idx];
	पूर्ण

	अगर (elems->vht_cap_elem)
		bss->vht_cap_info =
			le32_to_cpu(elems->vht_cap_elem->vht_cap_info);
	अन्यथा
		bss->vht_cap_info = 0;
पूर्ण

काष्ठा ieee80211_bss *
ieee80211_bss_info_update(काष्ठा ieee80211_local *local,
			  काष्ठा ieee80211_rx_status *rx_status,
			  काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
			  काष्ठा ieee80211_channel *channel)
अणु
	bool beacon = ieee80211_is_beacon(mgmt->frame_control) ||
		      ieee80211_is_s1g_beacon(mgmt->frame_control);
	काष्ठा cfg80211_bss *cbss, *non_tx_cbss;
	काष्ठा ieee80211_bss *bss, *non_tx_bss;
	काष्ठा cfg80211_inक्रमm_bss bss_meta = अणु
		.bootसमय_ns = rx_status->bootसमय_ns,
	पूर्ण;
	bool संकेत_valid;
	काष्ठा ieee80211_sub_अगर_data *scan_sdata;
	काष्ठा ieee802_11_elems elems;
	माप_प्रकार baselen;
	u8 *elements;

	अगर (rx_status->flag & RX_FLAG_NO_SIGNAL_VAL)
		bss_meta.संकेत = 0; /* invalid संकेत indication */
	अन्यथा अगर (ieee80211_hw_check(&local->hw, SIGNAL_DBM))
		bss_meta.संकेत = rx_status->संकेत * 100;
	अन्यथा अगर (ieee80211_hw_check(&local->hw, SIGNAL_UNSPEC))
		bss_meta.संकेत = (rx_status->संकेत * 100) / local->hw.max_संकेत;

	bss_meta.scan_width = NL80211_BSS_CHAN_WIDTH_20;
	अगर (rx_status->bw == RATE_INFO_BW_5)
		bss_meta.scan_width = NL80211_BSS_CHAN_WIDTH_5;
	अन्यथा अगर (rx_status->bw == RATE_INFO_BW_10)
		bss_meta.scan_width = NL80211_BSS_CHAN_WIDTH_10;

	bss_meta.chan = channel;

	rcu_पढ़ो_lock();
	scan_sdata = rcu_dereference(local->scan_sdata);
	अगर (scan_sdata && scan_sdata->vअगर.type == NL80211_IFTYPE_STATION &&
	    scan_sdata->vअगर.bss_conf.assoc &&
	    ieee80211_have_rx_बारtamp(rx_status)) अणु
		bss_meta.parent_tsf =
			ieee80211_calculate_rx_बारtamp(local, rx_status,
							 len + FCS_LEN, 24);
		ether_addr_copy(bss_meta.parent_bssid,
				scan_sdata->vअगर.bss_conf.bssid);
	पूर्ण
	rcu_पढ़ो_unlock();

	cbss = cfg80211_inक्रमm_bss_frame_data(local->hw.wiphy, &bss_meta,
					      mgmt, len, GFP_ATOMIC);
	अगर (!cbss)
		वापस शून्य;

	अगर (ieee80211_is_probe_resp(mgmt->frame_control)) अणु
		elements = mgmt->u.probe_resp.variable;
		baselen = दुरत्व(काष्ठा ieee80211_mgmt,
				   u.probe_resp.variable);
	पूर्ण अन्यथा अगर (ieee80211_is_s1g_beacon(mgmt->frame_control)) अणु
		काष्ठा ieee80211_ext *ext = (व्योम *) mgmt;

		baselen = दुरत्व(काष्ठा ieee80211_ext, u.s1g_beacon.variable);
		elements = ext->u.s1g_beacon.variable;
	पूर्ण अन्यथा अणु
		baselen = दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);
		elements = mgmt->u.beacon.variable;
	पूर्ण

	अगर (baselen > len)
		वापस शून्य;

	ieee802_11_parse_elems(elements, len - baselen, false, &elems,
			       mgmt->bssid, cbss->bssid);

	/* In हाल the संकेत is invalid update the status */
	संकेत_valid = channel == cbss->channel;
	अगर (!संकेत_valid)
		rx_status->flag |= RX_FLAG_NO_SIGNAL_VAL;

	bss = (व्योम *)cbss->priv;
	ieee80211_update_bss_from_elems(local, bss, &elems, rx_status, beacon);

	list_क्रम_each_entry(non_tx_cbss, &cbss->nontrans_list, nontrans_list) अणु
		non_tx_bss = (व्योम *)non_tx_cbss->priv;

		ieee80211_update_bss_from_elems(local, non_tx_bss, &elems,
						rx_status, beacon);
	पूर्ण

	वापस bss;
पूर्ण

अटल bool ieee80211_scan_accept_presp(काष्ठा ieee80211_sub_अगर_data *sdata,
					u32 scan_flags, स्थिर u8 *da)
अणु
	अगर (!sdata)
		वापस false;
	/* accept broadcast क्रम OCE */
	अगर (scan_flags & NL80211_SCAN_FLAG_ACCEPT_BCAST_PROBE_RESP &&
	    is_broadcast_ether_addr(da))
		वापस true;
	अगर (scan_flags & NL80211_SCAN_FLAG_RANDOM_ADDR)
		वापस true;
	वापस ether_addr_equal(da, sdata->vअगर.addr);
पूर्ण

व्योम ieee80211_scan_rx(काष्ठा ieee80211_local *local, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_sub_अगर_data *sdata1, *sdata2;
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)skb->data;
	काष्ठा ieee80211_bss *bss;
	काष्ठा ieee80211_channel *channel;
	माप_प्रकार min_hdr_len = दुरत्व(काष्ठा ieee80211_mgmt,
				      u.probe_resp.variable);

	अगर (!ieee80211_is_probe_resp(mgmt->frame_control) &&
	    !ieee80211_is_beacon(mgmt->frame_control) &&
	    !ieee80211_is_s1g_beacon(mgmt->frame_control))
		वापस;

	अगर (ieee80211_is_s1g_beacon(mgmt->frame_control)) अणु
		अगर (ieee80211_is_s1g_लघु_beacon(mgmt->frame_control))
			min_hdr_len = दुरत्व(काष्ठा ieee80211_ext,
					       u.s1g_लघु_beacon.variable);
		अन्यथा
			min_hdr_len = दुरत्व(काष्ठा ieee80211_ext,
					       u.s1g_beacon);
	पूर्ण

	अगर (skb->len < min_hdr_len)
		वापस;

	sdata1 = rcu_dereference(local->scan_sdata);
	sdata2 = rcu_dereference(local->sched_scan_sdata);

	अगर (likely(!sdata1 && !sdata2))
		वापस;

	अगर (ieee80211_is_probe_resp(mgmt->frame_control)) अणु
		काष्ठा cfg80211_scan_request *scan_req;
		काष्ठा cfg80211_sched_scan_request *sched_scan_req;
		u32 scan_req_flags = 0, sched_scan_req_flags = 0;

		scan_req = rcu_dereference(local->scan_req);
		sched_scan_req = rcu_dereference(local->sched_scan_req);

		अगर (scan_req)
			scan_req_flags = scan_req->flags;

		अगर (sched_scan_req)
			sched_scan_req_flags = sched_scan_req->flags;

		/* ignore ProbeResp to क्रमeign address or non-bcast (OCE)
		 * unless scanning with अक्रमomised address
		 */
		अगर (!ieee80211_scan_accept_presp(sdata1, scan_req_flags,
						 mgmt->da) &&
		    !ieee80211_scan_accept_presp(sdata2, sched_scan_req_flags,
						 mgmt->da))
			वापस;
	पूर्ण

	channel = ieee80211_get_channel_khz(local->hw.wiphy,
					ieee80211_rx_status_to_khz(rx_status));

	अगर (!channel || channel->flags & IEEE80211_CHAN_DISABLED)
		वापस;

	bss = ieee80211_bss_info_update(local, rx_status,
					mgmt, skb->len,
					channel);
	अगर (bss)
		ieee80211_rx_bss_put(local, bss);
पूर्ण

अटल व्योम
ieee80211_prepare_scan_chandef(काष्ठा cfg80211_chan_def *chandef,
			       क्रमागत nl80211_bss_scan_width scan_width)
अणु
	स_रखो(chandef, 0, माप(*chandef));
	चयन (scan_width) अणु
	हाल NL80211_BSS_CHAN_WIDTH_5:
		chandef->width = NL80211_CHAN_WIDTH_5;
		अवरोध;
	हाल NL80211_BSS_CHAN_WIDTH_10:
		chandef->width = NL80211_CHAN_WIDTH_10;
		अवरोध;
	शेष:
		chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
		अवरोध;
	पूर्ण
पूर्ण

/* वापस false अगर no more work */
अटल bool ieee80211_prep_hw_scan(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा cfg80211_scan_request *req;
	काष्ठा cfg80211_chan_def chandef;
	u8 bands_used = 0;
	पूर्णांक i, ielen, n_chans;
	u32 flags = 0;

	req = rcu_dereference_रक्षित(local->scan_req,
					lockdep_is_held(&local->mtx));

	अगर (test_bit(SCAN_HW_CANCELLED, &local->scanning))
		वापस false;

	अगर (ieee80211_hw_check(&local->hw, SINGLE_SCAN_ON_ALL_BANDS)) अणु
		क्रम (i = 0; i < req->n_channels; i++) अणु
			local->hw_scan_req->req.channels[i] = req->channels[i];
			bands_used |= BIT(req->channels[i]->band);
		पूर्ण

		n_chans = req->n_channels;
	पूर्ण अन्यथा अणु
		करो अणु
			अगर (local->hw_scan_band == NUM_NL80211_BANDS)
				वापस false;

			n_chans = 0;

			क्रम (i = 0; i < req->n_channels; i++) अणु
				अगर (req->channels[i]->band !=
				    local->hw_scan_band)
					जारी;
				local->hw_scan_req->req.channels[n_chans] =
							req->channels[i];
				n_chans++;
				bands_used |= BIT(req->channels[i]->band);
			पूर्ण

			local->hw_scan_band++;
		पूर्ण जबतक (!n_chans);
	पूर्ण

	local->hw_scan_req->req.n_channels = n_chans;
	ieee80211_prepare_scan_chandef(&chandef, req->scan_width);

	अगर (req->flags & NL80211_SCAN_FLAG_MIN_PREQ_CONTENT)
		flags |= IEEE80211_PROBE_FLAG_MIN_CONTENT;

	ielen = ieee80211_build_preq_ies(sdata,
					 (u8 *)local->hw_scan_req->req.ie,
					 local->hw_scan_ies_bufsize,
					 &local->hw_scan_req->ies,
					 req->ie, req->ie_len,
					 bands_used, req->rates, &chandef,
					 flags);
	local->hw_scan_req->req.ie_len = ielen;
	local->hw_scan_req->req.no_cck = req->no_cck;
	ether_addr_copy(local->hw_scan_req->req.mac_addr, req->mac_addr);
	ether_addr_copy(local->hw_scan_req->req.mac_addr_mask,
			req->mac_addr_mask);
	ether_addr_copy(local->hw_scan_req->req.bssid, req->bssid);

	वापस true;
पूर्ण

अटल व्योम __ieee80211_scan_completed(काष्ठा ieee80211_hw *hw, bool पातed)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	bool hw_scan = test_bit(SCAN_HW_SCANNING, &local->scanning);
	bool was_scanning = local->scanning;
	काष्ठा cfg80211_scan_request *scan_req;
	काष्ठा ieee80211_sub_अगर_data *scan_sdata;
	काष्ठा ieee80211_sub_अगर_data *sdata;

	lockdep_निश्चित_held(&local->mtx);

	/*
	 * It's ok to पात a not-yet-running scan (that
	 * we have one at all will be verअगरied by checking
	 * local->scan_req next), but not to complete it
	 * successfully.
	 */
	अगर (WARN_ON(!local->scanning && !पातed))
		पातed = true;

	अगर (WARN_ON(!local->scan_req))
		वापस;

	scan_sdata = rcu_dereference_रक्षित(local->scan_sdata,
					       lockdep_is_held(&local->mtx));

	अगर (hw_scan && !पातed &&
	    !ieee80211_hw_check(&local->hw, SINGLE_SCAN_ON_ALL_BANDS) &&
	    ieee80211_prep_hw_scan(scan_sdata)) अणु
		पूर्णांक rc;

		rc = drv_hw_scan(local,
			rcu_dereference_रक्षित(local->scan_sdata,
						  lockdep_is_held(&local->mtx)),
			local->hw_scan_req);

		अगर (rc == 0)
			वापस;

		/* HW scan failed and is going to be reported as पातed,
		 * so clear old scan info.
		 */
		स_रखो(&local->scan_info, 0, माप(local->scan_info));
		पातed = true;
	पूर्ण

	kमुक्त(local->hw_scan_req);
	local->hw_scan_req = शून्य;

	scan_req = rcu_dereference_रक्षित(local->scan_req,
					     lockdep_is_held(&local->mtx));

	अगर (scan_req != local->पूर्णांक_scan_req) अणु
		local->scan_info.पातed = पातed;
		cfg80211_scan_करोne(scan_req, &local->scan_info);
	पूर्ण
	RCU_INIT_POINTER(local->scan_req, शून्य);
	RCU_INIT_POINTER(local->scan_sdata, शून्य);

	local->scanning = 0;
	local->scan_chandef.chan = शून्य;

	/* Set घातer back to normal operating levels. */
	ieee80211_hw_config(local, 0);

	अगर (!hw_scan) अणु
		ieee80211_configure_filter(local);
		drv_sw_scan_complete(local, scan_sdata);
		ieee80211_offchannel_वापस(local);
	पूर्ण

	ieee80211_recalc_idle(local);

	ieee80211_mlme_notअगरy_scan_completed(local);
	ieee80211_ibss_notअगरy_scan_completed(local);

	/* Requeue all the work that might have been ignored जबतक
	 * the scan was in progress; अगर there was none this will
	 * just be a no-op क्रम the particular पूर्णांकerface.
	 */
	list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (ieee80211_sdata_running(sdata))
			ieee80211_queue_work(&sdata->local->hw, &sdata->work);
	पूर्ण

	अगर (was_scanning)
		ieee80211_start_next_roc(local);
पूर्ण

व्योम ieee80211_scan_completed(काष्ठा ieee80211_hw *hw,
			      काष्ठा cfg80211_scan_info *info)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	trace_api_scan_completed(local, info->पातed);

	set_bit(SCAN_COMPLETED, &local->scanning);
	अगर (info->पातed)
		set_bit(SCAN_ABORTED, &local->scanning);

	स_नकल(&local->scan_info, info, माप(*info));

	ieee80211_queue_delayed_work(&local->hw, &local->scan_work, 0);
पूर्ण
EXPORT_SYMBOL(ieee80211_scan_completed);

अटल पूर्णांक ieee80211_start_sw_scan(काष्ठा ieee80211_local *local,
				   काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	/* Software scan is not supported in multi-channel हालs */
	अगर (local->use_chanctx)
		वापस -EOPNOTSUPP;

	/*
	 * Hardware/driver करोesn't support hw_scan, so use software
	 * scanning instead. First send a nullfunc frame with घातer save
	 * bit on so that AP will buffer the frames क्रम us जबतक we are not
	 * listening, then send probe requests to each channel and रुको क्रम
	 * the responses. After all channels are scanned, tune back to the
	 * original channel and send a nullfunc frame with घातer save bit
	 * off to trigger the AP to send us all the buffered frames.
	 *
	 * Note that जबतक local->sw_scanning is true everything अन्यथा but
	 * nullfunc frames and probe requests will be dropped in
	 * ieee80211_tx_h_check_assoc().
	 */
	drv_sw_scan_start(local, sdata, local->scan_addr);

	local->leave_oper_channel_समय = jअगरfies;
	local->next_scan_state = SCAN_DECISION;
	local->scan_channel_idx = 0;

	ieee80211_offchannel_stop_vअगरs(local);

	/* ensure nullfunc is transmitted beक्रमe leaving operating channel */
	ieee80211_flush_queues(local, शून्य, false);

	ieee80211_configure_filter(local);

	/* We need to set घातer level at maximum rate क्रम scanning. */
	ieee80211_hw_config(local, 0);

	ieee80211_queue_delayed_work(&local->hw,
				     &local->scan_work, 0);

	वापस 0;
पूर्ण

अटल bool __ieee80211_can_leave_ch(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_sub_अगर_data *sdata_iter;

	अगर (!ieee80211_is_radar_required(local))
		वापस true;

	अगर (!regulatory_pre_cac_allowed(local->hw.wiphy))
		वापस false;

	mutex_lock(&local->अगरlist_mtx);
	list_क्रम_each_entry(sdata_iter, &local->पूर्णांकerfaces, list) अणु
		अगर (sdata_iter->wdev.cac_started) अणु
			mutex_unlock(&local->अगरlist_mtx);
			वापस false;
		पूर्ण
	पूर्ण
	mutex_unlock(&local->अगरlist_mtx);

	वापस true;
पूर्ण

अटल bool ieee80211_can_scan(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (!__ieee80211_can_leave_ch(sdata))
		वापस false;

	अगर (!list_empty(&local->roc_list))
		वापस false;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
	    sdata->u.mgd.flags & IEEE80211_STA_CONNECTION_POLL)
		वापस false;

	वापस true;
पूर्ण

व्योम ieee80211_run_deferred_scan(काष्ठा ieee80211_local *local)
अणु
	lockdep_निश्चित_held(&local->mtx);

	अगर (!local->scan_req || local->scanning)
		वापस;

	अगर (!ieee80211_can_scan(local,
				rcu_dereference_रक्षित(
					local->scan_sdata,
					lockdep_is_held(&local->mtx))))
		वापस;

	ieee80211_queue_delayed_work(&local->hw, &local->scan_work,
				     round_jअगरfies_relative(0));
पूर्ण

अटल व्योम ieee80211_send_scan_probe_req(काष्ठा ieee80211_sub_अगर_data *sdata,
					  स्थिर u8 *src, स्थिर u8 *dst,
					  स्थिर u8 *ssid, माप_प्रकार ssid_len,
					  स्थिर u8 *ie, माप_प्रकार ie_len,
					  u32 ratemask, u32 flags, u32 tx_flags,
					  काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा sk_buff *skb;

	skb = ieee80211_build_probe_req(sdata, src, dst, ratemask, channel,
					ssid, ssid_len,
					ie, ie_len, flags);

	अगर (skb) अणु
		अगर (flags & IEEE80211_PROBE_FLAG_RANDOM_SN) अणु
			काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
			काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
			u16 sn = get_अक्रमom_u32();

			info->control.flags |= IEEE80211_TX_CTRL_NO_SEQNO;
			hdr->seq_ctrl =
				cpu_to_le16(IEEE80211_SN_TO_SEQ(sn));
		पूर्ण
		IEEE80211_SKB_CB(skb)->flags |= tx_flags;
		ieee80211_tx_skb_tid_band(sdata, skb, 7, channel->band);
	पूर्ण
पूर्ण

अटल व्योम ieee80211_scan_state_send_probe(काष्ठा ieee80211_local *local,
					    अचिन्हित दीर्घ *next_delay)
अणु
	पूर्णांक i;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा cfg80211_scan_request *scan_req;
	क्रमागत nl80211_band band = local->hw.conf.chandef.chan->band;
	u32 flags = 0, tx_flags;

	scan_req = rcu_dereference_रक्षित(local->scan_req,
					     lockdep_is_held(&local->mtx));

	tx_flags = IEEE80211_TX_INTFL_OFFCHAN_TX_OK;
	अगर (scan_req->no_cck)
		tx_flags |= IEEE80211_TX_CTL_NO_CCK_RATE;
	अगर (scan_req->flags & NL80211_SCAN_FLAG_MIN_PREQ_CONTENT)
		flags |= IEEE80211_PROBE_FLAG_MIN_CONTENT;
	अगर (scan_req->flags & NL80211_SCAN_FLAG_RANDOM_SN)
		flags |= IEEE80211_PROBE_FLAG_RANDOM_SN;

	sdata = rcu_dereference_रक्षित(local->scan_sdata,
					  lockdep_is_held(&local->mtx));

	क्रम (i = 0; i < scan_req->n_ssids; i++)
		ieee80211_send_scan_probe_req(
			sdata, local->scan_addr, scan_req->bssid,
			scan_req->ssids[i].ssid, scan_req->ssids[i].ssid_len,
			scan_req->ie, scan_req->ie_len,
			scan_req->rates[band], flags,
			tx_flags, local->hw.conf.chandef.chan);

	/*
	 * After sending probe requests, रुको क्रम probe responses
	 * on the channel.
	 */
	*next_delay = IEEE80211_CHANNEL_TIME;
	local->next_scan_state = SCAN_DECISION;
पूर्ण

अटल पूर्णांक __ieee80211_start_scan(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा cfg80211_scan_request *req)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	bool hw_scan = local->ops->hw_scan;
	पूर्णांक rc;

	lockdep_निश्चित_held(&local->mtx);

	अगर (local->scan_req)
		वापस -EBUSY;

	अगर (!__ieee80211_can_leave_ch(sdata))
		वापस -EBUSY;

	अगर (!ieee80211_can_scan(local, sdata)) अणु
		/* रुको क्रम the work to finish/समय out */
		rcu_assign_poपूर्णांकer(local->scan_req, req);
		rcu_assign_poपूर्णांकer(local->scan_sdata, sdata);
		वापस 0;
	पूर्ण

 again:
	अगर (hw_scan) अणु
		u8 *ies;

		local->hw_scan_ies_bufsize = local->scan_ies_len + req->ie_len;

		अगर (ieee80211_hw_check(&local->hw, SINGLE_SCAN_ON_ALL_BANDS)) अणु
			पूर्णांक i, n_bands = 0;
			u8 bands_counted = 0;

			क्रम (i = 0; i < req->n_channels; i++) अणु
				अगर (bands_counted & BIT(req->channels[i]->band))
					जारी;
				bands_counted |= BIT(req->channels[i]->band);
				n_bands++;
			पूर्ण

			local->hw_scan_ies_bufsize *= n_bands;
		पूर्ण

		local->hw_scan_req = kदो_स्मृति(
				माप(*local->hw_scan_req) +
				req->n_channels * माप(req->channels[0]) +
				local->hw_scan_ies_bufsize, GFP_KERNEL);
		अगर (!local->hw_scan_req)
			वापस -ENOMEM;

		local->hw_scan_req->req.ssids = req->ssids;
		local->hw_scan_req->req.n_ssids = req->n_ssids;
		ies = (u8 *)local->hw_scan_req +
			माप(*local->hw_scan_req) +
			req->n_channels * माप(req->channels[0]);
		local->hw_scan_req->req.ie = ies;
		local->hw_scan_req->req.flags = req->flags;
		eth_broadcast_addr(local->hw_scan_req->req.bssid);
		local->hw_scan_req->req.duration = req->duration;
		local->hw_scan_req->req.duration_mandatory =
			req->duration_mandatory;

		local->hw_scan_band = 0;
		local->hw_scan_req->req.n_6ghz_params = req->n_6ghz_params;
		local->hw_scan_req->req.scan_6ghz_params =
			req->scan_6ghz_params;
		local->hw_scan_req->req.scan_6ghz = req->scan_6ghz;

		/*
		 * After allocating local->hw_scan_req, we must
		 * go through until ieee80211_prep_hw_scan(), so
		 * anything that might be changed here and leave
		 * this function early must not go after this
		 * allocation.
		 */
	पूर्ण

	rcu_assign_poपूर्णांकer(local->scan_req, req);
	rcu_assign_poपूर्णांकer(local->scan_sdata, sdata);

	अगर (req->flags & NL80211_SCAN_FLAG_RANDOM_ADDR)
		get_अक्रमom_mask_addr(local->scan_addr,
				     req->mac_addr,
				     req->mac_addr_mask);
	अन्यथा
		स_नकल(local->scan_addr, sdata->vअगर.addr, ETH_ALEN);

	अगर (hw_scan) अणु
		__set_bit(SCAN_HW_SCANNING, &local->scanning);
	पूर्ण अन्यथा अगर ((req->n_channels == 1) &&
		   (req->channels[0] == local->_oper_chandef.chan)) अणु
		/*
		 * If we are scanning only on the operating channel
		 * then we करो not need to stop normal activities
		 */
		अचिन्हित दीर्घ next_delay;

		__set_bit(SCAN_ONCHANNEL_SCANNING, &local->scanning);

		ieee80211_recalc_idle(local);

		/* Notअगरy driver scan is starting, keep order of operations
		 * same as normal software scan, in हाल that matters. */
		drv_sw_scan_start(local, sdata, local->scan_addr);

		ieee80211_configure_filter(local); /* accept probe-responses */

		/* We need to ensure घातer level is at max क्रम scanning. */
		ieee80211_hw_config(local, 0);

		अगर ((req->channels[0]->flags & (IEEE80211_CHAN_NO_IR |
						IEEE80211_CHAN_RADAR)) ||
		    !req->n_ssids) अणु
			next_delay = IEEE80211_PASSIVE_CHANNEL_TIME;
		पूर्ण अन्यथा अणु
			ieee80211_scan_state_send_probe(local, &next_delay);
			next_delay = IEEE80211_CHANNEL_TIME;
		पूर्ण

		/* Now, just रुको a bit and we are all करोne! */
		ieee80211_queue_delayed_work(&local->hw, &local->scan_work,
					     next_delay);
		वापस 0;
	पूर्ण अन्यथा अणु
		/* Do normal software scan */
		__set_bit(SCAN_SW_SCANNING, &local->scanning);
	पूर्ण

	ieee80211_recalc_idle(local);

	अगर (hw_scan) अणु
		WARN_ON(!ieee80211_prep_hw_scan(sdata));
		rc = drv_hw_scan(local, sdata, local->hw_scan_req);
	पूर्ण अन्यथा अणु
		rc = ieee80211_start_sw_scan(local, sdata);
	पूर्ण

	अगर (rc) अणु
		kमुक्त(local->hw_scan_req);
		local->hw_scan_req = शून्य;
		local->scanning = 0;

		ieee80211_recalc_idle(local);

		local->scan_req = शून्य;
		RCU_INIT_POINTER(local->scan_sdata, शून्य);
	पूर्ण

	अगर (hw_scan && rc == 1) अणु
		/*
		 * we can't fall back to software क्रम P2P-GO
		 * as it must update NoA etc.
		 */
		अगर (ieee80211_vअगर_type_p2p(&sdata->vअगर) ==
				NL80211_IFTYPE_P2P_GO)
			वापस -EOPNOTSUPP;
		hw_scan = false;
		जाओ again;
	पूर्ण

	वापस rc;
पूर्ण

अटल अचिन्हित दीर्घ
ieee80211_scan_get_channel_समय(काष्ठा ieee80211_channel *chan)
अणु
	/*
	 * TODO: channel चयनing also consumes quite some समय,
	 * add that delay as well to get a better estimation
	 */
	अगर (chan->flags & (IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_RADAR))
		वापस IEEE80211_PASSIVE_CHANNEL_TIME;
	वापस IEEE80211_PROBE_DELAY + IEEE80211_CHANNEL_TIME;
पूर्ण

अटल व्योम ieee80211_scan_state_decision(काष्ठा ieee80211_local *local,
					  अचिन्हित दीर्घ *next_delay)
अणु
	bool associated = false;
	bool tx_empty = true;
	bool bad_latency;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_channel *next_chan;
	क्रमागत mac80211_scan_state next_scan_state;
	काष्ठा cfg80211_scan_request *scan_req;

	/*
	 * check अगर at least one STA पूर्णांकerface is associated,
	 * check अगर at least one STA पूर्णांकerface has pending tx frames
	 * and grab the lowest used beacon पूर्णांकerval
	 */
	mutex_lock(&local->अगरlist_mtx);
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(sdata))
			जारी;

		अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION) अणु
			अगर (sdata->u.mgd.associated) अणु
				associated = true;

				अगर (!qdisc_all_tx_empty(sdata->dev)) अणु
					tx_empty = false;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&local->अगरlist_mtx);

	scan_req = rcu_dereference_रक्षित(local->scan_req,
					     lockdep_is_held(&local->mtx));

	next_chan = scan_req->channels[local->scan_channel_idx];

	/*
	 * we're currently scanning a different channel, let's
	 * see अगर we can scan another channel without पूर्णांकerfering
	 * with the current traffic situation.
	 *
	 * Keep good latency, करो not stay off-channel more than 125 ms.
	 */

	bad_latency = समय_after(jअगरfies +
				 ieee80211_scan_get_channel_समय(next_chan),
				 local->leave_oper_channel_समय + HZ / 8);

	अगर (associated && !tx_empty) अणु
		अगर (scan_req->flags & NL80211_SCAN_FLAG_LOW_PRIORITY)
			next_scan_state = SCAN_ABORT;
		अन्यथा
			next_scan_state = SCAN_SUSPEND;
	पूर्ण अन्यथा अगर (associated && bad_latency) अणु
		next_scan_state = SCAN_SUSPEND;
	पूर्ण अन्यथा अणु
		next_scan_state = SCAN_SET_CHANNEL;
	पूर्ण

	local->next_scan_state = next_scan_state;

	*next_delay = 0;
पूर्ण

अटल व्योम ieee80211_scan_state_set_channel(काष्ठा ieee80211_local *local,
					     अचिन्हित दीर्घ *next_delay)
अणु
	पूर्णांक skip;
	काष्ठा ieee80211_channel *chan;
	क्रमागत nl80211_bss_scan_width oper_scan_width;
	काष्ठा cfg80211_scan_request *scan_req;

	scan_req = rcu_dereference_रक्षित(local->scan_req,
					     lockdep_is_held(&local->mtx));

	skip = 0;
	chan = scan_req->channels[local->scan_channel_idx];

	local->scan_chandef.chan = chan;
	local->scan_chandef.center_freq1 = chan->center_freq;
	local->scan_chandef.freq1_offset = chan->freq_offset;
	local->scan_chandef.center_freq2 = 0;

	/* For scanning on the S1G band, ignore scan_width (which is स्थिरant
	 * across all channels) क्रम now since channel width is specअगरic to each
	 * channel. Detect the required channel width here and likely revisit
	 * later. Maybe scan_width could be used to build the channel scan list?
	 */
	अगर (chan->band == NL80211_BAND_S1GHZ) अणु
		local->scan_chandef.width = ieee80211_s1g_channel_width(chan);
		जाओ set_channel;
	पूर्ण

	चयन (scan_req->scan_width) अणु
	हाल NL80211_BSS_CHAN_WIDTH_5:
		local->scan_chandef.width = NL80211_CHAN_WIDTH_5;
		अवरोध;
	हाल NL80211_BSS_CHAN_WIDTH_10:
		local->scan_chandef.width = NL80211_CHAN_WIDTH_10;
		अवरोध;
	शेष:
	हाल NL80211_BSS_CHAN_WIDTH_20:
		/* If scanning on oper channel, use whatever channel-type
		 * is currently in use.
		 */
		oper_scan_width = cfg80211_chandef_to_scan_width(
					&local->_oper_chandef);
		अगर (chan == local->_oper_chandef.chan &&
		    oper_scan_width == scan_req->scan_width)
			local->scan_chandef = local->_oper_chandef;
		अन्यथा
			local->scan_chandef.width = NL80211_CHAN_WIDTH_20_NOHT;
		अवरोध;
	हाल NL80211_BSS_CHAN_WIDTH_1:
	हाल NL80211_BSS_CHAN_WIDTH_2:
		/* shouldn't get here, S1G handled above */
		WARN_ON(1);
		अवरोध;
	पूर्ण

set_channel:
	अगर (ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_CHANNEL))
		skip = 1;

	/* advance state machine to next channel/band */
	local->scan_channel_idx++;

	अगर (skip) अणु
		/* अगर we skip this channel वापस to the decision state */
		local->next_scan_state = SCAN_DECISION;
		वापस;
	पूर्ण

	/*
	 * Probe delay is used to update the NAV, cf. 11.1.3.2.2
	 * (which unक्रमtunately करोesn't say _why_ step a) is करोne,
	 * but it रुकोs क्रम the probe delay or until a frame is
	 * received - and the received frame would update the NAV).
	 * For now, we करो not support रुकोing until a frame is
	 * received.
	 *
	 * In any हाल, it is not necessary क्रम a passive scan.
	 */
	अगर ((chan->flags & (IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_RADAR)) ||
	    !scan_req->n_ssids) अणु
		*next_delay = IEEE80211_PASSIVE_CHANNEL_TIME;
		local->next_scan_state = SCAN_DECISION;
		वापस;
	पूर्ण

	/* active scan, send probes */
	*next_delay = IEEE80211_PROBE_DELAY;
	local->next_scan_state = SCAN_SEND_PROBE;
पूर्ण

अटल व्योम ieee80211_scan_state_suspend(काष्ठा ieee80211_local *local,
					 अचिन्हित दीर्घ *next_delay)
अणु
	/* चयन back to the operating channel */
	local->scan_chandef.chan = शून्य;
	ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_CHANNEL);

	/* disable PS */
	ieee80211_offchannel_वापस(local);

	*next_delay = HZ / 5;
	/* afterwards, resume scan & go to next channel */
	local->next_scan_state = SCAN_RESUME;
पूर्ण

अटल व्योम ieee80211_scan_state_resume(काष्ठा ieee80211_local *local,
					अचिन्हित दीर्घ *next_delay)
अणु
	ieee80211_offchannel_stop_vअगरs(local);

	अगर (local->ops->flush) अणु
		ieee80211_flush_queues(local, शून्य, false);
		*next_delay = 0;
	पूर्ण अन्यथा
		*next_delay = HZ / 10;

	/* remember when we left the operating channel */
	local->leave_oper_channel_समय = jअगरfies;

	/* advance to the next channel to be scanned */
	local->next_scan_state = SCAN_SET_CHANNEL;
पूर्ण

व्योम ieee80211_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local =
		container_of(work, काष्ठा ieee80211_local, scan_work.work);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा cfg80211_scan_request *scan_req;
	अचिन्हित दीर्घ next_delay = 0;
	bool पातed;

	mutex_lock(&local->mtx);

	अगर (!ieee80211_can_run_worker(local)) अणु
		पातed = true;
		जाओ out_complete;
	पूर्ण

	sdata = rcu_dereference_रक्षित(local->scan_sdata,
					  lockdep_is_held(&local->mtx));
	scan_req = rcu_dereference_रक्षित(local->scan_req,
					     lockdep_is_held(&local->mtx));

	/* When scanning on-channel, the first-callback means completed. */
	अगर (test_bit(SCAN_ONCHANNEL_SCANNING, &local->scanning)) अणु
		पातed = test_and_clear_bit(SCAN_ABORTED, &local->scanning);
		जाओ out_complete;
	पूर्ण

	अगर (test_and_clear_bit(SCAN_COMPLETED, &local->scanning)) अणु
		पातed = test_and_clear_bit(SCAN_ABORTED, &local->scanning);
		जाओ out_complete;
	पूर्ण

	अगर (!sdata || !scan_req)
		जाओ out;

	अगर (!local->scanning) अणु
		पूर्णांक rc;

		RCU_INIT_POINTER(local->scan_req, शून्य);
		RCU_INIT_POINTER(local->scan_sdata, शून्य);

		rc = __ieee80211_start_scan(sdata, scan_req);
		अगर (rc) अणु
			/* need to complete scan in cfg80211 */
			rcu_assign_poपूर्णांकer(local->scan_req, scan_req);
			पातed = true;
			जाओ out_complete;
		पूर्ण अन्यथा
			जाओ out;
	पूर्ण

	/*
	 * as दीर्घ as no delay is required advance immediately
	 * without scheduling a new work
	 */
	करो अणु
		अगर (!ieee80211_sdata_running(sdata)) अणु
			पातed = true;
			जाओ out_complete;
		पूर्ण

		चयन (local->next_scan_state) अणु
		हाल SCAN_DECISION:
			/* अगर no more bands/channels left, complete scan */
			अगर (local->scan_channel_idx >= scan_req->n_channels) अणु
				पातed = false;
				जाओ out_complete;
			पूर्ण
			ieee80211_scan_state_decision(local, &next_delay);
			अवरोध;
		हाल SCAN_SET_CHANNEL:
			ieee80211_scan_state_set_channel(local, &next_delay);
			अवरोध;
		हाल SCAN_SEND_PROBE:
			ieee80211_scan_state_send_probe(local, &next_delay);
			अवरोध;
		हाल SCAN_SUSPEND:
			ieee80211_scan_state_suspend(local, &next_delay);
			अवरोध;
		हाल SCAN_RESUME:
			ieee80211_scan_state_resume(local, &next_delay);
			अवरोध;
		हाल SCAN_ABORT:
			पातed = true;
			जाओ out_complete;
		पूर्ण
	पूर्ण जबतक (next_delay == 0);

	ieee80211_queue_delayed_work(&local->hw, &local->scan_work, next_delay);
	जाओ out;

out_complete:
	__ieee80211_scan_completed(&local->hw, पातed);
out:
	mutex_unlock(&local->mtx);
पूर्ण

पूर्णांक ieee80211_request_scan(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा cfg80211_scan_request *req)
अणु
	पूर्णांक res;

	mutex_lock(&sdata->local->mtx);
	res = __ieee80211_start_scan(sdata, req);
	mutex_unlock(&sdata->local->mtx);

	वापस res;
पूर्ण

पूर्णांक ieee80211_request_ibss_scan(काष्ठा ieee80211_sub_अगर_data *sdata,
				स्थिर u8 *ssid, u8 ssid_len,
				काष्ठा ieee80211_channel **channels,
				अचिन्हित पूर्णांक n_channels,
				क्रमागत nl80211_bss_scan_width scan_width)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक ret = -EBUSY, i, n_ch = 0;
	क्रमागत nl80211_band band;

	mutex_lock(&local->mtx);

	/* busy scanning */
	अगर (local->scan_req)
		जाओ unlock;

	/* fill पूर्णांकernal scan request */
	अगर (!channels) अणु
		पूर्णांक max_n;

		क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
			अगर (!local->hw.wiphy->bands[band] ||
			    band == NL80211_BAND_6GHZ)
				जारी;

			max_n = local->hw.wiphy->bands[band]->n_channels;
			क्रम (i = 0; i < max_n; i++) अणु
				काष्ठा ieee80211_channel *पंचांगp_ch =
				    &local->hw.wiphy->bands[band]->channels[i];

				अगर (पंचांगp_ch->flags & (IEEE80211_CHAN_NO_IR |
						     IEEE80211_CHAN_DISABLED))
					जारी;

				local->पूर्णांक_scan_req->channels[n_ch] = पंचांगp_ch;
				n_ch++;
			पूर्ण
		पूर्ण

		अगर (WARN_ON_ONCE(n_ch == 0))
			जाओ unlock;

		local->पूर्णांक_scan_req->n_channels = n_ch;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < n_channels; i++) अणु
			अगर (channels[i]->flags & (IEEE80211_CHAN_NO_IR |
						  IEEE80211_CHAN_DISABLED))
				जारी;

			local->पूर्णांक_scan_req->channels[n_ch] = channels[i];
			n_ch++;
		पूर्ण

		अगर (WARN_ON_ONCE(n_ch == 0))
			जाओ unlock;

		local->पूर्णांक_scan_req->n_channels = n_ch;
	पूर्ण

	local->पूर्णांक_scan_req->ssids = &local->scan_ssid;
	local->पूर्णांक_scan_req->n_ssids = 1;
	local->पूर्णांक_scan_req->scan_width = scan_width;
	स_नकल(local->पूर्णांक_scan_req->ssids[0].ssid, ssid, IEEE80211_MAX_SSID_LEN);
	local->पूर्णांक_scan_req->ssids[0].ssid_len = ssid_len;

	ret = __ieee80211_start_scan(sdata, sdata->local->पूर्णांक_scan_req);
 unlock:
	mutex_unlock(&local->mtx);
	वापस ret;
पूर्ण

/*
 * Only call this function when a scan can't be queued -- under RTNL.
 */
व्योम ieee80211_scan_cancel(काष्ठा ieee80211_local *local)
अणु
	/*
	 * We are canceling software scan, or deferred scan that was not
	 * yet really started (see __ieee80211_start_scan ).
	 *
	 * Regarding hardware scan:
	 * - we can not call  __ieee80211_scan_completed() as when
	 *   SCAN_HW_SCANNING bit is set this function change
	 *   local->hw_scan_req to operate on 5G band, what race with
	 *   driver which can use local->hw_scan_req
	 *
	 * - we can not cancel scan_work since driver can schedule it
	 *   by ieee80211_scan_completed(..., true) to finish scan
	 *
	 * Hence we only call the cancel_hw_scan() callback, but the low-level
	 * driver is still responsible क्रम calling ieee80211_scan_completed()
	 * after the scan was completed/पातed.
	 */

	mutex_lock(&local->mtx);
	अगर (!local->scan_req)
		जाओ out;

	/*
	 * We have a scan running and the driver alपढ़ोy reported completion,
	 * but the worker hasn't run yet or is stuck on the mutex - mark it as
	 * cancelled.
	 */
	अगर (test_bit(SCAN_HW_SCANNING, &local->scanning) &&
	    test_bit(SCAN_COMPLETED, &local->scanning)) अणु
		set_bit(SCAN_HW_CANCELLED, &local->scanning);
		जाओ out;
	पूर्ण

	अगर (test_bit(SCAN_HW_SCANNING, &local->scanning)) अणु
		/*
		 * Make sure that __ieee80211_scan_completed करोesn't trigger a
		 * scan on another band.
		 */
		set_bit(SCAN_HW_CANCELLED, &local->scanning);
		अगर (local->ops->cancel_hw_scan)
			drv_cancel_hw_scan(local,
				rcu_dereference_रक्षित(local->scan_sdata,
						lockdep_is_held(&local->mtx)));
		जाओ out;
	पूर्ण

	/*
	 * If the work is currently running, it must be blocked on
	 * the mutex, but we'll set scan_sdata = NULL and it'll
	 * simply निकास once it acquires the mutex.
	 */
	cancel_delayed_work(&local->scan_work);
	/* and clean up */
	स_रखो(&local->scan_info, 0, माप(local->scan_info));
	__ieee80211_scan_completed(&local->hw, true);
out:
	mutex_unlock(&local->mtx);
पूर्ण

पूर्णांक __ieee80211_request_sched_scan_start(काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा cfg80211_sched_scan_request *req)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_scan_ies sched_scan_ies = अणुपूर्ण;
	काष्ठा cfg80211_chan_def chandef;
	पूर्णांक ret, i, iebufsz, num_bands = 0;
	u32 rate_masks[NUM_NL80211_BANDS] = अणुपूर्ण;
	u8 bands_used = 0;
	u8 *ie;
	u32 flags = 0;

	iebufsz = local->scan_ies_len + req->ie_len;

	lockdep_निश्चित_held(&local->mtx);

	अगर (!local->ops->sched_scan_start)
		वापस -ENOTSUPP;

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
		अगर (local->hw.wiphy->bands[i]) अणु
			bands_used |= BIT(i);
			rate_masks[i] = (u32) -1;
			num_bands++;
		पूर्ण
	पूर्ण

	अगर (req->flags & NL80211_SCAN_FLAG_MIN_PREQ_CONTENT)
		flags |= IEEE80211_PROBE_FLAG_MIN_CONTENT;

	ie = kसुस्मृति(iebufsz, num_bands, GFP_KERNEL);
	अगर (!ie) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ieee80211_prepare_scan_chandef(&chandef, req->scan_width);

	ieee80211_build_preq_ies(sdata, ie, num_bands * iebufsz,
				 &sched_scan_ies, req->ie,
				 req->ie_len, bands_used, rate_masks, &chandef,
				 flags);

	ret = drv_sched_scan_start(local, sdata, req, &sched_scan_ies);
	अगर (ret == 0) अणु
		rcu_assign_poपूर्णांकer(local->sched_scan_sdata, sdata);
		rcu_assign_poपूर्णांकer(local->sched_scan_req, req);
	पूर्ण

	kमुक्त(ie);

out:
	अगर (ret) अणु
		/* Clean in हाल of failure after HW restart or upon resume. */
		RCU_INIT_POINTER(local->sched_scan_sdata, शून्य);
		RCU_INIT_POINTER(local->sched_scan_req, शून्य);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ieee80211_request_sched_scan_start(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा cfg80211_sched_scan_request *req)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक ret;

	mutex_lock(&local->mtx);

	अगर (rcu_access_poपूर्णांकer(local->sched_scan_sdata)) अणु
		mutex_unlock(&local->mtx);
		वापस -EBUSY;
	पूर्ण

	ret = __ieee80211_request_sched_scan_start(sdata, req);

	mutex_unlock(&local->mtx);
	वापस ret;
पूर्ण

पूर्णांक ieee80211_request_sched_scan_stop(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sched_scan_sdata;
	पूर्णांक ret = -ENOENT;

	mutex_lock(&local->mtx);

	अगर (!local->ops->sched_scan_stop) अणु
		ret = -ENOTSUPP;
		जाओ out;
	पूर्ण

	/* We करोn't want to restart sched scan anymore. */
	RCU_INIT_POINTER(local->sched_scan_req, शून्य);

	sched_scan_sdata = rcu_dereference_रक्षित(local->sched_scan_sdata,
						lockdep_is_held(&local->mtx));
	अगर (sched_scan_sdata) अणु
		ret = drv_sched_scan_stop(local, sched_scan_sdata);
		अगर (!ret)
			RCU_INIT_POINTER(local->sched_scan_sdata, शून्य);
	पूर्ण
out:
	mutex_unlock(&local->mtx);

	वापस ret;
पूर्ण

व्योम ieee80211_sched_scan_results(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	trace_api_sched_scan_results(local);

	cfg80211_sched_scan_results(hw->wiphy, 0);
पूर्ण
EXPORT_SYMBOL(ieee80211_sched_scan_results);

व्योम ieee80211_sched_scan_end(काष्ठा ieee80211_local *local)
अणु
	mutex_lock(&local->mtx);

	अगर (!rcu_access_poपूर्णांकer(local->sched_scan_sdata)) अणु
		mutex_unlock(&local->mtx);
		वापस;
	पूर्ण

	RCU_INIT_POINTER(local->sched_scan_sdata, शून्य);

	/* If sched scan was पातed by the driver. */
	RCU_INIT_POINTER(local->sched_scan_req, शून्य);

	mutex_unlock(&local->mtx);

	cfg80211_sched_scan_stopped(local->hw.wiphy, 0);
पूर्ण

व्योम ieee80211_sched_scan_stopped_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local =
		container_of(work, काष्ठा ieee80211_local,
			     sched_scan_stopped_work);

	ieee80211_sched_scan_end(local);
पूर्ण

व्योम ieee80211_sched_scan_stopped(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	trace_api_sched_scan_stopped(local);

	/*
	 * this shouldn't really happen, so क्रम simplicity
	 * simply ignore it, and let mac80211 reconfigure
	 * the sched scan later on.
	 */
	अगर (local->in_reconfig)
		वापस;

	schedule_work(&local->sched_scan_stopped_work);
पूर्ण
EXPORT_SYMBOL(ieee80211_sched_scan_stopped);
