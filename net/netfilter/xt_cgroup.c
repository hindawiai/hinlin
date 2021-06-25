<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Xtables module to match the process control group.
 *
 * Might be used to implement inभागidual "per-application" firewall
 * policies in contrast to global policies based on control groups.
 * Matching is based upon processes tagged to net_cls' classid marker.
 *
 * (C) 2013 Daniel Borkmann <dborkman@redhat.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/skbuff.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_cgroup.h>
#समावेश <net/sock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Borkmann <dborkman@redhat.com>");
MODULE_DESCRIPTION("Xtables: process control group matching");
MODULE_ALIAS("ipt_cgroup");
MODULE_ALIAS("ip6t_cgroup");

अटल पूर्णांक cgroup_mt_check_v0(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_cgroup_info_v0 *info = par->matchinfo;

	अगर (info->invert & ~1)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_mt_check_v1(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_cgroup_info_v1 *info = par->matchinfo;
	काष्ठा cgroup *cgrp;

	अगर ((info->invert_path & ~1) || (info->invert_classid & ~1))
		वापस -EINVAL;

	अगर (!info->has_path && !info->has_classid) अणु
		pr_info("xt_cgroup: no path or classid specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (info->has_path && info->has_classid) अणु
		pr_info_ratelimited("path and classid specified\n");
		वापस -EINVAL;
	पूर्ण

	info->priv = शून्य;
	अगर (info->has_path) अणु
		cgrp = cgroup_get_from_path(info->path);
		अगर (IS_ERR(cgrp)) अणु
			pr_info_ratelimited("invalid path, errno=%ld\n",
					    PTR_ERR(cgrp));
			वापस -EINVAL;
		पूर्ण
		info->priv = cgrp;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cgroup_mt_check_v2(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_cgroup_info_v2 *info = par->matchinfo;
	काष्ठा cgroup *cgrp;

	अगर ((info->invert_path & ~1) || (info->invert_classid & ~1))
		वापस -EINVAL;

	अगर (!info->has_path && !info->has_classid) अणु
		pr_info("xt_cgroup: no path or classid specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (info->has_path && info->has_classid) अणु
		pr_info_ratelimited("path and classid specified\n");
		वापस -EINVAL;
	पूर्ण

	info->priv = शून्य;
	अगर (info->has_path) अणु
		cgrp = cgroup_get_from_path(info->path);
		अगर (IS_ERR(cgrp)) अणु
			pr_info_ratelimited("invalid path, errno=%ld\n",
					    PTR_ERR(cgrp));
			वापस -EINVAL;
		पूर्ण
		info->priv = cgrp;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
cgroup_mt_v0(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_cgroup_info_v0 *info = par->matchinfo;
	काष्ठा sock *sk = skb->sk;

	अगर (!sk || !sk_fullsock(sk) || !net_eq(xt_net(par), sock_net(sk)))
		वापस false;

	वापस (info->id == sock_cgroup_classid(&skb->sk->sk_cgrp_data)) ^
		info->invert;
पूर्ण

अटल bool cgroup_mt_v1(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_cgroup_info_v1 *info = par->matchinfo;
	काष्ठा sock_cgroup_data *skcd = &skb->sk->sk_cgrp_data;
	काष्ठा cgroup *ancestor = info->priv;
	काष्ठा sock *sk = skb->sk;

	अगर (!sk || !sk_fullsock(sk) || !net_eq(xt_net(par), sock_net(sk)))
		वापस false;

	अगर (ancestor)
		वापस cgroup_is_descendant(sock_cgroup_ptr(skcd), ancestor) ^
			info->invert_path;
	अन्यथा
		वापस (info->classid == sock_cgroup_classid(skcd)) ^
			info->invert_classid;
पूर्ण

अटल bool cgroup_mt_v2(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_cgroup_info_v2 *info = par->matchinfo;
	काष्ठा sock_cgroup_data *skcd = &skb->sk->sk_cgrp_data;
	काष्ठा cgroup *ancestor = info->priv;
	काष्ठा sock *sk = skb->sk;

	अगर (!sk || !sk_fullsock(sk) || !net_eq(xt_net(par), sock_net(sk)))
		वापस false;

	अगर (ancestor)
		वापस cgroup_is_descendant(sock_cgroup_ptr(skcd), ancestor) ^
			info->invert_path;
	अन्यथा
		वापस (info->classid == sock_cgroup_classid(skcd)) ^
			info->invert_classid;
पूर्ण

अटल व्योम cgroup_mt_destroy_v1(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	काष्ठा xt_cgroup_info_v1 *info = par->matchinfo;

	अगर (info->priv)
		cgroup_put(info->priv);
पूर्ण

अटल व्योम cgroup_mt_destroy_v2(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	काष्ठा xt_cgroup_info_v2 *info = par->matchinfo;

	अगर (info->priv)
		cgroup_put(info->priv);
पूर्ण

अटल काष्ठा xt_match cgroup_mt_reg[] __पढ़ो_mostly = अणु
	अणु
		.name		= "cgroup",
		.revision	= 0,
		.family		= NFPROTO_UNSPEC,
		.checkentry	= cgroup_mt_check_v0,
		.match		= cgroup_mt_v0,
		.matchsize	= माप(काष्ठा xt_cgroup_info_v0),
		.me		= THIS_MODULE,
		.hooks		= (1 << NF_INET_LOCAL_OUT) |
				  (1 << NF_INET_POST_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
	पूर्ण,
	अणु
		.name		= "cgroup",
		.revision	= 1,
		.family		= NFPROTO_UNSPEC,
		.checkentry	= cgroup_mt_check_v1,
		.match		= cgroup_mt_v1,
		.matchsize	= माप(काष्ठा xt_cgroup_info_v1),
		.usersize	= दुरत्व(काष्ठा xt_cgroup_info_v1, priv),
		.destroy	= cgroup_mt_destroy_v1,
		.me		= THIS_MODULE,
		.hooks		= (1 << NF_INET_LOCAL_OUT) |
				  (1 << NF_INET_POST_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
	पूर्ण,
	अणु
		.name		= "cgroup",
		.revision	= 2,
		.family		= NFPROTO_UNSPEC,
		.checkentry	= cgroup_mt_check_v2,
		.match		= cgroup_mt_v2,
		.matchsize	= माप(काष्ठा xt_cgroup_info_v2),
		.usersize	= दुरत्व(काष्ठा xt_cgroup_info_v2, priv),
		.destroy	= cgroup_mt_destroy_v2,
		.me		= THIS_MODULE,
		.hooks		= (1 << NF_INET_LOCAL_OUT) |
				  (1 << NF_INET_POST_ROUTING) |
				  (1 << NF_INET_LOCAL_IN),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cgroup_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_matches(cgroup_mt_reg, ARRAY_SIZE(cgroup_mt_reg));
पूर्ण

अटल व्योम __निकास cgroup_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_matches(cgroup_mt_reg, ARRAY_SIZE(cgroup_mt_reg));
पूर्ण

module_init(cgroup_mt_init);
module_निकास(cgroup_mt_निकास);
