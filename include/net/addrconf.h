<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ADDRCONF_H
#घोषणा _ADDRCONF_H

#घोषणा MAX_RTR_SOLICITATIONS		-1		/* unlimited */
#घोषणा RTR_SOLICITATION_INTERVAL	(4*HZ)
#घोषणा RTR_SOLICITATION_MAX_INTERVAL	(3600*HZ)	/* 1 hour */

#घोषणा TEMP_VALID_LIFETIME		(7*86400)
#घोषणा TEMP_PREFERRED_LIFETIME		(86400)
#घोषणा REGEN_MAX_RETRY			(3)
#घोषणा MAX_DESYNC_FACTOR		(600)

#घोषणा ADDR_CHECK_FREQUENCY		(120*HZ)

#घोषणा IPV6_MAX_ADDRESSES		16

#घोषणा ADDRCONF_TIMER_FUZZ_MINUS	(HZ > 50 ? HZ / 50 : 1)
#घोषणा ADDRCONF_TIMER_FUZZ		(HZ / 4)
#घोषणा ADDRCONF_TIMER_FUZZ_MAX		(HZ)

#घोषणा ADDRCONF_NOTIFY_PRIORITY	0

#समावेश <linux/in.h>
#समावेश <linux/in6.h>

काष्ठा prefix_info अणु
	__u8			type;
	__u8			length;
	__u8			prefix_len;

#अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8			onlink : 1,
			 	स्वतःconf : 1,
				reserved : 6;
#या_अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8			reserved : 6,
				स्वतःconf : 1,
				onlink : 1;
#अन्यथा
#त्रुटि "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	__be32			valid;
	__be32			prefered;
	__be32			reserved2;

	काष्ठा in6_addr		prefix;
पूर्ण;

#समावेश <linux/ipv6.h>
#समावेश <linux/netdevice.h>
#समावेश <net/अगर_inet6.h>
#समावेश <net/ipv6.h>

काष्ठा in6_validator_info अणु
	काष्ठा in6_addr		i6vi_addr;
	काष्ठा inet6_dev	*i6vi_dev;
	काष्ठा netlink_ext_ack	*extack;
पूर्ण;

काष्ठा अगरa6_config अणु
	स्थिर काष्ठा in6_addr	*pfx;
	अचिन्हित पूर्णांक		plen;

	स्थिर काष्ठा in6_addr	*peer_pfx;

	u32			rt_priority;
	u32			अगरa_flags;
	u32			preferred_lft;
	u32			valid_lft;
	u16			scope;
पूर्ण;

पूर्णांक addrconf_init(व्योम);
व्योम addrconf_cleanup(व्योम);

पूर्णांक addrconf_add_अगरaddr(काष्ठा net *net, व्योम __user *arg);
पूर्णांक addrconf_del_अगरaddr(काष्ठा net *net, व्योम __user *arg);
पूर्णांक addrconf_set_dstaddr(काष्ठा net *net, व्योम __user *arg);

पूर्णांक ipv6_chk_addr(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
		  स्थिर काष्ठा net_device *dev, पूर्णांक strict);
पूर्णांक ipv6_chk_addr_and_flags(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			    स्थिर काष्ठा net_device *dev, bool skip_dev_check,
			    पूर्णांक strict, u32 banned_flags);

#अगर defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
पूर्णांक ipv6_chk_home_addr(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr);
#पूर्ण_अगर

पूर्णांक ipv6_chk_rpl_srh_loop(काष्ठा net *net, स्थिर काष्ठा in6_addr *segs,
			  अचिन्हित अक्षर nsegs);

bool ipv6_chk_custom_prefix(स्थिर काष्ठा in6_addr *addr,
				   स्थिर अचिन्हित पूर्णांक prefix_len,
				   काष्ठा net_device *dev);

पूर्णांक ipv6_chk_prefix(स्थिर काष्ठा in6_addr *addr, काष्ठा net_device *dev);

काष्ठा net_device *ipv6_dev_find(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
				 काष्ठा net_device *dev);

काष्ठा inet6_अगरaddr *ipv6_get_अगरaddr(काष्ठा net *net,
				     स्थिर काष्ठा in6_addr *addr,
				     काष्ठा net_device *dev, पूर्णांक strict);

