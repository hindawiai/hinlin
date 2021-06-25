<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* iptables module क्रम the packet checksum mangling
 *
 * (C) 2002 by Harald Welte <laक्रमge@netfilter.org>
 * (C) 2010 Red Hat, Inc.
 *
 * Author: Michael S. Tsirkin <mst@redhat.com>
*/
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_CHECKSUM.h>

#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael S. Tsirkin <mst@redhat.com>");
MODULE_DESCRIPTION("Xtables: checksum modification");
MODULE_ALIAS("ipt_CHECKSUM");
MODULE_ALIAS("ip6t_CHECKSUM");

अटल अचिन्हित पूर्णांक
checksum_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	अगर (skb->ip_summed == CHECKSUM_PARTIAL && !skb_is_gso(skb))
		skb_checksum_help(skb);

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक checksum_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_CHECKSUM_info *einfo = par->targinfo;
	स्थिर काष्ठा ip6t_ip6 *i6 = par->entryinfo;
	स्थिर काष्ठा ipt_ip *i4 = par->entryinfo;

	अगर (einfo->operation & ~XT_CHECKSUM_OP_FILL) अणु
		pr_info_ratelimited("unsupported CHECKSUM operation %x\n",
				    einfo->operation);
		वापस -EINVAL;
	पूर्ण
	अगर (!einfo->operation)
		वापस -EINVAL;

	चयन (par->family) अणु
	हाल NFPROTO_IPV4:
		अगर (i4->proto == IPPROTO_UDP &&
		    (i4->invflags & XT_INV_PROTO) == 0)
			वापस 0;
		अवरोध;
	हाल NFPROTO_IPV6:
		अगर ((i6->flags & IP6T_F_PROTO) &&
		    i6->proto == IPPROTO_UDP &&
		    (i6->invflags & XT_INV_PROTO) == 0)
			वापस 0;
		अवरोध;
	पूर्ण

	pr_warn_once("CHECKSUM should be avoided.  If really needed, restrict with \"-p udp\" and only use in OUTPUT\n");
	वापस 0;
पूर्ण

अटल काष्ठा xt_target checksum_tg_reg __पढ़ो_mostly = अणु
	.name		= "CHECKSUM",
	.family		= NFPROTO_UNSPEC,
	.target		= checksum_tg,
	.tarमाला_लोize	= माप(काष्ठा xt_CHECKSUM_info),
	.table		= "mangle",
	.checkentry	= checksum_tg_check,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init checksum_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&checksum_tg_reg);
पूर्ण

अटल व्योम __निकास checksum_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_target(&checksum_tg_reg);
पूर्ण

module_init(checksum_tg_init);
module_निकास(checksum_tg_निकास);
