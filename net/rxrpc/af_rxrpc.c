<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AF_RXRPC implementation
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/net.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/poll.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/key-type.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश "ar-internal.h"

MODULE_DESCRIPTION("RxRPC network protocol");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_RXRPC);

अचिन्हित पूर्णांक rxrpc_debug; // = RXRPC_DEBUG_KPROTO;
module_param_named(debug, rxrpc_debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug, "RxRPC debugging mask");

अटल काष्ठा proto rxrpc_proto;
अटल स्थिर काष्ठा proto_ops rxrpc_rpc_ops;

/* current debugging ID */
atomic_t rxrpc_debug_id;
EXPORT_SYMBOL(rxrpc_debug_id);

/* count of skbs currently in use */
atomic_t rxrpc_n_tx_skbs, rxrpc_n_rx_skbs;

काष्ठा workqueue_काष्ठा *rxrpc_workqueue;

अटल व्योम rxrpc_sock_deकाष्ठाor(काष्ठा sock *);

/*
 * see अगर an RxRPC socket is currently writable
 */
अटल अंतरभूत पूर्णांक rxrpc_writable(काष्ठा sock *sk)
अणु
	वापस refcount_पढ़ो(&sk->sk_wmem_alloc) < (माप_प्रकार) sk->sk_sndbuf;
पूर्ण

/*
 * रुको क्रम ग_लिखो bufferage to become available
 */
अटल व्योम rxrpc_ग_लिखो_space(काष्ठा sock *sk)
अणु
	_enter("%p", sk);
	rcu_पढ़ो_lock();
	अगर (rxrpc_writable(sk)) अणु
		काष्ठा socket_wq *wq = rcu_dereference(sk->sk_wq);

		अगर (skwq_has_sleeper(wq))
			wake_up_पूर्णांकerruptible(&wq->रुको);
		sk_wake_async(sk, SOCK_WAKE_SPACE, POLL_OUT);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * validate an RxRPC address
 */
अटल पूर्णांक rxrpc_validate_address(काष्ठा rxrpc_sock *rx,
				  काष्ठा sockaddr_rxrpc *srx,
				  पूर्णांक len)
अणु
	अचिन्हित पूर्णांक tail;

	अगर (len < माप(काष्ठा sockaddr_rxrpc))
		वापस -EINVAL;

	अगर (srx->srx_family != AF_RXRPC)
		वापस -EAFNOSUPPORT;

	अगर (srx->transport_type != SOCK_DGRAM)
		वापस -ESOCKTNOSUPPORT;

	len -= दुरत्व(काष्ठा sockaddr_rxrpc, transport);
	अगर (srx->transport_len < माप(sa_family_t) ||
	    srx->transport_len > len)
		वापस -EINVAL;

	अगर (srx->transport.family != rx->family &&
	    srx->transport.family == AF_INET && rx->family != AF_INET6)
		वापस -EAFNOSUPPORT;

	चयन (srx->transport.family) अणु
	हाल AF_INET:
		अगर (srx->transport_len < माप(काष्ठा sockaddr_in))
			वापस -EINVAL;
		tail = दुरत्व(काष्ठा sockaddr_rxrpc, transport.sin.__pad);
		अवरोध;

#अगर_घोषित CONFIG_AF_RXRPC_IPV6
	हाल AF_INET6:
		अगर (srx->transport_len < माप(काष्ठा sockaddr_in6))
			वापस -EINVAL;
		tail = दुरत्व(काष्ठा sockaddr_rxrpc, transport) +
			माप(काष्ठा sockaddr_in6);
		अवरोध;
#पूर्ण_अगर

	शेष:
		वापस -EAFNOSUPPORT;
	पूर्ण

	अगर (tail < len)
		स_रखो((व्योम *)srx + tail, 0, len - tail);
	_debug("INET: %pISp", &srx->transport);
	वापस 0;
पूर्ण

/*
 * bind a local address to an RxRPC socket
 */
