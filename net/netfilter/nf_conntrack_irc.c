<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* IRC extension क्रम IP connection tracking, Version 1.21
 * (C) 2000-2002 by Harald Welte <laक्रमge@gnumonks.org>
 * based on RR's ip_conntrack_ftp.c
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/slab.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <linux/netfilter/nf_conntrack_irc.h>

#घोषणा MAX_PORTS 8
अटल अचिन्हित लघु ports[MAX_PORTS];
अटल अचिन्हित पूर्णांक ports_c;
अटल अचिन्हित पूर्णांक max_dcc_channels = 8;
अटल अचिन्हित पूर्णांक dcc_समयout __पढ़ो_mostly = 300;
/* This is slow, but it's simple. --RR */
अटल अक्षर *irc_buffer;
अटल DEFINE_SPINLOCK(irc_buffer_lock);

अचिन्हित पूर्णांक (*nf_nat_irc_hook)(काष्ठा sk_buff *skb,
				क्रमागत ip_conntrack_info ctinfo,
				अचिन्हित पूर्णांक protoff,
				अचिन्हित पूर्णांक matchoff,
				अचिन्हित पूर्णांक matchlen,
				काष्ठा nf_conntrack_expect *exp) __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_nat_irc_hook);

#घोषणा HELPER_NAME "irc"

MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("IRC (DCC) connection tracking helper");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ip_conntrack_irc");
MODULE_ALIAS_NFCT_HELPER(HELPER_NAME);

module_param_array(ports, uलघु, &ports_c, 0400);
MODULE_PARM_DESC(ports, "port numbers of IRC servers");
module_param(max_dcc_channels, uपूर्णांक, 0400);
MODULE_PARM_DESC(max_dcc_channels, "max number of expected DCC channels per "
				   "IRC session");
module_param(dcc_समयout, uपूर्णांक, 0400);
MODULE_PARM_DESC(dcc_समयout, "timeout on for unestablished DCC channels");

अटल स्थिर अक्षर *स्थिर dccprotos[] = अणु
	"SEND ", "CHAT ", "MOVE ", "TSEND ", "SCHAT "
पूर्ण;

#घोषणा MINMATCHLEN	5

/* tries to get the ip_addr and port out of a dcc command
 * वापस value: -1 on failure, 0 on success
 *	data		poपूर्णांकer to first byte of DCC command data
 *	data_end	poपूर्णांकer to last byte of dcc command data
 *	ip		वापसs parsed ip of dcc command
 *	port		वापसs parsed port of dcc command
 *	ad_beg_p	वापसs poपूर्णांकer to first byte of addr data
 *	ad_end_p	वापसs poपूर्णांकer to last byte of addr data
 */
अटल पूर्णांक parse_dcc(अक्षर *data, स्थिर अक्षर *data_end, __be32 *ip,
		     u_पूर्णांक16_t *port, अक्षर **ad_beg_p, अक्षर **ad_end_p)
अणु
	अक्षर *पंचांगp;

	/* at least 12: "AAAAAAAA P\1\n" */
	जबतक (*data++ != ' ')
		अगर (data > data_end - 12)
			वापस -1;

	/* Make sure we have a newline अक्षरacter within the packet boundaries
	 * because simple_म_से_अदीर्घ parses until the first invalid अक्षरacter. */
	क्रम (पंचांगp = data; पंचांगp <= data_end; पंचांगp++)
		अगर (*पंचांगp == '\n')
			अवरोध;
	अगर (पंचांगp > data_end || *पंचांगp != '\n')
		वापस -1;

	*ad_beg_p = data;
	*ip = cpu_to_be32(simple_म_से_अदीर्घ(data, &data, 10));

	/* skip blanks between ip and port */
	जबतक (*data == ' ') अणु
		अगर (data >= data_end)
			वापस -1;
		data++;
	पूर्ण

	*port = simple_म_से_अदीर्घ(data, &data, 10);
	*ad_end_p = data;

	वापस 0;
पूर्ण

