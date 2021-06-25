<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NETLINK      Generic Netlink Family
 *
 * 		Authors:	Jamal Hadi Salim
 * 				Thomas Graf <tgraf@suug.ch>
 *				Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/mutex.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/idr.h>
#समावेश <net/sock.h>
#समावेश <net/genetlink.h>

अटल DEFINE_MUTEX(genl_mutex); /* serialization of message processing */
अटल DECLARE_RWSEM(cb_lock);

atomic_t genl_sk_deकाष्ठाing_cnt = ATOMIC_INIT(0);
DECLARE_WAIT_QUEUE_HEAD(genl_sk_deकाष्ठाing_रुकोq);

व्योम genl_lock(व्योम)
अणु
	mutex_lock(&genl_mutex);
पूर्ण
EXPORT_SYMBOL(genl_lock);

व्योम genl_unlock(व्योम)
अणु
	mutex_unlock(&genl_mutex);
पूर्ण
EXPORT_SYMBOL(genl_unlock);

#अगर_घोषित CONFIG_LOCKDEP
bool lockdep_genl_is_held(व्योम)
अणु
	वापस lockdep_is_held(&genl_mutex);
पूर्ण
EXPORT_SYMBOL(lockdep_genl_is_held);
#पूर्ण_अगर

अटल व्योम genl_lock_all(व्योम)
अणु
	करोwn_ग_लिखो(&cb_lock);
	genl_lock();
पूर्ण

अटल व्योम genl_unlock_all(व्योम)
अणु
	genl_unlock();
	up_ग_लिखो(&cb_lock);
पूर्ण

अटल DEFINE_IDR(genl_fam_idr);

/*
 * Biपंचांगap of multicast groups that are currently in use.
 *
 * To aव्योम an allocation at boot of just one अचिन्हित दीर्घ,
 * declare it global instead.
 * Bit 0 is marked as alपढ़ोy used since group 0 is invalid.
 * Bit 1 is marked as alपढ़ोy used since the drop-monitor code
 * abuses the API and thinks it can अटलally use group 1.
 * That group will typically conflict with other groups that
 * any proper users use.
 * Bit 16 is marked as used since it's used क्रम generic netlink
 * and the code no दीर्घer marks pre-reserved IDs as used.
 * Bit 17 is marked as alपढ़ोy used since the VFS quota code
 * also abused this API and relied on family == group ID, we
 * cater to that by giving it a अटल family and group ID.
 * Bit 18 is marked as alपढ़ोy used since the PMCRAID driver
 * did the same thing as the VFS quota code (maybe copied?)
 */
अटल अचिन्हित दीर्घ mc_group_start = 0x3 | BIT(GENL_ID_CTRL) |
				      BIT(GENL_ID_VFS_DQUOT) |
				      BIT(GENL_ID_PMCRAID);
अटल अचिन्हित दीर्घ *mc_groups = &mc_group_start;
अटल अचिन्हित दीर्घ mc_groups_दीर्घs = 1;

अटल पूर्णांक genl_ctrl_event(पूर्णांक event, स्थिर काष्ठा genl_family *family,
			   स्थिर काष्ठा genl_multicast_group *grp,
			   पूर्णांक grp_id);

अटल स्थिर काष्ठा genl_family *genl_family_find_byid(अचिन्हित पूर्णांक id)
अणु
	वापस idr_find(&genl_fam_idr, id);
पूर्ण

अटल स्थिर काष्ठा genl_family *genl_family_find_byname(अक्षर *name)
अणु
	स्थिर काष्ठा genl_family *family;
	अचिन्हित पूर्णांक id;

	idr_क्रम_each_entry(&genl_fam_idr, family, id)
		अगर (म_भेद(family->name, name) == 0)
			वापस family;

	वापस शून्य;
पूर्ण

अटल पूर्णांक genl_get_cmd_cnt(स्थिर काष्ठा genl_family *family)
अणु
	वापस family->n_ops + family->n_small_ops;
पूर्ण

अटल व्योम genl_op_from_full(स्थिर काष्ठा genl_family *family,
			      अचिन्हित पूर्णांक i, काष्ठा genl_ops *op)
अणु
	*op = family->ops[i];

	अगर (!op->maxattr)
		op->maxattr = family->maxattr;
	अगर (!op->policy)
		op->policy = family->policy;
पूर्ण

अटल पूर्णांक genl_get_cmd_full(u32 cmd, स्थिर काष्ठा genl_family *family,
			     काष्ठा genl_ops *op)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < family->n_ops; i++)
		अगर (family->ops[i].cmd == cmd) अणु
			genl_op_from_full(family, i, op);
			वापस 0;
		पूर्ण

	वापस -ENOENT;
पूर्ण

अटल व्योम genl_op_from_small(स्थिर काष्ठा genl_family *family,
			       अचिन्हित पूर्णांक i, काष्ठा genl_ops *op)
अणु
	स_रखो(op, 0, माप(*op));
	op->करोit	= family->small_ops[i].करोit;
	op->dumpit	= family->small_ops[i].dumpit;
	op->cmd		= family->small_ops[i].cmd;
	op->पूर्णांकernal_flags = family->small_ops[i].पूर्णांकernal_flags;
	op->flags	= family->small_ops[i].flags;
	op->validate	= family->small_ops[i].validate;

	op->maxattr = family->maxattr;
	op->policy = family->policy;
पूर्ण

अटल पूर्णांक genl_get_cmd_small(u32 cmd, स्थिर काष्ठा genl_family *family,
			      काष्ठा genl_ops *op)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < family->n_small_ops; i++)
		अगर (family->small_ops[i].cmd == cmd) अणु
			genl_op_from_small(family, i, op);
			वापस 0;
		पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक genl_get_cmd(u32 cmd, स्थिर काष्ठा genl_family *family,
			काष्ठा genl_ops *op)
अणु
	अगर (!genl_get_cmd_full(cmd, family, op))
		वापस 0;
	वापस genl_get_cmd_small(cmd, family, op);
पूर्ण

अटल व्योम genl_get_cmd_by_index(अचिन्हित पूर्णांक i,
				  स्थिर काष्ठा genl_family *family,
				  काष्ठा genl_ops *op)
अणु
	अगर (i < family->n_ops)
		genl_op_from_full(family, i, op);
	अन्यथा अगर (i < family->n_ops + family->n_small_ops)
		genl_op_from_small(family, i - family->n_ops, op);
	अन्यथा
		WARN_ON_ONCE(1);
पूर्ण

अटल पूर्णांक genl_allocate_reserve_groups(पूर्णांक n_groups, पूर्णांक *first_id)
अणु
	अचिन्हित दीर्घ *new_groups;
	पूर्णांक start = 0;
	पूर्णांक i;
	पूर्णांक id;
	bool fits;

	करो अणु
		अगर (start == 0)
			id = find_first_zero_bit(mc_groups,
						 mc_groups_दीर्घs *
						 BITS_PER_LONG);
		अन्यथा
			id = find_next_zero_bit(mc_groups,
						mc_groups_दीर्घs * BITS_PER_LONG,
						start);

		fits = true;
		क्रम (i = id;
		     i < min_t(पूर्णांक, id + n_groups,
			       mc_groups_दीर्घs * BITS_PER_LONG);
		     i++) अणु
			अगर (test_bit(i, mc_groups)) अणु
				start = i;
				fits = false;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (id + n_groups > mc_groups_दीर्घs * BITS_PER_LONG) अणु
			अचिन्हित दीर्घ new_दीर्घs = mc_groups_दीर्घs +
						  BITS_TO_LONGS(n_groups);
			माप_प्रकार nlen = new_दीर्घs * माप(अचिन्हित दीर्घ);

			अगर (mc_groups == &mc_group_start) अणु
				new_groups = kzalloc(nlen, GFP_KERNEL);
				अगर (!new_groups)
					वापस -ENOMEM;
				mc_groups = new_groups;
				*mc_groups = mc_group_start;
			पूर्ण अन्यथा अणु
				new_groups = kपुनः_स्मृति(mc_groups, nlen,
						      GFP_KERNEL);
				अगर (!new_groups)
					वापस -ENOMEM;
				mc_groups = new_groups;
				क्रम (i = 0; i < BITS_TO_LONGS(n_groups); i++)
					mc_groups[mc_groups_दीर्घs + i] = 0;
			पूर्ण
			mc_groups_दीर्घs = new_दीर्घs;
		पूर्ण
	पूर्ण जबतक (!fits);

	क्रम (i = id; i < id + n_groups; i++)
		set_bit(i, mc_groups);
	*first_id = id;
	वापस 0;
पूर्ण

अटल काष्ठा genl_family genl_ctrl;

अटल पूर्णांक genl_validate_assign_mc_groups(काष्ठा genl_family *family)
अणु
	पूर्णांक first_id;
	पूर्णांक n_groups = family->n_mcgrps;
	पूर्णांक err = 0, i;
	bool groups_allocated = false;

	अगर (!n_groups)
		वापस 0;

	क्रम (i = 0; i < n_groups; i++) अणु
		स्थिर काष्ठा genl_multicast_group *grp = &family->mcgrps[i];

		अगर (WARN_ON(grp->name[0] == '\0'))
			वापस -EINVAL;
		अगर (WARN_ON(स_प्रथम(grp->name, '\0', GENL_NAMSIZ) == शून्य))
			वापस -EINVAL;
	पूर्ण

	/* special-हाल our own group and hacks */
	अगर (family == &genl_ctrl) अणु
		first_id = GENL_ID_CTRL;
		BUG_ON(n_groups != 1);
	पूर्ण अन्यथा अगर (म_भेद(family->name, "NET_DM") == 0) अणु
		first_id = 1;
		BUG_ON(n_groups != 1);
	पूर्ण अन्यथा अगर (family->id == GENL_ID_VFS_DQUOT) अणु
		first_id = GENL_ID_VFS_DQUOT;
		BUG_ON(n_groups != 1);
	पूर्ण अन्यथा अगर (family->id == GENL_ID_PMCRAID) अणु
		first_id = GENL_ID_PMCRAID;
		BUG_ON(n_groups != 1);
	पूर्ण अन्यथा अणु
		groups_allocated = true;
		err = genl_allocate_reserve_groups(n_groups, &first_id);
		अगर (err)
			वापस err;
	पूर्ण

	family->mcgrp_offset = first_id;

	/* अगर still initializing, can't and don't need to पुनः_स्मृति biपंचांगaps */
	अगर (!init_net.genl_sock)
		वापस 0;

	अगर (family->netnsok) अणु
		काष्ठा net *net;

		netlink_table_grab();
		rcu_पढ़ो_lock();
		क्रम_each_net_rcu(net) अणु
			err = __netlink_change_ngroups(net->genl_sock,
					mc_groups_दीर्घs * BITS_PER_LONG);
			अगर (err) अणु
				/*
				 * No need to roll back, can only fail अगर
				 * memory allocation fails and then the
				 * number of _possible_ groups has been
				 * increased on some sockets which is ok.
				 */
				अवरोध;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
		netlink_table_ungrab();
	पूर्ण अन्यथा अणु
		err = netlink_change_ngroups(init_net.genl_sock,
					     mc_groups_दीर्घs * BITS_PER_LONG);
	पूर्ण

	अगर (groups_allocated && err) अणु
		क्रम (i = 0; i < family->n_mcgrps; i++)
			clear_bit(family->mcgrp_offset + i, mc_groups);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम genl_unरेजिस्टर_mc_groups(स्थिर काष्ठा genl_family *family)
अणु
	काष्ठा net *net;
	पूर्णांक i;

	netlink_table_grab();
	rcu_पढ़ो_lock();
	क्रम_each_net_rcu(net) अणु
		क्रम (i = 0; i < family->n_mcgrps; i++)
			__netlink_clear_multicast_users(
				net->genl_sock, family->mcgrp_offset + i);
	पूर्ण
	rcu_पढ़ो_unlock();
	netlink_table_ungrab();

	क्रम (i = 0; i < family->n_mcgrps; i++) अणु
		पूर्णांक grp_id = family->mcgrp_offset + i;

		अगर (grp_id != 1)
			clear_bit(grp_id, mc_groups);
		genl_ctrl_event(CTRL_CMD_DELMCAST_GRP, family,
				&family->mcgrps[i], grp_id);
	पूर्ण
पूर्ण

अटल पूर्णांक genl_validate_ops(स्थिर काष्ठा genl_family *family)
अणु
	पूर्णांक i, j;

	अगर (WARN_ON(family->n_ops && !family->ops) ||
	    WARN_ON(family->n_small_ops && !family->small_ops))
		वापस -EINVAL;

	क्रम (i = 0; i < genl_get_cmd_cnt(family); i++) अणु
		काष्ठा genl_ops op;

		genl_get_cmd_by_index(i, family, &op);
		अगर (op.dumpit == शून्य && op.करोit == शून्य)
			वापस -EINVAL;
		क्रम (j = i + 1; j < genl_get_cmd_cnt(family); j++) अणु
			काष्ठा genl_ops op2;

			genl_get_cmd_by_index(j, family, &op2);
			अगर (op.cmd == op2.cmd)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * genl_रेजिस्टर_family - रेजिस्टर a generic netlink family
 * @family: generic netlink family
 *
 * Registers the specअगरied family after validating it first. Only one
 * family may be रेजिस्टरed with the same family name or identअगरier.
 *
 * The family's ops, multicast groups and module poपूर्णांकer must alपढ़ोy
 * be asचिन्हित.
 *
 * Return 0 on success or a negative error code.
 */
पूर्णांक genl_रेजिस्टर_family(काष्ठा genl_family *family)
अणु
	पूर्णांक err, i;
	पूर्णांक start = GENL_START_ALLOC, end = GENL_MAX_ID;

	err = genl_validate_ops(family);
	अगर (err)
		वापस err;

	genl_lock_all();

	अगर (genl_family_find_byname(family->name)) अणु
		err = -EEXIST;
		जाओ errout_locked;
	पूर्ण

	/*
	 * Sadly, a few हालs need to be special-हालd
	 * due to them having previously abused the API
	 * and having used their family ID also as their
	 * multicast group ID, so we use reserved IDs
	 * क्रम both to be sure we can करो that mapping.
	 */
	अगर (family == &genl_ctrl) अणु
		/* and this needs to be special क्रम initial family lookups */
		start = end = GENL_ID_CTRL;
	पूर्ण अन्यथा अगर (म_भेद(family->name, "pmcraid") == 0) अणु
		start = end = GENL_ID_PMCRAID;
	पूर्ण अन्यथा अगर (म_भेद(family->name, "VFS_DQUOT") == 0) अणु
		start = end = GENL_ID_VFS_DQUOT;
	पूर्ण

	family->id = idr_alloc_cyclic(&genl_fam_idr, family,
				      start, end + 1, GFP_KERNEL);
	अगर (family->id < 0) अणु
		err = family->id;
		जाओ errout_locked;
	पूर्ण

	err = genl_validate_assign_mc_groups(family);
	अगर (err)
		जाओ errout_हटाओ;

	genl_unlock_all();

	/* send all events */
	genl_ctrl_event(CTRL_CMD_NEWFAMILY, family, शून्य, 0);
	क्रम (i = 0; i < family->n_mcgrps; i++)
		genl_ctrl_event(CTRL_CMD_NEWMCAST_GRP, family,
				&family->mcgrps[i], family->mcgrp_offset + i);

	वापस 0;

errout_हटाओ:
	idr_हटाओ(&genl_fam_idr, family->id);
errout_locked:
	genl_unlock_all();
	वापस err;
पूर्ण
EXPORT_SYMBOL(genl_रेजिस्टर_family);

/**
 * genl_unरेजिस्टर_family - unरेजिस्टर generic netlink family
 * @family: generic netlink family
 *
 * Unरेजिस्टरs the specअगरied family.
 *
 * Returns 0 on success or a negative error code.
 */
पूर्णांक genl_unरेजिस्टर_family(स्थिर काष्ठा genl_family *family)
अणु
	genl_lock_all();

	अगर (!genl_family_find_byid(family->id)) अणु
		genl_unlock_all();
		वापस -ENOENT;
	पूर्ण

	genl_unरेजिस्टर_mc_groups(family);

	idr_हटाओ(&genl_fam_idr, family->id);

	up_ग_लिखो(&cb_lock);
	रुको_event(genl_sk_deकाष्ठाing_रुकोq,
		   atomic_पढ़ो(&genl_sk_deकाष्ठाing_cnt) == 0);
	genl_unlock();

	genl_ctrl_event(CTRL_CMD_DELFAMILY, family, शून्य, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(genl_unरेजिस्टर_family);

/**
 * genlmsg_put - Add generic netlink header to netlink message
 * @skb: socket buffer holding the message
 * @portid: netlink portid the message is addressed to
 * @seq: sequence number (usually the one of the sender)
 * @family: generic netlink family
 * @flags: netlink message flags
 * @cmd: generic netlink command
 *
 * Returns poपूर्णांकer to user specअगरic header
 */
व्योम *genlmsg_put(काष्ठा sk_buff *skb, u32 portid, u32 seq,
		  स्थिर काष्ठा genl_family *family, पूर्णांक flags, u8 cmd)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा genlmsghdr *hdr;

	nlh = nlmsg_put(skb, portid, seq, family->id, GENL_HDRLEN +
			family->hdrsize, flags);
	अगर (nlh == शून्य)
		वापस शून्य;

	hdr = nlmsg_data(nlh);
	hdr->cmd = cmd;
	hdr->version = family->version;
	hdr->reserved = 0;

	वापस (अक्षर *) hdr + GENL_HDRLEN;
पूर्ण
EXPORT_SYMBOL(genlmsg_put);

अटल काष्ठा genl_dumpit_info *genl_dumpit_info_alloc(व्योम)
अणु
	वापस kदो_स्मृति(माप(काष्ठा genl_dumpit_info), GFP_KERNEL);
पूर्ण

अटल व्योम genl_dumpit_info_मुक्त(स्थिर काष्ठा genl_dumpit_info *info)
अणु
	kमुक्त(info);
पूर्ण

अटल काष्ठा nlattr **
genl_family_rcv_msg_attrs_parse(स्थिर काष्ठा genl_family *family,
				काष्ठा nlmsghdr *nlh,
				काष्ठा netlink_ext_ack *extack,
				स्थिर काष्ठा genl_ops *ops,
				पूर्णांक hdrlen,
				क्रमागत genl_validate_flags no_strict_flag)
अणु
	क्रमागत netlink_validation validate = ops->validate & no_strict_flag ?
					   NL_VALIDATE_LIBERAL :
					   NL_VALIDATE_STRICT;
	काष्ठा nlattr **attrbuf;
	पूर्णांक err;

	अगर (!ops->maxattr)
		वापस शून्य;

	attrbuf = kदो_स्मृति_array(ops->maxattr + 1,
				माप(काष्ठा nlattr *), GFP_KERNEL);
	अगर (!attrbuf)
		वापस ERR_PTR(-ENOMEM);

	err = __nlmsg_parse(nlh, hdrlen, attrbuf, ops->maxattr, ops->policy,
			    validate, extack);
	अगर (err) अणु
		kमुक्त(attrbuf);
		वापस ERR_PTR(err);
	पूर्ण
	वापस attrbuf;
पूर्ण

अटल व्योम genl_family_rcv_msg_attrs_मुक्त(काष्ठा nlattr **attrbuf)
अणु
	kमुक्त(attrbuf);
पूर्ण

काष्ठा genl_start_context अणु
	स्थिर काष्ठा genl_family *family;
	काष्ठा nlmsghdr *nlh;
	काष्ठा netlink_ext_ack *extack;
	स्थिर काष्ठा genl_ops *ops;
	पूर्णांक hdrlen;
पूर्ण;

अटल पूर्णांक genl_start(काष्ठा netlink_callback *cb)
अणु
	काष्ठा genl_start_context *ctx = cb->data;
	स्थिर काष्ठा genl_ops *ops = ctx->ops;
	काष्ठा genl_dumpit_info *info;
	काष्ठा nlattr **attrs = शून्य;
	पूर्णांक rc = 0;

	अगर (ops->validate & GENL_DONT_VALIDATE_DUMP)
		जाओ no_attrs;

	अगर (ctx->nlh->nlmsg_len < nlmsg_msg_size(ctx->hdrlen))
		वापस -EINVAL;

	attrs = genl_family_rcv_msg_attrs_parse(ctx->family, ctx->nlh, ctx->extack,
						ops, ctx->hdrlen,
						GENL_DONT_VALIDATE_DUMP_STRICT);
	अगर (IS_ERR(attrs))
		वापस PTR_ERR(attrs);

no_attrs:
	info = genl_dumpit_info_alloc();
	अगर (!info) अणु
		genl_family_rcv_msg_attrs_मुक्त(attrs);
		वापस -ENOMEM;
	पूर्ण
	info->family = ctx->family;
	info->op = *ops;
	info->attrs = attrs;

	cb->data = info;
	अगर (ops->start) अणु
		अगर (!ctx->family->parallel_ops)
			genl_lock();
		rc = ops->start(cb);
		अगर (!ctx->family->parallel_ops)
			genl_unlock();
	पूर्ण

	अगर (rc) अणु
		genl_family_rcv_msg_attrs_मुक्त(info->attrs);
		genl_dumpit_info_मुक्त(info);
		cb->data = शून्य;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक genl_lock_dumpit(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा genl_ops *ops = &genl_dumpit_info(cb)->op;
	पूर्णांक rc;

	genl_lock();
	rc = ops->dumpit(skb, cb);
	genl_unlock();
	वापस rc;
पूर्ण

अटल पूर्णांक genl_lock_करोne(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	स्थिर काष्ठा genl_ops *ops = &info->op;
	पूर्णांक rc = 0;

	अगर (ops->करोne) अणु
		genl_lock();
		rc = ops->करोne(cb);
		genl_unlock();
	पूर्ण
	genl_family_rcv_msg_attrs_मुक्त(info->attrs);
	genl_dumpit_info_मुक्त(info);
	वापस rc;
पूर्ण

अटल पूर्णांक genl_parallel_करोne(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	स्थिर काष्ठा genl_ops *ops = &info->op;
	पूर्णांक rc = 0;

	अगर (ops->करोne)
		rc = ops->करोne(cb);
	genl_family_rcv_msg_attrs_मुक्त(info->attrs);
	genl_dumpit_info_मुक्त(info);
	वापस rc;
पूर्ण

अटल पूर्णांक genl_family_rcv_msg_dumpit(स्थिर काष्ठा genl_family *family,
				      काष्ठा sk_buff *skb,
				      काष्ठा nlmsghdr *nlh,
				      काष्ठा netlink_ext_ack *extack,
				      स्थिर काष्ठा genl_ops *ops,
				      पूर्णांक hdrlen, काष्ठा net *net)
अणु
	काष्ठा genl_start_context ctx;
	पूर्णांक err;

	अगर (!ops->dumpit)
		वापस -EOPNOTSUPP;

	ctx.family = family;
	ctx.nlh = nlh;
	ctx.extack = extack;
	ctx.ops = ops;
	ctx.hdrlen = hdrlen;

	अगर (!family->parallel_ops) अणु
		काष्ठा netlink_dump_control c = अणु
			.module = family->module,
			.data = &ctx,
			.start = genl_start,
			.dump = genl_lock_dumpit,
			.करोne = genl_lock_करोne,
		पूर्ण;

		genl_unlock();
		err = __netlink_dump_start(net->genl_sock, skb, nlh, &c);
		genl_lock();
	पूर्ण अन्यथा अणु
		काष्ठा netlink_dump_control c = अणु
			.module = family->module,
			.data = &ctx,
			.start = genl_start,
			.dump = ops->dumpit,
			.करोne = genl_parallel_करोne,
		पूर्ण;

		err = __netlink_dump_start(net->genl_sock, skb, nlh, &c);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक genl_family_rcv_msg_करोit(स्थिर काष्ठा genl_family *family,
				    काष्ठा sk_buff *skb,
				    काष्ठा nlmsghdr *nlh,
				    काष्ठा netlink_ext_ack *extack,
				    स्थिर काष्ठा genl_ops *ops,
				    पूर्णांक hdrlen, काष्ठा net *net)
अणु
	काष्ठा nlattr **attrbuf;
	काष्ठा genl_info info;
	पूर्णांक err;

	अगर (!ops->करोit)
		वापस -EOPNOTSUPP;

	attrbuf = genl_family_rcv_msg_attrs_parse(family, nlh, extack,
						  ops, hdrlen,
						  GENL_DONT_VALIDATE_STRICT);
	अगर (IS_ERR(attrbuf))
		वापस PTR_ERR(attrbuf);

	info.snd_seq = nlh->nlmsg_seq;
	info.snd_portid = NETLINK_CB(skb).portid;
	info.nlhdr = nlh;
	info.genlhdr = nlmsg_data(nlh);
	info.userhdr = nlmsg_data(nlh) + GENL_HDRLEN;
	info.attrs = attrbuf;
	info.extack = extack;
	genl_info_net_set(&info, net);
	स_रखो(&info.user_ptr, 0, माप(info.user_ptr));

	अगर (family->pre_करोit) अणु
		err = family->pre_करोit(ops, skb, &info);
		अगर (err)
			जाओ out;
	पूर्ण

	err = ops->करोit(skb, &info);

	अगर (family->post_करोit)
		family->post_करोit(ops, skb, &info);

out:
	genl_family_rcv_msg_attrs_मुक्त(attrbuf);

	वापस err;
पूर्ण

अटल पूर्णांक genl_family_rcv_msg(स्थिर काष्ठा genl_family *family,
			       काष्ठा sk_buff *skb,
			       काष्ठा nlmsghdr *nlh,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा genlmsghdr *hdr = nlmsg_data(nlh);
	काष्ठा genl_ops op;
	पूर्णांक hdrlen;

	/* this family करोesn't exist in this netns */
	अगर (!family->netnsok && !net_eq(net, &init_net))
		वापस -ENOENT;

	hdrlen = GENL_HDRLEN + family->hdrsize;
	अगर (nlh->nlmsg_len < nlmsg_msg_size(hdrlen))
		वापस -EINVAL;

	अगर (genl_get_cmd(hdr->cmd, family, &op))
		वापस -EOPNOTSUPP;

	अगर ((op.flags & GENL_ADMIN_PERM) &&
	    !netlink_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर ((op.flags & GENL_UNS_ADMIN_PERM) &&
	    !netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर ((nlh->nlmsg_flags & NLM_F_DUMP) == NLM_F_DUMP)
		वापस genl_family_rcv_msg_dumpit(family, skb, nlh, extack,
						  &op, hdrlen, net);
	अन्यथा
		वापस genl_family_rcv_msg_करोit(family, skb, nlh, extack,
						&op, hdrlen, net);
पूर्ण

अटल पूर्णांक genl_rcv_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा genl_family *family;
	पूर्णांक err;

	family = genl_family_find_byid(nlh->nlmsg_type);
	अगर (family == शून्य)
		वापस -ENOENT;

	अगर (!family->parallel_ops)
		genl_lock();

	err = genl_family_rcv_msg(family, skb, nlh, extack);

	अगर (!family->parallel_ops)
		genl_unlock();

	वापस err;
पूर्ण

अटल व्योम genl_rcv(काष्ठा sk_buff *skb)
अणु
	करोwn_पढ़ो(&cb_lock);
	netlink_rcv_skb(skb, &genl_rcv_msg);
	up_पढ़ो(&cb_lock);
पूर्ण

/**************************************************************************
 * Controller
 **************************************************************************/

अटल काष्ठा genl_family genl_ctrl;

अटल पूर्णांक ctrl_fill_info(स्थिर काष्ठा genl_family *family, u32 portid, u32 seq,
			  u32 flags, काष्ठा sk_buff *skb, u8 cmd)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(skb, portid, seq, &genl_ctrl, flags, cmd);
	अगर (hdr == शून्य)
		वापस -1;

	अगर (nla_put_string(skb, CTRL_ATTR_FAMILY_NAME, family->name) ||
	    nla_put_u16(skb, CTRL_ATTR_FAMILY_ID, family->id) ||
	    nla_put_u32(skb, CTRL_ATTR_VERSION, family->version) ||
	    nla_put_u32(skb, CTRL_ATTR_HDRSIZE, family->hdrsize) ||
	    nla_put_u32(skb, CTRL_ATTR_MAXATTR, family->maxattr))
		जाओ nla_put_failure;

	अगर (genl_get_cmd_cnt(family)) अणु
		काष्ठा nlattr *nla_ops;
		पूर्णांक i;

		nla_ops = nla_nest_start_noflag(skb, CTRL_ATTR_OPS);
		अगर (nla_ops == शून्य)
			जाओ nla_put_failure;

		क्रम (i = 0; i < genl_get_cmd_cnt(family); i++) अणु
			काष्ठा nlattr *nest;
			काष्ठा genl_ops op;
			u32 op_flags;

			genl_get_cmd_by_index(i, family, &op);
			op_flags = op.flags;
			अगर (op.dumpit)
				op_flags |= GENL_CMD_CAP_DUMP;
			अगर (op.करोit)
				op_flags |= GENL_CMD_CAP_DO;
			अगर (op.policy)
				op_flags |= GENL_CMD_CAP_HASPOL;

			nest = nla_nest_start_noflag(skb, i + 1);
			अगर (nest == शून्य)
				जाओ nla_put_failure;

			अगर (nla_put_u32(skb, CTRL_ATTR_OP_ID, op.cmd) ||
			    nla_put_u32(skb, CTRL_ATTR_OP_FLAGS, op_flags))
				जाओ nla_put_failure;

			nla_nest_end(skb, nest);
		पूर्ण

		nla_nest_end(skb, nla_ops);
	पूर्ण

	अगर (family->n_mcgrps) अणु
		काष्ठा nlattr *nla_grps;
		पूर्णांक i;

		nla_grps = nla_nest_start_noflag(skb, CTRL_ATTR_MCAST_GROUPS);
		अगर (nla_grps == शून्य)
			जाओ nla_put_failure;

		क्रम (i = 0; i < family->n_mcgrps; i++) अणु
			काष्ठा nlattr *nest;
			स्थिर काष्ठा genl_multicast_group *grp;

			grp = &family->mcgrps[i];

			nest = nla_nest_start_noflag(skb, i + 1);
			अगर (nest == शून्य)
				जाओ nla_put_failure;

			अगर (nla_put_u32(skb, CTRL_ATTR_MCAST_GRP_ID,
					family->mcgrp_offset + i) ||
			    nla_put_string(skb, CTRL_ATTR_MCAST_GRP_NAME,
					   grp->name))
				जाओ nla_put_failure;

			nla_nest_end(skb, nest);
		पूर्ण
		nla_nest_end(skb, nla_grps);
	पूर्ण

	genlmsg_end(skb, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ctrl_fill_mcgrp_info(स्थिर काष्ठा genl_family *family,
				स्थिर काष्ठा genl_multicast_group *grp,
				पूर्णांक grp_id, u32 portid, u32 seq, u32 flags,
				काष्ठा sk_buff *skb, u8 cmd)
अणु
	व्योम *hdr;
	काष्ठा nlattr *nla_grps;
	काष्ठा nlattr *nest;

	hdr = genlmsg_put(skb, portid, seq, &genl_ctrl, flags, cmd);
	अगर (hdr == शून्य)
		वापस -1;

	अगर (nla_put_string(skb, CTRL_ATTR_FAMILY_NAME, family->name) ||
	    nla_put_u16(skb, CTRL_ATTR_FAMILY_ID, family->id))
		जाओ nla_put_failure;

	nla_grps = nla_nest_start_noflag(skb, CTRL_ATTR_MCAST_GROUPS);
	अगर (nla_grps == शून्य)
		जाओ nla_put_failure;

	nest = nla_nest_start_noflag(skb, 1);
	अगर (nest == शून्य)
		जाओ nla_put_failure;

	अगर (nla_put_u32(skb, CTRL_ATTR_MCAST_GRP_ID, grp_id) ||
	    nla_put_string(skb, CTRL_ATTR_MCAST_GRP_NAME,
			   grp->name))
		जाओ nla_put_failure;

	nla_nest_end(skb, nest);
	nla_nest_end(skb, nla_grps);

	genlmsg_end(skb, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक ctrl_dumpfamily(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक n = 0;
	काष्ठा genl_family *rt;
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक fams_to_skip = cb->args[0];
	अचिन्हित पूर्णांक id;

	idr_क्रम_each_entry(&genl_fam_idr, rt, id) अणु
		अगर (!rt->netnsok && !net_eq(net, &init_net))
			जारी;

		अगर (n++ < fams_to_skip)
			जारी;

		अगर (ctrl_fill_info(rt, NETLINK_CB(cb->skb).portid,
				   cb->nlh->nlmsg_seq, NLM_F_MULTI,
				   skb, CTRL_CMD_NEWFAMILY) < 0) अणु
			n--;
			अवरोध;
		पूर्ण
	पूर्ण

	cb->args[0] = n;
	वापस skb->len;
पूर्ण

अटल काष्ठा sk_buff *ctrl_build_family_msg(स्थिर काष्ठा genl_family *family,
					     u32 portid, पूर्णांक seq, u8 cmd)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (skb == शून्य)
		वापस ERR_PTR(-ENOBUFS);

	err = ctrl_fill_info(family, portid, seq, 0, skb, cmd);
	अगर (err < 0) अणु
		nlmsg_मुक्त(skb);
		वापस ERR_PTR(err);
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ctrl_build_mcgrp_msg(स्थिर काष्ठा genl_family *family,
		     स्थिर काष्ठा genl_multicast_group *grp,
		     पूर्णांक grp_id, u32 portid, पूर्णांक seq, u8 cmd)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (skb == शून्य)
		वापस ERR_PTR(-ENOBUFS);

	err = ctrl_fill_mcgrp_info(family, grp, grp_id, portid,
				   seq, 0, skb, cmd);
	अगर (err < 0) अणु
		nlmsg_मुक्त(skb);
		वापस ERR_PTR(err);
	पूर्ण

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा nla_policy ctrl_policy_family[] = अणु
	[CTRL_ATTR_FAMILY_ID]	= अणु .type = NLA_U16 पूर्ण,
	[CTRL_ATTR_FAMILY_NAME]	= अणु .type = NLA_NUL_STRING,
				    .len = GENL_NAMSIZ - 1 पूर्ण,
पूर्ण;

अटल पूर्णांक ctrl_getfamily(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	स्थिर काष्ठा genl_family *res = शून्य;
	पूर्णांक err = -EINVAL;

	अगर (info->attrs[CTRL_ATTR_FAMILY_ID]) अणु
		u16 id = nla_get_u16(info->attrs[CTRL_ATTR_FAMILY_ID]);
		res = genl_family_find_byid(id);
		err = -ENOENT;
	पूर्ण

	अगर (info->attrs[CTRL_ATTR_FAMILY_NAME]) अणु
		अक्षर *name;

		name = nla_data(info->attrs[CTRL_ATTR_FAMILY_NAME]);
		res = genl_family_find_byname(name);
#अगर_घोषित CONFIG_MODULES
		अगर (res == शून्य) अणु
			genl_unlock();
			up_पढ़ो(&cb_lock);
			request_module("net-pf-%d-proto-%d-family-%s",
				       PF_NETLINK, NETLINK_GENERIC, name);
			करोwn_पढ़ो(&cb_lock);
			genl_lock();
			res = genl_family_find_byname(name);
		पूर्ण
#पूर्ण_अगर
		err = -ENOENT;
	पूर्ण

	अगर (res == शून्य)
		वापस err;

	अगर (!res->netnsok && !net_eq(genl_info_net(info), &init_net)) अणु
		/* family करोesn't exist here */
		वापस -ENOENT;
	पूर्ण

	msg = ctrl_build_family_msg(res, info->snd_portid, info->snd_seq,
				    CTRL_CMD_NEWFAMILY);
	अगर (IS_ERR(msg))
		वापस PTR_ERR(msg);

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक genl_ctrl_event(पूर्णांक event, स्थिर काष्ठा genl_family *family,
			   स्थिर काष्ठा genl_multicast_group *grp,
			   पूर्णांक grp_id)
अणु
	काष्ठा sk_buff *msg;

	/* genl is still initialising */
	अगर (!init_net.genl_sock)
		वापस 0;

	चयन (event) अणु
	हाल CTRL_CMD_NEWFAMILY:
	हाल CTRL_CMD_DELFAMILY:
		WARN_ON(grp);
		msg = ctrl_build_family_msg(family, 0, 0, event);
		अवरोध;
	हाल CTRL_CMD_NEWMCAST_GRP:
	हाल CTRL_CMD_DELMCAST_GRP:
		BUG_ON(!grp);
		msg = ctrl_build_mcgrp_msg(family, grp, grp_id, 0, 0, event);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR(msg))
		वापस PTR_ERR(msg);

	अगर (!family->netnsok) अणु
		genlmsg_multicast_netns(&genl_ctrl, &init_net, msg, 0,
					0, GFP_KERNEL);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_lock();
		genlmsg_multicast_allns(&genl_ctrl, msg, 0,
					0, GFP_ATOMIC);
		rcu_पढ़ो_unlock();
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा ctrl_dump_policy_ctx अणु
	काष्ठा netlink_policy_dump_state *state;
	स्थिर काष्ठा genl_family *rt;
	अचिन्हित पूर्णांक opidx;
	u32 op;
	u16 fam_id;
	u8 policies:1,
	   single_op:1;
पूर्ण;

अटल स्थिर काष्ठा nla_policy ctrl_policy_policy[] = अणु
	[CTRL_ATTR_FAMILY_ID]	= अणु .type = NLA_U16 पूर्ण,
	[CTRL_ATTR_FAMILY_NAME]	= अणु .type = NLA_NUL_STRING,
				    .len = GENL_NAMSIZ - 1 पूर्ण,
	[CTRL_ATTR_OP]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक ctrl_dumppolicy_start(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	काष्ठा ctrl_dump_policy_ctx *ctx = (व्योम *)cb->ctx;
	काष्ठा nlattr **tb = info->attrs;
	स्थिर काष्ठा genl_family *rt;
	काष्ठा genl_ops op;
	पूर्णांक err, i;

	BUILD_BUG_ON(माप(*ctx) > माप(cb->ctx));

	अगर (!tb[CTRL_ATTR_FAMILY_ID] && !tb[CTRL_ATTR_FAMILY_NAME])
		वापस -EINVAL;

	अगर (tb[CTRL_ATTR_FAMILY_ID]) अणु
		ctx->fam_id = nla_get_u16(tb[CTRL_ATTR_FAMILY_ID]);
	पूर्ण अन्यथा अणु
		rt = genl_family_find_byname(
			nla_data(tb[CTRL_ATTR_FAMILY_NAME]));
		अगर (!rt)
			वापस -ENOENT;
		ctx->fam_id = rt->id;
	पूर्ण

	rt = genl_family_find_byid(ctx->fam_id);
	अगर (!rt)
		वापस -ENOENT;

	ctx->rt = rt;

	अगर (tb[CTRL_ATTR_OP]) अणु
		ctx->single_op = true;
		ctx->op = nla_get_u32(tb[CTRL_ATTR_OP]);

		err = genl_get_cmd(ctx->op, rt, &op);
		अगर (err) अणु
			NL_SET_BAD_ATTR(cb->extack, tb[CTRL_ATTR_OP]);
			वापस err;
		पूर्ण

		अगर (!op.policy)
			वापस -ENODATA;

		वापस netlink_policy_dump_add_policy(&ctx->state, op.policy,
						      op.maxattr);
	पूर्ण

	क्रम (i = 0; i < genl_get_cmd_cnt(rt); i++) अणु
		genl_get_cmd_by_index(i, rt, &op);

		अगर (op.policy) अणु
			err = netlink_policy_dump_add_policy(&ctx->state,
							     op.policy,
							     op.maxattr);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (!ctx->state)
		वापस -ENODATA;
	वापस 0;
पूर्ण

अटल व्योम *ctrl_dumppolicy_prep(काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb)
अणु
	काष्ठा ctrl_dump_policy_ctx *ctx = (व्योम *)cb->ctx;
	व्योम *hdr;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid,
			  cb->nlh->nlmsg_seq, &genl_ctrl,
			  NLM_F_MULTI, CTRL_CMD_GETPOLICY);
	अगर (!hdr)
		वापस शून्य;

	अगर (nla_put_u16(skb, CTRL_ATTR_FAMILY_ID, ctx->fam_id))
		वापस शून्य;

	वापस hdr;
पूर्ण

अटल पूर्णांक ctrl_dumppolicy_put_op(काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb,
			          काष्ठा genl_ops *op)
अणु
	काष्ठा ctrl_dump_policy_ctx *ctx = (व्योम *)cb->ctx;
	काष्ठा nlattr *nest_pol, *nest_op;
	व्योम *hdr;
	पूर्णांक idx;

	/* skip अगर we have nothing to show */
	अगर (!op->policy)
		वापस 0;
	अगर (!op->करोit &&
	    (!op->dumpit || op->validate & GENL_DONT_VALIDATE_DUMP))
		वापस 0;

	hdr = ctrl_dumppolicy_prep(skb, cb);
	अगर (!hdr)
		वापस -ENOBUFS;

	nest_pol = nla_nest_start(skb, CTRL_ATTR_OP_POLICY);
	अगर (!nest_pol)
		जाओ err;

	nest_op = nla_nest_start(skb, op->cmd);
	अगर (!nest_op)
		जाओ err;

	/* क्रम now both करो/dump are always the same */
	idx = netlink_policy_dump_get_policy_idx(ctx->state,
						 op->policy,
						 op->maxattr);

	अगर (op->करोit && nla_put_u32(skb, CTRL_ATTR_POLICY_DO, idx))
		जाओ err;

	अगर (op->dumpit && !(op->validate & GENL_DONT_VALIDATE_DUMP) &&
	    nla_put_u32(skb, CTRL_ATTR_POLICY_DUMP, idx))
		जाओ err;

	nla_nest_end(skb, nest_op);
	nla_nest_end(skb, nest_pol);
	genlmsg_end(skb, hdr);

	वापस 0;
err:
	genlmsg_cancel(skb, hdr);
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक ctrl_dumppolicy(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा ctrl_dump_policy_ctx *ctx = (व्योम *)cb->ctx;
	व्योम *hdr;

	अगर (!ctx->policies) अणु
		जबतक (ctx->opidx < genl_get_cmd_cnt(ctx->rt)) अणु
			काष्ठा genl_ops op;

			अगर (ctx->single_op) अणु
				पूर्णांक err;

				err = genl_get_cmd(ctx->op, ctx->rt, &op);
				अगर (WARN_ON(err))
					वापस skb->len;

				/* अवरोध out of the loop after this one */
				ctx->opidx = genl_get_cmd_cnt(ctx->rt);
			पूर्ण अन्यथा अणु
				genl_get_cmd_by_index(ctx->opidx, ctx->rt, &op);
			पूर्ण

			अगर (ctrl_dumppolicy_put_op(skb, cb, &op))
				वापस skb->len;

			ctx->opidx++;
		पूर्ण

		/* completed with the per-op policy index list */
		ctx->policies = true;
	पूर्ण

	जबतक (netlink_policy_dump_loop(ctx->state)) अणु
		काष्ठा nlattr *nest;

		hdr = ctrl_dumppolicy_prep(skb, cb);
		अगर (!hdr)
			जाओ nla_put_failure;

		nest = nla_nest_start(skb, CTRL_ATTR_POLICY);
		अगर (!nest)
			जाओ nla_put_failure;

		अगर (netlink_policy_dump_ग_लिखो(skb, ctx->state))
			जाओ nla_put_failure;

		nla_nest_end(skb, nest);

		genlmsg_end(skb, hdr);
	पूर्ण

	वापस skb->len;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस skb->len;
पूर्ण

अटल पूर्णांक ctrl_dumppolicy_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा ctrl_dump_policy_ctx *ctx = (व्योम *)cb->ctx;

	netlink_policy_dump_मुक्त(ctx->state);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा genl_ops genl_ctrl_ops[] = अणु
	अणु
		.cmd		= CTRL_CMD_GETFAMILY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.policy		= ctrl_policy_family,
		.maxattr	= ARRAY_SIZE(ctrl_policy_family) - 1,
		.करोit		= ctrl_getfamily,
		.dumpit		= ctrl_dumpfamily,
	पूर्ण,
	अणु
		.cmd		= CTRL_CMD_GETPOLICY,
		.policy		= ctrl_policy_policy,
		.maxattr	= ARRAY_SIZE(ctrl_policy_policy) - 1,
		.start		= ctrl_dumppolicy_start,
		.dumpit		= ctrl_dumppolicy,
		.करोne		= ctrl_dumppolicy_करोne,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group genl_ctrl_groups[] = अणु
	अणु .name = "notify", पूर्ण,
पूर्ण;

अटल काष्ठा genl_family genl_ctrl __ro_after_init = अणु
	.module = THIS_MODULE,
	.ops = genl_ctrl_ops,
	.n_ops = ARRAY_SIZE(genl_ctrl_ops),
	.mcgrps = genl_ctrl_groups,
	.n_mcgrps = ARRAY_SIZE(genl_ctrl_groups),
	.id = GENL_ID_CTRL,
	.name = "nlctrl",
	.version = 0x2,
	.netnsok = true,
पूर्ण;

अटल पूर्णांक genl_bind(काष्ठा net *net, पूर्णांक group)
अणु
	स्थिर काष्ठा genl_family *family;
	अचिन्हित पूर्णांक id;
	पूर्णांक ret = 0;

	genl_lock_all();

	idr_क्रम_each_entry(&genl_fam_idr, family, id) अणु
		स्थिर काष्ठा genl_multicast_group *grp;
		पूर्णांक i;

		अगर (family->n_mcgrps == 0)
			जारी;

		i = group - family->mcgrp_offset;
		अगर (i < 0 || i >= family->n_mcgrps)
			जारी;

		grp = &family->mcgrps[i];
		अगर ((grp->flags & GENL_UNS_ADMIN_PERM) &&
		    !ns_capable(net->user_ns, CAP_NET_ADMIN))
			ret = -EPERM;

		अवरोध;
	पूर्ण

	genl_unlock_all();
	वापस ret;
पूर्ण

अटल पूर्णांक __net_init genl_pernet_init(काष्ठा net *net)
अणु
	काष्ठा netlink_kernel_cfg cfg = अणु
		.input		= genl_rcv,
		.flags		= NL_CFG_F_NONROOT_RECV,
		.bind		= genl_bind,
	पूर्ण;

	/* we'll bump the group number right afterwards */
	net->genl_sock = netlink_kernel_create(net, NETLINK_GENERIC, &cfg);

	अगर (!net->genl_sock && net_eq(net, &init_net))
		panic("GENL: Cannot initialize generic netlink\n");

	अगर (!net->genl_sock)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास genl_pernet_निकास(काष्ठा net *net)
अणु
	netlink_kernel_release(net->genl_sock);
	net->genl_sock = शून्य;
पूर्ण

अटल काष्ठा pernet_operations genl_pernet_ops = अणु
	.init = genl_pernet_init,
	.निकास = genl_pernet_निकास,
पूर्ण;

अटल पूर्णांक __init genl_init(व्योम)
अणु
	पूर्णांक err;

	err = genl_रेजिस्टर_family(&genl_ctrl);
	अगर (err < 0)
		जाओ problem;

	err = रेजिस्टर_pernet_subsys(&genl_pernet_ops);
	अगर (err)
		जाओ problem;

	वापस 0;

problem:
	panic("GENL: Cannot register controller: %d\n", err);
पूर्ण

core_initcall(genl_init);

अटल पूर्णांक genlmsg_mcast(काष्ठा sk_buff *skb, u32 portid, अचिन्हित दीर्घ group,
			 gfp_t flags)
अणु
	काष्ठा sk_buff *पंचांगp;
	काष्ठा net *net, *prev = शून्य;
	bool delivered = false;
	पूर्णांक err;

	क्रम_each_net_rcu(net) अणु
		अगर (prev) अणु
			पंचांगp = skb_clone(skb, flags);
			अगर (!पंचांगp) अणु
				err = -ENOMEM;
				जाओ error;
			पूर्ण
			err = nlmsg_multicast(prev->genl_sock, पंचांगp,
					      portid, group, flags);
			अगर (!err)
				delivered = true;
			अन्यथा अगर (err != -ESRCH)
				जाओ error;
		पूर्ण

		prev = net;
	पूर्ण

	err = nlmsg_multicast(prev->genl_sock, skb, portid, group, flags);
	अगर (!err)
		delivered = true;
	अन्यथा अगर (err != -ESRCH)
		वापस err;
	वापस delivered ? 0 : -ESRCH;
 error:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

पूर्णांक genlmsg_multicast_allns(स्थिर काष्ठा genl_family *family,
			    काष्ठा sk_buff *skb, u32 portid,
			    अचिन्हित पूर्णांक group, gfp_t flags)
अणु
	अगर (WARN_ON_ONCE(group >= family->n_mcgrps))
		वापस -EINVAL;
	group = family->mcgrp_offset + group;
	वापस genlmsg_mcast(skb, portid, group, flags);
पूर्ण
EXPORT_SYMBOL(genlmsg_multicast_allns);

व्योम genl_notअगरy(स्थिर काष्ठा genl_family *family, काष्ठा sk_buff *skb,
		 काष्ठा genl_info *info, u32 group, gfp_t flags)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा sock *sk = net->genl_sock;
	पूर्णांक report = 0;

	अगर (info->nlhdr)
		report = nlmsg_report(info->nlhdr);

	अगर (WARN_ON_ONCE(group >= family->n_mcgrps))
		वापस;
	group = family->mcgrp_offset + group;
	nlmsg_notअगरy(sk, skb, info->snd_portid, group, report, flags);
पूर्ण
EXPORT_SYMBOL(genl_notअगरy);
