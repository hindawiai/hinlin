<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/ip.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netns/generic.h>
#समावेश <net/route.h>
#समावेश <net/ip.h>

#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <net/netfilter/ipv4/nf_defrag_ipv4.h>
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#पूर्ण_अगर
#समावेश <net/netfilter/nf_conntrack_zones.h>

अटल अचिन्हित पूर्णांक defrag4_pernet_id __पढ़ो_mostly;
अटल DEFINE_MUTEX(defrag4_mutex);

काष्ठा defrag4_pernet अणु
	अचिन्हित पूर्णांक users;
पूर्ण;

अटल पूर्णांक nf_ct_ipv4_gather_frags(काष्ठा net *net, काष्ठा sk_buff *skb,
				   u_पूर्णांक32_t user)
अणु
	पूर्णांक err;

	local_bh_disable();
	err = ip_defrag(net, skb, user);
	local_bh_enable();

	अगर (!err)
		skb->ignore_df = 1;

	वापस err;
पूर्ण

अटल क्रमागत ip_defrag_users nf_ct_defrag_user(अचिन्हित पूर्णांक hooknum,
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
		वापस IP_DEFRAG_CONNTRACK_BRIDGE_IN + zone_id;

	अगर (hooknum == NF_INET_PRE_ROUTING)
		वापस IP_DEFRAG_CONNTRACK_IN + zone_id;
	अन्यथा
		वापस IP_DEFRAG_CONNTRACK_OUT + zone_id;
पूर्ण

अटल अचिन्हित पूर्णांक ipv4_conntrack_defrag(व्योम *priv,
					  काष्ठा sk_buff *skb,
					  स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा sock *sk = skb->sk;

	अगर (sk && sk_fullsock(sk) && (sk->sk_family == PF_INET) &&
	    inet_sk(sk)->nodefrag)
		वापस NF_ACCEPT;

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#अगर !IS_ENABLED(CONFIG_NF_NAT)
	/* Previously seen (loopback)?  Ignore.  Do this beक्रमe
	   fragment check. */
	अगर (skb_nfct(skb) && !nf_ct_is_ढाँचा((काष्ठा nf_conn *)skb_nfct(skb)))
		वापस NF_ACCEPT;
#पूर्ण_अगर
	अगर (skb->_nfct == IP_CT_UNTRACKED)
		वापस NF_ACCEPT;
#पूर्ण_अगर
	/* Gather fragments. */
	अगर (ip_is_fragment(ip_hdr(skb))) अणु
		क्रमागत ip_defrag_users user =
			nf_ct_defrag_user(state->hook, skb);

		अगर (nf_ct_ipv4_gather_frags(state->net, skb, user))
			वापस NF_STOLEN;
	पूर्ण
	वापस NF_ACCEPT;
पूर्ण

अटल स्थिर काष्ठा nf_hook_ops ipv4_defrag_ops[] = अणु
	अणु
		.hook		= ipv4_conntrack_defrag,
		.pf		= NFPROTO_IPV4,
		.hooknum	= NF_INET_PRE_ROUTING,
		.priority	= NF_IP_PRI_CONNTRACK_DEFRAG,
	पूर्ण,
	अणु
		.hook           = ipv4_conntrack_defrag,
		.pf             = NFPROTO_IPV4,
		.hooknum        = NF_INET_LOCAL_OUT,
		.priority       = NF_IP_PRI_CONNTRACK_DEFRAG,
	पूर्ण,
पूर्ण;

अटल व्योम __net_निकास defrag4_net_निकास(काष्ठा net *net)
अणु
	काष्ठा defrag4_pernet *nf_defrag = net_generic(net, defrag4_pernet_id);

	अगर (nf_defrag->users) अणु
		nf_unरेजिस्टर_net_hooks(net, ipv4_defrag_ops,
					ARRAY_SIZE(ipv4_defrag_ops));
		nf_defrag->users = 0;
	पूर्ण
पूर्ण

अटल काष्ठा pernet_operations defrag4_net_ops = अणु
	.निकास = defrag4_net_निकास,
	.id   = &defrag4_pernet_id,
	.size = माप(काष्ठा defrag4_pernet),
पूर्ण;

अटल पूर्णांक __init nf_defrag_init(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&defrag4_net_ops);
पूर्ण

अटल व्योम __निकास nf_defrag_fini(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&defrag4_net_ops);
पूर्ण

पूर्णांक nf_defrag_ipv4_enable(काष्ठा net *net)
अणु
	काष्ठा defrag4_pernet *nf_defrag = net_generic(net, defrag4_pernet_id);
	पूर्णांक err = 0;

	mutex_lock(&defrag4_mutex);
	अगर (nf_defrag->users == अच_पूर्णांक_उच्च) अणु
		err = -EOVERFLOW;
		जाओ out_unlock;
	पूर्ण

	अगर (nf_defrag->users) अणु
		nf_defrag->users++;
		जाओ out_unlock;
	पूर्ण

	err = nf_रेजिस्टर_net_hooks(net, ipv4_defrag_ops,
				    ARRAY_SIZE(ipv4_defrag_ops));
	अगर (err == 0)
		nf_defrag->users = 1;

 out_unlock:
	mutex_unlock(&defrag4_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nf_defrag_ipv4_enable);

व्योम nf_defrag_ipv4_disable(काष्ठा net *net)
अणु
	काष्ठा defrag4_pernet *nf_defrag = net_generic(net, defrag4_pernet_id);

	mutex_lock(&defrag4_mutex);
	अगर (nf_defrag->users) अणु
		nf_defrag->users--;
		अगर (nf_defrag->users == 0)
			nf_unरेजिस्टर_net_hooks(net, ipv4_defrag_ops,
						ARRAY_SIZE(ipv4_defrag_ops));
	पूर्ण

	mutex_unlock(&defrag4_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(nf_defrag_ipv4_disable);

module_init(nf_defrag_init);
module_निकास(nf_defrag_fini);

MODULE_LICENSE("GPL");
