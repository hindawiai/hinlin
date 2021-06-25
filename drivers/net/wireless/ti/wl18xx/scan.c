<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2012 Texas Instruments. All rights reserved.
 */

#समावेश <linux/ieee80211.h>
#समावेश "scan.h"
#समावेश "../wlcore/debug.h"

अटल व्योम wl18xx_adjust_channels(काष्ठा wl18xx_cmd_scan_params *cmd,
				   काष्ठा wlcore_scan_channels *cmd_channels)
अणु
	स_नकल(cmd->passive, cmd_channels->passive, माप(cmd->passive));
	स_नकल(cmd->active, cmd_channels->active, माप(cmd->active));
	cmd->dfs = cmd_channels->dfs;
	cmd->passive_active = cmd_channels->passive_active;

	स_नकल(cmd->channels_2, cmd_channels->channels_2,
	       माप(cmd->channels_2));
	स_नकल(cmd->channels_5, cmd_channels->channels_5,
	       माप(cmd->channels_5));
	/* channels_4 are not supported, so no need to copy them */
पूर्ण

अटल पूर्णांक wl18xx_scan_send(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			    काष्ठा cfg80211_scan_request *req)
अणु
	काष्ठा wl18xx_cmd_scan_params *cmd;
	काष्ठा wlcore_scan_channels *cmd_channels = शून्य;
	पूर्णांक ret;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* scan on the dev role अगर the regular one is not started */
	अगर (wlcore_is_p2p_mgmt(wlvअगर))
		cmd->role_id = wlvअगर->dev_role_id;
	अन्यथा
		cmd->role_id = wlvअगर->role_id;

	अगर (WARN_ON(cmd->role_id == WL12XX_INVALID_ROLE_ID)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	cmd->scan_type = SCAN_TYPE_SEARCH;
	cmd->rssi_threshold = -127;
	cmd->snr_threshold = 0;

	cmd->bss_type = SCAN_BSS_TYPE_ANY;

	cmd->ssid_from_list = 0;
	cmd->filter = 0;
	cmd->add_broadcast = 0;

	cmd->urgency = 0;
	cmd->protect = 0;

	cmd->n_probe_reqs = wl->conf.scan.num_probe_reqs;
	cmd->terminate_after = 0;

	/* configure channels */
	WARN_ON(req->n_ssids > 1);

	cmd_channels = kzalloc(माप(*cmd_channels), GFP_KERNEL);
	अगर (!cmd_channels) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wlcore_set_scan_chan_params(wl, cmd_channels, req->channels,
				    req->n_channels, req->n_ssids,
				    SCAN_TYPE_SEARCH);
	wl18xx_adjust_channels(cmd, cmd_channels);

	/*
	 * all the cycles params (except total cycles) should
	 * reमुख्य 0 क्रम normal scan
	 */
	cmd->total_cycles = 1;

	अगर (req->no_cck)
		cmd->rate = WL18XX_SCAN_RATE_6;

	cmd->tag = WL1271_SCAN_DEFAULT_TAG;

	अगर (req->n_ssids) अणु
		cmd->ssid_len = req->ssids[0].ssid_len;
		स_नकल(cmd->ssid, req->ssids[0].ssid, cmd->ssid_len);
	पूर्ण

	/* TODO: per-band ies? */
	अगर (cmd->active[0]) अणु
		u8 band = NL80211_BAND_2GHZ;
		ret = wl12xx_cmd_build_probe_req(wl, wlvअगर,
				 cmd->role_id, band,
				 req->ssids ? req->ssids[0].ssid : शून्य,
				 req->ssids ? req->ssids[0].ssid_len : 0,
				 req->ie,
				 req->ie_len,
				 शून्य,
				 0,
				 false);
		अगर (ret < 0) अणु
			wl1271_error("2.4GHz PROBE request template failed");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (cmd->active[1] || cmd->dfs) अणु
		u8 band = NL80211_BAND_5GHZ;
		ret = wl12xx_cmd_build_probe_req(wl, wlvअगर,
				 cmd->role_id, band,
				 req->ssids ? req->ssids[0].ssid : शून्य,
				 req->ssids ? req->ssids[0].ssid_len : 0,
				 req->ie,
				 req->ie_len,
				 शून्य,
				 0,
				 false);
		अगर (ret < 0) अणु
			wl1271_error("5GHz PROBE request template failed");
			जाओ out;
		पूर्ण
	पूर्ण

	wl1271_dump(DEBUG_SCAN, "SCAN: ", cmd, माप(*cmd));

	ret = wl1271_cmd_send(wl, CMD_SCAN, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("SCAN failed");
		जाओ out;
	पूर्ण

out:
	kमुक्त(cmd_channels);
	kमुक्त(cmd);
	वापस ret;
पूर्ण

व्योम wl18xx_scan_completed(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	wl->scan.failed = false;
	cancel_delayed_work(&wl->scan_complete_work);
	ieee80211_queue_delayed_work(wl->hw, &wl->scan_complete_work,
				     msecs_to_jअगरfies(0));
पूर्ण

अटल
पूर्णांक wl18xx_scan_sched_scan_config(काष्ठा wl1271 *wl,
				  काष्ठा wl12xx_vअगर *wlvअगर,
				  काष्ठा cfg80211_sched_scan_request *req,
				  काष्ठा ieee80211_scan_ies *ies)
अणु
	काष्ठा wl18xx_cmd_scan_params *cmd;
	काष्ठा wlcore_scan_channels *cmd_channels = शून्य;
	काष्ठा conf_sched_scan_settings *c = &wl->conf.sched_scan;
	पूर्णांक ret;
	पूर्णांक filter_type;

	wl1271_debug(DEBUG_CMD, "cmd sched_scan scan config");

	filter_type = wlcore_scan_sched_scan_ssid_list(wl, wlvअगर, req);
	अगर (filter_type < 0)
		वापस filter_type;

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->role_id = wlvअगर->role_id;

	अगर (WARN_ON(cmd->role_id == WL12XX_INVALID_ROLE_ID)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	cmd->scan_type = SCAN_TYPE_PERIODIC;
	cmd->rssi_threshold = c->rssi_threshold;
	cmd->snr_threshold = c->snr_threshold;

	/* करोn't filter on BSS type */
	cmd->bss_type = SCAN_BSS_TYPE_ANY;

	cmd->ssid_from_list = 1;
	अगर (filter_type == SCAN_SSID_FILTER_LIST)
		cmd->filter = 1;
	cmd->add_broadcast = 0;

	cmd->urgency = 0;
	cmd->protect = 0;

	cmd->n_probe_reqs = c->num_probe_reqs;
	/* करोn't stop scanning स्वतःmatically when something is found */
	cmd->terminate_after = 0;

	cmd_channels = kzalloc(माप(*cmd_channels), GFP_KERNEL);
	अगर (!cmd_channels) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* configure channels */
	wlcore_set_scan_chan_params(wl, cmd_channels, req->channels,
				    req->n_channels, req->n_ssids,
				    SCAN_TYPE_PERIODIC);
	wl18xx_adjust_channels(cmd, cmd_channels);

	अगर (c->num_लघु_पूर्णांकervals && c->दीर्घ_पूर्णांकerval &&
	    c->दीर्घ_पूर्णांकerval > req->scan_plans[0].पूर्णांकerval * MSEC_PER_SEC) अणु
		cmd->लघु_cycles_msec =
			cpu_to_le16(req->scan_plans[0].पूर्णांकerval * MSEC_PER_SEC);
		cmd->दीर्घ_cycles_msec = cpu_to_le16(c->दीर्घ_पूर्णांकerval);
		cmd->लघु_cycles_count = c->num_लघु_पूर्णांकervals;
	पूर्ण अन्यथा अणु
		cmd->लघु_cycles_msec = 0;
		cmd->दीर्घ_cycles_msec =
			cpu_to_le16(req->scan_plans[0].पूर्णांकerval * MSEC_PER_SEC);
		cmd->लघु_cycles_count = 0;
	पूर्ण
	wl1271_debug(DEBUG_SCAN, "short_interval: %d, long_interval: %d, num_short: %d",
		     le16_to_cpu(cmd->लघु_cycles_msec),
		     le16_to_cpu(cmd->दीर्घ_cycles_msec),
		     cmd->लघु_cycles_count);

	cmd->total_cycles = 0;

	cmd->tag = WL1271_SCAN_DEFAULT_TAG;

	/* create a PERIODIC_SCAN_REPORT_EVENT whenever we've got a match */
	cmd->report_threshold = 1;
	cmd->terminate_on_report = 0;

	अगर (cmd->active[0]) अणु
		u8 band = NL80211_BAND_2GHZ;
		ret = wl12xx_cmd_build_probe_req(wl, wlvअगर,
				 cmd->role_id, band,
				 req->ssids ? req->ssids[0].ssid : शून्य,
				 req->ssids ? req->ssids[0].ssid_len : 0,
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

	अगर (cmd->active[1] || cmd->dfs) अणु
		u8 band = NL80211_BAND_5GHZ;
		ret = wl12xx_cmd_build_probe_req(wl, wlvअगर,
				 cmd->role_id, band,
				 req->ssids ? req->ssids[0].ssid : शून्य,
				 req->ssids ? req->ssids[0].ssid_len : 0,
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

	wl1271_dump(DEBUG_SCAN, "SCAN: ", cmd, माप(*cmd));

	ret = wl1271_cmd_send(wl, CMD_SCAN, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("SCAN failed");
		जाओ out;
	पूर्ण

out:
	kमुक्त(cmd_channels);
	kमुक्त(cmd);
	वापस ret;
पूर्ण

पूर्णांक wl18xx_sched_scan_start(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			    काष्ठा cfg80211_sched_scan_request *req,
			    काष्ठा ieee80211_scan_ies *ies)
अणु
	वापस wl18xx_scan_sched_scan_config(wl, wlvअगर, req, ies);
पूर्ण

अटल पूर्णांक __wl18xx_scan_stop(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			       u8 scan_type)
अणु
	काष्ठा wl18xx_cmd_scan_stop *stop;
	पूर्णांक ret;

	wl1271_debug(DEBUG_CMD, "cmd periodic scan stop");

	stop = kzalloc(माप(*stop), GFP_KERNEL);
	अगर (!stop) अणु
		wl1271_error("failed to alloc memory to send sched scan stop");
		वापस -ENOMEM;
	पूर्ण

	stop->role_id = wlvअगर->role_id;
	stop->scan_type = scan_type;

	ret = wl1271_cmd_send(wl, CMD_STOP_SCAN, stop, माप(*stop), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send sched scan stop command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(stop);
	वापस ret;
पूर्ण

व्योम wl18xx_scan_sched_scan_stop(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	__wl18xx_scan_stop(wl, wlvअगर, SCAN_TYPE_PERIODIC);
पूर्ण
पूर्णांक wl18xx_scan_start(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		      काष्ठा cfg80211_scan_request *req)
अणु
	वापस wl18xx_scan_send(wl, wlvअगर, req);
पूर्ण

पूर्णांक wl18xx_scan_stop(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	वापस __wl18xx_scan_stop(wl, wlvअगर, SCAN_TYPE_SEARCH);
पूर्ण
