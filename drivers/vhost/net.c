<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2009 Red Hat, Inc.
 * Author: Michael S. Tsirkin <mst@redhat.com>
 *
 * virtio-net server in host kernel.
 */

#समावेश <linux/compat.h>
#समावेश <linux/eventfd.h>
#समावेश <linux/vhost.h>
#समावेश <linux/virtio_net.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/net.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_tun.h>
#समावेश <linux/अगर_macvlan.h>
#समावेश <linux/अगर_tap.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/skb_array.h>
#समावेश <linux/skbuff.h>

#समावेश <net/sock.h>
#समावेश <net/xdp.h>

#समावेश "vhost.h"

अटल पूर्णांक experimental_zcopytx = 0;
module_param(experimental_zcopytx, पूर्णांक, 0444);
MODULE_PARM_DESC(experimental_zcopytx, "Enable Zero Copy TX;"
		                       " 1 -Enable; 0 - Disable");

/* Max number of bytes transferred beक्रमe requeueing the job.
 * Using this limit prevents one virtqueue from starving others. */
#घोषणा VHOST_NET_WEIGHT 0x80000

/* Max number of packets transferred beक्रमe requeueing the job.
 * Using this limit prevents one virtqueue from starving others with small
 * pkts.
 */
#घोषणा VHOST_NET_PKT_WEIGHT 256

/* MAX number of TX used buffers क्रम outstanding zerocopy */
#घोषणा VHOST_MAX_PEND 128
#घोषणा VHOST_GOODCOPY_LEN 256

/*
 * For transmit, used buffer len is unused; we override it to track buffer
 * status पूर्णांकernally; used क्रम zerocopy tx only.
 */
/* Lower device DMA failed */
#घोषणा VHOST_DMA_FAILED_LEN	((__क्रमce __virtio32)3)
/* Lower device DMA करोne */
#घोषणा VHOST_DMA_DONE_LEN	((__क्रमce __virtio32)2)
/* Lower device DMA in progress */
#घोषणा VHOST_DMA_IN_PROGRESS	((__क्रमce __virtio32)1)
/* Buffer unused */
#घोषणा VHOST_DMA_CLEAR_LEN	((__क्रमce __virtio32)0)

#घोषणा VHOST_DMA_IS_DONE(len) ((__क्रमce u32)(len) >= (__क्रमce u32)VHOST_DMA_DONE_LEN)

क्रमागत अणु
	VHOST_NET_FEATURES = VHOST_FEATURES |
			 (1ULL << VHOST_NET_F_VIRTIO_NET_HDR) |
			 (1ULL << VIRTIO_NET_F_MRG_RXBUF) |
			 (1ULL << VIRTIO_F_ACCESS_PLATFORM)
पूर्ण;

क्रमागत अणु
	VHOST_NET_BACKEND_FEATURES = (1ULL << VHOST_BACKEND_F_IOTLB_MSG_V2)
पूर्ण;

क्रमागत अणु
	VHOST_NET_VQ_RX = 0,
	VHOST_NET_VQ_TX = 1,
	VHOST_NET_VQ_MAX = 2,
पूर्ण;

काष्ठा vhost_net_ubuf_ref अणु
	/* refcount follows semantics similar to kref:
	 *  0: object is released
	 *  1: no outstanding ubufs
	 * >1: outstanding ubufs
	 */
	atomic_t refcount;
	रुको_queue_head_t रुको;
	काष्ठा vhost_virtqueue *vq;
पूर्ण;

#घोषणा VHOST_NET_BATCH 64
काष्ठा vhost_net_buf अणु
	व्योम **queue;
	पूर्णांक tail;
	पूर्णांक head;
पूर्ण;

काष्ठा vhost_net_virtqueue अणु
	काष्ठा vhost_virtqueue vq;
	माप_प्रकार vhost_hlen;
	माप_प्रकार sock_hlen;
	/* vhost zerocopy support fields below: */
	/* last used idx क्रम outstanding DMA zerocopy buffers */
	पूर्णांक upend_idx;
	/* For TX, first used idx क्रम DMA करोne zerocopy buffers
	 * For RX, number of batched heads
	 */
	पूर्णांक करोne_idx;
	/* Number of XDP frames batched */
	पूर्णांक batched_xdp;
	/* an array of userspace buffers info */
	काष्ठा ubuf_info *ubuf_info;
	/* Reference counting क्रम outstanding ubufs.
	 * Protected by vq mutex. Writers must also take device mutex. */
	काष्ठा vhost_net_ubuf_ref *ubufs;
	काष्ठा ptr_ring *rx_ring;
	काष्ठा vhost_net_buf rxq;
	/* Batched XDP buffs */
	काष्ठा xdp_buff *xdp;
पूर्ण;

काष्ठा vhost_net अणु
	काष्ठा vhost_dev dev;
	काष्ठा vhost_net_virtqueue vqs[VHOST_NET_VQ_MAX];
	काष्ठा vhost_poll poll[VHOST_NET_VQ_MAX];
	/* Number of TX recently submitted.
	 * Protected by tx vq lock. */
	अचिन्हित tx_packets;
	/* Number of बार zerocopy TX recently failed.
	 * Protected by tx vq lock. */
	अचिन्हित tx_zcopy_err;
	/* Flush in progress. Protected by tx vq lock. */
	bool tx_flush;
	/* Private page frag */
	काष्ठा page_frag page_frag;
	/* Refcount bias of page frag */
	पूर्णांक refcnt_bias;
पूर्ण;

अटल अचिन्हित vhost_net_zcopy_mask __पढ़ो_mostly;

अटल व्योम *vhost_net_buf_get_ptr(काष्ठा vhost_net_buf *rxq)
अणु
	अगर (rxq->tail != rxq->head)
		वापस rxq->queue[rxq->head];
	अन्यथा
		वापस शून्य;
पूर्ण

अटल पूर्णांक vhost_net_buf_get_size(काष्ठा vhost_net_buf *rxq)
अणु
	वापस rxq->tail - rxq->head;
पूर्ण

अटल पूर्णांक vhost_net_buf_is_empty(काष्ठा vhost_net_buf *rxq)
अणु
	वापस rxq->tail == rxq->head;
पूर्ण

अटल व्योम *vhost_net_buf_consume(काष्ठा vhost_net_buf *rxq)
अणु
	व्योम *ret = vhost_net_buf_get_ptr(rxq);
	++rxq->head;
	वापस ret;
पूर्ण

अटल पूर्णांक vhost_net_buf_produce(काष्ठा vhost_net_virtqueue *nvq)
अणु
	काष्ठा vhost_net_buf *rxq = &nvq->rxq;

	rxq->head = 0;
	rxq->tail = ptr_ring_consume_batched(nvq->rx_ring, rxq->queue,
					      VHOST_NET_BATCH);
	वापस rxq->tail;
पूर्ण

अटल व्योम vhost_net_buf_unproduce(काष्ठा vhost_net_virtqueue *nvq)
अणु
	काष्ठा vhost_net_buf *rxq = &nvq->rxq;

	अगर (nvq->rx_ring && !vhost_net_buf_is_empty(rxq)) अणु
		ptr_ring_unconsume(nvq->rx_ring, rxq->queue + rxq->head,
				   vhost_net_buf_get_size(rxq),
				   tun_ptr_मुक्त);
		rxq->head = rxq->tail = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक vhost_net_buf_peek_len(व्योम *ptr)
अणु
	अगर (tun_is_xdp_frame(ptr)) अणु
		काष्ठा xdp_frame *xdpf = tun_ptr_to_xdp(ptr);

		वापस xdpf->len;
	पूर्ण

	वापस __skb_array_len_with_tag(ptr);
पूर्ण

अटल पूर्णांक vhost_net_buf_peek(काष्ठा vhost_net_virtqueue *nvq)
अणु
	काष्ठा vhost_net_buf *rxq = &nvq->rxq;

	अगर (!vhost_net_buf_is_empty(rxq))
		जाओ out;

	अगर (!vhost_net_buf_produce(nvq))
		वापस 0;

out:
	वापस vhost_net_buf_peek_len(vhost_net_buf_get_ptr(rxq));
पूर्ण

अटल व्योम vhost_net_buf_init(काष्ठा vhost_net_buf *rxq)
अणु
	rxq->head = rxq->tail = 0;
पूर्ण

अटल व्योम vhost_net_enable_zcopy(पूर्णांक vq)
अणु
	vhost_net_zcopy_mask |= 0x1 << vq;
पूर्ण

अटल काष्ठा vhost_net_ubuf_ref *
vhost_net_ubuf_alloc(काष्ठा vhost_virtqueue *vq, bool zcopy)
अणु
	काष्ठा vhost_net_ubuf_ref *ubufs;
	/* No zero copy backend? Nothing to count. */
	अगर (!zcopy)
		वापस शून्य;
	ubufs = kदो_स्मृति(माप(*ubufs), GFP_KERNEL);
	अगर (!ubufs)
		वापस ERR_PTR(-ENOMEM);
	atomic_set(&ubufs->refcount, 1);
	init_रुकोqueue_head(&ubufs->रुको);
	ubufs->vq = vq;
	वापस ubufs;
पूर्ण

अटल पूर्णांक vhost_net_ubuf_put(काष्ठा vhost_net_ubuf_ref *ubufs)
अणु
	पूर्णांक r = atomic_sub_वापस(1, &ubufs->refcount);
	अगर (unlikely(!r))
		wake_up(&ubufs->रुको);
	वापस r;
पूर्ण

अटल व्योम vhost_net_ubuf_put_and_रुको(काष्ठा vhost_net_ubuf_ref *ubufs)
अणु
	vhost_net_ubuf_put(ubufs);
	रुको_event(ubufs->रुको, !atomic_पढ़ो(&ubufs->refcount));
पूर्ण

अटल व्योम vhost_net_ubuf_put_रुको_and_मुक्त(काष्ठा vhost_net_ubuf_ref *ubufs)
अणु
	vhost_net_ubuf_put_and_रुको(ubufs);
	kमुक्त(ubufs);
पूर्ण

अटल व्योम vhost_net_clear_ubuf_info(काष्ठा vhost_net *n)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VHOST_NET_VQ_MAX; ++i) अणु
		kमुक्त(n->vqs[i].ubuf_info);
		n->vqs[i].ubuf_info = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक vhost_net_set_ubuf_info(काष्ठा vhost_net *n)
अणु
	bool zcopy;
	पूर्णांक i;

	क्रम (i = 0; i < VHOST_NET_VQ_MAX; ++i) अणु
		zcopy = vhost_net_zcopy_mask & (0x1 << i);
		अगर (!zcopy)
			जारी;
		n->vqs[i].ubuf_info =
			kदो_स्मृति_array(UIO_MAXIOV,
				      माप(*n->vqs[i].ubuf_info),
				      GFP_KERNEL);
		अगर  (!n->vqs[i].ubuf_info)
			जाओ err;
	पूर्ण
	वापस 0;

err:
	vhost_net_clear_ubuf_info(n);
	वापस -ENOMEM;
पूर्ण

अटल व्योम vhost_net_vq_reset(काष्ठा vhost_net *n)
अणु
	पूर्णांक i;

	vhost_net_clear_ubuf_info(n);

	क्रम (i = 0; i < VHOST_NET_VQ_MAX; i++) अणु
		n->vqs[i].करोne_idx = 0;
		n->vqs[i].upend_idx = 0;
		n->vqs[i].ubufs = शून्य;
		n->vqs[i].vhost_hlen = 0;
		n->vqs[i].sock_hlen = 0;
		vhost_net_buf_init(&n->vqs[i].rxq);
	पूर्ण

पूर्ण

अटल व्योम vhost_net_tx_packet(काष्ठा vhost_net *net)
अणु
	++net->tx_packets;
	अगर (net->tx_packets < 1024)
		वापस;
	net->tx_packets = 0;
	net->tx_zcopy_err = 0;
पूर्ण

अटल व्योम vhost_net_tx_err(काष्ठा vhost_net *net)
अणु
	++net->tx_zcopy_err;
पूर्ण

अटल bool vhost_net_tx_select_zcopy(काष्ठा vhost_net *net)
अणु
	/* TX flush रुकोs क्रम outstanding DMAs to be करोne.
	 * Don't start new DMAs.
	 */
	वापस !net->tx_flush &&
		net->tx_packets / 64 >= net->tx_zcopy_err;
पूर्ण

अटल bool vhost_sock_zcopy(काष्ठा socket *sock)
अणु
	वापस unlikely(experimental_zcopytx) &&
		sock_flag(sock->sk, SOCK_ZEROCOPY);
पूर्ण

अटल bool vhost_sock_xdp(काष्ठा socket *sock)
अणु
	वापस sock_flag(sock->sk, SOCK_XDP);
पूर्ण

/* In हाल of DMA करोne not in order in lower device driver क्रम some reason.
 * upend_idx is used to track end of used idx, करोne_idx is used to track head
 * of used idx. Once lower device DMA करोne contiguously, we will संकेत KVM
 * guest used idx.
 */
अटल व्योम vhost_zerocopy_संकेत_used(काष्ठा vhost_net *net,
				       काष्ठा vhost_virtqueue *vq)
अणु
	काष्ठा vhost_net_virtqueue *nvq =
		container_of(vq, काष्ठा vhost_net_virtqueue, vq);
	पूर्णांक i, add;
	पूर्णांक j = 0;

	क्रम (i = nvq->करोne_idx; i != nvq->upend_idx; i = (i + 1) % UIO_MAXIOV) अणु
		अगर (vq->heads[i].len == VHOST_DMA_FAILED_LEN)
			vhost_net_tx_err(net);
		अगर (VHOST_DMA_IS_DONE(vq->heads[i].len)) अणु
			vq->heads[i].len = VHOST_DMA_CLEAR_LEN;
			++j;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	जबतक (j) अणु
		add = min(UIO_MAXIOV - nvq->करोne_idx, j);
		vhost_add_used_and_संकेत_n(vq->dev, vq,
					    &vq->heads[nvq->करोne_idx], add);
		nvq->करोne_idx = (nvq->करोne_idx + add) % UIO_MAXIOV;
		j -= add;
	पूर्ण
पूर्ण

अटल व्योम vhost_zerocopy_callback(काष्ठा sk_buff *skb,
				    काष्ठा ubuf_info *ubuf, bool success)
अणु
	काष्ठा vhost_net_ubuf_ref *ubufs = ubuf->ctx;
	काष्ठा vhost_virtqueue *vq = ubufs->vq;
	पूर्णांक cnt;

	rcu_पढ़ो_lock_bh();

	/* set len to mark this desc buffers करोne DMA */
	vq->heads[ubuf->desc].len = success ?
		VHOST_DMA_DONE_LEN : VHOST_DMA_FAILED_LEN;
	cnt = vhost_net_ubuf_put(ubufs);

	/*
	 * Trigger polling thपढ़ो अगर guest stopped submitting new buffers:
	 * in this हाल, the refcount after decrement will eventually reach 1.
	 * We also trigger polling periodically after each 16 packets
	 * (the value 16 here is more or less arbitrary, it's tuned to trigger
	 * less than 10% of बार).
	 */
	अगर (cnt <= 1 || !(cnt % 16))
		vhost_poll_queue(&vq->poll);

	rcu_पढ़ो_unlock_bh();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ busy_घड़ी(व्योम)
अणु
	वापस local_घड़ी() >> 10;
पूर्ण

अटल bool vhost_can_busy_poll(अचिन्हित दीर्घ endसमय)
अणु
	वापस likely(!need_resched() && !समय_after(busy_घड़ी(), endसमय) &&
		      !संकेत_pending(current));
पूर्ण

अटल व्योम vhost_net_disable_vq(काष्ठा vhost_net *n,
				 काष्ठा vhost_virtqueue *vq)
अणु
	काष्ठा vhost_net_virtqueue *nvq =
		container_of(vq, काष्ठा vhost_net_virtqueue, vq);
	काष्ठा vhost_poll *poll = n->poll + (nvq - n->vqs);
	अगर (!vhost_vq_get_backend(vq))
		वापस;
	vhost_poll_stop(poll);
पूर्ण

अटल पूर्णांक vhost_net_enable_vq(काष्ठा vhost_net *n,
				काष्ठा vhost_virtqueue *vq)
अणु
	काष्ठा vhost_net_virtqueue *nvq =
		container_of(vq, काष्ठा vhost_net_virtqueue, vq);
	काष्ठा vhost_poll *poll = n->poll + (nvq - n->vqs);
	काष्ठा socket *sock;

	sock = vhost_vq_get_backend(vq);
	अगर (!sock)
		वापस 0;

	वापस vhost_poll_start(poll, sock->file);
पूर्ण

अटल व्योम vhost_net_संकेत_used(काष्ठा vhost_net_virtqueue *nvq)
अणु
	काष्ठा vhost_virtqueue *vq = &nvq->vq;
	काष्ठा vhost_dev *dev = vq->dev;

	अगर (!nvq->करोne_idx)
		वापस;

	vhost_add_used_and_संकेत_n(dev, vq, vq->heads, nvq->करोne_idx);
	nvq->करोne_idx = 0;
पूर्ण

अटल व्योम vhost_tx_batch(काष्ठा vhost_net *net,
			   काष्ठा vhost_net_virtqueue *nvq,
			   काष्ठा socket *sock,
			   काष्ठा msghdr *msghdr)
अणु
	काष्ठा tun_msg_ctl ctl = अणु
		.type = TUN_MSG_PTR,
		.num = nvq->batched_xdp,
		.ptr = nvq->xdp,
	पूर्ण;
	पूर्णांक err;

	अगर (nvq->batched_xdp == 0)
		जाओ संकेत_used;

	msghdr->msg_control = &ctl;
	err = sock->ops->sendmsg(sock, msghdr, 0);
	अगर (unlikely(err < 0)) अणु
		vq_err(&nvq->vq, "Fail to batch sending packets\n");
		वापस;
	पूर्ण

संकेत_used:
	vhost_net_संकेत_used(nvq);
	nvq->batched_xdp = 0;
पूर्ण

अटल पूर्णांक sock_has_rx_data(काष्ठा socket *sock)
अणु
	अगर (unlikely(!sock))
		वापस 0;

	अगर (sock->ops->peek_len)
		वापस sock->ops->peek_len(sock);

	वापस skb_queue_empty(&sock->sk->sk_receive_queue);
पूर्ण

अटल व्योम vhost_net_busy_poll_try_queue(काष्ठा vhost_net *net,
					  काष्ठा vhost_virtqueue *vq)
अणु
	अगर (!vhost_vq_avail_empty(&net->dev, vq)) अणु
		vhost_poll_queue(&vq->poll);
	पूर्ण अन्यथा अगर (unlikely(vhost_enable_notअगरy(&net->dev, vq))) अणु
		vhost_disable_notअगरy(&net->dev, vq);
		vhost_poll_queue(&vq->poll);
	पूर्ण
पूर्ण

अटल व्योम vhost_net_busy_poll(काष्ठा vhost_net *net,
				काष्ठा vhost_virtqueue *rvq,
				काष्ठा vhost_virtqueue *tvq,
				bool *busyloop_पूर्णांकr,
				bool poll_rx)
अणु
	अचिन्हित दीर्घ busyloop_समयout;
	अचिन्हित दीर्घ endसमय;
	काष्ठा socket *sock;
	काष्ठा vhost_virtqueue *vq = poll_rx ? tvq : rvq;

	/* Try to hold the vq mutex of the paired virtqueue. We can't
	 * use mutex_lock() here since we could not guarantee a
	 * consistenet lock ordering.
	 */
	अगर (!mutex_trylock(&vq->mutex))
		वापस;

	vhost_disable_notअगरy(&net->dev, vq);
	sock = vhost_vq_get_backend(rvq);

	busyloop_समयout = poll_rx ? rvq->busyloop_समयout:
				     tvq->busyloop_समयout;

	preempt_disable();
	endसमय = busy_घड़ी() + busyloop_समयout;

	जबतक (vhost_can_busy_poll(endसमय)) अणु
		अगर (vhost_has_work(&net->dev)) अणु
			*busyloop_पूर्णांकr = true;
			अवरोध;
		पूर्ण

		अगर ((sock_has_rx_data(sock) &&
		     !vhost_vq_avail_empty(&net->dev, rvq)) ||
		    !vhost_vq_avail_empty(&net->dev, tvq))
			अवरोध;

		cpu_relax();
	पूर्ण

	preempt_enable();

	अगर (poll_rx || sock_has_rx_data(sock))
		vhost_net_busy_poll_try_queue(net, vq);
	अन्यथा अगर (!poll_rx) /* On tx here, sock has no rx data. */
		vhost_enable_notअगरy(&net->dev, rvq);

	mutex_unlock(&vq->mutex);
पूर्ण

अटल पूर्णांक vhost_net_tx_get_vq_desc(काष्ठा vhost_net *net,
				    काष्ठा vhost_net_virtqueue *tnvq,
				    अचिन्हित पूर्णांक *out_num, अचिन्हित पूर्णांक *in_num,
				    काष्ठा msghdr *msghdr, bool *busyloop_पूर्णांकr)
अणु
	काष्ठा vhost_net_virtqueue *rnvq = &net->vqs[VHOST_NET_VQ_RX];
	काष्ठा vhost_virtqueue *rvq = &rnvq->vq;
	काष्ठा vhost_virtqueue *tvq = &tnvq->vq;

	पूर्णांक r = vhost_get_vq_desc(tvq, tvq->iov, ARRAY_SIZE(tvq->iov),
				  out_num, in_num, शून्य, शून्य);

	अगर (r == tvq->num && tvq->busyloop_समयout) अणु
		/* Flush batched packets first */
		अगर (!vhost_sock_zcopy(vhost_vq_get_backend(tvq)))
			vhost_tx_batch(net, tnvq,
				       vhost_vq_get_backend(tvq),
				       msghdr);

		vhost_net_busy_poll(net, rvq, tvq, busyloop_पूर्णांकr, false);

		r = vhost_get_vq_desc(tvq, tvq->iov, ARRAY_SIZE(tvq->iov),
				      out_num, in_num, शून्य, शून्य);
	पूर्ण

	वापस r;
पूर्ण

अटल bool vhost_exceeds_maxpend(काष्ठा vhost_net *net)
अणु
	काष्ठा vhost_net_virtqueue *nvq = &net->vqs[VHOST_NET_VQ_TX];
	काष्ठा vhost_virtqueue *vq = &nvq->vq;

	वापस (nvq->upend_idx + UIO_MAXIOV - nvq->करोne_idx) % UIO_MAXIOV >
	       min_t(अचिन्हित पूर्णांक, VHOST_MAX_PEND, vq->num >> 2);
पूर्ण

अटल माप_प्रकार init_iov_iter(काष्ठा vhost_virtqueue *vq, काष्ठा iov_iter *iter,
			    माप_प्रकार hdr_size, पूर्णांक out)
अणु
	/* Skip header. TODO: support TSO. */
	माप_प्रकार len = iov_length(vq->iov, out);

	iov_iter_init(iter, WRITE, vq->iov, out, len);
	iov_iter_advance(iter, hdr_size);

	वापस iov_iter_count(iter);
पूर्ण

अटल पूर्णांक get_tx_bufs(काष्ठा vhost_net *net,
		       काष्ठा vhost_net_virtqueue *nvq,
		       काष्ठा msghdr *msg,
		       अचिन्हित पूर्णांक *out, अचिन्हित पूर्णांक *in,
		       माप_प्रकार *len, bool *busyloop_पूर्णांकr)
अणु
	काष्ठा vhost_virtqueue *vq = &nvq->vq;
	पूर्णांक ret;

	ret = vhost_net_tx_get_vq_desc(net, nvq, out, in, msg, busyloop_पूर्णांकr);

	अगर (ret < 0 || ret == vq->num)
		वापस ret;

	अगर (*in) अणु
		vq_err(vq, "Unexpected descriptor format for TX: out %d, int %d\n",
			*out, *in);
		वापस -EFAULT;
	पूर्ण

	/* Sanity check */
	*len = init_iov_iter(vq, &msg->msg_iter, nvq->vhost_hlen, *out);
	अगर (*len == 0) अणु
		vq_err(vq, "Unexpected header len for TX: %zd expected %zd\n",
			*len, nvq->vhost_hlen);
		वापस -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool tx_can_batch(काष्ठा vhost_virtqueue *vq, माप_प्रकार total_len)
अणु
	वापस total_len < VHOST_NET_WEIGHT &&
	       !vhost_vq_avail_empty(vq->dev, vq);
पूर्ण

#घोषणा SKB_FRAG_PAGE_ORDER     get_order(32768)

अटल bool vhost_net_page_frag_refill(काष्ठा vhost_net *net, अचिन्हित पूर्णांक sz,
				       काष्ठा page_frag *pfrag, gfp_t gfp)
अणु
	अगर (pfrag->page) अणु
		अगर (pfrag->offset + sz <= pfrag->size)
			वापस true;
		__page_frag_cache_drain(pfrag->page, net->refcnt_bias);
	पूर्ण

	pfrag->offset = 0;
	net->refcnt_bias = 0;
	अगर (SKB_FRAG_PAGE_ORDER) अणु
		/* Aव्योम direct reclaim but allow kswapd to wake */
		pfrag->page = alloc_pages((gfp & ~__GFP_सूचीECT_RECLAIM) |
					  __GFP_COMP | __GFP_NOWARN |
					  __GFP_NORETRY,
					  SKB_FRAG_PAGE_ORDER);
		अगर (likely(pfrag->page)) अणु
			pfrag->size = PAGE_SIZE << SKB_FRAG_PAGE_ORDER;
			जाओ करोne;
		पूर्ण
	पूर्ण
	pfrag->page = alloc_page(gfp);
	अगर (likely(pfrag->page)) अणु
		pfrag->size = PAGE_SIZE;
		जाओ करोne;
	पूर्ण
	वापस false;

करोne:
	net->refcnt_bias = अच_लघु_उच्च;
	page_ref_add(pfrag->page, अच_लघु_उच्च - 1);
	वापस true;
पूर्ण

#घोषणा VHOST_NET_RX_PAD (NET_IP_ALIGN + NET_SKB_PAD)

अटल पूर्णांक vhost_net_build_xdp(काष्ठा vhost_net_virtqueue *nvq,
			       काष्ठा iov_iter *from)
अणु
	काष्ठा vhost_virtqueue *vq = &nvq->vq;
	काष्ठा vhost_net *net = container_of(vq->dev, काष्ठा vhost_net,
					     dev);
	काष्ठा socket *sock = vhost_vq_get_backend(vq);
	काष्ठा page_frag *alloc_frag = &net->page_frag;
	काष्ठा virtio_net_hdr *gso;
	काष्ठा xdp_buff *xdp = &nvq->xdp[nvq->batched_xdp];
	काष्ठा tun_xdp_hdr *hdr;
	माप_प्रकार len = iov_iter_count(from);
	पूर्णांक headroom = vhost_sock_xdp(sock) ? XDP_PACKET_HEADROOM : 0;
	पूर्णांक buflen = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	पूर्णांक pad = SKB_DATA_ALIGN(VHOST_NET_RX_PAD + headroom + nvq->sock_hlen);
	पूर्णांक sock_hlen = nvq->sock_hlen;
	व्योम *buf;
	पूर्णांक copied;

	अगर (unlikely(len < nvq->sock_hlen))
		वापस -EFAULT;

	अगर (SKB_DATA_ALIGN(len + pad) +
	    SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) > PAGE_SIZE)
		वापस -ENOSPC;

	buflen += SKB_DATA_ALIGN(len + pad);
	alloc_frag->offset = ALIGN((u64)alloc_frag->offset, SMP_CACHE_BYTES);
	अगर (unlikely(!vhost_net_page_frag_refill(net, buflen,
						 alloc_frag, GFP_KERNEL)))
		वापस -ENOMEM;

	buf = (अक्षर *)page_address(alloc_frag->page) + alloc_frag->offset;
	copied = copy_page_from_iter(alloc_frag->page,
				     alloc_frag->offset +
				     दुरत्व(काष्ठा tun_xdp_hdr, gso),
				     sock_hlen, from);
	अगर (copied != sock_hlen)
		वापस -EFAULT;

	hdr = buf;
	gso = &hdr->gso;

	अगर ((gso->flags & VIRTIO_NET_HDR_F_NEEDS_CSUM) &&
	    vhost16_to_cpu(vq, gso->csum_start) +
	    vhost16_to_cpu(vq, gso->csum_offset) + 2 >
	    vhost16_to_cpu(vq, gso->hdr_len)) अणु
		gso->hdr_len = cpu_to_vhost16(vq,
			       vhost16_to_cpu(vq, gso->csum_start) +
			       vhost16_to_cpu(vq, gso->csum_offset) + 2);

		अगर (vhost16_to_cpu(vq, gso->hdr_len) > len)
			वापस -EINVAL;
	पूर्ण

	len -= sock_hlen;
	copied = copy_page_from_iter(alloc_frag->page,
				     alloc_frag->offset + pad,
				     len, from);
	अगर (copied != len)
		वापस -EFAULT;

	xdp->data_hard_start = buf;
	xdp->data = buf + pad;
	xdp->data_end = xdp->data + len;
	hdr->buflen = buflen;
	xdp->frame_sz = buflen;

	--net->refcnt_bias;
	alloc_frag->offset += buflen;

	++nvq->batched_xdp;

	वापस 0;
पूर्ण

अटल व्योम handle_tx_copy(काष्ठा vhost_net *net, काष्ठा socket *sock)
अणु
	काष्ठा vhost_net_virtqueue *nvq = &net->vqs[VHOST_NET_VQ_TX];
	काष्ठा vhost_virtqueue *vq = &nvq->vq;
	अचिन्हित out, in;
	पूर्णांक head;
	काष्ठा msghdr msg = अणु
		.msg_name = शून्य,
		.msg_namelen = 0,
		.msg_control = शून्य,
		.msg_controllen = 0,
		.msg_flags = MSG_DONTWAIT,
	पूर्ण;
	माप_प्रकार len, total_len = 0;
	पूर्णांक err;
	पूर्णांक sent_pkts = 0;
	bool sock_can_batch = (sock->sk->sk_sndbuf == पूर्णांक_उच्च);

	करो अणु
		bool busyloop_पूर्णांकr = false;

		अगर (nvq->करोne_idx == VHOST_NET_BATCH)
			vhost_tx_batch(net, nvq, sock, &msg);

		head = get_tx_bufs(net, nvq, &msg, &out, &in, &len,
				   &busyloop_पूर्णांकr);
		/* On error, stop handling until the next kick. */
		अगर (unlikely(head < 0))
			अवरोध;
		/* Nothing new?  Wait क्रम eventfd to tell us they refilled. */
		अगर (head == vq->num) अणु
			अगर (unlikely(busyloop_पूर्णांकr)) अणु
				vhost_poll_queue(&vq->poll);
			पूर्ण अन्यथा अगर (unlikely(vhost_enable_notअगरy(&net->dev,
								vq))) अणु
				vhost_disable_notअगरy(&net->dev, vq);
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		total_len += len;

		/* For simplicity, TX batching is only enabled अगर
		 * sndbuf is unlimited.
		 */
		अगर (sock_can_batch) अणु
			err = vhost_net_build_xdp(nvq, &msg.msg_iter);
			अगर (!err) अणु
				जाओ करोne;
			पूर्ण अन्यथा अगर (unlikely(err != -ENOSPC)) अणु
				vhost_tx_batch(net, nvq, sock, &msg);
				vhost_discard_vq_desc(vq, 1);
				vhost_net_enable_vq(net, vq);
				अवरोध;
			पूर्ण

			/* We can't build XDP buff, go क्रम single
			 * packet path but let's flush batched
			 * packets.
			 */
			vhost_tx_batch(net, nvq, sock, &msg);
			msg.msg_control = शून्य;
		पूर्ण अन्यथा अणु
			अगर (tx_can_batch(vq, total_len))
				msg.msg_flags |= MSG_MORE;
			अन्यथा
				msg.msg_flags &= ~MSG_MORE;
		पूर्ण

		err = sock->ops->sendmsg(sock, &msg, len);
		अगर (unlikely(err < 0)) अणु
			अगर (err == -EAGAIN || err == -ENOMEM || err == -ENOBUFS) अणु
				vhost_discard_vq_desc(vq, 1);
				vhost_net_enable_vq(net, vq);
				अवरोध;
			पूर्ण
			pr_debug("Fail to send packet: err %d", err);
		पूर्ण अन्यथा अगर (unlikely(err != len))
			pr_debug("Truncated TX packet: len %d != %zd\n",
				 err, len);
करोne:
		vq->heads[nvq->करोne_idx].id = cpu_to_vhost32(vq, head);
		vq->heads[nvq->करोne_idx].len = 0;
		++nvq->करोne_idx;
	पूर्ण जबतक (likely(!vhost_exceeds_weight(vq, ++sent_pkts, total_len)));

	vhost_tx_batch(net, nvq, sock, &msg);
पूर्ण

अटल व्योम handle_tx_zerocopy(काष्ठा vhost_net *net, काष्ठा socket *sock)
अणु
	काष्ठा vhost_net_virtqueue *nvq = &net->vqs[VHOST_NET_VQ_TX];
	काष्ठा vhost_virtqueue *vq = &nvq->vq;
	अचिन्हित out, in;
	पूर्णांक head;
	काष्ठा msghdr msg = अणु
		.msg_name = शून्य,
		.msg_namelen = 0,
		.msg_control = शून्य,
		.msg_controllen = 0,
		.msg_flags = MSG_DONTWAIT,
	पूर्ण;
	काष्ठा tun_msg_ctl ctl;
	माप_प्रकार len, total_len = 0;
	पूर्णांक err;
	काष्ठा vhost_net_ubuf_ref *ubufs;
	काष्ठा ubuf_info *ubuf;
	bool zcopy_used;
	पूर्णांक sent_pkts = 0;

	करो अणु
		bool busyloop_पूर्णांकr;

		/* Release DMAs करोne buffers first */
		vhost_zerocopy_संकेत_used(net, vq);

		busyloop_पूर्णांकr = false;
		head = get_tx_bufs(net, nvq, &msg, &out, &in, &len,
				   &busyloop_पूर्णांकr);
		/* On error, stop handling until the next kick. */
		अगर (unlikely(head < 0))
			अवरोध;
		/* Nothing new?  Wait क्रम eventfd to tell us they refilled. */
		अगर (head == vq->num) अणु
			अगर (unlikely(busyloop_पूर्णांकr)) अणु
				vhost_poll_queue(&vq->poll);
			पूर्ण अन्यथा अगर (unlikely(vhost_enable_notअगरy(&net->dev, vq))) अणु
				vhost_disable_notअगरy(&net->dev, vq);
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		zcopy_used = len >= VHOST_GOODCOPY_LEN
			     && !vhost_exceeds_maxpend(net)
			     && vhost_net_tx_select_zcopy(net);

		/* use msg_control to pass vhost zerocopy ubuf info to skb */
		अगर (zcopy_used) अणु
			ubuf = nvq->ubuf_info + nvq->upend_idx;
			vq->heads[nvq->upend_idx].id = cpu_to_vhost32(vq, head);
			vq->heads[nvq->upend_idx].len = VHOST_DMA_IN_PROGRESS;
			ubuf->callback = vhost_zerocopy_callback;
			ubuf->ctx = nvq->ubufs;
			ubuf->desc = nvq->upend_idx;
			ubuf->flags = SKBFL_ZEROCOPY_FRAG;
			refcount_set(&ubuf->refcnt, 1);
			msg.msg_control = &ctl;
			ctl.type = TUN_MSG_UBUF;
			ctl.ptr = ubuf;
			msg.msg_controllen = माप(ctl);
			ubufs = nvq->ubufs;
			atomic_inc(&ubufs->refcount);
			nvq->upend_idx = (nvq->upend_idx + 1) % UIO_MAXIOV;
		पूर्ण अन्यथा अणु
			msg.msg_control = शून्य;
			ubufs = शून्य;
		पूर्ण
		total_len += len;
		अगर (tx_can_batch(vq, total_len) &&
		    likely(!vhost_exceeds_maxpend(net))) अणु
			msg.msg_flags |= MSG_MORE;
		पूर्ण अन्यथा अणु
			msg.msg_flags &= ~MSG_MORE;
		पूर्ण

		err = sock->ops->sendmsg(sock, &msg, len);
		अगर (unlikely(err < 0)) अणु
			अगर (zcopy_used) अणु
				अगर (vq->heads[ubuf->desc].len == VHOST_DMA_IN_PROGRESS)
					vhost_net_ubuf_put(ubufs);
				nvq->upend_idx = ((अचिन्हित)nvq->upend_idx - 1)
					% UIO_MAXIOV;
			पूर्ण
			अगर (err == -EAGAIN || err == -ENOMEM || err == -ENOBUFS) अणु
				vhost_discard_vq_desc(vq, 1);
				vhost_net_enable_vq(net, vq);
				अवरोध;
			पूर्ण
			pr_debug("Fail to send packet: err %d", err);
		पूर्ण अन्यथा अगर (unlikely(err != len))
			pr_debug("Truncated TX packet: "
				 " len %d != %zd\n", err, len);
		अगर (!zcopy_used)
			vhost_add_used_and_संकेत(&net->dev, vq, head, 0);
		अन्यथा
			vhost_zerocopy_संकेत_used(net, vq);
		vhost_net_tx_packet(net);
	पूर्ण जबतक (likely(!vhost_exceeds_weight(vq, ++sent_pkts, total_len)));
पूर्ण

/* Expects to be always run from workqueue - which acts as
 * पढ़ो-size critical section क्रम our kind of RCU. */
अटल व्योम handle_tx(काष्ठा vhost_net *net)
अणु
	काष्ठा vhost_net_virtqueue *nvq = &net->vqs[VHOST_NET_VQ_TX];
	काष्ठा vhost_virtqueue *vq = &nvq->vq;
	काष्ठा socket *sock;

	mutex_lock_nested(&vq->mutex, VHOST_NET_VQ_TX);
	sock = vhost_vq_get_backend(vq);
	अगर (!sock)
		जाओ out;

	अगर (!vq_meta_prefetch(vq))
		जाओ out;

	vhost_disable_notअगरy(&net->dev, vq);
	vhost_net_disable_vq(net, vq);

	अगर (vhost_sock_zcopy(sock))
		handle_tx_zerocopy(net, sock);
	अन्यथा
		handle_tx_copy(net, sock);

out:
	mutex_unlock(&vq->mutex);
पूर्ण

