<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This module is used to copy security markings from packets
 * to connections, and restore security markings from connections
 * back to packets.  This would normally be perक्रमmed in conjunction
 * with the SECMARK target and state match.
 *
 * Based somewhat on CONNMARK:
 *   Copyright (C) 2002,2004 MARA Systems AB <https://www.maraप्रणालीs.com>
 *    by Henrik Nordstrom <hno@maraप्रणालीs.com>
 *
 * (C) 2006,2008 Red Hat, Inc., James Morris <jmorris@redhat.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_CONNSECMARK.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Morris <jmorris@redhat.com>");
MODULE_DESCRIPTION("Xtables: target for copying between connection and security mark");
MODULE_ALIAS("ipt_CONNSECMARK");
MODULE_ALIAS("ip6t_CONNSECMARK");

/*
 * If the packet has a security mark and the connection करोes not, copy
 * the security mark from the packet to the connection.
 */
अटल व्योम secmark_save(स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb->secmark) अणु
		काष्ठा nf_conn *ct;
		क्रमागत ip_conntrack_info ctinfo;

		ct = nf_ct_get(skb, &ctinfo);
		अगर (ct && !ct->secmark) अणु
			ct->secmark = skb->secmark;
			nf_conntrack_event_cache(IPCT_SECMARK, ct);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * If packet has no security mark, and the connection करोes, restore the
 * security mark from the connection to the packet.
 */
अटल व्योम secmark_restore(काष्ठा sk_buff *skb)
अणु
	अगर (!skb->secmark) अणु
		स्थिर काष्ठा nf_conn *ct;
		क्रमागत ip_conntrack_info ctinfo;

		ct = nf_ct_get(skb, &ctinfo);
		अगर (ct && ct->secmark)
			skb->secmark = ct->secmark;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक
connsecmark_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_connsecmark_target_info *info = par->targinfo;

	चयन (info->mode) अणु
	हाल CONNSECMARK_SAVE:
		secmark_save(skb);
		अवरोध;

	हाल CONNSECMARK_RESTORE:
		secmark_restore(skb);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक connsecmark_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_connsecmark_target_info *info = par->targinfo;
	पूर्णांक ret;

	अगर (म_भेद(par->table, "mangle") != 0 &&
	    म_भेद(par->table, "security") != 0) अणु
		pr_info_ratelimited("only valid in \'mangle\' or \'security\' table, not \'%s\'\n",
				    par->table);
		वापस -EINVAL;
	पूर्ण

	चयन (info->mode) अणु
	हाल CONNSECMARK_SAVE:
	हाल CONNSECMARK_RESTORE:
		अवरोध;

	शेष:
		pr_info_ratelimited("invalid mode: %hu\n", info->mode);
		वापस -EINVAL;
	पूर्ण

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0)
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
	वापस ret;
पूर्ण

अटल व्योम connsecmark_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल काष्ठा xt_target connsecmark_tg_reg __पढ़ो_mostly = अणु
	.name       = "CONNSECMARK",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.checkentry = connsecmark_tg_check,
	.destroy    = connsecmark_tg_destroy,
	.target     = connsecmark_tg,
	.tarमाला_लोize = माप(काष्ठा xt_connsecmark_target_info),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init connsecmark_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&connsecmark_tg_reg);
पूर्ण

अटल व्योम __निकास connsecmark_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_target(&connsecmark_tg_reg);
पूर्ण

module_init(connsecmark_tg_init);
module_निकास(connsecmark_tg_निकास);
