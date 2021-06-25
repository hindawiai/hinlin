<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mac80211 glue code क्रम mac80211 ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 *
 * Based on:
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright (c) 2007-2009, Christian Lamparter <chunkeey@web.de>
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 *
 * Based on:
 * - the islsm (sofपंचांगac prism54) driver, which is:
 *   Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 * - stlc45xx driver
 *   Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 */

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <net/mac80211.h>

#समावेश "cw1200.h"
#समावेश "txrx.h"
#समावेश "hwbus.h"
#समावेश "fwio.h"
#समावेश "hwio.h"
#समावेश "bh.h"
#समावेश "sta.h"
#समावेश "scan.h"
#समावेश "debug.h"
#समावेश "pm.h"

MODULE_AUTHOR("Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>");
MODULE_DESCRIPTION("Softmac ST-Ericsson CW1200 common code");
MODULE_LICENSE("GPL");
MODULE_ALIAS("cw1200_core");

/* Accept MAC address of the क्रमm macaddr=0x00,0x80,0xE1,0x30,0x40,0x50 */
अटल u8 cw1200_mac_ढाँचा[ETH_ALEN] = अणु0x02, 0x80, 0xe1, 0x00, 0x00, 0x00पूर्ण;
module_param_array_named(macaddr, cw1200_mac_ढाँचा, byte, शून्य, 0444);
MODULE_PARM_DESC(macaddr, "Override platform_data MAC address");

अटल अक्षर *cw1200_sdd_path;
module_param(cw1200_sdd_path, अक्षरp, 0644);
MODULE_PARM_DESC(cw1200_sdd_path, "Override platform_data SDD file");
अटल पूर्णांक cw1200_refclk;
module_param(cw1200_refclk, पूर्णांक, 0644);
MODULE_PARM_DESC(cw1200_refclk, "Override platform_data reference clock");

पूर्णांक cw1200_घातer_mode = wsm_घातer_mode_quiescent;
module_param(cw1200_घातer_mode, पूर्णांक, 0644);
MODULE_PARM_DESC(cw1200_घातer_mode, "WSM power mode.  0 == active, 1 == doze, 2 == quiescent (default)");

#घोषणा RATETAB_ENT(_rate, _rateid, _flags)		\
	अणु						\
		.bitrate	= (_rate),		\
		.hw_value	= (_rateid),		\
		.flags		= (_flags),		\
	पूर्ण

अटल काष्ठा ieee80211_rate cw1200_rates[] = अणु
	RATETAB_ENT(10,  0,   0),
	RATETAB_ENT(20,  1,   0),
	RATETAB_ENT(55,  2,   0),
	RATETAB_ENT(110, 3,   0),
	RATETAB_ENT(60,  6,  0),
	RATETAB_ENT(90,  7,  0),
	RATETAB_ENT(120, 8,  0),
	RATETAB_ENT(180, 9,  0),
	RATETAB_ENT(240, 10, 0),
	RATETAB_ENT(360, 11, 0),
	RATETAB_ENT(480, 12, 0),
	RATETAB_ENT(540, 13, 0),
पूर्ण;

अटल काष्ठा ieee80211_rate cw1200_mcs_rates[] = अणु
	RATETAB_ENT(65,  14, IEEE80211_TX_RC_MCS),
	RATETAB_ENT(130, 15, IEEE80211_TX_RC_MCS),
	RATETAB_ENT(195, 16, IEEE80211_TX_RC_MCS),
	RATETAB_ENT(260, 17, IEEE80211_TX_RC_MCS),
	RATETAB_ENT(390, 18, IEEE80211_TX_RC_MCS),
	RATETAB_ENT(520, 19, IEEE80211_TX_RC_MCS),
	RATETAB_ENT(585, 20, IEEE80211_TX_RC_MCS),
	RATETAB_ENT(650, 21, IEEE80211_TX_RC_MCS),
पूर्ण;

#घोषणा cw1200_a_rates		(cw1200_rates + 4)
#घोषणा cw1200_a_rates_size	(ARRAY_SIZE(cw1200_rates) - 4)
#घोषणा cw1200_g_rates		(cw1200_rates + 0)
#घोषणा cw1200_g_rates_size	(ARRAY_SIZE(cw1200_rates))
#घोषणा cw1200_n_rates		(cw1200_mcs_rates)
#घोषणा cw1200_n_rates_size	(ARRAY_SIZE(cw1200_mcs_rates))


