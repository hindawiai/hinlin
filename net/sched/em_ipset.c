<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sched/em_ipset.c	ipset ematch
 *
 * Copyright (c) 2012 Florian Westphal <fw@म_माप.de>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter/xt_set.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ip.h>
#समावेश <net/pkt_cls.h>

अटल पूर्णांक em_ipset_change(काष्ठा net *net, व्योम *data, पूर्णांक data_len,
			   काष्ठा tcf_ematch *em)
अणु
	काष्ठा xt_set_info *set = data;
	ip_set_id_t index;

	अगर (data_len != माप(*set))
		वापस -EINVAL;

	index = ip_set_nfnl_get_byindex(net, set->index);
	अगर (index == IPSET_INVALID_ID)
		वापस -ENOENT;

	em->datalen = माप(*set);
	em->data = (अचिन्हित दीर्घ)kmemdup(data, em->datalen, GFP_KERNEL);
	अगर (em->data)
		वापस 0;

	ip_set_nfnl_put(net, index);
	वापस -ENOMEM;
पूर्ण

अटल व्योम em_ipset_destroy(काष्ठा tcf_ematch *em)
अणु
	स्थिर काष्ठा xt_set_info *set = (स्थिर व्योम *) em->data;
	अगर (set) अणु
		ip_set_nfnl_put(em->net, set->index);
		kमुक्त((व्योम *) em->data);
	पूर्ण
पूर्ण

अटल पूर्णांक em_ipset_match(काष्ठा sk_buff *skb, काष्ठा tcf_ematch *em,
			  काष्ठा tcf_pkt_info *info)
अणु
	काष्ठा ip_set_adt_opt opt;
	काष्ठा xt_action_param acpar;
	स्थिर काष्ठा xt_set_info *set = (स्थिर व्योम *) em->data;
	काष्ठा net_device *dev, *indev = शून्य;
	काष्ठा nf_hook_state state = अणु
		.net	= em->net,
	पूर्ण;
	पूर्णांक ret, network_offset;

	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		state.pf = NFPROTO_IPV4;
		अगर (!pskb_network_may_pull(skb, माप(काष्ठा iphdr)))
			वापस 0;
		acpar.thoff = ip_hdrlen(skb);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		state.pf = NFPROTO_IPV6;
		अगर (!pskb_network_may_pull(skb, माप(काष्ठा ipv6hdr)))
			वापस 0;
		/* करोesn't call ipv6_find_hdr() because ipset doesn't use thoff, yet */
		acpar.thoff = माप(काष्ठा ipv6hdr);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	opt.family = state.pf;
	opt.dim = set->dim;
	opt.flags = set->flags;
	opt.cmdflags = 0;
	opt.ext.समयout = ~0u;

	network_offset = skb_network_offset(skb);
	skb_pull(skb, network_offset);

	dev = skb->dev;

	rcu_पढ़ो_lock();

	अगर (skb->skb_iअगर)
		indev = dev_get_by_index_rcu(em->net, skb->skb_iअगर);

	state.in      = indev ? indev : dev;
	state.out     = dev;
	acpar.state   = &state;

	ret = ip_set_test(set->index, skb, &acpar, &opt);

	rcu_पढ़ो_unlock();

	skb_push(skb, network_offset);
	वापस ret;
पूर्ण

अटल काष्ठा tcf_ematch_ops em_ipset_ops = अणु
	.kind	  = TCF_EM_IPSET,
	.change	  = em_ipset_change,
	.destroy  = em_ipset_destroy,
	.match	  = em_ipset_match,
	.owner	  = THIS_MODULE,
	.link	  = LIST_HEAD_INIT(em_ipset_ops.link)
पूर्ण;

अटल पूर्णांक __init init_em_ipset(व्योम)
अणु
	वापस tcf_em_रेजिस्टर(&em_ipset_ops);
पूर्ण

अटल व्योम __निकास निकास_em_ipset(व्योम)
अणु
	tcf_em_unरेजिस्टर(&em_ipset_ops);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
MODULE_DESCRIPTION("TC extended match for IP sets");

module_init(init_em_ipset);
module_निकास(निकास_em_ipset);

MODULE_ALIAS_TCF_EMATCH(TCF_EM_IPSET);
