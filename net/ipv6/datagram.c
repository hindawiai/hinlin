<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	common UDP/RAW code
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 */

#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/in6.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/route.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/icmp.h>

#समावेश <net/ipv6.h>
#समावेश <net/ndisc.h>
#समावेश <net/addrconf.h>
#समावेश <net/transp_v6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/tcp_states.h>
#समावेश <net/dsfield.h>
#समावेश <net/sock_reuseport.h>

#समावेश <linux/errqueue.h>
#समावेश <linux/uaccess.h>

अटल bool ipv6_mapped_addr_any(स्थिर काष्ठा in6_addr *a)
अणु
	वापस ipv6_addr_v4mapped(a) && (a->s6_addr32[3] == 0);
पूर्ण

अटल व्योम ip6_datagram_flow_key_init(काष्ठा flowi6 *fl6, काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	स_रखो(fl6, 0, माप(*fl6));
	fl6->flowi6_proto = sk->sk_protocol;
	fl6->daddr = sk->sk_v6_daddr;
	fl6->saddr = np->saddr;
	fl6->flowi6_oअगर = sk->sk_bound_dev_अगर;
	fl6->flowi6_mark = sk->sk_mark;
	fl6->fl6_dport = inet->inet_dport;
	fl6->fl6_sport = inet->inet_sport;
	fl6->flowlabel = np->flow_label;
	fl6->flowi6_uid = sk->sk_uid;

	अगर (!fl6->flowi6_oअगर)
		fl6->flowi6_oअगर = np->sticky_pktinfo.ipi6_अगरindex;

	अगर (!fl6->flowi6_oअगर && ipv6_addr_is_multicast(&fl6->daddr))
		fl6->flowi6_oअगर = np->mcast_oअगर;

	security_sk_classअगरy_flow(sk, flowi6_to_flowi_common(fl6));
पूर्ण

पूर्णांक ip6_datagram_dst_update(काष्ठा sock *sk, bool fix_sk_saddr)
अणु
	काष्ठा ip6_flowlabel *flowlabel = शून्य;
	काष्ठा in6_addr *final_p, final;
	काष्ठा ipv6_txoptions *opt;
	काष्ठा dst_entry *dst;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा flowi6 fl6;
	पूर्णांक err = 0;

	अगर (np->sndflow && (np->flow_label & IPV6_FLOWLABEL_MASK)) अणु
		flowlabel = fl6_sock_lookup(sk, np->flow_label);
		अगर (IS_ERR(flowlabel))
			वापस -EINVAL;
	पूर्ण
	ip6_datagram_flow_key_init(&fl6, sk);

	rcu_पढ़ो_lock();
	opt = flowlabel ? flowlabel->opt : rcu_dereference(np->opt);
	final_p = fl6_update_dst(&fl6, opt, &final);
	rcu_पढ़ो_unlock();

	dst = ip6_dst_lookup_flow(sock_net(sk), sk, &fl6, final_p);
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		जाओ out;
	पूर्ण

	अगर (fix_sk_saddr) अणु
		अगर (ipv6_addr_any(&np->saddr))
			np->saddr = fl6.saddr;

		अगर (ipv6_addr_any(&sk->sk_v6_rcv_saddr)) अणु
			sk->sk_v6_rcv_saddr = fl6.saddr;
			inet->inet_rcv_saddr = LOOPBACK4_IPV6;
			अगर (sk->sk_prot->rehash)
				sk->sk_prot->rehash(sk);
		पूर्ण
	पूर्ण

	ip6_sk_dst_store_flow(sk, dst, &fl6);

out:
	fl6_sock_release(flowlabel);
	वापस err;
पूर्ण

व्योम ip6_datagram_release_cb(काष्ठा sock *sk)
अणु
	काष्ठा dst_entry *dst;

	अगर (ipv6_addr_v4mapped(&sk->sk_v6_daddr))
		वापस;

	rcu_पढ़ो_lock();
	dst = __sk_dst_get(sk);
	अगर (!dst || !dst->obsolete ||
	    dst->ops->check(dst, inet6_sk(sk)->dst_cookie)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();

	ip6_datagram_dst_update(sk, false);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_datagram_release_cb);

पूर्णांक __ip6_datagram_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr,
			   पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_in6	*usin = (काष्ठा sockaddr_in6 *) uaddr;
	काष्ठा inet_sock	*inet = inet_sk(sk);
	काष्ठा ipv6_pinfo	*np = inet6_sk(sk);
	काष्ठा in6_addr		*daddr, old_daddr;
	__be32			fl6_flowlabel = 0;
	__be32			old_fl6_flowlabel;
	__be16			old_dport;
	पूर्णांक			addr_type;
	पूर्णांक			err;

	अगर (usin->sin6_family == AF_INET) अणु
		अगर (__ipv6_only_sock(sk))
			वापस -EAFNOSUPPORT;
		err = __ip4_datagram_connect(sk, uaddr, addr_len);
		जाओ ipv4_connected;
	पूर्ण

	अगर (addr_len < SIN6_LEN_RFC2133)
		वापस -EINVAL;

	अगर (usin->sin6_family != AF_INET6)
		वापस -EAFNOSUPPORT;

	अगर (np->sndflow)
		fl6_flowlabel = usin->sin6_flowinfo & IPV6_FLOWINFO_MASK;

	अगर (ipv6_addr_any(&usin->sin6_addr)) अणु
		/*
		 *	connect to self
		 */
		अगर (ipv6_addr_v4mapped(&sk->sk_v6_rcv_saddr))
			ipv6_addr_set_v4mapped(htonl(INADDR_LOOPBACK),
					       &usin->sin6_addr);
		अन्यथा
			usin->sin6_addr = in6addr_loopback;
	पूर्ण

	addr_type = ipv6_addr_type(&usin->sin6_addr);

	daddr = &usin->sin6_addr;

	अगर (addr_type & IPV6_ADDR_MAPPED) अणु
		काष्ठा sockaddr_in sin;

		अगर (__ipv6_only_sock(sk)) अणु
			err = -ENETUNREACH;
			जाओ out;
		पूर्ण
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = daddr->s6_addr32[3];
		sin.sin_port = usin->sin6_port;

		err = __ip4_datagram_connect(sk,
					     (काष्ठा sockaddr *) &sin,
					     माप(sin));

ipv4_connected:
		अगर (err)
			जाओ out;

		ipv6_addr_set_v4mapped(inet->inet_daddr, &sk->sk_v6_daddr);

		अगर (ipv6_addr_any(&np->saddr) ||
		    ipv6_mapped_addr_any(&np->saddr))
			ipv6_addr_set_v4mapped(inet->inet_saddr, &np->saddr);

		अगर (ipv6_addr_any(&sk->sk_v6_rcv_saddr) ||
		    ipv6_mapped_addr_any(&sk->sk_v6_rcv_saddr)) अणु
			ipv6_addr_set_v4mapped(inet->inet_rcv_saddr,
					       &sk->sk_v6_rcv_saddr);
			अगर (sk->sk_prot->rehash)
				sk->sk_prot->rehash(sk);
		पूर्ण

		जाओ out;
	पूर्ण

	अगर (__ipv6_addr_needs_scope_id(addr_type)) अणु
		अगर (addr_len >= माप(काष्ठा sockaddr_in6) &&
		    usin->sin6_scope_id) अणु
			अगर (!sk_dev_equal_l3scope(sk, usin->sin6_scope_id)) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण
			sk->sk_bound_dev_अगर = usin->sin6_scope_id;
		पूर्ण

		अगर (!sk->sk_bound_dev_अगर && (addr_type & IPV6_ADDR_MULTICAST))
			sk->sk_bound_dev_अगर = np->mcast_oअगर;

		/* Connect to link-local address requires an पूर्णांकerface */
		अगर (!sk->sk_bound_dev_अगर) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* save the current peer inक्रमmation beक्रमe updating it */
	old_daddr = sk->sk_v6_daddr;
	old_fl6_flowlabel = np->flow_label;
	old_dport = inet->inet_dport;

	sk->sk_v6_daddr = *daddr;
	np->flow_label = fl6_flowlabel;
	inet->inet_dport = usin->sin6_port;

	/*
	 *	Check क्रम a route to destination an obtain the
	 *	destination cache क्रम it.
	 */

	err = ip6_datagram_dst_update(sk, true);
	अगर (err) अणु
		/* Restore the socket peer info, to keep it consistent with
		 * the old socket state
		 */
		sk->sk_v6_daddr = old_daddr;
		np->flow_label = old_fl6_flowlabel;
		inet->inet_dport = old_dport;
		जाओ out;
	पूर्ण

	reuseport_has_conns(sk, true);
	sk->sk_state = TCP_ESTABLISHED;
	sk_set_txhash(sk);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__ip6_datagram_connect);

पूर्णांक ip6_datagram_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	पूर्णांक res;

	lock_sock(sk);
	res = __ip6_datagram_connect(sk, uaddr, addr_len);
	release_sock(sk);
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(ip6_datagram_connect);

पूर्णांक ip6_datagram_connect_v6_only(काष्ठा sock *sk, काष्ठा sockaddr *uaddr,
				 पूर्णांक addr_len)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, sin6, uaddr);
	अगर (sin6->sin6_family != AF_INET6)
		वापस -EAFNOSUPPORT;
	वापस ip6_datagram_connect(sk, uaddr, addr_len);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_datagram_connect_v6_only);

अटल व्योम ipv6_icmp_error_rfc4884(स्थिर काष्ठा sk_buff *skb,
				    काष्ठा sock_ee_data_rfc4884 *out)
अणु
	चयन (icmp6_hdr(skb)->icmp6_type) अणु
	हाल ICMPV6_TIME_EXCEED:
	हाल ICMPV6_DEST_UNREACH:
		ip_icmp_error_rfc4884(skb, out, माप(काष्ठा icmp6hdr),
				      icmp6_hdr(skb)->icmp6_datagram_len * 8);
	पूर्ण
पूर्ण

व्योम ipv6_icmp_error(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक err,
		     __be16 port, u32 info, u8 *payload)
अणु
	काष्ठा ipv6_pinfo *np  = inet6_sk(sk);
	काष्ठा icmp6hdr *icmph = icmp6_hdr(skb);
	काष्ठा sock_exterr_skb *serr;

	अगर (!np->recverr)
		वापस;

	skb = skb_clone(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	skb->protocol = htons(ETH_P_IPV6);

	serr = SKB_EXT_ERR(skb);
	serr->ee.ee_त्रुटि_सं = err;
	serr->ee.ee_origin = SO_EE_ORIGIN_ICMP6;
	serr->ee.ee_type = icmph->icmp6_type;
	serr->ee.ee_code = icmph->icmp6_code;
	serr->ee.ee_pad = 0;
	serr->ee.ee_info = info;
	serr->ee.ee_data = 0;
	serr->addr_offset = (u8 *)&(((काष्ठा ipv6hdr *)(icmph + 1))->daddr) -
				  skb_network_header(skb);
	serr->port = port;

	__skb_pull(skb, payload - skb->data);

	अगर (inet6_sk(sk)->recverr_rfc4884)
		ipv6_icmp_error_rfc4884(skb, &serr->ee.ee_rfc4884);

	skb_reset_transport_header(skb);

	अगर (sock_queue_err_skb(sk, skb))
		kमुक्त_skb(skb);
पूर्ण

व्योम ipv6_local_error(काष्ठा sock *sk, पूर्णांक err, काष्ठा flowi6 *fl6, u32 info)
अणु
	स्थिर काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा sock_exterr_skb *serr;
	काष्ठा ipv6hdr *iph;
	काष्ठा sk_buff *skb;

	अगर (!np->recverr)
		वापस;

	skb = alloc_skb(माप(काष्ठा ipv6hdr), GFP_ATOMIC);
	अगर (!skb)
		वापस;

	skb->protocol = htons(ETH_P_IPV6);

	skb_put(skb, माप(काष्ठा ipv6hdr));
	skb_reset_network_header(skb);
	iph = ipv6_hdr(skb);
	iph->daddr = fl6->daddr;
	ip6_flow_hdr(iph, 0, 0);

	serr = SKB_EXT_ERR(skb);
	serr->ee.ee_त्रुटि_सं = err;
	serr->ee.ee_origin = SO_EE_ORIGIN_LOCAL;
	serr->ee.ee_type = 0;
	serr->ee.ee_code = 0;
	serr->ee.ee_pad = 0;
	serr->ee.ee_info = info;
	serr->ee.ee_data = 0;
	serr->addr_offset = (u8 *)&iph->daddr - skb_network_header(skb);
	serr->port = fl6->fl6_dport;

	__skb_pull(skb, skb_tail_poपूर्णांकer(skb) - skb->data);
	skb_reset_transport_header(skb);

	अगर (sock_queue_err_skb(sk, skb))
		kमुक्त_skb(skb);
पूर्ण

व्योम ipv6_local_rxpmtu(काष्ठा sock *sk, काष्ठा flowi6 *fl6, u32 mtu)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6hdr *iph;
	काष्ठा sk_buff *skb;
	काष्ठा ip6_mtuinfo *mtu_info;

	अगर (!np->rxopt.bits.rxpmtu)
		वापस;

	skb = alloc_skb(माप(काष्ठा ipv6hdr), GFP_ATOMIC);
	अगर (!skb)
		वापस;

	skb_put(skb, माप(काष्ठा ipv6hdr));
	skb_reset_network_header(skb);
	iph = ipv6_hdr(skb);
	iph->daddr = fl6->daddr;

	mtu_info = IP6CBMTU(skb);

	mtu_info->ip6m_mtu = mtu;
	mtu_info->ip6m_addr.sin6_family = AF_INET6;
	mtu_info->ip6m_addr.sin6_port = 0;
	mtu_info->ip6m_addr.sin6_flowinfo = 0;
	mtu_info->ip6m_addr.sin6_scope_id = fl6->flowi6_oअगर;
	mtu_info->ip6m_addr.sin6_addr = ipv6_hdr(skb)->daddr;

	__skb_pull(skb, skb_tail_poपूर्णांकer(skb) - skb->data);
	skb_reset_transport_header(skb);

	skb = xchg(&np->rxpmtu, skb);
	kमुक्त_skb(skb);
पूर्ण

/* For some errors we have valid addr_offset even with zero payload and
 * zero port. Also, addr_offset should be supported अगर port is set.
 */
अटल अंतरभूत bool ipv6_datagram_support_addr(काष्ठा sock_exterr_skb *serr)
अणु
	वापस serr->ee.ee_origin == SO_EE_ORIGIN_ICMP6 ||
	       serr->ee.ee_origin == SO_EE_ORIGIN_ICMP ||
	       serr->ee.ee_origin == SO_EE_ORIGIN_LOCAL || serr->port;
पूर्ण

/* IPv6 supports cmsg on all origins aside from SO_EE_ORIGIN_LOCAL.
 *
 * At one poपूर्णांक, excluding local errors was a quick test to identअगरy icmp/icmp6
 * errors. This is no दीर्घer true, but the test reमुख्यed, so the v6 stack,
 * unlike v4, also honors cmsg requests on all wअगरi and बारtamp errors.
 */
अटल bool ip6_datagram_support_cmsg(काष्ठा sk_buff *skb,
				      काष्ठा sock_exterr_skb *serr)
अणु
	अगर (serr->ee.ee_origin == SO_EE_ORIGIN_ICMP ||
	    serr->ee.ee_origin == SO_EE_ORIGIN_ICMP6)
		वापस true;

	अगर (serr->ee.ee_origin == SO_EE_ORIGIN_LOCAL)
		वापस false;

	अगर (!IP6CB(skb)->iअगर)
		वापस false;

	वापस true;
पूर्ण

/*
 *	Handle MSG_ERRQUEUE
 */
पूर्णांक ipv6_recv_error(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len, पूर्णांक *addr_len)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा sock_exterr_skb *serr;
	काष्ठा sk_buff *skb;
	DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, sin, msg->msg_name);
	काष्ठा अणु
		काष्ठा sock_extended_err ee;
		काष्ठा sockaddr_in6	 offender;
	पूर्ण errhdr;
	पूर्णांक err;
	पूर्णांक copied;

	err = -EAGAIN;
	skb = sock_dequeue_err_skb(sk);
	अगर (!skb)
		जाओ out;

	copied = skb->len;
	अगर (copied > len) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण
	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (unlikely(err)) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण
	sock_recv_बारtamp(msg, sk, skb);

	serr = SKB_EXT_ERR(skb);

	अगर (sin && ipv6_datagram_support_addr(serr)) अणु
		स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);
		sin->sin6_family = AF_INET6;
		sin->sin6_flowinfo = 0;
		sin->sin6_port = serr->port;
		अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
			स्थिर काष्ठा ipv6hdr *ip6h = container_of((काष्ठा in6_addr *)(nh + serr->addr_offset),
								  काष्ठा ipv6hdr, daddr);
			sin->sin6_addr = ip6h->daddr;
			अगर (np->sndflow)
				sin->sin6_flowinfo = ip6_flowinfo(ip6h);
			sin->sin6_scope_id =
				ipv6_अगरace_scope_id(&sin->sin6_addr,
						    IP6CB(skb)->iअगर);
		पूर्ण अन्यथा अणु
			ipv6_addr_set_v4mapped(*(__be32 *)(nh + serr->addr_offset),
					       &sin->sin6_addr);
			sin->sin6_scope_id = 0;
		पूर्ण
		*addr_len = माप(*sin);
	पूर्ण

	स_नकल(&errhdr.ee, &serr->ee, माप(काष्ठा sock_extended_err));
	sin = &errhdr.offender;
	स_रखो(sin, 0, माप(*sin));

	अगर (ip6_datagram_support_cmsg(skb, serr)) अणु
		sin->sin6_family = AF_INET6;
		अगर (np->rxopt.all)
			ip6_datagram_recv_common_ctl(sk, msg, skb);
		अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
			sin->sin6_addr = ipv6_hdr(skb)->saddr;
			अगर (np->rxopt.all)
				ip6_datagram_recv_specअगरic_ctl(sk, msg, skb);
			sin->sin6_scope_id =
				ipv6_अगरace_scope_id(&sin->sin6_addr,
						    IP6CB(skb)->iअगर);
		पूर्ण अन्यथा अणु
			ipv6_addr_set_v4mapped(ip_hdr(skb)->saddr,
					       &sin->sin6_addr);
			अगर (inet_sk(sk)->cmsg_flags)
				ip_cmsg_recv(msg, skb);
		पूर्ण
	पूर्ण

	put_cmsg(msg, SOL_IPV6, IPV6_RECVERR, माप(errhdr), &errhdr);

	/* Now we could try to dump offended packet options */

	msg->msg_flags |= MSG_ERRQUEUE;
	err = copied;

	consume_skb(skb);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ipv6_recv_error);

