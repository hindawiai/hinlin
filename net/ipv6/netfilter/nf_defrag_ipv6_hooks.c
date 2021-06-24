<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/in6.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/icmp.h>
#समावेश <linux/sysctl.h>
#समावेश <net/ipv6_frag.h>

#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter_bridge.h>
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/ipv6/nf_conntrack_ipv6.h>
#पूर्ण_अगर
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>

बाह्य अचिन्हित पूर्णांक nf_frag_pernet_id;

अटल DEFINE_MUTEX(defrag6_mutex);

अटल क्रमागत ip6_defrag_users nf_ct6_defrag_user(अचिन्हित पूर्णांक hooknum,
						काष्ठा sk_buff *skb)
अणु
	u16 zone_id = NF_CT_DEFAULT_ZONE_ID;
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	अगर (skb_nfct(skb)) अणु
		क्रमागत ip_conntrack_info ctinfo;
		स्थिर काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);

		zone_id = nf_ct_zone_id(nf_ct_zone(ct), CTINFO2सूची(ctinfo));
	पूर्ण
#पूर्ण_अगर
	अगर (nf_bridge_in_prerouting(skb))
		वापस IP6_DEFRAG_CONNTRACK_BRIDGE_IN + zone_id;

	अगर (hooknum == NF_INET_PRE_ROUTING)
		वापस IP6_DEFRAG_CONNTRACK_IN + zone_id;
	अन्यथा
		वापस IP6_DEFRAG_CONNTRACK_OUT + zone_id;
पूर्ण

अटल अचिन्हित पूर्णांक ipv6_defrag(व्योम *priv,
				काष्ठा sk_buff *skb,
				स्थिर काष्ठा nf_hook_state *state)
अणु
	पूर्णांक err;

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	/* Previously seen (loopback)?	*/
	अगर (skb_nfct(skb) && !nf_ct_is_ढाँचा((काष्ठा nf_conn *)skb_nfct(skb)))
		वापस NF_ACCEPT;

	अगर (skb->_nfct == IP_CT_UNTRACKED)
		वापस NF_ACCEPT;
#पूर्ण_अगर

	err = nf_ct_frag6_gather(state->net, skb,
				 nf_ct6_defrag_user(state->hook, skb));
	/* queued */
	अगर (err == -EINPROGRESS)
		वापस NF_STOLEN;

	वापस err == 0 ? NF_ACCEPT : NF_DROP;
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops ipv6_defrag_ops[] = अणु
	अणु
		.hook		= ipv6_defrag,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_PRE_ROUTING,
		.priority	= NF_IP6_PRI_CONNTRACK_DEFRAG,
	पूर्ण,
	अणु
		.hook		= ipv6_defrag,
		.pf		= NFPROTO_IPV6,
		.hooknum	= NF_INET_LOCAL_OUT,
		.priority	= NF_IP6_PRI_CONNTRACK_DEFRAG,
	पूर्ण,
पूर्ण;

अटल व्योम __net_निकास defrag6_net_निकास(काष्ठा net *net)
अणु
	काष्ठा nft_ct_frag6_pernet *nf_frag = net_generic(net, nf_frag_pernet_id);

	अगर (nf_frag->users) अणु
		nf_unरेजिस्टर_net_hooks(net, ipv6_defrag_ops,
					ARRAY_SIZE(ipv6_defrag_ops));
		nf_frag->users = 0;
	पूर्ण
पूर्ण

अटल काष्ठा pernet_operations defrag6_net_ops = अणु
	.निकास = defrag6_net_निकास,
पूर्ण;

अटल पूर्णांक __init nf_defrag_init(व्योम)
अणु
	पूर्णांक ret = 0;

	ret = nf_ct_frag6_init();
	अगर (ret < 0) अणु
		pr_err("nf_defrag_ipv6: can't initialize frag6.\n");
		वापस ret;
	पूर्ण
	ret = रेजिस्टर_pernet_subsys(&defrag6_net_ops);
	अगर (ret < 0) अणु
		pr_err("nf_defrag_ipv6: can't register pernet ops\n");
		जाओ cleanup_frag6;
	पूर्ण
	वापस ret;

cleanup_frag6:
	nf_ct_frag6_cleanup();
	वापस ret;

पूर्ण

अटल व्योम __निकास nf_defrag_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&defrag6_net_ops);
	nf_ct_frag6_cleanup();
पूर्ण

पूर्णांक nf_defrag_ipv6_enable(काष्ठा net *net)
अणु
	काष्ठा nft_ct_frag6_pernet *nf_frag = net_generic(net, nf_frag_pernet_id);
	पूर्णांक err = 0;

	mutex_lock(&defrag6_mutex);
	अगर (nf_frag->users == अच_पूर्णांक_उच्च) अणु
		err = -EOVERFLOW;
		जाओ out_unlock;
	पूर्ण

	अगर (nf_frag->users) अणु
		nf_frag->users++;
		जाओ out_unlock;
	पूर्ण

	err = nf_रेजिस्टर_net_hooks(net, ipv6_defrag_ops,
				    ARRAY_SIZE(ipv6_defrag_ops));
	अगर (err == 0)
		nf_frag->users = 1;

 out_unlock:
	mutex_unlock(&defrag6_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nf_defrag_ipv6_enable);

व्योम nf_defrag_ipv6_disable(काष्ठा net *net)
अणु
	काष्ठा nft_ct_frag6_pernet *nf_frag = net_generic(net, nf_frag_pernet_id);

	mutex_lock(&defrag6_mutex);
	अगर (nf_frag->users) अणु
		nf_frag->users--;
		अगर (nf_frag->users == 0)
			nf_unरेजिस्टर_net_hooks(net, ipv6_defrag_ops,
						ARRAY_SIZE(ipv6_defrag_ops));
	पूर्ण
	mutex_unlock(&defrag6_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nf_defrag_ipv6_disable);

module_init(nf_defrag_init);
module_निकास(nf_defrag_fini);

MODULE_LICENSE("GPL");
