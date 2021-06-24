<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	UDP over IPv6
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *
 *	Based on linux/ipv4/udp.c
 *
 *	Fixes:
 *	Hideaki YOSHIFUJI	:	sin6_scope_id support
 *	YOSHIFUJI Hideaki @USAGI and:	Support IPV6_V6ONLY socket option, which
 *	Alexey Kuznetsov		allow both IPv4 and IPv6 sockets to bind
 *					a single port at the same समय.
 *      Kazunori MIYAZAWA @USAGI:       change process style to use ip6_append_data
 *      YOSHIFUJI Hideaki @USAGI:	convert /proc/net/udp6 to seq_file.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश <net/addrconf.h>
#समावेश <net/ndisc.h>
#समावेश <net/protocol.h>
#समावेश <net/transp_v6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/raw.h>
#समावेश <net/tcp_states.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/ip6_tunnel.h>
#समावेश <net/xfrm.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/busy_poll.h>
#समावेश <net/sock_reuseport.h>

#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <trace/events/skb.h>
#समावेश "udp_impl.h"

अटल u32 udp6_ehashfn(स्थिर काष्ठा net *net,
			स्थिर काष्ठा in6_addr *laddr,
			स्थिर u16 lport,
			स्थिर काष्ठा in6_addr *faddr,
			स्थिर __be16 fport)
अणु
	अटल u32 udp6_ehash_secret __पढ़ो_mostly;
	अटल u32 udp_ipv6_hash_secret __पढ़ो_mostly;

	u32 lhash, fhash;

	net_get_अक्रमom_once(&udp6_ehash_secret,
			    माप(udp6_ehash_secret));
	net_get_अक्रमom_once(&udp_ipv6_hash_secret,
			    माप(udp_ipv6_hash_secret));

	lhash = (__क्रमce u32)laddr->s6_addr32[3];
	fhash = __ipv6_addr_jhash(faddr, udp_ipv6_hash_secret);

	वापस __inet6_ehashfn(lhash, lport, fhash, fport,
			       udp_ipv6_hash_secret + net_hash_mix(net));
पूर्ण

पूर्णांक udp_v6_get_port(काष्ठा sock *sk, अचिन्हित लघु snum)
अणु
	अचिन्हित पूर्णांक hash2_nulladdr =
		ipv6_portaddr_hash(sock_net(sk), &in6addr_any, snum);
	अचिन्हित पूर्णांक hash2_partial =
		ipv6_portaddr_hash(sock_net(sk), &sk->sk_v6_rcv_saddr, 0);

	/* precompute partial secondary hash */
	udp_sk(sk)->udp_portaddr_hash = hash2_partial;
	वापस udp_lib_get_port(sk, snum, hash2_nulladdr);
पूर्ण

व्योम udp_v6_rehash(काष्ठा sock *sk)
अणु
	u16 new_hash = ipv6_portaddr_hash(sock_net(sk),
					  &sk->sk_v6_rcv_saddr,
					  inet_sk(sk)->inet_num);

	udp_lib_rehash(sk, new_hash);
पूर्ण

अटल पूर्णांक compute_score(काष्ठा sock *sk, काष्ठा net *net,
			 स्थिर काष्ठा in6_addr *saddr, __be16 sport,
			 स्थिर काष्ठा in6_addr *daddr, अचिन्हित लघु hnum,
			 पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
	पूर्णांक score;
	काष्ठा inet_sock *inet;
	bool dev_match;

	अगर (!net_eq(sock_net(sk), net) ||
	    udp_sk(sk)->udp_port_hash != hnum ||
	    sk->sk_family != PF_INET6)
		वापस -1;

	अगर (!ipv6_addr_equal(&sk->sk_v6_rcv_saddr, daddr))
		वापस -1;

	score = 0;
	inet = inet_sk(sk);

	अगर (inet->inet_dport) अणु
		अगर (inet->inet_dport != sport)
			वापस -1;
		score++;
	पूर्ण

	अगर (!ipv6_addr_any(&sk->sk_v6_daddr)) अणु
		अगर (!ipv6_addr_equal(&sk->sk_v6_daddr, saddr))
			वापस -1;
		score++;
	पूर्ण

	dev_match = udp_sk_bound_dev_eq(net, sk->sk_bound_dev_अगर, dअगर, sdअगर);
	अगर (!dev_match)
		वापस -1;
	score++;

	अगर (READ_ONCE(sk->sk_incoming_cpu) == raw_smp_processor_id())
		score++;

	वापस score;
पूर्ण

अटल काष्ठा sock *lookup_reuseport(काष्ठा net *net, काष्ठा sock *sk,
				     काष्ठा sk_buff *skb,
				     स्थिर काष्ठा in6_addr *saddr,
				     __be16 sport,
				     स्थिर काष्ठा in6_addr *daddr,
				     अचिन्हित पूर्णांक hnum)
अणु
	काष्ठा sock *reuse_sk = शून्य;
	u32 hash;

	अगर (sk->sk_reuseport && sk->sk_state != TCP_ESTABLISHED) अणु
		hash = udp6_ehashfn(net, daddr, hnum, saddr, sport);
		reuse_sk = reuseport_select_sock(sk, hash, skb,
						 माप(काष्ठा udphdr));
	पूर्ण
	वापस reuse_sk;
पूर्ण

/* called with rcu_पढ़ो_lock() */
अटल काष्ठा sock *udp6_lib_lookup2(काष्ठा net *net,
		स्थिर काष्ठा in6_addr *saddr, __be16 sport,
		स्थिर काष्ठा in6_addr *daddr, अचिन्हित पूर्णांक hnum,
		पूर्णांक dअगर, पूर्णांक sdअगर, काष्ठा udp_hslot *hslot2,
		काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk, *result;
	पूर्णांक score, badness;

	result = शून्य;
	badness = -1;
	udp_portaddr_क्रम_each_entry_rcu(sk, &hslot2->head) अणु
		score = compute_score(sk, net, saddr, sport,
				      daddr, hnum, dअगर, sdअगर);
		अगर (score > badness) अणु
			result = lookup_reuseport(net, sk, skb,
						  saddr, sport, daddr, hnum);
			/* Fall back to scoring अगर group has connections */
			अगर (result && !reuseport_has_conns(sk, false))
				वापस result;

			result = result ? : sk;
			badness = score;
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

अटल अंतरभूत काष्ठा sock *udp6_lookup_run_bpf(काष्ठा net *net,
					       काष्ठा udp_table *udptable,
					       काष्ठा sk_buff *skb,
					       स्थिर काष्ठा in6_addr *saddr,
					       __be16 sport,
					       स्थिर काष्ठा in6_addr *daddr,
					       u16 hnum)
अणु
	काष्ठा sock *sk, *reuse_sk;
	bool no_reuseport;

	अगर (udptable != &udp_table)
		वापस शून्य; /* only UDP is supported */

	no_reuseport = bpf_sk_lookup_run_v6(net, IPPROTO_UDP,
					    saddr, sport, daddr, hnum, &sk);
	अगर (no_reuseport || IS_ERR_OR_शून्य(sk))
		वापस sk;

	reuse_sk = lookup_reuseport(net, sk, skb, saddr, sport, daddr, hnum);
	अगर (reuse_sk)
		sk = reuse_sk;
	वापस sk;
पूर्ण

/* rcu_पढ़ो_lock() must be held */
काष्ठा sock *__udp6_lib_lookup(काष्ठा net *net,
			       स्थिर काष्ठा in6_addr *saddr, __be16 sport,
			       स्थिर काष्ठा in6_addr *daddr, __be16 dport,
			       पूर्णांक dअगर, पूर्णांक sdअगर, काष्ठा udp_table *udptable,
			       काष्ठा sk_buff *skb)
अणु
	अचिन्हित लघु hnum = ntohs(dport);
	अचिन्हित पूर्णांक hash2, slot2;
	काष्ठा udp_hslot *hslot2;
	काष्ठा sock *result, *sk;

	hash2 = ipv6_portaddr_hash(net, daddr, hnum);
	slot2 = hash2 & udptable->mask;
	hslot2 = &udptable->hash2[slot2];

	/* Lookup connected or non-wildcard sockets */
	result = udp6_lib_lookup2(net, saddr, sport,
				  daddr, hnum, dअगर, sdअगर,
				  hslot2, skb);
	अगर (!IS_ERR_OR_शून्य(result) && result->sk_state == TCP_ESTABLISHED)
		जाओ करोne;

	/* Lookup redirect from BPF */
	अगर (अटल_branch_unlikely(&bpf_sk_lookup_enabled)) अणु
		sk = udp6_lookup_run_bpf(net, udptable, skb,
					 saddr, sport, daddr, hnum);
		अगर (sk) अणु
			result = sk;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* Got non-wildcard socket or error on first lookup */
	अगर (result)
		जाओ करोne;

	/* Lookup wildcard sockets */
	hash2 = ipv6_portaddr_hash(net, &in6addr_any, hnum);
	slot2 = hash2 & udptable->mask;
	hslot2 = &udptable->hash2[slot2];

	result = udp6_lib_lookup2(net, saddr, sport,
				  &in6addr_any, hnum, dअगर, sdअगर,
				  hslot2, skb);
करोne:
	अगर (IS_ERR(result))
		वापस शून्य;
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(__udp6_lib_lookup);

अटल काष्ठा sock *__udp6_lib_lookup_skb(काष्ठा sk_buff *skb,
					  __be16 sport, __be16 dport,
					  काष्ठा udp_table *udptable)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);

	वापस __udp6_lib_lookup(dev_net(skb->dev), &iph->saddr, sport,
				 &iph->daddr, dport, inet6_iअगर(skb),
				 inet6_sdअगर(skb), udptable, skb);
पूर्ण

काष्ठा sock *udp6_lib_lookup_skb(स्थिर काष्ठा sk_buff *skb,
				 __be16 sport, __be16 dport)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);

	वापस __udp6_lib_lookup(dev_net(skb->dev), &iph->saddr, sport,
				 &iph->daddr, dport, inet6_iअगर(skb),
				 inet6_sdअगर(skb), &udp_table, शून्य);
पूर्ण

/* Must be called under rcu_पढ़ो_lock().
 * Does increment socket refcount.
 */
#अगर IS_ENABLED(CONFIG_NF_TPROXY_IPV6) || IS_ENABLED(CONFIG_NF_SOCKET_IPV6)
काष्ठा sock *udp6_lib_lookup(काष्ठा net *net, स्थिर काष्ठा in6_addr *saddr, __be16 sport,
			     स्थिर काष्ठा in6_addr *daddr, __be16 dport, पूर्णांक dअगर)
अणु
	काष्ठा sock *sk;

	sk =  __udp6_lib_lookup(net, saddr, sport, daddr, dport,
				dअगर, 0, &udp_table, शून्य);
	अगर (sk && !refcount_inc_not_zero(&sk->sk_refcnt))
		sk = शून्य;
	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(udp6_lib_lookup);
#पूर्ण_अगर

/* करो not use the scratch area len क्रम jumbogram: their length execeeds the
 * scratch area space; note that the IP6CB flags is still in the first
 * cacheline, so checking क्रम jumbograms is cheap
 */
अटल पूर्णांक udp6_skb_len(काष्ठा sk_buff *skb)
अणु
	वापस unlikely(inet6_is_jumbogram(skb)) ? skb->len : udp_skb_len(skb);
पूर्ण

/*
 *	This should be easy, अगर there is something there we
 *	वापस it, otherwise we block.
 */

पूर्णांक udpv6_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
		  पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक ulen, copied;
	पूर्णांक off, err, peeking = flags & MSG_PEEK;
	पूर्णांक is_udplite = IS_UDPLITE(sk);
	काष्ठा udp_mib __percpu *mib;
	bool checksum_valid = false;
	पूर्णांक is_udp4;

	अगर (flags & MSG_ERRQUEUE)
		वापस ipv6_recv_error(sk, msg, len, addr_len);

	अगर (np->rxpmtu && np->rxopt.bits.rxpmtu)
		वापस ipv6_recv_rxpmtu(sk, msg, len, addr_len);

try_again:
	off = sk_peek_offset(sk, flags);
	skb = __skb_recv_udp(sk, flags, noblock, &off, &err);
	अगर (!skb)
		वापस err;

	ulen = udp6_skb_len(skb);
	copied = len;
	अगर (copied > ulen - off)
		copied = ulen - off;
	अन्यथा अगर (copied < ulen)
		msg->msg_flags |= MSG_TRUNC;

	is_udp4 = (skb->protocol == htons(ETH_P_IP));
	mib = __UDPX_MIB(sk, is_udp4);

	/*
	 * If checksum is needed at all, try to करो it जबतक copying the
	 * data.  If the data is truncated, or अगर we only want a partial
	 * coverage checksum (UDP-Lite), करो it beक्रमe the copy.
	 */

	अगर (copied < ulen || peeking ||
	    (is_udplite && UDP_SKB_CB(skb)->partial_cov)) अणु
		checksum_valid = udp_skb_csum_unnecessary(skb) ||
				!__udp_lib_checksum_complete(skb);
		अगर (!checksum_valid)
			जाओ csum_copy_err;
	पूर्ण

	अगर (checksum_valid || udp_skb_csum_unnecessary(skb)) अणु
		अगर (udp_skb_is_linear(skb))
			err = copy_linear_skb(skb, copied, off, &msg->msg_iter);
		अन्यथा
			err = skb_copy_datagram_msg(skb, off, msg, copied);
	पूर्ण अन्यथा अणु
		err = skb_copy_and_csum_datagram_msg(skb, off, msg);
		अगर (err == -EINVAL)
			जाओ csum_copy_err;
	पूर्ण
	अगर (unlikely(err)) अणु
		अगर (!peeking) अणु
			atomic_inc(&sk->sk_drops);
			SNMP_INC_STATS(mib, UDP_MIB_INERRORS);
		पूर्ण
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण
	अगर (!peeking)
		SNMP_INC_STATS(mib, UDP_MIB_INDATAGRAMS);

	sock_recv_ts_and_drops(msg, sk, skb);

	/* Copy the address. */
	अगर (msg->msg_name) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, sin6, msg->msg_name);
		sin6->sin6_family = AF_INET6;
		sin6->sin6_port = udp_hdr(skb)->source;
		sin6->sin6_flowinfo = 0;

		अगर (is_udp4) अणु
			ipv6_addr_set_v4mapped(ip_hdr(skb)->saddr,
					       &sin6->sin6_addr);
			sin6->sin6_scope_id = 0;
		पूर्ण अन्यथा अणु
			sin6->sin6_addr = ipv6_hdr(skb)->saddr;
			sin6->sin6_scope_id =
				ipv6_अगरace_scope_id(&sin6->sin6_addr,
						    inet6_iअगर(skb));
		पूर्ण
		*addr_len = माप(*sin6);

		BPF_CGROUP_RUN_PROG_UDP6_RECVMSG_LOCK(sk,
						      (काष्ठा sockaddr *)sin6);
	पूर्ण

	अगर (udp_sk(sk)->gro_enabled)
		udp_cmsg_recv(msg, sk, skb);

	अगर (np->rxopt.all)
		ip6_datagram_recv_common_ctl(sk, msg, skb);

	अगर (is_udp4) अणु
		अगर (inet->cmsg_flags)
			ip_cmsg_recv_offset(msg, sk, skb,
					    माप(काष्ठा udphdr), off);
	पूर्ण अन्यथा अणु
		अगर (np->rxopt.all)
			ip6_datagram_recv_specअगरic_ctl(sk, msg, skb);
	पूर्ण

	err = copied;
	अगर (flags & MSG_TRUNC)
		err = ulen;

	skb_consume_udp(sk, skb, peeking ? -err : err);
	वापस err;

csum_copy_err:
	अगर (!__sk_queue_drop_skb(sk, &udp_sk(sk)->पढ़ोer_queue, skb, flags,
				 udp_skb_deकाष्ठाor)) अणु
		SNMP_INC_STATS(mib, UDP_MIB_CSUMERRORS);
		SNMP_INC_STATS(mib, UDP_MIB_INERRORS);
	पूर्ण
	kमुक्त_skb(skb);

	/* starting over क्रम a new packet, but check अगर we need to yield */
	cond_resched();
	msg->msg_flags &= ~MSG_TRUNC;
	जाओ try_again;
पूर्ण

DEFINE_STATIC_KEY_FALSE(udpv6_encap_needed_key);
व्योम udpv6_encap_enable(व्योम)
अणु
	अटल_branch_inc(&udpv6_encap_needed_key);
पूर्ण
EXPORT_SYMBOL(udpv6_encap_enable);

