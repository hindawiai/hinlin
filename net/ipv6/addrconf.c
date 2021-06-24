<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPv6 Address [स्वतः]configuration
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *	Alexey Kuznetsov	<kuznet@ms2.inr.ac.ru>
 */

/*
 *	Changes:
 *
 *	Janos Farkas			:	delete समयr on अगरकरोwn
 *	<chexum@bankinf.banki.hu>
 *	Andi Kleen			:	समाप्त द्विगुन kमुक्त on module
 *						unload.
 *	Maciej W. Rozycki		:	FDDI support
 *	sekiya@USAGI			:	Don't send too many RS
 *						packets.
 *	yoshfuji@USAGI			:       Fixed पूर्णांकerval between DAD
 *						packets.
 *	YOSHIFUJI Hideaki @USAGI	:	improved accuracy of
 *						address validation समयr.
 *	YOSHIFUJI Hideaki @USAGI	:	Privacy Extensions (RFC3041)
 *						support.
 *	Yuji SEKIYA @USAGI		:	Don't assign a same IPv6
 *						address on a same पूर्णांकerface.
 *	YOSHIFUJI Hideaki @USAGI	:	ARCnet support
 *	YOSHIFUJI Hideaki @USAGI	:	convert /proc/net/अगर_inet6 to
 *						seq_file.
 *	YOSHIFUJI Hideaki @USAGI	:	improved source address
 *						selection; consider scope,
 *						status etc.
 */

#घोषणा pr_fmt(fmt) "IPv6: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/inet.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_addr.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_arcnet.h>
#समावेश <linux/अगर_infiniband.h>
#समावेश <linux/route.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर
#समावेश <linux/capability.h>
#समावेश <linux/delay.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/माला.स>
#समावेश <linux/hash.h>

#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/snmp.h>

#समावेश <net/6lowpan.h>
#समावेश <net/firewire.h>
#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/ndisc.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/tcp.h>
#समावेश <net/ip.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/l3mdev.h>
#समावेश <linux/अगर_tunnel.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/netconf.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/export.h>

#घोषणा	अनन्त_LIFE_TIME	0xFFFFFFFF

#घोषणा IPV6_MAX_STRLEN \
	माप("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")

अटल अंतरभूत u32 cstamp_delta(अचिन्हित दीर्घ cstamp)
अणु
	वापस (cstamp - INITIAL_JIFFIES) * 100UL / HZ;
पूर्ण

अटल अंतरभूत s32 rfc3315_s14_backoff_init(s32 irt)
अणु
	/* multiply 'initial retransmission time' by 0.9 .. 1.1 */
	u64 पंचांगp = (900000 + pअक्रमom_u32() % 200001) * (u64)irt;
	करो_भाग(पंचांगp, 1000000);
	वापस (s32)पंचांगp;
पूर्ण

अटल अंतरभूत s32 rfc3315_s14_backoff_update(s32 rt, s32 mrt)
अणु
	/* multiply 'retransmission timeout' by 1.9 .. 2.1 */
	u64 पंचांगp = (1900000 + pअक्रमom_u32() % 200001) * (u64)rt;
	करो_भाग(पंचांगp, 1000000);
	अगर ((s32)पंचांगp > mrt) अणु
		/* multiply 'maximum retransmission time' by 0.9 .. 1.1 */
		पंचांगp = (900000 + pअक्रमom_u32() % 200001) * (u64)mrt;
		करो_भाग(पंचांगp, 1000000);
	पूर्ण
	वापस (s32)पंचांगp;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक addrconf_sysctl_रेजिस्टर(काष्ठा inet6_dev *idev);
अटल व्योम addrconf_sysctl_unरेजिस्टर(काष्ठा inet6_dev *idev);
#अन्यथा
अटल अंतरभूत पूर्णांक addrconf_sysctl_रेजिस्टर(काष्ठा inet6_dev *idev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम addrconf_sysctl_unरेजिस्टर(काष्ठा inet6_dev *idev)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम ipv6_gen_rnd_iid(काष्ठा in6_addr *addr);

अटल पूर्णांक ipv6_generate_eui64(u8 *eui, काष्ठा net_device *dev);
अटल पूर्णांक ipv6_count_addresses(स्थिर काष्ठा inet6_dev *idev);
अटल पूर्णांक ipv6_generate_stable_address(काष्ठा in6_addr *addr,
					u8 dad_count,
					स्थिर काष्ठा inet6_dev *idev);

#घोषणा IN6_ADDR_HSIZE_SHIFT	8
#घोषणा IN6_ADDR_HSIZE		(1 << IN6_ADDR_HSIZE_SHIFT)
/*
 *	Configured unicast address hash table
 */
अटल काष्ठा hlist_head inet6_addr_lst[IN6_ADDR_HSIZE];
अटल DEFINE_SPINLOCK(addrconf_hash_lock);

अटल व्योम addrconf_verअगरy(व्योम);
अटल व्योम addrconf_verअगरy_rtnl(व्योम);
अटल व्योम addrconf_verअगरy_work(काष्ठा work_काष्ठा *);

अटल काष्ठा workqueue_काष्ठा *addrconf_wq;
अटल DECLARE_DELAYED_WORK(addr_chk_work, addrconf_verअगरy_work);

अटल व्योम addrconf_join_anycast(काष्ठा inet6_अगरaddr *अगरp);
अटल व्योम addrconf_leave_anycast(काष्ठा inet6_अगरaddr *अगरp);

अटल व्योम addrconf_type_change(काष्ठा net_device *dev,
				 अचिन्हित दीर्घ event);
अटल पूर्णांक addrconf_अगरकरोwn(काष्ठा net_device *dev, bool unरेजिस्टर);

अटल काष्ठा fib6_info *addrconf_get_prefix_route(स्थिर काष्ठा in6_addr *pfx,
						  पूर्णांक plen,
						  स्थिर काष्ठा net_device *dev,
						  u32 flags, u32 noflags,
						  bool no_gw);

अटल व्योम addrconf_dad_start(काष्ठा inet6_अगरaddr *अगरp);
अटल व्योम addrconf_dad_work(काष्ठा work_काष्ठा *w);
अटल व्योम addrconf_dad_completed(काष्ठा inet6_अगरaddr *अगरp, bool bump_id,
				   bool send_na);
अटल व्योम addrconf_dad_run(काष्ठा inet6_dev *idev, bool restart);
अटल व्योम addrconf_rs_समयr(काष्ठा समयr_list *t);
अटल व्योम __ipv6_अगरa_notअगरy(पूर्णांक event, काष्ठा inet6_अगरaddr *अगरa);
अटल व्योम ipv6_अगरa_notअगरy(पूर्णांक event, काष्ठा inet6_अगरaddr *अगरa);

अटल व्योम inet6_prefix_notअगरy(पूर्णांक event, काष्ठा inet6_dev *idev,
				काष्ठा prefix_info *pinfo);

अटल काष्ठा ipv6_devconf ipv6_devconf __पढ़ो_mostly = अणु
	.क्रमwarding		= 0,
	.hop_limit		= IPV6_DEFAULT_HOPLIMIT,
	.mtu6			= IPV6_MIN_MTU,
	.accept_ra		= 1,
	.accept_redirects	= 1,
	.स्वतःconf		= 1,
	.क्रमce_mld_version	= 0,
	.mldv1_unsolicited_report_पूर्णांकerval = 10 * HZ,
	.mldv2_unsolicited_report_पूर्णांकerval = HZ,
	.dad_transmits		= 1,
	.rtr_solicits		= MAX_RTR_SOLICITATIONS,
	.rtr_solicit_पूर्णांकerval	= RTR_SOLICITATION_INTERVAL,
	.rtr_solicit_max_पूर्णांकerval = RTR_SOLICITATION_MAX_INTERVAL,
	.rtr_solicit_delay	= MAX_RTR_SOLICITATION_DELAY,
	.use_tempaddr		= 0,
	.temp_valid_lft		= TEMP_VALID_LIFETIME,
	.temp_prefered_lft	= TEMP_PREFERRED_LIFETIME,
	.regen_max_retry	= REGEN_MAX_RETRY,
	.max_desync_factor	= MAX_DESYNC_FACTOR,
	.max_addresses		= IPV6_MAX_ADDRESSES,
	.accept_ra_defrtr	= 1,
	.ra_defrtr_metric	= IP6_RT_PRIO_USER,
	.accept_ra_from_local	= 0,
	.accept_ra_min_hop_limit= 1,
	.accept_ra_pinfo	= 1,
#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
	.accept_ra_rtr_pref	= 1,
	.rtr_probe_पूर्णांकerval	= 60 * HZ,
#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
	.accept_ra_rt_info_min_plen = 0,
	.accept_ra_rt_info_max_plen = 0,
#पूर्ण_अगर
#पूर्ण_अगर
	.proxy_ndp		= 0,
	.accept_source_route	= 0,	/* we करो not accept RH0 by शेष. */
	.disable_ipv6		= 0,
	.accept_dad		= 0,
	.suppress_frag_ndisc	= 1,
	.accept_ra_mtu		= 1,
	.stable_secret		= अणु
		.initialized = false,
	पूर्ण,
	.use_oअगर_addrs_only	= 0,
	.ignore_routes_with_linkकरोwn = 0,
	.keep_addr_on_करोwn	= 0,
	.seg6_enabled		= 0,
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	.seg6_require_hmac	= 0,
#पूर्ण_अगर
	.enhanced_dad           = 1,
	.addr_gen_mode		= IN6_ADDR_GEN_MODE_EUI64,
	.disable_policy		= 0,
	.rpl_seg_enabled	= 0,
पूर्ण;

अटल काष्ठा ipv6_devconf ipv6_devconf_dflt __पढ़ो_mostly = अणु
	.क्रमwarding		= 0,
	.hop_limit		= IPV6_DEFAULT_HOPLIMIT,
	.mtu6			= IPV6_MIN_MTU,
	.accept_ra		= 1,
	.accept_redirects	= 1,
	.स्वतःconf		= 1,
	.क्रमce_mld_version	= 0,
	.mldv1_unsolicited_report_पूर्णांकerval = 10 * HZ,
	.mldv2_unsolicited_report_पूर्णांकerval = HZ,
	.dad_transmits		= 1,
	.rtr_solicits		= MAX_RTR_SOLICITATIONS,
	.rtr_solicit_पूर्णांकerval	= RTR_SOLICITATION_INTERVAL,
	.rtr_solicit_max_पूर्णांकerval = RTR_SOLICITATION_MAX_INTERVAL,
	.rtr_solicit_delay	= MAX_RTR_SOLICITATION_DELAY,
	.use_tempaddr		= 0,
	.temp_valid_lft		= TEMP_VALID_LIFETIME,
	.temp_prefered_lft	= TEMP_PREFERRED_LIFETIME,
	.regen_max_retry	= REGEN_MAX_RETRY,
	.max_desync_factor	= MAX_DESYNC_FACTOR,
	.max_addresses		= IPV6_MAX_ADDRESSES,
	.accept_ra_defrtr	= 1,
	.ra_defrtr_metric	= IP6_RT_PRIO_USER,
	.accept_ra_from_local	= 0,
	.accept_ra_min_hop_limit= 1,
	.accept_ra_pinfo	= 1,
#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
	.accept_ra_rtr_pref	= 1,
	.rtr_probe_पूर्णांकerval	= 60 * HZ,
#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
	.accept_ra_rt_info_min_plen = 0,
	.accept_ra_rt_info_max_plen = 0,
#पूर्ण_अगर
#पूर्ण_अगर
	.proxy_ndp		= 0,
	.accept_source_route	= 0,	/* we करो not accept RH0 by शेष. */
	.disable_ipv6		= 0,
	.accept_dad		= 1,
	.suppress_frag_ndisc	= 1,
	.accept_ra_mtu		= 1,
	.stable_secret		= अणु
		.initialized = false,
	पूर्ण,
	.use_oअगर_addrs_only	= 0,
	.ignore_routes_with_linkकरोwn = 0,
	.keep_addr_on_करोwn	= 0,
	.seg6_enabled		= 0,
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	.seg6_require_hmac	= 0,
#पूर्ण_अगर
	.enhanced_dad           = 1,
	.addr_gen_mode		= IN6_ADDR_GEN_MODE_EUI64,
	.disable_policy		= 0,
	.rpl_seg_enabled	= 0,
पूर्ण;

/* Check अगर link is पढ़ोy: is it up and is a valid qdisc available */
अटल अंतरभूत bool addrconf_link_पढ़ोy(स्थिर काष्ठा net_device *dev)
अणु
	वापस netअगर_oper_up(dev) && !qdisc_tx_is_noop(dev);
पूर्ण

अटल व्योम addrconf_del_rs_समयr(काष्ठा inet6_dev *idev)
अणु
	अगर (del_समयr(&idev->rs_समयr))
		__in6_dev_put(idev);
पूर्ण

अटल व्योम addrconf_del_dad_work(काष्ठा inet6_अगरaddr *अगरp)
अणु
	अगर (cancel_delayed_work(&अगरp->dad_work))
		__in6_अगरa_put(अगरp);
पूर्ण

अटल व्योम addrconf_mod_rs_समयr(काष्ठा inet6_dev *idev,
				  अचिन्हित दीर्घ when)
अणु
	अगर (!समयr_pending(&idev->rs_समयr))
		in6_dev_hold(idev);
	mod_समयr(&idev->rs_समयr, jअगरfies + when);
पूर्ण

अटल व्योम addrconf_mod_dad_work(काष्ठा inet6_अगरaddr *अगरp,
				   अचिन्हित दीर्घ delay)
अणु
	in6_अगरa_hold(अगरp);
	अगर (mod_delayed_work(addrconf_wq, &अगरp->dad_work, delay))
		in6_अगरa_put(अगरp);
पूर्ण

अटल पूर्णांक snmp6_alloc_dev(काष्ठा inet6_dev *idev)
अणु
	पूर्णांक i;

	idev->stats.ipv6 = alloc_percpu(काष्ठा ipstats_mib);
	अगर (!idev->stats.ipv6)
		जाओ err_ip;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा ipstats_mib *addrconf_stats;
		addrconf_stats = per_cpu_ptr(idev->stats.ipv6, i);
		u64_stats_init(&addrconf_stats->syncp);
	पूर्ण


	idev->stats.icmpv6dev = kzalloc(माप(काष्ठा icmpv6_mib_device),
					GFP_KERNEL);
	अगर (!idev->stats.icmpv6dev)
		जाओ err_icmp;
	idev->stats.icmpv6msgdev = kzalloc(माप(काष्ठा icmpv6msg_mib_device),
					   GFP_KERNEL);
	अगर (!idev->stats.icmpv6msgdev)
		जाओ err_icmpmsg;

	वापस 0;

err_icmpmsg:
	kमुक्त(idev->stats.icmpv6dev);
err_icmp:
	मुक्त_percpu(idev->stats.ipv6);
err_ip:
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा inet6_dev *ipv6_add_dev(काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *ndev;
	पूर्णांक err = -ENOMEM;

	ASSERT_RTNL();

	अगर (dev->mtu < IPV6_MIN_MTU)
		वापस ERR_PTR(-EINVAL);

	ndev = kzalloc(माप(काष्ठा inet6_dev), GFP_KERNEL);
	अगर (!ndev)
		वापस ERR_PTR(err);

	rwlock_init(&ndev->lock);
	ndev->dev = dev;
	INIT_LIST_HEAD(&ndev->addr_list);
	समयr_setup(&ndev->rs_समयr, addrconf_rs_समयr, 0);
	स_नकल(&ndev->cnf, dev_net(dev)->ipv6.devconf_dflt, माप(ndev->cnf));

	अगर (ndev->cnf.stable_secret.initialized)
		ndev->cnf.addr_gen_mode = IN6_ADDR_GEN_MODE_STABLE_PRIVACY;

	ndev->cnf.mtu6 = dev->mtu;
	ndev->nd_parms = neigh_parms_alloc(dev, &nd_tbl);
	अगर (!ndev->nd_parms) अणु
		kमुक्त(ndev);
		वापस ERR_PTR(err);
	पूर्ण
	अगर (ndev->cnf.क्रमwarding)
		dev_disable_lro(dev);
	/* We refer to the device */
	dev_hold(dev);

	अगर (snmp6_alloc_dev(ndev) < 0) अणु
		netdev_dbg(dev, "%s: cannot allocate memory for statistics\n",
			   __func__);
		neigh_parms_release(&nd_tbl, ndev->nd_parms);
		dev_put(dev);
		kमुक्त(ndev);
		वापस ERR_PTR(err);
	पूर्ण

	अगर (snmp6_रेजिस्टर_dev(ndev) < 0) अणु
		netdev_dbg(dev, "%s: cannot create /proc/net/dev_snmp6/%s\n",
			   __func__, dev->name);
		जाओ err_release;
	पूर्ण

	/* One reference from device. */
	refcount_set(&ndev->refcnt, 1);

	अगर (dev->flags & (IFF_NOARP | IFF_LOOPBACK))
		ndev->cnf.accept_dad = -1;

#अगर IS_ENABLED(CONFIG_IPV6_SIT)
	अगर (dev->type == ARPHRD_SIT && (dev->priv_flags & IFF_ISATAP)) अणु
		pr_info("%s: Disabled Multicast RS\n", dev->name);
		ndev->cnf.rtr_solicits = 0;
	पूर्ण
#पूर्ण_अगर

	INIT_LIST_HEAD(&ndev->tempaddr_list);
	ndev->desync_factor = U32_MAX;
	अगर ((dev->flags&IFF_LOOPBACK) ||
	    dev->type == ARPHRD_TUNNEL ||
	    dev->type == ARPHRD_TUNNEL6 ||
	    dev->type == ARPHRD_SIT ||
	    dev->type == ARPHRD_NONE) अणु
		ndev->cnf.use_tempaddr = -1;
	पूर्ण

	ndev->token = in6addr_any;

	अगर (netअगर_running(dev) && addrconf_link_पढ़ोy(dev))
		ndev->अगर_flags |= IF_READY;

	ipv6_mc_init_dev(ndev);
	ndev->tstamp = jअगरfies;
	err = addrconf_sysctl_रेजिस्टर(ndev);
	अगर (err) अणु
		ipv6_mc_destroy_dev(ndev);
		snmp6_unरेजिस्टर_dev(ndev);
		जाओ err_release;
	पूर्ण
	/* रक्षित by rtnl_lock */
	rcu_assign_poपूर्णांकer(dev->ip6_ptr, ndev);

	/* Join पूर्णांकerface-local all-node multicast group */
	ipv6_dev_mc_inc(dev, &in6addr_पूर्णांकerfacelocal_allnodes);

	/* Join all-node multicast group */
	ipv6_dev_mc_inc(dev, &in6addr_linklocal_allnodes);

	/* Join all-router multicast group अगर क्रमwarding is set */
	अगर (ndev->cnf.क्रमwarding && (dev->flags & IFF_MULTICAST))
		ipv6_dev_mc_inc(dev, &in6addr_linklocal_allrouters);

	वापस ndev;

err_release:
	neigh_parms_release(&nd_tbl, ndev->nd_parms);
	ndev->dead = 1;
	in6_dev_finish_destroy(ndev);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा inet6_dev *ipv6_find_idev(काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *idev;

	ASSERT_RTNL();

	idev = __in6_dev_get(dev);
	अगर (!idev) अणु
		idev = ipv6_add_dev(dev);
		अगर (IS_ERR(idev))
			वापस idev;
	पूर्ण

	अगर (dev->flags&IFF_UP)
		ipv6_mc_up(idev);
	वापस idev;
पूर्ण

अटल पूर्णांक inet6_netconf_msgsize_devconf(पूर्णांक type)
अणु
	पूर्णांक size =  NLMSG_ALIGN(माप(काष्ठा netconfmsg))
		    + nla_total_size(4);	/* NETCONFA_IFINDEX */
	bool all = false;

	अगर (type == NETCONFA_ALL)
		all = true;

	अगर (all || type == NETCONFA_FORWARDING)
		size += nla_total_size(4);
#अगर_घोषित CONFIG_IPV6_MROUTE
	अगर (all || type == NETCONFA_MC_FORWARDING)
		size += nla_total_size(4);
#पूर्ण_अगर
	अगर (all || type == NETCONFA_PROXY_NEIGH)
		size += nla_total_size(4);

	अगर (all || type == NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN)
		size += nla_total_size(4);

	वापस size;
पूर्ण

अटल पूर्णांक inet6_netconf_fill_devconf(काष्ठा sk_buff *skb, पूर्णांक अगरindex,
				      काष्ठा ipv6_devconf *devconf, u32 portid,
				      u32 seq, पूर्णांक event, अचिन्हित पूर्णांक flags,
				      पूर्णांक type)
अणु
	काष्ठा nlmsghdr  *nlh;
	काष्ठा netconfmsg *ncm;
	bool all = false;

	nlh = nlmsg_put(skb, portid, seq, event, माप(काष्ठा netconfmsg),
			flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	अगर (type == NETCONFA_ALL)
		all = true;

	ncm = nlmsg_data(nlh);
	ncm->ncm_family = AF_INET6;

	अगर (nla_put_s32(skb, NETCONFA_IFINDEX, अगरindex) < 0)
		जाओ nla_put_failure;

	अगर (!devconf)
		जाओ out;

	अगर ((all || type == NETCONFA_FORWARDING) &&
	    nla_put_s32(skb, NETCONFA_FORWARDING, devconf->क्रमwarding) < 0)
		जाओ nla_put_failure;
#अगर_घोषित CONFIG_IPV6_MROUTE
	अगर ((all || type == NETCONFA_MC_FORWARDING) &&
	    nla_put_s32(skb, NETCONFA_MC_FORWARDING,
			devconf->mc_क्रमwarding) < 0)
		जाओ nla_put_failure;
#पूर्ण_अगर
	अगर ((all || type == NETCONFA_PROXY_NEIGH) &&
	    nla_put_s32(skb, NETCONFA_PROXY_NEIGH, devconf->proxy_ndp) < 0)
		जाओ nla_put_failure;

	अगर ((all || type == NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN) &&
	    nla_put_s32(skb, NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN,
			devconf->ignore_routes_with_linkकरोwn) < 0)
		जाओ nla_put_failure;

out:
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

व्योम inet6_netconf_notअगरy_devconf(काष्ठा net *net, पूर्णांक event, पूर्णांक type,
				  पूर्णांक अगरindex, काष्ठा ipv6_devconf *devconf)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(inet6_netconf_msgsize_devconf(type), GFP_KERNEL);
	अगर (!skb)
		जाओ errout;

	err = inet6_netconf_fill_devconf(skb, अगरindex, devconf, 0, 0,
					 event, 0, type);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in inet6_netconf_msgsize_devconf() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV6_NETCONF, शून्य, GFP_KERNEL);
	वापस;
errout:
	rtnl_set_sk_err(net, RTNLGRP_IPV6_NETCONF, err);
पूर्ण

अटल स्थिर काष्ठा nla_policy devconf_ipv6_policy[NETCONFA_MAX+1] = अणु
	[NETCONFA_IFINDEX]	= अणु .len = माप(पूर्णांक) पूर्ण,
	[NETCONFA_FORWARDING]	= अणु .len = माप(पूर्णांक) पूर्ण,
	[NETCONFA_PROXY_NEIGH]	= अणु .len = माप(पूर्णांक) पूर्ण,
	[NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN]	= अणु .len = माप(पूर्णांक) पूर्ण,
पूर्ण;

अटल पूर्णांक inet6_netconf_valid_get_req(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा nlmsghdr *nlh,
				       काष्ठा nlattr **tb,
				       काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक i, err;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(काष्ठा netconfmsg))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid header for netconf get request");
		वापस -EINVAL;
	पूर्ण

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(काष्ठा netconfmsg),
					      tb, NETCONFA_MAX,
					      devconf_ipv6_policy, extack);

	err = nlmsg_parse_deprecated_strict(nlh, माप(काष्ठा netconfmsg),
					    tb, NETCONFA_MAX,
					    devconf_ipv6_policy, extack);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <= NETCONFA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल NETCONFA_IFINDEX:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported attribute in netconf get request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet6_netconf_get_devconf(काष्ठा sk_buff *in_skb,
				     काष्ठा nlmsghdr *nlh,
				     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा nlattr *tb[NETCONFA_MAX+1];
	काष्ठा inet6_dev *in6_dev = शून्य;
	काष्ठा net_device *dev = शून्य;
	काष्ठा sk_buff *skb;
	काष्ठा ipv6_devconf *devconf;
	पूर्णांक अगरindex;
	पूर्णांक err;

	err = inet6_netconf_valid_get_req(in_skb, nlh, tb, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NETCONFA_IFINDEX])
		वापस -EINVAL;

	err = -EINVAL;
	अगरindex = nla_get_s32(tb[NETCONFA_IFINDEX]);
	चयन (अगरindex) अणु
	हाल NETCONFA_IFINDEX_ALL:
		devconf = net->ipv6.devconf_all;
		अवरोध;
	हाल NETCONFA_IFINDEX_DEFAULT:
		devconf = net->ipv6.devconf_dflt;
		अवरोध;
	शेष:
		dev = dev_get_by_index(net, अगरindex);
		अगर (!dev)
			वापस -EINVAL;
		in6_dev = in6_dev_get(dev);
		अगर (!in6_dev)
			जाओ errout;
		devconf = &in6_dev->cnf;
		अवरोध;
	पूर्ण

	err = -ENOBUFS;
	skb = nlmsg_new(inet6_netconf_msgsize_devconf(NETCONFA_ALL), GFP_KERNEL);
	अगर (!skb)
		जाओ errout;

	err = inet6_netconf_fill_devconf(skb, अगरindex, devconf,
					 NETLINK_CB(in_skb).portid,
					 nlh->nlmsg_seq, RTM_NEWNETCONF, 0,
					 NETCONFA_ALL);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in inet6_netconf_msgsize_devconf() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
errout:
	अगर (in6_dev)
		in6_dev_put(in6_dev);
	अगर (dev)
		dev_put(dev);
	वापस err;
पूर्ण

अटल पूर्णांक inet6_netconf_dump_devconf(काष्ठा sk_buff *skb,
				      काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक h, s_h;
	पूर्णांक idx, s_idx;
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;
	काष्ठा hlist_head *head;

	अगर (cb->strict_check) अणु
		काष्ठा netlink_ext_ack *extack = cb->extack;
		काष्ठा netconfmsg *ncm;

		अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*ncm))) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid header for netconf dump request");
			वापस -EINVAL;
		पूर्ण

		अगर (nlmsg_attrlen(nlh, माप(*ncm))) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid data after header in netconf dump request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	s_h = cb->args[0];
	s_idx = idx = cb->args[1];

	क्रम (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		idx = 0;
		head = &net->dev_index_head[h];
		rcu_पढ़ो_lock();
		cb->seq = atomic_पढ़ो(&net->ipv6.dev_addr_genid) ^
			  net->dev_base_seq;
		hlist_क्रम_each_entry_rcu(dev, head, index_hlist) अणु
			अगर (idx < s_idx)
				जाओ cont;
			idev = __in6_dev_get(dev);
			अगर (!idev)
				जाओ cont;

			अगर (inet6_netconf_fill_devconf(skb, dev->अगरindex,
						       &idev->cnf,
						       NETLINK_CB(cb->skb).portid,
						       nlh->nlmsg_seq,
						       RTM_NEWNETCONF,
						       NLM_F_MULTI,
						       NETCONFA_ALL) < 0) अणु
				rcu_पढ़ो_unlock();
				जाओ करोne;
			पूर्ण
			nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
			idx++;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	अगर (h == NETDEV_HASHENTRIES) अणु
		अगर (inet6_netconf_fill_devconf(skb, NETCONFA_IFINDEX_ALL,
					       net->ipv6.devconf_all,
					       NETLINK_CB(cb->skb).portid,
					       nlh->nlmsg_seq,
					       RTM_NEWNETCONF, NLM_F_MULTI,
					       NETCONFA_ALL) < 0)
			जाओ करोne;
		अन्यथा
			h++;
	पूर्ण
	अगर (h == NETDEV_HASHENTRIES + 1) अणु
		अगर (inet6_netconf_fill_devconf(skb, NETCONFA_IFINDEX_DEFAULT,
					       net->ipv6.devconf_dflt,
					       NETLINK_CB(cb->skb).portid,
					       nlh->nlmsg_seq,
					       RTM_NEWNETCONF, NLM_F_MULTI,
					       NETCONFA_ALL) < 0)
			जाओ करोne;
		अन्यथा
			h++;
	पूर्ण
करोne:
	cb->args[0] = h;
	cb->args[1] = idx;

	वापस skb->len;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL
अटल व्योम dev_क्रमward_change(काष्ठा inet6_dev *idev)
अणु
	काष्ठा net_device *dev;
	काष्ठा inet6_अगरaddr *अगरa;

	अगर (!idev)
		वापस;
	dev = idev->dev;
	अगर (idev->cnf.क्रमwarding)
		dev_disable_lro(dev);
	अगर (dev->flags & IFF_MULTICAST) अणु
		अगर (idev->cnf.क्रमwarding) अणु
			ipv6_dev_mc_inc(dev, &in6addr_linklocal_allrouters);
			ipv6_dev_mc_inc(dev, &in6addr_पूर्णांकerfacelocal_allrouters);
			ipv6_dev_mc_inc(dev, &in6addr_sitelocal_allrouters);
		पूर्ण अन्यथा अणु
			ipv6_dev_mc_dec(dev, &in6addr_linklocal_allrouters);
			ipv6_dev_mc_dec(dev, &in6addr_पूर्णांकerfacelocal_allrouters);
			ipv6_dev_mc_dec(dev, &in6addr_sitelocal_allrouters);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(अगरa, &idev->addr_list, अगर_list) अणु
		अगर (अगरa->flags&IFA_F_TENTATIVE)
			जारी;
		अगर (idev->cnf.क्रमwarding)
			addrconf_join_anycast(अगरa);
		अन्यथा
			addrconf_leave_anycast(अगरa);
	पूर्ण
	inet6_netconf_notअगरy_devconf(dev_net(dev), RTM_NEWNETCONF,
				     NETCONFA_FORWARDING,
				     dev->अगरindex, &idev->cnf);
पूर्ण


अटल व्योम addrconf_क्रमward_change(काष्ठा net *net, __s32 newf)
अणु
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;

	क्रम_each_netdev(net, dev) अणु
		idev = __in6_dev_get(dev);
		अगर (idev) अणु
			पूर्णांक changed = (!idev->cnf.क्रमwarding) ^ (!newf);
			idev->cnf.क्रमwarding = newf;
			अगर (changed)
				dev_क्रमward_change(idev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक addrconf_fixup_क्रमwarding(काष्ठा ctl_table *table, पूर्णांक *p, पूर्णांक newf)
अणु
	काष्ठा net *net;
	पूर्णांक old;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	net = (काष्ठा net *)table->extra2;
	old = *p;
	*p = newf;

	अगर (p == &net->ipv6.devconf_dflt->क्रमwarding) अणु
		अगर ((!newf) ^ (!old))
			inet6_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						     NETCONFA_FORWARDING,
						     NETCONFA_IFINDEX_DEFAULT,
						     net->ipv6.devconf_dflt);
		rtnl_unlock();
		वापस 0;
	पूर्ण

	अगर (p == &net->ipv6.devconf_all->क्रमwarding) अणु
		पूर्णांक old_dflt = net->ipv6.devconf_dflt->क्रमwarding;

		net->ipv6.devconf_dflt->क्रमwarding = newf;
		अगर ((!newf) ^ (!old_dflt))
			inet6_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						     NETCONFA_FORWARDING,
						     NETCONFA_IFINDEX_DEFAULT,
						     net->ipv6.devconf_dflt);

		addrconf_क्रमward_change(net, newf);
		अगर ((!newf) ^ (!old))
			inet6_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						     NETCONFA_FORWARDING,
						     NETCONFA_IFINDEX_ALL,
						     net->ipv6.devconf_all);
	पूर्ण अन्यथा अगर ((!newf) ^ (!old))
		dev_क्रमward_change((काष्ठा inet6_dev *)table->extra1);
	rtnl_unlock();

	अगर (newf)
		rt6_purge_dflt_routers(net);
	वापस 1;
पूर्ण

अटल व्योम addrconf_linkकरोwn_change(काष्ठा net *net, __s32 newf)
अणु
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;

	क्रम_each_netdev(net, dev) अणु
		idev = __in6_dev_get(dev);
		अगर (idev) अणु
			पूर्णांक changed = (!idev->cnf.ignore_routes_with_linkकरोwn) ^ (!newf);

			idev->cnf.ignore_routes_with_linkकरोwn = newf;
			अगर (changed)
				inet6_netconf_notअगरy_devconf(dev_net(dev),
							     RTM_NEWNETCONF,
							     NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN,
							     dev->अगरindex,
							     &idev->cnf);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक addrconf_fixup_linkकरोwn(काष्ठा ctl_table *table, पूर्णांक *p, पूर्णांक newf)
