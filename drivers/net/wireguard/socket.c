<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#समावेश "device.h"
#समावेश "peer.h"
#समावेश "socket.h"
#समावेश "queueing.h"
#समावेश "messages.h"

#समावेश <linux/प्रकार.स>
#समावेश <linux/net.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/ipv6.h>

अटल पूर्णांक send4(काष्ठा wg_device *wg, काष्ठा sk_buff *skb,
		 काष्ठा endpoपूर्णांक *endpoपूर्णांक, u8 ds, काष्ठा dst_cache *cache)
अणु
	काष्ठा flowi4 fl = अणु
		.saddr = endpoपूर्णांक->src4.s_addr,
		.daddr = endpoपूर्णांक->addr4.sin_addr.s_addr,
		.fl4_dport = endpoपूर्णांक->addr4.sin_port,
		.flowi4_mark = wg->fwmark,
		.flowi4_proto = IPPROTO_UDP
	पूर्ण;
	काष्ठा rtable *rt = शून्य;
	काष्ठा sock *sock;
	पूर्णांक ret = 0;

	skb_mark_not_on_list(skb);
	skb->dev = wg->dev;
	skb->mark = wg->fwmark;

	rcu_पढ़ो_lock_bh();
	sock = rcu_dereference_bh(wg->sock4);

	अगर (unlikely(!sock)) अणु
		ret = -ENONET;
		जाओ err;
	पूर्ण

	fl.fl4_sport = inet_sk(sock)->inet_sport;

	अगर (cache)
		rt = dst_cache_get_ip4(cache, &fl.saddr);

	अगर (!rt) अणु
		security_sk_classअगरy_flow(sock, flowi4_to_flowi_common(&fl));
		अगर (unlikely(!inet_confirm_addr(sock_net(sock), शून्य, 0,
						fl.saddr, RT_SCOPE_HOST))) अणु
			endpoपूर्णांक->src4.s_addr = 0;
			endpoपूर्णांक->src_अगर4 = 0;
			fl.saddr = 0;
			अगर (cache)
				dst_cache_reset(cache);
		पूर्ण
		rt = ip_route_output_flow(sock_net(sock), &fl, sock);
		अगर (unlikely(endpoपूर्णांक->src_अगर4 && ((IS_ERR(rt) &&
			     PTR_ERR(rt) == -EINVAL) || (!IS_ERR(rt) &&
			     rt->dst.dev->अगरindex != endpoपूर्णांक->src_अगर4)))) अणु
			endpoपूर्णांक->src4.s_addr = 0;
			endpoपूर्णांक->src_अगर4 = 0;
			fl.saddr = 0;
			अगर (cache)
				dst_cache_reset(cache);
			अगर (!IS_ERR(rt))
				ip_rt_put(rt);
			rt = ip_route_output_flow(sock_net(sock), &fl, sock);
		पूर्ण
		अगर (IS_ERR(rt)) अणु
			ret = PTR_ERR(rt);
			net_dbg_ratelimited("%s: No route to %pISpfsc, error %d\n",
					    wg->dev->name, &endpoपूर्णांक->addr, ret);
			जाओ err;
		पूर्ण
		अगर (cache)
			dst_cache_set_ip4(cache, &rt->dst, fl.saddr);
	पूर्ण

	skb->ignore_df = 1;
	udp_tunnel_xmit_skb(rt, sock, skb, fl.saddr, fl.daddr, ds,
			    ip4_dst_hoplimit(&rt->dst), 0, fl.fl4_sport,
			    fl.fl4_dport, false, false);
	जाओ out;

err:
	kमुक्त_skb(skb);
out:
	rcu_पढ़ो_unlock_bh();
	वापस ret;
पूर्ण

