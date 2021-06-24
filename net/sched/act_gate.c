<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Copyright 2020 NXP */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <net/act_api.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gate.h>

अटल अचिन्हित पूर्णांक gate_net_id;
अटल काष्ठा tc_action_ops act_gate_ops;

अटल kसमय_प्रकार gate_get_समय(काष्ठा tcf_gate *gact)
अणु
	kसमय_प्रकार mono = kसमय_get();

	चयन (gact->tk_offset) अणु
	हाल TK_OFFS_MAX:
		वापस mono;
	शेष:
		वापस kसमय_mono_to_any(mono, gact->tk_offset);
	पूर्ण

	वापस KTIME_MAX;
पूर्ण

अटल व्योम gate_get_start_समय(काष्ठा tcf_gate *gact, kसमय_प्रकार *start)
अणु
	काष्ठा tcf_gate_params *param = &gact->param;
	kसमय_प्रकार now, base, cycle;
	u64 n;

	base = ns_to_kसमय(param->tcfg_baseसमय);
	now = gate_get_समय(gact);

	अगर (kसमय_after(base, now)) अणु
		*start = base;
		वापस;
	पूर्ण

	cycle = param->tcfg_cycleसमय;

	n = भाग64_u64(kसमय_sub_ns(now, base), cycle);
	*start = kसमय_add_ns(base, (n + 1) * cycle);
पूर्ण

अटल व्योम gate_start_समयr(काष्ठा tcf_gate *gact, kसमय_प्रकार start)
अणु
	kसमय_प्रकार expires;

	expires = hrसमयr_get_expires(&gact->hiसमयr);
	अगर (expires == 0)
		expires = KTIME_MAX;

	start = min_t(kसमय_प्रकार, start, expires);

	hrसमयr_start(&gact->hiसमयr, start, HRTIMER_MODE_ABS_SOFT);
पूर्ण

अटल क्रमागत hrसमयr_restart gate_समयr_func(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा tcf_gate *gact = container_of(समयr, काष्ठा tcf_gate,
					     hiसमयr);
	काष्ठा tcf_gate_params *p = &gact->param;
	काष्ठा tcfg_gate_entry *next;
	kसमय_प्रकार बंद_समय, now;

	spin_lock(&gact->tcf_lock);

	next = gact->next_entry;

	/* cycle start, clear pending bit, clear total octets */
	gact->current_gate_status = next->gate_state ? GATE_ACT_GATE_OPEN : 0;
	gact->current_entry_octets = 0;
	gact->current_max_octets = next->maxoctets;

	gact->current_बंद_समय = kसमय_add_ns(gact->current_बंद_समय,
						next->पूर्णांकerval);

	बंद_समय = gact->current_बंद_समय;

	अगर (list_is_last(&next->list, &p->entries))
		next = list_first_entry(&p->entries,
					काष्ठा tcfg_gate_entry, list);
	अन्यथा
		next = list_next_entry(next, list);

	now = gate_get_समय(gact);

	अगर (kसमय_after(now, बंद_समय)) अणु
		kसमय_प्रकार cycle, base;
		u64 n;

		cycle = p->tcfg_cycleसमय;
		base = ns_to_kसमय(p->tcfg_baseसमय);
		n = भाग64_u64(kसमय_sub_ns(now, base), cycle);
		बंद_समय = kसमय_add_ns(base, (n + 1) * cycle);
	पूर्ण

	gact->next_entry = next;

	hrसमयr_set_expires(&gact->hiसमयr, बंद_समय);

	spin_unlock(&gact->tcf_lock);

	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक tcf_gate_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_gate *gact = to_gate(a);

	spin_lock(&gact->tcf_lock);

	tcf_lastuse_update(&gact->tcf_पंचांग);
	bstats_update(&gact->tcf_bstats, skb);

	अगर (unlikely(gact->current_gate_status & GATE_ACT_PENDING)) अणु
		spin_unlock(&gact->tcf_lock);
		वापस gact->tcf_action;
	पूर्ण

	अगर (!(gact->current_gate_status & GATE_ACT_GATE_OPEN))
		जाओ drop;

	अगर (gact->current_max_octets >= 0) अणु
		gact->current_entry_octets += qdisc_pkt_len(skb);
		अगर (gact->current_entry_octets > gact->current_max_octets) अणु
			gact->tcf_qstats.overlimits++;
			जाओ drop;
		पूर्ण
	पूर्ण

	spin_unlock(&gact->tcf_lock);

	वापस gact->tcf_action;
drop:
	gact->tcf_qstats.drops++;
	spin_unlock(&gact->tcf_lock);

	वापस TC_ACT_SHOT;
पूर्ण

अटल स्थिर काष्ठा nla_policy entry_policy[TCA_GATE_ENTRY_MAX + 1] = अणु
	[TCA_GATE_ENTRY_INDEX]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_GATE_ENTRY_GATE]		= अणु .type = NLA_FLAG पूर्ण,
	[TCA_GATE_ENTRY_INTERVAL]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_GATE_ENTRY_IPV]		= अणु .type = NLA_S32 पूर्ण,
	[TCA_GATE_ENTRY_MAX_OCTETS]	= अणु .type = NLA_S32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy gate_policy[TCA_GATE_MAX + 1] = अणु
	[TCA_GATE_PARMS]		=
		NLA_POLICY_EXACT_LEN(माप(काष्ठा tc_gate)),
	[TCA_GATE_PRIORITY]		= अणु .type = NLA_S32 पूर्ण,
	[TCA_GATE_ENTRY_LIST]		= अणु .type = NLA_NESTED पूर्ण,
	[TCA_GATE_BASE_TIME]		= अणु .type = NLA_U64 पूर्ण,
	[TCA_GATE_CYCLE_TIME]		= अणु .type = NLA_U64 पूर्ण,
	[TCA_GATE_CYCLE_TIME_EXT]	= अणु .type = NLA_U64 पूर्ण,
	[TCA_GATE_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_GATE_CLOCKID]		= अणु .type = NLA_S32 पूर्ण,
