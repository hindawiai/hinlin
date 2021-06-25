<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2012 Texas Instruments. All rights reserved.
 */

#समावेश <linux/ieee80211.h>
#समावेश "scan.h"
#समावेश "../wlcore/debug.h"
#समावेश "../wlcore/tx.h"

अटल पूर्णांक wl1271_get_scan_channels(काष्ठा wl1271 *wl,
				    काष्ठा cfg80211_scan_request *req,
				    काष्ठा basic_scan_channel_params *channels,
				    क्रमागत nl80211_band band, bool passive)
अणु
	काष्ठा conf_scan_settings *c = &wl->conf.scan;
	पूर्णांक i, j;
	u32 flags;

	क्रम (i = 0, j = 0;
	     i < req->n_channels && j < WL1271_SCAN_MAX_CHANNELS;
	     i++) अणु
		flags = req->channels[i]->flags;

		अगर (!test_bit(i, wl->scan.scanned_ch) &&
		    !(flags & IEEE80211_CHAN_DISABLED) &&
		    (req->channels[i]->band == band) &&
		    /*
		     * In passive scans, we scan all reमुख्यing
		     * channels, even अगर not marked as such.
		     * In active scans, we only scan channels not
		     * marked as passive.
		     */
		    (passive || !(flags & IEEE80211_CHAN_NO_IR))) अणु
			wl1271_debug(DEBUG_SCAN, "band %d, center_freq %d ",
				     req->channels[i]->band,
				     req->channels[i]->center_freq);
			wl1271_debug(DEBUG_SCAN, "hw_value %d, flags %X",
				     req->channels[i]->hw_value,
				     req->channels[i]->flags);
			wl1271_debug(DEBUG_SCAN,
				     "max_antenna_gain %d, max_power %d",
				     req->channels[i]->max_antenna_gain,
				     req->channels[i]->max_घातer);
			wl1271_debug(DEBUG_SCAN, "beacon_found %d",
				     req->channels[i]->beacon_found);

			अगर (!passive) अणु
				channels[j].min_duration =
					cpu_to_le32(c->min_dwell_समय_active);
				channels[j].max_duration =
					cpu_to_le32(c->max_dwell_समय_active);
			पूर्ण अन्यथा अणु
				channels[j].min_duration =
					cpu_to_le32(c->dwell_समय_passive);
				channels[j].max_duration =
					cpu_to_le32(c->dwell_समय_passive);
			पूर्ण
			channels[j].early_termination = 0;
			channels[j].tx_घातer_att = req->channels[i]->max_घातer;
			channels[j].channel = req->channels[i]->hw_value;

			स_रखो(&channels[j].bssid_lsb, 0xff, 4);
			स_रखो(&channels[j].bssid_msb, 0xff, 2);

			/* Mark the channels we alपढ़ोy used */
			set_bit(i, wl->scan.scanned_ch);

			j++;
		पूर्ण
	पूर्ण

	वापस j;
पूर्ण

#घोषणा WL1271_NOTHING_TO_SCAN 1

अटल पूर्णांक wl1271_scan_send(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			    क्रमागत nl80211_band band,
			    bool passive, u32 basic_rate)
