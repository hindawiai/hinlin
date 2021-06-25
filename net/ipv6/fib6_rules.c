<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/ipv6/fib6_rules.c	IPv6 Routing Policy Rules
 *
 * Copyright (C)2003-2006 Helsinki University of Technology
 * Copyright (C)2003-2006 USAGI/WIDE Project
 *
 * Authors
 *	Thomas Graf		<tgraf@suug.ch>
 *	Ville Nuorvala		<vnuorval@tcs.hut.fi>
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/export.h>
#समावेश <linux/indirect_call_wrapper.h>

#समावेश <net/fib_rules.h>
#समावेश <net/ipv6.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_route.h>
#समावेश <net/netlink.h>

काष्ठा fib6_rule अणु
	काष्ठा fib_rule		common;
	काष्ठा rt6key		src;
	काष्ठा rt6key		dst;
	u8			tclass;
पूर्ण;

अटल bool fib6_rule_matchall(स्थिर काष्ठा fib_rule *rule)
अणु
	काष्ठा fib6_rule *r = container_of(rule, काष्ठा fib6_rule, common);

	अगर (r->dst.plen || r->src.plen || r->tclass)
		वापस false;
	वापस fib_rule_matchall(rule);
पूर्ण

bool fib6_rule_शेष(स्थिर काष्ठा fib_rule *rule)
अणु
	अगर (!fib6_rule_matchall(rule) || rule->action != FR_ACT_TO_TBL ||
	    rule->l3mdev)
		वापस false;
	अगर (rule->table != RT6_TABLE_LOCAL && rule->table != RT6_TABLE_MAIN)
		वापस false;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(fib6_rule_शेष);

पूर्णांक fib6_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
		    काष्ठा netlink_ext_ack *extack)
अणु
	वापस fib_rules_dump(net, nb, AF_INET6, extack);
पूर्ण

अचिन्हित पूर्णांक fib6_rules_seq_पढ़ो(काष्ठा net *net)
अणु
	वापस fib_rules_seq_पढ़ो(net, AF_INET6);
पूर्ण

/* called with rcu lock held; no reference taken on fib6_info */
पूर्णांक fib6_lookup(काष्ठा net *net, पूर्णांक oअगर, काष्ठा flowi6 *fl6,
		काष्ठा fib6_result *res, पूर्णांक flags)
अणु
	पूर्णांक err;

	अगर (net->ipv6.fib6_has_custom_rules) अणु
		काष्ठा fib_lookup_arg arg = अणु
			.lookup_ptr = fib6_table_lookup,
			.lookup_data = &oअगर,
			.result = res,
			.flags = FIB_LOOKUP_NOREF,
		पूर्ण;

		l3mdev_update_flow(net, flowi6_to_flowi(fl6));

		err = fib_rules_lookup(net->ipv6.fib6_rules_ops,
				       flowi6_to_flowi(fl6), flags, &arg);
	पूर्ण अन्यथा अणु
		err = fib6_table_lookup(net, net->ipv6.fib6_local_tbl, oअगर,
					fl6, res, flags);
		अगर (err || res->f6i == net->ipv6.fib6_null_entry)
			err = fib6_table_lookup(net, net->ipv6.fib6_मुख्य_tbl,
						oअगर, fl6, res, flags);
	पूर्ण

	वापस err;
पूर्ण

काष्ठा dst_entry *fib6_rule_lookup(काष्ठा net *net, काष्ठा flowi6 *fl6,
				   स्थिर काष्ठा sk_buff *skb,
				   पूर्णांक flags, pol_lookup_t lookup)
अणु
	अगर (net->ipv6.fib6_has_custom_rules) अणु
		काष्ठा fib6_result res = अणुपूर्ण;
		काष्ठा fib_lookup_arg arg = अणु
			.lookup_ptr = lookup,
			.lookup_data = skb,
			.result = &res,
			.flags = FIB_LOOKUP_NOREF,
		पूर्ण;

		/* update flow अगर oअगर or iअगर poपूर्णांक to device enslaved to l3mdev */
		l3mdev_update_flow(net, flowi6_to_flowi(fl6));

		fib_rules_lookup(net->ipv6.fib6_rules_ops,
				 flowi6_to_flowi(fl6), flags, &arg);

		अगर (res.rt6)
			वापस &res.rt6->dst;
	पूर्ण अन्यथा अणु
		काष्ठा rt6_info *rt;

		rt = pol_lookup_func(lookup,
			     net, net->ipv6.fib6_local_tbl, fl6, skb, flags);
		अगर (rt != net->ipv6.ip6_null_entry && rt->dst.error != -EAGAIN)
			वापस &rt->dst;
		ip6_rt_put_flags(rt, flags);
		rt = pol_lookup_func(lookup,
			     net, net->ipv6.fib6_मुख्य_tbl, fl6, skb, flags);
		अगर (rt->dst.error != -EAGAIN)
			वापस &rt->dst;
		ip6_rt_put_flags(rt, flags);
	पूर्ण

	अगर (!(flags & RT6_LOOKUP_F_DST_NOREF))
		dst_hold(&net->ipv6.ip6_null_entry->dst);
	वापस &net->ipv6.ip6_null_entry->dst;
