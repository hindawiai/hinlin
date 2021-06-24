<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	inet6 पूर्णांकerface/address list definitions
 *	Linux INET6 implementation 
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>	
 */

#अगर_अघोषित _NET_IF_INET6_H
#घोषणा _NET_IF_INET6_H

#समावेश <net/snmp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/refcount.h>

/* inet6_dev.अगर_flags */

#घोषणा IF_RA_OTHERCONF	0x80
#घोषणा IF_RA_MANAGED	0x40
#घोषणा IF_RA_RCVD	0x20
#घोषणा IF_RS_SENT	0x10
#घोषणा IF_READY	0x80000000

/* prefix flags */
#घोषणा IF_PREFIX_ONLINK	0x01
#घोषणा IF_PREFIX_AUTOCONF	0x02

क्रमागत अणु
	INET6_IFADDR_STATE_PREDAD,
	INET6_IFADDR_STATE_DAD,
	INET6_IFADDR_STATE_POSTDAD,
	INET6_IFADDR_STATE_ERRDAD,
	INET6_IFADDR_STATE_DEAD,
पूर्ण;

काष्ठा inet6_अगरaddr अणु
	काष्ठा in6_addr		addr;
	__u32			prefix_len;
	__u32			rt_priority;

	/* In seconds, relative to tstamp. Expiry is at tstamp + HZ * lft. */
	__u32			valid_lft;
	__u32			prefered_lft;
	refcount_t		refcnt;
	spinlock_t		lock;

	पूर्णांक			state;

	__u32			flags;
	__u8			dad_probes;
	__u8			stable_privacy_retry;

	__u16			scope;
	__u64			dad_nonce;

	अचिन्हित दीर्घ		cstamp;	/* created बारtamp */
	अचिन्हित दीर्घ		tstamp; /* updated बारtamp */

	काष्ठा delayed_work	dad_work;

	काष्ठा inet6_dev	*idev;
	काष्ठा fib6_info	*rt;

	काष्ठा hlist_node	addr_lst;
	काष्ठा list_head	अगर_list;

	काष्ठा list_head	पंचांगp_list;
	काष्ठा inet6_अगरaddr	*अगरpub;
	पूर्णांक			regen_count;

	bool			tokenized;

	काष्ठा rcu_head		rcu;
	काष्ठा in6_addr		peer_addr;
पूर्ण;

काष्ठा ip6_sf_socklist अणु
	अचिन्हित पूर्णांक		sl_max;
	अचिन्हित पूर्णांक		sl_count;
	काष्ठा rcu_head		rcu;
	काष्ठा in6_addr		sl_addr[];
पूर्ण;

#घोषणा IP6_SFLSIZE(count)	(माप(काष्ठा ip6_sf_socklist) + \
	(count) * माप(काष्ठा in6_addr))

#घोषणा IP6_SFBLOCK	10	/* allocate this many at once */

काष्ठा ipv6_mc_socklist अणु
	काष्ठा in6_addr		addr;
	पूर्णांक			अगरindex;
	अचिन्हित पूर्णांक		sभ_शेषe;		/* MCAST_अणुINCLUDE,EXCLUDEपूर्ण */
	काष्ठा ipv6_mc_socklist __rcu *next;
	काष्ठा ip6_sf_socklist	__rcu *sflist;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा ip6_sf_list अणु
	काष्ठा ip6_sf_list __rcu *sf_next;
	काष्ठा in6_addr		sf_addr;
	अचिन्हित दीर्घ		sf_count[2];	/* include/exclude counts */
	अचिन्हित अक्षर		sf_gsresp;	/* include in g & s response? */
	अचिन्हित अक्षर		sf_oldin;	/* change state */
	अचिन्हित अक्षर		sf_crcount;	/* retrans. left to send */
	काष्ठा rcu_head		rcu;
पूर्ण;

#घोषणा MAF_TIMER_RUNNING	0x01
#घोषणा MAF_LAST_REPORTER	0x02
#घोषणा MAF_LOADED		0x04
#घोषणा MAF_NOREPORT		0x08
#घोषणा MAF_GSQUERY		0x10

काष्ठा अगरmcaddr6 अणु
	काष्ठा in6_addr		mca_addr;
	काष्ठा inet6_dev	*idev;
	काष्ठा अगरmcaddr6	__rcu *next;
	काष्ठा ip6_sf_list	__rcu *mca_sources;
	काष्ठा ip6_sf_list	__rcu *mca_tomb;
	अचिन्हित पूर्णांक		mca_sभ_शेषe;
	अचिन्हित अक्षर		mca_crcount;
	अचिन्हित दीर्घ		mca_sfcount[2];
	काष्ठा delayed_work	mca_work;
	अचिन्हित पूर्णांक		mca_flags;
	पूर्णांक			mca_users;
	refcount_t		mca_refcnt;
	अचिन्हित दीर्घ		mca_cstamp;
	अचिन्हित दीर्घ		mca_tstamp;
	काष्ठा rcu_head		rcu;
पूर्ण;

/* Anycast stuff */

काष्ठा ipv6_ac_socklist अणु
	काष्ठा in6_addr		acl_addr;
	पूर्णांक			acl_अगरindex;
	काष्ठा ipv6_ac_socklist *acl_next;
पूर्ण;

काष्ठा अगरacaddr6 अणु
	काष्ठा in6_addr		aca_addr;
	काष्ठा fib6_info	*aca_rt;
	काष्ठा अगरacaddr6	*aca_next;
	काष्ठा hlist_node	aca_addr_lst;
	पूर्णांक			aca_users;
	refcount_t		aca_refcnt;
	अचिन्हित दीर्घ		aca_cstamp;
	अचिन्हित दीर्घ		aca_tstamp;
	काष्ठा rcu_head		rcu;
