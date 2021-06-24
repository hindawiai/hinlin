<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NDISC_H
#घोषणा _NDISC_H

#समावेश <net/ipv6_stubs.h>

/*
 *	ICMP codes क्रम neighbour discovery messages
 */

#घोषणा NDISC_ROUTER_SOLICITATION	133
#घोषणा NDISC_ROUTER_ADVERTISEMENT	134
#घोषणा NDISC_NEIGHBOUR_SOLICITATION	135
#घोषणा NDISC_NEIGHBOUR_ADVERTISEMENT	136
#घोषणा NDISC_REसूचीECT			137

/*
 * Router type: cross-layer inक्रमmation from link-layer to
 * IPv6 layer reported by certain link types (e.g., RFC4214).
 */
#घोषणा NDISC_NODETYPE_UNSPEC		0	/* unspecअगरied (शेष) */
#घोषणा NDISC_NODETYPE_HOST		1	/* host or unauthorized router */
#घोषणा NDISC_NODETYPE_NODEFAULT	2	/* non-शेष router */
#घोषणा NDISC_NODETYPE_DEFAULT		3	/* शेष router */

/*
 *	ndisc options
 */

क्रमागत अणु
	__ND_OPT_PREFIX_INFO_END = 0,
	ND_OPT_SOURCE_LL_ADDR = 1,	/* RFC2461 */
	ND_OPT_TARGET_LL_ADDR = 2,	/* RFC2461 */
	ND_OPT_PREFIX_INFO = 3,		/* RFC2461 */
	ND_OPT_REसूचीECT_HDR = 4,	/* RFC2461 */
	ND_OPT_MTU = 5,			/* RFC2461 */
	ND_OPT_NONCE = 14,              /* RFC7527 */
	__ND_OPT_ARRAY_MAX,
	ND_OPT_ROUTE_INFO = 24,		/* RFC4191 */
	ND_OPT_RDNSS = 25,		/* RFC5006 */
	ND_OPT_DNSSL = 31,		/* RFC6106 */
	ND_OPT_6CO = 34,		/* RFC6775 */
	ND_OPT_CAPTIVE_PORTAL = 37,	/* RFC7710 */
	ND_OPT_PREF64 = 38,		/* RFC8781 */
	__ND_OPT_MAX
पूर्ण;

#घोषणा MAX_RTR_SOLICITATION_DELAY	HZ

#घोषणा ND_REACHABLE_TIME		(30*HZ)
#घोषणा ND_RETRANS_TIMER		HZ

#समावेश <linux/compiler.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/in6.h>
#समावेश <linux/types.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hash.h>

#समावेश <net/neighbour.h>

/* Set to 3 to get tracing... */
#घोषणा ND_DEBUG 1

#घोषणा ND_PRINTK(val, level, fmt, ...)				\
करो अणु								\
	अगर (val <= ND_DEBUG)					\
		net_##level##_ratelimited(fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

काष्ठा ctl_table;
काष्ठा inet6_dev;
काष्ठा net_device;
काष्ठा net_proto_family;
काष्ठा sk_buff;
काष्ठा prefix_info;

बाह्य काष्ठा neigh_table nd_tbl;

काष्ठा nd_msg अणु
        काष्ठा icmp6hdr	icmph;
        काष्ठा in6_addr	target;
	__u8		opt[];
पूर्ण;

काष्ठा rs_msg अणु
	काष्ठा icmp6hdr	icmph;
	__u8		opt[];
पूर्ण;

काष्ठा ra_msg अणु
        काष्ठा icmp6hdr		icmph;
	__be32			reachable_समय;
	__be32			retrans_समयr;
पूर्ण;

काष्ठा rd_msg अणु
	काष्ठा icmp6hdr icmph;
	काष्ठा in6_addr	target;
	काष्ठा in6_addr	dest;
	__u8		opt[];
पूर्ण;

