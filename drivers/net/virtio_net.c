<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* A network driver using virtio.
 *
 * Copyright 2007 Rusty Russell <rusty@rustcorp.com.au> IBM Corporation
 */
//#घोषणा DEBUG
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_net.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/average.h>
#समावेश <linux/filter.h>
#समावेश <linux/kernel.h>
#समावेश <net/route.h>
#समावेश <net/xdp.h>
#समावेश <net/net_failover.h>

अटल पूर्णांक napi_weight = NAPI_POLL_WEIGHT;
module_param(napi_weight, पूर्णांक, 0444);

अटल bool csum = true, gso = true, napi_tx = true;
module_param(csum, bool, 0444);
module_param(gso, bool, 0444);
module_param(napi_tx, bool, 0644);

/* FIXME: MTU in config. */
#घोषणा GOOD_PACKET_LEN (ETH_HLEN + VLAN_HLEN + ETH_DATA_LEN)
#घोषणा GOOD_COPY_LEN	128

#घोषणा VIRTNET_RX_PAD (NET_IP_ALIGN + NET_SKB_PAD)

/* Amount of XDP headroom to prepend to packets क्रम use by xdp_adjust_head */
#घोषणा VIRTIO_XDP_HEADROOM 256

/* Separating two types of XDP xmit */
#घोषणा VIRTIO_XDP_TX		BIT(0)
#घोषणा VIRTIO_XDP_REसूची	BIT(1)

#घोषणा VIRTIO_XDP_FLAG	BIT(0)

/* RX packet size EWMA. The average packet size is used to determine the packet
 * buffer size when refilling RX rings. As the entire RX ring may be refilled
 * at once, the weight is chosen so that the EWMA will be insensitive to लघु-
 * term, transient changes in packet size.
 */
DECLARE_EWMA(pkt_len, 0, 64)

#घोषणा VIRTNET_DRIVER_VERSION "1.0.0"

अटल स्थिर अचिन्हित दीर्घ guest_offloads[] = अणु
	VIRTIO_NET_F_GUEST_TSO4,
	VIRTIO_NET_F_GUEST_TSO6,
	VIRTIO_NET_F_GUEST_ECN,
	VIRTIO_NET_F_GUEST_UFO,
	VIRTIO_NET_F_GUEST_CSUM
पूर्ण;

#घोषणा GUEST_OFFLOAD_LRO_MASK ((1ULL << VIRTIO_NET_F_GUEST_TSO4) | \
				(1ULL << VIRTIO_NET_F_GUEST_TSO6) | \
				(1ULL << VIRTIO_NET_F_GUEST_ECN)  | \
				(1ULL << VIRTIO_NET_F_GUEST_UFO))

काष्ठा virtnet_stat_desc अणु
	अक्षर desc[ETH_GSTRING_LEN];
	माप_प्रकार offset;
पूर्ण;

काष्ठा virtnet_sq_stats अणु
	काष्ठा u64_stats_sync syncp;
	u64 packets;
	u64 bytes;
	u64 xdp_tx;
	u64 xdp_tx_drops;
	u64 kicks;
पूर्ण;

काष्ठा virtnet_rq_stats अणु
	काष्ठा u64_stats_sync syncp;
	u64 packets;
	u64 bytes;
	u64 drops;
	u64 xdp_packets;
	u64 xdp_tx;
	u64 xdp_redirects;
	u64 xdp_drops;
	u64 kicks;
पूर्ण;

#घोषणा VIRTNET_SQ_STAT(m)	दुरत्व(काष्ठा virtnet_sq_stats, m)
#घोषणा VIRTNET_RQ_STAT(m)	दुरत्व(काष्ठा virtnet_rq_stats, m)

अटल स्थिर काष्ठा virtnet_stat_desc virtnet_sq_stats_desc[] = अणु
	अणु "packets",		VIRTNET_SQ_STAT(packets) पूर्ण,
	अणु "bytes",		VIRTNET_SQ_STAT(bytes) पूर्ण,
	अणु "xdp_tx",		VIRTNET_SQ_STAT(xdp_tx) पूर्ण,
	अणु "xdp_tx_drops",	VIRTNET_SQ_STAT(xdp_tx_drops) पूर्ण,
	अणु "kicks",		VIRTNET_SQ_STAT(kicks) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा virtnet_stat_desc virtnet_rq_stats_desc[] = अणु
	अणु "packets",		VIRTNET_RQ_STAT(packets) पूर्ण,
	अणु "bytes",		VIRTNET_RQ_STAT(bytes) पूर्ण,
	अणु "drops",		VIRTNET_RQ_STAT(drops) पूर्ण,
	अणु "xdp_packets",	VIRTNET_RQ_STAT(xdp_packets) पूर्ण,
	अणु "xdp_tx",		VIRTNET_RQ_STAT(xdp_tx) पूर्ण,
	अणु "xdp_redirects",	VIRTNET_RQ_STAT(xdp_redirects) पूर्ण,
	अणु "xdp_drops",		VIRTNET_RQ_STAT(xdp_drops) पूर्ण,
	अणु "kicks",		VIRTNET_RQ_STAT(kicks) पूर्ण,
पूर्ण;

#घोषणा VIRTNET_SQ_STATS_LEN	ARRAY_SIZE(virtnet_sq_stats_desc)
#घोषणा VIRTNET_RQ_STATS_LEN	ARRAY_SIZE(virtnet_rq_stats_desc)

/* Internal representation of a send virtqueue */
काष्ठा send_queue अणु
	/* Virtqueue associated with this send _queue */
	काष्ठा virtqueue *vq;

	/* TX: fragments + linear part + virtio header */
	काष्ठा scatterlist sg[MAX_SKB_FRAGS + 2];

	/* Name of the send queue: output.$index */
	अक्षर name[40];

	काष्ठा virtnet_sq_stats stats;

	काष्ठा napi_काष्ठा napi;
पूर्ण;

/* Internal representation of a receive virtqueue */
काष्ठा receive_queue अणु
	/* Virtqueue associated with this receive_queue */
	काष्ठा virtqueue *vq;

	काष्ठा napi_काष्ठा napi;

	काष्ठा bpf_prog __rcu *xdp_prog;

	काष्ठा virtnet_rq_stats stats;

	/* Chain pages by the निजी ptr. */
	काष्ठा page *pages;

	/* Average packet length क्रम mergeable receive buffers. */
	काष्ठा ewma_pkt_len mrg_avg_pkt_len;

	/* Page frag क्रम packet buffer allocation. */
	काष्ठा page_frag alloc_frag;

	/* RX: fragments + linear part + virtio header */
	काष्ठा scatterlist sg[MAX_SKB_FRAGS + 2];

	/* Min single buffer size क्रम mergeable buffers हाल. */
	अचिन्हित पूर्णांक min_buf_len;

	/* Name of this receive queue: input.$index */
	अक्षर name[40];

	काष्ठा xdp_rxq_info xdp_rxq;
पूर्ण;

/* Control VQ buffers: रक्षित by the rtnl lock */
काष्ठा control_buf अणु
	काष्ठा virtio_net_ctrl_hdr hdr;
	virtio_net_ctrl_ack status;
	काष्ठा virtio_net_ctrl_mq mq;
	u8 promisc;
	u8 allmulti;
	__virtio16 vid;
	__virtio64 offloads;
पूर्ण;

काष्ठा virtnet_info अणु
	काष्ठा virtio_device *vdev;
	काष्ठा virtqueue *cvq;
	काष्ठा net_device *dev;
	काष्ठा send_queue *sq;
	काष्ठा receive_queue *rq;
	अचिन्हित पूर्णांक status;

	/* Max # of queue pairs supported by the device */
	u16 max_queue_pairs;

	/* # of queue pairs currently used by the driver */
	u16 curr_queue_pairs;

	/* # of XDP queue pairs currently used by the driver */
	u16 xdp_queue_pairs;

	/* xdp_queue_pairs may be 0, when xdp is alपढ़ोy loaded. So add this. */
	bool xdp_enabled;

	/* I like... big packets and I cannot lie! */
	bool big_packets;

	/* Host will merge rx buffers क्रम big packets (shake it! shake it!) */
	bool mergeable_rx_bufs;

	/* Has control virtqueue */
	bool has_cvq;

	/* Host can handle any s/g split between our header and packet data */
	bool any_header_sg;

	/* Packet virtio header size */
	u8 hdr_len;

	/* Work काष्ठा क्रम refilling अगर we run low on memory. */
	काष्ठा delayed_work refill;

	/* Work काष्ठा क्रम config space updates */
	काष्ठा work_काष्ठा config_work;

	/* Does the affinity hपूर्णांक is set क्रम virtqueues? */
	bool affinity_hपूर्णांक_set;

	/* CPU hotplug instances क्रम online & dead */
	काष्ठा hlist_node node;
	काष्ठा hlist_node node_dead;

	काष्ठा control_buf *ctrl;

	/* Ethtool settings */
	u8 duplex;
	u32 speed;

	अचिन्हित दीर्घ guest_offloads;
	अचिन्हित दीर्घ guest_offloads_capable;

	/* failover when STANDBY feature enabled */
	काष्ठा failover *failover;
पूर्ण;

काष्ठा padded_vnet_hdr अणु
	काष्ठा virtio_net_hdr_mrg_rxbuf hdr;
	/*
	 * hdr is in a separate sg buffer, and data sg buffer shares same page
	 * with this header sg. This padding makes next sg 16 byte aligned
	 * after the header.
	 */
	अक्षर padding[4];
पूर्ण;

अटल bool is_xdp_frame(व्योम *ptr)
अणु
	वापस (अचिन्हित दीर्घ)ptr & VIRTIO_XDP_FLAG;
पूर्ण

अटल व्योम *xdp_to_ptr(काष्ठा xdp_frame *ptr)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)ptr | VIRTIO_XDP_FLAG);
पूर्ण

अटल काष्ठा xdp_frame *ptr_to_xdp(व्योम *ptr)
अणु
	वापस (काष्ठा xdp_frame *)((अचिन्हित दीर्घ)ptr & ~VIRTIO_XDP_FLAG);
पूर्ण

/* Converting between virtqueue no. and kernel tx/rx queue no.
 * 0:rx0 1:tx0 2:rx1 3:tx1 ... 2N:rxN 2N+1:txN 2N+2:cvq
 */
अटल पूर्णांक vq2txq(काष्ठा virtqueue *vq)
अणु
	वापस (vq->index - 1) / 2;
पूर्ण

अटल पूर्णांक txq2vq(पूर्णांक txq)
अणु
	वापस txq * 2 + 1;
पूर्ण

अटल पूर्णांक vq2rxq(काष्ठा virtqueue *vq)
अणु
	वापस vq->index / 2;
पूर्ण

अटल पूर्णांक rxq2vq(पूर्णांक rxq)
अणु
	वापस rxq * 2;
पूर्ण

अटल अंतरभूत काष्ठा virtio_net_hdr_mrg_rxbuf *skb_vnet_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा virtio_net_hdr_mrg_rxbuf *)skb->cb;
पूर्ण

/*
 * निजी is used to chain pages क्रम big packets, put the whole
 * most recent used list in the beginning क्रम reuse
 */
अटल व्योम give_pages(काष्ठा receive_queue *rq, काष्ठा page *page)
अणु
	काष्ठा page *end;

	/* Find end of list, sew whole thing पूर्णांकo vi->rq.pages. */
	क्रम (end = page; end->निजी; end = (काष्ठा page *)end->निजी);
	end->निजी = (अचिन्हित दीर्घ)rq->pages;
	rq->pages = page;
पूर्ण

अटल काष्ठा page *get_a_page(काष्ठा receive_queue *rq, gfp_t gfp_mask)
अणु
	काष्ठा page *p = rq->pages;

	अगर (p) अणु
		rq->pages = (काष्ठा page *)p->निजी;
		/* clear निजी here, it is used to chain pages */
		p->निजी = 0;
	पूर्ण अन्यथा
		p = alloc_page(gfp_mask);
	वापस p;
पूर्ण

अटल व्योम virtqueue_napi_schedule(काष्ठा napi_काष्ठा *napi,
				    काष्ठा virtqueue *vq)
अणु
	अगर (napi_schedule_prep(napi)) अणु
		virtqueue_disable_cb(vq);
		__napi_schedule(napi);
	पूर्ण
पूर्ण

अटल व्योम virtqueue_napi_complete(काष्ठा napi_काष्ठा *napi,
				    काष्ठा virtqueue *vq, पूर्णांक processed)
अणु
	पूर्णांक opaque;

	opaque = virtqueue_enable_cb_prepare(vq);
	अगर (napi_complete_करोne(napi, processed)) अणु
		अगर (unlikely(virtqueue_poll(vq, opaque)))
			virtqueue_napi_schedule(napi, vq);
	पूर्ण अन्यथा अणु
		virtqueue_disable_cb(vq);
	पूर्ण
पूर्ण

अटल व्योम skb_xmit_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtnet_info *vi = vq->vdev->priv;
	काष्ठा napi_काष्ठा *napi = &vi->sq[vq2txq(vq)].napi;

	/* Suppress further पूर्णांकerrupts. */
	virtqueue_disable_cb(vq);

	अगर (napi->weight)
		virtqueue_napi_schedule(napi, vq);
	अन्यथा
		/* We were probably रुकोing क्रम more output buffers. */
		netअगर_wake_subqueue(vi->dev, vq2txq(vq));
पूर्ण

#घोषणा MRG_CTX_HEADER_SHIFT 22
अटल व्योम *mergeable_len_to_ctx(अचिन्हित पूर्णांक truesize,
				  अचिन्हित पूर्णांक headroom)
अणु
	वापस (व्योम *)(अचिन्हित दीर्घ)((headroom << MRG_CTX_HEADER_SHIFT) | truesize);
पूर्ण

अटल अचिन्हित पूर्णांक mergeable_ctx_to_headroom(व्योम *mrg_ctx)
अणु
	वापस (अचिन्हित दीर्घ)mrg_ctx >> MRG_CTX_HEADER_SHIFT;
पूर्ण

अटल अचिन्हित पूर्णांक mergeable_ctx_to_truesize(व्योम *mrg_ctx)
अणु
	वापस (अचिन्हित दीर्घ)mrg_ctx & ((1 << MRG_CTX_HEADER_SHIFT) - 1);
पूर्ण

