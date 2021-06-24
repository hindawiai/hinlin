<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2013
 * Authors: Vicram Arv
 *	    Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 *	    Sjur Brendeland
 */
#समावेश <linux/module.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/vringh.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_caअगर.h>
#समावेश <linux/virtio_ring.h>
#समावेश <linux/dma-mapping.h>
#समावेश <net/caअगर/caअगर_dev.h>
#समावेश <linux/virtio_config.h>

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Vicram Arv");
MODULE_AUTHOR("Sjur Brendeland");
MODULE_DESCRIPTION("Virtio CAIF Driver");

/* NAPI schedule quota */
#घोषणा CFV_DEFAULT_QUOTA 32

/* Defaults used अगर virtio config space is unavailable */
#घोषणा CFV_DEF_MTU_SIZE 4096
#घोषणा CFV_DEF_HEADROOM 32
#घोषणा CFV_DEF_TAILROOM 32

/* Required IP header alignment */
#घोषणा IP_HDR_ALIGN 4

/* काष्ठा cfv_napi_contxt - NAPI context info
 * @riov: IOV holding data पढ़ो from the ring. Note that riov may
 *	  still hold data when cfv_rx_poll() वापसs.
 * @head: Last descriptor ID we received from vringh_getdesc_kern.
 *	  We use this to put descriptor back on the used ring. अच_लघु_उच्च is
 *	  used to indicate invalid head-id.
 */
काष्ठा cfv_napi_context अणु
	काष्ठा vringh_kiov riov;
	अचिन्हित लघु head;
पूर्ण;

/* काष्ठा cfv_stats - statistics क्रम debugfs
 * @rx_napi_complete:	Number of NAPI completions (RX)
 * @rx_napi_resched:	Number of calls where the full quota was used (RX)
 * @rx_nomem:		Number of SKB alloc failures (RX)
 * @rx_kicks:		Number of RX kicks
 * @tx_full_ring:	Number बार TX ring was full
 * @tx_no_mem:		Number of बार TX went out of memory
 * @tx_flow_on:		Number of flow on (TX)
 * @tx_kicks:		Number of TX kicks
 */
काष्ठा cfv_stats अणु
	u32 rx_napi_complete;
	u32 rx_napi_resched;
	u32 rx_nomem;
	u32 rx_kicks;
	u32 tx_full_ring;
	u32 tx_no_mem;
	u32 tx_flow_on;
	u32 tx_kicks;
पूर्ण;

/* काष्ठा cfv_info - Caअगर Virtio control काष्ठाure
 * @cfdev:	caअगर common header
 * @vdev:	Associated virtio device
 * @vr_rx:	rx/करोwnlink host vring
 * @vq_tx:	tx/uplink virtqueue
 * @ndev:	CAIF link layer device
 * @watermark_tx: indicates number of मुक्त descriptors we need
 *		to reखोलो the tx-queues after overload.
 * @tx_lock:	protects vq_tx from concurrent use
 * @tx_release_tasklet: Tasklet क्रम मुक्तing consumed TX buffers
 * @napi:       Napi context used in cfv_rx_poll()
 * @ctx:        Context data used in cfv_rx_poll()
 * @tx_hr:	transmit headroom
 * @rx_hr:	receive headroom
 * @tx_tr:	transmit tail room
 * @rx_tr:	receive tail room
 * @mtu:	transmit max size
 * @mru:	receive max size
 * @allocsz:    size of dma memory reserved क्रम TX buffers
 * @alloc_addr: भव address to dma memory क्रम TX buffers
 * @alloc_dma:  dma address to dma memory क्रम TX buffers
 * @genpool:    Gen Pool used क्रम allocating TX buffers
 * @reserved_mem: Poपूर्णांकer to memory reserve allocated from genpool
 * @reserved_size: Size of memory reserve allocated from genpool
 * @stats:       Statistics exposed in sysfs
 * @debugfs:    Debugfs dentry क्रम statistic counters
 */
