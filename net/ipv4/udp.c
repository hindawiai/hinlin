<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		The User Datagram Protocol (UDP).
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Arnt Gulbअक्रमsen, <agulbra@nvg.unit.no>
 *		Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *		Hirokazu Takahashi, <taka@valinux.co.jp>
 *
 * Fixes:
 *		Alan Cox	:	verअगरy_area() calls
 *		Alan Cox	: 	stopped बंद जबतक in use off icmp
 *					messages. Not a fix but a botch that
 *					क्रम udp at least is 'valid'.
 *		Alan Cox	:	Fixed icmp handling properly
 *		Alan Cox	: 	Correct error क्रम oversized datagrams
 *		Alan Cox	:	Tidied select() semantics.
 *		Alan Cox	:	udp_err() fixed properly, also now
 *					select and पढ़ो wake correctly on errors
 *		Alan Cox	:	udp_send verअगरy_area moved to aव्योम mem leak
 *		Alan Cox	:	UDP can count its memory
 *		Alan Cox	:	send to an unknown connection causes
 *					an ECONNREFUSED off the icmp, but
 *					करोes NOT बंद.
 *		Alan Cox	:	Switched to new sk_buff handlers. No more backlog!
 *		Alan Cox	:	Using generic datagram code. Even smaller and the PEEK
 *					bug no दीर्घer crashes it.
 *		Fred Van Kempen	: 	Net2e support क्रम sk->broadcast.
 *		Alan Cox	:	Uses skb_मुक्त_datagram
 *		Alan Cox	:	Added get/set sockopt support.
 *		Alan Cox	:	Broadcasting without option set वापसs EACCES.
 *		Alan Cox	:	No wakeup calls. Instead we now use the callbacks.
 *		Alan Cox	:	Use ip_tos and ip_ttl
 *		Alan Cox	:	SNMP Mibs
 *		Alan Cox	:	MSG_DONTROUTE, and 0.0.0.0 support.
 *		Matt Dillon	:	UDP length checks.
 *		Alan Cox	:	Smarter af_inet used properly.
 *		Alan Cox	:	Use new kernel side addressing.
 *		Alan Cox	:	Incorrect वापस on truncated datagram receive.
 *	Arnt Gulbअक्रमsen 	:	New udp_send and stuff
 *		Alan Cox	:	Cache last socket
 *		Alan Cox	:	Route cache
 *		Jon Peatfield	:	Minor efficiency fix to sendto().
 *		Mike Shaver	:	RFC1122 checks.
 *		Alan Cox	:	Nonblocking error fix.
 *	Willy Konynenberg	:	Transparent proxying support.
 *		Mike McLagan	:	Routing by source
 *		David S. Miller	:	New socket lookup architecture.
 *					Last socket cache retained as it
 *					करोes have a high hit rate.
 *		Olaf Kirch	:	Don't linearise iovec on sendmsg.
 *		Andi Kleen	:	Some cleanups, cache destination entry
 *					क्रम connect.
 *	Vitaly E. Lavrov	:	Transparent proxy revived after year coma.
 *		Melvin Smith	:	Check msg_name not msg_namelen in sendto(),
 *					वापस ENOTCONN क्रम unconnected sockets (POSIX)
 *		Janos Farkas	:	करोn't deliver multi/broadcasts to a dअगरferent
 *					bound-to-device socket
 *	Hirokazu Takahashi	:	HW checksumming क्रम outgoing UDP
 *					datagrams.
 *	Hirokazu Takahashi	:	sendfile() on UDP works now.
 *		Arnalकरो C. Melo :	convert /proc/net/udp to seq_file
 *	YOSHIFUJI Hideaki @USAGI and:	Support IPV6_V6ONLY socket option, which
 *	Alexey Kuznetsov:		allow both IPv4 and IPv6 sockets to bind
 *					a single port at the same समय.
 *	Derek Atkins <derek@ihtfp.com>: Add Encapulation Support
 *	James Chapman		:	Add L2TP encapsulation type.
 */

#घोषणा pr_fmt(fmt) "UDP: " fmt

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <linux/memblock.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/swap.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/module.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/igmp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <net/tcp_states.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <net/net_namespace.h>
#समावेश <net/icmp.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/route.h>
#समावेश <net/checksum.h>
#समावेश <net/xfrm.h>
#समावेश <trace/events/udp.h>
#समावेश <linux/अटल_key.h>
#समावेश <linux/btf_ids.h>
#समावेश <trace/events/skb.h>
#समावेश <net/busy_poll.h>
#समावेश "udp_impl.h"
#समावेश <net/sock_reuseport.h>
#समावेश <net/addrconf.h>
#समावेश <net/udp_tunnel.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ipv6_stubs.h>
#पूर्ण_अगर

काष्ठा udp_table udp_table __पढ़ो_mostly;
EXPORT_SYMBOL(udp_table);

दीर्घ sysctl_udp_mem[3] __पढ़ो_mostly;
EXPORT_SYMBOL(sysctl_udp_mem);

atomic_दीर्घ_t udp_memory_allocated;
EXPORT_SYMBOL(udp_memory_allocated);

#घोषणा MAX_UDP_PORTS 65536
#घोषणा PORTS_PER_CHAIN (MAX_UDP_PORTS / UDP_HTABLE_SIZE_MIN)

अटल पूर्णांक udp_lib_lport_inuse(काष्ठा net *net, __u16 num,
			       स्थिर काष्ठा udp_hslot *hslot,
			       अचिन्हित दीर्घ *biपंचांगap,
			       काष्ठा sock *sk, अचिन्हित पूर्णांक log)
अणु
	काष्ठा sock *sk2;
	kuid_t uid = sock_i_uid(sk);

	sk_क्रम_each(sk2, &hslot->head) अणु
		अगर (net_eq(sock_net(sk2), net) &&
		    sk2 != sk &&
		    (biपंचांगap || udp_sk(sk2)->udp_port_hash == num) &&
		    (!sk2->sk_reuse || !sk->sk_reuse) &&
		    (!sk2->sk_bound_dev_अगर || !sk->sk_bound_dev_अगर ||
		     sk2->sk_bound_dev_अगर == sk->sk_bound_dev_अगर) &&
		    inet_rcv_saddr_equal(sk, sk2, true)) अणु
			अगर (sk2->sk_reuseport && sk->sk_reuseport &&
			    !rcu_access_poपूर्णांकer(sk->sk_reuseport_cb) &&
			    uid_eq(uid, sock_i_uid(sk2))) अणु
				अगर (!biपंचांगap)
					वापस 0;
			पूर्ण अन्यथा अणु
				अगर (!biपंचांगap)
					वापस 1;
				__set_bit(udp_sk(sk2)->udp_port_hash >> log,
					  biपंचांगap);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Note: we still hold spinlock of primary hash chain, so no other ग_लिखोr
 * can insert/delete a socket with local_port == num
 */
अटल पूर्णांक udp_lib_lport_inuse2(काष्ठा net *net, __u16 num,
				काष्ठा udp_hslot *hslot2,
				काष्ठा sock *sk)
अणु
	काष्ठा sock *sk2;
	kuid_t uid = sock_i_uid(sk);
	पूर्णांक res = 0;

	spin_lock(&hslot2->lock);
	udp_portaddr_क्रम_each_entry(sk2, &hslot2->head) अणु
		अगर (net_eq(sock_net(sk2), net) &&
		    sk2 != sk &&
		    (udp_sk(sk2)->udp_port_hash == num) &&
		    (!sk2->sk_reuse || !sk->sk_reuse) &&
		    (!sk2->sk_bound_dev_अगर || !sk->sk_bound_dev_अगर ||
		     sk2->sk_bound_dev_अगर == sk->sk_bound_dev_अगर) &&
		    inet_rcv_saddr_equal(sk, sk2, true)) अणु
			अगर (sk2->sk_reuseport && sk->sk_reuseport &&
			    !rcu_access_poपूर्णांकer(sk->sk_reuseport_cb) &&
			    uid_eq(uid, sock_i_uid(sk2))) अणु
				res = 0;
			पूर्ण अन्यथा अणु
				res = 1;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&hslot2->lock);
	वापस res;
पूर्ण

अटल पूर्णांक udp_reuseport_add_sock(काष्ठा sock *sk, काष्ठा udp_hslot *hslot)
अणु
	काष्ठा net *net = sock_net(sk);
	kuid_t uid = sock_i_uid(sk);
	काष्ठा sock *sk2;

	sk_क्रम_each(sk2, &hslot->head) अणु
		अगर (net_eq(sock_net(sk2), net) &&
		    sk2 != sk &&
		    sk2->sk_family == sk->sk_family &&
		    ipv6_only_sock(sk2) == ipv6_only_sock(sk) &&
		    (udp_sk(sk2)->udp_port_hash == udp_sk(sk)->udp_port_hash) &&
		    (sk2->sk_bound_dev_अगर == sk->sk_bound_dev_अगर) &&
		    sk2->sk_reuseport && uid_eq(uid, sock_i_uid(sk2)) &&
		    inet_rcv_saddr_equal(sk, sk2, false)) अणु
			वापस reuseport_add_sock(sk, sk2,
						  inet_rcv_saddr_any(sk));
		पूर्ण
	पूर्ण

	वापस reuseport_alloc(sk, inet_rcv_saddr_any(sk));
पूर्ण

/**
 *  udp_lib_get_port  -  UDP/-Lite port lookup क्रम IPv4 and IPv6
 *
 *  @sk:          socket काष्ठा in question
 *  @snum:        port number to look up
 *  @hash2_nulladdr: AF-dependent hash value in secondary hash chains,
 *                   with शून्य address
 */
पूर्णांक udp_lib_get_port(काष्ठा sock *sk, अचिन्हित लघु snum,
		     अचिन्हित पूर्णांक hash2_nulladdr)
अणु
	काष्ठा udp_hslot *hslot, *hslot2;
	काष्ठा udp_table *udptable = sk->sk_prot->h.udp_table;
	पूर्णांक    error = 1;
	काष्ठा net *net = sock_net(sk);

	अगर (!snum) अणु
		पूर्णांक low, high, reमुख्यing;
		अचिन्हित पूर्णांक अक्रम;
		अचिन्हित लघु first, last;
		DECLARE_BITMAP(biपंचांगap, PORTS_PER_CHAIN);

		inet_get_local_port_range(net, &low, &high);
		reमुख्यing = (high - low) + 1;

		अक्रम = pअक्रमom_u32();
		first = reciprocal_scale(अक्रम, reमुख्यing) + low;
		/*
		 * क्रमce अक्रम to be an odd multiple of UDP_HTABLE_SIZE
		 */
		अक्रम = (अक्रम | 1) * (udptable->mask + 1);
		last = first + udptable->mask + 1;
		करो अणु
			hslot = udp_hashslot(udptable, net, first);
			biपंचांगap_zero(biपंचांगap, PORTS_PER_CHAIN);
			spin_lock_bh(&hslot->lock);
			udp_lib_lport_inuse(net, snum, hslot, biपंचांगap, sk,
					    udptable->log);

			snum = first;
			/*
			 * Iterate on all possible values of snum क्रम this hash.
			 * Using steps of an odd multiple of UDP_HTABLE_SIZE
			 * give us अक्रमomization and full range coverage.
			 */
			करो अणु
				अगर (low <= snum && snum <= high &&
				    !test_bit(snum >> udptable->log, biपंचांगap) &&
				    !inet_is_local_reserved_port(net, snum))
					जाओ found;
				snum += अक्रम;
			पूर्ण जबतक (snum != first);
			spin_unlock_bh(&hslot->lock);
			cond_resched();
		पूर्ण जबतक (++first != last);
		जाओ fail;
	पूर्ण अन्यथा अणु
		hslot = udp_hashslot(udptable, net, snum);
		spin_lock_bh(&hslot->lock);
		अगर (hslot->count > 10) अणु
			पूर्णांक exist;
			अचिन्हित पूर्णांक slot2 = udp_sk(sk)->udp_portaddr_hash ^ snum;

			slot2          &= udptable->mask;
			hash2_nulladdr &= udptable->mask;

			hslot2 = udp_hashslot2(udptable, slot2);
			अगर (hslot->count < hslot2->count)
				जाओ scan_primary_hash;

			exist = udp_lib_lport_inuse2(net, snum, hslot2, sk);
			अगर (!exist && (hash2_nulladdr != slot2)) अणु
				hslot2 = udp_hashslot2(udptable, hash2_nulladdr);
				exist = udp_lib_lport_inuse2(net, snum, hslot2,
							     sk);
			पूर्ण
			अगर (exist)
				जाओ fail_unlock;
			अन्यथा
				जाओ found;
		पूर्ण
scan_primary_hash:
		अगर (udp_lib_lport_inuse(net, snum, hslot, शून्य, sk, 0))
			जाओ fail_unlock;
	पूर्ण
found:
	inet_sk(sk)->inet_num = snum;
	udp_sk(sk)->udp_port_hash = snum;
	udp_sk(sk)->udp_portaddr_hash ^= snum;
	अगर (sk_unhashed(sk)) अणु
		अगर (sk->sk_reuseport &&
		    udp_reuseport_add_sock(sk, hslot)) अणु
			inet_sk(sk)->inet_num = 0;
			udp_sk(sk)->udp_port_hash = 0;
			udp_sk(sk)->udp_portaddr_hash ^= snum;
			जाओ fail_unlock;
		पूर्ण

		sk_add_node_rcu(sk, &hslot->head);
		hslot->count++;
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);

		hslot2 = udp_hashslot2(udptable, udp_sk(sk)->udp_portaddr_hash);
		spin_lock(&hslot2->lock);
		अगर (IS_ENABLED(CONFIG_IPV6) && sk->sk_reuseport &&
		    sk->sk_family == AF_INET6)
			hlist_add_tail_rcu(&udp_sk(sk)->udp_portaddr_node,
					   &hslot2->head);
		अन्यथा
			hlist_add_head_rcu(&udp_sk(sk)->udp_portaddr_node,
					   &hslot2->head);
		hslot2->count++;
		spin_unlock(&hslot2->lock);
	पूर्ण
	sock_set_flag(sk, SOCK_RCU_FREE);
	error = 0;
fail_unlock:
	spin_unlock_bh(&hslot->lock);
