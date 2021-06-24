<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * O(1) TX queue with built-in allocator क्रम ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#अगर_अघोषित CW1200_QUEUE_H_INCLUDED
#घोषणा CW1200_QUEUE_H_INCLUDED

/* निजी */ काष्ठा cw1200_queue_item;

/* बाह्य */ काष्ठा sk_buff;
/* बाह्य */ काष्ठा wsm_tx;
/* बाह्य */ काष्ठा cw1200_common;
/* बाह्य */ काष्ठा ieee80211_tx_queue_stats;
/* बाह्य */ काष्ठा cw1200_txpriv;

/* क्रमward */ काष्ठा cw1200_queue_stats;

प्रकार व्योम (*cw1200_queue_skb_dtor_t)(काष्ठा cw1200_common *priv,
					काष्ठा sk_buff *skb,
					स्थिर काष्ठा cw1200_txpriv *txpriv);

काष्ठा cw1200_queue अणु
	काष्ठा cw1200_queue_stats *stats;
	माप_प्रकार			capacity;
	माप_प्रकार			num_queued;
	माप_प्रकार			num_pending;
	माप_प्रकार			num_sent;
	काष्ठा cw1200_queue_item *pool;
	काष्ठा list_head	queue;
	काष्ठा list_head	मुक्त_pool;
	काष्ठा list_head	pending;
	पूर्णांक			tx_locked_cnt;
	पूर्णांक			*link_map_cache;
	bool			overfull;
	spinlock_t		lock; /* Protect queue entry */
	u8			queue_id;
	u8			generation;
	काष्ठा समयr_list	gc;
	अचिन्हित दीर्घ		ttl;
पूर्ण;

काष्ठा cw1200_queue_stats अणु
	spinlock_t		lock; /* Protect stats entry */
	पूर्णांक			*link_map_cache;
	पूर्णांक			num_queued;
	माप_प्रकार			map_capacity;
	रुको_queue_head_t	रुको_link_id_empty;
	cw1200_queue_skb_dtor_t	skb_dtor;
	काष्ठा cw1200_common	*priv;
पूर्ण;

काष्ठा cw1200_txpriv अणु
	u8 link_id;
	u8 raw_link_id;
	u8 tid;
	u8 rate_id;
	u8 offset;
पूर्ण;

पूर्णांक cw1200_queue_stats_init(काष्ठा cw1200_queue_stats *stats,
			    माप_प्रकार map_capacity,
			    cw1200_queue_skb_dtor_t skb_dtor,
			    काष्ठा cw1200_common *priv);
पूर्णांक cw1200_queue_init(काष्ठा cw1200_queue *queue,
		      काष्ठा cw1200_queue_stats *stats,
		      u8 queue_id,
		      माप_प्रकार capacity,
		      अचिन्हित दीर्घ ttl);
पूर्णांक cw1200_queue_clear(काष्ठा cw1200_queue *queue);
व्योम cw1200_queue_stats_deinit(काष्ठा cw1200_queue_stats *stats);
व्योम cw1200_queue_deinit(काष्ठा cw1200_queue *queue);

माप_प्रकार cw1200_queue_get_num_queued(काष्ठा cw1200_queue *queue,
				   u32 link_id_map);
पूर्णांक cw1200_queue_put(काष्ठा cw1200_queue *queue,
		     काष्ठा sk_buff *skb,
		     काष्ठा cw1200_txpriv *txpriv);
पूर्णांक cw1200_queue_get(काष्ठा cw1200_queue *queue,
		     u32 link_id_map,
		     काष्ठा wsm_tx **tx,
		     काष्ठा ieee80211_tx_info **tx_info,
		     स्थिर काष्ठा cw1200_txpriv **txpriv);
पूर्णांक cw1200_queue_requeue(काष्ठा cw1200_queue *queue, u32 packet_id);
पूर्णांक cw1200_queue_requeue_all(काष्ठा cw1200_queue *queue);
पूर्णांक cw1200_queue_हटाओ(काष्ठा cw1200_queue *queue,
			u32 packet_id);
पूर्णांक cw1200_queue_get_skb(काष्ठा cw1200_queue *queue, u32 packet_id,
			 काष्ठा sk_buff **skb,
			 स्थिर काष्ठा cw1200_txpriv **txpriv);
व्योम cw1200_queue_lock(काष्ठा cw1200_queue *queue);
व्योम cw1200_queue_unlock(काष्ठा cw1200_queue *queue);
bool cw1200_queue_get_xmit_बारtamp(काष्ठा cw1200_queue *queue,
				     अचिन्हित दीर्घ *बारtamp,
				     u32 pending_frame_id);

bool cw1200_queue_stats_is_empty(काष्ठा cw1200_queue_stats *stats,
				 u32 link_id_map);

अटल अंतरभूत u8 cw1200_queue_get_queue_id(u32 packet_id)
अणु
	वापस (packet_id >> 16) & 0xFF;
पूर्ण

अटल अंतरभूत u8 cw1200_queue_get_generation(u32 packet_id)
अणु
	वापस (packet_id >>  8) & 0xFF;
पूर्ण

#पूर्ण_अगर /* CW1200_QUEUE_H_INCLUDED */
