<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware vSockets Driver
 *
 * Copyright (C) 2007-2013 VMware, Inc. All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cred.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/net.h>
#समावेश <linux/poll.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/smp.h>
#समावेश <linux/socket.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <net/sock.h>
#समावेश <net/af_vsock.h>

#समावेश "vmci_transport_notify.h"

अटल पूर्णांक vmci_transport_recv_dgram_cb(व्योम *data, काष्ठा vmci_datagram *dg);
अटल पूर्णांक vmci_transport_recv_stream_cb(व्योम *data, काष्ठा vmci_datagram *dg);
अटल व्योम vmci_transport_peer_detach_cb(u32 sub_id,
					  स्थिर काष्ठा vmci_event_data *ed,
					  व्योम *client_data);
अटल व्योम vmci_transport_recv_pkt_work(काष्ठा work_काष्ठा *work);
अटल व्योम vmci_transport_cleanup(काष्ठा work_काष्ठा *work);
अटल पूर्णांक vmci_transport_recv_listen(काष्ठा sock *sk,
				      काष्ठा vmci_transport_packet *pkt);
अटल पूर्णांक vmci_transport_recv_connecting_server(
					काष्ठा sock *sk,
					काष्ठा sock *pending,
					काष्ठा vmci_transport_packet *pkt);
अटल पूर्णांक vmci_transport_recv_connecting_client(
					काष्ठा sock *sk,
					काष्ठा vmci_transport_packet *pkt);
अटल पूर्णांक vmci_transport_recv_connecting_client_negotiate(
					काष्ठा sock *sk,
					काष्ठा vmci_transport_packet *pkt);
अटल पूर्णांक vmci_transport_recv_connecting_client_invalid(
					काष्ठा sock *sk,
					काष्ठा vmci_transport_packet *pkt);
अटल पूर्णांक vmci_transport_recv_connected(काष्ठा sock *sk,
					 काष्ठा vmci_transport_packet *pkt);
अटल bool vmci_transport_old_proto_override(bool *old_pkt_proto);
अटल u16 vmci_transport_new_proto_supported_versions(व्योम);
अटल bool vmci_transport_proto_to_notअगरy_काष्ठा(काष्ठा sock *sk, u16 *proto,
						  bool old_pkt_proto);
अटल bool vmci_check_transport(काष्ठा vsock_sock *vsk);

काष्ठा vmci_transport_recv_pkt_info अणु
	काष्ठा work_काष्ठा work;
	काष्ठा sock *sk;
	काष्ठा vmci_transport_packet pkt;
पूर्ण;

अटल LIST_HEAD(vmci_transport_cleanup_list);
अटल DEFINE_SPINLOCK(vmci_transport_cleanup_lock);
अटल DECLARE_WORK(vmci_transport_cleanup_work, vmci_transport_cleanup);

अटल काष्ठा vmci_handle vmci_transport_stream_handle = अणु VMCI_INVALID_ID,
							   VMCI_INVALID_ID पूर्ण;
अटल u32 vmci_transport_qp_resumed_sub_id = VMCI_INVALID_ID;

अटल पूर्णांक PROTOCOL_OVERRIDE = -1;

/* Helper function to convert from a VMCI error code to a VSock error code. */

अटल s32 vmci_transport_error_to_vsock_error(s32 vmci_error)
अणु
	चयन (vmci_error) अणु
	हाल VMCI_ERROR_NO_MEM:
		वापस -ENOMEM;
	हाल VMCI_ERROR_DUPLICATE_ENTRY:
	हाल VMCI_ERROR_ALREADY_EXISTS:
		वापस -EADDRINUSE;
	हाल VMCI_ERROR_NO_ACCESS:
		वापस -EPERM;
	हाल VMCI_ERROR_NO_RESOURCES:
		वापस -ENOBUFS;
	हाल VMCI_ERROR_INVALID_RESOURCE:
		वापस -EHOSTUNREACH;
	हाल VMCI_ERROR_INVALID_ARGS:
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल u32 vmci_transport_peer_rid(u32 peer_cid)
अणु
	अगर (VMADDR_CID_HYPERVISOR == peer_cid)
		वापस VMCI_TRANSPORT_HYPERVISOR_PACKET_RID;

	वापस VMCI_TRANSPORT_PACKET_RID;
पूर्ण

अटल अंतरभूत व्योम
vmci_transport_packet_init(काष्ठा vmci_transport_packet *pkt,
			   काष्ठा sockaddr_vm *src,
			   काष्ठा sockaddr_vm *dst,
			   u8 type,
			   u64 size,
			   u64 mode,
			   काष्ठा vmci_transport_रुकोing_info *रुको,
			   u16 proto,
			   काष्ठा vmci_handle handle)
अणु
	/* We रेजिस्टर the stream control handler as an any cid handle so we
	 * must always send from a source address of VMADDR_CID_ANY
	 */
	pkt->dg.src = vmci_make_handle(VMADDR_CID_ANY,
				       VMCI_TRANSPORT_PACKET_RID);
	pkt->dg.dst = vmci_make_handle(dst->svm_cid,
				       vmci_transport_peer_rid(dst->svm_cid));
	pkt->dg.payload_size = माप(*pkt) - माप(pkt->dg);
	pkt->version = VMCI_TRANSPORT_PACKET_VERSION;
	pkt->type = type;
	pkt->src_port = src->svm_port;
	pkt->dst_port = dst->svm_port;
	स_रखो(&pkt->proto, 0, माप(pkt->proto));
	स_रखो(&pkt->_reserved2, 0, माप(pkt->_reserved2));

	चयन (pkt->type) अणु
	हाल VMCI_TRANSPORT_PACKET_TYPE_INVALID:
		pkt->u.size = 0;
		अवरोध;

	हाल VMCI_TRANSPORT_PACKET_TYPE_REQUEST:
	हाल VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE:
		pkt->u.size = size;
		अवरोध;

	हाल VMCI_TRANSPORT_PACKET_TYPE_OFFER:
	हाल VMCI_TRANSPORT_PACKET_TYPE_ATTACH:
		pkt->u.handle = handle;
		अवरोध;

	हाल VMCI_TRANSPORT_PACKET_TYPE_WROTE:
	हाल VMCI_TRANSPORT_PACKET_TYPE_READ:
	हाल VMCI_TRANSPORT_PACKET_TYPE_RST:
		pkt->u.size = 0;
		अवरोध;

	हाल VMCI_TRANSPORT_PACKET_TYPE_SHUTDOWN:
		pkt->u.mode = mode;
		अवरोध;

	हाल VMCI_TRANSPORT_PACKET_TYPE_WAITING_READ:
	हाल VMCI_TRANSPORT_PACKET_TYPE_WAITING_WRITE:
		स_नकल(&pkt->u.रुको, रुको, माप(pkt->u.रुको));
		अवरोध;

	हाल VMCI_TRANSPORT_PACKET_TYPE_REQUEST2:
	हाल VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE2:
		pkt->u.size = size;
		pkt->proto = proto;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
vmci_transport_packet_get_addresses(काष्ठा vmci_transport_packet *pkt,
				    काष्ठा sockaddr_vm *local,
				    काष्ठा sockaddr_vm *remote)
अणु
	vsock_addr_init(local, pkt->dg.dst.context, pkt->dst_port);
	vsock_addr_init(remote, pkt->dg.src.context, pkt->src_port);
पूर्ण

अटल पूर्णांक
__vmci_transport_send_control_pkt(काष्ठा vmci_transport_packet *pkt,
				  काष्ठा sockaddr_vm *src,
				  काष्ठा sockaddr_vm *dst,
				  क्रमागत vmci_transport_packet_type type,
				  u64 size,
				  u64 mode,
				  काष्ठा vmci_transport_रुकोing_info *रुको,
				  u16 proto,
				  काष्ठा vmci_handle handle,
				  bool convert_error)
अणु
	पूर्णांक err;

	vmci_transport_packet_init(pkt, src, dst, type, size, mode, रुको,
				   proto, handle);
	err = vmci_datagram_send(&pkt->dg);
	अगर (convert_error && (err < 0))
		वापस vmci_transport_error_to_vsock_error(err);

	वापस err;
पूर्ण

अटल पूर्णांक
vmci_transport_reply_control_pkt_fast(काष्ठा vmci_transport_packet *pkt,
				      क्रमागत vmci_transport_packet_type type,
				      u64 size,
				      u64 mode,
				      काष्ठा vmci_transport_रुकोing_info *रुको,
				      काष्ठा vmci_handle handle)
अणु
	काष्ठा vmci_transport_packet reply;
	काष्ठा sockaddr_vm src, dst;

	अगर (pkt->type == VMCI_TRANSPORT_PACKET_TYPE_RST) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		vmci_transport_packet_get_addresses(pkt, &src, &dst);
		वापस __vmci_transport_send_control_pkt(&reply, &src, &dst,
							 type,
							 size, mode, रुको,
							 VSOCK_PROTO_INVALID,
							 handle, true);
	पूर्ण
पूर्ण

अटल पूर्णांक
vmci_transport_send_control_pkt_bh(काष्ठा sockaddr_vm *src,
				   काष्ठा sockaddr_vm *dst,
				   क्रमागत vmci_transport_packet_type type,
				   u64 size,
				   u64 mode,
				   काष्ठा vmci_transport_रुकोing_info *रुको,
				   काष्ठा vmci_handle handle)
अणु
	/* Note that it is safe to use a single packet across all CPUs since
	 * two tasklets of the same type are guaranteed to not ever run
	 * simultaneously. If that ever changes, or VMCI stops using tasklets,
	 * we can use per-cpu packets.
	 */
	अटल काष्ठा vmci_transport_packet pkt;

	वापस __vmci_transport_send_control_pkt(&pkt, src, dst, type,
						 size, mode, रुको,
						 VSOCK_PROTO_INVALID, handle,
						 false);
पूर्ण

अटल पूर्णांक
vmci_transport_alloc_send_control_pkt(काष्ठा sockaddr_vm *src,
				      काष्ठा sockaddr_vm *dst,
				      क्रमागत vmci_transport_packet_type type,
				      u64 size,
				      u64 mode,
				      काष्ठा vmci_transport_रुकोing_info *रुको,
				      u16 proto,
				      काष्ठा vmci_handle handle)
अणु
	काष्ठा vmci_transport_packet *pkt;
	पूर्णांक err;

	pkt = kदो_स्मृति(माप(*pkt), GFP_KERNEL);
	अगर (!pkt)
		वापस -ENOMEM;

	err = __vmci_transport_send_control_pkt(pkt, src, dst, type, size,
						mode, रुको, proto, handle,
						true);
	kमुक्त(pkt);

	वापस err;
पूर्ण

अटल पूर्णांक
vmci_transport_send_control_pkt(काष्ठा sock *sk,
				क्रमागत vmci_transport_packet_type type,
				u64 size,
				u64 mode,
				काष्ठा vmci_transport_रुकोing_info *रुको,
				u16 proto,
				काष्ठा vmci_handle handle)
अणु
	काष्ठा vsock_sock *vsk;

	vsk = vsock_sk(sk);

	अगर (!vsock_addr_bound(&vsk->local_addr))
		वापस -EINVAL;

	अगर (!vsock_addr_bound(&vsk->remote_addr))
		वापस -EINVAL;

	वापस vmci_transport_alloc_send_control_pkt(&vsk->local_addr,
						     &vsk->remote_addr,
						     type, size, mode,
						     रुको, proto, handle);
पूर्ण

अटल पूर्णांक vmci_transport_send_reset_bh(काष्ठा sockaddr_vm *dst,
					काष्ठा sockaddr_vm *src,
					काष्ठा vmci_transport_packet *pkt)
अणु
	अगर (pkt->type == VMCI_TRANSPORT_PACKET_TYPE_RST)
		वापस 0;
	वापस vmci_transport_send_control_pkt_bh(
					dst, src,
					VMCI_TRANSPORT_PACKET_TYPE_RST, 0,
					0, शून्य, VMCI_INVALID_HANDLE);
पूर्ण

अटल पूर्णांक vmci_transport_send_reset(काष्ठा sock *sk,
				     काष्ठा vmci_transport_packet *pkt)
अणु
	काष्ठा sockaddr_vm *dst_ptr;
	काष्ठा sockaddr_vm dst;
	काष्ठा vsock_sock *vsk;

	अगर (pkt->type == VMCI_TRANSPORT_PACKET_TYPE_RST)
		वापस 0;

	vsk = vsock_sk(sk);

	अगर (!vsock_addr_bound(&vsk->local_addr))
		वापस -EINVAL;

	अगर (vsock_addr_bound(&vsk->remote_addr)) अणु
		dst_ptr = &vsk->remote_addr;
	पूर्ण अन्यथा अणु
		vsock_addr_init(&dst, pkt->dg.src.context,
				pkt->src_port);
		dst_ptr = &dst;
	पूर्ण
	वापस vmci_transport_alloc_send_control_pkt(&vsk->local_addr, dst_ptr,
					     VMCI_TRANSPORT_PACKET_TYPE_RST,
					     0, 0, शून्य, VSOCK_PROTO_INVALID,
					     VMCI_INVALID_HANDLE);
पूर्ण

अटल पूर्णांक vmci_transport_send_negotiate(काष्ठा sock *sk, माप_प्रकार size)
अणु
	वापस vmci_transport_send_control_pkt(
					sk,
					VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE,
					size, 0, शून्य,
					VSOCK_PROTO_INVALID,
					VMCI_INVALID_HANDLE);
पूर्ण

अटल पूर्णांक vmci_transport_send_negotiate2(काष्ठा sock *sk, माप_प्रकार size,
					  u16 version)
अणु
	वापस vmci_transport_send_control_pkt(
					sk,
					VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE2,
					size, 0, शून्य, version,
					VMCI_INVALID_HANDLE);
पूर्ण

अटल पूर्णांक vmci_transport_send_qp_offer(काष्ठा sock *sk,
					काष्ठा vmci_handle handle)
अणु
	वापस vmci_transport_send_control_pkt(
					sk, VMCI_TRANSPORT_PACKET_TYPE_OFFER, 0,
					0, शून्य,
					VSOCK_PROTO_INVALID, handle);
पूर्ण

अटल पूर्णांक vmci_transport_send_attach(काष्ठा sock *sk,
				      काष्ठा vmci_handle handle)
अणु
	वापस vmci_transport_send_control_pkt(
					sk, VMCI_TRANSPORT_PACKET_TYPE_ATTACH,
					0, 0, शून्य, VSOCK_PROTO_INVALID,
					handle);
पूर्ण

अटल पूर्णांक vmci_transport_reply_reset(काष्ठा vmci_transport_packet *pkt)
अणु
	वापस vmci_transport_reply_control_pkt_fast(
						pkt,
						VMCI_TRANSPORT_PACKET_TYPE_RST,
						0, 0, शून्य,
						VMCI_INVALID_HANDLE);
पूर्ण

अटल पूर्णांक vmci_transport_send_invalid_bh(काष्ठा sockaddr_vm *dst,
					  काष्ठा sockaddr_vm *src)
अणु
	वापस vmci_transport_send_control_pkt_bh(
					dst, src,
					VMCI_TRANSPORT_PACKET_TYPE_INVALID,
					0, 0, शून्य, VMCI_INVALID_HANDLE);
पूर्ण

पूर्णांक vmci_transport_send_wrote_bh(काष्ठा sockaddr_vm *dst,
				 काष्ठा sockaddr_vm *src)
अणु
	वापस vmci_transport_send_control_pkt_bh(
					dst, src,
					VMCI_TRANSPORT_PACKET_TYPE_WROTE, 0,
					0, शून्य, VMCI_INVALID_HANDLE);
पूर्ण

पूर्णांक vmci_transport_send_पढ़ो_bh(काष्ठा sockaddr_vm *dst,
				काष्ठा sockaddr_vm *src)
अणु
	वापस vmci_transport_send_control_pkt_bh(
					dst, src,
					VMCI_TRANSPORT_PACKET_TYPE_READ, 0,
					0, शून्य, VMCI_INVALID_HANDLE);
पूर्ण

पूर्णांक vmci_transport_send_wrote(काष्ठा sock *sk)
अणु
	वापस vmci_transport_send_control_pkt(
					sk, VMCI_TRANSPORT_PACKET_TYPE_WROTE, 0,
					0, शून्य, VSOCK_PROTO_INVALID,
					VMCI_INVALID_HANDLE);
पूर्ण

पूर्णांक vmci_transport_send_पढ़ो(काष्ठा sock *sk)
अणु
	वापस vmci_transport_send_control_pkt(
					sk, VMCI_TRANSPORT_PACKET_TYPE_READ, 0,
					0, शून्य, VSOCK_PROTO_INVALID,
					VMCI_INVALID_HANDLE);
पूर्ण

पूर्णांक vmci_transport_send_रुकोing_ग_लिखो(काष्ठा sock *sk,
				      काष्ठा vmci_transport_रुकोing_info *रुको)
अणु
	वापस vmci_transport_send_control_pkt(
				sk, VMCI_TRANSPORT_PACKET_TYPE_WAITING_WRITE,
				0, 0, रुको, VSOCK_PROTO_INVALID,
				VMCI_INVALID_HANDLE);
पूर्ण

पूर्णांक vmci_transport_send_रुकोing_पढ़ो(काष्ठा sock *sk,
				     काष्ठा vmci_transport_रुकोing_info *रुको)
अणु
	वापस vmci_transport_send_control_pkt(
				sk, VMCI_TRANSPORT_PACKET_TYPE_WAITING_READ,
				0, 0, रुको, VSOCK_PROTO_INVALID,
				VMCI_INVALID_HANDLE);
पूर्ण

अटल पूर्णांक vmci_transport_shutकरोwn(काष्ठा vsock_sock *vsk, पूर्णांक mode)
अणु
	वापस vmci_transport_send_control_pkt(
					&vsk->sk,
					VMCI_TRANSPORT_PACKET_TYPE_SHUTDOWN,
					0, mode, शून्य,
					VSOCK_PROTO_INVALID,
					VMCI_INVALID_HANDLE);
पूर्ण

अटल पूर्णांक vmci_transport_send_conn_request(काष्ठा sock *sk, माप_प्रकार size)
अणु
	वापस vmci_transport_send_control_pkt(sk,
					VMCI_TRANSPORT_PACKET_TYPE_REQUEST,
					size, 0, शून्य,
					VSOCK_PROTO_INVALID,
					VMCI_INVALID_HANDLE);
पूर्ण

अटल पूर्णांक vmci_transport_send_conn_request2(काष्ठा sock *sk, माप_प्रकार size,
					     u16 version)
अणु
	वापस vmci_transport_send_control_pkt(
					sk, VMCI_TRANSPORT_PACKET_TYPE_REQUEST2,
					size, 0, शून्य, version,
					VMCI_INVALID_HANDLE);
पूर्ण

अटल काष्ठा sock *vmci_transport_get_pending(
					काष्ठा sock *listener,
					काष्ठा vmci_transport_packet *pkt)
अणु
	काष्ठा vsock_sock *vlistener;
	काष्ठा vsock_sock *vpending;
	काष्ठा sock *pending;
	काष्ठा sockaddr_vm src;

	vsock_addr_init(&src, pkt->dg.src.context, pkt->src_port);

	vlistener = vsock_sk(listener);

	list_क्रम_each_entry(vpending, &vlistener->pending_links,
			    pending_links) अणु
		अगर (vsock_addr_equals_addr(&src, &vpending->remote_addr) &&
		    pkt->dst_port == vpending->local_addr.svm_port) अणु
			pending = sk_vsock(vpending);
			sock_hold(pending);
			जाओ found;
		पूर्ण
	पूर्ण

	pending = शून्य;
found:
	वापस pending;

पूर्ण

अटल व्योम vmci_transport_release_pending(काष्ठा sock *pending)
अणु
	sock_put(pending);
पूर्ण

/* We allow two kinds of sockets to communicate with a restricted VM: 1)
 * trusted sockets 2) sockets from applications running as the same user as the
 * VM (this is only true क्रम the host side and only when using hosted products)
 */

अटल bool vmci_transport_is_trusted(काष्ठा vsock_sock *vsock, u32 peer_cid)
अणु
	वापस vsock->trusted ||
	       vmci_is_context_owner(peer_cid, vsock->owner->uid);