#घोषणा CHAN2G(_channel, _freq, _flags) अणु			\
	.band			= NL80211_BAND_2GHZ,		\
	.center_freq		= (_freq),			\
	.hw_value		= (_channel),			\
	.flags			= (_flags),			\
	.max_antenna_gain	= 0,				\
	.max_घातer		= 30,				\
पूर्ण

#घोषणा CHAN5G(_channel, _flags) अणु				\
	.band			= NL80211_BAND_5GHZ,		\
	.center_freq	= 5000 + (5 * (_channel)),		\
	.hw_value		= (_channel),			\
	.flags			= (_flags),			\
	.max_antenna_gain	= 0,				\
	.max_घातer		= 30,				\
पूर्ण

अटल काष्ठा ieee80211_channel cw1200_2ghz_chantable[] = अणु
	CHAN2G(1, 2412, 0),
	CHAN2G(2, 2417, 0),
	CHAN2G(3, 2422, 0),
	CHAN2G(4, 2427, 0),
	CHAN2G(5, 2432, 0),
	CHAN2G(6, 2437, 0),
	CHAN2G(7, 2442, 0),
	CHAN2G(8, 2447, 0),
	CHAN2G(9, 2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
पूर्ण;

अटल काष्ठा ieee80211_channel cw1200_5ghz_chantable[] = अणु
	CHAN5G(34, 0),		CHAN5G(36, 0),
	CHAN5G(38, 0),		CHAN5G(40, 0),
	CHAN5G(42, 0),		CHAN5G(44, 0),
	CHAN5G(46, 0),		CHAN5G(48, 0),
	CHAN5G(52, 0),		CHAN5G(56, 0),
	CHAN5G(60, 0),		CHAN5G(64, 0),
	CHAN5G(100, 0),		CHAN5G(104, 0),
	CHAN5G(108, 0),		CHAN5G(112, 0),
	CHAN5G(116, 0),		CHAN5G(120, 0),
	CHAN5G(124, 0),		CHAN5G(128, 0),
	CHAN5G(132, 0),		CHAN5G(136, 0),
	CHAN5G(140, 0),		CHAN5G(149, 0),
	CHAN5G(153, 0),		CHAN5G(157, 0),
	CHAN5G(161, 0),		CHAN5G(165, 0),
	CHAN5G(184, 0),		CHAN5G(188, 0),
	CHAN5G(192, 0),		CHAN5G(196, 0),
	CHAN5G(200, 0),		CHAN5G(204, 0),
	CHAN5G(208, 0),		CHAN5G(212, 0),
	CHAN5G(216, 0),
पूर्ण;

अटल काष्ठा ieee80211_supported_band cw1200_band_2ghz = अणु
	.channels = cw1200_2ghz_chantable,
	.n_channels = ARRAY_SIZE(cw1200_2ghz_chantable),
	.bitrates = cw1200_g_rates,
	.n_bitrates = cw1200_g_rates_size,
	.ht_cap = अणु
		.cap = IEEE80211_HT_CAP_GRN_FLD |
			(1 << IEEE80211_HT_CAP_RX_STBC_SHIFT) |
			IEEE80211_HT_CAP_MAX_AMSDU,
		.ht_supported = 1,
		.ampdu_factor = IEEE80211_HT_MAX_AMPDU_8K,
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE,
		.mcs = अणु
			.rx_mask[0] = 0xFF,
			.rx_highest = __cpu_to_le16(0x41),
			.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_supported_band cw1200_band_5ghz = अणु
	.channels = cw1200_5ghz_chantable,
	.n_channels = ARRAY_SIZE(cw1200_5ghz_chantable),
	.bitrates = cw1200_a_rates,
	.n_bitrates = cw1200_a_rates_size,
	.ht_cap = अणु
		.cap = IEEE80211_HT_CAP_GRN_FLD |
			(1 << IEEE80211_HT_CAP_RX_STBC_SHIFT) |
			IEEE80211_HT_CAP_MAX_AMSDU,
		.ht_supported = 1,
		.ampdu_factor = IEEE80211_HT_MAX_AMPDU_8K,
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE,
		.mcs = अणु
			.rx_mask[0] = 0xFF,
			.rx_highest = __cpu_to_le16(0x41),
			.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ cw1200_ttl[] = अणु
	1 * HZ,	/* VO */
	2 * HZ,	/* VI */
	5 * HZ, /* BE */
	10 * HZ	/* BK */
पूर्ण;

अटल स्थिर काष्ठा ieee80211_ops cw1200_ops = अणु
	.start			= cw1200_start,
	.stop			= cw1200_stop,
	.add_पूर्णांकerface		= cw1200_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= cw1200_हटाओ_पूर्णांकerface,
	.change_पूर्णांकerface	= cw1200_change_पूर्णांकerface,
	.tx			= cw1200_tx,
	.hw_scan		= cw1200_hw_scan,
	.set_tim		= cw1200_set_tim,
	.sta_notअगरy		= cw1200_sta_notअगरy,
	.sta_add		= cw1200_sta_add,
	.sta_हटाओ		= cw1200_sta_हटाओ,
	.set_key		= cw1200_set_key,
	.set_rts_threshold	= cw1200_set_rts_threshold,
	.config			= cw1200_config,
	.bss_info_changed	= cw1200_bss_info_changed,
	.prepare_multicast	= cw1200_prepare_multicast,
	.configure_filter	= cw1200_configure_filter,
	.conf_tx		= cw1200_conf_tx,
	.get_stats		= cw1200_get_stats,
	.ampdu_action		= cw1200_ampdu_action,
	.flush			= cw1200_flush,
#अगर_घोषित CONFIG_PM
	.suspend		= cw1200_wow_suspend,
	.resume			= cw1200_wow_resume,
#पूर्ण_अगर
	/* Intentionally not offloaded:					*/
	/*.channel_चयन	= cw1200_channel_चयन,		*/
	/*.reमुख्य_on_channel	= cw1200_reमुख्य_on_channel,		*/
	/*.cancel_reमुख्य_on_channel = cw1200_cancel_reमुख्य_on_channel,	*/
पूर्ण;

अटल पूर्णांक cw1200_ba_rx_tids = -1;
अटल पूर्णांक cw1200_ba_tx_tids = -1;
module_param(cw1200_ba_rx_tids, पूर्णांक, 0644);
module_param(cw1200_ba_tx_tids, पूर्णांक, 0644);
MODULE_PARM_DESC(cw1200_ba_rx_tids, "Block ACK RX TIDs");
MODULE_PARM_DESC(cw1200_ba_tx_tids, "Block ACK TX TIDs");

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा wiphy_wowlan_support cw1200_wowlan_support = अणु
	/* Support only क्रम limited wowlan functionalities */
	.flags = WIPHY_WOWLAN_ANY | WIPHY_WOWLAN_DISCONNECT,
पूर्ण;
#पूर्ण_अगर


अटल काष्ठा ieee80211_hw *cw1200_init_common(स्थिर u8 *macaddr,
						स्थिर bool have_5ghz)
अणु
	पूर्णांक i, band;
	काष्ठा ieee80211_hw *hw;
	काष्ठा cw1200_common *priv;

	hw = ieee80211_alloc_hw(माप(काष्ठा cw1200_common), &cw1200_ops);
	अगर (!hw)
		वापस शून्य;

	priv = hw->priv;
	priv->hw = hw;
	priv->hw_type = -1;
	priv->mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->rates = cw1200_rates; /* TODO: fetch from FW */
	priv->mcs_rates = cw1200_n_rates;
	अगर (cw1200_ba_rx_tids != -1)
		priv->ba_rx_tid_mask = cw1200_ba_rx_tids;
	अन्यथा
		priv->ba_rx_tid_mask = 0xFF; /* Enable RX BLKACK क्रम all TIDs */
	अगर (cw1200_ba_tx_tids != -1)
		priv->ba_tx_tid_mask = cw1200_ba_tx_tids;
	अन्यथा
		priv->ba_tx_tid_mask = 0xff; /* Enable TX BLKACK क्रम all TIDs */

	ieee80211_hw_set(hw, NEED_DTIM_BEFORE_ASSOC);
	ieee80211_hw_set(hw, TX_AMPDU_SETUP_IN_HW);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, CONNECTION_MONITOR);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, SUPPORTS_PS);

	hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
					  BIT(NL80211_IFTYPE_ADHOC) |
					  BIT(NL80211_IFTYPE_AP) |
					  BIT(NL80211_IFTYPE_MESH_POINT) |
					  BIT(NL80211_IFTYPE_P2P_CLIENT) |
					  BIT(NL80211_IFTYPE_P2P_GO);

