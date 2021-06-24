<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	xt_ipvs - kernel module to match IPVS connection properties
 *
 *	Author: Hannes Eder <heder@google.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#अगर_घोषित CONFIG_IP_VS_IPV6
#समावेश <net/ipv6.h>
#पूर्ण_अगर
#समावेश <linux/ip_vs.h>
#समावेश <linux/types.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_ipvs.h>
#समावेश <net/netfilter/nf_conntrack.h>

#समावेश <net/ip_vs.h>

MODULE_AUTHOR("Hannes Eder <heder@google.com>");
MODULE_DESCRIPTION("Xtables: match IPVS connection properties");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_ipvs");
MODULE_ALIAS("ip6t_ipvs");

/* borrowed from xt_conntrack */
अटल bool ipvs_mt_addrcmp(स्थिर जोड़ nf_inet_addr *kaddr,
			    स्थिर जोड़ nf_inet_addr *uaddr,
			    स्थिर जोड़ nf_inet_addr *umask,
			    अचिन्हित पूर्णांक l3proto)
अणु
	अगर (l3proto == NFPROTO_IPV4)
		वापस ((kaddr->ip ^ uaddr->ip) & umask->ip) == 0;
#अगर_घोषित CONFIG_IP_VS_IPV6
	अन्यथा अगर (l3proto == NFPROTO_IPV6)
		वापस ipv6_masked_addr_cmp(&kaddr->in6, &umask->in6,
		       &uaddr->in6) == 0;
#पूर्ण_अगर
	अन्यथा
		वापस false;
पूर्ण

अटल bool
ipvs_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_ipvs_mtinfo *data = par->matchinfo;
	काष्ठा netns_ipvs *ipvs = net_ipvs(xt_net(par));
	/* ipvs_mt_check ensures that family is only NFPROTO_IPV[46]. */
	स्थिर u_पूर्णांक8_t family = xt_family(par);
	काष्ठा ip_vs_iphdr iph;
	काष्ठा ip_vs_protocol *pp;
	काष्ठा ip_vs_conn *cp;
	bool match = true;

	अगर (data->biपंचांगask == XT_IPVS_IPVS_PROPERTY) अणु
		match = skb->ipvs_property ^
			!!(data->invert & XT_IPVS_IPVS_PROPERTY);
		जाओ out;
	पूर्ण

	/* other flags than XT_IPVS_IPVS_PROPERTY are set */
	अगर (!skb->ipvs_property) अणु
		match = false;
		जाओ out;
	पूर्ण

	ip_vs_fill_iph_skb(family, skb, true, &iph);

	अगर (data->biपंचांगask & XT_IPVS_PROTO)
		अगर ((iph.protocol == data->l4proto) ^
		    !(data->invert & XT_IPVS_PROTO)) अणु
			match = false;
			जाओ out;
		पूर्ण

	pp = ip_vs_proto_get(iph.protocol);
	अगर (unlikely(!pp)) अणु
		match = false;
		जाओ out;
	पूर्ण

	/*
	 * Check अगर the packet beदीर्घs to an existing entry
	 */
	cp = pp->conn_out_get(ipvs, family, skb, &iph);
	अगर (unlikely(cp == शून्य)) अणु
		match = false;
		जाओ out;
	पूर्ण

	/*
	 * We found a connection, i.e. ct != 0, make sure to call
	 * __ip_vs_conn_put beक्रमe वापसing.  In our हाल jump to out_put_con.
	 */

	अगर (data->biपंचांगask & XT_IPVS_VPORT)
		अगर ((cp->vport == data->vport) ^
		    !(data->invert & XT_IPVS_VPORT)) अणु
			match = false;
			जाओ out_put_cp;
		पूर्ण

	अगर (data->biपंचांगask & XT_IPVS_VPORTCTL)
		अगर ((cp->control != शून्य &&
		     cp->control->vport == data->vportctl) ^
		    !(data->invert & XT_IPVS_VPORTCTL)) अणु
			match = false;
			जाओ out_put_cp;
		पूर्ण

	अगर (data->biपंचांगask & XT_IPVS_सूची) अणु
		क्रमागत ip_conntrack_info ctinfo;
		काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);

		अगर (ct == शून्य) अणु
			match = false;
			जाओ out_put_cp;
		पूर्ण

		अगर ((ctinfo >= IP_CT_IS_REPLY) ^
		    !!(data->invert & XT_IPVS_सूची)) अणु
			match = false;
			जाओ out_put_cp;
		पूर्ण
	पूर्ण

	अगर (data->biपंचांगask & XT_IPVS_METHOD)
		अगर (((cp->flags & IP_VS_CONN_F_FWD_MASK) == data->fwd_method) ^
		    !(data->invert & XT_IPVS_METHOD)) अणु
			match = false;
			जाओ out_put_cp;
		पूर्ण

	अगर (data->biपंचांगask & XT_IPVS_VADDR) अणु
		अगर (ipvs_mt_addrcmp(&cp->vaddr, &data->vaddr,
				    &data->vmask, family) ^
		    !(data->invert & XT_IPVS_VADDR)) अणु
			match = false;
			जाओ out_put_cp;
		पूर्ण
	पूर्ण

out_put_cp:
	__ip_vs_conn_put(cp);
out:
	pr_debug("match=%d\n", match);
	वापस match;
पूर्ण

अटल पूर्णांक ipvs_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	अगर (par->family != NFPROTO_IPV4
#अगर_घोषित CONFIG_IP_VS_IPV6
	    && par->family != NFPROTO_IPV6
#पूर्ण_अगर
		) अणु
		pr_info_ratelimited("protocol family %u not supported\n",
				    par->family);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xt_match xt_ipvs_mt_reg __पढ़ो_mostly = अणु
	.name       = "ipvs",
	.revision   = 0,
	.family     = NFPROTO_UNSPEC,
	.match      = ipvs_mt,
	.checkentry = ipvs_mt_check,
	.matchsize  = XT_ALIGN(माप(काष्ठा xt_ipvs_mtinfo)),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ipvs_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&xt_ipvs_mt_reg);
पूर्ण

अटल व्योम __निकास ipvs_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&xt_ipvs_mt_reg);
पूर्ण

module_init(ipvs_mt_init);
module_निकास(ipvs_mt_निकास);