अटल पूर्णांक send6(काष्ठा wg_device *wg, काष्ठा sk_buff *skb,
		 काष्ठा endpoपूर्णांक *endpoपूर्णांक, u8 ds, काष्ठा dst_cache *cache)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा flowi6 fl = अणु
		.saddr = endpoपूर्णांक->src6,
		.daddr = endpoपूर्णांक->addr6.sin6_addr,
		.fl6_dport = endpoपूर्णांक->addr6.sin6_port,
		.flowi6_mark = wg->fwmark,
		.flowi6_oअगर = endpoपूर्णांक->addr6.sin6_scope_id,
		.flowi6_proto = IPPROTO_UDP
		/* TODO: addr->sin6_flowinfo */
	पूर्ण;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा sock *sock;
	पूर्णांक ret = 0;

	skb_mark_not_on_list(skb);
	skb->dev = wg->dev;
	skb->mark = wg->fwmark;

	rcu_पढ़ो_lock_bh();
	sock = rcu_dereference_bh(wg->sock6);

	अगर (unlikely(!sock)) अणु
		ret = -ENONET;
		जाओ err;
	पूर्ण

	fl.fl6_sport = inet_sk(sock)->inet_sport;

	अगर (cache)
		dst = dst_cache_get_ip6(cache, &fl.saddr);

	अगर (!dst) अणु
		security_sk_classअगरy_flow(sock, flowi6_to_flowi_common(&fl));
		अगर (unlikely(!ipv6_addr_any(&fl.saddr) &&
			     !ipv6_chk_addr(sock_net(sock), &fl.saddr, शून्य, 0))) अणु
			endpoपूर्णांक->src6 = fl.saddr = in6addr_any;
			अगर (cache)
				dst_cache_reset(cache);
		पूर्ण
		dst = ipv6_stub->ipv6_dst_lookup_flow(sock_net(sock), sock, &fl,
						      शून्य);
		अगर (IS_ERR(dst)) अणु
			ret = PTR_ERR(dst);
			net_dbg_ratelimited("%s: No route to %pISpfsc, error %d\n",
					    wg->dev->name, &endpoपूर्णांक->addr, ret);
			जाओ err;
		पूर्ण
		अगर (cache)
			dst_cache_set_ip6(cache, dst, &fl.saddr);
	पूर्ण

	skb->ignore_df = 1;
	udp_tunnel6_xmit_skb(dst, sock, skb, skb->dev, &fl.saddr, &fl.daddr, ds,
			     ip6_dst_hoplimit(dst), 0, fl.fl6_sport,
			     fl.fl6_dport, false);
	जाओ out;

err:
	kमुक्त_skb(skb);
out:
	rcu_पढ़ो_unlock_bh();
	वापस ret;
#अन्यथा
	वापस -EAFNOSUPPORT;
#पूर्ण_अगर
पूर्ण

पूर्णांक wg_socket_send_skb_to_peer(काष्ठा wg_peer *peer, काष्ठा sk_buff *skb, u8 ds)
अणु
	माप_प्रकार skb_len = skb->len;
	पूर्णांक ret = -EAFNOSUPPORT;

	पढ़ो_lock_bh(&peer->endpoपूर्णांक_lock);
	अगर (peer->endpoपूर्णांक.addr.sa_family == AF_INET)
		ret = send4(peer->device, skb, &peer->endpoपूर्णांक, ds,
			    &peer->endpoपूर्णांक_cache);
	अन्यथा अगर (peer->endpoपूर्णांक.addr.sa_family == AF_INET6)
		ret = send6(peer->device, skb, &peer->endpoपूर्णांक, ds,
			    &peer->endpoपूर्णांक_cache);
	अन्यथा
		dev_kमुक्त_skb(skb);
	अगर (likely(!ret))
		peer->tx_bytes += skb_len;
	पढ़ो_unlock_bh(&peer->endpoपूर्णांक_lock);

	वापस ret;
पूर्ण

पूर्णांक wg_socket_send_buffer_to_peer(काष्ठा wg_peer *peer, व्योम *buffer,
				  माप_प्रकार len, u8 ds)
अणु
	काष्ठा sk_buff *skb = alloc_skb(len + SKB_HEADER_LEN, GFP_ATOMIC);

	अगर (unlikely(!skb))
		वापस -ENOMEM;

	skb_reserve(skb, SKB_HEADER_LEN);
	skb_set_inner_network_header(skb, 0);
	skb_put_data(skb, buffer, len);
	वापस wg_socket_send_skb_to_peer(peer, skb, ds);
पूर्ण

पूर्णांक wg_socket_send_buffer_as_reply_to_skb(काष्ठा wg_device *wg,
					  काष्ठा sk_buff *in_skb, व्योम *buffer,
					  माप_प्रकार len)
