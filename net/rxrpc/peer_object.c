<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RxRPC remote transport endpoपूर्णांक record management
 *
 * Copyright (C) 2007, 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/udp.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/slab.h>
#समावेश <linux/hashtable.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/ip6_route.h>
#समावेश "ar-internal.h"

/*
 * Hash a peer key.
 */
अटल अचिन्हित दीर्घ rxrpc_peer_hash_key(काष्ठा rxrpc_local *local,
					 स्थिर काष्ठा sockaddr_rxrpc *srx)
अणु
	स्थिर u16 *p;
	अचिन्हित पूर्णांक i, size;
	अचिन्हित दीर्घ hash_key;

	_enter("");

	hash_key = (अचिन्हित दीर्घ)local / __alignof__(*local);
	hash_key += srx->transport_type;
	hash_key += srx->transport_len;
	hash_key += srx->transport.family;

	चयन (srx->transport.family) अणु
	हाल AF_INET:
		hash_key += (u16 __क्रमce)srx->transport.sin.sin_port;
		size = माप(srx->transport.sin.sin_addr);
		p = (u16 *)&srx->transport.sin.sin_addr;
		अवरोध;
#अगर_घोषित CONFIG_AF_RXRPC_IPV6
	हाल AF_INET6:
		hash_key += (u16 __क्रमce)srx->transport.sin.sin_port;
		size = माप(srx->transport.sin6.sin6_addr);
		p = (u16 *)&srx->transport.sin6.sin6_addr;
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN(1, "AF_RXRPC: Unsupported transport address family\n");
		वापस 0;
	पूर्ण

	/* Step through the peer address in 16-bit portions क्रम speed */
	क्रम (i = 0; i < size; i += माप(*p), p++)
		hash_key += *p;

	_leave(" 0x%lx", hash_key);
	वापस hash_key;
पूर्ण

/*
 * Compare a peer to a key.  Return -ve, 0 or +ve to indicate less than, same
 * or greater than.
 *
 * Unक्रमtunately, the primitives in linux/hashtable.h करोn't allow क्रम sorted
 * buckets and mid-bucket insertion, so we करोn't make full use of this
 * inक्रमmation at this poपूर्णांक.
 */
अटल दीर्घ rxrpc_peer_cmp_key(स्थिर काष्ठा rxrpc_peer *peer,
			       काष्ठा rxrpc_local *local,
			       स्थिर काष्ठा sockaddr_rxrpc *srx,
			       अचिन्हित दीर्घ hash_key)
अणु
	दीर्घ dअगरf;

	dअगरf = ((peer->hash_key - hash_key) ?:
		((अचिन्हित दीर्घ)peer->local - (अचिन्हित दीर्घ)local) ?:
		(peer->srx.transport_type - srx->transport_type) ?:
		(peer->srx.transport_len - srx->transport_len) ?:
		(peer->srx.transport.family - srx->transport.family));
	अगर (dअगरf != 0)
		वापस dअगरf;

	चयन (srx->transport.family) अणु
	हाल AF_INET:
		वापस ((u16 __क्रमce)peer->srx.transport.sin.sin_port -
			(u16 __क्रमce)srx->transport.sin.sin_port) ?:
			स_भेद(&peer->srx.transport.sin.sin_addr,
			       &srx->transport.sin.sin_addr,
			       माप(काष्ठा in_addr));
#अगर_घोषित CONFIG_AF_RXRPC_IPV6
	हाल AF_INET6:
		वापस ((u16 __क्रमce)peer->srx.transport.sin6.sin6_port -
			(u16 __क्रमce)srx->transport.sin6.sin6_port) ?:
			स_भेद(&peer->srx.transport.sin6.sin6_addr,
			       &srx->transport.sin6.sin6_addr,
			       माप(काष्ठा in6_addr));
#पूर्ण_अगर
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Look up a remote transport endpoपूर्णांक क्रम the specअगरied address using RCU.
 */
अटल काष्ठा rxrpc_peer *__rxrpc_lookup_peer_rcu(
	काष्ठा rxrpc_local *local,
	स्थिर काष्ठा sockaddr_rxrpc *srx,
	अचिन्हित दीर्घ hash_key)
अणु
	काष्ठा rxrpc_peer *peer;
	काष्ठा rxrpc_net *rxnet = local->rxnet;

	hash_क्रम_each_possible_rcu(rxnet->peer_hash, peer, hash_link, hash_key) अणु
		अगर (rxrpc_peer_cmp_key(peer, local, srx, hash_key) == 0 &&
		    atomic_पढ़ो(&peer->usage) > 0)
			वापस peer;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Look up a remote transport endpoपूर्णांक क्रम the specअगरied address using RCU.
 */
