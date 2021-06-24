<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mac80211 घातer management API क्रम ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2011, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#समावेश <linux/module.h>
#समावेश <linux/अगर_ether.h>
#समावेश "cw1200.h"
#समावेश "pm.h"
#समावेश "sta.h"
#समावेश "bh.h"
#समावेश "hwbus.h"

#घोषणा CW1200_BEACON_SKIPPING_MULTIPLIER 3

काष्ठा cw1200_udp_port_filter अणु
	काष्ठा wsm_udp_port_filter_hdr hdr;
	/* Up to 4 filters are allowed. */
	काष्ठा wsm_udp_port_filter filters[WSM_MAX_FILTER_ELEMENTS];
पूर्ण __packed;

काष्ठा cw1200_ether_type_filter अणु
	काष्ठा wsm_ether_type_filter_hdr hdr;
	/* Up to 4 filters are allowed. */
	काष्ठा wsm_ether_type_filter filters[WSM_MAX_FILTER_ELEMENTS];
पूर्ण __packed;

अटल काष्ठा cw1200_udp_port_filter cw1200_udp_port_filter_on = अणु
	.hdr.num = 2,
	.filters = अणु
		[0] = अणु
			.action = WSM_FILTER_ACTION_FILTER_OUT,
			.type = WSM_FILTER_PORT_TYPE_DST,
			.port = __cpu_to_le16(67), /* DHCP Bootps */
		पूर्ण,
		[1] = अणु
			.action = WSM_FILTER_ACTION_FILTER_OUT,
			.type = WSM_FILTER_PORT_TYPE_DST,
			.port = __cpu_to_le16(68), /* DHCP Bootpc */
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा wsm_udp_port_filter_hdr cw1200_udp_port_filter_off = अणु
	.num = 0,
पूर्ण;

#अगर_अघोषित ETH_P_WAPI
#घोषणा ETH_P_WAPI     0x88B4
#पूर्ण_अगर

अटल काष्ठा cw1200_ether_type_filter cw1200_ether_type_filter_on = अणु
	.hdr.num = 4,
	.filters = अणु
		[0] = अणु
			.action = WSM_FILTER_ACTION_FILTER_IN,
			.type = __cpu_to_le16(ETH_P_IP),
		पूर्ण,
		[1] = अणु
			.action = WSM_FILTER_ACTION_FILTER_IN,
			.type = __cpu_to_le16(ETH_P_PAE),
		पूर्ण,
		[2] = अणु
			.action = WSM_FILTER_ACTION_FILTER_IN,
			.type = __cpu_to_le16(ETH_P_WAPI),
		पूर्ण,
		[3] = अणु
			.action = WSM_FILTER_ACTION_FILTER_IN,
			.type = __cpu_to_le16(ETH_P_ARP),
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा wsm_ether_type_filter_hdr cw1200_ether_type_filter_off = अणु
	.num = 0,
पूर्ण;

/* निजी */
काष्ठा cw1200_suspend_state अणु
	अचिन्हित दीर्घ bss_loss_पंचांगo;
	अचिन्हित दीर्घ join_पंचांगo;
	अचिन्हित दीर्घ direct_probe;
	अचिन्हित दीर्घ link_id_gc;
	bool beacon_skipping;
	u8 prev_ps_mode;
पूर्ण;

अटल व्योम cw1200_pm_stay_awake_पंचांगo(काष्ठा समयr_list *unused)
अणु
	/* XXX what's the poपूर्णांक of this ? */
पूर्ण

पूर्णांक cw1200_pm_init(काष्ठा cw1200_pm_state *pm,
		   काष्ठा cw1200_common *priv)
अणु
	spin_lock_init(&pm->lock);

	समयr_setup(&pm->stay_awake, cw1200_pm_stay_awake_पंचांगo, 0);

	वापस 0;
पूर्ण

व्योम cw1200_pm_deinit(काष्ठा cw1200_pm_state *pm)
अणु
	del_समयr_sync(&pm->stay_awake);
पूर्ण

व्योम cw1200_pm_stay_awake(काष्ठा cw1200_pm_state *pm,
			  अचिन्हित दीर्घ पंचांगo)
अणु
	दीर्घ cur_पंचांगo;
	spin_lock_bh(&pm->lock);
	cur_पंचांगo = pm->stay_awake.expires - jअगरfies;
	अगर (!समयr_pending(&pm->stay_awake) || cur_पंचांगo < (दीर्घ)पंचांगo)
		mod_समयr(&pm->stay_awake, jअगरfies + पंचांगo);
	spin_unlock_bh(&pm->lock);
