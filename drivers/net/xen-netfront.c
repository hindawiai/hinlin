<शैली गुरु>
/*
 * Virtual network driver क्रम conversing with remote driver backends.
 *
 * Copyright (c) 2002-2005, K A Fraser
 * Copyright (c) 2005, XenSource Ltd
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_ether.h>
#समावेश <net/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <net/ip.h>
#समावेश <linux/bpf.h>
#समावेश <net/page_pool.h>
#समावेश <linux/bpf_trace.h>

#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/events.h>
#समावेश <xen/page.h>
#समावेश <xen/platक्रमm_pci.h>
#समावेश <xen/grant_table.h>

#समावेश <xen/पूर्णांकerface/io/netअगर.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/पूर्णांकerface/grant_table.h>

/* Module parameters */
#घोषणा MAX_QUEUES_DEFAULT 8
अटल अचिन्हित पूर्णांक xennet_max_queues;
module_param_named(max_queues, xennet_max_queues, uपूर्णांक, 0644);
MODULE_PARM_DESC(max_queues,
		 "Maximum number of queues per virtual interface");

#घोषणा XENNET_TIMEOUT  (5 * HZ)

अटल स्थिर काष्ठा ethtool_ops xennet_ethtool_ops;

काष्ठा netfront_cb अणु
	पूर्णांक pull_to;
पूर्ण;

#घोषणा NETFRONT_SKB_CB(skb)	((काष्ठा netfront_cb *)((skb)->cb))

#घोषणा RX_COPY_THRESHOLD 256

#घोषणा GRANT_INVALID_REF	0

#घोषणा NET_TX_RING_SIZE __CONST_RING_SIZE(xen_netअगर_tx, XEN_PAGE_SIZE)
#घोषणा NET_RX_RING_SIZE __CONST_RING_SIZE(xen_netअगर_rx, XEN_PAGE_SIZE)

/* Minimum number of Rx slots (includes slot क्रम GSO metadata). */
#घोषणा NET_RX_SLOTS_MIN (XEN_NETIF_NR_SLOTS_MIN + 1)

/* Queue name is पूर्णांकerface name with "-qNNN" appended */
#घोषणा QUEUE_NAME_SIZE (IFNAMSIZ + 6)

/* IRQ name is queue name with "-tx" or "-rx" appended */
#घोषणा IRQ_NAME_SIZE (QUEUE_NAME_SIZE + 3)

अटल DECLARE_WAIT_QUEUE_HEAD(module_wq);

काष्ठा netfront_stats अणु
	u64			packets;
	u64			bytes;
	काष्ठा u64_stats_sync	syncp;
पूर्ण;

काष्ठा netfront_info;

काष्ठा netfront_queue अणु
	अचिन्हित पूर्णांक id; /* Queue ID, 0-based */
	अक्षर name[QUEUE_NAME_SIZE]; /* DEVNAME-qN */
	काष्ठा netfront_info *info;

	काष्ठा bpf_prog __rcu *xdp_prog;

	काष्ठा napi_काष्ठा napi;

	/* Split event channels support, tx_* == rx_* when using
	 * single event channel.
	 */
	अचिन्हित पूर्णांक tx_evtchn, rx_evtchn;
	अचिन्हित पूर्णांक tx_irq, rx_irq;
	/* Only used when split event channels support is enabled */
	अक्षर tx_irq_name[IRQ_NAME_SIZE]; /* DEVNAME-qN-tx */
	अक्षर rx_irq_name[IRQ_NAME_SIZE]; /* DEVNAME-qN-rx */

	spinlock_t   tx_lock;
	काष्ठा xen_netअगर_tx_front_ring tx;
	पूर्णांक tx_ring_ref;

	/*
	 * अणुtx,rxपूर्ण_skbs store outstanding skbuffs. Free tx_skb entries
	 * are linked from tx_skb_मुक्तlist through skb_entry.link.
	 *
	 *  NB. Freelist index entries are always going to be less than
	 *  PAGE_OFFSET, whereas poपूर्णांकers to skbs will always be equal or
	 *  greater than PAGE_OFFSET: we use this property to distinguish
	 *  them.
	 */
	जोड़ skb_entry अणु
		काष्ठा sk_buff *skb;
		अचिन्हित दीर्घ link;
	पूर्ण tx_skbs[NET_TX_RING_SIZE];
	grant_ref_t gref_tx_head;
	grant_ref_t grant_tx_ref[NET_TX_RING_SIZE];
	काष्ठा page *grant_tx_page[NET_TX_RING_SIZE];
	अचिन्हित tx_skb_मुक्तlist;

	spinlock_t   rx_lock ____cacheline_aligned_in_smp;
	काष्ठा xen_netअगर_rx_front_ring rx;
	पूर्णांक rx_ring_ref;

	काष्ठा समयr_list rx_refill_समयr;

	काष्ठा sk_buff *rx_skbs[NET_RX_RING_SIZE];
	grant_ref_t gref_rx_head;
	grant_ref_t grant_rx_ref[NET_RX_RING_SIZE];

	काष्ठा page_pool *page_pool;
	काष्ठा xdp_rxq_info xdp_rxq;
पूर्ण;

काष्ठा netfront_info अणु
	काष्ठा list_head list;
	काष्ठा net_device *netdev;

	काष्ठा xenbus_device *xbdev;

	/* Multi-queue support */
	काष्ठा netfront_queue *queues;

	/* Statistics */
	काष्ठा netfront_stats __percpu *rx_stats;
	काष्ठा netfront_stats __percpu *tx_stats;

	/* XDP state */
	bool netback_has_xdp_headroom;
	bool netfront_xdp_enabled;

	atomic_t rx_gso_checksum_fixup;
पूर्ण;

काष्ठा netfront_rx_info अणु
	काष्ठा xen_netअगर_rx_response rx;
	काष्ठा xen_netअगर_extra_info extras[XEN_NETIF_EXTRA_TYPE_MAX - 1];
पूर्ण;

अटल व्योम skb_entry_set_link(जोड़ skb_entry *list, अचिन्हित लघु id)
अणु
	list->link = id;
पूर्ण

अटल पूर्णांक skb_entry_is_link(स्थिर जोड़ skb_entry *list)
अणु
	BUILD_BUG_ON(माप(list->skb) != माप(list->link));
	वापस (अचिन्हित दीर्घ)list->skb < PAGE_OFFSET;
पूर्ण

/*
 * Access macros क्रम acquiring मुक्तing slots in tx_skbs[].
 */

अटल व्योम add_id_to_मुक्तlist(अचिन्हित *head, जोड़ skb_entry *list,
			       अचिन्हित लघु id)
अणु
	skb_entry_set_link(&list[id], *head);
	*head = id;
पूर्ण

अटल अचिन्हित लघु get_id_from_मुक्तlist(अचिन्हित *head,
					   जोड़ skb_entry *list)
अणु
	अचिन्हित पूर्णांक id = *head;
	*head = list[id].link;
	वापस id;
पूर्ण

अटल पूर्णांक xennet_rxidx(RING_IDX idx)
अणु
	वापस idx & (NET_RX_RING_SIZE - 1);
पूर्ण

अटल काष्ठा sk_buff *xennet_get_rx_skb(काष्ठा netfront_queue *queue,
					 RING_IDX ri)
अणु
	पूर्णांक i = xennet_rxidx(ri);
	काष्ठा sk_buff *skb = queue->rx_skbs[i];
	queue->rx_skbs[i] = शून्य;
	वापस skb;
पूर्ण

अटल grant_ref_t xennet_get_rx_ref(काष्ठा netfront_queue *queue,
					    RING_IDX ri)
अणु
	पूर्णांक i = xennet_rxidx(ri);
	grant_ref_t ref = queue->grant_rx_ref[i];
	queue->grant_rx_ref[i] = GRANT_INVALID_REF;
	वापस ref;
पूर्ण

#अगर_घोषित CONFIG_SYSFS
अटल स्थिर काष्ठा attribute_group xennet_dev_group;
#पूर्ण_अगर

अटल bool xennet_can_sg(काष्ठा net_device *dev)
अणु
	वापस dev->features & NETIF_F_SG;
पूर्ण


अटल व्योम rx_refill_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा netfront_queue *queue = from_समयr(queue, t, rx_refill_समयr);
	napi_schedule(&queue->napi);
पूर्ण

अटल पूर्णांक netfront_tx_slot_available(काष्ठा netfront_queue *queue)
अणु
	वापस (queue->tx.req_prod_pvt - queue->tx.rsp_cons) <
		(NET_TX_RING_SIZE - XEN_NETIF_NR_SLOTS_MIN - 1);
पूर्ण

अटल व्योम xennet_maybe_wake_tx(काष्ठा netfront_queue *queue)
अणु
	काष्ठा net_device *dev = queue->info->netdev;
	काष्ठा netdev_queue *dev_queue = netdev_get_tx_queue(dev, queue->id);

	अगर (unlikely(netअगर_tx_queue_stopped(dev_queue)) &&
	    netfront_tx_slot_available(queue) &&
	    likely(netअगर_running(dev)))
		netअगर_tx_wake_queue(netdev_get_tx_queue(dev, queue->id));
पूर्ण


अटल काष्ठा sk_buff *xennet_alloc_one_rx_buffer(काष्ठा netfront_queue *queue)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा page *page;

	skb = __netdev_alloc_skb(queue->info->netdev,
				 RX_COPY_THRESHOLD + NET_IP_ALIGN,
				 GFP_ATOMIC | __GFP_NOWARN);
	अगर (unlikely(!skb))
		वापस शून्य;

	page = page_pool_dev_alloc_pages(queue->page_pool);
	अगर (unlikely(!page)) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण
	skb_add_rx_frag(skb, 0, page, 0, 0, PAGE_SIZE);

	/* Align ip header to a 16 bytes boundary */
	skb_reserve(skb, NET_IP_ALIGN);
	skb->dev = queue->info->netdev;

	वापस skb;
पूर्ण


अटल व्योम xennet_alloc_rx_buffers(काष्ठा netfront_queue *queue)
अणु
	RING_IDX req_prod = queue->rx.req_prod_pvt;
	पूर्णांक notअगरy;
	पूर्णांक err = 0;

	अगर (unlikely(!netअगर_carrier_ok(queue->info->netdev)))
		वापस;

	क्रम (req_prod = queue->rx.req_prod_pvt;
	     req_prod - queue->rx.rsp_cons < NET_RX_RING_SIZE;
	     req_prod++) अणु
		काष्ठा sk_buff *skb;
		अचिन्हित लघु id;
		grant_ref_t ref;
		काष्ठा page *page;
		काष्ठा xen_netअगर_rx_request *req;

		skb = xennet_alloc_one_rx_buffer(queue);
		अगर (!skb) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		id = xennet_rxidx(req_prod);

		BUG_ON(queue->rx_skbs[id]);
		queue->rx_skbs[id] = skb;

		ref = gnttab_claim_grant_reference(&queue->gref_rx_head);
		WARN_ON_ONCE(IS_ERR_VALUE((अचिन्हित दीर्घ)(पूर्णांक)ref));
		queue->grant_rx_ref[id] = ref;

		page = skb_frag_page(&skb_shinfo(skb)->frags[0]);

		req = RING_GET_REQUEST(&queue->rx, req_prod);
		gnttab_page_grant_क्रमeign_access_ref_one(ref,
							 queue->info->xbdev->otherend_id,
							 page,
							 0);
		req->id = id;
		req->gref = ref;
	पूर्ण

	queue->rx.req_prod_pvt = req_prod;

	/* Try again later अगर there are not enough requests or skb allocation
	 * failed.
	 * Enough requests is quantअगरied as the sum of newly created slots and
	 * the unconsumed slots at the backend.
	 */
	अगर (req_prod - queue->rx.rsp_cons < NET_RX_SLOTS_MIN ||
	    unlikely(err)) अणु
		mod_समयr(&queue->rx_refill_समयr, jअगरfies + (HZ/10));
		वापस;
	पूर्ण

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&queue->rx, notअगरy);
	अगर (notअगरy)
		notअगरy_remote_via_irq(queue->rx_irq);
पूर्ण

अटल पूर्णांक xennet_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा netfront_info *np = netdev_priv(dev);
	अचिन्हित पूर्णांक num_queues = dev->real_num_tx_queues;
	अचिन्हित पूर्णांक i = 0;
	काष्ठा netfront_queue *queue = शून्य;

	अगर (!np->queues)
		वापस -ENODEV;

	क्रम (i = 0; i < num_queues; ++i) अणु
		queue = &np->queues[i];
		napi_enable(&queue->napi);

		spin_lock_bh(&queue->rx_lock);
		अगर (netअगर_carrier_ok(dev)) अणु
			xennet_alloc_rx_buffers(queue);
			queue->rx.sring->rsp_event = queue->rx.rsp_cons + 1;
			अगर (RING_HAS_UNCONSUMED_RESPONSES(&queue->rx))
				napi_schedule(&queue->napi);
		पूर्ण
		spin_unlock_bh(&queue->rx_lock);
	पूर्ण

	netअगर_tx_start_all_queues(dev);

	वापस 0;
पूर्ण

अटल व्योम xennet_tx_buf_gc(काष्ठा netfront_queue *queue)
अणु
	RING_IDX cons, prod;
	अचिन्हित लघु id;
	काष्ठा sk_buff *skb;
	bool more_to_करो;

	BUG_ON(!netअगर_carrier_ok(queue->info->netdev));

	करो अणु
		prod = queue->tx.sring->rsp_prod;
		rmb(); /* Ensure we see responses up to 'rp'. */

		क्रम (cons = queue->tx.rsp_cons; cons != prod; cons++) अणु
			काष्ठा xen_netअगर_tx_response *txrsp;

			txrsp = RING_GET_RESPONSE(&queue->tx, cons);
			अगर (txrsp->status == XEN_NETIF_RSP_शून्य)
				जारी;

			id  = txrsp->id;
			skb = queue->tx_skbs[id].skb;
			अगर (unlikely(gnttab_query_क्रमeign_access(
				queue->grant_tx_ref[id]) != 0)) अणु
				pr_alert("%s: warning -- grant still in use by backend domain\n",
					 __func__);
				BUG();
			पूर्ण
			gnttab_end_क्रमeign_access_ref(
				queue->grant_tx_ref[id], GNTMAP_पढ़ोonly);
			gnttab_release_grant_reference(
				&queue->gref_tx_head, queue->grant_tx_ref[id]);
			queue->grant_tx_ref[id] = GRANT_INVALID_REF;
			queue->grant_tx_page[id] = शून्य;
			add_id_to_मुक्तlist(&queue->tx_skb_मुक्तlist, queue->tx_skbs, id);
			dev_kमुक्त_skb_irq(skb);
		पूर्ण

		queue->tx.rsp_cons = prod;

		RING_FINAL_CHECK_FOR_RESPONSES(&queue->tx, more_to_करो);
	पूर्ण जबतक (more_to_करो);

	xennet_maybe_wake_tx(queue);
पूर्ण

काष्ठा xennet_gnttab_make_txreq अणु
	काष्ठा netfront_queue *queue;
	काष्ठा sk_buff *skb;
	काष्ठा page *page;
	काष्ठा xen_netअगर_tx_request *tx; /* Last request */
	अचिन्हित पूर्णांक size;
पूर्ण;

अटल व्योम xennet_tx_setup_grant(अचिन्हित दीर्घ gfn, अचिन्हित पूर्णांक offset,
				  अचिन्हित पूर्णांक len, व्योम *data)
अणु
	काष्ठा xennet_gnttab_make_txreq *info = data;
	अचिन्हित पूर्णांक id;
	काष्ठा xen_netअगर_tx_request *tx;
	grant_ref_t ref;
	/* convenient aliases */
	काष्ठा page *page = info->page;
	काष्ठा netfront_queue *queue = info->queue;
	काष्ठा sk_buff *skb = info->skb;

	id = get_id_from_मुक्तlist(&queue->tx_skb_मुक्तlist, queue->tx_skbs);
	tx = RING_GET_REQUEST(&queue->tx, queue->tx.req_prod_pvt++);
	ref = gnttab_claim_grant_reference(&queue->gref_tx_head);
	WARN_ON_ONCE(IS_ERR_VALUE((अचिन्हित दीर्घ)(पूर्णांक)ref));

	gnttab_grant_क्रमeign_access_ref(ref, queue->info->xbdev->otherend_id,
					gfn, GNTMAP_पढ़ोonly);

	queue->tx_skbs[id].skb = skb;
	queue->grant_tx_page[id] = page;
	queue->grant_tx_ref[id] = ref;

	tx->id = id;
	tx->gref = ref;
	tx->offset = offset;
	tx->size = len;
	tx->flags = 0;

	info->tx = tx;
	info->size += tx->size;
पूर्ण

अटल काष्ठा xen_netअगर_tx_request *xennet_make_first_txreq(
	काष्ठा netfront_queue *queue, काष्ठा sk_buff *skb,
	काष्ठा page *page, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len)
अणु
	काष्ठा xennet_gnttab_make_txreq info = अणु
		.queue = queue,
		.skb = skb,
		.page = page,
		.size = 0,
	पूर्ण;

	gnttab_क्रम_one_grant(page, offset, len, xennet_tx_setup_grant, &info);

	वापस info.tx;
पूर्ण

अटल व्योम xennet_make_one_txreq(अचिन्हित दीर्घ gfn, अचिन्हित पूर्णांक offset,
				  अचिन्हित पूर्णांक len, व्योम *data)
अणु
	काष्ठा xennet_gnttab_make_txreq *info = data;

	info->tx->flags |= XEN_NETTXF_more_data;
	skb_get(info->skb);
	xennet_tx_setup_grant(gfn, offset, len, data);
पूर्ण

अटल काष्ठा xen_netअगर_tx_request *xennet_make_txreqs(
	काष्ठा netfront_queue *queue, काष्ठा xen_netअगर_tx_request *tx,
	काष्ठा sk_buff *skb, काष्ठा page *page,
	अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len)
अणु
	काष्ठा xennet_gnttab_make_txreq info = अणु
		.queue = queue,
		.skb = skb,
		.tx = tx,
	पूर्ण;

	/* Skip unused frames from start of page */
	page += offset >> PAGE_SHIFT;
	offset &= ~PAGE_MASK;

	जबतक (len) अणु
		info.page = page;
		info.size = 0;

		gnttab_क्रमeach_grant_in_range(page, offset, len,
					      xennet_make_one_txreq,
					      &info);

		page++;
		offset = 0;
		len -= info.size;
	पूर्ण

	वापस info.tx;
पूर्ण

/*
 * Count how many ring slots are required to send this skb. Each frag
 * might be a compound page.
 */
अटल पूर्णांक xennet_count_skb_slots(काष्ठा sk_buff *skb)
अणु
	पूर्णांक i, frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक slots;

	slots = gnttab_count_grant(offset_in_page(skb->data),
				   skb_headlen(skb));

	क्रम (i = 0; i < frags; i++) अणु
		skb_frag_t *frag = skb_shinfo(skb)->frags + i;
		अचिन्हित दीर्घ size = skb_frag_size(frag);
		अचिन्हित दीर्घ offset = skb_frag_off(frag);

		/* Skip unused frames from start of page */
		offset &= ~PAGE_MASK;

		slots += gnttab_count_grant(offset, size);
	पूर्ण

	वापस slots;
पूर्ण

अटल u16 xennet_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			       काष्ठा net_device *sb_dev)
अणु
	अचिन्हित पूर्णांक num_queues = dev->real_num_tx_queues;
	u32 hash;
	u16 queue_idx;

	/* First, check अगर there is only one queue */
	अगर (num_queues == 1) अणु
		queue_idx = 0;
	पूर्ण अन्यथा अणु
		hash = skb_get_hash(skb);
		queue_idx = hash % num_queues;
	पूर्ण

	वापस queue_idx;
पूर्ण

अटल पूर्णांक xennet_xdp_xmit_one(काष्ठा net_device *dev,
			       काष्ठा netfront_queue *queue,
			       काष्ठा xdp_frame *xdpf)
अणु
	काष्ठा netfront_info *np = netdev_priv(dev);
	काष्ठा netfront_stats *tx_stats = this_cpu_ptr(np->tx_stats);
	पूर्णांक notअगरy;

	xennet_make_first_txreq(queue, शून्य,
				virt_to_page(xdpf->data),
				offset_in_page(xdpf->data),
				xdpf->len);

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&queue->tx, notअगरy);
	अगर (notअगरy)
		notअगरy_remote_via_irq(queue->tx_irq);

	u64_stats_update_begin(&tx_stats->syncp);
	tx_stats->bytes += xdpf->len;
	tx_stats->packets++;
	u64_stats_update_end(&tx_stats->syncp);

	xennet_tx_buf_gc(queue);

	वापस 0;
पूर्ण

अटल पूर्णांक xennet_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n,
			   काष्ठा xdp_frame **frames, u32 flags)
अणु
	अचिन्हित पूर्णांक num_queues = dev->real_num_tx_queues;
	काष्ठा netfront_info *np = netdev_priv(dev);
	काष्ठा netfront_queue *queue = शून्य;
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक nxmit = 0;
	पूर्णांक i;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	queue = &np->queues[smp_processor_id() % num_queues];

	spin_lock_irqsave(&queue->tx_lock, irq_flags);
	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *xdpf = frames[i];

		अगर (!xdpf)
			जारी;
		अगर (xennet_xdp_xmit_one(dev, queue, xdpf))
			अवरोध;
		nxmit++;
	पूर्ण
	spin_unlock_irqrestore(&queue->tx_lock, irq_flags);

	वापस nxmit;
पूर्ण


#घोषणा MAX_XEN_SKB_FRAGS (65536 / XEN_PAGE_SIZE + 1)

