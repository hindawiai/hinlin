<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश "acx.h"

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "wl12xx_80211.h"
#समावेश "hw_ops.h"

पूर्णांक wl1271_acx_wake_up_conditions(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				  u8 wake_up_event, u8 listen_पूर्णांकerval)
अणु
	काष्ठा acx_wake_up_condition *wake_up;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx wake up conditions (wake_up_event %d listen_interval %d)",
		     wake_up_event, listen_पूर्णांकerval);

	wake_up = kzalloc(माप(*wake_up), GFP_KERNEL);
	अगर (!wake_up) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wake_up->role_id = wlvअगर->role_id;
	wake_up->wake_up_event = wake_up_event;
	wake_up->listen_पूर्णांकerval = listen_पूर्णांकerval;

	ret = wl1271_cmd_configure(wl, ACX_WAKE_UP_CONDITIONS,
				   wake_up, माप(*wake_up));
	अगर (ret < 0) अणु
		wl1271_warning("could not set wake up conditions: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(wake_up);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_sleep_auth(काष्ठा wl1271 *wl, u8 sleep_auth)
अणु
	काष्ठा acx_sleep_auth *auth;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx sleep auth %d", sleep_auth);

	auth = kzalloc(माप(*auth), GFP_KERNEL);
	अगर (!auth) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	auth->sleep_auth = sleep_auth;

	ret = wl1271_cmd_configure(wl, ACX_SLEEP_AUTH, auth, माप(*auth));
	अगर (ret < 0) अणु
		wl1271_error("could not configure sleep_auth to %d: %d",
			     sleep_auth, ret);
		जाओ out;
	पूर्ण

	wl->sleep_auth = sleep_auth;
out:
	kमुक्त(auth);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_acx_sleep_auth);

पूर्णांक wl1271_acx_tx_घातer(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			पूर्णांक घातer)
अणु
	काष्ठा acx_current_tx_घातer *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx dot11_cur_tx_pwr %d", घातer);

	अगर (घातer < 0 || घातer > 25)
		वापस -EINVAL;

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->current_tx_घातer = घातer * 10;

	ret = wl1271_cmd_configure(wl, DOT11_CUR_TX_PWR, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("configure of tx power failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_feature_cfg(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा acx_feature_config *feature;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx feature cfg");

	feature = kzalloc(माप(*feature), GFP_KERNEL);
	अगर (!feature) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* DF_ENCRYPTION_DISABLE and DF_SNIFF_MODE_ENABLE are disabled */
	feature->role_id = wlvअगर->role_id;
	feature->data_flow_options = 0;
	feature->options = 0;

	ret = wl1271_cmd_configure(wl, ACX_FEATURE_CFG,
				   feature, माप(*feature));
	अगर (ret < 0) अणु
		wl1271_error("Couldn't set HW encryption");
		जाओ out;
	पूर्ण

out:
	kमुक्त(feature);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_mem_map(काष्ठा wl1271 *wl, काष्ठा acx_header *mem_map,
		       माप_प्रकार len)
अणु
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx mem map");

	ret = wl1271_cmd_पूर्णांकerrogate(wl, ACX_MEM_MAP, mem_map,
				     माप(काष्ठा acx_header), len);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1271_acx_rx_msdu_lअगरe_समय(काष्ठा wl1271 *wl)
अणु
	काष्ठा acx_rx_msdu_lअगरeसमय *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx rx msdu life time");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->lअगरeसमय = cpu_to_le32(wl->conf.rx.rx_msdu_lअगरe_समय);
	ret = wl1271_cmd_configure(wl, DOT11_RX_MSDU_LIFE_TIME,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set rx msdu life time: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_slot(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		    क्रमागत acx_slot_type slot_समय)
अणु
	काष्ठा acx_slot *slot;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx slot");

	slot = kzalloc(माप(*slot), GFP_KERNEL);
	अगर (!slot) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	slot->role_id = wlvअगर->role_id;
	slot->wone_index = STATION_WONE_INDEX;
	slot->slot_समय = slot_समय;

	ret = wl1271_cmd_configure(wl, ACX_SLOT, slot, माप(*slot));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set slot time: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(slot);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_group_address_tbl(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				 bool enable, व्योम *mc_list, u32 mc_list_len)
अणु
	काष्ठा acx_करोt11_grp_addr_tbl *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx group address tbl");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* MAC filtering */
	acx->role_id = wlvअगर->role_id;
	acx->enabled = enable;
	acx->num_groups = mc_list_len;
	स_नकल(acx->mac_table, mc_list, mc_list_len * ETH_ALEN);

	ret = wl1271_cmd_configure(wl, DOT11_GROUP_ADDRESS_TBL,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set group addr table: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_service_period_समयout(काष्ठा wl1271 *wl,
				      काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा acx_rx_समयout *rx_समयout;
	पूर्णांक ret;

	rx_समयout = kzalloc(माप(*rx_समयout), GFP_KERNEL);
	अगर (!rx_समयout) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_ACX, "acx service period timeout");

	rx_समयout->role_id = wlvअगर->role_id;
	rx_समयout->ps_poll_समयout = cpu_to_le16(wl->conf.rx.ps_poll_समयout);
	rx_समयout->upsd_समयout = cpu_to_le16(wl->conf.rx.upsd_समयout);

	ret = wl1271_cmd_configure(wl, ACX_SERVICE_PERIOD_TIMEOUT,
				   rx_समयout, माप(*rx_समयout));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set service period timeout: %d",
			       ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(rx_समयout);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_rts_threshold(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			     u32 rts_threshold)
अणु
	काष्ठा acx_rts_threshold *rts;
	पूर्णांक ret;

	/*
	 * If the RTS threshold is not configured or out of range, use the
	 * शेष value.
	 */
	अगर (rts_threshold > IEEE80211_MAX_RTS_THRESHOLD)
		rts_threshold = wl->conf.rx.rts_threshold;

	wl1271_debug(DEBUG_ACX, "acx rts threshold: %d", rts_threshold);

	rts = kzalloc(माप(*rts), GFP_KERNEL);
	अगर (!rts) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	rts->role_id = wlvअगर->role_id;
	rts->threshold = cpu_to_le16((u16)rts_threshold);

	ret = wl1271_cmd_configure(wl, DOT11_RTS_THRESHOLD, rts, माप(*rts));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set rts threshold: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(rts);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_dco_itrim_params(काष्ठा wl1271 *wl)
अणु
	काष्ठा acx_dco_itrim_params *dco;
	काष्ठा conf_itrim_settings *c = &wl->conf.itrim;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx dco itrim parameters");

	dco = kzalloc(माप(*dco), GFP_KERNEL);
	अगर (!dco) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	dco->enable = c->enable;
	dco->समयout = cpu_to_le32(c->समयout);

	ret = wl1271_cmd_configure(wl, ACX_SET_DCO_ITRIM_PARAMS,
				   dco, माप(*dco));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set dco itrim parameters: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(dco);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_beacon_filter_opt(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				 bool enable_filter)
अणु
	काष्ठा acx_beacon_filter_option *beacon_filter = शून्य;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx beacon filter opt enable=%d",
		     enable_filter);

	अगर (enable_filter &&
	    wl->conf.conn.bcn_filt_mode == CONF_BCN_FILT_MODE_DISABLED)
		जाओ out;

	beacon_filter = kzalloc(माप(*beacon_filter), GFP_KERNEL);
	अगर (!beacon_filter) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	beacon_filter->role_id = wlvअगर->role_id;
	beacon_filter->enable = enable_filter;

	/*
	 * When set to zero, and the filter is enabled, beacons
	 * without the unicast TIM bit set are dropped.
	 */
	beacon_filter->max_num_beacons = 0;

	ret = wl1271_cmd_configure(wl, ACX_BEACON_FILTER_OPT,
				   beacon_filter, माप(*beacon_filter));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set beacon filter opt: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(beacon_filter);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_beacon_filter_table(काष्ठा wl1271 *wl,
				   काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा acx_beacon_filter_ie_table *ie_table;
	पूर्णांक i, idx = 0;
	पूर्णांक ret;
	bool venकरोr_spec = false;

	wl1271_debug(DEBUG_ACX, "acx beacon filter table");

	ie_table = kzalloc(माप(*ie_table), GFP_KERNEL);
	अगर (!ie_table) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* configure शेष beacon pass-through rules */
	ie_table->role_id = wlvअगर->role_id;
	ie_table->num_ie = 0;
	क्रम (i = 0; i < wl->conf.conn.bcn_filt_ie_count; i++) अणु
		काष्ठा conf_bcn_filt_rule *r = &(wl->conf.conn.bcn_filt_ie[i]);
		ie_table->table[idx++] = r->ie;
		ie_table->table[idx++] = r->rule;

		अगर (r->ie == WLAN_EID_VENDOR_SPECIFIC) अणु
			/* only one venकरोr specअगरic ie allowed */
			अगर (venकरोr_spec)
				जारी;

			/* क्रम venकरोr specअगरic rules configure the
			   additional fields */
			स_नकल(&(ie_table->table[idx]), r->oui,
			       CONF_BCN_IE_OUI_LEN);
			idx += CONF_BCN_IE_OUI_LEN;
			ie_table->table[idx++] = r->type;
			स_नकल(&(ie_table->table[idx]), r->version,
			       CONF_BCN_IE_VER_LEN);
			idx += CONF_BCN_IE_VER_LEN;
			venकरोr_spec = true;
		पूर्ण

		ie_table->num_ie++;
	पूर्ण

	ret = wl1271_cmd_configure(wl, ACX_BEACON_FILTER_TABLE,
				   ie_table, माप(*ie_table));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set beacon filter table: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(ie_table);
	वापस ret;
पूर्ण

#घोषणा ACX_CONN_MONIT_DISABLE_VALUE  0xffffffff

पूर्णांक wl1271_acx_conn_monit_params(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				 bool enable)
अणु
	काष्ठा acx_conn_monit_params *acx;
	u32 threshold = ACX_CONN_MONIT_DISABLE_VALUE;
	u32 समयout = ACX_CONN_MONIT_DISABLE_VALUE;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx connection monitor parameters: %s",
		     enable ? "enabled" : "disabled");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (enable) अणु
		threshold = wl->conf.conn.synch_fail_thold;
		समयout = wl->conf.conn.bss_lose_समयout;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->synch_fail_thold = cpu_to_le32(threshold);
	acx->bss_lose_समयout = cpu_to_le32(समयout);

	ret = wl1271_cmd_configure(wl, ACX_CONN_MONIT_PARAMS,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set connection monitor "
			       "parameters: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण


पूर्णांक wl1271_acx_sg_enable(काष्ठा wl1271 *wl, bool enable)
अणु
	काष्ठा acx_bt_wlan_coex *pta;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx sg enable");

	pta = kzalloc(माप(*pta), GFP_KERNEL);
	अगर (!pta) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (enable)
		pta->enable = wl->conf.sg.state;
	अन्यथा
		pta->enable = CONF_SG_DISABLE;

	ret = wl1271_cmd_configure(wl, ACX_SG_ENABLE, pta, माप(*pta));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set softgemini enable: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(pta);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_acx_sg_cfg(काष्ठा wl1271 *wl)
अणु
	काष्ठा acx_bt_wlan_coex_param *param;
	काष्ठा conf_sg_settings *c = &wl->conf.sg;
	पूर्णांक i, ret;

	wl1271_debug(DEBUG_ACX, "acx sg cfg");

	param = kzalloc(माप(*param), GFP_KERNEL);
	अगर (!param) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* BT-WLAN coext parameters */
	क्रम (i = 0; i < WLCORE_CONF_SG_PARAMS_MAX; i++)
		param->params[i] = cpu_to_le32(c->params[i]);
	param->param_idx = WLCORE_CONF_SG_PARAMS_ALL;

	ret = wl1271_cmd_configure(wl, ACX_SG_CFG, param, माप(*param));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set sg config: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(param);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_cca_threshold(काष्ठा wl1271 *wl)
अणु
	काष्ठा acx_energy_detection *detection;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx cca threshold");

	detection = kzalloc(माप(*detection), GFP_KERNEL);
	अगर (!detection) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	detection->rx_cca_threshold = cpu_to_le16(wl->conf.rx.rx_cca_threshold);
	detection->tx_energy_detection = wl->conf.tx.tx_energy_detection;

	ret = wl1271_cmd_configure(wl, ACX_CCA_THRESHOLD,
				   detection, माप(*detection));
	अगर (ret < 0)
		wl1271_warning("failed to set cca threshold: %d", ret);

out:
	kमुक्त(detection);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_bcn_dtim_options(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा acx_beacon_broadcast *bb;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx bcn dtim options");

	bb = kzalloc(माप(*bb), GFP_KERNEL);
	अगर (!bb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	bb->role_id = wlvअगर->role_id;
	bb->beacon_rx_समयout = cpu_to_le16(wl->conf.conn.beacon_rx_समयout);
	bb->broadcast_समयout = cpu_to_le16(wl->conf.conn.broadcast_समयout);
	bb->rx_broadcast_in_ps = wl->conf.conn.rx_broadcast_in_ps;
	bb->ps_poll_threshold = wl->conf.conn.ps_poll_threshold;

	ret = wl1271_cmd_configure(wl, ACX_BCN_DTIM_OPTIONS, bb, माप(*bb));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set rx config: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(bb);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_aid(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर, u16 aid)
अणु
	काष्ठा acx_aid *acx_aid;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx aid");

	acx_aid = kzalloc(माप(*acx_aid), GFP_KERNEL);
	अगर (!acx_aid) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx_aid->role_id = wlvअगर->role_id;
	acx_aid->aid = cpu_to_le16(aid);

	ret = wl1271_cmd_configure(wl, ACX_AID, acx_aid, माप(*acx_aid));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set aid: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx_aid);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_event_mbox_mask(काष्ठा wl1271 *wl, u32 event_mask)
अणु
	काष्ठा acx_event_mask *mask;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx event mbox mask");

	mask = kzalloc(माप(*mask), GFP_KERNEL);
	अगर (!mask) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* high event mask is unused */
	mask->high_event_mask = cpu_to_le32(0xffffffff);
	mask->event_mask = cpu_to_le32(event_mask);

	ret = wl1271_cmd_configure(wl, ACX_EVENT_MBOX_MASK,
				   mask, माप(*mask));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set acx_event_mbox_mask: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(mask);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_set_preamble(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			    क्रमागत acx_preamble_type preamble)
अणु
	काष्ठा acx_preamble *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx_set_preamble");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->preamble = preamble;

	ret = wl1271_cmd_configure(wl, ACX_PREAMBLE_TYPE, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("Setting of preamble failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_cts_protect(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			   क्रमागत acx_ctsprotect_type ctsprotect)
अणु
	काष्ठा acx_ctsprotect *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx_set_ctsprotect");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->ctsprotect = ctsprotect;

	ret = wl1271_cmd_configure(wl, ACX_CTS_PROTECTION, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("Setting of ctsprotect failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_statistics(काष्ठा wl1271 *wl, व्योम *stats)
अणु
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx statistics");

	ret = wl1271_cmd_पूर्णांकerrogate(wl, ACX_STATISTICS, stats,
				     माप(काष्ठा acx_header),
				     wl->stats.fw_stats_len);
	अगर (ret < 0) अणु
		wl1271_warning("acx statistics failed: %d", ret);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wl1271_acx_sta_rate_policies(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा acx_rate_policy *acx;
	काष्ठा conf_tx_rate_class *c = &wl->conf.tx.sta_rc_conf;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx rate policies");

	acx = kzalloc(माप(*acx), GFP_KERNEL);

	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wl1271_debug(DEBUG_ACX, "basic_rate: 0x%x, full_rate: 0x%x",
		wlvअगर->basic_rate, wlvअगर->rate_set);

	/* configure one basic rate class */
	acx->rate_policy_idx = cpu_to_le32(wlvअगर->sta.basic_rate_idx);
	acx->rate_policy.enabled_rates = cpu_to_le32(wlvअगर->basic_rate);
	acx->rate_policy.लघु_retry_limit = c->लघु_retry_limit;
	acx->rate_policy.दीर्घ_retry_limit = c->दीर्घ_retry_limit;
	acx->rate_policy.aflags = c->aflags;

	ret = wl1271_cmd_configure(wl, ACX_RATE_POLICY, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("Setting of rate policies failed: %d", ret);
		जाओ out;
	पूर्ण

	/* configure one AP supported rate class */
	acx->rate_policy_idx = cpu_to_le32(wlvअगर->sta.ap_rate_idx);

	/* the AP policy is HW specअगरic */
	acx->rate_policy.enabled_rates =
		cpu_to_le32(wlcore_hw_sta_get_ap_rate_mask(wl, wlvअगर));
	acx->rate_policy.लघु_retry_limit = c->लघु_retry_limit;
	acx->rate_policy.दीर्घ_retry_limit = c->दीर्घ_retry_limit;
	acx->rate_policy.aflags = c->aflags;

	ret = wl1271_cmd_configure(wl, ACX_RATE_POLICY, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("Setting of rate policies failed: %d", ret);
		जाओ out;
	पूर्ण

	/*
	 * configure one rate class क्रम basic p2p operations.
	 * (p2p packets should always go out with OFDM rates, even
	 * अगर we are currently connected to 11b AP)
	 */
	acx->rate_policy_idx = cpu_to_le32(wlvअगर->sta.p2p_rate_idx);
	acx->rate_policy.enabled_rates =
				cpu_to_le32(CONF_TX_RATE_MASK_BASIC_P2P);
	acx->rate_policy.लघु_retry_limit = c->लघु_retry_limit;
	acx->rate_policy.दीर्घ_retry_limit = c->दीर्घ_retry_limit;
	acx->rate_policy.aflags = c->aflags;

	ret = wl1271_cmd_configure(wl, ACX_RATE_POLICY, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("Setting of rate policies failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_ap_rate_policy(काष्ठा wl1271 *wl, काष्ठा conf_tx_rate_class *c,
		      u8 idx)
अणु
	काष्ठा acx_rate_policy *acx;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx ap rate policy %d rates 0x%x",
		     idx, c->enabled_rates);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->rate_policy.enabled_rates = cpu_to_le32(c->enabled_rates);
	acx->rate_policy.लघु_retry_limit = c->लघु_retry_limit;
	acx->rate_policy.दीर्घ_retry_limit = c->दीर्घ_retry_limit;
	acx->rate_policy.aflags = c->aflags;

	acx->rate_policy_idx = cpu_to_le32(idx);

	ret = wl1271_cmd_configure(wl, ACX_RATE_POLICY, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("Setting of ap rate policy failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_ac_cfg(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		      u8 ac, u8 cw_min, u16 cw_max, u8 aअगरsn, u16 txop)
अणु
	काष्ठा acx_ac_cfg *acx;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx ac cfg %d cw_ming %d cw_max %d "
		     "aifs %d txop %d", ac, cw_min, cw_max, aअगरsn, txop);

	acx = kzalloc(माप(*acx), GFP_KERNEL);

	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->ac = ac;
	acx->cw_min = cw_min;
	acx->cw_max = cpu_to_le16(cw_max);
	acx->aअगरsn = aअगरsn;
	acx->tx_op_limit = cpu_to_le16(txop);

	ret = wl1271_cmd_configure(wl, ACX_AC_CFG, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx ac cfg failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_tid_cfg(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
		       u8 queue_id, u8 channel_type,
		       u8 tsid, u8 ps_scheme, u8 ack_policy,
		       u32 apsd_conf0, u32 apsd_conf1)
अणु
	काष्ठा acx_tid_config *acx;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx tid config");

	acx = kzalloc(माप(*acx), GFP_KERNEL);

	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->queue_id = queue_id;
	acx->channel_type = channel_type;
	acx->tsid = tsid;
	acx->ps_scheme = ps_scheme;
	acx->ack_policy = ack_policy;
	acx->apsd_conf[0] = cpu_to_le32(apsd_conf0);
	acx->apsd_conf[1] = cpu_to_le32(apsd_conf1);

	ret = wl1271_cmd_configure(wl, ACX_TID_CFG, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("Setting of tid config failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_frag_threshold(काष्ठा wl1271 *wl, u32 frag_threshold)
अणु
	काष्ठा acx_frag_threshold *acx;
	पूर्णांक ret = 0;

	/*
	 * If the fragmentation is not configured or out of range, use the
	 * शेष value.
	 */
	अगर (frag_threshold > IEEE80211_MAX_FRAG_THRESHOLD)
		frag_threshold = wl->conf.tx.frag_threshold;

	wl1271_debug(DEBUG_ACX, "acx frag threshold: %d", frag_threshold);

	acx = kzalloc(माप(*acx), GFP_KERNEL);

	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->frag_threshold = cpu_to_le16((u16)frag_threshold);
	ret = wl1271_cmd_configure(wl, ACX_FRAG_CFG, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("Setting of frag threshold failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_tx_config_options(काष्ठा wl1271 *wl)
अणु
	काष्ठा acx_tx_config_options *acx;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx tx config options");

	acx = kzalloc(माप(*acx), GFP_KERNEL);

	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->tx_compl_समयout = cpu_to_le16(wl->conf.tx.tx_compl_समयout);
	acx->tx_compl_threshold = cpu_to_le16(wl->conf.tx.tx_compl_threshold);
	ret = wl1271_cmd_configure(wl, ACX_TX_CONFIG_OPT, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("Setting of tx options failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_acx_mem_cfg(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_acx_config_memory *mem_conf;
	काष्ठा conf_memory_settings *mem;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "wl1271 mem cfg");

	mem_conf = kzalloc(माप(*mem_conf), GFP_KERNEL);
	अगर (!mem_conf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mem = &wl->conf.mem;

	/* memory config */
	mem_conf->num_stations = mem->num_stations;
	mem_conf->rx_mem_block_num = mem->rx_block_num;
	mem_conf->tx_min_mem_block_num = mem->tx_min_block_num;
	mem_conf->num_ssid_profiles = mem->ssid_profiles;
	mem_conf->total_tx_descriptors = cpu_to_le32(wl->num_tx_desc);
	mem_conf->dyn_mem_enable = mem->dynamic_memory;
	mem_conf->tx_मुक्त_req = mem->min_req_tx_blocks;
	mem_conf->rx_मुक्त_req = mem->min_req_rx_blocks;
	mem_conf->tx_min = mem->tx_min;
	mem_conf->fwlog_blocks = wl->conf.fwlog.mem_blocks;

	ret = wl1271_cmd_configure(wl, ACX_MEM_CFG, mem_conf,
				   माप(*mem_conf));
	अगर (ret < 0) अणु
		wl1271_warning("wl1271 mem config failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(mem_conf);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wl12xx_acx_mem_cfg);

पूर्णांक wl1271_acx_init_mem_config(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	wl->target_mem_map = kzalloc(माप(काष्ठा wl1271_acx_mem_map),
				     GFP_KERNEL);
	अगर (!wl->target_mem_map) अणु
		wl1271_error("couldn't allocate target memory map");
		वापस -ENOMEM;
	पूर्ण

	/* we now ask क्रम the firmware built memory map */
	ret = wl1271_acx_mem_map(wl, (व्योम *)wl->target_mem_map,
				 माप(काष्ठा wl1271_acx_mem_map));
	अगर (ret < 0) अणु
		wl1271_error("couldn't retrieve firmware memory map");
		kमुक्त(wl->target_mem_map);
		wl->target_mem_map = शून्य;
		वापस ret;
	पूर्ण

	/* initialize TX block book keeping */
	wl->tx_blocks_available =
		le32_to_cpu(wl->target_mem_map->num_tx_mem_blocks);
	wl1271_debug(DEBUG_TX, "available tx blocks: %d",
		     wl->tx_blocks_available);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_acx_init_mem_config);

पूर्णांक wl1271_acx_init_rx_पूर्णांकerrupt(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl1271_acx_rx_config_opt *rx_conf;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "wl1271 rx interrupt config");

	rx_conf = kzalloc(माप(*rx_conf), GFP_KERNEL);
	अगर (!rx_conf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	rx_conf->threshold = cpu_to_le16(wl->conf.rx.irq_pkt_threshold);
	rx_conf->समयout = cpu_to_le16(wl->conf.rx.irq_समयout);
	rx_conf->mblk_threshold = cpu_to_le16(wl->conf.rx.irq_blk_threshold);
	rx_conf->queue_type = wl->conf.rx.queue_type;

	ret = wl1271_cmd_configure(wl, ACX_RX_CONFIG_OPT, rx_conf,
				   माप(*rx_conf));
	अगर (ret < 0) अणु
		wl1271_warning("wl1271 rx config opt failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(rx_conf);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_bet_enable(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			  bool enable)
अणु
	काष्ठा wl1271_acx_bet_enable *acx = शून्य;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx bet enable");

	अगर (enable && wl->conf.conn.bet_enable == CONF_BET_MODE_DISABLE)
		जाओ out;

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->enable = enable ? CONF_BET_MODE_ENABLE : CONF_BET_MODE_DISABLE;
	acx->max_consecutive = wl->conf.conn.bet_max_consecutive;

	ret = wl1271_cmd_configure(wl, ACX_BET_ENABLE, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx bet enable failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_arp_ip_filter(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			     u8 enable, __be32 address)
अणु
	काष्ठा wl1271_acx_arp_filter *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx arp ip filter, enable: %d", enable);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->version = ACX_IPV4_VERSION;
	acx->enable = enable;

	अगर (enable)
		स_नकल(acx->address, &address, ACX_IPV4_ADDR_SIZE);

	ret = wl1271_cmd_configure(wl, ACX_ARP_IP_FILTER,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("failed to set arp ip filter: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_pm_config(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl1271_acx_pm_config *acx = शून्य;
	काष्ठा  conf_pm_config_settings *c = &wl->conf.pm_config;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx pm config");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->host_clk_settling_समय = cpu_to_le32(c->host_clk_settling_समय);
	acx->host_fast_wakeup_support = c->host_fast_wakeup_support;

	ret = wl1271_cmd_configure(wl, ACX_PM_CONFIG, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx pm config failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_acx_pm_config);

पूर्णांक wl1271_acx_keep_alive_mode(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			       bool enable)
अणु
	काष्ठा wl1271_acx_keep_alive_mode *acx = शून्य;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx keep alive mode: %d", enable);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->enabled = enable;

	ret = wl1271_cmd_configure(wl, ACX_KEEP_ALIVE_MODE, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx keep alive mode failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_keep_alive_config(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				 u8 index, u8 tpl_valid)
अणु
	काष्ठा wl1271_acx_keep_alive_config *acx = शून्य;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx keep alive config");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->period = cpu_to_le32(wl->conf.conn.keep_alive_पूर्णांकerval);
	acx->index = index;
	acx->tpl_validation = tpl_valid;
	acx->trigger = ACX_KEEP_ALIVE_NO_TX;

	ret = wl1271_cmd_configure(wl, ACX_SET_KEEP_ALIVE_CONFIG,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx keep alive config failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_rssi_snr_trigger(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
				bool enable, s16 thold, u8 hyst)
अणु
	काष्ठा wl1271_acx_rssi_snr_trigger *acx = शून्य;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx rssi snr trigger");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	wlvअगर->last_rssi_event = -1;

	acx->role_id = wlvअगर->role_id;
	acx->pacing = cpu_to_le16(wl->conf.roam_trigger.trigger_pacing);
	acx->metric = WL1271_ACX_TRIG_METRIC_RSSI_BEACON;
	acx->type = WL1271_ACX_TRIG_TYPE_EDGE;
	अगर (enable)
		acx->enable = WL1271_ACX_TRIG_ENABLE;
	अन्यथा
		acx->enable = WL1271_ACX_TRIG_DISABLE;

	acx->index = WL1271_ACX_TRIG_IDX_RSSI;
	acx->dir = WL1271_ACX_TRIG_सूची_BIसूची;
	acx->threshold = cpu_to_le16(thold);
	acx->hysteresis = hyst;

	ret = wl1271_cmd_configure(wl, ACX_RSSI_SNR_TRIGGER, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx rssi snr trigger setting failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_rssi_snr_avg_weights(काष्ठा wl1271 *wl,
				    काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl1271_acx_rssi_snr_avg_weights *acx = शून्य;
	काष्ठा conf_roam_trigger_settings *c = &wl->conf.roam_trigger;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx rssi snr avg weights");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->rssi_beacon = c->avg_weight_rssi_beacon;
	acx->rssi_data = c->avg_weight_rssi_data;
	acx->snr_beacon = c->avg_weight_snr_beacon;
	acx->snr_data = c->avg_weight_snr_data;

	ret = wl1271_cmd_configure(wl, ACX_RSSI_SNR_WEIGHTS, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx rssi snr trigger weights failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_set_ht_capabilities(काष्ठा wl1271 *wl,
				    काष्ठा ieee80211_sta_ht_cap *ht_cap,
				    bool allow_ht_operation, u8 hlid)
अणु
	काष्ठा wl1271_acx_ht_capabilities *acx;
	पूर्णांक ret = 0;
	u32 ht_capabilites = 0;

	wl1271_debug(DEBUG_ACX, "acx ht capabilities setting "
		     "sta supp: %d sta cap: %d", ht_cap->ht_supported,
		     ht_cap->cap);

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

	ret = wl1271_cmd_configure(wl, ACX_PEER_HT_CAP, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx ht capabilities setting failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_acx_set_ht_capabilities);


पूर्णांक wl1271_acx_set_ht_inक्रमmation(काष्ठा wl1271 *wl,
				   काष्ठा wl12xx_vअगर *wlvअगर,
				   u16 ht_operation_mode)
अणु
	काष्ठा wl1271_acx_ht_inक्रमmation *acx;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx ht information setting");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	acx->ht_protection =
		(u8)(ht_operation_mode & IEEE80211_HT_OP_MODE_PROTECTION);
	acx->rअगरs_mode = 0;
	acx->gf_protection =
		!!(ht_operation_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
	acx->ht_tx_burst_limit = 0;
	acx->dual_cts_protection = 0;

	ret = wl1271_cmd_configure(wl, ACX_HT_BSS_OPERATION, acx, माप(*acx));

	अगर (ret < 0) अणु
		wl1271_warning("acx ht information setting failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

/* Configure BA session initiator/receiver parameters setting in the FW. */
पूर्णांक wl12xx_acx_set_ba_initiator_policy(काष्ठा wl1271 *wl,
				       काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl1271_acx_ba_initiator_policy *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx ba initiator policy");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* set क्रम the current role */
	acx->role_id = wlvअगर->role_id;
	acx->tid_biपंचांगap = wl->conf.ht.tx_ba_tid_biपंचांगap;
	acx->win_size = wl->conf.ht.tx_ba_win_size;
	acx->inactivity_समयout = wl->conf.ht.inactivity_समयout;

	ret = wl1271_cmd_configure(wl,
				   ACX_BA_SESSION_INIT_POLICY,
				   acx,
				   माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx ba initiator policy failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

/* setup BA session receiver setting in the FW. */
पूर्णांक wl12xx_acx_set_ba_receiver_session(काष्ठा wl1271 *wl, u8 tid_index,
				       u16 ssn, bool enable, u8 peer_hlid,
				       u8 win_size)
अणु
	काष्ठा wl1271_acx_ba_receiver_setup *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx ba receiver session setting");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->hlid = peer_hlid;
	acx->tid = tid_index;
	acx->enable = enable;
	acx->win_size =	win_size;
	acx->ssn = ssn;

	ret = wlcore_cmd_configure_failsafe(wl, ACX_BA_SESSION_RX_SETUP, acx,
					    माप(*acx),
					    BIT(CMD_STATUS_NO_RX_BA_SESSION));
	अगर (ret < 0) अणु
		wl1271_warning("acx ba receiver session failed: %d", ret);
		जाओ out;
	पूर्ण

	/* someबार we can't start the session */
	अगर (ret == CMD_STATUS_NO_RX_BA_SESSION) अणु
		wl1271_warning("no fw rx ba on tid %d", tid_index);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = 0;
out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_acx_tsf_info(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			u64 *maस_समय)
अणु
	काष्ठा wl12xx_acx_fw_tsf_inक्रमmation *tsf_info;
	पूर्णांक ret;

	tsf_info = kzalloc(माप(*tsf_info), GFP_KERNEL);
	अगर (!tsf_info) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	tsf_info->role_id = wlvअगर->role_id;

	ret = wl1271_cmd_पूर्णांकerrogate(wl, ACX_TSF_INFO, tsf_info,
				माप(काष्ठा acx_header), माप(*tsf_info));
	अगर (ret < 0) अणु
		wl1271_warning("acx tsf info interrogate failed");
		जाओ out;
	पूर्ण

	*maस_समय = le32_to_cpu(tsf_info->current_tsf_low) |
		((u64) le32_to_cpu(tsf_info->current_tsf_high) << 32);

out:
	kमुक्त(tsf_info);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_ps_rx_streaming(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			       bool enable)
अणु
	काष्ठा wl1271_acx_ps_rx_streaming *rx_streaming;
	u32 conf_queues, enable_queues;
	पूर्णांक i, ret = 0;

	wl1271_debug(DEBUG_ACX, "acx ps rx streaming");

	rx_streaming = kzalloc(माप(*rx_streaming), GFP_KERNEL);
	अगर (!rx_streaming) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	conf_queues = wl->conf.rx_streaming.queues;
	अगर (enable)
		enable_queues = conf_queues;
	अन्यथा
		enable_queues = 0;

	क्रम (i = 0; i < 8; i++) अणु
		/*
		 * Skip non-changed queues, to aव्योम redundant acxs.
		 * this check assumes conf.rx_streaming.queues can't
		 * be changed जबतक rx_streaming is enabled.
		 */
		अगर (!(conf_queues & BIT(i)))
			जारी;

		rx_streaming->role_id = wlvअगर->role_id;
		rx_streaming->tid = i;
		rx_streaming->enable = enable_queues & BIT(i);
		rx_streaming->period = wl->conf.rx_streaming.पूर्णांकerval;
		rx_streaming->समयout = wl->conf.rx_streaming.पूर्णांकerval;

		ret = wl1271_cmd_configure(wl, ACX_PS_RX_STREAMING,
					   rx_streaming,
					   माप(*rx_streaming));
		अगर (ret < 0) अणु
			wl1271_warning("acx ps rx streaming failed: %d", ret);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	kमुक्त(rx_streaming);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_ap_max_tx_retry(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl1271_acx_ap_max_tx_retry *acx = शून्य;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx ap max tx retry");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->role_id = wlvअगर->role_id;
	acx->max_tx_retry = cpu_to_le16(wl->conf.tx.max_tx_retries);

	ret = wl1271_cmd_configure(wl, ACX_MAX_TX_FAILURE, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx ap max tx retry failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_acx_config_ps(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl1271_acx_config_ps *config_ps;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx config ps");

	config_ps = kzalloc(माप(*config_ps), GFP_KERNEL);
	अगर (!config_ps) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	config_ps->निकास_retries = wl->conf.conn.psm_निकास_retries;
	config_ps->enter_retries = wl->conf.conn.psm_entry_retries;
	config_ps->null_data_rate = cpu_to_le32(wlvअगर->basic_rate);

	ret = wl1271_cmd_configure(wl, ACX_CONFIG_PS, config_ps,
				   माप(*config_ps));

	अगर (ret < 0) अणु
		wl1271_warning("acx config ps failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(config_ps);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_set_inconnection_sta(काष्ठा wl1271 *wl,
				    काष्ठा wl12xx_vअगर *wlvअगर, u8 *addr)
अणु
	काष्ठा wl1271_acx_inconnection_sta *acx = शून्य;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx set inconnaction sta %pM", addr);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	स_नकल(acx->addr, addr, ETH_ALEN);
	acx->role_id = wlvअगर->role_id;

	ret = wl1271_cmd_configure(wl, ACX_UPDATE_INCONNECTION_STA_LIST,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx set inconnaction sta failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1271_acx_fm_coex(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl1271_acx_fm_coex *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx fm coex setting");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->enable = wl->conf.fm_coex.enable;
	acx->swallow_period = wl->conf.fm_coex.swallow_period;
	acx->n_भागider_fref_set_1 = wl->conf.fm_coex.n_भागider_fref_set_1;
	acx->n_भागider_fref_set_2 = wl->conf.fm_coex.n_भागider_fref_set_2;
	acx->m_भागider_fref_set_1 =
		cpu_to_le16(wl->conf.fm_coex.m_भागider_fref_set_1);
	acx->m_भागider_fref_set_2 =
		cpu_to_le16(wl->conf.fm_coex.m_भागider_fref_set_2);
	acx->coex_pll_stabilization_समय =
		cpu_to_le32(wl->conf.fm_coex.coex_pll_stabilization_समय);
	acx->lकरो_stabilization_समय =
		cpu_to_le16(wl->conf.fm_coex.lकरो_stabilization_समय);
	acx->fm_disturbed_band_margin =
		wl->conf.fm_coex.fm_disturbed_band_margin;
	acx->swallow_clk_dअगरf = wl->conf.fm_coex.swallow_clk_dअगरf;

	ret = wl1271_cmd_configure(wl, ACX_FM_COEX_CFG, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx fm coex setting failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_acx_set_rate_mgmt_params(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_acx_set_rate_mgmt_params *acx = शून्य;
	काष्ठा conf_rate_policy_settings *conf = &wl->conf.rate;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx set rate mgmt params");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->index = ACX_RATE_MGMT_ALL_PARAMS;
	acx->rate_retry_score = cpu_to_le16(conf->rate_retry_score);
	acx->per_add = cpu_to_le16(conf->per_add);
	acx->per_th1 = cpu_to_le16(conf->per_th1);
	acx->per_th2 = cpu_to_le16(conf->per_th2);
	acx->max_per = cpu_to_le16(conf->max_per);
	acx->inverse_curiosity_factor = conf->inverse_curiosity_factor;
	acx->tx_fail_low_th = conf->tx_fail_low_th;
	acx->tx_fail_high_th = conf->tx_fail_high_th;
	acx->per_alpha_shअगरt = conf->per_alpha_shअगरt;
	acx->per_add_shअगरt = conf->per_add_shअगरt;
	acx->per_beta1_shअगरt = conf->per_beta1_shअगरt;
	acx->per_beta2_shअगरt = conf->per_beta2_shअगरt;
	acx->rate_check_up = conf->rate_check_up;
	acx->rate_check_करोwn = conf->rate_check_करोwn;
	स_नकल(acx->rate_retry_policy, conf->rate_retry_policy,
	       माप(acx->rate_retry_policy));

	ret = wl1271_cmd_configure(wl, ACX_SET_RATE_MGMT_PARAMS,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx set rate mgmt params failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_acx_config_hangover(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_acx_config_hangover *acx;
	काष्ठा conf_hangover_settings *conf = &wl->conf.hangover;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx config hangover");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->recover_समय = cpu_to_le32(conf->recover_समय);
	acx->hangover_period = conf->hangover_period;
	acx->dynamic_mode = conf->dynamic_mode;
	acx->early_termination_mode = conf->early_termination_mode;
	acx->max_period = conf->max_period;
	acx->min_period = conf->min_period;
	acx->increase_delta = conf->increase_delta;
	acx->decrease_delta = conf->decrease_delta;
	acx->quiet_समय = conf->quiet_समय;
	acx->increase_समय = conf->increase_समय;
	acx->winकरोw_size = conf->winकरोw_size;

	ret = wl1271_cmd_configure(wl, ACX_CONFIG_HANGOVER, acx,
				   माप(*acx));

	अगर (ret < 0) अणु
		wl1271_warning("acx config hangover failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;

पूर्ण

पूर्णांक wlcore_acx_average_rssi(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर,
			    s8 *avg_rssi)
अणु
	काष्ठा acx_roaming_stats *acx;
	पूर्णांक ret = 0;

	wl1271_debug(DEBUG_ACX, "acx roaming statistics");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	acx->role_id = wlvअगर->role_id;
	ret = wl1271_cmd_पूर्णांकerrogate(wl, ACX_ROAMING_STATISTICS_TBL,
				     acx, माप(*acx), माप(*acx));
	अगर (ret	< 0) अणु
		wl1271_warning("acx roaming statistics failed: %d", ret);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	*avg_rssi = acx->rssi_beacon;
out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
/* Set the global behaviour of RX filters - On/Off + शेष action */
पूर्णांक wl1271_acx_शेष_rx_filter_enable(काष्ठा wl1271 *wl, bool enable,
					क्रमागत rx_filter_action action)
अणु
	काष्ठा acx_शेष_rx_filter *acx;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "acx default rx filter en: %d act: %d",
		     enable, action);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->enable = enable;
	acx->शेष_action = action;

	ret = wl1271_cmd_configure(wl, ACX_ENABLE_RX_DATA_FILTER, acx,
				   माप(*acx));
	अगर (ret < 0) अणु
		wl1271_warning("acx default rx filter enable failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

/* Configure or disable a specअगरic RX filter pattern */
पूर्णांक wl1271_acx_set_rx_filter(काष्ठा wl1271 *wl, u8 index, bool enable,
			     काष्ठा wl12xx_rx_filter *filter)
अणु
	काष्ठा acx_rx_filter_cfg *acx;
	पूर्णांक fields_size = 0;
	पूर्णांक acx_size;
	पूर्णांक ret;

	WARN_ON(enable && !filter);
	WARN_ON(index >= WL1271_MAX_RX_FILTERS);

	wl1271_debug(DEBUG_ACX,
		     "acx set rx filter idx: %d enable: %d filter: %p",
		     index, enable, filter);

	अगर (enable) अणु
		fields_size = wl1271_rx_filter_get_fields_size(filter);

		wl1271_debug(DEBUG_ACX, "act: %d num_fields: %d field_size: %d",
		      filter->action, filter->num_fields, fields_size);
	पूर्ण

	acx_size = ALIGN(माप(*acx) + fields_size, 4);
	acx = kzalloc(acx_size, GFP_KERNEL);

	अगर (!acx)
		वापस -ENOMEM;

	acx->enable = enable;
	acx->index = index;

	अगर (enable) अणु
		acx->num_fields = filter->num_fields;
		acx->action = filter->action;
		wl1271_rx_filter_flatten_fields(filter, acx->fields);
	पूर्ण

	wl1271_dump(DEBUG_ACX, "RX_FILTER: ", acx, acx_size);

	ret = wl1271_cmd_configure(wl, ACX_SET_RX_DATA_FILTER, acx, acx_size);
	अगर (ret < 0) अणु
		wl1271_warning("setting rx filter failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */
