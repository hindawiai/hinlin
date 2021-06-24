<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Scan implementation क्रम ST-Ericsson CW1200 mac80211 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#समावेश <linux/sched.h>
#समावेश "cw1200.h"
#समावेश "scan.h"
#समावेश "sta.h"
#समावेश "pm.h"

अटल व्योम cw1200_scan_restart_delayed(काष्ठा cw1200_common *priv);

अटल पूर्णांक cw1200_scan_start(काष्ठा cw1200_common *priv, काष्ठा wsm_scan *scan)
अणु
	पूर्णांक ret, i;
	पूर्णांक पंचांगo = 2000;

	चयन (priv->join_status) अणु
	हाल CW1200_JOIN_STATUS_PRE_STA:
	हाल CW1200_JOIN_STATUS_JOINING:
		वापस -EBUSY;
	शेष:
		अवरोध;
	पूर्ण

	wiphy_dbg(priv->hw->wiphy, "[SCAN] hw req, type %d, %d channels, flags: 0x%x.\n",
		  scan->type, scan->num_channels, scan->flags);

	क्रम (i = 0; i < scan->num_channels; ++i)
		पंचांगo += scan->ch[i].max_chan_समय + 10;

	cancel_delayed_work_sync(&priv->clear_recent_scan_work);
	atomic_set(&priv->scan.in_progress, 1);
	atomic_set(&priv->recent_scan, 1);
	cw1200_pm_stay_awake(&priv->pm_state, msecs_to_jअगरfies(पंचांगo));
	queue_delayed_work(priv->workqueue, &priv->scan.समयout,
			   msecs_to_jअगरfies(पंचांगo));
	ret = wsm_scan(priv, scan);
	अगर (ret) अणु
		atomic_set(&priv->scan.in_progress, 0);
		cancel_delayed_work_sync(&priv->scan.समयout);
		cw1200_scan_restart_delayed(priv);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक cw1200_hw_scan(काष्ठा ieee80211_hw *hw,
		   काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा cw1200_common *priv = hw->priv;
	काष्ठा cfg80211_scan_request *req = &hw_req->req;
	काष्ठा wsm_ढाँचा_frame frame = अणु
		.frame_type = WSM_FRAME_TYPE_PROBE_REQUEST,
	पूर्ण;
	पूर्णांक i, ret;

	अगर (!priv->vअगर)
		वापस -EINVAL;

	/* Scan when P2P_GO corrupt firmware MiniAP mode */
	अगर (priv->join_status == CW1200_JOIN_STATUS_AP)
		वापस -EOPNOTSUPP;

	अगर (req->n_ssids == 1 && !req->ssids[0].ssid_len)
		req->n_ssids = 0;

	wiphy_dbg(hw->wiphy, "[SCAN] Scan request for %d SSIDs.\n",
		  req->n_ssids);

	अगर (req->n_ssids > WSM_SCAN_MAX_NUM_OF_SSIDS)
		वापस -EINVAL;

	/* will be unlocked in cw1200_scan_work() */
	करोwn(&priv->scan.lock);
	mutex_lock(&priv->conf_mutex);

	frame.skb = ieee80211_probereq_get(hw, priv->vअगर->addr, शून्य, 0,
		req->ie_len);
	अगर (!frame.skb) अणु
		mutex_unlock(&priv->conf_mutex);
		up(&priv->scan.lock);
		वापस -ENOMEM;
	पूर्ण

	अगर (req->ie_len)
		skb_put_data(frame.skb, req->ie, req->ie_len);

	ret = wsm_set_ढाँचा_frame(priv, &frame);
	अगर (!ret) अणु
		/* Host want to be the probe responder. */
		ret = wsm_set_probe_responder(priv, true);
	पूर्ण
	अगर (ret) अणु
		dev_kमुक्त_skb(frame.skb);
		mutex_unlock(&priv->conf_mutex);
		up(&priv->scan.lock);
		वापस ret;
	पूर्ण

	wsm_lock_tx(priv);

	BUG_ON(priv->scan.req);
	priv->scan.req = req;
	priv->scan.n_ssids = 0;
	priv->scan.status = 0;
	priv->scan.begin = &req->channels[0];
	priv->scan.curr = priv->scan.begin;
	priv->scan.end = &req->channels[req->n_channels];
	priv->scan.output_घातer = priv->output_घातer;

	क्रम (i = 0; i < req->n_ssids; ++i) अणु
		काष्ठा wsm_ssid *dst = &priv->scan.ssids[priv->scan.n_ssids];
		स_नकल(&dst->ssid[0], req->ssids[i].ssid, माप(dst->ssid));
		dst->length = req->ssids[i].ssid_len;
		++priv->scan.n_ssids;
	पूर्ण

	dev_kमुक्त_skb(frame.skb);
	mutex_unlock(&priv->conf_mutex);
	queue_work(priv->workqueue, &priv->scan.work);
	वापस 0;
पूर्ण

व्योम cw1200_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv = container_of(work, काष्ठा cw1200_common,
							scan.work);
	काष्ठा ieee80211_channel **it;
	काष्ठा wsm_scan scan = अणु
		.type = WSM_SCAN_TYPE_FOREGROUND,
		.flags = WSM_SCAN_FLAG_SPLIT_METHOD,
	पूर्ण;
	bool first_run = (priv->scan.begin == priv->scan.curr &&
			  priv->scan.begin != priv->scan.end);
	पूर्णांक i;

	अगर (first_run) अणु
		/* Firmware माला_लो crazy अगर scan request is sent
		 * when STA is joined but not yet associated.
		 * Force unjoin in this हाल.
		 */
		अगर (cancel_delayed_work_sync(&priv->join_समयout) > 0)
			cw1200_join_समयout(&priv->join_समयout.work);
	पूर्ण

	mutex_lock(&priv->conf_mutex);

	अगर (first_run) अणु
		अगर (priv->join_status == CW1200_JOIN_STATUS_STA &&
		    !(priv->घातersave_mode.mode & WSM_PSM_PS)) अणु
			काष्ठा wsm_set_pm pm = priv->घातersave_mode;
			pm.mode = WSM_PSM_PS;
			cw1200_set_pm(priv, &pm);
		पूर्ण अन्यथा अगर (priv->join_status == CW1200_JOIN_STATUS_MONITOR) अणु
			/* FW bug: driver has to restart p2p-dev mode
			 * after scan
			 */
			cw1200_disable_listening(priv);
		पूर्ण
	पूर्ण

	अगर (!priv->scan.req || (priv->scan.curr == priv->scan.end)) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = priv->scan.status ? 1 : 0,
		पूर्ण;

		अगर (priv->scan.output_घातer != priv->output_घातer)
			wsm_set_output_घातer(priv, priv->output_घातer * 10);
		अगर (priv->join_status == CW1200_JOIN_STATUS_STA &&
		    !(priv->घातersave_mode.mode & WSM_PSM_PS))
			cw1200_set_pm(priv, &priv->घातersave_mode);

		अगर (priv->scan.status < 0)
			wiphy_warn(priv->hw->wiphy,
				   "[SCAN] Scan failed (%d).\n",
				   priv->scan.status);
		अन्यथा अगर (priv->scan.req)
			wiphy_dbg(priv->hw->wiphy,
				  "[SCAN] Scan completed.\n");
		अन्यथा
			wiphy_dbg(priv->hw->wiphy,
				  "[SCAN] Scan canceled.\n");

		priv->scan.req = शून्य;
		cw1200_scan_restart_delayed(priv);
		wsm_unlock_tx(priv);
		mutex_unlock(&priv->conf_mutex);
		ieee80211_scan_completed(priv->hw, &info);
		up(&priv->scan.lock);
		वापस;
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_channel *first = *priv->scan.curr;
		क्रम (it = priv->scan.curr + 1, i = 1;
		     it != priv->scan.end && i < WSM_SCAN_MAX_NUM_OF_CHANNELS;
		     ++it, ++i) अणु
			अगर ((*it)->band != first->band)
				अवरोध;
			अगर (((*it)->flags ^ first->flags) &
					IEEE80211_CHAN_NO_IR)
				अवरोध;
			अगर (!(first->flags & IEEE80211_CHAN_NO_IR) &&
			    (*it)->max_घातer != first->max_घातer)
				अवरोध;
		पूर्ण
		scan.band = first->band;

		अगर (priv->scan.req->no_cck)
			scan.max_tx_rate = WSM_TRANSMIT_RATE_6;
		अन्यथा
			scan.max_tx_rate = WSM_TRANSMIT_RATE_1;
		scan.num_probes =
			(first->flags & IEEE80211_CHAN_NO_IR) ? 0 : 2;
		scan.num_ssids = priv->scan.n_ssids;
		scan.ssids = &priv->scan.ssids[0];
		scan.num_channels = it - priv->scan.curr;
		/* TODO: Is it optimal? */
		scan.probe_delay = 100;
		/* It is not stated in WSM specअगरication, however
		 * FW team says that driver may not use FG scan
		 * when joined.
		 */
		अगर (priv->join_status == CW1200_JOIN_STATUS_STA) अणु
			scan.type = WSM_SCAN_TYPE_BACKGROUND;
			scan.flags = WSM_SCAN_FLAG_FORCE_BACKGROUND;
		पूर्ण
		scan.ch = kसुस्मृति(it - priv->scan.curr,
				  माप(काष्ठा wsm_scan_ch),
				  GFP_KERNEL);
		अगर (!scan.ch) अणु
			priv->scan.status = -ENOMEM;
			जाओ fail;
		पूर्ण
		क्रम (i = 0; i < scan.num_channels; ++i) अणु
			scan.ch[i].number = priv->scan.curr[i]->hw_value;
			अगर (priv->scan.curr[i]->flags & IEEE80211_CHAN_NO_IR) अणु
				scan.ch[i].min_chan_समय = 50;
				scan.ch[i].max_chan_समय = 100;
			पूर्ण अन्यथा अणु
				scan.ch[i].min_chan_समय = 10;
				scan.ch[i].max_chan_समय = 25;
			पूर्ण
		पूर्ण
		अगर (!(first->flags & IEEE80211_CHAN_NO_IR) &&
		    priv->scan.output_घातer != first->max_घातer) अणु
			priv->scan.output_घातer = first->max_घातer;
			wsm_set_output_घातer(priv,
					     priv->scan.output_घातer * 10);
		पूर्ण
		priv->scan.status = cw1200_scan_start(priv, &scan);
		kमुक्त(scan.ch);
		अगर (priv->scan.status)
			जाओ fail;
		priv->scan.curr = it;
	पूर्ण
	mutex_unlock(&priv->conf_mutex);
	वापस;

fail:
	priv->scan.curr = priv->scan.end;
	mutex_unlock(&priv->conf_mutex);
	queue_work(priv->workqueue, &priv->scan.work);
	वापस;
पूर्ण

अटल व्योम cw1200_scan_restart_delayed(काष्ठा cw1200_common *priv)
अणु
	/* FW bug: driver has to restart p2p-dev mode after scan. */
	अगर (priv->join_status == CW1200_JOIN_STATUS_MONITOR) अणु
		cw1200_enable_listening(priv);
		cw1200_update_filtering(priv);
	पूर्ण

	अगर (priv->delayed_unjoin) अणु
		priv->delayed_unjoin = false;
		अगर (queue_work(priv->workqueue, &priv->unjoin_work) <= 0)
			wsm_unlock_tx(priv);
	पूर्ण अन्यथा अगर (priv->delayed_link_loss) अणु
			wiphy_dbg(priv->hw->wiphy, "[CQM] Requeue BSS loss.\n");
			priv->delayed_link_loss = 0;
			cw1200_cqm_bssloss_sm(priv, 1, 0, 0);
	पूर्ण
पूर्ण

अटल व्योम cw1200_scan_complete(काष्ठा cw1200_common *priv)
अणु
	queue_delayed_work(priv->workqueue, &priv->clear_recent_scan_work, HZ);
	अगर (priv->scan.direct_probe) अणु
		wiphy_dbg(priv->hw->wiphy, "[SCAN] Direct probe complete.\n");
		cw1200_scan_restart_delayed(priv);
		priv->scan.direct_probe = 0;
		up(&priv->scan.lock);
		wsm_unlock_tx(priv);
	पूर्ण अन्यथा अणु
		cw1200_scan_work(&priv->scan.work);
	पूर्ण
पूर्ण

व्योम cw1200_scan_failed_cb(काष्ठा cw1200_common *priv)
अणु
	अगर (priv->mode == NL80211_IFTYPE_UNSPECIFIED)
		/* STA is stopped. */
		वापस;

	अगर (cancel_delayed_work_sync(&priv->scan.समयout) > 0) अणु
		priv->scan.status = -EIO;
		queue_delayed_work(priv->workqueue, &priv->scan.समयout, 0);
	पूर्ण
पूर्ण


व्योम cw1200_scan_complete_cb(काष्ठा cw1200_common *priv,
				काष्ठा wsm_scan_complete *arg)
अणु
	अगर (priv->mode == NL80211_IFTYPE_UNSPECIFIED)
		/* STA is stopped. */
		वापस;

	अगर (cancel_delayed_work_sync(&priv->scan.समयout) > 0) अणु
		priv->scan.status = 1;
		queue_delayed_work(priv->workqueue, &priv->scan.समयout, 0);
	पूर्ण
पूर्ण

व्योम cw1200_clear_recent_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common,
			     clear_recent_scan_work.work);
	atomic_xchg(&priv->recent_scan, 0);
