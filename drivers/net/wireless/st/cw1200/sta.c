<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mac80211 STA API क्रम ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>

#समावेश "cw1200.h"
#समावेश "sta.h"
#समावेश "fwio.h"
#समावेश "bh.h"
#समावेश "debug.h"

#अगर_अघोषित ERP_INFO_BYTE_OFFSET
#घोषणा ERP_INFO_BYTE_OFFSET 2
#पूर्ण_अगर

अटल व्योम cw1200_करो_join(काष्ठा cw1200_common *priv);
अटल व्योम cw1200_करो_unjoin(काष्ठा cw1200_common *priv);

अटल पूर्णांक cw1200_upload_beacon(काष्ठा cw1200_common *priv);
अटल पूर्णांक cw1200_upload_pspoll(काष्ठा cw1200_common *priv);
अटल पूर्णांक cw1200_upload_null(काष्ठा cw1200_common *priv);
अटल पूर्णांक cw1200_upload_qosnull(काष्ठा cw1200_common *priv);
अटल पूर्णांक cw1200_start_ap(काष्ठा cw1200_common *priv);
अटल पूर्णांक cw1200_update_beaconing(काष्ठा cw1200_common *priv);
अटल पूर्णांक cw1200_enable_beaconing(काष्ठा cw1200_common *priv,
				   bool enable);
अटल व्योम __cw1200_sta_notअगरy(काष्ठा ieee80211_hw *dev,
				काष्ठा ieee80211_vअगर *vअगर,
				क्रमागत sta_notअगरy_cmd notअगरy_cmd,
				पूर्णांक link_id);
अटल पूर्णांक __cw1200_flush(काष्ठा cw1200_common *priv, bool drop);

अटल अंतरभूत व्योम __cw1200_मुक्त_event_queue(काष्ठा list_head *list)
अणु
	काष्ठा cw1200_wsm_event *event, *पंचांगp;
	list_क्रम_each_entry_safe(event, पंचांगp, list, link) अणु
		list_del(&event->link);
		kमुक्त(event);
	पूर्ण
पूर्ण

/* ******************************************************************** */
/* STA API								*/

पूर्णांक cw1200_start(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	पूर्णांक ret = 0;

	cw1200_pm_stay_awake(&priv->pm_state, HZ);

	mutex_lock(&priv->conf_mutex);

	/* शेष EDCA */
	WSM_EDCA_SET(&priv->edca, 0, 0x0002, 0x0003, 0x0007, 47, 0xc8, false);
	WSM_EDCA_SET(&priv->edca, 1, 0x0002, 0x0007, 0x000f, 94, 0xc8, false);
	WSM_EDCA_SET(&priv->edca, 2, 0x0003, 0x000f, 0x03ff, 0, 0xc8, false);
	WSM_EDCA_SET(&priv->edca, 3, 0x0007, 0x000f, 0x03ff, 0, 0xc8, false);
	ret = wsm_set_edca_params(priv, &priv->edca);
	अगर (ret)
		जाओ out;

	ret = cw1200_set_uapsd_param(priv, &priv->edca);
	अगर (ret)
		जाओ out;

	priv->setbssparams_करोne = false;

	स_नकल(priv->mac_addr, dev->wiphy->perm_addr, ETH_ALEN);
	priv->mode = NL80211_IFTYPE_MONITOR;
	priv->wep_शेष_key_id = -1;

	priv->cqm_beacon_loss_count = 10;

	ret = cw1200_setup_mac(priv);
	अगर (ret)
		जाओ out;

out:
	mutex_unlock(&priv->conf_mutex);
	वापस ret;
पूर्ण

व्योम cw1200_stop(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	LIST_HEAD(list);
	पूर्णांक i;

	wsm_lock_tx(priv);

	जबतक (करोwn_trylock(&priv->scan.lock)) अणु
		/* Scan is in progress. Force it to stop. */
		priv->scan.req = शून्य;
		schedule();
	पूर्ण
	up(&priv->scan.lock);

	cancel_delayed_work_sync(&priv->scan.probe_work);
	cancel_delayed_work_sync(&priv->scan.समयout);
	cancel_delayed_work_sync(&priv->clear_recent_scan_work);
	cancel_delayed_work_sync(&priv->join_समयout);
	cw1200_cqm_bssloss_sm(priv, 0, 0, 0);
	cancel_work_sync(&priv->unjoin_work);
	cancel_delayed_work_sync(&priv->link_id_gc_work);
	flush_workqueue(priv->workqueue);
	del_समयr_sync(&priv->mcast_समयout);
	mutex_lock(&priv->conf_mutex);
	priv->mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->listening = false;

	spin_lock(&priv->event_queue_lock);
	list_splice_init(&priv->event_queue, &list);
	spin_unlock(&priv->event_queue_lock);
	__cw1200_मुक्त_event_queue(&list);


	priv->join_status = CW1200_JOIN_STATUS_PASSIVE;
	priv->join_pending = false;

	क्रम (i = 0; i < 4; i++)
		cw1200_queue_clear(&priv->tx_queue[i]);
	mutex_unlock(&priv->conf_mutex);
	tx_policy_clean(priv);

	/* HACK! */
	अगर (atomic_xchg(&priv->tx_lock, 1) != 1)
		pr_debug("[STA] TX is force-unlocked due to stop request.\n");

	wsm_unlock_tx(priv);
	atomic_xchg(&priv->tx_lock, 0); /* क्रम recovery to work */
पूर्ण

अटल पूर्णांक cw1200_bssloss_mitigation = 1;
module_param(cw1200_bssloss_mitigation, पूर्णांक, 0644);
MODULE_PARM_DESC(cw1200_bssloss_mitigation, "BSS Loss mitigation. 0 == disabled, 1 == enabled (default)");


व्योम __cw1200_cqm_bssloss_sm(काष्ठा cw1200_common *priv,
			     पूर्णांक init, पूर्णांक good, पूर्णांक bad)
अणु
	पूर्णांक tx = 0;

	priv->delayed_link_loss = 0;
	cancel_work_sync(&priv->bss_params_work);

	pr_debug("[STA] CQM BSSLOSS_SM: state: %d init %d good %d bad: %d txlock: %d uj: %d\n",
		 priv->bss_loss_state,
		 init, good, bad,
		 atomic_पढ़ो(&priv->tx_lock),
		 priv->delayed_unjoin);

	/* If we have a pending unjoin */
	अगर (priv->delayed_unjoin)
		वापस;

	अगर (init) अणु
		queue_delayed_work(priv->workqueue,
				   &priv->bss_loss_work,
				   HZ);
		priv->bss_loss_state = 0;

		/* Skip the confimration procedure in P2P हाल */
		अगर (!priv->vअगर->p2p && !atomic_पढ़ो(&priv->tx_lock))
			tx = 1;
	पूर्ण अन्यथा अगर (good) अणु
		cancel_delayed_work_sync(&priv->bss_loss_work);
		priv->bss_loss_state = 0;
		queue_work(priv->workqueue, &priv->bss_params_work);
	पूर्ण अन्यथा अगर (bad) अणु
		/* XXX Should we just keep going until we समय out? */
		अगर (priv->bss_loss_state < 3)
			tx = 1;
	पूर्ण अन्यथा अणु
		cancel_delayed_work_sync(&priv->bss_loss_work);
		priv->bss_loss_state = 0;
	पूर्ण

	/* Bypass mitigation अगर it's disabled */
	अगर (!cw1200_bssloss_mitigation)
		tx = 0;

	/* Spit out a शून्य packet to our AP अगर necessary */
	अगर (tx) अणु
		काष्ठा sk_buff *skb;

		priv->bss_loss_state++;

		skb = ieee80211_nullfunc_get(priv->hw, priv->vअगर, false);
		WARN_ON(!skb);
		अगर (skb)
			cw1200_tx(priv->hw, शून्य, skb);
	पूर्ण
पूर्ण

पूर्णांक cw1200_add_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
			 काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक ret;
	काष्ठा cw1200_common *priv = dev->priv;
	/* __le32 स्वतः_calibration_mode = __cpu_to_le32(1); */

	vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER |
			     IEEE80211_VIF_SUPPORTS_UAPSD |
			     IEEE80211_VIF_SUPPORTS_CQM_RSSI;

	mutex_lock(&priv->conf_mutex);

	अगर (priv->mode != NL80211_IFTYPE_MONITOR) अणु
		mutex_unlock(&priv->conf_mutex);
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		priv->mode = vअगर->type;
		अवरोध;
	शेष:
		mutex_unlock(&priv->conf_mutex);
		वापस -EOPNOTSUPP;
	पूर्ण

	priv->vअगर = vअगर;
	स_नकल(priv->mac_addr, vअगर->addr, ETH_ALEN);
	ret = cw1200_setup_mac(priv);
	/* Enable स्वतः-calibration */
	/* Exception in subsequent channel चयन; disabled.
	 *  wsm_ग_लिखो_mib(priv, WSM_MIB_ID_SET_AUTO_CALIBRATION_MODE,
	 *      &स्वतः_calibration_mode, माप(स्वतः_calibration_mode));
	*/

	mutex_unlock(&priv->conf_mutex);
	वापस ret;
पूर्ण

व्योम cw1200_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
			     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	काष्ठा wsm_reset reset = अणु
		.reset_statistics = true,
	पूर्ण;
	पूर्णांक i;

	mutex_lock(&priv->conf_mutex);
	चयन (priv->join_status) अणु
	हाल CW1200_JOIN_STATUS_JOINING:
	हाल CW1200_JOIN_STATUS_PRE_STA:
	हाल CW1200_JOIN_STATUS_STA:
	हाल CW1200_JOIN_STATUS_IBSS:
		wsm_lock_tx(priv);
		अगर (queue_work(priv->workqueue, &priv->unjoin_work) <= 0)
			wsm_unlock_tx(priv);
		अवरोध;
	हाल CW1200_JOIN_STATUS_AP:
		क्रम (i = 0; priv->link_id_map; ++i) अणु
			अगर (priv->link_id_map & BIT(i)) अणु
				reset.link_id = i;
				wsm_reset(priv, &reset);
				priv->link_id_map &= ~BIT(i);
			पूर्ण
		पूर्ण
		स_रखो(priv->link_id_db, 0, माप(priv->link_id_db));
		priv->sta_asleep_mask = 0;
		priv->enable_beacon = false;
		priv->tx_multicast = false;
		priv->aid0_bit_set = false;
		priv->buffered_multicasts = false;
		priv->pspoll_mask = 0;
		reset.link_id = 0;
		wsm_reset(priv, &reset);
		अवरोध;
	हाल CW1200_JOIN_STATUS_MONITOR:
		cw1200_update_listening(priv, false);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	priv->vअगर = शून्य;
	priv->mode = NL80211_IFTYPE_MONITOR;
	eth_zero_addr(priv->mac_addr);
	स_रखो(&priv->p2p_ps_modeinfo, 0, माप(priv->p2p_ps_modeinfo));
	cw1200_मुक्त_keys(priv);
	cw1200_setup_mac(priv);
	priv->listening = false;
	priv->join_status = CW1200_JOIN_STATUS_PASSIVE;
	अगर (!__cw1200_flush(priv, true))
		wsm_unlock_tx(priv);

	mutex_unlock(&priv->conf_mutex);
पूर्ण

पूर्णांक cw1200_change_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
			    काष्ठा ieee80211_vअगर *vअगर,
			    क्रमागत nl80211_अगरtype new_type,
			    bool p2p)
अणु
	पूर्णांक ret = 0;
	pr_debug("change_interface new: %d (%d), old: %d (%d)\n", new_type,
		 p2p, vअगर->type, vअगर->p2p);

	अगर (new_type != vअगर->type || vअगर->p2p != p2p) अणु
		cw1200_हटाओ_पूर्णांकerface(dev, vअगर);
		vअगर->type = new_type;
		vअगर->p2p = p2p;
		ret = cw1200_add_पूर्णांकerface(dev, vअगर);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cw1200_config(काष्ठा ieee80211_hw *dev, u32 changed)
अणु
	पूर्णांक ret = 0;
	काष्ठा cw1200_common *priv = dev->priv;
	काष्ठा ieee80211_conf *conf = &dev->conf;

	pr_debug("CONFIG CHANGED:  %08x\n", changed);

	करोwn(&priv->scan.lock);
	mutex_lock(&priv->conf_mutex);
	/* TODO: IEEE80211_CONF_CHANGE_QOS */
	/* TODO: IEEE80211_CONF_CHANGE_LISTEN_INTERVAL */

	अगर (changed & IEEE80211_CONF_CHANGE_POWER) अणु
		priv->output_घातer = conf->घातer_level;
		pr_debug("[STA] TX power: %d\n", priv->output_घातer);
		wsm_set_output_घातer(priv, priv->output_घातer * 10);
	पूर्ण

	अगर ((changed & IEEE80211_CONF_CHANGE_CHANNEL) &&
	    (priv->channel != conf->chandef.chan)) अणु
		काष्ठा ieee80211_channel *ch = conf->chandef.chan;
		काष्ठा wsm_चयन_channel channel = अणु
			.channel_number = ch->hw_value,
		पूर्ण;
		pr_debug("[STA] Freq %d (wsm ch: %d).\n",
			 ch->center_freq, ch->hw_value);

		/* __cw1200_flush() implicitly locks tx, अगर successful */
		अगर (!__cw1200_flush(priv, false)) अणु
			अगर (!wsm_चयन_channel(priv, &channel)) अणु
				ret = रुको_event_समयout(priv->channel_चयन_करोne,
							 !priv->channel_चयन_in_progress,
							 3 * HZ);
				अगर (ret) अणु
					/* Alपढ़ोy unlocks अगर successful */
					priv->channel = ch;
					ret = 0;
				पूर्ण अन्यथा अणु
					ret = -ETIMEDOUT;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Unlock अगर चयन channel fails */
				wsm_unlock_tx(priv);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_PS) अणु
		अगर (!(conf->flags & IEEE80211_CONF_PS))
			priv->घातersave_mode.mode = WSM_PSM_ACTIVE;
		अन्यथा अगर (conf->dynamic_ps_समयout <= 0)
			priv->घातersave_mode.mode = WSM_PSM_PS;
		अन्यथा
			priv->घातersave_mode.mode = WSM_PSM_FAST_PS;

		/* Firmware requires that value क्रम this 1-byte field must
		 * be specअगरied in units of 500us. Values above the 128ms
		 * threshold are not supported.
		 */
		अगर (conf->dynamic_ps_समयout >= 0x80)
			priv->घातersave_mode.fast_psm_idle_period = 0xFF;
		अन्यथा
			priv->घातersave_mode.fast_psm_idle_period =
					conf->dynamic_ps_समयout << 1;

		अगर (priv->join_status == CW1200_JOIN_STATUS_STA &&
		    priv->bss_params.aid)
			cw1200_set_pm(priv, &priv->घातersave_mode);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		/* TBD: It looks like it's transparent
		 * there's a monitor पूर्णांकerface present -- use this
		 * to determine क्रम example whether to calculate
		 * बारtamps क्रम packets or not, करो not use instead
		 * of filter flags!
		 */
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_IDLE) अणु
		काष्ठा wsm_operational_mode mode = अणु
			.घातer_mode = cw1200_घातer_mode,
			.disable_more_flag_usage = true,
		पूर्ण;

		wsm_lock_tx(priv);
		/* Disable p2p-dev mode क्रमced by TX request */
		अगर ((priv->join_status == CW1200_JOIN_STATUS_MONITOR) &&
		    (conf->flags & IEEE80211_CONF_IDLE) &&
		    !priv->listening) अणु
			cw1200_disable_listening(priv);
			priv->join_status = CW1200_JOIN_STATUS_PASSIVE;
		पूर्ण
		wsm_set_operational_mode(priv, &mode);
		wsm_unlock_tx(priv);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS) अणु
		pr_debug("[STA] Retry limits: %d (long), %d (short).\n",
			 conf->दीर्घ_frame_max_tx_count,
			 conf->लघु_frame_max_tx_count);
		spin_lock_bh(&priv->tx_policy_cache.lock);
		priv->दीर्घ_frame_max_tx_count = conf->दीर्घ_frame_max_tx_count;
		priv->लघु_frame_max_tx_count =
			(conf->लघु_frame_max_tx_count < 0x0F) ?
			conf->लघु_frame_max_tx_count : 0x0F;
		priv->hw->max_rate_tries = priv->लघु_frame_max_tx_count;
		spin_unlock_bh(&priv->tx_policy_cache.lock);
	पूर्ण
	mutex_unlock(&priv->conf_mutex);
	up(&priv->scan.lock);
	वापस ret;
