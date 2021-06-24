<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश <linux/ieee80211.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "cmd.h"
#समावेश "scan.h"
#समावेश "acx.h"
#समावेश "tx.h"

व्योम wl1271_scan_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork;
	काष्ठा wl1271 *wl;
	काष्ठा wl12xx_vअगर *wlvअगर;
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = false,
	पूर्ण;
	पूर्णांक ret;

	dwork = to_delayed_work(work);
	wl = container_of(dwork, काष्ठा wl1271, scan_complete_work);

	wl1271_debug(DEBUG_SCAN, "Scanning complete");

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	अगर (wl->scan.state == WL1271_SCAN_STATE_IDLE)
		जाओ out;

	wlvअगर = wl->scan_wlvअगर;

	/*
	 * Rearm the tx watchकरोg just beक्रमe idling scan. This
	 * prevents just-finished scans from triggering the watchकरोg
	 */
	wl12xx_rearm_tx_watchकरोg_locked(wl);

	wl->scan.state = WL1271_SCAN_STATE_IDLE;
	स_रखो(wl->scan.scanned_ch, 0, माप(wl->scan.scanned_ch));
	wl->scan.req = शून्य;
	wl->scan_wlvअगर = शून्य;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	अगर (test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags)) अणु
		/* restore hardware connection monitoring ढाँचा */
		wl1271_cmd_build_ap_probe_req(wl, wlvअगर, wlvअगर->probereq);
	पूर्ण

	अगर (wl->scan.failed) अणु
		wl1271_info("Scan completed due to error.");
		wl12xx_queue_recovery_work(wl);
	पूर्ण

	wlcore_cmd_regकरोमुख्य_config_locked(wl);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

	ieee80211_scan_completed(wl->hw, &info);

out:
	mutex_unlock(&wl->mutex);

पूर्ण

अटल व्योम wlcore_started_vअगरs_iter(व्योम *data, u8 *mac,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	bool active = false;
	पूर्णांक *count = (पूर्णांक *)data;

	/*
	 * count active पूर्णांकerfaces according to पूर्णांकerface type.
	 * checking only bss_conf.idle is bad क्रम some हालs, e.g.
	 * we करोn't want to count sta in p2p_find as active पूर्णांकerface.
	 */
	चयन (wlvअगर->bss_type) अणु
	हाल BSS_TYPE_STA_BSS:
		अगर (test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags))
			active = true;
		अवरोध;

	हाल BSS_TYPE_AP_BSS:
		अगर (wlvअगर->wl->active_sta_count > 0)
			active = true;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (active)
		(*count)++;
पूर्ण

अटल पूर्णांक wlcore_count_started_vअगरs(काष्ठा wl1271 *wl)
अणु
	पूर्णांक count = 0;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(wl->hw,
					IEEE80211_IFACE_ITER_RESUME_ALL,
					wlcore_started_vअगरs_iter, &count);
	वापस count;
पूर्ण

अटल पूर्णांक
wlcore_scan_get_channels(काष्ठा wl1271 *wl,
			 काष्ठा ieee80211_channel *req_channels[],
			 u32 n_channels,
			 u32 n_ssids,
			 काष्ठा conn_scan_ch_params *channels,
			 u32 band, bool radar, bool passive,
			 पूर्णांक start, पूर्णांक max_channels,
			 u8 *n_pactive_ch,
			 पूर्णांक scan_type)