अणु
	काष्ठा net *net;
	पूर्णांक old;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	net = (काष्ठा net *)table->extra2;
	old = *p;
	*p = newf;

	अगर (p == &net->ipv6.devconf_dflt->ignore_routes_with_linkकरोwn) अणु
		अगर ((!newf) ^ (!old))
			inet6_netconf_notअगरy_devconf(net,
						     RTM_NEWNETCONF,
						     NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN,
						     NETCONFA_IFINDEX_DEFAULT,
						     net->ipv6.devconf_dflt);
		rtnl_unlock();
		वापस 0;
	पूर्ण

	अगर (p == &net->ipv6.devconf_all->ignore_routes_with_linkकरोwn) अणु
		net->ipv6.devconf_dflt->ignore_routes_with_linkकरोwn = newf;
		addrconf_linkकरोwn_change(net, newf);
		अगर ((!newf) ^ (!old))
			inet6_netconf_notअगरy_devconf(net,
						     RTM_NEWNETCONF,
						     NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN,
						     NETCONFA_IFINDEX_ALL,
						     net->ipv6.devconf_all);
	पूर्ण
	rtnl_unlock();

	वापस 1;
पूर्ण

#पूर्ण_अगर

/* Nobody refers to this अगरaddr, destroy it */
व्योम inet6_अगरa_finish_destroy(काष्ठा inet6_अगरaddr *अगरp)
अणु
	WARN_ON(!hlist_unhashed(&अगरp->addr_lst));

#अगर_घोषित NET_REFCNT_DEBUG
	pr_debug("%s\n", __func__);
#पूर्ण_अगर

	in6_dev_put(अगरp->idev);

	अगर (cancel_delayed_work(&अगरp->dad_work))
		pr_notice("delayed DAD work was pending while freeing ifa=%p\n",
			  अगरp);

	अगर (अगरp->state != INET6_IFADDR_STATE_DEAD) अणु
		pr_warn("Freeing alive inet6 address %p\n", अगरp);
		वापस;
	पूर्ण

	kमुक्त_rcu(अगरp, rcu);
पूर्ण

अटल व्योम
ipv6_link_dev_addr(काष्ठा inet6_dev *idev, काष्ठा inet6_अगरaddr *अगरp)
अणु
	काष्ठा list_head *p;
	पूर्णांक अगरp_scope = ipv6_addr_src_scope(&अगरp->addr);

	/*
	 * Each device address list is sorted in order of scope -
	 * global beक्रमe linklocal.
	 */
	list_क्रम_each(p, &idev->addr_list) अणु
		काष्ठा inet6_अगरaddr *अगरa
			= list_entry(p, काष्ठा inet6_अगरaddr, अगर_list);
		अगर (अगरp_scope >= ipv6_addr_src_scope(&अगरa->addr))
			अवरोध;
	पूर्ण

	list_add_tail_rcu(&अगरp->अगर_list, p);
पूर्ण

अटल u32 inet6_addr_hash(स्थिर काष्ठा net *net, स्थिर काष्ठा in6_addr *addr)
अणु
	u32 val = ipv6_addr_hash(addr) ^ net_hash_mix(net);

	वापस hash_32(val, IN6_ADDR_HSIZE_SHIFT);
पूर्ण

अटल bool ipv6_chk_same_addr(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			       काष्ठा net_device *dev, अचिन्हित पूर्णांक hash)
अणु
	काष्ठा inet6_अगरaddr *अगरp;

	hlist_क्रम_each_entry(अगरp, &inet6_addr_lst[hash], addr_lst) अणु
		अगर (!net_eq(dev_net(अगरp->idev->dev), net))
			जारी;
		अगर (ipv6_addr_equal(&अगरp->addr, addr)) अणु
			अगर (!dev || अगरp->idev->dev == dev)
				वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक ipv6_add_addr_hash(काष्ठा net_device *dev, काष्ठा inet6_अगरaddr *अगरa)
अणु
	अचिन्हित पूर्णांक hash = inet6_addr_hash(dev_net(dev), &अगरa->addr);
	पूर्णांक err = 0;

	spin_lock(&addrconf_hash_lock);

	/* Ignore adding duplicate addresses on an पूर्णांकerface */
	अगर (ipv6_chk_same_addr(dev_net(dev), &अगरa->addr, dev, hash)) अणु
		netdev_dbg(dev, "ipv6_add_addr: already assigned\n");
		err = -EEXIST;
	पूर्ण अन्यथा अणु
		hlist_add_head_rcu(&अगरa->addr_lst, &inet6_addr_lst[hash]);
	पूर्ण

	spin_unlock(&addrconf_hash_lock);

	वापस err;
पूर्ण

/* On success it वापसs अगरp with increased reference count */

अटल काष्ठा inet6_अगरaddr *
ipv6_add_addr(काष्ठा inet6_dev *idev, काष्ठा अगरa6_config *cfg,
	      bool can_block, काष्ठा netlink_ext_ack *extack)
अणु
	gfp_t gfp_flags = can_block ? GFP_KERNEL : GFP_ATOMIC;
	पूर्णांक addr_type = ipv6_addr_type(cfg->pfx);
	काष्ठा net *net = dev_net(idev->dev);
	काष्ठा inet6_अगरaddr *अगरa = शून्य;
	काष्ठा fib6_info *f6i = शून्य;
	पूर्णांक err = 0;

	अगर (addr_type == IPV6_ADDR_ANY ||
	    (addr_type & IPV6_ADDR_MULTICAST &&
	     !(cfg->अगरa_flags & IFA_F_MCAUTOJOIN)) ||
	    (!(idev->dev->flags & IFF_LOOPBACK) &&
	     !netअगर_is_l3_master(idev->dev) &&
	     addr_type & IPV6_ADDR_LOOPBACK))
		वापस ERR_PTR(-EADDRNOTAVAIL);

	अगर (idev->dead) अणु
		err = -ENODEV;			/*XXX*/
		जाओ out;
	पूर्ण

	अगर (idev->cnf.disable_ipv6) अणु
		err = -EACCES;
		जाओ out;
	पूर्ण

	/* validator notअगरier needs to be blocking;
	 * करो not call in atomic context
	 */
	अगर (can_block) अणु
		काष्ठा in6_validator_info i6vi = अणु
			.i6vi_addr = *cfg->pfx,
			.i6vi_dev = idev,
			.extack = extack,
		पूर्ण;

		err = inet6addr_validator_notअगरier_call_chain(NETDEV_UP, &i6vi);
		err = notअगरier_to_त्रुटि_सं(err);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	अगरa = kzalloc(माप(*अगरa), gfp_flags);
	अगर (!अगरa) अणु
		err = -ENOBUFS;
		जाओ out;
	पूर्ण

	f6i = addrconf_f6i_alloc(net, idev, cfg->pfx, false, gfp_flags);
	अगर (IS_ERR(f6i)) अणु
		err = PTR_ERR(f6i);
		f6i = शून्य;
		जाओ out;
	पूर्ण

	अगर (net->ipv6.devconf_all->disable_policy ||
	    idev->cnf.disable_policy)
		f6i->dst_nopolicy = true;

	neigh_parms_data_state_setall(idev->nd_parms);

	अगरa->addr = *cfg->pfx;
	अगर (cfg->peer_pfx)
		अगरa->peer_addr = *cfg->peer_pfx;

	spin_lock_init(&अगरa->lock);
	INIT_DELAYED_WORK(&अगरa->dad_work, addrconf_dad_work);
	INIT_HLIST_NODE(&अगरa->addr_lst);
	अगरa->scope = cfg->scope;
	अगरa->prefix_len = cfg->plen;
	अगरa->rt_priority = cfg->rt_priority;
	अगरa->flags = cfg->अगरa_flags;
	/* No need to add the TENTATIVE flag क्रम addresses with NODAD */
	अगर (!(cfg->अगरa_flags & IFA_F_NODAD))
		अगरa->flags |= IFA_F_TENTATIVE;
	अगरa->valid_lft = cfg->valid_lft;
	अगरa->prefered_lft = cfg->preferred_lft;
	अगरa->cstamp = अगरa->tstamp = jअगरfies;
	अगरa->tokenized = false;

	अगरa->rt = f6i;

	अगरa->idev = idev;
	in6_dev_hold(idev);

	/* For caller */
	refcount_set(&अगरa->refcnt, 1);

	rcu_पढ़ो_lock_bh();

	err = ipv6_add_addr_hash(idev->dev, अगरa);
	अगर (err < 0) अणु
		rcu_पढ़ो_unlock_bh();
		जाओ out;
	पूर्ण

	ग_लिखो_lock(&idev->lock);

	/* Add to inet6_dev unicast addr list. */
	ipv6_link_dev_addr(idev, अगरa);

	अगर (अगरa->flags&IFA_F_TEMPORARY) अणु
		list_add(&अगरa->पंचांगp_list, &idev->tempaddr_list);
		in6_अगरa_hold(अगरa);
	पूर्ण

	in6_अगरa_hold(अगरa);
	ग_लिखो_unlock(&idev->lock);

	rcu_पढ़ो_unlock_bh();

	inet6addr_notअगरier_call_chain(NETDEV_UP, अगरa);
out:
	अगर (unlikely(err < 0)) अणु
		fib6_info_release(f6i);

		अगर (अगरa) अणु
			अगर (अगरa->idev)
				in6_dev_put(अगरa->idev);
			kमुक्त(अगरa);
		पूर्ण
		अगरa = ERR_PTR(err);
	पूर्ण

	वापस अगरa;
पूर्ण

क्रमागत cleanup_prefix_rt_t अणु
	CLEANUP_PREFIX_RT_NOP,    /* no cleanup action क्रम prefix route */
	CLEANUP_PREFIX_RT_DEL,    /* delete the prefix route */
	CLEANUP_PREFIX_RT_EXPIRE, /* update the lअगरeसमय of the prefix route */
पूर्ण;

/*
 * Check, whether the prefix क्रम अगरp would still need a prefix route
 * after deleting अगरp. The function वापसs one of the CLEANUP_PREFIX_RT_*
 * स्थिरants.
 *
 * 1) we करोn't purge prefix अगर address was not permanent.
 *    prefix is managed by its own lअगरeसमय.
 * 2) we also करोn't purge, अगर the address was IFA_F_NOPREFIXROUTE.
 * 3) अगर there are no addresses, delete prefix.
 * 4) अगर there are still other permanent address(es),
 *    corresponding prefix is still permanent.
 * 5) अगर there are still other addresses with IFA_F_NOPREFIXROUTE,
 *    करोn't purge the prefix, assume user space is managing it.
 * 6) otherwise, update prefix lअगरeसमय to the
 *    दीर्घest valid lअगरeसमय among the corresponding
 *    addresses on the device.
 *    Note: subsequent RA will update lअगरeसमय.
 **/
अटल क्रमागत cleanup_prefix_rt_t
check_cleanup_prefix_route(काष्ठा inet6_अगरaddr *अगरp, अचिन्हित दीर्घ *expires)
अणु
	काष्ठा inet6_अगरaddr *अगरa;
	काष्ठा inet6_dev *idev = अगरp->idev;
	अचिन्हित दीर्घ lअगरeसमय;
	क्रमागत cleanup_prefix_rt_t action = CLEANUP_PREFIX_RT_DEL;

	*expires = jअगरfies;

	list_क्रम_each_entry(अगरa, &idev->addr_list, अगर_list) अणु
		अगर (अगरa == अगरp)
			जारी;
		अगर (अगरa->prefix_len != अगरp->prefix_len ||
		    !ipv6_prefix_equal(&अगरa->addr, &अगरp->addr,
				       अगरp->prefix_len))
			जारी;
		अगर (अगरa->flags & (IFA_F_PERMANENT | IFA_F_NOPREFIXROUTE))
			वापस CLEANUP_PREFIX_RT_NOP;

		action = CLEANUP_PREFIX_RT_EXPIRE;

		spin_lock(&अगरa->lock);

		lअगरeसमय = addrconf_समयout_fixup(अगरa->valid_lft, HZ);
		/*
		 * Note: Because this address is
		 * not permanent, lअगरeसमय <
		 * दीर्घ_उच्च / HZ here.
		 */
		अगर (समय_beक्रमe(*expires, अगरa->tstamp + lअगरeसमय * HZ))
			*expires = अगरa->tstamp + lअगरeसमय * HZ;
		spin_unlock(&अगरa->lock);
	पूर्ण

	वापस action;
पूर्ण

अटल व्योम
cleanup_prefix_route(काष्ठा inet6_अगरaddr *अगरp, अचिन्हित दीर्घ expires,
		     bool del_rt, bool del_peer)
अणु
	काष्ठा fib6_info *f6i;

	f6i = addrconf_get_prefix_route(del_peer ? &अगरp->peer_addr : &अगरp->addr,
					अगरp->prefix_len,
					अगरp->idev->dev, 0, RTF_DEFAULT, true);
	अगर (f6i) अणु
		अगर (del_rt)
			ip6_del_rt(dev_net(अगरp->idev->dev), f6i, false);
		अन्यथा अणु
			अगर (!(f6i->fib6_flags & RTF_EXPIRES))
				fib6_set_expires(f6i, expires);
			fib6_info_release(f6i);
		पूर्ण
	पूर्ण
पूर्ण


/* This function wants to get referenced अगरp and releases it beक्रमe वापस */

अटल व्योम ipv6_del_addr(काष्ठा inet6_अगरaddr *अगरp)
अणु
	पूर्णांक state;
	क्रमागत cleanup_prefix_rt_t action = CLEANUP_PREFIX_RT_NOP;
	अचिन्हित दीर्घ expires;

	ASSERT_RTNL();

	spin_lock_bh(&अगरp->lock);
	state = अगरp->state;
	अगरp->state = INET6_IFADDR_STATE_DEAD;
	spin_unlock_bh(&अगरp->lock);

	अगर (state == INET6_IFADDR_STATE_DEAD)
		जाओ out;

	spin_lock_bh(&addrconf_hash_lock);
	hlist_del_init_rcu(&अगरp->addr_lst);
	spin_unlock_bh(&addrconf_hash_lock);

	ग_लिखो_lock_bh(&अगरp->idev->lock);

	अगर (अगरp->flags&IFA_F_TEMPORARY) अणु
		list_del(&अगरp->पंचांगp_list);
		अगर (अगरp->अगरpub) अणु
			in6_अगरa_put(अगरp->अगरpub);
			अगरp->अगरpub = शून्य;
		पूर्ण
		__in6_अगरa_put(अगरp);
	पूर्ण

	अगर (अगरp->flags & IFA_F_PERMANENT && !(अगरp->flags & IFA_F_NOPREFIXROUTE))
		action = check_cleanup_prefix_route(अगरp, &expires);

	list_del_rcu(&अगरp->अगर_list);
	__in6_अगरa_put(अगरp);

	ग_लिखो_unlock_bh(&अगरp->idev->lock);

	addrconf_del_dad_work(अगरp);

	ipv6_अगरa_notअगरy(RTM_DELADDR, अगरp);

	inet6addr_notअगरier_call_chain(NETDEV_DOWN, अगरp);

	अगर (action != CLEANUP_PREFIX_RT_NOP) अणु
		cleanup_prefix_route(अगरp, expires,
			action == CLEANUP_PREFIX_RT_DEL, false);
	पूर्ण

	/* clean up prefsrc entries */
	rt6_हटाओ_prefsrc(अगरp);
out:
	in6_अगरa_put(अगरp);
पूर्ण

अटल पूर्णांक ipv6_create_tempaddr(काष्ठा inet6_अगरaddr *अगरp, bool block)
अणु
	काष्ठा inet6_dev *idev = अगरp->idev;
	अचिन्हित दीर्घ पंचांगp_tstamp, age;
	अचिन्हित दीर्घ regen_advance;
	अचिन्हित दीर्घ now = jअगरfies;
	s32 cnf_temp_preferred_lft;
	काष्ठा inet6_अगरaddr *अगरt;
	काष्ठा अगरa6_config cfg;
	दीर्घ max_desync_factor;
	काष्ठा in6_addr addr;
	पूर्णांक ret = 0;

	ग_लिखो_lock_bh(&idev->lock);

retry:
	in6_dev_hold(idev);
	अगर (idev->cnf.use_tempaddr <= 0) अणु
		ग_लिखो_unlock_bh(&idev->lock);
		pr_info("%s: use_tempaddr is disabled\n", __func__);
		in6_dev_put(idev);
		ret = -1;
		जाओ out;
	पूर्ण
	spin_lock_bh(&अगरp->lock);
	अगर (अगरp->regen_count++ >= idev->cnf.regen_max_retry) अणु
		idev->cnf.use_tempaddr = -1;	/*XXX*/
		spin_unlock_bh(&अगरp->lock);
		ग_लिखो_unlock_bh(&idev->lock);
		pr_warn("%s: regeneration time exceeded - disabled temporary address support\n",
			__func__);
		in6_dev_put(idev);
		ret = -1;
		जाओ out;
	पूर्ण
	in6_अगरa_hold(अगरp);
	स_नकल(addr.s6_addr, अगरp->addr.s6_addr, 8);
	ipv6_gen_rnd_iid(&addr);

	age = (now - अगरp->tstamp) / HZ;

	regen_advance = idev->cnf.regen_max_retry *
			idev->cnf.dad_transmits *
			max(NEIGH_VAR(idev->nd_parms, RETRANS_TIME), HZ/100) / HZ;

	/* recalculate max_desync_factor each समय and update
	 * idev->desync_factor अगर it's larger
	 */
	cnf_temp_preferred_lft = READ_ONCE(idev->cnf.temp_prefered_lft);
	max_desync_factor = min_t(__u32,
				  idev->cnf.max_desync_factor,
				  cnf_temp_preferred_lft - regen_advance);

	अगर (unlikely(idev->desync_factor > max_desync_factor)) अणु
		अगर (max_desync_factor > 0) अणु
			get_अक्रमom_bytes(&idev->desync_factor,
					 माप(idev->desync_factor));
			idev->desync_factor %= max_desync_factor;
		पूर्ण अन्यथा अणु
			idev->desync_factor = 0;
		पूर्ण
	पूर्ण

	स_रखो(&cfg, 0, माप(cfg));
	cfg.valid_lft = min_t(__u32, अगरp->valid_lft,
			      idev->cnf.temp_valid_lft + age);
	cfg.preferred_lft = cnf_temp_preferred_lft + age - idev->desync_factor;
	cfg.preferred_lft = min_t(__u32, अगरp->prefered_lft, cfg.preferred_lft);

	cfg.plen = अगरp->prefix_len;
	पंचांगp_tstamp = अगरp->tstamp;
	spin_unlock_bh(&अगरp->lock);

	ग_लिखो_unlock_bh(&idev->lock);

	/* A temporary address is created only अगर this calculated Preferred
	 * Lअगरeसमय is greater than REGEN_ADVANCE समय units.  In particular,
	 * an implementation must not create a temporary address with a zero
	 * Preferred Lअगरeसमय.
	 * Use age calculation as in addrconf_verअगरy to aव्योम unnecessary
	 * temporary addresses being generated.
	 */
	age = (now - पंचांगp_tstamp + ADDRCONF_TIMER_FUZZ_MINUS) / HZ;
	अगर (cfg.preferred_lft <= regen_advance + age) अणु
		in6_अगरa_put(अगरp);
		in6_dev_put(idev);
		ret = -1;
		जाओ out;
	पूर्ण

	cfg.अगरa_flags = IFA_F_TEMPORARY;
	/* set in addrconf_prefix_rcv() */
	अगर (अगरp->flags & IFA_F_OPTIMISTIC)
		cfg.अगरa_flags |= IFA_F_OPTIMISTIC;

	cfg.pfx = &addr;
	cfg.scope = ipv6_addr_scope(cfg.pfx);

	अगरt = ipv6_add_addr(idev, &cfg, block, शून्य);
	अगर (IS_ERR(अगरt)) अणु
		in6_अगरa_put(अगरp);
		in6_dev_put(idev);
		pr_info("%s: retry temporary address regeneration\n", __func__);
		ग_लिखो_lock_bh(&idev->lock);
		जाओ retry;
	पूर्ण

	spin_lock_bh(&अगरt->lock);
	अगरt->अगरpub = अगरp;
	अगरt->cstamp = now;
	अगरt->tstamp = पंचांगp_tstamp;
	spin_unlock_bh(&अगरt->lock);

	addrconf_dad_start(अगरt);
	in6_अगरa_put(अगरt);
	in6_dev_put(idev);
out:
	वापस ret;
पूर्ण

/*
 *	Choose an appropriate source address (RFC3484)
 */
क्रमागत अणु
	IPV6_SADDR_RULE_INIT = 0,
	IPV6_SADDR_RULE_LOCAL,
	IPV6_SADDR_RULE_SCOPE,
	IPV6_SADDR_RULE_PREFERRED,
#अगर_घोषित CONFIG_IPV6_MIP6
	IPV6_SADDR_RULE_HOA,
#पूर्ण_अगर
	IPV6_SADDR_RULE_OIF,
	IPV6_SADDR_RULE_LABEL,
	IPV6_SADDR_RULE_PRIVACY,
	IPV6_SADDR_RULE_ORCHID,
	IPV6_SADDR_RULE_PREFIX,
#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	IPV6_SADDR_RULE_NOT_OPTIMISTIC,
#पूर्ण_अगर
	IPV6_SADDR_RULE_MAX
पूर्ण;

काष्ठा ipv6_saddr_score अणु
	पूर्णांक			rule;
	पूर्णांक			addr_type;
	काष्ठा inet6_अगरaddr	*अगरa;
	DECLARE_BITMAP(scorebits, IPV6_SADDR_RULE_MAX);
	पूर्णांक			scopedist;
	पूर्णांक			matchlen;
पूर्ण;

काष्ठा ipv6_saddr_dst अणु
	स्थिर काष्ठा in6_addr *addr;
	पूर्णांक अगरindex;
	पूर्णांक scope;
	पूर्णांक label;
	अचिन्हित पूर्णांक prefs;
पूर्ण;

अटल अंतरभूत पूर्णांक ipv6_saddr_preferred(पूर्णांक type)
अणु
	अगर (type & (IPV6_ADDR_MAPPED|IPV6_ADDR_COMPATv4|IPV6_ADDR_LOOPBACK))
		वापस 1;
	वापस 0;
पूर्ण

अटल bool ipv6_use_optimistic_addr(काष्ठा net *net,
				     काष्ठा inet6_dev *idev)
अणु
#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	अगर (!idev)
		वापस false;
	अगर (!net->ipv6.devconf_all->optimistic_dad && !idev->cnf.optimistic_dad)
		वापस false;
	अगर (!net->ipv6.devconf_all->use_optimistic && !idev->cnf.use_optimistic)
		वापस false;

	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल bool ipv6_allow_optimistic_dad(काष्ठा net *net,
				      काष्ठा inet6_dev *idev)
अणु
#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	अगर (!idev)
		वापस false;
	अगर (!net->ipv6.devconf_all->optimistic_dad && !idev->cnf.optimistic_dad)
		वापस false;

	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ipv6_get_saddr_eval(काष्ठा net *net,
			       काष्ठा ipv6_saddr_score *score,
			       काष्ठा ipv6_saddr_dst *dst,
			       पूर्णांक i)
अणु
	पूर्णांक ret;

	अगर (i <= score->rule) अणु
		चयन (i) अणु
		हाल IPV6_SADDR_RULE_SCOPE:
			ret = score->scopedist;
			अवरोध;
		हाल IPV6_SADDR_RULE_PREFIX:
			ret = score->matchlen;
			अवरोध;
		शेष:
			ret = !!test_bit(i, score->scorebits);
		पूर्ण
		जाओ out;
	पूर्ण

	चयन (i) अणु
	हाल IPV6_SADDR_RULE_INIT:
		/* Rule 0: remember अगर hiscore is not पढ़ोy yet */
		ret = !!score->अगरa;
		अवरोध;
	हाल IPV6_SADDR_RULE_LOCAL:
		/* Rule 1: Prefer same address */
		ret = ipv6_addr_equal(&score->अगरa->addr, dst->addr);
		अवरोध;
	हाल IPV6_SADDR_RULE_SCOPE:
		/* Rule 2: Prefer appropriate scope
		 *
		 *      ret
		 *       ^
		 *    -1 |  d 15
		 *    ---+--+-+---> scope
		 *       |
		 *       |             d is scope of the destination.
		 *  B-d  |  \
		 *       |   \      <- smaller scope is better अगर
		 *  B-15 |    \        अगर scope is enough क्रम destination.
		 *       |             ret = B - scope (-1 <= scope >= d <= 15).
		 * d-C-1 | /
		 *       |/         <- greater is better
		 *   -C  /             अगर scope is not enough क्रम destination.
		 *      /|             ret = scope - C (-1 <= d < scope <= 15).
		 *
		 * d - C - 1 < B -15 (क्रम all -1 <= d <= 15).
		 * C > d + 14 - B >= 15 + 14 - B = 29 - B.
		 * Assume B = 0 and we get C > 29.
		 */
		ret = __ipv6_addr_src_scope(score->addr_type);
		अगर (ret >= dst->scope)
			ret = -ret;
		अन्यथा
			ret -= 128;	/* 30 is enough */
		score->scopedist = ret;
		अवरोध;
	हाल IPV6_SADDR_RULE_PREFERRED:
	    अणु
		/* Rule 3: Aव्योम deprecated and optimistic addresses */
		u8 aव्योम = IFA_F_DEPRECATED;

		अगर (!ipv6_use_optimistic_addr(net, score->अगरa->idev))
			aव्योम |= IFA_F_OPTIMISTIC;
		ret = ipv6_saddr_preferred(score->addr_type) ||
		      !(score->अगरa->flags & aव्योम);
		अवरोध;
	    पूर्ण
#अगर_घोषित CONFIG_IPV6_MIP6
	हाल IPV6_SADDR_RULE_HOA:
	    अणु
		/* Rule 4: Prefer home address */
		पूर्णांक prefhome = !(dst->prefs & IPV6_PREFER_SRC_COA);
		ret = !(score->अगरa->flags & IFA_F_HOMEADDRESS) ^ prefhome;
		अवरोध;
	    पूर्ण
#पूर्ण_अगर
	हाल IPV6_SADDR_RULE_OIF:
		/* Rule 5: Prefer outgoing पूर्णांकerface */
		ret = (!dst->अगरindex ||
		       dst->अगरindex == score->अगरa->idev->dev->अगरindex);
		अवरोध;
	हाल IPV6_SADDR_RULE_LABEL:
		/* Rule 6: Prefer matching label */
		ret = ipv6_addr_label(net,
				      &score->अगरa->addr, score->addr_type,
				      score->अगरa->idev->dev->अगरindex) == dst->label;
		अवरोध;
	हाल IPV6_SADDR_RULE_PRIVACY:
	    अणु
		/* Rule 7: Prefer खुला address
		 * Note: prefer temporary address अगर use_tempaddr >= 2
		 */
		पूर्णांक prefपंचांगp = dst->prefs & (IPV6_PREFER_SRC_PUBLIC|IPV6_PREFER_SRC_TMP) ?
				!!(dst->prefs & IPV6_PREFER_SRC_TMP) :
				score->अगरa->idev->cnf.use_tempaddr >= 2;
		ret = (!(score->अगरa->flags & IFA_F_TEMPORARY)) ^ prefपंचांगp;
		अवरोध;
	    पूर्ण
	हाल IPV6_SADDR_RULE_ORCHID:
		/* Rule 8-: Prefer ORCHID vs ORCHID or
		 *	    non-ORCHID vs non-ORCHID
		 */
		ret = !(ipv6_addr_orchid(&score->अगरa->addr) ^
			ipv6_addr_orchid(dst->addr));
		अवरोध;
	हाल IPV6_SADDR_RULE_PREFIX:
		/* Rule 8: Use दीर्घest matching prefix */
		ret = ipv6_addr_dअगरf(&score->अगरa->addr, dst->addr);
		अगर (ret > score->अगरa->prefix_len)
			ret = score->अगरa->prefix_len;
		score->matchlen = ret;
		अवरोध;
#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	हाल IPV6_SADDR_RULE_NOT_OPTIMISTIC:
		/* Optimistic addresses still have lower precedence than other
		 * preferred addresses.
		 */
		ret = !(score->अगरa->flags & IFA_F_OPTIMISTIC);
		अवरोध;
#पूर्ण_अगर
	शेष:
		ret = 0;
	पूर्ण

	अगर (ret)
		__set_bit(i, score->scorebits);
	score->rule = i;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक __ipv6_dev_get_saddr(काष्ठा net *net,
				काष्ठा ipv6_saddr_dst *dst,
				काष्ठा inet6_dev *idev,
				काष्ठा ipv6_saddr_score *scores,
				पूर्णांक hiscore_idx)
अणु
	काष्ठा ipv6_saddr_score *score = &scores[1 - hiscore_idx], *hiscore = &scores[hiscore_idx];

	list_क्रम_each_entry_rcu(score->अगरa, &idev->addr_list, अगर_list) अणु
		पूर्णांक i;

		/*
		 * - Tentative Address (RFC2462 section 5.4)
		 *  - A tentative address is not considered
		 *    "assigned to an interface" in the traditional
		 *    sense, unless it is also flagged as optimistic.
		 * - Candidate Source Address (section 4)
		 *  - In any हाल, anycast addresses, multicast
		 *    addresses, and the unspecअगरied address MUST
		 *    NOT be included in a candidate set.
		 */
		अगर ((score->अगरa->flags & IFA_F_TENTATIVE) &&
		    (!(score->अगरa->flags & IFA_F_OPTIMISTIC)))
			जारी;

		score->addr_type = __ipv6_addr_type(&score->अगरa->addr);

		अगर (unlikely(score->addr_type == IPV6_ADDR_ANY ||
			     score->addr_type & IPV6_ADDR_MULTICAST)) अणु
			net_dbg_ratelimited("ADDRCONF: unspecified / multicast address assigned as unicast address on %s",
					    idev->dev->name);
			जारी;
		पूर्ण

		score->rule = -1;
		biपंचांगap_zero(score->scorebits, IPV6_SADDR_RULE_MAX);

		क्रम (i = 0; i < IPV6_SADDR_RULE_MAX; i++) अणु
			पूर्णांक minihiscore, miniscore;

			minihiscore = ipv6_get_saddr_eval(net, hiscore, dst, i);
			miniscore = ipv6_get_saddr_eval(net, score, dst, i);

			अगर (minihiscore > miniscore) अणु
				अगर (i == IPV6_SADDR_RULE_SCOPE &&
				    score->scopedist > 0) अणु
					/*
					 * special हाल:
					 * each reमुख्यing entry
					 * has too small (not enough)
					 * scope, because अगरa entries
					 * are sorted by their scope
					 * values.
					 */
					जाओ out;
				पूर्ण
				अवरोध;
			पूर्ण अन्यथा अगर (minihiscore < miniscore) अणु
				swap(hiscore, score);
				hiscore_idx = 1 - hiscore_idx;

				/* restore our iterator */
				score->अगरa = hiscore->अगरa;

				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस hiscore_idx;
पूर्ण

अटल पूर्णांक ipv6_get_saddr_master(काष्ठा net *net,
				 स्थिर काष्ठा net_device *dst_dev,
				 स्थिर काष्ठा net_device *master,
				 काष्ठा ipv6_saddr_dst *dst,
				 काष्ठा ipv6_saddr_score *scores,
				 पूर्णांक hiscore_idx)
अणु
	काष्ठा inet6_dev *idev;

	idev = __in6_dev_get(dst_dev);
	अगर (idev)
		hiscore_idx = __ipv6_dev_get_saddr(net, dst, idev,
						   scores, hiscore_idx);

	idev = __in6_dev_get(master);
	अगर (idev)
		hiscore_idx = __ipv6_dev_get_saddr(net, dst, idev,
						   scores, hiscore_idx);

	वापस hiscore_idx;
पूर्ण

पूर्णांक ipv6_dev_get_saddr(काष्ठा net *net, स्थिर काष्ठा net_device *dst_dev,
		       स्थिर काष्ठा in6_addr *daddr, अचिन्हित पूर्णांक prefs,
		       काष्ठा in6_addr *saddr)