पूर्ण

व्योम cw1200_update_filtering(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret;
	bool bssid_filtering = !priv->rx_filter.bssid;
	bool is_p2p = priv->vअगर && priv->vअगर->p2p;
	bool is_sta = priv->vअगर && NL80211_IFTYPE_STATION == priv->vअगर->type;

	अटल काष्ठा wsm_beacon_filter_control bf_ctrl;
	अटल काष्ठा wsm_mib_beacon_filter_table bf_tbl = अणु
		.entry[0].ie_id = WLAN_EID_VENDOR_SPECIFIC,
		.entry[0].flags = WSM_BEACON_FILTER_IE_HAS_CHANGED |
					WSM_BEACON_FILTER_IE_NO_LONGER_PRESENT |
					WSM_BEACON_FILTER_IE_HAS_APPEARED,
		.entry[0].oui[0] = 0x50,
		.entry[0].oui[1] = 0x6F,
		.entry[0].oui[2] = 0x9A,
		.entry[1].ie_id = WLAN_EID_HT_OPERATION,
		.entry[1].flags = WSM_BEACON_FILTER_IE_HAS_CHANGED |
					WSM_BEACON_FILTER_IE_NO_LONGER_PRESENT |
					WSM_BEACON_FILTER_IE_HAS_APPEARED,
		.entry[2].ie_id = WLAN_EID_ERP_INFO,
		.entry[2].flags = WSM_BEACON_FILTER_IE_HAS_CHANGED |
					WSM_BEACON_FILTER_IE_NO_LONGER_PRESENT |
					WSM_BEACON_FILTER_IE_HAS_APPEARED,
	पूर्ण;

	अगर (priv->join_status == CW1200_JOIN_STATUS_PASSIVE)
		वापस;
	अन्यथा अगर (priv->join_status == CW1200_JOIN_STATUS_MONITOR)
		bssid_filtering = false;

	अगर (priv->disable_beacon_filter) अणु
		bf_ctrl.enabled = 0;
		bf_ctrl.bcn_count = 1;
		bf_tbl.num = __cpu_to_le32(0);
	पूर्ण अन्यथा अगर (is_p2p || !is_sta) अणु
		bf_ctrl.enabled = WSM_BEACON_FILTER_ENABLE |
			WSM_BEACON_FILTER_AUTO_ERP;
		bf_ctrl.bcn_count = 0;
		bf_tbl.num = __cpu_to_le32(2);
	पूर्ण अन्यथा अणु
		bf_ctrl.enabled = WSM_BEACON_FILTER_ENABLE;
		bf_ctrl.bcn_count = 0;
		bf_tbl.num = __cpu_to_le32(3);
	पूर्ण

	/* When acting as p2p client being connected to p2p GO, in order to
	 * receive frames from a dअगरferent p2p device, turn off bssid filter.
	 *
	 * WARNING: FW dependency!
	 * This can only be used with FW WSM371 and its successors.
	 * In that FW version even with bssid filter turned off,
	 * device will block most of the unwanted frames.
	 */
	अगर (is_p2p)
		bssid_filtering = false;

	ret = wsm_set_rx_filter(priv, &priv->rx_filter);
	अगर (!ret)
		ret = wsm_set_beacon_filter_table(priv, &bf_tbl);
	अगर (!ret)
		ret = wsm_beacon_filter_control(priv, &bf_ctrl);
	अगर (!ret)
		ret = wsm_set_bssid_filtering(priv, bssid_filtering);
	अगर (!ret)
		ret = wsm_set_multicast_filter(priv, &priv->multicast_filter);
	अगर (ret)
		wiphy_err(priv->hw->wiphy,
			  "Update filtering failed: %d.\n", ret);
	वापस;
पूर्ण

व्योम cw1200_update_filtering_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common,
			     update_filtering_work);

	cw1200_update_filtering(priv);
पूर्ण

व्योम cw1200_set_beacon_wakeup_period_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common,
			     set_beacon_wakeup_period_work);

	wsm_set_beacon_wakeup_period(priv,
				     priv->beacon_पूर्णांक * priv->join_dtim_period >
				     MAX_BEACON_SKIP_TIME_MS ? 1 :
				     priv->join_dtim_period, 0);
पूर्ण

u64 cw1200_prepare_multicast(काष्ठा ieee80211_hw *hw,
			     काष्ठा netdev_hw_addr_list *mc_list)
अणु
	अटल u8 broadcast_ipv6[ETH_ALEN] = अणु
		0x33, 0x33, 0x00, 0x00, 0x00, 0x01
	पूर्ण;
	अटल u8 broadcast_ipv4[ETH_ALEN] = अणु
		0x01, 0x00, 0x5e, 0x00, 0x00, 0x01
	पूर्ण;
	काष्ठा cw1200_common *priv = hw->priv;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक count = 0;

	/* Disable multicast filtering */
	priv->has_multicast_subscription = false;
	स_रखो(&priv->multicast_filter, 0x00, माप(priv->multicast_filter));

	अगर (netdev_hw_addr_list_count(mc_list) > WSM_MAX_GRP_ADDRTABLE_ENTRIES)
		वापस 0;

	/* Enable अगर requested */
	netdev_hw_addr_list_क्रम_each(ha, mc_list) अणु
		pr_debug("[STA] multicast: %pM\n", ha->addr);
		स_नकल(&priv->multicast_filter.macaddrs[count],
		       ha->addr, ETH_ALEN);
		अगर (!ether_addr_equal(ha->addr, broadcast_ipv4) &&
		    !ether_addr_equal(ha->addr, broadcast_ipv6))
			priv->has_multicast_subscription = true;
		count++;
	पूर्ण

	अगर (count) अणु
		priv->multicast_filter.enable = __cpu_to_le32(1);
		priv->multicast_filter.num_addrs = __cpu_to_le32(count);
	पूर्ण

	वापस netdev_hw_addr_list_count(mc_list);
पूर्ण