काष्ठा nd_opt_hdr अणु
	__u8		nd_opt_type;
	__u8		nd_opt_len;
पूर्ण __packed;

/* ND options */
काष्ठा ndisc_options अणु
	काष्ठा nd_opt_hdr *nd_opt_array[__ND_OPT_ARRAY_MAX];
#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
	काष्ठा nd_opt_hdr *nd_opts_ri;
	काष्ठा nd_opt_hdr *nd_opts_ri_end;
#पूर्ण_अगर
	काष्ठा nd_opt_hdr *nd_useropts;
	काष्ठा nd_opt_hdr *nd_useropts_end;
#अगर IS_ENABLED(CONFIG_IEEE802154_6LOWPAN)
	काष्ठा nd_opt_hdr *nd_802154_opt_array[ND_OPT_TARGET_LL_ADDR + 1];
#पूर्ण_अगर
पूर्ण;

#घोषणा nd_opts_src_lladdr		nd_opt_array[ND_OPT_SOURCE_LL_ADDR]
#घोषणा nd_opts_tgt_lladdr		nd_opt_array[ND_OPT_TARGET_LL_ADDR]
#घोषणा nd_opts_pi			nd_opt_array[ND_OPT_PREFIX_INFO]
#घोषणा nd_opts_pi_end			nd_opt_array[__ND_OPT_PREFIX_INFO_END]
#घोषणा nd_opts_rh			nd_opt_array[ND_OPT_REसूचीECT_HDR]
#घोषणा nd_opts_mtu			nd_opt_array[ND_OPT_MTU]
#घोषणा nd_opts_nonce			nd_opt_array[ND_OPT_NONCE]
#घोषणा nd_802154_opts_src_lladdr	nd_802154_opt_array[ND_OPT_SOURCE_LL_ADDR]
#घोषणा nd_802154_opts_tgt_lladdr	nd_802154_opt_array[ND_OPT_TARGET_LL_ADDR]

#घोषणा NDISC_OPT_SPACE(len) (((len)+2+7)&~7)

काष्ठा ndisc_options *ndisc_parse_options(स्थिर काष्ठा net_device *dev,
					  u8 *opt, पूर्णांक opt_len,
					  काष्ठा ndisc_options *nकरोpts);

व्योम __ndisc_fill_addr_option(काष्ठा sk_buff *skb, पूर्णांक type, व्योम *data,
			      पूर्णांक data_len, पूर्णांक pad);

#घोषणा NDISC_OPS_REसूचीECT_DATA_SPACE	2