अणु
	काष्ठा ipv6_saddr_score scores[2], *hiscore;
	काष्ठा ipv6_saddr_dst dst;
	काष्ठा inet6_dev *idev;
	काष्ठा net_device *dev;
	पूर्णांक dst_type;
	bool use_oअगर_addr = false;
	पूर्णांक hiscore_idx = 0;
	पूर्णांक ret = 0;

	dst_type = __ipv6_addr_type(daddr);
	dst.addr = daddr;
	dst.अगरindex = dst_dev ? dst_dev->अगरindex : 0;
	dst.scope = __ipv6_addr_src_scope(dst_type);
	dst.label = ipv6_addr_label(net, daddr, dst_type, dst.अगरindex);
	dst.prefs = prefs;

	scores[hiscore_idx].rule = -1;
	scores[hiscore_idx].अगरa = शून्य;

	rcu_पढ़ो_lock();

	/* Candidate Source Address (section 4)
	 *  - multicast and link-local destination address,
	 *    the set of candidate source address MUST only
	 *    include addresses asचिन्हित to पूर्णांकerfaces
	 *    beदीर्घing to the same link as the outgoing
	 *    पूर्णांकerface.
	 * (- For site-local destination addresses, the
	 *    set of candidate source addresses MUST only
	 *    include addresses asचिन्हित to पूर्णांकerfaces
	 *    beदीर्घing to the same site as the outgoing
	 *    पूर्णांकerface.)
	 *  - "It is RECOMMENDED that the candidate source addresses
	 *    be the set of unicast addresses asचिन्हित to the
	 *    पूर्णांकerface that will be used to send to the destination
	 *    (the 'outgoing' पूर्णांकerface)." (RFC 6724)
	 */
	अगर (dst_dev) अणु
		idev = __in6_dev_get(dst_dev);
		अगर ((dst_type & IPV6_ADDR_MULTICAST) ||
		    dst.scope <= IPV6_ADDR_SCOPE_LINKLOCAL ||
		    (idev && idev->cnf.use_oअगर_addrs_only)) अणु
			use_oअगर_addr = true;
		पूर्ण
	पूर्ण

	अगर (use_oअगर_addr) अणु
		अगर (idev)
			hiscore_idx = __ipv6_dev_get_saddr(net, &dst, idev, scores, hiscore_idx);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा net_device *master;
		पूर्णांक master_idx = 0;

		/* अगर dst_dev exists and is enslaved to an L3 device, then
		 * prefer addresses from dst_dev and then the master over
		 * any other enslaved devices in the L3 करोमुख्य.
		 */
		master = l3mdev_master_dev_rcu(dst_dev);
		अगर (master) अणु
			master_idx = master->अगरindex;

			hiscore_idx = ipv6_get_saddr_master(net, dst_dev,
							    master, &dst,
							    scores, hiscore_idx);

			अगर (scores[hiscore_idx].अगरa)
				जाओ out;
		पूर्ण

		क्रम_each_netdev_rcu(net, dev) अणु
			/* only consider addresses on devices in the
			 * same L3 करोमुख्य
			 */
			अगर (l3mdev_master_अगरindex_rcu(dev) != master_idx)
				जारी;
			idev = __in6_dev_get(dev);
			अगर (!idev)
				जारी;
			hiscore_idx = __ipv6_dev_get_saddr(net, &dst, idev, scores, hiscore_idx);
		पूर्ण
	पूर्ण

out:
	hiscore = &scores[hiscore_idx];
	अगर (!hiscore->अगरa)
		ret = -EADDRNOTAVAIL;
	अन्यथा
		*saddr = hiscore->अगरa->addr;

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ipv6_dev_get_saddr);

पूर्णांक __ipv6_get_lladdr(काष्ठा inet6_dev *idev, काष्ठा in6_addr *addr,
		      u32 banned_flags)
अणु
	काष्ठा inet6_अगरaddr *अगरp;
	पूर्णांक err = -EADDRNOTAVAIL;

	list_क्रम_each_entry_reverse(अगरp, &idev->addr_list, अगर_list) अणु
		अगर (अगरp->scope > IFA_LINK)
			अवरोध;
		अगर (अगरp->scope == IFA_LINK &&
		    !(अगरp->flags & banned_flags)) अणु
			*addr = अगरp->addr;
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक ipv6_get_lladdr(काष्ठा net_device *dev, काष्ठा in6_addr *addr,
		    u32 banned_flags)
अणु
	काष्ठा inet6_dev *idev;
	पूर्णांक err = -EADDRNOTAVAIL;

	rcu_पढ़ो_lock();
	idev = __in6_dev_get(dev);
	अगर (idev) अणु
		पढ़ो_lock_bh(&idev->lock);
		err = __ipv6_get_lladdr(idev, addr, banned_flags);
		पढ़ो_unlock_bh(&idev->lock);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक ipv6_count_addresses(स्थिर काष्ठा inet6_dev *idev)
अणु
	स्थिर काष्ठा inet6_अगरaddr *अगरp;
	पूर्णांक cnt = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(अगरp, &idev->addr_list, अगर_list)
		cnt++;
	rcu_पढ़ो_unlock();
	वापस cnt;
पूर्ण

पूर्णांक ipv6_chk_addr(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
		  स्थिर काष्ठा net_device *dev, पूर्णांक strict)
अणु
	वापस ipv6_chk_addr_and_flags(net, addr, dev, !dev,
				       strict, IFA_F_TENTATIVE);
पूर्ण
EXPORT_SYMBOL(ipv6_chk_addr);

/* device argument is used to find the L3 करोमुख्य of पूर्णांकerest. If
 * skip_dev_check is set, then the अगरp device is not checked against
 * the passed in dev argument. So the 2 हालs क्रम addresses checks are:
 *   1. करोes the address exist in the L3 करोमुख्य that dev is part of
 *      (skip_dev_check = true), or
 *
 *   2. करोes the address exist on the specअगरic device
 *      (skip_dev_check = false)
 */
अटल काष्ठा net_device *
__ipv6_chk_addr_and_flags(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			  स्थिर काष्ठा net_device *dev, bool skip_dev_check,
			  पूर्णांक strict, u32 banned_flags)
अणु
	अचिन्हित पूर्णांक hash = inet6_addr_hash(net, addr);
	काष्ठा net_device *l3mdev, *ndev;
	काष्ठा inet6_अगरaddr *अगरp;
	u32 अगरp_flags;

	rcu_पढ़ो_lock();

	l3mdev = l3mdev_master_dev_rcu(dev);
	अगर (skip_dev_check)
		dev = शून्य;

	hlist_क्रम_each_entry_rcu(अगरp, &inet6_addr_lst[hash], addr_lst) अणु
		ndev = अगरp->idev->dev;
		अगर (!net_eq(dev_net(ndev), net))
			जारी;

		अगर (l3mdev_master_dev_rcu(ndev) != l3mdev)
			जारी;

		/* Decouple optimistic from tentative क्रम evaluation here.
		 * Ban optimistic addresses explicitly, when required.
		 */
		अगरp_flags = (अगरp->flags&IFA_F_OPTIMISTIC)
			    ? (अगरp->flags&~IFA_F_TENTATIVE)
			    : अगरp->flags;
		अगर (ipv6_addr_equal(&अगरp->addr, addr) &&
		    !(अगरp_flags&banned_flags) &&
		    (!dev || ndev == dev ||
		     !(अगरp->scope&(IFA_LINK|IFA_HOST) || strict))) अणु
			rcu_पढ़ो_unlock();
			वापस ndev;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

पूर्णांक ipv6_chk_addr_and_flags(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
			    स्थिर काष्ठा net_device *dev, bool skip_dev_check,
			    पूर्णांक strict, u32 banned_flags)
अणु
	वापस __ipv6_chk_addr_and_flags(net, addr, dev, skip_dev_check,
					 strict, banned_flags) ? 1 : 0;
पूर्ण
EXPORT_SYMBOL(ipv6_chk_addr_and_flags);


/* Compares an address/prefix_len with addresses on device @dev.
 * If one is found it वापसs true.
 */
bool ipv6_chk_custom_prefix(स्थिर काष्ठा in6_addr *addr,
	स्थिर अचिन्हित पूर्णांक prefix_len, काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा inet6_अगरaddr *अगरa;
	स्थिर काष्ठा inet6_dev *idev;
	bool ret = false;

	rcu_पढ़ो_lock();
	idev = __in6_dev_get(dev);
	अगर (idev) अणु
		list_क्रम_each_entry_rcu(अगरa, &idev->addr_list, अगर_list) अणु
			ret = ipv6_prefix_equal(addr, &अगरa->addr, prefix_len);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ipv6_chk_custom_prefix);