पूर्णांक ipv6_dev_get_saddr(काष्ठा net *net, स्थिर काष्ठा net_device *dev,
		       स्थिर काष्ठा in6_addr *daddr, अचिन्हित पूर्णांक srcprefs,
		       काष्ठा in6_addr *saddr);
पूर्णांक __ipv6_get_lladdr(काष्ठा inet6_dev *idev, काष्ठा in6_addr *addr,
		      u32 banned_flags);
पूर्णांक ipv6_get_lladdr(काष्ठा net_device *dev, काष्ठा in6_addr *addr,
		    u32 banned_flags);
bool inet_rcv_saddr_equal(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sock *sk2,
			  bool match_wildcard);
bool inet_rcv_saddr_any(स्थिर काष्ठा sock *sk);
व्योम addrconf_join_solict(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *addr);
व्योम addrconf_leave_solict(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *addr);

व्योम addrconf_add_linklocal(काष्ठा inet6_dev *idev,
			    स्थिर काष्ठा in6_addr *addr, u32 flags);

पूर्णांक addrconf_prefix_rcv_add_addr(काष्ठा net *net, काष्ठा net_device *dev,
				 स्थिर काष्ठा prefix_info *pinfo,
				 काष्ठा inet6_dev *in6_dev,
				 स्थिर काष्ठा in6_addr *addr, पूर्णांक addr_type,
				 u32 addr_flags, bool sllao, bool tokenized,
				 __u32 valid_lft, u32 prefered_lft);

अटल अंतरभूत व्योम addrconf_addr_eui48_base(u8 *eui, स्थिर अक्षर *स्थिर addr)
अणु
	स_नकल(eui, addr, 3);
	eui[3] = 0xFF;
	eui[4] = 0xFE;
	स_नकल(eui + 5, addr + 3, 3);
पूर्ण

अटल अंतरभूत व्योम addrconf_addr_eui48(u8 *eui, स्थिर अक्षर *स्थिर addr)
अणु
	addrconf_addr_eui48_base(eui, addr);
	eui[0] ^= 2;
पूर्ण

अटल अंतरभूत पूर्णांक addrconf_अगरid_eui48(u8 *eui, काष्ठा net_device *dev)
अणु
	अगर (dev->addr_len != ETH_ALEN)
		वापस -1;

	/*
	 * The zSeries OSA network cards can be shared among various
	 * OS instances, but the OSA cards have only one MAC address.
	 * This leads to duplicate address conflicts in conjunction
	 * with IPv6 अगर more than one instance uses the same card.
	 *
	 * The driver क्रम these cards can deliver a unique 16-bit
	 * identअगरier क्रम each instance sharing the same card.  It is
	 * placed instead of 0xFFFE in the पूर्णांकerface identअगरier.  The
	 * "u" bit of the पूर्णांकerface identअगरier is not inverted in this
	 * हाल.  Hence the resulting पूर्णांकerface identअगरier has local
	 * scope according to RFC2373.
	 */

	addrconf_addr_eui48_base(eui, dev->dev_addr);

	अगर (dev->dev_id) अणु
		eui[3] = (dev->dev_id >> 8) & 0xFF;
		eui[4] = dev->dev_id & 0xFF;
	पूर्ण अन्यथा अणु
		eui[0] ^= 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ addrconf_समयout_fixup(u32 समयout,
						   अचिन्हित पूर्णांक unit)
अणु
	अगर (समयout == 0xffffffff)
		वापस ~0UL;

	/*
	 * Aव्योम arithmetic overflow.
	 * Assuming unit is स्थिरant and non-zero, this "if" statement
	 * will go away on 64bit archs.
	 */
	अगर (0xfffffffe > दीर्घ_उच्च / unit && समयout > दीर्घ_उच्च / unit)
		वापस दीर्घ_उच्च / unit;

	वापस समयout;
पूर्ण

अटल अंतरभूत पूर्णांक addrconf_finite_समयout(अचिन्हित दीर्घ समयout)
अणु
	वापस ~समयout;
पूर्ण

/*
 *	IPv6 Address Label subप्रणाली (addrlabel.c)
 */
