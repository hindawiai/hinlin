<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Neighbour Discovery क्रम IPv6
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *	Mike Shaver		<shaver@ingenia.com>
 */

/*
 *	Changes:
 *
 *	Alexey I. Froloff		:	RFC6106 (DNSSL) support
 *	Pierre Ynard			:	export userland ND options
 *						through netlink (RDNSS support)
 *	Lars Fenneberg			:	fixed MTU setting on receipt
 *						of an RA.
 *	Janos Farkas			:	kदो_स्मृति failure checks
 *	Alexey Kuznetsov		:	state machine reworked
 *						and moved to net/core.
 *	Pekka Savola			:	RFC2461 validation
 *	YOSHIFUJI Hideaki @USAGI	:	Verअगरy ND options properly
 */

#घोषणा pr_fmt(fmt) "ICMPv6: " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/sched.h>
#समावेश <linux/net.h>
#समावेश <linux/in6.h>
#समावेश <linux/route.h>
#समावेश <linux/init.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/slab.h>
#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर

#समावेश <linux/अगर_addr.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/jhash.h>

#समावेश <net/sock.h>
#समावेश <net/snmp.h>

#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/ndisc.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/icmp.h>

#समावेश <net/netlink.h>
#समावेश <linux/rtnetlink.h>

#समावेश <net/flow.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/inet_common.h>
#समावेश <linux/proc_fs.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>

अटल u32 ndisc_hash(स्थिर व्योम *pkey,
		      स्थिर काष्ठा net_device *dev,
		      __u32 *hash_rnd);
अटल bool ndisc_key_eq(स्थिर काष्ठा neighbour *neigh, स्थिर व्योम *pkey);
अटल bool ndisc_allow_add(स्थिर काष्ठा net_device *dev,
			    काष्ठा netlink_ext_ack *extack);
अटल पूर्णांक ndisc_स्थिरructor(काष्ठा neighbour *neigh);
अटल व्योम ndisc_solicit(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb);
अटल व्योम ndisc_error_report(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb);
अटल पूर्णांक pndisc_स्थिरructor(काष्ठा pneigh_entry *n);
अटल व्योम pndisc_deकाष्ठाor(काष्ठा pneigh_entry *n);
अटल व्योम pndisc_reकरो(काष्ठा sk_buff *skb);
अटल पूर्णांक ndisc_is_multicast(स्थिर व्योम *pkey);

अटल स्थिर काष्ठा neigh_ops ndisc_generic_ops = अणु
	.family =		AF_INET6,
	.solicit =		ndisc_solicit,
	.error_report =		ndisc_error_report,
	.output =		neigh_resolve_output,
	.connected_output =	neigh_connected_output,
पूर्ण;

अटल स्थिर काष्ठा neigh_ops ndisc_hh_ops = अणु
	.family =		AF_INET6,
	.solicit =		ndisc_solicit,
	.error_report =		ndisc_error_report,
	.output =		neigh_resolve_output,
	.connected_output =	neigh_resolve_output,
पूर्ण;


अटल स्थिर काष्ठा neigh_ops ndisc_direct_ops = अणु
	.family =		AF_INET6,
	.output =		neigh_direct_output,
	.connected_output =	neigh_direct_output,
पूर्ण;

काष्ठा neigh_table nd_tbl = अणु
	.family =	AF_INET6,
	.key_len =	माप(काष्ठा in6_addr),
	.protocol =	cpu_to_be16(ETH_P_IPV6),
	.hash =		ndisc_hash,
	.key_eq =	ndisc_key_eq,
	.स्थिरructor =	ndisc_स्थिरructor,
	.pस्थिरructor =	pndisc_स्थिरructor,
	.pdeकाष्ठाor =	pndisc_deकाष्ठाor,
	.proxy_reकरो =	pndisc_reकरो,
	.is_multicast =	ndisc_is_multicast,
	.allow_add  =   ndisc_allow_add,
	.id =		"ndisc_cache",
	.parms = अणु
		.tbl			= &nd_tbl,
		.reachable_समय		= ND_REACHABLE_TIME,
		.data = अणु
			[NEIGH_VAR_MCAST_PROBES] = 3,
			[NEIGH_VAR_UCAST_PROBES] = 3,
			[NEIGH_VAR_RETRANS_TIME] = ND_RETRANS_TIMER,
			[NEIGH_VAR_BASE_REACHABLE_TIME] = ND_REACHABLE_TIME,
			[NEIGH_VAR_DELAY_PROBE_TIME] = 5 * HZ,
			[NEIGH_VAR_GC_STALETIME] = 60 * HZ,
			[NEIGH_VAR_QUEUE_LEN_BYTES] = SK_WMEM_MAX,
			[NEIGH_VAR_PROXY_QLEN] = 64,
			[NEIGH_VAR_ANYCAST_DELAY] = 1 * HZ,
			[NEIGH_VAR_PROXY_DELAY] = (8 * HZ) / 10,
		पूर्ण,
	पूर्ण,
	.gc_पूर्णांकerval =	  30 * HZ,
	.gc_thresh1 =	 128,
	.gc_thresh2 =	 512,
	.gc_thresh3 =	1024,
पूर्ण;
EXPORT_SYMBOL_GPL(nd_tbl);

व्योम __ndisc_fill_addr_option(काष्ठा sk_buff *skb, पूर्णांक type, व्योम *data,
			      पूर्णांक data_len, पूर्णांक pad)
अणु
	पूर्णांक space = __ndisc_opt_addr_space(data_len, pad);
	u8 *opt = skb_put(skb, space);

	opt[0] = type;
	opt[1] = space>>3;

	स_रखो(opt + 2, 0, pad);
	opt   += pad;
	space -= pad;

	स_नकल(opt+2, data, data_len);
	data_len += 2;
	opt += data_len;
	space -= data_len;
	अगर (space > 0)
		स_रखो(opt, 0, space);
पूर्ण
EXPORT_SYMBOL_GPL(__ndisc_fill_addr_option);

अटल अंतरभूत व्योम ndisc_fill_addr_option(काष्ठा sk_buff *skb, पूर्णांक type,
					  व्योम *data, u8 icmp6_type)
अणु
	__ndisc_fill_addr_option(skb, type, data, skb->dev->addr_len,
				 ndisc_addr_option_pad(skb->dev->type));
	ndisc_ops_fill_addr_option(skb->dev, skb, icmp6_type);
पूर्ण

अटल अंतरभूत व्योम ndisc_fill_redirect_addr_option(काष्ठा sk_buff *skb,
						   व्योम *ha,
						   स्थिर u8 *ops_data)
अणु
	ndisc_fill_addr_option(skb, ND_OPT_TARGET_LL_ADDR, ha, NDISC_REसूचीECT);
	ndisc_ops_fill_redirect_addr_option(skb->dev, skb, ops_data);
पूर्ण

अटल काष्ठा nd_opt_hdr *ndisc_next_option(काष्ठा nd_opt_hdr *cur,
					    काष्ठा nd_opt_hdr *end)
अणु
	पूर्णांक type;
	अगर (!cur || !end || cur >= end)
		वापस शून्य;
	type = cur->nd_opt_type;
	करो अणु
		cur = ((व्योम *)cur) + (cur->nd_opt_len << 3);
	पूर्ण जबतक (cur < end && cur->nd_opt_type != type);
	वापस cur <= end && cur->nd_opt_type == type ? cur : शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक ndisc_is_useropt(स्थिर काष्ठा net_device *dev,
				   काष्ठा nd_opt_hdr *opt)
अणु
	वापस opt->nd_opt_type == ND_OPT_RDNSS ||
		opt->nd_opt_type == ND_OPT_DNSSL ||
		opt->nd_opt_type == ND_OPT_CAPTIVE_PORTAL ||
		opt->nd_opt_type == ND_OPT_PREF64 ||
		ndisc_ops_is_useropt(dev, opt->nd_opt_type);
पूर्ण

अटल काष्ठा nd_opt_hdr *ndisc_next_useropt(स्थिर काष्ठा net_device *dev,
					     काष्ठा nd_opt_hdr *cur,
					     काष्ठा nd_opt_hdr *end)
अणु
	अगर (!cur || !end || cur >= end)
		वापस शून्य;
	करो अणु
		cur = ((व्योम *)cur) + (cur->nd_opt_len << 3);
	पूर्ण जबतक (cur < end && !ndisc_is_useropt(dev, cur));
	वापस cur <= end && ndisc_is_useropt(dev, cur) ? cur : शून्य;
पूर्ण

काष्ठा ndisc_options *ndisc_parse_options(स्थिर काष्ठा net_device *dev,
					  u8 *opt, पूर्णांक opt_len,
					  काष्ठा ndisc_options *nकरोpts)
अणु
	काष्ठा nd_opt_hdr *nd_opt = (काष्ठा nd_opt_hdr *)opt;

	अगर (!nd_opt || opt_len < 0 || !nकरोpts)
		वापस शून्य;
	स_रखो(nकरोpts, 0, माप(*nकरोpts));
	जबतक (opt_len) अणु
		पूर्णांक l;
		अगर (opt_len < माप(काष्ठा nd_opt_hdr))
			वापस शून्य;
		l = nd_opt->nd_opt_len << 3;
		अगर (opt_len < l || l == 0)
			वापस शून्य;
		अगर (ndisc_ops_parse_options(dev, nd_opt, nकरोpts))
			जाओ next_opt;
		चयन (nd_opt->nd_opt_type) अणु
		हाल ND_OPT_SOURCE_LL_ADDR:
		हाल ND_OPT_TARGET_LL_ADDR:
		हाल ND_OPT_MTU:
		हाल ND_OPT_NONCE:
		हाल ND_OPT_REसूचीECT_HDR:
			अगर (nकरोpts->nd_opt_array[nd_opt->nd_opt_type]) अणु
				ND_PRINTK(2, warn,
					  "%s: duplicated ND6 option found: type=%d\n",
					  __func__, nd_opt->nd_opt_type);
			पूर्ण अन्यथा अणु
				nकरोpts->nd_opt_array[nd_opt->nd_opt_type] = nd_opt;
			पूर्ण
			अवरोध;
		हाल ND_OPT_PREFIX_INFO:
			nकरोpts->nd_opts_pi_end = nd_opt;
			अगर (!nकरोpts->nd_opt_array[nd_opt->nd_opt_type])
				nकरोpts->nd_opt_array[nd_opt->nd_opt_type] = nd_opt;
			अवरोध;