fail:
	वापस error;
पूर्ण
EXPORT_SYMBOL(udp_lib_get_port);

पूर्णांक udp_v4_get_port(काष्ठा sock *sk, अचिन्हित लघु snum)
अणु
	अचिन्हित पूर्णांक hash2_nulladdr =
		ipv4_portaddr_hash(sock_net(sk), htonl(INADDR_ANY), snum);
	अचिन्हित पूर्णांक hash2_partial =
		ipv4_portaddr_hash(sock_net(sk), inet_sk(sk)->inet_rcv_saddr, 0);

	/* precompute partial secondary hash */
	udp_sk(sk)->udp_portaddr_hash = hash2_partial;
	वापस udp_lib_get_port(sk, snum, hash2_nulladdr);
पूर्ण

अटल पूर्णांक compute_score(काष्ठा sock *sk, काष्ठा net *net,
			 __be32 saddr, __be16 sport,
			 __be32 daddr, अचिन्हित लघु hnum,
			 पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
	पूर्णांक score;
	काष्ठा inet_sock *inet;
	bool dev_match;

	अगर (!net_eq(sock_net(sk), net) ||
	    udp_sk(sk)->udp_port_hash != hnum ||
	    ipv6_only_sock(sk))
		वापस -1;

	अगर (sk->sk_rcv_saddr != daddr)
		वापस -1;

	score = (sk->sk_family == PF_INET) ? 2 : 1;

	inet = inet_sk(sk);
	अगर (inet->inet_daddr) अणु
		अगर (inet->inet_daddr != saddr)
			वापस -1;
		score += 4;
	पूर्ण

	अगर (inet->inet_dport) अणु
		अगर (inet->inet_dport != sport)
			वापस -1;
		score += 4;
	पूर्ण

	dev_match = udp_sk_bound_dev_eq(net, sk->sk_bound_dev_अगर,
					dअगर, sdअगर);
	अगर (!dev_match)
		वापस -1;
	score += 4;

	अगर (READ_ONCE(sk->sk_incoming_cpu) == raw_smp_processor_id())
		score++;
	वापस score;
पूर्ण

अटल u32 udp_ehashfn(स्थिर काष्ठा net *net, स्थिर __be32 laddr,
		       स्थिर __u16 lport, स्थिर __be32 faddr,
		       स्थिर __be16 fport)
अणु
	अटल u32 udp_ehash_secret __पढ़ो_mostly;

	net_get_अक्रमom_once(&udp_ehash_secret, माप(udp_ehash_secret));

	वापस __inet_ehashfn(laddr, lport, faddr, fport,
			      udp_ehash_secret + net_hash_mix(net));
पूर्ण

अटल काष्ठा sock *lookup_reuseport(काष्ठा net *net, काष्ठा sock *sk,
				     काष्ठा sk_buff *skb,
				     __be32 saddr, __be16 sport,
				     __be32 daddr, अचिन्हित लघु hnum)
अणु
	काष्ठा sock *reuse_sk = शून्य;
	u32 hash;

	अगर (sk->sk_reuseport && sk->sk_state != TCP_ESTABLISHED) अणु
		hash = udp_ehashfn(net, daddr, hnum, saddr, sport);
		reuse_sk = reuseport_select_sock(sk, hash, skb,
						 माप(काष्ठा udphdr));
	पूर्ण
	वापस reuse_sk;
पूर्ण

/* called with rcu_पढ़ो_lock() */
अटल काष्ठा sock *udp4_lib_lookup2(काष्ठा net *net,
				     __be32 saddr, __be16 sport,
				     __be32 daddr, अचिन्हित पूर्णांक hnum,
				     पूर्णांक dअगर, पूर्णांक sdअगर,
				     काष्ठा udp_hslot *hslot2,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk, *result;
	पूर्णांक score, badness;

	result = शून्य;
	badness = 0;
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

अटल काष्ठा sock *udp4_lookup_run_bpf(काष्ठा net *net,
					काष्ठा udp_table *udptable,
					काष्ठा sk_buff *skb,
					__be32 saddr, __be16 sport,
					__be32 daddr, u16 hnum)
अणु
	काष्ठा sock *sk, *reuse_sk;
	bool no_reuseport;

	अगर (udptable != &udp_table)
		वापस शून्य; /* only UDP is supported */

	no_reuseport = bpf_sk_lookup_run_v4(net, IPPROTO_UDP,
					    saddr, sport, daddr, hnum, &sk);
	अगर (no_reuseport || IS_ERR_OR_शून्य(sk))
		वापस sk;

	reuse_sk = lookup_reuseport(net, sk, skb, saddr, sport, daddr, hnum);
	अगर (reuse_sk)
		sk = reuse_sk;
	वापस sk;
पूर्ण

/* UDP is nearly always wildcards out the wazoo, it makes no sense to try
 * harder than this. -DaveM
 */
काष्ठा sock *__udp4_lib_lookup(काष्ठा net *net, __be32 saddr,
		__be16 sport, __be32 daddr, __be16 dport, पूर्णांक dअगर,
		पूर्णांक sdअगर, काष्ठा udp_table *udptable, काष्ठा sk_buff *skb)
अणु
	अचिन्हित लघु hnum = ntohs(dport);
	अचिन्हित पूर्णांक hash2, slot2;
	काष्ठा udp_hslot *hslot2;
	काष्ठा sock *result, *sk;

	hash2 = ipv4_portaddr_hash(net, daddr, hnum);
	slot2 = hash2 & udptable->mask;
	hslot2 = &udptable->hash2[slot2];

	/* Lookup connected or non-wildcard socket */
	result = udp4_lib_lookup2(net, saddr, sport,
				  daddr, hnum, dअगर, sdअगर,
				  hslot2, skb);
	अगर (!IS_ERR_OR_शून्य(result) && result->sk_state == TCP_ESTABLISHED)
		जाओ करोne;

	/* Lookup redirect from BPF */
	अगर (अटल_branch_unlikely(&bpf_sk_lookup_enabled)) अणु
		sk = udp4_lookup_run_bpf(net, udptable, skb,
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
	hash2 = ipv4_portaddr_hash(net, htonl(INADDR_ANY), hnum);
	slot2 = hash2 & udptable->mask;
	hslot2 = &udptable->hash2[slot2];

	result = udp4_lib_lookup2(net, saddr, sport,
				  htonl(INADDR_ANY), hnum, dअगर, sdअगर,
				  hslot2, skb);
करोne:
	अगर (IS_ERR(result))
		वापस शून्य;
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(__udp4_lib_lookup);

अटल अंतरभूत काष्ठा sock *__udp4_lib_lookup_skb(काष्ठा sk_buff *skb,
						 __be16 sport, __be16 dport,
						 काष्ठा udp_table *udptable)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

	वापस __udp4_lib_lookup(dev_net(skb->dev), iph->saddr, sport,
				 iph->daddr, dport, inet_iअगर(skb),
				 inet_sdअगर(skb), udptable, skb);
पूर्ण

काष्ठा sock *udp4_lib_lookup_skb(स्थिर काष्ठा sk_buff *skb,
				 __be16 sport, __be16 dport)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

	वापस __udp4_lib_lookup(dev_net(skb->dev), iph->saddr, sport,
				 iph->daddr, dport, inet_iअगर(skb),
				 inet_sdअगर(skb), &udp_table, शून्य);
पूर्ण

/* Must be called under rcu_पढ़ो_lock().
 * Does increment socket refcount.
 */
#अगर IS_ENABLED(CONFIG_NF_TPROXY_IPV4) || IS_ENABLED(CONFIG_NF_SOCKET_IPV4)
काष्ठा sock *udp4_lib_lookup(काष्ठा net *net, __be32 saddr, __be16 sport,
			     __be32 daddr, __be16 dport, पूर्णांक dअगर)
अणु
	काष्ठा sock *sk;

	sk = __udp4_lib_lookup(net, saddr, sport, daddr, dport,
			       dअगर, 0, &udp_table, शून्य);
	अगर (sk && !refcount_inc_not_zero(&sk->sk_refcnt))
		sk = शून्य;
	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(udp4_lib_lookup);
#पूर्ण_अगर

अटल अंतरभूत bool __udp_is_mcast_sock(काष्ठा net *net, काष्ठा sock *sk,
				       __be16 loc_port, __be32 loc_addr,
				       __be16 rmt_port, __be32 rmt_addr,
				       पूर्णांक dअगर, पूर्णांक sdअगर, अचिन्हित लघु hnum)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);

	अगर (!net_eq(sock_net(sk), net) ||
	    udp_sk(sk)->udp_port_hash != hnum ||
	    (inet->inet_daddr && inet->inet_daddr != rmt_addr) ||
	    (inet->inet_dport != rmt_port && inet->inet_dport) ||
	    (inet->inet_rcv_saddr && inet->inet_rcv_saddr != loc_addr) ||
	    ipv6_only_sock(sk) ||
	    !udp_sk_bound_dev_eq(net, sk->sk_bound_dev_अगर, dअगर, sdअगर))
		वापस false;
	अगर (!ip_mc_sf_allow(sk, loc_addr, rmt_addr, dअगर, sdअगर))
		वापस false;
	वापस true;
पूर्ण

DEFINE_STATIC_KEY_FALSE(udp_encap_needed_key);
व्योम udp_encap_enable(व्योम)
अणु
	अटल_branch_inc(&udp_encap_needed_key);
पूर्ण
EXPORT_SYMBOL(udp_encap_enable);

व्योम udp_encap_disable(व्योम)
अणु
	अटल_branch_dec(&udp_encap_needed_key);
पूर्ण
EXPORT_SYMBOL(udp_encap_disable);

/* Handler क्रम tunnels with arbitrary destination ports: no socket lookup, go
 * through error handlers in encapsulations looking क्रम a match.
 */
अटल पूर्णांक __udp4_lib_err_encap_no_sk(काष्ठा sk_buff *skb, u32 info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_IPTUN_ENCAP_OPS; i++) अणु
		पूर्णांक (*handler)(काष्ठा sk_buff *skb, u32 info);
		स्थिर काष्ठा ip_tunnel_encap_ops *encap;

		encap = rcu_dereference(iptun_encaps[i]);
		अगर (!encap)
			जारी;
		handler = encap->err_handler;
		अगर (handler && !handler(skb, info))
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
अटल काष्ठा sock *__udp4_lib_err_encap(काष्ठा net *net,
					 स्थिर काष्ठा iphdr *iph,
					 काष्ठा udphdr *uh,
					 काष्ठा udp_table *udptable,
					 काष्ठा sk_buff *skb, u32 info)
अणु
	पूर्णांक network_offset, transport_offset;
	काष्ठा sock *sk;

	network_offset = skb_network_offset(skb);
	transport_offset = skb_transport_offset(skb);

	/* Network header needs to poपूर्णांक to the outer IPv4 header inside ICMP */
	skb_reset_network_header(skb);

	/* Transport header needs to poपूर्णांक to the UDP header */
	skb_set_transport_header(skb, iph->ihl << 2);

	sk = __udp4_lib_lookup(net, iph->daddr, uh->source,
			       iph->saddr, uh->dest, skb->dev->अगरindex, 0,
			       udptable, शून्य);
	अगर (sk) अणु
		पूर्णांक (*lookup)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
		काष्ठा udp_sock *up = udp_sk(sk);

		lookup = READ_ONCE(up->encap_err_lookup);
		अगर (!lookup || lookup(sk, skb))
			sk = शून्य;
	पूर्ण

	अगर (!sk)
		sk = ERR_PTR(__udp4_lib_err_encap_no_sk(skb, info));

	skb_set_transport_header(skb, transport_offset);
	skb_set_network_header(skb, network_offset);

	वापस sk;
पूर्ण

/*
 * This routine is called by the ICMP module when it माला_लो some
 * sort of error condition.  If err < 0 then the socket should
 * be बंदd and the error वापसed to the user.  If err > 0
 * it's just the icmp type << 8 | icmp code.
 * Header poपूर्णांकs to the ip header of the error packet. We move
 * on past this. Then (as it used to claim beक्रमe adjusपंचांगent)
 * header poपूर्णांकs to the first 8 bytes of the udp header.  We need
 * to find the appropriate port.
 */

पूर्णांक __udp4_lib_err(काष्ठा sk_buff *skb, u32 info, काष्ठा udp_table *udptable)
अणु
	काष्ठा inet_sock *inet;
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	काष्ठा udphdr *uh = (काष्ठा udphdr *)(skb->data+(iph->ihl<<2));
	स्थिर पूर्णांक type = icmp_hdr(skb)->type;
	स्थिर पूर्णांक code = icmp_hdr(skb)->code;
	bool tunnel = false;
	काष्ठा sock *sk;
	पूर्णांक harderr;
	पूर्णांक err;
	काष्ठा net *net = dev_net(skb->dev);

	sk = __udp4_lib_lookup(net, iph->daddr, uh->dest,
			       iph->saddr, uh->source, skb->dev->अगरindex,
			       inet_sdअगर(skb), udptable, शून्य);
	अगर (!sk || udp_sk(sk)->encap_type) अणु
		/* No socket क्रम error: try tunnels beक्रमe discarding */
		sk = ERR_PTR(-ENOENT);
		अगर (अटल_branch_unlikely(&udp_encap_needed_key)) अणु
			sk = __udp4_lib_err_encap(net, iph, uh, udptable, skb,
						  info);
			अगर (!sk)
				वापस 0;
		पूर्ण

		अगर (IS_ERR(sk)) अणु
			__ICMP_INC_STATS(net, ICMP_MIB_INERRORS);
			वापस PTR_ERR(sk);
		पूर्ण

		tunnel = true;
	पूर्ण

	err = 0;
	harderr = 0;
	inet = inet_sk(sk);

	चयन (type) अणु
	शेष:
	हाल ICMP_TIME_EXCEEDED:
		err = EHOSTUNREACH;
		अवरोध;
	हाल ICMP_SOURCE_QUENCH:
		जाओ out;
	हाल ICMP_PARAMETERPROB:
		err = EPROTO;
		harderr = 1;
		अवरोध;
	हाल ICMP_DEST_UNREACH:
		अगर (code == ICMP_FRAG_NEEDED) अणु /* Path MTU discovery */
			ipv4_sk_update_pmtu(skb, sk, info);
			अगर (inet->pmtudisc != IP_PMTUDISC_DONT) अणु
				err = EMSGSIZE;
				harderr = 1;
				अवरोध;
			पूर्ण
			जाओ out;
		पूर्ण
		err = EHOSTUNREACH;
		अगर (code <= NR_ICMP_UNREACH) अणु
			harderr = icmp_err_convert[code].fatal;
			err = icmp_err_convert[code].त्रुटि_सं;
		पूर्ण
		अवरोध;
	हाल ICMP_REसूचीECT:
		ipv4_sk_redirect(skb, sk);
		जाओ out;
	पूर्ण

	/*
	 *      RFC1122: OK.  Passes ICMP errors back to application, as per
	 *	4.1.3.3.
	 */
	अगर (tunnel) अणु
		/* ...not क्रम tunnels though: we करोn't have a sending socket */
		जाओ out;
	पूर्ण
	अगर (!inet->recverr) अणु
		अगर (!harderr || sk->sk_state != TCP_ESTABLISHED)
			जाओ out;
	पूर्ण अन्यथा
		ip_icmp_error(sk, skb, err, uh->dest, info, (u8 *)(uh+1));

	sk->sk_err = err;
	sk->sk_error_report(sk);
out:
	वापस 0;
पूर्ण

पूर्णांक udp_err(काष्ठा sk_buff *skb, u32 info)
अणु
	वापस __udp4_lib_err(skb, info, &udp_table);
पूर्ण

/*
 * Throw away all pending data and cancel the corking. Socket is locked.
 */
व्योम udp_flush_pending_frames(काष्ठा sock *sk)
अणु
	काष्ठा udp_sock *up = udp_sk(sk);

	अगर (up->pending) अणु
		up->len = 0;
		up->pending = 0;
		ip_flush_pending_frames(sk);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(udp_flush_pending_frames);

/**
 * 	udp4_hwcsum  -  handle outgoing HW checksumming
 * 	@skb: 	sk_buff containing the filled-in UDP header
 * 	        (checksum field must be zeroed out)
 *	@src:	source IP address
 *	@dst:	destination IP address
 */
व्योम udp4_hwcsum(काष्ठा sk_buff *skb, __be32 src, __be32 dst)
अणु
	काष्ठा udphdr *uh = udp_hdr(skb);
	पूर्णांक offset = skb_transport_offset(skb);
	पूर्णांक len = skb->len - offset;
	पूर्णांक hlen = len;
	__wsum csum = 0;

	अगर (!skb_has_frag_list(skb)) अणु
		/*
		 * Only one fragment on the socket.
		 */
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = दुरत्व(काष्ठा udphdr, check);
		uh->check = ~csum_tcpudp_magic(src, dst, len,
					       IPPROTO_UDP, 0);
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *frags;

		/*
		 * HW-checksum won't work as there are two or more
		 * fragments on the socket so that all csums of sk_buffs
		 * should be together
		 */
		skb_walk_frags(skb, frags) अणु
			csum = csum_add(csum, frags->csum);
			hlen -= frags->len;
		पूर्ण

		csum = skb_checksum(skb, offset, hlen, csum);
		skb->ip_summed = CHECKSUM_NONE;

		uh->check = csum_tcpudp_magic(src, dst, len, IPPROTO_UDP, csum);
		अगर (uh->check == 0)
			uh->check = CSUM_MANGLED_0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(udp4_hwcsum);

/* Function to set UDP checksum क्रम an IPv4 UDP packet. This is पूर्णांकended
 * क्रम the simple हाल like when setting the checksum क्रम a UDP tunnel.
 */
व्योम udp_set_csum(bool nocheck, काष्ठा sk_buff *skb,
		  __be32 saddr, __be32 daddr, पूर्णांक len)
अणु
	काष्ठा udphdr *uh = udp_hdr(skb);

	अगर (nocheck) अणु
		uh->check = 0;
	पूर्ण अन्यथा अगर (skb_is_gso(skb)) अणु
		uh->check = ~udp_v4_check(len, saddr, daddr, 0);
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		uh->check = 0;
		uh->check = udp_v4_check(len, saddr, daddr, lco_csum(skb));
		अगर (uh->check == 0)
			uh->check = CSUM_MANGLED_0;
	पूर्ण अन्यथा अणु
		skb->ip_summed = CHECKSUM_PARTIAL;
		skb->csum_start = skb_transport_header(skb) - skb->head;
		skb->csum_offset = दुरत्व(काष्ठा udphdr, check);
		uh->check = ~udp_v4_check(len, saddr, daddr, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(udp_set_csum);

अटल पूर्णांक udp_send_skb(काष्ठा sk_buff *skb, काष्ठा flowi4 *fl4,
			काष्ठा inet_cork *cork)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा udphdr *uh;
	पूर्णांक err;
	पूर्णांक is_udplite = IS_UDPLITE(sk);
	पूर्णांक offset = skb_transport_offset(skb);
	पूर्णांक len = skb->len - offset;
	पूर्णांक datalen = len - माप(*uh);
	__wsum csum = 0;

	/*
	 * Create a UDP header
	 */
	uh = udp_hdr(skb);
	uh->source = inet->inet_sport;
	uh->dest = fl4->fl4_dport;
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
		अगर (sk->sk_no_check_tx) अणु
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

	अगर (is_udplite)  				 /*     UDP-Lite      */
		csum = udplite_csum(skb);

	अन्यथा अगर (sk->sk_no_check_tx) अणु			 /* UDP csum off */

		skb->ip_summed = CHECKSUM_NONE;
		जाओ send;

	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु /* UDP hardware csum */
csum_partial:

		udp4_hwcsum(skb, fl4->saddr, fl4->daddr);
		जाओ send;

	पूर्ण अन्यथा
		csum = udp_csum(skb);

	/* add protocol-dependent pseuकरो-header */
	uh->check = csum_tcpudp_magic(fl4->saddr, fl4->daddr, len,
				      sk->sk_protocol, csum);
	अगर (uh->check == 0)
		uh->check = CSUM_MANGLED_0;

send:
	err = ip_send_skb(sock_net(sk), skb);
	अगर (err) अणु
		अगर (err == -ENOBUFS && !inet->recverr) अणु
			UDP_INC_STATS(sock_net(sk),
				      UDP_MIB_SNDBUFERRORS, is_udplite);
			err = 0;
		पूर्ण
	पूर्ण अन्यथा
		UDP_INC_STATS(sock_net(sk),
			      UDP_MIB_OUTDATAGRAMS, is_udplite);
	वापस err;
पूर्ण

/*
 * Push out all pending data as one UDP datagram. Socket is locked.
 */
पूर्णांक udp_push_pending_frames(काष्ठा sock *sk)
अणु
	काष्ठा udp_sock  *up = udp_sk(sk);
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा flowi4 *fl4 = &inet->cork.fl.u.ip4;
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;

	skb = ip_finish_skb(sk, fl4);
	अगर (!skb)
		जाओ out;

	err = udp_send_skb(skb, fl4, &inet->cork.base);

out:
	up->len = 0;
	up->pending = 0;
	वापस err;
पूर्ण
EXPORT_SYMBOL(udp_push_pending_frames);

अटल पूर्णांक __udp_cmsg_send(काष्ठा cmsghdr *cmsg, u16 *gso_size)
अणु
	चयन (cmsg->cmsg_type) अणु
	हाल UDP_SEGMENT:
		अगर (cmsg->cmsg_len != CMSG_LEN(माप(__u16)))
			वापस -EINVAL;
		*gso_size = *(__u16 *)CMSG_DATA(cmsg);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक udp_cmsg_send(काष्ठा sock *sk, काष्ठा msghdr *msg, u16 *gso_size)
अणु
	काष्ठा cmsghdr *cmsg;
	bool need_ip = false;
	पूर्णांक err;

	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg))
			वापस -EINVAL;

		अगर (cmsg->cmsg_level != SOL_UDP) अणु
			need_ip = true;
			जारी;
		पूर्ण

		err = __udp_cmsg_send(cmsg, gso_size);
		अगर (err)
			वापस err;
	पूर्ण

	वापस need_ip;
पूर्ण
EXPORT_SYMBOL_GPL(udp_cmsg_send);

पूर्णांक udp_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा udp_sock *up = udp_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_in *, usin, msg->msg_name);
	काष्ठा flowi4 fl4_stack;
	काष्ठा flowi4 *fl4;
	पूर्णांक ulen = len;
	काष्ठा ipcm_cookie ipc;
	काष्ठा rtable *rt = शून्य;
	पूर्णांक मुक्त = 0;
	पूर्णांक connected = 0;
	__be32 daddr, faddr, saddr;
	__be16 dport;
	u8  tos;
	पूर्णांक err, is_udplite = IS_UDPLITE(sk);
	पूर्णांक corkreq = up->corkflag || msg->msg_flags&MSG_MORE;
	पूर्णांक (*getfrag)(व्योम *, अक्षर *, पूर्णांक, पूर्णांक, पूर्णांक, काष्ठा sk_buff *);
	काष्ठा sk_buff *skb;
	काष्ठा ip_options_data opt_copy;

	अगर (len > 0xFFFF)
		वापस -EMSGSIZE;

	/*
	 *	Check the flags.
	 */

	अगर (msg->msg_flags & MSG_OOB) /* Mirror BSD error message compatibility */
		वापस -EOPNOTSUPP;

	getfrag = is_udplite ? udplite_getfrag : ip_generic_getfrag;

	fl4 = &inet->cork.fl.u.ip4;
	अगर (up->pending) अणु
		/*
		 * There are pending frames.
		 * The socket lock must be held जबतक it's corked.
		 */
		lock_sock(sk);
		अगर (likely(up->pending)) अणु
			अगर (unlikely(up->pending != AF_INET)) अणु
				release_sock(sk);
				वापस -EINVAL;
			पूर्ण
			जाओ करो_append_data;
		पूर्ण
		release_sock(sk);
	पूर्ण
	ulen += माप(काष्ठा udphdr);

	/*
	 *	Get and verअगरy the address.
	 */
	अगर (usin) अणु
		अगर (msg->msg_namelen < माप(*usin))
			वापस -EINVAL;
		अगर (usin->sin_family != AF_INET) अणु
			अगर (usin->sin_family != AF_UNSPEC)
				वापस -EAFNOSUPPORT;
		पूर्ण

		daddr = usin->sin_addr.s_addr;
		dport = usin->sin_port;
		अगर (dport == 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (sk->sk_state != TCP_ESTABLISHED)
			वापस -EDESTADDRREQ;
		daddr = inet->inet_daddr;
		dport = inet->inet_dport;
		/* Open fast path क्रम connected socket.
		   Route will not be used, अगर at least one option is set.
		 */
		connected = 1;
	पूर्ण

	ipcm_init_sk(&ipc, inet);
	ipc.gso_size = up->gso_size;

	अगर (msg->msg_controllen) अणु
		err = udp_cmsg_send(sk, msg, &ipc.gso_size);
		अगर (err > 0)
			err = ip_cmsg_send(sk, msg, &ipc,
					   sk->sk_family == AF_INET6);
		अगर (unlikely(err < 0)) अणु
			kमुक्त(ipc.opt);
			वापस err;
		पूर्ण
		अगर (ipc.opt)
			मुक्त = 1;
		connected = 0;
	पूर्ण
	अगर (!ipc.opt) अणु
		काष्ठा ip_options_rcu *inet_opt;

		rcu_पढ़ो_lock();
		inet_opt = rcu_dereference(inet->inet_opt);
		अगर (inet_opt) अणु
			स_नकल(&opt_copy, inet_opt,
			       माप(*inet_opt) + inet_opt->opt.optlen);
			ipc.opt = &opt_copy.opt;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (cgroup_bpf_enabled(BPF_CGROUP_UDP4_SENDMSG) && !connected) अणु
		err = BPF_CGROUP_RUN_PROG_UDP4_SENDMSG_LOCK(sk,
					    (काष्ठा sockaddr *)usin, &ipc.addr);
		अगर (err)
			जाओ out_मुक्त;
		अगर (usin) अणु
			अगर (usin->sin_port == 0) अणु
				/* BPF program set invalid port. Reject it. */
				err = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
			daddr = usin->sin_addr.s_addr;
			dport = usin->sin_port;
		पूर्ण
	पूर्ण

	saddr = ipc.addr;
	ipc.addr = faddr = daddr;

	अगर (ipc.opt && ipc.opt->opt.srr) अणु
		अगर (!daddr) अणु
			err = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		faddr = ipc.opt->opt.faddr;
		connected = 0;
	पूर्ण
	tos = get_rttos(&ipc, inet);
	अगर (sock_flag(sk, SOCK_LOCALROUTE) ||
	    (msg->msg_flags & MSG_DONTROUTE) ||
	    (ipc.opt && ipc.opt->opt.is_strictroute)) अणु
		tos |= RTO_ONLINK;
		connected = 0;
	पूर्ण

	अगर (ipv4_is_multicast(daddr)) अणु
		अगर (!ipc.oअगर || netअगर_index_is_l3_master(sock_net(sk), ipc.oअगर))
			ipc.oअगर = inet->mc_index;
		अगर (!saddr)
			saddr = inet->mc_addr;
		connected = 0;
	पूर्ण अन्यथा अगर (!ipc.oअगर) अणु
		ipc.oअगर = inet->uc_index;
	पूर्ण अन्यथा अगर (ipv4_is_lbcast(daddr) && inet->uc_index) अणु
		/* oअगर is set, packet is to local broadcast and
		 * uc_index is set. oअगर is most likely set
		 * by sk_bound_dev_अगर. If uc_index != oअगर check अगर the
		 * oअगर is an L3 master and uc_index is an L3 slave.
		 * If so, we want to allow the send using the uc_index.
		 */
		अगर (ipc.oअगर != inet->uc_index &&
		    ipc.oअगर == l3mdev_master_अगरindex_by_index(sock_net(sk),
							      inet->uc_index)) अणु
			ipc.oअगर = inet->uc_index;
		पूर्ण
	पूर्ण

	अगर (connected)
		rt = (काष्ठा rtable *)sk_dst_check(sk, 0);

	अगर (!rt) अणु
		काष्ठा net *net = sock_net(sk);
		__u8 flow_flags = inet_sk_flowi_flags(sk);

		fl4 = &fl4_stack;

		flowi4_init_output(fl4, ipc.oअगर, ipc.sockc.mark, tos,
				   RT_SCOPE_UNIVERSE, sk->sk_protocol,
				   flow_flags,
				   faddr, saddr, dport, inet->inet_sport,
				   sk->sk_uid);

		security_sk_classअगरy_flow(sk, flowi4_to_flowi_common(fl4));
		rt = ip_route_output_flow(net, fl4, sk);
		अगर (IS_ERR(rt)) अणु
			err = PTR_ERR(rt);
			rt = शून्य;
			अगर (err == -ENETUNREACH)
				IP_INC_STATS(net, IPSTATS_MIB_OUTNOROUTES);
			जाओ out;
		पूर्ण

		err = -EACCES;
		अगर ((rt->rt_flags & RTCF_BROADCAST) &&
		    !sock_flag(sk, SOCK_BROADCAST))
			जाओ out;
		अगर (connected)
			sk_dst_set(sk, dst_clone(&rt->dst));
	पूर्ण

	अगर (msg->msg_flags&MSG_CONFIRM)
		जाओ करो_confirm;
back_from_confirm:

	saddr = fl4->saddr;
	अगर (!ipc.addr)
		daddr = ipc.addr = fl4->daddr;

	/* Lockless fast path क्रम the non-corking हाल. */
	अगर (!corkreq) अणु
		काष्ठा inet_cork cork;

		skb = ip_make_skb(sk, fl4, getfrag, msg, ulen,
				  माप(काष्ठा udphdr), &ipc, &rt,
				  &cork, msg->msg_flags);
		err = PTR_ERR(skb);
		अगर (!IS_ERR_OR_शून्य(skb))
			err = udp_send_skb(skb, fl4, &cork);
		जाओ out;
	पूर्ण

	lock_sock(sk);
	अगर (unlikely(up->pending)) अणु
		/* The socket is alपढ़ोy corked जबतक preparing it. */
		/* ... which is an evident application bug. --ANK */
		release_sock(sk);

		net_dbg_ratelimited("socket already corked\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण
	/*
	 *	Now cork the socket to pend data.
	 */
	fl4 = &inet->cork.fl.u.ip4;
	fl4->daddr = daddr;
	fl4->saddr = saddr;
	fl4->fl4_dport = dport;
	fl4->fl4_sport = inet->inet_sport;
	up->pending = AF_INET;

करो_append_data:
	up->len += ulen;
	err = ip_append_data(sk, fl4, getfrag, msg, ulen,
			     माप(काष्ठा udphdr), &ipc, &rt,
			     corkreq ? msg->msg_flags|MSG_MORE : msg->msg_flags);
	अगर (err)
		udp_flush_pending_frames(sk);
	अन्यथा अगर (!corkreq)
		err = udp_push_pending_frames(sk);
	अन्यथा अगर (unlikely(skb_queue_empty(&sk->sk_ग_लिखो_queue)))
		up->pending = 0;
	release_sock(sk);

out:
	ip_rt_put(rt);
out_मुक्त:
	अगर (मुक्त)
		kमुक्त(ipc.opt);
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
		UDP_INC_STATS(sock_net(sk),
			      UDP_MIB_SNDBUFERRORS, is_udplite);
	पूर्ण
	वापस err;

करो_confirm:
	अगर (msg->msg_flags & MSG_PROBE)
		dst_confirm_neigh(&rt->dst, &fl4->daddr);
	अगर (!(msg->msg_flags&MSG_PROBE) || len)
		जाओ back_from_confirm;
	err = 0;
	जाओ out;
पूर्ण
EXPORT_SYMBOL(udp_sendmsg);

पूर्णांक udp_sendpage(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
		 माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	काष्ठा udp_sock *up = udp_sk(sk);
	पूर्णांक ret;

	अगर (flags & MSG_SENDPAGE_NOTLAST)
		flags |= MSG_MORE;

	अगर (!up->pending) अणु
		काष्ठा msghdr msg = अणु	.msg_flags = flags|MSG_MORE पूर्ण;

		/* Call udp_sendmsg to specअगरy destination address which
		 * sendpage पूर्णांकerface can't pass.
		 * This will succeed only when the socket is connected.
		 */
		ret = udp_sendmsg(sk, &msg, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	lock_sock(sk);

	अगर (unlikely(!up->pending)) अणु
		release_sock(sk);

		net_dbg_ratelimited("cork failed\n");
		वापस -EINVAL;
	पूर्ण

	ret = ip_append_page(sk, &inet->cork.fl.u.ip4,
			     page, offset, size, flags);
	अगर (ret == -EOPNOTSUPP) अणु
		release_sock(sk);
		वापस sock_no_sendpage(sk->sk_socket, page, offset,
					size, flags);
	पूर्ण
	अगर (ret < 0) अणु
		udp_flush_pending_frames(sk);
		जाओ out;
	पूर्ण

	up->len += size;
	अगर (!(up->corkflag || (flags&MSG_MORE)))
		ret = udp_push_pending_frames(sk);
	अगर (!ret)
		ret = size;
out:
	release_sock(sk);
	वापस ret;
पूर्ण

#घोषणा UDP_SKB_IS_STATELESS 0x80000000

/* all head states (dst, sk, nf conntrack) except skb extensions are
 * cleared by udp_rcv().
 *
 * We need to preserve secpath, अगर present, to eventually process
 * IP_CMSG_PASSSEC at recvmsg() समय.
 *
 * Other extensions can be cleared.
 */
अटल bool udp_try_make_stateless(काष्ठा sk_buff *skb)
अणु
	अगर (!skb_has_extensions(skb))
		वापस true;

	अगर (!secpath_exists(skb)) अणु
		skb_ext_reset(skb);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम udp_set_dev_scratch(काष्ठा sk_buff *skb)
अणु
	काष्ठा udp_dev_scratch *scratch = udp_skb_scratch(skb);

	BUILD_BUG_ON(माप(काष्ठा udp_dev_scratch) > माप(दीर्घ));
	scratch->_tsize_state = skb->truesize;
#अगर BITS_PER_LONG == 64
	scratch->len = skb->len;
	scratch->csum_unnecessary = !!skb_csum_unnecessary(skb);
	scratch->is_linear = !skb_is_nonlinear(skb);
#पूर्ण_अगर
	अगर (udp_try_make_stateless(skb))
		scratch->_tsize_state |= UDP_SKB_IS_STATELESS;
पूर्ण

अटल व्योम udp_skb_csum_unnecessary_set(काष्ठा sk_buff *skb)
अणु
	/* We come here after udp_lib_checksum_complete() वापसed 0.
	 * This means that __skb_checksum_complete() might have
	 * set skb->csum_valid to 1.
	 * On 64bit platक्रमms, we can set csum_unnecessary
	 * to true, but only अगर the skb is not shared.
	 */
#अगर BITS_PER_LONG == 64
	अगर (!skb_shared(skb))
		udp_skb_scratch(skb)->csum_unnecessary = true;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक udp_skb_truesize(काष्ठा sk_buff *skb)
अणु
	वापस udp_skb_scratch(skb)->_tsize_state & ~UDP_SKB_IS_STATELESS;
पूर्ण

अटल bool udp_skb_has_head_state(काष्ठा sk_buff *skb)
अणु
	वापस !(udp_skb_scratch(skb)->_tsize_state & UDP_SKB_IS_STATELESS);
पूर्ण

/* fully reclaim rmem/fwd memory allocated क्रम skb */
अटल व्योम udp_rmem_release(काष्ठा sock *sk, पूर्णांक size, पूर्णांक partial,
			     bool rx_queue_lock_held)
अणु
	काष्ठा udp_sock *up = udp_sk(sk);
	काष्ठा sk_buff_head *sk_queue;
	पूर्णांक amt;

	अगर (likely(partial)) अणु
		up->क्रमward_deficit += size;
		size = up->क्रमward_deficit;
		अगर (size < (sk->sk_rcvbuf >> 2) &&
		    !skb_queue_empty(&up->पढ़ोer_queue))
			वापस;
	पूर्ण अन्यथा अणु
		size += up->क्रमward_deficit;
	पूर्ण
	up->क्रमward_deficit = 0;

	/* acquire the sk_receive_queue क्रम fwd allocated memory scheduling,
	 * अगर the called करोn't held it alपढ़ोy
	 */
	sk_queue = &sk->sk_receive_queue;
	अगर (!rx_queue_lock_held)
		spin_lock(&sk_queue->lock);


	sk->sk_क्रमward_alloc += size;
	amt = (sk->sk_क्रमward_alloc - partial) & ~(SK_MEM_QUANTUM - 1);
	sk->sk_क्रमward_alloc -= amt;

	अगर (amt)
		__sk_mem_reduce_allocated(sk, amt >> SK_MEM_QUANTUM_SHIFT);

	atomic_sub(size, &sk->sk_rmem_alloc);

	/* this can save us from acquiring the rx queue lock on next receive */
	skb_queue_splice_tail_init(sk_queue, &up->पढ़ोer_queue);

	अगर (!rx_queue_lock_held)
		spin_unlock(&sk_queue->lock);
पूर्ण

/* Note: called with पढ़ोer_queue.lock held.
 * Instead of using skb->truesize here, find a copy of it in skb->dev_scratch
 * This aव्योमs a cache line miss जबतक receive_queue lock is held.
 * Look at __udp_enqueue_schedule_skb() to find where this copy is करोne.
 */
व्योम udp_skb_deकाष्ठाor(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	prefetch(&skb->data);
	udp_rmem_release(sk, udp_skb_truesize(skb), 1, false);
पूर्ण
EXPORT_SYMBOL(udp_skb_deकाष्ठाor);

/* as above, but the caller held the rx queue lock, too */
अटल व्योम udp_skb_dtor_locked(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	prefetch(&skb->data);
	udp_rmem_release(sk, udp_skb_truesize(skb), 1, true);
पूर्ण

/* Idea of busylocks is to let producers grab an extra spinlock
 * to relieve pressure on the receive_queue spinlock shared by consumer.
 * Under flood, this means that only one producer can be in line
 * trying to acquire the receive_queue spinlock.
 * These busylock can be allocated on a per cpu manner, instead of a
 * per socket one (that would consume a cache line per socket)
 */
अटल पूर्णांक udp_busylocks_log __पढ़ो_mostly;
अटल spinlock_t *udp_busylocks __पढ़ो_mostly;

अटल spinlock_t *busylock_acquire(व्योम *ptr)
अणु
	spinlock_t *busy;

	busy = udp_busylocks + hash_ptr(ptr, udp_busylocks_log);
	spin_lock(busy);
	वापस busy;
पूर्ण

अटल व्योम busylock_release(spinlock_t *busy)
अणु
	अगर (busy)
		spin_unlock(busy);
पूर्ण

पूर्णांक __udp_enqueue_schedule_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff_head *list = &sk->sk_receive_queue;
	पूर्णांक rmem, delta, amt, err = -ENOMEM;
	spinlock_t *busy = शून्य;
	पूर्णांक size;

	/* try to aव्योम the costly atomic add/sub pair when the receive
	 * queue is full; always allow at least a packet
	 */
	rmem = atomic_पढ़ो(&sk->sk_rmem_alloc);
	अगर (rmem > sk->sk_rcvbuf)
		जाओ drop;

	/* Under mem pressure, it might be helpful to help udp_recvmsg()
	 * having linear skbs :
	 * - Reduce memory overhead and thus increase receive queue capacity
	 * - Less cache line misses at copyout() समय
	 * - Less work at consume_skb() (less alien page frag मुक्तing)
	 */
	अगर (rmem > (sk->sk_rcvbuf >> 1)) अणु
		skb_condense(skb);

		busy = busylock_acquire(sk);
	पूर्ण
	size = skb->truesize;
	udp_set_dev_scratch(skb);

	/* we drop only अगर the receive buf is full and the receive
	 * queue contains some other skb
	 */
	rmem = atomic_add_वापस(size, &sk->sk_rmem_alloc);
	अगर (rmem > (size + (अचिन्हित पूर्णांक)sk->sk_rcvbuf))
		जाओ unअक्षरge_drop;

	spin_lock(&list->lock);
	अगर (size >= sk->sk_क्रमward_alloc) अणु
		amt = sk_mem_pages(size);
		delta = amt << SK_MEM_QUANTUM_SHIFT;
		अगर (!__sk_mem_उठाओ_allocated(sk, delta, amt, SK_MEM_RECV)) अणु
			err = -ENOBUFS;
			spin_unlock(&list->lock);
			जाओ unअक्षरge_drop;
		पूर्ण

		sk->sk_क्रमward_alloc += delta;
	पूर्ण

	sk->sk_क्रमward_alloc -= size;

	/* no need to setup a deकाष्ठाor, we will explicitly release the
	 * क्रमward allocated memory on dequeue
	 */
	sock_skb_set_dropcount(sk, skb);

	__skb_queue_tail(list, skb);
	spin_unlock(&list->lock);

	अगर (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_पढ़ोy(sk);

	busylock_release(busy);
	वापस 0;

unअक्षरge_drop:
	atomic_sub(skb->truesize, &sk->sk_rmem_alloc);

drop:
	atomic_inc(&sk->sk_drops);
	busylock_release(busy);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__udp_enqueue_schedule_skb);

व्योम udp_deकाष्ठा_sock(काष्ठा sock *sk)
अणु
	/* reclaim completely the क्रमward allocated memory */
	काष्ठा udp_sock *up = udp_sk(sk);
	अचिन्हित पूर्णांक total = 0;
	काष्ठा sk_buff *skb;

	skb_queue_splice_tail_init(&sk->sk_receive_queue, &up->पढ़ोer_queue);
	जबतक ((skb = __skb_dequeue(&up->पढ़ोer_queue)) != शून्य) अणु
		total += skb->truesize;
		kमुक्त_skb(skb);
	पूर्ण
	udp_rmem_release(sk, total, 0, true);

	inet_sock_deकाष्ठा(sk);
पूर्ण
EXPORT_SYMBOL_GPL(udp_deकाष्ठा_sock);

पूर्णांक udp_init_sock(काष्ठा sock *sk)
अणु
	skb_queue_head_init(&udp_sk(sk)->पढ़ोer_queue);
	sk->sk_deकाष्ठा = udp_deकाष्ठा_sock;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(udp_init_sock);

व्योम skb_consume_udp(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक len)
अणु
	अगर (unlikely(READ_ONCE(sk->sk_peek_off) >= 0)) अणु
		bool slow = lock_sock_fast(sk);

		sk_peek_offset_bwd(sk, len);
		unlock_sock_fast(sk, slow);
	पूर्ण

	अगर (!skb_unref(skb))
		वापस;

	/* In the more common हालs we cleared the head states previously,
	 * see __udp_queue_rcv_skb().
	 */
	अगर (unlikely(udp_skb_has_head_state(skb)))
		skb_release_head_state(skb);
	__consume_stateless_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(skb_consume_udp);

अटल काष्ठा sk_buff *__first_packet_length(काष्ठा sock *sk,
					     काष्ठा sk_buff_head *rcvq,
					     पूर्णांक *total)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_peek(rcvq)) != शून्य) अणु
		अगर (udp_lib_checksum_complete(skb)) अणु
			__UDP_INC_STATS(sock_net(sk), UDP_MIB_CSUMERRORS,
					IS_UDPLITE(sk));
			__UDP_INC_STATS(sock_net(sk), UDP_MIB_INERRORS,
					IS_UDPLITE(sk));
			atomic_inc(&sk->sk_drops);
			__skb_unlink(skb, rcvq);
			*total += skb->truesize;
			kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
			udp_skb_csum_unnecessary_set(skb);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस skb;
पूर्ण

/**
 *	first_packet_length	- वापस length of first packet in receive queue
 *	@sk: socket
 *
 *	Drops all bad checksum frames, until a valid one is found.
 *	Returns the length of found skb, or -1 अगर none is found.
 */
अटल पूर्णांक first_packet_length(काष्ठा sock *sk)
अणु
	काष्ठा sk_buff_head *rcvq = &udp_sk(sk)->पढ़ोer_queue;
	काष्ठा sk_buff_head *sk_queue = &sk->sk_receive_queue;
	काष्ठा sk_buff *skb;
	पूर्णांक total = 0;
	पूर्णांक res;

	spin_lock_bh(&rcvq->lock);
	skb = __first_packet_length(sk, rcvq, &total);
	अगर (!skb && !skb_queue_empty_lockless(sk_queue)) अणु
		spin_lock(&sk_queue->lock);
		skb_queue_splice_tail_init(sk_queue, rcvq);
		spin_unlock(&sk_queue->lock);

		skb = __first_packet_length(sk, rcvq, &total);
	पूर्ण
	res = skb ? skb->len : -1;
	अगर (total)
		udp_rmem_release(sk, total, 1, false);
	spin_unlock_bh(&rcvq->lock);
	वापस res;
पूर्ण

/*
 *	IOCTL requests applicable to the UDP protocol
 */

पूर्णांक udp_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल SIOCOUTQ:
	अणु
		पूर्णांक amount = sk_wmem_alloc_get(sk);

		वापस put_user(amount, (पूर्णांक __user *)arg);
	पूर्ण

	हाल SIOCINQ:
	अणु
		पूर्णांक amount = max_t(पूर्णांक, 0, first_packet_length(sk));

		वापस put_user(amount, (पूर्णांक __user *)arg);
	पूर्ण

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(udp_ioctl);

काष्ठा sk_buff *__skb_recv_udp(काष्ठा sock *sk, अचिन्हित पूर्णांक flags,
			       पूर्णांक noblock, पूर्णांक *off, पूर्णांक *err)
अणु
	काष्ठा sk_buff_head *sk_queue = &sk->sk_receive_queue;
	काष्ठा sk_buff_head *queue;
	काष्ठा sk_buff *last;
	दीर्घ समयo;
	पूर्णांक error;

	queue = &udp_sk(sk)->पढ़ोer_queue;
	flags |= noblock ? MSG_DONTWAIT : 0;
	समयo = sock_rcvसमयo(sk, flags & MSG_DONTWAIT);
	करो अणु
		काष्ठा sk_buff *skb;

		error = sock_error(sk);
		अगर (error)
			अवरोध;

		error = -EAGAIN;
		करो अणु
			spin_lock_bh(&queue->lock);
			skb = __skb_try_recv_from_queue(sk, queue, flags, off,
							err, &last);
			अगर (skb) अणु
				अगर (!(flags & MSG_PEEK))
					udp_skb_deकाष्ठाor(sk, skb);
				spin_unlock_bh(&queue->lock);
				वापस skb;
			पूर्ण

			अगर (skb_queue_empty_lockless(sk_queue)) अणु
				spin_unlock_bh(&queue->lock);
				जाओ busy_check;
			पूर्ण

			/* refill the पढ़ोer queue and walk it again
			 * keep both queues locked to aव्योम re-acquiring
			 * the sk_receive_queue lock अगर fwd memory scheduling
			 * is needed.
			 */
			spin_lock(&sk_queue->lock);
			skb_queue_splice_tail_init(sk_queue, queue);

			skb = __skb_try_recv_from_queue(sk, queue, flags, off,
							err, &last);
			अगर (skb && !(flags & MSG_PEEK))
				udp_skb_dtor_locked(sk, skb);
			spin_unlock(&sk_queue->lock);
			spin_unlock_bh(&queue->lock);
			अगर (skb)
				वापस skb;

busy_check:
			अगर (!sk_can_busy_loop(sk))
				अवरोध;

			sk_busy_loop(sk, flags & MSG_DONTWAIT);
		पूर्ण जबतक (!skb_queue_empty_lockless(sk_queue));

		/* sk_queue is empty, पढ़ोer_queue may contain peeked packets */
	पूर्ण जबतक (समयo &&
		 !__skb_रुको_क्रम_more_packets(sk, &sk->sk_receive_queue,
					      &error, &समयo,
					      (काष्ठा sk_buff *)sk_queue));

	*err = error;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__skb_recv_udp);

पूर्णांक udp_पढ़ो_sock(काष्ठा sock *sk, पढ़ो_descriptor_t *desc,
		  sk_पढ़ो_actor_t recv_actor)
अणु
	पूर्णांक copied = 0;

	जबतक (1) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक err, used;

		skb = skb_recv_udp(sk, 0, 1, &err);
		अगर (!skb)
			वापस err;
		used = recv_actor(desc, skb, 0, skb->len);
		अगर (used <= 0) अणु
			अगर (!copied)
				copied = used;
			अवरोध;
		पूर्ण अन्यथा अगर (used <= skb->len) अणु
			copied += used;
		पूर्ण

		अगर (!desc->count)
			अवरोध;
	पूर्ण

	वापस copied;
पूर्ण
EXPORT_SYMBOL(udp_पढ़ो_sock);

/*
 * 	This should be easy, अगर there is something there we
 * 	वापस it, otherwise we block.
 */

पूर्णांक udp_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len, पूर्णांक noblock,
		पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_in *, sin, msg->msg_name);
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक ulen, copied;
	पूर्णांक off, err, peeking = flags & MSG_PEEK;
	पूर्णांक is_udplite = IS_UDPLITE(sk);
	bool checksum_valid = false;

	अगर (flags & MSG_ERRQUEUE)
		वापस ip_recv_error(sk, msg, len, addr_len);

try_again:
	off = sk_peek_offset(sk, flags);
	skb = __skb_recv_udp(sk, flags, noblock, &off, &err);
	अगर (!skb)
		वापस err;

	ulen = udp_skb_len(skb);
	copied = len;
	अगर (copied > ulen - off)
		copied = ulen - off;
	अन्यथा अगर (copied < ulen)
		msg->msg_flags |= MSG_TRUNC;

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
			UDP_INC_STATS(sock_net(sk),
				      UDP_MIB_INERRORS, is_udplite);
		पूर्ण
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	अगर (!peeking)
		UDP_INC_STATS(sock_net(sk),
			      UDP_MIB_INDATAGRAMS, is_udplite);

	sock_recv_ts_and_drops(msg, sk, skb);

	/* Copy the address. */
	अगर (sin) अणु
		sin->sin_family = AF_INET;
		sin->sin_port = udp_hdr(skb)->source;
		sin->sin_addr.s_addr = ip_hdr(skb)->saddr;
		स_रखो(sin->sin_zero, 0, माप(sin->sin_zero));
		*addr_len = माप(*sin);

		BPF_CGROUP_RUN_PROG_UDP4_RECVMSG_LOCK(sk,
						      (काष्ठा sockaddr *)sin);
	पूर्ण

	अगर (udp_sk(sk)->gro_enabled)
		udp_cmsg_recv(msg, sk, skb);

	अगर (inet->cmsg_flags)
		ip_cmsg_recv_offset(msg, sk, skb, माप(काष्ठा udphdr), off);

	err = copied;
	अगर (flags & MSG_TRUNC)
		err = ulen;

	skb_consume_udp(sk, skb, peeking ? -err : err);
	वापस err;

csum_copy_err:
	अगर (!__sk_queue_drop_skb(sk, &udp_sk(sk)->पढ़ोer_queue, skb, flags,
				 udp_skb_deकाष्ठाor)) अणु
		UDP_INC_STATS(sock_net(sk), UDP_MIB_CSUMERRORS, is_udplite);
		UDP_INC_STATS(sock_net(sk), UDP_MIB_INERRORS, is_udplite);
	पूर्ण
	kमुक्त_skb(skb);

	/* starting over क्रम a new packet, but check अगर we need to yield */
	cond_resched();
	msg->msg_flags &= ~MSG_TRUNC;
	जाओ try_again;
पूर्ण

पूर्णांक udp_pre_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	/* This check is replicated from __ip4_datagram_connect() and
	 * पूर्णांकended to prevent BPF program called below from accessing bytes
	 * that are out of the bound specअगरied by user in addr_len.
	 */
	अगर (addr_len < माप(काष्ठा sockaddr_in))
		वापस -EINVAL;

	वापस BPF_CGROUP_RUN_PROG_INET4_CONNECT_LOCK(sk, uaddr);
पूर्ण
EXPORT_SYMBOL(udp_pre_connect);

पूर्णांक __udp_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा inet_sock *inet = inet_sk(sk);
	/*
	 *	1003.1g - अवरोध association.
	 */

	sk->sk_state = TCP_CLOSE;
	inet->inet_daddr = 0;
	inet->inet_dport = 0;
	sock_rps_reset_rxhash(sk);
	sk->sk_bound_dev_अगर = 0;
	अगर (!(sk->sk_userlocks & SOCK_BINDADDR_LOCK)) अणु
		inet_reset_saddr(sk);
		अगर (sk->sk_prot->rehash &&
		    (sk->sk_userlocks & SOCK_BINDPORT_LOCK))
			sk->sk_prot->rehash(sk);
	पूर्ण

	अगर (!(sk->sk_userlocks & SOCK_BINDPORT_LOCK)) अणु
		sk->sk_prot->unhash(sk);
		inet->inet_sport = 0;
	पूर्ण
	sk_dst_reset(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__udp_disconnect);

पूर्णांक udp_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	lock_sock(sk);
	__udp_disconnect(sk, flags);
	release_sock(sk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(udp_disconnect);

व्योम udp_lib_unhash(काष्ठा sock *sk)
अणु
	अगर (sk_hashed(sk)) अणु
		काष्ठा udp_table *udptable = sk->sk_prot->h.udp_table;
		काष्ठा udp_hslot *hslot, *hslot2;

		hslot  = udp_hashslot(udptable, sock_net(sk),
				      udp_sk(sk)->udp_port_hash);
		hslot2 = udp_hashslot2(udptable, udp_sk(sk)->udp_portaddr_hash);

		spin_lock_bh(&hslot->lock);
		अगर (rcu_access_poपूर्णांकer(sk->sk_reuseport_cb))
			reuseport_detach_sock(sk);
		अगर (sk_del_node_init_rcu(sk)) अणु
			hslot->count--;
			inet_sk(sk)->inet_num = 0;
			sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);

			spin_lock(&hslot2->lock);
			hlist_del_init_rcu(&udp_sk(sk)->udp_portaddr_node);
			hslot2->count--;
			spin_unlock(&hslot2->lock);
		पूर्ण
		spin_unlock_bh(&hslot->lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(udp_lib_unhash);

/*
 * inet_rcv_saddr was changed, we must rehash secondary hash
 */
व्योम udp_lib_rehash(काष्ठा sock *sk, u16 newhash)
अणु
	अगर (sk_hashed(sk)) अणु
		काष्ठा udp_table *udptable = sk->sk_prot->h.udp_table;
		काष्ठा udp_hslot *hslot, *hslot2, *nhslot2;

		hslot2 = udp_hashslot2(udptable, udp_sk(sk)->udp_portaddr_hash);
		nhslot2 = udp_hashslot2(udptable, newhash);
		udp_sk(sk)->udp_portaddr_hash = newhash;

		अगर (hslot2 != nhslot2 ||
		    rcu_access_poपूर्णांकer(sk->sk_reuseport_cb)) अणु
			hslot = udp_hashslot(udptable, sock_net(sk),
					     udp_sk(sk)->udp_port_hash);
			/* we must lock primary chain too */
			spin_lock_bh(&hslot->lock);
			अगर (rcu_access_poपूर्णांकer(sk->sk_reuseport_cb))
				reuseport_detach_sock(sk);

			अगर (hslot2 != nhslot2) अणु
				spin_lock(&hslot2->lock);
				hlist_del_init_rcu(&udp_sk(sk)->udp_portaddr_node);
				hslot2->count--;
				spin_unlock(&hslot2->lock);

				spin_lock(&nhslot2->lock);
				hlist_add_head_rcu(&udp_sk(sk)->udp_portaddr_node,
							 &nhslot2->head);
				nhslot2->count++;
				spin_unlock(&nhslot2->lock);
			पूर्ण

			spin_unlock_bh(&hslot->lock);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(udp_lib_rehash);

व्योम udp_v4_rehash(काष्ठा sock *sk)
अणु
	u16 new_hash = ipv4_portaddr_hash(sock_net(sk),
					  inet_sk(sk)->inet_rcv_saddr,
					  inet_sk(sk)->inet_num);
	udp_lib_rehash(sk, new_hash);
पूर्ण

अटल पूर्णांक __udp_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;

	अगर (inet_sk(sk)->inet_daddr) अणु
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
			UDP_INC_STATS(sock_net(sk), UDP_MIB_RCVBUFERRORS,
					is_udplite);
		अन्यथा
			UDP_INC_STATS(sock_net(sk), UDP_MIB_MEMERRORS,
				      is_udplite);
		UDP_INC_STATS(sock_net(sk), UDP_MIB_INERRORS, is_udplite);
		kमुक्त_skb(skb);
		trace_udp_fail_queue_rcv_skb(rc, sk);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* वापसs:
 *  -1: error
 *   0: success
 *  >0: "udp encap" protocol resubmission
 *
 * Note that in the success and error हालs, the skb is assumed to
 * have either been requeued or मुक्तd.
 */
अटल पूर्णांक udp_queue_rcv_one_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा udp_sock *up = udp_sk(sk);
	पूर्णांक is_udplite = IS_UDPLITE(sk);

	/*
	 *	Charge it to the socket, dropping अगर the queue is full.
	 */
	अगर (!xfrm4_policy_check(sk, XFRM_POLICY_IN, skb))
		जाओ drop;
	nf_reset_ct(skb);

	अगर (अटल_branch_unlikely(&udp_encap_needed_key) && up->encap_type) अणु
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
	 * 	UDP-Lite specअगरic tests, ignored on UDP sockets
	 */
	अगर ((up->pcflag & UDPLITE_RECV_CC)  &&  UDP_SKB_CB(skb)->partial_cov) अणु

		/*
		 * MIB statistics other than incrementing the error count are
		 * disabled क्रम the following two types of errors: these depend
		 * on the application settings, not on the functioning of the
		 * protocol stack as such.
		 *
		 * RFC 3828 here recommends (sec 3.3): "There should also be a
		 * way ... to ... at least let the receiving application block
		 * delivery of packets with coverage values less than a value
		 * provided by the application."
		 */
		अगर (up->pcrlen == 0) अणु          /* full coverage was set  */
			net_dbg_ratelimited("UDPLite: partial coverage %d while full coverage %d requested\n",
					    UDP_SKB_CB(skb)->cscov, skb->len);
			जाओ drop;
		पूर्ण
		/* The next हाल involves violating the min. coverage requested
		 * by the receiver. This is subtle: अगर receiver wants x and x is
		 * greater than the buffersize/MTU then receiver will complain
		 * that it wants x जबतक sender emits packets of smaller size y.
		 * Thereक्रमe the above ...()->partial_cov statement is essential.
		 */
		अगर (UDP_SKB_CB(skb)->cscov  <  up->pcrlen) अणु
			net_dbg_ratelimited("UDPLite: coverage %d too small, need min %d\n",
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

	ipv4_pktinfo_prepare(sk, skb);
	वापस __udp_queue_rcv_skb(sk, skb);

csum_error:
	__UDP_INC_STATS(sock_net(sk), UDP_MIB_CSUMERRORS, is_udplite);
drop:
	__UDP_INC_STATS(sock_net(sk), UDP_MIB_INERRORS, is_udplite);
	atomic_inc(&sk->sk_drops);
	kमुक्त_skb(skb);
	वापस -1;
पूर्ण

अटल पूर्णांक udp_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *next, *segs;
	पूर्णांक ret;

	अगर (likely(!udp_unexpected_gso(sk, skb)))
		वापस udp_queue_rcv_one_skb(sk, skb);

	BUILD_BUG_ON(माप(काष्ठा udp_skb_cb) > SKB_GSO_CB_OFFSET);
	__skb_push(skb, -skb_mac_offset(skb));
	segs = udp_rcv_segment(sk, skb, true);
	skb_list_walk_safe(segs, skb, next) अणु
		__skb_pull(skb, skb_transport_offset(skb));

		udp_post_segment_fix_csum(skb);
		ret = udp_queue_rcv_one_skb(sk, skb);
		अगर (ret > 0)
			ip_protocol_deliver_rcu(dev_net(skb->dev), skb, ret);
	पूर्ण
	वापस 0;
पूर्ण

/* For TCP sockets, sk_rx_dst is रक्षित by socket lock
 * For UDP, we use xchg() to guard against concurrent changes.
 */
bool udp_sk_rx_dst_set(काष्ठा sock *sk, काष्ठा dst_entry *dst)
अणु
	काष्ठा dst_entry *old;

	अगर (dst_hold_safe(dst)) अणु
		old = xchg(&sk->sk_rx_dst, dst);
		dst_release(old);
		वापस old != dst;
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL(udp_sk_rx_dst_set);

/*
 *	Multicasts and broadcasts go to each listener.
 *
 *	Note: called only from the BH handler context.
 */
अटल पूर्णांक __udp4_lib_mcast_deliver(काष्ठा net *net, काष्ठा sk_buff *skb,
				    काष्ठा udphdr  *uh,
				    __be32 saddr, __be32 daddr,
				    काष्ठा udp_table *udptable,
				    पूर्णांक proto)
अणु
	काष्ठा sock *sk, *first = शून्य;
	अचिन्हित लघु hnum = ntohs(uh->dest);
	काष्ठा udp_hslot *hslot = udp_hashslot(udptable, net, hnum);
	अचिन्हित पूर्णांक hash2 = 0, hash2_any = 0, use_hash2 = (hslot->count > 10);
	अचिन्हित पूर्णांक offset = दुरत्व(typeof(*sk), sk_node);
	पूर्णांक dअगर = skb->dev->अगरindex;
	पूर्णांक sdअगर = inet_sdअगर(skb);
	काष्ठा hlist_node *node;
	काष्ठा sk_buff *nskb;

	अगर (use_hash2) अणु
		hash2_any = ipv4_portaddr_hash(net, htonl(INADDR_ANY), hnum) &
			    udptable->mask;
		hash2 = ipv4_portaddr_hash(net, daddr, hnum) & udptable->mask;
start_lookup:
		hslot = &udptable->hash2[hash2];
		offset = दुरत्व(typeof(*sk), __sk_common.skc_portaddr_node);
	पूर्ण

	sk_क्रम_each_entry_offset_rcu(sk, node, &hslot->head, offset) अणु
		अगर (!__udp_is_mcast_sock(net, sk, uh->dest, daddr,
					 uh->source, saddr, dअगर, sdअगर, hnum))
			जारी;

		अगर (!first) अणु
			first = sk;
			जारी;
		पूर्ण
		nskb = skb_clone(skb, GFP_ATOMIC);

		अगर (unlikely(!nskb)) अणु
			atomic_inc(&sk->sk_drops);
			__UDP_INC_STATS(net, UDP_MIB_RCVBUFERRORS,
					IS_UDPLITE(sk));
			__UDP_INC_STATS(net, UDP_MIB_INERRORS,
					IS_UDPLITE(sk));
			जारी;
		पूर्ण
		अगर (udp_queue_rcv_skb(sk, nskb) > 0)
			consume_skb(nskb);
	पूर्ण

	/* Also lookup *:port अगर we are using hash2 and haven't करोne so yet. */
	अगर (use_hash2 && hash2 != hash2_any) अणु
		hash2 = hash2_any;
		जाओ start_lookup;
	पूर्ण

	अगर (first) अणु
		अगर (udp_queue_rcv_skb(first, skb) > 0)
			consume_skb(skb);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
		__UDP_INC_STATS(net, UDP_MIB_IGNOREDMULTI,
				proto == IPPROTO_UDPLITE);
	पूर्ण
	वापस 0;
पूर्ण

/* Initialize UDP checksum. If निकासed with zero value (success),
 * CHECKSUM_UNNECESSARY means, that no more checks are required.
 * Otherwise, csum completion requires checksumming packet body,
 * including udp header and folding it to skb->csum.
 */
अटल अंतरभूत पूर्णांक udp4_csum_init(काष्ठा sk_buff *skb, काष्ठा udphdr *uh,
				 पूर्णांक proto)
अणु
	पूर्णांक err;

	UDP_SKB_CB(skb)->partial_cov = 0;
	UDP_SKB_CB(skb)->cscov = skb->len;

	अगर (proto == IPPROTO_UDPLITE) अणु
		err = udplite_checksum_init(skb, uh);
		अगर (err)
			वापस err;

		अगर (UDP_SKB_CB(skb)->partial_cov) अणु
			skb->csum = inet_compute_pseuकरो(skb, proto);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Note, we are only पूर्णांकerested in != 0 or == 0, thus the
	 * क्रमce to पूर्णांक.
	 */
	err = (__क्रमce पूर्णांक)skb_checksum_init_zero_check(skb, proto, uh->check,
							inet_compute_pseuकरो);
	अगर (err)
		वापस err;

	अगर (skb->ip_summed == CHECKSUM_COMPLETE && !skb->csum_valid) अणु
		/* If SW calculated the value, we know it's bad */
		अगर (skb->csum_complete_sw)
			वापस 1;

		/* HW says the value is bad. Let's validate that.
		 * skb->csum is no दीर्घer the full packet checksum,
		 * so करोn't treat it as such.
		 */
		skb_checksum_complete_unset(skb);
	पूर्ण

	वापस 0;
पूर्ण

/* wrapper क्रम udp_queue_rcv_skb tacking care of csum conversion and
 * वापस code conversion क्रम ip layer consumption
 */
अटल पूर्णांक udp_unicast_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			       काष्ठा udphdr *uh)
अणु
	पूर्णांक ret;

	अगर (inet_get_convert_csum(sk) && uh->check && !IS_UDPLITE(sk))
		skb_checksum_try_convert(skb, IPPROTO_UDP, inet_compute_pseuकरो);

	ret = udp_queue_rcv_skb(sk, skb);

	/* a वापस value > 0 means to resubmit the input, but
	 * it wants the वापस to be -protocol, or 0
	 */
	अगर (ret > 0)
		वापस -ret;
	वापस 0;
पूर्ण

/*
 *	All we need to करो is get the socket, and then करो a checksum.
 */

पूर्णांक __udp4_lib_rcv(काष्ठा sk_buff *skb, काष्ठा udp_table *udptable,
		   पूर्णांक proto)
अणु
	काष्ठा sock *sk;
	काष्ठा udphdr *uh;
	अचिन्हित लघु ulen;
	काष्ठा rtable *rt = skb_rtable(skb);
	__be32 saddr, daddr;
	काष्ठा net *net = dev_net(skb->dev);
	bool refcounted;

	/*
	 *  Validate the packet.
	 */
	अगर (!pskb_may_pull(skb, माप(काष्ठा udphdr)))
		जाओ drop;		/* No space क्रम header. */

	uh   = udp_hdr(skb);
	ulen = ntohs(uh->len);
	saddr = ip_hdr(skb)->saddr;
	daddr = ip_hdr(skb)->daddr;

	अगर (ulen > skb->len)
		जाओ लघु_packet;

	अगर (proto == IPPROTO_UDP) अणु
		/* UDP validates ulen. */
		अगर (ulen < माप(*uh) || pskb_trim_rcsum(skb, ulen))
			जाओ लघु_packet;
		uh = udp_hdr(skb);
	पूर्ण

	अगर (udp4_csum_init(skb, uh, proto))
		जाओ csum_error;

	sk = skb_steal_sock(skb, &refcounted);
	अगर (sk) अणु
		काष्ठा dst_entry *dst = skb_dst(skb);
		पूर्णांक ret;

		अगर (unlikely(sk->sk_rx_dst != dst))
			udp_sk_rx_dst_set(sk, dst);

		ret = udp_unicast_rcv_skb(sk, skb, uh);
		अगर (refcounted)
			sock_put(sk);
		वापस ret;
	पूर्ण

	अगर (rt->rt_flags & (RTCF_BROADCAST|RTCF_MULTICAST))
		वापस __udp4_lib_mcast_deliver(net, skb, uh,
						saddr, daddr, udptable, proto);

	sk = __udp4_lib_lookup_skb(skb, uh->source, uh->dest, udptable);
	अगर (sk)
		वापस udp_unicast_rcv_skb(sk, skb, uh);

	अगर (!xfrm4_policy_check(शून्य, XFRM_POLICY_IN, skb))
		जाओ drop;
	nf_reset_ct(skb);

	/* No socket. Drop packet silently, अगर checksum is wrong */
	अगर (udp_lib_checksum_complete(skb))
		जाओ csum_error;

	__UDP_INC_STATS(net, UDP_MIB_NOPORTS, proto == IPPROTO_UDPLITE);
	icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);

	/*
	 * Hmm.  We got an UDP packet to a port to which we
	 * करोn't wanna listen.  Ignore it.
	 */
	kमुक्त_skb(skb);
	वापस 0;

लघु_packet:
	net_dbg_ratelimited("UDP%s: short packet: From %pI4:%u %d/%d to %pI4:%u\n",
			    proto == IPPROTO_UDPLITE ? "Lite" : "",
			    &saddr, ntohs(uh->source),
			    ulen, skb->len,
			    &daddr, ntohs(uh->dest));
	जाओ drop;

csum_error:
	/*
	 * RFC1122: OK.  Discards the bad packet silently (as far as
	 * the network is concerned, anyway) as per 4.1.3.4 (MUST).
	 */
	net_dbg_ratelimited("UDP%s: bad checksum. From %pI4:%u to %pI4:%u ulen %d\n",
			    proto == IPPROTO_UDPLITE ? "Lite" : "",
			    &saddr, ntohs(uh->source), &daddr, ntohs(uh->dest),
			    ulen);
	__UDP_INC_STATS(net, UDP_MIB_CSUMERRORS, proto == IPPROTO_UDPLITE);
drop:
	__UDP_INC_STATS(net, UDP_MIB_INERRORS, proto == IPPROTO_UDPLITE);
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/* We can only early demux multicast अगर there is a single matching socket.
 * If more than one socket found वापसs शून्य
 */
अटल काष्ठा sock *__udp4_lib_mcast_demux_lookup(काष्ठा net *net,
						  __be16 loc_port, __be32 loc_addr,
						  __be16 rmt_port, __be32 rmt_addr,
						  पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
	काष्ठा sock *sk, *result;
	अचिन्हित लघु hnum = ntohs(loc_port);
	अचिन्हित पूर्णांक slot = udp_hashfn(net, hnum, udp_table.mask);
	काष्ठा udp_hslot *hslot = &udp_table.hash[slot];

	/* Do not bother scanning a too big list */
	अगर (hslot->count > 10)
		वापस शून्य;

	result = शून्य;
	sk_क्रम_each_rcu(sk, &hslot->head) अणु
		अगर (__udp_is_mcast_sock(net, sk, loc_port, loc_addr,
					rmt_port, rmt_addr, dअगर, sdअगर, hnum)) अणु
			अगर (result)
				वापस शून्य;
			result = sk;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

/* For unicast we should only early demux connected sockets or we can
 * अवरोध क्रमwarding setups.  The chains here can be दीर्घ so only check
 * अगर the first socket is an exact match and अगर not move on.
 */
अटल काष्ठा sock *__udp4_lib_demux_lookup(काष्ठा net *net,
					    __be16 loc_port, __be32 loc_addr,
					    __be16 rmt_port, __be32 rmt_addr,
					    पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
	अचिन्हित लघु hnum = ntohs(loc_port);
	अचिन्हित पूर्णांक hash2 = ipv4_portaddr_hash(net, loc_addr, hnum);
	अचिन्हित पूर्णांक slot2 = hash2 & udp_table.mask;
	काष्ठा udp_hslot *hslot2 = &udp_table.hash2[slot2];
	INET_ADDR_COOKIE(acookie, rmt_addr, loc_addr);
	स्थिर __portpair ports = INET_COMBINED_PORTS(rmt_port, hnum);
	काष्ठा sock *sk;

	udp_portaddr_क्रम_each_entry_rcu(sk, &hslot2->head) अणु
		अगर (INET_MATCH(sk, net, acookie, rmt_addr,
			       loc_addr, ports, dअगर, sdअगर))
			वापस sk;
		/* Only check first socket in chain */
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक udp_v4_early_demux(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा in_device *in_dev = शून्य;
	स्थिर काष्ठा iphdr *iph;
	स्थिर काष्ठा udphdr *uh;
	काष्ठा sock *sk = शून्य;
	काष्ठा dst_entry *dst;
	पूर्णांक dअगर = skb->dev->अगरindex;
	पूर्णांक sdअगर = inet_sdअगर(skb);
	पूर्णांक ours;

	/* validate the packet */
	अगर (!pskb_may_pull(skb, skb_transport_offset(skb) + माप(काष्ठा udphdr)))
		वापस 0;

	iph = ip_hdr(skb);
	uh = udp_hdr(skb);

	अगर (skb->pkt_type == PACKET_MULTICAST) अणु
		in_dev = __in_dev_get_rcu(skb->dev);

		अगर (!in_dev)
			वापस 0;

		ours = ip_check_mc_rcu(in_dev, iph->daddr, iph->saddr,
				       iph->protocol);
		अगर (!ours)
			वापस 0;

		sk = __udp4_lib_mcast_demux_lookup(net, uh->dest, iph->daddr,
						   uh->source, iph->saddr,
						   dअगर, sdअगर);
	पूर्ण अन्यथा अगर (skb->pkt_type == PACKET_HOST) अणु
		sk = __udp4_lib_demux_lookup(net, uh->dest, iph->daddr,
					     uh->source, iph->saddr, dअगर, sdअगर);
	पूर्ण

	अगर (!sk || !refcount_inc_not_zero(&sk->sk_refcnt))
		वापस 0;

	skb->sk = sk;
	skb->deकाष्ठाor = sock_eमुक्त;
	dst = READ_ONCE(sk->sk_rx_dst);

	अगर (dst)
		dst = dst_check(dst, 0);
	अगर (dst) अणु
		u32 itag = 0;

		/* set noref क्रम now.
		 * any place which wants to hold dst has to call
		 * dst_hold_safe()
		 */
		skb_dst_set_noref(skb, dst);

		/* क्रम unconnected multicast sockets we need to validate
		 * the source on each packet
		 */
		अगर (!inet_sk(sk)->inet_daddr && in_dev)
			वापस ip_mc_validate_source(skb, iph->daddr,
						     iph->saddr,
						     iph->tos & IPTOS_RT_MASK,
						     skb->dev, in_dev, &itag);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक udp_rcv(काष्ठा sk_buff *skb)
अणु
	वापस __udp4_lib_rcv(skb, &udp_table, IPPROTO_UDP);
पूर्ण

व्योम udp_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा udp_sock *up = udp_sk(sk);
	bool slow = lock_sock_fast(sk);

	/* protects from races with udp_पात() */
	sock_set_flag(sk, SOCK_DEAD);
	udp_flush_pending_frames(sk);
	unlock_sock_fast(sk, slow);
	अगर (अटल_branch_unlikely(&udp_encap_needed_key)) अणु
		अगर (up->encap_type) अणु
			व्योम (*encap_destroy)(काष्ठा sock *sk);
			encap_destroy = READ_ONCE(up->encap_destroy);
			अगर (encap_destroy)
				encap_destroy(sk);
		पूर्ण
		अगर (up->encap_enabled)
			अटल_branch_dec(&udp_encap_needed_key);
	पूर्ण
पूर्ण

/*
 *	Socket option code क्रम UDP
 */
पूर्णांक udp_lib_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		       sockptr_t optval, अचिन्हित पूर्णांक optlen,
		       पूर्णांक (*push_pending_frames)(काष्ठा sock *))
अणु
	काष्ठा udp_sock *up = udp_sk(sk);
	पूर्णांक val, valbool;
	पूर्णांक err = 0;
	पूर्णांक is_udplite = IS_UDPLITE(sk);

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&val, optval, माप(val)))
		वापस -EFAULT;

	valbool = val ? 1 : 0;

	चयन (optname) अणु
	हाल UDP_CORK:
		अगर (val != 0) अणु
			up->corkflag = 1;
		पूर्ण अन्यथा अणु
			up->corkflag = 0;
			lock_sock(sk);
			push_pending_frames(sk);
			release_sock(sk);
		पूर्ण
		अवरोध;

	हाल UDP_ENCAP:
		चयन (val) अणु
		हाल 0:
#अगर_घोषित CONFIG_XFRM
		हाल UDP_ENCAP_ESPINUDP:
		हाल UDP_ENCAP_ESPINUDP_NON_IKE:
#अगर IS_ENABLED(CONFIG_IPV6)
			अगर (sk->sk_family == AF_INET6)
				up->encap_rcv = ipv6_stub->xfrm6_udp_encap_rcv;
			अन्यथा
#पूर्ण_अगर
				up->encap_rcv = xfrm4_udp_encap_rcv;
#पूर्ण_अगर
			fallthrough;
		हाल UDP_ENCAP_L2TPINUDP:
			up->encap_type = val;
			lock_sock(sk);
			udp_tunnel_encap_enable(sk->sk_socket);
			release_sock(sk);
			अवरोध;
		शेष:
			err = -ENOPROTOOPT;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल UDP_NO_CHECK6_TX:
		up->no_check6_tx = valbool;
		अवरोध;

	हाल UDP_NO_CHECK6_RX:
		up->no_check6_rx = valbool;
		अवरोध;

	हाल UDP_SEGMENT:
		अगर (val < 0 || val > अच_लघु_उच्च)
			वापस -EINVAL;
		up->gso_size = val;
		अवरोध;

	हाल UDP_GRO:
		lock_sock(sk);

		/* when enabling GRO, accept the related GSO packet type */
		अगर (valbool)
			udp_tunnel_encap_enable(sk->sk_socket);
		up->gro_enabled = valbool;
		up->accept_udp_l4 = valbool;
		release_sock(sk);
		अवरोध;

	/*
	 * 	UDP-Lite's partial checksum coverage (RFC 3828).
	 */
	/* The sender sets actual checksum coverage length via this option.
	 * The हाल coverage > packet length is handled by send module. */
	हाल UDPLITE_SEND_CSCOV:
		अगर (!is_udplite)         /* Disable the option on UDP sockets */
			वापस -ENOPROTOOPT;
		अगर (val != 0 && val < 8) /* Illegal coverage: use शेष (8) */
			val = 8;
		अन्यथा अगर (val > अच_लघु_उच्च)
			val = अच_लघु_उच्च;
		up->pcslen = val;
		up->pcflag |= UDPLITE_SEND_CC;
		अवरोध;

	/* The receiver specअगरies a minimum checksum coverage value. To make
	 * sense, this should be set to at least 8 (as करोne below). If zero is
	 * used, this again means full checksum coverage.                     */
	हाल UDPLITE_RECV_CSCOV:
		अगर (!is_udplite)         /* Disable the option on UDP sockets */
			वापस -ENOPROTOOPT;
		अगर (val != 0 && val < 8) /* Aव्योम silly minimal values.       */
			val = 8;
		अन्यथा अगर (val > अच_लघु_उच्च)
			val = अच_लघु_उच्च;
		up->pcrlen = val;
		up->pcflag |= UDPLITE_RECV_CC;
		अवरोध;

	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(udp_lib_setsockopt);

पूर्णांक udp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		   अचिन्हित पूर्णांक optlen)
अणु
	अगर (level == SOL_UDP  ||  level == SOL_UDPLITE)
		वापस udp_lib_setsockopt(sk, level, optname,
					  optval, optlen,
					  udp_push_pending_frames);
	वापस ip_setsockopt(sk, level, optname, optval, optlen);
पूर्ण

पूर्णांक udp_lib_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		       अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा udp_sock *up = udp_sk(sk);
	पूर्णांक val, len;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	len = min_t(अचिन्हित पूर्णांक, len, माप(पूर्णांक));

	अगर (len < 0)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल UDP_CORK:
		val = up->corkflag;
		अवरोध;

	हाल UDP_ENCAP:
		val = up->encap_type;
		अवरोध;

	हाल UDP_NO_CHECK6_TX:
		val = up->no_check6_tx;
		अवरोध;

	हाल UDP_NO_CHECK6_RX:
		val = up->no_check6_rx;
		अवरोध;

	हाल UDP_SEGMENT:
		val = up->gso_size;
		अवरोध;

	हाल UDP_GRO:
		val = up->gro_enabled;
		अवरोध;

	/* The following two cannot be changed on UDP sockets, the वापस is
	 * always 0 (which corresponds to the full checksum coverage of UDP). */
	हाल UDPLITE_SEND_CSCOV:
		val = up->pcslen;
		अवरोध;

	हाल UDPLITE_RECV_CSCOV:
		val = up->pcrlen;
		अवरोध;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(udp_lib_माला_लोockopt);

पूर्णांक udp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		   अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	अगर (level == SOL_UDP  ||  level == SOL_UDPLITE)
		वापस udp_lib_माला_लोockopt(sk, level, optname, optval, optlen);
	वापस ip_माला_लोockopt(sk, level, optname, optval, optlen);
पूर्ण

/**
 * 	udp_poll - रुको क्रम a UDP event.
 *	@file: - file काष्ठा
 *	@sock: - socket
 *	@रुको: - poll table
 *
 *	This is same as datagram poll, except क्रम the special हाल of
 *	blocking sockets. If application is using a blocking fd
 *	and a packet with checksum error is in the queue;
 *	then it could get वापस from select indicating data available
 *	but then block when पढ़ोing it. Add special हाल code
 *	to work around these arguably broken applications.
 */
__poll_t udp_poll(काष्ठा file *file, काष्ठा socket *sock, poll_table *रुको)
अणु
	__poll_t mask = datagram_poll(file, sock, रुको);
	काष्ठा sock *sk = sock->sk;

	अगर (!skb_queue_empty_lockless(&udp_sk(sk)->पढ़ोer_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	/* Check क्रम false positives due to checksum errors */
	अगर ((mask & EPOLLRDNORM) && !(file->f_flags & O_NONBLOCK) &&
	    !(sk->sk_shutकरोwn & RCV_SHUTDOWN) && first_packet_length(sk) == -1)
		mask &= ~(EPOLLIN | EPOLLRDNORM);

	वापस mask;

पूर्ण
EXPORT_SYMBOL(udp_poll);

पूर्णांक udp_पात(काष्ठा sock *sk, पूर्णांक err)
अणु
	lock_sock(sk);

	/* udpअणुv6पूर्ण_destroy_sock() sets it under the sk lock, aव्योम racing
	 * with बंद()
	 */
	अगर (sock_flag(sk, SOCK_DEAD))
		जाओ out;

	sk->sk_err = err;
	sk->sk_error_report(sk);
	__udp_disconnect(sk, 0);

out:
	release_sock(sk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(udp_पात);

काष्ठा proto udp_prot = अणु
	.name			= "UDP",
	.owner			= THIS_MODULE,
	.बंद			= udp_lib_बंद,
	.pre_connect		= udp_pre_connect,
	.connect		= ip4_datagram_connect,
	.disconnect		= udp_disconnect,
	.ioctl			= udp_ioctl,
	.init			= udp_init_sock,
	.destroy		= udp_destroy_sock,
	.setsockopt		= udp_setsockopt,
	.माला_लोockopt		= udp_माला_लोockopt,
	.sendmsg		= udp_sendmsg,
	.recvmsg		= udp_recvmsg,
	.sendpage		= udp_sendpage,
	.release_cb		= ip4_datagram_release_cb,
	.hash			= udp_lib_hash,
	.unhash			= udp_lib_unhash,
	.rehash			= udp_v4_rehash,
	.get_port		= udp_v4_get_port,
#अगर_घोषित CONFIG_BPF_SYSCALL
	.psock_update_sk_prot	= udp_bpf_update_proto,
#पूर्ण_अगर
	.memory_allocated	= &udp_memory_allocated,
	.sysctl_mem		= sysctl_udp_mem,
	.sysctl_wmem_offset	= दुरत्व(काष्ठा net, ipv4.sysctl_udp_wmem_min),
	.sysctl_rmem_offset	= दुरत्व(काष्ठा net, ipv4.sysctl_udp_rmem_min),
	.obj_size		= माप(काष्ठा udp_sock),
	.h.udp_table		= &udp_table,
	.diag_destroy		= udp_पात,
पूर्ण;
EXPORT_SYMBOL(udp_prot);

/* ------------------------------------------------------------------------ */
#अगर_घोषित CONFIG_PROC_FS

अटल काष्ठा sock *udp_get_first(काष्ठा seq_file *seq, पूर्णांक start)
अणु
	काष्ठा sock *sk;
	काष्ठा udp_seq_afinfo *afinfo;
	काष्ठा udp_iter_state *state = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);

	अगर (state->bpf_seq_afinfo)
		afinfo = state->bpf_seq_afinfo;
	अन्यथा
		afinfo = PDE_DATA(file_inode(seq->file));

	क्रम (state->bucket = start; state->bucket <= afinfo->udp_table->mask;
	     ++state->bucket) अणु
		काष्ठा udp_hslot *hslot = &afinfo->udp_table->hash[state->bucket];

		अगर (hlist_empty(&hslot->head))
			जारी;

		spin_lock_bh(&hslot->lock);
		sk_क्रम_each(sk, &hslot->head) अणु
			अगर (!net_eq(sock_net(sk), net))
				जारी;
			अगर (afinfo->family == AF_UNSPEC ||
			    sk->sk_family == afinfo->family)
				जाओ found;
		पूर्ण
		spin_unlock_bh(&hslot->lock);
	पूर्ण
	sk = शून्य;
found:
	वापस sk;
पूर्ण

अटल काष्ठा sock *udp_get_next(काष्ठा seq_file *seq, काष्ठा sock *sk)
अणु
	काष्ठा udp_seq_afinfo *afinfo;
	काष्ठा udp_iter_state *state = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);

	अगर (state->bpf_seq_afinfo)
		afinfo = state->bpf_seq_afinfo;
	अन्यथा
		afinfo = PDE_DATA(file_inode(seq->file));

	करो अणु
		sk = sk_next(sk);
	पूर्ण जबतक (sk && (!net_eq(sock_net(sk), net) ||
			(afinfo->family != AF_UNSPEC &&
			 sk->sk_family != afinfo->family)));

	अगर (!sk) अणु
		अगर (state->bucket <= afinfo->udp_table->mask)
			spin_unlock_bh(&afinfo->udp_table->hash[state->bucket].lock);
		वापस udp_get_first(seq, state->bucket + 1);
	पूर्ण
	वापस sk;
पूर्ण

अटल काष्ठा sock *udp_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा sock *sk = udp_get_first(seq, 0);

	अगर (sk)
		जबतक (pos && (sk = udp_get_next(seq, sk)) != शून्य)
			--pos;
	वापस pos ? शून्य : sk;
पूर्ण

व्योम *udp_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा udp_iter_state *state = seq->निजी;
	state->bucket = MAX_UDP_PORTS;

	वापस *pos ? udp_get_idx(seq, *pos-1) : SEQ_START_TOKEN;
पूर्ण
EXPORT_SYMBOL(udp_seq_start);

व्योम *udp_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा sock *sk;

	अगर (v == SEQ_START_TOKEN)
		sk = udp_get_idx(seq, 0);
	अन्यथा
		sk = udp_get_next(seq, v);

	++*pos;
	वापस sk;
पूर्ण
EXPORT_SYMBOL(udp_seq_next);

व्योम udp_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा udp_seq_afinfo *afinfo;
	काष्ठा udp_iter_state *state = seq->निजी;

	अगर (state->bpf_seq_afinfo)
		afinfo = state->bpf_seq_afinfo;
	अन्यथा
		afinfo = PDE_DATA(file_inode(seq->file));

	अगर (state->bucket <= afinfo->udp_table->mask)
		spin_unlock_bh(&afinfo->udp_table->hash[state->bucket].lock);
पूर्ण
EXPORT_SYMBOL(udp_seq_stop);

/* ------------------------------------------------------------------------ */
अटल व्योम udp4_क्रमmat_sock(काष्ठा sock *sp, काष्ठा seq_file *f,
		पूर्णांक bucket)
अणु
	काष्ठा inet_sock *inet = inet_sk(sp);
	__be32 dest = inet->inet_daddr;
	__be32 src  = inet->inet_rcv_saddr;
	__u16 destp	  = ntohs(inet->inet_dport);
	__u16 srcp	  = ntohs(inet->inet_sport);

	seq_म_लिखो(f, "%5d: %08X:%04X %08X:%04X"
		" %02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d %pK %u",
		bucket, src, srcp, dest, destp, sp->sk_state,
		sk_wmem_alloc_get(sp),
		udp_rqueue_get(sp),
		0, 0L, 0,
		from_kuid_munged(seq_user_ns(f), sock_i_uid(sp)),
		0, sock_i_ino(sp),
		refcount_पढ़ो(&sp->sk_refcnt), sp,
		atomic_पढ़ो(&sp->sk_drops));
पूर्ण

पूर्णांक udp4_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	seq_setwidth(seq, 127);
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "  sl  local_address rem_address   st tx_queue "
			   "rx_queue tr tm->when retrnsmt   uid  timeout "
			   "inode ref pointer drops");
	अन्यथा अणु
		काष्ठा udp_iter_state *state = seq->निजी;

		udp4_क्रमmat_sock(v, seq, state->bucket);
	पूर्ण
	seq_pad(seq, '\n');
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
काष्ठा bpf_iter__udp अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा udp_sock *, udp_sk);
	uid_t uid __aligned(8);
	पूर्णांक bucket __aligned(8);
