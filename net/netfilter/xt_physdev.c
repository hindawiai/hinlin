<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match the bridge port in and
 * out device क्रम IP packets coming पूर्णांकo contact with a bridge. */

/* (C) 2001-2003 Bart De Schuymer <bdschuym@panकरोra.be>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/अगर.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter_bridge.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <uapi/linux/netfilter/xt_physdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bart De Schuymer <bdschuym@pandora.be>");
MODULE_DESCRIPTION("Xtables: Bridge physical device match");
MODULE_ALIAS("ipt_physdev");
MODULE_ALIAS("ip6t_physdev");


अटल bool
physdev_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_physdev_info *info = par->matchinfo;
	स्थिर काष्ठा net_device *physdev;
	अचिन्हित दीर्घ ret;
	स्थिर अक्षर *indev, *outdev;

	/* Not a bridged IP packet or no info available yet:
	 * LOCAL_OUT/mangle and LOCAL_OUT/nat करोn't know अगर
	 * the destination device will be a bridge. */
	अगर (!nf_bridge_info_exists(skb)) अणु
		/* Return MATCH अगर the invert flags of the used options are on */
		अगर ((info->biपंचांगask & XT_PHYSDEV_OP_BRIDGED) &&
		    !(info->invert & XT_PHYSDEV_OP_BRIDGED))
			वापस false;
		अगर ((info->biपंचांगask & XT_PHYSDEV_OP_ISIN) &&
		    !(info->invert & XT_PHYSDEV_OP_ISIN))
			वापस false;
		अगर ((info->biपंचांगask & XT_PHYSDEV_OP_ISOUT) &&
		    !(info->invert & XT_PHYSDEV_OP_ISOUT))
			वापस false;
		अगर ((info->biपंचांगask & XT_PHYSDEV_OP_IN) &&
		    !(info->invert & XT_PHYSDEV_OP_IN))
			वापस false;
		अगर ((info->biपंचांगask & XT_PHYSDEV_OP_OUT) &&
		    !(info->invert & XT_PHYSDEV_OP_OUT))
			वापस false;
		वापस true;
	पूर्ण

	physdev = nf_bridge_get_physoutdev(skb);
	outdev = physdev ? physdev->name : शून्य;

	/* This only makes sense in the FORWARD and POSTROUTING chains */
	अगर ((info->biपंचांगask & XT_PHYSDEV_OP_BRIDGED) &&
	    (!!outdev ^ !(info->invert & XT_PHYSDEV_OP_BRIDGED)))
		वापस false;

	physdev = nf_bridge_get_physindev(skb);
	indev = physdev ? physdev->name : शून्य;

	अगर ((info->biपंचांगask & XT_PHYSDEV_OP_ISIN &&
	    (!indev ^ !!(info->invert & XT_PHYSDEV_OP_ISIN))) ||
	    (info->biपंचांगask & XT_PHYSDEV_OP_ISOUT &&
	    (!outdev ^ !!(info->invert & XT_PHYSDEV_OP_ISOUT))))
		वापस false;

	अगर (!(info->biपंचांगask & XT_PHYSDEV_OP_IN))
		जाओ match_outdev;

	अगर (indev) अणु
		ret = अगरname_compare_aligned(indev, info->physindev,
					     info->in_mask);

		अगर (!ret ^ !(info->invert & XT_PHYSDEV_OP_IN))
			वापस false;
	पूर्ण

match_outdev:
	अगर (!(info->biपंचांगask & XT_PHYSDEV_OP_OUT))
		वापस true;

	अगर (!outdev)
		वापस false;

	ret = अगरname_compare_aligned(outdev, info->physoutdev, info->out_mask);

	वापस (!!ret ^ !(info->invert & XT_PHYSDEV_OP_OUT));
पूर्ण

अटल पूर्णांक physdev_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_physdev_info *info = par->matchinfo;
	अटल bool brnf_probed __पढ़ो_mostly;

	अगर (!(info->biपंचांगask & XT_PHYSDEV_OP_MASK) ||
	    info->biपंचांगask & ~XT_PHYSDEV_OP_MASK)
		वापस -EINVAL;
	अगर (info->biपंचांगask & (XT_PHYSDEV_OP_OUT | XT_PHYSDEV_OP_ISOUT) &&
	    (!(info->biपंचांगask & XT_PHYSDEV_OP_BRIDGED) ||
	     info->invert & XT_PHYSDEV_OP_BRIDGED) &&
	    par->hook_mask & (1 << NF_INET_LOCAL_OUT)) अणु
		pr_info_ratelimited("--physdev-out and --physdev-is-out only supported in the FORWARD and POSTROUTING chains with bridged traffic\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!brnf_probed) अणु
		brnf_probed = true;
		request_module("br_netfilter");
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_match physdev_mt_reg __पढ़ो_mostly = अणु
	.name       = "physdev",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.checkentry = physdev_mt_check,
	.match      = physdev_mt,
	.matchsize  = माप(काष्ठा xt_physdev_info),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init physdev_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&physdev_mt_reg);
पूर्ण

अटल व्योम __निकास physdev_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&physdev_mt_reg);
पूर्ण

module_init(physdev_mt_init);
module_निकास(physdev_mt_निकास);