पूर्ण;

अटल पूर्णांक fill_gate_entry(काष्ठा nlattr **tb, काष्ठा tcfg_gate_entry *entry,
			   काष्ठा netlink_ext_ack *extack)
अणु
	u32 पूर्णांकerval = 0;

	entry->gate_state = nla_get_flag(tb[TCA_GATE_ENTRY_GATE]);

	अगर (tb[TCA_GATE_ENTRY_INTERVAL])
		पूर्णांकerval = nla_get_u32(tb[TCA_GATE_ENTRY_INTERVAL]);

	अगर (पूर्णांकerval == 0) अणु
		NL_SET_ERR_MSG(extack, "Invalid interval for schedule entry");
		वापस -EINVAL;
	पूर्ण

	entry->पूर्णांकerval = पूर्णांकerval;

	अगर (tb[TCA_GATE_ENTRY_IPV])
		entry->ipv = nla_get_s32(tb[TCA_GATE_ENTRY_IPV]);
	अन्यथा
		entry->ipv = -1;

	अगर (tb[TCA_GATE_ENTRY_MAX_OCTETS])
		entry->maxoctets = nla_get_s32(tb[TCA_GATE_ENTRY_MAX_OCTETS]);
	अन्यथा
		entry->maxoctets = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_gate_entry(काष्ठा nlattr *n, काष्ठा  tcfg_gate_entry *entry,
			    पूर्णांक index, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_GATE_ENTRY_MAX + 1] = अणु पूर्ण;
	पूर्णांक err;

	err = nla_parse_nested(tb, TCA_GATE_ENTRY_MAX, n, entry_policy, extack);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG(extack, "Could not parse nested entry");
		वापस -EINVAL;
	पूर्ण

	entry->index = index;

	वापस fill_gate_entry(tb, entry, extack);
पूर्ण

