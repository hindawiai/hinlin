<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vhost transport क्रम vsock
 *
 * Copyright (C) 2013-2015 Red Hat, Inc.
 * Author: Asias He <asias@redhat.com>
 *         Stefan Hajnoczi <stefanha@redhat.com>
 */
#समावेश <linux/miscdevice.h>
#समावेश <linux/atomic.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/sock.h>
#समावेश <linux/virtio_vsock.h>
#समावेश <linux/vhost.h>
#समावेश <linux/hashtable.h>

#समावेश <net/af_vsock.h>
#समावेश "vhost.h"

#घोषणा VHOST_VSOCK_DEFAULT_HOST_CID	2
/* Max number of bytes transferred beक्रमe requeueing the job.
 * Using this limit prevents one virtqueue from starving others. */
#घोषणा VHOST_VSOCK_WEIGHT 0x80000
/* Max number of packets transferred beक्रमe requeueing the job.
 * Using this limit prevents one virtqueue from starving others with
 * small pkts.
 */
#घोषणा VHOST_VSOCK_PKT_WEIGHT 256

क्रमागत अणु
	VHOST_VSOCK_FEATURES = VHOST_FEATURES |
			       (1ULL << VIRTIO_F_ACCESS_PLATFORM)
पूर्ण;

क्रमागत अणु
	VHOST_VSOCK_BACKEND_FEATURES = (1ULL << VHOST_BACKEND_F_IOTLB_MSG_V2)
पूर्ण;

/* Used to track all the vhost_vsock instances on the प्रणाली. */
अटल DEFINE_MUTEX(vhost_vsock_mutex);
अटल DEFINE_READ_MOSTLY_HASHTABLE(vhost_vsock_hash, 8);

काष्ठा vhost_vsock अणु
	काष्ठा vhost_dev dev;
	काष्ठा vhost_virtqueue vqs[2];

	/* Link to global vhost_vsock_hash, ग_लिखोs use vhost_vsock_mutex */
	काष्ठा hlist_node hash;

	काष्ठा vhost_work send_pkt_work;
	spinlock_t send_pkt_list_lock;
	काष्ठा list_head send_pkt_list;	/* host->guest pending packets */

	atomic_t queued_replies;

	u32 guest_cid;
पूर्ण;

अटल u32 vhost_transport_get_local_cid(व्योम)
अणु
	वापस VHOST_VSOCK_DEFAULT_HOST_CID;
पूर्ण

/* Callers that dereference the वापस value must hold vhost_vsock_mutex or the
 * RCU पढ़ो lock.
 */
अटल काष्ठा vhost_vsock *vhost_vsock_get(u32 guest_cid)
अणु
	काष्ठा vhost_vsock *vsock;

	hash_क्रम_each_possible_rcu(vhost_vsock_hash, vsock, hash, guest_cid) अणु
		u32 other_cid = vsock->guest_cid;

		/* Skip instances that have no CID yet */
		अगर (other_cid == 0)
			जारी;

		अगर (other_cid == guest_cid)
			वापस vsock;

	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
vhost_transport_करो_send_pkt(काष्ठा vhost_vsock *vsock,
			    काष्ठा vhost_virtqueue *vq)
अणु
	काष्ठा vhost_virtqueue *tx_vq = &vsock->vqs[VSOCK_VQ_TX];
	पूर्णांक pkts = 0, total_len = 0;
	bool added = false;
	bool restart_tx = false;

	mutex_lock(&vq->mutex);

	अगर (!vhost_vq_get_backend(vq))
		जाओ out;

	अगर (!vq_meta_prefetch(vq))
		जाओ out;

	/* Aव्योम further vmनिकासs, we're alपढ़ोy processing the virtqueue */
	vhost_disable_notअगरy(&vsock->dev, vq);

	करो अणु
		काष्ठा virtio_vsock_pkt *pkt;
		काष्ठा iov_iter iov_iter;
		अचिन्हित out, in;
		माप_प्रकार nbytes;
		माप_प्रकार iov_len, payload_len;
		पूर्णांक head;

		spin_lock_bh(&vsock->send_pkt_list_lock);
		अगर (list_empty(&vsock->send_pkt_list)) अणु
			spin_unlock_bh(&vsock->send_pkt_list_lock);
			vhost_enable_notअगरy(&vsock->dev, vq);
			अवरोध;
		पूर्ण

		pkt = list_first_entry(&vsock->send_pkt_list,
				       काष्ठा virtio_vsock_pkt, list);
		list_del_init(&pkt->list);
		spin_unlock_bh(&vsock->send_pkt_list_lock);

		head = vhost_get_vq_desc(vq, vq->iov, ARRAY_SIZE(vq->iov),
					 &out, &in, शून्य, शून्य);
		अगर (head < 0) अणु
			spin_lock_bh(&vsock->send_pkt_list_lock);
			list_add(&pkt->list, &vsock->send_pkt_list);
			spin_unlock_bh(&vsock->send_pkt_list_lock);
			अवरोध;
		पूर्ण

		अगर (head == vq->num) अणु
			spin_lock_bh(&vsock->send_pkt_list_lock);
			list_add(&pkt->list, &vsock->send_pkt_list);
			spin_unlock_bh(&vsock->send_pkt_list_lock);

			/* We cannot finish yet अगर more buffers snuck in जबतक
			 * re-enabling notअगरy.
			 */
			अगर (unlikely(vhost_enable_notअगरy(&vsock->dev, vq))) अणु
				vhost_disable_notअगरy(&vsock->dev, vq);
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (out) अणु
			virtio_transport_मुक्त_pkt(pkt);
			vq_err(vq, "Expected 0 output buffers, got %u\n", out);
			अवरोध;
		पूर्ण

		iov_len = iov_length(&vq->iov[out], in);
		अगर (iov_len < माप(pkt->hdr)) अणु
			virtio_transport_मुक्त_pkt(pkt);
			vq_err(vq, "Buffer len [%zu] too small\n", iov_len);
			अवरोध;
		पूर्ण

		iov_iter_init(&iov_iter, READ, &vq->iov[out], in, iov_len);
		payload_len = pkt->len - pkt->off;

		/* If the packet is greater than the space available in the
		 * buffer, we split it using multiple buffers.
		 */
		अगर (payload_len > iov_len - माप(pkt->hdr))
			payload_len = iov_len - माप(pkt->hdr);

		/* Set the correct length in the header */
		pkt->hdr.len = cpu_to_le32(payload_len);

		nbytes = copy_to_iter(&pkt->hdr, माप(pkt->hdr), &iov_iter);
		अगर (nbytes != माप(pkt->hdr)) अणु
			virtio_transport_मुक्त_pkt(pkt);
			vq_err(vq, "Faulted on copying pkt hdr\n");
			अवरोध;
		पूर्ण

		nbytes = copy_to_iter(pkt->buf + pkt->off, payload_len,
				      &iov_iter);
		अगर (nbytes != payload_len) अणु
			virtio_transport_मुक्त_pkt(pkt);
			vq_err(vq, "Faulted on copying pkt buf\n");
			अवरोध;
		पूर्ण

		/* Deliver to monitoring devices all packets that we
		 * will transmit.
		 */
		virtio_transport_deliver_tap_pkt(pkt);

		vhost_add_used(vq, head, माप(pkt->hdr) + payload_len);
		added = true;

		pkt->off += payload_len;
		total_len += payload_len;

		/* If we didn't send all the payload we can requeue the packet
		 * to send it with the next available buffer.
		 */
		अगर (pkt->off < pkt->len) अणु
			/* We are queueing the same virtio_vsock_pkt to handle
			 * the reमुख्यing bytes, and we want to deliver it
			 * to monitoring devices in the next iteration.
			 */
			pkt->tap_delivered = false;

			spin_lock_bh(&vsock->send_pkt_list_lock);
			list_add(&pkt->list, &vsock->send_pkt_list);
			spin_unlock_bh(&vsock->send_pkt_list_lock);
		पूर्ण अन्यथा अणु
			अगर (pkt->reply) अणु
				पूर्णांक val;

				val = atomic_dec_वापस(&vsock->queued_replies);

				/* Do we have resources to resume tx
				 * processing?
				 */
				अगर (val + 1 == tx_vq->num)
					restart_tx = true;
			पूर्ण

			virtio_transport_मुक्त_pkt(pkt);
		पूर्ण
	पूर्ण जबतक(likely(!vhost_exceeds_weight(vq, ++pkts, total_len)));
	अगर (added)
		vhost_संकेत(&vsock->dev, vq);