/* Called from bottom half context */
अटल काष्ठा sk_buff *page_to_skb(काष्ठा virtnet_info *vi,
				   काष्ठा receive_queue *rq,
				   काष्ठा page *page, अचिन्हित पूर्णांक offset,
				   अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक truesize,
				   bool hdr_valid, अचिन्हित पूर्णांक metasize,
				   अचिन्हित पूर्णांक headroom)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा virtio_net_hdr_mrg_rxbuf *hdr;
	अचिन्हित पूर्णांक copy, hdr_len, hdr_padded_len;
	काष्ठा page *page_to_मुक्त = शून्य;
	पूर्णांक tailroom, shinfo_size;
	अक्षर *p, *hdr_p, *buf;

	p = page_address(page) + offset;
	hdr_p = p;

	hdr_len = vi->hdr_len;
	अगर (vi->mergeable_rx_bufs)
		hdr_padded_len = माप(*hdr);
	अन्यथा
		hdr_padded_len = माप(काष्ठा padded_vnet_hdr);

	/* If headroom is not 0, there is an offset between the beginning of the
	 * data and the allocated space, otherwise the data and the allocated
	 * space are aligned.
	 *
	 * Buffers with headroom use PAGE_SIZE as alloc size, see
	 * add_recvbuf_mergeable() + get_mergeable_buf_len()
	 */
	truesize = headroom ? PAGE_SIZE : truesize;
	tailroom = truesize - len - headroom - (hdr_padded_len - hdr_len);
	buf = p - headroom;

	len -= hdr_len;
	offset += hdr_padded_len;
	p += hdr_padded_len;

	shinfo_size = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	/* copy small packet so we can reuse these pages */
	अगर (!NET_IP_ALIGN && len > GOOD_COPY_LEN && tailroom >= shinfo_size) अणु
		skb = build_skb(buf, truesize);
		अगर (unlikely(!skb))
			वापस शून्य;

		skb_reserve(skb, p - buf);
		skb_put(skb, len);
		जाओ ok;
	पूर्ण

	/* copy small packet so we can reuse these pages क्रम small data */
	skb = napi_alloc_skb(&rq->napi, GOOD_COPY_LEN);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* Copy all frame अगर it fits skb->head, otherwise
	 * we let virtio_net_hdr_to_skb() and GRO pull headers as needed.
	 */
	अगर (len <= skb_tailroom(skb))
		copy = len;
	अन्यथा
		copy = ETH_HLEN + metasize;
	skb_put_data(skb, p, copy);

	len -= copy;
	offset += copy;

	अगर (vi->mergeable_rx_bufs) अणु
		अगर (len)
			skb_add_rx_frag(skb, 0, page, offset, len, truesize);
		अन्यथा
			page_to_मुक्त = page;
		जाओ ok;
	पूर्ण

	/*
	 * Verअगरy that we can indeed put this data पूर्णांकo a skb.
	 * This is here to handle हालs when the device erroneously
	 * tries to receive more than is possible. This is usually
	 * the हाल of a broken device.
	 */
	अगर (unlikely(len > MAX_SKB_FRAGS * PAGE_SIZE)) अणु
		net_dbg_ratelimited("%s: too much data\n", skb->dev->name);
		dev_kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण
	BUG_ON(offset >= PAGE_SIZE);
	जबतक (len) अणु
		अचिन्हित पूर्णांक frag_size = min((अचिन्हित)PAGE_SIZE - offset, len);
		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page, offset,
				frag_size, truesize);
		len -= frag_size;
		page = (काष्ठा page *)page->निजी;
		offset = 0;
	पूर्ण

	अगर (page)
		give_pages(rq, page);

ok:
	/* hdr_valid means no XDP, so we can copy the vnet header */
	अगर (hdr_valid) अणु
		hdr = skb_vnet_hdr(skb);
		स_नकल(hdr, hdr_p, hdr_len);
	पूर्ण
	अगर (page_to_मुक्त)
		put_page(page_to_मुक्त);

	अगर (metasize) अणु
		__skb_pull(skb, metasize);
		skb_metadata_set(skb, metasize);
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक __virtnet_xdp_xmit_one(काष्ठा virtnet_info *vi,
				   काष्ठा send_queue *sq,
				   काष्ठा xdp_frame *xdpf)
अणु
	काष्ठा virtio_net_hdr_mrg_rxbuf *hdr;
	पूर्णांक err;

	अगर (unlikely(xdpf->headroom < vi->hdr_len))
		वापस -EOVERFLOW;

	/* Make room क्रम virtqueue hdr (also change xdpf->headroom?) */
	xdpf->data -= vi->hdr_len;
	/* Zero header and leave csum up to XDP layers */
	hdr = xdpf->data;
	स_रखो(hdr, 0, vi->hdr_len);
	xdpf->len   += vi->hdr_len;

	sg_init_one(sq->sg, xdpf->data, xdpf->len);

	err = virtqueue_add_outbuf(sq->vq, sq->sg, 1, xdp_to_ptr(xdpf),
				   GFP_ATOMIC);
	अगर (unlikely(err))
		वापस -ENOSPC; /* Caller handle मुक्त/refcnt */

	वापस 0;
पूर्ण

/* when vi->curr_queue_pairs > nr_cpu_ids, the txq/sq is only used क्रम xdp tx on
 * the current cpu, so it करोes not need to be locked.
 *
 * Here we use marco instead of अंतरभूत functions because we have to deal with
 * three issues at the same समय: 1. the choice of sq. 2. judge and execute the
 * lock/unlock of txq 3. make sparse happy. It is dअगरficult क्रम two अंतरभूत
 * functions to perfectly solve these three problems at the same समय.
 */
#घोषणा virtnet_xdp_get_sq(vi) (अणु                                       \
	काष्ठा netdev_queue *txq;                                       \
	typeof(vi) v = (vi);                                            \
	अचिन्हित पूर्णांक qp;                                                \
									\
	अगर (v->curr_queue_pairs > nr_cpu_ids) अणु                         \
		qp = v->curr_queue_pairs - v->xdp_queue_pairs;          \
		qp += smp_processor_id();                               \
		txq = netdev_get_tx_queue(v->dev, qp);                  \
		__netअगर_tx_acquire(txq);                                \
	पूर्ण अन्यथा अणु                                                        \
		qp = smp_processor_id() % v->curr_queue_pairs;          \
		txq = netdev_get_tx_queue(v->dev, qp);                  \
		__netअगर_tx_lock(txq, raw_smp_processor_id());           \
	पूर्ण                                                               \
	v->sq + qp;                                                     \
पूर्ण)

#घोषणा virtnet_xdp_put_sq(vi, q) अणु                                     \
	काष्ठा netdev_queue *txq;                                       \
	typeof(vi) v = (vi);                                            \
									\
	txq = netdev_get_tx_queue(v->dev, (q) - v->sq);                 \
	अगर (v->curr_queue_pairs > nr_cpu_ids)                           \
		__netअगर_tx_release(txq);                                \
	अन्यथा                                                            \
		__netअगर_tx_unlock(txq);                                 \
पूर्ण

