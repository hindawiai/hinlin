<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * common code क्रम virtio vsock
 *
 * Copyright (C) 2013-2015 Red Hat, Inc.
 * Author: Asias He <asias@redhat.com>
 *         Stefan Hajnoczi <stefanha@redhat.com>
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/list.h>
#समावेश <linux/virtio_vsock.h>
#समावेश <uapi/linux/vsockmon.h>

#समावेश <net/sock.h>
#समावेश <net/af_vsock.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/vsock_virtio_transport_common.h>

/* How दीर्घ to रुको क्रम graceful shutकरोwn of a connection */
#घोषणा VSOCK_CLOSE_TIMEOUT (8 * HZ)

/* Threshold क्रम detecting small packets to copy */
#घोषणा GOOD_COPY_LEN  128

अटल स्थिर काष्ठा virtio_transport *
virtio_transport_get_ops(काष्ठा vsock_sock *vsk)
अणु
	स्थिर काष्ठा vsock_transport *t = vsock_core_get_transport(vsk);

	अगर (WARN_ON(!t))
		वापस शून्य;

	वापस container_of(t, काष्ठा virtio_transport, transport);
पूर्ण

अटल काष्ठा virtio_vsock_pkt *
virtio_transport_alloc_pkt(काष्ठा virtio_vsock_pkt_info *info,
			   माप_प्रकार len,
			   u32 src_cid,
			   u32 src_port,
			   u32 dst_cid,
			   u32 dst_port)
अणु
	काष्ठा virtio_vsock_pkt *pkt;
	पूर्णांक err;

	pkt = kzalloc(माप(*pkt), GFP_KERNEL);
	अगर (!pkt)
		वापस शून्य;

	pkt->hdr.type		= cpu_to_le16(info->type);
	pkt->hdr.op		= cpu_to_le16(info->op);
	pkt->hdr.src_cid	= cpu_to_le64(src_cid);
	pkt->hdr.dst_cid	= cpu_to_le64(dst_cid);
	pkt->hdr.src_port	= cpu_to_le32(src_port);
	pkt->hdr.dst_port	= cpu_to_le32(dst_port);
	pkt->hdr.flags		= cpu_to_le32(info->flags);
	pkt->len		= len;
	pkt->hdr.len		= cpu_to_le32(len);
	pkt->reply		= info->reply;
	pkt->vsk		= info->vsk;

	अगर (info->msg && len > 0) अणु
		pkt->buf = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!pkt->buf)
			जाओ out_pkt;

		pkt->buf_len = len;

		err = स_नकल_from_msg(pkt->buf, info->msg, len);
		अगर (err)
			जाओ out;
	पूर्ण

	trace_virtio_transport_alloc_pkt(src_cid, src_port,
					 dst_cid, dst_port,
					 len,
					 info->type,
					 info->op,
					 info->flags);

	वापस pkt;

out:
	kमुक्त(pkt->buf);
out_pkt:
	kमुक्त(pkt);
	वापस शून्य;
पूर्ण

/* Packet capture */
अटल काष्ठा sk_buff *virtio_transport_build_skb(व्योम *opaque)
अणु
	काष्ठा virtio_vsock_pkt *pkt = opaque;
	काष्ठा af_vsockmon_hdr *hdr;
	काष्ठा sk_buff *skb;
	माप_प्रकार payload_len;
	व्योम *payload_buf;

	/* A packet could be split to fit the RX buffer, so we can retrieve
	 * the payload length from the header and the buffer poपूर्णांकer taking
	 * care of the offset in the original packet.
	 */
	payload_len = le32_to_cpu(pkt->hdr.len);
	payload_buf = pkt->buf + pkt->off;

	skb = alloc_skb(माप(*hdr) + माप(pkt->hdr) + payload_len,
			GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;

	hdr = skb_put(skb, माप(*hdr));

	/* pkt->hdr is little-endian so no need to byteswap here */
	hdr->src_cid = pkt->hdr.src_cid;
	hdr->src_port = pkt->hdr.src_port;
	hdr->dst_cid = pkt->hdr.dst_cid;
	hdr->dst_port = pkt->hdr.dst_port;

	hdr->transport = cpu_to_le16(AF_VSOCK_TRANSPORT_VIRTIO);
	hdr->len = cpu_to_le16(माप(pkt->hdr));
	स_रखो(hdr->reserved, 0, माप(hdr->reserved));

	चयन (le16_to_cpu(pkt->hdr.op)) अणु
	हाल VIRTIO_VSOCK_OP_REQUEST:
	हाल VIRTIO_VSOCK_OP_RESPONSE:
		hdr->op = cpu_to_le16(AF_VSOCK_OP_CONNECT);
		अवरोध;
	हाल VIRTIO_VSOCK_OP_RST:
	हाल VIRTIO_VSOCK_OP_SHUTDOWN:
		hdr->op = cpu_to_le16(AF_VSOCK_OP_DISCONNECT);
		अवरोध;
	हाल VIRTIO_VSOCK_OP_RW:
		hdr->op = cpu_to_le16(AF_VSOCK_OP_PAYLOAD);
		अवरोध;
	हाल VIRTIO_VSOCK_OP_CREDIT_UPDATE:
	हाल VIRTIO_VSOCK_OP_CREDIT_REQUEST:
		hdr->op = cpu_to_le16(AF_VSOCK_OP_CONTROL);
		अवरोध;
	शेष:
		hdr->op = cpu_to_le16(AF_VSOCK_OP_UNKNOWN);
		अवरोध;
	पूर्ण

	skb_put_data(skb, &pkt->hdr, माप(pkt->hdr));

	अगर (payload_len) अणु
		skb_put_data(skb, payload_buf, payload_len);
	पूर्ण

	वापस skb;
पूर्ण

व्योम virtio_transport_deliver_tap_pkt(काष्ठा virtio_vsock_pkt *pkt)
अणु
	अगर (pkt->tap_delivered)
		वापस;

	vsock_deliver_tap(virtio_transport_build_skb, pkt);
	pkt->tap_delivered = true;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_deliver_tap_pkt);

/* This function can only be used on connecting/connected sockets,
 * since a socket asचिन्हित to a transport is required.
 *
 * Do not use on listener sockets!
 */
अटल पूर्णांक virtio_transport_send_pkt_info(काष्ठा vsock_sock *vsk,
					  काष्ठा virtio_vsock_pkt_info *info)
अणु
	u32 src_cid, src_port, dst_cid, dst_port;
	स्थिर काष्ठा virtio_transport *t_ops;
	काष्ठा virtio_vsock_sock *vvs;
	काष्ठा virtio_vsock_pkt *pkt;
	u32 pkt_len = info->pkt_len;

	t_ops = virtio_transport_get_ops(vsk);
	अगर (unlikely(!t_ops))
		वापस -EFAULT;

	src_cid = t_ops->transport.get_local_cid();
	src_port = vsk->local_addr.svm_port;
	अगर (!info->remote_cid) अणु
		dst_cid	= vsk->remote_addr.svm_cid;
		dst_port = vsk->remote_addr.svm_port;
	पूर्ण अन्यथा अणु
		dst_cid = info->remote_cid;
		dst_port = info->remote_port;
	पूर्ण

	vvs = vsk->trans;

	/* we can send less than pkt_len bytes */
	अगर (pkt_len > VIRTIO_VSOCK_MAX_PKT_BUF_SIZE)
		pkt_len = VIRTIO_VSOCK_MAX_PKT_BUF_SIZE;

	/* virtio_transport_get_credit might वापस less than pkt_len credit */
	pkt_len = virtio_transport_get_credit(vvs, pkt_len);

	/* Do not send zero length OP_RW pkt */
	अगर (pkt_len == 0 && info->op == VIRTIO_VSOCK_OP_RW)
		वापस pkt_len;

	pkt = virtio_transport_alloc_pkt(info, pkt_len,
					 src_cid, src_port,
					 dst_cid, dst_port);
	अगर (!pkt) अणु
		virtio_transport_put_credit(vvs, pkt_len);
		वापस -ENOMEM;
	पूर्ण

	virtio_transport_inc_tx_pkt(vvs, pkt);

	वापस t_ops->send_pkt(pkt);
पूर्ण

अटल bool virtio_transport_inc_rx_pkt(काष्ठा virtio_vsock_sock *vvs,
					काष्ठा virtio_vsock_pkt *pkt)
अणु
	अगर (vvs->rx_bytes + pkt->len > vvs->buf_alloc)
		वापस false;

	vvs->rx_bytes += pkt->len;
	वापस true;
पूर्ण

अटल व्योम virtio_transport_dec_rx_pkt(काष्ठा virtio_vsock_sock *vvs,
					काष्ठा virtio_vsock_pkt *pkt)
अणु
	vvs->rx_bytes -= pkt->len;
	vvs->fwd_cnt += pkt->len;
पूर्ण

व्योम virtio_transport_inc_tx_pkt(काष्ठा virtio_vsock_sock *vvs, काष्ठा virtio_vsock_pkt *pkt)
अणु
	spin_lock_bh(&vvs->rx_lock);
	vvs->last_fwd_cnt = vvs->fwd_cnt;
	pkt->hdr.fwd_cnt = cpu_to_le32(vvs->fwd_cnt);
	pkt->hdr.buf_alloc = cpu_to_le32(vvs->buf_alloc);
	spin_unlock_bh(&vvs->rx_lock);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_inc_tx_pkt);

u32 virtio_transport_get_credit(काष्ठा virtio_vsock_sock *vvs, u32 credit)
अणु
	u32 ret;

	spin_lock_bh(&vvs->tx_lock);
	ret = vvs->peer_buf_alloc - (vvs->tx_cnt - vvs->peer_fwd_cnt);
	अगर (ret > credit)
		ret = credit;
	vvs->tx_cnt += ret;
	spin_unlock_bh(&vvs->tx_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_get_credit);

व्योम virtio_transport_put_credit(काष्ठा virtio_vsock_sock *vvs, u32 credit)
अणु
	spin_lock_bh(&vvs->tx_lock);
	vvs->tx_cnt -= credit;
	spin_unlock_bh(&vvs->tx_lock);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_put_credit);

अटल पूर्णांक virtio_transport_send_credit_update(काष्ठा vsock_sock *vsk,
					       पूर्णांक type,
					       काष्ठा virtio_vsock_hdr *hdr)
अणु
	काष्ठा virtio_vsock_pkt_info info = अणु
		.op = VIRTIO_VSOCK_OP_CREDIT_UPDATE,
		.type = type,
		.vsk = vsk,
	पूर्ण;

	वापस virtio_transport_send_pkt_info(vsk, &info);
