<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Linux IPv6 multicast routing support क्रम BSD pim6sd
 *	Based on net/ipv4/ipmr.c.
 *
 *	(c) 2004 Mickael Hoerdt, <hoerdt@clarinet.u-strasbg.fr>
 *		LSIIT Laboratory, Strasbourg, France
 *	(c) 2004 Jean-Philippe Andriot, <jean-philippe.andriot@6WIND.com>
 *		6WIND, Paris, France
 *	Copyright (C)2007,2008 USAGI/WIDE Project
 *		YOSHIFUJI Hideaki <yoshfuji@linux-ipv6.org>
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/socket.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/compat.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/protocol.h>
#समावेश <linux/skbuff.h>
#समावेश <net/raw.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/checksum.h>
#समावेश <net/netlink.h>
#समावेश <net/fib_rules.h>

#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <linux/mroute6.h>
#समावेश <linux/pim.h>
#समावेश <net/addrconf.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/export.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/netconf.h>
#समावेश <net/ip_tunnels.h>

#समावेश <linux/nospec.h>

काष्ठा ip6mr_rule अणु
	काष्ठा fib_rule		common;
पूर्ण;

काष्ठा ip6mr_result अणु
	काष्ठा mr_table	*mrt;
पूर्ण;

/* Big lock, protecting vअगर table, mrt cache and mroute socket state.
   Note that the changes are semaphored via rtnl_lock.
 */

अटल DEFINE_RWLOCK(mrt_lock);

/* Multicast router control variables */

/* Special spinlock क्रम queue of unresolved entries */
अटल DEFINE_SPINLOCK(mfc_unres_lock);

/* We वापस to original Alan's scheme. Hash table of resolved
   entries is changed only in process context and रक्षित
   with weak lock mrt_lock. Queue of unresolved entries is रक्षित
   with strong spinlock mfc_unres_lock.

   In this हाल data path is मुक्त of exclusive locks at all.
 */

अटल काष्ठा kmem_cache *mrt_cachep __पढ़ो_mostly;

अटल काष्ठा mr_table *ip6mr_new_table(काष्ठा net *net, u32 id);
अटल व्योम ip6mr_मुक्त_table(काष्ठा mr_table *mrt);

अटल व्योम ip6_mr_क्रमward(काष्ठा net *net, काष्ठा mr_table *mrt,
			   काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			   काष्ठा mfc6_cache *cache);
अटल पूर्णांक ip6mr_cache_report(काष्ठा mr_table *mrt, काष्ठा sk_buff *pkt,
			      mअगरi_t mअगरi, पूर्णांक निश्चित);
अटल व्योम mr6_netlink_event(काष्ठा mr_table *mrt, काष्ठा mfc6_cache *mfc,
			      पूर्णांक cmd);
अटल व्योम mrt6msg_netlink_event(काष्ठा mr_table *mrt, काष्ठा sk_buff *pkt);
अटल पूर्णांक ip6mr_rपंचांग_dumproute(काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb);
अटल व्योम mroute_clean_tables(काष्ठा mr_table *mrt, पूर्णांक flags);
अटल व्योम ipmr_expire_process(काष्ठा समयr_list *t);

#अगर_घोषित CONFIG_IPV6_MROUTE_MULTIPLE_TABLES
#घोषणा ip6mr_क्रम_each_table(mrt, net) \
	list_क्रम_each_entry_rcu(mrt, &net->ipv6.mr6_tables, list, \
				lockdep_rtnl_is_held() || \
				list_empty(&net->ipv6.mr6_tables))

अटल काष्ठा mr_table *ip6mr_mr_table_iter(काष्ठा net *net,
					    काष्ठा mr_table *mrt)
अणु
	काष्ठा mr_table *ret;

	अगर (!mrt)
		ret = list_entry_rcu(net->ipv6.mr6_tables.next,
				     काष्ठा mr_table, list);
	अन्यथा
		ret = list_entry_rcu(mrt->list.next,
				     काष्ठा mr_table, list);

	अगर (&ret->list == &net->ipv6.mr6_tables)
		वापस शून्य;
	वापस ret;
पूर्ण

अटल काष्ठा mr_table *ip6mr_get_table(काष्ठा net *net, u32 id)
अणु
	काष्ठा mr_table *mrt;

	ip6mr_क्रम_each_table(mrt, net) अणु
		अगर (mrt->id == id)
			वापस mrt;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक ip6mr_fib_lookup(काष्ठा net *net, काष्ठा flowi6 *flp6,
			    काष्ठा mr_table **mrt)
अणु
	पूर्णांक err;
	काष्ठा ip6mr_result res;
	काष्ठा fib_lookup_arg arg = अणु
		.result = &res,
		.flags = FIB_LOOKUP_NOREF,
	पूर्ण;

	/* update flow अगर oअगर or iअगर poपूर्णांक to device enslaved to l3mdev */
	l3mdev_update_flow(net, flowi6_to_flowi(flp6));

	err = fib_rules_lookup(net->ipv6.mr6_rules_ops,
			       flowi6_to_flowi(flp6), 0, &arg);
	अगर (err < 0)
		वापस err;
	*mrt = res.mrt;
	वापस 0;
पूर्ण

अटल पूर्णांक ip6mr_rule_action(काष्ठा fib_rule *rule, काष्ठा flowi *flp,
			     पूर्णांक flags, काष्ठा fib_lookup_arg *arg)
अणु
	काष्ठा ip6mr_result *res = arg->result;
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

	mrt = ip6mr_get_table(rule->fr_net, arg->table);
	अगर (!mrt)
		वापस -EAGAIN;
	res->mrt = mrt;
	वापस 0;
पूर्ण

अटल पूर्णांक ip6mr_rule_match(काष्ठा fib_rule *rule, काष्ठा flowi *flp, पूर्णांक flags)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा nla_policy ip6mr_rule_policy[FRA_MAX + 1] = अणु
	FRA_GENERIC_POLICY,
पूर्ण;

अटल पूर्णांक ip6mr_rule_configure(काष्ठा fib_rule *rule, काष्ठा sk_buff *skb,
				काष्ठा fib_rule_hdr *frh, काष्ठा nlattr **tb,
				काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक ip6mr_rule_compare(काष्ठा fib_rule *rule, काष्ठा fib_rule_hdr *frh,
			      काष्ठा nlattr **tb)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक ip6mr_rule_fill(काष्ठा fib_rule *rule, काष्ठा sk_buff *skb,
			   काष्ठा fib_rule_hdr *frh)
अणु
	frh->dst_len = 0;
	frh->src_len = 0;
	frh->tos     = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fib_rules_ops __net_initस्थिर ip6mr_rules_ops_ढाँचा = अणु
	.family		= RTNL_FAMILY_IP6MR,
	.rule_size	= माप(काष्ठा ip6mr_rule),
	.addr_size	= माप(काष्ठा in6_addr),
	.action		= ip6mr_rule_action,
	.match		= ip6mr_rule_match,
	.configure	= ip6mr_rule_configure,
	.compare	= ip6mr_rule_compare,
	.fill		= ip6mr_rule_fill,
	.nlgroup	= RTNLGRP_IPV6_RULE,
	.policy		= ip6mr_rule_policy,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __net_init ip6mr_rules_init(काष्ठा net *net)
अणु
	काष्ठा fib_rules_ops *ops;
	काष्ठा mr_table *mrt;
	पूर्णांक err;

	ops = fib_rules_रेजिस्टर(&ip6mr_rules_ops_ढाँचा, net);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);

	INIT_LIST_HEAD(&net->ipv6.mr6_tables);

	mrt = ip6mr_new_table(net, RT6_TABLE_DFLT);
	अगर (IS_ERR(mrt)) अणु
		err = PTR_ERR(mrt);
		जाओ err1;
	पूर्ण

	err = fib_शेष_rule_add(ops, 0x7fff, RT6_TABLE_DFLT, 0);
	अगर (err < 0)
		जाओ err2;

	net->ipv6.mr6_rules_ops = ops;
	वापस 0;

err2:
	ip6mr_मुक्त_table(mrt);
err1:
	fib_rules_unरेजिस्टर(ops);
	वापस err;
पूर्ण

अटल व्योम __net_निकास ip6mr_rules_निकास(काष्ठा net *net)
अणु
	काष्ठा mr_table *mrt, *next;

	rtnl_lock();
	list_क्रम_each_entry_safe(mrt, next, &net->ipv6.mr6_tables, list) अणु
		list_del(&mrt->list);
		ip6mr_मुक्त_table(mrt);
	पूर्ण
	fib_rules_unरेजिस्टर(net->ipv6.mr6_rules_ops);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक ip6mr_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			    काष्ठा netlink_ext_ack *extack)
अणु
	वापस fib_rules_dump(net, nb, RTNL_FAMILY_IP6MR, extack);
पूर्ण

अटल अचिन्हित पूर्णांक ip6mr_rules_seq_पढ़ो(काष्ठा net *net)
अणु
	वापस fib_rules_seq_पढ़ो(net, RTNL_FAMILY_IP6MR);
पूर्ण

bool ip6mr_rule_शेष(स्थिर काष्ठा fib_rule *rule)
अणु
	वापस fib_rule_matchall(rule) && rule->action == FR_ACT_TO_TBL &&
	       rule->table == RT6_TABLE_DFLT && !rule->l3mdev;
पूर्ण
EXPORT_SYMBOL(ip6mr_rule_शेष);
#अन्यथा
#घोषणा ip6mr_क्रम_each_table(mrt, net) \
	क्रम (mrt = net->ipv6.mrt6; mrt; mrt = शून्य)

अटल काष्ठा mr_table *ip6mr_mr_table_iter(काष्ठा net *net,
					    काष्ठा mr_table *mrt)
अणु
	अगर (!mrt)
		वापस net->ipv6.mrt6;
	वापस शून्य;
पूर्ण

अटल काष्ठा mr_table *ip6mr_get_table(काष्ठा net *net, u32 id)
अणु
	वापस net->ipv6.mrt6;
पूर्ण

अटल पूर्णांक ip6mr_fib_lookup(काष्ठा net *net, काष्ठा flowi6 *flp6,
			    काष्ठा mr_table **mrt)
अणु
	*mrt = net->ipv6.mrt6;
	वापस 0;
पूर्ण

अटल पूर्णांक __net_init ip6mr_rules_init(काष्ठा net *net)
अणु
	काष्ठा mr_table *mrt;

	mrt = ip6mr_new_table(net, RT6_TABLE_DFLT);
	अगर (IS_ERR(mrt))
		वापस PTR_ERR(mrt);
	net->ipv6.mrt6 = mrt;
	वापस 0;
पूर्ण

अटल व्योम __net_निकास ip6mr_rules_निकास(काष्ठा net *net)
अणु
	rtnl_lock();
	ip6mr_मुक्त_table(net->ipv6.mrt6);
	net->ipv6.mrt6 = शून्य;
	rtnl_unlock();
पूर्ण

