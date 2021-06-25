<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* FTP extension क्रम TCP NAT alteration. */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/inet.h>
#समावेश <linux/tcp.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <linux/netfilter/nf_conntrack_ftp.h>

#घोषणा NAT_HELPER_NAME "ftp"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rusty Russell <rusty@rustcorp.com.au>");
MODULE_DESCRIPTION("ftp NAT helper");
MODULE_ALIAS_NF_NAT_HELPER(NAT_HELPER_NAME);

/* FIXME: Time out? --RR */

अटल काष्ठा nf_conntrack_nat_helper nat_helper_ftp =
	NF_CT_NAT_HELPER_INIT(NAT_HELPER_NAME);

अटल पूर्णांक nf_nat_ftp_fmt_cmd(काष्ठा nf_conn *ct, क्रमागत nf_ct_ftp_type type,
			      अक्षर *buffer, माप_प्रकार buflen,
			      जोड़ nf_inet_addr *addr, u16 port)
अणु
	चयन (type) अणु
	हाल NF_CT_FTP_PORT:
	हाल NF_CT_FTP_PASV:
		वापस snम_लिखो(buffer, buflen, "%u,%u,%u,%u,%u,%u",
				((अचिन्हित अक्षर *)&addr->ip)[0],
				((अचिन्हित अक्षर *)&addr->ip)[1],
				((अचिन्हित अक्षर *)&addr->ip)[2],
				((अचिन्हित अक्षर *)&addr->ip)[3],
				port >> 8,
				port & 0xFF);
	हाल NF_CT_FTP_EPRT:
		अगर (nf_ct_l3num(ct) == NFPROTO_IPV4)
			वापस snम_लिखो(buffer, buflen, "|1|%pI4|%u|",
					&addr->ip, port);
		अन्यथा
			वापस snम_लिखो(buffer, buflen, "|2|%pI6|%u|",
					&addr->ip6, port);
	हाल NF_CT_FTP_EPSV:
		वापस snम_लिखो(buffer, buflen, "|||%u|", port);
	पूर्ण

	वापस 0;
पूर्ण

/* So, this packet has hit the connection tracking matching code.
   Mangle it, and change the expectation to match the new version. */
अटल अचिन्हित पूर्णांक nf_nat_ftp(काष्ठा sk_buff *skb,
			       क्रमागत ip_conntrack_info ctinfo,
			       क्रमागत nf_ct_ftp_type type,
			       अचिन्हित पूर्णांक protoff,
			       अचिन्हित पूर्णांक matchoff,
			       अचिन्हित पूर्णांक matchlen,
			       काष्ठा nf_conntrack_expect *exp)
अणु
	जोड़ nf_inet_addr newaddr;
	u_पूर्णांक16_t port;
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	काष्ठा nf_conn *ct = exp->master;
	अक्षर buffer[माप("|1||65535|") + INET6_ADDRSTRLEN];
	अचिन्हित पूर्णांक buflen;

	pr_debug("type %i, off %u len %u\n", type, matchoff, matchlen);

	/* Connection will come from wherever this packet goes, hence !dir */
	newaddr = ct->tuplehash[!dir].tuple.dst.u3;
	exp->saved_proto.tcp.port = exp->tuple.dst.u.tcp.port;
	exp->dir = !dir;

	/* When you see the packet, we need to NAT it the same as the
	 * this one. */
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

	buflen = nf_nat_ftp_fmt_cmd(ct, type, buffer, माप(buffer),
				    &newaddr, port);
	अगर (!buflen)
		जाओ out;

	pr_debug("calling nf_nat_mangle_tcp_packet\n");

	अगर (!nf_nat_mangle_tcp_packet(skb, ct, ctinfo, protoff, matchoff,
				      matchlen, buffer, buflen))
		जाओ out;

	वापस NF_ACCEPT;

out:
	nf_ct_helper_log(skb, ct, "cannot mangle packet");
	nf_ct_unexpect_related(exp);
	वापस NF_DROP;
पूर्ण

अटल व्योम __निकास nf_nat_ftp_fini(व्योम)
अणु
	nf_nat_helper_unरेजिस्टर(&nat_helper_ftp);
	RCU_INIT_POINTER(nf_nat_ftp_hook, शून्य);
	synchronize_rcu();
पूर्ण

अटल पूर्णांक __init nf_nat_ftp_init(व्योम)
अणु
	BUG_ON(nf_nat_ftp_hook != शून्य);
	nf_nat_helper_रेजिस्टर(&nat_helper_ftp);
	RCU_INIT_POINTER(nf_nat_ftp_hook, nf_nat_ftp);
	वापस 0;
पूर्ण

/* Prior to 2.6.11, we had a ports param.  No दीर्घer, but करोn't अवरोध users. */
अटल पूर्णांक warn_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	pr_info("kernel >= 2.6.10 only uses 'ports' for conntrack modules\n");
	वापस 0;
पूर्ण
module_param_call(ports, warn_set, शून्य, शून्य, 0);

module_init(nf_nat_ftp_init);
module_निकास(nf_nat_ftp_fini);
