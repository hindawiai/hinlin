<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 Nokia, Inc.
 * Copyright (c) 2001 La Monte H.P. Yarroll
 *
 * This file is part of the SCTP kernel implementation
 *
 * Initialization/cleanup क्रम SCTP protocol support.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Karl Knutson <karl@athena.chicago.il.us>
 *    Jon Grimm <jgrimm@us.ibm.com>
 *    Sridhar Samudrala <sri@us.ibm.com>
 *    Daisy Chang <daisyc@us.ibm.com>
 *    Ardelle Fan <ardelle.fan@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/memblock.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/swap.h>
#समावेश <linux/slab.h>
#समावेश <net/net_namespace.h>
#समावेश <net/protocol.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/route.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/addrconf.h>
#समावेश <net/inet_common.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/udp_tunnel.h>

#घोषणा MAX_SCTP_PORT_HASH_ENTRIES (64 * 1024)

/* Global data काष्ठाures. */
काष्ठा sctp_globals sctp_globals __पढ़ो_mostly;

काष्ठा idr sctp_assocs_id;
DEFINE_SPINLOCK(sctp_assocs_id_lock);

अटल काष्ठा sctp_pf *sctp_pf_inet6_specअगरic;
अटल काष्ठा sctp_pf *sctp_pf_inet_specअगरic;
अटल काष्ठा sctp_af *sctp_af_v4_specअगरic;
अटल काष्ठा sctp_af *sctp_af_v6_specअगरic;

काष्ठा kmem_cache *sctp_chunk_cachep __पढ़ो_mostly;
काष्ठा kmem_cache *sctp_bucket_cachep __पढ़ो_mostly;

दीर्घ sysctl_sctp_mem[3];
पूर्णांक sysctl_sctp_rmem[3];
पूर्णांक sysctl_sctp_wmem[3];

/* Private helper to extract ipv4 address and stash them in
 * the protocol काष्ठाure.
 */
अटल व्योम sctp_v4_copy_addrlist(काष्ठा list_head *addrlist,
				  काष्ठा net_device *dev)
अणु
	काष्ठा in_device *in_dev;
	काष्ठा in_अगरaddr *अगरa;
	काष्ठा sctp_sockaddr_entry *addr;

	rcu_पढ़ो_lock();
	अगर ((in_dev = __in_dev_get_rcu(dev)) == शून्य) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
		/* Add the address to the local list.  */
		addr = kzalloc(माप(*addr), GFP_ATOMIC);
		अगर (addr) अणु
			addr->a.v4.sin_family = AF_INET;
			addr->a.v4.sin_addr.s_addr = अगरa->अगरa_local;
			addr->valid = 1;
			INIT_LIST_HEAD(&addr->list);
			list_add_tail(&addr->list, addrlist);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

/* Extract our IP addresses from the प्रणाली and stash them in the
 * protocol काष्ठाure.
 */
अटल व्योम sctp_get_local_addr_list(काष्ठा net *net)
अणु
	काष्ठा net_device *dev;
	काष्ठा list_head *pos;
	काष्ठा sctp_af *af;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev) अणु
		list_क्रम_each(pos, &sctp_address_families) अणु
			af = list_entry(pos, काष्ठा sctp_af, list);
			af->copy_addrlist(&net->sctp.local_addr_list, dev);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* Free the existing local addresses.  */
अटल व्योम sctp_मुक्त_local_addr_list(काष्ठा net *net)
अणु
	काष्ठा sctp_sockaddr_entry *addr;
	काष्ठा list_head *pos, *temp;

	list_क्रम_each_safe(pos, temp, &net->sctp.local_addr_list) अणु
		addr = list_entry(pos, काष्ठा sctp_sockaddr_entry, list);
		list_del(pos);
		kमुक्त(addr);
	पूर्ण
पूर्ण

/* Copy the local addresses which are valid क्रम 'scope' into 'bp'.  */
पूर्णांक sctp_copy_local_addr_list(काष्ठा net *net, काष्ठा sctp_bind_addr *bp,
			      क्रमागत sctp_scope scope, gfp_t gfp, पूर्णांक copy_flags)
अणु
	काष्ठा sctp_sockaddr_entry *addr;
	जोड़ sctp_addr laddr;
	पूर्णांक error = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(addr, &net->sctp.local_addr_list, list) अणु
		अगर (!addr->valid)
			जारी;
		अगर (!sctp_in_scope(net, &addr->a, scope))
			जारी;

		/* Now that the address is in scope, check to see अगर
		 * the address type is really supported by the local
		 * sock as well as the remote peer.
		 */
		अगर (addr->a.sa.sa_family == AF_INET &&
		    (!(copy_flags & SCTP_ADDR4_ALLOWED) ||
		     !(copy_flags & SCTP_ADDR4_PEERSUPP)))
			जारी;
		अगर (addr->a.sa.sa_family == AF_INET6 &&
		    (!(copy_flags & SCTP_ADDR6_ALLOWED) ||
		     !(copy_flags & SCTP_ADDR6_PEERSUPP)))
			जारी;

		laddr = addr->a;
		/* also works क्रम setting ipv6 address port */
		laddr.v4.sin_port = htons(bp->port);
		अगर (sctp_bind_addr_state(bp, &laddr) != -1)
			जारी;

		error = sctp_add_bind_addr(bp, &addr->a, माप(addr->a),
					   SCTP_ADDR_SRC, GFP_ATOMIC);
		अगर (error)
			अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस error;
पूर्ण

/* Copy over any ip options */
अटल व्योम sctp_v4_copy_ip_options(काष्ठा sock *sk, काष्ठा sock *newsk)
अणु
	काष्ठा inet_sock *newinet, *inet = inet_sk(sk);
	काष्ठा ip_options_rcu *inet_opt, *newopt = शून्य;

	newinet = inet_sk(newsk);

	rcu_पढ़ो_lock();
	inet_opt = rcu_dereference(inet->inet_opt);
	अगर (inet_opt) अणु
		newopt = sock_kदो_स्मृति(newsk, माप(*inet_opt) +
				      inet_opt->opt.optlen, GFP_ATOMIC);
		अगर (newopt)
			स_नकल(newopt, inet_opt, माप(*inet_opt) +
			       inet_opt->opt.optlen);
		अन्यथा
			pr_err("%s: Failed to copy ip options\n", __func__);
	पूर्ण
	RCU_INIT_POINTER(newinet->inet_opt, newopt);
	rcu_पढ़ो_unlock();
पूर्ण

/* Account क्रम the IP options */
अटल पूर्णांक sctp_v4_ip_options_len(काष्ठा sock *sk)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा ip_options_rcu *inet_opt;
	पूर्णांक len = 0;

	rcu_पढ़ो_lock();
	inet_opt = rcu_dereference(inet->inet_opt);
	अगर (inet_opt)
		len = inet_opt->opt.optlen;

	rcu_पढ़ो_unlock();
	वापस len;
पूर्ण

/* Initialize a sctp_addr from in incoming skb.  */
अटल व्योम sctp_v4_from_skb(जोड़ sctp_addr *addr, काष्ठा sk_buff *skb,
			     पूर्णांक is_saddr)
अणु
	/* Always called on head skb, so this is safe */
	काष्ठा sctphdr *sh = sctp_hdr(skb);
	काष्ठा sockaddr_in *sa = &addr->v4;

	addr->v4.sin_family = AF_INET;

	अगर (is_saddr) अणु
		sa->sin_port = sh->source;
		sa->sin_addr.s_addr = ip_hdr(skb)->saddr;
	पूर्ण अन्यथा अणु
		sa->sin_port = sh->dest;
		sa->sin_addr.s_addr = ip_hdr(skb)->daddr;
	पूर्ण
	स_रखो(sa->sin_zero, 0, माप(sa->sin_zero));
पूर्ण

/* Initialize an sctp_addr from a socket. */
अटल व्योम sctp_v4_from_sk(जोड़ sctp_addr *addr, काष्ठा sock *sk)
अणु
	addr->v4.sin_family = AF_INET;
	addr->v4.sin_port = 0;
	addr->v4.sin_addr.s_addr = inet_sk(sk)->inet_rcv_saddr;
	स_रखो(addr->v4.sin_zero, 0, माप(addr->v4.sin_zero));
पूर्ण

/* Initialize sk->sk_rcv_saddr from sctp_addr. */
अटल व्योम sctp_v4_to_sk_saddr(जोड़ sctp_addr *addr, काष्ठा sock *sk)
अणु
	inet_sk(sk)->inet_rcv_saddr = addr->v4.sin_addr.s_addr;
पूर्ण

