<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware vSockets Driver
 *
 * Copyright (C) 2007-2013 VMware, Inc. All rights reserved.
 */

/* Implementation notes:
 *
 * - There are two kinds of sockets: those created by user action (such as
 * calling socket(2)) and those created by incoming connection request packets.
 *
 * - There are two "global" tables, one क्रम bound sockets (sockets that have
 * specअगरied an address that they are responsible क्रम) and one क्रम connected
 * sockets (sockets that have established a connection with another socket).
 * These tables are "global" in that all sockets on the प्रणाली are placed
 * within them. - Note, though, that the bound table contains an extra entry
 * क्रम a list of unbound sockets and SOCK_DGRAM sockets will always reमुख्य in
 * that list. The bound table is used solely क्रम lookup of sockets when packets
 * are received and that's not necessary क्रम SOCK_DGRAM sockets since we create
 * a datagram handle क्रम each and need not perक्रमm a lookup.  Keeping SOCK_DGRAM
 * sockets out of the bound hash buckets will reduce the chance of collisions
 * when looking क्रम SOCK_STREAM sockets and prevents us from having to check the
 * socket type in the hash table lookups.
 *
 * - Sockets created by user action will either be "client" sockets that
 * initiate a connection or "server" sockets that listen क्रम connections; we करो
 * not support simultaneous connects (two "client" sockets connecting).
 *
 * - "Server" sockets are referred to as listener sockets throughout this
 * implementation because they are in the TCP_LISTEN state.  When a
 * connection request is received (the second kind of socket mentioned above),
 * we create a new socket and refer to it as a pending socket.  These pending
 * sockets are placed on the pending connection list of the listener socket.
 * When future packets are received क्रम the address the listener socket is
 * bound to, we check अगर the source of the packet is from one that has an
 * existing pending connection.  If it करोes, we process the packet क्रम the
 * pending socket.  When that socket reaches the connected state, it is हटाओd
 * from the listener socket's pending list and enqueued in the listener
 * socket's accept queue.  Callers of accept(2) will accept connected sockets
 * from the listener socket's accept queue.  If the socket cannot be accepted
 * क्रम some reason then it is marked rejected.  Once the connection is
 * accepted, it is owned by the user process and the responsibility क्रम cleanup
 * falls with that user process.
 *
 * - It is possible that these pending sockets will never reach the connected
 * state; in fact, we may never receive another packet after the connection
 * request.  Because of this, we must schedule a cleanup function to run in the
 * future, after some amount of समय passes where a connection should have been
 * established.  This function ensures that the socket is off all lists so it
 * cannot be retrieved, then drops all references to the socket so it is cleaned
 * up (sock_put() -> sk_मुक्त() -> our sk_deकाष्ठा implementation).  Note this
 * function will also cleanup rejected sockets, those that reach the connected
 * state but leave it beक्रमe they have been accepted.
 *
 * - Lock ordering क्रम pending or accept queue sockets is:
 *
 *     lock_sock(listener);
 *     lock_sock_nested(pending, SINGLE_DEPTH_NESTING);
 *
 * Using explicit nested locking keeps lockdep happy since normally only one
 * lock of a given class may be taken at a समय.
 *
 * - Sockets created by user action will be cleaned up when the user process
 * calls बंद(2), causing our release implementation to be called. Our release
 * implementation will perक्रमm some cleanup then drop the last reference so our
 * sk_deकाष्ठा implementation is invoked.  Our sk_deकाष्ठा implementation will
 * perक्रमm additional cleanup that's common क्रम both types of sockets.
 *
 * - A socket's reference count is what ensures that the structure won't be
 * मुक्तd.  Each entry in a list (such as the "global" bound and connected tables
 * and the listener socket's pending list and connected queue) ensures a
 * reference.  When we defer work until process context and pass a socket as our
 * argument, we must ensure the reference count is increased to ensure the
 * socket isn't मुक्तd beक्रमe the function is run; the deferred function will
 * then drop the reference.
 *
 * - sk->sk_state uses the TCP state स्थिरants because they are widely used by
 * other address families and exposed to userspace tools like ss(8):
 *
 *   TCP_CLOSE - unconnected
 *   TCP_SYN_SENT - connecting
 *   TCP_ESTABLISHED - connected
 *   TCP_CLOSING - disconnecting
 *   TCP_LISTEN - listening
 */

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cred.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kmod.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/net.h>
#समावेश <linux/poll.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/smp.h>
#समावेश <linux/socket.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <net/sock.h>
#समावेश <net/af_vsock.h>

अटल पूर्णांक __vsock_bind(काष्ठा sock *sk, काष्ठा sockaddr_vm *addr);
अटल व्योम vsock_sk_deकाष्ठा(काष्ठा sock *sk);
अटल पूर्णांक vsock_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);

/* Protocol family. */
अटल काष्ठा proto vsock_proto = अणु
	.name = "AF_VSOCK",
	.owner = THIS_MODULE,
	.obj_size = माप(काष्ठा vsock_sock),
पूर्ण;

/* The शेष peer समयout indicates how दीर्घ we will रुको क्रम a peer response
 * to a control message.
 */
#घोषणा VSOCK_DEFAULT_CONNECT_TIMEOUT (2 * HZ)

#घोषणा VSOCK_DEFAULT_BUFFER_SIZE     (1024 * 256)
#घोषणा VSOCK_DEFAULT_BUFFER_MAX_SIZE (1024 * 256)
#घोषणा VSOCK_DEFAULT_BUFFER_MIN_SIZE 128

/* Transport used क्रम host->guest communication */
अटल स्थिर काष्ठा vsock_transport *transport_h2g;
/* Transport used क्रम guest->host communication */
अटल स्थिर काष्ठा vsock_transport *transport_g2h;
/* Transport used क्रम DGRAM communication */
अटल स्थिर काष्ठा vsock_transport *transport_dgram;
/* Transport used क्रम local communication */
अटल स्थिर काष्ठा vsock_transport *transport_local;
अटल DEFINE_MUTEX(vsock_रेजिस्टर_mutex);

/**** UTILS ****/

/* Each bound VSocket is stored in the bind hash table and each connected
 * VSocket is stored in the connected hash table.
 *
 * Unbound sockets are all put on the same list attached to the end of the hash
 * table (vsock_unbound_sockets).  Bound sockets are added to the hash table in
 * the bucket that their local address hashes to (vsock_bound_sockets(addr)
 * represents the list that addr hashes to).
 *
 * Specअगरically, we initialize the vsock_bind_table array to a size of
 * VSOCK_HASH_SIZE + 1 so that vsock_bind_table[0] through
 * vsock_bind_table[VSOCK_HASH_SIZE - 1] are क्रम bound sockets and
 * vsock_bind_table[VSOCK_HASH_SIZE] is क्रम unbound sockets.  The hash function
 * mods with VSOCK_HASH_SIZE to ensure this.
 */
#घोषणा MAX_PORT_RETRIES        24

#घोषणा VSOCK_HASH(addr)        ((addr)->svm_port % VSOCK_HASH_SIZE)
#घोषणा vsock_bound_sockets(addr) (&vsock_bind_table[VSOCK_HASH(addr)])
#घोषणा vsock_unbound_sockets     (&vsock_bind_table[VSOCK_HASH_SIZE])

/* XXX This can probably be implemented in a better way. */
#घोषणा VSOCK_CONN_HASH(src, dst)				\
	(((src)->svm_cid ^ (dst)->svm_port) % VSOCK_HASH_SIZE)
#घोषणा vsock_connected_sockets(src, dst)		\
	(&vsock_connected_table[VSOCK_CONN_HASH(src, dst)])
#घोषणा vsock_connected_sockets_vsk(vsk)				\
	vsock_connected_sockets(&(vsk)->remote_addr, &(vsk)->local_addr)

काष्ठा list_head vsock_bind_table[VSOCK_HASH_SIZE + 1];
EXPORT_SYMBOL_GPL(vsock_bind_table);
काष्ठा list_head vsock_connected_table[VSOCK_HASH_SIZE];
EXPORT_SYMBOL_GPL(vsock_connected_table);
DEFINE_SPINLOCK(vsock_table_lock);
EXPORT_SYMBOL_GPL(vsock_table_lock);

/* Autobind this socket to the local address अगर necessary. */
अटल पूर्णांक vsock_स्वतः_bind(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा sock *sk = sk_vsock(vsk);
	काष्ठा sockaddr_vm local_addr;

	अगर (vsock_addr_bound(&vsk->local_addr))
		वापस 0;
	vsock_addr_init(&local_addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);
	वापस __vsock_bind(sk, &local_addr);
पूर्ण

अटल व्योम vsock_init_tables(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vsock_bind_table); i++)
		INIT_LIST_HEAD(&vsock_bind_table[i]);

	क्रम (i = 0; i < ARRAY_SIZE(vsock_connected_table); i++)
		INIT_LIST_HEAD(&vsock_connected_table[i]);
पूर्ण

अटल व्योम __vsock_insert_bound(काष्ठा list_head *list,
				 काष्ठा vsock_sock *vsk)
अणु
	sock_hold(&vsk->sk);
	list_add(&vsk->bound_table, list);
पूर्ण

अटल व्योम __vsock_insert_connected(काष्ठा list_head *list,
				     काष्ठा vsock_sock *vsk)
अणु
	sock_hold(&vsk->sk);
	list_add(&vsk->connected_table, list);
पूर्ण

अटल व्योम __vsock_हटाओ_bound(काष्ठा vsock_sock *vsk)
अणु
	list_del_init(&vsk->bound_table);
	sock_put(&vsk->sk);
पूर्ण

अटल व्योम __vsock_हटाओ_connected(काष्ठा vsock_sock *vsk)
अणु
	list_del_init(&vsk->connected_table);
	sock_put(&vsk->sk);
पूर्ण

अटल काष्ठा sock *__vsock_find_bound_socket(काष्ठा sockaddr_vm *addr)
अणु
	काष्ठा vsock_sock *vsk;

	list_क्रम_each_entry(vsk, vsock_bound_sockets(addr), bound_table) अणु
		अगर (vsock_addr_equals_addr(addr, &vsk->local_addr))
			वापस sk_vsock(vsk);

		अगर (addr->svm_port == vsk->local_addr.svm_port &&
		    (vsk->local_addr.svm_cid == VMADDR_CID_ANY ||
		     addr->svm_cid == VMADDR_CID_ANY))
			वापस sk_vsock(vsk);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा sock *__vsock_find_connected_socket(काष्ठा sockaddr_vm *src,
						  काष्ठा sockaddr_vm *dst)
अणु
	काष्ठा vsock_sock *vsk;

	list_क्रम_each_entry(vsk, vsock_connected_sockets(src, dst),
			    connected_table) अणु
		अगर (vsock_addr_equals_addr(src, &vsk->remote_addr) &&
		    dst->svm_port == vsk->local_addr.svm_port) अणु
			वापस sk_vsock(vsk);
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम vsock_insert_unbound(काष्ठा vsock_sock *vsk)
अणु
	spin_lock_bh(&vsock_table_lock);
	__vsock_insert_bound(vsock_unbound_sockets, vsk);
	spin_unlock_bh(&vsock_table_lock);
पूर्ण

व्योम vsock_insert_connected(काष्ठा vsock_sock *vsk)
अणु
	काष्ठा list_head *list = vsock_connected_sockets(
		&vsk->remote_addr, &vsk->local_addr);

	spin_lock_bh(&vsock_table_lock);
	__vsock_insert_connected(list, vsk);
	spin_unlock_bh(&vsock_table_lock);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_insert_connected);

व्योम vsock_हटाओ_bound(काष्ठा vsock_sock *vsk)
अणु
	spin_lock_bh(&vsock_table_lock);
	अगर (__vsock_in_bound_table(vsk))
		__vsock_हटाओ_bound(vsk);
	spin_unlock_bh(&vsock_table_lock);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_हटाओ_bound);

व्योम vsock_हटाओ_connected(काष्ठा vsock_sock *vsk)
अणु
	spin_lock_bh(&vsock_table_lock);
	अगर (__vsock_in_connected_table(vsk))
		__vsock_हटाओ_connected(vsk);
	spin_unlock_bh(&vsock_table_lock);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_हटाओ_connected);

काष्ठा sock *vsock_find_bound_socket(काष्ठा sockaddr_vm *addr)
अणु
	काष्ठा sock *sk;

	spin_lock_bh(&vsock_table_lock);
	sk = __vsock_find_bound_socket(addr);
	अगर (sk)
		sock_hold(sk);

	spin_unlock_bh(&vsock_table_lock);

	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_find_bound_socket);

काष्ठा sock *vsock_find_connected_socket(काष्ठा sockaddr_vm *src,
					 काष्ठा sockaddr_vm *dst)
अणु
	काष्ठा sock *sk;

	spin_lock_bh(&vsock_table_lock);
	sk = __vsock_find_connected_socket(src, dst);
	अगर (sk)
		sock_hold(sk);

	spin_unlock_bh(&vsock_table_lock);

	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_find_connected_socket);

व्योम vsock_हटाओ_sock(काष्ठा vsock_sock *vsk)
अणु
	vsock_हटाओ_bound(vsk);
	vsock_हटाओ_connected(vsk);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_हटाओ_sock);

व्योम vsock_क्रम_each_connected_socket(व्योम (*fn)(काष्ठा sock *sk))
अणु
	पूर्णांक i;

	spin_lock_bh(&vsock_table_lock);

	क्रम (i = 0; i < ARRAY_SIZE(vsock_connected_table); i++) अणु
		काष्ठा vsock_sock *vsk;
		list_क्रम_each_entry(vsk, &vsock_connected_table[i],
				    connected_table)
			fn(sk_vsock(vsk));
	पूर्ण

	spin_unlock_bh(&vsock_table_lock);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_क्रम_each_connected_socket);

व्योम vsock_add_pending(काष्ठा sock *listener, काष्ठा sock *pending)
अणु
	काष्ठा vsock_sock *vlistener;
	काष्ठा vsock_sock *vpending;

	vlistener = vsock_sk(listener);
	vpending = vsock_sk(pending);

	sock_hold(pending);
	sock_hold(listener);
	list_add_tail(&vpending->pending_links, &vlistener->pending_links);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_add_pending);

व्योम vsock_हटाओ_pending(काष्ठा sock *listener, काष्ठा sock *pending)
अणु
	काष्ठा vsock_sock *vpending = vsock_sk(pending);

	list_del_init(&vpending->pending_links);
	sock_put(listener);
	sock_put(pending);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_हटाओ_pending);

व्योम vsock_enqueue_accept(काष्ठा sock *listener, काष्ठा sock *connected)
अणु
	काष्ठा vsock_sock *vlistener;
	काष्ठा vsock_sock *vconnected;

	vlistener = vsock_sk(listener);
	vconnected = vsock_sk(connected);

	sock_hold(connected);
	sock_hold(listener);
	list_add_tail(&vconnected->accept_queue, &vlistener->accept_queue);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_enqueue_accept);

अटल bool vsock_use_local_transport(अचिन्हित पूर्णांक remote_cid)
अणु
	अगर (!transport_local)
		वापस false;

	अगर (remote_cid == VMADDR_CID_LOCAL)
		वापस true;

	अगर (transport_g2h) अणु
		वापस remote_cid == transport_g2h->get_local_cid();
	पूर्ण अन्यथा अणु
		वापस remote_cid == VMADDR_CID_HOST;
	पूर्ण
पूर्ण

अटल व्योम vsock_deassign_transport(काष्ठा vsock_sock *vsk)
अणु
	अगर (!vsk->transport)
		वापस;

	vsk->transport->deकाष्ठा(vsk);
	module_put(vsk->transport->module);
	vsk->transport = शून्य;
पूर्ण

/* Assign a transport to a socket and call the .init transport callback.
 *
 * Note: क्रम stream socket this must be called when vsk->remote_addr is set
 * (e.g. during the connect() or when a connection request on a listener
 * socket is received).
 * The vsk->remote_addr is used to decide which transport to use:
 *  - remote CID == VMADDR_CID_LOCAL or g2h->local_cid or VMADDR_CID_HOST अगर
 *    g2h is not loaded, will use local transport;
 *  - remote CID <= VMADDR_CID_HOST or h2g is not loaded or remote flags field
 *    includes VMADDR_FLAG_TO_HOST flag value, will use guest->host transport;
 *  - remote CID > VMADDR_CID_HOST will use host->guest transport;
 */
पूर्णांक vsock_assign_transport(काष्ठा vsock_sock *vsk, काष्ठा vsock_sock *psk)
अणु
	स्थिर काष्ठा vsock_transport *new_transport;
	काष्ठा sock *sk = sk_vsock(vsk);
	अचिन्हित पूर्णांक remote_cid = vsk->remote_addr.svm_cid;
	__u8 remote_flags;
	पूर्णांक ret;

	/* If the packet is coming with the source and destination CIDs higher
	 * than VMADDR_CID_HOST, then a vsock channel where all the packets are
	 * क्रमwarded to the host should be established. Then the host will
	 * need to क्रमward the packets to the guest.
	 *
	 * The flag is set on the (listen) receive path (psk is not शून्य). On
	 * the connect path the flag can be set by the user space application.
	 */
	अगर (psk && vsk->local_addr.svm_cid > VMADDR_CID_HOST &&
	    vsk->remote_addr.svm_cid > VMADDR_CID_HOST)
		vsk->remote_addr.svm_flags |= VMADDR_FLAG_TO_HOST;

	remote_flags = vsk->remote_addr.svm_flags;

	चयन (sk->sk_type) अणु
	हाल SOCK_DGRAM:
		new_transport = transport_dgram;
		अवरोध;
	हाल SOCK_STREAM:
		अगर (vsock_use_local_transport(remote_cid))
			new_transport = transport_local;
		अन्यथा अगर (remote_cid <= VMADDR_CID_HOST || !transport_h2g ||
			 (remote_flags & VMADDR_FLAG_TO_HOST))
			new_transport = transport_g2h;
		अन्यथा
			new_transport = transport_h2g;
		अवरोध;
	शेष:
		वापस -ESOCKTNOSUPPORT;
	पूर्ण

	अगर (vsk->transport) अणु
		अगर (vsk->transport == new_transport)
			वापस 0;

		/* transport->release() must be called with sock lock acquired.
		 * This path can only be taken during vsock_stream_connect(),
		 * where we have alपढ़ोy held the sock lock.
		 * In the other हालs, this function is called on a new socket
		 * which is not asचिन्हित to any transport.
		 */
		vsk->transport->release(vsk);
		vsock_deassign_transport(vsk);
	पूर्ण

	/* We increase the module refcnt to prevent the transport unloading
	 * जबतक there are खोलो sockets asचिन्हित to it.
	 */
	अगर (!new_transport || !try_module_get(new_transport->module))
		वापस -ENODEV;

	ret = new_transport->init(vsk, psk);
	अगर (ret) अणु
		module_put(new_transport->module);
		वापस ret;
	पूर्ण

	vsk->transport = new_transport;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_assign_transport);

bool vsock_find_cid(अचिन्हित पूर्णांक cid)
अणु
	अगर (transport_g2h && cid == transport_g2h->get_local_cid())
		वापस true;

	अगर (transport_h2g && cid == VMADDR_CID_HOST)
		वापस true;

	अगर (transport_local && cid == VMADDR_CID_LOCAL)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_find_cid);

अटल काष्ठा sock *vsock_dequeue_accept(काष्ठा sock *listener)
अणु
	काष्ठा vsock_sock *vlistener;
	काष्ठा vsock_sock *vconnected;

	vlistener = vsock_sk(listener);

	अगर (list_empty(&vlistener->accept_queue))
		वापस शून्य;

	vconnected = list_entry(vlistener->accept_queue.next,
				काष्ठा vsock_sock, accept_queue);

	list_del_init(&vconnected->accept_queue);
	sock_put(listener);
	/* The caller will need a reference on the connected socket so we let
	 * it call sock_put().
	 */

	वापस sk_vsock(vconnected);
पूर्ण

अटल bool vsock_is_accept_queue_empty(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);
	वापस list_empty(&vsk->accept_queue);
पूर्ण

अटल bool vsock_is_pending(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);
	वापस !list_empty(&vsk->pending_links);
पूर्ण

अटल पूर्णांक vsock_send_shutकरोwn(काष्ठा sock *sk, पूर्णांक mode)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	अगर (!vsk->transport)
		वापस -ENODEV;

	वापस vsk->transport->shutकरोwn(vsk, mode);
पूर्ण

अटल व्योम vsock_pending_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sock *sk;
	काष्ठा sock *listener;
	काष्ठा vsock_sock *vsk;
	bool cleanup;

	vsk = container_of(work, काष्ठा vsock_sock, pending_work.work);
	sk = sk_vsock(vsk);
	listener = vsk->listener;
	cleanup = true;

	lock_sock(listener);
	lock_sock_nested(sk, SINGLE_DEPTH_NESTING);

	अगर (vsock_is_pending(sk)) अणु
		vsock_हटाओ_pending(listener, sk);

		sk_acceptq_हटाओd(listener);
	पूर्ण अन्यथा अगर (!vsk->rejected) अणु
		/* We are not on the pending list and accept() did not reject
		 * us, so we must have been accepted by our user process.  We
		 * just need to drop our references to the sockets and be on
		 * our way.
		 */
		cleanup = false;
		जाओ out;
	पूर्ण

	/* We need to हटाओ ourself from the global connected sockets list so
	 * incoming packets can't find this socket, and to reduce the reference
	 * count.
	 */
	vsock_हटाओ_connected(vsk);

	sk->sk_state = TCP_CLOSE;

out:
	release_sock(sk);
	release_sock(listener);
	अगर (cleanup)
		sock_put(sk);

	sock_put(sk);
	sock_put(listener);
पूर्ण

/**** SOCKET OPERATIONS ****/

अटल पूर्णांक __vsock_bind_stream(काष्ठा vsock_sock *vsk,
			       काष्ठा sockaddr_vm *addr)
अणु
	अटल u32 port;
	काष्ठा sockaddr_vm new_addr;

	अगर (!port)
		port = LAST_RESERVED_PORT + 1 +
			pअक्रमom_u32_max(U32_MAX - LAST_RESERVED_PORT);

	vsock_addr_init(&new_addr, addr->svm_cid, addr->svm_port);

	अगर (addr->svm_port == VMADDR_PORT_ANY) अणु
		bool found = false;
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < MAX_PORT_RETRIES; i++) अणु
			अगर (port <= LAST_RESERVED_PORT)
				port = LAST_RESERVED_PORT + 1;

			new_addr.svm_port = port++;

			अगर (!__vsock_find_bound_socket(&new_addr)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found)
			वापस -EADDRNOTAVAIL;
	पूर्ण अन्यथा अणु
		/* If port is in reserved range, ensure caller
		 * has necessary privileges.
		 */
		अगर (addr->svm_port <= LAST_RESERVED_PORT &&
		    !capable(CAP_NET_BIND_SERVICE)) अणु
			वापस -EACCES;
		पूर्ण

		अगर (__vsock_find_bound_socket(&new_addr))
			वापस -EADDRINUSE;
	पूर्ण

	vsock_addr_init(&vsk->local_addr, new_addr.svm_cid, new_addr.svm_port);

	/* Remove stream sockets from the unbound list and add them to the hash
	 * table क्रम easy lookup by its address.  The unbound list is simply an
	 * extra entry at the end of the hash table, a trick used by AF_UNIX.
	 */
	__vsock_हटाओ_bound(vsk);
	__vsock_insert_bound(vsock_bound_sockets(&vsk->local_addr), vsk);

	वापस 0;
पूर्ण

अटल पूर्णांक __vsock_bind_dgram(काष्ठा vsock_sock *vsk,
			      काष्ठा sockaddr_vm *addr)
अणु
	वापस vsk->transport->dgram_bind(vsk, addr);
पूर्ण

अटल पूर्णांक __vsock_bind(काष्ठा sock *sk, काष्ठा sockaddr_vm *addr)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);
	पूर्णांक retval;

	/* First ensure this socket isn't alपढ़ोy bound. */
	अगर (vsock_addr_bound(&vsk->local_addr))
		वापस -EINVAL;

	/* Now bind to the provided address or select appropriate values अगर
	 * none are provided (VMADDR_CID_ANY and VMADDR_PORT_ANY).  Note that
	 * like AF_INET prevents binding to a non-local IP address (in most
	 * हालs), we only allow binding to a local CID.
	 */
	अगर (addr->svm_cid != VMADDR_CID_ANY && !vsock_find_cid(addr->svm_cid))
		वापस -EADDRNOTAVAIL;

	चयन (sk->sk_socket->type) अणु
	हाल SOCK_STREAM:
		spin_lock_bh(&vsock_table_lock);
		retval = __vsock_bind_stream(vsk, addr);
		spin_unlock_bh(&vsock_table_lock);
		अवरोध;

	हाल SOCK_DGRAM:
		retval = __vsock_bind_dgram(vsk, addr);
		अवरोध;

	शेष:
		retval = -EINVAL;
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम vsock_connect_समयout(काष्ठा work_काष्ठा *work);