अटल पूर्णांक rxrpc_bind(काष्ठा socket *sock, काष्ठा sockaddr *saddr, पूर्णांक len)
अणु
	काष्ठा sockaddr_rxrpc *srx = (काष्ठा sockaddr_rxrpc *)saddr;
	काष्ठा rxrpc_local *local;
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sock->sk);
	u16 service_id;
	पूर्णांक ret;

	_enter("%p,%p,%d", rx, saddr, len);

	ret = rxrpc_validate_address(rx, srx, len);
	अगर (ret < 0)
		जाओ error;
	service_id = srx->srx_service;

	lock_sock(&rx->sk);

	चयन (rx->sk.sk_state) अणु
	हाल RXRPC_UNBOUND:
		rx->srx = *srx;
		local = rxrpc_lookup_local(sock_net(&rx->sk), &rx->srx);
		अगर (IS_ERR(local)) अणु
			ret = PTR_ERR(local);
			जाओ error_unlock;
		पूर्ण

		अगर (service_id) अणु
			ग_लिखो_lock(&local->services_lock);
			अगर (rcu_access_poपूर्णांकer(local->service))
				जाओ service_in_use;
			rx->local = local;
			rcu_assign_poपूर्णांकer(local->service, rx);
			ग_लिखो_unlock(&local->services_lock);

			rx->sk.sk_state = RXRPC_SERVER_BOUND;
		पूर्ण अन्यथा अणु
			rx->local = local;
			rx->sk.sk_state = RXRPC_CLIENT_BOUND;
		पूर्ण
		अवरोध;

	हाल RXRPC_SERVER_BOUND:
		ret = -EINVAL;
		अगर (service_id == 0)
			जाओ error_unlock;
		ret = -EADDRINUSE;
		अगर (service_id == rx->srx.srx_service)
			जाओ error_unlock;
		ret = -EINVAL;
		srx->srx_service = rx->srx.srx_service;
		अगर (स_भेद(srx, &rx->srx, माप(*srx)) != 0)
			जाओ error_unlock;
		rx->second_service = service_id;
		rx->sk.sk_state = RXRPC_SERVER_BOUND2;
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ error_unlock;
	पूर्ण

	release_sock(&rx->sk);
	_leave(" = 0");
	वापस 0;

service_in_use:
	ग_लिखो_unlock(&local->services_lock);
	rxrpc_unuse_local(local);
	rxrpc_put_local(local);
	ret = -EADDRINUSE;
error_unlock:
	release_sock(&rx->sk);
error:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * set the number of pending calls permitted on a listening socket
 */
अटल पूर्णांक rxrpc_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sk);
	अचिन्हित पूर्णांक max, old;
	पूर्णांक ret;

	_enter("%p,%d", rx, backlog);

	lock_sock(&rx->sk);

	चयन (rx->sk.sk_state) अणु
	हाल RXRPC_UNBOUND:
		ret = -EADDRNOTAVAIL;
		अवरोध;
	हाल RXRPC_SERVER_BOUND:
	हाल RXRPC_SERVER_BOUND2:
		ASSERT(rx->local != शून्य);
		max = READ_ONCE(rxrpc_max_backlog);
		ret = -EINVAL;
		अगर (backlog == पूर्णांक_उच्च)
			backlog = max;
		अन्यथा अगर (backlog < 0 || backlog > max)
			अवरोध;
		old = sk->sk_max_ack_backlog;
		sk->sk_max_ack_backlog = backlog;
		ret = rxrpc_service_pपुनः_स्मृति(rx, GFP_KERNEL);
		अगर (ret == 0)
			rx->sk.sk_state = RXRPC_SERVER_LISTENING;
		अन्यथा
			sk->sk_max_ack_backlog = old;
		अवरोध;
	हाल RXRPC_SERVER_LISTENING:
		अगर (backlog == 0) अणु
			rx->sk.sk_state = RXRPC_SERVER_LISTEN_DISABLED;
			sk->sk_max_ack_backlog = 0;
			rxrpc_discard_pपुनः_स्मृति(rx);
			ret = 0;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		ret = -EBUSY;
		अवरोध;
	पूर्ण

	release_sock(&rx->sk);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/**
 * rxrpc_kernel_begin_call - Allow a kernel service to begin a call
 * @sock: The socket on which to make the call
 * @srx: The address of the peer to contact
 * @key: The security context to use (शेषs to socket setting)
 * @user_call_ID: The ID to use
 * @tx_total_len: Total length of data to transmit during the call (or -1)
 * @gfp: The allocation स्थिरraपूर्णांकs
 * @notअगरy_rx: Where to send notअगरications instead of socket queue
 * @upgrade: Request service upgrade क्रम call
 * @पूर्णांकerruptibility: The call is पूर्णांकerruptible, or can be canceled.
 * @debug_id: The debug ID क्रम tracing to be asचिन्हित to the call
 *
 * Allow a kernel service to begin a call on the nominated socket.  This just
 * sets up all the पूर्णांकernal tracking काष्ठाures and allocates connection and
 * call IDs as appropriate.  The call to be used is वापसed.
 *
 * The शेष socket destination address and security may be overridden by
 * supplying @srx and @key.
 */
