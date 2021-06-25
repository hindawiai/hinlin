<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hyper-V transport क्रम vsock
 *
 * Hyper-V Sockets supplies a byte-stream based communication mechanism
 * between the host and the VM. This driver implements the necessary
 * support in the VM by पूर्णांकroducing the new vsock transport.
 *
 * Copyright (c) 2017, Microsoft Corporation.
 */
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/hyperv.h>
#समावेश <net/sock.h>
#समावेश <net/af_vsock.h>
#समावेश <यंत्र/hyperv-tlfs.h>

/* Older (VMBUS version 'VERSION_WIN10' or beक्रमe) Winकरोws hosts have some
 * stricter requirements on the hv_sock ring buffer size of six 4K pages.
 * hyperv-tlfs defines HV_HYP_PAGE_SIZE as 4K. Newer hosts करोn't have this
 * limitation; but, keep the शेषs the same क्रम compat.
 */
#घोषणा RINGBUFFER_HVS_RCV_SIZE (HV_HYP_PAGE_SIZE * 6)
#घोषणा RINGBUFFER_HVS_SND_SIZE (HV_HYP_PAGE_SIZE * 6)
#घोषणा RINGBUFFER_HVS_MAX_SIZE (HV_HYP_PAGE_SIZE * 64)

/* The MTU is 16KB per the host side's design */
#घोषणा HVS_MTU_SIZE		(1024 * 16)

/* How दीर्घ to रुको क्रम graceful shutकरोwn of a connection */
#घोषणा HVS_CLOSE_TIMEOUT (8 * HZ)

काष्ठा vmpipe_proto_header अणु
	u32 pkt_type;
	u32 data_size;
पूर्ण;

/* For recv, we use the VMBus in-place packet iterator APIs to directly copy
 * data from the ringbuffer पूर्णांकo the userspace buffer.
 */
काष्ठा hvs_recv_buf अणु
	/* The header beक्रमe the payload data */
	काष्ठा vmpipe_proto_header hdr;

	/* The payload */
	u8 data[HVS_MTU_SIZE];
पूर्ण;

/* We can send up to HVS_MTU_SIZE bytes of payload to the host, but let's use
 * a smaller size, i.e. HVS_SEND_BUF_SIZE, to maximize concurrency between the
 * guest and the host processing as one VMBUS packet is the smallest processing
 * unit.
 *
 * Note: the buffer can be eliminated in the future when we add new VMBus
 * ringbuffer APIs that allow us to directly copy data from userspace buffer
 * to VMBus ringbuffer.
 */
#घोषणा HVS_SEND_BUF_SIZE \
		(HV_HYP_PAGE_SIZE - माप(काष्ठा vmpipe_proto_header))

काष्ठा hvs_send_buf अणु
	/* The header beक्रमe the payload data */
	काष्ठा vmpipe_proto_header hdr;

	/* The payload */
	u8 data[HVS_SEND_BUF_SIZE];
पूर्ण;

#घोषणा HVS_HEADER_LEN	(माप(काष्ठा vmpacket_descriptor) + \
			 माप(काष्ठा vmpipe_proto_header))

/* See 'prev_indices' in hv_ringbuffer_पढ़ो(), hv_ringbuffer_ग_लिखो(), and
 * __hv_pkt_iter_next().
 */
#घोषणा VMBUS_PKT_TRAILER_SIZE	(माप(u64))

#घोषणा HVS_PKT_LEN(payload_len)	(HVS_HEADER_LEN + \
					 ALIGN((payload_len), 8) + \
					 VMBUS_PKT_TRAILER_SIZE)

जोड़ hvs_service_id अणु
	guid_t	srv_id;

	काष्ठा अणु
		अचिन्हित पूर्णांक svm_port;
		अचिन्हित अक्षर b[माप(guid_t) - माप(अचिन्हित पूर्णांक)];
	पूर्ण;
पूर्ण;

/* Per-socket state (accessed via vsk->trans) */
काष्ठा hvsock अणु
	काष्ठा vsock_sock *vsk;

	guid_t vm_srv_id;
	guid_t host_srv_id;

	काष्ठा vmbus_channel *chan;
	काष्ठा vmpacket_descriptor *recv_desc;

	/* The length of the payload not delivered to userland yet */
	u32 recv_data_len;
	/* The offset of the payload */
	u32 recv_data_off;

	/* Have we sent the zero-length packet (FIN)? */
	bool fin_sent;
