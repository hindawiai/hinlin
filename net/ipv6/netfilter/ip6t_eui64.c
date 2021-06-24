<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match EUI64 address parameters. */

/* (C) 2001-2002 Andras Kis-Szabo <kisza@sch.bme.hu>
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/अगर_ether.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>

MODULE_DESCRIPTION("Xtables: IPv6 EUI64 address match");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andras Kis-Szabo <kisza@sch.bme.hu>");

अटल bool
eui64_mt6(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	अचिन्हित अक्षर eui64[8];

	अगर (!(skb_mac_header(skb) >= skb->head &&
	      skb_mac_header(skb) + ETH_HLEN <= skb->data) &&
	    par->fragoff != 0) अणु
		par->hotdrop = true;
		वापस false;
	पूर्ण

	स_रखो(eui64, 0, माप(eui64));

	अगर (eth_hdr(skb)->h_proto == htons(ETH_P_IPV6)) अणु
		अगर (ipv6_hdr(skb)->version == 0x6) अणु
			स_नकल(eui64, eth_hdr(skb)->h_source, 3);
			स_नकल(eui64 + 5, eth_hdr(skb)->h_source + 3, 3);
			eui64[3] = 0xff;
			eui64[4] = 0xfe;
			eui64[0] ^= 0x02;

			अगर (!स_भेद(ipv6_hdr(skb)->saddr.s6_addr + 8, eui64,
				    माप(eui64)))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा xt_match eui64_mt6_reg __पढ़ो_mostly = अणु
	.name		= "eui64",
	.family		= NFPROTO_IPV6,
	.match		= eui64_mt6,
	.matchsize	= माप(पूर्णांक),
	.hooks		= (1 << NF_INET_PRE_ROUTING) | (1 << NF_INET_LOCAL_IN) |
			  (1 << NF_INET_FORWARD),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init eui64_mt6_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&eui64_mt6_reg);
पूर्ण

अटल व्योम __निकास eui64_mt6_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&eui64_mt6_reg);
पूर्ण

module_init(eui64_mt6_init);
module_निकास(eui64_mt6_निकास);