/* Initialize sk->sk_daddr from sctp_addr. */
अटल व्योम sctp_v4_to_sk_daddr(जोड़ sctp_addr *addr, काष्ठा sock *sk)
अणु
	inet_sk(sk)->inet_daddr = addr->v4.sin_addr.s_addr;
पूर्ण

/* Initialize a sctp_addr from an address parameter. */
अटल व्योम sctp_v4_from_addr_param(जोड़ sctp_addr *addr,
				    जोड़ sctp_addr_param *param,
				    __be16 port, पूर्णांक iअगर)
अणु
	addr->v4.sin_family = AF_INET;
	addr->v4.sin_port = port;
	addr->v4.sin_addr.s_addr = param->v4.addr.s_addr;
	स_रखो(addr->v4.sin_zero, 0, माप(addr->v4.sin_zero));
पूर्ण

/* Initialize an address parameter from a sctp_addr and वापस the length
 * of the address parameter.
 */
अटल पूर्णांक sctp_v4_to_addr_param(स्थिर जोड़ sctp_addr *addr,
				 जोड़ sctp_addr_param *param)
अणु
	पूर्णांक length = माप(काष्ठा sctp_ipv4addr_param);

	param->v4.param_hdr.type = SCTP_PARAM_IPV4_ADDRESS;
	param->v4.param_hdr.length = htons(length);
	param->v4.addr.s_addr = addr->v4.sin_addr.s_addr;

	वापस length;
पूर्ण

/* Initialize a sctp_addr from a dst_entry. */
अटल व्योम sctp_v4_dst_saddr(जोड़ sctp_addr *saddr, काष्ठा flowi4 *fl4,
			      __be16 port)
अणु
	saddr->v4.sin_family = AF_INET;
	saddr->v4.sin_port = port;
	saddr->v4.sin_addr.s_addr = fl4->saddr;
	स_रखो(saddr->v4.sin_zero, 0, माप(saddr->v4.sin_zero));
पूर्ण

/* Compare two addresses exactly. */
अटल पूर्णांक sctp_v4_cmp_addr(स्थिर जोड़ sctp_addr *addr1,
			    स्थिर जोड़ sctp_addr *addr2)
अणु
	अगर (addr1->sa.sa_family != addr2->sa.sa_family)
		वापस 0;
	अगर (addr1->v4.sin_port != addr2->v4.sin_port)
		वापस 0;
	अगर (addr1->v4.sin_addr.s_addr != addr2->v4.sin_addr.s_addr)
		वापस 0;

	वापस 1;
पूर्ण

/* Initialize addr काष्ठा to INADDR_ANY. */
अटल व्योम sctp_v4_inaddr_any(जोड़ sctp_addr *addr, __be16 port)
अणु
	addr->v4.sin_family = AF_INET;
	addr->v4.sin_addr.s_addr = htonl(INADDR_ANY);
	addr->v4.sin_port = port;
	स_रखो(addr->v4.sin_zero, 0, माप(addr->v4.sin_zero));
पूर्ण

/* Is this a wildcard address? */
अटल पूर्णांक sctp_v4_is_any(स्थिर जोड़ sctp_addr *addr)
अणु
	वापस htonl(INADDR_ANY) == addr->v4.sin_addr.s_addr;
पूर्ण

/* This function checks अगर the address is a valid address to be used क्रम
 * SCTP binding.
 *
 * Output:
 * Return 0 - If the address is a non-unicast or an illegal address.
 * Return 1 - If the address is a unicast.
 */
अटल पूर्णांक sctp_v4_addr_valid(जोड़ sctp_addr *addr,
			      काष्ठा sctp_sock *sp,
			      स्थिर काष्ठा sk_buff *skb)
अणु
	/* IPv4 addresses not allowed */
	अगर (sp && ipv6_only_sock(sctp_opt2sk(sp)))
		वापस 0;

	/* Is this a non-unicast address or a unusable SCTP address? */
	अगर (IS_IPV4_UNUSABLE_ADDRESS(addr->v4.sin_addr.s_addr))
		वापस 0;

	/* Is this a broadcast address? */
	अगर (skb && skb_rtable(skb)->rt_flags & RTCF_BROADCAST)
		वापस 0;

	वापस 1;
पूर्ण

/* Should this be available क्रम binding?   */
अटल पूर्णांक sctp_v4_available(जोड़ sctp_addr *addr, काष्ठा sctp_sock *sp)
अणु
	काष्ठा net *net = sock_net(&sp->inet.sk);
	पूर्णांक ret = inet_addr_type(net, addr->v4.sin_addr.s_addr);


	अगर (addr->v4.sin_addr.s_addr != htonl(INADDR_ANY) &&
	   ret != RTN_LOCAL &&
	   !sp->inet.मुक्तbind &&
	   !net->ipv4.sysctl_ip_nonlocal_bind)
		वापस 0;

	अगर (ipv6_only_sock(sctp_opt2sk(sp)))
		वापस 0;

	वापस 1;
पूर्ण

/* Checking the loopback, निजी and other address scopes as defined in
 * RFC 1918.   The IPv4 scoping is based on the draft क्रम SCTP IPv4
 * scoping <draft-stewart-tsvwg-sctp-ipv4-00.txt>.
 *
 * Level 0 - unusable SCTP addresses
 * Level 1 - loopback address
 * Level 2 - link-local addresses
 * Level 3 - निजी addresses.
 * Level 4 - global addresses
 * For INIT and INIT-ACK address list, let L be the level of
 * requested destination address, sender and receiver
 * SHOULD include all of its addresses with level greater
 * than or equal to L.
 *
 * IPv4 scoping can be controlled through sysctl option
 * net.sctp.addr_scope_policy
 */
अटल क्रमागत sctp_scope sctp_v4_scope(जोड़ sctp_addr *addr)
अणु
	क्रमागत sctp_scope retval;

	/* Check क्रम unusable SCTP addresses. */
	अगर (IS_IPV4_UNUSABLE_ADDRESS(addr->v4.sin_addr.s_addr)) अणु
		retval =  SCTP_SCOPE_UNUSABLE;
	पूर्ण अन्यथा अगर (ipv4_is_loopback(addr->v4.sin_addr.s_addr)) अणु
		retval = SCTP_SCOPE_LOOPBACK;
	पूर्ण अन्यथा अगर (ipv4_is_linklocal_169(addr->v4.sin_addr.s_addr)) अणु
		retval = SCTP_SCOPE_LINK;
	पूर्ण अन्यथा अगर (ipv4_is_निजी_10(addr->v4.sin_addr.s_addr) ||
		   ipv4_is_निजी_172(addr->v4.sin_addr.s_addr) ||
		   ipv4_is_निजी_192(addr->v4.sin_addr.s_addr)) अणु
		retval = SCTP_SCOPE_PRIVATE;
	पूर्ण अन्यथा अणु
		retval = SCTP_SCOPE_GLOBAL;
	पूर्ण

	वापस retval;
पूर्ण

/* Returns a valid dst cache entry क्रम the given source and destination ip
 * addresses. If an association is passed, trys to get a dst entry with a
 * source address that matches an address in the bind address list.
 */
अटल व्योम sctp_v4_get_dst(काष्ठा sctp_transport *t, जोड़ sctp_addr *saddr,
				काष्ठा flowi *fl, काष्ठा sock *sk)