काष्ठा rxrpc_call *rxrpc_kernel_begin_call(काष्ठा socket *sock,
					   काष्ठा sockaddr_rxrpc *srx,
					   काष्ठा key *key,
					   अचिन्हित दीर्घ user_call_ID,
					   s64 tx_total_len,
					   gfp_t gfp,
					   rxrpc_notअगरy_rx_t notअगरy_rx,
					   bool upgrade,
					   क्रमागत rxrpc_पूर्णांकerruptibility पूर्णांकerruptibility,
					   अचिन्हित पूर्णांक debug_id)
अणु
	काष्ठा rxrpc_conn_parameters cp;
	काष्ठा rxrpc_call_params p;
	काष्ठा rxrpc_call *call;
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sock->sk);
	पूर्णांक ret;

	_enter(",,%x,%lx", key_serial(key), user_call_ID);

	ret = rxrpc_validate_address(rx, srx, माप(*srx));
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	lock_sock(&rx->sk);

	अगर (!key)
		key = rx->key;
	अगर (key && !key->payload.data[0])
		key = शून्य; /* a no-security key */

	स_रखो(&p, 0, माप(p));
	p.user_call_ID		= user_call_ID;
	p.tx_total_len		= tx_total_len;
	p.पूर्णांकerruptibility	= पूर्णांकerruptibility;
	p.kernel		= true;

	स_रखो(&cp, 0, माप(cp));
	cp.local		= rx->local;
	cp.key			= key;
	cp.security_level	= rx->min_sec_level;
	cp.exclusive		= false;
	cp.upgrade		= upgrade;
	cp.service_id		= srx->srx_service;
	call = rxrpc_new_client_call(rx, &cp, srx, &p, gfp, debug_id);
	/* The socket has been unlocked. */
	अगर (!IS_ERR(call)) अणु
		call->notअगरy_rx = notअगरy_rx;
		mutex_unlock(&call->user_mutex);
	पूर्ण

	rxrpc_put_peer(cp.peer);
	_leave(" = %p", call);
	वापस call;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_begin_call);

/*
 * Dummy function used to stop the notअगरier talking to recvmsg().
 */
अटल व्योम rxrpc_dummy_notअगरy_rx(काष्ठा sock *sk, काष्ठा rxrpc_call *rxcall,
				  अचिन्हित दीर्घ call_user_ID)
अणु
पूर्ण

/**
 * rxrpc_kernel_end_call - Allow a kernel service to end a call it was using
 * @sock: The socket the call is on
 * @call: The call to end
 *
 * Allow a kernel service to end a call it was using.  The call must be
 * complete beक्रमe this is called (the call should be पातed अगर necessary).
 */
व्योम rxrpc_kernel_end_call(काष्ठा socket *sock, काष्ठा rxrpc_call *call)
अणु
	_enter("%d{%d}", call->debug_id, atomic_पढ़ो(&call->usage));

	mutex_lock(&call->user_mutex);
	rxrpc_release_call(rxrpc_sk(sock->sk), call);

	/* Make sure we're not going to call back पूर्णांकo a kernel service */
	अगर (call->notअगरy_rx) अणु
		spin_lock_bh(&call->notअगरy_lock);
		call->notअगरy_rx = rxrpc_dummy_notअगरy_rx;
		spin_unlock_bh(&call->notअगरy_lock);
	पूर्ण

	mutex_unlock(&call->user_mutex);
	rxrpc_put_call(call, rxrpc_call_put_kernel);
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_end_call);

/**
 * rxrpc_kernel_check_lअगरe - Check to see whether a call is still alive
 * @sock: The socket the call is on
 * @call: The call to check
 *
 * Allow a kernel service to find out whether a call is still alive -
 * ie. whether it has completed.
 */
bool rxrpc_kernel_check_lअगरe(स्थिर काष्ठा socket *sock,
			     स्थिर काष्ठा rxrpc_call *call)
अणु
	वापस call->state != RXRPC_CALL_COMPLETE;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_check_lअगरe);

/**
 * rxrpc_kernel_get_epoch - Retrieve the epoch value from a call.
 * @sock: The socket the call is on
 * @call: The call to query
 *
 * Allow a kernel service to retrieve the epoch value from a service call to
 * see अगर the client at the other end rebooted.
 */
u32 rxrpc_kernel_get_epoch(काष्ठा socket *sock, काष्ठा rxrpc_call *call)
अणु
	वापस call->conn->proto.epoch;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_get_epoch);

/**
 * rxrpc_kernel_new_call_notअगरication - Get notअगरications of new calls
 * @sock: The socket to पूर्णांकercept received messages on
 * @notअगरy_new_call: Function to be called when new calls appear
 * @discard_new_call: Function to discard pपुनः_स्मृतिated calls
 *
 * Allow a kernel service to be given notअगरications about new calls.
 */