अटल काष्ठा sock *__vsock_create(काष्ठा net *net,
				   काष्ठा socket *sock,
				   काष्ठा sock *parent,
				   gfp_t priority,
				   अचिन्हित लघु type,
				   पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा vsock_sock *psk;
	काष्ठा vsock_sock *vsk;

	sk = sk_alloc(net, AF_VSOCK, priority, &vsock_proto, kern);
	अगर (!sk)
		वापस शून्य;

	sock_init_data(sock, sk);

	/* sk->sk_type is normally set in sock_init_data, but only अगर sock is
	 * non-शून्य. We make sure that our sockets always have a type by
	 * setting it here अगर needed.
	 */
	अगर (!sock)
		sk->sk_type = type;

	vsk = vsock_sk(sk);
	vsock_addr_init(&vsk->local_addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);
	vsock_addr_init(&vsk->remote_addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);

	sk->sk_deकाष्ठा = vsock_sk_deकाष्ठा;
	sk->sk_backlog_rcv = vsock_queue_rcv_skb;
	sock_reset_flag(sk, SOCK_DONE);

	INIT_LIST_HEAD(&vsk->bound_table);
	INIT_LIST_HEAD(&vsk->connected_table);
	vsk->listener = शून्य;
	INIT_LIST_HEAD(&vsk->pending_links);
	INIT_LIST_HEAD(&vsk->accept_queue);
	vsk->rejected = false;
	vsk->sent_request = false;
	vsk->ignore_connecting_rst = false;
	vsk->peer_shutकरोwn = 0;
	INIT_DELAYED_WORK(&vsk->connect_work, vsock_connect_समयout);
	INIT_DELAYED_WORK(&vsk->pending_work, vsock_pending_work);

	psk = parent ? vsock_sk(parent) : शून्य;
	अगर (parent) अणु
		vsk->trusted = psk->trusted;
		vsk->owner = get_cred(psk->owner);
		vsk->connect_समयout = psk->connect_समयout;
		vsk->buffer_size = psk->buffer_size;
		vsk->buffer_min_size = psk->buffer_min_size;
		vsk->buffer_max_size = psk->buffer_max_size;
		security_sk_clone(parent, sk);
	पूर्ण अन्यथा अणु
		vsk->trusted = ns_capable_noaudit(&init_user_ns, CAP_NET_ADMIN);
		vsk->owner = get_current_cred();
		vsk->connect_समयout = VSOCK_DEFAULT_CONNECT_TIMEOUT;
		vsk->buffer_size = VSOCK_DEFAULT_BUFFER_SIZE;
		vsk->buffer_min_size = VSOCK_DEFAULT_BUFFER_MIN_SIZE;
		vsk->buffer_max_size = VSOCK_DEFAULT_BUFFER_MAX_SIZE;
	पूर्ण

	वापस sk;
पूर्ण

अटल व्योम __vsock_release(काष्ठा sock *sk, पूर्णांक level)
अणु
	अगर (sk) अणु
		काष्ठा sock *pending;
		काष्ठा vsock_sock *vsk;

		vsk = vsock_sk(sk);
		pending = शून्य;	/* Compiler warning. */

		/* When "level" is SINGLE_DEPTH_NESTING, use the nested
		 * version to aव्योम the warning "possible recursive locking
		 * detected". When "level" is 0, lock_sock_nested(sk, level)
		 * is the same as lock_sock(sk).
		 */
		lock_sock_nested(sk, level);

		अगर (vsk->transport)
			vsk->transport->release(vsk);
		अन्यथा अगर (sk->sk_type == SOCK_STREAM)
			vsock_हटाओ_sock(vsk);

		sock_orphan(sk);
		sk->sk_shutकरोwn = SHUTDOWN_MASK;

		skb_queue_purge(&sk->sk_receive_queue);

		/* Clean up any sockets that never were accepted. */
		जबतक ((pending = vsock_dequeue_accept(sk)) != शून्य) अणु
			__vsock_release(pending, SINGLE_DEPTH_NESTING);
			sock_put(pending);
		पूर्ण

		release_sock(sk);
		sock_put(sk);
	पूर्ण
पूर्ण

अटल व्योम vsock_sk_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sk);

	vsock_deassign_transport(vsk);

	/* When clearing these addresses, there's no need to set the family and
	 * possibly रेजिस्टर the address family with the kernel.
	 */
	vsock_addr_init(&vsk->local_addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);
	vsock_addr_init(&vsk->remote_addr, VMADDR_CID_ANY, VMADDR_PORT_ANY);

	put_cred(vsk->owner);
पूर्ण

अटल पूर्णांक vsock_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = sock_queue_rcv_skb(sk, skb);
	अगर (err)
		kमुक्त_skb(skb);

	वापस err;
पूर्ण

काष्ठा sock *vsock_create_connected(काष्ठा sock *parent)
अणु
	वापस __vsock_create(sock_net(parent), शून्य, parent, GFP_KERNEL,
			      parent->sk_type, 0);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_create_connected);

s64 vsock_stream_has_data(काष्ठा vsock_sock *vsk)
अणु
	वापस vsk->transport->stream_has_data(vsk);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_stream_has_data);

s64 vsock_stream_has_space(काष्ठा vsock_sock *vsk)
अणु
	वापस vsk->transport->stream_has_space(vsk);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_stream_has_space);

अटल पूर्णांक vsock_release(काष्ठा socket *sock)
अणु
	__vsock_release(sock->sk, 0);
	sock->sk = शून्य;
	sock->state = SS_FREE;

	वापस 0;
पूर्ण

अटल पूर्णांक
vsock_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक addr_len)
अणु
	पूर्णांक err;
	काष्ठा sock *sk;
	काष्ठा sockaddr_vm *vm_addr;

	sk = sock->sk;

	अगर (vsock_addr_cast(addr, addr_len, &vm_addr) != 0)
		वापस -EINVAL;

	lock_sock(sk);
	err = __vsock_bind(sk, vm_addr);
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक vsock_getname(काष्ठा socket *sock,
			 काष्ठा sockaddr *addr, पूर्णांक peer)
अणु
	पूर्णांक err;
	काष्ठा sock *sk;
	काष्ठा vsock_sock *vsk;
	काष्ठा sockaddr_vm *vm_addr;

	sk = sock->sk;
	vsk = vsock_sk(sk);
	err = 0;

	lock_sock(sk);

	अगर (peer) अणु
		अगर (sock->state != SS_CONNECTED) अणु
			err = -ENOTCONN;
			जाओ out;
		पूर्ण
		vm_addr = &vsk->remote_addr;
	पूर्ण अन्यथा अणु
		vm_addr = &vsk->local_addr;
	पूर्ण

	अगर (!vm_addr) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* sys_माला_लोockname() and sys_getpeername() pass us a
	 * MAX_SOCK_ADDR-sized buffer and करोn't set addr_len.  Unक्रमtunately
	 * that macro is defined in socket.c instead of .h, so we hardcode its
	 * value here.
	 */
	BUILD_BUG_ON(माप(*vm_addr) > 128);
	स_नकल(addr, vm_addr, माप(*vm_addr));
	err = माप(*vm_addr);

out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक vsock_shutकरोwn(काष्ठा socket *sock, पूर्णांक mode)
अणु
	पूर्णांक err;
	काष्ठा sock *sk;

	/* User level uses SHUT_RD (0) and SHUT_WR (1), but the kernel uses
	 * RCV_SHUTDOWN (1) and SEND_SHUTDOWN (2), so we must increment mode
	 * here like the other address families करो.  Note also that the
	 * increment makes SHUT_RDWR (2) पूर्णांकo RCV_SHUTDOWN | SEND_SHUTDOWN (3),
	 * which is what we want.
	 */
	mode++;

	अगर ((mode & ~SHUTDOWN_MASK) || !mode)
		वापस -EINVAL;

	/* If this is a STREAM socket and it is not connected then bail out
	 * immediately.  If it is a DGRAM socket then we must first kick the
	 * socket so that it wakes up from any sleeping calls, क्रम example
	 * recv(), and then afterwards वापस the error.
	 */

	sk = sock->sk;

	lock_sock(sk);
	अगर (sock->state == SS_UNCONNECTED) अणु
		err = -ENOTCONN;
		अगर (sk->sk_type == SOCK_STREAM)
			जाओ out;
	पूर्ण अन्यथा अणु
		sock->state = SS_DISCONNECTING;
		err = 0;
	पूर्ण

	/* Receive and send shutकरोwns are treated alike. */
	mode = mode & (RCV_SHUTDOWN | SEND_SHUTDOWN);
	अगर (mode) अणु
		sk->sk_shutकरोwn |= mode;
		sk->sk_state_change(sk);

		अगर (sk->sk_type == SOCK_STREAM) अणु
			sock_reset_flag(sk, SOCK_DONE);
			vsock_send_shutकरोwn(sk, mode);
		पूर्ण
	पूर्ण

out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल __poll_t vsock_poll(काष्ठा file *file, काष्ठा socket *sock,
			       poll_table *रुको)
