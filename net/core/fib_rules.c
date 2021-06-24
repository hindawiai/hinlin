<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/core/fib_rules.c		Generic Routing Rules
 *
 * Authors:	Thomas Graf <tgraf@suug.ch>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/fib_rules.h>
#समावेश <net/ip_tunnels.h>
#समावेश <linux/indirect_call_wrapper.h>

#अगर defined(CONFIG_IPV6) && defined(CONFIG_IPV6_MULTIPLE_TABLES)
#अगर_घोषित CONFIG_IP_MULTIPLE_TABLES
#घोषणा INसूचीECT_CALL_MT(f, f2, f1, ...) \
	INसूचीECT_CALL_INET(f, f2, f1, __VA_ARGS__)
#अन्यथा
#घोषणा INसूचीECT_CALL_MT(f, f2, f1, ...) INसूचीECT_CALL_1(f, f2, __VA_ARGS__)
#पूर्ण_अगर
#या_अगर defined(CONFIG_IP_MULTIPLE_TABLES)
#घोषणा INसूचीECT_CALL_MT(f, f2, f1, ...) INसूचीECT_CALL_1(f, f1, __VA_ARGS__)
#अन्यथा
#घोषणा INसूचीECT_CALL_MT(f, f2, f1, ...) f(__VA_ARGS__)
#पूर्ण_अगर

अटल स्थिर काष्ठा fib_kuid_range fib_kuid_range_unset = अणु
	KUIDT_INIT(0),
	KUIDT_INIT(~0),
पूर्ण;

bool fib_rule_matchall(स्थिर काष्ठा fib_rule *rule)
अणु
	अगर (rule->iअगरindex || rule->oअगरindex || rule->mark || rule->tun_id ||
	    rule->flags)
		वापस false;
	अगर (rule->suppress_अगरgroup != -1 || rule->suppress_prefixlen != -1)
		वापस false;
	अगर (!uid_eq(rule->uid_range.start, fib_kuid_range_unset.start) ||
	    !uid_eq(rule->uid_range.end, fib_kuid_range_unset.end))
		वापस false;
	अगर (fib_rule_port_range_set(&rule->sport_range))
		वापस false;
	अगर (fib_rule_port_range_set(&rule->dport_range))
		वापस false;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(fib_rule_matchall);

पूर्णांक fib_शेष_rule_add(काष्ठा fib_rules_ops *ops,
			 u32 pref, u32 table, u32 flags)
अणु
	काष्ठा fib_rule *r;

	r = kzalloc(ops->rule_size, GFP_KERNEL);
	अगर (r == शून्य)
		वापस -ENOMEM;

	refcount_set(&r->refcnt, 1);
	r->action = FR_ACT_TO_TBL;
	r->pref = pref;
	r->table = table;
	r->flags = flags;
	r->proto = RTPROT_KERNEL;
	r->fr_net = ops->fro_net;
	r->uid_range = fib_kuid_range_unset;

	r->suppress_prefixlen = -1;
	r->suppress_अगरgroup = -1;

	/* The lock is not required here, the list in unreacheable
	 * at the moment this function is called */
	list_add_tail(&r->list, &ops->rules_list);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fib_शेष_rule_add);

अटल u32 fib_शेष_rule_pref(काष्ठा fib_rules_ops *ops)
अणु
	काष्ठा list_head *pos;
	काष्ठा fib_rule *rule;

	अगर (!list_empty(&ops->rules_list)) अणु
		pos = ops->rules_list.next;
		अगर (pos->next != &ops->rules_list) अणु
			rule = list_entry(pos->next, काष्ठा fib_rule, list);
			अगर (rule->pref)
				वापस rule->pref - 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम notअगरy_rule_change(पूर्णांक event, काष्ठा fib_rule *rule,
			       काष्ठा fib_rules_ops *ops, काष्ठा nlmsghdr *nlh,
			       u32 pid);

अटल काष्ठा fib_rules_ops *lookup_rules_ops(काष्ठा net *net, पूर्णांक family)
अणु
	काष्ठा fib_rules_ops *ops;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ops, &net->rules_ops, list) अणु
		अगर (ops->family == family) अणु
			अगर (!try_module_get(ops->owner))
				ops = शून्य;
			rcu_पढ़ो_unlock();
			वापस ops;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल व्योम rules_ops_put(काष्ठा fib_rules_ops *ops)
अणु
	अगर (ops)
		module_put(ops->owner);
पूर्ण

अटल व्योम flush_route_cache(काष्ठा fib_rules_ops *ops)
अणु
	अगर (ops->flush_cache)
		ops->flush_cache(ops);
पूर्ण

अटल पूर्णांक __fib_rules_रेजिस्टर(काष्ठा fib_rules_ops *ops)
अणु
	पूर्णांक err = -EEXIST;
	काष्ठा fib_rules_ops *o;
	काष्ठा net *net;

	net = ops->fro_net;

	अगर (ops->rule_size < माप(काष्ठा fib_rule))
		वापस -EINVAL;

	अगर (ops->match == शून्य || ops->configure == शून्य ||
	    ops->compare == शून्य || ops->fill == शून्य ||
	    ops->action == शून्य)
		वापस -EINVAL;

	spin_lock(&net->rules_mod_lock);
	list_क्रम_each_entry(o, &net->rules_ops, list)
		अगर (ops->family == o->family)
			जाओ errout;

	list_add_tail_rcu(&ops->list, &net->rules_ops);
	err = 0;
errout:
	spin_unlock(&net->rules_mod_lock);

	वापस err;
पूर्ण