व्योम cw1200_configure_filter(काष्ठा ieee80211_hw *dev,
			     अचिन्हित पूर्णांक changed_flags,
			     अचिन्हित पूर्णांक *total_flags,
			     u64 multicast)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	bool listening = !!(*total_flags &
			    (FIF_OTHER_BSS |
			     FIF_BCN_PRBRESP_PROMISC |
			     FIF_PROBE_REQ));

	*total_flags &= FIF_OTHER_BSS |
			FIF_FCSFAIL |
			FIF_BCN_PRBRESP_PROMISC |
			FIF_PROBE_REQ;

	करोwn(&priv->scan.lock);
	mutex_lock(&priv->conf_mutex);

	priv->rx_filter.promiscuous = 0;
	priv->rx_filter.bssid = (*total_flags & (FIF_OTHER_BSS |
			FIF_PROBE_REQ)) ? 1 : 0;
	priv->rx_filter.fcs = (*total_flags & FIF_FCSFAIL) ? 1 : 0;
	priv->disable_beacon_filter = !(*total_flags &
					(FIF_BCN_PRBRESP_PROMISC |
					 FIF_PROBE_REQ));
	अगर (priv->listening != listening) अणु
		priv->listening = listening;
		wsm_lock_tx(priv);
		cw1200_update_listening(priv, listening);
		wsm_unlock_tx(priv);
	पूर्ण
	cw1200_update_filtering(priv);
	mutex_unlock(&priv->conf_mutex);
	up(&priv->scan.lock);
पूर्ण

पूर्णांक cw1200_conf_tx(काष्ठा ieee80211_hw *dev, काष्ठा ieee80211_vअगर *vअगर,
		   u16 queue, स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	पूर्णांक ret = 0;
	/* To prevent re-applying PM request OID again and again*/
	bool old_uapsd_flags;

	mutex_lock(&priv->conf_mutex);

	अगर (queue < dev->queues) अणु
		old_uapsd_flags = le16_to_cpu(priv->uapsd_info.uapsd_flags);

		WSM_TX_QUEUE_SET(&priv->tx_queue_params, queue, 0, 0, 0);
		ret = wsm_set_tx_queue_params(priv,
					      &priv->tx_queue_params.params[queue], queue);
		अगर (ret) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		WSM_EDCA_SET(&priv->edca, queue, params->aअगरs,
			     params->cw_min, params->cw_max,
			     params->txop, 0xc8,
			     params->uapsd);
		ret = wsm_set_edca_params(priv, &priv->edca);
		अगर (ret) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (priv->mode == NL80211_IFTYPE_STATION) अणु
			ret = cw1200_set_uapsd_param(priv, &priv->edca);
			अगर (!ret && priv->setbssparams_करोne &&
			    (priv->join_status == CW1200_JOIN_STATUS_STA) &&
			    (old_uapsd_flags != le16_to_cpu(priv->uapsd_info.uapsd_flags)))
				ret = cw1200_set_pm(priv, &priv->घातersave_mode);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

out:
	mutex_unlock(&priv->conf_mutex);
	वापस ret;
पूर्ण

पूर्णांक cw1200_get_stats(काष्ठा ieee80211_hw *dev,
		     काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा cw1200_common *priv = dev->priv;

	स_नकल(stats, &priv->stats, माप(*stats));
	वापस 0;
पूर्ण

पूर्णांक cw1200_set_pm(काष्ठा cw1200_common *priv, स्थिर काष्ठा wsm_set_pm *arg)
अणु
	काष्ठा wsm_set_pm pm = *arg;

	अगर (priv->uapsd_info.uapsd_flags != 0)
		pm.mode &= ~WSM_PSM_FAST_PS_FLAG;

	अगर (स_भेद(&pm, &priv->firmware_ps_mode,
		   माप(काष्ठा wsm_set_pm))) अणु
		priv->firmware_ps_mode = pm;
		वापस wsm_set_pm(priv, &pm);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक cw1200_set_key(काष्ठा ieee80211_hw *dev, क्रमागत set_key_cmd cmd,
		   काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		   काष्ठा ieee80211_key_conf *key)
अणु
	पूर्णांक ret = -EOPNOTSUPP;
	काष्ठा cw1200_common *priv = dev->priv;
	काष्ठा ieee80211_key_seq seq;

	mutex_lock(&priv->conf_mutex);

	अगर (cmd == SET_KEY) अणु
		u8 *peer_addr = शून्य;
		पूर्णांक pairwise = (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) ?
			1 : 0;
		पूर्णांक idx = cw1200_alloc_key(priv);
		काष्ठा wsm_add_key *wsm_key = &priv->keys[idx];

		अगर (idx < 0) अणु
			ret = -EINVAL;
			जाओ finally;
		पूर्ण

		अगर (sta)
			peer_addr = sta->addr;

		key->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE |
			      IEEE80211_KEY_FLAG_RESERVE_TAILROOM;

		चयन (key->cipher) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			अगर (key->keylen > 16) अणु
				cw1200_मुक्त_key(priv, idx);
				ret = -EINVAL;
				जाओ finally;
			पूर्ण

			अगर (pairwise) अणु
				wsm_key->type = WSM_KEY_TYPE_WEP_PAIRWISE;
				स_नकल(wsm_key->wep_pairwise.peer,
				       peer_addr, ETH_ALEN);
				स_नकल(wsm_key->wep_pairwise.keydata,
				       &key->key[0], key->keylen);
				wsm_key->wep_pairwise.keylen = key->keylen;
			पूर्ण अन्यथा अणु
				wsm_key->type = WSM_KEY_TYPE_WEP_DEFAULT;
				स_नकल(wsm_key->wep_group.keydata,
				       &key->key[0], key->keylen);
				wsm_key->wep_group.keylen = key->keylen;
				wsm_key->wep_group.keyid = key->keyidx;
			पूर्ण
			अवरोध;
		हाल WLAN_CIPHER_SUITE_TKIP:
			ieee80211_get_key_rx_seq(key, 0, &seq);
			अगर (pairwise) अणु
				wsm_key->type = WSM_KEY_TYPE_TKIP_PAIRWISE;
				स_नकल(wsm_key->tkip_pairwise.peer,
				       peer_addr, ETH_ALEN);
				स_नकल(wsm_key->tkip_pairwise.keydata,
				       &key->key[0], 16);
				स_नकल(wsm_key->tkip_pairwise.tx_mic_key,
				       &key->key[16], 8);
				स_नकल(wsm_key->tkip_pairwise.rx_mic_key,
				       &key->key[24], 8);
			पूर्ण अन्यथा अणु
				माप_प्रकार mic_offset =
					(priv->mode == NL80211_IFTYPE_AP) ?
					16 : 24;
				wsm_key->type = WSM_KEY_TYPE_TKIP_GROUP;
				स_नकल(wsm_key->tkip_group.keydata,
				       &key->key[0], 16);
				स_नकल(wsm_key->tkip_group.rx_mic_key,
				       &key->key[mic_offset], 8);

				wsm_key->tkip_group.rx_seqnum[0] = seq.tkip.iv16 & 0xff;
				wsm_key->tkip_group.rx_seqnum[1] = (seq.tkip.iv16 >> 8) & 0xff;
				wsm_key->tkip_group.rx_seqnum[2] = seq.tkip.iv32 & 0xff;
				wsm_key->tkip_group.rx_seqnum[3] = (seq.tkip.iv32 >> 8) & 0xff;
				wsm_key->tkip_group.rx_seqnum[4] = (seq.tkip.iv32 >> 16) & 0xff;
				wsm_key->tkip_group.rx_seqnum[5] = (seq.tkip.iv32 >> 24) & 0xff;
				wsm_key->tkip_group.rx_seqnum[6] = 0;
				wsm_key->tkip_group.rx_seqnum[7] = 0;

				wsm_key->tkip_group.keyid = key->keyidx;
			पूर्ण
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			ieee80211_get_key_rx_seq(key, 0, &seq);
			अगर (pairwise) अणु
				wsm_key->type = WSM_KEY_TYPE_AES_PAIRWISE;
				स_नकल(wsm_key->aes_pairwise.peer,
				       peer_addr, ETH_ALEN);
				स_नकल(wsm_key->aes_pairwise.keydata,
				       &key->key[0], 16);
			पूर्ण अन्यथा अणु
				wsm_key->type = WSM_KEY_TYPE_AES_GROUP;
				स_नकल(wsm_key->aes_group.keydata,
				       &key->key[0], 16);

				wsm_key->aes_group.rx_seqnum[0] = seq.ccmp.pn[5];
				wsm_key->aes_group.rx_seqnum[1] = seq.ccmp.pn[4];
				wsm_key->aes_group.rx_seqnum[2] = seq.ccmp.pn[3];
				wsm_key->aes_group.rx_seqnum[3] = seq.ccmp.pn[2];
				wsm_key->aes_group.rx_seqnum[4] = seq.ccmp.pn[1];
				wsm_key->aes_group.rx_seqnum[5] = seq.ccmp.pn[0];
				wsm_key->aes_group.rx_seqnum[6] = 0;
				wsm_key->aes_group.rx_seqnum[7] = 0;
				wsm_key->aes_group.keyid = key->keyidx;
			पूर्ण
			अवरोध;
		हाल WLAN_CIPHER_SUITE_SMS4:
			अगर (pairwise) अणु
				wsm_key->type = WSM_KEY_TYPE_WAPI_PAIRWISE;
				स_नकल(wsm_key->wapi_pairwise.peer,
				       peer_addr, ETH_ALEN);
				स_नकल(wsm_key->wapi_pairwise.keydata,
				       &key->key[0], 16);
				स_नकल(wsm_key->wapi_pairwise.mic_key,
				       &key->key[16], 16);
				wsm_key->wapi_pairwise.keyid = key->keyidx;
			पूर्ण अन्यथा अणु
				wsm_key->type = WSM_KEY_TYPE_WAPI_GROUP;
				स_नकल(wsm_key->wapi_group.keydata,
				       &key->key[0],  16);
				स_नकल(wsm_key->wapi_group.mic_key,
				       &key->key[16], 16);
				wsm_key->wapi_group.keyid = key->keyidx;
			पूर्ण
			अवरोध;
		शेष:
			pr_warn("Unhandled key type %d\n", key->cipher);
			cw1200_मुक्त_key(priv, idx);
			ret = -EOPNOTSUPP;
			जाओ finally;
		पूर्ण
		ret = wsm_add_key(priv, wsm_key);
		अगर (!ret)
			key->hw_key_idx = idx;
		अन्यथा
			cw1200_मुक्त_key(priv, idx);
	पूर्ण अन्यथा अगर (cmd == DISABLE_KEY) अणु
		काष्ठा wsm_हटाओ_key wsm_key = अणु
			.index = key->hw_key_idx,
		पूर्ण;

		अगर (wsm_key.index > WSM_KEY_MAX_INDEX) अणु
			ret = -EINVAL;
			जाओ finally;
		पूर्ण

		cw1200_मुक्त_key(priv, wsm_key.index);
		ret = wsm_हटाओ_key(priv, &wsm_key);
	पूर्ण अन्यथा अणु
		pr_warn("Unhandled key command %d\n", cmd);
	पूर्ण

finally:
	mutex_unlock(&priv->conf_mutex);
	वापस ret;
पूर्ण

व्योम cw1200_wep_key_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, wep_key_work);
	u8 queue_id = cw1200_queue_get_queue_id(priv->pending_frame_id);
	काष्ठा cw1200_queue *queue = &priv->tx_queue[queue_id];
	__le32 wep_शेष_key_id = __cpu_to_le32(
		priv->wep_शेष_key_id);

	pr_debug("[STA] Setting default WEP key: %d\n",
		 priv->wep_शेष_key_id);
	wsm_flush_tx(priv);
	wsm_ग_लिखो_mib(priv, WSM_MIB_ID_DOT11_WEP_DEFAULT_KEY_ID,
		      &wep_शेष_key_id, माप(wep_शेष_key_id));
	cw1200_queue_requeue(queue, priv->pending_frame_id);
	wsm_unlock_tx(priv);
पूर्ण

पूर्णांक cw1200_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	पूर्णांक ret = 0;
	__le32 val32;
	काष्ठा cw1200_common *priv = hw->priv;

	अगर (priv->mode == NL80211_IFTYPE_UNSPECIFIED)
		वापस 0;

	अगर (value != (u32) -1)
		val32 = __cpu_to_le32(value);
	अन्यथा
		val32 = 0; /* disabled */

	अगर (priv->rts_threshold == value)
		जाओ out;

	pr_debug("[STA] Setting RTS threshold: %d\n",
		 priv->rts_threshold);

	/* mutex_lock(&priv->conf_mutex); */
	ret = wsm_ग_लिखो_mib(priv, WSM_MIB_ID_DOT11_RTS_THRESHOLD,
			    &val32, माप(val32));
	अगर (!ret)
		priv->rts_threshold = value;
	/* mutex_unlock(&priv->conf_mutex); */

out:
	वापस ret;
पूर्ण

/* If successful, LOCKS the TX queue! */
अटल पूर्णांक __cw1200_flush(काष्ठा cw1200_common *priv, bool drop)
अणु
	पूर्णांक i, ret;

	क्रम (;;) अणु
		/* TODO: correct flush handling is required when dev_stop.
		 * Temporary workaround: 2s
		 */
		अगर (drop) अणु
			क्रम (i = 0; i < 4; ++i)
				cw1200_queue_clear(&priv->tx_queue[i]);
		पूर्ण अन्यथा अणु
			ret = रुको_event_समयout(
				priv->tx_queue_stats.रुको_link_id_empty,
				cw1200_queue_stats_is_empty(
					&priv->tx_queue_stats, -1),
				2 * HZ);
		पूर्ण

		अगर (!drop && ret <= 0) अणु
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण

		wsm_lock_tx(priv);
		अगर (!cw1200_queue_stats_is_empty(&priv->tx_queue_stats, -1)) अणु
			/* Highly unlikely: WSM requeued frames. */
			wsm_unlock_tx(priv);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

व्योम cw1200_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  u32 queues, bool drop)
अणु
	काष्ठा cw1200_common *priv = hw->priv;

	चयन (priv->mode) अणु
	हाल NL80211_IFTYPE_MONITOR:
		drop = true;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		अगर (!priv->enable_beacon)
			drop = true;
		अवरोध;
	पूर्ण

	अगर (!__cw1200_flush(priv, drop))
		wsm_unlock_tx(priv);

	वापस;
