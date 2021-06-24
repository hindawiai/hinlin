<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/cls_flow.c		Generic flow classअगरier
 *
 * Copyright (c) 2007, 2008 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/jhash.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <net/inet_sock.h>

#समावेश <net/pkt_cls.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/flow_dissector.h>

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#पूर्ण_अगर

काष्ठा flow_head अणु
	काष्ठा list_head	filters;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा flow_filter अणु
	काष्ठा list_head	list;
	काष्ठा tcf_exts		exts;
	काष्ठा tcf_ematch_tree	ematches;
	काष्ठा tcf_proto	*tp;
	काष्ठा समयr_list	perturb_समयr;
	u32			perturb_period;
	u32			handle;

	u32			nkeys;
	u32			keymask;
	u32			mode;
	u32			mask;
	u32			xor;
	u32			rshअगरt;
	u32			addend;
	u32			भागisor;
	u32			baseclass;
	u32			hashrnd;
	काष्ठा rcu_work		rwork;
पूर्ण;

अटल अंतरभूत u32 addr_fold(व्योम *addr)
अणु
	अचिन्हित दीर्घ a = (अचिन्हित दीर्घ)addr;

	वापस (a & 0xFFFFFFFF) ^ (BITS_PER_LONG > 32 ? a >> 32 : 0);
पूर्ण

अटल u32 flow_get_src(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा flow_keys *flow)
अणु
	__be32 src = flow_get_u32_src(flow);

	अगर (src)
		वापस ntohl(src);

	वापस addr_fold(skb->sk);
पूर्ण

अटल u32 flow_get_dst(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा flow_keys *flow)
अणु
	__be32 dst = flow_get_u32_dst(flow);

	अगर (dst)
		वापस ntohl(dst);

	वापस addr_fold(skb_dst(skb)) ^ (__क्रमce u16)skb_protocol(skb, true);
पूर्ण

अटल u32 flow_get_proto(स्थिर काष्ठा sk_buff *skb,
			  स्थिर काष्ठा flow_keys *flow)
अणु
	वापस flow->basic.ip_proto;
पूर्ण

अटल u32 flow_get_proto_src(स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा flow_keys *flow)
अणु
	अगर (flow->ports.ports)
		वापस ntohs(flow->ports.src);

	वापस addr_fold(skb->sk);
पूर्ण

अटल u32 flow_get_proto_dst(स्थिर काष्ठा sk_buff *skb,
			      स्थिर काष्ठा flow_keys *flow)
अणु
	अगर (flow->ports.ports)
		वापस ntohs(flow->ports.dst);

	वापस addr_fold(skb_dst(skb)) ^ (__क्रमce u16)skb_protocol(skb, true);
पूर्ण

अटल u32 flow_get_iअगर(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->skb_iअगर;
पूर्ण

अटल u32 flow_get_priority(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->priority;
पूर्ण

अटल u32 flow_get_mark(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->mark;
पूर्ण

अटल u32 flow_get_nfct(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	वापस addr_fold(skb_nfct(skb));
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#घोषणा CTTUPLE(skb, member)						\
(अणु									\
	क्रमागत ip_conntrack_info ctinfo;					\
	स्थिर काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);		\
	अगर (ct == शून्य)							\
		जाओ fallback;						\
	ct->tuplehash[CTINFO2सूची(ctinfo)].tuple.member;			\
पूर्ण)
#अन्यथा
#घोषणा CTTUPLE(skb, member)						\
(अणु									\
	जाओ fallback;							\
	0;								\
पूर्ण)
#पूर्ण_अगर

अटल u32 flow_get_nfct_src(स्थिर काष्ठा sk_buff *skb,
			     स्थिर काष्ठा flow_keys *flow)
अणु
	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		वापस ntohl(CTTUPLE(skb, src.u3.ip));
	हाल htons(ETH_P_IPV6):
		वापस ntohl(CTTUPLE(skb, src.u3.ip6[3]));
	पूर्ण
fallback:
	वापस flow_get_src(skb, flow);
पूर्ण

अटल u32 flow_get_nfct_dst(स्थिर काष्ठा sk_buff *skb,
			     स्थिर काष्ठा flow_keys *flow)
अणु
	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		वापस ntohl(CTTUPLE(skb, dst.u3.ip));
	हाल htons(ETH_P_IPV6):
		वापस ntohl(CTTUPLE(skb, dst.u3.ip6[3]));
	पूर्ण
fallback:
	वापस flow_get_dst(skb, flow);
पूर्ण

अटल u32 flow_get_nfct_proto_src(स्थिर काष्ठा sk_buff *skb,
				   स्थिर काष्ठा flow_keys *flow)
अणु
	वापस ntohs(CTTUPLE(skb, src.u.all));
fallback:
	वापस flow_get_proto_src(skb, flow);
पूर्ण

अटल u32 flow_get_nfct_proto_dst(स्थिर काष्ठा sk_buff *skb,
				   स्थिर काष्ठा flow_keys *flow)
अणु
	वापस ntohs(CTTUPLE(skb, dst.u.all));
fallback:
	वापस flow_get_proto_dst(skb, flow);
पूर्ण

अटल u32 flow_get_rtclassid(स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	अगर (skb_dst(skb))
		वापस skb_dst(skb)->tclassid;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल u32 flow_get_skuid(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (sk && sk->sk_socket && sk->sk_socket->file) अणु
		kuid_t skuid = sk->sk_socket->file->f_cred->fsuid;

		वापस from_kuid(&init_user_ns, skuid);
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 flow_get_skgid(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (sk && sk->sk_socket && sk->sk_socket->file) अणु
		kgid_t skgid = sk->sk_socket->file->f_cred->fsgid;

		वापस from_kgid(&init_user_ns, skgid);
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 flow_get_vlan_tag(स्थिर काष्ठा sk_buff *skb)
अणु
	u16 tag;

	अगर (vlan_get_tag(skb, &tag) < 0)
		वापस 0;
	वापस tag & VLAN_VID_MASK;
पूर्ण

अटल u32 flow_get_rxhash(काष्ठा sk_buff *skb)
अणु
	वापस skb_get_hash(skb);
पूर्ण

अटल u32 flow_key_get(काष्ठा sk_buff *skb, पूर्णांक key, काष्ठा flow_keys *flow)
अणु
	चयन (key) अणु
	हाल FLOW_KEY_SRC:
		वापस flow_get_src(skb, flow);
	हाल FLOW_KEY_DST:
		वापस flow_get_dst(skb, flow);
	हाल FLOW_KEY_PROTO:
		वापस flow_get_proto(skb, flow);
	हाल FLOW_KEY_PROTO_SRC:
		वापस flow_get_proto_src(skb, flow);
	हाल FLOW_KEY_PROTO_DST:
		वापस flow_get_proto_dst(skb, flow);
	हाल FLOW_KEY_IIF:
		वापस flow_get_iअगर(skb);
	हाल FLOW_KEY_PRIORITY:
		वापस flow_get_priority(skb);
	हाल FLOW_KEY_MARK:
		वापस flow_get_mark(skb);
	हाल FLOW_KEY_NFCT:
		वापस flow_get_nfct(skb);
	हाल FLOW_KEY_NFCT_SRC:
		वापस flow_get_nfct_src(skb, flow);
	हाल FLOW_KEY_NFCT_DST:
		वापस flow_get_nfct_dst(skb, flow);
	हाल FLOW_KEY_NFCT_PROTO_SRC:
		वापस flow_get_nfct_proto_src(skb, flow);
	हाल FLOW_KEY_NFCT_PROTO_DST:
		वापस flow_get_nfct_proto_dst(skb, flow);
	हाल FLOW_KEY_RTCLASSID:
		वापस flow_get_rtclassid(skb);
	हाल FLOW_KEY_SKUID:
		वापस flow_get_skuid(skb);
	हाल FLOW_KEY_SKGID:
		वापस flow_get_skgid(skb);
	हाल FLOW_KEY_VLAN_TAG:
		वापस flow_get_vlan_tag(skb);
	हाल FLOW_KEY_RXHASH:
		वापस flow_get_rxhash(skb);
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

#घोषणा FLOW_KEYS_NEEDED ((1 << FLOW_KEY_SRC) | 		\
			  (1 << FLOW_KEY_DST) |			\
			  (1 << FLOW_KEY_PROTO) |		\
			  (1 << FLOW_KEY_PROTO_SRC) |		\
			  (1 << FLOW_KEY_PROTO_DST) | 		\
			  (1 << FLOW_KEY_NFCT_SRC) |		\
			  (1 << FLOW_KEY_NFCT_DST) |		\
			  (1 << FLOW_KEY_NFCT_PROTO_SRC) |	\
			  (1 << FLOW_KEY_NFCT_PROTO_DST))

अटल पूर्णांक flow_classअगरy(काष्ठा sk_buff *skb, स्थिर काष्ठा tcf_proto *tp,
			 काष्ठा tcf_result *res)
अणु
	काष्ठा flow_head *head = rcu_dereference_bh(tp->root);
	काष्ठा flow_filter *f;
	u32 keymask;
	u32 classid;
	अचिन्हित पूर्णांक n, key;
	पूर्णांक r;

	list_क्रम_each_entry_rcu(f, &head->filters, list) अणु
		u32 keys[FLOW_KEY_MAX + 1];
		काष्ठा flow_keys flow_keys;

		अगर (!tcf_em_tree_match(skb, &f->ematches, शून्य))
			जारी;

		keymask = f->keymask;
		अगर (keymask & FLOW_KEYS_NEEDED)
			skb_flow_dissect_flow_keys(skb, &flow_keys, 0);

		क्रम (n = 0; n < f->nkeys; n++) अणु
			key = ffs(keymask) - 1;
			keymask &= ~(1 << key);
			keys[n] = flow_key_get(skb, key, &flow_keys);
		पूर्ण

		अगर (f->mode == FLOW_MODE_HASH)
			classid = jhash2(keys, f->nkeys, f->hashrnd);
		अन्यथा अणु
			classid = keys[0];
			classid = (classid & f->mask) ^ f->xor;
			classid = (classid >> f->rshअगरt) + f->addend;
		पूर्ण

		अगर (f->भागisor)
			classid %= f->भागisor;

		res->class   = 0;
		res->classid = TC_H_MAKE(f->baseclass, f->baseclass + classid);

		r = tcf_exts_exec(skb, &f->exts, res);
		अगर (r < 0)
			जारी;
		वापस r;
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम flow_perturbation(काष्ठा समयr_list *t)
अणु
	काष्ठा flow_filter *f = from_समयr(f, t, perturb_समयr);

	get_अक्रमom_bytes(&f->hashrnd, 4);
	अगर (f->perturb_period)
		mod_समयr(&f->perturb_समयr, jअगरfies + f->perturb_period);
पूर्ण

अटल स्थिर काष्ठा nla_policy flow_policy[TCA_FLOW_MAX + 1] = अणु
	[TCA_FLOW_KEYS]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOW_MODE]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOW_BASECLASS]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOW_RSHIFT]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOW_ADDEND]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOW_MASK]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOW_XOR]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOW_DIVISOR]	= अणु .type = NLA_U32 पूर्ण,
	[TCA_FLOW_ACT]		= अणु .type = NLA_NESTED पूर्ण,
	[TCA_FLOW_POLICE]	= अणु .type = NLA_NESTED पूर्ण,
	[TCA_FLOW_EMATCHES]	= अणु .type = NLA_NESTED पूर्ण,
	[TCA_FLOW_PERTURB]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल व्योम __flow_destroy_filter(काष्ठा flow_filter *f)
अणु
	del_समयr_sync(&f->perturb_समयr);
	tcf_exts_destroy(&f->exts);
	tcf_em_tree_destroy(&f->ematches);
	tcf_exts_put_net(&f->exts);
	kमुक्त(f);
पूर्ण

अटल व्योम flow_destroy_filter_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा flow_filter *f = container_of(to_rcu_work(work),
					     काष्ठा flow_filter,
					     rwork);
	rtnl_lock();
	__flow_destroy_filter(f);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक flow_change(काष्ठा net *net, काष्ठा sk_buff *in_skb,
		       काष्ठा tcf_proto *tp, अचिन्हित दीर्घ base,
		       u32 handle, काष्ठा nlattr **tca,
		       व्योम **arg, bool ovr, bool rtnl_held,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा flow_head *head = rtnl_dereference(tp->root);
	काष्ठा flow_filter *fold, *fnew;
	काष्ठा nlattr *opt = tca[TCA_OPTIONS];
	काष्ठा nlattr *tb[TCA_FLOW_MAX + 1];
	अचिन्हित पूर्णांक nkeys = 0;
	अचिन्हित पूर्णांक perturb_period = 0;
	u32 baseclass = 0;
	u32 keymask = 0;
	u32 mode;
	पूर्णांक err;

	अगर (opt == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_FLOW_MAX, opt, flow_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_FLOW_BASECLASS]) अणु
		baseclass = nla_get_u32(tb[TCA_FLOW_BASECLASS]);
		अगर (TC_H_MIN(baseclass) == 0)
			वापस -EINVAL;
	पूर्ण

	अगर (tb[TCA_FLOW_KEYS]) अणु
		keymask = nla_get_u32(tb[TCA_FLOW_KEYS]);

		nkeys = hweight32(keymask);
		अगर (nkeys == 0)
			वापस -EINVAL;

		अगर (fls(keymask) - 1 > FLOW_KEY_MAX)
			वापस -EOPNOTSUPP;

		अगर ((keymask & (FLOW_KEY_SKUID|FLOW_KEY_SKGID)) &&
		    sk_user_ns(NETLINK_CB(in_skb).sk) != &init_user_ns)
			वापस -EOPNOTSUPP;
	पूर्ण

	fnew = kzalloc(माप(*fnew), GFP_KERNEL);
	अगर (!fnew)
		वापस -ENOBUFS;

	err = tcf_em_tree_validate(tp, tb[TCA_FLOW_EMATCHES], &fnew->ematches);
	अगर (err < 0)
		जाओ err1;

	err = tcf_exts_init(&fnew->exts, net, TCA_FLOW_ACT, TCA_FLOW_POLICE);
	अगर (err < 0)
		जाओ err2;

	err = tcf_exts_validate(net, tp, tb, tca[TCA_RATE], &fnew->exts, ovr,
				true, extack);
	अगर (err < 0)
		जाओ err2;

	fold = *arg;
	अगर (fold) अणु
		err = -EINVAL;
		अगर (fold->handle != handle && handle)
			जाओ err2;

		/* Copy fold पूर्णांकo fnew */
		fnew->tp = fold->tp;
		fnew->handle = fold->handle;
		fnew->nkeys = fold->nkeys;
		fnew->keymask = fold->keymask;
		fnew->mode = fold->mode;
		fnew->mask = fold->mask;
		fnew->xor = fold->xor;
		fnew->rshअगरt = fold->rshअगरt;
		fnew->addend = fold->addend;
		fnew->भागisor = fold->भागisor;
		fnew->baseclass = fold->baseclass;
		fnew->hashrnd = fold->hashrnd;

		mode = fold->mode;
		अगर (tb[TCA_FLOW_MODE])
			mode = nla_get_u32(tb[TCA_FLOW_MODE]);
		अगर (mode != FLOW_MODE_HASH && nkeys > 1)
			जाओ err2;

		अगर (mode == FLOW_MODE_HASH)
			perturb_period = fold->perturb_period;
		अगर (tb[TCA_FLOW_PERTURB]) अणु
			अगर (mode != FLOW_MODE_HASH)
				जाओ err2;
			perturb_period = nla_get_u32(tb[TCA_FLOW_PERTURB]) * HZ;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		अगर (!handle)
			जाओ err2;
		अगर (!tb[TCA_FLOW_KEYS])
			जाओ err2;

		mode = FLOW_MODE_MAP;
		अगर (tb[TCA_FLOW_MODE])
			mode = nla_get_u32(tb[TCA_FLOW_MODE]);
		अगर (mode != FLOW_MODE_HASH && nkeys > 1)
			जाओ err2;

		अगर (tb[TCA_FLOW_PERTURB]) अणु
			अगर (mode != FLOW_MODE_HASH)
				जाओ err2;
			perturb_period = nla_get_u32(tb[TCA_FLOW_PERTURB]) * HZ;
		पूर्ण

		अगर (TC_H_MAJ(baseclass) == 0) अणु
			काष्ठा Qdisc *q = tcf_block_q(tp->chain->block);

			baseclass = TC_H_MAKE(q->handle, baseclass);
		पूर्ण
		अगर (TC_H_MIN(baseclass) == 0)
			baseclass = TC_H_MAKE(baseclass, 1);

		fnew->handle = handle;
		fnew->mask  = ~0U;
		fnew->tp = tp;
		get_अक्रमom_bytes(&fnew->hashrnd, 4);
	पूर्ण

	समयr_setup(&fnew->perturb_समयr, flow_perturbation, TIMER_DEFERRABLE);

	tcf_block_netअगर_keep_dst(tp->chain->block);

	अगर (tb[TCA_FLOW_KEYS]) अणु
		fnew->keymask = keymask;
		fnew->nkeys   = nkeys;
	पूर्ण

	fnew->mode = mode;

	अगर (tb[TCA_FLOW_MASK])
		fnew->mask = nla_get_u32(tb[TCA_FLOW_MASK]);
	अगर (tb[TCA_FLOW_XOR])
		fnew->xor = nla_get_u32(tb[TCA_FLOW_XOR]);
	अगर (tb[TCA_FLOW_RSHIFT])
		fnew->rshअगरt = nla_get_u32(tb[TCA_FLOW_RSHIFT]);
	अगर (tb[TCA_FLOW_ADDEND])
		fnew->addend = nla_get_u32(tb[TCA_FLOW_ADDEND]);

	अगर (tb[TCA_FLOW_DIVISOR])
		fnew->भागisor = nla_get_u32(tb[TCA_FLOW_DIVISOR]);
	अगर (baseclass)
		fnew->baseclass = baseclass;

	fnew->perturb_period = perturb_period;
	अगर (perturb_period)
		mod_समयr(&fnew->perturb_समयr, jअगरfies + perturb_period);

	अगर (!*arg)
		list_add_tail_rcu(&fnew->list, &head->filters);
	अन्यथा
		list_replace_rcu(&fold->list, &fnew->list);

	*arg = fnew;

	अगर (fold) अणु
		tcf_exts_get_net(&fold->exts);
		tcf_queue_work(&fold->rwork, flow_destroy_filter_work);
	पूर्ण
	वापस 0;

err2:
	tcf_exts_destroy(&fnew->exts);
	tcf_em_tree_destroy(&fnew->ematches);
err1:
	kमुक्त(fnew);
	वापस err;
पूर्ण

अटल पूर्णांक flow_delete(काष्ठा tcf_proto *tp, व्योम *arg, bool *last,
		       bool rtnl_held, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा flow_head *head = rtnl_dereference(tp->root);
	काष्ठा flow_filter *f = arg;

	list_del_rcu(&f->list);
	tcf_exts_get_net(&f->exts);
	tcf_queue_work(&f->rwork, flow_destroy_filter_work);
	*last = list_empty(&head->filters);
	वापस 0;
पूर्ण

अटल पूर्णांक flow_init(काष्ठा tcf_proto *tp)
अणु
	काष्ठा flow_head *head;

	head = kzalloc(माप(*head), GFP_KERNEL);
	अगर (head == शून्य)
		वापस -ENOBUFS;
	INIT_LIST_HEAD(&head->filters);
	rcu_assign_poपूर्णांकer(tp->root, head);
	वापस 0;
पूर्ण

अटल व्योम flow_destroy(काष्ठा tcf_proto *tp, bool rtnl_held,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा flow_head *head = rtnl_dereference(tp->root);
	काष्ठा flow_filter *f, *next;

	list_क्रम_each_entry_safe(f, next, &head->filters, list) अणु
		list_del_rcu(&f->list);
		अगर (tcf_exts_get_net(&f->exts))
			tcf_queue_work(&f->rwork, flow_destroy_filter_work);
		अन्यथा
			__flow_destroy_filter(f);
	पूर्ण
	kमुक्त_rcu(head, rcu);
पूर्ण

अटल व्योम *flow_get(काष्ठा tcf_proto *tp, u32 handle)
अणु
	काष्ठा flow_head *head = rtnl_dereference(tp->root);
	काष्ठा flow_filter *f;

	list_क्रम_each_entry(f, &head->filters, list)
		अगर (f->handle == handle)
			वापस f;
	वापस शून्य;
पूर्ण

अटल पूर्णांक flow_dump(काष्ठा net *net, काष्ठा tcf_proto *tp, व्योम *fh,
		     काष्ठा sk_buff *skb, काष्ठा tcmsg *t, bool rtnl_held)
अणु
	काष्ठा flow_filter *f = fh;
	काष्ठा nlattr *nest;

	अगर (f == शून्य)
		वापस skb->len;

	t->tcm_handle = f->handle;

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, TCA_FLOW_KEYS, f->keymask) ||
	    nla_put_u32(skb, TCA_FLOW_MODE, f->mode))
		जाओ nla_put_failure;

	अगर (f->mask != ~0 || f->xor != 0) अणु
		अगर (nla_put_u32(skb, TCA_FLOW_MASK, f->mask) ||
		    nla_put_u32(skb, TCA_FLOW_XOR, f->xor))
			जाओ nla_put_failure;
	पूर्ण
	अगर (f->rshअगरt &&
	    nla_put_u32(skb, TCA_FLOW_RSHIFT, f->rshअगरt))
		जाओ nla_put_failure;
	अगर (f->addend &&
	    nla_put_u32(skb, TCA_FLOW_ADDEND, f->addend))
		जाओ nla_put_failure;

	अगर (f->भागisor &&
	    nla_put_u32(skb, TCA_FLOW_DIVISOR, f->भागisor))
		जाओ nla_put_failure;
	अगर (f->baseclass &&
	    nla_put_u32(skb, TCA_FLOW_BASECLASS, f->baseclass))
		जाओ nla_put_failure;

	अगर (f->perturb_period &&
	    nla_put_u32(skb, TCA_FLOW_PERTURB, f->perturb_period / HZ))
		जाओ nla_put_failure;

	अगर (tcf_exts_dump(skb, &f->exts) < 0)
		जाओ nla_put_failure;
#अगर_घोषित CONFIG_NET_EMATCH
	अगर (f->ematches.hdr.nmatches &&
	    tcf_em_tree_dump(skb, &f->ematches, TCA_FLOW_EMATCHES) < 0)
		जाओ nla_put_failure;
#पूर्ण_अगर
	nla_nest_end(skb, nest);

	अगर (tcf_exts_dump_stats(skb, &f->exts) < 0)
		जाओ nla_put_failure;

	वापस skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल व्योम flow_walk(काष्ठा tcf_proto *tp, काष्ठा tcf_walker *arg,
		      bool rtnl_held)
अणु
	काष्ठा flow_head *head = rtnl_dereference(tp->root);
	काष्ठा flow_filter *f;

	list_क्रम_each_entry(f, &head->filters, list) अणु
		अगर (arg->count < arg->skip)
			जाओ skip;
		अगर (arg->fn(tp, f, arg) < 0) अणु
			arg->stop = 1;
			अवरोध;
		पूर्ण
skip:
		arg->count++;
	पूर्ण
पूर्ण

अटल काष्ठा tcf_proto_ops cls_flow_ops __पढ़ो_mostly = अणु
	.kind		= "flow",
	.classअगरy	= flow_classअगरy,
	.init		= flow_init,
	.destroy	= flow_destroy,
	.change		= flow_change,
	.delete		= flow_delete,
	.get		= flow_get,
	.dump		= flow_dump,
	.walk		= flow_walk,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init cls_flow_init(व्योम)
अणु
	वापस रेजिस्टर_tcf_proto_ops(&cls_flow_ops);
पूर्ण

अटल व्योम __निकास cls_flow_निकास(व्योम)
अणु
	unरेजिस्टर_tcf_proto_ops(&cls_flow_ops);
पूर्ण

module_init(cls_flow_init);
module_निकास(cls_flow_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("TC flow classifier");