काष्ठा cfv_info अणु
	काष्ठा caअगर_dev_common cfdev;
	काष्ठा virtio_device *vdev;
	काष्ठा vringh *vr_rx;
	काष्ठा virtqueue *vq_tx;
	काष्ठा net_device *ndev;
	अचिन्हित पूर्णांक watermark_tx;
	/* Protect access to vq_tx */
	spinlock_t tx_lock;
	काष्ठा tasklet_काष्ठा tx_release_tasklet;
	काष्ठा napi_काष्ठा napi;
	काष्ठा cfv_napi_context ctx;
	u16 tx_hr;
	u16 rx_hr;
	u16 tx_tr;
	u16 rx_tr;
	u32 mtu;
	u32 mru;
	माप_प्रकार allocsz;
	व्योम *alloc_addr;
	dma_addr_t alloc_dma;
	काष्ठा gen_pool *genpool;
	अचिन्हित दीर्घ reserved_mem;
	माप_प्रकार reserved_size;
	काष्ठा cfv_stats stats;
	काष्ठा dentry *debugfs;
पूर्ण;

/* काष्ठा buf_info - मुख्यtains transmit buffer data handle
 * @size:	size of transmit buffer
 * @dma_handle: handle to allocated dma device memory area
 * @vaddr:	भव address mapping to allocated memory area
 */
काष्ठा buf_info अणु
	माप_प्रकार size;
	u8 *vaddr;
पूर्ण;

/* Called from virtio device, in IRQ context */
अटल व्योम cfv_release_cb(काष्ठा virtqueue *vq_tx)
अणु
	काष्ठा cfv_info *cfv = vq_tx->vdev->priv;

	++cfv->stats.tx_kicks;
	tasklet_schedule(&cfv->tx_release_tasklet);
पूर्ण

अटल व्योम मुक्त_buf_info(काष्ठा cfv_info *cfv, काष्ठा buf_info *buf_info)
अणु
	अगर (!buf_info)
		वापस;
	gen_pool_मुक्त(cfv->genpool, (अचिन्हित दीर्घ) buf_info->vaddr,
		      buf_info->size);
	kमुक्त(buf_info);
पूर्ण

/* This is invoked whenever the remote processor completed processing
 * a TX msg we just sent, and the buffer is put back to the used ring.
 */
अटल व्योम cfv_release_used_buf(काष्ठा virtqueue *vq_tx)
अणु
	काष्ठा cfv_info *cfv = vq_tx->vdev->priv;
	अचिन्हित दीर्घ flags;

	BUG_ON(vq_tx != cfv->vq_tx);

	क्रम (;;) अणु
		अचिन्हित पूर्णांक len;
		काष्ठा buf_info *buf_info;

		/* Get used buffer from used ring to recycle used descriptors */
		spin_lock_irqsave(&cfv->tx_lock, flags);
		buf_info = virtqueue_get_buf(vq_tx, &len);
		spin_unlock_irqrestore(&cfv->tx_lock, flags);

		/* Stop looping अगर there are no more buffers to मुक्त */
		अगर (!buf_info)
			अवरोध;

		मुक्त_buf_info(cfv, buf_info);

		/* watermark_tx indicates अगर we previously stopped the tx
		 * queues. If we have enough मुक्त stots in the virtio ring,
		 * re-establish memory reserved and खोलो up tx queues.
		 */
		अगर (cfv->vq_tx->num_मुक्त <= cfv->watermark_tx)
			जारी;

		/* Re-establish memory reserve */
		अगर (cfv->reserved_mem == 0 && cfv->genpool)
			cfv->reserved_mem =
				gen_pool_alloc(cfv->genpool,
					       cfv->reserved_size);

		/* Open up the tx queues */
		अगर (cfv->reserved_mem) अणु
			cfv->watermark_tx =
				virtqueue_get_vring_size(cfv->vq_tx);
			netअगर_tx_wake_all_queues(cfv->ndev);
			/* Buffers are recycled in cfv_netdev_tx, so
			 * disable notअगरications when queues are खोलोed.
			 */
			virtqueue_disable_cb(cfv->vq_tx);
			++cfv->stats.tx_flow_on;
		पूर्ण अन्यथा अणु
			/* अगर no memory reserve, रुको क्रम more मुक्त slots */
			WARN_ON(cfv->watermark_tx >
			       virtqueue_get_vring_size(cfv->vq_tx));
			cfv->watermark_tx +=
				virtqueue_get_vring_size(cfv->vq_tx) / 4;
		पूर्ण
	पूर्ण
पूर्ण

/* Allocate a SKB and copy packet data to it */
अटल काष्ठा sk_buff *cfv_alloc_and_copy_skb(पूर्णांक *err,
					      काष्ठा cfv_info *cfv,
					      u8 *frm, u32 frm_len)
अणु
	काष्ठा sk_buff *skb;
	u32 cfpkt_len, pad_len;

	*err = 0;
	/* Verअगरy that packet size with करोwn-link header and mtu size */
	अगर (frm_len > cfv->mru || frm_len <= cfv->rx_hr + cfv->rx_tr) अणु
		netdev_err(cfv->ndev,
			   "Invalid frmlen:%u  mtu:%u hr:%d tr:%d\n",
			   frm_len, cfv->mru,  cfv->rx_hr,
			   cfv->rx_tr);
		*err = -EPROTO;
		वापस शून्य;
	पूर्ण

	cfpkt_len = frm_len - (cfv->rx_hr + cfv->rx_tr);
	pad_len = (अचिन्हित दीर्घ)(frm + cfv->rx_hr) & (IP_HDR_ALIGN - 1);

	skb = netdev_alloc_skb(cfv->ndev, frm_len + pad_len);
	अगर (!skb) अणु
		*err = -ENOMEM;
		वापस शून्य;
	पूर्ण

	skb_reserve(skb, cfv->rx_hr + pad_len);

	skb_put_data(skb, frm + cfv->rx_hr, cfpkt_len);
	वापस skb;
पूर्ण

/* Get packets from the host vring */
अटल पूर्णांक cfv_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा cfv_info *cfv = container_of(napi, काष्ठा cfv_info, napi);
	पूर्णांक rxcnt = 0;
	पूर्णांक err = 0;
	व्योम *buf;
	काष्ठा sk_buff *skb;
	काष्ठा vringh_kiov *riov = &cfv->ctx.riov;
	अचिन्हित पूर्णांक skb_len;

	करो अणु
		skb = शून्य;

		/* Put the previous iovec back on the used ring and
		 * fetch a new iovec अगर we have processed all elements.
		 */
		अगर (riov->i == riov->used) अणु
			अगर (cfv->ctx.head != अच_लघु_उच्च) अणु
				vringh_complete_kern(cfv->vr_rx,
						     cfv->ctx.head,
						     0);
				cfv->ctx.head = अच_लघु_उच्च;
			पूर्ण

			err = vringh_getdesc_kern(
				cfv->vr_rx,
				riov,
				शून्य,
				&cfv->ctx.head,
				GFP_ATOMIC);

			अगर (err <= 0)
				जाओ निकास;
		पूर्ण

		buf = phys_to_virt((अचिन्हित दीर्घ) riov->iov[riov->i].iov_base);
		/* TODO: Add check on valid buffer address */

		skb = cfv_alloc_and_copy_skb(&err, cfv, buf,
					     riov->iov[riov->i].iov_len);
		अगर (unlikely(err))
			जाओ निकास;

		/* Push received packet up the stack. */
		skb_len = skb->len;
		skb->protocol = htons(ETH_P_CAIF);
		skb_reset_mac_header(skb);
		skb->dev = cfv->ndev;
		err = netअगर_receive_skb(skb);
		अगर (unlikely(err)) अणु
			++cfv->ndev->stats.rx_dropped;
		पूर्ण अन्यथा अणु
			++cfv->ndev->stats.rx_packets;
			cfv->ndev->stats.rx_bytes += skb_len;
		पूर्ण

		++riov->i;
		++rxcnt;
	पूर्ण जबतक (rxcnt < quota);

	++cfv->stats.rx_napi_resched;
	जाओ out;

निकास:
	चयन (err) अणु
	हाल 0:
		++cfv->stats.rx_napi_complete;

		/* Really out of patckets? (stolen from virtio_net)*/
		napi_complete(napi);
		अगर (unlikely(!vringh_notअगरy_enable_kern(cfv->vr_rx)) &&
		    napi_schedule_prep(napi)) अणु
			vringh_notअगरy_disable_kern(cfv->vr_rx);
			__napi_schedule(napi);
		पूर्ण
		अवरोध;

	हाल -ENOMEM:
		++cfv->stats.rx_nomem;
		dev_kमुक्त_skb(skb);
		/* Stop NAPI poll on OOM, we hope to be polled later */
		napi_complete(napi);
		vringh_notअगरy_enable_kern(cfv->vr_rx);
		अवरोध;

	शेष:
		/* We're करोomed, any modem fault is fatal */
		netdev_warn(cfv->ndev, "Bad ring, disable device\n");
		cfv->ndev->stats.rx_dropped = riov->used - riov->i;
		napi_complete(napi);
		vringh_notअगरy_disable_kern(cfv->vr_rx);
		netअगर_carrier_off(cfv->ndev);
		अवरोध;
	पूर्ण
out:
	अगर (rxcnt && vringh_need_notअगरy_kern(cfv->vr_rx) > 0)
		vringh_notअगरy(cfv->vr_rx);
	वापस rxcnt;
पूर्ण

अटल व्योम cfv_recv(काष्ठा virtio_device *vdev, काष्ठा vringh *vr_rx)
अणु
	काष्ठा cfv_info *cfv = vdev->priv;

	++cfv->stats.rx_kicks;
	vringh_notअगरy_disable_kern(cfv->vr_rx);
	napi_schedule(&cfv->napi);
पूर्ण

अटल व्योम cfv_destroy_genpool(काष्ठा cfv_info *cfv)
अणु
	अगर (cfv->alloc_addr)
		dma_मुक्त_coherent(cfv->vdev->dev.parent->parent,
				  cfv->allocsz, cfv->alloc_addr,
				  cfv->alloc_dma);

	अगर (!cfv->genpool)
		वापस;
	gen_pool_मुक्त(cfv->genpool,  cfv->reserved_mem,
		      cfv->reserved_size);
	gen_pool_destroy(cfv->genpool);
	cfv->genpool = शून्य;
पूर्ण

अटल पूर्णांक cfv_create_genpool(काष्ठा cfv_info *cfv)
अणु
	पूर्णांक err;

	/* dma_alloc can only allocate whole pages, and we need a more
	 * fine graned allocation so we use genpool. We ask क्रम space needed
	 * by IP and a full ring. If the dma allcoation fails we retry with a
	 * smaller allocation size.
	 */
	err = -ENOMEM;
	cfv->allocsz = (virtqueue_get_vring_size(cfv->vq_tx) *
			(ETH_DATA_LEN + cfv->tx_hr + cfv->tx_tr) * 11)/10;
	अगर (cfv->allocsz <= (num_possible_cpus() + 1) * cfv->ndev->mtu)
		वापस -EINVAL;

	क्रम (;;) अणु
		अगर (cfv->allocsz <= num_possible_cpus() * cfv->ndev->mtu) अणु
			netdev_info(cfv->ndev, "Not enough device memory\n");
			वापस -ENOMEM;
		पूर्ण

		cfv->alloc_addr = dma_alloc_coherent(
						cfv->vdev->dev.parent->parent,
						cfv->allocsz, &cfv->alloc_dma,
						GFP_ATOMIC);
		अगर (cfv->alloc_addr)
			अवरोध;

		cfv->allocsz = (cfv->allocsz * 3) >> 2;
	पूर्ण

	netdev_dbg(cfv->ndev, "Allocated %zd bytes from dma-memory\n",
		   cfv->allocsz);

	/* Allocate on 128 bytes boundaries (1 << 7)*/
	cfv->genpool = gen_pool_create(7, -1);
	अगर (!cfv->genpool)
		जाओ err;

	err = gen_pool_add_virt(cfv->genpool, (अचिन्हित दीर्घ)cfv->alloc_addr,
				(phys_addr_t)virt_to_phys(cfv->alloc_addr),
				cfv->allocsz, -1);
	अगर (err)
		जाओ err;

	/* Reserve some memory क्रम low memory situations. If we hit the roof
	 * in the memory pool, we stop TX flow and release the reserve.
	 */
	cfv->reserved_size = num_possible_cpus() * cfv->ndev->mtu;
	cfv->reserved_mem = gen_pool_alloc(cfv->genpool,
					   cfv->reserved_size);
	अगर (!cfv->reserved_mem) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	cfv->watermark_tx = virtqueue_get_vring_size(cfv->vq_tx);
	वापस 0;
err:
	cfv_destroy_genpool(cfv);
	वापस err;
पूर्ण

/* Enable the CAIF पूर्णांकerface and allocate the memory-pool */
अटल पूर्णांक cfv_netdev_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा cfv_info *cfv = netdev_priv(netdev);

	अगर (cfv_create_genpool(cfv))
		वापस -ENOMEM;

	netअगर_carrier_on(netdev);
	napi_enable(&cfv->napi);

	/* Schedule NAPI to पढ़ो any pending packets */
	napi_schedule(&cfv->napi);
	वापस 0;
पूर्ण

/* Disable the CAIF पूर्णांकerface and मुक्त the memory-pool */
अटल पूर्णांक cfv_netdev_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा cfv_info *cfv = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	काष्ठा buf_info *buf_info;

	/* Disable पूर्णांकerrupts, queues and NAPI polling */
	netअगर_carrier_off(netdev);
	virtqueue_disable_cb(cfv->vq_tx);
	vringh_notअगरy_disable_kern(cfv->vr_rx);
	napi_disable(&cfv->napi);

	/* Release any TX buffers on both used and avilable rings */
	cfv_release_used_buf(cfv->vq_tx);
	spin_lock_irqsave(&cfv->tx_lock, flags);
	जबतक ((buf_info = virtqueue_detach_unused_buf(cfv->vq_tx)))
		मुक्त_buf_info(cfv, buf_info);
	spin_unlock_irqrestore(&cfv->tx_lock, flags);

	/* Release all dma allocated memory and destroy the pool */
	cfv_destroy_genpool(cfv);
	वापस 0;
पूर्ण

/* Allocate a buffer in dma-memory and copy skb to it */
अटल काष्ठा buf_info *cfv_alloc_and_copy_to_shm(काष्ठा cfv_info *cfv,
						       काष्ठा sk_buff *skb,
						       काष्ठा scatterlist *sg)
अणु
	काष्ठा caअगर_payload_info *info = (व्योम *)&skb->cb;
	काष्ठा buf_info *buf_info = शून्य;
	u8 pad_len, hdr_ofs;

	अगर (!cfv->genpool)
		जाओ err;

	अगर (unlikely(cfv->tx_hr + skb->len + cfv->tx_tr > cfv->mtu)) अणु
		netdev_warn(cfv->ndev, "Invalid packet len (%d > %d)\n",
			    cfv->tx_hr + skb->len + cfv->tx_tr, cfv->mtu);
		जाओ err;
	पूर्ण

	buf_info = kदो_स्मृति(माप(काष्ठा buf_info), GFP_ATOMIC);
	अगर (unlikely(!buf_info))
		जाओ err;

	/* Make the IP header aligned in tbe buffer */
	hdr_ofs = cfv->tx_hr + info->hdr_len;
	pad_len = hdr_ofs & (IP_HDR_ALIGN - 1);
	buf_info->size = cfv->tx_hr + skb->len + cfv->tx_tr + pad_len;

	/* allocate dma memory buffer */
	buf_info->vaddr = (व्योम *)gen_pool_alloc(cfv->genpool, buf_info->size);
	अगर (unlikely(!buf_info->vaddr))
		जाओ err;

	/* copy skbuf contents to send buffer */
	skb_copy_bits(skb, 0, buf_info->vaddr + cfv->tx_hr + pad_len, skb->len);
	sg_init_one(sg, buf_info->vaddr + pad_len,
		    skb->len + cfv->tx_hr + cfv->rx_hr);

	वापस buf_info;
