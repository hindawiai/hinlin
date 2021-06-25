<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_arpreply
 *
 *	Authors:
 *	Grzegorz Borowiak <grzes@gnu.univ.gda.pl>
 *	Bart De Schuymer <bdschuym@panकरोra.be>
 *
 *  August, 2003
 *
 */
#समावेश <linux/अगर_arp.h>
#समावेश <net/arp.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_arpreply.h>

अटल अचिन्हित पूर्णांक
ebt_arpreply_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_arpreply_info *info = par->targinfo;
	स्थिर __be32 *siptr, *diptr;
	__be32 _sip, _dip;
	स्थिर काष्ठा arphdr *ap;
	काष्ठा arphdr _ah;
	स्थिर अचिन्हित अक्षर *shp;
	अचिन्हित अक्षर _sha[ETH_ALEN];

	ap = skb_header_poपूर्णांकer(skb, 0, माप(_ah), &_ah);
	अगर (ap == शून्य)
		वापस EBT_DROP;

	अगर (ap->ar_op != htons(ARPOP_REQUEST) ||
	    ap->ar_hln != ETH_ALEN ||
	    ap->ar_pro != htons(ETH_P_IP) ||
	    ap->ar_pln != 4)
		वापस EBT_CONTINUE;

	shp = skb_header_poपूर्णांकer(skb, माप(_ah), ETH_ALEN, &_sha);
	अगर (shp == शून्य)
		वापस EBT_DROP;

	siptr = skb_header_poपूर्णांकer(skb, माप(_ah) + ETH_ALEN,
				   माप(_sip), &_sip);
	अगर (siptr == शून्य)
		वापस EBT_DROP;

	diptr = skb_header_poपूर्णांकer(skb,
				   माप(_ah) + 2 * ETH_ALEN + माप(_sip),
				   माप(_dip), &_dip);
	अगर (diptr == शून्य)
		वापस EBT_DROP;

	arp_send(ARPOP_REPLY, ETH_P_ARP, *siptr,
		 (काष्ठा net_device *)xt_in(par),
		 *diptr, shp, info->mac, shp);

	वापस info->target;
पूर्ण

अटल पूर्णांक ebt_arpreply_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा ebt_arpreply_info *info = par->targinfo;
	स्थिर काष्ठा ebt_entry *e = par->entryinfo;

	अगर (BASE_CHAIN && info->target == EBT_RETURN)
		वापस -EINVAL;
	अगर (e->ethproto != htons(ETH_P_ARP) ||
	    e->invflags & EBT_IPROTO)
		वापस -EINVAL;
	अगर (ebt_invalid_target(info->target))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा xt_target ebt_arpreply_tg_reg __पढ़ो_mostly = अणु
	.name		= "arpreply",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.table		= "nat",
	.hooks		= (1 << NF_BR_NUMHOOKS) | (1 << NF_BR_PRE_ROUTING),
	.target		= ebt_arpreply_tg,
	.checkentry	= ebt_arpreply_tg_check,
	.tarमाला_लोize	= माप(काष्ठा ebt_arpreply_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_arpreply_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&ebt_arpreply_tg_reg);
पूर्ण

अटल व्योम __निकास ebt_arpreply_fini(व्योम)
अणु
	xt_unरेजिस्टर_target(&ebt_arpreply_tg_reg);
पूर्ण

module_init(ebt_arpreply_init);
module_निकास(ebt_arpreply_fini);
MODULE_DESCRIPTION("Ebtables: ARP reply target");
MODULE_LICENSE("GPL");
