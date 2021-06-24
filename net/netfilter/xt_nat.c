<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2011 Patrick McHardy <kaber@trash.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/netfilter/nf_nat.h>

अटल पूर्णांक xt_nat_checkentry_v0(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा nf_nat_ipv4_multi_range_compat *mr = par->targinfo;

	अगर (mr->rangesize != 1) अणु
		pr_info_ratelimited("multiple ranges no longer supported\n");
		वापस -EINVAL;
	पूर्ण
	वापस nf_ct_netns_get(par->net, par->family);
पूर्ण

अटल पूर्णांक xt_nat_checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	वापस nf_ct_netns_get(par->net, par->family);
पूर्ण

अटल व्योम xt_nat_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	nf_ct_netns_put(par->net, par->family);
पूर्ण

अटल व्योम xt_nat_convert_range(काष्ठा nf_nat_range2 *dst,
				 स्थिर काष्ठा nf_nat_ipv4_range *src)
अणु
	स_रखो(&dst->min_addr, 0, माप(dst->min_addr));
	स_रखो(&dst->max_addr, 0, माप(dst->max_addr));
	स_रखो(&dst->base_proto, 0, माप(dst->base_proto));

	dst->flags	 = src->flags;
	dst->min_addr.ip = src->min_ip;
	dst->max_addr.ip = src->max_ip;
	dst->min_proto	 = src->min;
	dst->max_proto	 = src->max;
पूर्ण

अटल अचिन्हित पूर्णांक
xt_snat_target_v0(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा nf_nat_ipv4_multi_range_compat *mr = par->targinfo;
	काष्ठा nf_nat_range2 range;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	WARN_ON(!(ct != शून्य &&
		 (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
		  ctinfo == IP_CT_RELATED_REPLY)));

	xt_nat_convert_range(&range, &mr->range[0]);
	वापस nf_nat_setup_info(ct, &range, NF_NAT_MANIP_SRC);
पूर्ण

अटल अचिन्हित पूर्णांक
xt_dnat_target_v0(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा nf_nat_ipv4_multi_range_compat *mr = par->targinfo;
	काष्ठा nf_nat_range2 range;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	WARN_ON(!(ct != शून्य &&
		 (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED)));

	xt_nat_convert_range(&range, &mr->range[0]);
	वापस nf_nat_setup_info(ct, &range, NF_NAT_MANIP_DST);
पूर्ण

अटल अचिन्हित पूर्णांक
xt_snat_target_v1(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा nf_nat_range *range_v1 = par->targinfo;
	काष्ठा nf_nat_range2 range;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	WARN_ON(!(ct != शून्य &&
		 (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
		  ctinfo == IP_CT_RELATED_REPLY)));

	स_नकल(&range, range_v1, माप(*range_v1));
	स_रखो(&range.base_proto, 0, माप(range.base_proto));

	वापस nf_nat_setup_info(ct, &range, NF_NAT_MANIP_SRC);
पूर्ण

अटल अचिन्हित पूर्णांक
xt_dnat_target_v1(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा nf_nat_range *range_v1 = par->targinfo;
	काष्ठा nf_nat_range2 range;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	WARN_ON(!(ct != शून्य &&
		 (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED)));

	स_नकल(&range, range_v1, माप(*range_v1));
	स_रखो(&range.base_proto, 0, माप(range.base_proto));

	वापस nf_nat_setup_info(ct, &range, NF_NAT_MANIP_DST);
पूर्ण

अटल अचिन्हित पूर्णांक
xt_snat_target_v2(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा nf_nat_range2 *range = par->targinfo;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	WARN_ON(!(ct != शून्य &&
		 (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
		  ctinfo == IP_CT_RELATED_REPLY)));

	वापस nf_nat_setup_info(ct, range, NF_NAT_MANIP_SRC);
पूर्ण

अटल अचिन्हित पूर्णांक
xt_dnat_target_v2(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा nf_nat_range2 *range = par->targinfo;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	WARN_ON(!(ct != शून्य &&
		 (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED)));

	वापस nf_nat_setup_info(ct, range, NF_NAT_MANIP_DST);
पूर्ण

अटल काष्ठा xt_target xt_nat_target_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "SNAT",
		.revision	= 0,
		.checkentry	= xt_nat_checkentry_v0,
		.destroy	= xt_nat_destroy,
		.target		= xt_snat_target_v0,
		.tarमाला_लोize	= माप(काष्ठा nf_nat_ipv4_multi_range_compat),
		.family		= NFPROTO_IPV4,
		.table		= "nat",
		.hooks		= (1 << NF_INET_POST_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "DNAT",
		.revision	= 0,
		.checkentry	= xt_nat_checkentry_v0,
		.destroy	= xt_nat_destroy,
		.target		= xt_dnat_target_v0,
		.tarमाला_लोize	= माप(काष्ठा nf_nat_ipv4_multi_range_compat),
		.family		= NFPROTO_IPV4,
		.table		= "nat",
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_OUT),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "SNAT",
		.revision	= 1,
		.checkentry	= xt_nat_checkentry,
		.destroy	= xt_nat_destroy,
		.target		= xt_snat_target_v1,
		.tarमाला_लोize	= माप(काष्ठा nf_nat_range),
		.table		= "nat",
		.hooks		= (1 << NF_INET_POST_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "DNAT",
		.revision	= 1,
		.checkentry	= xt_nat_checkentry,
		.destroy	= xt_nat_destroy,
		.target		= xt_dnat_target_v1,
		.tarमाला_लोize	= माप(काष्ठा nf_nat_range),
		.table		= "nat",
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_OUT),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "SNAT",
		.revision	= 2,
		.checkentry	= xt_nat_checkentry,
		.destroy	= xt_nat_destroy,
		.target		= xt_snat_target_v2,
		.tarमाला_लोize	= माप(काष्ठा nf_nat_range2),
		.table		= "nat",
		.hooks		= (1 << NF_INET_POST_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "DNAT",
		.revision	= 2,
		.checkentry	= xt_nat_checkentry,
		.destroy	= xt_nat_destroy,
		.target		= xt_dnat_target_v2,
		.tarमाला_लोize	= माप(काष्ठा nf_nat_range2),
		.table		= "nat",
		.hooks		= (1 << NF_INET_PRE_ROUTING) |
				  (1 << NF_INET_LOCAL_OUT),
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init xt_nat_init(व्योम)
अणु
	वापस xt_रेजिस्टर_tarमाला_लो(xt_nat_target_reg,
				   ARRAY_SIZE(xt_nat_target_reg));
पूर्ण

अटल व्योम __निकास xt_nat_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(xt_nat_target_reg, ARRAY_SIZE(xt_nat_target_reg));
पूर्ण

module_init(xt_nat_init);
module_निकास(xt_nat_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_ALIAS("ipt_SNAT");
MODULE_ALIAS("ipt_DNAT");
MODULE_ALIAS("ip6t_SNAT");
MODULE_ALIAS("ip6t_DNAT");
MODULE_DESCRIPTION("SNAT and DNAT targets support");