पूर्ण

/* ******************************************************************** */
/* WSM callbacks							*/

व्योम cw1200_मुक्त_event_queue(काष्ठा cw1200_common *priv)
अणु
	LIST_HEAD(list);

	spin_lock(&priv->event_queue_lock);
	list_splice_init(&priv->event_queue, &list);
	spin_unlock(&priv->event_queue_lock);

	__cw1200_मुक्त_event_queue(&list);
पूर्ण

व्योम cw1200_event_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, event_handler);
	काष्ठा cw1200_wsm_event *event;
	LIST_HEAD(list);

	spin_lock(&priv->event_queue_lock);
	list_splice_init(&priv->event_queue, &list);
	spin_unlock(&priv->event_queue_lock);

	list_क्रम_each_entry(event, &list, link) अणु
		चयन (event->evt.id) अणु
		हाल WSM_EVENT_ERROR:
			pr_err("Unhandled WSM Error from LMAC\n");
			अवरोध;
		हाल WSM_EVENT_BSS_LOST:
			pr_debug("[CQM] BSS lost.\n");
			cancel_work_sync(&priv->unjoin_work);
			अगर (!करोwn_trylock(&priv->scan.lock)) अणु
				cw1200_cqm_bssloss_sm(priv, 1, 0, 0);
				up(&priv->scan.lock);
			पूर्ण अन्यथा अणु
				/* Scan is in progress. Delay reporting.
				 * Scan complete will trigger bss_loss_work
				 */
				priv->delayed_link_loss = 1;
				/* Also start a watchकरोg. */
				queue_delayed_work(priv->workqueue,
						   &priv->bss_loss_work, 5*HZ);
			पूर्ण
			अवरोध;
		हाल WSM_EVENT_BSS_REGAINED:
			pr_debug("[CQM] BSS regained.\n");
			cw1200_cqm_bssloss_sm(priv, 0, 0, 0);
			cancel_work_sync(&priv->unjoin_work);
			अवरोध;
		हाल WSM_EVENT_RADAR_DETECTED:
			wiphy_info(priv->hw->wiphy, "radar pulse detected\n");
			अवरोध;
		हाल WSM_EVENT_RCPI_RSSI:
		अणु
			/* RSSI: चिन्हित Q8.0, RCPI: अचिन्हित Q7.1
			 * RSSI = RCPI / 2 - 110
			 */
			पूर्णांक rcpi_rssi = (पूर्णांक)(event->evt.data & 0xFF);
			पूर्णांक cqm_evt;
			अगर (priv->cqm_use_rssi)
				rcpi_rssi = (s8)rcpi_rssi;
			अन्यथा
				rcpi_rssi =  rcpi_rssi / 2 - 110;

			cqm_evt = (rcpi_rssi <= priv->cqm_rssi_thold) ?
				NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW :
				NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH;
			pr_debug("[CQM] RSSI event: %d.\n", rcpi_rssi);
			ieee80211_cqm_rssi_notअगरy(priv->vअगर, cqm_evt, rcpi_rssi,
						  GFP_KERNEL);
			अवरोध;
		पूर्ण
		हाल WSM_EVENT_BT_INACTIVE:
			pr_warn("Unhandled BT INACTIVE from LMAC\n");
			अवरोध;
		हाल WSM_EVENT_BT_ACTIVE:
			pr_warn("Unhandled BT ACTIVE from LMAC\n");
			अवरोध;
		पूर्ण
	पूर्ण
	__cw1200_मुक्त_event_queue(&list);
पूर्ण

व्योम cw1200_bss_loss_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, bss_loss_work.work);

	pr_debug("[CQM] Reporting connection loss.\n");
	wsm_lock_tx(priv);
	अगर (queue_work(priv->workqueue, &priv->unjoin_work) <= 0)
		wsm_unlock_tx(priv);
पूर्ण

व्योम cw1200_bss_params_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, bss_params_work);
	mutex_lock(&priv->conf_mutex);

	priv->bss_params.reset_beacon_loss = 1;
	wsm_set_bss_params(priv, &priv->bss_params);
	priv->bss_params.reset_beacon_loss = 0;

	mutex_unlock(&priv->conf_mutex);
पूर्ण

/* ******************************************************************** */
/* Internal API								*/

/* This function is called to Parse the SDD file
 * to extract listen_पूर्णांकerval and PTA related inक्रमmation
 * sdd is a TLV: u8 id, u8 len, u8 data[]
 */
अटल पूर्णांक cw1200_parse_sdd_file(काष्ठा cw1200_common *priv)
अणु
	स्थिर u8 *p = priv->sdd->data;
	पूर्णांक ret = 0;

	जबतक (p + 2 <= priv->sdd->data + priv->sdd->size) अणु
		अगर (p + p[1] + 2 > priv->sdd->data + priv->sdd->size) अणु
			pr_warn("Malformed sdd structure\n");
			वापस -1;
		पूर्ण
		चयन (p[0]) अणु
		हाल SDD_PTA_CFG_ELT_ID: अणु
			u16 v;
			अगर (p[1] < 4) अणु
				pr_warn("SDD_PTA_CFG_ELT_ID malformed\n");
				ret = -1;
				अवरोध;
			पूर्ण
			v = le16_to_cpu(*((__le16 *)(p + 2)));
			अगर (!v)  /* non-zero means this is enabled */
				अवरोध;

			v = le16_to_cpu(*((__le16 *)(p + 4)));
			priv->conf_listen_पूर्णांकerval = (v >> 7) & 0x1F;
			pr_debug("PTA found; Listen Interval %d\n",
				 priv->conf_listen_पूर्णांकerval);
			अवरोध;
		पूर्ण
		हाल SDD_REFERENCE_FREQUENCY_ELT_ID: अणु
			u16 clk = le16_to_cpu(*((__le16 *)(p + 2)));
			अगर (clk != priv->hw_refclk)
				pr_warn("SDD file doesn't match configured refclk (%d vs %d)\n",
					clk, priv->hw_refclk);
			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
		p += p[1] + 2;
	पूर्ण

	अगर (!priv->bt_present) अणु
		pr_debug("PTA element NOT found.\n");
		priv->conf_listen_पूर्णांकerval = 0;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक cw1200_setup_mac(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret = 0;

	/* NOTE: There is a bug in FW: it reports संकेत
	 * as RSSI अगर RSSI subscription is enabled.
	 * It's not enough to set WSM_RCPI_RSSI_USE_RSSI.
	 *
	 * NOTE2: RSSI based reports have been चयनed to RCPI, since
	 * FW has a bug and RSSI reported values are not stable,
	 * what can lead to संकेत level oscilations in user-end applications
	 */
	काष्ठा wsm_rcpi_rssi_threshold threshold = अणु
		.rssiRcpiMode = WSM_RCPI_RSSI_THRESHOLD_ENABLE |
		WSM_RCPI_RSSI_DONT_USE_UPPER |
		WSM_RCPI_RSSI_DONT_USE_LOWER,
		.rollingAverageCount = 16,
	पूर्ण;

	काष्ठा wsm_configuration cfg = अणु
		.करोt11StationId = &priv->mac_addr[0],
	पूर्ण;

	/* Remember the decission here to make sure, we will handle
	 * the RCPI/RSSI value correctly on WSM_EVENT_RCPI_RSS
	 */
	अगर (threshold.rssiRcpiMode & WSM_RCPI_RSSI_USE_RSSI)
		priv->cqm_use_rssi = true;

	अगर (!priv->sdd) अणु
		ret = request_firmware(&priv->sdd, priv->sdd_path, priv->pdev);
		अगर (ret) अणु
			pr_err("Can't load sdd file %s.\n", priv->sdd_path);
			वापस ret;
		पूर्ण
		cw1200_parse_sdd_file(priv);
	पूर्ण

	cfg.dpdData = priv->sdd->data;
	cfg.dpdData_size = priv->sdd->size;
	ret = wsm_configuration(priv, &cfg);
	अगर (ret)
		वापस ret;

	/* Configure RSSI/SCPI reporting as RSSI. */
	wsm_set_rcpi_rssi_threshold(priv, &threshold);

	वापस 0;
पूर्ण

अटल व्योम cw1200_join_complete(काष्ठा cw1200_common *priv)
अणु
	pr_debug("[STA] Join complete (%d)\n", priv->join_complete_status);

	priv->join_pending = false;
	अगर (priv->join_complete_status) अणु
		priv->join_status = CW1200_JOIN_STATUS_PASSIVE;
		cw1200_update_listening(priv, priv->listening);
		cw1200_करो_unjoin(priv);
		ieee80211_connection_loss(priv->vअगर);
	पूर्ण अन्यथा अणु
		अगर (priv->mode == NL80211_IFTYPE_ADHOC)
			priv->join_status = CW1200_JOIN_STATUS_IBSS;
		अन्यथा
			priv->join_status = CW1200_JOIN_STATUS_PRE_STA;
	पूर्ण
	wsm_unlock_tx(priv); /* Clearing the lock held beक्रमe करो_join() */
पूर्ण

व्योम cw1200_join_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, join_complete_work);
	mutex_lock(&priv->conf_mutex);
	cw1200_join_complete(priv);
	mutex_unlock(&priv->conf_mutex);
पूर्ण

व्योम cw1200_join_complete_cb(काष्ठा cw1200_common *priv,
			     काष्ठा wsm_join_complete *arg)
अणु
	pr_debug("[STA] cw1200_join_complete_cb called, status=%d.\n",
		 arg->status);

	अगर (cancel_delayed_work(&priv->join_समयout)) अणु
		priv->join_complete_status = arg->status;
		queue_work(priv->workqueue, &priv->join_complete_work);
	पूर्ण
