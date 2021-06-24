<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) 2012 Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * This software has been sponsored by Vyatta Inc. <http://www.vyatta.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rculist.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/capability.h>
#समावेश <net/netlink.h>
#समावेश <net/sock.h>

#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_conntrack.h>
#समावेश <linux/netfilter/nfnetlink_cthelper.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_DESCRIPTION("nfnl_cthelper: User-space connection tracking helpers");

काष्ठा nfnl_cthelper अणु
	काष्ठा list_head		list;
	काष्ठा nf_conntrack_helper	helper;
पूर्ण;

अटल LIST_HEAD(nfnl_cthelper_list);

अटल पूर्णांक
nfnl_userspace_cthelper(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo)
अणु
	स्थिर काष्ठा nf_conn_help *help;
	काष्ठा nf_conntrack_helper *helper;

	help = nfct_help(ct);
	अगर (help == शून्य)
		वापस NF_DROP;

	/* rcu_पढ़ो_lock()ed by nf_hook_thresh */
	helper = rcu_dereference(help->helper);
	अगर (helper == शून्य)
		वापस NF_DROP;

	/* This is a user-space helper not yet configured, skip. */
	अगर ((helper->flags &
	    (NF_CT_HELPER_F_USERSPACE | NF_CT_HELPER_F_CONFIGURED)) ==
	     NF_CT_HELPER_F_USERSPACE)
		वापस NF_ACCEPT;

	/* If the user-space helper is not available, करोn't block traffic. */
	वापस NF_QUEUE_NR(helper->queue_num) | NF_VERDICT_FLAG_QUEUE_BYPASS;
पूर्ण

अटल स्थिर काष्ठा nla_policy nfnl_cthelper_tuple_pol[NFCTH_TUPLE_MAX+1] = अणु
	[NFCTH_TUPLE_L3PROTONUM] = अणु .type = NLA_U16, पूर्ण,
	[NFCTH_TUPLE_L4PROTONUM] = अणु .type = NLA_U8, पूर्ण,
पूर्ण;

अटल पूर्णांक
nfnl_cthelper_parse_tuple(काष्ठा nf_conntrack_tuple *tuple,
			  स्थिर काष्ठा nlattr *attr)
अणु
	पूर्णांक err;
	काष्ठा nlattr *tb[NFCTH_TUPLE_MAX+1];

	err = nla_parse_nested_deprecated(tb, NFCTH_TUPLE_MAX, attr,
					  nfnl_cthelper_tuple_pol, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFCTH_TUPLE_L3PROTONUM] || !tb[NFCTH_TUPLE_L4PROTONUM])
		वापस -EINVAL;

	/* Not all fields are initialized so first zero the tuple */
	स_रखो(tuple, 0, माप(काष्ठा nf_conntrack_tuple));

	tuple->src.l3num = ntohs(nla_get_be16(tb[NFCTH_TUPLE_L3PROTONUM]));
	tuple->dst.protonum = nla_get_u8(tb[NFCTH_TUPLE_L4PROTONUM]);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfnl_cthelper_from_nlattr(काष्ठा nlattr *attr, काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_help *help = nfct_help(ct);

	अगर (attr == शून्य)
		वापस -EINVAL;

	अगर (help->helper->data_len == 0)
		वापस -EINVAL;

	nla_स_नकल(help->data, attr, माप(help->data));
	वापस 0;
पूर्ण

अटल पूर्णांक
nfnl_cthelper_to_nlattr(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct)
अणु
	स्थिर काष्ठा nf_conn_help *help = nfct_help(ct);

	अगर (help->helper->data_len &&
	    nla_put(skb, CTA_HELP_INFO, help->helper->data_len, &help->data))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -ENOSPC;
पूर्ण

अटल स्थिर काष्ठा nla_policy nfnl_cthelper_expect_pol[NFCTH_POLICY_MAX+1] = अणु
	[NFCTH_POLICY_NAME] = अणु .type = NLA_NUL_STRING,
				.len = NF_CT_HELPER_NAME_LEN-1 पूर्ण,
	[NFCTH_POLICY_EXPECT_MAX] = अणु .type = NLA_U32, पूर्ण,
	[NFCTH_POLICY_EXPECT_TIMEOUT] = अणु .type = NLA_U32, पूर्ण,
पूर्ण;

अटल पूर्णांक
nfnl_cthelper_expect_policy(काष्ठा nf_conntrack_expect_policy *expect_policy,
			    स्थिर काष्ठा nlattr *attr)
अणु
	पूर्णांक err;
	काष्ठा nlattr *tb[NFCTH_POLICY_MAX+1];

	err = nla_parse_nested_deprecated(tb, NFCTH_POLICY_MAX, attr,
					  nfnl_cthelper_expect_pol, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFCTH_POLICY_NAME] ||
	    !tb[NFCTH_POLICY_EXPECT_MAX] ||
	    !tb[NFCTH_POLICY_EXPECT_TIMEOUT])
		वापस -EINVAL;

	nla_strscpy(expect_policy->name,
		    tb[NFCTH_POLICY_NAME], NF_CT_HELPER_NAME_LEN);
	expect_policy->max_expected =
		ntohl(nla_get_be32(tb[NFCTH_POLICY_EXPECT_MAX]));
	अगर (expect_policy->max_expected > NF_CT_EXPECT_MAX_CNT)
		वापस -EINVAL;

	expect_policy->समयout =
		ntohl(nla_get_be32(tb[NFCTH_POLICY_EXPECT_TIMEOUT]));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy
nfnl_cthelper_expect_policy_set[NFCTH_POLICY_SET_MAX+1] = अणु
	[NFCTH_POLICY_SET_NUM] = अणु .type = NLA_U32, पूर्ण,
पूर्ण;

अटल पूर्णांक
nfnl_cthelper_parse_expect_policy(काष्ठा nf_conntrack_helper *helper,
				  स्थिर काष्ठा nlattr *attr)
अणु
	पूर्णांक i, ret;
	काष्ठा nf_conntrack_expect_policy *expect_policy;
	काष्ठा nlattr *tb[NFCTH_POLICY_SET_MAX+1];
	अचिन्हित पूर्णांक class_max;

	ret = nla_parse_nested_deprecated(tb, NFCTH_POLICY_SET_MAX, attr,
					  nfnl_cthelper_expect_policy_set,
					  शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (!tb[NFCTH_POLICY_SET_NUM])
		वापस -EINVAL;

	class_max = ntohl(nla_get_be32(tb[NFCTH_POLICY_SET_NUM]));
	अगर (class_max == 0)
		वापस -EINVAL;
	अगर (class_max > NF_CT_MAX_EXPECT_CLASSES)
		वापस -EOVERFLOW;

	expect_policy = kसुस्मृति(class_max,
				माप(काष्ठा nf_conntrack_expect_policy),
				GFP_KERNEL);
	अगर (expect_policy == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < class_max; i++) अणु
		अगर (!tb[NFCTH_POLICY_SET+i])
			जाओ err;

		ret = nfnl_cthelper_expect_policy(&expect_policy[i],
						  tb[NFCTH_POLICY_SET+i]);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	helper->expect_class_max = class_max - 1;
	helper->expect_policy = expect_policy;
	वापस 0;
err:
	kमुक्त(expect_policy);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nfnl_cthelper_create(स्थिर काष्ठा nlattr * स्थिर tb[],
		     काष्ठा nf_conntrack_tuple *tuple)
अणु
	काष्ठा nf_conntrack_helper *helper;
	काष्ठा nfnl_cthelper *nfcth;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	अगर (!tb[NFCTH_TUPLE] || !tb[NFCTH_POLICY] || !tb[NFCTH_PRIV_DATA_LEN])
		वापस -EINVAL;

	nfcth = kzalloc(माप(*nfcth), GFP_KERNEL);
	अगर (nfcth == शून्य)
		वापस -ENOMEM;
	helper = &nfcth->helper;

	ret = nfnl_cthelper_parse_expect_policy(helper, tb[NFCTH_POLICY]);
	अगर (ret < 0)
		जाओ err1;

	nla_strscpy(helper->name,
		    tb[NFCTH_NAME], NF_CT_HELPER_NAME_LEN);
	size = ntohl(nla_get_be32(tb[NFCTH_PRIV_DATA_LEN]));
	अगर (size > माप_field(काष्ठा nf_conn_help, data)) अणु
		ret = -ENOMEM;
		जाओ err2;
	पूर्ण
	helper->data_len = size;

	helper->flags |= NF_CT_HELPER_F_USERSPACE;
	स_नकल(&helper->tuple, tuple, माप(काष्ठा nf_conntrack_tuple));

	helper->me = THIS_MODULE;
	helper->help = nfnl_userspace_cthelper;
	helper->from_nlattr = nfnl_cthelper_from_nlattr;
	helper->to_nlattr = nfnl_cthelper_to_nlattr;

	/* Default to queue number zero, this can be updated at any समय. */
	अगर (tb[NFCTH_QUEUE_NUM])
		helper->queue_num = ntohl(nla_get_be32(tb[NFCTH_QUEUE_NUM]));

	अगर (tb[NFCTH_STATUS]) अणु
		पूर्णांक status = ntohl(nla_get_be32(tb[NFCTH_STATUS]));

		चयन(status) अणु
		हाल NFCT_HELPER_STATUS_ENABLED:
			helper->flags |= NF_CT_HELPER_F_CONFIGURED;
			अवरोध;
		हाल NFCT_HELPER_STATUS_DISABLED:
			helper->flags &= ~NF_CT_HELPER_F_CONFIGURED;
			अवरोध;
		पूर्ण
	पूर्ण

	ret = nf_conntrack_helper_रेजिस्टर(helper);
	अगर (ret < 0)
		जाओ err2;

	list_add_tail(&nfcth->list, &nfnl_cthelper_list);
	वापस 0;
err2:
	kमुक्त(helper->expect_policy);
err1:
	kमुक्त(nfcth);
	वापस ret;
पूर्ण

अटल पूर्णांक
nfnl_cthelper_update_policy_one(स्थिर काष्ठा nf_conntrack_expect_policy *policy,
				काष्ठा nf_conntrack_expect_policy *new_policy,
				स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr *tb[NFCTH_POLICY_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFCTH_POLICY_MAX, attr,
					  nfnl_cthelper_expect_pol, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFCTH_POLICY_NAME] ||
	    !tb[NFCTH_POLICY_EXPECT_MAX] ||
	    !tb[NFCTH_POLICY_EXPECT_TIMEOUT])
		वापस -EINVAL;

	अगर (nla_म_भेद(tb[NFCTH_POLICY_NAME], policy->name))
		वापस -EBUSY;

	new_policy->max_expected =
		ntohl(nla_get_be32(tb[NFCTH_POLICY_EXPECT_MAX]));
	अगर (new_policy->max_expected > NF_CT_EXPECT_MAX_CNT)
		वापस -EINVAL;

	new_policy->समयout =
		ntohl(nla_get_be32(tb[NFCTH_POLICY_EXPECT_TIMEOUT]));

	वापस 0;
पूर्ण

अटल पूर्णांक nfnl_cthelper_update_policy_all(काष्ठा nlattr *tb[],
					   काष्ठा nf_conntrack_helper *helper)
अणु
	काष्ठा nf_conntrack_expect_policy *new_policy;
	काष्ठा nf_conntrack_expect_policy *policy;
	पूर्णांक i, ret = 0;

	new_policy = kदो_स्मृति_array(helper->expect_class_max + 1,
				   माप(*new_policy), GFP_KERNEL);
	अगर (!new_policy)
		वापस -ENOMEM;

	/* Check first that all policy attributes are well-क्रमmed, so we करोn't
	 * leave things in inconsistent state on errors.
	 */
	क्रम (i = 0; i < helper->expect_class_max + 1; i++) अणु

		अगर (!tb[NFCTH_POLICY_SET + i]) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		ret = nfnl_cthelper_update_policy_one(&helper->expect_policy[i],
						      &new_policy[i],
						      tb[NFCTH_POLICY_SET + i]);
		अगर (ret < 0)
			जाओ err;
	पूर्ण
	/* Now we can safely update them. */
	क्रम (i = 0; i < helper->expect_class_max + 1; i++) अणु
		policy = (काष्ठा nf_conntrack_expect_policy *)
				&helper->expect_policy[i];
		policy->max_expected = new_policy->max_expected;
		policy->समयout	= new_policy->समयout;
	पूर्ण

err:
	kमुक्त(new_policy);
	वापस ret;
पूर्ण

अटल पूर्णांक nfnl_cthelper_update_policy(काष्ठा nf_conntrack_helper *helper,
				       स्थिर काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr *tb[NFCTH_POLICY_SET_MAX + 1];
	अचिन्हित पूर्णांक class_max;
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFCTH_POLICY_SET_MAX, attr,
					  nfnl_cthelper_expect_policy_set,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFCTH_POLICY_SET_NUM])
		वापस -EINVAL;

	class_max = ntohl(nla_get_be32(tb[NFCTH_POLICY_SET_NUM]));
	अगर (helper->expect_class_max + 1 != class_max)
		वापस -EBUSY;

	वापस nfnl_cthelper_update_policy_all(tb, helper);