अणु
	पूर्णांक i, j;
	u32 flags;
	bool क्रमce_passive = !n_ssids;
	u32 min_dwell_समय_active, max_dwell_समय_active;
	u32 dwell_समय_passive, dwell_समय_dfs;

	/* configure dwell बार according to scan type */
	अगर (scan_type == SCAN_TYPE_SEARCH) अणु
		काष्ठा conf_scan_settings *c = &wl->conf.scan;
		bool active_vअगर_exists = !!wlcore_count_started_vअगरs(wl);

		min_dwell_समय_active = active_vअगर_exists ?
			c->min_dwell_समय_active :
			c->min_dwell_समय_active_दीर्घ;
		max_dwell_समय_active = active_vअगर_exists ?
			c->max_dwell_समय_active :
			c->max_dwell_समय_active_दीर्घ;
		dwell_समय_passive = c->dwell_समय_passive;
		dwell_समय_dfs = c->dwell_समय_dfs;
	पूर्ण अन्यथा अणु
		काष्ठा conf_sched_scan_settings *c = &wl->conf.sched_scan;
		u32 delta_per_probe;

		अगर (band == NL80211_BAND_5GHZ)
			delta_per_probe = c->dwell_समय_delta_per_probe_5;
		अन्यथा
			delta_per_probe = c->dwell_समय_delta_per_probe;

		min_dwell_समय_active = c->base_dwell_समय +
			 n_ssids * c->num_probe_reqs * delta_per_probe;

		max_dwell_समय_active = min_dwell_समय_active +
					c->max_dwell_समय_delta;
		dwell_समय_passive = c->dwell_समय_passive;
		dwell_समय_dfs = c->dwell_समय_dfs;
	पूर्ण
	min_dwell_समय_active = DIV_ROUND_UP(min_dwell_समय_active, 1000);
	max_dwell_समय_active = DIV_ROUND_UP(max_dwell_समय_active, 1000);
	dwell_समय_passive = DIV_ROUND_UP(dwell_समय_passive, 1000);
	dwell_समय_dfs = DIV_ROUND_UP(dwell_समय_dfs, 1000);

	क्रम (i = 0, j = start;
	     i < n_channels && j < max_channels;
	     i++) अणु
		flags = req_channels[i]->flags;

		अगर (क्रमce_passive)
			flags |= IEEE80211_CHAN_NO_IR;

		अगर ((req_channels[i]->band == band) &&
		    !(flags & IEEE80211_CHAN_DISABLED) &&
		    (!!(flags & IEEE80211_CHAN_RADAR) == radar) &&
		    /* अगर radar is set, we ignore the passive flag */
		    (radar ||
		     !!(flags & IEEE80211_CHAN_NO_IR) == passive)) अणु
			अगर (flags & IEEE80211_CHAN_RADAR) अणु
				channels[j].flags |= SCAN_CHANNEL_FLAGS_DFS;

				channels[j].passive_duration =
					cpu_to_le16(dwell_समय_dfs);
			पूर्ण अन्यथा अणु
				channels[j].passive_duration =
					cpu_to_le16(dwell_समय_passive);
			पूर्ण

			channels[j].min_duration =
				cpu_to_le16(min_dwell_समय_active);
			channels[j].max_duration =
				cpu_to_le16(max_dwell_समय_active);

			channels[j].tx_घातer_att = req_channels[i]->max_घातer;
			channels[j].channel = req_channels[i]->hw_value;

			अगर (n_pactive_ch &&
			    (band == NL80211_BAND_2GHZ) &&
			    (channels[j].channel >= 12) &&
			    (channels[j].channel <= 14) &&
			    (flags & IEEE80211_CHAN_NO_IR) &&
			    !क्रमce_passive) अणु
				/* pactive channels treated as DFS */
				channels[j].flags = SCAN_CHANNEL_FLAGS_DFS;

				/*
				 * n_pactive_ch is counted करोwn from the end of
				 * the passive channel list
				 */
				(*n_pactive_ch)++;
				wl1271_debug(DEBUG_SCAN, "n_pactive_ch = %d",
					     *n_pactive_ch);
			पूर्ण

			wl1271_debug(DEBUG_SCAN, "freq %d, ch. %d, flags 0x%x, power %d, min/max_dwell %d/%d%s%s",
				     req_channels[i]->center_freq,
				     req_channels[i]->hw_value,
				     req_channels[i]->flags,
				     req_channels[i]->max_घातer,
				     min_dwell_समय_active,
				     max_dwell_समय_active,
				     flags & IEEE80211_CHAN_RADAR ?
					", DFS" : "",
				     flags & IEEE80211_CHAN_NO_IR ?
					", NO-IR" : "");
			j++;
		पूर्ण
	पूर्ण

	वापस j - start;
पूर्ण

bool
wlcore_set_scan_chan_params(काष्ठा wl1271 *wl,
			    काष्ठा wlcore_scan_channels *cfg,
			    काष्ठा ieee80211_channel *channels[],
			    u32 n_channels,
			    u32 n_ssids,
			    पूर्णांक scan_type)
