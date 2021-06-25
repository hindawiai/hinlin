<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* XDP sockets
 *
 * AF_XDP sockets allows a channel between XDP programs and userspace
 * applications.
 * Copyright(c) 2018 Intel Corporation.
 *
 * Author(s): Bjथघrn Tथघpel <bjorn.topel@पूर्णांकel.com>
 *	      Magnus Karlsson <magnus.karlsson@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "AF_XDP: %s: " fmt, __func__

#समावेश <linux/अगर_xdp.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/socket.h>
#समावेश <linux/file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rculist.h>
#समावेश <net/xdp_sock_drv.h>
#समावेश <net/busy_poll.h>
#समावेश <net/xdp.h>

#समावेश "xsk_queue.h"
#समावेश "xdp_umem.h"
#समावेश "xsk.h"

#घोषणा TX_BATCH_SIZE 32

अटल DEFINE_PER_CPU(काष्ठा list_head, xskmap_flush_list);

व्योम xsk_set_rx_need_wakeup(काष्ठा xsk_buff_pool *pool)
अणु
	अगर (pool->cached_need_wakeup & XDP_WAKEUP_RX)
		वापस;

	pool->fq->ring->flags |= XDP_RING_NEED_WAKEUP;
	pool->cached_need_wakeup |= XDP_WAKEUP_RX;
पूर्ण
EXPORT_SYMBOL(xsk_set_rx_need_wakeup);

व्योम xsk_set_tx_need_wakeup(काष्ठा xsk_buff_pool *pool)
अणु
	काष्ठा xdp_sock *xs;

	अगर (pool->cached_need_wakeup & XDP_WAKEUP_TX)
		वापस;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(xs, &pool->xsk_tx_list, tx_list) अणु
		xs->tx->ring->flags |= XDP_RING_NEED_WAKEUP;
	पूर्ण
	rcu_पढ़ो_unlock();

	pool->cached_need_wakeup |= XDP_WAKEUP_TX;
पूर्ण
EXPORT_SYMBOL(xsk_set_tx_need_wakeup);

व्योम xsk_clear_rx_need_wakeup(काष्ठा xsk_buff_pool *pool)
अणु
	अगर (!(pool->cached_need_wakeup & XDP_WAKEUP_RX))
		वापस;

	pool->fq->ring->flags &= ~XDP_RING_NEED_WAKEUP;
	pool->cached_need_wakeup &= ~XDP_WAKEUP_RX;
पूर्ण
EXPORT_SYMBOL(xsk_clear_rx_need_wakeup);

व्योम xsk_clear_tx_need_wakeup(काष्ठा xsk_buff_pool *pool)
अणु
	काष्ठा xdp_sock *xs;

	अगर (!(pool->cached_need_wakeup & XDP_WAKEUP_TX))
		वापस;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(xs, &pool->xsk_tx_list, tx_list) अणु
		xs->tx->ring->flags &= ~XDP_RING_NEED_WAKEUP;
	पूर्ण
	rcu_पढ़ो_unlock();

	pool->cached_need_wakeup &= ~XDP_WAKEUP_TX;
पूर्ण
EXPORT_SYMBOL(xsk_clear_tx_need_wakeup);

bool xsk_uses_need_wakeup(काष्ठा xsk_buff_pool *pool)
अणु
	वापस pool->uses_need_wakeup;
पूर्ण
EXPORT_SYMBOL(xsk_uses_need_wakeup);

काष्ठा xsk_buff_pool *xsk_get_pool_from_qid(काष्ठा net_device *dev,
					    u16 queue_id)
अणु
	अगर (queue_id < dev->real_num_rx_queues)
		वापस dev->_rx[queue_id].pool;
	अगर (queue_id < dev->real_num_tx_queues)
		वापस dev->_tx[queue_id].pool;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(xsk_get_pool_from_qid);

व्योम xsk_clear_pool_at_qid(काष्ठा net_device *dev, u16 queue_id)
अणु
	अगर (queue_id < dev->num_rx_queues)
		dev->_rx[queue_id].pool = शून्य;
	अगर (queue_id < dev->num_tx_queues)
		dev->_tx[queue_id].pool = शून्य;
पूर्ण

/* The buffer pool is stored both in the _rx काष्ठा and the _tx काष्ठा as we करो
 * not know अगर the device has more tx queues than rx, or the opposite.
 * This might also change during run समय.
 */
पूर्णांक xsk_reg_pool_at_qid(काष्ठा net_device *dev, काष्ठा xsk_buff_pool *pool,
			u16 queue_id)
अणु
	अगर (queue_id >= max_t(अचिन्हित पूर्णांक,
			      dev->real_num_rx_queues,
			      dev->real_num_tx_queues))
		वापस -EINVAL;

	अगर (queue_id < dev->real_num_rx_queues)
		dev->_rx[queue_id].pool = pool;
	अगर (queue_id < dev->real_num_tx_queues)
		dev->_tx[queue_id].pool = pool;

	वापस 0;
पूर्ण

व्योम xp_release(काष्ठा xdp_buff_xsk *xskb)
अणु
	xskb->pool->मुक्त_heads[xskb->pool->मुक्त_heads_cnt++] = xskb;
पूर्ण

अटल u64 xp_get_handle(काष्ठा xdp_buff_xsk *xskb)
अणु
	u64 offset = xskb->xdp.data - xskb->xdp.data_hard_start;

	offset += xskb->pool->headroom;
	अगर (!xskb->pool->unaligned)
		वापस xskb->orig_addr + offset;
	वापस xskb->orig_addr + (offset << XSK_UNALIGNED_BUF_OFFSET_SHIFT);
पूर्ण

अटल पूर्णांक __xsk_rcv_zc(काष्ठा xdp_sock *xs, काष्ठा xdp_buff *xdp, u32 len)
अणु
	काष्ठा xdp_buff_xsk *xskb = container_of(xdp, काष्ठा xdp_buff_xsk, xdp);
	u64 addr;
	पूर्णांक err;

	addr = xp_get_handle(xskb);
	err = xskq_prod_reserve_desc(xs->rx, addr, len);
	अगर (err) अणु
		xs->rx_queue_full++;
		वापस err;
	पूर्ण

	xp_release(xskb);
	वापस 0;
पूर्ण

अटल व्योम xsk_copy_xdp(काष्ठा xdp_buff *to, काष्ठा xdp_buff *from, u32 len)
अणु
	व्योम *from_buf, *to_buf;
	u32 metalen;

	अगर (unlikely(xdp_data_meta_unsupported(from))) अणु
		from_buf = from->data;
		to_buf = to->data;
		metalen = 0;
	पूर्ण अन्यथा अणु
		from_buf = from->data_meta;
		metalen = from->data - from->data_meta;
		to_buf = to->data - metalen;
	पूर्ण

	स_नकल(to_buf, from_buf, len + metalen);
पूर्ण

अटल पूर्णांक __xsk_rcv(काष्ठा xdp_sock *xs, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा xdp_buff *xsk_xdp;
	पूर्णांक err;
	u32 len;

	len = xdp->data_end - xdp->data;
	अगर (len > xsk_pool_get_rx_frame_size(xs->pool)) अणु
		xs->rx_dropped++;
		वापस -ENOSPC;
	पूर्ण

	xsk_xdp = xsk_buff_alloc(xs->pool);
	अगर (!xsk_xdp) अणु
		xs->rx_dropped++;
		वापस -ENOSPC;
	पूर्ण

	xsk_copy_xdp(xsk_xdp, xdp, len);
	err = __xsk_rcv_zc(xs, xsk_xdp, len);
	अगर (err) अणु
		xsk_buff_मुक्त(xsk_xdp);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool xsk_tx_ग_लिखोable(काष्ठा xdp_sock *xs)
अणु
	अगर (xskq_cons_present_entries(xs->tx) > xs->tx->nentries / 2)
		वापस false;

	वापस true;
पूर्ण

अटल bool xsk_is_bound(काष्ठा xdp_sock *xs)
अणु
	अगर (READ_ONCE(xs->state) == XSK_BOUND) अणु
		/* Matches smp_wmb() in bind(). */
		smp_rmb();
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक xsk_rcv_check(काष्ठा xdp_sock *xs, काष्ठा xdp_buff *xdp)
अणु
	अगर (!xsk_is_bound(xs))
		वापस -EINVAL;

	अगर (xs->dev != xdp->rxq->dev || xs->queue_id != xdp->rxq->queue_index)
		वापस -EINVAL;

	sk_mark_napi_id_once_xdp(&xs->sk, xdp);
	वापस 0;
पूर्ण

अटल व्योम xsk_flush(काष्ठा xdp_sock *xs)
अणु
	xskq_prod_submit(xs->rx);
	__xskq_cons_release(xs->pool->fq);
	sock_def_पढ़ोable(&xs->sk);
पूर्ण

पूर्णांक xsk_generic_rcv(काष्ठा xdp_sock *xs, काष्ठा xdp_buff *xdp)
अणु
	पूर्णांक err;

	spin_lock_bh(&xs->rx_lock);
	err = xsk_rcv_check(xs, xdp);
	अगर (!err) अणु
		err = __xsk_rcv(xs, xdp);
		xsk_flush(xs);
	पूर्ण
	spin_unlock_bh(&xs->rx_lock);
	वापस err;
पूर्ण

अटल पूर्णांक xsk_rcv(काष्ठा xdp_sock *xs, काष्ठा xdp_buff *xdp)
अणु
	पूर्णांक err;
	u32 len;

	err = xsk_rcv_check(xs, xdp);
	अगर (err)
		वापस err;

	अगर (xdp->rxq->mem.type == MEM_TYPE_XSK_BUFF_POOL) अणु
		len = xdp->data_end - xdp->data;
		वापस __xsk_rcv_zc(xs, xdp, len);
	पूर्ण

	err = __xsk_rcv(xs, xdp);
	अगर (!err)
		xdp_वापस_buff(xdp);
	वापस err;
पूर्ण

पूर्णांक __xsk_map_redirect(काष्ठा xdp_sock *xs, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा list_head *flush_list = this_cpu_ptr(&xskmap_flush_list);
	पूर्णांक err;

	err = xsk_rcv(xs, xdp);
	अगर (err)
		वापस err;

	अगर (!xs->flush_node.prev)
		list_add(&xs->flush_node, flush_list);

	वापस 0;
पूर्ण

व्योम __xsk_map_flush(व्योम)
अणु
	काष्ठा list_head *flush_list = this_cpu_ptr(&xskmap_flush_list);
	काष्ठा xdp_sock *xs, *पंचांगp;

	list_क्रम_each_entry_safe(xs, पंचांगp, flush_list, flush_node) अणु
		xsk_flush(xs);
		__list_del_clearprev(&xs->flush_node);
	पूर्ण
पूर्ण

व्योम xsk_tx_completed(काष्ठा xsk_buff_pool *pool, u32 nb_entries)
अणु
	xskq_prod_submit_n(pool->cq, nb_entries);
पूर्ण
EXPORT_SYMBOL(xsk_tx_completed);

व्योम xsk_tx_release(काष्ठा xsk_buff_pool *pool)
अणु
	काष्ठा xdp_sock *xs;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(xs, &pool->xsk_tx_list, tx_list) अणु
		__xskq_cons_release(xs->tx);
		अगर (xsk_tx_ग_लिखोable(xs))
			xs->sk.sk_ग_लिखो_space(&xs->sk);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(xsk_tx_release);

bool xsk_tx_peek_desc(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_desc *desc)
अणु
	काष्ठा xdp_sock *xs;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(xs, &pool->xsk_tx_list, tx_list) अणु
		अगर (!xskq_cons_peek_desc(xs->tx, desc, pool)) अणु
			xs->tx->queue_empty_descs++;
			जारी;
		पूर्ण

		/* This is the backpressure mechanism क्रम the Tx path.
		 * Reserve space in the completion queue and only proceed
		 * अगर there is space in it. This aव्योमs having to implement
		 * any buffering in the Tx path.
		 */
		अगर (xskq_prod_reserve_addr(pool->cq, desc->addr))
			जाओ out;

		xskq_cons_release(xs->tx);
		rcu_पढ़ो_unlock();
		वापस true;
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस false;
पूर्ण
EXPORT_SYMBOL(xsk_tx_peek_desc);

अटल u32 xsk_tx_peek_release_fallback(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_desc *descs,
					u32 max_entries)
अणु
	u32 nb_pkts = 0;

	जबतक (nb_pkts < max_entries && xsk_tx_peek_desc(pool, &descs[nb_pkts]))
		nb_pkts++;

	xsk_tx_release(pool);
	वापस nb_pkts;
पूर्ण

u32 xsk_tx_peek_release_desc_batch(काष्ठा xsk_buff_pool *pool, काष्ठा xdp_desc *descs,
				   u32 max_entries)
अणु
	काष्ठा xdp_sock *xs;
	u32 nb_pkts;

	rcu_पढ़ो_lock();
	अगर (!list_is_singular(&pool->xsk_tx_list)) अणु
		/* Fallback to the non-batched version */
		rcu_पढ़ो_unlock();
		वापस xsk_tx_peek_release_fallback(pool, descs, max_entries);
	पूर्ण

	xs = list_first_or_null_rcu(&pool->xsk_tx_list, काष्ठा xdp_sock, tx_list);
	अगर (!xs) अणु
		nb_pkts = 0;
		जाओ out;
	पूर्ण

	nb_pkts = xskq_cons_peek_desc_batch(xs->tx, descs, pool, max_entries);
	अगर (!nb_pkts) अणु
		xs->tx->queue_empty_descs++;
		जाओ out;
	पूर्ण

	/* This is the backpressure mechanism क्रम the Tx path. Try to
	 * reserve space in the completion queue क्रम all packets, but
	 * अगर there are fewer slots available, just process that many
	 * packets. This aव्योमs having to implement any buffering in
	 * the Tx path.
	 */
	nb_pkts = xskq_prod_reserve_addr_batch(pool->cq, descs, nb_pkts);
	अगर (!nb_pkts)
		जाओ out;

	xskq_cons_release_n(xs->tx, nb_pkts);
	__xskq_cons_release(xs->tx);
	xs->sk.sk_ग_लिखो_space(&xs->sk);

out:
	rcu_पढ़ो_unlock();
	वापस nb_pkts;
पूर्ण
EXPORT_SYMBOL(xsk_tx_peek_release_desc_batch);

अटल पूर्णांक xsk_wakeup(काष्ठा xdp_sock *xs, u8 flags)
अणु
	काष्ठा net_device *dev = xs->dev;
	पूर्णांक err;

	rcu_पढ़ो_lock();
	err = dev->netdev_ops->nकरो_xsk_wakeup(dev, xs->queue_id, flags);
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल पूर्णांक xsk_zc_xmit(काष्ठा xdp_sock *xs)
अणु
	वापस xsk_wakeup(xs, XDP_WAKEUP_TX);
पूर्ण

अटल व्योम xsk_deकाष्ठा_skb(काष्ठा sk_buff *skb)
अणु
	u64 addr = (u64)(दीर्घ)skb_shinfo(skb)->deकाष्ठाor_arg;
	काष्ठा xdp_sock *xs = xdp_sk(skb->sk);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&xs->pool->cq_lock, flags);
	xskq_prod_submit_addr(xs->pool->cq, addr);
	spin_unlock_irqrestore(&xs->pool->cq_lock, flags);

	sock_wमुक्त(skb);
पूर्ण

अटल काष्ठा sk_buff *xsk_build_skb_zerocopy(काष्ठा xdp_sock *xs,
					      काष्ठा xdp_desc *desc)
अणु
	काष्ठा xsk_buff_pool *pool = xs->pool;
	u32 hr, len, ts, offset, copy, copied;
	काष्ठा sk_buff *skb;
	काष्ठा page *page;
	व्योम *buffer;
	पूर्णांक err, i;
	u64 addr;

	hr = max(NET_SKB_PAD, L1_CACHE_ALIGN(xs->dev->needed_headroom));

	skb = sock_alloc_send_skb(&xs->sk, hr, 1, &err);
	अगर (unlikely(!skb))
		वापस ERR_PTR(err);

	skb_reserve(skb, hr);

	addr = desc->addr;
	len = desc->len;
	ts = pool->unaligned ? len : pool->chunk_size;

	buffer = xsk_buff_raw_get_data(pool, addr);
	offset = offset_in_page(buffer);
	addr = buffer - pool->addrs;

	क्रम (copied = 0, i = 0; copied < len; i++) अणु
		page = pool->umem->pgs[addr >> PAGE_SHIFT];
		get_page(page);

		copy = min_t(u32, PAGE_SIZE - offset, len - copied);
		skb_fill_page_desc(skb, i, page, offset, copy);

		copied += copy;
		addr += copy;
		offset = 0;
	पूर्ण

	skb->len += len;
	skb->data_len += len;
	skb->truesize += ts;

	refcount_add(ts, &xs->sk.sk_wmem_alloc);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *xsk_build_skb(काष्ठा xdp_sock *xs,
				     काष्ठा xdp_desc *desc)
अणु
	काष्ठा net_device *dev = xs->dev;
	काष्ठा sk_buff *skb;

	अगर (dev->priv_flags & IFF_TX_SKB_NO_LINEAR) अणु
		skb = xsk_build_skb_zerocopy(xs, desc);
		अगर (IS_ERR(skb))
			वापस skb;
	पूर्ण अन्यथा अणु
		u32 hr, tr, len;
		व्योम *buffer;
		पूर्णांक err;

		hr = max(NET_SKB_PAD, L1_CACHE_ALIGN(dev->needed_headroom));
		tr = dev->needed_tailroom;
		len = desc->len;

		skb = sock_alloc_send_skb(&xs->sk, hr + len + tr, 1, &err);
		अगर (unlikely(!skb))
			वापस ERR_PTR(err);

		skb_reserve(skb, hr);
		skb_put(skb, len);

		buffer = xsk_buff_raw_get_data(xs->pool, desc->addr);
		err = skb_store_bits(skb, 0, buffer, len);
		अगर (unlikely(err)) अणु
			kमुक्त_skb(skb);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	skb->dev = dev;
	skb->priority = xs->sk.sk_priority;
	skb->mark = xs->sk.sk_mark;
	skb_shinfo(skb)->deकाष्ठाor_arg = (व्योम *)(दीर्घ)desc->addr;
	skb->deकाष्ठाor = xsk_deकाष्ठा_skb;

	वापस skb;
पूर्ण

अटल पूर्णांक xsk_generic_xmit(काष्ठा sock *sk)
अणु
	काष्ठा xdp_sock *xs = xdp_sk(sk);
	u32 max_batch = TX_BATCH_SIZE;
	bool sent_frame = false;
	काष्ठा xdp_desc desc;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	mutex_lock(&xs->mutex);

	अगर (xs->queue_id >= xs->dev->real_num_tx_queues)
		जाओ out;

	जबतक (xskq_cons_peek_desc(xs->tx, &desc, xs->pool)) अणु
		अगर (max_batch-- == 0) अणु
			err = -EAGAIN;
			जाओ out;
		पूर्ण

		skb = xsk_build_skb(xs, &desc);
		अगर (IS_ERR(skb)) अणु
			err = PTR_ERR(skb);
			जाओ out;
		पूर्ण

		/* This is the backpressure mechanism क्रम the Tx path.
		 * Reserve space in the completion queue and only proceed
		 * अगर there is space in it. This aव्योमs having to implement
		 * any buffering in the Tx path.
		 */
		spin_lock_irqsave(&xs->pool->cq_lock, flags);
		अगर (xskq_prod_reserve(xs->pool->cq)) अणु
			spin_unlock_irqrestore(&xs->pool->cq_lock, flags);
			kमुक्त_skb(skb);
			जाओ out;
		पूर्ण
		spin_unlock_irqrestore(&xs->pool->cq_lock, flags);

		err = __dev_direct_xmit(skb, xs->queue_id);
		अगर  (err == NETDEV_TX_BUSY) अणु
			/* Tell user-space to retry the send */
			skb->deकाष्ठाor = sock_wमुक्त;
			spin_lock_irqsave(&xs->pool->cq_lock, flags);
			xskq_prod_cancel(xs->pool->cq);
			spin_unlock_irqrestore(&xs->pool->cq_lock, flags);
			/* Free skb without triggering the perf drop trace */
			consume_skb(skb);
			err = -EAGAIN;
			जाओ out;
		पूर्ण

		xskq_cons_release(xs->tx);
		/* Ignore NET_XMIT_CN as packet might have been sent */
		अगर (err == NET_XMIT_DROP) अणु
			/* SKB completed but not sent */
			err = -EBUSY;
			जाओ out;
		पूर्ण

		sent_frame = true;
	पूर्ण

	xs->tx->queue_empty_descs++;

out:
	अगर (sent_frame)
		अगर (xsk_tx_ग_लिखोable(xs))
			sk->sk_ग_लिखो_space(sk);

	mutex_unlock(&xs->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक __xsk_sendmsg(काष्ठा sock *sk)
अणु
	काष्ठा xdp_sock *xs = xdp_sk(sk);

	अगर (unlikely(!(xs->dev->flags & IFF_UP)))
		वापस -ENETDOWN;
	अगर (unlikely(!xs->tx))
		वापस -ENOBUFS;

	वापस xs->zc ? xsk_zc_xmit(xs) : xsk_generic_xmit(sk);
पूर्ण

अटल bool xsk_no_wakeup(काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	/* Prefer busy-polling, skip the wakeup. */
	वापस READ_ONCE(sk->sk_prefer_busy_poll) && READ_ONCE(sk->sk_ll_usec) &&
		READ_ONCE(sk->sk_napi_id) >= MIN_NAPI_ID;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक xsk_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार total_len)
अणु
	bool need_रुको = !(m->msg_flags & MSG_DONTWAIT);
	काष्ठा sock *sk = sock->sk;
	काष्ठा xdp_sock *xs = xdp_sk(sk);
	काष्ठा xsk_buff_pool *pool;

	अगर (unlikely(!xsk_is_bound(xs)))
		वापस -ENXIO;
	अगर (unlikely(need_रुको))
		वापस -EOPNOTSUPP;

	अगर (sk_can_busy_loop(sk))
		sk_busy_loop(sk, 1); /* only support non-blocking sockets */

	अगर (xsk_no_wakeup(sk))
		वापस 0;

	pool = xs->pool;
	अगर (pool->cached_need_wakeup & XDP_WAKEUP_TX)
		वापस __xsk_sendmsg(sk);
	वापस 0;
पूर्ण

अटल पूर्णांक xsk_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार len, पूर्णांक flags)
अणु
	bool need_रुको = !(flags & MSG_DONTWAIT);
	काष्ठा sock *sk = sock->sk;
	काष्ठा xdp_sock *xs = xdp_sk(sk);

	अगर (unlikely(!xsk_is_bound(xs)))
		वापस -ENXIO;
	अगर (unlikely(!(xs->dev->flags & IFF_UP)))
		वापस -ENETDOWN;
	अगर (unlikely(!xs->rx))
		वापस -ENOBUFS;
	अगर (unlikely(need_रुको))
		वापस -EOPNOTSUPP;

	अगर (sk_can_busy_loop(sk))
		sk_busy_loop(sk, 1); /* only support non-blocking sockets */

	अगर (xsk_no_wakeup(sk))
		वापस 0;

	अगर (xs->pool->cached_need_wakeup & XDP_WAKEUP_RX && xs->zc)
		वापस xsk_wakeup(xs, XDP_WAKEUP_RX);
	वापस 0;
पूर्ण

अटल __poll_t xsk_poll(काष्ठा file *file, काष्ठा socket *sock,
			     काष्ठा poll_table_काष्ठा *रुको)
अणु
	__poll_t mask = 0;
	काष्ठा sock *sk = sock->sk;
	काष्ठा xdp_sock *xs = xdp_sk(sk);
	काष्ठा xsk_buff_pool *pool;

	sock_poll_रुको(file, sock, रुको);

	अगर (unlikely(!xsk_is_bound(xs)))
		वापस mask;

	pool = xs->pool;

	अगर (pool->cached_need_wakeup) अणु
		अगर (xs->zc)
			xsk_wakeup(xs, pool->cached_need_wakeup);
		अन्यथा
			/* Poll needs to drive Tx also in copy mode */
			__xsk_sendmsg(sk);
	पूर्ण

	अगर (xs->rx && !xskq_prod_is_empty(xs->rx))
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (xs->tx && xsk_tx_ग_लिखोable(xs))
		mask |= EPOLLOUT | EPOLLWRNORM;

	वापस mask;
पूर्ण

अटल पूर्णांक xsk_init_queue(u32 entries, काष्ठा xsk_queue **queue,
			  bool umem_queue)
अणु
	काष्ठा xsk_queue *q;

	अगर (entries == 0 || *queue || !is_घातer_of_2(entries))
		वापस -EINVAL;

	q = xskq_create(entries, umem_queue);
	अगर (!q)
		वापस -ENOMEM;

	/* Make sure queue is पढ़ोy beक्रमe it can be seen by others */
	smp_wmb();
	WRITE_ONCE(*queue, q);
	वापस 0;
पूर्ण

अटल व्योम xsk_unbind_dev(काष्ठा xdp_sock *xs)
अणु
	काष्ठा net_device *dev = xs->dev;

	अगर (xs->state != XSK_BOUND)
		वापस;
	WRITE_ONCE(xs->state, XSK_UNBOUND);

	/* Wait क्रम driver to stop using the xdp socket. */
	xp_del_xsk(xs->pool, xs);
	xs->dev = शून्य;
	synchronize_net();
	dev_put(dev);
पूर्ण

अटल काष्ठा xsk_map *xsk_get_map_list_entry(काष्ठा xdp_sock *xs,
					      काष्ठा xdp_sock ***map_entry)
अणु
	काष्ठा xsk_map *map = शून्य;
	काष्ठा xsk_map_node *node;

	*map_entry = शून्य;

	spin_lock_bh(&xs->map_list_lock);
	node = list_first_entry_or_null(&xs->map_list, काष्ठा xsk_map_node,
					node);
	अगर (node) अणु
		bpf_map_inc(&node->map->map);
		map = node->map;
		*map_entry = node->map_entry;
	पूर्ण
	spin_unlock_bh(&xs->map_list_lock);
	वापस map;
पूर्ण

अटल व्योम xsk_delete_from_maps(काष्ठा xdp_sock *xs)
अणु
	/* This function हटाओs the current XDP socket from all the
	 * maps it resides in. We need to take extra care here, due to
	 * the two locks involved. Each map has a lock synchronizing
	 * updates to the entries, and each socket has a lock that
	 * synchronizes access to the list of maps (map_list). For
	 * deadlock aव्योमance the locks need to be taken in the order
	 * "map lock"->"socket map list lock". We start off by
	 * accessing the socket map list, and take a reference to the
	 * map to guarantee existence between the
	 * xsk_get_map_list_entry() and xsk_map_try_sock_delete()
	 * calls. Then we ask the map to हटाओ the socket, which
	 * tries to हटाओ the socket from the map. Note that there
	 * might be updates to the map between
	 * xsk_get_map_list_entry() and xsk_map_try_sock_delete().
	 */
	काष्ठा xdp_sock **map_entry = शून्य;
	काष्ठा xsk_map *map;

	जबतक ((map = xsk_get_map_list_entry(xs, &map_entry))) अणु
		xsk_map_try_sock_delete(map, xs, map_entry);
		bpf_map_put(&map->map);
	पूर्ण
पूर्ण

अटल पूर्णांक xsk_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा xdp_sock *xs = xdp_sk(sk);
	काष्ठा net *net;

	अगर (!sk)
		वापस 0;

	net = sock_net(sk);

	mutex_lock(&net->xdp.lock);
	sk_del_node_init_rcu(sk);
	mutex_unlock(&net->xdp.lock);

	local_bh_disable();
	sock_prot_inuse_add(net, sk->sk_prot, -1);
	local_bh_enable();

	xsk_delete_from_maps(xs);
	mutex_lock(&xs->mutex);
	xsk_unbind_dev(xs);
	mutex_unlock(&xs->mutex);

	xskq_destroy(xs->rx);
	xskq_destroy(xs->tx);
	xskq_destroy(xs->fq_पंचांगp);
	xskq_destroy(xs->cq_पंचांगp);

	sock_orphan(sk);
	sock->sk = शून्य;

	sk_refcnt_debug_release(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल काष्ठा socket *xsk_lookup_xsk_from_fd(पूर्णांक fd)
अणु
	काष्ठा socket *sock;
	पूर्णांक err;

	sock = sockfd_lookup(fd, &err);
	अगर (!sock)
		वापस ERR_PTR(-ENOTSOCK);

	अगर (sock->sk->sk_family != PF_XDP) अणु
		sockfd_put(sock);
		वापस ERR_PTR(-ENOPROTOOPT);
	पूर्ण

	वापस sock;
पूर्ण

अटल bool xsk_validate_queues(काष्ठा xdp_sock *xs)
अणु
	वापस xs->fq_पंचांगp && xs->cq_पंचांगp;
पूर्ण

अटल पूर्णांक xsk_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_xdp *sxdp = (काष्ठा sockaddr_xdp *)addr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा xdp_sock *xs = xdp_sk(sk);
	काष्ठा net_device *dev;
	u32 flags, qid;
	पूर्णांक err = 0;

	अगर (addr_len < माप(काष्ठा sockaddr_xdp))
		वापस -EINVAL;
	अगर (sxdp->sxdp_family != AF_XDP)
		वापस -EINVAL;

	flags = sxdp->sxdp_flags;
	अगर (flags & ~(XDP_SHARED_UMEM | XDP_COPY | XDP_ZEROCOPY |
		      XDP_USE_NEED_WAKEUP))
		वापस -EINVAL;

	rtnl_lock();
	mutex_lock(&xs->mutex);
	अगर (xs->state != XSK_READY) अणु
		err = -EBUSY;
		जाओ out_release;
	पूर्ण

	dev = dev_get_by_index(sock_net(sk), sxdp->sxdp_अगरindex);
	अगर (!dev) अणु
		err = -ENODEV;
		जाओ out_release;
	पूर्ण

	अगर (!xs->rx && !xs->tx) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	qid = sxdp->sxdp_queue_id;

	अगर (flags & XDP_SHARED_UMEM) अणु
		काष्ठा xdp_sock *umem_xs;
		काष्ठा socket *sock;

		अगर ((flags & XDP_COPY) || (flags & XDP_ZEROCOPY) ||
		    (flags & XDP_USE_NEED_WAKEUP)) अणु
			/* Cannot specअगरy flags क्रम shared sockets. */
			err = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		अगर (xs->umem) अणु
			/* We have alपढ़ोy our own. */
			err = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		sock = xsk_lookup_xsk_from_fd(sxdp->sxdp_shared_umem_fd);
		अगर (IS_ERR(sock)) अणु
			err = PTR_ERR(sock);
			जाओ out_unlock;
		पूर्ण

		umem_xs = xdp_sk(sock->sk);
		अगर (!xsk_is_bound(umem_xs)) अणु
			err = -EBADF;
			sockfd_put(sock);
			जाओ out_unlock;
		पूर्ण

		अगर (umem_xs->queue_id != qid || umem_xs->dev != dev) अणु
			/* Share the umem with another socket on another qid
			 * and/or device.
			 */
			xs->pool = xp_create_and_assign_umem(xs,
							     umem_xs->umem);
			अगर (!xs->pool) अणु
				err = -ENOMEM;
				sockfd_put(sock);
				जाओ out_unlock;
			पूर्ण

			err = xp_assign_dev_shared(xs->pool, umem_xs->umem,
						   dev, qid);
			अगर (err) अणु
				xp_destroy(xs->pool);
				xs->pool = शून्य;
				sockfd_put(sock);
				जाओ out_unlock;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Share the buffer pool with the other socket. */
			अगर (xs->fq_पंचांगp || xs->cq_पंचांगp) अणु
				/* Do not allow setting your own fq or cq. */
				err = -EINVAL;
				sockfd_put(sock);
				जाओ out_unlock;
			पूर्ण

			xp_get_pool(umem_xs->pool);
			xs->pool = umem_xs->pool;
		पूर्ण

		xdp_get_umem(umem_xs->umem);
		WRITE_ONCE(xs->umem, umem_xs->umem);
		sockfd_put(sock);
	पूर्ण अन्यथा अगर (!xs->umem || !xsk_validate_queues(xs)) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण अन्यथा अणु
		/* This xsk has its own umem. */
		xs->pool = xp_create_and_assign_umem(xs, xs->umem);
		अगर (!xs->pool) अणु
			err = -ENOMEM;
			जाओ out_unlock;
		पूर्ण

		err = xp_assign_dev(xs->pool, dev, qid, flags);
		अगर (err) अणु
			xp_destroy(xs->pool);
			xs->pool = शून्य;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/* FQ and CQ are now owned by the buffer pool and cleaned up with it. */
	xs->fq_पंचांगp = शून्य;
	xs->cq_पंचांगp = शून्य;

	xs->dev = dev;
	xs->zc = xs->umem->zc;
	xs->queue_id = qid;
	xp_add_xsk(xs->pool, xs);

out_unlock:
	अगर (err) अणु
		dev_put(dev);
	पूर्ण अन्यथा अणु
		/* Matches smp_rmb() in bind() क्रम shared umem
		 * sockets, and xsk_is_bound().
		 */
		smp_wmb();
		WRITE_ONCE(xs->state, XSK_BOUND);
	पूर्ण
out_release:
	mutex_unlock(&xs->mutex);
	rtnl_unlock();
	वापस err;
पूर्ण

काष्ठा xdp_umem_reg_v1 अणु
	__u64 addr; /* Start of packet data area */
	__u64 len; /* Length of packet data area */
	__u32 chunk_size;
	__u32 headroom;
पूर्ण;

अटल पूर्णांक xsk_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा xdp_sock *xs = xdp_sk(sk);
	पूर्णांक err;

	अगर (level != SOL_XDP)
		वापस -ENOPROTOOPT;

	चयन (optname) अणु
	हाल XDP_RX_RING:
	हाल XDP_TX_RING:
	अणु
		काष्ठा xsk_queue **q;
		पूर्णांक entries;

		अगर (optlen < माप(entries))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&entries, optval, माप(entries)))
			वापस -EFAULT;

		mutex_lock(&xs->mutex);
		अगर (xs->state != XSK_READY) अणु
			mutex_unlock(&xs->mutex);
			वापस -EBUSY;
		पूर्ण
		q = (optname == XDP_TX_RING) ? &xs->tx : &xs->rx;
		err = xsk_init_queue(entries, q, false);
		अगर (!err && optname == XDP_TX_RING)
			/* Tx needs to be explicitly woken up the first समय */
			xs->tx->ring->flags |= XDP_RING_NEED_WAKEUP;
		mutex_unlock(&xs->mutex);
		वापस err;
	पूर्ण
	हाल XDP_UMEM_REG:
	अणु
		माप_प्रकार mr_size = माप(काष्ठा xdp_umem_reg);
		काष्ठा xdp_umem_reg mr = अणुपूर्ण;
		काष्ठा xdp_umem *umem;

		अगर (optlen < माप(काष्ठा xdp_umem_reg_v1))
			वापस -EINVAL;
		अन्यथा अगर (optlen < माप(mr))
			mr_size = माप(काष्ठा xdp_umem_reg_v1);

		अगर (copy_from_sockptr(&mr, optval, mr_size))
			वापस -EFAULT;

		mutex_lock(&xs->mutex);
		अगर (xs->state != XSK_READY || xs->umem) अणु
			mutex_unlock(&xs->mutex);
			वापस -EBUSY;
		पूर्ण

		umem = xdp_umem_create(&mr);
		अगर (IS_ERR(umem)) अणु
			mutex_unlock(&xs->mutex);
			वापस PTR_ERR(umem);
		पूर्ण

		/* Make sure umem is पढ़ोy beक्रमe it can be seen by others */
		smp_wmb();
		WRITE_ONCE(xs->umem, umem);
		mutex_unlock(&xs->mutex);
		वापस 0;
	पूर्ण
	हाल XDP_UMEM_FILL_RING:
	हाल XDP_UMEM_COMPLETION_RING:
	अणु
		काष्ठा xsk_queue **q;
		पूर्णांक entries;

		अगर (copy_from_sockptr(&entries, optval, माप(entries)))
			वापस -EFAULT;

		mutex_lock(&xs->mutex);
		अगर (xs->state != XSK_READY) अणु
			mutex_unlock(&xs->mutex);
			वापस -EBUSY;
		पूर्ण

		q = (optname == XDP_UMEM_FILL_RING) ? &xs->fq_पंचांगp :
			&xs->cq_पंचांगp;
		err = xsk_init_queue(entries, q, true);
		mutex_unlock(&xs->mutex);
		वापस err;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस -ENOPROTOOPT;
पूर्ण

अटल व्योम xsk_enter_rxtx_offsets(काष्ठा xdp_ring_offset_v1 *ring)
अणु
	ring->producer = दुरत्व(काष्ठा xdp_rxtx_ring, ptrs.producer);
	ring->consumer = दुरत्व(काष्ठा xdp_rxtx_ring, ptrs.consumer);
	ring->desc = दुरत्व(काष्ठा xdp_rxtx_ring, desc);
पूर्ण

अटल व्योम xsk_enter_umem_offsets(काष्ठा xdp_ring_offset_v1 *ring)
अणु
	ring->producer = दुरत्व(काष्ठा xdp_umem_ring, ptrs.producer);
	ring->consumer = दुरत्व(काष्ठा xdp_umem_ring, ptrs.consumer);
	ring->desc = दुरत्व(काष्ठा xdp_umem_ring, desc);
पूर्ण

काष्ठा xdp_statistics_v1 अणु
	__u64 rx_dropped;
	__u64 rx_invalid_descs;
	__u64 tx_invalid_descs;
पूर्ण;

अटल पूर्णांक xsk_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा xdp_sock *xs = xdp_sk(sk);
	पूर्णांक len;

	अगर (level != SOL_XDP)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;
	अगर (len < 0)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल XDP_STATISTICS:
	अणु
		काष्ठा xdp_statistics stats = अणुपूर्ण;
		bool extra_stats = true;
		माप_प्रकार stats_size;

		अगर (len < माप(काष्ठा xdp_statistics_v1)) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (len < माप(stats)) अणु
			extra_stats = false;
			stats_size = माप(काष्ठा xdp_statistics_v1);
		पूर्ण अन्यथा अणु
			stats_size = माप(stats);
		पूर्ण

		mutex_lock(&xs->mutex);
		stats.rx_dropped = xs->rx_dropped;
		अगर (extra_stats) अणु
			stats.rx_ring_full = xs->rx_queue_full;
			stats.rx_fill_ring_empty_descs =
				xs->pool ? xskq_nb_queue_empty_descs(xs->pool->fq) : 0;
			stats.tx_ring_empty_descs = xskq_nb_queue_empty_descs(xs->tx);
		पूर्ण अन्यथा अणु
			stats.rx_dropped += xs->rx_queue_full;
		पूर्ण
		stats.rx_invalid_descs = xskq_nb_invalid_descs(xs->rx);
		stats.tx_invalid_descs = xskq_nb_invalid_descs(xs->tx);
		mutex_unlock(&xs->mutex);

		अगर (copy_to_user(optval, &stats, stats_size))
			वापस -EFAULT;
		अगर (put_user(stats_size, optlen))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल XDP_MMAP_OFFSETS:
	अणु
		काष्ठा xdp_mmap_offsets off;
		काष्ठा xdp_mmap_offsets_v1 off_v1;
		bool flags_supported = true;
		व्योम *to_copy;

		अगर (len < माप(off_v1))
			वापस -EINVAL;
		अन्यथा अगर (len < माप(off))
			flags_supported = false;

		अगर (flags_supported) अणु
			/* xdp_ring_offset is identical to xdp_ring_offset_v1
			 * except क्रम the flags field added to the end.
			 */
			xsk_enter_rxtx_offsets((काष्ठा xdp_ring_offset_v1 *)
					       &off.rx);
			xsk_enter_rxtx_offsets((काष्ठा xdp_ring_offset_v1 *)
					       &off.tx);
			xsk_enter_umem_offsets((काष्ठा xdp_ring_offset_v1 *)
					       &off.fr);
			xsk_enter_umem_offsets((काष्ठा xdp_ring_offset_v1 *)
					       &off.cr);
			off.rx.flags = दुरत्व(काष्ठा xdp_rxtx_ring,
						ptrs.flags);
			off.tx.flags = दुरत्व(काष्ठा xdp_rxtx_ring,
						ptrs.flags);
			off.fr.flags = दुरत्व(काष्ठा xdp_umem_ring,
						ptrs.flags);
			off.cr.flags = दुरत्व(काष्ठा xdp_umem_ring,
						ptrs.flags);

			len = माप(off);
			to_copy = &off;
		पूर्ण अन्यथा अणु
			xsk_enter_rxtx_offsets(&off_v1.rx);
			xsk_enter_rxtx_offsets(&off_v1.tx);
			xsk_enter_umem_offsets(&off_v1.fr);
			xsk_enter_umem_offsets(&off_v1.cr);

			len = माप(off_v1);
			to_copy = &off_v1;
		पूर्ण

		अगर (copy_to_user(optval, to_copy, len))
			वापस -EFAULT;
		अगर (put_user(len, optlen))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल XDP_OPTIONS:
	अणु
		काष्ठा xdp_options opts = अणुपूर्ण;

		अगर (len < माप(opts))
			वापस -EINVAL;

		mutex_lock(&xs->mutex);
		अगर (xs->zc)
			opts.flags |= XDP_OPTIONS_ZEROCOPY;
		mutex_unlock(&xs->mutex);

		len = माप(opts);
		अगर (copy_to_user(optval, &opts, len))
			वापस -EFAULT;
		अगर (put_user(len, optlen))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक xsk_mmap(काष्ठा file *file, काष्ठा socket *sock,
		    काष्ठा vm_area_काष्ठा *vma)
