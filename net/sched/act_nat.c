<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Stateless NAT actions
 *
 * Copyright (c) 2007 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/tc_act/tc_nat.h>
#समावेश <net/act_api.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/icmp.h>
#समावेश <net/ip.h>
#समावेश <net/netlink.h>
#समावेश <net/tc_act/tc_nat.h>
#समावेश <net/tcp.h>
#समावेश <net/udp.h>


अटल अचिन्हित पूर्णांक nat_net_id;
अटल काष्ठा tc_action_ops act_nat_ops;

अटल स्थिर काष्ठा nla_policy nat_policy[TCA_NAT_MAX + 1] = अणु
	[TCA_NAT_PARMS]	= अणु .len = माप(काष्ठा tc_nat) पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_nat_init(काष्ठा net *net, काष्ठा nlattr *nla, काष्ठा nlattr *est,
			काष्ठा tc_action **a, पूर्णांक ovr, पूर्णांक bind,
			bool rtnl_held,	काष्ठा tcf_proto *tp,
			u32 flags, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, nat_net_id);
	काष्ठा nlattr *tb[TCA_NAT_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_nat *parm;
	पूर्णांक ret = 0, err;
	काष्ठा tcf_nat *p;
	u32 index;

	अगर (nla == शून्य)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, TCA_NAT_MAX, nla, nat_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[TCA_NAT_PARMS] == शून्य)
		वापस -EINVAL;
	parm = nla_data(tb[TCA_NAT_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (!err) अणु
		ret = tcf_idr_create(tn, index, est, a,
				     &act_nat_ops, bind, false, 0);
		अगर (ret) अणु
			tcf_idr_cleanup(tn, index);
			वापस ret;
		पूर्ण
		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (err > 0) अणु
		अगर (bind)
			वापस 0;
		अगर (!ovr) अणु
			tcf_idr_release(*a, bind);
			वापस -EEXIST;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस err;
	पूर्ण
	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ release_idr;
	p = to_tcf_nat(*a);

	spin_lock_bh(&p->tcf_lock);
	p->old_addr = parm->old_addr;
	p->new_addr = parm->new_addr;
	p->mask = parm->mask;
	p->flags = parm->flags;

	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	spin_unlock_bh(&p->tcf_lock);
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);

	वापस ret;
release_idr:
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल पूर्णांक tcf_nat_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
		       काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_nat *p = to_tcf_nat(a);
	काष्ठा iphdr *iph;
	__be32 old_addr;
	__be32 new_addr;
	__be32 mask;
	__be32 addr;
	पूर्णांक egress;
	पूर्णांक action;
	पूर्णांक ihl;
	पूर्णांक noff;

	spin_lock(&p->tcf_lock);

	tcf_lastuse_update(&p->tcf_पंचांग);
	old_addr = p->old_addr;
	new_addr = p->new_addr;
	mask = p->mask;
	egress = p->flags & TCA_NAT_FLAG_EGRESS;
	action = p->tcf_action;

	bstats_update(&p->tcf_bstats, skb);

	spin_unlock(&p->tcf_lock);

	अगर (unlikely(action == TC_ACT_SHOT))
		जाओ drop;

	noff = skb_network_offset(skb);
	अगर (!pskb_may_pull(skb, माप(*iph) + noff))
		जाओ drop;

	iph = ip_hdr(skb);

	अगर (egress)
		addr = iph->saddr;
	अन्यथा
		addr = iph->daddr;

	अगर (!((old_addr ^ addr) & mask)) अणु
		अगर (skb_try_make_writable(skb, माप(*iph) + noff))
			जाओ drop;

		new_addr &= mask;
		new_addr |= addr & ~mask;

		/* Reग_लिखो IP header */
		iph = ip_hdr(skb);
		अगर (egress)
			iph->saddr = new_addr;
		अन्यथा
			iph->daddr = new_addr;

		csum_replace4(&iph->check, addr, new_addr);
	पूर्ण अन्यथा अगर ((iph->frag_off & htons(IP_OFFSET)) ||
		   iph->protocol != IPPROTO_ICMP) अणु
		जाओ out;
	पूर्ण

	ihl = iph->ihl * 4;

	/* It would be nice to share code with stateful NAT. */
	चयन (iph->frag_off & htons(IP_OFFSET) ? 0 : iph->protocol) अणु
	हाल IPPROTO_TCP:
	अणु
		काष्ठा tcphdr *tcph;

		अगर (!pskb_may_pull(skb, ihl + माप(*tcph) + noff) ||
		    skb_try_make_writable(skb, ihl + माप(*tcph) + noff))
			जाओ drop;

		tcph = (व्योम *)(skb_network_header(skb) + ihl);
		inet_proto_csum_replace4(&tcph->check, skb, addr, new_addr,
					 true);
		अवरोध;
	पूर्ण
	हाल IPPROTO_UDP:
	अणु
		काष्ठा udphdr *udph;

		अगर (!pskb_may_pull(skb, ihl + माप(*udph) + noff) ||
		    skb_try_make_writable(skb, ihl + माप(*udph) + noff))
			जाओ drop;

		udph = (व्योम *)(skb_network_header(skb) + ihl);
		अगर (udph->check || skb->ip_summed == CHECKSUM_PARTIAL) अणु
			inet_proto_csum_replace4(&udph->check, skb, addr,
						 new_addr, true);
			अगर (!udph->check)
				udph->check = CSUM_MANGLED_0;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल IPPROTO_ICMP:
	अणु
		काष्ठा icmphdr *icmph;

		अगर (!pskb_may_pull(skb, ihl + माप(*icmph) + noff))
			जाओ drop;

		icmph = (व्योम *)(skb_network_header(skb) + ihl);

		अगर (!icmp_is_err(icmph->type))
			अवरोध;

		अगर (!pskb_may_pull(skb, ihl + माप(*icmph) + माप(*iph) +
					noff))
			जाओ drop;

		icmph = (व्योम *)(skb_network_header(skb) + ihl);
		iph = (व्योम *)(icmph + 1);
		अगर (egress)
			addr = iph->daddr;
		अन्यथा
			addr = iph->saddr;

		अगर ((old_addr ^ addr) & mask)
			अवरोध;

		अगर (skb_try_make_writable(skb, ihl + माप(*icmph) +
					  माप(*iph) + noff))
			जाओ drop;

		icmph = (व्योम *)(skb_network_header(skb) + ihl);
		iph = (व्योम *)(icmph + 1);

		new_addr &= mask;
		new_addr |= addr & ~mask;

		/* XXX Fix up the inner checksums. */
		अगर (egress)
			iph->daddr = new_addr;
		अन्यथा
			iph->saddr = new_addr;

		inet_proto_csum_replace4(&icmph->checksum, skb, addr, new_addr,
					 false);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

out:
	वापस action;

drop:
	spin_lock(&p->tcf_lock);
	p->tcf_qstats.drops++;
	spin_unlock(&p->tcf_lock);
	वापस TC_ACT_SHOT;
पूर्ण

अटल पूर्णांक tcf_nat_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_nat *p = to_tcf_nat(a);
	काष्ठा tc_nat opt = अणु
		.index    = p->tcf_index,
		.refcnt   = refcount_पढ़ो(&p->tcf_refcnt) - ref,
		.bindcnt  = atomic_पढ़ो(&p->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&p->tcf_lock);
	opt.old_addr = p->old_addr;
	opt.new_addr = p->new_addr;
	opt.mask = p->mask;
	opt.flags = p->flags;
	opt.action = p->tcf_action;

	अगर (nla_put(skb, TCA_NAT_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &p->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_NAT_TM, माप(t), &t, TCA_NAT_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&p->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&p->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_nat_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			  काष्ठा netlink_callback *cb, पूर्णांक type,
			  स्थिर काष्ठा tc_action_ops *ops,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, nat_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_nat_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, nat_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_nat_ops = अणु
	.kind		=	"nat",
	.id		=	TCA_ID_NAT,
	.owner		=	THIS_MODULE,
	.act		=	tcf_nat_act,
	.dump		=	tcf_nat_dump,
	.init		=	tcf_nat_init,
	.walk		=	tcf_nat_walker,
	.lookup		=	tcf_nat_search,
	.size		=	माप(काष्ठा tcf_nat),
पूर्ण;

अटल __net_init पूर्णांक nat_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, nat_net_id);

	वापस tc_action_net_init(net, tn, &act_nat_ops);
पूर्ण

अटल व्योम __net_निकास nat_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, nat_net_id);
पूर्ण

अटल काष्ठा pernet_operations nat_net_ops = अणु
	.init = nat_init_net,
	.निकास_batch = nat_निकास_net,
	.id   = &nat_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

MODULE_DESCRIPTION("Stateless NAT actions");
MODULE_LICENSE("GPL");

अटल पूर्णांक __init nat_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_nat_ops, &nat_net_ops);
पूर्ण

अटल व्योम __निकास nat_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_nat_ops, &nat_net_ops);
पूर्ण

module_init(nat_init_module);
module_निकास(nat_cleanup_module);