अटल netdev_tx_t xennet_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा netfront_info *np = netdev_priv(dev);
	काष्ठा netfront_stats *tx_stats = this_cpu_ptr(np->tx_stats);
	काष्ठा xen_netअगर_tx_request *tx, *first_tx;
	अचिन्हित पूर्णांक i;
	पूर्णांक notअगरy;
	पूर्णांक slots;
	काष्ठा page *page;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ flags;
	काष्ठा netfront_queue *queue = शून्य;
	अचिन्हित पूर्णांक num_queues = dev->real_num_tx_queues;
	u16 queue_index;
	काष्ठा sk_buff *nskb;

	/* Drop the packet अगर no queues are set up */
	अगर (num_queues < 1)
		जाओ drop;
	/* Determine which queue to transmit this SKB on */
	queue_index = skb_get_queue_mapping(skb);
	queue = &np->queues[queue_index];

	/* If skb->len is too big क्रम wire क्रमmat, drop skb and alert
	 * user about misconfiguration.
	 */
	अगर (unlikely(skb->len > XEN_NETIF_MAX_TX_SIZE)) अणु
		net_alert_ratelimited(
			"xennet: skb->len = %u, too big for wire format\n",
			skb->len);
		जाओ drop;
	पूर्ण

	slots = xennet_count_skb_slots(skb);
	अगर (unlikely(slots > MAX_XEN_SKB_FRAGS + 1)) अणु
		net_dbg_ratelimited("xennet: skb rides the rocket: %d slots, %d bytes\n",
				    slots, skb->len);
		अगर (skb_linearize(skb))
			जाओ drop;
	पूर्ण

	page = virt_to_page(skb->data);
	offset = offset_in_page(skb->data);

	/* The first req should be at least ETH_HLEN size or the packet will be
	 * dropped by netback.
	 */
	अगर (unlikely(PAGE_SIZE - offset < ETH_HLEN)) अणु
		nskb = skb_copy(skb, GFP_ATOMIC);
		अगर (!nskb)
			जाओ drop;
		dev_consume_skb_any(skb);
		skb = nskb;
		page = virt_to_page(skb->data);
		offset = offset_in_page(skb->data);
	पूर्ण

	len = skb_headlen(skb);

	spin_lock_irqsave(&queue->tx_lock, flags);

	अगर (unlikely(!netअगर_carrier_ok(dev) ||
		     (slots > 1 && !xennet_can_sg(dev)) ||
		     netअगर_needs_gso(skb, netअगर_skb_features(skb)))) अणु
		spin_unlock_irqrestore(&queue->tx_lock, flags);
		जाओ drop;
	पूर्ण

	/* First request क्रम the linear area. */
	first_tx = tx = xennet_make_first_txreq(queue, skb,
						page, offset, len);
	offset += tx->size;
	अगर (offset == PAGE_SIZE) अणु
		page++;
		offset = 0;
	पूर्ण
	len -= tx->size;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		/* local packet? */
		tx->flags |= XEN_NETTXF_csum_blank | XEN_NETTXF_data_validated;
	अन्यथा अगर (skb->ip_summed == CHECKSUM_UNNECESSARY)
		/* remote but checksummed. */
		tx->flags |= XEN_NETTXF_data_validated;

	/* Optional extra info after the first request. */
	अगर (skb_shinfo(skb)->gso_size) अणु
		काष्ठा xen_netअगर_extra_info *gso;

		gso = (काष्ठा xen_netअगर_extra_info *)
			RING_GET_REQUEST(&queue->tx, queue->tx.req_prod_pvt++);

		tx->flags |= XEN_NETTXF_extra_info;

		gso->u.gso.size = skb_shinfo(skb)->gso_size;
		gso->u.gso.type = (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6) ?
			XEN_NETIF_GSO_TYPE_TCPV6 :
			XEN_NETIF_GSO_TYPE_TCPV4;
		gso->u.gso.pad = 0;
		gso->u.gso.features = 0;

		gso->type = XEN_NETIF_EXTRA_TYPE_GSO;
		gso->flags = 0;
	पूर्ण

	/* Requests क्रम the rest of the linear area. */
	tx = xennet_make_txreqs(queue, tx, skb, page, offset, len);

	/* Requests क्रम all the frags. */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		tx = xennet_make_txreqs(queue, tx, skb, skb_frag_page(frag),
					skb_frag_off(frag),
					skb_frag_size(frag));
	पूर्ण

	/* First request has the packet length. */
	first_tx->size = skb->len;

	/* बारtamp packet in software */
	skb_tx_बारtamp(skb);

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&queue->tx, notअगरy);
	अगर (notअगरy)
		notअगरy_remote_via_irq(queue->tx_irq);

	u64_stats_update_begin(&tx_stats->syncp);
	tx_stats->bytes += skb->len;
	tx_stats->packets++;
	u64_stats_update_end(&tx_stats->syncp);

	/* Note: It is not safe to access skb after xennet_tx_buf_gc()! */
	xennet_tx_buf_gc(queue);

	अगर (!netfront_tx_slot_available(queue))
		netअगर_tx_stop_queue(netdev_get_tx_queue(dev, queue->id));

	spin_unlock_irqrestore(&queue->tx_lock, flags);

	वापस NETDEV_TX_OK;

 drop:
	dev->stats.tx_dropped++;
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक xennet_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा netfront_info *np = netdev_priv(dev);
	अचिन्हित पूर्णांक num_queues = dev->real_num_tx_queues;
	अचिन्हित पूर्णांक i;
	काष्ठा netfront_queue *queue;
	netअगर_tx_stop_all_queues(np->netdev);
	क्रम (i = 0; i < num_queues; ++i) अणु
		queue = &np->queues[i];
		napi_disable(&queue->napi);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम xennet_move_rx_slot(काष्ठा netfront_queue *queue, काष्ठा sk_buff *skb,
				grant_ref_t ref)
अणु
	पूर्णांक new = xennet_rxidx(queue->rx.req_prod_pvt);

	BUG_ON(queue->rx_skbs[new]);
	queue->rx_skbs[new] = skb;
	queue->grant_rx_ref[new] = ref;
	RING_GET_REQUEST(&queue->rx, queue->rx.req_prod_pvt)->id = new;
	RING_GET_REQUEST(&queue->rx, queue->rx.req_prod_pvt)->gref = ref;
	queue->rx.req_prod_pvt++;
पूर्ण

अटल पूर्णांक xennet_get_extras(काष्ठा netfront_queue *queue,
			     काष्ठा xen_netअगर_extra_info *extras,
			     RING_IDX rp)

अणु
	काष्ठा xen_netअगर_extra_info *extra;
	काष्ठा device *dev = &queue->info->netdev->dev;
	RING_IDX cons = queue->rx.rsp_cons;
	पूर्णांक err = 0;

	करो अणु
		काष्ठा sk_buff *skb;
		grant_ref_t ref;

		अगर (unlikely(cons + 1 == rp)) अणु
			अगर (net_ratelimit())
				dev_warn(dev, "Missing extra info\n");
			err = -EBADR;
			अवरोध;
		पूर्ण

		extra = (काष्ठा xen_netअगर_extra_info *)
			RING_GET_RESPONSE(&queue->rx, ++cons);

		अगर (unlikely(!extra->type ||
			     extra->type >= XEN_NETIF_EXTRA_TYPE_MAX)) अणु
			अगर (net_ratelimit())
				dev_warn(dev, "Invalid extra type: %d\n",
					extra->type);
			err = -EINVAL;
		पूर्ण अन्यथा अणु
			स_नकल(&extras[extra->type - 1], extra,
			       माप(*extra));
		पूर्ण

		skb = xennet_get_rx_skb(queue, cons);
		ref = xennet_get_rx_ref(queue, cons);
		xennet_move_rx_slot(queue, skb, ref);
	पूर्ण जबतक (extra->flags & XEN_NETIF_EXTRA_FLAG_MORE);

	queue->rx.rsp_cons = cons;
	वापस err;
पूर्ण

अटल u32 xennet_run_xdp(काष्ठा netfront_queue *queue, काष्ठा page *pdata,
		   काष्ठा xen_netअगर_rx_response *rx, काष्ठा bpf_prog *prog,
		   काष्ठा xdp_buff *xdp, bool *need_xdp_flush)
अणु
	काष्ठा xdp_frame *xdpf;
	u32 len = rx->status;
	u32 act;
	पूर्णांक err;

	xdp_init_buff(xdp, XEN_PAGE_SIZE - XDP_PACKET_HEADROOM,
		      &queue->xdp_rxq);
	xdp_prepare_buff(xdp, page_address(pdata), XDP_PACKET_HEADROOM,
			 len, false);

	act = bpf_prog_run_xdp(prog, xdp);
	चयन (act) अणु
	हाल XDP_TX:
		get_page(pdata);
		xdpf = xdp_convert_buff_to_frame(xdp);
		err = xennet_xdp_xmit(queue->info->netdev, 1, &xdpf, 0);
		अगर (unlikely(!err))
			xdp_वापस_frame_rx_napi(xdpf);
		अन्यथा अगर (unlikely(err < 0))
			trace_xdp_exception(queue->info->netdev, prog, act);
		अवरोध;
	हाल XDP_REसूचीECT:
		get_page(pdata);
		err = xdp_करो_redirect(queue->info->netdev, xdp, prog);
		*need_xdp_flush = true;
		अगर (unlikely(err))
			trace_xdp_exception(queue->info->netdev, prog, act);
		अवरोध;
	हाल XDP_PASS:
	हाल XDP_DROP:
		अवरोध;

	हाल XDP_ABORTED:
		trace_xdp_exception(queue->info->netdev, prog, act);
		अवरोध;

	शेष:
		bpf_warn_invalid_xdp_action(act);
	पूर्ण

	वापस act;
पूर्ण

अटल पूर्णांक xennet_get_responses(काष्ठा netfront_queue *queue,
				काष्ठा netfront_rx_info *rinfo, RING_IDX rp,
				काष्ठा sk_buff_head *list,
				bool *need_xdp_flush)
अणु
	काष्ठा xen_netअगर_rx_response *rx = &rinfo->rx;
	पूर्णांक max = XEN_NETIF_NR_SLOTS_MIN + (rx->status <= RX_COPY_THRESHOLD);
	RING_IDX cons = queue->rx.rsp_cons;
	काष्ठा sk_buff *skb = xennet_get_rx_skb(queue, cons);
	काष्ठा xen_netअगर_extra_info *extras = rinfo->extras;
	grant_ref_t ref = xennet_get_rx_ref(queue, cons);
	काष्ठा device *dev = &queue->info->netdev->dev;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा xdp_buff xdp;
	अचिन्हित दीर्घ ret;
	पूर्णांक slots = 1;
	पूर्णांक err = 0;
	u32 verdict;

	अगर (rx->flags & XEN_NETRXF_extra_info) अणु
		err = xennet_get_extras(queue, extras, rp);
		अगर (!err) अणु
			अगर (extras[XEN_NETIF_EXTRA_TYPE_XDP - 1].type) अणु
				काष्ठा xen_netअगर_extra_info *xdp;

				xdp = &extras[XEN_NETIF_EXTRA_TYPE_XDP - 1];
				rx->offset = xdp->u.xdp.headroom;
			पूर्ण
		पूर्ण
		cons = queue->rx.rsp_cons;
	पूर्ण

	क्रम (;;) अणु
		अगर (unlikely(rx->status < 0 ||
			     rx->offset + rx->status > XEN_PAGE_SIZE)) अणु
			अगर (net_ratelimit())
				dev_warn(dev, "rx->offset: %u, size: %d\n",
					 rx->offset, rx->status);
			xennet_move_rx_slot(queue, skb, ref);
			err = -EINVAL;
			जाओ next;
		पूर्ण

		/*
		 * This definitely indicates a bug, either in this driver or in
		 * the backend driver. In future this should flag the bad
		 * situation to the प्रणाली controller to reboot the backend.
		 */
		अगर (ref == GRANT_INVALID_REF) अणु
			अगर (net_ratelimit())
				dev_warn(dev, "Bad rx response id %d.\n",
					 rx->id);
			err = -EINVAL;
			जाओ next;
		पूर्ण

		ret = gnttab_end_क्रमeign_access_ref(ref, 0);
		BUG_ON(!ret);

		gnttab_release_grant_reference(&queue->gref_rx_head, ref);

		rcu_पढ़ो_lock();
		xdp_prog = rcu_dereference(queue->xdp_prog);
		अगर (xdp_prog) अणु
			अगर (!(rx->flags & XEN_NETRXF_more_data)) अणु
				/* currently only a single page contains data */
				verdict = xennet_run_xdp(queue,
							 skb_frag_page(&skb_shinfo(skb)->frags[0]),
							 rx, xdp_prog, &xdp, need_xdp_flush);
				अगर (verdict != XDP_PASS)
					err = -EINVAL;
			पूर्ण अन्यथा अणु
				/* drop the frame */
				err = -EINVAL;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