पूर्ण;

अटल पूर्णांक udp_prog_seq_show(काष्ठा bpf_prog *prog, काष्ठा bpf_iter_meta *meta,
			     काष्ठा udp_sock *udp_sk, uid_t uid, पूर्णांक bucket)
अणु
	काष्ठा bpf_iter__udp ctx;

	meta->seq_num--;  /* skip SEQ_START_TOKEN */
	ctx.meta = meta;
	ctx.udp_sk = udp_sk;
	ctx.uid = uid;
	ctx.bucket = bucket;
	वापस bpf_iter_run_prog(prog, &ctx);
पूर्ण

अटल पूर्णांक bpf_iter_udp_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा udp_iter_state *state = seq->निजी;
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;
	काष्ठा sock *sk = v;
	uid_t uid;

	अगर (v == SEQ_START_TOKEN)
		वापस 0;

	uid = from_kuid_munged(seq_user_ns(seq), sock_i_uid(sk));
	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, false);
	वापस udp_prog_seq_show(prog, &meta, v, uid, state->bucket);
पूर्ण

अटल व्योम bpf_iter_udp_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;

	अगर (!v) अणु
		meta.seq = seq;
		prog = bpf_iter_get_info(&meta, true);
		अगर (prog)
			(व्योम)udp_prog_seq_show(prog, &meta, v, 0, 0);
	पूर्ण

	udp_seq_stop(seq, v);