/*
 * This काष्ठाure defines the hooks क्रम IPv6 neighbour discovery.
 * The following hooks can be defined; unless noted otherwise, they are
 * optional and can be filled with a null poपूर्णांकer.
 *
 * पूर्णांक (*is_useropt)(u8 nd_opt_type):
 *     This function is called when IPv6 decide RA userspace options. अगर
 *     this function वापसs 1 then the option given by nd_opt_type will
 *     be handled as userspace option additional to the IPv6 options.
 *
 * पूर्णांक (*parse_options)(स्थिर काष्ठा net_device *dev,
 *			काष्ठा nd_opt_hdr *nd_opt,
 *			काष्ठा ndisc_options *nकरोpts):
 *     This function is called जबतक parsing ndisc ops and put each position
 *     as poपूर्णांकer पूर्णांकo nकरोpts. If this function वापस unequal 0, then this
 *     function took care about the ndisc option, अगर 0 then the IPv6 ndisc
 *     option parser will take care about that option.
 *
 * व्योम (*update)(स्थिर काष्ठा net_device *dev, काष्ठा neighbour *n,
 *		  u32 flags, u8 icmp6_type,
 *		  स्थिर काष्ठा ndisc_options *nकरोpts):
 *     This function is called when IPv6 ndisc updates the neighbour cache
 *     entry. Additional options which can be updated may be previously
 *     parsed by parse_opts callback and accessible over nकरोpts parameter.
 *
 * पूर्णांक (*opt_addr_space)(स्थिर काष्ठा net_device *dev, u8 icmp6_type,
 *			 काष्ठा neighbour *neigh, u8 *ha_buf,
 *			 u8 **ha):
 *     This function is called when the necessary option space will be
 *     calculated beक्रमe allocating a skb. The parameters neigh, ha_buf
 *     abd ha are available on NDISC_REसूचीECT messages only.
 *
 * व्योम (*fill_addr_option)(स्थिर काष्ठा net_device *dev,
 *			    काष्ठा sk_buff *skb, u8 icmp6_type,
 *			    स्थिर u8 *ha):
 *     This function is called when the skb will finally fill the option
 *     fields inside skb. NOTE: this callback should fill the option
 *     fields to the skb which are previously indicated by opt_space
 *     parameter. That means the decision to add such option should
 *     not lost between these two callbacks, e.g. रक्षित by पूर्णांकerface
 *     up state.
 *
 * व्योम (*prefix_rcv_add_addr)(काष्ठा net *net, काष्ठा net_device *dev,
 *			       स्थिर काष्ठा prefix_info *pinfo,
 *			       काष्ठा inet6_dev *in6_dev,
 *			       काष्ठा in6_addr *addr,
 *			       पूर्णांक addr_type, u32 addr_flags,
 *			       bool sllao, bool tokenized,
 *			       __u32 valid_lft, u32 prefered_lft,
 *			       bool dev_addr_generated):
 *     This function is called when a RA messages is received with valid
 *     PIO option fields and an IPv6 address will be added to the पूर्णांकerface
 *     क्रम स्वतःconfiguration. The parameter dev_addr_generated reports about
 *     अगर the address was based on dev->dev_addr or not. This can be used
 *     to add a second address अगर link-layer operates with two link layer
 *     addresses. E.g. 802.15.4 6LoWPAN.
 */
काष्ठा ndisc_ops अणु
	पूर्णांक	(*is_useropt)(u8 nd_opt_type);
	पूर्णांक	(*parse_options)(स्थिर काष्ठा net_device *dev,
				 काष्ठा nd_opt_hdr *nd_opt,
				 काष्ठा ndisc_options *nकरोpts);
	व्योम	(*update)(स्थिर काष्ठा net_device *dev, काष्ठा neighbour *n,
			  u32 flags, u8 icmp6_type,
			  स्थिर काष्ठा ndisc_options *nकरोpts);
	पूर्णांक	(*opt_addr_space)(स्थिर काष्ठा net_device *dev, u8 icmp6_type,
				  काष्ठा neighbour *neigh, u8 *ha_buf,
				  u8 **ha);
	व्योम	(*fill_addr_option)(स्थिर काष्ठा net_device *dev,
				    काष्ठा sk_buff *skb, u8 icmp6_type,
				    स्थिर u8 *ha);
	व्योम	(*prefix_rcv_add_addr)(काष्ठा net *net, काष्ठा net_device *dev,
				       स्थिर काष्ठा prefix_info *pinfo,
				       काष्ठा inet6_dev *in6_dev,
				       काष्ठा in6_addr *addr,
				       पूर्णांक addr_type, u32 addr_flags,
				       bool sllao, bool tokenized,
				       __u32 valid_lft, u32 prefered_lft,
				       bool dev_addr_generated);
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत पूर्णांक ndisc_ops_is_useropt(स्थिर काष्ठा net_device *dev,
				       u8 nd_opt_type)
अणु
	अगर (dev->ndisc_ops && dev->ndisc_ops->is_useropt)
		वापस dev->ndisc_ops->is_useropt(nd_opt_type);
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ndisc_ops_parse_options(स्थिर काष्ठा net_device *dev,
					  काष्ठा nd_opt_hdr *nd_opt,
					  काष्ठा ndisc_options *nकरोpts)
