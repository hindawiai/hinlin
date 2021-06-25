<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the UDP module.
 *
 * Version:	@(#)udp.h	1.0.2	05/07/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 * Fixes:
 *		Alan Cox	: Turned on udp checksums. I करोn't want to
 *				  chase 'memory corruption' bugs that aren't!
 */
#अगर_अघोषित _UDP_H
#घोषणा _UDP_H

#समावेश <linux/list.h>
#समावेश <linux/bug.h>
#समावेश <net/inet_sock.h>
#समावेश <net/sock.h>
#समावेश <net/snmp.h>
#समावेश <net/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/poll.h>
#समावेश <linux/indirect_call_wrapper.h>

/**
 *	काष्ठा udp_skb_cb  -  UDP(-Lite) निजी variables
 *
 *	@header:      निजी variables used by IPv4/IPv6
 *	@cscov:       checksum coverage length (UDP-Lite only)
 *	@partial_cov: अगर set indicates partial csum coverage
 */
काष्ठा udp_skb_cb अणु
	जोड़ अणु
		काष्ठा inet_skb_parm	h4;
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा inet6_skb_parm	h6;
#पूर्ण_अगर
	पूर्ण header;
	__u16		cscov;
	__u8		partial_cov;
पूर्ण;
#घोषणा UDP_SKB_CB(__skb)	((काष्ठा udp_skb_cb *)((__skb)->cb))

/**
 *	काष्ठा udp_hslot - UDP hash slot
 *
 *	@head:	head of list of sockets
 *	@count:	number of sockets in 'head' list
 *	@lock:	spinlock protecting changes to head/count
 */
काष्ठा udp_hslot अणु
	काष्ठा hlist_head	head;
	पूर्णांक			count;
	spinlock_t		lock;
पूर्ण __attribute__((aligned(2 * माप(दीर्घ))));

/**
 *	काष्ठा udp_table - UDP table
 *
 *	@hash:	hash table, sockets are hashed on (local port)
 *	@hash2:	hash table, sockets are hashed on (local port, local address)
 *	@mask:	number of slots in hash tables, minus 1
 *	@log:	log2(number of slots in hash table)
 */
काष्ठा udp_table अणु
	काष्ठा udp_hslot	*hash;
	काष्ठा udp_hslot	*hash2;
	अचिन्हित पूर्णांक		mask;
	अचिन्हित पूर्णांक		log;
पूर्ण;
बाह्य काष्ठा udp_table udp_table;
व्योम udp_table_init(काष्ठा udp_table *, स्थिर अक्षर *);
अटल अंतरभूत काष्ठा udp_hslot *udp_hashslot(काष्ठा udp_table *table,
					     काष्ठा net *net, अचिन्हित पूर्णांक num)
अणु
	वापस &table->hash[udp_hashfn(net, num, table->mask)];
पूर्ण
/*
 * For secondary hash, net_hash_mix() is perक्रमmed beक्रमe calling
 * udp_hashslot2(), this explains dअगरference with udp_hashslot()
 */
अटल अंतरभूत काष्ठा udp_hslot *udp_hashslot2(काष्ठा udp_table *table,
					      अचिन्हित पूर्णांक hash)
अणु
	वापस &table->hash2[hash & table->mask];
पूर्ण

बाह्य काष्ठा proto udp_prot;

बाह्य atomic_दीर्घ_t udp_memory_allocated;

/* sysctl variables क्रम udp */
बाह्य दीर्घ sysctl_udp_mem[3];
बाह्य पूर्णांक sysctl_udp_rmem_min;
बाह्य पूर्णांक sysctl_udp_wmem_min;

काष्ठा sk_buff;

/*
 *	Generic checksumming routines क्रम UDP(-Lite) v4 and v6
 */
अटल अंतरभूत __sum16 __udp_lib_checksum_complete(काष्ठा sk_buff *skb)
अणु
	वापस (UDP_SKB_CB(skb)->cscov == skb->len ?
		__skb_checksum_complete(skb) :
		__skb_checksum_complete_head(skb, UDP_SKB_CB(skb)->cscov));
पूर्ण

अटल अंतरभूत पूर्णांक udp_lib_checksum_complete(काष्ठा sk_buff *skb)
अणु
	वापस !skb_csum_unnecessary(skb) &&
		__udp_lib_checksum_complete(skb);
पूर्ण

/**
 * 	udp_csum_outgoing  -  compute UDPv4/v6 checksum over fragments
 * 	@sk: 	socket we are writing to
 * 	@skb: 	sk_buff containing the filled-in UDP header
 * 	        (checksum field must be zeroed out)
 */
अटल अंतरभूत __wsum udp_csum_outgoing(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	__wsum csum = csum_partial(skb_transport_header(skb),
				   माप(काष्ठा udphdr), 0);
	skb_queue_walk(&sk->sk_ग_लिखो_queue, skb) अणु
		csum = csum_add(csum, skb->csum);
	पूर्ण
	वापस csum;
पूर्ण

अटल अंतरभूत __wsum udp_csum(काष्ठा sk_buff *skb)
अणु
	__wsum csum = csum_partial(skb_transport_header(skb),
				   माप(काष्ठा udphdr), skb->csum);

	क्रम (skb = skb_shinfo(skb)->frag_list; skb; skb = skb->next) अणु
		csum = csum_add(csum, skb->csum);
	पूर्ण
	वापस csum;
पूर्ण

अटल अंतरभूत __sum16 udp_v4_check(पूर्णांक len, __be32 saddr,
				   __be32 daddr, __wsum base)
अणु
	वापस csum_tcpudp_magic(saddr, daddr, len, IPPROTO_UDP, base);
पूर्ण

व्योम udp_set_csum(bool nocheck, काष्ठा sk_buff *skb,
		  __be32 saddr, __be32 daddr, पूर्णांक len);

अटल अंतरभूत व्योम udp_csum_pull_header(काष्ठा sk_buff *skb)
अणु
	अगर (!skb->csum_valid && skb->ip_summed == CHECKSUM_NONE)
		skb->csum = csum_partial(skb->data, माप(काष्ठा udphdr),
					 skb->csum);
	skb_pull_rcsum(skb, माप(काष्ठा udphdr));
	UDP_SKB_CB(skb)->cscov -= माप(काष्ठा udphdr);
पूर्ण

प्रकार काष्ठा sock *(*udp_lookup_t)(स्थिर काष्ठा sk_buff *skb, __be16 sport,
				     __be16 dport);

INसूचीECT_CALLABLE_DECLARE(काष्ठा sk_buff *udp4_gro_receive(काष्ठा list_head *,
							   काष्ठा sk_buff *));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक udp4_gro_complete(काष्ठा sk_buff *, पूर्णांक));
INसूचीECT_CALLABLE_DECLARE(काष्ठा sk_buff *udp6_gro_receive(काष्ठा list_head *,
							   काष्ठा sk_buff *));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक udp6_gro_complete(काष्ठा sk_buff *, पूर्णांक));