/*
 *	Handle IPV6_RECVPATHMTU
 */
पूर्णांक ipv6_recv_rxpmtu(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len,
		     पूर्णांक *addr_len)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा sk_buff *skb;
	काष्ठा ip6_mtuinfo mtu_info;
	DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, sin, msg->msg_name);
	पूर्णांक err;
	पूर्णांक copied;

	err = -EAGAIN;
	skb = xchg(&np->rxpmtu, शून्य);
	अगर (!skb)
		जाओ out;

	copied = skb->len;
	अगर (copied > len) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण
	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (err)
		जाओ out_मुक्त_skb;

	sock_recv_बारtamp(msg, sk, skb);

	स_नकल(&mtu_info, IP6CBMTU(skb), माप(mtu_info));

	अगर (sin) अणु
		sin->sin6_family = AF_INET6;
		sin->sin6_flowinfo = 0;
		sin->sin6_port = 0;
		sin->sin6_scope_id = mtu_info.ip6m_addr.sin6_scope_id;
		sin->sin6_addr = mtu_info.ip6m_addr.sin6_addr;
		*addr_len = माप(*sin);
	पूर्ण

	put_cmsg(msg, SOL_IPV6, IPV6_PATHMTU, माप(mtu_info), &mtu_info);

	err = copied;

