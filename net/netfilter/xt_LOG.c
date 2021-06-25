<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is a module which is used क्रम logging packets.
 */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/icmp.h>
#समावेश <net/udp.h>
#समावेश <net/tcp.h>
#समावेश <net/route.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_LOG.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <net/netfilter/nf_log.h>

अटल अचिन्हित पूर्णांक
log_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_log_info *loginfo = par->targinfo;
	काष्ठा net *net = xt_net(par);
	काष्ठा nf_loginfo li;

	li.type = NF_LOG_TYPE_LOG;
	li.u.log.level = loginfo->level;
	li.u.log.logflags = loginfo->logflags;

	nf_log_packet(net, xt_family(par), xt_hooknum(par), skb, xt_in(par),
		      xt_out(par), &li, "%s", loginfo->prefix);
	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक log_tg_check(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_log_info *loginfo = par->targinfo;

	अगर (par->family != NFPROTO_IPV4 && par->family != NFPROTO_IPV6)
		वापस -EINVAL;

	अगर (loginfo->level >= 8) अणु
		pr_debug("level %u >= 8\n", loginfo->level);
		वापस -EINVAL;
	पूर्ण

	अगर (loginfo->prefix[माप(loginfo->prefix)-1] != '\0') अणु
		pr_debug("prefix is not null-terminated\n");
		वापस -EINVAL;
	पूर्ण

	वापस nf_logger_find_get(par->family, NF_LOG_TYPE_LOG);
पूर्ण

अटल व्योम log_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_logger_put(par->family, NF_LOG_TYPE_LOG);
पूर्ण

अटल काष्ठा xt_target log_tg_regs[] __पढ़ो_mostly = अणु
	अणु
		.name		= "LOG",
		.family		= NFPROTO_IPV4,
		.target		= log_tg,
		.tarमाला_लोize	= माप(काष्ठा xt_log_info),
		.checkentry	= log_tg_check,
		.destroy	= log_tg_destroy,
		.me		= THIS_MODULE,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IP6_NF_IPTABLES)
	अणु
		.name		= "LOG",
		.family		= NFPROTO_IPV6,
		.target		= log_tg,
		.tarमाला_लोize	= माप(काष्ठा xt_log_info),
		.checkentry	= log_tg_check,
		.destroy	= log_tg_destroy,
		.me		= THIS_MODULE,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init log_tg_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(log_tg_regs, ARRAY_SIZE(log_tg_regs));
पूर्ण

अटल व्योम __निकास log_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(log_tg_regs, ARRAY_SIZE(log_tg_regs));
पूर्ण

module_init(log_tg_init);
module_निकास(log_tg_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_AUTHOR("Jan Rekorajski <baggins@pld.org.pl>");
MODULE_DESCRIPTION("Xtables: IPv4/IPv6 packet logging");
MODULE_ALIAS("ipt_LOG");
MODULE_ALIAS("ip6t_LOG");
MODULE_SOFTDEP("pre: nf_log_syslog");