next:
		__skb_queue_tail(list, skb);
		अगर (!(rx->flags & XEN_NETRXF_more_data))
			अवरोध;

		अगर (cons + slots == rp) अणु
			अगर (net_ratelimit())
				dev_warn(dev, "Need more slots\n");
			err = -ENOENT;
			अवरोध;
		पूर्ण

		rx = RING_GET_RESPONSE(&queue->rx, cons + slots);
		skb = xennet_get_rx_skb(queue, cons + slots);
		ref = xennet_get_rx_ref(queue, cons + slots);
		slots++;
	पूर्ण

	अगर (unlikely(slots > max)) अणु
		अगर (net_ratelimit())
			dev_warn(dev, "Too many slots\n");
		err = -E2BIG;
	पूर्ण

	अगर (unlikely(err))
		queue->rx.rsp_cons = cons + slots;

	वापस err;
पूर्ण

अटल पूर्णांक xennet_set_skb_gso(काष्ठा sk_buff *skb,
			      काष्ठा xen_netअगर_extra_info *gso)
अणु
	अगर (!gso->u.gso.size) अणु
		अगर (net_ratelimit())
			pr_warn("GSO size must not be zero\n");
		वापस -EINVAL;
	पूर्ण

	अगर (gso->u.gso.type != XEN_NETIF_GSO_TYPE_TCPV4 &&
	    gso->u.gso.type != XEN_NETIF_GSO_TYPE_TCPV6) अणु
		अगर (net_ratelimit())
			pr_warn("Bad GSO type %d\n", gso->u.gso.type);
		वापस -EINVAL;
	पूर्ण

	skb_shinfo(skb)->gso_size = gso->u.gso.size;
	skb_shinfo(skb)->gso_type =
		(gso->u.gso.type == XEN_NETIF_GSO_TYPE_TCPV4) ?
		SKB_GSO_TCPV4 :
		SKB_GSO_TCPV6;

	/* Header must be checked, and gso_segs computed. */
	skb_shinfo(skb)->gso_type |= SKB_GSO_DODGY;
	skb_shinfo(skb)->gso_segs = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक xennet_fill_frags(काष्ठा netfront_queue *queue,
			     काष्ठा sk_buff *skb,
			     काष्ठा sk_buff_head *list)
अणु
	RING_IDX cons = queue->rx.rsp_cons;
	काष्ठा sk_buff *nskb;

	जबतक ((nskb = __skb_dequeue(list))) अणु
		काष्ठा xen_netअगर_rx_response *rx =
			RING_GET_RESPONSE(&queue->rx, ++cons);
		skb_frag_t *nfrag = &skb_shinfo(nskb)->frags[0];

		अगर (skb_shinfo(skb)->nr_frags == MAX_SKB_FRAGS) अणु
			अचिन्हित पूर्णांक pull_to = NETFRONT_SKB_CB(skb)->pull_to;

			BUG_ON(pull_to < skb_headlen(skb));
			__pskb_pull_tail(skb, pull_to - skb_headlen(skb));
		पूर्ण
		अगर (unlikely(skb_shinfo(skb)->nr_frags >= MAX_SKB_FRAGS)) अणु
			queue->rx.rsp_cons = ++cons + skb_queue_len(list);
			kमुक्त_skb(nskb);
			वापस -ENOENT;
		पूर्ण

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
				skb_frag_page(nfrag),
				rx->offset, rx->status, PAGE_SIZE);

		skb_shinfo(nskb)->nr_frags = 0;
		kमुक्त_skb(nskb);
	पूर्ण

	queue->rx.rsp_cons = cons;

	वापस 0;
पूर्ण

अटल पूर्णांक checksum_setup(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	bool recalculate_partial_csum = false;

	/*
	 * A GSO SKB must be CHECKSUM_PARTIAL. However some buggy
	 * peers can fail to set NETRXF_csum_blank when sending a GSO
	 * frame. In this हाल क्रमce the SKB to CHECKSUM_PARTIAL and
	 * recalculate the partial checksum.
	 */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL && skb_is_gso(skb)) अणु
		काष्ठा netfront_info *np = netdev_priv(dev);
		atomic_inc(&np->rx_gso_checksum_fixup);
		skb->ip_summed = CHECKSUM_PARTIAL;
		recalculate_partial_csum = true;
	पूर्ण

	/* A non-CHECKSUM_PARTIAL SKB करोes not require setup. */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	वापस skb_checksum_setup(skb, recalculate_partial_csum);
पूर्ण

अटल पूर्णांक handle_incoming_queue(काष्ठा netfront_queue *queue,
				 काष्ठा sk_buff_head *rxq)
अणु
	काष्ठा netfront_stats *rx_stats = this_cpu_ptr(queue->info->rx_stats);
	पूर्णांक packets_dropped = 0;
	काष्ठा sk_buff *skb;

	जबतक ((skb = __skb_dequeue(rxq)) != शून्य) अणु
		पूर्णांक pull_to = NETFRONT_SKB_CB(skb)->pull_to;

		अगर (pull_to > skb_headlen(skb))
			__pskb_pull_tail(skb, pull_to - skb_headlen(skb));

		/* Ethernet work: Delayed to here as it peeks the header. */
		skb->protocol = eth_type_trans(skb, queue->info->netdev);
		skb_reset_network_header(skb);

		अगर (checksum_setup(queue->info->netdev, skb)) अणु
			kमुक्त_skb(skb);
			packets_dropped++;
			queue->info->netdev->stats.rx_errors++;
			जारी;
		पूर्ण

		u64_stats_update_begin(&rx_stats->syncp);
		rx_stats->packets++;
		rx_stats->bytes += skb->len;
		u64_stats_update_end(&rx_stats->syncp);

		/* Pass it up. */
		napi_gro_receive(&queue->napi, skb);
	पूर्ण

	वापस packets_dropped;
पूर्ण

अटल पूर्णांक xennet_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा netfront_queue *queue = container_of(napi, काष्ठा netfront_queue, napi);
	काष्ठा net_device *dev = queue->info->netdev;
	काष्ठा sk_buff *skb;
	काष्ठा netfront_rx_info rinfo;
	काष्ठा xen_netअगर_rx_response *rx = &rinfo.rx;
	काष्ठा xen_netअगर_extra_info *extras = rinfo.extras;
	RING_IDX i, rp;
	पूर्णांक work_करोne;
	काष्ठा sk_buff_head rxq;
	काष्ठा sk_buff_head errq;
	काष्ठा sk_buff_head पंचांगpq;
	पूर्णांक err;
	bool need_xdp_flush = false;

	spin_lock(&queue->rx_lock);

	skb_queue_head_init(&rxq);
	skb_queue_head_init(&errq);
	skb_queue_head_init(&पंचांगpq);

	rp = queue->rx.sring->rsp_prod;
	rmb(); /* Ensure we see queued responses up to 'rp'. */

	i = queue->rx.rsp_cons;
	work_करोne = 0;
	जबतक ((i != rp) && (work_करोne < budget)) अणु
		स_नकल(rx, RING_GET_RESPONSE(&queue->rx, i), माप(*rx));
		स_रखो(extras, 0, माप(rinfo.extras));

		err = xennet_get_responses(queue, &rinfo, rp, &पंचांगpq,
					   &need_xdp_flush);

		अगर (unlikely(err)) अणु
err:
			जबतक ((skb = __skb_dequeue(&पंचांगpq)))
				__skb_queue_tail(&errq, skb);
			dev->stats.rx_errors++;
			i = queue->rx.rsp_cons;
			जारी;
		पूर्ण

		skb = __skb_dequeue(&पंचांगpq);

		अगर (extras[XEN_NETIF_EXTRA_TYPE_GSO - 1].type) अणु
			काष्ठा xen_netअगर_extra_info *gso;
			gso = &extras[XEN_NETIF_EXTRA_TYPE_GSO - 1];

			अगर (unlikely(xennet_set_skb_gso(skb, gso))) अणु
				__skb_queue_head(&पंचांगpq, skb);
				queue->rx.rsp_cons += skb_queue_len(&पंचांगpq);
				जाओ err;
			पूर्ण
		पूर्ण

		NETFRONT_SKB_CB(skb)->pull_to = rx->status;
		अगर (NETFRONT_SKB_CB(skb)->pull_to > RX_COPY_THRESHOLD)
			NETFRONT_SKB_CB(skb)->pull_to = RX_COPY_THRESHOLD;

		skb_frag_off_set(&skb_shinfo(skb)->frags[0], rx->offset);
		skb_frag_size_set(&skb_shinfo(skb)->frags[0], rx->status);
		skb->data_len = rx->status;
		skb->len += rx->status;

		अगर (unlikely(xennet_fill_frags(queue, skb, &पंचांगpq)))
			जाओ err;

		अगर (rx->flags & XEN_NETRXF_csum_blank)
			skb->ip_summed = CHECKSUM_PARTIAL;
		अन्यथा अगर (rx->flags & XEN_NETRXF_data_validated)
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		__skb_queue_tail(&rxq, skb);

		i = ++queue->rx.rsp_cons;
		work_करोne++;
	पूर्ण
	अगर (need_xdp_flush)
		xdp_करो_flush();

	__skb_queue_purge(&errq);

	work_करोne -= handle_incoming_queue(queue, &rxq);

	xennet_alloc_rx_buffers(queue);

	अगर (work_करोne < budget) अणु
		पूर्णांक more_to_करो = 0;

		napi_complete_करोne(napi, work_करोne);

		RING_FINAL_CHECK_FOR_RESPONSES(&queue->rx, more_to_करो);
		अगर (more_to_करो)
			napi_schedule(napi);
	पूर्ण

	spin_unlock(&queue->rx_lock);

	वापस work_करोne;
पूर्ण