पूर्णांक ipv6_chk_prefix(स्थिर काष्ठा in6_addr *addr, काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा inet6_अगरaddr *अगरa;
	स्थिर काष्ठा inet6_dev *idev;
	पूर्णांक	onlink;

	onlink = 0;
	rcu_पढ़ो_lock();
	idev = __in6_dev_get(dev);
	अगर (idev) अणु
		list_क्रम_each_entry_rcu(अगरa, &idev->addr_list, अगर_list) अणु
			onlink = ipv6_prefix_equal(addr, &अगरa->addr,
						   अगरa->prefix_len);
			अगर (onlink)
				अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस onlink;
पूर्ण
EXPORT_SYMBOL(ipv6_chk_prefix);

/**
 * ipv6_dev_find - find the first device with a given source address.
 * @net: the net namespace
 * @addr: the source address
 * @dev: used to find the L3 करोमुख्य of पूर्णांकerest
 *
 * The caller should be रक्षित by RCU, or RTNL.
 */
काष्ठा net_device *ipv6_dev_find(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
				 काष्ठा net_device *dev)
अणु
	वापस __ipv6_chk_addr_and_flags(net, addr, dev, !dev, 1,
					 IFA_F_TENTATIVE);
पूर्ण
EXPORT_SYMBOL(ipv6_dev_find);

काष्ठा inet6_अगरaddr *ipv6_get_अगरaddr(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr,
				     काष्ठा net_device *dev, पूर्णांक strict)
अणु
	अचिन्हित पूर्णांक hash = inet6_addr_hash(net, addr);
	काष्ठा inet6_अगरaddr *अगरp, *result = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(अगरp, &inet6_addr_lst[hash], addr_lst) अणु
		अगर (!net_eq(dev_net(अगरp->idev->dev), net))
			जारी;
		अगर (ipv6_addr_equal(&अगरp->addr, addr)) अणु
			अगर (!dev || अगरp->idev->dev == dev ||
			    !(अगरp->scope&(IFA_LINK|IFA_HOST) || strict)) अणु
				result = अगरp;
				in6_अगरa_hold(अगरp);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस result;
पूर्ण

/* Gets referenced address, destroys अगरaddr */

अटल व्योम addrconf_dad_stop(काष्ठा inet6_अगरaddr *अगरp, पूर्णांक dad_failed)
अणु
	अगर (dad_failed)
		अगरp->flags |= IFA_F_DADFAILED;

	अगर (अगरp->flags&IFA_F_TEMPORARY) अणु
		काष्ठा inet6_अगरaddr *अगरpub;
		spin_lock_bh(&अगरp->lock);
		अगरpub = अगरp->अगरpub;
		अगर (अगरpub) अणु
			in6_अगरa_hold(अगरpub);
			spin_unlock_bh(&अगरp->lock);
			ipv6_create_tempaddr(अगरpub, true);
			in6_अगरa_put(अगरpub);
		पूर्ण अन्यथा अणु
			spin_unlock_bh(&अगरp->lock);
		पूर्ण
		ipv6_del_addr(अगरp);
	पूर्ण अन्यथा अगर (अगरp->flags&IFA_F_PERMANENT || !dad_failed) अणु
		spin_lock_bh(&अगरp->lock);
		addrconf_del_dad_work(अगरp);
		अगरp->flags |= IFA_F_TENTATIVE;
		अगर (dad_failed)
			अगरp->flags &= ~IFA_F_OPTIMISTIC;
		spin_unlock_bh(&अगरp->lock);
		अगर (dad_failed)
			ipv6_अगरa_notअगरy(0, अगरp);
		in6_अगरa_put(अगरp);
	पूर्ण अन्यथा अणु
		ipv6_del_addr(अगरp);
	पूर्ण
पूर्ण

अटल पूर्णांक addrconf_dad_end(काष्ठा inet6_अगरaddr *अगरp)
अणु
	पूर्णांक err = -ENOENT;

	spin_lock_bh(&अगरp->lock);
	अगर (अगरp->state == INET6_IFADDR_STATE_DAD) अणु
		अगरp->state = INET6_IFADDR_STATE_POSTDAD;
		err = 0;
	पूर्ण
	spin_unlock_bh(&अगरp->lock);

	वापस err;
पूर्ण

व्योम addrconf_dad_failure(काष्ठा sk_buff *skb, काष्ठा inet6_अगरaddr *अगरp)
अणु
	काष्ठा inet6_dev *idev = अगरp->idev;
	काष्ठा net *net = dev_net(अगरp->idev->dev);

	अगर (addrconf_dad_end(अगरp)) अणु
		in6_अगरa_put(अगरp);
		वापस;
	पूर्ण

	net_info_ratelimited("%s: IPv6 duplicate address %pI6c used by %pM detected!\n",
			     अगरp->idev->dev->name, &अगरp->addr, eth_hdr(skb)->h_source);

	spin_lock_bh(&अगरp->lock);

	अगर (अगरp->flags & IFA_F_STABLE_PRIVACY) अणु
		काष्ठा in6_addr new_addr;
		काष्ठा inet6_अगरaddr *अगरp2;
		पूर्णांक retries = अगरp->stable_privacy_retry + 1;
		काष्ठा अगरa6_config cfg = अणु
			.pfx = &new_addr,
			.plen = अगरp->prefix_len,
			.अगरa_flags = अगरp->flags,
			.valid_lft = अगरp->valid_lft,
			.preferred_lft = अगरp->prefered_lft,
			.scope = अगरp->scope,
		पूर्ण;

		अगर (retries > net->ipv6.sysctl.idgen_retries) अणु
			net_info_ratelimited("%s: privacy stable address generation failed because of DAD conflicts!\n",
					     अगरp->idev->dev->name);
			जाओ errdad;
		पूर्ण

		new_addr = अगरp->addr;
		अगर (ipv6_generate_stable_address(&new_addr, retries,
						 idev))
			जाओ errdad;

		spin_unlock_bh(&अगरp->lock);

		अगर (idev->cnf.max_addresses &&
		    ipv6_count_addresses(idev) >=
		    idev->cnf.max_addresses)
			जाओ lock_errdad;

		net_info_ratelimited("%s: generating new stable privacy address because of DAD conflict\n",
				     अगरp->idev->dev->name);

		अगरp2 = ipv6_add_addr(idev, &cfg, false, शून्य);
		अगर (IS_ERR(अगरp2))
			जाओ lock_errdad;

		spin_lock_bh(&अगरp2->lock);
		अगरp2->stable_privacy_retry = retries;
		अगरp2->state = INET6_IFADDR_STATE_PREDAD;
		spin_unlock_bh(&अगरp2->lock);

		addrconf_mod_dad_work(अगरp2, net->ipv6.sysctl.idgen_delay);
		in6_अगरa_put(अगरp2);
lock_errdad:
		spin_lock_bh(&अगरp->lock);
	पूर्ण

errdad:
	/* transition from _POSTDAD to _ERRDAD */
	अगरp->state = INET6_IFADDR_STATE_ERRDAD;
	spin_unlock_bh(&अगरp->lock);

	addrconf_mod_dad_work(अगरp, 0);
	in6_अगरa_put(अगरp);
पूर्ण

/* Join to solicited addr multicast group.
 * caller must hold RTNL */
व्योम addrconf_join_solict(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा in6_addr maddr;

	अगर (dev->flags&(IFF_LOOPBACK|IFF_NOARP))
		वापस;

	addrconf_addr_solict_mult(addr, &maddr);
	ipv6_dev_mc_inc(dev, &maddr);
पूर्ण

/* caller must hold RTNL */
व्योम addrconf_leave_solict(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा in6_addr maddr;

	अगर (idev->dev->flags&(IFF_LOOPBACK|IFF_NOARP))
		वापस;

	addrconf_addr_solict_mult(addr, &maddr);
	__ipv6_dev_mc_dec(idev, &maddr);
पूर्ण

/* caller must hold RTNL */
अटल व्योम addrconf_join_anycast(काष्ठा inet6_अगरaddr *अगरp)
अणु
	काष्ठा in6_addr addr;

	अगर (अगरp->prefix_len >= 127) /* RFC 6164 */
		वापस;
	ipv6_addr_prefix(&addr, &अगरp->addr, अगरp->prefix_len);
	अगर (ipv6_addr_any(&addr))
		वापस;
	__ipv6_dev_ac_inc(अगरp->idev, &addr);
पूर्ण

/* caller must hold RTNL */
अटल व्योम addrconf_leave_anycast(काष्ठा inet6_अगरaddr *अगरp)
अणु
	काष्ठा in6_addr addr;

	अगर (अगरp->prefix_len >= 127) /* RFC 6164 */
		वापस;
	ipv6_addr_prefix(&addr, &अगरp->addr, अगरp->prefix_len);
	अगर (ipv6_addr_any(&addr))
		वापस;
	__ipv6_dev_ac_dec(अगरp->idev, &addr);
पूर्ण

अटल पूर्णांक addrconf_अगरid_6lowpan(u8 *eui, काष्ठा net_device *dev)
अणु
	चयन (dev->addr_len) अणु
	हाल ETH_ALEN:
		स_नकल(eui, dev->dev_addr, 3);
		eui[3] = 0xFF;
		eui[4] = 0xFE;
		स_नकल(eui + 5, dev->dev_addr + 3, 3);
		अवरोध;
	हाल EUI64_ADDR_LEN:
		स_नकल(eui, dev->dev_addr, EUI64_ADDR_LEN);
		eui[0] ^= 2;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक addrconf_अगरid_ieee1394(u8 *eui, काष्ठा net_device *dev)
अणु
	जोड़ fwnet_hwaddr *ha;

	अगर (dev->addr_len != FWNET_ALEN)
		वापस -1;

	ha = (जोड़ fwnet_hwaddr *)dev->dev_addr;

	स_नकल(eui, &ha->uc.uniq_id, माप(ha->uc.uniq_id));
	eui[0] ^= 2;
	वापस 0;
पूर्ण

अटल पूर्णांक addrconf_अगरid_arcnet(u8 *eui, काष्ठा net_device *dev)
अणु
	/* XXX: inherit EUI-64 from other पूर्णांकerface -- yoshfuji */
	अगर (dev->addr_len != ARCNET_ALEN)
		वापस -1;
	स_रखो(eui, 0, 7);
	eui[7] = *(u8 *)dev->dev_addr;
	वापस 0;
पूर्ण

अटल पूर्णांक addrconf_अगरid_infiniband(u8 *eui, काष्ठा net_device *dev)
अणु
	अगर (dev->addr_len != INFINIBAND_ALEN)
		वापस -1;
	स_नकल(eui, dev->dev_addr + 12, 8);
	eui[0] |= 2;
	वापस 0;
पूर्ण

अटल पूर्णांक __ipv6_isatap_अगरid(u8 *eui, __be32 addr)
अणु
	अगर (addr == 0)
		वापस -1;
	eui[0] = (ipv4_is_zeronet(addr) || ipv4_is_निजी_10(addr) ||
		  ipv4_is_loopback(addr) || ipv4_is_linklocal_169(addr) ||
		  ipv4_is_निजी_172(addr) || ipv4_is_test_192(addr) ||
		  ipv4_is_anycast_6to4(addr) || ipv4_is_निजी_192(addr) ||
		  ipv4_is_test_198(addr) || ipv4_is_multicast(addr) ||
		  ipv4_is_lbcast(addr)) ? 0x00 : 0x02;
	eui[1] = 0;
	eui[2] = 0x5E;
	eui[3] = 0xFE;
	स_नकल(eui + 4, &addr, 4);
	वापस 0;
पूर्ण

अटल पूर्णांक addrconf_अगरid_sit(u8 *eui, काष्ठा net_device *dev)
अणु
	अगर (dev->priv_flags & IFF_ISATAP)
		वापस __ipv6_isatap_अगरid(eui, *(__be32 *)dev->dev_addr);
	वापस -1;
पूर्ण

अटल पूर्णांक addrconf_अगरid_gre(u8 *eui, काष्ठा net_device *dev)
अणु
	वापस __ipv6_isatap_अगरid(eui, *(__be32 *)dev->dev_addr);
पूर्ण

अटल पूर्णांक addrconf_अगरid_ip6tnl(u8 *eui, काष्ठा net_device *dev)
अणु
	स_नकल(eui, dev->perm_addr, 3);
	स_नकल(eui + 5, dev->perm_addr + 3, 3);
	eui[3] = 0xFF;
	eui[4] = 0xFE;
	eui[0] ^= 2;
	वापस 0;
पूर्ण

अटल पूर्णांक ipv6_generate_eui64(u8 *eui, काष्ठा net_device *dev)
अणु
	चयन (dev->type) अणु
	हाल ARPHRD_ETHER:
	हाल ARPHRD_FDDI:
		वापस addrconf_अगरid_eui48(eui, dev);
	हाल ARPHRD_ARCNET:
		वापस addrconf_अगरid_arcnet(eui, dev);
	हाल ARPHRD_INFINIBAND:
		वापस addrconf_अगरid_infiniband(eui, dev);
	हाल ARPHRD_SIT:
		वापस addrconf_अगरid_sit(eui, dev);
	हाल ARPHRD_IPGRE:
	हाल ARPHRD_TUNNEL:
		वापस addrconf_अगरid_gre(eui, dev);
	हाल ARPHRD_6LOWPAN:
		वापस addrconf_अगरid_6lowpan(eui, dev);
	हाल ARPHRD_IEEE1394:
		वापस addrconf_अगरid_ieee1394(eui, dev);
	हाल ARPHRD_TUNNEL6:
	हाल ARPHRD_IP6GRE:
	हाल ARPHRD_RAWIP:
		वापस addrconf_अगरid_ip6tnl(eui, dev);
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक ipv6_inherit_eui64(u8 *eui, काष्ठा inet6_dev *idev)
अणु
	पूर्णांक err = -1;
	काष्ठा inet6_अगरaddr *अगरp;

	पढ़ो_lock_bh(&idev->lock);
	list_क्रम_each_entry_reverse(अगरp, &idev->addr_list, अगर_list) अणु
		अगर (अगरp->scope > IFA_LINK)
			अवरोध;
		अगर (अगरp->scope == IFA_LINK && !(अगरp->flags&IFA_F_TENTATIVE)) अणु
			स_नकल(eui, अगरp->addr.s6_addr+8, 8);
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&idev->lock);
	वापस err;
पूर्ण

/* Generation of a अक्रमomized Interface Identअगरier
 * draft-ietf-6man-rfc4941bis, Section 3.3.1
 */

अटल व्योम ipv6_gen_rnd_iid(काष्ठा in6_addr *addr)
अणु
regen:
	get_अक्रमom_bytes(&addr->s6_addr[8], 8);

	/* <draft-ietf-6man-rfc4941bis-08.txt>, Section 3.3.1:
	 * check अगर generated address is not inappropriate:
	 *
	 * - Reserved IPv6 Interface Identअगरiers
	 * - XXX: alपढ़ोy asचिन्हित to an address on the device
	 */

	/* Subnet-router anycast: 0000:0000:0000:0000 */
	अगर (!(addr->s6_addr32[2] | addr->s6_addr32[3]))
		जाओ regen;

	/* IANA Ethernet block: 0200:5EFF:FE00:0000-0200:5EFF:FE00:5212
	 * Proxy Mobile IPv6:   0200:5EFF:FE00:5213
	 * IANA Ethernet block: 0200:5EFF:FE00:5214-0200:5EFF:FEFF:FFFF
	 */
	अगर (ntohl(addr->s6_addr32[2]) == 0x02005eff &&
	    (ntohl(addr->s6_addr32[3]) & 0Xff000000) == 0xfe000000)
		जाओ regen;

	/* Reserved subnet anycast addresses */
	अगर (ntohl(addr->s6_addr32[2]) == 0xfdffffff &&
	    ntohl(addr->s6_addr32[3]) >= 0Xffffff80)
		जाओ regen;
पूर्ण

/*
 *	Add prefix route.
 */

अटल व्योम
addrconf_prefix_route(काष्ठा in6_addr *pfx, पूर्णांक plen, u32 metric,
		      काष्ठा net_device *dev, अचिन्हित दीर्घ expires,
		      u32 flags, gfp_t gfp_flags)
अणु
	काष्ठा fib6_config cfg = अणु
		.fc_table = l3mdev_fib_table(dev) ? : RT6_TABLE_PREFIX,
		.fc_metric = metric ? : IP6_RT_PRIO_ADDRCONF,
		.fc_अगरindex = dev->अगरindex,
		.fc_expires = expires,
		.fc_dst_len = plen,
		.fc_flags = RTF_UP | flags,
		.fc_nlinfo.nl_net = dev_net(dev),
		.fc_protocol = RTPROT_KERNEL,
		.fc_type = RTN_UNICAST,
	पूर्ण;

	cfg.fc_dst = *pfx;

	/* Prevent useless cloning on PtP SIT.
	   This thing is करोne here expecting that the whole
	   class of non-broadcast devices need not cloning.
	 */
#अगर IS_ENABLED(CONFIG_IPV6_SIT)
	अगर (dev->type == ARPHRD_SIT && (dev->flags & IFF_POINTOPOINT))
		cfg.fc_flags |= RTF_NONEXTHOP;
#पूर्ण_अगर

	ip6_route_add(&cfg, gfp_flags, शून्य);
पूर्ण


अटल काष्ठा fib6_info *addrconf_get_prefix_route(स्थिर काष्ठा in6_addr *pfx,
						  पूर्णांक plen,
						  स्थिर काष्ठा net_device *dev,
						  u32 flags, u32 noflags,
						  bool no_gw)
अणु
	काष्ठा fib6_node *fn;
	काष्ठा fib6_info *rt = शून्य;
	काष्ठा fib6_table *table;
	u32 tb_id = l3mdev_fib_table(dev) ? : RT6_TABLE_PREFIX;

	table = fib6_get_table(dev_net(dev), tb_id);
	अगर (!table)
		वापस शून्य;

	rcu_पढ़ो_lock();
	fn = fib6_locate(&table->tb6_root, pfx, plen, शून्य, 0, true);
	अगर (!fn)
		जाओ out;

	क्रम_each_fib6_node_rt_rcu(fn) अणु
		/* prefix routes only use builtin fib6_nh */
		अगर (rt->nh)
			जारी;

		अगर (rt->fib6_nh->fib_nh_dev->अगरindex != dev->अगरindex)
			जारी;
		अगर (no_gw && rt->fib6_nh->fib_nh_gw_family)
			जारी;
		अगर ((rt->fib6_flags & flags) != flags)
			जारी;
		अगर ((rt->fib6_flags & noflags) != 0)
			जारी;
		अगर (!fib6_info_hold_safe(rt))
			जारी;
		अवरोध;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस rt;
पूर्ण


/* Create "default" multicast route to the पूर्णांकerface */

अटल व्योम addrconf_add_mroute(काष्ठा net_device *dev)
अणु
	काष्ठा fib6_config cfg = अणु
		.fc_table = l3mdev_fib_table(dev) ? : RT6_TABLE_LOCAL,
		.fc_metric = IP6_RT_PRIO_ADDRCONF,
		.fc_अगरindex = dev->अगरindex,
		.fc_dst_len = 8,
		.fc_flags = RTF_UP,
		.fc_type = RTN_MULTICAST,
		.fc_nlinfo.nl_net = dev_net(dev),
		.fc_protocol = RTPROT_KERNEL,
	पूर्ण;

	ipv6_addr_set(&cfg.fc_dst, htonl(0xFF000000), 0, 0, 0);

	ip6_route_add(&cfg, GFP_KERNEL, शून्य);
पूर्ण

अटल काष्ठा inet6_dev *addrconf_add_dev(काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *idev;

	ASSERT_RTNL();

	idev = ipv6_find_idev(dev);
	अगर (IS_ERR(idev))
		वापस idev;

	अगर (idev->cnf.disable_ipv6)
		वापस ERR_PTR(-EACCES);

	/* Add शेष multicast route */
	अगर (!(dev->flags & IFF_LOOPBACK) && !netअगर_is_l3_master(dev))
		addrconf_add_mroute(dev);

	वापस idev;
पूर्ण

अटल व्योम manage_tempaddrs(काष्ठा inet6_dev *idev,
			     काष्ठा inet6_अगरaddr *अगरp,
			     __u32 valid_lft, __u32 prefered_lft,
			     bool create, अचिन्हित दीर्घ now)
अणु
	u32 flags;
	काष्ठा inet6_अगरaddr *अगरt;

	पढ़ो_lock_bh(&idev->lock);
	/* update all temporary addresses in the list */
	list_क्रम_each_entry(अगरt, &idev->tempaddr_list, पंचांगp_list) अणु
		पूर्णांक age, max_valid, max_prefered;

		अगर (अगरp != अगरt->अगरpub)
			जारी;

		/* RFC 4941 section 3.3:
		 * If a received option will extend the lअगरeसमय of a खुला
		 * address, the lअगरeबार of temporary addresses should
		 * be extended, subject to the overall स्थिरraपूर्णांक that no
		 * temporary addresses should ever reमुख्य "valid" or "preferred"
		 * क्रम a समय दीर्घer than (TEMP_VALID_LIFETIME) or
		 * (TEMP_PREFERRED_LIFETIME - DESYNC_FACTOR), respectively.
		 */
		age = (now - अगरt->cstamp) / HZ;
		max_valid = idev->cnf.temp_valid_lft - age;
		अगर (max_valid < 0)
			max_valid = 0;

		max_prefered = idev->cnf.temp_prefered_lft -
			       idev->desync_factor - age;
		अगर (max_prefered < 0)
			max_prefered = 0;

		अगर (valid_lft > max_valid)
			valid_lft = max_valid;

		अगर (prefered_lft > max_prefered)
			prefered_lft = max_prefered;

		spin_lock(&अगरt->lock);
		flags = अगरt->flags;
		अगरt->valid_lft = valid_lft;
		अगरt->prefered_lft = prefered_lft;
		अगरt->tstamp = now;
		अगर (prefered_lft > 0)
			अगरt->flags &= ~IFA_F_DEPRECATED;

		spin_unlock(&अगरt->lock);
		अगर (!(flags&IFA_F_TENTATIVE))
			ipv6_अगरa_notअगरy(0, अगरt);
	पूर्ण

	अगर ((create || list_empty(&idev->tempaddr_list)) &&
	    idev->cnf.use_tempaddr > 0) अणु
		/* When a new खुला address is created as described
		 * in [ADDRCONF], also create a new temporary address.
		 * Also create a temporary address अगर it's enabled but
		 * no temporary address currently exists.
		 */
		पढ़ो_unlock_bh(&idev->lock);
		ipv6_create_tempaddr(अगरp, false);
	पूर्ण अन्यथा अणु
		पढ़ो_unlock_bh(&idev->lock);
	पूर्ण
पूर्ण

अटल bool is_addr_mode_generate_stable(काष्ठा inet6_dev *idev)
अणु
	वापस idev->cnf.addr_gen_mode == IN6_ADDR_GEN_MODE_STABLE_PRIVACY ||
	       idev->cnf.addr_gen_mode == IN6_ADDR_GEN_MODE_RANDOM;
पूर्ण

पूर्णांक addrconf_prefix_rcv_add_addr(काष्ठा net *net, काष्ठा net_device *dev,
				 स्थिर काष्ठा prefix_info *pinfo,
				 काष्ठा inet6_dev *in6_dev,
				 स्थिर काष्ठा in6_addr *addr, पूर्णांक addr_type,
				 u32 addr_flags, bool sllao, bool tokenized,
				 __u32 valid_lft, u32 prefered_lft)
अणु
	काष्ठा inet6_अगरaddr *अगरp = ipv6_get_अगरaddr(net, addr, dev, 1);
	पूर्णांक create = 0;

	अगर (!अगरp && valid_lft) अणु
		पूर्णांक max_addresses = in6_dev->cnf.max_addresses;
		काष्ठा अगरa6_config cfg = अणु
			.pfx = addr,
			.plen = pinfo->prefix_len,
			.अगरa_flags = addr_flags,
			.valid_lft = valid_lft,
			.preferred_lft = prefered_lft,
			.scope = addr_type & IPV6_ADDR_SCOPE_MASK,
		पूर्ण;

#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
		अगर ((net->ipv6.devconf_all->optimistic_dad ||
		     in6_dev->cnf.optimistic_dad) &&
		    !net->ipv6.devconf_all->क्रमwarding && sllao)
			cfg.अगरa_flags |= IFA_F_OPTIMISTIC;
#पूर्ण_अगर

		/* Do not allow to create too much of स्वतःconfigured
		 * addresses; this would be too easy way to crash kernel.
		 */
		अगर (!max_addresses ||
		    ipv6_count_addresses(in6_dev) < max_addresses)
			अगरp = ipv6_add_addr(in6_dev, &cfg, false, शून्य);

		अगर (IS_ERR_OR_शून्य(अगरp))
			वापस -1;

		create = 1;
		spin_lock_bh(&अगरp->lock);
		अगरp->flags |= IFA_F_MANAGETEMPADDR;
		अगरp->cstamp = jअगरfies;
		अगरp->tokenized = tokenized;
		spin_unlock_bh(&अगरp->lock);
		addrconf_dad_start(अगरp);
	पूर्ण

	अगर (अगरp) अणु
		u32 flags;
		अचिन्हित दीर्घ now;
		u32 stored_lft;

		/* Update lअगरeसमय (RFC4862 5.5.3 e)
		 * We deviate from RFC4862 by honoring all Valid Lअगरeबार to
		 * improve the reaction of SLAAC to rक्रमागतbering events
		 * (draft-gont-6man-slaac-rक्रमागत-06, Section 4.2)
		 */
		spin_lock_bh(&अगरp->lock);
		now = jअगरfies;
		अगर (अगरp->valid_lft > (now - अगरp->tstamp) / HZ)
			stored_lft = अगरp->valid_lft - (now - अगरp->tstamp) / HZ;
		अन्यथा
			stored_lft = 0;

		अगर (!create && stored_lft) अणु
			अगरp->valid_lft = valid_lft;
			अगरp->prefered_lft = prefered_lft;
			अगरp->tstamp = now;
			flags = अगरp->flags;
			अगरp->flags &= ~IFA_F_DEPRECATED;
			spin_unlock_bh(&अगरp->lock);

			अगर (!(flags&IFA_F_TENTATIVE))
				ipv6_अगरa_notअगरy(0, अगरp);
		पूर्ण अन्यथा
			spin_unlock_bh(&अगरp->lock);

		manage_tempaddrs(in6_dev, अगरp, valid_lft, prefered_lft,
				 create, now);

		in6_अगरa_put(अगरp);
		addrconf_verअगरy();
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(addrconf_prefix_rcv_add_addr);

व्योम addrconf_prefix_rcv(काष्ठा net_device *dev, u8 *opt, पूर्णांक len, bool sllao)
अणु
	काष्ठा prefix_info *pinfo;
	__u32 valid_lft;
	__u32 prefered_lft;
	पूर्णांक addr_type, err;
	u32 addr_flags = 0;
	काष्ठा inet6_dev *in6_dev;
	काष्ठा net *net = dev_net(dev);

	pinfo = (काष्ठा prefix_info *) opt;

	अगर (len < माप(काष्ठा prefix_info)) अणु
		netdev_dbg(dev, "addrconf: prefix option too short\n");
		वापस;
	पूर्ण

	/*
	 *	Validation checks ([ADDRCONF], page 19)
	 */

	addr_type = ipv6_addr_type(&pinfo->prefix);

	अगर (addr_type & (IPV6_ADDR_MULTICAST|IPV6_ADDR_LINKLOCAL))
		वापस;

	valid_lft = ntohl(pinfo->valid);
	prefered_lft = ntohl(pinfo->prefered);

	अगर (prefered_lft > valid_lft) अणु
		net_warn_ratelimited("addrconf: prefix option has invalid lifetime\n");
		वापस;
	पूर्ण

	in6_dev = in6_dev_get(dev);

	अगर (!in6_dev) अणु
		net_dbg_ratelimited("addrconf: device %s not configured\n",
				    dev->name);
		वापस;
	पूर्ण

	/*
	 *	Two things going on here:
	 *	1) Add routes क्रम on-link prefixes
	 *	2) Configure prefixes with the स्वतः flag set
	 */

	अगर (pinfo->onlink) अणु
		काष्ठा fib6_info *rt;
		अचिन्हित दीर्घ rt_expires;

		/* Aव्योम arithmetic overflow. Really, we could
		 * save rt_expires in seconds, likely valid_lft,
		 * but it would require भागision in fib gc, that it
		 * not good.
		 */
		अगर (HZ > USER_HZ)
			rt_expires = addrconf_समयout_fixup(valid_lft, HZ);
		अन्यथा
			rt_expires = addrconf_समयout_fixup(valid_lft, USER_HZ);

		अगर (addrconf_finite_समयout(rt_expires))
			rt_expires *= HZ;

		rt = addrconf_get_prefix_route(&pinfo->prefix,
					       pinfo->prefix_len,
					       dev,
					       RTF_ADDRCONF | RTF_PREFIX_RT,
					       RTF_DEFAULT, true);

		अगर (rt) अणु
			/* Autoconf prefix route */
			अगर (valid_lft == 0) अणु
				ip6_del_rt(net, rt, false);
				rt = शून्य;
			पूर्ण अन्यथा अगर (addrconf_finite_समयout(rt_expires)) अणु
				/* not infinity */
				fib6_set_expires(rt, jअगरfies + rt_expires);
			पूर्ण अन्यथा अणु
				fib6_clean_expires(rt);
			पूर्ण
		पूर्ण अन्यथा अगर (valid_lft) अणु
			घड़ी_प्रकार expires = 0;
			पूर्णांक flags = RTF_ADDRCONF | RTF_PREFIX_RT;
			अगर (addrconf_finite_समयout(rt_expires)) अणु
				/* not infinity */
				flags |= RTF_EXPIRES;
				expires = jअगरfies_to_घड़ी_प्रकार(rt_expires);
			पूर्ण
			addrconf_prefix_route(&pinfo->prefix, pinfo->prefix_len,
					      0, dev, expires, flags,
					      GFP_ATOMIC);
		पूर्ण
		fib6_info_release(rt);
	पूर्ण

	/* Try to figure out our local address क्रम this prefix */

	अगर (pinfo->स्वतःconf && in6_dev->cnf.स्वतःconf) अणु
		काष्ठा in6_addr addr;
		bool tokenized = false, dev_addr_generated = false;

		अगर (pinfo->prefix_len == 64) अणु
			स_नकल(&addr, &pinfo->prefix, 8);

			अगर (!ipv6_addr_any(&in6_dev->token)) अणु
				पढ़ो_lock_bh(&in6_dev->lock);
				स_नकल(addr.s6_addr + 8,
				       in6_dev->token.s6_addr + 8, 8);
				पढ़ो_unlock_bh(&in6_dev->lock);
				tokenized = true;
			पूर्ण अन्यथा अगर (is_addr_mode_generate_stable(in6_dev) &&
				   !ipv6_generate_stable_address(&addr, 0,
								 in6_dev)) अणु
				addr_flags |= IFA_F_STABLE_PRIVACY;
				जाओ ok;
			पूर्ण अन्यथा अगर (ipv6_generate_eui64(addr.s6_addr + 8, dev) &&
				   ipv6_inherit_eui64(addr.s6_addr + 8, in6_dev)) अणु
				जाओ put;
			पूर्ण अन्यथा अणु
				dev_addr_generated = true;
			पूर्ण
			जाओ ok;
		पूर्ण
		net_dbg_ratelimited("IPv6 addrconf: prefix with wrong length %d\n",
				    pinfo->prefix_len);
		जाओ put;

ok:
		err = addrconf_prefix_rcv_add_addr(net, dev, pinfo, in6_dev,
						   &addr, addr_type,
						   addr_flags, sllao,
						   tokenized, valid_lft,
						   prefered_lft);
		अगर (err)
			जाओ put;

		/* Ignore error हाल here because previous prefix add addr was
		 * successful which will be notअगरied.
		 */
		ndisc_ops_prefix_rcv_add_addr(net, dev, pinfo, in6_dev, &addr,
					      addr_type, addr_flags, sllao,
					      tokenized, valid_lft,
					      prefered_lft,
					      dev_addr_generated);
	पूर्ण
	inet6_prefix_notअगरy(RTM_NEWPREFIX, in6_dev, pinfo);
put:
	in6_dev_put(in6_dev);
पूर्ण

अटल पूर्णांक addrconf_set_sit_dstaddr(काष्ठा net *net, काष्ठा net_device *dev,
		काष्ठा in6_अगरreq *ireq)
अणु
	काष्ठा ip_tunnel_parm p = अणु पूर्ण;
	पूर्णांक err;

	अगर (!(ipv6_addr_type(&ireq->अगरr6_addr) & IPV6_ADDR_COMPATv4))
		वापस -EADDRNOTAVAIL;

	p.iph.daddr = ireq->अगरr6_addr.s6_addr32[3];
	p.iph.version = 4;
	p.iph.ihl = 5;
	p.iph.protocol = IPPROTO_IPV6;
	p.iph.ttl = 64;

	अगर (!dev->netdev_ops->nकरो_tunnel_ctl)
		वापस -EOPNOTSUPP;
	err = dev->netdev_ops->nकरो_tunnel_ctl(dev, &p, SIOCADDTUNNEL);
	अगर (err)
		वापस err;

	dev = __dev_get_by_name(net, p.name);
	अगर (!dev)
		वापस -ENOBUFS;
	वापस dev_खोलो(dev, शून्य);
पूर्ण

/*
 *	Set destination address.
 *	Special हाल क्रम SIT पूर्णांकerfaces where we create a new "virtual"
 *	device.
 */
पूर्णांक addrconf_set_dstaddr(काष्ठा net *net, व्योम __user *arg)
अणु
	काष्ठा net_device *dev;
	काष्ठा in6_अगरreq ireq;
	पूर्णांक err = -ENODEV;

	अगर (!IS_ENABLED(CONFIG_IPV6_SIT))
		वापस -ENODEV;
	अगर (copy_from_user(&ireq, arg, माप(काष्ठा in6_अगरreq)))
		वापस -EFAULT;

	rtnl_lock();
	dev = __dev_get_by_index(net, ireq.अगरr6_अगरindex);
	अगर (dev && dev->type == ARPHRD_SIT)
		err = addrconf_set_sit_dstaddr(net, dev, &ireq);
	rtnl_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक ipv6_mc_config(काष्ठा sock *sk, bool join,
			  स्थिर काष्ठा in6_addr *addr, पूर्णांक अगरindex)
अणु
	पूर्णांक ret;

	ASSERT_RTNL();

	lock_sock(sk);
	अगर (join)
		ret = ipv6_sock_mc_join(sk, अगरindex, addr);
	अन्यथा
		ret = ipv6_sock_mc_drop(sk, अगरindex, addr);
	release_sock(sk);

	वापस ret;
पूर्ण

/*
 *	Manual configuration of address on an पूर्णांकerface
 */
अटल पूर्णांक inet6_addr_add(काष्ठा net *net, पूर्णांक अगरindex,
			  काष्ठा अगरa6_config *cfg,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा inet6_अगरaddr *अगरp;
	काष्ठा inet6_dev *idev;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ समयout;
	घड़ी_प्रकार expires;
	u32 flags;

	ASSERT_RTNL();

	अगर (cfg->plen > 128)
		वापस -EINVAL;

	/* check the lअगरeसमय */
	अगर (!cfg->valid_lft || cfg->preferred_lft > cfg->valid_lft)
		वापस -EINVAL;

	अगर (cfg->अगरa_flags & IFA_F_MANAGETEMPADDR && cfg->plen != 64)
		वापस -EINVAL;

	dev = __dev_get_by_index(net, अगरindex);
	अगर (!dev)
		वापस -ENODEV;

	idev = addrconf_add_dev(dev);
	अगर (IS_ERR(idev))
		वापस PTR_ERR(idev);

	अगर (cfg->अगरa_flags & IFA_F_MCAUTOJOIN) अणु
		पूर्णांक ret = ipv6_mc_config(net->ipv6.mc_स्वतःjoin_sk,
					 true, cfg->pfx, अगरindex);

		अगर (ret < 0)
			वापस ret;
	पूर्ण

	cfg->scope = ipv6_addr_scope(cfg->pfx);

	समयout = addrconf_समयout_fixup(cfg->valid_lft, HZ);
	अगर (addrconf_finite_समयout(समयout)) अणु
		expires = jअगरfies_to_घड़ी_प्रकार(समयout * HZ);
		cfg->valid_lft = समयout;
		flags = RTF_EXPIRES;
	पूर्ण अन्यथा अणु
		expires = 0;
		flags = 0;
		cfg->अगरa_flags |= IFA_F_PERMANENT;
	पूर्ण

	समयout = addrconf_समयout_fixup(cfg->preferred_lft, HZ);
	अगर (addrconf_finite_समयout(समयout)) अणु
		अगर (समयout == 0)
			cfg->अगरa_flags |= IFA_F_DEPRECATED;
		cfg->preferred_lft = समयout;
	पूर्ण

	अगरp = ipv6_add_addr(idev, cfg, true, extack);
	अगर (!IS_ERR(अगरp)) अणु
		अगर (!(cfg->अगरa_flags & IFA_F_NOPREFIXROUTE)) अणु
			addrconf_prefix_route(&अगरp->addr, अगरp->prefix_len,
					      अगरp->rt_priority, dev, expires,
					      flags, GFP_KERNEL);
		पूर्ण

		/* Send a netlink notअगरication अगर DAD is enabled and
		 * optimistic flag is not set
		 */
		अगर (!(अगरp->flags & (IFA_F_OPTIMISTIC | IFA_F_NODAD)))
			ipv6_अगरa_notअगरy(0, अगरp);
		/*
		 * Note that section 3.1 of RFC 4429 indicates
		 * that the Optimistic flag should not be set क्रम
		 * manually configured addresses
		 */
		addrconf_dad_start(अगरp);
		अगर (cfg->अगरa_flags & IFA_F_MANAGETEMPADDR)
			manage_tempaddrs(idev, अगरp, cfg->valid_lft,
					 cfg->preferred_lft, true, jअगरfies);
		in6_अगरa_put(अगरp);
		addrconf_verअगरy_rtnl();
		वापस 0;
	पूर्ण अन्यथा अगर (cfg->अगरa_flags & IFA_F_MCAUTOJOIN) अणु
		ipv6_mc_config(net->ipv6.mc_स्वतःjoin_sk, false,
			       cfg->pfx, अगरindex);
	पूर्ण

	वापस PTR_ERR(अगरp);
पूर्ण

अटल पूर्णांक inet6_addr_del(काष्ठा net *net, पूर्णांक अगरindex, u32 अगरa_flags,
			  स्थिर काष्ठा in6_addr *pfx, अचिन्हित पूर्णांक plen)
अणु
	काष्ठा inet6_अगरaddr *अगरp;
	काष्ठा inet6_dev *idev;
	काष्ठा net_device *dev;

	अगर (plen > 128)
		वापस -EINVAL;

	dev = __dev_get_by_index(net, अगरindex);
	अगर (!dev)
		वापस -ENODEV;

	idev = __in6_dev_get(dev);
	अगर (!idev)
		वापस -ENXIO;

	पढ़ो_lock_bh(&idev->lock);
	list_क्रम_each_entry(अगरp, &idev->addr_list, अगर_list) अणु
		अगर (अगरp->prefix_len == plen &&
		    ipv6_addr_equal(pfx, &अगरp->addr)) अणु
			in6_अगरa_hold(अगरp);
			पढ़ो_unlock_bh(&idev->lock);

			अगर (!(अगरp->flags & IFA_F_TEMPORARY) &&
			    (अगरa_flags & IFA_F_MANAGETEMPADDR))
				manage_tempaddrs(idev, अगरp, 0, 0, false,
						 jअगरfies);
			ipv6_del_addr(अगरp);
			addrconf_verअगरy_rtnl();
			अगर (ipv6_addr_is_multicast(pfx)) अणु
				ipv6_mc_config(net->ipv6.mc_स्वतःjoin_sk,
					       false, pfx, dev->अगरindex);
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&idev->lock);
	वापस -EADDRNOTAVAIL;
पूर्ण


पूर्णांक addrconf_add_अगरaddr(काष्ठा net *net, व्योम __user *arg)
अणु
	काष्ठा अगरa6_config cfg = अणु
		.अगरa_flags = IFA_F_PERMANENT,
		.preferred_lft = अनन्त_LIFE_TIME,
		.valid_lft = अनन्त_LIFE_TIME,
	पूर्ण;
	काष्ठा in6_अगरreq ireq;
	पूर्णांक err;

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (copy_from_user(&ireq, arg, माप(काष्ठा in6_अगरreq)))
		वापस -EFAULT;

	cfg.pfx = &ireq.अगरr6_addr;
	cfg.plen = ireq.अगरr6_prefixlen;

	rtnl_lock();
	err = inet6_addr_add(net, ireq.अगरr6_अगरindex, &cfg, शून्य);
	rtnl_unlock();
	वापस err;
पूर्ण

पूर्णांक addrconf_del_अगरaddr(काष्ठा net *net, व्योम __user *arg)
अणु
	काष्ठा in6_अगरreq ireq;
	पूर्णांक err;

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (copy_from_user(&ireq, arg, माप(काष्ठा in6_अगरreq)))
		वापस -EFAULT;

	rtnl_lock();
	err = inet6_addr_del(net, ireq.अगरr6_अगरindex, 0, &ireq.अगरr6_addr,
			     ireq.अगरr6_prefixlen);
	rtnl_unlock();
	वापस err;
पूर्ण

अटल व्योम add_addr(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *addr,
		     पूर्णांक plen, पूर्णांक scope)
अणु
	काष्ठा inet6_अगरaddr *अगरp;
	काष्ठा अगरa6_config cfg = अणु
		.pfx = addr,
		.plen = plen,
		.अगरa_flags = IFA_F_PERMANENT,
		.valid_lft = अनन्त_LIFE_TIME,
		.preferred_lft = अनन्त_LIFE_TIME,
		.scope = scope
	पूर्ण;

	अगरp = ipv6_add_addr(idev, &cfg, true, शून्य);
	अगर (!IS_ERR(अगरp)) अणु
		spin_lock_bh(&अगरp->lock);
		अगरp->flags &= ~IFA_F_TENTATIVE;
		spin_unlock_bh(&अगरp->lock);
		rt_genid_bump_ipv6(dev_net(idev->dev));
		ipv6_अगरa_notअगरy(RTM_NEWADDR, अगरp);
		in6_अगरa_put(अगरp);
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6_SIT)
अटल व्योम sit_add_v4_addrs(काष्ठा inet6_dev *idev)
अणु
	काष्ठा in6_addr addr;
	काष्ठा net_device *dev;
	काष्ठा net *net = dev_net(idev->dev);
	पूर्णांक scope, plen;
	u32 pflags = 0;

	ASSERT_RTNL();

	स_रखो(&addr, 0, माप(काष्ठा in6_addr));
	स_नकल(&addr.s6_addr32[3], idev->dev->dev_addr, 4);

	अगर (idev->dev->flags&IFF_POINTOPOINT) अणु
		addr.s6_addr32[0] = htonl(0xfe800000);
		scope = IFA_LINK;
		plen = 64;
	पूर्ण अन्यथा अणु
		scope = IPV6_ADDR_COMPATv4;
		plen = 96;
		pflags |= RTF_NONEXTHOP;
	पूर्ण

	अगर (addr.s6_addr32[3]) अणु
		add_addr(idev, &addr, plen, scope);
		addrconf_prefix_route(&addr, plen, 0, idev->dev, 0, pflags,
				      GFP_KERNEL);
		वापस;
	पूर्ण

	क्रम_each_netdev(net, dev) अणु
		काष्ठा in_device *in_dev = __in_dev_get_rtnl(dev);
		अगर (in_dev && (dev->flags & IFF_UP)) अणु
			काष्ठा in_अगरaddr *अगरa;
			पूर्णांक flag = scope;

			in_dev_क्रम_each_अगरa_rtnl(अगरa, in_dev) अणु
				addr.s6_addr32[3] = अगरa->अगरa_local;

				अगर (अगरa->अगरa_scope == RT_SCOPE_LINK)
					जारी;
				अगर (अगरa->अगरa_scope >= RT_SCOPE_HOST) अणु
					अगर (idev->dev->flags&IFF_POINTOPOINT)
						जारी;
					flag |= IFA_HOST;
				पूर्ण

				add_addr(idev, &addr, plen, flag);
				addrconf_prefix_route(&addr, plen, 0, idev->dev,
						      0, pflags, GFP_KERNEL);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम init_loopback(काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev  *idev;

	/* ::1 */

	ASSERT_RTNL();

	idev = ipv6_find_idev(dev);
	अगर (IS_ERR(idev)) अणु
		pr_debug("%s: add_dev failed\n", __func__);
		वापस;
	पूर्ण

	add_addr(idev, &in6addr_loopback, 128, IFA_HOST);
पूर्ण

व्योम addrconf_add_linklocal(काष्ठा inet6_dev *idev,
			    स्थिर काष्ठा in6_addr *addr, u32 flags)
अणु
	काष्ठा अगरa6_config cfg = अणु
		.pfx = addr,
		.plen = 64,
		.अगरa_flags = flags | IFA_F_PERMANENT,
		.valid_lft = अनन्त_LIFE_TIME,
		.preferred_lft = अनन्त_LIFE_TIME,
		.scope = IFA_LINK
	पूर्ण;
	काष्ठा inet6_अगरaddr *अगरp;

#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	अगर ((dev_net(idev->dev)->ipv6.devconf_all->optimistic_dad ||
	     idev->cnf.optimistic_dad) &&
	    !dev_net(idev->dev)->ipv6.devconf_all->क्रमwarding)
		cfg.अगरa_flags |= IFA_F_OPTIMISTIC;
#पूर्ण_अगर

	अगरp = ipv6_add_addr(idev, &cfg, true, शून्य);
	अगर (!IS_ERR(अगरp)) अणु
		addrconf_prefix_route(&अगरp->addr, अगरp->prefix_len, 0, idev->dev,
				      0, 0, GFP_ATOMIC);
		addrconf_dad_start(अगरp);
		in6_अगरa_put(अगरp);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(addrconf_add_linklocal);

अटल bool ipv6_reserved_पूर्णांकerfaceid(काष्ठा in6_addr address)
अणु
	अगर ((address.s6_addr32[2] | address.s6_addr32[3]) == 0)
		वापस true;

	अगर (address.s6_addr32[2] == htonl(0x02005eff) &&
	    ((address.s6_addr32[3] & htonl(0xfe000000)) == htonl(0xfe000000)))
		वापस true;

	अगर (address.s6_addr32[2] == htonl(0xfdffffff) &&
	    ((address.s6_addr32[3] & htonl(0xffffff80)) == htonl(0xffffff80)))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक ipv6_generate_stable_address(काष्ठा in6_addr *address,
					u8 dad_count,
					स्थिर काष्ठा inet6_dev *idev)
अणु
	अटल DEFINE_SPINLOCK(lock);
	अटल __u32 digest[SHA1_DIGEST_WORDS];
	अटल __u32 workspace[SHA1_WORKSPACE_WORDS];

	अटल जोड़ अणु
		अक्षर __data[SHA1_BLOCK_SIZE];
		काष्ठा अणु
			काष्ठा in6_addr secret;
			__be32 prefix[2];
			अचिन्हित अक्षर hwaddr[MAX_ADDR_LEN];
			u8 dad_count;
		पूर्ण __packed;
	पूर्ण data;

	काष्ठा in6_addr secret;
	काष्ठा in6_addr temp;
	काष्ठा net *net = dev_net(idev->dev);

	BUILD_BUG_ON(माप(data.__data) != माप(data));

	अगर (idev->cnf.stable_secret.initialized)
		secret = idev->cnf.stable_secret.secret;
	अन्यथा अगर (net->ipv6.devconf_dflt->stable_secret.initialized)
		secret = net->ipv6.devconf_dflt->stable_secret.secret;
	अन्यथा
		वापस -1;

retry:
	spin_lock_bh(&lock);

	sha1_init(digest);
	स_रखो(&data, 0, माप(data));
	स_रखो(workspace, 0, माप(workspace));
	स_नकल(data.hwaddr, idev->dev->perm_addr, idev->dev->addr_len);
	data.prefix[0] = address->s6_addr32[0];
	data.prefix[1] = address->s6_addr32[1];
	data.secret = secret;
	data.dad_count = dad_count;

	sha1_transक्रमm(digest, data.__data, workspace);

	temp = *address;
	temp.s6_addr32[2] = (__क्रमce __be32)digest[0];
	temp.s6_addr32[3] = (__क्रमce __be32)digest[1];

	spin_unlock_bh(&lock);

	अगर (ipv6_reserved_पूर्णांकerfaceid(temp)) अणु
		dad_count++;
		अगर (dad_count > dev_net(idev->dev)->ipv6.sysctl.idgen_retries)
			वापस -1;
		जाओ retry;
	पूर्ण

	*address = temp;
	वापस 0;
पूर्ण

अटल व्योम ipv6_gen_mode_अक्रमom_init(काष्ठा inet6_dev *idev)
अणु
	काष्ठा ipv6_stable_secret *s = &idev->cnf.stable_secret;

	अगर (s->initialized)
		वापस;
	s = &idev->cnf.stable_secret;
	get_अक्रमom_bytes(&s->secret, माप(s->secret));
	s->initialized = true;
पूर्ण

अटल व्योम addrconf_addr_gen(काष्ठा inet6_dev *idev, bool prefix_route)
अणु
	काष्ठा in6_addr addr;

	/* no link local addresses on L3 master devices */
	अगर (netअगर_is_l3_master(idev->dev))
		वापस;

	/* no link local addresses on devices flagged as slaves */
	अगर (idev->dev->flags & IFF_SLAVE)
		वापस;

	ipv6_addr_set(&addr, htonl(0xFE800000), 0, 0, 0);

	चयन (idev->cnf.addr_gen_mode) अणु
	हाल IN6_ADDR_GEN_MODE_RANDOM:
		ipv6_gen_mode_अक्रमom_init(idev);
		fallthrough;
	हाल IN6_ADDR_GEN_MODE_STABLE_PRIVACY:
		अगर (!ipv6_generate_stable_address(&addr, 0, idev))
			addrconf_add_linklocal(idev, &addr,
					       IFA_F_STABLE_PRIVACY);
		अन्यथा अगर (prefix_route)
			addrconf_prefix_route(&addr, 64, 0, idev->dev,
					      0, 0, GFP_KERNEL);
		अवरोध;
	हाल IN6_ADDR_GEN_MODE_EUI64:
		/* addrconf_add_linklocal also adds a prefix_route and we
		 * only need to care about prefix routes अगर ipv6_generate_eui64
		 * couldn't generate one.
		 */
		अगर (ipv6_generate_eui64(addr.s6_addr + 8, idev->dev) == 0)
			addrconf_add_linklocal(idev, &addr, 0);
		अन्यथा अगर (prefix_route)
			addrconf_prefix_route(&addr, 64, 0, idev->dev,
					      0, 0, GFP_KERNEL);
		अवरोध;
	हाल IN6_ADDR_GEN_MODE_NONE:
	शेष:
		/* will not add any link local address */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम addrconf_dev_config(काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *idev;

	ASSERT_RTNL();

	अगर ((dev->type != ARPHRD_ETHER) &&
	    (dev->type != ARPHRD_FDDI) &&
	    (dev->type != ARPHRD_ARCNET) &&
	    (dev->type != ARPHRD_INFINIBAND) &&
	    (dev->type != ARPHRD_IEEE1394) &&
	    (dev->type != ARPHRD_TUNNEL6) &&
	    (dev->type != ARPHRD_6LOWPAN) &&
	    (dev->type != ARPHRD_IP6GRE) &&
	    (dev->type != ARPHRD_IPGRE) &&
	    (dev->type != ARPHRD_TUNNEL) &&
	    (dev->type != ARPHRD_NONE) &&
	    (dev->type != ARPHRD_RAWIP)) अणु
		/* Alas, we support only Ethernet स्वतःconfiguration. */
		idev = __in6_dev_get(dev);
		अगर (!IS_ERR_OR_शून्य(idev) && dev->flags & IFF_UP &&
		    dev->flags & IFF_MULTICAST)
			ipv6_mc_up(idev);
		वापस;
	पूर्ण

	idev = addrconf_add_dev(dev);
	अगर (IS_ERR(idev))
		वापस;

	/* this device type has no EUI support */
	अगर (dev->type == ARPHRD_NONE &&
	    idev->cnf.addr_gen_mode == IN6_ADDR_GEN_MODE_EUI64)
		idev->cnf.addr_gen_mode = IN6_ADDR_GEN_MODE_RANDOM;

	addrconf_addr_gen(idev, false);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6_SIT)
अटल व्योम addrconf_sit_config(काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *idev;

	ASSERT_RTNL();

	/*
	 * Configure the tunnel with one of our IPv4
	 * addresses... we should configure all of
	 * our v4 addrs in the tunnel
	 */

	idev = ipv6_find_idev(dev);
	अगर (IS_ERR(idev)) अणु
		pr_debug("%s: add_dev failed\n", __func__);
		वापस;
	पूर्ण

	अगर (dev->priv_flags & IFF_ISATAP) अणु
		addrconf_addr_gen(idev, false);
		वापस;
	पूर्ण

	sit_add_v4_addrs(idev);

	अगर (dev->flags&IFF_POINTOPOINT)
		addrconf_add_mroute(dev);
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_NET_IPGRE)
अटल व्योम addrconf_gre_config(काष्ठा net_device *dev)
अणु
	काष्ठा inet6_dev *idev;

	ASSERT_RTNL();

	idev = ipv6_find_idev(dev);
	अगर (IS_ERR(idev)) अणु
		pr_debug("%s: add_dev failed\n", __func__);
		वापस;
	पूर्ण

	addrconf_addr_gen(idev, true);
	अगर (dev->flags & IFF_POINTOPOINT)
		addrconf_add_mroute(dev);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक fixup_permanent_addr(काष्ठा net *net,
				काष्ठा inet6_dev *idev,
				काष्ठा inet6_अगरaddr *अगरp)
अणु
	/* !fib6_node means the host route was हटाओd from the
	 * FIB, क्रम example, अगर 'lo' device is taken करोwn. In that
	 * हाल regenerate the host route.
	 */
	अगर (!अगरp->rt || !अगरp->rt->fib6_node) अणु
		काष्ठा fib6_info *f6i, *prev;

		f6i = addrconf_f6i_alloc(net, idev, &अगरp->addr, false,
					 GFP_ATOMIC);
		अगर (IS_ERR(f6i))
			वापस PTR_ERR(f6i);

		/* अगरp->rt can be accessed outside of rtnl */
		spin_lock(&अगरp->lock);
		prev = अगरp->rt;
		अगरp->rt = f6i;
		spin_unlock(&अगरp->lock);

		fib6_info_release(prev);
	पूर्ण

	अगर (!(अगरp->flags & IFA_F_NOPREFIXROUTE)) अणु
		addrconf_prefix_route(&अगरp->addr, अगरp->prefix_len,
				      अगरp->rt_priority, idev->dev, 0, 0,
				      GFP_ATOMIC);
	पूर्ण

	अगर (अगरp->state == INET6_IFADDR_STATE_PREDAD)
		addrconf_dad_start(अगरp);

	वापस 0;
पूर्ण

अटल व्योम addrconf_permanent_addr(काष्ठा net *net, काष्ठा net_device *dev)
अणु
	काष्ठा inet6_अगरaddr *अगरp, *पंचांगp;
	काष्ठा inet6_dev *idev;

	idev = __in6_dev_get(dev);
	अगर (!idev)
		वापस;

	ग_लिखो_lock_bh(&idev->lock);

	list_क्रम_each_entry_safe(अगरp, पंचांगp, &idev->addr_list, अगर_list) अणु
		अगर ((अगरp->flags & IFA_F_PERMANENT) &&
		    fixup_permanent_addr(net, idev, अगरp) < 0) अणु
			ग_लिखो_unlock_bh(&idev->lock);
			in6_अगरa_hold(अगरp);
			ipv6_del_addr(अगरp);
			ग_लिखो_lock_bh(&idev->lock);

			net_info_ratelimited("%s: Failed to add prefix route for address %pI6c; dropping\n",
					     idev->dev->name, &अगरp->addr);
		पूर्ण
	पूर्ण

	ग_लिखो_unlock_bh(&idev->lock);
पूर्ण

अटल पूर्णांक addrconf_notअगरy(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा netdev_notअगरier_change_info *change_info;
	काष्ठा netdev_notअगरier_changeupper_info *info;
	काष्ठा inet6_dev *idev = __in6_dev_get(dev);
	काष्ठा net *net = dev_net(dev);
	पूर्णांक run_pending = 0;
	पूर्णांक err;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		अगर (!idev && dev->mtu >= IPV6_MIN_MTU) अणु
			idev = ipv6_add_dev(dev);
			अगर (IS_ERR(idev))
				वापस notअगरier_from_त्रुटि_सं(PTR_ERR(idev));
		पूर्ण
		अवरोध;

	हाल NETDEV_CHANGEMTU:
		/* अगर MTU under IPV6_MIN_MTU stop IPv6 on this पूर्णांकerface. */
		अगर (dev->mtu < IPV6_MIN_MTU) अणु
			addrconf_अगरकरोwn(dev, dev != net->loopback_dev);
			अवरोध;
		पूर्ण

		अगर (idev) अणु
			rt6_mtu_change(dev, dev->mtu);
			idev->cnf.mtu6 = dev->mtu;
			अवरोध;
		पूर्ण

		/* allocate new idev */
		idev = ipv6_add_dev(dev);
		अगर (IS_ERR(idev))
			अवरोध;

		/* device is still not पढ़ोy */
		अगर (!(idev->अगर_flags & IF_READY))
			अवरोध;

		run_pending = 1;
		fallthrough;
	हाल NETDEV_UP:
	हाल NETDEV_CHANGE:
		अगर (dev->flags & IFF_SLAVE)
			अवरोध;

		अगर (idev && idev->cnf.disable_ipv6)
			अवरोध;

		अगर (event == NETDEV_UP) अणु
			/* restore routes क्रम permanent addresses */
			addrconf_permanent_addr(net, dev);

			अगर (!addrconf_link_पढ़ोy(dev)) अणु
				/* device is not पढ़ोy yet. */
				pr_debug("ADDRCONF(NETDEV_UP): %s: link is not ready\n",
					 dev->name);
				अवरोध;
			पूर्ण

			अगर (!idev && dev->mtu >= IPV6_MIN_MTU)
				idev = ipv6_add_dev(dev);

			अगर (!IS_ERR_OR_शून्य(idev)) अणु
				idev->अगर_flags |= IF_READY;
				run_pending = 1;
			पूर्ण
		पूर्ण अन्यथा अगर (event == NETDEV_CHANGE) अणु
			अगर (!addrconf_link_पढ़ोy(dev)) अणु
				/* device is still not पढ़ोy. */
				rt6_sync_करोwn_dev(dev, event);
				अवरोध;
			पूर्ण

			अगर (!IS_ERR_OR_शून्य(idev)) अणु
				अगर (idev->अगर_flags & IF_READY) अणु
					/* device is alपढ़ोy configured -
					 * but resend MLD reports, we might
					 * have roamed and need to update
					 * multicast snooping चयनes
					 */
					ipv6_mc_up(idev);
					change_info = ptr;
					अगर (change_info->flags_changed & IFF_NOARP)
						addrconf_dad_run(idev, true);
					rt6_sync_up(dev, RTNH_F_LINKDOWN);
					अवरोध;
				पूर्ण
				idev->अगर_flags |= IF_READY;
			पूर्ण

			pr_info("ADDRCONF(NETDEV_CHANGE): %s: link becomes ready\n",
				dev->name);

			run_pending = 1;
		पूर्ण

		चयन (dev->type) अणु
#अगर IS_ENABLED(CONFIG_IPV6_SIT)
		हाल ARPHRD_SIT:
			addrconf_sit_config(dev);
			अवरोध;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_NET_IPGRE)
		हाल ARPHRD_IPGRE:
			addrconf_gre_config(dev);
			अवरोध;
#पूर्ण_अगर
		हाल ARPHRD_LOOPBACK:
			init_loopback(dev);
			अवरोध;

		शेष:
			addrconf_dev_config(dev);
			अवरोध;
		पूर्ण

		अगर (!IS_ERR_OR_शून्य(idev)) अणु
			अगर (run_pending)
				addrconf_dad_run(idev, false);

			/* Device has an address by now */
			rt6_sync_up(dev, RTNH_F_DEAD);

			/*
			 * If the MTU changed during the पूर्णांकerface करोwn,
			 * when the पूर्णांकerface up, the changed MTU must be
			 * reflected in the idev as well as routers.
			 */
			अगर (idev->cnf.mtu6 != dev->mtu &&
			    dev->mtu >= IPV6_MIN_MTU) अणु
				rt6_mtu_change(dev, dev->mtu);
				idev->cnf.mtu6 = dev->mtu;
			पूर्ण
			idev->tstamp = jअगरfies;
			inet6_अगरinfo_notअगरy(RTM_NEWLINK, idev);

			/*
			 * If the changed mtu during करोwn is lower than
			 * IPV6_MIN_MTU stop IPv6 on this पूर्णांकerface.
			 */
			अगर (dev->mtu < IPV6_MIN_MTU)
				addrconf_अगरकरोwn(dev, dev != net->loopback_dev);
		पूर्ण
		अवरोध;

	हाल NETDEV_DOWN:
	हाल NETDEV_UNREGISTER:
		/*
		 *	Remove all addresses from this पूर्णांकerface.
		 */
		addrconf_अगरकरोwn(dev, event != NETDEV_DOWN);
		अवरोध;

	हाल NETDEV_CHANGENAME:
		अगर (idev) अणु
			snmp6_unरेजिस्टर_dev(idev);
			addrconf_sysctl_unरेजिस्टर(idev);
			err = addrconf_sysctl_रेजिस्टर(idev);
			अगर (err)
				वापस notअगरier_from_त्रुटि_सं(err);
			err = snmp6_रेजिस्टर_dev(idev);
			अगर (err) अणु
				addrconf_sysctl_unरेजिस्टर(idev);
				वापस notअगरier_from_त्रुटि_सं(err);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल NETDEV_PRE_TYPE_CHANGE:
	हाल NETDEV_POST_TYPE_CHANGE:
		अगर (idev)
			addrconf_type_change(dev, event);
		अवरोध;

	हाल NETDEV_CHANGEUPPER:
		info = ptr;

		/* flush all routes अगर dev is linked to or unlinked from
		 * an L3 master device (e.g., VRF)
		 */
		अगर (info->upper_dev && netअगर_is_l3_master(info->upper_dev))
			addrconf_अगरकरोwn(dev, false);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

/*
 *	addrconf module should be notअगरied of a device going up
 */
अटल काष्ठा notअगरier_block ipv6_dev_notf = अणु
	.notअगरier_call = addrconf_notअगरy,
	.priority = ADDRCONF_NOTIFY_PRIORITY,
पूर्ण;

अटल व्योम addrconf_type_change(काष्ठा net_device *dev, अचिन्हित दीर्घ event)
अणु
	काष्ठा inet6_dev *idev;
	ASSERT_RTNL();

	idev = __in6_dev_get(dev);

	अगर (event == NETDEV_POST_TYPE_CHANGE)
		ipv6_mc_remap(idev);
	अन्यथा अगर (event == NETDEV_PRE_TYPE_CHANGE)
		ipv6_mc_unmap(idev);
पूर्ण

अटल bool addr_is_local(स्थिर काष्ठा in6_addr *addr)
अणु
	वापस ipv6_addr_type(addr) &
		(IPV6_ADDR_LINKLOCAL | IPV6_ADDR_LOOPBACK);
पूर्ण

अटल पूर्णांक addrconf_अगरकरोwn(काष्ठा net_device *dev, bool unरेजिस्टर)
अणु
	अचिन्हित दीर्घ event = unरेजिस्टर ? NETDEV_UNREGISTER : NETDEV_DOWN;
	काष्ठा net *net = dev_net(dev);
	काष्ठा inet6_dev *idev;
	काष्ठा inet6_अगरaddr *अगरa, *पंचांगp;
	bool keep_addr = false;
	पूर्णांक state, i;

	ASSERT_RTNL();

	rt6_disable_ip(dev, event);

	idev = __in6_dev_get(dev);
	अगर (!idev)
		वापस -ENODEV;

	/*
	 * Step 1: हटाओ reference to ipv6 device from parent device.
	 *	   Do not dev_put!
	 */
	अगर (unरेजिस्टर) अणु
		idev->dead = 1;

		/* रक्षित by rtnl_lock */
		RCU_INIT_POINTER(dev->ip6_ptr, शून्य);

		/* Step 1.5: हटाओ snmp6 entry */
		snmp6_unरेजिस्टर_dev(idev);

	पूर्ण

	/* combine the user config with event to determine अगर permanent
	 * addresses are to be हटाओd from address hash table
	 */
	अगर (!unरेजिस्टर && !idev->cnf.disable_ipv6) अणु
		/* aggregate the प्रणाली setting and पूर्णांकerface setting */
		पूर्णांक _keep_addr = net->ipv6.devconf_all->keep_addr_on_करोwn;

		अगर (!_keep_addr)
			_keep_addr = idev->cnf.keep_addr_on_करोwn;

		keep_addr = (_keep_addr > 0);
	पूर्ण

	/* Step 2: clear hash table */
	क्रम (i = 0; i < IN6_ADDR_HSIZE; i++) अणु
		काष्ठा hlist_head *h = &inet6_addr_lst[i];

		spin_lock_bh(&addrconf_hash_lock);
restart:
		hlist_क्रम_each_entry_rcu(अगरa, h, addr_lst) अणु
			अगर (अगरa->idev == idev) अणु
				addrconf_del_dad_work(अगरa);
				/* combined flag + permanent flag decide अगर
				 * address is retained on a करोwn event
				 */
				अगर (!keep_addr ||
				    !(अगरa->flags & IFA_F_PERMANENT) ||
				    addr_is_local(&अगरa->addr)) अणु
					hlist_del_init_rcu(&अगरa->addr_lst);
					जाओ restart;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock_bh(&addrconf_hash_lock);
	पूर्ण

	ग_लिखो_lock_bh(&idev->lock);

	addrconf_del_rs_समयr(idev);

	/* Step 2: clear flags क्रम stateless addrconf */
	अगर (!unरेजिस्टर)
		idev->अगर_flags &= ~(IF_RS_SENT|IF_RA_RCVD|IF_READY);

	/* Step 3: clear tempaddr list */
	जबतक (!list_empty(&idev->tempaddr_list)) अणु
		अगरa = list_first_entry(&idev->tempaddr_list,
				       काष्ठा inet6_अगरaddr, पंचांगp_list);
		list_del(&अगरa->पंचांगp_list);
		ग_लिखो_unlock_bh(&idev->lock);
		spin_lock_bh(&अगरa->lock);

		अगर (अगरa->अगरpub) अणु
			in6_अगरa_put(अगरa->अगरpub);
			अगरa->अगरpub = शून्य;
		पूर्ण
		spin_unlock_bh(&अगरa->lock);
		in6_अगरa_put(अगरa);
		ग_लिखो_lock_bh(&idev->lock);
	पूर्ण

	list_क्रम_each_entry_safe(अगरa, पंचांगp, &idev->addr_list, अगर_list) अणु
		काष्ठा fib6_info *rt = शून्य;
		bool keep;

		addrconf_del_dad_work(अगरa);

		keep = keep_addr && (अगरa->flags & IFA_F_PERMANENT) &&
			!addr_is_local(&अगरa->addr);

		ग_लिखो_unlock_bh(&idev->lock);
		spin_lock_bh(&अगरa->lock);

		अगर (keep) अणु
			/* set state to skip the notअगरier below */
			state = INET6_IFADDR_STATE_DEAD;
			अगरa->state = INET6_IFADDR_STATE_PREDAD;
			अगर (!(अगरa->flags & IFA_F_NODAD))
				अगरa->flags |= IFA_F_TENTATIVE;

			rt = अगरa->rt;
			अगरa->rt = शून्य;
		पूर्ण अन्यथा अणु
			state = अगरa->state;
			अगरa->state = INET6_IFADDR_STATE_DEAD;
		पूर्ण

		spin_unlock_bh(&अगरa->lock);

		अगर (rt)
			ip6_del_rt(net, rt, false);

		अगर (state != INET6_IFADDR_STATE_DEAD) अणु
			__ipv6_अगरa_notअगरy(RTM_DELADDR, अगरa);
			inet6addr_notअगरier_call_chain(NETDEV_DOWN, अगरa);
		पूर्ण अन्यथा अणु
			अगर (idev->cnf.क्रमwarding)
				addrconf_leave_anycast(अगरa);
			addrconf_leave_solict(अगरa->idev, &अगरa->addr);
		पूर्ण

		ग_लिखो_lock_bh(&idev->lock);
		अगर (!keep) अणु
			list_del_rcu(&अगरa->अगर_list);
			in6_अगरa_put(अगरa);
		पूर्ण
	पूर्ण

	ग_लिखो_unlock_bh(&idev->lock);

	/* Step 5: Discard anycast and multicast list */
	अगर (unरेजिस्टर) अणु
		ipv6_ac_destroy_dev(idev);
		ipv6_mc_destroy_dev(idev);
	पूर्ण अन्यथा अणु
		ipv6_mc_करोwn(idev);
	पूर्ण

	idev->tstamp = jअगरfies;

	/* Last: Shot the device (अगर unरेजिस्टरed) */
	अगर (unरेजिस्टर) अणु
		addrconf_sysctl_unरेजिस्टर(idev);
		neigh_parms_release(&nd_tbl, idev->nd_parms);
		neigh_अगरकरोwn(&nd_tbl, dev);
		in6_dev_put(idev);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम addrconf_rs_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा inet6_dev *idev = from_समयr(idev, t, rs_समयr);
	काष्ठा net_device *dev = idev->dev;
	काष्ठा in6_addr lladdr;

	ग_लिखो_lock(&idev->lock);
	अगर (idev->dead || !(idev->अगर_flags & IF_READY))
		जाओ out;

	अगर (!ipv6_accept_ra(idev))
		जाओ out;

	/* Announcement received after solicitation was sent */
	अगर (idev->अगर_flags & IF_RA_RCVD)
		जाओ out;

	अगर (idev->rs_probes++ < idev->cnf.rtr_solicits || idev->cnf.rtr_solicits < 0) अणु
		ग_लिखो_unlock(&idev->lock);
		अगर (!ipv6_get_lladdr(dev, &lladdr, IFA_F_TENTATIVE))
			ndisc_send_rs(dev, &lladdr,
				      &in6addr_linklocal_allrouters);
		अन्यथा
			जाओ put;

		ग_लिखो_lock(&idev->lock);
		idev->rs_पूर्णांकerval = rfc3315_s14_backoff_update(
			idev->rs_पूर्णांकerval, idev->cnf.rtr_solicit_max_पूर्णांकerval);
		/* The रुको after the last probe can be लघुer */
		addrconf_mod_rs_समयr(idev, (idev->rs_probes ==
					     idev->cnf.rtr_solicits) ?
				      idev->cnf.rtr_solicit_delay :
				      idev->rs_पूर्णांकerval);
	पूर्ण अन्यथा अणु
		/*
		 * Note: we करो not support deprecated "all on-link"
		 * assumption any दीर्घer.
		 */
		pr_debug("%s: no IPv6 routers present\n", idev->dev->name);
	पूर्ण

out:
	ग_लिखो_unlock(&idev->lock);
put:
	in6_dev_put(idev);
पूर्ण

/*
 *	Duplicate Address Detection
 */
अटल व्योम addrconf_dad_kick(काष्ठा inet6_अगरaddr *अगरp)
अणु
	अचिन्हित दीर्घ अक्रम_num;
	काष्ठा inet6_dev *idev = अगरp->idev;
	u64 nonce;

	अगर (अगरp->flags & IFA_F_OPTIMISTIC)
		अक्रम_num = 0;
	अन्यथा
		अक्रम_num = pअक्रमom_u32() % (idev->cnf.rtr_solicit_delay ? : 1);

	nonce = 0;
	अगर (idev->cnf.enhanced_dad ||
	    dev_net(idev->dev)->ipv6.devconf_all->enhanced_dad) अणु
		करो
			get_अक्रमom_bytes(&nonce, 6);
		जबतक (nonce == 0);
	पूर्ण
	अगरp->dad_nonce = nonce;
	अगरp->dad_probes = idev->cnf.dad_transmits;
	addrconf_mod_dad_work(अगरp, अक्रम_num);
पूर्ण

अटल व्योम addrconf_dad_begin(काष्ठा inet6_अगरaddr *अगरp)
अणु
	काष्ठा inet6_dev *idev = अगरp->idev;
	काष्ठा net_device *dev = idev->dev;
	bool bump_id, notअगरy = false;
	काष्ठा net *net;

	addrconf_join_solict(dev, &अगरp->addr);

	pअक्रमom_seed((__क्रमce u32) अगरp->addr.s6_addr32[3]);

	पढ़ो_lock_bh(&idev->lock);
	spin_lock(&अगरp->lock);
	अगर (अगरp->state == INET6_IFADDR_STATE_DEAD)
		जाओ out;

	net = dev_net(dev);
	अगर (dev->flags&(IFF_NOARP|IFF_LOOPBACK) ||
	    (net->ipv6.devconf_all->accept_dad < 1 &&
	     idev->cnf.accept_dad < 1) ||
	    !(अगरp->flags&IFA_F_TENTATIVE) ||
	    अगरp->flags & IFA_F_NODAD) अणु
		bool send_na = false;

		अगर (अगरp->flags & IFA_F_TENTATIVE &&
		    !(अगरp->flags & IFA_F_OPTIMISTIC))
			send_na = true;
		bump_id = अगरp->flags & IFA_F_TENTATIVE;
		अगरp->flags &= ~(IFA_F_TENTATIVE|IFA_F_OPTIMISTIC|IFA_F_DADFAILED);
		spin_unlock(&अगरp->lock);
		पढ़ो_unlock_bh(&idev->lock);

		addrconf_dad_completed(अगरp, bump_id, send_na);
		वापस;
	पूर्ण

	अगर (!(idev->अगर_flags & IF_READY)) अणु
		spin_unlock(&अगरp->lock);
		पढ़ो_unlock_bh(&idev->lock);
		/*
		 * If the device is not पढ़ोy:
		 * - keep it tentative अगर it is a permanent address.
		 * - otherwise, समाप्त it.
		 */
		in6_अगरa_hold(अगरp);
		addrconf_dad_stop(अगरp, 0);
		वापस;
	पूर्ण

	/*
	 * Optimistic nodes can start receiving
	 * Frames right away
	 */
	अगर (अगरp->flags & IFA_F_OPTIMISTIC) अणु
		ip6_ins_rt(net, अगरp->rt);
		अगर (ipv6_use_optimistic_addr(net, idev)) अणु
			/* Because optimistic nodes can use this address,
			 * notअगरy listeners. If DAD fails, RTM_DELADDR is sent.
			 */
			notअगरy = true;
		पूर्ण
	पूर्ण

	addrconf_dad_kick(अगरp);
out:
	spin_unlock(&अगरp->lock);
	पढ़ो_unlock_bh(&idev->lock);
	अगर (notअगरy)
		ipv6_अगरa_notअगरy(RTM_NEWADDR, अगरp);
पूर्ण

अटल व्योम addrconf_dad_start(काष्ठा inet6_अगरaddr *अगरp)
अणु
	bool begin_dad = false;

	spin_lock_bh(&अगरp->lock);
	अगर (अगरp->state != INET6_IFADDR_STATE_DEAD) अणु
		अगरp->state = INET6_IFADDR_STATE_PREDAD;
		begin_dad = true;
	पूर्ण
	spin_unlock_bh(&अगरp->lock);

	अगर (begin_dad)
		addrconf_mod_dad_work(अगरp, 0);
पूर्ण

अटल व्योम addrconf_dad_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा inet6_अगरaddr *अगरp = container_of(to_delayed_work(w),
						काष्ठा inet6_अगरaddr,
						dad_work);
	काष्ठा inet6_dev *idev = अगरp->idev;
	bool bump_id, disable_ipv6 = false;
	काष्ठा in6_addr mcaddr;

	क्रमागत अणु
		DAD_PROCESS,
		DAD_BEGIN,
		DAD_ABORT,
	पूर्ण action = DAD_PROCESS;

	rtnl_lock();

	spin_lock_bh(&अगरp->lock);
	अगर (अगरp->state == INET6_IFADDR_STATE_PREDAD) अणु
		action = DAD_BEGIN;
		अगरp->state = INET6_IFADDR_STATE_DAD;
	पूर्ण अन्यथा अगर (अगरp->state == INET6_IFADDR_STATE_ERRDAD) अणु
		action = DAD_ABORT;
		अगरp->state = INET6_IFADDR_STATE_POSTDAD;

		अगर ((dev_net(idev->dev)->ipv6.devconf_all->accept_dad > 1 ||
		     idev->cnf.accept_dad > 1) &&
		    !idev->cnf.disable_ipv6 &&
		    !(अगरp->flags & IFA_F_STABLE_PRIVACY)) अणु
			काष्ठा in6_addr addr;

			addr.s6_addr32[0] = htonl(0xfe800000);
			addr.s6_addr32[1] = 0;

			अगर (!ipv6_generate_eui64(addr.s6_addr + 8, idev->dev) &&
			    ipv6_addr_equal(&अगरp->addr, &addr)) अणु
				/* DAD failed क्रम link-local based on MAC */
				idev->cnf.disable_ipv6 = 1;

				pr_info("%s: IPv6 being disabled!\n",
					अगरp->idev->dev->name);
				disable_ipv6 = true;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&अगरp->lock);

	अगर (action == DAD_BEGIN) अणु
		addrconf_dad_begin(अगरp);
		जाओ out;
	पूर्ण अन्यथा अगर (action == DAD_ABORT) अणु
		in6_अगरa_hold(अगरp);
		addrconf_dad_stop(अगरp, 1);
		अगर (disable_ipv6)
			addrconf_अगरकरोwn(idev->dev, false);
		जाओ out;
	पूर्ण

	अगर (!अगरp->dad_probes && addrconf_dad_end(अगरp))
		जाओ out;

	ग_लिखो_lock_bh(&idev->lock);
	अगर (idev->dead || !(idev->अगर_flags & IF_READY)) अणु
		ग_लिखो_unlock_bh(&idev->lock);
		जाओ out;
	पूर्ण

	spin_lock(&अगरp->lock);
	अगर (अगरp->state == INET6_IFADDR_STATE_DEAD) अणु
		spin_unlock(&अगरp->lock);
		ग_लिखो_unlock_bh(&idev->lock);
		जाओ out;
	पूर्ण

	अगर (अगरp->dad_probes == 0) अणु
		bool send_na = false;

		/*
		 * DAD was successful
		 */

		अगर (अगरp->flags & IFA_F_TENTATIVE &&
		    !(अगरp->flags & IFA_F_OPTIMISTIC))
			send_na = true;
		bump_id = अगरp->flags & IFA_F_TENTATIVE;
		अगरp->flags &= ~(IFA_F_TENTATIVE|IFA_F_OPTIMISTIC|IFA_F_DADFAILED);
		spin_unlock(&अगरp->lock);
		ग_लिखो_unlock_bh(&idev->lock);

		addrconf_dad_completed(अगरp, bump_id, send_na);

		जाओ out;
	पूर्ण

	अगरp->dad_probes--;
	addrconf_mod_dad_work(अगरp,
			      max(NEIGH_VAR(अगरp->idev->nd_parms, RETRANS_TIME),
				  HZ/100));
	spin_unlock(&अगरp->lock);
	ग_लिखो_unlock_bh(&idev->lock);

	/* send a neighbour solicitation क्रम our addr */
	addrconf_addr_solict_mult(&अगरp->addr, &mcaddr);
	ndisc_send_ns(अगरp->idev->dev, &अगरp->addr, &mcaddr, &in6addr_any,
		      अगरp->dad_nonce);
out:
	in6_अगरa_put(अगरp);
	rtnl_unlock();
पूर्ण

/* अगरp->idev must be at least पढ़ो locked */
अटल bool ipv6_lonely_lladdr(काष्ठा inet6_अगरaddr *अगरp)
अणु
	काष्ठा inet6_अगरaddr *अगरpiter;
	काष्ठा inet6_dev *idev = अगरp->idev;

	list_क्रम_each_entry_reverse(अगरpiter, &idev->addr_list, अगर_list) अणु
		अगर (अगरpiter->scope > IFA_LINK)
			अवरोध;
		अगर (अगरp != अगरpiter && अगरpiter->scope == IFA_LINK &&
		    (अगरpiter->flags & (IFA_F_PERMANENT|IFA_F_TENTATIVE|
				       IFA_F_OPTIMISTIC|IFA_F_DADFAILED)) ==
		    IFA_F_PERMANENT)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम addrconf_dad_completed(काष्ठा inet6_अगरaddr *अगरp, bool bump_id,
				   bool send_na)
अणु
	काष्ठा net_device *dev = अगरp->idev->dev;
	काष्ठा in6_addr lladdr;
	bool send_rs, send_mld;

	addrconf_del_dad_work(अगरp);

	/*
	 *	Configure the address क्रम reception. Now it is valid.
	 */

	ipv6_अगरa_notअगरy(RTM_NEWADDR, अगरp);

	/* If added prefix is link local and we are prepared to process
	   router advertisements, start sending router solicitations.
	 */

	पढ़ो_lock_bh(&अगरp->idev->lock);
	send_mld = अगरp->scope == IFA_LINK && ipv6_lonely_lladdr(अगरp);
	send_rs = send_mld &&
		  ipv6_accept_ra(अगरp->idev) &&
		  अगरp->idev->cnf.rtr_solicits != 0 &&
		  (dev->flags&IFF_LOOPBACK) == 0;
	पढ़ो_unlock_bh(&अगरp->idev->lock);

	/* While dad is in progress mld report's source address is in6_addrany.
	 * Resend with proper ll now.
	 */
	अगर (send_mld)
		ipv6_mc_dad_complete(अगरp->idev);

	/* send unsolicited NA अगर enabled */
	अगर (send_na &&
	    (अगरp->idev->cnf.ndisc_notअगरy ||
	     dev_net(dev)->ipv6.devconf_all->ndisc_notअगरy)) अणु
		ndisc_send_na(dev, &in6addr_linklocal_allnodes, &अगरp->addr,
			      /*router=*/ !!अगरp->idev->cnf.क्रमwarding,
			      /*solicited=*/ false, /*override=*/ true,
			      /*inc_opt=*/ true);
	पूर्ण

	अगर (send_rs) अणु
		/*
		 *	If a host as alपढ़ोy perक्रमmed a अक्रमom delay
		 *	[...] as part of DAD [...] there is no need
		 *	to delay again beक्रमe sending the first RS
		 */
		अगर (ipv6_get_lladdr(dev, &lladdr, IFA_F_TENTATIVE))
			वापस;
		ndisc_send_rs(dev, &lladdr, &in6addr_linklocal_allrouters);

		ग_लिखो_lock_bh(&अगरp->idev->lock);
		spin_lock(&अगरp->lock);
		अगरp->idev->rs_पूर्णांकerval = rfc3315_s14_backoff_init(
			अगरp->idev->cnf.rtr_solicit_पूर्णांकerval);
		अगरp->idev->rs_probes = 1;
		अगरp->idev->अगर_flags |= IF_RS_SENT;
		addrconf_mod_rs_समयr(अगरp->idev, अगरp->idev->rs_पूर्णांकerval);
		spin_unlock(&अगरp->lock);
		ग_लिखो_unlock_bh(&अगरp->idev->lock);
	पूर्ण

	अगर (bump_id)
		rt_genid_bump_ipv6(dev_net(dev));

	/* Make sure that a new temporary address will be created
	 * beक्रमe this temporary address becomes deprecated.
	 */
	अगर (अगरp->flags & IFA_F_TEMPORARY)
		addrconf_verअगरy_rtnl();
पूर्ण

अटल व्योम addrconf_dad_run(काष्ठा inet6_dev *idev, bool restart)
अणु
	काष्ठा inet6_अगरaddr *अगरp;

	पढ़ो_lock_bh(&idev->lock);
	list_क्रम_each_entry(अगरp, &idev->addr_list, अगर_list) अणु
		spin_lock(&अगरp->lock);
		अगर ((अगरp->flags & IFA_F_TENTATIVE &&
		     अगरp->state == INET6_IFADDR_STATE_DAD) || restart) अणु
			अगर (restart)
				अगरp->state = INET6_IFADDR_STATE_PREDAD;
			addrconf_dad_kick(अगरp);
		पूर्ण
		spin_unlock(&अगरp->lock);
	पूर्ण
	पढ़ो_unlock_bh(&idev->lock);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
काष्ठा अगर6_iter_state अणु
	काष्ठा seq_net_निजी p;
	पूर्णांक bucket;
	पूर्णांक offset;
पूर्ण;

अटल काष्ठा inet6_अगरaddr *अगर6_get_first(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा अगर6_iter_state *state = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा inet6_अगरaddr *अगरa = शून्य;
	पूर्णांक p = 0;

	/* initial bucket अगर pos is 0 */
	अगर (pos == 0) अणु
		state->bucket = 0;
		state->offset = 0;
	पूर्ण

	क्रम (; state->bucket < IN6_ADDR_HSIZE; ++state->bucket) अणु
		hlist_क्रम_each_entry_rcu(अगरa, &inet6_addr_lst[state->bucket],
					 addr_lst) अणु
			अगर (!net_eq(dev_net(अगरa->idev->dev), net))
				जारी;
			/* sync with offset */
			अगर (p < state->offset) अणु
				p++;
				जारी;
			पूर्ण
			वापस अगरa;
		पूर्ण

		/* prepare क्रम next bucket */
		state->offset = 0;
		p = 0;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा inet6_अगरaddr *अगर6_get_next(काष्ठा seq_file *seq,
					 काष्ठा inet6_अगरaddr *अगरa)
अणु
	काष्ठा अगर6_iter_state *state = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);

	hlist_क्रम_each_entry_जारी_rcu(अगरa, addr_lst) अणु
		अगर (!net_eq(dev_net(अगरa->idev->dev), net))
			जारी;
		state->offset++;
		वापस अगरa;
	पूर्ण

	state->offset = 0;
	जबतक (++state->bucket < IN6_ADDR_HSIZE) अणु
		hlist_क्रम_each_entry_rcu(अगरa,
				     &inet6_addr_lst[state->bucket], addr_lst) अणु
			अगर (!net_eq(dev_net(अगरa->idev->dev), net))
				जारी;
			वापस अगरa;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *अगर6_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(rcu)
अणु
	rcu_पढ़ो_lock();
	वापस अगर6_get_first(seq, *pos);
पूर्ण

अटल व्योम *अगर6_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा inet6_अगरaddr *अगरa;

	अगरa = अगर6_get_next(seq, v);
	++*pos;
	वापस अगरa;
पूर्ण

अटल व्योम अगर6_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(rcu)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक अगर6_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा inet6_अगरaddr *अगरp = (काष्ठा inet6_अगरaddr *)v;
	seq_म_लिखो(seq, "%pi6 %02x %02x %02x %02x %8s\n",
		   &अगरp->addr,
		   अगरp->idev->dev->अगरindex,
		   अगरp->prefix_len,
		   अगरp->scope,
		   (u8) अगरp->flags,
		   अगरp->idev->dev->name);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations अगर6_seq_ops = अणु
	.start	= अगर6_seq_start,
	.next	= अगर6_seq_next,
	.show	= अगर6_seq_show,
	.stop	= अगर6_seq_stop,
पूर्ण;

अटल पूर्णांक __net_init अगर6_proc_net_init(काष्ठा net *net)
अणु
	अगर (!proc_create_net("if_inet6", 0444, net->proc_net, &अगर6_seq_ops,
			माप(काष्ठा अगर6_iter_state)))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास अगर6_proc_net_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("if_inet6", net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations अगर6_proc_net_ops = अणु
	.init = अगर6_proc_net_init,
	.निकास = अगर6_proc_net_निकास,
पूर्ण;

पूर्णांक __init अगर6_proc_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&अगर6_proc_net_ops);
पूर्ण

व्योम अगर6_proc_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&अगर6_proc_net_ops);
पूर्ण
#पूर्ण_अगर	/* CONFIG_PROC_FS */

#अगर IS_ENABLED(CONFIG_IPV6_MIP6)
/* Check अगर address is a home address configured on any पूर्णांकerface. */
पूर्णांक ipv6_chk_home_addr(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr)
अणु
	अचिन्हित पूर्णांक hash = inet6_addr_hash(net, addr);
	काष्ठा inet6_अगरaddr *अगरp = शून्य;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(अगरp, &inet6_addr_lst[hash], addr_lst) अणु
		अगर (!net_eq(dev_net(अगरp->idev->dev), net))
			जारी;
		अगर (ipv6_addr_equal(&अगरp->addr, addr) &&
		    (अगरp->flags & IFA_F_HOMEADDRESS)) अणु
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
#पूर्ण_अगर