अणु
	पूर्णांक ret = 0;
	काष्ठा sk_buff *skb;
	काष्ठा endpoपूर्णांक endpoपूर्णांक;

	अगर (unlikely(!in_skb))
		वापस -EINVAL;
	ret = wg_socket_endpoपूर्णांक_from_skb(&endpoपूर्णांक, in_skb);
	अगर (unlikely(ret < 0))
		वापस ret;

	skb = alloc_skb(len + SKB_HEADER_LEN, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस -ENOMEM;
	skb_reserve(skb, SKB_HEADER_LEN);
	skb_set_inner_network_header(skb, 0);
	skb_put_data(skb, buffer, len);

	अगर (endpoपूर्णांक.addr.sa_family == AF_INET)
		ret = send4(wg, skb, &endpoपूर्णांक, 0, शून्य);
	अन्यथा अगर (endpoपूर्णांक.addr.sa_family == AF_INET6)
		ret = send6(wg, skb, &endpoपूर्णांक, 0, शून्य);
	/* No other possibilities अगर the endpoपूर्णांक is valid, which it is,
	 * as we checked above.
	 */

	वापस ret;
पूर्ण

पूर्णांक wg_socket_endpoपूर्णांक_from_skb(काष्ठा endpoपूर्णांक *endpoपूर्णांक,
				स्थिर काष्ठा sk_buff *skb)
अणु
	स_रखो(endpoपूर्णांक, 0, माप(*endpoपूर्णांक));
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		endpoपूर्णांक->addr4.sin_family = AF_INET;
		endpoपूर्णांक->addr4.sin_port = udp_hdr(skb)->source;
		endpoपूर्णांक->addr4.sin_addr.s_addr = ip_hdr(skb)->saddr;
		endpoपूर्णांक->src4.s_addr = ip_hdr(skb)->daddr;
		endpoपूर्णांक->src_अगर4 = skb->skb_iअगर;
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		endpoपूर्णांक->addr6.sin6_family = AF_INET6;
		endpoपूर्णांक->addr6.sin6_port = udp_hdr(skb)->source;
		endpoपूर्णांक->addr6.sin6_addr = ipv6_hdr(skb)->saddr;
		endpoपूर्णांक->addr6.sin6_scope_id = ipv6_अगरace_scope_id(
			&ipv6_hdr(skb)->saddr, skb->skb_iअगर);
		endpoपूर्णांक->src6 = ipv6_hdr(skb)->daddr;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool endpoपूर्णांक_eq(स्थिर काष्ठा endpoपूर्णांक *a, स्थिर काष्ठा endpoपूर्णांक *b)
अणु
	वापस (a->addr.sa_family == AF_INET && b->addr.sa_family == AF_INET &&
		a->addr4.sin_port == b->addr4.sin_port &&
		a->addr4.sin_addr.s_addr == b->addr4.sin_addr.s_addr &&
		a->src4.s_addr == b->src4.s_addr && a->src_अगर4 == b->src_अगर4) ||
	       (a->addr.sa_family == AF_INET6 &&
		b->addr.sa_family == AF_INET6 &&
		a->addr6.sin6_port == b->addr6.sin6_port &&
		ipv6_addr_equal(&a->addr6.sin6_addr, &b->addr6.sin6_addr) &&
		a->addr6.sin6_scope_id == b->addr6.sin6_scope_id &&
		ipv6_addr_equal(&a->src6, &b->src6)) ||
	       unlikely(!a->addr.sa_family && !b->addr.sa_family);
पूर्ण

व्योम wg_socket_set_peer_endpoपूर्णांक(काष्ठा wg_peer *peer,
				 स्थिर काष्ठा endpoपूर्णांक *endpoपूर्णांक)
अणु
	/* First we check unlocked, in order to optimize, since it's pretty rare
	 * that an endpoपूर्णांक will change. If we happen to be mid-ग_लिखो, and two
	 * CPUs wind up writing the same thing or something slightly dअगरferent,
	 * it करोesn't really matter much either.
	 */
	अगर (endpoपूर्णांक_eq(endpoपूर्णांक, &peer->endpoपूर्णांक))
		वापस;
	ग_लिखो_lock_bh(&peer->endpoपूर्णांक_lock);
	अगर (endpoपूर्णांक->addr.sa_family == AF_INET) अणु
		peer->endpoपूर्णांक.addr4 = endpoपूर्णांक->addr4;
		peer->endpoपूर्णांक.src4 = endpoपूर्णांक->src4;
		peer->endpoपूर्णांक.src_अगर4 = endpoपूर्णांक->src_अगर4;
	पूर्ण अन्यथा अगर (endpoपूर्णांक->addr.sa_family == AF_INET6) अणु
		peer->endpoपूर्णांक.addr6 = endpoपूर्णांक->addr6;
		peer->endpoपूर्णांक.src6 = endpoपूर्णांक->src6;
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण
	dst_cache_reset(&peer->endpoपूर्णांक_cache);
out:
	ग_लिखो_unlock_bh(&peer->endpoपूर्णांक_lock);
पूर्ण

व्योम wg_socket_set_peer_endpoपूर्णांक_from_skb(काष्ठा wg_peer *peer,
					  स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा endpoपूर्णांक endpoपूर्णांक;

	अगर (!wg_socket_endpoपूर्णांक_from_skb(&endpoपूर्णांक, skb))
		wg_socket_set_peer_endpoपूर्णांक(peer, &endpoपूर्णांक);
पूर्ण

व्योम wg_socket_clear_peer_endpoपूर्णांक_src(काष्ठा wg_peer *peer)
अणु
	ग_लिखो_lock_bh(&peer->endpoपूर्णांक_lock);
	स_रखो(&peer->endpoपूर्णांक.src6, 0, माप(peer->endpoपूर्णांक.src6));
	dst_cache_reset(&peer->endpoपूर्णांक_cache);
	ग_लिखो_unlock_bh(&peer->endpoपूर्णांक_lock);
पूर्ण

अटल पूर्णांक wg_receive(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा wg_device *wg;

	अगर (unlikely(!sk))
		जाओ err;
	wg = sk->sk_user_data;
	अगर (unlikely(!wg))
		जाओ err;
	skb_mark_not_on_list(skb);
	wg_packet_receive(wg, skb);
	वापस 0;

err:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम sock_मुक्त(काष्ठा sock *sock)
अणु
	अगर (unlikely(!sock))
		वापस;
	sk_clear_meदो_स्मृति(sock);
	udp_tunnel_sock_release(sock->sk_socket);
पूर्ण

अटल व्योम set_sock_opts(काष्ठा socket *sock)
अणु
	sock->sk->sk_allocation = GFP_ATOMIC;
	sock->sk->sk_sndbuf = पूर्णांक_उच्च;
	sk_set_meदो_स्मृति(sock->sk);
पूर्ण

पूर्णांक wg_socket_init(काष्ठा wg_device *wg, u16 port)
अणु
	काष्ठा net *net;
	पूर्णांक ret;
	काष्ठा udp_tunnel_sock_cfg cfg = अणु
		.sk_user_data = wg,
		.encap_type = 1,
		.encap_rcv = wg_receive
	पूर्ण;
	काष्ठा socket *new4 = शून्य, *new6 = शून्य;
	काष्ठा udp_port_cfg port4 = अणु
		.family = AF_INET,
		.local_ip.s_addr = htonl(INADDR_ANY),
		.local_udp_port = htons(port),
		.use_udp_checksums = true
	पूर्ण;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्णांक retries = 0;
	काष्ठा udp_port_cfg port6 = अणु
		.family = AF_INET6,
		.local_ip6 = IN6ADDR_ANY_INIT,
		.use_udp6_tx_checksums = true,
		.use_udp6_rx_checksums = true,
		.ipv6_v6only = true
	पूर्ण;
#पूर्ण_अगर

	rcu_पढ़ो_lock();
	net = rcu_dereference(wg->creating_net);
	net = net ? maybe_get_net(net) : शून्य;
	rcu_पढ़ो_unlock();
	अगर (unlikely(!net))
		वापस -ENONET;

#अगर IS_ENABLED(CONFIG_IPV6)
retry:
#पूर्ण_अगर

	ret = udp_sock_create(net, &port4, &new4);
	अगर (ret < 0) अणु
		pr_err("%s: Could not create IPv4 socket\n", wg->dev->name);
		जाओ out;
	पूर्ण
	set_sock_opts(new4);
	setup_udp_tunnel_sock(net, new4, &cfg);

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (ipv6_mod_enabled()) अणु
		port6.local_udp_port = inet_sk(new4->sk)->inet_sport;
		ret = udp_sock_create(net, &port6, &new6);
		अगर (ret < 0) अणु
			udp_tunnel_sock_release(new4);
			अगर (ret == -EADDRINUSE && !port && retries++ < 100)
				जाओ retry;
			pr_err("%s: Could not create IPv6 socket\n",
			       wg->dev->name);
			जाओ out;
		पूर्ण
		set_sock_opts(new6);
		setup_udp_tunnel_sock(net, new6, &cfg);
	पूर्ण
#पूर्ण_अगर

	wg_socket_reinit(wg, new4->sk, new6 ? new6->sk : शून्य);
	ret = 0;
out:
	put_net(net);
	वापस ret;
पूर्ण

व्योम wg_socket_reinit(काष्ठा wg_device *wg, काष्ठा sock *new4,
		      काष्ठा sock *new6)
अणु
	काष्ठा sock *old4, *old6;

	mutex_lock(&wg->socket_update_lock);
	old4 = rcu_dereference_रक्षित(wg->sock4,
				lockdep_is_held(&wg->socket_update_lock));
	old6 = rcu_dereference_रक्षित(wg->sock6,
				lockdep_is_held(&wg->socket_update_lock));
	rcu_assign_poपूर्णांकer(wg->sock4, new4);
	rcu_assign_poपूर्णांकer(wg->sock6, new6);
	अगर (new4)
		wg->incoming_port = ntohs(inet_sk(new4)->inet_sport);
	mutex_unlock(&wg->socket_update_lock);
	synchronize_net();
	sock_मुक्त(old4);
	sock_मुक्त(old6);
पूर्ण