अटल पूर्णांक ip6mr_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			    काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ip6mr_rules_seq_पढ़ो(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ip6mr_hash_cmp(काष्ठा rhashtable_compare_arg *arg,
			  स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा mfc6_cache_cmp_arg *cmparg = arg->key;
	काष्ठा mfc6_cache *c = (काष्ठा mfc6_cache *)ptr;

	वापस !ipv6_addr_equal(&c->mf6c_mcastgrp, &cmparg->mf6c_mcastgrp) ||
	       !ipv6_addr_equal(&c->mf6c_origin, &cmparg->mf6c_origin);
पूर्ण

अटल स्थिर काष्ठा rhashtable_params ip6mr_rht_params = अणु
	.head_offset = दुरत्व(काष्ठा mr_mfc, mnode),
	.key_offset = दुरत्व(काष्ठा mfc6_cache, cmparg),
	.key_len = माप(काष्ठा mfc6_cache_cmp_arg),
	.nelem_hपूर्णांक = 3,
	.obj_cmpfn = ip6mr_hash_cmp,
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल व्योम ip6mr_new_table_set(काष्ठा mr_table *mrt,
				काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_IPV6_MROUTE_MULTIPLE_TABLES
	list_add_tail_rcu(&mrt->list, &net->ipv6.mr6_tables);
#पूर्ण_अगर
पूर्ण

अटल काष्ठा mfc6_cache_cmp_arg ip6mr_mr_table_ops_cmparg_any = अणु
	.mf6c_origin = IN6ADDR_ANY_INIT,
	.mf6c_mcastgrp = IN6ADDR_ANY_INIT,
पूर्ण;

अटल काष्ठा mr_table_ops ip6mr_mr_table_ops = अणु
	.rht_params = &ip6mr_rht_params,
	.cmparg_any = &ip6mr_mr_table_ops_cmparg_any,
पूर्ण;

अटल काष्ठा mr_table *ip6mr_new_table(काष्ठा net *net, u32 id)
अणु
	काष्ठा mr_table *mrt;

	mrt = ip6mr_get_table(net, id);
	अगर (mrt)
		वापस mrt;

	वापस mr_table_alloc(net, id, &ip6mr_mr_table_ops,
			      ipmr_expire_process, ip6mr_new_table_set);
पूर्ण

अटल व्योम ip6mr_मुक्त_table(काष्ठा mr_table *mrt)
अणु
	del_समयr_sync(&mrt->ipmr_expire_समयr);
	mroute_clean_tables(mrt, MRT6_FLUSH_MIFS | MRT6_FLUSH_MIFS_STATIC |
				 MRT6_FLUSH_MFC | MRT6_FLUSH_MFC_STATIC);
	rhltable_destroy(&mrt->mfc_hash);
	kमुक्त(mrt);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
/* The /proc पूर्णांकerfaces to multicast routing
 * /proc/ip6_mr_cache /proc/ip6_mr_vअगर
 */

अटल व्योम *ip6mr_vअगर_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(mrt_lock)
अणु
	काष्ठा mr_vअगर_iter *iter = seq->निजी;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा mr_table *mrt;

	mrt = ip6mr_get_table(net, RT6_TABLE_DFLT);
	अगर (!mrt)
		वापस ERR_PTR(-ENOENT);

	iter->mrt = mrt;

	पढ़ो_lock(&mrt_lock);
	वापस mr_vअगर_seq_start(seq, pos);
पूर्ण

अटल व्योम ip6mr_vअगर_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(mrt_lock)
अणु
	पढ़ो_unlock(&mrt_lock);
पूर्ण

अटल पूर्णांक ip6mr_vअगर_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा mr_vअगर_iter *iter = seq->निजी;
	काष्ठा mr_table *mrt = iter->mrt;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq,
			 "Interface      BytesIn  PktsIn  BytesOut PktsOut Flags\n");
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा vअगर_device *vअगर = v;
		स्थिर अक्षर *name = vअगर->dev ? vअगर->dev->name : "none";

		seq_म_लिखो(seq,
			   "%2td %-10s %8ld %7ld  %8ld %7ld %05X\n",
			   vअगर - mrt->vअगर_table,
			   name, vअगर->bytes_in, vअगर->pkt_in,
			   vअगर->bytes_out, vअगर->pkt_out,
			   vअगर->flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ip6mr_vअगर_seq_ops = अणु
	.start = ip6mr_vअगर_seq_start,
	.next  = mr_vअगर_seq_next,
	.stop  = ip6mr_vअगर_seq_stop,
	.show  = ip6mr_vअगर_seq_show,
पूर्ण;

अटल व्योम *ipmr_mfc_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा mr_table *mrt;

	mrt = ip6mr_get_table(net, RT6_TABLE_DFLT);
	अगर (!mrt)
		वापस ERR_PTR(-ENOENT);

	वापस mr_mfc_seq_start(seq, pos, mrt, &mfc_unres_lock);
पूर्ण

अटल पूर्णांक ipmr_mfc_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक n;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq,
			 "Group                            "
			 "Origin                           "
			 "Iif      Pkts  Bytes     Wrong  Oifs\n");
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा mfc6_cache *mfc = v;
		स्थिर काष्ठा mr_mfc_iter *it = seq->निजी;
		काष्ठा mr_table *mrt = it->mrt;

		seq_म_लिखो(seq, "%pI6 %pI6 %-3hd",
			   &mfc->mf6c_mcastgrp, &mfc->mf6c_origin,
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
						   " %2d:%-3d", n,
						   mfc->_c.mfc_un.res.ttls[n]);
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

#अगर_घोषित CONFIG_IPV6_PIMSM_V2

अटल पूर्णांक pim6_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा pimreghdr *pim;
	काष्ठा ipv6hdr   *encap;
	काष्ठा net_device  *reg_dev = शून्य;
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा mr_table *mrt;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_iअगर	= skb->dev->अगरindex,
		.flowi6_mark	= skb->mark,
	पूर्ण;
	पूर्णांक reg_vअगर_num;

	अगर (!pskb_may_pull(skb, माप(*pim) + माप(*encap)))
		जाओ drop;

	pim = (काष्ठा pimreghdr *)skb_transport_header(skb);
	अगर (pim->type != ((PIM_VERSION << 4) | PIM_TYPE_REGISTER) ||
	    (pim->flags & PIM_शून्य_REGISTER) ||
	    (csum_ipv6_magic(&ipv6_hdr(skb)->saddr, &ipv6_hdr(skb)->daddr,
			     माप(*pim), IPPROTO_PIM,
			     csum_partial((व्योम *)pim, माप(*pim), 0)) &&
	     csum_fold(skb_checksum(skb, 0, skb->len, 0))))
		जाओ drop;

	/* check अगर the inner packet is destined to mcast group */
	encap = (काष्ठा ipv6hdr *)(skb_transport_header(skb) +
				   माप(*pim));

	अगर (!ipv6_addr_is_multicast(&encap->daddr) ||
	    encap->payload_len == 0 ||
	    ntohs(encap->payload_len) + माप(*pim) > skb->len)
		जाओ drop;

	अगर (ip6mr_fib_lookup(net, &fl6, &mrt) < 0)
		जाओ drop;
	reg_vअगर_num = mrt->mroute_reg_vअगर_num;

	पढ़ो_lock(&mrt_lock);
	अगर (reg_vअगर_num >= 0)
		reg_dev = mrt->vअगर_table[reg_vअगर_num].dev;
	अगर (reg_dev)
		dev_hold(reg_dev);
	पढ़ो_unlock(&mrt_lock);

	अगर (!reg_dev)
		जाओ drop;

	skb->mac_header = skb->network_header;
	skb_pull(skb, (u8 *)encap - skb->data);
	skb_reset_network_header(skb);
	skb->protocol = htons(ETH_P_IPV6);
	skb->ip_summed = CHECKSUM_NONE;

	skb_tunnel_rx(skb, reg_dev, dev_net(reg_dev));

	netअगर_rx(skb);

	dev_put(reg_dev);
	वापस 0;
 drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inet6_protocol pim6_protocol = अणु
	.handler	=	pim6_rcv,
पूर्ण;

/* Service routines creating भव पूर्णांकerfaces: PIMREG */

अटल netdev_tx_t reg_vअगर_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा mr_table *mrt;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_oअगर	= dev->अगरindex,
		.flowi6_iअगर	= skb->skb_iअगर ? : LOOPBACK_IFINDEX,
		.flowi6_mark	= skb->mark,
	पूर्ण;

	अगर (!pskb_inet_may_pull(skb))
		जाओ tx_err;

	अगर (ip6mr_fib_lookup(net, &fl6, &mrt) < 0)
		जाओ tx_err;

	पढ़ो_lock(&mrt_lock);
	dev->stats.tx_bytes += skb->len;
	dev->stats.tx_packets++;
	ip6mr_cache_report(mrt, skb, mrt->mroute_reg_vअगर_num, MRT6MSG_WHOLEPKT);
	पढ़ो_unlock(&mrt_lock);
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;

tx_err:
	dev->stats.tx_errors++;
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
	dev->mtu		= 1500 - माप(काष्ठा ipv6hdr) - 8;
	dev->flags		= IFF_NOARP;
	dev->netdev_ops		= &reg_vअगर_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
	dev->features		|= NETIF_F_NETNS_LOCAL;
पूर्ण

अटल काष्ठा net_device *ip6mr_reg_vअगर(काष्ठा net *net, काष्ठा mr_table *mrt)
अणु
	काष्ठा net_device *dev;
	अक्षर name[IFNAMSIZ];

	अगर (mrt->id == RT6_TABLE_DFLT)
		प्र_लिखो(name, "pim6reg");
	अन्यथा
		प्र_लिखो(name, "pim6reg%u", mrt->id);

	dev = alloc_netdev(0, name, NET_NAME_UNKNOWN, reg_vअगर_setup);
	अगर (!dev)
		वापस शून्य;

	dev_net_set(dev, net);

	अगर (रेजिस्टर_netdevice(dev)) अणु
		मुक्त_netdev(dev);
		वापस शून्य;
	पूर्ण

	अगर (dev_खोलो(dev, शून्य))
		जाओ failure;

	dev_hold(dev);
	वापस dev;

failure:
	unरेजिस्टर_netdevice(dev);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक call_ip6mr_vअगर_entry_notअगरiers(काष्ठा net *net,
					  क्रमागत fib_event_type event_type,
					  काष्ठा vअगर_device *vअगर,
					  mअगरi_t vअगर_index, u32 tb_id)
अणु
	वापस mr_call_vअगर_notअगरiers(net, RTNL_FAMILY_IP6MR, event_type,
				     vअगर, vअगर_index, tb_id,
				     &net->ipv6.ipmr_seq);
पूर्ण

अटल पूर्णांक call_ip6mr_mfc_entry_notअगरiers(काष्ठा net *net,
					  क्रमागत fib_event_type event_type,
					  काष्ठा mfc6_cache *mfc, u32 tb_id)
अणु
	वापस mr_call_mfc_notअगरiers(net, RTNL_FAMILY_IP6MR, event_type,
				     &mfc->_c, tb_id, &net->ipv6.ipmr_seq);
पूर्ण

/* Delete a VIF entry */
अटल पूर्णांक mअगर6_delete(काष्ठा mr_table *mrt, पूर्णांक vअगरi, पूर्णांक notअगरy,
		       काष्ठा list_head *head)
अणु
	काष्ठा vअगर_device *v;
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *in6_dev;

	अगर (vअगरi < 0 || vअगरi >= mrt->maxvअगर)
		वापस -EADDRNOTAVAIL;

	v = &mrt->vअगर_table[vअगरi];

	अगर (VIF_EXISTS(mrt, vअगरi))
		call_ip6mr_vअगर_entry_notअगरiers(पढ़ो_pnet(&mrt->net),
					       FIB_EVENT_VIF_DEL, v, vअगरi,
					       mrt->id);

	ग_लिखो_lock_bh(&mrt_lock);
	dev = v->dev;
	v->dev = शून्य;

	अगर (!dev) अणु
		ग_लिखो_unlock_bh(&mrt_lock);
		वापस -EADDRNOTAVAIL;
	पूर्ण

#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	अगर (vअगरi == mrt->mroute_reg_vअगर_num)
		mrt->mroute_reg_vअगर_num = -1;
#पूर्ण_अगर

	अगर (vअगरi + 1 == mrt->maxvअगर) अणु
		पूर्णांक पंचांगp;
		क्रम (पंचांगp = vअगरi - 1; पंचांगp >= 0; पंचांगp--) अणु
			अगर (VIF_EXISTS(mrt, पंचांगp))
				अवरोध;
		पूर्ण
		mrt->maxvअगर = पंचांगp + 1;
	पूर्ण

	ग_लिखो_unlock_bh(&mrt_lock);

	dev_set_allmulti(dev, -1);

	in6_dev = __in6_dev_get(dev);
	अगर (in6_dev) अणु
		in6_dev->cnf.mc_क्रमwarding--;
		inet6_netconf_notअगरy_devconf(dev_net(dev), RTM_NEWNETCONF,
					     NETCONFA_MC_FORWARDING,
					     dev->अगरindex, &in6_dev->cnf);
	पूर्ण

	अगर ((v->flags & MIFF_REGISTER) && !notअगरy)
		unरेजिस्टर_netdevice_queue(dev, head);

	dev_put(dev);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ip6mr_cache_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा mr_mfc *c = container_of(head, काष्ठा mr_mfc, rcu);

	kmem_cache_मुक्त(mrt_cachep, (काष्ठा mfc6_cache *)c);
पूर्ण

अटल अंतरभूत व्योम ip6mr_cache_मुक्त(काष्ठा mfc6_cache *c)
अणु
	call_rcu(&c->_c.rcu, ip6mr_cache_मुक्त_rcu);
पूर्ण

/* Destroy an unresolved cache entry, समाप्तing queued skbs
   and reporting error to netlink पढ़ोers.
 */

अटल व्योम ip6mr_destroy_unres(काष्ठा mr_table *mrt, काष्ठा mfc6_cache *c)
अणु
	काष्ठा net *net = पढ़ो_pnet(&mrt->net);
	काष्ठा sk_buff *skb;

	atomic_dec(&mrt->cache_resolve_queue_len);

	जबतक ((skb = skb_dequeue(&c->_c.mfc_un.unres.unresolved)) != शून्य) अणु
		अगर (ipv6_hdr(skb)->version == 0) अणु
			काष्ठा nlmsghdr *nlh = skb_pull(skb,
							माप(काष्ठा ipv6hdr));
			nlh->nlmsg_type = NLMSG_ERROR;
			nlh->nlmsg_len = nlmsg_msg_size(माप(काष्ठा nlmsgerr));
			skb_trim(skb, nlh->nlmsg_len);
			((काष्ठा nlmsgerr *)nlmsg_data(nlh))->error = -ETIMEDOUT;
			rtnl_unicast(skb, net, NETLINK_CB(skb).portid);
		पूर्ण अन्यथा
			kमुक्त_skb(skb);
	पूर्ण

	ip6mr_cache_मुक्त(c);
पूर्ण


/* Timer process क्रम all the unresolved queue. */

अटल व्योम ipmr_करो_expire_process(काष्ठा mr_table *mrt)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ expires = 10 * HZ;
	काष्ठा mr_mfc *c, *next;

	list_क्रम_each_entry_safe(c, next, &mrt->mfc_unres_queue, list) अणु
		अगर (समय_after(c->mfc_un.unres.expires, now)) अणु
			/* not yet... */
			अचिन्हित दीर्घ पूर्णांकerval = c->mfc_un.unres.expires - now;
			अगर (पूर्णांकerval < expires)
				expires = पूर्णांकerval;
			जारी;
		पूर्ण

		list_del(&c->list);
		mr6_netlink_event(mrt, (काष्ठा mfc6_cache *)c, RTM_DELROUTE);
		ip6mr_destroy_unres(mrt, (काष्ठा mfc6_cache *)c);
	पूर्ण

	अगर (!list_empty(&mrt->mfc_unres_queue))
		mod_समयr(&mrt->ipmr_expire_समयr, jअगरfies + expires);
पूर्ण

अटल व्योम ipmr_expire_process(काष्ठा समयr_list *t)
अणु
	काष्ठा mr_table *mrt = from_समयr(mrt, t, ipmr_expire_समयr);

	अगर (!spin_trylock(&mfc_unres_lock)) अणु
		mod_समयr(&mrt->ipmr_expire_समयr, jअगरfies + 1);
		वापस;
	पूर्ण

	अगर (!list_empty(&mrt->mfc_unres_queue))
		ipmr_करो_expire_process(mrt);

	spin_unlock(&mfc_unres_lock);
पूर्ण

/* Fill oअगरs list. It is called under ग_लिखो locked mrt_lock. */

अटल व्योम ip6mr_update_thresholds(काष्ठा mr_table *mrt,
				    काष्ठा mr_mfc *cache,
				    अचिन्हित अक्षर *ttls)
अणु
	पूर्णांक vअगरi;

	cache->mfc_un.res.minvअगर = MAXMIFS;
	cache->mfc_un.res.maxvअगर = 0;
	स_रखो(cache->mfc_un.res.ttls, 255, MAXMIFS);

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

अटल पूर्णांक mअगर6_add(काष्ठा net *net, काष्ठा mr_table *mrt,
		    काष्ठा mअगर6ctl *vअगरc, पूर्णांक mrtsock)
अणु
	पूर्णांक vअगरi = vअगरc->mअगर6c_mअगरi;
	काष्ठा vअगर_device *v = &mrt->vअगर_table[vअगरi];
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *in6_dev;
	पूर्णांक err;

	/* Is vअगर busy ? */
	अगर (VIF_EXISTS(mrt, vअगरi))
		वापस -EADDRINUSE;

	चयन (vअगरc->mअगर6c_flags) अणु
#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	हाल MIFF_REGISTER:
		/*
		 * Special Purpose VIF in PIM
		 * All the packets will be sent to the daemon
		 */
		अगर (mrt->mroute_reg_vअगर_num >= 0)
			वापस -EADDRINUSE;
		dev = ip6mr_reg_vअगर(net, mrt);
		अगर (!dev)
			वापस -ENOBUFS;
		err = dev_set_allmulti(dev, 1);
		अगर (err) अणु
			unरेजिस्टर_netdevice(dev);
			dev_put(dev);
			वापस err;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	हाल 0:
		dev = dev_get_by_index(net, vअगरc->mअगर6c_pअगरi);
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

	in6_dev = __in6_dev_get(dev);
	अगर (in6_dev) अणु
		in6_dev->cnf.mc_क्रमwarding++;
		inet6_netconf_notअगरy_devconf(dev_net(dev), RTM_NEWNETCONF,
					     NETCONFA_MC_FORWARDING,
					     dev->अगरindex, &in6_dev->cnf);
	पूर्ण

	/* Fill in the VIF काष्ठाures */
	vअगर_device_init(v, dev, vअगरc->vअगरc_rate_limit, vअगरc->vअगरc_threshold,
			vअगरc->mअगर6c_flags | (!mrtsock ? VIFF_STATIC : 0),
			MIFF_REGISTER);

	/* And finish update writing critical data */
	ग_लिखो_lock_bh(&mrt_lock);
	v->dev = dev;
#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	अगर (v->flags & MIFF_REGISTER)
		mrt->mroute_reg_vअगर_num = vअगरi;
#पूर्ण_अगर
	अगर (vअगरi + 1 > mrt->maxvअगर)
		mrt->maxvअगर = vअगरi + 1;
	ग_लिखो_unlock_bh(&mrt_lock);
	call_ip6mr_vअगर_entry_notअगरiers(net, FIB_EVENT_VIF_ADD,
				       v, vअगरi, mrt->id);
	वापस 0;
पूर्ण

अटल काष्ठा mfc6_cache *ip6mr_cache_find(काष्ठा mr_table *mrt,
					   स्थिर काष्ठा in6_addr *origin,
					   स्थिर काष्ठा in6_addr *mcastgrp)
अणु
	काष्ठा mfc6_cache_cmp_arg arg = अणु
		.mf6c_origin = *origin,
		.mf6c_mcastgrp = *mcastgrp,
	पूर्ण;

	वापस mr_mfc_find(mrt, &arg);
पूर्ण

/* Look क्रम a (*,G) entry */
अटल काष्ठा mfc6_cache *ip6mr_cache_find_any(काष्ठा mr_table *mrt,
					       काष्ठा in6_addr *mcastgrp,
					       mअगरi_t mअगरi)
अणु
	काष्ठा mfc6_cache_cmp_arg arg = अणु
		.mf6c_origin = in6addr_any,
		.mf6c_mcastgrp = *mcastgrp,
	पूर्ण;

	अगर (ipv6_addr_any(mcastgrp))
		वापस mr_mfc_find_any_parent(mrt, mअगरi);
	वापस mr_mfc_find_any(mrt, mअगरi, &arg);
पूर्ण

/* Look क्रम a (S,G,iअगर) entry अगर parent != -1 */
अटल काष्ठा mfc6_cache *
ip6mr_cache_find_parent(काष्ठा mr_table *mrt,
			स्थिर काष्ठा in6_addr *origin,
			स्थिर काष्ठा in6_addr *mcastgrp,
			पूर्णांक parent)
अणु
	काष्ठा mfc6_cache_cmp_arg arg = अणु
		.mf6c_origin = *origin,
		.mf6c_mcastgrp = *mcastgrp,
	पूर्ण;

	वापस mr_mfc_find_parent(mrt, &arg, parent);
पूर्ण

/* Allocate a multicast cache entry */
अटल काष्ठा mfc6_cache *ip6mr_cache_alloc(व्योम)
अणु
	काष्ठा mfc6_cache *c = kmem_cache_zalloc(mrt_cachep, GFP_KERNEL);
	अगर (!c)
		वापस शून्य;
	c->_c.mfc_un.res.last_निश्चित = jअगरfies - MFC_ASSERT_THRESH - 1;
	c->_c.mfc_un.res.minvअगर = MAXMIFS;
	c->_c.मुक्त = ip6mr_cache_मुक्त_rcu;
	refcount_set(&c->_c.mfc_un.res.refcount, 1);
	वापस c;
पूर्ण

अटल काष्ठा mfc6_cache *ip6mr_cache_alloc_unres(व्योम)
अणु
	काष्ठा mfc6_cache *c = kmem_cache_zalloc(mrt_cachep, GFP_ATOMIC);
	अगर (!c)
		वापस शून्य;
	skb_queue_head_init(&c->_c.mfc_un.unres.unresolved);
	c->_c.mfc_un.unres.expires = jअगरfies + 10 * HZ;
	वापस c;
पूर्ण

/*
 *	A cache entry has gone पूर्णांकo a resolved state from queued
 */

अटल व्योम ip6mr_cache_resolve(काष्ठा net *net, काष्ठा mr_table *mrt,
				काष्ठा mfc6_cache *uc, काष्ठा mfc6_cache *c)
अणु
	काष्ठा sk_buff *skb;

	/*
	 *	Play the pending entries through our router
	 */

	जबतक ((skb = __skb_dequeue(&uc->_c.mfc_un.unres.unresolved))) अणु
		अगर (ipv6_hdr(skb)->version == 0) अणु
			काष्ठा nlmsghdr *nlh = skb_pull(skb,
							माप(काष्ठा ipv6hdr));

			अगर (mr_fill_mroute(mrt, skb, &c->_c,
					   nlmsg_data(nlh)) > 0) अणु
				nlh->nlmsg_len = skb_tail_poपूर्णांकer(skb) - (u8 *)nlh;
			पूर्ण अन्यथा अणु
				nlh->nlmsg_type = NLMSG_ERROR;
				nlh->nlmsg_len = nlmsg_msg_size(माप(काष्ठा nlmsgerr));
				skb_trim(skb, nlh->nlmsg_len);
				((काष्ठा nlmsgerr *)nlmsg_data(nlh))->error = -EMSGSIZE;
			पूर्ण
			rtnl_unicast(skb, net, NETLINK_CB(skb).portid);
		पूर्ण अन्यथा
			ip6_mr_क्रमward(net, mrt, skb->dev, skb, c);
	पूर्ण
पूर्ण

/*
 *	Bounce a cache query up to pim6sd and netlink.
 *
 *	Called under mrt_lock.
 */

अटल पूर्णांक ip6mr_cache_report(काष्ठा mr_table *mrt, काष्ठा sk_buff *pkt,
			      mअगरi_t mअगरi, पूर्णांक निश्चित)
अणु
	काष्ठा sock *mroute6_sk;
	काष्ठा sk_buff *skb;
	काष्ठा mrt6msg *msg;
	पूर्णांक ret;

#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	अगर (निश्चित == MRT6MSG_WHOLEPKT)
		skb = skb_पुनः_स्मृति_headroom(pkt, -skb_network_offset(pkt)
						+माप(*msg));
	अन्यथा
#पूर्ण_अगर
		skb = alloc_skb(माप(काष्ठा ipv6hdr) + माप(*msg), GFP_ATOMIC);

	अगर (!skb)
		वापस -ENOBUFS;

	/* I suppose that पूर्णांकernal messages
	 * करो not require checksums */

	skb->ip_summed = CHECKSUM_UNNECESSARY;

#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	अगर (निश्चित == MRT6MSG_WHOLEPKT) अणु
		/* Ugly, but we have no choice with this पूर्णांकerface.
		   Duplicate old header, fix length etc.
		   And all this only to mangle msg->im6_msgtype and
		   to set msg->im6_mbz to "mbz" :-)
		 */
		skb_push(skb, -skb_network_offset(pkt));

		skb_push(skb, माप(*msg));
		skb_reset_transport_header(skb);
		msg = (काष्ठा mrt6msg *)skb_transport_header(skb);
		msg->im6_mbz = 0;
		msg->im6_msgtype = MRT6MSG_WHOLEPKT;
		msg->im6_mअगर = mrt->mroute_reg_vअगर_num;
		msg->im6_pad = 0;
		msg->im6_src = ipv6_hdr(pkt)->saddr;
		msg->im6_dst = ipv6_hdr(pkt)->daddr;

		skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
	/*
	 *	Copy the IP header
	 */

	skb_put(skb, माप(काष्ठा ipv6hdr));
	skb_reset_network_header(skb);
	skb_copy_to_linear_data(skb, ipv6_hdr(pkt), माप(काष्ठा ipv6hdr));

	/*
	 *	Add our header
	 */
	skb_put(skb, माप(*msg));
	skb_reset_transport_header(skb);
	msg = (काष्ठा mrt6msg *)skb_transport_header(skb);

	msg->im6_mbz = 0;
	msg->im6_msgtype = निश्चित;
	msg->im6_mअगर = mअगरi;
	msg->im6_pad = 0;
	msg->im6_src = ipv6_hdr(pkt)->saddr;
	msg->im6_dst = ipv6_hdr(pkt)->daddr;

	skb_dst_set(skb, dst_clone(skb_dst(pkt)));
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

	rcu_पढ़ो_lock();
	mroute6_sk = rcu_dereference(mrt->mroute_sk);
	अगर (!mroute6_sk) अणु
		rcu_पढ़ो_unlock();
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	mrt6msg_netlink_event(mrt, skb);

	/* Deliver to user space multicast routing algorithms */
	ret = sock_queue_rcv_skb(mroute6_sk, skb);
	rcu_पढ़ो_unlock();
	अगर (ret < 0) अणु
		net_warn_ratelimited("mroute6: pending queue full, dropping entries\n");
		kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

/* Queue a packet क्रम resolution. It माला_लो locked cache entry! */
अटल पूर्णांक ip6mr_cache_unresolved(काष्ठा mr_table *mrt, mअगरi_t mअगरi,
				  काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mfc6_cache *c;
	bool found = false;
	पूर्णांक err;

	spin_lock_bh(&mfc_unres_lock);
	list_क्रम_each_entry(c, &mrt->mfc_unres_queue, _c.list) अणु
		अगर (ipv6_addr_equal(&c->mf6c_mcastgrp, &ipv6_hdr(skb)->daddr) &&
		    ipv6_addr_equal(&c->mf6c_origin, &ipv6_hdr(skb)->saddr)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		/*
		 *	Create a new entry अगर allowable
		 */

		c = ip6mr_cache_alloc_unres();
		अगर (!c) अणु
			spin_unlock_bh(&mfc_unres_lock);

			kमुक्त_skb(skb);
			वापस -ENOBUFS;
		पूर्ण

		/* Fill in the new cache entry */
		c->_c.mfc_parent = -1;
		c->mf6c_origin = ipv6_hdr(skb)->saddr;
		c->mf6c_mcastgrp = ipv6_hdr(skb)->daddr;

		/*
		 *	Reflect first query at pim6sd
		 */
		err = ip6mr_cache_report(mrt, skb, mअगरi, MRT6MSG_NOCACHE);
		अगर (err < 0) अणु
			/* If the report failed throw the cache entry
			   out - Brad Parker
			 */
			spin_unlock_bh(&mfc_unres_lock);

			ip6mr_cache_मुक्त(c);
			kमुक्त_skb(skb);
			वापस err;
		पूर्ण

		atomic_inc(&mrt->cache_resolve_queue_len);
		list_add(&c->_c.list, &mrt->mfc_unres_queue);
		mr6_netlink_event(mrt, c, RTM_NEWROUTE);

		ipmr_करो_expire_process(mrt);
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

/*
 *	MFC6 cache manipulation by user space
 */

अटल पूर्णांक ip6mr_mfc_delete(काष्ठा mr_table *mrt, काष्ठा mf6cctl *mfc,
			    पूर्णांक parent)
अणु
	काष्ठा mfc6_cache *c;

	/* The entries are added/deleted only under RTNL */
	rcu_पढ़ो_lock();
	c = ip6mr_cache_find_parent(mrt, &mfc->mf6cc_origin.sin6_addr,
				    &mfc->mf6cc_mcastgrp.sin6_addr, parent);
	rcu_पढ़ो_unlock();
	अगर (!c)
		वापस -ENOENT;
	rhltable_हटाओ(&mrt->mfc_hash, &c->_c.mnode, ip6mr_rht_params);
	list_del_rcu(&c->_c.list);

	call_ip6mr_mfc_entry_notअगरiers(पढ़ो_pnet(&mrt->net),
				       FIB_EVENT_ENTRY_DEL, c, mrt->id);
	mr6_netlink_event(mrt, c, RTM_DELROUTE);
	mr_cache_put(&c->_c);
	वापस 0;
पूर्ण

अटल पूर्णांक ip6mr_device_event(काष्ठा notअगरier_block *this,
			      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);
	काष्ठा mr_table *mrt;
	काष्ठा vअगर_device *v;
	पूर्णांक ct;

	अगर (event != NETDEV_UNREGISTER)
		वापस NOTIFY_DONE;

	ip6mr_क्रम_each_table(mrt, net) अणु
		v = &mrt->vअगर_table[0];
		क्रम (ct = 0; ct < mrt->maxvअगर; ct++, v++) अणु
			अगर (v->dev == dev)
				mअगर6_delete(mrt, ct, 1, शून्य);
		पूर्ण
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल अचिन्हित पूर्णांक ip6mr_seq_पढ़ो(काष्ठा net *net)
अणु
	ASSERT_RTNL();

	वापस net->ipv6.ipmr_seq + ip6mr_rules_seq_पढ़ो(net);
पूर्ण

अटल पूर्णांक ip6mr_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
		      काष्ठा netlink_ext_ack *extack)
अणु
	वापस mr_dump(net, nb, RTNL_FAMILY_IP6MR, ip6mr_rules_dump,
		       ip6mr_mr_table_iter, &mrt_lock, extack);
पूर्ण

अटल काष्ठा notअगरier_block ip6_mr_notअगरier = अणु
	.notअगरier_call = ip6mr_device_event
पूर्ण;

अटल स्थिर काष्ठा fib_notअगरier_ops ip6mr_notअगरier_ops_ढाँचा = अणु
	.family		= RTNL_FAMILY_IP6MR,
	.fib_seq_पढ़ो	= ip6mr_seq_पढ़ो,
	.fib_dump	= ip6mr_dump,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __net_init ip6mr_notअगरier_init(काष्ठा net *net)
अणु
	काष्ठा fib_notअगरier_ops *ops;

	net->ipv6.ipmr_seq = 0;

	ops = fib_notअगरier_ops_रेजिस्टर(&ip6mr_notअगरier_ops_ढाँचा, net);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);

	net->ipv6.ip6mr_notअगरier_ops = ops;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास ip6mr_notअगरier_निकास(काष्ठा net *net)
अणु
	fib_notअगरier_ops_unरेजिस्टर(net->ipv6.ip6mr_notअगरier_ops);
	net->ipv6.ip6mr_notअगरier_ops = शून्य;
पूर्ण

/* Setup क्रम IP multicast routing */
अटल पूर्णांक __net_init ip6mr_net_init(काष्ठा net *net)
अणु
	पूर्णांक err;

	err = ip6mr_notअगरier_init(net);
	अगर (err)
		वापस err;

	err = ip6mr_rules_init(net);
	अगर (err < 0)
		जाओ ip6mr_rules_fail;

#अगर_घोषित CONFIG_PROC_FS
	err = -ENOMEM;
	अगर (!proc_create_net("ip6_mr_vif", 0, net->proc_net, &ip6mr_vअगर_seq_ops,
			माप(काष्ठा mr_vअगर_iter)))
		जाओ proc_vअगर_fail;
	अगर (!proc_create_net("ip6_mr_cache", 0, net->proc_net, &ipmr_mfc_seq_ops,
			माप(काष्ठा mr_mfc_iter)))
		जाओ proc_cache_fail;
#पूर्ण_अगर

	वापस 0;

#अगर_घोषित CONFIG_PROC_FS
proc_cache_fail:
	हटाओ_proc_entry("ip6_mr_vif", net->proc_net);
proc_vअगर_fail:
	ip6mr_rules_निकास(net);
#पूर्ण_अगर
ip6mr_rules_fail:
	ip6mr_notअगरier_निकास(net);
	वापस err;
पूर्ण

अटल व्योम __net_निकास ip6mr_net_निकास(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("ip6_mr_cache", net->proc_net);
	हटाओ_proc_entry("ip6_mr_vif", net->proc_net);
#पूर्ण_अगर
	ip6mr_rules_निकास(net);
	ip6mr_notअगरier_निकास(net);
पूर्ण

अटल काष्ठा pernet_operations ip6mr_net_ops = अणु
	.init = ip6mr_net_init,
	.निकास = ip6mr_net_निकास,
पूर्ण;

पूर्णांक __init ip6_mr_init(व्योम)
अणु
	पूर्णांक err;

	mrt_cachep = kmem_cache_create("ip6_mrt_cache",
				       माप(काष्ठा mfc6_cache),
				       0, SLAB_HWCACHE_ALIGN,
				       शून्य);
	अगर (!mrt_cachep)
		वापस -ENOMEM;

	err = रेजिस्टर_pernet_subsys(&ip6mr_net_ops);
	अगर (err)
		जाओ reg_pernet_fail;

	err = रेजिस्टर_netdevice_notअगरier(&ip6_mr_notअगरier);
	अगर (err)
		जाओ reg_notअगर_fail;
#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	अगर (inet6_add_protocol(&pim6_protocol, IPPROTO_PIM) < 0) अणु
		pr_err("%s: can't add PIM protocol\n", __func__);
		err = -EAGAIN;
		जाओ add_proto_fail;
	पूर्ण
#पूर्ण_अगर
	err = rtnl_रेजिस्टर_module(THIS_MODULE, RTNL_FAMILY_IP6MR, RTM_GETROUTE,
				   शून्य, ip6mr_rपंचांग_dumproute, 0);
	अगर (err == 0)
		वापस 0;

#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	inet6_del_protocol(&pim6_protocol, IPPROTO_PIM);
add_proto_fail:
	unरेजिस्टर_netdevice_notअगरier(&ip6_mr_notअगरier);
#पूर्ण_अगर
reg_notअगर_fail:
	unरेजिस्टर_pernet_subsys(&ip6mr_net_ops);
reg_pernet_fail:
	kmem_cache_destroy(mrt_cachep);
	वापस err;
पूर्ण

व्योम ip6_mr_cleanup(व्योम)
अणु
	rtnl_unरेजिस्टर(RTNL_FAMILY_IP6MR, RTM_GETROUTE);
#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	inet6_del_protocol(&pim6_protocol, IPPROTO_PIM);
#पूर्ण_अगर
	unरेजिस्टर_netdevice_notअगरier(&ip6_mr_notअगरier);
	unरेजिस्टर_pernet_subsys(&ip6mr_net_ops);
	kmem_cache_destroy(mrt_cachep);
पूर्ण

अटल पूर्णांक ip6mr_mfc_add(काष्ठा net *net, काष्ठा mr_table *mrt,
			 काष्ठा mf6cctl *mfc, पूर्णांक mrtsock, पूर्णांक parent)
अणु
	अचिन्हित अक्षर ttls[MAXMIFS];
	काष्ठा mfc6_cache *uc, *c;
	काष्ठा mr_mfc *_uc;
	bool found;
	पूर्णांक i, err;

	अगर (mfc->mf6cc_parent >= MAXMIFS)
		वापस -ENखाता;

	स_रखो(ttls, 255, MAXMIFS);
	क्रम (i = 0; i < MAXMIFS; i++) अणु
		अगर (IF_ISSET(i, &mfc->mf6cc_अगरset))
			ttls[i] = 1;
	पूर्ण

	/* The entries are added/deleted only under RTNL */
	rcu_पढ़ो_lock();
	c = ip6mr_cache_find_parent(mrt, &mfc->mf6cc_origin.sin6_addr,
				    &mfc->mf6cc_mcastgrp.sin6_addr, parent);
	rcu_पढ़ो_unlock();
	अगर (c) अणु
		ग_लिखो_lock_bh(&mrt_lock);
		c->_c.mfc_parent = mfc->mf6cc_parent;
		ip6mr_update_thresholds(mrt, &c->_c, ttls);
		अगर (!mrtsock)
			c->_c.mfc_flags |= MFC_STATIC;
		ग_लिखो_unlock_bh(&mrt_lock);
		call_ip6mr_mfc_entry_notअगरiers(net, FIB_EVENT_ENTRY_REPLACE,
					       c, mrt->id);
		mr6_netlink_event(mrt, c, RTM_NEWROUTE);
		वापस 0;
	पूर्ण

	अगर (!ipv6_addr_any(&mfc->mf6cc_mcastgrp.sin6_addr) &&
	    !ipv6_addr_is_multicast(&mfc->mf6cc_mcastgrp.sin6_addr))
		वापस -EINVAL;

	c = ip6mr_cache_alloc();
	अगर (!c)
		वापस -ENOMEM;

	c->mf6c_origin = mfc->mf6cc_origin.sin6_addr;
	c->mf6c_mcastgrp = mfc->mf6cc_mcastgrp.sin6_addr;
	c->_c.mfc_parent = mfc->mf6cc_parent;
	ip6mr_update_thresholds(mrt, &c->_c, ttls);
	अगर (!mrtsock)
		c->_c.mfc_flags |= MFC_STATIC;

	err = rhltable_insert_key(&mrt->mfc_hash, &c->cmparg, &c->_c.mnode,
				  ip6mr_rht_params);
	अगर (err) अणु
		pr_err("ip6mr: rhtable insert error %d\n", err);
		ip6mr_cache_मुक्त(c);
		वापस err;
	पूर्ण
	list_add_tail_rcu(&c->_c.list, &mrt->mfc_cache_list);

	/* Check to see अगर we resolved a queued list. If so we
	 * need to send on the frames and tidy up.
	 */
	found = false;
	spin_lock_bh(&mfc_unres_lock);
	list_क्रम_each_entry(_uc, &mrt->mfc_unres_queue, list) अणु
		uc = (काष्ठा mfc6_cache *)_uc;
		अगर (ipv6_addr_equal(&uc->mf6c_origin, &c->mf6c_origin) &&
		    ipv6_addr_equal(&uc->mf6c_mcastgrp, &c->mf6c_mcastgrp)) अणु
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
		ip6mr_cache_resolve(net, mrt, uc, c);
		ip6mr_cache_मुक्त(uc);
	पूर्ण
	call_ip6mr_mfc_entry_notअगरiers(net, FIB_EVENT_ENTRY_ADD,
				       c, mrt->id);
	mr6_netlink_event(mrt, c, RTM_NEWROUTE);
	वापस 0;
पूर्ण

/*
 *	Close the multicast socket, and clear the vअगर tables etc
 */

अटल व्योम mroute_clean_tables(काष्ठा mr_table *mrt, पूर्णांक flags)
अणु
	काष्ठा mr_mfc *c, *पंचांगp;
	LIST_HEAD(list);
	पूर्णांक i;

	/* Shut करोwn all active vअगर entries */
	अगर (flags & (MRT6_FLUSH_MIFS | MRT6_FLUSH_MIFS_STATIC)) अणु
		क्रम (i = 0; i < mrt->maxvअगर; i++) अणु
			अगर (((mrt->vअगर_table[i].flags & VIFF_STATIC) &&
			     !(flags & MRT6_FLUSH_MIFS_STATIC)) ||
			    (!(mrt->vअगर_table[i].flags & VIFF_STATIC) && !(flags & MRT6_FLUSH_MIFS)))
				जारी;
			mअगर6_delete(mrt, i, 0, &list);
		पूर्ण
		unरेजिस्टर_netdevice_many(&list);
	पूर्ण

	/* Wipe the cache */
	अगर (flags & (MRT6_FLUSH_MFC | MRT6_FLUSH_MFC_STATIC)) अणु
		list_क्रम_each_entry_safe(c, पंचांगp, &mrt->mfc_cache_list, list) अणु
			अगर (((c->mfc_flags & MFC_STATIC) && !(flags & MRT6_FLUSH_MFC_STATIC)) ||
			    (!(c->mfc_flags & MFC_STATIC) && !(flags & MRT6_FLUSH_MFC)))
				जारी;
			rhltable_हटाओ(&mrt->mfc_hash, &c->mnode, ip6mr_rht_params);
			list_del_rcu(&c->list);
			call_ip6mr_mfc_entry_notअगरiers(पढ़ो_pnet(&mrt->net),
						       FIB_EVENT_ENTRY_DEL,
						       (काष्ठा mfc6_cache *)c, mrt->id);
			mr6_netlink_event(mrt, (काष्ठा mfc6_cache *)c, RTM_DELROUTE);
			mr_cache_put(c);
		पूर्ण
	पूर्ण

	अगर (flags & MRT6_FLUSH_MFC) अणु
		अगर (atomic_पढ़ो(&mrt->cache_resolve_queue_len) != 0) अणु
			spin_lock_bh(&mfc_unres_lock);
			list_क्रम_each_entry_safe(c, पंचांगp, &mrt->mfc_unres_queue, list) अणु
				list_del(&c->list);
				mr6_netlink_event(mrt, (काष्ठा mfc6_cache *)c,
						  RTM_DELROUTE);
				ip6mr_destroy_unres(mrt, (काष्ठा mfc6_cache *)c);
			पूर्ण
			spin_unlock_bh(&mfc_unres_lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ip6mr_sk_init(काष्ठा mr_table *mrt, काष्ठा sock *sk)
अणु
	पूर्णांक err = 0;
	काष्ठा net *net = sock_net(sk);

	rtnl_lock();
	ग_लिखो_lock_bh(&mrt_lock);
	अगर (rtnl_dereference(mrt->mroute_sk)) अणु
		err = -EADDRINUSE;
	पूर्ण अन्यथा अणु
		rcu_assign_poपूर्णांकer(mrt->mroute_sk, sk);
		sock_set_flag(sk, SOCK_RCU_FREE);
		net->ipv6.devconf_all->mc_क्रमwarding++;
	पूर्ण
	ग_लिखो_unlock_bh(&mrt_lock);

	अगर (!err)
		inet6_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
					     NETCONFA_MC_FORWARDING,
					     NETCONFA_IFINDEX_ALL,
					     net->ipv6.devconf_all);
	rtnl_unlock();

	वापस err;
पूर्ण

पूर्णांक ip6mr_sk_करोne(काष्ठा sock *sk)
अणु
	पूर्णांक err = -EACCES;
	काष्ठा net *net = sock_net(sk);
	काष्ठा mr_table *mrt;

	अगर (sk->sk_type != SOCK_RAW ||
	    inet_sk(sk)->inet_num != IPPROTO_ICMPV6)
		वापस err;

	rtnl_lock();
	ip6mr_क्रम_each_table(mrt, net) अणु
		अगर (sk == rtnl_dereference(mrt->mroute_sk)) अणु
			ग_लिखो_lock_bh(&mrt_lock);
			RCU_INIT_POINTER(mrt->mroute_sk, शून्य);
			/* Note that mroute_sk had SOCK_RCU_FREE set,
			 * so the RCU grace period beक्रमe sk मुक्तing
			 * is guaranteed by sk_deकाष्ठा()
			 */
			net->ipv6.devconf_all->mc_क्रमwarding--;
			ग_लिखो_unlock_bh(&mrt_lock);
			inet6_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						     NETCONFA_MC_FORWARDING,
						     NETCONFA_IFINDEX_ALL,
						     net->ipv6.devconf_all);

			mroute_clean_tables(mrt, MRT6_FLUSH_MIFS | MRT6_FLUSH_MFC);
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	rtnl_unlock();

	वापस err;
पूर्ण

bool mroute6_is_socket(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	काष्ठा mr_table *mrt;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_iअगर	= skb->skb_iअगर ? : LOOPBACK_IFINDEX,
		.flowi6_oअगर	= skb->dev->अगरindex,
		.flowi6_mark	= skb->mark,
	पूर्ण;

	अगर (ip6mr_fib_lookup(net, &fl6, &mrt) < 0)
		वापस शून्य;

	वापस rcu_access_poपूर्णांकer(mrt->mroute_sk);
पूर्ण
EXPORT_SYMBOL(mroute6_is_socket);

/*
 *	Socket options and भव पूर्णांकerface manipulation. The whole
 *	भव पूर्णांकerface प्रणाली is a complete heap, but unक्रमtunately
 *	that's how BSD mrouted happens to think. Maybe one day with a proper
 *	MOSPF/PIM router set up we can clean this up.
 */

पूर्णांक ip6_mroute_setsockopt(काष्ठा sock *sk, पूर्णांक optname, sockptr_t optval,
			  अचिन्हित पूर्णांक optlen)
अणु
	पूर्णांक ret, parent = 0;
	काष्ठा mअगर6ctl vअगर;
	काष्ठा mf6cctl mfc;
	mअगरi_t mअगरi;
	काष्ठा net *net = sock_net(sk);
	काष्ठा mr_table *mrt;

	अगर (sk->sk_type != SOCK_RAW ||
	    inet_sk(sk)->inet_num != IPPROTO_ICMPV6)
		वापस -EOPNOTSUPP;

	mrt = ip6mr_get_table(net, raw6_sk(sk)->ip6mr_table ? : RT6_TABLE_DFLT);
	अगर (!mrt)
		वापस -ENOENT;

	अगर (optname != MRT6_INIT) अणु
		अगर (sk != rcu_access_poपूर्णांकer(mrt->mroute_sk) &&
		    !ns_capable(net->user_ns, CAP_NET_ADMIN))
			वापस -EACCES;
	पूर्ण

	चयन (optname) अणु
	हाल MRT6_INIT:
		अगर (optlen < माप(पूर्णांक))
			वापस -EINVAL;

		वापस ip6mr_sk_init(mrt, sk);

	हाल MRT6_DONE:
		वापस ip6mr_sk_करोne(sk);

	हाल MRT6_ADD_MIF:
		अगर (optlen < माप(vअगर))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&vअगर, optval, माप(vअगर)))
			वापस -EFAULT;
		अगर (vअगर.mअगर6c_mअगरi >= MAXMIFS)
			वापस -ENखाता;
		rtnl_lock();
		ret = mअगर6_add(net, mrt, &vअगर,
			       sk == rtnl_dereference(mrt->mroute_sk));
		rtnl_unlock();
		वापस ret;

	हाल MRT6_DEL_MIF:
		अगर (optlen < माप(mअगरi_t))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&mअगरi, optval, माप(mअगरi_t)))
			वापस -EFAULT;
		rtnl_lock();
		ret = mअगर6_delete(mrt, mअगरi, 0, शून्य);
		rtnl_unlock();
		वापस ret;

	/*
	 *	Manipulate the क्रमwarding caches. These live
	 *	in a sort of kernel/user symbiosis.
	 */
	हाल MRT6_ADD_MFC:
	हाल MRT6_DEL_MFC:
		parent = -1;
		fallthrough;
	हाल MRT6_ADD_MFC_PROXY:
	हाल MRT6_DEL_MFC_PROXY:
		अगर (optlen < माप(mfc))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&mfc, optval, माप(mfc)))
			वापस -EFAULT;
		अगर (parent == 0)
			parent = mfc.mf6cc_parent;
		rtnl_lock();
		अगर (optname == MRT6_DEL_MFC || optname == MRT6_DEL_MFC_PROXY)
			ret = ip6mr_mfc_delete(mrt, &mfc, parent);
		अन्यथा
			ret = ip6mr_mfc_add(net, mrt, &mfc,
					    sk ==
					    rtnl_dereference(mrt->mroute_sk),
					    parent);
		rtnl_unlock();
		वापस ret;

	हाल MRT6_FLUSH:
	अणु
		पूर्णांक flags;

		अगर (optlen != माप(flags))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&flags, optval, माप(flags)))
			वापस -EFAULT;
		rtnl_lock();
		mroute_clean_tables(mrt, flags);
		rtnl_unlock();
		वापस 0;
	पूर्ण

	/*
	 *	Control PIM निश्चित (to activate pim will activate निश्चित)
	 */
	हाल MRT6_ASSERT:
	अणु
		पूर्णांक v;

		अगर (optlen != माप(v))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&v, optval, माप(v)))
			वापस -EFAULT;
		mrt->mroute_करो_निश्चित = v;
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	हाल MRT6_PIM:
	अणु
		पूर्णांक v;

		अगर (optlen != माप(v))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&v, optval, माप(v)))
			वापस -EFAULT;
		v = !!v;
		rtnl_lock();
		ret = 0;
		अगर (v != mrt->mroute_करो_pim) अणु
			mrt->mroute_करो_pim = v;
			mrt->mroute_करो_निश्चित = v;
		पूर्ण
		rtnl_unlock();
		वापस ret;
	पूर्ण