पूर्ण

अटल पूर्णांक
nfnl_cthelper_update(स्थिर काष्ठा nlattr * स्थिर tb[],
		     काष्ठा nf_conntrack_helper *helper)
अणु
	u32 size;
	पूर्णांक ret;

	अगर (tb[NFCTH_PRIV_DATA_LEN]) अणु
		size = ntohl(nla_get_be32(tb[NFCTH_PRIV_DATA_LEN]));
		अगर (size != helper->data_len)
			वापस -EBUSY;
	पूर्ण

	अगर (tb[NFCTH_POLICY]) अणु
		ret = nfnl_cthelper_update_policy(helper, tb[NFCTH_POLICY]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	अगर (tb[NFCTH_QUEUE_NUM])
		helper->queue_num = ntohl(nla_get_be32(tb[NFCTH_QUEUE_NUM]));

	अगर (tb[NFCTH_STATUS]) अणु
		पूर्णांक status = ntohl(nla_get_be32(tb[NFCTH_STATUS]));

		चयन(status) अणु
		हाल NFCT_HELPER_STATUS_ENABLED:
			helper->flags |= NF_CT_HELPER_F_CONFIGURED;
			अवरोध;
		हाल NFCT_HELPER_STATUS_DISABLED:
			helper->flags &= ~NF_CT_HELPER_F_CONFIGURED;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nfnl_cthelper_new(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	स्थिर अक्षर *helper_name;
	काष्ठा nf_conntrack_helper *cur, *helper = शून्य;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nfnl_cthelper *nlcth;
	पूर्णांक ret = 0;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!tb[NFCTH_NAME] || !tb[NFCTH_TUPLE])
		वापस -EINVAL;

	helper_name = nla_data(tb[NFCTH_NAME]);

	ret = nfnl_cthelper_parse_tuple(&tuple, tb[NFCTH_TUPLE]);
	अगर (ret < 0)
		वापस ret;

	list_क्रम_each_entry(nlcth, &nfnl_cthelper_list, list) अणु
		cur = &nlcth->helper;

		अगर (म_भेदन(cur->name, helper_name, NF_CT_HELPER_NAME_LEN))
			जारी;

		अगर ((tuple.src.l3num != cur->tuple.src.l3num ||
		     tuple.dst.protonum != cur->tuple.dst.protonum))
			जारी;

		अगर (info->nlh->nlmsg_flags & NLM_F_EXCL)
			वापस -EEXIST;

		helper = cur;
		अवरोध;
	पूर्ण

	अगर (helper == शून्य)
		ret = nfnl_cthelper_create(tb, &tuple);
	अन्यथा
		ret = nfnl_cthelper_update(tb, helper);

	वापस ret;
पूर्ण

अटल पूर्णांक
nfnl_cthelper_dump_tuple(काष्ठा sk_buff *skb,
			 काष्ठा nf_conntrack_helper *helper)
अणु
	काष्ठा nlattr *nest_parms;

	nest_parms = nla_nest_start(skb, NFCTH_TUPLE);
	अगर (nest_parms == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put_be16(skb, NFCTH_TUPLE_L3PROTONUM,
			 htons(helper->tuple.src.l3num)))
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, NFCTH_TUPLE_L4PROTONUM, helper->tuple.dst.protonum))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest_parms);
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक
nfnl_cthelper_dump_policy(काष्ठा sk_buff *skb,
			काष्ठा nf_conntrack_helper *helper)