अणु
	काष्ठा sock *sk;
	__poll_t mask;
	काष्ठा vsock_sock *vsk;

	sk = sock->sk;
	vsk = vsock_sk(sk);

	poll_रुको(file, sk_sleep(sk), रुको);
	mask = 0;

	अगर (sk->sk_err)
		/* Signअगरy that there has been an error on this socket. */
		mask |= EPOLLERR;

	/* INET sockets treat local ग_लिखो shutकरोwn and peer ग_लिखो shutकरोwn as a
	 * हाल of EPOLLHUP set.
	 */
	अगर ((sk->sk_shutकरोwn == SHUTDOWN_MASK) ||
	    ((sk->sk_shutकरोwn & SEND_SHUTDOWN) &&
	     (vsk->peer_shutकरोwn & SEND_SHUTDOWN))) अणु
		mask |= EPOLLHUP;
	पूर्ण

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN ||
	    vsk->peer_shutकरोwn & SEND_SHUTDOWN) अणु
		mask |= EPOLLRDHUP;
	पूर्ण

	अगर (sock->type == SOCK_DGRAM) अणु
		/* For datagram sockets we can पढ़ो अगर there is something in
		 * the queue and ग_लिखो as दीर्घ as the socket isn't shutकरोwn क्रम
		 * sending.
		 */
		अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue) ||
		    (sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
			mask |= EPOLLIN | EPOLLRDNORM;
		पूर्ण

		अगर (!(sk->sk_shutकरोwn & SEND_SHUTDOWN))
			mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;

	पूर्ण अन्यथा अगर (sock->type == SOCK_STREAM) अणु
		स्थिर काष्ठा vsock_transport *transport;

		lock_sock(sk);

		transport = vsk->transport;

		/* Listening sockets that have connections in their accept
		 * queue can be पढ़ो.
		 */
		अगर (sk->sk_state == TCP_LISTEN
		    && !vsock_is_accept_queue_empty(sk))
			mask |= EPOLLIN | EPOLLRDNORM;

		/* If there is something in the queue then we can पढ़ो. */
		अगर (transport && transport->stream_is_active(vsk) &&
		    !(sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
			bool data_पढ़ोy_now = false;
			पूर्णांक ret = transport->notअगरy_poll_in(
					vsk, 1, &data_पढ़ोy_now);
			अगर (ret < 0) अणु
				mask |= EPOLLERR;
			पूर्ण अन्यथा अणु
				अगर (data_पढ़ोy_now)
					mask |= EPOLLIN | EPOLLRDNORM;

			पूर्ण
		पूर्ण

		/* Sockets whose connections have been बंदd, reset, or
		 * terminated should also be considered पढ़ो, and we check the
		 * shutकरोwn flag क्रम that.
		 */
		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN ||
		    vsk->peer_shutकरोwn & SEND_SHUTDOWN) अणु
			mask |= EPOLLIN | EPOLLRDNORM;
		पूर्ण

		/* Connected sockets that can produce data can be written. */
		अगर (transport && sk->sk_state == TCP_ESTABLISHED) अणु
			अगर (!(sk->sk_shutकरोwn & SEND_SHUTDOWN)) अणु
				bool space_avail_now = false;
				पूर्णांक ret = transport->notअगरy_poll_out(
						vsk, 1, &space_avail_now);
				अगर (ret < 0) अणु
					mask |= EPOLLERR;
				पूर्ण अन्यथा अणु
					अगर (space_avail_now)
						/* Remove EPOLLWRBAND since INET
						 * sockets are not setting it.
						 */
						mask |= EPOLLOUT | EPOLLWRNORM;

				पूर्ण
			पूर्ण
		पूर्ण

		/* Simulate INET socket poll behaviors, which sets
		 * EPOLLOUT|EPOLLWRNORM when peer is बंदd and nothing to पढ़ो,
		 * but local send is not shutकरोwn.
		 */
		अगर (sk->sk_state == TCP_CLOSE || sk->sk_state == TCP_CLOSING) अणु
			अगर (!(sk->sk_shutकरोwn & SEND_SHUTDOWN))
				mask |= EPOLLOUT | EPOLLWRNORM;

		पूर्ण

		release_sock(sk);
	पूर्ण

	वापस mask;
पूर्ण

अटल पूर्णांक vsock_dgram_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार len)
अणु
	पूर्णांक err;
	काष्ठा sock *sk;
	काष्ठा vsock_sock *vsk;
	काष्ठा sockaddr_vm *remote_addr;
	स्थिर काष्ठा vsock_transport *transport;

	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	/* For now, MSG_DONTWAIT is always assumed... */
	err = 0;
	sk = sock->sk;
	vsk = vsock_sk(sk);

	lock_sock(sk);

	transport = vsk->transport;

	err = vsock_स्वतः_bind(vsk);
	अगर (err)
		जाओ out;


	/* If the provided message contains an address, use that.  Otherwise
	 * fall back on the socket's remote handle (अगर it has been connected).
	 */
	अगर (msg->msg_name &&
	    vsock_addr_cast(msg->msg_name, msg->msg_namelen,
			    &remote_addr) == 0) अणु
		/* Ensure this address is of the right type and is a valid
		 * destination.
		 */

		अगर (remote_addr->svm_cid == VMADDR_CID_ANY)
			remote_addr->svm_cid = transport->get_local_cid();

		अगर (!vsock_addr_bound(remote_addr)) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (sock->state == SS_CONNECTED) अणु
		remote_addr = &vsk->remote_addr;

		अगर (remote_addr->svm_cid == VMADDR_CID_ANY)
			remote_addr->svm_cid = transport->get_local_cid();

		/* XXX Should connect() or this function ensure remote_addr is
		 * bound?
		 */
		अगर (!vsock_addr_bound(&vsk->remote_addr)) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!transport->dgram_allow(remote_addr->svm_cid,
				    remote_addr->svm_port)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = transport->dgram_enqueue(vsk, remote_addr, msg, len);

out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक vsock_dgram_connect(काष्ठा socket *sock,
			       काष्ठा sockaddr *addr, पूर्णांक addr_len, पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा sock *sk;
	काष्ठा vsock_sock *vsk;
	काष्ठा sockaddr_vm *remote_addr;

	sk = sock->sk;
	vsk = vsock_sk(sk);

	err = vsock_addr_cast(addr, addr_len, &remote_addr);
	अगर (err == -EAFNOSUPPORT && remote_addr->svm_family == AF_UNSPEC) अणु
		lock_sock(sk);
		vsock_addr_init(&vsk->remote_addr, VMADDR_CID_ANY,
				VMADDR_PORT_ANY);
		sock->state = SS_UNCONNECTED;
		release_sock(sk);
		वापस 0;
	पूर्ण अन्यथा अगर (err != 0)
		वापस -EINVAL;

	lock_sock(sk);

	err = vsock_स्वतः_bind(vsk);
	अगर (err)
		जाओ out;

	अगर (!vsk->transport->dgram_allow(remote_addr->svm_cid,
					 remote_addr->svm_port)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	स_नकल(&vsk->remote_addr, remote_addr, माप(vsk->remote_addr));
	sock->state = SS_CONNECTED;

out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक vsock_dgram_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा vsock_sock *vsk = vsock_sk(sock->sk);

	वापस vsk->transport->dgram_dequeue(vsk, msg, len, flags);
पूर्ण

अटल स्थिर काष्ठा proto_ops vsock_dgram_ops = अणु
	.family = PF_VSOCK,
	.owner = THIS_MODULE,
	.release = vsock_release,
	.bind = vsock_bind,
	.connect = vsock_dgram_connect,
	.socketpair = sock_no_socketpair,
	.accept = sock_no_accept,
	.getname = vsock_getname,
	.poll = vsock_poll,
	.ioctl = sock_no_ioctl,
	.listen = sock_no_listen,
	.shutकरोwn = vsock_shutकरोwn,
	.sendmsg = vsock_dgram_sendmsg,
	.recvmsg = vsock_dgram_recvmsg,
	.mmap = sock_no_mmap,
	.sendpage = sock_no_sendpage,
पूर्ण;

अटल पूर्णांक vsock_transport_cancel_pkt(काष्ठा vsock_sock *vsk)
अणु
	स्थिर काष्ठा vsock_transport *transport = vsk->transport;

	अगर (!transport || !transport->cancel_pkt)
		वापस -EOPNOTSUPP;

	वापस transport->cancel_pkt(vsk);
पूर्ण

अटल व्योम vsock_connect_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sock *sk;
	काष्ठा vsock_sock *vsk;

	vsk = container_of(work, काष्ठा vsock_sock, connect_work.work);
	sk = sk_vsock(vsk);

	lock_sock(sk);
	अगर (sk->sk_state == TCP_SYN_SENT &&
	    (sk->sk_shutकरोwn != SHUTDOWN_MASK)) अणु
		sk->sk_state = TCP_CLOSE;
		sk->sk_err = ETIMEDOUT;
		sk->sk_error_report(sk);
		vsock_transport_cancel_pkt(vsk);
	पूर्ण
	release_sock(sk);

	sock_put(sk);
पूर्ण

अटल पूर्णांक vsock_stream_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
				पूर्णांक addr_len, पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा sock *sk;
	काष्ठा vsock_sock *vsk;
	स्थिर काष्ठा vsock_transport *transport;
	काष्ठा sockaddr_vm *remote_addr;
	दीर्घ समयout;
	DEFINE_WAIT(रुको);

	err = 0;
	sk = sock->sk;
	vsk = vsock_sk(sk);

	lock_sock(sk);

	/* XXX AF_UNSPEC should make us disconnect like AF_INET. */
	चयन (sock->state) अणु
	हाल SS_CONNECTED:
		err = -EISCONN;
		जाओ out;
	हाल SS_DISCONNECTING:
		err = -EINVAL;
		जाओ out;
	हाल SS_CONNECTING:
		/* This जारीs on so we can move sock पूर्णांकo the SS_CONNECTED
		 * state once the connection has completed (at which poपूर्णांक err
		 * will be set to zero also).  Otherwise, we will either रुको
		 * क्रम the connection or वापस -EALREADY should this be a
		 * non-blocking call.
		 */
		err = -EALREADY;
		अवरोध;
	शेष:
		अगर ((sk->sk_state == TCP_LISTEN) ||
		    vsock_addr_cast(addr, addr_len, &remote_addr) != 0) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		/* Set the remote address that we are connecting to. */
		स_नकल(&vsk->remote_addr, remote_addr,
		       माप(vsk->remote_addr));

		err = vsock_assign_transport(vsk, शून्य);
		अगर (err)
			जाओ out;

		transport = vsk->transport;

		/* The hypervisor and well-known contexts करो not have socket
		 * endpoपूर्णांकs.
		 */
		अगर (!transport ||
		    !transport->stream_allow(remote_addr->svm_cid,
					     remote_addr->svm_port)) अणु
			err = -ENETUNREACH;
			जाओ out;
		पूर्ण

		err = vsock_स्वतः_bind(vsk);
		अगर (err)
			जाओ out;

		sk->sk_state = TCP_SYN_SENT;

		err = transport->connect(vsk);
		अगर (err < 0)
			जाओ out;

		/* Mark sock as connecting and set the error code to in
		 * progress in हाल this is a non-blocking connect.
		 */
		sock->state = SS_CONNECTING;
		err = -EINPROGRESS;
	पूर्ण

	/* The receive path will handle all communication until we are able to
	 * enter the connected state.  Here we रुको क्रम the connection to be
	 * completed or a notअगरication of an error.
	 */
	समयout = vsk->connect_समयout;
	prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);

	जबतक (sk->sk_state != TCP_ESTABLISHED && sk->sk_err == 0) अणु
		अगर (flags & O_NONBLOCK) अणु
			/* If we're not going to block, we schedule a समयout
			 * function to generate a समयout on the connection
			 * attempt, in हाल the peer करोesn't respond in a
			 * समयly manner. We hold on to the socket until the
			 * समयout fires.
			 */
			sock_hold(sk);
			schedule_delayed_work(&vsk->connect_work, समयout);

			/* Skip ahead to preserve error code set above. */
			जाओ out_रुको;
		पूर्ण

		release_sock(sk);
		समयout = schedule_समयout(समयout);
		lock_sock(sk);

		अगर (संकेत_pending(current)) अणु
			err = sock_पूर्णांकr_त्रुटि_सं(समयout);
			sk->sk_state = TCP_CLOSE;
			sock->state = SS_UNCONNECTED;
			vsock_transport_cancel_pkt(vsk);
			जाओ out_रुको;
		पूर्ण अन्यथा अगर (समयout == 0) अणु
			err = -ETIMEDOUT;
			sk->sk_state = TCP_CLOSE;
			sock->state = SS_UNCONNECTED;
			vsock_transport_cancel_pkt(vsk);
			जाओ out_रुको;
		पूर्ण

		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
	पूर्ण

	अगर (sk->sk_err) अणु
		err = -sk->sk_err;
		sk->sk_state = TCP_CLOSE;
		sock->state = SS_UNCONNECTED;
	पूर्ण अन्यथा अणु
		err = 0;
	पूर्ण

out_रुको:
	finish_रुको(sk_sleep(sk), &रुको);
out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक vsock_accept(काष्ठा socket *sock, काष्ठा socket *newsock, पूर्णांक flags,
			bool kern)
अणु
	काष्ठा sock *listener;
	पूर्णांक err;
	काष्ठा sock *connected;
	काष्ठा vsock_sock *vconnected;
	दीर्घ समयout;
	DEFINE_WAIT(रुको);

	err = 0;
	listener = sock->sk;

	lock_sock(listener);

	अगर (sock->type != SOCK_STREAM) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (listener->sk_state != TCP_LISTEN) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Wait क्रम children sockets to appear; these are the new sockets
	 * created upon connection establishment.
	 */
	समयout = sock_rcvसमयo(listener, flags & O_NONBLOCK);
	prepare_to_रुको(sk_sleep(listener), &रुको, TASK_INTERRUPTIBLE);

	जबतक ((connected = vsock_dequeue_accept(listener)) == शून्य &&
	       listener->sk_err == 0) अणु
		release_sock(listener);
		समयout = schedule_समयout(समयout);
		finish_रुको(sk_sleep(listener), &रुको);
		lock_sock(listener);

		अगर (संकेत_pending(current)) अणु
			err = sock_पूर्णांकr_त्रुटि_सं(समयout);
			जाओ out;
		पूर्ण अन्यथा अगर (समयout == 0) अणु
			err = -EAGAIN;
			जाओ out;
		पूर्ण

		prepare_to_रुको(sk_sleep(listener), &रुको, TASK_INTERRUPTIBLE);
	पूर्ण
	finish_रुको(sk_sleep(listener), &रुको);

	अगर (listener->sk_err)
		err = -listener->sk_err;

	अगर (connected) अणु
		sk_acceptq_हटाओd(listener);

		lock_sock_nested(connected, SINGLE_DEPTH_NESTING);
		vconnected = vsock_sk(connected);

		/* If the listener socket has received an error, then we should
		 * reject this socket and वापस.  Note that we simply mark the
		 * socket rejected, drop our reference, and let the cleanup
		 * function handle the cleanup; the fact that we found it in
		 * the listener's accept queue guarantees that the cleanup
		 * function hasn't run yet.
		 */
		अगर (err) अणु
			vconnected->rejected = true;
		पूर्ण अन्यथा अणु
			newsock->state = SS_CONNECTED;
			sock_graft(connected, newsock);
		पूर्ण

		release_sock(connected);
		sock_put(connected);
	पूर्ण

out:
	release_sock(listener);
	वापस err;
पूर्ण

अटल पूर्णांक vsock_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	पूर्णांक err;
	काष्ठा sock *sk;
	काष्ठा vsock_sock *vsk;

	sk = sock->sk;

	lock_sock(sk);

	अगर (sock->type != SOCK_STREAM) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (sock->state != SS_UNCONNECTED) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	vsk = vsock_sk(sk);

	अगर (!vsock_addr_bound(&vsk->local_addr)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	sk->sk_max_ack_backlog = backlog;
	sk->sk_state = TCP_LISTEN;

	err = 0;

out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल व्योम vsock_update_buffer_size(काष्ठा vsock_sock *vsk,
				     स्थिर काष्ठा vsock_transport *transport,
				     u64 val)
अणु
	अगर (val > vsk->buffer_max_size)
		val = vsk->buffer_max_size;

	अगर (val < vsk->buffer_min_size)
		val = vsk->buffer_min_size;

	अगर (val != vsk->buffer_size &&
	    transport && transport->notअगरy_buffer_size)
		transport->notअगरy_buffer_size(vsk, &val);

	vsk->buffer_size = val;
पूर्ण

अटल पूर्णांक vsock_stream_setsockopt(काष्ठा socket *sock,
				   पूर्णांक level,
				   पूर्णांक optname,
				   sockptr_t optval,
				   अचिन्हित पूर्णांक optlen)
अणु
	पूर्णांक err;
	काष्ठा sock *sk;
	काष्ठा vsock_sock *vsk;
	स्थिर काष्ठा vsock_transport *transport;
	u64 val;

	अगर (level != AF_VSOCK)
		वापस -ENOPROTOOPT;

#घोषणा COPY_IN(_v)                                       \
	करो अणु						  \
		अगर (optlen < माप(_v)) अणु		  \
			err = -EINVAL;			  \
			जाओ निकास;			  \
		पूर्ण					  \
		अगर (copy_from_sockptr(&_v, optval, माप(_v)) != 0) अणु	\
			err = -EFAULT;					\
			जाओ निकास;					\
		पूर्ण							\
	पूर्ण जबतक (0)

	err = 0;
	sk = sock->sk;
	vsk = vsock_sk(sk);

	lock_sock(sk);

	transport = vsk->transport;

	चयन (optname) अणु
	हाल SO_VM_SOCKETS_BUFFER_SIZE:
		COPY_IN(val);
		vsock_update_buffer_size(vsk, transport, val);
		अवरोध;

	हाल SO_VM_SOCKETS_BUFFER_MAX_SIZE:
		COPY_IN(val);
		vsk->buffer_max_size = val;
		vsock_update_buffer_size(vsk, transport, vsk->buffer_size);
		अवरोध;

	हाल SO_VM_SOCKETS_BUFFER_MIN_SIZE:
		COPY_IN(val);
		vsk->buffer_min_size = val;
		vsock_update_buffer_size(vsk, transport, vsk->buffer_size);
		अवरोध;

	हाल SO_VM_SOCKETS_CONNECT_TIMEOUT: अणु
		काष्ठा __kernel_old_समयval tv;
		COPY_IN(tv);
		अगर (tv.tv_sec >= 0 && tv.tv_usec < USEC_PER_SEC &&
		    tv.tv_sec < (MAX_SCHEDULE_TIMEOUT / HZ - 1)) अणु
			vsk->connect_समयout = tv.tv_sec * HZ +
			    DIV_ROUND_UP(tv.tv_usec, (1000000 / HZ));
			अगर (vsk->connect_समयout == 0)
				vsk->connect_समयout =
				    VSOCK_DEFAULT_CONNECT_TIMEOUT;

		पूर्ण अन्यथा अणु
			err = -दुस्फल;
		पूर्ण
		अवरोध;
	पूर्ण

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

#अघोषित COPY_IN

निकास:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक vsock_stream_माला_लोockopt(काष्ठा socket *sock,
				   पूर्णांक level, पूर्णांक optname,
				   अक्षर __user *optval,
				   पूर्णांक __user *optlen)
अणु
	पूर्णांक err;
	पूर्णांक len;
	काष्ठा sock *sk;
	काष्ठा vsock_sock *vsk;
	u64 val;

	अगर (level != AF_VSOCK)
		वापस -ENOPROTOOPT;

	err = get_user(len, optlen);
	अगर (err != 0)
		वापस err;

#घोषणा COPY_OUT(_v)                            \
	करो अणु					\
		अगर (len < माप(_v))		\
			वापस -EINVAL;		\
						\
		len = माप(_v);		\
		अगर (copy_to_user(optval, &_v, len) != 0)	\
			वापस -EFAULT;				\
								\
	पूर्ण जबतक (0)

	err = 0;
	sk = sock->sk;
	vsk = vsock_sk(sk);

	चयन (optname) अणु
	हाल SO_VM_SOCKETS_BUFFER_SIZE:
		val = vsk->buffer_size;
		COPY_OUT(val);
		अवरोध;

	हाल SO_VM_SOCKETS_BUFFER_MAX_SIZE:
		val = vsk->buffer_max_size;
		COPY_OUT(val);
		अवरोध;

	हाल SO_VM_SOCKETS_BUFFER_MIN_SIZE:
		val = vsk->buffer_min_size;
		COPY_OUT(val);
		अवरोध;

	हाल SO_VM_SOCKETS_CONNECT_TIMEOUT: अणु
		काष्ठा __kernel_old_समयval tv;
		tv.tv_sec = vsk->connect_समयout / HZ;
		tv.tv_usec =
		    (vsk->connect_समयout -
		     tv.tv_sec * HZ) * (1000000 / HZ);
		COPY_OUT(tv);
		अवरोध;
	पूर्ण
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	err = put_user(len, optlen);
	अगर (err != 0)
		वापस -EFAULT;

#अघोषित COPY_OUT

	वापस 0;
पूर्ण

अटल पूर्णांक vsock_stream_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
				माप_प्रकार len)
अणु
	काष्ठा sock *sk;
	काष्ठा vsock_sock *vsk;
	स्थिर काष्ठा vsock_transport *transport;
	sमाप_प्रकार total_written;
	दीर्घ समयout;
	पूर्णांक err;
	काष्ठा vsock_transport_send_notअगरy_data send_data;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	sk = sock->sk;
	vsk = vsock_sk(sk);
	total_written = 0;
	err = 0;

	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	lock_sock(sk);

	transport = vsk->transport;

	/* Callers should not provide a destination with stream sockets. */
	अगर (msg->msg_namelen) अणु
		err = sk->sk_state == TCP_ESTABLISHED ? -EISCONN : -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* Send data only अगर both sides are not shutकरोwn in the direction. */
	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN ||
	    vsk->peer_shutकरोwn & RCV_SHUTDOWN) अणु
		err = -EPIPE;
		जाओ out;
	पूर्ण

	अगर (!transport || sk->sk_state != TCP_ESTABLISHED ||
	    !vsock_addr_bound(&vsk->local_addr)) अणु
		err = -ENOTCONN;
		जाओ out;
	पूर्ण

	अगर (!vsock_addr_bound(&vsk->remote_addr)) अणु
		err = -EDESTADDRREQ;
		जाओ out;
	पूर्ण

	/* Wait क्रम room in the produce queue to enqueue our user's data. */
	समयout = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);

	err = transport->notअगरy_send_init(vsk, &send_data);
	अगर (err < 0)
		जाओ out;

	जबतक (total_written < len) अणु
		sमाप_प्रकार written;

		add_रुको_queue(sk_sleep(sk), &रुको);
		जबतक (vsock_stream_has_space(vsk) == 0 &&
		       sk->sk_err == 0 &&
		       !(sk->sk_shutकरोwn & SEND_SHUTDOWN) &&
		       !(vsk->peer_shutकरोwn & RCV_SHUTDOWN)) अणु

			/* Don't रुको क्रम non-blocking sockets. */
			अगर (समयout == 0) अणु
				err = -EAGAIN;
				हटाओ_रुको_queue(sk_sleep(sk), &रुको);
				जाओ out_err;
			पूर्ण

			err = transport->notअगरy_send_pre_block(vsk, &send_data);
			अगर (err < 0) अणु
				हटाओ_रुको_queue(sk_sleep(sk), &रुको);
				जाओ out_err;
			पूर्ण

			release_sock(sk);
			समयout = रुको_woken(&रुको, TASK_INTERRUPTIBLE, समयout);
			lock_sock(sk);
			अगर (संकेत_pending(current)) अणु
				err = sock_पूर्णांकr_त्रुटि_सं(समयout);
				हटाओ_रुको_queue(sk_sleep(sk), &रुको);
				जाओ out_err;
			पूर्ण अन्यथा अगर (समयout == 0) अणु
				err = -EAGAIN;
				हटाओ_रुको_queue(sk_sleep(sk), &रुको);
				जाओ out_err;
			पूर्ण
		पूर्ण
		हटाओ_रुको_queue(sk_sleep(sk), &रुको);

		/* These checks occur both as part of and after the loop
		 * conditional since we need to check beक्रमe and after
		 * sleeping.
		 */
		अगर (sk->sk_err) अणु
			err = -sk->sk_err;
			जाओ out_err;
		पूर्ण अन्यथा अगर ((sk->sk_shutकरोwn & SEND_SHUTDOWN) ||
			   (vsk->peer_shutकरोwn & RCV_SHUTDOWN)) अणु
			err = -EPIPE;
			जाओ out_err;
		पूर्ण

		err = transport->notअगरy_send_pre_enqueue(vsk, &send_data);
		अगर (err < 0)
			जाओ out_err;

		/* Note that enqueue will only ग_लिखो as many bytes as are मुक्त
		 * in the produce queue, so we करोn't need to ensure len is
		 * smaller than the queue size.  It is the caller's
		 * responsibility to check how many bytes we were able to send.
		 */

		written = transport->stream_enqueue(
				vsk, msg,
				len - total_written);
		अगर (written < 0) अणु
			err = -ENOMEM;
			जाओ out_err;
		पूर्ण

		total_written += written;

		err = transport->notअगरy_send_post_enqueue(
				vsk, written, &send_data);
		अगर (err < 0)
			जाओ out_err;

	पूर्ण