पूर्ण

/* MUST be called with tx_lock held!  It will be unlocked क्रम us. */
अटल व्योम cw1200_करो_join(काष्ठा cw1200_common *priv)
अणु
	स्थिर u8 *bssid;
	काष्ठा ieee80211_bss_conf *conf = &priv->vअगर->bss_conf;
	काष्ठा cfg80211_bss *bss = शून्य;
	काष्ठा wsm_रक्षित_mgmt_policy mgmt_policy;
	काष्ठा wsm_join join = अणु
		.mode = conf->ibss_joined ?
				WSM_JOIN_MODE_IBSS : WSM_JOIN_MODE_BSS,
		.preamble_type = WSM_JOIN_PREAMBLE_LONG,
		.probe_क्रम_join = 1,
		.atim_winकरोw = 0,
		.basic_rate_set = cw1200_rate_mask_to_wsm(priv,
							  conf->basic_rates),
	पूर्ण;
	अगर (delayed_work_pending(&priv->join_समयout)) अणु
		pr_warn("[STA] - Join request already pending, skipping..\n");
		wsm_unlock_tx(priv);
		वापस;
	पूर्ण

	अगर (priv->join_status)
		cw1200_करो_unjoin(priv);

	bssid = priv->vअगर->bss_conf.bssid;

	bss = cfg80211_get_bss(priv->hw->wiphy, priv->channel, bssid, शून्य, 0,
			       IEEE80211_BSS_TYPE_ANY, IEEE80211_PRIVACY_ANY);

	अगर (!bss && !conf->ibss_joined) अणु
		wsm_unlock_tx(priv);
		वापस;
	पूर्ण

	mutex_lock(&priv->conf_mutex);

	/* Under the conf lock: check scan status and
	 * bail out अगर it is in progress.
	 */
	अगर (atomic_पढ़ो(&priv->scan.in_progress)) अणु
		wsm_unlock_tx(priv);
		जाओ करोne_put;
	पूर्ण

	priv->join_pending = true;

	/* Sanity check basic rates */
	अगर (!join.basic_rate_set)
		join.basic_rate_set = 7;

	/* Sanity check beacon पूर्णांकerval */
	अगर (!priv->beacon_पूर्णांक)
		priv->beacon_पूर्णांक = 1;

	join.beacon_पूर्णांकerval = priv->beacon_पूर्णांक;

	/* BT Coex related changes */
	अगर (priv->bt_present) अणु
		अगर (((priv->conf_listen_पूर्णांकerval * 100) %
		     priv->beacon_पूर्णांक) == 0)
			priv->listen_पूर्णांकerval =
				((priv->conf_listen_पूर्णांकerval * 100) /
				 priv->beacon_पूर्णांक);
		अन्यथा
			priv->listen_पूर्णांकerval =
				((priv->conf_listen_पूर्णांकerval * 100) /
				 priv->beacon_पूर्णांक + 1);
	पूर्ण

	अगर (priv->hw->conf.ps_dtim_period)
		priv->join_dtim_period = priv->hw->conf.ps_dtim_period;
	join.dtim_period = priv->join_dtim_period;

	join.channel_number = priv->channel->hw_value;
	join.band = (priv->channel->band == NL80211_BAND_5GHZ) ?
		WSM_PHY_BAND_5G : WSM_PHY_BAND_2_4G;

	स_नकल(join.bssid, bssid, माप(join.bssid));

	pr_debug("[STA] Join BSSID: %pM DTIM: %d, interval: %d\n",
		 join.bssid,
		 join.dtim_period, priv->beacon_पूर्णांक);

	अगर (!conf->ibss_joined) अणु
		स्थिर u8 *ssidie;
		rcu_पढ़ो_lock();
		ssidie = ieee80211_bss_get_ie(bss, WLAN_EID_SSID);
		अगर (ssidie) अणु
			join.ssid_len = ssidie[1];
			स_नकल(join.ssid, &ssidie[2], join.ssid_len);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (priv->vअगर->p2p) अणु
		join.flags |= WSM_JOIN_FLAGS_P2P_GO;
		join.basic_rate_set =
			cw1200_rate_mask_to_wsm(priv, 0xFF0);
	पूर्ण

	/* Enable asynchronous join calls */
	अगर (!conf->ibss_joined) अणु
		join.flags |= WSM_JOIN_FLAGS_FORCE;
		join.flags |= WSM_JOIN_FLAGS_FORCE_WITH_COMPLETE_IND;
	पूर्ण

	wsm_flush_tx(priv);

	/* Stay Awake क्रम Join and Auth Timeouts and a bit more */
	cw1200_pm_stay_awake(&priv->pm_state,
			     CW1200_JOIN_TIMEOUT + CW1200_AUTH_TIMEOUT);

	cw1200_update_listening(priv, false);

	/* Turn on Block ACKs */
	wsm_set_block_ack_policy(priv, priv->ba_tx_tid_mask,
				 priv->ba_rx_tid_mask);

	/* Set up समयout */
	अगर (join.flags & WSM_JOIN_FLAGS_FORCE_WITH_COMPLETE_IND) अणु
		priv->join_status = CW1200_JOIN_STATUS_JOINING;
		queue_delayed_work(priv->workqueue,
				   &priv->join_समयout,
				   CW1200_JOIN_TIMEOUT);
	पूर्ण

	/* 802.11w रक्षित mgmt frames */
	mgmt_policy.रक्षितMgmtEnable = 0;
	mgmt_policy.unरक्षितMgmtFramesAllowed = 1;
	mgmt_policy.encryptionForAuthFrame = 1;
	wsm_set_रक्षित_mgmt_policy(priv, &mgmt_policy);

	/* Perक्रमm actual join */
	अगर (wsm_join(priv, &join)) अणु
		pr_err("[STA] cw1200_join_work: wsm_join failed!\n");
		cancel_delayed_work_sync(&priv->join_समयout);
		cw1200_update_listening(priv, priv->listening);
		/* Tx lock still held, unjoin will clear it. */
		अगर (queue_work(priv->workqueue, &priv->unjoin_work) <= 0)
			wsm_unlock_tx(priv);
	पूर्ण अन्यथा अणु
		अगर (!(join.flags & WSM_JOIN_FLAGS_FORCE_WITH_COMPLETE_IND))
			cw1200_join_complete(priv); /* Will clear tx_lock */

		/* Upload keys */
		cw1200_upload_keys(priv);

		/* Due to beacon filtering it is possible that the
		 * AP's beacon is not known क्रम the mac80211 stack.
		 * Disable filtering temporary to make sure the stack
		 * receives at least one
		 */
		priv->disable_beacon_filter = true;
	पूर्ण
	cw1200_update_filtering(priv);

करोne_put:
	mutex_unlock(&priv->conf_mutex);
	अगर (bss)
		cfg80211_put_bss(priv->hw->wiphy, bss);
पूर्ण

व्योम cw1200_join_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, join_समयout.work);
	pr_debug("[WSM] Join timed out.\n");
	wsm_lock_tx(priv);
	अगर (queue_work(priv->workqueue, &priv->unjoin_work) <= 0)
		wsm_unlock_tx(priv);
पूर्ण

अटल व्योम cw1200_करो_unjoin(काष्ठा cw1200_common *priv)
अणु
	काष्ठा wsm_reset reset = अणु
		.reset_statistics = true,
	पूर्ण;

	cancel_delayed_work_sync(&priv->join_समयout);

	mutex_lock(&priv->conf_mutex);
	priv->join_pending = false;

	अगर (atomic_पढ़ो(&priv->scan.in_progress)) अणु
		अगर (priv->delayed_unjoin)
			wiphy_dbg(priv->hw->wiphy, "Delayed unjoin is already scheduled.\n");
		अन्यथा
			priv->delayed_unjoin = true;
		जाओ करोne;
	पूर्ण

	priv->delayed_link_loss = false;

	अगर (!priv->join_status)
		जाओ करोne;

	अगर (priv->join_status == CW1200_JOIN_STATUS_AP)
		जाओ करोne;

	cancel_work_sync(&priv->update_filtering_work);
	cancel_work_sync(&priv->set_beacon_wakeup_period_work);
	priv->join_status = CW1200_JOIN_STATUS_PASSIVE;

	/* Unjoin is a reset. */
	wsm_flush_tx(priv);
	wsm_keep_alive_period(priv, 0);
	wsm_reset(priv, &reset);
	wsm_set_output_घातer(priv, priv->output_घातer * 10);
	priv->join_dtim_period = 0;
	cw1200_setup_mac(priv);
	cw1200_मुक्त_event_queue(priv);
	cancel_work_sync(&priv->event_handler);
	cw1200_update_listening(priv, priv->listening);
	cw1200_cqm_bssloss_sm(priv, 0, 0, 0);

	/* Disable Block ACKs */
	wsm_set_block_ack_policy(priv, 0, 0);

	priv->disable_beacon_filter = false;
	cw1200_update_filtering(priv);
	स_रखो(&priv->association_mode, 0,
	       माप(priv->association_mode));
	स_रखो(&priv->bss_params, 0, माप(priv->bss_params));
	priv->setbssparams_करोne = false;
	स_रखो(&priv->firmware_ps_mode, 0,
	       माप(priv->firmware_ps_mode));

	pr_debug("[STA] Unjoin completed.\n");

करोne:
	mutex_unlock(&priv->conf_mutex);
पूर्ण

व्योम cw1200_unjoin_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, unjoin_work);

	cw1200_करो_unjoin(priv);

	/* Tell the stack we're dead */
	ieee80211_connection_loss(priv->vअगर);

	wsm_unlock_tx(priv);
पूर्ण

पूर्णांक cw1200_enable_listening(काष्ठा cw1200_common *priv)
अणु
	काष्ठा wsm_start start = अणु
		.mode = WSM_START_MODE_P2P_DEV,
		.band = WSM_PHY_BAND_2_4G,
		.beacon_पूर्णांकerval = 100,
		.dtim_period = 1,
		.probe_delay = 0,
		.basic_rate_set = 0x0F,
	पूर्ण;

	अगर (priv->channel) अणु
		start.band = priv->channel->band == NL80211_BAND_5GHZ ?
			     WSM_PHY_BAND_5G : WSM_PHY_BAND_2_4G;
		start.channel_number = priv->channel->hw_value;
	पूर्ण अन्यथा अणु
		start.band = WSM_PHY_BAND_2_4G;
		start.channel_number = 1;
	पूर्ण

	वापस wsm_start(priv, &start);
पूर्ण