अणु
	पूर्णांक i;
	काष्ठा nlattr *nest_parms1, *nest_parms2;

	nest_parms1 = nla_nest_start(skb, NFCTH_POLICY);
	अगर (nest_parms1 == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, NFCTH_POLICY_SET_NUM,
			 htonl(helper->expect_class_max + 1)))
		जाओ nla_put_failure;

	क्रम (i = 0; i < helper->expect_class_max + 1; i++) अणु
		nest_parms2 = nla_nest_start(skb, (NFCTH_POLICY_SET + i));
		अगर (nest_parms2 == शून्य)
			जाओ nla_put_failure;

		अगर (nla_put_string(skb, NFCTH_POLICY_NAME,
				   helper->expect_policy[i].name))
			जाओ nla_put_failure;

		अगर (nla_put_be32(skb, NFCTH_POLICY_EXPECT_MAX,
				 htonl(helper->expect_policy[i].max_expected)))
			जाओ nla_put_failure;

		अगर (nla_put_be32(skb, NFCTH_POLICY_EXPECT_TIMEOUT,
				 htonl(helper->expect_policy[i].समयout)))
			जाओ nla_put_failure;

		nla_nest_end(skb, nest_parms2);
	पूर्ण
	nla_nest_end(skb, nest_parms1);
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक
nfnl_cthelper_fill_info(काष्ठा sk_buff *skb, u32 portid, u32 seq, u32 type,
			पूर्णांक event, काष्ठा nf_conntrack_helper *helper)
