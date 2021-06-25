<शैली गुरु>
/*
 * Back-end of the driver क्रम भव network devices. This portion of the
 * driver exports a 'unified' network-device पूर्णांकerface that can be accessed
 * by any operating प्रणाली that implements a compatible front end. A
 * reference front-end implementation can be found in:
 *  drivers/net/xen-netfront.c
 *
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
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/udp.h>
#समावेश <linux/highस्मृति.स>

#समावेश <net/tcp.h>

#समावेश <xen/xen.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/page.h>

#समावेश <यंत्र/xen/hypercall.h>

/* Provide an option to disable split event channels at load समय as
 * event channels are limited resource. Split event channels are
 * enabled by शेष.
 */
bool separate_tx_rx_irq = true;
module_param(separate_tx_rx_irq, bool, 0644);

/* The समय that packets can stay on the guest Rx पूर्णांकernal queue
 * beक्रमe they are dropped.
 */
अचिन्हित पूर्णांक rx_drain_समयout_msecs = 10000;
module_param(rx_drain_समयout_msecs, uपूर्णांक, 0444);

/* The length of समय beक्रमe the frontend is considered unresponsive
 * because it isn't providing Rx slots.
 */
अचिन्हित पूर्णांक rx_stall_समयout_msecs = 60000;
module_param(rx_stall_समयout_msecs, uपूर्णांक, 0444);

#घोषणा MAX_QUEUES_DEFAULT 8
अचिन्हित पूर्णांक xenvअगर_max_queues;
module_param_named(max_queues, xenvअगर_max_queues, uपूर्णांक, 0644);
MODULE_PARM_DESC(max_queues,
		 "Maximum number of queues per virtual interface");

/*
 * This is the maximum slots a skb can have. If a guest sends a skb
 * which exceeds this limit it is considered malicious.
 */
#घोषणा FATAL_SKB_SLOTS_DEFAULT 20
अटल अचिन्हित पूर्णांक fatal_skb_slots = FATAL_SKB_SLOTS_DEFAULT;
module_param(fatal_skb_slots, uपूर्णांक, 0444);

/* The amount to copy out of the first guest Tx slot पूर्णांकo the skb's
 * linear area.  If the first slot has more data, it will be mapped
 * and put पूर्णांकo the first frag.
 *
 * This is sized to aव्योम pulling headers from the frags क्रम most
 * TCP/IP packets.
 */
#घोषणा XEN_NETBACK_TX_COPY_LEN 128

/* This is the maximum number of flows in the hash cache. */
#घोषणा XENVIF_HASH_CACHE_SIZE_DEFAULT 64
अचिन्हित पूर्णांक xenvअगर_hash_cache_size = XENVIF_HASH_CACHE_SIZE_DEFAULT;
module_param_named(hash_cache_size, xenvअगर_hash_cache_size, uपूर्णांक, 0644);
MODULE_PARM_DESC(hash_cache_size, "Number of flows in the hash cache");

/* The module parameter tells that we have to put data
 * क्रम xen-netfront with the XDP_PACKET_HEADROOM offset
 * needed क्रम XDP processing
 */
bool provides_xdp_headroom = true;
module_param(provides_xdp_headroom, bool, 0644);

अटल व्योम xenvअगर_idx_release(काष्ठा xenvअगर_queue *queue, u16 pending_idx,
			       u8 status);

अटल व्योम make_tx_response(काष्ठा xenvअगर_queue *queue,
			     काष्ठा xen_netअगर_tx_request *txp,
			     अचिन्हित पूर्णांक extra_count,
			     s8       st);
अटल व्योम push_tx_responses(काष्ठा xenvअगर_queue *queue);

अटल अंतरभूत पूर्णांक tx_work_toकरो(काष्ठा xenvअगर_queue *queue);

अटल अंतरभूत अचिन्हित दीर्घ idx_to_pfn(काष्ठा xenvअगर_queue *queue,
				       u16 idx)
अणु
	वापस page_to_pfn(queue->mmap_pages[idx]);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ idx_to_kaddr(काष्ठा xenvअगर_queue *queue,
					 u16 idx)
अणु
	वापस (अचिन्हित दीर्घ)pfn_to_kaddr(idx_to_pfn(queue, idx));
पूर्ण

#घोषणा callback_param(vअगर, pending_idx) \
	(vअगर->pending_tx_info[pending_idx].callback_काष्ठा)

/* Find the containing VIF's काष्ठाure from a poपूर्णांकer in pending_tx_info array
 */
अटल अंतरभूत काष्ठा xenvअगर_queue *ubuf_to_queue(स्थिर काष्ठा ubuf_info *ubuf)
अणु
	u16 pending_idx = ubuf->desc;
	काष्ठा pending_tx_info *temp =
		container_of(ubuf, काष्ठा pending_tx_info, callback_काष्ठा);
	वापस container_of(temp - pending_idx,
			    काष्ठा xenvअगर_queue,
			    pending_tx_info[0]);
पूर्ण

अटल u16 frag_get_pending_idx(skb_frag_t *frag)
अणु
	वापस (u16)skb_frag_off(frag);
पूर्ण

अटल व्योम frag_set_pending_idx(skb_frag_t *frag, u16 pending_idx)
अणु
	skb_frag_off_set(frag, pending_idx);
पूर्ण

अटल अंतरभूत pending_ring_idx_t pending_index(अचिन्हित i)
अणु
	वापस i & (MAX_PENDING_REQS-1);
पूर्ण

व्योम xenvअगर_kick_thपढ़ो(काष्ठा xenvअगर_queue *queue)
अणु
	wake_up(&queue->wq);
पूर्ण

व्योम xenvअगर_napi_schedule_or_enable_events(काष्ठा xenvअगर_queue *queue)
अणु
	पूर्णांक more_to_करो;

	RING_FINAL_CHECK_FOR_REQUESTS(&queue->tx, more_to_करो);

	अगर (more_to_करो)
		napi_schedule(&queue->napi);
	अन्यथा अगर (atomic_fetch_andnot(NETBK_TX_EOI | NETBK_COMMON_EOI,
				     &queue->eoi_pending) &
		 (NETBK_TX_EOI | NETBK_COMMON_EOI))
		xen_irq_lateeoi(queue->tx_irq, 0);
पूर्ण

अटल व्योम tx_add_credit(काष्ठा xenvअगर_queue *queue)
अणु
	अचिन्हित दीर्घ max_burst, max_credit;

	/*
	 * Allow a burst big enough to transmit a jumbo packet of up to 128kB.
	 * Otherwise the पूर्णांकerface can seize up due to insufficient credit.
	 */
	max_burst = max(131072UL, queue->credit_bytes);

	/* Take care that adding a new chunk of credit करोesn't wrap to zero. */
	max_credit = queue->reमुख्यing_credit + queue->credit_bytes;
	अगर (max_credit < queue->reमुख्यing_credit)
		max_credit = अच_दीर्घ_उच्च; /* wrapped: clamp to अच_दीर्घ_उच्च */

	queue->reमुख्यing_credit = min(max_credit, max_burst);
	queue->rate_limited = false;
पूर्ण

व्योम xenvअगर_tx_credit_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा xenvअगर_queue *queue = from_समयr(queue, t, credit_समयout);
	tx_add_credit(queue);
	xenvअगर_napi_schedule_or_enable_events(queue);
पूर्ण

अटल व्योम xenvअगर_tx_err(काष्ठा xenvअगर_queue *queue,
			  काष्ठा xen_netअगर_tx_request *txp,
			  अचिन्हित पूर्णांक extra_count, RING_IDX end)
अणु
	RING_IDX cons = queue->tx.req_cons;
	अचिन्हित दीर्घ flags;

	करो अणु
		spin_lock_irqsave(&queue->response_lock, flags);
		make_tx_response(queue, txp, extra_count, XEN_NETIF_RSP_ERROR);
		push_tx_responses(queue);
		spin_unlock_irqrestore(&queue->response_lock, flags);
		अगर (cons == end)
			अवरोध;
		RING_COPY_REQUEST(&queue->tx, cons++, txp);
		extra_count = 0; /* only the first frag can have extras */
	पूर्ण जबतक (1);
	queue->tx.req_cons = cons;
पूर्ण

