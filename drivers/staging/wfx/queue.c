<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * O(1) TX queue with built-in allocator.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/sched.h>
#समावेश <net/mac80211.h>

#समावेश "queue.h"
#समावेश "wfx.h"
#समावेश "sta.h"
#समावेश "data_tx.h"
#समावेश "traces.h"

व्योम wfx_tx_lock(काष्ठा wfx_dev *wdev)
अणु
	atomic_inc(&wdev->tx_lock);
पूर्ण

व्योम wfx_tx_unlock(काष्ठा wfx_dev *wdev)
अणु
	पूर्णांक tx_lock = atomic_dec_वापस(&wdev->tx_lock);

	WARN(tx_lock < 0, "inconsistent tx_lock value");
	अगर (!tx_lock)
		wfx_bh_request_tx(wdev);
पूर्ण

व्योम wfx_tx_flush(काष्ठा wfx_dev *wdev)
अणु
	पूर्णांक ret;

	// Do not रुको क्रम any reply अगर chip is frozen
	अगर (wdev->chip_frozen)
		वापस;

	wfx_tx_lock(wdev);
	mutex_lock(&wdev->hअगर_cmd.lock);
	ret = रुको_event_समयout(wdev->hअगर.tx_buffers_empty,
				 !wdev->hअगर.tx_buffers_used,
				 msecs_to_jअगरfies(3000));
	अगर (!ret) अणु
		dev_warn(wdev->dev, "cannot flush tx buffers (%d still busy)\n",
			 wdev->hअगर.tx_buffers_used);
		wfx_pending_dump_old_frames(wdev, 3000);
		// FIXME: drop pending frames here
		wdev->chip_frozen = true;
	पूर्ण
	mutex_unlock(&wdev->hअगर_cmd.lock);
	wfx_tx_unlock(wdev);
पूर्ण

व्योम wfx_tx_lock_flush(काष्ठा wfx_dev *wdev)
अणु
	wfx_tx_lock(wdev);
	wfx_tx_flush(wdev);
पूर्ण

व्योम wfx_tx_queues_init(काष्ठा wfx_vअगर *wvअगर)
अणु
	// The device is in अक्षरge to respect the details of the QoS parameters.
	// The driver just ensure that it roughtly respect the priorities to
	// aव्योम any लघुage.
	स्थिर पूर्णांक priorities[IEEE80211_NUM_ACS] = अणु 1, 2, 64, 128 पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; ++i) अणु
		skb_queue_head_init(&wvअगर->tx_queue[i].normal);
		skb_queue_head_init(&wvअगर->tx_queue[i].cab);
		wvअगर->tx_queue[i].priority = priorities[i];
	पूर्ण
पूर्ण

व्योम wfx_tx_queues_check_empty(काष्ठा wfx_vअगर *wvअगर)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; ++i) अणु
		WARN_ON(atomic_पढ़ो(&wvअगर->tx_queue[i].pending_frames));
		WARN_ON(!skb_queue_empty_lockless(&wvअगर->tx_queue[i].normal));
		WARN_ON(!skb_queue_empty_lockless(&wvअगर->tx_queue[i].cab));
	पूर्ण
पूर्ण

bool wfx_tx_queue_empty(काष्ठा wfx_vअगर *wvअगर, काष्ठा wfx_queue *queue)
अणु
	वापस skb_queue_empty(&queue->normal) && skb_queue_empty(&queue->cab);
पूर्ण

अटल व्योम __wfx_tx_queue_drop(काष्ठा wfx_vअगर *wvअगर,
				काष्ठा sk_buff_head *skb_queue,
				काष्ठा sk_buff_head *dropped)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;

	spin_lock_bh(&skb_queue->lock);
	skb_queue_walk_safe(skb_queue, skb, पंचांगp) अणु
		__skb_unlink(skb, skb_queue);
		skb_queue_head(dropped, skb);
	पूर्ण
	spin_unlock_bh(&skb_queue->lock);
पूर्ण

व्योम wfx_tx_queue_drop(काष्ठा wfx_vअगर *wvअगर, काष्ठा wfx_queue *queue,
		       काष्ठा sk_buff_head *dropped)
अणु
	__wfx_tx_queue_drop(wvअगर, &queue->cab, dropped);
	__wfx_tx_queue_drop(wvअगर, &queue->normal, dropped);
	wake_up(&wvअगर->wdev->tx_dequeue);