पूर्णांक cw1200_disable_listening(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret;
	काष्ठा wsm_reset reset = अणु
		.reset_statistics = true,
	पूर्ण;
	ret = wsm_reset(priv, &reset);
	वापस ret;
पूर्ण

व्योम cw1200_update_listening(काष्ठा cw1200_common *priv, bool enabled)
अणु
	अगर (enabled) अणु
		अगर (priv->join_status == CW1200_JOIN_STATUS_PASSIVE) अणु
			अगर (!cw1200_enable_listening(priv))
				priv->join_status = CW1200_JOIN_STATUS_MONITOR;
			wsm_set_probe_responder(priv, true);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (priv->join_status == CW1200_JOIN_STATUS_MONITOR) अणु
			अगर (!cw1200_disable_listening(priv))
				priv->join_status = CW1200_JOIN_STATUS_PASSIVE;
			wsm_set_probe_responder(priv, false);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक cw1200_set_uapsd_param(काष्ठा cw1200_common *priv,
			   स्थिर काष्ठा wsm_edca_params *arg)
अणु
	पूर्णांक ret;
	u16 uapsd_flags = 0;

	/* Here's the mapping AC [queue, bit]
	 *  VO [0,3], VI [1, 2], BE [2, 1], BK [3, 0]
	 */

	अगर (arg->uapsd_enable[0])
		uapsd_flags |= 1 << 3;

	अगर (arg->uapsd_enable[1])
		uapsd_flags |= 1 << 2;

	अगर (arg->uapsd_enable[2])
		uapsd_flags |= 1 << 1;

	अगर (arg->uapsd_enable[3])
		uapsd_flags |= 1;

	/* Currently pseuकरो U-APSD operation is not supported, so setting
	 * MinAutoTriggerInterval, MaxAutoTriggerInterval and
	 * AutoTriggerStep to 0
	 */

	priv->uapsd_info.uapsd_flags = cpu_to_le16(uapsd_flags);
	priv->uapsd_info.min_स्वतः_trigger_पूर्णांकerval = 0;
	priv->uapsd_info.max_स्वतः_trigger_पूर्णांकerval = 0;
	priv->uapsd_info.स्वतः_trigger_step = 0;

	ret = wsm_set_uapsd_info(priv, &priv->uapsd_info);
	वापस ret;
पूर्ण

/* ******************************************************************** */
/* AP API								*/

पूर्णांक cw1200_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा cw1200_common *priv = hw->priv;
	काष्ठा cw1200_sta_priv *sta_priv =
			(काष्ठा cw1200_sta_priv *)&sta->drv_priv;
	काष्ठा cw1200_link_entry *entry;
	काष्ठा sk_buff *skb;

	अगर (priv->mode != NL80211_IFTYPE_AP)
		वापस 0;

	sta_priv->link_id = cw1200_find_link_id(priv, sta->addr);
	अगर (WARN_ON(!sta_priv->link_id)) अणु
		wiphy_info(priv->hw->wiphy,
			   "[AP] No more link IDs available.\n");
		वापस -ENOENT;
	पूर्ण

	entry = &priv->link_id_db[sta_priv->link_id - 1];
	spin_lock_bh(&priv->ps_state_lock);
	अगर ((sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_MASK) ==
					IEEE80211_WMM_IE_STA_QOSINFO_AC_MASK)
		priv->sta_asleep_mask |= BIT(sta_priv->link_id);
	entry->status = CW1200_LINK_HARD;
	जबतक ((skb = skb_dequeue(&entry->rx_queue)))
		ieee80211_rx_irqsafe(priv->hw, skb);
	spin_unlock_bh(&priv->ps_state_lock);
	वापस 0;
पूर्ण

पूर्णांक cw1200_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा cw1200_common *priv = hw->priv;
	काष्ठा cw1200_sta_priv *sta_priv =
			(काष्ठा cw1200_sta_priv *)&sta->drv_priv;
	काष्ठा cw1200_link_entry *entry;

	अगर (priv->mode != NL80211_IFTYPE_AP || !sta_priv->link_id)
		वापस 0;

	entry = &priv->link_id_db[sta_priv->link_id - 1];
	spin_lock_bh(&priv->ps_state_lock);
	entry->status = CW1200_LINK_RESERVE;
	entry->बारtamp = jअगरfies;
	wsm_lock_tx_async(priv);
	अगर (queue_work(priv->workqueue, &priv->link_id_work) <= 0)
		wsm_unlock_tx(priv);
	spin_unlock_bh(&priv->ps_state_lock);
	flush_workqueue(priv->workqueue);
	वापस 0;
पूर्ण

अटल व्योम __cw1200_sta_notअगरy(काष्ठा ieee80211_hw *dev,
				काष्ठा ieee80211_vअगर *vअगर,
				क्रमागत sta_notअगरy_cmd notअगरy_cmd,
				पूर्णांक link_id)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	u32 bit, prev;

	/* Zero link id means "for all link IDs" */
	अगर (link_id)
		bit = BIT(link_id);
	अन्यथा अगर (WARN_ON_ONCE(notअगरy_cmd != STA_NOTIFY_AWAKE))
		bit = 0;
	अन्यथा
		bit = priv->link_id_map;
	prev = priv->sta_asleep_mask & bit;

	चयन (notअगरy_cmd) अणु
	हाल STA_NOTIFY_SLEEP:
		अगर (!prev) अणु
			अगर (priv->buffered_multicasts &&
			    !priv->sta_asleep_mask)
				queue_work(priv->workqueue,
					   &priv->multicast_start_work);
			priv->sta_asleep_mask |= bit;
		पूर्ण
		अवरोध;
	हाल STA_NOTIFY_AWAKE:
		अगर (prev) अणु
			priv->sta_asleep_mask &= ~bit;
			priv->pspoll_mask &= ~bit;
			अगर (priv->tx_multicast && link_id &&
			    !priv->sta_asleep_mask)
				queue_work(priv->workqueue,
					   &priv->multicast_stop_work);
			cw1200_bh_wakeup(priv);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

व्योम cw1200_sta_notअगरy(काष्ठा ieee80211_hw *dev,
		       काष्ठा ieee80211_vअगर *vअगर,
		       क्रमागत sta_notअगरy_cmd notअगरy_cmd,
		       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	काष्ठा cw1200_sta_priv *sta_priv =
		(काष्ठा cw1200_sta_priv *)&sta->drv_priv;

	spin_lock_bh(&priv->ps_state_lock);
	__cw1200_sta_notअगरy(dev, vअगर, notअगरy_cmd, sta_priv->link_id);
	spin_unlock_bh(&priv->ps_state_lock);
पूर्ण

अटल व्योम cw1200_ps_notअगरy(काष्ठा cw1200_common *priv,
		      पूर्णांक link_id, bool ps)
अणु
	अगर (link_id > CW1200_MAX_STA_IN_AP_MODE)
		वापस;

	pr_debug("%s for LinkId: %d. STAs asleep: %.8X\n",
		 ps ? "Stop" : "Start",
		 link_id, priv->sta_asleep_mask);

	__cw1200_sta_notअगरy(priv->hw, priv->vअगर,
			    ps ? STA_NOTIFY_SLEEP : STA_NOTIFY_AWAKE, link_id);
पूर्ण

अटल पूर्णांक cw1200_set_tim_impl(काष्ठा cw1200_common *priv, bool aid0_bit_set)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wsm_update_ie update_ie = अणु
		.what = WSM_UPDATE_IE_BEACON,
		.count = 1,
	पूर्ण;
	u16 tim_offset, tim_length;

	pr_debug("[AP] mcast: %s.\n", aid0_bit_set ? "ena" : "dis");

	skb = ieee80211_beacon_get_tim(priv->hw, priv->vअगर,
			&tim_offset, &tim_length);
	अगर (!skb) अणु
		अगर (!__cw1200_flush(priv, true))
			wsm_unlock_tx(priv);
		वापस -ENOENT;
	पूर्ण

	अगर (tim_offset && tim_length >= 6) अणु
		/* Ignore DTIM count from mac80211:
		 * firmware handles DTIM पूर्णांकernally.
		 */
		skb->data[tim_offset + 2] = 0;

		/* Set/reset aid0 bit */
		अगर (aid0_bit_set)
			skb->data[tim_offset + 4] |= 1;
		अन्यथा
			skb->data[tim_offset + 4] &= ~1;
	पूर्ण

	update_ie.ies = &skb->data[tim_offset];
	update_ie.length = tim_length;
	wsm_update_ie(priv, &update_ie);

	dev_kमुक्त_skb(skb);

	वापस 0;
पूर्ण

व्योम cw1200_set_tim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, set_tim_work);
	(व्योम)cw1200_set_tim_impl(priv, priv->aid0_bit_set);
पूर्ण

पूर्णांक cw1200_set_tim(काष्ठा ieee80211_hw *dev, काष्ठा ieee80211_sta *sta,
		   bool set)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	queue_work(priv->workqueue, &priv->set_tim_work);
	वापस 0;
पूर्ण

व्योम cw1200_set_cts_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, set_cts_work);

	u8 erp_ie[3] = अणुWLAN_EID_ERP_INFO, 0x1, 0पूर्ण;
	काष्ठा wsm_update_ie update_ie = अणु
		.what = WSM_UPDATE_IE_BEACON,
		.count = 1,
		.ies = erp_ie,
		.length = 3,
	पूर्ण;
	u32 erp_info;
	__le32 use_cts_prot;
	mutex_lock(&priv->conf_mutex);
	erp_info = priv->erp_info;
	mutex_unlock(&priv->conf_mutex);
	use_cts_prot =
		erp_info & WLAN_ERP_USE_PROTECTION ?
		__cpu_to_le32(1) : 0;

	erp_ie[ERP_INFO_BYTE_OFFSET] = erp_info;

	pr_debug("[STA] ERP information 0x%x\n", erp_info);

	wsm_ग_लिखो_mib(priv, WSM_MIB_ID_NON_ERP_PROTECTION,
		      &use_cts_prot, माप(use_cts_prot));
	wsm_update_ie(priv, &update_ie);

	वापस;
पूर्ण

अटल पूर्णांक cw1200_set_btcoexinfo(काष्ठा cw1200_common *priv)
अणु
	काष्ठा wsm_override_पूर्णांकernal_txrate arg;
	पूर्णांक ret = 0;

	अगर (priv->mode == NL80211_IFTYPE_STATION) अणु
		/* Plumb PSPOLL and शून्य ढाँचा */
		cw1200_upload_pspoll(priv);
		cw1200_upload_null(priv);
		cw1200_upload_qosnull(priv);
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण

	स_रखो(&arg, 0, माप(काष्ठा wsm_override_पूर्णांकernal_txrate));

	अगर (!priv->vअगर->p2p) अणु
		/* STATION mode */
		अगर (priv->bss_params.operational_rate_set & ~0xF) अणु
			pr_debug("[STA] STA has ERP rates\n");
			/* G or BG mode */
			arg.पूर्णांकernalTxRate = (__ffs(
			priv->bss_params.operational_rate_set & ~0xF));
		पूर्ण अन्यथा अणु
			pr_debug("[STA] STA has non ERP rates\n");
			/* B only mode */
			arg.पूर्णांकernalTxRate = (__ffs(le32_to_cpu(priv->association_mode.basic_rate_set)));
		पूर्ण
		arg.nonErpInternalTxRate = (__ffs(le32_to_cpu(priv->association_mode.basic_rate_set)));
	पूर्ण अन्यथा अणु
		/* P2P mode */
		arg.पूर्णांकernalTxRate = (__ffs(priv->bss_params.operational_rate_set & ~0xF));
		arg.nonErpInternalTxRate = (__ffs(priv->bss_params.operational_rate_set & ~0xF));
	पूर्ण

	pr_debug("[STA] BTCOEX_INFO MODE %d, internalTxRate : %x, nonErpInternalTxRate: %x\n",
		 priv->mode,
		 arg.पूर्णांकernalTxRate,
		 arg.nonErpInternalTxRate);

	ret = wsm_ग_लिखो_mib(priv, WSM_MIB_ID_OVERRIDE_INTERNAL_TX_RATE,
			    &arg, माप(arg));

	वापस ret;
पूर्ण

व्योम cw1200_bss_info_changed(काष्ठा ieee80211_hw *dev,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_bss_conf *info,
			     u32 changed)