अटल पूर्णांक peek_head_len(काष्ठा vhost_net_virtqueue *rvq, काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *head;
	पूर्णांक len = 0;
	अचिन्हित दीर्घ flags;

	अगर (rvq->rx_ring)
		वापस vhost_net_buf_peek(rvq);

	spin_lock_irqsave(&sk->sk_receive_queue.lock, flags);
	head = skb_peek(&sk->sk_receive_queue);
	अगर (likely(head)) अणु
		len = head->len;
		अगर (skb_vlan_tag_present(head))
			len += VLAN_HLEN;
	पूर्ण

	spin_unlock_irqrestore(&sk->sk_receive_queue.lock, flags);
	वापस len;
पूर्ण

अटल पूर्णांक vhost_net_rx_peek_head_len(काष्ठा vhost_net *net, काष्ठा sock *sk,
				      bool *busyloop_पूर्णांकr)
अणु
	काष्ठा vhost_net_virtqueue *rnvq = &net->vqs[VHOST_NET_VQ_RX];
	काष्ठा vhost_net_virtqueue *tnvq = &net->vqs[VHOST_NET_VQ_TX];
	काष्ठा vhost_virtqueue *rvq = &rnvq->vq;
	काष्ठा vhost_virtqueue *tvq = &tnvq->vq;
	पूर्णांक len = peek_head_len(rnvq, sk);

	अगर (!len && rvq->busyloop_समयout) अणु
		/* Flush batched heads first */
		vhost_net_संकेत_used(rnvq);
		/* Both tx vq and rx socket were polled here */
		vhost_net_busy_poll(net, rvq, tvq, busyloop_पूर्णांकr, true);

		len = peek_head_len(rnvq, sk);
	पूर्ण

	वापस len;
पूर्ण

/* This is a multi-buffer version of vhost_get_desc, that works अगर
 *	vq has पढ़ो descriptors only.
 * @vq		- the relevant virtqueue
 * @datalen	- data length we'll be पढ़ोing
 * @iovcount	- वापसed count of io vectors we fill
 * @log		- vhost log
 * @log_num	- log offset
 * @quota       - headcount quota, 1 क्रम big buffer
 *	वापसs number of buffer heads allocated, negative on error
 */
अटल पूर्णांक get_rx_bufs(काष्ठा vhost_virtqueue *vq,
		       काष्ठा vring_used_elem *heads,
		       पूर्णांक datalen,
		       अचिन्हित *iovcount,
		       काष्ठा vhost_log *log,
		       अचिन्हित *log_num,
		       अचिन्हित पूर्णांक quota)
अणु
	अचिन्हित पूर्णांक out, in;
	पूर्णांक seg = 0;
	पूर्णांक headcount = 0;
	अचिन्हित d;
	पूर्णांक r, nlogs = 0;
	/* len is always initialized beक्रमe use since we are always called with
	 * datalen > 0.
	 */
	u32 len;

	जबतक (datalen > 0 && headcount < quota) अणु
		अगर (unlikely(seg >= UIO_MAXIOV)) अणु
			r = -ENOBUFS;
			जाओ err;
		पूर्ण
		r = vhost_get_vq_desc(vq, vq->iov + seg,
				      ARRAY_SIZE(vq->iov) - seg, &out,
				      &in, log, log_num);
		अगर (unlikely(r < 0))
			जाओ err;

		d = r;
		अगर (d == vq->num) अणु
			r = 0;
			जाओ err;
		पूर्ण
		अगर (unlikely(out || in <= 0)) अणु
			vq_err(vq, "unexpected descriptor format for RX: "
				"out %d, in %d\n", out, in);
			r = -EINVAL;
			जाओ err;
		पूर्ण
		अगर (unlikely(log)) अणु
			nlogs += *log_num;
			log += *log_num;
		पूर्ण
		heads[headcount].id = cpu_to_vhost32(vq, d);
		len = iov_length(vq->iov + seg, in);
		heads[headcount].len = cpu_to_vhost32(vq, len);
		datalen -= len;
		++headcount;
		seg += in;
	पूर्ण
	heads[headcount - 1].len = cpu_to_vhost32(vq, len + datalen);
	*iovcount = seg;
	अगर (unlikely(log))
		*log_num = nlogs;

	/* Detect overrun */
	अगर (unlikely(datalen > 0)) अणु
		r = UIO_MAXIOV + 1;
		जाओ err;
	पूर्ण
	वापस headcount;
err:
	vhost_discard_vq_desc(vq, headcount);
	वापस r;
पूर्ण

/* Expects to be always run from workqueue - which acts as
 * पढ़ो-size critical section क्रम our kind of RCU. */
अटल व्योम handle_rx(काष्ठा vhost_net *net)
अणु
	काष्ठा vhost_net_virtqueue *nvq = &net->vqs[VHOST_NET_VQ_RX];
	काष्ठा vhost_virtqueue *vq = &nvq->vq;
	अचिन्हित in, log;
	काष्ठा vhost_log *vq_log;
	काष्ठा msghdr msg = अणु
		.msg_name = शून्य,
		.msg_namelen = 0,
		.msg_control = शून्य, /* FIXME: get and handle RX aux data. */
		.msg_controllen = 0,
		.msg_flags = MSG_DONTWAIT,
	पूर्ण;
	काष्ठा virtio_net_hdr hdr = अणु
		.flags = 0,
		.gso_type = VIRTIO_NET_HDR_GSO_NONE
	पूर्ण;
	माप_प्रकार total_len = 0;
	पूर्णांक err, mergeable;
	s16 headcount;
	माप_प्रकार vhost_hlen, sock_hlen;
	माप_प्रकार vhost_len, sock_len;
	bool busyloop_पूर्णांकr = false;
	काष्ठा socket *sock;
	काष्ठा iov_iter fixup;
	__virtio16 num_buffers;
	पूर्णांक recv_pkts = 0;

	mutex_lock_nested(&vq->mutex, VHOST_NET_VQ_RX);
	sock = vhost_vq_get_backend(vq);
	अगर (!sock)
		जाओ out;

	अगर (!vq_meta_prefetch(vq))
		जाओ out;

	vhost_disable_notअगरy(&net->dev, vq);
	vhost_net_disable_vq(net, vq);

	vhost_hlen = nvq->vhost_hlen;
	sock_hlen = nvq->sock_hlen;

	vq_log = unlikely(vhost_has_feature(vq, VHOST_F_LOG_ALL)) ?
		vq->log : शून्य;
	mergeable = vhost_has_feature(vq, VIRTIO_NET_F_MRG_RXBUF);

	करो अणु
		sock_len = vhost_net_rx_peek_head_len(net, sock->sk,
						      &busyloop_पूर्णांकr);
		अगर (!sock_len)
			अवरोध;
		sock_len += sock_hlen;
		vhost_len = sock_len + vhost_hlen;
		headcount = get_rx_bufs(vq, vq->heads + nvq->करोne_idx,
					vhost_len, &in, vq_log, &log,
					likely(mergeable) ? UIO_MAXIOV : 1);
		/* On error, stop handling until the next kick. */
		अगर (unlikely(headcount < 0))
			जाओ out;
		/* OK, now we need to know about added descriptors. */
		अगर (!headcount) अणु
			अगर (unlikely(busyloop_पूर्णांकr)) अणु
				vhost_poll_queue(&vq->poll);
			पूर्ण अन्यथा अगर (unlikely(vhost_enable_notअगरy(&net->dev, vq))) अणु
				/* They have slipped one in as we were
				 * करोing that: check again. */
				vhost_disable_notअगरy(&net->dev, vq);
				जारी;
			पूर्ण
			/* Nothing new?  Wait क्रम eventfd to tell us
			 * they refilled. */
			जाओ out;
		पूर्ण
		busyloop_पूर्णांकr = false;
		अगर (nvq->rx_ring)
			msg.msg_control = vhost_net_buf_consume(&nvq->rxq);
		/* On overrun, truncate and discard */
		अगर (unlikely(headcount > UIO_MAXIOV)) अणु
			iov_iter_init(&msg.msg_iter, READ, vq->iov, 1, 1);
			err = sock->ops->recvmsg(sock, &msg,
						 1, MSG_DONTWAIT | MSG_TRUNC);
			pr_debug("Discarded rx packet: len %zd\n", sock_len);
			जारी;
		पूर्ण
		/* We करोn't need to be notअगरied again. */
		iov_iter_init(&msg.msg_iter, READ, vq->iov, in, vhost_len);
		fixup = msg.msg_iter;
		अगर (unlikely((vhost_hlen))) अणु
			/* We will supply the header ourselves
			 * TODO: support TSO.
			 */
			iov_iter_advance(&msg.msg_iter, vhost_hlen);
		पूर्ण
		err = sock->ops->recvmsg(sock, &msg,
					 sock_len, MSG_DONTWAIT | MSG_TRUNC);
		/* Userspace might have consumed the packet meanजबतक:
		 * it's not supposed to करो this usually, but might be hard
		 * to prevent. Discard data we got (अगर any) and keep going. */
		अगर (unlikely(err != sock_len)) अणु
			pr_debug("Discarded rx packet: "
				 " len %d, expected %zd\n", err, sock_len);
			vhost_discard_vq_desc(vq, headcount);
			जारी;
		पूर्ण
		/* Supply virtio_net_hdr अगर VHOST_NET_F_VIRTIO_NET_HDR */
		अगर (unlikely(vhost_hlen)) अणु
			अगर (copy_to_iter(&hdr, माप(hdr),
					 &fixup) != माप(hdr)) अणु
				vq_err(vq, "Unable to write vnet_hdr "
				       "at addr %p\n", vq->iov->iov_base);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Header came from socket; we'll need to patch
			 * ->num_buffers over अगर VIRTIO_NET_F_MRG_RXBUF
			 */
			iov_iter_advance(&fixup, माप(hdr));
		पूर्ण
		/* TODO: Should check and handle checksum. */

		num_buffers = cpu_to_vhost16(vq, headcount);
		अगर (likely(mergeable) &&
		    copy_to_iter(&num_buffers, माप num_buffers,
				 &fixup) != माप num_buffers) अणु
			vq_err(vq, "Failed num_buffers write");
			vhost_discard_vq_desc(vq, headcount);
			जाओ out;
		पूर्ण
		nvq->करोne_idx += headcount;
		अगर (nvq->करोne_idx > VHOST_NET_BATCH)
			vhost_net_संकेत_used(nvq);
		अगर (unlikely(vq_log))
			vhost_log_ग_लिखो(vq, vq_log, log, vhost_len,
					vq->iov, in);
		total_len += vhost_len;
	पूर्ण जबतक (likely(!vhost_exceeds_weight(vq, ++recv_pkts, total_len)));

	अगर (unlikely(busyloop_पूर्णांकr))
		vhost_poll_queue(&vq->poll);
	अन्यथा अगर (!sock_len)
		vhost_net_enable_vq(net, vq);
out:
	vhost_net_संकेत_used(nvq);
	mutex_unlock(&vq->mutex);
पूर्ण

अटल व्योम handle_tx_kick(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_virtqueue *vq = container_of(work, काष्ठा vhost_virtqueue,
						  poll.work);
	काष्ठा vhost_net *net = container_of(vq->dev, काष्ठा vhost_net, dev);

	handle_tx(net);
पूर्ण

अटल व्योम handle_rx_kick(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_virtqueue *vq = container_of(work, काष्ठा vhost_virtqueue,
						  poll.work);
	काष्ठा vhost_net *net = container_of(vq->dev, काष्ठा vhost_net, dev);

	handle_rx(net);
पूर्ण

अटल व्योम handle_tx_net(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_net *net = container_of(work, काष्ठा vhost_net,
					     poll[VHOST_NET_VQ_TX].work);
	handle_tx(net);
पूर्ण

अटल व्योम handle_rx_net(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_net *net = container_of(work, काष्ठा vhost_net,
					     poll[VHOST_NET_VQ_RX].work);
	handle_rx(net);
पूर्ण

अटल पूर्णांक vhost_net_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा vhost_net *n;
	काष्ठा vhost_dev *dev;
	काष्ठा vhost_virtqueue **vqs;
	व्योम **queue;
	काष्ठा xdp_buff *xdp;
	पूर्णांक i;

	n = kvदो_स्मृति(माप *n, GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	अगर (!n)
		वापस -ENOMEM;
	vqs = kदो_स्मृति_array(VHOST_NET_VQ_MAX, माप(*vqs), GFP_KERNEL);
	अगर (!vqs) अणु
		kvमुक्त(n);
		वापस -ENOMEM;
	पूर्ण

	queue = kदो_स्मृति_array(VHOST_NET_BATCH, माप(व्योम *),
			      GFP_KERNEL);
	अगर (!queue) अणु
		kमुक्त(vqs);
		kvमुक्त(n);
		वापस -ENOMEM;
	पूर्ण
	n->vqs[VHOST_NET_VQ_RX].rxq.queue = queue;

	xdp = kदो_स्मृति_array(VHOST_NET_BATCH, माप(*xdp), GFP_KERNEL);
	अगर (!xdp) अणु
		kमुक्त(vqs);
		kvमुक्त(n);
		kमुक्त(queue);
		वापस -ENOMEM;
	पूर्ण
	n->vqs[VHOST_NET_VQ_TX].xdp = xdp;

	dev = &n->dev;
	vqs[VHOST_NET_VQ_TX] = &n->vqs[VHOST_NET_VQ_TX].vq;
	vqs[VHOST_NET_VQ_RX] = &n->vqs[VHOST_NET_VQ_RX].vq;
	n->vqs[VHOST_NET_VQ_TX].vq.handle_kick = handle_tx_kick;
	n->vqs[VHOST_NET_VQ_RX].vq.handle_kick = handle_rx_kick;
	क्रम (i = 0; i < VHOST_NET_VQ_MAX; i++) अणु
		n->vqs[i].ubufs = शून्य;
		n->vqs[i].ubuf_info = शून्य;
		n->vqs[i].upend_idx = 0;
		n->vqs[i].करोne_idx = 0;
		n->vqs[i].batched_xdp = 0;
		n->vqs[i].vhost_hlen = 0;
		n->vqs[i].sock_hlen = 0;
		n->vqs[i].rx_ring = शून्य;
		vhost_net_buf_init(&n->vqs[i].rxq);
	पूर्ण
	vhost_dev_init(dev, vqs, VHOST_NET_VQ_MAX,
		       UIO_MAXIOV + VHOST_NET_BATCH,
		       VHOST_NET_PKT_WEIGHT, VHOST_NET_WEIGHT, true,
		       शून्य);

	vhost_poll_init(n->poll + VHOST_NET_VQ_TX, handle_tx_net, EPOLLOUT, dev);
	vhost_poll_init(n->poll + VHOST_NET_VQ_RX, handle_rx_net, EPOLLIN, dev);

	f->निजी_data = n;
	n->page_frag.page = शून्य;
	n->refcnt_bias = 0;

	वापस 0;
पूर्ण

अटल काष्ठा socket *vhost_net_stop_vq(काष्ठा vhost_net *n,
					काष्ठा vhost_virtqueue *vq)
अणु
	काष्ठा socket *sock;
	काष्ठा vhost_net_virtqueue *nvq =
		container_of(vq, काष्ठा vhost_net_virtqueue, vq);

	mutex_lock(&vq->mutex);
	sock = vhost_vq_get_backend(vq);
	vhost_net_disable_vq(n, vq);
	vhost_vq_set_backend(vq, शून्य);
	vhost_net_buf_unproduce(nvq);
	nvq->rx_ring = शून्य;
	mutex_unlock(&vq->mutex);
	वापस sock;
पूर्ण

अटल व्योम vhost_net_stop(काष्ठा vhost_net *n, काष्ठा socket **tx_sock,
			   काष्ठा socket **rx_sock)
अणु
	*tx_sock = vhost_net_stop_vq(n, &n->vqs[VHOST_NET_VQ_TX].vq);
	*rx_sock = vhost_net_stop_vq(n, &n->vqs[VHOST_NET_VQ_RX].vq);
पूर्ण

अटल व्योम vhost_net_flush_vq(काष्ठा vhost_net *n, पूर्णांक index)
अणु
	vhost_poll_flush(n->poll + index);
	vhost_poll_flush(&n->vqs[index].vq.poll);
पूर्ण

अटल व्योम vhost_net_flush(काष्ठा vhost_net *n)
अणु
	vhost_net_flush_vq(n, VHOST_NET_VQ_TX);
	vhost_net_flush_vq(n, VHOST_NET_VQ_RX);
	अगर (n->vqs[VHOST_NET_VQ_TX].ubufs) अणु
		mutex_lock(&n->vqs[VHOST_NET_VQ_TX].vq.mutex);
		n->tx_flush = true;
		mutex_unlock(&n->vqs[VHOST_NET_VQ_TX].vq.mutex);
		/* Wait क्रम all lower device DMAs करोne. */
		vhost_net_ubuf_put_and_रुको(n->vqs[VHOST_NET_VQ_TX].ubufs);
		mutex_lock(&n->vqs[VHOST_NET_VQ_TX].vq.mutex);
		n->tx_flush = false;
		atomic_set(&n->vqs[VHOST_NET_VQ_TX].ubufs->refcount, 1);
		mutex_unlock(&n->vqs[VHOST_NET_VQ_TX].vq.mutex);
	पूर्ण
पूर्ण

अटल पूर्णांक vhost_net_release(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा vhost_net *n = f->निजी_data;
	काष्ठा socket *tx_sock;
	काष्ठा socket *rx_sock;

	vhost_net_stop(n, &tx_sock, &rx_sock);
	vhost_net_flush(n);
	vhost_dev_stop(&n->dev);
	vhost_dev_cleanup(&n->dev);
	vhost_net_vq_reset(n);
	अगर (tx_sock)
		sockfd_put(tx_sock);
	अगर (rx_sock)
		sockfd_put(rx_sock);
	/* Make sure no callbacks are outstanding */
	synchronize_rcu();
	/* We करो an extra flush beक्रमe मुक्तing memory,
	 * since jobs can re-queue themselves. */
	vhost_net_flush(n);
	kमुक्त(n->vqs[VHOST_NET_VQ_RX].rxq.queue);
	kमुक्त(n->vqs[VHOST_NET_VQ_TX].xdp);
	kमुक्त(n->dev.vqs);
	अगर (n->page_frag.page)
		__page_frag_cache_drain(n->page_frag.page, n->refcnt_bias);
	kvमुक्त(n);
	वापस 0;
पूर्ण

अटल काष्ठा socket *get_raw_socket(पूर्णांक fd)
अणु
	पूर्णांक r;
	काष्ठा socket *sock = sockfd_lookup(fd, &r);

	अगर (!sock)
		वापस ERR_PTR(-ENOTSOCK);

	/* Parameter checking */
	अगर (sock->sk->sk_type != SOCK_RAW) अणु
		r = -ESOCKTNOSUPPORT;
		जाओ err;
	पूर्ण

	अगर (sock->sk->sk_family != AF_PACKET) अणु
		r = -EPFNOSUPPORT;
		जाओ err;
	पूर्ण
	वापस sock;
err:
	sockfd_put(sock);
	वापस ERR_PTR(r);
पूर्ण

अटल काष्ठा ptr_ring *get_tap_ptr_ring(पूर्णांक fd)
अणु
	काष्ठा ptr_ring *ring;
	काष्ठा file *file = fget(fd);

	अगर (!file)
		वापस शून्य;
	ring = tun_get_tx_ring(file);
	अगर (!IS_ERR(ring))
		जाओ out;
	ring = tap_get_ptr_ring(file);
	अगर (!IS_ERR(ring))
		जाओ out;
	ring = शून्य;
out:
	fput(file);
	वापस ring;
पूर्ण

अटल काष्ठा socket *get_tap_socket(पूर्णांक fd)
अणु
	काष्ठा file *file = fget(fd);
	काष्ठा socket *sock;

	अगर (!file)
		वापस ERR_PTR(-EBADF);
	sock = tun_get_socket(file);
	अगर (!IS_ERR(sock))
		वापस sock;
	sock = tap_get_socket(file);
	अगर (IS_ERR(sock))
		fput(file);
	वापस sock;
पूर्ण

अटल काष्ठा socket *get_socket(पूर्णांक fd)
अणु
	काष्ठा socket *sock;

	/* special हाल to disable backend */
	अगर (fd == -1)
		वापस शून्य;
	sock = get_raw_socket(fd);
	अगर (!IS_ERR(sock))
		वापस sock;
	sock = get_tap_socket(fd);
	अगर (!IS_ERR(sock))
		वापस sock;
	वापस ERR_PTR(-ENOTSOCK);
पूर्ण

अटल दीर्घ vhost_net_set_backend(काष्ठा vhost_net *n, अचिन्हित index, पूर्णांक fd)
अणु
	काष्ठा socket *sock, *oldsock;
	काष्ठा vhost_virtqueue *vq;
	काष्ठा vhost_net_virtqueue *nvq;
	काष्ठा vhost_net_ubuf_ref *ubufs, *oldubufs = शून्य;
	पूर्णांक r;

	mutex_lock(&n->dev.mutex);
	r = vhost_dev_check_owner(&n->dev);
	अगर (r)
		जाओ err;

	अगर (index >= VHOST_NET_VQ_MAX) अणु
		r = -ENOBUFS;
		जाओ err;
	पूर्ण
	vq = &n->vqs[index].vq;
	nvq = &n->vqs[index];
	mutex_lock(&vq->mutex);

	/* Verअगरy that ring has been setup correctly. */
	अगर (!vhost_vq_access_ok(vq)) अणु
		r = -EFAULT;
		जाओ err_vq;
	पूर्ण
	sock = get_socket(fd);
	अगर (IS_ERR(sock)) अणु
		r = PTR_ERR(sock);
		जाओ err_vq;
	पूर्ण

	/* start polling new socket */
	oldsock = vhost_vq_get_backend(vq);
	अगर (sock != oldsock) अणु
		ubufs = vhost_net_ubuf_alloc(vq,
					     sock && vhost_sock_zcopy(sock));
		अगर (IS_ERR(ubufs)) अणु
			r = PTR_ERR(ubufs);
			जाओ err_ubufs;
		पूर्ण

		vhost_net_disable_vq(n, vq);
		vhost_vq_set_backend(vq, sock);
		vhost_net_buf_unproduce(nvq);
		r = vhost_vq_init_access(vq);
		अगर (r)
			जाओ err_used;
		r = vhost_net_enable_vq(n, vq);
		अगर (r)
			जाओ err_used;
		अगर (index == VHOST_NET_VQ_RX)
			nvq->rx_ring = get_tap_ptr_ring(fd);

		oldubufs = nvq->ubufs;
		nvq->ubufs = ubufs;

		n->tx_packets = 0;
		n->tx_zcopy_err = 0;
		n->tx_flush = false;
	पूर्ण

	mutex_unlock(&vq->mutex);

	अगर (oldubufs) अणु
		vhost_net_ubuf_put_रुको_and_मुक्त(oldubufs);
		mutex_lock(&vq->mutex);
		vhost_zerocopy_संकेत_used(n, vq);
		mutex_unlock(&vq->mutex);
	पूर्ण

	अगर (oldsock) अणु
		vhost_net_flush_vq(n, index);
		sockfd_put(oldsock);
	पूर्ण

	mutex_unlock(&n->dev.mutex);
	वापस 0;

err_used:
	vhost_vq_set_backend(vq, oldsock);
	vhost_net_enable_vq(n, vq);
	अगर (ubufs)
		vhost_net_ubuf_put_रुको_and_मुक्त(ubufs);
err_ubufs:
	अगर (sock)
		sockfd_put(sock);
err_vq:
	mutex_unlock(&vq->mutex);
err:
	mutex_unlock(&n->dev.mutex);
	वापस r;
पूर्ण

अटल दीर्घ vhost_net_reset_owner(काष्ठा vhost_net *n)
अणु
	काष्ठा socket *tx_sock = शून्य;
	काष्ठा socket *rx_sock = शून्य;
	दीर्घ err;
	काष्ठा vhost_iotlb *umem;

	mutex_lock(&n->dev.mutex);
	err = vhost_dev_check_owner(&n->dev);
	अगर (err)
		जाओ करोne;
	umem = vhost_dev_reset_owner_prepare();
	अगर (!umem) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण
	vhost_net_stop(n, &tx_sock, &rx_sock);
	vhost_net_flush(n);
	vhost_dev_stop(&n->dev);
	vhost_dev_reset_owner(&n->dev, umem);
	vhost_net_vq_reset(n);
करोne:
	mutex_unlock(&n->dev.mutex);
	अगर (tx_sock)
		sockfd_put(tx_sock);
	अगर (rx_sock)
		sockfd_put(rx_sock);
	वापस err;
पूर्ण

अटल पूर्णांक vhost_net_set_features(काष्ठा vhost_net *n, u64 features)
अणु
	माप_प्रकार vhost_hlen, sock_hlen, hdr_len;
	पूर्णांक i;

	hdr_len = (features & ((1ULL << VIRTIO_NET_F_MRG_RXBUF) |
			       (1ULL << VIRTIO_F_VERSION_1))) ?
			माप(काष्ठा virtio_net_hdr_mrg_rxbuf) :
			माप(काष्ठा virtio_net_hdr);
	अगर (features & (1 << VHOST_NET_F_VIRTIO_NET_HDR)) अणु
		/* vhost provides vnet_hdr */
		vhost_hlen = hdr_len;
		sock_hlen = 0;
	पूर्ण अन्यथा अणु
		/* socket provides vnet_hdr */
		vhost_hlen = 0;
		sock_hlen = hdr_len;
	पूर्ण
	mutex_lock(&n->dev.mutex);
	अगर ((features & (1 << VHOST_F_LOG_ALL)) &&
	    !vhost_log_access_ok(&n->dev))
		जाओ out_unlock;

	अगर ((features & (1ULL << VIRTIO_F_ACCESS_PLATFORM))) अणु
		अगर (vhost_init_device_iotlb(&n->dev, true))
			जाओ out_unlock;
	पूर्ण

	क्रम (i = 0; i < VHOST_NET_VQ_MAX; ++i) अणु
		mutex_lock(&n->vqs[i].vq.mutex);
		n->vqs[i].vq.acked_features = features;
		n->vqs[i].vhost_hlen = vhost_hlen;
		n->vqs[i].sock_hlen = sock_hlen;
		mutex_unlock(&n->vqs[i].vq.mutex);
	पूर्ण
	mutex_unlock(&n->dev.mutex);
	वापस 0;

out_unlock:
	mutex_unlock(&n->dev.mutex);
	वापस -EFAULT;
पूर्ण

अटल दीर्घ vhost_net_set_owner(काष्ठा vhost_net *n)
अणु
	पूर्णांक r;

	mutex_lock(&n->dev.mutex);
	अगर (vhost_dev_has_owner(&n->dev)) अणु
		r = -EBUSY;
		जाओ out;
	पूर्ण
	r = vhost_net_set_ubuf_info(n);
	अगर (r)
		जाओ out;
	r = vhost_dev_set_owner(&n->dev);
	अगर (r)
		vhost_net_clear_ubuf_info(n);
	vhost_net_flush(n);
out:
	mutex_unlock(&n->dev.mutex);
	वापस r;
पूर्ण

अटल दीर्घ vhost_net_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक ioctl,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा vhost_net *n = f->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	u64 __user *featurep = argp;
	काष्ठा vhost_vring_file backend;
	u64 features;
	पूर्णांक r;

	चयन (ioctl) अणु
	हाल VHOST_NET_SET_BACKEND:
		अगर (copy_from_user(&backend, argp, माप backend))
			वापस -EFAULT;
		वापस vhost_net_set_backend(n, backend.index, backend.fd);
	हाल VHOST_GET_FEATURES:
		features = VHOST_NET_FEATURES;
		अगर (copy_to_user(featurep, &features, माप features))
			वापस -EFAULT;
		वापस 0;
	हाल VHOST_SET_FEATURES:
		अगर (copy_from_user(&features, featurep, माप features))
			वापस -EFAULT;
		अगर (features & ~VHOST_NET_FEATURES)
			वापस -EOPNOTSUPP;
		वापस vhost_net_set_features(n, features);
	हाल VHOST_GET_BACKEND_FEATURES:
		features = VHOST_NET_BACKEND_FEATURES;
		अगर (copy_to_user(featurep, &features, माप(features)))
			वापस -EFAULT;
		वापस 0;
	हाल VHOST_SET_BACKEND_FEATURES:
		अगर (copy_from_user(&features, featurep, माप(features)))
			वापस -EFAULT;
		अगर (features & ~VHOST_NET_BACKEND_FEATURES)
			वापस -EOPNOTSUPP;
		vhost_set_backend_features(&n->dev, features);
		वापस 0;
	हाल VHOST_RESET_OWNER:
		वापस vhost_net_reset_owner(n);
	हाल VHOST_SET_OWNER:
		वापस vhost_net_set_owner(n);
	शेष:
		mutex_lock(&n->dev.mutex);
		r = vhost_dev_ioctl(&n->dev, ioctl, argp);
		अगर (r == -ENOIOCTLCMD)
			r = vhost_vring_ioctl(&n->dev, ioctl, argp);
		अन्यथा
			vhost_net_flush(n);
		mutex_unlock(&n->dev.mutex);
		वापस r;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार vhost_net_chr_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा vhost_net *n = file->निजी_data;
	काष्ठा vhost_dev *dev = &n->dev;
	पूर्णांक noblock = file->f_flags & O_NONBLOCK;

	वापस vhost_chr_पढ़ो_iter(dev, to, noblock);
पूर्ण

अटल sमाप_प्रकार vhost_net_chr_ग_लिखो_iter(काष्ठा kiocb *iocb,
					काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा vhost_net *n = file->निजी_data;
	काष्ठा vhost_dev *dev = &n->dev;

	वापस vhost_chr_ग_लिखो_iter(dev, from);
पूर्ण

अटल __poll_t vhost_net_chr_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा vhost_net *n = file->निजी_data;
	काष्ठा vhost_dev *dev = &n->dev;

	वापस vhost_chr_poll(file, dev, रुको);
पूर्ण

अटल स्थिर काष्ठा file_operations vhost_net_fops = अणु
	.owner          = THIS_MODULE,
	.release        = vhost_net_release,
	.पढ़ो_iter      = vhost_net_chr_पढ़ो_iter,
	.ग_लिखो_iter     = vhost_net_chr_ग_लिखो_iter,
	.poll           = vhost_net_chr_poll,
	.unlocked_ioctl = vhost_net_ioctl,
	.compat_ioctl   = compat_ptr_ioctl,
	.खोलो           = vhost_net_खोलो,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice vhost_net_misc = अणु
	.minor = VHOST_NET_MINOR,
	.name = "vhost-net",
	.fops = &vhost_net_fops,
पूर्ण;

अटल पूर्णांक vhost_net_init(व्योम)
अणु
	अगर (experimental_zcopytx)
		vhost_net_enable_zcopy(VHOST_NET_VQ_TX);
	वापस misc_रेजिस्टर(&vhost_net_misc);
पूर्ण
module_init(vhost_net_init);

अटल व्योम vhost_net_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&vhost_net_misc);
पूर्ण
module_निकास(vhost_net_निकास);

MODULE_VERSION("0.0.1");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Michael S. Tsirkin");
MODULE_DESCRIPTION("Host kernel accelerator for virtio net");
MODULE_ALIAS_MISCDEV(VHOST_NET_MINOR);
MODULE_ALIAS("devname:vhost-net");