/* Handler क्रम tunnels with arbitrary destination ports: no socket lookup, go
 * through error handlers in encapsulations looking क्रम a match.
 */
अटल पूर्णांक __udp6_lib_err_encap_no_sk(काष्ठा sk_buff *skb,
				      काष्ठा inet6_skb_parm *opt,
				      u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_IPTUN_ENCAP_OPS; i++) अणु
		पूर्णांक (*handler)(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
			       u8 type, u8 code, पूर्णांक offset, __be32 info);
		स्थिर काष्ठा ip6_tnl_encap_ops *encap;

		encap = rcu_dereference(ip6tun_encaps[i]);
		अगर (!encap)
			जारी;
		handler = encap->err_handler;
		अगर (handler && !handler(skb, opt, type, code, offset, info))
			वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/* Try to match ICMP errors to UDP tunnels by looking up a socket without
 * reversing source and destination port: this will match tunnels that क्रमce the
 * same destination port on both endpoपूर्णांकs (e.g. VXLAN, GENEVE). Note that
 * lwtunnels might actually अवरोध this assumption by being configured with
 * dअगरferent destination ports on endpoपूर्णांकs, in this हाल we won't be able to
 * trace ICMP messages back to them.
 *
 * If this करोesn't match any socket, probe tunnels with arbitrary destination
 * ports (e.g. FoU, GUE): there, the receiving socket is useless, as the port
 * we've sent packets to won't necessarily match the local destination port.
 *
 * Then ask the tunnel implementation to match the error against a valid
 * association.
 *
 * Return an error अगर we can't find a match, the socket अगर we need further
 * processing, zero otherwise.
 */
अटल काष्ठा sock *__udp6_lib_err_encap(काष्ठा net *net,
					 स्थिर काष्ठा ipv6hdr *hdr, पूर्णांक offset,
					 काष्ठा udphdr *uh,
					 काष्ठा udp_table *udptable,
					 काष्ठा sk_buff *skb,
					 काष्ठा inet6_skb_parm *opt,
					 u8 type, u8 code, __be32 info)
अणु
	पूर्णांक network_offset, transport_offset;
	काष्ठा sock *sk;

	network_offset = skb_network_offset(skb);
	transport_offset = skb_transport_offset(skb);

	/* Network header needs to poपूर्णांक to the outer IPv6 header inside ICMP */
	skb_reset_network_header(skb);

	/* Transport header needs to poपूर्णांक to the UDP header */
	skb_set_transport_header(skb, offset);

	sk = __udp6_lib_lookup(net, &hdr->daddr, uh->source,
			       &hdr->saddr, uh->dest,
			       inet6_iअगर(skb), 0, udptable, skb);
	अगर (sk) अणु
		पूर्णांक (*lookup)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
		काष्ठा udp_sock *up = udp_sk(sk);

		lookup = READ_ONCE(up->encap_err_lookup);
		अगर (!lookup || lookup(sk, skb))
			sk = शून्य;
	पूर्ण

	अगर (!sk) अणु
		sk = ERR_PTR(__udp6_lib_err_encap_no_sk(skb, opt, type, code,
							offset, info));
	पूर्ण

	skb_set_transport_header(skb, transport_offset);
	skb_set_network_header(skb, network_offset);

	वापस sk;
पूर्ण

पूर्णांक __udp6_lib_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
		   u8 type, u8 code, पूर्णांक offset, __be32 info,
		   काष्ठा udp_table *udptable)
अणु
	काष्ठा ipv6_pinfo *np;
	स्थिर काष्ठा ipv6hdr *hdr = (स्थिर काष्ठा ipv6hdr *)skb->data;
	स्थिर काष्ठा in6_addr *saddr = &hdr->saddr;
	स्थिर काष्ठा in6_addr *daddr = &hdr->daddr;
	काष्ठा udphdr *uh = (काष्ठा udphdr *)(skb->data+offset);
	bool tunnel = false;
	काष्ठा sock *sk;
	पूर्णांक harderr;
	पूर्णांक err;
	काष्ठा net *net = dev_net(skb->dev);

	sk = __udp6_lib_lookup(net, daddr, uh->dest, saddr, uh->source,
			       inet6_iअगर(skb), inet6_sdअगर(skb), udptable, शून्य);
	अगर (!sk || udp_sk(sk)->encap_type) अणु
		/* No socket क्रम error: try tunnels beक्रमe discarding */
		sk = ERR_PTR(-ENOENT);
		अगर (अटल_branch_unlikely(&udpv6_encap_needed_key)) अणु
			sk = __udp6_lib_err_encap(net, hdr, offset, uh,
						  udptable, skb,
						  opt, type, code, info);
			अगर (!sk)
				वापस 0;
		पूर्ण

		अगर (IS_ERR(sk)) अणु
			__ICMP6_INC_STATS(net, __in6_dev_get(skb->dev),
					  ICMP6_MIB_INERRORS);
			वापस PTR_ERR(sk);
		पूर्ण

		tunnel = true;
	पूर्ण

	harderr = icmpv6_err_convert(type, code, &err);
	np = inet6_sk(sk);

	अगर (type == ICMPV6_PKT_TOOBIG) अणु
		अगर (!ip6_sk_accept_pmtu(sk))
			जाओ out;
		ip6_sk_update_pmtu(skb, sk, info);
		अगर (np->pmtudisc != IPV6_PMTUDISC_DONT)
			harderr = 1;
	पूर्ण
	अगर (type == NDISC_REसूचीECT) अणु
		अगर (tunnel) अणु
			ip6_redirect(skb, sock_net(sk), inet6_iअगर(skb),
				     sk->sk_mark, sk->sk_uid);
		पूर्ण अन्यथा अणु
			ip6_sk_redirect(skb, sk);
		पूर्ण
		जाओ out;
	पूर्ण

	/* Tunnels करोn't have an application socket: don't pass errors back */
	अगर (tunnel)
		जाओ out;

	अगर (!np->recverr) अणु
		अगर (!harderr || sk->sk_state != TCP_ESTABLISHED)
			जाओ out;
	पूर्ण अन्यथा अणु
		ipv6_icmp_error(sk, skb, err, uh->dest, ntohl(info), (u8 *)(uh+1));
	पूर्ण

	sk->sk_err = err;
	sk->sk_error_report(sk);
out:
	वापस 0;
पूर्ण

अटल पूर्णांक __udpv6_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;

	अगर (!ipv6_addr_any(&sk->sk_v6_daddr)) अणु
		sock_rps_save_rxhash(sk, skb);
		sk_mark_napi_id(sk, skb);
		sk_incoming_cpu_update(sk);
	पूर्ण अन्यथा अणु
		sk_mark_napi_id_once(sk, skb);
	पूर्ण

	rc = __udp_enqueue_schedule_skb(sk, skb);
	अगर (rc < 0) अणु
		पूर्णांक is_udplite = IS_UDPLITE(sk);

		/* Note that an ENOMEM error is अक्षरged twice */
		अगर (rc == -ENOMEM)
			UDP6_INC_STATS(sock_net(sk),
					 UDP_MIB_RCVBUFERRORS, is_udplite);
		अन्यथा
			UDP6_INC_STATS(sock_net(sk),
				       UDP_MIB_MEMERRORS, is_udplite);
		UDP6_INC_STATS(sock_net(sk), UDP_MIB_INERRORS, is_udplite);
		kमुक्त_skb(skb);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक udpv6_err(काष्ठा sk_buff *skb,
				काष्ठा inet6_skb_parm *opt, u8 type,
				u8 code, पूर्णांक offset, __be32 info)
अणु
	वापस __udp6_lib_err(skb, opt, type, code, offset, info, &udp_table);
पूर्ण