पूर्ण;

/* In the VM, we support Hyper-V Sockets with AF_VSOCK, and the endpoपूर्णांक is
 * <cid, port> (see काष्ठा sockaddr_vm). Note: cid is not really used here:
 * when we ग_लिखो apps to connect to the host, we can only use VMADDR_CID_ANY
 * or VMADDR_CID_HOST (both are equivalent) as the remote cid, and when we
 * ग_लिखो apps to bind() & listen() in the VM, we can only use VMADDR_CID_ANY
 * as the local cid.
 *
 * On the host, Hyper-V Sockets are supported by Winsock AF_HYPERV:
 * https://करोcs.microsoft.com/en-us/भवization/hyper-v-on-winकरोws/user-
 * guide/make-पूर्णांकegration-service, and the endpoपूर्णांक is <VmID, ServiceId> with
 * the below sockaddr:
 *
 * काष्ठा SOCKADDR_HV
 * अणु
 *    ADDRESS_FAMILY Family;
 *    USHORT Reserved;
 *    GUID VmId;
 *    GUID ServiceId;
 * पूर्ण;
 * Note: VmID is not used by Linux VM and actually it isn't transmitted via
 * VMBus, because here it's obvious the host and the VM can easily identअगरy
 * each other. Though the VmID is useful on the host, especially in the हाल
 * of Winकरोws container, Linux VM करोesn't need it at all.
 *
 * To make use of the AF_VSOCK infraकाष्ठाure in Linux VM, we have to limit
 * the available GUID space of SOCKADDR_HV so that we can create a mapping
 * between AF_VSOCK port and SOCKADDR_HV Service GUID. The rule of writing
 * Hyper-V Sockets apps on the host and in Linux VM is:
 *
 ****************************************************************************
 * The only valid Service GUIDs, from the perspectives of both the host and *
 * Linux VM, that can be connected by the other end, must conक्रमm to this   *
 * क्रमmat: <port>-facb-11e6-bd58-64006a7986d3.                              *
 ****************************************************************************
 *
 * When we ग_लिखो apps on the host to connect(), the GUID ServiceID is used.
 * When we ग_लिखो apps in Linux VM to connect(), we only need to specअगरy the
 * port and the driver will क्रमm the GUID and use that to request the host.
 *
 */

/* 00000000-facb-11e6-bd58-64006a7986d3 */
अटल स्थिर guid_t srv_id_ढाँचा =
	GUID_INIT(0x00000000, 0xfacb, 0x11e6, 0xbd, 0x58,
		  0x64, 0x00, 0x6a, 0x79, 0x86, 0xd3);

अटल bool hvs_check_transport(काष्ठा vsock_sock *vsk);

अटल bool is_valid_srv_id(स्थिर guid_t *id)
अणु
	वापस !स_भेद(&id->b[4], &srv_id_ढाँचा.b[4], माप(guid_t) - 4);
पूर्ण

अटल अचिन्हित पूर्णांक get_port_by_srv_id(स्थिर guid_t *svr_id)
अणु
	वापस *((अचिन्हित पूर्णांक *)svr_id);
पूर्ण

अटल व्योम hvs_addr_init(काष्ठा sockaddr_vm *addr, स्थिर guid_t *svr_id)
अणु
	अचिन्हित पूर्णांक port = get_port_by_srv_id(svr_id);

	vsock_addr_init(addr, VMADDR_CID_ANY, port);
पूर्ण

अटल व्योम hvs_set_channel_pending_send_size(काष्ठा vmbus_channel *chan)
अणु
	set_channel_pending_send_size(chan,
				      HVS_PKT_LEN(HVS_SEND_BUF_SIZE));

	virt_mb();
पूर्ण

अटल bool hvs_channel_पढ़ोable(काष्ठा vmbus_channel *chan)
अणु
	u32 पढ़ोable = hv_get_bytes_to_पढ़ो(&chan->inbound);

	/* 0-size payload means FIN */
	वापस पढ़ोable >= HVS_PKT_LEN(0);
पूर्ण

अटल पूर्णांक hvs_channel_पढ़ोable_payload(काष्ठा vmbus_channel *chan)
अणु
	u32 पढ़ोable = hv_get_bytes_to_पढ़ो(&chan->inbound);

	अगर (पढ़ोable > HVS_PKT_LEN(0)) अणु
		/* At least we have 1 byte to पढ़ो. We करोn't need to वापस
		 * the exact पढ़ोable bytes: see vsock_stream_recvmsg() ->
		 * vsock_stream_has_data().
		 */
		वापस 1;
	पूर्ण

	अगर (पढ़ोable == HVS_PKT_LEN(0)) अणु
		/* 0-size payload means FIN */
		वापस 0;
	पूर्ण

	/* No payload or FIN */
	वापस -1;