अणु
	u8 n_pactive_ch = 0;

	cfg->passive[0] =
		wlcore_scan_get_channels(wl,
					 channels,
					 n_channels,
					 n_ssids,
					 cfg->channels_2,
					 NL80211_BAND_2GHZ,
					 false, true, 0,
					 MAX_CHANNELS_2GHZ,
					 &n_pactive_ch,
					 scan_type);
	cfg->active[0] =
		wlcore_scan_get_channels(wl,
					 channels,
					 n_channels,
					 n_ssids,
					 cfg->channels_2,
					 NL80211_BAND_2GHZ,
					 false, false,
					 cfg->passive[0],
					 MAX_CHANNELS_2GHZ,
					 &n_pactive_ch,
					 scan_type);
	cfg->passive[1] =
		wlcore_scan_get_channels(wl,
					 channels,
					 n_channels,
					 n_ssids,
					 cfg->channels_5,
					 NL80211_BAND_5GHZ,
					 false, true, 0,
					 wl->max_channels_5,
					 &n_pactive_ch,
					 scan_type);
	cfg->dfs =
		wlcore_scan_get_channels(wl,
					 channels,
					 n_channels,
					 n_ssids,
					 cfg->channels_5,
					 NL80211_BAND_5GHZ,
					 true, true,
					 cfg->passive[1],
					 wl->max_channels_5,
					 &n_pactive_ch,
					 scan_type);
	cfg->active[1] =
		wlcore_scan_get_channels(wl,
					 channels,
					 n_channels,
					 n_ssids,
					 cfg->channels_5,
					 NL80211_BAND_5GHZ,
					 false, false,
					 cfg->passive[1] + cfg->dfs,
					 wl->max_channels_5,
					 &n_pactive_ch,
					 scan_type);

	/* 802.11j channels are not supported yet */
	cfg->passive[2] = 0;
	cfg->active[2] = 0;

	cfg->passive_active = n_pactive_ch;

	wl1271_debug(DEBUG_SCAN, "    2.4GHz: active %d passive %d",
		     cfg->active[0], cfg->passive[0]);
	wl1271_debug(DEBUG_SCAN, "    5GHz: active %d passive %d",
		     cfg->active[1], cfg->passive[1]);
	wl1271_debug(DEBUG_SCAN, "    DFS: %d", cfg->dfs);

	वापस  cfg->passive[0] || cfg->active[0] ||
		cfg->passive[1] || cfg->active[1] || cfg->dfs ||
		cfg->passive[2] || cfg->active[2];
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_set_scan_chan_params);

पूर्णांक wlcore_scan(काष्ठा wl1271 *wl, काष्ठा ieee80211_vअगर *vअगर,
		स्थिर u8 *ssid, माप_प्रकार ssid_len,
		काष्ठा cfg80211_scan_request *req)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);

	/*
	 * cfg80211 should guarantee that we करोn't get more channels
	 * than what we have रेजिस्टरed.
	 */
	BUG_ON(req->n_channels > WL1271_MAX_CHANNELS);

	अगर (wl->scan.state != WL1271_SCAN_STATE_IDLE)
		वापस -EBUSY;

	wl->scan.state = WL1271_SCAN_STATE_2GHZ_ACTIVE;

	अगर (ssid_len && ssid) अणु
		wl->scan.ssid_len = ssid_len;
		स_नकल(wl->scan.ssid, ssid, ssid_len);
	पूर्ण अन्यथा अणु
		wl->scan.ssid_len = 0;
	पूर्ण

	wl->scan_wlvअगर = wlvअगर;
	wl->scan.req = req;
	स_रखो(wl->scan.scanned_ch, 0, माप(wl->scan.scanned_ch));

	/* we assume failure so that समयout scenarios are handled correctly */
	wl->scan.failed = true;
	ieee80211_queue_delayed_work(wl->hw, &wl->scan_complete_work,
				     msecs_to_jअगरfies(WL1271_SCAN_TIMEOUT));

	wl->ops->scan_start(wl, wlvअगर, req);

	वापस 0;
पूर्ण
/* Returns the scan type to be used or a negative value on error */
पूर्णांक
wlcore_scan_sched_scan_ssid_list(काष्ठा wl1271 *wl,
				 काष्ठा wl12xx_vअगर *wlvअगर,
				 काष्ठा cfg80211_sched_scan_request *req)