व्योम rxrpc_kernel_new_call_notअगरication(
	काष्ठा socket *sock,
	rxrpc_notअगरy_new_call_t notअगरy_new_call,
	rxrpc_discard_new_call_t discard_new_call)
अणु
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sock->sk);

	rx->notअगरy_new_call = notअगरy_new_call;
	rx->discard_new_call = discard_new_call;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_new_call_notअगरication);

/**
 * rxrpc_kernel_set_max_lअगरe - Set maximum lअगरespan on a call
 * @sock: The socket the call is on
 * @call: The call to configure
 * @hard_समयout: The maximum lअगरespan of the call in jअगरfies
 *
 * Set the maximum lअगरespan of a call.  The call will end with ETIME or
 * ETIMEDOUT अगर it takes दीर्घer than this.
 */
व्योम rxrpc_kernel_set_max_lअगरe(काष्ठा socket *sock, काष्ठा rxrpc_call *call,
			       अचिन्हित दीर्घ hard_समयout)
अणु
	अचिन्हित दीर्घ now;

	mutex_lock(&call->user_mutex);

	now = jअगरfies;
	hard_समयout += now;
	WRITE_ONCE(call->expect_term_by, hard_समयout);
	rxrpc_reduce_call_समयr(call, hard_समयout, now, rxrpc_समयr_set_क्रम_hard);

	mutex_unlock(&call->user_mutex);
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_set_max_lअगरe);

/*
 * connect an RxRPC socket
 * - this just tarमाला_लो it at a specअगरic destination; no actual connection
 *   negotiation takes place
 */
अटल पूर्णांक rxrpc_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			 पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sockaddr_rxrpc *srx = (काष्ठा sockaddr_rxrpc *)addr;
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sock->sk);
	पूर्णांक ret;

	_enter("%p,%p,%d,%d", rx, addr, addr_len, flags);

	ret = rxrpc_validate_address(rx, srx, addr_len);
	अगर (ret < 0) अणु
		_leave(" = %d [bad addr]", ret);
		वापस ret;
	पूर्ण

	lock_sock(&rx->sk);

	ret = -EISCONN;
	अगर (test_bit(RXRPC_SOCK_CONNECTED, &rx->flags))
		जाओ error;

	चयन (rx->sk.sk_state) अणु
	हाल RXRPC_UNBOUND:
		rx->sk.sk_state = RXRPC_CLIENT_UNBOUND;
	हाल RXRPC_CLIENT_UNBOUND:
	हाल RXRPC_CLIENT_BOUND:
		अवरोध;
	शेष:
		ret = -EBUSY;
		जाओ error;
	पूर्ण

	rx->connect_srx = *srx;
	set_bit(RXRPC_SOCK_CONNECTED, &rx->flags);
	ret = 0;

error:
	release_sock(&rx->sk);
	वापस ret;
पूर्ण

/*
 * send a message through an RxRPC socket
 * - in a client this करोes a number of things:
 *   - finds/sets up a connection क्रम the security specअगरied (अगर any)
 *   - initiates a call (ID in control data)
 *   - ends the request phase of a call (अगर MSG_MORE is not set)
 *   - sends a call data packet
 *   - may send an पात (पात code in control data)
 */