पूर्ण

/* We allow sending datagrams to and receiving datagrams from a restricted VM
 * only अगर it is trusted as described in vmci_transport_is_trusted.
 */

अटल bool vmci_transport_allow_dgram(काष्ठा vsock_sock *vsock, u32 peer_cid)
अणु
	अगर (VMADDR_CID_HYPERVISOR == peer_cid)
		वापस true;

	अगर (vsock->cached_peer != peer_cid) अणु
		vsock->cached_peer = peer_cid;
		अगर (!vmci_transport_is_trusted(vsock, peer_cid) &&
		    (vmci_context_get_priv_flags(peer_cid) &
		     VMCI_PRIVILEGE_FLAG_RESTRICTED)) अणु
			vsock->cached_peer_allow_dgram = false;
		पूर्ण अन्यथा अणु
			vsock->cached_peer_allow_dgram = true;
		पूर्ण
	पूर्ण

	वापस vsock->cached_peer_allow_dgram;
पूर्ण

अटल पूर्णांक
vmci_transport_queue_pair_alloc(काष्ठा vmci_qp **qpair,
				काष्ठा vmci_handle *handle,
				u64 produce_size,
				u64 consume_size,
				u32 peer, u32 flags, bool trusted)
अणु
	पूर्णांक err = 0;

	अगर (trusted) अणु
		/* Try to allocate our queue pair as trusted. This will only
		 * work अगर vsock is running in the host.
		 */

		err = vmci_qpair_alloc(qpair, handle, produce_size,
				       consume_size,
				       peer, flags,
				       VMCI_PRIVILEGE_FLAG_TRUSTED);
		अगर (err != VMCI_ERROR_NO_ACCESS)
			जाओ out;

	पूर्ण

	err = vmci_qpair_alloc(qpair, handle, produce_size, consume_size,
			       peer, flags, VMCI_NO_PRIVILEGE_FLAGS);
out:
	अगर (err < 0) अणु
		pr_err_once("Could not attach to queue pair with %d\n", err);
		err = vmci_transport_error_to_vsock_error(err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
vmci_transport_datagram_create_hnd(u32 resource_id,
				   u32 flags,
				   vmci_datagram_recv_cb recv_cb,
				   व्योम *client_data,
				   काष्ठा vmci_handle *out_handle)
अणु
	पूर्णांक err = 0;

	/* Try to allocate our datagram handler as trusted. This will only work
	 * अगर vsock is running in the host.
	 */

	err = vmci_datagram_create_handle_priv(resource_id, flags,
					       VMCI_PRIVILEGE_FLAG_TRUSTED,
					       recv_cb,
					       client_data, out_handle);

	अगर (err == VMCI_ERROR_NO_ACCESS)
		err = vmci_datagram_create_handle(resource_id, flags,
						  recv_cb, client_data,
						  out_handle);

	वापस err;
पूर्ण

/* This is invoked as part of a tasklet that's scheduled when the VMCI
 * पूर्णांकerrupt fires.  This is run in bottom-half context and अगर it ever needs to
 * sleep it should defer that work to a work queue.
 */

अटल पूर्णांक vmci_transport_recv_dgram_cb(व्योम *data, काष्ठा vmci_datagram *dg)
अणु
	काष्ठा sock *sk;
	माप_प्रकार size;
	काष्ठा sk_buff *skb;
	काष्ठा vsock_sock *vsk;

	sk = (काष्ठा sock *)data;

	/* This handler is privileged when this module is running on the host.
	 * We will get datagrams from all endpoपूर्णांकs (even VMs that are in a
	 * restricted context). If we get one from a restricted context then
	 * the destination socket must be trusted.
	 *
	 * NOTE: We access the socket काष्ठा without holding the lock here.
	 * This is ok because the field we are पूर्णांकerested is never modअगरied
	 * outside of the create and deकाष्ठा socket functions.
	 */
	vsk = vsock_sk(sk);
	अगर (!vmci_transport_allow_dgram(vsk, dg->src.context))
		वापस VMCI_ERROR_NO_ACCESS;

	size = VMCI_DG_SIZE(dg);

	/* Attach the packet to the socket's receive queue as an sk_buff. */
	skb = alloc_skb(size, GFP_ATOMIC);
	अगर (!skb)
		वापस VMCI_ERROR_NO_MEM;

	/* sk_receive_skb() will करो a sock_put(), so hold here. */
	sock_hold(sk);
	skb_put(skb, size);
	स_नकल(skb->data, dg, size);
	sk_receive_skb(sk, skb, 0);

	वापस VMCI_SUCCESS;
पूर्ण

अटल bool vmci_transport_stream_allow(u32 cid, u32 port)
अणु
	अटल स्थिर u32 non_socket_contexts[] = अणु
		VMADDR_CID_LOCAL,
	पूर्ण;
	पूर्णांक i;

	BUILD_BUG_ON(माप(cid) != माप(*non_socket_contexts));

	क्रम (i = 0; i < ARRAY_SIZE(non_socket_contexts); i++) अणु
		अगर (cid == non_socket_contexts[i])
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* This is invoked as part of a tasklet that's scheduled when the VMCI
 * पूर्णांकerrupt fires.  This is run in bottom-half context but it defers most of
 * its work to the packet handling work queue.
 */

अटल पूर्णांक vmci_transport_recv_stream_cb(व्योम *data, काष्ठा vmci_datagram *dg)
अणु
	काष्ठा sock *sk;
	काष्ठा sockaddr_vm dst;
	काष्ठा sockaddr_vm src;
	काष्ठा vmci_transport_packet *pkt;
	काष्ठा vsock_sock *vsk;
	bool bh_process_pkt;
	पूर्णांक err;

	sk = शून्य;
	err = VMCI_SUCCESS;
	bh_process_pkt = false;

	/* Ignore incoming packets from contexts without sockets, or resources
	 * that aren't vsock implementations.
	 */

	अगर (!vmci_transport_stream_allow(dg->src.context, -1)
	    || vmci_transport_peer_rid(dg->src.context) != dg->src.resource)
		वापस VMCI_ERROR_NO_ACCESS;

	अगर (VMCI_DG_SIZE(dg) < माप(*pkt))
		/* Drop datagrams that करो not contain full VSock packets. */
		वापस VMCI_ERROR_INVALID_ARGS;

	pkt = (काष्ठा vmci_transport_packet *)dg;

	/* Find the socket that should handle this packet.  First we look क्रम a
	 * connected socket and अगर there is none we look क्रम a socket bound to
	 * the destपूर्णांकation address.
	 */
	vsock_addr_init(&src, pkt->dg.src.context, pkt->src_port);
	vsock_addr_init(&dst, pkt->dg.dst.context, pkt->dst_port);

	sk = vsock_find_connected_socket(&src, &dst);
	अगर (!sk) अणु
		sk = vsock_find_bound_socket(&dst);
		अगर (!sk) अणु
			/* We could not find a socket क्रम this specअगरied
			 * address.  If this packet is a RST, we just drop it.
			 * If it is another packet, we send a RST.  Note that
			 * we करो not send a RST reply to RSTs so that we करो not
			 * continually send RSTs between two endpoपूर्णांकs.
			 *
			 * Note that since this is a reply, dst is src and src
			 * is dst.
			 */
			अगर (vmci_transport_send_reset_bh(&dst, &src, pkt) < 0)
				pr_err("unable to send reset\n");

			err = VMCI_ERROR_NOT_FOUND;
			जाओ out;
		पूर्ण
	पूर्ण

	/* If the received packet type is beyond all types known to this
	 * implementation, reply with an invalid message.  Hopefully this will
	 * help when implementing backwards compatibility in the future.
	 */
	अगर (pkt->type >= VMCI_TRANSPORT_PACKET_TYPE_MAX) अणु
		vmci_transport_send_invalid_bh(&dst, &src);
		err = VMCI_ERROR_INVALID_ARGS;
		जाओ out;
	पूर्ण

	/* This handler is privileged when this module is running on the host.
	 * We will get datagram connect requests from all endpoपूर्णांकs (even VMs
	 * that are in a restricted context). If we get one from a restricted
	 * context then the destination socket must be trusted.
	 *
	 * NOTE: We access the socket काष्ठा without holding the lock here.
	 * This is ok because the field we are पूर्णांकerested is never modअगरied
	 * outside of the create and deकाष्ठा socket functions.
	 */
	vsk = vsock_sk(sk);
	अगर (!vmci_transport_allow_dgram(vsk, pkt->dg.src.context)) अणु
		err = VMCI_ERROR_NO_ACCESS;
		जाओ out;
	पूर्ण

	/* We करो most everything in a work queue, but let's fast path the
	 * notअगरication of पढ़ोs and ग_लिखोs to help data transfer perक्रमmance.
	 * We can only करो this अगर there is no process context code executing
	 * क्रम this socket since that may change the state.
	 */
	bh_lock_sock(sk);

	अगर (!sock_owned_by_user(sk)) अणु
		/* The local context ID may be out of date, update it. */
		vsk->local_addr.svm_cid = dst.svm_cid;

		अगर (sk->sk_state == TCP_ESTABLISHED)
			vmci_trans(vsk)->notअगरy_ops->handle_notअगरy_pkt(
					sk, pkt, true, &dst, &src,
					&bh_process_pkt);
	पूर्ण

	bh_unlock_sock(sk);

	अगर (!bh_process_pkt) अणु
		काष्ठा vmci_transport_recv_pkt_info *recv_pkt_info;

		recv_pkt_info = kदो_स्मृति(माप(*recv_pkt_info), GFP_ATOMIC);
		अगर (!recv_pkt_info) अणु
			अगर (vmci_transport_send_reset_bh(&dst, &src, pkt) < 0)
				pr_err("unable to send reset\n");

			err = VMCI_ERROR_NO_MEM;
			जाओ out;
		पूर्ण

		recv_pkt_info->sk = sk;
		स_नकल(&recv_pkt_info->pkt, pkt, माप(recv_pkt_info->pkt));
		INIT_WORK(&recv_pkt_info->work, vmci_transport_recv_pkt_work);

		schedule_work(&recv_pkt_info->work);
		/* Clear sk so that the reference count incremented by one of
		 * the Find functions above is not decremented below.  We need
		 * that reference count क्रम the packet handler we've scheduled
		 * to run.
		 */
		sk = शून्य;
	पूर्ण

out:
	अगर (sk)
		sock_put(sk);

	वापस err;
पूर्ण

अटल व्योम vmci_transport_handle_detach(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk;

	vsk = vsock_sk(sk);
	अगर (!vmci_handle_is_invalid(vmci_trans(vsk)->qp_handle)) अणु
		sock_set_flag(sk, SOCK_DONE);

		/* On a detach the peer will not be sending or receiving
		 * anymore.
		 */
		vsk->peer_shutकरोwn = SHUTDOWN_MASK;

		/* We should not be sending anymore since the peer won't be
		 * there to receive, but we can still receive अगर there is data
		 * left in our consume queue. If the local endpoपूर्णांक is a host,
		 * we can't call vsock_stream_has_data, since that may block,
		 * but a host endpoपूर्णांक can't पढ़ो data once the VM has
		 * detached, so there is no available data in that हाल.
		 */
		अगर (vsk->local_addr.svm_cid == VMADDR_CID_HOST ||
		    vsock_stream_has_data(vsk) <= 0) अणु
			अगर (sk->sk_state == TCP_SYN_SENT) अणु
				/* The peer may detach from a queue pair जबतक
				 * we are still in the connecting state, i.e.,
				 * अगर the peer VM is समाप्तed after attaching to
				 * a queue pair, but beक्रमe we complete the
				 * handshake. In that हाल, we treat the detach
				 * event like a reset.
				 */

				sk->sk_state = TCP_CLOSE;
				sk->sk_err = ECONNRESET;
				sk->sk_error_report(sk);
				वापस;
			पूर्ण
			sk->sk_state = TCP_CLOSE;
		पूर्ण
		sk->sk_state_change(sk);
	पूर्ण
पूर्ण

अटल व्योम vmci_transport_peer_detach_cb(u32 sub_id,
					  स्थिर काष्ठा vmci_event_data *e_data,
					  व्योम *client_data)
अणु
	काष्ठा vmci_transport *trans = client_data;
	स्थिर काष्ठा vmci_event_payload_qp *e_payload;

	e_payload = vmci_event_data_स्थिर_payload(e_data);

	/* XXX This is lame, we should provide a way to lookup sockets by
	 * qp_handle.
	 */
	अगर (vmci_handle_is_invalid(e_payload->handle) ||
	    !vmci_handle_is_equal(trans->qp_handle, e_payload->handle))
		वापस;

	/* We करोn't ask क्रम delayed CBs when we subscribe to this event (we
	 * pass 0 as flags to vmci_event_subscribe()).  VMCI makes no
	 * guarantees in that हाल about what context we might be running in,
	 * so it could be BH or process, blockable or non-blockable.  So we
	 * need to account क्रम all possible contexts here.
	 */
	spin_lock_bh(&trans->lock);
	अगर (!trans->sk)
		जाओ out;

	/* Apart from here, trans->lock is only grabbed as part of sk deकाष्ठा,
	 * where trans->sk isn't locked.
	 */
	bh_lock_sock(trans->sk);

	vmci_transport_handle_detach(trans->sk);

	bh_unlock_sock(trans->sk);
 out:
	spin_unlock_bh(&trans->lock);
पूर्ण

अटल व्योम vmci_transport_qp_resumed_cb(u32 sub_id,
					 स्थिर काष्ठा vmci_event_data *e_data,
					 व्योम *client_data)
अणु
	vsock_क्रम_each_connected_socket(vmci_transport_handle_detach);
पूर्ण

अटल व्योम vmci_transport_recv_pkt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vmci_transport_recv_pkt_info *recv_pkt_info;
	काष्ठा vmci_transport_packet *pkt;
	काष्ठा sock *sk;

	recv_pkt_info =
		container_of(work, काष्ठा vmci_transport_recv_pkt_info, work);
	sk = recv_pkt_info->sk;
	pkt = &recv_pkt_info->pkt;

	lock_sock(sk);

	/* The local context ID may be out of date. */
	vsock_sk(sk)->local_addr.svm_cid = pkt->dg.dst.context;

	चयन (sk->sk_state) अणु
	हाल TCP_LISTEN:
		vmci_transport_recv_listen(sk, pkt);
		अवरोध;
	हाल TCP_SYN_SENT:
		/* Processing of pending connections क्रम servers goes through
		 * the listening socket, so see vmci_transport_recv_listen()
		 * क्रम that path.
		 */
		vmci_transport_recv_connecting_client(sk, pkt);
		अवरोध;
	हाल TCP_ESTABLISHED:
		vmci_transport_recv_connected(sk, pkt);
		अवरोध;
	शेष:
		/* Because this function करोes not run in the same context as
		 * vmci_transport_recv_stream_cb it is possible that the
		 * socket has बंदd. We need to let the other side know or it
		 * could be sitting in a connect and hang क्रमever. Send a
		 * reset to prevent that.
		 */
		vmci_transport_send_reset(sk, pkt);
		अवरोध;
	पूर्ण

	release_sock(sk);
	kमुक्त(recv_pkt_info);
	/* Release reference obtained in the stream callback when we fetched
	 * this socket out of the bound or connected list.
	 */
	sock_put(sk);
पूर्ण

अटल पूर्णांक vmci_transport_recv_listen(काष्ठा sock *sk,
				      काष्ठा vmci_transport_packet *pkt)
अणु
	काष्ठा sock *pending;
	काष्ठा vsock_sock *vpending;
	पूर्णांक err;
	u64 qp_size;
	bool old_request = false;
	bool old_pkt_proto = false;

	/* Because we are in the listen state, we could be receiving a packet
	 * क्रम ourself or any previous connection requests that we received.
	 * If it's the latter, we try to find a socket in our list of pending
	 * connections and, अगर we करो, call the appropriate handler क्रम the
	 * state that that socket is in.  Otherwise we try to service the
	 * connection request.
	 */
	pending = vmci_transport_get_pending(sk, pkt);
	अगर (pending) अणु
		lock_sock(pending);

		/* The local context ID may be out of date. */
		vsock_sk(pending)->local_addr.svm_cid = pkt->dg.dst.context;

		चयन (pending->sk_state) अणु
		हाल TCP_SYN_SENT:
			err = vmci_transport_recv_connecting_server(sk,
								    pending,
								    pkt);
			अवरोध;
		शेष:
			vmci_transport_send_reset(pending, pkt);
			err = -EINVAL;
		पूर्ण

		अगर (err < 0)
			vsock_हटाओ_pending(sk, pending);

		release_sock(pending);
		vmci_transport_release_pending(pending);

		वापस err;
	पूर्ण

	/* The listen state only accepts connection requests.  Reply with a
	 * reset unless we received a reset.
	 */

	अगर (!(pkt->type == VMCI_TRANSPORT_PACKET_TYPE_REQUEST ||
	      pkt->type == VMCI_TRANSPORT_PACKET_TYPE_REQUEST2)) अणु
		vmci_transport_reply_reset(pkt);
		वापस -EINVAL;
	पूर्ण

	अगर (pkt->u.size == 0) अणु
		vmci_transport_reply_reset(pkt);
		वापस -EINVAL;
	पूर्ण

	/* If this socket can't accommodate this connection request, we send a
	 * reset.  Otherwise we create and initialize a child socket and reply
	 * with a connection negotiation.
	 */
	अगर (sk->sk_ack_backlog >= sk->sk_max_ack_backlog) अणु
		vmci_transport_reply_reset(pkt);
		वापस -ECONNREFUSED;
	पूर्ण

	pending = vsock_create_connected(sk);
	अगर (!pending) अणु
		vmci_transport_send_reset(sk, pkt);
		वापस -ENOMEM;
	पूर्ण

	vpending = vsock_sk(pending);

	vsock_addr_init(&vpending->local_addr, pkt->dg.dst.context,
			pkt->dst_port);
	vsock_addr_init(&vpending->remote_addr, pkt->dg.src.context,
			pkt->src_port);

	err = vsock_assign_transport(vpending, vsock_sk(sk));
	/* Transport asचिन्हित (looking at remote_addr) must be the same
	 * where we received the request.
	 */
	अगर (err || !vmci_check_transport(vpending)) अणु
		vmci_transport_send_reset(sk, pkt);
		sock_put(pending);
		वापस err;
	पूर्ण

	/* If the proposed size fits within our min/max, accept it. Otherwise
	 * propose our own size.
	 */
	अगर (pkt->u.size >= vpending->buffer_min_size &&
	    pkt->u.size <= vpending->buffer_max_size) अणु
		qp_size = pkt->u.size;
	पूर्ण अन्यथा अणु
		qp_size = vpending->buffer_size;
	पूर्ण

	/* Figure out अगर we are using old or new requests based on the
	 * overrides pkt types sent by our peer.
	 */
	अगर (vmci_transport_old_proto_override(&old_pkt_proto)) अणु
		old_request = old_pkt_proto;
	पूर्ण अन्यथा अणु
		अगर (pkt->type == VMCI_TRANSPORT_PACKET_TYPE_REQUEST)
			old_request = true;
		अन्यथा अगर (pkt->type == VMCI_TRANSPORT_PACKET_TYPE_REQUEST2)
			old_request = false;

	पूर्ण

	अगर (old_request) अणु
		/* Handle a REQUEST (or override) */
		u16 version = VSOCK_PROTO_INVALID;
		अगर (vmci_transport_proto_to_notअगरy_काष्ठा(
			pending, &version, true))
			err = vmci_transport_send_negotiate(pending, qp_size);
		अन्यथा
			err = -EINVAL;

	पूर्ण अन्यथा अणु
		/* Handle a REQUEST2 (or override) */
		पूर्णांक proto_पूर्णांक = pkt->proto;
		पूर्णांक pos;
		u16 active_proto_version = 0;

		/* The list of possible protocols is the पूर्णांकersection of all
		 * protocols the client supports ... plus all the protocols we
		 * support.
		 */
		proto_पूर्णांक &= vmci_transport_new_proto_supported_versions();

		/* We choose the highest possible protocol version and use that
		 * one.
		 */
		pos = fls(proto_पूर्णांक);
		अगर (pos) अणु
			active_proto_version = (1 << (pos - 1));
			अगर (vmci_transport_proto_to_notअगरy_काष्ठा(
				pending, &active_proto_version, false))
				err = vmci_transport_send_negotiate2(pending,
							qp_size,
							active_proto_version);
			अन्यथा
				err = -EINVAL;

		पूर्ण अन्यथा अणु
			err = -EINVAL;
		पूर्ण
	पूर्ण

	अगर (err < 0) अणु
		vmci_transport_send_reset(sk, pkt);
		sock_put(pending);
		err = vmci_transport_error_to_vsock_error(err);
		जाओ out;
	पूर्ण

	vsock_add_pending(sk, pending);
	sk_acceptq_added(sk);

	pending->sk_state = TCP_SYN_SENT;
	vmci_trans(vpending)->produce_size =
		vmci_trans(vpending)->consume_size = qp_size;
	vpending->buffer_size = qp_size;

	vmci_trans(vpending)->notअगरy_ops->process_request(pending);

	/* We might never receive another message क्रम this socket and it's not
	 * connected to any process, so we have to ensure it माला_लो cleaned up
	 * ourself.  Our delayed work function will take care of that.  Note
	 * that we करो not ever cancel this function since we have few
	 * guarantees about its state when calling cancel_delayed_work().
	 * Instead we hold a reference on the socket क्रम that function and make
	 * it capable of handling हालs where it needs to करो nothing but
	 * release that reference.
	 */
	vpending->listener = sk;
	sock_hold(sk);
	sock_hold(pending);
	schedule_delayed_work(&vpending->pending_work, HZ);

out:
	वापस err;
पूर्ण

अटल पूर्णांक
vmci_transport_recv_connecting_server(काष्ठा sock *listener,
				      काष्ठा sock *pending,
				      काष्ठा vmci_transport_packet *pkt)
अणु
	काष्ठा vsock_sock *vpending;
	काष्ठा vmci_handle handle;
	काष्ठा vmci_qp *qpair;
	bool is_local;
	u32 flags;
	u32 detach_sub_id;
	पूर्णांक err;
	पूर्णांक skerr;

	vpending = vsock_sk(pending);
	detach_sub_id = VMCI_INVALID_ID;

	चयन (pkt->type) अणु
	हाल VMCI_TRANSPORT_PACKET_TYPE_OFFER:
		अगर (vmci_handle_is_invalid(pkt->u.handle)) अणु
			vmci_transport_send_reset(pending, pkt);
			skerr = EPROTO;
			err = -EINVAL;
			जाओ destroy;
		पूर्ण
		अवरोध;
	शेष:
		/* Close and cleanup the connection. */
		vmci_transport_send_reset(pending, pkt);
		skerr = EPROTO;
		err = pkt->type == VMCI_TRANSPORT_PACKET_TYPE_RST ? 0 : -EINVAL;
		जाओ destroy;
	पूर्ण

	/* In order to complete the connection we need to attach to the offered
	 * queue pair and send an attach notअगरication.  We also subscribe to the
	 * detach event so we know when our peer goes away, and we करो that
	 * beक्रमe attaching so we करोn't miss an event.  If all this succeeds,
	 * we update our state and wakeup anything रुकोing in accept() क्रम a
	 * connection.
	 */

	/* We करोn't care about attach since we ensure the other side has
	 * attached by specअगरying the ATTACH_ONLY flag below.
	 */
	err = vmci_event_subscribe(VMCI_EVENT_QP_PEER_DETACH,
				   vmci_transport_peer_detach_cb,
				   vmci_trans(vpending), &detach_sub_id);
	अगर (err < VMCI_SUCCESS) अणु
		vmci_transport_send_reset(pending, pkt);
		err = vmci_transport_error_to_vsock_error(err);
		skerr = -err;
		जाओ destroy;
	पूर्ण

	vmci_trans(vpending)->detach_sub_id = detach_sub_id;

	/* Now attach to the queue pair the client created. */
	handle = pkt->u.handle;

	/* vpending->local_addr always has a context id so we करो not need to
	 * worry about VMADDR_CID_ANY in this हाल.
	 */
	is_local =
	    vpending->remote_addr.svm_cid == vpending->local_addr.svm_cid;
	flags = VMCI_QPFLAG_ATTACH_ONLY;
	flags |= is_local ? VMCI_QPFLAG_LOCAL : 0;

	err = vmci_transport_queue_pair_alloc(
					&qpair,
					&handle,
					vmci_trans(vpending)->produce_size,
					vmci_trans(vpending)->consume_size,
					pkt->dg.src.context,
					flags,
					vmci_transport_is_trusted(
						vpending,
						vpending->remote_addr.svm_cid));
	अगर (err < 0) अणु
		vmci_transport_send_reset(pending, pkt);
		skerr = -err;
		जाओ destroy;
	पूर्ण

	vmci_trans(vpending)->qp_handle = handle;
	vmci_trans(vpending)->qpair = qpair;

	/* When we send the attach message, we must be पढ़ोy to handle incoming
	 * control messages on the newly connected socket. So we move the
	 * pending socket to the connected state beक्रमe sending the attach
	 * message. Otherwise, an incoming packet triggered by the attach being
	 * received by the peer may be processed concurrently with what happens
	 * below after sending the attach message, and that incoming packet
	 * will find the listening socket instead of the (currently) pending
	 * socket. Note that enqueueing the socket increments the reference
	 * count, so even अगर a reset comes beक्रमe the connection is accepted,
	 * the socket will be valid until it is हटाओd from the queue.
	 *
	 * If we fail sending the attach below, we हटाओ the socket from the
	 * connected list and move the socket to TCP_CLOSE beक्रमe
	 * releasing the lock, so a pending slow path processing of an incoming
	 * packet will not see the socket in the connected state in that हाल.
	 */
	pending->sk_state = TCP_ESTABLISHED;

	vsock_insert_connected(vpending);

	/* Notअगरy our peer of our attach. */
	err = vmci_transport_send_attach(pending, handle);
	अगर (err < 0) अणु
		vsock_हटाओ_connected(vpending);
		pr_err("Could not send attach\n");
		vmci_transport_send_reset(pending, pkt);
		err = vmci_transport_error_to_vsock_error(err);
		skerr = -err;
		जाओ destroy;
	पूर्ण

	/* We have a connection. Move the now connected socket from the
	 * listener's pending list to the accept queue so callers of accept()
	 * can find it.
	 */
	vsock_हटाओ_pending(listener, pending);
	vsock_enqueue_accept(listener, pending);

	/* Callers of accept() will be be रुकोing on the listening socket, not
	 * the pending socket.
	 */
	listener->sk_data_पढ़ोy(listener);

	वापस 0;

destroy:
	pending->sk_err = skerr;
	pending->sk_state = TCP_CLOSE;
	/* As दीर्घ as we drop our reference, all necessary cleanup will handle
	 * when the cleanup function drops its reference and our deकाष्ठा
	 * implementation is called.  Note that since the listen handler will
	 * हटाओ pending from the pending list upon our failure, the cleanup
	 * function won't drop the additional reference, which is why we करो it
	 * here.
	 */
	sock_put(pending);

	वापस err;
पूर्ण

अटल पूर्णांक
vmci_transport_recv_connecting_client(काष्ठा sock *sk,
				      काष्ठा vmci_transport_packet *pkt)
अणु
	काष्ठा vsock_sock *vsk;
	पूर्णांक err;
	पूर्णांक skerr;

	vsk = vsock_sk(sk);

	चयन (pkt->type) अणु
	हाल VMCI_TRANSPORT_PACKET_TYPE_ATTACH:
		अगर (vmci_handle_is_invalid(pkt->u.handle) ||
		    !vmci_handle_is_equal(pkt->u.handle,
					  vmci_trans(vsk)->qp_handle)) अणु
			skerr = EPROTO;
			err = -EINVAL;
			जाओ destroy;
		पूर्ण

		/* Signअगरy the socket is connected and wakeup the रुकोer in
		 * connect(). Also place the socket in the connected table क्रम
		 * accounting (it can alपढ़ोy be found since it's in the bound
		 * table).
		 */
		sk->sk_state = TCP_ESTABLISHED;
		sk->sk_socket->state = SS_CONNECTED;
		vsock_insert_connected(vsk);
		sk->sk_state_change(sk);

		अवरोध;
	हाल VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE:
	हाल VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE2:
		अगर (pkt->u.size == 0
		    || pkt->dg.src.context != vsk->remote_addr.svm_cid
		    || pkt->src_port != vsk->remote_addr.svm_port
		    || !vmci_handle_is_invalid(vmci_trans(vsk)->qp_handle)
		    || vmci_trans(vsk)->qpair
		    || vmci_trans(vsk)->produce_size != 0
		    || vmci_trans(vsk)->consume_size != 0
		    || vmci_trans(vsk)->detach_sub_id != VMCI_INVALID_ID) अणु
			skerr = EPROTO;
			err = -EINVAL;

			जाओ destroy;
		पूर्ण

		err = vmci_transport_recv_connecting_client_negotiate(sk, pkt);
		अगर (err) अणु
			skerr = -err;
			जाओ destroy;
		पूर्ण

		अवरोध;
	हाल VMCI_TRANSPORT_PACKET_TYPE_INVALID:
		err = vmci_transport_recv_connecting_client_invalid(sk, pkt);
		अगर (err) अणु
			skerr = -err;
			जाओ destroy;
		पूर्ण

		अवरोध;
	हाल VMCI_TRANSPORT_PACKET_TYPE_RST:
		/* Older versions of the linux code (WS 6.5 / ESX 4.0) used to
		 * जारी processing here after they sent an INVALID packet.
		 * This meant that we got a RST after the INVALID. We ignore a
		 * RST after an INVALID. The common code करोesn't send the RST
		 * ... so we can hang अगर an old version of the common code
		 * fails between getting a REQUEST and sending an OFFER back.
		 * Not much we can करो about it... except hope that it करोesn't
		 * happen.
		 */
		अगर (vsk->ignore_connecting_rst) अणु
			vsk->ignore_connecting_rst = false;
		पूर्ण अन्यथा अणु
			skerr = ECONNRESET;
			err = 0;
			जाओ destroy;
		पूर्ण

		अवरोध;
	शेष:
		/* Close and cleanup the connection. */
		skerr = EPROTO;
		err = -EINVAL;
		जाओ destroy;
	पूर्ण

	वापस 0;

destroy:
	vmci_transport_send_reset(sk, pkt);

	sk->sk_state = TCP_CLOSE;
	sk->sk_err = skerr;
	sk->sk_error_report(sk);
	वापस err;
पूर्ण

अटल पूर्णांक vmci_transport_recv_connecting_client_negotiate(
					काष्ठा sock *sk,
					काष्ठा vmci_transport_packet *pkt)
अणु
	पूर्णांक err;
	काष्ठा vsock_sock *vsk;
	काष्ठा vmci_handle handle;
	काष्ठा vmci_qp *qpair;
	u32 detach_sub_id;
	bool is_local;
	u32 flags;
	bool old_proto = true;
	bool old_pkt_proto;
	u16 version;

	vsk = vsock_sk(sk);
	handle = VMCI_INVALID_HANDLE;
	detach_sub_id = VMCI_INVALID_ID;

	/* If we have gotten here then we should be past the poपूर्णांक where old
	 * linux vsock could have sent the bogus rst.
	 */
	vsk->sent_request = false;
	vsk->ignore_connecting_rst = false;

	/* Verअगरy that we're OK with the proposed queue pair size */
	अगर (pkt->u.size < vsk->buffer_min_size ||
	    pkt->u.size > vsk->buffer_max_size) अणु
		err = -EINVAL;
		जाओ destroy;
	पूर्ण

	/* At this poपूर्णांक we know the CID the peer is using to talk to us. */

	अगर (vsk->local_addr.svm_cid == VMADDR_CID_ANY)
		vsk->local_addr.svm_cid = pkt->dg.dst.context;

	/* Setup the notअगरy ops to be the highest supported version that both
	 * the server and the client support.
	 */

	अगर (vmci_transport_old_proto_override(&old_pkt_proto)) अणु
		old_proto = old_pkt_proto;
	पूर्ण अन्यथा अणु
		अगर (pkt->type == VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE)
			old_proto = true;
		अन्यथा अगर (pkt->type == VMCI_TRANSPORT_PACKET_TYPE_NEGOTIATE2)
			old_proto = false;

	पूर्ण

	अगर (old_proto)
		version = VSOCK_PROTO_INVALID;
	अन्यथा
		version = pkt->proto;

	अगर (!vmci_transport_proto_to_notअगरy_काष्ठा(sk, &version, old_proto)) अणु
		err = -EINVAL;
		जाओ destroy;
	पूर्ण

	/* Subscribe to detach events first.
	 *
	 * XXX We attach once क्रम each queue pair created क्रम now so it is easy
	 * to find the socket (it's provided), but later we should only
	 * subscribe once and add a way to lookup sockets by queue pair handle.
	 */
	err = vmci_event_subscribe(VMCI_EVENT_QP_PEER_DETACH,
				   vmci_transport_peer_detach_cb,
				   vmci_trans(vsk), &detach_sub_id);
	अगर (err < VMCI_SUCCESS) अणु
		err = vmci_transport_error_to_vsock_error(err);
		जाओ destroy;
	पूर्ण

	/* Make VMCI select the handle क्रम us. */
	handle = VMCI_INVALID_HANDLE;
	is_local = vsk->remote_addr.svm_cid == vsk->local_addr.svm_cid;
	flags = is_local ? VMCI_QPFLAG_LOCAL : 0;

	err = vmci_transport_queue_pair_alloc(&qpair,
					      &handle,
					      pkt->u.size,
					      pkt->u.size,
					      vsk->remote_addr.svm_cid,
					      flags,
					      vmci_transport_is_trusted(
						  vsk,
						  vsk->
						  remote_addr.svm_cid));
	अगर (err < 0)
		जाओ destroy;

	err = vmci_transport_send_qp_offer(sk, handle);
	अगर (err < 0) अणु
		err = vmci_transport_error_to_vsock_error(err);
		जाओ destroy;
	पूर्ण

	vmci_trans(vsk)->qp_handle = handle;
	vmci_trans(vsk)->qpair = qpair;

	vmci_trans(vsk)->produce_size = vmci_trans(vsk)->consume_size =
		pkt->u.size;

	vmci_trans(vsk)->detach_sub_id = detach_sub_id;

	vmci_trans(vsk)->notअगरy_ops->process_negotiate(sk);

	वापस 0;

destroy:
	अगर (detach_sub_id != VMCI_INVALID_ID)
		vmci_event_unsubscribe(detach_sub_id);

	अगर (!vmci_handle_is_invalid(handle))
		vmci_qpair_detach(&qpair);

	वापस err;
पूर्ण

अटल पूर्णांक
vmci_transport_recv_connecting_client_invalid(काष्ठा sock *sk,
					      काष्ठा vmci_transport_packet *pkt)
अणु
	पूर्णांक err = 0;
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	अगर (vsk->sent_request) अणु
		vsk->sent_request = false;
		vsk->ignore_connecting_rst = true;

		err = vmci_transport_send_conn_request(sk, vsk->buffer_size);
		अगर (err < 0)
			err = vmci_transport_error_to_vsock_error(err);
		अन्यथा
			err = 0;

	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक vmci_transport_recv_connected(काष्ठा sock *sk,
					 काष्ठा vmci_transport_packet *pkt)
अणु
	काष्ठा vsock_sock *vsk;
	bool pkt_processed = false;

	/* In हालs where we are closing the connection, it's sufficient to
	 * mark the state change (and maybe error) and wake up any रुकोing
	 * thपढ़ोs. Since this is a connected socket, it's owned by a user
	 * process and will be cleaned up when the failure is passed back on
	 * the current or next प्रणाली call.  Our प्रणाली call implementations
	 * must thereक्रमe check क्रम error and state changes on entry and when
	 * being awoken.
	 */
	चयन (pkt->type) अणु
	हाल VMCI_TRANSPORT_PACKET_TYPE_SHUTDOWN:
		अगर (pkt->u.mode) अणु
			vsk = vsock_sk(sk);

			vsk->peer_shutकरोwn |= pkt->u.mode;
			sk->sk_state_change(sk);
		पूर्ण
		अवरोध;

	हाल VMCI_TRANSPORT_PACKET_TYPE_RST:
		vsk = vsock_sk(sk);
		/* It is possible that we sent our peer a message (e.g a
		 * WAITING_READ) right beक्रमe we got notअगरied that the peer had
		 * detached. If that happens then we can get a RST pkt back
		 * from our peer even though there is data available क्रम us to
		 * पढ़ो. In that हाल, करोn't shutकरोwn the socket completely but
		 * instead allow the local client to finish पढ़ोing data off
		 * the queuepair. Always treat a RST pkt in connected mode like
		 * a clean shutकरोwn.
		 */
		sock_set_flag(sk, SOCK_DONE);
		vsk->peer_shutकरोwn = SHUTDOWN_MASK;
		अगर (vsock_stream_has_data(vsk) <= 0)
			sk->sk_state = TCP_CLOSING;

		sk->sk_state_change(sk);
		अवरोध;

	शेष:
		vsk = vsock_sk(sk);
		vmci_trans(vsk)->notअगरy_ops->handle_notअगरy_pkt(
				sk, pkt, false, शून्य, शून्य,
				&pkt_processed);
		अगर (!pkt_processed)
			वापस -EINVAL;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmci_transport_socket_init(काष्ठा vsock_sock *vsk,
				      काष्ठा vsock_sock *psk)
अणु
	vsk->trans = kदो_स्मृति(माप(काष्ठा vmci_transport), GFP_KERNEL);
	अगर (!vsk->trans)
		वापस -ENOMEM;

	vmci_trans(vsk)->dg_handle = VMCI_INVALID_HANDLE;
	vmci_trans(vsk)->qp_handle = VMCI_INVALID_HANDLE;
	vmci_trans(vsk)->qpair = शून्य;
	vmci_trans(vsk)->produce_size = vmci_trans(vsk)->consume_size = 0;
	vmci_trans(vsk)->detach_sub_id = VMCI_INVALID_ID;
	vmci_trans(vsk)->notअगरy_ops = शून्य;
	INIT_LIST_HEAD(&vmci_trans(vsk)->elem);
	vmci_trans(vsk)->sk = &vsk->sk;
	spin_lock_init(&vmci_trans(vsk)->lock);

	वापस 0;
पूर्ण

अटल व्योम vmci_transport_मुक्त_resources(काष्ठा list_head *transport_list)
अणु
	जबतक (!list_empty(transport_list)) अणु
		काष्ठा vmci_transport *transport =
		    list_first_entry(transport_list, काष्ठा vmci_transport,
				     elem);
		list_del(&transport->elem);

		अगर (transport->detach_sub_id != VMCI_INVALID_ID) अणु
			vmci_event_unsubscribe(transport->detach_sub_id);
			transport->detach_sub_id = VMCI_INVALID_ID;
		पूर्ण

		अगर (!vmci_handle_is_invalid(transport->qp_handle)) अणु
			vmci_qpair_detach(&transport->qpair);
			transport->qp_handle = VMCI_INVALID_HANDLE;
			transport->produce_size = 0;
			transport->consume_size = 0;
		पूर्ण

		kमुक्त(transport);
	पूर्ण
पूर्ण

अटल व्योम vmci_transport_cleanup(काष्ठा work_काष्ठा *work)
अणु
	LIST_HEAD(pending);

	spin_lock_bh(&vmci_transport_cleanup_lock);
	list_replace_init(&vmci_transport_cleanup_list, &pending);
	spin_unlock_bh(&vmci_transport_cleanup_lock);
	vmci_transport_मुक्त_resources(&pending);
पूर्ण

अटल व्योम vmci_transport_deकाष्ठा(काष्ठा vsock_sock *vsk)
अणु
	/* transport can be शून्य अगर we hit a failure at init() समय */
	अगर (!vmci_trans(vsk))
		वापस;

	/* Ensure that the detach callback करोesn't use the sk/vsk
	 * we are about to deकाष्ठा.
	 */
	spin_lock_bh(&vmci_trans(vsk)->lock);
	vmci_trans(vsk)->sk = शून्य;
	spin_unlock_bh(&vmci_trans(vsk)->lock);

	अगर (vmci_trans(vsk)->notअगरy_ops)
		vmci_trans(vsk)->notअगरy_ops->socket_deकाष्ठा(vsk);

	spin_lock_bh(&vmci_transport_cleanup_lock);
	list_add(&vmci_trans(vsk)->elem, &vmci_transport_cleanup_list);
	spin_unlock_bh(&vmci_transport_cleanup_lock);
	schedule_work(&vmci_transport_cleanup_work);

	vsk->trans = शून्य;
पूर्ण

अटल व्योम vmci_transport_release(काष्ठा vsock_sock *vsk)
अणु
	vsock_हटाओ_sock(vsk);

	अगर (!vmci_handle_is_invalid(vmci_trans(vsk)->dg_handle)) अणु
		vmci_datagram_destroy_handle(vmci_trans(vsk)->dg_handle);
		vmci_trans(vsk)->dg_handle = VMCI_INVALID_HANDLE;
	पूर्ण
पूर्ण

अटल पूर्णांक vmci_transport_dgram_bind(काष्ठा vsock_sock *vsk,
				     काष्ठा sockaddr_vm *addr)
अणु
	u32 port;
	u32 flags;
	पूर्णांक err;

	/* VMCI will select a resource ID क्रम us अगर we provide
	 * VMCI_INVALID_ID.
	 */
	port = addr->svm_port == VMADDR_PORT_ANY ?
			VMCI_INVALID_ID : addr->svm_port;

	अगर (port <= LAST_RESERVED_PORT && !capable(CAP_NET_BIND_SERVICE))
		वापस -EACCES;

	flags = addr->svm_cid == VMADDR_CID_ANY ?
				VMCI_FLAG_ANYCID_DG_HND : 0;

	err = vmci_transport_datagram_create_hnd(port, flags,
						 vmci_transport_recv_dgram_cb,
						 &vsk->sk,
						 &vmci_trans(vsk)->dg_handle);
	अगर (err < VMCI_SUCCESS)
		वापस vmci_transport_error_to_vsock_error(err);
	vsock_addr_init(&vsk->local_addr, addr->svm_cid,
			vmci_trans(vsk)->dg_handle.resource);

	वापस 0;
पूर्ण

अटल पूर्णांक vmci_transport_dgram_enqueue(
	काष्ठा vsock_sock *vsk,
	काष्ठा sockaddr_vm *remote_addr,
	काष्ठा msghdr *msg,
	माप_प्रकार len)
अणु
	पूर्णांक err;
	काष्ठा vmci_datagram *dg;

	अगर (len > VMCI_MAX_DG_PAYLOAD_SIZE)
		वापस -EMSGSIZE;

	अगर (!vmci_transport_allow_dgram(vsk, remote_addr->svm_cid))
		वापस -EPERM;

	/* Allocate a buffer क्रम the user's message and our packet header. */
	dg = kदो_स्मृति(len + माप(*dg), GFP_KERNEL);
	अगर (!dg)
		वापस -ENOMEM;

	स_नकल_from_msg(VMCI_DG_PAYLOAD(dg), msg, len);

	dg->dst = vmci_make_handle(remote_addr->svm_cid,
				   remote_addr->svm_port);
	dg->src = vmci_make_handle(vsk->local_addr.svm_cid,
				   vsk->local_addr.svm_port);
	dg->payload_size = len;

	err = vmci_datagram_send(dg);
	kमुक्त(dg);
	अगर (err < 0)
		वापस vmci_transport_error_to_vsock_error(err);

	वापस err - माप(*dg);
पूर्ण

अटल पूर्णांक vmci_transport_dgram_dequeue(काष्ठा vsock_sock *vsk,
					काष्ठा msghdr *msg, माप_प्रकार len,
					पूर्णांक flags)
अणु
	पूर्णांक err;
	पूर्णांक noblock;
	काष्ठा vmci_datagram *dg;
	माप_प्रकार payload_len;
	काष्ठा sk_buff *skb;

	noblock = flags & MSG_DONTWAIT;

	अगर (flags & MSG_OOB || flags & MSG_ERRQUEUE)
		वापस -EOPNOTSUPP;

	/* Retrieve the head sk_buff from the socket's receive queue. */
	err = 0;
	skb = skb_recv_datagram(&vsk->sk, flags, noblock, &err);
	अगर (!skb)
		वापस err;

	dg = (काष्ठा vmci_datagram *)skb->data;
	अगर (!dg)
		/* err is 0, meaning we पढ़ो zero bytes. */
		जाओ out;

	payload_len = dg->payload_size;
	/* Ensure the sk_buff matches the payload size claimed in the packet. */
	अगर (payload_len != skb->len - माप(*dg)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (payload_len > len) अणु
		payload_len = len;
		msg->msg_flags |= MSG_TRUNC;
	पूर्ण

	/* Place the datagram payload in the user's iovec. */
	err = skb_copy_datagram_msg(skb, माप(*dg), msg, payload_len);
	अगर (err)
		जाओ out;

	अगर (msg->msg_name) अणु
		/* Provide the address of the sender. */
		DECLARE_SOCKADDR(काष्ठा sockaddr_vm *, vm_addr, msg->msg_name);
		vsock_addr_init(vm_addr, dg->src.context, dg->src.resource);
		msg->msg_namelen = माप(*vm_addr);
	पूर्ण
	err = payload_len;

out:
	skb_मुक्त_datagram(&vsk->sk, skb);
	वापस err;
पूर्ण

अटल bool vmci_transport_dgram_allow(u32 cid, u32 port)
अणु
	अगर (cid == VMADDR_CID_HYPERVISOR) अणु
		/* Registrations of PBRPC Servers करो not modअगरy VMX/Hypervisor
		 * state and are allowed.
		 */
		वापस port == VMCI_UNITY_PBRPC_REGISTER;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक vmci_transport_connect(काष्ठा vsock_sock *vsk)
अणु
	पूर्णांक err;
	bool old_pkt_proto = false;
	काष्ठा sock *sk = &vsk->sk;

	अगर (vmci_transport_old_proto_override(&old_pkt_proto) &&
		old_pkt_proto) अणु
		err = vmci_transport_send_conn_request(sk, vsk->buffer_size);
		अगर (err < 0) अणु
			sk->sk_state = TCP_CLOSE;
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक supported_proto_versions =
			vmci_transport_new_proto_supported_versions();
		err = vmci_transport_send_conn_request2(sk, vsk->buffer_size,
				supported_proto_versions);
		अगर (err < 0) अणु
			sk->sk_state = TCP_CLOSE;
			वापस err;
		पूर्ण

		vsk->sent_request = true;
	पूर्ण

	वापस err;
पूर्ण

अटल sमाप_प्रकार vmci_transport_stream_dequeue(
	काष्ठा vsock_sock *vsk,
	काष्ठा msghdr *msg,
	माप_प्रकार len,
	पूर्णांक flags)
अणु
	अगर (flags & MSG_PEEK)
		वापस vmci_qpair_peekv(vmci_trans(vsk)->qpair, msg, len, 0);
	अन्यथा
		वापस vmci_qpair_dequev(vmci_trans(vsk)->qpair, msg, len, 0);
पूर्ण

अटल sमाप_प्रकार vmci_transport_stream_enqueue(
	काष्ठा vsock_sock *vsk,
	काष्ठा msghdr *msg,
	माप_प्रकार len)
अणु
	वापस vmci_qpair_enquev(vmci_trans(vsk)->qpair, msg, len, 0);
पूर्ण

अटल s64 vmci_transport_stream_has_data(काष्ठा vsock_sock *vsk)
अणु
	वापस vmci_qpair_consume_buf_पढ़ोy(vmci_trans(vsk)->qpair);
पूर्ण

अटल s64 vmci_transport_stream_has_space(काष्ठा vsock_sock *vsk)
अणु
	वापस vmci_qpair_produce_मुक्त_space(vmci_trans(vsk)->qpair);
पूर्ण

अटल u64 vmci_transport_stream_rcvhiwat(काष्ठा vsock_sock *vsk)
अणु
	वापस vmci_trans(vsk)->consume_size;
पूर्ण

अटल bool vmci_transport_stream_is_active(काष्ठा vsock_sock *vsk)
अणु
	वापस !vmci_handle_is_invalid(vmci_trans(vsk)->qp_handle);
पूर्ण

अटल पूर्णांक vmci_transport_notअगरy_poll_in(
	काष्ठा vsock_sock *vsk,
	माप_प्रकार target,
	bool *data_पढ़ोy_now)
अणु
	वापस vmci_trans(vsk)->notअगरy_ops->poll_in(
			&vsk->sk, target, data_पढ़ोy_now);
पूर्ण

अटल पूर्णांक vmci_transport_notअगरy_poll_out(
	काष्ठा vsock_sock *vsk,
	माप_प्रकार target,
	bool *space_available_now)
अणु
	वापस vmci_trans(vsk)->notअगरy_ops->poll_out(
			&vsk->sk, target, space_available_now);
पूर्ण

अटल पूर्णांक vmci_transport_notअगरy_recv_init(
	काष्ठा vsock_sock *vsk,
	माप_प्रकार target,
	काष्ठा vsock_transport_recv_notअगरy_data *data)
अणु
	वापस vmci_trans(vsk)->notअगरy_ops->recv_init(
			&vsk->sk, target,
			(काष्ठा vmci_transport_recv_notअगरy_data *)data);
पूर्ण

अटल पूर्णांक vmci_transport_notअगरy_recv_pre_block(
	काष्ठा vsock_sock *vsk,
	माप_प्रकार target,
	काष्ठा vsock_transport_recv_notअगरy_data *data)
अणु
	वापस vmci_trans(vsk)->notअगरy_ops->recv_pre_block(
			&vsk->sk, target,
			(काष्ठा vmci_transport_recv_notअगरy_data *)data);
पूर्ण

अटल पूर्णांक vmci_transport_notअगरy_recv_pre_dequeue(
	काष्ठा vsock_sock *vsk,
	माप_प्रकार target,
	काष्ठा vsock_transport_recv_notअगरy_data *data)
अणु
	वापस vmci_trans(vsk)->notअगरy_ops->recv_pre_dequeue(
			&vsk->sk, target,
			(काष्ठा vmci_transport_recv_notअगरy_data *)data);
पूर्ण

अटल पूर्णांक vmci_transport_notअगरy_recv_post_dequeue(
	काष्ठा vsock_sock *vsk,
	माप_प्रकार target,
	sमाप_प्रकार copied,
	bool data_पढ़ो,
	काष्ठा vsock_transport_recv_notअगरy_data *data)
अणु
	वापस vmci_trans(vsk)->notअगरy_ops->recv_post_dequeue(
			&vsk->sk, target, copied, data_पढ़ो,
			(काष्ठा vmci_transport_recv_notअगरy_data *)data);
पूर्ण

अटल पूर्णांक vmci_transport_notअगरy_send_init(
	काष्ठा vsock_sock *vsk,
	काष्ठा vsock_transport_send_notअगरy_data *data)
अणु
	वापस vmci_trans(vsk)->notअगरy_ops->send_init(
			&vsk->sk,
			(काष्ठा vmci_transport_send_notअगरy_data *)data);
पूर्ण

अटल पूर्णांक vmci_transport_notअगरy_send_pre_block(
	काष्ठा vsock_sock *vsk,
	काष्ठा vsock_transport_send_notअगरy_data *data)
अणु
	वापस vmci_trans(vsk)->notअगरy_ops->send_pre_block(
			&vsk->sk,
			(काष्ठा vmci_transport_send_notअगरy_data *)data);
पूर्ण

अटल पूर्णांक vmci_transport_notअगरy_send_pre_enqueue(
	काष्ठा vsock_sock *vsk,
	काष्ठा vsock_transport_send_notअगरy_data *data)
अणु
	वापस vmci_trans(vsk)->notअगरy_ops->send_pre_enqueue(
			&vsk->sk,
			(काष्ठा vmci_transport_send_notअगरy_data *)data);
पूर्ण

अटल पूर्णांक vmci_transport_notअगरy_send_post_enqueue(
	काष्ठा vsock_sock *vsk,
	sमाप_प्रकार written,
	काष्ठा vsock_transport_send_notअगरy_data *data)
अणु
	वापस vmci_trans(vsk)->notअगरy_ops->send_post_enqueue(
			&vsk->sk, written,
			(काष्ठा vmci_transport_send_notअगरy_data *)data);
पूर्ण

अटल bool vmci_transport_old_proto_override(bool *old_pkt_proto)
अणु
	अगर (PROTOCOL_OVERRIDE != -1) अणु
		अगर (PROTOCOL_OVERRIDE == 0)
			*old_pkt_proto = true;
		अन्यथा
			*old_pkt_proto = false;

		pr_info("Proto override in use\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool vmci_transport_proto_to_notअगरy_काष्ठा(काष्ठा sock *sk,
						  u16 *proto,
						  bool old_pkt_proto)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	अगर (old_pkt_proto) अणु
		अगर (*proto != VSOCK_PROTO_INVALID) अणु
			pr_err("Can't set both an old and new protocol\n");
			वापस false;
		पूर्ण
		vmci_trans(vsk)->notअगरy_ops = &vmci_transport_notअगरy_pkt_ops;
		जाओ निकास;
	पूर्ण

	चयन (*proto) अणु
	हाल VSOCK_PROTO_PKT_ON_NOTIFY:
		vmci_trans(vsk)->notअगरy_ops =
			&vmci_transport_notअगरy_pkt_q_state_ops;
		अवरोध;
	शेष:
		pr_err("Unknown notify protocol version\n");
		वापस false;
	पूर्ण

निकास:
	vmci_trans(vsk)->notअगरy_ops->socket_init(sk);
	वापस true;
पूर्ण

अटल u16 vmci_transport_new_proto_supported_versions(व्योम)
अणु
	अगर (PROTOCOL_OVERRIDE != -1)
		वापस PROTOCOL_OVERRIDE;

	वापस VSOCK_PROTO_ALL_SUPPORTED;
पूर्ण

अटल u32 vmci_transport_get_local_cid(व्योम)
अणु
	वापस vmci_get_context_id();
पूर्ण

अटल काष्ठा vsock_transport vmci_transport = अणु
	.module = THIS_MODULE,
	.init = vmci_transport_socket_init,
	.deकाष्ठा = vmci_transport_deकाष्ठा,
	.release = vmci_transport_release,
	.connect = vmci_transport_connect,
	.dgram_bind = vmci_transport_dgram_bind,
	.dgram_dequeue = vmci_transport_dgram_dequeue,
	.dgram_enqueue = vmci_transport_dgram_enqueue,
	.dgram_allow = vmci_transport_dgram_allow,
	.stream_dequeue = vmci_transport_stream_dequeue,
	.stream_enqueue = vmci_transport_stream_enqueue,
	.stream_has_data = vmci_transport_stream_has_data,
	.stream_has_space = vmci_transport_stream_has_space,
	.stream_rcvhiwat = vmci_transport_stream_rcvhiwat,
	.stream_is_active = vmci_transport_stream_is_active,
	.stream_allow = vmci_transport_stream_allow,
	.notअगरy_poll_in = vmci_transport_notअगरy_poll_in,
	.notअगरy_poll_out = vmci_transport_notअगरy_poll_out,
	.notअगरy_recv_init = vmci_transport_notअगरy_recv_init,
	.notअगरy_recv_pre_block = vmci_transport_notअगरy_recv_pre_block,
	.notअगरy_recv_pre_dequeue = vmci_transport_notअगरy_recv_pre_dequeue,
	.notअगरy_recv_post_dequeue = vmci_transport_notअगरy_recv_post_dequeue,
	.notअगरy_send_init = vmci_transport_notअगरy_send_init,
	.notअगरy_send_pre_block = vmci_transport_notअगरy_send_pre_block,
	.notअगरy_send_pre_enqueue = vmci_transport_notअगरy_send_pre_enqueue,
	.notअगरy_send_post_enqueue = vmci_transport_notअगरy_send_post_enqueue,
	.shutकरोwn = vmci_transport_shutकरोwn,
	.get_local_cid = vmci_transport_get_local_cid,
पूर्ण;

अटल bool vmci_check_transport(काष्ठा vsock_sock *vsk)
अणु
	वापस vsk->transport == &vmci_transport;
पूर्ण

अटल व्योम vmci_vsock_transport_cb(bool is_host)
अणु
	पूर्णांक features;

	अगर (is_host)
		features = VSOCK_TRANSPORT_F_H2G;
	अन्यथा
		features = VSOCK_TRANSPORT_F_G2H;

	vsock_core_रेजिस्टर(&vmci_transport, features);
पूर्ण

अटल पूर्णांक __init vmci_transport_init(व्योम)
अणु
	पूर्णांक err;

	/* Create the datagram handle that we will use to send and receive all
	 * VSocket control messages क्रम this context.
	 */
	err = vmci_transport_datagram_create_hnd(VMCI_TRANSPORT_PACKET_RID,
						 VMCI_FLAG_ANYCID_DG_HND,
						 vmci_transport_recv_stream_cb,
						 शून्य,
						 &vmci_transport_stream_handle);
	अगर (err < VMCI_SUCCESS) अणु
		pr_err("Unable to create datagram handle. (%d)\n", err);
		वापस vmci_transport_error_to_vsock_error(err);
	पूर्ण
	err = vmci_event_subscribe(VMCI_EVENT_QP_RESUMED,
				   vmci_transport_qp_resumed_cb,
				   शून्य, &vmci_transport_qp_resumed_sub_id);
	अगर (err < VMCI_SUCCESS) अणु
		pr_err("Unable to subscribe to resumed event. (%d)\n", err);
		err = vmci_transport_error_to_vsock_error(err);
		vmci_transport_qp_resumed_sub_id = VMCI_INVALID_ID;
		जाओ err_destroy_stream_handle;
	पूर्ण

	/* Register only with dgram feature, other features (H2G, G2H) will be
	 * रेजिस्टरed when the first host or guest becomes active.
	 */
	err = vsock_core_रेजिस्टर(&vmci_transport, VSOCK_TRANSPORT_F_DGRAM);
	अगर (err < 0)
		जाओ err_unsubscribe;

	err = vmci_रेजिस्टर_vsock_callback(vmci_vsock_transport_cb);
	अगर (err < 0)
		जाओ err_unरेजिस्टर;

	वापस 0;

err_unरेजिस्टर:
	vsock_core_unरेजिस्टर(&vmci_transport);
err_unsubscribe:
	vmci_event_unsubscribe(vmci_transport_qp_resumed_sub_id);
err_destroy_stream_handle:
	vmci_datagram_destroy_handle(vmci_transport_stream_handle);
	वापस err;
पूर्ण
module_init(vmci_transport_init);

अटल व्योम __निकास vmci_transport_निकास(व्योम)
अणु
	cancel_work_sync(&vmci_transport_cleanup_work);
	vmci_transport_मुक्त_resources(&vmci_transport_cleanup_list);

	अगर (!vmci_handle_is_invalid(vmci_transport_stream_handle)) अणु
		अगर (vmci_datagram_destroy_handle(
			vmci_transport_stream_handle) != VMCI_SUCCESS)
			pr_err("Couldn't destroy datagram handle\n");
		vmci_transport_stream_handle = VMCI_INVALID_HANDLE;
	पूर्ण

	अगर (vmci_transport_qp_resumed_sub_id != VMCI_INVALID_ID) अणु
		vmci_event_unsubscribe(vmci_transport_qp_resumed_sub_id);
		vmci_transport_qp_resumed_sub_id = VMCI_INVALID_ID;
	पूर्ण

	vmci_रेजिस्टर_vsock_callback(शून्य);
	vsock_core_unरेजिस्टर(&vmci_transport);
पूर्ण
module_निकास(vmci_transport_निकास);

MODULE_AUTHOR("VMware, Inc.");
MODULE_DESCRIPTION("VMCI transport for Virtual Sockets");
MODULE_VERSION("1.0.5.0-k");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("vmware_vsock");
MODULE_ALIAS_NETPROTO(PF_VSOCK);
