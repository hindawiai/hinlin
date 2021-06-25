<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_arp
 *
 *	Authors:
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *	Tim Gardner <timg@tpi.com>
 *
 *  April, 2002
 *
 */
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_arp.h>

अटल bool
ebt_arp_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_arp_info *info = par->matchinfo;
	स्थिर काष्ठा arphdr *ah;
	काष्ठा arphdr _arph;

	ah = skb_header_poपूर्णांकer(skb, 0, माप(_arph), &_arph);
	अगर (ah == शून्य)
		वापस false;
	अगर ((info->biपंचांगask & EBT_ARP_OPCODE) &&
	    NF_INVF(info, EBT_ARP_OPCODE, info->opcode != ah->ar_op))
		वापस false;
	अगर ((info->biपंचांगask & EBT_ARP_HTYPE) &&
	    NF_INVF(info, EBT_ARP_HTYPE, info->htype != ah->ar_hrd))
		वापस false;
	अगर ((info->biपंचांगask & EBT_ARP_PTYPE) &&
	    NF_INVF(info, EBT_ARP_PTYPE, info->ptype != ah->ar_pro))
		वापस false;

	अगर (info->biपंचांगask & (EBT_ARP_SRC_IP | EBT_ARP_DST_IP | EBT_ARP_GRAT)) अणु
		स्थिर __be32 *sap, *dap;
		__be32 saddr, daddr;

		अगर (ah->ar_pln != माप(__be32) || ah->ar_pro != htons(ETH_P_IP))
			वापस false;
		sap = skb_header_poपूर्णांकer(skb, माप(काष्ठा arphdr) +
					ah->ar_hln, माप(saddr),
					&saddr);
		अगर (sap == शून्य)
			वापस false;
		dap = skb_header_poपूर्णांकer(skb, माप(काष्ठा arphdr) +
					2*ah->ar_hln+माप(saddr),
					माप(daddr), &daddr);
		अगर (dap == शून्य)
			वापस false;
		अगर ((info->biपंचांगask & EBT_ARP_SRC_IP) &&
		    NF_INVF(info, EBT_ARP_SRC_IP,
			    info->saddr != (*sap & info->smsk)))
			वापस false;
		अगर ((info->biपंचांगask & EBT_ARP_DST_IP) &&
		    NF_INVF(info, EBT_ARP_DST_IP,
			    info->daddr != (*dap & info->dmsk)))
			वापस false;
		अगर ((info->biपंचांगask & EBT_ARP_GRAT) &&
		    NF_INVF(info, EBT_ARP_GRAT, *dap != *sap))
			वापस false;
	पूर्ण

	अगर (info->biपंचांगask & (EBT_ARP_SRC_MAC | EBT_ARP_DST_MAC)) अणु
		स्थिर अचिन्हित अक्षर *mp;
		अचिन्हित अक्षर _mac[ETH_ALEN];

		अगर (ah->ar_hln != ETH_ALEN || ah->ar_hrd != htons(ARPHRD_ETHER))
			वापस false;
		अगर (info->biपंचांगask & EBT_ARP_SRC_MAC) अणु
			mp = skb_header_poपूर्णांकer(skb, माप(काष्ठा arphdr),
						माप(_mac), &_mac);
			अगर (mp == शून्य)
				वापस false;
			अगर (NF_INVF(info, EBT_ARP_SRC_MAC,
				    !ether_addr_equal_masked(mp, info->smaddr,
							     info->smmsk)))
				वापस false;
		पूर्ण

		अगर (info->biपंचांगask & EBT_ARP_DST_MAC) अणु
			mp = skb_header_poपूर्णांकer(skb, माप(काष्ठा arphdr) +
						ah->ar_hln + ah->ar_pln,
						माप(_mac), &_mac);
			अगर (mp == शून्य)
				वापस false;
			अगर (NF_INVF(info, EBT_ARP_DST_MAC,
				    !ether_addr_equal_masked(mp, info->dmaddr,
							     info->dmmsk)))
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक ebt_arp_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ebt_arp_info *info = par->matchinfo;
	स्थिर काष्ठा ebt_entry *e = par->entryinfo;

	अगर ((e->ethproto != htons(ETH_P_ARP) &&
	   e->ethproto != htons(ETH_P_RARP)) ||
	   e->invflags & EBT_IPROTO)
		वापस -EINVAL;
	अगर (info->biपंचांगask & ~EBT_ARP_MASK || info->invflags & ~EBT_ARP_MASK)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा xt_match ebt_arp_mt_reg __पढ़ो_mostly = अणु
	.name		= "arp",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_arp_mt,
	.checkentry	= ebt_arp_mt_check,
	.matchsize	= माप(काष्ठा ebt_arp_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_arp_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ebt_arp_mt_reg);
पूर्ण

अटल व्योम __निकास ebt_arp_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&ebt_arp_mt_reg);
पूर्ण

module_init(ebt_arp_init);
module_निकास(ebt_arp_fini);
MODULE_DESCRIPTION("Ebtables: ARP protocol packet match");
MODULE_LICENSE("GPL");