पूर्ण

अटल sमाप_प्रकार
virtio_transport_stream_करो_peek(काष्ठा vsock_sock *vsk,
				काष्ठा msghdr *msg,
				माप_प्रकार len)
अणु
	काष्ठा virtio_vsock_sock *vvs = vsk->trans;
	काष्ठा virtio_vsock_pkt *pkt;
	माप_प्रकार bytes, total = 0, off;
	पूर्णांक err = -EFAULT;

	spin_lock_bh(&vvs->rx_lock);

	list_क्रम_each_entry(pkt, &vvs->rx_queue, list) अणु
		off = pkt->off;

		अगर (total == len)
			अवरोध;

		जबतक (total < len && off < pkt->len) अणु
			bytes = len - total;
			अगर (bytes > pkt->len - off)
				bytes = pkt->len - off;

			/* sk_lock is held by caller so no one अन्यथा can dequeue.
			 * Unlock rx_lock since स_नकल_to_msg() may sleep.
			 */
			spin_unlock_bh(&vvs->rx_lock);

			err = स_नकल_to_msg(msg, pkt->buf + off, bytes);
			अगर (err)
				जाओ out;

			spin_lock_bh(&vvs->rx_lock);

			total += bytes;
			off += bytes;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&vvs->rx_lock);

	वापस total;

out:
	अगर (total)
		err = total;
	वापस err;
पूर्ण

अटल sमाप_प्रकार
virtio_transport_stream_करो_dequeue(काष्ठा vsock_sock *vsk,
				   काष्ठा msghdr *msg,
				   माप_प्रकार len)
अणु
	काष्ठा virtio_vsock_sock *vvs = vsk->trans;
	काष्ठा virtio_vsock_pkt *pkt;
	माप_प्रकार bytes, total = 0;
	u32 मुक्त_space;
	पूर्णांक err = -EFAULT;

	spin_lock_bh(&vvs->rx_lock);
	जबतक (total < len && !list_empty(&vvs->rx_queue)) अणु
		pkt = list_first_entry(&vvs->rx_queue,
				       काष्ठा virtio_vsock_pkt, list);

		bytes = len - total;
		अगर (bytes > pkt->len - pkt->off)
			bytes = pkt->len - pkt->off;

		/* sk_lock is held by caller so no one अन्यथा can dequeue.
		 * Unlock rx_lock since स_नकल_to_msg() may sleep.
		 */
		spin_unlock_bh(&vvs->rx_lock);

		err = स_नकल_to_msg(msg, pkt->buf + pkt->off, bytes);
		अगर (err)
			जाओ out;

		spin_lock_bh(&vvs->rx_lock);

		total += bytes;
		pkt->off += bytes;
		अगर (pkt->off == pkt->len) अणु
			virtio_transport_dec_rx_pkt(vvs, pkt);
			list_del(&pkt->list);
			virtio_transport_मुक्त_pkt(pkt);
		पूर्ण
	पूर्ण

	मुक्त_space = vvs->buf_alloc - (vvs->fwd_cnt - vvs->last_fwd_cnt);

	spin_unlock_bh(&vvs->rx_lock);

	/* To reduce the number of credit update messages,
	 * करोn't update credits as दीर्घ as lots of space is available.
	 * Note: the limit chosen here is arbitrary. Setting the limit
	 * too high causes extra messages. Too low causes transmitter
	 * stalls. As stalls are in theory more expensive than extra
	 * messages, we set the limit to a high value. TODO: experiment
	 * with dअगरferent values.
	 */
	अगर (मुक्त_space < VIRTIO_VSOCK_MAX_PKT_BUF_SIZE) अणु
		virtio_transport_send_credit_update(vsk,
						    VIRTIO_VSOCK_TYPE_STREAM,
						    शून्य);
	पूर्ण

	वापस total;

out:
	अगर (total)
		err = total;
	वापस err;
पूर्ण

sमाप_प्रकार
virtio_transport_stream_dequeue(काष्ठा vsock_sock *vsk,
				काष्ठा msghdr *msg,
				माप_प्रकार len, पूर्णांक flags)
अणु
	अगर (flags & MSG_PEEK)
		वापस virtio_transport_stream_करो_peek(vsk, msg, len);
	अन्यथा
		वापस virtio_transport_stream_करो_dequeue(vsk, msg, len);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_stream_dequeue);

पूर्णांक
virtio_transport_dgram_dequeue(काष्ठा vsock_sock *vsk,
			       काष्ठा msghdr *msg,
			       माप_प्रकार len, पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_dgram_dequeue);

s64 virtio_transport_stream_has_data(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा virtio_vsock_sock *vvs = vsk->trans;
	s64 bytes;

	spin_lock_bh(&vvs->rx_lock);
	bytes = vvs->rx_bytes;
	spin_unlock_bh(&vvs->rx_lock);

	वापस bytes;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_stream_has_data);

अटल s64 virtio_transport_has_space(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा virtio_vsock_sock *vvs = vsk->trans;
	s64 bytes;

	bytes = vvs->peer_buf_alloc - (vvs->tx_cnt - vvs->peer_fwd_cnt);
	अगर (bytes < 0)
		bytes = 0;

	वापस bytes;
पूर्ण

s64 virtio_transport_stream_has_space(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा virtio_vsock_sock *vvs = vsk->trans;
	s64 bytes;

	spin_lock_bh(&vvs->tx_lock);
	bytes = virtio_transport_has_space(vsk);
	spin_unlock_bh(&vvs->tx_lock);

	वापस bytes;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_stream_has_space);

पूर्णांक virtio_transport_करो_socket_init(काष्ठा vsock_sock *vsk,
				    काष्ठा vsock_sock *psk)
अणु
	काष्ठा virtio_vsock_sock *vvs;

	vvs = kzalloc(माप(*vvs), GFP_KERNEL);
	अगर (!vvs)
		वापस -ENOMEM;

	vsk->trans = vvs;
	vvs->vsk = vsk;
	अगर (psk && psk->trans) अणु
		काष्ठा virtio_vsock_sock *ptrans = psk->trans;

		vvs->peer_buf_alloc = ptrans->peer_buf_alloc;
	पूर्ण

	अगर (vsk->buffer_size > VIRTIO_VSOCK_MAX_BUF_SIZE)
		vsk->buffer_size = VIRTIO_VSOCK_MAX_BUF_SIZE;

	vvs->buf_alloc = vsk->buffer_size;

	spin_lock_init(&vvs->rx_lock);
	spin_lock_init(&vvs->tx_lock);
	INIT_LIST_HEAD(&vvs->rx_queue);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_करो_socket_init);

/* sk_lock held by the caller */
व्योम virtio_transport_notअगरy_buffer_size(काष्ठा vsock_sock *vsk, u64 *val)
अणु
	काष्ठा virtio_vsock_sock *vvs = vsk->trans;

	अगर (*val > VIRTIO_VSOCK_MAX_BUF_SIZE)
		*val = VIRTIO_VSOCK_MAX_BUF_SIZE;

	vvs->buf_alloc = *val;

	virtio_transport_send_credit_update(vsk, VIRTIO_VSOCK_TYPE_STREAM,
					    शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_buffer_size);

पूर्णांक
virtio_transport_notअगरy_poll_in(काष्ठा vsock_sock *vsk,
				माप_प्रकार target,
				bool *data_पढ़ोy_now)
अणु
	अगर (vsock_stream_has_data(vsk))
		*data_पढ़ोy_now = true;
	अन्यथा
		*data_पढ़ोy_now = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_poll_in);

पूर्णांक
virtio_transport_notअगरy_poll_out(काष्ठा vsock_sock *vsk,
				 माप_प्रकार target,
				 bool *space_avail_now)
अणु
	s64 मुक्त_space;

	मुक्त_space = vsock_stream_has_space(vsk);
	अगर (मुक्त_space > 0)
		*space_avail_now = true;
	अन्यथा अगर (मुक्त_space == 0)
		*space_avail_now = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_poll_out);

पूर्णांक virtio_transport_notअगरy_recv_init(काष्ठा vsock_sock *vsk,
	माप_प्रकार target, काष्ठा vsock_transport_recv_notअगरy_data *data)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_recv_init);

पूर्णांक virtio_transport_notअगरy_recv_pre_block(काष्ठा vsock_sock *vsk,
	माप_प्रकार target, काष्ठा vsock_transport_recv_notअगरy_data *data)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_recv_pre_block);

पूर्णांक virtio_transport_notअगरy_recv_pre_dequeue(काष्ठा vsock_sock *vsk,
	माप_प्रकार target, काष्ठा vsock_transport_recv_notअगरy_data *data)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_recv_pre_dequeue);

पूर्णांक virtio_transport_notअगरy_recv_post_dequeue(काष्ठा vsock_sock *vsk,
	माप_प्रकार target, sमाप_प्रकार copied, bool data_पढ़ो,
	काष्ठा vsock_transport_recv_notअगरy_data *data)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_recv_post_dequeue);

पूर्णांक virtio_transport_notअगरy_send_init(काष्ठा vsock_sock *vsk,
	काष्ठा vsock_transport_send_notअगरy_data *data)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_send_init);

पूर्णांक virtio_transport_notअगरy_send_pre_block(काष्ठा vsock_sock *vsk,
	काष्ठा vsock_transport_send_notअगरy_data *data)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_send_pre_block);

पूर्णांक virtio_transport_notअगरy_send_pre_enqueue(काष्ठा vsock_sock *vsk,
	काष्ठा vsock_transport_send_notअगरy_data *data)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_send_pre_enqueue);

पूर्णांक virtio_transport_notअगरy_send_post_enqueue(काष्ठा vsock_sock *vsk,
	sमाप_प्रकार written, काष्ठा vsock_transport_send_notअगरy_data *data)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_notअगरy_send_post_enqueue);

u64 virtio_transport_stream_rcvhiwat(काष्ठा vsock_sock *vsk)
अणु
	वापस vsk->buffer_size;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_stream_rcvhiwat);

bool virtio_transport_stream_is_active(काष्ठा vsock_sock *vsk)
अणु
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_stream_is_active);

bool virtio_transport_stream_allow(u32 cid, u32 port)
अणु
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_stream_allow);

पूर्णांक virtio_transport_dgram_bind(काष्ठा vsock_sock *vsk,
				काष्ठा sockaddr_vm *addr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_dgram_bind);

bool virtio_transport_dgram_allow(u32 cid, u32 port)
अणु
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_dgram_allow);