अणु
	काष्ठा wl1271_cmd_sched_scan_ssid_list *cmd = शून्य;
	काष्ठा cfg80211_match_set *sets = req->match_sets;
	काष्ठा cfg80211_ssid *ssids = req->ssids;
	पूर्णांक ret = 0, type, i, j, n_match_ssids = 0;

	wl1271_debug((DEBUG_CMD | DEBUG_SCAN), "cmd sched scan ssid list");

	/* count the match sets that contain SSIDs */
	क्रम (i = 0; i < req->n_match_sets; i++)
		अगर (sets[i].ssid.ssid_len > 0)
			n_match_ssids++;

	/* No filter, no ssids or only bcast ssid */
	अगर (!n_match_ssids &&
	    (!req->n_ssids ||
	     (req->n_ssids == 1 && req->ssids[0].ssid_len == 0))) अणु
		type = SCAN_SSID_FILTER_ANY;
		जाओ out;
	पूर्ण

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->role_id = wlvअगर->role_id;
	अगर (!n_match_ssids) अणु
		/* No filter, with ssids */
		type = SCAN_SSID_FILTER_DISABLED;

		क्रम (i = 0; i < req->n_ssids; i++) अणु
			cmd->ssids[cmd->n_ssids].type = (ssids[i].ssid_len) ?
				SCAN_SSID_TYPE_HIDDEN : SCAN_SSID_TYPE_PUBLIC;
			cmd->ssids[cmd->n_ssids].len = ssids[i].ssid_len;
			स_नकल(cmd->ssids[cmd->n_ssids].ssid, ssids[i].ssid,
			       ssids[i].ssid_len);
			cmd->n_ssids++;
		पूर्ण
	पूर्ण अन्यथा अणु
		type = SCAN_SSID_FILTER_LIST;

		/* Add all SSIDs from the filters */
		क्रम (i = 0; i < req->n_match_sets; i++) अणु
			/* ignore sets without SSIDs */
			अगर (!sets[i].ssid.ssid_len)
				जारी;

			cmd->ssids[cmd->n_ssids].type = SCAN_SSID_TYPE_PUBLIC;
			cmd->ssids[cmd->n_ssids].len = sets[i].ssid.ssid_len;
			स_नकल(cmd->ssids[cmd->n_ssids].ssid,
			       sets[i].ssid.ssid, sets[i].ssid.ssid_len);
			cmd->n_ssids++;
		पूर्ण
		अगर ((req->n_ssids > 1) ||
		    (req->n_ssids == 1 && req->ssids[0].ssid_len > 0)) अणु
			/*
			 * Mark all the SSIDs passed in the SSID list as HIDDEN,
			 * so they're used in probe requests.
			 */
			क्रम (i = 0; i < req->n_ssids; i++) अणु
				अगर (!req->ssids[i].ssid_len)
					जारी;

				क्रम (j = 0; j < cmd->n_ssids; j++)
					अगर ((req->ssids[i].ssid_len ==
					     cmd->ssids[j].len) &&
					    !स_भेद(req->ssids[i].ssid,
						   cmd->ssids[j].ssid,
						   req->ssids[i].ssid_len)) अणु
						cmd->ssids[j].type =
							SCAN_SSID_TYPE_HIDDEN;
						अवरोध;
					पूर्ण
				/* Fail अगर SSID isn't present in the filters */
				अगर (j == cmd->n_ssids) अणु
					ret = -EINVAL;
					जाओ out_मुक्त;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	ret = wl1271_cmd_send(wl, CMD_CONNECTION_SCAN_SSID_CFG, cmd,
			      माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("cmd sched scan ssid list failed");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);
out:
	अगर (ret < 0)
		वापस ret;
	वापस type;
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_scan_sched_scan_ssid_list);

व्योम wlcore_scan_sched_scan_results(काष्ठा wl1271 *wl)
अणु
	wl1271_debug(DEBUG_SCAN, "got periodic scan results");

	ieee80211_sched_scan_results(wl->hw);
पूर्ण
EXPORT_SYMBOL_GPL(wlcore_scan_sched_scan_results);