पूर्ण;

#घोषणा	IFA_HOST	IPV6_ADDR_LOOPBACK
#घोषणा	IFA_LINK	IPV6_ADDR_LINKLOCAL
#घोषणा	IFA_SITE	IPV6_ADDR_SITELOCAL

काष्ठा ipv6_devstat अणु
	काष्ठा proc_dir_entry	*proc_dir_entry;
	DEFINE_SNMP_STAT(काष्ठा ipstats_mib, ipv6);
	DEFINE_SNMP_STAT_ATOMIC(काष्ठा icmpv6_mib_device, icmpv6dev);
	DEFINE_SNMP_STAT_ATOMIC(काष्ठा icmpv6msg_mib_device, icmpv6msgdev);
पूर्ण;

काष्ठा inet6_dev अणु
	काष्ठा net_device	*dev;

	काष्ठा list_head	addr_list;

	काष्ठा अगरmcaddr6	__rcu *mc_list;
	काष्ठा अगरmcaddr6	__rcu *mc_tomb;

	अचिन्हित अक्षर		mc_qrv;		/* Query Robustness Variable */
	अचिन्हित अक्षर		mc_gq_running;
	अचिन्हित अक्षर		mc_अगरc_count;
	अचिन्हित अक्षर		mc_dad_count;

	अचिन्हित दीर्घ		mc_v1_seen;	/* Max समय we stay in MLDv1 mode */
	अचिन्हित दीर्घ		mc_qi;		/* Query Interval */
	अचिन्हित दीर्घ		mc_qri;		/* Query Response Interval */
	अचिन्हित दीर्घ		mc_maxdelay;

	काष्ठा delayed_work	mc_gq_work;	/* general query work */
	काष्ठा delayed_work	mc_अगरc_work;	/* पूर्णांकerface change work */
	काष्ठा delayed_work	mc_dad_work;	/* dad complete mc work */
	काष्ठा delayed_work	mc_query_work;	/* mld query work */
	काष्ठा delayed_work	mc_report_work;	/* mld report work */

	काष्ठा sk_buff_head	mc_query_queue;		/* mld query queue */
	काष्ठा sk_buff_head	mc_report_queue;	/* mld report queue */

	spinlock_t		mc_query_lock;	/* mld query queue lock */
	spinlock_t		mc_report_lock;	/* mld query report lock */
	काष्ठा mutex		mc_lock;	/* mld global lock */

	काष्ठा अगरacaddr6	*ac_list;
	rwlock_t		lock;
	refcount_t		refcnt;
	__u32			अगर_flags;
	पूर्णांक			dead;

	u32			desync_factor;
	काष्ठा list_head	tempaddr_list;

	काष्ठा in6_addr		token;

	काष्ठा neigh_parms	*nd_parms;
	काष्ठा ipv6_devconf	cnf;
	काष्ठा ipv6_devstat	stats;

	काष्ठा समयr_list	rs_समयr;
	__s32			rs_पूर्णांकerval;	/* in jअगरfies */
	__u8			rs_probes;

	अचिन्हित दीर्घ		tstamp; /* ipv6InterfaceTable update बारtamp */
	काष्ठा rcu_head		rcu;
पूर्ण;

अटल अंतरभूत व्योम ipv6_eth_mc_map(स्थिर काष्ठा in6_addr *addr, अक्षर *buf)
अणु
	/*
	 *	+-------+-------+-------+-------+-------+-------+
	 *      |   33  |   33  | DST13 | DST14 | DST15 | DST16 |
	 *      +-------+-------+-------+-------+-------+-------+
	 */

	buf[0]= 0x33;
	buf[1]= 0x33;

	स_नकल(buf + 2, &addr->s6_addr32[3], माप(__u32));
पूर्ण

अटल अंतरभूत व्योम ipv6_arcnet_mc_map(स्थिर काष्ठा in6_addr *addr, अक्षर *buf)
अणु
	buf[0] = 0x00;
पूर्ण

अटल अंतरभूत व्योम ipv6_ib_mc_map(स्थिर काष्ठा in6_addr *addr,
				  स्थिर अचिन्हित अक्षर *broadcast, अक्षर *buf)
अणु
	अचिन्हित अक्षर scope = broadcast[5] & 0xF;

	buf[0]  = 0;		/* Reserved */
	buf[1]  = 0xff;		/* Multicast QPN */
	buf[2]  = 0xff;
	buf[3]  = 0xff;
	buf[4]  = 0xff;
	buf[5]  = 0x10 | scope;	/* scope from broadcast address */
	buf[6]  = 0x60;		/* IPv6 signature */
	buf[7]  = 0x1b;
	buf[8]  = broadcast[8];	/* P_Key */
	buf[9]  = broadcast[9];
	स_नकल(buf + 10, addr->s6_addr + 6, 10);
पूर्ण

अटल अंतरभूत पूर्णांक ipv6_ipgre_mc_map(स्थिर काष्ठा in6_addr *addr,
				    स्थिर अचिन्हित अक्षर *broadcast, अक्षर *buf)
अणु
	अगर ((broadcast[0] | broadcast[1] | broadcast[2] | broadcast[3]) != 0) अणु
		स_नकल(buf, broadcast, 4);
	पूर्ण अन्यथा अणु
		/* v4mapped? */
		अगर ((addr->s6_addr32[0] | addr->s6_addr32[1] |
		     (addr->s6_addr32[2] ^ htonl(0x0000ffff))) != 0)
			वापस -EINVAL;
		स_नकल(buf, &addr->s6_addr32[3], 4);
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर
