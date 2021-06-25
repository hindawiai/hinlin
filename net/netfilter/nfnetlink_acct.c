<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) 2011 Pablo Neira Ayuso <pablo@netfilter.org>
 * (C) 2011 Intra2net AG <https://www.पूर्णांकra2net.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rculist.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <net/netlink.h>
#समावेश <net/sock.h>
#समावेश <net/netns/generic.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_acct.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_DESCRIPTION("nfacct: Extended Netfilter accounting infrastructure");

काष्ठा nf_acct अणु
	atomic64_t		pkts;
	atomic64_t		bytes;
	अचिन्हित दीर्घ		flags;
	काष्ठा list_head	head;
	refcount_t		refcnt;
	अक्षर			name[NFACCT_NAME_MAX];
	काष्ठा rcu_head		rcu_head;
	अक्षर			data[];
पूर्ण;

काष्ठा nfacct_filter अणु
	u32 value;
	u32 mask;
पूर्ण;

काष्ठा nfnl_acct_net अणु
	काष्ठा list_head        nfnl_acct_list;
पूर्ण;

अटल अचिन्हित पूर्णांक nfnl_acct_net_id __पढ़ो_mostly;

अटल अंतरभूत काष्ठा nfnl_acct_net *nfnl_acct_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, nfnl_acct_net_id);
पूर्ण

#घोषणा NFACCT_F_QUOTA (NFACCT_F_QUOTA_PKTS | NFACCT_F_QUOTA_BYTES)
#घोषणा NFACCT_OVERQUOTA_BIT	2	/* NFACCT_F_OVERQUOTA */

अटल पूर्णांक nfnl_acct_new(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			 स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nfnl_acct_net *nfnl_acct_net = nfnl_acct_pernet(info->net);
	काष्ठा nf_acct *nfacct, *matching = शून्य;
	अचिन्हित पूर्णांक size = 0;
	अक्षर *acct_name;
	u32 flags = 0;

	अगर (!tb[NFACCT_NAME])
		वापस -EINVAL;

	acct_name = nla_data(tb[NFACCT_NAME]);
	अगर (म_माप(acct_name) == 0)
		वापस -EINVAL;

	list_क्रम_each_entry(nfacct, &nfnl_acct_net->nfnl_acct_list, head) अणु
		अगर (म_भेदन(nfacct->name, acct_name, NFACCT_NAME_MAX) != 0)
			जारी;

                अगर (info->nlh->nlmsg_flags & NLM_F_EXCL)
			वापस -EEXIST;

		matching = nfacct;
		अवरोध;
        पूर्ण

	अगर (matching) अणु
		अगर (info->nlh->nlmsg_flags & NLM_F_REPLACE) अणु
			/* reset counters अगर you request a replacement. */
			atomic64_set(&matching->pkts, 0);
			atomic64_set(&matching->bytes, 0);
			smp_mb__beक्रमe_atomic();
			/* reset overquota flag अगर quota is enabled. */
			अगर ((matching->flags & NFACCT_F_QUOTA))
				clear_bit(NFACCT_OVERQUOTA_BIT,
					  &matching->flags);
			वापस 0;
		पूर्ण
		वापस -EBUSY;
	पूर्ण

	अगर (tb[NFACCT_FLAGS]) अणु
		flags = ntohl(nla_get_be32(tb[NFACCT_FLAGS]));
		अगर (flags & ~NFACCT_F_QUOTA)
			वापस -EOPNOTSUPP;
		अगर ((flags & NFACCT_F_QUOTA) == NFACCT_F_QUOTA)
			वापस -EINVAL;
		अगर (flags & NFACCT_F_OVERQUOTA)
			वापस -EINVAL;
		अगर ((flags & NFACCT_F_QUOTA) && !tb[NFACCT_QUOTA])
			वापस -EINVAL;

		size += माप(u64);
	पूर्ण

	nfacct = kzalloc(माप(काष्ठा nf_acct) + size, GFP_KERNEL);
	अगर (nfacct == शून्य)
		वापस -ENOMEM;

	अगर (flags & NFACCT_F_QUOTA) अणु
		u64 *quota = (u64 *)nfacct->data;

		*quota = be64_to_cpu(nla_get_be64(tb[NFACCT_QUOTA]));
		nfacct->flags = flags;
	पूर्ण

	nla_strscpy(nfacct->name, tb[NFACCT_NAME], NFACCT_NAME_MAX);

	अगर (tb[NFACCT_BYTES]) अणु
		atomic64_set(&nfacct->bytes,
			     be64_to_cpu(nla_get_be64(tb[NFACCT_BYTES])));
	पूर्ण
	अगर (tb[NFACCT_PKTS]) अणु
		atomic64_set(&nfacct->pkts,
			     be64_to_cpu(nla_get_be64(tb[NFACCT_PKTS])));
	पूर्ण
	refcount_set(&nfacct->refcnt, 1);
	list_add_tail_rcu(&nfacct->head, &nfnl_acct_net->nfnl_acct_list);
	वापस 0;
पूर्ण

अटल पूर्णांक
nfnl_acct_fill_info(काष्ठा sk_buff *skb, u32 portid, u32 seq, u32 type,
		   पूर्णांक event, काष्ठा nf_acct *acct)
अणु
	काष्ठा nlmsghdr *nlh;
	अचिन्हित पूर्णांक flags = portid ? NLM_F_MULTI : 0;
	u64 pkts, bytes;
	u32 old_flags;

	event = nfnl_msg_type(NFNL_SUBSYS_ACCT, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, AF_UNSPEC,
			   NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nlmsg_failure;

	अगर (nla_put_string(skb, NFACCT_NAME, acct->name))
		जाओ nla_put_failure;

	old_flags = acct->flags;
	अगर (type == NFNL_MSG_ACCT_GET_CTRZERO) अणु
		pkts = atomic64_xchg(&acct->pkts, 0);
		bytes = atomic64_xchg(&acct->bytes, 0);
		smp_mb__beक्रमe_atomic();
		अगर (acct->flags & NFACCT_F_QUOTA)
			clear_bit(NFACCT_OVERQUOTA_BIT, &acct->flags);
	पूर्ण अन्यथा अणु
		pkts = atomic64_पढ़ो(&acct->pkts);
		bytes = atomic64_पढ़ो(&acct->bytes);
	पूर्ण
	अगर (nla_put_be64(skb, NFACCT_PKTS, cpu_to_be64(pkts),
			 NFACCT_PAD) ||
	    nla_put_be64(skb, NFACCT_BYTES, cpu_to_be64(bytes),
			 NFACCT_PAD) ||
	    nla_put_be32(skb, NFACCT_USE, htonl(refcount_पढ़ो(&acct->refcnt))))
		जाओ nla_put_failure;
	अगर (acct->flags & NFACCT_F_QUOTA) अणु
		u64 *quota = (u64 *)acct->data;

		अगर (nla_put_be32(skb, NFACCT_FLAGS, htonl(old_flags)) ||
		    nla_put_be64(skb, NFACCT_QUOTA, cpu_to_be64(*quota),
				 NFACCT_PAD))
			जाओ nla_put_failure;
	पूर्ण
	nlmsg_end(skb, nlh);
	वापस skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -1;
पूर्ण

अटल पूर्णांक
nfnl_acct_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nfnl_acct_net *nfnl_acct_net = nfnl_acct_pernet(net);
	काष्ठा nf_acct *cur, *last;
	स्थिर काष्ठा nfacct_filter *filter = cb->data;

	अगर (cb->args[2])
		वापस 0;

	last = (काष्ठा nf_acct *)cb->args[1];
	अगर (cb->args[1])
		cb->args[1] = 0;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(cur, &nfnl_acct_net->nfnl_acct_list, head) अणु
		अगर (last) अणु
			अगर (cur != last)
				जारी;

			last = शून्य;
		पूर्ण

		अगर (filter && (cur->flags & filter->mask) != filter->value)
			जारी;

		अगर (nfnl_acct_fill_info(skb, NETLINK_CB(cb->skb).portid,
				       cb->nlh->nlmsg_seq,
				       NFNL_MSG_TYPE(cb->nlh->nlmsg_type),
				       NFNL_MSG_ACCT_NEW, cur) < 0) अणु
			cb->args[1] = (अचिन्हित दीर्घ)cur;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!cb->args[1])
		cb->args[2] = 1;
	rcu_पढ़ो_unlock();
	वापस skb->len;
पूर्ण

अटल पूर्णांक nfnl_acct_करोne(काष्ठा netlink_callback *cb)
अणु
	kमुक्त(cb->data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy filter_policy[NFACCT_FILTER_MAX + 1] = अणु
	[NFACCT_FILTER_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[NFACCT_FILTER_VALUE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nfnl_acct_start(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlattr *स्थिर attr = cb->data;
	काष्ठा nlattr *tb[NFACCT_FILTER_MAX + 1];
	काष्ठा nfacct_filter *filter;
	पूर्णांक err;

	अगर (!attr)
		वापस 0;

	err = nla_parse_nested_deprecated(tb, NFACCT_FILTER_MAX, attr,
					  filter_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFACCT_FILTER_MASK] || !tb[NFACCT_FILTER_VALUE])
		वापस -EINVAL;

	filter = kzalloc(माप(काष्ठा nfacct_filter), GFP_KERNEL);
	अगर (!filter)
		वापस -ENOMEM;

	filter->mask = ntohl(nla_get_be32(tb[NFACCT_FILTER_MASK]));
	filter->value = ntohl(nla_get_be32(tb[NFACCT_FILTER_VALUE]));
	cb->data = filter;

	वापस 0;
पूर्ण

अटल पूर्णांक nfnl_acct_get(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			 स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nfnl_acct_net *nfnl_acct_net = nfnl_acct_pernet(info->net);
	पूर्णांक ret = -ENOENT;
	काष्ठा nf_acct *cur;
	अक्षर *acct_name;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = nfnl_acct_dump,
			.start = nfnl_acct_start,
			.करोne = nfnl_acct_करोne,
			.data = (व्योम *)tb[NFACCT_FILTER],
		पूर्ण;

		वापस netlink_dump_start(info->sk, skb, info->nlh, &c);
	पूर्ण

	अगर (!tb[NFACCT_NAME])
		वापस -EINVAL;
	acct_name = nla_data(tb[NFACCT_NAME]);

	list_क्रम_each_entry(cur, &nfnl_acct_net->nfnl_acct_list, head) अणु
		काष्ठा sk_buff *skb2;

		अगर (म_भेदन(cur->name, acct_name, NFACCT_NAME_MAX)!= 0)
			जारी;

		skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
		अगर (skb2 == शून्य) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		ret = nfnl_acct_fill_info(skb2, NETLINK_CB(skb).portid,
					  info->nlh->nlmsg_seq,
					  NFNL_MSG_TYPE(info->nlh->nlmsg_type),
					  NFNL_MSG_ACCT_NEW, cur);
		अगर (ret <= 0) अणु
			kमुक्त_skb(skb2);
			अवरोध;
		पूर्ण
		ret = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
				      MSG_DONTWAIT);
		अगर (ret > 0)
			ret = 0;

		/* this aव्योमs a loop in nfnetlink. */
		वापस ret == -EAGAIN ? -ENOBUFS : ret;
	पूर्ण
	वापस ret;
पूर्ण

/* try to delete object, fail अगर it is still in use. */
अटल पूर्णांक nfnl_acct_try_del(काष्ठा nf_acct *cur)
अणु
	पूर्णांक ret = 0;

	/* We want to aव्योम races with nfnl_acct_put. So only when the current
	 * refcnt is 1, we decrease it to 0.
	 */
	अगर (refcount_dec_अगर_one(&cur->refcnt)) अणु
		/* We are रक्षित by nfnl mutex. */
		list_del_rcu(&cur->head);
		kमुक्त_rcu(cur, rcu_head);
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nfnl_acct_del(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			 स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nfnl_acct_net *nfnl_acct_net = nfnl_acct_pernet(info->net);
	काष्ठा nf_acct *cur, *पंचांगp;
	पूर्णांक ret = -ENOENT;
	अक्षर *acct_name;

	अगर (!tb[NFACCT_NAME]) अणु
		list_क्रम_each_entry_safe(cur, पंचांगp, &nfnl_acct_net->nfnl_acct_list, head)
			nfnl_acct_try_del(cur);

		वापस 0;
	पूर्ण
	acct_name = nla_data(tb[NFACCT_NAME]);

	list_क्रम_each_entry(cur, &nfnl_acct_net->nfnl_acct_list, head) अणु
		अगर (म_भेदन(cur->name, acct_name, NFACCT_NAME_MAX) != 0)
			जारी;

		ret = nfnl_acct_try_del(cur);
		अगर (ret < 0)
			वापस ret;

		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nla_policy nfnl_acct_policy[NFACCT_MAX+1] = अणु
	[NFACCT_NAME] = अणु .type = NLA_NUL_STRING, .len = NFACCT_NAME_MAX-1 पूर्ण,
	[NFACCT_BYTES] = अणु .type = NLA_U64 पूर्ण,
	[NFACCT_PKTS] = अणु .type = NLA_U64 पूर्ण,
	[NFACCT_FLAGS] = अणु .type = NLA_U32 पूर्ण,
	[NFACCT_QUOTA] = अणु .type = NLA_U64 पूर्ण,
	[NFACCT_FILTER] = अणु.type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnl_callback nfnl_acct_cb[NFNL_MSG_ACCT_MAX] = अणु
	[NFNL_MSG_ACCT_NEW] = अणु
		.call		= nfnl_acct_new,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= NFACCT_MAX,
		.policy		= nfnl_acct_policy
	पूर्ण,
	[NFNL_MSG_ACCT_GET] = अणु
		.call		= nfnl_acct_get,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= NFACCT_MAX,
		.policy		= nfnl_acct_policy
	पूर्ण,
	[NFNL_MSG_ACCT_GET_CTRZERO] = अणु
		.call		= nfnl_acct_get,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= NFACCT_MAX,
		.policy		= nfnl_acct_policy
	पूर्ण,
	[NFNL_MSG_ACCT_DEL] = अणु
		.call		= nfnl_acct_del,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= NFACCT_MAX,
		.policy		= nfnl_acct_policy
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnetlink_subप्रणाली nfnl_acct_subsys = अणु
	.name				= "acct",
	.subsys_id			= NFNL_SUBSYS_ACCT,
	.cb_count			= NFNL_MSG_ACCT_MAX,
	.cb				= nfnl_acct_cb,
पूर्ण;

MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_ACCT);

काष्ठा nf_acct *nfnl_acct_find_get(काष्ठा net *net, स्थिर अक्षर *acct_name)
अणु
	काष्ठा nfnl_acct_net *nfnl_acct_net = nfnl_acct_pernet(net);
	काष्ठा nf_acct *cur, *acct = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(cur, &nfnl_acct_net->nfnl_acct_list, head) अणु
		अगर (म_भेदन(cur->name, acct_name, NFACCT_NAME_MAX)!= 0)
			जारी;

		अगर (!try_module_get(THIS_MODULE))
			जाओ err;

		अगर (!refcount_inc_not_zero(&cur->refcnt)) अणु
			module_put(THIS_MODULE);
			जाओ err;
		पूर्ण

		acct = cur;
		अवरोध;
	पूर्ण
err:
	rcu_पढ़ो_unlock();
	वापस acct;
पूर्ण
EXPORT_SYMBOL_GPL(nfnl_acct_find_get);

व्योम nfnl_acct_put(काष्ठा nf_acct *acct)
अणु
	अगर (refcount_dec_and_test(&acct->refcnt))
		kमुक्त_rcu(acct, rcu_head);

	module_put(THIS_MODULE);
पूर्ण
EXPORT_SYMBOL_GPL(nfnl_acct_put);

व्योम nfnl_acct_update(स्थिर काष्ठा sk_buff *skb, काष्ठा nf_acct *nfacct)
अणु
	atomic64_inc(&nfacct->pkts);
	atomic64_add(skb->len, &nfacct->bytes);
पूर्ण
EXPORT_SYMBOL_GPL(nfnl_acct_update);

अटल व्योम nfnl_overquota_report(काष्ठा net *net, काष्ठा nf_acct *nfacct)
अणु
	पूर्णांक ret;
	काष्ठा sk_buff *skb;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस;

	ret = nfnl_acct_fill_info(skb, 0, 0, NFNL_MSG_ACCT_OVERQUOTA, 0,
				  nfacct);
	अगर (ret <= 0) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	nfnetlink_broadcast(net, skb, 0, NFNLGRP_ACCT_QUOTA, GFP_ATOMIC);
पूर्ण

पूर्णांक nfnl_acct_overquota(काष्ठा net *net, काष्ठा nf_acct *nfacct)
अणु
	u64 now;
	u64 *quota;
	पूर्णांक ret = NFACCT_UNDERQUOTA;

	/* no place here अगर we करोn't have a quota */
	अगर (!(nfacct->flags & NFACCT_F_QUOTA))
		वापस NFACCT_NO_QUOTA;

	quota = (u64 *)nfacct->data;
	now = (nfacct->flags & NFACCT_F_QUOTA_PKTS) ?
	       atomic64_पढ़ो(&nfacct->pkts) : atomic64_पढ़ो(&nfacct->bytes);

	ret = now > *quota;

	अगर (now >= *quota &&
	    !test_and_set_bit(NFACCT_OVERQUOTA_BIT, &nfacct->flags)) अणु
		nfnl_overquota_report(net, nfacct);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nfnl_acct_overquota);

अटल पूर्णांक __net_init nfnl_acct_net_init(काष्ठा net *net)
अणु
	INIT_LIST_HEAD(&nfnl_acct_pernet(net)->nfnl_acct_list);

	वापस 0;
पूर्ण

अटल व्योम __net_निकास nfnl_acct_net_निकास(काष्ठा net *net)
अणु
	काष्ठा nfnl_acct_net *nfnl_acct_net = nfnl_acct_pernet(net);
	काष्ठा nf_acct *cur, *पंचांगp;

	list_क्रम_each_entry_safe(cur, पंचांगp, &nfnl_acct_net->nfnl_acct_list, head) अणु
		list_del_rcu(&cur->head);

		अगर (refcount_dec_and_test(&cur->refcnt))
			kमुक्त_rcu(cur, rcu_head);
	पूर्ण
पूर्ण

अटल काष्ठा pernet_operations nfnl_acct_ops = अणु
        .init   = nfnl_acct_net_init,
        .निकास   = nfnl_acct_net_निकास,
        .id     = &nfnl_acct_net_id,
        .size   = माप(काष्ठा nfnl_acct_net),
पूर्ण;

अटल पूर्णांक __init nfnl_acct_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&nfnl_acct_ops);
	अगर (ret < 0) अणु
		pr_err("nfnl_acct_init: failed to register pernet ops\n");
		जाओ err_out;
	पूर्ण

	ret = nfnetlink_subsys_रेजिस्टर(&nfnl_acct_subsys);
	अगर (ret < 0) अणु
		pr_err("nfnl_acct_init: cannot register with nfnetlink.\n");
		जाओ cleanup_pernet;
	पूर्ण
	वापस 0;

cleanup_pernet:
	unरेजिस्टर_pernet_subsys(&nfnl_acct_ops);
err_out:
	वापस ret;
पूर्ण

अटल व्योम __निकास nfnl_acct_निकास(व्योम)
अणु
	nfnetlink_subsys_unरेजिस्टर(&nfnl_acct_subsys);
	unरेजिस्टर_pernet_subsys(&nfnl_acct_ops);
पूर्ण

module_init(nfnl_acct_init);
module_निकास(nfnl_acct_निकास);