काष्ठा rxrpc_peer *rxrpc_lookup_peer_rcu(काष्ठा rxrpc_local *local,
					 स्थिर काष्ठा sockaddr_rxrpc *srx)
अणु
	काष्ठा rxrpc_peer *peer;
	अचिन्हित दीर्घ hash_key = rxrpc_peer_hash_key(local, srx);

	peer = __rxrpc_lookup_peer_rcu(local, srx, hash_key);
	अगर (peer) अणु
		_net("PEER %d {%pISp}", peer->debug_id, &peer->srx.transport);
		_leave(" = %p {u=%d}", peer, atomic_पढ़ो(&peer->usage));
	पूर्ण
	वापस peer;
पूर्ण

/*
 * assess the MTU size क्रम the network पूर्णांकerface through which this peer is
 * reached
 */
अटल व्योम rxrpc_assess_MTU_size(काष्ठा rxrpc_sock *rx,
				  काष्ठा rxrpc_peer *peer)
अणु
	काष्ठा net *net = sock_net(&rx->sk);
	काष्ठा dst_entry *dst;
	काष्ठा rtable *rt;
	काष्ठा flowi fl;
	काष्ठा flowi4 *fl4 = &fl.u.ip4;
#अगर_घोषित CONFIG_AF_RXRPC_IPV6
	काष्ठा flowi6 *fl6 = &fl.u.ip6;
#पूर्ण_अगर

	peer->अगर_mtu = 1500;

	स_रखो(&fl, 0, माप(fl));
	चयन (peer->srx.transport.family) अणु
	हाल AF_INET:
		rt = ip_route_output_ports(
			net, fl4, शून्य,
			peer->srx.transport.sin.sin_addr.s_addr, 0,
			htons(7000), htons(7001), IPPROTO_UDP, 0, 0);
		अगर (IS_ERR(rt)) अणु
			_leave(" [route err %ld]", PTR_ERR(rt));
			वापस;
		पूर्ण
		dst = &rt->dst;
		अवरोध;

#अगर_घोषित CONFIG_AF_RXRPC_IPV6
	हाल AF_INET6:
		fl6->flowi6_iअगर = LOOPBACK_IFINDEX;
		fl6->flowi6_scope = RT_SCOPE_UNIVERSE;
		fl6->flowi6_proto = IPPROTO_UDP;
		स_नकल(&fl6->daddr, &peer->srx.transport.sin6.sin6_addr,
		       माप(काष्ठा in6_addr));
		fl6->fl6_dport = htons(7001);
		fl6->fl6_sport = htons(7000);
		dst = ip6_route_output(net, शून्य, fl6);
		अगर (dst->error) अणु
			_leave(" [route err %d]", dst->error);
			वापस;
		पूर्ण
		अवरोध;
#पूर्ण_अगर

	शेष:
		BUG();
	पूर्ण

	peer->अगर_mtu = dst_mtu(dst);
	dst_release(dst);

	_leave(" [if_mtu %u]", peer->अगर_mtu);
पूर्ण

/*
 * Allocate a peer.
 */
काष्ठा rxrpc_peer *rxrpc_alloc_peer(काष्ठा rxrpc_local *local, gfp_t gfp)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	काष्ठा rxrpc_peer *peer;

	_enter("");

	peer = kzalloc(माप(काष्ठा rxrpc_peer), gfp);
	अगर (peer) अणु
		atomic_set(&peer->usage, 1);
		peer->local = rxrpc_get_local(local);
		INIT_HLIST_HEAD(&peer->error_tarमाला_लो);
		peer->service_conns = RB_ROOT;
		seqlock_init(&peer->service_conn_lock);
		spin_lock_init(&peer->lock);
		spin_lock_init(&peer->rtt_input_lock);
		peer->debug_id = atomic_inc_वापस(&rxrpc_debug_id);

		rxrpc_peer_init_rtt(peer);

		अगर (RXRPC_TX_SMSS > 2190)
			peer->cong_cwnd = 2;
		अन्यथा अगर (RXRPC_TX_SMSS > 1095)
			peer->cong_cwnd = 3;
		अन्यथा
			peer->cong_cwnd = 4;
		trace_rxrpc_peer(peer->debug_id, rxrpc_peer_new, 1, here);
	पूर्ण

	_leave(" = %p", peer);
	वापस peer;
पूर्ण

/*
 * Initialise peer record.
 */
अटल व्योम rxrpc_init_peer(काष्ठा rxrpc_sock *rx, काष्ठा rxrpc_peer *peer,
			    अचिन्हित दीर्घ hash_key)
अणु
	peer->hash_key = hash_key;
	rxrpc_assess_MTU_size(rx, peer);
	peer->mtu = peer->अगर_mtu;
	peer->rtt_last_req = kसमय_get_real();

	चयन (peer->srx.transport.family) अणु
	हाल AF_INET:
		peer->hdrsize = माप(काष्ठा iphdr);
		अवरोध;
#अगर_घोषित CONFIG_AF_RXRPC_IPV6
	हाल AF_INET6:
		peer->hdrsize = माप(काष्ठा ipv6hdr);
		अवरोध;
#पूर्ण_अगर
	शेष:
		BUG();
	पूर्ण

	चयन (peer->srx.transport_type) अणु
	हाल SOCK_DGRAM:
		peer->hdrsize += माप(काष्ठा udphdr);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	peer->hdrsize += माप(काष्ठा rxrpc_wire_header);
	peer->maxdata = peer->mtu - peer->hdrsize;
पूर्ण

/*
 * Set up a new peer.
 */
अटल काष्ठा rxrpc_peer *rxrpc_create_peer(काष्ठा rxrpc_sock *rx,
					    काष्ठा rxrpc_local *local,
					    काष्ठा sockaddr_rxrpc *srx,
					    अचिन्हित दीर्घ hash_key,
					    gfp_t gfp)
अणु
	काष्ठा rxrpc_peer *peer;

	_enter("");

	peer = rxrpc_alloc_peer(local, gfp);
	अगर (peer) अणु
		स_नकल(&peer->srx, srx, माप(*srx));
		rxrpc_init_peer(rx, peer, hash_key);
	पूर्ण

	_leave(" = %p", peer);
	वापस peer;
पूर्ण

/*
 * Set up a new incoming peer.  There shouldn't be any other matching peers
 * since we've alपढ़ोy करोne a search in the list from the non-reentrant context
 * (the data_पढ़ोy handler) that is the only place we can add new peers.
 */
व्योम rxrpc_new_incoming_peer(काष्ठा rxrpc_sock *rx, काष्ठा rxrpc_local *local,
			     काष्ठा rxrpc_peer *peer)
अणु
	काष्ठा rxrpc_net *rxnet = local->rxnet;
	अचिन्हित दीर्घ hash_key;

	hash_key = rxrpc_peer_hash_key(local, &peer->srx);
	rxrpc_init_peer(rx, peer, hash_key);

	spin_lock(&rxnet->peer_hash_lock);
	hash_add_rcu(rxnet->peer_hash, &peer->hash_link, hash_key);
	list_add_tail(&peer->keepalive_link, &rxnet->peer_keepalive_new);
	spin_unlock(&rxnet->peer_hash_lock);
पूर्ण

/*
 * obtain a remote transport endpoपूर्णांक क्रम the specअगरied address
 */
काष्ठा rxrpc_peer *rxrpc_lookup_peer(काष्ठा rxrpc_sock *rx,
				     काष्ठा rxrpc_local *local,
				     काष्ठा sockaddr_rxrpc *srx, gfp_t gfp)
अणु
	काष्ठा rxrpc_peer *peer, *candidate;
	काष्ठा rxrpc_net *rxnet = local->rxnet;
	अचिन्हित दीर्घ hash_key = rxrpc_peer_hash_key(local, srx);

	_enter("{%pISp}", &srx->transport);

	/* search the peer list first */
	rcu_पढ़ो_lock();
	peer = __rxrpc_lookup_peer_rcu(local, srx, hash_key);
	अगर (peer && !rxrpc_get_peer_maybe(peer))
		peer = शून्य;
	rcu_पढ़ो_unlock();

	अगर (!peer) अणु
		/* The peer is not yet present in hash - create a candidate
		 * क्रम a new record and then reकरो the search.
		 */
		candidate = rxrpc_create_peer(rx, local, srx, hash_key, gfp);
		अगर (!candidate) अणु
			_leave(" = NULL [nomem]");
			वापस शून्य;
		पूर्ण

		spin_lock_bh(&rxnet->peer_hash_lock);

		/* Need to check that we aren't racing with someone अन्यथा */
		peer = __rxrpc_lookup_peer_rcu(local, srx, hash_key);
		अगर (peer && !rxrpc_get_peer_maybe(peer))
			peer = शून्य;
		अगर (!peer) अणु
			hash_add_rcu(rxnet->peer_hash,
				     &candidate->hash_link, hash_key);
			list_add_tail(&candidate->keepalive_link,
				      &rxnet->peer_keepalive_new);
		पूर्ण

		spin_unlock_bh(&rxnet->peer_hash_lock);

		अगर (peer)
			kमुक्त(candidate);
		अन्यथा
			peer = candidate;
	पूर्ण

	_net("PEER %d {%pISp}", peer->debug_id, &peer->srx.transport);

	_leave(" = %p {u=%d}", peer, atomic_पढ़ो(&peer->usage));
	वापस peer;
पूर्ण

/*
 * Get a ref on a peer record.
 */
