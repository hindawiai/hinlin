<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010 Patrick McHardy <kaber@trash.net>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netfilter_ipv4/ip_tables.h>
#समावेश <linux/netfilter_ipv6/ip6_tables.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_CT.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>

अटल अंतरभूत पूर्णांक xt_ct_target(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct)
अणु
	/* Previously seen (loopback)? Ignore. */
	अगर (skb->_nfct != 0)
		वापस XT_CONTINUE;

	अगर (ct) अणु
		atomic_inc(&ct->ct_general.use);
		nf_ct_set(skb, ct, IP_CT_NEW);
	पूर्ण अन्यथा अणु
		nf_ct_set(skb, ct, IP_CT_UNTRACKED);
	पूर्ण

	वापस XT_CONTINUE;
पूर्ण

अटल अचिन्हित पूर्णांक xt_ct_target_v0(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_ct_target_info *info = par->targinfo;
	काष्ठा nf_conn *ct = info->ct;

	वापस xt_ct_target(skb, ct);
पूर्ण

अटल अचिन्हित पूर्णांक xt_ct_target_v1(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_ct_target_info_v1 *info = par->targinfo;
	काष्ठा nf_conn *ct = info->ct;

	वापस xt_ct_target(skb, ct);
पूर्ण

अटल u8 xt_ct_find_proto(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	अगर (par->family == NFPROTO_IPV4) अणु
		स्थिर काष्ठा ipt_entry *e = par->entryinfo;

		अगर (e->ip.invflags & IPT_INV_PROTO)
			वापस 0;
		वापस e->ip.proto;
	पूर्ण अन्यथा अगर (par->family == NFPROTO_IPV6) अणु
		स्थिर काष्ठा ip6t_entry *e = par->entryinfo;

		अगर (e->ipv6.invflags & IP6T_INV_PROTO)
			वापस 0;
		वापस e->ipv6.proto;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक
xt_ct_set_helper(काष्ठा nf_conn *ct, स्थिर अक्षर *helper_name,
		 स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा nf_conntrack_helper *helper;
	काष्ठा nf_conn_help *help;
	u8 proto;

	proto = xt_ct_find_proto(par);
	अगर (!proto) अणु
		pr_info_ratelimited("You must specify a L4 protocol and not use inversions on it\n");
		वापस -ENOENT;
	पूर्ण

	helper = nf_conntrack_helper_try_module_get(helper_name, par->family,
						    proto);
	अगर (helper == शून्य) अणु
		pr_info_ratelimited("No such helper \"%s\"\n", helper_name);
		वापस -ENOENT;
	पूर्ण

	help = nf_ct_helper_ext_add(ct, GFP_KERNEL);
	अगर (help == शून्य) अणु
		nf_conntrack_helper_put(helper);
		वापस -ENOMEM;
	पूर्ण

	help->helper = helper;
	वापस 0;
पूर्ण

अटल पूर्णांक
xt_ct_set_समयout(काष्ठा nf_conn *ct, स्थिर काष्ठा xt_tgchk_param *par,
		  स्थिर अक्षर *समयout_name)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	u8 proto;

	proto = xt_ct_find_proto(par);
	अगर (!proto) अणु
		pr_info_ratelimited("You must specify a L4 protocol and not "
				    "use inversions on it");
		वापस -EINVAL;
	पूर्ण
	l4proto = nf_ct_l4proto_find(proto);
	वापस nf_ct_set_समयout(par->net, ct, par->family, l4proto->l4proto,
				 समयout_name);

#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल u16 xt_ct_flags_to_dir(स्थिर काष्ठा xt_ct_target_info_v1 *info)
अणु
	चयन (info->flags & (XT_CT_ZONE_सूची_ORIG |
			       XT_CT_ZONE_सूची_REPL)) अणु
	हाल XT_CT_ZONE_सूची_ORIG:
		वापस NF_CT_ZONE_सूची_ORIG;
	हाल XT_CT_ZONE_सूची_REPL:
		वापस NF_CT_ZONE_सूची_REPL;
	शेष:
		वापस NF_CT_DEFAULT_ZONE_सूची;
	पूर्ण
पूर्ण

अटल पूर्णांक xt_ct_tg_check(स्थिर काष्ठा xt_tgchk_param *par,
			  काष्ठा xt_ct_target_info_v1 *info)
अणु
	काष्ठा nf_conntrack_zone zone;
	काष्ठा nf_conn_help *help;
	काष्ठा nf_conn *ct;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (info->flags & XT_CT_NOTRACK) अणु
		ct = शून्य;
		जाओ out;
	पूर्ण

#अगर_अघोषित CONFIG_NF_CONNTRACK_ZONES
	अगर (info->zone || info->flags & (XT_CT_ZONE_सूची_ORIG |
					 XT_CT_ZONE_सूची_REPL |
					 XT_CT_ZONE_MARK))
		जाओ err1;
#पूर्ण_अगर

	ret = nf_ct_netns_get(par->net, par->family);
	अगर (ret < 0)
		जाओ err1;

	स_रखो(&zone, 0, माप(zone));
	zone.id = info->zone;
	zone.dir = xt_ct_flags_to_dir(info);
	अगर (info->flags & XT_CT_ZONE_MARK)
		zone.flags |= NF_CT_FLAG_MARK;

	ct = nf_ct_पंचांगpl_alloc(par->net, &zone, GFP_KERNEL);
	अगर (!ct) अणु
		ret = -ENOMEM;
		जाओ err2;
	पूर्ण

	ret = 0;
	अगर ((info->ct_events || info->exp_events) &&
	    !nf_ct_ecache_ext_add(ct, info->ct_events, info->exp_events,
				  GFP_KERNEL)) अणु
		ret = -EINVAL;
		जाओ err3;
	पूर्ण

	अगर (info->helper[0]) अणु
		अगर (strnlen(info->helper, माप(info->helper)) == माप(info->helper)) अणु
			ret = -ENAMETOOLONG;
			जाओ err3;
		पूर्ण

		ret = xt_ct_set_helper(ct, info->helper, par);
		अगर (ret < 0)
			जाओ err3;
	पूर्ण

	अगर (info->समयout[0]) अणु
		अगर (strnlen(info->समयout, माप(info->समयout)) == माप(info->समयout)) अणु
			ret = -ENAMETOOLONG;
			जाओ err4;
		पूर्ण

		ret = xt_ct_set_समयout(ct, par, info->समयout);
		अगर (ret < 0)
			जाओ err4;
	पूर्ण
	__set_bit(IPS_CONFIRMED_BIT, &ct->status);
	nf_conntrack_get(&ct->ct_general);
out:
	info->ct = ct;
	वापस 0;

err4:
	help = nfct_help(ct);
	अगर (help)
		nf_conntrack_helper_put(help->helper);
err3:
	nf_ct_पंचांगpl_मुक्त(ct);
err2:
	nf_ct_netns_put(par->net, par->family);
err1:
	वापस ret;
पूर्ण

अटल पूर्णांक xt_ct_tg_check_v0(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा xt_ct_target_info *info = par->targinfo;
	काष्ठा xt_ct_target_info_v1 info_v1 = अणु
		.flags 		= info->flags,
		.zone		= info->zone,
		.ct_events	= info->ct_events,
		.exp_events	= info->exp_events,
	पूर्ण;
	पूर्णांक ret;

	अगर (info->flags & ~XT_CT_NOTRACK)
		वापस -EINVAL;

	स_नकल(info_v1.helper, info->helper, माप(info->helper));

	ret = xt_ct_tg_check(par, &info_v1);
	अगर (ret < 0)
		वापस ret;

	info->ct = info_v1.ct;

	वापस ret;
पूर्ण

अटल पूर्णांक xt_ct_tg_check_v1(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा xt_ct_target_info_v1 *info = par->targinfo;

	अगर (info->flags & ~XT_CT_NOTRACK)
		वापस -EINVAL;

	वापस xt_ct_tg_check(par, par->targinfo);
पूर्ण

अटल पूर्णांक xt_ct_tg_check_v2(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा xt_ct_target_info_v1 *info = par->targinfo;

	अगर (info->flags & ~XT_CT_MASK)
		वापस -EINVAL;

	वापस xt_ct_tg_check(par, par->targinfo);
पूर्ण

अटल व्योम xt_ct_tg_destroy(स्थिर काष्ठा xt_tgdtor_param *par,
			     काष्ठा xt_ct_target_info_v1 *info)
अणु
	काष्ठा nf_conn *ct = info->ct;
	काष्ठा nf_conn_help *help;

	अगर (ct) अणु
		help = nfct_help(ct);
		अगर (help)
			nf_conntrack_helper_put(help->helper);

		nf_ct_netns_put(par->net, par->family);

		nf_ct_destroy_समयout(ct);
		nf_ct_put(info->ct);
	पूर्ण
पूर्ण

अटल व्योम xt_ct_tg_destroy_v0(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	काष्ठा xt_ct_target_info *info = par->targinfo;
	काष्ठा xt_ct_target_info_v1 info_v1 = अणु
		.flags 		= info->flags,
		.zone		= info->zone,
		.ct_events	= info->ct_events,
		.exp_events	= info->exp_events,
		.ct		= info->ct,
	पूर्ण;
	स_नकल(info_v1.helper, info->helper, माप(info->helper));

	xt_ct_tg_destroy(par, &info_v1);
पूर्ण

अटल व्योम xt_ct_tg_destroy_v1(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	xt_ct_tg_destroy(par, par->targinfo);
पूर्ण

अटल काष्ठा xt_target xt_ct_tg_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "CT",
		.family		= NFPROTO_UNSPEC,
		.tarमाला_लोize	= माप(काष्ठा xt_ct_target_info),
		.usersize	= दुरत्व(काष्ठा xt_ct_target_info, ct),
		.checkentry	= xt_ct_tg_check_v0,
		.destroy	= xt_ct_tg_destroy_v0,
		.target		= xt_ct_target_v0,
		.table		= "raw",
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "CT",
		.family		= NFPROTO_UNSPEC,
		.revision	= 1,
		.tarमाला_लोize	= माप(काष्ठा xt_ct_target_info_v1),
		.usersize	= दुरत्व(काष्ठा xt_ct_target_info, ct),
		.checkentry	= xt_ct_tg_check_v1,
		.destroy	= xt_ct_tg_destroy_v1,
		.target		= xt_ct_target_v1,
		.table		= "raw",
		.me		= THIS_MODULE,
	पूर्ण,
	अणु
		.name		= "CT",
		.family		= NFPROTO_UNSPEC,
		.revision	= 2,
		.tarमाला_लोize	= माप(काष्ठा xt_ct_target_info_v1),
		.usersize	= दुरत्व(काष्ठा xt_ct_target_info, ct),
		.checkentry	= xt_ct_tg_check_v2,
		.destroy	= xt_ct_tg_destroy_v1,
		.target		= xt_ct_target_v1,
		.table		= "raw",
		.me		= THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक
notrack_tg(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	/* Previously seen (loopback)? Ignore. */
	अगर (skb->_nfct != 0)
		वापस XT_CONTINUE;

	nf_ct_set(skb, शून्य, IP_CT_UNTRACKED);

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक notrack_chk(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	अगर (!par->net->xt.notrack_deprecated_warning) अणु
		pr_info("netfilter: NOTRACK target is deprecated, "
			"use CT instead or upgrade iptables\n");
		par->net->xt.notrack_deprecated_warning = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_target notrack_tg_reg __पढ़ो_mostly = अणु
	.name		= "NOTRACK",
	.revision	= 0,
	.family		= NFPROTO_UNSPEC,
	.checkentry	= notrack_chk,
	.target		= notrack_tg,
	.table		= "raw",
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init xt_ct_tg_init(व्योम)
अणु
	पूर्णांक ret;

	ret = xt_रेजिस्टर_target(&notrack_tg_reg);
	अगर (ret < 0)
		वापस ret;

	ret = xt_रेजिस्टर_tarमाला_लो(xt_ct_tg_reg, ARRAY_SIZE(xt_ct_tg_reg));
	अगर (ret < 0) अणु
		xt_unरेजिस्टर_target(&notrack_tg_reg);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास xt_ct_tg_निकास(व्योम)
अणु
	xt_unरेजिस्टर_tarमाला_लो(xt_ct_tg_reg, ARRAY_SIZE(xt_ct_tg_reg));
	xt_unरेजिस्टर_target(&notrack_tg_reg);
पूर्ण

module_init(xt_ct_tg_init);
module_निकास(xt_ct_tg_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Xtables: connection tracking target");
MODULE_ALIAS("ipt_CT");
MODULE_ALIAS("ip6t_CT");
MODULE_ALIAS("ipt_NOTRACK");
MODULE_ALIAS("ip6t_NOTRACK");
