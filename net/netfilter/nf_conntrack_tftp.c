<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 2001-2002 Magnus Boden <mb@ozaba.mine.nu>
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/in.h>
#समावेश <linux/udp.h>
#समावेश <linux/netfilter.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <linux/netfilter/nf_conntrack_tftp.h>

#घोषणा HELPER_NAME "tftp"

MODULE_AUTHOR("Magnus Boden <mb@ozaba.mine.nu>");
MODULE_DESCRIPTION("TFTP connection tracking helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ip_conntrack_tftp");
MODULE_ALIAS_NFCT_HELPER(HELPER_NAME);

#घोषणा MAX_PORTS 8
अटल अचिन्हित लघु ports[MAX_PORTS];
अटल अचिन्हित पूर्णांक ports_c;
module_param_array(ports, uलघु, &ports_c, 0400);
MODULE_PARM_DESC(ports, "Port numbers of TFTP servers");

अचिन्हित पूर्णांक (*nf_nat_tftp_hook)(काष्ठा sk_buff *skb,
				 क्रमागत ip_conntrack_info ctinfo,
				 काष्ठा nf_conntrack_expect *exp) __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_nat_tftp_hook);

अटल पूर्णांक tftp_help(काष्ठा sk_buff *skb,
		     अचिन्हित पूर्णांक protoff,
		     काष्ठा nf_conn *ct,
		     क्रमागत ip_conntrack_info ctinfo)
अणु
	स्थिर काष्ठा tftphdr *tfh;
	काष्ठा tftphdr _tftph;
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conntrack_tuple *tuple;
	अचिन्हित पूर्णांक ret = NF_ACCEPT;
	typeof(nf_nat_tftp_hook) nf_nat_tftp;

	tfh = skb_header_poपूर्णांकer(skb, protoff + माप(काष्ठा udphdr),
				 माप(_tftph), &_tftph);
	अगर (tfh == शून्य)
		वापस NF_ACCEPT;

	चयन (ntohs(tfh->opcode)) अणु
	हाल TFTP_OPCODE_READ:
	हाल TFTP_OPCODE_WRITE:
		/* RRQ and WRQ works the same way */
		nf_ct_dump_tuple(&ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple);
		nf_ct_dump_tuple(&ct->tuplehash[IP_CT_सूची_REPLY].tuple);

		exp = nf_ct_expect_alloc(ct);
		अगर (exp == शून्य) अणु
			nf_ct_helper_log(skb, ct, "cannot alloc expectation");
			वापस NF_DROP;
		पूर्ण
		tuple = &ct->tuplehash[IP_CT_सूची_REPLY].tuple;
		nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT,
				  nf_ct_l3num(ct),
				  &tuple->src.u3, &tuple->dst.u3,
				  IPPROTO_UDP, शून्य, &tuple->dst.u.udp.port);

		pr_debug("expect: ");
		nf_ct_dump_tuple(&exp->tuple);

		nf_nat_tftp = rcu_dereference(nf_nat_tftp_hook);
		अगर (nf_nat_tftp && ct->status & IPS_NAT_MASK)
			ret = nf_nat_tftp(skb, ctinfo, exp);
		अन्यथा अगर (nf_ct_expect_related(exp, 0) != 0) अणु
			nf_ct_helper_log(skb, ct, "cannot add expectation");
			ret = NF_DROP;
		पूर्ण
		nf_ct_expect_put(exp);
		अवरोध;
	हाल TFTP_OPCODE_DATA:
	हाल TFTP_OPCODE_ACK:
		pr_debug("Data/ACK opcode\n");
		अवरोध;
	हाल TFTP_OPCODE_ERROR:
		pr_debug("Error opcode\n");
		अवरोध;
	शेष:
		pr_debug("Unknown opcode\n");
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा nf_conntrack_helper tftp[MAX_PORTS * 2] __पढ़ो_mostly;

अटल स्थिर काष्ठा nf_conntrack_expect_policy tftp_exp_policy = अणु
	.max_expected	= 1,
	.समयout	= 5 * 60,
पूर्ण;

अटल व्योम __निकास nf_conntrack_tftp_fini(व्योम)
अणु
	nf_conntrack_helpers_unरेजिस्टर(tftp, ports_c * 2);
पूर्ण

अटल पूर्णांक __init nf_conntrack_tftp_init(व्योम)
अणु
	पूर्णांक i, ret;

	NF_CT_HELPER_BUILD_BUG_ON(0);

	अगर (ports_c == 0)
		ports[ports_c++] = TFTP_PORT;

	क्रम (i = 0; i < ports_c; i++) अणु
		nf_ct_helper_init(&tftp[2 * i], AF_INET, IPPROTO_UDP,
				  HELPER_NAME, TFTP_PORT, ports[i], i,
				  &tftp_exp_policy, 0, tftp_help, शून्य,
				  THIS_MODULE);
		nf_ct_helper_init(&tftp[2 * i + 1], AF_INET6, IPPROTO_UDP,
				  HELPER_NAME, TFTP_PORT, ports[i], i,
				  &tftp_exp_policy, 0, tftp_help, शून्य,
				  THIS_MODULE);
	पूर्ण

	ret = nf_conntrack_helpers_रेजिस्टर(tftp, ports_c * 2);
	अगर (ret < 0) अणु
		pr_err("failed to register helpers\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

module_init(nf_conntrack_tftp_init);
module_निकास(nf_conntrack_tftp_fini);
