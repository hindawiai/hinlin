<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VIRTIO_VSOCK_H
#घोषणा _LINUX_VIRTIO_VSOCK_H

#समावेश <uapi/linux/virtio_vsock.h>
#समावेश <linux/socket.h>
#समावेश <net/sock.h>
#समावेश <net/af_vsock.h>

#घोषणा VIRTIO_VSOCK_DEFAULT_RX_BUF_SIZE	(1024 * 4)
#घोषणा VIRTIO_VSOCK_MAX_BUF_SIZE		0xFFFFFFFFUL
#घोषणा VIRTIO_VSOCK_MAX_PKT_BUF_SIZE		(1024 * 64)

क्रमागत अणु
	VSOCK_VQ_RX     = 0, /* क्रम host to guest data */
	VSOCK_VQ_TX     = 1, /* क्रम guest to host data */
	VSOCK_VQ_EVENT  = 2,
	VSOCK_VQ_MAX    = 3,
पूर्ण;

/* Per-socket state (accessed via vsk->trans) */
काष्ठा virtio_vsock_sock अणु
	काष्ठा vsock_sock *vsk;

	spinlock_t tx_lock;
	spinlock_t rx_lock;

	/* Protected by tx_lock */
	u32 tx_cnt;
	u32 peer_fwd_cnt;
	u32 peer_buf_alloc;

	/* Protected by rx_lock */
	u32 fwd_cnt;
	u32 last_fwd_cnt;
	u32 rx_bytes;
	u32 buf_alloc;
	काष्ठा list_head rx_queue;
पूर्ण;

काष्ठा virtio_vsock_pkt अणु
	काष्ठा virtio_vsock_hdr	hdr;
	काष्ठा list_head list;
	/* socket refcnt not held, only use क्रम cancellation */
	काष्ठा vsock_sock *vsk;
	व्योम *buf;
	u32 buf_len;
	u32 len;
	u32 off;
	bool reply;
	bool tap_delivered;
पूर्ण;

काष्ठा virtio_vsock_pkt_info अणु
	u32 remote_cid, remote_port;
	काष्ठा vsock_sock *vsk;
	काष्ठा msghdr *msg;
	u32 pkt_len;
	u16 type;
	u16 op;
	u32 flags;
	bool reply;
पूर्ण;

काष्ठा virtio_transport अणु
	/* This must be the first field */
	काष्ठा vsock_transport transport;

	/* Takes ownership of the packet */
	पूर्णांक (*send_pkt)(काष्ठा virtio_vsock_pkt *pkt);
पूर्ण;

sमाप_प्रकार
virtio_transport_stream_dequeue(काष्ठा vsock_sock *vsk,
				काष्ठा msghdr *msg,
				माप_प्रकार len,
				पूर्णांक type);
पूर्णांक
virtio_transport_dgram_dequeue(काष्ठा vsock_sock *vsk,
			       काष्ठा msghdr *msg,
			       माप_प्रकार len, पूर्णांक flags);

s64 virtio_transport_stream_has_data(काष्ठा vsock_sock *vsk);
s64 virtio_transport_stream_has_space(काष्ठा vsock_sock *vsk);

पूर्णांक virtio_transport_करो_socket_init(काष्ठा vsock_sock *vsk,
				 काष्ठा vsock_sock *psk);
पूर्णांक
virtio_transport_notअगरy_poll_in(काष्ठा vsock_sock *vsk,
				माप_प्रकार target,
				bool *data_पढ़ोy_now);
पूर्णांक
virtio_transport_notअगरy_poll_out(काष्ठा vsock_sock *vsk,
				 माप_प्रकार target,
				 bool *space_available_now);

पूर्णांक virtio_transport_notअगरy_recv_init(काष्ठा vsock_sock *vsk,
	माप_प्रकार target, काष्ठा vsock_transport_recv_notअगरy_data *data);
पूर्णांक virtio_transport_notअगरy_recv_pre_block(काष्ठा vsock_sock *vsk,
	माप_प्रकार target, काष्ठा vsock_transport_recv_notअगरy_data *data);
पूर्णांक virtio_transport_notअगरy_recv_pre_dequeue(काष्ठा vsock_sock *vsk,
	माप_प्रकार target, काष्ठा vsock_transport_recv_notअगरy_data *data);
पूर्णांक virtio_transport_notअगरy_recv_post_dequeue(काष्ठा vsock_sock *vsk,
	माप_प्रकार target, sमाप_प्रकार copied, bool data_पढ़ो,
	काष्ठा vsock_transport_recv_notअगरy_data *data);
पूर्णांक virtio_transport_notअगरy_send_init(काष्ठा vsock_sock *vsk,
	काष्ठा vsock_transport_send_notअगरy_data *data);
पूर्णांक virtio_transport_notअगरy_send_pre_block(काष्ठा vsock_sock *vsk,
	काष्ठा vsock_transport_send_notअगरy_data *data);
पूर्णांक virtio_transport_notअगरy_send_pre_enqueue(काष्ठा vsock_sock *vsk,
	काष्ठा vsock_transport_send_notअगरy_data *data);
पूर्णांक virtio_transport_notअगरy_send_post_enqueue(काष्ठा vsock_sock *vsk,
	sमाप_प्रकार written, काष्ठा vsock_transport_send_notअगरy_data *data);
व्योम virtio_transport_notअगरy_buffer_size(काष्ठा vsock_sock *vsk, u64 *val);

u64 virtio_transport_stream_rcvhiwat(काष्ठा vsock_sock *vsk);
bool virtio_transport_stream_is_active(काष्ठा vsock_sock *vsk);
bool virtio_transport_stream_allow(u32 cid, u32 port);
पूर्णांक virtio_transport_dgram_bind(काष्ठा vsock_sock *vsk,
				काष्ठा sockaddr_vm *addr);
bool virtio_transport_dgram_allow(u32 cid, u32 port);

पूर्णांक virtio_transport_connect(काष्ठा vsock_sock *vsk);

पूर्णांक virtio_transport_shutकरोwn(काष्ठा vsock_sock *vsk, पूर्णांक mode);

व्योम virtio_transport_release(काष्ठा vsock_sock *vsk);

sमाप_प्रकार
virtio_transport_stream_enqueue(काष्ठा vsock_sock *vsk,
				काष्ठा msghdr *msg,
				माप_प्रकार len);
पूर्णांक
virtio_transport_dgram_enqueue(काष्ठा vsock_sock *vsk,
			       काष्ठा sockaddr_vm *remote_addr,
			       काष्ठा msghdr *msg,
			       माप_प्रकार len);

व्योम virtio_transport_deकाष्ठा(काष्ठा vsock_sock *vsk);

व्योम virtio_transport_recv_pkt(काष्ठा virtio_transport *t,
			       काष्ठा virtio_vsock_pkt *pkt);
व्योम virtio_transport_मुक्त_pkt(काष्ठा virtio_vsock_pkt *pkt);
व्योम virtio_transport_inc_tx_pkt(काष्ठा virtio_vsock_sock *vvs, काष्ठा virtio_vsock_pkt *pkt);
u32 virtio_transport_get_credit(काष्ठा virtio_vsock_sock *vvs, u32 wanted);
व्योम virtio_transport_put_credit(काष्ठा virtio_vsock_sock *vvs, u32 credit);
व्योम virtio_transport_deliver_tap_pkt(काष्ठा virtio_vsock_pkt *pkt);

#पूर्ण_अगर /* _LINUX_VIRTIO_VSOCK_H */