INसूचीECT_CALLABLE_DECLARE(व्योम udp_v6_early_demux(काष्ठा sk_buff *));
INसूचीECT_CALLABLE_DECLARE(पूर्णांक udpv6_rcv(काष्ठा sk_buff *));

काष्ठा sk_buff *udp_gro_receive(काष्ठा list_head *head, काष्ठा sk_buff *skb,
				काष्ठा udphdr *uh, काष्ठा sock *sk);
पूर्णांक udp_gro_complete(काष्ठा sk_buff *skb, पूर्णांक nhoff, udp_lookup_t lookup);

काष्ठा sk_buff *__udp_gso_segment(काष्ठा sk_buff *gso_skb,
				  netdev_features_t features, bool is_ipv6);

अटल अंतरभूत काष्ठा udphdr *udp_gro_udphdr(काष्ठा sk_buff *skb)
अणु
	काष्ठा udphdr *uh;
	अचिन्हित पूर्णांक hlen, off;

	off  = skb_gro_offset(skb);
	hlen = off + माप(*uh);
	uh   = skb_gro_header_fast(skb, off);
	अगर (skb_gro_header_hard(skb, hlen))
		uh = skb_gro_header_slow(skb, hlen, off);

	वापस uh;
पूर्ण

/* hash routines shared between UDPv4/6 and UDP-Litev4/6 */
अटल अंतरभूत पूर्णांक udp_lib_hash(काष्ठा sock *sk)
अणु
	BUG();
	वापस 0;