/* RFC6554 has some algorithm to aव्योम loops in segment routing by
 * checking अगर the segments contains any of a local पूर्णांकerface address.
 *
 * Quote:
 *
 * To detect loops in the SRH, a router MUST determine अगर the SRH
 * includes multiple addresses asचिन्हित to any पूर्णांकerface on that router.
 * If such addresses appear more than once and are separated by at least
 * one address not asचिन्हित to that router.
 */
पूर्णांक ipv6_chk_rpl_srh_loop(काष्ठा net *net, स्थिर काष्ठा in6_addr *segs,
			  अचिन्हित अक्षर nsegs)
अणु
	स्थिर काष्ठा in6_addr *addr;
	पूर्णांक i, ret = 0, found = 0;
	काष्ठा inet6_अगरaddr *अगरp;
	bool separated = false;
	अचिन्हित पूर्णांक hash;
	bool hash_found;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < nsegs; i++) अणु
		addr = &segs[i];
		hash = inet6_addr_hash(net, addr);

		hash_found = false;
		hlist_क्रम_each_entry_rcu(अगरp, &inet6_addr_lst[hash], addr_lst) अणु
			अगर (!net_eq(dev_net(अगरp->idev->dev), net))
				जारी;

			अगर (ipv6_addr_equal(&अगरp->addr, addr)) अणु
				hash_found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (hash_found) अणु
			अगर (found > 1 && separated) अणु
				ret = 1;
				अवरोध;
			पूर्ण

			separated = false;
			found++;
		पूर्ण अन्यथा अणु
			separated = true;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/*
 *	Periodic address status verअगरication
 */

अटल व्योम addrconf_verअगरy_rtnl(व्योम)
अणु
	अचिन्हित दीर्घ now, next, next_sec, next_sched;
	काष्ठा inet6_अगरaddr *अगरp;
	पूर्णांक i;

	ASSERT_RTNL();

	rcu_पढ़ो_lock_bh();
	now = jअगरfies;
	next = round_jअगरfies_up(now + ADDR_CHECK_FREQUENCY);

	cancel_delayed_work(&addr_chk_work);

	क्रम (i = 0; i < IN6_ADDR_HSIZE; i++) अणु
restart:
		hlist_क्रम_each_entry_rcu_bh(अगरp, &inet6_addr_lst[i], addr_lst) अणु
			अचिन्हित दीर्घ age;

			/* When setting preferred_lft to a value not zero or
			 * infinity, जबतक valid_lft is infinity
			 * IFA_F_PERMANENT has a non-infinity lअगरe समय.
			 */
			अगर ((अगरp->flags & IFA_F_PERMANENT) &&
			    (अगरp->prefered_lft == अनन्त_LIFE_TIME))
				जारी;

			spin_lock(&अगरp->lock);
			/* We try to batch several events at once. */
			age = (now - अगरp->tstamp + ADDRCONF_TIMER_FUZZ_MINUS) / HZ;

			अगर (अगरp->valid_lft != अनन्त_LIFE_TIME &&
			    age >= अगरp->valid_lft) अणु
				spin_unlock(&अगरp->lock);
				in6_अगरa_hold(अगरp);
				rcu_पढ़ो_unlock_bh();
				ipv6_del_addr(अगरp);
				rcu_पढ़ो_lock_bh();
				जाओ restart;
			पूर्ण अन्यथा अगर (अगरp->prefered_lft == अनन्त_LIFE_TIME) अणु
				spin_unlock(&अगरp->lock);
				जारी;
			पूर्ण अन्यथा अगर (age >= अगरp->prefered_lft) अणु
				/* jअगरfies - अगरp->tstamp > age >= अगरp->prefered_lft */
				पूर्णांक deprecate = 0;

				अगर (!(अगरp->flags&IFA_F_DEPRECATED)) अणु
					deprecate = 1;
					अगरp->flags |= IFA_F_DEPRECATED;
				पूर्ण

				अगर ((अगरp->valid_lft != अनन्त_LIFE_TIME) &&
				    (समय_beक्रमe(अगरp->tstamp + अगरp->valid_lft * HZ, next)))
					next = अगरp->tstamp + अगरp->valid_lft * HZ;

				spin_unlock(&अगरp->lock);

				अगर (deprecate) अणु
					in6_अगरa_hold(अगरp);

					ipv6_अगरa_notअगरy(0, अगरp);
					in6_अगरa_put(अगरp);
					जाओ restart;
				पूर्ण
			पूर्ण अन्यथा अगर ((अगरp->flags&IFA_F_TEMPORARY) &&
				   !(अगरp->flags&IFA_F_TENTATIVE)) अणु
				अचिन्हित दीर्घ regen_advance = अगरp->idev->cnf.regen_max_retry *
					अगरp->idev->cnf.dad_transmits *
					max(NEIGH_VAR(अगरp->idev->nd_parms, RETRANS_TIME), HZ/100) / HZ;

				अगर (age >= अगरp->prefered_lft - regen_advance) अणु
					काष्ठा inet6_अगरaddr *अगरpub = अगरp->अगरpub;
					अगर (समय_beक्रमe(अगरp->tstamp + अगरp->prefered_lft * HZ, next))
						next = अगरp->tstamp + अगरp->prefered_lft * HZ;
					अगर (!अगरp->regen_count && अगरpub) अणु
						अगरp->regen_count++;
						in6_अगरa_hold(अगरp);
						in6_अगरa_hold(अगरpub);
						spin_unlock(&अगरp->lock);

						spin_lock(&अगरpub->lock);
						अगरpub->regen_count = 0;
						spin_unlock(&अगरpub->lock);
						rcu_पढ़ो_unlock_bh();
						ipv6_create_tempaddr(अगरpub, true);
						in6_अगरa_put(अगरpub);
						in6_अगरa_put(अगरp);
						rcu_पढ़ो_lock_bh();
						जाओ restart;
					पूर्ण
				पूर्ण अन्यथा अगर (समय_beक्रमe(अगरp->tstamp + अगरp->prefered_lft * HZ - regen_advance * HZ, next))
					next = अगरp->tstamp + अगरp->prefered_lft * HZ - regen_advance * HZ;
				spin_unlock(&अगरp->lock);
			पूर्ण अन्यथा अणु
				/* अगरp->prefered_lft <= अगरp->valid_lft */
				अगर (समय_beक्रमe(अगरp->tstamp + अगरp->prefered_lft * HZ, next))
					next = अगरp->tstamp + अगरp->prefered_lft * HZ;
				spin_unlock(&अगरp->lock);
			पूर्ण
		पूर्ण
	पूर्ण

	next_sec = round_jअगरfies_up(next);
	next_sched = next;

	/* If rounded समयout is accurate enough, accept it. */
	अगर (समय_beक्रमe(next_sec, next + ADDRCONF_TIMER_FUZZ))
		next_sched = next_sec;

	/* And minimum पूर्णांकerval is ADDRCONF_TIMER_FUZZ_MAX. */
	अगर (समय_beक्रमe(next_sched, jअगरfies + ADDRCONF_TIMER_FUZZ_MAX))
		next_sched = jअगरfies + ADDRCONF_TIMER_FUZZ_MAX;

	pr_debug("now = %lu, schedule = %lu, rounded schedule = %lu => %lu\n",
		 now, next, next_sec, next_sched);
	mod_delayed_work(addrconf_wq, &addr_chk_work, next_sched - now);
	rcu_पढ़ो_unlock_bh();
पूर्ण

अटल व्योम addrconf_verअगरy_work(काष्ठा work_काष्ठा *w)
अणु
	rtnl_lock();
	addrconf_verअगरy_rtnl();
	rtnl_unlock();
पूर्ण

अटल व्योम addrconf_verअगरy(व्योम)
अणु
	mod_delayed_work(addrconf_wq, &addr_chk_work, 0);
पूर्ण

अटल काष्ठा in6_addr *extract_addr(काष्ठा nlattr *addr, काष्ठा nlattr *local,
				     काष्ठा in6_addr **peer_pfx)
अणु
	काष्ठा in6_addr *pfx = शून्य;

	*peer_pfx = शून्य;

	अगर (addr)
		pfx = nla_data(addr);

	अगर (local) अणु
		अगर (pfx && nla_स_भेद(local, pfx, माप(*pfx)))
			*peer_pfx = pfx;
		pfx = nla_data(local);
	पूर्ण

	वापस pfx;
पूर्ण

अटल स्थिर काष्ठा nla_policy अगरa_ipv6_policy[IFA_MAX+1] = अणु
	[IFA_ADDRESS]		= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IFA_LOCAL]		= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IFA_CACHEINFO]		= अणु .len = माप(काष्ठा अगरa_cacheinfo) पूर्ण,
	[IFA_FLAGS]		= अणु .len = माप(u32) पूर्ण,
	[IFA_RT_PRIORITY]	= अणु .len = माप(u32) पूर्ण,
	[IFA_TARGET_NETNSID]	= अणु .type = NLA_S32 पूर्ण,
पूर्ण;

अटल पूर्णांक
inet6_rपंचांग_deladdr(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा अगरaddrmsg *अगरm;
	काष्ठा nlattr *tb[IFA_MAX+1];
	काष्ठा in6_addr *pfx, *peer_pfx;
	u32 अगरa_flags;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFA_MAX,
				     अगरa_ipv6_policy, extack);
	अगर (err < 0)
		वापस err;

	अगरm = nlmsg_data(nlh);
	pfx = extract_addr(tb[IFA_ADDRESS], tb[IFA_LOCAL], &peer_pfx);
	अगर (!pfx)
		वापस -EINVAL;

	अगरa_flags = tb[IFA_FLAGS] ? nla_get_u32(tb[IFA_FLAGS]) : अगरm->अगरa_flags;

	/* We ignore other flags so far. */
	अगरa_flags &= IFA_F_MANAGETEMPADDR;

	वापस inet6_addr_del(net, अगरm->अगरa_index, अगरa_flags, pfx,
			      अगरm->अगरa_prefixlen);
पूर्ण

अटल पूर्णांक modअगरy_prefix_route(काष्ठा inet6_अगरaddr *अगरp,
			       अचिन्हित दीर्घ expires, u32 flags,
			       bool modअगरy_peer)
अणु
	काष्ठा fib6_info *f6i;
	u32 prio;

	f6i = addrconf_get_prefix_route(modअगरy_peer ? &अगरp->peer_addr : &अगरp->addr,
					अगरp->prefix_len,
					अगरp->idev->dev, 0, RTF_DEFAULT, true);
	अगर (!f6i)
		वापस -ENOENT;

	prio = अगरp->rt_priority ? : IP6_RT_PRIO_ADDRCONF;
	अगर (f6i->fib6_metric != prio) अणु
		/* delete old one */
		ip6_del_rt(dev_net(अगरp->idev->dev), f6i, false);

		/* add new one */
		addrconf_prefix_route(modअगरy_peer ? &अगरp->peer_addr : &अगरp->addr,
				      अगरp->prefix_len,
				      अगरp->rt_priority, अगरp->idev->dev,
				      expires, flags, GFP_KERNEL);
	पूर्ण अन्यथा अणु
		अगर (!expires)
			fib6_clean_expires(f6i);
		अन्यथा
			fib6_set_expires(f6i, expires);

		fib6_info_release(f6i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet6_addr_modअगरy(काष्ठा inet6_अगरaddr *अगरp, काष्ठा अगरa6_config *cfg)
अणु
	u32 flags;
	घड़ी_प्रकार expires;
	अचिन्हित दीर्घ समयout;
	bool was_managetempaddr;
	bool had_prefixroute;
	bool new_peer = false;

	ASSERT_RTNL();

	अगर (!cfg->valid_lft || cfg->preferred_lft > cfg->valid_lft)
		वापस -EINVAL;

	अगर (cfg->अगरa_flags & IFA_F_MANAGETEMPADDR &&
	    (अगरp->flags & IFA_F_TEMPORARY || अगरp->prefix_len != 64))
		वापस -EINVAL;

	अगर (!(अगरp->flags & IFA_F_TENTATIVE) || अगरp->flags & IFA_F_DADFAILED)
		cfg->अगरa_flags &= ~IFA_F_OPTIMISTIC;

	समयout = addrconf_समयout_fixup(cfg->valid_lft, HZ);
	अगर (addrconf_finite_समयout(समयout)) अणु
		expires = jअगरfies_to_घड़ी_प्रकार(समयout * HZ);
		cfg->valid_lft = समयout;
		flags = RTF_EXPIRES;
	पूर्ण अन्यथा अणु
		expires = 0;
		flags = 0;
		cfg->अगरa_flags |= IFA_F_PERMANENT;
	पूर्ण

	समयout = addrconf_समयout_fixup(cfg->preferred_lft, HZ);
	अगर (addrconf_finite_समयout(समयout)) अणु
		अगर (समयout == 0)
			cfg->अगरa_flags |= IFA_F_DEPRECATED;
		cfg->preferred_lft = समयout;
	पूर्ण

	अगर (cfg->peer_pfx &&
	    स_भेद(&अगरp->peer_addr, cfg->peer_pfx, माप(काष्ठा in6_addr))) अणु
		अगर (!ipv6_addr_any(&अगरp->peer_addr))
			cleanup_prefix_route(अगरp, expires, true, true);
		new_peer = true;
	पूर्ण

	spin_lock_bh(&अगरp->lock);
	was_managetempaddr = अगरp->flags & IFA_F_MANAGETEMPADDR;
	had_prefixroute = अगरp->flags & IFA_F_PERMANENT &&
			  !(अगरp->flags & IFA_F_NOPREFIXROUTE);
	अगरp->flags &= ~(IFA_F_DEPRECATED | IFA_F_PERMANENT | IFA_F_NODAD |
			IFA_F_HOMEADDRESS | IFA_F_MANAGETEMPADDR |
			IFA_F_NOPREFIXROUTE);
	अगरp->flags |= cfg->अगरa_flags;
	अगरp->tstamp = jअगरfies;
	अगरp->valid_lft = cfg->valid_lft;
	अगरp->prefered_lft = cfg->preferred_lft;

	अगर (cfg->rt_priority && cfg->rt_priority != अगरp->rt_priority)
		अगरp->rt_priority = cfg->rt_priority;

	अगर (new_peer)
		अगरp->peer_addr = *cfg->peer_pfx;

	spin_unlock_bh(&अगरp->lock);
	अगर (!(अगरp->flags&IFA_F_TENTATIVE))
		ipv6_अगरa_notअगरy(0, अगरp);

	अगर (!(cfg->अगरa_flags & IFA_F_NOPREFIXROUTE)) अणु
		पूर्णांक rc = -ENOENT;

		अगर (had_prefixroute)
			rc = modअगरy_prefix_route(अगरp, expires, flags, false);

		/* prefix route could have been deleted; अगर so restore it */
		अगर (rc == -ENOENT) अणु
			addrconf_prefix_route(&अगरp->addr, अगरp->prefix_len,
					      अगरp->rt_priority, अगरp->idev->dev,
					      expires, flags, GFP_KERNEL);
		पूर्ण

		अगर (had_prefixroute && !ipv6_addr_any(&अगरp->peer_addr))
			rc = modअगरy_prefix_route(अगरp, expires, flags, true);

		अगर (rc == -ENOENT && !ipv6_addr_any(&अगरp->peer_addr)) अणु
			addrconf_prefix_route(&अगरp->peer_addr, अगरp->prefix_len,
					      अगरp->rt_priority, अगरp->idev->dev,
					      expires, flags, GFP_KERNEL);
		पूर्ण
	पूर्ण अन्यथा अगर (had_prefixroute) अणु
		क्रमागत cleanup_prefix_rt_t action;
		अचिन्हित दीर्घ rt_expires;

		ग_लिखो_lock_bh(&अगरp->idev->lock);
		action = check_cleanup_prefix_route(अगरp, &rt_expires);
		ग_लिखो_unlock_bh(&अगरp->idev->lock);

		अगर (action != CLEANUP_PREFIX_RT_NOP) अणु
			cleanup_prefix_route(अगरp, rt_expires,
				action == CLEANUP_PREFIX_RT_DEL, false);
		पूर्ण
	पूर्ण

	अगर (was_managetempaddr || अगरp->flags & IFA_F_MANAGETEMPADDR) अणु
		अगर (was_managetempaddr &&
		    !(अगरp->flags & IFA_F_MANAGETEMPADDR)) अणु
			cfg->valid_lft = 0;
			cfg->preferred_lft = 0;
		पूर्ण
		manage_tempaddrs(अगरp->idev, अगरp, cfg->valid_lft,
				 cfg->preferred_lft, !was_managetempaddr,
				 jअगरfies);
	पूर्ण

	addrconf_verअगरy_rtnl();

	वापस 0;
पूर्ण

अटल पूर्णांक
inet6_rपंचांग_newaddr(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा अगरaddrmsg *अगरm;
	काष्ठा nlattr *tb[IFA_MAX+1];
	काष्ठा in6_addr *peer_pfx;
	काष्ठा inet6_अगरaddr *अगरa;
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;
	काष्ठा अगरa6_config cfg;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFA_MAX,
				     अगरa_ipv6_policy, extack);
	अगर (err < 0)
		वापस err;

	स_रखो(&cfg, 0, माप(cfg));

	अगरm = nlmsg_data(nlh);
	cfg.pfx = extract_addr(tb[IFA_ADDRESS], tb[IFA_LOCAL], &peer_pfx);
	अगर (!cfg.pfx)
		वापस -EINVAL;

	cfg.peer_pfx = peer_pfx;
	cfg.plen = अगरm->अगरa_prefixlen;
	अगर (tb[IFA_RT_PRIORITY])
		cfg.rt_priority = nla_get_u32(tb[IFA_RT_PRIORITY]);

	cfg.valid_lft = अनन्त_LIFE_TIME;
	cfg.preferred_lft = अनन्त_LIFE_TIME;

	अगर (tb[IFA_CACHEINFO]) अणु
		काष्ठा अगरa_cacheinfo *ci;

		ci = nla_data(tb[IFA_CACHEINFO]);
		cfg.valid_lft = ci->अगरa_valid;
		cfg.preferred_lft = ci->अगरa_prefered;
	पूर्ण

	dev =  __dev_get_by_index(net, अगरm->अगरa_index);
	अगर (!dev)
		वापस -ENODEV;

	अगर (tb[IFA_FLAGS])
		cfg.अगरa_flags = nla_get_u32(tb[IFA_FLAGS]);
	अन्यथा
		cfg.अगरa_flags = अगरm->अगरa_flags;

	/* We ignore other flags so far. */
	cfg.अगरa_flags &= IFA_F_NODAD | IFA_F_HOMEADDRESS |
			 IFA_F_MANAGETEMPADDR | IFA_F_NOPREFIXROUTE |
			 IFA_F_MCAUTOJOIN | IFA_F_OPTIMISTIC;

	idev = ipv6_find_idev(dev);
	अगर (IS_ERR(idev))
		वापस PTR_ERR(idev);

	अगर (!ipv6_allow_optimistic_dad(net, idev))
		cfg.अगरa_flags &= ~IFA_F_OPTIMISTIC;

	अगर (cfg.अगरa_flags & IFA_F_NODAD &&
	    cfg.अगरa_flags & IFA_F_OPTIMISTIC) अणु
		NL_SET_ERR_MSG(extack, "IFA_F_NODAD and IFA_F_OPTIMISTIC are mutually exclusive");
		वापस -EINVAL;
	पूर्ण

	अगरa = ipv6_get_अगरaddr(net, cfg.pfx, dev, 1);
	अगर (!अगरa) अणु
		/*
		 * It would be best to check क्रम !NLM_F_CREATE here but
		 * userspace alपढ़ोy relies on not having to provide this.
		 */
		वापस inet6_addr_add(net, अगरm->अगरa_index, &cfg, extack);
	पूर्ण

	अगर (nlh->nlmsg_flags & NLM_F_EXCL ||
	    !(nlh->nlmsg_flags & NLM_F_REPLACE))
		err = -EEXIST;
	अन्यथा
		err = inet6_addr_modअगरy(अगरa, &cfg);

	in6_अगरa_put(अगरa);

	वापस err;
पूर्ण

अटल व्योम put_अगरaddrmsg(काष्ठा nlmsghdr *nlh, u8 prefixlen, u32 flags,
			  u8 scope, पूर्णांक अगरindex)
अणु
	काष्ठा अगरaddrmsg *अगरm;

	अगरm = nlmsg_data(nlh);
	अगरm->अगरa_family = AF_INET6;
	अगरm->अगरa_prefixlen = prefixlen;
	अगरm->अगरa_flags = flags;
	अगरm->अगरa_scope = scope;
	अगरm->अगरa_index = अगरindex;
पूर्ण

अटल पूर्णांक put_cacheinfo(काष्ठा sk_buff *skb, अचिन्हित दीर्घ cstamp,
			 अचिन्हित दीर्घ tstamp, u32 preferred, u32 valid)
अणु
	काष्ठा अगरa_cacheinfo ci;

	ci.cstamp = cstamp_delta(cstamp);
	ci.tstamp = cstamp_delta(tstamp);
	ci.अगरa_prefered = preferred;
	ci.अगरa_valid = valid;

	वापस nla_put(skb, IFA_CACHEINFO, माप(ci), &ci);
पूर्ण

अटल अंतरभूत पूर्णांक rt_scope(पूर्णांक अगरa_scope)
अणु
	अगर (अगरa_scope & IFA_HOST)
		वापस RT_SCOPE_HOST;
	अन्यथा अगर (अगरa_scope & IFA_LINK)
		वापस RT_SCOPE_LINK;
	अन्यथा अगर (अगरa_scope & IFA_SITE)
		वापस RT_SCOPE_SITE;
	अन्यथा
		वापस RT_SCOPE_UNIVERSE;
पूर्ण

अटल अंतरभूत पूर्णांक inet6_अगरaddr_msgsize(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा अगरaddrmsg))
	       + nla_total_size(16) /* IFA_LOCAL */
	       + nla_total_size(16) /* IFA_ADDRESS */
	       + nla_total_size(माप(काष्ठा अगरa_cacheinfo))
	       + nla_total_size(4)  /* IFA_FLAGS */
	       + nla_total_size(4)  /* IFA_RT_PRIORITY */;
पूर्ण

क्रमागत addr_type_t अणु
	UNICAST_ADDR,
	MULTICAST_ADDR,
	ANYCAST_ADDR,
पूर्ण;

काष्ठा inet6_fill_args अणु
	u32 portid;
	u32 seq;
	पूर्णांक event;
	अचिन्हित पूर्णांक flags;
	पूर्णांक netnsid;
	पूर्णांक अगरindex;
	क्रमागत addr_type_t type;
पूर्ण;

अटल पूर्णांक inet6_fill_अगरaddr(काष्ठा sk_buff *skb, काष्ठा inet6_अगरaddr *अगरa,
			     काष्ठा inet6_fill_args *args)
अणु
	काष्ठा nlmsghdr  *nlh;
	u32 preferred, valid;

	nlh = nlmsg_put(skb, args->portid, args->seq, args->event,
			माप(काष्ठा अगरaddrmsg), args->flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	put_अगरaddrmsg(nlh, अगरa->prefix_len, अगरa->flags, rt_scope(अगरa->scope),
		      अगरa->idev->dev->अगरindex);

	अगर (args->netnsid >= 0 &&
	    nla_put_s32(skb, IFA_TARGET_NETNSID, args->netnsid))
		जाओ error;

	अगर (!((अगरa->flags&IFA_F_PERMANENT) &&
	      (अगरa->prefered_lft == अनन्त_LIFE_TIME))) अणु
		preferred = अगरa->prefered_lft;
		valid = अगरa->valid_lft;
		अगर (preferred != अनन्त_LIFE_TIME) अणु
			दीर्घ tval = (jअगरfies - अगरa->tstamp)/HZ;
			अगर (preferred > tval)
				preferred -= tval;
			अन्यथा
				preferred = 0;
			अगर (valid != अनन्त_LIFE_TIME) अणु
				अगर (valid > tval)
					valid -= tval;
				अन्यथा
					valid = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		preferred = अनन्त_LIFE_TIME;
		valid = अनन्त_LIFE_TIME;
	पूर्ण

	अगर (!ipv6_addr_any(&अगरa->peer_addr)) अणु
		अगर (nla_put_in6_addr(skb, IFA_LOCAL, &अगरa->addr) < 0 ||
		    nla_put_in6_addr(skb, IFA_ADDRESS, &अगरa->peer_addr) < 0)
			जाओ error;
	पूर्ण अन्यथा
		अगर (nla_put_in6_addr(skb, IFA_ADDRESS, &अगरa->addr) < 0)
			जाओ error;

	अगर (अगरa->rt_priority &&
	    nla_put_u32(skb, IFA_RT_PRIORITY, अगरa->rt_priority))
		जाओ error;

	अगर (put_cacheinfo(skb, अगरa->cstamp, अगरa->tstamp, preferred, valid) < 0)
		जाओ error;

	अगर (nla_put_u32(skb, IFA_FLAGS, अगरa->flags) < 0)
		जाओ error;

	nlmsg_end(skb, nlh);
	वापस 0;

error:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक inet6_fill_अगरmcaddr(काष्ठा sk_buff *skb, काष्ठा अगरmcaddr6 *अगरmca,
			       काष्ठा inet6_fill_args *args)
अणु
	काष्ठा nlmsghdr  *nlh;
	u8 scope = RT_SCOPE_UNIVERSE;
	पूर्णांक अगरindex = अगरmca->idev->dev->अगरindex;

	अगर (ipv6_addr_scope(&अगरmca->mca_addr) & IFA_SITE)
		scope = RT_SCOPE_SITE;

	nlh = nlmsg_put(skb, args->portid, args->seq, args->event,
			माप(काष्ठा अगरaddrmsg), args->flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	अगर (args->netnsid >= 0 &&
	    nla_put_s32(skb, IFA_TARGET_NETNSID, args->netnsid)) अणु
		nlmsg_cancel(skb, nlh);
		वापस -EMSGSIZE;
	पूर्ण

	put_अगरaddrmsg(nlh, 128, IFA_F_PERMANENT, scope, अगरindex);
	अगर (nla_put_in6_addr(skb, IFA_MULTICAST, &अगरmca->mca_addr) < 0 ||
	    put_cacheinfo(skb, अगरmca->mca_cstamp, अगरmca->mca_tstamp,
			  अनन्त_LIFE_TIME, अनन्त_LIFE_TIME) < 0) अणु
		nlmsg_cancel(skb, nlh);
		वापस -EMSGSIZE;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक inet6_fill_अगरacaddr(काष्ठा sk_buff *skb, काष्ठा अगरacaddr6 *अगरaca,
			       काष्ठा inet6_fill_args *args)
अणु
	काष्ठा net_device *dev = fib6_info_nh_dev(अगरaca->aca_rt);
	पूर्णांक अगरindex = dev ? dev->अगरindex : 1;
	काष्ठा nlmsghdr  *nlh;
	u8 scope = RT_SCOPE_UNIVERSE;

	अगर (ipv6_addr_scope(&अगरaca->aca_addr) & IFA_SITE)
		scope = RT_SCOPE_SITE;

	nlh = nlmsg_put(skb, args->portid, args->seq, args->event,
			माप(काष्ठा अगरaddrmsg), args->flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	अगर (args->netnsid >= 0 &&
	    nla_put_s32(skb, IFA_TARGET_NETNSID, args->netnsid)) अणु
		nlmsg_cancel(skb, nlh);
		वापस -EMSGSIZE;
	पूर्ण

	put_अगरaddrmsg(nlh, 128, IFA_F_PERMANENT, scope, अगरindex);
	अगर (nla_put_in6_addr(skb, IFA_ANYCAST, &अगरaca->aca_addr) < 0 ||
	    put_cacheinfo(skb, अगरaca->aca_cstamp, अगरaca->aca_tstamp,
			  अनन्त_LIFE_TIME, अनन्त_LIFE_TIME) < 0) अणु
		nlmsg_cancel(skb, nlh);
		वापस -EMSGSIZE;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

/* called with rcu_पढ़ो_lock() */
अटल पूर्णांक in6_dump_addrs(काष्ठा inet6_dev *idev, काष्ठा sk_buff *skb,
			  काष्ठा netlink_callback *cb, पूर्णांक s_ip_idx,
			  काष्ठा inet6_fill_args *fillargs)
अणु
	काष्ठा अगरmcaddr6 *अगरmca;
	काष्ठा अगरacaddr6 *अगरaca;
	पूर्णांक ip_idx = 0;
	पूर्णांक err = 1;

	पढ़ो_lock_bh(&idev->lock);
	चयन (fillargs->type) अणु
	हाल UNICAST_ADDR: अणु
		काष्ठा inet6_अगरaddr *अगरa;
		fillargs->event = RTM_NEWADDR;

		/* unicast address incl. temp addr */
		list_क्रम_each_entry(अगरa, &idev->addr_list, अगर_list) अणु
			अगर (ip_idx < s_ip_idx)
				जाओ next;
			err = inet6_fill_अगरaddr(skb, अगरa, fillargs);
			अगर (err < 0)
				अवरोध;
			nl_dump_check_consistent(cb, nlmsg_hdr(skb));
next:
			ip_idx++;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल MULTICAST_ADDR:
		पढ़ो_unlock_bh(&idev->lock);
		fillargs->event = RTM_GETMULTICAST;

		/* multicast address */
		क्रम (अगरmca = rcu_dereference(idev->mc_list);
		     अगरmca;
		     अगरmca = rcu_dereference(अगरmca->next), ip_idx++) अणु
			अगर (ip_idx < s_ip_idx)
				जारी;
			err = inet6_fill_अगरmcaddr(skb, अगरmca, fillargs);
			अगर (err < 0)
				अवरोध;
		पूर्ण
		पढ़ो_lock_bh(&idev->lock);
		अवरोध;
	हाल ANYCAST_ADDR:
		fillargs->event = RTM_GETANYCAST;
		/* anycast address */
		क्रम (अगरaca = idev->ac_list; अगरaca;
		     अगरaca = अगरaca->aca_next, ip_idx++) अणु
			अगर (ip_idx < s_ip_idx)
				जारी;
			err = inet6_fill_अगरacaddr(skb, अगरaca, fillargs);
			अगर (err < 0)
				अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	पढ़ो_unlock_bh(&idev->lock);
	cb->args[2] = ip_idx;
	वापस err;
पूर्ण

अटल पूर्णांक inet6_valid_dump_अगरaddr_req(स्थिर काष्ठा nlmsghdr *nlh,
				       काष्ठा inet6_fill_args *fillargs,
				       काष्ठा net **tgt_net, काष्ठा sock *sk,
				       काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlink_ext_ack *extack = cb->extack;
	काष्ठा nlattr *tb[IFA_MAX+1];
	काष्ठा अगरaddrmsg *अगरm;
	पूर्णांक err, i;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरm))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid header for address dump request");
		वापस -EINVAL;
	पूर्ण

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरa_prefixlen || अगरm->अगरa_flags || अगरm->अगरa_scope) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid values in header for address dump request");
		वापस -EINVAL;
	पूर्ण

	fillargs->अगरindex = अगरm->अगरa_index;
	अगर (fillargs->अगरindex) अणु
		cb->answer_flags |= NLM_F_DUMP_FILTERED;
		fillargs->flags |= NLM_F_DUMP_FILTERED;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(*अगरm), tb, IFA_MAX,
					    अगरa_ipv6_policy, extack);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i <= IFA_MAX; ++i) अणु
		अगर (!tb[i])
			जारी;

		अगर (i == IFA_TARGET_NETNSID) अणु
			काष्ठा net *net;

			fillargs->netnsid = nla_get_s32(tb[i]);
			net = rtnl_get_net_ns_capable(sk, fillargs->netnsid);
			अगर (IS_ERR(net)) अणु
				fillargs->netnsid = -1;
				NL_SET_ERR_MSG_MOD(extack, "Invalid target network namespace id");
				वापस PTR_ERR(net);
			पूर्ण
			*tgt_net = net;
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG_MOD(extack, "Unsupported attribute in dump request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet6_dump_addr(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
			   क्रमागत addr_type_t type)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा inet6_fill_args fillargs = अणु
		.portid = NETLINK_CB(cb->skb).portid,
		.seq = cb->nlh->nlmsg_seq,
		.flags = NLM_F_MULTI,
		.netnsid = -1,
		.type = type,
	पूर्ण;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net *tgt_net = net;
	पूर्णांक idx, s_idx, s_ip_idx;
	पूर्णांक h, s_h;
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;
	काष्ठा hlist_head *head;
	पूर्णांक err = 0;

	s_h = cb->args[0];
	s_idx = idx = cb->args[1];
	s_ip_idx = cb->args[2];

	अगर (cb->strict_check) अणु
		err = inet6_valid_dump_अगरaddr_req(nlh, &fillargs, &tgt_net,
						  skb->sk, cb);
		अगर (err < 0)
			जाओ put_tgt_net;

		err = 0;
		अगर (fillargs.अगरindex) अणु
			dev = __dev_get_by_index(tgt_net, fillargs.अगरindex);
			अगर (!dev) अणु
				err = -ENODEV;
				जाओ put_tgt_net;
			पूर्ण
			idev = __in6_dev_get(dev);
			अगर (idev) अणु
				err = in6_dump_addrs(idev, skb, cb, s_ip_idx,
						     &fillargs);
				अगर (err > 0)
					err = 0;
			पूर्ण
			जाओ put_tgt_net;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_lock();
	cb->seq = atomic_पढ़ो(&tgt_net->ipv6.dev_addr_genid) ^ tgt_net->dev_base_seq;
	क्रम (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		idx = 0;
		head = &tgt_net->dev_index_head[h];
		hlist_क्रम_each_entry_rcu(dev, head, index_hlist) अणु
			अगर (idx < s_idx)
				जाओ cont;
			अगर (h > s_h || idx > s_idx)
				s_ip_idx = 0;
			idev = __in6_dev_get(dev);
			अगर (!idev)
				जाओ cont;

			अगर (in6_dump_addrs(idev, skb, cb, s_ip_idx,
					   &fillargs) < 0)
				जाओ करोne;
cont:
			idx++;
		पूर्ण
	पूर्ण
करोne:
	rcu_पढ़ो_unlock();
	cb->args[0] = h;
	cb->args[1] = idx;
put_tgt_net:
	अगर (fillargs.netnsid >= 0)
		put_net(tgt_net);

	वापस skb->len ? : err;
पूर्ण

अटल पूर्णांक inet6_dump_अगरaddr(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	क्रमागत addr_type_t type = UNICAST_ADDR;

	वापस inet6_dump_addr(skb, cb, type);
पूर्ण

अटल पूर्णांक inet6_dump_अगरmcaddr(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	क्रमागत addr_type_t type = MULTICAST_ADDR;

	वापस inet6_dump_addr(skb, cb, type);
पूर्ण


अटल पूर्णांक inet6_dump_अगरacaddr(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	क्रमागत addr_type_t type = ANYCAST_ADDR;

	वापस inet6_dump_addr(skb, cb, type);
पूर्ण

अटल पूर्णांक inet6_rपंचांग_valid_getaddr_req(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा nlmsghdr *nlh,
				       काष्ठा nlattr **tb,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा अगरaddrmsg *अगरm;
	पूर्णांक i, err;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरm))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid header for get address request");
		वापस -EINVAL;
	पूर्ण

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFA_MAX,
					      अगरa_ipv6_policy, extack);

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरa_prefixlen || अगरm->अगरa_flags || अगरm->अगरa_scope) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid values in header for get address request");
		वापस -EINVAL;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(*अगरm), tb, IFA_MAX,
					    अगरa_ipv6_policy, extack);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <= IFA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल IFA_TARGET_NETNSID:
		हाल IFA_ADDRESS:
		हाल IFA_LOCAL:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported attribute in get address request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet6_rपंचांग_getaddr(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा inet6_fill_args fillargs = अणु
		.portid = NETLINK_CB(in_skb).portid,
		.seq = nlh->nlmsg_seq,
		.event = RTM_NEWADDR,
		.flags = 0,
		.netnsid = -1,
	पूर्ण;
	काष्ठा net *tgt_net = net;
	काष्ठा अगरaddrmsg *अगरm;
	काष्ठा nlattr *tb[IFA_MAX+1];
	काष्ठा in6_addr *addr = शून्य, *peer;
	काष्ठा net_device *dev = शून्य;
	काष्ठा inet6_अगरaddr *अगरa;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	err = inet6_rपंचांग_valid_getaddr_req(in_skb, nlh, tb, extack);
	अगर (err < 0)
		वापस err;

	अगर (tb[IFA_TARGET_NETNSID]) अणु
		fillargs.netnsid = nla_get_s32(tb[IFA_TARGET_NETNSID]);

		tgt_net = rtnl_get_net_ns_capable(NETLINK_CB(in_skb).sk,
						  fillargs.netnsid);
		अगर (IS_ERR(tgt_net))
			वापस PTR_ERR(tgt_net);
	पूर्ण

	addr = extract_addr(tb[IFA_ADDRESS], tb[IFA_LOCAL], &peer);
	अगर (!addr)
		वापस -EINVAL;

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरa_index)
		dev = dev_get_by_index(tgt_net, अगरm->अगरa_index);

	अगरa = ipv6_get_अगरaddr(tgt_net, addr, dev, 1);
	अगर (!अगरa) अणु
		err = -EADDRNOTAVAIL;
		जाओ errout;
	पूर्ण

	skb = nlmsg_new(inet6_अगरaddr_msgsize(), GFP_KERNEL);
	अगर (!skb) अणु
		err = -ENOBUFS;
		जाओ errout_अगरa;
	पूर्ण

	err = inet6_fill_अगरaddr(skb, अगरa, &fillargs);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in inet6_अगरaddr_msgsize() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout_अगरa;
	पूर्ण
	err = rtnl_unicast(skb, tgt_net, NETLINK_CB(in_skb).portid);
