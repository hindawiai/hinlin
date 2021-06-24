<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "debug.h"
#समावेश "init.h"
#समावेश "wl12xx_80211.h"
#समावेश "acx.h"
#समावेश "cmd.h"
#समावेश "tx.h"
#समावेश "io.h"
#समावेश "hw_ops.h"

पूर्णांक wl1271_init_ढाँचाs_config(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret, i;
	माप_प्रकार max_size;

	/* send empty ढाँचाs क्रम fw memory reservation */
	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      wl->scan_templ_id_2_4, शून्य,
				      WL1271_CMD_TEMPL_MAX_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      wl->scan_templ_id_5,
				      शून्य, WL1271_CMD_TEMPL_MAX_SIZE, 0,
				      WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	अगर (wl->quirks & WLCORE_QUIRK_DUAL_PROBE_TMPL) अणु
		ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
					      wl->sched_scan_templ_id_2_4,
					      शून्य,
					      WL1271_CMD_TEMPL_MAX_SIZE,
					      0, WL1271_RATE_AUTOMATIC);
		अगर (ret < 0)
			वापस ret;

		ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
					      wl->sched_scan_templ_id_5,
					      शून्य,
					      WL1271_CMD_TEMPL_MAX_SIZE,
					      0, WL1271_RATE_AUTOMATIC);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_शून्य_DATA, शून्य,
				      माप(काष्ठा wl12xx_null_data_ढाँचा),
				      0, WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_PS_POLL, शून्य,
				      माप(काष्ठा wl12xx_ps_poll_ढाँचा),
				      0, WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_QOS_शून्य_DATA, शून्य,
				      माप
				      (काष्ठा ieee80211_qos_hdr),
				      0, WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_PROBE_RESPONSE, शून्य,
				      WL1271_CMD_TEMPL_DFLT_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_BEACON, शून्य,
				      WL1271_CMD_TEMPL_DFLT_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	max_size = माप(काष्ठा wl12xx_arp_rsp_ढाँचा) +
		   WL1271_EXTRA_SPACE_MAX;
	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_ARP_RSP, शून्य,
				      max_size,
				      0, WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Put very large empty placeholders क्रम all ढाँचाs. These
	 * reserve memory क्रम later.
	 */
	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_AP_PROBE_RESPONSE, शून्य,
				      WL1271_CMD_TEMPL_MAX_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_AP_BEACON, शून्य,
				      WL1271_CMD_TEMPL_MAX_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_DEAUTH_AP, शून्य,
				      माप
				      (काष्ठा wl12xx_disconn_ढाँचा),
				      0, WL1271_RATE_AUTOMATIC);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < WLCORE_MAX_KLV_TEMPLATES; i++) अणु
		ret = wl1271_cmd_ढाँचा_set(wl, WL12XX_INVALID_ROLE_ID,
					      CMD_TEMPL_KLV, शून्य,
					      माप(काष्ठा ieee80211_qos_hdr),
					      i, WL1271_RATE_AUTOMATIC);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_ap_init_deauth_ढाँचा(काष्ठा wl1271 *wl,
					  काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	काष्ठा wl12xx_disconn_ढाँचा *पंचांगpl;
	पूर्णांक ret;
	u32 rate;

	पंचांगpl = kzalloc(माप(*पंचांगpl), GFP_KERNEL);
	अगर (!पंचांगpl) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	पंचांगpl->header.frame_ctl = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					     IEEE80211_STYPE_DEAUTH);

	rate = wl1271_tx_min_rate_get(wl, wlvअगर->basic_rate_set);
	ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
				      CMD_TEMPL_DEAUTH_AP,
				      पंचांगpl, माप(*पंचांगpl), 0, rate);

out:
	kमुक्त(पंचांगpl);
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_ap_init_null_ढाँचा(काष्ठा wl1271 *wl,
					काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा ieee80211_hdr_3addr *nullfunc;
	पूर्णांक ret;
	u32 rate;

	nullfunc = kzalloc(माप(*nullfunc), GFP_KERNEL);
	अगर (!nullfunc) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	nullfunc->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					      IEEE80211_STYPE_शून्यFUNC |
					      IEEE80211_FCTL_FROMDS);

	/* nullfunc->addr1 is filled by FW */

	स_नकल(nullfunc->addr2, vअगर->addr, ETH_ALEN);
	स_नकल(nullfunc->addr3, vअगर->addr, ETH_ALEN);

	rate = wl1271_tx_min_rate_get(wl, wlvअगर->basic_rate_set);
	ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
				      CMD_TEMPL_शून्य_DATA, nullfunc,
				      माप(*nullfunc), 0, rate);