#पूर्ण_अगर
#अगर_घोषित CONFIG_IPV6_MROUTE_MULTIPLE_TABLES
	हाल MRT6_TABLE:
	अणु
		u32 v;

		अगर (optlen != माप(u32))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&v, optval, माप(v)))
			वापस -EFAULT;
		/* "pim6reg%u" should not exceed 16 bytes (IFNAMSIZ) */
		अगर (v != RT_TABLE_DEFAULT && v >= 100000000)
			वापस -EINVAL;
		अगर (sk == rcu_access_poपूर्णांकer(mrt->mroute_sk))
			वापस -EBUSY;

		rtnl_lock();
		ret = 0;
		mrt = ip6mr_new_table(net, v);
		अगर (IS_ERR(mrt))
			ret = PTR_ERR(mrt);
		अन्यथा
			raw6_sk(sk)->ip6mr_table = v;
		rtnl_unlock();
		वापस ret;
	पूर्ण
#पूर्ण_अगर
	/*
	 *	Spurious command, or MRT6_VERSION which you cannot
	 *	set.
	 */
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण
पूर्ण

/*
 *	Getsock opt support क्रम the multicast routing प्रणाली.
 */

पूर्णांक ip6_mroute_माला_लोockopt(काष्ठा sock *sk, पूर्णांक optname, अक्षर __user *optval,
			  पूर्णांक __user *optlen)
अणु
	पूर्णांक olr;
	पूर्णांक val;
	काष्ठा net *net = sock_net(sk);
	काष्ठा mr_table *mrt;

	अगर (sk->sk_type != SOCK_RAW ||
	    inet_sk(sk)->inet_num != IPPROTO_ICMPV6)
		वापस -EOPNOTSUPP;

	mrt = ip6mr_get_table(net, raw6_sk(sk)->ip6mr_table ? : RT6_TABLE_DFLT);
	अगर (!mrt)
		वापस -ENOENT;

	चयन (optname) अणु
	हाल MRT6_VERSION:
		val = 0x0305;
		अवरोध;
#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	हाल MRT6_PIM:
		val = mrt->mroute_करो_pim;
		अवरोध;
#पूर्ण_अगर
	हाल MRT6_ASSERT:
		val = mrt->mroute_करो_निश्चित;
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (get_user(olr, optlen))
		वापस -EFAULT;

	olr = min_t(पूर्णांक, olr, माप(पूर्णांक));
	अगर (olr < 0)
		वापस -EINVAL;

	अगर (put_user(olr, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, olr))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 *	The IP multicast ioctl support routines.
 */

पूर्णांक ip6mr_ioctl(काष्ठा sock *sk, पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा sioc_sg_req6 sr;
	काष्ठा sioc_mअगर_req6 vr;
	काष्ठा vअगर_device *vअगर;
	काष्ठा mfc6_cache *c;
	काष्ठा net *net = sock_net(sk);
	काष्ठा mr_table *mrt;

	mrt = ip6mr_get_table(net, raw6_sk(sk)->ip6mr_table ? : RT6_TABLE_DFLT);
	अगर (!mrt)
		वापस -ENOENT;

	चयन (cmd) अणु
	हाल SIOCGETMIFCNT_IN6:
		अगर (copy_from_user(&vr, arg, माप(vr)))
			वापस -EFAULT;
		अगर (vr.mअगरi >= mrt->maxvअगर)
			वापस -EINVAL;
		vr.mअगरi = array_index_nospec(vr.mअगरi, mrt->maxvअगर);
		पढ़ो_lock(&mrt_lock);
		vअगर = &mrt->vअगर_table[vr.mअगरi];
		अगर (VIF_EXISTS(mrt, vr.mअगरi)) अणु
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
	हाल SIOCGETSGCNT_IN6:
		अगर (copy_from_user(&sr, arg, माप(sr)))
			वापस -EFAULT;

		rcu_पढ़ो_lock();
		c = ip6mr_cache_find(mrt, &sr.src.sin6_addr, &sr.grp.sin6_addr);
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
काष्ठा compat_sioc_sg_req6 अणु
	काष्ठा sockaddr_in6 src;
	काष्ठा sockaddr_in6 grp;
	compat_uदीर्घ_t pktcnt;
	compat_uदीर्घ_t bytecnt;
	compat_uदीर्घ_t wrong_अगर;
पूर्ण;

काष्ठा compat_sioc_mअगर_req6 अणु
	mअगरi_t	mअगरi;
	compat_uदीर्घ_t icount;
	compat_uदीर्घ_t ocount;
	compat_uदीर्घ_t ibytes;
	compat_uदीर्घ_t obytes;
पूर्ण;

पूर्णांक ip6mr_compat_ioctl(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd, व्योम __user *arg)
अणु
	काष्ठा compat_sioc_sg_req6 sr;
	काष्ठा compat_sioc_mअगर_req6 vr;
	काष्ठा vअगर_device *vअगर;
	काष्ठा mfc6_cache *c;
	काष्ठा net *net = sock_net(sk);
	काष्ठा mr_table *mrt;

	mrt = ip6mr_get_table(net, raw6_sk(sk)->ip6mr_table ? : RT6_TABLE_DFLT);
	अगर (!mrt)
		वापस -ENOENT;

	चयन (cmd) अणु
	हाल SIOCGETMIFCNT_IN6:
		अगर (copy_from_user(&vr, arg, माप(vr)))
			वापस -EFAULT;
		अगर (vr.mअगरi >= mrt->maxvअगर)
			वापस -EINVAL;
		vr.mअगरi = array_index_nospec(vr.mअगरi, mrt->maxvअगर);
		पढ़ो_lock(&mrt_lock);
		vअगर = &mrt->vअगर_table[vr.mअगरi];
		अगर (VIF_EXISTS(mrt, vr.mअगरi)) अणु
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
	हाल SIOCGETSGCNT_IN6:
		अगर (copy_from_user(&sr, arg, माप(sr)))
			वापस -EFAULT;

		rcu_पढ़ो_lock();
		c = ip6mr_cache_find(mrt, &sr.src.sin6_addr, &sr.grp.sin6_addr);
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

अटल अंतरभूत पूर्णांक ip6mr_क्रमward2_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
		      IPSTATS_MIB_OUTFORWDATAGRAMS);
	IP6_ADD_STATS(net, ip6_dst_idev(skb_dst(skb)),
		      IPSTATS_MIB_OUTOCTETS, skb->len);
	वापस dst_output(net, sk, skb);
पूर्ण

/*
 *	Processing handlers क्रम ip6mr_क्रमward
 */

अटल पूर्णांक ip6mr_क्रमward2(काष्ठा net *net, काष्ठा mr_table *mrt,
			  काष्ठा sk_buff *skb, पूर्णांक vअगरi)
अणु
	काष्ठा ipv6hdr *ipv6h;
	काष्ठा vअगर_device *vअगर = &mrt->vअगर_table[vअगरi];
	काष्ठा net_device *dev;
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6;

	अगर (!vअगर->dev)
		जाओ out_मुक्त;

#अगर_घोषित CONFIG_IPV6_PIMSM_V2
	अगर (vअगर->flags & MIFF_REGISTER) अणु
		vअगर->pkt_out++;
		vअगर->bytes_out += skb->len;
		vअगर->dev->stats.tx_bytes += skb->len;
		vअगर->dev->stats.tx_packets++;
		ip6mr_cache_report(mrt, skb, vअगरi, MRT6MSG_WHOLEPKT);
		जाओ out_मुक्त;
	पूर्ण
#पूर्ण_अगर

	ipv6h = ipv6_hdr(skb);

	fl6 = (काष्ठा flowi6) अणु
		.flowi6_oअगर = vअगर->link,
		.daddr = ipv6h->daddr,
	पूर्ण;

	dst = ip6_route_output(net, शून्य, &fl6);
	अगर (dst->error) अणु
		dst_release(dst);
		जाओ out_मुक्त;
	पूर्ण

	skb_dst_drop(skb);
	skb_dst_set(skb, dst);

	/*
	 * RFC1584 teaches, that DVMRP/PIM router must deliver packets locally
	 * not only beक्रमe क्रमwarding, but after क्रमwarding on all output
	 * पूर्णांकerfaces. It is clear, अगर mrouter runs a multicasting
	 * program, it should receive packets not depending to what पूर्णांकerface
	 * program is joined.
	 * If we will not make it, the program will have to join on all
	 * पूर्णांकerfaces. On the other hand, multihoming host (or router, but
	 * not mrouter) cannot join to more than one पूर्णांकerface - it will
	 * result in receiving multiple packets.
	 */
	dev = vअगर->dev;
	skb->dev = dev;
	vअगर->pkt_out++;
	vअगर->bytes_out += skb->len;

	/* We are about to ग_लिखो */
	/* XXX: extension headers? */
	अगर (skb_cow(skb, माप(*ipv6h) + LL_RESERVED_SPACE(dev)))
		जाओ out_मुक्त;

	ipv6h = ipv6_hdr(skb);
	ipv6h->hop_limit--;

	IP6CB(skb)->flags |= IP6SKB_FORWARDED;

	वापस NF_HOOK(NFPROTO_IPV6, NF_INET_FORWARD,
		       net, शून्य, skb, skb->dev, dev,
		       ip6mr_क्रमward2_finish);

