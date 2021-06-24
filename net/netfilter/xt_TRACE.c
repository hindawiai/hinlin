<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* This is a module which is used to mark packets क्रम tracing.
 */
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/netfilter/nf_log.h>

MODULE_DESCRIPTION("Xtables: packet flow tracing");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_TRACE");
MODULE_ALIAS("ip6t_TRACE");

अटल पूर्णांक trace_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	वापस nf_logger_find_get(par->family, NF_LOG_TYPE_LOG);
पूर्ण

अटल व्योम trace_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_logger_put(par->family, NF_LOG_TYPE_LOG);
पूर्ण

अटल अचिन्हित पूर्णांक
trace_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	skb->nf_trace = 1;
	वापस XT_CONTINUE;
पूर्ण

अटल काष्ठा xt_target trace_tg_reg __पढ़ो_mostly = अणु
	.name		= "TRACE",
	.revision	= 0,
	.family		= NFPROTO_UNSPEC,
	.table		= "raw",
	.target		= trace_tg,
	.checkentry	= trace_tg_check,
	.destroy	= trace_tg_destroy,
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init trace_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_target(&trace_tg_reg);
पूर्ण

अटल व्योम __निकास trace_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_target(&trace_tg_reg);
पूर्ण

module_init(trace_tg_init);
module_निकास(trace_tg_निकास);
MODULE_SOFTDEP("pre: nf_log_syslog");