अटल पूर्णांक xennet_change_mtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	पूर्णांक max = xennet_can_sg(dev) ? XEN_NETIF_MAX_TX_SIZE : ETH_DATA_LEN;

	अगर (mtu > max)
		वापस -EINVAL;
	dev->mtu = mtu;
	वापस 0;
पूर्ण

अटल व्योम xennet_get_stats64(काष्ठा net_device *dev,
			       काष्ठा rtnl_link_stats64 *tot)
अणु
	काष्ठा netfront_info *np = netdev_priv(dev);
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा netfront_stats *rx_stats = per_cpu_ptr(np->rx_stats, cpu);
		काष्ठा netfront_stats *tx_stats = per_cpu_ptr(np->tx_stats, cpu);
		u64 rx_packets, rx_bytes, tx_packets, tx_bytes;
		अचिन्हित पूर्णांक start;

		करो अणु
			start = u64_stats_fetch_begin_irq(&tx_stats->syncp);
			tx_packets = tx_stats->packets;
			tx_bytes = tx_stats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&tx_stats->syncp, start));

		करो अणु
			start = u64_stats_fetch_begin_irq(&rx_stats->syncp);
			rx_packets = rx_stats->packets;
			rx_bytes = rx_stats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&rx_stats->syncp, start));

		tot->rx_packets += rx_packets;
		tot->tx_packets += tx_packets;
		tot->rx_bytes   += rx_bytes;
		tot->tx_bytes   += tx_bytes;
	पूर्ण

	tot->rx_errors  = dev->stats.rx_errors;
	tot->tx_dropped = dev->stats.tx_dropped;
पूर्ण

अटल व्योम xennet_release_tx_bufs(काष्ठा netfront_queue *queue)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < NET_TX_RING_SIZE; i++) अणु
		/* Skip over entries which are actually मुक्तlist references */
		अगर (skb_entry_is_link(&queue->tx_skbs[i]))
			जारी;

		skb = queue->tx_skbs[i].skb;
		get_page(queue->grant_tx_page[i]);
		gnttab_end_क्रमeign_access(queue->grant_tx_ref[i],
					  GNTMAP_पढ़ोonly,
					  (अचिन्हित दीर्घ)page_address(queue->grant_tx_page[i]));
		queue->grant_tx_page[i] = शून्य;
		queue->grant_tx_ref[i] = GRANT_INVALID_REF;
		add_id_to_मुक्तlist(&queue->tx_skb_मुक्तlist, queue->tx_skbs, i);
		dev_kमुक्त_skb_irq(skb);
	पूर्ण
पूर्ण

अटल व्योम xennet_release_rx_bufs(काष्ठा netfront_queue *queue)
अणु
	पूर्णांक id, ref;

	spin_lock_bh(&queue->rx_lock);

	क्रम (id = 0; id < NET_RX_RING_SIZE; id++) अणु
		काष्ठा sk_buff *skb;
		काष्ठा page *page;

		skb = queue->rx_skbs[id];
		अगर (!skb)
			जारी;

		ref = queue->grant_rx_ref[id];
		अगर (ref == GRANT_INVALID_REF)
			जारी;

		page = skb_frag_page(&skb_shinfo(skb)->frags[0]);

		/* gnttab_end_क्रमeign_access() needs a page ref until
		 * क्रमeign access is ended (which may be deferred).
		 */
		get_page(page);
		gnttab_end_क्रमeign_access(ref, 0,
					  (अचिन्हित दीर्घ)page_address(page));
		queue->grant_rx_ref[id] = GRANT_INVALID_REF;

		kमुक्त_skb(skb);
	पूर्ण

	spin_unlock_bh(&queue->rx_lock);
पूर्ण

अटल netdev_features_t xennet_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा netfront_info *np = netdev_priv(dev);

	अगर (features & NETIF_F_SG &&
	    !xenbus_पढ़ो_अचिन्हित(np->xbdev->otherend, "feature-sg", 0))
		features &= ~NETIF_F_SG;

	अगर (features & NETIF_F_IPV6_CSUM &&
	    !xenbus_पढ़ो_अचिन्हित(np->xbdev->otherend,
				  "feature-ipv6-csum-offload", 0))
		features &= ~NETIF_F_IPV6_CSUM;

	अगर (features & NETIF_F_TSO &&
	    !xenbus_पढ़ो_अचिन्हित(np->xbdev->otherend, "feature-gso-tcpv4", 0))
		features &= ~NETIF_F_TSO;

	अगर (features & NETIF_F_TSO6 &&
	    !xenbus_पढ़ो_अचिन्हित(np->xbdev->otherend, "feature-gso-tcpv6", 0))
		features &= ~NETIF_F_TSO6;

	वापस features;
पूर्ण

अटल पूर्णांक xennet_set_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	अगर (!(features & NETIF_F_SG) && dev->mtu > ETH_DATA_LEN) अणु
		netdev_info(dev, "Reducing MTU because no SG offload");
		dev->mtu = ETH_DATA_LEN;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t xennet_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा netfront_queue *queue = dev_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&queue->tx_lock, flags);
	xennet_tx_buf_gc(queue);
	spin_unlock_irqrestore(&queue->tx_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t xennet_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा netfront_queue *queue = dev_id;
	काष्ठा net_device *dev = queue->info->netdev;

	अगर (likely(netअगर_carrier_ok(dev) &&
		   RING_HAS_UNCONSUMED_RESPONSES(&queue->rx)))
		napi_schedule(&queue->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t xennet_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	xennet_tx_पूर्णांकerrupt(irq, dev_id);
	xennet_rx_पूर्णांकerrupt(irq, dev_id);
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम xennet_poll_controller(काष्ठा net_device *dev)
अणु
	/* Poll each queue */
	काष्ठा netfront_info *info = netdev_priv(dev);
	अचिन्हित पूर्णांक num_queues = dev->real_num_tx_queues;
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < num_queues; ++i)
		xennet_पूर्णांकerrupt(0, &info->queues[i]);
पूर्ण
#पूर्ण_अगर

#घोषणा NETBACK_XDP_HEADROOM_DISABLE	0
#घोषणा NETBACK_XDP_HEADROOM_ENABLE	1

अटल पूर्णांक talk_to_netback_xdp(काष्ठा netfront_info *np, पूर्णांक xdp)
अणु
	पूर्णांक err;
	अचिन्हित लघु headroom;

	headroom = xdp ? XDP_PACKET_HEADROOM : 0;
	err = xenbus_म_लिखो(XBT_NIL, np->xbdev->nodename,
			    "xdp-headroom", "%hu",
			    headroom);
	अगर (err)
		pr_warn("Error writing xdp-headroom\n");

	वापस err;
पूर्ण

अटल पूर्णांक xennet_xdp_set(काष्ठा net_device *dev, काष्ठा bpf_prog *prog,
			  काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित दीर्घ max_mtu = XEN_PAGE_SIZE - XDP_PACKET_HEADROOM;
	काष्ठा netfront_info *np = netdev_priv(dev);
	काष्ठा bpf_prog *old_prog;
	अचिन्हित पूर्णांक i, err;

	अगर (dev->mtu > max_mtu) अणु
		netdev_warn(dev, "XDP requires MTU less than %lu\n", max_mtu);
		वापस -EINVAL;
	पूर्ण

	अगर (!np->netback_has_xdp_headroom)
		वापस 0;

	xenbus_चयन_state(np->xbdev, XenbusStateReconfiguring);

	err = talk_to_netback_xdp(np, prog ? NETBACK_XDP_HEADROOM_ENABLE :
				  NETBACK_XDP_HEADROOM_DISABLE);
	अगर (err)
		वापस err;

	/* aव्योम the race with XDP headroom adjusपंचांगent */
	रुको_event(module_wq,
		   xenbus_पढ़ो_driver_state(np->xbdev->otherend) ==
		   XenbusStateReconfigured);
	np->netfront_xdp_enabled = true;

	old_prog = rtnl_dereference(np->queues[0].xdp_prog);

	अगर (prog)
		bpf_prog_add(prog, dev->real_num_tx_queues);

	क्रम (i = 0; i < dev->real_num_tx_queues; ++i)
		rcu_assign_poपूर्णांकer(np->queues[i].xdp_prog, prog);

	अगर (old_prog)
		क्रम (i = 0; i < dev->real_num_tx_queues; ++i)
			bpf_prog_put(old_prog);

	xenbus_चयन_state(np->xbdev, XenbusStateConnected);

	वापस 0;
पूर्ण

अटल पूर्णांक xennet_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस xennet_xdp_set(dev, xdp->prog, xdp->extack);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops xennet_netdev_ops = अणु
	.nकरो_खोलो            = xennet_खोलो,
	.nकरो_stop            = xennet_बंद,
	.nकरो_start_xmit      = xennet_start_xmit,
	.nकरो_change_mtu	     = xennet_change_mtu,
	.nकरो_get_stats64     = xennet_get_stats64,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_validate_addr   = eth_validate_addr,
	.nकरो_fix_features    = xennet_fix_features,
	.nकरो_set_features    = xennet_set_features,
	.nकरो_select_queue    = xennet_select_queue,
	.nकरो_bpf            = xennet_xdp,
	.nकरो_xdp_xmit	    = xennet_xdp_xmit,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = xennet_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल व्योम xennet_मुक्त_netdev(काष्ठा net_device *netdev)
अणु
	काष्ठा netfront_info *np = netdev_priv(netdev);

	मुक्त_percpu(np->rx_stats);
	मुक्त_percpu(np->tx_stats);
	मुक्त_netdev(netdev);
पूर्ण

अटल काष्ठा net_device *xennet_create_dev(काष्ठा xenbus_device *dev)
अणु
	पूर्णांक err;
	काष्ठा net_device *netdev;
	काष्ठा netfront_info *np;

	netdev = alloc_etherdev_mq(माप(काष्ठा netfront_info), xennet_max_queues);
	अगर (!netdev)
		वापस ERR_PTR(-ENOMEM);

	np                   = netdev_priv(netdev);
	np->xbdev            = dev;

	np->queues = शून्य;

	err = -ENOMEM;
	np->rx_stats = netdev_alloc_pcpu_stats(काष्ठा netfront_stats);
	अगर (np->rx_stats == शून्य)
		जाओ निकास;
	np->tx_stats = netdev_alloc_pcpu_stats(काष्ठा netfront_stats);
	अगर (np->tx_stats == शून्य)
		जाओ निकास;

	netdev->netdev_ops	= &xennet_netdev_ops;

	netdev->features        = NETIF_F_IP_CSUM | NETIF_F_RXCSUM |
				  NETIF_F_GSO_ROBUST;
	netdev->hw_features	= NETIF_F_SG |
				  NETIF_F_IPV6_CSUM |
				  NETIF_F_TSO | NETIF_F_TSO6;

	/*
         * Assume that all hw features are available क्रम now. This set
         * will be adjusted by the call to netdev_update_features() in
         * xennet_connect() which is the earliest poपूर्णांक where we can
         * negotiate with the backend regarding supported features.
         */
	netdev->features |= netdev->hw_features;

	netdev->ethtool_ops = &xennet_ethtool_ops;
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = XEN_NETIF_MAX_TX_SIZE;
	SET_NETDEV_DEV(netdev, &dev->dev);

	np->netdev = netdev;
	np->netfront_xdp_enabled = false;

	netअगर_carrier_off(netdev);

	करो अणु
		xenbus_चयन_state(dev, XenbusStateInitialising);
		err = रुको_event_समयout(module_wq,
				 xenbus_पढ़ो_driver_state(dev->otherend) !=
				 XenbusStateClosed &&
				 xenbus_पढ़ो_driver_state(dev->otherend) !=
				 XenbusStateUnknown, XENNET_TIMEOUT);
	पूर्ण जबतक (!err);

	वापस netdev;

 निकास:
	xennet_मुक्त_netdev(netdev);
	वापस ERR_PTR(err);
पूर्ण

/*
 * Entry poपूर्णांक to this code when a new device is created.  Allocate the basic
 * काष्ठाures and the ring buffers क्रम communication with the backend, and
 * inक्रमm the backend of the appropriate details क्रम those.
 */
अटल पूर्णांक netfront_probe(काष्ठा xenbus_device *dev,
			  स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा net_device *netdev;
	काष्ठा netfront_info *info;

	netdev = xennet_create_dev(dev);
	अगर (IS_ERR(netdev)) अणु
		err = PTR_ERR(netdev);
		xenbus_dev_fatal(dev, err, "creating netdev");
		वापस err;
	पूर्ण

	info = netdev_priv(netdev);
	dev_set_drvdata(&dev->dev, info);
#अगर_घोषित CONFIG_SYSFS
	info->netdev->sysfs_groups[0] = &xennet_dev_group;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम xennet_end_access(पूर्णांक ref, व्योम *page)
अणु
	/* This मुक्तs the page as a side-effect */
	अगर (ref != GRANT_INVALID_REF)
		gnttab_end_क्रमeign_access(ref, 0, (अचिन्हित दीर्घ)page);
पूर्ण

अटल व्योम xennet_disconnect_backend(काष्ठा netfront_info *info)
अणु
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक num_queues = info->netdev->real_num_tx_queues;

	netअगर_carrier_off(info->netdev);

	क्रम (i = 0; i < num_queues && info->queues; ++i) अणु
		काष्ठा netfront_queue *queue = &info->queues[i];

		del_समयr_sync(&queue->rx_refill_समयr);

		अगर (queue->tx_irq && (queue->tx_irq == queue->rx_irq))
			unbind_from_irqhandler(queue->tx_irq, queue);
		अगर (queue->tx_irq && (queue->tx_irq != queue->rx_irq)) अणु
			unbind_from_irqhandler(queue->tx_irq, queue);
			unbind_from_irqhandler(queue->rx_irq, queue);
		पूर्ण
		queue->tx_evtchn = queue->rx_evtchn = 0;
		queue->tx_irq = queue->rx_irq = 0;

		अगर (netअगर_running(info->netdev))
			napi_synchronize(&queue->napi);

		xennet_release_tx_bufs(queue);
		xennet_release_rx_bufs(queue);
		gnttab_मुक्त_grant_references(queue->gref_tx_head);
		gnttab_मुक्त_grant_references(queue->gref_rx_head);

		/* End access and मुक्त the pages */
		xennet_end_access(queue->tx_ring_ref, queue->tx.sring);
		xennet_end_access(queue->rx_ring_ref, queue->rx.sring);

		queue->tx_ring_ref = GRANT_INVALID_REF;
		queue->rx_ring_ref = GRANT_INVALID_REF;
		queue->tx.sring = शून्य;
		queue->rx.sring = शून्य;

		page_pool_destroy(queue->page_pool);
	पूर्ण
पूर्ण

/*
 * We are reconnecting to the backend, due to a suspend/resume, or a backend
 * driver restart.  We tear करोwn our netअगर काष्ठाure and recreate it, but
 * leave the device-layer काष्ठाures पूर्णांकact so that this is transparent to the
 * rest of the kernel.
 */
अटल पूर्णांक netfront_resume(काष्ठा xenbus_device *dev)
अणु
	काष्ठा netfront_info *info = dev_get_drvdata(&dev->dev);

	dev_dbg(&dev->dev, "%s\n", dev->nodename);

	xennet_disconnect_backend(info);
	वापस 0;
पूर्ण

अटल पूर्णांक xen_net_पढ़ो_mac(काष्ठा xenbus_device *dev, u8 mac[])
अणु
	अक्षर *s, *e, *macstr;
	पूर्णांक i;

	macstr = s = xenbus_पढ़ो(XBT_NIL, dev->nodename, "mac", शून्य);
	अगर (IS_ERR(macstr))
		वापस PTR_ERR(macstr);

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		mac[i] = simple_म_से_अदीर्घ(s, &e, 16);
		अगर ((s == e) || (*e != ((i == ETH_ALEN-1) ? '\0' : ':'))) अणु
			kमुक्त(macstr);
			वापस -ENOENT;
		पूर्ण
		s = e+1;
	पूर्ण

	kमुक्त(macstr);
	वापस 0;
पूर्ण

अटल पूर्णांक setup_netfront_single(काष्ठा netfront_queue *queue)
अणु
	पूर्णांक err;

	err = xenbus_alloc_evtchn(queue->info->xbdev, &queue->tx_evtchn);
	अगर (err < 0)
		जाओ fail;

	err = bind_evtchn_to_irqhandler(queue->tx_evtchn,
					xennet_पूर्णांकerrupt,
					0, queue->info->netdev->name, queue);
	अगर (err < 0)
		जाओ bind_fail;
	queue->rx_evtchn = queue->tx_evtchn;
	queue->rx_irq = queue->tx_irq = err;

	वापस 0;

bind_fail:
	xenbus_मुक्त_evtchn(queue->info->xbdev, queue->tx_evtchn);
	queue->tx_evtchn = 0;
fail:
	वापस err;
पूर्ण

अटल पूर्णांक setup_netfront_split(काष्ठा netfront_queue *queue)
अणु
	पूर्णांक err;

	err = xenbus_alloc_evtchn(queue->info->xbdev, &queue->tx_evtchn);
	अगर (err < 0)
		जाओ fail;
	err = xenbus_alloc_evtchn(queue->info->xbdev, &queue->rx_evtchn);
	अगर (err < 0)
		जाओ alloc_rx_evtchn_fail;

	snम_लिखो(queue->tx_irq_name, माप(queue->tx_irq_name),
		 "%s-tx", queue->name);
	err = bind_evtchn_to_irqhandler(queue->tx_evtchn,
					xennet_tx_पूर्णांकerrupt,
					0, queue->tx_irq_name, queue);
	अगर (err < 0)
		जाओ bind_tx_fail;
	queue->tx_irq = err;

	snम_लिखो(queue->rx_irq_name, माप(queue->rx_irq_name),
		 "%s-rx", queue->name);
	err = bind_evtchn_to_irqhandler(queue->rx_evtchn,
					xennet_rx_पूर्णांकerrupt,
					0, queue->rx_irq_name, queue);
	अगर (err < 0)
		जाओ bind_rx_fail;
	queue->rx_irq = err;

	वापस 0;

bind_rx_fail:
	unbind_from_irqhandler(queue->tx_irq, queue);
	queue->tx_irq = 0;
bind_tx_fail:
	xenbus_मुक्त_evtchn(queue->info->xbdev, queue->rx_evtchn);
	queue->rx_evtchn = 0;
alloc_rx_evtchn_fail:
	xenbus_मुक्त_evtchn(queue->info->xbdev, queue->tx_evtchn);
	queue->tx_evtchn = 0;
fail:
	वापस err;
पूर्ण

अटल पूर्णांक setup_netfront(काष्ठा xenbus_device *dev,
			काष्ठा netfront_queue *queue, अचिन्हित पूर्णांक feature_split_evtchn)
अणु
	काष्ठा xen_netअगर_tx_sring *txs;
	काष्ठा xen_netअगर_rx_sring *rxs;
	grant_ref_t gref;
	पूर्णांक err;

	queue->tx_ring_ref = GRANT_INVALID_REF;
	queue->rx_ring_ref = GRANT_INVALID_REF;
	queue->rx.sring = शून्य;
	queue->tx.sring = शून्य;

	txs = (काष्ठा xen_netअगर_tx_sring *)get_zeroed_page(GFP_NOIO | __GFP_HIGH);
	अगर (!txs) अणु
		err = -ENOMEM;
		xenbus_dev_fatal(dev, err, "allocating tx ring page");
		जाओ fail;
	पूर्ण
	SHARED_RING_INIT(txs);
	FRONT_RING_INIT(&queue->tx, txs, XEN_PAGE_SIZE);

	err = xenbus_grant_ring(dev, txs, 1, &gref);
	अगर (err < 0)
		जाओ grant_tx_ring_fail;
	queue->tx_ring_ref = gref;

	rxs = (काष्ठा xen_netअगर_rx_sring *)get_zeroed_page(GFP_NOIO | __GFP_HIGH);
	अगर (!rxs) अणु
		err = -ENOMEM;
		xenbus_dev_fatal(dev, err, "allocating rx ring page");
		जाओ alloc_rx_ring_fail;
	पूर्ण
	SHARED_RING_INIT(rxs);
	FRONT_RING_INIT(&queue->rx, rxs, XEN_PAGE_SIZE);

	err = xenbus_grant_ring(dev, rxs, 1, &gref);
	अगर (err < 0)
		जाओ grant_rx_ring_fail;
	queue->rx_ring_ref = gref;

	अगर (feature_split_evtchn)
		err = setup_netfront_split(queue);
	/* setup single event channel अगर
	 *  a) feature-split-event-channels == 0
	 *  b) feature-split-event-channels == 1 but failed to setup
	 */
	अगर (!feature_split_evtchn || err)
		err = setup_netfront_single(queue);

	अगर (err)
		जाओ alloc_evtchn_fail;

	वापस 0;

	/* If we fail to setup netfront, it is safe to just revoke access to
	 * granted pages because backend is not accessing it at this poपूर्णांक.
	 */
alloc_evtchn_fail:
	gnttab_end_क्रमeign_access_ref(queue->rx_ring_ref, 0);
grant_rx_ring_fail:
	मुक्त_page((अचिन्हित दीर्घ)rxs);
alloc_rx_ring_fail:
	gnttab_end_क्रमeign_access_ref(queue->tx_ring_ref, 0);
grant_tx_ring_fail:
	मुक्त_page((अचिन्हित दीर्घ)txs);
fail:
	वापस err;
पूर्ण

/* Queue-specअगरic initialisation
 * This used to be करोne in xennet_create_dev() but must now
 * be run per-queue.
 */
अटल पूर्णांक xennet_init_queue(काष्ठा netfront_queue *queue)
अणु
	अचिन्हित लघु i;
	पूर्णांक err = 0;
	अक्षर *devid;

	spin_lock_init(&queue->tx_lock);
	spin_lock_init(&queue->rx_lock);

	समयr_setup(&queue->rx_refill_समयr, rx_refill_समयout, 0);

	devid = म_खोजप(queue->info->xbdev->nodename, '/') + 1;
	snम_लिखो(queue->name, माप(queue->name), "vif%s-q%u",
		 devid, queue->id);

	/* Initialise tx_skbs as a मुक्त chain containing every entry. */
	queue->tx_skb_मुक्तlist = 0;
	क्रम (i = 0; i < NET_TX_RING_SIZE; i++) अणु
		skb_entry_set_link(&queue->tx_skbs[i], i+1);
		queue->grant_tx_ref[i] = GRANT_INVALID_REF;
		queue->grant_tx_page[i] = शून्य;
	पूर्ण

	/* Clear out rx_skbs */
	क्रम (i = 0; i < NET_RX_RING_SIZE; i++) अणु
		queue->rx_skbs[i] = शून्य;
		queue->grant_rx_ref[i] = GRANT_INVALID_REF;
	पूर्ण

	/* A grant क्रम every tx ring slot */
	अगर (gnttab_alloc_grant_references(NET_TX_RING_SIZE,
					  &queue->gref_tx_head) < 0) अणु
		pr_alert("can't alloc tx grant refs\n");
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	/* A grant क्रम every rx ring slot */
	अगर (gnttab_alloc_grant_references(NET_RX_RING_SIZE,
					  &queue->gref_rx_head) < 0) अणु
		pr_alert("can't alloc rx grant refs\n");
		err = -ENOMEM;
		जाओ निकास_मुक्त_tx;
	पूर्ण

	वापस 0;

 निकास_मुक्त_tx:
	gnttab_मुक्त_grant_references(queue->gref_tx_head);
 निकास:
	वापस err;
पूर्ण

अटल पूर्णांक ग_लिखो_queue_xenstore_keys(काष्ठा netfront_queue *queue,
			   काष्ठा xenbus_transaction *xbt, पूर्णांक ग_लिखो_hierarchical)
अणु
	/* Write the queue-specअगरic keys पूर्णांकo XenStore in the traditional
	 * way क्रम a single queue, or in a queue subkeys क्रम multiple
	 * queues.
	 */
	काष्ठा xenbus_device *dev = queue->info->xbdev;
	पूर्णांक err;
	स्थिर अक्षर *message;
	अक्षर *path;
	माप_प्रकार pathsize;

	/* Choose the correct place to ग_लिखो the keys */
	अगर (ग_लिखो_hierarchical) अणु
		pathsize = म_माप(dev->nodename) + 10;
		path = kzalloc(pathsize, GFP_KERNEL);
		अगर (!path) अणु
			err = -ENOMEM;
			message = "out of memory while writing ring references";
			जाओ error;
		पूर्ण
		snम_लिखो(path, pathsize, "%s/queue-%u",
				dev->nodename, queue->id);
	पूर्ण अन्यथा अणु
		path = (अक्षर *)dev->nodename;
	पूर्ण

	/* Write ring references */
	err = xenbus_म_लिखो(*xbt, path, "tx-ring-ref", "%u",
			queue->tx_ring_ref);
	अगर (err) अणु
		message = "writing tx-ring-ref";
		जाओ error;
	पूर्ण

	err = xenbus_म_लिखो(*xbt, path, "rx-ring-ref", "%u",
			queue->rx_ring_ref);
	अगर (err) अणु
		message = "writing rx-ring-ref";
		जाओ error;
	पूर्ण

	/* Write event channels; taking पूर्णांकo account both shared
	 * and split event channel scenarios.
	 */
	अगर (queue->tx_evtchn == queue->rx_evtchn) अणु
		/* Shared event channel */
		err = xenbus_म_लिखो(*xbt, path,
				"event-channel", "%u", queue->tx_evtchn);
		अगर (err) अणु
			message = "writing event-channel";
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Split event channels */
		err = xenbus_म_लिखो(*xbt, path,
				"event-channel-tx", "%u", queue->tx_evtchn);
		अगर (err) अणु
			message = "writing event-channel-tx";
			जाओ error;
		पूर्ण

		err = xenbus_म_लिखो(*xbt, path,
				"event-channel-rx", "%u", queue->rx_evtchn);
		अगर (err) अणु
			message = "writing event-channel-rx";
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (ग_लिखो_hierarchical)
		kमुक्त(path);
	वापस 0;

error:
	अगर (ग_लिखो_hierarchical)
		kमुक्त(path);
	xenbus_dev_fatal(dev, err, "%s", message);
	वापस err;
पूर्ण

अटल व्योम xennet_destroy_queues(काष्ठा netfront_info *info)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < info->netdev->real_num_tx_queues; i++) अणु
		काष्ठा netfront_queue *queue = &info->queues[i];

		अगर (netअगर_running(info->netdev))
			napi_disable(&queue->napi);
		netअगर_napi_del(&queue->napi);
	पूर्ण

	kमुक्त(info->queues);
	info->queues = शून्य;
पूर्ण



अटल पूर्णांक xennet_create_page_pool(काष्ठा netfront_queue *queue)
अणु
	पूर्णांक err;
	काष्ठा page_pool_params pp_params = अणु
		.order = 0,
		.flags = 0,
		.pool_size = NET_RX_RING_SIZE,
		.nid = NUMA_NO_NODE,
		.dev = &queue->info->netdev->dev,
		.offset = XDP_PACKET_HEADROOM,
		.max_len = XEN_PAGE_SIZE - XDP_PACKET_HEADROOM,
	पूर्ण;

	queue->page_pool = page_pool_create(&pp_params);
	अगर (IS_ERR(queue->page_pool)) अणु
		err = PTR_ERR(queue->page_pool);
		queue->page_pool = शून्य;
		वापस err;
	पूर्ण

	err = xdp_rxq_info_reg(&queue->xdp_rxq, queue->info->netdev,
			       queue->id, 0);
	अगर (err) अणु
		netdev_err(queue->info->netdev, "xdp_rxq_info_reg failed\n");
		जाओ err_मुक्त_pp;
	पूर्ण

	err = xdp_rxq_info_reg_mem_model(&queue->xdp_rxq,
					 MEM_TYPE_PAGE_POOL, queue->page_pool);
	अगर (err) अणु
		netdev_err(queue->info->netdev, "xdp_rxq_info_reg_mem_model failed\n");
		जाओ err_unरेजिस्टर_rxq;
	पूर्ण
	वापस 0;

err_unरेजिस्टर_rxq:
	xdp_rxq_info_unreg(&queue->xdp_rxq);
err_मुक्त_pp:
	page_pool_destroy(queue->page_pool);
	queue->page_pool = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक xennet_create_queues(काष्ठा netfront_info *info,
				अचिन्हित पूर्णांक *num_queues)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	info->queues = kसुस्मृति(*num_queues, माप(काष्ठा netfront_queue),
			       GFP_KERNEL);
	अगर (!info->queues)
		वापस -ENOMEM;

	क्रम (i = 0; i < *num_queues; i++) अणु
		काष्ठा netfront_queue *queue = &info->queues[i];

		queue->id = i;
		queue->info = info;

		ret = xennet_init_queue(queue);
		अगर (ret < 0) अणु
			dev_warn(&info->xbdev->dev,
				 "only created %d queues\n", i);
			*num_queues = i;
			अवरोध;
		पूर्ण

		/* use page pool recycling instead of buddy allocator */
		ret = xennet_create_page_pool(queue);
		अगर (ret < 0) अणु
			dev_err(&info->xbdev->dev, "can't allocate page pool\n");
			*num_queues = i;
			वापस ret;
		पूर्ण

		netअगर_napi_add(queue->info->netdev, &queue->napi,
			       xennet_poll, 64);
		अगर (netअगर_running(info->netdev))
			napi_enable(&queue->napi);
	पूर्ण

	netअगर_set_real_num_tx_queues(info->netdev, *num_queues);

	अगर (*num_queues == 0) अणु
		dev_err(&info->xbdev->dev, "no queues\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Common code used when first setting up, and when resuming. */
अटल पूर्णांक talk_to_netback(काष्ठा xenbus_device *dev,
			   काष्ठा netfront_info *info)
अणु
	स्थिर अक्षर *message;
	काष्ठा xenbus_transaction xbt;
	पूर्णांक err;
	अचिन्हित पूर्णांक feature_split_evtchn;
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक max_queues = 0;
	काष्ठा netfront_queue *queue = शून्य;
	अचिन्हित पूर्णांक num_queues = 1;

	info->netdev->irq = 0;

	/* Check अगर backend supports multiple queues */
	max_queues = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
					  "multi-queue-max-queues", 1);
	num_queues = min(max_queues, xennet_max_queues);

	/* Check feature-split-event-channels */
	feature_split_evtchn = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
					"feature-split-event-channels", 0);

	/* Read mac addr. */
	err = xen_net_पढ़ो_mac(dev, info->netdev->dev_addr);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "parsing %s/mac", dev->nodename);
		जाओ out_unlocked;
	पूर्ण

	info->netback_has_xdp_headroom = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
							      "feature-xdp-headroom", 0);
	अगर (info->netback_has_xdp_headroom) अणु
		/* set the current xen-netfront xdp state */
		err = talk_to_netback_xdp(info, info->netfront_xdp_enabled ?
					  NETBACK_XDP_HEADROOM_ENABLE :
					  NETBACK_XDP_HEADROOM_DISABLE);
		अगर (err)
			जाओ out_unlocked;
	पूर्ण

	rtnl_lock();
	अगर (info->queues)
		xennet_destroy_queues(info);

	err = xennet_create_queues(info, &num_queues);
	अगर (err < 0) अणु
		xenbus_dev_fatal(dev, err, "creating queues");
		kमुक्त(info->queues);
		info->queues = शून्य;
		जाओ out;
	पूर्ण
	rtnl_unlock();

	/* Create shared ring, alloc event channel -- क्रम each queue */
	क्रम (i = 0; i < num_queues; ++i) अणु
		queue = &info->queues[i];
		err = setup_netfront(dev, queue, feature_split_evtchn);
		अगर (err)
			जाओ destroy_ring;
	पूर्ण