out_err:
	अगर (total_written > 0)
		err = total_written;
out:
	release_sock(sk);
	वापस err;
पूर्ण


अटल पूर्णांक
vsock_stream_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
		     पूर्णांक flags)
अणु
	काष्ठा sock *sk;
	काष्ठा vsock_sock *vsk;
	स्थिर काष्ठा vsock_transport *transport;
	पूर्णांक err;
	माप_प्रकार target;
	sमाप_प्रकार copied;
	दीर्घ समयout;
	काष्ठा vsock_transport_recv_notअगरy_data recv_data;

	DEFINE_WAIT(रुको);

	sk = sock->sk;
	vsk = vsock_sk(sk);
	err = 0;

	lock_sock(sk);

	transport = vsk->transport;

	अगर (!transport || sk->sk_state != TCP_ESTABLISHED) अणु
		/* Recvmsg is supposed to वापस 0 अगर a peer perक्रमms an
		 * orderly shutकरोwn. Dअगरferentiate between that हाल and when a
		 * peer has not connected or a local shutकरोwn occurred with the
		 * SOCK_DONE flag.
		 */
		अगर (sock_flag(sk, SOCK_DONE))
			err = 0;
		अन्यथा
			err = -ENOTCONN;

		जाओ out;
	पूर्ण

	अगर (flags & MSG_OOB) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* We करोn't check peer_shutकरोwn flag here since peer may actually shut
	 * करोwn, but there can be data in the queue that a local socket can
	 * receive.
	 */
	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN) अणु
		err = 0;
		जाओ out;
	पूर्ण

	/* It is valid on Linux to pass in a zero-length receive buffer.  This
	 * is not an error.  We may as well bail out now.
	 */
	अगर (!len) अणु
		err = 0;
		जाओ out;
	पूर्ण

	/* We must not copy less than target bytes पूर्णांकo the user's buffer
	 * beक्रमe वापसing successfully, so we रुको क्रम the consume queue to
	 * have that much data to consume beक्रमe dequeueing.  Note that this
	 * makes it impossible to handle हालs where target is greater than the
	 * queue size.
	 */
	target = sock_rcvlowat(sk, flags & MSG_WAITALL, len);
	अगर (target >= transport->stream_rcvhiwat(vsk)) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	समयout = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);
	copied = 0;

	err = transport->notअगरy_recv_init(vsk, target, &recv_data);
	अगर (err < 0)
		जाओ out;


	जबतक (1) अणु
		s64 पढ़ोy;

		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
		पढ़ोy = vsock_stream_has_data(vsk);

		अगर (पढ़ोy == 0) अणु
			अगर (sk->sk_err != 0 ||
			    (sk->sk_shutकरोwn & RCV_SHUTDOWN) ||
			    (vsk->peer_shutकरोwn & SEND_SHUTDOWN)) अणु
				finish_रुको(sk_sleep(sk), &रुको);
				अवरोध;
			पूर्ण
			/* Don't रुको क्रम non-blocking sockets. */
			अगर (समयout == 0) अणु
				err = -EAGAIN;
				finish_रुको(sk_sleep(sk), &रुको);
				अवरोध;
			पूर्ण

			err = transport->notअगरy_recv_pre_block(
					vsk, target, &recv_data);
			अगर (err < 0) अणु
				finish_रुको(sk_sleep(sk), &रुको);
				अवरोध;
			पूर्ण
			release_sock(sk);
			समयout = schedule_समयout(समयout);
			lock_sock(sk);

			अगर (संकेत_pending(current)) अणु
				err = sock_पूर्णांकr_त्रुटि_सं(समयout);
				finish_रुको(sk_sleep(sk), &रुको);
				अवरोध;
			पूर्ण अन्यथा अगर (समयout == 0) अणु
				err = -EAGAIN;
				finish_रुको(sk_sleep(sk), &रुको);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			sमाप_प्रकार पढ़ो;

			finish_रुको(sk_sleep(sk), &रुको);

			अगर (पढ़ोy < 0) अणु
				/* Invalid queue pair content. XXX This should
				* be changed to a connection reset in a later
				* change.
				*/

				err = -ENOMEM;
				जाओ out;
			पूर्ण

			err = transport->notअगरy_recv_pre_dequeue(
					vsk, target, &recv_data);
			अगर (err < 0)
				अवरोध;

			पढ़ो = transport->stream_dequeue(
					vsk, msg,
					len - copied, flags);
			अगर (पढ़ो < 0) अणु
				err = -ENOMEM;
				अवरोध;
			पूर्ण

			copied += पढ़ो;

			err = transport->notअगरy_recv_post_dequeue(
					vsk, target, पढ़ो,
					!(flags & MSG_PEEK), &recv_data);
			अगर (err < 0)
				जाओ out;

			अगर (पढ़ो >= target || flags & MSG_PEEK)
				अवरोध;

			target -= पढ़ो;
		पूर्ण
	पूर्ण

	अगर (sk->sk_err)
		err = -sk->sk_err;
	अन्यथा अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		err = 0;

	अगर (copied > 0)
		err = copied;

