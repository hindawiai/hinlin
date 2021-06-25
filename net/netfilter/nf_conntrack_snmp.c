<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      SNMP service broadcast connection tracking helper
 *
 *      (c) 2011 Jiri Olsa <jolsa@redhat.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/in.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <linux/netfilter/nf_conntrack_snmp.h>

#घोषणा SNMP_PORT	161

MODULE_AUTHOR("Jiri Olsa <jolsa@redhat.com>");
MODULE_DESCRIPTION("SNMP service broadcast connection tracking helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NFCT_HELPER("snmp");

अटल अचिन्हित पूर्णांक समयout __पढ़ो_mostly = 30;
module_param(समयout, uपूर्णांक, 0400);
MODULE_PARM_DESC(समयout, "timeout for master connection/replies in seconds");

पूर्णांक (*nf_nat_snmp_hook)(काष्ठा sk_buff *skb,
			अचिन्हित पूर्णांक protoff,
			काष्ठा nf_conn *ct,
			क्रमागत ip_conntrack_info ctinfo);
EXPORT_SYMBOL_GPL(nf_nat_snmp_hook);

अटल पूर्णांक snmp_conntrack_help(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			       काष्ठा nf_conn *ct,
			       क्रमागत ip_conntrack_info ctinfo)
अणु
	typeof(nf_nat_snmp_hook) nf_nat_snmp;

	nf_conntrack_broadcast_help(skb, ct, ctinfo, समयout);

	nf_nat_snmp = rcu_dereference(nf_nat_snmp_hook);
	अगर (nf_nat_snmp && ct->status & IPS_NAT_MASK)
		वापस nf_nat_snmp(skb, protoff, ct, ctinfo);

	वापस NF_ACCEPT;
पूर्ण

अटल काष्ठा nf_conntrack_expect_policy exp_policy = अणु
	.max_expected	= 1,
पूर्ण;

अटल काष्ठा nf_conntrack_helper helper __पढ़ो_mostly = अणु
	.name			= "snmp",
	.tuple.src.l3num	= NFPROTO_IPV4,
	.tuple.src.u.udp.port	= cpu_to_be16(SNMP_PORT),
	.tuple.dst.protonum	= IPPROTO_UDP,
	.me			= THIS_MODULE,
	.help			= snmp_conntrack_help,
	.expect_policy		= &exp_policy,
पूर्ण;

अटल पूर्णांक __init nf_conntrack_snmp_init(व्योम)
अणु
	exp_policy.समयout = समयout;
	वापस nf_conntrack_helper_रेजिस्टर(&helper);
पूर्ण

अटल व्योम __निकास nf_conntrack_snmp_fini(व्योम)
अणु
	nf_conntrack_helper_unरेजिस्टर(&helper);
पूर्ण

module_init(nf_conntrack_snmp_init);
module_निकास(nf_conntrack_snmp_fini);
