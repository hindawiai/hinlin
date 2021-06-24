<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2008-2009 Pablo Neira Ayuso <pablo@netfilter.org>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/jhash.h>
#समावेश <linux/ip.h>
#समावेश <net/ipv6.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <linux/netfilter/xt_cluster.h>

अटल अंतरभूत u32 nf_ct_orig_ipv4_src(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस (__क्रमce u32)ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u3.ip;
पूर्ण

अटल अंतरभूत स्थिर u32 *nf_ct_orig_ipv6_src(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस (__क्रमce u32 *)ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u3.ip6;
पूर्ण

अटल अंतरभूत u_पूर्णांक32_t
xt_cluster_hash_ipv4(u_पूर्णांक32_t ip, स्थिर काष्ठा xt_cluster_match_info *info)
अणु
	वापस jhash_1word(ip, info->hash_seed);
पूर्ण

अटल अंतरभूत u_पूर्णांक32_t
xt_cluster_hash_ipv6(स्थिर व्योम *ip, स्थिर काष्ठा xt_cluster_match_info *info)
अणु
	वापस jhash2(ip, NF_CT_TUPLE_L3SIZE / माप(__u32), info->hash_seed);
पूर्ण

अटल अंतरभूत u_पूर्णांक32_t
xt_cluster_hash(स्थिर काष्ठा nf_conn *ct,
		स्थिर काष्ठा xt_cluster_match_info *info)
अणु
	u_पूर्णांक32_t hash = 0;

	चयन(nf_ct_l3num(ct)) अणु
	हाल AF_INET:
		hash = xt_cluster_hash_ipv4(nf_ct_orig_ipv4_src(ct), info);
		अवरोध;
	हाल AF_INET6:
		hash = xt_cluster_hash_ipv6(nf_ct_orig_ipv6_src(ct), info);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस reciprocal_scale(hash, info->total_nodes);
पूर्ण

अटल अंतरभूत bool
xt_cluster_is_multicast_addr(स्थिर काष्ठा sk_buff *skb, u_पूर्णांक8_t family)
अणु
	bool is_multicast = false;

	चयन(family) अणु
	हाल NFPROTO_IPV4:
		is_multicast = ipv4_is_multicast(ip_hdr(skb)->daddr);
		अवरोध;
	हाल NFPROTO_IPV6:
		is_multicast = ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
	वापस is_multicast;
पूर्ण

अटल bool
xt_cluster_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	काष्ठा sk_buff *pskb = (काष्ठा sk_buff *)skb;
	स्थिर काष्ठा xt_cluster_match_info *info = par->matchinfo;
	स्थिर काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	अचिन्हित दीर्घ hash;

	/* This match assumes that all nodes see the same packets. This can be
	 * achieved अगर the चयन that connects the cluster nodes support some
	 * sort of 'port mirroring'. However, अगर your चयन करोes not support
	 * this, your cluster nodes can reply ARP request using a multicast MAC
	 * address. Thus, your चयन will flood the same packets to the
	 * cluster nodes with the same multicast MAC address. Using a multicast
	 * link address is a RFC 1812 (section 3.3.2) violation, but this works
	 * fine in practise.
	 *
	 * Unक्रमtunately, अगर you use the multicast MAC address, the link layer
	 * sets skbuff's pkt_type to PACKET_MULTICAST, which is not accepted
	 * by TCP and others क्रम packets coming to this node. For that reason,
	 * this match mangles skbuff's pkt_type अगर it detects a packet
	 * addressed to a unicast address but using PACKET_MULTICAST. Yes, I
	 * know, matches should not alter packets, but we are करोing this here
	 * because we would need to add a PKTTYPE target क्रम this sole purpose.
	 */
	अगर (!xt_cluster_is_multicast_addr(skb, xt_family(par)) &&
	    skb->pkt_type == PACKET_MULTICAST) अणु
	    	pskb->pkt_type = PACKET_HOST;
	पूर्ण

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct == शून्य)
		वापस false;

	अगर (ct->master)
		hash = xt_cluster_hash(ct->master, info);
	अन्यथा
		hash = xt_cluster_hash(ct, info);

	वापस !!((1 << hash) & info->node_mask) ^
	       !!(info->flags & XT_CLUSTER_F_INV);
पूर्ण

अटल पूर्णांक xt_cluster_mt_checkentry(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_cluster_match_info *info = par->matchinfo;
	पूर्णांक ret;

	अगर (info->total_nodes > XT_CLUSTER_NODES_MAX) अणु
		pr_info_ratelimited("you have exceeded the maximum number of cluster nodes (%u > %u)\n",
				    info->total_nodes, XT_CLUSTER_NODES_MAX);
		वापस -EINVAL;
	पूर्ण
	अगर (info->node_mask >= (1ULL << info->total_nodes)) अणु
		pr_info_ratelimited("node mask cannot exceed total number of nodes\n");
		वापस -गलत_तर्क;
	पूर्ण

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0)
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
	वापस ret;
पूर्ण

अटल व्योम xt_cluster_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल काष्ठा xt_match xt_cluster_match __पढ़ो_mostly = अणु
	.name		= "cluster",
	.family		= NFPROTO_UNSPEC,
	.match		= xt_cluster_mt,
	.checkentry	= xt_cluster_mt_checkentry,
	.matchsize	= माप(काष्ठा xt_cluster_match_info),
	.destroy	= xt_cluster_mt_destroy,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init xt_cluster_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&xt_cluster_match);
पूर्ण

अटल व्योम __निकास xt_cluster_mt_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&xt_cluster_match);
पूर्ण

MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: hash-based cluster match");
MODULE_ALIAS("ipt_cluster");
MODULE_ALIAS("ip6t_cluster");
module_init(xt_cluster_mt_init);
module_निकास(xt_cluster_mt_fini);