अटल पूर्णांक virtnet_xdp_xmit(काष्ठा net_device *dev,
			    पूर्णांक n, काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	काष्ठा receive_queue *rq = vi->rq;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा send_queue *sq;
	अचिन्हित पूर्णांक len;
	पूर्णांक packets = 0;
	पूर्णांक bytes = 0;
	पूर्णांक nxmit = 0;
	पूर्णांक kicks = 0;
	व्योम *ptr;
	पूर्णांक ret;
	पूर्णांक i;

	/* Only allow nकरो_xdp_xmit अगर XDP is loaded on dev, as this
	 * indicate XDP resources have been successfully allocated.
	 */
	xdp_prog = rcu_access_poपूर्णांकer(rq->xdp_prog);
	अगर (!xdp_prog)
		वापस -ENXIO;

	sq = virtnet_xdp_get_sq(vi);

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Free up any pending old buffers beक्रमe queueing new ones. */
	जबतक ((ptr = virtqueue_get_buf(sq->vq, &len)) != शून्य) अणु
		अगर (likely(is_xdp_frame(ptr))) अणु
			काष्ठा xdp_frame *frame = ptr_to_xdp(ptr);

			bytes += frame->len;
			xdp_वापस_frame(frame);
		पूर्ण अन्यथा अणु
			काष्ठा sk_buff *skb = ptr;

			bytes += skb->len;
			napi_consume_skb(skb, false);
		पूर्ण
		packets++;
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *xdpf = frames[i];

		अगर (__virtnet_xdp_xmit_one(vi, sq, xdpf))
			अवरोध;
		nxmit++;
	पूर्ण
	ret = nxmit;

	अगर (flags & XDP_XMIT_FLUSH) अणु
		अगर (virtqueue_kick_prepare(sq->vq) && virtqueue_notअगरy(sq->vq))
			kicks = 1;
	पूर्ण
out:
	u64_stats_update_begin(&sq->stats.syncp);
	sq->stats.bytes += bytes;
	sq->stats.packets += packets;
	sq->stats.xdp_tx += n;
	sq->stats.xdp_tx_drops += n - nxmit;
	sq->stats.kicks += kicks;
	u64_stats_update_end(&sq->stats.syncp);

	virtnet_xdp_put_sq(vi, sq);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक virtnet_get_headroom(काष्ठा virtnet_info *vi)
अणु
	वापस vi->xdp_enabled ? VIRTIO_XDP_HEADROOM : 0;
पूर्ण

/* We copy the packet क्रम XDP in the following हालs:
 *
 * 1) Packet is scattered across multiple rx buffers.
 * 2) Headroom space is insufficient.
 *
 * This is inefficient but it's a temporary condition that
 * we hit right after XDP is enabled and until queue is refilled
 * with large buffers with sufficient headroom - so it should affect
 * at most queue size packets.
 * Afterwards, the conditions to enable
 * XDP should preclude the underlying device from sending packets
 * across multiple buffers (num_buf > 1), and we make sure buffers
 * have enough headroom.
 */
अटल काष्ठा page *xdp_linearize_page(काष्ठा receive_queue *rq,
				       u16 *num_buf,
				       काष्ठा page *p,
				       पूर्णांक offset,
				       पूर्णांक page_off,
				       अचिन्हित पूर्णांक *len)
अणु
	काष्ठा page *page = alloc_page(GFP_ATOMIC);

	अगर (!page)
		वापस शून्य;

	स_नकल(page_address(page) + page_off, page_address(p) + offset, *len);
	page_off += *len;

	जबतक (--*num_buf) अणु
		पूर्णांक tailroom = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
		अचिन्हित पूर्णांक buflen;
		व्योम *buf;
		पूर्णांक off;

		buf = virtqueue_get_buf(rq->vq, &buflen);
		अगर (unlikely(!buf))
			जाओ err_buf;

		p = virt_to_head_page(buf);
		off = buf - page_address(p);

		/* guard against a misconfigured or uncooperative backend that
		 * is sending packet larger than the MTU.
		 */
		अगर ((page_off + buflen + tailroom) > PAGE_SIZE) अणु
			put_page(p);
			जाओ err_buf;
		पूर्ण

		स_नकल(page_address(page) + page_off,
		       page_address(p) + off, buflen);
		page_off += buflen;
		put_page(p);
	पूर्ण

	/* Headroom करोes not contribute to packet length */
	*len = page_off - VIRTIO_XDP_HEADROOM;
	वापस page;
err_buf:
	__मुक्त_pages(page, 0);
	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *receive_small(काष्ठा net_device *dev,
				     काष्ठा virtnet_info *vi,
				     काष्ठा receive_queue *rq,
				     व्योम *buf, व्योम *ctx,
				     अचिन्हित पूर्णांक len,
				     अचिन्हित पूर्णांक *xdp_xmit,
				     काष्ठा virtnet_rq_stats *stats)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा bpf_prog *xdp_prog;
	अचिन्हित पूर्णांक xdp_headroom = (अचिन्हित दीर्घ)ctx;
	अचिन्हित पूर्णांक header_offset = VIRTNET_RX_PAD + xdp_headroom;
	अचिन्हित पूर्णांक headroom = vi->hdr_len + header_offset;
	अचिन्हित पूर्णांक buflen = SKB_DATA_ALIGN(GOOD_PACKET_LEN + headroom) +
			      SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	काष्ठा page *page = virt_to_head_page(buf);
	अचिन्हित पूर्णांक delta = 0;
	काष्ठा page *xdp_page;
	पूर्णांक err;
	अचिन्हित पूर्णांक metasize = 0;

	len -= vi->hdr_len;
	stats->bytes += len;

	rcu_पढ़ो_lock();
	xdp_prog = rcu_dereference(rq->xdp_prog);
	अगर (xdp_prog) अणु
		काष्ठा virtio_net_hdr_mrg_rxbuf *hdr = buf + header_offset;
		काष्ठा xdp_frame *xdpf;
		काष्ठा xdp_buff xdp;
		व्योम *orig_data;
		u32 act;

		अगर (unlikely(hdr->hdr.gso_type))
			जाओ err_xdp;

		अगर (unlikely(xdp_headroom < virtnet_get_headroom(vi))) अणु
			पूर्णांक offset = buf - page_address(page) + header_offset;
			अचिन्हित पूर्णांक tlen = len + vi->hdr_len;
			u16 num_buf = 1;

			xdp_headroom = virtnet_get_headroom(vi);
			header_offset = VIRTNET_RX_PAD + xdp_headroom;
			headroom = vi->hdr_len + header_offset;
			buflen = SKB_DATA_ALIGN(GOOD_PACKET_LEN + headroom) +
				 SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
			xdp_page = xdp_linearize_page(rq, &num_buf, page,
						      offset, header_offset,
						      &tlen);
			अगर (!xdp_page)
				जाओ err_xdp;

			buf = page_address(xdp_page);
			put_page(page);
			page = xdp_page;
		पूर्ण

		xdp_init_buff(&xdp, buflen, &rq->xdp_rxq);
		xdp_prepare_buff(&xdp, buf + VIRTNET_RX_PAD + vi->hdr_len,
				 xdp_headroom, len, true);
		orig_data = xdp.data;
		act = bpf_prog_run_xdp(xdp_prog, &xdp);
		stats->xdp_packets++;

		चयन (act) अणु
		हाल XDP_PASS:
			/* Recalculate length in हाल bpf program changed it */
			delta = orig_data - xdp.data;
			len = xdp.data_end - xdp.data;
			metasize = xdp.data - xdp.data_meta;
			अवरोध;
		हाल XDP_TX:
			stats->xdp_tx++;
			xdpf = xdp_convert_buff_to_frame(&xdp);
			अगर (unlikely(!xdpf))
				जाओ err_xdp;
			err = virtnet_xdp_xmit(dev, 1, &xdpf, 0);
			अगर (unlikely(!err)) अणु
				xdp_वापस_frame_rx_napi(xdpf);
			पूर्ण अन्यथा अगर (unlikely(err < 0)) अणु
				trace_xdp_exception(vi->dev, xdp_prog, act);
				जाओ err_xdp;
			पूर्ण
			*xdp_xmit |= VIRTIO_XDP_TX;
			rcu_पढ़ो_unlock();
			जाओ xdp_xmit;
		हाल XDP_REसूचीECT:
			stats->xdp_redirects++;
			err = xdp_करो_redirect(dev, &xdp, xdp_prog);
			अगर (err)
				जाओ err_xdp;
			*xdp_xmit |= VIRTIO_XDP_REसूची;
			rcu_पढ़ो_unlock();
			जाओ xdp_xmit;
		शेष:
			bpf_warn_invalid_xdp_action(act);
			fallthrough;
		हाल XDP_ABORTED:
			trace_xdp_exception(vi->dev, xdp_prog, act);
			जाओ err_xdp;
		हाल XDP_DROP:
			जाओ err_xdp;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	skb = build_skb(buf, buflen);
	अगर (!skb) अणु
		put_page(page);
		जाओ err;
	पूर्ण
	skb_reserve(skb, headroom - delta);
	skb_put(skb, len);
	अगर (!xdp_prog) अणु
		buf += header_offset;
		स_नकल(skb_vnet_hdr(skb), buf, vi->hdr_len);
	पूर्ण /* keep zeroed vnet hdr since XDP is loaded */

	अगर (metasize)
		skb_metadata_set(skb, metasize);

err:
	वापस skb;

err_xdp:
	rcu_पढ़ो_unlock();
	stats->xdp_drops++;
	stats->drops++;
	put_page(page);
xdp_xmit:
	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *receive_big(काष्ठा net_device *dev,
				   काष्ठा virtnet_info *vi,
				   काष्ठा receive_queue *rq,
				   व्योम *buf,
				   अचिन्हित पूर्णांक len,
				   काष्ठा virtnet_rq_stats *stats)
अणु
	काष्ठा page *page = buf;
	काष्ठा sk_buff *skb =
		page_to_skb(vi, rq, page, 0, len, PAGE_SIZE, true, 0, 0);

	stats->bytes += len - vi->hdr_len;
	अगर (unlikely(!skb))
		जाओ err;

	वापस skb;

err:
	stats->drops++;
	give_pages(rq, page);
	वापस शून्य;
पूर्ण

अटल काष्ठा sk_buff *receive_mergeable(काष्ठा net_device *dev,
					 काष्ठा virtnet_info *vi,
					 काष्ठा receive_queue *rq,
					 व्योम *buf,
					 व्योम *ctx,
					 अचिन्हित पूर्णांक len,
					 अचिन्हित पूर्णांक *xdp_xmit,
					 काष्ठा virtnet_rq_stats *stats)
अणु
	काष्ठा virtio_net_hdr_mrg_rxbuf *hdr = buf;
	u16 num_buf = virtio16_to_cpu(vi->vdev, hdr->num_buffers);
	काष्ठा page *page = virt_to_head_page(buf);
	पूर्णांक offset = buf - page_address(page);
	काष्ठा sk_buff *head_skb, *curr_skb;
	काष्ठा bpf_prog *xdp_prog;
	अचिन्हित पूर्णांक truesize = mergeable_ctx_to_truesize(ctx);
	अचिन्हित पूर्णांक headroom = mergeable_ctx_to_headroom(ctx);
	अचिन्हित पूर्णांक metasize = 0;
	अचिन्हित पूर्णांक frame_sz;
	पूर्णांक err;

	head_skb = शून्य;
	stats->bytes += len - vi->hdr_len;

	rcu_पढ़ो_lock();
	xdp_prog = rcu_dereference(rq->xdp_prog);
	अगर (xdp_prog) अणु
		काष्ठा xdp_frame *xdpf;
		काष्ठा page *xdp_page;
		काष्ठा xdp_buff xdp;
		व्योम *data;
		u32 act;

		/* Transient failure which in theory could occur अगर
		 * in-flight packets from beक्रमe XDP was enabled reach
		 * the receive path after XDP is loaded.
		 */
		अगर (unlikely(hdr->hdr.gso_type))
			जाओ err_xdp;

		/* Buffers with headroom use PAGE_SIZE as alloc size,
		 * see add_recvbuf_mergeable() + get_mergeable_buf_len()
		 */
		frame_sz = headroom ? PAGE_SIZE : truesize;

		/* This happens when rx buffer size is underestimated
		 * or headroom is not enough because of the buffer
		 * was refilled beक्रमe XDP is set. This should only
		 * happen क्रम the first several packets, so we करोn't
		 * care much about its perक्रमmance.
		 */
		अगर (unlikely(num_buf > 1 ||
			     headroom < virtnet_get_headroom(vi))) अणु
			/* linearize data क्रम XDP */
			xdp_page = xdp_linearize_page(rq, &num_buf,
						      page, offset,
						      VIRTIO_XDP_HEADROOM,
						      &len);
			frame_sz = PAGE_SIZE;

			अगर (!xdp_page)
				जाओ err_xdp;
			offset = VIRTIO_XDP_HEADROOM;
		पूर्ण अन्यथा अणु
			xdp_page = page;
		पूर्ण

		/* Allow consuming headroom but reserve enough space to push
		 * the descriptor on अगर we get an XDP_TX वापस code.
		 */
		data = page_address(xdp_page) + offset;
		xdp_init_buff(&xdp, frame_sz - vi->hdr_len, &rq->xdp_rxq);
		xdp_prepare_buff(&xdp, data - VIRTIO_XDP_HEADROOM + vi->hdr_len,
				 VIRTIO_XDP_HEADROOM, len - vi->hdr_len, true);

		act = bpf_prog_run_xdp(xdp_prog, &xdp);
		stats->xdp_packets++;

		चयन (act) अणु
		हाल XDP_PASS:
			metasize = xdp.data - xdp.data_meta;

			/* recalculate offset to account क्रम any header
			 * adjusपंचांगents and minus the metasize to copy the
			 * metadata in page_to_skb(). Note other हालs करो not
			 * build an skb and aव्योम using offset
			 */
			offset = xdp.data - page_address(xdp_page) -
				 vi->hdr_len - metasize;

			/* recalculate len अगर xdp.data, xdp.data_end or
			 * xdp.data_meta were adjusted
			 */
			len = xdp.data_end - xdp.data + vi->hdr_len + metasize;
			/* We can only create skb based on xdp_page. */
			अगर (unlikely(xdp_page != page)) अणु
				rcu_पढ़ो_unlock();
				put_page(page);
				head_skb = page_to_skb(vi, rq, xdp_page, offset,
						       len, PAGE_SIZE, false,
						       metasize,
						       VIRTIO_XDP_HEADROOM);
				वापस head_skb;
			पूर्ण
			अवरोध;
		हाल XDP_TX:
			stats->xdp_tx++;
			xdpf = xdp_convert_buff_to_frame(&xdp);
			अगर (unlikely(!xdpf))
				जाओ err_xdp;
			err = virtnet_xdp_xmit(dev, 1, &xdpf, 0);
			अगर (unlikely(!err)) अणु
				xdp_वापस_frame_rx_napi(xdpf);
			पूर्ण अन्यथा अगर (unlikely(err < 0)) अणु
				trace_xdp_exception(vi->dev, xdp_prog, act);
				अगर (unlikely(xdp_page != page))
					put_page(xdp_page);
				जाओ err_xdp;
			पूर्ण
			*xdp_xmit |= VIRTIO_XDP_TX;
			अगर (unlikely(xdp_page != page))
				put_page(page);
			rcu_पढ़ो_unlock();
			जाओ xdp_xmit;
		हाल XDP_REसूचीECT:
			stats->xdp_redirects++;
			err = xdp_करो_redirect(dev, &xdp, xdp_prog);
			अगर (err) अणु
				अगर (unlikely(xdp_page != page))
					put_page(xdp_page);
				जाओ err_xdp;
			पूर्ण
			*xdp_xmit |= VIRTIO_XDP_REसूची;
			अगर (unlikely(xdp_page != page))
				put_page(page);
			rcu_पढ़ो_unlock();
			जाओ xdp_xmit;
		शेष:
			bpf_warn_invalid_xdp_action(act);
			fallthrough;
		हाल XDP_ABORTED:
			trace_xdp_exception(vi->dev, xdp_prog, act);
			fallthrough;
		हाल XDP_DROP:
			अगर (unlikely(xdp_page != page))
				__मुक्त_pages(xdp_page, 0);
			जाओ err_xdp;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (unlikely(len > truesize)) अणु
		pr_debug("%s: rx error: len %u exceeds truesize %lu\n",
			 dev->name, len, (अचिन्हित दीर्घ)ctx);
		dev->stats.rx_length_errors++;
		जाओ err_skb;
	पूर्ण

	head_skb = page_to_skb(vi, rq, page, offset, len, truesize, !xdp_prog,
			       metasize, headroom);
	curr_skb = head_skb;

	अगर (unlikely(!curr_skb))
		जाओ err_skb;
	जबतक (--num_buf) अणु
		पूर्णांक num_skb_frags;

		buf = virtqueue_get_buf_ctx(rq->vq, &len, &ctx);
		अगर (unlikely(!buf)) अणु
			pr_debug("%s: rx error: %d buffers out of %d missing\n",
				 dev->name, num_buf,
				 virtio16_to_cpu(vi->vdev,
						 hdr->num_buffers));
			dev->stats.rx_length_errors++;
			जाओ err_buf;
		पूर्ण

		stats->bytes += len;
		page = virt_to_head_page(buf);

		truesize = mergeable_ctx_to_truesize(ctx);
		अगर (unlikely(len > truesize)) अणु
			pr_debug("%s: rx error: len %u exceeds truesize %lu\n",
				 dev->name, len, (अचिन्हित दीर्घ)ctx);
			dev->stats.rx_length_errors++;
			जाओ err_skb;
		पूर्ण

		num_skb_frags = skb_shinfo(curr_skb)->nr_frags;
		अगर (unlikely(num_skb_frags == MAX_SKB_FRAGS)) अणु
			काष्ठा sk_buff *nskb = alloc_skb(0, GFP_ATOMIC);

			अगर (unlikely(!nskb))
				जाओ err_skb;
			अगर (curr_skb == head_skb)
				skb_shinfo(curr_skb)->frag_list = nskb;
			अन्यथा
				curr_skb->next = nskb;
			curr_skb = nskb;
			head_skb->truesize += nskb->truesize;
			num_skb_frags = 0;
		पूर्ण
		अगर (curr_skb != head_skb) अणु
			head_skb->data_len += len;
			head_skb->len += len;
			head_skb->truesize += truesize;
		पूर्ण
		offset = buf - page_address(page);
		अगर (skb_can_coalesce(curr_skb, num_skb_frags, page, offset)) अणु
			put_page(page);
			skb_coalesce_rx_frag(curr_skb, num_skb_frags - 1,
					     len, truesize);
		पूर्ण अन्यथा अणु
			skb_add_rx_frag(curr_skb, num_skb_frags, page,
					offset, len, truesize);
		पूर्ण
	पूर्ण

	ewma_pkt_len_add(&rq->mrg_avg_pkt_len, head_skb->len);
	वापस head_skb;

err_xdp:
	rcu_पढ़ो_unlock();
	stats->xdp_drops++;
err_skb:
	put_page(page);
	जबतक (num_buf-- > 1) अणु
		buf = virtqueue_get_buf(rq->vq, &len);
		अगर (unlikely(!buf)) अणु
			pr_debug("%s: rx error: %d buffers missing\n",
				 dev->name, num_buf);
			dev->stats.rx_length_errors++;
			अवरोध;
		पूर्ण
		stats->bytes += len;
		page = virt_to_head_page(buf);
		put_page(page);
	पूर्ण
err_buf:
	stats->drops++;
	dev_kमुक्त_skb(head_skb);
xdp_xmit:
	वापस शून्य;
पूर्ण

अटल व्योम receive_buf(काष्ठा virtnet_info *vi, काष्ठा receive_queue *rq,
			व्योम *buf, अचिन्हित पूर्णांक len, व्योम **ctx,
			अचिन्हित पूर्णांक *xdp_xmit,
			काष्ठा virtnet_rq_stats *stats)
अणु
	काष्ठा net_device *dev = vi->dev;
	काष्ठा sk_buff *skb;
	काष्ठा virtio_net_hdr_mrg_rxbuf *hdr;

	अगर (unlikely(len < vi->hdr_len + ETH_HLEN)) अणु
		pr_debug("%s: short packet %i\n", dev->name, len);
		dev->stats.rx_length_errors++;
		अगर (vi->mergeable_rx_bufs) अणु
			put_page(virt_to_head_page(buf));
		पूर्ण अन्यथा अगर (vi->big_packets) अणु
			give_pages(rq, buf);
		पूर्ण अन्यथा अणु
			put_page(virt_to_head_page(buf));
		पूर्ण
		वापस;
	पूर्ण

	अगर (vi->mergeable_rx_bufs)
		skb = receive_mergeable(dev, vi, rq, buf, ctx, len, xdp_xmit,
					stats);
	अन्यथा अगर (vi->big_packets)
		skb = receive_big(dev, vi, rq, buf, len, stats);
	अन्यथा
		skb = receive_small(dev, vi, rq, buf, ctx, len, xdp_xmit, stats);

	अगर (unlikely(!skb))
		वापस;

	hdr = skb_vnet_hdr(skb);

	अगर (hdr->hdr.flags & VIRTIO_NET_HDR_F_DATA_VALID)
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	अगर (virtio_net_hdr_to_skb(skb, &hdr->hdr,
				  virtio_is_little_endian(vi->vdev))) अणु
		net_warn_ratelimited("%s: bad gso: type: %u, size: %u\n",
				     dev->name, hdr->hdr.gso_type,
				     hdr->hdr.gso_size);
		जाओ frame_err;
	पूर्ण

	skb_record_rx_queue(skb, vq2rxq(rq->vq));
	skb->protocol = eth_type_trans(skb, dev);
	pr_debug("Receiving skb proto 0x%04x len %i type %i\n",
		 ntohs(skb->protocol), skb->len, skb->pkt_type);

	napi_gro_receive(&rq->napi, skb);
	वापस;

frame_err:
	dev->stats.rx_frame_errors++;
	dev_kमुक्त_skb(skb);
पूर्ण

/* Unlike mergeable buffers, all buffers are allocated to the
 * same size, except क्रम the headroom. For this reason we करो
 * not need to use  mergeable_len_to_ctx here - it is enough
 * to store the headroom as the context ignoring the truesize.
 */
अटल पूर्णांक add_recvbuf_small(काष्ठा virtnet_info *vi, काष्ठा receive_queue *rq,
			     gfp_t gfp)
अणु
	काष्ठा page_frag *alloc_frag = &rq->alloc_frag;
	अक्षर *buf;
	अचिन्हित पूर्णांक xdp_headroom = virtnet_get_headroom(vi);
	व्योम *ctx = (व्योम *)(अचिन्हित दीर्घ)xdp_headroom;
	पूर्णांक len = vi->hdr_len + VIRTNET_RX_PAD + GOOD_PACKET_LEN + xdp_headroom;
	पूर्णांक err;

	len = SKB_DATA_ALIGN(len) +
	      SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	अगर (unlikely(!skb_page_frag_refill(len, alloc_frag, gfp)))
		वापस -ENOMEM;

	buf = (अक्षर *)page_address(alloc_frag->page) + alloc_frag->offset;
	get_page(alloc_frag->page);
	alloc_frag->offset += len;
	sg_init_one(rq->sg, buf + VIRTNET_RX_PAD + xdp_headroom,
		    vi->hdr_len + GOOD_PACKET_LEN);
	err = virtqueue_add_inbuf_ctx(rq->vq, rq->sg, 1, buf, ctx, gfp);
	अगर (err < 0)
		put_page(virt_to_head_page(buf));
	वापस err;
पूर्ण

अटल पूर्णांक add_recvbuf_big(काष्ठा virtnet_info *vi, काष्ठा receive_queue *rq,
			   gfp_t gfp)
अणु
	काष्ठा page *first, *list = शून्य;
	अक्षर *p;
	पूर्णांक i, err, offset;

	sg_init_table(rq->sg, MAX_SKB_FRAGS + 2);

	/* page in rq->sg[MAX_SKB_FRAGS + 1] is list tail */
	क्रम (i = MAX_SKB_FRAGS + 1; i > 1; --i) अणु
		first = get_a_page(rq, gfp);
		अगर (!first) अणु
			अगर (list)
				give_pages(rq, list);
			वापस -ENOMEM;
		पूर्ण
		sg_set_buf(&rq->sg[i], page_address(first), PAGE_SIZE);

		/* chain new page in list head to match sg */
		first->निजी = (अचिन्हित दीर्घ)list;
		list = first;
	पूर्ण

	first = get_a_page(rq, gfp);
	अगर (!first) अणु
		give_pages(rq, list);
		वापस -ENOMEM;
	पूर्ण
	p = page_address(first);

	/* rq->sg[0], rq->sg[1] share the same page */
	/* a separated rq->sg[0] क्रम header - required in हाल !any_header_sg */
	sg_set_buf(&rq->sg[0], p, vi->hdr_len);

	/* rq->sg[1] क्रम data packet, from offset */
	offset = माप(काष्ठा padded_vnet_hdr);
	sg_set_buf(&rq->sg[1], p + offset, PAGE_SIZE - offset);

	/* chain first in list head */
	first->निजी = (अचिन्हित दीर्घ)list;
	err = virtqueue_add_inbuf(rq->vq, rq->sg, MAX_SKB_FRAGS + 2,
				  first, gfp);
	अगर (err < 0)
		give_pages(rq, first);

	वापस err;
पूर्ण

अटल अचिन्हित पूर्णांक get_mergeable_buf_len(काष्ठा receive_queue *rq,
					  काष्ठा ewma_pkt_len *avg_pkt_len,
					  अचिन्हित पूर्णांक room)
अणु
	स्थिर माप_प्रकार hdr_len = माप(काष्ठा virtio_net_hdr_mrg_rxbuf);
	अचिन्हित पूर्णांक len;

	अगर (room)
		वापस PAGE_SIZE - room;

	len = hdr_len +	clamp_t(अचिन्हित पूर्णांक, ewma_pkt_len_पढ़ो(avg_pkt_len),
				rq->min_buf_len, PAGE_SIZE - hdr_len);

	वापस ALIGN(len, L1_CACHE_BYTES);
पूर्ण

अटल पूर्णांक add_recvbuf_mergeable(काष्ठा virtnet_info *vi,
				 काष्ठा receive_queue *rq, gfp_t gfp)
अणु
	काष्ठा page_frag *alloc_frag = &rq->alloc_frag;
	अचिन्हित पूर्णांक headroom = virtnet_get_headroom(vi);
	अचिन्हित पूर्णांक tailroom = headroom ? माप(काष्ठा skb_shared_info) : 0;
	अचिन्हित पूर्णांक room = SKB_DATA_ALIGN(headroom + tailroom);
	अक्षर *buf;
	व्योम *ctx;
	पूर्णांक err;
	अचिन्हित पूर्णांक len, hole;

	/* Extra tailroom is needed to satisfy XDP's assumption. This
	 * means rx frags coalescing won't work, but consider we've
	 * disabled GSO क्रम XDP, it won't be a big issue.
	 */
	len = get_mergeable_buf_len(rq, &rq->mrg_avg_pkt_len, room);
	अगर (unlikely(!skb_page_frag_refill(len + room, alloc_frag, gfp)))
		वापस -ENOMEM;

	buf = (अक्षर *)page_address(alloc_frag->page) + alloc_frag->offset;
	buf += headroom; /* advance address leaving hole at front of pkt */
	get_page(alloc_frag->page);
	alloc_frag->offset += len + room;
	hole = alloc_frag->size - alloc_frag->offset;
	अगर (hole < len + room) अणु
		/* To aव्योम पूर्णांकernal fragmentation, अगर there is very likely not
		 * enough space क्रम another buffer, add the reमुख्यing space to
		 * the current buffer.
		 */
		len += hole;
		alloc_frag->offset += hole;
	पूर्ण

	sg_init_one(rq->sg, buf, len);
	ctx = mergeable_len_to_ctx(len, headroom);
	err = virtqueue_add_inbuf_ctx(rq->vq, rq->sg, 1, buf, ctx, gfp);
	अगर (err < 0)
		put_page(virt_to_head_page(buf));

	वापस err;
पूर्ण

/*
 * Returns false अगर we couldn't fill entirely (OOM).
 *
 * Normally run in the receive path, but can also be run from nकरो_खोलो
 * beक्रमe we're receiving packets, or from refill_work which is
 * careful to disable receiving (using napi_disable).
 */
अटल bool try_fill_recv(काष्ठा virtnet_info *vi, काष्ठा receive_queue *rq,
			  gfp_t gfp)
अणु
	पूर्णांक err;
	bool oom;

	करो अणु
		अगर (vi->mergeable_rx_bufs)
			err = add_recvbuf_mergeable(vi, rq, gfp);
		अन्यथा अगर (vi->big_packets)
			err = add_recvbuf_big(vi, rq, gfp);
		अन्यथा
			err = add_recvbuf_small(vi, rq, gfp);

		oom = err == -ENOMEM;
		अगर (err)
			अवरोध;
	पूर्ण जबतक (rq->vq->num_मुक्त);
	अगर (virtqueue_kick_prepare(rq->vq) && virtqueue_notअगरy(rq->vq)) अणु
		अचिन्हित दीर्घ flags;

		flags = u64_stats_update_begin_irqsave(&rq->stats.syncp);
		rq->stats.kicks++;
		u64_stats_update_end_irqrestore(&rq->stats.syncp, flags);
	पूर्ण

	वापस !oom;
पूर्ण

अटल व्योम skb_recv_करोne(काष्ठा virtqueue *rvq)
अणु
	काष्ठा virtnet_info *vi = rvq->vdev->priv;
	काष्ठा receive_queue *rq = &vi->rq[vq2rxq(rvq)];

	virtqueue_napi_schedule(&rq->napi, rvq);
पूर्ण

अटल व्योम virtnet_napi_enable(काष्ठा virtqueue *vq, काष्ठा napi_काष्ठा *napi)
अणु
	napi_enable(napi);

	/* If all buffers were filled by other side beक्रमe we napi_enabled, we
	 * won't get another पूर्णांकerrupt, so process any outstanding packets now.
	 * Call local_bh_enable after to trigger softIRQ processing.
	 */
	local_bh_disable();
	virtqueue_napi_schedule(napi, vq);
	local_bh_enable();
पूर्ण

अटल व्योम virtnet_napi_tx_enable(काष्ठा virtnet_info *vi,
				   काष्ठा virtqueue *vq,
				   काष्ठा napi_काष्ठा *napi)
अणु
	अगर (!napi->weight)
		वापस;

	/* Tx napi touches cachelines on the cpu handling tx पूर्णांकerrupts. Only
	 * enable the feature अगर this is likely affine with the transmit path.
	 */
	अगर (!vi->affinity_hपूर्णांक_set) अणु
		napi->weight = 0;
		वापस;
	पूर्ण

	वापस virtnet_napi_enable(vq, napi);
पूर्ण

अटल व्योम virtnet_napi_tx_disable(काष्ठा napi_काष्ठा *napi)
अणु
	अगर (napi->weight)
		napi_disable(napi);
पूर्ण

अटल व्योम refill_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtnet_info *vi =
		container_of(work, काष्ठा virtnet_info, refill.work);
	bool still_empty;
	पूर्णांक i;

	क्रम (i = 0; i < vi->curr_queue_pairs; i++) अणु
		काष्ठा receive_queue *rq = &vi->rq[i];

		napi_disable(&rq->napi);
		still_empty = !try_fill_recv(vi, rq, GFP_KERNEL);
		virtnet_napi_enable(rq->vq, &rq->napi);

		/* In theory, this can happen: अगर we करोn't get any buffers in
		 * we will *never* try to fill again.
		 */
		अगर (still_empty)
			schedule_delayed_work(&vi->refill, HZ/2);
	पूर्ण
पूर्ण

अटल पूर्णांक virtnet_receive(काष्ठा receive_queue *rq, पूर्णांक budget,
			   अचिन्हित पूर्णांक *xdp_xmit)
अणु
	काष्ठा virtnet_info *vi = rq->vq->vdev->priv;
	काष्ठा virtnet_rq_stats stats = अणुपूर्ण;
	अचिन्हित पूर्णांक len;
	व्योम *buf;
	पूर्णांक i;

	अगर (!vi->big_packets || vi->mergeable_rx_bufs) अणु
		व्योम *ctx;

		जबतक (stats.packets < budget &&
		       (buf = virtqueue_get_buf_ctx(rq->vq, &len, &ctx))) अणु
			receive_buf(vi, rq, buf, len, ctx, xdp_xmit, &stats);
			stats.packets++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (stats.packets < budget &&
		       (buf = virtqueue_get_buf(rq->vq, &len)) != शून्य) अणु
			receive_buf(vi, rq, buf, len, शून्य, xdp_xmit, &stats);
			stats.packets++;
		पूर्ण
	पूर्ण

	अगर (rq->vq->num_मुक्त > min((अचिन्हित पूर्णांक)budget, virtqueue_get_vring_size(rq->vq)) / 2) अणु
		अगर (!try_fill_recv(vi, rq, GFP_ATOMIC))
			schedule_delayed_work(&vi->refill, 0);
	पूर्ण

	u64_stats_update_begin(&rq->stats.syncp);
	क्रम (i = 0; i < VIRTNET_RQ_STATS_LEN; i++) अणु
		माप_प्रकार offset = virtnet_rq_stats_desc[i].offset;
		u64 *item;

		item = (u64 *)((u8 *)&rq->stats + offset);
		*item += *(u64 *)((u8 *)&stats + offset);
	पूर्ण
	u64_stats_update_end(&rq->stats.syncp);

	वापस stats.packets;
पूर्ण

अटल व्योम मुक्त_old_xmit_skbs(काष्ठा send_queue *sq, bool in_napi)
अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक packets = 0;
	अचिन्हित पूर्णांक bytes = 0;
	व्योम *ptr;

	जबतक ((ptr = virtqueue_get_buf(sq->vq, &len)) != शून्य) अणु
		अगर (likely(!is_xdp_frame(ptr))) अणु
			काष्ठा sk_buff *skb = ptr;

			pr_debug("Sent skb %p\n", skb);

			bytes += skb->len;
			napi_consume_skb(skb, in_napi);
		पूर्ण अन्यथा अणु
			काष्ठा xdp_frame *frame = ptr_to_xdp(ptr);

			bytes += frame->len;
			xdp_वापस_frame(frame);
		पूर्ण
		packets++;
	पूर्ण

	/* Aव्योम overhead when no packets have been processed
	 * happens when called speculatively from start_xmit.
	 */
	अगर (!packets)
		वापस;

	u64_stats_update_begin(&sq->stats.syncp);
	sq->stats.bytes += bytes;
	sq->stats.packets += packets;
	u64_stats_update_end(&sq->stats.syncp);
पूर्ण

अटल bool is_xdp_raw_buffer_queue(काष्ठा virtnet_info *vi, पूर्णांक q)
अणु
	अगर (q < (vi->curr_queue_pairs - vi->xdp_queue_pairs))
		वापस false;
	अन्यथा अगर (q < vi->curr_queue_pairs)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम virtnet_poll_cleantx(काष्ठा receive_queue *rq)
अणु
	काष्ठा virtnet_info *vi = rq->vq->vdev->priv;
	अचिन्हित पूर्णांक index = vq2rxq(rq->vq);
	काष्ठा send_queue *sq = &vi->sq[index];
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(vi->dev, index);

	अगर (!sq->napi.weight || is_xdp_raw_buffer_queue(vi, index))
		वापस;

	अगर (__netअगर_tx_trylock(txq)) अणु
		मुक्त_old_xmit_skbs(sq, true);
		__netअगर_tx_unlock(txq);
	पूर्ण

	अगर (sq->vq->num_मुक्त >= 2 + MAX_SKB_FRAGS)
		netअगर_tx_wake_queue(txq);
पूर्ण

अटल पूर्णांक virtnet_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा receive_queue *rq =
		container_of(napi, काष्ठा receive_queue, napi);
	काष्ठा virtnet_info *vi = rq->vq->vdev->priv;
	काष्ठा send_queue *sq;
	अचिन्हित पूर्णांक received;
	अचिन्हित पूर्णांक xdp_xmit = 0;

	virtnet_poll_cleantx(rq);

	received = virtnet_receive(rq, budget, &xdp_xmit);

	/* Out of packets? */
	अगर (received < budget)
		virtqueue_napi_complete(napi, rq->vq, received);

	अगर (xdp_xmit & VIRTIO_XDP_REसूची)
		xdp_करो_flush();

	अगर (xdp_xmit & VIRTIO_XDP_TX) अणु
		sq = virtnet_xdp_get_sq(vi);
		अगर (virtqueue_kick_prepare(sq->vq) && virtqueue_notअगरy(sq->vq)) अणु
			u64_stats_update_begin(&sq->stats.syncp);
			sq->stats.kicks++;
			u64_stats_update_end(&sq->stats.syncp);
		पूर्ण
		virtnet_xdp_put_sq(vi, sq);
	पूर्ण

	वापस received;
पूर्ण

अटल पूर्णांक virtnet_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	पूर्णांक i, err;

	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		अगर (i < vi->curr_queue_pairs)
			/* Make sure we have some buffers: अगर oom use wq. */
			अगर (!try_fill_recv(vi, &vi->rq[i], GFP_KERNEL))
				schedule_delayed_work(&vi->refill, 0);

		err = xdp_rxq_info_reg(&vi->rq[i].xdp_rxq, dev, i, vi->rq[i].napi.napi_id);
		अगर (err < 0)
			वापस err;

		err = xdp_rxq_info_reg_mem_model(&vi->rq[i].xdp_rxq,
						 MEM_TYPE_PAGE_SHARED, शून्य);
		अगर (err < 0) अणु
			xdp_rxq_info_unreg(&vi->rq[i].xdp_rxq);
			वापस err;
		पूर्ण

		virtnet_napi_enable(vi->rq[i].vq, &vi->rq[i].napi);
		virtnet_napi_tx_enable(vi, vi->sq[i].vq, &vi->sq[i].napi);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक virtnet_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा send_queue *sq = container_of(napi, काष्ठा send_queue, napi);
	काष्ठा virtnet_info *vi = sq->vq->vdev->priv;
	अचिन्हित पूर्णांक index = vq2txq(sq->vq);
	काष्ठा netdev_queue *txq;

	अगर (unlikely(is_xdp_raw_buffer_queue(vi, index))) अणु
		/* We करोn't need to enable cb क्रम XDP */
		napi_complete_करोne(napi, 0);
		वापस 0;
	पूर्ण

	txq = netdev_get_tx_queue(vi->dev, index);
	__netअगर_tx_lock(txq, raw_smp_processor_id());
	मुक्त_old_xmit_skbs(sq, true);
	__netअगर_tx_unlock(txq);

	virtqueue_napi_complete(napi, sq->vq, 0);

	अगर (sq->vq->num_मुक्त >= 2 + MAX_SKB_FRAGS)
		netअगर_tx_wake_queue(txq);

	वापस 0;
पूर्ण

अटल पूर्णांक xmit_skb(काष्ठा send_queue *sq, काष्ठा sk_buff *skb)
अणु
	काष्ठा virtio_net_hdr_mrg_rxbuf *hdr;
	स्थिर अचिन्हित अक्षर *dest = ((काष्ठा ethhdr *)skb->data)->h_dest;
	काष्ठा virtnet_info *vi = sq->vq->vdev->priv;
	पूर्णांक num_sg;
	अचिन्हित hdr_len = vi->hdr_len;
	bool can_push;

	pr_debug("%s: xmit %p %pM\n", vi->dev->name, skb, dest);

	can_push = vi->any_header_sg &&
		!((अचिन्हित दीर्घ)skb->data & (__alignof__(*hdr) - 1)) &&
		!skb_header_cloned(skb) && skb_headroom(skb) >= hdr_len;
	/* Even अगर we can, करोn't push here yet as this would skew
	 * csum_start offset below. */
	अगर (can_push)
		hdr = (काष्ठा virtio_net_hdr_mrg_rxbuf *)(skb->data - hdr_len);
	अन्यथा
		hdr = skb_vnet_hdr(skb);

	अगर (virtio_net_hdr_from_skb(skb, &hdr->hdr,
				    virtio_is_little_endian(vi->vdev), false,
				    0))
		BUG();

	अगर (vi->mergeable_rx_bufs)
		hdr->num_buffers = 0;

	sg_init_table(sq->sg, skb_shinfo(skb)->nr_frags + (can_push ? 1 : 2));
	अगर (can_push) अणु
		__skb_push(skb, hdr_len);
		num_sg = skb_to_sgvec(skb, sq->sg, 0, skb->len);
		अगर (unlikely(num_sg < 0))
			वापस num_sg;
		/* Pull header back to aव्योम skew in tx bytes calculations. */
		__skb_pull(skb, hdr_len);
	पूर्ण अन्यथा अणु
		sg_set_buf(sq->sg, hdr, hdr_len);
		num_sg = skb_to_sgvec(skb, sq->sg + 1, 0, skb->len);
		अगर (unlikely(num_sg < 0))
			वापस num_sg;
		num_sg++;
	पूर्ण
	वापस virtqueue_add_outbuf(sq->vq, sq->sg, num_sg, skb, GFP_ATOMIC);
पूर्ण

अटल netdev_tx_t start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	पूर्णांक qnum = skb_get_queue_mapping(skb);
	काष्ठा send_queue *sq = &vi->sq[qnum];
	पूर्णांक err;
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(dev, qnum);
	bool kick = !netdev_xmit_more();
	bool use_napi = sq->napi.weight;

	/* Free up any pending old buffers beक्रमe queueing new ones. */
	मुक्त_old_xmit_skbs(sq, false);

	अगर (use_napi && kick)
		virtqueue_enable_cb_delayed(sq->vq);

	/* बारtamp packet in software */
	skb_tx_बारtamp(skb);

	/* Try to transmit */
	err = xmit_skb(sq, skb);

	/* This should not happen! */
	अगर (unlikely(err)) अणु
		dev->stats.tx_fअगरo_errors++;
		अगर (net_ratelimit())
			dev_warn(&dev->dev,
				 "Unexpected TXQ (%d) queue failure: %d\n",
				 qnum, err);
		dev->stats.tx_dropped++;
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Don't रुको up क्रम transmitted skbs to be मुक्तd. */
	अगर (!use_napi) अणु
		skb_orphan(skb);
		nf_reset_ct(skb);
	पूर्ण

	/* If running out of space, stop queue to aव्योम getting packets that we
	 * are then unable to transmit.
	 * An alternative would be to क्रमce queuing layer to requeue the skb by
	 * वापसing NETDEV_TX_BUSY. However, NETDEV_TX_BUSY should not be
	 * वापसed in a normal path of operation: it means that driver is not
	 * मुख्यtaining the TX queue stop/start state properly, and causes
	 * the stack to करो a non-trivial amount of useless work.
	 * Since most packets only take 1 or 2 ring slots, stopping the queue
	 * early means 16 slots are typically wasted.
	 */
	अगर (sq->vq->num_मुक्त < 2+MAX_SKB_FRAGS) अणु
		netअगर_stop_subqueue(dev, qnum);
		अगर (!use_napi &&
		    unlikely(!virtqueue_enable_cb_delayed(sq->vq))) अणु
			/* More just got used, मुक्त them then recheck. */
			मुक्त_old_xmit_skbs(sq, false);
			अगर (sq->vq->num_मुक्त >= 2+MAX_SKB_FRAGS) अणु
				netअगर_start_subqueue(dev, qnum);
				virtqueue_disable_cb(sq->vq);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (kick || netअगर_xmit_stopped(txq)) अणु
		अगर (virtqueue_kick_prepare(sq->vq) && virtqueue_notअगरy(sq->vq)) अणु
			u64_stats_update_begin(&sq->stats.syncp);
			sq->stats.kicks++;
			u64_stats_update_end(&sq->stats.syncp);
		पूर्ण
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

/*
 * Send command via the control virtqueue and check status.  Commands
 * supported by the hypervisor, as indicated by feature bits, should
 * never fail unless improperly क्रमmatted.
 */
अटल bool virtnet_send_command(काष्ठा virtnet_info *vi, u8 class, u8 cmd,
				 काष्ठा scatterlist *out)
अणु
	काष्ठा scatterlist *sgs[4], hdr, stat;
	अचिन्हित out_num = 0, पंचांगp;

	/* Caller should know better */
	BUG_ON(!virtio_has_feature(vi->vdev, VIRTIO_NET_F_CTRL_VQ));

	vi->ctrl->status = ~0;
	vi->ctrl->hdr.class = class;
	vi->ctrl->hdr.cmd = cmd;
	/* Add header */
	sg_init_one(&hdr, &vi->ctrl->hdr, माप(vi->ctrl->hdr));
	sgs[out_num++] = &hdr;

	अगर (out)
		sgs[out_num++] = out;

	/* Add वापस status. */
	sg_init_one(&stat, &vi->ctrl->status, माप(vi->ctrl->status));
	sgs[out_num] = &stat;

	BUG_ON(out_num + 1 > ARRAY_SIZE(sgs));
	virtqueue_add_sgs(vi->cvq, sgs, out_num, 1, vi, GFP_ATOMIC);

	अगर (unlikely(!virtqueue_kick(vi->cvq)))
		वापस vi->ctrl->status == VIRTIO_NET_OK;

	/* Spin क्रम a response, the kick causes an ioport ग_लिखो, trapping
	 * पूर्णांकo the hypervisor, so the request should be handled immediately.
	 */
	जबतक (!virtqueue_get_buf(vi->cvq, &पंचांगp) &&
	       !virtqueue_is_broken(vi->cvq))
		cpu_relax();

	वापस vi->ctrl->status == VIRTIO_NET_OK;
पूर्ण

अटल पूर्णांक virtnet_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	काष्ठा virtio_device *vdev = vi->vdev;
	पूर्णांक ret;
	काष्ठा sockaddr *addr;
	काष्ठा scatterlist sg;

	अगर (virtio_has_feature(vi->vdev, VIRTIO_NET_F_STANDBY))
		वापस -EOPNOTSUPP;

	addr = kmemdup(p, माप(*addr), GFP_KERNEL);
	अगर (!addr)
		वापस -ENOMEM;

	ret = eth_prepare_mac_addr_change(dev, addr);
	अगर (ret)
		जाओ out;

	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_CTRL_MAC_ADDR)) अणु
		sg_init_one(&sg, addr->sa_data, dev->addr_len);
		अगर (!virtnet_send_command(vi, VIRTIO_NET_CTRL_MAC,
					  VIRTIO_NET_CTRL_MAC_ADDR_SET, &sg)) अणु
			dev_warn(&vdev->dev,
				 "Failed to set mac address by vq command.\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (virtio_has_feature(vdev, VIRTIO_NET_F_MAC) &&
		   !virtio_has_feature(vdev, VIRTIO_F_VERSION_1)) अणु
		अचिन्हित पूर्णांक i;

		/* Naturally, this has an atomicity problem. */
		क्रम (i = 0; i < dev->addr_len; i++)
			virtio_cग_लिखो8(vdev,
				       दुरत्व(काष्ठा virtio_net_config, mac) +
				       i, addr->sa_data[i]);
	पूर्ण

	eth_commit_mac_addr_change(dev, p);
	ret = 0;

out:
	kमुक्त(addr);
	वापस ret;
पूर्ण

अटल व्योम virtnet_stats(काष्ठा net_device *dev,
			  काष्ठा rtnl_link_stats64 *tot)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	अचिन्हित पूर्णांक start;
	पूर्णांक i;

	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		u64 tpackets, tbytes, rpackets, rbytes, rdrops;
		काष्ठा receive_queue *rq = &vi->rq[i];
		काष्ठा send_queue *sq = &vi->sq[i];

		करो अणु
			start = u64_stats_fetch_begin_irq(&sq->stats.syncp);
			tpackets = sq->stats.packets;
			tbytes   = sq->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&sq->stats.syncp, start));

		करो अणु
			start = u64_stats_fetch_begin_irq(&rq->stats.syncp);
			rpackets = rq->stats.packets;
			rbytes   = rq->stats.bytes;
			rdrops   = rq->stats.drops;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&rq->stats.syncp, start));

		tot->rx_packets += rpackets;
		tot->tx_packets += tpackets;
		tot->rx_bytes   += rbytes;
		tot->tx_bytes   += tbytes;
		tot->rx_dropped += rdrops;
	पूर्ण

	tot->tx_dropped = dev->stats.tx_dropped;
	tot->tx_fअगरo_errors = dev->stats.tx_fअगरo_errors;
	tot->rx_length_errors = dev->stats.rx_length_errors;
	tot->rx_frame_errors = dev->stats.rx_frame_errors;