अटल पूर्णांक udpv6_queue_rcv_one_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा udp_sock *up = udp_sk(sk);
	पूर्णांक is_udplite = IS_UDPLITE(sk);

	अगर (!xfrm6_policy_check(sk, XFRM_POLICY_IN, skb))
		जाओ drop;

	अगर (अटल_branch_unlikely(&udpv6_encap_needed_key) && up->encap_type) अणु
		पूर्णांक (*encap_rcv)(काष्ठा sock *sk, काष्ठा sk_buff *skb);

		/*
		 * This is an encapsulation socket so pass the skb to
		 * the socket's udp_encap_rcv() hook. Otherwise, just
		 * fall through and pass this up the UDP socket.
		 * up->encap_rcv() वापसs the following value:
		 * =0 अगर skb was successfully passed to the encap
		 *    handler or was discarded by it.
		 * >0 अगर skb should be passed on to UDP.
		 * <0 अगर skb should be resubmitted as proto -N
		 */

		/* अगर we're overly लघु, let UDP handle it */
		encap_rcv = READ_ONCE(up->encap_rcv);
		अगर (encap_rcv) अणु
			पूर्णांक ret;

			/* Verअगरy checksum beक्रमe giving to encap */
			अगर (udp_lib_checksum_complete(skb))
				जाओ csum_error;

			ret = encap_rcv(sk, skb);
			अगर (ret <= 0) अणु
				__UDP_INC_STATS(sock_net(sk),
						UDP_MIB_INDATAGRAMS,
						is_udplite);
				वापस -ret;
			पूर्ण
		पूर्ण

		/* FALLTHROUGH -- it's a UDP Packet */
	पूर्ण

	/*
	 * UDP-Lite specअगरic tests, ignored on UDP sockets (see net/ipv4/udp.c).
	 */
	अगर ((up->pcflag & UDPLITE_RECV_CC)  &&  UDP_SKB_CB(skb)->partial_cov) अणु

		अगर (up->pcrlen == 0) अणु          /* full coverage was set  */
			net_dbg_ratelimited("UDPLITE6: partial coverage %d while full coverage %d requested\n",
					    UDP_SKB_CB(skb)->cscov, skb->len);
			जाओ drop;
		पूर्ण
		अगर (UDP_SKB_CB(skb)->cscov  <  up->pcrlen) अणु
			net_dbg_ratelimited("UDPLITE6: coverage %d too small, need min %d\n",
					    UDP_SKB_CB(skb)->cscov, up->pcrlen);
			जाओ drop;
		पूर्ण
	पूर्ण

	prefetch(&sk->sk_rmem_alloc);
	अगर (rcu_access_poपूर्णांकer(sk->sk_filter) &&
	    udp_lib_checksum_complete(skb))
		जाओ csum_error;

	अगर (sk_filter_trim_cap(sk, skb, माप(काष्ठा udphdr)))
		जाओ drop;

	udp_csum_pull_header(skb);

	skb_dst_drop(skb);

	वापस __udpv6_queue_rcv_skb(sk, skb);

csum_error:
	__UDP6_INC_STATS(sock_net(sk), UDP_MIB_CSUMERRORS, is_udplite);
drop:
	__UDP6_INC_STATS(sock_net(sk), UDP_MIB_INERRORS, is_udplite);
	atomic_inc(&sk->sk_drops);
	kमुक्त_skb(skb);
	वापस -1;
पूर्ण

अटल पूर्णांक udpv6_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *next, *segs;
	पूर्णांक ret;

	अगर (likely(!udp_unexpected_gso(sk, skb)))
		वापस udpv6_queue_rcv_one_skb(sk, skb);

	__skb_push(skb, -skb_mac_offset(skb));
	segs = udp_rcv_segment(sk, skb, false);
	skb_list_walk_safe(segs, skb, next) अणु
		__skb_pull(skb, skb_transport_offset(skb));

		udp_post_segment_fix_csum(skb);
		ret = udpv6_queue_rcv_one_skb(sk, skb);
		अगर (ret > 0)
			ip6_protocol_deliver_rcu(dev_net(skb->dev), skb, ret,
						 true);
	पूर्ण
	वापस 0;
पूर्ण

अटल bool __udp_v6_is_mcast_sock(काष्ठा net *net, काष्ठा sock *sk,
				   __be16 loc_port, स्थिर काष्ठा in6_addr *loc_addr,
				   __be16 rmt_port, स्थिर काष्ठा in6_addr *rmt_addr,
				   पूर्णांक dअगर, पूर्णांक sdअगर, अचिन्हित लघु hnum)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	अगर (!net_eq(sock_net(sk), net))
		वापस false;

	अगर (udp_sk(sk)->udp_port_hash != hnum ||
	    sk->sk_family != PF_INET6 ||
	    (inet->inet_dport && inet->inet_dport != rmt_port) ||
	    (!ipv6_addr_any(&sk->sk_v6_daddr) &&
		    !ipv6_addr_equal(&sk->sk_v6_daddr, rmt_addr)) ||
	    !udp_sk_bound_dev_eq(net, sk->sk_bound_dev_अगर, dअगर, sdअगर) ||
	    (!ipv6_addr_any(&sk->sk_v6_rcv_saddr) &&
		    !ipv6_addr_equal(&sk->sk_v6_rcv_saddr, loc_addr)))
		वापस false;
	अगर (!inet6_mc_check(sk, loc_addr, rmt_addr))
		वापस false;
	वापस true;
पूर्ण

अटल व्योम udp6_csum_zero_error(काष्ठा sk_buff *skb)
अणु
	/* RFC 2460 section 8.1 says that we SHOULD log
	 * this error. Well, it is reasonable.
	 */
	net_dbg_ratelimited("IPv6: udp checksum is 0 for [%pI6c]:%u->[%pI6c]:%u\n",
			    &ipv6_hdr(skb)->saddr, ntohs(udp_hdr(skb)->source),
			    &ipv6_hdr(skb)->daddr, ntohs(udp_hdr(skb)->dest));
पूर्ण

/*
 * Note: called only from the BH handler context,
 * so we करोn't need to lock the hashes.
 */
अटल पूर्णांक __udp6_lib_mcast_deliver(काष्ठा net *net, काष्ठा sk_buff *skb,
		स्थिर काष्ठा in6_addr *saddr, स्थिर काष्ठा in6_addr *daddr,
		काष्ठा udp_table *udptable, पूर्णांक proto)
अणु
	काष्ठा sock *sk, *first = शून्य;
	स्थिर काष्ठा udphdr *uh = udp_hdr(skb);
	अचिन्हित लघु hnum = ntohs(uh->dest);
	काष्ठा udp_hslot *hslot = udp_hashslot(udptable, net, hnum);
	अचिन्हित पूर्णांक offset = दुरत्व(typeof(*sk), sk_node);
	अचिन्हित पूर्णांक hash2 = 0, hash2_any = 0, use_hash2 = (hslot->count > 10);
	पूर्णांक dअगर = inet6_iअगर(skb);
	पूर्णांक sdअगर = inet6_sdअगर(skb);
	काष्ठा hlist_node *node;
	काष्ठा sk_buff *nskb;

	अगर (use_hash2) अणु
		hash2_any = ipv6_portaddr_hash(net, &in6addr_any, hnum) &
			    udptable->mask;
		hash2 = ipv6_portaddr_hash(net, daddr, hnum) & udptable->mask;
start_lookup:
		hslot = &udptable->hash2[hash2];
		offset = दुरत्व(typeof(*sk), __sk_common.skc_portaddr_node);
	पूर्ण

	sk_क्रम_each_entry_offset_rcu(sk, node, &hslot->head, offset) अणु
		अगर (!__udp_v6_is_mcast_sock(net, sk, uh->dest, daddr,
					    uh->source, saddr, dअगर, sdअगर,
					    hnum))
			जारी;
		/* If zero checksum and no_check is not on क्रम
		 * the socket then skip it.
		 */
		अगर (!uh->check && !udp_sk(sk)->no_check6_rx)
			जारी;
		अगर (!first) अणु
			first = sk;
			जारी;
		पूर्ण
		nskb = skb_clone(skb, GFP_ATOMIC);
		अगर (unlikely(!nskb)) अणु
			atomic_inc(&sk->sk_drops);
			__UDP6_INC_STATS(net, UDP_MIB_RCVBUFERRORS,
					 IS_UDPLITE(sk));
			__UDP6_INC_STATS(net, UDP_MIB_INERRORS,
					 IS_UDPLITE(sk));
			जारी;
		पूर्ण

		अगर (udpv6_queue_rcv_skb(sk, nskb) > 0)
			consume_skb(nskb);
	पूर्ण

	/* Also lookup *:port अगर we are using hash2 and haven't करोne so yet. */
	अगर (use_hash2 && hash2 != hash2_any) अणु
		hash2 = hash2_any;
		जाओ start_lookup;
	पूर्ण

	अगर (first) अणु
		अगर (udpv6_queue_rcv_skb(first, skb) > 0)
			consume_skb(skb);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
		__UDP6_INC_STATS(net, UDP_MIB_IGNOREDMULTI,
				 proto == IPPROTO_UDPLITE);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम udp6_sk_rx_dst_set(काष्ठा sock *sk, काष्ठा dst_entry *dst)