again:
	err = xenbus_transaction_start(&xbt);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "starting transaction");
		जाओ destroy_ring;
	पूर्ण

	अगर (xenbus_exists(XBT_NIL,
			  info->xbdev->otherend, "multi-queue-max-queues")) अणु
		/* Write the number of queues */
		err = xenbus_म_लिखो(xbt, dev->nodename,
				    "multi-queue-num-queues", "%u", num_queues);
		अगर (err) अणु
			message = "writing multi-queue-num-queues";
			जाओ पात_transaction_no_dev_fatal;
		पूर्ण
	पूर्ण

	अगर (num_queues == 1) अणु
		err = ग_लिखो_queue_xenstore_keys(&info->queues[0], &xbt, 0); /* flat */
		अगर (err)
			जाओ पात_transaction_no_dev_fatal;
	पूर्ण अन्यथा अणु
		/* Write the keys क्रम each queue */
		क्रम (i = 0; i < num_queues; ++i) अणु
			queue = &info->queues[i];
			err = ग_लिखो_queue_xenstore_keys(queue, &xbt, 1); /* hierarchical */
			अगर (err)
				जाओ पात_transaction_no_dev_fatal;
		पूर्ण
	पूर्ण

	/* The reमुख्यing keys are not queue-specअगरic */
	err = xenbus_म_लिखो(xbt, dev->nodename, "request-rx-copy", "%u",
			    1);
	अगर (err) अणु
		message = "writing request-rx-copy";
		जाओ पात_transaction;
	पूर्ण

	err = xenbus_म_लिखो(xbt, dev->nodename, "feature-rx-notify", "%d", 1);
	अगर (err) अणु
		message = "writing feature-rx-notify";
		जाओ पात_transaction;
	पूर्ण

	err = xenbus_म_लिखो(xbt, dev->nodename, "feature-sg", "%d", 1);
	अगर (err) अणु
		message = "writing feature-sg";
		जाओ पात_transaction;
	पूर्ण

	err = xenbus_म_लिखो(xbt, dev->nodename, "feature-gso-tcpv4", "%d", 1);
	अगर (err) अणु
		message = "writing feature-gso-tcpv4";
		जाओ पात_transaction;
	पूर्ण

	err = xenbus_ग_लिखो(xbt, dev->nodename, "feature-gso-tcpv6", "1");
	अगर (err) अणु
		message = "writing feature-gso-tcpv6";
		जाओ पात_transaction;
	पूर्ण

	err = xenbus_ग_लिखो(xbt, dev->nodename, "feature-ipv6-csum-offload",
			   "1");
	अगर (err) अणु
		message = "writing feature-ipv6-csum-offload";
		जाओ पात_transaction;
	पूर्ण

	err = xenbus_transaction_end(xbt, 0);
	अगर (err) अणु
		अगर (err == -EAGAIN)
			जाओ again;
		xenbus_dev_fatal(dev, err, "completing transaction");
		जाओ destroy_ring;
	पूर्ण

	वापस 0;

 पात_transaction:
	xenbus_dev_fatal(dev, err, "%s", message);
