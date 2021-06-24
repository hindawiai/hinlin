<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match MAC address parameters. */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/etherdevice.h>

#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/netfilter/xt_mac.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("Xtables: MAC address match");
MODULE_ALIAS("ipt_mac");
MODULE_ALIAS("ip6t_mac");

अटल bool mac_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_mac_info *info = par->matchinfo;
	bool ret;

	अगर (skb->dev == शून्य || skb->dev->type != ARPHRD_ETHER)
		वापस false;
	अगर (skb_mac_header(skb) < skb->head)
		वापस false;
	अगर (skb_mac_header(skb) + ETH_HLEN > skb->data)
		वापस false;
	ret  = ether_addr_equal(eth_hdr(skb)->h_source, info->srcaddr);
	ret ^= info->invert;
	वापस ret;
पूर्ण

अटल काष्ठा xt_match mac_mt_reg __पढ़ो_mostly = अणु
	.name      = "mac",
	.revision  = 0,
	.family    = NFPROTO_UNSPEC,
	.match     = mac_mt,
	.matchsize = माप(काष्ठा xt_mac_info),
	.hooks     = (1 << NF_INET_PRE_ROUTING) | (1 << NF_INET_LOCAL_IN) |
	             (1 << NF_INET_FORWARD),
	.me        = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init mac_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&mac_mt_reg);
पूर्ण

अटल व्योम __निकास mac_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&mac_mt_reg);
पूर्ण

module_init(mac_mt_init);
module_निकास(mac_mt_निकास);