अणु
	अगर (udp_sk_rx_dst_set(sk, dst)) अणु
		स्थिर काष्ठा rt6_info *rt = (स्थिर काष्ठा rt6_info *)dst;

		inet6_sk(sk)->rx_dst_cookie = rt6_get_cookie(rt);
	पूर्ण
पूर्ण

/* wrapper क्रम udp_queue_rcv_skb tacking care of csum conversion and
 * वापस code conversion क्रम ip layer consumption
 */
अटल पूर्णांक udp6_unicast_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				काष्ठा udphdr *uh)
अणु
	पूर्णांक ret;

	अगर (inet_get_convert_csum(sk) && uh->check && !IS_UDPLITE(sk))
		skb_checksum_try_convert(skb, IPPROTO_UDP, ip6_compute_pseuकरो);

	ret = udpv6_queue_rcv_skb(sk, skb);

	/* a वापस value > 0 means to resubmit the input */
	अगर (ret > 0)
		वापस ret;
	वापस 0;
पूर्ण

पूर्णांक __udp6_lib_rcv(काष्ठा sk_buff *skb, काष्ठा udp_table *udptable,
		   पूर्णांक proto)
अणु
	स्थिर काष्ठा in6_addr *saddr, *daddr;
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा udphdr *uh;
	काष्ठा sock *sk;
	bool refcounted;
	u32 ulen = 0;

	अगर (!pskb_may_pull(skb, माप(काष्ठा udphdr)))
		जाओ discard;

	saddr = &ipv6_hdr(skb)->saddr;
	daddr = &ipv6_hdr(skb)->daddr;
	uh = udp_hdr(skb);

	ulen = ntohs(uh->len);
	अगर (ulen > skb->len)
		जाओ लघु_packet;

	अगर (proto == IPPROTO_UDP) अणु
		/* UDP validates ulen. */

		/* Check क्रम jumbo payload */
		अगर (ulen == 0)
			ulen = skb->len;

		अगर (ulen < माप(*uh))
			जाओ लघु_packet;

		अगर (ulen < skb->len) अणु
			अगर (pskb_trim_rcsum(skb, ulen))
				जाओ लघु_packet;
			saddr = &ipv6_hdr(skb)->saddr;
			daddr = &ipv6_hdr(skb)->daddr;
			uh = udp_hdr(skb);
		पूर्ण
	पूर्ण

	अगर (udp6_csum_init(skb, uh, proto))
		जाओ csum_error;

	/* Check अगर the socket is alपढ़ोy available, e.g. due to early demux */
	sk = skb_steal_sock(skb, &refcounted);
	अगर (sk) अणु
		काष्ठा dst_entry *dst = skb_dst(skb);
		पूर्णांक ret;

		अगर (unlikely(sk->sk_rx_dst != dst))
			udp6_sk_rx_dst_set(sk, dst);

		अगर (!uh->check && !udp_sk(sk)->no_check6_rx) अणु
			अगर (refcounted)
				sock_put(sk);
			जाओ report_csum_error;
		पूर्ण

		ret = udp6_unicast_rcv_skb(sk, skb, uh);
		अगर (refcounted)
			sock_put(sk);
		वापस ret;
	पूर्ण

	/*
	 *	Multicast receive code
	 */
	अगर (ipv6_addr_is_multicast(daddr))
		वापस __udp6_lib_mcast_deliver(net, skb,
				saddr, daddr, udptable, proto);

	/* Unicast */
	sk = __udp6_lib_lookup_skb(skb, uh->source, uh->dest, udptable);
	अगर (sk) अणु
		अगर (!uh->check && !udp_sk(sk)->no_check6_rx)
			जाओ report_csum_error;
		वापस udp6_unicast_rcv_skb(sk, skb, uh);
	पूर्ण

	अगर (!uh->check)
		जाओ report_csum_error;

	अगर (!xfrm6_policy_check(शून्य, XFRM_POLICY_IN, skb))
		जाओ discard;

	अगर (udp_lib_checksum_complete(skb))
		जाओ csum_error;

	__UDP6_INC_STATS(net, UDP_MIB_NOPORTS, proto == IPPROTO_UDPLITE);
	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);

	kमुक्त_skb(skb);
	वापस 0;

लघु_packet:
	net_dbg_ratelimited("UDP%sv6: short packet: From [%pI6c]:%u %d/%d to [%pI6c]:%u\n",
			    proto == IPPROTO_UDPLITE ? "-Lite" : "",
			    saddr, ntohs(uh->source),
			    ulen, skb->len,
			    daddr, ntohs(uh->dest));
	जाओ discard;

report_csum_error:
	udp6_csum_zero_error(skb);
csum_error:
	__UDP6_INC_STATS(net, UDP_MIB_CSUMERRORS, proto == IPPROTO_UDPLITE);
discard:
	__UDP6_INC_STATS(net, UDP_MIB_INERRORS, proto == IPPROTO_UDPLITE);
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण


अटल काष्ठा sock *__udp6_lib_demux_lookup(काष्ठा net *net,
			__be16 loc_port, स्थिर काष्ठा in6_addr *loc_addr,
			__be16 rmt_port, स्थिर काष्ठा in6_addr *rmt_addr,
			पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
	अचिन्हित लघु hnum = ntohs(loc_port);
	अचिन्हित पूर्णांक hash2 = ipv6_portaddr_hash(net, loc_addr, hnum);
	अचिन्हित पूर्णांक slot2 = hash2 & udp_table.mask;
	काष्ठा udp_hslot *hslot2 = &udp_table.hash2[slot2];
	स्थिर __portpair ports = INET_COMBINED_PORTS(rmt_port, hnum);
	काष्ठा sock *sk;

	udp_portaddr_क्रम_each_entry_rcu(sk, &hslot2->head) अणु
		अगर (sk->sk_state == TCP_ESTABLISHED &&
		    INET6_MATCH(sk, net, rmt_addr, loc_addr, ports, dअगर, sdअगर))
			वापस sk;
		/* Only check first socket in chain */
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

INसूचीECT_CALLABLE_SCOPE व्योम udp_v6_early_demux(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	स्थिर काष्ठा udphdr *uh;
	काष्ठा sock *sk;
	काष्ठा dst_entry *dst;
	पूर्णांक dअगर = skb->dev->अगरindex;
	पूर्णांक sdअगर = inet6_sdअगर(skb);

	अगर (!pskb_may_pull(skb, skb_transport_offset(skb) +
	    माप(काष्ठा udphdr)))
		वापस;

	uh = udp_hdr(skb);

	अगर (skb->pkt_type == PACKET_HOST)
		sk = __udp6_lib_demux_lookup(net, uh->dest,
					     &ipv6_hdr(skb)->daddr,
					     uh->source, &ipv6_hdr(skb)->saddr,
					     dअगर, sdअगर);
	अन्यथा
		वापस;

	अगर (!sk || !refcount_inc_not_zero(&sk->sk_refcnt))
		वापस;

	skb->sk = sk;
	skb->deकाष्ठाor = sock_eमुक्त;
	dst = READ_ONCE(sk->sk_rx_dst);

	अगर (dst)
		dst = dst_check(dst, inet6_sk(sk)->rx_dst_cookie);
	अगर (dst) अणु
		/* set noref क्रम now.
		 * any place which wants to hold dst has to call
		 * dst_hold_safe()
		 */
		skb_dst_set_noref(skb, dst);
	पूर्ण
पूर्ण

INसूचीECT_CALLABLE_SCOPE पूर्णांक udpv6_rcv(काष्ठा sk_buff *skb)
अणु
	वापस __udp6_lib_rcv(skb, &udp_table, IPPROTO_UDP);
पूर्ण

/*
 * Throw away all pending data and cancel the corking. Socket is locked.
 */
अटल व्योम udp_v6_flush_pending_frames(काष्ठा sock *sk)
अणु
	काष्ठा udp_sock *up = udp_sk(sk);

	अगर (up->pending == AF_INET)
		udp_flush_pending_frames(sk);
	अन्यथा अगर (up->pending) अणु
		up->len = 0;
		up->pending = 0;
		ip6_flush_pending_frames(sk);
	पूर्ण
पूर्ण

अटल पूर्णांक udpv6_pre_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr,
			     पूर्णांक addr_len)
अणु
	अगर (addr_len < दुरत्वend(काष्ठा sockaddr, sa_family))
		वापस -EINVAL;
	/* The following checks are replicated from __ip6_datagram_connect()
	 * and पूर्णांकended to prevent BPF program called below from accessing
	 * bytes that are out of the bound specअगरied by user in addr_len.
	 */
	अगर (uaddr->sa_family == AF_INET) अणु
		अगर (__ipv6_only_sock(sk))
			वापस -EAFNOSUPPORT;
		वापस udp_pre_connect(sk, uaddr, addr_len);
	पूर्ण

	अगर (addr_len < SIN6_LEN_RFC2133)
		वापस -EINVAL;

	वापस BPF_CGROUP_RUN_PROG_INET6_CONNECT_LOCK(sk, uaddr);
पूर्ण

/**
 *	udp6_hwcsum_outgoing  -  handle outgoing HW checksumming
 *	@sk:	socket we are sending on
 *	@skb:	sk_buff containing the filled-in UDP header
 *		(checksum field must be zeroed out)
 *	@saddr: source address
 *	@daddr: destination address
 *	@len:	length of packet
 */
अटल व्योम udp6_hwcsum_outgoing(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				 स्थिर काष्ठा in6_addr *saddr,
				 स्थिर काष्ठा in6_addr *daddr, पूर्णांक len)
अणु
	अचिन्हित पूर्णांक offset;
	काष्ठा udphdr *uh = udp_hdr(skb);
	काष्ठा sk_buff *frags = skb_shinfo(skb)->frag_list;
	__wsum csum = 0;

	अगर (!frags) अणु
		/* Only one fragment on the socket.  */
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = दुरत्व(काष्ठा udphdr, check);
		uh->check = ~csum_ipv6_magic(saddr, daddr, len, IPPROTO_UDP, 0);
	पूर्ण अन्यथा अणु
		/*
		 * HW-checksum won't work as there are two or more
		 * fragments on the socket so that all csums of sk_buffs
		 * should be together
		 */
		offset = skb_transport_offset(skb);
		skb->csum = skb_checksum(skb, offset, skb->len - offset, 0);
		csum = skb->csum;

		skb->ip_summed = CHECKSUM_NONE;

		करो अणु
			csum = csum_add(csum, frags->csum);
		पूर्ण जबतक ((frags = frags->next));

		uh->check = csum_ipv6_magic(saddr, daddr, len, IPPROTO_UDP,
					    csum);
		अगर (uh->check == 0)
			uh->check = CSUM_MANGLED_0;
	पूर्ण
पूर्ण

/*
 *	Sending
 */

अटल पूर्णांक udp_v6_send_skb(काष्ठा sk_buff *skb, काष्ठा flowi6 *fl6,
			   काष्ठा inet_cork *cork)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा udphdr *uh;
	पूर्णांक err = 0;
	पूर्णांक is_udplite = IS_UDPLITE(sk);
	__wsum csum = 0;
	पूर्णांक offset = skb_transport_offset(skb);
	पूर्णांक len = skb->len - offset;
	पूर्णांक datalen = len - माप(*uh);

	/*
	 * Create a UDP header
	 */
	uh = udp_hdr(skb);
	uh->source = fl6->fl6_sport;
	uh->dest = fl6->fl6_dport;
	uh->len = htons(len);
	uh->check = 0;

	अगर (cork->gso_size) अणु
		स्थिर पूर्णांक hlen = skb_network_header_len(skb) +
				 माप(काष्ठा udphdr);

		अगर (hlen + cork->gso_size > cork->fragsize) अणु
			kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण
		अगर (skb->len > cork->gso_size * UDP_MAX_SEGMENTS) अणु
			kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण
		अगर (udp_sk(sk)->no_check6_tx) अणु
			kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण
		अगर (skb->ip_summed != CHECKSUM_PARTIAL || is_udplite ||
		    dst_xfrm(skb_dst(skb))) अणु
			kमुक्त_skb(skb);
			वापस -EIO;
		पूर्ण

		अगर (datalen > cork->gso_size) अणु
			skb_shinfo(skb)->gso_size = cork->gso_size;
			skb_shinfo(skb)->gso_type = SKB_GSO_UDP_L4;
			skb_shinfo(skb)->gso_segs = DIV_ROUND_UP(datalen,
								 cork->gso_size);
		पूर्ण
		जाओ csum_partial;
	पूर्ण

	अगर (is_udplite)
		csum = udplite_csum(skb);
	अन्यथा अगर (udp_sk(sk)->no_check6_tx) अणु   /* UDP csum disabled */
		skb->ip_summed = CHECKSUM_NONE;
		जाओ send;
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु /* UDP hardware csum */
csum_partial:
		udp6_hwcsum_outgoing(sk, skb, &fl6->saddr, &fl6->daddr, len);
		जाओ send;
	पूर्ण अन्यथा
		csum = udp_csum(skb);

	/* add protocol-dependent pseuकरो-header */
	uh->check = csum_ipv6_magic(&fl6->saddr, &fl6->daddr,
				    len, fl6->flowi6_proto, csum);
	अगर (uh->check == 0)
		uh->check = CSUM_MANGLED_0;

send:
	err = ip6_send_skb(skb);
	अगर (err) अणु
		अगर (err == -ENOBUFS && !inet6_sk(sk)->recverr) अणु
			UDP6_INC_STATS(sock_net(sk),
				       UDP_MIB_SNDBUFERRORS, is_udplite);
			err = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		UDP6_INC_STATS(sock_net(sk),
			       UDP_MIB_OUTDATAGRAMS, is_udplite);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक udp_v6_push_pending_frames(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा udp_sock  *up = udp_sk(sk);
	काष्ठा flowi6 fl6;
	पूर्णांक err = 0;

	अगर (up->pending == AF_INET)
		वापस udp_push_pending_frames(sk);

	/* ip6_finish_skb will release the cork, so make a copy of
	 * fl6 here.
	 */
	fl6 = inet_sk(sk)->cork.fl.u.ip6;

	skb = ip6_finish_skb(sk);
	अगर (!skb)
		जाओ out;

	err = udp_v6_send_skb(skb, &fl6, &inet_sk(sk)->cork.base);

out:
	up->len = 0;
	up->pending = 0;
	वापस err;
पूर्ण

पूर्णांक udpv6_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा ipv6_txoptions opt_space;
	काष्ठा udp_sock *up = udp_sk(sk);
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_in6 *, sin6, msg->msg_name);
	काष्ठा in6_addr *daddr, *final_p, final;
	काष्ठा ipv6_txoptions *opt = शून्य;
	काष्ठा ipv6_txoptions *opt_to_मुक्त = शून्य;
	काष्ठा ip6_flowlabel *flowlabel = शून्य;
	काष्ठा flowi6 fl6;
	काष्ठा dst_entry *dst;
	काष्ठा ipcm6_cookie ipc6;
	पूर्णांक addr_len = msg->msg_namelen;
	bool connected = false;
	पूर्णांक ulen = len;
	पूर्णांक corkreq = up->corkflag || msg->msg_flags&MSG_MORE;
	पूर्णांक err;
	पूर्णांक is_udplite = IS_UDPLITE(sk);
	पूर्णांक (*getfrag)(व्योम *, अक्षर *, पूर्णांक, पूर्णांक, पूर्णांक, काष्ठा sk_buff *);

	ipcm6_init(&ipc6);
	ipc6.gso_size = up->gso_size;
	ipc6.sockc.tsflags = sk->sk_tsflags;
	ipc6.sockc.mark = sk->sk_mark;

	/* destination address check */
	अगर (sin6) अणु
		अगर (addr_len < दुरत्व(काष्ठा sockaddr, sa_data))
			वापस -EINVAL;

		चयन (sin6->sin6_family) अणु
		हाल AF_INET6:
			अगर (addr_len < SIN6_LEN_RFC2133)
				वापस -EINVAL;
			daddr = &sin6->sin6_addr;
			अगर (ipv6_addr_any(daddr) &&
			    ipv6_addr_v4mapped(&np->saddr))
				ipv6_addr_set_v4mapped(htonl(INADDR_LOOPBACK),
						       daddr);
			अवरोध;
		हाल AF_INET:
			जाओ करो_udp_sendmsg;
		हाल AF_UNSPEC:
			msg->msg_name = sin6 = शून्य;
			msg->msg_namelen = addr_len = 0;
			daddr = शून्य;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (!up->pending) अणु
		अगर (sk->sk_state != TCP_ESTABLISHED)
			वापस -EDESTADDRREQ;
		daddr = &sk->sk_v6_daddr;
	पूर्ण अन्यथा
		daddr = शून्य;

	अगर (daddr) अणु
		अगर (ipv6_addr_v4mapped(daddr)) अणु
			काष्ठा sockaddr_in sin;
			sin.sin_family = AF_INET;
			sin.sin_port = sin6 ? sin6->sin6_port : inet->inet_dport;
			sin.sin_addr.s_addr = daddr->s6_addr32[3];
			msg->msg_name = &sin;
			msg->msg_namelen = माप(sin);
करो_udp_sendmsg:
			अगर (__ipv6_only_sock(sk))
				वापस -ENETUNREACH;
			वापस udp_sendmsg(sk, msg, len);
		पूर्ण
	पूर्ण

	अगर (up->pending == AF_INET)
		वापस udp_sendmsg(sk, msg, len);

	/* Rough check on arithmetic overflow,
	   better check is made in ip6_append_data().
	   */
	अगर (len > पूर्णांक_उच्च - माप(काष्ठा udphdr))
		वापस -EMSGSIZE;

	getfrag  =  is_udplite ?  udplite_getfrag : ip_generic_getfrag;
	अगर (up->pending) अणु
		/*
		 * There are pending frames.
		 * The socket lock must be held जबतक it's corked.
		 */
		lock_sock(sk);
		अगर (likely(up->pending)) अणु
			अगर (unlikely(up->pending != AF_INET6)) अणु
				release_sock(sk);
				वापस -EAFNOSUPPORT;
			पूर्ण
			dst = शून्य;
			जाओ करो_append_data;
		पूर्ण
		release_sock(sk);
	पूर्ण
	ulen += माप(काष्ठा udphdr);

	स_रखो(&fl6, 0, माप(fl6));

	अगर (sin6) अणु
		अगर (sin6->sin6_port == 0)
			वापस -EINVAL;

		fl6.fl6_dport = sin6->sin6_port;
		daddr = &sin6->sin6_addr;

		अगर (np->sndflow) अणु
			fl6.flowlabel = sin6->sin6_flowinfo&IPV6_FLOWINFO_MASK;
			अगर (fl6.flowlabel&IPV6_FLOWLABEL_MASK) अणु
				flowlabel = fl6_sock_lookup(sk, fl6.flowlabel);
				अगर (IS_ERR(flowlabel))
					वापस -EINVAL;
			पूर्ण
		पूर्ण

		/*
		 * Otherwise it will be dअगरficult to मुख्यtain
		 * sk->sk_dst_cache.
		 */
		अगर (sk->sk_state == TCP_ESTABLISHED &&
		    ipv6_addr_equal(daddr, &sk->sk_v6_daddr))
			daddr = &sk->sk_v6_daddr;

		अगर (addr_len >= माप(काष्ठा sockaddr_in6) &&
		    sin6->sin6_scope_id &&
		    __ipv6_addr_needs_scope_id(__ipv6_addr_type(daddr)))
			fl6.flowi6_oअगर = sin6->sin6_scope_id;
	पूर्ण अन्यथा अणु
		अगर (sk->sk_state != TCP_ESTABLISHED)
			वापस -EDESTADDRREQ;

		fl6.fl6_dport = inet->inet_dport;
		daddr = &sk->sk_v6_daddr;
		fl6.flowlabel = np->flow_label;
		connected = true;
	पूर्ण

	अगर (!fl6.flowi6_oअगर)
		fl6.flowi6_oअगर = sk->sk_bound_dev_अगर;

	अगर (!fl6.flowi6_oअगर)
		fl6.flowi6_oअगर = np->sticky_pktinfo.ipi6_अगरindex;

	fl6.flowi6_mark = ipc6.sockc.mark;
	fl6.flowi6_uid = sk->sk_uid;

	अगर (msg->msg_controllen) अणु
		opt = &opt_space;
		स_रखो(opt, 0, माप(काष्ठा ipv6_txoptions));
		opt->tot_len = माप(*opt);
		ipc6.opt = opt;

		err = udp_cmsg_send(sk, msg, &ipc6.gso_size);
		अगर (err > 0)
			err = ip6_datagram_send_ctl(sock_net(sk), sk, msg, &fl6,
						    &ipc6);
		अगर (err < 0) अणु
			fl6_sock_release(flowlabel);
			वापस err;
		पूर्ण
		अगर ((fl6.flowlabel&IPV6_FLOWLABEL_MASK) && !flowlabel) अणु
			flowlabel = fl6_sock_lookup(sk, fl6.flowlabel);
			अगर (IS_ERR(flowlabel))
				वापस -EINVAL;
		पूर्ण
		अगर (!(opt->opt_nflen|opt->opt_flen))
			opt = शून्य;
		connected = false;
	पूर्ण
	अगर (!opt) अणु
		opt = txopt_get(np);
		opt_to_मुक्त = opt;
	पूर्ण
	अगर (flowlabel)
		opt = fl6_merge_options(&opt_space, flowlabel, opt);
	opt = ipv6_fixup_options(&opt_space, opt);
	ipc6.opt = opt;

	fl6.flowi6_proto = sk->sk_protocol;
	fl6.daddr = *daddr;
	अगर (ipv6_addr_any(&fl6.saddr) && !ipv6_addr_any(&np->saddr))
		fl6.saddr = np->saddr;
	fl6.fl6_sport = inet->inet_sport;

	अगर (cgroup_bpf_enabled(BPF_CGROUP_UDP6_SENDMSG) && !connected) अणु
		err = BPF_CGROUP_RUN_PROG_UDP6_SENDMSG_LOCK(sk,
					   (काष्ठा sockaddr *)sin6, &fl6.saddr);
		अगर (err)
			जाओ out_no_dst;
		अगर (sin6) अणु
			अगर (ipv6_addr_v4mapped(&sin6->sin6_addr)) अणु
				/* BPF program rewrote IPv6-only by IPv4-mapped
				 * IPv6. It's currently unsupported.
				 */
				err = -ENOTSUPP;
				जाओ out_no_dst;
			पूर्ण
			अगर (sin6->sin6_port == 0) अणु
				/* BPF program set invalid port. Reject it. */
				err = -EINVAL;
				जाओ out_no_dst;
			पूर्ण
			fl6.fl6_dport = sin6->sin6_port;
			fl6.daddr = sin6->sin6_addr;
		पूर्ण
	पूर्ण

	अगर (ipv6_addr_any(&fl6.daddr))
		fl6.daddr.s6_addr[15] = 0x1; /* :: means loopback (BSD'ism) */

	final_p = fl6_update_dst(&fl6, opt, &final);
	अगर (final_p)
		connected = false;

	अगर (!fl6.flowi6_oअगर && ipv6_addr_is_multicast(&fl6.daddr)) अणु
		fl6.flowi6_oअगर = np->mcast_oअगर;
		connected = false;
	पूर्ण अन्यथा अगर (!fl6.flowi6_oअगर)
		fl6.flowi6_oअगर = np->ucast_oअगर;

	security_sk_classअगरy_flow(sk, flowi6_to_flowi_common(&fl6));

	अगर (ipc6.tclass < 0)
		ipc6.tclass = np->tclass;

	fl6.flowlabel = ip6_make_flowinfo(ipc6.tclass, fl6.flowlabel);

	dst = ip6_sk_dst_lookup_flow(sk, &fl6, final_p, connected);
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		dst = शून्य;
		जाओ out;
	पूर्ण

	अगर (ipc6.hlimit < 0)
		ipc6.hlimit = ip6_sk_dst_hoplimit(np, &fl6, dst);

	अगर (msg->msg_flags&MSG_CONFIRM)
		जाओ करो_confirm;
back_from_confirm:

	/* Lockless fast path क्रम the non-corking हाल */
	अगर (!corkreq) अणु
		काष्ठा inet_cork_full cork;
		काष्ठा sk_buff *skb;

		skb = ip6_make_skb(sk, getfrag, msg, ulen,
				   माप(काष्ठा udphdr), &ipc6,
				   &fl6, (काष्ठा rt6_info *)dst,
				   msg->msg_flags, &cork);
		err = PTR_ERR(skb);
		अगर (!IS_ERR_OR_शून्य(skb))
			err = udp_v6_send_skb(skb, &fl6, &cork.base);
		जाओ out;
	पूर्ण

	lock_sock(sk);
	अगर (unlikely(up->pending)) अणु
		/* The socket is alपढ़ोy corked जबतक preparing it. */
		/* ... which is an evident application bug. --ANK */
		release_sock(sk);

		net_dbg_ratelimited("udp cork app bug 2\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	up->pending = AF_INET6;

करो_append_data:
	अगर (ipc6.करोntfrag < 0)
		ipc6.करोntfrag = np->करोntfrag;
	up->len += ulen;
	err = ip6_append_data(sk, getfrag, msg, ulen, माप(काष्ठा udphdr),
			      &ipc6, &fl6, (काष्ठा rt6_info *)dst,
			      corkreq ? msg->msg_flags|MSG_MORE : msg->msg_flags);
	अगर (err)
		udp_v6_flush_pending_frames(sk);
	अन्यथा अगर (!corkreq)
		err = udp_v6_push_pending_frames(sk);
	अन्यथा अगर (unlikely(skb_queue_empty(&sk->sk_ग_लिखो_queue)))
		up->pending = 0;

	अगर (err > 0)
		err = np->recverr ? net_xmit_त्रुटि_सं(err) : 0;
	release_sock(sk);

out:
	dst_release(dst);
out_no_dst:
	fl6_sock_release(flowlabel);
	txopt_put(opt_to_मुक्त);
	अगर (!err)
		वापस len;
	/*
	 * ENOBUFS = no kernel mem, SOCK_NOSPACE = no sndbuf space.  Reporting
	 * ENOBUFS might not be good (it's not tunable per se), but otherwise
	 * we करोn't have a good statistic (IpOutDiscards but it can be too many
	 * things).  We could add another new stat but at least क्रम now that
	 * seems like overसमाप्त.
	 */
	अगर (err == -ENOBUFS || test_bit(SOCK_NOSPACE, &sk->sk_socket->flags)) अणु
		UDP6_INC_STATS(sock_net(sk),
			       UDP_MIB_SNDBUFERRORS, is_udplite);
	पूर्ण
	वापस err;

करो_confirm:
	अगर (msg->msg_flags & MSG_PROBE)
		dst_confirm_neigh(dst, &fl6.daddr);
	अगर (!(msg->msg_flags&MSG_PROBE) || len)
		जाओ back_from_confirm;
	err = 0;
	जाओ out;
पूर्ण

व्योम udpv6_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा udp_sock *up = udp_sk(sk);
	lock_sock(sk);

	/* protects from races with udp_पात() */
	sock_set_flag(sk, SOCK_DEAD);
	udp_v6_flush_pending_frames(sk);
	release_sock(sk);

	अगर (अटल_branch_unlikely(&udpv6_encap_needed_key)) अणु
		अगर (up->encap_type) अणु
			व्योम (*encap_destroy)(काष्ठा sock *sk);
			encap_destroy = READ_ONCE(up->encap_destroy);
			अगर (encap_destroy)
				encap_destroy(sk);
		पूर्ण
		अगर (up->encap_enabled) अणु
			अटल_branch_dec(&udpv6_encap_needed_key);
			udp_encap_disable();
		पूर्ण
	पूर्ण

	inet6_destroy_sock(sk);
पूर्ण

/*
 *	Socket option code क्रम UDP
 */
पूर्णांक udpv6_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		     अचिन्हित पूर्णांक optlen)
अणु
	अगर (level == SOL_UDP  ||  level == SOL_UDPLITE)
		वापस udp_lib_setsockopt(sk, level, optname,
					  optval, optlen,
					  udp_v6_push_pending_frames);
	वापस ipv6_setsockopt(sk, level, optname, optval, optlen);
पूर्ण

पूर्णांक udpv6_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		     अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	अगर (level == SOL_UDP  ||  level == SOL_UDPLITE)
		वापस udp_lib_माला_लोockopt(sk, level, optname, optval, optlen);
	वापस ipv6_माला_लोockopt(sk, level, optname, optval, optlen);
पूर्ण

/* thinking of making this स्थिर? Don't.
 * early_demux can change based on sysctl.
 */
अटल काष्ठा inet6_protocol udpv6_protocol = अणु
	.early_demux	=	udp_v6_early_demux,
	.early_demux_handler =  udp_v6_early_demux,
	.handler	=	udpv6_rcv,
	.err_handler	=	udpv6_err,
	.flags		=	INET6_PROTO_NOPOLICY|INET6_PROTO_FINAL,
पूर्ण;

/* ------------------------------------------------------------------------ */
#अगर_घोषित CONFIG_PROC_FS
पूर्णांक udp6_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, IPV6_SEQ_DGRAM_HEADER);
	पूर्ण अन्यथा अणु
		पूर्णांक bucket = ((काष्ठा udp_iter_state *)seq->निजी)->bucket;
		काष्ठा inet_sock *inet = inet_sk(v);
		__u16 srcp = ntohs(inet->inet_sport);
		__u16 destp = ntohs(inet->inet_dport);
		__ip6_dgram_sock_seq_show(seq, v, srcp, destp,
					  udp_rqueue_get(v), bucket);
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा seq_operations udp6_seq_ops = अणु
	.start		= udp_seq_start,
	.next		= udp_seq_next,
	.stop		= udp_seq_stop,
	.show		= udp6_seq_show,