पूर्णांक ipv6_addr_label_init(व्योम);
व्योम ipv6_addr_label_cleanup(व्योम);
पूर्णांक ipv6_addr_label_rtnl_रेजिस्टर(व्योम);
u32 ipv6_addr_label(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
		    पूर्णांक type, पूर्णांक अगरindex);

/*
 *	multicast prototypes (mcast.c)
 */
अटल अंतरभूत bool ipv6_mc_may_pull(काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक len)
अणु
	अगर (skb_transport_offset(skb) + ipv6_transport_len(skb) < len)
		वापस false;

	वापस pskb_may_pull(skb, len);
पूर्ण

पूर्णांक ipv6_sock_mc_join(काष्ठा sock *sk, पूर्णांक अगरindex,
		      स्थिर काष्ठा in6_addr *addr);
पूर्णांक ipv6_sock_mc_drop(काष्ठा sock *sk, पूर्णांक अगरindex,
		      स्थिर काष्ठा in6_addr *addr);
व्योम __ipv6_sock_mc_बंद(काष्ठा sock *sk);
व्योम ipv6_sock_mc_बंद(काष्ठा sock *sk);
bool inet6_mc_check(काष्ठा sock *sk, स्थिर काष्ठा in6_addr *mc_addr,
		    स्थिर काष्ठा in6_addr *src_addr);

पूर्णांक ipv6_dev_mc_inc(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *addr);
पूर्णांक __ipv6_dev_mc_dec(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *addr);
पूर्णांक ipv6_dev_mc_dec(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *addr);
व्योम ipv6_mc_up(काष्ठा inet6_dev *idev);
व्योम ipv6_mc_करोwn(काष्ठा inet6_dev *idev);
व्योम ipv6_mc_unmap(काष्ठा inet6_dev *idev);
व्योम ipv6_mc_remap(काष्ठा inet6_dev *idev);
व्योम ipv6_mc_init_dev(काष्ठा inet6_dev *idev);
व्योम ipv6_mc_destroy_dev(काष्ठा inet6_dev *idev);
पूर्णांक ipv6_mc_check_mld(काष्ठा sk_buff *skb);
व्योम addrconf_dad_failure(काष्ठा sk_buff *skb, काष्ठा inet6_अगरaddr *अगरp);

bool ipv6_chk_mcast_addr(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *group,
			 स्थिर काष्ठा in6_addr *src_addr);

व्योम ipv6_mc_dad_complete(काष्ठा inet6_dev *idev);

/*
 * identअगरy MLD packets क्रम MLD filter exceptions
 */
अटल अंतरभूत bool ipv6_is_mld(काष्ठा sk_buff *skb, पूर्णांक nexthdr, पूर्णांक offset)
अणु
	काष्ठा icmp6hdr *hdr;

	अगर (nexthdr != IPPROTO_ICMPV6 ||
	    !pskb_network_may_pull(skb, offset + माप(काष्ठा icmp6hdr)))
		वापस false;

	hdr = (काष्ठा icmp6hdr *)(skb_network_header(skb) + offset);

	चयन (hdr->icmp6_type) अणु
	हाल ICMPV6_MGM_QUERY:
	हाल ICMPV6_MGM_REPORT:
	हाल ICMPV6_MGM_REDUCTION:
	हाल ICMPV6_MLD2_REPORT:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

व्योम addrconf_prefix_rcv(काष्ठा net_device *dev,
			 u8 *opt, पूर्णांक len, bool sllao);

/*
 *	anycast prototypes (anycast.c)
 */
पूर्णांक ipv6_sock_ac_join(काष्ठा sock *sk, पूर्णांक अगरindex,
		      स्थिर काष्ठा in6_addr *addr);
पूर्णांक ipv6_sock_ac_drop(काष्ठा sock *sk, पूर्णांक अगरindex,
		      स्थिर काष्ठा in6_addr *addr);
व्योम __ipv6_sock_ac_बंद(काष्ठा sock *sk);
व्योम ipv6_sock_ac_बंद(काष्ठा sock *sk);

पूर्णांक __ipv6_dev_ac_inc(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *addr);
पूर्णांक __ipv6_dev_ac_dec(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *addr);
व्योम ipv6_ac_destroy_dev(काष्ठा inet6_dev *idev);
bool ipv6_chk_acast_addr(काष्ठा net *net, काष्ठा net_device *dev,
			 स्थिर काष्ठा in6_addr *addr);