अणु
	अगर (dev->ndisc_ops && dev->ndisc_ops->parse_options)
		वापस dev->ndisc_ops->parse_options(dev, nd_opt, nकरोpts);
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत व्योम ndisc_ops_update(स्थिर काष्ठा net_device *dev,
					  काष्ठा neighbour *n, u32 flags,
					  u8 icmp6_type,
					  स्थिर काष्ठा ndisc_options *nकरोpts)
अणु
	अगर (dev->ndisc_ops && dev->ndisc_ops->update)
		dev->ndisc_ops->update(dev, n, flags, icmp6_type, nकरोpts);
पूर्ण

अटल अंतरभूत पूर्णांक ndisc_ops_opt_addr_space(स्थिर काष्ठा net_device *dev,
					   u8 icmp6_type)
अणु
	अगर (dev->ndisc_ops && dev->ndisc_ops->opt_addr_space &&
	    icmp6_type != NDISC_REसूचीECT)
		वापस dev->ndisc_ops->opt_addr_space(dev, icmp6_type, शून्य,
						      शून्य, शून्य);
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ndisc_ops_redirect_opt_addr_space(स्थिर काष्ठा net_device *dev,
						    काष्ठा neighbour *neigh,
						    u8 *ha_buf, u8 **ha)
अणु
	अगर (dev->ndisc_ops && dev->ndisc_ops->opt_addr_space)
		वापस dev->ndisc_ops->opt_addr_space(dev, NDISC_REसूचीECT,
						      neigh, ha_buf, ha);
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत व्योम ndisc_ops_fill_addr_option(स्थिर काष्ठा net_device *dev,
					      काष्ठा sk_buff *skb,
					      u8 icmp6_type)
अणु
	अगर (dev->ndisc_ops && dev->ndisc_ops->fill_addr_option &&
	    icmp6_type != NDISC_REसूचीECT)
		dev->ndisc_ops->fill_addr_option(dev, skb, icmp6_type, शून्य);
पूर्ण

अटल अंतरभूत व्योम ndisc_ops_fill_redirect_addr_option(स्थिर काष्ठा net_device *dev,
						       काष्ठा sk_buff *skb,
						       स्थिर u8 *ha)
अणु
	अगर (dev->ndisc_ops && dev->ndisc_ops->fill_addr_option)
		dev->ndisc_ops->fill_addr_option(dev, skb, NDISC_REसूचीECT, ha);
पूर्ण

अटल अंतरभूत व्योम ndisc_ops_prefix_rcv_add_addr(काष्ठा net *net,
						 काष्ठा net_device *dev,
						 स्थिर काष्ठा prefix_info *pinfo,
						 काष्ठा inet6_dev *in6_dev,
						 काष्ठा in6_addr *addr,
						 पूर्णांक addr_type, u32 addr_flags,
						 bool sllao, bool tokenized,
						 __u32 valid_lft,
						 u32 prefered_lft,
						 bool dev_addr_generated)
अणु
	अगर (dev->ndisc_ops && dev->ndisc_ops->prefix_rcv_add_addr)
		dev->ndisc_ops->prefix_rcv_add_addr(net, dev, pinfo, in6_dev,
						    addr, addr_type,
						    addr_flags, sllao,
						    tokenized, valid_lft,
						    prefered_lft,
						    dev_addr_generated);
पूर्ण
#पूर्ण_अगर

/*
 * Return the padding between the option length and the start of the
 * link addr.  Currently only IP-over-InfiniBand needs this, although
 * अगर RFC 3831 IPv6-over-Fibre Channel is ever implemented it may
 * also need a pad of 2.
 */
अटल अंतरभूत पूर्णांक ndisc_addr_option_pad(अचिन्हित लघु type)
अणु
	चयन (type) अणु
	हाल ARPHRD_INFINIBAND: वापस 2;
	शेष:                वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक __ndisc_opt_addr_space(अचिन्हित अक्षर addr_len, पूर्णांक pad)
