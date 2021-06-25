<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_snat
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *
 *  June, 2002
 *
 */
#समावेश <linux/module.h>
#समावेश <net/sock.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/arp.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_nat.h>

अटल अचिन्हित पूर्णांक
ebt_snat_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_nat_info *info = par->targinfo;

	अगर (skb_ensure_writable(skb, 0))
		वापस EBT_DROP;

	ether_addr_copy(eth_hdr(skb)->h_source, info->mac);
	अगर (!(info->target & NAT_ARP_BIT) &&
	    eth_hdr(skb)->h_proto == htons(ETH_P_ARP)) अणु
		स्थिर काष्ठा arphdr *ap;
		काष्ठा arphdr _ah;

		ap = skb_header_poपूर्णांकer(skb, 0, माप(_ah), &_ah);
		अगर (ap == शून्य)
			वापस EBT_DROP;
		अगर (ap->ar_hln != ETH_ALEN)
			जाओ out;
		अगर (skb_store_bits(skb, माप(_ah), info->mac, ETH_ALEN))
			वापस EBT_DROP;
	पूर्ण
out:
	वापस info->target | ~EBT_VERDICT_BITS;
पूर्ण

अटल पूर्णांक ebt_snat_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ebt_nat_info *info = par->targinfo;
	पूर्णांक पंचांगp;

	पंचांगp = info->target | ~EBT_VERDICT_BITS;
	अगर (BASE_CHAIN && पंचांगp == EBT_RETURN)
		वापस -EINVAL;

	अगर (ebt_invalid_target(पंचांगp))
		वापस -EINVAL;
	पंचांगp = info->target | EBT_VERDICT_BITS;
	अगर ((पंचांगp & ~NAT_ARP_BIT) != ~NAT_ARP_BIT)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा xt_target ebt_snat_tg_reg __पढ़ो_mostly = अणु
	.name		= "snat",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.table		= "nat",
	.hooks		= (1 << NF_BR_NUMHOOKS) | (1 << NF_BR_POST_ROUTING),
	.target		= ebt_snat_tg,
	.checkentry	= ebt_snat_tg_check,
	.tarमाला_लोize	= माप(काष्ठा ebt_nat_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_snat_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&ebt_snat_tg_reg);
पूर्ण

अटल व्योम __निकास ebt_snat_fini(व्योम)
अणु
	xt_unरेजिस्टर_target(&ebt_snat_tg_reg);
पूर्ण

module_init(ebt_snat_init);
module_निकास(ebt_snat_fini);
MODULE_DESCRIPTION("Ebtables: Source MAC address translation");
MODULE_LICENSE("GPL");
