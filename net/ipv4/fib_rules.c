<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		IPv4 Forwarding Inक्रमmation Base: policy rules.
 *
 * Authors:	Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *		Thomas Graf <tgraf@suug.ch>
 *
 * Fixes:
 *		Rani Assaf	:	local_rule cannot be deleted
 *		Marc Boucher	:	routing by fwmark
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/export.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/tcp.h>
#समावेश <net/ip_fib.h>
#समावेश <net/nexthop.h>
#समावेश <net/fib_rules.h>
#समावेश <linux/indirect_call_wrapper.h>

काष्ठा fib4_rule अणु
	काष्ठा fib_rule		common;
	u8			dst_len;
	u8			src_len;
	u8			tos;
	__be32			src;
	__be32			srcmask;
	__be32			dst;
	__be32			dsपंचांगask;
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	u32			tclassid;
#पूर्ण_अगर
पूर्ण;

अटल bool fib4_rule_matchall(स्थिर काष्ठा fib_rule *rule)
अणु
	काष्ठा fib4_rule *r = container_of(rule, काष्ठा fib4_rule, common);

	अगर (r->dst_len || r->src_len || r->tos)
		वापस false;
	वापस fib_rule_matchall(rule);
पूर्ण

bool fib4_rule_शेष(स्थिर काष्ठा fib_rule *rule)
अणु
	अगर (!fib4_rule_matchall(rule) || rule->action != FR_ACT_TO_TBL ||
	    rule->l3mdev)
		वापस false;
	अगर (rule->table != RT_TABLE_LOCAL && rule->table != RT_TABLE_MAIN &&
	    rule->table != RT_TABLE_DEFAULT)
		वापस false;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(fib4_rule_शेष);

पूर्णांक fib4_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
		    काष्ठा netlink_ext_ack *extack)
अणु
	वापस fib_rules_dump(net, nb, AF_INET, extack);
पूर्ण

अचिन्हित पूर्णांक fib4_rules_seq_पढ़ो(काष्ठा net *net)
अणु
	वापस fib_rules_seq_पढ़ो(net, AF_INET);
पूर्ण

पूर्णांक __fib_lookup(काष्ठा net *net, काष्ठा flowi4 *flp,
		 काष्ठा fib_result *res, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fib_lookup_arg arg = अणु
		.result = res,
		.flags = flags,
	पूर्ण;
	पूर्णांक err;

	/* update flow अगर oअगर or iअगर poपूर्णांक to device enslaved to l3mdev */
	l3mdev_update_flow(net, flowi4_to_flowi(flp));

	err = fib_rules_lookup(net->ipv4.rules_ops, flowi4_to_flowi(flp), 0, &arg);
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	अगर (arg.rule)
		res->tclassid = ((काष्ठा fib4_rule *)arg.rule)->tclassid;
	अन्यथा
		res->tclassid = 0;
#पूर्ण_अगर

	अगर (err == -ESRCH)
		err = -ENETUNREACH;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__fib_lookup);

INसूचीECT_CALLABLE_SCOPE पूर्णांक fib4_rule_action(काष्ठा fib_rule *rule,
					     काष्ठा flowi *flp, पूर्णांक flags,
					     काष्ठा fib_lookup_arg *arg)
अणु
	पूर्णांक err = -EAGAIN;
	काष्ठा fib_table *tbl;
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

	rcu_पढ़ो_lock();

	tb_id = fib_rule_get_table(rule, arg);
	tbl = fib_get_table(rule->fr_net, tb_id);
	अगर (tbl)
		err = fib_table_lookup(tbl, &flp->u.ip4,
				       (काष्ठा fib_result *)arg->result,
				       arg->flags);

	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

INसूचीECT_CALLABLE_SCOPE bool fib4_rule_suppress(काष्ठा fib_rule *rule,
						काष्ठा fib_lookup_arg *arg)
अणु
	काष्ठा fib_result *result = (काष्ठा fib_result *) arg->result;
	काष्ठा net_device *dev = शून्य;

	अगर (result->fi) अणु
		काष्ठा fib_nh_common *nhc = fib_info_nhc(result->fi, 0);

		dev = nhc->nhc_dev;
	पूर्ण

	/* करो not accept result अगर the route करोes
	 * not meet the required prefix length
	 */
	अगर (result->prefixlen <= rule->suppress_prefixlen)
		जाओ suppress_route;

	/* करो not accept result अगर the route uses a device
	 * beदीर्घing to a क्रमbidden पूर्णांकerface group
	 */
	अगर (rule->suppress_अगरgroup != -1 && dev && dev->group == rule->suppress_अगरgroup)
		जाओ suppress_route;

	वापस false;

suppress_route:
	अगर (!(arg->flags & FIB_LOOKUP_NOREF))
		fib_info_put(result->fi);
	वापस true;
पूर्ण

INसूचीECT_CALLABLE_SCOPE पूर्णांक fib4_rule_match(काष्ठा fib_rule *rule,
					    काष्ठा flowi *fl, पूर्णांक flags)
अणु
	काष्ठा fib4_rule *r = (काष्ठा fib4_rule *) rule;
	काष्ठा flowi4 *fl4 = &fl->u.ip4;
	__be32 daddr = fl4->daddr;
	__be32 saddr = fl4->saddr;

	अगर (((saddr ^ r->src) & r->srcmask) ||
	    ((daddr ^ r->dst) & r->dsपंचांगask))
		वापस 0;

	अगर (r->tos && (r->tos != fl4->flowi4_tos))
		वापस 0;

	अगर (rule->ip_proto && (rule->ip_proto != fl4->flowi4_proto))
		वापस 0;

	अगर (fib_rule_port_range_set(&rule->sport_range) &&
	    !fib_rule_port_inrange(&rule->sport_range, fl4->fl4_sport))
		वापस 0;

	अगर (fib_rule_port_range_set(&rule->dport_range) &&
	    !fib_rule_port_inrange(&rule->dport_range, fl4->fl4_dport))
		वापस 0;

	वापस 1;
पूर्ण

अटल काष्ठा fib_table *fib_empty_table(काष्ठा net *net)
अणु
	u32 id = 1;

	जबतक (1) अणु
		अगर (!fib_get_table(net, id))
			वापस fib_new_table(net, id);

		अगर (id++ == RT_TABLE_MAX)
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा nla_policy fib4_rule_policy[FRA_MAX+1] = अणु
	FRA_GENERIC_POLICY,
	[FRA_FLOW]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक fib4_rule_configure(काष्ठा fib_rule *rule, काष्ठा sk_buff *skb,
			       काष्ठा fib_rule_hdr *frh,
			       काष्ठा nlattr **tb,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक err = -EINVAL;
	काष्ठा fib4_rule *rule4 = (काष्ठा fib4_rule *) rule;

	अगर (frh->tos & ~IPTOS_TOS_MASK) अणु
		NL_SET_ERR_MSG(extack, "Invalid tos");
		जाओ errout;
	पूर्ण

	/* split local/मुख्य अगर they are not alपढ़ोy split */
	err = fib_unmerge(net);
	अगर (err)
		जाओ errout;

	अगर (rule->table == RT_TABLE_UNSPEC && !rule->l3mdev) अणु
		अगर (rule->action == FR_ACT_TO_TBL) अणु
			काष्ठा fib_table *table;

			table = fib_empty_table(net);
			अगर (!table) अणु
				err = -ENOBUFS;
				जाओ errout;
			पूर्ण

			rule->table = table->tb_id;
		पूर्ण
	पूर्ण

	अगर (frh->src_len)
		rule4->src = nla_get_in_addr(tb[FRA_SRC]);

	अगर (frh->dst_len)
		rule4->dst = nla_get_in_addr(tb[FRA_DST]);

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	अगर (tb[FRA_FLOW]) अणु
		rule4->tclassid = nla_get_u32(tb[FRA_FLOW]);
		अगर (rule4->tclassid)
			net->ipv4.fib_num_tclassid_users++;
	पूर्ण
#पूर्ण_अगर

	अगर (fib_rule_requires_fldissect(rule))
		net->ipv4.fib_rules_require_fldissect++;

	rule4->src_len = frh->src_len;
	rule4->srcmask = inet_make_mask(rule4->src_len);
	rule4->dst_len = frh->dst_len;
	rule4->dsपंचांगask = inet_make_mask(rule4->dst_len);
	rule4->tos = frh->tos;

	net->ipv4.fib_has_custom_rules = true;

	err = 0;
errout:
	वापस err;
पूर्ण

अटल पूर्णांक fib4_rule_delete(काष्ठा fib_rule *rule)
अणु
	काष्ठा net *net = rule->fr_net;
	पूर्णांक err;

	/* split local/मुख्य अगर they are not alपढ़ोy split */
	err = fib_unmerge(net);
	अगर (err)
		जाओ errout;

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	अगर (((काष्ठा fib4_rule *)rule)->tclassid)
		net->ipv4.fib_num_tclassid_users--;
#पूर्ण_अगर
	net->ipv4.fib_has_custom_rules = true;

	अगर (net->ipv4.fib_rules_require_fldissect &&
	    fib_rule_requires_fldissect(rule))
		net->ipv4.fib_rules_require_fldissect--;
errout:
	वापस err;
पूर्ण

अटल पूर्णांक fib4_rule_compare(काष्ठा fib_rule *rule, काष्ठा fib_rule_hdr *frh,
			     काष्ठा nlattr **tb)
अणु
	काष्ठा fib4_rule *rule4 = (काष्ठा fib4_rule *) rule;

	अगर (frh->src_len && (rule4->src_len != frh->src_len))
		वापस 0;

	अगर (frh->dst_len && (rule4->dst_len != frh->dst_len))
		वापस 0;

	अगर (frh->tos && (rule4->tos != frh->tos))
		वापस 0;

#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	अगर (tb[FRA_FLOW] && (rule4->tclassid != nla_get_u32(tb[FRA_FLOW])))
		वापस 0;
#पूर्ण_अगर

	अगर (frh->src_len && (rule4->src != nla_get_in_addr(tb[FRA_SRC])))
		वापस 0;

	अगर (frh->dst_len && (rule4->dst != nla_get_in_addr(tb[FRA_DST])))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक fib4_rule_fill(काष्ठा fib_rule *rule, काष्ठा sk_buff *skb,
			  काष्ठा fib_rule_hdr *frh)
अणु
	काष्ठा fib4_rule *rule4 = (काष्ठा fib4_rule *) rule;

	frh->dst_len = rule4->dst_len;
	frh->src_len = rule4->src_len;
	frh->tos = rule4->tos;

	अगर ((rule4->dst_len &&
	     nla_put_in_addr(skb, FRA_DST, rule4->dst)) ||
	    (rule4->src_len &&
	     nla_put_in_addr(skb, FRA_SRC, rule4->src)))
		जाओ nla_put_failure;
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	अगर (rule4->tclassid &&
	    nla_put_u32(skb, FRA_FLOW, rule4->tclassid))
		जाओ nla_put_failure;
#पूर्ण_अगर
	वापस 0;

nla_put_failure:
	वापस -ENOBUFS;
पूर्ण

अटल माप_प्रकार fib4_rule_nlmsg_payload(काष्ठा fib_rule *rule)
अणु
	वापस nla_total_size(4) /* dst */
	       + nla_total_size(4) /* src */
	       + nla_total_size(4); /* flow */
पूर्ण

अटल व्योम fib4_rule_flush_cache(काष्ठा fib_rules_ops *ops)
अणु
	rt_cache_flush(ops->fro_net);
पूर्ण

अटल स्थिर काष्ठा fib_rules_ops __net_initस्थिर fib4_rules_ops_ढाँचा = अणु
	.family		= AF_INET,
	.rule_size	= माप(काष्ठा fib4_rule),
	.addr_size	= माप(u32),
	.action		= fib4_rule_action,
	.suppress	= fib4_rule_suppress,
	.match		= fib4_rule_match,
	.configure	= fib4_rule_configure,
	.delete		= fib4_rule_delete,
	.compare	= fib4_rule_compare,
	.fill		= fib4_rule_fill,
	.nlmsg_payload	= fib4_rule_nlmsg_payload,
	.flush_cache	= fib4_rule_flush_cache,
	.nlgroup	= RTNLGRP_IPV4_RULE,
	.policy		= fib4_rule_policy,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक fib_शेष_rules_init(काष्ठा fib_rules_ops *ops)
अणु
	पूर्णांक err;

	err = fib_शेष_rule_add(ops, 0, RT_TABLE_LOCAL, 0);
	अगर (err < 0)
		वापस err;
	err = fib_शेष_rule_add(ops, 0x7FFE, RT_TABLE_MAIN, 0);
	अगर (err < 0)
		वापस err;
	err = fib_शेष_rule_add(ops, 0x7FFF, RT_TABLE_DEFAULT, 0);
	अगर (err < 0)
		वापस err;
	वापस 0;
पूर्ण

पूर्णांक __net_init fib4_rules_init(काष्ठा net *net)
अणु
	पूर्णांक err;
	काष्ठा fib_rules_ops *ops;

	ops = fib_rules_रेजिस्टर(&fib4_rules_ops_ढाँचा, net);
	अगर (IS_ERR(ops))
		वापस PTR_ERR(ops);

	err = fib_शेष_rules_init(ops);
	अगर (err < 0)
		जाओ fail;
	net->ipv4.rules_ops = ops;
	net->ipv4.fib_has_custom_rules = false;
	net->ipv4.fib_rules_require_fldissect = 0;
	वापस 0;

fail:
	/* also cleans all rules alपढ़ोy added */
	fib_rules_unरेजिस्टर(ops);
	वापस err;
पूर्ण

व्योम __net_निकास fib4_rules_निकास(काष्ठा net *net)
अणु
	fib_rules_unरेजिस्टर(net->ipv4.rules_ops);
पूर्ण
