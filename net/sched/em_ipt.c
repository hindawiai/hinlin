<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/sched/em_ipt.c IPtables matches Ematch
 *
 * (c) 2018 Eyal Birger <eyal.birger@gmail.com>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/tc_ematch/tc_em_ipt.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <net/pkt_cls.h>

काष्ठा em_ipt_match अणु
	स्थिर काष्ठा xt_match *match;
	u32 hook;
	u8 nfproto;
	u8 match_data[] __aligned(8);
पूर्ण;

काष्ठा em_ipt_xt_match अणु
	अक्षर *match_name;
	पूर्णांक (*validate_match_data)(काष्ठा nlattr **tb, u8 mrev);
पूर्ण;

अटल स्थिर काष्ठा nla_policy em_ipt_policy[TCA_EM_IPT_MAX + 1] = अणु
	[TCA_EM_IPT_MATCH_NAME]		= अणु .type = NLA_STRING,
					    .len = XT_EXTENSION_MAXNAMELEN पूर्ण,
	[TCA_EM_IPT_MATCH_REVISION]	= अणु .type = NLA_U8 पूर्ण,
	[TCA_EM_IPT_HOOK]		= अणु .type = NLA_U32 पूर्ण,
	[TCA_EM_IPT_NFPROTO]		= अणु .type = NLA_U8 पूर्ण,
	[TCA_EM_IPT_MATCH_DATA]		= अणु .type = NLA_UNSPEC पूर्ण,
पूर्ण;

अटल पूर्णांक check_match(काष्ठा net *net, काष्ठा em_ipt_match *im, पूर्णांक mdata_len)
अणु
	काष्ठा xt_mtchk_param mtpar = अणुपूर्ण;
	जोड़ अणु
		काष्ठा ipt_entry e4;
		काष्ठा ip6t_entry e6;
	पूर्ण e = अणुपूर्ण;

	mtpar.net	= net;
	mtpar.table	= "filter";
	mtpar.hook_mask	= 1 << im->hook;
	mtpar.family	= im->match->family;
	mtpar.match	= im->match;
	mtpar.entryinfo = &e;
	mtpar.matchinfo	= (व्योम *)im->match_data;
	वापस xt_check_match(&mtpar, mdata_len, 0, 0);
पूर्ण

अटल पूर्णांक policy_validate_match_data(काष्ठा nlattr **tb, u8 mrev)
अणु
	अगर (mrev != 0) अणु
		pr_err("only policy match revision 0 supported");
		वापस -EINVAL;
	पूर्ण

	अगर (nla_get_u32(tb[TCA_EM_IPT_HOOK]) != NF_INET_PRE_ROUTING) अणु
		pr_err("policy can only be matched on NF_INET_PRE_ROUTING");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक addrtype_validate_match_data(काष्ठा nlattr **tb, u8 mrev)
अणु
	अगर (mrev != 1) अणु
		pr_err("only addrtype match revision 1 supported");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा em_ipt_xt_match em_ipt_xt_matches[] = अणु
	अणु
		.match_name = "policy",
		.validate_match_data = policy_validate_match_data
	पूर्ण,
	अणु
		.match_name = "addrtype",
		.validate_match_data = addrtype_validate_match_data
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा xt_match *get_xt_match(काष्ठा nlattr **tb)
अणु
	स्थिर काष्ठा em_ipt_xt_match *m;
	काष्ठा nlattr *mname_attr;
	u8 nfproto, mrev = 0;
	पूर्णांक ret;

	mname_attr = tb[TCA_EM_IPT_MATCH_NAME];
	क्रम (m = em_ipt_xt_matches; m->match_name; m++) अणु
		अगर (!nla_म_भेद(mname_attr, m->match_name))
			अवरोध;
	पूर्ण

	अगर (!m->match_name) अणु
		pr_err("Unsupported xt match");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (tb[TCA_EM_IPT_MATCH_REVISION])
		mrev = nla_get_u8(tb[TCA_EM_IPT_MATCH_REVISION]);

	ret = m->validate_match_data(tb, mrev);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	nfproto = nla_get_u8(tb[TCA_EM_IPT_NFPROTO]);
	वापस xt_request_find_match(nfproto, m->match_name, mrev);
पूर्ण

अटल पूर्णांक em_ipt_change(काष्ठा net *net, व्योम *data, पूर्णांक data_len,
			 काष्ठा tcf_ematch *em)
अणु
	काष्ठा nlattr *tb[TCA_EM_IPT_MAX + 1];
	काष्ठा em_ipt_match *im = शून्य;
	काष्ठा xt_match *match;
	पूर्णांक mdata_len, ret;
	u8 nfproto;

	ret = nla_parse_deprecated(tb, TCA_EM_IPT_MAX, data, data_len,
				   em_ipt_policy, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (!tb[TCA_EM_IPT_HOOK] || !tb[TCA_EM_IPT_MATCH_NAME] ||
	    !tb[TCA_EM_IPT_MATCH_DATA] || !tb[TCA_EM_IPT_NFPROTO])
		वापस -EINVAL;

	nfproto = nla_get_u8(tb[TCA_EM_IPT_NFPROTO]);
	चयन (nfproto) अणु
	हाल NFPROTO_IPV4:
	हाल NFPROTO_IPV6:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	match = get_xt_match(tb);
	अगर (IS_ERR(match)) अणु
		pr_err("unable to load match\n");
		वापस PTR_ERR(match);
	पूर्ण

	mdata_len = XT_ALIGN(nla_len(tb[TCA_EM_IPT_MATCH_DATA]));
	im = kzalloc(माप(*im) + mdata_len, GFP_KERNEL);
	अगर (!im) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	im->match = match;
	im->hook = nla_get_u32(tb[TCA_EM_IPT_HOOK]);
	im->nfproto = nfproto;
	nla_स_नकल(im->match_data, tb[TCA_EM_IPT_MATCH_DATA], mdata_len);

	ret = check_match(net, im, mdata_len);
	अगर (ret)
		जाओ err;

	em->datalen = माप(*im) + mdata_len;
	em->data = (अचिन्हित दीर्घ)im;
	वापस 0;

err:
	kमुक्त(im);
	module_put(match->me);
	वापस ret;
पूर्ण

अटल व्योम em_ipt_destroy(काष्ठा tcf_ematch *em)
अणु
	काष्ठा em_ipt_match *im = (व्योम *)em->data;

	अगर (!im)
		वापस;

	अगर (im->match->destroy) अणु
		काष्ठा xt_mtdtor_param par = अणु
			.net = em->net,
			.match = im->match,
			.matchinfo = im->match_data,
			.family = im->match->family
		पूर्ण;
		im->match->destroy(&par);
	पूर्ण
	module_put(im->match->me);
	kमुक्त(im);
पूर्ण

अटल पूर्णांक em_ipt_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *em,
			काष्ठा tcf_pkt_info *info)
अणु
	स्थिर काष्ठा em_ipt_match *im = (स्थिर व्योम *)em->data;
	काष्ठा xt_action_param acpar = अणुपूर्ण;
	काष्ठा net_device *indev = शून्य;
	u8 nfproto = im->match->family;
	काष्ठा nf_hook_state state;
	पूर्णांक ret;

	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		अगर (!pskb_network_may_pull(skb, माप(काष्ठा iphdr)))
			वापस 0;
		अगर (nfproto == NFPROTO_UNSPEC)
			nfproto = NFPROTO_IPV4;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		अगर (!pskb_network_may_pull(skb, माप(काष्ठा ipv6hdr)))
			वापस 0;
		अगर (nfproto == NFPROTO_UNSPEC)
			nfproto = NFPROTO_IPV6;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	rcu_पढ़ो_lock();

	अगर (skb->skb_iअगर)
		indev = dev_get_by_index_rcu(em->net, skb->skb_iअगर);

	nf_hook_state_init(&state, im->hook, nfproto,
			   indev ?: skb->dev, skb->dev, शून्य, em->net, शून्य);

	acpar.match = im->match;
	acpar.matchinfo = im->match_data;
	acpar.state = &state;

	ret = im->match->match(skb, &acpar);

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक em_ipt_dump(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *em)
अणु
	काष्ठा em_ipt_match *im = (व्योम *)em->data;

	अगर (nla_put_string(skb, TCA_EM_IPT_MATCH_NAME, im->match->name) < 0)
		वापस -EMSGSIZE;
	अगर (nla_put_u32(skb, TCA_EM_IPT_HOOK, im->hook) < 0)
		वापस -EMSGSIZE;
	अगर (nla_put_u8(skb, TCA_EM_IPT_MATCH_REVISION, im->match->revision) < 0)
		वापस -EMSGSIZE;
	अगर (nla_put_u8(skb, TCA_EM_IPT_NFPROTO, im->nfproto) < 0)
		वापस -EMSGSIZE;
	अगर (nla_put(skb, TCA_EM_IPT_MATCH_DATA,
		    im->match->usersize ?: im->match->matchsize,
		    im->match_data) < 0)
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल काष्ठा tcf_ematch_ops em_ipt_ops = अणु
	.kind	  = TCF_EM_IPT,
	.change	  = em_ipt_change,
	.destroy  = em_ipt_destroy,
	.match	  = em_ipt_match,
	.dump	  = em_ipt_dump,
	.owner	  = THIS_MODULE,
	.link	  = LIST_HEAD_INIT(em_ipt_ops.link)
पूर्ण;

अटल पूर्णांक __init init_em_ipt(व्योम)
अणु
	वापस tcf_em_रेजिस्टर(&em_ipt_ops);
पूर्ण

अटल व्योम __निकास निकास_em_ipt(व्योम)
अणु
	tcf_em_unरेजिस्टर(&em_ipt_ops);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eyal Birger <eyal.birger@gmail.com>");
MODULE_DESCRIPTION("TC extended match for IPtables matches");

module_init(init_em_ipt);
module_निकास(निकास_em_ipt);

MODULE_ALIAS_TCF_EMATCH(TCF_EM_IPT);
