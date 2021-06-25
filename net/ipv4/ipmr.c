<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IP multicast routing support क्रम mrouted 3.6/3.8
 *
 *		(c) 1995 Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *	  Linux Consultancy and Custom Driver Development
 *
 *	Fixes:
 *	Michael Chastain	:	Incorrect size of copying.
 *	Alan Cox		:	Added the cache manager code
 *	Alan Cox		:	Fixed the clone/copy bug and device race.
 *	Mike McLagan		:	Routing by source
 *	Malcolm Beattie		:	Buffer handling fixes.
 *	Alexey Kuznetsov	:	Double buffer मुक्त and other fixes.
 *	SVR Anand		:	Fixed several multicast bugs and problems.
 *	Alexey Kuznetsov	:	Status, optimisations and more.
 *	Brad Parker		:	Better behaviour on mrouted upcall
 *					overflow.
 *      Carlos Picoto           :       PIMv1 Support
 *	Pavlin Ivanov Raकरोslavov:	PIMv2 Registers must checksum only PIM header
 *					Relax this requirement to work with older peers.
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/types.h>
#समावेश <linux/cache.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/igmp.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mroute.h>
#समावेश <linux/init.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/slab.h>
#समावेश <net/net_namespace.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <linux/skbuff.h>
#समावेश <net/route.h>
#समावेश <net/icmp.h>
#समावेश <net/udp.h>
#समावेश <net/raw.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/compat.h>
#समावेश <linux/export.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/checksum.h>
#समावेश <net/netlink.h>
#समावेश <net/fib_rules.h>
#समावेश <linux/netconf.h>
#समावेश <net/rtnh.h>

#समावेश <linux/nospec.h>

काष्ठा ipmr_rule अणु
	काष्ठा fib_rule		common;
पूर्ण;

काष्ठा ipmr_result अणु
	काष्ठा mr_table		*mrt;
पूर्ण;

/* Big lock, protecting vअगर table, mrt cache and mroute socket state.
 * Note that the changes are semaphored via rtnl_lock.
 */

अटल DEFINE_RWLOCK(mrt_lock);

/* Multicast router control variables */

/* Special spinlock क्रम queue of unresolved entries */
अटल DEFINE_SPINLOCK(mfc_unres_lock);

/* We वापस to original Alan's scheme. Hash table of resolved
 * entries is changed only in process context and रक्षित
 * with weak lock mrt_lock. Queue of unresolved entries is रक्षित
 * with strong spinlock mfc_unres_lock.
 *
 * In this हाल data path is मुक्त of exclusive locks at all.
 */

अटल काष्ठा kmem_cache *mrt_cachep __ro_after_init;

अटल काष्ठा mr_table *ipmr_new_table(काष्ठा net *net, u32 id);
अटल व्योम ipmr_मुक्त_table(काष्ठा mr_table *mrt);

अटल व्योम ip_mr_क्रमward(काष्ठा net *net, काष्ठा mr_table *mrt,
			  काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			  काष्ठा mfc_cache *cache, पूर्णांक local);
अटल पूर्णांक ipmr_cache_report(काष्ठा mr_table *mrt,
			     काष्ठा sk_buff *pkt, vअगरi_t vअगरi, पूर्णांक निश्चित);
अटल व्योम mroute_netlink_event(काष्ठा mr_table *mrt, काष्ठा mfc_cache *mfc,
				 पूर्णांक cmd);
अटल व्योम igmpmsg_netlink_event(काष्ठा mr_table *mrt, काष्ठा sk_buff *pkt);
अटल व्योम mroute_clean_tables(काष्ठा mr_table *mrt, पूर्णांक flags);
अटल व्योम ipmr_expire_process(काष्ठा समयr_list *t);

#अगर_घोषित CONFIG_IP_MROUTE_MULTIPLE_TABLES
#घोषणा ipmr_क्रम_each_table(mrt, net)					\
	list_क्रम_each_entry_rcu(mrt, &net->ipv4.mr_tables, list,	\
				lockdep_rtnl_is_held() ||		\
				list_empty(&net->ipv4.mr_tables))

अटल काष्ठा mr_table *ipmr_mr_table_iter(काष्ठा net *net,
					   काष्ठा mr_table *mrt)
अणु
	काष्ठा mr_table *ret;

	अगर (!mrt)
		ret = list_entry_rcu(net->ipv4.mr_tables.next,
				     काष्ठा mr_table, list);
	अन्यथा
		ret = list_entry_rcu(mrt->list.next,
				     काष्ठा mr_table, list);

	अगर (&ret->list == &net->ipv4.mr_tables)
		वापस शून्य;
	वापस ret;
पूर्ण

अटल काष्ठा mr_table *ipmr_get_table(काष्ठा net *net, u32 id)
अणु
	काष्ठा mr_table *mrt;

	ipmr_क्रम_each_table(mrt, net) अणु
		अगर (mrt->id == id)
			वापस mrt;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक ipmr_fib_lookup(काष्ठा net *net, काष्ठा flowi4 *flp4,
			   काष्ठा mr_table **mrt)
अणु
	पूर्णांक err;
	काष्ठा ipmr_result res;
	काष्ठा fib_lookup_arg arg = अणु
		.result = &res,
		.flags = FIB_LOOKUP_NOREF,
	पूर्ण;

	/* update flow अगर oअगर or iअगर poपूर्णांक to device enslaved to l3mdev */
	l3mdev_update_flow(net, flowi4_to_flowi(flp4));

	err = fib_rules_lookup(net->ipv4.mr_rules_ops,
			       flowi4_to_flowi(flp4), 0, &arg);
	अगर (err < 0)
		वापस err;
	*mrt = res.mrt;
	वापस 0;
पूर्ण

अटल पूर्णांक ipmr_rule_action(काष्ठा fib_rule *rule, काष्ठा flowi *flp,
			    पूर्णांक flags, काष्ठा fib_lookup_arg *arg)
अणु
	काष्ठा ipmr_result *res = arg->result;
	काष्ठा mr_table *mrt;

	चयन (rule->action) अणु
	हाल FR_ACT_TO_TBL:
		अवरोध;
	हाल FR_ACT_UNREACHABLE:
		वापस -ENETUNREACH;
	हाल FR_ACT_PROHIBIT:
		वापस -EACCES;
	हाल FR_ACT_BLACKHOLE:
	शेष:
		वापस -EINVAL;
	पूर्ण

	arg->table = fib_rule_get_table(rule, arg);

	mrt = ipmr_get_table(rule->fr_net, arg->table);
	अगर (!mrt)
		वापस -EAGAIN;
	res->mrt = mrt;
	वापस 0;
पूर्ण

अटल पूर्णांक ipmr_rule_match(काष्ठा fib_rule *rule, काष्ठा flowi *fl, पूर्णांक flags)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा nla_policy ipmr_rule_policy[FRA_MAX + 1] = अणु
	FRA_GENERIC_POLICY,
पूर्ण;

अटल पूर्णांक ipmr_rule_configure(काष्ठा fib_rule *rule, काष्ठा sk_buff *skb,
			       काष्ठा fib_rule_hdr *frh, काष्ठा nlattr **tb,
			       काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ipmr_rule_compare(काष्ठा fib_rule *rule, काष्ठा fib_rule_hdr *frh,
			     काष्ठा nlattr **tb)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक ipmr_rule_fill(काष्ठा fib_rule *rule, काष्ठा sk_buff *skb,
			  काष्ठा fib_rule_hdr *frh)
अणु
	frh->dst_len = 0;
	frh->src_len = 0;
	frh->tos     = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fib_rules_ops __net_initस्थिर ipmr_rules_ops_ढाँचा = अणु
	.family		= RTNL_FAMILY_IPMR,
	.rule_size	= माप(काष्ठा ipmr_rule),
	.addr_size	= माप(u32),
	.action		= ipmr_rule_action,
	.match		= ipmr_rule_match,
	.configure	= ipmr_rule_configure,
	.compare	= ipmr_rule_compare,
	.fill		= ipmr_rule_fill,
	.nlgroup	= RTNLGRP_IPV4_RULE,
	.policy		= ipmr_rule_policy,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __net_init ipmr_rules_init(काष्ठा net *net)
अणु
	काष्ठा fib_rules_ops *ops;
	काष्ठा mr_table *mrt;
	पूर्णांक err;

	ops = fib_rules_रेजिस्टर(&ipmr_rules_ops_ढाँचा, net);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);

	INIT_LIST_HEAD(&net->ipv4.mr_tables);

	mrt = ipmr_new_table(net, RT_TABLE_DEFAULT);
	अगर (IS_ERR(mrt)) अणु
		err = PTR_ERR(mrt);
		जाओ err1;
	पूर्ण

	err = fib_शेष_rule_add(ops, 0x7fff, RT_TABLE_DEFAULT, 0);
	अगर (err < 0)
		जाओ err2;

	net->ipv4.mr_rules_ops = ops;
	वापस 0;

err2:
	ipmr_मुक्त_table(mrt);
err1:
	fib_rules_unरेजिस्टर(ops);
	वापस err;
पूर्ण

अटल व्योम __net_निकास ipmr_rules_निकास(काष्ठा net *net)
अणु
	काष्ठा mr_table *mrt, *next;

	rtnl_lock();
	list_क्रम_each_entry_safe(mrt, next, &net->ipv4.mr_tables, list) अणु
		list_del(&mrt->list);
		ipmr_मुक्त_table(mrt);
	पूर्ण
	fib_rules_unरेजिस्टर(net->ipv4.mr_rules_ops);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक ipmr_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			   काष्ठा netlink_ext_ack *extack)
अणु
	वापस fib_rules_dump(net, nb, RTNL_FAMILY_IPMR, extack);
पूर्ण

अटल अचिन्हित पूर्णांक ipmr_rules_seq_पढ़ो(काष्ठा net *net)
अणु
	वापस fib_rules_seq_पढ़ो(net, RTNL_FAMILY_IPMR);
पूर्ण

bool ipmr_rule_शेष(स्थिर काष्ठा fib_rule *rule)
अणु
	वापस fib_rule_matchall(rule) && rule->table == RT_TABLE_DEFAULT;
पूर्ण
EXPORT_SYMBOL(ipmr_rule_शेष);
#अन्यथा
#घोषणा ipmr_क्रम_each_table(mrt, net) \
	क्रम (mrt = net->ipv4.mrt; mrt; mrt = शून्य)

अटल काष्ठा mr_table *ipmr_mr_table_iter(काष्ठा net *net,
					   काष्ठा mr_table *mrt)
अणु
	अगर (!mrt)
		वापस net->ipv4.mrt;
	वापस शून्य;
पूर्ण

अटल काष्ठा mr_table *ipmr_get_table(काष्ठा net *net, u32 id)
अणु
	वापस net->ipv4.mrt;
पूर्ण

अटल पूर्णांक ipmr_fib_lookup(काष्ठा net *net, काष्ठा flowi4 *flp4,
			   काष्ठा mr_table **mrt)
अणु
	*mrt = net->ipv4.mrt;
	वापस 0;
पूर्ण

अटल पूर्णांक __net_init ipmr_rules_init(काष्ठा net *net)
अणु
	काष्ठा mr_table *mrt;

	mrt = ipmr_new_table(net, RT_TABLE_DEFAULT);
	अगर (IS_ERR(mrt))
		वापस PTR_ERR(mrt);
	net->ipv4.mrt = mrt;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास ipmr_rules_निकास(काष्ठा net *net)
अणु
	rtnl_lock();
	ipmr_मुक्त_table(net->ipv4.mrt);
	net->ipv4.mrt = शून्य;
	rtnl_unlock();
पूर्ण

अटल पूर्णांक ipmr_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			   काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ipmr_rules_seq_पढ़ो(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

bool ipmr_rule_शेष(स्थिर काष्ठा fib_rule *rule)
अणु
	वापस true;
पूर्ण
EXPORT_SYMBOL(ipmr_rule_शेष);
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक ipmr_hash_cmp(काष्ठा rhashtable_compare_arg *arg,
				स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा mfc_cache_cmp_arg *cmparg = arg->key;
	काष्ठा mfc_cache *c = (काष्ठा mfc_cache *)ptr;

	वापस cmparg->mfc_mcastgrp != c->mfc_mcastgrp ||
	       cmparg->mfc_origin != c->mfc_origin;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params ipmr_rht_params = अणु
	.head_offset = दुरत्व(काष्ठा mr_mfc, mnode),
	.key_offset = दुरत्व(काष्ठा mfc_cache, cmparg),
	.key_len = माप(काष्ठा mfc_cache_cmp_arg),
	.nelem_hपूर्णांक = 3,
	.obj_cmpfn = ipmr_hash_cmp,
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल व्योम ipmr_new_table_set(काष्ठा mr_table *mrt,
			       काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_IP_MROUTE_MULTIPLE_TABLES
	list_add_tail_rcu(&mrt->list, &net->ipv4.mr_tables);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा mfc_cache_cmp_arg ipmr_mr_table_ops_cmparg_any = अणु
	.mfc_mcastgrp = htonl(INADDR_ANY),
	.mfc_origin = htonl(INADDR_ANY),
पूर्ण;

अटल काष्ठा mr_table_ops ipmr_mr_table_ops = अणु
	.rht_params = &ipmr_rht_params,
	.cmparg_any = &ipmr_mr_table_ops_cmparg_any,
पूर्ण;

अटल काष्ठा mr_table *ipmr_new_table(काष्ठा net *net, u32 id)
अणु
	काष्ठा mr_table *mrt;

	/* "pimreg%u" should not exceed 16 bytes (IFNAMSIZ) */
	अगर (id != RT_TABLE_DEFAULT && id >= 1000000000)
		वापस ERR_PTR(-EINVAL);

	mrt = ipmr_get_table(net, id);
	अगर (mrt)
		वापस mrt;

	वापस mr_table_alloc(net, id, &ipmr_mr_table_ops,
			      ipmr_expire_process, ipmr_new_table_set);
पूर्ण

अटल व्योम ipmr_मुक्त_table(काष्ठा mr_table *mrt)
अणु
	del_समयr_sync(&mrt->ipmr_expire_समयr);
	mroute_clean_tables(mrt, MRT_FLUSH_VIFS | MRT_FLUSH_VIFS_STATIC |
				 MRT_FLUSH_MFC | MRT_FLUSH_MFC_STATIC);
	rhltable_destroy(&mrt->mfc_hash);
	kमुक्त(mrt);
पूर्ण

/* Service routines creating भव पूर्णांकerfaces: DVMRP tunnels and PIMREG */

/* Initialize ipmr pimreg/tunnel in_device */
अटल bool ipmr_init_vअगर_indev(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा in_device *in_dev;

	ASSERT_RTNL();

	in_dev = __in_dev_get_rtnl(dev);
	अगर (!in_dev)
		वापस false;
	ipv4_devconf_setall(in_dev);
	neigh_parms_data_state_setall(in_dev->arp_parms);
	IPV4_DEVCONF(in_dev->cnf, RP_FILTER) = 0;

	वापस true;
पूर्ण

अटल काष्ठा net_device *ipmr_new_tunnel(काष्ठा net *net, काष्ठा vअगरctl *v)
अणु
	काष्ठा net_device *tunnel_dev, *new_dev;
	काष्ठा ip_tunnel_parm p = अणु पूर्ण;
	पूर्णांक err;

	tunnel_dev = __dev_get_by_name(net, "tunl0");
	अगर (!tunnel_dev)
		जाओ out;

	p.iph.daddr = v->vअगरc_rmt_addr.s_addr;
	p.iph.saddr = v->vअगरc_lcl_addr.s_addr;
	p.iph.version = 4;
	p.iph.ihl = 5;
	p.iph.protocol = IPPROTO_IPIP;
	प्र_लिखो(p.name, "dvmrp%d", v->vअगरc_vअगरi);

	अगर (!tunnel_dev->netdev_ops->nकरो_tunnel_ctl)
		जाओ out;
	err = tunnel_dev->netdev_ops->nकरो_tunnel_ctl(tunnel_dev, &p,
			SIOCADDTUNNEL);
	अगर (err)
		जाओ out;

	new_dev = __dev_get_by_name(net, p.name);
	अगर (!new_dev)
		जाओ out;

	new_dev->flags |= IFF_MULTICAST;
	अगर (!ipmr_init_vअगर_indev(new_dev))
		जाओ out_unरेजिस्टर;
	अगर (dev_खोलो(new_dev, शून्य))
		जाओ out_unरेजिस्टर;
	dev_hold(new_dev);
	err = dev_set_allmulti(new_dev, 1);
	अगर (err) अणु
		dev_बंद(new_dev);
		tunnel_dev->netdev_ops->nकरो_tunnel_ctl(tunnel_dev, &p,
				SIOCDELTUNNEL);
		dev_put(new_dev);
		new_dev = ERR_PTR(err);
	पूर्ण
	वापस new_dev;

out_unरेजिस्टर:
	unरेजिस्टर_netdevice(new_dev);
out:
	वापस ERR_PTR(-ENOBUFS);
पूर्ण

#अगर defined(CONFIG_IP_PIMSM_V1) || defined(CONFIG_IP_PIMSM_V2)
अटल netdev_tx_t reg_vअगर_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा mr_table *mrt;
	काष्ठा flowi4 fl4 = अणु
		.flowi4_oअगर	= dev->अगरindex,
		.flowi4_iअगर	= skb->skb_iअगर ? : LOOPBACK_IFINDEX,
		.flowi4_mark	= skb->mark,
	पूर्ण;
	पूर्णांक err;

	err = ipmr_fib_lookup(net, &fl4, &mrt);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	पढ़ो_lock(&mrt_lock);
	dev->stats.tx_bytes += skb->len;
	dev->stats.tx_packets++;
	ipmr_cache_report(mrt, skb, mrt->mroute_reg_vअगर_num, IGMPMSG_WHOLEPKT);
	पढ़ो_unlock(&mrt_lock);
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक reg_vअगर_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops reg_vअगर_netdev_ops = अणु
	.nकरो_start_xmit	= reg_vअगर_xmit,
	.nकरो_get_अगरlink = reg_vअगर_get_अगरlink,
पूर्ण;

अटल व्योम reg_vअगर_setup(काष्ठा net_device *dev)
अणु
	dev->type		= ARPHRD_PIMREG;
	dev->mtu		= ETH_DATA_LEN - माप(काष्ठा iphdr) - 8;
	dev->flags		= IFF_NOARP;
	dev->netdev_ops		= &reg_vअगर_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
	dev->features		|= NETIF_F_NETNS_LOCAL;
पूर्ण

अटल काष्ठा net_device *ipmr_reg_vअगर(काष्ठा net *net, काष्ठा mr_table *mrt)
अणु
	काष्ठा net_device *dev;
	अक्षर name[IFNAMSIZ];

	अगर (mrt->id == RT_TABLE_DEFAULT)
		प्र_लिखो(name, "pimreg");
	अन्यथा
		प्र_लिखो(name, "pimreg%u", mrt->id);

	dev = alloc_netdev(0, name, NET_NAME_UNKNOWN, reg_vअगर_setup);

	अगर (!dev)
		वापस शून्य;

	dev_net_set(dev, net);

	अगर (रेजिस्टर_netdevice(dev)) अणु
		मुक्त_netdev(dev);
		वापस शून्य;
	पूर्ण

	अगर (!ipmr_init_vअगर_indev(dev))
		जाओ failure;
	अगर (dev_खोलो(dev, शून्य))
		जाओ failure;

	dev_hold(dev);

	वापस dev;

failure:
	unरेजिस्टर_netdevice(dev);
	वापस शून्य;
पूर्ण

/* called with rcu_पढ़ो_lock() */
अटल पूर्णांक __pim_rcv(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
		     अचिन्हित पूर्णांक pimlen)
अणु
	काष्ठा net_device *reg_dev = शून्य;
	काष्ठा iphdr *encap;

	encap = (काष्ठा iphdr *)(skb_transport_header(skb) + pimlen);
	/* Check that:
	 * a. packet is really sent to a multicast group
	 * b. packet is not a शून्य-REGISTER
	 * c. packet is not truncated
	 */
	अगर (!ipv4_is_multicast(encap->daddr) ||
	    encap->tot_len == 0 ||
	    ntohs(encap->tot_len) + pimlen > skb->len)
		वापस 1;

	पढ़ो_lock(&mrt_lock);
	अगर (mrt->mroute_reg_vअगर_num >= 0)
		reg_dev = mrt->vअगर_table[mrt->mroute_reg_vअगर_num].dev;
	पढ़ो_unlock(&mrt_lock);

	अगर (!reg_dev)
		वापस 1;

	skb->mac_header = skb->network_header;
	skb_pull(skb, (u8 *)encap - skb->data);
	skb_reset_network_header(skb);
	skb->protocol = htons(ETH_P_IP);
	skb->ip_summed = CHECKSUM_NONE;

	skb_tunnel_rx(skb, reg_dev, dev_net(reg_dev));

	netअगर_rx(skb);

	वापस NET_RX_SUCCESS;
पूर्ण
#अन्यथा
अटल काष्ठा net_device *ipmr_reg_vअगर(काष्ठा net *net, काष्ठा mr_table *mrt)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक call_ipmr_vअगर_entry_notअगरiers(काष्ठा net *net,
					 क्रमागत fib_event_type event_type,
					 काष्ठा vअगर_device *vअगर,
					 vअगरi_t vअगर_index, u32 tb_id)
अणु
	वापस mr_call_vअगर_notअगरiers(net, RTNL_FAMILY_IPMR, event_type,
				     vअगर, vअगर_index, tb_id,
				     &net->ipv4.ipmr_seq);
पूर्ण

अटल पूर्णांक call_ipmr_mfc_entry_notअगरiers(काष्ठा net *net,
					 क्रमागत fib_event_type event_type,
					 काष्ठा mfc_cache *mfc, u32 tb_id)
अणु
	वापस mr_call_mfc_notअगरiers(net, RTNL_FAMILY_IPMR, event_type,
				     &mfc->_c, tb_id, &net->ipv4.ipmr_seq);
पूर्ण

/**
 *	vअगर_delete - Delete a VIF entry
 *	@mrt: Table to delete from
 *	@vअगरi: VIF identअगरier to delete
 *	@notअगरy: Set to 1, अगर the caller is a notअगरier_call
 *	@head: अगर unरेजिस्टरing the VIF, place it on this queue
 */
अटल पूर्णांक vअगर_delete(काष्ठा mr_table *mrt, पूर्णांक vअगरi, पूर्णांक notअगरy,
		      काष्ठा list_head *head)
अणु
	काष्ठा net *net = पढ़ो_pnet(&mrt->net);
	काष्ठा vअगर_device *v;
	काष्ठा net_device *dev;
	काष्ठा in_device *in_dev;

	अगर (vअगरi < 0 || vअगरi >= mrt->maxvअगर)
		वापस -EADDRNOTAVAIL;

	v = &mrt->vअगर_table[vअगरi];

	अगर (VIF_EXISTS(mrt, vअगरi))
		call_ipmr_vअगर_entry_notअगरiers(net, FIB_EVENT_VIF_DEL, v, vअगरi,
					      mrt->id);

	ग_लिखो_lock_bh(&mrt_lock);
	dev = v->dev;
	v->dev = शून्य;

	अगर (!dev) अणु
		ग_लिखो_unlock_bh(&mrt_lock);
		वापस -EADDRNOTAVAIL;
	पूर्ण

	अगर (vअगरi == mrt->mroute_reg_vअगर_num)
		mrt->mroute_reg_vअगर_num = -1;

	अगर (vअगरi + 1 == mrt->maxvअगर) अणु
		पूर्णांक पंचांगp;

		क्रम (पंचांगp = vअगरi - 1; पंचांगp >= 0; पंचांगp--) अणु
			अगर (VIF_EXISTS(mrt, पंचांगp))
				अवरोध;
		पूर्ण
		mrt->maxvअगर = पंचांगp+1;
	पूर्ण

	ग_लिखो_unlock_bh(&mrt_lock);

	dev_set_allmulti(dev, -1);

	in_dev = __in_dev_get_rtnl(dev);
	अगर (in_dev) अणु
		IPV4_DEVCONF(in_dev->cnf, MC_FORWARDING)--;
		inet_netconf_notअगरy_devconf(dev_net(dev), RTM_NEWNETCONF,
					    NETCONFA_MC_FORWARDING,
					    dev->अगरindex, &in_dev->cnf);
		ip_rt_multicast_event(in_dev);
	पूर्ण

	अगर (v->flags & (VIFF_TUNNEL | VIFF_REGISTER) && !notअगरy)
		unरेजिस्टर_netdevice_queue(dev, head);

	dev_put(dev);
	वापस 0;
पूर्ण

अटल व्योम ipmr_cache_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा mr_mfc *c = container_of(head, काष्ठा mr_mfc, rcu);

	kmem_cache_मुक्त(mrt_cachep, (काष्ठा mfc_cache *)c);
पूर्ण

अटल व्योम ipmr_cache_मुक्त(काष्ठा mfc_cache *c)
अणु
	call_rcu(&c->_c.rcu, ipmr_cache_मुक्त_rcu);
पूर्ण

/* Destroy an unresolved cache entry, समाप्तing queued skbs
 * and reporting error to netlink पढ़ोers.
 */
अटल व्योम ipmr_destroy_unres(काष्ठा mr_table *mrt, काष्ठा mfc_cache *c)
अणु
	काष्ठा net *net = पढ़ो_pnet(&mrt->net);
	काष्ठा sk_buff *skb;
	काष्ठा nlmsgerr *e;

	atomic_dec(&mrt->cache_resolve_queue_len);

	जबतक ((skb = skb_dequeue(&c->_c.mfc_un.unres.unresolved))) अणु
		अगर (ip_hdr(skb)->version == 0) अणु
			काष्ठा nlmsghdr *nlh = skb_pull(skb,
							माप(काष्ठा iphdr));
			nlh->nlmsg_type = NLMSG_ERROR;
			nlh->nlmsg_len = nlmsg_msg_size(माप(काष्ठा nlmsgerr));
			skb_trim(skb, nlh->nlmsg_len);
			e = nlmsg_data(nlh);
			e->error = -ETIMEDOUT;
			स_रखो(&e->msg, 0, माप(e->msg));

			rtnl_unicast(skb, net, NETLINK_CB(skb).portid);
		पूर्ण अन्यथा अणु
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	ipmr_cache_मुक्त(c);
पूर्ण

/* Timer process क्रम the unresolved queue. */
अटल व्योम ipmr_expire_process(काष्ठा समयr_list *t)
अणु
	काष्ठा mr_table *mrt = from_समयr(mrt, t, ipmr_expire_समयr);
	काष्ठा mr_mfc *c, *next;
	अचिन्हित दीर्घ expires;
	अचिन्हित दीर्घ now;

	अगर (!spin_trylock(&mfc_unres_lock)) अणु
		mod_समयr(&mrt->ipmr_expire_समयr, jअगरfies+HZ/10);
		वापस;
	पूर्ण

	अगर (list_empty(&mrt->mfc_unres_queue))
		जाओ out;

	now = jअगरfies;
	expires = 10*HZ;

	list_क्रम_each_entry_safe(c, next, &mrt->mfc_unres_queue, list) अणु
		अगर (समय_after(c->mfc_un.unres.expires, now)) अणु
			अचिन्हित दीर्घ पूर्णांकerval = c->mfc_un.unres.expires - now;
			अगर (पूर्णांकerval < expires)
				expires = पूर्णांकerval;
			जारी;
		पूर्ण

		list_del(&c->list);
		mroute_netlink_event(mrt, (काष्ठा mfc_cache *)c, RTM_DELROUTE);
		ipmr_destroy_unres(mrt, (काष्ठा mfc_cache *)c);
	पूर्ण

	अगर (!list_empty(&mrt->mfc_unres_queue))
		mod_समयr(&mrt->ipmr_expire_समयr, jअगरfies + expires);

out:
	spin_unlock(&mfc_unres_lock);
पूर्ण

/* Fill oअगरs list. It is called under ग_लिखो locked mrt_lock. */
अटल व्योम ipmr_update_thresholds(काष्ठा mr_table *mrt, काष्ठा mr_mfc *cache,
				   अचिन्हित अक्षर *ttls)
अणु
	पूर्णांक vअगरi;

	cache->mfc_un.res.minvअगर = MAXVIFS;
	cache->mfc_un.res.maxvअगर = 0;
	स_रखो(cache->mfc_un.res.ttls, 255, MAXVIFS);

	क्रम (vअगरi = 0; vअगरi < mrt->maxvअगर; vअगरi++) अणु
		अगर (VIF_EXISTS(mrt, vअगरi) &&
		    ttls[vअगरi] && ttls[vअगरi] < 255) अणु
			cache->mfc_un.res.ttls[vअगरi] = ttls[vअगरi];
			अगर (cache->mfc_un.res.minvअगर > vअगरi)
				cache->mfc_un.res.minvअगर = vअगरi;
			अगर (cache->mfc_un.res.maxvअगर <= vअगरi)
				cache->mfc_un.res.maxvअगर = vअगरi + 1;
		पूर्ण
	पूर्ण
	cache->mfc_un.res.lastuse = jअगरfies;
पूर्ण

अटल पूर्णांक vअगर_add(काष्ठा net *net, काष्ठा mr_table *mrt,
		   काष्ठा vअगरctl *vअगरc, पूर्णांक mrtsock)
अणु
	काष्ठा netdev_phys_item_id ppid = अणु पूर्ण;
	पूर्णांक vअगरi = vअगरc->vअगरc_vअगरi;
	काष्ठा vअगर_device *v = &mrt->vअगर_table[vअगरi];
	काष्ठा net_device *dev;
	काष्ठा in_device *in_dev;
	पूर्णांक err;

	/* Is vअगर busy ? */
	अगर (VIF_EXISTS(mrt, vअगरi))
		वापस -EADDRINUSE;

	चयन (vअगरc->vअगरc_flags) अणु
	हाल VIFF_REGISTER:
		अगर (!ipmr_pimsm_enabled())
			वापस -EINVAL;
		/* Special Purpose VIF in PIM
		 * All the packets will be sent to the daemon
		 */
		अगर (mrt->mroute_reg_vअगर_num >= 0)
			वापस -EADDRINUSE;
		dev = ipmr_reg_vअगर(net, mrt);
		अगर (!dev)
			वापस -ENOBUFS;
		err = dev_set_allmulti(dev, 1);
		अगर (err) अणु
			unरेजिस्टर_netdevice(dev);
			dev_put(dev);
			वापस err;
		पूर्ण
		अवरोध;
	हाल VIFF_TUNNEL:
		dev = ipmr_new_tunnel(net, vअगरc);
		अगर (IS_ERR(dev))
			वापस PTR_ERR(dev);
		अवरोध;
	हाल VIFF_USE_IFINDEX:
	हाल 0:
		अगर (vअगरc->vअगरc_flags == VIFF_USE_IFINDEX) अणु
			dev = dev_get_by_index(net, vअगरc->vअगरc_lcl_अगरindex);
			अगर (dev && !__in_dev_get_rtnl(dev)) अणु
				dev_put(dev);
				वापस -EADDRNOTAVAIL;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev = ip_dev_find(net, vअगरc->vअगरc_lcl_addr.s_addr);
		पूर्ण
		अगर (!dev)
			वापस -EADDRNOTAVAIL;
		err = dev_set_allmulti(dev, 1);
		अगर (err) अणु
			dev_put(dev);
			वापस err;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	in_dev = __in_dev_get_rtnl(dev);
	अगर (!in_dev) अणु
		dev_put(dev);
		वापस -EADDRNOTAVAIL;
	पूर्ण
	IPV4_DEVCONF(in_dev->cnf, MC_FORWARDING)++;
	inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF, NETCONFA_MC_FORWARDING,
				    dev->अगरindex, &in_dev->cnf);
	ip_rt_multicast_event(in_dev);

	/* Fill in the VIF काष्ठाures */
	vअगर_device_init(v, dev, vअगरc->vअगरc_rate_limit,
			vअगरc->vअगरc_threshold,
			vअगरc->vअगरc_flags | (!mrtsock ? VIFF_STATIC : 0),
			(VIFF_TUNNEL | VIFF_REGISTER));

	err = dev_get_port_parent_id(dev, &ppid, true);
	अगर (err == 0) अणु
		स_नकल(v->dev_parent_id.id, ppid.id, ppid.id_len);
		v->dev_parent_id.id_len = ppid.id_len;
	पूर्ण अन्यथा अणु
		v->dev_parent_id.id_len = 0;
	पूर्ण

	v->local = vअगरc->vअगरc_lcl_addr.s_addr;
	v->remote = vअगरc->vअगरc_rmt_addr.s_addr;

	/* And finish update writing critical data */
	ग_लिखो_lock_bh(&mrt_lock);
	v->dev = dev;
	अगर (v->flags & VIFF_REGISTER)
		mrt->mroute_reg_vअगर_num = vअगरi;
	अगर (vअगरi+1 > mrt->maxvअगर)
		mrt->maxvअगर = vअगरi+1;
	ग_लिखो_unlock_bh(&mrt_lock);
	call_ipmr_vअगर_entry_notअगरiers(net, FIB_EVENT_VIF_ADD, v, vअगरi, mrt->id);
	वापस 0;
पूर्ण

/* called with rcu_पढ़ो_lock() */
अटल काष्ठा mfc_cache *ipmr_cache_find(काष्ठा mr_table *mrt,
					 __be32 origin,
					 __be32 mcastgrp)
अणु
	काष्ठा mfc_cache_cmp_arg arg = अणु
			.mfc_mcastgrp = mcastgrp,
			.mfc_origin = origin
	पूर्ण;

	वापस mr_mfc_find(mrt, &arg);
पूर्ण

/* Look क्रम a (*,G) entry */
अटल काष्ठा mfc_cache *ipmr_cache_find_any(काष्ठा mr_table *mrt,
					     __be32 mcastgrp, पूर्णांक vअगरi)
अणु
	काष्ठा mfc_cache_cmp_arg arg = अणु
			.mfc_mcastgrp = mcastgrp,
			.mfc_origin = htonl(INADDR_ANY)
	पूर्ण;

	अगर (mcastgrp == htonl(INADDR_ANY))
		वापस mr_mfc_find_any_parent(mrt, vअगरi);
	वापस mr_mfc_find_any(mrt, vअगरi, &arg);
पूर्ण

/* Look क्रम a (S,G,iअगर) entry अगर parent != -1 */
अटल काष्ठा mfc_cache *ipmr_cache_find_parent(काष्ठा mr_table *mrt,
						__be32 origin, __be32 mcastgrp,
						पूर्णांक parent)
अणु
	काष्ठा mfc_cache_cmp_arg arg = अणु
			.mfc_mcastgrp = mcastgrp,
			.mfc_origin = origin,
	पूर्ण;

	वापस mr_mfc_find_parent(mrt, &arg, parent);
पूर्ण

/* Allocate a multicast cache entry */
अटल काष्ठा mfc_cache *ipmr_cache_alloc(व्योम)
अणु
	काष्ठा mfc_cache *c = kmem_cache_zalloc(mrt_cachep, GFP_KERNEL);

	अगर (c) अणु
		c->_c.mfc_un.res.last_निश्चित = jअगरfies - MFC_ASSERT_THRESH - 1;
		c->_c.mfc_un.res.minvअगर = MAXVIFS;
		c->_c.मुक्त = ipmr_cache_मुक्त_rcu;
		refcount_set(&c->_c.mfc_un.res.refcount, 1);
	पूर्ण
	वापस c;
पूर्ण

अटल काष्ठा mfc_cache *ipmr_cache_alloc_unres(व्योम)
अणु
	काष्ठा mfc_cache *c = kmem_cache_zalloc(mrt_cachep, GFP_ATOMIC);

	अगर (c) अणु
		skb_queue_head_init(&c->_c.mfc_un.unres.unresolved);
		c->_c.mfc_un.unres.expires = jअगरfies + 10 * HZ;
	पूर्ण
	वापस c;
पूर्ण

/* A cache entry has gone पूर्णांकo a resolved state from queued */
अटल व्योम ipmr_cache_resolve(काष्ठा net *net, काष्ठा mr_table *mrt,
			       काष्ठा mfc_cache *uc, काष्ठा mfc_cache *c)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nlmsgerr *e;

	/* Play the pending entries through our router */
	जबतक ((skb = __skb_dequeue(&uc->_c.mfc_un.unres.unresolved))) अणु
		अगर (ip_hdr(skb)->version == 0) अणु
			काष्ठा nlmsghdr *nlh = skb_pull(skb,
							माप(काष्ठा iphdr));

			अगर (mr_fill_mroute(mrt, skb, &c->_c,
					   nlmsg_data(nlh)) > 0) अणु
				nlh->nlmsg_len = skb_tail_poपूर्णांकer(skb) -
						 (u8 *)nlh;
			पूर्ण अन्यथा अणु
				nlh->nlmsg_type = NLMSG_ERROR;
				nlh->nlmsg_len = nlmsg_msg_size(माप(काष्ठा nlmsgerr));
				skb_trim(skb, nlh->nlmsg_len);
				e = nlmsg_data(nlh);
				e->error = -EMSGSIZE;
				स_रखो(&e->msg, 0, माप(e->msg));
			पूर्ण

			rtnl_unicast(skb, net, NETLINK_CB(skb).portid);
		पूर्ण अन्यथा अणु
			ip_mr_क्रमward(net, mrt, skb->dev, skb, c, 0);
		पूर्ण
	पूर्ण
पूर्ण

/* Bounce a cache query up to mrouted and netlink.
 *
 * Called under mrt_lock.
 */
अटल पूर्णांक ipmr_cache_report(काष्ठा mr_table *mrt,
			     काष्ठा sk_buff *pkt, vअगरi_t vअगरi, पूर्णांक निश्चित)
अणु
	स्थिर पूर्णांक ihl = ip_hdrlen(pkt);
	काष्ठा sock *mroute_sk;
	काष्ठा igmphdr *igmp;
	काष्ठा igmpmsg *msg;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	अगर (निश्चित == IGMPMSG_WHOLEPKT || निश्चित == IGMPMSG_WRVIFWHOLE)
		skb = skb_पुनः_स्मृति_headroom(pkt, माप(काष्ठा iphdr));
	अन्यथा
		skb = alloc_skb(128, GFP_ATOMIC);

	अगर (!skb)
		वापस -ENOBUFS;

	अगर (निश्चित == IGMPMSG_WHOLEPKT || निश्चित == IGMPMSG_WRVIFWHOLE) अणु
		/* Ugly, but we have no choice with this पूर्णांकerface.
		 * Duplicate old header, fix ihl, length etc.
		 * And all this only to mangle msg->im_msgtype and
		 * to set msg->im_mbz to "mbz" :-)
		 */
		skb_push(skb, माप(काष्ठा iphdr));
		skb_reset_network_header(skb);
		skb_reset_transport_header(skb);
		msg = (काष्ठा igmpmsg *)skb_network_header(skb);
		स_नकल(msg, skb_network_header(pkt), माप(काष्ठा iphdr));
		msg->im_msgtype = निश्चित;
		msg->im_mbz = 0;
		अगर (निश्चित == IGMPMSG_WRVIFWHOLE) अणु
			msg->im_vअगर = vअगरi;
			msg->im_vअगर_hi = vअगरi >> 8;
		पूर्ण अन्यथा अणु
			msg->im_vअगर = mrt->mroute_reg_vअगर_num;
			msg->im_vअगर_hi = mrt->mroute_reg_vअगर_num >> 8;
		पूर्ण
		ip_hdr(skb)->ihl = माप(काष्ठा iphdr) >> 2;
		ip_hdr(skb)->tot_len = htons(ntohs(ip_hdr(pkt)->tot_len) +
					     माप(काष्ठा iphdr));
	पूर्ण अन्यथा अणु
		/* Copy the IP header */
		skb_set_network_header(skb, skb->len);
		skb_put(skb, ihl);
		skb_copy_to_linear_data(skb, pkt->data, ihl);
		/* Flag to the kernel this is a route add */
		ip_hdr(skb)->protocol = 0;
		msg = (काष्ठा igmpmsg *)skb_network_header(skb);
		msg->im_vअगर = vअगरi;
		msg->im_vअगर_hi = vअगरi >> 8;
		skb_dst_set(skb, dst_clone(skb_dst(pkt)));
		/* Add our header */
		igmp = skb_put(skb, माप(काष्ठा igmphdr));
		igmp->type = निश्चित;
		msg->im_msgtype = निश्चित;
		igmp->code = 0;
		ip_hdr(skb)->tot_len = htons(skb->len);	/* Fix the length */
		skb->transport_header = skb->network_header;
	पूर्ण

	rcu_पढ़ो_lock();
	mroute_sk = rcu_dereference(mrt->mroute_sk);
	अगर (!mroute_sk) अणु
		rcu_पढ़ो_unlock();
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	igmpmsg_netlink_event(mrt, skb);

	/* Deliver to mrouted */
	ret = sock_queue_rcv_skb(mroute_sk, skb);
	rcu_पढ़ो_unlock();
	अगर (ret < 0) अणु
		net_warn_ratelimited("mroute: pending queue full, dropping entries\n");
		kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

/* Queue a packet क्रम resolution. It माला_लो locked cache entry! */
अटल पूर्णांक ipmr_cache_unresolved(काष्ठा mr_table *mrt, vअगरi_t vअगरi,
				 काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा mfc_cache *c;
	bool found = false;
	पूर्णांक err;

	spin_lock_bh(&mfc_unres_lock);
	list_क्रम_each_entry(c, &mrt->mfc_unres_queue, _c.list) अणु
		अगर (c->mfc_mcastgrp == iph->daddr &&
		    c->mfc_origin == iph->saddr) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		/* Create a new entry अगर allowable */
		c = ipmr_cache_alloc_unres();
		अगर (!c) अणु
			spin_unlock_bh(&mfc_unres_lock);

			kमुक्त_skb(skb);
			वापस -ENOBUFS;
		पूर्ण

		/* Fill in the new cache entry */
		c->_c.mfc_parent = -1;
		c->mfc_origin	= iph->saddr;
		c->mfc_mcastgrp	= iph->daddr;

		/* Reflect first query at mrouted. */
		err = ipmr_cache_report(mrt, skb, vअगरi, IGMPMSG_NOCACHE);

		अगर (err < 0) अणु
			/* If the report failed throw the cache entry
			   out - Brad Parker
			 */
			spin_unlock_bh(&mfc_unres_lock);

			ipmr_cache_मुक्त(c);
			kमुक्त_skb(skb);
			वापस err;
		पूर्ण

		atomic_inc(&mrt->cache_resolve_queue_len);
		list_add(&c->_c.list, &mrt->mfc_unres_queue);
		mroute_netlink_event(mrt, c, RTM_NEWROUTE);

		अगर (atomic_पढ़ो(&mrt->cache_resolve_queue_len) == 1)
			mod_समयr(&mrt->ipmr_expire_समयr,
				  c->_c.mfc_un.unres.expires);
	पूर्ण

	/* See अगर we can append the packet */
	अगर (c->_c.mfc_un.unres.unresolved.qlen > 3) अणु
		kमुक्त_skb(skb);
		err = -ENOBUFS;
	पूर्ण अन्यथा अणु
		अगर (dev) अणु
			skb->dev = dev;
			skb->skb_iअगर = dev->अगरindex;
		पूर्ण
		skb_queue_tail(&c->_c.mfc_un.unres.unresolved, skb);
		err = 0;
	पूर्ण

	spin_unlock_bh(&mfc_unres_lock);
	वापस err;
पूर्ण

/* MFC cache manipulation by user space mroute daemon */

अटल पूर्णांक ipmr_mfc_delete(काष्ठा mr_table *mrt, काष्ठा mfcctl *mfc, पूर्णांक parent)
अणु
	काष्ठा net *net = पढ़ो_pnet(&mrt->net);
	काष्ठा mfc_cache *c;

	/* The entries are added/deleted only under RTNL */
	rcu_पढ़ो_lock();
	c = ipmr_cache_find_parent(mrt, mfc->mfcc_origin.s_addr,
				   mfc->mfcc_mcastgrp.s_addr, parent);
	rcu_पढ़ो_unlock();
	अगर (!c)
		वापस -ENOENT;
	rhltable_हटाओ(&mrt->mfc_hash, &c->_c.mnode, ipmr_rht_params);
	list_del_rcu(&c->_c.list);
	call_ipmr_mfc_entry_notअगरiers(net, FIB_EVENT_ENTRY_DEL, c, mrt->id);
	mroute_netlink_event(mrt, c, RTM_DELROUTE);
	mr_cache_put(&c->_c);

	वापस 0;
पूर्ण

अटल पूर्णांक ipmr_mfc_add(काष्ठा net *net, काष्ठा mr_table *mrt,
			काष्ठा mfcctl *mfc, पूर्णांक mrtsock, पूर्णांक parent)
अणु
	काष्ठा mfc_cache *uc, *c;
	काष्ठा mr_mfc *_uc;
	bool found;
	पूर्णांक ret;

	अगर (mfc->mfcc_parent >= MAXVIFS)
		वापस -ENखाता;

	/* The entries are added/deleted only under RTNL */
	rcu_पढ़ो_lock();
	c = ipmr_cache_find_parent(mrt, mfc->mfcc_origin.s_addr,
				   mfc->mfcc_mcastgrp.s_addr, parent);
	rcu_पढ़ो_unlock();
	अगर (c) अणु
		ग_लिखो_lock_bh(&mrt_lock);
		c->_c.mfc_parent = mfc->mfcc_parent;
		ipmr_update_thresholds(mrt, &c->_c, mfc->mfcc_ttls);
		अगर (!mrtsock)
			c->_c.mfc_flags |= MFC_STATIC;
		ग_लिखो_unlock_bh(&mrt_lock);
		call_ipmr_mfc_entry_notअगरiers(net, FIB_EVENT_ENTRY_REPLACE, c,
					      mrt->id);
		mroute_netlink_event(mrt, c, RTM_NEWROUTE);
		वापस 0;
	पूर्ण

	अगर (mfc->mfcc_mcastgrp.s_addr != htonl(INADDR_ANY) &&
	    !ipv4_is_multicast(mfc->mfcc_mcastgrp.s_addr))
		वापस -EINVAL;

	c = ipmr_cache_alloc();
	अगर (!c)
		वापस -ENOMEM;

	c->mfc_origin = mfc->mfcc_origin.s_addr;
	c->mfc_mcastgrp = mfc->mfcc_mcastgrp.s_addr;
	c->_c.mfc_parent = mfc->mfcc_parent;
	ipmr_update_thresholds(mrt, &c->_c, mfc->mfcc_ttls);
	अगर (!mrtsock)
		c->_c.mfc_flags |= MFC_STATIC;

	ret = rhltable_insert_key(&mrt->mfc_hash, &c->cmparg, &c->_c.mnode,
				  ipmr_rht_params);
	अगर (ret) अणु
		pr_err("ipmr: rhtable insert error %d\n", ret);
		ipmr_cache_मुक्त(c);
		वापस ret;
	पूर्ण
	list_add_tail_rcu(&c->_c.list, &mrt->mfc_cache_list);
	/* Check to see अगर we resolved a queued list. If so we
	 * need to send on the frames and tidy up.
	 */
	found = false;
	spin_lock_bh(&mfc_unres_lock);
	list_क्रम_each_entry(_uc, &mrt->mfc_unres_queue, list) अणु
		uc = (काष्ठा mfc_cache *)_uc;
		अगर (uc->mfc_origin == c->mfc_origin &&
		    uc->mfc_mcastgrp == c->mfc_mcastgrp) अणु
			list_del(&_uc->list);
			atomic_dec(&mrt->cache_resolve_queue_len);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (list_empty(&mrt->mfc_unres_queue))
		del_समयr(&mrt->ipmr_expire_समयr);
	spin_unlock_bh(&mfc_unres_lock);

	अगर (found) अणु
		ipmr_cache_resolve(net, mrt, uc, c);
		ipmr_cache_मुक्त(uc);
	पूर्ण
	call_ipmr_mfc_entry_notअगरiers(net, FIB_EVENT_ENTRY_ADD, c, mrt->id);
	mroute_netlink_event(mrt, c, RTM_NEWROUTE);
	वापस 0;
पूर्ण

/* Close the multicast socket, and clear the vअगर tables etc */
अटल व्योम mroute_clean_tables(काष्ठा mr_table *mrt, पूर्णांक flags)
अणु
	काष्ठा net *net = पढ़ो_pnet(&mrt->net);
	काष्ठा mr_mfc *c, *पंचांगp;
	काष्ठा mfc_cache *cache;
	LIST_HEAD(list);
	पूर्णांक i;

	/* Shut करोwn all active vअगर entries */
	अगर (flags & (MRT_FLUSH_VIFS | MRT_FLUSH_VIFS_STATIC)) अणु
		क्रम (i = 0; i < mrt->maxvअगर; i++) अणु
			अगर (((mrt->vअगर_table[i].flags & VIFF_STATIC) &&
			     !(flags & MRT_FLUSH_VIFS_STATIC)) ||
			    (!(mrt->vअगर_table[i].flags & VIFF_STATIC) && !(flags & MRT_FLUSH_VIFS)))
				जारी;
			vअगर_delete(mrt, i, 0, &list);
		पूर्ण
		unरेजिस्टर_netdevice_many(&list);
	पूर्ण

	/* Wipe the cache */
	अगर (flags & (MRT_FLUSH_MFC | MRT_FLUSH_MFC_STATIC)) अणु
		list_क्रम_each_entry_safe(c, पंचांगp, &mrt->mfc_cache_list, list) अणु
			अगर (((c->mfc_flags & MFC_STATIC) && !(flags & MRT_FLUSH_MFC_STATIC)) ||
			    (!(c->mfc_flags & MFC_STATIC) && !(flags & MRT_FLUSH_MFC)))
				जारी;
			rhltable_हटाओ(&mrt->mfc_hash, &c->mnode, ipmr_rht_params);
			list_del_rcu(&c->list);
			cache = (काष्ठा mfc_cache *)c;
			call_ipmr_mfc_entry_notअगरiers(net, FIB_EVENT_ENTRY_DEL, cache,
						      mrt->id);
			mroute_netlink_event(mrt, cache, RTM_DELROUTE);
			mr_cache_put(c);
		पूर्ण
	पूर्ण

	अगर (flags & MRT_FLUSH_MFC) अणु
		अगर (atomic_पढ़ो(&mrt->cache_resolve_queue_len) != 0) अणु
			spin_lock_bh(&mfc_unres_lock);
			list_क्रम_each_entry_safe(c, पंचांगp, &mrt->mfc_unres_queue, list) अणु
				list_del(&c->list);
				cache = (काष्ठा mfc_cache *)c;
				mroute_netlink_event(mrt, cache, RTM_DELROUTE);
				ipmr_destroy_unres(mrt, cache);
			पूर्ण
			spin_unlock_bh(&mfc_unres_lock);
		पूर्ण
	पूर्ण
पूर्ण

/* called from ip_ra_control(), beक्रमe an RCU grace period,
 * we करोnt need to call synchronize_rcu() here
 */
अटल व्योम mrtsock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा mr_table *mrt;

	rtnl_lock();
	ipmr_क्रम_each_table(mrt, net) अणु
		अगर (sk == rtnl_dereference(mrt->mroute_sk)) अणु
			IPV4_DEVCONF_ALL(net, MC_FORWARDING)--;
			inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						    NETCONFA_MC_FORWARDING,
						    NETCONFA_IFINDEX_ALL,
						    net->ipv4.devconf_all);
			RCU_INIT_POINTER(mrt->mroute_sk, शून्य);
			mroute_clean_tables(mrt, MRT_FLUSH_VIFS | MRT_FLUSH_MFC);
		पूर्ण
	पूर्ण
	rtnl_unlock();
पूर्ण

/* Socket options and भव पूर्णांकerface manipulation. The whole
 * भव पूर्णांकerface प्रणाली is a complete heap, but unक्रमtunately
 * that's how BSD mrouted happens to think. Maybe one day with a proper
 * MOSPF/PIM router set up we can clean this up.
 */

पूर्णांक ip_mroute_setsockopt(काष्ठा sock *sk, पूर्णांक optname, sockptr_t optval,
			 अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा net *net = sock_net(sk);
	पूर्णांक val, ret = 0, parent = 0;
	काष्ठा mr_table *mrt;
	काष्ठा vअगरctl vअगर;
	काष्ठा mfcctl mfc;
	bool करो_wrvअगरwhole;
	u32 uval;

	/* There's one exception to the lock - MRT_DONE which needs to unlock */
	rtnl_lock();
	अगर (sk->sk_type != SOCK_RAW ||
	    inet_sk(sk)->inet_num != IPPROTO_IGMP) अणु
		ret = -EOPNOTSUPP;
		जाओ out_unlock;
	पूर्ण

	mrt = ipmr_get_table(net, raw_sk(sk)->ipmr_table ? : RT_TABLE_DEFAULT);
	अगर (!mrt) अणु
		ret = -ENOENT;
		जाओ out_unlock;
	पूर्ण
	अगर (optname != MRT_INIT) अणु
		अगर (sk != rcu_access_poपूर्णांकer(mrt->mroute_sk) &&
		    !ns_capable(net->user_ns, CAP_NET_ADMIN)) अणु
			ret = -EACCES;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	चयन (optname) अणु
	हाल MRT_INIT:
		अगर (optlen != माप(पूर्णांक)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (rtnl_dereference(mrt->mroute_sk)) अणु
			ret = -EADDRINUSE;
			अवरोध;
		पूर्ण

		ret = ip_ra_control(sk, 1, mrtsock_deकाष्ठा);
		अगर (ret == 0) अणु
			rcu_assign_poपूर्णांकer(mrt->mroute_sk, sk);
			IPV4_DEVCONF_ALL(net, MC_FORWARDING)++;
			inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						    NETCONFA_MC_FORWARDING,
						    NETCONFA_IFINDEX_ALL,
						    net->ipv4.devconf_all);
		पूर्ण
		अवरोध;
	हाल MRT_DONE:
		अगर (sk != rcu_access_poपूर्णांकer(mrt->mroute_sk)) अणु
			ret = -EACCES;
		पूर्ण अन्यथा अणु
			/* We need to unlock here because mrtsock_deकाष्ठा takes
			 * care of rtnl itself and we can't change that due to
			 * the IP_ROUTER_ALERT setsockopt which runs without it.
			 */
			rtnl_unlock();
			ret = ip_ra_control(sk, 0, शून्य);
			जाओ out;
		पूर्ण
		अवरोध;
	हाल MRT_ADD_VIF:
	हाल MRT_DEL_VIF:
		अगर (optlen != माप(vअगर)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (copy_from_sockptr(&vअगर, optval, माप(vअगर))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (vअगर.vअगरc_vअगरi >= MAXVIFS) अणु
			ret = -ENखाता;
			अवरोध;
		पूर्ण
		अगर (optname == MRT_ADD_VIF) अणु
			ret = vअगर_add(net, mrt, &vअगर,
				      sk == rtnl_dereference(mrt->mroute_sk));
		पूर्ण अन्यथा अणु
			ret = vअगर_delete(mrt, vअगर.vअगरc_vअगरi, 0, शून्य);
		पूर्ण
		अवरोध;
	/* Manipulate the क्रमwarding caches. These live
	 * in a sort of kernel/user symbiosis.
	 */
	हाल MRT_ADD_MFC:
	हाल MRT_DEL_MFC:
		parent = -1;
		fallthrough;
	हाल MRT_ADD_MFC_PROXY:
	हाल MRT_DEL_MFC_PROXY:
		अगर (optlen != माप(mfc)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (copy_from_sockptr(&mfc, optval, माप(mfc))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (parent == 0)
			parent = mfc.mfcc_parent;
		अगर (optname == MRT_DEL_MFC || optname == MRT_DEL_MFC_PROXY)
			ret = ipmr_mfc_delete(mrt, &mfc, parent);
		अन्यथा
			ret = ipmr_mfc_add(net, mrt, &mfc,
					   sk == rtnl_dereference(mrt->mroute_sk),
					   parent);
		अवरोध;
	हाल MRT_FLUSH:
		अगर (optlen != माप(val)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (copy_from_sockptr(&val, optval, माप(val))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		mroute_clean_tables(mrt, val);
		अवरोध;
	/* Control PIM निश्चित. */
	हाल MRT_ASSERT:
		अगर (optlen != माप(val)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (copy_from_sockptr(&val, optval, माप(val))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण
		mrt->mroute_करो_निश्चित = val;
		अवरोध;
	हाल MRT_PIM:
		अगर (!ipmr_pimsm_enabled()) अणु
			ret = -ENOPROTOOPT;
			अवरोध;
		पूर्ण
		अगर (optlen != माप(val)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (copy_from_sockptr(&val, optval, माप(val))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		करो_wrvअगरwhole = (val == IGMPMSG_WRVIFWHOLE);
		val = !!val;
		अगर (val != mrt->mroute_करो_pim) अणु
			mrt->mroute_करो_pim = val;
			mrt->mroute_करो_निश्चित = val;
			mrt->mroute_करो_wrvअगरwhole = करो_wrvअगरwhole;
		पूर्ण
		अवरोध;
	हाल MRT_TABLE:
		अगर (!IS_BUILTIN(CONFIG_IP_MROUTE_MULTIPLE_TABLES)) अणु
			ret = -ENOPROTOOPT;
			अवरोध;
		पूर्ण
		अगर (optlen != माप(uval)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (copy_from_sockptr(&uval, optval, माप(uval))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (sk == rtnl_dereference(mrt->mroute_sk)) अणु
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			mrt = ipmr_new_table(net, uval);
			अगर (IS_ERR(mrt))
				ret = PTR_ERR(mrt);
			अन्यथा
				raw_sk(sk)->ipmr_table = uval;
		पूर्ण
		अवरोध;
	/* Spurious command, or MRT_VERSION which you cannot set. */
	शेष:
		ret = -ENOPROTOOPT;
	पूर्ण
out_unlock:
	rtnl_unlock();
out:
	वापस ret;
पूर्ण

/* Getsock opt support क्रम the multicast routing प्रणाली. */
पूर्णांक ip_mroute_माला_लोockopt(काष्ठा sock *sk, पूर्णांक optname, अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	पूर्णांक olr;
	पूर्णांक val;
	काष्ठा net *net = sock_net(sk);
	काष्ठा mr_table *mrt;

	अगर (sk->sk_type != SOCK_RAW ||
	    inet_sk(sk)->inet_num != IPPROTO_IGMP)
		वापस -EOPNOTSUPP;

	mrt = ipmr_get_table(net, raw_sk(sk)->ipmr_table ? : RT_TABLE_DEFAULT);
	अगर (!mrt)
		वापस -ENOENT;

	चयन (optname) अणु
	हाल MRT_VERSION:
		val = 0x0305;
		अवरोध;
	हाल MRT_PIM:
		अगर (!ipmr_pimsm_enabled())
			वापस -ENOPROTOOPT;
		val = mrt->mroute_करो_pim;
		अवरोध;
	हाल MRT_ASSERT:
		val = mrt->mroute_करो_निश्चित;
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (get_user(olr, optlen))
		वापस -EFAULT;
	olr = min_t(अचिन्हित पूर्णांक, olr, माप(पूर्णांक));
	अगर (olr < 0)
		वापस -EINVAL;
	अगर (put_user(olr, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, olr))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/* The IP multicast ioctl support routines. */
पूर्णांक ipmr_ioctl(काष्ठा sock *sk, पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा sioc_sg_req sr;
	काष्ठा sioc_vअगर_req vr;
	काष्ठा vअगर_device *vअगर;
	काष्ठा mfc_cache *c;
	काष्ठा net *net = sock_net(sk);
	काष्ठा mr_table *mrt;

	mrt = ipmr_get_table(net, raw_sk(sk)->ipmr_table ? : RT_TABLE_DEFAULT);
	अगर (!mrt)
		वापस -ENOENT;

	चयन (cmd) अणु
	हाल SIOCGETVIFCNT:
		अगर (copy_from_user(&vr, arg, माप(vr)))
			वापस -EFAULT;
		अगर (vr.vअगरi >= mrt->maxvअगर)
			वापस -EINVAL;
		vr.vअगरi = array_index_nospec(vr.vअगरi, mrt->maxvअगर);
		पढ़ो_lock(&mrt_lock);
		vअगर = &mrt->vअगर_table[vr.vअगरi];
		अगर (VIF_EXISTS(mrt, vr.vअगरi)) अणु
			vr.icount = vअगर->pkt_in;
			vr.ocount = vअगर->pkt_out;
			vr.ibytes = vअगर->bytes_in;
			vr.obytes = vअगर->bytes_out;
			पढ़ो_unlock(&mrt_lock);

			अगर (copy_to_user(arg, &vr, माप(vr)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
		पढ़ो_unlock(&mrt_lock);
		वापस -EADDRNOTAVAIL;
	हाल SIOCGETSGCNT:
		अगर (copy_from_user(&sr, arg, माप(sr)))
			वापस -EFAULT;

		rcu_पढ़ो_lock();
		c = ipmr_cache_find(mrt, sr.src.s_addr, sr.grp.s_addr);
		अगर (c) अणु
			sr.pktcnt = c->_c.mfc_un.res.pkt;
			sr.bytecnt = c->_c.mfc_un.res.bytes;
			sr.wrong_अगर = c->_c.mfc_un.res.wrong_अगर;
			rcu_पढ़ो_unlock();

			अगर (copy_to_user(arg, &sr, माप(sr)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
		rcu_पढ़ो_unlock();
		वापस -EADDRNOTAVAIL;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_sioc_sg_req अणु
	काष्ठा in_addr src;
	काष्ठा in_addr grp;
	compat_uदीर्घ_t pktcnt;
	compat_uदीर्घ_t bytecnt;
	compat_uदीर्घ_t wrong_अगर;
पूर्ण;

काष्ठा compat_sioc_vअगर_req अणु
	vअगरi_t	vअगरi;		/* Which अगरace */
	compat_uदीर्घ_t icount;
	compat_uदीर्घ_t ocount;
	compat_uदीर्घ_t ibytes;
	compat_uदीर्घ_t obytes;
पूर्ण;

पूर्णांक ipmr_compat_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा compat_sioc_sg_req sr;
	काष्ठा compat_sioc_vअगर_req vr;
	काष्ठा vअगर_device *vअगर;
	काष्ठा mfc_cache *c;
	काष्ठा net *net = sock_net(sk);
	काष्ठा mr_table *mrt;

	mrt = ipmr_get_table(net, raw_sk(sk)->ipmr_table ? : RT_TABLE_DEFAULT);
	अगर (!mrt)
		वापस -ENOENT;

	चयन (cmd) अणु
	हाल SIOCGETVIFCNT:
		अगर (copy_from_user(&vr, arg, माप(vr)))
			वापस -EFAULT;
		अगर (vr.vअगरi >= mrt->maxvअगर)
			वापस -EINVAL;
		vr.vअगरi = array_index_nospec(vr.vअगरi, mrt->maxvअगर);
		पढ़ो_lock(&mrt_lock);
		vअगर = &mrt->vअगर_table[vr.vअगरi];
		अगर (VIF_EXISTS(mrt, vr.vअगरi)) अणु
			vr.icount = vअगर->pkt_in;
			vr.ocount = vअगर->pkt_out;
			vr.ibytes = vअगर->bytes_in;
			vr.obytes = vअगर->bytes_out;
			पढ़ो_unlock(&mrt_lock);

			अगर (copy_to_user(arg, &vr, माप(vr)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
		पढ़ो_unlock(&mrt_lock);
		वापस -EADDRNOTAVAIL;
	हाल SIOCGETSGCNT:
		अगर (copy_from_user(&sr, arg, माप(sr)))
			वापस -EFAULT;

		rcu_पढ़ो_lock();
		c = ipmr_cache_find(mrt, sr.src.s_addr, sr.grp.s_addr);
		अगर (c) अणु
			sr.pktcnt = c->_c.mfc_un.res.pkt;
			sr.bytecnt = c->_c.mfc_un.res.bytes;
			sr.wrong_अगर = c->_c.mfc_un.res.wrong_अगर;
			rcu_पढ़ो_unlock();

			अगर (copy_to_user(arg, &sr, माप(sr)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
		rcu_पढ़ो_unlock();
		वापस -EADDRNOTAVAIL;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ipmr_device_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);
	काष्ठा mr_table *mrt;
	काष्ठा vअगर_device *v;
	पूर्णांक ct;

	अगर (event != NETDEV_UNREGISTER)
		वापस NOTIFY_DONE;

	ipmr_क्रम_each_table(mrt, net) अणु
		v = &mrt->vअगर_table[0];
		क्रम (ct = 0; ct < mrt->maxvअगर; ct++, v++) अणु
			अगर (v->dev == dev)
				vअगर_delete(mrt, ct, 1, शून्य);
		पूर्ण
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ip_mr_notअगरier = अणु
	.notअगरier_call = ipmr_device_event,
पूर्ण;

/* Encapsulate a packet by attaching a valid IPIP header to it.
 * This aव्योमs tunnel drivers and other mess and gives us the speed so
 * important क्रम multicast video.
 */
अटल व्योम ip_encap(काष्ठा net *net, काष्ठा sk_buff *skb,
		     __be32 saddr, __be32 daddr)
अणु
	काष्ठा iphdr *iph;
	स्थिर काष्ठा iphdr *old_iph = ip_hdr(skb);

	skb_push(skb, माप(काष्ठा iphdr));
	skb->transport_header = skb->network_header;
	skb_reset_network_header(skb);
	iph = ip_hdr(skb);

	iph->version	=	4;
	iph->tos	=	old_iph->tos;
	iph->ttl	=	old_iph->ttl;
	iph->frag_off	=	0;
	iph->daddr	=	daddr;
	iph->saddr	=	saddr;
	iph->protocol	=	IPPROTO_IPIP;
	iph->ihl	=	5;
	iph->tot_len	=	htons(skb->len);
	ip_select_ident(net, skb, शून्य);
	ip_send_check(iph);

	स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));
	nf_reset_ct(skb);
पूर्ण

अटल अंतरभूत पूर्णांक ipmr_क्रमward_finish(काष्ठा net *net, काष्ठा sock *sk,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_options *opt = &(IPCB(skb)->opt);

	IP_INC_STATS(net, IPSTATS_MIB_OUTFORWDATAGRAMS);
	IP_ADD_STATS(net, IPSTATS_MIB_OUTOCTETS, skb->len);

	अगर (unlikely(opt->optlen))
		ip_क्रमward_options(skb);

	वापस dst_output(net, sk, skb);
पूर्ण

#अगर_घोषित CONFIG_NET_SWITCHDEV
अटल bool ipmr_क्रमward_offloaded(काष्ठा sk_buff *skb, काष्ठा mr_table *mrt,
				   पूर्णांक in_vअगरi, पूर्णांक out_vअगरi)
अणु
	काष्ठा vअगर_device *out_vअगर = &mrt->vअगर_table[out_vअगरi];
	काष्ठा vअगर_device *in_vअगर = &mrt->vअगर_table[in_vअगरi];

	अगर (!skb->offload_l3_fwd_mark)
		वापस false;
	अगर (!out_vअगर->dev_parent_id.id_len || !in_vअगर->dev_parent_id.id_len)
		वापस false;
	वापस netdev_phys_item_id_same(&out_vअगर->dev_parent_id,
					&in_vअगर->dev_parent_id);
पूर्ण
#अन्यथा
अटल bool ipmr_क्रमward_offloaded(काष्ठा sk_buff *skb, काष्ठा mr_table *mrt,
				   पूर्णांक in_vअगरi, पूर्णांक out_vअगरi)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/* Processing handlers क्रम ipmr_क्रमward */

अटल व्योम ipmr_queue_xmit(काष्ठा net *net, काष्ठा mr_table *mrt,
			    पूर्णांक in_vअगरi, काष्ठा sk_buff *skb, पूर्णांक vअगरi)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा vअगर_device *vअगर = &mrt->vअगर_table[vअगरi];
	काष्ठा net_device *dev;
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4;
	पूर्णांक    encap = 0;

	अगर (!vअगर->dev)
		जाओ out_मुक्त;

	अगर (vअगर->flags & VIFF_REGISTER) अणु
		vअगर->pkt_out++;
		vअगर->bytes_out += skb->len;
		vअगर->dev->stats.tx_bytes += skb->len;
		vअगर->dev->stats.tx_packets++;
		ipmr_cache_report(mrt, skb, vअगरi, IGMPMSG_WHOLEPKT);
		जाओ out_मुक्त;
	पूर्ण

	अगर (ipmr_क्रमward_offloaded(skb, mrt, in_vअगरi, vअगरi))
		जाओ out_मुक्त;

	अगर (vअगर->flags & VIFF_TUNNEL) अणु
		rt = ip_route_output_ports(net, &fl4, शून्य,
					   vअगर->remote, vअगर->local,
					   0, 0,
					   IPPROTO_IPIP,
					   RT_TOS(iph->tos), vअगर->link);
		अगर (IS_ERR(rt))
			जाओ out_मुक्त;
		encap = माप(काष्ठा iphdr);
	पूर्ण अन्यथा अणु
		rt = ip_route_output_ports(net, &fl4, शून्य, iph->daddr, 0,
					   0, 0,
					   IPPROTO_IPIP,
					   RT_TOS(iph->tos), vअगर->link);
		अगर (IS_ERR(rt))
			जाओ out_मुक्त;
	पूर्ण

	dev = rt->dst.dev;

	अगर (skb->len+encap > dst_mtu(&rt->dst) && (ntohs(iph->frag_off) & IP_DF)) अणु
		/* Do not fragment multicasts. Alas, IPv4 करोes not
		 * allow to send ICMP, so that packets will disappear
		 * to blackhole.
		 */
		IP_INC_STATS(net, IPSTATS_MIB_FRAGFAILS);
		ip_rt_put(rt);
		जाओ out_मुक्त;
	पूर्ण

	encap += LL_RESERVED_SPACE(dev) + rt->dst.header_len;

	अगर (skb_cow(skb, encap)) अणु
		ip_rt_put(rt);
		जाओ out_मुक्त;
	पूर्ण

	vअगर->pkt_out++;
	vअगर->bytes_out += skb->len;

	skb_dst_drop(skb);
	skb_dst_set(skb, &rt->dst);
	ip_decrease_ttl(ip_hdr(skb));

	/* FIXME: क्रमward and output firewalls used to be called here.
	 * What करो we करो with netfilter? -- RR
	 */
	अगर (vअगर->flags & VIFF_TUNNEL) अणु
		ip_encap(net, skb, vअगर->local, vअगर->remote);
		/* FIXME: extra output firewall step used to be here. --RR */
		vअगर->dev->stats.tx_packets++;
		vअगर->dev->stats.tx_bytes += skb->len;
	पूर्ण

	IPCB(skb)->flags |= IPSKB_FORWARDED;

	/* RFC1584 teaches, that DVMRP/PIM router must deliver packets locally
	 * not only beक्रमe क्रमwarding, but after क्रमwarding on all output
	 * पूर्णांकerfaces. It is clear, अगर mrouter runs a multicasting
	 * program, it should receive packets not depending to what पूर्णांकerface
	 * program is joined.
	 * If we will not make it, the program will have to join on all
	 * पूर्णांकerfaces. On the other hand, multihoming host (or router, but
	 * not mrouter) cannot join to more than one पूर्णांकerface - it will
	 * result in receiving multiple packets.
	 */
	NF_HOOK(NFPROTO_IPV4, NF_INET_FORWARD,
		net, शून्य, skb, skb->dev, dev,
		ipmr_क्रमward_finish);
	वापस;

out_मुक्त:
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक ipmr_find_vअगर(काष्ठा mr_table *mrt, काष्ठा net_device *dev)
अणु
	पूर्णांक ct;

	क्रम (ct = mrt->maxvअगर-1; ct >= 0; ct--) अणु
		अगर (mrt->vअगर_table[ct].dev == dev)
			अवरोध;
	पूर्ण
	वापस ct;
पूर्ण

/* "local" means that we should preserve one skb (क्रम local delivery) */
अटल व्योम ip_mr_क्रमward(काष्ठा net *net, काष्ठा mr_table *mrt,
			  काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			  काष्ठा mfc_cache *c, पूर्णांक local)
अणु
	पूर्णांक true_vअगरi = ipmr_find_vअगर(mrt, dev);
	पूर्णांक psend = -1;
	पूर्णांक vअगर, ct;

	vअगर = c->_c.mfc_parent;
	c->_c.mfc_un.res.pkt++;
	c->_c.mfc_un.res.bytes += skb->len;
	c->_c.mfc_un.res.lastuse = jअगरfies;

	अगर (c->mfc_origin == htonl(INADDR_ANY) && true_vअगरi >= 0) अणु
		काष्ठा mfc_cache *cache_proxy;

		/* For an (*,G) entry, we only check that the incomming
		 * पूर्णांकerface is part of the अटल tree.
		 */
		cache_proxy = mr_mfc_find_any_parent(mrt, vअगर);
		अगर (cache_proxy &&
		    cache_proxy->_c.mfc_un.res.ttls[true_vअगरi] < 255)
			जाओ क्रमward;
	पूर्ण

	/* Wrong पूर्णांकerface: drop packet and (maybe) send PIM निश्चित. */
	अगर (mrt->vअगर_table[vअगर].dev != dev) अणु
		अगर (rt_is_output_route(skb_rtable(skb))) अणु
			/* It is our own packet, looped back.
			 * Very complicated situation...
			 *
			 * The best workaround until routing daemons will be
			 * fixed is not to redistribute packet, अगर it was
			 * send through wrong पूर्णांकerface. It means, that
			 * multicast applications WILL NOT work क्रम
			 * (S,G), which have शेष multicast route poपूर्णांकing
			 * to wrong oअगर. In any हाल, it is not a good
			 * idea to use multicasting applications on router.
			 */
			जाओ करोnt_क्रमward;
		पूर्ण

		c->_c.mfc_un.res.wrong_अगर++;

		अगर (true_vअगरi >= 0 && mrt->mroute_करो_निश्चित &&
		    /* pimsm uses निश्चितs, when चयनing from RPT to SPT,
		     * so that we cannot check that packet arrived on an oअगर.
		     * It is bad, but otherwise we would need to move pretty
		     * large chunk of pimd to kernel. Ough... --ANK
		     */
		    (mrt->mroute_करो_pim ||
		     c->_c.mfc_un.res.ttls[true_vअगरi] < 255) &&
		    समय_after(jअगरfies,
			       c->_c.mfc_un.res.last_निश्चित +
			       MFC_ASSERT_THRESH)) अणु
			c->_c.mfc_un.res.last_निश्चित = jअगरfies;
			ipmr_cache_report(mrt, skb, true_vअगरi, IGMPMSG_WRONGVIF);
			अगर (mrt->mroute_करो_wrvअगरwhole)
				ipmr_cache_report(mrt, skb, true_vअगरi,
						  IGMPMSG_WRVIFWHOLE);
		पूर्ण
		जाओ करोnt_क्रमward;
	पूर्ण

क्रमward:
	mrt->vअगर_table[vअगर].pkt_in++;
	mrt->vअगर_table[vअगर].bytes_in += skb->len;

	/* Forward the frame */
	अगर (c->mfc_origin == htonl(INADDR_ANY) &&
	    c->mfc_mcastgrp == htonl(INADDR_ANY)) अणु
		अगर (true_vअगरi >= 0 &&
		    true_vअगरi != c->_c.mfc_parent &&
		    ip_hdr(skb)->ttl >
				c->_c.mfc_un.res.ttls[c->_c.mfc_parent]) अणु
			/* It's an (*,*) entry and the packet is not coming from
			 * the upstream: क्रमward the packet to the upstream
			 * only.
			 */
			psend = c->_c.mfc_parent;
			जाओ last_क्रमward;
		पूर्ण
		जाओ करोnt_क्रमward;
	पूर्ण
	क्रम (ct = c->_c.mfc_un.res.maxvअगर - 1;
	     ct >= c->_c.mfc_un.res.minvअगर; ct--) अणु
		/* For (*,G) entry, करोn't क्रमward to the incoming पूर्णांकerface */
		अगर ((c->mfc_origin != htonl(INADDR_ANY) ||
		     ct != true_vअगरi) &&
		    ip_hdr(skb)->ttl > c->_c.mfc_un.res.ttls[ct]) अणु
			अगर (psend != -1) अणु
				काष्ठा sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);

				अगर (skb2)
					ipmr_queue_xmit(net, mrt, true_vअगरi,
							skb2, psend);
			पूर्ण
			psend = ct;
		पूर्ण
	पूर्ण
last_क्रमward:
	अगर (psend != -1) अणु
		अगर (local) अणु
			काष्ठा sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);

			अगर (skb2)
				ipmr_queue_xmit(net, mrt, true_vअगरi, skb2,
						psend);
		पूर्ण अन्यथा अणु
			ipmr_queue_xmit(net, mrt, true_vअगरi, skb, psend);
			वापस;
		पूर्ण
	पूर्ण

करोnt_क्रमward:
	अगर (!local)
		kमुक्त_skb(skb);
पूर्ण

अटल काष्ठा mr_table *ipmr_rt_fib_lookup(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtable *rt = skb_rtable(skb);
	काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा flowi4 fl4 = अणु
		.daddr = iph->daddr,
		.saddr = iph->saddr,
		.flowi4_tos = RT_TOS(iph->tos),
		.flowi4_oअगर = (rt_is_output_route(rt) ?
			       skb->dev->अगरindex : 0),
		.flowi4_iअगर = (rt_is_output_route(rt) ?
			       LOOPBACK_IFINDEX :
			       skb->dev->अगरindex),
		.flowi4_mark = skb->mark,
	पूर्ण;
	काष्ठा mr_table *mrt;
	पूर्णांक err;

	err = ipmr_fib_lookup(net, &fl4, &mrt);
	अगर (err)
		वापस ERR_PTR(err);
	वापस mrt;
पूर्ण

/* Multicast packets क्रम क्रमwarding arrive here
 * Called with rcu_पढ़ो_lock();
 */
पूर्णांक ip_mr_input(काष्ठा sk_buff *skb)
अणु
	काष्ठा mfc_cache *cache;
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक local = skb_rtable(skb)->rt_flags & RTCF_LOCAL;
	काष्ठा mr_table *mrt;
	काष्ठा net_device *dev;

	/* skb->dev passed in is the loX master dev क्रम vrfs.
	 * As there are no vअगरs associated with loopback devices,
	 * get the proper पूर्णांकerface that करोes have a vअगर associated with it.
	 */
	dev = skb->dev;
	अगर (netअगर_is_l3_master(skb->dev)) अणु
		dev = dev_get_by_index_rcu(net, IPCB(skb)->iअगर);
		अगर (!dev) अणु
			kमुक्त_skb(skb);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Packet is looped back after क्रमward, it should not be
	 * क्रमwarded second समय, but still can be delivered locally.
	 */
	अगर (IPCB(skb)->flags & IPSKB_FORWARDED)
		जाओ करोnt_क्रमward;

	mrt = ipmr_rt_fib_lookup(net, skb);
	अगर (IS_ERR(mrt)) अणु
		kमुक्त_skb(skb);
		वापस PTR_ERR(mrt);
	पूर्ण
	अगर (!local) अणु
		अगर (IPCB(skb)->opt.router_alert) अणु
			अगर (ip_call_ra_chain(skb))
				वापस 0;
		पूर्ण अन्यथा अगर (ip_hdr(skb)->protocol == IPPROTO_IGMP) अणु
			/* IGMPv1 (and broken IGMPv2 implementations sort of
			 * Cisco IOS <= 11.2(8)) करो not put router alert
			 * option to IGMP packets destined to routable
			 * groups. It is very bad, because it means
			 * that we can क्रमward NO IGMP messages.
			 */
			काष्ठा sock *mroute_sk;

			mroute_sk = rcu_dereference(mrt->mroute_sk);
			अगर (mroute_sk) अणु
				nf_reset_ct(skb);
				raw_rcv(mroute_sk, skb);
				वापस 0;
			पूर्ण
		    पूर्ण
	पूर्ण

	/* alपढ़ोy under rcu_पढ़ो_lock() */
	cache = ipmr_cache_find(mrt, ip_hdr(skb)->saddr, ip_hdr(skb)->daddr);
	अगर (!cache) अणु
		पूर्णांक vअगर = ipmr_find_vअगर(mrt, dev);

		अगर (vअगर >= 0)
			cache = ipmr_cache_find_any(mrt, ip_hdr(skb)->daddr,
						    vअगर);
	पूर्ण

	/* No usable cache entry */
	अगर (!cache) अणु
		पूर्णांक vअगर;

		अगर (local) अणु
			काष्ठा sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
			ip_local_deliver(skb);
			अगर (!skb2)
				वापस -ENOBUFS;
			skb = skb2;
		पूर्ण

		पढ़ो_lock(&mrt_lock);
		vअगर = ipmr_find_vअगर(mrt, dev);
		अगर (vअगर >= 0) अणु
			पूर्णांक err2 = ipmr_cache_unresolved(mrt, vअगर, skb, dev);
			पढ़ो_unlock(&mrt_lock);

			वापस err2;
		पूर्ण
		पढ़ो_unlock(&mrt_lock);
		kमुक्त_skb(skb);
		वापस -ENODEV;
	पूर्ण

	पढ़ो_lock(&mrt_lock);
	ip_mr_क्रमward(net, mrt, dev, skb, cache, local);
	पढ़ो_unlock(&mrt_lock);

	अगर (local)
		वापस ip_local_deliver(skb);

	वापस 0;

करोnt_क्रमward:
	अगर (local)
		वापस ip_local_deliver(skb);
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IP_PIMSM_V1
/* Handle IGMP messages of PIMv1 */
पूर्णांक pim_rcv_v1(काष्ठा sk_buff *skb)
अणु
	काष्ठा igmphdr *pim;
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा mr_table *mrt;

	अगर (!pskb_may_pull(skb, माप(*pim) + माप(काष्ठा iphdr)))
		जाओ drop;

	pim = igmp_hdr(skb);

	mrt = ipmr_rt_fib_lookup(net, skb);
	अगर (IS_ERR(mrt))
		जाओ drop;
	अगर (!mrt->mroute_करो_pim ||
	    pim->group != PIM_V1_VERSION || pim->code != PIM_V1_REGISTER)
		जाओ drop;

	अगर (__pim_rcv(mrt, skb, माप(*pim))) अणु
drop:
		kमुक्त_skb(skb);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_PIMSM_V2
अटल पूर्णांक pim_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा pimreghdr *pim;
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा mr_table *mrt;

	अगर (!pskb_may_pull(skb, माप(*pim) + माप(काष्ठा iphdr)))
		जाओ drop;

	pim = (काष्ठा pimreghdr *)skb_transport_header(skb);
	अगर (pim->type != ((PIM_VERSION << 4) | (PIM_TYPE_REGISTER)) ||
	    (pim->flags & PIM_शून्य_REGISTER) ||
	    (ip_compute_csum((व्योम *)pim, माप(*pim)) != 0 &&
	     csum_fold(skb_checksum(skb, 0, skb->len, 0))))
		जाओ drop;

	mrt = ipmr_rt_fib_lookup(net, skb);
	अगर (IS_ERR(mrt))
		जाओ drop;
	अगर (__pim_rcv(mrt, skb, माप(*pim))) अणु
drop:
		kमुक्त_skb(skb);
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक ipmr_get_route(काष्ठा net *net, काष्ठा sk_buff *skb,
		   __be32 saddr, __be32 daddr,
		   काष्ठा rपंचांगsg *rपंचांग, u32 portid)
अणु
	काष्ठा mfc_cache *cache;
	काष्ठा mr_table *mrt;
	पूर्णांक err;

	mrt = ipmr_get_table(net, RT_TABLE_DEFAULT);
	अगर (!mrt)
		वापस -ENOENT;

	rcu_पढ़ो_lock();
	cache = ipmr_cache_find(mrt, saddr, daddr);
	अगर (!cache && skb->dev) अणु
		पूर्णांक vअगर = ipmr_find_vअगर(mrt, skb->dev);

		अगर (vअगर >= 0)
			cache = ipmr_cache_find_any(mrt, daddr, vअगर);
	पूर्ण
	अगर (!cache) अणु
		काष्ठा sk_buff *skb2;
		काष्ठा iphdr *iph;
		काष्ठा net_device *dev;
		पूर्णांक vअगर = -1;

		dev = skb->dev;
		पढ़ो_lock(&mrt_lock);
		अगर (dev)
			vअगर = ipmr_find_vअगर(mrt, dev);
		अगर (vअगर < 0) अणु
			पढ़ो_unlock(&mrt_lock);
			rcu_पढ़ो_unlock();
			वापस -ENODEV;
		पूर्ण

		skb2 = skb_पुनः_स्मृति_headroom(skb, माप(काष्ठा iphdr));
		अगर (!skb2) अणु
			पढ़ो_unlock(&mrt_lock);
			rcu_पढ़ो_unlock();
			वापस -ENOMEM;
		पूर्ण

		NETLINK_CB(skb2).portid = portid;
		skb_push(skb2, माप(काष्ठा iphdr));
		skb_reset_network_header(skb2);
		iph = ip_hdr(skb2);
		iph->ihl = माप(काष्ठा iphdr) >> 2;
		iph->saddr = saddr;
		iph->daddr = daddr;
		iph->version = 0;
		err = ipmr_cache_unresolved(mrt, vअगर, skb2, dev);
		पढ़ो_unlock(&mrt_lock);
		rcu_पढ़ो_unlock();
		वापस err;
	पूर्ण

	पढ़ो_lock(&mrt_lock);
	err = mr_fill_mroute(mrt, skb, &cache->_c, rपंचांग);
	पढ़ो_unlock(&mrt_lock);
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक ipmr_fill_mroute(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
			    u32 portid, u32 seq, काष्ठा mfc_cache *c, पूर्णांक cmd,
			    पूर्णांक flags)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा rपंचांगsg *rपंचांग;
	पूर्णांक err;

	nlh = nlmsg_put(skb, portid, seq, cmd, माप(*rपंचांग), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	rपंचांग = nlmsg_data(nlh);
	rपंचांग->rपंचांग_family   = RTNL_FAMILY_IPMR;
	rपंचांग->rपंचांग_dst_len  = 32;
	rपंचांग->rपंचांग_src_len  = 32;
	rपंचांग->rपंचांग_tos      = 0;
	rपंचांग->rपंचांग_table    = mrt->id;
	अगर (nla_put_u32(skb, RTA_TABLE, mrt->id))
		जाओ nla_put_failure;
	rपंचांग->rपंचांग_type     = RTN_MULTICAST;
	rपंचांग->rपंचांग_scope    = RT_SCOPE_UNIVERSE;
	अगर (c->_c.mfc_flags & MFC_STATIC)
		rपंचांग->rपंचांग_protocol = RTPROT_STATIC;
	अन्यथा
		rपंचांग->rपंचांग_protocol = RTPROT_MROUTED;
	rपंचांग->rपंचांग_flags    = 0;

	अगर (nla_put_in_addr(skb, RTA_SRC, c->mfc_origin) ||
	    nla_put_in_addr(skb, RTA_DST, c->mfc_mcastgrp))
		जाओ nla_put_failure;
	err = mr_fill_mroute(mrt, skb, &c->_c, rपंचांग);
	/* करो not अवरोध the dump अगर cache is unresolved */
	अगर (err < 0 && err != -ENOENT)
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक _ipmr_fill_mroute(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
			     u32 portid, u32 seq, काष्ठा mr_mfc *c, पूर्णांक cmd,
			     पूर्णांक flags)
अणु
	वापस ipmr_fill_mroute(mrt, skb, portid, seq, (काष्ठा mfc_cache *)c,
				cmd, flags);
पूर्ण

अटल माप_प्रकार mroute_msgsize(bool unresolved, पूर्णांक maxvअगर)
अणु
	माप_प्रकार len =
		NLMSG_ALIGN(माप(काष्ठा rपंचांगsg))
		+ nla_total_size(4)	/* RTA_TABLE */
		+ nla_total_size(4)	/* RTA_SRC */
		+ nla_total_size(4)	/* RTA_DST */
		;

	अगर (!unresolved)
		len = len
		      + nla_total_size(4)	/* RTA_IIF */
		      + nla_total_size(0)	/* RTA_MULTIPATH */
		      + maxvअगर * NLA_ALIGN(माप(काष्ठा rtnexthop))
						/* RTA_MFC_STATS */
		      + nla_total_size_64bit(माप(काष्ठा rta_mfc_stats))
		;

	वापस len;
पूर्ण

अटल व्योम mroute_netlink_event(काष्ठा mr_table *mrt, काष्ठा mfc_cache *mfc,
				 पूर्णांक cmd)
अणु
	काष्ठा net *net = पढ़ो_pnet(&mrt->net);
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(mroute_msgsize(mfc->_c.mfc_parent >= MAXVIFS,
				       mrt->maxvअगर),
			GFP_ATOMIC);
	अगर (!skb)
		जाओ errout;

	err = ipmr_fill_mroute(mrt, skb, 0, 0, mfc, cmd, 0);
	अगर (err < 0)
		जाओ errout;

	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV4_MROUTE, शून्य, GFP_ATOMIC);
	वापस;

errout:
	kमुक्त_skb(skb);
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV4_MROUTE, err);
पूर्ण

अटल माप_प्रकार igmpmsg_netlink_msgsize(माप_प्रकार payloadlen)
अणु
	माप_प्रकार len =
		NLMSG_ALIGN(माप(काष्ठा rtgenmsg))
		+ nla_total_size(1)	/* IPMRA_CREPORT_MSGTYPE */
		+ nla_total_size(4)	/* IPMRA_CREPORT_VIF_ID */
		+ nla_total_size(4)	/* IPMRA_CREPORT_SRC_ADDR */
		+ nla_total_size(4)	/* IPMRA_CREPORT_DST_ADDR */
		+ nla_total_size(4)	/* IPMRA_CREPORT_TABLE */
					/* IPMRA_CREPORT_PKT */
		+ nla_total_size(payloadlen)
		;

	वापस len;
पूर्ण

अटल व्योम igmpmsg_netlink_event(काष्ठा mr_table *mrt, काष्ठा sk_buff *pkt)
अणु
	काष्ठा net *net = पढ़ो_pnet(&mrt->net);
	काष्ठा nlmsghdr *nlh;
	काष्ठा rtgenmsg *rtgenm;
	काष्ठा igmpmsg *msg;
	काष्ठा sk_buff *skb;
	काष्ठा nlattr *nla;
	पूर्णांक payloadlen;

	payloadlen = pkt->len - माप(काष्ठा igmpmsg);
	msg = (काष्ठा igmpmsg *)skb_network_header(pkt);

	skb = nlmsg_new(igmpmsg_netlink_msgsize(payloadlen), GFP_ATOMIC);
	अगर (!skb)
		जाओ errout;

	nlh = nlmsg_put(skb, 0, 0, RTM_NEWCACHEREPORT,
			माप(काष्ठा rtgenmsg), 0);
	अगर (!nlh)
		जाओ errout;
	rtgenm = nlmsg_data(nlh);
	rtgenm->rtgen_family = RTNL_FAMILY_IPMR;
	अगर (nla_put_u8(skb, IPMRA_CREPORT_MSGTYPE, msg->im_msgtype) ||
	    nla_put_u32(skb, IPMRA_CREPORT_VIF_ID, msg->im_vअगर | (msg->im_vअगर_hi << 8)) ||
	    nla_put_in_addr(skb, IPMRA_CREPORT_SRC_ADDR,
			    msg->im_src.s_addr) ||
	    nla_put_in_addr(skb, IPMRA_CREPORT_DST_ADDR,
			    msg->im_dst.s_addr) ||
	    nla_put_u32(skb, IPMRA_CREPORT_TABLE, mrt->id))
		जाओ nla_put_failure;

	nla = nla_reserve(skb, IPMRA_CREPORT_PKT, payloadlen);
	अगर (!nla || skb_copy_bits(pkt, माप(काष्ठा igmpmsg),
				  nla_data(nla), payloadlen))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);

	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV4_MROUTE_R, शून्य, GFP_ATOMIC);
	वापस;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
errout:
	kमुक्त_skb(skb);
	rtnl_set_sk_err(net, RTNLGRP_IPV4_MROUTE_R, -ENOBUFS);
पूर्ण

अटल पूर्णांक ipmr_rपंचांग_valid_getroute_req(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा nlmsghdr *nlh,
				       काष्ठा nlattr **tb,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा rपंचांगsg *rपंचांग;
	पूर्णांक i, err;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*rपंचांग))) अणु
		NL_SET_ERR_MSG(extack, "ipv4: Invalid header for multicast route get request");
		वापस -EINVAL;
	पूर्ण

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(*rपंचांग), tb, RTA_MAX,
					      rपंचांग_ipv4_policy, extack);

	rपंचांग = nlmsg_data(nlh);
	अगर ((rपंचांग->rपंचांग_src_len && rपंचांग->rपंचांग_src_len != 32) ||
	    (rपंचांग->rपंचांग_dst_len && rपंचांग->rपंचांग_dst_len != 32) ||
	    rपंचांग->rपंचांग_tos || rपंचांग->rपंचांग_table || rपंचांग->rपंचांग_protocol ||
	    rपंचांग->rपंचांग_scope || rपंचांग->rपंचांग_type || rपंचांग->rपंचांग_flags) अणु
		NL_SET_ERR_MSG(extack, "ipv4: Invalid values in header for multicast route get request");
		वापस -EINVAL;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(*rपंचांग), tb, RTA_MAX,
					    rपंचांग_ipv4_policy, extack);
	अगर (err)
		वापस err;

	अगर ((tb[RTA_SRC] && !rपंचांग->rपंचांग_src_len) ||
	    (tb[RTA_DST] && !rपंचांग->rपंचांग_dst_len)) अणु
		NL_SET_ERR_MSG(extack, "ipv4: rtm_src_len and rtm_dst_len must be 32 for IPv4");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i <= RTA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल RTA_SRC:
		हाल RTA_DST:
		हाल RTA_TABLE:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "ipv4: Unsupported attribute in multicast route get request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipmr_rपंचांग_getroute(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा nlattr *tb[RTA_MAX + 1];
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा mfc_cache *cache;
	काष्ठा mr_table *mrt;
	__be32 src, grp;
	u32 tableid;
	पूर्णांक err;

	err = ipmr_rपंचांग_valid_getroute_req(in_skb, nlh, tb, extack);
	अगर (err < 0)
		जाओ errout;

	src = tb[RTA_SRC] ? nla_get_in_addr(tb[RTA_SRC]) : 0;
	grp = tb[RTA_DST] ? nla_get_in_addr(tb[RTA_DST]) : 0;
	tableid = tb[RTA_TABLE] ? nla_get_u32(tb[RTA_TABLE]) : 0;

	mrt = ipmr_get_table(net, tableid ? tableid : RT_TABLE_DEFAULT);
	अगर (!mrt) अणु
		err = -ENOENT;
		जाओ errout_मुक्त;
	पूर्ण

	/* entries are added/deleted only under RTNL */
	rcu_पढ़ो_lock();
	cache = ipmr_cache_find(mrt, src, grp);
	rcu_पढ़ो_unlock();
	अगर (!cache) अणु
		err = -ENOENT;
		जाओ errout_मुक्त;
	पूर्ण

	skb = nlmsg_new(mroute_msgsize(false, mrt->maxvअगर), GFP_KERNEL);
	अगर (!skb) अणु
		err = -ENOBUFS;
		जाओ errout_मुक्त;
	पूर्ण

	err = ipmr_fill_mroute(mrt, skb, NETLINK_CB(in_skb).portid,
			       nlh->nlmsg_seq, cache,
			       RTM_NEWROUTE, 0);
	अगर (err < 0)
		जाओ errout_मुक्त;

	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);

errout:
	वापस err;

errout_मुक्त:
	kमुक्त_skb(skb);
	जाओ errout;
पूर्ण

अटल पूर्णांक ipmr_rपंचांग_dumproute(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा fib_dump_filter filter = अणुपूर्ण;
	पूर्णांक err;

	अगर (cb->strict_check) अणु
		err = ip_valid_fib_dump_req(sock_net(skb->sk), cb->nlh,
					    &filter, cb);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (filter.table_id) अणु
		काष्ठा mr_table *mrt;

		mrt = ipmr_get_table(sock_net(skb->sk), filter.table_id);
		अगर (!mrt) अणु
			अगर (rtnl_msg_family(cb->nlh) != RTNL_FAMILY_IPMR)
				वापस skb->len;

			NL_SET_ERR_MSG(cb->extack, "ipv4: MR table does not exist");
			वापस -ENOENT;
		पूर्ण
		err = mr_table_dump(mrt, skb, cb, _ipmr_fill_mroute,
				    &mfc_unres_lock, &filter);
		वापस skb->len ? : err;
	पूर्ण

	वापस mr_rपंचांग_dumproute(skb, cb, ipmr_mr_table_iter,
				_ipmr_fill_mroute, &mfc_unres_lock, &filter);
पूर्ण

अटल स्थिर काष्ठा nla_policy rपंचांग_ipmr_policy[RTA_MAX + 1] = अणु
	[RTA_SRC]	= अणु .type = NLA_U32 पूर्ण,
	[RTA_DST]	= अणु .type = NLA_U32 पूर्ण,
	[RTA_IIF]	= अणु .type = NLA_U32 पूर्ण,
	[RTA_TABLE]	= अणु .type = NLA_U32 पूर्ण,
	[RTA_MULTIPATH]	= अणु .len = माप(काष्ठा rtnexthop) पूर्ण,
पूर्ण;

अटल bool ipmr_rपंचांग_validate_proto(अचिन्हित अक्षर rपंचांग_protocol)
अणु
	चयन (rपंचांग_protocol) अणु
	हाल RTPROT_STATIC:
	हाल RTPROT_MROUTED:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक ipmr_nla_get_ttls(स्थिर काष्ठा nlattr *nla, काष्ठा mfcctl *mfcc)
अणु
	काष्ठा rtnexthop *rtnh = nla_data(nla);
	पूर्णांक reमुख्यing = nla_len(nla), vअगरi = 0;

	जबतक (rtnh_ok(rtnh, reमुख्यing)) अणु
		mfcc->mfcc_ttls[vअगरi] = rtnh->rtnh_hops;
		अगर (++vअगरi == MAXVIFS)
			अवरोध;
		rtnh = rtnh_next(rtnh, &reमुख्यing);
	पूर्ण

	वापस reमुख्यing > 0 ? -EINVAL : vअगरi;
पूर्ण

/* वापसs < 0 on error, 0 क्रम ADD_MFC and 1 क्रम ADD_MFC_PROXY */
अटल पूर्णांक rपंचांग_to_ipmr_mfcc(काष्ठा net *net, काष्ठा nlmsghdr *nlh,
			    काष्ठा mfcctl *mfcc, पूर्णांक *mrtsock,
			    काष्ठा mr_table **mrtret,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev = शून्य;
	u32 tblid = RT_TABLE_DEFAULT;
	काष्ठा mr_table *mrt;
	काष्ठा nlattr *attr;
	काष्ठा rपंचांगsg *rपंचांग;
	पूर्णांक ret, rem;

	ret = nlmsg_validate_deprecated(nlh, माप(*rपंचांग), RTA_MAX,
					rपंचांग_ipmr_policy, extack);
	अगर (ret < 0)
		जाओ out;
	rपंचांग = nlmsg_data(nlh);

	ret = -EINVAL;
	अगर (rपंचांग->rपंचांग_family != RTNL_FAMILY_IPMR || rपंचांग->rपंचांग_dst_len != 32 ||
	    rपंचांग->rपंचांग_type != RTN_MULTICAST ||
	    rपंचांग->rपंचांग_scope != RT_SCOPE_UNIVERSE ||
	    !ipmr_rपंचांग_validate_proto(rपंचांग->rपंचांग_protocol))
		जाओ out;

	स_रखो(mfcc, 0, माप(*mfcc));
	mfcc->mfcc_parent = -1;
	ret = 0;
	nlmsg_क्रम_each_attr(attr, nlh, माप(काष्ठा rपंचांगsg), rem) अणु
		चयन (nla_type(attr)) अणु
		हाल RTA_SRC:
			mfcc->mfcc_origin.s_addr = nla_get_be32(attr);
			अवरोध;
		हाल RTA_DST:
			mfcc->mfcc_mcastgrp.s_addr = nla_get_be32(attr);
			अवरोध;
		हाल RTA_IIF:
			dev = __dev_get_by_index(net, nla_get_u32(attr));
			अगर (!dev) अणु
				ret = -ENODEV;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल RTA_MULTIPATH:
			अगर (ipmr_nla_get_ttls(attr, mfcc) < 0) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल RTA_PREFSRC:
			ret = 1;
			अवरोध;
		हाल RTA_TABLE:
			tblid = nla_get_u32(attr);
			अवरोध;
		पूर्ण
	पूर्ण
	mrt = ipmr_get_table(net, tblid);
	अगर (!mrt) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	*mrtret = mrt;
	*mrtsock = rपंचांग->rपंचांग_protocol == RTPROT_MROUTED ? 1 : 0;
	अगर (dev)
		mfcc->mfcc_parent = ipmr_find_vअगर(mrt, dev);

out:
	वापस ret;
पूर्ण

/* takes care of both newroute and delroute */
अटल पूर्णांक ipmr_rपंचांग_route(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक ret, mrtsock, parent;
	काष्ठा mr_table *tbl;
	काष्ठा mfcctl mfcc;

	mrtsock = 0;
	tbl = शून्य;
	ret = rपंचांग_to_ipmr_mfcc(net, nlh, &mfcc, &mrtsock, &tbl, extack);
	अगर (ret < 0)
		वापस ret;

	parent = ret ? mfcc.mfcc_parent : -1;
	अगर (nlh->nlmsg_type == RTM_NEWROUTE)
		वापस ipmr_mfc_add(net, tbl, &mfcc, mrtsock, parent);
	अन्यथा
		वापस ipmr_mfc_delete(tbl, &mfcc, parent);
पूर्ण

अटल bool ipmr_fill_table(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb)
अणु
	u32 queue_len = atomic_पढ़ो(&mrt->cache_resolve_queue_len);

	अगर (nla_put_u32(skb, IPMRA_TABLE_ID, mrt->id) ||
	    nla_put_u32(skb, IPMRA_TABLE_CACHE_RES_QUEUE_LEN, queue_len) ||
	    nla_put_s32(skb, IPMRA_TABLE_MROUTE_REG_VIF_NUM,
			mrt->mroute_reg_vअगर_num) ||
	    nla_put_u8(skb, IPMRA_TABLE_MROUTE_DO_ASSERT,
		       mrt->mroute_करो_निश्चित) ||
	    nla_put_u8(skb, IPMRA_TABLE_MROUTE_DO_PIM, mrt->mroute_करो_pim) ||
	    nla_put_u8(skb, IPMRA_TABLE_MROUTE_DO_WRVIFWHOLE,
		       mrt->mroute_करो_wrvअगरwhole))
		वापस false;

	वापस true;
पूर्ण

अटल bool ipmr_fill_vअगर(काष्ठा mr_table *mrt, u32 vअगरid, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *vअगर_nest;
	काष्ठा vअगर_device *vअगर;

	/* अगर the VIF करोesn't exist just जारी */
	अगर (!VIF_EXISTS(mrt, vअगरid))
		वापस true;

	vअगर = &mrt->vअगर_table[vअगरid];
	vअगर_nest = nla_nest_start_noflag(skb, IPMRA_VIF);
	अगर (!vअगर_nest)
		वापस false;
	अगर (nla_put_u32(skb, IPMRA_VIFA_IFINDEX, vअगर->dev->अगरindex) ||
	    nla_put_u32(skb, IPMRA_VIFA_VIF_ID, vअगरid) ||
	    nla_put_u16(skb, IPMRA_VIFA_FLAGS, vअगर->flags) ||
	    nla_put_u64_64bit(skb, IPMRA_VIFA_BYTES_IN, vअगर->bytes_in,
			      IPMRA_VIFA_PAD) ||
	    nla_put_u64_64bit(skb, IPMRA_VIFA_BYTES_OUT, vअगर->bytes_out,
			      IPMRA_VIFA_PAD) ||
	    nla_put_u64_64bit(skb, IPMRA_VIFA_PACKETS_IN, vअगर->pkt_in,
			      IPMRA_VIFA_PAD) ||
	    nla_put_u64_64bit(skb, IPMRA_VIFA_PACKETS_OUT, vअगर->pkt_out,
			      IPMRA_VIFA_PAD) ||
	    nla_put_be32(skb, IPMRA_VIFA_LOCAL_ADDR, vअगर->local) ||
	    nla_put_be32(skb, IPMRA_VIFA_REMOTE_ADDR, vअगर->remote)) अणु
		nla_nest_cancel(skb, vअगर_nest);
		वापस false;
	पूर्ण
	nla_nest_end(skb, vअगर_nest);

	वापस true;
पूर्ण

अटल पूर्णांक ipmr_valid_dumplink(स्थिर काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा अगरinfomsg *अगरm;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरm))) अणु
		NL_SET_ERR_MSG(extack, "ipv4: Invalid header for ipmr link dump");
		वापस -EINVAL;
	पूर्ण

	अगर (nlmsg_attrlen(nlh, माप(*अगरm))) अणु
		NL_SET_ERR_MSG(extack, "Invalid data after header in ipmr link dump");
		वापस -EINVAL;
	पूर्ण

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->__अगरi_pad || अगरm->अगरi_type || अगरm->अगरi_flags ||
	    अगरm->अगरi_change || अगरm->अगरi_index) अणु
		NL_SET_ERR_MSG(extack, "Invalid values in header for ipmr link dump request");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ipmr_rपंचांग_dumplink(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlmsghdr *nlh = शून्य;
	अचिन्हित पूर्णांक t = 0, s_t;
	अचिन्हित पूर्णांक e = 0, s_e;
	काष्ठा mr_table *mrt;

	अगर (cb->strict_check) अणु
		पूर्णांक err = ipmr_valid_dumplink(cb->nlh, cb->extack);

		अगर (err < 0)
			वापस err;
	पूर्ण

	s_t = cb->args[0];
	s_e = cb->args[1];

	ipmr_क्रम_each_table(mrt, net) अणु
		काष्ठा nlattr *vअगरs, *af;
		काष्ठा अगरinfomsg *hdr;
		u32 i;

		अगर (t < s_t)
			जाओ skip_table;
		nlh = nlmsg_put(skb, NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, RTM_NEWLINK,
				माप(*hdr), NLM_F_MULTI);
		अगर (!nlh)
			अवरोध;

		hdr = nlmsg_data(nlh);
		स_रखो(hdr, 0, माप(*hdr));
		hdr->अगरi_family = RTNL_FAMILY_IPMR;

		af = nla_nest_start_noflag(skb, IFLA_AF_SPEC);
		अगर (!af) अणु
			nlmsg_cancel(skb, nlh);
			जाओ out;
		पूर्ण

		अगर (!ipmr_fill_table(mrt, skb)) अणु
			nlmsg_cancel(skb, nlh);
			जाओ out;
		पूर्ण

		vअगरs = nla_nest_start_noflag(skb, IPMRA_TABLE_VIFS);
		अगर (!vअगरs) अणु
			nla_nest_end(skb, af);
			nlmsg_end(skb, nlh);
			जाओ out;
		पूर्ण
		क्रम (i = 0; i < mrt->maxvअगर; i++) अणु
			अगर (e < s_e)
				जाओ skip_entry;
			अगर (!ipmr_fill_vअगर(mrt, i, skb)) अणु
				nla_nest_end(skb, vअगरs);
				nla_nest_end(skb, af);
				nlmsg_end(skb, nlh);
				जाओ out;
			पूर्ण
skip_entry:
			e++;
		पूर्ण
		s_e = 0;
		e = 0;
		nla_nest_end(skb, vअगरs);
		nla_nest_end(skb, af);
		nlmsg_end(skb, nlh);
skip_table:
		t++;
	पूर्ण

out:
	cb->args[1] = e;
	cb->args[0] = t;

	वापस skb->len;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/* The /proc पूर्णांकerfaces to multicast routing :
 * /proc/net/ip_mr_cache & /proc/net/ip_mr_vअगर
 */

अटल व्योम *ipmr_vअगर_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(mrt_lock)
अणु
	काष्ठा mr_vअगर_iter *iter = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा mr_table *mrt;

	mrt = ipmr_get_table(net, RT_TABLE_DEFAULT);
	अगर (!mrt)
		वापस ERR_PTR(-ENOENT);

	iter->mrt = mrt;

	पढ़ो_lock(&mrt_lock);
	वापस mr_vअगर_seq_start(seq, pos);
पूर्ण

अटल व्योम ipmr_vअगर_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(mrt_lock)
अणु
	पढ़ो_unlock(&mrt_lock);
पूर्ण

अटल पूर्णांक ipmr_vअगर_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा mr_vअगर_iter *iter = seq->निजी;
	काष्ठा mr_table *mrt = iter->mrt;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq,
			 "Interface      BytesIn  PktsIn  BytesOut PktsOut Flags Local    Remote\n");
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा vअगर_device *vअगर = v;
		स्थिर अक्षर *name =  vअगर->dev ?
				    vअगर->dev->name : "none";

		seq_म_लिखो(seq,
			   "%2td %-10s %8ld %7ld  %8ld %7ld %05X %08X %08X\n",
			   vअगर - mrt->vअगर_table,
			   name, vअगर->bytes_in, vअगर->pkt_in,
			   vअगर->bytes_out, vअगर->pkt_out,
			   vअगर->flags, vअगर->local, vअगर->remote);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ipmr_vअगर_seq_ops = अणु
	.start = ipmr_vअगर_seq_start,
	.next  = mr_vअगर_seq_next,
	.stop  = ipmr_vअगर_seq_stop,
	.show  = ipmr_vअगर_seq_show,
पूर्ण;

अटल व्योम *ipmr_mfc_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा mr_table *mrt;

	mrt = ipmr_get_table(net, RT_TABLE_DEFAULT);
	अगर (!mrt)
		वापस ERR_PTR(-ENOENT);

	वापस mr_mfc_seq_start(seq, pos, mrt, &mfc_unres_lock);
पूर्ण

अटल पूर्णांक ipmr_mfc_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक n;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq,
		 "Group    Origin   Iif     Pkts    Bytes    Wrong Oifs\n");
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा mfc_cache *mfc = v;
		स्थिर काष्ठा mr_mfc_iter *it = seq->निजी;
		स्थिर काष्ठा mr_table *mrt = it->mrt;

		seq_म_लिखो(seq, "%08X %08X %-3hd",
			   (__क्रमce u32) mfc->mfc_mcastgrp,
			   (__क्रमce u32) mfc->mfc_origin,
			   mfc->_c.mfc_parent);

		अगर (it->cache != &mrt->mfc_unres_queue) अणु
			seq_म_लिखो(seq, " %8lu %8lu %8lu",
				   mfc->_c.mfc_un.res.pkt,
				   mfc->_c.mfc_un.res.bytes,
				   mfc->_c.mfc_un.res.wrong_अगर);
			क्रम (n = mfc->_c.mfc_un.res.minvअगर;
			     n < mfc->_c.mfc_un.res.maxvअगर; n++) अणु
				अगर (VIF_EXISTS(mrt, n) &&
				    mfc->_c.mfc_un.res.ttls[n] < 255)
					seq_म_लिखो(seq,
					   " %2d:%-3d",
					   n, mfc->_c.mfc_un.res.ttls[n]);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* unresolved mfc_caches करोn't contain
			 * pkt, bytes and wrong_अगर values
			 */
			seq_म_लिखो(seq, " %8lu %8lu %8lu", 0ul, 0ul, 0ul);
		पूर्ण
		seq_अ_दो(seq, '\n');
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ipmr_mfc_seq_ops = अणु
	.start = ipmr_mfc_seq_start,
	.next  = mr_mfc_seq_next,
	.stop  = mr_mfc_seq_stop,
	.show  = ipmr_mfc_seq_show,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_PIMSM_V2
अटल स्थिर काष्ठा net_protocol pim_protocol = अणु
	.handler	=	pim_rcv,
	.netns_ok	=	1,
पूर्ण;
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक ipmr_seq_पढ़ो(काष्ठा net *net)
अणु
	ASSERT_RTNL();

	वापस net->ipv4.ipmr_seq + ipmr_rules_seq_पढ़ो(net);
पूर्ण

अटल पूर्णांक ipmr_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
		     काष्ठा netlink_ext_ack *extack)
अणु
	वापस mr_dump(net, nb, RTNL_FAMILY_IPMR, ipmr_rules_dump,
		       ipmr_mr_table_iter, &mrt_lock, extack);
पूर्ण

अटल स्थिर काष्ठा fib_notअगरier_ops ipmr_notअगरier_ops_ढाँचा = अणु
	.family		= RTNL_FAMILY_IPMR,
	.fib_seq_पढ़ो	= ipmr_seq_पढ़ो,
	.fib_dump	= ipmr_dump,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __net_init ipmr_notअगरier_init(काष्ठा net *net)
अणु
	काष्ठा fib_notअगरier_ops *ops;

	net->ipv4.ipmr_seq = 0;

	ops = fib_notअगरier_ops_रेजिस्टर(&ipmr_notअगरier_ops_ढाँचा, net);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);
	net->ipv4.ipmr_notअगरier_ops = ops;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास ipmr_notअगरier_निकास(काष्ठा net *net)
अणु
	fib_notअगरier_ops_unरेजिस्टर(net->ipv4.ipmr_notअगरier_ops);
	net->ipv4.ipmr_notअगरier_ops = शून्य;
पूर्ण

/* Setup क्रम IP multicast routing */
अटल पूर्णांक __net_init ipmr_net_init(काष्ठा net *net)
अणु
	पूर्णांक err;

	err = ipmr_notअगरier_init(net);
	अगर (err)
		जाओ ipmr_notअगरier_fail;

	err = ipmr_rules_init(net);
	अगर (err < 0)
		जाओ ipmr_rules_fail;

#अगर_घोषित CONFIG_PROC_FS
	err = -ENOMEM;
	अगर (!proc_create_net("ip_mr_vif", 0, net->proc_net, &ipmr_vअगर_seq_ops,
			माप(काष्ठा mr_vअगर_iter)))
		जाओ proc_vअगर_fail;
	अगर (!proc_create_net("ip_mr_cache", 0, net->proc_net, &ipmr_mfc_seq_ops,
			माप(काष्ठा mr_mfc_iter)))
		जाओ proc_cache_fail;
#पूर्ण_अगर
	वापस 0;

#अगर_घोषित CONFIG_PROC_FS
proc_cache_fail:
	हटाओ_proc_entry("ip_mr_vif", net->proc_net);
proc_vअगर_fail:
	ipmr_rules_निकास(net);
#पूर्ण_अगर
ipmr_rules_fail:
	ipmr_notअगरier_निकास(net);
ipmr_notअगरier_fail:
	वापस err;
पूर्ण

अटल व्योम __net_निकास ipmr_net_निकास(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("ip_mr_cache", net->proc_net);
	हटाओ_proc_entry("ip_mr_vif", net->proc_net);
#पूर्ण_अगर
	ipmr_notअगरier_निकास(net);
	ipmr_rules_निकास(net);
पूर्ण

अटल काष्ठा pernet_operations ipmr_net_ops = अणु
	.init = ipmr_net_init,
	.निकास = ipmr_net_निकास,
पूर्ण;

पूर्णांक __init ip_mr_init(व्योम)
अणु
	पूर्णांक err;

	mrt_cachep = kmem_cache_create("ip_mrt_cache",
				       माप(काष्ठा mfc_cache),
				       0, SLAB_HWCACHE_ALIGN | SLAB_PANIC,
				       शून्य);

	err = रेजिस्टर_pernet_subsys(&ipmr_net_ops);
	अगर (err)
		जाओ reg_pernet_fail;

	err = रेजिस्टर_netdevice_notअगरier(&ip_mr_notअगरier);
	अगर (err)
		जाओ reg_notअगर_fail;
#अगर_घोषित CONFIG_IP_PIMSM_V2
	अगर (inet_add_protocol(&pim_protocol, IPPROTO_PIM) < 0) अणु
		pr_err("%s: can't add PIM protocol\n", __func__);
		err = -EAGAIN;
		जाओ add_proto_fail;
	पूर्ण
#पूर्ण_अगर
	rtnl_रेजिस्टर(RTNL_FAMILY_IPMR, RTM_GETROUTE,
		      ipmr_rपंचांग_getroute, ipmr_rपंचांग_dumproute, 0);
	rtnl_रेजिस्टर(RTNL_FAMILY_IPMR, RTM_NEWROUTE,
		      ipmr_rपंचांग_route, शून्य, 0);
	rtnl_रेजिस्टर(RTNL_FAMILY_IPMR, RTM_DELROUTE,
		      ipmr_rपंचांग_route, शून्य, 0);

	rtnl_रेजिस्टर(RTNL_FAMILY_IPMR, RTM_GETLINK,
		      शून्य, ipmr_rपंचांग_dumplink, 0);
	वापस 0;

#अगर_घोषित CONFIG_IP_PIMSM_V2
add_proto_fail:
	unरेजिस्टर_netdevice_notअगरier(&ip_mr_notअगरier);
#पूर्ण_अगर
reg_notअगर_fail:
	unरेजिस्टर_pernet_subsys(&ipmr_net_ops);
reg_pernet_fail:
	kmem_cache_destroy(mrt_cachep);
	वापस err;
पूर्ण