अटल पूर्णांक rxrpc_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *m, माप_प्रकार len)
अणु
	काष्ठा rxrpc_local *local;
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sock->sk);
	पूर्णांक ret;

	_enter(",{%d},,%zu", rx->sk.sk_state, len);

	अगर (m->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	अगर (m->msg_name) अणु
		ret = rxrpc_validate_address(rx, m->msg_name, m->msg_namelen);
		अगर (ret < 0) अणु
			_leave(" = %d [bad addr]", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	lock_sock(&rx->sk);

	चयन (rx->sk.sk_state) अणु
	हाल RXRPC_UNBOUND:
	हाल RXRPC_CLIENT_UNBOUND:
		rx->srx.srx_family = AF_RXRPC;
		rx->srx.srx_service = 0;
		rx->srx.transport_type = SOCK_DGRAM;
		rx->srx.transport.family = rx->family;
		चयन (rx->family) अणु
		हाल AF_INET:
			rx->srx.transport_len = माप(काष्ठा sockaddr_in);
			अवरोध;
#अगर_घोषित CONFIG_AF_RXRPC_IPV6
		हाल AF_INET6:
			rx->srx.transport_len = माप(काष्ठा sockaddr_in6);
			अवरोध;
#पूर्ण_अगर
		शेष:
			ret = -EAFNOSUPPORT;
			जाओ error_unlock;
		पूर्ण
		local = rxrpc_lookup_local(sock_net(sock->sk), &rx->srx);
		अगर (IS_ERR(local)) अणु
			ret = PTR_ERR(local);
			जाओ error_unlock;
		पूर्ण

		rx->local = local;
		rx->sk.sk_state = RXRPC_CLIENT_BOUND;
		fallthrough;

	हाल RXRPC_CLIENT_BOUND:
		अगर (!m->msg_name &&
		    test_bit(RXRPC_SOCK_CONNECTED, &rx->flags)) अणु
			m->msg_name = &rx->connect_srx;
			m->msg_namelen = माप(rx->connect_srx);
		पूर्ण
		fallthrough;
	हाल RXRPC_SERVER_BOUND:
	हाल RXRPC_SERVER_LISTENING:
		ret = rxrpc_करो_sendmsg(rx, m, len);
		/* The socket has been unlocked */
		जाओ out;
	शेष:
		ret = -EINVAL;
		जाओ error_unlock;
	पूर्ण

error_unlock:
	release_sock(&rx->sk);
out:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

पूर्णांक rxrpc_sock_set_min_security_level(काष्ठा sock *sk, अचिन्हित पूर्णांक val)
अणु
	अगर (sk->sk_state != RXRPC_UNBOUND)
		वापस -EISCONN;
	अगर (val > RXRPC_SECURITY_MAX)
		वापस -EINVAL;
	lock_sock(sk);
	rxrpc_sk(sk)->min_sec_level = val;
	release_sock(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rxrpc_sock_set_min_security_level);

/*
 * set RxRPC socket options
 */
अटल पूर्णांक rxrpc_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			    sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sock->sk);
	अचिन्हित पूर्णांक min_sec_level;
	u16 service_upgrade[2];
	पूर्णांक ret;

	_enter(",%d,%d,,%d", level, optname, optlen);

	lock_sock(&rx->sk);
	ret = -EOPNOTSUPP;

	अगर (level == SOL_RXRPC) अणु
		चयन (optname) अणु
		हाल RXRPC_EXCLUSIVE_CONNECTION:
			ret = -EINVAL;
			अगर (optlen != 0)
				जाओ error;
			ret = -EISCONN;
			अगर (rx->sk.sk_state != RXRPC_UNBOUND)
				जाओ error;
			rx->exclusive = true;
			जाओ success;

		हाल RXRPC_SECURITY_KEY:
			ret = -EINVAL;
			अगर (rx->key)
				जाओ error;
			ret = -EISCONN;
			अगर (rx->sk.sk_state != RXRPC_UNBOUND)
				जाओ error;
			ret = rxrpc_request_key(rx, optval, optlen);
			जाओ error;

		हाल RXRPC_SECURITY_KEYRING:
			ret = -EINVAL;
			अगर (rx->key)
				जाओ error;
			ret = -EISCONN;
			अगर (rx->sk.sk_state != RXRPC_UNBOUND)
				जाओ error;
			ret = rxrpc_server_keyring(rx, optval, optlen);
			जाओ error;

		हाल RXRPC_MIN_SECURITY_LEVEL:
			ret = -EINVAL;
			अगर (optlen != माप(अचिन्हित पूर्णांक))
				जाओ error;
			ret = -EISCONN;
			अगर (rx->sk.sk_state != RXRPC_UNBOUND)
				जाओ error;
			ret = copy_from_sockptr(&min_sec_level, optval,
				       माप(अचिन्हित पूर्णांक));
			अगर (ret < 0)
				जाओ error;
			ret = -EINVAL;
			अगर (min_sec_level > RXRPC_SECURITY_MAX)
				जाओ error;
			rx->min_sec_level = min_sec_level;
			जाओ success;

		हाल RXRPC_UPGRADEABLE_SERVICE:
			ret = -EINVAL;
			अगर (optlen != माप(service_upgrade) ||
			    rx->service_upgrade.from != 0)
				जाओ error;
			ret = -EISCONN;
			अगर (rx->sk.sk_state != RXRPC_SERVER_BOUND2)
				जाओ error;
			ret = -EFAULT;
			अगर (copy_from_sockptr(service_upgrade, optval,
					   माप(service_upgrade)) != 0)
				जाओ error;
			ret = -EINVAL;
			अगर ((service_upgrade[0] != rx->srx.srx_service ||
			     service_upgrade[1] != rx->second_service) &&
			    (service_upgrade[0] != rx->second_service ||
			     service_upgrade[1] != rx->srx.srx_service))
				जाओ error;
			rx->service_upgrade.from = service_upgrade[0];
			rx->service_upgrade.to = service_upgrade[1];
			जाओ success;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

success:
	ret = 0;
error:
	release_sock(&rx->sk);
	वापस ret;
पूर्ण

/*
 * Get socket options.
 */
अटल पूर्णांक rxrpc_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			    अक्षर __user *optval, पूर्णांक __user *_optlen)
अणु
	पूर्णांक optlen;

	अगर (level != SOL_RXRPC)
		वापस -EOPNOTSUPP;

	अगर (get_user(optlen, _optlen))
		वापस -EFAULT;

	चयन (optname) अणु
	हाल RXRPC_SUPPORTED_CMSG:
		अगर (optlen < माप(पूर्णांक))
			वापस -ETOOSMALL;
		अगर (put_user(RXRPC__SUPPORTED - 1, (पूर्णांक __user *)optval) ||
		    put_user(माप(पूर्णांक), _optlen))
			वापस -EFAULT;
		वापस 0;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/*
 * permit an RxRPC socket to be polled
 */