out_मुक्त:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक ip6mr_find_vअगर(काष्ठा mr_table *mrt, काष्ठा net_device *dev)
अणु
	पूर्णांक ct;

	क्रम (ct = mrt->maxvअगर - 1; ct >= 0; ct--) अणु
		अगर (mrt->vअगर_table[ct].dev == dev)
			अवरोध;
	पूर्ण
	वापस ct;
पूर्ण

अटल व्योम ip6_mr_क्रमward(काष्ठा net *net, काष्ठा mr_table *mrt,
			   काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			   काष्ठा mfc6_cache *c)
अणु
	पूर्णांक psend = -1;
	पूर्णांक vअगर, ct;
	पूर्णांक true_vअगरi = ip6mr_find_vअगर(mrt, dev);

	vअगर = c->_c.mfc_parent;
	c->_c.mfc_un.res.pkt++;
	c->_c.mfc_un.res.bytes += skb->len;
	c->_c.mfc_un.res.lastuse = jअगरfies;

	अगर (ipv6_addr_any(&c->mf6c_origin) && true_vअगरi >= 0) अणु
		काष्ठा mfc6_cache *cache_proxy;

		/* For an (*,G) entry, we only check that the incoming
		 * पूर्णांकerface is part of the अटल tree.
		 */
		rcu_पढ़ो_lock();
		cache_proxy = mr_mfc_find_any_parent(mrt, vअगर);
		अगर (cache_proxy &&
		    cache_proxy->_c.mfc_un.res.ttls[true_vअगरi] < 255) अणु
			rcu_पढ़ो_unlock();
			जाओ क्रमward;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	/*
	 * Wrong पूर्णांकerface: drop packet and (maybe) send PIM निश्चित.
	 */
	अगर (mrt->vअगर_table[vअगर].dev != dev) अणु
		c->_c.mfc_un.res.wrong_अगर++;

		अगर (true_vअगरi >= 0 && mrt->mroute_करो_निश्चित &&
		    /* pimsm uses निश्चितs, when चयनing from RPT to SPT,
		       so that we cannot check that packet arrived on an oअगर.
		       It is bad, but otherwise we would need to move pretty
		       large chunk of pimd to kernel. Ough... --ANK
		     */
		    (mrt->mroute_करो_pim ||
		     c->_c.mfc_un.res.ttls[true_vअगरi] < 255) &&
		    समय_after(jअगरfies,
			       c->_c.mfc_un.res.last_निश्चित +
			       MFC_ASSERT_THRESH)) अणु
			c->_c.mfc_un.res.last_निश्चित = jअगरfies;
			ip6mr_cache_report(mrt, skb, true_vअगरi, MRT6MSG_WRONGMIF);
		पूर्ण
		जाओ करोnt_क्रमward;
	पूर्ण