पूर्ण

अटल दीर्घ cw1200_suspend_work(काष्ठा delayed_work *work)
अणु
	पूर्णांक ret = cancel_delayed_work(work);
	दीर्घ पंचांगo;
	अगर (ret > 0) अणु
		/* Timer is pending */
		पंचांगo = work->समयr.expires - jअगरfies;
		अगर (पंचांगo < 0)
			पंचांगo = 0;
	पूर्ण अन्यथा अणु
		पंचांगo = -1;
	पूर्ण
	वापस पंचांगo;
पूर्ण

अटल पूर्णांक cw1200_resume_work(काष्ठा cw1200_common *priv,
			       काष्ठा delayed_work *work,
			       अचिन्हित दीर्घ पंचांगo)
अणु
	अगर ((दीर्घ)पंचांगo < 0)
		वापस 1;

	वापस queue_delayed_work(priv->workqueue, work, पंचांगo);
पूर्ण

पूर्णांक cw1200_can_suspend(काष्ठा cw1200_common *priv)
अणु
	अगर (atomic_पढ़ो(&priv->bh_rx)) अणु
		wiphy_dbg(priv->hw->wiphy, "Suspend interrupted.\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(cw1200_can_suspend);

पूर्णांक cw1200_wow_suspend(काष्ठा ieee80211_hw *hw, काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा cw1200_common *priv = hw->priv;
	काष्ठा cw1200_pm_state *pm_state = &priv->pm_state;
	काष्ठा cw1200_suspend_state *state;
	पूर्णांक ret;

	spin_lock_bh(&pm_state->lock);
	ret = समयr_pending(&pm_state->stay_awake);
	spin_unlock_bh(&pm_state->lock);
	अगर (ret)
		वापस -EAGAIN;

	/* Do not suspend when datapath is not idle */
	अगर (priv->tx_queue_stats.num_queued)
		वापस -EBUSY;

	/* Make sure there is no configuration requests in progress. */
	अगर (!mutex_trylock(&priv->conf_mutex))
		वापस -EBUSY;

	/* Ensure pending operations are करोne.
	 * Note also that wow_suspend must वापस in ~2.5sec, beक्रमe
	 * watchकरोg is triggered.
	 */
	अगर (priv->channel_चयन_in_progress)
		जाओ revert1;

	/* Do not suspend when join is pending */
	अगर (priv->join_pending)
		जाओ revert1;

	/* Do not suspend when scanning */
	अगर (करोwn_trylock(&priv->scan.lock))
		जाओ revert1;

	/* Lock TX. */
	wsm_lock_tx_async(priv);

	/* Wait to aव्योम possible race with bh code.
	 * But करो not रुको too दीर्घ...
	 */
	अगर (रुको_event_समयout(priv->bh_evt_wq,
			       !priv->hw_bufs_used, HZ / 10) <= 0)
		जाओ revert2;

	/* Set UDP filter */
	wsm_set_udp_port_filter(priv, &cw1200_udp_port_filter_on.hdr);

	/* Set ethernet frame type filter */
	wsm_set_ether_type_filter(priv, &cw1200_ether_type_filter_on.hdr);

	/* Allocate state */
	state = kzalloc(माप(काष्ठा cw1200_suspend_state), GFP_KERNEL);
	अगर (!state)
		जाओ revert3;

	/* Change to legacy PS जबतक going to suspend */
	अगर (!priv->vअगर->p2p &&
	    priv->join_status == CW1200_JOIN_STATUS_STA &&
	    priv->घातersave_mode.mode != WSM_PSM_PS) अणु
		state->prev_ps_mode = priv->घातersave_mode.mode;
		priv->घातersave_mode.mode = WSM_PSM_PS;
		cw1200_set_pm(priv, &priv->घातersave_mode);
		अगर (रुको_event_पूर्णांकerruptible_समयout(priv->ps_mode_चयन_करोne,
						     !priv->ps_mode_चयन_in_progress, 1*HZ) <= 0) अणु
			जाओ revert4;
		पूर्ण
	पूर्ण

	/* Store delayed work states. */
	state->bss_loss_पंचांगo =
		cw1200_suspend_work(&priv->bss_loss_work);
	state->join_पंचांगo =
		cw1200_suspend_work(&priv->join_समयout);
	state->direct_probe =
		cw1200_suspend_work(&priv->scan.probe_work);
	state->link_id_gc =
		cw1200_suspend_work(&priv->link_id_gc_work);

	cancel_delayed_work_sync(&priv->clear_recent_scan_work);
	atomic_set(&priv->recent_scan, 0);

	/* Enable beacon skipping */
	अगर (priv->join_status == CW1200_JOIN_STATUS_STA &&
	    priv->join_dtim_period &&
	    !priv->has_multicast_subscription) अणु
		state->beacon_skipping = true;
		wsm_set_beacon_wakeup_period(priv,
					     priv->join_dtim_period,
					     CW1200_BEACON_SKIPPING_MULTIPLIER * priv->join_dtim_period);
	पूर्ण

	/* Stop serving thपढ़ो */
	अगर (cw1200_bh_suspend(priv))
		जाओ revert5;

	ret = समयr_pending(&priv->mcast_समयout);
	अगर (ret)
		जाओ revert6;

	/* Store suspend state */
	pm_state->suspend_state = state;

	/* Enable IRQ wake */
	ret = priv->hwbus_ops->घातer_mgmt(priv->hwbus_priv, true);
	अगर (ret) अणु
		wiphy_err(priv->hw->wiphy,
			  "PM request failed: %d. WoW is disabled.\n", ret);
		cw1200_wow_resume(hw);
		वापस -EBUSY;
	पूर्ण

	/* Force resume अगर event is coming from the device. */
	अगर (atomic_पढ़ो(&priv->bh_rx)) अणु
		cw1200_wow_resume(hw);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;

revert6:
	WARN_ON(cw1200_bh_resume(priv));
revert5:
	cw1200_resume_work(priv, &priv->bss_loss_work,
			   state->bss_loss_पंचांगo);
	cw1200_resume_work(priv, &priv->join_समयout,
			   state->join_पंचांगo);
	cw1200_resume_work(priv, &priv->scan.probe_work,
			   state->direct_probe);
	cw1200_resume_work(priv, &priv->link_id_gc_work,
			   state->link_id_gc);
revert4:
	kमुक्त(state);
revert3:
	wsm_set_udp_port_filter(priv, &cw1200_udp_port_filter_off);
	wsm_set_ether_type_filter(priv, &cw1200_ether_type_filter_off);
revert2:
	wsm_unlock_tx(priv);
	up(&priv->scan.lock);
revert1:
	mutex_unlock(&priv->conf_mutex);
	वापस -EBUSY;
पूर्ण

पूर्णांक cw1200_wow_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा cw1200_common *priv = hw->priv;
	काष्ठा cw1200_pm_state *pm_state = &priv->pm_state;
	काष्ठा cw1200_suspend_state *state;

	state = pm_state->suspend_state;
	pm_state->suspend_state = शून्य;

	/* Disable IRQ wake */
	priv->hwbus_ops->घातer_mgmt(priv->hwbus_priv, false);

	/* Scan.lock must be released beक्रमe BH is resumed other way
	 * in हाल when BSS_LOST command arrived the processing of the
	 * command will be delayed.
	 */
	up(&priv->scan.lock);

	/* Resume BH thपढ़ो */
	WARN_ON(cw1200_bh_resume(priv));

	/* Restores previous PS mode */
	अगर (!priv->vअगर->p2p && priv->join_status == CW1200_JOIN_STATUS_STA) अणु
		priv->घातersave_mode.mode = state->prev_ps_mode;
		cw1200_set_pm(priv, &priv->घातersave_mode);
	पूर्ण

	अगर (state->beacon_skipping) अणु
		wsm_set_beacon_wakeup_period(priv, priv->beacon_पूर्णांक *
					     priv->join_dtim_period >
					     MAX_BEACON_SKIP_TIME_MS ? 1 :
					     priv->join_dtim_period, 0);
		state->beacon_skipping = false;
	पूर्ण

	/* Resume delayed work */
	cw1200_resume_work(priv, &priv->bss_loss_work,
			   state->bss_loss_पंचांगo);
	cw1200_resume_work(priv, &priv->join_समयout,
			   state->join_पंचांगo);
	cw1200_resume_work(priv, &priv->scan.probe_work,
			   state->direct_probe);
	cw1200_resume_work(priv, &priv->link_id_gc_work,
			   state->link_id_gc);

	/* Remove UDP port filter */
	wsm_set_udp_port_filter(priv, &cw1200_udp_port_filter_off);

	/* Remove ethernet frame type filter */
	wsm_set_ether_type_filter(priv, &cw1200_ether_type_filter_off);

	/* Unlock datapath */
	wsm_unlock_tx(priv);

	/* Unlock configuration mutex */
	mutex_unlock(&priv->conf_mutex);

	/* Free memory */
	kमुक्त(state);

	वापस 0;
पूर्ण