अटल व्योम release_entry_list(काष्ठा list_head *entries)
अणु
	काष्ठा tcfg_gate_entry *entry, *e;

	list_क्रम_each_entry_safe(entry, e, entries, list) अणु
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल पूर्णांक parse_gate_list(काष्ठा nlattr *list_attr,
			   काष्ठा tcf_gate_params *sched,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tcfg_gate_entry *entry;
	काष्ठा nlattr *n;
	पूर्णांक err, rem;
	पूर्णांक i = 0;

	अगर (!list_attr)
		वापस -EINVAL;

	nla_क्रम_each_nested(n, list_attr, rem) अणु
		अगर (nla_type(n) != TCA_GATE_ONE_ENTRY) अणु
			NL_SET_ERR_MSG(extack, "Attribute isn't type 'entry'");
			जारी;
		पूर्ण

		entry = kzalloc(माप(*entry), GFP_ATOMIC);
		अगर (!entry) अणु
			NL_SET_ERR_MSG(extack, "Not enough memory for entry");
			err = -ENOMEM;
			जाओ release_list;
		पूर्ण

		err = parse_gate_entry(n, entry, i, extack);
		अगर (err < 0) अणु
			kमुक्त(entry);
			जाओ release_list;
		पूर्ण

		list_add_tail(&entry->list, &sched->entries);
		i++;
	पूर्ण

	sched->num_entries = i;

	वापस i;

release_list:
	release_entry_list(&sched->entries);

	वापस err;
पूर्ण

अटल व्योम gate_setup_समयr(काष्ठा tcf_gate *gact, u64 baseसमय,
			     क्रमागत tk_offsets tko, s32 घड़ीid,
			     bool करो_init)
अणु
	अगर (!करो_init) अणु
		अगर (baseसमय == gact->param.tcfg_baseसमय &&
		    tko == gact->tk_offset &&
		    घड़ीid == gact->param.tcfg_घड़ीid)
			वापस;

		spin_unlock_bh(&gact->tcf_lock);
		hrसमयr_cancel(&gact->hiसमयr);
		spin_lock_bh(&gact->tcf_lock);
	पूर्ण
	gact->param.tcfg_baseसमय = baseसमय;
	gact->param.tcfg_घड़ीid = घड़ीid;
	gact->tk_offset = tko;
	hrसमयr_init(&gact->hiसमयr, घड़ीid, HRTIMER_MODE_ABS_SOFT);
	gact->hiसमयr.function = gate_समयr_func;
पूर्ण

अटल पूर्णांक tcf_gate_init(काष्ठा net *net, काष्ठा nlattr *nla,
			 काष्ठा nlattr *est, काष्ठा tc_action **a,
			 पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			 काष्ठा tcf_proto *tp, u32 flags,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, gate_net_id);
	क्रमागत tk_offsets tk_offset = TK_OFFS_TAI;
	काष्ठा nlattr *tb[TCA_GATE_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	u64 cycleसमय = 0, baseसमय = 0;
	काष्ठा tcf_gate_params *p;
	s32 घड़ीid = CLOCK_TAI;
	काष्ठा tcf_gate *gact;
	काष्ठा tc_gate *parm;
	पूर्णांक ret = 0, err;
	u32 gflags = 0;
	s32 prio = -1;
	kसमय_प्रकार start;
	u32 index;

	अगर (!nla)
		वापस -EINVAL;

	err = nla_parse_nested(tb, TCA_GATE_MAX, nla, gate_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_GATE_PARMS])
		वापस -EINVAL;

	अगर (tb[TCA_GATE_CLOCKID]) अणु
		घड़ीid = nla_get_s32(tb[TCA_GATE_CLOCKID]);
		चयन (घड़ीid) अणु
		हाल CLOCK_REALTIME:
			tk_offset = TK_OFFS_REAL;
			अवरोध;
		हाल CLOCK_MONOTONIC:
			tk_offset = TK_OFFS_MAX;
			अवरोध;
		हाल CLOCK_BOOTTIME:
			tk_offset = TK_OFFS_BOOT;
			अवरोध;
		हाल CLOCK_TAI:
			tk_offset = TK_OFFS_TAI;
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "Invalid 'clockid'");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	parm = nla_data(tb[TCA_GATE_PARMS]);
	index = parm->index;

	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;

	अगर (err && bind)
		वापस 0;

	अगर (!err) अणु
		ret = tcf_idr_create(tn, index, est, a,
				     &act_gate_ops, bind, false, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण

		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (!ovr) अणु
		tcf_idr_release(*a, bind);
		वापस -EEXIST;
	पूर्ण

	अगर (tb[TCA_GATE_PRIORITY])
		prio = nla_get_s32(tb[TCA_GATE_PRIORITY]);

	अगर (tb[TCA_GATE_BASE_TIME])
		baseसमय = nla_get_u64(tb[TCA_GATE_BASE_TIME]);

	अगर (tb[TCA_GATE_FLAGS])
		gflags = nla_get_u32(tb[TCA_GATE_FLAGS]);

	gact = to_gate(*a);
	अगर (ret == ACT_P_CREATED)
		INIT_LIST_HEAD(&gact->param.entries);

	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ release_idr;

	spin_lock_bh(&gact->tcf_lock);
	p = &gact->param;

	अगर (tb[TCA_GATE_CYCLE_TIME])
		cycleसमय = nla_get_u64(tb[TCA_GATE_CYCLE_TIME]);

	अगर (tb[TCA_GATE_ENTRY_LIST]) अणु
		err = parse_gate_list(tb[TCA_GATE_ENTRY_LIST], p, extack);
		अगर (err < 0)
			जाओ chain_put;
	पूर्ण

	अगर (!cycleसमय) अणु
		काष्ठा tcfg_gate_entry *entry;
		kसमय_प्रकार cycle = 0;

		list_क्रम_each_entry(entry, &p->entries, list)
			cycle = kसमय_add_ns(cycle, entry->पूर्णांकerval);
		cycleसमय = cycle;
		अगर (!cycleसमय) अणु
			err = -EINVAL;
			जाओ chain_put;
		पूर्ण
	पूर्ण
	p->tcfg_cycleसमय = cycleसमय;

	अगर (tb[TCA_GATE_CYCLE_TIME_EXT])
		p->tcfg_cycleसमय_ext =
			nla_get_u64(tb[TCA_GATE_CYCLE_TIME_EXT]);

	gate_setup_समयr(gact, baseसमय, tk_offset, घड़ीid,
			 ret == ACT_P_CREATED);
	p->tcfg_priority = prio;
	p->tcfg_flags = gflags;
	gate_get_start_समय(gact, &start);

	gact->current_बंद_समय = start;
	gact->current_gate_status = GATE_ACT_GATE_OPEN | GATE_ACT_PENDING;

	gact->next_entry = list_first_entry(&p->entries,
					    काष्ठा tcfg_gate_entry, list);

	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);

	gate_start_समयr(gact, start);

	spin_unlock_bh(&gact->tcf_lock);

	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);

	वापस ret;

chain_put:
	spin_unlock_bh(&gact->tcf_lock);

	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
release_idr:
	/* action is not inserted in any list: it's safe to init hiसमयr
	 * without taking tcf_lock.
	 */
	अगर (ret == ACT_P_CREATED)
		gate_setup_समयr(gact, gact->param.tcfg_baseसमय,
				 gact->tk_offset, gact->param.tcfg_घड़ीid,
				 true);
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल व्योम tcf_gate_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_gate *gact = to_gate(a);
	काष्ठा tcf_gate_params *p;

	p = &gact->param;
	hrसमयr_cancel(&gact->hiसमयr);
	release_entry_list(&p->entries);
पूर्ण

अटल पूर्णांक dumping_entry(काष्ठा sk_buff *skb,
			 काष्ठा tcfg_gate_entry *entry)
अणु
	काष्ठा nlattr *item;

	item = nla_nest_start_noflag(skb, TCA_GATE_ONE_ENTRY);
	अगर (!item)
		वापस -ENOSPC;

	अगर (nla_put_u32(skb, TCA_GATE_ENTRY_INDEX, entry->index))
		जाओ nla_put_failure;

	अगर (entry->gate_state && nla_put_flag(skb, TCA_GATE_ENTRY_GATE))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_GATE_ENTRY_INTERVAL, entry->पूर्णांकerval))
		जाओ nla_put_failure;

	अगर (nla_put_s32(skb, TCA_GATE_ENTRY_MAX_OCTETS, entry->maxoctets))
		जाओ nla_put_failure;

	अगर (nla_put_s32(skb, TCA_GATE_ENTRY_IPV, entry->ipv))
		जाओ nla_put_failure;

	वापस nla_nest_end(skb, item);

nla_put_failure:
	nla_nest_cancel(skb, item);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_gate_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			 पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_gate *gact = to_gate(a);
	काष्ठा tc_gate opt = अणु
		.index    = gact->tcf_index,
		.refcnt   = refcount_पढ़ो(&gact->tcf_refcnt) - ref,
		.bindcnt  = atomic_पढ़ो(&gact->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcfg_gate_entry *entry;
	काष्ठा tcf_gate_params *p;
	काष्ठा nlattr *entry_list;
	काष्ठा tcf_t t;

	spin_lock_bh(&gact->tcf_lock);
	opt.action = gact->tcf_action;

	p = &gact->param;

	अगर (nla_put(skb, TCA_GATE_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(skb, TCA_GATE_BASE_TIME,
			      p->tcfg_baseसमय, TCA_GATE_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(skb, TCA_GATE_CYCLE_TIME,
			      p->tcfg_cycleसमय, TCA_GATE_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(skb, TCA_GATE_CYCLE_TIME_EXT,
			      p->tcfg_cycleसमय_ext, TCA_GATE_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_s32(skb, TCA_GATE_CLOCKID, p->tcfg_घड़ीid))
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_GATE_FLAGS, p->tcfg_flags))
		जाओ nla_put_failure;

	अगर (nla_put_s32(skb, TCA_GATE_PRIORITY, p->tcfg_priority))
		जाओ nla_put_failure;

	entry_list = nla_nest_start_noflag(skb, TCA_GATE_ENTRY_LIST);
	अगर (!entry_list)
		जाओ nla_put_failure;

	list_क्रम_each_entry(entry, &p->entries, list) अणु
		अगर (dumping_entry(skb, entry) < 0)
			जाओ nla_put_failure;
	पूर्ण

	nla_nest_end(skb, entry_list);

	tcf_पंचांग_dump(&t, &gact->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_GATE_TM, माप(t), &t, TCA_GATE_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&gact->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&gact->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_gate_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			   काष्ठा netlink_callback *cb, पूर्णांक type,
			   स्थिर काष्ठा tc_action_ops *ops,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, gate_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल व्योम tcf_gate_stats_update(काष्ठा tc_action *a, u64 bytes, u64 packets,
				  u64 drops, u64 lastuse, bool hw)
अणु
	काष्ठा tcf_gate *gact = to_gate(a);
	काष्ठा tcf_t *पंचांग = &gact->tcf_पंचांग;

	tcf_action_update_stats(a, bytes, packets, drops, hw);
	पंचांग->lastuse = max_t(u64, पंचांग->lastuse, lastuse);
पूर्ण

अटल पूर्णांक tcf_gate_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, gate_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल माप_प्रकार tcf_gate_get_fill_size(स्थिर काष्ठा tc_action *act)
अणु
	वापस nla_total_size(माप(काष्ठा tc_gate));
पूर्ण

अटल काष्ठा tc_action_ops act_gate_ops = अणु
	.kind		=	"gate",
	.id		=	TCA_ID_GATE,
	.owner		=	THIS_MODULE,
	.act		=	tcf_gate_act,
	.dump		=	tcf_gate_dump,
	.init		=	tcf_gate_init,
	.cleanup	=	tcf_gate_cleanup,
	.walk		=	tcf_gate_walker,
	.stats_update	=	tcf_gate_stats_update,
	.get_fill_size	=	tcf_gate_get_fill_size,
	.lookup		=	tcf_gate_search,
	.size		=	माप(काष्ठा tcf_gate),
पूर्ण;

अटल __net_init पूर्णांक gate_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, gate_net_id);

	वापस tc_action_net_init(net, tn, &act_gate_ops);
पूर्ण

अटल व्योम __net_निकास gate_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, gate_net_id);
पूर्ण

अटल काष्ठा pernet_operations gate_net_ops = अणु
	.init = gate_init_net,
	.निकास_batch = gate_निकास_net,
	.id   = &gate_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक __init gate_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_gate_ops, &gate_net_ops);
पूर्ण

अटल व्योम __निकास gate_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_gate_ops, &gate_net_ops);
पूर्ण

module_init(gate_init_module);
module_निकास(gate_cleanup_module);
MODULE_LICENSE("GPL v2");
