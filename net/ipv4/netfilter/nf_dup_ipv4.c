<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) 2007 by Sebastian Claथen <sebastian.classen@मुक्तnet.ag>
 * (C) 2007-2010 by Jan Engelhardt <jengelh@meकरोzas.de>
 *
 * Extracted from xt_TEE.c
 */
#समावेश <linux/ip.h>
#समावेश <linux/module.h>
#समावेश <linux/percpu.h>
#समावेश <linux/route.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter.h>
#समावेश <net/checksum.h>
#समावेश <net/icmp.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/netfilter/ipv4/nf_dup_ipv4.h>
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#पूर्ण_अगर

अटल bool nf_dup_ipv4_route(काष्ठा net *net, काष्ठा sk_buff *skb,
			      स्थिर काष्ठा in_addr *gw, पूर्णांक oअगर)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4;

	स_रखो(&fl4, 0, माप(fl4));
	अगर (oअगर != -1)
		fl4.flowi4_oअगर = oअगर;

	fl4.daddr = gw->s_addr;
	fl4.flowi4_tos = RT_TOS(iph->tos);
	fl4.flowi4_scope = RT_SCOPE_UNIVERSE;
	fl4.flowi4_flags = FLOWI_FLAG_KNOWN_NH;
	rt = ip_route_output_key(net, &fl4);
	अगर (IS_ERR(rt))
		वापस false;

	skb_dst_drop(skb);
	skb_dst_set(skb, &rt->dst);
	skb->dev      = rt->dst.dev;
	skb->protocol = htons(ETH_P_IP);

	वापस true;
पूर्ण

व्योम nf_dup_ipv4(काष्ठा net *net, काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hooknum,
		 स्थिर काष्ठा in_addr *gw, पूर्णांक oअगर)
अणु
	काष्ठा iphdr *iph;

	अगर (this_cpu_पढ़ो(nf_skb_duplicated))
		वापस;
	/*
	 * Copy the skb, and route the copy. Will later वापस %XT_CONTINUE क्रम
	 * the original skb, which should जारी on its way as अगर nothing has
	 * happened. The copy should be independently delivered to the gateway.
	 */
	skb = pskb_copy(skb, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस;

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	/* Aव्योम counting cloned packets towards the original connection. */
	nf_reset_ct(skb);
	nf_ct_set(skb, शून्य, IP_CT_UNTRACKED);
#पूर्ण_अगर
	/*
	 * If we are in PREROUTING/INPUT, decrease the TTL to mitigate potential
	 * loops between two hosts.
	 *
	 * Set %IP_DF so that the original source is notअगरied of a potentially
	 * decreased MTU on the clone route. IPv6 करोes this too.
	 *
	 * IP header checksum will be recalculated at ip_local_out.
	 */
	iph = ip_hdr(skb);
	iph->frag_off |= htons(IP_DF);
	अगर (hooknum == NF_INET_PRE_ROUTING ||
	    hooknum == NF_INET_LOCAL_IN)
		--iph->ttl;

	अगर (nf_dup_ipv4_route(net, skb, gw, oअगर)) अणु
		__this_cpu_ग_लिखो(nf_skb_duplicated, true);
		ip_local_out(net, skb->sk, skb);
		__this_cpu_ग_लिखो(nf_skb_duplicated, false);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nf_dup_ipv4);

MODULE_AUTHOR("Sebastian Claथen <sebastian.classen@freenet.ag>");
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("nf_dup_ipv4: Duplicate IPv4 packet");
MODULE_LICENSE("GPL");