पूर्ण;
EXPORT_SYMBOL(udp6_seq_ops);

अटल काष्ठा udp_seq_afinfo udp6_seq_afinfo = अणु
	.family		= AF_INET6,
	.udp_table	= &udp_table,
पूर्ण;

पूर्णांक __net_init udp6_proc_init(काष्ठा net *net)
अणु
	अगर (!proc_create_net_data("udp6", 0444, net->proc_net, &udp6_seq_ops,
			माप(काष्ठा udp_iter_state), &udp6_seq_afinfo))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम udp6_proc_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("udp6", net->proc_net);
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

/* ------------------------------------------------------------------------ */

काष्ठा proto udpv6_prot = अणु
	.name			= "UDPv6",
	.owner			= THIS_MODULE,
	.बंद			= udp_lib_बंद,
	.pre_connect		= udpv6_pre_connect,
	.connect		= ip6_datagram_connect,
	.disconnect		= udp_disconnect,
	.ioctl			= udp_ioctl,
	.init			= udp_init_sock,
	.destroy		= udpv6_destroy_sock,
	.setsockopt		= udpv6_setsockopt,
	.माला_लोockopt		= udpv6_माला_लोockopt,
	.sendmsg		= udpv6_sendmsg,
	.recvmsg		= udpv6_recvmsg,
	.release_cb		= ip6_datagram_release_cb,
	.hash			= udp_lib_hash,
	.unhash			= udp_lib_unhash,
	.rehash			= udp_v6_rehash,
	.get_port		= udp_v6_get_port,
#अगर_घोषित CONFIG_BPF_SYSCALL
	.psock_update_sk_prot	= udp_bpf_update_proto,
#पूर्ण_अगर
	.memory_allocated	= &udp_memory_allocated,
	.sysctl_mem		= sysctl_udp_mem,
	.sysctl_wmem_offset     = दुरत्व(काष्ठा net, ipv4.sysctl_udp_wmem_min),
	.sysctl_rmem_offset     = दुरत्व(काष्ठा net, ipv4.sysctl_udp_rmem_min),
	.obj_size		= माप(काष्ठा udp6_sock),
	.h.udp_table		= &udp_table,
	.diag_destroy		= udp_पात,
पूर्ण;

अटल काष्ठा inet_protosw udpv6_protosw = अणु
	.type =      SOCK_DGRAM,
	.protocol =  IPPROTO_UDP,
	.prot =      &udpv6_prot,
	.ops =       &inet6_dgram_ops,
	.flags =     INET_PROTOSW_PERMANENT,
पूर्ण;

पूर्णांक __init udpv6_init(व्योम)
अणु
	पूर्णांक ret;

	ret = inet6_add_protocol(&udpv6_protocol, IPPROTO_UDP);
	अगर (ret)
		जाओ out;

	ret = inet6_रेजिस्टर_protosw(&udpv6_protosw);
	अगर (ret)
		जाओ out_udpv6_protocol;
out:
	वापस ret;

out_udpv6_protocol:
	inet6_del_protocol(&udpv6_protocol, IPPROTO_UDP);
	जाओ out;
पूर्ण

व्योम udpv6_निकास(व्योम)
अणु
	inet6_unरेजिस्टर_protosw(&udpv6_protosw);
	inet6_del_protocol(&udpv6_protocol, IPPROTO_UDP);
पूर्ण