#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
		हाल ND_OPT_ROUTE_INFO:
			nकरोpts->nd_opts_ri_end = nd_opt;
			अगर (!nकरोpts->nd_opts_ri)
				nकरोpts->nd_opts_ri = nd_opt;
			अवरोध;
#पूर्ण_अगर
		शेष:
			अगर (ndisc_is_useropt(dev, nd_opt)) अणु
				nकरोpts->nd_useropts_end = nd_opt;
				अगर (!nकरोpts->nd_useropts)
					nकरोpts->nd_useropts = nd_opt;
			पूर्ण अन्यथा अणु
				/*
				 * Unknown options must be silently ignored,
				 * to accommodate future extension to the
				 * protocol.
				 */
				ND_PRINTK(2, notice,
					  "%s: ignored unsupported option; type=%d, len=%d\n",
					  __func__,
					  nd_opt->nd_opt_type,
					  nd_opt->nd_opt_len);
			पूर्ण
		पूर्ण
next_opt:
		opt_len -= l;
		nd_opt = ((व्योम *)nd_opt) + l;
	पूर्ण
	वापस nकरोpts;
पूर्ण

पूर्णांक ndisc_mc_map(स्थिर काष्ठा in6_addr *addr, अक्षर *buf, काष्ठा net_device *dev, पूर्णांक dir)
अणु
	चयन (dev->type) अणु
	हाल ARPHRD_ETHER:
	हाल ARPHRD_IEEE802:	/* Not sure. Check it later. --ANK */
	हाल ARPHRD_FDDI:
		ipv6_eth_mc_map(addr, buf);
		वापस 0;
	हाल ARPHRD_ARCNET:
		ipv6_arcnet_mc_map(addr, buf);
		वापस 0;
	हाल ARPHRD_INFINIBAND:
		ipv6_ib_mc_map(addr, dev->broadcast, buf);
		वापस 0;
	हाल ARPHRD_IPGRE:
		वापस ipv6_ipgre_mc_map(addr, dev->broadcast, buf);
	शेष:
		अगर (dir) अणु
			स_नकल(buf, dev->broadcast, dev->addr_len);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(ndisc_mc_map);

अटल u32 ndisc_hash(स्थिर व्योम *pkey,
		      स्थिर काष्ठा net_device *dev,
		      __u32 *hash_rnd)
अणु
	वापस ndisc_hashfn(pkey, dev, hash_rnd);
पूर्ण

अटल bool ndisc_key_eq(स्थिर काष्ठा neighbour *n, स्थिर व्योम *pkey)
अणु
	वापस neigh_key_eq128(n, pkey);
पूर्ण