पूर्ण

व्योम wfx_tx_queues_put(काष्ठा wfx_vअगर *wvअगर, काष्ठा sk_buff *skb)
अणु
	काष्ठा wfx_queue *queue = &wvअगर->tx_queue[skb_get_queue_mapping(skb)];
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);

	अगर (tx_info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM)
		skb_queue_tail(&queue->cab, skb);
	अन्यथा
		skb_queue_tail(&queue->normal, skb);
पूर्ण

व्योम wfx_pending_drop(काष्ठा wfx_dev *wdev, काष्ठा sk_buff_head *dropped)
अणु
	काष्ठा wfx_queue *queue;
	काष्ठा wfx_vअगर *wvअगर;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा sk_buff *skb;

	WARN(!wdev->chip_frozen, "%s should only be used to recover a frozen device",
	     __func__);
	जबतक ((skb = skb_dequeue(&wdev->tx_pending)) != शून्य) अणु
		hअगर = (काष्ठा hअगर_msg *)skb->data;
		wvअगर = wdev_to_wvअगर(wdev, hअगर->पूर्णांकerface);
		अगर (wvअगर) अणु
			queue = &wvअगर->tx_queue[skb_get_queue_mapping(skb)];
			WARN_ON(skb_get_queue_mapping(skb) > 3);
			WARN_ON(!atomic_पढ़ो(&queue->pending_frames));
			atomic_dec(&queue->pending_frames);
		पूर्ण
		skb_queue_head(dropped, skb);
	पूर्ण
पूर्ण

काष्ठा sk_buff *wfx_pending_get(काष्ठा wfx_dev *wdev, u32 packet_id)
अणु
	काष्ठा wfx_queue *queue;
	काष्ठा hअगर_req_tx *req;
	काष्ठा wfx_vअगर *wvअगर;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा sk_buff *skb;

	spin_lock_bh(&wdev->tx_pending.lock);
	skb_queue_walk(&wdev->tx_pending, skb) अणु
		hअगर = (काष्ठा hअगर_msg *)skb->data;
		req = (काष्ठा hअगर_req_tx *)hअगर->body;
		अगर (req->packet_id != packet_id)
			जारी;
		spin_unlock_bh(&wdev->tx_pending.lock);
		wvअगर = wdev_to_wvअगर(wdev, hअगर->पूर्णांकerface);
		अगर (wvअगर) अणु
			queue = &wvअगर->tx_queue[skb_get_queue_mapping(skb)];
			WARN_ON(skb_get_queue_mapping(skb) > 3);
			WARN_ON(!atomic_पढ़ो(&queue->pending_frames));
			atomic_dec(&queue->pending_frames);
		पूर्ण
		skb_unlink(skb, &wdev->tx_pending);
		वापस skb;
	पूर्ण
	spin_unlock_bh(&wdev->tx_pending.lock);
	WARN(1, "cannot find packet in pending queue");
	वापस शून्य;
पूर्ण

व्योम wfx_pending_dump_old_frames(काष्ठा wfx_dev *wdev, अचिन्हित पूर्णांक limit_ms)
अणु
	kसमय_प्रकार now = kसमय_get();
	काष्ठा wfx_tx_priv *tx_priv;
	काष्ठा hअगर_req_tx *req;
	काष्ठा sk_buff *skb;
	bool first = true;

	spin_lock_bh(&wdev->tx_pending.lock);
	skb_queue_walk(&wdev->tx_pending, skb) अणु
		tx_priv = wfx_skb_tx_priv(skb);
		req = wfx_skb_txreq(skb);
		अगर (kसमय_after(now, kसमय_add_ms(tx_priv->xmit_बारtamp,
						  limit_ms))) अणु
			अगर (first) अणु
				dev_info(wdev->dev, "frames stuck in firmware since %dms or more:\n",
					 limit_ms);
				first = false;
			पूर्ण
			dev_info(wdev->dev, "   id %08x sent %lldms ago\n",
				 req->packet_id,
				 kसमय_ms_delta(now, tx_priv->xmit_बारtamp));
		पूर्ण
	पूर्ण
	spin_unlock_bh(&wdev->tx_pending.lock);
पूर्ण

