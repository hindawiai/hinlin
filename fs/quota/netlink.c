<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/cred.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>

अटल स्थिर काष्ठा genl_multicast_group quota_mcgrps[] = अणु
	अणु .name = "events", पूर्ण,
पूर्ण;

/* Netlink family काष्ठाure क्रम quota */
अटल काष्ठा genl_family quota_genl_family __ro_after_init = अणु
	.module = THIS_MODULE,
	.hdrsize = 0,
	.name = "VFS_DQUOT",
	.version = 1,
	.maxattr = QUOTA_NL_A_MAX,
	.mcgrps = quota_mcgrps,
	.n_mcgrps = ARRAY_SIZE(quota_mcgrps),
पूर्ण;

/**
 * quota_send_warning - Send warning to userspace about exceeded quota
 * @qid: The kernel पूर्णांकernal quota identअगरier.
 * @dev: The device on which the fs is mounted (sb->s_dev)
 * @warntype: The type of the warning: QUOTA_NL_...
 *
 * This can be used by fileप्रणालीs (including those which करोn't use
 * dquot) to send a message to userspace relating to quota limits.
 *
 */

व्योम quota_send_warning(काष्ठा kqid qid, dev_t dev,
			स्थिर अक्षर warntype)
अणु
	अटल atomic_t seq;
	काष्ठा sk_buff *skb;
	व्योम *msg_head;
	पूर्णांक ret;
	पूर्णांक msg_size = 4 * nla_total_size(माप(u32)) +
		       2 * nla_total_size_64bit(माप(u64));

	/* We have to allocate using GFP_NOFS as we are called from a
	 * fileप्रणाली perक्रमming ग_लिखो and thus further recursion पूर्णांकo
	 * the fs to मुक्त some data could cause deadlocks. */
	skb = genlmsg_new(msg_size, GFP_NOFS);
	अगर (!skb) अणु
		prपूर्णांकk(KERN_ERR
		  "VFS: Not enough memory to send quota warning.\n");
		वापस;
	पूर्ण
	msg_head = genlmsg_put(skb, 0, atomic_add_वापस(1, &seq),
			&quota_genl_family, 0, QUOTA_NL_C_WARNING);
	अगर (!msg_head) अणु
		prपूर्णांकk(KERN_ERR
		  "VFS: Cannot store netlink header in quota warning.\n");
		जाओ err_out;
	पूर्ण
	ret = nla_put_u32(skb, QUOTA_NL_A_QTYPE, qid.type);
	अगर (ret)
		जाओ attr_err_out;
	ret = nla_put_u64_64bit(skb, QUOTA_NL_A_EXCESS_ID,
				from_kqid_munged(&init_user_ns, qid),
				QUOTA_NL_A_PAD);
	अगर (ret)
		जाओ attr_err_out;
	ret = nla_put_u32(skb, QUOTA_NL_A_WARNING, warntype);
	अगर (ret)
		जाओ attr_err_out;
	ret = nla_put_u32(skb, QUOTA_NL_A_DEV_MAJOR, MAJOR(dev));
	अगर (ret)
		जाओ attr_err_out;
	ret = nla_put_u32(skb, QUOTA_NL_A_DEV_MINOR, MINOR(dev));
	अगर (ret)
		जाओ attr_err_out;
	ret = nla_put_u64_64bit(skb, QUOTA_NL_A_CAUSED_ID,
				from_kuid_munged(&init_user_ns, current_uid()),
				QUOTA_NL_A_PAD);
	अगर (ret)
		जाओ attr_err_out;
	genlmsg_end(skb, msg_head);

	genlmsg_multicast(&quota_genl_family, skb, 0, 0, GFP_NOFS);
	वापस;
attr_err_out:
	prपूर्णांकk(KERN_ERR "VFS: Not enough space to compose quota message!\n");
err_out:
	kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL(quota_send_warning);

अटल पूर्णांक __init quota_init(व्योम)
अणु
	अगर (genl_रेजिस्टर_family(&quota_genl_family) != 0)
		prपूर्णांकk(KERN_ERR
		       "VFS: Failed to create quota netlink interface.\n");
	वापस 0;
पूर्ण;
fs_initcall(quota_init);
