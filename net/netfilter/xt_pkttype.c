<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Michal Ludvig <michal@logix.cz>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>

#समावेश <linux/netfilter/xt_pkttype.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michal Ludvig <michal@logix.cz>");
MODULE_DESCRIPTION("Xtables: link layer packet type match");
MODULE_ALIAS("ipt_pkttype");
MODULE_ALIAS("ip6t_pkttype");

अटल bool
pkttype_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_pkttype_info *info = par->matchinfo;
	u_पूर्णांक8_t type;

	अगर (skb->pkt_type != PACKET_LOOPBACK)
		type = skb->pkt_type;
	अन्यथा अगर (xt_family(par) == NFPROTO_IPV4 &&
	    ipv4_is_multicast(ip_hdr(skb)->daddr))
		type = PACKET_MULTICAST;
	अन्यथा अगर (xt_family(par) == NFPROTO_IPV6)
		type = PACKET_MULTICAST;
	अन्यथा
		type = PACKET_BROADCAST;

	वापस (type == info->pkttype) ^ info->invert;
पूर्ण

अटल काष्ठा xt_match pkttype_mt_reg __पढ़ो_mostly = अणु
	.name      = "pkttype",
	.revision  = 0,
	.family    = NFPROTO_UNSPEC,
	.match     = pkttype_mt,
	.matchsize = माप(काष्ठा xt_pkttype_info),
	.me        = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init pkttype_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&pkttype_mt_reg);
पूर्ण

अटल व्योम __निकास pkttype_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&pkttype_mt_reg);
पूर्ण

module_init(pkttype_mt_init);
module_निकास(pkttype_mt_निकास);
