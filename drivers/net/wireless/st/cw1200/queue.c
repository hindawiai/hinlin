<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * O(1) TX queue with built-in allocator क्रम ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#समावेश <net/mac80211.h>
#समावेश <linux/sched.h>
#समावेश "queue.h"
#समावेश "cw1200.h"
#समावेश "debug.h"

/* निजी */ काष्ठा cw1200_queue_item
अणु
	काष्ठा list_head	head;
	काष्ठा sk_buff		*skb;
	u32			packet_id;
	अचिन्हित दीर्घ		queue_बारtamp;
	अचिन्हित दीर्घ		xmit_बारtamp;
	काष्ठा cw1200_txpriv	txpriv;
	u8			generation;
पूर्ण;

अटल अंतरभूत व्योम __cw1200_queue_lock(काष्ठा cw1200_queue *queue)
अणु
	काष्ठा cw1200_queue_stats *stats = queue->stats;
	अगर (queue->tx_locked_cnt++ == 0) अणु
		pr_debug("[TX] Queue %d is locked.\n",
			 queue->queue_id);
		ieee80211_stop_queue(stats->priv->hw, queue->queue_id);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __cw1200_queue_unlock(काष्ठा cw1200_queue *queue)
अणु
	काष्ठा cw1200_queue_stats *stats = queue->stats;
	BUG_ON(!queue->tx_locked_cnt);
	अगर (--queue->tx_locked_cnt == 0) अणु
		pr_debug("[TX] Queue %d is unlocked.\n",
			 queue->queue_id);
		ieee80211_wake_queue(stats->priv->hw, queue->queue_id);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cw1200_queue_parse_id(u32 packet_id, u8 *queue_generation,
					 u8 *queue_id, u8 *item_generation,
					 u8 *item_id)
अणु
	*item_id		= (packet_id >>  0) & 0xFF;
	*item_generation	= (packet_id >>  8) & 0xFF;
	*queue_id		= (packet_id >> 16) & 0xFF;
	*queue_generation	= (packet_id >> 24) & 0xFF;
पूर्ण

अटल अंतरभूत u32 cw1200_queue_mk_packet_id(u8 queue_generation, u8 queue_id,
					    u8 item_generation, u8 item_id)
अणु
	वापस ((u32)item_id << 0) |
		((u32)item_generation << 8) |
		((u32)queue_id << 16) |
		((u32)queue_generation << 24);
पूर्ण

अटल व्योम cw1200_queue_post_gc(काष्ठा cw1200_queue_stats *stats,
				 काष्ठा list_head *gc_list)
अणु
	काष्ठा cw1200_queue_item *item, *पंचांगp;

	list_क्रम_each_entry_safe(item, पंचांगp, gc_list, head) अणु
		list_del(&item->head);
		stats->skb_dtor(stats->priv, item->skb, &item->txpriv);
		kमुक्त(item);
	पूर्ण
पूर्ण

अटल व्योम cw1200_queue_रेजिस्टर_post_gc(काष्ठा list_head *gc_list,
					  काष्ठा cw1200_queue_item *item)
अणु
	काष्ठा cw1200_queue_item *gc_item;
	gc_item = kmemdup(item, माप(काष्ठा cw1200_queue_item),
			GFP_ATOMIC);
	BUG_ON(!gc_item);
	list_add_tail(&gc_item->head, gc_list);
पूर्ण

अटल व्योम __cw1200_queue_gc(काष्ठा cw1200_queue *queue,
			      काष्ठा list_head *head,
			      bool unlock)
अणु
	काष्ठा cw1200_queue_stats *stats = queue->stats;
	काष्ठा cw1200_queue_item *item = शून्य, *पंचांगp;
	bool wakeup_stats = false;

	list_क्रम_each_entry_safe(item, पंचांगp, &queue->queue, head) अणु
		अगर (jअगरfies - item->queue_बारtamp < queue->ttl)
			अवरोध;
		--queue->num_queued;
		--queue->link_map_cache[item->txpriv.link_id];
		spin_lock_bh(&stats->lock);
		--stats->num_queued;
		अगर (!--stats->link_map_cache[item->txpriv.link_id])
			wakeup_stats = true;
		spin_unlock_bh(&stats->lock);
		cw1200_debug_tx_ttl(stats->priv);
		cw1200_queue_रेजिस्टर_post_gc(head, item);
		item->skb = शून्य;
		list_move_tail(&item->head, &queue->मुक्त_pool);
	पूर्ण

	अगर (wakeup_stats)
		wake_up(&stats->रुको_link_id_empty);

	अगर (queue->overfull) अणु
		अगर (queue->num_queued <= (queue->capacity >> 1)) अणु
			queue->overfull = false;
			अगर (unlock)
				__cw1200_queue_unlock(queue);
		पूर्ण अन्यथा अगर (item) अणु
			अचिन्हित दीर्घ पंचांगo = item->queue_बारtamp + queue->ttl;
			mod_समयr(&queue->gc, पंचांगo);
			cw1200_pm_stay_awake(&stats->priv->pm_state,
					     पंचांगo - jअगरfies);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cw1200_queue_gc(काष्ठा समयr_list *t)
अणु
	LIST_HEAD(list);
	काष्ठा cw1200_queue *queue =
		from_समयr(queue, t, gc);

	spin_lock_bh(&queue->lock);
	__cw1200_queue_gc(queue, &list, true);
	spin_unlock_bh(&queue->lock);
	cw1200_queue_post_gc(queue->stats, &list);
पूर्ण

पूर्णांक cw1200_queue_stats_init(काष्ठा cw1200_queue_stats *stats,
			    माप_प्रकार map_capacity,
			    cw1200_queue_skb_dtor_t skb_dtor,
			    काष्ठा cw1200_common *priv)
अणु
	स_रखो(stats, 0, माप(*stats));
	stats->map_capacity = map_capacity;
	stats->skb_dtor = skb_dtor;
	stats->priv = priv;
	spin_lock_init(&stats->lock);
	init_रुकोqueue_head(&stats->रुको_link_id_empty);

	stats->link_map_cache = kसुस्मृति(map_capacity, माप(पूर्णांक),
					GFP_KERNEL);
	अगर (!stats->link_map_cache)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक cw1200_queue_init(काष्ठा cw1200_queue *queue,
		      काष्ठा cw1200_queue_stats *stats,
		      u8 queue_id,
		      माप_प्रकार capacity,
		      अचिन्हित दीर्घ ttl)
अणु
	माप_प्रकार i;

	स_रखो(queue, 0, माप(*queue));
	queue->stats = stats;
	queue->capacity = capacity;
	queue->queue_id = queue_id;
	queue->ttl = ttl;
	INIT_LIST_HEAD(&queue->queue);
	INIT_LIST_HEAD(&queue->pending);
	INIT_LIST_HEAD(&queue->मुक्त_pool);
	spin_lock_init(&queue->lock);
	समयr_setup(&queue->gc, cw1200_queue_gc, 0);

	queue->pool = kसुस्मृति(capacity, माप(काष्ठा cw1200_queue_item),
			      GFP_KERNEL);
	अगर (!queue->pool)
		वापस -ENOMEM;

	queue->link_map_cache = kसुस्मृति(stats->map_capacity, माप(पूर्णांक),
					GFP_KERNEL);
	अगर (!queue->link_map_cache) अणु
		kमुक्त(queue->pool);
		queue->pool = शून्य;
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < capacity; ++i)
		list_add_tail(&queue->pool[i].head, &queue->मुक्त_pool);

	वापस 0;
पूर्ण

पूर्णांक cw1200_queue_clear(काष्ठा cw1200_queue *queue)
अणु
	पूर्णांक i;
	LIST_HEAD(gc_list);
	काष्ठा cw1200_queue_stats *stats = queue->stats;
	काष्ठा cw1200_queue_item *item, *पंचांगp;

	spin_lock_bh(&queue->lock);
	queue->generation++;
	list_splice_tail_init(&queue->queue, &queue->pending);
	list_क्रम_each_entry_safe(item, पंचांगp, &queue->pending, head) अणु
		WARN_ON(!item->skb);
		cw1200_queue_रेजिस्टर_post_gc(&gc_list, item);
		item->skb = शून्य;
		list_move_tail(&item->head, &queue->मुक्त_pool);
	पूर्ण
	queue->num_queued = 0;
	queue->num_pending = 0;

	spin_lock_bh(&stats->lock);
	क्रम (i = 0; i < stats->map_capacity; ++i) अणु
		stats->num_queued -= queue->link_map_cache[i];
		stats->link_map_cache[i] -= queue->link_map_cache[i];
		queue->link_map_cache[i] = 0;
	पूर्ण
	spin_unlock_bh(&stats->lock);
	अगर (queue->overfull) अणु
		queue->overfull = false;
		__cw1200_queue_unlock(queue);
	पूर्ण
	spin_unlock_bh(&queue->lock);
	wake_up(&stats->रुको_link_id_empty);
	cw1200_queue_post_gc(stats, &gc_list);
	वापस 0;
पूर्ण

व्योम cw1200_queue_stats_deinit(काष्ठा cw1200_queue_stats *stats)
अणु
	kमुक्त(stats->link_map_cache);
	stats->link_map_cache = शून्य;
पूर्ण

व्योम cw1200_queue_deinit(काष्ठा cw1200_queue *queue)
अणु
	cw1200_queue_clear(queue);
	del_समयr_sync(&queue->gc);
	INIT_LIST_HEAD(&queue->मुक्त_pool);
	kमुक्त(queue->pool);
	kमुक्त(queue->link_map_cache);
	queue->pool = शून्य;
	queue->link_map_cache = शून्य;
	queue->capacity = 0;
पूर्ण

माप_प्रकार cw1200_queue_get_num_queued(काष्ठा cw1200_queue *queue,
				   u32 link_id_map)
अणु
	माप_प्रकार ret;
	पूर्णांक i, bit;
	माप_प्रकार map_capacity = queue->stats->map_capacity;

	अगर (!link_id_map)
		वापस 0;

	spin_lock_bh(&queue->lock);
	अगर (link_id_map == (u32)-1) अणु
		ret = queue->num_queued - queue->num_pending;
	पूर्ण अन्यथा अणु
		ret = 0;
		क्रम (i = 0, bit = 1; i < map_capacity; ++i, bit <<= 1) अणु
			अगर (link_id_map & bit)
				ret += queue->link_map_cache[i];
		पूर्ण
	पूर्ण
	spin_unlock_bh(&queue->lock);
	वापस ret;
पूर्ण

पूर्णांक cw1200_queue_put(काष्ठा cw1200_queue *queue,
		     काष्ठा sk_buff *skb,
		     काष्ठा cw1200_txpriv *txpriv)
अणु
	पूर्णांक ret = 0;
	काष्ठा cw1200_queue_stats *stats = queue->stats;

	अगर (txpriv->link_id >= queue->stats->map_capacity)
		वापस -EINVAL;

	spin_lock_bh(&queue->lock);
	अगर (!WARN_ON(list_empty(&queue->मुक्त_pool))) अणु
		काष्ठा cw1200_queue_item *item = list_first_entry(
			&queue->मुक्त_pool, काष्ठा cw1200_queue_item, head);
		BUG_ON(item->skb);

		list_move_tail(&item->head, &queue->queue);
		item->skb = skb;
		item->txpriv = *txpriv;
		item->generation = 0;
		item->packet_id = cw1200_queue_mk_packet_id(queue->generation,
							    queue->queue_id,
							    item->generation,
							    item - queue->pool);
		item->queue_बारtamp = jअगरfies;

		++queue->num_queued;
		++queue->link_map_cache[txpriv->link_id];

		spin_lock_bh(&stats->lock);
		++stats->num_queued;
		++stats->link_map_cache[txpriv->link_id];
		spin_unlock_bh(&stats->lock);

		/* TX may happen in parallel someबार.
		 * Leave extra queue slots so we करोn't overflow.
		 */
		अगर (queue->overfull == false &&
		    queue->num_queued >=
		    (queue->capacity - (num_present_cpus() - 1))) अणु
			queue->overfull = true;
			__cw1200_queue_lock(queue);
			mod_समयr(&queue->gc, jअगरfies);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -ENOENT;
	पूर्ण
	spin_unlock_bh(&queue->lock);
	वापस ret;
पूर्ण

पूर्णांक cw1200_queue_get(काष्ठा cw1200_queue *queue,
		     u32 link_id_map,
		     काष्ठा wsm_tx **tx,
		     काष्ठा ieee80211_tx_info **tx_info,
		     स्थिर काष्ठा cw1200_txpriv **txpriv)
अणु
	पूर्णांक ret = -ENOENT;
	काष्ठा cw1200_queue_item *item;
	काष्ठा cw1200_queue_stats *stats = queue->stats;
	bool wakeup_stats = false;

	spin_lock_bh(&queue->lock);
	list_क्रम_each_entry(item, &queue->queue, head) अणु
		अगर (link_id_map & BIT(item->txpriv.link_id)) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!WARN_ON(ret)) अणु
		*tx = (काष्ठा wsm_tx *)item->skb->data;
		*tx_info = IEEE80211_SKB_CB(item->skb);
		*txpriv = &item->txpriv;
		(*tx)->packet_id = item->packet_id;
		list_move_tail(&item->head, &queue->pending);
		++queue->num_pending;
		--queue->link_map_cache[item->txpriv.link_id];
		item->xmit_बारtamp = jअगरfies;

		spin_lock_bh(&stats->lock);
		--stats->num_queued;
		अगर (!--stats->link_map_cache[item->txpriv.link_id])
			wakeup_stats = true;
		spin_unlock_bh(&stats->lock);
	पूर्ण
	spin_unlock_bh(&queue->lock);
	अगर (wakeup_stats)
		wake_up(&stats->रुको_link_id_empty);
	वापस ret;
पूर्ण

पूर्णांक cw1200_queue_requeue(काष्ठा cw1200_queue *queue, u32 packet_id)
अणु
	पूर्णांक ret = 0;
	u8 queue_generation, queue_id, item_generation, item_id;
	काष्ठा cw1200_queue_item *item;
	काष्ठा cw1200_queue_stats *stats = queue->stats;

	cw1200_queue_parse_id(packet_id, &queue_generation, &queue_id,
			      &item_generation, &item_id);

	item = &queue->pool[item_id];

	spin_lock_bh(&queue->lock);
	BUG_ON(queue_id != queue->queue_id);
	अगर (queue_generation != queue->generation) अणु
		ret = -ENOENT;
	पूर्ण अन्यथा अगर (item_id >= (अचिन्हित) queue->capacity) अणु
		WARN_ON(1);
		ret = -EINVAL;
	पूर्ण अन्यथा अगर (item->generation != item_generation) अणु
		WARN_ON(1);
		ret = -ENOENT;
	पूर्ण अन्यथा अणु
		--queue->num_pending;
		++queue->link_map_cache[item->txpriv.link_id];

		spin_lock_bh(&stats->lock);
		++stats->num_queued;
		++stats->link_map_cache[item->txpriv.link_id];
		spin_unlock_bh(&stats->lock);

		item->generation = ++item_generation;
		item->packet_id = cw1200_queue_mk_packet_id(queue_generation,
							    queue_id,
							    item_generation,
							    item_id);
		list_move(&item->head, &queue->queue);
	पूर्ण
	spin_unlock_bh(&queue->lock);
	वापस ret;
पूर्ण

पूर्णांक cw1200_queue_requeue_all(काष्ठा cw1200_queue *queue)
अणु
	काष्ठा cw1200_queue_item *item, *पंचांगp;
	काष्ठा cw1200_queue_stats *stats = queue->stats;
	spin_lock_bh(&queue->lock);

	list_क्रम_each_entry_safe_reverse(item, पंचांगp, &queue->pending, head) अणु
		--queue->num_pending;
		++queue->link_map_cache[item->txpriv.link_id];

		spin_lock_bh(&stats->lock);
		++stats->num_queued;
		++stats->link_map_cache[item->txpriv.link_id];
		spin_unlock_bh(&stats->lock);

		++item->generation;
		item->packet_id = cw1200_queue_mk_packet_id(queue->generation,
							    queue->queue_id,
							    item->generation,
							    item - queue->pool);
		list_move(&item->head, &queue->queue);
	पूर्ण
	spin_unlock_bh(&queue->lock);

	वापस 0;
पूर्ण

पूर्णांक cw1200_queue_हटाओ(काष्ठा cw1200_queue *queue, u32 packet_id)
अणु
	पूर्णांक ret = 0;
	u8 queue_generation, queue_id, item_generation, item_id;
	काष्ठा cw1200_queue_item *item;
	काष्ठा cw1200_queue_stats *stats = queue->stats;
	काष्ठा sk_buff *gc_skb = शून्य;
	काष्ठा cw1200_txpriv gc_txpriv;

	cw1200_queue_parse_id(packet_id, &queue_generation, &queue_id,
			      &item_generation, &item_id);

	item = &queue->pool[item_id];

	spin_lock_bh(&queue->lock);
	BUG_ON(queue_id != queue->queue_id);
	अगर (queue_generation != queue->generation) अणु
		ret = -ENOENT;
	पूर्ण अन्यथा अगर (item_id >= (अचिन्हित) queue->capacity) अणु
		WARN_ON(1);
		ret = -EINVAL;
	पूर्ण अन्यथा अगर (item->generation != item_generation) अणु
		WARN_ON(1);
		ret = -ENOENT;
	पूर्ण अन्यथा अणु
		gc_txpriv = item->txpriv;
		gc_skb = item->skb;
		item->skb = शून्य;
		--queue->num_pending;
		--queue->num_queued;
		++queue->num_sent;
		++item->generation;
		/* Do not use list_move_tail here, but list_move:
		 * try to utilize cache row.
		 */
		list_move(&item->head, &queue->मुक्त_pool);

		अगर (queue->overfull &&
		    (queue->num_queued <= (queue->capacity >> 1))) अणु
			queue->overfull = false;
			__cw1200_queue_unlock(queue);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&queue->lock);

	अगर (gc_skb)
		stats->skb_dtor(stats->priv, gc_skb, &gc_txpriv);

	वापस ret;
पूर्ण

पूर्णांक cw1200_queue_get_skb(काष्ठा cw1200_queue *queue, u32 packet_id,
			 काष्ठा sk_buff **skb,
			 स्थिर काष्ठा cw1200_txpriv **txpriv)
अणु
	पूर्णांक ret = 0;
	u8 queue_generation, queue_id, item_generation, item_id;
	काष्ठा cw1200_queue_item *item;
	cw1200_queue_parse_id(packet_id, &queue_generation, &queue_id,
			      &item_generation, &item_id);

	item = &queue->pool[item_id];

	spin_lock_bh(&queue->lock);
	BUG_ON(queue_id != queue->queue_id);
	अगर (queue_generation != queue->generation) अणु
		ret = -ENOENT;
	पूर्ण अन्यथा अगर (item_id >= (अचिन्हित) queue->capacity) अणु
		WARN_ON(1);
		ret = -EINVAL;
	पूर्ण अन्यथा अगर (item->generation != item_generation) अणु
		WARN_ON(1);
		ret = -ENOENT;
	पूर्ण अन्यथा अणु
		*skb = item->skb;
		*txpriv = &item->txpriv;
	पूर्ण
	spin_unlock_bh(&queue->lock);
	वापस ret;
पूर्ण

व्योम cw1200_queue_lock(काष्ठा cw1200_queue *queue)
अणु
	spin_lock_bh(&queue->lock);
	__cw1200_queue_lock(queue);
	spin_unlock_bh(&queue->lock);
पूर्ण

व्योम cw1200_queue_unlock(काष्ठा cw1200_queue *queue)
अणु
	spin_lock_bh(&queue->lock);
	__cw1200_queue_unlock(queue);
	spin_unlock_bh(&queue->lock);
पूर्ण

bool cw1200_queue_get_xmit_बारtamp(काष्ठा cw1200_queue *queue,
				     अचिन्हित दीर्घ *बारtamp,
				     u32 pending_frame_id)
अणु
	काष्ठा cw1200_queue_item *item;
	bool ret;

	spin_lock_bh(&queue->lock);
	ret = !list_empty(&queue->pending);
	अगर (ret) अणु
		list_क्रम_each_entry(item, &queue->pending, head) अणु
			अगर (item->packet_id != pending_frame_id)
				अगर (समय_beक्रमe(item->xmit_बारtamp,
						*बारtamp))
					*बारtamp = item->xmit_बारtamp;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&queue->lock);
	वापस ret;
पूर्ण

bool cw1200_queue_stats_is_empty(काष्ठा cw1200_queue_stats *stats,
				 u32 link_id_map)
अणु
	bool empty = true;

	spin_lock_bh(&stats->lock);
	अगर (link_id_map == (u32)-1) अणु
		empty = stats->num_queued == 0;
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		क्रम (i = 0; i < stats->map_capacity; ++i) अणु
			अगर (link_id_map & BIT(i)) अणु
				अगर (stats->link_map_cache[i]) अणु
					empty = false;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&stats->lock);

	वापस empty;
पूर्ण
