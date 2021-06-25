<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2000-2002 Joakim Axelsson <gozem@linux.nu>
 *                         Patrick Schaaf <bof@bof.de>
 *                         Martin Josefsson <gandalf@wlug.westbo.se>
 * Copyright (C) 2003-2013 Jozsef Kadlecsik <kadlec@netfilter.org>
 */

/* Kernel module which implements the set match and SET target
 * क्रम netfilter/iptables.
 */

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/ipset/ip_set.h>
#समावेश <uapi/linux/netfilter/xt_set.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jozsef Kadlecsik <kadlec@netfilter.org>");
MODULE_DESCRIPTION("Xtables: IP set match and target module");
MODULE_ALIAS("xt_SET");
MODULE_ALIAS("ipt_set");
MODULE_ALIAS("ip6t_set");
MODULE_ALIAS("ipt_SET");
MODULE_ALIAS("ip6t_SET");

अटल अंतरभूत पूर्णांक
match_set(ip_set_id_t index, स्थिर काष्ठा sk_buff *skb,
	  स्थिर काष्ठा xt_action_param *par,
	  काष्ठा ip_set_adt_opt *opt, पूर्णांक inv)
अणु
	अगर (ip_set_test(index, skb, par, opt))
		inv = !inv;
	वापस inv;
पूर्ण

#घोषणा ADT_OPT(n, f, d, fs, cfs, t, p, b, po, bo)	\
काष्ठा ip_set_adt_opt n = अणु				\
	.family	= f,					\
	.dim = d,					\
	.flags = fs,					\
	.cmdflags = cfs,				\
	.ext.समयout = t,				\
	.ext.packets = p,				\
	.ext.bytes = b,					\
	.ext.packets_op = po,				\
	.ext.bytes_op = bo,				\
पूर्ण

/* Revision 0 पूर्णांकerface: backward compatible with netfilter/iptables */