पूर्ण

अटल स्थिर काष्ठा seq_operations bpf_iter_udp_seq_ops = अणु
	.start		= udp_seq_start,
	.next		= udp_seq_next,
	.stop		= bpf_iter_udp_seq_stop,
	.show		= bpf_iter_udp_seq_show,
पूर्ण;
#पूर्ण_अगर

स्थिर काष्ठा seq_operations udp_seq_ops = अणु
	.start		= udp_seq_start,
	.next		= udp_seq_next,
	.stop		= udp_seq_stop,
	.show		= udp4_seq_show,
पूर्ण;
EXPORT_SYMBOL(udp_seq_ops);

अटल काष्ठा udp_seq_afinfo udp4_seq_afinfo = अणु
	.family		= AF_INET,
	.udp_table	= &udp_table,
पूर्ण;

अटल पूर्णांक __net_init udp4_proc_init_net(काष्ठा net *net)
अणु
	अगर (!proc_create_net_data("udp", 0444, net->proc_net, &udp_seq_ops,
			माप(काष्ठा udp_iter_state), &udp4_seq_afinfo))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास udp4_proc_निकास_net(काष्ठा net *net)
अणु
	हटाओ_proc_entry("udp", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations udp4_net_ops = अणु
	.init = udp4_proc_init_net,
	.निकास = udp4_proc_निकास_net,
पूर्ण;

पूर्णांक __init udp4_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&udp4_net_ops);
पूर्ण