पूर्ण

व्योम udp_lib_unhash(काष्ठा sock *sk);
व्योम udp_lib_rehash(काष्ठा sock *sk, u16 new_hash);

अटल अंतरभूत व्योम udp_lib_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	sk_common_release(sk);
पूर्ण

पूर्णांक udp_lib_get_port(काष्ठा sock *sk, अचिन्हित लघु snum,
		     अचिन्हित पूर्णांक hash2_nulladdr);

u32 udp_flow_hashrnd(व्योम);

अटल अंतरभूत __be16 udp_flow_src_port(काष्ठा net *net, काष्ठा sk_buff *skb,
				       पूर्णांक min, पूर्णांक max, bool use_eth)
अणु
	u32 hash;

	अगर (min >= max) अणु
		/* Use शेष range */
		inet_get_local_port_range(net, &min, &max);
	पूर्ण

	hash = skb_get_hash(skb);
	अगर (unlikely(!hash)) अणु
		अगर (use_eth) अणु
			/* Can't find a normal hash, caller has indicated an
			 * Ethernet packet so use that to compute a hash.
			 */
			hash = jhash(skb->data, 2 * ETH_ALEN,
				     (__क्रमce u32) skb->protocol);
		पूर्ण अन्यथा अणु
			/* Can't derive any sort of hash क्रम the packet, set
			 * to some consistent अक्रमom value.
			 */
			hash = udp_flow_hashrnd();
		पूर्ण
	पूर्ण

	/* Since this is being sent on the wire obfuscate hash a bit
	 * to minimize possbility that any useful inक्रमmation to an
	 * attacker is leaked. Only upper 16 bits are relevant in the
	 * computation क्रम 16 bit port value.
	 */
	hash ^= hash << 16;

	वापस htons((((u64) hash * (max - min)) >> 32) + min);
पूर्ण

अटल अंतरभूत पूर्णांक udp_rqueue_get(काष्ठा sock *sk)
अणु
	वापस sk_rmem_alloc_get(sk) - READ_ONCE(udp_sk(sk)->क्रमward_deficit);
पूर्ण

अटल अंतरभूत bool udp_sk_bound_dev_eq(काष्ठा net *net, पूर्णांक bound_dev_अगर,
				       पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
#अगर IS_ENABLED(CONFIG_NET_L3_MASTER_DEV)
	वापस inet_bound_dev_eq(!!net->ipv4.sysctl_udp_l3mdev_accept,
				 bound_dev_अगर, dअगर, sdअगर);
#अन्यथा
	वापस inet_bound_dev_eq(true, bound_dev_अगर, dअगर, sdअगर);
#पूर्ण_अगर
पूर्ण

/* net/ipv4/udp.c */
व्योम udp_deकाष्ठा_sock(काष्ठा sock *sk);
व्योम skb_consume_udp(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक len);
पूर्णांक __udp_enqueue_schedule_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम udp_skb_deकाष्ठाor(काष्ठा sock *sk, काष्ठा sk_buff *skb);
काष्ठा sk_buff *__skb_recv_udp(काष्ठा sock *sk, अचिन्हित पूर्णांक flags,
			       पूर्णांक noblock, पूर्णांक *off, पूर्णांक *err);
अटल अंतरभूत काष्ठा sk_buff *skb_recv_udp(काष्ठा sock *sk, अचिन्हित पूर्णांक flags,
					   पूर्णांक noblock, पूर्णांक *err)
अणु
	पूर्णांक off = 0;

	वापस __skb_recv_udp(sk, flags, noblock, &off, err);
पूर्ण

पूर्णांक udp_v4_early_demux(काष्ठा sk_buff *skb);
bool udp_sk_rx_dst_set(काष्ठा sock *sk, काष्ठा dst_entry *dst);
पूर्णांक udp_get_port(काष्ठा sock *sk, अचिन्हित लघु snum,
		 पूर्णांक (*saddr_cmp)(स्थिर काष्ठा sock *,
				  स्थिर काष्ठा sock *));
पूर्णांक udp_err(काष्ठा sk_buff *, u32);
पूर्णांक udp_पात(काष्ठा sock *sk, पूर्णांक err);
पूर्णांक udp_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len);
पूर्णांक udp_push_pending_frames(काष्ठा sock *sk);
व्योम udp_flush_pending_frames(काष्ठा sock *sk);
पूर्णांक udp_cmsg_send(काष्ठा sock *sk, काष्ठा msghdr *msg, u16 *gso_size);
व्योम udp4_hwcsum(काष्ठा sk_buff *skb, __be32 src, __be32 dst);
पूर्णांक udp_rcv(काष्ठा sk_buff *skb);
पूर्णांक udp_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक udp_init_sock(काष्ठा sock *sk);
पूर्णांक udp_pre_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len);
पूर्णांक __udp_disconnect(काष्ठा sock *sk, पूर्णांक flags);
पूर्णांक udp_disconnect(काष्ठा sock *sk, पूर्णांक flags);
__poll_t udp_poll(काष्ठा file *file, काष्ठा socket *sock, poll_table *रुको);
काष्ठा sk_buff *skb_udp_tunnel_segment(काष्ठा sk_buff *skb,
				       netdev_features_t features,
				       bool is_ipv6);