err:
	kमुक्त(buf_info);
	वापस शून्य;
पूर्ण

/* Put the CAIF packet on the virtio ring and kick the receiver */
अटल netdev_tx_t cfv_netdev_tx(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा cfv_info *cfv = netdev_priv(netdev);
	काष्ठा buf_info *buf_info;
	काष्ठा scatterlist sg;
	अचिन्हित दीर्घ flags;
	bool flow_off = false;
	पूर्णांक ret;

	/* garbage collect released buffers */
	cfv_release_used_buf(cfv->vq_tx);
	spin_lock_irqsave(&cfv->tx_lock, flags);

	/* Flow-off check takes पूर्णांकo account number of cpus to make sure
	 * virtqueue will not be overfilled in any possible smp conditions.
	 *
	 * Flow-on is triggered when sufficient buffers are मुक्तd
	 */
	अगर (unlikely(cfv->vq_tx->num_मुक्त <= num_present_cpus())) अणु
		flow_off = true;
		cfv->stats.tx_full_ring++;
	पूर्ण

	/* If we run out of memory, we release the memory reserve and retry
	 * allocation.
	 */
	buf_info = cfv_alloc_and_copy_to_shm(cfv, skb, &sg);
	अगर (unlikely(!buf_info)) अणु
		cfv->stats.tx_no_mem++;
		flow_off = true;

		अगर (cfv->reserved_mem && cfv->genpool) अणु
			gen_pool_मुक्त(cfv->genpool,  cfv->reserved_mem,
				      cfv->reserved_size);
			cfv->reserved_mem = 0;
			buf_info = cfv_alloc_and_copy_to_shm(cfv, skb, &sg);
		पूर्ण
	पूर्ण

	अगर (unlikely(flow_off)) अणु
		/* Turn flow on when a 1/4 of the descriptors are released */
		cfv->watermark_tx = virtqueue_get_vring_size(cfv->vq_tx) / 4;
		/* Enable notअगरications of recycled TX buffers */
		virtqueue_enable_cb(cfv->vq_tx);
		netअगर_tx_stop_all_queues(netdev);
	पूर्ण

	अगर (unlikely(!buf_info)) अणु
		/* If the memory reserve करोes it's job, this shouldn't happen */
		netdev_warn(cfv->ndev, "Out of gen_pool memory\n");
		जाओ err;
	पूर्ण

	ret = virtqueue_add_outbuf(cfv->vq_tx, &sg, 1, buf_info, GFP_ATOMIC);
	अगर (unlikely((ret < 0))) अणु
		/* If flow control works, this shouldn't happen */
		netdev_warn(cfv->ndev, "Failed adding buffer to TX vring:%d\n",
			    ret);
		जाओ err;
	पूर्ण

	/* update netdev statistics */
	cfv->ndev->stats.tx_packets++;
	cfv->ndev->stats.tx_bytes += skb->len;
	spin_unlock_irqrestore(&cfv->tx_lock, flags);

	/* tell the remote processor it has a pending message to पढ़ो */
	virtqueue_kick(cfv->vq_tx);

	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
err:
	spin_unlock_irqrestore(&cfv->tx_lock, flags);
	cfv->ndev->stats.tx_dropped++;
	मुक्त_buf_info(cfv, buf_info);
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम cfv_tx_release_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा cfv_info *cfv = from_tasklet(cfv, t, tx_release_tasklet);
	cfv_release_used_buf(cfv->vq_tx);
पूर्ण

अटल स्थिर काष्ठा net_device_ops cfv_netdev_ops = अणु
	.nकरो_खोलो = cfv_netdev_खोलो,
	.nकरो_stop = cfv_netdev_बंद,
	.nकरो_start_xmit = cfv_netdev_tx,
पूर्ण;

अटल व्योम cfv_netdev_setup(काष्ठा net_device *netdev)
अणु
	netdev->netdev_ops = &cfv_netdev_ops;
	netdev->type = ARPHRD_CAIF;
	netdev->tx_queue_len = 100;
	netdev->flags = IFF_POINTOPOINT | IFF_NOARP;
	netdev->mtu = CFV_DEF_MTU_SIZE;
	netdev->needs_मुक्त_netdev = true;
पूर्ण

/* Create debugfs counters क्रम the device */
अटल अंतरभूत व्योम debugfs_init(काष्ठा cfv_info *cfv)
अणु
	cfv->debugfs = debugfs_create_dir(netdev_name(cfv->ndev), शून्य);

	debugfs_create_u32("rx-napi-complete", 0400, cfv->debugfs,
			   &cfv->stats.rx_napi_complete);
	debugfs_create_u32("rx-napi-resched", 0400, cfv->debugfs,
			   &cfv->stats.rx_napi_resched);
	debugfs_create_u32("rx-nomem", 0400, cfv->debugfs,
			   &cfv->stats.rx_nomem);
	debugfs_create_u32("rx-kicks", 0400, cfv->debugfs,
			   &cfv->stats.rx_kicks);
	debugfs_create_u32("tx-full-ring", 0400, cfv->debugfs,
			   &cfv->stats.tx_full_ring);
	debugfs_create_u32("tx-no-mem", 0400, cfv->debugfs,
			   &cfv->stats.tx_no_mem);
	debugfs_create_u32("tx-kicks", 0400, cfv->debugfs,
			   &cfv->stats.tx_kicks);
	debugfs_create_u32("tx-flow-on", 0400, cfv->debugfs,
			   &cfv->stats.tx_flow_on);
पूर्ण

/* Setup CAIF क्रम the a virtio device */
अटल पूर्णांक cfv_probe(काष्ठा virtio_device *vdev)
अणु
	vq_callback_t *vq_cbs = cfv_release_cb;
	vrh_callback_t *vrh_cbs = cfv_recv;
	स्थिर अक्षर *names =  "output";
	स्थिर अक्षर *cfv_netdev_name = "cfvrt";
	काष्ठा net_device *netdev;
	काष्ठा cfv_info *cfv;
	पूर्णांक err;

	netdev = alloc_netdev(माप(काष्ठा cfv_info), cfv_netdev_name,
			      NET_NAME_UNKNOWN, cfv_netdev_setup);
	अगर (!netdev)
		वापस -ENOMEM;

	cfv = netdev_priv(netdev);
	cfv->vdev = vdev;
	cfv->ndev = netdev;

	spin_lock_init(&cfv->tx_lock);

	/* Get the RX virtio ring. This is a "host side vring". */
	err = -ENODEV;
	अगर (!vdev->vringh_config || !vdev->vringh_config->find_vrhs)
		जाओ err;

	err = vdev->vringh_config->find_vrhs(vdev, 1, &cfv->vr_rx, &vrh_cbs);
	अगर (err)
		जाओ err;

	/* Get the TX virtio ring. This is a "guest side vring". */
	err = virtio_find_vqs(vdev, 1, &cfv->vq_tx, &vq_cbs, &names, शून्य);
	अगर (err)
		जाओ err;

	/* Get the CAIF configuration from virtio config space, अगर available */
	अगर (vdev->config->get) अणु
		virtio_cपढ़ो(vdev, काष्ठा virtio_caअगर_transf_config, headroom,
			     &cfv->tx_hr);
		virtio_cपढ़ो(vdev, काष्ठा virtio_caअगर_transf_config, headroom,
			     &cfv->rx_hr);
		virtio_cपढ़ो(vdev, काष्ठा virtio_caअगर_transf_config, tailroom,
			     &cfv->tx_tr);
		virtio_cपढ़ो(vdev, काष्ठा virtio_caअगर_transf_config, tailroom,
			     &cfv->rx_tr);
		virtio_cपढ़ो(vdev, काष्ठा virtio_caअगर_transf_config, mtu,
			     &cfv->mtu);
		virtio_cपढ़ो(vdev, काष्ठा virtio_caअगर_transf_config, mtu,
			     &cfv->mru);
	पूर्ण अन्यथा अणु
		cfv->tx_hr = CFV_DEF_HEADROOM;
		cfv->rx_hr = CFV_DEF_HEADROOM;
		cfv->tx_tr = CFV_DEF_TAILROOM;
		cfv->rx_tr = CFV_DEF_TAILROOM;
		cfv->mtu = CFV_DEF_MTU_SIZE;
		cfv->mru = CFV_DEF_MTU_SIZE;
	पूर्ण

	netdev->needed_headroom = cfv->tx_hr;
	netdev->needed_tailroom = cfv->tx_tr;

	/* Disable buffer release पूर्णांकerrupts unless we have stopped TX queues */
	virtqueue_disable_cb(cfv->vq_tx);

	netdev->mtu = cfv->mtu - cfv->tx_tr;
	vdev->priv = cfv;

	/* Initialize NAPI poll context data */
	vringh_kiov_init(&cfv->ctx.riov, शून्य, 0);
	cfv->ctx.head = अच_लघु_उच्च;
	netअगर_napi_add(netdev, &cfv->napi, cfv_rx_poll, CFV_DEFAULT_QUOTA);

	tasklet_setup(&cfv->tx_release_tasklet, cfv_tx_release_tasklet);

	/* Carrier is off until netdevice is खोलोed */
	netअगर_carrier_off(netdev);

	/* रेजिस्टर Netdev */
	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(&vdev->dev, "Unable to register netdev (%d)\n", err);
		जाओ err;
	पूर्ण

	debugfs_init(cfv);

	वापस 0;
err:
	netdev_warn(cfv->ndev, "CAIF Virtio probe failed:%d\n", err);

	अगर (cfv->vr_rx)
		vdev->vringh_config->del_vrhs(cfv->vdev);
	अगर (cfv->vdev)
		vdev->config->del_vqs(cfv->vdev);
	मुक्त_netdev(netdev);
	वापस err;
पूर्ण

अटल व्योम cfv_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा cfv_info *cfv = vdev->priv;

	rtnl_lock();
	dev_बंद(cfv->ndev);
	rtnl_unlock();

	tasklet_समाप्त(&cfv->tx_release_tasklet);
	debugfs_हटाओ_recursive(cfv->debugfs);

	vringh_kiov_cleanup(&cfv->ctx.riov);
	vdev->config->reset(vdev);
	vdev->vringh_config->del_vrhs(cfv->vdev);
	cfv->vr_rx = शून्य;
	vdev->config->del_vqs(cfv->vdev);
	unरेजिस्टर_netdev(cfv->ndev);
पूर्ण

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_CAIF, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक features[] = अणु
पूर्ण;

अटल काष्ठा virtio_driver caअगर_virtio_driver = अणु
	.feature_table		= features,
	.feature_table_size	= ARRAY_SIZE(features),
	.driver.name		= KBUILD_MODNAME,
	.driver.owner		= THIS_MODULE,
	.id_table		= id_table,
	.probe			= cfv_probe,
	.हटाओ			= cfv_हटाओ,
पूर्ण;

module_virtio_driver(caअगर_virtio_driver);
MODULE_DEVICE_TABLE(virtio, id_table);