पूर्ण

अटल पूर्णांक fib6_rule_saddr(काष्ठा net *net, काष्ठा fib_rule *rule, पूर्णांक flags,
			   काष्ठा flowi6 *flp6, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा fib6_rule *r = (काष्ठा fib6_rule *)rule;

	/* If we need to find a source address क्रम this traffic,
	 * we check the result अगर it meets requirement of the rule.
	 */
	अगर ((rule->flags & FIB_RULE_FIND_SADDR) &&
	    r->src.plen && !(flags & RT6_LOOKUP_F_HAS_SADDR)) अणु
		काष्ठा in6_addr saddr;

		अगर (ipv6_dev_get_saddr(net, dev, &flp6->daddr,
				       rt6_flags2srcprefs(flags), &saddr))
			वापस -EAGAIN;

		अगर (!ipv6_prefix_equal(&saddr, &r->src.addr, r->src.plen))
			वापस -EAGAIN;

		flp6->saddr = saddr;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fib6_rule_action_alt(काष्ठा fib_rule *rule, काष्ठा flowi *flp,
				पूर्णांक flags, काष्ठा fib_lookup_arg *arg)
अणु
	काष्ठा fib6_result *res = arg->result;
	काष्ठा flowi6 *flp6 = &flp->u.ip6;
	काष्ठा net *net = rule->fr_net;
	काष्ठा fib6_table *table;
	पूर्णांक err, *oअगर;
	u32 tb_id;

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

	tb_id = fib_rule_get_table(rule, arg);
	table = fib6_get_table(net, tb_id);
	अगर (!table)
		वापस -EAGAIN;

	oअगर = (पूर्णांक *)arg->lookup_data;
	err = fib6_table_lookup(net, table, *oअगर, flp6, res, flags);
	अगर (!err && res->f6i != net->ipv6.fib6_null_entry)
		err = fib6_rule_saddr(net, rule, flags, flp6,
				      res->nh->fib_nh_dev);
	अन्यथा
		err = -EAGAIN;

	वापस err;
पूर्ण

अटल पूर्णांक __fib6_rule_action(काष्ठा fib_rule *rule, काष्ठा flowi *flp,
			      पूर्णांक flags, काष्ठा fib_lookup_arg *arg)
अणु
	काष्ठा fib6_result *res = arg->result;
	काष्ठा flowi6 *flp6 = &flp->u.ip6;
	काष्ठा rt6_info *rt = शून्य;
	काष्ठा fib6_table *table;
	काष्ठा net *net = rule->fr_net;
	pol_lookup_t lookup = arg->lookup_ptr;
	पूर्णांक err = 0;
	u32 tb_id;

	चयन (rule->action) अणु
	हाल FR_ACT_TO_TBL:
		अवरोध;
	हाल FR_ACT_UNREACHABLE:
		err = -ENETUNREACH;
		rt = net->ipv6.ip6_null_entry;
		जाओ discard_pkt;
	शेष:
	हाल FR_ACT_BLACKHOLE:
		err = -EINVAL;
		rt = net->ipv6.ip6_blk_hole_entry;
		जाओ discard_pkt;
	हाल FR_ACT_PROHIBIT:
		err = -EACCES;
		rt = net->ipv6.ip6_prohibit_entry;
		जाओ discard_pkt;
	पूर्ण

	tb_id = fib_rule_get_table(rule, arg);
	table = fib6_get_table(net, tb_id);
	अगर (!table) अणु
		err = -EAGAIN;
		जाओ out;
	पूर्ण

	rt = pol_lookup_func(lookup,
			     net, table, flp6, arg->lookup_data, flags);
	अगर (rt != net->ipv6.ip6_null_entry) अणु
		err = fib6_rule_saddr(net, rule, flags, flp6,
				      ip6_dst_idev(&rt->dst)->dev);

		अगर (err == -EAGAIN)
			जाओ again;

		err = rt->dst.error;
		अगर (err != -EAGAIN)
			जाओ out;
	पूर्ण
again:
	ip6_rt_put_flags(rt, flags);
	err = -EAGAIN;
	rt = शून्य;
	जाओ out;

discard_pkt:
	अगर (!(flags & RT6_LOOKUP_F_DST_NOREF))
		dst_hold(&rt->dst);
out:
	res->rt6 = rt;
	वापस err;
पूर्ण

INसूचीECT_CALLABLE_SCOPE पूर्णांक fib6_rule_action(काष्ठा fib_rule *rule,
					     काष्ठा flowi *flp, पूर्णांक flags,
					     काष्ठा fib_lookup_arg *arg)
अणु
	अगर (arg->lookup_ptr == fib6_table_lookup)
		वापस fib6_rule_action_alt(rule, flp, flags, arg);

	वापस __fib6_rule_action(rule, flp, flags, arg);
पूर्ण

INसूचीECT_CALLABLE_SCOPE bool fib6_rule_suppress(काष्ठा fib_rule *rule,
						काष्ठा fib_lookup_arg *arg)
अणु
	काष्ठा fib6_result *res = arg->result;
	काष्ठा rt6_info *rt = res->rt6;
	काष्ठा net_device *dev = शून्य;

	अगर (!rt)
		वापस false;

	अगर (rt->rt6i_idev)
		dev = rt->rt6i_idev->dev;

	/* करो not accept result अगर the route करोes
	 * not meet the required prefix length
	 */
	अगर (rt->rt6i_dst.plen <= rule->suppress_prefixlen)
		जाओ suppress_route;

	/* करो not accept result अगर the route uses a device
	 * beदीर्घing to a क्रमbidden पूर्णांकerface group
	 */
	अगर (rule->suppress_अगरgroup != -1 && dev && dev->group == rule->suppress_अगरgroup)
		जाओ suppress_route;

	वापस false;

suppress_route:
	अगर (!(arg->flags & FIB_LOOKUP_NOREF))
		ip6_rt_put(rt);
	वापस true;
पूर्ण

INसूचीECT_CALLABLE_SCOPE पूर्णांक fib6_rule_match(काष्ठा fib_rule *rule,
					    काष्ठा flowi *fl, पूर्णांक flags)
अणु
	काष्ठा fib6_rule *r = (काष्ठा fib6_rule *) rule;
	काष्ठा flowi6 *fl6 = &fl->u.ip6;

	अगर (r->dst.plen &&
	    !ipv6_prefix_equal(&fl6->daddr, &r->dst.addr, r->dst.plen))
		वापस 0;

	/*
	 * If FIB_RULE_FIND_SADDR is set and we करो not have a
	 * source address क्रम the traffic, we defer check क्रम
	 * source address.
	 */
	अगर (r->src.plen) अणु
		अगर (flags & RT6_LOOKUP_F_HAS_SADDR) अणु
			अगर (!ipv6_prefix_equal(&fl6->saddr, &r->src.addr,
					       r->src.plen))
				वापस 0;
		पूर्ण अन्यथा अगर (!(r->common.flags & FIB_RULE_FIND_SADDR))
			वापस 0;
	पूर्ण

	अगर (r->tclass && r->tclass != ip6_tclass(fl6->flowlabel))
		वापस 0;

	अगर (rule->ip_proto && (rule->ip_proto != fl6->flowi6_proto))
		वापस 0;

	अगर (fib_rule_port_range_set(&rule->sport_range) &&
	    !fib_rule_port_inrange(&rule->sport_range, fl6->fl6_sport))
		वापस 0;

	अगर (fib_rule_port_range_set(&rule->dport_range) &&
	    !fib_rule_port_inrange(&rule->dport_range, fl6->fl6_dport))
		वापस 0;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा nla_policy fib6_rule_policy[FRA_MAX+1] = अणु
	FRA_GENERIC_POLICY,
पूर्ण;

अटल पूर्णांक fib6_rule_configure(काष्ठा fib_rule *rule, काष्ठा sk_buff *skb,
			       काष्ठा fib_rule_hdr *frh,
			       काष्ठा nlattr **tb,
			       काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा fib6_rule *rule6 = (काष्ठा fib6_rule *) rule;

	अगर (rule->action == FR_ACT_TO_TBL && !rule->l3mdev) अणु
		अगर (rule->table == RT6_TABLE_UNSPEC) अणु
			NL_SET_ERR_MSG(extack, "Invalid table");
			जाओ errout;
		पूर्ण

		अगर (fib6_new_table(net, rule->table) == शून्य) अणु
			err = -ENOBUFS;
			जाओ errout;
		पूर्ण
	पूर्ण

	अगर (frh->src_len)
		rule6->src.addr = nla_get_in6_addr(tb[FRA_SRC]);

	अगर (frh->dst_len)
		rule6->dst.addr = nla_get_in6_addr(tb[FRA_DST]);

	rule6->src.plen = frh->src_len;
	rule6->dst.plen = frh->dst_len;
	rule6->tclass = frh->tos;

	अगर (fib_rule_requires_fldissect(rule))
		net->ipv6.fib6_rules_require_fldissect++;

	net->ipv6.fib6_has_custom_rules = true;
	err = 0;
errout:
	वापस err;
पूर्ण

अटल पूर्णांक fib6_rule_delete(काष्ठा fib_rule *rule)
अणु
	काष्ठा net *net = rule->fr_net;

	अगर (net->ipv6.fib6_rules_require_fldissect &&
	    fib_rule_requires_fldissect(rule))
		net->ipv6.fib6_rules_require_fldissect--;

	वापस 0;
पूर्ण

अटल पूर्णांक fib6_rule_compare(काष्ठा fib_rule *rule, काष्ठा fib_rule_hdr *frh,
			     काष्ठा nlattr **tb)
अणु
	काष्ठा fib6_rule *rule6 = (काष्ठा fib6_rule *) rule;

	अगर (frh->src_len && (rule6->src.plen != frh->src_len))
		वापस 0;

	अगर (frh->dst_len && (rule6->dst.plen != frh->dst_len))
		वापस 0;

	अगर (frh->tos && (rule6->tclass != frh->tos))
		वापस 0;

	अगर (frh->src_len &&
	    nla_स_भेद(tb[FRA_SRC], &rule6->src.addr, माप(काष्ठा in6_addr)))
		वापस 0;

	अगर (frh->dst_len &&
	    nla_स_भेद(tb[FRA_DST], &rule6->dst.addr, माप(काष्ठा in6_addr)))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक fib6_rule_fill(काष्ठा fib_rule *rule, काष्ठा sk_buff *skb,
			  काष्ठा fib_rule_hdr *frh)
अणु
	काष्ठा fib6_rule *rule6 = (काष्ठा fib6_rule *) rule;

	frh->dst_len = rule6->dst.plen;
	frh->src_len = rule6->src.plen;
	frh->tos = rule6->tclass;

	अगर ((rule6->dst.plen &&
	     nla_put_in6_addr(skb, FRA_DST, &rule6->dst.addr)) ||
	    (rule6->src.plen &&
	     nla_put_in6_addr(skb, FRA_SRC, &rule6->src.addr)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -ENOBUFS;
पूर्ण

अटल माप_प्रकार fib6_rule_nlmsg_payload(काष्ठा fib_rule *rule)
अणु
	वापस nla_total_size(16) /* dst */
	       + nla_total_size(16); /* src */
पूर्ण

अटल स्थिर काष्ठा fib_rules_ops __net_initस्थिर fib6_rules_ops_ढाँचा = अणु
	.family			= AF_INET6,
	.rule_size		= माप(काष्ठा fib6_rule),
	.addr_size		= माप(काष्ठा in6_addr),
	.action			= fib6_rule_action,
	.match			= fib6_rule_match,
	.suppress		= fib6_rule_suppress,
	.configure		= fib6_rule_configure,
	.delete			= fib6_rule_delete,
	.compare		= fib6_rule_compare,
	.fill			= fib6_rule_fill,
	.nlmsg_payload		= fib6_rule_nlmsg_payload,
	.nlgroup		= RTNLGRP_IPV6_RULE,
	.policy			= fib6_rule_policy,
	.owner			= THIS_MODULE,
	.fro_net		= &init_net,
पूर्ण;

अटल पूर्णांक __net_init fib6_rules_net_init(काष्ठा net *net)
अणु
	काष्ठा fib_rules_ops *ops;
	पूर्णांक err = -ENOMEM;

	ops = fib_rules_रेजिस्टर(&fib6_rules_ops_ढाँचा, net);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);

	err = fib_शेष_rule_add(ops, 0, RT6_TABLE_LOCAL, 0);
	अगर (err)
		जाओ out_fib6_rules_ops;

	err = fib_शेष_rule_add(ops, 0x7FFE, RT6_TABLE_MAIN, 0);
	अगर (err)
		जाओ out_fib6_rules_ops;

	net->ipv6.fib6_rules_ops = ops;
	net->ipv6.fib6_rules_require_fldissect = 0;
out:
	वापस err;

out_fib6_rules_ops:
	fib_rules_unरेजिस्टर(ops);
	जाओ out;
पूर्ण

अटल व्योम __net_निकास fib6_rules_net_निकास(काष्ठा net *net)
अणु
	rtnl_lock();
	fib_rules_unरेजिस्टर(net->ipv6.fib6_rules_ops);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations fib6_rules_net_ops = अणु
	.init = fib6_rules_net_init,
	.निकास = fib6_rules_net_निकास,
पूर्ण;

पूर्णांक __init fib6_rules_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&fib6_rules_net_ops);
पूर्ण


व्योम fib6_rules_cleanup(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&fib6_rules_net_ops);
पूर्ण