पूर्णांक udp_lib_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		       अक्षर __user *optval, पूर्णांक __user *optlen);
पूर्णांक udp_lib_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		       sockptr_t optval, अचिन्हित पूर्णांक optlen,
		       पूर्णांक (*push_pending_frames)(काष्ठा sock *));
काष्ठा sock *udp4_lib_lookup(काष्ठा net *net, __be32 saddr, __be16 sport,
			     __be32 daddr, __be16 dport, पूर्णांक dअगर);
काष्ठा sock *__udp4_lib_lookup(काष्ठा net *net, __be32 saddr, __be16 sport,
			       __be32 daddr, __be16 dport, पूर्णांक dअगर, पूर्णांक sdअगर,
			       काष्ठा udp_table *tbl, काष्ठा sk_buff *skb);
काष्ठा sock *udp4_lib_lookup_skb(स्थिर काष्ठा sk_buff *skb,
				 __be16 sport, __be16 dport);
काष्ठा sock *udp6_lib_lookup(काष्ठा net *net,
			     स्थिर काष्ठा in6_addr *saddr, __be16 sport,
			     स्थिर काष्ठा in6_addr *daddr, __be16 dport,
			     पूर्णांक dअगर);
काष्ठा sock *__udp6_lib_lookup(काष्ठा net *net,
			       स्थिर काष्ठा in6_addr *saddr, __be16 sport,
			       स्थिर काष्ठा in6_addr *daddr, __be16 dport,
			       पूर्णांक dअगर, पूर्णांक sdअगर, काष्ठा udp_table *tbl,
			       काष्ठा sk_buff *skb);
काष्ठा sock *udp6_lib_lookup_skb(स्थिर काष्ठा sk_buff *skb,
				 __be16 sport, __be16 dport);
पूर्णांक udp_पढ़ो_sock(काष्ठा sock *sk, पढ़ो_descriptor_t *desc,
		  sk_पढ़ो_actor_t recv_actor);

/* UDP uses skb->dev_scratch to cache as much inक्रमmation as possible and aव्योम
 * possibly multiple cache miss on dequeue()
 */
काष्ठा udp_dev_scratch अणु
	/* skb->truesize and the stateless bit are embedded in a single field;
	 * करो not use a bitfield since the compiler emits better/smaller code
	 * this way
	 */
	u32 _tsize_state;

#अगर BITS_PER_LONG == 64
	/* len and the bit needed to compute skb_csum_unnecessary
	 * will be on cold cache lines at recvmsg समय.
	 * skb->len can be stored on 16 bits since the udp header has been
	 * alपढ़ोy validated and pulled.
	 */
	u16 len;
	bool is_linear;
	bool csum_unnecessary;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा udp_dev_scratch *udp_skb_scratch(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा udp_dev_scratch *)&skb->dev_scratch;
पूर्ण

#अगर BITS_PER_LONG == 64
अटल अंतरभूत अचिन्हित पूर्णांक udp_skb_len(काष्ठा sk_buff *skb)
अणु
	वापस udp_skb_scratch(skb)->len;
पूर्ण