#अगर_घोषित CONFIG_PM
	hw->wiphy->wowlan = &cw1200_wowlan_support;
#पूर्ण_अगर

	hw->wiphy->flags |= WIPHY_FLAG_AP_UAPSD;

	hw->queues = 4;

	priv->rts_threshold = -1;

	hw->max_rates = 8;
	hw->max_rate_tries = 15;
	hw->extra_tx_headroom = WSM_TX_EXTRA_HEADROOM +
		8;  /* TKIP IV */

	hw->sta_data_size = माप(काष्ठा cw1200_sta_priv);

	hw->wiphy->bands[NL80211_BAND_2GHZ] = &cw1200_band_2ghz;
	अगर (have_5ghz)
		hw->wiphy->bands[NL80211_BAND_5GHZ] = &cw1200_band_5ghz;

	/* Channel params have to be cleared beक्रमe रेजिस्टरing wiphy again */
	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		काष्ठा ieee80211_supported_band *sband = hw->wiphy->bands[band];
		अगर (!sband)
			जारी;
		क्रम (i = 0; i < sband->n_channels; i++) अणु
			sband->channels[i].flags = 0;
			sband->channels[i].max_antenna_gain = 0;
			sband->channels[i].max_घातer = 30;
		पूर्ण
	पूर्ण

	hw->wiphy->max_scan_ssids = 2;
	hw->wiphy->max_scan_ie_len = IEEE80211_MAX_DATA_LEN;

	अगर (macaddr)
		SET_IEEE80211_PERM_ADDR(hw, (u8 *)macaddr);
	अन्यथा
		SET_IEEE80211_PERM_ADDR(hw, cw1200_mac_ढाँचा);

	/* Fix up mac address अगर necessary */
	अगर (hw->wiphy->perm_addr[3] == 0 &&
	    hw->wiphy->perm_addr[4] == 0 &&
	    hw->wiphy->perm_addr[5] == 0) अणु
		get_अक्रमom_bytes(&hw->wiphy->perm_addr[3], 3);
	पूर्ण

	mutex_init(&priv->wsm_cmd_mux);
	mutex_init(&priv->conf_mutex);
	priv->workqueue = create_singlethपढ़ो_workqueue("cw1200_wq");
	अगर (!priv->workqueue) अणु
		ieee80211_मुक्त_hw(hw);
		वापस शून्य;
	पूर्ण

	sema_init(&priv->scan.lock, 1);
	INIT_WORK(&priv->scan.work, cw1200_scan_work);
	INIT_DELAYED_WORK(&priv->scan.probe_work, cw1200_probe_work);
	INIT_DELAYED_WORK(&priv->scan.समयout, cw1200_scan_समयout);
	INIT_DELAYED_WORK(&priv->clear_recent_scan_work,
			  cw1200_clear_recent_scan_work);
	INIT_DELAYED_WORK(&priv->join_समयout, cw1200_join_समयout);
	INIT_WORK(&priv->unjoin_work, cw1200_unjoin_work);
	INIT_WORK(&priv->join_complete_work, cw1200_join_complete_work);
	INIT_WORK(&priv->wep_key_work, cw1200_wep_key_work);
	INIT_WORK(&priv->tx_policy_upload_work, tx_policy_upload_work);
	spin_lock_init(&priv->event_queue_lock);
	INIT_LIST_HEAD(&priv->event_queue);
	INIT_WORK(&priv->event_handler, cw1200_event_handler);
	INIT_DELAYED_WORK(&priv->bss_loss_work, cw1200_bss_loss_work);
	INIT_WORK(&priv->bss_params_work, cw1200_bss_params_work);
	spin_lock_init(&priv->bss_loss_lock);
	spin_lock_init(&priv->ps_state_lock);
	INIT_WORK(&priv->set_cts_work, cw1200_set_cts_work);
	INIT_WORK(&priv->set_tim_work, cw1200_set_tim_work);
	INIT_WORK(&priv->multicast_start_work, cw1200_multicast_start_work);
	INIT_WORK(&priv->multicast_stop_work, cw1200_multicast_stop_work);
	INIT_WORK(&priv->link_id_work, cw1200_link_id_work);
	INIT_DELAYED_WORK(&priv->link_id_gc_work, cw1200_link_id_gc_work);
	INIT_WORK(&priv->linkid_reset_work, cw1200_link_id_reset);
	INIT_WORK(&priv->update_filtering_work, cw1200_update_filtering_work);
	INIT_WORK(&priv->set_beacon_wakeup_period_work,
		  cw1200_set_beacon_wakeup_period_work);
	समयr_setup(&priv->mcast_समयout, cw1200_mcast_समयout, 0);

	अगर (cw1200_queue_stats_init(&priv->tx_queue_stats,
				    CW1200_LINK_ID_MAX,
				    cw1200_skb_dtor,
				    priv)) अणु
		destroy_workqueue(priv->workqueue);
		ieee80211_मुक्त_hw(hw);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < 4; ++i) अणु
		अगर (cw1200_queue_init(&priv->tx_queue[i],
				      &priv->tx_queue_stats, i, 16,
				      cw1200_ttl[i])) अणु
			क्रम (; i > 0; i--)
				cw1200_queue_deinit(&priv->tx_queue[i - 1]);
			cw1200_queue_stats_deinit(&priv->tx_queue_stats);
			destroy_workqueue(priv->workqueue);
			ieee80211_मुक्त_hw(hw);
			वापस शून्य;
		पूर्ण
	पूर्ण

	init_रुकोqueue_head(&priv->channel_चयन_करोne);
	init_रुकोqueue_head(&priv->wsm_cmd_wq);
	init_रुकोqueue_head(&priv->wsm_startup_करोne);
	init_रुकोqueue_head(&priv->ps_mode_चयन_करोne);
	wsm_buf_init(&priv->wsm_cmd_buf);
	spin_lock_init(&priv->wsm_cmd.lock);
	priv->wsm_cmd.करोne = 1;
	tx_policy_init(priv);

	वापस hw;
