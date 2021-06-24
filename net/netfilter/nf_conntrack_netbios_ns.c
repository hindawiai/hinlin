<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      NetBIOS name service broadcast connection tracking helper
 *
 *      (c) 2005 Patrick McHardy <kaber@trash.net>
 */
/*
 *      This helper tracks locally originating NetBIOS name service
 *      requests by issuing permanent expectations (valid until
 *      timing out) matching all reply connections from the
 *      destination network. The only NetBIOS specअगरic thing is
 *      actually the port number.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/in.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>

#घोषणा NMBD_PORT	137

MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_DESCRIPTION("NetBIOS name service broadcast connection tracking helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ip_conntrack_netbios_ns");
MODULE_ALIAS_NFCT_HELPER("netbios_ns");

अटल अचिन्हित पूर्णांक समयout __पढ़ो_mostly = 3;
module_param(समयout, uपूर्णांक, 0400);
MODULE_PARM_DESC(समयout, "timeout for master connection/replies in seconds");

अटल काष्ठा nf_conntrack_expect_policy exp_policy = अणु
	.max_expected	= 1,
पूर्ण;

अटल पूर्णांक netbios_ns_help(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			   काष्ठा nf_conn *ct,
			   क्रमागत ip_conntrack_info ctinfo)
अणु
	वापस nf_conntrack_broadcast_help(skb, ct, ctinfo, समयout);
पूर्ण

अटल काष्ठा nf_conntrack_helper helper __पढ़ो_mostly = अणु
	.name			= "netbios-ns",
	.tuple.src.l3num	= NFPROTO_IPV4,
	.tuple.src.u.udp.port	= cpu_to_be16(NMBD_PORT),
	.tuple.dst.protonum	= IPPROTO_UDP,
	.me			= THIS_MODULE,
	.help			= netbios_ns_help,
	.expect_policy		= &exp_policy,
पूर्ण;

अटल पूर्णांक __init nf_conntrack_netbios_ns_init(व्योम)
अणु
	NF_CT_HELPER_BUILD_BUG_ON(0);

	exp_policy.समयout = समयout;
	वापस nf_conntrack_helper_रेजिस्टर(&helper);
पूर्ण

अटल व्योम __निकास nf_conntrack_netbios_ns_fini(व्योम)
अणु
	nf_conntrack_helper_unरेजिस्टर(&helper);
पूर्ण

module_init(nf_conntrack_netbios_ns_init);
module_निकास(nf_conntrack_netbios_ns_fini);