क्रमward:
	mrt->vअगर_table[vअगर].pkt_in++;
	mrt->vअगर_table[vअगर].bytes_in += skb->len;

	/*
	 *	Forward the frame
	 */
	अगर (ipv6_addr_any(&c->mf6c_origin) &&
	    ipv6_addr_any(&c->mf6c_mcastgrp)) अणु
		अगर (true_vअगरi >= 0 &&
		    true_vअगरi != c->_c.mfc_parent &&
		    ipv6_hdr(skb)->hop_limit >
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
		अगर ((!ipv6_addr_any(&c->mf6c_origin) || ct != true_vअगरi) &&
		    ipv6_hdr(skb)->hop_limit > c->_c.mfc_un.res.ttls[ct]) अणु
			अगर (psend != -1) अणु
				काष्ठा sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
				अगर (skb2)
					ip6mr_क्रमward2(net, mrt, skb2, psend);
			पूर्ण
			psend = ct;
		पूर्ण
	पूर्ण
last_क्रमward:
	अगर (psend != -1) अणु
		ip6mr_क्रमward2(net, mrt, skb, psend);
		वापस;
	पूर्ण

करोnt_क्रमward:
	kमुक्त_skb(skb);
पूर्ण


/*
 *	Multicast packets क्रम क्रमwarding arrive here
 */

पूर्णांक ip6_mr_input(काष्ठा sk_buff *skb)
अणु
	काष्ठा mfc6_cache *cache;
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा mr_table *mrt;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_iअगर	= skb->dev->अगरindex,
		.flowi6_mark	= skb->mark,
	पूर्ण;
	पूर्णांक err;
	काष्ठा net_device *dev;

	/* skb->dev passed in is the master dev क्रम vrfs.
	 * Get the proper पूर्णांकerface that करोes have a vअगर associated with it.
	 */
	dev = skb->dev;
	अगर (netअगर_is_l3_master(skb->dev)) अणु
		dev = dev_get_by_index_rcu(net, IPCB(skb)->iअगर);
		अगर (!dev) अणु
			kमुक्त_skb(skb);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	err = ip6mr_fib_lookup(net, &fl6, &mrt);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	पढ़ो_lock(&mrt_lock);
	cache = ip6mr_cache_find(mrt,
				 &ipv6_hdr(skb)->saddr, &ipv6_hdr(skb)->daddr);
	अगर (!cache) अणु
		पूर्णांक vअगर = ip6mr_find_vअगर(mrt, dev);

		अगर (vअगर >= 0)
			cache = ip6mr_cache_find_any(mrt,
						     &ipv6_hdr(skb)->daddr,
						     vअगर);
	पूर्ण

	/*
	 *	No usable cache entry
	 */
	अगर (!cache) अणु
		पूर्णांक vअगर;

		vअगर = ip6mr_find_vअगर(mrt, dev);
		अगर (vअगर >= 0) अणु
			पूर्णांक err = ip6mr_cache_unresolved(mrt, vअगर, skb, dev);
			पढ़ो_unlock(&mrt_lock);

			वापस err;
		पूर्ण
		पढ़ो_unlock(&mrt_lock);
		kमुक्त_skb(skb);
		वापस -ENODEV;
	पूर्ण

	ip6_mr_क्रमward(net, mrt, dev, skb, cache);

	पढ़ो_unlock(&mrt_lock);

	वापस 0;
पूर्ण

पूर्णांक ip6mr_get_route(काष्ठा net *net, काष्ठा sk_buff *skb, काष्ठा rपंचांगsg *rपंचांग,
		    u32 portid)
अणु
	पूर्णांक err;
	काष्ठा mr_table *mrt;
	काष्ठा mfc6_cache *cache;
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)skb_dst(skb);

	mrt = ip6mr_get_table(net, RT6_TABLE_DFLT);
	अगर (!mrt)
		वापस -ENOENT;

	पढ़ो_lock(&mrt_lock);
	cache = ip6mr_cache_find(mrt, &rt->rt6i_src.addr, &rt->rt6i_dst.addr);
	अगर (!cache && skb->dev) अणु
		पूर्णांक vअगर = ip6mr_find_vअगर(mrt, skb->dev);

		अगर (vअगर >= 0)
			cache = ip6mr_cache_find_any(mrt, &rt->rt6i_dst.addr,
						     vअगर);
	पूर्ण

	अगर (!cache) अणु
		काष्ठा sk_buff *skb2;
		काष्ठा ipv6hdr *iph;
		काष्ठा net_device *dev;
		पूर्णांक vअगर;

		dev = skb->dev;
		अगर (!dev || (vअगर = ip6mr_find_vअगर(mrt, dev)) < 0) अणु
			पढ़ो_unlock(&mrt_lock);
			वापस -ENODEV;
		पूर्ण

		/* really correct? */
		skb2 = alloc_skb(माप(काष्ठा ipv6hdr), GFP_ATOMIC);
		अगर (!skb2) अणु
			पढ़ो_unlock(&mrt_lock);
			वापस -ENOMEM;
		पूर्ण

		NETLINK_CB(skb2).portid = portid;
		skb_reset_transport_header(skb2);

		skb_put(skb2, माप(काष्ठा ipv6hdr));
		skb_reset_network_header(skb2);

		iph = ipv6_hdr(skb2);
		iph->version = 0;
		iph->priority = 0;
		iph->flow_lbl[0] = 0;
		iph->flow_lbl[1] = 0;
		iph->flow_lbl[2] = 0;
		iph->payload_len = 0;
		iph->nexthdr = IPPROTO_NONE;
		iph->hop_limit = 0;
		iph->saddr = rt->rt6i_src.addr;
		iph->daddr = rt->rt6i_dst.addr;

		err = ip6mr_cache_unresolved(mrt, vअगर, skb2, dev);
		पढ़ो_unlock(&mrt_lock);

		वापस err;
	पूर्ण

	err = mr_fill_mroute(mrt, skb, &cache->_c, rपंचांग);
	पढ़ो_unlock(&mrt_lock);
	वापस err;