अणु
	वापस NDISC_OPT_SPACE(addr_len + pad);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत पूर्णांक ndisc_opt_addr_space(काष्ठा net_device *dev, u8 icmp6_type)
अणु
	वापस __ndisc_opt_addr_space(dev->addr_len,
				      ndisc_addr_option_pad(dev->type)) +
		ndisc_ops_opt_addr_space(dev, icmp6_type);
पूर्ण

अटल अंतरभूत पूर्णांक ndisc_redirect_opt_addr_space(काष्ठा net_device *dev,
						काष्ठा neighbour *neigh,
						u8 *ops_data_buf,
						u8 **ops_data)
अणु
	वापस __ndisc_opt_addr_space(dev->addr_len,
				      ndisc_addr_option_pad(dev->type)) +
		ndisc_ops_redirect_opt_addr_space(dev, neigh, ops_data_buf,
						  ops_data);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u8 *__ndisc_opt_addr_data(काष्ठा nd_opt_hdr *p,
					अचिन्हित अक्षर addr_len, पूर्णांक prepad)
अणु
	u8 *lladdr = (u8 *)(p + 1);
	पूर्णांक lladdrlen = p->nd_opt_len << 3;
	अगर (lladdrlen != __ndisc_opt_addr_space(addr_len, prepad))
		वापस शून्य;
	वापस lladdr + prepad;
पूर्ण

अटल अंतरभूत u8 *ndisc_opt_addr_data(काष्ठा nd_opt_hdr *p,
				      काष्ठा net_device *dev)
अणु
	वापस __ndisc_opt_addr_data(p, dev->addr_len,
				     ndisc_addr_option_pad(dev->type));
पूर्ण

अटल अंतरभूत u32 ndisc_hashfn(स्थिर व्योम *pkey, स्थिर काष्ठा net_device *dev, __u32 *hash_rnd)
अणु
	स्थिर u32 *p32 = pkey;

	वापस (((p32[0] ^ hash32_ptr(dev)) * hash_rnd[0]) +
		(p32[1] * hash_rnd[1]) +
		(p32[2] * hash_rnd[2]) +
		(p32[3] * hash_rnd[3]));
पूर्ण

अटल अंतरभूत काष्ठा neighbour *__ipv6_neigh_lookup_noref(काष्ठा net_device *dev, स्थिर व्योम *pkey)
अणु
	वापस ___neigh_lookup_noref(&nd_tbl, neigh_key_eq128, ndisc_hashfn, pkey, dev);
पूर्ण

अटल अंतरभूत
काष्ठा neighbour *__ipv6_neigh_lookup_noref_stub(काष्ठा net_device *dev,
						 स्थिर व्योम *pkey)
अणु
	वापस ___neigh_lookup_noref(ipv6_stub->nd_tbl, neigh_key_eq128,
				     ndisc_hashfn, pkey, dev);
पूर्ण

अटल अंतरभूत काष्ठा neighbour *__ipv6_neigh_lookup(काष्ठा net_device *dev, स्थिर व्योम *pkey)
अणु
	काष्ठा neighbour *n;

	rcu_पढ़ो_lock_bh();
	n = __ipv6_neigh_lookup_noref(dev, pkey);
	अगर (n && !refcount_inc_not_zero(&n->refcnt))
		n = शून्य;
	rcu_पढ़ो_unlock_bh();

	वापस n;
पूर्ण

अटल अंतरभूत व्योम __ipv6_confirm_neigh(काष्ठा net_device *dev,
					स्थिर व्योम *pkey)
