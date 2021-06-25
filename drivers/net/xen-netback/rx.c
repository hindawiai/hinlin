<शैली गुरु>
/*
 * Copyright (c) 2016 Citrix Systems Inc.
 * Copyright (c) 2002-2005, K A Fraser
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#समावेश "common.h"

#समावेश <linux/kthपढ़ो.h>

#समावेश <xen/xen.h>
#समावेश <xen/events.h>

अटल bool xenvअगर_rx_ring_slots_available(काष्ठा xenvअगर_queue *queue)
अणु
	RING_IDX prod, cons;
	काष्ठा sk_buff *skb;
	पूर्णांक needed;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->rx_queue.lock, flags);

	skb = skb_peek(&queue->rx_queue);
	अगर (!skb) अणु
		spin_unlock_irqrestore(&queue->rx_queue.lock, flags);
		वापस false;
	पूर्ण

	needed = DIV_ROUND_UP(skb->len, XEN_PAGE_SIZE);
	अगर (skb_is_gso(skb))
		needed++;
	अगर (skb->sw_hash)
		needed++;

	spin_unlock_irqrestore(&queue->rx_queue.lock, flags);

	करो अणु
		prod = queue->rx.sring->req_prod;
		cons = queue->rx.req_cons;

		अगर (prod - cons >= needed)
			वापस true;

		queue->rx.sring->req_event = prod + 1;

		/* Make sure event is visible beक्रमe we check prod
		 * again.
		 */
		mb();
	पूर्ण जबतक (queue->rx.sring->req_prod != prod);

	वापस false;
पूर्ण

व्योम xenvअगर_rx_queue_tail(काष्ठा xenvअगर_queue *queue, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->rx_queue.lock, flags);

	__skb_queue_tail(&queue->rx_queue, skb);

	queue->rx_queue_len += skb->len;
	अगर (queue->rx_queue_len > queue->rx_queue_max) अणु
		काष्ठा net_device *dev = queue->vअगर->dev;

		netअगर_tx_stop_queue(netdev_get_tx_queue(dev, queue->id));
	पूर्ण

	spin_unlock_irqrestore(&queue->rx_queue.lock, flags);
पूर्ण

अटल काष्ठा sk_buff *xenvअगर_rx_dequeue(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा sk_buff *skb;

	spin_lock_irq(&queue->rx_queue.lock);

	skb = __skb_dequeue(&queue->rx_queue);
	अगर (skb) अणु
		queue->rx_queue_len -= skb->len;
		अगर (queue->rx_queue_len < queue->rx_queue_max) अणु
			काष्ठा netdev_queue *txq;

			txq = netdev_get_tx_queue(queue->vअगर->dev, queue->id);
			netअगर_tx_wake_queue(txq);
		पूर्ण
	पूर्ण

	spin_unlock_irq(&queue->rx_queue.lock);

	वापस skb;
पूर्ण

अटल व्योम xenvअगर_rx_queue_purge(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = xenvअगर_rx_dequeue(queue)) != शून्य)
		kमुक्त_skb(skb);
पूर्ण

अटल व्योम xenvअगर_rx_queue_drop_expired(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा sk_buff *skb;

	क्रम (;;) अणु
		skb = skb_peek(&queue->rx_queue);
		अगर (!skb)
			अवरोध;
		अगर (समय_beक्रमe(jअगरfies, XENVIF_RX_CB(skb)->expires))
			अवरोध;
		xenvअगर_rx_dequeue(queue);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम xenvअगर_rx_copy_flush(काष्ठा xenvअगर_queue *queue)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक notअगरy;

	gnttab_batch_copy(queue->rx_copy.op, queue->rx_copy.num);

	क्रम (i = 0; i < queue->rx_copy.num; i++) अणु
		काष्ठा gnttab_copy *op;

		op = &queue->rx_copy.op[i];

		/* If the copy failed, overग_लिखो the status field in
		 * the corresponding response.
		 */
		अगर (unlikely(op->status != GNTST_okay)) अणु
			काष्ठा xen_netअगर_rx_response *rsp;

			rsp = RING_GET_RESPONSE(&queue->rx,
						queue->rx_copy.idx[i]);
			rsp->status = op->status;
		पूर्ण
	पूर्ण

	queue->rx_copy.num = 0;

	/* Push responses क्रम all completed packets. */
	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&queue->rx, notअगरy);
	अगर (notअगरy)
		notअगरy_remote_via_irq(queue->rx_irq);

	__skb_queue_purge(queue->rx_copy.completed);
पूर्ण