errout_अगरa:
	in6_अगरa_put(अगरa);
errout:
	अगर (dev)
		dev_put(dev);
	अगर (fillargs.netnsid >= 0)
		put_net(tgt_net);

	वापस err;
पूर्ण

अटल व्योम inet6_अगरa_notअगरy(पूर्णांक event, काष्ठा inet6_अगरaddr *अगरa)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net *net = dev_net(अगरa->idev->dev);
	काष्ठा inet6_fill_args fillargs = अणु
		.portid = 0,
		.seq = 0,
		.event = event,
		.flags = 0,
		.netnsid = -1,
	पूर्ण;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(inet6_अगरaddr_msgsize(), GFP_ATOMIC);
	अगर (!skb)
		जाओ errout;

	err = inet6_fill_अगरaddr(skb, अगरa, &fillargs);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in inet6_अगरaddr_msgsize() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV6_IFADDR, शून्य, GFP_ATOMIC);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV6_IFADDR, err);
पूर्ण

अटल अंतरभूत व्योम ipv6_store_devconf(काष्ठा ipv6_devconf *cnf,
				__s32 *array, पूर्णांक bytes)
अणु
	BUG_ON(bytes < (DEVCONF_MAX * 4));

	स_रखो(array, 0, bytes);
	array[DEVCONF_FORWARDING] = cnf->क्रमwarding;
	array[DEVCONF_HOPLIMIT] = cnf->hop_limit;
	array[DEVCONF_MTU6] = cnf->mtu6;
	array[DEVCONF_ACCEPT_RA] = cnf->accept_ra;
	array[DEVCONF_ACCEPT_REसूचीECTS] = cnf->accept_redirects;
	array[DEVCONF_AUTOCONF] = cnf->स्वतःconf;
	array[DEVCONF_DAD_TRANSMITS] = cnf->dad_transmits;
	array[DEVCONF_RTR_SOLICITS] = cnf->rtr_solicits;
	array[DEVCONF_RTR_SOLICIT_INTERVAL] =
		jअगरfies_to_msecs(cnf->rtr_solicit_पूर्णांकerval);
	array[DEVCONF_RTR_SOLICIT_MAX_INTERVAL] =
		jअगरfies_to_msecs(cnf->rtr_solicit_max_पूर्णांकerval);
	array[DEVCONF_RTR_SOLICIT_DELAY] =
		jअगरfies_to_msecs(cnf->rtr_solicit_delay);
	array[DEVCONF_FORCE_MLD_VERSION] = cnf->क्रमce_mld_version;
	array[DEVCONF_MLDV1_UNSOLICITED_REPORT_INTERVAL] =
		jअगरfies_to_msecs(cnf->mldv1_unsolicited_report_पूर्णांकerval);
	array[DEVCONF_MLDV2_UNSOLICITED_REPORT_INTERVAL] =
		jअगरfies_to_msecs(cnf->mldv2_unsolicited_report_पूर्णांकerval);
	array[DEVCONF_USE_TEMPADDR] = cnf->use_tempaddr;
	array[DEVCONF_TEMP_VALID_LFT] = cnf->temp_valid_lft;
	array[DEVCONF_TEMP_PREFERED_LFT] = cnf->temp_prefered_lft;
	array[DEVCONF_REGEN_MAX_RETRY] = cnf->regen_max_retry;
	array[DEVCONF_MAX_DESYNC_FACTOR] = cnf->max_desync_factor;
	array[DEVCONF_MAX_ADDRESSES] = cnf->max_addresses;
	array[DEVCONF_ACCEPT_RA_DEFRTR] = cnf->accept_ra_defrtr;
	array[DEVCONF_RA_DEFRTR_METRIC] = cnf->ra_defrtr_metric;
	array[DEVCONF_ACCEPT_RA_MIN_HOP_LIMIT] = cnf->accept_ra_min_hop_limit;
	array[DEVCONF_ACCEPT_RA_PINFO] = cnf->accept_ra_pinfo;
#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
	array[DEVCONF_ACCEPT_RA_RTR_PREF] = cnf->accept_ra_rtr_pref;
	array[DEVCONF_RTR_PROBE_INTERVAL] =
		jअगरfies_to_msecs(cnf->rtr_probe_पूर्णांकerval);
#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
	array[DEVCONF_ACCEPT_RA_RT_INFO_MIN_PLEN] = cnf->accept_ra_rt_info_min_plen;
	array[DEVCONF_ACCEPT_RA_RT_INFO_MAX_PLEN] = cnf->accept_ra_rt_info_max_plen;
#पूर्ण_अगर
#पूर्ण_अगर
	array[DEVCONF_PROXY_NDP] = cnf->proxy_ndp;
	array[DEVCONF_ACCEPT_SOURCE_ROUTE] = cnf->accept_source_route;
#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	array[DEVCONF_OPTIMISTIC_DAD] = cnf->optimistic_dad;
	array[DEVCONF_USE_OPTIMISTIC] = cnf->use_optimistic;
#पूर्ण_अगर
#अगर_घोषित CONFIG_IPV6_MROUTE
	array[DEVCONF_MC_FORWARDING] = cnf->mc_क्रमwarding;
#पूर्ण_अगर
	array[DEVCONF_DISABLE_IPV6] = cnf->disable_ipv6;
	array[DEVCONF_ACCEPT_DAD] = cnf->accept_dad;
	array[DEVCONF_FORCE_TLLAO] = cnf->क्रमce_tllao;
	array[DEVCONF_NDISC_NOTIFY] = cnf->ndisc_notअगरy;
	array[DEVCONF_SUPPRESS_FRAG_NDISC] = cnf->suppress_frag_ndisc;
	array[DEVCONF_ACCEPT_RA_FROM_LOCAL] = cnf->accept_ra_from_local;
	array[DEVCONF_ACCEPT_RA_MTU] = cnf->accept_ra_mtu;
	array[DEVCONF_IGNORE_ROUTES_WITH_LINKDOWN] = cnf->ignore_routes_with_linkकरोwn;
	/* we omit DEVCONF_STABLE_SECRET क्रम now */
	array[DEVCONF_USE_OIF_ADDRS_ONLY] = cnf->use_oअगर_addrs_only;
	array[DEVCONF_DROP_UNICAST_IN_L2_MULTICAST] = cnf->drop_unicast_in_l2_multicast;
	array[DEVCONF_DROP_UNSOLICITED_NA] = cnf->drop_unsolicited_na;
	array[DEVCONF_KEEP_ADDR_ON_DOWN] = cnf->keep_addr_on_करोwn;
	array[DEVCONF_SEG6_ENABLED] = cnf->seg6_enabled;
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	array[DEVCONF_SEG6_REQUIRE_HMAC] = cnf->seg6_require_hmac;
#पूर्ण_अगर
	array[DEVCONF_ENHANCED_DAD] = cnf->enhanced_dad;
	array[DEVCONF_ADDR_GEN_MODE] = cnf->addr_gen_mode;
	array[DEVCONF_DISABLE_POLICY] = cnf->disable_policy;
	array[DEVCONF_NDISC_TCLASS] = cnf->ndisc_tclass;
	array[DEVCONF_RPL_SEG_ENABLED] = cnf->rpl_seg_enabled;
पूर्ण

अटल अंतरभूत माप_प्रकार inet6_अगरla6_size(व्योम)
अणु
	वापस nla_total_size(4) /* IFLA_INET6_FLAGS */
	     + nla_total_size(माप(काष्ठा अगरla_cacheinfo))
	     + nla_total_size(DEVCONF_MAX * 4) /* IFLA_INET6_CONF */
	     + nla_total_size(IPSTATS_MIB_MAX * 8) /* IFLA_INET6_STATS */
	     + nla_total_size(ICMP6_MIB_MAX * 8) /* IFLA_INET6_ICMP6STATS */
	     + nla_total_size(माप(काष्ठा in6_addr)) /* IFLA_INET6_TOKEN */
	     + nla_total_size(1) /* IFLA_INET6_ADDR_GEN_MODE */
	     + 0;
पूर्ण

अटल अंतरभूत माप_प्रकार inet6_अगर_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा अगरinfomsg))
	       + nla_total_size(IFNAMSIZ) /* IFLA_IFNAME */
	       + nla_total_size(MAX_ADDR_LEN) /* IFLA_ADDRESS */
	       + nla_total_size(4) /* IFLA_MTU */
	       + nla_total_size(4) /* IFLA_LINK */
	       + nla_total_size(1) /* IFLA_OPERSTATE */
	       + nla_total_size(inet6_अगरla6_size()); /* IFLA_PROTINFO */
पूर्ण

अटल अंतरभूत व्योम __snmp6_fill_statsdev(u64 *stats, atomic_दीर्घ_t *mib,
					पूर्णांक bytes)
अणु
	पूर्णांक i;
	पूर्णांक pad = bytes - माप(u64) * ICMP6_MIB_MAX;
	BUG_ON(pad < 0);

	/* Use put_unaligned() because stats may not be aligned क्रम u64. */
	put_unaligned(ICMP6_MIB_MAX, &stats[0]);
	क्रम (i = 1; i < ICMP6_MIB_MAX; i++)
		put_unaligned(atomic_दीर्घ_पढ़ो(&mib[i]), &stats[i]);

	स_रखो(&stats[ICMP6_MIB_MAX], 0, pad);
पूर्ण

अटल अंतरभूत व्योम __snmp6_fill_stats64(u64 *stats, व्योम __percpu *mib,
					पूर्णांक bytes, माप_प्रकार syncpoff)
अणु
	पूर्णांक i, c;
	u64 buff[IPSTATS_MIB_MAX];
	पूर्णांक pad = bytes - माप(u64) * IPSTATS_MIB_MAX;

	BUG_ON(pad < 0);

	स_रखो(buff, 0, माप(buff));
	buff[0] = IPSTATS_MIB_MAX;

	क्रम_each_possible_cpu(c) अणु
		क्रम (i = 1; i < IPSTATS_MIB_MAX; i++)
			buff[i] += snmp_get_cpu_field64(mib, c, i, syncpoff);
	पूर्ण

	स_नकल(stats, buff, IPSTATS_MIB_MAX * माप(u64));
	स_रखो(&stats[IPSTATS_MIB_MAX], 0, pad);
पूर्ण

अटल व्योम snmp6_fill_stats(u64 *stats, काष्ठा inet6_dev *idev, पूर्णांक attrtype,
			     पूर्णांक bytes)
अणु
	चयन (attrtype) अणु
	हाल IFLA_INET6_STATS:
		__snmp6_fill_stats64(stats, idev->stats.ipv6, bytes,
				     दुरत्व(काष्ठा ipstats_mib, syncp));
		अवरोध;
	हाल IFLA_INET6_ICMP6STATS:
		__snmp6_fill_statsdev(stats, idev->stats.icmpv6dev->mibs, bytes);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक inet6_fill_अगरla6_attrs(काष्ठा sk_buff *skb, काष्ठा inet6_dev *idev,
				  u32 ext_filter_mask)
अणु
	काष्ठा nlattr *nla;
	काष्ठा अगरla_cacheinfo ci;

	अगर (nla_put_u32(skb, IFLA_INET6_FLAGS, idev->अगर_flags))
		जाओ nla_put_failure;
	ci.max_reयंत्र_len = IPV6_MAXPLEN;
	ci.tstamp = cstamp_delta(idev->tstamp);
	ci.reachable_समय = jअगरfies_to_msecs(idev->nd_parms->reachable_समय);
	ci.retrans_समय = jअगरfies_to_msecs(NEIGH_VAR(idev->nd_parms, RETRANS_TIME));
	अगर (nla_put(skb, IFLA_INET6_CACHEINFO, माप(ci), &ci))
		जाओ nla_put_failure;
	nla = nla_reserve(skb, IFLA_INET6_CONF, DEVCONF_MAX * माप(s32));
	अगर (!nla)
		जाओ nla_put_failure;
	ipv6_store_devconf(&idev->cnf, nla_data(nla), nla_len(nla));

	/* XXX - MC not implemented */

	अगर (ext_filter_mask & RTEXT_FILTER_SKIP_STATS)
		वापस 0;

	nla = nla_reserve(skb, IFLA_INET6_STATS, IPSTATS_MIB_MAX * माप(u64));
	अगर (!nla)
		जाओ nla_put_failure;
	snmp6_fill_stats(nla_data(nla), idev, IFLA_INET6_STATS, nla_len(nla));

	nla = nla_reserve(skb, IFLA_INET6_ICMP6STATS, ICMP6_MIB_MAX * माप(u64));
	अगर (!nla)
		जाओ nla_put_failure;
	snmp6_fill_stats(nla_data(nla), idev, IFLA_INET6_ICMP6STATS, nla_len(nla));

	nla = nla_reserve(skb, IFLA_INET6_TOKEN, माप(काष्ठा in6_addr));
	अगर (!nla)
		जाओ nla_put_failure;
	पढ़ो_lock_bh(&idev->lock);
	स_नकल(nla_data(nla), idev->token.s6_addr, nla_len(nla));
	पढ़ो_unlock_bh(&idev->lock);

	अगर (nla_put_u8(skb, IFLA_INET6_ADDR_GEN_MODE, idev->cnf.addr_gen_mode))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल माप_प्रकार inet6_get_link_af_size(स्थिर काष्ठा net_device *dev,
				     u32 ext_filter_mask)
अणु
	अगर (!__in6_dev_get(dev))
		वापस 0;

	वापस inet6_अगरla6_size();
पूर्ण

अटल पूर्णांक inet6_fill_link_af(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev,
			      u32 ext_filter_mask)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get(dev);

	अगर (!idev)
		वापस -ENODATA;

	अगर (inet6_fill_अगरla6_attrs(skb, idev, ext_filter_mask) < 0)
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक inet6_set_अगरtoken(काष्ठा inet6_dev *idev, काष्ठा in6_addr *token,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा inet6_अगरaddr *अगरp;
	काष्ठा net_device *dev = idev->dev;
	bool clear_token, update_rs = false;
	काष्ठा in6_addr ll_addr;

	ASSERT_RTNL();

	अगर (!token)
		वापस -EINVAL;

	अगर (dev->flags & IFF_LOOPBACK) अणु
		NL_SET_ERR_MSG_MOD(extack, "Device is loopback");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->flags & IFF_NOARP) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Device does not do neighbour discovery");
		वापस -EINVAL;
	पूर्ण

	अगर (!ipv6_accept_ra(idev)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Router advertisement is disabled on device");
		वापस -EINVAL;
	पूर्ण

	अगर (idev->cnf.rtr_solicits == 0) अणु
		NL_SET_ERR_MSG(extack,
			       "Router solicitation is disabled on device");
		वापस -EINVAL;
	पूर्ण

	ग_लिखो_lock_bh(&idev->lock);

	BUILD_BUG_ON(माप(token->s6_addr) != 16);
	स_नकल(idev->token.s6_addr + 8, token->s6_addr + 8, 8);

	ग_लिखो_unlock_bh(&idev->lock);

	clear_token = ipv6_addr_any(token);
	अगर (clear_token)
		जाओ update_lft;

	अगर (!idev->dead && (idev->अगर_flags & IF_READY) &&
	    !ipv6_get_lladdr(dev, &ll_addr, IFA_F_TENTATIVE |
			     IFA_F_OPTIMISTIC)) अणु
		/* If we're not पढ़ोy, then normal अगरup will take care
		 * of this. Otherwise, we need to request our rs here.
		 */
		ndisc_send_rs(dev, &ll_addr, &in6addr_linklocal_allrouters);
		update_rs = true;
	पूर्ण

update_lft:
	ग_लिखो_lock_bh(&idev->lock);

	अगर (update_rs) अणु
		idev->अगर_flags |= IF_RS_SENT;
		idev->rs_पूर्णांकerval = rfc3315_s14_backoff_init(
			idev->cnf.rtr_solicit_पूर्णांकerval);
		idev->rs_probes = 1;
		addrconf_mod_rs_समयr(idev, idev->rs_पूर्णांकerval);
	पूर्ण

	/* Well, that's kinda nasty ... */
	list_क्रम_each_entry(अगरp, &idev->addr_list, अगर_list) अणु
		spin_lock(&अगरp->lock);
		अगर (अगरp->tokenized) अणु
			अगरp->valid_lft = 0;
			अगरp->prefered_lft = 0;
		पूर्ण
		spin_unlock(&अगरp->lock);
	पूर्ण

	ग_लिखो_unlock_bh(&idev->lock);
	inet6_अगरinfo_notअगरy(RTM_NEWLINK, idev);
	addrconf_verअगरy_rtnl();
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy inet6_af_policy[IFLA_INET6_MAX + 1] = अणु
	[IFLA_INET6_ADDR_GEN_MODE]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_INET6_TOKEN]		= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
पूर्ण;

अटल पूर्णांक check_addr_gen_mode(पूर्णांक mode)
अणु
	अगर (mode != IN6_ADDR_GEN_MODE_EUI64 &&
	    mode != IN6_ADDR_GEN_MODE_NONE &&
	    mode != IN6_ADDR_GEN_MODE_STABLE_PRIVACY &&
	    mode != IN6_ADDR_GEN_MODE_RANDOM)
		वापस -EINVAL;
	वापस 1;
पूर्ण

अटल पूर्णांक check_stable_privacy(काष्ठा inet6_dev *idev, काष्ठा net *net,
				पूर्णांक mode)
अणु
	अगर (mode == IN6_ADDR_GEN_MODE_STABLE_PRIVACY &&
	    !idev->cnf.stable_secret.initialized &&
	    !net->ipv6.devconf_dflt->stable_secret.initialized)
		वापस -EINVAL;
	वापस 1;
पूर्ण

अटल पूर्णांक inet6_validate_link_af(स्थिर काष्ठा net_device *dev,
				  स्थिर काष्ठा nlattr *nla)
अणु
	काष्ठा nlattr *tb[IFLA_INET6_MAX + 1];
	काष्ठा inet6_dev *idev = शून्य;
	पूर्णांक err;

	अगर (dev) अणु
		idev = __in6_dev_get(dev);
		अगर (!idev)
			वापस -EAFNOSUPPORT;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, IFLA_INET6_MAX, nla,
					  inet6_af_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (!tb[IFLA_INET6_TOKEN] && !tb[IFLA_INET6_ADDR_GEN_MODE])
		वापस -EINVAL;

	अगर (tb[IFLA_INET6_ADDR_GEN_MODE]) अणु
		u8 mode = nla_get_u8(tb[IFLA_INET6_ADDR_GEN_MODE]);

		अगर (check_addr_gen_mode(mode) < 0)
			वापस -EINVAL;
		अगर (dev && check_stable_privacy(idev, dev_net(dev), mode) < 0)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet6_set_link_af(काष्ठा net_device *dev, स्थिर काष्ठा nlattr *nla,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get(dev);
	काष्ठा nlattr *tb[IFLA_INET6_MAX + 1];
	पूर्णांक err;

	अगर (!idev)
		वापस -EAFNOSUPPORT;

	अगर (nla_parse_nested_deprecated(tb, IFLA_INET6_MAX, nla, शून्य, शून्य) < 0)
		वापस -EINVAL;

	अगर (tb[IFLA_INET6_TOKEN]) अणु
		err = inet6_set_अगरtoken(idev, nla_data(tb[IFLA_INET6_TOKEN]),
					extack);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tb[IFLA_INET6_ADDR_GEN_MODE]) अणु
		u8 mode = nla_get_u8(tb[IFLA_INET6_ADDR_GEN_MODE]);

		idev->cnf.addr_gen_mode = mode;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet6_fill_अगरinfo(काष्ठा sk_buff *skb, काष्ठा inet6_dev *idev,
			     u32 portid, u32 seq, पूर्णांक event, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा net_device *dev = idev->dev;
	काष्ठा अगरinfomsg *hdr;
	काष्ठा nlmsghdr *nlh;
	व्योम *protoinfo;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*hdr), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	hdr = nlmsg_data(nlh);
	hdr->अगरi_family = AF_INET6;
	hdr->__अगरi_pad = 0;
	hdr->अगरi_type = dev->type;
	hdr->अगरi_index = dev->अगरindex;
	hdr->अगरi_flags = dev_get_flags(dev);
	hdr->अगरi_change = 0;

	अगर (nla_put_string(skb, IFLA_IFNAME, dev->name) ||
	    (dev->addr_len &&
	     nla_put(skb, IFLA_ADDRESS, dev->addr_len, dev->dev_addr)) ||
	    nla_put_u32(skb, IFLA_MTU, dev->mtu) ||
	    (dev->अगरindex != dev_get_अगरlink(dev) &&
	     nla_put_u32(skb, IFLA_LINK, dev_get_अगरlink(dev))) ||
	    nla_put_u8(skb, IFLA_OPERSTATE,
		       netअगर_running(dev) ? dev->operstate : IF_OPER_DOWN))
		जाओ nla_put_failure;
	protoinfo = nla_nest_start_noflag(skb, IFLA_PROTINFO);
	अगर (!protoinfo)
		जाओ nla_put_failure;

	अगर (inet6_fill_अगरla6_attrs(skb, idev, 0) < 0)
		जाओ nla_put_failure;

	nla_nest_end(skb, protoinfo);
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक inet6_valid_dump_अगरinfo(स्थिर काष्ठा nlmsghdr *nlh,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा अगरinfomsg *अगरm;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरm))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid header for link dump request");
		वापस -EINVAL;
	पूर्ण

	अगर (nlmsg_attrlen(nlh, माप(*अगरm))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid data after header");
		वापस -EINVAL;
	पूर्ण

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->__अगरi_pad || अगरm->अगरi_type || अगरm->अगरi_flags ||
	    अगरm->अगरi_change || अगरm->अगरi_index) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid values in header for dump request");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet6_dump_अगरinfo(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक h, s_h;
	पूर्णांक idx = 0, s_idx;
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;
	काष्ठा hlist_head *head;

	/* only requests using strict checking can pass data to
	 * influence the dump
	 */
	अगर (cb->strict_check) अणु
		पूर्णांक err = inet6_valid_dump_अगरinfo(cb->nlh, cb->extack);

		अगर (err < 0)
			वापस err;
	पूर्ण

	s_h = cb->args[0];
	s_idx = cb->args[1];

	rcu_पढ़ो_lock();
	क्रम (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		idx = 0;
		head = &net->dev_index_head[h];
		hlist_क्रम_each_entry_rcu(dev, head, index_hlist) अणु
			अगर (idx < s_idx)
				जाओ cont;
			idev = __in6_dev_get(dev);
			अगर (!idev)
				जाओ cont;
			अगर (inet6_fill_अगरinfo(skb, idev,
					      NETLINK_CB(cb->skb).portid,
					      cb->nlh->nlmsg_seq,
					      RTM_NEWLINK, NLM_F_MULTI) < 0)
				जाओ out;
cont:
			idx++;
		पूर्ण
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	cb->args[1] = idx;
	cb->args[0] = h;

	वापस skb->len;
पूर्ण

व्योम inet6_अगरinfo_notअगरy(पूर्णांक event, काष्ठा inet6_dev *idev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net *net = dev_net(idev->dev);
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(inet6_अगर_nlmsg_size(), GFP_ATOMIC);
	अगर (!skb)
		जाओ errout;

	err = inet6_fill_अगरinfo(skb, idev, 0, 0, event, 0);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in inet6_अगर_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV6_IFINFO, शून्य, GFP_ATOMIC);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV6_IFINFO, err);
पूर्ण

अटल अंतरभूत माप_प्रकार inet6_prefix_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा prefixmsg))
	       + nla_total_size(माप(काष्ठा in6_addr))
	       + nla_total_size(माप(काष्ठा prefix_cacheinfo));
पूर्ण

अटल पूर्णांक inet6_fill_prefix(काष्ठा sk_buff *skb, काष्ठा inet6_dev *idev,
			     काष्ठा prefix_info *pinfo, u32 portid, u32 seq,
			     पूर्णांक event, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा prefixmsg *pmsg;
	काष्ठा nlmsghdr *nlh;
	काष्ठा prefix_cacheinfo	ci;

	nlh = nlmsg_put(skb, portid, seq, event, माप(*pmsg), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	pmsg = nlmsg_data(nlh);
	pmsg->prefix_family = AF_INET6;
	pmsg->prefix_pad1 = 0;
	pmsg->prefix_pad2 = 0;
	pmsg->prefix_अगरindex = idev->dev->अगरindex;
	pmsg->prefix_len = pinfo->prefix_len;
	pmsg->prefix_type = pinfo->type;
	pmsg->prefix_pad3 = 0;
	pmsg->prefix_flags = 0;
	अगर (pinfo->onlink)
		pmsg->prefix_flags |= IF_PREFIX_ONLINK;
	अगर (pinfo->स्वतःconf)
		pmsg->prefix_flags |= IF_PREFIX_AUTOCONF;

	अगर (nla_put(skb, PREFIX_ADDRESS, माप(pinfo->prefix), &pinfo->prefix))
		जाओ nla_put_failure;
	ci.preferred_समय = ntohl(pinfo->prefered);
	ci.valid_समय = ntohl(pinfo->valid);
	अगर (nla_put(skb, PREFIX_CACHEINFO, माप(ci), &ci))
		जाओ nla_put_failure;
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम inet6_prefix_notअगरy(पूर्णांक event, काष्ठा inet6_dev *idev,
			 काष्ठा prefix_info *pinfo)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा net *net = dev_net(idev->dev);
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(inet6_prefix_nlmsg_size(), GFP_ATOMIC);
	अगर (!skb)
		जाओ errout;

	err = inet6_fill_prefix(skb, idev, pinfo, 0, 0, event, 0);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in inet6_prefix_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV6_PREFIX, शून्य, GFP_ATOMIC);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV6_PREFIX, err);
पूर्ण

अटल व्योम __ipv6_अगरa_notअगरy(पूर्णांक event, काष्ठा inet6_अगरaddr *अगरp)
अणु
	काष्ठा net *net = dev_net(अगरp->idev->dev);

	अगर (event)
		ASSERT_RTNL();

	inet6_अगरa_notअगरy(event ? : RTM_NEWADDR, अगरp);

	चयन (event) अणु
	हाल RTM_NEWADDR:
		/*
		 * If the address was optimistic we inserted the route at the
		 * start of our DAD process, so we करोn't need to करो it again.
		 * If the device was taken करोwn in the middle of the DAD
		 * cycle there is a race where we could get here without a
		 * host route, so nothing to insert. That will be fixed when
		 * the device is brought up.
		 */
		अगर (अगरp->rt && !rcu_access_poपूर्णांकer(अगरp->rt->fib6_node)) अणु
			ip6_ins_rt(net, अगरp->rt);
		पूर्ण अन्यथा अगर (!अगरp->rt && (अगरp->idev->dev->flags & IFF_UP)) अणु
			pr_warn("BUG: Address %pI6c on device %s is missing its host route.\n",
				&अगरp->addr, अगरp->idev->dev->name);
		पूर्ण

		अगर (अगरp->idev->cnf.क्रमwarding)
			addrconf_join_anycast(अगरp);
		अगर (!ipv6_addr_any(&अगरp->peer_addr))
			addrconf_prefix_route(&अगरp->peer_addr, 128,
					      अगरp->rt_priority, अगरp->idev->dev,
					      0, 0, GFP_ATOMIC);
		अवरोध;
	हाल RTM_DELADDR:
		अगर (अगरp->idev->cnf.क्रमwarding)
			addrconf_leave_anycast(अगरp);
		addrconf_leave_solict(अगरp->idev, &अगरp->addr);
		अगर (!ipv6_addr_any(&अगरp->peer_addr)) अणु
			काष्ठा fib6_info *rt;

			rt = addrconf_get_prefix_route(&अगरp->peer_addr, 128,
						       अगरp->idev->dev, 0, 0,
						       false);
			अगर (rt)
				ip6_del_rt(net, rt, false);
		पूर्ण
		अगर (अगरp->rt) अणु
			ip6_del_rt(net, अगरp->rt, false);
			अगरp->rt = शून्य;
		पूर्ण
		rt_genid_bump_ipv6(net);
		अवरोध;
	पूर्ण
	atomic_inc(&net->ipv6.dev_addr_genid);
