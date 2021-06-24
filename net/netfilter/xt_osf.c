<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2003+ Evgeniy Polyakov <zbr@ioremap.net>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <linux/capability.h>
#समावेश <linux/अगर.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/tcp.h>

#समावेश <net/ip.h>
#समावेश <net/tcp.h>

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/netfilter/nf_log.h>
#समावेश <linux/netfilter/xt_osf.h>

अटल bool
xt_osf_match_packet(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *p)
अणु
	वापस nf_osf_match(skb, xt_family(p), xt_hooknum(p), xt_in(p),
			    xt_out(p), p->matchinfo, xt_net(p), nf_osf_fingers);
पूर्ण

अटल काष्ठा xt_match xt_osf_match = अणु
	.name 		= "osf",
	.revision	= 0,
	.family		= NFPROTO_IPV4,
	.proto		= IPPROTO_TCP,
	.hooks      	= (1 << NF_INET_LOCAL_IN) |
				(1 << NF_INET_PRE_ROUTING) |
				(1 << NF_INET_FORWARD),
	.match 		= xt_osf_match_packet,
	.matchsize	= माप(काष्ठा xt_osf_info),
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init xt_osf_init(व्योम)
अणु
	पूर्णांक err;

	err = xt_रेजिस्टर_match(&xt_osf_match);
	अगर (err) अणु
		pr_err("Failed to register OS fingerprint "
		       "matching module (%d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास xt_osf_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&xt_osf_match);
पूर्ण

module_init(xt_osf_init);
module_निकास(xt_osf_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Evgeniy Polyakov <zbr@ioremap.net>");
MODULE_DESCRIPTION("Passive OS fingerprint matching.");
MODULE_ALIAS("ipt_osf");
MODULE_ALIAS("ip6t_osf");
MODULE_ALIAS_NFNL_SUBSYS(NFNL_SUBSYS_OSF);
