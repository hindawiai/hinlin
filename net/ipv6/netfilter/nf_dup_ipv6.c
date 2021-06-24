<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) 2007 by Sebastian Claथen <sebastian.classen@मुक्तnet.ag>
 * (C) 2007-2010 by Jan Engelhardt <jengelh@meकरोzas.de>
 *
 * Extracted from xt_TEE.c
 */
#समावेश <linux/module.h>
#समावेश <linux/percpu.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/netfilter/ipv6/nf_dup_ipv6.h>
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
#समावेश <net/netfilter/nf_conntrack.h>
#पूर्ण_अगर

अटल bool nf_dup_ipv6_route(काष्ठा net *net, काष्ठा sk_buff *skb,
			      स्थिर काष्ठा in6_addr *gw, पूर्णांक oअगर)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6;

	स_रखो(&fl6, 0, माप(fl6));
	अगर (oअगर != -1)
		fl6.flowi6_oअगर = oअगर;

	fl6.daddr = *gw;
	fl6.flowlabel = (__क्रमce __be32)(((iph->flow_lbl[0] & 0xF) << 16) |
			(iph->flow_lbl[1] << 8) | iph->flow_lbl[2]);
	fl6.flowi6_flags = FLOWI_FLAG_KNOWN_NH;
	dst = ip6_route_output(net, शून्य, &fl6);
	अगर (dst->error) अणु
		dst_release(dst);
		वापस false;
	पूर्ण
	skb_dst_drop(skb);
	skb_dst_set(skb, dst);
	skb->dev      = dst->dev;
	skb->protocol = htons(ETH_P_IPV6);

	वापस true;
पूर्ण

व्योम nf_dup_ipv6(काष्ठा net *net, काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hooknum,
		 स्थिर काष्ठा in6_addr *gw, पूर्णांक oअगर)
अणु
	अगर (this_cpu_पढ़ो(nf_skb_duplicated))
		वापस;
	skb = pskb_copy(skb, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस;

#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	nf_reset_ct(skb);
	nf_ct_set(skb, शून्य, IP_CT_UNTRACKED);
#पूर्ण_अगर
	अगर (hooknum == NF_INET_PRE_ROUTING ||
	    hooknum == NF_INET_LOCAL_IN) अणु
		काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
		--iph->hop_limit;
	पूर्ण
	अगर (nf_dup_ipv6_route(net, skb, gw, oअगर)) अणु
		__this_cpu_ग_लिखो(nf_skb_duplicated, true);
		ip6_local_out(net, skb->sk, skb);
		__this_cpu_ग_लिखो(nf_skb_duplicated, false);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nf_dup_ipv6);

MODULE_AUTHOR("Sebastian Claथen <sebastian.classen@freenet.ag>");
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("nf_dup_ipv6: IPv6 packet duplication");
MODULE_LICENSE("GPL");
