<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 */

#अगर_अघोषित _NET_IPV6_H
#घोषणा _NET_IPV6_H

#समावेश <linux/ipv6.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/jhash.h>
#समावेश <linux/refcount.h>
#समावेश <linux/jump_label_ratelimit.h>
#समावेश <net/अगर_inet6.h>
#समावेश <net/ndisc.h>
#समावेश <net/flow.h>
#समावेश <net/flow_dissector.h>
#समावेश <net/snmp.h>
#समावेश <net/netns/hash.h>

#घोषणा SIN6_LEN_RFC2133	24

#घोषणा IPV6_MAXPLEN		65535

/*
 *	NextHeader field of IPv6 header
 */

#घोषणा NEXTHDR_HOP		0	/* Hop-by-hop option header. */
#घोषणा NEXTHDR_IPV4		4	/* IPv4 in IPv6 */
#घोषणा NEXTHDR_TCP		6	/* TCP segment. */
#घोषणा NEXTHDR_UDP		17	/* UDP message. */
#घोषणा NEXTHDR_IPV6		41	/* IPv6 in IPv6 */
#घोषणा NEXTHDR_ROUTING		43	/* Routing header. */
#घोषणा NEXTHDR_FRAGMENT	44	/* Fragmentation/reassembly header. */
#घोषणा NEXTHDR_GRE		47	/* GRE header. */
#घोषणा NEXTHDR_ESP		50	/* Encapsulating security payload. */
#घोषणा NEXTHDR_AUTH		51	/* Authentication header. */
#घोषणा NEXTHDR_ICMP		58	/* ICMP क्रम IPv6. */
#घोषणा NEXTHDR_NONE		59	/* No next header */
#घोषणा NEXTHDR_DEST		60	/* Destination options header. */
#घोषणा NEXTHDR_SCTP		132	/* SCTP message. */
#घोषणा NEXTHDR_MOBILITY	135	/* Mobility header. */

#घोषणा NEXTHDR_MAX		255

#घोषणा IPV6_DEFAULT_HOPLIMIT   64
#घोषणा IPV6_DEFAULT_MCASTHOPS	1

/* Limits on Hop-by-Hop and Destination options.
 *
 * Per RFC8200 there is no limit on the maximum number or lengths of options in
 * Hop-by-Hop or Destination options other then the packet must fit in an MTU.
 * We allow configurable limits in order to mitigate potential denial of
 * service attacks.
 *
 * There are three limits that may be set:
 *   - Limit the number of options in a Hop-by-Hop or Destination options
 *     extension header
 *   - Limit the byte length of a Hop-by-Hop or Destination options extension
 *     header
 *   - Disallow unknown options
 *
 * The limits are expressed in corresponding sysctls:
 *
 * ipv6.sysctl.max_dst_opts_cnt
 * ipv6.sysctl.max_hbh_opts_cnt
 * ipv6.sysctl.max_dst_opts_len
 * ipv6.sysctl.max_hbh_opts_len
 *
 * max_*_opts_cnt is the number of TLVs that are allowed क्रम Destination
 * options or Hop-by-Hop options. If the number is less than zero then unknown
 * TLVs are disallowed and the number of known options that are allowed is the
 * असलolute value. Setting the value to पूर्णांक_उच्च indicates no limit.
 *
 * max_*_opts_len is the length limit in bytes of a Destination or
 * Hop-by-Hop options extension header. Setting the value to पूर्णांक_उच्च
 * indicates no length limit.
 *
 * If a limit is exceeded when processing an extension header the packet is
 * silently discarded.
 */

/* Default limits क्रम Hop-by-Hop and Destination options */
#घोषणा IP6_DEFAULT_MAX_DST_OPTS_CNT	 8
#घोषणा IP6_DEFAULT_MAX_HBH_OPTS_CNT	 8
#घोषणा IP6_DEFAULT_MAX_DST_OPTS_LEN	 पूर्णांक_उच्च /* No limit */
#घोषणा IP6_DEFAULT_MAX_HBH_OPTS_LEN	 पूर्णांक_उच्च /* No limit */

/*
 *	Addr type
 *	
 *	type	-	unicast | multicast
 *	scope	-	local	| site	    | global
 *	v4	-	compat
 *	v4mapped
 *	any
 *	loopback
 */

#घोषणा IPV6_ADDR_ANY		0x0000U

#घोषणा IPV6_ADDR_UNICAST	0x0001U
#घोषणा IPV6_ADDR_MULTICAST	0x0002U

#घोषणा IPV6_ADDR_LOOPBACK	0x0010U
#घोषणा IPV6_ADDR_LINKLOCAL	0x0020U
#घोषणा IPV6_ADDR_SITELOCAL	0x0040U

#घोषणा IPV6_ADDR_COMPATv4	0x0080U

#घोषणा IPV6_ADDR_SCOPE_MASK	0x00f0U

#घोषणा IPV6_ADDR_MAPPED	0x1000U

/*
 *	Addr scopes
 */
#घोषणा IPV6_ADDR_MC_SCOPE(a)	\
	((a)->s6_addr[1] & 0x0f)	/* nonstandard */
#घोषणा __IPV6_ADDR_SCOPE_INVALID	-1
#घोषणा IPV6_ADDR_SCOPE_NODELOCAL	0x01
#घोषणा IPV6_ADDR_SCOPE_LINKLOCAL	0x02
#घोषणा IPV6_ADDR_SCOPE_SITELOCAL	0x05
#घोषणा IPV6_ADDR_SCOPE_ORGLOCAL	0x08
#घोषणा IPV6_ADDR_SCOPE_GLOBAL		0x0e

/*
 *	Addr flags
 */
#घोषणा IPV6_ADDR_MC_FLAG_TRANSIENT(a)	\
	((a)->s6_addr[1] & 0x10)
#घोषणा IPV6_ADDR_MC_FLAG_PREFIX(a)	\
	((a)->s6_addr[1] & 0x20)
#घोषणा IPV6_ADDR_MC_FLAG_RENDEZVOUS(a)	\
	((a)->s6_addr[1] & 0x40)

/*
 *	fragmentation header
 */

काष्ठा frag_hdr अणु
	__u8	nexthdr;
	__u8	reserved;
	__be16	frag_off;
	__be32	identअगरication;
पूर्ण;

#घोषणा	IP6_MF		0x0001
#घोषणा	IP6_OFFSET	0xFFF8

काष्ठा ip6_fraglist_iter अणु
	काष्ठा ipv6hdr	*पंचांगp_hdr;
	काष्ठा sk_buff	*frag;
	पूर्णांक		offset;
	अचिन्हित पूर्णांक	hlen;
	__be32		frag_id;
	u8		nexthdr;
पूर्ण;

पूर्णांक ip6_fraglist_init(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hlen, u8 *prevhdr,
		      u8 nexthdr, __be32 frag_id,
		      काष्ठा ip6_fraglist_iter *iter);
व्योम ip6_fraglist_prepare(काष्ठा sk_buff *skb, काष्ठा ip6_fraglist_iter *iter);