अणु
	काष्ठा cw1200_common *priv = dev->priv;
	bool करो_join = false;

	mutex_lock(&priv->conf_mutex);

	pr_debug("BSS CHANGED:  %08x\n", changed);

	/* TODO: BSS_CHANGED_QOS */
	/* TODO: BSS_CHANGED_TXPOWER */

	अगर (changed & BSS_CHANGED_ARP_FILTER) अणु
		काष्ठा wsm_mib_arp_ipv4_filter filter = अणु0पूर्ण;
		पूर्णांक i;

		pr_debug("[STA] BSS_CHANGED_ARP_FILTER cnt: %d\n",
			 info->arp_addr_cnt);

		/* Currently only one IP address is supported by firmware.
		 * In हाल of more IPs arp filtering will be disabled.
		 */
		अगर (info->arp_addr_cnt > 0 &&
		    info->arp_addr_cnt <= WSM_MAX_ARP_IP_ADDRTABLE_ENTRIES) अणु
			क्रम (i = 0; i < info->arp_addr_cnt; i++) अणु
				filter.ipv4addrs[i] = info->arp_addr_list[i];
				pr_debug("[STA] addr[%d]: 0x%X\n",
					 i, filter.ipv4addrs[i]);
			पूर्ण
			filter.enable = __cpu_to_le32(1);
		पूर्ण

		pr_debug("[STA] arp ip filter enable: %d\n",
			 __le32_to_cpu(filter.enable));

		wsm_set_arp_ipv4_filter(priv, &filter);
	पूर्ण

	अगर (changed &
	    (BSS_CHANGED_BEACON |
	     BSS_CHANGED_AP_PROBE_RESP |
	     BSS_CHANGED_BSSID |
	     BSS_CHANGED_SSID |
	     BSS_CHANGED_IBSS)) अणु
		pr_debug("BSS_CHANGED_BEACON\n");
		priv->beacon_पूर्णांक = info->beacon_पूर्णांक;
		cw1200_update_beaconing(priv);
		cw1200_upload_beacon(priv);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_ENABLED) अणु
		pr_debug("BSS_CHANGED_BEACON_ENABLED (%d)\n", info->enable_beacon);

		अगर (priv->enable_beacon != info->enable_beacon) अणु
			cw1200_enable_beaconing(priv, info->enable_beacon);
			priv->enable_beacon = info->enable_beacon;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		pr_debug("CHANGED_BEACON_INT\n");
		अगर (info->ibss_joined)
			करो_join = true;
		अन्यथा अगर (priv->join_status == CW1200_JOIN_STATUS_AP)
			cw1200_update_beaconing(priv);
	पूर्ण

	/* assoc/disassoc, or maybe AID changed */
	अगर (changed & BSS_CHANGED_ASSOC) अणु
		wsm_lock_tx(priv);
		priv->wep_शेष_key_id = -1;
		wsm_unlock_tx(priv);
	पूर्ण

	अगर (changed & BSS_CHANGED_BSSID) अणु
		pr_debug("BSS_CHANGED_BSSID\n");
		करो_join = true;
	पूर्ण

	अगर (changed &
	    (BSS_CHANGED_ASSOC |
	     BSS_CHANGED_BSSID |
	     BSS_CHANGED_IBSS |
	     BSS_CHANGED_BASIC_RATES |
	     BSS_CHANGED_HT)) अणु
		pr_debug("BSS_CHANGED_ASSOC\n");
		अगर (info->assoc) अणु
			अगर (priv->join_status < CW1200_JOIN_STATUS_PRE_STA) अणु
				ieee80211_connection_loss(vअगर);
				mutex_unlock(&priv->conf_mutex);
				वापस;
			पूर्ण अन्यथा अगर (priv->join_status == CW1200_JOIN_STATUS_PRE_STA) अणु
				priv->join_status = CW1200_JOIN_STATUS_STA;
			पूर्ण
		पूर्ण अन्यथा अणु
			करो_join = true;
		पूर्ण

		अगर (info->assoc || info->ibss_joined) अणु
			काष्ठा ieee80211_sta *sta = शून्य;
			__le32 htprot = 0;

			अगर (info->dtim_period)
				priv->join_dtim_period = info->dtim_period;
			priv->beacon_पूर्णांक = info->beacon_पूर्णांक;

			rcu_पढ़ो_lock();

			अगर (info->bssid && !info->ibss_joined)
				sta = ieee80211_find_sta(vअगर, info->bssid);
			अगर (sta) अणु
				priv->ht_info.ht_cap = sta->ht_cap;
				priv->bss_params.operational_rate_set =
					cw1200_rate_mask_to_wsm(priv,
								sta->supp_rates[priv->channel->band]);
				priv->ht_info.channel_type = cfg80211_get_chandef_type(&dev->conf.chandef);
				priv->ht_info.operation_mode = info->ht_operation_mode;
			पूर्ण अन्यथा अणु
				स_रखो(&priv->ht_info, 0,
				       माप(priv->ht_info));
				priv->bss_params.operational_rate_set = -1;
			पूर्ण
			rcu_पढ़ो_unlock();

			/* Non Greenfield stations present */
			अगर (priv->ht_info.operation_mode &
			    IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT)
				htprot |= cpu_to_le32(WSM_NON_GREENFIELD_STA_PRESENT);

			/* Set HT protection method */
			htprot |= cpu_to_le32((priv->ht_info.operation_mode & IEEE80211_HT_OP_MODE_PROTECTION) << 2);

			/* TODO:
			 * STBC_param.dual_cts
			 *  STBC_param.LSIG_TXOP_FILL
			 */

			wsm_ग_लिखो_mib(priv, WSM_MIB_ID_SET_HT_PROTECTION,
				      &htprot, माप(htprot));

			priv->association_mode.greenfield =
				cw1200_ht_greenfield(&priv->ht_info);
			priv->association_mode.flags =
				WSM_ASSOCIATION_MODE_SNOOP_ASSOC_FRAMES |
				WSM_ASSOCIATION_MODE_USE_PREAMBLE_TYPE |
				WSM_ASSOCIATION_MODE_USE_HT_MODE |
				WSM_ASSOCIATION_MODE_USE_BASIC_RATE_SET |
				WSM_ASSOCIATION_MODE_USE_MPDU_START_SPACING;
			priv->association_mode.preamble =
				info->use_लघु_preamble ?
				WSM_JOIN_PREAMBLE_SHORT :
				WSM_JOIN_PREAMBLE_LONG;
			priv->association_mode.basic_rate_set = __cpu_to_le32(
				cw1200_rate_mask_to_wsm(priv,
							info->basic_rates));
			priv->association_mode.mpdu_start_spacing =
				cw1200_ht_ampdu_density(&priv->ht_info);

			cw1200_cqm_bssloss_sm(priv, 0, 0, 0);
			cancel_work_sync(&priv->unjoin_work);

			priv->bss_params.beacon_lost_count = priv->cqm_beacon_loss_count;
			priv->bss_params.aid = info->aid;

			अगर (priv->join_dtim_period < 1)
				priv->join_dtim_period = 1;

			pr_debug("[STA] DTIM %d, interval: %d\n",
				 priv->join_dtim_period, priv->beacon_पूर्णांक);
			pr_debug("[STA] Preamble: %d, Greenfield: %d, Aid: %d, Rates: 0x%.8X, Basic: 0x%.8X\n",
				 priv->association_mode.preamble,
				 priv->association_mode.greenfield,
				 priv->bss_params.aid,
				 priv->bss_params.operational_rate_set,
				 priv->association_mode.basic_rate_set);
			wsm_set_association_mode(priv, &priv->association_mode);

			अगर (!info->ibss_joined) अणु
				wsm_keep_alive_period(priv, 30 /* sec */);
				wsm_set_bss_params(priv, &priv->bss_params);
				priv->setbssparams_करोne = true;
				cw1200_set_beacon_wakeup_period_work(&priv->set_beacon_wakeup_period_work);
				cw1200_set_pm(priv, &priv->घातersave_mode);
			पूर्ण
			अगर (priv->vअगर->p2p) अणु
				pr_debug("[STA] Setting p2p powersave configuration.\n");
				wsm_set_p2p_ps_modeinfo(priv,
							&priv->p2p_ps_modeinfo);
			पूर्ण
			अगर (priv->bt_present)
				cw1200_set_btcoexinfo(priv);
		पूर्ण अन्यथा अणु
			स_रखो(&priv->association_mode, 0,
			       माप(priv->association_mode));
			स_रखो(&priv->bss_params, 0, माप(priv->bss_params));
		पूर्ण
	पूर्ण

	/* ERP Protection */
	अगर (changed & (BSS_CHANGED_ASSOC |
		       BSS_CHANGED_ERP_CTS_PROT |
		       BSS_CHANGED_ERP_PREAMBLE)) अणु
		u32 prev_erp_info = priv->erp_info;
		अगर (info->use_cts_prot)
			priv->erp_info |= WLAN_ERP_USE_PROTECTION;
		अन्यथा अगर (!(prev_erp_info & WLAN_ERP_NON_ERP_PRESENT))
			priv->erp_info &= ~WLAN_ERP_USE_PROTECTION;

		अगर (info->use_लघु_preamble)
			priv->erp_info |= WLAN_ERP_BARKER_PREAMBLE;
		अन्यथा
			priv->erp_info &= ~WLAN_ERP_BARKER_PREAMBLE;

		pr_debug("[STA] ERP Protection: %x\n", priv->erp_info);

		अगर (prev_erp_info != priv->erp_info)
			queue_work(priv->workqueue, &priv->set_cts_work);
	पूर्ण

	/* ERP Slotसमय */
	अगर (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_ERP_SLOT)) अणु
		__le32 slot_समय = info->use_लघु_slot ?
			__cpu_to_le32(9) : __cpu_to_le32(20);
		pr_debug("[STA] Slot time: %d us.\n",
			 __le32_to_cpu(slot_समय));
		wsm_ग_लिखो_mib(priv, WSM_MIB_ID_DOT11_SLOT_TIME,
			      &slot_समय, माप(slot_समय));
	पूर्ण

	अगर (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_CQM)) अणु
		काष्ठा wsm_rcpi_rssi_threshold threshold = अणु
			.rollingAverageCount = 8,
		पूर्ण;
		pr_debug("[CQM] RSSI threshold subscribe: %d +- %d\n",
			 info->cqm_rssi_thold, info->cqm_rssi_hyst);
		priv->cqm_rssi_thold = info->cqm_rssi_thold;
		priv->cqm_rssi_hyst = info->cqm_rssi_hyst;

		अगर (info->cqm_rssi_thold || info->cqm_rssi_hyst) अणु
			/* RSSI subscription enabled */
			/* TODO: It's not a correct way of setting threshold.
			 * Upper and lower must be set equal here and adjusted
			 * in callback. However current implementation is much
			 * more relaible and stable.
			 */

			/* RSSI: चिन्हित Q8.0, RCPI: अचिन्हित Q7.1
			 * RSSI = RCPI / 2 - 110
			 */
			अगर (priv->cqm_use_rssi) अणु
				threshold.upperThreshold =
					info->cqm_rssi_thold + info->cqm_rssi_hyst;
				threshold.lowerThreshold =
					info->cqm_rssi_thold;
				threshold.rssiRcpiMode |= WSM_RCPI_RSSI_USE_RSSI;
			पूर्ण अन्यथा अणु
				threshold.upperThreshold = (info->cqm_rssi_thold + info->cqm_rssi_hyst + 110) * 2;
				threshold.lowerThreshold = (info->cqm_rssi_thold + 110) * 2;
			पूर्ण
			threshold.rssiRcpiMode |= WSM_RCPI_RSSI_THRESHOLD_ENABLE;
		पूर्ण अन्यथा अणु
			/* There is a bug in FW, see sta.c. We have to enable
			 * dummy subscription to get correct RSSI values.
			 */
			threshold.rssiRcpiMode |=
				WSM_RCPI_RSSI_THRESHOLD_ENABLE |
				WSM_RCPI_RSSI_DONT_USE_UPPER |
				WSM_RCPI_RSSI_DONT_USE_LOWER;
			अगर (priv->cqm_use_rssi)
				threshold.rssiRcpiMode |= WSM_RCPI_RSSI_USE_RSSI;
		पूर्ण
		wsm_set_rcpi_rssi_threshold(priv, &threshold);
	पूर्ण
	mutex_unlock(&priv->conf_mutex);

	अगर (करो_join) अणु
		wsm_lock_tx(priv);
		cw1200_करो_join(priv); /* Will unlock it क्रम us */
	पूर्ण
