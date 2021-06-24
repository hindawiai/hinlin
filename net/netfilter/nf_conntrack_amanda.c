<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Amanda extension क्रम IP connection tracking
 *
 * (C) 2002 by Brian J. Murrell <netfilter@पूर्णांकerlinx.bc.ca>
 * based on HW's ip_conntrack_irc.c as well as other modules
 * (C) 2006 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/textsearch.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/udp.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/gfp.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <linux/netfilter/nf_conntrack_amanda.h>

अटल अचिन्हित पूर्णांक master_समयout __पढ़ो_mostly = 300;
अटल अक्षर *ts_algo = "kmp";

#घोषणा HELPER_NAME "amanda"

MODULE_AUTHOR("Brian J. Murrell <netfilter@interlinx.bc.ca>");
MODULE_DESCRIPTION("Amanda connection tracking module");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ip_conntrack_amanda");
MODULE_ALIAS_NFCT_HELPER(HELPER_NAME);

module_param(master_समयout, uपूर्णांक, 0600);
MODULE_PARM_DESC(master_समयout, "timeout for the master connection");
module_param(ts_algo, अक्षरp, 0400);
MODULE_PARM_DESC(ts_algo, "textsearch algorithm to use (default kmp)");

अचिन्हित पूर्णांक (*nf_nat_amanda_hook)(काष्ठा sk_buff *skb,
				   क्रमागत ip_conntrack_info ctinfo,
				   अचिन्हित पूर्णांक protoff,
				   अचिन्हित पूर्णांक matchoff,
				   अचिन्हित पूर्णांक matchlen,
				   काष्ठा nf_conntrack_expect *exp)
				   __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nf_nat_amanda_hook);

क्रमागत amanda_strings अणु
	SEARCH_CONNECT,
	SEARCH_NEWLINE,
	SEARCH_DATA,
	SEARCH_MESG,
	SEARCH_INDEX,
	SEARCH_STATE,
पूर्ण;

अटल काष्ठा अणु
	स्थिर अक्षर		*string;
	माप_प्रकार			len;
	काष्ठा ts_config	*ts;
पूर्ण search[] __पढ़ो_mostly = अणु
	[SEARCH_CONNECT] = अणु
		.string	= "CONNECT ",
		.len	= 8,
	पूर्ण,
	[SEARCH_NEWLINE] = अणु
		.string	= "\n",
		.len	= 1,
	पूर्ण,
	[SEARCH_DATA] = अणु
		.string	= "DATA ",
		.len	= 5,
	पूर्ण,
	[SEARCH_MESG] = अणु
		.string	= "MESG ",
		.len	= 5,
	पूर्ण,
	[SEARCH_INDEX] = अणु
		.string = "INDEX ",
		.len	= 6,
	पूर्ण,
	[SEARCH_STATE] = अणु
		.string = "STATE ",
		.len	= 6,
	पूर्ण,
पूर्ण;

अटल पूर्णांक amanda_help(काष्ठा sk_buff *skb,
		       अचिन्हित पूर्णांक protoff,
		       काष्ठा nf_conn *ct,
		       क्रमागत ip_conntrack_info ctinfo)
अणु
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा nf_conntrack_tuple *tuple;
	अचिन्हित पूर्णांक dataoff, start, stop, off, i;
	अक्षर pbuf[माप("65535")], *पंचांगp;
	u_पूर्णांक16_t len;
	__be16 port;
	पूर्णांक ret = NF_ACCEPT;
	typeof(nf_nat_amanda_hook) nf_nat_amanda;

	/* Only look at packets from the Amanda server */
	अगर (CTINFO2सूची(ctinfo) == IP_CT_सूची_ORIGINAL)
		वापस NF_ACCEPT;

	/* increase the UDP समयout of the master connection as replies from
	 * Amanda clients to the server can be quite delayed */
	nf_ct_refresh(ct, skb, master_समयout * HZ);

	/* No data? */
	dataoff = protoff + माप(काष्ठा udphdr);
	अगर (dataoff >= skb->len) अणु
		net_err_ratelimited("amanda_help: skblen = %u\n", skb->len);
		वापस NF_ACCEPT;
	पूर्ण

	start = skb_find_text(skb, dataoff, skb->len,
			      search[SEARCH_CONNECT].ts);
	अगर (start == अच_पूर्णांक_उच्च)
		जाओ out;
	start += dataoff + search[SEARCH_CONNECT].len;

	stop = skb_find_text(skb, start, skb->len,
			     search[SEARCH_NEWLINE].ts);
	अगर (stop == अच_पूर्णांक_उच्च)
		जाओ out;
	stop += start;

	क्रम (i = SEARCH_DATA; i <= SEARCH_STATE; i++) अणु
		off = skb_find_text(skb, start, stop, search[i].ts);
		अगर (off == अच_पूर्णांक_उच्च)
			जारी;
		off += start + search[i].len;

		len = min_t(अचिन्हित पूर्णांक, माप(pbuf) - 1, stop - off);
		अगर (skb_copy_bits(skb, off, pbuf, len))
			अवरोध;
		pbuf[len] = '\0';

		port = htons(simple_म_से_अदीर्घ(pbuf, &पंचांगp, 10));
		len = पंचांगp - pbuf;
		अगर (port == 0 || len > 5)
			अवरोध;

		exp = nf_ct_expect_alloc(ct);
		अगर (exp == शून्य) अणु
			nf_ct_helper_log(skb, ct, "cannot alloc expectation");
			ret = NF_DROP;
			जाओ out;
		पूर्ण
		tuple = &ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple;
		nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT,
				  nf_ct_l3num(ct),
				  &tuple->src.u3, &tuple->dst.u3,
				  IPPROTO_TCP, शून्य, &port);

		nf_nat_amanda = rcu_dereference(nf_nat_amanda_hook);
		अगर (nf_nat_amanda && ct->status & IPS_NAT_MASK)
			ret = nf_nat_amanda(skb, ctinfo, protoff,
					    off - dataoff, len, exp);
		अन्यथा अगर (nf_ct_expect_related(exp, 0) != 0) अणु
			nf_ct_helper_log(skb, ct, "cannot add expectation");
			ret = NF_DROP;
		पूर्ण
		nf_ct_expect_put(exp);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nf_conntrack_expect_policy amanda_exp_policy = अणु
	.max_expected		= 4,
	.समयout		= 180,
पूर्ण;

अटल काष्ठा nf_conntrack_helper amanda_helper[2] __पढ़ो_mostly = अणु
	अणु
		.name			= HELPER_NAME,
		.me			= THIS_MODULE,
		.help			= amanda_help,
		.tuple.src.l3num	= AF_INET,
		.tuple.src.u.udp.port	= cpu_to_be16(10080),
		.tuple.dst.protonum	= IPPROTO_UDP,
		.expect_policy		= &amanda_exp_policy,
		.nat_mod_name		= NF_NAT_HELPER_NAME(HELPER_NAME),
	पूर्ण,
	अणु
		.name			= "amanda",
		.me			= THIS_MODULE,
		.help			= amanda_help,
		.tuple.src.l3num	= AF_INET6,
		.tuple.src.u.udp.port	= cpu_to_be16(10080),
		.tuple.dst.protonum	= IPPROTO_UDP,
		.expect_policy		= &amanda_exp_policy,
		.nat_mod_name		= NF_NAT_HELPER_NAME(HELPER_NAME),
	पूर्ण,
पूर्ण;

अटल व्योम __निकास nf_conntrack_amanda_fini(व्योम)
अणु
	पूर्णांक i;

	nf_conntrack_helpers_unरेजिस्टर(amanda_helper,
					ARRAY_SIZE(amanda_helper));
	क्रम (i = 0; i < ARRAY_SIZE(search); i++)
		textsearch_destroy(search[i].ts);
पूर्ण

अटल पूर्णांक __init nf_conntrack_amanda_init(व्योम)
अणु
	पूर्णांक ret, i;

	NF_CT_HELPER_BUILD_BUG_ON(0);

	क्रम (i = 0; i < ARRAY_SIZE(search); i++) अणु
		search[i].ts = textsearch_prepare(ts_algo, search[i].string,
						  search[i].len,
						  GFP_KERNEL, TS_AUTOLOAD);
		अगर (IS_ERR(search[i].ts)) अणु
			ret = PTR_ERR(search[i].ts);
			जाओ err1;
		पूर्ण
	पूर्ण
	ret = nf_conntrack_helpers_रेजिस्टर(amanda_helper,
					    ARRAY_SIZE(amanda_helper));
	अगर (ret < 0)
		जाओ err1;
	वापस 0;

err1:
	जबतक (--i >= 0)
		textsearch_destroy(search[i].ts);

	वापस ret;
पूर्ण

module_init(nf_conntrack_amanda_init);
module_निकास(nf_conntrack_amanda_fini);