अटल अंतरभूत काष्ठा sk_buff *ip6_fraglist_next(काष्ठा ip6_fraglist_iter *iter)
अणु
	काष्ठा sk_buff *skb = iter->frag;

	iter->frag = skb->next;
	skb_mark_not_on_list(skb);

	वापस skb;
पूर्ण

काष्ठा ip6_frag_state अणु
	u8		*prevhdr;
	अचिन्हित पूर्णांक	hlen;
	अचिन्हित पूर्णांक	mtu;
	अचिन्हित पूर्णांक	left;
	पूर्णांक		offset;
	पूर्णांक		ptr;
	पूर्णांक		hroom;
	पूर्णांक		troom;
	__be32		frag_id;
	u8		nexthdr;
पूर्ण;

व्योम ip6_frag_init(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hlen, अचिन्हित पूर्णांक mtu,
		   अचिन्हित लघु needed_tailroom, पूर्णांक hdr_room, u8 *prevhdr,
		   u8 nexthdr, __be32 frag_id, काष्ठा ip6_frag_state *state);
काष्ठा sk_buff *ip6_frag_next(काष्ठा sk_buff *skb,
			      काष्ठा ip6_frag_state *state);

#घोषणा IP6_REPLY_MARK(net, mark) \
	((net)->ipv6.sysctl.fwmark_reflect ? (mark) : 0)

#समावेश <net/sock.h>

/* sysctls */
बाह्य पूर्णांक sysctl_mld_max_msf;
बाह्य पूर्णांक sysctl_mld_qrv;

#घोषणा _DEVINC(net, statname, mod, idev, field)			\
(अणु									\
	काष्ठा inet6_dev *_idev = (idev);				\
	अगर (likely(_idev != शून्य))					\
		mod##SNMP_INC_STATS64((_idev)->stats.statname, (field));\
	mod##SNMP_INC_STATS64((net)->mib.statname##_statistics, (field));\
पूर्ण)

/* per device counters are atomic_दीर्घ_t */
#घोषणा _DEVINCATOMIC(net, statname, mod, idev, field)			\
(अणु									\
	काष्ठा inet6_dev *_idev = (idev);				\
	अगर (likely(_idev != शून्य))					\
		SNMP_INC_STATS_ATOMIC_LONG((_idev)->stats.statname##dev, (field)); \
	mod##SNMP_INC_STATS((net)->mib.statname##_statistics, (field));\
पूर्ण)

/* per device and per net counters are atomic_दीर्घ_t */
#घोषणा _DEVINC_ATOMIC_ATOMIC(net, statname, idev, field)		\
(अणु									\
	काष्ठा inet6_dev *_idev = (idev);				\
	अगर (likely(_idev != शून्य))					\
		SNMP_INC_STATS_ATOMIC_LONG((_idev)->stats.statname##dev, (field)); \
	SNMP_INC_STATS_ATOMIC_LONG((net)->mib.statname##_statistics, (field));\
पूर्ण)

#घोषणा _DEVADD(net, statname, mod, idev, field, val)			\
(अणु									\
	काष्ठा inet6_dev *_idev = (idev);				\
	अगर (likely(_idev != शून्य))					\
		mod##SNMP_ADD_STATS((_idev)->stats.statname, (field), (val)); \
	mod##SNMP_ADD_STATS((net)->mib.statname##_statistics, (field), (val));\
पूर्ण)

#घोषणा _DEVUPD(net, statname, mod, idev, field, val)			\
(अणु									\
	काष्ठा inet6_dev *_idev = (idev);				\
	अगर (likely(_idev != शून्य))					\
		mod##SNMP_UPD_PO_STATS((_idev)->stats.statname, field, (val)); \
	mod##SNMP_UPD_PO_STATS((net)->mib.statname##_statistics, field, (val));\
पूर्ण)

/* MIBs */

#घोषणा IP6_INC_STATS(net, idev,field)		\
		_DEVINC(net, ipv6, , idev, field)
#घोषणा __IP6_INC_STATS(net, idev,field)	\
		_DEVINC(net, ipv6, __, idev, field)
#घोषणा IP6_ADD_STATS(net, idev,field,val)	\
		_DEVADD(net, ipv6, , idev, field, val)
#घोषणा __IP6_ADD_STATS(net, idev,field,val)	\
		_DEVADD(net, ipv6, __, idev, field, val)
#घोषणा IP6_UPD_PO_STATS(net, idev,field,val)   \
		_DEVUPD(net, ipv6, , idev, field, val)
#घोषणा __IP6_UPD_PO_STATS(net, idev,field,val)   \
		_DEVUPD(net, ipv6, __, idev, field, val)
#घोषणा ICMP6_INC_STATS(net, idev, field)	\
		_DEVINCATOMIC(net, icmpv6, , idev, field)
#घोषणा __ICMP6_INC_STATS(net, idev, field)	\
		_DEVINCATOMIC(net, icmpv6, __, idev, field)

#घोषणा ICMP6MSGOUT_INC_STATS(net, idev, field)		\
	_DEVINC_ATOMIC_ATOMIC(net, icmpv6msg, idev, field +256)
#घोषणा ICMP6MSGIN_INC_STATS(net, idev, field)	\
	_DEVINC_ATOMIC_ATOMIC(net, icmpv6msg, idev, field)

काष्ठा ip6_ra_chain अणु
	काष्ठा ip6_ra_chain	*next;
	काष्ठा sock		*sk;
	पूर्णांक			sel;
	व्योम			(*deकाष्ठाor)(काष्ठा sock *);
पूर्ण;

बाह्य काष्ठा ip6_ra_chain	*ip6_ra_chain;
बाह्य rwlock_t ip6_ra_lock;

/*
   This काष्ठाure is prepared by protocol, when parsing
   ancillary data and passed to IPv6.
 */

काष्ठा ipv6_txoptions अणु
	refcount_t		refcnt;
	/* Length of this काष्ठाure */
	पूर्णांक			tot_len;

	/* length of extension headers   */

	__u16			opt_flen;	/* after fragment hdr */
	__u16			opt_nflen;	/* beक्रमe fragment hdr */

	काष्ठा ipv6_opt_hdr	*hopopt;
	काष्ठा ipv6_opt_hdr	*dst0opt;
	काष्ठा ipv6_rt_hdr	*srcrt;	/* Routing Header */
	काष्ठा ipv6_opt_hdr	*dst1opt;
	काष्ठा rcu_head		rcu;
	/* Option buffer, as पढ़ो by IPV6_PKTOPTIONS, starts here. */
पूर्ण;

/* flowlabel_reflect sysctl values */
क्रमागत flowlabel_reflect अणु
	FLOWLABEL_REFLECT_ESTABLISHED		= 1,
	FLOWLABEL_REFLECT_TCP_RESET		= 2,
	FLOWLABEL_REFLECT_ICMPV6_ECHO_REPLIES	= 4,
पूर्ण;

काष्ठा ip6_flowlabel अणु
	काष्ठा ip6_flowlabel __rcu *next;
	__be32			label;
	atomic_t		users;
	काष्ठा in6_addr		dst;
	काष्ठा ipv6_txoptions	*opt;
	अचिन्हित दीर्घ		linger;
	काष्ठा rcu_head		rcu;
	u8			share;
	जोड़ अणु
		काष्ठा pid *pid;
		kuid_t uid;
	पूर्ण owner;
	अचिन्हित दीर्घ		lastuse;
	अचिन्हित दीर्घ		expires;
	काष्ठा net		*fl_net;
पूर्ण;

#घोषणा IPV6_FLOWINFO_MASK		cpu_to_be32(0x0FFFFFFF)
#घोषणा IPV6_FLOWLABEL_MASK		cpu_to_be32(0x000FFFFF)
#घोषणा IPV6_FLOWLABEL_STATELESS_FLAG	cpu_to_be32(0x00080000)

#घोषणा IPV6_TCLASS_MASK (IPV6_FLOWINFO_MASK & ~IPV6_FLOWLABEL_MASK)
#घोषणा IPV6_TCLASS_SHIFT	20

काष्ठा ipv6_fl_socklist अणु
	काष्ठा ipv6_fl_socklist	__rcu	*next;
	काष्ठा ip6_flowlabel		*fl;
	काष्ठा rcu_head			rcu;
पूर्ण;

काष्ठा ipcm6_cookie अणु
	काष्ठा sockcm_cookie sockc;
	__s16 hlimit;
	__s16 tclass;
	__s8  करोntfrag;
	काष्ठा ipv6_txoptions *opt;
	__u16 gso_size;
पूर्ण;

अटल अंतरभूत व्योम ipcm6_init(काष्ठा ipcm6_cookie *ipc6)
अणु
	*ipc6 = (काष्ठा ipcm6_cookie) अणु
		.hlimit = -1,
		.tclass = -1,
		.करोntfrag = -1,
	पूर्ण;
पूर्ण

अटल अंतरभूत व्योम ipcm6_init_sk(काष्ठा ipcm6_cookie *ipc6,
				 स्थिर काष्ठा ipv6_pinfo *np)
अणु
	*ipc6 = (काष्ठा ipcm6_cookie) अणु
		.hlimit = -1,
		.tclass = np->tclass,
		.करोntfrag = np->करोntfrag,
	पूर्ण;
पूर्ण

अटल अंतरभूत काष्ठा ipv6_txoptions *txopt_get(स्थिर काष्ठा ipv6_pinfo *np)
अणु
	काष्ठा ipv6_txoptions *opt;

	rcu_पढ़ो_lock();
	opt = rcu_dereference(np->opt);
	अगर (opt) अणु
		अगर (!refcount_inc_not_zero(&opt->refcnt))
			opt = शून्य;
		अन्यथा
			opt = rcu_poपूर्णांकer_hanकरोff(opt);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस opt;
पूर्ण

अटल अंतरभूत व्योम txopt_put(काष्ठा ipv6_txoptions *opt)
अणु
	अगर (opt && refcount_dec_and_test(&opt->refcnt))
		kमुक्त_rcu(opt, rcu);
पूर्ण

काष्ठा ip6_flowlabel *__fl6_sock_lookup(काष्ठा sock *sk, __be32 label);

बाह्य काष्ठा अटल_key_false_deferred ipv6_flowlabel_exclusive;
अटल अंतरभूत काष्ठा ip6_flowlabel *fl6_sock_lookup(काष्ठा sock *sk,
						    __be32 label)
अणु
	अगर (अटल_branch_unlikely(&ipv6_flowlabel_exclusive.key))
		वापस __fl6_sock_lookup(sk, label) ? : ERR_PTR(-ENOENT);

	वापस शून्य;
पूर्ण

काष्ठा ipv6_txoptions *fl6_merge_options(काष्ठा ipv6_txoptions *opt_space,
					 काष्ठा ip6_flowlabel *fl,
					 काष्ठा ipv6_txoptions *fopt);
व्योम fl6_मुक्त_socklist(काष्ठा sock *sk);
पूर्णांक ipv6_flowlabel_opt(काष्ठा sock *sk, sockptr_t optval, पूर्णांक optlen);
पूर्णांक ipv6_flowlabel_opt_get(काष्ठा sock *sk, काष्ठा in6_flowlabel_req *freq,
			   पूर्णांक flags);
पूर्णांक ip6_flowlabel_init(व्योम);
व्योम ip6_flowlabel_cleanup(व्योम);
bool ip6_स्वतःflowlabel(काष्ठा net *net, स्थिर काष्ठा ipv6_pinfo *np);

अटल अंतरभूत व्योम fl6_sock_release(काष्ठा ip6_flowlabel *fl)
अणु
	अगर (fl)
		atomic_dec(&fl->users);
पूर्ण

व्योम icmpv6_notअगरy(काष्ठा sk_buff *skb, u8 type, u8 code, __be32 info);

व्योम icmpv6_push_pending_frames(काष्ठा sock *sk, काष्ठा flowi6 *fl6,
				काष्ठा icmp6hdr *thdr, पूर्णांक len);

पूर्णांक ip6_ra_control(काष्ठा sock *sk, पूर्णांक sel);

पूर्णांक ipv6_parse_hopopts(काष्ठा sk_buff *skb);

काष्ठा ipv6_txoptions *ipv6_dup_options(काष्ठा sock *sk,
					काष्ठा ipv6_txoptions *opt);
काष्ठा ipv6_txoptions *ipv6_renew_options(काष्ठा sock *sk,
					  काष्ठा ipv6_txoptions *opt,
					  पूर्णांक newtype,
					  काष्ठा ipv6_opt_hdr *newopt);
काष्ठा ipv6_txoptions *ipv6_fixup_options(काष्ठा ipv6_txoptions *opt_space,
					  काष्ठा ipv6_txoptions *opt);

bool ipv6_opt_accepted(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb,
		       स्थिर काष्ठा inet6_skb_parm *opt);
काष्ठा ipv6_txoptions *ipv6_update_options(काष्ठा sock *sk,
					   काष्ठा ipv6_txoptions *opt);

अटल अंतरभूत bool ipv6_accept_ra(काष्ठा inet6_dev *idev)
अणु
	/* If क्रमwarding is enabled, RA are not accepted unless the special
	 * hybrid mode (accept_ra=2) is enabled.
	 */
	वापस idev->cnf.क्रमwarding ? idev->cnf.accept_ra == 2 :
	    idev->cnf.accept_ra;
पूर्ण

#घोषणा IPV6_FRAG_HIGH_THRESH	(4 * 1024*1024)	/* 4194304 */
#घोषणा IPV6_FRAG_LOW_THRESH	(3 * 1024*1024)	/* 3145728 */
#घोषणा IPV6_FRAG_TIMEOUT	(60 * HZ)	/* 60 seconds */

पूर्णांक __ipv6_addr_type(स्थिर काष्ठा in6_addr *addr);
अटल अंतरभूत पूर्णांक ipv6_addr_type(स्थिर काष्ठा in6_addr *addr)
अणु
	वापस __ipv6_addr_type(addr) & 0xffff;
पूर्ण

अटल अंतरभूत पूर्णांक ipv6_addr_scope(स्थिर काष्ठा in6_addr *addr)
अणु
	वापस __ipv6_addr_type(addr) & IPV6_ADDR_SCOPE_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक __ipv6_addr_src_scope(पूर्णांक type)
अणु
	वापस (type == IPV6_ADDR_ANY) ? __IPV6_ADDR_SCOPE_INVALID : (type >> 16);
पूर्ण

अटल अंतरभूत पूर्णांक ipv6_addr_src_scope(स्थिर काष्ठा in6_addr *addr)
अणु
	वापस __ipv6_addr_src_scope(__ipv6_addr_type(addr));
पूर्ण

अटल अंतरभूत bool __ipv6_addr_needs_scope_id(पूर्णांक type)
अणु
	वापस type & IPV6_ADDR_LINKLOCAL ||
	       (type & IPV6_ADDR_MULTICAST &&
		(type & (IPV6_ADDR_LOOPBACK|IPV6_ADDR_LINKLOCAL)));
पूर्ण

अटल अंतरभूत __u32 ipv6_अगरace_scope_id(स्थिर काष्ठा in6_addr *addr, पूर्णांक अगरace)
अणु
	वापस __ipv6_addr_needs_scope_id(__ipv6_addr_type(addr)) ? अगरace : 0;
पूर्ण

अटल अंतरभूत पूर्णांक ipv6_addr_cmp(स्थिर काष्ठा in6_addr *a1, स्थिर काष्ठा in6_addr *a2)
अणु
	वापस स_भेद(a1, a2, माप(काष्ठा in6_addr));
पूर्ण

अटल अंतरभूत bool
ipv6_masked_addr_cmp(स्थिर काष्ठा in6_addr *a1, स्थिर काष्ठा in6_addr *m,
		     स्थिर काष्ठा in6_addr *a2)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	स्थिर अचिन्हित दीर्घ *ul1 = (स्थिर अचिन्हित दीर्घ *)a1;
	स्थिर अचिन्हित दीर्घ *ulm = (स्थिर अचिन्हित दीर्घ *)m;
	स्थिर अचिन्हित दीर्घ *ul2 = (स्थिर अचिन्हित दीर्घ *)a2;

	वापस !!(((ul1[0] ^ ul2[0]) & ulm[0]) |
		  ((ul1[1] ^ ul2[1]) & ulm[1]));
#अन्यथा
	वापस !!(((a1->s6_addr32[0] ^ a2->s6_addr32[0]) & m->s6_addr32[0]) |
		  ((a1->s6_addr32[1] ^ a2->s6_addr32[1]) & m->s6_addr32[1]) |
		  ((a1->s6_addr32[2] ^ a2->s6_addr32[2]) & m->s6_addr32[2]) |
		  ((a1->s6_addr32[3] ^ a2->s6_addr32[3]) & m->s6_addr32[3]));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ipv6_addr_prefix(काष्ठा in6_addr *pfx,
				    स्थिर काष्ठा in6_addr *addr,
				    पूर्णांक plen)
अणु
	/* caller must guarantee 0 <= plen <= 128 */
	पूर्णांक o = plen >> 3,
	    b = plen & 0x7;

	स_रखो(pfx->s6_addr, 0, माप(pfx->s6_addr));
	स_नकल(pfx->s6_addr, addr, o);
	अगर (b != 0)
		pfx->s6_addr[o] = addr->s6_addr[o] & (0xff00 >> b);
पूर्ण

अटल अंतरभूत व्योम ipv6_addr_prefix_copy(काष्ठा in6_addr *addr,
					 स्थिर काष्ठा in6_addr *pfx,
					 पूर्णांक plen)
अणु
	/* caller must guarantee 0 <= plen <= 128 */
	पूर्णांक o = plen >> 3,
	    b = plen & 0x7;

	स_नकल(addr->s6_addr, pfx, o);
	अगर (b != 0) अणु
		addr->s6_addr[o] &= ~(0xff00 >> b);
		addr->s6_addr[o] |= (pfx->s6_addr[o] & (0xff00 >> b));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __ipv6_addr_set_half(__be32 *addr,
					__be32 wh, __be32 wl)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
#अगर defined(__BIG_ENDIAN)
	अगर (__builtin_स्थिरant_p(wh) && __builtin_स्थिरant_p(wl)) अणु
		*(__क्रमce u64 *)addr = ((__क्रमce u64)(wh) << 32 | (__क्रमce u64)(wl));
		वापस;
	पूर्ण
#या_अगर defined(__LITTLE_ENDIAN)
	अगर (__builtin_स्थिरant_p(wl) && __builtin_स्थिरant_p(wh)) अणु
		*(__क्रमce u64 *)addr = ((__क्रमce u64)(wl) << 32 | (__क्रमce u64)(wh));
		वापस;
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
	addr[0] = wh;
	addr[1] = wl;
पूर्ण

अटल अंतरभूत व्योम ipv6_addr_set(काष्ठा in6_addr *addr,
				     __be32 w1, __be32 w2,
				     __be32 w3, __be32 w4)
अणु
	__ipv6_addr_set_half(&addr->s6_addr32[0], w1, w2);
	__ipv6_addr_set_half(&addr->s6_addr32[2], w3, w4);
पूर्ण

अटल अंतरभूत bool ipv6_addr_equal(स्थिर काष्ठा in6_addr *a1,
				   स्थिर काष्ठा in6_addr *a2)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	स्थिर अचिन्हित दीर्घ *ul1 = (स्थिर अचिन्हित दीर्घ *)a1;
	स्थिर अचिन्हित दीर्घ *ul2 = (स्थिर अचिन्हित दीर्घ *)a2;

	वापस ((ul1[0] ^ ul2[0]) | (ul1[1] ^ ul2[1])) == 0UL;
#अन्यथा
	वापस ((a1->s6_addr32[0] ^ a2->s6_addr32[0]) |
		(a1->s6_addr32[1] ^ a2->s6_addr32[1]) |
		(a1->s6_addr32[2] ^ a2->s6_addr32[2]) |
		(a1->s6_addr32[3] ^ a2->s6_addr32[3])) == 0;
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
अटल अंतरभूत bool __ipv6_prefix_equal64_half(स्थिर __be64 *a1,
					      स्थिर __be64 *a2,
					      अचिन्हित पूर्णांक len)
अणु
	अगर (len && ((*a1 ^ *a2) & cpu_to_be64((~0UL) << (64 - len))))
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool ipv6_prefix_equal(स्थिर काष्ठा in6_addr *addr1,
				     स्थिर काष्ठा in6_addr *addr2,
				     अचिन्हित पूर्णांक prefixlen)
अणु
	स्थिर __be64 *a1 = (स्थिर __be64 *)addr1;
	स्थिर __be64 *a2 = (स्थिर __be64 *)addr2;

	अगर (prefixlen >= 64) अणु
		अगर (a1[0] ^ a2[0])
			वापस false;
		वापस __ipv6_prefix_equal64_half(a1 + 1, a2 + 1, prefixlen - 64);
	पूर्ण
	वापस __ipv6_prefix_equal64_half(a1, a2, prefixlen);
पूर्ण
#अन्यथा
अटल अंतरभूत bool ipv6_prefix_equal(स्थिर काष्ठा in6_addr *addr1,
				     स्थिर काष्ठा in6_addr *addr2,
				     अचिन्हित पूर्णांक prefixlen)
अणु
	स्थिर __be32 *a1 = addr1->s6_addr32;
	स्थिर __be32 *a2 = addr2->s6_addr32;
	अचिन्हित पूर्णांक pdw, pbi;

	/* check complete u32 in prefix */
	pdw = prefixlen >> 5;
	अगर (pdw && स_भेद(a1, a2, pdw << 2))
		वापस false;

	/* check incomplete u32 in prefix */
	pbi = prefixlen & 0x1f;
	अगर (pbi && ((a1[pdw] ^ a2[pdw]) & htonl((0xffffffff) << (32 - pbi))))
		वापस false;

	वापस true;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool ipv6_addr_any(स्थिर काष्ठा in6_addr *a)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	स्थिर अचिन्हित दीर्घ *ul = (स्थिर अचिन्हित दीर्घ *)a;

	वापस (ul[0] | ul[1]) == 0UL;
#अन्यथा
	वापस (a->s6_addr32[0] | a->s6_addr32[1] |
		a->s6_addr32[2] | a->s6_addr32[3]) == 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u32 ipv6_addr_hash(स्थिर काष्ठा in6_addr *a)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	स्थिर अचिन्हित दीर्घ *ul = (स्थिर अचिन्हित दीर्घ *)a;
	अचिन्हित दीर्घ x = ul[0] ^ ul[1];

	वापस (u32)(x ^ (x >> 32));
#अन्यथा
	वापस (__क्रमce u32)(a->s6_addr32[0] ^ a->s6_addr32[1] ^
			     a->s6_addr32[2] ^ a->s6_addr32[3]);
#पूर्ण_अगर
पूर्ण

/* more secured version of ipv6_addr_hash() */
अटल अंतरभूत u32 __ipv6_addr_jhash(स्थिर काष्ठा in6_addr *a, स्थिर u32 initval)
अणु
	u32 v = (__क्रमce u32)a->s6_addr32[0] ^ (__क्रमce u32)a->s6_addr32[1];

	वापस jhash_3words(v,
			    (__क्रमce u32)a->s6_addr32[2],
			    (__क्रमce u32)a->s6_addr32[3],
			    initval);
पूर्ण

अटल अंतरभूत bool ipv6_addr_loopback(स्थिर काष्ठा in6_addr *a)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	स्थिर __be64 *be = (स्थिर __be64 *)a;

	वापस (be[0] | (be[1] ^ cpu_to_be64(1))) == 0UL;
#अन्यथा
	वापस (a->s6_addr32[0] | a->s6_addr32[1] |
		a->s6_addr32[2] | (a->s6_addr32[3] ^ cpu_to_be32(1))) == 0;
#पूर्ण_अगर
पूर्ण

/*
 * Note that we must __क्रमce cast these to अचिन्हित दीर्घ to make sparse happy,
 * since all of the endian-annotated types are fixed size regardless of arch.
 */
अटल अंतरभूत bool ipv6_addr_v4mapped(स्थिर काष्ठा in6_addr *a)
अणु
	वापस (
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
		*(अचिन्हित दीर्घ *)a |
#अन्यथा
		(__क्रमce अचिन्हित दीर्घ)(a->s6_addr32[0] | a->s6_addr32[1]) |
#पूर्ण_अगर
		(__क्रमce अचिन्हित दीर्घ)(a->s6_addr32[2] ^
					cpu_to_be32(0x0000ffff))) == 0UL;
पूर्ण

अटल अंतरभूत bool ipv6_addr_v4mapped_loopback(स्थिर काष्ठा in6_addr *a)
अणु
	वापस ipv6_addr_v4mapped(a) && ipv4_is_loopback(a->s6_addr32[3]);
पूर्ण

अटल अंतरभूत u32 ipv6_portaddr_hash(स्थिर काष्ठा net *net,
				     स्थिर काष्ठा in6_addr *addr6,
				     अचिन्हित पूर्णांक port)
अणु
	अचिन्हित पूर्णांक hash, mix = net_hash_mix(net);

	अगर (ipv6_addr_any(addr6))
		hash = jhash_1word(0, mix);
	अन्यथा अगर (ipv6_addr_v4mapped(addr6))
		hash = jhash_1word((__क्रमce u32)addr6->s6_addr32[3], mix);
	अन्यथा
		hash = jhash2((__क्रमce u32 *)addr6->s6_addr32, 4, mix);

	वापस hash ^ port;
पूर्ण

/*
 * Check क्रम a RFC 4843 ORCHID address
 * (Overlay Routable Cryptographic Hash Identअगरiers)
 */
अटल अंतरभूत bool ipv6_addr_orchid(स्थिर काष्ठा in6_addr *a)
अणु
	वापस (a->s6_addr32[0] & htonl(0xfffffff0)) == htonl(0x20010010);
पूर्ण

अटल अंतरभूत bool ipv6_addr_is_multicast(स्थिर काष्ठा in6_addr *addr)
अणु
	वापस (addr->s6_addr32[0] & htonl(0xFF000000)) == htonl(0xFF000000);
पूर्ण

अटल अंतरभूत व्योम ipv6_addr_set_v4mapped(स्थिर __be32 addr,
					  काष्ठा in6_addr *v4mapped)
अणु
	ipv6_addr_set(v4mapped,
			0, 0,
			htonl(0x0000FFFF),
			addr);
पूर्ण

/*
 * find the first dअगरferent bit between two addresses
 * length of address must be a multiple of 32bits
 */
अटल अंतरभूत पूर्णांक __ipv6_addr_dअगरf32(स्थिर व्योम *token1, स्थिर व्योम *token2, पूर्णांक addrlen)
अणु
	स्थिर __be32 *a1 = token1, *a2 = token2;
	पूर्णांक i;

	addrlen >>= 2;

	क्रम (i = 0; i < addrlen; i++) अणु
		__be32 xb = a1[i] ^ a2[i];
		अगर (xb)
			वापस i * 32 + 31 - __fls(ntohl(xb));
	पूर्ण

	/*
	 *	we should *never* get to this poपूर्णांक since that
	 *	would mean the addrs are equal
	 *
	 *	However, we करो get to it 8) And exacly, when
	 *	addresses are equal 8)
	 *
	 *	ip route add 1111::/128 via ...
	 *	ip route add 1111::/64 via ...
	 *	and we are here.
	 *
	 *	Ideally, this function should stop comparison
	 *	at prefix length. It करोes not, but it is still OK,
	 *	अगर वापसed value is greater than prefix length.
	 *					--ANK (980803)
	 */
	वापस addrlen << 5;
पूर्ण

#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
अटल अंतरभूत पूर्णांक __ipv6_addr_dअगरf64(स्थिर व्योम *token1, स्थिर व्योम *token2, पूर्णांक addrlen)
अणु
	स्थिर __be64 *a1 = token1, *a2 = token2;
	पूर्णांक i;

	addrlen >>= 3;

	क्रम (i = 0; i < addrlen; i++) अणु
		__be64 xb = a1[i] ^ a2[i];
		अगर (xb)
			वापस i * 64 + 63 - __fls(be64_to_cpu(xb));
	पूर्ण

	वापस addrlen << 6;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक __ipv6_addr_dअगरf(स्थिर व्योम *token1, स्थिर व्योम *token2, पूर्णांक addrlen)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	अगर (__builtin_स्थिरant_p(addrlen) && !(addrlen & 7))
		वापस __ipv6_addr_dअगरf64(token1, token2, addrlen);
#पूर्ण_अगर
	वापस __ipv6_addr_dअगरf32(token1, token2, addrlen);
पूर्ण

अटल अंतरभूत पूर्णांक ipv6_addr_dअगरf(स्थिर काष्ठा in6_addr *a1, स्थिर काष्ठा in6_addr *a2)
अणु
	वापस __ipv6_addr_dअगरf(a1, a2, माप(काष्ठा in6_addr));
पूर्ण

__be32 ipv6_select_ident(काष्ठा net *net,
			 स्थिर काष्ठा in6_addr *daddr,
			 स्थिर काष्ठा in6_addr *saddr);
__be32 ipv6_proxy_select_ident(काष्ठा net *net, काष्ठा sk_buff *skb);

पूर्णांक ip6_dst_hoplimit(काष्ठा dst_entry *dst);

अटल अंतरभूत पूर्णांक ip6_sk_dst_hoplimit(काष्ठा ipv6_pinfo *np, काष्ठा flowi6 *fl6,
				      काष्ठा dst_entry *dst)
अणु
	पूर्णांक hlimit;

	अगर (ipv6_addr_is_multicast(&fl6->daddr))
		hlimit = np->mcast_hops;
	अन्यथा
		hlimit = np->hop_limit;
	अगर (hlimit < 0)
		hlimit = ip6_dst_hoplimit(dst);
	वापस hlimit;
पूर्ण

/* copy IPv6 saddr & daddr to flow_keys, possibly using 64bit load/store
 * Equivalent to :	flow->v6addrs.src = iph->saddr;
 *			flow->v6addrs.dst = iph->daddr;
 */
अटल अंतरभूत व्योम iph_to_flow_copy_v6addrs(काष्ठा flow_keys *flow,
					    स्थिर काष्ठा ipv6hdr *iph)
अणु
	BUILD_BUG_ON(दुरत्व(typeof(flow->addrs), v6addrs.dst) !=
		     दुरत्व(typeof(flow->addrs), v6addrs.src) +
		     माप(flow->addrs.v6addrs.src));
	स_नकल(&flow->addrs.v6addrs, &iph->saddr, माप(flow->addrs.v6addrs));
	flow->control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)

अटल अंतरभूत bool ipv6_can_nonlocal_bind(काष्ठा net *net,
					  काष्ठा inet_sock *inet)
अणु
	वापस net->ipv6.sysctl.ip_nonlocal_bind ||
		inet->मुक्तbind || inet->transparent;
पूर्ण

/* Sysctl settings क्रम net ipv6.स्वतः_flowlabels */
#घोषणा IP6_AUTO_FLOW_LABEL_OFF		0
#घोषणा IP6_AUTO_FLOW_LABEL_OPTOUT	1
#घोषणा IP6_AUTO_FLOW_LABEL_OPTIN	2
#घोषणा IP6_AUTO_FLOW_LABEL_FORCED	3

#घोषणा IP6_AUTO_FLOW_LABEL_MAX		IP6_AUTO_FLOW_LABEL_FORCED

#घोषणा IP6_DEFAULT_AUTO_FLOW_LABELS	IP6_AUTO_FLOW_LABEL_OPTOUT

अटल अंतरभूत __be32 ip6_make_flowlabel(काष्ठा net *net, काष्ठा sk_buff *skb,
					__be32 flowlabel, bool स्वतःlabel,
					काष्ठा flowi6 *fl6)
अणु
	u32 hash;

	/* @flowlabel may include more than a flow label, eg, the traffic class.
	 * Here we want only the flow label value.
	 */
	flowlabel &= IPV6_FLOWLABEL_MASK;

	अगर (flowlabel ||
	    net->ipv6.sysctl.स्वतः_flowlabels == IP6_AUTO_FLOW_LABEL_OFF ||
	    (!स्वतःlabel &&
	     net->ipv6.sysctl.स्वतः_flowlabels != IP6_AUTO_FLOW_LABEL_FORCED))
		वापस flowlabel;

	hash = skb_get_hash_flowi6(skb, fl6);

	/* Since this is being sent on the wire obfuscate hash a bit
	 * to minimize possbility that any useful inक्रमmation to an
	 * attacker is leaked. Only lower 20 bits are relevant.
	 */
	hash = rol32(hash, 16);

	flowlabel = (__क्रमce __be32)hash & IPV6_FLOWLABEL_MASK;

	अगर (net->ipv6.sysctl.flowlabel_state_ranges)
		flowlabel |= IPV6_FLOWLABEL_STATELESS_FLAG;

	वापस flowlabel;
पूर्ण

अटल अंतरभूत पूर्णांक ip6_शेष_np_स्वतःlabel(काष्ठा net *net)
अणु
	चयन (net->ipv6.sysctl.स्वतः_flowlabels) अणु
	हाल IP6_AUTO_FLOW_LABEL_OFF:
	हाल IP6_AUTO_FLOW_LABEL_OPTIN:
	शेष:
		वापस 0;
	हाल IP6_AUTO_FLOW_LABEL_OPTOUT:
	हाल IP6_AUTO_FLOW_LABEL_FORCED:
		वापस 1;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत __be32 ip6_make_flowlabel(काष्ठा net *net, काष्ठा sk_buff *skb,
					__be32 flowlabel, bool स्वतःlabel,
					काष्ठा flowi6 *fl6)
अणु
	वापस flowlabel;
पूर्ण
अटल अंतरभूत पूर्णांक ip6_शेष_np_स्वतःlabel(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत पूर्णांक ip6_multipath_hash_policy(स्थिर काष्ठा net *net)
अणु
	वापस net->ipv6.sysctl.multipath_hash_policy;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक ip6_multipath_hash_policy(स्थिर काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 *	Header manipulation
 */
अटल अंतरभूत व्योम ip6_flow_hdr(काष्ठा ipv6hdr *hdr, अचिन्हित पूर्णांक tclass,
				__be32 flowlabel)
अणु
	*(__be32 *)hdr = htonl(0x60000000 | (tclass << 20)) | flowlabel;
पूर्ण

अटल अंतरभूत __be32 ip6_flowinfo(स्थिर काष्ठा ipv6hdr *hdr)
अणु
	वापस *(__be32 *)hdr & IPV6_FLOWINFO_MASK;
पूर्ण

अटल अंतरभूत __be32 ip6_flowlabel(स्थिर काष्ठा ipv6hdr *hdr)
अणु
	वापस *(__be32 *)hdr & IPV6_FLOWLABEL_MASK;
पूर्ण

अटल अंतरभूत u8 ip6_tclass(__be32 flowinfo)
अणु
	वापस ntohl(flowinfo & IPV6_TCLASS_MASK) >> IPV6_TCLASS_SHIFT;
पूर्ण

अटल अंतरभूत __be32 ip6_make_flowinfo(अचिन्हित पूर्णांक tclass, __be32 flowlabel)
अणु
	वापस htonl(tclass << IPV6_TCLASS_SHIFT) | flowlabel;
पूर्ण

अटल अंतरभूत __be32 flowi6_get_flowlabel(स्थिर काष्ठा flowi6 *fl6)
अणु
	वापस fl6->flowlabel & IPV6_FLOWLABEL_MASK;
पूर्ण

/*
 *	Prototypes exported by ipv6
 */

/*
 *	rcv function (called from netdevice level)
 */

पूर्णांक ipv6_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
	     काष्ठा packet_type *pt, काष्ठा net_device *orig_dev);
व्योम ipv6_list_rcv(काष्ठा list_head *head, काष्ठा packet_type *pt,
		   काष्ठा net_device *orig_dev);

पूर्णांक ip6_rcv_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);

/*
 *	upper-layer output functions
 */
पूर्णांक ip6_xmit(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi6 *fl6,
	     __u32 mark, काष्ठा ipv6_txoptions *opt, पूर्णांक tclass, u32 priority);

पूर्णांक ip6_find_1stfragopt(काष्ठा sk_buff *skb, u8 **nexthdr);

पूर्णांक ip6_append_data(काष्ठा sock *sk,
		    पूर्णांक getfrag(व्योम *from, अक्षर *to, पूर्णांक offset, पूर्णांक len,
				पूर्णांक odd, काष्ठा sk_buff *skb),
		    व्योम *from, पूर्णांक length, पूर्णांक transhdrlen,
		    काष्ठा ipcm6_cookie *ipc6, काष्ठा flowi6 *fl6,
		    काष्ठा rt6_info *rt, अचिन्हित पूर्णांक flags);

पूर्णांक ip6_push_pending_frames(काष्ठा sock *sk);

व्योम ip6_flush_pending_frames(काष्ठा sock *sk);

पूर्णांक ip6_send_skb(काष्ठा sk_buff *skb);

काष्ठा sk_buff *__ip6_make_skb(काष्ठा sock *sk, काष्ठा sk_buff_head *queue,
			       काष्ठा inet_cork_full *cork,
			       काष्ठा inet6_cork *v6_cork);
काष्ठा sk_buff *ip6_make_skb(काष्ठा sock *sk,
			     पूर्णांक getfrag(व्योम *from, अक्षर *to, पूर्णांक offset,
					 पूर्णांक len, पूर्णांक odd, काष्ठा sk_buff *skb),
			     व्योम *from, पूर्णांक length, पूर्णांक transhdrlen,
			     काष्ठा ipcm6_cookie *ipc6, काष्ठा flowi6 *fl6,
			     काष्ठा rt6_info *rt, अचिन्हित पूर्णांक flags,
			     काष्ठा inet_cork_full *cork);

अटल अंतरभूत काष्ठा sk_buff *ip6_finish_skb(काष्ठा sock *sk)
अणु
	वापस __ip6_make_skb(sk, &sk->sk_ग_लिखो_queue, &inet_sk(sk)->cork,
			      &inet6_sk(sk)->cork);
पूर्ण

पूर्णांक ip6_dst_lookup(काष्ठा net *net, काष्ठा sock *sk, काष्ठा dst_entry **dst,
		   काष्ठा flowi6 *fl6);
काष्ठा dst_entry *ip6_dst_lookup_flow(काष्ठा net *net, स्थिर काष्ठा sock *sk, काष्ठा flowi6 *fl6,
				      स्थिर काष्ठा in6_addr *final_dst);
काष्ठा dst_entry *ip6_sk_dst_lookup_flow(काष्ठा sock *sk, काष्ठा flowi6 *fl6,
					 स्थिर काष्ठा in6_addr *final_dst,
					 bool connected);
काष्ठा dst_entry *ip6_dst_lookup_tunnel(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev,
					काष्ठा net *net, काष्ठा socket *sock,
					काष्ठा in6_addr *saddr,
					स्थिर काष्ठा ip_tunnel_info *info,
					u8 protocol, bool use_cache);
काष्ठा dst_entry *ip6_blackhole_route(काष्ठा net *net,
				      काष्ठा dst_entry *orig_dst);

/*
 *	skb processing functions
 */

पूर्णांक ip6_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक ip6_क्रमward(काष्ठा sk_buff *skb);
पूर्णांक ip6_input(काष्ठा sk_buff *skb);
पूर्णांक ip6_mc_input(काष्ठा sk_buff *skb);
व्योम ip6_protocol_deliver_rcu(काष्ठा net *net, काष्ठा sk_buff *skb, पूर्णांक nexthdr,
			      bool have_final);

पूर्णांक __ip6_local_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक ip6_local_out(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);

/*
 *	Extension header (options) processing
 */

व्योम ipv6_push_nfrag_opts(काष्ठा sk_buff *skb, काष्ठा ipv6_txoptions *opt,
			  u8 *proto, काष्ठा in6_addr **daddr_p,
			  काष्ठा in6_addr *saddr);
व्योम ipv6_push_frag_opts(काष्ठा sk_buff *skb, काष्ठा ipv6_txoptions *opt,
			 u8 *proto);

पूर्णांक ipv6_skip_exthdr(स्थिर काष्ठा sk_buff *, पूर्णांक start, u8 *nexthdrp,
		     __be16 *frag_offp);

bool ipv6_ext_hdr(u8 nexthdr);

क्रमागत अणु
	IP6_FH_F_FRAG		= (1 << 0),
	IP6_FH_F_AUTH		= (1 << 1),
	IP6_FH_F_SKIP_RH	= (1 << 2),
पूर्ण;

/* find specअगरied header and get offset to it */
पूर्णांक ipv6_find_hdr(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक *offset, पूर्णांक target,
		  अचिन्हित लघु *fragoff, पूर्णांक *fragflg);

पूर्णांक ipv6_find_tlv(स्थिर काष्ठा sk_buff *skb, पूर्णांक offset, पूर्णांक type);

काष्ठा in6_addr *fl6_update_dst(काष्ठा flowi6 *fl6,
				स्थिर काष्ठा ipv6_txoptions *opt,
				काष्ठा in6_addr *orig);

/*
 *	socket options (ipv6_sockglue.c)
 */

पूर्णांक ipv6_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		    अचिन्हित पूर्णांक optlen);
पूर्णांक ipv6_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		    अक्षर __user *optval, पूर्णांक __user *optlen);