अटल अंतरभूत bool udp_skb_csum_unnecessary(काष्ठा sk_buff *skb)
अणु
	वापस udp_skb_scratch(skb)->csum_unnecessary;
पूर्ण

अटल अंतरभूत bool udp_skb_is_linear(काष्ठा sk_buff *skb)
अणु
	वापस udp_skb_scratch(skb)->is_linear;
पूर्ण

#अन्यथा
अटल अंतरभूत अचिन्हित पूर्णांक udp_skb_len(काष्ठा sk_buff *skb)
अणु
	वापस skb->len;
पूर्ण

अटल अंतरभूत bool udp_skb_csum_unnecessary(काष्ठा sk_buff *skb)
अणु
	वापस skb_csum_unnecessary(skb);
पूर्ण

अटल अंतरभूत bool udp_skb_is_linear(काष्ठा sk_buff *skb)
अणु
	वापस !skb_is_nonlinear(skb);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक copy_linear_skb(काष्ठा sk_buff *skb, पूर्णांक len, पूर्णांक off,
				  काष्ठा iov_iter *to)
अणु
	पूर्णांक n;

	n = copy_to_iter(skb->data + off, len, to);
	अगर (n == len)
		वापस 0;

	iov_iter_revert(to, n);
	वापस -EFAULT;
पूर्ण

/*
 * 	SNMP statistics क्रम UDP and UDP-Lite
 */
#घोषणा UDP_INC_STATS(net, field, is_udplite)		      करो अणु \
	अगर (is_udplite) SNMP_INC_STATS((net)->mib.udplite_statistics, field);       \
	अन्यथा		SNMP_INC_STATS((net)->mib.udp_statistics, field);  पूर्ण  जबतक(0)
#घोषणा __UDP_INC_STATS(net, field, is_udplite) 	      करो अणु \
	अगर (is_udplite) __SNMP_INC_STATS((net)->mib.udplite_statistics, field);         \
	अन्यथा		__SNMP_INC_STATS((net)->mib.udp_statistics, field);    पूर्ण  जबतक(0)

#घोषणा __UDP6_INC_STATS(net, field, is_udplite)	    करो अणु \
	अगर (is_udplite) __SNMP_INC_STATS((net)->mib.udplite_stats_in6, field);\
	अन्यथा		__SNMP_INC_STATS((net)->mib.udp_stats_in6, field);  \
पूर्ण जबतक(0)
#घोषणा UDP6_INC_STATS(net, field, __lite)		    करो अणु \
	अगर (__lite) SNMP_INC_STATS((net)->mib.udplite_stats_in6, field);  \
	अन्यथा	    SNMP_INC_STATS((net)->mib.udp_stats_in6, field);      \
पूर्ण जबतक(0)

#अगर IS_ENABLED(CONFIG_IPV6)
#घोषणा __UDPX_MIB(sk, ipv4)						\
(अणु									\
	ipv4 ? (IS_UDPLITE(sk) ? sock_net(sk)->mib.udplite_statistics :	\
				 sock_net(sk)->mib.udp_statistics) :	\
		(IS_UDPLITE(sk) ? sock_net(sk)->mib.udplite_stats_in6 :	\
				 sock_net(sk)->mib.udp_stats_in6);	\
पूर्ण)
#अन्यथा
#घोषणा __UDPX_MIB(sk, ipv4)						\
(अणु									\
	IS_UDPLITE(sk) ? sock_net(sk)->mib.udplite_statistics :		\
			 sock_net(sk)->mib.udp_statistics;		\
पूर्ण)
#पूर्ण_अगर

#घोषणा __UDPX_INC_STATS(sk, field) \
	__SNMP_INC_STATS(__UDPX_MIB(sk, (sk)->sk_family == AF_INET), field)

#अगर_घोषित CONFIG_PROC_FS
काष्ठा udp_seq_afinfo अणु
	sa_family_t			family;
	काष्ठा udp_table		*udp_table;
पूर्ण;

काष्ठा udp_iter_state अणु
	काष्ठा seq_net_निजी  p;
	पूर्णांक			bucket;
	काष्ठा udp_seq_afinfo	*bpf_seq_afinfo;
पूर्ण;

व्योम *udp_seq_start(काष्ठा seq_file *seq, loff_t *pos);
व्योम *udp_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos);
व्योम udp_seq_stop(काष्ठा seq_file *seq, व्योम *v);

