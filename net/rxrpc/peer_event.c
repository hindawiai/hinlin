<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Peer event handling, typically ICMP messages.
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/udp.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/icmp.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <net/ip.h>
#समावेश "ar-internal.h"

अटल व्योम rxrpc_store_error(काष्ठा rxrpc_peer *, काष्ठा sock_exterr_skb *);
अटल व्योम rxrpc_distribute_error(काष्ठा rxrpc_peer *, पूर्णांक,
				   क्रमागत rxrpc_call_completion);

/*
 * Find the peer associated with an ICMP packet.
 */
अटल काष्ठा rxrpc_peer *rxrpc_lookup_peer_icmp_rcu(काष्ठा rxrpc_local *local,
						     स्थिर काष्ठा sk_buff *skb,
						     काष्ठा sockaddr_rxrpc *srx)
अणु
	काष्ठा sock_exterr_skb *serr = SKB_EXT_ERR(skb);

	_enter("");

	स_रखो(srx, 0, माप(*srx));
	srx->transport_type = local->srx.transport_type;
	srx->transport_len = local->srx.transport_len;
	srx->transport.family = local->srx.transport.family;

	/* Can we see an ICMP4 packet on an ICMP6 listening socket?  and vice
	 * versa?
	 */
	चयन (srx->transport.family) अणु
	हाल AF_INET:
		srx->transport_len = माप(srx->transport.sin);
		srx->transport.family = AF_INET;
		srx->transport.sin.sin_port = serr->port;
		चयन (serr->ee.ee_origin) अणु
		हाल SO_EE_ORIGIN_ICMP:
			_net("Rx ICMP");
			स_नकल(&srx->transport.sin.sin_addr,
			       skb_network_header(skb) + serr->addr_offset,
			       माप(काष्ठा in_addr));
			अवरोध;
		हाल SO_EE_ORIGIN_ICMP6:
			_net("Rx ICMP6 on v4 sock");
			स_नकल(&srx->transport.sin.sin_addr,
			       skb_network_header(skb) + serr->addr_offset + 12,
			       माप(काष्ठा in_addr));
			अवरोध;
		शेष:
			स_नकल(&srx->transport.sin.sin_addr, &ip_hdr(skb)->saddr,
			       माप(काष्ठा in_addr));
			अवरोध;
		पूर्ण
		अवरोध;

#अगर_घोषित CONFIG_AF_RXRPC_IPV6
	हाल AF_INET6:
		चयन (serr->ee.ee_origin) अणु
		हाल SO_EE_ORIGIN_ICMP6:
			_net("Rx ICMP6");
			srx->transport.sin6.sin6_port = serr->port;
			स_नकल(&srx->transport.sin6.sin6_addr,
			       skb_network_header(skb) + serr->addr_offset,
			       माप(काष्ठा in6_addr));
			अवरोध;
		हाल SO_EE_ORIGIN_ICMP:
			_net("Rx ICMP on v6 sock");
			srx->transport_len = माप(srx->transport.sin);
			srx->transport.family = AF_INET;
			srx->transport.sin.sin_port = serr->port;
			स_नकल(&srx->transport.sin.sin_addr,
			       skb_network_header(skb) + serr->addr_offset,
			       माप(काष्ठा in_addr));
			अवरोध;
		शेष:
			स_नकल(&srx->transport.sin6.sin6_addr,
			       &ipv6_hdr(skb)->saddr,
			       माप(काष्ठा in6_addr));
			अवरोध;
		पूर्ण
		अवरोध;
#पूर्ण_अगर

	शेष:
		BUG();
	पूर्ण

	वापस rxrpc_lookup_peer_rcu(local, srx);
पूर्ण

/*
 * Handle an MTU/fragmentation problem.
 */
अटल व्योम rxrpc_adjust_mtu(काष्ठा rxrpc_peer *peer, काष्ठा sock_exterr_skb *serr)
अणु
	u32 mtu = serr->ee.ee_info;

	_net("Rx ICMP Fragmentation Needed (%d)", mtu);

	/* wind करोwn the local पूर्णांकerface MTU */
	अगर (mtu > 0 && peer->अगर_mtu == 65535 && mtu < peer->अगर_mtu) अणु
		peer->अगर_mtu = mtu;
		_net("I/F MTU %u", mtu);
	पूर्ण

	अगर (mtu == 0) अणु
		/* they didn't give us a size, estimate one */
		mtu = peer->अगर_mtu;
		अगर (mtu > 1500) अणु
			mtu >>= 1;
			अगर (mtu < 1500)
				mtu = 1500;
		पूर्ण अन्यथा अणु
			mtu -= 100;
			अगर (mtu < peer->hdrsize)
				mtu = peer->hdrsize + 4;
		पूर्ण
	पूर्ण

	अगर (mtu < peer->mtu) अणु
		spin_lock_bh(&peer->lock);
		peer->mtu = mtu;
		peer->maxdata = peer->mtu - peer->hdrsize;
		spin_unlock_bh(&peer->lock);
		_net("Net MTU %u (maxdata %u)",
		     peer->mtu, peer->maxdata);
	पूर्ण