पूर्णांक __ip6_datagram_connect(काष्ठा sock *sk, काष्ठा sockaddr *addr,
			   पूर्णांक addr_len);
पूर्णांक ip6_datagram_connect(काष्ठा sock *sk, काष्ठा sockaddr *addr, पूर्णांक addr_len);
पूर्णांक ip6_datagram_connect_v6_only(काष्ठा sock *sk, काष्ठा sockaddr *addr,
				 पूर्णांक addr_len);
पूर्णांक ip6_datagram_dst_update(काष्ठा sock *sk, bool fix_sk_saddr);
व्योम ip6_datagram_release_cb(काष्ठा sock *sk);

पूर्णांक ipv6_recv_error(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len,
		    पूर्णांक *addr_len);
पूर्णांक ipv6_recv_rxpmtu(काष्ठा sock *sk, काष्ठा msghdr *msg, पूर्णांक len,
		     पूर्णांक *addr_len);
व्योम ipv6_icmp_error(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक err, __be16 port,
		     u32 info, u8 *payload);
व्योम ipv6_local_error(काष्ठा sock *sk, पूर्णांक err, काष्ठा flowi6 *fl6, u32 info);
व्योम ipv6_local_rxpmtu(काष्ठा sock *sk, काष्ठा flowi6 *fl6, u32 mtu);

पूर्णांक inet6_release(काष्ठा socket *sock);
पूर्णांक inet6_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len);
पूर्णांक inet6_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
		  पूर्णांक peer);
पूर्णांक inet6_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक inet6_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
		अचिन्हित दीर्घ arg);

पूर्णांक inet6_hash_connect(काष्ठा inet_समयरुको_death_row *death_row,
			      काष्ठा sock *sk);
पूर्णांक inet6_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size);
पूर्णांक inet6_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार size,
		  पूर्णांक flags);

/*
 * reassembly.c
 */
बाह्य स्थिर काष्ठा proto_ops inet6_stream_ops;
बाह्य स्थिर काष्ठा proto_ops inet6_dgram_ops;
बाह्य स्थिर काष्ठा proto_ops inet6_sockraw_ops;

काष्ठा group_source_req;
काष्ठा group_filter;

पूर्णांक ip6_mc_source(पूर्णांक add, पूर्णांक omode, काष्ठा sock *sk,
		  काष्ठा group_source_req *pgsr);
पूर्णांक ip6_mc_msfilter(काष्ठा sock *sk, काष्ठा group_filter *gsf,
		  काष्ठा sockaddr_storage *list);
पूर्णांक ip6_mc_msfget(काष्ठा sock *sk, काष्ठा group_filter *gsf,
		  काष्ठा sockaddr_storage __user *p);

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक ac6_proc_init(काष्ठा net *net);
व्योम ac6_proc_निकास(काष्ठा net *net);
पूर्णांक raw6_proc_init(व्योम);
व्योम raw6_proc_निकास(व्योम);
पूर्णांक tcp6_proc_init(काष्ठा net *net);
व्योम tcp6_proc_निकास(काष्ठा net *net);
पूर्णांक udp6_proc_init(काष्ठा net *net);
व्योम udp6_proc_निकास(काष्ठा net *net);
पूर्णांक udplite6_proc_init(व्योम);
व्योम udplite6_proc_निकास(व्योम);
पूर्णांक ipv6_misc_proc_init(व्योम);
व्योम ipv6_misc_proc_निकास(व्योम);
पूर्णांक snmp6_रेजिस्टर_dev(काष्ठा inet6_dev *idev);
पूर्णांक snmp6_unरेजिस्टर_dev(काष्ठा inet6_dev *idev);

#अन्यथा
अटल अंतरभूत पूर्णांक ac6_proc_init(काष्ठा net *net) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ac6_proc_निकास(काष्ठा net *net) अणु पूर्ण
अटल अंतरभूत पूर्णांक snmp6_रेजिस्टर_dev(काष्ठा inet6_dev *idev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक snmp6_unरेजिस्टर_dev(काष्ठा inet6_dev *idev) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSCTL
काष्ठा ctl_table *ipv6_icmp_sysctl_init(काष्ठा net *net);
काष्ठा ctl_table *ipv6_route_sysctl_init(काष्ठा net *net);
पूर्णांक ipv6_sysctl_रेजिस्टर(व्योम);
व्योम ipv6_sysctl_unरेजिस्टर(व्योम);
#पूर्ण_अगर

पूर्णांक ipv6_sock_mc_join(काष्ठा sock *sk, पूर्णांक अगरindex,
		      स्थिर काष्ठा in6_addr *addr);
पूर्णांक ipv6_sock_mc_join_ssm(काष्ठा sock *sk, पूर्णांक अगरindex,
			  स्थिर काष्ठा in6_addr *addr, अचिन्हित पूर्णांक mode);
पूर्णांक ipv6_sock_mc_drop(काष्ठा sock *sk, पूर्णांक अगरindex,
		      स्थिर काष्ठा in6_addr *addr);

अटल अंतरभूत पूर्णांक ip6_sock_set_v6only(काष्ठा sock *sk)
अणु
	अगर (inet_sk(sk)->inet_num)
		वापस -EINVAL;
	lock_sock(sk);
	sk->sk_ipv6only = true;
	release_sock(sk);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ip6_sock_set_recverr(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	inet6_sk(sk)->recverr = true;
	release_sock(sk);
पूर्ण

अटल अंतरभूत पूर्णांक __ip6_sock_set_addr_preferences(काष्ठा sock *sk, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक pref = 0;
	अचिन्हित पूर्णांक prefmask = ~0;

	/* check PUBLIC/TMP/PUBTMP_DEFAULT conflicts */
	चयन (val & (IPV6_PREFER_SRC_PUBLIC |
		       IPV6_PREFER_SRC_TMP |
		       IPV6_PREFER_SRC_PUBTMP_DEFAULT)) अणु
	हाल IPV6_PREFER_SRC_PUBLIC:
		pref |= IPV6_PREFER_SRC_PUBLIC;
		prefmask &= ~(IPV6_PREFER_SRC_PUBLIC |
			      IPV6_PREFER_SRC_TMP);
		अवरोध;
	हाल IPV6_PREFER_SRC_TMP:
		pref |= IPV6_PREFER_SRC_TMP;
		prefmask &= ~(IPV6_PREFER_SRC_PUBLIC |
			      IPV6_PREFER_SRC_TMP);
		अवरोध;
	हाल IPV6_PREFER_SRC_PUBTMP_DEFAULT:
		prefmask &= ~(IPV6_PREFER_SRC_PUBLIC |
			      IPV6_PREFER_SRC_TMP);
		अवरोध;
	हाल 0:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* check HOME/COA conflicts */
	चयन (val & (IPV6_PREFER_SRC_HOME | IPV6_PREFER_SRC_COA)) अणु
	हाल IPV6_PREFER_SRC_HOME:
		prefmask &= ~IPV6_PREFER_SRC_COA;
		अवरोध;
	हाल IPV6_PREFER_SRC_COA:
		pref |= IPV6_PREFER_SRC_COA;
		अवरोध;
	हाल 0:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* check CGA/NONCGA conflicts */
	चयन (val & (IPV6_PREFER_SRC_CGA|IPV6_PREFER_SRC_NONCGA)) अणु
	हाल IPV6_PREFER_SRC_CGA:
	हाल IPV6_PREFER_SRC_NONCGA:
	हाल 0:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	inet6_sk(sk)->srcprefs = (inet6_sk(sk)->srcprefs & prefmask) | pref;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ip6_sock_set_addr_preferences(काष्ठा sock *sk, bool val)
अणु
	पूर्णांक ret;

	lock_sock(sk);
	ret = __ip6_sock_set_addr_preferences(sk, val);
	release_sock(sk);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम ip6_sock_set_recvpktinfo(काष्ठा sock *sk)
अणु
	lock_sock(sk);
	inet6_sk(sk)->rxopt.bits.rxinfo = true;
	release_sock(sk);
पूर्ण

#पूर्ण_अगर /* _NET_IPV6_H */