अणु
	loff_t offset = (loff_t)vma->vm_pgoff << PAGE_SHIFT;
	अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;
	काष्ठा xdp_sock *xs = xdp_sk(sock->sk);
	काष्ठा xsk_queue *q = शून्य;
	अचिन्हित दीर्घ pfn;
	काष्ठा page *qpg;

	अगर (READ_ONCE(xs->state) != XSK_READY)
		वापस -EBUSY;

	अगर (offset == XDP_PGOFF_RX_RING) अणु
		q = READ_ONCE(xs->rx);
	पूर्ण अन्यथा अगर (offset == XDP_PGOFF_TX_RING) अणु
		q = READ_ONCE(xs->tx);
	पूर्ण अन्यथा अणु
		/* Matches the smp_wmb() in XDP_UMEM_REG */
		smp_rmb();
		अगर (offset == XDP_UMEM_PGOFF_FILL_RING)
			q = READ_ONCE(xs->fq_पंचांगp);
		अन्यथा अगर (offset == XDP_UMEM_PGOFF_COMPLETION_RING)
			q = READ_ONCE(xs->cq_पंचांगp);
	पूर्ण

	अगर (!q)
		वापस -EINVAL;

	/* Matches the smp_wmb() in xsk_init_queue */
	smp_rmb();
	qpg = virt_to_head_page(q->ring);
	अगर (size > page_size(qpg))
		वापस -EINVAL;

	pfn = virt_to_phys(q->ring) >> PAGE_SHIFT;
	वापस remap_pfn_range(vma, vma->vm_start, pfn,
			       size, vma->vm_page_prot);
पूर्ण

अटल पूर्णांक xsk_notअगरier(काष्ठा notअगरier_block *this,
			अचिन्हित दीर्घ msg, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);
	काष्ठा sock *sk;

	चयन (msg) अणु
	हाल NETDEV_UNREGISTER:
		mutex_lock(&net->xdp.lock);
		sk_क्रम_each(sk, &net->xdp.list) अणु
			काष्ठा xdp_sock *xs = xdp_sk(sk);

			mutex_lock(&xs->mutex);
			अगर (xs->dev == dev) अणु
				sk->sk_err = ENETDOWN;
				अगर (!sock_flag(sk, SOCK_DEAD))
					sk->sk_error_report(sk);

				xsk_unbind_dev(xs);

				/* Clear device references. */
				xp_clear_dev(xs->pool);
			पूर्ण
			mutex_unlock(&xs->mutex);
		पूर्ण
		mutex_unlock(&net->xdp.lock);
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा proto xsk_proto = अणु
	.name =		"XDP",
	.owner =	THIS_MODULE,
	.obj_size =	माप(काष्ठा xdp_sock),
पूर्ण;

अटल स्थिर काष्ठा proto_ops xsk_proto_ops = अणु
	.family		= PF_XDP,
	.owner		= THIS_MODULE,
	.release	= xsk_release,
	.bind		= xsk_bind,
	.connect	= sock_no_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.getname	= sock_no_getname,
	.poll		= xsk_poll,
	.ioctl		= sock_no_ioctl,
	.listen		= sock_no_listen,
	.shutकरोwn	= sock_no_shutकरोwn,
	.setsockopt	= xsk_setsockopt,
	.माला_लोockopt	= xsk_माला_लोockopt,
	.sendmsg	= xsk_sendmsg,
	.recvmsg	= xsk_recvmsg,
	.mmap		= xsk_mmap,
	.sendpage	= sock_no_sendpage,
पूर्ण;

अटल व्योम xsk_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा xdp_sock *xs = xdp_sk(sk);

	अगर (!sock_flag(sk, SOCK_DEAD))
		वापस;

	अगर (!xp_put_pool(xs->pool))
		xdp_put_umem(xs->umem, !xs->pool);

	sk_refcnt_debug_dec(sk);
पूर्ण

अटल पूर्णांक xsk_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		      पूर्णांक kern)
अणु
	काष्ठा xdp_sock *xs;
	काष्ठा sock *sk;

	अगर (!ns_capable(net->user_ns, CAP_NET_RAW))
		वापस -EPERM;
	अगर (sock->type != SOCK_RAW)
		वापस -ESOCKTNOSUPPORT;

	अगर (protocol)
		वापस -EPROTONOSUPPORT;

	sock->state = SS_UNCONNECTED;

	sk = sk_alloc(net, PF_XDP, GFP_KERNEL, &xsk_proto, kern);
	अगर (!sk)
		वापस -ENOBUFS;

	sock->ops = &xsk_proto_ops;

	sock_init_data(sock, sk);

	sk->sk_family = PF_XDP;

	sk->sk_deकाष्ठा = xsk_deकाष्ठा;
	sk_refcnt_debug_inc(sk);

	sock_set_flag(sk, SOCK_RCU_FREE);

	xs = xdp_sk(sk);
	xs->state = XSK_READY;
	mutex_init(&xs->mutex);
	spin_lock_init(&xs->rx_lock);

	INIT_LIST_HEAD(&xs->map_list);
	spin_lock_init(&xs->map_list_lock);

	mutex_lock(&net->xdp.lock);
	sk_add_node_rcu(sk, &net->xdp.list);
	mutex_unlock(&net->xdp.lock);

	local_bh_disable();
	sock_prot_inuse_add(net, &xsk_proto, 1);
	local_bh_enable();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_proto_family xsk_family_ops = अणु
	.family = PF_XDP,
	.create = xsk_create,
	.owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा notअगरier_block xsk_netdev_notअगरier = अणु
	.notअगरier_call	= xsk_notअगरier,