अणु
	काष्ठा sctp_association *asoc = t->asoc;
	काष्ठा rtable *rt;
	काष्ठा flowi _fl;
	काष्ठा flowi4 *fl4 = &_fl.u.ip4;
	काष्ठा sctp_bind_addr *bp;
	काष्ठा sctp_sockaddr_entry *laddr;
	काष्ठा dst_entry *dst = शून्य;
	जोड़ sctp_addr *daddr = &t->ipaddr;
	जोड़ sctp_addr dst_saddr;
	__u8 tos = inet_sk(sk)->tos;

	अगर (t->dscp & SCTP_DSCP_SET_MASK)
		tos = t->dscp & SCTP_DSCP_VAL_MASK;
	स_रखो(&_fl, 0x0, माप(_fl));
	fl4->daddr  = daddr->v4.sin_addr.s_addr;
	fl4->fl4_dport = daddr->v4.sin_port;
	fl4->flowi4_proto = IPPROTO_SCTP;
	अगर (asoc) अणु
		fl4->flowi4_tos = RT_CONN_FLAGS_TOS(asoc->base.sk, tos);
		fl4->flowi4_oअगर = asoc->base.sk->sk_bound_dev_अगर;
		fl4->fl4_sport = htons(asoc->base.bind_addr.port);
	पूर्ण
	अगर (saddr) अणु
		fl4->saddr = saddr->v4.sin_addr.s_addr;
		अगर (!fl4->fl4_sport)
			fl4->fl4_sport = saddr->v4.sin_port;
	पूर्ण

	pr_debug("%s: dst:%pI4, src:%pI4 - ", __func__, &fl4->daddr,
		 &fl4->saddr);

	rt = ip_route_output_key(sock_net(sk), fl4);
	अगर (!IS_ERR(rt)) अणु
		dst = &rt->dst;
		t->dst = dst;
		स_नकल(fl, &_fl, माप(_fl));
	पूर्ण

	/* If there is no association or अगर a source address is passed, no
	 * more validation is required.
	 */
	अगर (!asoc || saddr)
		जाओ out;

	bp = &asoc->base.bind_addr;

	अगर (dst) अणु
		/* Walk through the bind address list and look क्रम a bind
		 * address that matches the source address of the वापसed dst.
		 */
		sctp_v4_dst_saddr(&dst_saddr, fl4, htons(bp->port));
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(laddr, &bp->address_list, list) अणु
			अगर (!laddr->valid || (laddr->state == SCTP_ADDR_DEL) ||
			    (laddr->state != SCTP_ADDR_SRC &&
			    !asoc->src_out_of_asoc_ok))
				जारी;
			अगर (sctp_v4_cmp_addr(&dst_saddr, &laddr->a))
				जाओ out_unlock;
		पूर्ण
		rcu_पढ़ो_unlock();

		/* None of the bound addresses match the source address of the
		 * dst. So release it.
		 */
		dst_release(dst);
		dst = शून्य;
	पूर्ण

	/* Walk through the bind address list and try to get a dst that
	 * matches a bind address as the source address.
	 */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(laddr, &bp->address_list, list) अणु
		काष्ठा net_device *odev;

		अगर (!laddr->valid)
			जारी;
		अगर (laddr->state != SCTP_ADDR_SRC ||
		    AF_INET != laddr->a.sa.sa_family)
			जारी;

		fl4->fl4_sport = laddr->a.v4.sin_port;
		flowi4_update_output(fl4,
				     asoc->base.sk->sk_bound_dev_अगर,
				     RT_CONN_FLAGS_TOS(asoc->base.sk, tos),
				     daddr->v4.sin_addr.s_addr,
				     laddr->a.v4.sin_addr.s_addr);

		rt = ip_route_output_key(sock_net(sk), fl4);
		अगर (IS_ERR(rt))
			जारी;

		/* Ensure the src address beदीर्घs to the output
		 * पूर्णांकerface.
		 */
		odev = __ip_dev_find(sock_net(sk), laddr->a.v4.sin_addr.s_addr,
				     false);
		अगर (!odev || odev->अगरindex != fl4->flowi4_oअगर) अणु
			अगर (!dst) अणु
				dst = &rt->dst;
				t->dst = dst;
				स_नकल(fl, &_fl, माप(_fl));
			पूर्ण अन्यथा अणु
				dst_release(&rt->dst);
			पूर्ण
			जारी;
		पूर्ण

		dst_release(dst);
		dst = &rt->dst;
		t->dst = dst;
		स_नकल(fl, &_fl, माप(_fl));
		अवरोध;
	पूर्ण

out_unlock:
	rcu_पढ़ो_unlock();
out:
	अगर (dst) अणु
		pr_debug("rt_dst:%pI4, rt_src:%pI4\n",
			 &fl->u.ip4.daddr, &fl->u.ip4.saddr);
	पूर्ण अन्यथा अणु
		t->dst = शून्य;
		pr_debug("no route\n");
	पूर्ण
पूर्ण

/* For v4, the source address is cached in the route entry(dst). So no need
 * to cache it separately and hence this is an empty routine.
 */
अटल व्योम sctp_v4_get_saddr(काष्ठा sctp_sock *sk,
			      काष्ठा sctp_transport *t,
			      काष्ठा flowi *fl)
अणु
	जोड़ sctp_addr *saddr = &t->saddr;
	काष्ठा rtable *rt = (काष्ठा rtable *)t->dst;

	अगर (rt) अणु
		saddr->v4.sin_family = AF_INET;
		saddr->v4.sin_addr.s_addr = fl->u.ip4.saddr;
	पूर्ण
पूर्ण