bool ipv6_chk_acast_addr_src(काष्ठा net *net, काष्ठा net_device *dev,
			     स्थिर काष्ठा in6_addr *addr);
पूर्णांक ipv6_anycast_init(व्योम);
व्योम ipv6_anycast_cleanup(व्योम);

/* Device notअगरier */
पूर्णांक रेजिस्टर_inet6addr_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_inet6addr_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक inet6addr_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v);

पूर्णांक रेजिस्टर_inet6addr_validator_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_inet6addr_validator_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक inet6addr_validator_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v);

व्योम inet6_netconf_notअगरy_devconf(काष्ठा net *net, पूर्णांक event, पूर्णांक type,
				  पूर्णांक अगरindex, काष्ठा ipv6_devconf *devconf);

/**
 * __in6_dev_get - get inet6_dev poपूर्णांकer from netdevice
 * @dev: network device
 *
 * Caller must hold rcu_पढ़ो_lock or RTNL, because this function
 * करोes not take a reference on the inet6_dev.
 */
अटल अंतरभूत काष्ठा inet6_dev *__in6_dev_get(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_dereference_rtnl(dev->ip6_ptr);
पूर्ण

/**
 * __in6_dev_stats_get - get inet6_dev poपूर्णांकer क्रम stats
 * @dev: network device
 * @skb: skb क्रम original incoming पूर्णांकerface अगर neeeded
 *
 * Caller must hold rcu_पढ़ो_lock or RTNL, because this function
 * करोes not take a reference on the inet6_dev.
 */
अटल अंतरभूत काष्ठा inet6_dev *__in6_dev_stats_get(स्थिर काष्ठा net_device *dev,
						    स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (netअगर_is_l3_master(dev))
		dev = dev_get_by_index_rcu(dev_net(dev), inet6_iअगर(skb));
	वापस __in6_dev_get(dev);
पूर्ण

/**
 * __in6_dev_get_safely - get inet6_dev poपूर्णांकer from netdevice
 * @dev: network device
 *
 * This is a safer version of __in6_dev_get
 */
अटल अंतरभूत काष्ठा inet6_dev *__in6_dev_get_safely(स्थिर काष्ठा net_device *dev)
अणु
	अगर (likely(dev))
		वापस rcu_dereference_rtnl(dev->ip6_ptr);
	अन्यथा
		वापस शून्य;
पूर्ण

/**
 * in6_dev_get - get inet6_dev poपूर्णांकer from netdevice
 * @dev: network device
 *
 * This version can be used in any context, and takes a reference
 * on the inet6_dev. Callers must use in6_dev_put() later to
 * release this reference.
 */
अटल अंतरभूत काष्ठा inet6_dev *in6_dev_get(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *idev;

	rcu_पढ़ो_lock();
	idev = rcu_dereference(dev->ip6_ptr);
	अगर (idev)
		refcount_inc(&idev->refcnt);
	rcu_पढ़ो_unlock();
	वापस idev;
पूर्ण

अटल अंतरभूत काष्ठा neigh_parms *__in6_dev_nd_parms_get_rcu(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get(dev);

	वापस idev ? idev->nd_parms : शून्य;
पूर्ण

व्योम in6_dev_finish_destroy(काष्ठा inet6_dev *idev);

अटल अंतरभूत व्योम in6_dev_put(काष्ठा inet6_dev *idev)
अणु
	अगर (refcount_dec_and_test(&idev->refcnt))
		in6_dev_finish_destroy(idev);
पूर्ण

अटल अंतरभूत व्योम in6_dev_put_clear(काष्ठा inet6_dev **pidev)
अणु
	काष्ठा inet6_dev *idev = *pidev;

	अगर (idev) अणु
		in6_dev_put(idev);
		*pidev = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __in6_dev_put(काष्ठा inet6_dev *idev)
अणु
	refcount_dec(&idev->refcnt);
पूर्ण

अटल अंतरभूत व्योम in6_dev_hold(काष्ठा inet6_dev *idev)
अणु
	refcount_inc(&idev->refcnt);
पूर्ण

/* called with rcu_पढ़ो_lock held */
अटल अंतरभूत bool ip6_ignore_linkकरोwn(स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा inet6_dev *idev = __in6_dev_get(dev);

	वापस !!idev->cnf.ignore_routes_with_linkकरोwn;
पूर्ण

व्योम inet6_अगरa_finish_destroy(काष्ठा inet6_अगरaddr *अगरp);

अटल अंतरभूत व्योम in6_अगरa_put(काष्ठा inet6_अगरaddr *अगरp)
अणु
	अगर (refcount_dec_and_test(&अगरp->refcnt))
		inet6_अगरa_finish_destroy(अगरp);
पूर्ण

अटल अंतरभूत व्योम __in6_अगरa_put(काष्ठा inet6_अगरaddr *अगरp)
अणु
	refcount_dec(&अगरp->refcnt);
पूर्ण

अटल अंतरभूत व्योम in6_अगरa_hold(काष्ठा inet6_अगरaddr *अगरp)
अणु
	refcount_inc(&अगरp->refcnt);
पूर्ण


/*
 *	compute link-local solicited-node multicast address
 */

अटल अंतरभूत व्योम addrconf_addr_solict_mult(स्थिर काष्ठा in6_addr *addr,
					     काष्ठा in6_addr *solicited)
अणु
	ipv6_addr_set(solicited,
		      htonl(0xFF020000), 0,
		      htonl(0x1),
		      htonl(0xFF000000) | addr->s6_addr32[3]);
पूर्ण

अटल अंतरभूत bool ipv6_addr_is_ll_all_nodes(स्थिर काष्ठा in6_addr *addr)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	__be64 *p = (__क्रमce __be64 *)addr;
	वापस ((p[0] ^ cpu_to_be64(0xff02000000000000UL)) | (p[1] ^ cpu_to_be64(1))) == 0UL;
#अन्यथा
	वापस ((addr->s6_addr32[0] ^ htonl(0xff020000)) |
		addr->s6_addr32[1] | addr->s6_addr32[2] |
		(addr->s6_addr32[3] ^ htonl(0x00000001))) == 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool ipv6_addr_is_ll_all_routers(स्थिर काष्ठा in6_addr *addr)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	__be64 *p = (__क्रमce __be64 *)addr;
	वापस ((p[0] ^ cpu_to_be64(0xff02000000000000UL)) | (p[1] ^ cpu_to_be64(2))) == 0UL;
#अन्यथा
	वापस ((addr->s6_addr32[0] ^ htonl(0xff020000)) |
		addr->s6_addr32[1] | addr->s6_addr32[2] |
		(addr->s6_addr32[3] ^ htonl(0x00000002))) == 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool ipv6_addr_is_isatap(स्थिर काष्ठा in6_addr *addr)
अणु
	वापस (addr->s6_addr32[2] | htonl(0x02000000)) == htonl(0x02005EFE);
पूर्ण

अटल अंतरभूत bool ipv6_addr_is_solict_mult(स्थिर काष्ठा in6_addr *addr)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	__be64 *p = (__क्रमce __be64 *)addr;
	वापस ((p[0] ^ cpu_to_be64(0xff02000000000000UL)) |
		((p[1] ^ cpu_to_be64(0x00000001ff000000UL)) &
		 cpu_to_be64(0xffffffffff000000UL))) == 0UL;
#अन्यथा
	वापस ((addr->s6_addr32[0] ^ htonl(0xff020000)) |
		addr->s6_addr32[1] |
		(addr->s6_addr32[2] ^ htonl(0x00000001)) |
		(addr->s6_addr[12] ^ 0xff)) == 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool ipv6_addr_is_all_snoopers(स्थिर काष्ठा in6_addr *addr)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS) && BITS_PER_LONG == 64
	__be64 *p = (__क्रमce __be64 *)addr;

	वापस ((p[0] ^ cpu_to_be64(0xff02000000000000UL)) |
		(p[1] ^ cpu_to_be64(0x6a))) == 0UL;
#अन्यथा
	वापस ((addr->s6_addr32[0] ^ htonl(0xff020000)) |
		addr->s6_addr32[1] | addr->s6_addr32[2] |
		(addr->s6_addr32[3] ^ htonl(0x0000006a))) == 0;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक अगर6_proc_init(व्योम);
व्योम अगर6_proc_निकास(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर
