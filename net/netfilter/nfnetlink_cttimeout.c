<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) 2012 by Pablo Neira Ayuso <pablo@netfilter.org>
 * (C) 2012 by Vyatta Inc. <http://www.vyatta.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rculist_nulls.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/security.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netlink.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#समावेश <linux/netfilter.h>
#समावेश <net/netlink.h>
#समावेश <net/netns/generic.h>
#समावेश <net/sock.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_ctसमयout.h>

अटल अचिन्हित पूर्णांक nfct_समयout_id __पढ़ो_mostly;

काष्ठा nfct_समयout_pernet अणु
	काष्ठा list_head	nfct_समयout_list;
पूर्ण;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_DESCRIPTION("cttimeout: Extended Netfilter Connection Tracking timeout tuning");

अटल स्थिर काष्ठा nla_policy ctसमयout_nla_policy[CTA_TIMEOUT_MAX+1] = अणु
	[CTA_TIMEOUT_NAME]	= अणु .type = NLA_NUL_STRING,
				    .len  = CTNL_TIMEOUT_NAME_MAX - 1पूर्ण,
	[CTA_TIMEOUT_L3PROTO]	= अणु .type = NLA_U16 पूर्ण,
	[CTA_TIMEOUT_L4PROTO]	= अणु .type = NLA_U8 पूर्ण,
	[CTA_TIMEOUT_DATA]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल काष्ठा nfct_समयout_pernet *nfct_समयout_pernet(काष्ठा net *net)
अणु
	वापस net_generic(net, nfct_समयout_id);
पूर्ण

अटल पूर्णांक
ctnl_समयout_parse_policy(व्योम *समयout,
			  स्थिर काष्ठा nf_conntrack_l4proto *l4proto,
			  काष्ठा net *net, स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr **tb;
	पूर्णांक ret = 0;

	tb = kसुस्मृति(l4proto->ctnl_समयout.nlattr_max + 1, माप(*tb),
		     GFP_KERNEL);

	अगर (!tb)
		वापस -ENOMEM;

	ret = nla_parse_nested_deprecated(tb,
					  l4proto->ctnl_समयout.nlattr_max,
					  attr,
					  l4proto->ctnl_समयout.nla_policy,
					  शून्य);
	अगर (ret < 0)
		जाओ err;

	ret = l4proto->ctnl_समयout.nlattr_to_obj(tb, net, समयout);

err:
	kमुक्त(tb);
	वापस ret;
पूर्ण

अटल पूर्णांक ctसमयout_new_समयout(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nfnl_info *info,
				 स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nfct_समयout_pernet *pernet = nfct_समयout_pernet(info->net);
	__u16 l3num;
	__u8 l4num;
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	काष्ठा ctnl_समयout *समयout, *matching = शून्य;
	अक्षर *name;
	पूर्णांक ret;

	अगर (!cda[CTA_TIMEOUT_NAME] ||
	    !cda[CTA_TIMEOUT_L3PROTO] ||
	    !cda[CTA_TIMEOUT_L4PROTO] ||
	    !cda[CTA_TIMEOUT_DATA])
		वापस -EINVAL;

	name = nla_data(cda[CTA_TIMEOUT_NAME]);
	l3num = ntohs(nla_get_be16(cda[CTA_TIMEOUT_L3PROTO]));
	l4num = nla_get_u8(cda[CTA_TIMEOUT_L4PROTO]);

	list_क्रम_each_entry(समयout, &pernet->nfct_समयout_list, head) अणु
		अगर (म_भेदन(समयout->name, name, CTNL_TIMEOUT_NAME_MAX) != 0)
			जारी;

		अगर (info->nlh->nlmsg_flags & NLM_F_EXCL)
			वापस -EEXIST;

		matching = समयout;
		अवरोध;
	पूर्ण

	अगर (matching) अणु
		अगर (info->nlh->nlmsg_flags & NLM_F_REPLACE) अणु
			/* You cannot replace one समयout policy by another of
			 * dअगरferent kind, sorry.
			 */
			अगर (matching->समयout.l3num != l3num ||
			    matching->समयout.l4proto->l4proto != l4num)
				वापस -EINVAL;

			वापस ctnl_समयout_parse_policy(&matching->समयout.data,
							 matching->समयout.l4proto,
							 info->net,
							 cda[CTA_TIMEOUT_DATA]);
		पूर्ण

		वापस -EBUSY;
	पूर्ण

	l4proto = nf_ct_l4proto_find(l4num);

	/* This protocol is not supportted, skip. */
	अगर (l4proto->l4proto != l4num) अणु
		ret = -EOPNOTSUPP;
		जाओ err_proto_put;
	पूर्ण

	समयout = kzalloc(माप(काष्ठा ctnl_समयout) +
			  l4proto->ctnl_समयout.obj_size, GFP_KERNEL);
	अगर (समयout == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_proto_put;
	पूर्ण

	ret = ctnl_समयout_parse_policy(&समयout->समयout.data, l4proto,
					info->net, cda[CTA_TIMEOUT_DATA]);
	अगर (ret < 0)
		जाओ err;

	म_नकल(समयout->name, nla_data(cda[CTA_TIMEOUT_NAME]));
	समयout->समयout.l3num = l3num;
	समयout->समयout.l4proto = l4proto;
	refcount_set(&समयout->refcnt, 1);
	list_add_tail_rcu(&समयout->head, &pernet->nfct_समयout_list);

	वापस 0;
err:
	kमुक्त(समयout);
err_proto_put:
	वापस ret;
पूर्ण

अटल पूर्णांक
ctnl_समयout_fill_info(काष्ठा sk_buff *skb, u32 portid, u32 seq, u32 type,
		       पूर्णांक event, काष्ठा ctnl_समयout *समयout)
अणु
	काष्ठा nlmsghdr *nlh;
	अचिन्हित पूर्णांक flags = portid ? NLM_F_MULTI : 0;
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto = समयout->समयout.l4proto;
	काष्ठा nlattr *nest_parms;
	पूर्णांक ret;

	event = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK_TIMEOUT, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, AF_UNSPEC,
			   NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nlmsg_failure;

	अगर (nla_put_string(skb, CTA_TIMEOUT_NAME, समयout->name) ||
	    nla_put_be16(skb, CTA_TIMEOUT_L3PROTO,
			 htons(समयout->समयout.l3num)) ||
	    nla_put_u8(skb, CTA_TIMEOUT_L4PROTO, l4proto->l4proto) ||
	    nla_put_be32(skb, CTA_TIMEOUT_USE,
			 htonl(refcount_पढ़ो(&समयout->refcnt))))
		जाओ nla_put_failure;

	nest_parms = nla_nest_start(skb, CTA_TIMEOUT_DATA);
	अगर (!nest_parms)
		जाओ nla_put_failure;

	ret = l4proto->ctnl_समयout.obj_to_nlattr(skb, &समयout->समयout.data);
	अगर (ret < 0)
		जाओ nla_put_failure;

	nla_nest_end(skb, nest_parms);

	nlmsg_end(skb, nlh);
	वापस skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -1;
पूर्ण

अटल पूर्णांक
ctnl_समयout_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nfct_समयout_pernet *pernet;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा ctnl_समयout *cur, *last;

	अगर (cb->args[2])
		वापस 0;

	last = (काष्ठा ctnl_समयout *)cb->args[1];
	अगर (cb->args[1])
		cb->args[1] = 0;

	rcu_पढ़ो_lock();
	pernet = nfct_समयout_pernet(net);
	list_क्रम_each_entry_rcu(cur, &pernet->nfct_समयout_list, head) अणु
		अगर (last) अणु
			अगर (cur != last)
				जारी;

			last = शून्य;
		पूर्ण
		अगर (ctnl_समयout_fill_info(skb, NETLINK_CB(cb->skb).portid,
					   cb->nlh->nlmsg_seq,
					   NFNL_MSG_TYPE(cb->nlh->nlmsg_type),
					   IPCTNL_MSG_TIMEOUT_NEW, cur) < 0) अणु
			cb->args[1] = (अचिन्हित दीर्घ)cur;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!cb->args[1])
		cb->args[2] = 1;
	rcu_पढ़ो_unlock();
	वापस skb->len;
पूर्ण

अटल पूर्णांक ctसमयout_get_समयout(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nfnl_info *info,
				 स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nfct_समयout_pernet *pernet = nfct_समयout_pernet(info->net);
	पूर्णांक ret = -ENOENT;
	अक्षर *name;
	काष्ठा ctnl_समयout *cur;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = ctnl_समयout_dump,
		पूर्ण;
		वापस netlink_dump_start(info->sk, skb, info->nlh, &c);
	पूर्ण

	अगर (!cda[CTA_TIMEOUT_NAME])
		वापस -EINVAL;
	name = nla_data(cda[CTA_TIMEOUT_NAME]);

	list_क्रम_each_entry(cur, &pernet->nfct_समयout_list, head) अणु
		काष्ठा sk_buff *skb2;

		अगर (म_भेदन(cur->name, name, CTNL_TIMEOUT_NAME_MAX) != 0)
			जारी;

		skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
		अगर (skb2 == शून्य) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		ret = ctnl_समयout_fill_info(skb2, NETLINK_CB(skb).portid,
					     info->nlh->nlmsg_seq,
					     NFNL_MSG_TYPE(info->nlh->nlmsg_type),
					     IPCTNL_MSG_TIMEOUT_NEW, cur);
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
अटल पूर्णांक ctnl_समयout_try_del(काष्ठा net *net, काष्ठा ctnl_समयout *समयout)
अणु
	पूर्णांक ret = 0;

	/* We want to aव्योम races with ctnl_समयout_put. So only when the
	 * current refcnt is 1, we decrease it to 0.
	 */
	अगर (refcount_dec_अगर_one(&समयout->refcnt)) अणु
		/* We are रक्षित by nfnl mutex. */
		list_del_rcu(&समयout->head);
		nf_ct_unसमयout(net, &समयout->समयout);
		kमुक्त_rcu(समयout, rcu_head);
	पूर्ण अन्यथा अणु
		ret = -EBUSY;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ctसमयout_del_समयout(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nfnl_info *info,
				 स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	काष्ठा nfct_समयout_pernet *pernet = nfct_समयout_pernet(info->net);
	काष्ठा ctnl_समयout *cur, *पंचांगp;
	पूर्णांक ret = -ENOENT;
	अक्षर *name;

	अगर (!cda[CTA_TIMEOUT_NAME]) अणु
		list_क्रम_each_entry_safe(cur, पंचांगp, &pernet->nfct_समयout_list,
					 head)
			ctnl_समयout_try_del(info->net, cur);

		वापस 0;
	पूर्ण
	name = nla_data(cda[CTA_TIMEOUT_NAME]);

	list_क्रम_each_entry(cur, &pernet->nfct_समयout_list, head) अणु
		अगर (म_भेदन(cur->name, name, CTNL_TIMEOUT_NAME_MAX) != 0)
			जारी;

		ret = ctnl_समयout_try_del(info->net, cur);
		अगर (ret < 0)
			वापस ret;

		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ctसमयout_शेष_set(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nfnl_info *info,
				 स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	__u8 l4num;
	पूर्णांक ret;

	अगर (!cda[CTA_TIMEOUT_L3PROTO] ||
	    !cda[CTA_TIMEOUT_L4PROTO] ||
	    !cda[CTA_TIMEOUT_DATA])
		वापस -EINVAL;

	l4num = nla_get_u8(cda[CTA_TIMEOUT_L4PROTO]);
	l4proto = nf_ct_l4proto_find(l4num);

	/* This protocol is not supported, skip. */
	अगर (l4proto->l4proto != l4num) अणु
		ret = -EOPNOTSUPP;
		जाओ err;
	पूर्ण

	ret = ctnl_समयout_parse_policy(शून्य, l4proto, info->net,
					cda[CTA_TIMEOUT_DATA]);
	अगर (ret < 0)
		जाओ err;

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक
ctसमयout_शेष_fill_info(काष्ठा net *net, काष्ठा sk_buff *skb, u32 portid,
			    u32 seq, u32 type, पूर्णांक event, u16 l3num,
			    स्थिर काष्ठा nf_conntrack_l4proto *l4proto,
			    स्थिर अचिन्हित पूर्णांक *समयouts)
अणु
	काष्ठा nlmsghdr *nlh;
	अचिन्हित पूर्णांक flags = portid ? NLM_F_MULTI : 0;
	काष्ठा nlattr *nest_parms;
	पूर्णांक ret;

	event = nfnl_msg_type(NFNL_SUBSYS_CTNETLINK_TIMEOUT, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, AF_UNSPEC,
			   NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nlmsg_failure;

	अगर (nla_put_be16(skb, CTA_TIMEOUT_L3PROTO, htons(l3num)) ||
	    nla_put_u8(skb, CTA_TIMEOUT_L4PROTO, l4proto->l4proto))
		जाओ nla_put_failure;

	nest_parms = nla_nest_start(skb, CTA_TIMEOUT_DATA);
	अगर (!nest_parms)
		जाओ nla_put_failure;

	ret = l4proto->ctnl_समयout.obj_to_nlattr(skb, समयouts);
	अगर (ret < 0)
		जाओ nla_put_failure;

	nla_nest_end(skb, nest_parms);

	nlmsg_end(skb, nlh);
	वापस skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -1;
पूर्ण

अटल पूर्णांक ctसमयout_शेष_get(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nfnl_info *info,
				 स्थिर काष्ठा nlattr * स्थिर cda[])
अणु
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	अचिन्हित पूर्णांक *समयouts = शून्य;
	काष्ठा sk_buff *skb2;
	पूर्णांक ret, err;
	__u16 l3num;
	__u8 l4num;

	अगर (!cda[CTA_TIMEOUT_L3PROTO] || !cda[CTA_TIMEOUT_L4PROTO])
		वापस -EINVAL;

	l3num = ntohs(nla_get_be16(cda[CTA_TIMEOUT_L3PROTO]));
	l4num = nla_get_u8(cda[CTA_TIMEOUT_L4PROTO]);
	l4proto = nf_ct_l4proto_find(l4num);

	err = -EOPNOTSUPP;
	अगर (l4proto->l4proto != l4num)
		जाओ err;

	चयन (l4proto->l4proto) अणु
	हाल IPPROTO_ICMP:
		समयouts = &nf_icmp_pernet(info->net)->समयout;
		अवरोध;
	हाल IPPROTO_TCP:
		समयouts = nf_tcp_pernet(info->net)->समयouts;
		अवरोध;
	हाल IPPROTO_UDP:
	हाल IPPROTO_UDPLITE:
		समयouts = nf_udp_pernet(info->net)->समयouts;
		अवरोध;
	हाल IPPROTO_DCCP:
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
		समयouts = nf_dccp_pernet(info->net)->dccp_समयout;
#पूर्ण_अगर
		अवरोध;
	हाल IPPROTO_ICMPV6:
		समयouts = &nf_icmpv6_pernet(info->net)->समयout;
		अवरोध;
	हाल IPPROTO_SCTP:
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
		समयouts = nf_sctp_pernet(info->net)->समयouts;
#पूर्ण_अगर
		अवरोध;
	हाल IPPROTO_GRE:
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
		समयouts = nf_gre_pernet(info->net)->समयouts;
#पूर्ण_अगर
		अवरोध;
	हाल 255:
		समयouts = &nf_generic_pernet(info->net)->समयout;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Missing timeouts for proto %d", l4proto->l4proto);
		अवरोध;
	पूर्ण

	अगर (!समयouts)
		जाओ err;

	skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (skb2 == शून्य) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	ret = ctसमयout_शेष_fill_info(info->net, skb2,
					  NETLINK_CB(skb).portid,
					  info->nlh->nlmsg_seq,
					  NFNL_MSG_TYPE(info->nlh->nlmsg_type),
					  IPCTNL_MSG_TIMEOUT_DEFAULT_SET,
					  l3num, l4proto, समयouts);
	अगर (ret <= 0) अणु
		kमुक्त_skb(skb2);
		err = -ENOMEM;
		जाओ err;
	पूर्ण
	ret = netlink_unicast(info->sk, skb2, NETLINK_CB(skb).portid,
			      MSG_DONTWAIT);
	अगर (ret > 0)
		ret = 0;

	/* this aव्योमs a loop in nfnetlink. */
	वापस ret == -EAGAIN ? -ENOBUFS : ret;
err:
	वापस err;
पूर्ण

अटल काष्ठा nf_ct_समयout *ctnl_समयout_find_get(काष्ठा net *net,
						   स्थिर अक्षर *name)
अणु
	काष्ठा nfct_समयout_pernet *pernet = nfct_समयout_pernet(net);
	काष्ठा ctnl_समयout *समयout, *matching = शून्य;

	list_क्रम_each_entry_rcu(समयout, &pernet->nfct_समयout_list, head) अणु
		अगर (म_भेदन(समयout->name, name, CTNL_TIMEOUT_NAME_MAX) != 0)
			जारी;

		अगर (!try_module_get(THIS_MODULE))
			जाओ err;

		अगर (!refcount_inc_not_zero(&समयout->refcnt)) अणु
			module_put(THIS_MODULE);
			जाओ err;
		पूर्ण
		matching = समयout;
		अवरोध;
	पूर्ण
err:
	वापस matching ? &matching->समयout : शून्य;
पूर्ण

अटल व्योम ctnl_समयout_put(काष्ठा nf_ct_समयout *t)
अणु
	काष्ठा ctnl_समयout *समयout =
		container_of(t, काष्ठा ctnl_समयout, समयout);

	अगर (refcount_dec_and_test(&समयout->refcnt))
		kमुक्त_rcu(समयout, rcu_head);

	module_put(THIS_MODULE);
पूर्ण

अटल स्थिर काष्ठा nfnl_callback ctसमयout_cb[IPCTNL_MSG_TIMEOUT_MAX] = अणु
	[IPCTNL_MSG_TIMEOUT_NEW] = अणु
		.call		= ctसमयout_new_समयout,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_TIMEOUT_MAX,
		.policy		= ctसमयout_nla_policy
	पूर्ण,
	[IPCTNL_MSG_TIMEOUT_GET] = अणु
		.call		= ctसमयout_get_समयout,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_TIMEOUT_MAX,
		.policy		= ctसमयout_nla_policy
	पूर्ण,
	[IPCTNL_MSG_TIMEOUT_DELETE] = अणु
		.call		= ctसमयout_del_समयout,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_TIMEOUT_MAX,
		.policy		= ctसमयout_nla_policy
	पूर्ण,
	[IPCTNL_MSG_TIMEOUT_DEFAULT_SET] = अणु
		.call		= ctसमयout_शेष_set,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_TIMEOUT_MAX,
		.policy		= ctसमयout_nla_policy
	पूर्ण,
	[IPCTNL_MSG_TIMEOUT_DEFAULT_GET] = अणु
		.call		= ctसमयout_शेष_get,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= CTA_TIMEOUT_MAX,
		.policy		= ctसमयout_nla_policy
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnetlink_subप्रणाली ctसमयout_subsys = अणु
	.name				= "conntrack_timeout",
	.subsys_id			= NFNL_SUBSYS_CTNETLINK_TIMEOUT,
	.cb_count			= IPCTNL_MSG_TIMEOUT_MAX,
	.cb				= ctसमयout_cb,
पूर्ण;

MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_CTNETLINK_TIMEOUT);

अटल पूर्णांक __net_init ctसमयout_net_init(काष्ठा net *net)
अणु
	काष्ठा nfct_समयout_pernet *pernet = nfct_समयout_pernet(net);

	INIT_LIST_HEAD(&pernet->nfct_समयout_list);

	वापस 0;
पूर्ण

अटल व्योम __net_निकास ctसमयout_net_निकास(काष्ठा net *net)
अणु
	काष्ठा nfct_समयout_pernet *pernet = nfct_समयout_pernet(net);
	काष्ठा ctnl_समयout *cur, *पंचांगp;

	nf_ct_unconfirmed_destroy(net);
	nf_ct_unसमयout(net, शून्य);

	list_क्रम_each_entry_safe(cur, पंचांगp, &pernet->nfct_समयout_list, head) अणु
		list_del_rcu(&cur->head);

		अगर (refcount_dec_and_test(&cur->refcnt))
			kमुक्त_rcu(cur, rcu_head);
	पूर्ण
पूर्ण

अटल काष्ठा pernet_operations ctसमयout_ops = अणु
	.init	= ctसमयout_net_init,
	.निकास	= ctसमयout_net_निकास,
	.id     = &nfct_समयout_id,
	.size   = माप(काष्ठा nfct_समयout_pernet),
पूर्ण;

अटल पूर्णांक __init ctसमयout_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&ctसमयout_ops);
	अगर (ret < 0)
		वापस ret;

	ret = nfnetlink_subsys_रेजिस्टर(&ctसमयout_subsys);
	अगर (ret < 0) अणु
		pr_err("cttimeout_init: cannot register cttimeout with "
			"nfnetlink.\n");
		जाओ err_out;
	पूर्ण
	RCU_INIT_POINTER(nf_ct_समयout_find_get_hook, ctnl_समयout_find_get);
	RCU_INIT_POINTER(nf_ct_समयout_put_hook, ctnl_समयout_put);
	वापस 0;

err_out:
	unरेजिस्टर_pernet_subsys(&ctसमयout_ops);
	वापस ret;
पूर्ण

अटल व्योम __निकास ctसमयout_निकास(व्योम)
अणु
	nfnetlink_subsys_unरेजिस्टर(&ctसमयout_subsys);

	unरेजिस्टर_pernet_subsys(&ctसमयout_ops);
	RCU_INIT_POINTER(nf_ct_समयout_find_get_hook, शून्य);
	RCU_INIT_POINTER(nf_ct_समयout_put_hook, शून्य);
	synchronize_rcu();
पूर्ण

module_init(ctसमयout_init);
module_निकास(ctसमयout_निकास);