पूर्ण

अटल व्योम virtnet_ack_link_announce(काष्ठा virtnet_info *vi)
अणु
	rtnl_lock();
	अगर (!virtnet_send_command(vi, VIRTIO_NET_CTRL_ANNOUNCE,
				  VIRTIO_NET_CTRL_ANNOUNCE_ACK, शून्य))
		dev_warn(&vi->dev->dev, "Failed to ack link announce.\n");
	rtnl_unlock();
पूर्ण

अटल पूर्णांक _virtnet_set_queues(काष्ठा virtnet_info *vi, u16 queue_pairs)
अणु
	काष्ठा scatterlist sg;
	काष्ठा net_device *dev = vi->dev;

	अगर (!vi->has_cvq || !virtio_has_feature(vi->vdev, VIRTIO_NET_F_MQ))
		वापस 0;

	vi->ctrl->mq.virtqueue_pairs = cpu_to_virtio16(vi->vdev, queue_pairs);
	sg_init_one(&sg, &vi->ctrl->mq, माप(vi->ctrl->mq));

	अगर (!virtnet_send_command(vi, VIRTIO_NET_CTRL_MQ,
				  VIRTIO_NET_CTRL_MQ_VQ_PAIRS_SET, &sg)) अणु
		dev_warn(&dev->dev, "Fail to set num of queue pairs to %d\n",
			 queue_pairs);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		vi->curr_queue_pairs = queue_pairs;
		/* virtnet_खोलो() will refill when device is going to up. */
		अगर (dev->flags & IFF_UP)
			schedule_delayed_work(&vi->refill, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक virtnet_set_queues(काष्ठा virtnet_info *vi, u16 queue_pairs)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = _virtnet_set_queues(vi, queue_pairs);
	rtnl_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक virtnet_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	पूर्णांक i;

	/* Make sure refill_work करोesn't re-enable napi! */
	cancel_delayed_work_sync(&vi->refill);

	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		xdp_rxq_info_unreg(&vi->rq[i].xdp_rxq);
		napi_disable(&vi->rq[i].napi);
		virtnet_napi_tx_disable(&vi->sq[i].napi);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम virtnet_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	काष्ठा scatterlist sg[2];
	काष्ठा virtio_net_ctrl_mac *mac_data;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक uc_count;
	पूर्णांक mc_count;
	व्योम *buf;
	पूर्णांक i;

	/* We can't dynamically set nकरो_set_rx_mode, so वापस gracefully */
	अगर (!virtio_has_feature(vi->vdev, VIRTIO_NET_F_CTRL_RX))
		वापस;

	vi->ctrl->promisc = ((dev->flags & IFF_PROMISC) != 0);
	vi->ctrl->allmulti = ((dev->flags & IFF_ALLMULTI) != 0);

	sg_init_one(sg, &vi->ctrl->promisc, माप(vi->ctrl->promisc));

	अगर (!virtnet_send_command(vi, VIRTIO_NET_CTRL_RX,
				  VIRTIO_NET_CTRL_RX_PROMISC, sg))
		dev_warn(&dev->dev, "Failed to %sable promisc mode.\n",
			 vi->ctrl->promisc ? "en" : "dis");

	sg_init_one(sg, &vi->ctrl->allmulti, माप(vi->ctrl->allmulti));

	अगर (!virtnet_send_command(vi, VIRTIO_NET_CTRL_RX,
				  VIRTIO_NET_CTRL_RX_ALLMULTI, sg))
		dev_warn(&dev->dev, "Failed to %sable allmulti mode.\n",
			 vi->ctrl->allmulti ? "en" : "dis");

	uc_count = netdev_uc_count(dev);
	mc_count = netdev_mc_count(dev);
	/* MAC filter - use one buffer क्रम both lists */
	buf = kzalloc(((uc_count + mc_count) * ETH_ALEN) +
		      (2 * माप(mac_data->entries)), GFP_ATOMIC);
	mac_data = buf;
	अगर (!buf)
		वापस;

	sg_init_table(sg, 2);

	/* Store the unicast list and count in the front of the buffer */
	mac_data->entries = cpu_to_virtio32(vi->vdev, uc_count);
	i = 0;
	netdev_क्रम_each_uc_addr(ha, dev)
		स_नकल(&mac_data->macs[i++][0], ha->addr, ETH_ALEN);

	sg_set_buf(&sg[0], mac_data,
		   माप(mac_data->entries) + (uc_count * ETH_ALEN));

	/* multicast list and count fill the end */
	mac_data = (व्योम *)&mac_data->macs[uc_count][0];

	mac_data->entries = cpu_to_virtio32(vi->vdev, mc_count);
	i = 0;
	netdev_क्रम_each_mc_addr(ha, dev)
		स_नकल(&mac_data->macs[i++][0], ha->addr, ETH_ALEN);

	sg_set_buf(&sg[1], mac_data,
		   माप(mac_data->entries) + (mc_count * ETH_ALEN));

	अगर (!virtnet_send_command(vi, VIRTIO_NET_CTRL_MAC,
				  VIRTIO_NET_CTRL_MAC_TABLE_SET, sg))
		dev_warn(&dev->dev, "Failed to set MAC filter table.\n");

	kमुक्त(buf);
पूर्ण

अटल पूर्णांक virtnet_vlan_rx_add_vid(काष्ठा net_device *dev,
				   __be16 proto, u16 vid)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	काष्ठा scatterlist sg;

	vi->ctrl->vid = cpu_to_virtio16(vi->vdev, vid);
	sg_init_one(&sg, &vi->ctrl->vid, माप(vi->ctrl->vid));

	अगर (!virtnet_send_command(vi, VIRTIO_NET_CTRL_VLAN,
				  VIRTIO_NET_CTRL_VLAN_ADD, &sg))
		dev_warn(&dev->dev, "Failed to add VLAN ID %d.\n", vid);
	वापस 0;
पूर्ण

अटल पूर्णांक virtnet_vlan_rx_समाप्त_vid(काष्ठा net_device *dev,
				    __be16 proto, u16 vid)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	काष्ठा scatterlist sg;

	vi->ctrl->vid = cpu_to_virtio16(vi->vdev, vid);
	sg_init_one(&sg, &vi->ctrl->vid, माप(vi->ctrl->vid));

	अगर (!virtnet_send_command(vi, VIRTIO_NET_CTRL_VLAN,
				  VIRTIO_NET_CTRL_VLAN_DEL, &sg))
		dev_warn(&dev->dev, "Failed to kill VLAN ID %d.\n", vid);
	वापस 0;
पूर्ण

अटल व्योम virtnet_clean_affinity(काष्ठा virtnet_info *vi)
अणु
	पूर्णांक i;

	अगर (vi->affinity_hपूर्णांक_set) अणु
		क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
			virtqueue_set_affinity(vi->rq[i].vq, शून्य);
			virtqueue_set_affinity(vi->sq[i].vq, शून्य);
		पूर्ण

		vi->affinity_hपूर्णांक_set = false;
	पूर्ण
पूर्ण

अटल व्योम virtnet_set_affinity(काष्ठा virtnet_info *vi)
अणु
	cpumask_var_t mask;
	पूर्णांक stragglers;
	पूर्णांक group_size;
	पूर्णांक i, j, cpu;
	पूर्णांक num_cpu;
	पूर्णांक stride;

	अगर (!zalloc_cpumask_var(&mask, GFP_KERNEL)) अणु
		virtnet_clean_affinity(vi);
		वापस;
	पूर्ण

	num_cpu = num_online_cpus();
	stride = max_t(पूर्णांक, num_cpu / vi->curr_queue_pairs, 1);
	stragglers = num_cpu >= vi->curr_queue_pairs ?
			num_cpu % vi->curr_queue_pairs :
			0;
	cpu = cpumask_next(-1, cpu_online_mask);

	क्रम (i = 0; i < vi->curr_queue_pairs; i++) अणु
		group_size = stride + (i < stragglers ? 1 : 0);

		क्रम (j = 0; j < group_size; j++) अणु
			cpumask_set_cpu(cpu, mask);
			cpu = cpumask_next_wrap(cpu, cpu_online_mask,
						nr_cpu_ids, false);
		पूर्ण
		virtqueue_set_affinity(vi->rq[i].vq, mask);
		virtqueue_set_affinity(vi->sq[i].vq, mask);
		__netअगर_set_xps_queue(vi->dev, cpumask_bits(mask), i, XPS_CPUS);
		cpumask_clear(mask);
	पूर्ण

	vi->affinity_hपूर्णांक_set = true;
	मुक्त_cpumask_var(mask);
पूर्ण

अटल पूर्णांक virtnet_cpu_online(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा virtnet_info *vi = hlist_entry_safe(node, काष्ठा virtnet_info,
						   node);
	virtnet_set_affinity(vi);
	वापस 0;
पूर्ण

अटल पूर्णांक virtnet_cpu_dead(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा virtnet_info *vi = hlist_entry_safe(node, काष्ठा virtnet_info,
						   node_dead);
	virtnet_set_affinity(vi);
	वापस 0;
पूर्ण

अटल पूर्णांक virtnet_cpu_करोwn_prep(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा virtnet_info *vi = hlist_entry_safe(node, काष्ठा virtnet_info,
						   node);

	virtnet_clean_affinity(vi);
	वापस 0;
पूर्ण

अटल क्रमागत cpuhp_state virtionet_online;

अटल पूर्णांक virtnet_cpu_notअगर_add(काष्ठा virtnet_info *vi)
अणु
	पूर्णांक ret;

	ret = cpuhp_state_add_instance_nocalls(virtionet_online, &vi->node);
	अगर (ret)
		वापस ret;
	ret = cpuhp_state_add_instance_nocalls(CPUHP_VIRT_NET_DEAD,
					       &vi->node_dead);
	अगर (!ret)
		वापस ret;
	cpuhp_state_हटाओ_instance_nocalls(virtionet_online, &vi->node);
	वापस ret;
पूर्ण

अटल व्योम virtnet_cpu_notअगर_हटाओ(काष्ठा virtnet_info *vi)
अणु
	cpuhp_state_हटाओ_instance_nocalls(virtionet_online, &vi->node);
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_VIRT_NET_DEAD,
					    &vi->node_dead);
पूर्ण

अटल व्योम virtnet_get_ringparam(काष्ठा net_device *dev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);

	ring->rx_max_pending = virtqueue_get_vring_size(vi->rq[0].vq);
	ring->tx_max_pending = virtqueue_get_vring_size(vi->sq[0].vq);
	ring->rx_pending = ring->rx_max_pending;
	ring->tx_pending = ring->tx_max_pending;
पूर्ण


अटल व्योम virtnet_get_drvinfo(काष्ठा net_device *dev,
				काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	काष्ठा virtio_device *vdev = vi->vdev;

	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	strlcpy(info->version, VIRTNET_DRIVER_VERSION, माप(info->version));
	strlcpy(info->bus_info, virtio_bus_name(vdev), माप(info->bus_info));

पूर्ण

/* TODO: Eliminate OOO packets during चयनing */
अटल पूर्णांक virtnet_set_channels(काष्ठा net_device *dev,
				काष्ठा ethtool_channels *channels)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	u16 queue_pairs = channels->combined_count;
	पूर्णांक err;

	/* We करोn't support separate rx/tx channels.
	 * We करोn't allow setting 'other' channels.
	 */
	अगर (channels->rx_count || channels->tx_count || channels->other_count)
		वापस -EINVAL;

	अगर (queue_pairs > vi->max_queue_pairs || queue_pairs == 0)
		वापस -EINVAL;

	/* For now we करोn't support modअगरying channels जबतक XDP is loaded
	 * also when XDP is loaded all RX queues have XDP programs so we only
	 * need to check a single RX queue.
	 */
	अगर (vi->rq[0].xdp_prog)
		वापस -EINVAL;

	get_online_cpus();
	err = _virtnet_set_queues(vi, queue_pairs);
	अगर (err) अणु
		put_online_cpus();
		जाओ err;
	पूर्ण
	virtnet_set_affinity(vi);
	put_online_cpus();

	netअगर_set_real_num_tx_queues(dev, queue_pairs);
	netअगर_set_real_num_rx_queues(dev, queue_pairs);
 err:
	वापस err;
पूर्ण

अटल व्योम virtnet_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	अचिन्हित पूर्णांक i, j;
	u8 *p = data;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < vi->curr_queue_pairs; i++) अणु
			क्रम (j = 0; j < VIRTNET_RQ_STATS_LEN; j++)
				ethtool_प्र_लिखो(&p, "rx_queue_%u_%s", i,
						virtnet_rq_stats_desc[j].desc);
		पूर्ण

		क्रम (i = 0; i < vi->curr_queue_pairs; i++) अणु
			क्रम (j = 0; j < VIRTNET_SQ_STATS_LEN; j++)
				ethtool_प्र_लिखो(&p, "tx_queue_%u_%s", i,
						virtnet_sq_stats_desc[j].desc);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक virtnet_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस vi->curr_queue_pairs * (VIRTNET_RQ_STATS_LEN +
					       VIRTNET_SQ_STATS_LEN);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम virtnet_get_ethtool_stats(काष्ठा net_device *dev,
				      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	अचिन्हित पूर्णांक idx = 0, start, i, j;
	स्थिर u8 *stats_base;
	माप_प्रकार offset;

	क्रम (i = 0; i < vi->curr_queue_pairs; i++) अणु
		काष्ठा receive_queue *rq = &vi->rq[i];

		stats_base = (u8 *)&rq->stats;
		करो अणु
			start = u64_stats_fetch_begin_irq(&rq->stats.syncp);
			क्रम (j = 0; j < VIRTNET_RQ_STATS_LEN; j++) अणु
				offset = virtnet_rq_stats_desc[j].offset;
				data[idx + j] = *(u64 *)(stats_base + offset);
			पूर्ण
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&rq->stats.syncp, start));
		idx += VIRTNET_RQ_STATS_LEN;
	पूर्ण

	क्रम (i = 0; i < vi->curr_queue_pairs; i++) अणु
		काष्ठा send_queue *sq = &vi->sq[i];

		stats_base = (u8 *)&sq->stats;
		करो अणु
			start = u64_stats_fetch_begin_irq(&sq->stats.syncp);
			क्रम (j = 0; j < VIRTNET_SQ_STATS_LEN; j++) अणु
				offset = virtnet_sq_stats_desc[j].offset;
				data[idx + j] = *(u64 *)(stats_base + offset);
			पूर्ण
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&sq->stats.syncp, start));
		idx += VIRTNET_SQ_STATS_LEN;
	पूर्ण