पूर्ण

अटल माप_प्रकार hvs_channel_writable_bytes(काष्ठा vmbus_channel *chan)
अणु
	u32 ग_लिखोable = hv_get_bytes_to_ग_लिखो(&chan->outbound);
	माप_प्रकार ret;

	/* The ringbuffer mustn't be 100% full, and we should reserve a
	 * zero-length-payload packet क्रम the FIN: see hv_ringbuffer_ग_लिखो()
	 * and hvs_shutकरोwn().
	 */
	अगर (ग_लिखोable <= HVS_PKT_LEN(1) + HVS_PKT_LEN(0))
		वापस 0;

	ret = ग_लिखोable - HVS_PKT_LEN(1) - HVS_PKT_LEN(0);

	वापस round_करोwn(ret, 8);
पूर्ण

अटल पूर्णांक hvs_send_data(काष्ठा vmbus_channel *chan,
			 काष्ठा hvs_send_buf *send_buf, माप_प्रकार to_ग_लिखो)
अणु
	send_buf->hdr.pkt_type = 1;
	send_buf->hdr.data_size = to_ग_लिखो;
	वापस vmbus_sendpacket(chan, &send_buf->hdr,
				माप(send_buf->hdr) + to_ग_लिखो,
				0, VM_PKT_DATA_INBAND, 0);
पूर्ण

अटल व्योम hvs_channel_cb(व्योम *ctx)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)ctx;
	काष्ठा vsock_sock *vsk = vsock_sk(sk);
	काष्ठा hvsock *hvs = vsk->trans;
	काष्ठा vmbus_channel *chan = hvs->chan;

	अगर (hvs_channel_पढ़ोable(chan))
		sk->sk_data_पढ़ोy(sk);

	अगर (hv_get_bytes_to_ग_लिखो(&chan->outbound) > 0)
		sk->sk_ग_लिखो_space(sk);
पूर्ण

अटल व्योम hvs_करो_बंद_lock_held(काष्ठा vsock_sock *vsk,
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
		vsock_हटाओ_sock(vsk);

		/* Release the reference taken जबतक scheduling the समयout */
		sock_put(sk);
	पूर्ण
पूर्ण

अटल व्योम hvs_बंद_connection(काष्ठा vmbus_channel *chan)
अणु
	काष्ठा sock *sk = get_per_channel_state(chan);

	lock_sock(sk);
	hvs_करो_बंद_lock_held(vsock_sk(sk), true);
	release_sock(sk);

	/* Release the refcnt क्रम the channel that's खोलोed in
	 * hvs_खोलो_connection().
	 */
	sock_put(sk);
पूर्ण

अटल व्योम hvs_खोलो_connection(काष्ठा vmbus_channel *chan)
अणु
	guid_t *अगर_instance, *अगर_type;
	अचिन्हित अक्षर conn_from_host;

	काष्ठा sockaddr_vm addr;
	काष्ठा sock *sk, *new = शून्य;
	काष्ठा vsock_sock *vnew = शून्य;
	काष्ठा hvsock *hvs = शून्य;
	काष्ठा hvsock *hvs_new = शून्य;
	पूर्णांक rcvbuf;
	पूर्णांक ret;
	पूर्णांक sndbuf;

	अगर_type = &chan->offermsg.offer.अगर_type;
	अगर_instance = &chan->offermsg.offer.अगर_instance;
	conn_from_host = chan->offermsg.offer.u.pipe.user_def[0];
	अगर (!is_valid_srv_id(अगर_type))
		वापस;

	hvs_addr_init(&addr, conn_from_host ? अगर_type : अगर_instance);
	sk = vsock_find_bound_socket(&addr);
	अगर (!sk)
		वापस;

	lock_sock(sk);
	अगर ((conn_from_host && sk->sk_state != TCP_LISTEN) ||
	    (!conn_from_host && sk->sk_state != TCP_SYN_SENT))
		जाओ out;

	अगर (conn_from_host) अणु
		अगर (sk->sk_ack_backlog >= sk->sk_max_ack_backlog)
			जाओ out;

		new = vsock_create_connected(sk);
		अगर (!new)
			जाओ out;

		new->sk_state = TCP_SYN_SENT;
		vnew = vsock_sk(new);

		hvs_addr_init(&vnew->local_addr, अगर_type);

		/* Remote peer is always the host */
		vsock_addr_init(&vnew->remote_addr,
				VMADDR_CID_HOST, VMADDR_PORT_ANY);
		vnew->remote_addr.svm_port = get_port_by_srv_id(अगर_instance);
		ret = vsock_assign_transport(vnew, vsock_sk(sk));
		/* Transport asचिन्हित (looking at remote_addr) must be the
		 * same where we received the request.
		 */
		अगर (ret || !hvs_check_transport(vnew)) अणु
			sock_put(new);
			जाओ out;
		पूर्ण
		hvs_new = vnew->trans;
		hvs_new->chan = chan;
	पूर्ण अन्यथा अणु
		hvs = vsock_sk(sk)->trans;
		hvs->chan = chan;
	पूर्ण

	set_channel_पढ़ो_mode(chan, HV_CALL_सूचीECT);

	/* Use the socket buffer sizes as hपूर्णांकs क्रम the VMBUS ring size. For
	 * server side sockets, 'sk' is the parent socket and thus, this will
	 * allow the child sockets to inherit the size from the parent. Keep
	 * the mins to the शेष value and align to page size as per VMBUS
	 * requirements.
	 * For the max, the socket core library will limit the socket buffer
	 * size that can be set by the user, but, since currently, the hv_sock
	 * VMBUS ring buffer is physically contiguous allocation, restrict it
	 * further.
	 * Older versions of hv_sock host side code cannot handle bigger VMBUS
	 * ring buffer size. Use the version number to limit the change to newer
	 * versions.
	 */
	अगर (vmbus_proto_version < VERSION_WIN10_V5) अणु
		sndbuf = RINGBUFFER_HVS_SND_SIZE;
		rcvbuf = RINGBUFFER_HVS_RCV_SIZE;
	पूर्ण अन्यथा अणु
		sndbuf = max_t(पूर्णांक, sk->sk_sndbuf, RINGBUFFER_HVS_SND_SIZE);
		sndbuf = min_t(पूर्णांक, sndbuf, RINGBUFFER_HVS_MAX_SIZE);
		sndbuf = ALIGN(sndbuf, HV_HYP_PAGE_SIZE);
		rcvbuf = max_t(पूर्णांक, sk->sk_rcvbuf, RINGBUFFER_HVS_RCV_SIZE);
		rcvbuf = min_t(पूर्णांक, rcvbuf, RINGBUFFER_HVS_MAX_SIZE);
		rcvbuf = ALIGN(rcvbuf, HV_HYP_PAGE_SIZE);
	पूर्ण

	ret = vmbus_खोलो(chan, sndbuf, rcvbuf, शून्य, 0, hvs_channel_cb,
			 conn_from_host ? new : sk);
	अगर (ret != 0) अणु
		अगर (conn_from_host) अणु
			hvs_new->chan = शून्य;
			sock_put(new);
		पूर्ण अन्यथा अणु
			hvs->chan = शून्य;
		पूर्ण
		जाओ out;
	पूर्ण

	set_per_channel_state(chan, conn_from_host ? new : sk);

	/* This reference will be dropped by hvs_बंद_connection(). */
	sock_hold(conn_from_host ? new : sk);
	vmbus_set_chn_rescind_callback(chan, hvs_बंद_connection);

	/* Set the pending send size to max packet size to always get
	 * notअगरications from the host when there is enough writable space.
	 * The host is optimized to send notअगरications only when the pending
	 * size boundary is crossed, and not always.
	 */
	hvs_set_channel_pending_send_size(chan);

	अगर (conn_from_host) अणु
		new->sk_state = TCP_ESTABLISHED;
		sk_acceptq_added(sk);

		hvs_new->vm_srv_id = *अगर_type;
		hvs_new->host_srv_id = *अगर_instance;

		vsock_insert_connected(vnew);

		vsock_enqueue_accept(sk, new);
	पूर्ण अन्यथा अणु
		sk->sk_state = TCP_ESTABLISHED;
		sk->sk_socket->state = SS_CONNECTED;

		vsock_insert_connected(vsock_sk(sk));
	पूर्ण

	sk->sk_state_change(sk);

out:
	/* Release refcnt obtained when we called vsock_find_bound_socket() */
	sock_put(sk);

	release_sock(sk);
पूर्ण

अटल u32 hvs_get_local_cid(व्योम)
अणु
	वापस VMADDR_CID_ANY;
पूर्ण

अटल पूर्णांक hvs_sock_init(काष्ठा vsock_sock *vsk, काष्ठा vsock_sock *psk)
अणु
	काष्ठा hvsock *hvs;
	काष्ठा sock *sk = sk_vsock(vsk);

	hvs = kzalloc(माप(*hvs), GFP_KERNEL);
	अगर (!hvs)
		वापस -ENOMEM;

	vsk->trans = hvs;
	hvs->vsk = vsk;
	sk->sk_sndbuf = RINGBUFFER_HVS_SND_SIZE;
	sk->sk_rcvbuf = RINGBUFFER_HVS_RCV_SIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक hvs_connect(काष्ठा vsock_sock *vsk)
अणु
	जोड़ hvs_service_id vm, host;
	काष्ठा hvsock *h = vsk->trans;

	vm.srv_id = srv_id_ढाँचा;
	vm.svm_port = vsk->local_addr.svm_port;
	h->vm_srv_id = vm.srv_id;

	host.srv_id = srv_id_ढाँचा;
	host.svm_port = vsk->remote_addr.svm_port;
	h->host_srv_id = host.srv_id;

	वापस vmbus_send_tl_connect_request(&h->vm_srv_id, &h->host_srv_id);
पूर्ण

अटल व्योम hvs_shutकरोwn_lock_held(काष्ठा hvsock *hvs, पूर्णांक mode)
अणु
	काष्ठा vmpipe_proto_header hdr;

	अगर (hvs->fin_sent || !hvs->chan)
		वापस;

	/* It can't fail: see hvs_channel_writable_bytes(). */
	(व्योम)hvs_send_data(hvs->chan, (काष्ठा hvs_send_buf *)&hdr, 0);
	hvs->fin_sent = true;
पूर्ण

अटल पूर्णांक hvs_shutकरोwn(काष्ठा vsock_sock *vsk, पूर्णांक mode)
अणु
	अगर (!(mode & SEND_SHUTDOWN))
		वापस 0;

	hvs_shutकरोwn_lock_held(vsk->trans, mode);
	वापस 0;
पूर्ण

अटल व्योम hvs_बंद_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vsock_sock *vsk =
		container_of(work, काष्ठा vsock_sock, बंद_work.work);
	काष्ठा sock *sk = sk_vsock(vsk);

	sock_hold(sk);
	lock_sock(sk);
	अगर (!sock_flag(sk, SOCK_DONE))
		hvs_करो_बंद_lock_held(vsk, false);

	vsk->बंद_work_scheduled = false;
	release_sock(sk);
	sock_put(sk);
पूर्ण

/* Returns true, अगर it is safe to हटाओ socket; false otherwise */
अटल bool hvs_बंद_lock_held(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा sock *sk = sk_vsock(vsk);

	अगर (!(sk->sk_state == TCP_ESTABLISHED ||
	      sk->sk_state == TCP_CLOSING))
		वापस true;

	अगर ((sk->sk_shutकरोwn & SHUTDOWN_MASK) != SHUTDOWN_MASK)
		hvs_shutकरोwn_lock_held(vsk->trans, SHUTDOWN_MASK);

	अगर (sock_flag(sk, SOCK_DONE))
		वापस true;

	/* This reference will be dropped by the delayed बंद routine */
	sock_hold(sk);
	INIT_DELAYED_WORK(&vsk->बंद_work, hvs_बंद_समयout);
	vsk->बंद_work_scheduled = true;
	schedule_delayed_work(&vsk->बंद_work, HVS_CLOSE_TIMEOUT);
	वापस false;
पूर्ण

अटल व्योम hvs_release(काष्ठा vsock_sock *vsk)
अणु
	bool हटाओ_sock;

	हटाओ_sock = hvs_बंद_lock_held(vsk);
	अगर (हटाओ_sock)
		vsock_हटाओ_sock(vsk);
पूर्ण

अटल व्योम hvs_deकाष्ठा(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा hvsock *hvs = vsk->trans;
	काष्ठा vmbus_channel *chan = hvs->chan;

	अगर (chan)
		vmbus_hvsock_device_unरेजिस्टर(chan);

	kमुक्त(hvs);
पूर्ण

अटल पूर्णांक hvs_dgram_bind(काष्ठा vsock_sock *vsk, काष्ठा sockaddr_vm *addr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hvs_dgram_dequeue(काष्ठा vsock_sock *vsk, काष्ठा msghdr *msg,
			     माप_प्रकार len, पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक hvs_dgram_enqueue(काष्ठा vsock_sock *vsk,
			     काष्ठा sockaddr_vm *remote, काष्ठा msghdr *msg,
			     माप_प्रकार dgram_len)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल bool hvs_dgram_allow(u32 cid, u32 port)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक hvs_update_recv_data(काष्ठा hvsock *hvs)
अणु
	काष्ठा hvs_recv_buf *recv_buf;
	u32 payload_len;

	recv_buf = (काष्ठा hvs_recv_buf *)(hvs->recv_desc + 1);
	payload_len = recv_buf->hdr.data_size;

	अगर (payload_len > HVS_MTU_SIZE)
		वापस -EIO;

	अगर (payload_len == 0)
		hvs->vsk->peer_shutकरोwn |= SEND_SHUTDOWN;

	hvs->recv_data_len = payload_len;
	hvs->recv_data_off = 0;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार hvs_stream_dequeue(काष्ठा vsock_sock *vsk, काष्ठा msghdr *msg,
				  माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा hvsock *hvs = vsk->trans;
	bool need_refill = !hvs->recv_desc;
	काष्ठा hvs_recv_buf *recv_buf;
	u32 to_पढ़ो;
	पूर्णांक ret;

	अगर (flags & MSG_PEEK)
		वापस -EOPNOTSUPP;

	अगर (need_refill) अणु
		hvs->recv_desc = hv_pkt_iter_first(hvs->chan);
		ret = hvs_update_recv_data(hvs);
		अगर (ret)
			वापस ret;
	पूर्ण

	recv_buf = (काष्ठा hvs_recv_buf *)(hvs->recv_desc + 1);
	to_पढ़ो = min_t(u32, len, hvs->recv_data_len);
	ret = स_नकल_to_msg(msg, recv_buf->data + hvs->recv_data_off, to_पढ़ो);
	अगर (ret != 0)
		वापस ret;

	hvs->recv_data_len -= to_पढ़ो;
	अगर (hvs->recv_data_len == 0) अणु
		hvs->recv_desc = hv_pkt_iter_next(hvs->chan, hvs->recv_desc);
		अगर (hvs->recv_desc) अणु
			ret = hvs_update_recv_data(hvs);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		hvs->recv_data_off += to_पढ़ो;
	पूर्ण

	वापस to_पढ़ो;
पूर्ण

अटल sमाप_प्रकार hvs_stream_enqueue(काष्ठा vsock_sock *vsk, काष्ठा msghdr *msg,
				  माप_प्रकार len)
अणु
	काष्ठा hvsock *hvs = vsk->trans;
	काष्ठा vmbus_channel *chan = hvs->chan;
	काष्ठा hvs_send_buf *send_buf;
	sमाप_प्रकार to_ग_लिखो, max_writable;
	sमाप_प्रकार ret = 0;
	sमाप_प्रकार bytes_written = 0;

	BUILD_BUG_ON(माप(*send_buf) != HV_HYP_PAGE_SIZE);

	send_buf = kदो_स्मृति(माप(*send_buf), GFP_KERNEL);
	अगर (!send_buf)
		वापस -ENOMEM;

	/* Reader(s) could be draining data from the channel as we ग_लिखो.
	 * Maximize bandwidth, by iterating until the channel is found to be
	 * full.
	 */
	जबतक (len) अणु
		max_writable = hvs_channel_writable_bytes(chan);
		अगर (!max_writable)
			अवरोध;
		to_ग_लिखो = min_t(sमाप_प्रकार, len, max_writable);
		to_ग_लिखो = min_t(sमाप_प्रकार, to_ग_लिखो, HVS_SEND_BUF_SIZE);
		/* स_नकल_from_msg is safe क्रम loop as it advances the offsets
		 * within the message iterator.
		 */
		ret = स_नकल_from_msg(send_buf->data, msg, to_ग_लिखो);
		अगर (ret < 0)
			जाओ out;

		ret = hvs_send_data(hvs->chan, send_buf, to_ग_लिखो);
		अगर (ret < 0)
			जाओ out;

		bytes_written += to_ग_लिखो;
		len -= to_ग_लिखो;
	पूर्ण
out:
	/* If any data has been sent, वापस that */
	अगर (bytes_written)
		ret = bytes_written;
	kमुक्त(send_buf);
	वापस ret;
पूर्ण

अटल s64 hvs_stream_has_data(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा hvsock *hvs = vsk->trans;
	s64 ret;

	अगर (hvs->recv_data_len > 0)
		वापस 1;

	चयन (hvs_channel_पढ़ोable_payload(hvs->chan)) अणु
	हाल 1:
		ret = 1;
		अवरोध;
	हाल 0:
		vsk->peer_shutकरोwn |= SEND_SHUTDOWN;
		ret = 0;
		अवरोध;
	शेष: /* -1 */
		ret = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल s64 hvs_stream_has_space(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा hvsock *hvs = vsk->trans;

	वापस hvs_channel_writable_bytes(hvs->chan);
पूर्ण

अटल u64 hvs_stream_rcvhiwat(काष्ठा vsock_sock *vsk)
अणु
	वापस HVS_MTU_SIZE + 1;
पूर्ण

अटल bool hvs_stream_is_active(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा hvsock *hvs = vsk->trans;

	वापस hvs->chan != शून्य;
पूर्ण

अटल bool hvs_stream_allow(u32 cid, u32 port)
अणु
	अगर (cid == VMADDR_CID_HOST)
		वापस true;

	वापस false;
पूर्ण

अटल
पूर्णांक hvs_notअगरy_poll_in(काष्ठा vsock_sock *vsk, माप_प्रकार target, bool *पढ़ोable)
अणु
	काष्ठा hvsock *hvs = vsk->trans;

	*पढ़ोable = hvs_channel_पढ़ोable(hvs->chan);
	वापस 0;
पूर्ण

अटल
पूर्णांक hvs_notअगरy_poll_out(काष्ठा vsock_sock *vsk, माप_प्रकार target, bool *writable)
अणु
	*writable = hvs_stream_has_space(vsk) > 0;

	वापस 0;
पूर्ण

अटल
पूर्णांक hvs_notअगरy_recv_init(काष्ठा vsock_sock *vsk, माप_प्रकार target,
			 काष्ठा vsock_transport_recv_notअगरy_data *d)
अणु
	वापस 0;
पूर्ण

अटल
पूर्णांक hvs_notअगरy_recv_pre_block(काष्ठा vsock_sock *vsk, माप_प्रकार target,
			      काष्ठा vsock_transport_recv_notअगरy_data *d)
अणु
	वापस 0;
पूर्ण

अटल
पूर्णांक hvs_notअगरy_recv_pre_dequeue(काष्ठा vsock_sock *vsk, माप_प्रकार target,
				काष्ठा vsock_transport_recv_notअगरy_data *d)
अणु
	वापस 0;
पूर्ण

अटल
पूर्णांक hvs_notअगरy_recv_post_dequeue(काष्ठा vsock_sock *vsk, माप_प्रकार target,
				 sमाप_प्रकार copied, bool data_पढ़ो,
				 काष्ठा vsock_transport_recv_notअगरy_data *d)
अणु
	वापस 0;
पूर्ण

अटल
पूर्णांक hvs_notअगरy_send_init(काष्ठा vsock_sock *vsk,
			 काष्ठा vsock_transport_send_notअगरy_data *d)
अणु
	वापस 0;
पूर्ण

अटल
पूर्णांक hvs_notअगरy_send_pre_block(काष्ठा vsock_sock *vsk,
			      काष्ठा vsock_transport_send_notअगरy_data *d)
अणु
	वापस 0;
पूर्ण

अटल
पूर्णांक hvs_notअगरy_send_pre_enqueue(काष्ठा vsock_sock *vsk,
				काष्ठा vsock_transport_send_notअगरy_data *d)
अणु
	वापस 0;
पूर्ण

अटल
पूर्णांक hvs_notअगरy_send_post_enqueue(काष्ठा vsock_sock *vsk, sमाप_प्रकार written,
				 काष्ठा vsock_transport_send_notअगरy_data *d)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा vsock_transport hvs_transport = अणु
	.module                   = THIS_MODULE,

	.get_local_cid            = hvs_get_local_cid,

	.init                     = hvs_sock_init,
	.deकाष्ठा                 = hvs_deकाष्ठा,
	.release                  = hvs_release,
	.connect                  = hvs_connect,
	.shutकरोwn                 = hvs_shutकरोwn,

	.dgram_bind               = hvs_dgram_bind,
	.dgram_dequeue            = hvs_dgram_dequeue,
	.dgram_enqueue            = hvs_dgram_enqueue,
	.dgram_allow              = hvs_dgram_allow,

	.stream_dequeue           = hvs_stream_dequeue,
	.stream_enqueue           = hvs_stream_enqueue,
	.stream_has_data          = hvs_stream_has_data,
	.stream_has_space         = hvs_stream_has_space,
	.stream_rcvhiwat          = hvs_stream_rcvhiwat,
	.stream_is_active         = hvs_stream_is_active,
	.stream_allow             = hvs_stream_allow,

	.notअगरy_poll_in           = hvs_notअगरy_poll_in,
	.notअगरy_poll_out          = hvs_notअगरy_poll_out,
	.notअगरy_recv_init         = hvs_notअगरy_recv_init,
	.notअगरy_recv_pre_block    = hvs_notअगरy_recv_pre_block,
	.notअगरy_recv_pre_dequeue  = hvs_notअगरy_recv_pre_dequeue,
	.notअगरy_recv_post_dequeue = hvs_notअगरy_recv_post_dequeue,
	.notअगरy_send_init         = hvs_notअगरy_send_init,
	.notअगरy_send_pre_block    = hvs_notअगरy_send_pre_block,
	.notअगरy_send_pre_enqueue  = hvs_notअगरy_send_pre_enqueue,
	.notअगरy_send_post_enqueue = hvs_notअगरy_send_post_enqueue,

पूर्ण;

अटल bool hvs_check_transport(काष्ठा vsock_sock *vsk)
अणु
	वापस vsk->transport == &hvs_transport;
पूर्ण

अटल पूर्णांक hvs_probe(काष्ठा hv_device *hdev,
		     स्थिर काष्ठा hv_vmbus_device_id *dev_id)
अणु
	काष्ठा vmbus_channel *chan = hdev->channel;

	hvs_खोलो_connection(chan);

	/* Always वापस success to suppress the unnecessary error message
	 * in vmbus_probe(): on error the host will rescind the device in
	 * 30 seconds and we can करो cleanup at that समय in
	 * vmbus_onoffer_rescind().
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक hvs_हटाओ(काष्ठा hv_device *hdev)
अणु
	काष्ठा vmbus_channel *chan = hdev->channel;

	vmbus_बंद(chan);

	वापस 0;
पूर्ण

/* hv_sock connections can not persist across hibernation, and all the hv_sock
 * channels are क्रमced to be rescinded beक्रमe hibernation: see
 * vmbus_bus_suspend(). Here the dummy hvs_suspend() and hvs_resume()
 * are only needed because hibernation requires that every vmbus device's
 * driver should have a .suspend and .resume callback: see vmbus_suspend().
 */
अटल पूर्णांक hvs_suspend(काष्ठा hv_device *hv_dev)
अणु
	/* Dummy */
	वापस 0;
पूर्ण

अटल पूर्णांक hvs_resume(काष्ठा hv_device *dev)
अणु
	/* Dummy */
	वापस 0;
पूर्ण

/* This isn't really used. See vmbus_match() and vmbus_probe() */
अटल स्थिर काष्ठा hv_vmbus_device_id id_table[] = अणु
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा hv_driver hvs_drv = अणु
	.name		= "hv_sock",
	.hvsock		= true,
	.id_table	= id_table,
	.probe		= hvs_probe,
	.हटाओ		= hvs_हटाओ,
	.suspend	= hvs_suspend,
	.resume		= hvs_resume,
पूर्ण;

अटल पूर्णांक __init hvs_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (vmbus_proto_version < VERSION_WIN10)
		वापस -ENODEV;

	ret = vmbus_driver_रेजिस्टर(&hvs_drv);
	अगर (ret != 0)
		वापस ret;

	ret = vsock_core_रेजिस्टर(&hvs_transport, VSOCK_TRANSPORT_F_G2H);
	अगर (ret) अणु
		vmbus_driver_unरेजिस्टर(&hvs_drv);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास hvs_निकास(व्योम)
अणु
	vsock_core_unरेजिस्टर(&hvs_transport);
	vmbus_driver_unरेजिस्टर(&hvs_drv);
पूर्ण

module_init(hvs_init);
module_निकास(hvs_निकास);

MODULE_DESCRIPTION("Hyper-V Sockets");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_VSOCK);