/* What पूर्णांकerface did this skb arrive on? */
अटल पूर्णांक sctp_v4_skb_iअगर(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस inet_iअगर(skb);
पूर्ण

/* Was this packet marked by Explicit Congestion Notअगरication? */
अटल पूर्णांक sctp_v4_is_ce(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस INET_ECN_is_ce(ip_hdr(skb)->tos);
पूर्ण

/* Create and initialize a new sk क्रम the socket वापसed by accept(). */
अटल काष्ठा sock *sctp_v4_create_accept_sk(काष्ठा sock *sk,
					     काष्ठा sctp_association *asoc,
					     bool kern)
अणु
	काष्ठा sock *newsk = sk_alloc(sock_net(sk), PF_INET, GFP_KERNEL,
			sk->sk_prot, kern);
	काष्ठा inet_sock *newinet;

	अगर (!newsk)
		जाओ out;

	sock_init_data(शून्य, newsk);

	sctp_copy_sock(newsk, sk, asoc);
	sock_reset_flag(newsk, SOCK_ZAPPED);

	sctp_v4_copy_ip_options(sk, newsk);

	newinet = inet_sk(newsk);

	newinet->inet_daddr = asoc->peer.primary_addr.v4.sin_addr.s_addr;

	sk_refcnt_debug_inc(newsk);

	अगर (newsk->sk_prot->init(newsk)) अणु
		sk_common_release(newsk);
		newsk = शून्य;
	पूर्ण

out:
	वापस newsk;
पूर्ण

अटल पूर्णांक sctp_v4_addr_to_user(काष्ठा sctp_sock *sp, जोड़ sctp_addr *addr)
अणु
	/* No address mapping क्रम V4 sockets */
	स_रखो(addr->v4.sin_zero, 0, माप(addr->v4.sin_zero));
	वापस माप(काष्ठा sockaddr_in);
पूर्ण

/* Dump the v4 addr to the seq file. */
अटल व्योम sctp_v4_seq_dump_addr(काष्ठा seq_file *seq, जोड़ sctp_addr *addr)
अणु
	seq_म_लिखो(seq, "%pI4 ", &addr->v4.sin_addr);
पूर्ण

अटल व्योम sctp_v4_ecn_capable(काष्ठा sock *sk)
अणु
	INET_ECN_xmit(sk);
पूर्ण

अटल व्योम sctp_addr_wq_समयout_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा net *net = from_समयr(net, t, sctp.addr_wq_समयr);
	काष्ठा sctp_sockaddr_entry *addrw, *temp;
	काष्ठा sctp_sock *sp;

	spin_lock_bh(&net->sctp.addr_wq_lock);

	list_क्रम_each_entry_safe(addrw, temp, &net->sctp.addr_रुकोq, list) अणु
		pr_debug("%s: the first ent in wq:%p is addr:%pISc for cmd:%d at "
			 "entry:%p\n", __func__, &net->sctp.addr_रुकोq, &addrw->a.sa,
			 addrw->state, addrw);

#अगर IS_ENABLED(CONFIG_IPV6)
		/* Now we send an ASCONF क्रम each association */
		/* Note. we currently करोn't handle link local IPv6 addressees */
		अगर (addrw->a.sa.sa_family == AF_INET6) अणु
			काष्ठा in6_addr *in6;

			अगर (ipv6_addr_type(&addrw->a.v6.sin6_addr) &
			    IPV6_ADDR_LINKLOCAL)
				जाओ मुक्त_next;

			in6 = (काष्ठा in6_addr *)&addrw->a.v6.sin6_addr;
			अगर (ipv6_chk_addr(net, in6, शून्य, 0) == 0 &&
			    addrw->state == SCTP_ADDR_NEW) अणु
				अचिन्हित दीर्घ समयo_val;

				pr_debug("%s: this is on DAD, trying %d sec "
					 "later\n", __func__,
					 SCTP_ADDRESS_TICK_DELAY);

				समयo_val = jअगरfies;
				समयo_val += msecs_to_jअगरfies(SCTP_ADDRESS_TICK_DELAY);
				mod_समयr(&net->sctp.addr_wq_समयr, समयo_val);
				अवरोध;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		list_क्रम_each_entry(sp, &net->sctp.स्वतः_asconf_splist, स्वतः_asconf_list) अणु
			काष्ठा sock *sk;

			sk = sctp_opt2sk(sp);
			/* ignore bound-specअगरic endpoपूर्णांकs */
			अगर (!sctp_is_ep_boundall(sk))
				जारी;
			bh_lock_sock(sk);
			अगर (sctp_asconf_mgmt(sp, addrw) < 0)
				pr_debug("%s: sctp_asconf_mgmt failed\n", __func__);
			bh_unlock_sock(sk);
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
मुक्त_next:
#पूर्ण_अगर
		list_del(&addrw->list);
		kमुक्त(addrw);
	पूर्ण
	spin_unlock_bh(&net->sctp.addr_wq_lock);
पूर्ण

अटल व्योम sctp_मुक्त_addr_wq(काष्ठा net *net)
अणु
	काष्ठा sctp_sockaddr_entry *addrw;
	काष्ठा sctp_sockaddr_entry *temp;

	spin_lock_bh(&net->sctp.addr_wq_lock);
	del_समयr(&net->sctp.addr_wq_समयr);
	list_क्रम_each_entry_safe(addrw, temp, &net->sctp.addr_रुकोq, list) अणु
		list_del(&addrw->list);
		kमुक्त(addrw);
	पूर्ण
	spin_unlock_bh(&net->sctp.addr_wq_lock);
पूर्ण

/* lookup the entry क्रम the same address in the addr_रुकोq
 * sctp_addr_wq MUST be locked
 */
अटल काष्ठा sctp_sockaddr_entry *sctp_addr_wq_lookup(काष्ठा net *net,
					काष्ठा sctp_sockaddr_entry *addr)
अणु
	काष्ठा sctp_sockaddr_entry *addrw;

	list_क्रम_each_entry(addrw, &net->sctp.addr_रुकोq, list) अणु
		अगर (addrw->a.sa.sa_family != addr->a.sa.sa_family)
			जारी;
		अगर (addrw->a.sa.sa_family == AF_INET) अणु
			अगर (addrw->a.v4.sin_addr.s_addr ==
			    addr->a.v4.sin_addr.s_addr)
				वापस addrw;
		पूर्ण अन्यथा अगर (addrw->a.sa.sa_family == AF_INET6) अणु
			अगर (ipv6_addr_equal(&addrw->a.v6.sin6_addr,
			    &addr->a.v6.sin6_addr))
				वापस addrw;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम sctp_addr_wq_mgmt(काष्ठा net *net, काष्ठा sctp_sockaddr_entry *addr, पूर्णांक cmd)
अणु
	काष्ठा sctp_sockaddr_entry *addrw;
	अचिन्हित दीर्घ समयo_val;

	/* first, we check अगर an opposite message alपढ़ोy exist in the queue.
	 * If we found such message, it is हटाओd.
	 * This operation is a bit stupid, but the DHCP client attaches the
	 * new address after a couple of addition and deletion of that address
	 */

	spin_lock_bh(&net->sctp.addr_wq_lock);
	/* Offsets existing events in addr_wq */
	addrw = sctp_addr_wq_lookup(net, addr);
	अगर (addrw) अणु
		अगर (addrw->state != cmd) अणु
			pr_debug("%s: offsets existing entry for %d, addr:%pISc "
				 "in wq:%p\n", __func__, addrw->state, &addrw->a.sa,
				 &net->sctp.addr_रुकोq);

			list_del(&addrw->list);
			kमुक्त(addrw);
		पूर्ण
		spin_unlock_bh(&net->sctp.addr_wq_lock);
		वापस;
	पूर्ण

	/* OK, we have to add the new address to the रुको queue */
	addrw = kmemdup(addr, माप(काष्ठा sctp_sockaddr_entry), GFP_ATOMIC);
	अगर (addrw == शून्य) अणु
		spin_unlock_bh(&net->sctp.addr_wq_lock);
		वापस;
	पूर्ण
	addrw->state = cmd;
	list_add_tail(&addrw->list, &net->sctp.addr_रुकोq);

	pr_debug("%s: add new entry for cmd:%d, addr:%pISc in wq:%p\n",
		 __func__, addrw->state, &addrw->a.sa, &net->sctp.addr_रुकोq);

	अगर (!समयr_pending(&net->sctp.addr_wq_समयr)) अणु
		समयo_val = jअगरfies;
		समयo_val += msecs_to_jअगरfies(SCTP_ADDRESS_TICK_DELAY);
		mod_समयr(&net->sctp.addr_wq_समयr, समयo_val);
	पूर्ण
	spin_unlock_bh(&net->sctp.addr_wq_lock);
पूर्ण

/* Event handler क्रम inet address addition/deletion events.
 * The sctp_local_addr_list needs to be protocted by a spin lock since
 * multiple notअगरiers (say IPv4 and IPv6) may be running at the same
 * समय and thus corrupt the list.
 * The पढ़ोer side is रक्षित with RCU.
 */
अटल पूर्णांक sctp_inetaddr_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ ev,
			       व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = (काष्ठा in_अगरaddr *)ptr;
	काष्ठा sctp_sockaddr_entry *addr = शून्य;
	काष्ठा sctp_sockaddr_entry *temp;
	काष्ठा net *net = dev_net(अगरa->अगरa_dev->dev);
	पूर्णांक found = 0;

	चयन (ev) अणु
	हाल NETDEV_UP:
		addr = kzalloc(माप(*addr), GFP_ATOMIC);
		अगर (addr) अणु
			addr->a.v4.sin_family = AF_INET;
			addr->a.v4.sin_addr.s_addr = अगरa->अगरa_local;
			addr->valid = 1;
			spin_lock_bh(&net->sctp.local_addr_lock);
			list_add_tail_rcu(&addr->list, &net->sctp.local_addr_list);
			sctp_addr_wq_mgmt(net, addr, SCTP_ADDR_NEW);
			spin_unlock_bh(&net->sctp.local_addr_lock);
		पूर्ण
		अवरोध;
	हाल NETDEV_DOWN:
		spin_lock_bh(&net->sctp.local_addr_lock);
		list_क्रम_each_entry_safe(addr, temp,
					&net->sctp.local_addr_list, list) अणु
			अगर (addr->a.sa.sa_family == AF_INET &&
					addr->a.v4.sin_addr.s_addr ==
					अगरa->अगरa_local) अणु
				sctp_addr_wq_mgmt(net, addr, SCTP_ADDR_DEL);
				found = 1;
				addr->valid = 0;
				list_del_rcu(&addr->list);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&net->sctp.local_addr_lock);
		अगर (found)
			kमुक्त_rcu(addr, rcu);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/*
 * Initialize the control inode/socket with a control endpoपूर्णांक data
 * काष्ठाure.  This endpoपूर्णांक is reserved exclusively क्रम the OOTB processing.
 */
अटल पूर्णांक sctp_ctl_sock_init(काष्ठा net *net)
अणु
	पूर्णांक err;
	sa_family_t family = PF_INET;

	अगर (sctp_get_pf_specअगरic(PF_INET6))
		family = PF_INET6;

	err = inet_ctl_sock_create(&net->sctp.ctl_sock, family,
				   SOCK_SEQPACKET, IPPROTO_SCTP, net);

	/* If IPv6 socket could not be created, try the IPv4 socket */
	अगर (err < 0 && family == PF_INET6)
		err = inet_ctl_sock_create(&net->sctp.ctl_sock, AF_INET,
					   SOCK_SEQPACKET, IPPROTO_SCTP,
					   net);

	अगर (err < 0) अणु
		pr_err("Failed to create the SCTP control socket\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_udp_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	SCTP_INPUT_CB(skb)->encap_port = udp_hdr(skb)->source;

	skb_set_transport_header(skb, माप(काष्ठा udphdr));
	sctp_rcv(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक sctp_udp_err_lookup(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sctp_association *asoc;
	काष्ठा sctp_transport *t;
	पूर्णांक family;

	skb->transport_header += माप(काष्ठा udphdr);
	family = (ip_hdr(skb)->version == 4) ? AF_INET : AF_INET6;
	sk = sctp_err_lookup(dev_net(skb->dev), family, skb, sctp_hdr(skb),
			     &asoc, &t);
	अगर (!sk)
		वापस -ENOENT;

	sctp_err_finish(sk, t);
	वापस 0;
पूर्ण

पूर्णांक sctp_udp_sock_start(काष्ठा net *net)
अणु
	काष्ठा udp_tunnel_sock_cfg tuncfg = अणुशून्यपूर्ण;
	काष्ठा udp_port_cfg udp_conf = अणु0पूर्ण;
	काष्ठा socket *sock;
	पूर्णांक err;

	udp_conf.family = AF_INET;
	udp_conf.local_ip.s_addr = htonl(INADDR_ANY);
	udp_conf.local_udp_port = htons(net->sctp.udp_port);
	err = udp_sock_create(net, &udp_conf, &sock);
	अगर (err) अणु
		pr_err("Failed to create the SCTP UDP tunneling v4 sock\n");
		वापस err;
	पूर्ण

	tuncfg.encap_type = 1;
	tuncfg.encap_rcv = sctp_udp_rcv;
	tuncfg.encap_err_lookup = sctp_udp_err_lookup;
	setup_udp_tunnel_sock(net, sock, &tuncfg);
	net->sctp.udp4_sock = sock->sk;

#अगर IS_ENABLED(CONFIG_IPV6)
	स_रखो(&udp_conf, 0, माप(udp_conf));

	udp_conf.family = AF_INET6;
	udp_conf.local_ip6 = in6addr_any;
	udp_conf.local_udp_port = htons(net->sctp.udp_port);
	udp_conf.use_udp6_rx_checksums = true;
	udp_conf.ipv6_v6only = true;
	err = udp_sock_create(net, &udp_conf, &sock);
	अगर (err) अणु
		pr_err("Failed to create the SCTP UDP tunneling v6 sock\n");
		udp_tunnel_sock_release(net->sctp.udp4_sock->sk_socket);
		net->sctp.udp4_sock = शून्य;
		वापस err;
	पूर्ण

	tuncfg.encap_type = 1;
	tuncfg.encap_rcv = sctp_udp_rcv;
	tuncfg.encap_err_lookup = sctp_udp_err_lookup;
	setup_udp_tunnel_sock(net, sock, &tuncfg);
	net->sctp.udp6_sock = sock->sk;
#पूर्ण_अगर

	वापस 0;
पूर्ण

व्योम sctp_udp_sock_stop(काष्ठा net *net)
अणु
	अगर (net->sctp.udp4_sock) अणु
		udp_tunnel_sock_release(net->sctp.udp4_sock->sk_socket);
		net->sctp.udp4_sock = शून्य;
	पूर्ण
	अगर (net->sctp.udp6_sock) अणु
		udp_tunnel_sock_release(net->sctp.udp6_sock->sk_socket);
		net->sctp.udp6_sock = शून्य;
	पूर्ण
पूर्ण

/* Register address family specअगरic functions. */
पूर्णांक sctp_रेजिस्टर_af(काष्ठा sctp_af *af)
अणु
	चयन (af->sa_family) अणु
	हाल AF_INET:
		अगर (sctp_af_v4_specअगरic)
			वापस 0;
		sctp_af_v4_specअगरic = af;
		अवरोध;
	हाल AF_INET6:
		अगर (sctp_af_v6_specअगरic)
			वापस 0;
		sctp_af_v6_specअगरic = af;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	INIT_LIST_HEAD(&af->list);
	list_add_tail(&af->list, &sctp_address_families);
	वापस 1;
पूर्ण

/* Get the table of functions क्रम manipulating a particular address
 * family.
 */
काष्ठा sctp_af *sctp_get_af_specअगरic(sa_family_t family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		वापस sctp_af_v4_specअगरic;
	हाल AF_INET6:
		वापस sctp_af_v6_specअगरic;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

/* Common code to initialize a AF_INET msg_name. */
अटल व्योम sctp_inet_msgname(अक्षर *msgname, पूर्णांक *addr_len)
अणु
	काष्ठा sockaddr_in *sin;

	sin = (काष्ठा sockaddr_in *)msgname;
	*addr_len = माप(काष्ठा sockaddr_in);
	sin->sin_family = AF_INET;
	स_रखो(sin->sin_zero, 0, माप(sin->sin_zero));
पूर्ण

/* Copy the primary address of the peer primary address as the msg_name. */
अटल व्योम sctp_inet_event_msgname(काष्ठा sctp_ulpevent *event, अक्षर *msgname,
				    पूर्णांक *addr_len)
अणु
	काष्ठा sockaddr_in *sin, *sinfrom;

	अगर (msgname) अणु
		काष्ठा sctp_association *asoc;

		asoc = event->asoc;
		sctp_inet_msgname(msgname, addr_len);
		sin = (काष्ठा sockaddr_in *)msgname;
		sinfrom = &asoc->peer.primary_addr.v4;
		sin->sin_port = htons(asoc->peer.port);
		sin->sin_addr.s_addr = sinfrom->sin_addr.s_addr;
	पूर्ण
पूर्ण

/* Initialize and copy out a msgname from an inbound skb. */
अटल व्योम sctp_inet_skb_msgname(काष्ठा sk_buff *skb, अक्षर *msgname, पूर्णांक *len)
अणु
	अगर (msgname) अणु
		काष्ठा sctphdr *sh = sctp_hdr(skb);
		काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)msgname;

		sctp_inet_msgname(msgname, len);
		sin->sin_port = sh->source;
		sin->sin_addr.s_addr = ip_hdr(skb)->saddr;
	पूर्ण
पूर्ण

/* Do we support this AF? */
अटल पूर्णांक sctp_inet_af_supported(sa_family_t family, काष्ठा sctp_sock *sp)
अणु
	/* PF_INET only supports AF_INET addresses. */
	वापस AF_INET == family;
पूर्ण

/* Address matching with wildcards allowed. */
अटल पूर्णांक sctp_inet_cmp_addr(स्थिर जोड़ sctp_addr *addr1,
			      स्थिर जोड़ sctp_addr *addr2,
			      काष्ठा sctp_sock *opt)
अणु
	/* PF_INET only supports AF_INET addresses. */
	अगर (addr1->sa.sa_family != addr2->sa.sa_family)
		वापस 0;
	अगर (htonl(INADDR_ANY) == addr1->v4.sin_addr.s_addr ||
	    htonl(INADDR_ANY) == addr2->v4.sin_addr.s_addr)
		वापस 1;
	अगर (addr1->v4.sin_addr.s_addr == addr2->v4.sin_addr.s_addr)
		वापस 1;

	वापस 0;
पूर्ण

/* Verअगरy that provided sockaddr looks bindable.  Common verअगरication has
 * alपढ़ोy been taken care of.
 */
अटल पूर्णांक sctp_inet_bind_verअगरy(काष्ठा sctp_sock *opt, जोड़ sctp_addr *addr)
अणु
	वापस sctp_v4_available(addr, opt);
पूर्ण

/* Verअगरy that sockaddr looks sendable.  Common verअगरication has alपढ़ोy
 * been taken care of.
 */
अटल पूर्णांक sctp_inet_send_verअगरy(काष्ठा sctp_sock *opt, जोड़ sctp_addr *addr)
अणु
	वापस 1;
पूर्ण

/* Fill in Supported Address Type inक्रमmation क्रम INIT and INIT-ACK
 * chunks.  Returns number of addresses supported.
 */
अटल पूर्णांक sctp_inet_supported_addrs(स्थिर काष्ठा sctp_sock *opt,
				     __be16 *types)
अणु
	types[0] = SCTP_PARAM_IPV4_ADDRESS;
	वापस 1;
पूर्ण

/* Wrapper routine that calls the ip transmit routine. */
अटल अंतरभूत पूर्णांक sctp_v4_xmit(काष्ठा sk_buff *skb, काष्ठा sctp_transport *t)
अणु
	काष्ठा dst_entry *dst = dst_clone(t->dst);
	काष्ठा flowi4 *fl4 = &t->fl.u.ip4;
	काष्ठा sock *sk = skb->sk;
	काष्ठा inet_sock *inet = inet_sk(sk);
	__u8 dscp = inet->tos;
	__be16 df = 0;

	pr_debug("%s: skb:%p, len:%d, src:%pI4, dst:%pI4\n", __func__, skb,
		 skb->len, &fl4->saddr, &fl4->daddr);

	अगर (t->dscp & SCTP_DSCP_SET_MASK)
		dscp = t->dscp & SCTP_DSCP_VAL_MASK;

	inet->pmtudisc = t->param_flags & SPP_PMTUD_ENABLE ? IP_PMTUDISC_DO
							   : IP_PMTUDISC_DONT;
	SCTP_INC_STATS(sock_net(sk), SCTP_MIB_OUTSCTPPACKS);

	अगर (!t->encap_port || !sctp_sk(sk)->udp_port) अणु
		skb_dst_set(skb, dst);
		वापस __ip_queue_xmit(sk, skb, &t->fl, dscp);
	पूर्ण

	अगर (skb_is_gso(skb))
		skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEL_CSUM;

	अगर (ip_करोnt_fragment(sk, dst) && !skb->ignore_df)
		df = htons(IP_DF);

	skb->encapsulation = 1;
	skb_reset_inner_mac_header(skb);
	skb_reset_inner_transport_header(skb);
	skb_set_inner_ipproto(skb, IPPROTO_SCTP);
	udp_tunnel_xmit_skb((काष्ठा rtable *)dst, sk, skb, fl4->saddr,
			    fl4->daddr, dscp, ip4_dst_hoplimit(dst), df,
			    sctp_sk(sk)->udp_port, t->encap_port, false, false);
	वापस 0;
पूर्ण

अटल काष्ठा sctp_af sctp_af_inet;

अटल काष्ठा sctp_pf sctp_pf_inet = अणु
	.event_msgname = sctp_inet_event_msgname,
	.skb_msgname   = sctp_inet_skb_msgname,
	.af_supported  = sctp_inet_af_supported,
	.cmp_addr      = sctp_inet_cmp_addr,
	.bind_verअगरy   = sctp_inet_bind_verअगरy,
	.send_verअगरy   = sctp_inet_send_verअगरy,
	.supported_addrs = sctp_inet_supported_addrs,
	.create_accept_sk = sctp_v4_create_accept_sk,
	.addr_to_user  = sctp_v4_addr_to_user,
	.to_sk_saddr   = sctp_v4_to_sk_saddr,
	.to_sk_daddr   = sctp_v4_to_sk_daddr,
	.copy_ip_options = sctp_v4_copy_ip_options,
	.af            = &sctp_af_inet
पूर्ण;

/* Notअगरier क्रम inetaddr addition/deletion events.  */
अटल काष्ठा notअगरier_block sctp_inetaddr_notअगरier = अणु
	.notअगरier_call = sctp_inetaddr_event,
पूर्ण;

/* Socket operations.  */
अटल स्थिर काष्ठा proto_ops inet_seqpacket_ops = अणु
	.family		   = PF_INET,
	.owner		   = THIS_MODULE,
	.release	   = inet_release,	/* Needs to be wrapped... */
	.bind		   = inet_bind,
	.connect	   = sctp_inet_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = inet_accept,
	.getname	   = inet_getname,	/* Semantics are dअगरferent.  */
	.poll		   = sctp_poll,
	.ioctl		   = inet_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = sctp_inet_listen,
	.shutकरोwn	   = inet_shutकरोwn,	/* Looks harmless.  */
	.setsockopt	   = sock_common_setsockopt, /* IP_SOL IP_OPTION is a problem */
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = inet_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = sock_no_sendpage,
पूर्ण;

/* Registration with AF_INET family.  */
अटल काष्ठा inet_protosw sctp_seqpacket_protosw = अणु
	.type       = SOCK_SEQPACKET,
	.protocol   = IPPROTO_SCTP,
	.prot       = &sctp_prot,
	.ops        = &inet_seqpacket_ops,
	.flags      = SCTP_PROTOSW_FLAG
पूर्ण;
अटल काष्ठा inet_protosw sctp_stream_protosw = अणु
	.type       = SOCK_STREAM,
	.protocol   = IPPROTO_SCTP,
	.prot       = &sctp_prot,
	.ops        = &inet_seqpacket_ops,
	.flags      = SCTP_PROTOSW_FLAG
पूर्ण;

अटल पूर्णांक sctp4_rcv(काष्ठा sk_buff *skb)
अणु
	SCTP_INPUT_CB(skb)->encap_port = 0;
	वापस sctp_rcv(skb);
पूर्ण

/* Register with IP layer.  */
अटल स्थिर काष्ठा net_protocol sctp_protocol = अणु
	.handler     = sctp4_rcv,
	.err_handler = sctp_v4_err,
	.no_policy   = 1,
	.netns_ok    = 1,
	.icmp_strict_tag_validation = 1,
पूर्ण;

/* IPv4 address related functions.  */
अटल काष्ठा sctp_af sctp_af_inet = अणु
	.sa_family	   = AF_INET,
	.sctp_xmit	   = sctp_v4_xmit,
	.setsockopt	   = ip_setsockopt,
	.माला_लोockopt	   = ip_माला_लोockopt,
	.get_dst	   = sctp_v4_get_dst,
	.get_saddr	   = sctp_v4_get_saddr,
	.copy_addrlist	   = sctp_v4_copy_addrlist,
	.from_skb	   = sctp_v4_from_skb,
	.from_sk	   = sctp_v4_from_sk,
	.from_addr_param   = sctp_v4_from_addr_param,
	.to_addr_param	   = sctp_v4_to_addr_param,
	.cmp_addr	   = sctp_v4_cmp_addr,
	.addr_valid	   = sctp_v4_addr_valid,
	.inaddr_any	   = sctp_v4_inaddr_any,
	.is_any		   = sctp_v4_is_any,
	.available	   = sctp_v4_available,
	.scope		   = sctp_v4_scope,
	.skb_iअगर	   = sctp_v4_skb_iअगर,
	.is_ce		   = sctp_v4_is_ce,
	.seq_dump_addr	   = sctp_v4_seq_dump_addr,
	.ecn_capable	   = sctp_v4_ecn_capable,
	.net_header_len	   = माप(काष्ठा iphdr),
	.sockaddr_len	   = माप(काष्ठा sockaddr_in),
	.ip_options_len	   = sctp_v4_ip_options_len,
पूर्ण;

काष्ठा sctp_pf *sctp_get_pf_specअगरic(sa_family_t family)
अणु
	चयन (family) अणु
	हाल PF_INET:
		वापस sctp_pf_inet_specअगरic;
	हाल PF_INET6:
		वापस sctp_pf_inet6_specअगरic;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

/* Register the PF specअगरic function table.  */
पूर्णांक sctp_रेजिस्टर_pf(काष्ठा sctp_pf *pf, sa_family_t family)
अणु
	चयन (family) अणु
	हाल PF_INET:
		अगर (sctp_pf_inet_specअगरic)
			वापस 0;
		sctp_pf_inet_specअगरic = pf;
		अवरोध;
	हाल PF_INET6:
		अगर (sctp_pf_inet6_specअगरic)
			वापस 0;
		sctp_pf_inet6_specअगरic = pf;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक init_sctp_mibs(काष्ठा net *net)
अणु
	net->sctp.sctp_statistics = alloc_percpu(काष्ठा sctp_mib);
	अगर (!net->sctp.sctp_statistics)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cleanup_sctp_mibs(काष्ठा net *net)
अणु
	मुक्त_percpu(net->sctp.sctp_statistics);
पूर्ण

अटल व्योम sctp_v4_pf_init(व्योम)
अणु
	/* Initialize the SCTP specअगरic PF functions. */
	sctp_रेजिस्टर_pf(&sctp_pf_inet, PF_INET);
	sctp_रेजिस्टर_af(&sctp_af_inet);
पूर्ण

अटल व्योम sctp_v4_pf_निकास(व्योम)
अणु
	list_del(&sctp_af_inet.list);
पूर्ण

अटल पूर्णांक sctp_v4_protosw_init(व्योम)
अणु
	पूर्णांक rc;

	rc = proto_रेजिस्टर(&sctp_prot, 1);
	अगर (rc)
		वापस rc;

	/* Register SCTP(UDP and TCP style) with socket layer.  */
	inet_रेजिस्टर_protosw(&sctp_seqpacket_protosw);
	inet_रेजिस्टर_protosw(&sctp_stream_protosw);

	वापस 0;
पूर्ण

अटल व्योम sctp_v4_protosw_निकास(व्योम)
अणु
	inet_unरेजिस्टर_protosw(&sctp_stream_protosw);
	inet_unरेजिस्टर_protosw(&sctp_seqpacket_protosw);
	proto_unरेजिस्टर(&sctp_prot);
पूर्ण

अटल पूर्णांक sctp_v4_add_protocol(व्योम)
अणु
	/* Register notअगरier क्रम inet address additions/deletions. */
	रेजिस्टर_inetaddr_notअगरier(&sctp_inetaddr_notअगरier);

	/* Register SCTP with inet layer.  */
	अगर (inet_add_protocol(&sctp_protocol, IPPROTO_SCTP) < 0)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल व्योम sctp_v4_del_protocol(व्योम)
अणु
	inet_del_protocol(&sctp_protocol, IPPROTO_SCTP);
	unरेजिस्टर_inetaddr_notअगरier(&sctp_inetaddr_notअगरier);
पूर्ण

अटल पूर्णांक __net_init sctp_शेषs_init(काष्ठा net *net)
अणु
	पूर्णांक status;

	/*
	 * 14. Suggested SCTP Protocol Parameter Values
	 */
	/* The following protocol parameters are RECOMMENDED:  */
	/* RTO.Initial              - 3  seconds */
	net->sctp.rto_initial			= SCTP_RTO_INITIAL;
	/* RTO.Min                  - 1  second */
	net->sctp.rto_min	 		= SCTP_RTO_MIN;
	/* RTO.Max                 -  60 seconds */
	net->sctp.rto_max 			= SCTP_RTO_MAX;
	/* RTO.Alpha                - 1/8 */
	net->sctp.rto_alpha			= SCTP_RTO_ALPHA;
	/* RTO.Beta                 - 1/4 */
	net->sctp.rto_beta			= SCTP_RTO_BETA;

	/* Valid.Cookie.Lअगरe        - 60  seconds */
	net->sctp.valid_cookie_lअगरe		= SCTP_DEFAULT_COOKIE_LIFE;

	/* Whether Cookie Preservative is enabled(1) or not(0) */
	net->sctp.cookie_preserve_enable 	= 1;

	/* Default sctp sockets to use md5 as their hmac alg */
#अगर defined (CONFIG_SCTP_DEFAULT_COOKIE_HMAC_MD5)
	net->sctp.sctp_hmac_alg			= "md5";
#या_अगर defined (CONFIG_SCTP_DEFAULT_COOKIE_HMAC_SHA1)
	net->sctp.sctp_hmac_alg			= "sha1";
#अन्यथा
	net->sctp.sctp_hmac_alg			= शून्य;
#पूर्ण_अगर

	/* Max.Burst		    - 4 */
	net->sctp.max_burst			= SCTP_DEFAULT_MAX_BURST;

	/* Disable of Primary Path Switchover by शेष */
	net->sctp.ps_retrans = SCTP_PS_RETRANS_MAX;

	/* Enable pf state by शेष */
	net->sctp.pf_enable = 1;

	/* Ignore pf exposure feature by शेष */
	net->sctp.pf_expose = SCTP_PF_EXPOSE_UNSET;

	/* Association.Max.Retrans  - 10 attempts
	 * Path.Max.Retrans         - 5  attempts (per destination address)
	 * Max.Init.Retransmits     - 8  attempts
	 */
	net->sctp.max_retrans_association	= 10;
	net->sctp.max_retrans_path		= 5;
	net->sctp.max_retrans_init		= 8;

	/* Sendbuffer growth	    - करो per-socket accounting */
	net->sctp.sndbuf_policy			= 0;

	/* Rcvbuffer growth	    - करो per-socket accounting */
	net->sctp.rcvbuf_policy			= 0;

	/* HB.पूर्णांकerval              - 30 seconds */
	net->sctp.hb_पूर्णांकerval			= SCTP_DEFAULT_TIMEOUT_HEARTBEAT;

	/* delayed SACK समयout */
	net->sctp.sack_समयout			= SCTP_DEFAULT_TIMEOUT_SACK;

	/* Disable ADDIP by शेष. */
	net->sctp.addip_enable = 0;
	net->sctp.addip_noauth = 0;
	net->sctp.शेष_स्वतः_asconf = 0;

	/* Enable PR-SCTP by शेष. */
	net->sctp.prsctp_enable = 1;

	/* Disable RECONF by शेष. */
	net->sctp.reconf_enable = 0;

	/* Disable AUTH by शेष. */
	net->sctp.auth_enable = 0;

	/* Enable ECN by शेष. */
	net->sctp.ecn_enable = 1;

	/* Set UDP tunneling listening port to 0 by शेष */
	net->sctp.udp_port = 0;

	/* Set remote encap port to 0 by शेष */
	net->sctp.encap_port = 0;

	/* Set SCOPE policy to enabled */
	net->sctp.scope_policy = SCTP_SCOPE_POLICY_ENABLE;

	/* Set the शेष rwnd update threshold */
	net->sctp.rwnd_upd_shअगरt = SCTP_DEFAULT_RWND_SHIFT;

	/* Initialize maximum स्वतःबंद समयout. */
	net->sctp.max_स्वतःबंद		= पूर्णांक_उच्च / HZ;

	status = sctp_sysctl_net_रेजिस्टर(net);
	अगर (status)
		जाओ err_sysctl_रेजिस्टर;

	/* Allocate and initialise sctp mibs.  */
	status = init_sctp_mibs(net);
	अगर (status)
		जाओ err_init_mibs;

#अगर_घोषित CONFIG_PROC_FS
	/* Initialize proc fs directory.  */
	status = sctp_proc_init(net);
	अगर (status)
		जाओ err_init_proc;
#पूर्ण_अगर

	sctp_dbg_objcnt_init(net);

	/* Initialize the local address list. */
	INIT_LIST_HEAD(&net->sctp.local_addr_list);
	spin_lock_init(&net->sctp.local_addr_lock);
	sctp_get_local_addr_list(net);

	/* Initialize the address event list */
	INIT_LIST_HEAD(&net->sctp.addr_रुकोq);
	INIT_LIST_HEAD(&net->sctp.स्वतः_asconf_splist);
	spin_lock_init(&net->sctp.addr_wq_lock);
	net->sctp.addr_wq_समयr.expires = 0;
	समयr_setup(&net->sctp.addr_wq_समयr, sctp_addr_wq_समयout_handler, 0);

	वापस 0;

#अगर_घोषित CONFIG_PROC_FS
err_init_proc:
	cleanup_sctp_mibs(net);
#पूर्ण_अगर
err_init_mibs:
	sctp_sysctl_net_unरेजिस्टर(net);
err_sysctl_रेजिस्टर:
	वापस status;
पूर्ण

अटल व्योम __net_निकास sctp_शेषs_निकास(काष्ठा net *net)
अणु
	/* Free the local address list */
	sctp_मुक्त_addr_wq(net);
	sctp_मुक्त_local_addr_list(net);

#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_subtree("sctp", net->proc_net);
	net->sctp.proc_net_sctp = शून्य;
#पूर्ण_अगर
	cleanup_sctp_mibs(net);
	sctp_sysctl_net_unरेजिस्टर(net);
पूर्ण

अटल काष्ठा pernet_operations sctp_शेषs_ops = अणु
	.init = sctp_शेषs_init,
	.निकास = sctp_शेषs_निकास,
पूर्ण;

अटल पूर्णांक __net_init sctp_ctrlsock_init(काष्ठा net *net)
अणु
	पूर्णांक status;

	/* Initialize the control inode/socket क्रम handling OOTB packets.  */
	status = sctp_ctl_sock_init(net);
	अगर (status)
		pr_err("Failed to initialize the SCTP control sock\n");

	वापस status;
पूर्ण

अटल व्योम __net_निकास sctp_ctrlsock_निकास(काष्ठा net *net)
अणु
	/* Free the control endpoपूर्णांक.  */
	inet_ctl_sock_destroy(net->sctp.ctl_sock);
पूर्ण

अटल काष्ठा pernet_operations sctp_ctrlsock_ops = अणु
	.init = sctp_ctrlsock_init,
	.निकास = sctp_ctrlsock_निकास,
पूर्ण;

/* Initialize the universe पूर्णांकo something sensible.  */
अटल __init पूर्णांक sctp_init(व्योम)
अणु
	अचिन्हित दीर्घ nr_pages = totalram_pages();
	अचिन्हित दीर्घ limit;
	अचिन्हित दीर्घ goal;
	पूर्णांक max_entry_order;
	पूर्णांक num_entries;
	पूर्णांक max_share;
	पूर्णांक status;
	पूर्णांक order;
	पूर्णांक i;

	sock_skb_cb_check_size(माप(काष्ठा sctp_ulpevent));

	/* Allocate bind_bucket and chunk caches. */
	status = -ENOBUFS;
	sctp_bucket_cachep = kmem_cache_create("sctp_bind_bucket",
					       माप(काष्ठा sctp_bind_bucket),
					       0, SLAB_HWCACHE_ALIGN,
					       शून्य);
	अगर (!sctp_bucket_cachep)
		जाओ out;

	sctp_chunk_cachep = kmem_cache_create("sctp_chunk",
					       माप(काष्ठा sctp_chunk),
					       0, SLAB_HWCACHE_ALIGN,
					       शून्य);
	अगर (!sctp_chunk_cachep)
		जाओ err_chunk_cachep;

	status = percpu_counter_init(&sctp_sockets_allocated, 0, GFP_KERNEL);
	अगर (status)
		जाओ err_percpu_counter_init;

	/* Implementation specअगरic variables. */

	/* Initialize शेष stream count setup inक्रमmation. */
	sctp_max_instreams    		= SCTP_DEFAULT_INSTREAMS;
	sctp_max_outstreams   		= SCTP_DEFAULT_OUTSTREAMS;

	/* Initialize handle used क्रम association ids. */
	idr_init(&sctp_assocs_id);

	limit = nr_मुक्त_buffer_pages() / 8;
	limit = max(limit, 128UL);
	sysctl_sctp_mem[0] = limit / 4 * 3;
	sysctl_sctp_mem[1] = limit;
	sysctl_sctp_mem[2] = sysctl_sctp_mem[0] * 2;

	/* Set per-socket limits to no more than 1/128 the pressure threshold*/
	limit = (sysctl_sctp_mem[1]) << (PAGE_SHIFT - 7);
	max_share = min(4UL*1024*1024, limit);

	sysctl_sctp_rmem[0] = SK_MEM_QUANTUM; /* give each asoc 1 page min */
	sysctl_sctp_rmem[1] = 1500 * SKB_TRUESIZE(1);
	sysctl_sctp_rmem[2] = max(sysctl_sctp_rmem[1], max_share);

	sysctl_sctp_wmem[0] = SK_MEM_QUANTUM;
	sysctl_sctp_wmem[1] = 16*1024;
	sysctl_sctp_wmem[2] = max(64*1024, max_share);

	/* Size and allocate the association hash table.
	 * The methoकरोlogy is similar to that of the tcp hash tables.
	 * Though not identical.  Start by getting a goal size
	 */
	अगर (nr_pages >= (128 * 1024))
		goal = nr_pages >> (22 - PAGE_SHIFT);
	अन्यथा
		goal = nr_pages >> (24 - PAGE_SHIFT);

	/* Then compute the page order क्रम said goal */
	order = get_order(goal);

	/* Now compute the required page order क्रम the maximum sized table we
	 * want to create
	 */
	max_entry_order = get_order(MAX_SCTP_PORT_HASH_ENTRIES *
				    माप(काष्ठा sctp_bind_hashbucket));

	/* Limit the page order by that maximum hash table size */
	order = min(order, max_entry_order);

	/* Allocate and initialize the endpoपूर्णांक hash table.  */
	sctp_ep_hashsize = 64;
	sctp_ep_hashtable =
		kदो_स्मृति_array(64, माप(काष्ठा sctp_hashbucket), GFP_KERNEL);
	अगर (!sctp_ep_hashtable) अणु
		pr_err("Failed endpoint_hash alloc\n");
		status = -ENOMEM;
		जाओ err_ehash_alloc;
	पूर्ण
	क्रम (i = 0; i < sctp_ep_hashsize; i++) अणु
		rwlock_init(&sctp_ep_hashtable[i].lock);
		INIT_HLIST_HEAD(&sctp_ep_hashtable[i].chain);
	पूर्ण

	/* Allocate and initialize the SCTP port hash table.
	 * Note that order is initalized to start at the max sized
	 * table we want to support.  If we can't get that many pages
	 * reduce the order and try again
	 */
	करो अणु
		sctp_port_hashtable = (काष्ठा sctp_bind_hashbucket *)
			__get_मुक्त_pages(GFP_KERNEL | __GFP_NOWARN, order);
	पूर्ण जबतक (!sctp_port_hashtable && --order > 0);

	अगर (!sctp_port_hashtable) अणु
		pr_err("Failed bind hash alloc\n");
		status = -ENOMEM;
		जाओ err_bhash_alloc;
	पूर्ण

	/* Now compute the number of entries that will fit in the
	 * port hash space we allocated
	 */
	num_entries = (1UL << order) * PAGE_SIZE /
		      माप(काष्ठा sctp_bind_hashbucket);

	/* And finish by rounding it करोwn to the nearest घातer of two.
	 * This wastes some memory of course, but it's needed because
	 * the hash function operates based on the assumption that
	 * the number of entries is a घातer of two.
	 */
	sctp_port_hashsize = roundकरोwn_घात_of_two(num_entries);

	क्रम (i = 0; i < sctp_port_hashsize; i++) अणु
		spin_lock_init(&sctp_port_hashtable[i].lock);
		INIT_HLIST_HEAD(&sctp_port_hashtable[i].chain);
	पूर्ण

	status = sctp_transport_hashtable_init();
	अगर (status)
		जाओ err_thash_alloc;

	pr_info("Hash tables configured (bind %d/%d)\n", sctp_port_hashsize,
		num_entries);

	sctp_sysctl_रेजिस्टर();

	INIT_LIST_HEAD(&sctp_address_families);
	sctp_v4_pf_init();
	sctp_v6_pf_init();
	sctp_sched_ops_init();

	status = रेजिस्टर_pernet_subsys(&sctp_शेषs_ops);
	अगर (status)
		जाओ err_रेजिस्टर_शेषs;

	status = sctp_v4_protosw_init();
	अगर (status)
		जाओ err_protosw_init;

	status = sctp_v6_protosw_init();
	अगर (status)
		जाओ err_v6_protosw_init;

	status = रेजिस्टर_pernet_subsys(&sctp_ctrlsock_ops);
	अगर (status)
		जाओ err_रेजिस्टर_ctrlsock;

	status = sctp_v4_add_protocol();
	अगर (status)
		जाओ err_add_protocol;

	/* Register SCTP with inet6 layer.  */
	status = sctp_v6_add_protocol();
	अगर (status)
		जाओ err_v6_add_protocol;

	अगर (sctp_offload_init() < 0)
		pr_crit("%s: Cannot add SCTP protocol offload\n", __func__);

out:
	वापस status;
err_v6_add_protocol:
	sctp_v4_del_protocol();
err_add_protocol:
	unरेजिस्टर_pernet_subsys(&sctp_ctrlsock_ops);
err_रेजिस्टर_ctrlsock:
	sctp_v6_protosw_निकास();
err_v6_protosw_init:
	sctp_v4_protosw_निकास();
err_protosw_init:
	unरेजिस्टर_pernet_subsys(&sctp_शेषs_ops);
err_रेजिस्टर_शेषs:
	sctp_v4_pf_निकास();
	sctp_v6_pf_निकास();
	sctp_sysctl_unरेजिस्टर();
	मुक्त_pages((अचिन्हित दीर्घ)sctp_port_hashtable,
		   get_order(sctp_port_hashsize *
			     माप(काष्ठा sctp_bind_hashbucket)));
err_bhash_alloc:
	sctp_transport_hashtable_destroy();
err_thash_alloc:
	kमुक्त(sctp_ep_hashtable);
err_ehash_alloc:
	percpu_counter_destroy(&sctp_sockets_allocated);
err_percpu_counter_init:
	kmem_cache_destroy(sctp_chunk_cachep);
err_chunk_cachep:
	kmem_cache_destroy(sctp_bucket_cachep);
	जाओ out;
पूर्ण

/* Exit handler क्रम the SCTP protocol.  */
अटल __निकास व्योम sctp_निकास(व्योम)
अणु
	/* BUG.  This should probably करो something useful like clean
	 * up all the reमुख्यing associations and all that memory.
	 */

	/* Unरेजिस्टर with inet6/inet layers. */
	sctp_v6_del_protocol();
	sctp_v4_del_protocol();

	unरेजिस्टर_pernet_subsys(&sctp_ctrlsock_ops);

	/* Free protosw registrations */
	sctp_v6_protosw_निकास();
	sctp_v4_protosw_निकास();

	unरेजिस्टर_pernet_subsys(&sctp_शेषs_ops);

	/* Unरेजिस्टर with socket layer. */
	sctp_v6_pf_निकास();
	sctp_v4_pf_निकास();

	sctp_sysctl_unरेजिस्टर();

	मुक्त_pages((अचिन्हित दीर्घ)sctp_port_hashtable,
		   get_order(sctp_port_hashsize *
			     माप(काष्ठा sctp_bind_hashbucket)));
	kमुक्त(sctp_ep_hashtable);
	sctp_transport_hashtable_destroy();

	percpu_counter_destroy(&sctp_sockets_allocated);

	rcu_barrier(); /* Wait क्रम completion of call_rcu()'s */

	kmem_cache_destroy(sctp_chunk_cachep);
	kmem_cache_destroy(sctp_bucket_cachep);
पूर्ण

module_init(sctp_init);
module_निकास(sctp_निकास);

/*
 * __stringअगरy करोesn't likes क्रमागतs, so use IPPROTO_SCTP value (132) directly.
 */
MODULE_ALIAS("net-pf-" __stringअगरy(PF_INET) "-proto-132");
MODULE_ALIAS("net-pf-" __stringअगरy(PF_INET6) "-proto-132");
MODULE_AUTHOR("Linux Kernel SCTP developers <linux-sctp@vger.kernel.org>");
MODULE_DESCRIPTION("Support for the SCTP protocol (RFC2960)");
module_param_named(no_checksums, sctp_checksum_disable, bool, 0644);
MODULE_PARM_DESC(no_checksums, "Disable checksums computing and verification");
MODULE_LICENSE("GPL");
