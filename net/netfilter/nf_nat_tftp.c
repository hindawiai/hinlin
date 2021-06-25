<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 2001-2002 Magnus Boden <mb@ozaba.mine.nu>
 */

#समावेश <linux/module.h>
#समावेश <linux/udp.h>

#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <linux/netfilter/nf_conntrack_tftp.h>

#घोषणा NAT_HELPER_NAME "tftp"

MODULE_AUTHOR("Magnus Boden <mb@ozaba.mine.nu>");
MODULE_DESCRIPTION("TFTP NAT helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NF_NAT_HELPER(NAT_HELPER_NAME);

अटल काष्ठा nf_conntrack_nat_helper nat_helper_tftp =
	NF_CT_NAT_HELPER_INIT(NAT_HELPER_NAME);

अटल अचिन्हित पूर्णांक help(काष्ठा sk_buff *skb,
			 क्रमागत ip_conntrack_info ctinfo,
			 काष्ठा nf_conntrack_expect *exp)
अणु
	स्थिर काष्ठा nf_conn *ct = exp->master;

	exp->saved_proto.udp.port
		= ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.u.udp.port;
	exp->dir = IP_CT_सूची_REPLY;
	exp->expectfn = nf_nat_follow_master;
	अगर (nf_ct_expect_related(exp, 0) != 0) अणु
		nf_ct_helper_log(skb, exp->master, "cannot add expectation");
		वापस NF_DROP;
	पूर्ण
	वापस NF_ACCEPT;
पूर्ण

अटल व्योम __निकास nf_nat_tftp_fini(व्योम)
अणु
	nf_nat_helper_unरेजिस्टर(&nat_helper_tftp);
	RCU_INIT_POINTER(nf_nat_tftp_hook, शून्य);
	synchronize_rcu();
पूर्ण

अटल पूर्णांक __init nf_nat_tftp_init(व्योम)
अणु
	BUG_ON(nf_nat_tftp_hook != शून्य);
	nf_nat_helper_रेजिस्टर(&nat_helper_tftp);
	RCU_INIT_POINTER(nf_nat_tftp_hook, help);
	वापस 0;
पूर्ण

module_init(nf_nat_tftp_init);
module_निकास(nf_nat_tftp_fini);