अटल व्योम xenvअगर_rx_copy_add(काष्ठा xenvअगर_queue *queue,
			       काष्ठा xen_netअगर_rx_request *req,
			       अचिन्हित पूर्णांक offset, व्योम *data, माप_प्रकार len)
अणु
	काष्ठा gnttab_copy *op;
	काष्ठा page *page;
	काष्ठा xen_page_क्रमeign *क्रमeign;

	अगर (queue->rx_copy.num == COPY_BATCH_SIZE)
		xenvअगर_rx_copy_flush(queue);

	op = &queue->rx_copy.op[queue->rx_copy.num];

	page = virt_to_page(data);

	op->flags = GNTCOPY_dest_gref;

	क्रमeign = xen_page_क्रमeign(page);
	अगर (क्रमeign) अणु
		op->source.करोmid = क्रमeign->करोmid;
		op->source.u.ref = क्रमeign->gref;
		op->flags |= GNTCOPY_source_gref;
	पूर्ण अन्यथा अणु
		op->source.u.gmfn = virt_to_gfn(data);
		op->source.करोmid  = DOMID_SELF;
	पूर्ण

	op->source.offset = xen_offset_in_page(data);
	op->dest.u.ref    = req->gref;
	op->dest.करोmid    = queue->vअगर->करोmid;
	op->dest.offset   = offset;
	op->len           = len;

	queue->rx_copy.idx[queue->rx_copy.num] = queue->rx.req_cons;
	queue->rx_copy.num++;
पूर्ण

अटल अचिन्हित पूर्णांक xenvअगर_gso_type(काष्ठा sk_buff *skb)
अणु
	अगर (skb_is_gso(skb)) अणु
		अगर (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4)
			वापस XEN_NETIF_GSO_TYPE_TCPV4;
		अन्यथा
			वापस XEN_NETIF_GSO_TYPE_TCPV6;
	पूर्ण
	वापस XEN_NETIF_GSO_TYPE_NONE;
पूर्ण

काष्ठा xenvअगर_pkt_state अणु
	काष्ठा sk_buff *skb;
	माप_प्रकार reमुख्यing_len;
	काष्ठा sk_buff *frag_iter;
	पूर्णांक frag; /* frag == -1 => frag_iter->head */
	अचिन्हित पूर्णांक frag_offset;
	काष्ठा xen_netअगर_extra_info extras[XEN_NETIF_EXTRA_TYPE_MAX - 1];
	अचिन्हित पूर्णांक extra_count;
	अचिन्हित पूर्णांक slot;
पूर्ण;

अटल व्योम xenvअगर_rx_next_skb(काष्ठा xenvअगर_queue *queue,
			       काष्ठा xenvअगर_pkt_state *pkt)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक gso_type;

	skb = xenvअगर_rx_dequeue(queue);

	queue->stats.tx_bytes += skb->len;
	queue->stats.tx_packets++;

	/* Reset packet state. */
	स_रखो(pkt, 0, माप(काष्ठा xenvअगर_pkt_state));

	pkt->skb = skb;
	pkt->frag_iter = skb;
	pkt->reमुख्यing_len = skb->len;
	pkt->frag = -1;

	gso_type = xenvअगर_gso_type(skb);
	अगर ((1 << gso_type) & queue->vअगर->gso_mask) अणु
		काष्ठा xen_netअगर_extra_info *extra;

		extra = &pkt->extras[XEN_NETIF_EXTRA_TYPE_GSO - 1];

		extra->u.gso.type = gso_type;
		extra->u.gso.size = skb_shinfo(skb)->gso_size;
		extra->u.gso.pad = 0;
		extra->u.gso.features = 0;
		extra->type = XEN_NETIF_EXTRA_TYPE_GSO;
		extra->flags = 0;

		pkt->extra_count++;
	पूर्ण

	अगर (queue->vअगर->xdp_headroom) अणु
		काष्ठा xen_netअगर_extra_info *extra;

		extra = &pkt->extras[XEN_NETIF_EXTRA_TYPE_XDP - 1];

		स_रखो(extra, 0, माप(काष्ठा xen_netअगर_extra_info));
		extra->u.xdp.headroom = queue->vअगर->xdp_headroom;
		extra->type = XEN_NETIF_EXTRA_TYPE_XDP;
		extra->flags = 0;

		pkt->extra_count++;
	पूर्ण

	अगर (skb->sw_hash) अणु
		काष्ठा xen_netअगर_extra_info *extra;

		extra = &pkt->extras[XEN_NETIF_EXTRA_TYPE_HASH - 1];

		extra->u.hash.algorithm =
			XEN_NETIF_CTRL_HASH_ALGORITHM_TOEPLITZ;

		अगर (skb->l4_hash)
			extra->u.hash.type =
				skb->protocol == htons(ETH_P_IP) ?
				_XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP :
				_XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP;
		अन्यथा
			extra->u.hash.type =
				skb->protocol == htons(ETH_P_IP) ?
				_XEN_NETIF_CTRL_HASH_TYPE_IPV4 :
				_XEN_NETIF_CTRL_HASH_TYPE_IPV6;

		*(uपूर्णांक32_t *)extra->u.hash.value = skb_get_hash_raw(skb);

		extra->type = XEN_NETIF_EXTRA_TYPE_HASH;
		extra->flags = 0;

		pkt->extra_count++;
	पूर्ण
पूर्ण

अटल व्योम xenvअगर_rx_complete(काष्ठा xenvअगर_queue *queue,
			       काष्ठा xenvअगर_pkt_state *pkt)
अणु
	/* All responses are पढ़ोy to be pushed. */
	queue->rx.rsp_prod_pvt = queue->rx.req_cons;

	__skb_queue_tail(queue->rx_copy.completed, pkt->skb);
पूर्ण

अटल व्योम xenvअगर_rx_next_frag(काष्ठा xenvअगर_pkt_state *pkt)
अणु
	काष्ठा sk_buff *frag_iter = pkt->frag_iter;
	अचिन्हित पूर्णांक nr_frags = skb_shinfo(frag_iter)->nr_frags;

	pkt->frag++;
	pkt->frag_offset = 0;

	अगर (pkt->frag >= nr_frags) अणु
		अगर (frag_iter == pkt->skb)
			pkt->frag_iter = skb_shinfo(frag_iter)->frag_list;
		अन्यथा
			pkt->frag_iter = frag_iter->next;

		pkt->frag = -1;
	पूर्ण
पूर्ण

अटल व्योम xenvअगर_rx_next_chunk(काष्ठा xenvअगर_queue *queue,
				 काष्ठा xenvअगर_pkt_state *pkt,
				 अचिन्हित पूर्णांक offset, व्योम **data,
				 माप_प्रकार *len)
अणु
	काष्ठा sk_buff *frag_iter = pkt->frag_iter;
	व्योम *frag_data;
	माप_प्रकार frag_len, chunk_len;

	BUG_ON(!frag_iter);

	अगर (pkt->frag == -1) अणु
		frag_data = frag_iter->data;
		frag_len = skb_headlen(frag_iter);
	पूर्ण अन्यथा अणु
		skb_frag_t *frag = &skb_shinfo(frag_iter)->frags[pkt->frag];

		frag_data = skb_frag_address(frag);
		frag_len = skb_frag_size(frag);
	पूर्ण

	frag_data += pkt->frag_offset;
	frag_len -= pkt->frag_offset;

	chunk_len = min_t(माप_प्रकार, frag_len, XEN_PAGE_SIZE - offset);
	chunk_len = min_t(माप_प्रकार, chunk_len, XEN_PAGE_SIZE -
					     xen_offset_in_page(frag_data));

	pkt->frag_offset += chunk_len;

	/* Advance to next frag? */
	अगर (frag_len == chunk_len)
		xenvअगर_rx_next_frag(pkt);

	*data = frag_data;
	*len = chunk_len;
पूर्ण

अटल व्योम xenvअगर_rx_data_slot(काष्ठा xenvअगर_queue *queue,
				काष्ठा xenvअगर_pkt_state *pkt,
				काष्ठा xen_netअगर_rx_request *req,
				काष्ठा xen_netअगर_rx_response *rsp)
अणु
	अचिन्हित पूर्णांक offset = queue->vअगर->xdp_headroom;
	अचिन्हित पूर्णांक flags;

	करो अणु
		माप_प्रकार len;
		व्योम *data;

		xenvअगर_rx_next_chunk(queue, pkt, offset, &data, &len);
		xenvअगर_rx_copy_add(queue, req, offset, data, len);

		offset += len;
		pkt->reमुख्यing_len -= len;

	पूर्ण जबतक (offset < XEN_PAGE_SIZE && pkt->reमुख्यing_len > 0);

	अगर (pkt->reमुख्यing_len > 0)
		flags = XEN_NETRXF_more_data;
	अन्यथा
		flags = 0;

	अगर (pkt->slot == 0) अणु
		काष्ठा sk_buff *skb = pkt->skb;

		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			flags |= XEN_NETRXF_csum_blank |
				 XEN_NETRXF_data_validated;
		अन्यथा अगर (skb->ip_summed == CHECKSUM_UNNECESSARY)
			flags |= XEN_NETRXF_data_validated;

		अगर (pkt->extra_count != 0)
			flags |= XEN_NETRXF_extra_info;
	पूर्ण

	rsp->offset = 0;
	rsp->flags = flags;
	rsp->id = req->id;
	rsp->status = (s16)offset;
पूर्ण

अटल व्योम xenvअगर_rx_extra_slot(काष्ठा xenvअगर_queue *queue,
				 काष्ठा xenvअगर_pkt_state *pkt,
				 काष्ठा xen_netअगर_rx_request *req,
				 काष्ठा xen_netअगर_rx_response *rsp)
अणु
	काष्ठा xen_netअगर_extra_info *extra = (व्योम *)rsp;
	अचिन्हित पूर्णांक i;

	pkt->extra_count--;

	क्रम (i = 0; i < ARRAY_SIZE(pkt->extras); i++) अणु
		अगर (pkt->extras[i].type) अणु
			*extra = pkt->extras[i];

			अगर (pkt->extra_count != 0)
				extra->flags |= XEN_NETIF_EXTRA_FLAG_MORE;

			pkt->extras[i].type = 0;
			वापस;
		पूर्ण
	पूर्ण
	BUG();
पूर्ण

अटल व्योम xenvअगर_rx_skb(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा xenvअगर_pkt_state pkt;

	xenvअगर_rx_next_skb(queue, &pkt);

	queue->last_rx_समय = jअगरfies;

	करो अणु
		काष्ठा xen_netअगर_rx_request *req;
		काष्ठा xen_netअगर_rx_response *rsp;

		req = RING_GET_REQUEST(&queue->rx, queue->rx.req_cons);
		rsp = RING_GET_RESPONSE(&queue->rx, queue->rx.req_cons);

		/* Extras must go after the first data slot */
		अगर (pkt.slot != 0 && pkt.extra_count != 0)
			xenvअगर_rx_extra_slot(queue, &pkt, req, rsp);
		अन्यथा
			xenvअगर_rx_data_slot(queue, &pkt, req, rsp);

		queue->rx.req_cons++;
		pkt.slot++;
	पूर्ण जबतक (pkt.reमुख्यing_len > 0 || pkt.extra_count != 0);

	xenvअगर_rx_complete(queue, &pkt);
पूर्ण

#घोषणा RX_BATCH_SIZE 64

व्योम xenvअगर_rx_action(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा sk_buff_head completed_skbs;
	अचिन्हित पूर्णांक work_करोne = 0;

	__skb_queue_head_init(&completed_skbs);
	queue->rx_copy.completed = &completed_skbs;

	जबतक (xenvअगर_rx_ring_slots_available(queue) &&
	       work_करोne < RX_BATCH_SIZE) अणु
		xenvअगर_rx_skb(queue);
		work_करोne++;
	पूर्ण

	/* Flush any pending copies and complete all skbs. */
	xenvअगर_rx_copy_flush(queue);
पूर्ण

अटल bool xenvअगर_rx_queue_stalled(काष्ठा xenvअगर_queue *queue)
अणु
	RING_IDX prod, cons;

	prod = queue->rx.sring->req_prod;
	cons = queue->rx.req_cons;

	वापस !queue->stalled &&
		prod - cons < 1 &&
		समय_after(jअगरfies,
			   queue->last_rx_समय + queue->vअगर->stall_समयout);
पूर्ण

अटल bool xenvअगर_rx_queue_पढ़ोy(काष्ठा xenvअगर_queue *queue)
अणु
	RING_IDX prod, cons;

	prod = queue->rx.sring->req_prod;
	cons = queue->rx.req_cons;

	वापस queue->stalled && prod - cons >= 1;
पूर्ण

bool xenvअगर_have_rx_work(काष्ठा xenvअगर_queue *queue, bool test_kthपढ़ो)
अणु
	वापस xenvअगर_rx_ring_slots_available(queue) ||
		(queue->vअगर->stall_समयout &&
		 (xenvअगर_rx_queue_stalled(queue) ||
		  xenvअगर_rx_queue_पढ़ोy(queue))) ||
		(test_kthपढ़ो && kthपढ़ो_should_stop()) ||
		queue->vअगर->disabled;
पूर्ण

अटल दीर्घ xenvअगर_rx_queue_समयout(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा sk_buff *skb;
	दीर्घ समयout;

	skb = skb_peek(&queue->rx_queue);
	अगर (!skb)
		वापस MAX_SCHEDULE_TIMEOUT;

	समयout = XENVIF_RX_CB(skb)->expires - jअगरfies;
	वापस समयout < 0 ? 0 : समयout;
पूर्ण

/* Wait until the guest Rx thपढ़ो has work.
 *
 * The समयout needs to be adjusted based on the current head of the
 * queue (and not just the head at the beginning).  In particular, अगर
 * the queue is initially empty an infinite समयout is used and this
 * needs to be reduced when a skb is queued.
 *
 * This cannot be करोne with रुको_event_समयout() because it only
 * calculates the समयout once.
 */
अटल व्योम xenvअगर_रुको_क्रम_rx_work(काष्ठा xenvअगर_queue *queue)
अणु
	DEFINE_WAIT(रुको);

	अगर (xenvअगर_have_rx_work(queue, true))
		वापस;

	क्रम (;;) अणु
		दीर्घ ret;

		prepare_to_रुको(&queue->wq, &रुको, TASK_INTERRUPTIBLE);
		अगर (xenvअगर_have_rx_work(queue, true))
			अवरोध;
		अगर (atomic_fetch_andnot(NETBK_RX_EOI | NETBK_COMMON_EOI,
					&queue->eoi_pending) &
		    (NETBK_RX_EOI | NETBK_COMMON_EOI))
			xen_irq_lateeoi(queue->rx_irq, 0);

		ret = schedule_समयout(xenvअगर_rx_queue_समयout(queue));
		अगर (!ret)
			अवरोध;
	पूर्ण
	finish_रुको(&queue->wq, &रुको);
पूर्ण

अटल व्योम xenvअगर_queue_carrier_off(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा xenvअगर *vअगर = queue->vअगर;

	queue->stalled = true;

	/* At least one queue has stalled? Disable the carrier. */
	spin_lock(&vअगर->lock);
	अगर (vअगर->stalled_queues++ == 0) अणु
		netdev_info(vअगर->dev, "Guest Rx stalled");
		netअगर_carrier_off(vअगर->dev);
	पूर्ण
	spin_unlock(&vअगर->lock);
पूर्ण

अटल व्योम xenvअगर_queue_carrier_on(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा xenvअगर *vअगर = queue->vअगर;

	queue->last_rx_समय = jअगरfies; /* Reset Rx stall detection. */
	queue->stalled = false;

	/* All queues are पढ़ोy? Enable the carrier. */
	spin_lock(&vअगर->lock);
	अगर (--vअगर->stalled_queues == 0) अणु
		netdev_info(vअगर->dev, "Guest Rx ready");
		netअगर_carrier_on(vअगर->dev);
	पूर्ण
	spin_unlock(&vअगर->lock);
पूर्ण

पूर्णांक xenvअगर_kthपढ़ो_guest_rx(व्योम *data)
अणु
	काष्ठा xenvअगर_queue *queue = data;
	काष्ठा xenvअगर *vअगर = queue->vअगर;

	अगर (!vअगर->stall_समयout)
		xenvअगर_queue_carrier_on(queue);

	क्रम (;;) अणु
		xenvअगर_रुको_क्रम_rx_work(queue);

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/* This frontend is found to be rogue, disable it in
		 * kthपढ़ो context. Currently this is only set when
		 * netback finds out frontend sends malक्रमmed packet,
		 * but we cannot disable the पूर्णांकerface in softirq
		 * context so we defer it here, अगर this thपढ़ो is
		 * associated with queue 0.
		 */
		अगर (unlikely(vअगर->disabled && queue->id == 0)) अणु
			xenvअगर_carrier_off(vअगर);
			अवरोध;
		पूर्ण

		अगर (!skb_queue_empty(&queue->rx_queue))
			xenvअगर_rx_action(queue);

		/* If the guest hasn't provided any Rx slots क्रम a
		 * जबतक it's probably not responsive, drop the
		 * carrier so packets are dropped earlier.
		 */
		अगर (vअगर->stall_समयout) अणु
			अगर (xenvअगर_rx_queue_stalled(queue))
				xenvअगर_queue_carrier_off(queue);
			अन्यथा अगर (xenvअगर_rx_queue_पढ़ोy(queue))
				xenvअगर_queue_carrier_on(queue);
		पूर्ण

		/* Queued packets may have क्रमeign pages from other
		 * करोमुख्यs.  These cannot be queued indefinitely as
		 * this would starve guests of grant refs and transmit
		 * slots.
		 */
		xenvअगर_rx_queue_drop_expired(queue);

		cond_resched();
	पूर्ण

	/* Bin any reमुख्यing skbs */
	xenvअगर_rx_queue_purge(queue);

	वापस 0;
पूर्ण
