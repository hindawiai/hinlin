<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel module to match running CPU */

/*
 * Might be used to distribute connections on several daemons, अगर
 * RPS (Remote Packet Steering) is enabled or NIC is multiqueue capable,
 * each RX queue IRQ affined to one CPU (1:1 mapping)
 */

/* (C) 2010 Eric Dumazet
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter/xt_cpu.h>
#समावेश <linux/netfilter/x_tables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Eric Dumazet <eric.dumazet@gmail.com>");
MODULE_DESCRIPTION("Xtables: CPU match");
MODULE_ALIAS("ipt_cpu");
MODULE_ALIAS("ip6t_cpu");

अटल पूर्णांक cpu_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_cpu_info *info = par->matchinfo;

	अगर (info->invert & ~1)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल bool cpu_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_cpu_info *info = par->matchinfo;

	वापस (info->cpu == smp_processor_id()) ^ info->invert;
पूर्ण

अटल काष्ठा xt_match cpu_mt_reg __पढ़ो_mostly = अणु
	.name       = "cpu",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.checkentry = cpu_mt_check,
	.match      = cpu_mt,
	.matchsize  = माप(काष्ठा xt_cpu_info),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init cpu_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&cpu_mt_reg);
पूर्ण

अटल व्योम __निकास cpu_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&cpu_mt_reg);
पूर्ण

module_init(cpu_mt_init);
module_निकास(cpu_mt_निकास);