पूर्ण

अटल पूर्णांक ip6mr_fill_mroute(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
			     u32 portid, u32 seq, काष्ठा mfc6_cache *c, पूर्णांक cmd,
			     पूर्णांक flags)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा rपंचांगsg *rपंचांग;
	पूर्णांक err;

	nlh = nlmsg_put(skb, portid, seq, cmd, माप(*rपंचांग), flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	rपंचांग = nlmsg_data(nlh);
	rपंचांग->rपंचांग_family   = RTNL_FAMILY_IP6MR;
	rपंचांग->rपंचांग_dst_len  = 128;
	rपंचांग->rपंचांग_src_len  = 128;
	rपंचांग->rपंचांग_tos      = 0;
	rपंचांग->rपंचांग_table    = mrt->id;
	अगर (nla_put_u32(skb, RTA_TABLE, mrt->id))
		जाओ nla_put_failure;
	rपंचांग->rपंचांग_type = RTN_MULTICAST;
	rपंचांग->rपंचांग_scope    = RT_SCOPE_UNIVERSE;
	अगर (c->_c.mfc_flags & MFC_STATIC)
		rपंचांग->rपंचांग_protocol = RTPROT_STATIC;
	अन्यथा
		rपंचांग->rपंचांग_protocol = RTPROT_MROUTED;
	rपंचांग->rपंचांग_flags    = 0;

	अगर (nla_put_in6_addr(skb, RTA_SRC, &c->mf6c_origin) ||
	    nla_put_in6_addr(skb, RTA_DST, &c->mf6c_mcastgrp))
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

अटल पूर्णांक _ip6mr_fill_mroute(काष्ठा mr_table *mrt, काष्ठा sk_buff *skb,
			      u32 portid, u32 seq, काष्ठा mr_mfc *c,
			      पूर्णांक cmd, पूर्णांक flags)
अणु
	वापस ip6mr_fill_mroute(mrt, skb, portid, seq, (काष्ठा mfc6_cache *)c,
				 cmd, flags);
पूर्ण

अटल पूर्णांक mr6_msgsize(bool unresolved, पूर्णांक maxvअगर)
अणु
	माप_प्रकार len =
		NLMSG_ALIGN(माप(काष्ठा rपंचांगsg))
		+ nla_total_size(4)	/* RTA_TABLE */
		+ nla_total_size(माप(काष्ठा in6_addr))	/* RTA_SRC */
		+ nla_total_size(माप(काष्ठा in6_addr))	/* RTA_DST */
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

अटल व्योम mr6_netlink_event(काष्ठा mr_table *mrt, काष्ठा mfc6_cache *mfc,
			      पूर्णांक cmd)
अणु
	काष्ठा net *net = पढ़ो_pnet(&mrt->net);
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(mr6_msgsize(mfc->_c.mfc_parent >= MAXMIFS, mrt->maxvअगर),
			GFP_ATOMIC);
	अगर (!skb)
		जाओ errout;

	err = ip6mr_fill_mroute(mrt, skb, 0, 0, mfc, cmd, 0);
	अगर (err < 0)
		जाओ errout;

	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV6_MROUTE, शून्य, GFP_ATOMIC);
	वापस;

errout:
	kमुक्त_skb(skb);
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV6_MROUTE, err);
पूर्ण

अटल माप_प्रकार mrt6msg_netlink_msgsize(माप_प्रकार payloadlen)
अणु
	माप_प्रकार len =
		NLMSG_ALIGN(माप(काष्ठा rtgenmsg))
		+ nla_total_size(1)	/* IP6MRA_CREPORT_MSGTYPE */
		+ nla_total_size(4)	/* IP6MRA_CREPORT_MIF_ID */
					/* IP6MRA_CREPORT_SRC_ADDR */
		+ nla_total_size(माप(काष्ठा in6_addr))
					/* IP6MRA_CREPORT_DST_ADDR */
		+ nla_total_size(माप(काष्ठा in6_addr))
					/* IP6MRA_CREPORT_PKT */
		+ nla_total_size(payloadlen)
		;

	वापस len;
पूर्ण

अटल व्योम mrt6msg_netlink_event(काष्ठा mr_table *mrt, काष्ठा sk_buff *pkt)
अणु
	काष्ठा net *net = पढ़ो_pnet(&mrt->net);
	काष्ठा nlmsghdr *nlh;
	काष्ठा rtgenmsg *rtgenm;
	काष्ठा mrt6msg *msg;
	काष्ठा sk_buff *skb;
	काष्ठा nlattr *nla;
	पूर्णांक payloadlen;

	payloadlen = pkt->len - माप(काष्ठा mrt6msg);
	msg = (काष्ठा mrt6msg *)skb_transport_header(pkt);

	skb = nlmsg_new(mrt6msg_netlink_msgsize(payloadlen), GFP_ATOMIC);
	अगर (!skb)
		जाओ errout;

	nlh = nlmsg_put(skb, 0, 0, RTM_NEWCACHEREPORT,
			माप(काष्ठा rtgenmsg), 0);
	अगर (!nlh)
		जाओ errout;
	rtgenm = nlmsg_data(nlh);
	rtgenm->rtgen_family = RTNL_FAMILY_IP6MR;
	अगर (nla_put_u8(skb, IP6MRA_CREPORT_MSGTYPE, msg->im6_msgtype) ||
	    nla_put_u32(skb, IP6MRA_CREPORT_MIF_ID, msg->im6_mअगर) ||
	    nla_put_in6_addr(skb, IP6MRA_CREPORT_SRC_ADDR,
			     &msg->im6_src) ||
	    nla_put_in6_addr(skb, IP6MRA_CREPORT_DST_ADDR,
			     &msg->im6_dst))
		जाओ nla_put_failure;

	nla = nla_reserve(skb, IP6MRA_CREPORT_PKT, payloadlen);
	अगर (!nla || skb_copy_bits(pkt, माप(काष्ठा mrt6msg),
				  nla_data(nla), payloadlen))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);

	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV6_MROUTE_R, शून्य, GFP_ATOMIC);
	वापस;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
errout:
	kमुक्त_skb(skb);
	rtnl_set_sk_err(net, RTNLGRP_IPV6_MROUTE_R, -ENOBUFS);
पूर्ण

अटल पूर्णांक ip6mr_rपंचांग_dumproute(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा fib_dump_filter filter = अणुपूर्ण;
	पूर्णांक err;

	अगर (cb->strict_check) अणु
		err = ip_valid_fib_dump_req(sock_net(skb->sk), nlh,
					    &filter, cb);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (filter.table_id) अणु
		काष्ठा mr_table *mrt;

		mrt = ip6mr_get_table(sock_net(skb->sk), filter.table_id);
		अगर (!mrt) अणु
			अगर (rtnl_msg_family(cb->nlh) != RTNL_FAMILY_IP6MR)
				वापस skb->len;

			NL_SET_ERR_MSG_MOD(cb->extack, "MR table does not exist");
			वापस -ENOENT;
		पूर्ण
		err = mr_table_dump(mrt, skb, cb, _ip6mr_fill_mroute,
				    &mfc_unres_lock, &filter);
		वापस skb->len ? : err;
	पूर्ण

	वापस mr_rपंचांग_dumproute(skb, cb, ip6mr_mr_table_iter,
				_ip6mr_fill_mroute, &mfc_unres_lock, &filter);
पूर्ण