पात_transaction_no_dev_fatal:
	xenbus_transaction_end(xbt, 1);
 destroy_ring:
	xennet_disconnect_backend(info);
	rtnl_lock();
	xennet_destroy_queues(info);
 out:
	rtnl_unlock();
out_unlocked:
	device_unरेजिस्टर(&dev->dev);
	वापस err;
पूर्ण

अटल पूर्णांक xennet_connect(काष्ठा net_device *dev)
अणु
	काष्ठा netfront_info *np = netdev_priv(dev);
	अचिन्हित पूर्णांक num_queues = 0;
	पूर्णांक err;
	अचिन्हित पूर्णांक j = 0;
	काष्ठा netfront_queue *queue = शून्य;

	अगर (!xenbus_पढ़ो_अचिन्हित(np->xbdev->otherend, "feature-rx-copy", 0)) अणु
		dev_info(&dev->dev,
			 "backend does not support copying receive path\n");
		वापस -ENODEV;
	पूर्ण

	err = talk_to_netback(np->xbdev, np);
	अगर (err)
		वापस err;
	अगर (np->netback_has_xdp_headroom)
		pr_info("backend supports XDP headroom\n");

	/* talk_to_netback() sets the correct number of queues */
	num_queues = dev->real_num_tx_queues;

	अगर (dev->reg_state == NETREG_UNINITIALIZED) अणु
		err = रेजिस्टर_netdev(dev);
		अगर (err) अणु
			pr_warn("%s: register_netdev err=%d\n", __func__, err);
			device_unरेजिस्टर(&np->xbdev->dev);
			वापस err;
		पूर्ण
	पूर्ण

	rtnl_lock();
	netdev_update_features(dev);
	rtnl_unlock();

	/*
	 * All खुला and निजी state should now be sane.  Get
	 * पढ़ोy to start sending and receiving packets and give the driver
	 * करोमुख्य a kick because we've probably just requeued some
	 * packets.
	 */
	netअगर_carrier_on(np->netdev);
	क्रम (j = 0; j < num_queues; ++j) अणु
		queue = &np->queues[j];

		notअगरy_remote_via_irq(queue->tx_irq);
		अगर (queue->tx_irq != queue->rx_irq)
			notअगरy_remote_via_irq(queue->rx_irq);

		spin_lock_irq(&queue->tx_lock);
		xennet_tx_buf_gc(queue);
		spin_unlock_irq(&queue->tx_lock);

		spin_lock_bh(&queue->rx_lock);
		xennet_alloc_rx_buffers(queue);
		spin_unlock_bh(&queue->rx_lock);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Callback received when the backend's state changes.
 */
अटल व्योम netback_changed(काष्ठा xenbus_device *dev,
			    क्रमागत xenbus_state backend_state)
अणु
	काष्ठा netfront_info *np = dev_get_drvdata(&dev->dev);
	काष्ठा net_device *netdev = np->netdev;

	dev_dbg(&dev->dev, "%s\n", xenbus_strstate(backend_state));

	wake_up_all(&module_wq);

	चयन (backend_state) अणु
	हाल XenbusStateInitialising:
	हाल XenbusStateInitialised:
	हाल XenbusStateReconfiguring:
	हाल XenbusStateReconfigured:
	हाल XenbusStateUnknown:
		अवरोध;

	हाल XenbusStateInitWait:
		अगर (dev->state != XenbusStateInitialising)
			अवरोध;
		अगर (xennet_connect(netdev) != 0)
			अवरोध;
		xenbus_चयन_state(dev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateConnected:
		netdev_notअगरy_peers(netdev);
		अवरोध;

	हाल XenbusStateClosed:
		अगर (dev->state == XenbusStateClosed)
			अवरोध;
		fallthrough;	/* Missed the backend's CLOSING state */
	हाल XenbusStateClosing:
		xenbus_frontend_बंदd(dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा xennet_stat अणु
	अक्षर name[ETH_GSTRING_LEN];
	u16 offset;
पूर्ण xennet_stats[] = अणु
	अणु
		"rx_gso_checksum_fixup",
		दुरत्व(काष्ठा netfront_info, rx_gso_checksum_fixup)
	पूर्ण,
पूर्ण;

अटल पूर्णांक xennet_get_sset_count(काष्ठा net_device *dev, पूर्णांक string_set)
अणु
	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(xennet_stats);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम xennet_get_ethtool_stats(काष्ठा net_device *dev,
				     काष्ठा ethtool_stats *stats, u64 * data)
अणु
	व्योम *np = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(xennet_stats); i++)
		data[i] = atomic_पढ़ो((atomic_t *)(np + xennet_stats[i].offset));
पूर्ण

अटल व्योम xennet_get_strings(काष्ठा net_device *dev, u32 stringset, u8 * data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(xennet_stats); i++)
			स_नकल(data + i * ETH_GSTRING_LEN,
			       xennet_stats[i].name, ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops xennet_ethtool_ops =
अणु
	.get_link = ethtool_op_get_link,

	.get_sset_count = xennet_get_sset_count,
	.get_ethtool_stats = xennet_get_ethtool_stats,
	.get_strings = xennet_get_strings,
	.get_ts_info = ethtool_op_get_ts_info,
पूर्ण;

#अगर_घोषित CONFIG_SYSFS
अटल sमाप_प्रकार show_rxbuf(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%lu\n", NET_RX_RING_SIZE);
पूर्ण

अटल sमाप_प्रकार store_rxbuf(काष्ठा device *dev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अक्षर *endp;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	simple_म_से_अदीर्घ(buf, &endp, 0);
	अगर (endp == buf)
		वापस -EBADMSG;

	/* rxbuf_min and rxbuf_max are no दीर्घer configurable. */

	वापस len;
पूर्ण

अटल DEVICE_ATTR(rxbuf_min, 0644, show_rxbuf, store_rxbuf);
अटल DEVICE_ATTR(rxbuf_max, 0644, show_rxbuf, store_rxbuf);
अटल DEVICE_ATTR(rxbuf_cur, 0444, show_rxbuf, शून्य);

अटल काष्ठा attribute *xennet_dev_attrs[] = अणु
	&dev_attr_rxbuf_min.attr,
	&dev_attr_rxbuf_max.attr,
	&dev_attr_rxbuf_cur.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group xennet_dev_group = अणु
	.attrs = xennet_dev_attrs
पूर्ण;
#पूर्ण_अगर /* CONFIG_SYSFS */

अटल व्योम xennet_bus_बंद(काष्ठा xenbus_device *dev)
अणु
	पूर्णांक ret;

	अगर (xenbus_पढ़ो_driver_state(dev->otherend) == XenbusStateClosed)
		वापस;
	करो अणु
		xenbus_चयन_state(dev, XenbusStateClosing);
		ret = रुको_event_समयout(module_wq,
				   xenbus_पढ़ो_driver_state(dev->otherend) ==
				   XenbusStateClosing ||
				   xenbus_पढ़ो_driver_state(dev->otherend) ==
				   XenbusStateClosed ||
				   xenbus_पढ़ो_driver_state(dev->otherend) ==
				   XenbusStateUnknown,
				   XENNET_TIMEOUT);
	पूर्ण जबतक (!ret);

	अगर (xenbus_पढ़ो_driver_state(dev->otherend) == XenbusStateClosed)
		वापस;

	करो अणु
		xenbus_चयन_state(dev, XenbusStateClosed);
		ret = रुको_event_समयout(module_wq,
				   xenbus_पढ़ो_driver_state(dev->otherend) ==
				   XenbusStateClosed ||
				   xenbus_पढ़ो_driver_state(dev->otherend) ==
				   XenbusStateUnknown,
				   XENNET_TIMEOUT);
	पूर्ण जबतक (!ret);
पूर्ण

अटल पूर्णांक xennet_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा netfront_info *info = dev_get_drvdata(&dev->dev);

	xennet_bus_बंद(dev);
	xennet_disconnect_backend(info);

	अगर (info->netdev->reg_state == NETREG_REGISTERED)
		unरेजिस्टर_netdev(info->netdev);

	अगर (info->queues) अणु
		rtnl_lock();
		xennet_destroy_queues(info);
		rtnl_unlock();
	पूर्ण
	xennet_मुक्त_netdev(info->netdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id netfront_ids[] = अणु
	अणु "vif" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver netfront_driver = अणु
	.ids = netfront_ids,
	.probe = netfront_probe,
	.हटाओ = xennet_हटाओ,
	.resume = netfront_resume,
	.otherend_changed = netback_changed,
पूर्ण;

अटल पूर्णांक __init netअगर_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	अगर (!xen_has_pv_nic_devices())
		वापस -ENODEV;

	pr_info("Initialising Xen virtual ethernet driver\n");

	/* Allow as many queues as there are CPUs inut max. 8 अगर user has not
	 * specअगरied a value.
	 */
	अगर (xennet_max_queues == 0)
		xennet_max_queues = min_t(अचिन्हित पूर्णांक, MAX_QUEUES_DEFAULT,
					  num_online_cpus());

	वापस xenbus_रेजिस्टर_frontend(&netfront_driver);
पूर्ण
module_init(netअगर_init);


अटल व्योम __निकास netअगर_निकास(व्योम)
अणु
	xenbus_unरेजिस्टर_driver(&netfront_driver);
पूर्ण
module_निकास(netअगर_निकास);

MODULE_DESCRIPTION("Xen virtual network device frontend");
MODULE_LICENSE("GPL");
MODULE_ALIAS("xen:vif");
MODULE_ALIAS("xennet");
