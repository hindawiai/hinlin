<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 802_3
 *
 * Author:
 * Chris Vitale csv@bluetail.com
 *
 * May 2003
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/skbuff.h>
#समावेश <uapi/linux/netfilter_bridge/ebt_802_3.h>

अटल काष्ठा ebt_802_3_hdr *ebt_802_3_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ebt_802_3_hdr *)skb_mac_header(skb);
पूर्ण

अटल bool
ebt_802_3_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_802_3_info *info = par->matchinfo;
	स्थिर काष्ठा ebt_802_3_hdr *hdr = ebt_802_3_hdr(skb);
	__be16 type = hdr->llc.ui.ctrl & IS_UI ? hdr->llc.ui.type : hdr->llc.ni.type;

	अगर (info->biपंचांगask & EBT_802_3_SAP) अणु
		अगर (NF_INVF(info, EBT_802_3_SAP, info->sap != hdr->llc.ui.ssap))
			वापस false;
		अगर (NF_INVF(info, EBT_802_3_SAP, info->sap != hdr->llc.ui.dsap))
			वापस false;
	पूर्ण

	अगर (info->biपंचांगask & EBT_802_3_TYPE) अणु
		अगर (!(hdr->llc.ui.dsap == CHECK_TYPE && hdr->llc.ui.ssap == CHECK_TYPE))
			वापस false;
		अगर (NF_INVF(info, EBT_802_3_TYPE, info->type != type))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक ebt_802_3_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ebt_802_3_info *info = par->matchinfo;

	अगर (info->biपंचांगask & ~EBT_802_3_MASK || info->invflags & ~EBT_802_3_MASK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा xt_match ebt_802_3_mt_reg __पढ़ो_mostly = अणु
	.name		= "802_3",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_802_3_mt,
	.checkentry	= ebt_802_3_mt_check,
	.matchsize	= माप(काष्ठा ebt_802_3_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_802_3_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ebt_802_3_mt_reg);
पूर्ण

अटल व्योम __निकास ebt_802_3_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&ebt_802_3_mt_reg);
पूर्ण

module_init(ebt_802_3_init);
module_निकास(ebt_802_3_fini);
MODULE_DESCRIPTION("Ebtables: DSAP/SSAP field and SNAP type matching");
MODULE_LICENSE("GPL");