व्योम udp4_proc_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&udp4_net_ops);
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_FS */

अटल __initdata अचिन्हित दीर्घ uhash_entries;
अटल पूर्णांक __init set_uhash_entries(अक्षर *str)
अणु
	sमाप_प्रकार ret;

	अगर (!str)
		वापस 0;

	ret = kम_से_अदीर्घ(str, 0, &uhash_entries);
	अगर (ret)
		वापस 0;

	अगर (uhash_entries && uhash_entries < UDP_HTABLE_SIZE_MIN)
		uhash_entries = UDP_HTABLE_SIZE_MIN;
	वापस 1;
पूर्ण
__setup("uhash_entries=", set_uhash_entries);

व्योम __init udp_table_init(काष्ठा udp_table *table, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	table->hash = alloc_large_प्रणाली_hash(name,
					      2 * माप(काष्ठा udp_hslot),
					      uhash_entries,
					      21, /* one slot per 2 MB */
					      0,
					      &table->log,
					      &table->mask,
					      UDP_HTABLE_SIZE_MIN,
					      64 * 1024);

	table->hash2 = table->hash + (table->mask + 1);
	क्रम (i = 0; i <= table->mask; i++) अणु
		INIT_HLIST_HEAD(&table->hash[i].head);
		table->hash[i].count = 0;
		spin_lock_init(&table->hash[i].lock);
	पूर्ण
	क्रम (i = 0; i <= table->mask; i++) अणु
		INIT_HLIST_HEAD(&table->hash2[i].head);
		table->hash2[i].count = 0;
		spin_lock_init(&table->hash2[i].lock);
	पूर्ण
पूर्ण

u32 udp_flow_hashrnd(व्योम)
अणु
	अटल u32 hashrnd __पढ़ो_mostly;

	net_get_अक्रमom_once(&hashrnd, माप(hashrnd));

	वापस hashrnd;
पूर्ण
EXPORT_SYMBOL(udp_flow_hashrnd);

अटल व्योम __udp_sysctl_init(काष्ठा net *net)
अणु
	net->ipv4.sysctl_udp_rmem_min = SK_MEM_QUANTUM;
	net->ipv4.sysctl_udp_wmem_min = SK_MEM_QUANTUM;

#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
	net->ipv4.sysctl_udp_l3mdev_accept = 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __net_init udp_sysctl_init(काष्ठा net *net)
अणु
	__udp_sysctl_init(net);
	वापस 0;
पूर्ण

अटल काष्ठा pernet_operations __net_initdata udp_sysctl_ops = अणु
	.init	= udp_sysctl_init,
पूर्ण;

#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_PROC_FS)
DEFINE_BPF_ITER_FUNC(udp, काष्ठा bpf_iter_meta *meta,
		     काष्ठा udp_sock *udp_sk, uid_t uid, पूर्णांक bucket)

अटल पूर्णांक bpf_iter_init_udp(व्योम *priv_data, काष्ठा bpf_iter_aux_info *aux)
अणु
	काष्ठा udp_iter_state *st = priv_data;
	काष्ठा udp_seq_afinfo *afinfo;
	पूर्णांक ret;

	afinfo = kदो_स्मृति(माप(*afinfo), GFP_USER | __GFP_NOWARN);
	अगर (!afinfo)
		वापस -ENOMEM;

	afinfo->family = AF_UNSPEC;
	afinfo->udp_table = &udp_table;
	st->bpf_seq_afinfo = afinfo;
	ret = bpf_iter_init_seq_net(priv_data, aux);
	अगर (ret)
		kमुक्त(afinfo);
	वापस ret;
पूर्ण

अटल व्योम bpf_iter_fini_udp(व्योम *priv_data)
अणु
	काष्ठा udp_iter_state *st = priv_data;

	kमुक्त(st->bpf_seq_afinfo);
	bpf_iter_fini_seq_net(priv_data);
पूर्ण

अटल स्थिर काष्ठा bpf_iter_seq_info udp_seq_info = अणु
	.seq_ops		= &bpf_iter_udp_seq_ops,
	.init_seq_निजी	= bpf_iter_init_udp,
	.fini_seq_निजी	= bpf_iter_fini_udp,
	.seq_priv_size		= माप(काष्ठा udp_iter_state),
पूर्ण;

अटल काष्ठा bpf_iter_reg udp_reg_info = अणु
	.target			= "udp",
	.ctx_arg_info_size	= 1,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__udp, udp_sk),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
	पूर्ण,
	.seq_info		= &udp_seq_info,
पूर्ण;

अटल व्योम __init bpf_iter_रेजिस्टर(व्योम)
अणु
	udp_reg_info.ctx_arg_info[0].btf_id = btf_sock_ids[BTF_SOCK_TYPE_UDP];
	अगर (bpf_iter_reg_target(&udp_reg_info))
		pr_warn("Warning: could not register bpf iterator udp\n");
पूर्ण
#पूर्ण_अगर

व्योम __init udp_init(व्योम)
अणु
	अचिन्हित दीर्घ limit;
	अचिन्हित पूर्णांक i;

	udp_table_init(&udp_table, "UDP");
	limit = nr_मुक्त_buffer_pages() / 8;
	limit = max(limit, 128UL);
	sysctl_udp_mem[0] = limit / 4 * 3;
	sysctl_udp_mem[1] = limit;
	sysctl_udp_mem[2] = sysctl_udp_mem[0] * 2;

	__udp_sysctl_init(&init_net);

	/* 16 spinlocks per cpu */
	udp_busylocks_log = ilog2(nr_cpu_ids) + 4;
	udp_busylocks = kदो_स्मृति(माप(spinlock_t) << udp_busylocks_log,
				GFP_KERNEL);
	अगर (!udp_busylocks)
		panic("UDP: failed to alloc udp_busylocks\n");
	क्रम (i = 0; i < (1U << udp_busylocks_log); i++)
		spin_lock_init(udp_busylocks + i);

	अगर (रेजिस्टर_pernet_subsys(&udp_sysctl_ops))
		panic("UDP: failed to init sysctl parameters.\n");

#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_PROC_FS)
	bpf_iter_रेजिस्टर();
#पूर्ण_अगर
पूर्ण