out:
	kमुक्त(nullfunc);
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_ap_init_qos_null_ढाँचा(काष्ठा wl1271 *wl,
					    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा ieee80211_qos_hdr *qosnull;
	पूर्णांक ret;
	u32 rate;

	qosnull = kzalloc(माप(*qosnull), GFP_KERNEL);
	अगर (!qosnull) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	qosnull->frame_control = cpu_to_le16(IEEE80211_FTYPE_DATA |
					     IEEE80211_STYPE_QOS_शून्यFUNC |
					     IEEE80211_FCTL_FROMDS);

	/* qosnull->addr1 is filled by FW */

	स_नकल(qosnull->addr2, vअगर->addr, ETH_ALEN);
	स_नकल(qosnull->addr3, vअगर->addr, ETH_ALEN);

	rate = wl1271_tx_min_rate_get(wl, wlvअगर->basic_rate_set);
	ret = wl1271_cmd_ढाँचा_set(wl, wlvअगर->role_id,
				      CMD_TEMPL_QOS_शून्य_DATA, qosnull,
				      माप(*qosnull), 0, rate);

out:
	kमुक्त(qosnull);
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_init_rx_config(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	ret = wl1271_acx_rx_msdu_lअगरe_समय(wl);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wl12xx_init_phy_vअगर_config(काष्ठा wl1271 *wl,
					    काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;

	ret = wl1271_acx_slot(wl, wlvअगर, DEFAULT_SLOT_TIME);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_acx_service_period_समयout(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_acx_rts_threshold(wl, wlvअगर, wl->hw->wiphy->rts_threshold);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_init_sta_beacon_filter(काष्ठा wl1271 *wl,
					 काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;

	ret = wl1271_acx_beacon_filter_table(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	/* disable beacon filtering until we get the first beacon */
	ret = wl1271_acx_beacon_filter_opt(wl, wlvअगर, false);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1271_init_pta(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	ret = wl12xx_acx_sg_cfg(wl);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_acx_sg_enable(wl, wl->sg_enabled);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1271_init_energy_detection(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	ret = wl1271_acx_cca_threshold(wl);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_init_beacon_broadcast(काष्ठा wl1271 *wl,
					काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;

	ret = wl1271_acx_bcn_dtim_options(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wl12xx_init_fwlog(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	अगर (wl->quirks & WLCORE_QUIRK_FWLOG_NOT_IMPLEMENTED)
		वापस 0;

	ret = wl12xx_cmd_config_fwlog(wl);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* generic sta initialization (non vअगर-specअगरic) */
पूर्णांक wl1271_sta_hw_init(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;

	/* PS config */
	ret = wl12xx_acx_config_ps(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	/* FM WLAN coexistence */
	ret = wl1271_acx_fm_coex(wl);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_acx_sta_rate_policies(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_sta_hw_init_post_mem(काष्ठा wl1271 *wl,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret;

	/* disable the keep-alive feature */
	ret = wl1271_acx_keep_alive_mode(wl, wlvअगर, false);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* generic ap initialization (non vअगर-specअगरic) */
अटल पूर्णांक wl1271_ap_hw_init(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;

	ret = wl1271_init_ap_rates(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	/* configure AP sleep, अगर enabled */
	ret = wlcore_hw_ap_sleep(wl);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1271_ap_init_ढाँचाs(काष्ठा wl1271 *wl, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	पूर्णांक ret;

	ret = wl1271_ap_init_deauth_ढाँचा(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_ap_init_null_ढाँचा(wl, vअगर);
	अगर (ret < 0)
		वापस ret;

	ret = wl1271_ap_init_qos_null_ढाँचा(wl, vअगर);
	अगर (ret < 0)
		वापस ret;

	/*
	 * when operating as AP we want to receive बाह्यal beacons क्रम
	 * configuring ERP protection.
	 */
	ret = wl1271_acx_beacon_filter_opt(wl, wlvअगर, false);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_ap_hw_init_post_mem(काष्ठा wl1271 *wl,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	वापस wl1271_ap_init_ढाँचाs(wl, vअगर);
पूर्ण

पूर्णांक wl1271_init_ap_rates(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक i, ret;
	काष्ठा conf_tx_rate_class rc;
	u32 supported_rates;

	wl1271_debug(DEBUG_AP, "AP basic rate set: 0x%x",
		     wlvअगर->basic_rate_set);

	अगर (wlvअगर->basic_rate_set == 0)
		वापस -EINVAL;

	rc.enabled_rates = wlvअगर->basic_rate_set;
	rc.दीर्घ_retry_limit = 10;
	rc.लघु_retry_limit = 10;
	rc.aflags = 0;
	ret = wl1271_acx_ap_rate_policy(wl, &rc, wlvअगर->ap.mgmt_rate_idx);
	अगर (ret < 0)
		वापस ret;

	/* use the min basic rate क्रम AP broadcast/multicast */
	rc.enabled_rates = wl1271_tx_min_rate_get(wl, wlvअगर->basic_rate_set);
	rc.लघु_retry_limit = 10;
	rc.दीर्घ_retry_limit = 10;
	rc.aflags = 0;
	ret = wl1271_acx_ap_rate_policy(wl, &rc, wlvअगर->ap.bcast_rate_idx);
	अगर (ret < 0)
		वापस ret;

	/*
	 * If the basic rates contain OFDM rates, use OFDM only
	 * rates क्रम unicast TX as well. Else use all supported rates.
	 */
	अगर (wl->ofdm_only_ap && (wlvअगर->basic_rate_set & CONF_TX_OFDM_RATES))
		supported_rates = CONF_TX_OFDM_RATES;
	अन्यथा
		supported_rates = CONF_TX_ENABLED_RATES;

	/* unconditionally enable HT rates */
	supported_rates |= CONF_TX_MCS_RATES;

	/* get extra MIMO or wide-chan rates where the HW supports it */
	supported_rates |= wlcore_hw_ap_get_mimo_wide_rate_mask(wl, wlvअगर);

	/* configure unicast TX rate classes */
	क्रम (i = 0; i < wl->conf.tx.ac_conf_count; i++) अणु
		rc.enabled_rates = supported_rates;
		rc.लघु_retry_limit = 10;
		rc.दीर्घ_retry_limit = 10;
		rc.aflags = 0;
		ret = wl1271_acx_ap_rate_policy(wl, &rc,
						wlvअगर->ap.ucast_rate_idx[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1271_set_ba_policies(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	/* Reset the BA RX indicators */
	wlvअगर->ba_allowed = true;
	wl->ba_rx_session_count = 0;

	/* BA is supported in STA/AP modes */
	अगर (wlvअगर->bss_type != BSS_TYPE_AP_BSS &&
	    wlvअगर->bss_type != BSS_TYPE_STA_BSS) अणु
		wlvअगर->ba_support = false;
		वापस 0;
	पूर्ण

	wlvअगर->ba_support = true;

	/* 802.11n initiator BA session setting */
	वापस wl12xx_acx_set_ba_initiator_policy(wl, wlvअगर);
पूर्ण

/* vअगर-specअगरc initialization */
अटल पूर्णांक wl12xx_init_sta_role(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;

	ret = wl1271_acx_group_address_tbl(wl, wlvअगर, true, शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	/* Initialize connection monitoring thresholds */
	ret = wl1271_acx_conn_monit_params(wl, wlvअगर, false);
	अगर (ret < 0)
		वापस ret;

	/* Beacon filtering */
	ret = wl1271_init_sta_beacon_filter(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	/* Beacons and broadcast settings */
	ret = wl1271_init_beacon_broadcast(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	/* Configure rssi/snr averaging weights */
	ret = wl1271_acx_rssi_snr_avg_weights(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* vअगर-specअगरic initialization */
अटल पूर्णांक wl12xx_init_ap_role(काष्ठा wl1271 *wl, काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	पूर्णांक ret;

	ret = wl1271_acx_ap_max_tx_retry(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	/* initialize Tx घातer */
	ret = wl1271_acx_tx_घातer(wl, wlvअगर, wlvअगर->घातer_level);
	अगर (ret < 0)
		वापस ret;

	अगर (wl->radar_debug_mode)
		wlcore_cmd_generic_cfg(wl, wlvअगर,
				       WLCORE_CFG_FEATURE_RADAR_DEBUG,
				       wl->radar_debug_mode, 0);

	वापस 0;
पूर्ण

पूर्णांक wl1271_init_vअगर_specअगरic(काष्ठा wl1271 *wl, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wl12xx_vअगर *wlvअगर = wl12xx_vअगर_to_data(vअगर);
	काष्ठा conf_tx_ac_category *conf_ac;
	काष्ठा conf_tx_tid *conf_tid;
	bool is_ap = (wlvअगर->bss_type == BSS_TYPE_AP_BSS);
	पूर्णांक ret, i;

	/* consider all existing roles beक्रमe configuring psm. */

	अगर (wl->ap_count == 0 && is_ap) अणु /* first AP */
		ret = wl1271_acx_sleep_auth(wl, WL1271_PSM_ELP);
		अगर (ret < 0)
			वापस ret;

		/* unmask ap events */
		wl->event_mask |= wl->ap_event_mask;
		ret = wl1271_event_unmask(wl);
		अगर (ret < 0)
			वापस ret;
	/* first STA, no APs */
	पूर्ण अन्यथा अगर (wl->sta_count == 0 && wl->ap_count == 0 && !is_ap) अणु
		u8 sta_auth = wl->conf.conn.sta_sleep_auth;
		/* Configure क्रम घातer according to debugfs */
		अगर (sta_auth != WL1271_PSM_ILLEGAL)
			ret = wl1271_acx_sleep_auth(wl, sta_auth);
		/* Configure क्रम ELP घातer saving */
		अन्यथा
			ret = wl1271_acx_sleep_auth(wl, WL1271_PSM_ELP);

		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Mode specअगरic init */
	अगर (is_ap) अणु
		ret = wl1271_ap_hw_init(wl, wlvअगर);
		अगर (ret < 0)
			वापस ret;

		ret = wl12xx_init_ap_role(wl, wlvअगर);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = wl1271_sta_hw_init(wl, wlvअगर);
		अगर (ret < 0)
			वापस ret;

		ret = wl12xx_init_sta_role(wl, wlvअगर);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	wl12xx_init_phy_vअगर_config(wl, wlvअगर);

	/* Default TID/AC configuration */
	BUG_ON(wl->conf.tx.tid_conf_count != wl->conf.tx.ac_conf_count);
	क्रम (i = 0; i < wl->conf.tx.tid_conf_count; i++) अणु
		conf_ac = &wl->conf.tx.ac_conf[i];
		ret = wl1271_acx_ac_cfg(wl, wlvअगर, conf_ac->ac,
					conf_ac->cw_min, conf_ac->cw_max,
					conf_ac->aअगरsn, conf_ac->tx_op_limit);
		अगर (ret < 0)
			वापस ret;

		conf_tid = &wl->conf.tx.tid_conf[i];
		ret = wl1271_acx_tid_cfg(wl, wlvअगर,
					 conf_tid->queue_id,
					 conf_tid->channel_type,
					 conf_tid->tsid,
					 conf_tid->ps_scheme,
					 conf_tid->ack_policy,
					 conf_tid->apsd_conf[0],
					 conf_tid->apsd_conf[1]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Configure HW encryption */
	ret = wl1271_acx_feature_cfg(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	/* Mode specअगरic init - post mem init */
	अगर (is_ap)
		ret = wl1271_ap_hw_init_post_mem(wl, vअगर);
	अन्यथा
		ret = wl1271_sta_hw_init_post_mem(wl, vअगर);

	अगर (ret < 0)
		वापस ret;

	/* Configure initiator BA sessions policies */
	ret = wl1271_set_ba_policies(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	ret = wlcore_hw_init_vअगर(wl, wlvअगर);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1271_hw_init(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	/* Chip-specअगरic hw init */
	ret = wl->ops->hw_init(wl);
	अगर (ret < 0)
		वापस ret;

	/* Init ढाँचाs */
	ret = wl1271_init_ढाँचाs_config(wl);
	अगर (ret < 0)
		वापस ret;

	ret = wl12xx_acx_mem_cfg(wl);
	अगर (ret < 0)
		वापस ret;

	/* Configure the FW logger */
	ret = wl12xx_init_fwlog(wl);
	अगर (ret < 0)
		वापस ret;

	ret = wlcore_cmd_regकरोमुख्य_config_locked(wl);
	अगर (ret < 0)
		वापस ret;

	/* Bluetooth WLAN coexistence */
	ret = wl1271_init_pta(wl);
	अगर (ret < 0)
		वापस ret;

	/* Default memory configuration */
	ret = wl1271_acx_init_mem_config(wl);
	अगर (ret < 0)
		वापस ret;

	/* RX config */
	ret = wl12xx_init_rx_config(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	ret = wl1271_acx_dco_itrim_params(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* Configure TX patch complete पूर्णांकerrupt behavior */
	ret = wl1271_acx_tx_config_options(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* RX complete पूर्णांकerrupt pacing */
	ret = wl1271_acx_init_rx_पूर्णांकerrupt(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* Energy detection */
	ret = wl1271_init_energy_detection(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* Default fragmentation threshold */
	ret = wl1271_acx_frag_threshold(wl, wl->hw->wiphy->frag_threshold);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* Enable data path */
	ret = wl1271_cmd_data_path(wl, 1);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* configure PM */
	ret = wl1271_acx_pm_config(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	ret = wl12xx_acx_set_rate_mgmt_params(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* configure hangover */
	ret = wl12xx_acx_config_hangover(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	वापस 0;

 out_मुक्त_memmap:
	kमुक्त(wl->target_mem_map);
	wl->target_mem_map = शून्य;

	वापस ret;
पूर्ण