अचिन्हित पूर्णांक wfx_pending_get_pkt_us_delay(काष्ठा wfx_dev *wdev,
					  काष्ठा sk_buff *skb)
अणु
	kसमय_प्रकार now = kसमय_get();
	काष्ठा wfx_tx_priv *tx_priv = wfx_skb_tx_priv(skb);

	वापस kसमय_us_delta(now, tx_priv->xmit_बारtamp);
पूर्ण

bool wfx_tx_queues_has_cab(काष्ठा wfx_vअगर *wvअगर)
अणु
	पूर्णांक i;

	अगर (wvअगर->vअगर->type != NL80211_IFTYPE_AP)
		वापस false;
	क्रम (i = 0; i < IEEE80211_NUM_ACS; ++i)
		// Note: since only AP can have mcast frames in queue and only
		// one vअगर can be AP, all queued frames has same पूर्णांकerface id
		अगर (!skb_queue_empty_lockless(&wvअगर->tx_queue[i].cab))
			वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक wfx_tx_queue_get_weight(काष्ठा wfx_queue *queue)
अणु
	वापस atomic_पढ़ो(&queue->pending_frames) * queue->priority;
पूर्ण

अटल काष्ठा sk_buff *wfx_tx_queues_get_skb(काष्ठा wfx_dev *wdev)
अणु
	काष्ठा wfx_queue *queues[IEEE80211_NUM_ACS * ARRAY_SIZE(wdev->vअगर)];
	पूर्णांक i, j, num_queues = 0;
	काष्ठा wfx_vअगर *wvअगर;
	काष्ठा hअगर_msg *hअगर;
	काष्ठा sk_buff *skb;

	// sort the queues
	wvअगर = शून्य;
	जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य) अणु
		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
			WARN_ON(num_queues >= ARRAY_SIZE(queues));
			queues[num_queues] = &wvअगर->tx_queue[i];
			क्रम (j = num_queues; j > 0; j--)
				अगर (wfx_tx_queue_get_weight(queues[j]) <
				    wfx_tx_queue_get_weight(queues[j - 1]))
					swap(queues[j - 1], queues[j]);
			num_queues++;
		पूर्ण
	पूर्ण

	wvअगर = शून्य;
	जबतक ((wvअगर = wvअगर_iterate(wdev, wvअगर)) != शून्य) अणु
		अगर (!wvअगर->after_dtim_tx_allowed)
			जारी;
		क्रम (i = 0; i < num_queues; i++) अणु
			skb = skb_dequeue(&queues[i]->cab);
			अगर (!skb)
				जारी;
			// Note: since only AP can have mcast frames in queue
			// and only one vअगर can be AP, all queued frames has
			// same पूर्णांकerface id
			hअगर = (काष्ठा hअगर_msg *)skb->data;
			WARN_ON(hअगर->पूर्णांकerface != wvअगर->id);
			WARN_ON(queues[i] !=
				&wvअगर->tx_queue[skb_get_queue_mapping(skb)]);
			atomic_inc(&queues[i]->pending_frames);
			trace_queues_stats(wdev, queues[i]);
			वापस skb;
		पूर्ण
		// No more multicast to sent
		wvअगर->after_dtim_tx_allowed = false;
		schedule_work(&wvअगर->update_tim_work);
	पूर्ण

	क्रम (i = 0; i < num_queues; i++) अणु
		skb = skb_dequeue(&queues[i]->normal);
		अगर (skb) अणु
			atomic_inc(&queues[i]->pending_frames);
			trace_queues_stats(wdev, queues[i]);
			वापस skb;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा hअगर_msg *wfx_tx_queues_get(काष्ठा wfx_dev *wdev)
अणु
	काष्ठा wfx_tx_priv *tx_priv;
	काष्ठा sk_buff *skb;

	अगर (atomic_पढ़ो(&wdev->tx_lock))
		वापस शून्य;
	skb = wfx_tx_queues_get_skb(wdev);
	अगर (!skb)
		वापस शून्य;
	skb_queue_tail(&wdev->tx_pending, skb);
	wake_up(&wdev->tx_dequeue);
	tx_priv = wfx_skb_tx_priv(skb);
	tx_priv->xmit_बारtamp = kसमय_get();
	वापस (काष्ठा hअगर_msg *)skb->data;
पूर्ण