out:
	mutex_unlock(&vq->mutex);

	अगर (restart_tx)
		vhost_poll_queue(&tx_vq->poll);
पूर्ण

अटल व्योम vhost_transport_send_pkt_work(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_virtqueue *vq;
	काष्ठा vhost_vsock *vsock;

	vsock = container_of(work, काष्ठा vhost_vsock, send_pkt_work);
	vq = &vsock->vqs[VSOCK_VQ_RX];

	vhost_transport_करो_send_pkt(vsock, vq);
पूर्ण

अटल पूर्णांक
vhost_transport_send_pkt(काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा vhost_vsock *vsock;
	पूर्णांक len = pkt->len;

	rcu_पढ़ो_lock();

	/* Find the vhost_vsock according to guest context id  */
	vsock = vhost_vsock_get(le64_to_cpu(pkt->hdr.dst_cid));
	अगर (!vsock) अणु
		rcu_पढ़ो_unlock();
		virtio_transport_मुक्त_pkt(pkt);
		वापस -ENODEV;
	पूर्ण

	अगर (pkt->reply)
		atomic_inc(&vsock->queued_replies);

	spin_lock_bh(&vsock->send_pkt_list_lock);
	list_add_tail(&pkt->list, &vsock->send_pkt_list);
	spin_unlock_bh(&vsock->send_pkt_list_lock);

	vhost_work_queue(&vsock->dev, &vsock->send_pkt_work);

	rcu_पढ़ो_unlock();
	वापस len;
पूर्ण

अटल पूर्णांक
vhost_transport_cancel_pkt(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा vhost_vsock *vsock;
	काष्ठा virtio_vsock_pkt *pkt, *n;
	पूर्णांक cnt = 0;
	पूर्णांक ret = -ENODEV;
	LIST_HEAD(मुक्तme);

	rcu_पढ़ो_lock();

	/* Find the vhost_vsock according to guest context id  */
	vsock = vhost_vsock_get(vsk->remote_addr.svm_cid);
	अगर (!vsock)
		जाओ out;

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
		काष्ठा vhost_virtqueue *tx_vq = &vsock->vqs[VSOCK_VQ_TX];
		पूर्णांक new_cnt;

		new_cnt = atomic_sub_वापस(cnt, &vsock->queued_replies);
		अगर (new_cnt + cnt >= tx_vq->num && new_cnt < tx_vq->num)
			vhost_poll_queue(&tx_vq->poll);
	पूर्ण

	ret = 0;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल काष्ठा virtio_vsock_pkt *
vhost_vsock_alloc_pkt(काष्ठा vhost_virtqueue *vq,
		      अचिन्हित पूर्णांक out, अचिन्हित पूर्णांक in)
अणु
	काष्ठा virtio_vsock_pkt *pkt;
	काष्ठा iov_iter iov_iter;
	माप_प्रकार nbytes;
	माप_प्रकार len;

	अगर (in != 0) अणु
		vq_err(vq, "Expected 0 input buffers, got %u\n", in);
		वापस शून्य;
	पूर्ण

	pkt = kzalloc(माप(*pkt), GFP_KERNEL);
	अगर (!pkt)
		वापस शून्य;

	len = iov_length(vq->iov, out);
	iov_iter_init(&iov_iter, WRITE, vq->iov, out, len);

	nbytes = copy_from_iter(&pkt->hdr, माप(pkt->hdr), &iov_iter);
	अगर (nbytes != माप(pkt->hdr)) अणु
		vq_err(vq, "Expected %zu bytes for pkt->hdr, got %zu bytes\n",
		       माप(pkt->hdr), nbytes);
		kमुक्त(pkt);
		वापस शून्य;
	पूर्ण

	अगर (le16_to_cpu(pkt->hdr.type) == VIRTIO_VSOCK_TYPE_STREAM)
		pkt->len = le32_to_cpu(pkt->hdr.len);

	/* No payload */
	अगर (!pkt->len)
		वापस pkt;

	/* The pkt is too big */
	अगर (pkt->len > VIRTIO_VSOCK_MAX_PKT_BUF_SIZE) अणु
		kमुक्त(pkt);
		वापस शून्य;
	पूर्ण

	pkt->buf = kदो_स्मृति(pkt->len, GFP_KERNEL);
	अगर (!pkt->buf) अणु
		kमुक्त(pkt);
		वापस शून्य;
	पूर्ण

	pkt->buf_len = pkt->len;

	nbytes = copy_from_iter(pkt->buf, pkt->len, &iov_iter);
	अगर (nbytes != pkt->len) अणु
		vq_err(vq, "Expected %u byte payload, got %zu bytes\n",
		       pkt->len, nbytes);
		virtio_transport_मुक्त_pkt(pkt);
		वापस शून्य;
	पूर्ण

	वापस pkt;
पूर्ण

/* Is there space left क्रम replies to rx packets? */
अटल bool vhost_vsock_more_replies(काष्ठा vhost_vsock *vsock)
अणु
	काष्ठा vhost_virtqueue *vq = &vsock->vqs[VSOCK_VQ_TX];
	पूर्णांक val;

	smp_rmb(); /* paired with atomic_inc() and atomic_dec_वापस() */
	val = atomic_पढ़ो(&vsock->queued_replies);

	वापस val < vq->num;
पूर्ण

अटल काष्ठा virtio_transport vhost_transport = अणु
	.transport = अणु
		.module                   = THIS_MODULE,

		.get_local_cid            = vhost_transport_get_local_cid,

		.init                     = virtio_transport_करो_socket_init,
		.deकाष्ठा                 = virtio_transport_deकाष्ठा,
		.release                  = virtio_transport_release,
		.connect                  = virtio_transport_connect,
		.shutकरोwn                 = virtio_transport_shutकरोwn,
		.cancel_pkt               = vhost_transport_cancel_pkt,

		.dgram_enqueue            = virtio_transport_dgram_enqueue,
		.dgram_dequeue            = virtio_transport_dgram_dequeue,
		.dgram_bind               = virtio_transport_dgram_bind,
		.dgram_allow              = virtio_transport_dgram_allow,

		.stream_enqueue           = virtio_transport_stream_enqueue,
		.stream_dequeue           = virtio_transport_stream_dequeue,
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

	.send_pkt = vhost_transport_send_pkt,
पूर्ण;

अटल व्योम vhost_vsock_handle_tx_kick(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_virtqueue *vq = container_of(work, काष्ठा vhost_virtqueue,
						  poll.work);
	काष्ठा vhost_vsock *vsock = container_of(vq->dev, काष्ठा vhost_vsock,
						 dev);
	काष्ठा virtio_vsock_pkt *pkt;
	पूर्णांक head, pkts = 0, total_len = 0;
	अचिन्हित पूर्णांक out, in;
	bool added = false;

	mutex_lock(&vq->mutex);

	अगर (!vhost_vq_get_backend(vq))
		जाओ out;

	अगर (!vq_meta_prefetch(vq))
		जाओ out;

	vhost_disable_notअगरy(&vsock->dev, vq);
	करो अणु
		u32 len;

		अगर (!vhost_vsock_more_replies(vsock)) अणु
			/* Stop tx until the device processes alपढ़ोy
			 * pending replies.  Leave tx virtqueue
			 * callbacks disabled.
			 */
			जाओ no_more_replies;
		पूर्ण

		head = vhost_get_vq_desc(vq, vq->iov, ARRAY_SIZE(vq->iov),
					 &out, &in, शून्य, शून्य);
		अगर (head < 0)
			अवरोध;

		अगर (head == vq->num) अणु
			अगर (unlikely(vhost_enable_notअगरy(&vsock->dev, vq))) अणु
				vhost_disable_notअगरy(&vsock->dev, vq);
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		pkt = vhost_vsock_alloc_pkt(vq, out, in);
		अगर (!pkt) अणु
			vq_err(vq, "Faulted on pkt\n");
			जारी;
		पूर्ण

		len = pkt->len;

		/* Deliver to monitoring devices all received packets */
		virtio_transport_deliver_tap_pkt(pkt);

		/* Only accept correctly addressed packets */
		अगर (le64_to_cpu(pkt->hdr.src_cid) == vsock->guest_cid &&
		    le64_to_cpu(pkt->hdr.dst_cid) ==
		    vhost_transport_get_local_cid())
			virtio_transport_recv_pkt(&vhost_transport, pkt);
		अन्यथा
			virtio_transport_मुक्त_pkt(pkt);

		len += माप(pkt->hdr);
		vhost_add_used(vq, head, len);
		total_len += len;
		added = true;
	पूर्ण जबतक(likely(!vhost_exceeds_weight(vq, ++pkts, total_len)));

no_more_replies:
	अगर (added)
		vhost_संकेत(&vsock->dev, vq);

out:
	mutex_unlock(&vq->mutex);
पूर्ण

अटल व्योम vhost_vsock_handle_rx_kick(काष्ठा vhost_work *work)
अणु
	काष्ठा vhost_virtqueue *vq = container_of(work, काष्ठा vhost_virtqueue,
						poll.work);
	काष्ठा vhost_vsock *vsock = container_of(vq->dev, काष्ठा vhost_vsock,
						 dev);

	vhost_transport_करो_send_pkt(vsock, vq);
पूर्ण

अटल पूर्णांक vhost_vsock_start(काष्ठा vhost_vsock *vsock)
अणु
	काष्ठा vhost_virtqueue *vq;
	माप_प्रकार i;
	पूर्णांक ret;

	mutex_lock(&vsock->dev.mutex);

	ret = vhost_dev_check_owner(&vsock->dev);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < ARRAY_SIZE(vsock->vqs); i++) अणु
		vq = &vsock->vqs[i];

		mutex_lock(&vq->mutex);

		अगर (!vhost_vq_access_ok(vq)) अणु
			ret = -EFAULT;
			जाओ err_vq;
		पूर्ण

		अगर (!vhost_vq_get_backend(vq)) अणु
			vhost_vq_set_backend(vq, vsock);
			ret = vhost_vq_init_access(vq);
			अगर (ret)
				जाओ err_vq;
		पूर्ण

		mutex_unlock(&vq->mutex);
	पूर्ण

	/* Some packets may have been queued beक्रमe the device was started,
	 * let's kick the send worker to send them.
	 */
	vhost_work_queue(&vsock->dev, &vsock->send_pkt_work);

	mutex_unlock(&vsock->dev.mutex);
	वापस 0;

err_vq:
	vhost_vq_set_backend(vq, शून्य);
	mutex_unlock(&vq->mutex);

	क्रम (i = 0; i < ARRAY_SIZE(vsock->vqs); i++) अणु
		vq = &vsock->vqs[i];

		mutex_lock(&vq->mutex);
		vhost_vq_set_backend(vq, शून्य);
		mutex_unlock(&vq->mutex);
	पूर्ण
err:
	mutex_unlock(&vsock->dev.mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक vhost_vsock_stop(काष्ठा vhost_vsock *vsock)
अणु
	माप_प्रकार i;
	पूर्णांक ret;

	mutex_lock(&vsock->dev.mutex);

	ret = vhost_dev_check_owner(&vsock->dev);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < ARRAY_SIZE(vsock->vqs); i++) अणु
		काष्ठा vhost_virtqueue *vq = &vsock->vqs[i];

		mutex_lock(&vq->mutex);
		vhost_vq_set_backend(vq, शून्य);
		mutex_unlock(&vq->mutex);
	पूर्ण

err:
	mutex_unlock(&vsock->dev.mutex);
	वापस ret;
पूर्ण

अटल व्योम vhost_vsock_मुक्त(काष्ठा vhost_vsock *vsock)
अणु
	kvमुक्त(vsock);
पूर्ण

अटल पूर्णांक vhost_vsock_dev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vhost_virtqueue **vqs;
	काष्ठा vhost_vsock *vsock;
	पूर्णांक ret;

	/* This काष्ठा is large and allocation could fail, fall back to vदो_स्मृति
	 * अगर there is no other way.
	 */
	vsock = kvदो_स्मृति(माप(*vsock), GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	अगर (!vsock)
		वापस -ENOMEM;

	vqs = kदो_स्मृति_array(ARRAY_SIZE(vsock->vqs), माप(*vqs), GFP_KERNEL);
	अगर (!vqs) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	vsock->guest_cid = 0; /* no CID asचिन्हित yet */

	atomic_set(&vsock->queued_replies, 0);

	vqs[VSOCK_VQ_TX] = &vsock->vqs[VSOCK_VQ_TX];
	vqs[VSOCK_VQ_RX] = &vsock->vqs[VSOCK_VQ_RX];
	vsock->vqs[VSOCK_VQ_TX].handle_kick = vhost_vsock_handle_tx_kick;
	vsock->vqs[VSOCK_VQ_RX].handle_kick = vhost_vsock_handle_rx_kick;

	vhost_dev_init(&vsock->dev, vqs, ARRAY_SIZE(vsock->vqs),
		       UIO_MAXIOV, VHOST_VSOCK_PKT_WEIGHT,
		       VHOST_VSOCK_WEIGHT, true, शून्य);

	file->निजी_data = vsock;
	spin_lock_init(&vsock->send_pkt_list_lock);
	INIT_LIST_HEAD(&vsock->send_pkt_list);
	vhost_work_init(&vsock->send_pkt_work, vhost_transport_send_pkt_work);
	वापस 0;

out:
	vhost_vsock_मुक्त(vsock);
	वापस ret;
पूर्ण

अटल व्योम vhost_vsock_flush(काष्ठा vhost_vsock *vsock)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vsock->vqs); i++)
		अगर (vsock->vqs[i].handle_kick)
			vhost_poll_flush(&vsock->vqs[i].poll);
	vhost_work_flush(&vsock->dev, &vsock->send_pkt_work);
पूर्ण

अटल व्योम vhost_vsock_reset_orphans(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	/* vmci_transport.c करोesn't take sk_lock here either.  At least we're
	 * under vsock_table_lock so the sock cannot disappear जबतक we're
	 * executing.
	 */

	/* If the peer is still valid, no need to reset connection */
	अगर (vhost_vsock_get(vsk->remote_addr.svm_cid))
		वापस;

	/* If the बंद समयout is pending, let it expire.  This aव्योमs races
	 * with the समयout callback.
	 */
	अगर (vsk->बंद_work_scheduled)
		वापस;

	sock_set_flag(sk, SOCK_DONE);
	vsk->peer_shutकरोwn = SHUTDOWN_MASK;
	sk->sk_state = SS_UNCONNECTED;
	sk->sk_err = ECONNRESET;
	sk->sk_error_report(sk);
पूर्ण

अटल पूर्णांक vhost_vsock_dev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vhost_vsock *vsock = file->निजी_data;

	mutex_lock(&vhost_vsock_mutex);
	अगर (vsock->guest_cid)
		hash_del_rcu(&vsock->hash);
	mutex_unlock(&vhost_vsock_mutex);

	/* Wait क्रम other CPUs to finish using vsock */
	synchronize_rcu();

	/* Iterating over all connections क्रम all CIDs to find orphans is
	 * inefficient.  Room क्रम improvement here. */
	vsock_क्रम_each_connected_socket(vhost_vsock_reset_orphans);

	vhost_vsock_stop(vsock);
	vhost_vsock_flush(vsock);
	vhost_dev_stop(&vsock->dev);

	spin_lock_bh(&vsock->send_pkt_list_lock);
	जबतक (!list_empty(&vsock->send_pkt_list)) अणु
		काष्ठा virtio_vsock_pkt *pkt;

		pkt = list_first_entry(&vsock->send_pkt_list,
				काष्ठा virtio_vsock_pkt, list);
		list_del_init(&pkt->list);
		virtio_transport_मुक्त_pkt(pkt);
	पूर्ण
	spin_unlock_bh(&vsock->send_pkt_list_lock);

	vhost_dev_cleanup(&vsock->dev);
	kमुक्त(vsock->dev.vqs);
	vhost_vsock_मुक्त(vsock);
	वापस 0;
पूर्ण

अटल पूर्णांक vhost_vsock_set_cid(काष्ठा vhost_vsock *vsock, u64 guest_cid)
अणु
	काष्ठा vhost_vsock *other;

	/* Refuse reserved CIDs */
	अगर (guest_cid <= VMADDR_CID_HOST ||
	    guest_cid == U32_MAX)
		वापस -EINVAL;

	/* 64-bit CIDs are not yet supported */
	अगर (guest_cid > U32_MAX)
		वापस -EINVAL;

	/* Refuse अगर CID is asचिन्हित to the guest->host transport (i.e. nested
	 * VM), to make the loopback work.
	 */
	अगर (vsock_find_cid(guest_cid))
		वापस -EADDRINUSE;

	/* Refuse अगर CID is alपढ़ोy in use */
	mutex_lock(&vhost_vsock_mutex);
	other = vhost_vsock_get(guest_cid);
	अगर (other && other != vsock) अणु
		mutex_unlock(&vhost_vsock_mutex);
		वापस -EADDRINUSE;
	पूर्ण

	अगर (vsock->guest_cid)
		hash_del_rcu(&vsock->hash);

	vsock->guest_cid = guest_cid;
	hash_add_rcu(vhost_vsock_hash, &vsock->hash, vsock->guest_cid);
	mutex_unlock(&vhost_vsock_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक vhost_vsock_set_features(काष्ठा vhost_vsock *vsock, u64 features)
अणु
	काष्ठा vhost_virtqueue *vq;
	पूर्णांक i;

	अगर (features & ~VHOST_VSOCK_FEATURES)
		वापस -EOPNOTSUPP;

	mutex_lock(&vsock->dev.mutex);
	अगर ((features & (1 << VHOST_F_LOG_ALL)) &&
	    !vhost_log_access_ok(&vsock->dev)) अणु
		जाओ err;
	पूर्ण

	अगर ((features & (1ULL << VIRTIO_F_ACCESS_PLATFORM))) अणु
		अगर (vhost_init_device_iotlb(&vsock->dev, true))
			जाओ err;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(vsock->vqs); i++) अणु
		vq = &vsock->vqs[i];
		mutex_lock(&vq->mutex);
		vq->acked_features = features;
		mutex_unlock(&vq->mutex);
	पूर्ण
	mutex_unlock(&vsock->dev.mutex);
	वापस 0;

err:
	mutex_unlock(&vsock->dev.mutex);
	वापस -EFAULT;
पूर्ण

अटल दीर्घ vhost_vsock_dev_ioctl(काष्ठा file *f, अचिन्हित पूर्णांक ioctl,
				  अचिन्हित दीर्घ arg)
अणु
	काष्ठा vhost_vsock *vsock = f->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	u64 guest_cid;
	u64 features;
	पूर्णांक start;
	पूर्णांक r;

	चयन (ioctl) अणु
	हाल VHOST_VSOCK_SET_GUEST_CID:
		अगर (copy_from_user(&guest_cid, argp, माप(guest_cid)))
			वापस -EFAULT;
		वापस vhost_vsock_set_cid(vsock, guest_cid);
	हाल VHOST_VSOCK_SET_RUNNING:
		अगर (copy_from_user(&start, argp, माप(start)))
			वापस -EFAULT;
		अगर (start)
			वापस vhost_vsock_start(vsock);
		अन्यथा
			वापस vhost_vsock_stop(vsock);
	हाल VHOST_GET_FEATURES:
		features = VHOST_VSOCK_FEATURES;
		अगर (copy_to_user(argp, &features, माप(features)))
			वापस -EFAULT;
		वापस 0;
	हाल VHOST_SET_FEATURES:
		अगर (copy_from_user(&features, argp, माप(features)))
			वापस -EFAULT;
		वापस vhost_vsock_set_features(vsock, features);
	हाल VHOST_GET_BACKEND_FEATURES:
		features = VHOST_VSOCK_BACKEND_FEATURES;
		अगर (copy_to_user(argp, &features, माप(features)))
			वापस -EFAULT;
		वापस 0;
	हाल VHOST_SET_BACKEND_FEATURES:
		अगर (copy_from_user(&features, argp, माप(features)))
			वापस -EFAULT;
		अगर (features & ~VHOST_VSOCK_BACKEND_FEATURES)
			वापस -EOPNOTSUPP;
		vhost_set_backend_features(&vsock->dev, features);
		वापस 0;
	शेष:
		mutex_lock(&vsock->dev.mutex);
		r = vhost_dev_ioctl(&vsock->dev, ioctl, argp);
		अगर (r == -ENOIOCTLCMD)
			r = vhost_vring_ioctl(&vsock->dev, ioctl, argp);
		अन्यथा
			vhost_vsock_flush(vsock);
		mutex_unlock(&vsock->dev.mutex);
		वापस r;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार vhost_vsock_chr_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा vhost_vsock *vsock = file->निजी_data;
	काष्ठा vhost_dev *dev = &vsock->dev;
	पूर्णांक noblock = file->f_flags & O_NONBLOCK;

	वापस vhost_chr_पढ़ो_iter(dev, to, noblock);
पूर्ण

अटल sमाप_प्रकार vhost_vsock_chr_ग_लिखो_iter(काष्ठा kiocb *iocb,
					काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा vhost_vsock *vsock = file->निजी_data;
	काष्ठा vhost_dev *dev = &vsock->dev;

	वापस vhost_chr_ग_लिखो_iter(dev, from);
पूर्ण

अटल __poll_t vhost_vsock_chr_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा vhost_vsock *vsock = file->निजी_data;
	काष्ठा vhost_dev *dev = &vsock->dev;

	वापस vhost_chr_poll(file, dev, रुको);
पूर्ण

अटल स्थिर काष्ठा file_operations vhost_vsock_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो           = vhost_vsock_dev_खोलो,
	.release        = vhost_vsock_dev_release,
	.llseek		= noop_llseek,
	.unlocked_ioctl = vhost_vsock_dev_ioctl,
	.compat_ioctl   = compat_ptr_ioctl,
	.पढ़ो_iter      = vhost_vsock_chr_पढ़ो_iter,
	.ग_लिखो_iter     = vhost_vsock_chr_ग_लिखो_iter,
	.poll           = vhost_vsock_chr_poll,
पूर्ण;

अटल काष्ठा miscdevice vhost_vsock_misc = अणु
	.minor = VHOST_VSOCK_MINOR,
	.name = "vhost-vsock",
	.fops = &vhost_vsock_fops,
पूर्ण;

अटल पूर्णांक __init vhost_vsock_init(व्योम)
अणु
	पूर्णांक ret;

	ret = vsock_core_रेजिस्टर(&vhost_transport.transport,
				  VSOCK_TRANSPORT_F_H2G);
	अगर (ret < 0)
		वापस ret;
	वापस misc_रेजिस्टर(&vhost_vsock_misc);
पूर्ण;

अटल व्योम __निकास vhost_vsock_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&vhost_vsock_misc);
	vsock_core_unरेजिस्टर(&vhost_transport.transport);
पूर्ण;

module_init(vhost_vsock_init);
module_निकास(vhost_vsock_निकास);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Asias He");
MODULE_DESCRIPTION("vhost transport for vsock ");
MODULE_ALIAS_MISCDEV(VHOST_VSOCK_MINOR);
MODULE_ALIAS("devname:vhost-vsock");
