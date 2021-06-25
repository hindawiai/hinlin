<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match packet length. */
/* (C) 1999-2001 James Morris <jmorros@पूर्णांकercode.com.au>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ip.h>

#समावेश <linux/netfilter/xt_length.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_AUTHOR("James Morris <jmorris@intercode.com.au>");
MODULE_DESCRIPTION("Xtables: Packet length (Layer3,4,5) match");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_length");
MODULE_ALIAS("ip6t_length");

अटल bool
length_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_length_info *info = par->matchinfo;
	u_पूर्णांक16_t pktlen = ntohs(ip_hdr(skb)->tot_len);

	वापस (pktlen >= info->min && pktlen <= info->max) ^ info->invert;
पूर्ण

अटल bool
length_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_length_info *info = par->matchinfo;
	स्थिर u_पूर्णांक16_t pktlen = ntohs(ipv6_hdr(skb)->payload_len) +
				 माप(काष्ठा ipv6hdr);

	वापस (pktlen >= info->min && pktlen <= info->max) ^ info->invert;
पूर्ण

अटल काष्ठा xt_match length_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "length",
		.family		= NFPROTO_IPV4,
		.match		= length_mt,
		.matchsize	= माप(काष्ठा xt_length_info),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "length",
		.family		= NFPROTO_IPV6,
		.match		= length_mt6,
		.matchsize	= माप(काष्ठा xt_length_info),
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init length_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(length_mt_reg, ARRAY_SIZE(length_mt_reg));
पूर्ण

अटल व्योम __निकास length_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(length_mt_reg, ARRAY_SIZE(length_mt_reg));
पूर्ण

module_init(length_mt_init);
module_निकास(length_mt_निकास);
