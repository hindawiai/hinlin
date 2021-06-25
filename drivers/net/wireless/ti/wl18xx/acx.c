<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2011 Texas Instruments Inc.
 */

#समावेश "../wlcore/cmd.h"
#समावेश "../wlcore/debug.h"
#समावेश "../wlcore/acx.h"

#समावेश "acx.h"
#समावेश "wl18xx.h"

पूर्णांक wl18xx_acx_host_अगर_cfg_biपंचांगap(काष्ठा wl1271 *wl, u32 host_cfg_biपंचांगap,
				  u32 sdio_blk_size, u32 extra_mem_blks,
				  u32 len_field_size)
अणु
	काष्ठा wl18xx_acx_host_config_biपंचांगap *biपंचांगap_conf;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx cfg bitmap %d blk %d spare %d field %d",
		     host_cfg_biपंचांगap, sdio_blk_size, extra_mem_blks,
		     len_field_size);

	biपंचांगap_conf = kzalloc(माप(*biपंचांगap_conf), GFP_KERNEL);
	अगर (!biपंचांगap_conf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	biपंचांगap_conf->host_cfg_biपंचांगap = cpu_to_le32(host_cfg_biपंचांगap);
	biपंचांगap_conf->host_sdio_block_size = cpu_to_le32(sdio_blk_size);
	biपंचांगap_conf->extra_mem_blocks = cpu_to_le32(extra_mem_blks);
	biपंचांगap_conf->length_field_size = cpu_to_le32(len_field_size);

	ret = wl1271_cmd_configure(wl, ACX_HOST_IF_CFG_BITMAP,
				   biपंचांगap_conf, माप(*biपंचांगap_conf));
	अगर (ret < 0) अणु
		wl1271_warning("wl1271 bitmap config opt failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(biपंचांगap_conf);

	वापस ret;
पूर्ण

पूर्णांक wl18xx_acx_set_checksum_state(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl18xx_acx_checksum_state *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx checksum state");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->checksum_state = CHECKSUM_OFFLOAD_ENABLED;

	ret = wl1271_cmd_configure(wl, ACX_CSUM_CONFIG, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set Tx checksum state: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl18xx_acx_clear_statistics(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl18xx_acx_clear_statistics *acx;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx clear statistics");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = wl1271_cmd_configure(wl, ACX_CLEAR_STATISTICS, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("failed to clear firmware statistics: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl18xx_acx_peer_ht_operation_mode(काष्ठा wl1271 *wl, u8 hlid, bool wide)
अणु
	काष्ठा wlcore_peer_ht_operation_mode *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx peer ht operation mode hlid %d bw %d",
		     hlid, wide);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->hlid = hlid;
	acx->bandwidth = wide ? WLCORE_BANDWIDTH_40MHZ : WLCORE_BANDWIDTH_20MHZ;

	ret = wl1271_cmd_configure(wl, ACX_PEER_HT_OPERATION_MODE_CFG, acx,
				   माप(*acx));

	अगर (ret < 0) अणु
		wl1271_warning("acx peer ht operation mode failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;

पूर्ण

/*
 * this command is basically the same as wl1271_acx_ht_capabilities,
 * with the addition of supported rates. they should be unअगरied in
 * the next fw api change
 */
पूर्णांक wl18xx_acx_set_peer_cap(काष्ठा wl1271 *wl,
			    काष्ठा ieee80211_sta_ht_cap *ht_cap,
			    bool allow_ht_operation,
			    u32 rate_set, u8 hlid)
अणु
	काष्ठा wlcore_acx_peer_cap *acx;
	पूर्णांक ret = 0;
	u32 ht_capabilites = 0;

	wl1271_debug(DEBUG_ACX,
		     "acx set cap ht_supp: %d ht_cap: %d rates: 0x%x",
		     ht_cap->ht_supported, ht_cap->cap, rate_set);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (allow_ht_operation && ht_cap->ht_supported) अणु
		/* no need to translate capabilities - use the spec values */
		ht_capabilites = ht_cap->cap;

		/*
		 * this bit is not employed by the spec but only by FW to
		 * indicate peer HT support
		 */
		ht_capabilites |= WL12XX_HT_CAP_HT_OPERATION;

		/* get data from A-MPDU parameters field */
		acx->ampdu_max_length = ht_cap->ampdu_factor;
		acx->ampdu_min_spacing = ht_cap->ampdu_density;
	पूर्ण

	acx->hlid = hlid;
	acx->ht_capabilites = cpu_to_le32(ht_capabilites);
	acx->supported_rates = cpu_to_le32(rate_set);

	ret = wl1271_cmd_configure(wl, ACX_PEER_CAP, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx ht capabilities setting failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

/*
 * When the host is suspended, we करोn't want to get any fast-link/PSM
 * notअगरications
 */
पूर्णांक wl18xx_acx_पूर्णांकerrupt_notअगरy_config(काष्ठा wl1271 *wl,
				       bool action)
अणु
	काष्ठा wl18xx_acx_पूर्णांकerrupt_notअगरy *acx;
	पूर्णांक ret = 0;

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->enable = action;
	ret = wl1271_cmd_configure(wl, ACX_INTERRUPT_NOTIFY, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx interrupt notify setting failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

/*
 * When the host is suspended, we can configure the FW to disable RX BA
 * notअगरications.
 */
पूर्णांक wl18xx_acx_rx_ba_filter(काष्ठा wl1271 *wl, bool action)
अणु
	काष्ठा wl18xx_acx_rx_ba_filter *acx;
	पूर्णांक ret = 0;

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->enable = (u32)action;
	ret = wl1271_cmd_configure(wl, ACX_RX_BA_FILTER, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx rx ba activity filter setting failed: %d",
			       ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl18xx_acx_ap_sleep(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl18xx_priv *priv = wl->priv;
	काष्ठा acx_ap_sleep_cfg *acx;
	काष्ठा conf_ap_sleep_settings *conf = &priv->conf.ap_sleep;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx config ap sleep");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->idle_duty_cycle = conf->idle_duty_cycle;
	acx->connected_duty_cycle = conf->connected_duty_cycle;
	acx->max_stations_thresh = conf->max_stations_thresh;
	acx->idle_conn_thresh = conf->idle_conn_thresh;

	ret = wl1271_cmd_configure(wl, ACX_AP_SLEEP_CFG, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx config ap-sleep failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl18xx_acx_dynamic_fw_traces(काष्ठा wl1271 *wl)
अणु
	काष्ठा acx_dynamic_fw_traces_cfg *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx dynamic fw traces config %d",
		     wl->dynamic_fw_traces);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->dynamic_fw_traces = cpu_to_le32(wl->dynamic_fw_traces);

	ret = wl1271_cmd_configure(wl, ACX_DYNAMIC_TRACES_CFG,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx config dynamic fw traces failed: %d", ret);
		जाओ out;
	पूर्ण
out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl18xx_acx_समय_sync_cfg(काष्ठा wl1271 *wl)
अणु
	काष्ठा acx_समय_sync_cfg *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx time sync cfg: mode %d, addr: %pM",
		     wl->conf.sg.params[WL18XX_CONF_SG_TIME_SYNC],
		     wl->zone_master_mac_addr);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->sync_mode = wl->conf.sg.params[WL18XX_CONF_SG_TIME_SYNC];
	स_नकल(acx->zone_mac_addr, wl->zone_master_mac_addr, ETH_ALEN);

	ret = wl1271_cmd_configure(wl, ACX_TIME_SYNC_CFG,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx time sync cfg failed: %d", ret);
		जाओ out;
	पूर्ण
out:
	kमुक्त(acx);
	वापस ret;
पूर्ण