बाह्य स्थिर काष्ठा seq_operations udp_seq_ops;
बाह्य स्थिर काष्ठा seq_operations udp6_seq_ops;

पूर्णांक udp4_proc_init(व्योम);
व्योम udp4_proc_निकास(व्योम);
#पूर्ण_अगर /* CONFIG_PROC_FS */

पूर्णांक udpv4_offload_init(व्योम);

व्योम udp_init(व्योम);

DECLARE_STATIC_KEY_FALSE(udp_encap_needed_key);
व्योम udp_encap_enable(व्योम);
व्योम udp_encap_disable(व्योम);
#अगर IS_ENABLED(CONFIG_IPV6)
DECLARE_STATIC_KEY_FALSE(udpv6_encap_needed_key);
व्योम udpv6_encap_enable(व्योम);
#पूर्ण_अगर

अटल अंतरभूत काष्ठा sk_buff *udp_rcv_segment(काष्ठा sock *sk,
					      काष्ठा sk_buff *skb, bool ipv4)
अणु
	netdev_features_t features = NETIF_F_SG;
	काष्ठा sk_buff *segs;

	/* Aव्योम csum recalculation by skb_segment unless userspace explicitly
	 * asks क्रम the final checksum values
	 */
	अगर (!inet_get_convert_csum(sk))
		features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;

	/* UDP segmentation expects packets of type CHECKSUM_PARTIAL or
	 * CHECKSUM_NONE in __udp_gso_segment. UDP GRO indeed builds partial
	 * packets in udp_gro_complete_segment. As करोes UDP GSO, verअगरied by
	 * udp_send_skb. But when those packets are looped in dev_loopback_xmit
	 * their ip_summed is set to CHECKSUM_UNNECESSARY. Reset in this
	 * specअगरic हाल, where PARTIAL is both correct and required.
	 */
	अगर (skb->pkt_type == PACKET_LOOPBACK)
		skb->ip_summed = CHECKSUM_PARTIAL;

	/* the GSO CB lays after the UDP one, no need to save and restore any
	 * CB fragment
	 */
	segs = __skb_gso_segment(skb, features, false);
	अगर (IS_ERR_OR_शून्य(segs)) अणु
		पूर्णांक segs_nr = skb_shinfo(skb)->gso_segs;

		atomic_add(segs_nr, &sk->sk_drops);
		SNMP_ADD_STATS(__UDPX_MIB(sk, ipv4), UDP_MIB_INERRORS, segs_nr);
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	consume_skb(skb);
	वापस segs;
पूर्ण

अटल अंतरभूत व्योम udp_post_segment_fix_csum(काष्ठा sk_buff *skb)
अणु
	/* UDP-lite can't land here - no GRO */
	WARN_ON_ONCE(UDP_SKB_CB(skb)->partial_cov);

	/* UDP packets generated with UDP_SEGMENT and traversing:
	 *
	 * UDP tunnel(xmit) -> veth (segmentation) -> veth (gro) -> UDP tunnel (rx)
	 *
	 * can reach an UDP socket with CHECKSUM_NONE, because
	 * __iptunnel_pull_header() converts CHECKSUM_PARTIAL पूर्णांकo NONE.
	 * SKB_GSO_UDP_L4 or SKB_GSO_FRAGLIST packets with no UDP tunnel will
	 * have a valid checksum, as the GRO engine validates the UDP csum
	 * beक्रमe the aggregation and nobody strips such info in between.
	 * Instead of adding another check in the tunnel fastpath, we can क्रमce
	 * a valid csum after the segmentation.
	 * Additionally fixup the UDP CB.
	 */
	UDP_SKB_CB(skb)->cscov = skb->len;
	अगर (skb->ip_summed == CHECKSUM_NONE && !skb->csum_valid)
		skb->csum_valid = 1;
पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
काष्ठा sk_psock;
काष्ठा proto *udp_bpf_get_proto(काष्ठा sock *sk, काष्ठा sk_psock *psock);
पूर्णांक udp_bpf_update_proto(काष्ठा sock *sk, काष्ठा sk_psock *psock, bool restore);
#पूर्ण_अगर

#पूर्ण_अगर	/* _UDP_H */