अणु
	काष्ठा nlmsghdr *nlh;
	अचिन्हित पूर्णांक flags = portid ? NLM_F_MULTI : 0;
	पूर्णांक status;

	event = nfnl_msg_type(NFNL_SUBSYS_CTHELPER, event);
	nlh = nfnl_msg_put(skb, portid, seq, event, flags, AF_UNSPEC,
			   NFNETLINK_V0, 0);
	अगर (!nlh)
		जाओ nlmsg_failure;

	अगर (nla_put_string(skb, NFCTH_NAME, helper->name))
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, NFCTH_QUEUE_NUM, htonl(helper->queue_num)))
		जाओ nla_put_failure;

	अगर (nfnl_cthelper_dump_tuple(skb, helper) < 0)
		जाओ nla_put_failure;

	अगर (nfnl_cthelper_dump_policy(skb, helper) < 0)
		जाओ nla_put_failure;

	अगर (nla_put_be32(skb, NFCTH_PRIV_DATA_LEN, htonl(helper->data_len)))
		जाओ nla_put_failure;

	अगर (helper->flags & NF_CT_HELPER_F_CONFIGURED)
		status = NFCT_HELPER_STATUS_ENABLED;
	अन्यथा
		status = NFCT_HELPER_STATUS_DISABLED;

	अगर (nla_put_be32(skb, NFCTH_STATUS, htonl(status)))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस skb->len;

