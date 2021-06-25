<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * virtio transport क्रम vsock
 *
 * Copyright (C) 2013-2015 Red Hat, Inc.
 * Author: Asias He <asias@redhat.com>
 *         Stefan Hajnoczi <stefanha@redhat.com>
 *
 * Some of the code is take from Gerd Hoffmann <kraxel@redhat.com>'s
 * early virtio-vsock proof-of-concept bits.
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/atomic.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_vsock.h>
#समावेश <net/sock.h>
#समावेश <linux/mutex.h>
#समावेश <net/af_vsock.h>

अटल काष्ठा workqueue_काष्ठा *virtio_vsock_workqueue;
अटल काष्ठा virtio_vsock __rcu *the_virtio_vsock;
अटल DEFINE_MUTEX(the_virtio_vsock_mutex); /* protects the_virtio_vsock */

काष्ठा virtio_vsock अणु
	काष्ठा virtio_device *vdev;
	काष्ठा virtqueue *vqs[VSOCK_VQ_MAX];

	/* Virtqueue processing is deferred to a workqueue */
	काष्ठा work_काष्ठा tx_work;
	काष्ठा work_काष्ठा rx_work;
	काष्ठा work_काष्ठा event_work;

	/* The following fields are रक्षित by tx_lock.  vqs[VSOCK_VQ_TX]
	 * must be accessed with tx_lock held.
	 */
	काष्ठा mutex tx_lock;
	bool tx_run;

	काष्ठा work_काष्ठा send_pkt_work;
	spinlock_t send_pkt_list_lock;
	काष्ठा list_head send_pkt_list;

	atomic_t queued_replies;

	/* The following fields are रक्षित by rx_lock.  vqs[VSOCK_VQ_RX]
	 * must be accessed with rx_lock held.
	 */
	काष्ठा mutex rx_lock;
	bool rx_run;
	पूर्णांक rx_buf_nr;
	पूर्णांक rx_buf_max_nr;

	/* The following fields are रक्षित by event_lock.
	 * vqs[VSOCK_VQ_EVENT] must be accessed with event_lock held.
	 */
	काष्ठा mutex event_lock;
	bool event_run;
	काष्ठा virtio_vsock_event event_list[8];

	u32 guest_cid;
पूर्ण;

अटल u32 virtio_transport_get_local_cid(व्योम)
अणु
	काष्ठा virtio_vsock *vsock;
	u32 ret;

	rcu_पढ़ो_lock();
	vsock = rcu_dereference(the_virtio_vsock);
	अगर (!vsock) अणु
		ret = VMADDR_CID_ANY;
		जाओ out_rcu;
	पूर्ण

	ret = vsock->guest_cid;
out_rcu:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल व्योम
virtio_transport_send_pkt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_vsock *vsock =
		container_of(work, काष्ठा virtio_vsock, send_pkt_work);
	काष्ठा virtqueue *vq;
	bool added = false;
	bool restart_rx = false;

	mutex_lock(&vsock->tx_lock);

	अगर (!vsock->tx_run)
		जाओ out;

	vq = vsock->vqs[VSOCK_VQ_TX];

	क्रम (;;) अणु
		काष्ठा virtio_vsock_pkt *pkt;
		काष्ठा scatterlist hdr, buf, *sgs[2];
		पूर्णांक ret, in_sg = 0, out_sg = 0;
		bool reply;

		spin_lock_bh(&vsock->send_pkt_list_lock);
		अगर (list_empty(&vsock->send_pkt_list)) अणु
			spin_unlock_bh(&vsock->send_pkt_list_lock);
			अवरोध;
		पूर्ण

		pkt = list_first_entry(&vsock->send_pkt_list,
				       काष्ठा virtio_vsock_pkt, list);
		list_del_init(&pkt->list);
		spin_unlock_bh(&vsock->send_pkt_list_lock);

		virtio_transport_deliver_tap_pkt(pkt);

		reply = pkt->reply;

		sg_init_one(&hdr, &pkt->hdr, माप(pkt->hdr));
		sgs[out_sg++] = &hdr;
		अगर (pkt->buf) अणु
			sg_init_one(&buf, pkt->buf, pkt->len);
			sgs[out_sg++] = &buf;
		पूर्ण

		ret = virtqueue_add_sgs(vq, sgs, out_sg, in_sg, pkt, GFP_KERNEL);
		/* Usually this means that there is no more space available in
		 * the vq
		 */
		अगर (ret < 0) अणु
			spin_lock_bh(&vsock->send_pkt_list_lock);
			list_add(&pkt->list, &vsock->send_pkt_list);
			spin_unlock_bh(&vsock->send_pkt_list_lock);
			अवरोध;
		पूर्ण

		अगर (reply) अणु
			काष्ठा virtqueue *rx_vq = vsock->vqs[VSOCK_VQ_RX];
			पूर्णांक val;

			val = atomic_dec_वापस(&vsock->queued_replies);

			/* Do we now have resources to resume rx processing? */
			अगर (val + 1 == virtqueue_get_vring_size(rx_vq))
				restart_rx = true;
		पूर्ण

		added = true;
	पूर्ण

	अगर (added)
		virtqueue_kick(vq);

out:
	mutex_unlock(&vsock->tx_lock);

	अगर (restart_rx)
		queue_work(virtio_vsock_workqueue, &vsock->rx_work);
पूर्ण

अटल पूर्णांक
virtio_transport_send_pkt(काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा virtio_vsock *vsock;
	पूर्णांक len = pkt->len;

	rcu_पढ़ो_lock();
	vsock = rcu_dereference(the_virtio_vsock);
	अगर (!vsock) अणु
		virtio_transport_मुक्त_pkt(pkt);
		len = -ENODEV;
		जाओ out_rcu;
	पूर्ण

	अगर (le64_to_cpu(pkt->hdr.dst_cid) == vsock->guest_cid) अणु
		virtio_transport_मुक्त_pkt(pkt);
		len = -ENODEV;
		जाओ out_rcu;
	पूर्ण

	अगर (pkt->reply)
		atomic_inc(&vsock->queued_replies);

	spin_lock_bh(&vsock->send_pkt_list_lock);
	list_add_tail(&pkt->list, &vsock->send_pkt_list);
	spin_unlock_bh(&vsock->send_pkt_list_lock);

	queue_work(virtio_vsock_workqueue, &vsock->send_pkt_work);

out_rcu:
	rcu_पढ़ो_unlock();
	वापस len;
पूर्ण

अटल पूर्णांक
virtio_transport_cancel_pkt(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा virtio_vsock *vsock;
	काष्ठा virtio_vsock_pkt *pkt, *n;
	पूर्णांक cnt = 0, ret;
	LIST_HEAD(मुक्तme);

	rcu_पढ़ो_lock();
	vsock = rcu_dereference(the_virtio_vsock);
	अगर (!vsock) अणु
		ret = -ENODEV;
		जाओ out_rcu;
	पूर्ण

	spin_lock_bh(&vsock->send_pkt_list_lock);
	list_क्रम_each_entry_safe(pkt, n, &vsock->send_pkt_list, list) अणु
		अगर (pkt->vsk != vsk)
			जारी;
		list_move(&pkt->list, &मुक्तme);
	पूर्ण
	spin_unlock_bh(&vsock->send_pkt_list_lock);

	list_क्रम_each_entry_safe(pkt, n, &मुक्तme, list) अणु
		अगर (pkt->reply)
			cnt++;
		list_del(&pkt->list);
		virtio_transport_मुक्त_pkt(pkt);
	पूर्ण

	अगर (cnt) अणु
		काष्ठा virtqueue *rx_vq = vsock->vqs[VSOCK_VQ_RX];
		पूर्णांक new_cnt;

		new_cnt = atomic_sub_वापस(cnt, &vsock->queued_replies);
		अगर (new_cnt + cnt >= virtqueue_get_vring_size(rx_vq) &&
		    new_cnt < virtqueue_get_vring_size(rx_vq))
			queue_work(virtio_vsock_workqueue, &vsock->rx_work);
	पूर्ण

	ret = 0;

out_rcu:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल व्योम virtio_vsock_rx_fill(काष्ठा virtio_vsock *vsock)
अणु
	पूर्णांक buf_len = VIRTIO_VSOCK_DEFAULT_RX_BUF_SIZE;
	काष्ठा virtio_vsock_pkt *pkt;
	काष्ठा scatterlist hdr, buf, *sgs[2];
	काष्ठा virtqueue *vq;
	पूर्णांक ret;

	vq = vsock->vqs[VSOCK_VQ_RX];

	करो अणु
		pkt = kzalloc(माप(*pkt), GFP_KERNEL);
		अगर (!pkt)
			अवरोध;

		pkt->buf = kदो_स्मृति(buf_len, GFP_KERNEL);
		अगर (!pkt->buf) अणु
			virtio_transport_मुक्त_pkt(pkt);
			अवरोध;
		पूर्ण

		pkt->buf_len = buf_len;
		pkt->len = buf_len;

		sg_init_one(&hdr, &pkt->hdr, माप(pkt->hdr));
		sgs[0] = &hdr;

		sg_init_one(&buf, pkt->buf, buf_len);
		sgs[1] = &buf;
		ret = virtqueue_add_sgs(vq, sgs, 0, 2, pkt, GFP_KERNEL);
		अगर (ret) अणु
			virtio_transport_मुक्त_pkt(pkt);
			अवरोध;
		पूर्ण
		vsock->rx_buf_nr++;
	पूर्ण जबतक (vq->num_मुक्त);
	अगर (vsock->rx_buf_nr > vsock->rx_buf_max_nr)
		vsock->rx_buf_max_nr = vsock->rx_buf_nr;
	virtqueue_kick(vq);
पूर्ण

अटल व्योम virtio_transport_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_vsock *vsock =
		container_of(work, काष्ठा virtio_vsock, tx_work);
	काष्ठा virtqueue *vq;
	bool added = false;

	vq = vsock->vqs[VSOCK_VQ_TX];
	mutex_lock(&vsock->tx_lock);

	अगर (!vsock->tx_run)
		जाओ out;

	करो अणु
		काष्ठा virtio_vsock_pkt *pkt;
		अचिन्हित पूर्णांक len;

		virtqueue_disable_cb(vq);
		जबतक ((pkt = virtqueue_get_buf(vq, &len)) != शून्य) अणु
			virtio_transport_मुक्त_pkt(pkt);
			added = true;
		पूर्ण
	पूर्ण जबतक (!virtqueue_enable_cb(vq));

out:
	mutex_unlock(&vsock->tx_lock);

	अगर (added)
		queue_work(virtio_vsock_workqueue, &vsock->send_pkt_work);
पूर्ण

/* Is there space left क्रम replies to rx packets? */
अटल bool virtio_transport_more_replies(काष्ठा virtio_vsock *vsock)
अणु
	काष्ठा virtqueue *vq = vsock->vqs[VSOCK_VQ_RX];
	पूर्णांक val;

	smp_rmb(); /* paired with atomic_inc() and atomic_dec_वापस() */
	val = atomic_पढ़ो(&vsock->queued_replies);

	वापस val < virtqueue_get_vring_size(vq);
पूर्ण

/* event_lock must be held */
अटल पूर्णांक virtio_vsock_event_fill_one(काष्ठा virtio_vsock *vsock,
				       काष्ठा virtio_vsock_event *event)
अणु
	काष्ठा scatterlist sg;
	काष्ठा virtqueue *vq;

	vq = vsock->vqs[VSOCK_VQ_EVENT];

	sg_init_one(&sg, event, माप(*event));

	वापस virtqueue_add_inbuf(vq, &sg, 1, event, GFP_KERNEL);
पूर्ण

/* event_lock must be held */
अटल व्योम virtio_vsock_event_fill(काष्ठा virtio_vsock *vsock)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(vsock->event_list); i++) अणु
		काष्ठा virtio_vsock_event *event = &vsock->event_list[i];

		virtio_vsock_event_fill_one(vsock, event);
	पूर्ण

	virtqueue_kick(vsock->vqs[VSOCK_VQ_EVENT]);
पूर्ण

अटल व्योम virtio_vsock_reset_sock(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	sk->sk_state = TCP_CLOSE;
	sk->sk_err = ECONNRESET;
	sk->sk_error_report(sk);
	release_sock(sk);
पूर्ण

अटल व्योम virtio_vsock_update_guest_cid(काष्ठा virtio_vsock *vsock)
अणु
	काष्ठा virtio_device *vdev = vsock->vdev;
	__le64 guest_cid;

	vdev->config->get(vdev, दुरत्व(काष्ठा virtio_vsock_config, guest_cid),
			  &guest_cid, माप(guest_cid));
	vsock->guest_cid = le64_to_cpu(guest_cid);
पूर्ण

/* event_lock must be held */
अटल व्योम virtio_vsock_event_handle(काष्ठा virtio_vsock *vsock,
				      काष्ठा virtio_vsock_event *event)
अणु
	चयन (le32_to_cpu(event->id)) अणु
	हाल VIRTIO_VSOCK_EVENT_TRANSPORT_RESET:
		virtio_vsock_update_guest_cid(vsock);
		vsock_क्रम_each_connected_socket(virtio_vsock_reset_sock);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम virtio_transport_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_vsock *vsock =
		container_of(work, काष्ठा virtio_vsock, event_work);
	काष्ठा virtqueue *vq;

	vq = vsock->vqs[VSOCK_VQ_EVENT];

	mutex_lock(&vsock->event_lock);

	अगर (!vsock->event_run)
		जाओ out;

	करो अणु
		काष्ठा virtio_vsock_event *event;
		अचिन्हित पूर्णांक len;

		virtqueue_disable_cb(vq);
		जबतक ((event = virtqueue_get_buf(vq, &len)) != शून्य) अणु
			अगर (len == माप(*event))
				virtio_vsock_event_handle(vsock, event);

			virtio_vsock_event_fill_one(vsock, event);
		पूर्ण
	पूर्ण जबतक (!virtqueue_enable_cb(vq));

	virtqueue_kick(vsock->vqs[VSOCK_VQ_EVENT]);
out:
	mutex_unlock(&vsock->event_lock);
पूर्ण

अटल व्योम virtio_vsock_event_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_vsock *vsock = vq->vdev->priv;

	अगर (!vsock)
		वापस;
	queue_work(virtio_vsock_workqueue, &vsock->event_work);
पूर्ण

अटल व्योम virtio_vsock_tx_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_vsock *vsock = vq->vdev->priv;

	अगर (!vsock)
		वापस;
	queue_work(virtio_vsock_workqueue, &vsock->tx_work);
पूर्ण

अटल व्योम virtio_vsock_rx_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_vsock *vsock = vq->vdev->priv;

	अगर (!vsock)
		वापस;
	queue_work(virtio_vsock_workqueue, &vsock->rx_work);
पूर्ण

अटल काष्ठा virtio_transport virtio_transport = अणु
	.transport = अणु
		.module                   = THIS_MODULE,

		.get_local_cid            = virtio_transport_get_local_cid,

		.init                     = virtio_transport_करो_socket_init,
		.deकाष्ठा                 = virtio_transport_deकाष्ठा,
		.release                  = virtio_transport_release,
		.connect                  = virtio_transport_connect,
		.shutकरोwn                 = virtio_transport_shutकरोwn,
		.cancel_pkt               = virtio_transport_cancel_pkt,

		.dgram_bind               = virtio_transport_dgram_bind,
		.dgram_dequeue            = virtio_transport_dgram_dequeue,
		.dgram_enqueue            = virtio_transport_dgram_enqueue,
		.dgram_allow              = virtio_transport_dgram_allow,

		.stream_dequeue           = virtio_transport_stream_dequeue,
		.stream_enqueue           = virtio_transport_stream_enqueue,
		.stream_has_data          = virtio_transport_stream_has_data,
		.stream_has_space         = virtio_transport_stream_has_space,
		.stream_rcvhiwat          = virtio_transport_stream_rcvhiwat,
		.stream_is_active         = virtio_transport_stream_is_active,
		.stream_allow             = virtio_transport_stream_allow,

		.notअगरy_poll_in           = virtio_transport_notअगरy_poll_in,
		.notअगरy_poll_out          = virtio_transport_notअगरy_poll_out,
		.notअगरy_recv_init         = virtio_transport_notअगरy_recv_init,
		.notअगरy_recv_pre_block    = virtio_transport_notअगरy_recv_pre_block,
		.notअगरy_recv_pre_dequeue  = virtio_transport_notअगरy_recv_pre_dequeue,
		.notअगरy_recv_post_dequeue = virtio_transport_notअगरy_recv_post_dequeue,
		.notअगरy_send_init         = virtio_transport_notअगरy_send_init,
		.notअगरy_send_pre_block    = virtio_transport_notअगरy_send_pre_block,
		.notअगरy_send_pre_enqueue  = virtio_transport_notअगरy_send_pre_enqueue,
		.notअगरy_send_post_enqueue = virtio_transport_notअगरy_send_post_enqueue,
		.notअगरy_buffer_size       = virtio_transport_notअगरy_buffer_size,
	पूर्ण,

	.send_pkt = virtio_transport_send_pkt,
पूर्ण;

अटल व्योम virtio_transport_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_vsock *vsock =
		container_of(work, काष्ठा virtio_vsock, rx_work);
	काष्ठा virtqueue *vq;

	vq = vsock->vqs[VSOCK_VQ_RX];

	mutex_lock(&vsock->rx_lock);

	अगर (!vsock->rx_run)
		जाओ out;

	करो अणु
		virtqueue_disable_cb(vq);
		क्रम (;;) अणु
			काष्ठा virtio_vsock_pkt *pkt;
			अचिन्हित पूर्णांक len;

			अगर (!virtio_transport_more_replies(vsock)) अणु
				/* Stop rx until the device processes alपढ़ोy
				 * pending replies.  Leave rx virtqueue
				 * callbacks disabled.
				 */
				जाओ out;
			पूर्ण

			pkt = virtqueue_get_buf(vq, &len);
			अगर (!pkt) अणु
				अवरोध;
			पूर्ण

			vsock->rx_buf_nr--;

			/* Drop लघु/दीर्घ packets */
			अगर (unlikely(len < माप(pkt->hdr) ||
				     len > माप(pkt->hdr) + pkt->len)) अणु
				virtio_transport_मुक्त_pkt(pkt);
				जारी;
			पूर्ण

			pkt->len = len - माप(pkt->hdr);
			virtio_transport_deliver_tap_pkt(pkt);
			virtio_transport_recv_pkt(&virtio_transport, pkt);
		पूर्ण
	पूर्ण जबतक (!virtqueue_enable_cb(vq));

out:
	अगर (vsock->rx_buf_nr < vsock->rx_buf_max_nr / 2)
		virtio_vsock_rx_fill(vsock);
	mutex_unlock(&vsock->rx_lock);
पूर्ण

अटल पूर्णांक virtio_vsock_probe(काष्ठा virtio_device *vdev)
अणु
	vq_callback_t *callbacks[] = अणु
		virtio_vsock_rx_करोne,
		virtio_vsock_tx_करोne,
		virtio_vsock_event_करोne,
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		"rx",
		"tx",
		"event",
	पूर्ण;
	काष्ठा virtio_vsock *vsock = शून्य;
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&the_virtio_vsock_mutex);
	अगर (ret)
		वापस ret;

	/* Only one virtio-vsock device per guest is supported */
	अगर (rcu_dereference_रक्षित(the_virtio_vsock,
				lockdep_is_held(&the_virtio_vsock_mutex))) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	vsock = kzalloc(माप(*vsock), GFP_KERNEL);
	अगर (!vsock) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	vsock->vdev = vdev;

	ret = virtio_find_vqs(vsock->vdev, VSOCK_VQ_MAX,
			      vsock->vqs, callbacks, names,
			      शून्य);
	अगर (ret < 0)
		जाओ out;

	virtio_vsock_update_guest_cid(vsock);

	vsock->rx_buf_nr = 0;
	vsock->rx_buf_max_nr = 0;
	atomic_set(&vsock->queued_replies, 0);

	mutex_init(&vsock->tx_lock);
	mutex_init(&vsock->rx_lock);
	mutex_init(&vsock->event_lock);
	spin_lock_init(&vsock->send_pkt_list_lock);
	INIT_LIST_HEAD(&vsock->send_pkt_list);
	INIT_WORK(&vsock->rx_work, virtio_transport_rx_work);
	INIT_WORK(&vsock->tx_work, virtio_transport_tx_work);
	INIT_WORK(&vsock->event_work, virtio_transport_event_work);
	INIT_WORK(&vsock->send_pkt_work, virtio_transport_send_pkt_work);

	mutex_lock(&vsock->tx_lock);
	vsock->tx_run = true;
	mutex_unlock(&vsock->tx_lock);

	mutex_lock(&vsock->rx_lock);
	virtio_vsock_rx_fill(vsock);
	vsock->rx_run = true;
	mutex_unlock(&vsock->rx_lock);

	mutex_lock(&vsock->event_lock);
	virtio_vsock_event_fill(vsock);
	vsock->event_run = true;
	mutex_unlock(&vsock->event_lock);

	vdev->priv = vsock;
	rcu_assign_poपूर्णांकer(the_virtio_vsock, vsock);

	mutex_unlock(&the_virtio_vsock_mutex);
	वापस 0;

out:
	kमुक्त(vsock);
	mutex_unlock(&the_virtio_vsock_mutex);
	वापस ret;
पूर्ण

अटल व्योम virtio_vsock_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_vsock *vsock = vdev->priv;
	काष्ठा virtio_vsock_pkt *pkt;

	mutex_lock(&the_virtio_vsock_mutex);

	vdev->priv = शून्य;
	rcu_assign_poपूर्णांकer(the_virtio_vsock, शून्य);
	synchronize_rcu();

	/* Reset all connected sockets when the device disappear */
	vsock_क्रम_each_connected_socket(virtio_vsock_reset_sock);

	/* Stop all work handlers to make sure no one is accessing the device,
	 * so we can safely call vdev->config->reset().
	 */
	mutex_lock(&vsock->rx_lock);
	vsock->rx_run = false;
	mutex_unlock(&vsock->rx_lock);

	mutex_lock(&vsock->tx_lock);
	vsock->tx_run = false;
	mutex_unlock(&vsock->tx_lock);

	mutex_lock(&vsock->event_lock);
	vsock->event_run = false;
	mutex_unlock(&vsock->event_lock);

	/* Flush all device ग_लिखोs and पूर्णांकerrupts, device will not use any
	 * more buffers.
	 */
	vdev->config->reset(vdev);

	mutex_lock(&vsock->rx_lock);
	जबतक ((pkt = virtqueue_detach_unused_buf(vsock->vqs[VSOCK_VQ_RX])))
		virtio_transport_मुक्त_pkt(pkt);
	mutex_unlock(&vsock->rx_lock);

	mutex_lock(&vsock->tx_lock);
	जबतक ((pkt = virtqueue_detach_unused_buf(vsock->vqs[VSOCK_VQ_TX])))
		virtio_transport_मुक्त_pkt(pkt);
	mutex_unlock(&vsock->tx_lock);

	spin_lock_bh(&vsock->send_pkt_list_lock);
	जबतक (!list_empty(&vsock->send_pkt_list)) अणु
		pkt = list_first_entry(&vsock->send_pkt_list,
				       काष्ठा virtio_vsock_pkt, list);
		list_del(&pkt->list);
		virtio_transport_मुक्त_pkt(pkt);
	पूर्ण
	spin_unlock_bh(&vsock->send_pkt_list_lock);

	/* Delete virtqueues and flush outstanding callbacks अगर any */
	vdev->config->del_vqs(vdev);

	/* Other works can be queued beक्रमe 'config->del_vqs()', so we flush
	 * all works beक्रमe to मुक्त the vsock object to aव्योम use after मुक्त.
	 */
	flush_work(&vsock->rx_work);
	flush_work(&vsock->tx_work);
	flush_work(&vsock->event_work);
	flush_work(&vsock->send_pkt_work);

	mutex_unlock(&the_virtio_vsock_mutex);

	kमुक्त(vsock);
पूर्ण

अटल काष्ठा virtio_device_id id_table[] = अणु
	अणु VIRTIO_ID_VSOCK, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक features[] = अणु
पूर्ण;

अटल काष्ठा virtio_driver virtio_vsock_driver = अणु
	.feature_table = features,
	.feature_table_size = ARRAY_SIZE(features),
	.driver.name = KBUILD_MODNAME,
	.driver.owner = THIS_MODULE,
	.id_table = id_table,
	.probe = virtio_vsock_probe,
	.हटाओ = virtio_vsock_हटाओ,
पूर्ण;

अटल पूर्णांक __init virtio_vsock_init(व्योम)
अणु
	पूर्णांक ret;

	virtio_vsock_workqueue = alloc_workqueue("virtio_vsock", 0, 0);
	अगर (!virtio_vsock_workqueue)
		वापस -ENOMEM;

	ret = vsock_core_रेजिस्टर(&virtio_transport.transport,
				  VSOCK_TRANSPORT_F_G2H);
	अगर (ret)
		जाओ out_wq;

	ret = रेजिस्टर_virtio_driver(&virtio_vsock_driver);
	अगर (ret)
		जाओ out_vci;

	वापस 0;

out_vci:
	vsock_core_unरेजिस्टर(&virtio_transport.transport);
out_wq:
	destroy_workqueue(virtio_vsock_workqueue);
	वापस ret;
पूर्ण

अटल व्योम __निकास virtio_vsock_निकास(व्योम)
अणु
	unरेजिस्टर_virtio_driver(&virtio_vsock_driver);
	vsock_core_unरेजिस्टर(&virtio_transport.transport);
	destroy_workqueue(virtio_vsock_workqueue);
पूर्ण

module_init(virtio_vsock_init);
module_निकास(virtio_vsock_निकास);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Asias He");
MODULE_DESCRIPTION("virtio transport for vsock");
MODULE_DEVICE_TABLE(virtio, id_table);