पूर्ण

अटल व्योम ipv6_अगरa_notअगरy(पूर्णांक event, काष्ठा inet6_अगरaddr *अगरp)
अणु
	अगर (likely(अगरp->idev->dead == 0))
		__ipv6_अगरa_notअगरy(event, अगरp);
पूर्ण

#अगर_घोषित CONFIG_SYSCTL

अटल पूर्णांक addrconf_sysctl_क्रमward(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक *valp = ctl->data;
	पूर्णांक val = *valp;
	loff_t pos = *ppos;
	काष्ठा ctl_table lctl;
	पूर्णांक ret;

	/*
	 * ctl->data poपूर्णांकs to idev->cnf.क्रमwarding, we should
	 * not modअगरy it until we get the rtnl lock.
	 */
	lctl = *ctl;
	lctl.data = &val;

	ret = proc_करोपूर्णांकvec(&lctl, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो)
		ret = addrconf_fixup_क्रमwarding(ctl, valp, val);
	अगर (ret)
		*ppos = pos;
	वापस ret;
पूर्ण

अटल पूर्णांक addrconf_sysctl_mtu(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा inet6_dev *idev = ctl->extra1;
	पूर्णांक min_mtu = IPV6_MIN_MTU;
	काष्ठा ctl_table lctl;

	lctl = *ctl;
	lctl.extra1 = &min_mtu;
	lctl.extra2 = idev ? &idev->dev->mtu : शून्य;

	वापस proc_करोपूर्णांकvec_minmax(&lctl, ग_लिखो, buffer, lenp, ppos);
पूर्ण

अटल व्योम dev_disable_change(काष्ठा inet6_dev *idev)
अणु
	काष्ठा netdev_notअगरier_info info;

	अगर (!idev || !idev->dev)
		वापस;

	netdev_notअगरier_info_init(&info, idev->dev);
	अगर (idev->cnf.disable_ipv6)
		addrconf_notअगरy(शून्य, NETDEV_DOWN, &info);
	अन्यथा
		addrconf_notअगरy(शून्य, NETDEV_UP, &info);
पूर्ण

अटल व्योम addrconf_disable_change(काष्ठा net *net, __s32 newf)
अणु
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;

	क्रम_each_netdev(net, dev) अणु
		idev = __in6_dev_get(dev);
		अगर (idev) अणु
			पूर्णांक changed = (!idev->cnf.disable_ipv6) ^ (!newf);
			idev->cnf.disable_ipv6 = newf;
			अगर (changed)
				dev_disable_change(idev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक addrconf_disable_ipv6(काष्ठा ctl_table *table, पूर्णांक *p, पूर्णांक newf)
अणु
	काष्ठा net *net;
	पूर्णांक old;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	net = (काष्ठा net *)table->extra2;
	old = *p;
	*p = newf;

	अगर (p == &net->ipv6.devconf_dflt->disable_ipv6) अणु
		rtnl_unlock();
		वापस 0;
	पूर्ण

	अगर (p == &net->ipv6.devconf_all->disable_ipv6) अणु
		net->ipv6.devconf_dflt->disable_ipv6 = newf;
		addrconf_disable_change(net, newf);
	पूर्ण अन्यथा अगर ((!newf) ^ (!old))
		dev_disable_change((काष्ठा inet6_dev *)table->extra1);

	rtnl_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक addrconf_sysctl_disable(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक *valp = ctl->data;
	पूर्णांक val = *valp;
	loff_t pos = *ppos;
	काष्ठा ctl_table lctl;
	पूर्णांक ret;

	/*
	 * ctl->data poपूर्णांकs to idev->cnf.disable_ipv6, we should
	 * not modअगरy it until we get the rtnl lock.
	 */
	lctl = *ctl;
	lctl.data = &val;

	ret = proc_करोपूर्णांकvec(&lctl, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो)
		ret = addrconf_disable_ipv6(ctl, valp, val);
	अगर (ret)
		*ppos = pos;
	वापस ret;
पूर्ण

अटल पूर्णांक addrconf_sysctl_proxy_ndp(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक *valp = ctl->data;
	पूर्णांक ret;
	पूर्णांक old, new;

	old = *valp;
	ret = proc_करोपूर्णांकvec(ctl, ग_लिखो, buffer, lenp, ppos);
	new = *valp;

	अगर (ग_लिखो && old != new) अणु
		काष्ठा net *net = ctl->extra2;

		अगर (!rtnl_trylock())
			वापस restart_syscall();

		अगर (valp == &net->ipv6.devconf_dflt->proxy_ndp)
			inet6_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						     NETCONFA_PROXY_NEIGH,
						     NETCONFA_IFINDEX_DEFAULT,
						     net->ipv6.devconf_dflt);
		अन्यथा अगर (valp == &net->ipv6.devconf_all->proxy_ndp)
			inet6_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						     NETCONFA_PROXY_NEIGH,
						     NETCONFA_IFINDEX_ALL,
						     net->ipv6.devconf_all);
		अन्यथा अणु
			काष्ठा inet6_dev *idev = ctl->extra1;

			inet6_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						     NETCONFA_PROXY_NEIGH,
						     idev->dev->अगरindex,
						     &idev->cnf);
		पूर्ण
		rtnl_unlock();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक addrconf_sysctl_addr_gen_mode(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
					 व्योम *buffer, माप_प्रकार *lenp,
					 loff_t *ppos)
अणु
	पूर्णांक ret = 0;
	u32 new_val;
	काष्ठा inet6_dev *idev = (काष्ठा inet6_dev *)ctl->extra1;
	काष्ठा net *net = (काष्ठा net *)ctl->extra2;
	काष्ठा ctl_table पंचांगp = अणु
		.data = &new_val,
		.maxlen = माप(new_val),
		.mode = ctl->mode,
	पूर्ण;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	new_val = *((u32 *)ctl->data);

	ret = proc_करोuपूर्णांकvec(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	अगर (ret != 0)
		जाओ out;

	अगर (ग_लिखो) अणु
		अगर (check_addr_gen_mode(new_val) < 0) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (idev) अणु
			अगर (check_stable_privacy(idev, net, new_val) < 0) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (idev->cnf.addr_gen_mode != new_val) अणु
				idev->cnf.addr_gen_mode = new_val;
				addrconf_dev_config(idev->dev);
			पूर्ण
		पूर्ण अन्यथा अगर (&net->ipv6.devconf_all->addr_gen_mode == ctl->data) अणु
			काष्ठा net_device *dev;

			net->ipv6.devconf_dflt->addr_gen_mode = new_val;
			क्रम_each_netdev(net, dev) अणु
				idev = __in6_dev_get(dev);
				अगर (idev &&
				    idev->cnf.addr_gen_mode != new_val) अणु
					idev->cnf.addr_gen_mode = new_val;
					addrconf_dev_config(idev->dev);
				पूर्ण
			पूर्ण
		पूर्ण

		*((u32 *)ctl->data) = new_val;
	पूर्ण

out:
	rtnl_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक addrconf_sysctl_stable_secret(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
					 व्योम *buffer, माप_प्रकार *lenp,
					 loff_t *ppos)
अणु
	पूर्णांक err;
	काष्ठा in6_addr addr;
	अक्षर str[IPV6_MAX_STRLEN];
	काष्ठा ctl_table lctl = *ctl;
	काष्ठा net *net = ctl->extra2;
	काष्ठा ipv6_stable_secret *secret = ctl->data;

	अगर (&net->ipv6.devconf_all->stable_secret == ctl->data)
		वापस -EIO;

	lctl.maxlen = IPV6_MAX_STRLEN;
	lctl.data = str;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	अगर (!ग_लिखो && !secret->initialized) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	err = snम_लिखो(str, माप(str), "%pI6", &secret->secret);
	अगर (err >= माप(str)) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	err = proc_करोstring(&lctl, ग_लिखो, buffer, lenp, ppos);
	अगर (err || !ग_लिखो)
		जाओ out;

	अगर (in6_pton(str, -1, addr.in6_u.u6_addr8, -1, शून्य) != 1) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	secret->initialized = true;
	secret->secret = addr;

	अगर (&net->ipv6.devconf_dflt->stable_secret == ctl->data) अणु
		काष्ठा net_device *dev;

		क्रम_each_netdev(net, dev) अणु
			काष्ठा inet6_dev *idev = __in6_dev_get(dev);

			अगर (idev) अणु
				idev->cnf.addr_gen_mode =
					IN6_ADDR_GEN_MODE_STABLE_PRIVACY;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा inet6_dev *idev = ctl->extra1;

		idev->cnf.addr_gen_mode = IN6_ADDR_GEN_MODE_STABLE_PRIVACY;
	पूर्ण

out:
	rtnl_unlock();

	वापस err;
पूर्ण

अटल
पूर्णांक addrconf_sysctl_ignore_routes_with_linkकरोwn(काष्ठा ctl_table *ctl,
						पूर्णांक ग_लिखो, व्योम *buffer,
						माप_प्रकार *lenp,
						loff_t *ppos)
अणु
	पूर्णांक *valp = ctl->data;
	पूर्णांक val = *valp;
	loff_t pos = *ppos;
	काष्ठा ctl_table lctl;
	पूर्णांक ret;

	/* ctl->data poपूर्णांकs to idev->cnf.ignore_routes_when_linkकरोwn
	 * we should not modअगरy it until we get the rtnl lock.
	 */
	lctl = *ctl;
	lctl.data = &val;

	ret = proc_करोपूर्णांकvec(&lctl, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो)
		ret = addrconf_fixup_linkकरोwn(ctl, valp, val);
	अगर (ret)
		*ppos = pos;
	वापस ret;
पूर्ण

अटल
व्योम addrconf_set_nopolicy(काष्ठा rt6_info *rt, पूर्णांक action)
अणु
	अगर (rt) अणु
		अगर (action)
			rt->dst.flags |= DST_NOPOLICY;
		अन्यथा
			rt->dst.flags &= ~DST_NOPOLICY;
	पूर्ण
पूर्ण

अटल
व्योम addrconf_disable_policy_idev(काष्ठा inet6_dev *idev, पूर्णांक val)
अणु
	काष्ठा inet6_अगरaddr *अगरa;

	पढ़ो_lock_bh(&idev->lock);
	list_क्रम_each_entry(अगरa, &idev->addr_list, अगर_list) अणु
		spin_lock(&अगरa->lock);
		अगर (अगरa->rt) अणु
			/* host routes only use builtin fib6_nh */
			काष्ठा fib6_nh *nh = अगरa->rt->fib6_nh;
			पूर्णांक cpu;

			rcu_पढ़ो_lock();
			अगरa->rt->dst_nopolicy = val ? true : false;
			अगर (nh->rt6i_pcpu) अणु
				क्रम_each_possible_cpu(cpu) अणु
					काष्ठा rt6_info **rtp;

					rtp = per_cpu_ptr(nh->rt6i_pcpu, cpu);
					addrconf_set_nopolicy(*rtp, val);
				पूर्ण
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण
		spin_unlock(&अगरa->lock);
	पूर्ण
	पढ़ो_unlock_bh(&idev->lock);
पूर्ण

अटल
पूर्णांक addrconf_disable_policy(काष्ठा ctl_table *ctl, पूर्णांक *valp, पूर्णांक val)
अणु
	काष्ठा inet6_dev *idev;
	काष्ठा net *net;

	अगर (!rtnl_trylock())
		वापस restart_syscall();

	*valp = val;

	net = (काष्ठा net *)ctl->extra2;
	अगर (valp == &net->ipv6.devconf_dflt->disable_policy) अणु
		rtnl_unlock();
		वापस 0;
	पूर्ण

	अगर (valp == &net->ipv6.devconf_all->disable_policy)  अणु
		काष्ठा net_device *dev;

		क्रम_each_netdev(net, dev) अणु
			idev = __in6_dev_get(dev);
			अगर (idev)
				addrconf_disable_policy_idev(idev, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		idev = (काष्ठा inet6_dev *)ctl->extra1;
		addrconf_disable_policy_idev(idev, val);
	पूर्ण

	rtnl_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक addrconf_sysctl_disable_policy(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक *valp = ctl->data;
	पूर्णांक val = *valp;
	loff_t pos = *ppos;
	काष्ठा ctl_table lctl;
	पूर्णांक ret;

	lctl = *ctl;
	lctl.data = &val;
	ret = proc_करोपूर्णांकvec(&lctl, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && (*valp != val))
		ret = addrconf_disable_policy(ctl, valp, val);

	अगर (ret)
		*ppos = pos;

	वापस ret;
पूर्ण

अटल पूर्णांक minus_one = -1;
अटल स्थिर पूर्णांक two_five_five = 255;

अटल स्थिर काष्ठा ctl_table addrconf_sysctl[] = अणु
	अणु
		.procname	= "forwarding",
		.data		= &ipv6_devconf.क्रमwarding,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= addrconf_sysctl_क्रमward,
	पूर्ण,
	अणु
		.procname	= "hop_limit",
		.data		= &ipv6_devconf.hop_limit,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (व्योम *)SYSCTL_ONE,
		.extra2		= (व्योम *)&two_five_five,
	पूर्ण,
	अणु
		.procname	= "mtu",
		.data		= &ipv6_devconf.mtu6,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= addrconf_sysctl_mtu,
	पूर्ण,
	अणु
		.procname	= "accept_ra",
		.data		= &ipv6_devconf.accept_ra,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "accept_redirects",
		.data		= &ipv6_devconf.accept_redirects,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "autoconf",
		.data		= &ipv6_devconf.स्वतःconf,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "dad_transmits",
		.data		= &ipv6_devconf.dad_transmits,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "router_solicitations",
		.data		= &ipv6_devconf.rtr_solicits,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &minus_one,
	पूर्ण,
	अणु
		.procname	= "router_solicitation_interval",
		.data		= &ipv6_devconf.rtr_solicit_पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "router_solicitation_max_interval",
		.data		= &ipv6_devconf.rtr_solicit_max_पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "router_solicitation_delay",
		.data		= &ipv6_devconf.rtr_solicit_delay,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "force_mld_version",
		.data		= &ipv6_devconf.क्रमce_mld_version,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "mldv1_unsolicited_report_interval",
		.data		=
			&ipv6_devconf.mldv1_unsolicited_report_पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_ms_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "mldv2_unsolicited_report_interval",
		.data		=
			&ipv6_devconf.mldv2_unsolicited_report_पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_ms_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "use_tempaddr",
		.data		= &ipv6_devconf.use_tempaddr,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "temp_valid_lft",
		.data		= &ipv6_devconf.temp_valid_lft,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "temp_prefered_lft",
		.data		= &ipv6_devconf.temp_prefered_lft,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "regen_max_retry",
		.data		= &ipv6_devconf.regen_max_retry,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "max_desync_factor",
		.data		= &ipv6_devconf.max_desync_factor,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "max_addresses",
		.data		= &ipv6_devconf.max_addresses,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "accept_ra_defrtr",
		.data		= &ipv6_devconf.accept_ra_defrtr,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "ra_defrtr_metric",
		.data		= &ipv6_devconf.ra_defrtr_metric,
		.maxlen		= माप(u32),
		.mode		= 0644,
		.proc_handler	= proc_करोuपूर्णांकvec_minmax,
		.extra1		= (व्योम *)SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "accept_ra_min_hop_limit",
		.data		= &ipv6_devconf.accept_ra_min_hop_limit,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "accept_ra_pinfo",
		.data		= &ipv6_devconf.accept_ra_pinfo,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
	अणु
		.procname	= "accept_ra_rtr_pref",
		.data		= &ipv6_devconf.accept_ra_rtr_pref,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "router_probe_interval",
		.data		= &ipv6_devconf.rtr_probe_पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
#अगर_घोषित CONFIG_IPV6_ROUTE_INFO
	अणु
		.procname	= "accept_ra_rt_info_min_plen",
		.data		= &ipv6_devconf.accept_ra_rt_info_min_plen,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "accept_ra_rt_info_max_plen",
		.data		= &ipv6_devconf.accept_ra_rt_info_max_plen,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#पूर्ण_अगर
	अणु
		.procname	= "proxy_ndp",
		.data		= &ipv6_devconf.proxy_ndp,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= addrconf_sysctl_proxy_ndp,
	पूर्ण,
	अणु
		.procname	= "accept_source_route",
		.data		= &ipv6_devconf.accept_source_route,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#अगर_घोषित CONFIG_IPV6_OPTIMISTIC_DAD
	अणु
		.procname	= "optimistic_dad",
		.data		= &ipv6_devconf.optimistic_dad,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler   = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "use_optimistic",
		.data		= &ipv6_devconf.use_optimistic,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IPV6_MROUTE
	अणु
		.procname	= "mc_forwarding",
		.data		= &ipv6_devconf.mc_क्रमwarding,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0444,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "disable_ipv6",
		.data		= &ipv6_devconf.disable_ipv6,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= addrconf_sysctl_disable,
	पूर्ण,
	अणु
		.procname	= "accept_dad",
		.data		= &ipv6_devconf.accept_dad,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "force_tllao",
		.data		= &ipv6_devconf.क्रमce_tllao,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "ndisc_notify",
		.data		= &ipv6_devconf.ndisc_notअगरy,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "suppress_frag_ndisc",
		.data		= &ipv6_devconf.suppress_frag_ndisc,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
	अणु
		.procname	= "accept_ra_from_local",
		.data		= &ipv6_devconf.accept_ra_from_local,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "accept_ra_mtu",
		.data		= &ipv6_devconf.accept_ra_mtu,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "stable_secret",
		.data		= &ipv6_devconf.stable_secret,
		.maxlen		= IPV6_MAX_STRLEN,
		.mode		= 0600,
		.proc_handler	= addrconf_sysctl_stable_secret,
	पूर्ण,
	अणु
		.procname	= "use_oif_addrs_only",
		.data		= &ipv6_devconf.use_oअगर_addrs_only,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "ignore_routes_with_linkdown",
		.data		= &ipv6_devconf.ignore_routes_with_linkकरोwn,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= addrconf_sysctl_ignore_routes_with_linkकरोwn,
	पूर्ण,
	अणु
		.procname	= "drop_unicast_in_l2_multicast",
		.data		= &ipv6_devconf.drop_unicast_in_l2_multicast,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "drop_unsolicited_na",
		.data		= &ipv6_devconf.drop_unsolicited_na,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "keep_addr_on_down",
		.data		= &ipv6_devconf.keep_addr_on_करोwn,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,

	पूर्ण,
	अणु
		.procname	= "seg6_enabled",
		.data		= &ipv6_devconf.seg6_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	अणु
		.procname	= "seg6_require_hmac",
		.data		= &ipv6_devconf.seg6_require_hmac,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname       = "enhanced_dad",
		.data           = &ipv6_devconf.enhanced_dad,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname		= "addr_gen_mode",
		.data			= &ipv6_devconf.addr_gen_mode,
		.maxlen			= माप(पूर्णांक),
		.mode			= 0644,
		.proc_handler	= addrconf_sysctl_addr_gen_mode,
	पूर्ण,
	अणु
		.procname       = "disable_policy",
		.data           = &ipv6_devconf.disable_policy,
		.maxlen         = माप(पूर्णांक),
		.mode           = 0644,
		.proc_handler   = addrconf_sysctl_disable_policy,
	पूर्ण,
	अणु
		.procname	= "ndisc_tclass",
		.data		= &ipv6_devconf.ndisc_tclass,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (व्योम *)SYSCTL_ZERO,
		.extra2		= (व्योम *)&two_five_five,
	पूर्ण,
	अणु
		.procname	= "rpl_seg_enabled",
		.data		= &ipv6_devconf.rpl_seg_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		/* sentinel */
	पूर्ण
पूर्ण;

अटल पूर्णांक __addrconf_sysctl_रेजिस्टर(काष्ठा net *net, अक्षर *dev_name,
		काष्ठा inet6_dev *idev, काष्ठा ipv6_devconf *p)
अणु
	पूर्णांक i, अगरindex;
	काष्ठा ctl_table *table;
	अक्षर path[माप("net/ipv6/conf/") + IFNAMSIZ];

	table = kmemdup(addrconf_sysctl, माप(addrconf_sysctl), GFP_KERNEL);
	अगर (!table)
		जाओ out;

	क्रम (i = 0; table[i].data; i++) अणु
		table[i].data += (अक्षर *)p - (अक्षर *)&ipv6_devconf;
		/* If one of these is alपढ़ोy set, then it is not safe to
		 * overग_लिखो either of them: this makes proc_करोपूर्णांकvec_minmax
		 * usable.
		 */
		अगर (!table[i].extra1 && !table[i].extra2) अणु
			table[i].extra1 = idev; /* embedded; no ref */
			table[i].extra2 = net;
		पूर्ण
	पूर्ण

	snम_लिखो(path, माप(path), "net/ipv6/conf/%s", dev_name);

	p->sysctl_header = रेजिस्टर_net_sysctl(net, path, table);
	अगर (!p->sysctl_header)
		जाओ मुक्त;

	अगर (!म_भेद(dev_name, "all"))
		अगरindex = NETCONFA_IFINDEX_ALL;
	अन्यथा अगर (!म_भेद(dev_name, "default"))
		अगरindex = NETCONFA_IFINDEX_DEFAULT;
	अन्यथा
		अगरindex = idev->dev->अगरindex;
	inet6_netconf_notअगरy_devconf(net, RTM_NEWNETCONF, NETCONFA_ALL,
				     अगरindex, p);
	वापस 0;

मुक्त:
	kमुक्त(table);
out:
	वापस -ENOBUFS;
पूर्ण

अटल व्योम __addrconf_sysctl_unरेजिस्टर(काष्ठा net *net,
					 काष्ठा ipv6_devconf *p, पूर्णांक अगरindex)
अणु
	काष्ठा ctl_table *table;

	अगर (!p->sysctl_header)
		वापस;

	table = p->sysctl_header->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(p->sysctl_header);
	p->sysctl_header = शून्य;
	kमुक्त(table);

	inet6_netconf_notअगरy_devconf(net, RTM_DELNETCONF, 0, अगरindex, शून्य);
पूर्ण

अटल पूर्णांक addrconf_sysctl_रेजिस्टर(काष्ठा inet6_dev *idev)
अणु
	पूर्णांक err;

	अगर (!sysctl_dev_name_is_allowed(idev->dev->name))
		वापस -EINVAL;

	err = neigh_sysctl_रेजिस्टर(idev->dev, idev->nd_parms,
				    &ndisc_अगरinfo_sysctl_change);
	अगर (err)
		वापस err;
	err = __addrconf_sysctl_रेजिस्टर(dev_net(idev->dev), idev->dev->name,
					 idev, &idev->cnf);
	अगर (err)
		neigh_sysctl_unरेजिस्टर(idev->nd_parms);

	वापस err;
पूर्ण

अटल व्योम addrconf_sysctl_unरेजिस्टर(काष्ठा inet6_dev *idev)
अणु
	__addrconf_sysctl_unरेजिस्टर(dev_net(idev->dev), &idev->cnf,
				     idev->dev->अगरindex);
	neigh_sysctl_unरेजिस्टर(idev->nd_parms);
पूर्ण


#पूर्ण_अगर

अटल पूर्णांक __net_init addrconf_init_net(काष्ठा net *net)
अणु
	पूर्णांक err = -ENOMEM;
	काष्ठा ipv6_devconf *all, *dflt;

	all = kmemdup(&ipv6_devconf, माप(ipv6_devconf), GFP_KERNEL);
	अगर (!all)
		जाओ err_alloc_all;

	dflt = kmemdup(&ipv6_devconf_dflt, माप(ipv6_devconf_dflt), GFP_KERNEL);
	अगर (!dflt)
		जाओ err_alloc_dflt;

	अगर (IS_ENABLED(CONFIG_SYSCTL) &&
	    !net_eq(net, &init_net)) अणु
		चयन (sysctl_devconf_inherit_init_net) अणु
		हाल 1:  /* copy from init_net */
			स_नकल(all, init_net.ipv6.devconf_all,
			       माप(ipv6_devconf));
			स_नकल(dflt, init_net.ipv6.devconf_dflt,
			       माप(ipv6_devconf_dflt));
			अवरोध;
		हाल 3: /* copy from the current netns */
			स_नकल(all, current->nsproxy->net_ns->ipv6.devconf_all,
			       माप(ipv6_devconf));
			स_नकल(dflt,
			       current->nsproxy->net_ns->ipv6.devconf_dflt,
			       माप(ipv6_devconf_dflt));
			अवरोध;
		हाल 0:
		हाल 2:
			/* use compiled values */
			अवरोध;
		पूर्ण
	पूर्ण

	/* these will be inherited by all namespaces */
	dflt->स्वतःconf = ipv6_शेषs.स्वतःconf;
	dflt->disable_ipv6 = ipv6_शेषs.disable_ipv6;

	dflt->stable_secret.initialized = false;
	all->stable_secret.initialized = false;

	net->ipv6.devconf_all = all;
	net->ipv6.devconf_dflt = dflt;

#अगर_घोषित CONFIG_SYSCTL
	err = __addrconf_sysctl_रेजिस्टर(net, "all", शून्य, all);
	अगर (err < 0)
		जाओ err_reg_all;

	err = __addrconf_sysctl_रेजिस्टर(net, "default", शून्य, dflt);
	अगर (err < 0)
		जाओ err_reg_dflt;
#पूर्ण_अगर
	वापस 0;

#अगर_घोषित CONFIG_SYSCTL
err_reg_dflt:
	__addrconf_sysctl_unरेजिस्टर(net, all, NETCONFA_IFINDEX_ALL);
err_reg_all:
	kमुक्त(dflt);
#पूर्ण_अगर
err_alloc_dflt:
	kमुक्त(all);
err_alloc_all:
	वापस err;
पूर्ण

अटल व्योम __net_निकास addrconf_निकास_net(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_SYSCTL
	__addrconf_sysctl_unरेजिस्टर(net, net->ipv6.devconf_dflt,
				     NETCONFA_IFINDEX_DEFAULT);
	__addrconf_sysctl_unरेजिस्टर(net, net->ipv6.devconf_all,
				     NETCONFA_IFINDEX_ALL);
#पूर्ण_अगर
	kमुक्त(net->ipv6.devconf_dflt);
	kमुक्त(net->ipv6.devconf_all);
पूर्ण

अटल काष्ठा pernet_operations addrconf_ops = अणु
	.init = addrconf_init_net,
	.निकास = addrconf_निकास_net,
पूर्ण;

अटल काष्ठा rtnl_af_ops inet6_ops __पढ़ो_mostly = अणु
	.family		  = AF_INET6,
	.fill_link_af	  = inet6_fill_link_af,
	.get_link_af_size = inet6_get_link_af_size,
	.validate_link_af = inet6_validate_link_af,
	.set_link_af	  = inet6_set_link_af,
पूर्ण;

/*
 *	Init / cleanup code
 */

पूर्णांक __init addrconf_init(व्योम)
अणु
	काष्ठा inet6_dev *idev;
	पूर्णांक i, err;

	err = ipv6_addr_label_init();
	अगर (err < 0) अणु
		pr_crit("%s: cannot initialize default policy table: %d\n",
			__func__, err);
		जाओ out;
	पूर्ण

	err = रेजिस्टर_pernet_subsys(&addrconf_ops);
	अगर (err < 0)
		जाओ out_addrlabel;

	addrconf_wq = create_workqueue("ipv6_addrconf");
	अगर (!addrconf_wq) अणु
		err = -ENOMEM;
		जाओ out_nowq;
	पूर्ण

	/* The addrconf netdev notअगरier requires that loopback_dev
	 * has it's ipv6 निजी inक्रमmation allocated and setup
	 * beक्रमe it can bring up and give link-local addresses
	 * to other devices which are up.
	 *
	 * Unक्रमtunately, loopback_dev is not necessarily the first
	 * entry in the global dev_base list of net devices.  In fact,
	 * it is likely to be the very last entry on that list.
	 * So this causes the notअगरier registry below to try and
	 * give link-local addresses to all devices besides loopback_dev
	 * first, then loopback_dev, which हालs all the non-loopback_dev
	 * devices to fail to get a link-local address.
	 *
	 * So, as a temporary fix, allocate the ipv6 काष्ठाure क्रम
	 * loopback_dev first by hand.
	 * Longer term, all of the dependencies ipv6 has upon the loopback
	 * device and it being up should be हटाओd.
	 */
	rtnl_lock();
	idev = ipv6_add_dev(init_net.loopback_dev);
	rtnl_unlock();
	अगर (IS_ERR(idev)) अणु
		err = PTR_ERR(idev);
		जाओ errlo;
	पूर्ण

	ip6_route_init_special_entries();

	क्रम (i = 0; i < IN6_ADDR_HSIZE; i++)
		INIT_HLIST_HEAD(&inet6_addr_lst[i]);

	रेजिस्टर_netdevice_notअगरier(&ipv6_dev_notf);

	addrconf_verअगरy();

	rtnl_af_रेजिस्टर(&inet6_ops);

	err = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_GETLINK,
				   शून्य, inet6_dump_अगरinfo, 0);
	अगर (err < 0)
		जाओ errout;

	err = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_NEWADDR,
				   inet6_rपंचांग_newaddr, शून्य, 0);
	अगर (err < 0)
		जाओ errout;
	err = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_DELADDR,
				   inet6_rपंचांग_deladdr, शून्य, 0);
	अगर (err < 0)
		जाओ errout;
	err = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_GETADDR,
				   inet6_rपंचांग_getaddr, inet6_dump_अगरaddr,
				   RTNL_FLAG_DOIT_UNLOCKED);
	अगर (err < 0)
		जाओ errout;
	err = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_GETMULTICAST,
				   शून्य, inet6_dump_अगरmcaddr, 0);
	अगर (err < 0)
		जाओ errout;
	err = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_GETANYCAST,
				   शून्य, inet6_dump_अगरacaddr, 0);
	अगर (err < 0)
		जाओ errout;
	err = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_GETNETCONF,
				   inet6_netconf_get_devconf,
				   inet6_netconf_dump_devconf,
				   RTNL_FLAG_DOIT_UNLOCKED);
	अगर (err < 0)
		जाओ errout;
	err = ipv6_addr_label_rtnl_रेजिस्टर();
	अगर (err < 0)
		जाओ errout;

	वापस 0;
errout:
	rtnl_unरेजिस्टर_all(PF_INET6);
	rtnl_af_unरेजिस्टर(&inet6_ops);
	unरेजिस्टर_netdevice_notअगरier(&ipv6_dev_notf);
errlo:
	destroy_workqueue(addrconf_wq);
out_nowq:
	unरेजिस्टर_pernet_subsys(&addrconf_ops);
out_addrlabel:
	ipv6_addr_label_cleanup();
out:
	वापस err;
पूर्ण

व्योम addrconf_cleanup(व्योम)
अणु
	काष्ठा net_device *dev;
	पूर्णांक i;

	unरेजिस्टर_netdevice_notअगरier(&ipv6_dev_notf);
	unरेजिस्टर_pernet_subsys(&addrconf_ops);
	ipv6_addr_label_cleanup();

	rtnl_af_unरेजिस्टर(&inet6_ops);

	rtnl_lock();

	/* clean dev list */
	क्रम_each_netdev(&init_net, dev) अणु
		अगर (__in6_dev_get(dev) == शून्य)
			जारी;
		addrconf_अगरकरोwn(dev, true);
	पूर्ण
	addrconf_अगरकरोwn(init_net.loopback_dev, true);

	/*
	 *	Check hash table.
	 */
	spin_lock_bh(&addrconf_hash_lock);
	क्रम (i = 0; i < IN6_ADDR_HSIZE; i++)
		WARN_ON(!hlist_empty(&inet6_addr_lst[i]));
	spin_unlock_bh(&addrconf_hash_lock);
	cancel_delayed_work(&addr_chk_work);
	rtnl_unlock();

	destroy_workqueue(addrconf_wq);
पूर्ण