पूर्ण

अटल व्योम virtnet_get_channels(काष्ठा net_device *dev,
				 काष्ठा ethtool_channels *channels)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);

	channels->combined_count = vi->curr_queue_pairs;
	channels->max_combined = vi->max_queue_pairs;
	channels->max_other = 0;
	channels->rx_count = 0;
	channels->tx_count = 0;
	channels->other_count = 0;
पूर्ण

अटल पूर्णांक virtnet_set_link_ksettings(काष्ठा net_device *dev,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);

	वापस ethtool_virtdev_set_link_ksettings(dev, cmd,
						  &vi->speed, &vi->duplex);
पूर्ण

अटल पूर्णांक virtnet_get_link_ksettings(काष्ठा net_device *dev,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);

	cmd->base.speed = vi->speed;
	cmd->base.duplex = vi->duplex;
	cmd->base.port = PORT_OTHER;

	वापस 0;
पूर्ण

अटल पूर्णांक virtnet_set_coalesce(काष्ठा net_device *dev,
				काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	पूर्णांक i, napi_weight;

	अगर (ec->tx_max_coalesced_frames > 1 ||
	    ec->rx_max_coalesced_frames != 1)
		वापस -EINVAL;

	napi_weight = ec->tx_max_coalesced_frames ? NAPI_POLL_WEIGHT : 0;
	अगर (napi_weight ^ vi->sq[0].napi.weight) अणु
		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;
		क्रम (i = 0; i < vi->max_queue_pairs; i++)
			vi->sq[i].napi.weight = napi_weight;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक virtnet_get_coalesce(काष्ठा net_device *dev,
				काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा ethtool_coalesce ec_शेष = अणु
		.cmd = ETHTOOL_GCOALESCE,
		.rx_max_coalesced_frames = 1,
	पूर्ण;
	काष्ठा virtnet_info *vi = netdev_priv(dev);

	स_नकल(ec, &ec_शेष, माप(ec_शेष));

	अगर (vi->sq[0].napi.weight)
		ec->tx_max_coalesced_frames = 1;

	वापस 0;
पूर्ण

अटल व्योम virtnet_init_settings(काष्ठा net_device *dev)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);

	vi->speed = SPEED_UNKNOWN;
	vi->duplex = DUPLEX_UNKNOWN;
पूर्ण

अटल व्योम virtnet_update_settings(काष्ठा virtnet_info *vi)
अणु
	u32 speed;
	u8 duplex;

	अगर (!virtio_has_feature(vi->vdev, VIRTIO_NET_F_SPEED_DUPLEX))
		वापस;

	virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_net_config, speed, &speed);

	अगर (ethtool_validate_speed(speed))
		vi->speed = speed;

	virtio_cपढ़ो_le(vi->vdev, काष्ठा virtio_net_config, duplex, &duplex);

	अगर (ethtool_validate_duplex(duplex))
		vi->duplex = duplex;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops virtnet_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo = virtnet_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_ringparam = virtnet_get_ringparam,
	.get_strings = virtnet_get_strings,
	.get_sset_count = virtnet_get_sset_count,
	.get_ethtool_stats = virtnet_get_ethtool_stats,
	.set_channels = virtnet_set_channels,
	.get_channels = virtnet_get_channels,
	.get_ts_info = ethtool_op_get_ts_info,
	.get_link_ksettings = virtnet_get_link_ksettings,
	.set_link_ksettings = virtnet_set_link_ksettings,
	.set_coalesce = virtnet_set_coalesce,
	.get_coalesce = virtnet_get_coalesce,
पूर्ण;

