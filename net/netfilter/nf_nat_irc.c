<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* IRC extension क्रम TCP NAT alteration.
 *
 * (C) 2000-2001 by Harald Welte <laक्रमge@gnumonks.org>
 * (C) 2004 Rusty Russell <rusty@rustcorp.com.au> IBM Corporation
 * based on a copy of RR's ip_nat_ftp.c
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/tcp.h>
#समावेश <linux/kernel.h>

#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <linux/netfilter/nf_conntrack_irc.h>

#घोषणा NAT_HELPER_NAME "irc"

MODULE_AUTHOR("Harald Welte <laforge@gnumonks.org>");
MODULE_DESCRIPTION("IRC (DCC) NAT helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NF_NAT_HELPER(NAT_HELPER_NAME);

अटल काष्ठा nf_conntrack_nat_helper nat_helper_irc =
	NF_CT_NAT_HELPER_INIT(NAT_HELPER_NAME);

अटल अचिन्हित पूर्णांक help(काष्ठा sk_buff *skb,
			 क्रमागत ip_conntrack_info ctinfo,
			 अचिन्हित पूर्णांक protoff,
			 अचिन्हित पूर्णांक matchoff,
			 अचिन्हित पूर्णांक matchlen,
			 काष्ठा nf_conntrack_expect *exp)
अणु
	अक्षर buffer[माप("4294967296 65635")];
	काष्ठा nf_conn *ct = exp->master;
	जोड़ nf_inet_addr newaddr;
	u_पूर्णांक16_t port;

	/* Reply comes from server. */
	newaddr = ct->tuplehash[IP_CT_सूची_REPLY].tuple.dst.u3;

	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->dir = IP_CT_सूची_REPLY;
	exp->expectfn = nf_nat_follow_master;

	/* Try to get same port: अगर not, try to change it. */
	क्रम (port = ntohs(exp->saved_proto.tcp.port); port != 0; port++) अणु
		पूर्णांक ret;

		exp->tuple.dst.u.tcp.port = htons(port);
		ret = nf_ct_expect_related(exp, 0);
		अगर (ret == 0)
			अवरोध;
		अन्यथा अगर (ret != -EBUSY) अणु
			port = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (port == 0) अणु
		nf_ct_helper_log(skb, ct, "all ports in use");
		वापस NF_DROP;
	पूर्ण

	/* म_माप("\1DCC CHAT chat AAAAAAAA P\1\n")=27
	 * म_माप("\1DCC SCHAT chat AAAAAAAA P\1\n")=28
	 * म_माप("\1DCC SEND F AAAAAAAA P S\1\n")=26
	 * म_माप("\1DCC MOVE F AAAAAAAA P S\1\n")=26
	 * म_माप("\1DCC TSEND F AAAAAAAA P S\1\n")=27
	 *
	 * AAAAAAAAA: bound addr (1.0.0.0==16777216, min 8 digits,
	 *                        255.255.255.255==4294967296, 10 digits)
	 * P:         bound port (min 1 d, max 5d (65635))
	 * F:         filename   (min 1 d )
	 * S:         size       (min 1 d )
	 * 0x01, \न:  terminators
	 */
	/* AAA = "us", ie. where server normally talks to. */
	snम_लिखो(buffer, माप(buffer), "%u %u", ntohl(newaddr.ip), port);
	pr_debug("inserting '%s' == %pI4, port %u\n",
		 buffer, &newaddr.ip, port);

	अगर (!nf_nat_mangle_tcp_packet(skb, ct, ctinfo, protoff, matchoff,
				      matchlen, buffer, म_माप(buffer))) अणु
		nf_ct_helper_log(skb, ct, "cannot mangle packet");
		nf_ct_unexpect_related(exp);
		वापस NF_DROP;
	पूर्ण

	वापस NF_ACCEPT;
पूर्ण

अटल व्योम __निकास nf_nat_irc_fini(व्योम)
अणु
	nf_nat_helper_unरेजिस्टर(&nat_helper_irc);
	RCU_INIT_POINTER(nf_nat_irc_hook, शून्य);
	synchronize_rcu();
पूर्ण

अटल पूर्णांक __init nf_nat_irc_init(व्योम)
अणु
	BUG_ON(nf_nat_irc_hook != शून्य);
	nf_nat_helper_रेजिस्टर(&nat_helper_irc);
	RCU_INIT_POINTER(nf_nat_irc_hook, help);
	वापस 0;
पूर्ण

/* Prior to 2.6.11, we had a ports param.  No दीर्घer, but करोn't अवरोध users. */
अटल पूर्णांक warn_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	pr_info("kernel >= 2.6.10 only uses 'ports' for conntrack modules\n");
	वापस 0;
पूर्ण
module_param_call(ports, warn_set, शून्य, शून्य, 0);

module_init(nf_nat_irc_init);
module_निकास(nf_nat_irc_fini);