out_मुक्त_skb:
	kमुक्त_skb(skb);
out:
	वापस err;
पूर्ण


व्योम ip6_datagram_recv_common_ctl(काष्ठा sock *sk, काष्ठा msghdr *msg,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	bool is_ipv6 = skb->protocol == htons(ETH_P_IPV6);

	अगर (np->rxopt.bits.rxinfo) अणु
		काष्ठा in6_pktinfo src_info;

		अगर (is_ipv6) अणु
			src_info.ipi6_अगरindex = IP6CB(skb)->iअगर;
			src_info.ipi6_addr = ipv6_hdr(skb)->daddr;
		पूर्ण अन्यथा अणु
			src_info.ipi6_अगरindex =
				PKTINFO_SKB_CB(skb)->ipi_अगरindex;
			ipv6_addr_set_v4mapped(ip_hdr(skb)->daddr,
					       &src_info.ipi6_addr);
		पूर्ण

		अगर (src_info.ipi6_अगरindex >= 0)
			put_cmsg(msg, SOL_IPV6, IPV6_PKTINFO,
				 माप(src_info), &src_info);
	पूर्ण
पूर्ण

व्योम ip6_datagram_recv_specअगरic_ctl(काष्ठा sock *sk, काष्ठा msghdr *msg,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा inet6_skb_parm *opt = IP6CB(skb);
	अचिन्हित अक्षर *nh = skb_network_header(skb);

	अगर (np->rxopt.bits.rxhlim) अणु
		पूर्णांक hlim = ipv6_hdr(skb)->hop_limit;
		put_cmsg(msg, SOL_IPV6, IPV6_HOPLIMIT, माप(hlim), &hlim);
	पूर्ण

	अगर (np->rxopt.bits.rxtclass) अणु
		पूर्णांक tclass = ipv6_get_dsfield(ipv6_hdr(skb));
		put_cmsg(msg, SOL_IPV6, IPV6_TCLASS, माप(tclass), &tclass);
	पूर्ण

	अगर (np->rxopt.bits.rxflow) अणु
		__be32 flowinfo = ip6_flowinfo((काष्ठा ipv6hdr *)nh);
		अगर (flowinfo)
			put_cmsg(msg, SOL_IPV6, IPV6_FLOWINFO, माप(flowinfo), &flowinfo);
	पूर्ण

	/* HbH is allowed only once */
	अगर (np->rxopt.bits.hopopts && (opt->flags & IP6SKB_HOPBYHOP)) अणु
		u8 *ptr = nh + माप(काष्ठा ipv6hdr);
		put_cmsg(msg, SOL_IPV6, IPV6_HOPOPTS, (ptr[1]+1)<<3, ptr);
	पूर्ण

	अगर (opt->lastopt &&
	    (np->rxopt.bits.dstopts || np->rxopt.bits.srcrt)) अणु
		/*
		 * Silly enough, but we need to reparse in order to
		 * report extension headers (except क्रम HbH)
		 * in order.
		 *
		 * Also note that IPV6_RECVRTHDRDSTOPTS is NOT
		 * (and WILL NOT be) defined because
		 * IPV6_RECVDSTOPTS is more generic. --yoshfuji
		 */
		अचिन्हित पूर्णांक off = माप(काष्ठा ipv6hdr);
		u8 nexthdr = ipv6_hdr(skb)->nexthdr;

		जबतक (off <= opt->lastopt) अणु
			अचिन्हित पूर्णांक len;
			u8 *ptr = nh + off;

			चयन (nexthdr) अणु
			हाल IPPROTO_DSTOPTS:
				nexthdr = ptr[0];
				len = (ptr[1] + 1) << 3;
				अगर (np->rxopt.bits.dstopts)
					put_cmsg(msg, SOL_IPV6, IPV6_DSTOPTS, len, ptr);
				अवरोध;
			हाल IPPROTO_ROUTING:
				nexthdr = ptr[0];
				len = (ptr[1] + 1) << 3;
				अगर (np->rxopt.bits.srcrt)
					put_cmsg(msg, SOL_IPV6, IPV6_RTHDR, len, ptr);
				अवरोध;
			हाल IPPROTO_AH:
				nexthdr = ptr[0];
				len = (ptr[1] + 2) << 2;
				अवरोध;
			शेष:
				nexthdr = ptr[0];
				len = (ptr[1] + 1) << 3;
				अवरोध;
			पूर्ण

			off += len;
		पूर्ण
	पूर्ण

	/* socket options in old style */
	अगर (np->rxopt.bits.rxoinfo) अणु
		काष्ठा in6_pktinfo src_info;

		src_info.ipi6_अगरindex = opt->iअगर;
		src_info.ipi6_addr = ipv6_hdr(skb)->daddr;
		put_cmsg(msg, SOL_IPV6, IPV6_2292PKTINFO, माप(src_info), &src_info);
	पूर्ण
	अगर (np->rxopt.bits.rxohlim) अणु
		पूर्णांक hlim = ipv6_hdr(skb)->hop_limit;
		put_cmsg(msg, SOL_IPV6, IPV6_2292HOPLIMIT, माप(hlim), &hlim);
	पूर्ण
	अगर (np->rxopt.bits.ohopopts && (opt->flags & IP6SKB_HOPBYHOP)) अणु
		u8 *ptr = nh + माप(काष्ठा ipv6hdr);
		put_cmsg(msg, SOL_IPV6, IPV6_2292HOPOPTS, (ptr[1]+1)<<3, ptr);
	पूर्ण
	अगर (np->rxopt.bits.odstopts && opt->dst0) अणु
		u8 *ptr = nh + opt->dst0;
		put_cmsg(msg, SOL_IPV6, IPV6_2292DSTOPTS, (ptr[1]+1)<<3, ptr);
	पूर्ण
	अगर (np->rxopt.bits.osrcrt && opt->srcrt) अणु
		काष्ठा ipv6_rt_hdr *rthdr = (काष्ठा ipv6_rt_hdr *)(nh + opt->srcrt);
		put_cmsg(msg, SOL_IPV6, IPV6_2292RTHDR, (rthdr->hdrlen+1) << 3, rthdr);
	पूर्ण
	अगर (np->rxopt.bits.odstopts && opt->dst1) अणु
		u8 *ptr = nh + opt->dst1;
		put_cmsg(msg, SOL_IPV6, IPV6_2292DSTOPTS, (ptr[1]+1)<<3, ptr);
	पूर्ण
	अगर (np->rxopt.bits.rxorigdstaddr) अणु
		काष्ठा sockaddr_in6 sin6;
		__be16 _ports[2], *ports;

		ports = skb_header_poपूर्णांकer(skb, skb_transport_offset(skb),
					   माप(_ports), &_ports);
		अगर (ports) अणु
			/* All current transport protocols have the port numbers in the
			 * first four bytes of the transport header and this function is
			 * written with this assumption in mind.
			 */
			sin6.sin6_family = AF_INET6;
			sin6.sin6_addr = ipv6_hdr(skb)->daddr;
			sin6.sin6_port = ports[1];
			sin6.sin6_flowinfo = 0;
			sin6.sin6_scope_id =
				ipv6_अगरace_scope_id(&ipv6_hdr(skb)->daddr,
						    opt->iअगर);

			put_cmsg(msg, SOL_IPV6, IPV6_ORIGDSTADDR, माप(sin6), &sin6);
		पूर्ण
	पूर्ण
	अगर (np->rxopt.bits.recvfragsize && opt->frag_max_size) अणु
		पूर्णांक val = opt->frag_max_size;

		put_cmsg(msg, SOL_IPV6, IPV6_RECVFRAGSIZE, माप(val), &val);
	पूर्ण
पूर्ण

व्योम ip6_datagram_recv_ctl(काष्ठा sock *sk, काष्ठा msghdr *msg,
			  काष्ठा sk_buff *skb)
अणु
	ip6_datagram_recv_common_ctl(sk, msg, skb);
	ip6_datagram_recv_specअगरic_ctl(sk, msg, skb);
पूर्ण
EXPORT_SYMBOL_GPL(ip6_datagram_recv_ctl);

पूर्णांक ip6_datagram_send_ctl(काष्ठा net *net, काष्ठा sock *sk,
			  काष्ठा msghdr *msg, काष्ठा flowi6 *fl6,
			  काष्ठा ipcm6_cookie *ipc6)
अणु
	काष्ठा in6_pktinfo *src_info;
	काष्ठा cmsghdr *cmsg;
	काष्ठा ipv6_rt_hdr *rthdr;
	काष्ठा ipv6_opt_hdr *hdr;
	काष्ठा ipv6_txoptions *opt = ipc6->opt;
	पूर्णांक len;
	पूर्णांक err = 0;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		पूर्णांक addr_type;

		अगर (!CMSG_OK(msg, cmsg)) अणु
			err = -EINVAL;
			जाओ निकास_f;
		पूर्ण

		अगर (cmsg->cmsg_level == SOL_SOCKET) अणु
			err = __sock_cmsg_send(sk, msg, cmsg, &ipc6->sockc);
			अगर (err)
				वापस err;
			जारी;
		पूर्ण

		अगर (cmsg->cmsg_level != SOL_IPV6)
			जारी;

		चयन (cmsg->cmsg_type) अणु
		हाल IPV6_PKTINFO:
		हाल IPV6_2292PKTINFO:
		    अणु
			काष्ठा net_device *dev = शून्य;
			पूर्णांक src_idx;

			अगर (cmsg->cmsg_len < CMSG_LEN(माप(काष्ठा in6_pktinfo))) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			src_info = (काष्ठा in6_pktinfo *)CMSG_DATA(cmsg);
			src_idx = src_info->ipi6_अगरindex;

			अगर (src_idx) अणु
				अगर (fl6->flowi6_oअगर &&
				    src_idx != fl6->flowi6_oअगर &&
				    (sk->sk_bound_dev_अगर != fl6->flowi6_oअगर ||
				     !sk_dev_equal_l3scope(sk, src_idx)))
					वापस -EINVAL;
				fl6->flowi6_oअगर = src_idx;
			पूर्ण

			addr_type = __ipv6_addr_type(&src_info->ipi6_addr);

			rcu_पढ़ो_lock();
			अगर (fl6->flowi6_oअगर) अणु
				dev = dev_get_by_index_rcu(net, fl6->flowi6_oअगर);
				अगर (!dev) अणु
					rcu_पढ़ो_unlock();
					वापस -ENODEV;
				पूर्ण
			पूर्ण अन्यथा अगर (addr_type & IPV6_ADDR_LINKLOCAL) अणु
				rcu_पढ़ो_unlock();
				वापस -EINVAL;
			पूर्ण

			अगर (addr_type != IPV6_ADDR_ANY) अणु
				पूर्णांक strict = __ipv6_addr_src_scope(addr_type) <= IPV6_ADDR_SCOPE_LINKLOCAL;
				अगर (!ipv6_can_nonlocal_bind(net, inet_sk(sk)) &&
				    !ipv6_chk_addr_and_flags(net, &src_info->ipi6_addr,
							     dev, !strict, 0,
							     IFA_F_TENTATIVE) &&
				    !ipv6_chk_acast_addr_src(net, dev,
							     &src_info->ipi6_addr))
					err = -EINVAL;
				अन्यथा
					fl6->saddr = src_info->ipi6_addr;
			पूर्ण

			rcu_पढ़ो_unlock();

			अगर (err)
				जाओ निकास_f;

			अवरोध;
		    पूर्ण

		हाल IPV6_FLOWINFO:
			अगर (cmsg->cmsg_len < CMSG_LEN(4)) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			अगर (fl6->flowlabel&IPV6_FLOWINFO_MASK) अणु
				अगर ((fl6->flowlabel^*(__be32 *)CMSG_DATA(cmsg))&~IPV6_FLOWINFO_MASK) अणु
					err = -EINVAL;
					जाओ निकास_f;
				पूर्ण
			पूर्ण
			fl6->flowlabel = IPV6_FLOWINFO_MASK & *(__be32 *)CMSG_DATA(cmsg);
			अवरोध;

		हाल IPV6_2292HOPOPTS:
		हाल IPV6_HOPOPTS:
			अगर (opt->hopopt || cmsg->cmsg_len < CMSG_LEN(माप(काष्ठा ipv6_opt_hdr))) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			hdr = (काष्ठा ipv6_opt_hdr *)CMSG_DATA(cmsg);
			len = ((hdr->hdrlen + 1) << 3);
			अगर (cmsg->cmsg_len < CMSG_LEN(len)) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण
			अगर (!ns_capable(net->user_ns, CAP_NET_RAW)) अणु
				err = -EPERM;
				जाओ निकास_f;
			पूर्ण
			opt->opt_nflen += len;
			opt->hopopt = hdr;
			अवरोध;

		हाल IPV6_2292DSTOPTS:
			अगर (cmsg->cmsg_len < CMSG_LEN(माप(काष्ठा ipv6_opt_hdr))) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			hdr = (काष्ठा ipv6_opt_hdr *)CMSG_DATA(cmsg);
			len = ((hdr->hdrlen + 1) << 3);
			अगर (cmsg->cmsg_len < CMSG_LEN(len)) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण
			अगर (!ns_capable(net->user_ns, CAP_NET_RAW)) अणु
				err = -EPERM;
				जाओ निकास_f;
			पूर्ण
			अगर (opt->dst1opt) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण
			opt->opt_flen += len;
			opt->dst1opt = hdr;
			अवरोध;

		हाल IPV6_DSTOPTS:
		हाल IPV6_RTHDRDSTOPTS:
			अगर (cmsg->cmsg_len < CMSG_LEN(माप(काष्ठा ipv6_opt_hdr))) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			hdr = (काष्ठा ipv6_opt_hdr *)CMSG_DATA(cmsg);
			len = ((hdr->hdrlen + 1) << 3);
			अगर (cmsg->cmsg_len < CMSG_LEN(len)) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण
			अगर (!ns_capable(net->user_ns, CAP_NET_RAW)) अणु
				err = -EPERM;
				जाओ निकास_f;
			पूर्ण
			अगर (cmsg->cmsg_type == IPV6_DSTOPTS) अणु
				opt->opt_flen += len;
				opt->dst1opt = hdr;
			पूर्ण अन्यथा अणु
				opt->opt_nflen += len;
				opt->dst0opt = hdr;
			पूर्ण
			अवरोध;

		हाल IPV6_2292RTHDR:
		हाल IPV6_RTHDR:
			अगर (cmsg->cmsg_len < CMSG_LEN(माप(काष्ठा ipv6_rt_hdr))) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			rthdr = (काष्ठा ipv6_rt_hdr *)CMSG_DATA(cmsg);

			चयन (rthdr->type) अणु
#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
			हाल IPV6_SRCRT_TYPE_2:
				अगर (rthdr->hdrlen != 2 ||
				    rthdr->segments_left != 1) अणु
					err = -EINVAL;
					जाओ निकास_f;
				पूर्ण
				अवरोध;
#पूर्ण_अगर
			शेष:
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			len = ((rthdr->hdrlen + 1) << 3);

			अगर (cmsg->cmsg_len < CMSG_LEN(len)) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			/* segments left must also match */
			अगर ((rthdr->hdrlen >> 1) != rthdr->segments_left) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			opt->opt_nflen += len;
			opt->srcrt = rthdr;

			अगर (cmsg->cmsg_type == IPV6_2292RTHDR && opt->dst1opt) अणु
				पूर्णांक dsthdrlen = ((opt->dst1opt->hdrlen+1)<<3);

				opt->opt_nflen += dsthdrlen;
				opt->dst0opt = opt->dst1opt;
				opt->dst1opt = शून्य;
				opt->opt_flen -= dsthdrlen;
			पूर्ण

			अवरोध;

		हाल IPV6_2292HOPLIMIT:
		हाल IPV6_HOPLIMIT:
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(पूर्णांक))) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			ipc6->hlimit = *(पूर्णांक *)CMSG_DATA(cmsg);
			अगर (ipc6->hlimit < -1 || ipc6->hlimit > 0xff) अणु
				err = -EINVAL;
				जाओ निकास_f;
			पूर्ण

			अवरोध;

		हाल IPV6_TCLASS:
		    अणु
			पूर्णांक tc;

			err = -EINVAL;
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(पूर्णांक)))
				जाओ निकास_f;

			tc = *(पूर्णांक *)CMSG_DATA(cmsg);
			अगर (tc < -1 || tc > 0xff)
				जाओ निकास_f;

			err = 0;
			ipc6->tclass = tc;

			अवरोध;
		    पूर्ण

		हाल IPV6_DONTFRAG:
		    अणु
			पूर्णांक df;

			err = -EINVAL;
			अगर (cmsg->cmsg_len != CMSG_LEN(माप(पूर्णांक)))
				जाओ निकास_f;

			df = *(पूर्णांक *)CMSG_DATA(cmsg);
			अगर (df < 0 || df > 1)
				जाओ निकास_f;

			err = 0;
			ipc6->करोntfrag = df;

			अवरोध;
		    पूर्ण
		शेष:
			net_dbg_ratelimited("invalid cmsg type: %d\n",
					    cmsg->cmsg_type);
			err = -EINVAL;
			जाओ निकास_f;
		पूर्ण
	पूर्ण

निकास_f:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ip6_datagram_send_ctl);

व्योम __ip6_dgram_sock_seq_show(काष्ठा seq_file *seq, काष्ठा sock *sp,
			       __u16 srcp, __u16 destp, पूर्णांक rqueue, पूर्णांक bucket)
अणु
	स्थिर काष्ठा in6_addr *dest, *src;

	dest  = &sp->sk_v6_daddr;
	src   = &sp->sk_v6_rcv_saddr;
	seq_म_लिखो(seq,
		   "%5d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
		   "%02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d %pK %u\n",
		   bucket,
		   src->s6_addr32[0], src->s6_addr32[1],
		   src->s6_addr32[2], src->s6_addr32[3], srcp,
		   dest->s6_addr32[0], dest->s6_addr32[1],
		   dest->s6_addr32[2], dest->s6_addr32[3], destp,
		   sp->sk_state,
		   sk_wmem_alloc_get(sp),
		   rqueue,
		   0, 0L, 0,
		   from_kuid_munged(seq_user_ns(seq), sock_i_uid(sp)),
		   0,
		   sock_i_ino(sp),
		   refcount_पढ़ो(&sp->sk_refcnt), sp,
		   atomic_पढ़ो(&sp->sk_drops));
पूर्ण