अणु
	काष्ठा neighbour *n;

	rcu_पढ़ो_lock_bh();
	n = __ipv6_neigh_lookup_noref(dev, pkey);
	अगर (n) अणु
		अचिन्हित दीर्घ now = jअगरfies;

		/* aव्योम dirtying neighbour */
		अगर (READ_ONCE(n->confirmed) != now)
			WRITE_ONCE(n->confirmed, now);
	पूर्ण
	rcu_पढ़ो_unlock_bh();
पूर्ण

अटल अंतरभूत व्योम __ipv6_confirm_neigh_stub(काष्ठा net_device *dev,
					     स्थिर व्योम *pkey)
अणु
	काष्ठा neighbour *n;

	rcu_पढ़ो_lock_bh();
	n = __ipv6_neigh_lookup_noref_stub(dev, pkey);
	अगर (n) अणु
		अचिन्हित दीर्घ now = jअगरfies;

		/* aव्योम dirtying neighbour */
		अगर (READ_ONCE(n->confirmed) != now)
			WRITE_ONCE(n->confirmed, now);
	पूर्ण
	rcu_पढ़ो_unlock_bh();
पूर्ण

/* uses ipv6_stub and is meant क्रम use outside of IPv6 core */
अटल अंतरभूत काष्ठा neighbour *ip_neigh_gw6(काष्ठा net_device *dev,
					     स्थिर व्योम *addr)
अणु
	काष्ठा neighbour *neigh;

	neigh = __ipv6_neigh_lookup_noref_stub(dev, addr);
	अगर (unlikely(!neigh))
		neigh = __neigh_create(ipv6_stub->nd_tbl, addr, dev, false);

	वापस neigh;
पूर्ण

पूर्णांक ndisc_init(व्योम);
पूर्णांक ndisc_late_init(व्योम);

व्योम ndisc_late_cleanup(व्योम);
व्योम ndisc_cleanup(व्योम);

पूर्णांक ndisc_rcv(काष्ठा sk_buff *skb);

व्योम ndisc_send_ns(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *solicit,
		   स्थिर काष्ठा in6_addr *daddr, स्थिर काष्ठा in6_addr *saddr,
		   u64 nonce);

व्योम ndisc_send_rs(काष्ठा net_device *dev,
		   स्थिर काष्ठा in6_addr *saddr, स्थिर काष्ठा in6_addr *daddr);
व्योम ndisc_send_na(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *daddr,
		   स्थिर काष्ठा in6_addr *solicited_addr,
		   bool router, bool solicited, bool override, bool inc_opt);

व्योम ndisc_send_redirect(काष्ठा sk_buff *skb, स्थिर काष्ठा in6_addr *target);

पूर्णांक ndisc_mc_map(स्थिर काष्ठा in6_addr *addr, अक्षर *buf, काष्ठा net_device *dev,
		 पूर्णांक dir);

व्योम ndisc_update(स्थिर काष्ठा net_device *dev, काष्ठा neighbour *neigh,
		  स्थिर u8 *lladdr, u8 new, u32 flags, u8 icmp6_type,
		  काष्ठा ndisc_options *nकरोpts);

/*
 *	IGMP
 */
पूर्णांक igmp6_init(व्योम);
पूर्णांक igmp6_late_init(व्योम);

व्योम igmp6_cleanup(व्योम);
व्योम igmp6_late_cleanup(व्योम);

पूर्णांक igmp6_event_query(काष्ठा sk_buff *skb);

पूर्णांक igmp6_event_report(काष्ठा sk_buff *skb);


#अगर_घोषित CONFIG_SYSCTL
पूर्णांक ndisc_अगरinfo_sysctl_change(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			       व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक ndisc_अगरinfo_sysctl_strategy(काष्ठा ctl_table *ctl,
				 व्योम __user *oldval, माप_प्रकार __user *oldlenp,
				 व्योम __user *newval, माप_प्रकार newlen);
#पूर्ण_अगर

व्योम inet6_अगरinfo_notअगरy(पूर्णांक event, काष्ठा inet6_dev *idev);

#पूर्ण_अगर