पूर्णांक virtio_transport_connect(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा virtio_vsock_pkt_info info = अणु
		.op = VIRTIO_VSOCK_OP_REQUEST,
		.type = VIRTIO_VSOCK_TYPE_STREAM,
		.vsk = vsk,
	पूर्ण;

	वापस virtio_transport_send_pkt_info(vsk, &info);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_connect);

पूर्णांक virtio_transport_shutकरोwn(काष्ठा vsock_sock *vsk, पूर्णांक mode)
अणु
	काष्ठा virtio_vsock_pkt_info info = अणु
		.op = VIRTIO_VSOCK_OP_SHUTDOWN,
		.type = VIRTIO_VSOCK_TYPE_STREAM,
		.flags = (mode & RCV_SHUTDOWN ?
			  VIRTIO_VSOCK_SHUTDOWN_RCV : 0) |
			 (mode & SEND_SHUTDOWN ?
			  VIRTIO_VSOCK_SHUTDOWN_SEND : 0),
		.vsk = vsk,
	पूर्ण;

	वापस virtio_transport_send_pkt_info(vsk, &info);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_shutकरोwn);

पूर्णांक
virtio_transport_dgram_enqueue(काष्ठा vsock_sock *vsk,
			       काष्ठा sockaddr_vm *remote_addr,
			       काष्ठा msghdr *msg,
			       माप_प्रकार dgram_len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_dgram_enqueue);

sमाप_प्रकार
virtio_transport_stream_enqueue(काष्ठा vsock_sock *vsk,
				काष्ठा msghdr *msg,
				माप_प्रकार len)
अणु
	काष्ठा virtio_vsock_pkt_info info = अणु
		.op = VIRTIO_VSOCK_OP_RW,
		.type = VIRTIO_VSOCK_TYPE_STREAM,
		.msg = msg,
		.pkt_len = len,
		.vsk = vsk,
	पूर्ण;

	वापस virtio_transport_send_pkt_info(vsk, &info);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_stream_enqueue);

व्योम virtio_transport_deकाष्ठा(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा virtio_vsock_sock *vvs = vsk->trans;

	kमुक्त(vvs);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_deकाष्ठा);