अटल व्योम xenvअगर_fatal_tx_err(काष्ठा xenvअगर *vअगर)
अणु
	netdev_err(vअगर->dev, "fatal error; disabling device\n");
	vअगर->disabled = true;
	/* Disable the vअगर from queue 0's kthपढ़ो */
	अगर (vअगर->num_queues)
		xenvअगर_kick_thपढ़ो(&vअगर->queues[0]);
पूर्ण

अटल पूर्णांक xenvअगर_count_requests(काष्ठा xenvअगर_queue *queue,
				 काष्ठा xen_netअगर_tx_request *first,
				 अचिन्हित पूर्णांक extra_count,
				 काष्ठा xen_netअगर_tx_request *txp,
				 पूर्णांक work_to_करो)
अणु
	RING_IDX cons = queue->tx.req_cons;
	पूर्णांक slots = 0;
	पूर्णांक drop_err = 0;
	पूर्णांक more_data;

	अगर (!(first->flags & XEN_NETTXF_more_data))
		वापस 0;

	करो अणु
		काष्ठा xen_netअगर_tx_request dropped_tx = अणु 0 पूर्ण;

		अगर (slots >= work_to_करो) अणु
			netdev_err(queue->vअगर->dev,
				   "Asked for %d slots but exceeds this limit\n",
				   work_to_करो);
			xenvअगर_fatal_tx_err(queue->vअगर);
			वापस -ENODATA;
		पूर्ण

		/* This guest is really using too many slots and
		 * considered malicious.
		 */
		अगर (unlikely(slots >= fatal_skb_slots)) अणु
			netdev_err(queue->vअगर->dev,
				   "Malicious frontend using %d slots, threshold %u\n",
				   slots, fatal_skb_slots);
			xenvअगर_fatal_tx_err(queue->vअगर);
			वापस -E2BIG;
		पूर्ण

		/* Xen network protocol had implicit dependency on
		 * MAX_SKB_FRAGS. XEN_NETBK_LEGACY_SLOTS_MAX is set to
		 * the historical MAX_SKB_FRAGS value 18 to honor the
		 * same behavior as beक्रमe. Any packet using more than
		 * 18 slots but less than fatal_skb_slots slots is
		 * dropped
		 */
		अगर (!drop_err && slots >= XEN_NETBK_LEGACY_SLOTS_MAX) अणु
			अगर (net_ratelimit())
				netdev_dbg(queue->vअगर->dev,
					   "Too many slots (%d) exceeding limit (%d), dropping packet\n",
					   slots, XEN_NETBK_LEGACY_SLOTS_MAX);
			drop_err = -E2BIG;
		पूर्ण

		अगर (drop_err)
			txp = &dropped_tx;

		RING_COPY_REQUEST(&queue->tx, cons + slots, txp);

		/* If the guest submitted a frame >= 64 KiB then
		 * first->size overflowed and following slots will
		 * appear to be larger than the frame.
		 *
		 * This cannot be fatal error as there are buggy
		 * frontends that करो this.
		 *
		 * Consume all slots and drop the packet.
		 */
		अगर (!drop_err && txp->size > first->size) अणु
			अगर (net_ratelimit())
				netdev_dbg(queue->vअगर->dev,
					   "Invalid tx request, slot size %u > remaining size %u\n",
					   txp->size, first->size);
			drop_err = -EIO;
		पूर्ण

		first->size -= txp->size;
		slots++;

		अगर (unlikely((txp->offset + txp->size) > XEN_PAGE_SIZE)) अणु
			netdev_err(queue->vअगर->dev, "Cross page boundary, txp->offset: %u, size: %u\n",
				 txp->offset, txp->size);
			xenvअगर_fatal_tx_err(queue->vअगर);
			वापस -EINVAL;
		पूर्ण

		more_data = txp->flags & XEN_NETTXF_more_data;

		अगर (!drop_err)
			txp++;

	पूर्ण जबतक (more_data);

	अगर (drop_err) अणु
		xenvअगर_tx_err(queue, first, extra_count, cons + slots);
		वापस drop_err;
	पूर्ण

	वापस slots;
पूर्ण


काष्ठा xenvअगर_tx_cb अणु
	u16 pending_idx;
पूर्ण;

#घोषणा XENVIF_TX_CB(skb) ((काष्ठा xenvअगर_tx_cb *)(skb)->cb)

अटल अंतरभूत व्योम xenvअगर_tx_create_map_op(काष्ठा xenvअगर_queue *queue,
					   u16 pending_idx,
					   काष्ठा xen_netअगर_tx_request *txp,
					   अचिन्हित पूर्णांक extra_count,
					   काष्ठा gnttab_map_grant_ref *mop)
अणु
	queue->pages_to_map[mop-queue->tx_map_ops] = queue->mmap_pages[pending_idx];
	gnttab_set_map_op(mop, idx_to_kaddr(queue, pending_idx),
			  GNTMAP_host_map | GNTMAP_पढ़ोonly,
			  txp->gref, queue->vअगर->करोmid);

	स_नकल(&queue->pending_tx_info[pending_idx].req, txp,
	       माप(*txp));
	queue->pending_tx_info[pending_idx].extra_count = extra_count;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *xenvअगर_alloc_skb(अचिन्हित पूर्णांक size)
अणु
	काष्ठा sk_buff *skb =
		alloc_skb(size + NET_SKB_PAD + NET_IP_ALIGN,
			  GFP_ATOMIC | __GFP_NOWARN);
	अगर (unlikely(skb == शून्य))
		वापस शून्य;

	/* Packets passed to netअगर_rx() must have some headroom. */
	skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN);

	/* Initialize it here to aव्योम later surprises */
	skb_shinfo(skb)->deकाष्ठाor_arg = शून्य;

	वापस skb;
पूर्ण

अटल काष्ठा gnttab_map_grant_ref *xenvअगर_get_requests(काष्ठा xenvअगर_queue *queue,
							काष्ठा sk_buff *skb,
							काष्ठा xen_netअगर_tx_request *txp,
							काष्ठा gnttab_map_grant_ref *gop,
							अचिन्हित पूर्णांक frag_overflow,
							काष्ठा sk_buff *nskb)
अणु
	काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	skb_frag_t *frags = shinfo->frags;
	u16 pending_idx = XENVIF_TX_CB(skb)->pending_idx;
	पूर्णांक start;
	pending_ring_idx_t index;
	अचिन्हित पूर्णांक nr_slots;

	nr_slots = shinfo->nr_frags;

	/* Skip first skb fragment अगर it is on same page as header fragment. */
	start = (frag_get_pending_idx(&shinfo->frags[0]) == pending_idx);

	क्रम (shinfo->nr_frags = start; shinfo->nr_frags < nr_slots;
	     shinfo->nr_frags++, txp++, gop++) अणु
		index = pending_index(queue->pending_cons++);
		pending_idx = queue->pending_ring[index];
		xenvअगर_tx_create_map_op(queue, pending_idx, txp, 0, gop);
		frag_set_pending_idx(&frags[shinfo->nr_frags], pending_idx);
	पूर्ण

	अगर (frag_overflow) अणु

		shinfo = skb_shinfo(nskb);
		frags = shinfo->frags;

		क्रम (shinfo->nr_frags = 0; shinfo->nr_frags < frag_overflow;
		     shinfo->nr_frags++, txp++, gop++) अणु
			index = pending_index(queue->pending_cons++);
			pending_idx = queue->pending_ring[index];
			xenvअगर_tx_create_map_op(queue, pending_idx, txp, 0,
						gop);
			frag_set_pending_idx(&frags[shinfo->nr_frags],
					     pending_idx);
		पूर्ण

		skb_shinfo(skb)->frag_list = nskb;
	पूर्ण

	वापस gop;
पूर्ण

अटल अंतरभूत व्योम xenvअगर_grant_handle_set(काष्ठा xenvअगर_queue *queue,
					   u16 pending_idx,
					   grant_handle_t handle)
अणु
	अगर (unlikely(queue->grant_tx_handle[pending_idx] !=
		     NETBACK_INVALID_HANDLE)) अणु
		netdev_err(queue->vअगर->dev,
			   "Trying to overwrite active handle! pending_idx: 0x%x\n",
			   pending_idx);
		BUG();
	पूर्ण
	queue->grant_tx_handle[pending_idx] = handle;
पूर्ण

अटल अंतरभूत व्योम xenvअगर_grant_handle_reset(काष्ठा xenvअगर_queue *queue,
					     u16 pending_idx)
अणु
	अगर (unlikely(queue->grant_tx_handle[pending_idx] ==
		     NETBACK_INVALID_HANDLE)) अणु
		netdev_err(queue->vअगर->dev,
			   "Trying to unmap invalid handle! pending_idx: 0x%x\n",
			   pending_idx);
		BUG();
	पूर्ण
	queue->grant_tx_handle[pending_idx] = NETBACK_INVALID_HANDLE;
पूर्ण

अटल पूर्णांक xenvअगर_tx_check_gop(काष्ठा xenvअगर_queue *queue,
			       काष्ठा sk_buff *skb,
			       काष्ठा gnttab_map_grant_ref **gopp_map,
			       काष्ठा gnttab_copy **gopp_copy)
अणु
	काष्ठा gnttab_map_grant_ref *gop_map = *gopp_map;
	u16 pending_idx = XENVIF_TX_CB(skb)->pending_idx;
	/* This always poपूर्णांकs to the shinfo of the skb being checked, which
	 * could be either the first or the one on the frag_list
	 */
	काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	/* If this is non-शून्य, we are currently checking the frag_list skb, and
	 * this poपूर्णांकs to the shinfo of the first one
	 */
	काष्ठा skb_shared_info *first_shinfo = शून्य;
	पूर्णांक nr_frags = shinfo->nr_frags;
	स्थिर bool sharedslot = nr_frags &&
				frag_get_pending_idx(&shinfo->frags[0]) == pending_idx;
	पूर्णांक i, err;

	/* Check status of header. */
	err = (*gopp_copy)->status;
	अगर (unlikely(err)) अणु
		अगर (net_ratelimit())
			netdev_dbg(queue->vअगर->dev,
				   "Grant copy of header failed! status: %d pending_idx: %u ref: %u\n",
				   (*gopp_copy)->status,
				   pending_idx,
				   (*gopp_copy)->source.u.ref);
		/* The first frag might still have this slot mapped */
		अगर (!sharedslot)
			xenvअगर_idx_release(queue, pending_idx,
					   XEN_NETIF_RSP_ERROR);
	पूर्ण
	(*gopp_copy)++;

check_frags:
	क्रम (i = 0; i < nr_frags; i++, gop_map++) अणु
		पूर्णांक j, newerr;

		pending_idx = frag_get_pending_idx(&shinfo->frags[i]);

		/* Check error status: अगर okay then remember grant handle. */
		newerr = gop_map->status;

		अगर (likely(!newerr)) अणु
			xenvअगर_grant_handle_set(queue,
						pending_idx,
						gop_map->handle);
			/* Had a previous error? Invalidate this fragment. */
			अगर (unlikely(err)) अणु
				xenvअगर_idx_unmap(queue, pending_idx);
				/* If the mapping of the first frag was OK, but
				 * the header's copy failed, and they are
				 * sharing a slot, send an error
				 */
				अगर (i == 0 && sharedslot)
					xenvअगर_idx_release(queue, pending_idx,
							   XEN_NETIF_RSP_ERROR);
				अन्यथा
					xenvअगर_idx_release(queue, pending_idx,
							   XEN_NETIF_RSP_OKAY);
			पूर्ण
			जारी;
		पूर्ण

		/* Error on this fragment: respond to client with an error. */
		अगर (net_ratelimit())
			netdev_dbg(queue->vअगर->dev,
				   "Grant map of %d. frag failed! status: %d pending_idx: %u ref: %u\n",
				   i,
				   gop_map->status,
				   pending_idx,
				   gop_map->ref);

		xenvअगर_idx_release(queue, pending_idx, XEN_NETIF_RSP_ERROR);

		/* Not the first error? Preceding frags alपढ़ोy invalidated. */
		अगर (err)
			जारी;

		/* First error: अगर the header haven't shared a slot with the
		 * first frag, release it as well.
		 */
		अगर (!sharedslot)
			xenvअगर_idx_release(queue,
					   XENVIF_TX_CB(skb)->pending_idx,
					   XEN_NETIF_RSP_OKAY);

		/* Invalidate preceding fragments of this skb. */
		क्रम (j = 0; j < i; j++) अणु
			pending_idx = frag_get_pending_idx(&shinfo->frags[j]);
			xenvअगर_idx_unmap(queue, pending_idx);
			xenvअगर_idx_release(queue, pending_idx,
					   XEN_NETIF_RSP_OKAY);
		पूर्ण

		/* And अगर we found the error जबतक checking the frag_list, unmap
		 * the first skb's frags
		 */
		अगर (first_shinfo) अणु
			क्रम (j = 0; j < first_shinfo->nr_frags; j++) अणु
				pending_idx = frag_get_pending_idx(&first_shinfo->frags[j]);
				xenvअगर_idx_unmap(queue, pending_idx);
				xenvअगर_idx_release(queue, pending_idx,
						   XEN_NETIF_RSP_OKAY);
			पूर्ण
		पूर्ण

		/* Remember the error: invalidate all subsequent fragments. */
		err = newerr;
	पूर्ण

	अगर (skb_has_frag_list(skb) && !first_shinfo) अणु
		first_shinfo = shinfo;
		shinfo = skb_shinfo(shinfo->frag_list);
		nr_frags = shinfo->nr_frags;

		जाओ check_frags;
	पूर्ण

	*gopp_map = gop_map;
	वापस err;
पूर्ण

अटल व्योम xenvअगर_fill_frags(काष्ठा xenvअगर_queue *queue, काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	पूर्णांक nr_frags = shinfo->nr_frags;
	पूर्णांक i;
	u16 prev_pending_idx = INVALID_PENDING_IDX;

	क्रम (i = 0; i < nr_frags; i++) अणु
		skb_frag_t *frag = shinfo->frags + i;
		काष्ठा xen_netअगर_tx_request *txp;
		काष्ठा page *page;
		u16 pending_idx;

		pending_idx = frag_get_pending_idx(frag);

		/* If this is not the first frag, chain it to the previous*/
		अगर (prev_pending_idx == INVALID_PENDING_IDX)
			skb_shinfo(skb)->deकाष्ठाor_arg =
				&callback_param(queue, pending_idx);
		अन्यथा
			callback_param(queue, prev_pending_idx).ctx =
				&callback_param(queue, pending_idx);

		callback_param(queue, pending_idx).ctx = शून्य;
		prev_pending_idx = pending_idx;

		txp = &queue->pending_tx_info[pending_idx].req;
		page = virt_to_page(idx_to_kaddr(queue, pending_idx));
		__skb_fill_page_desc(skb, i, page, txp->offset, txp->size);
		skb->len += txp->size;
		skb->data_len += txp->size;
		skb->truesize += txp->size;

		/* Take an extra reference to offset network stack's put_page */
		get_page(queue->mmap_pages[pending_idx]);
	पूर्ण
पूर्ण

अटल पूर्णांक xenvअगर_get_extras(काष्ठा xenvअगर_queue *queue,
			     काष्ठा xen_netअगर_extra_info *extras,
			     अचिन्हित पूर्णांक *extra_count,
			     पूर्णांक work_to_करो)
अणु
	काष्ठा xen_netअगर_extra_info extra;
	RING_IDX cons = queue->tx.req_cons;

	करो अणु
		अगर (unlikely(work_to_करो-- <= 0)) अणु
			netdev_err(queue->vअगर->dev, "Missing extra info\n");
			xenvअगर_fatal_tx_err(queue->vअगर);
			वापस -EBADR;
		पूर्ण

		RING_COPY_REQUEST(&queue->tx, cons, &extra);

		queue->tx.req_cons = ++cons;
		(*extra_count)++;

		अगर (unlikely(!extra.type ||
			     extra.type >= XEN_NETIF_EXTRA_TYPE_MAX)) अणु
			netdev_err(queue->vअगर->dev,
				   "Invalid extra type: %d\n", extra.type);
			xenvअगर_fatal_tx_err(queue->vअगर);
			वापस -EINVAL;
		पूर्ण

		स_नकल(&extras[extra.type - 1], &extra, माप(extra));
	पूर्ण जबतक (extra.flags & XEN_NETIF_EXTRA_FLAG_MORE);

	वापस work_to_करो;
पूर्ण

अटल पूर्णांक xenvअगर_set_skb_gso(काष्ठा xenvअगर *vअगर,
			      काष्ठा sk_buff *skb,
			      काष्ठा xen_netअगर_extra_info *gso)
अणु
	अगर (!gso->u.gso.size) अणु
		netdev_err(vअगर->dev, "GSO size must not be zero.\n");
		xenvअगर_fatal_tx_err(vअगर);
		वापस -EINVAL;
	पूर्ण

	चयन (gso->u.gso.type) अणु
	हाल XEN_NETIF_GSO_TYPE_TCPV4:
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;
		अवरोध;
	हाल XEN_NETIF_GSO_TYPE_TCPV6:
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
		अवरोध;
	शेष:
		netdev_err(vअगर->dev, "Bad GSO type %d.\n", gso->u.gso.type);
		xenvअगर_fatal_tx_err(vअगर);
		वापस -EINVAL;
	पूर्ण

	skb_shinfo(skb)->gso_size = gso->u.gso.size;
	/* gso_segs will be calculated later */

	वापस 0;
पूर्ण

अटल पूर्णांक checksum_setup(काष्ठा xenvअगर_queue *queue, काष्ठा sk_buff *skb)
अणु
	bool recalculate_partial_csum = false;

	/* A GSO SKB must be CHECKSUM_PARTIAL. However some buggy
	 * peers can fail to set NETRXF_csum_blank when sending a GSO
	 * frame. In this हाल क्रमce the SKB to CHECKSUM_PARTIAL and
	 * recalculate the partial checksum.
	 */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL && skb_is_gso(skb)) अणु
		queue->stats.rx_gso_checksum_fixup++;
		skb->ip_summed = CHECKSUM_PARTIAL;
		recalculate_partial_csum = true;
	पूर्ण

	/* A non-CHECKSUM_PARTIAL SKB करोes not require setup. */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	वापस skb_checksum_setup(skb, recalculate_partial_csum);
पूर्ण

अटल bool tx_credit_exceeded(काष्ठा xenvअगर_queue *queue, अचिन्हित size)
अणु
	u64 now = get_jअगरfies_64();
	u64 next_credit = queue->credit_winकरोw_start +
		msecs_to_jअगरfies(queue->credit_usec / 1000);

	/* Timer could alपढ़ोy be pending in rare हालs. */
	अगर (समयr_pending(&queue->credit_समयout)) अणु
		queue->rate_limited = true;
		वापस true;
	पूर्ण

	/* Passed the poपूर्णांक where we can replenish credit? */
	अगर (समय_after_eq64(now, next_credit)) अणु
		queue->credit_winकरोw_start = now;
		tx_add_credit(queue);
	पूर्ण

	/* Still too big to send right now? Set a callback. */
	अगर (size > queue->reमुख्यing_credit) अणु
		mod_समयr(&queue->credit_समयout,
			  next_credit);
		queue->credit_winकरोw_start = next_credit;
		queue->rate_limited = true;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* No locking is required in xenvअगर_mcast_add/del() as they are
 * only ever invoked from NAPI poll. An RCU list is used because
 * xenvअगर_mcast_match() is called asynchronously, during start_xmit.
 */

अटल पूर्णांक xenvअगर_mcast_add(काष्ठा xenvअगर *vअगर, स्थिर u8 *addr)
अणु
	काष्ठा xenvअगर_mcast_addr *mcast;

	अगर (vअगर->fe_mcast_count == XEN_NETBK_MCAST_MAX) अणु
		अगर (net_ratelimit())
			netdev_err(vअगर->dev,
				   "Too many multicast addresses\n");
		वापस -ENOSPC;
	पूर्ण

	mcast = kzalloc(माप(*mcast), GFP_ATOMIC);
	अगर (!mcast)
		वापस -ENOMEM;

	ether_addr_copy(mcast->addr, addr);
	list_add_tail_rcu(&mcast->entry, &vअगर->fe_mcast_addr);
	vअगर->fe_mcast_count++;

	वापस 0;
पूर्ण

अटल व्योम xenvअगर_mcast_del(काष्ठा xenvअगर *vअगर, स्थिर u8 *addr)
अणु
	काष्ठा xenvअगर_mcast_addr *mcast;

	list_क्रम_each_entry_rcu(mcast, &vअगर->fe_mcast_addr, entry) अणु
		अगर (ether_addr_equal(addr, mcast->addr)) अणु
			--vअगर->fe_mcast_count;
			list_del_rcu(&mcast->entry);
			kमुक्त_rcu(mcast, rcu);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

bool xenvअगर_mcast_match(काष्ठा xenvअगर *vअगर, स्थिर u8 *addr)
अणु
	काष्ठा xenvअगर_mcast_addr *mcast;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(mcast, &vअगर->fe_mcast_addr, entry) अणु
		अगर (ether_addr_equal(addr, mcast->addr)) अणु
			rcu_पढ़ो_unlock();
			वापस true;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस false;
पूर्ण

व्योम xenvअगर_mcast_addr_list_मुक्त(काष्ठा xenvअगर *vअगर)
अणु
	/* No need क्रम locking or RCU here. NAPI poll and TX queue
	 * are stopped.
	 */
	जबतक (!list_empty(&vअगर->fe_mcast_addr)) अणु
		काष्ठा xenvअगर_mcast_addr *mcast;

		mcast = list_first_entry(&vअगर->fe_mcast_addr,
					 काष्ठा xenvअगर_mcast_addr,
					 entry);
		--vअगर->fe_mcast_count;
		list_del(&mcast->entry);
		kमुक्त(mcast);
	पूर्ण
पूर्ण

अटल व्योम xenvअगर_tx_build_gops(काष्ठा xenvअगर_queue *queue,
				     पूर्णांक budget,
				     अचिन्हित *copy_ops,
				     अचिन्हित *map_ops)
अणु
	काष्ठा gnttab_map_grant_ref *gop = queue->tx_map_ops;
	काष्ठा sk_buff *skb, *nskb;
	पूर्णांक ret;
	अचिन्हित पूर्णांक frag_overflow;

	जबतक (skb_queue_len(&queue->tx_queue) < budget) अणु
		काष्ठा xen_netअगर_tx_request txreq;
		काष्ठा xen_netअगर_tx_request txfrags[XEN_NETBK_LEGACY_SLOTS_MAX];
		काष्ठा xen_netअगर_extra_info extras[XEN_NETIF_EXTRA_TYPE_MAX-1];
		अचिन्हित पूर्णांक extra_count;
		u16 pending_idx;
		RING_IDX idx;
		पूर्णांक work_to_करो;
		अचिन्हित पूर्णांक data_len;
		pending_ring_idx_t index;

		अगर (queue->tx.sring->req_prod - queue->tx.req_cons >
		    XEN_NETIF_TX_RING_SIZE) अणु
			netdev_err(queue->vअगर->dev,
				   "Impossible number of requests. "
				   "req_prod %d, req_cons %d, size %ld\n",
				   queue->tx.sring->req_prod, queue->tx.req_cons,
				   XEN_NETIF_TX_RING_SIZE);
			xenvअगर_fatal_tx_err(queue->vअगर);
			अवरोध;
		पूर्ण

		work_to_करो = RING_HAS_UNCONSUMED_REQUESTS(&queue->tx);
		अगर (!work_to_करो)
			अवरोध;

		idx = queue->tx.req_cons;
		rmb(); /* Ensure that we see the request beक्रमe we copy it. */
		RING_COPY_REQUEST(&queue->tx, idx, &txreq);

		/* Credit-based scheduling. */
		अगर (txreq.size > queue->reमुख्यing_credit &&
		    tx_credit_exceeded(queue, txreq.size))
			अवरोध;

		queue->reमुख्यing_credit -= txreq.size;

		work_to_करो--;
		queue->tx.req_cons = ++idx;

		स_रखो(extras, 0, माप(extras));
		extra_count = 0;
		अगर (txreq.flags & XEN_NETTXF_extra_info) अणु
			work_to_करो = xenvअगर_get_extras(queue, extras,
						       &extra_count,
						       work_to_करो);
			idx = queue->tx.req_cons;
			अगर (unlikely(work_to_करो < 0))
				अवरोध;
		पूर्ण

		अगर (extras[XEN_NETIF_EXTRA_TYPE_MCAST_ADD - 1].type) अणु
			काष्ठा xen_netअगर_extra_info *extra;

			extra = &extras[XEN_NETIF_EXTRA_TYPE_MCAST_ADD - 1];
			ret = xenvअगर_mcast_add(queue->vअगर, extra->u.mcast.addr);

			make_tx_response(queue, &txreq, extra_count,
					 (ret == 0) ?
					 XEN_NETIF_RSP_OKAY :
					 XEN_NETIF_RSP_ERROR);
			push_tx_responses(queue);
			जारी;
		पूर्ण

		अगर (extras[XEN_NETIF_EXTRA_TYPE_MCAST_DEL - 1].type) अणु
			काष्ठा xen_netअगर_extra_info *extra;

			extra = &extras[XEN_NETIF_EXTRA_TYPE_MCAST_DEL - 1];
			xenvअगर_mcast_del(queue->vअगर, extra->u.mcast.addr);

			make_tx_response(queue, &txreq, extra_count,
					 XEN_NETIF_RSP_OKAY);
			push_tx_responses(queue);
			जारी;
		पूर्ण

		ret = xenvअगर_count_requests(queue, &txreq, extra_count,
					    txfrags, work_to_करो);
		अगर (unlikely(ret < 0))
			अवरोध;

		idx += ret;

		अगर (unlikely(txreq.size < ETH_HLEN)) अणु
			netdev_dbg(queue->vअगर->dev,
				   "Bad packet size: %d\n", txreq.size);
			xenvअगर_tx_err(queue, &txreq, extra_count, idx);
			अवरोध;
		पूर्ण

		/* No crossing a page as the payload mustn't fragment. */
		अगर (unlikely((txreq.offset + txreq.size) > XEN_PAGE_SIZE)) अणु
			netdev_err(queue->vअगर->dev,
				   "txreq.offset: %u, size: %u, end: %lu\n",
				   txreq.offset, txreq.size,
				   (अचिन्हित दीर्घ)(txreq.offset&~XEN_PAGE_MASK) + txreq.size);
			xenvअगर_fatal_tx_err(queue->vअगर);
			अवरोध;
		पूर्ण

		index = pending_index(queue->pending_cons);
		pending_idx = queue->pending_ring[index];

		data_len = (txreq.size > XEN_NETBACK_TX_COPY_LEN &&
			    ret < XEN_NETBK_LEGACY_SLOTS_MAX) ?
			XEN_NETBACK_TX_COPY_LEN : txreq.size;

		skb = xenvअगर_alloc_skb(data_len);
		अगर (unlikely(skb == शून्य)) अणु
			netdev_dbg(queue->vअगर->dev,
				   "Can't allocate a skb in start_xmit.\n");
			xenvअगर_tx_err(queue, &txreq, extra_count, idx);
			अवरोध;
		पूर्ण

		skb_shinfo(skb)->nr_frags = ret;
		अगर (data_len < txreq.size)
			skb_shinfo(skb)->nr_frags++;
		/* At this poपूर्णांक shinfo->nr_frags is in fact the number of
		 * slots, which can be as large as XEN_NETBK_LEGACY_SLOTS_MAX.
		 */
		frag_overflow = 0;
		nskb = शून्य;
		अगर (skb_shinfo(skb)->nr_frags > MAX_SKB_FRAGS) अणु
			frag_overflow = skb_shinfo(skb)->nr_frags - MAX_SKB_FRAGS;
			BUG_ON(frag_overflow > MAX_SKB_FRAGS);
			skb_shinfo(skb)->nr_frags = MAX_SKB_FRAGS;
			nskb = xenvअगर_alloc_skb(0);
			अगर (unlikely(nskb == शून्य)) अणु
				skb_shinfo(skb)->nr_frags = 0;
				kमुक्त_skb(skb);
				xenvअगर_tx_err(queue, &txreq, extra_count, idx);
				अगर (net_ratelimit())
					netdev_err(queue->vअगर->dev,
						   "Can't allocate the frag_list skb.\n");
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (extras[XEN_NETIF_EXTRA_TYPE_GSO - 1].type) अणु
			काष्ठा xen_netअगर_extra_info *gso;
			gso = &extras[XEN_NETIF_EXTRA_TYPE_GSO - 1];

			अगर (xenvअगर_set_skb_gso(queue->vअगर, skb, gso)) अणु
				/* Failure in xenvअगर_set_skb_gso is fatal. */
				skb_shinfo(skb)->nr_frags = 0;
				kमुक्त_skb(skb);
				kमुक्त_skb(nskb);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (extras[XEN_NETIF_EXTRA_TYPE_HASH - 1].type) अणु
			काष्ठा xen_netअगर_extra_info *extra;
			क्रमागत pkt_hash_types type = PKT_HASH_TYPE_NONE;

			extra = &extras[XEN_NETIF_EXTRA_TYPE_HASH - 1];

			चयन (extra->u.hash.type) अणु
			हाल _XEN_NETIF_CTRL_HASH_TYPE_IPV4:
			हाल _XEN_NETIF_CTRL_HASH_TYPE_IPV6:
				type = PKT_HASH_TYPE_L3;
				अवरोध;

			हाल _XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP:
			हाल _XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP:
				type = PKT_HASH_TYPE_L4;
				अवरोध;

			शेष:
				अवरोध;
			पूर्ण

			अगर (type != PKT_HASH_TYPE_NONE)
				skb_set_hash(skb,
					     *(u32 *)extra->u.hash.value,
					     type);
		पूर्ण

		XENVIF_TX_CB(skb)->pending_idx = pending_idx;

		__skb_put(skb, data_len);
		queue->tx_copy_ops[*copy_ops].source.u.ref = txreq.gref;
		queue->tx_copy_ops[*copy_ops].source.करोmid = queue->vअगर->करोmid;
		queue->tx_copy_ops[*copy_ops].source.offset = txreq.offset;

		queue->tx_copy_ops[*copy_ops].dest.u.gmfn =
			virt_to_gfn(skb->data);
		queue->tx_copy_ops[*copy_ops].dest.करोmid = DOMID_SELF;
		queue->tx_copy_ops[*copy_ops].dest.offset =
			offset_in_page(skb->data) & ~XEN_PAGE_MASK;

		queue->tx_copy_ops[*copy_ops].len = data_len;
		queue->tx_copy_ops[*copy_ops].flags = GNTCOPY_source_gref;

		(*copy_ops)++;

		अगर (data_len < txreq.size) अणु
			frag_set_pending_idx(&skb_shinfo(skb)->frags[0],
					     pending_idx);
			xenvअगर_tx_create_map_op(queue, pending_idx, &txreq,
						extra_count, gop);
			gop++;
		पूर्ण अन्यथा अणु
			frag_set_pending_idx(&skb_shinfo(skb)->frags[0],
					     INVALID_PENDING_IDX);
			स_नकल(&queue->pending_tx_info[pending_idx].req,
			       &txreq, माप(txreq));
			queue->pending_tx_info[pending_idx].extra_count =
				extra_count;
		पूर्ण

		queue->pending_cons++;

		gop = xenvअगर_get_requests(queue, skb, txfrags, gop,
				          frag_overflow, nskb);

		__skb_queue_tail(&queue->tx_queue, skb);

		queue->tx.req_cons = idx;

		अगर (((gop-queue->tx_map_ops) >= ARRAY_SIZE(queue->tx_map_ops)) ||
		    (*copy_ops >= ARRAY_SIZE(queue->tx_copy_ops)))
			अवरोध;
	पूर्ण

	(*map_ops) = gop - queue->tx_map_ops;
	वापस;
पूर्ण

/* Consolidate skb with a frag_list पूर्णांकo a bअक्रम new one with local pages on
 * frags. Returns 0 or -ENOMEM अगर can't allocate new pages.
 */
अटल पूर्णांक xenvअगर_handle_frag_list(काष्ठा xenvअगर_queue *queue, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक offset = skb_headlen(skb);
	skb_frag_t frags[MAX_SKB_FRAGS];
	पूर्णांक i, f;
	काष्ठा ubuf_info *uarg;
	काष्ठा sk_buff *nskb = skb_shinfo(skb)->frag_list;

	queue->stats.tx_zerocopy_sent += 2;
	queue->stats.tx_frag_overflow++;

	xenvअगर_fill_frags(queue, nskb);
	/* Subtract frags size, we will correct it later */
	skb->truesize -= skb->data_len;
	skb->len += nskb->len;
	skb->data_len += nskb->len;

	/* create a bअक्रम new frags array and coalesce there */
	क्रम (i = 0; offset < skb->len; i++) अणु
		काष्ठा page *page;
		अचिन्हित पूर्णांक len;

		BUG_ON(i >= MAX_SKB_FRAGS);
		page = alloc_page(GFP_ATOMIC);
		अगर (!page) अणु
			पूर्णांक j;
			skb->truesize += skb->data_len;
			क्रम (j = 0; j < i; j++)
				put_page(skb_frag_page(&frags[j]));
			वापस -ENOMEM;
		पूर्ण

		अगर (offset + PAGE_SIZE < skb->len)
			len = PAGE_SIZE;
		अन्यथा
			len = skb->len - offset;
		अगर (skb_copy_bits(skb, offset, page_address(page), len))
			BUG();

		offset += len;
		__skb_frag_set_page(&frags[i], page);
		skb_frag_off_set(&frags[i], 0);
		skb_frag_size_set(&frags[i], len);
	पूर्ण

	/* Release all the original (क्रमeign) frags. */
	क्रम (f = 0; f < skb_shinfo(skb)->nr_frags; f++)
		skb_frag_unref(skb, f);
	uarg = skb_shinfo(skb)->deकाष्ठाor_arg;
	/* increase inflight counter to offset decrement in callback */
	atomic_inc(&queue->inflight_packets);
	uarg->callback(शून्य, uarg, true);
	skb_shinfo(skb)->deकाष्ठाor_arg = शून्य;

	/* Fill the skb with the new (local) frags. */
	स_नकल(skb_shinfo(skb)->frags, frags, i * माप(skb_frag_t));
	skb_shinfo(skb)->nr_frags = i;
	skb->truesize += i * PAGE_SIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक xenvअगर_tx_submit(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा gnttab_map_grant_ref *gop_map = queue->tx_map_ops;
	काष्ठा gnttab_copy *gop_copy = queue->tx_copy_ops;
	काष्ठा sk_buff *skb;
	पूर्णांक work_करोne = 0;

	जबतक ((skb = __skb_dequeue(&queue->tx_queue)) != शून्य) अणु
		काष्ठा xen_netअगर_tx_request *txp;
		u16 pending_idx;
		अचिन्हित data_len;

		pending_idx = XENVIF_TX_CB(skb)->pending_idx;
		txp = &queue->pending_tx_info[pending_idx].req;

		/* Check the remap error code. */
		अगर (unlikely(xenvअगर_tx_check_gop(queue, skb, &gop_map, &gop_copy))) अणु
			/* If there was an error, xenvअगर_tx_check_gop is
			 * expected to release all the frags which were mapped,
			 * so kमुक्त_skb shouldn't करो it again
			 */
			skb_shinfo(skb)->nr_frags = 0;
			अगर (skb_has_frag_list(skb)) अणु
				काष्ठा sk_buff *nskb =
						skb_shinfo(skb)->frag_list;
				skb_shinfo(nskb)->nr_frags = 0;
			पूर्ण
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		data_len = skb->len;
		callback_param(queue, pending_idx).ctx = शून्य;
		अगर (data_len < txp->size) अणु
			/* Append the packet payload as a fragment. */
			txp->offset += data_len;
			txp->size -= data_len;
		पूर्ण अन्यथा अणु
			/* Schedule a response immediately. */
			xenvअगर_idx_release(queue, pending_idx,
					   XEN_NETIF_RSP_OKAY);
		पूर्ण

		अगर (txp->flags & XEN_NETTXF_csum_blank)
			skb->ip_summed = CHECKSUM_PARTIAL;
		अन्यथा अगर (txp->flags & XEN_NETTXF_data_validated)
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		xenvअगर_fill_frags(queue, skb);

		अगर (unlikely(skb_has_frag_list(skb))) अणु
			काष्ठा sk_buff *nskb = skb_shinfo(skb)->frag_list;
			xenvअगर_skb_zerocopy_prepare(queue, nskb);
			अगर (xenvअगर_handle_frag_list(queue, skb)) अणु
				अगर (net_ratelimit())
					netdev_err(queue->vअगर->dev,
						   "Not enough memory to consolidate frag_list!\n");
				xenvअगर_skb_zerocopy_prepare(queue, skb);
				kमुक्त_skb(skb);
				जारी;
			पूर्ण
			/* Copied all the bits from the frag list -- मुक्त it. */
			skb_frag_list_init(skb);
			kमुक्त_skb(nskb);
		पूर्ण

		skb->dev      = queue->vअगर->dev;
		skb->protocol = eth_type_trans(skb, skb->dev);
		skb_reset_network_header(skb);

		अगर (checksum_setup(queue, skb)) अणु
			netdev_dbg(queue->vअगर->dev,
				   "Can't setup checksum in net_tx_action\n");
			/* We have to set this flag to trigger the callback */
			अगर (skb_shinfo(skb)->deकाष्ठाor_arg)
				xenvअगर_skb_zerocopy_prepare(queue, skb);
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		skb_probe_transport_header(skb);

		/* If the packet is GSO then we will have just set up the
		 * transport header offset in checksum_setup so it's now
		 * straightक्रमward to calculate gso_segs.
		 */
		अगर (skb_is_gso(skb)) अणु
			पूर्णांक mss, hdrlen;

			/* GSO implies having the L4 header. */
			WARN_ON_ONCE(!skb_transport_header_was_set(skb));
			अगर (unlikely(!skb_transport_header_was_set(skb))) अणु
				kमुक्त_skb(skb);
				जारी;
			पूर्ण

			mss = skb_shinfo(skb)->gso_size;
			hdrlen = skb_transport_header(skb) -
				skb_mac_header(skb) +
				tcp_hdrlen(skb);

			skb_shinfo(skb)->gso_segs =
				DIV_ROUND_UP(skb->len - hdrlen, mss);
		पूर्ण

		queue->stats.rx_bytes += skb->len;
		queue->stats.rx_packets++;

		work_करोne++;

		/* Set this flag right beक्रमe netअगर_receive_skb, otherwise
		 * someone might think this packet alपढ़ोy left netback, and
		 * करो a skb_copy_ubufs जबतक we are still in control of the
		 * skb. E.g. the __pskb_pull_tail earlier can करो such thing.
		 */
		अगर (skb_shinfo(skb)->deकाष्ठाor_arg) अणु
			xenvअगर_skb_zerocopy_prepare(queue, skb);
			queue->stats.tx_zerocopy_sent++;
		पूर्ण

		netअगर_receive_skb(skb);
	पूर्ण

	वापस work_करोne;
पूर्ण

व्योम xenvअगर_zerocopy_callback(काष्ठा sk_buff *skb, काष्ठा ubuf_info *ubuf,
			      bool zerocopy_success)
अणु
	अचिन्हित दीर्घ flags;
	pending_ring_idx_t index;
	काष्ठा xenvअगर_queue *queue = ubuf_to_queue(ubuf);

	/* This is the only place where we grab this lock, to protect callbacks
	 * from each other.
	 */
	spin_lock_irqsave(&queue->callback_lock, flags);
	करो अणु
		u16 pending_idx = ubuf->desc;
		ubuf = (काष्ठा ubuf_info *) ubuf->ctx;
		BUG_ON(queue->dealloc_prod - queue->dealloc_cons >=
			MAX_PENDING_REQS);
		index = pending_index(queue->dealloc_prod);
		queue->dealloc_ring[index] = pending_idx;
		/* Sync with xenvअगर_tx_dealloc_action:
		 * insert idx then incr producer.
		 */
		smp_wmb();
		queue->dealloc_prod++;
	पूर्ण जबतक (ubuf);
	spin_unlock_irqrestore(&queue->callback_lock, flags);

	अगर (likely(zerocopy_success))
		queue->stats.tx_zerocopy_success++;
	अन्यथा
		queue->stats.tx_zerocopy_fail++;
	xenvअगर_skb_zerocopy_complete(queue);
पूर्ण

अटल अंतरभूत व्योम xenvअगर_tx_dealloc_action(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा gnttab_unmap_grant_ref *gop;
	pending_ring_idx_t dc, dp;
	u16 pending_idx, pending_idx_release[MAX_PENDING_REQS];
	अचिन्हित पूर्णांक i = 0;

	dc = queue->dealloc_cons;
	gop = queue->tx_unmap_ops;

	/* Free up any grants we have finished using */
	करो अणु
		dp = queue->dealloc_prod;

		/* Ensure we see all indices enqueued by all
		 * xenvअगर_zerocopy_callback().
		 */
		smp_rmb();

		जबतक (dc != dp) अणु
			BUG_ON(gop - queue->tx_unmap_ops >= MAX_PENDING_REQS);
			pending_idx =
				queue->dealloc_ring[pending_index(dc++)];

			pending_idx_release[gop - queue->tx_unmap_ops] =
				pending_idx;
			queue->pages_to_unmap[gop - queue->tx_unmap_ops] =
				queue->mmap_pages[pending_idx];
			gnttab_set_unmap_op(gop,
					    idx_to_kaddr(queue, pending_idx),
					    GNTMAP_host_map,
					    queue->grant_tx_handle[pending_idx]);
			xenvअगर_grant_handle_reset(queue, pending_idx);
			++gop;
		पूर्ण

	पूर्ण जबतक (dp != queue->dealloc_prod);

	queue->dealloc_cons = dc;

	अगर (gop - queue->tx_unmap_ops > 0) अणु
		पूर्णांक ret;
		ret = gnttab_unmap_refs(queue->tx_unmap_ops,
					शून्य,
					queue->pages_to_unmap,
					gop - queue->tx_unmap_ops);
		अगर (ret) अणु
			netdev_err(queue->vअगर->dev, "Unmap fail: nr_ops %tu ret %d\n",
				   gop - queue->tx_unmap_ops, ret);
			क्रम (i = 0; i < gop - queue->tx_unmap_ops; ++i) अणु
				अगर (gop[i].status != GNTST_okay)
					netdev_err(queue->vअगर->dev,
						   " host_addr: 0x%llx handle: 0x%x status: %d\n",
						   gop[i].host_addr,
						   gop[i].handle,
						   gop[i].status);
			पूर्ण
			BUG();
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < gop - queue->tx_unmap_ops; ++i)
		xenvअगर_idx_release(queue, pending_idx_release[i],
				   XEN_NETIF_RSP_OKAY);
पूर्ण


/* Called after netfront has transmitted */
पूर्णांक xenvअगर_tx_action(काष्ठा xenvअगर_queue *queue, पूर्णांक budget)
अणु
	अचिन्हित nr_mops, nr_cops = 0;
	पूर्णांक work_करोne, ret;

	अगर (unlikely(!tx_work_toकरो(queue)))
		वापस 0;

	xenvअगर_tx_build_gops(queue, budget, &nr_cops, &nr_mops);

	अगर (nr_cops == 0)
		वापस 0;

	gnttab_batch_copy(queue->tx_copy_ops, nr_cops);
	अगर (nr_mops != 0) अणु
		ret = gnttab_map_refs(queue->tx_map_ops,
				      शून्य,
				      queue->pages_to_map,
				      nr_mops);
		अगर (ret) अणु
			अचिन्हित पूर्णांक i;

			netdev_err(queue->vअगर->dev, "Map fail: nr %u ret %d\n",
				   nr_mops, ret);
			क्रम (i = 0; i < nr_mops; ++i)
				WARN_ON_ONCE(queue->tx_map_ops[i].status ==
				             GNTST_okay);
		पूर्ण
	पूर्ण

	work_करोne = xenvअगर_tx_submit(queue);

	वापस work_करोne;
पूर्ण

अटल व्योम xenvअगर_idx_release(काष्ठा xenvअगर_queue *queue, u16 pending_idx,
			       u8 status)
अणु
	काष्ठा pending_tx_info *pending_tx_info;
	pending_ring_idx_t index;
	अचिन्हित दीर्घ flags;

	pending_tx_info = &queue->pending_tx_info[pending_idx];

	spin_lock_irqsave(&queue->response_lock, flags);

	make_tx_response(queue, &pending_tx_info->req,
			 pending_tx_info->extra_count, status);

	/* Release the pending index beक्रमe pusing the Tx response so
	 * its available beक्रमe a new Tx request is pushed by the
	 * frontend.
	 */
	index = pending_index(queue->pending_prod++);
	queue->pending_ring[index] = pending_idx;

	push_tx_responses(queue);

	spin_unlock_irqrestore(&queue->response_lock, flags);
पूर्ण


अटल व्योम make_tx_response(काष्ठा xenvअगर_queue *queue,
			     काष्ठा xen_netअगर_tx_request *txp,
			     अचिन्हित पूर्णांक extra_count,
			     s8       st)
अणु
	RING_IDX i = queue->tx.rsp_prod_pvt;
	काष्ठा xen_netअगर_tx_response *resp;

	resp = RING_GET_RESPONSE(&queue->tx, i);
	resp->id     = txp->id;
	resp->status = st;

	जबतक (extra_count-- != 0)
		RING_GET_RESPONSE(&queue->tx, ++i)->status = XEN_NETIF_RSP_शून्य;

	queue->tx.rsp_prod_pvt = ++i;
पूर्ण

अटल व्योम push_tx_responses(काष्ठा xenvअगर_queue *queue)
अणु
	पूर्णांक notअगरy;

	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&queue->tx, notअगरy);
	अगर (notअगरy)
		notअगरy_remote_via_irq(queue->tx_irq);
पूर्ण

व्योम xenvअगर_idx_unmap(काष्ठा xenvअगर_queue *queue, u16 pending_idx)
अणु
	पूर्णांक ret;
	काष्ठा gnttab_unmap_grant_ref tx_unmap_op;

	gnttab_set_unmap_op(&tx_unmap_op,
			    idx_to_kaddr(queue, pending_idx),
			    GNTMAP_host_map,
			    queue->grant_tx_handle[pending_idx]);
	xenvअगर_grant_handle_reset(queue, pending_idx);

	ret = gnttab_unmap_refs(&tx_unmap_op, शून्य,
				&queue->mmap_pages[pending_idx], 1);
	अगर (ret) अणु
		netdev_err(queue->vअगर->dev,
			   "Unmap fail: ret: %d pending_idx: %d host_addr: %llx handle: 0x%x status: %d\n",
			   ret,
			   pending_idx,
			   tx_unmap_op.host_addr,
			   tx_unmap_op.handle,
			   tx_unmap_op.status);
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक tx_work_toकरो(काष्ठा xenvअगर_queue *queue)
अणु
	अगर (likely(RING_HAS_UNCONSUMED_REQUESTS(&queue->tx)))
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत bool tx_dealloc_work_toकरो(काष्ठा xenvअगर_queue *queue)
अणु
	वापस queue->dealloc_cons != queue->dealloc_prod;
पूर्ण

व्योम xenvअगर_unmap_frontend_data_rings(काष्ठा xenvअगर_queue *queue)
अणु
	अगर (queue->tx.sring)
		xenbus_unmap_ring_vमुक्त(xenvअगर_to_xenbus_device(queue->vअगर),
					queue->tx.sring);
	अगर (queue->rx.sring)
		xenbus_unmap_ring_vमुक्त(xenvअगर_to_xenbus_device(queue->vअगर),
					queue->rx.sring);
पूर्ण

पूर्णांक xenvअगर_map_frontend_data_rings(काष्ठा xenvअगर_queue *queue,
				   grant_ref_t tx_ring_ref,
				   grant_ref_t rx_ring_ref)
अणु
	व्योम *addr;
	काष्ठा xen_netअगर_tx_sring *txs;
	काष्ठा xen_netअगर_rx_sring *rxs;
	RING_IDX rsp_prod, req_prod;
	पूर्णांक err = -ENOMEM;

	err = xenbus_map_ring_valloc(xenvअगर_to_xenbus_device(queue->vअगर),
				     &tx_ring_ref, 1, &addr);
	अगर (err)
		जाओ err;

	txs = (काष्ठा xen_netअगर_tx_sring *)addr;
	rsp_prod = READ_ONCE(txs->rsp_prod);
	req_prod = READ_ONCE(txs->req_prod);

	BACK_RING_ATTACH(&queue->tx, txs, rsp_prod, XEN_PAGE_SIZE);

	err = -EIO;
	अगर (req_prod - rsp_prod > RING_SIZE(&queue->tx))
		जाओ err;

	err = xenbus_map_ring_valloc(xenvअगर_to_xenbus_device(queue->vअगर),
				     &rx_ring_ref, 1, &addr);
	अगर (err)
		जाओ err;

	rxs = (काष्ठा xen_netअगर_rx_sring *)addr;
	rsp_prod = READ_ONCE(rxs->rsp_prod);
	req_prod = READ_ONCE(rxs->req_prod);

	BACK_RING_ATTACH(&queue->rx, rxs, rsp_prod, XEN_PAGE_SIZE);

	err = -EIO;
	अगर (req_prod - rsp_prod > RING_SIZE(&queue->rx))
		जाओ err;

	वापस 0;

err:
	xenvअगर_unmap_frontend_data_rings(queue);
	वापस err;
पूर्ण

अटल bool xenvअगर_dealloc_kthपढ़ो_should_stop(काष्ठा xenvअगर_queue *queue)
अणु
	/* Dealloc thपढ़ो must reमुख्य running until all inflight
	 * packets complete.
	 */
	वापस kthपढ़ो_should_stop() &&
		!atomic_पढ़ो(&queue->inflight_packets);
पूर्ण

पूर्णांक xenvअगर_dealloc_kthपढ़ो(व्योम *data)
अणु
	काष्ठा xenvअगर_queue *queue = data;

	क्रम (;;) अणु
		रुको_event_पूर्णांकerruptible(queue->dealloc_wq,
					 tx_dealloc_work_toकरो(queue) ||
					 xenvअगर_dealloc_kthपढ़ो_should_stop(queue));
		अगर (xenvअगर_dealloc_kthपढ़ो_should_stop(queue))
			अवरोध;

		xenvअगर_tx_dealloc_action(queue);
		cond_resched();
	पूर्ण

	/* Unmap anything reमुख्यing*/
	अगर (tx_dealloc_work_toकरो(queue))
		xenvअगर_tx_dealloc_action(queue);

	वापस 0;
पूर्ण

अटल व्योम make_ctrl_response(काष्ठा xenvअगर *vअगर,
			       स्थिर काष्ठा xen_netअगर_ctrl_request *req,
			       u32 status, u32 data)
अणु
	RING_IDX idx = vअगर->ctrl.rsp_prod_pvt;
	काष्ठा xen_netअगर_ctrl_response rsp = अणु
		.id = req->id,
		.type = req->type,
		.status = status,
		.data = data,
	पूर्ण;

	*RING_GET_RESPONSE(&vअगर->ctrl, idx) = rsp;
	vअगर->ctrl.rsp_prod_pvt = ++idx;
पूर्ण

अटल व्योम push_ctrl_response(काष्ठा xenvअगर *vअगर)
अणु
	पूर्णांक notअगरy;

	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&vअगर->ctrl, notअगरy);
	अगर (notअगरy)
		notअगरy_remote_via_irq(vअगर->ctrl_irq);
पूर्ण

अटल व्योम process_ctrl_request(काष्ठा xenvअगर *vअगर,
				 स्थिर काष्ठा xen_netअगर_ctrl_request *req)
अणु
	u32 status = XEN_NETIF_CTRL_STATUS_NOT_SUPPORTED;
	u32 data = 0;

	चयन (req->type) अणु
	हाल XEN_NETIF_CTRL_TYPE_SET_HASH_ALGORITHM:
		status = xenvअगर_set_hash_alg(vअगर, req->data[0]);
		अवरोध;

	हाल XEN_NETIF_CTRL_TYPE_GET_HASH_FLAGS:
		status = xenvअगर_get_hash_flags(vअगर, &data);
		अवरोध;

	हाल XEN_NETIF_CTRL_TYPE_SET_HASH_FLAGS:
		status = xenvअगर_set_hash_flags(vअगर, req->data[0]);
		अवरोध;

	हाल XEN_NETIF_CTRL_TYPE_SET_HASH_KEY:
		status = xenvअगर_set_hash_key(vअगर, req->data[0],
					     req->data[1]);
		अवरोध;

	हाल XEN_NETIF_CTRL_TYPE_GET_HASH_MAPPING_SIZE:
		status = XEN_NETIF_CTRL_STATUS_SUCCESS;
		data = XEN_NETBK_MAX_HASH_MAPPING_SIZE;
		अवरोध;

	हाल XEN_NETIF_CTRL_TYPE_SET_HASH_MAPPING_SIZE:
		status = xenvअगर_set_hash_mapping_size(vअगर,
						      req->data[0]);
		अवरोध;

	हाल XEN_NETIF_CTRL_TYPE_SET_HASH_MAPPING:
		status = xenvअगर_set_hash_mapping(vअगर, req->data[0],
						 req->data[1],
						 req->data[2]);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	make_ctrl_response(vअगर, req, status, data);
	push_ctrl_response(vअगर);
पूर्ण

अटल व्योम xenvअगर_ctrl_action(काष्ठा xenvअगर *vअगर)
अणु
	क्रम (;;) अणु
		RING_IDX req_prod, req_cons;

		req_prod = vअगर->ctrl.sring->req_prod;
		req_cons = vअगर->ctrl.req_cons;

		/* Make sure we can see requests beक्रमe we process them. */
		rmb();

		अगर (req_cons == req_prod)
			अवरोध;

		जबतक (req_cons != req_prod) अणु
			काष्ठा xen_netअगर_ctrl_request req;

			RING_COPY_REQUEST(&vअगर->ctrl, req_cons, &req);
			req_cons++;

			process_ctrl_request(vअगर, &req);
		पूर्ण

		vअगर->ctrl.req_cons = req_cons;
		vअगर->ctrl.sring->req_event = req_cons + 1;
	पूर्ण
पूर्ण

अटल bool xenvअगर_ctrl_work_toकरो(काष्ठा xenvअगर *vअगर)
अणु
	अगर (likely(RING_HAS_UNCONSUMED_REQUESTS(&vअगर->ctrl)))
		वापस true;

	वापस false;
पूर्ण

irqवापस_t xenvअगर_ctrl_irq_fn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xenvअगर *vअगर = data;
	अचिन्हित पूर्णांक eoi_flag = XEN_EOI_FLAG_SPURIOUS;

	जबतक (xenvअगर_ctrl_work_toकरो(vअगर)) अणु
		xenvअगर_ctrl_action(vअगर);
		eoi_flag = 0;
	पूर्ण

	xen_irq_lateeoi(irq, eoi_flag);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init netback_init(व्योम)
अणु
	पूर्णांक rc = 0;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	/* Allow as many queues as there are CPUs but max. 8 अगर user has not
	 * specअगरied a value.
	 */
	अगर (xenvअगर_max_queues == 0)
		xenvअगर_max_queues = min_t(अचिन्हित पूर्णांक, MAX_QUEUES_DEFAULT,
					  num_online_cpus());

	अगर (fatal_skb_slots < XEN_NETBK_LEGACY_SLOTS_MAX) अणु
		pr_info("fatal_skb_slots too small (%d), bump it to XEN_NETBK_LEGACY_SLOTS_MAX (%d)\n",
			fatal_skb_slots, XEN_NETBK_LEGACY_SLOTS_MAX);
		fatal_skb_slots = XEN_NETBK_LEGACY_SLOTS_MAX;
	पूर्ण

	rc = xenvअगर_xenbus_init();
	अगर (rc)
		जाओ failed_init;

#अगर_घोषित CONFIG_DEBUG_FS
	xen_netback_dbg_root = debugfs_create_dir("xen-netback", शून्य);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

	वापस 0;

failed_init:
	वापस rc;
पूर्ण

module_init(netback_init);

अटल व्योम __निकास netback_fini(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_FS
	debugfs_हटाओ_recursive(xen_netback_dbg_root);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
	xenvअगर_xenbus_fini();
पूर्ण
module_निकास(netback_fini);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("xen-backend:vif");