अटल __poll_t rxrpc_poll(काष्ठा file *file, काष्ठा socket *sock,
			       poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sk);
	__poll_t mask;

	sock_poll_रुको(file, sock, रुको);
	mask = 0;

	/* the socket is पढ़ोable अगर there are any messages रुकोing on the Rx
	 * queue */
	अगर (!list_empty(&rx->recvmsg_q))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* the socket is writable अगर there is space to add new data to the
	 * socket; there is no guarantee that any particular call in progress
	 * on the socket may have space in the Tx ACK winकरोw */
	अगर (rxrpc_writable(sk))
		mask |= EPOLLOUT | EPOLLWRNORM;

	वापस mask;
पूर्ण

/*
 * create an RxRPC socket
 */
अटल पूर्णांक rxrpc_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			पूर्णांक kern)
अणु
	काष्ठा rxrpc_net *rxnet;
	काष्ठा rxrpc_sock *rx;
	काष्ठा sock *sk;

	_enter("%p,%d", sock, protocol);

	/* we support transport protocol UDP/UDP6 only */
	अगर (protocol != PF_INET &&
	    IS_ENABLED(CONFIG_AF_RXRPC_IPV6) && protocol != PF_INET6)
		वापस -EPROTONOSUPPORT;

	अगर (sock->type != SOCK_DGRAM)
		वापस -ESOCKTNOSUPPORT;

	sock->ops = &rxrpc_rpc_ops;
	sock->state = SS_UNCONNECTED;

	sk = sk_alloc(net, PF_RXRPC, GFP_KERNEL, &rxrpc_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sock_init_data(sock, sk);
	sock_set_flag(sk, SOCK_RCU_FREE);
	sk->sk_state		= RXRPC_UNBOUND;
	sk->sk_ग_लिखो_space	= rxrpc_ग_लिखो_space;
	sk->sk_max_ack_backlog	= 0;
	sk->sk_deकाष्ठा		= rxrpc_sock_deकाष्ठाor;

	rx = rxrpc_sk(sk);
	rx->family = protocol;
	rx->calls = RB_ROOT;

	spin_lock_init(&rx->incoming_lock);
	INIT_LIST_HEAD(&rx->sock_calls);
	INIT_LIST_HEAD(&rx->to_be_accepted);
	INIT_LIST_HEAD(&rx->recvmsg_q);
	rwlock_init(&rx->recvmsg_lock);
	rwlock_init(&rx->call_lock);
	स_रखो(&rx->srx, 0, माप(rx->srx));

	rxnet = rxrpc_net(sock_net(&rx->sk));
	समयr_reduce(&rxnet->peer_keepalive_समयr, jअगरfies + 1);

	_leave(" = 0 [%p]", rx);
	वापस 0;
पूर्ण

/*
 * Kill all the calls on a socket and shut it करोwn.
 */
अटल पूर्णांक rxrpc_shutकरोwn(काष्ठा socket *sock, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sk);
	पूर्णांक ret = 0;

	_enter("%p,%d", sk, flags);

	अगर (flags != SHUT_RDWR)
		वापस -EOPNOTSUPP;
	अगर (sk->sk_state == RXRPC_CLOSE)
		वापस -ESHUTDOWN;

	lock_sock(sk);

	spin_lock_bh(&sk->sk_receive_queue.lock);
	अगर (sk->sk_state < RXRPC_CLOSE) अणु
		sk->sk_state = RXRPC_CLOSE;
		sk->sk_shutकरोwn = SHUTDOWN_MASK;
	पूर्ण अन्यथा अणु
		ret = -ESHUTDOWN;
	पूर्ण
	spin_unlock_bh(&sk->sk_receive_queue.lock);

	rxrpc_discard_pपुनः_स्मृति(rx);

	release_sock(sk);
	वापस ret;
पूर्ण

/*
 * RxRPC socket deकाष्ठाor
 */
अटल व्योम rxrpc_sock_deकाष्ठाor(काष्ठा sock *sk)
अणु
	_enter("%p", sk);

	rxrpc_purge_queue(&sk->sk_receive_queue);

	WARN_ON(refcount_पढ़ो(&sk->sk_wmem_alloc));
	WARN_ON(!sk_unhashed(sk));
	WARN_ON(sk->sk_socket);

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		prपूर्णांकk("Attempt to release alive rxrpc socket: %p\n", sk);
		वापस;
	पूर्ण
पूर्ण

/*
 * release an RxRPC socket
 */
अटल पूर्णांक rxrpc_release_sock(काष्ठा sock *sk)
अणु
	काष्ठा rxrpc_sock *rx = rxrpc_sk(sk);

	_enter("%p{%d,%d}", sk, sk->sk_state, refcount_पढ़ो(&sk->sk_refcnt));

	/* declare the socket बंदd क्रम business */
	sock_orphan(sk);
	sk->sk_shutकरोwn = SHUTDOWN_MASK;

	/* We want to समाप्त off all connections from a service socket
	 * as fast as possible because we can't share these; client
	 * sockets, on the other hand, can share an endpoपूर्णांक.
	 */
	चयन (sk->sk_state) अणु
	हाल RXRPC_SERVER_BOUND:
	हाल RXRPC_SERVER_BOUND2:
	हाल RXRPC_SERVER_LISTENING:
	हाल RXRPC_SERVER_LISTEN_DISABLED:
		rx->local->service_बंदd = true;
		अवरोध;
	पूर्ण

	spin_lock_bh(&sk->sk_receive_queue.lock);
	sk->sk_state = RXRPC_CLOSE;
	spin_unlock_bh(&sk->sk_receive_queue.lock);

	अगर (rx->local && rcu_access_poपूर्णांकer(rx->local->service) == rx) अणु
		ग_लिखो_lock(&rx->local->services_lock);
		rcu_assign_poपूर्णांकer(rx->local->service, शून्य);
		ग_लिखो_unlock(&rx->local->services_lock);
	पूर्ण

	/* try to flush out this socket */
	rxrpc_discard_pपुनः_स्मृति(rx);
	rxrpc_release_calls_on_socket(rx);
	flush_workqueue(rxrpc_workqueue);
	rxrpc_purge_queue(&sk->sk_receive_queue);

	rxrpc_unuse_local(rx->local);
	rxrpc_put_local(rx->local);
	rx->local = शून्य;
	key_put(rx->key);
	rx->key = शून्य;
	key_put(rx->securities);
	rx->securities = शून्य;
	sock_put(sk);

	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * release an RxRPC BSD socket on बंद() or equivalent
 */
अटल पूर्णांक rxrpc_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	_enter("%p{%p}", sock, sk);

	अगर (!sk)
		वापस 0;

	sock->sk = शून्य;

	वापस rxrpc_release_sock(sk);
पूर्ण

/*
 * RxRPC network protocol
 */
अटल स्थिर काष्ठा proto_ops rxrpc_rpc_ops = अणु
	.family		= PF_RXRPC,
	.owner		= THIS_MODULE,
	.release	= rxrpc_release,
	.bind		= rxrpc_bind,
	.connect	= rxrpc_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.getname	= sock_no_getname,
	.poll		= rxrpc_poll,
	.ioctl		= sock_no_ioctl,
	.listen		= rxrpc_listen,
	.shutकरोwn	= rxrpc_shutकरोwn,
	.setsockopt	= rxrpc_setsockopt,
	.माला_लोockopt	= rxrpc_माला_लोockopt,
	.sendmsg	= rxrpc_sendmsg,
	.recvmsg	= rxrpc_recvmsg,
	.mmap		= sock_no_mmap,
	.sendpage	= sock_no_sendpage,
पूर्ण;

अटल काष्ठा proto rxrpc_proto = अणु
	.name		= "RXRPC",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा rxrpc_sock),
	.max_header	= माप(काष्ठा rxrpc_wire_header),