अटल व्योम virtnet_मुक्तze_करोwn(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtnet_info *vi = vdev->priv;
	पूर्णांक i;

	/* Make sure no work handler is accessing the device */
	flush_work(&vi->config_work);

	netअगर_tx_lock_bh(vi->dev);
	netअगर_device_detach(vi->dev);
	netअगर_tx_unlock_bh(vi->dev);
	cancel_delayed_work_sync(&vi->refill);

	अगर (netअगर_running(vi->dev)) अणु
		क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
			napi_disable(&vi->rq[i].napi);
			virtnet_napi_tx_disable(&vi->sq[i].napi);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक init_vqs(काष्ठा virtnet_info *vi);

अटल पूर्णांक virtnet_restore_up(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtnet_info *vi = vdev->priv;
	पूर्णांक err, i;

	err = init_vqs(vi);
	अगर (err)
		वापस err;

	virtio_device_पढ़ोy(vdev);

	अगर (netअगर_running(vi->dev)) अणु
		क्रम (i = 0; i < vi->curr_queue_pairs; i++)
			अगर (!try_fill_recv(vi, &vi->rq[i], GFP_KERNEL))
				schedule_delayed_work(&vi->refill, 0);

		क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
			virtnet_napi_enable(vi->rq[i].vq, &vi->rq[i].napi);
			virtnet_napi_tx_enable(vi, vi->sq[i].vq,
					       &vi->sq[i].napi);
		पूर्ण
	पूर्ण

	netअगर_tx_lock_bh(vi->dev);
	netअगर_device_attach(vi->dev);
	netअगर_tx_unlock_bh(vi->dev);
	वापस err;
पूर्ण

अटल पूर्णांक virtnet_set_guest_offloads(काष्ठा virtnet_info *vi, u64 offloads)
अणु
	काष्ठा scatterlist sg;
	vi->ctrl->offloads = cpu_to_virtio64(vi->vdev, offloads);

	sg_init_one(&sg, &vi->ctrl->offloads, माप(vi->ctrl->offloads));

	अगर (!virtnet_send_command(vi, VIRTIO_NET_CTRL_GUEST_OFFLOADS,
				  VIRTIO_NET_CTRL_GUEST_OFFLOADS_SET, &sg)) अणु
		dev_warn(&vi->dev->dev, "Fail to set guest offload.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक virtnet_clear_guest_offloads(काष्ठा virtnet_info *vi)
अणु
	u64 offloads = 0;

	अगर (!vi->guest_offloads)
		वापस 0;

	वापस virtnet_set_guest_offloads(vi, offloads);
पूर्ण

अटल पूर्णांक virtnet_restore_guest_offloads(काष्ठा virtnet_info *vi)
अणु
	u64 offloads = vi->guest_offloads;

	अगर (!vi->guest_offloads)
		वापस 0;

	वापस virtnet_set_guest_offloads(vi, offloads);
पूर्ण

अटल पूर्णांक virtnet_xdp_set(काष्ठा net_device *dev, काष्ठा bpf_prog *prog,
			   काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित दीर्घ पूर्णांक max_sz = PAGE_SIZE - माप(काष्ठा padded_vnet_hdr);
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	काष्ठा bpf_prog *old_prog;
	u16 xdp_qp = 0, curr_qp;
	पूर्णांक i, err;

	अगर (!virtio_has_feature(vi->vdev, VIRTIO_NET_F_CTRL_GUEST_OFFLOADS)
	    && (virtio_has_feature(vi->vdev, VIRTIO_NET_F_GUEST_TSO4) ||
	        virtio_has_feature(vi->vdev, VIRTIO_NET_F_GUEST_TSO6) ||
	        virtio_has_feature(vi->vdev, VIRTIO_NET_F_GUEST_ECN) ||
		virtio_has_feature(vi->vdev, VIRTIO_NET_F_GUEST_UFO) ||
		virtio_has_feature(vi->vdev, VIRTIO_NET_F_GUEST_CSUM))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Can't set XDP while host is implementing LRO/CSUM, disable LRO/CSUM first");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (vi->mergeable_rx_bufs && !vi->any_header_sg) अणु
		NL_SET_ERR_MSG_MOD(extack, "XDP expects header/data in single page, any_header_sg required");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->mtu > max_sz) अणु
		NL_SET_ERR_MSG_MOD(extack, "MTU too large to enable XDP");
		netdev_warn(dev, "XDP requires MTU less than %lu\n", max_sz);
		वापस -EINVAL;
	पूर्ण

	curr_qp = vi->curr_queue_pairs - vi->xdp_queue_pairs;
	अगर (prog)
		xdp_qp = nr_cpu_ids;

	/* XDP requires extra queues क्रम XDP_TX */
	अगर (curr_qp + xdp_qp > vi->max_queue_pairs) अणु
		netdev_warn(dev, "XDP request %i queues but max is %i. XDP_TX and XDP_REDIRECT will operate in a slower locked tx mode.\n",
			    curr_qp + xdp_qp, vi->max_queue_pairs);
		xdp_qp = 0;
	पूर्ण

	old_prog = rtnl_dereference(vi->rq[0].xdp_prog);
	अगर (!prog && !old_prog)
		वापस 0;

	अगर (prog)
		bpf_prog_add(prog, vi->max_queue_pairs - 1);

	/* Make sure NAPI is not using any XDP TX queues क्रम RX. */
	अगर (netअगर_running(dev)) अणु
		क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
			napi_disable(&vi->rq[i].napi);
			virtnet_napi_tx_disable(&vi->sq[i].napi);
		पूर्ण
	पूर्ण

	अगर (!prog) अणु
		क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
			rcu_assign_poपूर्णांकer(vi->rq[i].xdp_prog, prog);
			अगर (i == 0)
				virtnet_restore_guest_offloads(vi);
		पूर्ण
		synchronize_net();
	पूर्ण

	err = _virtnet_set_queues(vi, curr_qp + xdp_qp);
	अगर (err)
		जाओ err;
	netअगर_set_real_num_rx_queues(dev, curr_qp + xdp_qp);
	vi->xdp_queue_pairs = xdp_qp;

	अगर (prog) अणु
		vi->xdp_enabled = true;
		क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
			rcu_assign_poपूर्णांकer(vi->rq[i].xdp_prog, prog);
			अगर (i == 0 && !old_prog)
				virtnet_clear_guest_offloads(vi);
		पूर्ण
	पूर्ण अन्यथा अणु
		vi->xdp_enabled = false;
	पूर्ण

	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		अगर (old_prog)
			bpf_prog_put(old_prog);
		अगर (netअगर_running(dev)) अणु
			virtnet_napi_enable(vi->rq[i].vq, &vi->rq[i].napi);
			virtnet_napi_tx_enable(vi, vi->sq[i].vq,
					       &vi->sq[i].napi);
		पूर्ण
	पूर्ण

	वापस 0;

err:
	अगर (!prog) अणु
		virtnet_clear_guest_offloads(vi);
		क्रम (i = 0; i < vi->max_queue_pairs; i++)
			rcu_assign_poपूर्णांकer(vi->rq[i].xdp_prog, old_prog);
	पूर्ण

	अगर (netअगर_running(dev)) अणु
		क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
			virtnet_napi_enable(vi->rq[i].vq, &vi->rq[i].napi);
			virtnet_napi_tx_enable(vi, vi->sq[i].vq,
					       &vi->sq[i].napi);
		पूर्ण
	पूर्ण
	अगर (prog)
		bpf_prog_sub(prog, vi->max_queue_pairs - 1);
	वापस err;
पूर्ण

अटल पूर्णांक virtnet_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस virtnet_xdp_set(dev, xdp->prog, xdp->extack);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक virtnet_get_phys_port_name(काष्ठा net_device *dev, अक्षर *buf,
				      माप_प्रकार len)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	पूर्णांक ret;

	अगर (!virtio_has_feature(vi->vdev, VIRTIO_NET_F_STANDBY))
		वापस -EOPNOTSUPP;

	ret = snम_लिखो(buf, len, "sby");
	अगर (ret >= len)
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक virtnet_set_features(काष्ठा net_device *dev,
				netdev_features_t features)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(dev);
	u64 offloads;
	पूर्णांक err;

	अगर ((dev->features ^ features) & NETIF_F_LRO) अणु
		अगर (vi->xdp_enabled)
			वापस -EBUSY;

		अगर (features & NETIF_F_LRO)
			offloads = vi->guest_offloads_capable;
		अन्यथा
			offloads = vi->guest_offloads_capable &
				   ~GUEST_OFFLOAD_LRO_MASK;

		err = virtnet_set_guest_offloads(vi, offloads);
		अगर (err)
			वापस err;
		vi->guest_offloads = offloads;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops virtnet_netdev = अणु
	.nकरो_खोलो            = virtnet_खोलो,
	.nकरो_stop   	     = virtnet_बंद,
	.nकरो_start_xmit      = start_xmit,
	.nकरो_validate_addr   = eth_validate_addr,
	.nकरो_set_mac_address = virtnet_set_mac_address,
	.nकरो_set_rx_mode     = virtnet_set_rx_mode,
	.nकरो_get_stats64     = virtnet_stats,
	.nकरो_vlan_rx_add_vid = virtnet_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid = virtnet_vlan_rx_समाप्त_vid,
	.nकरो_bpf		= virtnet_xdp,
	.nकरो_xdp_xmit		= virtnet_xdp_xmit,
	.nकरो_features_check	= passthru_features_check,
	.nकरो_get_phys_port_name	= virtnet_get_phys_port_name,
	.nकरो_set_features	= virtnet_set_features,
पूर्ण;

अटल व्योम virtnet_config_changed_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtnet_info *vi =
		container_of(work, काष्ठा virtnet_info, config_work);
	u16 v;

	अगर (virtio_cपढ़ो_feature(vi->vdev, VIRTIO_NET_F_STATUS,
				 काष्ठा virtio_net_config, status, &v) < 0)
		वापस;

	अगर (v & VIRTIO_NET_S_ANNOUNCE) अणु
		netdev_notअगरy_peers(vi->dev);
		virtnet_ack_link_announce(vi);
	पूर्ण

	/* Ignore unknown (future) status bits */
	v &= VIRTIO_NET_S_LINK_UP;

	अगर (vi->status == v)
		वापस;

	vi->status = v;

	अगर (vi->status & VIRTIO_NET_S_LINK_UP) अणु
		virtnet_update_settings(vi);
		netअगर_carrier_on(vi->dev);
		netअगर_tx_wake_all_queues(vi->dev);
	पूर्ण अन्यथा अणु
		netअगर_carrier_off(vi->dev);
		netअगर_tx_stop_all_queues(vi->dev);
	पूर्ण
पूर्ण

अटल व्योम virtnet_config_changed(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtnet_info *vi = vdev->priv;

	schedule_work(&vi->config_work);
पूर्ण

अटल व्योम virtnet_मुक्त_queues(काष्ठा virtnet_info *vi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		__netअगर_napi_del(&vi->rq[i].napi);
		__netअगर_napi_del(&vi->sq[i].napi);
	पूर्ण

	/* We called __netअगर_napi_del(),
	 * we need to respect an RCU grace period beक्रमe मुक्तing vi->rq
	 */
	synchronize_net();

	kमुक्त(vi->rq);
	kमुक्त(vi->sq);
	kमुक्त(vi->ctrl);
पूर्ण

अटल व्योम _मुक्त_receive_bufs(काष्ठा virtnet_info *vi)
अणु
	काष्ठा bpf_prog *old_prog;
	पूर्णांक i;

	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		जबतक (vi->rq[i].pages)
			__मुक्त_pages(get_a_page(&vi->rq[i], GFP_KERNEL), 0);

		old_prog = rtnl_dereference(vi->rq[i].xdp_prog);
		RCU_INIT_POINTER(vi->rq[i].xdp_prog, शून्य);
		अगर (old_prog)
			bpf_prog_put(old_prog);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_receive_bufs(काष्ठा virtnet_info *vi)
अणु
	rtnl_lock();
	_मुक्त_receive_bufs(vi);
	rtnl_unlock();
पूर्ण

अटल व्योम मुक्त_receive_page_frags(काष्ठा virtnet_info *vi)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < vi->max_queue_pairs; i++)
		अगर (vi->rq[i].alloc_frag.page)
			put_page(vi->rq[i].alloc_frag.page);
पूर्ण

अटल व्योम मुक्त_unused_bufs(काष्ठा virtnet_info *vi)
अणु
	व्योम *buf;
	पूर्णांक i;

	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		काष्ठा virtqueue *vq = vi->sq[i].vq;
		जबतक ((buf = virtqueue_detach_unused_buf(vq)) != शून्य) अणु
			अगर (!is_xdp_frame(buf))
				dev_kमुक्त_skb(buf);
			अन्यथा
				xdp_वापस_frame(ptr_to_xdp(buf));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		काष्ठा virtqueue *vq = vi->rq[i].vq;

		जबतक ((buf = virtqueue_detach_unused_buf(vq)) != शून्य) अणु
			अगर (vi->mergeable_rx_bufs) अणु
				put_page(virt_to_head_page(buf));
			पूर्ण अन्यथा अगर (vi->big_packets) अणु
				give_pages(&vi->rq[i], buf);
			पूर्ण अन्यथा अणु
				put_page(virt_to_head_page(buf));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम virtnet_del_vqs(काष्ठा virtnet_info *vi)
अणु
	काष्ठा virtio_device *vdev = vi->vdev;

	virtnet_clean_affinity(vi);

	vdev->config->del_vqs(vdev);

	virtnet_मुक्त_queues(vi);
पूर्ण

/* How large should a single buffer be so a queue full of these can fit at
 * least one full packet?
 * Logic below assumes the mergeable buffer header is used.
 */
अटल अचिन्हित पूर्णांक mergeable_min_buf_len(काष्ठा virtnet_info *vi, काष्ठा virtqueue *vq)
अणु
	स्थिर अचिन्हित पूर्णांक hdr_len = माप(काष्ठा virtio_net_hdr_mrg_rxbuf);
	अचिन्हित पूर्णांक rq_size = virtqueue_get_vring_size(vq);
	अचिन्हित पूर्णांक packet_len = vi->big_packets ? IP_MAX_MTU : vi->dev->max_mtu;
	अचिन्हित पूर्णांक buf_len = hdr_len + ETH_HLEN + VLAN_HLEN + packet_len;
	अचिन्हित पूर्णांक min_buf_len = DIV_ROUND_UP(buf_len, rq_size);

	वापस max(max(min_buf_len, hdr_len) - hdr_len,
		   (अचिन्हित पूर्णांक)GOOD_PACKET_LEN);
पूर्ण

अटल पूर्णांक virtnet_find_vqs(काष्ठा virtnet_info *vi)
अणु
	vq_callback_t **callbacks;
	काष्ठा virtqueue **vqs;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i, total_vqs;
	स्थिर अक्षर **names;
	bool *ctx;

	/* We expect 1 RX virtqueue followed by 1 TX virtqueue, followed by
	 * possible N-1 RX/TX queue pairs used in multiqueue mode, followed by
	 * possible control vq.
	 */
	total_vqs = vi->max_queue_pairs * 2 +
		    virtio_has_feature(vi->vdev, VIRTIO_NET_F_CTRL_VQ);

	/* Allocate space क्रम find_vqs parameters */
	vqs = kसुस्मृति(total_vqs, माप(*vqs), GFP_KERNEL);
	अगर (!vqs)
		जाओ err_vq;
	callbacks = kदो_स्मृति_array(total_vqs, माप(*callbacks), GFP_KERNEL);
	अगर (!callbacks)
		जाओ err_callback;
	names = kदो_स्मृति_array(total_vqs, माप(*names), GFP_KERNEL);
	अगर (!names)
		जाओ err_names;
	अगर (!vi->big_packets || vi->mergeable_rx_bufs) अणु
		ctx = kसुस्मृति(total_vqs, माप(*ctx), GFP_KERNEL);
		अगर (!ctx)
			जाओ err_ctx;
	पूर्ण अन्यथा अणु
		ctx = शून्य;
	पूर्ण

	/* Parameters क्रम control virtqueue, अगर any */
	अगर (vi->has_cvq) अणु
		callbacks[total_vqs - 1] = शून्य;
		names[total_vqs - 1] = "control";
	पूर्ण

	/* Allocate/initialize parameters क्रम send/receive virtqueues */
	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		callbacks[rxq2vq(i)] = skb_recv_करोne;
		callbacks[txq2vq(i)] = skb_xmit_करोne;
		प्र_लिखो(vi->rq[i].name, "input.%d", i);
		प्र_लिखो(vi->sq[i].name, "output.%d", i);
		names[rxq2vq(i)] = vi->rq[i].name;
		names[txq2vq(i)] = vi->sq[i].name;
		अगर (ctx)
			ctx[rxq2vq(i)] = true;
	पूर्ण

	ret = vi->vdev->config->find_vqs(vi->vdev, total_vqs, vqs, callbacks,
					 names, ctx, शून्य);
	अगर (ret)
		जाओ err_find;

	अगर (vi->has_cvq) अणु
		vi->cvq = vqs[total_vqs - 1];
		अगर (virtio_has_feature(vi->vdev, VIRTIO_NET_F_CTRL_VLAN))
			vi->dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	पूर्ण

	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		vi->rq[i].vq = vqs[rxq2vq(i)];
		vi->rq[i].min_buf_len = mergeable_min_buf_len(vi, vi->rq[i].vq);
		vi->sq[i].vq = vqs[txq2vq(i)];
	पूर्ण

	/* run here: ret == 0. */


err_find:
	kमुक्त(ctx);
err_ctx:
	kमुक्त(names);
err_names:
	kमुक्त(callbacks);
err_callback:
	kमुक्त(vqs);
err_vq:
	वापस ret;
पूर्ण

अटल पूर्णांक virtnet_alloc_queues(काष्ठा virtnet_info *vi)
अणु
	पूर्णांक i;

	अगर (vi->has_cvq) अणु
		vi->ctrl = kzalloc(माप(*vi->ctrl), GFP_KERNEL);
		अगर (!vi->ctrl)
			जाओ err_ctrl;
	पूर्ण अन्यथा अणु
		vi->ctrl = शून्य;
	पूर्ण
	vi->sq = kसुस्मृति(vi->max_queue_pairs, माप(*vi->sq), GFP_KERNEL);
	अगर (!vi->sq)
		जाओ err_sq;
	vi->rq = kसुस्मृति(vi->max_queue_pairs, माप(*vi->rq), GFP_KERNEL);
	अगर (!vi->rq)
		जाओ err_rq;

	INIT_DELAYED_WORK(&vi->refill, refill_work);
	क्रम (i = 0; i < vi->max_queue_pairs; i++) अणु
		vi->rq[i].pages = शून्य;
		netअगर_napi_add(vi->dev, &vi->rq[i].napi, virtnet_poll,
			       napi_weight);
		netअगर_tx_napi_add(vi->dev, &vi->sq[i].napi, virtnet_poll_tx,
				  napi_tx ? napi_weight : 0);

		sg_init_table(vi->rq[i].sg, ARRAY_SIZE(vi->rq[i].sg));
		ewma_pkt_len_init(&vi->rq[i].mrg_avg_pkt_len);
		sg_init_table(vi->sq[i].sg, ARRAY_SIZE(vi->sq[i].sg));

		u64_stats_init(&vi->rq[i].stats.syncp);
		u64_stats_init(&vi->sq[i].stats.syncp);
	पूर्ण

	वापस 0;

err_rq:
	kमुक्त(vi->sq);
err_sq:
	kमुक्त(vi->ctrl);
err_ctrl:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक init_vqs(काष्ठा virtnet_info *vi)
अणु
	पूर्णांक ret;

	/* Allocate send & receive queues */
	ret = virtnet_alloc_queues(vi);
	अगर (ret)
		जाओ err;

	ret = virtnet_find_vqs(vi);
	अगर (ret)
		जाओ err_मुक्त;

	get_online_cpus();
	virtnet_set_affinity(vi);
	put_online_cpus();

	वापस 0;

err_मुक्त:
	virtnet_मुक्त_queues(vi);
err:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SYSFS
अटल sमाप_प्रकार mergeable_rx_buffer_size_show(काष्ठा netdev_rx_queue *queue,
		अक्षर *buf)
अणु
	काष्ठा virtnet_info *vi = netdev_priv(queue->dev);
	अचिन्हित पूर्णांक queue_index = get_netdev_rx_queue_index(queue);
	अचिन्हित पूर्णांक headroom = virtnet_get_headroom(vi);
	अचिन्हित पूर्णांक tailroom = headroom ? माप(काष्ठा skb_shared_info) : 0;
	काष्ठा ewma_pkt_len *avg;

	BUG_ON(queue_index >= vi->max_queue_pairs);
	avg = &vi->rq[queue_index].mrg_avg_pkt_len;
	वापस प्र_लिखो(buf, "%u\n",
		       get_mergeable_buf_len(&vi->rq[queue_index], avg,
				       SKB_DATA_ALIGN(headroom + tailroom)));
पूर्ण

अटल काष्ठा rx_queue_attribute mergeable_rx_buffer_size_attribute =
	__ATTR_RO(mergeable_rx_buffer_size);

अटल काष्ठा attribute *virtio_net_mrg_rx_attrs[] = अणु
	&mergeable_rx_buffer_size_attribute.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group virtio_net_mrg_rx_group = अणु
	.name = "virtio_net",
	.attrs = virtio_net_mrg_rx_attrs
पूर्ण;
#पूर्ण_अगर

अटल bool virtnet_fail_on_feature(काष्ठा virtio_device *vdev,
				    अचिन्हित पूर्णांक fbit,
				    स्थिर अक्षर *fname, स्थिर अक्षर *dname)
अणु
	अगर (!virtio_has_feature(vdev, fbit))
		वापस false;

	dev_err(&vdev->dev, "device advertises feature %s but not %s",
		fname, dname);

	वापस true;
पूर्ण

#घोषणा VIRTNET_FAIL_ON(vdev, fbit, dbit)			\
	virtnet_fail_on_feature(vdev, fbit, #fbit, dbit)

अटल bool virtnet_validate_features(काष्ठा virtio_device *vdev)
अणु
	अगर (!virtio_has_feature(vdev, VIRTIO_NET_F_CTRL_VQ) &&
	    (VIRTNET_FAIL_ON(vdev, VIRTIO_NET_F_CTRL_RX,
			     "VIRTIO_NET_F_CTRL_VQ") ||
	     VIRTNET_FAIL_ON(vdev, VIRTIO_NET_F_CTRL_VLAN,
			     "VIRTIO_NET_F_CTRL_VQ") ||
	     VIRTNET_FAIL_ON(vdev, VIRTIO_NET_F_GUEST_ANNOUNCE,
			     "VIRTIO_NET_F_CTRL_VQ") ||
	     VIRTNET_FAIL_ON(vdev, VIRTIO_NET_F_MQ, "VIRTIO_NET_F_CTRL_VQ") ||
	     VIRTNET_FAIL_ON(vdev, VIRTIO_NET_F_CTRL_MAC_ADDR,
			     "VIRTIO_NET_F_CTRL_VQ"))) अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

#घोषणा MIN_MTU ETH_MIN_MTU
#घोषणा MAX_MTU ETH_MAX_MTU

अटल पूर्णांक virtnet_validate(काष्ठा virtio_device *vdev)
अणु
	अगर (!vdev->config->get) अणु
		dev_err(&vdev->dev, "%s failure: config access disabled\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!virtnet_validate_features(vdev))
		वापस -EINVAL;

	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_MTU)) अणु
		पूर्णांक mtu = virtio_cपढ़ो16(vdev,
					 दुरत्व(काष्ठा virtio_net_config,
						  mtu));
		अगर (mtu < MIN_MTU)
			__virtio_clear_bit(vdev, VIRTIO_NET_F_MTU);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक virtnet_probe(काष्ठा virtio_device *vdev)
अणु
	पूर्णांक i, err = -ENOMEM;
	काष्ठा net_device *dev;
	काष्ठा virtnet_info *vi;
	u16 max_queue_pairs;
	पूर्णांक mtu;

	/* Find अगर host supports multiqueue virtio_net device */
	err = virtio_cपढ़ो_feature(vdev, VIRTIO_NET_F_MQ,
				   काष्ठा virtio_net_config,
				   max_virtqueue_pairs, &max_queue_pairs);

	/* We need at least 2 queue's */
	अगर (err || max_queue_pairs < VIRTIO_NET_CTRL_MQ_VQ_PAIRS_MIN ||
	    max_queue_pairs > VIRTIO_NET_CTRL_MQ_VQ_PAIRS_MAX ||
	    !virtio_has_feature(vdev, VIRTIO_NET_F_CTRL_VQ))
		max_queue_pairs = 1;

	/* Allocate ourselves a network device with room क्रम our info */
	dev = alloc_etherdev_mq(माप(काष्ठा virtnet_info), max_queue_pairs);
	अगर (!dev)
		वापस -ENOMEM;

	/* Set up network device as normal. */
	dev->priv_flags |= IFF_UNICAST_FLT | IFF_LIVE_ADDR_CHANGE |
			   IFF_TX_SKB_NO_LINEAR;
	dev->netdev_ops = &virtnet_netdev;
	dev->features = NETIF_F_HIGHDMA;

	dev->ethtool_ops = &virtnet_ethtool_ops;
	SET_NETDEV_DEV(dev, &vdev->dev);

	/* Do we support "hardware" checksums? */
	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_CSUM)) अणु
		/* This खोलोs up the world of extra features. */
		dev->hw_features |= NETIF_F_HW_CSUM | NETIF_F_SG;
		अगर (csum)
			dev->features |= NETIF_F_HW_CSUM | NETIF_F_SG;

		अगर (virtio_has_feature(vdev, VIRTIO_NET_F_GSO)) अणु
			dev->hw_features |= NETIF_F_TSO
				| NETIF_F_TSO_ECN | NETIF_F_TSO6;
		पूर्ण
		/* Inभागidual feature bits: what can host handle? */
		अगर (virtio_has_feature(vdev, VIRTIO_NET_F_HOST_TSO4))
			dev->hw_features |= NETIF_F_TSO;
		अगर (virtio_has_feature(vdev, VIRTIO_NET_F_HOST_TSO6))
			dev->hw_features |= NETIF_F_TSO6;
		अगर (virtio_has_feature(vdev, VIRTIO_NET_F_HOST_ECN))
			dev->hw_features |= NETIF_F_TSO_ECN;

		dev->features |= NETIF_F_GSO_ROBUST;

		अगर (gso)
			dev->features |= dev->hw_features & NETIF_F_ALL_TSO;
		/* (!csum && gso) हाल will be fixed by रेजिस्टर_netdev() */
	पूर्ण
	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_GUEST_CSUM))
		dev->features |= NETIF_F_RXCSUM;
	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_GUEST_TSO4) ||
	    virtio_has_feature(vdev, VIRTIO_NET_F_GUEST_TSO6))
		dev->features |= NETIF_F_LRO;
	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_CTRL_GUEST_OFFLOADS))
		dev->hw_features |= NETIF_F_LRO;

	dev->vlan_features = dev->features;

	/* MTU range: 68 - 65535 */
	dev->min_mtu = MIN_MTU;
	dev->max_mtu = MAX_MTU;

	/* Configuration may specअगरy what MAC to use.  Otherwise अक्रमom. */
	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_MAC))
		virtio_cपढ़ो_bytes(vdev,
				   दुरत्व(काष्ठा virtio_net_config, mac),
				   dev->dev_addr, dev->addr_len);
	अन्यथा
		eth_hw_addr_अक्रमom(dev);

	/* Set up our device-specअगरic inक्रमmation */
	vi = netdev_priv(dev);
	vi->dev = dev;
	vi->vdev = vdev;
	vdev->priv = vi;

	INIT_WORK(&vi->config_work, virtnet_config_changed_work);

	/* If we can receive ANY GSO packets, we must allocate large ones. */
	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_GUEST_TSO4) ||
	    virtio_has_feature(vdev, VIRTIO_NET_F_GUEST_TSO6) ||
	    virtio_has_feature(vdev, VIRTIO_NET_F_GUEST_ECN) ||
	    virtio_has_feature(vdev, VIRTIO_NET_F_GUEST_UFO))
		vi->big_packets = true;

	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_MRG_RXBUF))
		vi->mergeable_rx_bufs = true;

	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_MRG_RXBUF) ||
	    virtio_has_feature(vdev, VIRTIO_F_VERSION_1))
		vi->hdr_len = माप(काष्ठा virtio_net_hdr_mrg_rxbuf);
	अन्यथा
		vi->hdr_len = माप(काष्ठा virtio_net_hdr);

	अगर (virtio_has_feature(vdev, VIRTIO_F_ANY_LAYOUT) ||
	    virtio_has_feature(vdev, VIRTIO_F_VERSION_1))
		vi->any_header_sg = true;

	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_CTRL_VQ))
		vi->has_cvq = true;

	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_MTU)) अणु
		mtu = virtio_cपढ़ो16(vdev,
				     दुरत्व(काष्ठा virtio_net_config,
					      mtu));
		अगर (mtu < dev->min_mtu) अणु
			/* Should never trigger: MTU was previously validated
			 * in virtnet_validate.
			 */
			dev_err(&vdev->dev,
				"device MTU appears to have changed it is now %d < %d",
				mtu, dev->min_mtu);
			err = -EINVAL;
			जाओ मुक्त;
		पूर्ण

		dev->mtu = mtu;
		dev->max_mtu = mtu;

		/* TODO: size buffers correctly in this हाल. */
		अगर (dev->mtu > ETH_DATA_LEN)
			vi->big_packets = true;
	पूर्ण

	अगर (vi->any_header_sg)
		dev->needed_headroom = vi->hdr_len;

	/* Enable multiqueue by शेष */
	अगर (num_online_cpus() >= max_queue_pairs)
		vi->curr_queue_pairs = max_queue_pairs;
	अन्यथा
		vi->curr_queue_pairs = num_online_cpus();
	vi->max_queue_pairs = max_queue_pairs;

	/* Allocate/initialize the rx/tx queues, and invoke find_vqs */
	err = init_vqs(vi);
	अगर (err)
		जाओ मुक्त;