पूर्ण

/*
 * Handle an error received on the local endpoपूर्णांक.
 */
व्योम rxrpc_error_report(काष्ठा sock *sk)
अणु
	काष्ठा sock_exterr_skb *serr;
	काष्ठा sockaddr_rxrpc srx;
	काष्ठा rxrpc_local *local;
	काष्ठा rxrpc_peer *peer;
	काष्ठा sk_buff *skb;

	rcu_पढ़ो_lock();
	local = rcu_dereference_sk_user_data(sk);
	अगर (unlikely(!local)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	_enter("%p{%d}", sk, local->debug_id);

	/* Clear the outstanding error value on the socket so that it करोesn't
	 * cause kernel_sendmsg() to वापस it later.
	 */
	sock_error(sk);

	skb = sock_dequeue_err_skb(sk);
	अगर (!skb) अणु
		rcu_पढ़ो_unlock();
		_leave("UDP socket errqueue empty");
		वापस;
	पूर्ण
	rxrpc_new_skb(skb, rxrpc_skb_received);
	serr = SKB_EXT_ERR(skb);
	अगर (!skb->len && serr->ee.ee_origin == SO_EE_ORIGIN_TIMESTAMPING) अणु
		_leave("UDP empty message");
		rcu_पढ़ो_unlock();
		rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
		वापस;
	पूर्ण

	peer = rxrpc_lookup_peer_icmp_rcu(local, skb, &srx);
	अगर (peer && !rxrpc_get_peer_maybe(peer))
		peer = शून्य;
	अगर (!peer) अणु
		rcu_पढ़ो_unlock();
		rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
		_leave(" [no peer]");
		वापस;
	पूर्ण

	trace_rxrpc_rx_icmp(peer, &serr->ee, &srx);

	अगर ((serr->ee.ee_origin == SO_EE_ORIGIN_ICMP &&
	     serr->ee.ee_type == ICMP_DEST_UNREACH &&
	     serr->ee.ee_code == ICMP_FRAG_NEEDED)) अणु
		rxrpc_adjust_mtu(peer, serr);
		rcu_पढ़ो_unlock();
		rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
		rxrpc_put_peer(peer);
		_leave(" [MTU update]");
		वापस;
	पूर्ण

	rxrpc_store_error(peer, serr);
	rcu_पढ़ो_unlock();
	rxrpc_मुक्त_skb(skb, rxrpc_skb_मुक्तd);
	rxrpc_put_peer(peer);

	_leave("");
पूर्ण

/*
 * Map an error report to error codes on the peer record.
 */
अटल व्योम rxrpc_store_error(काष्ठा rxrpc_peer *peer,
			      काष्ठा sock_exterr_skb *serr)
अणु
	क्रमागत rxrpc_call_completion compl = RXRPC_CALL_NETWORK_ERROR;
	काष्ठा sock_extended_err *ee;
	पूर्णांक err;

	_enter("");

	ee = &serr->ee;

	err = ee->ee_त्रुटि_सं;

	चयन (ee->ee_origin) अणु
	हाल SO_EE_ORIGIN_ICMP:
		चयन (ee->ee_type) अणु
		हाल ICMP_DEST_UNREACH:
			चयन (ee->ee_code) अणु
			हाल ICMP_NET_UNREACH:
				_net("Rx Received ICMP Network Unreachable");
				अवरोध;
			हाल ICMP_HOST_UNREACH:
				_net("Rx Received ICMP Host Unreachable");
				अवरोध;
			हाल ICMP_PORT_UNREACH:
				_net("Rx Received ICMP Port Unreachable");
				अवरोध;
			हाल ICMP_NET_UNKNOWN:
				_net("Rx Received ICMP Unknown Network");
				अवरोध;
			हाल ICMP_HOST_UNKNOWN:
				_net("Rx Received ICMP Unknown Host");
				अवरोध;
			शेष:
				_net("Rx Received ICMP DestUnreach code=%u",
				     ee->ee_code);
				अवरोध;
			पूर्ण
			अवरोध;

		हाल ICMP_TIME_EXCEEDED:
			_net("Rx Received ICMP TTL Exceeded");
			अवरोध;

		शेष:
			_proto("Rx Received ICMP error { type=%u code=%u }",
			       ee->ee_type, ee->ee_code);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SO_EE_ORIGIN_NONE:
	हाल SO_EE_ORIGIN_LOCAL:
		_proto("Rx Received local error { error=%d }", err);
		compl = RXRPC_CALL_LOCAL_ERROR;
		अवरोध;

	हाल SO_EE_ORIGIN_ICMP6:
		अगर (err == EACCES)
			err = EHOSTUNREACH;
		fallthrough;
	शेष:
		_proto("Rx Received error report { orig=%u }", ee->ee_origin);
		अवरोध;
	पूर्ण

	rxrpc_distribute_error(peer, err, compl);
पूर्ण

/*
 * Distribute an error that occurred on a peer.
 */
अटल व्योम rxrpc_distribute_error(काष्ठा rxrpc_peer *peer, पूर्णांक error,
				   क्रमागत rxrpc_call_completion compl)
अणु
	काष्ठा rxrpc_call *call;

	hlist_क्रम_each_entry_rcu(call, &peer->error_tarमाला_लो, error_link) अणु
		rxrpc_see_call(call);
		rxrpc_set_call_completion(call, compl, 0, -error);
	पूर्ण
पूर्ण

/*
 * Perक्रमm keep-alive pings.
 */
अटल व्योम rxrpc_peer_keepalive_dispatch(काष्ठा rxrpc_net *rxnet,
					  काष्ठा list_head *collector,
					  समय64_t base,
					  u8 cursor)
अणु
	काष्ठा rxrpc_peer *peer;
	स्थिर u8 mask = ARRAY_SIZE(rxnet->peer_keepalive) - 1;
	समय64_t keepalive_at;
	पूर्णांक slot;

	spin_lock_bh(&rxnet->peer_hash_lock);

	जबतक (!list_empty(collector)) अणु
		peer = list_entry(collector->next,
				  काष्ठा rxrpc_peer, keepalive_link);

		list_del_init(&peer->keepalive_link);
		अगर (!rxrpc_get_peer_maybe(peer))
			जारी;

		अगर (__rxrpc_use_local(peer->local)) अणु
			spin_unlock_bh(&rxnet->peer_hash_lock);

			keepalive_at = peer->last_tx_at + RXRPC_KEEPALIVE_TIME;
			slot = keepalive_at - base;
			_debug("%02x peer %u t=%d {%pISp}",
			       cursor, peer->debug_id, slot, &peer->srx.transport);

			अगर (keepalive_at <= base ||
			    keepalive_at > base + RXRPC_KEEPALIVE_TIME) अणु
				rxrpc_send_keepalive(peer);
				slot = RXRPC_KEEPALIVE_TIME;
			पूर्ण

			/* A transmission to this peer occurred since last we
			 * examined it so put it पूर्णांकo the appropriate future
			 * bucket.
			 */
			slot += cursor;
			slot &= mask;
			spin_lock_bh(&rxnet->peer_hash_lock);
			list_add_tail(&peer->keepalive_link,
				      &rxnet->peer_keepalive[slot & mask]);
			rxrpc_unuse_local(peer->local);
		पूर्ण
		rxrpc_put_peer_locked(peer);
	पूर्ण

	spin_unlock_bh(&rxnet->peer_hash_lock);
पूर्ण

/*
 * Perक्रमm keep-alive pings with VERSION packets to keep any NAT alive.
 */
व्योम rxrpc_peer_keepalive_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rxrpc_net *rxnet =
		container_of(work, काष्ठा rxrpc_net, peer_keepalive_work);
	स्थिर u8 mask = ARRAY_SIZE(rxnet->peer_keepalive) - 1;
	समय64_t base, now, delay;
	u8 cursor, stop;
	LIST_HEAD(collector);

	now = kसमय_get_seconds();
	base = rxnet->peer_keepalive_base;
	cursor = rxnet->peer_keepalive_cursor;
	_enter("%lld,%u", base - now, cursor);

	अगर (!rxnet->live)
		वापस;

	/* Remove to a temporary list all the peers that are currently lodged
	 * in expired buckets plus all new peers.
	 *
	 * Everything in the bucket at the cursor is processed this
	 * second; the bucket at cursor + 1 goes at now + 1s and so
	 * on...
	 */
	spin_lock_bh(&rxnet->peer_hash_lock);
	list_splice_init(&rxnet->peer_keepalive_new, &collector);

	stop = cursor + ARRAY_SIZE(rxnet->peer_keepalive);
	जबतक (base <= now && (s8)(cursor - stop) < 0) अणु
		list_splice_tail_init(&rxnet->peer_keepalive[cursor & mask],
				      &collector);
		base++;
		cursor++;
	पूर्ण

	base = now;
	spin_unlock_bh(&rxnet->peer_hash_lock);

	rxnet->peer_keepalive_base = base;
	rxnet->peer_keepalive_cursor = cursor;
	rxrpc_peer_keepalive_dispatch(rxnet, &collector, base, cursor);
	ASSERT(list_empty(&collector));

	/* Schedule the समयr क्रम the next occupied बारlot. */
	cursor = rxnet->peer_keepalive_cursor;
	stop = cursor + RXRPC_KEEPALIVE_TIME - 1;
	क्रम (; (s8)(cursor - stop) < 0; cursor++) अणु
		अगर (!list_empty(&rxnet->peer_keepalive[cursor & mask]))
			अवरोध;
		base++;
	पूर्ण

	now = kसमय_get_seconds();
	delay = base - now;
	अगर (delay < 1)
		delay = 1;
	delay *= HZ;
	अगर (rxnet->live)
		समयr_reduce(&rxnet->peer_keepalive_समयr, jअगरfies + delay);

	_leave("");
पूर्ण