पूर्ण;

अटल स्थिर काष्ठा net_proto_family rxrpc_family_ops = अणु
	.family	= PF_RXRPC,
	.create = rxrpc_create,
	.owner	= THIS_MODULE,
पूर्ण;

/*
 * initialise and रेजिस्टर the RxRPC protocol
 */
अटल पूर्णांक __init af_rxrpc_init(व्योम)
अणु
	पूर्णांक ret = -1;
	अचिन्हित पूर्णांक पंचांगp;

	BUILD_BUG_ON(माप(काष्ठा rxrpc_skb_priv) > माप_field(काष्ठा sk_buff, cb));

	get_अक्रमom_bytes(&पंचांगp, माप(पंचांगp));
	पंचांगp &= 0x3fffffff;
	अगर (पंचांगp == 0)
		पंचांगp = 1;
	idr_set_cursor(&rxrpc_client_conn_ids, पंचांगp);

	ret = -ENOMEM;
	rxrpc_call_jar = kmem_cache_create(
		"rxrpc_call_jar", माप(काष्ठा rxrpc_call), 0,
		SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!rxrpc_call_jar) अणु
		pr_notice("Failed to allocate call jar\n");
		जाओ error_call_jar;
	पूर्ण

	rxrpc_workqueue = alloc_workqueue("krxrpcd", 0, 1);
	अगर (!rxrpc_workqueue) अणु
		pr_notice("Failed to allocate work queue\n");
		जाओ error_work_queue;
	पूर्ण

	ret = rxrpc_init_security();
	अगर (ret < 0) अणु
		pr_crit("Cannot initialise security\n");
		जाओ error_security;
	पूर्ण

	ret = रेजिस्टर_pernet_device(&rxrpc_net_ops);
	अगर (ret)
		जाओ error_pernet;

	ret = proto_रेजिस्टर(&rxrpc_proto, 1);
	अगर (ret < 0) अणु
		pr_crit("Cannot register protocol\n");
		जाओ error_proto;
	पूर्ण

	ret = sock_रेजिस्टर(&rxrpc_family_ops);
	अगर (ret < 0) अणु
		pr_crit("Cannot register socket family\n");
		जाओ error_sock;
	पूर्ण

	ret = रेजिस्टर_key_type(&key_type_rxrpc);
	अगर (ret < 0) अणु
		pr_crit("Cannot register client key type\n");
		जाओ error_key_type;
	पूर्ण

	ret = रेजिस्टर_key_type(&key_type_rxrpc_s);
	अगर (ret < 0) अणु
		pr_crit("Cannot register server key type\n");
		जाओ error_key_type_s;
	पूर्ण

	ret = rxrpc_sysctl_init();
	अगर (ret < 0) अणु
		pr_crit("Cannot register sysctls\n");
		जाओ error_sysctls;
	पूर्ण

	वापस 0;

error_sysctls:
	unरेजिस्टर_key_type(&key_type_rxrpc_s);
error_key_type_s:
	unरेजिस्टर_key_type(&key_type_rxrpc);
error_key_type:
	sock_unरेजिस्टर(PF_RXRPC);
error_sock:
	proto_unरेजिस्टर(&rxrpc_proto);
error_proto:
	unरेजिस्टर_pernet_device(&rxrpc_net_ops);
error_pernet:
	rxrpc_निकास_security();
error_security:
	destroy_workqueue(rxrpc_workqueue);
error_work_queue:
	kmem_cache_destroy(rxrpc_call_jar);
error_call_jar:
	वापस ret;
पूर्ण

/*
 * unरेजिस्टर the RxRPC protocol
 */
अटल व्योम __निकास af_rxrpc_निकास(व्योम)
अणु
	_enter("");
	rxrpc_sysctl_निकास();
	unरेजिस्टर_key_type(&key_type_rxrpc_s);
	unरेजिस्टर_key_type(&key_type_rxrpc);
	sock_unरेजिस्टर(PF_RXRPC);
	proto_unरेजिस्टर(&rxrpc_proto);
	unरेजिस्टर_pernet_device(&rxrpc_net_ops);
	ASSERTCMP(atomic_पढ़ो(&rxrpc_n_tx_skbs), ==, 0);
	ASSERTCMP(atomic_पढ़ो(&rxrpc_n_rx_skbs), ==, 0);

	/* Make sure the local and peer records pinned by any dying connections
	 * are released.
	 */
	rcu_barrier();
	rxrpc_destroy_client_conn_ids();

	destroy_workqueue(rxrpc_workqueue);
	rxrpc_निकास_security();
	kmem_cache_destroy(rxrpc_call_jar);
	_leave("");
पूर्ण

module_init(af_rxrpc_init);
module_निकास(af_rxrpc_निकास);
