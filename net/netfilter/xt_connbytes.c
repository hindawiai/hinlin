<शैली गुरु>
/* Kernel module to match connection tracking byte counter.
 * GPL (C) 2002 Martin Devera (devik@cdi.cz).
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/math64.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_connbytes.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_acct.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Harald Welte <laforge@netfilter.org>");
MODULE_DESCRIPTION("Xtables: Number of packets/bytes per connection matching");
MODULE_ALIAS("ipt_connbytes");
MODULE_ALIAS("ip6t_connbytes");

अटल bool
connbytes_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_connbytes_info *sinfo = par->matchinfo;
	स्थिर काष्ठा nf_conn *ct;
	क्रमागत ip_conntrack_info ctinfo;
	u_पूर्णांक64_t what = 0;	/* initialize to make gcc happy */
	u_पूर्णांक64_t bytes = 0;
	u_पूर्णांक64_t pkts = 0;
	स्थिर काष्ठा nf_conn_acct *acct;
	स्थिर काष्ठा nf_conn_counter *counters;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct)
		वापस false;

	acct = nf_conn_acct_find(ct);
	अगर (!acct)
		वापस false;

	counters = acct->counter;
	चयन (sinfo->what) अणु
	हाल XT_CONNBYTES_PKTS:
		चयन (sinfo->direction) अणु
		हाल XT_CONNBYTES_सूची_ORIGINAL:
			what = atomic64_पढ़ो(&counters[IP_CT_सूची_ORIGINAL].packets);
			अवरोध;
		हाल XT_CONNBYTES_सूची_REPLY:
			what = atomic64_पढ़ो(&counters[IP_CT_सूची_REPLY].packets);
			अवरोध;
		हाल XT_CONNBYTES_सूची_BOTH:
			what = atomic64_पढ़ो(&counters[IP_CT_सूची_ORIGINAL].packets);
			what += atomic64_पढ़ो(&counters[IP_CT_सूची_REPLY].packets);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल XT_CONNBYTES_BYTES:
		चयन (sinfo->direction) अणु
		हाल XT_CONNBYTES_सूची_ORIGINAL:
			what = atomic64_पढ़ो(&counters[IP_CT_सूची_ORIGINAL].bytes);
			अवरोध;
		हाल XT_CONNBYTES_सूची_REPLY:
			what = atomic64_पढ़ो(&counters[IP_CT_सूची_REPLY].bytes);
			अवरोध;
		हाल XT_CONNBYTES_सूची_BOTH:
			what = atomic64_पढ़ो(&counters[IP_CT_सूची_ORIGINAL].bytes);
			what += atomic64_पढ़ो(&counters[IP_CT_सूची_REPLY].bytes);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल XT_CONNBYTES_AVGPKT:
		चयन (sinfo->direction) अणु
		हाल XT_CONNBYTES_सूची_ORIGINAL:
			bytes = atomic64_पढ़ो(&counters[IP_CT_सूची_ORIGINAL].bytes);
			pkts  = atomic64_पढ़ो(&counters[IP_CT_सूची_ORIGINAL].packets);
			अवरोध;
		हाल XT_CONNBYTES_सूची_REPLY:
			bytes = atomic64_पढ़ो(&counters[IP_CT_सूची_REPLY].bytes);
			pkts  = atomic64_पढ़ो(&counters[IP_CT_सूची_REPLY].packets);
			अवरोध;
		हाल XT_CONNBYTES_सूची_BOTH:
			bytes = atomic64_पढ़ो(&counters[IP_CT_सूची_ORIGINAL].bytes) +
				atomic64_पढ़ो(&counters[IP_CT_सूची_REPLY].bytes);
			pkts  = atomic64_पढ़ो(&counters[IP_CT_सूची_ORIGINAL].packets) +
				atomic64_पढ़ो(&counters[IP_CT_सूची_REPLY].packets);
			अवरोध;
		पूर्ण
		अगर (pkts != 0)
			what = भाग64_u64(bytes, pkts);
		अवरोध;
	पूर्ण

	अगर (sinfo->count.to >= sinfo->count.from)
		वापस what <= sinfo->count.to && what >= sinfo->count.from;
	अन्यथा /* inverted */
		वापस what < sinfo->count.to || what > sinfo->count.from;
पूर्ण

अटल पूर्णांक connbytes_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा xt_connbytes_info *sinfo = par->matchinfo;
	पूर्णांक ret;

	अगर (sinfo->what != XT_CONNBYTES_PKTS &&
	    sinfo->what != XT_CONNBYTES_BYTES &&
	    sinfo->what != XT_CONNBYTES_AVGPKT)
		वापस -EINVAL;

	अगर (sinfo->direction != XT_CONNBYTES_सूची_ORIGINAL &&
	    sinfo->direction != XT_CONNBYTES_सूची_REPLY &&
	    sinfo->direction != XT_CONNBYTES_सूची_BOTH)
		वापस -EINVAL;

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0)
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);

	/*
	 * This filter cannot function correctly unless connection tracking
	 * accounting is enabled, so complain in the hope that someone notices.
	 */
	अगर (!nf_ct_acct_enabled(par->net)) अणु
		pr_warn("Forcing CT accounting to be enabled\n");
		nf_ct_set_acct(par->net, true);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम connbytes_mt_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल काष्ठा xt_match connbytes_mt_reg __पढ़ो_mostly = अणु
	.name       = "connbytes",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.checkentry = connbytes_mt_check,
	.match      = connbytes_mt,
	.destroy    = connbytes_mt_destroy,
	.matchsize  = माप(काष्ठा xt_connbytes_info),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init connbytes_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&connbytes_mt_reg);
पूर्ण

अटल व्योम __निकास connbytes_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&connbytes_mt_reg);
पूर्ण

module_init(connbytes_mt_init);
module_निकास(connbytes_mt_निकास);