#अगर_घोषित CONFIG_SYSFS
	अगर (vi->mergeable_rx_bufs)
		dev->sysfs_rx_queue_group = &virtio_net_mrg_rx_group;
#पूर्ण_अगर
	netअगर_set_real_num_tx_queues(dev, vi->curr_queue_pairs);
	netअगर_set_real_num_rx_queues(dev, vi->curr_queue_pairs);

	virtnet_init_settings(dev);

	अगर (virtio_has_feature(vdev, VIRTIO_NET_F_STANDBY)) अणु
		vi->failover = net_failover_create(vi->dev);
		अगर (IS_ERR(vi->failover)) अणु
			err = PTR_ERR(vi->failover);
			जाओ मुक्त_vqs;
		पूर्ण
	पूर्ण

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		pr_debug("virtio_net: registering device failed\n");
		जाओ मुक्त_failover;
	पूर्ण

	virtio_device_पढ़ोy(vdev);

	err = virtnet_cpu_notअगर_add(vi);
	अगर (err) अणु
		pr_debug("virtio_net: registering cpu notifier failed\n");
		जाओ मुक्त_unरेजिस्टर_netdev;
	पूर्ण

	virtnet_set_queues(vi, vi->curr_queue_pairs);

	/* Assume link up अगर device can't report link status,
	   otherwise get link status from config. */
	netअगर_carrier_off(dev);
	अगर (virtio_has_feature(vi->vdev, VIRTIO_NET_F_STATUS)) अणु
		schedule_work(&vi->config_work);
	पूर्ण अन्यथा अणु
		vi->status = VIRTIO_NET_S_LINK_UP;
		virtnet_update_settings(vi);
		netअगर_carrier_on(dev);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(guest_offloads); i++)
		अगर (virtio_has_feature(vi->vdev, guest_offloads[i]))
			set_bit(guest_offloads[i], &vi->guest_offloads);
	vi->guest_offloads_capable = vi->guest_offloads;

	pr_debug("virtnet: registered device %s with %d RX and TX vq's\n",
		 dev->name, max_queue_pairs);

	वापस 0;

मुक्त_unरेजिस्टर_netdev:
	vi->vdev->config->reset(vdev);

	unरेजिस्टर_netdev(dev);
मुक्त_failover:
	net_failover_destroy(vi->failover);
मुक्त_vqs:
	cancel_delayed_work_sync(&vi->refill);
	मुक्त_receive_page_frags(vi);
	virtnet_del_vqs(vi);
मुक्त:
	मुक्त_netdev(dev);
	वापस err;
पूर्ण

अटल व्योम हटाओ_vq_common(काष्ठा virtnet_info *vi)
अणु
	vi->vdev->config->reset(vi->vdev);

	/* Free unused buffers in both send and recv, अगर any. */
	मुक्त_unused_bufs(vi);

	मुक्त_receive_bufs(vi);

	मुक्त_receive_page_frags(vi);

	virtnet_del_vqs(vi);
पूर्ण

अटल व्योम virtnet_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtnet_info *vi = vdev->priv;

	virtnet_cpu_notअगर_हटाओ(vi);

	/* Make sure no work handler is accessing the device. */
	flush_work(&vi->config_work);

	unरेजिस्टर_netdev(vi->dev);

	net_failover_destroy(vi->failover);

	हटाओ_vq_common(vi);

	मुक्त_netdev(vi->dev);
पूर्ण

अटल __maybe_unused पूर्णांक virtnet_मुक्तze(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtnet_info *vi = vdev->priv;

	virtnet_cpu_notअगर_हटाओ(vi);
	virtnet_मुक्तze_करोwn(vdev);
	हटाओ_vq_common(vi);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक virtnet_restore(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtnet_info *vi = vdev->priv;
	पूर्णांक err;

	err = virtnet_restore_up(vdev);
	अगर (err)
		वापस err;
	virtnet_set_queues(vi, vi->curr_queue_pairs);

	err = virtnet_cpu_notअगर_add(vi);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_NET, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

#घोषणा VIRTNET_FEATURES \
	VIRTIO_NET_F_CSUM, VIRTIO_NET_F_GUEST_CSUM, \
	VIRTIO_NET_F_MAC, \
	VIRTIO_NET_F_HOST_TSO4, VIRTIO_NET_F_HOST_UFO, VIRTIO_NET_F_HOST_TSO6, \
	VIRTIO_NET_F_HOST_ECN, VIRTIO_NET_F_GUEST_TSO4, VIRTIO_NET_F_GUEST_TSO6, \
	VIRTIO_NET_F_GUEST_ECN, VIRTIO_NET_F_GUEST_UFO, \
	VIRTIO_NET_F_MRG_RXBUF, VIRTIO_NET_F_STATUS, VIRTIO_NET_F_CTRL_VQ, \
	VIRTIO_NET_F_CTRL_RX, VIRTIO_NET_F_CTRL_VLAN, \
	VIRTIO_NET_F_GUEST_ANNOUNCE, VIRTIO_NET_F_MQ, \
	VIRTIO_NET_F_CTRL_MAC_ADDR, \
	VIRTIO_NET_F_MTU, VIRTIO_NET_F_CTRL_GUEST_OFFLOADS, \
	VIRTIO_NET_F_SPEED_DUPLEX, VIRTIO_NET_F_STANDBY

अटल अचिन्हित पूर्णांक features[] = अणु
	VIRTNET_FEATURES,
पूर्ण;

अटल अचिन्हित पूर्णांक features_legacy[] = अणु
	VIRTNET_FEATURES,
	VIRTIO_NET_F_GSO,
	VIRTIO_F_ANY_LAYOUT,
पूर्ण;

अटल काष्ठा virtio_driver virtio_net_driver = अणु
	.feature_table = features,
	.feature_table_size = ARRAY_SIZE(features),
	.feature_table_legacy = features_legacy,
	.feature_table_size_legacy = ARRAY_SIZE(features_legacy),
	.driver.name =	KBUILD_MODNAME,
	.driver.owner =	THIS_MODULE,
	.id_table =	id_table,
	.validate =	virtnet_validate,
	.probe =	virtnet_probe,
	.हटाओ =	virtnet_हटाओ,
	.config_changed = virtnet_config_changed,
#अगर_घोषित CONFIG_PM_SLEEP
	.मुक्तze =	virtnet_मुक्तze,
	.restore =	virtnet_restore,
#पूर्ण_अगर
पूर्ण;

अटल __init पूर्णांक virtio_net_driver_init(व्योम)
अणु
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN, "virtio/net:online",
				      virtnet_cpu_online,
				      virtnet_cpu_करोwn_prep);
	अगर (ret < 0)
		जाओ out;
	virtionet_online = ret;
	ret = cpuhp_setup_state_multi(CPUHP_VIRT_NET_DEAD, "virtio/net:dead",
				      शून्य, virtnet_cpu_dead);
	अगर (ret)
		जाओ err_dead;

        ret = रेजिस्टर_virtio_driver(&virtio_net_driver);
	अगर (ret)
		जाओ err_virtio;
	वापस 0;
err_virtio:
	cpuhp_हटाओ_multi_state(CPUHP_VIRT_NET_DEAD);
err_dead:
	cpuhp_हटाओ_multi_state(virtionet_online);
out:
	वापस ret;
पूर्ण
module_init(virtio_net_driver_init);

अटल __निकास व्योम virtio_net_driver_निकास(व्योम)
अणु
	unरेजिस्टर_virtio_driver(&virtio_net_driver);
	cpuhp_हटाओ_multi_state(CPUHP_VIRT_NET_DEAD);
	cpuhp_हटाओ_multi_state(virtionet_online);
पूर्ण
module_निकास(virtio_net_driver_निकास);

MODULE_DEVICE_TABLE(virtio, id_table);
MODULE_DESCRIPTION("Virtio network driver");
MODULE_LICENSE("GPL");