पूर्ण

व्योम cw1200_multicast_start_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, multicast_start_work);
	दीर्घ पंचांगo = priv->join_dtim_period *
			(priv->beacon_पूर्णांक + 20) * HZ / 1024;

	cancel_work_sync(&priv->multicast_stop_work);

	अगर (!priv->aid0_bit_set) अणु
		wsm_lock_tx(priv);
		cw1200_set_tim_impl(priv, true);
		priv->aid0_bit_set = true;
		mod_समयr(&priv->mcast_समयout, jअगरfies + पंचांगo);
		wsm_unlock_tx(priv);
	पूर्ण
पूर्ण

व्योम cw1200_multicast_stop_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, multicast_stop_work);

	अगर (priv->aid0_bit_set) अणु
		del_समयr_sync(&priv->mcast_समयout);
		wsm_lock_tx(priv);
		priv->aid0_bit_set = false;
		cw1200_set_tim_impl(priv, false);
		wsm_unlock_tx(priv);
	पूर्ण
पूर्ण

व्योम cw1200_mcast_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा cw1200_common *priv = from_समयr(priv, t, mcast_समयout);

	wiphy_warn(priv->hw->wiphy,
		   "Multicast delivery timeout.\n");
	spin_lock_bh(&priv->ps_state_lock);
	priv->tx_multicast = priv->aid0_bit_set &&
			priv->buffered_multicasts;
	अगर (priv->tx_multicast)
		cw1200_bh_wakeup(priv);
	spin_unlock_bh(&priv->ps_state_lock);
पूर्ण

पूर्णांक cw1200_ampdu_action(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_ampdu_params *params)
अणु
	/* Aggregation is implemented fully in firmware,
	 * including block ack negotiation. Do not allow
	 * mac80211 stack to करो anything: it पूर्णांकerferes with
	 * the firmware.
	 */

	/* Note that we still need this function stubbed. */
	वापस -ENOTSUPP;
पूर्ण

/* ******************************************************************** */
/* WSM callback								*/
व्योम cw1200_suspend_resume(काष्ठा cw1200_common *priv,
			  काष्ठा wsm_suspend_resume *arg)
अणु
	pr_debug("[AP] %s: %s\n",
		 arg->stop ? "stop" : "start",
		 arg->multicast ? "broadcast" : "unicast");

	अगर (arg->multicast) अणु
		bool cancel_पंचांगo = false;
		spin_lock_bh(&priv->ps_state_lock);
		अगर (arg->stop) अणु
			priv->tx_multicast = false;
		पूर्ण अन्यथा अणु
			/* Firmware sends this indication every DTIM अगर there
			 * is a STA in घातersave connected. There is no reason
			 * to suspend, following wakeup will consume much more
			 * घातer than it could be saved.
			 */
			cw1200_pm_stay_awake(&priv->pm_state,
					     priv->join_dtim_period *
					     (priv->beacon_पूर्णांक + 20) * HZ / 1024);
			priv->tx_multicast = (priv->aid0_bit_set &&
					      priv->buffered_multicasts);
			अगर (priv->tx_multicast) अणु
				cancel_पंचांगo = true;
				cw1200_bh_wakeup(priv);
			पूर्ण
		पूर्ण
		spin_unlock_bh(&priv->ps_state_lock);
		अगर (cancel_पंचांगo)
			del_समयr_sync(&priv->mcast_समयout);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&priv->ps_state_lock);
		cw1200_ps_notअगरy(priv, arg->link_id, arg->stop);
		spin_unlock_bh(&priv->ps_state_lock);
		अगर (!arg->stop)
			cw1200_bh_wakeup(priv);
	पूर्ण
	वापस;
पूर्ण

/* ******************************************************************** */
/* AP निजीs								*/

अटल पूर्णांक cw1200_upload_beacon(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret = 0;
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा wsm_ढाँचा_frame frame = अणु
		.frame_type = WSM_FRAME_TYPE_BEACON,
	पूर्ण;

	u16 tim_offset;
	u16 tim_len;

	अगर (priv->mode == NL80211_IFTYPE_STATION ||
	    priv->mode == NL80211_IFTYPE_MONITOR ||
	    priv->mode == NL80211_IFTYPE_UNSPECIFIED)
		जाओ करोne;

	अगर (priv->vअगर->p2p)
		frame.rate = WSM_TRANSMIT_RATE_6;

	frame.skb = ieee80211_beacon_get_tim(priv->hw, priv->vअगर,
					     &tim_offset, &tim_len);
	अगर (!frame.skb)
		वापस -ENOMEM;

	ret = wsm_set_ढाँचा_frame(priv, &frame);

	अगर (ret)
		जाओ करोne;

	/* TODO: Distill probe resp; हटाओ TIM
	 * and any other beacon-specअगरic IEs
	 */
	mgmt = (व्योम *)frame.skb->data;
	mgmt->frame_control =
		__cpu_to_le16(IEEE80211_FTYPE_MGMT |
			      IEEE80211_STYPE_PROBE_RESP);

	frame.frame_type = WSM_FRAME_TYPE_PROBE_RESPONSE;
	अगर (priv->vअगर->p2p) अणु
		ret = wsm_set_probe_responder(priv, true);
	पूर्ण अन्यथा अणु
		ret = wsm_set_ढाँचा_frame(priv, &frame);
		wsm_set_probe_responder(priv, false);
	पूर्ण

करोne:
	dev_kमुक्त_skb(frame.skb);

	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_upload_pspoll(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret = 0;
	काष्ठा wsm_ढाँचा_frame frame = अणु
		.frame_type = WSM_FRAME_TYPE_PS_POLL,
		.rate = 0xFF,
	पूर्ण;


	frame.skb = ieee80211_pspoll_get(priv->hw, priv->vअगर);
	अगर (!frame.skb)
		वापस -ENOMEM;

	ret = wsm_set_ढाँचा_frame(priv, &frame);

	dev_kमुक्त_skb(frame.skb);

	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_upload_null(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret = 0;
	काष्ठा wsm_ढाँचा_frame frame = अणु
		.frame_type = WSM_FRAME_TYPE_शून्य,
		.rate = 0xFF,
	पूर्ण;

	frame.skb = ieee80211_nullfunc_get(priv->hw, priv->vअगर, false);
	अगर (!frame.skb)
		वापस -ENOMEM;

	ret = wsm_set_ढाँचा_frame(priv, &frame);

	dev_kमुक्त_skb(frame.skb);

	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_upload_qosnull(काष्ठा cw1200_common *priv)
अणु
	/* TODO:  This needs to be implemented

	काष्ठा wsm_ढाँचा_frame frame = अणु
		.frame_type = WSM_FRAME_TYPE_QOS_शून्य,
		.rate = 0xFF,
	पूर्ण;

	frame.skb = ieee80211_qosnullfunc_get(priv->hw, priv->vअगर);
	अगर (!frame.skb)
		वापस -ENOMEM;

	ret = wsm_set_ढाँचा_frame(priv, &frame);

	dev_kमुक्त_skb(frame.skb);

	*/
	वापस 0;
पूर्ण

अटल पूर्णांक cw1200_enable_beaconing(काष्ठा cw1200_common *priv,
				   bool enable)
अणु
	काष्ठा wsm_beacon_transmit transmit = अणु
		.enable_beaconing = enable,
	पूर्ण;

	वापस wsm_beacon_transmit(priv, &transmit);
पूर्ण

अटल पूर्णांक cw1200_start_ap(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret;
	काष्ठा ieee80211_bss_conf *conf = &priv->vअगर->bss_conf;
	काष्ठा wsm_start start = अणु
		.mode = priv->vअगर->p2p ?
				WSM_START_MODE_P2P_GO : WSM_START_MODE_AP,
		.band = (priv->channel->band == NL80211_BAND_5GHZ) ?
				WSM_PHY_BAND_5G : WSM_PHY_BAND_2_4G,
		.channel_number = priv->channel->hw_value,
		.beacon_पूर्णांकerval = conf->beacon_पूर्णांक,
		.dtim_period = conf->dtim_period,
		.preamble = conf->use_लघु_preamble ?
				WSM_JOIN_PREAMBLE_SHORT :
				WSM_JOIN_PREAMBLE_LONG,
		.probe_delay = 100,
		.basic_rate_set = cw1200_rate_mask_to_wsm(priv,
				conf->basic_rates),
	पूर्ण;
	काष्ठा wsm_operational_mode mode = अणु
		.घातer_mode = cw1200_घातer_mode,
		.disable_more_flag_usage = true,
	पूर्ण;

	स_रखो(start.ssid, 0, माप(start.ssid));
	अगर (!conf->hidden_ssid) अणु
		start.ssid_len = conf->ssid_len;
		स_नकल(start.ssid, conf->ssid, start.ssid_len);
	पूर्ण

	priv->beacon_पूर्णांक = conf->beacon_पूर्णांक;
	priv->join_dtim_period = conf->dtim_period;

	स_रखो(&priv->link_id_db, 0, माप(priv->link_id_db));

	pr_debug("[AP] ch: %d(%d), bcn: %d(%d), brt: 0x%.8X, ssid: %.*s.\n",
		 start.channel_number, start.band,
		 start.beacon_पूर्णांकerval, start.dtim_period,
		 start.basic_rate_set,
		 start.ssid_len, start.ssid);
	ret = wsm_start(priv, &start);
	अगर (!ret)
		ret = cw1200_upload_keys(priv);
	अगर (!ret && priv->vअगर->p2p) अणु
		pr_debug("[AP] Setting p2p powersave configuration.\n");
		wsm_set_p2p_ps_modeinfo(priv, &priv->p2p_ps_modeinfo);
	पूर्ण
	अगर (!ret) अणु
		wsm_set_block_ack_policy(priv, 0, 0);
		priv->join_status = CW1200_JOIN_STATUS_AP;
		cw1200_update_filtering(priv);
	पूर्ण
	wsm_set_operational_mode(priv, &mode);
	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_update_beaconing(काष्ठा cw1200_common *priv)
अणु
	काष्ठा ieee80211_bss_conf *conf = &priv->vअगर->bss_conf;
	काष्ठा wsm_reset reset = अणु
		.link_id = 0,
		.reset_statistics = true,
	पूर्ण;

	अगर (priv->mode == NL80211_IFTYPE_AP) अणु
		/* TODO: check अगर changed channel, band */
		अगर (priv->join_status != CW1200_JOIN_STATUS_AP ||
		    priv->beacon_पूर्णांक != conf->beacon_पूर्णांक) अणु
			pr_debug("ap restarting\n");
			wsm_lock_tx(priv);
			अगर (priv->join_status != CW1200_JOIN_STATUS_PASSIVE)
				wsm_reset(priv, &reset);
			priv->join_status = CW1200_JOIN_STATUS_PASSIVE;
			cw1200_start_ap(priv);
			wsm_unlock_tx(priv);
		पूर्ण अन्यथा
			pr_debug("ap started join_status: %d\n",
				 priv->join_status);
	पूर्ण
	वापस 0;
पूर्ण
