<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ebt_nflog
 *
 *	Author:
 *	Peter Warasin <peter@endian.com>
 *
 *  February, 2008
 *
 * Based on:
 *  xt_NFLOG.c, (C) 2006 by Patrick McHardy <kaber@trash.net>
 *  ebt_ulog.c, (C) 2004 by Bart De Schuymer <bdschuym@panकरोra.be>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_nflog.h>
#समावेश <net/netfilter/nf_log.h>

अटल अचिन्हित पूर्णांक
ebt_nflog_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_nflog_info *info = par->targinfo;
	काष्ठा net *net = xt_net(par);
	काष्ठा nf_loginfo li;

	li.type = NF_LOG_TYPE_ULOG;
	li.u.ulog.copy_len = info->len;
	li.u.ulog.group = info->group;
	li.u.ulog.qthreshold = info->threshold;
	li.u.ulog.flags = 0;

	nf_log_packet(net, PF_BRIDGE, xt_hooknum(par), skb, xt_in(par),
		      xt_out(par), &li, "%s", info->prefix);
	वापस EBT_CONTINUE;
पूर्ण

अटल पूर्णांक ebt_nflog_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा ebt_nflog_info *info = par->targinfo;

	अगर (info->flags & ~EBT_NFLOG_MASK)
		वापस -EINVAL;
	info->prefix[EBT_NFLOG_PREFIX_SIZE - 1] = '\0';
	वापस 0;
पूर्ण

अटल काष्ठा xt_target ebt_nflog_tg_reg __पढ़ो_mostly = अणु
	.name       = "nflog",
	.revision   = 0,
	.family     = NFPROTO_BRIDGE,
	.target     = ebt_nflog_tg,
	.checkentry = ebt_nflog_tg_check,
	.tarमाला_लोize = माप(काष्ठा ebt_nflog_info),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_nflog_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&ebt_nflog_tg_reg);
पूर्ण

अटल व्योम __निकास ebt_nflog_fini(व्योम)
अणु
	xt_unरेजिस्टर_target(&ebt_nflog_tg_reg);
पूर्ण

module_init(ebt_nflog_init);
module_निकास(ebt_nflog_fini);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peter Warasin <peter@endian.com>");
MODULE_DESCRIPTION("ebtables NFLOG netfilter logging module");
