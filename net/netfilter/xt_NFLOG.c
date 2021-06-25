<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2006 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_NFLOG.h>
#समावेश <net/netfilter/nf_log.h>

MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("Xtables: packet logging to netlink using NFLOG");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_NFLOG");
MODULE_ALIAS("ip6t_NFLOG");

अटल अचिन्हित पूर्णांक
nflog_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_nflog_info *info = par->targinfo;
	काष्ठा net *net = xt_net(par);
	काष्ठा nf_loginfo li;

	li.type		     = NF_LOG_TYPE_ULOG;
	li.u.ulog.copy_len   = info->len;
	li.u.ulog.group	     = info->group;
	li.u.ulog.qthreshold = info->threshold;
	li.u.ulog.flags	     = 0;

	अगर (info->flags & XT_NFLOG_F_COPY_LEN)
		li.u.ulog.flags |= NF_LOG_F_COPY_LEN;

	nf_log_packet(net, xt_family(par), xt_hooknum(par), skb, xt_in(par),
		      xt_out(par), &li, "%s", info->prefix);

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक nflog_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_nflog_info *info = par->targinfo;

	अगर (info->flags & ~XT_NFLOG_MASK)
		वापस -EINVAL;
	अगर (info->prefix[माप(info->prefix) - 1] != '\0')
		वापस -EINVAL;

	वापस nf_logger_find_get(par->family, NF_LOG_TYPE_ULOG);
पूर्ण

अटल व्योम nflog_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_logger_put(par->family, NF_LOG_TYPE_ULOG);
पूर्ण

अटल काष्ठा xt_target nflog_tg_reg __पढ़ो_mostly = अणु
	.name       = "NFLOG",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.checkentry = nflog_tg_check,
	.destroy    = nflog_tg_destroy,
	.target     = nflog_tg,
	.tarमाला_लोize = माप(काष्ठा xt_nflog_info),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nflog_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&nflog_tg_reg);
पूर्ण

अटल व्योम __निकास nflog_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_target(&nflog_tg_reg);
पूर्ण

module_init(nflog_tg_init);
module_निकास(nflog_tg_निकास);
MODULE_SOFTDEP("pre: nfnetlink_log");