पूर्ण

अटल पूर्णांक cw1200_रेजिस्टर_common(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	पूर्णांक err;

#अगर_घोषित CONFIG_PM
	err = cw1200_pm_init(&priv->pm_state, priv);
	अगर (err) अणु
		pr_err("Cannot init PM. (%d).\n",
		       err);
		वापस err;
	पूर्ण
#पूर्ण_अगर

	err = ieee80211_रेजिस्टर_hw(dev);
	अगर (err) अणु
		pr_err("Cannot register device (%d).\n",
		       err);
#अगर_घोषित CONFIG_PM
		cw1200_pm_deinit(&priv->pm_state);
#पूर्ण_अगर
		वापस err;
	पूर्ण

	cw1200_debug_init(priv);

	pr_info("Registered as '%s'\n", wiphy_name(dev->wiphy));
	वापस 0;
पूर्ण

अटल व्योम cw1200_मुक्त_common(काष्ठा ieee80211_hw *dev)
अणु
	ieee80211_मुक्त_hw(dev);
पूर्ण

अटल व्योम cw1200_unरेजिस्टर_common(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	पूर्णांक i;

	ieee80211_unरेजिस्टर_hw(dev);

	del_समयr_sync(&priv->mcast_समयout);
	cw1200_unरेजिस्टर_bh(priv);

	cw1200_debug_release(priv);

	mutex_destroy(&priv->conf_mutex);

	wsm_buf_deinit(&priv->wsm_cmd_buf);

	destroy_workqueue(priv->workqueue);
	priv->workqueue = शून्य;

	अगर (priv->sdd) अणु
		release_firmware(priv->sdd);
		priv->sdd = शून्य;
	पूर्ण

	क्रम (i = 0; i < 4; ++i)
		cw1200_queue_deinit(&priv->tx_queue[i]);

	cw1200_queue_stats_deinit(&priv->tx_queue_stats);
#अगर_घोषित CONFIG_PM
	cw1200_pm_deinit(&priv->pm_state);
#पूर्ण_अगर
पूर्ण

/* Clock is in KHz */
u32 cw1200_dpll_from_clk(u16 clk_khz)
अणु
	चयन (clk_khz) अणु
	हाल 0x32C8: /* 13000 KHz */
		वापस 0x1D89D241;
	हाल 0x3E80: /* 16000 KHz */
		वापस 0x000001E1;
	हाल 0x41A0: /* 16800 KHz */
		वापस 0x124931C1;
	हाल 0x4B00: /* 19200 KHz */
		वापस 0x00000191;
	हाल 0x5DC0: /* 24000 KHz */
		वापस 0x00000141;
	हाल 0x6590: /* 26000 KHz */
		वापस 0x0EC4F121;
	हाल 0x8340: /* 33600 KHz */
		वापस 0x092490E1;
	हाल 0x9600: /* 38400 KHz */
		वापस 0x100010C1;
	हाल 0x9C40: /* 40000 KHz */
		वापस 0x000000C1;
	हाल 0xBB80: /* 48000 KHz */
		वापस 0x000000A1;
	हाल 0xCB20: /* 52000 KHz */
		वापस 0x07627091;
	शेष:
		pr_err("Unknown Refclk freq (0x%04x), using 26000KHz\n",
		       clk_khz);
		वापस 0x0EC4F121;
	पूर्ण
पूर्ण

पूर्णांक cw1200_core_probe(स्थिर काष्ठा hwbus_ops *hwbus_ops,
		      काष्ठा hwbus_priv *hwbus,
		      काष्ठा device *pdev,
		      काष्ठा cw1200_common **core,
		      पूर्णांक ref_clk, स्थिर u8 *macaddr,
		      स्थिर अक्षर *sdd_path, bool have_5ghz)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा ieee80211_hw *dev;
	काष्ठा cw1200_common *priv;
	काष्ठा wsm_operational_mode mode = अणु
		.घातer_mode = cw1200_घातer_mode,
		.disable_more_flag_usage = true,
	पूर्ण;

	dev = cw1200_init_common(macaddr, have_5ghz);
	अगर (!dev)
		जाओ err;

	priv = dev->priv;
	priv->hw_refclk = ref_clk;
	अगर (cw1200_refclk)
		priv->hw_refclk = cw1200_refclk;

	priv->sdd_path = (अक्षर *)sdd_path;
	अगर (cw1200_sdd_path)
		priv->sdd_path = cw1200_sdd_path;

	priv->hwbus_ops = hwbus_ops;
	priv->hwbus_priv = hwbus;
	priv->pdev = pdev;
	SET_IEEE80211_DEV(priv->hw, pdev);

	/* Pass काष्ठा cw1200_common back up */
	*core = priv;

	err = cw1200_रेजिस्टर_bh(priv);
	अगर (err)
		जाओ err1;

	err = cw1200_load_firmware(priv);
	अगर (err)
		जाओ err2;

	अगर (रुको_event_पूर्णांकerruptible_समयout(priv->wsm_startup_करोne,
					     priv->firmware_पढ़ोy,
					     3*HZ) <= 0) अणु
		/* TODO: Need to find how to reset device
		   in QUEUE mode properly.
		*/
		pr_err("Timeout waiting on device startup\n");
		err = -ETIMEDOUT;
		जाओ err2;
	पूर्ण

	/* Set low-घातer mode. */
	wsm_set_operational_mode(priv, &mode);

	/* Enable multi-TX confirmation */
	wsm_use_multi_tx_conf(priv, true);

	err = cw1200_रेजिस्टर_common(dev);
	अगर (err)
		जाओ err2;

	वापस err;

err2:
	cw1200_unरेजिस्टर_bh(priv);
err1:
	cw1200_मुक्त_common(dev);
err:
	*core = शून्य;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(cw1200_core_probe);

व्योम cw1200_core_release(काष्ठा cw1200_common *self)
अणु
	/* Disable device पूर्णांकerrupts */
	self->hwbus_ops->lock(self->hwbus_priv);
	__cw1200_irq_enable(self, 0);
	self->hwbus_ops->unlock(self->hwbus_priv);

	/* And then clean up */
	cw1200_unरेजिस्टर_common(self->hw);
	cw1200_मुक्त_common(self->hw);
	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(cw1200_core_release);