काष्ठा rxrpc_peer *rxrpc_get_peer(काष्ठा rxrpc_peer *peer)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	पूर्णांक n;

	n = atomic_inc_वापस(&peer->usage);
	trace_rxrpc_peer(peer->debug_id, rxrpc_peer_got, n, here);
	वापस peer;
पूर्ण

/*
 * Get a ref on a peer record unless its usage has alपढ़ोy reached 0.
 */
काष्ठा rxrpc_peer *rxrpc_get_peer_maybe(काष्ठा rxrpc_peer *peer)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);

	अगर (peer) अणु
		पूर्णांक n = atomic_fetch_add_unless(&peer->usage, 1, 0);
		अगर (n > 0)
			trace_rxrpc_peer(peer->debug_id, rxrpc_peer_got, n + 1, here);
		अन्यथा
			peer = शून्य;
	पूर्ण
	वापस peer;
पूर्ण

/*
 * Discard a peer record.
 */
अटल व्योम __rxrpc_put_peer(काष्ठा rxrpc_peer *peer)
अणु
	काष्ठा rxrpc_net *rxnet = peer->local->rxnet;

	ASSERT(hlist_empty(&peer->error_tarमाला_लो));

	spin_lock_bh(&rxnet->peer_hash_lock);
	hash_del_rcu(&peer->hash_link);
	list_del_init(&peer->keepalive_link);
	spin_unlock_bh(&rxnet->peer_hash_lock);

	rxrpc_put_local(peer->local);
	kमुक्त_rcu(peer, rcu);
पूर्ण

/*
 * Drop a ref on a peer record.
 */
व्योम rxrpc_put_peer(काष्ठा rxrpc_peer *peer)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अचिन्हित पूर्णांक debug_id;
	पूर्णांक n;

	अगर (peer) अणु
		debug_id = peer->debug_id;
		n = atomic_dec_वापस(&peer->usage);
		trace_rxrpc_peer(debug_id, rxrpc_peer_put, n, here);
		अगर (n == 0)
			__rxrpc_put_peer(peer);
	पूर्ण
पूर्ण

/*
 * Drop a ref on a peer record where the caller alपढ़ोy holds the
 * peer_hash_lock.
 */
व्योम rxrpc_put_peer_locked(काष्ठा rxrpc_peer *peer)
अणु
	स्थिर व्योम *here = __builtin_वापस_address(0);
	अचिन्हित पूर्णांक debug_id = peer->debug_id;
	पूर्णांक n;

	n = atomic_dec_वापस(&peer->usage);
	trace_rxrpc_peer(debug_id, rxrpc_peer_put, n, here);
	अगर (n == 0) अणु
		hash_del_rcu(&peer->hash_link);
		list_del_init(&peer->keepalive_link);
		rxrpc_put_local(peer->local);
		kमुक्त_rcu(peer, rcu);
	पूर्ण
पूर्ण

/*
 * Make sure all peer records have been discarded.
 */
व्योम rxrpc_destroy_all_peers(काष्ठा rxrpc_net *rxnet)
अणु
	काष्ठा rxrpc_peer *peer;
	पूर्णांक i;

	क्रम (i = 0; i < HASH_SIZE(rxnet->peer_hash); i++) अणु
		अगर (hlist_empty(&rxnet->peer_hash[i]))
			जारी;

		hlist_क्रम_each_entry(peer, &rxnet->peer_hash[i], hash_link) अणु
			pr_err("Leaked peer %u {%u} %pISp\n",
			       peer->debug_id,
			       atomic_पढ़ो(&peer->usage),
			       &peer->srx.transport);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * rxrpc_kernel_get_peer - Get the peer address of a call
 * @sock: The socket on which the call is in progress.
 * @call: The call to query
 * @_srx: Where to place the result
 *
 * Get the address of the remote peer in a call.
 */
व्योम rxrpc_kernel_get_peer(काष्ठा socket *sock, काष्ठा rxrpc_call *call,
			   काष्ठा sockaddr_rxrpc *_srx)
अणु
	*_srx = call->peer->srx;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_get_peer);

/**
 * rxrpc_kernel_get_srtt - Get a call's peer smoothed RTT
 * @sock: The socket on which the call is in progress.
 * @call: The call to query
 * @_srtt: Where to store the SRTT value.
 *
 * Get the call's peer smoothed RTT in uS.
 */
bool rxrpc_kernel_get_srtt(काष्ठा socket *sock, काष्ठा rxrpc_call *call,
			   u32 *_srtt)
अणु
	काष्ठा rxrpc_peer *peer = call->peer;

	अगर (peer->rtt_count == 0) अणु
		*_srtt = 1000000; /* 1S */
		वापस false;
	पूर्ण

	*_srtt = call->peer->srtt_us >> 3;
	वापस true;
पूर्ण
EXPORT_SYMBOL(rxrpc_kernel_get_srtt);