अटल पूर्णांक virtio_transport_reset(काष्ठा vsock_sock *vsk,
				  काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा virtio_vsock_pkt_info info = अणु
		.op = VIRTIO_VSOCK_OP_RST,
		.type = VIRTIO_VSOCK_TYPE_STREAM,
		.reply = !!pkt,
		.vsk = vsk,
	पूर्ण;

	/* Send RST only अगर the original pkt is not a RST pkt */
	अगर (pkt && le16_to_cpu(pkt->hdr.op) == VIRTIO_VSOCK_OP_RST)
		वापस 0;

	वापस virtio_transport_send_pkt_info(vsk, &info);
पूर्ण

/* Normally packets are associated with a socket.  There may be no socket अगर an
 * attempt was made to connect to a socket that करोes not exist.
 */
अटल पूर्णांक virtio_transport_reset_no_sock(स्थिर काष्ठा virtio_transport *t,
					  काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा virtio_vsock_pkt *reply;
	काष्ठा virtio_vsock_pkt_info info = अणु
		.op = VIRTIO_VSOCK_OP_RST,
		.type = le16_to_cpu(pkt->hdr.type),
		.reply = true,
	पूर्ण;

	/* Send RST only अगर the original pkt is not a RST pkt */
	अगर (le16_to_cpu(pkt->hdr.op) == VIRTIO_VSOCK_OP_RST)
		वापस 0;

	reply = virtio_transport_alloc_pkt(&info, 0,
					   le64_to_cpu(pkt->hdr.dst_cid),
					   le32_to_cpu(pkt->hdr.dst_port),
					   le64_to_cpu(pkt->hdr.src_cid),
					   le32_to_cpu(pkt->hdr.src_port));
	अगर (!reply)
		वापस -ENOMEM;

	अगर (!t) अणु
		virtio_transport_मुक्त_pkt(reply);
		वापस -ENOTCONN;
	पूर्ण

	वापस t->send_pkt(reply);
पूर्ण

/* This function should be called with sk_lock held and SOCK_DONE set */
अटल व्योम virtio_transport_हटाओ_sock(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा virtio_vsock_sock *vvs = vsk->trans;
	काष्ठा virtio_vsock_pkt *pkt, *पंचांगp;

	/* We करोn't need to take rx_lock, as the socket is closing and we are
	 * removing it.
	 */
	list_क्रम_each_entry_safe(pkt, पंचांगp, &vvs->rx_queue, list) अणु
		list_del(&pkt->list);
		virtio_transport_मुक्त_pkt(pkt);
	पूर्ण

	vsock_हटाओ_sock(vsk);
पूर्ण

अटल व्योम virtio_transport_रुको_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	अगर (समयout) अणु
		DEFINE_WAIT_FUNC(रुको, woken_wake_function);

		add_रुको_queue(sk_sleep(sk), &रुको);

		करो अणु
			अगर (sk_रुको_event(sk, &समयout,
					  sock_flag(sk, SOCK_DONE), &रुको))
				अवरोध;
		पूर्ण जबतक (!संकेत_pending(current) && समयout);

		हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	पूर्ण
पूर्ण

अटल व्योम virtio_transport_करो_बंद(काष्ठा vsock_sock *vsk,
				      bool cancel_समयout)
अणु
	काष्ठा sock *sk = sk_vsock(vsk);

	sock_set_flag(sk, SOCK_DONE);
	vsk->peer_shutकरोwn = SHUTDOWN_MASK;
	अगर (vsock_stream_has_data(vsk) <= 0)
		sk->sk_state = TCP_CLOSING;
	sk->sk_state_change(sk);

	अगर (vsk->बंद_work_scheduled &&
	    (!cancel_समयout || cancel_delayed_work(&vsk->बंद_work))) अणु
		vsk->बंद_work_scheduled = false;

		virtio_transport_हटाओ_sock(vsk);

		/* Release refcnt obtained when we scheduled the समयout */
		sock_put(sk);
	पूर्ण
पूर्ण

अटल व्योम virtio_transport_बंद_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vsock_sock *vsk =
		container_of(work, काष्ठा vsock_sock, बंद_work.work);
	काष्ठा sock *sk = sk_vsock(vsk);

	sock_hold(sk);
	lock_sock(sk);

	अगर (!sock_flag(sk, SOCK_DONE)) अणु
		(व्योम)virtio_transport_reset(vsk, शून्य);

		virtio_transport_करो_बंद(vsk, false);
	पूर्ण

	vsk->बंद_work_scheduled = false;

	release_sock(sk);
	sock_put(sk);
पूर्ण

/* User context, vsk->sk is locked */
अटल bool virtio_transport_बंद(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा sock *sk = &vsk->sk;

	अगर (!(sk->sk_state == TCP_ESTABLISHED ||
	      sk->sk_state == TCP_CLOSING))
		वापस true;

	/* Alपढ़ोy received SHUTDOWN from peer, reply with RST */
	अगर ((vsk->peer_shutकरोwn & SHUTDOWN_MASK) == SHUTDOWN_MASK) अणु
		(व्योम)virtio_transport_reset(vsk, शून्य);
		वापस true;
	पूर्ण

	अगर ((sk->sk_shutकरोwn & SHUTDOWN_MASK) != SHUTDOWN_MASK)
		(व्योम)virtio_transport_shutकरोwn(vsk, SHUTDOWN_MASK);

	अगर (sock_flag(sk, SOCK_LINGER) && !(current->flags & PF_EXITING))
		virtio_transport_रुको_बंद(sk, sk->sk_lingerसमय);

	अगर (sock_flag(sk, SOCK_DONE)) अणु
		वापस true;
	पूर्ण

	sock_hold(sk);
	INIT_DELAYED_WORK(&vsk->बंद_work,
			  virtio_transport_बंद_समयout);
	vsk->बंद_work_scheduled = true;
	schedule_delayed_work(&vsk->बंद_work, VSOCK_CLOSE_TIMEOUT);
	वापस false;
पूर्ण

व्योम virtio_transport_release(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा sock *sk = &vsk->sk;
	bool हटाओ_sock = true;

	अगर (sk->sk_type == SOCK_STREAM)
		हटाओ_sock = virtio_transport_बंद(vsk);

	अगर (हटाओ_sock) अणु
		sock_set_flag(sk, SOCK_DONE);
		virtio_transport_हटाओ_sock(vsk);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_release);

अटल पूर्णांक
virtio_transport_recv_connecting(काष्ठा sock *sk,
				 काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);
	पूर्णांक err;
	पूर्णांक skerr;

	चयन (le16_to_cpu(pkt->hdr.op)) अणु
	हाल VIRTIO_VSOCK_OP_RESPONSE:
		sk->sk_state = TCP_ESTABLISHED;
		sk->sk_socket->state = SS_CONNECTED;
		vsock_insert_connected(vsk);
		sk->sk_state_change(sk);
		अवरोध;
	हाल VIRTIO_VSOCK_OP_INVALID:
		अवरोध;
	हाल VIRTIO_VSOCK_OP_RST:
		skerr = ECONNRESET;
		err = 0;
		जाओ destroy;
	शेष:
		skerr = EPROTO;
		err = -EINVAL;
		जाओ destroy;
	पूर्ण
	वापस 0;

destroy:
	virtio_transport_reset(vsk, pkt);
	sk->sk_state = TCP_CLOSE;
	sk->sk_err = skerr;
	sk->sk_error_report(sk);
	वापस err;
पूर्ण

अटल व्योम
virtio_transport_recv_enqueue(काष्ठा vsock_sock *vsk,
			      काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा virtio_vsock_sock *vvs = vsk->trans;
	bool can_enqueue, मुक्त_pkt = false;

	pkt->len = le32_to_cpu(pkt->hdr.len);
	pkt->off = 0;

	spin_lock_bh(&vvs->rx_lock);

	can_enqueue = virtio_transport_inc_rx_pkt(vvs, pkt);
	अगर (!can_enqueue) अणु
		मुक्त_pkt = true;
		जाओ out;
	पूर्ण

	/* Try to copy small packets पूर्णांकo the buffer of last packet queued,
	 * to aव्योम wasting memory queueing the entire buffer with a small
	 * payload.
	 */
	अगर (pkt->len <= GOOD_COPY_LEN && !list_empty(&vvs->rx_queue)) अणु
		काष्ठा virtio_vsock_pkt *last_pkt;

		last_pkt = list_last_entry(&vvs->rx_queue,
					   काष्ठा virtio_vsock_pkt, list);

		/* If there is space in the last packet queued, we copy the
		 * new packet in its buffer.
		 */
		अगर (pkt->len <= last_pkt->buf_len - last_pkt->len) अणु
			स_नकल(last_pkt->buf + last_pkt->len, pkt->buf,
			       pkt->len);
			last_pkt->len += pkt->len;
			मुक्त_pkt = true;
			जाओ out;
		पूर्ण
	पूर्ण

	list_add_tail(&pkt->list, &vvs->rx_queue);

out:
	spin_unlock_bh(&vvs->rx_lock);
	अगर (मुक्त_pkt)
		virtio_transport_मुक्त_pkt(pkt);
पूर्ण

अटल पूर्णांक
virtio_transport_recv_connected(काष्ठा sock *sk,
				काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);
	पूर्णांक err = 0;

	चयन (le16_to_cpu(pkt->hdr.op)) अणु
	हाल VIRTIO_VSOCK_OP_RW:
		virtio_transport_recv_enqueue(vsk, pkt);
		sk->sk_data_पढ़ोy(sk);
		वापस err;
	हाल VIRTIO_VSOCK_OP_CREDIT_UPDATE:
		sk->sk_ग_लिखो_space(sk);
		अवरोध;
	हाल VIRTIO_VSOCK_OP_SHUTDOWN:
		अगर (le32_to_cpu(pkt->hdr.flags) & VIRTIO_VSOCK_SHUTDOWN_RCV)
			vsk->peer_shutकरोwn |= RCV_SHUTDOWN;
		अगर (le32_to_cpu(pkt->hdr.flags) & VIRTIO_VSOCK_SHUTDOWN_SEND)
			vsk->peer_shutकरोwn |= SEND_SHUTDOWN;
		अगर (vsk->peer_shutकरोwn == SHUTDOWN_MASK &&
		    vsock_stream_has_data(vsk) <= 0 &&
		    !sock_flag(sk, SOCK_DONE)) अणु
			(व्योम)virtio_transport_reset(vsk, शून्य);

			virtio_transport_करो_बंद(vsk, true);
		पूर्ण
		अगर (le32_to_cpu(pkt->hdr.flags))
			sk->sk_state_change(sk);
		अवरोध;
	हाल VIRTIO_VSOCK_OP_RST:
		virtio_transport_करो_बंद(vsk, true);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	virtio_transport_मुक्त_pkt(pkt);
	वापस err;
पूर्ण

अटल व्योम
virtio_transport_recv_disconnecting(काष्ठा sock *sk,
				    काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	अगर (le16_to_cpu(pkt->hdr.op) == VIRTIO_VSOCK_OP_RST)
		virtio_transport_करो_बंद(vsk, true);
पूर्ण

अटल पूर्णांक
virtio_transport_send_response(काष्ठा vsock_sock *vsk,
			       काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा virtio_vsock_pkt_info info = अणु
		.op = VIRTIO_VSOCK_OP_RESPONSE,
		.type = VIRTIO_VSOCK_TYPE_STREAM,
		.remote_cid = le64_to_cpu(pkt->hdr.src_cid),
		.remote_port = le32_to_cpu(pkt->hdr.src_port),
		.reply = true,
		.vsk = vsk,
	पूर्ण;

	वापस virtio_transport_send_pkt_info(vsk, &info);
पूर्ण

अटल bool virtio_transport_space_update(काष्ठा sock *sk,
					  काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);
	काष्ठा virtio_vsock_sock *vvs = vsk->trans;
	bool space_available;

	/* Listener sockets are not associated with any transport, so we are
	 * not able to take the state to see अगर there is space available in the
	 * remote peer, but since they are only used to receive requests, we
	 * can assume that there is always space available in the other peer.
	 */
	अगर (!vvs)
		वापस true;

	/* buf_alloc and fwd_cnt is always included in the hdr */
	spin_lock_bh(&vvs->tx_lock);
	vvs->peer_buf_alloc = le32_to_cpu(pkt->hdr.buf_alloc);
	vvs->peer_fwd_cnt = le32_to_cpu(pkt->hdr.fwd_cnt);
	space_available = virtio_transport_has_space(vsk);
	spin_unlock_bh(&vvs->tx_lock);
	वापस space_available;
पूर्ण

/* Handle server socket */
अटल पूर्णांक
virtio_transport_recv_listen(काष्ठा sock *sk, काष्ठा virtio_vsock_pkt *pkt,
			     काष्ठा virtio_transport *t)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);
	काष्ठा vsock_sock *vchild;
	काष्ठा sock *child;
	पूर्णांक ret;

	अगर (le16_to_cpu(pkt->hdr.op) != VIRTIO_VSOCK_OP_REQUEST) अणु
		virtio_transport_reset_no_sock(t, pkt);
		वापस -EINVAL;
	पूर्ण

	अगर (sk_acceptq_is_full(sk)) अणु
		virtio_transport_reset_no_sock(t, pkt);
		वापस -ENOMEM;
	पूर्ण

	child = vsock_create_connected(sk);
	अगर (!child) अणु
		virtio_transport_reset_no_sock(t, pkt);
		वापस -ENOMEM;
	पूर्ण

	sk_acceptq_added(sk);

	lock_sock_nested(child, SINGLE_DEPTH_NESTING);

	child->sk_state = TCP_ESTABLISHED;

	vchild = vsock_sk(child);
	vsock_addr_init(&vchild->local_addr, le64_to_cpu(pkt->hdr.dst_cid),
			le32_to_cpu(pkt->hdr.dst_port));
	vsock_addr_init(&vchild->remote_addr, le64_to_cpu(pkt->hdr.src_cid),
			le32_to_cpu(pkt->hdr.src_port));

	ret = vsock_assign_transport(vchild, vsk);
	/* Transport asचिन्हित (looking at remote_addr) must be the same
	 * where we received the request.
	 */
	अगर (ret || vchild->transport != &t->transport) अणु
		release_sock(child);
		virtio_transport_reset_no_sock(t, pkt);
		sock_put(child);
		वापस ret;
	पूर्ण

	अगर (virtio_transport_space_update(child, pkt))
		child->sk_ग_लिखो_space(child);

	vsock_insert_connected(vchild);
	vsock_enqueue_accept(sk, child);
	virtio_transport_send_response(vchild, pkt);

	release_sock(child);

	sk->sk_data_पढ़ोy(sk);
	वापस 0;
पूर्ण

/* We are under the virtio-vsock's vsock->rx_lock or vhost-vsock's vq->mutex
 * lock.
 */
व्योम virtio_transport_recv_pkt(काष्ठा virtio_transport *t,
			       काष्ठा virtio_vsock_pkt *pkt)
अणु
	काष्ठा sockaddr_vm src, dst;
	काष्ठा vsock_sock *vsk;
	काष्ठा sock *sk;
	bool space_available;

	vsock_addr_init(&src, le64_to_cpu(pkt->hdr.src_cid),
			le32_to_cpu(pkt->hdr.src_port));
	vsock_addr_init(&dst, le64_to_cpu(pkt->hdr.dst_cid),
			le32_to_cpu(pkt->hdr.dst_port));

	trace_virtio_transport_recv_pkt(src.svm_cid, src.svm_port,
					dst.svm_cid, dst.svm_port,
					le32_to_cpu(pkt->hdr.len),
					le16_to_cpu(pkt->hdr.type),
					le16_to_cpu(pkt->hdr.op),
					le32_to_cpu(pkt->hdr.flags),
					le32_to_cpu(pkt->hdr.buf_alloc),
					le32_to_cpu(pkt->hdr.fwd_cnt));

	अगर (le16_to_cpu(pkt->hdr.type) != VIRTIO_VSOCK_TYPE_STREAM) अणु
		(व्योम)virtio_transport_reset_no_sock(t, pkt);
		जाओ मुक्त_pkt;
	पूर्ण

	/* The socket must be in connected or bound table
	 * otherwise send reset back
	 */
	sk = vsock_find_connected_socket(&src, &dst);
	अगर (!sk) अणु
		sk = vsock_find_bound_socket(&dst);
		अगर (!sk) अणु
			(व्योम)virtio_transport_reset_no_sock(t, pkt);
			जाओ मुक्त_pkt;
		पूर्ण
	पूर्ण

	vsk = vsock_sk(sk);

	lock_sock(sk);

	/* Check अगर sk has been बंदd beक्रमe lock_sock */
	अगर (sock_flag(sk, SOCK_DONE)) अणु
		(व्योम)virtio_transport_reset_no_sock(t, pkt);
		release_sock(sk);
		sock_put(sk);
		जाओ मुक्त_pkt;
	पूर्ण

	space_available = virtio_transport_space_update(sk, pkt);

	/* Update CID in हाल it has changed after a transport reset event */
	vsk->local_addr.svm_cid = dst.svm_cid;

	अगर (space_available)
		sk->sk_ग_लिखो_space(sk);

	चयन (sk->sk_state) अणु
	हाल TCP_LISTEN:
		virtio_transport_recv_listen(sk, pkt, t);
		virtio_transport_मुक्त_pkt(pkt);
		अवरोध;
	हाल TCP_SYN_SENT:
		virtio_transport_recv_connecting(sk, pkt);
		virtio_transport_मुक्त_pkt(pkt);
		अवरोध;
	हाल TCP_ESTABLISHED:
		virtio_transport_recv_connected(sk, pkt);
		अवरोध;
	हाल TCP_CLOSING:
		virtio_transport_recv_disconnecting(sk, pkt);
		virtio_transport_मुक्त_pkt(pkt);
		अवरोध;
	शेष:
		(व्योम)virtio_transport_reset_no_sock(t, pkt);
		virtio_transport_मुक्त_pkt(pkt);
		अवरोध;
	पूर्ण

	release_sock(sk);

	/* Release refcnt obtained when we fetched this socket out of the
	 * bound or connected list.
	 */
	sock_put(sk);
	वापस;

मुक्त_pkt:
	virtio_transport_मुक्त_pkt(pkt);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_recv_pkt);

व्योम virtio_transport_मुक्त_pkt(काष्ठा virtio_vsock_pkt *pkt)
अणु
	kमुक्त(pkt->buf);
	kमुक्त(pkt);
पूर्ण
EXPORT_SYMBOL_GPL(virtio_transport_मुक्त_pkt);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Asias He");
MODULE_DESCRIPTION("common code for virtio vsock");