अटल bool
set_match_v0(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_set_info_match_v0 *info = par->matchinfo;

	ADT_OPT(opt, xt_family(par), info->match_set.u.compat.dim,
		info->match_set.u.compat.flags, 0, अच_पूर्णांक_उच्च,
		0, 0, 0, 0);

	वापस match_set(info->match_set.index, skb, par, &opt,
			 info->match_set.u.compat.flags & IPSET_INV_MATCH);
पूर्ण

अटल व्योम
compat_flags(काष्ठा xt_set_info_v0 *info)
अणु
	u_पूर्णांक8_t i;

	/* Fill out compatibility data according to क्रमागत ip_set_kopt */
	info->u.compat.dim = IPSET_DIM_ZERO;
	अगर (info->u.flags[0] & IPSET_MATCH_INV)
		info->u.compat.flags |= IPSET_INV_MATCH;
	क्रम (i = 0; i < IPSET_DIM_MAX - 1 && info->u.flags[i]; i++) अणु
		info->u.compat.dim++;
		अगर (info->u.flags[i] & IPSET_SRC)
			info->u.compat.flags |= (1 << info->u.compat.dim);
	पूर्ण
पूर्ण

अटल पूर्णांक
set_match_v0_checkentry(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_set_info_match_v0 *info = par->matchinfo;
	ip_set_id_t index;

	index = ip_set_nfnl_get_byindex(par->net, info->match_set.index);

	अगर (index == IPSET_INVALID_ID) अणु
		pr_info_ratelimited("Cannot find set identified by id %u to match\n",
				    info->match_set.index);
		वापस -ENOENT;
	पूर्ण
	अगर (info->match_set.u.flags[IPSET_DIM_MAX - 1] != 0) अणु
		pr_info_ratelimited("set match dimension is over the limit!\n");
		ip_set_nfnl_put(par->net, info->match_set.index);
		वापस -दुस्फल;
	पूर्ण

	/* Fill out compatibility data */
	compat_flags(&info->match_set);

	वापस 0;
पूर्ण

अटल व्योम
set_match_v0_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	काष्ठा xt_set_info_match_v0 *info = par->matchinfo;

	ip_set_nfnl_put(par->net, info->match_set.index);
पूर्ण

/* Revision 1 match */

अटल bool
set_match_v1(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_set_info_match_v1 *info = par->matchinfo;

	ADT_OPT(opt, xt_family(par), info->match_set.dim,
		info->match_set.flags, 0, अच_पूर्णांक_उच्च,
		0, 0, 0, 0);

	अगर (opt.flags & IPSET_RETURN_NOMATCH)
		opt.cmdflags |= IPSET_FLAG_RETURN_NOMATCH;

	वापस match_set(info->match_set.index, skb, par, &opt,
			 info->match_set.flags & IPSET_INV_MATCH);
पूर्ण

अटल पूर्णांक
set_match_v1_checkentry(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_set_info_match_v1 *info = par->matchinfo;
	ip_set_id_t index;

	index = ip_set_nfnl_get_byindex(par->net, info->match_set.index);

	अगर (index == IPSET_INVALID_ID) अणु
		pr_info_ratelimited("Cannot find set identified by id %u to match\n",
				    info->match_set.index);
		वापस -ENOENT;
	पूर्ण
	अगर (info->match_set.dim > IPSET_DIM_MAX) अणु
		pr_info_ratelimited("set match dimension is over the limit!\n");
		ip_set_nfnl_put(par->net, info->match_set.index);
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
set_match_v1_destroy(स्थिर काष्ठा xt_mtdtor_param *par)
अणु
	काष्ठा xt_set_info_match_v1 *info = par->matchinfo;

	ip_set_nfnl_put(par->net, info->match_set.index);
पूर्ण

/* Revision 3 match */

अटल bool
set_match_v3(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_set_info_match_v3 *info = par->matchinfo;

	ADT_OPT(opt, xt_family(par), info->match_set.dim,
		info->match_set.flags, info->flags, अच_पूर्णांक_उच्च,
		info->packets.value, info->bytes.value,
		info->packets.op, info->bytes.op);

	अगर (info->packets.op != IPSET_COUNTER_NONE ||
	    info->bytes.op != IPSET_COUNTER_NONE)
		opt.cmdflags |= IPSET_FLAG_MATCH_COUNTERS;

	वापस match_set(info->match_set.index, skb, par, &opt,
			 info->match_set.flags & IPSET_INV_MATCH);
पूर्ण

#घोषणा set_match_v3_checkentry	set_match_v1_checkentry
#घोषणा set_match_v3_destroy	set_match_v1_destroy

/* Revision 4 match */

अटल bool
set_match_v4(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_set_info_match_v4 *info = par->matchinfo;

	ADT_OPT(opt, xt_family(par), info->match_set.dim,
		info->match_set.flags, info->flags, अच_पूर्णांक_उच्च,
		info->packets.value, info->bytes.value,
		info->packets.op, info->bytes.op);

	अगर (info->packets.op != IPSET_COUNTER_NONE ||
	    info->bytes.op != IPSET_COUNTER_NONE)
		opt.cmdflags |= IPSET_FLAG_MATCH_COUNTERS;

	वापस match_set(info->match_set.index, skb, par, &opt,
			 info->match_set.flags & IPSET_INV_MATCH);
पूर्ण

#घोषणा set_match_v4_checkentry	set_match_v1_checkentry
#घोषणा set_match_v4_destroy	set_match_v1_destroy

/* Revision 0 पूर्णांकerface: backward compatible with netfilter/iptables */

अटल अचिन्हित पूर्णांक
set_target_v0(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_set_info_target_v0 *info = par->targinfo;

	ADT_OPT(add_opt, xt_family(par), info->add_set.u.compat.dim,
		info->add_set.u.compat.flags, 0, अच_पूर्णांक_उच्च,
		0, 0, 0, 0);
	ADT_OPT(del_opt, xt_family(par), info->del_set.u.compat.dim,
		info->del_set.u.compat.flags, 0, अच_पूर्णांक_उच्च,
		0, 0, 0, 0);

	अगर (info->add_set.index != IPSET_INVALID_ID)
		ip_set_add(info->add_set.index, skb, par, &add_opt);
	अगर (info->del_set.index != IPSET_INVALID_ID)
		ip_set_del(info->del_set.index, skb, par, &del_opt);

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक
set_target_v0_checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	काष्ठा xt_set_info_target_v0 *info = par->targinfo;
	ip_set_id_t index;

	अगर (info->add_set.index != IPSET_INVALID_ID) अणु
		index = ip_set_nfnl_get_byindex(par->net, info->add_set.index);
		अगर (index == IPSET_INVALID_ID) अणु
			pr_info_ratelimited("Cannot find add_set index %u as target\n",
					    info->add_set.index);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	अगर (info->del_set.index != IPSET_INVALID_ID) अणु
		index = ip_set_nfnl_get_byindex(par->net, info->del_set.index);
		अगर (index == IPSET_INVALID_ID) अणु
			pr_info_ratelimited("Cannot find del_set index %u as target\n",
					    info->del_set.index);
			अगर (info->add_set.index != IPSET_INVALID_ID)
				ip_set_nfnl_put(par->net, info->add_set.index);
			वापस -ENOENT;
		पूर्ण
	पूर्ण
	अगर (info->add_set.u.flags[IPSET_DIM_MAX - 1] != 0 ||
	    info->del_set.u.flags[IPSET_DIM_MAX - 1] != 0) अणु
		pr_info_ratelimited("SET target dimension over the limit!\n");
		अगर (info->add_set.index != IPSET_INVALID_ID)
			ip_set_nfnl_put(par->net, info->add_set.index);
		अगर (info->del_set.index != IPSET_INVALID_ID)
			ip_set_nfnl_put(par->net, info->del_set.index);
		वापस -दुस्फल;
	पूर्ण

	/* Fill out compatibility data */
	compat_flags(&info->add_set);
	compat_flags(&info->del_set);

	वापस 0;
पूर्ण

अटल व्योम
set_target_v0_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	स्थिर काष्ठा xt_set_info_target_v0 *info = par->targinfo;

	अगर (info->add_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->add_set.index);
	अगर (info->del_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->del_set.index);
पूर्ण

/* Revision 1 target */

अटल अचिन्हित पूर्णांक
set_target_v1(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_set_info_target_v1 *info = par->targinfo;

	ADT_OPT(add_opt, xt_family(par), info->add_set.dim,
		info->add_set.flags, 0, अच_पूर्णांक_उच्च,
		0, 0, 0, 0);
	ADT_OPT(del_opt, xt_family(par), info->del_set.dim,
		info->del_set.flags, 0, अच_पूर्णांक_उच्च,
		0, 0, 0, 0);

	अगर (info->add_set.index != IPSET_INVALID_ID)
		ip_set_add(info->add_set.index, skb, par, &add_opt);
	अगर (info->del_set.index != IPSET_INVALID_ID)
		ip_set_del(info->del_set.index, skb, par, &del_opt);

	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक
set_target_v1_checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_set_info_target_v1 *info = par->targinfo;
	ip_set_id_t index;

	अगर (info->add_set.index != IPSET_INVALID_ID) अणु
		index = ip_set_nfnl_get_byindex(par->net, info->add_set.index);
		अगर (index == IPSET_INVALID_ID) अणु
			pr_info_ratelimited("Cannot find add_set index %u as target\n",
					    info->add_set.index);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	अगर (info->del_set.index != IPSET_INVALID_ID) अणु
		index = ip_set_nfnl_get_byindex(par->net, info->del_set.index);
		अगर (index == IPSET_INVALID_ID) अणु
			pr_info_ratelimited("Cannot find del_set index %u as target\n",
					    info->del_set.index);
			अगर (info->add_set.index != IPSET_INVALID_ID)
				ip_set_nfnl_put(par->net, info->add_set.index);
			वापस -ENOENT;
		पूर्ण
	पूर्ण
	अगर (info->add_set.dim > IPSET_DIM_MAX ||
	    info->del_set.dim > IPSET_DIM_MAX) अणु
		pr_info_ratelimited("SET target dimension over the limit!\n");
		अगर (info->add_set.index != IPSET_INVALID_ID)
			ip_set_nfnl_put(par->net, info->add_set.index);
		अगर (info->del_set.index != IPSET_INVALID_ID)
			ip_set_nfnl_put(par->net, info->del_set.index);
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
set_target_v1_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	स्थिर काष्ठा xt_set_info_target_v1 *info = par->targinfo;

	अगर (info->add_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->add_set.index);
	अगर (info->del_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->del_set.index);
पूर्ण

/* Revision 2 target */

अटल अचिन्हित पूर्णांक
set_target_v2(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_set_info_target_v2 *info = par->targinfo;

	ADT_OPT(add_opt, xt_family(par), info->add_set.dim,
		info->add_set.flags, info->flags, info->समयout,
		0, 0, 0, 0);
	ADT_OPT(del_opt, xt_family(par), info->del_set.dim,
		info->del_set.flags, 0, अच_पूर्णांक_उच्च,
		0, 0, 0, 0);

	/* Normalize to fit पूर्णांकo jअगरfies */
	अगर (add_opt.ext.समयout != IPSET_NO_TIMEOUT &&
	    add_opt.ext.समयout > IPSET_MAX_TIMEOUT)
		add_opt.ext.समयout = IPSET_MAX_TIMEOUT;
	अगर (info->add_set.index != IPSET_INVALID_ID)
		ip_set_add(info->add_set.index, skb, par, &add_opt);
	अगर (info->del_set.index != IPSET_INVALID_ID)
		ip_set_del(info->del_set.index, skb, par, &del_opt);

	वापस XT_CONTINUE;
पूर्ण

#घोषणा set_target_v2_checkentry	set_target_v1_checkentry
#घोषणा set_target_v2_destroy		set_target_v1_destroy

/* Revision 3 target */

#घोषणा MOPT(opt, member)	((opt).ext.skbinfo.member)

अटल अचिन्हित पूर्णांक
set_target_v3(काष्ठा sk_buff *skb, स्थिर काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_set_info_target_v3 *info = par->targinfo;
	पूर्णांक ret;

	ADT_OPT(add_opt, xt_family(par), info->add_set.dim,
		info->add_set.flags, info->flags, info->समयout,
		0, 0, 0, 0);
	ADT_OPT(del_opt, xt_family(par), info->del_set.dim,
		info->del_set.flags, 0, अच_पूर्णांक_उच्च,
		0, 0, 0, 0);
	ADT_OPT(map_opt, xt_family(par), info->map_set.dim,
		info->map_set.flags, 0, अच_पूर्णांक_उच्च,
		0, 0, 0, 0);

	/* Normalize to fit पूर्णांकo jअगरfies */
	अगर (add_opt.ext.समयout != IPSET_NO_TIMEOUT &&
	    add_opt.ext.समयout > IPSET_MAX_TIMEOUT)
		add_opt.ext.समयout = IPSET_MAX_TIMEOUT;
	अगर (info->add_set.index != IPSET_INVALID_ID)
		ip_set_add(info->add_set.index, skb, par, &add_opt);
	अगर (info->del_set.index != IPSET_INVALID_ID)
		ip_set_del(info->del_set.index, skb, par, &del_opt);
	अगर (info->map_set.index != IPSET_INVALID_ID) अणु
		map_opt.cmdflags |= info->flags & (IPSET_FLAG_MAP_SKBMARK |
						   IPSET_FLAG_MAP_SKBPRIO |
						   IPSET_FLAG_MAP_SKBQUEUE);
		ret = match_set(info->map_set.index, skb, par, &map_opt,
				info->map_set.flags & IPSET_INV_MATCH);
		अगर (!ret)
			वापस XT_CONTINUE;
		अगर (map_opt.cmdflags & IPSET_FLAG_MAP_SKBMARK)
			skb->mark = (skb->mark & ~MOPT(map_opt,skbmarkmask))
				    ^ MOPT(map_opt, skbmark);
		अगर (map_opt.cmdflags & IPSET_FLAG_MAP_SKBPRIO)
			skb->priority = MOPT(map_opt, skbprio);
		अगर ((map_opt.cmdflags & IPSET_FLAG_MAP_SKBQUEUE) &&
		    skb->dev &&
		    skb->dev->real_num_tx_queues > MOPT(map_opt, skbqueue))
			skb_set_queue_mapping(skb, MOPT(map_opt, skbqueue));
	पूर्ण
	वापस XT_CONTINUE;
पूर्ण

अटल पूर्णांक
set_target_v3_checkentry(स्थिर काष्ठा xt_tgchk_param *par)
अणु
	स्थिर काष्ठा xt_set_info_target_v3 *info = par->targinfo;
	ip_set_id_t index;
	पूर्णांक ret = 0;

	अगर (info->add_set.index != IPSET_INVALID_ID) अणु
		index = ip_set_nfnl_get_byindex(par->net,
						info->add_set.index);
		अगर (index == IPSET_INVALID_ID) अणु
			pr_info_ratelimited("Cannot find add_set index %u as target\n",
					    info->add_set.index);
			वापस -ENOENT;
		पूर्ण
	पूर्ण

	अगर (info->del_set.index != IPSET_INVALID_ID) अणु
		index = ip_set_nfnl_get_byindex(par->net,
						info->del_set.index);
		अगर (index == IPSET_INVALID_ID) अणु
			pr_info_ratelimited("Cannot find del_set index %u as target\n",
					    info->del_set.index);
			ret = -ENOENT;
			जाओ cleanup_add;
		पूर्ण
	पूर्ण

	अगर (info->map_set.index != IPSET_INVALID_ID) अणु
		अगर (म_भेदन(par->table, "mangle", 7)) अणु
			pr_info_ratelimited("--map-set only usable from mangle table\n");
			ret = -EINVAL;
			जाओ cleanup_del;
		पूर्ण
		अगर (((info->flags & IPSET_FLAG_MAP_SKBPRIO) |
		     (info->flags & IPSET_FLAG_MAP_SKBQUEUE)) &&
		     (par->hook_mask & ~(1 << NF_INET_FORWARD |
					 1 << NF_INET_LOCAL_OUT |
					 1 << NF_INET_POST_ROUTING))) अणु
			pr_info_ratelimited("mapping of prio or/and queue is allowed only from OUTPUT/FORWARD/POSTROUTING chains\n");
			ret = -EINVAL;
			जाओ cleanup_del;
		पूर्ण
		index = ip_set_nfnl_get_byindex(par->net,
						info->map_set.index);
		अगर (index == IPSET_INVALID_ID) अणु
			pr_info_ratelimited("Cannot find map_set index %u as target\n",
					    info->map_set.index);
			ret = -ENOENT;
			जाओ cleanup_del;
		पूर्ण
	पूर्ण

	अगर (info->add_set.dim > IPSET_DIM_MAX ||
	    info->del_set.dim > IPSET_DIM_MAX ||
	    info->map_set.dim > IPSET_DIM_MAX) अणु
		pr_info_ratelimited("SET target dimension over the limit!\n");
		ret = -दुस्फल;
		जाओ cleanup_mark;
	पूर्ण

	वापस 0;
cleanup_mark:
	अगर (info->map_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->map_set.index);
cleanup_del:
	अगर (info->del_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->del_set.index);
cleanup_add:
	अगर (info->add_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->add_set.index);
	वापस ret;
पूर्ण

अटल व्योम
set_target_v3_destroy(स्थिर काष्ठा xt_tgdtor_param *par)
अणु
	स्थिर काष्ठा xt_set_info_target_v3 *info = par->targinfo;

	अगर (info->add_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->add_set.index);
	अगर (info->del_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->del_set.index);
	अगर (info->map_set.index != IPSET_INVALID_ID)
		ip_set_nfnl_put(par->net, info->map_set.index);
पूर्ण

अटल काष्ठा xt_match set_matches[] __पढ़ो_mostly = अणु
	अणु
		.name		= "set",
		.family		= NFPROTO_IPV4,
		.revision	= 0,
		.match		= set_match_v0,
		.matchsize	= माप(काष्ठा xt_set_info_match_v0),
		.checkentry	= set_match_v0_checkentry,
		.destroy	= set_match_v0_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "set",
		.family		= NFPROTO_IPV4,
		.revision	= 1,
		.match		= set_match_v1,
		.matchsize	= माप(काष्ठा xt_set_info_match_v1),
		.checkentry	= set_match_v1_checkentry,
		.destroy	= set_match_v1_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "set",
		.family		= NFPROTO_IPV6,
		.revision	= 1,
		.match		= set_match_v1,
		.matchsize	= माप(काष्ठा xt_set_info_match_v1),
		.checkentry	= set_match_v1_checkentry,
		.destroy	= set_match_v1_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	/* --वापस-nomatch flag support */
	अणु
		.name		= "set",
		.family		= NFPROTO_IPV4,
		.revision	= 2,
		.match		= set_match_v1,
		.matchsize	= माप(काष्ठा xt_set_info_match_v1),
		.checkentry	= set_match_v1_checkentry,
		.destroy	= set_match_v1_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "set",
		.family		= NFPROTO_IPV6,
		.revision	= 2,
		.match		= set_match_v1,
		.matchsize	= माप(काष्ठा xt_set_info_match_v1),
		.checkentry	= set_match_v1_checkentry,
		.destroy	= set_match_v1_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	/* counters support: update, match */
	अणु
		.name		= "set",
		.family		= NFPROTO_IPV4,
		.revision	= 3,
		.match		= set_match_v3,
		.matchsize	= माप(काष्ठा xt_set_info_match_v3),
		.checkentry	= set_match_v3_checkentry,
		.destroy	= set_match_v3_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "set",
		.family		= NFPROTO_IPV6,
		.revision	= 3,
		.match		= set_match_v3,
		.matchsize	= माप(काष्ठा xt_set_info_match_v3),
		.checkentry	= set_match_v3_checkentry,
		.destroy	= set_match_v3_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	/* new revision क्रम counters support: update, match */
	अणु
		.name		= "set",
		.family		= NFPROTO_IPV4,
		.revision	= 4,
		.match		= set_match_v4,
		.matchsize	= माप(काष्ठा xt_set_info_match_v4),
		.checkentry	= set_match_v4_checkentry,
		.destroy	= set_match_v4_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "set",
		.family		= NFPROTO_IPV6,
		.revision	= 4,
		.match		= set_match_v4,
		.matchsize	= माप(काष्ठा xt_set_info_match_v4),
		.checkentry	= set_match_v4_checkentry,
		.destroy	= set_match_v4_destroy,
		.me		= THIS_MODULE
	पूर्ण,
पूर्ण;

अटल काष्ठा xt_target set_tarमाला_लो[] __पढ़ो_mostly = अणु
	अणु
		.name		= "SET",
		.revision	= 0,
		.family		= NFPROTO_IPV4,
		.target		= set_target_v0,
		.tarमाला_लोize	= माप(काष्ठा xt_set_info_target_v0),
		.checkentry	= set_target_v0_checkentry,
		.destroy	= set_target_v0_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "SET",
		.revision	= 1,
		.family		= NFPROTO_IPV4,
		.target		= set_target_v1,
		.tarमाला_लोize	= माप(काष्ठा xt_set_info_target_v1),
		.checkentry	= set_target_v1_checkentry,
		.destroy	= set_target_v1_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "SET",
		.revision	= 1,
		.family		= NFPROTO_IPV6,
		.target		= set_target_v1,
		.tarमाला_लोize	= माप(काष्ठा xt_set_info_target_v1),
		.checkentry	= set_target_v1_checkentry,
		.destroy	= set_target_v1_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	/* --समयout and --exist flags support */
	अणु
		.name		= "SET",
		.revision	= 2,
		.family		= NFPROTO_IPV4,
		.target		= set_target_v2,
		.tarमाला_लोize	= माप(काष्ठा xt_set_info_target_v2),
		.checkentry	= set_target_v2_checkentry,
		.destroy	= set_target_v2_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "SET",
		.revision	= 2,
		.family		= NFPROTO_IPV6,
		.target		= set_target_v2,
		.tarमाला_लोize	= माप(काष्ठा xt_set_info_target_v2),
		.checkentry	= set_target_v2_checkentry,
		.destroy	= set_target_v2_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	/* --map-set support */
	अणु
		.name		= "SET",
		.revision	= 3,
		.family		= NFPROTO_IPV4,
		.target		= set_target_v3,
		.tarमाला_लोize	= माप(काष्ठा xt_set_info_target_v3),
		.checkentry	= set_target_v3_checkentry,
		.destroy	= set_target_v3_destroy,
		.me		= THIS_MODULE
	पूर्ण,
	अणु
		.name		= "SET",
		.revision	= 3,
		.family		= NFPROTO_IPV6,
		.target		= set_target_v3,
		.tarमाला_लोize	= माप(काष्ठा xt_set_info_target_v3),
		.checkentry	= set_target_v3_checkentry,
		.destroy	= set_target_v3_destroy,
		.me		= THIS_MODULE
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init xt_set_init(व्योम)
अणु
	पूर्णांक ret = xt_रेजिस्टर_matches(set_matches, ARRAY_SIZE(set_matches));

	अगर (!ret) अणु
		ret = xt_रेजिस्टर_tarमाला_लो(set_tarमाला_लो,
					  ARRAY_SIZE(set_tarमाला_लो));
		अगर (ret)
			xt_unरेजिस्टर_matches(set_matches,
					      ARRAY_SIZE(set_matches));
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास xt_set_fini(व्योम)
अणु
	xt_unरेजिस्टर_matches(set_matches, ARRAY_SIZE(set_matches));
	xt_unरेजिस्टर_tarमाला_लो(set_tarमाला_लो, ARRAY_SIZE(set_tarमाला_लो));
पूर्ण

module_init(xt_set_init);
module_निकास(xt_set_fini);