out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा proto_ops vsock_stream_ops = अणु
	.family = PF_VSOCK,
	.owner = THIS_MODULE,
	.release = vsock_release,
	.bind = vsock_bind,
	.connect = vsock_stream_connect,
	.socketpair = sock_no_socketpair,
	.accept = vsock_accept,
	.getname = vsock_getname,
	.poll = vsock_poll,
	.ioctl = sock_no_ioctl,
	.listen = vsock_listen,
	.shutकरोwn = vsock_shutकरोwn,
	.setsockopt = vsock_stream_setsockopt,
	.माला_लोockopt = vsock_stream_माला_लोockopt,
	.sendmsg = vsock_stream_sendmsg,
	.recvmsg = vsock_stream_recvmsg,
	.mmap = sock_no_mmap,
	.sendpage = sock_no_sendpage,
पूर्ण;

अटल पूर्णांक vsock_create(काष्ठा net *net, काष्ठा socket *sock,
			पूर्णांक protocol, पूर्णांक kern)
अणु
	काष्ठा vsock_sock *vsk;
	काष्ठा sock *sk;
	पूर्णांक ret;

	अगर (!sock)
		वापस -EINVAL;

	अगर (protocol && protocol != PF_VSOCK)
		वापस -EPROTONOSUPPORT;

	चयन (sock->type) अणु
	हाल SOCK_DGRAM:
		sock->ops = &vsock_dgram_ops;
		अवरोध;
	हाल SOCK_STREAM:
		sock->ops = &vsock_stream_ops;
		अवरोध;
	शेष:
		वापस -ESOCKTNOSUPPORT;
	पूर्ण

	sock->state = SS_UNCONNECTED;

	sk = __vsock_create(net, sock, शून्य, GFP_KERNEL, 0, kern);
	अगर (!sk)
		वापस -ENOMEM;

	vsk = vsock_sk(sk);

	अगर (sock->type == SOCK_DGRAM) अणु
		ret = vsock_assign_transport(vsk, शून्य);
		अगर (ret < 0) अणु
			sock_put(sk);
			वापस ret;
		पूर्ण
	पूर्ण

	vsock_insert_unbound(vsk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_proto_family vsock_family_ops = अणु
	.family = AF_VSOCK,
	.create = vsock_create,
	.owner = THIS_MODULE,
पूर्ण;

अटल दीर्घ vsock_dev_करो_ioctl(काष्ठा file *filp,
			       अचिन्हित पूर्णांक cmd, व्योम __user *ptr)
अणु
	u32 __user *p = ptr;
	u32 cid = VMADDR_CID_ANY;
	पूर्णांक retval = 0;

	चयन (cmd) अणु
	हाल IOCTL_VM_SOCKETS_GET_LOCAL_CID:
		/* To be compatible with the VMCI behavior, we prioritize the
		 * guest CID instead of well-know host CID (VMADDR_CID_HOST).
		 */
		अगर (transport_g2h)
			cid = transport_g2h->get_local_cid();
		अन्यथा अगर (transport_h2g)
			cid = transport_h2g->get_local_cid();

		अगर (put_user(cid, p) != 0)
			retval = -EFAULT;
		अवरोध;

	शेष:
		retval = -ENOIOCTLCMD;
	पूर्ण

	वापस retval;
पूर्ण

अटल दीर्घ vsock_dev_ioctl(काष्ठा file *filp,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस vsock_dev_करो_ioctl(filp, cmd, (व्योम __user *)arg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ vsock_dev_compat_ioctl(काष्ठा file *filp,
				   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस vsock_dev_करो_ioctl(filp, cmd, compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations vsock_device_ops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= vsock_dev_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= vsock_dev_compat_ioctl,
#पूर्ण_अगर
	.खोलो		= nonseekable_खोलो,
पूर्ण;

अटल काष्ठा miscdevice vsock_device = अणु
	.name		= "vsock",
	.fops		= &vsock_device_ops,
पूर्ण;

अटल पूर्णांक __init vsock_init(व्योम)
अणु
	पूर्णांक err = 0;

	vsock_init_tables();

	vsock_proto.owner = THIS_MODULE;
	vsock_device.minor = MISC_DYNAMIC_MINOR;
	err = misc_रेजिस्टर(&vsock_device);
	अगर (err) अणु
		pr_err("Failed to register misc device\n");
		जाओ err_reset_transport;
	पूर्ण

	err = proto_रेजिस्टर(&vsock_proto, 1);	/* we want our slab */
	अगर (err) अणु
		pr_err("Cannot register vsock protocol\n");
		जाओ err_deरेजिस्टर_misc;
	पूर्ण

	err = sock_रेजिस्टर(&vsock_family_ops);
	अगर (err) अणु
		pr_err("could not register af_vsock (%d) address family: %d\n",
		       AF_VSOCK, err);
		जाओ err_unरेजिस्टर_proto;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_proto:
	proto_unरेजिस्टर(&vsock_proto);
err_deरेजिस्टर_misc:
	misc_deरेजिस्टर(&vsock_device);
err_reset_transport:
	वापस err;
पूर्ण

अटल व्योम __निकास vsock_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&vsock_device);
	sock_unरेजिस्टर(AF_VSOCK);
	proto_unरेजिस्टर(&vsock_proto);
पूर्ण

स्थिर काष्ठा vsock_transport *vsock_core_get_transport(काष्ठा vsock_sock *vsk)
अणु
	वापस vsk->transport;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_core_get_transport);

पूर्णांक vsock_core_रेजिस्टर(स्थिर काष्ठा vsock_transport *t, पूर्णांक features)
अणु
	स्थिर काष्ठा vsock_transport *t_h2g, *t_g2h, *t_dgram, *t_local;
	पूर्णांक err = mutex_lock_पूर्णांकerruptible(&vsock_रेजिस्टर_mutex);

	अगर (err)
		वापस err;

	t_h2g = transport_h2g;
	t_g2h = transport_g2h;
	t_dgram = transport_dgram;
	t_local = transport_local;

	अगर (features & VSOCK_TRANSPORT_F_H2G) अणु
		अगर (t_h2g) अणु
			err = -EBUSY;
			जाओ err_busy;
		पूर्ण
		t_h2g = t;
	पूर्ण

	अगर (features & VSOCK_TRANSPORT_F_G2H) अणु
		अगर (t_g2h) अणु
			err = -EBUSY;
			जाओ err_busy;
		पूर्ण
		t_g2h = t;
	पूर्ण

	अगर (features & VSOCK_TRANSPORT_F_DGRAM) अणु
		अगर (t_dgram) अणु
			err = -EBUSY;
			जाओ err_busy;
		पूर्ण
		t_dgram = t;
	पूर्ण

	अगर (features & VSOCK_TRANSPORT_F_LOCAL) अणु
		अगर (t_local) अणु
			err = -EBUSY;
			जाओ err_busy;
		पूर्ण
		t_local = t;
	पूर्ण

	transport_h2g = t_h2g;
	transport_g2h = t_g2h;
	transport_dgram = t_dgram;
	transport_local = t_local;

err_busy:
	mutex_unlock(&vsock_रेजिस्टर_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(vsock_core_रेजिस्टर);

व्योम vsock_core_unरेजिस्टर(स्थिर काष्ठा vsock_transport *t)
अणु
	mutex_lock(&vsock_रेजिस्टर_mutex);

	अगर (transport_h2g == t)
		transport_h2g = शून्य;

	अगर (transport_g2h == t)
		transport_g2h = शून्य;

	अगर (transport_dgram == t)
		transport_dgram = शून्य;

	अगर (transport_local == t)
		transport_local = शून्य;

	mutex_unlock(&vsock_रेजिस्टर_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(vsock_core_unरेजिस्टर);

module_init(vsock_init);
module_निकास(vsock_निकास);

MODULE_AUTHOR("VMware, Inc.");
MODULE_DESCRIPTION("VMware Virtual Socket Family");
MODULE_VERSION("1.0.2.0-k");
MODULE_LICENSE("GPL v2");