अणु
	काष्ठा ieee80211_vअगर *vअगर = wl12xx_wlvअगर_to_vअगर(wlvअगर);
	काष्ठा wl1271_cmd_scan *cmd;
	काष्ठा wl1271_cmd_trigger_scan_to *trigger;
	पूर्णांक ret;
	u16 scan_options = 0;

	/* skip active scans अगर we करोn't have SSIDs */
	अगर (!passive && wl->scan.req->n_ssids == 0)
		वापस WL1271_NOTHING_TO_SCAN;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	trigger = kzalloc(माप(*trigger), GFP_KERNEL);
	अगर (!cmd || !trigger) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (wl->conf.scan.split_scan_समयout)
		scan_options |= WL1271_SCAN_OPT_SPLIT_SCAN;

	अगर (passive)
		scan_options |= WL1271_SCAN_OPT_PASSIVE;

	/* scan on the dev role अगर the regular one is not started */
	अगर (wlcore_is_p2p_mgmt(wlvअगर))
		cmd->params.role_id = wlvअगर->dev_role_id;
	अन्यथा
		cmd->params.role_id = wlvअगर->role_id;

	अगर (WARN_ON(cmd->params.role_id == WL12XX_INVALID_ROLE_ID)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	cmd->params.scan_options = cpu_to_le16(scan_options);

	cmd->params.n_ch = wl1271_get_scan_channels(wl, wl->scan.req,
						    cmd->channels,
						    band, passive);
	अगर (cmd->params.n_ch == 0) अणु
		ret = WL1271_NOTHING_TO_SCAN;
		जाओ out;
	पूर्ण

	cmd->params.tx_rate = cpu_to_le32(basic_rate);
	cmd->params.n_probe_reqs = wl->conf.scan.num_probe_reqs;
	cmd->params.tid_trigger = CONF_TX_AC_ANY_TID;
	cmd->params.scan_tag = WL1271_SCAN_DEFAULT_TAG;

	अगर (band == NL80211_BAND_2GHZ)
		cmd->params.band = WL1271_SCAN_BAND_2_4_GHZ;
	अन्यथा
		cmd->params.band = WL1271_SCAN_BAND_5_GHZ;

	अगर (wl->scan.ssid_len) अणु
		cmd->params.ssid_len = wl->scan.ssid_len;
		स_नकल(cmd->params.ssid, wl->scan.ssid, wl->scan.ssid_len);
	पूर्ण

	स_नकल(cmd->addr, vअगर->addr, ETH_ALEN);

	ret = wl12xx_cmd_build_probe_req(wl, wlvअगर,
					 cmd->params.role_id, band,
					 wl->scan.ssid, wl->scan.ssid_len,
					 wl->scan.req->ie,
					 wl->scan.req->ie_len, शून्य, 0, false);
	अगर (ret < 0) अणु
		wl1271_error("PROBE request template failed");
		जाओ out;
	पूर्ण

	trigger->समयout = cpu_to_le32(wl->conf.scan.split_scan_समयout);
	ret = wl1271_cmd_send(wl, CMD_TRIGGER_SCAN_TO, trigger,
			      माप(*trigger), 0);
	अगर (ret < 0) अणु
		wl1271_error("trigger scan to failed for hw scan");
		जाओ out;
	पूर्ण

	wl1271_dump(DEBUG_SCAN, "SCAN: ", cmd, माप(*cmd));

	ret = wl1271_cmd_send(wl, CMD_SCAN, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("SCAN failed");
		जाओ out;
	पूर्ण

out:
	kमुक्त(cmd);
	kमुक्त(trigger);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_scan_stop(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl1271_cmd_header *cmd = शून्य;
	पूर्णांक ret = 0;

	अगर (WARN_ON(wl->scan.state == WL1271_SCAN_STATE_IDLE))
		वापस -EINVAL;

	wl1271_debug(DEBUG_CMD, "cmd scan stop");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = wl1271_cmd_send(wl, CMD_STOP_SCAN, cmd,
			      माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("cmd stop_scan failed");
		जाओ out;
	पूर्ण
out:
	kमुक्त(cmd);
	वापस ret;
पूर्ण

व्योम wl1271_scan_sपंचांग(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret = 0;
	क्रमागत nl80211_band band;
	u32 rate, mask;

	चयन (wl->scan.state) अणु
	हाल WL1271_SCAN_STATE_IDLE:
		अवरोध;

	हाल WL1271_SCAN_STATE_2GHZ_ACTIVE:
		band = NL80211_BAND_2GHZ;
		mask = wlvअगर->bitrate_masks[band];
		अगर (wl->scan.req->no_cck) अणु
			mask &= ~CONF_TX_CCK_RATES;
			अगर (!mask)
				mask = CONF_TX_RATE_MASK_BASIC_P2P;
		पूर्ण
		rate = wl1271_tx_min_rate_get(wl, mask);
		ret = wl1271_scan_send(wl, wlvअगर, band, false, rate);
		अगर (ret == WL1271_NOTHING_TO_SCAN) अणु
			wl->scan.state = WL1271_SCAN_STATE_2GHZ_PASSIVE;
			wl1271_scan_sपंचांग(wl, wlvअगर);
		पूर्ण

		अवरोध;

	हाल WL1271_SCAN_STATE_2GHZ_PASSIVE:
		band = NL80211_BAND_2GHZ;
		mask = wlvअगर->bitrate_masks[band];
		अगर (wl->scan.req->no_cck) अणु
			mask &= ~CONF_TX_CCK_RATES;
			अगर (!mask)
				mask = CONF_TX_RATE_MASK_BASIC_P2P;
		पूर्ण
		rate = wl1271_tx_min_rate_get(wl, mask);
		ret = wl1271_scan_send(wl, wlvअगर, band, true, rate);
		अगर (ret == WL1271_NOTHING_TO_SCAN) अणु
			अगर (wl->enable_11a)
				wl->scan.state = WL1271_SCAN_STATE_5GHZ_ACTIVE;
			अन्यथा
				wl->scan.state = WL1271_SCAN_STATE_DONE;
			wl1271_scan_sपंचांग(wl, wlvअगर);
		पूर्ण

		अवरोध;

	हाल WL1271_SCAN_STATE_5GHZ_ACTIVE:
		band = NL80211_BAND_5GHZ;
		rate = wl1271_tx_min_rate_get(wl, wlvअगर->bitrate_masks[band]);
		ret = wl1271_scan_send(wl, wlvअगर, band, false, rate);
		अगर (ret == WL1271_NOTHING_TO_SCAN) अणु
			wl->scan.state = WL1271_SCAN_STATE_5GHZ_PASSIVE;
			wl1271_scan_sपंचांग(wl, wlvअगर);
		पूर्ण

		अवरोध;

	हाल WL1271_SCAN_STATE_5GHZ_PASSIVE:
		band = NL80211_BAND_5GHZ;
		rate = wl1271_tx_min_rate_get(wl, wlvअगर->bitrate_masks[band]);
		ret = wl1271_scan_send(wl, wlvअगर, band, true, rate);
		अगर (ret == WL1271_NOTHING_TO_SCAN) अणु
			wl->scan.state = WL1271_SCAN_STATE_DONE;
			wl1271_scan_sपंचांग(wl, wlvअगर);
		पूर्ण

		अवरोध;

	हाल WL1271_SCAN_STATE_DONE:
		wl->scan.failed = false;
		cancel_delayed_work(&wl->scan_complete_work);
		ieee80211_queue_delayed_work(wl->hw, &wl->scan_complete_work,
					     msecs_to_jअगरfies(0));
		अवरोध;

	शेष:
		wl1271_error("invalid scan state");
		अवरोध;
	पूर्ण

	अगर (ret < 0) अणु
		cancel_delayed_work(&wl->scan_complete_work);
		ieee80211_queue_delayed_work(wl->hw, &wl->scan_complete_work,
					     msecs_to_jअगरfies(0));
	पूर्ण
पूर्ण

अटल व्योम wl12xx_adjust_channels(काष्ठा wl1271_cmd_sched_scan_config *cmd,
				   काष्ठा wlcore_scan_channels *cmd_channels)
अणु
	स_नकल(cmd->passive, cmd_channels->passive, माप(cmd->passive));
	स_नकल(cmd->active, cmd_channels->active, माप(cmd->active));
	cmd->dfs = cmd_channels->dfs;
	cmd->n_pactive_ch = cmd_channels->passive_active;

	स_नकल(cmd->channels_2, cmd_channels->channels_2,
	       माप(cmd->channels_2));
	स_नकल(cmd->channels_5, cmd_channels->channels_5,
	       माप(cmd->channels_5));
	/* channels_4 are not supported, so no need to copy them */
पूर्ण

पूर्णांक wl1271_scan_sched_scan_config(काष्ठा wl1271 *wl,
				  काष्ठा wl12xx_vअगर *wlvअगर,
				  काष्ठा cfg80211_sched_scan_request *req,
				  काष्ठा ieee80211_scan_ies *ies)
अणु
	काष्ठा wl1271_cmd_sched_scan_config *cfg = शून्य;
	काष्ठा wlcore_scan_channels *cfg_channels = शून्य;
	काष्ठा conf_sched_scan_settings *c = &wl->conf.sched_scan;
	पूर्णांक i, ret;
	bool क्रमce_passive = !req->n_ssids;

	wl1271_debug(DEBUG_CMD, "cmd sched_scan scan config");

	cfg = kzalloc(माप(*cfg), GFP_KERNEL);
	अगर (!cfg)
		वापस -ENOMEM;

	cfg->role_id = wlvअगर->role_id;
	cfg->rssi_threshold = c->rssi_threshold;
	cfg->snr_threshold  = c->snr_threshold;
	cfg->n_probe_reqs = c->num_probe_reqs;
	/* cycles set to 0 it means infinite (until manually stopped) */
	cfg->cycles = 0;
	/* report APs when at least 1 is found */
	cfg->report_after = 1;
	/* करोn't stop scanning स्वतःmatically when something is found */
	cfg->terminate = 0;
	cfg->tag = WL1271_SCAN_DEFAULT_TAG;
	/* करोn't filter on BSS type */
	cfg->bss_type = SCAN_BSS_TYPE_ANY;
	/* currently NL80211 supports only a single पूर्णांकerval */
	क्रम (i = 0; i < SCAN_MAX_CYCLE_INTERVALS; i++)
		cfg->पूर्णांकervals[i] = cpu_to_le32(req->scan_plans[0].पूर्णांकerval *
						MSEC_PER_SEC);

	cfg->ssid_len = 0;
	ret = wlcore_scan_sched_scan_ssid_list(wl, wlvअगर, req);
	अगर (ret < 0)
		जाओ out;

	cfg->filter_type = ret;

	wl1271_debug(DEBUG_SCAN, "filter_type = %d", cfg->filter_type);

	cfg_channels = kzalloc(माप(*cfg_channels), GFP_KERNEL);
	अगर (!cfg_channels) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (!wlcore_set_scan_chan_params(wl, cfg_channels, req->channels,
					 req->n_channels, req->n_ssids,
					 SCAN_TYPE_PERIODIC)) अणु
		wl1271_error("scan channel list is empty");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	wl12xx_adjust_channels(cfg, cfg_channels);

	अगर (!क्रमce_passive && cfg->active[0]) अणु
		u8 band = NL80211_BAND_2GHZ;
		ret = wl12xx_cmd_build_probe_req(wl, wlvअगर,
						 wlvअगर->role_id, band,
						 req->ssids[0].ssid,
						 req->ssids[0].ssid_len,
						 ies->ies[band],
						 ies->len[band],
						 ies->common_ies,
						 ies->common_ie_len,
						 true);
		अगर (ret < 0) अणु
			wl1271_error("2.4GHz PROBE request template failed");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!क्रमce_passive && cfg->active[1]) अणु
		u8 band = NL80211_BAND_5GHZ;
		ret = wl12xx_cmd_build_probe_req(wl, wlvअगर,
						 wlvअगर->role_id, band,
						 req->ssids[0].ssid,
						 req->ssids[0].ssid_len,
						 ies->ies[band],
						 ies->len[band],
						 ies->common_ies,
						 ies->common_ie_len,
						 true);
		अगर (ret < 0) अणु
			wl1271_error("5GHz PROBE request template failed");
			जाओ out;
		पूर्ण
	पूर्ण

	wl1271_dump(DEBUG_SCAN, "SCAN_CFG: ", cfg, माप(*cfg));

	ret = wl1271_cmd_send(wl, CMD_CONNECTION_SCAN_CFG, cfg,
			      माप(*cfg), 0);
	अगर (ret < 0) अणु
		wl1271_error("SCAN configuration failed");
		जाओ out;
	पूर्ण
out:
	kमुक्त(cfg_channels);
	kमुक्त(cfg);
	वापस ret;
पूर्ण

पूर्णांक wl1271_scan_sched_scan_start(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl1271_cmd_sched_scan_start *start;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd periodic scan start");

	अगर (wlvअगर->bss_type != BSS_TYPE_STA_BSS)
		वापस -EOPNOTSUPP;

	अगर ((wl->quirks & WLCORE_QUIRK_NO_SCHED_SCAN_WHILE_CONN) &&
	    test_bit(WLVIF_FLAG_IN_USE, &wlvअगर->flags))
		वापस -EBUSY;

	start = kzalloc(माप(*start), GFP_KERNEL);
	अगर (!start)
		वापस -ENOMEM;

	start->role_id = wlvअगर->role_id;
	start->tag = WL1271_SCAN_DEFAULT_TAG;

	ret = wl1271_cmd_send(wl, CMD_START_PERIODIC_SCAN, start,
			      माप(*start), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send scan start command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(start);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_sched_scan_start(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर  *wlvअगर,
			    काष्ठा cfg80211_sched_scan_request *req,
			    काष्ठा ieee80211_scan_ies *ies)
अणु
	पूर्णांक ret;

	ret = wl1271_scan_sched_scan_config(wl, wlvअगर, req, ies);
	अगर (ret < 0)
		वापस ret;

	वापस wl1271_scan_sched_scan_start(wl, wlvअगर);
पूर्ण

व्योम wl12xx_scan_sched_scan_stop(काष्ठा wl1271 *wl,  काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl1271_cmd_sched_scan_stop *stop;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd periodic scan stop");

	/* FIXME: what to करो अगर alloc'ing to stop fails? */
	stop = kzalloc(माप(*stop), GFP_KERNEL);
	अगर (!stop) अणु
		wl1271_error("failed to alloc memory to send sched scan stop");
		वापस;
	पूर्ण

	stop->role_id = wlvअगर->role_id;
	stop->tag = WL1271_SCAN_DEFAULT_TAG;

	ret = wl1271_cmd_send(wl, CMD_STOP_PERIODIC_SCAN, stop,
			      माप(*stop), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send sched scan stop command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(stop);
पूर्ण

पूर्णांक wl12xx_scan_start(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		      काष्ठा cfg80211_scan_request *req)
अणु
	wl1271_scan_sपंचांग(wl, wlvअगर);
	वापस 0;
पूर्ण

व्योम wl12xx_scan_completed(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	wl1271_scan_sपंचांग(wl, wlvअगर);
पूर्ण