काष्ठा fib_rules_ops *
fib_rules_रेजिस्टर(स्थिर काष्ठा fib_rules_ops *पंचांगpl, काष्ठा net *net)
अणु
	काष्ठा fib_rules_ops *ops;
	पूर्णांक err;

	ops = kmemdup(पंचांगpl, माप(*ops), GFP_KERNEL);
	अगर (ops == शून्य)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&ops->rules_list);
	ops->fro_net = net;

	err = __fib_rules_रेजिस्टर(ops);
	अगर (err) अणु
		kमुक्त(ops);
		ops = ERR_PTR(err);
	पूर्ण

	वापस ops;
पूर्ण
EXPORT_SYMBOL_GPL(fib_rules_रेजिस्टर);

अटल व्योम fib_rules_cleanup_ops(काष्ठा fib_rules_ops *ops)
अणु
	काष्ठा fib_rule *rule, *पंचांगp;

	list_क्रम_each_entry_safe(rule, पंचांगp, &ops->rules_list, list) अणु
		list_del_rcu(&rule->list);
		अगर (ops->delete)
			ops->delete(rule);
		fib_rule_put(rule);
	पूर्ण
पूर्ण

व्योम fib_rules_unरेजिस्टर(काष्ठा fib_rules_ops *ops)
अणु
	काष्ठा net *net = ops->fro_net;

	spin_lock(&net->rules_mod_lock);
	list_del_rcu(&ops->list);
	spin_unlock(&net->rules_mod_lock);

	fib_rules_cleanup_ops(ops);
	kमुक्त_rcu(ops, rcu);
पूर्ण
EXPORT_SYMBOL_GPL(fib_rules_unरेजिस्टर);

अटल पूर्णांक uid_range_set(काष्ठा fib_kuid_range *range)
अणु
	वापस uid_valid(range->start) && uid_valid(range->end);
पूर्ण

अटल काष्ठा fib_kuid_range nla_get_kuid_range(काष्ठा nlattr **tb)
अणु
	काष्ठा fib_rule_uid_range *in;
	काष्ठा fib_kuid_range out;

	in = (काष्ठा fib_rule_uid_range *)nla_data(tb[FRA_UID_RANGE]);

	out.start = make_kuid(current_user_ns(), in->start);
	out.end = make_kuid(current_user_ns(), in->end);

	वापस out;
पूर्ण

अटल पूर्णांक nla_put_uid_range(काष्ठा sk_buff *skb, काष्ठा fib_kuid_range *range)
अणु
	काष्ठा fib_rule_uid_range out = अणु
		from_kuid_munged(current_user_ns(), range->start),
		from_kuid_munged(current_user_ns(), range->end)
	पूर्ण;

	वापस nla_put(skb, FRA_UID_RANGE, माप(out), &out);
पूर्ण

अटल पूर्णांक nla_get_port_range(काष्ठा nlattr *pattr,
			      काष्ठा fib_rule_port_range *port_range)
अणु
	स्थिर काष्ठा fib_rule_port_range *pr = nla_data(pattr);

	अगर (!fib_rule_port_range_valid(pr))
		वापस -EINVAL;

	port_range->start = pr->start;
	port_range->end = pr->end;

	वापस 0;
पूर्ण

अटल पूर्णांक nla_put_port_range(काष्ठा sk_buff *skb, पूर्णांक attrtype,
			      काष्ठा fib_rule_port_range *range)
अणु
	वापस nla_put(skb, attrtype, माप(*range), range);
पूर्ण

अटल पूर्णांक fib_rule_match(काष्ठा fib_rule *rule, काष्ठा fib_rules_ops *ops,
			  काष्ठा flowi *fl, पूर्णांक flags,
			  काष्ठा fib_lookup_arg *arg)
अणु
	पूर्णांक ret = 0;

	अगर (rule->iअगरindex && (rule->iअगरindex != fl->flowi_iअगर))
		जाओ out;

	अगर (rule->oअगरindex && (rule->oअगरindex != fl->flowi_oअगर))
		जाओ out;

	अगर ((rule->mark ^ fl->flowi_mark) & rule->mark_mask)
		जाओ out;

	अगर (rule->tun_id && (rule->tun_id != fl->flowi_tun_key.tun_id))
		जाओ out;

	अगर (rule->l3mdev && !l3mdev_fib_rule_match(rule->fr_net, fl, arg))
		जाओ out;

	अगर (uid_lt(fl->flowi_uid, rule->uid_range.start) ||
	    uid_gt(fl->flowi_uid, rule->uid_range.end))
		जाओ out;

	ret = INसूचीECT_CALL_MT(ops->match,
			       fib6_rule_match,
			       fib4_rule_match,
			       rule, fl, flags);
out:
	वापस (rule->flags & FIB_RULE_INVERT) ? !ret : ret;
पूर्ण

पूर्णांक fib_rules_lookup(काष्ठा fib_rules_ops *ops, काष्ठा flowi *fl,
		     पूर्णांक flags, काष्ठा fib_lookup_arg *arg)
अणु
	काष्ठा fib_rule *rule;
	पूर्णांक err;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(rule, &ops->rules_list, list) अणु
jumped:
		अगर (!fib_rule_match(rule, ops, fl, flags, arg))
			जारी;

		अगर (rule->action == FR_ACT_GOTO) अणु
			काष्ठा fib_rule *target;

			target = rcu_dereference(rule->ctarget);
			अगर (target == शून्य) अणु
				जारी;
			पूर्ण अन्यथा अणु
				rule = target;
				जाओ jumped;
			पूर्ण
		पूर्ण अन्यथा अगर (rule->action == FR_ACT_NOP)
			जारी;
		अन्यथा
			err = INसूचीECT_CALL_MT(ops->action,
					       fib6_rule_action,
					       fib4_rule_action,
					       rule, fl, flags, arg);

		अगर (!err && ops->suppress && INसूचीECT_CALL_MT(ops->suppress,
							      fib6_rule_suppress,
							      fib4_rule_suppress,
							      rule, arg))
			जारी;

		अगर (err != -EAGAIN) अणु
			अगर ((arg->flags & FIB_LOOKUP_NOREF) ||
			    likely(refcount_inc_not_zero(&rule->refcnt))) अणु
				arg->rule = rule;
				जाओ out;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	err = -ESRCH;
out:
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fib_rules_lookup);

अटल पूर्णांक call_fib_rule_notअगरier(काष्ठा notअगरier_block *nb,
				  क्रमागत fib_event_type event_type,
				  काष्ठा fib_rule *rule, पूर्णांक family,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_rule_notअगरier_info info = अणु
		.info.family = family,
		.info.extack = extack,
		.rule = rule,
	पूर्ण;

	वापस call_fib_notअगरier(nb, event_type, &info.info);
पूर्ण

अटल पूर्णांक call_fib_rule_notअगरiers(काष्ठा net *net,
				   क्रमागत fib_event_type event_type,
				   काष्ठा fib_rule *rule,
				   काष्ठा fib_rules_ops *ops,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_rule_notअगरier_info info = अणु
		.info.family = ops->family,
		.info.extack = extack,
		.rule = rule,
	पूर्ण;

	ops->fib_rules_seq++;
	वापस call_fib_notअगरiers(net, event_type, &info.info);
पूर्ण

/* Called with rcu_पढ़ो_lock() */
पूर्णांक fib_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb, पूर्णांक family,
		   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_rules_ops *ops;
	काष्ठा fib_rule *rule;
	पूर्णांक err = 0;

	ops = lookup_rules_ops(net, family);
	अगर (!ops)
		वापस -EAFNOSUPPORT;
	list_क्रम_each_entry_rcu(rule, &ops->rules_list, list) अणु
		err = call_fib_rule_notअगरier(nb, FIB_EVENT_RULE_ADD,
					     rule, family, extack);
		अगर (err)
			अवरोध;
	पूर्ण
	rules_ops_put(ops);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fib_rules_dump);

अचिन्हित पूर्णांक fib_rules_seq_पढ़ो(काष्ठा net *net, पूर्णांक family)
अणु
	अचिन्हित पूर्णांक fib_rules_seq;
	काष्ठा fib_rules_ops *ops;

	ASSERT_RTNL();

	ops = lookup_rules_ops(net, family);
	अगर (!ops)
		वापस 0;
	fib_rules_seq = ops->fib_rules_seq;
	rules_ops_put(ops);

	वापस fib_rules_seq;
पूर्ण
EXPORT_SYMBOL_GPL(fib_rules_seq_पढ़ो);

अटल काष्ठा fib_rule *rule_find(काष्ठा fib_rules_ops *ops,
				  काष्ठा fib_rule_hdr *frh,
				  काष्ठा nlattr **tb,
				  काष्ठा fib_rule *rule,
				  bool user_priority)
अणु
	काष्ठा fib_rule *r;

	list_क्रम_each_entry(r, &ops->rules_list, list) अणु
		अगर (rule->action && r->action != rule->action)
			जारी;

		अगर (rule->table && r->table != rule->table)
			जारी;

		अगर (user_priority && r->pref != rule->pref)
			जारी;

		अगर (rule->iअगरname[0] &&
		    स_भेद(r->iअगरname, rule->iअगरname, IFNAMSIZ))
			जारी;

		अगर (rule->oअगरname[0] &&
		    स_भेद(r->oअगरname, rule->oअगरname, IFNAMSIZ))
			जारी;

		अगर (rule->mark && r->mark != rule->mark)
			जारी;

		अगर (rule->suppress_अगरgroup != -1 &&
		    r->suppress_अगरgroup != rule->suppress_अगरgroup)
			जारी;

		अगर (rule->suppress_prefixlen != -1 &&
		    r->suppress_prefixlen != rule->suppress_prefixlen)
			जारी;

		अगर (rule->mark_mask && r->mark_mask != rule->mark_mask)
			जारी;

		अगर (rule->tun_id && r->tun_id != rule->tun_id)
			जारी;

		अगर (r->fr_net != rule->fr_net)
			जारी;

		अगर (rule->l3mdev && r->l3mdev != rule->l3mdev)
			जारी;

		अगर (uid_range_set(&rule->uid_range) &&
		    (!uid_eq(r->uid_range.start, rule->uid_range.start) ||
		    !uid_eq(r->uid_range.end, rule->uid_range.end)))
			जारी;

		अगर (rule->ip_proto && r->ip_proto != rule->ip_proto)
			जारी;

		अगर (rule->proto && r->proto != rule->proto)
			जारी;

		अगर (fib_rule_port_range_set(&rule->sport_range) &&
		    !fib_rule_port_range_compare(&r->sport_range,
						 &rule->sport_range))
			जारी;

		अगर (fib_rule_port_range_set(&rule->dport_range) &&
		    !fib_rule_port_range_compare(&r->dport_range,
						 &rule->dport_range))
			जारी;

		अगर (!ops->compare(r, frh, tb))
			जारी;
		वापस r;
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_NET_L3_MASTER_DEV
अटल पूर्णांक fib_nl2rule_l3mdev(काष्ठा nlattr *nla, काष्ठा fib_rule *nlrule,
			      काष्ठा netlink_ext_ack *extack)
अणु
	nlrule->l3mdev = nla_get_u8(nla);
	अगर (nlrule->l3mdev != 1) अणु
		NL_SET_ERR_MSG(extack, "Invalid l3mdev attribute");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक fib_nl2rule_l3mdev(काष्ठा nlattr *nla, काष्ठा fib_rule *nlrule,
			      काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG(extack, "l3mdev support is not enabled in kernel");
	वापस -1;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक fib_nl2rule(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		       काष्ठा netlink_ext_ack *extack,
		       काष्ठा fib_rules_ops *ops,
		       काष्ठा nlattr *tb[],
		       काष्ठा fib_rule **rule,
		       bool *user_priority)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा fib_rule_hdr *frh = nlmsg_data(nlh);
	काष्ठा fib_rule *nlrule = शून्य;
	पूर्णांक err = -EINVAL;

	अगर (frh->src_len)
		अगर (!tb[FRA_SRC] ||
		    frh->src_len > (ops->addr_size * 8) ||
		    nla_len(tb[FRA_SRC]) != ops->addr_size) अणु
			NL_SET_ERR_MSG(extack, "Invalid source address");
			जाओ errout;
	पूर्ण

	अगर (frh->dst_len)
		अगर (!tb[FRA_DST] ||
		    frh->dst_len > (ops->addr_size * 8) ||
		    nla_len(tb[FRA_DST]) != ops->addr_size) अणु
			NL_SET_ERR_MSG(extack, "Invalid dst address");
			जाओ errout;
	पूर्ण

	nlrule = kzalloc(ops->rule_size, GFP_KERNEL);
	अगर (!nlrule) अणु
		err = -ENOMEM;
		जाओ errout;
	पूर्ण
	refcount_set(&nlrule->refcnt, 1);
	nlrule->fr_net = net;

	अगर (tb[FRA_PRIORITY]) अणु
		nlrule->pref = nla_get_u32(tb[FRA_PRIORITY]);
		*user_priority = true;
	पूर्ण अन्यथा अणु
		nlrule->pref = fib_शेष_rule_pref(ops);
	पूर्ण

	nlrule->proto = tb[FRA_PROTOCOL] ?
		nla_get_u8(tb[FRA_PROTOCOL]) : RTPROT_UNSPEC;

	अगर (tb[FRA_IIFNAME]) अणु
		काष्ठा net_device *dev;

		nlrule->iअगरindex = -1;
		nla_strscpy(nlrule->iअगरname, tb[FRA_IIFNAME], IFNAMSIZ);
		dev = __dev_get_by_name(net, nlrule->iअगरname);
		अगर (dev)
			nlrule->iअगरindex = dev->अगरindex;
	पूर्ण

	अगर (tb[FRA_OIFNAME]) अणु
		काष्ठा net_device *dev;

		nlrule->oअगरindex = -1;
		nla_strscpy(nlrule->oअगरname, tb[FRA_OIFNAME], IFNAMSIZ);
		dev = __dev_get_by_name(net, nlrule->oअगरname);
		अगर (dev)
			nlrule->oअगरindex = dev->अगरindex;
	पूर्ण

	अगर (tb[FRA_FWMARK]) अणु
		nlrule->mark = nla_get_u32(tb[FRA_FWMARK]);
		अगर (nlrule->mark)
			/* compatibility: अगर the mark value is non-zero all bits
			 * are compared unless a mask is explicitly specअगरied.
			 */
			nlrule->mark_mask = 0xFFFFFFFF;
	पूर्ण

	अगर (tb[FRA_FWMASK])
		nlrule->mark_mask = nla_get_u32(tb[FRA_FWMASK]);

	अगर (tb[FRA_TUN_ID])
		nlrule->tun_id = nla_get_be64(tb[FRA_TUN_ID]);

	err = -EINVAL;
	अगर (tb[FRA_L3MDEV] &&
	    fib_nl2rule_l3mdev(tb[FRA_L3MDEV], nlrule, extack) < 0)
		जाओ errout_मुक्त;

	nlrule->action = frh->action;
	nlrule->flags = frh->flags;
	nlrule->table = frh_get_table(frh, tb);
	अगर (tb[FRA_SUPPRESS_PREFIXLEN])
		nlrule->suppress_prefixlen = nla_get_u32(tb[FRA_SUPPRESS_PREFIXLEN]);
	अन्यथा
		nlrule->suppress_prefixlen = -1;

	अगर (tb[FRA_SUPPRESS_IFGROUP])
		nlrule->suppress_अगरgroup = nla_get_u32(tb[FRA_SUPPRESS_IFGROUP]);
	अन्यथा
		nlrule->suppress_अगरgroup = -1;

	अगर (tb[FRA_GOTO]) अणु
		अगर (nlrule->action != FR_ACT_GOTO) अणु
			NL_SET_ERR_MSG(extack, "Unexpected goto");
			जाओ errout_मुक्त;
		पूर्ण

		nlrule->target = nla_get_u32(tb[FRA_GOTO]);
		/* Backward jumps are prohibited to aव्योम endless loops */
		अगर (nlrule->target <= nlrule->pref) अणु
			NL_SET_ERR_MSG(extack, "Backward goto not supported");
			जाओ errout_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अगर (nlrule->action == FR_ACT_GOTO) अणु
		NL_SET_ERR_MSG(extack, "Missing goto target for action goto");
		जाओ errout_मुक्त;
	पूर्ण

	अगर (nlrule->l3mdev && nlrule->table) अणु
		NL_SET_ERR_MSG(extack, "l3mdev and table are mutually exclusive");
		जाओ errout_मुक्त;
	पूर्ण

	अगर (tb[FRA_UID_RANGE]) अणु
		अगर (current_user_ns() != net->user_ns) अणु
			err = -EPERM;
			NL_SET_ERR_MSG(extack, "No permission to set uid");
			जाओ errout_मुक्त;
		पूर्ण

		nlrule->uid_range = nla_get_kuid_range(tb);

		अगर (!uid_range_set(&nlrule->uid_range) ||
		    !uid_lte(nlrule->uid_range.start, nlrule->uid_range.end)) अणु
			NL_SET_ERR_MSG(extack, "Invalid uid range");
			जाओ errout_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		nlrule->uid_range = fib_kuid_range_unset;
	पूर्ण

	अगर (tb[FRA_IP_PROTO])
		nlrule->ip_proto = nla_get_u8(tb[FRA_IP_PROTO]);

	अगर (tb[FRA_SPORT_RANGE]) अणु
		err = nla_get_port_range(tb[FRA_SPORT_RANGE],
					 &nlrule->sport_range);
		अगर (err) अणु
			NL_SET_ERR_MSG(extack, "Invalid sport range");
			जाओ errout_मुक्त;
		पूर्ण
	पूर्ण

	अगर (tb[FRA_DPORT_RANGE]) अणु
		err = nla_get_port_range(tb[FRA_DPORT_RANGE],
					 &nlrule->dport_range);
		अगर (err) अणु
			NL_SET_ERR_MSG(extack, "Invalid dport range");
			जाओ errout_मुक्त;
		पूर्ण
	पूर्ण

	*rule = nlrule;

	वापस 0;

errout_मुक्त:
	kमुक्त(nlrule);
errout:
	वापस err;
पूर्ण

अटल पूर्णांक rule_exists(काष्ठा fib_rules_ops *ops, काष्ठा fib_rule_hdr *frh,
		       काष्ठा nlattr **tb, काष्ठा fib_rule *rule)
अणु
	काष्ठा fib_rule *r;

	list_क्रम_each_entry(r, &ops->rules_list, list) अणु
		अगर (r->action != rule->action)
			जारी;

		अगर (r->table != rule->table)
			जारी;

		अगर (r->pref != rule->pref)
			जारी;

		अगर (स_भेद(r->iअगरname, rule->iअगरname, IFNAMSIZ))
			जारी;

		अगर (स_भेद(r->oअगरname, rule->oअगरname, IFNAMSIZ))
			जारी;

		अगर (r->mark != rule->mark)
			जारी;

		अगर (r->suppress_अगरgroup != rule->suppress_अगरgroup)
			जारी;

		अगर (r->suppress_prefixlen != rule->suppress_prefixlen)
			जारी;

		अगर (r->mark_mask != rule->mark_mask)
			जारी;

		अगर (r->tun_id != rule->tun_id)
			जारी;

		अगर (r->fr_net != rule->fr_net)
			जारी;

		अगर (r->l3mdev != rule->l3mdev)
			जारी;

		अगर (!uid_eq(r->uid_range.start, rule->uid_range.start) ||
		    !uid_eq(r->uid_range.end, rule->uid_range.end))
			जारी;

		अगर (r->ip_proto != rule->ip_proto)
			जारी;

		अगर (r->proto != rule->proto)
			जारी;

		अगर (!fib_rule_port_range_compare(&r->sport_range,
						 &rule->sport_range))
			जारी;

		अगर (!fib_rule_port_range_compare(&r->dport_range,
						 &rule->dport_range))
			जारी;

		अगर (!ops->compare(r, frh, tb))
			जारी;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक fib_nl_newrule(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा fib_rule_hdr *frh = nlmsg_data(nlh);
	काष्ठा fib_rules_ops *ops = शून्य;
	काष्ठा fib_rule *rule = शून्य, *r, *last = शून्य;
	काष्ठा nlattr *tb[FRA_MAX + 1];
	पूर्णांक err = -EINVAL, unresolved = 0;
	bool user_priority = false;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*frh))) अणु
		NL_SET_ERR_MSG(extack, "Invalid msg length");
		जाओ errout;
	पूर्ण

	ops = lookup_rules_ops(net, frh->family);
	अगर (!ops) अणु
		err = -EAFNOSUPPORT;
		NL_SET_ERR_MSG(extack, "Rule family not supported");
		जाओ errout;
	पूर्ण

	err = nlmsg_parse_deprecated(nlh, माप(*frh), tb, FRA_MAX,
				     ops->policy, extack);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG(extack, "Error parsing msg");
		जाओ errout;
	पूर्ण

	err = fib_nl2rule(skb, nlh, extack, ops, tb, &rule, &user_priority);
	अगर (err)
		जाओ errout;

	अगर ((nlh->nlmsg_flags & NLM_F_EXCL) &&
	    rule_exists(ops, frh, tb, rule)) अणु
		err = -EEXIST;
		जाओ errout_मुक्त;
	पूर्ण

	err = ops->configure(rule, skb, frh, tb, extack);
	अगर (err < 0)
		जाओ errout_मुक्त;

	err = call_fib_rule_notअगरiers(net, FIB_EVENT_RULE_ADD, rule, ops,
				      extack);
	अगर (err < 0)
		जाओ errout_मुक्त;

	list_क्रम_each_entry(r, &ops->rules_list, list) अणु
		अगर (r->pref == rule->target) अणु
			RCU_INIT_POINTER(rule->ctarget, r);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rcu_dereference_रक्षित(rule->ctarget, 1) == शून्य)
		unresolved = 1;

	list_क्रम_each_entry(r, &ops->rules_list, list) अणु
		अगर (r->pref > rule->pref)
			अवरोध;
		last = r;
	पूर्ण

	अगर (last)
		list_add_rcu(&rule->list, &last->list);
	अन्यथा
		list_add_rcu(&rule->list, &ops->rules_list);

	अगर (ops->unresolved_rules) अणु
		/*
		 * There are unresolved जाओ rules in the list, check अगर
		 * any of them are poपूर्णांकing to this new rule.
		 */
		list_क्रम_each_entry(r, &ops->rules_list, list) अणु
			अगर (r->action == FR_ACT_GOTO &&
			    r->target == rule->pref &&
			    rtnl_dereference(r->ctarget) == शून्य) अणु
				rcu_assign_poपूर्णांकer(r->ctarget, rule);
				अगर (--ops->unresolved_rules == 0)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rule->action == FR_ACT_GOTO)
		ops->nr_जाओ_rules++;

	अगर (unresolved)
		ops->unresolved_rules++;

	अगर (rule->tun_id)
		ip_tunnel_need_metadata();

	notअगरy_rule_change(RTM_NEWRULE, rule, ops, nlh, NETLINK_CB(skb).portid);
	flush_route_cache(ops);
	rules_ops_put(ops);
	वापस 0;

errout_मुक्त:
	kमुक्त(rule);
errout:
	rules_ops_put(ops);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fib_nl_newrule);

पूर्णांक fib_nl_delrule(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा fib_rule_hdr *frh = nlmsg_data(nlh);
	काष्ठा fib_rules_ops *ops = शून्य;
	काष्ठा fib_rule *rule = शून्य, *r, *nlrule = शून्य;
	काष्ठा nlattr *tb[FRA_MAX+1];
	पूर्णांक err = -EINVAL;
	bool user_priority = false;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*frh))) अणु
		NL_SET_ERR_MSG(extack, "Invalid msg length");
		जाओ errout;
	पूर्ण

	ops = lookup_rules_ops(net, frh->family);
	अगर (ops == शून्य) अणु
		err = -EAFNOSUPPORT;
		NL_SET_ERR_MSG(extack, "Rule family not supported");
		जाओ errout;
	पूर्ण

	err = nlmsg_parse_deprecated(nlh, माप(*frh), tb, FRA_MAX,
				     ops->policy, extack);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG(extack, "Error parsing msg");
		जाओ errout;
	पूर्ण

	err = fib_nl2rule(skb, nlh, extack, ops, tb, &nlrule, &user_priority);
	अगर (err)
		जाओ errout;

	rule = rule_find(ops, frh, tb, nlrule, user_priority);
	अगर (!rule) अणु
		err = -ENOENT;
		जाओ errout;
	पूर्ण

	अगर (rule->flags & FIB_RULE_PERMANENT) अणु
		err = -EPERM;
		जाओ errout;
	पूर्ण

	अगर (ops->delete) अणु
		err = ops->delete(rule);
		अगर (err)
			जाओ errout;
	पूर्ण

	अगर (rule->tun_id)
		ip_tunnel_unneed_metadata();

	list_del_rcu(&rule->list);

	अगर (rule->action == FR_ACT_GOTO) अणु
		ops->nr_जाओ_rules--;
		अगर (rtnl_dereference(rule->ctarget) == शून्य)
			ops->unresolved_rules--;
	पूर्ण

	/*
	 * Check अगर this rule is a target to any of them. If so,
	 * adjust to the next one with the same preference or
	 * disable them. As this operation is eventually very
	 * expensive, it is only perक्रमmed अगर जाओ rules, except
	 * current अगर it is जाओ rule, have actually been added.
	 */
	अगर (ops->nr_जाओ_rules > 0) अणु
		काष्ठा fib_rule *n;

		n = list_next_entry(rule, list);
		अगर (&n->list == &ops->rules_list || n->pref != rule->pref)
			n = शून्य;
		list_क्रम_each_entry(r, &ops->rules_list, list) अणु
			अगर (rtnl_dereference(r->ctarget) != rule)
				जारी;
			rcu_assign_poपूर्णांकer(r->ctarget, n);
			अगर (!n)
				ops->unresolved_rules++;
		पूर्ण
	पूर्ण

	call_fib_rule_notअगरiers(net, FIB_EVENT_RULE_DEL, rule, ops,
				शून्य);
	notअगरy_rule_change(RTM_DELRULE, rule, ops, nlh,
			   NETLINK_CB(skb).portid);
	fib_rule_put(rule);
	flush_route_cache(ops);
	rules_ops_put(ops);
	kमुक्त(nlrule);
	वापस 0;

errout:
	kमुक्त(nlrule);
	rules_ops_put(ops);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fib_nl_delrule);

अटल अंतरभूत माप_प्रकार fib_rule_nlmsg_size(काष्ठा fib_rules_ops *ops,
					 काष्ठा fib_rule *rule)
अणु
	माप_प्रकार payload = NLMSG_ALIGN(माप(काष्ठा fib_rule_hdr))
			 + nla_total_size(IFNAMSIZ) /* FRA_IIFNAME */
			 + nla_total_size(IFNAMSIZ) /* FRA_OIFNAME */
			 + nla_total_size(4) /* FRA_PRIORITY */
			 + nla_total_size(4) /* FRA_TABLE */
			 + nla_total_size(4) /* FRA_SUPPRESS_PREFIXLEN */
			 + nla_total_size(4) /* FRA_SUPPRESS_IFGROUP */
			 + nla_total_size(4) /* FRA_FWMARK */
			 + nla_total_size(4) /* FRA_FWMASK */
			 + nla_total_size_64bit(8) /* FRA_TUN_ID */
			 + nla_total_size(माप(काष्ठा fib_kuid_range))
			 + nla_total_size(1) /* FRA_PROTOCOL */
			 + nla_total_size(1) /* FRA_IP_PROTO */
			 + nla_total_size(माप(काष्ठा fib_rule_port_range)) /* FRA_SPORT_RANGE */
			 + nla_total_size(माप(काष्ठा fib_rule_port_range)); /* FRA_DPORT_RANGE */

	अगर (ops->nlmsg_payload)
		payload += ops->nlmsg_payload(rule);

	वापस payload;
पूर्ण

अटल पूर्णांक fib_nl_fill_rule(काष्ठा sk_buff *skb, काष्ठा fib_rule *rule,
			    u32 pid, u32 seq, पूर्णांक type, पूर्णांक flags,
			    काष्ठा fib_rules_ops *ops)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा fib_rule_hdr *frh;

	nlh = nlmsg_put(skb, pid, seq, type, माप(*frh), flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	frh = nlmsg_data(nlh);
	frh->family = ops->family;
	frh->table = rule->table < 256 ? rule->table : RT_TABLE_COMPAT;
	अगर (nla_put_u32(skb, FRA_TABLE, rule->table))
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, FRA_SUPPRESS_PREFIXLEN, rule->suppress_prefixlen))
		जाओ nla_put_failure;
	frh->res1 = 0;
	frh->res2 = 0;
	frh->action = rule->action;
	frh->flags = rule->flags;

	अगर (nla_put_u8(skb, FRA_PROTOCOL, rule->proto))
		जाओ nla_put_failure;

	अगर (rule->action == FR_ACT_GOTO &&
	    rcu_access_poपूर्णांकer(rule->ctarget) == शून्य)
		frh->flags |= FIB_RULE_UNRESOLVED;

	अगर (rule->iअगरname[0]) अणु
		अगर (nla_put_string(skb, FRA_IIFNAME, rule->iअगरname))
			जाओ nla_put_failure;
		अगर (rule->iअगरindex == -1)
			frh->flags |= FIB_RULE_IIF_DETACHED;
	पूर्ण

	अगर (rule->oअगरname[0]) अणु
		अगर (nla_put_string(skb, FRA_OIFNAME, rule->oअगरname))
			जाओ nla_put_failure;
		अगर (rule->oअगरindex == -1)
			frh->flags |= FIB_RULE_OIF_DETACHED;
	पूर्ण

	अगर ((rule->pref &&
	     nla_put_u32(skb, FRA_PRIORITY, rule->pref)) ||
	    (rule->mark &&
	     nla_put_u32(skb, FRA_FWMARK, rule->mark)) ||
	    ((rule->mark_mask || rule->mark) &&
	     nla_put_u32(skb, FRA_FWMASK, rule->mark_mask)) ||
	    (rule->target &&
	     nla_put_u32(skb, FRA_GOTO, rule->target)) ||
	    (rule->tun_id &&
	     nla_put_be64(skb, FRA_TUN_ID, rule->tun_id, FRA_PAD)) ||
	    (rule->l3mdev &&
	     nla_put_u8(skb, FRA_L3MDEV, rule->l3mdev)) ||
	    (uid_range_set(&rule->uid_range) &&
	     nla_put_uid_range(skb, &rule->uid_range)) ||
	    (fib_rule_port_range_set(&rule->sport_range) &&
	     nla_put_port_range(skb, FRA_SPORT_RANGE, &rule->sport_range)) ||
	    (fib_rule_port_range_set(&rule->dport_range) &&
	     nla_put_port_range(skb, FRA_DPORT_RANGE, &rule->dport_range)) ||
	    (rule->ip_proto && nla_put_u8(skb, FRA_IP_PROTO, rule->ip_proto)))
		जाओ nla_put_failure;

	अगर (rule->suppress_अगरgroup != -1) अणु
		अगर (nla_put_u32(skb, FRA_SUPPRESS_IFGROUP, rule->suppress_अगरgroup))
			जाओ nla_put_failure;
	पूर्ण

	अगर (ops->fill(rule, skb, frh) < 0)
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक dump_rules(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		      काष्ठा fib_rules_ops *ops)
अणु
	पूर्णांक idx = 0;
	काष्ठा fib_rule *rule;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(rule, &ops->rules_list, list) अणु
		अगर (idx < cb->args[1])
			जाओ skip;

		err = fib_nl_fill_rule(skb, rule, NETLINK_CB(cb->skb).portid,
				       cb->nlh->nlmsg_seq, RTM_NEWRULE,
				       NLM_F_MULTI, ops);
		अगर (err)
			अवरोध;
skip:
		idx++;
	पूर्ण
	rcu_पढ़ो_unlock();
	cb->args[1] = idx;
	rules_ops_put(ops);

	वापस err;
पूर्ण

अटल पूर्णांक fib_valid_dumprule_req(स्थिर काष्ठा nlmsghdr *nlh,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib_rule_hdr *frh;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*frh))) अणु
		NL_SET_ERR_MSG(extack, "Invalid header for fib rule dump request");
		वापस -EINVAL;
	पूर्ण

	frh = nlmsg_data(nlh);
	अगर (frh->dst_len || frh->src_len || frh->tos || frh->table ||
	    frh->res1 || frh->res2 || frh->action || frh->flags) अणु
		NL_SET_ERR_MSG(extack,
			       "Invalid values in header for fib rule dump request");
		वापस -EINVAL;
	पूर्ण

	अगर (nlmsg_attrlen(nlh, माप(*frh))) अणु
		NL_SET_ERR_MSG(extack, "Invalid data after header in fib rule dump request");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fib_nl_dumprule(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा fib_rules_ops *ops;
	पूर्णांक idx = 0, family;

	अगर (cb->strict_check) अणु
		पूर्णांक err = fib_valid_dumprule_req(nlh, cb->extack);

		अगर (err < 0)
			वापस err;
	पूर्ण

	family = rtnl_msg_family(nlh);
	अगर (family != AF_UNSPEC) अणु
		/* Protocol specअगरic dump request */
		ops = lookup_rules_ops(net, family);
		अगर (ops == शून्य)
			वापस -EAFNOSUPPORT;

		dump_rules(skb, cb, ops);

		वापस skb->len;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ops, &net->rules_ops, list) अणु
		अगर (idx < cb->args[0] || !try_module_get(ops->owner))
			जाओ skip;

		अगर (dump_rules(skb, cb, ops) < 0)
			अवरोध;

		cb->args[1] = 0;
skip:
		idx++;
	पूर्ण
	rcu_पढ़ो_unlock();
	cb->args[0] = idx;

	वापस skb->len;
पूर्ण

अटल व्योम notअगरy_rule_change(पूर्णांक event, काष्ठा fib_rule *rule,
			       काष्ठा fib_rules_ops *ops, काष्ठा nlmsghdr *nlh,
			       u32 pid)
अणु
	काष्ठा net *net;
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOMEM;

	net = ops->fro_net;
	skb = nlmsg_new(fib_rule_nlmsg_size(ops, rule), GFP_KERNEL);
	अगर (skb == शून्य)
		जाओ errout;

	err = fib_nl_fill_rule(skb, rule, pid, nlh->nlmsg_seq, event, 0, ops);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in fib_rule_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण

	rtnl_notअगरy(skb, net, pid, ops->nlgroup, nlh, GFP_KERNEL);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, ops->nlgroup, err);
पूर्ण

अटल व्योम attach_rules(काष्ठा list_head *rules, काष्ठा net_device *dev)
अणु
	काष्ठा fib_rule *rule;

	list_क्रम_each_entry(rule, rules, list) अणु
		अगर (rule->iअगरindex == -1 &&
		    म_भेद(dev->name, rule->iअगरname) == 0)
			rule->iअगरindex = dev->अगरindex;
		अगर (rule->oअगरindex == -1 &&
		    म_भेद(dev->name, rule->oअगरname) == 0)
			rule->oअगरindex = dev->अगरindex;
	पूर्ण
पूर्ण

अटल व्योम detach_rules(काष्ठा list_head *rules, काष्ठा net_device *dev)
अणु
	काष्ठा fib_rule *rule;

	list_क्रम_each_entry(rule, rules, list) अणु
		अगर (rule->iअगरindex == dev->अगरindex)
			rule->iअगरindex = -1;
		अगर (rule->oअगरindex == dev->अगरindex)
			rule->oअगरindex = -1;
	पूर्ण
पूर्ण


अटल पूर्णांक fib_rules_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा net *net = dev_net(dev);
	काष्ठा fib_rules_ops *ops;

	ASSERT_RTNL();

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		list_क्रम_each_entry(ops, &net->rules_ops, list)
			attach_rules(&ops->rules_list, dev);
		अवरोध;

	हाल NETDEV_CHANGENAME:
		list_क्रम_each_entry(ops, &net->rules_ops, list) अणु
			detach_rules(&ops->rules_list, dev);
			attach_rules(&ops->rules_list, dev);
		पूर्ण
		अवरोध;

	हाल NETDEV_UNREGISTER:
		list_क्रम_each_entry(ops, &net->rules_ops, list)
			detach_rules(&ops->rules_list, dev);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block fib_rules_notअगरier = अणु
	.notअगरier_call = fib_rules_event,
पूर्ण;

अटल पूर्णांक __net_init fib_rules_net_init(काष्ठा net *net)
अणु
	INIT_LIST_HEAD(&net->rules_ops);
	spin_lock_init(&net->rules_mod_lock);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास fib_rules_net_निकास(काष्ठा net *net)
अणु
	WARN_ON_ONCE(!list_empty(&net->rules_ops));
पूर्ण

अटल काष्ठा pernet_operations fib_rules_net_ops = अणु
	.init = fib_rules_net_init,
	.निकास = fib_rules_net_निकास,
पूर्ण;

अटल पूर्णांक __init fib_rules_init(व्योम)
अणु
	पूर्णांक err;
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWRULE, fib_nl_newrule, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_DELRULE, fib_nl_delrule, शून्य, 0);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETRULE, शून्य, fib_nl_dumprule, 0);

	err = रेजिस्टर_pernet_subsys(&fib_rules_net_ops);
	अगर (err < 0)
		जाओ fail;

	err = रेजिस्टर_netdevice_notअगरier(&fib_rules_notअगरier);
	अगर (err < 0)
		जाओ fail_unरेजिस्टर;

	वापस 0;

fail_unरेजिस्टर:
	unरेजिस्टर_pernet_subsys(&fib_rules_net_ops);
fail:
	rtnl_unरेजिस्टर(PF_UNSPEC, RTM_NEWRULE);
	rtnl_unरेजिस्टर(PF_UNSPEC, RTM_DELRULE);
	rtnl_unरेजिस्टर(PF_UNSPEC, RTM_GETRULE);
	वापस err;
पूर्ण

subsys_initcall(fib_rules_init);
