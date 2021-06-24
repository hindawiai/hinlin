<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* loopback transport क्रम vsock using virtio_transport_common APIs
 *
 * Copyright (C) 2013-2019 Red Hat, Inc.
 * Authors: Asias He <asias@redhat.com>
 *          Stefan Hajnoczi <stefanha@redhat.com>
 *          Stefano Garzarella <sgarzare@redhat.com>
 *
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/virtio_vsock.h>

काष्ठा vsock_loopback अणु
	काष्ठा workqueue_काष्ठा *workqueue;

	spinlock_t pkt_list_lock; /* protects pkt_list */
	काष्ठा list_head pkt_list;
	काष्ठा work_काष्ठा pkt_work;
पूर्ण;

अटल काष्ठा vsock_loopback the_vsock_loopback;

अटल u32 vsock_loopback_get_local_cid(व्योम)
अणु
	वापस VMADDR_CID_LOCAL;
पूर्ण

अटल पूर्णांक vsock_loopback_send_pkt(काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा vsock_loopback *vsock = &the_vsock_loopback;
	पूर्णांक len = pkt->len;

	spin_lock_bh(&vsock->pkt_list_lock);
	list_add_tail(&pkt->list, &vsock->pkt_list);
	spin_unlock_bh(&vsock->pkt_list_lock);

	queue_work(vsock->workqueue, &vsock->pkt_work);

	वापस len;
पूर्ण

अटल पूर्णांक vsock_loopback_cancel_pkt(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा vsock_loopback *vsock = &the_vsock_loopback;
	काष्ठा virtio_vsock_pkt *pkt, *n;
	LIST_HEAD(मुक्तme);

	spin_lock_bh(&vsock->pkt_list_lock);
	list_क्रम_each_entry_safe(pkt, n, &vsock->pkt_list, list) अणु
		अगर (pkt->vsk != vsk)
			जारी;
		list_move(&pkt->list, &मुक्तme);
	पूर्ण
	spin_unlock_bh(&vsock->pkt_list_lock);

	list_क्रम_each_entry_safe(pkt, n, &मुक्तme, list) अणु
		list_del(&pkt->list);
		virtio_transport_मुक्त_pkt(pkt);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा virtio_transport loopback_transport = अणु
	.transport = अणु
		.module                   = THIS_MODULE,

		.get_local_cid            = vsock_loopback_get_local_cid,

		.init                     = virtio_transport_करो_socket_init,
		.deकाष्ठा                 = virtio_transport_deकाष्ठा,
		.release                  = virtio_transport_release,
		.connect                  = virtio_transport_connect,
		.shutकरोwn                 = virtio_transport_shutकरोwn,
		.cancel_pkt               = vsock_loopback_cancel_pkt,

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

	.send_pkt = vsock_loopback_send_pkt,
पूर्ण;

अटल व्योम vsock_loopback_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vsock_loopback *vsock =
		container_of(work, काष्ठा vsock_loopback, pkt_work);
	LIST_HEAD(pkts);

	spin_lock_bh(&vsock->pkt_list_lock);
	list_splice_init(&vsock->pkt_list, &pkts);
	spin_unlock_bh(&vsock->pkt_list_lock);

	जबतक (!list_empty(&pkts)) अणु
		काष्ठा virtio_vsock_pkt *pkt;

		pkt = list_first_entry(&pkts, काष्ठा virtio_vsock_pkt, list);
		list_del_init(&pkt->list);

		virtio_transport_deliver_tap_pkt(pkt);
		virtio_transport_recv_pkt(&loopback_transport, pkt);
	पूर्ण
पूर्ण

अटल पूर्णांक __init vsock_loopback_init(व्योम)
अणु
	काष्ठा vsock_loopback *vsock = &the_vsock_loopback;
	पूर्णांक ret;

	vsock->workqueue = alloc_workqueue("vsock-loopback", 0, 0);
	अगर (!vsock->workqueue)
		वापस -ENOMEM;

	spin_lock_init(&vsock->pkt_list_lock);
	INIT_LIST_HEAD(&vsock->pkt_list);
	INIT_WORK(&vsock->pkt_work, vsock_loopback_work);

	ret = vsock_core_रेजिस्टर(&loopback_transport.transport,
				  VSOCK_TRANSPORT_F_LOCAL);
	अगर (ret)
		जाओ out_wq;

	वापस 0;

out_wq:
	destroy_workqueue(vsock->workqueue);
	वापस ret;
पूर्ण

अटल व्योम __निकास vsock_loopback_निकास(व्योम)
अणु
	काष्ठा vsock_loopback *vsock = &the_vsock_loopback;
	काष्ठा virtio_vsock_pkt *pkt;

	vsock_core_unरेजिस्टर(&loopback_transport.transport);

	flush_work(&vsock->pkt_work);

	spin_lock_bh(&vsock->pkt_list_lock);
	जबतक (!list_empty(&vsock->pkt_list)) अणु
		pkt = list_first_entry(&vsock->pkt_list,
				       काष्ठा virtio_vsock_pkt, list);
		list_del(&pkt->list);
		virtio_transport_मुक्त_pkt(pkt);
	पूर्ण
	spin_unlock_bh(&vsock->pkt_list_lock);

	destroy_workqueue(vsock->workqueue);
पूर्ण

module_init(vsock_loopback_init);
module_निकास(vsock_loopback_निकास);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Stefano Garzarella <sgarzare@redhat.com>");
MODULE_DESCRIPTION("loopback transport for vsock");
MODULE_ALIAS_NETPROTO(PF_VSOCK);