अटल पूर्णांक help(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo)
अणु
	अचिन्हित पूर्णांक dataoff;
	स्थिर काष्ठा iphdr *iph;
	स्थिर काष्ठा tcphdr *th;
	काष्ठा tcphdr _tcph;
	स्थिर अक्षर *data_limit;
	अक्षर *data, *ib_ptr;
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conntrack_tuple *tuple;
	__be32 dcc_ip;
	u_पूर्णांक16_t dcc_port;
	__be16 port;
	पूर्णांक i, ret = NF_ACCEPT;
	अक्षर *addr_beg_p, *addr_end_p;
	typeof(nf_nat_irc_hook) nf_nat_irc;

	/* If packet is coming from IRC server */
	अगर (dir == IP_CT_सूची_REPLY)
		वापस NF_ACCEPT;

	/* Until there's been traffic both ways, don't look in packets. */
	अगर (ctinfo != IP_CT_ESTABLISHED && ctinfo != IP_CT_ESTABLISHED_REPLY)
		वापस NF_ACCEPT;

	/* Not a full tcp header? */
	th = skb_header_poपूर्णांकer(skb, protoff, माप(_tcph), &_tcph);
	अगर (th == शून्य)
		वापस NF_ACCEPT;

	/* No data? */
	dataoff = protoff + th->करोff*4;
	अगर (dataoff >= skb->len)
		वापस NF_ACCEPT;

	spin_lock_bh(&irc_buffer_lock);
	ib_ptr = skb_header_poपूर्णांकer(skb, dataoff, skb->len - dataoff,
				    irc_buffer);
	अगर (!ib_ptr) अणु
		spin_unlock_bh(&irc_buffer_lock);
		वापस NF_ACCEPT;
	पूर्ण

	data = ib_ptr;
	data_limit = ib_ptr + skb->len - dataoff;

	/* म_माप("\1DCC SENT t AAAAAAAA P\1\n")=24
	 * 5+MINMATCHLEN+म_माप("t AAAAAAAA P\1\n")=14 */
	जबतक (data < data_limit - (19 + MINMATCHLEN)) अणु
		अगर (स_भेद(data, "\1DCC ", 5)) अणु
			data++;
			जारी;
		पूर्ण
		data += 5;
		/* we have at least (19+MINMATCHLEN)-5 bytes valid data left */

		iph = ip_hdr(skb);
		pr_debug("DCC found in master %pI4:%u %pI4:%u\n",
			 &iph->saddr, ntohs(th->source),
			 &iph->daddr, ntohs(th->dest));

		क्रम (i = 0; i < ARRAY_SIZE(dccprotos); i++) अणु
			अगर (स_भेद(data, dccprotos[i], म_माप(dccprotos[i]))) अणु
				/* no match */
				जारी;
			पूर्ण
			data += म_माप(dccprotos[i]);
			pr_debug("DCC %s detected\n", dccprotos[i]);

			/* we have at least
			 * (19+MINMATCHLEN)-5-dccprotos[i].matchlen bytes valid
			 * data left (== 14/13 bytes) */
			अगर (parse_dcc(data, data_limit, &dcc_ip,
				       &dcc_port, &addr_beg_p, &addr_end_p)) अणु
				pr_debug("unable to parse dcc command\n");
				जारी;
			पूर्ण

			pr_debug("DCC bound ip/port: %pI4:%u\n",
				 &dcc_ip, dcc_port);

			/* dcc_ip can be the पूर्णांकernal OR बाह्यal (NAT'ed) IP */
			tuple = &ct->tuplehash[dir].tuple;
			अगर (tuple->src.u3.ip != dcc_ip &&
			    tuple->dst.u3.ip != dcc_ip) अणु
				net_warn_ratelimited("Forged DCC command from %pI4: %pI4:%u\n",
						     &tuple->src.u3.ip,
						     &dcc_ip, dcc_port);
				जारी;
			पूर्ण

			exp = nf_ct_expect_alloc(ct);
			अगर (exp == शून्य) अणु
				nf_ct_helper_log(skb, ct,
						 "cannot alloc expectation");
				ret = NF_DROP;
				जाओ out;
			पूर्ण
			tuple = &ct->tuplehash[!dir].tuple;
			port = htons(dcc_port);
			nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT,
					  tuple->src.l3num,
					  शून्य, &tuple->dst.u3,
					  IPPROTO_TCP, शून्य, &port);

			nf_nat_irc = rcu_dereference(nf_nat_irc_hook);
			अगर (nf_nat_irc && ct->status & IPS_NAT_MASK)
				ret = nf_nat_irc(skb, ctinfo, protoff,
						 addr_beg_p - ib_ptr,
						 addr_end_p - addr_beg_p,
						 exp);
			अन्यथा अगर (nf_ct_expect_related(exp, 0) != 0) अणु
				nf_ct_helper_log(skb, ct,
						 "cannot add expectation");
				ret = NF_DROP;
			पूर्ण
			nf_ct_expect_put(exp);
			जाओ out;
		पूर्ण
	पूर्ण
 out:
	spin_unlock_bh(&irc_buffer_lock);
	वापस ret;
पूर्ण

अटल काष्ठा nf_conntrack_helper irc[MAX_PORTS] __पढ़ो_mostly;
अटल काष्ठा nf_conntrack_expect_policy irc_exp_policy;

अटल पूर्णांक __init nf_conntrack_irc_init(व्योम)
अणु
	पूर्णांक i, ret;

	अगर (max_dcc_channels < 1) अणु
		pr_err("max_dcc_channels must not be zero\n");
		वापस -EINVAL;
	पूर्ण

	अगर (max_dcc_channels > NF_CT_EXPECT_MAX_CNT) अणु
		pr_err("max_dcc_channels must not be more than %u\n",
		       NF_CT_EXPECT_MAX_CNT);
		वापस -EINVAL;
	पूर्ण

	irc_exp_policy.max_expected = max_dcc_channels;
	irc_exp_policy.समयout = dcc_समयout;

	irc_buffer = kदो_स्मृति(65536, GFP_KERNEL);
	अगर (!irc_buffer)
		वापस -ENOMEM;

	/* If no port given, शेष to standard irc port */
	अगर (ports_c == 0)
		ports[ports_c++] = IRC_PORT;

	क्रम (i = 0; i < ports_c; i++) अणु
		nf_ct_helper_init(&irc[i], AF_INET, IPPROTO_TCP, HELPER_NAME,
				  IRC_PORT, ports[i], i, &irc_exp_policy,
				  0, help, शून्य, THIS_MODULE);
	पूर्ण

	ret = nf_conntrack_helpers_रेजिस्टर(&irc[0], ports_c);
	अगर (ret) अणु
		pr_err("failed to register helpers\n");
		kमुक्त(irc_buffer);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास nf_conntrack_irc_fini(व्योम)
अणु
	nf_conntrack_helpers_unरेजिस्टर(irc, ports_c);
	kमुक्त(irc_buffer);
पूर्ण

module_init(nf_conntrack_irc_init);
module_निकास(nf_conntrack_irc_fini);