पूर्ण

व्योम cw1200_scan_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, scan.समयout.work);
	अगर (atomic_xchg(&priv->scan.in_progress, 0)) अणु
		अगर (priv->scan.status > 0) अणु
			priv->scan.status = 0;
		पूर्ण अन्यथा अगर (!priv->scan.status) अणु
			wiphy_warn(priv->hw->wiphy,
				   "Timeout waiting for scan complete notification.\n");
			priv->scan.status = -ETIMEDOUT;
			priv->scan.curr = priv->scan.end;
			wsm_stop_scan(priv);
		पूर्ण
		cw1200_scan_complete(priv);
	पूर्ण
पूर्ण

व्योम cw1200_probe_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
		container_of(work, काष्ठा cw1200_common, scan.probe_work.work);
	u8 queue_id = cw1200_queue_get_queue_id(priv->pending_frame_id);
	काष्ठा cw1200_queue *queue = &priv->tx_queue[queue_id];
	स्थिर काष्ठा cw1200_txpriv *txpriv;
	काष्ठा wsm_tx *wsm;
	काष्ठा wsm_ढाँचा_frame frame = अणु
		.frame_type = WSM_FRAME_TYPE_PROBE_REQUEST,
	पूर्ण;
	काष्ठा wsm_ssid ssids[1] = अणुअणु
		.length = 0,
	पूर्ण पूर्ण;
	काष्ठा wsm_scan_ch ch[1] = अणुअणु
		.min_chan_समय = 0,
		.max_chan_समय = 10,
	पूर्ण पूर्ण;
	काष्ठा wsm_scan scan = अणु
		.type = WSM_SCAN_TYPE_FOREGROUND,
		.num_probes = 1,
		.probe_delay = 0,
		.num_channels = 1,
		.ssids = ssids,
		.ch = ch,
	पूर्ण;
	u8 *ies;
	माप_प्रकार ies_len;
	पूर्णांक ret;

	wiphy_dbg(priv->hw->wiphy, "[SCAN] Direct probe work.\n");

	mutex_lock(&priv->conf_mutex);
	अगर (करोwn_trylock(&priv->scan.lock)) अणु
		/* Scan is alपढ़ोy in progress. Requeue self. */
		schedule();
		queue_delayed_work(priv->workqueue, &priv->scan.probe_work,
				   msecs_to_jअगरfies(100));
		mutex_unlock(&priv->conf_mutex);
		वापस;
	पूर्ण

	/* Make sure we still have a pending probe req */
	अगर (cw1200_queue_get_skb(queue,	priv->pending_frame_id,
				 &frame.skb, &txpriv)) अणु
		up(&priv->scan.lock);
		mutex_unlock(&priv->conf_mutex);
		wsm_unlock_tx(priv);
		वापस;
	पूर्ण
	wsm = (काष्ठा wsm_tx *)frame.skb->data;
	scan.max_tx_rate = wsm->max_tx_rate;
	scan.band = (priv->channel->band == NL80211_BAND_5GHZ) ?
		WSM_PHY_BAND_5G : WSM_PHY_BAND_2_4G;
	अगर (priv->join_status == CW1200_JOIN_STATUS_STA ||
	    priv->join_status == CW1200_JOIN_STATUS_IBSS) अणु
		scan.type = WSM_SCAN_TYPE_BACKGROUND;
		scan.flags = WSM_SCAN_FLAG_FORCE_BACKGROUND;
	पूर्ण
	ch[0].number = priv->channel->hw_value;

	skb_pull(frame.skb, txpriv->offset);

	ies = &frame.skb->data[माप(काष्ठा ieee80211_hdr_3addr)];
	ies_len = frame.skb->len - माप(काष्ठा ieee80211_hdr_3addr);

	अगर (ies_len) अणु
		u8 *ssidie =
			(u8 *)cfg80211_find_ie(WLAN_EID_SSID, ies, ies_len);
		अगर (ssidie && ssidie[1] && ssidie[1] <= माप(ssids[0].ssid)) अणु
			u8 *nextie = &ssidie[2 + ssidie[1]];
			/* Remove SSID from the IE list. It has to be provided
			 * as a separate argument in cw1200_scan_start call
			 */

			/* Store SSID localy */
			ssids[0].length = ssidie[1];
			स_नकल(ssids[0].ssid, &ssidie[2], ssids[0].length);
			scan.num_ssids = 1;

			/* Remove SSID from IE list */
			ssidie[1] = 0;
			स_हटाओ(&ssidie[2], nextie, &ies[ies_len] - nextie);
			skb_trim(frame.skb, frame.skb->len - ssids[0].length);
		पूर्ण
	पूर्ण

	/* FW bug: driver has to restart p2p-dev mode after scan */
	अगर (priv->join_status == CW1200_JOIN_STATUS_MONITOR)
		cw1200_disable_listening(priv);
	ret = wsm_set_ढाँचा_frame(priv, &frame);
	priv->scan.direct_probe = 1;
	अगर (!ret) अणु
		wsm_flush_tx(priv);
		ret = cw1200_scan_start(priv, &scan);
	पूर्ण
	mutex_unlock(&priv->conf_mutex);

	skb_push(frame.skb, txpriv->offset);
	अगर (!ret)
		IEEE80211_SKB_CB(frame.skb)->flags |= IEEE80211_TX_STAT_ACK;
	BUG_ON(cw1200_queue_हटाओ(queue, priv->pending_frame_id));

	अगर (ret) अणु
		priv->scan.direct_probe = 0;
		up(&priv->scan.lock);
		wsm_unlock_tx(priv);
	पूर्ण

	वापस;
पूर्ण
