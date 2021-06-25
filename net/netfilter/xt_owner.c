<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel module to match various things tied to sockets associated with
 * locally generated outgoing packets.
 *
 * (C) 2000 Marc Boucher <marc@mbsi.ca>
 *
 * Copyright तऊ CC Computer Consultants GmbH, 2007 - 2008
 */
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/file.h>
#समावेश <linux/cred.h>

#समावेश <net/sock.h>
#समावेश <net/inet_sock.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/xt_owner.h>

अटल पूर्णांक owner_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	काष्ठा xt_owner_match_info *info = par->matchinfo;
	काष्ठा net *net = par->net;

	अगर (info->match & ~XT_OWNER_MASK)
		वापस -EINVAL;

	/* Only allow the common हाल where the userns of the ग_लिखोr
	 * matches the userns of the network namespace.
	 */
	अगर ((info->match & (XT_OWNER_UID|XT_OWNER_GID)) &&
	    (current_user_ns() != net->user_ns))
		वापस -EINVAL;

	/* Ensure the uids are valid */
	अगर (info->match & XT_OWNER_UID) अणु
		kuid_t uid_min = make_kuid(net->user_ns, info->uid_min);
		kuid_t uid_max = make_kuid(net->user_ns, info->uid_max);

		अगर (!uid_valid(uid_min) || !uid_valid(uid_max) ||
		    (info->uid_max < info->uid_min) ||
		    uid_lt(uid_max, uid_min)) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Ensure the gids are valid */
	अगर (info->match & XT_OWNER_GID) अणु
		kgid_t gid_min = make_kgid(net->user_ns, info->gid_min);
		kgid_t gid_max = make_kgid(net->user_ns, info->gid_max);

		अगर (!gid_valid(gid_min) || !gid_valid(gid_max) ||
		    (info->gid_max < info->gid_min) ||
		    gid_lt(gid_max, gid_min)) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
owner_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा xt_owner_match_info *info = par->matchinfo;
	स्थिर काष्ठा file *filp;
	काष्ठा sock *sk = skb_to_full_sk(skb);
	काष्ठा net *net = xt_net(par);

	अगर (!sk || !sk->sk_socket || !net_eq(net, sock_net(sk)))
		वापस (info->match ^ info->invert) == 0;
	अन्यथा अगर (info->match & info->invert & XT_OWNER_SOCKET)
		/*
		 * Socket exists but user wanted ! --socket-exists.
		 * (Single ampersands पूर्णांकended.)
		 */
		वापस false;

	filp = sk->sk_socket->file;
	अगर (filp == शून्य)
		वापस ((info->match ^ info->invert) &
		       (XT_OWNER_UID | XT_OWNER_GID)) == 0;

	अगर (info->match & XT_OWNER_UID) अणु
		kuid_t uid_min = make_kuid(net->user_ns, info->uid_min);
		kuid_t uid_max = make_kuid(net->user_ns, info->uid_max);
		अगर ((uid_gte(filp->f_cred->fsuid, uid_min) &&
		     uid_lte(filp->f_cred->fsuid, uid_max)) ^
		    !(info->invert & XT_OWNER_UID))
			वापस false;
	पूर्ण

	अगर (info->match & XT_OWNER_GID) अणु
		अचिन्हित पूर्णांक i, match = false;
		kgid_t gid_min = make_kgid(net->user_ns, info->gid_min);
		kgid_t gid_max = make_kgid(net->user_ns, info->gid_max);
		काष्ठा group_info *gi = filp->f_cred->group_info;

		अगर (gid_gte(filp->f_cred->fsgid, gid_min) &&
		    gid_lte(filp->f_cred->fsgid, gid_max))
			match = true;

		अगर (!match && (info->match & XT_OWNER_SUPPL_GROUPS) && gi) अणु
			क्रम (i = 0; i < gi->ngroups; ++i) अणु
				kgid_t group = gi->gid[i];

				अगर (gid_gte(group, gid_min) &&
				    gid_lte(group, gid_max)) अणु
					match = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (match ^ !(info->invert & XT_OWNER_GID))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा xt_match owner_mt_reg __पढ़ो_mostly = अणु
	.name       = "owner",
	.revision   = 1,
	.family     = NFPROTO_UNSPEC,
	.checkentry = owner_check,
	.match      = owner_mt,
	.matchsize  = माप(काष्ठा xt_owner_match_info),
	.hooks      = (1 << NF_INET_LOCAL_OUT) |
	              (1 << NF_INET_POST_ROUTING),
	.me         = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init owner_mt_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&owner_mt_reg);
पूर्ण

अटल व्योम __निकास owner_mt_निकास(व्योम)
अणु
	xt_unरेजिस्टर_match(&owner_mt_reg);
पूर्ण

module_init(owner_mt_init);
module_निकास(owner_mt_निकास);
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_DESCRIPTION("Xtables: socket owner matching");
MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_owner");
MODULE_ALIAS("ip6t_owner");