nlmsg_failure:
nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -1;
पूर्ण

अटल पूर्णांक
nfnl_cthelper_dump_table(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nf_conntrack_helper *cur, *last;

	rcu_पढ़ो_lock();
	last = (काष्ठा nf_conntrack_helper *)cb->args[1];
	क्रम (; cb->args[0] < nf_ct_helper_hsize; cb->args[0]++) अणु
restart:
		hlist_क्रम_each_entry_rcu(cur,
				&nf_ct_helper_hash[cb->args[0]], hnode) अणु

			/* skip non-userspace conntrack helpers. */
			अगर (!(cur->flags & NF_CT_HELPER_F_USERSPACE))
				जारी;

			अगर (cb->args[1]) अणु
				अगर (cur != last)
					जारी;
				cb->args[1] = 0;
			पूर्ण
			अगर (nfnl_cthelper_fill_info(skb,
					    NETLINK_CB(cb->skb).portid,
					    cb->nlh->nlmsg_seq,
					    NFNL_MSG_TYPE(cb->nlh->nlmsg_type),
					    NFNL_MSG_CTHELPER_NEW, cur) < 0) अणु
				cb->args[1] = (अचिन्हित दीर्घ)cur;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (cb->args[1]) अणु
		cb->args[1] = 0;
		जाओ restart;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस skb->len;
पूर्ण

अटल पूर्णांक nfnl_cthelper_get(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	पूर्णांक ret = -ENOENT;
	काष्ठा nf_conntrack_helper *cur;
	काष्ठा sk_buff *skb2;
	अक्षर *helper_name = शून्य;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nfnl_cthelper *nlcth;
	bool tuple_set = false;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (info->nlh->nlmsg_flags & NLM_F_DUMP) अणु
		काष्ठा netlink_dump_control c = अणु
			.dump = nfnl_cthelper_dump_table,
		पूर्ण;
		वापस netlink_dump_start(info->sk, skb, info->nlh, &c);
	पूर्ण

	अगर (tb[NFCTH_NAME])
		helper_name = nla_data(tb[NFCTH_NAME]);

	अगर (tb[NFCTH_TUPLE]) अणु
		ret = nfnl_cthelper_parse_tuple(&tuple, tb[NFCTH_TUPLE]);
		अगर (ret < 0)
			वापस ret;

		tuple_set = true;
	पूर्ण

	list_क्रम_each_entry(nlcth, &nfnl_cthelper_list, list) अणु
		cur = &nlcth->helper;
		अगर (helper_name &&
		    म_भेदन(cur->name, helper_name, NF_CT_HELPER_NAME_LEN))
			जारी;

		अगर (tuple_set &&
		    (tuple.src.l3num != cur->tuple.src.l3num ||
		     tuple.dst.protonum != cur->tuple.dst.protonum))
			जारी;

		skb2 = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
		अगर (skb2 == शून्य) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		ret = nfnl_cthelper_fill_info(skb2, NETLINK_CB(skb).portid,
					      info->nlh->nlmsg_seq,
					      NFNL_MSG_TYPE(info->nlh->nlmsg_type),
					      NFNL_MSG_CTHELPER_NEW, cur);
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

अटल पूर्णांक nfnl_cthelper_del(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
			     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	अक्षर *helper_name = शून्य;
	काष्ठा nf_conntrack_helper *cur;
	काष्ठा nf_conntrack_tuple tuple;
	bool tuple_set = false, found = false;
	काष्ठा nfnl_cthelper *nlcth, *n;
	पूर्णांक j = 0, ret;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (tb[NFCTH_NAME])
		helper_name = nla_data(tb[NFCTH_NAME]);

	अगर (tb[NFCTH_TUPLE]) अणु
		ret = nfnl_cthelper_parse_tuple(&tuple, tb[NFCTH_TUPLE]);
		अगर (ret < 0)
			वापस ret;

		tuple_set = true;
	पूर्ण

	ret = -ENOENT;
	list_क्रम_each_entry_safe(nlcth, n, &nfnl_cthelper_list, list) अणु
		cur = &nlcth->helper;
		j++;

		अगर (helper_name &&
		    म_भेदन(cur->name, helper_name, NF_CT_HELPER_NAME_LEN))
			जारी;

		अगर (tuple_set &&
		    (tuple.src.l3num != cur->tuple.src.l3num ||
		     tuple.dst.protonum != cur->tuple.dst.protonum))
			जारी;

		अगर (refcount_dec_अगर_one(&cur->refcnt)) अणु
			found = true;
			nf_conntrack_helper_unरेजिस्टर(cur);
			kमुक्त(cur->expect_policy);

			list_del(&nlcth->list);
			kमुक्त(nlcth);
		पूर्ण अन्यथा अणु
			ret = -EBUSY;
		पूर्ण
	पूर्ण

	/* Make sure we वापस success अगर we flush and there is no helpers */
	वापस (found || j == 0) ? 0 : ret;
पूर्ण

अटल स्थिर काष्ठा nla_policy nfnl_cthelper_policy[NFCTH_MAX+1] = अणु
	[NFCTH_NAME] = अणु .type = NLA_NUL_STRING,
			 .len = NF_CT_HELPER_NAME_LEN-1 पूर्ण,
	[NFCTH_QUEUE_NUM] = अणु .type = NLA_U32, पूर्ण,
	[NFCTH_PRIV_DATA_LEN] = अणु .type = NLA_U32, पूर्ण,
	[NFCTH_STATUS] = अणु .type = NLA_U32, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnl_callback nfnl_cthelper_cb[NFNL_MSG_CTHELPER_MAX] = अणु
	[NFNL_MSG_CTHELPER_NEW]	= अणु
		.call		= nfnl_cthelper_new,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= NFCTH_MAX,
		.policy		= nfnl_cthelper_policy
	पूर्ण,
	[NFNL_MSG_CTHELPER_GET] = अणु
		.call		= nfnl_cthelper_get,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= NFCTH_MAX,
		.policy		= nfnl_cthelper_policy
	पूर्ण,
	[NFNL_MSG_CTHELPER_DEL]	= अणु
		.call		= nfnl_cthelper_del,
		.type		= NFNL_CB_MUTEX,
		.attr_count	= NFCTH_MAX,
		.policy		= nfnl_cthelper_policy
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nfnetlink_subप्रणाली nfnl_cthelper_subsys = अणु
	.name				= "cthelper",
	.subsys_id			= NFNL_SUBSYS_CTHELPER,
	.cb_count			= NFNL_MSG_CTHELPER_MAX,
	.cb				= nfnl_cthelper_cb,
पूर्ण;

MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_CTHELPER);

अटल पूर्णांक __init nfnl_cthelper_init(व्योम)
अणु
	पूर्णांक ret;

	ret = nfnetlink_subsys_रेजिस्टर(&nfnl_cthelper_subsys);
	अगर (ret < 0) अणु
		pr_err("nfnl_cthelper: cannot register with nfnetlink.\n");
		जाओ err_out;
	पूर्ण
	वापस 0;
err_out:
	वापस ret;
पूर्ण

अटल व्योम __निकास nfnl_cthelper_निकास(व्योम)
अणु
	काष्ठा nf_conntrack_helper *cur;
	काष्ठा nfnl_cthelper *nlcth, *n;

	nfnetlink_subsys_unरेजिस्टर(&nfnl_cthelper_subsys);

	list_क्रम_each_entry_safe(nlcth, n, &nfnl_cthelper_list, list) अणु
		cur = &nlcth->helper;

		nf_conntrack_helper_unरेजिस्टर(cur);
		kमुक्त(cur->expect_policy);
		kमुक्त(nlcth);
	पूर्ण
पूर्ण

module_init(nfnl_cthelper_init);
module_निकास(nfnl_cthelper_निकास);
