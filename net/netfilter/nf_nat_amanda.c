<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Amanda extension क्रम TCP NAT alteration.
 * (C) 2002 by Brian J. Murrell <netfilter@पूर्णांकerlinx.bc.ca>
 * based on a copy of HW's ip_nat_irc.c as well as other modules
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/udp.h>

#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <linux/netfilter/nf_conntrack_amanda.h>

#घोषणा NAT_HELPER_NAME "amanda"

MODULE_AUTHOR("Brian J. Murrell <netfilter@interlinx.bc.ca>");
MODULE_DESCRIPTION("Amanda NAT helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NF_NAT_HELPER(NAT_HELPER_NAME);

अटल काष्ठा nf_conntrack_nat_helper nat_helper_amanda =
	NF_CT_NAT_HELPER_INIT(NAT_HELPER_NAME);

अटल अचिन्हित पूर्णांक help(काष्ठा sk_buff *skb,
			 क्रमागत ip_conntrack_info ctinfo,
			 अचिन्हित पूर्णांक protoff,
			 अचिन्हित पूर्णांक matchoff,
			 अचिन्हित पूर्णांक matchlen,
			 काष्ठा nf_conntrack_expect *exp)
अणु
	अक्षर buffer[माप("65535")];
	u_पूर्णांक16_t port;

	/* Connection comes from client. */
	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->dir = IP_CT_सूची_ORIGINAL;

	/* When you see the packet, we need to NAT it the same as the
	 * this one (ie. same IP: it will be TCP and master is UDP). */
	exp->expectfn = nf_nat_follow_master;

	/* Try to get same port: अगर not, try to change it. */
	क्रम (port = ntohs(exp->saved_proto.tcp.port); port != 0; port++) अणु
		पूर्णांक res;

		exp->tuple.dst.u.tcp.port = htons(port);
		res = nf_ct_expect_related(exp, 0);
		अगर (res == 0)
			अवरोध;
		अन्यथा अगर (res != -EBUSY) अणु
			port = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (port == 0) अणु
		nf_ct_helper_log(skb, exp->master, "all ports in use");
		वापस NF_DROP;
	पूर्ण

	प्र_लिखो(buffer, "%u", port);
	अगर (!nf_nat_mangle_udp_packet(skb, exp->master, ctinfo,
				      protoff, matchoff, matchlen,
				      buffer, म_माप(buffer))) अणु
		nf_ct_helper_log(skb, exp->master, "cannot mangle packet");
		nf_ct_unexpect_related(exp);
		वापस NF_DROP;
	पूर्ण
	वापस NF_ACCEPT;
पूर्ण

अटल व्योम __निकास nf_nat_amanda_fini(व्योम)
अणु
	nf_nat_helper_unरेजिस्टर(&nat_helper_amanda);
	RCU_INIT_POINTER(nf_nat_amanda_hook, शून्य);
	synchronize_rcu();
पूर्ण

अटल पूर्णांक __init nf_nat_amanda_init(व्योम)
अणु
	BUG_ON(nf_nat_amanda_hook != शून्य);
	nf_nat_helper_रेजिस्टर(&nat_helper_amanda);
	RCU_INIT_POINTER(nf_nat_amanda_hook, help);
	वापस 0;
पूर्ण

module_init(nf_nat_amanda_init);
module_निकास(nf_nat_amanda_fini);
