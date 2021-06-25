<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * DECnet       An implementation of the DECnet protocol suite क्रम the LINUX
 *              operating प्रणाली.  DECnet is implemented using the  BSD Socket
 *              पूर्णांकerface as the means of communication with the user level.
 *
 *              DECnet Routing Forwarding Inक्रमmation Base (Rules)
 *
 * Author:      Steve Whitehouse <SteveW@ACM.org>
 *              Mostly copied from Alexey Kuznetsov's ipv4/fib_rules.c
 *
 *
 * Changes:
 *              Steve Whitehouse <steve@chygwyn.com>
 *              Updated क्रम Thomas Graf's generic rules
 *
 */
#समावेश <linux/net.h>
#समावेश <linux/init.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/export.h>
#समावेश <net/neighbour.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/fib_rules.h>
#समावेश <net/dn.h>
#समावेश <net/dn_fib.h>
#समावेश <net/dn_neigh.h>
#समावेश <net/dn_dev.h>
#समावेश <net/dn_route.h>

अटल काष्ठा fib_rules_ops *dn_fib_rules_ops;

काष्ठा dn_fib_rule
अणु
	काष्ठा fib_rule		common;
	अचिन्हित अक्षर		dst_len;
	अचिन्हित अक्षर		src_len;
	__le16			src;
	__le16			srcmask;
	__le16			dst;
	__le16			dsपंचांगask;
	__le16			srcmap;
	u8			flags;
पूर्ण;


पूर्णांक dn_fib_lookup(काष्ठा flowidn *flp, काष्ठा dn_fib_res *res)
अणु
	काष्ठा fib_lookup_arg arg = अणु
		.result = res,
	पूर्ण;
	पूर्णांक err;

	err = fib_rules_lookup(dn_fib_rules_ops,
			       flowidn_to_flowi(flp), 0, &arg);
	res->r = arg.rule;

	वापस err;
पूर्ण

अटल पूर्णांक dn_fib_rule_action(काष्ठा fib_rule *rule, काष्ठा flowi *flp,
			      पूर्णांक flags, काष्ठा fib_lookup_arg *arg)
अणु
	काष्ठा flowidn *fld = &flp->u.dn;
	पूर्णांक err = -EAGAIN;
	काष्ठा dn_fib_table *tbl;

	चयन(rule->action) अणु
	हाल FR_ACT_TO_TBL:
		अवरोध;

	हाल FR_ACT_UNREACHABLE:
		err = -ENETUNREACH;
		जाओ errout;

	हाल FR_ACT_PROHIBIT:
		err = -EACCES;
		जाओ errout;

	हाल FR_ACT_BLACKHOLE:
	शेष:
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	tbl = dn_fib_get_table(rule->table, 0);
	अगर (tbl == शून्य)
		जाओ errout;

	err = tbl->lookup(tbl, fld, (काष्ठा dn_fib_res *)arg->result);
	अगर (err > 0)
		err = -EAGAIN;
errout:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy dn_fib_rule_policy[FRA_MAX+1] = अणु
	FRA_GENERIC_POLICY,
पूर्ण;

अटल पूर्णांक dn_fib_rule_match(काष्ठा fib_rule *rule, काष्ठा flowi *fl, पूर्णांक flags)
अणु
	काष्ठा dn_fib_rule *r = (काष्ठा dn_fib_rule *)rule;
	काष्ठा flowidn *fld = &fl->u.dn;
	__le16 daddr = fld->daddr;
	__le16 saddr = fld->saddr;

	अगर (((saddr ^ r->src) & r->srcmask) ||
	    ((daddr ^ r->dst) & r->dsपंचांगask))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक dn_fib_rule_configure(काष्ठा fib_rule *rule, काष्ठा sk_buff *skb,
				 काष्ठा fib_rule_hdr *frh,
				 काष्ठा nlattr **tb,
				 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा dn_fib_rule *r = (काष्ठा dn_fib_rule *)rule;

	अगर (frh->tos) अणु
		NL_SET_ERR_MSG(extack, "Invalid tos value");
		जाओ  errout;
	पूर्ण

	अगर (rule->table == RT_TABLE_UNSPEC) अणु
		अगर (rule->action == FR_ACT_TO_TBL) अणु
			काष्ठा dn_fib_table *table;

			table = dn_fib_empty_table();
			अगर (table == शून्य) अणु
				err = -ENOBUFS;
				जाओ errout;
			पूर्ण

			rule->table = table->n;
		पूर्ण
	पूर्ण

	अगर (frh->src_len)
		r->src = nla_get_le16(tb[FRA_SRC]);

	अगर (frh->dst_len)
		r->dst = nla_get_le16(tb[FRA_DST]);

	r->src_len = frh->src_len;
	r->srcmask = dnet_make_mask(r->src_len);
	r->dst_len = frh->dst_len;
	r->dsपंचांगask = dnet_make_mask(r->dst_len);
	err = 0;
errout:
	वापस err;
पूर्ण

अटल पूर्णांक dn_fib_rule_compare(काष्ठा fib_rule *rule, काष्ठा fib_rule_hdr *frh,
			       काष्ठा nlattr **tb)
अणु
	काष्ठा dn_fib_rule *r = (काष्ठा dn_fib_rule *)rule;

	अगर (frh->src_len && (r->src_len != frh->src_len))
		वापस 0;

	अगर (frh->dst_len && (r->dst_len != frh->dst_len))
		वापस 0;

	अगर (frh->src_len && (r->src != nla_get_le16(tb[FRA_SRC])))
		वापस 0;

	अगर (frh->dst_len && (r->dst != nla_get_le16(tb[FRA_DST])))
		वापस 0;

	वापस 1;
पूर्ण

अचिन्हित पूर्णांक dnet_addr_type(__le16 addr)
अणु
	काष्ठा flowidn fld = अणु .daddr = addr पूर्ण;
	काष्ठा dn_fib_res res;
	अचिन्हित पूर्णांक ret = RTN_UNICAST;
	काष्ठा dn_fib_table *tb = dn_fib_get_table(RT_TABLE_LOCAL, 0);

	res.r = शून्य;

	अगर (tb) अणु
		अगर (!tb->lookup(tb, &fld, &res)) अणु
			ret = res.type;
			dn_fib_res_put(&res);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक dn_fib_rule_fill(काष्ठा fib_rule *rule, काष्ठा sk_buff *skb,
			    काष्ठा fib_rule_hdr *frh)
अणु
	काष्ठा dn_fib_rule *r = (काष्ठा dn_fib_rule *)rule;

	frh->dst_len = r->dst_len;
	frh->src_len = r->src_len;
	frh->tos = 0;

	अगर ((r->dst_len &&
	     nla_put_le16(skb, FRA_DST, r->dst)) ||
	    (r->src_len &&
	     nla_put_le16(skb, FRA_SRC, r->src)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -ENOBUFS;
पूर्ण

अटल व्योम dn_fib_rule_flush_cache(काष्ठा fib_rules_ops *ops)
अणु
	dn_rt_cache_flush(-1);
पूर्ण

अटल स्थिर काष्ठा fib_rules_ops __net_initस्थिर dn_fib_rules_ops_ढाँचा = अणु
	.family		= AF_DECnet,
	.rule_size	= माप(काष्ठा dn_fib_rule),
	.addr_size	= माप(u16),
	.action		= dn_fib_rule_action,
	.match		= dn_fib_rule_match,
	.configure	= dn_fib_rule_configure,
	.compare	= dn_fib_rule_compare,
	.fill		= dn_fib_rule_fill,
	.flush_cache	= dn_fib_rule_flush_cache,
	.nlgroup	= RTNLGRP_DECnet_RULE,
	.policy		= dn_fib_rule_policy,
	.owner		= THIS_MODULE,
	.fro_net	= &init_net,
पूर्ण;

व्योम __init dn_fib_rules_init(व्योम)
अणु
	dn_fib_rules_ops =
		fib_rules_रेजिस्टर(&dn_fib_rules_ops_ढाँचा, &init_net);
	BUG_ON(IS_ERR(dn_fib_rules_ops));
	BUG_ON(fib_शेष_rule_add(dn_fib_rules_ops, 0x7fff,
			            RT_TABLE_MAIN, 0));
पूर्ण

व्योम __निकास dn_fib_rules_cleanup(व्योम)
अणु
	rtnl_lock();
	fib_rules_unरेजिस्टर(dn_fib_rules_ops);
	rtnl_unlock();
	rcu_barrier();
पूर्ण