अटल पूर्णांक ndisc_स्थिरructor(काष्ठा neighbour *neigh)
अणु
	काष्ठा in6_addr *addr = (काष्ठा in6_addr *)&neigh->primary_key;
	काष्ठा net_device *dev = neigh->dev;
	काष्ठा inet6_dev *in6_dev;
	काष्ठा neigh_parms *parms;
	bool is_multicast = ipv6_addr_is_multicast(addr);

	in6_dev = in6_dev_get(dev);
	अगर (!in6_dev) अणु
		वापस -EINVAL;
	पूर्ण

	parms = in6_dev->nd_parms;
	__neigh_parms_put(neigh->parms);
	neigh->parms = neigh_parms_clone(parms);

	neigh->type = is_multicast ? RTN_MULTICAST : RTN_UNICAST;
	अगर (!dev->header_ops) अणु
		neigh->nud_state = NUD_NOARP;
		neigh->ops = &ndisc_direct_ops;
		neigh->output = neigh_direct_output;
	पूर्ण अन्यथा अणु
		अगर (is_multicast) अणु
			neigh->nud_state = NUD_NOARP;
			ndisc_mc_map(addr, neigh->ha, dev, 1);
		पूर्ण अन्यथा अगर (dev->flags&(IFF_NOARP|IFF_LOOPBACK)) अणु
			neigh->nud_state = NUD_NOARP;
			स_नकल(neigh->ha, dev->dev_addr, dev->addr_len);
			अगर (dev->flags&IFF_LOOPBACK)
				neigh->type = RTN_LOCAL;
		पूर्ण अन्यथा अगर (dev->flags&IFF_POINTOPOINT) अणु
			neigh->nud_state = NUD_NOARP;
			स_नकल(neigh->ha, dev->broadcast, dev->addr_len);
		पूर्ण
		अगर (dev->header_ops->cache)
			neigh->ops = &ndisc_hh_ops;
		अन्यथा
			neigh->ops = &ndisc_generic_ops;
		अगर (neigh->nud_state&NUD_VALID)
			neigh->output = neigh->ops->connected_output;
		अन्यथा
			neigh->output = neigh->ops->output;
	पूर्ण
	in6_dev_put(in6_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक pndisc_स्थिरructor(काष्ठा pneigh_entry *n)
अणु
	काष्ठा in6_addr *addr = (काष्ठा in6_addr *)&n->key;
	काष्ठा in6_addr maddr;
	काष्ठा net_device *dev = n->dev;

	अगर (!dev || !__in6_dev_get(dev))
		वापस -EINVAL;
	addrconf_addr_solict_mult(addr, &maddr);
	ipv6_dev_mc_inc(dev, &maddr);
	वापस 0;
पूर्ण

अटल व्योम pndisc_deकाष्ठाor(काष्ठा pneigh_entry *n)
अणु
	काष्ठा in6_addr *addr = (काष्ठा in6_addr *)&n->key;
	काष्ठा in6_addr maddr;
	काष्ठा net_device *dev = n->dev;

	अगर (!dev || !__in6_dev_get(dev))
		वापस;
	addrconf_addr_solict_mult(addr, &maddr);
	ipv6_dev_mc_dec(dev, &maddr);
पूर्ण

/* called with rtnl held */
अटल bool ndisc_allow_add(स्थिर काष्ठा net_device *dev,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get(dev);

	अगर (!idev || idev->cnf.disable_ipv6) अणु
		NL_SET_ERR_MSG(extack, "IPv6 is disabled on this device");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा sk_buff *ndisc_alloc_skb(काष्ठा net_device *dev,
				       पूर्णांक len)
अणु
	पूर्णांक hlen = LL_RESERVED_SPACE(dev);
	पूर्णांक tlen = dev->needed_tailroom;
	काष्ठा sock *sk = dev_net(dev)->ipv6.ndisc_sk;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(hlen + माप(काष्ठा ipv6hdr) + len + tlen, GFP_ATOMIC);
	अगर (!skb) अणु
		ND_PRINTK(0, err, "ndisc: %s failed to allocate an skb\n",
			  __func__);
		वापस शून्य;
	पूर्ण

	skb->protocol = htons(ETH_P_IPV6);
	skb->dev = dev;

	skb_reserve(skb, hlen + माप(काष्ठा ipv6hdr));
	skb_reset_transport_header(skb);

	/* Manually assign socket ownership as we aव्योम calling
	 * sock_alloc_send_pskb() to bypass wmem buffer limits
	 */
	skb_set_owner_w(skb, sk);

	वापस skb;
पूर्ण

अटल व्योम ip6_nd_hdr(काष्ठा sk_buff *skb,
		       स्थिर काष्ठा in6_addr *saddr,
		       स्थिर काष्ठा in6_addr *daddr,
		       पूर्णांक hop_limit, पूर्णांक len)
अणु
	काष्ठा ipv6hdr *hdr;
	काष्ठा inet6_dev *idev;
	अचिन्हित tclass;

	rcu_पढ़ो_lock();
	idev = __in6_dev_get(skb->dev);
	tclass = idev ? idev->cnf.ndisc_tclass : 0;
	rcu_पढ़ो_unlock();

	skb_push(skb, माप(*hdr));
	skb_reset_network_header(skb);
	hdr = ipv6_hdr(skb);

	ip6_flow_hdr(hdr, tclass, 0);

	hdr->payload_len = htons(len);
	hdr->nexthdr = IPPROTO_ICMPV6;
	hdr->hop_limit = hop_limit;

	hdr->saddr = *saddr;
	hdr->daddr = *daddr;
पूर्ण

अटल व्योम ndisc_send_skb(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा in6_addr *daddr,
			   स्थिर काष्ठा in6_addr *saddr)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा sock *sk = net->ipv6.ndisc_sk;
	काष्ठा inet6_dev *idev;
	पूर्णांक err;
	काष्ठा icmp6hdr *icmp6h = icmp6_hdr(skb);
	u8 type;

	type = icmp6h->icmp6_type;

	अगर (!dst) अणु
		काष्ठा flowi6 fl6;
		पूर्णांक oअगर = skb->dev->अगरindex;

		icmpv6_flow_init(sk, &fl6, type, saddr, daddr, oअगर);
		dst = icmp6_dst_alloc(skb->dev, &fl6);
		अगर (IS_ERR(dst)) अणु
			kमुक्त_skb(skb);
			वापस;
		पूर्ण

		skb_dst_set(skb, dst);
	पूर्ण

	icmp6h->icmp6_cksum = csum_ipv6_magic(saddr, daddr, skb->len,
					      IPPROTO_ICMPV6,
					      csum_partial(icmp6h,
							   skb->len, 0));

	ip6_nd_hdr(skb, saddr, daddr, inet6_sk(sk)->hop_limit, skb->len);

	rcu_पढ़ो_lock();
	idev = __in6_dev_get(dst->dev);
	IP6_UPD_PO_STATS(net, idev, IPSTATS_MIB_OUT, skb->len);

	err = NF_HOOK(NFPROTO_IPV6, NF_INET_LOCAL_OUT,
		      net, sk, skb, शून्य, dst->dev,
		      dst_output);
	अगर (!err) अणु
		ICMP6MSGOUT_INC_STATS(net, idev, type);
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTMSGS);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

व्योम ndisc_send_na(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *daddr,
		   स्थिर काष्ठा in6_addr *solicited_addr,
		   bool router, bool solicited, bool override, bool inc_opt)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा in6_addr पंचांगpaddr;
	काष्ठा inet6_अगरaddr *अगरp;
	स्थिर काष्ठा in6_addr *src_addr;
	काष्ठा nd_msg *msg;
	पूर्णांक optlen = 0;

	/* क्रम anycast or proxy, solicited_addr != src_addr */
	अगरp = ipv6_get_अगरaddr(dev_net(dev), solicited_addr, dev, 1);
	अगर (अगरp) अणु
		src_addr = solicited_addr;
		अगर (अगरp->flags & IFA_F_OPTIMISTIC)
			override = false;
		inc_opt |= अगरp->idev->cnf.क्रमce_tllao;
		in6_अगरa_put(अगरp);
	पूर्ण अन्यथा अणु
		अगर (ipv6_dev_get_saddr(dev_net(dev), dev, daddr,
				       inet6_sk(dev_net(dev)->ipv6.ndisc_sk)->srcprefs,
				       &पंचांगpaddr))
			वापस;
		src_addr = &पंचांगpaddr;
	पूर्ण

	अगर (!dev->addr_len)
		inc_opt = false;
	अगर (inc_opt)
		optlen += ndisc_opt_addr_space(dev,
					       NDISC_NEIGHBOUR_ADVERTISEMENT);

	skb = ndisc_alloc_skb(dev, माप(*msg) + optlen);
	अगर (!skb)
		वापस;

	msg = skb_put(skb, माप(*msg));
	*msg = (काष्ठा nd_msg) अणु
		.icmph = अणु
			.icmp6_type = NDISC_NEIGHBOUR_ADVERTISEMENT,
			.icmp6_router = router,
			.icmp6_solicited = solicited,
			.icmp6_override = override,
		पूर्ण,
		.target = *solicited_addr,
	पूर्ण;

	अगर (inc_opt)
		ndisc_fill_addr_option(skb, ND_OPT_TARGET_LL_ADDR,
				       dev->dev_addr,
				       NDISC_NEIGHBOUR_ADVERTISEMENT);

	ndisc_send_skb(skb, daddr, src_addr);
पूर्ण

अटल व्योम ndisc_send_unsol_na(काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *idev;
	काष्ठा inet6_अगरaddr *अगरa;

	idev = in6_dev_get(dev);
	अगर (!idev)
		वापस;

	पढ़ो_lock_bh(&idev->lock);
	list_क्रम_each_entry(अगरa, &idev->addr_list, अगर_list) अणु
		/* skip tentative addresses until dad completes */
		अगर (अगरa->flags & IFA_F_TENTATIVE &&
		    !(अगरa->flags & IFA_F_OPTIMISTIC))
			जारी;

		ndisc_send_na(dev, &in6addr_linklocal_allnodes, &अगरa->addr,
			      /*router=*/ !!idev->cnf.क्रमwarding,
			      /*solicited=*/ false, /*override=*/ true,
			      /*inc_opt=*/ true);
	पूर्ण
	पढ़ो_unlock_bh(&idev->lock);

	in6_dev_put(idev);
पूर्ण

व्योम ndisc_send_ns(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *solicit,
		   स्थिर काष्ठा in6_addr *daddr, स्थिर काष्ठा in6_addr *saddr,
		   u64 nonce)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा in6_addr addr_buf;
	पूर्णांक inc_opt = dev->addr_len;
	पूर्णांक optlen = 0;
	काष्ठा nd_msg *msg;

	अगर (!saddr) अणु
		अगर (ipv6_get_lladdr(dev, &addr_buf,
				   (IFA_F_TENTATIVE|IFA_F_OPTIMISTIC)))
			वापस;
		saddr = &addr_buf;
	पूर्ण

	अगर (ipv6_addr_any(saddr))
		inc_opt = false;
	अगर (inc_opt)
		optlen += ndisc_opt_addr_space(dev,
					       NDISC_NEIGHBOUR_SOLICITATION);
	अगर (nonce != 0)
		optlen += 8;

	skb = ndisc_alloc_skb(dev, माप(*msg) + optlen);
	अगर (!skb)
		वापस;

	msg = skb_put(skb, माप(*msg));
	*msg = (काष्ठा nd_msg) अणु
		.icmph = अणु
			.icmp6_type = NDISC_NEIGHBOUR_SOLICITATION,
		पूर्ण,
		.target = *solicit,
	पूर्ण;

	अगर (inc_opt)
		ndisc_fill_addr_option(skb, ND_OPT_SOURCE_LL_ADDR,
				       dev->dev_addr,
				       NDISC_NEIGHBOUR_SOLICITATION);
	अगर (nonce != 0) अणु
		u8 *opt = skb_put(skb, 8);

		opt[0] = ND_OPT_NONCE;
		opt[1] = 8 >> 3;
		स_नकल(opt + 2, &nonce, 6);
	पूर्ण

	ndisc_send_skb(skb, daddr, saddr);
पूर्ण

व्योम ndisc_send_rs(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *saddr,
		   स्थिर काष्ठा in6_addr *daddr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rs_msg *msg;
	पूर्णांक send_sllao = dev->addr_len;
	पूर्णांक optlen = 0;

#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	/*
	 * According to section 2.2 of RFC 4429, we must not
	 * send router solicitations with a sllao from
	 * optimistic addresses, but we may send the solicitation
	 * अगर we करोn't include the sllao.  So here we check
	 * अगर our address is optimistic, and अगर so, we
	 * suppress the inclusion of the sllao.
	 */
	अगर (send_sllao) अणु
		काष्ठा inet6_अगरaddr *अगरp = ipv6_get_अगरaddr(dev_net(dev), saddr,
							   dev, 1);
		अगर (अगरp) अणु
			अगर (अगरp->flags & IFA_F_OPTIMISTIC)  अणु
				send_sllao = 0;
			पूर्ण
			in6_अगरa_put(अगरp);
		पूर्ण अन्यथा अणु
			send_sllao = 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (send_sllao)
		optlen += ndisc_opt_addr_space(dev, NDISC_ROUTER_SOLICITATION);

	skb = ndisc_alloc_skb(dev, माप(*msg) + optlen);
	अगर (!skb)
		वापस;

	msg = skb_put(skb, माप(*msg));
	*msg = (काष्ठा rs_msg) अणु
		.icmph = अणु
			.icmp6_type = NDISC_ROUTER_SOLICITATION,
		पूर्ण,
	पूर्ण;

	अगर (send_sllao)
		ndisc_fill_addr_option(skb, ND_OPT_SOURCE_LL_ADDR,
				       dev->dev_addr,
				       NDISC_ROUTER_SOLICITATION);

	ndisc_send_skb(skb, daddr, saddr);
पूर्ण


अटल व्योम ndisc_error_report(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	/*
	 *	"The sender MUST वापस an ICMP
	 *	 destination unreachable"
	 */
	dst_link_failure(skb);
	kमुक्त_skb(skb);
पूर्ण

/* Called with locked neigh: either पढ़ो or both */

अटल व्योम ndisc_solicit(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	काष्ठा in6_addr *saddr = शून्य;
	काष्ठा in6_addr mcaddr;
	काष्ठा net_device *dev = neigh->dev;
	काष्ठा in6_addr *target = (काष्ठा in6_addr *)&neigh->primary_key;
	पूर्णांक probes = atomic_पढ़ो(&neigh->probes);

	अगर (skb && ipv6_chk_addr_and_flags(dev_net(dev), &ipv6_hdr(skb)->saddr,
					   dev, false, 1,
					   IFA_F_TENTATIVE|IFA_F_OPTIMISTIC))
		saddr = &ipv6_hdr(skb)->saddr;
	probes -= NEIGH_VAR(neigh->parms, UCAST_PROBES);
	अगर (probes < 0) अणु
		अगर (!(neigh->nud_state & NUD_VALID)) अणु
			ND_PRINTK(1, dbg,
				  "%s: trying to ucast probe in NUD_INVALID: %pI6\n",
				  __func__, target);
		पूर्ण
		ndisc_send_ns(dev, target, target, saddr, 0);
	पूर्ण अन्यथा अगर ((probes -= NEIGH_VAR(neigh->parms, APP_PROBES)) < 0) अणु
		neigh_app_ns(neigh);
	पूर्ण अन्यथा अणु
		addrconf_addr_solict_mult(target, &mcaddr);
		ndisc_send_ns(dev, target, &mcaddr, saddr, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक pndisc_is_router(स्थिर व्योम *pkey,
			    काष्ठा net_device *dev)
अणु
	काष्ठा pneigh_entry *n;
	पूर्णांक ret = -1;

	पढ़ो_lock_bh(&nd_tbl.lock);
	n = __pneigh_lookup(&nd_tbl, dev_net(dev), pkey, dev);
	अगर (n)
		ret = !!(n->flags & NTF_ROUTER);
	पढ़ो_unlock_bh(&nd_tbl.lock);

	वापस ret;
पूर्ण

व्योम ndisc_update(स्थिर काष्ठा net_device *dev, काष्ठा neighbour *neigh,
		  स्थिर u8 *lladdr, u8 new, u32 flags, u8 icmp6_type,
		  काष्ठा ndisc_options *nकरोpts)
अणु
	neigh_update(neigh, lladdr, new, flags, 0);
	/* report ndisc ops about neighbour update */
	ndisc_ops_update(dev, neigh, flags, icmp6_type, nकरोpts);
पूर्ण

अटल व्योम ndisc_recv_ns(काष्ठा sk_buff *skb)
अणु
	काष्ठा nd_msg *msg = (काष्ठा nd_msg *)skb_transport_header(skb);
	स्थिर काष्ठा in6_addr *saddr = &ipv6_hdr(skb)->saddr;
	स्थिर काष्ठा in6_addr *daddr = &ipv6_hdr(skb)->daddr;
	u8 *lladdr = शून्य;
	u32 nकरोptlen = skb_tail_poपूर्णांकer(skb) - (skb_transport_header(skb) +
				    दुरत्व(काष्ठा nd_msg, opt));
	काष्ठा ndisc_options nकरोpts;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा inet6_अगरaddr *अगरp;
	काष्ठा inet6_dev *idev = शून्य;
	काष्ठा neighbour *neigh;
	पूर्णांक dad = ipv6_addr_any(saddr);
	bool inc;
	पूर्णांक is_router = -1;
	u64 nonce = 0;

	अगर (skb->len < माप(काष्ठा nd_msg)) अणु
		ND_PRINTK(2, warn, "NS: packet too short\n");
		वापस;
	पूर्ण

	अगर (ipv6_addr_is_multicast(&msg->target)) अणु
		ND_PRINTK(2, warn, "NS: multicast target address\n");
		वापस;
	पूर्ण

	/*
	 * RFC2461 7.1.1:
	 * DAD has to be destined क्रम solicited node multicast address.
	 */
	अगर (dad && !ipv6_addr_is_solict_mult(daddr)) अणु
		ND_PRINTK(2, warn, "NS: bad DAD packet (wrong destination)\n");
		वापस;
	पूर्ण

	अगर (!ndisc_parse_options(dev, msg->opt, nकरोptlen, &nकरोpts)) अणु
		ND_PRINTK(2, warn, "NS: invalid ND options\n");
		वापस;
	पूर्ण

	अगर (nकरोpts.nd_opts_src_lladdr) अणु
		lladdr = ndisc_opt_addr_data(nकरोpts.nd_opts_src_lladdr, dev);
		अगर (!lladdr) अणु
			ND_PRINTK(2, warn,
				  "NS: invalid link-layer address length\n");
			वापस;
		पूर्ण

		/* RFC2461 7.1.1:
		 *	If the IP source address is the unspecअगरied address,
		 *	there MUST NOT be source link-layer address option
		 *	in the message.
		 */
		अगर (dad) अणु
			ND_PRINTK(2, warn,
				  "NS: bad DAD packet (link-layer address option)\n");
			वापस;
		पूर्ण
	पूर्ण
	अगर (nकरोpts.nd_opts_nonce && nकरोpts.nd_opts_nonce->nd_opt_len == 1)
		स_नकल(&nonce, (u8 *)(nकरोpts.nd_opts_nonce + 1), 6);

	inc = ipv6_addr_is_multicast(daddr);

	अगरp = ipv6_get_अगरaddr(dev_net(dev), &msg->target, dev, 1);
	अगर (अगरp) अणु
have_अगरp:
		अगर (अगरp->flags & (IFA_F_TENTATIVE|IFA_F_OPTIMISTIC)) अणु
			अगर (dad) अणु
				अगर (nonce != 0 && अगरp->dad_nonce == nonce) अणु
					u8 *np = (u8 *)&nonce;
					/* Matching nonce अगर looped back */
					ND_PRINTK(2, notice,
						  "%s: IPv6 DAD loopback for address %pI6c nonce %pM ignored\n",
						  अगरp->idev->dev->name,
						  &अगरp->addr, np);
					जाओ out;
				पूर्ण
				/*
				 * We are colliding with another node
				 * who is करोing DAD
				 * so fail our DAD process
				 */
				addrconf_dad_failure(skb, अगरp);
				वापस;
			पूर्ण अन्यथा अणु
				/*
				 * This is not a dad solicitation.
				 * If we are an optimistic node,
				 * we should respond.
				 * Otherwise, we should ignore it.
				 */
				अगर (!(अगरp->flags & IFA_F_OPTIMISTIC))
					जाओ out;
			पूर्ण
		पूर्ण

		idev = अगरp->idev;
	पूर्ण अन्यथा अणु
		काष्ठा net *net = dev_net(dev);

		/* perhaps an address on the master device */
		अगर (netअगर_is_l3_slave(dev)) अणु
			काष्ठा net_device *mdev;

			mdev = netdev_master_upper_dev_get_rcu(dev);
			अगर (mdev) अणु
				अगरp = ipv6_get_अगरaddr(net, &msg->target, mdev, 1);
				अगर (अगरp)
					जाओ have_अगरp;
			पूर्ण
		पूर्ण

		idev = in6_dev_get(dev);
		अगर (!idev) अणु
			/* XXX: count this drop? */
			वापस;
		पूर्ण

		अगर (ipv6_chk_acast_addr(net, dev, &msg->target) ||
		    (idev->cnf.क्रमwarding &&
		     (net->ipv6.devconf_all->proxy_ndp || idev->cnf.proxy_ndp) &&
		     (is_router = pndisc_is_router(&msg->target, dev)) >= 0)) अणु
			अगर (!(NEIGH_CB(skb)->flags & LOCALLY_ENQUEUED) &&
			    skb->pkt_type != PACKET_HOST &&
			    inc &&
			    NEIGH_VAR(idev->nd_parms, PROXY_DELAY) != 0) अणु
				/*
				 * क्रम anycast or proxy,
				 * sender should delay its response
				 * by a अक्रमom समय between 0 and
				 * MAX_ANYCAST_DELAY_TIME seconds.
				 * (RFC2461) -- yoshfuji
				 */
				काष्ठा sk_buff *n = skb_clone(skb, GFP_ATOMIC);
				अगर (n)
					pneigh_enqueue(&nd_tbl, idev->nd_parms, n);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा
			जाओ out;
	पूर्ण

	अगर (is_router < 0)
		is_router = idev->cnf.क्रमwarding;

	अगर (dad) अणु
		ndisc_send_na(dev, &in6addr_linklocal_allnodes, &msg->target,
			      !!is_router, false, (अगरp != शून्य), true);
		जाओ out;
	पूर्ण

	अगर (inc)
		NEIGH_CACHE_STAT_INC(&nd_tbl, rcv_probes_mcast);
	अन्यथा
		NEIGH_CACHE_STAT_INC(&nd_tbl, rcv_probes_ucast);

	/*
	 *	update / create cache entry
	 *	क्रम the source address
	 */
	neigh = __neigh_lookup(&nd_tbl, saddr, dev,
			       !inc || lladdr || !dev->addr_len);
	अगर (neigh)
		ndisc_update(dev, neigh, lladdr, NUD_STALE,
			     NEIGH_UPDATE_F_WEAK_OVERRIDE|
			     NEIGH_UPDATE_F_OVERRIDE,
			     NDISC_NEIGHBOUR_SOLICITATION, &nकरोpts);
	अगर (neigh || !dev->header_ops) अणु
		ndisc_send_na(dev, saddr, &msg->target, !!is_router,
			      true, (अगरp != शून्य && inc), inc);
		अगर (neigh)
			neigh_release(neigh);
	पूर्ण

out:
	अगर (अगरp)
		in6_अगरa_put(अगरp);
	अन्यथा
		in6_dev_put(idev);
पूर्ण

अटल व्योम ndisc_recv_na(काष्ठा sk_buff *skb)
अणु
	काष्ठा nd_msg *msg = (काष्ठा nd_msg *)skb_transport_header(skb);
	काष्ठा in6_addr *saddr = &ipv6_hdr(skb)->saddr;
	स्थिर काष्ठा in6_addr *daddr = &ipv6_hdr(skb)->daddr;
	u8 *lladdr = शून्य;
	u32 nकरोptlen = skb_tail_poपूर्णांकer(skb) - (skb_transport_header(skb) +
				    दुरत्व(काष्ठा nd_msg, opt));
	काष्ठा ndisc_options nकरोpts;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा inet6_dev *idev = __in6_dev_get(dev);
	काष्ठा inet6_अगरaddr *अगरp;
	काष्ठा neighbour *neigh;

	अगर (skb->len < माप(काष्ठा nd_msg)) अणु
		ND_PRINTK(2, warn, "NA: packet too short\n");
		वापस;
	पूर्ण

	अगर (ipv6_addr_is_multicast(&msg->target)) अणु
		ND_PRINTK(2, warn, "NA: target address is multicast\n");
		वापस;
	पूर्ण

	अगर (ipv6_addr_is_multicast(daddr) &&
	    msg->icmph.icmp6_solicited) अणु
		ND_PRINTK(2, warn, "NA: solicited NA is multicasted\n");
		वापस;
	पूर्ण

	/* For some 802.11 wireless deployments (and possibly other networks),
	 * there will be a NA proxy and unsolicitd packets are attacks
	 * and thus should not be accepted.
	 */
	अगर (!msg->icmph.icmp6_solicited && idev &&
	    idev->cnf.drop_unsolicited_na)
		वापस;

	अगर (!ndisc_parse_options(dev, msg->opt, nकरोptlen, &nकरोpts)) अणु
		ND_PRINTK(2, warn, "NS: invalid ND option\n");
		वापस;
	पूर्ण
	अगर (nकरोpts.nd_opts_tgt_lladdr) अणु
		lladdr = ndisc_opt_addr_data(nकरोpts.nd_opts_tgt_lladdr, dev);
		अगर (!lladdr) अणु
			ND_PRINTK(2, warn,
				  "NA: invalid link-layer address length\n");
			वापस;
		पूर्ण
	पूर्ण
	अगरp = ipv6_get_अगरaddr(dev_net(dev), &msg->target, dev, 1);
	अगर (अगरp) अणु
		अगर (skb->pkt_type != PACKET_LOOPBACK
		    && (अगरp->flags & IFA_F_TENTATIVE)) अणु
				addrconf_dad_failure(skb, अगरp);
				वापस;
		पूर्ण
		/* What should we make now? The advertisement
		   is invalid, but ndisc specs say nothing
		   about it. It could be misconfiguration, or
		   an smart proxy agent tries to help us :-)

		   We should not prपूर्णांक the error अगर NA has been
		   received from loopback - it is just our own
		   unsolicited advertisement.
		 */
		अगर (skb->pkt_type != PACKET_LOOPBACK)
			ND_PRINTK(1, warn,
				  "NA: %pM advertised our address %pI6c on %s!\n",
				  eth_hdr(skb)->h_source, &अगरp->addr, अगरp->idev->dev->name);
		in6_अगरa_put(अगरp);
		वापस;
	पूर्ण
	neigh = neigh_lookup(&nd_tbl, &msg->target, dev);

	अगर (neigh) अणु
		u8 old_flags = neigh->flags;
		काष्ठा net *net = dev_net(dev);

		अगर (neigh->nud_state & NUD_FAILED)
			जाओ out;

		/*
		 * Don't update the neighbor cache entry on a proxy NA from
		 * ourselves because either the proxied node is off link or it
		 * has alपढ़ोy sent a NA to us.
		 */
		अगर (lladdr && !स_भेद(lladdr, dev->dev_addr, dev->addr_len) &&
		    net->ipv6.devconf_all->क्रमwarding && net->ipv6.devconf_all->proxy_ndp &&
		    pneigh_lookup(&nd_tbl, net, &msg->target, dev, 0)) अणु
			/* XXX: idev->cnf.proxy_ndp */
			जाओ out;
		पूर्ण

		ndisc_update(dev, neigh, lladdr,
			     msg->icmph.icmp6_solicited ? NUD_REACHABLE : NUD_STALE,
			     NEIGH_UPDATE_F_WEAK_OVERRIDE|
			     (msg->icmph.icmp6_override ? NEIGH_UPDATE_F_OVERRIDE : 0)|
			     NEIGH_UPDATE_F_OVERRIDE_ISROUTER|
			     (msg->icmph.icmp6_router ? NEIGH_UPDATE_F_ISROUTER : 0),
			     NDISC_NEIGHBOUR_ADVERTISEMENT, &nकरोpts);

		अगर ((old_flags & ~neigh->flags) & NTF_ROUTER) अणु
			/*
			 * Change: router to host
			 */
			rt6_clean_tohost(dev_net(dev),  saddr);
		पूर्ण

out:
		neigh_release(neigh);
	पूर्ण
पूर्ण

अटल व्योम ndisc_recv_rs(काष्ठा sk_buff *skb)
अणु
	काष्ठा rs_msg *rs_msg = (काष्ठा rs_msg *)skb_transport_header(skb);
	अचिन्हित दीर्घ nकरोptlen = skb->len - माप(*rs_msg);
	काष्ठा neighbour *neigh;
	काष्ठा inet6_dev *idev;
	स्थिर काष्ठा in6_addr *saddr = &ipv6_hdr(skb)->saddr;
	काष्ठा ndisc_options nकरोpts;
	u8 *lladdr = शून्य;

	अगर (skb->len < माप(*rs_msg))
		वापस;

	idev = __in6_dev_get(skb->dev);
	अगर (!idev) अणु
		ND_PRINTK(1, err, "RS: can't find in6 device\n");
		वापस;
	पूर्ण

	/* Don't accept RS if we're not in router mode */
	अगर (!idev->cnf.क्रमwarding)
		जाओ out;

	/*
	 * Don't update NCE अगर src = ::;
	 * this implies that the source node has no ip address asचिन्हित yet.
	 */
	अगर (ipv6_addr_any(saddr))
		जाओ out;

	/* Parse ND options */
	अगर (!ndisc_parse_options(skb->dev, rs_msg->opt, nकरोptlen, &nकरोpts)) अणु
		ND_PRINTK(2, notice, "NS: invalid ND option, ignored\n");
		जाओ out;
	पूर्ण

	अगर (nकरोpts.nd_opts_src_lladdr) अणु
		lladdr = ndisc_opt_addr_data(nकरोpts.nd_opts_src_lladdr,
					     skb->dev);
		अगर (!lladdr)
			जाओ out;
	पूर्ण

	neigh = __neigh_lookup(&nd_tbl, saddr, skb->dev, 1);
	अगर (neigh) अणु
		ndisc_update(skb->dev, neigh, lladdr, NUD_STALE,
			     NEIGH_UPDATE_F_WEAK_OVERRIDE|
			     NEIGH_UPDATE_F_OVERRIDE|
			     NEIGH_UPDATE_F_OVERRIDE_ISROUTER,
			     NDISC_ROUTER_SOLICITATION, &nकरोpts);
		neigh_release(neigh);
	पूर्ण
out:
	वापस;
पूर्ण

अटल व्योम ndisc_ra_useropt(काष्ठा sk_buff *ra, काष्ठा nd_opt_hdr *opt)
अणु
	काष्ठा icmp6hdr *icmp6h = (काष्ठा icmp6hdr *)skb_transport_header(ra);
	काष्ठा sk_buff *skb;
	काष्ठा nlmsghdr *nlh;
	काष्ठा nduseropपंचांगsg *ndmsg;
	काष्ठा net *net = dev_net(ra->dev);
	पूर्णांक err;
	पूर्णांक base_size = NLMSG_ALIGN(माप(काष्ठा nduseropपंचांगsg)
				    + (opt->nd_opt_len << 3));
	माप_प्रकार msg_size = base_size + nla_total_size(माप(काष्ठा in6_addr));

	skb = nlmsg_new(msg_size, GFP_ATOMIC);
	अगर (!skb) अणु
		err = -ENOBUFS;
		जाओ errout;
	पूर्ण

	nlh = nlmsg_put(skb, 0, 0, RTM_NEWNDUSEROPT, base_size, 0);
	अगर (!nlh) अणु
		जाओ nla_put_failure;
	पूर्ण

	ndmsg = nlmsg_data(nlh);
	ndmsg->nduseropt_family = AF_INET6;
	ndmsg->nduseropt_अगरindex = ra->dev->अगरindex;
	ndmsg->nduseropt_icmp_type = icmp6h->icmp6_type;
	ndmsg->nduseropt_icmp_code = icmp6h->icmp6_code;
	ndmsg->nduseropt_opts_len = opt->nd_opt_len << 3;

	स_नकल(ndmsg + 1, opt, opt->nd_opt_len << 3);

	अगर (nla_put_in6_addr(skb, NDUSEROPT_SRCADDR, &ipv6_hdr(ra)->saddr))
		जाओ nla_put_failure;
	nlmsg_end(skb, nlh);

	rtnl_notअगरy(skb, net, 0, RTNLGRP_ND_USEROPT, शून्य, GFP_ATOMIC);
	वापस;

nla_put_failure:
	nlmsg_मुक्त(skb);
	err = -EMSGSIZE;
errout:
	rtnl_set_sk_err(net, RTNLGRP_ND_USEROPT, err);
पूर्ण

अटल व्योम ndisc_router_discovery(काष्ठा sk_buff *skb)
अणु
	काष्ठा ra_msg *ra_msg = (काष्ठा ra_msg *)skb_transport_header(skb);
	काष्ठा neighbour *neigh = शून्य;
	काष्ठा inet6_dev *in6_dev;
	काष्ठा fib6_info *rt = शून्य;
	u32 defrtr_usr_metric;
	काष्ठा net *net;
	पूर्णांक lअगरeसमय;
	काष्ठा ndisc_options nकरोpts;
	पूर्णांक optlen;
	अचिन्हित पूर्णांक pref = 0;
	__u32 old_अगर_flags;
	bool send_अगरinfo_notअगरy = false;

	__u8 *opt = (__u8 *)(ra_msg + 1);

	optlen = (skb_tail_poपूर्णांकer(skb) - skb_transport_header(skb)) -
		माप(काष्ठा ra_msg);

	ND_PRINTK(2, info,
		  "RA: %s, dev: %s\n",
		  __func__, skb->dev->name);
	अगर (!(ipv6_addr_type(&ipv6_hdr(skb)->saddr) & IPV6_ADDR_LINKLOCAL)) अणु
		ND_PRINTK(2, warn, "RA: source address is not link-local\n");
		वापस;
	पूर्ण
	अगर (optlen < 0) अणु
		ND_PRINTK(2, warn, "RA: packet too short\n");
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_IPV6_NDISC_NODETYPE
	अगर (skb->ndisc_nodetype == NDISC_NODETYPE_HOST) अणु
		ND_PRINTK(2, warn, "RA: from host or unauthorized router\n");
		वापस;
	पूर्ण
#पूर्ण_अगर

	/*
	 *	set the RA_RECV flag in the पूर्णांकerface
	 */

	in6_dev = __in6_dev_get(skb->dev);
	अगर (!in6_dev) अणु
		ND_PRINTK(0, err, "RA: can't find inet6 device for %s\n",
			  skb->dev->name);
		वापस;
	पूर्ण

	अगर (!ndisc_parse_options(skb->dev, opt, optlen, &nकरोpts)) अणु
		ND_PRINTK(2, warn, "RA: invalid ND options\n");
		वापस;
	पूर्ण

	अगर (!ipv6_accept_ra(in6_dev)) अणु
		ND_PRINTK(2, info,
			  "RA: %s, did not accept ra for dev: %s\n",
			  __func__, skb->dev->name);
		जाओ skip_linkparms;
	पूर्ण

#अगर_घोषित CONFIG_IPV6_NDISC_NODETYPE
	/* skip link-specअगरic parameters from पूर्णांकerior routers */
	अगर (skb->ndisc_nodetype == NDISC_NODETYPE_NODEFAULT) अणु
		ND_PRINTK(2, info,
			  "RA: %s, nodetype is NODEFAULT, dev: %s\n",
			  __func__, skb->dev->name);
		जाओ skip_linkparms;
	पूर्ण
#पूर्ण_अगर

	अगर (in6_dev->अगर_flags & IF_RS_SENT) अणु
		/*
		 *	flag that an RA was received after an RS was sent
		 *	out on this पूर्णांकerface.
		 */
		in6_dev->अगर_flags |= IF_RA_RCVD;
	पूर्ण

	/*
	 * Remember the managed/otherconf flags from most recently
	 * received RA message (RFC 2462) -- yoshfuji
	 */
	old_अगर_flags = in6_dev->अगर_flags;
	in6_dev->अगर_flags = (in6_dev->अगर_flags & ~(IF_RA_MANAGED |
				IF_RA_OTHERCONF)) |
				(ra_msg->icmph.icmp6_addrconf_managed ?
					IF_RA_MANAGED : 0) |
				(ra_msg->icmph.icmp6_addrconf_other ?
					IF_RA_OTHERCONF : 0);

	अगर (old_अगर_flags != in6_dev->अगर_flags)
		send_अगरinfo_notअगरy = true;

	अगर (!in6_dev->cnf.accept_ra_defrtr) अणु
		ND_PRINTK(2, info,
			  "RA: %s, defrtr is false for dev: %s\n",
			  __func__, skb->dev->name);
		जाओ skip_defrtr;
	पूर्ण

	/* Do not accept RA with source-addr found on local machine unless
	 * accept_ra_from_local is set to true.
	 */
	net = dev_net(in6_dev->dev);
	अगर (!in6_dev->cnf.accept_ra_from_local &&
	    ipv6_chk_addr(net, &ipv6_hdr(skb)->saddr, in6_dev->dev, 0)) अणु
		ND_PRINTK(2, info,
			  "RA from local address detected on dev: %s: default router ignored\n",
			  skb->dev->name);
		जाओ skip_defrtr;
	पूर्ण

	lअगरeसमय = ntohs(ra_msg->icmph.icmp6_rt_lअगरeसमय);

#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
	pref = ra_msg->icmph.icmp6_router_pref;
	/* 10b is handled as अगर it were 00b (medium) */
	अगर (pref == ICMPV6_ROUTER_PREF_INVALID ||
	    !in6_dev->cnf.accept_ra_rtr_pref)
		pref = ICMPV6_ROUTER_PREF_MEDIUM;
#पूर्ण_अगर
	/* routes added from RAs करो not use nexthop objects */
	rt = rt6_get_dflt_router(net, &ipv6_hdr(skb)->saddr, skb->dev);
	अगर (rt) अणु
		neigh = ip6_neigh_lookup(&rt->fib6_nh->fib_nh_gw6,
					 rt->fib6_nh->fib_nh_dev, शून्य,
					  &ipv6_hdr(skb)->saddr);
		अगर (!neigh) अणु
			ND_PRINTK(0, err,
				  "RA: %s got default router without neighbour\n",
				  __func__);
			fib6_info_release(rt);
			वापस;
		पूर्ण
	पूर्ण
	/* Set शेष route metric as specअगरied by user */
	defrtr_usr_metric = in6_dev->cnf.ra_defrtr_metric;
	/* delete the route अगर lअगरeसमय is 0 or अगर metric needs change */
	अगर (rt && (lअगरeसमय == 0 || rt->fib6_metric != defrtr_usr_metric)) अणु
		ip6_del_rt(net, rt, false);
		rt = शून्य;
	पूर्ण

	ND_PRINTK(3, info, "RA: rt: %p  lifetime: %d, metric: %d, for dev: %s\n",
		  rt, lअगरeसमय, defrtr_usr_metric, skb->dev->name);
	अगर (!rt && lअगरeसमय) अणु
		ND_PRINTK(3, info, "RA: adding default router\n");

		rt = rt6_add_dflt_router(net, &ipv6_hdr(skb)->saddr,
					 skb->dev, pref, defrtr_usr_metric);
		अगर (!rt) अणु
			ND_PRINTK(0, err,
				  "RA: %s failed to add default route\n",
				  __func__);
			वापस;
		पूर्ण

		neigh = ip6_neigh_lookup(&rt->fib6_nh->fib_nh_gw6,
					 rt->fib6_nh->fib_nh_dev, शून्य,
					  &ipv6_hdr(skb)->saddr);
		अगर (!neigh) अणु
			ND_PRINTK(0, err,
				  "RA: %s got default router without neighbour\n",
				  __func__);
			fib6_info_release(rt);
			वापस;
		पूर्ण
		neigh->flags |= NTF_ROUTER;
	पूर्ण अन्यथा अगर (rt) अणु
		rt->fib6_flags = (rt->fib6_flags & ~RTF_PREF_MASK) | RTF_PREF(pref);
	पूर्ण

	अगर (rt)
		fib6_set_expires(rt, jअगरfies + (HZ * lअगरeसमय));
	अगर (in6_dev->cnf.accept_ra_min_hop_limit < 256 &&
	    ra_msg->icmph.icmp6_hop_limit) अणु
		अगर (in6_dev->cnf.accept_ra_min_hop_limit <= ra_msg->icmph.icmp6_hop_limit) अणु
			in6_dev->cnf.hop_limit = ra_msg->icmph.icmp6_hop_limit;
			fib6_metric_set(rt, RTAX_HOPLIMIT,
					ra_msg->icmph.icmp6_hop_limit);
		पूर्ण अन्यथा अणु
			ND_PRINTK(2, warn, "RA: Got route advertisement with lower hop_limit than minimum\n");
		पूर्ण
	पूर्ण

skip_defrtr:

	/*
	 *	Update Reachable Time and Retrans Timer
	 */

	अगर (in6_dev->nd_parms) अणु
		अचिन्हित दीर्घ rसमय = ntohl(ra_msg->retrans_समयr);

		अगर (rसमय && rसमय/1000 < MAX_SCHEDULE_TIMEOUT/HZ) अणु
			rसमय = (rसमय*HZ)/1000;
			अगर (rसमय < HZ/100)
				rसमय = HZ/100;
			NEIGH_VAR_SET(in6_dev->nd_parms, RETRANS_TIME, rसमय);
			in6_dev->tstamp = jअगरfies;
			send_अगरinfo_notअगरy = true;
		पूर्ण

		rसमय = ntohl(ra_msg->reachable_समय);
		अगर (rसमय && rसमय/1000 < MAX_SCHEDULE_TIMEOUT/(3*HZ)) अणु
			rसमय = (rसमय*HZ)/1000;

			अगर (rसमय < HZ/10)
				rसमय = HZ/10;

			अगर (rसमय != NEIGH_VAR(in6_dev->nd_parms, BASE_REACHABLE_TIME)) अणु
				NEIGH_VAR_SET(in6_dev->nd_parms,
					      BASE_REACHABLE_TIME, rसमय);
				NEIGH_VAR_SET(in6_dev->nd_parms,
					      GC_STALETIME, 3 * rसमय);
				in6_dev->nd_parms->reachable_समय = neigh_अक्रम_reach_समय(rसमय);
				in6_dev->tstamp = jअगरfies;
				send_अगरinfo_notअगरy = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 *	Send a notअगरy अगर RA changed managed/otherconf flags or समयr settings
	 */
	अगर (send_अगरinfo_notअगरy)
		inet6_अगरinfo_notअगरy(RTM_NEWLINK, in6_dev);

skip_linkparms:

	/*
	 *	Process options.
	 */

	अगर (!neigh)
		neigh = __neigh_lookup(&nd_tbl, &ipv6_hdr(skb)->saddr,
				       skb->dev, 1);
	अगर (neigh) अणु
		u8 *lladdr = शून्य;
		अगर (nकरोpts.nd_opts_src_lladdr) अणु
			lladdr = ndisc_opt_addr_data(nकरोpts.nd_opts_src_lladdr,
						     skb->dev);
			अगर (!lladdr) अणु
				ND_PRINTK(2, warn,
					  "RA: invalid link-layer address length\n");
				जाओ out;
			पूर्ण
		पूर्ण
		ndisc_update(skb->dev, neigh, lladdr, NUD_STALE,
			     NEIGH_UPDATE_F_WEAK_OVERRIDE|
			     NEIGH_UPDATE_F_OVERRIDE|
			     NEIGH_UPDATE_F_OVERRIDE_ISROUTER|
			     NEIGH_UPDATE_F_ISROUTER,
			     NDISC_ROUTER_ADVERTISEMENT, &nकरोpts);
	पूर्ण

	अगर (!ipv6_accept_ra(in6_dev)) अणु
		ND_PRINTK(2, info,
			  "RA: %s, accept_ra is false for dev: %s\n",
			  __func__, skb->dev->name);
		जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
	अगर (!in6_dev->cnf.accept_ra_from_local &&
	    ipv6_chk_addr(dev_net(in6_dev->dev), &ipv6_hdr(skb)->saddr,
			  in6_dev->dev, 0)) अणु
		ND_PRINTK(2, info,
			  "RA from local address detected on dev: %s: router info ignored.\n",
			  skb->dev->name);
		जाओ skip_routeinfo;
	पूर्ण

	अगर (in6_dev->cnf.accept_ra_rtr_pref && nकरोpts.nd_opts_ri) अणु
		काष्ठा nd_opt_hdr *p;
		क्रम (p = nकरोpts.nd_opts_ri;
		     p;
		     p = ndisc_next_option(p, nकरोpts.nd_opts_ri_end)) अणु
			काष्ठा route_info *ri = (काष्ठा route_info *)p;
#अगर_घोषित CONFIG_IPV6_NDISC_NODETYPE
			अगर (skb->ndisc_nodetype == NDISC_NODETYPE_NODEFAULT &&
			    ri->prefix_len == 0)
				जारी;
#पूर्ण_अगर
			अगर (ri->prefix_len == 0 &&
			    !in6_dev->cnf.accept_ra_defrtr)
				जारी;
			अगर (ri->prefix_len < in6_dev->cnf.accept_ra_rt_info_min_plen)
				जारी;
			अगर (ri->prefix_len > in6_dev->cnf.accept_ra_rt_info_max_plen)
				जारी;
			rt6_route_rcv(skb->dev, (u8 *)p, (p->nd_opt_len) << 3,
				      &ipv6_hdr(skb)->saddr);
		पूर्ण
	पूर्ण

skip_routeinfo:
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPV6_NDISC_NODETYPE
	/* skip link-specअगरic nकरोpts from पूर्णांकerior routers */
	अगर (skb->ndisc_nodetype == NDISC_NODETYPE_NODEFAULT) अणु
		ND_PRINTK(2, info,
			  "RA: %s, nodetype is NODEFAULT (interior routes), dev: %s\n",
			  __func__, skb->dev->name);
		जाओ out;
	पूर्ण
#पूर्ण_अगर

	अगर (in6_dev->cnf.accept_ra_pinfo && nकरोpts.nd_opts_pi) अणु
		काष्ठा nd_opt_hdr *p;
		क्रम (p = nकरोpts.nd_opts_pi;
		     p;
		     p = ndisc_next_option(p, nकरोpts.nd_opts_pi_end)) अणु
			addrconf_prefix_rcv(skb->dev, (u8 *)p,
					    (p->nd_opt_len) << 3,
					    nकरोpts.nd_opts_src_lladdr != शून्य);
		पूर्ण
	पूर्ण

	अगर (nकरोpts.nd_opts_mtu && in6_dev->cnf.accept_ra_mtu) अणु
		__be32 n;
		u32 mtu;

		स_नकल(&n, ((u8 *)(nकरोpts.nd_opts_mtu+1))+2, माप(mtu));
		mtu = ntohl(n);

		अगर (mtu < IPV6_MIN_MTU || mtu > skb->dev->mtu) अणु
			ND_PRINTK(2, warn, "RA: invalid mtu: %d\n", mtu);
		पूर्ण अन्यथा अगर (in6_dev->cnf.mtu6 != mtu) अणु
			in6_dev->cnf.mtu6 = mtu;
			fib6_metric_set(rt, RTAX_MTU, mtu);
			rt6_mtu_change(skb->dev, mtu);
		पूर्ण
	पूर्ण

	अगर (nकरोpts.nd_useropts) अणु
		काष्ठा nd_opt_hdr *p;
		क्रम (p = nकरोpts.nd_useropts;
		     p;
		     p = ndisc_next_useropt(skb->dev, p,
					    nकरोpts.nd_useropts_end)) अणु
			ndisc_ra_useropt(skb, p);
		पूर्ण
	पूर्ण

	अगर (nकरोpts.nd_opts_tgt_lladdr || nकरोpts.nd_opts_rh) अणु
		ND_PRINTK(2, warn, "RA: invalid RA options\n");
	पूर्ण
out:
	fib6_info_release(rt);
	अगर (neigh)
		neigh_release(neigh);
पूर्ण

अटल व्योम ndisc_redirect_rcv(काष्ठा sk_buff *skb)
अणु
	u8 *hdr;
	काष्ठा ndisc_options nकरोpts;
	काष्ठा rd_msg *msg = (काष्ठा rd_msg *)skb_transport_header(skb);
	u32 nकरोptlen = skb_tail_poपूर्णांकer(skb) - (skb_transport_header(skb) +
				    दुरत्व(काष्ठा rd_msg, opt));

#अगर_घोषित CONFIG_IPV6_NDISC_NODETYPE
	चयन (skb->ndisc_nodetype) अणु
	हाल NDISC_NODETYPE_HOST:
	हाल NDISC_NODETYPE_NODEFAULT:
		ND_PRINTK(2, warn,
			  "Redirect: from host or unauthorized router\n");
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (!(ipv6_addr_type(&ipv6_hdr(skb)->saddr) & IPV6_ADDR_LINKLOCAL)) अणु
		ND_PRINTK(2, warn,
			  "Redirect: source address is not link-local\n");
		वापस;
	पूर्ण

	अगर (!ndisc_parse_options(skb->dev, msg->opt, nकरोptlen, &nकरोpts))
		वापस;

	अगर (!nकरोpts.nd_opts_rh) अणु
		ip6_redirect_no_header(skb, dev_net(skb->dev),
					skb->dev->अगरindex);
		वापस;
	पूर्ण

	hdr = (u8 *)nकरोpts.nd_opts_rh;
	hdr += 8;
	अगर (!pskb_pull(skb, hdr - skb_transport_header(skb)))
		वापस;

	icmpv6_notअगरy(skb, NDISC_REसूचीECT, 0, 0);
पूर्ण

अटल व्योम ndisc_fill_redirect_hdr_option(काष्ठा sk_buff *skb,
					   काष्ठा sk_buff *orig_skb,
					   पूर्णांक rd_len)
अणु
	u8 *opt = skb_put(skb, rd_len);

	स_रखो(opt, 0, 8);
	*(opt++) = ND_OPT_REसूचीECT_HDR;
	*(opt++) = (rd_len >> 3);
	opt += 6;

	skb_copy_bits(orig_skb, skb_network_offset(orig_skb), opt,
		      rd_len - 8);
पूर्ण

व्योम ndisc_send_redirect(काष्ठा sk_buff *skb, स्थिर काष्ठा in6_addr *target)
अणु
	काष्ठा net_device *dev = skb->dev;
	काष्ठा net *net = dev_net(dev);
	काष्ठा sock *sk = net->ipv6.ndisc_sk;
	पूर्णांक optlen = 0;
	काष्ठा inet_peer *peer;
	काष्ठा sk_buff *buff;
	काष्ठा rd_msg *msg;
	काष्ठा in6_addr saddr_buf;
	काष्ठा rt6_info *rt;
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6;
	पूर्णांक rd_len;
	u8 ha_buf[MAX_ADDR_LEN], *ha = शून्य,
	   ops_data_buf[NDISC_OPS_REसूचीECT_DATA_SPACE], *ops_data = शून्य;
	bool ret;

	अगर (netअगर_is_l3_master(skb->dev)) अणु
		dev = __dev_get_by_index(dev_net(skb->dev), IPCB(skb)->iअगर);
		अगर (!dev)
			वापस;
	पूर्ण

	अगर (ipv6_get_lladdr(dev, &saddr_buf, IFA_F_TENTATIVE)) अणु
		ND_PRINTK(2, warn, "Redirect: no link-local address on %s\n",
			  dev->name);
		वापस;
	पूर्ण

	अगर (!ipv6_addr_equal(&ipv6_hdr(skb)->daddr, target) &&
	    ipv6_addr_type(target) != (IPV6_ADDR_UNICAST|IPV6_ADDR_LINKLOCAL)) अणु
		ND_PRINTK(2, warn,
			  "Redirect: target address is not link-local unicast\n");
		वापस;
	पूर्ण

	icmpv6_flow_init(sk, &fl6, NDISC_REसूचीECT,
			 &saddr_buf, &ipv6_hdr(skb)->saddr, dev->अगरindex);

	dst = ip6_route_output(net, शून्य, &fl6);
	अगर (dst->error) अणु
		dst_release(dst);
		वापस;
	पूर्ण
	dst = xfrm_lookup(net, dst, flowi6_to_flowi(&fl6), शून्य, 0);
	अगर (IS_ERR(dst))
		वापस;

	rt = (काष्ठा rt6_info *) dst;

	अगर (rt->rt6i_flags & RTF_GATEWAY) अणु
		ND_PRINTK(2, warn,
			  "Redirect: destination is not a neighbour\n");
		जाओ release;
	पूर्ण
	peer = inet_getpeer_v6(net->ipv6.peers, &ipv6_hdr(skb)->saddr, 1);
	ret = inet_peer_xrlim_allow(peer, 1*HZ);
	अगर (peer)
		inet_putpeer(peer);
	अगर (!ret)
		जाओ release;

	अगर (dev->addr_len) अणु
		काष्ठा neighbour *neigh = dst_neigh_lookup(skb_dst(skb), target);
		अगर (!neigh) अणु
			ND_PRINTK(2, warn,
				  "Redirect: no neigh for target address\n");
			जाओ release;
		पूर्ण

		पढ़ो_lock_bh(&neigh->lock);
		अगर (neigh->nud_state & NUD_VALID) अणु
			स_नकल(ha_buf, neigh->ha, dev->addr_len);
			पढ़ो_unlock_bh(&neigh->lock);
			ha = ha_buf;
			optlen += ndisc_redirect_opt_addr_space(dev, neigh,
								ops_data_buf,
								&ops_data);
		पूर्ण अन्यथा
			पढ़ो_unlock_bh(&neigh->lock);

		neigh_release(neigh);
	पूर्ण

	rd_len = min_t(अचिन्हित पूर्णांक,
		       IPV6_MIN_MTU - माप(काष्ठा ipv6hdr) - माप(*msg) - optlen,
		       skb->len + 8);
	rd_len &= ~0x7;
	optlen += rd_len;

	buff = ndisc_alloc_skb(dev, माप(*msg) + optlen);
	अगर (!buff)
		जाओ release;

	msg = skb_put(buff, माप(*msg));
	*msg = (काष्ठा rd_msg) अणु
		.icmph = अणु
			.icmp6_type = NDISC_REसूचीECT,
		पूर्ण,
		.target = *target,
		.dest = ipv6_hdr(skb)->daddr,
	पूर्ण;

	/*
	 *	include target_address option
	 */

	अगर (ha)
		ndisc_fill_redirect_addr_option(buff, ha, ops_data);

	/*
	 *	build redirect option and copy skb over to the new packet.
	 */

	अगर (rd_len)
		ndisc_fill_redirect_hdr_option(buff, skb, rd_len);

	skb_dst_set(buff, dst);
	ndisc_send_skb(buff, &ipv6_hdr(skb)->saddr, &saddr_buf);
	वापस;

release:
	dst_release(dst);
पूर्ण

अटल व्योम pndisc_reकरो(काष्ठा sk_buff *skb)
अणु
	ndisc_recv_ns(skb);
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक ndisc_is_multicast(स्थिर व्योम *pkey)
अणु
	वापस ipv6_addr_is_multicast((काष्ठा in6_addr *)pkey);
पूर्ण

अटल bool ndisc_suppress_frag_ndisc(काष्ठा sk_buff *skb)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get(skb->dev);

	अगर (!idev)
		वापस true;
	अगर (IP6CB(skb)->flags & IP6SKB_FRAGMENTED &&
	    idev->cnf.suppress_frag_ndisc) अणु
		net_warn_ratelimited("Received fragmented ndisc packet. Carefully consider disabling suppress_frag_ndisc.\n");
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक ndisc_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा nd_msg *msg;

	अगर (ndisc_suppress_frag_ndisc(skb))
		वापस 0;

	अगर (skb_linearize(skb))
		वापस 0;

	msg = (काष्ठा nd_msg *)skb_transport_header(skb);

	__skb_push(skb, skb->data - skb_transport_header(skb));

	अगर (ipv6_hdr(skb)->hop_limit != 255) अणु
		ND_PRINTK(2, warn, "NDISC: invalid hop-limit: %d\n",
			  ipv6_hdr(skb)->hop_limit);
		वापस 0;
	पूर्ण

	अगर (msg->icmph.icmp6_code != 0) अणु
		ND_PRINTK(2, warn, "NDISC: invalid ICMPv6 code: %d\n",
			  msg->icmph.icmp6_code);
		वापस 0;
	पूर्ण

	चयन (msg->icmph.icmp6_type) अणु
	हाल NDISC_NEIGHBOUR_SOLICITATION:
		स_रखो(NEIGH_CB(skb), 0, माप(काष्ठा neighbour_cb));
		ndisc_recv_ns(skb);
		अवरोध;

	हाल NDISC_NEIGHBOUR_ADVERTISEMENT:
		ndisc_recv_na(skb);
		अवरोध;

	हाल NDISC_ROUTER_SOLICITATION:
		ndisc_recv_rs(skb);
		अवरोध;

	हाल NDISC_ROUTER_ADVERTISEMENT:
		ndisc_router_discovery(skb);
		अवरोध;

	हाल NDISC_REसूचीECT:
		ndisc_redirect_rcv(skb);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ndisc_netdev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_notअगरier_change_info *change_info;
	काष्ठा net *net = dev_net(dev);
	काष्ठा inet6_dev *idev;

	चयन (event) अणु
	हाल NETDEV_CHANGEADDR:
		neigh_changeaddr(&nd_tbl, dev);
		fib6_run_gc(0, net, false);
		fallthrough;
	हाल NETDEV_UP:
		idev = in6_dev_get(dev);
		अगर (!idev)
			अवरोध;
		अगर (idev->cnf.ndisc_notअगरy ||
		    net->ipv6.devconf_all->ndisc_notअगरy)
			ndisc_send_unsol_na(dev);
		in6_dev_put(idev);
		अवरोध;
	हाल NETDEV_CHANGE:
		change_info = ptr;
		अगर (change_info->flags_changed & IFF_NOARP)
			neigh_changeaddr(&nd_tbl, dev);
		अगर (!netअगर_carrier_ok(dev))
			neigh_carrier_करोwn(&nd_tbl, dev);
		अवरोध;
	हाल NETDEV_DOWN:
		neigh_अगरकरोwn(&nd_tbl, dev);
		fib6_run_gc(0, net, false);
		अवरोध;
	हाल NETDEV_NOTIFY_PEERS:
		ndisc_send_unsol_na(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ndisc_netdev_notअगरier = अणु
	.notअगरier_call = ndisc_netdev_event,
	.priority = ADDRCONF_NOTIFY_PRIORITY - 5,
पूर्ण;

#अगर_घोषित CONFIG_SYSCTL
अटल व्योम ndisc_warn_deprecated_sysctl(काष्ठा ctl_table *ctl,
					 स्थिर अक्षर *func, स्थिर अक्षर *dev_name)
अणु
	अटल अक्षर warncomm[TASK_COMM_LEN];
	अटल पूर्णांक warned;
	अगर (म_भेद(warncomm, current->comm) && warned < 5) अणु
		म_नकल(warncomm, current->comm);
		pr_warn("process `%s' is using deprecated sysctl (%s) net.ipv6.neigh.%s.%s - use net.ipv6.neigh.%s.%s_ms instead\n",
			warncomm, func,
			dev_name, ctl->procname,
			dev_name, ctl->procname);
		warned++;
	पूर्ण
पूर्ण

पूर्णांक ndisc_अगरinfo_sysctl_change(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा net_device *dev = ctl->extra1;
	काष्ठा inet6_dev *idev;
	पूर्णांक ret;

	अगर ((म_भेद(ctl->procname, "retrans_time") == 0) ||
	    (म_भेद(ctl->procname, "base_reachable_time") == 0))
		ndisc_warn_deprecated_sysctl(ctl, "syscall", dev ? dev->name : "default");

	अगर (म_भेद(ctl->procname, "retrans_time") == 0)
		ret = neigh_proc_करोपूर्णांकvec(ctl, ग_लिखो, buffer, lenp, ppos);

	अन्यथा अगर (म_भेद(ctl->procname, "base_reachable_time") == 0)
		ret = neigh_proc_करोपूर्णांकvec_jअगरfies(ctl, ग_लिखो,
						  buffer, lenp, ppos);

	अन्यथा अगर ((म_भेद(ctl->procname, "retrans_time_ms") == 0) ||
		 (म_भेद(ctl->procname, "base_reachable_time_ms") == 0))
		ret = neigh_proc_करोपूर्णांकvec_ms_jअगरfies(ctl, ग_लिखो,
						     buffer, lenp, ppos);
	अन्यथा
		ret = -1;

	अगर (ग_लिखो && ret == 0 && dev && (idev = in6_dev_get(dev)) != शून्य) अणु
		अगर (ctl->data == &NEIGH_VAR(idev->nd_parms, BASE_REACHABLE_TIME))
			idev->nd_parms->reachable_समय =
					neigh_अक्रम_reach_समय(NEIGH_VAR(idev->nd_parms, BASE_REACHABLE_TIME));
		idev->tstamp = jअगरfies;
		inet6_अगरinfo_notअगरy(RTM_NEWLINK, idev);
		in6_dev_put(idev);
	पूर्ण
	वापस ret;
पूर्ण


#पूर्ण_अगर

अटल पूर्णांक __net_init ndisc_net_init(काष्ठा net *net)
अणु
	काष्ठा ipv6_pinfo *np;
	काष्ठा sock *sk;
	पूर्णांक err;

	err = inet_ctl_sock_create(&sk, PF_INET6,
				   SOCK_RAW, IPPROTO_ICMPV6, net);
	अगर (err < 0) अणु
		ND_PRINTK(0, err,
			  "NDISC: Failed to initialize the control socket (err %d)\n",
			  err);
		वापस err;
	पूर्ण

	net->ipv6.ndisc_sk = sk;

	np = inet6_sk(sk);
	np->hop_limit = 255;
	/* Do not loopback ndisc messages */
	np->mc_loop = 0;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास ndisc_net_निकास(काष्ठा net *net)
अणु
	inet_ctl_sock_destroy(net->ipv6.ndisc_sk);
पूर्ण

अटल काष्ठा pernet_operations ndisc_net_ops = अणु
	.init = ndisc_net_init,
	.निकास = ndisc_net_निकास,
पूर्ण;

पूर्णांक __init ndisc_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_subsys(&ndisc_net_ops);
	अगर (err)
		वापस err;
	/*
	 * Initialize the neighbour table
	 */
	neigh_table_init(NEIGH_ND_TABLE, &nd_tbl);

#अगर_घोषित CONFIG_SYSCTL
	err = neigh_sysctl_रेजिस्टर(शून्य, &nd_tbl.parms,
				    ndisc_अगरinfo_sysctl_change);
	अगर (err)
		जाओ out_unरेजिस्टर_pernet;
out:
#पूर्ण_अगर
	वापस err;

#अगर_घोषित CONFIG_SYSCTL
out_unरेजिस्टर_pernet:
	unरेजिस्टर_pernet_subsys(&ndisc_net_ops);
	जाओ out;
#पूर्ण_अगर
पूर्ण

पूर्णांक __init ndisc_late_init(व्योम)
अणु
	वापस रेजिस्टर_netdevice_notअगरier(&ndisc_netdev_notअगरier);
पूर्ण

व्योम ndisc_late_cleanup(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&ndisc_netdev_notअगरier);
पूर्ण

व्योम ndisc_cleanup(व्योम)
अणु
#अगर_घोषित CONFIG_SYSCTL
	neigh_sysctl_unरेजिस्टर(&nd_tbl.parms);
#पूर्ण_अगर
	neigh_table_clear(NEIGH_ND_TABLE, &nd_tbl);
	unरेजिस्टर_pernet_subsys(&ndisc_net_ops);
पूर्ण