पूर्ण;

अटल पूर्णांक __net_init xsk_net_init(काष्ठा net *net)
अणु
	mutex_init(&net->xdp.lock);
	INIT_HLIST_HEAD(&net->xdp.list);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास xsk_net_निकास(काष्ठा net *net)
अणु
	WARN_ON_ONCE(!hlist_empty(&net->xdp.list));
पूर्ण

अटल काष्ठा pernet_operations xsk_net_ops = अणु
	.init = xsk_net_init,
	.निकास = xsk_net_निकास,
पूर्ण;

अटल पूर्णांक __init xsk_init(व्योम)
अणु
	पूर्णांक err, cpu;

	err = proto_रेजिस्टर(&xsk_proto, 0 /* no slab */);
	अगर (err)
		जाओ out;

	err = sock_रेजिस्टर(&xsk_family_ops);
	अगर (err)
		जाओ out_proto;

	err = रेजिस्टर_pernet_subsys(&xsk_net_ops);
	अगर (err)
		जाओ out_sk;

	err = रेजिस्टर_netdevice_notअगरier(&xsk_netdev_notअगरier);
	अगर (err)
		जाओ out_pernet;

	क्रम_each_possible_cpu(cpu)
		INIT_LIST_HEAD(&per_cpu(xskmap_flush_list, cpu));
	वापस 0;

out_pernet:
	unरेजिस्टर_pernet_subsys(&xsk_net_ops);
out_sk:
	sock_unरेजिस्टर(PF_XDP);
out_proto:
	proto_unरेजिस्टर(&xsk_proto);
out:
	वापस err;
पूर्ण

fs_initcall(xsk_init);
