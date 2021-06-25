<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  NSA Security-Enhanced Linux (SELinux) security module
 *
 *  This file contains the SELinux hook function implementations.
 *
 *  Authors:  Stephen Smalley, <sds@tycho.nsa.gov>
 *	      Chris Vance, <cvance@nai.com>
 *	      Wayne Salamon, <wsalamon@nai.com>
 *	      James Morris <jmorris@redhat.com>
 *
 *  Copyright (C) 2001,2002 Networks Associates Technology, Inc.
 *  Copyright (C) 2003-2008 Red Hat, Inc., James Morris <jmorris@redhat.com>
 *					   Eric Paris <eparis@redhat.com>
 *  Copyright (C) 2004-2005 Trusted Computer Solutions, Inc.
 *			    <dgoeddel@trustedcs.com>
 *  Copyright (C) 2006, 2007, 2009 Hewlett-Packard Development Company, L.P.
 *	Paul Moore <paul@paul-moore.com>
 *  Copyright (C) 2007 Hitachi Software Engineering Co., Ltd.
 *		       Yuichi Nakamura <ynakam@hitachisoft.jp>
 *  Copyright (C) 2016 Mellanox Technologies
 */

#समावेश <linux/init.h>
#समावेश <linux/kd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/xattr.h>
#समावेश <linux/capability.h>
#समावेश <linux/unistd.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/swap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/dcache.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/tty.h>
#समावेश <net/icmp.h>
#समावेश <net/ip.h>		/* क्रम local_port_range[] */
#समावेश <net/tcp.h>		/* काष्ठा or_callable used in sock_rcv_skb */
#समावेश <net/inet_connection_sock.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netlabel.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>	/* क्रम network पूर्णांकerface checks */
#समावेश <net/netlink.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/dccp.h>
#समावेश <linux/sctp.h>
#समावेश <net/sctp/काष्ठाs.h>
#समावेश <linux/quota.h>
#समावेश <linux/un.h>		/* क्रम Unix socket types */
#समावेश <net/af_unix.h>	/* क्रम Unix socket types */
#समावेश <linux/parser.h>
#समावेश <linux/nfs_mount.h>
#समावेश <net/ipv6.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/personality.h>
#समावेश <linux/audit.h>
#समावेश <linux/माला.स>
#समावेश <linux/mutex.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/syslog.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/export.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/bpf.h>
#समावेश <linux/kernfs.h>
#समावेश <linux/stringhash.h>	/* क्रम hashlen_string() */
#समावेश <uapi/linux/mount.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/fanotअगरy.h>

#समावेश "avc.h"
#समावेश "objsec.h"
#समावेश "netif.h"
#समावेश "netnode.h"
#समावेश "netport.h"
#समावेश "ibpkey.h"
#समावेश "xfrm.h"
#समावेश "netlabel.h"
#समावेश "audit.h"
#समावेश "avc_ss.h"

काष्ठा selinux_state selinux_state;

/* SECMARK reference count */
अटल atomic_t selinux_secmark_refcount = ATOMIC_INIT(0);

#अगर_घोषित CONFIG_SECURITY_SELINUX_DEVELOP
अटल पूर्णांक selinux_enक्रमcing_boot __initdata;

अटल पूर्णांक __init enक्रमcing_setup(अक्षर *str)
अणु
	अचिन्हित दीर्घ enक्रमcing;
	अगर (!kम_से_अदीर्घ(str, 0, &enक्रमcing))
		selinux_enक्रमcing_boot = enक्रमcing ? 1 : 0;
	वापस 1;
पूर्ण
__setup("enforcing=", enक्रमcing_setup);
#अन्यथा
#घोषणा selinux_enक्रमcing_boot 1
#पूर्ण_अगर

पूर्णांक selinux_enabled_boot __initdata = 1;
#अगर_घोषित CONFIG_SECURITY_SELINUX_BOOTPARAM
अटल पूर्णांक __init selinux_enabled_setup(अक्षर *str)
अणु
	अचिन्हित दीर्घ enabled;
	अगर (!kम_से_अदीर्घ(str, 0, &enabled))
		selinux_enabled_boot = enabled ? 1 : 0;
	वापस 1;
पूर्ण
__setup("selinux=", selinux_enabled_setup);
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक selinux_checkreqprot_boot =
	CONFIG_SECURITY_SELINUX_CHECKREQPROT_VALUE;

अटल पूर्णांक __init checkreqprot_setup(अक्षर *str)
अणु
	अचिन्हित दीर्घ checkreqprot;

	अगर (!kम_से_अदीर्घ(str, 0, &checkreqprot)) अणु
		selinux_checkreqprot_boot = checkreqprot ? 1 : 0;
		अगर (checkreqprot)
			pr_warn("SELinux: checkreqprot set to 1 via kernel parameter.  This is deprecated and will be rejected in a future kernel release.\n");
	पूर्ण
	वापस 1;
पूर्ण
__setup("checkreqprot=", checkreqprot_setup);

/**
 * selinux_secmark_enabled - Check to see अगर SECMARK is currently enabled
 *
 * Description:
 * This function checks the SECMARK reference counter to see अगर any SECMARK
 * tarमाला_लो are currently configured, अगर the reference counter is greater than
 * zero SECMARK is considered to be enabled.  Returns true (1) अगर SECMARK is
 * enabled, false (0) अगर SECMARK is disabled.  If the always_check_network
 * policy capability is enabled, SECMARK is always considered enabled.
 *
 */
अटल पूर्णांक selinux_secmark_enabled(व्योम)
अणु
	वापस (selinux_policycap_alwaysnetwork() ||
		atomic_पढ़ो(&selinux_secmark_refcount));
पूर्ण

/**
 * selinux_peerlbl_enabled - Check to see अगर peer labeling is currently enabled
 *
 * Description:
 * This function checks अगर NetLabel or labeled IPSEC is enabled.  Returns true
 * (1) अगर any are enabled or false (0) अगर neither are enabled.  If the
 * always_check_network policy capability is enabled, peer labeling
 * is always considered enabled.
 *
 */
अटल पूर्णांक selinux_peerlbl_enabled(व्योम)
अणु
	वापस (selinux_policycap_alwaysnetwork() ||
		netlbl_enabled() || selinux_xfrm_enabled());
पूर्ण

अटल पूर्णांक selinux_netcache_avc_callback(u32 event)
अणु
	अगर (event == AVC_CALLBACK_RESET) अणु
		sel_netअगर_flush();
		sel_netnode_flush();
		sel_netport_flush();
		synchronize_net();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक selinux_lsm_notअगरier_avc_callback(u32 event)
अणु
	अगर (event == AVC_CALLBACK_RESET) अणु
		sel_ib_pkey_flush();
		call_blocking_lsm_notअगरier(LSM_POLICY_CHANGE, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * initialise the security क्रम the init task
 */
अटल व्योम cred_init_security(व्योम)
अणु
	काष्ठा cred *cred = (काष्ठा cred *) current->real_cred;
	काष्ठा task_security_काष्ठा *tsec;

	tsec = selinux_cred(cred);
	tsec->osid = tsec->sid = SECINITSID_KERNEL;
पूर्ण

/*
 * get the security ID of a set of credentials
 */
अटल अंतरभूत u32 cred_sid(स्थिर काष्ठा cred *cred)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec;

	tsec = selinux_cred(cred);
	वापस tsec->sid;
पूर्ण

/*
 * get the subjective security ID of a task
 */
अटल अंतरभूत u32 task_sid_subj(स्थिर काष्ठा task_काष्ठा *task)
अणु
	u32 sid;

	rcu_पढ़ो_lock();
	sid = cred_sid(rcu_dereference(task->cred));
	rcu_पढ़ो_unlock();
	वापस sid;
पूर्ण

/*
 * get the objective security ID of a task
 */
अटल अंतरभूत u32 task_sid_obj(स्थिर काष्ठा task_काष्ठा *task)
अणु
	u32 sid;

	rcu_पढ़ो_lock();
	sid = cred_sid(__task_cred(task));
	rcu_पढ़ो_unlock();
	वापस sid;
पूर्ण

/*
 * get the security ID of a task क्रम use with binder
 */
अटल अंतरभूत u32 task_sid_binder(स्थिर काष्ठा task_काष्ठा *task)
अणु
	/*
	 * In many हाल where this function is used we should be using the
	 * task's subjective SID, but we can't reliably access the subjective
	 * creds of a task other than our own so we must use the objective
	 * creds/SID, which are safe to access.  The करोwnside is that अगर a task
	 * is temporarily overriding it's creds it will not be reflected here;
	 * however, it isn't clear that binder would handle that हाल well
	 * anyway.
	 *
	 * If this ever changes and we can safely reference the subjective
	 * creds/SID of another task, this function will make it easier to
	 * identअगरy the various places where we make use of the task SIDs in
	 * the binder code.  It is also likely that we will need to adjust
	 * the मुख्य drivers/android binder code as well.
	 */
	वापस task_sid_obj(task);
पूर्ण

अटल पूर्णांक inode_करोinit_with_dentry(काष्ठा inode *inode, काष्ठा dentry *opt_dentry);

/*
 * Try reloading inode security labels that have been marked as invalid.  The
 * @may_sleep parameter indicates when sleeping and thus reloading labels is
 * allowed; when set to false, वापसs -ECHILD when the label is
 * invalid.  The @dentry parameter should be set to a dentry of the inode.
 */
अटल पूर्णांक __inode_security_revalidate(काष्ठा inode *inode,
				       काष्ठा dentry *dentry,
				       bool may_sleep)
अणु
	काष्ठा inode_security_काष्ठा *isec = selinux_inode(inode);

	might_sleep_अगर(may_sleep);

	अगर (selinux_initialized(&selinux_state) &&
	    isec->initialized != LABEL_INITIALIZED) अणु
		अगर (!may_sleep)
			वापस -ECHILD;

		/*
		 * Try reloading the inode security label.  This will fail अगर
		 * @opt_dentry is शून्य and no dentry क्रम this inode can be
		 * found; in that हाल, जारी using the old label.
		 */
		inode_करोinit_with_dentry(inode, dentry);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा inode_security_काष्ठा *inode_security_novalidate(काष्ठा inode *inode)
अणु
	वापस selinux_inode(inode);
पूर्ण

अटल काष्ठा inode_security_काष्ठा *inode_security_rcu(काष्ठा inode *inode, bool rcu)
अणु
	पूर्णांक error;

	error = __inode_security_revalidate(inode, शून्य, !rcu);
	अगर (error)
		वापस ERR_PTR(error);
	वापस selinux_inode(inode);
पूर्ण

/*
 * Get the security label of an inode.
 */
अटल काष्ठा inode_security_काष्ठा *inode_security(काष्ठा inode *inode)
अणु
	__inode_security_revalidate(inode, शून्य, true);
	वापस selinux_inode(inode);
पूर्ण

अटल काष्ठा inode_security_काष्ठा *backing_inode_security_novalidate(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);

	वापस selinux_inode(inode);
पूर्ण

/*
 * Get the security label of a dentry's backing inode.
 */
अटल काष्ठा inode_security_काष्ठा *backing_inode_security(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);

	__inode_security_revalidate(inode, dentry, true);
	वापस selinux_inode(inode);
पूर्ण

अटल व्योम inode_मुक्त_security(काष्ठा inode *inode)
अणु
	काष्ठा inode_security_काष्ठा *isec = selinux_inode(inode);
	काष्ठा superblock_security_काष्ठा *sbsec;

	अगर (!isec)
		वापस;
	sbsec = selinux_superblock(inode->i_sb);
	/*
	 * As not all inode security काष्ठाures are in a list, we check क्रम
	 * empty list outside of the lock to make sure that we won't waste
	 * समय taking a lock करोing nothing.
	 *
	 * The list_del_init() function can be safely called more than once.
	 * It should not be possible क्रम this function to be called with
	 * concurrent list_add(), but क्रम better safety against future changes
	 * in the code, we use list_empty_careful() here.
	 */
	अगर (!list_empty_careful(&isec->list)) अणु
		spin_lock(&sbsec->isec_lock);
		list_del_init(&isec->list);
		spin_unlock(&sbsec->isec_lock);
	पूर्ण
पूर्ण

काष्ठा selinux_mnt_opts अणु
	स्थिर अक्षर *fscontext, *context, *rootcontext, *defcontext;
पूर्ण;

अटल व्योम selinux_मुक्त_mnt_opts(व्योम *mnt_opts)
अणु
	काष्ठा selinux_mnt_opts *opts = mnt_opts;
	kमुक्त(opts->fscontext);
	kमुक्त(opts->context);
	kमुक्त(opts->rootcontext);
	kमुक्त(opts->defcontext);
	kमुक्त(opts);
पूर्ण

क्रमागत अणु
	Opt_error = -1,
	Opt_context = 0,
	Opt_defcontext = 1,
	Opt_fscontext = 2,
	Opt_rootcontext = 3,
	Opt_seclabel = 4,
पूर्ण;

#घोषणा A(s, has_arg) अणु#s, माप(#s) - 1, Opt_##s, has_argपूर्ण
अटल काष्ठा अणु
	स्थिर अक्षर *name;
	पूर्णांक len;
	पूर्णांक opt;
	bool has_arg;
पूर्ण tokens[] = अणु
	A(context, true),
	A(fscontext, true),
	A(defcontext, true),
	A(rootcontext, true),
	A(seclabel, false),
पूर्ण;
#अघोषित A

अटल पूर्णांक match_opt_prefix(अक्षर *s, पूर्णांक l, अक्षर **arg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tokens); i++) अणु
		माप_प्रकार len = tokens[i].len;
		अगर (len > l || स_भेद(s, tokens[i].name, len))
			जारी;
		अगर (tokens[i].has_arg) अणु
			अगर (len == l || s[len] != '=')
				जारी;
			*arg = s + len + 1;
		पूर्ण अन्यथा अगर (len != l)
			जारी;
		वापस tokens[i].opt;
	पूर्ण
	वापस Opt_error;
पूर्ण

#घोषणा SEL_MOUNT_FAIL_MSG "SELinux:  duplicate or incompatible mount options\n"

अटल पूर्णांक may_context_mount_sb_relabel(u32 sid,
			काष्ठा superblock_security_काष्ठा *sbsec,
			स्थिर काष्ठा cred *cred)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(cred);
	पूर्णांक rc;

	rc = avc_has_perm(&selinux_state,
			  tsec->sid, sbsec->sid, SECCLASS_खाताSYSTEM,
			  खाताSYSTEM__RELABELFROM, शून्य);
	अगर (rc)
		वापस rc;

	rc = avc_has_perm(&selinux_state,
			  tsec->sid, sid, SECCLASS_खाताSYSTEM,
			  खाताSYSTEM__RELABELTO, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक may_context_mount_inode_relabel(u32 sid,
			काष्ठा superblock_security_काष्ठा *sbsec,
			स्थिर काष्ठा cred *cred)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(cred);
	पूर्णांक rc;
	rc = avc_has_perm(&selinux_state,
			  tsec->sid, sbsec->sid, SECCLASS_खाताSYSTEM,
			  खाताSYSTEM__RELABELFROM, शून्य);
	अगर (rc)
		वापस rc;

	rc = avc_has_perm(&selinux_state,
			  sid, sbsec->sid, SECCLASS_खाताSYSTEM,
			  खाताSYSTEM__ASSOCIATE, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_is_genfs_special_handling(काष्ठा super_block *sb)
अणु
	/* Special handling. Genfs but also in-core setxattr handler */
	वापस	!म_भेद(sb->s_type->name, "sysfs") ||
		!म_भेद(sb->s_type->name, "pstore") ||
		!म_भेद(sb->s_type->name, "debugfs") ||
		!म_भेद(sb->s_type->name, "tracefs") ||
		!म_भेद(sb->s_type->name, "rootfs") ||
		(selinux_policycap_cgroupseclabel() &&
		 (!म_भेद(sb->s_type->name, "cgroup") ||
		  !म_भेद(sb->s_type->name, "cgroup2")));
पूर्ण

अटल पूर्णांक selinux_is_sblabel_mnt(काष्ठा super_block *sb)
अणु
	काष्ठा superblock_security_काष्ठा *sbsec = selinux_superblock(sb);

	/*
	 * IMPORTANT: Double-check logic in this function when adding a new
	 * SECURITY_FS_USE_* definition!
	 */
	BUILD_BUG_ON(SECURITY_FS_USE_MAX != 7);

	चयन (sbsec->behavior) अणु
	हाल SECURITY_FS_USE_XATTR:
	हाल SECURITY_FS_USE_TRANS:
	हाल SECURITY_FS_USE_TASK:
	हाल SECURITY_FS_USE_NATIVE:
		वापस 1;

	हाल SECURITY_FS_USE_GENFS:
		वापस selinux_is_genfs_special_handling(sb);

	/* Never allow relabeling on context mounts */
	हाल SECURITY_FS_USE_MNTPOINT:
	हाल SECURITY_FS_USE_NONE:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक sb_check_xattr_support(काष्ठा super_block *sb)
अणु
	काष्ठा superblock_security_काष्ठा *sbsec = sb->s_security;
	काष्ठा dentry *root = sb->s_root;
	काष्ठा inode *root_inode = d_backing_inode(root);
	u32 sid;
	पूर्णांक rc;

	/*
	 * Make sure that the xattr handler exists and that no
	 * error other than -ENODATA is वापसed by getxattr on
	 * the root directory.  -ENODATA is ok, as this may be
	 * the first boot of the SELinux kernel beक्रमe we have
	 * asचिन्हित xattr values to the fileप्रणाली.
	 */
	अगर (!(root_inode->i_opflags & IOP_XATTR)) अणु
		pr_warn("SELinux: (dev %s, type %s) has no xattr support\n",
			sb->s_id, sb->s_type->name);
		जाओ fallback;
	पूर्ण

	rc = __vfs_getxattr(root, root_inode, XATTR_NAME_SELINUX, शून्य, 0);
	अगर (rc < 0 && rc != -ENODATA) अणु
		अगर (rc == -EOPNOTSUPP) अणु
			pr_warn("SELinux: (dev %s, type %s) has no security xattr handler\n",
				sb->s_id, sb->s_type->name);
			जाओ fallback;
		पूर्ण अन्यथा अणु
			pr_warn("SELinux: (dev %s, type %s) getxattr errno %d\n",
				sb->s_id, sb->s_type->name, -rc);
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;

fallback:
	/* No xattr support - try to fallback to genfs अगर possible. */
	rc = security_genfs_sid(&selinux_state, sb->s_type->name, "/",
				SECCLASS_सूची, &sid);
	अगर (rc)
		वापस -EOPNOTSUPP;

	pr_warn("SELinux: (dev %s, type %s) falling back to genfs\n",
		sb->s_id, sb->s_type->name);
	sbsec->behavior = SECURITY_FS_USE_GENFS;
	sbsec->sid = sid;
	वापस 0;
पूर्ण

अटल पूर्णांक sb_finish_set_opts(काष्ठा super_block *sb)
अणु
	काष्ठा superblock_security_काष्ठा *sbsec = selinux_superblock(sb);
	काष्ठा dentry *root = sb->s_root;
	काष्ठा inode *root_inode = d_backing_inode(root);
	पूर्णांक rc = 0;

	अगर (sbsec->behavior == SECURITY_FS_USE_XATTR) अणु
		rc = sb_check_xattr_support(sb);
		अगर (rc)
			वापस rc;
	पूर्ण

	sbsec->flags |= SE_SBINITIALIZED;

	/*
	 * Explicitly set or clear SBLABEL_MNT.  It's not sufficient to simply
	 * leave the flag untouched because sb_clone_mnt_opts might be handing
	 * us a superblock that needs the flag to be cleared.
	 */
	अगर (selinux_is_sblabel_mnt(sb))
		sbsec->flags |= SBLABEL_MNT;
	अन्यथा
		sbsec->flags &= ~SBLABEL_MNT;

	/* Initialize the root inode. */
	rc = inode_करोinit_with_dentry(root_inode, root);

	/* Initialize any other inodes associated with the superblock, e.g.
	   inodes created prior to initial policy load or inodes created
	   during get_sb by a pseuकरो fileप्रणाली that directly
	   populates itself. */
	spin_lock(&sbsec->isec_lock);
	जबतक (!list_empty(&sbsec->isec_head)) अणु
		काष्ठा inode_security_काष्ठा *isec =
				list_first_entry(&sbsec->isec_head,
					   काष्ठा inode_security_काष्ठा, list);
		काष्ठा inode *inode = isec->inode;
		list_del_init(&isec->list);
		spin_unlock(&sbsec->isec_lock);
		inode = igrab(inode);
		अगर (inode) अणु
			अगर (!IS_PRIVATE(inode))
				inode_करोinit_with_dentry(inode, शून्य);
			iput(inode);
		पूर्ण
		spin_lock(&sbsec->isec_lock);
	पूर्ण
	spin_unlock(&sbsec->isec_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक bad_option(काष्ठा superblock_security_काष्ठा *sbsec, अक्षर flag,
		      u32 old_sid, u32 new_sid)
अणु
	अक्षर mnt_flags = sbsec->flags & SE_MNTMASK;

	/* check अगर the old mount command had the same options */
	अगर (sbsec->flags & SE_SBINITIALIZED)
		अगर (!(sbsec->flags & flag) ||
		    (old_sid != new_sid))
			वापस 1;

	/* check अगर we were passed the same options twice,
	 * aka someone passed context=a,context=b
	 */
	अगर (!(sbsec->flags & SE_SBINITIALIZED))
		अगर (mnt_flags & flag)
			वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक parse_sid(काष्ठा super_block *sb, स्थिर अक्षर *s, u32 *sid)
अणु
	पूर्णांक rc = security_context_str_to_sid(&selinux_state, s,
					     sid, GFP_KERNEL);
	अगर (rc)
		pr_warn("SELinux: security_context_str_to_sid"
		       "(%s) failed for (dev %s, type %s) errno=%d\n",
		       s, sb->s_id, sb->s_type->name, rc);
	वापस rc;
पूर्ण

/*
 * Allow fileप्रणालीs with binary mount data to explicitly set mount poपूर्णांक
 * labeling inक्रमmation.
 */
अटल पूर्णांक selinux_set_mnt_opts(काष्ठा super_block *sb,
				व्योम *mnt_opts,
				अचिन्हित दीर्घ kern_flags,
				अचिन्हित दीर्घ *set_kern_flags)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा superblock_security_काष्ठा *sbsec = selinux_superblock(sb);
	काष्ठा dentry *root = sb->s_root;
	काष्ठा selinux_mnt_opts *opts = mnt_opts;
	काष्ठा inode_security_काष्ठा *root_isec;
	u32 fscontext_sid = 0, context_sid = 0, rootcontext_sid = 0;
	u32 defcontext_sid = 0;
	पूर्णांक rc = 0;

	mutex_lock(&sbsec->lock);

	अगर (!selinux_initialized(&selinux_state)) अणु
		अगर (!opts) अणु
			/* Defer initialization until selinux_complete_init,
			   after the initial policy is loaded and the security
			   server is पढ़ोy to handle calls. */
			जाओ out;
		पूर्ण
		rc = -EINVAL;
		pr_warn("SELinux: Unable to set superblock options "
			"before the security server is initialized\n");
		जाओ out;
	पूर्ण
	अगर (kern_flags && !set_kern_flags) अणु
		/* Specअगरying पूर्णांकernal flags without providing a place to
		 * place the results is not allowed */
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Binary mount data FS will come through this function twice.  Once
	 * from an explicit call and once from the generic calls from the vfs.
	 * Since the generic VFS calls will not contain any security mount data
	 * we need to skip the द्विगुन mount verअगरication.
	 *
	 * This करोes खोलो a hole in which we will not notice अगर the first
	 * mount using this sb set explict options and a second mount using
	 * this sb करोes not set any security options.  (The first options
	 * will be used क्रम both mounts)
	 */
	अगर ((sbsec->flags & SE_SBINITIALIZED) && (sb->s_type->fs_flags & FS_BINARY_MOUNTDATA)
	    && !opts)
		जाओ out;

	root_isec = backing_inode_security_novalidate(root);

	/*
	 * parse the mount options, check अगर they are valid sids.
	 * also check अगर someone is trying to mount the same sb more
	 * than once with dअगरferent security options.
	 */
	अगर (opts) अणु
		अगर (opts->fscontext) अणु
			rc = parse_sid(sb, opts->fscontext, &fscontext_sid);
			अगर (rc)
				जाओ out;
			अगर (bad_option(sbsec, FSCONTEXT_MNT, sbsec->sid,
					fscontext_sid))
				जाओ out_द्विगुन_mount;
			sbsec->flags |= FSCONTEXT_MNT;
		पूर्ण
		अगर (opts->context) अणु
			rc = parse_sid(sb, opts->context, &context_sid);
			अगर (rc)
				जाओ out;
			अगर (bad_option(sbsec, CONTEXT_MNT, sbsec->mntpoपूर्णांक_sid,
					context_sid))
				जाओ out_द्विगुन_mount;
			sbsec->flags |= CONTEXT_MNT;
		पूर्ण
		अगर (opts->rootcontext) अणु
			rc = parse_sid(sb, opts->rootcontext, &rootcontext_sid);
			अगर (rc)
				जाओ out;
			अगर (bad_option(sbsec, ROOTCONTEXT_MNT, root_isec->sid,
					rootcontext_sid))
				जाओ out_द्विगुन_mount;
			sbsec->flags |= ROOTCONTEXT_MNT;
		पूर्ण
		अगर (opts->defcontext) अणु
			rc = parse_sid(sb, opts->defcontext, &defcontext_sid);
			अगर (rc)
				जाओ out;
			अगर (bad_option(sbsec, DEFCONTEXT_MNT, sbsec->def_sid,
					defcontext_sid))
				जाओ out_द्विगुन_mount;
			sbsec->flags |= DEFCONTEXT_MNT;
		पूर्ण
	पूर्ण

	अगर (sbsec->flags & SE_SBINITIALIZED) अणु
		/* previously mounted with options, but not on this attempt? */
		अगर ((sbsec->flags & SE_MNTMASK) && !opts)
			जाओ out_द्विगुन_mount;
		rc = 0;
		जाओ out;
	पूर्ण

	अगर (म_भेद(sb->s_type->name, "proc") == 0)
		sbsec->flags |= SE_SBPROC | SE_SBGENFS;

	अगर (!म_भेद(sb->s_type->name, "debugfs") ||
	    !म_भेद(sb->s_type->name, "tracefs") ||
	    !म_भेद(sb->s_type->name, "binder") ||
	    !म_भेद(sb->s_type->name, "bpf") ||
	    !म_भेद(sb->s_type->name, "pstore"))
		sbsec->flags |= SE_SBGENFS;

	अगर (!म_भेद(sb->s_type->name, "sysfs") ||
	    !म_भेद(sb->s_type->name, "cgroup") ||
	    !म_भेद(sb->s_type->name, "cgroup2"))
		sbsec->flags |= SE_SBGENFS | SE_SBGENFS_XATTR;

	अगर (!sbsec->behavior) अणु
		/*
		 * Determine the labeling behavior to use क्रम this
		 * fileप्रणाली type.
		 */
		rc = security_fs_use(&selinux_state, sb);
		अगर (rc) अणु
			pr_warn("%s: security_fs_use(%s) returned %d\n",
					__func__, sb->s_type->name, rc);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * If this is a user namespace mount and the fileप्रणाली type is not
	 * explicitly whitelisted, then no contexts are allowed on the command
	 * line and security labels must be ignored.
	 */
	अगर (sb->s_user_ns != &init_user_ns &&
	    म_भेद(sb->s_type->name, "tmpfs") &&
	    म_भेद(sb->s_type->name, "ramfs") &&
	    म_भेद(sb->s_type->name, "devpts") &&
	    म_भेद(sb->s_type->name, "overlay")) अणु
		अगर (context_sid || fscontext_sid || rootcontext_sid ||
		    defcontext_sid) अणु
			rc = -EACCES;
			जाओ out;
		पूर्ण
		अगर (sbsec->behavior == SECURITY_FS_USE_XATTR) अणु
			sbsec->behavior = SECURITY_FS_USE_MNTPOINT;
			rc = security_transition_sid(&selinux_state,
						     current_sid(),
						     current_sid(),
						     SECCLASS_खाता, शून्य,
						     &sbsec->mntpoपूर्णांक_sid);
			अगर (rc)
				जाओ out;
		पूर्ण
		जाओ out_set_opts;
	पूर्ण

	/* sets the context of the superblock क्रम the fs being mounted. */
	अगर (fscontext_sid) अणु
		rc = may_context_mount_sb_relabel(fscontext_sid, sbsec, cred);
		अगर (rc)
			जाओ out;

		sbsec->sid = fscontext_sid;
	पूर्ण

	/*
	 * Switch to using mount poपूर्णांक labeling behavior.
	 * sets the label used on all file below the mountpoपूर्णांक, and will set
	 * the superblock context अगर not alपढ़ोy set.
	 */
	अगर (kern_flags & SECURITY_LSM_NATIVE_LABELS && !context_sid) अणु
		sbsec->behavior = SECURITY_FS_USE_NATIVE;
		*set_kern_flags |= SECURITY_LSM_NATIVE_LABELS;
	पूर्ण

	अगर (context_sid) अणु
		अगर (!fscontext_sid) अणु
			rc = may_context_mount_sb_relabel(context_sid, sbsec,
							  cred);
			अगर (rc)
				जाओ out;
			sbsec->sid = context_sid;
		पूर्ण अन्यथा अणु
			rc = may_context_mount_inode_relabel(context_sid, sbsec,
							     cred);
			अगर (rc)
				जाओ out;
		पूर्ण
		अगर (!rootcontext_sid)
			rootcontext_sid = context_sid;

		sbsec->mntpoपूर्णांक_sid = context_sid;
		sbsec->behavior = SECURITY_FS_USE_MNTPOINT;
	पूर्ण

	अगर (rootcontext_sid) अणु
		rc = may_context_mount_inode_relabel(rootcontext_sid, sbsec,
						     cred);
		अगर (rc)
			जाओ out;

		root_isec->sid = rootcontext_sid;
		root_isec->initialized = LABEL_INITIALIZED;
	पूर्ण

	अगर (defcontext_sid) अणु
		अगर (sbsec->behavior != SECURITY_FS_USE_XATTR &&
			sbsec->behavior != SECURITY_FS_USE_NATIVE) अणु
			rc = -EINVAL;
			pr_warn("SELinux: defcontext option is "
			       "invalid for this filesystem type\n");
			जाओ out;
		पूर्ण

		अगर (defcontext_sid != sbsec->def_sid) अणु
			rc = may_context_mount_inode_relabel(defcontext_sid,
							     sbsec, cred);
			अगर (rc)
				जाओ out;
		पूर्ण

		sbsec->def_sid = defcontext_sid;
	पूर्ण

out_set_opts:
	rc = sb_finish_set_opts(sb);
out:
	mutex_unlock(&sbsec->lock);
	वापस rc;
out_द्विगुन_mount:
	rc = -EINVAL;
	pr_warn("SELinux: mount invalid.  Same superblock, different "
	       "security settings for (dev %s, type %s)\n", sb->s_id,
	       sb->s_type->name);
	जाओ out;
पूर्ण

अटल पूर्णांक selinux_cmp_sb_context(स्थिर काष्ठा super_block *oldsb,
				    स्थिर काष्ठा super_block *newsb)
अणु
	काष्ठा superblock_security_काष्ठा *old = selinux_superblock(oldsb);
	काष्ठा superblock_security_काष्ठा *new = selinux_superblock(newsb);
	अक्षर oldflags = old->flags & SE_MNTMASK;
	अक्षर newflags = new->flags & SE_MNTMASK;

	अगर (oldflags != newflags)
		जाओ mismatch;
	अगर ((oldflags & FSCONTEXT_MNT) && old->sid != new->sid)
		जाओ mismatch;
	अगर ((oldflags & CONTEXT_MNT) && old->mntpoपूर्णांक_sid != new->mntpoपूर्णांक_sid)
		जाओ mismatch;
	अगर ((oldflags & DEFCONTEXT_MNT) && old->def_sid != new->def_sid)
		जाओ mismatch;
	अगर (oldflags & ROOTCONTEXT_MNT) अणु
		काष्ठा inode_security_काष्ठा *oldroot = backing_inode_security(oldsb->s_root);
		काष्ठा inode_security_काष्ठा *newroot = backing_inode_security(newsb->s_root);
		अगर (oldroot->sid != newroot->sid)
			जाओ mismatch;
	पूर्ण
	वापस 0;
mismatch:
	pr_warn("SELinux: mount invalid.  Same superblock, "
			    "different security settings for (dev %s, "
			    "type %s)\n", newsb->s_id, newsb->s_type->name);
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक selinux_sb_clone_mnt_opts(स्थिर काष्ठा super_block *oldsb,
					काष्ठा super_block *newsb,
					अचिन्हित दीर्घ kern_flags,
					अचिन्हित दीर्घ *set_kern_flags)
अणु
	पूर्णांक rc = 0;
	स्थिर काष्ठा superblock_security_काष्ठा *oldsbsec =
						selinux_superblock(oldsb);
	काष्ठा superblock_security_काष्ठा *newsbsec = selinux_superblock(newsb);

	पूर्णांक set_fscontext =	(oldsbsec->flags & FSCONTEXT_MNT);
	पूर्णांक set_context =	(oldsbsec->flags & CONTEXT_MNT);
	पूर्णांक set_rootcontext =	(oldsbsec->flags & ROOTCONTEXT_MNT);

	/*
	 * अगर the parent was able to be mounted it clearly had no special lsm
	 * mount options.  thus we can safely deal with this superblock later
	 */
	अगर (!selinux_initialized(&selinux_state))
		वापस 0;

	/*
	 * Specअगरying पूर्णांकernal flags without providing a place to
	 * place the results is not allowed.
	 */
	अगर (kern_flags && !set_kern_flags)
		वापस -EINVAL;

	/* how can we clone अगर the old one wasn't set up?? */
	BUG_ON(!(oldsbsec->flags & SE_SBINITIALIZED));

	/* अगर fs is reusing a sb, make sure that the contexts match */
	अगर (newsbsec->flags & SE_SBINITIALIZED) अणु
		अगर ((kern_flags & SECURITY_LSM_NATIVE_LABELS) && !set_context)
			*set_kern_flags |= SECURITY_LSM_NATIVE_LABELS;
		वापस selinux_cmp_sb_context(oldsb, newsb);
	पूर्ण

	mutex_lock(&newsbsec->lock);

	newsbsec->flags = oldsbsec->flags;

	newsbsec->sid = oldsbsec->sid;
	newsbsec->def_sid = oldsbsec->def_sid;
	newsbsec->behavior = oldsbsec->behavior;

	अगर (newsbsec->behavior == SECURITY_FS_USE_NATIVE &&
		!(kern_flags & SECURITY_LSM_NATIVE_LABELS) && !set_context) अणु
		rc = security_fs_use(&selinux_state, newsb);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर (kern_flags & SECURITY_LSM_NATIVE_LABELS && !set_context) अणु
		newsbsec->behavior = SECURITY_FS_USE_NATIVE;
		*set_kern_flags |= SECURITY_LSM_NATIVE_LABELS;
	पूर्ण

	अगर (set_context) अणु
		u32 sid = oldsbsec->mntpoपूर्णांक_sid;

		अगर (!set_fscontext)
			newsbsec->sid = sid;
		अगर (!set_rootcontext) अणु
			काष्ठा inode_security_काष्ठा *newisec = backing_inode_security(newsb->s_root);
			newisec->sid = sid;
		पूर्ण
		newsbsec->mntpoपूर्णांक_sid = sid;
	पूर्ण
	अगर (set_rootcontext) अणु
		स्थिर काष्ठा inode_security_काष्ठा *oldisec = backing_inode_security(oldsb->s_root);
		काष्ठा inode_security_काष्ठा *newisec = backing_inode_security(newsb->s_root);

		newisec->sid = oldisec->sid;
	पूर्ण

	sb_finish_set_opts(newsb);
out:
	mutex_unlock(&newsbsec->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_add_opt(पूर्णांक token, स्थिर अक्षर *s, व्योम **mnt_opts)
अणु
	काष्ठा selinux_mnt_opts *opts = *mnt_opts;

	अगर (token == Opt_seclabel)	/* eaten and completely ignored */
		वापस 0;

	अगर (!opts) अणु
		opts = kzalloc(माप(काष्ठा selinux_mnt_opts), GFP_KERNEL);
		अगर (!opts)
			वापस -ENOMEM;
		*mnt_opts = opts;
	पूर्ण
	अगर (!s)
		वापस -ENOMEM;
	चयन (token) अणु
	हाल Opt_context:
		अगर (opts->context || opts->defcontext)
			जाओ Einval;
		opts->context = s;
		अवरोध;
	हाल Opt_fscontext:
		अगर (opts->fscontext)
			जाओ Einval;
		opts->fscontext = s;
		अवरोध;
	हाल Opt_rootcontext:
		अगर (opts->rootcontext)
			जाओ Einval;
		opts->rootcontext = s;
		अवरोध;
	हाल Opt_defcontext:
		अगर (opts->context || opts->defcontext)
			जाओ Einval;
		opts->defcontext = s;
		अवरोध;
	पूर्ण
	वापस 0;
Einval:
	pr_warn(SEL_MOUNT_FAIL_MSG);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक selinux_add_mnt_opt(स्थिर अक्षर *option, स्थिर अक्षर *val, पूर्णांक len,
			       व्योम **mnt_opts)
अणु
	पूर्णांक token = Opt_error;
	पूर्णांक rc, i;

	क्रम (i = 0; i < ARRAY_SIZE(tokens); i++) अणु
		अगर (म_भेद(option, tokens[i].name) == 0) अणु
			token = tokens[i].opt;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (token == Opt_error)
		वापस -EINVAL;

	अगर (token != Opt_seclabel) अणु
		val = kmemdup_nul(val, len, GFP_KERNEL);
		अगर (!val) अणु
			rc = -ENOMEM;
			जाओ मुक्त_opt;
		पूर्ण
	पूर्ण
	rc = selinux_add_opt(token, val, mnt_opts);
	अगर (unlikely(rc)) अणु
		kमुक्त(val);
		जाओ मुक्त_opt;
	पूर्ण
	वापस rc;

मुक्त_opt:
	अगर (*mnt_opts) अणु
		selinux_मुक्त_mnt_opts(*mnt_opts);
		*mnt_opts = शून्य;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक show_sid(काष्ठा seq_file *m, u32 sid)
अणु
	अक्षर *context = शून्य;
	u32 len;
	पूर्णांक rc;

	rc = security_sid_to_context(&selinux_state, sid,
					     &context, &len);
	अगर (!rc) अणु
		bool has_comma = context && म_अक्षर(context, ',');

		seq_अ_दो(m, '=');
		अगर (has_comma)
			seq_अ_दो(m, '\"');
		seq_escape(m, context, "\"\n\\");
		अगर (has_comma)
			seq_अ_दो(m, '\"');
	पूर्ण
	kमुक्त(context);
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_sb_show_options(काष्ठा seq_file *m, काष्ठा super_block *sb)
अणु
	काष्ठा superblock_security_काष्ठा *sbsec = selinux_superblock(sb);
	पूर्णांक rc;

	अगर (!(sbsec->flags & SE_SBINITIALIZED))
		वापस 0;

	अगर (!selinux_initialized(&selinux_state))
		वापस 0;

	अगर (sbsec->flags & FSCONTEXT_MNT) अणु
		seq_अ_दो(m, ',');
		seq_माला_दो(m, FSCONTEXT_STR);
		rc = show_sid(m, sbsec->sid);
		अगर (rc)
			वापस rc;
	पूर्ण
	अगर (sbsec->flags & CONTEXT_MNT) अणु
		seq_अ_दो(m, ',');
		seq_माला_दो(m, CONTEXT_STR);
		rc = show_sid(m, sbsec->mntpoपूर्णांक_sid);
		अगर (rc)
			वापस rc;
	पूर्ण
	अगर (sbsec->flags & DEFCONTEXT_MNT) अणु
		seq_अ_दो(m, ',');
		seq_माला_दो(m, DEFCONTEXT_STR);
		rc = show_sid(m, sbsec->def_sid);
		अगर (rc)
			वापस rc;
	पूर्ण
	अगर (sbsec->flags & ROOTCONTEXT_MNT) अणु
		काष्ठा dentry *root = sb->s_root;
		काष्ठा inode_security_काष्ठा *isec = backing_inode_security(root);
		seq_अ_दो(m, ',');
		seq_माला_दो(m, ROOTCONTEXT_STR);
		rc = show_sid(m, isec->sid);
		अगर (rc)
			वापस rc;
	पूर्ण
	अगर (sbsec->flags & SBLABEL_MNT) अणु
		seq_अ_दो(m, ',');
		seq_माला_दो(m, SECLABEL_STR);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u16 inode_mode_to_security_class(umode_t mode)
अणु
	चयन (mode & S_IFMT) अणु
	हाल S_IFSOCK:
		वापस SECCLASS_SOCK_खाता;
	हाल S_IFLNK:
		वापस SECCLASS_LNK_खाता;
	हाल S_IFREG:
		वापस SECCLASS_खाता;
	हाल S_IFBLK:
		वापस SECCLASS_BLK_खाता;
	हाल S_IFसूची:
		वापस SECCLASS_सूची;
	हाल S_IFCHR:
		वापस SECCLASS_CHR_खाता;
	हाल S_IFIFO:
		वापस SECCLASS_FIFO_खाता;

	पूर्ण

	वापस SECCLASS_खाता;
पूर्ण

अटल अंतरभूत पूर्णांक शेष_protocol_stream(पूर्णांक protocol)
अणु
	वापस (protocol == IPPROTO_IP || protocol == IPPROTO_TCP ||
		protocol == IPPROTO_MPTCP);
पूर्ण

अटल अंतरभूत पूर्णांक शेष_protocol_dgram(पूर्णांक protocol)
अणु
	वापस (protocol == IPPROTO_IP || protocol == IPPROTO_UDP);
पूर्ण

अटल अंतरभूत u16 socket_type_to_security_class(पूर्णांक family, पूर्णांक type, पूर्णांक protocol)
अणु
	पूर्णांक extsockclass = selinux_policycap_extsockclass();

	चयन (family) अणु
	हाल PF_UNIX:
		चयन (type) अणु
		हाल SOCK_STREAM:
		हाल SOCK_SEQPACKET:
			वापस SECCLASS_UNIX_STREAM_SOCKET;
		हाल SOCK_DGRAM:
		हाल SOCK_RAW:
			वापस SECCLASS_UNIX_DGRAM_SOCKET;
		पूर्ण
		अवरोध;
	हाल PF_INET:
	हाल PF_INET6:
		चयन (type) अणु
		हाल SOCK_STREAM:
		हाल SOCK_SEQPACKET:
			अगर (शेष_protocol_stream(protocol))
				वापस SECCLASS_TCP_SOCKET;
			अन्यथा अगर (extsockclass && protocol == IPPROTO_SCTP)
				वापस SECCLASS_SCTP_SOCKET;
			अन्यथा
				वापस SECCLASS_RAWIP_SOCKET;
		हाल SOCK_DGRAM:
			अगर (शेष_protocol_dgram(protocol))
				वापस SECCLASS_UDP_SOCKET;
			अन्यथा अगर (extsockclass && (protocol == IPPROTO_ICMP ||
						  protocol == IPPROTO_ICMPV6))
				वापस SECCLASS_ICMP_SOCKET;
			अन्यथा
				वापस SECCLASS_RAWIP_SOCKET;
		हाल SOCK_DCCP:
			वापस SECCLASS_DCCP_SOCKET;
		शेष:
			वापस SECCLASS_RAWIP_SOCKET;
		पूर्ण
		अवरोध;
	हाल PF_NETLINK:
		चयन (protocol) अणु
		हाल NETLINK_ROUTE:
			वापस SECCLASS_NETLINK_ROUTE_SOCKET;
		हाल NETLINK_SOCK_DIAG:
			वापस SECCLASS_NETLINK_TCPDIAG_SOCKET;
		हाल NETLINK_NFLOG:
			वापस SECCLASS_NETLINK_NFLOG_SOCKET;
		हाल NETLINK_XFRM:
			वापस SECCLASS_NETLINK_XFRM_SOCKET;
		हाल NETLINK_SELINUX:
			वापस SECCLASS_NETLINK_SELINUX_SOCKET;
		हाल NETLINK_ISCSI:
			वापस SECCLASS_NETLINK_ISCSI_SOCKET;
		हाल NETLINK_AUDIT:
			वापस SECCLASS_NETLINK_AUDIT_SOCKET;
		हाल NETLINK_FIB_LOOKUP:
			वापस SECCLASS_NETLINK_FIB_LOOKUP_SOCKET;
		हाल NETLINK_CONNECTOR:
			वापस SECCLASS_NETLINK_CONNECTOR_SOCKET;
		हाल NETLINK_NETFILTER:
			वापस SECCLASS_NETLINK_NETFILTER_SOCKET;
		हाल NETLINK_DNRTMSG:
			वापस SECCLASS_NETLINK_DNRT_SOCKET;
		हाल NETLINK_KOBJECT_UEVENT:
			वापस SECCLASS_NETLINK_KOBJECT_UEVENT_SOCKET;
		हाल NETLINK_GENERIC:
			वापस SECCLASS_NETLINK_GENERIC_SOCKET;
		हाल NETLINK_SCSITRANSPORT:
			वापस SECCLASS_NETLINK_SCSITRANSPORT_SOCKET;
		हाल NETLINK_RDMA:
			वापस SECCLASS_NETLINK_RDMA_SOCKET;
		हाल NETLINK_CRYPTO:
			वापस SECCLASS_NETLINK_CRYPTO_SOCKET;
		शेष:
			वापस SECCLASS_NETLINK_SOCKET;
		पूर्ण
	हाल PF_PACKET:
		वापस SECCLASS_PACKET_SOCKET;
	हाल PF_KEY:
		वापस SECCLASS_KEY_SOCKET;
	हाल PF_APPLETALK:
		वापस SECCLASS_APPLETALK_SOCKET;
	पूर्ण

	अगर (extsockclass) अणु
		चयन (family) अणु
		हाल PF_AX25:
			वापस SECCLASS_AX25_SOCKET;
		हाल PF_IPX:
			वापस SECCLASS_IPX_SOCKET;
		हाल PF_NETROM:
			वापस SECCLASS_NETROM_SOCKET;
		हाल PF_ATMPVC:
			वापस SECCLASS_ATMPVC_SOCKET;
		हाल PF_X25:
			वापस SECCLASS_X25_SOCKET;
		हाल PF_ROSE:
			वापस SECCLASS_ROSE_SOCKET;
		हाल PF_DECnet:
			वापस SECCLASS_DECNET_SOCKET;
		हाल PF_ATMSVC:
			वापस SECCLASS_ATMSVC_SOCKET;
		हाल PF_RDS:
			वापस SECCLASS_RDS_SOCKET;
		हाल PF_IRDA:
			वापस SECCLASS_IRDA_SOCKET;
		हाल PF_PPPOX:
			वापस SECCLASS_PPPOX_SOCKET;
		हाल PF_LLC:
			वापस SECCLASS_LLC_SOCKET;
		हाल PF_CAN:
			वापस SECCLASS_CAN_SOCKET;
		हाल PF_TIPC:
			वापस SECCLASS_TIPC_SOCKET;
		हाल PF_BLUETOOTH:
			वापस SECCLASS_BLUETOOTH_SOCKET;
		हाल PF_IUCV:
			वापस SECCLASS_IUCV_SOCKET;
		हाल PF_RXRPC:
			वापस SECCLASS_RXRPC_SOCKET;
		हाल PF_ISDN:
			वापस SECCLASS_ISDN_SOCKET;
		हाल PF_PHONET:
			वापस SECCLASS_PHONET_SOCKET;
		हाल PF_IEEE802154:
			वापस SECCLASS_IEEE802154_SOCKET;
		हाल PF_CAIF:
			वापस SECCLASS_CAIF_SOCKET;
		हाल PF_ALG:
			वापस SECCLASS_ALG_SOCKET;
		हाल PF_NFC:
			वापस SECCLASS_NFC_SOCKET;
		हाल PF_VSOCK:
			वापस SECCLASS_VSOCK_SOCKET;
		हाल PF_KCM:
			वापस SECCLASS_KCM_SOCKET;
		हाल PF_QIPCRTR:
			वापस SECCLASS_QIPCRTR_SOCKET;
		हाल PF_SMC:
			वापस SECCLASS_SMC_SOCKET;
		हाल PF_XDP:
			वापस SECCLASS_XDP_SOCKET;
#अगर PF_MAX > 45
#त्रुटि New address family defined, please update this function.
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	वापस SECCLASS_SOCKET;
पूर्ण

अटल पूर्णांक selinux_genfs_get_sid(काष्ठा dentry *dentry,
				 u16 tclass,
				 u16 flags,
				 u32 *sid)
अणु
	पूर्णांक rc;
	काष्ठा super_block *sb = dentry->d_sb;
	अक्षर *buffer, *path;

	buffer = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	path = dentry_path_raw(dentry, buffer, PAGE_SIZE);
	अगर (IS_ERR(path))
		rc = PTR_ERR(path);
	अन्यथा अणु
		अगर (flags & SE_SBPROC) अणु
			/* each process माला_लो a /proc/PID/ entry. Strip off the
			 * PID part to get a valid selinux labeling.
			 * e.g. /proc/1/net/rpc/nfs -> /net/rpc/nfs */
			जबतक (path[1] >= '0' && path[1] <= '9') अणु
				path[1] = '/';
				path++;
			पूर्ण
		पूर्ण
		rc = security_genfs_sid(&selinux_state, sb->s_type->name,
					path, tclass, sid);
		अगर (rc == -ENOENT) अणु
			/* No match in policy, mark as unlabeled. */
			*sid = SECINITSID_UNLABELED;
			rc = 0;
		पूर्ण
	पूर्ण
	मुक्त_page((अचिन्हित दीर्घ)buffer);
	वापस rc;
पूर्ण

अटल पूर्णांक inode_करोinit_use_xattr(काष्ठा inode *inode, काष्ठा dentry *dentry,
				  u32 def_sid, u32 *sid)
अणु
#घोषणा INITCONTEXTLEN 255
	अक्षर *context;
	अचिन्हित पूर्णांक len;
	पूर्णांक rc;

	len = INITCONTEXTLEN;
	context = kदो_स्मृति(len + 1, GFP_NOFS);
	अगर (!context)
		वापस -ENOMEM;

	context[len] = '\0';
	rc = __vfs_getxattr(dentry, inode, XATTR_NAME_SELINUX, context, len);
	अगर (rc == -दुस्फल) अणु
		kमुक्त(context);

		/* Need a larger buffer.  Query क्रम the right size. */
		rc = __vfs_getxattr(dentry, inode, XATTR_NAME_SELINUX, शून्य, 0);
		अगर (rc < 0)
			वापस rc;

		len = rc;
		context = kदो_स्मृति(len + 1, GFP_NOFS);
		अगर (!context)
			वापस -ENOMEM;

		context[len] = '\0';
		rc = __vfs_getxattr(dentry, inode, XATTR_NAME_SELINUX,
				    context, len);
	पूर्ण
	अगर (rc < 0) अणु
		kमुक्त(context);
		अगर (rc != -ENODATA) अणु
			pr_warn("SELinux: %s:  getxattr returned %d for dev=%s ino=%ld\n",
				__func__, -rc, inode->i_sb->s_id, inode->i_ino);
			वापस rc;
		पूर्ण
		*sid = def_sid;
		वापस 0;
	पूर्ण

	rc = security_context_to_sid_शेष(&selinux_state, context, rc, sid,
					     def_sid, GFP_NOFS);
	अगर (rc) अणु
		अक्षर *dev = inode->i_sb->s_id;
		अचिन्हित दीर्घ ino = inode->i_ino;

		अगर (rc == -EINVAL) अणु
			pr_notice_ratelimited("SELinux: inode=%lu on dev=%s was found to have an invalid context=%s.  This indicates you may need to relabel the inode or the filesystem in question.\n",
					      ino, dev, context);
		पूर्ण अन्यथा अणु
			pr_warn("SELinux: %s:  context_to_sid(%s) returned %d for dev=%s ino=%ld\n",
				__func__, context, -rc, dev, ino);
		पूर्ण
	पूर्ण
	kमुक्त(context);
	वापस 0;
पूर्ण

/* The inode's security attributes must be initialized beक्रमe first use. */
अटल पूर्णांक inode_करोinit_with_dentry(काष्ठा inode *inode, काष्ठा dentry *opt_dentry)
अणु
	काष्ठा superblock_security_काष्ठा *sbsec = शून्य;
	काष्ठा inode_security_काष्ठा *isec = selinux_inode(inode);
	u32 task_sid, sid = 0;
	u16 sclass;
	काष्ठा dentry *dentry;
	पूर्णांक rc = 0;

	अगर (isec->initialized == LABEL_INITIALIZED)
		वापस 0;

	spin_lock(&isec->lock);
	अगर (isec->initialized == LABEL_INITIALIZED)
		जाओ out_unlock;

	अगर (isec->sclass == SECCLASS_खाता)
		isec->sclass = inode_mode_to_security_class(inode->i_mode);

	sbsec = selinux_superblock(inode->i_sb);
	अगर (!(sbsec->flags & SE_SBINITIALIZED)) अणु
		/* Defer initialization until selinux_complete_init,
		   after the initial policy is loaded and the security
		   server is पढ़ोy to handle calls. */
		spin_lock(&sbsec->isec_lock);
		अगर (list_empty(&isec->list))
			list_add(&isec->list, &sbsec->isec_head);
		spin_unlock(&sbsec->isec_lock);
		जाओ out_unlock;
	पूर्ण

	sclass = isec->sclass;
	task_sid = isec->task_sid;
	sid = isec->sid;
	isec->initialized = LABEL_PENDING;
	spin_unlock(&isec->lock);

	चयन (sbsec->behavior) अणु
	हाल SECURITY_FS_USE_NATIVE:
		अवरोध;
	हाल SECURITY_FS_USE_XATTR:
		अगर (!(inode->i_opflags & IOP_XATTR)) अणु
			sid = sbsec->def_sid;
			अवरोध;
		पूर्ण
		/* Need a dentry, since the xattr API requires one.
		   Lअगरe would be simpler अगर we could just pass the inode. */
		अगर (opt_dentry) अणु
			/* Called from d_instantiate or d_splice_alias. */
			dentry = dget(opt_dentry);
		पूर्ण अन्यथा अणु
			/*
			 * Called from selinux_complete_init, try to find a dentry.
			 * Some fileप्रणालीs really want a connected one, so try
			 * that first.  We could split SECURITY_FS_USE_XATTR in
			 * two, depending upon that...
			 */
			dentry = d_find_alias(inode);
			अगर (!dentry)
				dentry = d_find_any_alias(inode);
		पूर्ण
		अगर (!dentry) अणु
			/*
			 * this is can be hit on boot when a file is accessed
			 * beक्रमe the policy is loaded.  When we load policy we
			 * may find inodes that have no dentry on the
			 * sbsec->isec_head list.  No reason to complain as these
			 * will get fixed up the next समय we go through
			 * inode_करोinit with a dentry, beक्रमe these inodes could
			 * be used again by userspace.
			 */
			जाओ out_invalid;
		पूर्ण

		rc = inode_करोinit_use_xattr(inode, dentry, sbsec->def_sid,
					    &sid);
		dput(dentry);
		अगर (rc)
			जाओ out;
		अवरोध;
	हाल SECURITY_FS_USE_TASK:
		sid = task_sid;
		अवरोध;
	हाल SECURITY_FS_USE_TRANS:
		/* Default to the fs SID. */
		sid = sbsec->sid;

		/* Try to obtain a transition SID. */
		rc = security_transition_sid(&selinux_state, task_sid, sid,
					     sclass, शून्य, &sid);
		अगर (rc)
			जाओ out;
		अवरोध;
	हाल SECURITY_FS_USE_MNTPOINT:
		sid = sbsec->mntpoपूर्णांक_sid;
		अवरोध;
	शेष:
		/* Default to the fs superblock SID. */
		sid = sbsec->sid;

		अगर ((sbsec->flags & SE_SBGENFS) &&
		     (!S_ISLNK(inode->i_mode) ||
		      selinux_policycap_genfs_seclabel_symlinks())) अणु
			/* We must have a dentry to determine the label on
			 * procfs inodes */
			अगर (opt_dentry) अणु
				/* Called from d_instantiate or
				 * d_splice_alias. */
				dentry = dget(opt_dentry);
			पूर्ण अन्यथा अणु
				/* Called from selinux_complete_init, try to
				 * find a dentry.  Some fileप्रणालीs really want
				 * a connected one, so try that first.
				 */
				dentry = d_find_alias(inode);
				अगर (!dentry)
					dentry = d_find_any_alias(inode);
			पूर्ण
			/*
			 * This can be hit on boot when a file is accessed
			 * beक्रमe the policy is loaded.  When we load policy we
			 * may find inodes that have no dentry on the
			 * sbsec->isec_head list.  No reason to complain as
			 * these will get fixed up the next समय we go through
			 * inode_करोinit() with a dentry, beक्रमe these inodes
			 * could be used again by userspace.
			 */
			अगर (!dentry)
				जाओ out_invalid;
			rc = selinux_genfs_get_sid(dentry, sclass,
						   sbsec->flags, &sid);
			अगर (rc) अणु
				dput(dentry);
				जाओ out;
			पूर्ण

			अगर ((sbsec->flags & SE_SBGENFS_XATTR) &&
			    (inode->i_opflags & IOP_XATTR)) अणु
				rc = inode_करोinit_use_xattr(inode, dentry,
							    sid, &sid);
				अगर (rc) अणु
					dput(dentry);
					जाओ out;
				पूर्ण
			पूर्ण
			dput(dentry);
		पूर्ण
		अवरोध;
	पूर्ण

out:
	spin_lock(&isec->lock);
	अगर (isec->initialized == LABEL_PENDING) अणु
		अगर (rc) अणु
			isec->initialized = LABEL_INVALID;
			जाओ out_unlock;
		पूर्ण
		isec->initialized = LABEL_INITIALIZED;
		isec->sid = sid;
	पूर्ण

out_unlock:
	spin_unlock(&isec->lock);
	वापस rc;

out_invalid:
	spin_lock(&isec->lock);
	अगर (isec->initialized == LABEL_PENDING) अणु
		isec->initialized = LABEL_INVALID;
		isec->sid = sid;
	पूर्ण
	spin_unlock(&isec->lock);
	वापस 0;
पूर्ण

/* Convert a Linux संकेत to an access vector. */
अटल अंतरभूत u32 संकेत_to_av(पूर्णांक sig)
अणु
	u32 perm = 0;

	चयन (sig) अणु
	हाल SIGCHLD:
		/* Commonly granted from child to parent. */
		perm = PROCESS__SIGCHLD;
		अवरोध;
	हाल SIGKILL:
		/* Cannot be caught or ignored */
		perm = PROCESS__SIGKILL;
		अवरोध;
	हाल SIGSTOP:
		/* Cannot be caught or ignored */
		perm = PROCESS__SIGSTOP;
		अवरोध;
	शेष:
		/* All other संकेतs. */
		perm = PROCESS__SIGNAL;
		अवरोध;
	पूर्ण

	वापस perm;
पूर्ण

#अगर CAP_LAST_CAP > 63
#त्रुटि Fix SELinux to handle capabilities > 63.
#पूर्ण_अगर

/* Check whether a task is allowed to use a capability. */
अटल पूर्णांक cred_has_capability(स्थिर काष्ठा cred *cred,
			       पूर्णांक cap, अचिन्हित पूर्णांक opts, bool initns)
अणु
	काष्ठा common_audit_data ad;
	काष्ठा av_decision avd;
	u16 sclass;
	u32 sid = cred_sid(cred);
	u32 av = CAP_TO_MASK(cap);
	पूर्णांक rc;

	ad.type = LSM_AUDIT_DATA_CAP;
	ad.u.cap = cap;

	चयन (CAP_TO_INDEX(cap)) अणु
	हाल 0:
		sclass = initns ? SECCLASS_CAPABILITY : SECCLASS_CAP_USERNS;
		अवरोध;
	हाल 1:
		sclass = initns ? SECCLASS_CAPABILITY2 : SECCLASS_CAP2_USERNS;
		अवरोध;
	शेष:
		pr_err("SELinux:  out of range capability %d\n", cap);
		BUG();
		वापस -EINVAL;
	पूर्ण

	rc = avc_has_perm_noaudit(&selinux_state,
				  sid, sid, sclass, av, 0, &avd);
	अगर (!(opts & CAP_OPT_NOAUDIT)) अणु
		पूर्णांक rc2 = avc_audit(&selinux_state,
				    sid, sid, sclass, av, &avd, rc, &ad, 0);
		अगर (rc2)
			वापस rc2;
	पूर्ण
	वापस rc;
पूर्ण

/* Check whether a task has a particular permission to an inode.
   The 'adp' parameter is optional and allows other audit
   data to be passed (e.g. the dentry). */
अटल पूर्णांक inode_has_perm(स्थिर काष्ठा cred *cred,
			  काष्ठा inode *inode,
			  u32 perms,
			  काष्ठा common_audit_data *adp)
अणु
	काष्ठा inode_security_काष्ठा *isec;
	u32 sid;

	validate_creds(cred);

	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;

	sid = cred_sid(cred);
	isec = selinux_inode(inode);

	वापस avc_has_perm(&selinux_state,
			    sid, isec->sid, isec->sclass, perms, adp);
पूर्ण

/* Same as inode_has_perm, but pass explicit audit data containing
   the dentry to help the auditing code to more easily generate the
   pathname अगर needed. */
अटल अंतरभूत पूर्णांक dentry_has_perm(स्थिर काष्ठा cred *cred,
				  काष्ठा dentry *dentry,
				  u32 av)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_DENTRY;
	ad.u.dentry = dentry;
	__inode_security_revalidate(inode, dentry, true);
	वापस inode_has_perm(cred, inode, av, &ad);
पूर्ण

/* Same as inode_has_perm, but pass explicit audit data containing
   the path to help the auditing code to more easily generate the
   pathname अगर needed. */
अटल अंतरभूत पूर्णांक path_has_perm(स्थिर काष्ठा cred *cred,
				स्थिर काष्ठा path *path,
				u32 av)
अणु
	काष्ठा inode *inode = d_backing_inode(path->dentry);
	काष्ठा common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_PATH;
	ad.u.path = *path;
	__inode_security_revalidate(inode, path->dentry, true);
	वापस inode_has_perm(cred, inode, av, &ad);
पूर्ण

/* Same as path_has_perm, but uses the inode from the file काष्ठा. */
अटल अंतरभूत पूर्णांक file_path_has_perm(स्थिर काष्ठा cred *cred,
				     काष्ठा file *file,
				     u32 av)
अणु
	काष्ठा common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_खाता;
	ad.u.file = file;
	वापस inode_has_perm(cred, file_inode(file), av, &ad);
पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
अटल पूर्णांक bpf_fd_pass(काष्ठा file *file, u32 sid);
#पूर्ण_अगर

/* Check whether a task can use an खोलो file descriptor to
   access an inode in a given way.  Check access to the
   descriptor itself, and then use dentry_has_perm to
   check a particular permission to the file.
   Access to the descriptor is implicitly granted अगर it
   has the same SID as the process.  If av is zero, then
   access to the file is not checked, e.g. क्रम हालs
   where only the descriptor is affected like seek. */
अटल पूर्णांक file_has_perm(स्थिर काष्ठा cred *cred,
			 काष्ठा file *file,
			 u32 av)
अणु
	काष्ठा file_security_काष्ठा *fsec = selinux_file(file);
	काष्ठा inode *inode = file_inode(file);
	काष्ठा common_audit_data ad;
	u32 sid = cred_sid(cred);
	पूर्णांक rc;

	ad.type = LSM_AUDIT_DATA_खाता;
	ad.u.file = file;

	अगर (sid != fsec->sid) अणु
		rc = avc_has_perm(&selinux_state,
				  sid, fsec->sid,
				  SECCLASS_FD,
				  FD__USE,
				  &ad);
		अगर (rc)
			जाओ out;
	पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
	rc = bpf_fd_pass(file, cred_sid(cred));
	अगर (rc)
		वापस rc;
#पूर्ण_अगर

	/* av is zero अगर only checking access to the descriptor. */
	rc = 0;
	अगर (av)
		rc = inode_has_perm(cred, inode, av, &ad);

out:
	वापस rc;
पूर्ण

/*
 * Determine the label क्रम an inode that might be जोड़ed.
 */
अटल पूर्णांक
selinux_determine_inode_label(स्थिर काष्ठा task_security_काष्ठा *tsec,
				 काष्ठा inode *dir,
				 स्थिर काष्ठा qstr *name, u16 tclass,
				 u32 *_new_isid)
अणु
	स्थिर काष्ठा superblock_security_काष्ठा *sbsec =
						selinux_superblock(dir->i_sb);

	अगर ((sbsec->flags & SE_SBINITIALIZED) &&
	    (sbsec->behavior == SECURITY_FS_USE_MNTPOINT)) अणु
		*_new_isid = sbsec->mntpoपूर्णांक_sid;
	पूर्ण अन्यथा अगर ((sbsec->flags & SBLABEL_MNT) &&
		   tsec->create_sid) अणु
		*_new_isid = tsec->create_sid;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा inode_security_काष्ठा *dsec = inode_security(dir);
		वापस security_transition_sid(&selinux_state, tsec->sid,
					       dsec->sid, tclass,
					       name, _new_isid);
	पूर्ण

	वापस 0;
पूर्ण

/* Check whether a task can create a file. */
अटल पूर्णांक may_create(काष्ठा inode *dir,
		      काष्ठा dentry *dentry,
		      u16 tclass)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(current_cred());
	काष्ठा inode_security_काष्ठा *dsec;
	काष्ठा superblock_security_काष्ठा *sbsec;
	u32 sid, newsid;
	काष्ठा common_audit_data ad;
	पूर्णांक rc;

	dsec = inode_security(dir);
	sbsec = selinux_superblock(dir->i_sb);

	sid = tsec->sid;

	ad.type = LSM_AUDIT_DATA_DENTRY;
	ad.u.dentry = dentry;

	rc = avc_has_perm(&selinux_state,
			  sid, dsec->sid, SECCLASS_सूची,
			  सूची__ADD_NAME | सूची__SEARCH,
			  &ad);
	अगर (rc)
		वापस rc;

	rc = selinux_determine_inode_label(tsec, dir, &dentry->d_name, tclass,
					   &newsid);
	अगर (rc)
		वापस rc;

	rc = avc_has_perm(&selinux_state,
			  sid, newsid, tclass, खाता__CREATE, &ad);
	अगर (rc)
		वापस rc;

	वापस avc_has_perm(&selinux_state,
			    newsid, sbsec->sid,
			    SECCLASS_खाताSYSTEM,
			    खाताSYSTEM__ASSOCIATE, &ad);
पूर्ण

#घोषणा MAY_LINK	0
#घोषणा MAY_UNLINK	1
#घोषणा MAY_RMसूची	2

/* Check whether a task can link, unlink, or सूची_हटाओ a file/directory. */
अटल पूर्णांक may_link(काष्ठा inode *dir,
		    काष्ठा dentry *dentry,
		    पूर्णांक kind)

अणु
	काष्ठा inode_security_काष्ठा *dsec, *isec;
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();
	u32 av;
	पूर्णांक rc;

	dsec = inode_security(dir);
	isec = backing_inode_security(dentry);

	ad.type = LSM_AUDIT_DATA_DENTRY;
	ad.u.dentry = dentry;

	av = सूची__SEARCH;
	av |= (kind ? सूची__REMOVE_NAME : सूची__ADD_NAME);
	rc = avc_has_perm(&selinux_state,
			  sid, dsec->sid, SECCLASS_सूची, av, &ad);
	अगर (rc)
		वापस rc;

	चयन (kind) अणु
	हाल MAY_LINK:
		av = खाता__LINK;
		अवरोध;
	हाल MAY_UNLINK:
		av = खाता__UNLINK;
		अवरोध;
	हाल MAY_RMसूची:
		av = सूची__RMसूची;
		अवरोध;
	शेष:
		pr_warn("SELinux: %s:  unrecognized kind %d\n",
			__func__, kind);
		वापस 0;
	पूर्ण

	rc = avc_has_perm(&selinux_state,
			  sid, isec->sid, isec->sclass, av, &ad);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक may_नाम(काष्ठा inode *old_dir,
			     काष्ठा dentry *old_dentry,
			     काष्ठा inode *new_dir,
			     काष्ठा dentry *new_dentry)
अणु
	काष्ठा inode_security_काष्ठा *old_dsec, *new_dsec, *old_isec, *new_isec;
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();
	u32 av;
	पूर्णांक old_is_dir, new_is_dir;
	पूर्णांक rc;

	old_dsec = inode_security(old_dir);
	old_isec = backing_inode_security(old_dentry);
	old_is_dir = d_is_dir(old_dentry);
	new_dsec = inode_security(new_dir);

	ad.type = LSM_AUDIT_DATA_DENTRY;

	ad.u.dentry = old_dentry;
	rc = avc_has_perm(&selinux_state,
			  sid, old_dsec->sid, SECCLASS_सूची,
			  सूची__REMOVE_NAME | सूची__SEARCH, &ad);
	अगर (rc)
		वापस rc;
	rc = avc_has_perm(&selinux_state,
			  sid, old_isec->sid,
			  old_isec->sclass, खाता__RENAME, &ad);
	अगर (rc)
		वापस rc;
	अगर (old_is_dir && new_dir != old_dir) अणु
		rc = avc_has_perm(&selinux_state,
				  sid, old_isec->sid,
				  old_isec->sclass, सूची__REPARENT, &ad);
		अगर (rc)
			वापस rc;
	पूर्ण

	ad.u.dentry = new_dentry;
	av = सूची__ADD_NAME | सूची__SEARCH;
	अगर (d_is_positive(new_dentry))
		av |= सूची__REMOVE_NAME;
	rc = avc_has_perm(&selinux_state,
			  sid, new_dsec->sid, SECCLASS_सूची, av, &ad);
	अगर (rc)
		वापस rc;
	अगर (d_is_positive(new_dentry)) अणु
		new_isec = backing_inode_security(new_dentry);
		new_is_dir = d_is_dir(new_dentry);
		rc = avc_has_perm(&selinux_state,
				  sid, new_isec->sid,
				  new_isec->sclass,
				  (new_is_dir ? सूची__RMसूची : खाता__UNLINK), &ad);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/* Check whether a task can perक्रमm a fileप्रणाली operation. */
अटल पूर्णांक superblock_has_perm(स्थिर काष्ठा cred *cred,
			       काष्ठा super_block *sb,
			       u32 perms,
			       काष्ठा common_audit_data *ad)
अणु
	काष्ठा superblock_security_काष्ठा *sbsec;
	u32 sid = cred_sid(cred);

	sbsec = selinux_superblock(sb);
	वापस avc_has_perm(&selinux_state,
			    sid, sbsec->sid, SECCLASS_खाताSYSTEM, perms, ad);
पूर्ण

/* Convert a Linux mode and permission mask to an access vector. */
अटल अंतरभूत u32 file_mask_to_av(पूर्णांक mode, पूर्णांक mask)
अणु
	u32 av = 0;

	अगर (!S_ISसूची(mode)) अणु
		अगर (mask & MAY_EXEC)
			av |= खाता__EXECUTE;
		अगर (mask & MAY_READ)
			av |= खाता__READ;

		अगर (mask & MAY_APPEND)
			av |= खाता__APPEND;
		अन्यथा अगर (mask & MAY_WRITE)
			av |= खाता__WRITE;

	पूर्ण अन्यथा अणु
		अगर (mask & MAY_EXEC)
			av |= सूची__SEARCH;
		अगर (mask & MAY_WRITE)
			av |= सूची__WRITE;
		अगर (mask & MAY_READ)
			av |= सूची__READ;
	पूर्ण

	वापस av;
पूर्ण

/* Convert a Linux file to an access vector. */
अटल अंतरभूत u32 file_to_av(काष्ठा file *file)
अणु
	u32 av = 0;

	अगर (file->f_mode & FMODE_READ)
		av |= खाता__READ;
	अगर (file->f_mode & FMODE_WRITE) अणु
		अगर (file->f_flags & O_APPEND)
			av |= खाता__APPEND;
		अन्यथा
			av |= खाता__WRITE;
	पूर्ण
	अगर (!av) अणु
		/*
		 * Special file खोलोed with flags 3 क्रम ioctl-only use.
		 */
		av = खाता__IOCTL;
	पूर्ण

	वापस av;
पूर्ण

/*
 * Convert a file to an access vector and include the correct
 * खोलो permission.
 */
अटल अंतरभूत u32 खोलो_file_to_av(काष्ठा file *file)
अणु
	u32 av = file_to_av(file);
	काष्ठा inode *inode = file_inode(file);

	अगर (selinux_policycap_खोलोperm() &&
	    inode->i_sb->s_magic != SOCKFS_MAGIC)
		av |= खाता__OPEN;

	वापस av;
पूर्ण

/* Hook functions begin here. */

अटल पूर्णांक selinux_binder_set_context_mgr(काष्ठा task_काष्ठा *mgr)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_binder(mgr), SECCLASS_BINDER,
			    BINDER__SET_CONTEXT_MGR, शून्य);
पूर्ण

अटल पूर्णांक selinux_binder_transaction(काष्ठा task_काष्ठा *from,
				      काष्ठा task_काष्ठा *to)
अणु
	u32 mysid = current_sid();
	u32 fromsid = task_sid_binder(from);
	पूर्णांक rc;

	अगर (mysid != fromsid) अणु
		rc = avc_has_perm(&selinux_state,
				  mysid, fromsid, SECCLASS_BINDER,
				  BINDER__IMPERSONATE, शून्य);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस avc_has_perm(&selinux_state, fromsid, task_sid_binder(to),
			    SECCLASS_BINDER, BINDER__CALL, शून्य);
पूर्ण

अटल पूर्णांक selinux_binder_transfer_binder(काष्ठा task_काष्ठा *from,
					  काष्ठा task_काष्ठा *to)
अणु
	वापस avc_has_perm(&selinux_state,
			    task_sid_binder(from), task_sid_binder(to),
			    SECCLASS_BINDER, BINDER__TRANSFER,
			    शून्य);
पूर्ण

अटल पूर्णांक selinux_binder_transfer_file(काष्ठा task_काष्ठा *from,
					काष्ठा task_काष्ठा *to,
					काष्ठा file *file)
अणु
	u32 sid = task_sid_binder(to);
	काष्ठा file_security_काष्ठा *fsec = selinux_file(file);
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा inode_security_काष्ठा *isec;
	काष्ठा common_audit_data ad;
	पूर्णांक rc;

	ad.type = LSM_AUDIT_DATA_PATH;
	ad.u.path = file->f_path;

	अगर (sid != fsec->sid) अणु
		rc = avc_has_perm(&selinux_state,
				  sid, fsec->sid,
				  SECCLASS_FD,
				  FD__USE,
				  &ad);
		अगर (rc)
			वापस rc;
	पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
	rc = bpf_fd_pass(file, sid);
	अगर (rc)
		वापस rc;
#पूर्ण_अगर

	अगर (unlikely(IS_PRIVATE(d_backing_inode(dentry))))
		वापस 0;

	isec = backing_inode_security(dentry);
	वापस avc_has_perm(&selinux_state,
			    sid, isec->sid, isec->sclass, file_to_av(file),
			    &ad);
पूर्ण

अटल पूर्णांक selinux_ptrace_access_check(काष्ठा task_काष्ठा *child,
				       अचिन्हित पूर्णांक mode)
अणु
	u32 sid = current_sid();
	u32 csid = task_sid_obj(child);

	अगर (mode & PTRACE_MODE_READ)
		वापस avc_has_perm(&selinux_state,
				    sid, csid, SECCLASS_खाता, खाता__READ, शून्य);

	वापस avc_has_perm(&selinux_state,
			    sid, csid, SECCLASS_PROCESS, PROCESS__PTRACE, शून्य);
पूर्ण

अटल पूर्णांक selinux_ptrace_traceme(काष्ठा task_काष्ठा *parent)
अणु
	वापस avc_has_perm(&selinux_state,
			    task_sid_subj(parent), task_sid_obj(current),
			    SECCLASS_PROCESS, PROCESS__PTRACE, शून्य);
पूर्ण

अटल पूर्णांक selinux_capget(काष्ठा task_काष्ठा *target, kernel_cap_t *effective,
			  kernel_cap_t *inheritable, kernel_cap_t *permitted)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_obj(target), SECCLASS_PROCESS,
			    PROCESS__GETCAP, शून्य);
पूर्ण

अटल पूर्णांक selinux_capset(काष्ठा cred *new, स्थिर काष्ठा cred *old,
			  स्थिर kernel_cap_t *effective,
			  स्थिर kernel_cap_t *inheritable,
			  स्थिर kernel_cap_t *permitted)
अणु
	वापस avc_has_perm(&selinux_state,
			    cred_sid(old), cred_sid(new), SECCLASS_PROCESS,
			    PROCESS__SETCAP, शून्य);
पूर्ण

/*
 * (This comment used to live with the selinux_task_setuid hook,
 * which was हटाओd).
 *
 * Since setuid only affects the current process, and since the SELinux
 * controls are not based on the Linux identity attributes, SELinux करोes not
 * need to control this operation.  However, SELinux करोes control the use of
 * the CAP_SETUID and CAP_SETGID capabilities using the capable hook.
 */

अटल पूर्णांक selinux_capable(स्थिर काष्ठा cred *cred, काष्ठा user_namespace *ns,
			   पूर्णांक cap, अचिन्हित पूर्णांक opts)
अणु
	वापस cred_has_capability(cred, cap, opts, ns == &init_user_ns);
पूर्ण

अटल पूर्णांक selinux_quotactl(पूर्णांक cmds, पूर्णांक type, पूर्णांक id, काष्ठा super_block *sb)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक rc = 0;

	अगर (!sb)
		वापस 0;

	चयन (cmds) अणु
	हाल Q_SYNC:
	हाल Q_QUOTAON:
	हाल Q_QUOTAOFF:
	हाल Q_SETINFO:
	हाल Q_SETQUOTA:
	हाल Q_XQUOTAOFF:
	हाल Q_XQUOTAON:
	हाल Q_XSETQLIM:
		rc = superblock_has_perm(cred, sb, खाताSYSTEM__QUOTAMOD, शून्य);
		अवरोध;
	हाल Q_GETFMT:
	हाल Q_GETINFO:
	हाल Q_GETQUOTA:
	हाल Q_XGETQUOTA:
	हाल Q_XGETQSTAT:
	हाल Q_XGETQSTATV:
	हाल Q_XGETNEXTQUOTA:
		rc = superblock_has_perm(cred, sb, खाताSYSTEM__QUOTAGET, शून्य);
		अवरोध;
	शेष:
		rc = 0;  /* let the kernel handle invalid cmds */
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_quota_on(काष्ठा dentry *dentry)
अणु
	स्थिर काष्ठा cred *cred = current_cred();

	वापस dentry_has_perm(cred, dentry, खाता__QUOTAON);
पूर्ण

अटल पूर्णांक selinux_syslog(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल SYSLOG_ACTION_READ_ALL:	/* Read last kernel messages */
	हाल SYSLOG_ACTION_SIZE_BUFFER:	/* Return size of the log buffer */
		वापस avc_has_perm(&selinux_state,
				    current_sid(), SECINITSID_KERNEL,
				    SECCLASS_SYSTEM, SYSTEM__SYSLOG_READ, शून्य);
	हाल SYSLOG_ACTION_CONSOLE_OFF:	/* Disable logging to console */
	हाल SYSLOG_ACTION_CONSOLE_ON:	/* Enable logging to console */
	/* Set level of messages prपूर्णांकed to console */
	हाल SYSLOG_ACTION_CONSOLE_LEVEL:
		वापस avc_has_perm(&selinux_state,
				    current_sid(), SECINITSID_KERNEL,
				    SECCLASS_SYSTEM, SYSTEM__SYSLOG_CONSOLE,
				    शून्य);
	पूर्ण
	/* All other syslog types */
	वापस avc_has_perm(&selinux_state,
			    current_sid(), SECINITSID_KERNEL,
			    SECCLASS_SYSTEM, SYSTEM__SYSLOG_MOD, शून्य);
पूर्ण

/*
 * Check that a process has enough memory to allocate a new भव
 * mapping. 0 means there is enough memory क्रम the allocation to
 * succeed and -ENOMEM implies there is not.
 *
 * Do not audit the selinux permission check, as this is applied to all
 * processes that allocate mappings.
 */
अटल पूर्णांक selinux_vm_enough_memory(काष्ठा mm_काष्ठा *mm, दीर्घ pages)
अणु
	पूर्णांक rc, cap_sys_admin = 0;

	rc = cred_has_capability(current_cred(), CAP_SYS_ADMIN,
				 CAP_OPT_NOAUDIT, true);
	अगर (rc == 0)
		cap_sys_admin = 1;

	वापस cap_sys_admin;
पूर्ण

/* binprm security operations */

अटल u32 ptrace_parent_sid(व्योम)
अणु
	u32 sid = 0;
	काष्ठा task_काष्ठा *tracer;

	rcu_पढ़ो_lock();
	tracer = ptrace_parent(current);
	अगर (tracer)
		sid = task_sid_obj(tracer);
	rcu_पढ़ो_unlock();

	वापस sid;
पूर्ण

अटल पूर्णांक check_nnp_nosuid(स्थिर काष्ठा linux_binprm *bprm,
			    स्थिर काष्ठा task_security_काष्ठा *old_tsec,
			    स्थिर काष्ठा task_security_काष्ठा *new_tsec)
अणु
	पूर्णांक nnp = (bprm->unsafe & LSM_UNSAFE_NO_NEW_PRIVS);
	पूर्णांक nosuid = !mnt_may_suid(bprm->file->f_path.mnt);
	पूर्णांक rc;
	u32 av;

	अगर (!nnp && !nosuid)
		वापस 0; /* neither NNP nor nosuid */

	अगर (new_tsec->sid == old_tsec->sid)
		वापस 0; /* No change in credentials */

	/*
	 * If the policy enables the nnp_nosuid_transition policy capability,
	 * then we permit transitions under NNP or nosuid अगर the
	 * policy allows the corresponding permission between
	 * the old and new contexts.
	 */
	अगर (selinux_policycap_nnp_nosuid_transition()) अणु
		av = 0;
		अगर (nnp)
			av |= PROCESS2__NNP_TRANSITION;
		अगर (nosuid)
			av |= PROCESS2__NOSUID_TRANSITION;
		rc = avc_has_perm(&selinux_state,
				  old_tsec->sid, new_tsec->sid,
				  SECCLASS_PROCESS2, av, शून्य);
		अगर (!rc)
			वापस 0;
	पूर्ण

	/*
	 * We also permit NNP or nosuid transitions to bounded SIDs,
	 * i.e. SIDs that are guaranteed to only be allowed a subset
	 * of the permissions of the current SID.
	 */
	rc = security_bounded_transition(&selinux_state, old_tsec->sid,
					 new_tsec->sid);
	अगर (!rc)
		वापस 0;

	/*
	 * On failure, preserve the त्रुटि_सं values क्रम NNP vs nosuid.
	 * NNP:  Operation not permitted क्रम caller.
	 * nosuid:  Permission denied to file.
	 */
	अगर (nnp)
		वापस -EPERM;
	वापस -EACCES;
पूर्ण

अटल पूर्णांक selinux_bprm_creds_क्रम_exec(काष्ठा linux_binprm *bprm)
अणु
	स्थिर काष्ठा task_security_काष्ठा *old_tsec;
	काष्ठा task_security_काष्ठा *new_tsec;
	काष्ठा inode_security_काष्ठा *isec;
	काष्ठा common_audit_data ad;
	काष्ठा inode *inode = file_inode(bprm->file);
	पूर्णांक rc;

	/* SELinux context only depends on initial program or script and not
	 * the script पूर्णांकerpreter */

	old_tsec = selinux_cred(current_cred());
	new_tsec = selinux_cred(bprm->cred);
	isec = inode_security(inode);

	/* Default to the current task SID. */
	new_tsec->sid = old_tsec->sid;
	new_tsec->osid = old_tsec->sid;

	/* Reset fs, key, and sock SIDs on execve. */
	new_tsec->create_sid = 0;
	new_tsec->keycreate_sid = 0;
	new_tsec->sockcreate_sid = 0;

	अगर (old_tsec->exec_sid) अणु
		new_tsec->sid = old_tsec->exec_sid;
		/* Reset exec SID on execve. */
		new_tsec->exec_sid = 0;

		/* Fail on NNP or nosuid अगर not an allowed transition. */
		rc = check_nnp_nosuid(bprm, old_tsec, new_tsec);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		/* Check क्रम a शेष transition on this program. */
		rc = security_transition_sid(&selinux_state, old_tsec->sid,
					     isec->sid, SECCLASS_PROCESS, शून्य,
					     &new_tsec->sid);
		अगर (rc)
			वापस rc;

		/*
		 * Fallback to old SID on NNP or nosuid अगर not an allowed
		 * transition.
		 */
		rc = check_nnp_nosuid(bprm, old_tsec, new_tsec);
		अगर (rc)
			new_tsec->sid = old_tsec->sid;
	पूर्ण

	ad.type = LSM_AUDIT_DATA_खाता;
	ad.u.file = bprm->file;

	अगर (new_tsec->sid == old_tsec->sid) अणु
		rc = avc_has_perm(&selinux_state,
				  old_tsec->sid, isec->sid,
				  SECCLASS_खाता, खाता__EXECUTE_NO_TRANS, &ad);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		/* Check permissions क्रम the transition. */
		rc = avc_has_perm(&selinux_state,
				  old_tsec->sid, new_tsec->sid,
				  SECCLASS_PROCESS, PROCESS__TRANSITION, &ad);
		अगर (rc)
			वापस rc;

		rc = avc_has_perm(&selinux_state,
				  new_tsec->sid, isec->sid,
				  SECCLASS_खाता, खाता__ENTRYPOINT, &ad);
		अगर (rc)
			वापस rc;

		/* Check क्रम shared state */
		अगर (bprm->unsafe & LSM_UNSAFE_SHARE) अणु
			rc = avc_has_perm(&selinux_state,
					  old_tsec->sid, new_tsec->sid,
					  SECCLASS_PROCESS, PROCESS__SHARE,
					  शून्य);
			अगर (rc)
				वापस -EPERM;
		पूर्ण

		/* Make sure that anyone attempting to ptrace over a task that
		 * changes its SID has the appropriate permit */
		अगर (bprm->unsafe & LSM_UNSAFE_PTRACE) अणु
			u32 ptsid = ptrace_parent_sid();
			अगर (ptsid != 0) अणु
				rc = avc_has_perm(&selinux_state,
						  ptsid, new_tsec->sid,
						  SECCLASS_PROCESS,
						  PROCESS__PTRACE, शून्य);
				अगर (rc)
					वापस -EPERM;
			पूर्ण
		पूर्ण

		/* Clear any possibly unsafe personality bits on exec: */
		bprm->per_clear |= PER_CLEAR_ON_SETID;

		/* Enable secure mode क्रम SIDs transitions unless
		   the noatsecure permission is granted between
		   the two SIDs, i.e. ahp वापसs 0. */
		rc = avc_has_perm(&selinux_state,
				  old_tsec->sid, new_tsec->sid,
				  SECCLASS_PROCESS, PROCESS__NOATSECURE,
				  शून्य);
		bprm->secureexec |= !!rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक match_file(स्थिर व्योम *p, काष्ठा file *file, अचिन्हित fd)
अणु
	वापस file_has_perm(p, file, file_to_av(file)) ? fd + 1 : 0;
पूर्ण

/* Derived from fs/exec.c:flush_old_files. */
अटल अंतरभूत व्योम flush_unauthorized_files(स्थिर काष्ठा cred *cred,
					    काष्ठा files_काष्ठा *files)
अणु
	काष्ठा file *file, *devnull = शून्य;
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक drop_tty = 0;
	अचिन्हित n;

	tty = get_current_tty();
	अगर (tty) अणु
		spin_lock(&tty->files_lock);
		अगर (!list_empty(&tty->tty_files)) अणु
			काष्ठा tty_file_निजी *file_priv;

			/* Revalidate access to controlling tty.
			   Use file_path_has_perm on the tty path directly
			   rather than using file_has_perm, as this particular
			   खोलो file may beदीर्घ to another process and we are
			   only पूर्णांकerested in the inode-based check here. */
			file_priv = list_first_entry(&tty->tty_files,
						काष्ठा tty_file_निजी, list);
			file = file_priv->file;
			अगर (file_path_has_perm(cred, file, खाता__READ | खाता__WRITE))
				drop_tty = 1;
		पूर्ण
		spin_unlock(&tty->files_lock);
		tty_kref_put(tty);
	पूर्ण
	/* Reset controlling tty. */
	अगर (drop_tty)
		no_tty();

	/* Revalidate access to inherited खोलो files. */
	n = iterate_fd(files, 0, match_file, cred);
	अगर (!n) /* none found? */
		वापस;

	devnull = dentry_खोलो(&selinux_null, O_RDWR, cred);
	अगर (IS_ERR(devnull))
		devnull = शून्य;
	/* replace all the matching ones with this */
	करो अणु
		replace_fd(n - 1, devnull, 0);
	पूर्ण जबतक ((n = iterate_fd(files, n, match_file, cred)) != 0);
	अगर (devnull)
		fput(devnull);
पूर्ण

/*
 * Prepare a process क्रम imminent new credential changes due to exec
 */
अटल व्योम selinux_bprm_committing_creds(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा task_security_काष्ठा *new_tsec;
	काष्ठा rlimit *rlim, *initrlim;
	पूर्णांक rc, i;

	new_tsec = selinux_cred(bprm->cred);
	अगर (new_tsec->sid == new_tsec->osid)
		वापस;

	/* Close files क्रम which the new task SID is not authorized. */
	flush_unauthorized_files(bprm->cred, current->files);

	/* Always clear parent death संकेत on SID transitions. */
	current->pdeath_संकेत = 0;

	/* Check whether the new SID can inherit resource limits from the old
	 * SID.  If not, reset all soft limits to the lower of the current
	 * task's hard limit and the init task's soft limit.
	 *
	 * Note that the setting of hard limits (even to lower them) can be
	 * controlled by the setrlimit check.  The inclusion of the init task's
	 * soft limit पूर्णांकo the computation is to aव्योम resetting soft limits
	 * higher than the शेष soft limit क्रम हालs where the शेष is
	 * lower than the hard limit, e.g. RLIMIT_CORE or RLIMIT_STACK.
	 */
	rc = avc_has_perm(&selinux_state,
			  new_tsec->osid, new_tsec->sid, SECCLASS_PROCESS,
			  PROCESS__RLIMITINH, शून्य);
	अगर (rc) अणु
		/* protect against करो_prlimit() */
		task_lock(current);
		क्रम (i = 0; i < RLIM_NLIMITS; i++) अणु
			rlim = current->संकेत->rlim + i;
			initrlim = init_task.संकेत->rlim + i;
			rlim->rlim_cur = min(rlim->rlim_max, initrlim->rlim_cur);
		पूर्ण
		task_unlock(current);
		अगर (IS_ENABLED(CONFIG_POSIX_TIMERS))
			update_rlimit_cpu(current, rlimit(RLIMIT_CPU));
	पूर्ण
पूर्ण

/*
 * Clean up the process immediately after the installation of new credentials
 * due to exec
 */
अटल व्योम selinux_bprm_committed_creds(काष्ठा linux_binprm *bprm)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(current_cred());
	u32 osid, sid;
	पूर्णांक rc;

	osid = tsec->osid;
	sid = tsec->sid;

	अगर (sid == osid)
		वापस;

	/* Check whether the new SID can inherit संकेत state from the old SID.
	 * If not, clear iसमयrs to aव्योम subsequent संकेत generation and
	 * flush and unblock संकेतs.
	 *
	 * This must occur _after_ the task SID has been updated so that any
	 * समाप्त करोne after the flush will be checked against the new SID.
	 */
	rc = avc_has_perm(&selinux_state,
			  osid, sid, SECCLASS_PROCESS, PROCESS__SIGINH, शून्य);
	अगर (rc) अणु
		clear_iसमयr();

		spin_lock_irq(&current->sighand->siglock);
		अगर (!fatal_संकेत_pending(current)) अणु
			flush_sigqueue(&current->pending);
			flush_sigqueue(&current->संकेत->shared_pending);
			flush_संकेत_handlers(current, 1);
			sigemptyset(&current->blocked);
			recalc_संक_बाकी();
		पूर्ण
		spin_unlock_irq(&current->sighand->siglock);
	पूर्ण

	/* Wake up the parent अगर it is रुकोing so that it can recheck
	 * रुको permission to the new task SID. */
	पढ़ो_lock(&tasklist_lock);
	__wake_up_parent(current, current->real_parent);
	पढ़ो_unlock(&tasklist_lock);
पूर्ण

/* superblock security operations */

अटल पूर्णांक selinux_sb_alloc_security(काष्ठा super_block *sb)
अणु
	काष्ठा superblock_security_काष्ठा *sbsec = selinux_superblock(sb);

	mutex_init(&sbsec->lock);
	INIT_LIST_HEAD(&sbsec->isec_head);
	spin_lock_init(&sbsec->isec_lock);
	sbsec->sid = SECINITSID_UNLABELED;
	sbsec->def_sid = SECINITSID_खाता;
	sbsec->mntpoपूर्णांक_sid = SECINITSID_UNLABELED;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक opt_len(स्थिर अक्षर *s)
अणु
	bool खोलो_quote = false;
	पूर्णांक len;
	अक्षर c;

	क्रम (len = 0; (c = s[len]) != '\0'; len++) अणु
		अगर (c == '"')
			खोलो_quote = !खोलो_quote;
		अगर (c == ',' && !खोलो_quote)
			अवरोध;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक selinux_sb_eat_lsm_opts(अक्षर *options, व्योम **mnt_opts)
अणु
	अक्षर *from = options;
	अक्षर *to = options;
	bool first = true;
	पूर्णांक rc;

	जबतक (1) अणु
		पूर्णांक len = opt_len(from);
		पूर्णांक token;
		अक्षर *arg = शून्य;

		token = match_opt_prefix(from, len, &arg);

		अगर (token != Opt_error) अणु
			अक्षर *p, *q;

			/* strip quotes */
			अगर (arg) अणु
				क्रम (p = q = arg; p < from + len; p++) अणु
					अक्षर c = *p;
					अगर (c != '"')
						*q++ = c;
				पूर्ण
				arg = kmemdup_nul(arg, q - arg, GFP_KERNEL);
				अगर (!arg) अणु
					rc = -ENOMEM;
					जाओ मुक्त_opt;
				पूर्ण
			पूर्ण
			rc = selinux_add_opt(token, arg, mnt_opts);
			अगर (unlikely(rc)) अणु
				kमुक्त(arg);
				जाओ मुक्त_opt;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!first) अणु	// copy with preceding comma
				from--;
				len++;
			पूर्ण
			अगर (to != from)
				स_हटाओ(to, from, len);
			to += len;
			first = false;
		पूर्ण
		अगर (!from[len])
			अवरोध;
		from += len + 1;
	पूर्ण
	*to = '\0';
	वापस 0;

मुक्त_opt:
	अगर (*mnt_opts) अणु
		selinux_मुक्त_mnt_opts(*mnt_opts);
		*mnt_opts = शून्य;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_sb_mnt_opts_compat(काष्ठा super_block *sb, व्योम *mnt_opts)
अणु
	काष्ठा selinux_mnt_opts *opts = mnt_opts;
	काष्ठा superblock_security_काष्ठा *sbsec = sb->s_security;
	u32 sid;
	पूर्णांक rc;

	/*
	 * Superblock not initialized (i.e. no options) - reject अगर any
	 * options specअगरied, otherwise accept.
	 */
	अगर (!(sbsec->flags & SE_SBINITIALIZED))
		वापस opts ? 1 : 0;

	/*
	 * Superblock initialized and no options specअगरied - reject अगर
	 * superblock has any options set, otherwise accept.
	 */
	अगर (!opts)
		वापस (sbsec->flags & SE_MNTMASK) ? 1 : 0;

	अगर (opts->fscontext) अणु
		rc = parse_sid(sb, opts->fscontext, &sid);
		अगर (rc)
			वापस 1;
		अगर (bad_option(sbsec, FSCONTEXT_MNT, sbsec->sid, sid))
			वापस 1;
	पूर्ण
	अगर (opts->context) अणु
		rc = parse_sid(sb, opts->context, &sid);
		अगर (rc)
			वापस 1;
		अगर (bad_option(sbsec, CONTEXT_MNT, sbsec->mntpoपूर्णांक_sid, sid))
			वापस 1;
	पूर्ण
	अगर (opts->rootcontext) अणु
		काष्ठा inode_security_काष्ठा *root_isec;

		root_isec = backing_inode_security(sb->s_root);
		rc = parse_sid(sb, opts->rootcontext, &sid);
		अगर (rc)
			वापस 1;
		अगर (bad_option(sbsec, ROOTCONTEXT_MNT, root_isec->sid, sid))
			वापस 1;
	पूर्ण
	अगर (opts->defcontext) अणु
		rc = parse_sid(sb, opts->defcontext, &sid);
		अगर (rc)
			वापस 1;
		अगर (bad_option(sbsec, DEFCONTEXT_MNT, sbsec->def_sid, sid))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक selinux_sb_remount(काष्ठा super_block *sb, व्योम *mnt_opts)
अणु
	काष्ठा selinux_mnt_opts *opts = mnt_opts;
	काष्ठा superblock_security_काष्ठा *sbsec = selinux_superblock(sb);
	u32 sid;
	पूर्णांक rc;

	अगर (!(sbsec->flags & SE_SBINITIALIZED))
		वापस 0;

	अगर (!opts)
		वापस 0;

	अगर (opts->fscontext) अणु
		rc = parse_sid(sb, opts->fscontext, &sid);
		अगर (rc)
			वापस rc;
		अगर (bad_option(sbsec, FSCONTEXT_MNT, sbsec->sid, sid))
			जाओ out_bad_option;
	पूर्ण
	अगर (opts->context) अणु
		rc = parse_sid(sb, opts->context, &sid);
		अगर (rc)
			वापस rc;
		अगर (bad_option(sbsec, CONTEXT_MNT, sbsec->mntpoपूर्णांक_sid, sid))
			जाओ out_bad_option;
	पूर्ण
	अगर (opts->rootcontext) अणु
		काष्ठा inode_security_काष्ठा *root_isec;
		root_isec = backing_inode_security(sb->s_root);
		rc = parse_sid(sb, opts->rootcontext, &sid);
		अगर (rc)
			वापस rc;
		अगर (bad_option(sbsec, ROOTCONTEXT_MNT, root_isec->sid, sid))
			जाओ out_bad_option;
	पूर्ण
	अगर (opts->defcontext) अणु
		rc = parse_sid(sb, opts->defcontext, &sid);
		अगर (rc)
			वापस rc;
		अगर (bad_option(sbsec, DEFCONTEXT_MNT, sbsec->def_sid, sid))
			जाओ out_bad_option;
	पूर्ण
	वापस 0;

out_bad_option:
	pr_warn("SELinux: unable to change security options "
	       "during remount (dev %s, type=%s)\n", sb->s_id,
	       sb->s_type->name);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक selinux_sb_kern_mount(काष्ठा super_block *sb)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_DENTRY;
	ad.u.dentry = sb->s_root;
	वापस superblock_has_perm(cred, sb, खाताSYSTEM__MOUNT, &ad);
पूर्ण

अटल पूर्णांक selinux_sb_statfs(काष्ठा dentry *dentry)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_DENTRY;
	ad.u.dentry = dentry->d_sb->s_root;
	वापस superblock_has_perm(cred, dentry->d_sb, खाताSYSTEM__GETATTR, &ad);
पूर्ण

अटल पूर्णांक selinux_mount(स्थिर अक्षर *dev_name,
			 स्थिर काष्ठा path *path,
			 स्थिर अक्षर *type,
			 अचिन्हित दीर्घ flags,
			 व्योम *data)
अणु
	स्थिर काष्ठा cred *cred = current_cred();

	अगर (flags & MS_REMOUNT)
		वापस superblock_has_perm(cred, path->dentry->d_sb,
					   खाताSYSTEM__REMOUNT, शून्य);
	अन्यथा
		वापस path_has_perm(cred, path, खाता__MOUNTON);
पूर्ण

अटल पूर्णांक selinux_move_mount(स्थिर काष्ठा path *from_path,
			      स्थिर काष्ठा path *to_path)
अणु
	स्थिर काष्ठा cred *cred = current_cred();

	वापस path_has_perm(cred, to_path, खाता__MOUNTON);
पूर्ण

अटल पूर्णांक selinux_umount(काष्ठा vfsmount *mnt, पूर्णांक flags)
अणु
	स्थिर काष्ठा cred *cred = current_cred();

	वापस superblock_has_perm(cred, mnt->mnt_sb,
				   खाताSYSTEM__UNMOUNT, शून्य);
पूर्ण

अटल पूर्णांक selinux_fs_context_dup(काष्ठा fs_context *fc,
				  काष्ठा fs_context *src_fc)
अणु
	स्थिर काष्ठा selinux_mnt_opts *src = src_fc->security;
	काष्ठा selinux_mnt_opts *opts;

	अगर (!src)
		वापस 0;

	fc->security = kzalloc(माप(काष्ठा selinux_mnt_opts), GFP_KERNEL);
	अगर (!fc->security)
		वापस -ENOMEM;

	opts = fc->security;

	अगर (src->fscontext) अणु
		opts->fscontext = kstrdup(src->fscontext, GFP_KERNEL);
		अगर (!opts->fscontext)
			वापस -ENOMEM;
	पूर्ण
	अगर (src->context) अणु
		opts->context = kstrdup(src->context, GFP_KERNEL);
		अगर (!opts->context)
			वापस -ENOMEM;
	पूर्ण
	अगर (src->rootcontext) अणु
		opts->rootcontext = kstrdup(src->rootcontext, GFP_KERNEL);
		अगर (!opts->rootcontext)
			वापस -ENOMEM;
	पूर्ण
	अगर (src->defcontext) अणु
		opts->defcontext = kstrdup(src->defcontext, GFP_KERNEL);
		अगर (!opts->defcontext)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fs_parameter_spec selinux_fs_parameters[] = अणु
	fsparam_string(CONTEXT_STR,	Opt_context),
	fsparam_string(DEFCONTEXT_STR,	Opt_defcontext),
	fsparam_string(FSCONTEXT_STR,	Opt_fscontext),
	fsparam_string(ROOTCONTEXT_STR,	Opt_rootcontext),
	fsparam_flag  (SECLABEL_STR,	Opt_seclabel),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक selinux_fs_context_parse_param(काष्ठा fs_context *fc,
					  काष्ठा fs_parameter *param)
अणु
	काष्ठा fs_parse_result result;
	पूर्णांक opt, rc;

	opt = fs_parse(fc, selinux_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	rc = selinux_add_opt(opt, param->string, &fc->security);
	अगर (!rc) अणु
		param->string = शून्य;
		rc = 1;
	पूर्ण
	वापस rc;
पूर्ण

/* inode security operations */

अटल पूर्णांक selinux_inode_alloc_security(काष्ठा inode *inode)
अणु
	काष्ठा inode_security_काष्ठा *isec = selinux_inode(inode);
	u32 sid = current_sid();

	spin_lock_init(&isec->lock);
	INIT_LIST_HEAD(&isec->list);
	isec->inode = inode;
	isec->sid = SECINITSID_UNLABELED;
	isec->sclass = SECCLASS_खाता;
	isec->task_sid = sid;
	isec->initialized = LABEL_INVALID;

	वापस 0;
पूर्ण

अटल व्योम selinux_inode_मुक्त_security(काष्ठा inode *inode)
अणु
	inode_मुक्त_security(inode);
पूर्ण

अटल पूर्णांक selinux_dentry_init_security(काष्ठा dentry *dentry, पूर्णांक mode,
					स्थिर काष्ठा qstr *name, व्योम **ctx,
					u32 *ctxlen)
अणु
	u32 newsid;
	पूर्णांक rc;

	rc = selinux_determine_inode_label(selinux_cred(current_cred()),
					   d_inode(dentry->d_parent), name,
					   inode_mode_to_security_class(mode),
					   &newsid);
	अगर (rc)
		वापस rc;

	वापस security_sid_to_context(&selinux_state, newsid, (अक्षर **)ctx,
				       ctxlen);
पूर्ण

अटल पूर्णांक selinux_dentry_create_files_as(काष्ठा dentry *dentry, पूर्णांक mode,
					  काष्ठा qstr *name,
					  स्थिर काष्ठा cred *old,
					  काष्ठा cred *new)
अणु
	u32 newsid;
	पूर्णांक rc;
	काष्ठा task_security_काष्ठा *tsec;

	rc = selinux_determine_inode_label(selinux_cred(old),
					   d_inode(dentry->d_parent), name,
					   inode_mode_to_security_class(mode),
					   &newsid);
	अगर (rc)
		वापस rc;

	tsec = selinux_cred(new);
	tsec->create_sid = newsid;
	वापस 0;
पूर्ण

अटल पूर्णांक selinux_inode_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				       स्थिर काष्ठा qstr *qstr,
				       स्थिर अक्षर **name,
				       व्योम **value, माप_प्रकार *len)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(current_cred());
	काष्ठा superblock_security_काष्ठा *sbsec;
	u32 newsid, clen;
	पूर्णांक rc;
	अक्षर *context;

	sbsec = selinux_superblock(dir->i_sb);

	newsid = tsec->create_sid;

	rc = selinux_determine_inode_label(tsec, dir, qstr,
		inode_mode_to_security_class(inode->i_mode),
		&newsid);
	अगर (rc)
		वापस rc;

	/* Possibly defer initialization to selinux_complete_init. */
	अगर (sbsec->flags & SE_SBINITIALIZED) अणु
		काष्ठा inode_security_काष्ठा *isec = selinux_inode(inode);
		isec->sclass = inode_mode_to_security_class(inode->i_mode);
		isec->sid = newsid;
		isec->initialized = LABEL_INITIALIZED;
	पूर्ण

	अगर (!selinux_initialized(&selinux_state) ||
	    !(sbsec->flags & SBLABEL_MNT))
		वापस -EOPNOTSUPP;

	अगर (name)
		*name = XATTR_SELINUX_SUFFIX;

	अगर (value && len) अणु
		rc = security_sid_to_context_क्रमce(&selinux_state, newsid,
						   &context, &clen);
		अगर (rc)
			वापस rc;
		*value = context;
		*len = clen;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक selinux_inode_init_security_anon(काष्ठा inode *inode,
					    स्थिर काष्ठा qstr *name,
					    स्थिर काष्ठा inode *context_inode)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(current_cred());
	काष्ठा common_audit_data ad;
	काष्ठा inode_security_काष्ठा *isec;
	पूर्णांक rc;

	अगर (unlikely(!selinux_initialized(&selinux_state)))
		वापस 0;

	isec = selinux_inode(inode);

	/*
	 * We only get here once per ephemeral inode.  The inode has
	 * been initialized via inode_alloc_security but is otherwise
	 * untouched.
	 */

	अगर (context_inode) अणु
		काष्ठा inode_security_काष्ठा *context_isec =
			selinux_inode(context_inode);
		अगर (context_isec->initialized != LABEL_INITIALIZED) अणु
			pr_err("SELinux:  context_inode is not initialized");
			वापस -EACCES;
		पूर्ण

		isec->sclass = context_isec->sclass;
		isec->sid = context_isec->sid;
	पूर्ण अन्यथा अणु
		isec->sclass = SECCLASS_ANON_INODE;
		rc = security_transition_sid(
			&selinux_state, tsec->sid, tsec->sid,
			isec->sclass, name, &isec->sid);
		अगर (rc)
			वापस rc;
	पूर्ण

	isec->initialized = LABEL_INITIALIZED;
	/*
	 * Now that we've initialized security, check whether we're
	 * allowed to actually create this type of anonymous inode.
	 */

	ad.type = LSM_AUDIT_DATA_INODE;
	ad.u.inode = inode;

	वापस avc_has_perm(&selinux_state,
			    tsec->sid,
			    isec->sid,
			    isec->sclass,
			    खाता__CREATE,
			    &ad);
पूर्ण

अटल पूर्णांक selinux_inode_create(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode)
अणु
	वापस may_create(dir, dentry, SECCLASS_खाता);
पूर्ण

अटल पूर्णांक selinux_inode_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir, काष्ठा dentry *new_dentry)
अणु
	वापस may_link(dir, old_dentry, MAY_LINK);
पूर्ण

अटल पूर्णांक selinux_inode_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	वापस may_link(dir, dentry, MAY_UNLINK);
पूर्ण

अटल पूर्णांक selinux_inode_symlink(काष्ठा inode *dir, काष्ठा dentry *dentry, स्थिर अक्षर *name)
अणु
	वापस may_create(dir, dentry, SECCLASS_LNK_खाता);
पूर्ण

अटल पूर्णांक selinux_inode_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mask)
अणु
	वापस may_create(dir, dentry, SECCLASS_सूची);
पूर्ण

अटल पूर्णांक selinux_inode_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	वापस may_link(dir, dentry, MAY_RMसूची);
पूर्ण

अटल पूर्णांक selinux_inode_mknod(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode, dev_t dev)
अणु
	वापस may_create(dir, dentry, inode_mode_to_security_class(mode));
पूर्ण

अटल पूर्णांक selinux_inode_नाम(काष्ठा inode *old_inode, काष्ठा dentry *old_dentry,
				काष्ठा inode *new_inode, काष्ठा dentry *new_dentry)
अणु
	वापस may_नाम(old_inode, old_dentry, new_inode, new_dentry);
पूर्ण

अटल पूर्णांक selinux_inode_पढ़ोlink(काष्ठा dentry *dentry)
अणु
	स्थिर काष्ठा cred *cred = current_cred();

	वापस dentry_has_perm(cred, dentry, खाता__READ);
पूर्ण

अटल पूर्णांक selinux_inode_follow_link(काष्ठा dentry *dentry, काष्ठा inode *inode,
				     bool rcu)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा common_audit_data ad;
	काष्ठा inode_security_काष्ठा *isec;
	u32 sid;

	validate_creds(cred);

	ad.type = LSM_AUDIT_DATA_DENTRY;
	ad.u.dentry = dentry;
	sid = cred_sid(cred);
	isec = inode_security_rcu(inode, rcu);
	अगर (IS_ERR(isec))
		वापस PTR_ERR(isec);

	वापस avc_has_perm_flags(&selinux_state,
				  sid, isec->sid, isec->sclass, खाता__READ, &ad,
				  rcu ? MAY_NOT_BLOCK : 0);
पूर्ण

अटल noअंतरभूत पूर्णांक audit_inode_permission(काष्ठा inode *inode,
					   u32 perms, u32 audited, u32 denied,
					   पूर्णांक result)
अणु
	काष्ठा common_audit_data ad;
	काष्ठा inode_security_काष्ठा *isec = selinux_inode(inode);
	पूर्णांक rc;

	ad.type = LSM_AUDIT_DATA_INODE;
	ad.u.inode = inode;

	rc = slow_avc_audit(&selinux_state,
			    current_sid(), isec->sid, isec->sclass, perms,
			    audited, denied, result, &ad);
	अगर (rc)
		वापस rc;
	वापस 0;
पूर्ण

अटल पूर्णांक selinux_inode_permission(काष्ठा inode *inode, पूर्णांक mask)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	u32 perms;
	bool from_access;
	bool no_block = mask & MAY_NOT_BLOCK;
	काष्ठा inode_security_काष्ठा *isec;
	u32 sid;
	काष्ठा av_decision avd;
	पूर्णांक rc, rc2;
	u32 audited, denied;

	from_access = mask & MAY_ACCESS;
	mask &= (MAY_READ|MAY_WRITE|MAY_EXEC|MAY_APPEND);

	/* No permission to check.  Existence test. */
	अगर (!mask)
		वापस 0;

	validate_creds(cred);

	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;

	perms = file_mask_to_av(inode->i_mode, mask);

	sid = cred_sid(cred);
	isec = inode_security_rcu(inode, no_block);
	अगर (IS_ERR(isec))
		वापस PTR_ERR(isec);

	rc = avc_has_perm_noaudit(&selinux_state,
				  sid, isec->sid, isec->sclass, perms,
				  no_block ? AVC_NONBLOCKING : 0,
				  &avd);
	audited = avc_audit_required(perms, &avd, rc,
				     from_access ? खाता__AUDIT_ACCESS : 0,
				     &denied);
	अगर (likely(!audited))
		वापस rc;

	/* fall back to ref-walk अगर we have to generate audit */
	अगर (no_block)
		वापस -ECHILD;

	rc2 = audit_inode_permission(inode, perms, audited, denied, rc);
	अगर (rc2)
		वापस rc2;
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_inode_setattr(काष्ठा dentry *dentry, काष्ठा iattr *iattr)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा inode *inode = d_backing_inode(dentry);
	अचिन्हित पूर्णांक ia_valid = iattr->ia_valid;
	__u32 av = खाता__WRITE;

	/* ATTR_FORCE is just used क्रम ATTR_KILL_S[UG]ID. */
	अगर (ia_valid & ATTR_FORCE) अणु
		ia_valid &= ~(ATTR_KILL_SUID | ATTR_KILL_SGID | ATTR_MODE |
			      ATTR_FORCE);
		अगर (!ia_valid)
			वापस 0;
	पूर्ण

	अगर (ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID |
			ATTR_ATIME_SET | ATTR_MTIME_SET | ATTR_TIMES_SET))
		वापस dentry_has_perm(cred, dentry, खाता__SETATTR);

	अगर (selinux_policycap_खोलोperm() &&
	    inode->i_sb->s_magic != SOCKFS_MAGIC &&
	    (ia_valid & ATTR_SIZE) &&
	    !(ia_valid & ATTR_खाता))
		av |= खाता__OPEN;

	वापस dentry_has_perm(cred, dentry, av);
पूर्ण

अटल पूर्णांक selinux_inode_getattr(स्थिर काष्ठा path *path)
अणु
	वापस path_has_perm(current_cred(), path, खाता__GETATTR);
पूर्ण

अटल bool has_cap_mac_admin(bool audit)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	अचिन्हित पूर्णांक opts = audit ? CAP_OPT_NONE : CAP_OPT_NOAUDIT;

	अगर (cap_capable(cred, &init_user_ns, CAP_MAC_ADMIN, opts))
		वापस false;
	अगर (cred_has_capability(cred, CAP_MAC_ADMIN, opts, true))
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक selinux_inode_setxattr(काष्ठा user_namespace *mnt_userns,
				  काष्ठा dentry *dentry, स्थिर अक्षर *name,
				  स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा inode_security_काष्ठा *isec;
	काष्ठा superblock_security_काष्ठा *sbsec;
	काष्ठा common_audit_data ad;
	u32 newsid, sid = current_sid();
	पूर्णांक rc = 0;

	अगर (म_भेद(name, XATTR_NAME_SELINUX)) अणु
		rc = cap_inode_setxattr(dentry, name, value, size, flags);
		अगर (rc)
			वापस rc;

		/* Not an attribute we recognize, so just check the
		   ordinary setattr permission. */
		वापस dentry_has_perm(current_cred(), dentry, खाता__SETATTR);
	पूर्ण

	अगर (!selinux_initialized(&selinux_state))
		वापस (inode_owner_or_capable(mnt_userns, inode) ? 0 : -EPERM);

	sbsec = selinux_superblock(inode->i_sb);
	अगर (!(sbsec->flags & SBLABEL_MNT))
		वापस -EOPNOTSUPP;

	अगर (!inode_owner_or_capable(mnt_userns, inode))
		वापस -EPERM;

	ad.type = LSM_AUDIT_DATA_DENTRY;
	ad.u.dentry = dentry;

	isec = backing_inode_security(dentry);
	rc = avc_has_perm(&selinux_state,
			  sid, isec->sid, isec->sclass,
			  खाता__RELABELFROM, &ad);
	अगर (rc)
		वापस rc;

	rc = security_context_to_sid(&selinux_state, value, size, &newsid,
				     GFP_KERNEL);
	अगर (rc == -EINVAL) अणु
		अगर (!has_cap_mac_admin(true)) अणु
			काष्ठा audit_buffer *ab;
			माप_प्रकार audit_size;

			/* We strip a nul only अगर it is at the end, otherwise the
			 * context contains a nul and we should audit that */
			अगर (value) अणु
				स्थिर अक्षर *str = value;

				अगर (str[size - 1] == '\0')
					audit_size = size - 1;
				अन्यथा
					audit_size = size;
			पूर्ण अन्यथा अणु
				audit_size = 0;
			पूर्ण
			ab = audit_log_start(audit_context(),
					     GFP_ATOMIC, AUDIT_SELINUX_ERR);
			audit_log_क्रमmat(ab, "op=setxattr invalid_context=");
			audit_log_n_untrustedstring(ab, value, audit_size);
			audit_log_end(ab);

			वापस rc;
		पूर्ण
		rc = security_context_to_sid_क्रमce(&selinux_state, value,
						   size, &newsid);
	पूर्ण
	अगर (rc)
		वापस rc;

	rc = avc_has_perm(&selinux_state,
			  sid, newsid, isec->sclass,
			  खाता__RELABELTO, &ad);
	अगर (rc)
		वापस rc;

	rc = security_validate_transition(&selinux_state, isec->sid, newsid,
					  sid, isec->sclass);
	अगर (rc)
		वापस rc;

	वापस avc_has_perm(&selinux_state,
			    newsid,
			    sbsec->sid,
			    SECCLASS_खाताSYSTEM,
			    खाताSYSTEM__ASSOCIATE,
			    &ad);
पूर्ण

अटल व्योम selinux_inode_post_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name,
					स्थिर व्योम *value, माप_प्रकार size,
					पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा inode_security_काष्ठा *isec;
	u32 newsid;
	पूर्णांक rc;

	अगर (म_भेद(name, XATTR_NAME_SELINUX)) अणु
		/* Not an attribute we recognize, so nothing to करो. */
		वापस;
	पूर्ण

	अगर (!selinux_initialized(&selinux_state)) अणु
		/* If we haven't even been initialized, then we can't validate
		 * against a policy, so leave the label as invalid. It may
		 * resolve to a valid label on the next revalidation try अगर
		 * we've since initialized.
		 */
		वापस;
	पूर्ण

	rc = security_context_to_sid_क्रमce(&selinux_state, value, size,
					   &newsid);
	अगर (rc) अणु
		pr_err("SELinux:  unable to map context to SID"
		       "for (%s, %lu), rc=%d\n",
		       inode->i_sb->s_id, inode->i_ino, -rc);
		वापस;
	पूर्ण

	isec = backing_inode_security(dentry);
	spin_lock(&isec->lock);
	isec->sclass = inode_mode_to_security_class(inode->i_mode);
	isec->sid = newsid;
	isec->initialized = LABEL_INITIALIZED;
	spin_unlock(&isec->lock);

	वापस;
पूर्ण

अटल पूर्णांक selinux_inode_getxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा cred *cred = current_cred();

	वापस dentry_has_perm(cred, dentry, खाता__GETATTR);
पूर्ण

अटल पूर्णांक selinux_inode_listxattr(काष्ठा dentry *dentry)
अणु
	स्थिर काष्ठा cred *cred = current_cred();

	वापस dentry_has_perm(cred, dentry, खाता__GETATTR);
पूर्ण

अटल पूर्णांक selinux_inode_हटाओxattr(काष्ठा user_namespace *mnt_userns,
				     काष्ठा dentry *dentry, स्थिर अक्षर *name)
अणु
	अगर (म_भेद(name, XATTR_NAME_SELINUX)) अणु
		पूर्णांक rc = cap_inode_हटाओxattr(mnt_userns, dentry, name);
		अगर (rc)
			वापस rc;

		/* Not an attribute we recognize, so just check the
		   ordinary setattr permission. */
		वापस dentry_has_perm(current_cred(), dentry, खाता__SETATTR);
	पूर्ण

	अगर (!selinux_initialized(&selinux_state))
		वापस 0;

	/* No one is allowed to हटाओ a SELinux security label.
	   You can change the label, but all data must be labeled. */
	वापस -EACCES;
पूर्ण

अटल पूर्णांक selinux_path_notअगरy(स्थिर काष्ठा path *path, u64 mask,
						अचिन्हित पूर्णांक obj_type)
अणु
	पूर्णांक ret;
	u32 perm;

	काष्ठा common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_PATH;
	ad.u.path = *path;

	/*
	 * Set permission needed based on the type of mark being set.
	 * Perक्रमms an additional check क्रम sb watches.
	 */
	चयन (obj_type) अणु
	हाल FSNOTIFY_OBJ_TYPE_VFSMOUNT:
		perm = खाता__WATCH_MOUNT;
		अवरोध;
	हाल FSNOTIFY_OBJ_TYPE_SB:
		perm = खाता__WATCH_SB;
		ret = superblock_has_perm(current_cred(), path->dentry->d_sb,
						खाताSYSTEM__WATCH, &ad);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल FSNOTIFY_OBJ_TYPE_INODE:
		perm = खाता__WATCH;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* blocking watches require the file:watch_with_perm permission */
	अगर (mask & (ALL_FSNOTIFY_PERM_EVENTS))
		perm |= खाता__WATCH_WITH_PERM;

	/* watches on पढ़ो-like events need the file:watch_पढ़ोs permission */
	अगर (mask & (FS_ACCESS | FS_ACCESS_PERM | FS_CLOSE_NOWRITE))
		perm |= खाता__WATCH_READS;

	वापस path_has_perm(current_cred(), path, perm);
पूर्ण

/*
 * Copy the inode security context value to the user.
 *
 * Permission check is handled by selinux_inode_getxattr hook.
 */
अटल पूर्णांक selinux_inode_माला_लोecurity(काष्ठा user_namespace *mnt_userns,
				     काष्ठा inode *inode, स्थिर अक्षर *name,
				     व्योम **buffer, bool alloc)
अणु
	u32 size;
	पूर्णांक error;
	अक्षर *context = शून्य;
	काष्ठा inode_security_काष्ठा *isec;

	/*
	 * If we're not initialized yet, then we can't validate contexts, so
	 * just let vfs_getxattr fall back to using the on-disk xattr.
	 */
	अगर (!selinux_initialized(&selinux_state) ||
	    म_भेद(name, XATTR_SELINUX_SUFFIX))
		वापस -EOPNOTSUPP;

	/*
	 * If the caller has CAP_MAC_ADMIN, then get the raw context
	 * value even अगर it is not defined by current policy; otherwise,
	 * use the in-core value under current policy.
	 * Use the non-auditing क्रमms of the permission checks since
	 * getxattr may be called by unprivileged processes commonly
	 * and lack of permission just means that we fall back to the
	 * in-core context value, not a denial.
	 */
	isec = inode_security(inode);
	अगर (has_cap_mac_admin(false))
		error = security_sid_to_context_क्रमce(&selinux_state,
						      isec->sid, &context,
						      &size);
	अन्यथा
		error = security_sid_to_context(&selinux_state, isec->sid,
						&context, &size);
	अगर (error)
		वापस error;
	error = size;
	अगर (alloc) अणु
		*buffer = context;
		जाओ out_noमुक्त;
	पूर्ण
	kमुक्त(context);
out_noमुक्त:
	वापस error;
पूर्ण

अटल पूर्णांक selinux_inode_setsecurity(काष्ठा inode *inode, स्थिर अक्षर *name,
				     स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा inode_security_काष्ठा *isec = inode_security_novalidate(inode);
	काष्ठा superblock_security_काष्ठा *sbsec;
	u32 newsid;
	पूर्णांक rc;

	अगर (म_भेद(name, XATTR_SELINUX_SUFFIX))
		वापस -EOPNOTSUPP;

	sbsec = selinux_superblock(inode->i_sb);
	अगर (!(sbsec->flags & SBLABEL_MNT))
		वापस -EOPNOTSUPP;

	अगर (!value || !size)
		वापस -EACCES;

	rc = security_context_to_sid(&selinux_state, value, size, &newsid,
				     GFP_KERNEL);
	अगर (rc)
		वापस rc;

	spin_lock(&isec->lock);
	isec->sclass = inode_mode_to_security_class(inode->i_mode);
	isec->sid = newsid;
	isec->initialized = LABEL_INITIALIZED;
	spin_unlock(&isec->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक selinux_inode_listsecurity(काष्ठा inode *inode, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	स्थिर पूर्णांक len = माप(XATTR_NAME_SELINUX);

	अगर (!selinux_initialized(&selinux_state))
		वापस 0;

	अगर (buffer && len <= buffer_size)
		स_नकल(buffer, XATTR_NAME_SELINUX, len);
	वापस len;
पूर्ण

अटल व्योम selinux_inode_माला_लोecid(काष्ठा inode *inode, u32 *secid)
अणु
	काष्ठा inode_security_काष्ठा *isec = inode_security_novalidate(inode);
	*secid = isec->sid;
पूर्ण

अटल पूर्णांक selinux_inode_copy_up(काष्ठा dentry *src, काष्ठा cred **new)
अणु
	u32 sid;
	काष्ठा task_security_काष्ठा *tsec;
	काष्ठा cred *new_creds = *new;

	अगर (new_creds == शून्य) अणु
		new_creds = prepare_creds();
		अगर (!new_creds)
			वापस -ENOMEM;
	पूर्ण

	tsec = selinux_cred(new_creds);
	/* Get label from overlay inode and set it in create_sid */
	selinux_inode_माला_लोecid(d_inode(src), &sid);
	tsec->create_sid = sid;
	*new = new_creds;
	वापस 0;
पूर्ण

अटल पूर्णांक selinux_inode_copy_up_xattr(स्थिर अक्षर *name)
अणु
	/* The copy_up hook above sets the initial context on an inode, but we
	 * करोn't then want to overग_लिखो it by blindly copying all the lower
	 * xattrs up.  Instead, we have to filter out SELinux-related xattrs.
	 */
	अगर (म_भेद(name, XATTR_NAME_SELINUX) == 0)
		वापस 1; /* Discard */
	/*
	 * Any other attribute apart from SELINUX is not claimed, supported
	 * by selinux.
	 */
	वापस -EOPNOTSUPP;
पूर्ण

/* kernfs node operations */

अटल पूर्णांक selinux_kernfs_init_security(काष्ठा kernfs_node *kn_dir,
					काष्ठा kernfs_node *kn)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(current_cred());
	u32 parent_sid, newsid, clen;
	पूर्णांक rc;
	अक्षर *context;

	rc = kernfs_xattr_get(kn_dir, XATTR_NAME_SELINUX, शून्य, 0);
	अगर (rc == -ENODATA)
		वापस 0;
	अन्यथा अगर (rc < 0)
		वापस rc;

	clen = (u32)rc;
	context = kदो_स्मृति(clen, GFP_KERNEL);
	अगर (!context)
		वापस -ENOMEM;

	rc = kernfs_xattr_get(kn_dir, XATTR_NAME_SELINUX, context, clen);
	अगर (rc < 0) अणु
		kमुक्त(context);
		वापस rc;
	पूर्ण

	rc = security_context_to_sid(&selinux_state, context, clen, &parent_sid,
				     GFP_KERNEL);
	kमुक्त(context);
	अगर (rc)
		वापस rc;

	अगर (tsec->create_sid) अणु
		newsid = tsec->create_sid;
	पूर्ण अन्यथा अणु
		u16 secclass = inode_mode_to_security_class(kn->mode);
		काष्ठा qstr q;

		q.name = kn->name;
		q.hash_len = hashlen_string(kn_dir, kn->name);

		rc = security_transition_sid(&selinux_state, tsec->sid,
					     parent_sid, secclass, &q,
					     &newsid);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = security_sid_to_context_क्रमce(&selinux_state, newsid,
					   &context, &clen);
	अगर (rc)
		वापस rc;

	rc = kernfs_xattr_set(kn, XATTR_NAME_SELINUX, context, clen,
			      XATTR_CREATE);
	kमुक्त(context);
	वापस rc;
पूर्ण


/* file security operations */

अटल पूर्णांक selinux_revalidate_file_permission(काष्ठा file *file, पूर्णांक mask)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा inode *inode = file_inode(file);

	/* file_mask_to_av won't add खाता__WRITE अगर MAY_APPEND is set */
	अगर ((file->f_flags & O_APPEND) && (mask & MAY_WRITE))
		mask |= MAY_APPEND;

	वापस file_has_perm(cred, file,
			     file_mask_to_av(inode->i_mode, mask));
पूर्ण

अटल पूर्णांक selinux_file_permission(काष्ठा file *file, पूर्णांक mask)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा file_security_काष्ठा *fsec = selinux_file(file);
	काष्ठा inode_security_काष्ठा *isec;
	u32 sid = current_sid();

	अगर (!mask)
		/* No permission to check.  Existence test. */
		वापस 0;

	isec = inode_security(inode);
	अगर (sid == fsec->sid && fsec->isid == isec->sid &&
	    fsec->pseqno == avc_policy_seqno(&selinux_state))
		/* No change since file_खोलो check. */
		वापस 0;

	वापस selinux_revalidate_file_permission(file, mask);
पूर्ण

अटल पूर्णांक selinux_file_alloc_security(काष्ठा file *file)
अणु
	काष्ठा file_security_काष्ठा *fsec = selinux_file(file);
	u32 sid = current_sid();

	fsec->sid = sid;
	fsec->fown_sid = sid;

	वापस 0;
पूर्ण

/*
 * Check whether a task has the ioctl permission and cmd
 * operation to an inode.
 */
अटल पूर्णांक ioctl_has_perm(स्थिर काष्ठा cred *cred, काष्ठा file *file,
		u32 requested, u16 cmd)
अणु
	काष्ठा common_audit_data ad;
	काष्ठा file_security_काष्ठा *fsec = selinux_file(file);
	काष्ठा inode *inode = file_inode(file);
	काष्ठा inode_security_काष्ठा *isec;
	काष्ठा lsm_ioctlop_audit ioctl;
	u32 ssid = cred_sid(cred);
	पूर्णांक rc;
	u8 driver = cmd >> 8;
	u8 xperm = cmd & 0xff;

	ad.type = LSM_AUDIT_DATA_IOCTL_OP;
	ad.u.op = &ioctl;
	ad.u.op->cmd = cmd;
	ad.u.op->path = file->f_path;

	अगर (ssid != fsec->sid) अणु
		rc = avc_has_perm(&selinux_state,
				  ssid, fsec->sid,
				SECCLASS_FD,
				FD__USE,
				&ad);
		अगर (rc)
			जाओ out;
	पूर्ण

	अगर (unlikely(IS_PRIVATE(inode)))
		वापस 0;

	isec = inode_security(inode);
	rc = avc_has_extended_perms(&selinux_state,
				    ssid, isec->sid, isec->sclass,
				    requested, driver, xperm, &ad);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_file_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक error = 0;

	चयन (cmd) अणु
	हाल FIONREAD:
	हाल FIBMAP:
	हाल FIGETBSZ:
	हाल FS_IOC_GETFLAGS:
	हाल FS_IOC_GETVERSION:
		error = file_has_perm(cred, file, खाता__GETATTR);
		अवरोध;

	हाल FS_IOC_SETFLAGS:
	हाल FS_IOC_SETVERSION:
		error = file_has_perm(cred, file, खाता__SETATTR);
		अवरोध;

	/* sys_ioctl() checks */
	हाल FIONBIO:
	हाल FIOASYNC:
		error = file_has_perm(cred, file, 0);
		अवरोध;

	हाल KDSKBENT:
	हाल KDSKBSENT:
		error = cred_has_capability(cred, CAP_SYS_TTY_CONFIG,
					    CAP_OPT_NONE, true);
		अवरोध;

	/* शेष हाल assumes that the command will go
	 * to the file's ioctl() function.
	 */
	शेष:
		error = ioctl_has_perm(cred, file, खाता__IOCTL, (u16) cmd);
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक शेष_noexec __ro_after_init;

अटल पूर्णांक file_map_prot_check(काष्ठा file *file, अचिन्हित दीर्घ prot, पूर्णांक shared)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	u32 sid = cred_sid(cred);
	पूर्णांक rc = 0;

	अगर (शेष_noexec &&
	    (prot & PROT_EXEC) && (!file || IS_PRIVATE(file_inode(file)) ||
				   (!shared && (prot & PROT_WRITE)))) अणु
		/*
		 * We are making executable an anonymous mapping or a
		 * निजी file mapping that will also be writable.
		 * This has an additional check.
		 */
		rc = avc_has_perm(&selinux_state,
				  sid, sid, SECCLASS_PROCESS,
				  PROCESS__EXECMEM, शून्य);
		अगर (rc)
			जाओ error;
	पूर्ण

	अगर (file) अणु
		/* पढ़ो access is always possible with a mapping */
		u32 av = खाता__READ;

		/* ग_लिखो access only matters अगर the mapping is shared */
		अगर (shared && (prot & PROT_WRITE))
			av |= खाता__WRITE;

		अगर (prot & PROT_EXEC)
			av |= खाता__EXECUTE;

		वापस file_has_perm(cred, file, av);
	पूर्ण

error:
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_mmap_addr(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक rc = 0;

	अगर (addr < CONFIG_LSM_MMAP_MIN_ADDR) अणु
		u32 sid = current_sid();
		rc = avc_has_perm(&selinux_state,
				  sid, sid, SECCLASS_MEMPROTECT,
				  MEMPROTECT__MMAP_ZERO, शून्य);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक selinux_mmap_file(काष्ठा file *file, अचिन्हित दीर्घ reqprot,
			     अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags)
अणु
	काष्ठा common_audit_data ad;
	पूर्णांक rc;

	अगर (file) अणु
		ad.type = LSM_AUDIT_DATA_खाता;
		ad.u.file = file;
		rc = inode_has_perm(current_cred(), file_inode(file),
				    खाता__MAP, &ad);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (checkreqprot_get(&selinux_state))
		prot = reqprot;

	वापस file_map_prot_check(file, prot,
				   (flags & MAP_TYPE) == MAP_SHARED);
पूर्ण

अटल पूर्णांक selinux_file_mprotect(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ reqprot,
				 अचिन्हित दीर्घ prot)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	u32 sid = cred_sid(cred);

	अगर (checkreqprot_get(&selinux_state))
		prot = reqprot;

	अगर (शेष_noexec &&
	    (prot & PROT_EXEC) && !(vma->vm_flags & VM_EXEC)) अणु
		पूर्णांक rc = 0;
		अगर (vma->vm_start >= vma->vm_mm->start_brk &&
		    vma->vm_end <= vma->vm_mm->brk) अणु
			rc = avc_has_perm(&selinux_state,
					  sid, sid, SECCLASS_PROCESS,
					  PROCESS__EXECHEAP, शून्य);
		पूर्ण अन्यथा अगर (!vma->vm_file &&
			   ((vma->vm_start <= vma->vm_mm->start_stack &&
			     vma->vm_end >= vma->vm_mm->start_stack) ||
			    vma_is_stack_क्रम_current(vma))) अणु
			rc = avc_has_perm(&selinux_state,
					  sid, sid, SECCLASS_PROCESS,
					  PROCESS__EXECSTACK, शून्य);
		पूर्ण अन्यथा अगर (vma->vm_file && vma->anon_vma) अणु
			/*
			 * We are making executable a file mapping that has
			 * had some COW करोne. Since pages might have been
			 * written, check ability to execute the possibly
			 * modअगरied content.  This typically should only
			 * occur क्रम text relocations.
			 */
			rc = file_has_perm(cred, vma->vm_file, खाता__EXECMOD);
		पूर्ण
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस file_map_prot_check(vma->vm_file, prot, vma->vm_flags&VM_SHARED);
पूर्ण

अटल पूर्णांक selinux_file_lock(काष्ठा file *file, अचिन्हित पूर्णांक cmd)
अणु
	स्थिर काष्ठा cred *cred = current_cred();

	वापस file_has_perm(cred, file, खाता__LOCK);
पूर्ण

अटल पूर्णांक selinux_file_fcntl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल F_SETFL:
		अगर ((file->f_flags & O_APPEND) && !(arg & O_APPEND)) अणु
			err = file_has_perm(cred, file, खाता__WRITE);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल F_SETOWN:
	हाल F_SETSIG:
	हाल F_GETFL:
	हाल F_GETOWN:
	हाल F_GETSIG:
	हाल F_GETOWNER_UIDS:
		/* Just check FD__USE permission */
		err = file_has_perm(cred, file, 0);
		अवरोध;
	हाल F_GETLK:
	हाल F_SETLK:
	हाल F_SETLKW:
	हाल F_OFD_GETLK:
	हाल F_OFD_SETLK:
	हाल F_OFD_SETLKW:
#अगर BITS_PER_LONG == 32
	हाल F_GETLK64:
	हाल F_SETLK64:
	हाल F_SETLKW64:
#पूर्ण_अगर
		err = file_has_perm(cred, file, खाता__LOCK);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम selinux_file_set_fowner(काष्ठा file *file)
अणु
	काष्ठा file_security_काष्ठा *fsec;

	fsec = selinux_file(file);
	fsec->fown_sid = current_sid();
पूर्ण

अटल पूर्णांक selinux_file_send_sigiotask(काष्ठा task_काष्ठा *tsk,
				       काष्ठा fown_काष्ठा *fown, पूर्णांक signum)
अणु
	काष्ठा file *file;
	u32 sid = task_sid_obj(tsk);
	u32 perm;
	काष्ठा file_security_काष्ठा *fsec;

	/* काष्ठा fown_काष्ठा is never outside the context of a काष्ठा file */
	file = container_of(fown, काष्ठा file, f_owner);

	fsec = selinux_file(file);

	अगर (!signum)
		perm = संकेत_to_av(SIGIO); /* as per send_sigio_to_task */
	अन्यथा
		perm = संकेत_to_av(signum);

	वापस avc_has_perm(&selinux_state,
			    fsec->fown_sid, sid,
			    SECCLASS_PROCESS, perm, शून्य);
पूर्ण

अटल पूर्णांक selinux_file_receive(काष्ठा file *file)
अणु
	स्थिर काष्ठा cred *cred = current_cred();

	वापस file_has_perm(cred, file, file_to_av(file));
पूर्ण

अटल पूर्णांक selinux_file_खोलो(काष्ठा file *file)
अणु
	काष्ठा file_security_काष्ठा *fsec;
	काष्ठा inode_security_काष्ठा *isec;

	fsec = selinux_file(file);
	isec = inode_security(file_inode(file));
	/*
	 * Save inode label and policy sequence number
	 * at खोलो-समय so that selinux_file_permission
	 * can determine whether revalidation is necessary.
	 * Task label is alपढ़ोy saved in the file security
	 * काष्ठा as its SID.
	 */
	fsec->isid = isec->sid;
	fsec->pseqno = avc_policy_seqno(&selinux_state);
	/*
	 * Since the inode label or policy seqno may have changed
	 * between the selinux_inode_permission check and the saving
	 * of state above, recheck that access is still permitted.
	 * Otherwise, access might never be revalidated against the
	 * new inode label or new policy.
	 * This check is not redundant - करो not हटाओ.
	 */
	वापस file_path_has_perm(file->f_cred, file, खोलो_file_to_av(file));
पूर्ण

/* task security operations */

अटल पूर्णांक selinux_task_alloc(काष्ठा task_काष्ठा *task,
			      अचिन्हित दीर्घ clone_flags)
अणु
	u32 sid = current_sid();

	वापस avc_has_perm(&selinux_state,
			    sid, sid, SECCLASS_PROCESS, PROCESS__FORK, शून्य);
पूर्ण

/*
 * prepare a new set of credentials क्रम modअगरication
 */
अटल पूर्णांक selinux_cred_prepare(काष्ठा cred *new, स्थिर काष्ठा cred *old,
				gfp_t gfp)
अणु
	स्थिर काष्ठा task_security_काष्ठा *old_tsec = selinux_cred(old);
	काष्ठा task_security_काष्ठा *tsec = selinux_cred(new);

	*tsec = *old_tsec;
	वापस 0;
पूर्ण

/*
 * transfer the SELinux data to a blank set of creds
 */
अटल व्योम selinux_cred_transfer(काष्ठा cred *new, स्थिर काष्ठा cred *old)
अणु
	स्थिर काष्ठा task_security_काष्ठा *old_tsec = selinux_cred(old);
	काष्ठा task_security_काष्ठा *tsec = selinux_cred(new);

	*tsec = *old_tsec;
पूर्ण

अटल व्योम selinux_cred_माला_लोecid(स्थिर काष्ठा cred *c, u32 *secid)
अणु
	*secid = cred_sid(c);
पूर्ण

/*
 * set the security data क्रम a kernel service
 * - all the creation contexts are set to unlabelled
 */
अटल पूर्णांक selinux_kernel_act_as(काष्ठा cred *new, u32 secid)
अणु
	काष्ठा task_security_काष्ठा *tsec = selinux_cred(new);
	u32 sid = current_sid();
	पूर्णांक ret;

	ret = avc_has_perm(&selinux_state,
			   sid, secid,
			   SECCLASS_KERNEL_SERVICE,
			   KERNEL_SERVICE__USE_AS_OVERRIDE,
			   शून्य);
	अगर (ret == 0) अणु
		tsec->sid = secid;
		tsec->create_sid = 0;
		tsec->keycreate_sid = 0;
		tsec->sockcreate_sid = 0;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * set the file creation context in a security record to the same as the
 * objective context of the specअगरied inode
 */
अटल पूर्णांक selinux_kernel_create_files_as(काष्ठा cred *new, काष्ठा inode *inode)
अणु
	काष्ठा inode_security_काष्ठा *isec = inode_security(inode);
	काष्ठा task_security_काष्ठा *tsec = selinux_cred(new);
	u32 sid = current_sid();
	पूर्णांक ret;

	ret = avc_has_perm(&selinux_state,
			   sid, isec->sid,
			   SECCLASS_KERNEL_SERVICE,
			   KERNEL_SERVICE__CREATE_खाताS_AS,
			   शून्य);

	अगर (ret == 0)
		tsec->create_sid = isec->sid;
	वापस ret;
पूर्ण

अटल पूर्णांक selinux_kernel_module_request(अक्षर *kmod_name)
अणु
	काष्ठा common_audit_data ad;

	ad.type = LSM_AUDIT_DATA_KMOD;
	ad.u.kmod_name = kmod_name;

	वापस avc_has_perm(&selinux_state,
			    current_sid(), SECINITSID_KERNEL, SECCLASS_SYSTEM,
			    SYSTEM__MODULE_REQUEST, &ad);
पूर्ण

अटल पूर्णांक selinux_kernel_module_from_file(काष्ठा file *file)
अणु
	काष्ठा common_audit_data ad;
	काष्ठा inode_security_काष्ठा *isec;
	काष्ठा file_security_काष्ठा *fsec;
	u32 sid = current_sid();
	पूर्णांक rc;

	/* init_module */
	अगर (file == शून्य)
		वापस avc_has_perm(&selinux_state,
				    sid, sid, SECCLASS_SYSTEM,
					SYSTEM__MODULE_LOAD, शून्य);

	/* finit_module */

	ad.type = LSM_AUDIT_DATA_खाता;
	ad.u.file = file;

	fsec = selinux_file(file);
	अगर (sid != fsec->sid) अणु
		rc = avc_has_perm(&selinux_state,
				  sid, fsec->sid, SECCLASS_FD, FD__USE, &ad);
		अगर (rc)
			वापस rc;
	पूर्ण

	isec = inode_security(file_inode(file));
	वापस avc_has_perm(&selinux_state,
			    sid, isec->sid, SECCLASS_SYSTEM,
				SYSTEM__MODULE_LOAD, &ad);
पूर्ण

अटल पूर्णांक selinux_kernel_पढ़ो_file(काष्ठा file *file,
				    क्रमागत kernel_पढ़ो_file_id id,
				    bool contents)
अणु
	पूर्णांक rc = 0;

	चयन (id) अणु
	हाल READING_MODULE:
		rc = selinux_kernel_module_from_file(contents ? file : शून्य);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक selinux_kernel_load_data(क्रमागत kernel_load_data_id id, bool contents)
अणु
	पूर्णांक rc = 0;

	चयन (id) अणु
	हाल LOADING_MODULE:
		rc = selinux_kernel_module_from_file(शून्य);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक selinux_task_setpgid(काष्ठा task_काष्ठा *p, pid_t pgid)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_obj(p), SECCLASS_PROCESS,
			    PROCESS__SETPGID, शून्य);
पूर्ण

अटल पूर्णांक selinux_task_getpgid(काष्ठा task_काष्ठा *p)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_obj(p), SECCLASS_PROCESS,
			    PROCESS__GETPGID, शून्य);
पूर्ण

अटल पूर्णांक selinux_task_माला_लोid(काष्ठा task_काष्ठा *p)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_obj(p), SECCLASS_PROCESS,
			    PROCESS__GETSESSION, शून्य);
पूर्ण

अटल व्योम selinux_task_माला_लोecid_subj(काष्ठा task_काष्ठा *p, u32 *secid)
अणु
	*secid = task_sid_subj(p);
पूर्ण

अटल व्योम selinux_task_माला_लोecid_obj(काष्ठा task_काष्ठा *p, u32 *secid)
अणु
	*secid = task_sid_obj(p);
पूर्ण

अटल पूर्णांक selinux_task_setnice(काष्ठा task_काष्ठा *p, पूर्णांक nice)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_obj(p), SECCLASS_PROCESS,
			    PROCESS__SETSCHED, शून्य);
पूर्ण

अटल पूर्णांक selinux_task_setioprio(काष्ठा task_काष्ठा *p, पूर्णांक ioprio)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_obj(p), SECCLASS_PROCESS,
			    PROCESS__SETSCHED, शून्य);
पूर्ण

अटल पूर्णांक selinux_task_getioprio(काष्ठा task_काष्ठा *p)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_obj(p), SECCLASS_PROCESS,
			    PROCESS__GETSCHED, शून्य);
पूर्ण

अटल पूर्णांक selinux_task_prlimit(स्थिर काष्ठा cred *cred, स्थिर काष्ठा cred *tcred,
				अचिन्हित पूर्णांक flags)
अणु
	u32 av = 0;

	अगर (!flags)
		वापस 0;
	अगर (flags & LSM_PRLIMIT_WRITE)
		av |= PROCESS__SETRLIMIT;
	अगर (flags & LSM_PRLIMIT_READ)
		av |= PROCESS__GETRLIMIT;
	वापस avc_has_perm(&selinux_state,
			    cred_sid(cred), cred_sid(tcred),
			    SECCLASS_PROCESS, av, शून्य);
पूर्ण

अटल पूर्णांक selinux_task_setrlimit(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक resource,
		काष्ठा rlimit *new_rlim)
अणु
	काष्ठा rlimit *old_rlim = p->संकेत->rlim + resource;

	/* Control the ability to change the hard limit (whether
	   lowering or raising it), so that the hard limit can
	   later be used as a safe reset poपूर्णांक क्रम the soft limit
	   upon context transitions.  See selinux_bprm_committing_creds. */
	अगर (old_rlim->rlim_max != new_rlim->rlim_max)
		वापस avc_has_perm(&selinux_state,
				    current_sid(), task_sid_obj(p),
				    SECCLASS_PROCESS, PROCESS__SETRLIMIT, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक selinux_task_setscheduler(काष्ठा task_काष्ठा *p)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_obj(p), SECCLASS_PROCESS,
			    PROCESS__SETSCHED, शून्य);
पूर्ण

अटल पूर्णांक selinux_task_माला_लोcheduler(काष्ठा task_काष्ठा *p)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_obj(p), SECCLASS_PROCESS,
			    PROCESS__GETSCHED, शून्य);
पूर्ण

अटल पूर्णांक selinux_task_movememory(काष्ठा task_काष्ठा *p)
अणु
	वापस avc_has_perm(&selinux_state,
			    current_sid(), task_sid_obj(p), SECCLASS_PROCESS,
			    PROCESS__SETSCHED, शून्य);
पूर्ण

अटल पूर्णांक selinux_task_समाप्त(काष्ठा task_काष्ठा *p, काष्ठा kernel_siginfo *info,
				पूर्णांक sig, स्थिर काष्ठा cred *cred)
अणु
	u32 secid;
	u32 perm;

	अगर (!sig)
		perm = PROCESS__SIGशून्य; /* null संकेत; existence test */
	अन्यथा
		perm = संकेत_to_av(sig);
	अगर (!cred)
		secid = current_sid();
	अन्यथा
		secid = cred_sid(cred);
	वापस avc_has_perm(&selinux_state,
			    secid, task_sid_obj(p), SECCLASS_PROCESS, perm, शून्य);
पूर्ण

अटल व्योम selinux_task_to_inode(काष्ठा task_काष्ठा *p,
				  काष्ठा inode *inode)
अणु
	काष्ठा inode_security_काष्ठा *isec = selinux_inode(inode);
	u32 sid = task_sid_obj(p);

	spin_lock(&isec->lock);
	isec->sclass = inode_mode_to_security_class(inode->i_mode);
	isec->sid = sid;
	isec->initialized = LABEL_INITIALIZED;
	spin_unlock(&isec->lock);
पूर्ण

/* Returns error only अगर unable to parse addresses */
अटल पूर्णांक selinux_parse_skb_ipv4(काष्ठा sk_buff *skb,
			काष्ठा common_audit_data *ad, u8 *proto)
अणु
	पूर्णांक offset, ihlen, ret = -EINVAL;
	काष्ठा iphdr _iph, *ih;

	offset = skb_network_offset(skb);
	ih = skb_header_poपूर्णांकer(skb, offset, माप(_iph), &_iph);
	अगर (ih == शून्य)
		जाओ out;

	ihlen = ih->ihl * 4;
	अगर (ihlen < माप(_iph))
		जाओ out;

	ad->u.net->v4info.saddr = ih->saddr;
	ad->u.net->v4info.daddr = ih->daddr;
	ret = 0;

	अगर (proto)
		*proto = ih->protocol;

	चयन (ih->protocol) अणु
	हाल IPPROTO_TCP: अणु
		काष्ठा tcphdr _tcph, *th;

		अगर (ntohs(ih->frag_off) & IP_OFFSET)
			अवरोध;

		offset += ihlen;
		th = skb_header_poपूर्णांकer(skb, offset, माप(_tcph), &_tcph);
		अगर (th == शून्य)
			अवरोध;

		ad->u.net->sport = th->source;
		ad->u.net->dport = th->dest;
		अवरोध;
	पूर्ण

	हाल IPPROTO_UDP: अणु
		काष्ठा udphdr _udph, *uh;

		अगर (ntohs(ih->frag_off) & IP_OFFSET)
			अवरोध;

		offset += ihlen;
		uh = skb_header_poपूर्णांकer(skb, offset, माप(_udph), &_udph);
		अगर (uh == शून्य)
			अवरोध;

		ad->u.net->sport = uh->source;
		ad->u.net->dport = uh->dest;
		अवरोध;
	पूर्ण

	हाल IPPROTO_DCCP: अणु
		काष्ठा dccp_hdr _dccph, *dh;

		अगर (ntohs(ih->frag_off) & IP_OFFSET)
			अवरोध;

		offset += ihlen;
		dh = skb_header_poपूर्णांकer(skb, offset, माप(_dccph), &_dccph);
		अगर (dh == शून्य)
			अवरोध;

		ad->u.net->sport = dh->dccph_sport;
		ad->u.net->dport = dh->dccph_dport;
		अवरोध;
	पूर्ण

#अगर IS_ENABLED(CONFIG_IP_SCTP)
	हाल IPPROTO_SCTP: अणु
		काष्ठा sctphdr _sctph, *sh;

		अगर (ntohs(ih->frag_off) & IP_OFFSET)
			अवरोध;

		offset += ihlen;
		sh = skb_header_poपूर्णांकer(skb, offset, माप(_sctph), &_sctph);
		अगर (sh == शून्य)
			अवरोध;

		ad->u.net->sport = sh->source;
		ad->u.net->dport = sh->dest;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण
out:
	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)

/* Returns error only अगर unable to parse addresses */
अटल पूर्णांक selinux_parse_skb_ipv6(काष्ठा sk_buff *skb,
			काष्ठा common_audit_data *ad, u8 *proto)
अणु
	u8 nexthdr;
	पूर्णांक ret = -EINVAL, offset;
	काष्ठा ipv6hdr _ipv6h, *ip6;
	__be16 frag_off;

	offset = skb_network_offset(skb);
	ip6 = skb_header_poपूर्णांकer(skb, offset, माप(_ipv6h), &_ipv6h);
	अगर (ip6 == शून्य)
		जाओ out;

	ad->u.net->v6info.saddr = ip6->saddr;
	ad->u.net->v6info.daddr = ip6->daddr;
	ret = 0;

	nexthdr = ip6->nexthdr;
	offset += माप(_ipv6h);
	offset = ipv6_skip_exthdr(skb, offset, &nexthdr, &frag_off);
	अगर (offset < 0)
		जाओ out;

	अगर (proto)
		*proto = nexthdr;

	चयन (nexthdr) अणु
	हाल IPPROTO_TCP: अणु
		काष्ठा tcphdr _tcph, *th;

		th = skb_header_poपूर्णांकer(skb, offset, माप(_tcph), &_tcph);
		अगर (th == शून्य)
			अवरोध;

		ad->u.net->sport = th->source;
		ad->u.net->dport = th->dest;
		अवरोध;
	पूर्ण

	हाल IPPROTO_UDP: अणु
		काष्ठा udphdr _udph, *uh;

		uh = skb_header_poपूर्णांकer(skb, offset, माप(_udph), &_udph);
		अगर (uh == शून्य)
			अवरोध;

		ad->u.net->sport = uh->source;
		ad->u.net->dport = uh->dest;
		अवरोध;
	पूर्ण

	हाल IPPROTO_DCCP: अणु
		काष्ठा dccp_hdr _dccph, *dh;

		dh = skb_header_poपूर्णांकer(skb, offset, माप(_dccph), &_dccph);
		अगर (dh == शून्य)
			अवरोध;

		ad->u.net->sport = dh->dccph_sport;
		ad->u.net->dport = dh->dccph_dport;
		अवरोध;
	पूर्ण

#अगर IS_ENABLED(CONFIG_IP_SCTP)
	हाल IPPROTO_SCTP: अणु
		काष्ठा sctphdr _sctph, *sh;

		sh = skb_header_poपूर्णांकer(skb, offset, माप(_sctph), &_sctph);
		अगर (sh == शून्य)
			अवरोध;

		ad->u.net->sport = sh->source;
		ad->u.net->dport = sh->dest;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	/* includes fragments */
	शेष:
		अवरोध;
	पूर्ण
out:
	वापस ret;
पूर्ण

#पूर्ण_अगर /* IPV6 */

अटल पूर्णांक selinux_parse_skb(काष्ठा sk_buff *skb, काष्ठा common_audit_data *ad,
			     अक्षर **_addrp, पूर्णांक src, u8 *proto)
अणु
	अक्षर *addrp;
	पूर्णांक ret;

	चयन (ad->u.net->family) अणु
	हाल PF_INET:
		ret = selinux_parse_skb_ipv4(skb, ad, proto);
		अगर (ret)
			जाओ parse_error;
		addrp = (अक्षर *)(src ? &ad->u.net->v4info.saddr :
				       &ad->u.net->v4info.daddr);
		जाओ okay;

#अगर IS_ENABLED(CONFIG_IPV6)
	हाल PF_INET6:
		ret = selinux_parse_skb_ipv6(skb, ad, proto);
		अगर (ret)
			जाओ parse_error;
		addrp = (अक्षर *)(src ? &ad->u.net->v6info.saddr :
				       &ad->u.net->v6info.daddr);
		जाओ okay;
#पूर्ण_अगर	/* IPV6 */
	शेष:
		addrp = शून्य;
		जाओ okay;
	पूर्ण

parse_error:
	pr_warn(
	       "SELinux: failure in selinux_parse_skb(),"
	       " unable to parse packet\n");
	वापस ret;

okay:
	अगर (_addrp)
		*_addrp = addrp;
	वापस 0;
पूर्ण

/**
 * selinux_skb_peerlbl_sid - Determine the peer label of a packet
 * @skb: the packet
 * @family: protocol family
 * @sid: the packet's peer label SID
 *
 * Description:
 * Check the various dअगरferent क्रमms of network peer labeling and determine
 * the peer label/SID क्रम the packet; most of the magic actually occurs in
 * the security server function security_net_peersid_cmp().  The function
 * वापसs zero अगर the value in @sid is valid (although it may be SECSID_शून्य)
 * or -EACCES अगर @sid is invalid due to inconsistencies with the dअगरferent
 * peer labels.
 *
 */
अटल पूर्णांक selinux_skb_peerlbl_sid(काष्ठा sk_buff *skb, u16 family, u32 *sid)
अणु
	पूर्णांक err;
	u32 xfrm_sid;
	u32 nlbl_sid;
	u32 nlbl_type;

	err = selinux_xfrm_skb_sid(skb, &xfrm_sid);
	अगर (unlikely(err))
		वापस -EACCES;
	err = selinux_netlbl_skbuff_माला_लोid(skb, family, &nlbl_type, &nlbl_sid);
	अगर (unlikely(err))
		वापस -EACCES;

	err = security_net_peersid_resolve(&selinux_state, nlbl_sid,
					   nlbl_type, xfrm_sid, sid);
	अगर (unlikely(err)) अणु
		pr_warn(
		       "SELinux: failure in selinux_skb_peerlbl_sid(),"
		       " unable to determine packet's peer label\n");
		वापस -EACCES;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * selinux_conn_sid - Determine the child socket label क्रम a connection
 * @sk_sid: the parent socket's SID
 * @skb_sid: the packet's SID
 * @conn_sid: the resulting connection SID
 *
 * If @skb_sid is valid then the user:role:type inक्रमmation from @sk_sid is
 * combined with the MLS inक्रमmation from @skb_sid in order to create
 * @conn_sid.  If @skb_sid is not valid then @conn_sid is simply a copy
 * of @sk_sid.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक selinux_conn_sid(u32 sk_sid, u32 skb_sid, u32 *conn_sid)
अणु
	पूर्णांक err = 0;

	अगर (skb_sid != SECSID_शून्य)
		err = security_sid_mls_copy(&selinux_state, sk_sid, skb_sid,
					    conn_sid);
	अन्यथा
		*conn_sid = sk_sid;

	वापस err;
पूर्ण

/* socket security operations */

अटल पूर्णांक socket_sockcreate_sid(स्थिर काष्ठा task_security_काष्ठा *tsec,
				 u16 secclass, u32 *socksid)
अणु
	अगर (tsec->sockcreate_sid > SECSID_शून्य) अणु
		*socksid = tsec->sockcreate_sid;
		वापस 0;
	पूर्ण

	वापस security_transition_sid(&selinux_state, tsec->sid, tsec->sid,
				       secclass, शून्य, socksid);
पूर्ण

अटल पूर्णांक sock_has_perm(काष्ठा sock *sk, u32 perms)
अणु
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	काष्ठा common_audit_data ad;
	काष्ठा lsm_network_audit net = अणु0,पूर्ण;

	अगर (sksec->sid == SECINITSID_KERNEL)
		वापस 0;

	ad.type = LSM_AUDIT_DATA_NET;
	ad.u.net = &net;
	ad.u.net->sk = sk;

	वापस avc_has_perm(&selinux_state,
			    current_sid(), sksec->sid, sksec->sclass, perms,
			    &ad);
पूर्ण

अटल पूर्णांक selinux_socket_create(पूर्णांक family, पूर्णांक type,
				 पूर्णांक protocol, पूर्णांक kern)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(current_cred());
	u32 newsid;
	u16 secclass;
	पूर्णांक rc;

	अगर (kern)
		वापस 0;

	secclass = socket_type_to_security_class(family, type, protocol);
	rc = socket_sockcreate_sid(tsec, secclass, &newsid);
	अगर (rc)
		वापस rc;

	वापस avc_has_perm(&selinux_state,
			    tsec->sid, newsid, secclass, SOCKET__CREATE, शून्य);
पूर्ण

अटल पूर्णांक selinux_socket_post_create(काष्ठा socket *sock, पूर्णांक family,
				      पूर्णांक type, पूर्णांक protocol, पूर्णांक kern)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(current_cred());
	काष्ठा inode_security_काष्ठा *isec = inode_security_novalidate(SOCK_INODE(sock));
	काष्ठा sk_security_काष्ठा *sksec;
	u16 sclass = socket_type_to_security_class(family, type, protocol);
	u32 sid = SECINITSID_KERNEL;
	पूर्णांक err = 0;

	अगर (!kern) अणु
		err = socket_sockcreate_sid(tsec, sclass, &sid);
		अगर (err)
			वापस err;
	पूर्ण

	isec->sclass = sclass;
	isec->sid = sid;
	isec->initialized = LABEL_INITIALIZED;

	अगर (sock->sk) अणु
		sksec = sock->sk->sk_security;
		sksec->sclass = sclass;
		sksec->sid = sid;
		/* Allows detection of the first association on this socket */
		अगर (sksec->sclass == SECCLASS_SCTP_SOCKET)
			sksec->sctp_assoc_state = SCTP_ASSOC_UNSET;

		err = selinux_netlbl_socket_post_create(sock->sk, family);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक selinux_socket_socketpair(काष्ठा socket *socka,
				     काष्ठा socket *sockb)
अणु
	काष्ठा sk_security_काष्ठा *sksec_a = socka->sk->sk_security;
	काष्ठा sk_security_काष्ठा *sksec_b = sockb->sk->sk_security;

	sksec_a->peer_sid = sksec_b->sid;
	sksec_b->peer_sid = sksec_a->sid;

	वापस 0;
पूर्ण

/* Range of port numbers used to स्वतःmatically bind.
   Need to determine whether we should perक्रमm a name_bind
   permission check between the socket and the port number. */

अटल पूर्णांक selinux_socket_bind(काष्ठा socket *sock, काष्ठा sockaddr *address, पूर्णांक addrlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	u16 family;
	पूर्णांक err;

	err = sock_has_perm(sk, SOCKET__BIND);
	अगर (err)
		जाओ out;

	/* If PF_INET or PF_INET6, check name_bind permission क्रम the port. */
	family = sk->sk_family;
	अगर (family == PF_INET || family == PF_INET6) अणु
		अक्षर *addrp;
		काष्ठा common_audit_data ad;
		काष्ठा lsm_network_audit net = अणु0,पूर्ण;
		काष्ठा sockaddr_in *addr4 = शून्य;
		काष्ठा sockaddr_in6 *addr6 = शून्य;
		u16 family_sa;
		अचिन्हित लघु snum;
		u32 sid, node_perm;

		/*
		 * sctp_bindx(3) calls via selinux_sctp_bind_connect()
		 * that validates multiple binding addresses. Because of this
		 * need to check address->sa_family as it is possible to have
		 * sk->sk_family = PF_INET6 with addr->sa_family = AF_INET.
		 */
		अगर (addrlen < दुरत्वend(काष्ठा sockaddr, sa_family))
			वापस -EINVAL;
		family_sa = address->sa_family;
		चयन (family_sa) अणु
		हाल AF_UNSPEC:
		हाल AF_INET:
			अगर (addrlen < माप(काष्ठा sockaddr_in))
				वापस -EINVAL;
			addr4 = (काष्ठा sockaddr_in *)address;
			अगर (family_sa == AF_UNSPEC) अणु
				/* see __inet_bind(), we only want to allow
				 * AF_UNSPEC अगर the address is INADDR_ANY
				 */
				अगर (addr4->sin_addr.s_addr != htonl(INADDR_ANY))
					जाओ err_af;
				family_sa = AF_INET;
			पूर्ण
			snum = ntohs(addr4->sin_port);
			addrp = (अक्षर *)&addr4->sin_addr.s_addr;
			अवरोध;
		हाल AF_INET6:
			अगर (addrlen < SIN6_LEN_RFC2133)
				वापस -EINVAL;
			addr6 = (काष्ठा sockaddr_in6 *)address;
			snum = ntohs(addr6->sin6_port);
			addrp = (अक्षर *)&addr6->sin6_addr.s6_addr;
			अवरोध;
		शेष:
			जाओ err_af;
		पूर्ण

		ad.type = LSM_AUDIT_DATA_NET;
		ad.u.net = &net;
		ad.u.net->sport = htons(snum);
		ad.u.net->family = family_sa;

		अगर (snum) अणु
			पूर्णांक low, high;

			inet_get_local_port_range(sock_net(sk), &low, &high);

			अगर (inet_port_requires_bind_service(sock_net(sk), snum) ||
			    snum < low || snum > high) अणु
				err = sel_netport_sid(sk->sk_protocol,
						      snum, &sid);
				अगर (err)
					जाओ out;
				err = avc_has_perm(&selinux_state,
						   sksec->sid, sid,
						   sksec->sclass,
						   SOCKET__NAME_BIND, &ad);
				अगर (err)
					जाओ out;
			पूर्ण
		पूर्ण

		चयन (sksec->sclass) अणु
		हाल SECCLASS_TCP_SOCKET:
			node_perm = TCP_SOCKET__NODE_BIND;
			अवरोध;

		हाल SECCLASS_UDP_SOCKET:
			node_perm = UDP_SOCKET__NODE_BIND;
			अवरोध;

		हाल SECCLASS_DCCP_SOCKET:
			node_perm = DCCP_SOCKET__NODE_BIND;
			अवरोध;

		हाल SECCLASS_SCTP_SOCKET:
			node_perm = SCTP_SOCKET__NODE_BIND;
			अवरोध;

		शेष:
			node_perm = RAWIP_SOCKET__NODE_BIND;
			अवरोध;
		पूर्ण

		err = sel_netnode_sid(addrp, family_sa, &sid);
		अगर (err)
			जाओ out;

		अगर (family_sa == AF_INET)
			ad.u.net->v4info.saddr = addr4->sin_addr.s_addr;
		अन्यथा
			ad.u.net->v6info.saddr = addr6->sin6_addr;

		err = avc_has_perm(&selinux_state,
				   sksec->sid, sid,
				   sksec->sclass, node_perm, &ad);
		अगर (err)
			जाओ out;
	पूर्ण
out:
	वापस err;
err_af:
	/* Note that SCTP services expect -EINVAL, others -EAFNOSUPPORT. */
	अगर (sksec->sclass == SECCLASS_SCTP_SOCKET)
		वापस -EINVAL;
	वापस -EAFNOSUPPORT;
पूर्ण

/* This supports connect(2) and SCTP connect services such as sctp_connectx(3)
 * and sctp_sendmsg(3) as described in Documentation/security/SCTP.rst
 */
अटल पूर्णांक selinux_socket_connect_helper(काष्ठा socket *sock,
					 काष्ठा sockaddr *address, पूर्णांक addrlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	पूर्णांक err;

	err = sock_has_perm(sk, SOCKET__CONNECT);
	अगर (err)
		वापस err;
	अगर (addrlen < दुरत्वend(काष्ठा sockaddr, sa_family))
		वापस -EINVAL;

	/* connect(AF_UNSPEC) has special handling, as it is a करोcumented
	 * way to disconnect the socket
	 */
	अगर (address->sa_family == AF_UNSPEC)
		वापस 0;

	/*
	 * If a TCP, DCCP or SCTP socket, check name_connect permission
	 * क्रम the port.
	 */
	अगर (sksec->sclass == SECCLASS_TCP_SOCKET ||
	    sksec->sclass == SECCLASS_DCCP_SOCKET ||
	    sksec->sclass == SECCLASS_SCTP_SOCKET) अणु
		काष्ठा common_audit_data ad;
		काष्ठा lsm_network_audit net = अणु0,पूर्ण;
		काष्ठा sockaddr_in *addr4 = शून्य;
		काष्ठा sockaddr_in6 *addr6 = शून्य;
		अचिन्हित लघु snum;
		u32 sid, perm;

		/* sctp_connectx(3) calls via selinux_sctp_bind_connect()
		 * that validates multiple connect addresses. Because of this
		 * need to check address->sa_family as it is possible to have
		 * sk->sk_family = PF_INET6 with addr->sa_family = AF_INET.
		 */
		चयन (address->sa_family) अणु
		हाल AF_INET:
			addr4 = (काष्ठा sockaddr_in *)address;
			अगर (addrlen < माप(काष्ठा sockaddr_in))
				वापस -EINVAL;
			snum = ntohs(addr4->sin_port);
			अवरोध;
		हाल AF_INET6:
			addr6 = (काष्ठा sockaddr_in6 *)address;
			अगर (addrlen < SIN6_LEN_RFC2133)
				वापस -EINVAL;
			snum = ntohs(addr6->sin6_port);
			अवरोध;
		शेष:
			/* Note that SCTP services expect -EINVAL, whereas
			 * others expect -EAFNOSUPPORT.
			 */
			अगर (sksec->sclass == SECCLASS_SCTP_SOCKET)
				वापस -EINVAL;
			अन्यथा
				वापस -EAFNOSUPPORT;
		पूर्ण

		err = sel_netport_sid(sk->sk_protocol, snum, &sid);
		अगर (err)
			वापस err;

		चयन (sksec->sclass) अणु
		हाल SECCLASS_TCP_SOCKET:
			perm = TCP_SOCKET__NAME_CONNECT;
			अवरोध;
		हाल SECCLASS_DCCP_SOCKET:
			perm = DCCP_SOCKET__NAME_CONNECT;
			अवरोध;
		हाल SECCLASS_SCTP_SOCKET:
			perm = SCTP_SOCKET__NAME_CONNECT;
			अवरोध;
		पूर्ण

		ad.type = LSM_AUDIT_DATA_NET;
		ad.u.net = &net;
		ad.u.net->dport = htons(snum);
		ad.u.net->family = address->sa_family;
		err = avc_has_perm(&selinux_state,
				   sksec->sid, sid, sksec->sclass, perm, &ad);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Supports connect(2), see comments in selinux_socket_connect_helper() */
अटल पूर्णांक selinux_socket_connect(काष्ठा socket *sock,
				  काष्ठा sockaddr *address, पूर्णांक addrlen)
अणु
	पूर्णांक err;
	काष्ठा sock *sk = sock->sk;

	err = selinux_socket_connect_helper(sock, address, addrlen);
	अगर (err)
		वापस err;

	वापस selinux_netlbl_socket_connect(sk, address);
पूर्ण

अटल पूर्णांक selinux_socket_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	वापस sock_has_perm(sock->sk, SOCKET__LISTEN);
पूर्ण

अटल पूर्णांक selinux_socket_accept(काष्ठा socket *sock, काष्ठा socket *newsock)
अणु
	पूर्णांक err;
	काष्ठा inode_security_काष्ठा *isec;
	काष्ठा inode_security_काष्ठा *newisec;
	u16 sclass;
	u32 sid;

	err = sock_has_perm(sock->sk, SOCKET__ACCEPT);
	अगर (err)
		वापस err;

	isec = inode_security_novalidate(SOCK_INODE(sock));
	spin_lock(&isec->lock);
	sclass = isec->sclass;
	sid = isec->sid;
	spin_unlock(&isec->lock);

	newisec = inode_security_novalidate(SOCK_INODE(newsock));
	newisec->sclass = sclass;
	newisec->sid = sid;
	newisec->initialized = LABEL_INITIALIZED;

	वापस 0;
पूर्ण

अटल पूर्णांक selinux_socket_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
				  पूर्णांक size)
अणु
	वापस sock_has_perm(sock->sk, SOCKET__WRITE);
पूर्ण

अटल पूर्णांक selinux_socket_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
				  पूर्णांक size, पूर्णांक flags)
अणु
	वापस sock_has_perm(sock->sk, SOCKET__READ);
पूर्ण

अटल पूर्णांक selinux_socket_माला_लोockname(काष्ठा socket *sock)
अणु
	वापस sock_has_perm(sock->sk, SOCKET__GETATTR);
पूर्ण

अटल पूर्णांक selinux_socket_getpeername(काष्ठा socket *sock)
अणु
	वापस sock_has_perm(sock->sk, SOCKET__GETATTR);
पूर्ण

अटल पूर्णांक selinux_socket_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname)
अणु
	पूर्णांक err;

	err = sock_has_perm(sock->sk, SOCKET__SETOPT);
	अगर (err)
		वापस err;

	वापस selinux_netlbl_socket_setsockopt(sock, level, optname);
पूर्ण

अटल पूर्णांक selinux_socket_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level,
				     पूर्णांक optname)
अणु
	वापस sock_has_perm(sock->sk, SOCKET__GETOPT);
पूर्ण

अटल पूर्णांक selinux_socket_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	वापस sock_has_perm(sock->sk, SOCKET__SHUTDOWN);
पूर्ण

अटल पूर्णांक selinux_socket_unix_stream_connect(काष्ठा sock *sock,
					      काष्ठा sock *other,
					      काष्ठा sock *newsk)
अणु
	काष्ठा sk_security_काष्ठा *sksec_sock = sock->sk_security;
	काष्ठा sk_security_काष्ठा *sksec_other = other->sk_security;
	काष्ठा sk_security_काष्ठा *sksec_new = newsk->sk_security;
	काष्ठा common_audit_data ad;
	काष्ठा lsm_network_audit net = अणु0,पूर्ण;
	पूर्णांक err;

	ad.type = LSM_AUDIT_DATA_NET;
	ad.u.net = &net;
	ad.u.net->sk = other;

	err = avc_has_perm(&selinux_state,
			   sksec_sock->sid, sksec_other->sid,
			   sksec_other->sclass,
			   UNIX_STREAM_SOCKET__CONNECTTO, &ad);
	अगर (err)
		वापस err;

	/* server child socket */
	sksec_new->peer_sid = sksec_sock->sid;
	err = security_sid_mls_copy(&selinux_state, sksec_other->sid,
				    sksec_sock->sid, &sksec_new->sid);
	अगर (err)
		वापस err;

	/* connecting socket */
	sksec_sock->peer_sid = sksec_new->sid;

	वापस 0;
पूर्ण

अटल पूर्णांक selinux_socket_unix_may_send(काष्ठा socket *sock,
					काष्ठा socket *other)
अणु
	काष्ठा sk_security_काष्ठा *ssec = sock->sk->sk_security;
	काष्ठा sk_security_काष्ठा *osec = other->sk->sk_security;
	काष्ठा common_audit_data ad;
	काष्ठा lsm_network_audit net = अणु0,पूर्ण;

	ad.type = LSM_AUDIT_DATA_NET;
	ad.u.net = &net;
	ad.u.net->sk = other->sk;

	वापस avc_has_perm(&selinux_state,
			    ssec->sid, osec->sid, osec->sclass, SOCKET__SENDTO,
			    &ad);
पूर्ण

अटल पूर्णांक selinux_inet_sys_rcv_skb(काष्ठा net *ns, पूर्णांक अगरindex,
				    अक्षर *addrp, u16 family, u32 peer_sid,
				    काष्ठा common_audit_data *ad)
अणु
	पूर्णांक err;
	u32 अगर_sid;
	u32 node_sid;

	err = sel_netअगर_sid(ns, अगरindex, &अगर_sid);
	अगर (err)
		वापस err;
	err = avc_has_perm(&selinux_state,
			   peer_sid, अगर_sid,
			   SECCLASS_NETIF, NETIF__INGRESS, ad);
	अगर (err)
		वापस err;

	err = sel_netnode_sid(addrp, family, &node_sid);
	अगर (err)
		वापस err;
	वापस avc_has_perm(&selinux_state,
			    peer_sid, node_sid,
			    SECCLASS_NODE, NODE__RECVFROM, ad);
पूर्ण

अटल पूर्णांक selinux_sock_rcv_skb_compat(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				       u16 family)
अणु
	पूर्णांक err = 0;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	u32 sk_sid = sksec->sid;
	काष्ठा common_audit_data ad;
	काष्ठा lsm_network_audit net = अणु0,पूर्ण;
	अक्षर *addrp;

	ad.type = LSM_AUDIT_DATA_NET;
	ad.u.net = &net;
	ad.u.net->netअगर = skb->skb_iअगर;
	ad.u.net->family = family;
	err = selinux_parse_skb(skb, &ad, &addrp, 1, शून्य);
	अगर (err)
		वापस err;

	अगर (selinux_secmark_enabled()) अणु
		err = avc_has_perm(&selinux_state,
				   sk_sid, skb->secmark, SECCLASS_PACKET,
				   PACKET__RECV, &ad);
		अगर (err)
			वापस err;
	पूर्ण

	err = selinux_netlbl_sock_rcv_skb(sksec, skb, family, &ad);
	अगर (err)
		वापस err;
	err = selinux_xfrm_sock_rcv_skb(sksec->sid, skb, &ad);

	वापस err;
पूर्ण

अटल पूर्णांक selinux_socket_sock_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	u16 family = sk->sk_family;
	u32 sk_sid = sksec->sid;
	काष्ठा common_audit_data ad;
	काष्ठा lsm_network_audit net = अणु0,पूर्ण;
	अक्षर *addrp;
	u8 secmark_active;
	u8 peerlbl_active;

	अगर (family != PF_INET && family != PF_INET6)
		वापस 0;

	/* Handle mapped IPv4 packets arriving via IPv6 sockets */
	अगर (family == PF_INET6 && skb->protocol == htons(ETH_P_IP))
		family = PF_INET;

	/* If any sort of compatibility mode is enabled then hanकरोff processing
	 * to the selinux_sock_rcv_skb_compat() function to deal with the
	 * special handling.  We करो this in an attempt to keep this function
	 * as fast and as clean as possible. */
	अगर (!selinux_policycap_netpeer())
		वापस selinux_sock_rcv_skb_compat(sk, skb, family);

	secmark_active = selinux_secmark_enabled();
	peerlbl_active = selinux_peerlbl_enabled();
	अगर (!secmark_active && !peerlbl_active)
		वापस 0;

	ad.type = LSM_AUDIT_DATA_NET;
	ad.u.net = &net;
	ad.u.net->netअगर = skb->skb_iअगर;
	ad.u.net->family = family;
	err = selinux_parse_skb(skb, &ad, &addrp, 1, शून्य);
	अगर (err)
		वापस err;

	अगर (peerlbl_active) अणु
		u32 peer_sid;

		err = selinux_skb_peerlbl_sid(skb, family, &peer_sid);
		अगर (err)
			वापस err;
		err = selinux_inet_sys_rcv_skb(sock_net(sk), skb->skb_iअगर,
					       addrp, family, peer_sid, &ad);
		अगर (err) अणु
			selinux_netlbl_err(skb, family, err, 0);
			वापस err;
		पूर्ण
		err = avc_has_perm(&selinux_state,
				   sk_sid, peer_sid, SECCLASS_PEER,
				   PEER__RECV, &ad);
		अगर (err) अणु
			selinux_netlbl_err(skb, family, err, 0);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (secmark_active) अणु
		err = avc_has_perm(&selinux_state,
				   sk_sid, skb->secmark, SECCLASS_PACKET,
				   PACKET__RECV, &ad);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक selinux_socket_getpeersec_stream(काष्ठा socket *sock, अक्षर __user *optval,
					    पूर्णांक __user *optlen, अचिन्हित len)
अणु
	पूर्णांक err = 0;
	अक्षर *scontext;
	u32 scontext_len;
	काष्ठा sk_security_काष्ठा *sksec = sock->sk->sk_security;
	u32 peer_sid = SECSID_शून्य;

	अगर (sksec->sclass == SECCLASS_UNIX_STREAM_SOCKET ||
	    sksec->sclass == SECCLASS_TCP_SOCKET ||
	    sksec->sclass == SECCLASS_SCTP_SOCKET)
		peer_sid = sksec->peer_sid;
	अगर (peer_sid == SECSID_शून्य)
		वापस -ENOPROTOOPT;

	err = security_sid_to_context(&selinux_state, peer_sid, &scontext,
				      &scontext_len);
	अगर (err)
		वापस err;

	अगर (scontext_len > len) अणु
		err = -दुस्फल;
		जाओ out_len;
	पूर्ण

	अगर (copy_to_user(optval, scontext, scontext_len))
		err = -EFAULT;

out_len:
	अगर (put_user(scontext_len, optlen))
		err = -EFAULT;
	kमुक्त(scontext);
	वापस err;
पूर्ण

अटल पूर्णांक selinux_socket_getpeersec_dgram(काष्ठा socket *sock, काष्ठा sk_buff *skb, u32 *secid)
अणु
	u32 peer_secid = SECSID_शून्य;
	u16 family;
	काष्ठा inode_security_काष्ठा *isec;

	अगर (skb && skb->protocol == htons(ETH_P_IP))
		family = PF_INET;
	अन्यथा अगर (skb && skb->protocol == htons(ETH_P_IPV6))
		family = PF_INET6;
	अन्यथा अगर (sock)
		family = sock->sk->sk_family;
	अन्यथा
		जाओ out;

	अगर (sock && family == PF_UNIX) अणु
		isec = inode_security_novalidate(SOCK_INODE(sock));
		peer_secid = isec->sid;
	पूर्ण अन्यथा अगर (skb)
		selinux_skb_peerlbl_sid(skb, family, &peer_secid);

out:
	*secid = peer_secid;
	अगर (peer_secid == SECSID_शून्य)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक selinux_sk_alloc_security(काष्ठा sock *sk, पूर्णांक family, gfp_t priority)
अणु
	काष्ठा sk_security_काष्ठा *sksec;

	sksec = kzalloc(माप(*sksec), priority);
	अगर (!sksec)
		वापस -ENOMEM;

	sksec->peer_sid = SECINITSID_UNLABELED;
	sksec->sid = SECINITSID_UNLABELED;
	sksec->sclass = SECCLASS_SOCKET;
	selinux_netlbl_sk_security_reset(sksec);
	sk->sk_security = sksec;

	वापस 0;
पूर्ण

अटल व्योम selinux_sk_मुक्त_security(काष्ठा sock *sk)
अणु
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;

	sk->sk_security = शून्य;
	selinux_netlbl_sk_security_मुक्त(sksec);
	kमुक्त(sksec);
पूर्ण

अटल व्योम selinux_sk_clone_security(स्थिर काष्ठा sock *sk, काष्ठा sock *newsk)
अणु
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	काष्ठा sk_security_काष्ठा *newsksec = newsk->sk_security;

	newsksec->sid = sksec->sid;
	newsksec->peer_sid = sksec->peer_sid;
	newsksec->sclass = sksec->sclass;

	selinux_netlbl_sk_security_reset(newsksec);
पूर्ण

अटल व्योम selinux_sk_माला_लोecid(काष्ठा sock *sk, u32 *secid)
अणु
	अगर (!sk)
		*secid = SECINITSID_ANY_SOCKET;
	अन्यथा अणु
		काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;

		*secid = sksec->sid;
	पूर्ण
पूर्ण

अटल व्योम selinux_sock_graft(काष्ठा sock *sk, काष्ठा socket *parent)
अणु
	काष्ठा inode_security_काष्ठा *isec =
		inode_security_novalidate(SOCK_INODE(parent));
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;

	अगर (sk->sk_family == PF_INET || sk->sk_family == PF_INET6 ||
	    sk->sk_family == PF_UNIX)
		isec->sid = sksec->sid;
	sksec->sclass = isec->sclass;
पूर्ण

/* Called whenever SCTP receives an INIT chunk. This happens when an incoming
 * connect(2), sctp_connectx(3) or sctp_sendmsg(3) (with no association
 * alपढ़ोy present).
 */
अटल पूर्णांक selinux_sctp_assoc_request(काष्ठा sctp_endpoपूर्णांक *ep,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_security_काष्ठा *sksec = ep->base.sk->sk_security;
	काष्ठा common_audit_data ad;
	काष्ठा lsm_network_audit net = अणु0,पूर्ण;
	u8 peerlbl_active;
	u32 peer_sid = SECINITSID_UNLABELED;
	u32 conn_sid;
	पूर्णांक err = 0;

	अगर (!selinux_policycap_extsockclass())
		वापस 0;

	peerlbl_active = selinux_peerlbl_enabled();

	अगर (peerlbl_active) अणु
		/* This will वापस peer_sid = SECSID_शून्य अगर there are
		 * no peer labels, see security_net_peersid_resolve().
		 */
		err = selinux_skb_peerlbl_sid(skb, ep->base.sk->sk_family,
					      &peer_sid);
		अगर (err)
			वापस err;

		अगर (peer_sid == SECSID_शून्य)
			peer_sid = SECINITSID_UNLABELED;
	पूर्ण

	अगर (sksec->sctp_assoc_state == SCTP_ASSOC_UNSET) अणु
		sksec->sctp_assoc_state = SCTP_ASSOC_SET;

		/* Here as first association on socket. As the peer SID
		 * was allowed by peer recv (and the netअगर/node checks),
		 * then it is approved by policy and used as the primary
		 * peer SID क्रम getpeercon(3).
		 */
		sksec->peer_sid = peer_sid;
	पूर्ण अन्यथा अगर  (sksec->peer_sid != peer_sid) अणु
		/* Other association peer SIDs are checked to enक्रमce
		 * consistency among the peer SIDs.
		 */
		ad.type = LSM_AUDIT_DATA_NET;
		ad.u.net = &net;
		ad.u.net->sk = ep->base.sk;
		err = avc_has_perm(&selinux_state,
				   sksec->peer_sid, peer_sid, sksec->sclass,
				   SCTP_SOCKET__ASSOCIATION, &ad);
		अगर (err)
			वापस err;
	पूर्ण

	/* Compute the MLS component क्रम the connection and store
	 * the inक्रमmation in ep. This will be used by SCTP TCP type
	 * sockets and peeled off connections as they cause a new
	 * socket to be generated. selinux_sctp_sk_clone() will then
	 * plug this पूर्णांकo the new socket.
	 */
	err = selinux_conn_sid(sksec->sid, peer_sid, &conn_sid);
	अगर (err)
		वापस err;

	ep->secid = conn_sid;
	ep->peer_secid = peer_sid;

	/* Set any NetLabel labels including CIPSO/CALIPSO options. */
	वापस selinux_netlbl_sctp_assoc_request(ep, skb);
पूर्ण

/* Check अगर sctp IPv4/IPv6 addresses are valid क्रम binding or connecting
 * based on their @optname.
 */
अटल पूर्णांक selinux_sctp_bind_connect(काष्ठा sock *sk, पूर्णांक optname,
				     काष्ठा sockaddr *address,
				     पूर्णांक addrlen)
अणु
	पूर्णांक len, err = 0, walk_size = 0;
	व्योम *addr_buf;
	काष्ठा sockaddr *addr;
	काष्ठा socket *sock;

	अगर (!selinux_policycap_extsockclass())
		वापस 0;

	/* Process one or more addresses that may be IPv4 or IPv6 */
	sock = sk->sk_socket;
	addr_buf = address;

	जबतक (walk_size < addrlen) अणु
		अगर (walk_size + माप(sa_family_t) > addrlen)
			वापस -EINVAL;

		addr = addr_buf;
		चयन (addr->sa_family) अणु
		हाल AF_UNSPEC:
		हाल AF_INET:
			len = माप(काष्ठा sockaddr_in);
			अवरोध;
		हाल AF_INET6:
			len = माप(काष्ठा sockaddr_in6);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (walk_size + len > addrlen)
			वापस -EINVAL;

		err = -EINVAL;
		चयन (optname) अणु
		/* Bind checks */
		हाल SCTP_PRIMARY_ADDR:
		हाल SCTP_SET_PEER_PRIMARY_ADDR:
		हाल SCTP_SOCKOPT_BINDX_ADD:
			err = selinux_socket_bind(sock, addr, len);
			अवरोध;
		/* Connect checks */
		हाल SCTP_SOCKOPT_CONNECTX:
		हाल SCTP_PARAM_SET_PRIMARY:
		हाल SCTP_PARAM_ADD_IP:
		हाल SCTP_SENDMSG_CONNECT:
			err = selinux_socket_connect_helper(sock, addr, len);
			अगर (err)
				वापस err;

			/* As selinux_sctp_bind_connect() is called by the
			 * SCTP protocol layer, the socket is alपढ़ोy locked,
			 * thereक्रमe selinux_netlbl_socket_connect_locked()
			 * is called here. The situations handled are:
			 * sctp_connectx(3), sctp_sendmsg(3), sendmsg(2),
			 * whenever a new IP address is added or when a new
			 * primary address is selected.
			 * Note that an SCTP connect(2) call happens beक्रमe
			 * the SCTP protocol layer and is handled via
			 * selinux_socket_connect().
			 */
			err = selinux_netlbl_socket_connect_locked(sk, addr);
			अवरोध;
		पूर्ण

		अगर (err)
			वापस err;

		addr_buf += len;
		walk_size += len;
	पूर्ण

	वापस 0;
पूर्ण

/* Called whenever a new socket is created by accept(2) or sctp_peeloff(3). */
अटल व्योम selinux_sctp_sk_clone(काष्ठा sctp_endpoपूर्णांक *ep, काष्ठा sock *sk,
				  काष्ठा sock *newsk)
अणु
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	काष्ठा sk_security_काष्ठा *newsksec = newsk->sk_security;

	/* If policy करोes not support SECCLASS_SCTP_SOCKET then call
	 * the non-sctp clone version.
	 */
	अगर (!selinux_policycap_extsockclass())
		वापस selinux_sk_clone_security(sk, newsk);

	newsksec->sid = ep->secid;
	newsksec->peer_sid = ep->peer_secid;
	newsksec->sclass = sksec->sclass;
	selinux_netlbl_sctp_sk_clone(sk, newsk);
पूर्ण

अटल पूर्णांक selinux_inet_conn_request(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				     काष्ठा request_sock *req)
अणु
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	पूर्णांक err;
	u16 family = req->rsk_ops->family;
	u32 connsid;
	u32 peersid;

	err = selinux_skb_peerlbl_sid(skb, family, &peersid);
	अगर (err)
		वापस err;
	err = selinux_conn_sid(sksec->sid, peersid, &connsid);
	अगर (err)
		वापस err;
	req->secid = connsid;
	req->peer_secid = peersid;

	वापस selinux_netlbl_inet_conn_request(req, family);
पूर्ण

अटल व्योम selinux_inet_csk_clone(काष्ठा sock *newsk,
				   स्थिर काष्ठा request_sock *req)
अणु
	काष्ठा sk_security_काष्ठा *newsksec = newsk->sk_security;

	newsksec->sid = req->secid;
	newsksec->peer_sid = req->peer_secid;
	/* NOTE: Ideally, we should also get the isec->sid क्रम the
	   new socket in sync, but we करोn't have the isec available yet.
	   So we will रुको until sock_graft to करो it, by which
	   समय it will have been created and available. */

	/* We करोn't need to take any sort of lock here as we are the only
	 * thपढ़ो with access to newsksec */
	selinux_netlbl_inet_csk_clone(newsk, req->rsk_ops->family);
पूर्ण

अटल व्योम selinux_inet_conn_established(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	u16 family = sk->sk_family;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;

	/* handle mapped IPv4 packets arriving via IPv6 sockets */
	अगर (family == PF_INET6 && skb->protocol == htons(ETH_P_IP))
		family = PF_INET;

	selinux_skb_peerlbl_sid(skb, family, &sksec->peer_sid);
पूर्ण

अटल पूर्णांक selinux_secmark_relabel_packet(u32 sid)
अणु
	स्थिर काष्ठा task_security_काष्ठा *__tsec;
	u32 tsid;

	__tsec = selinux_cred(current_cred());
	tsid = __tsec->sid;

	वापस avc_has_perm(&selinux_state,
			    tsid, sid, SECCLASS_PACKET, PACKET__RELABELTO,
			    शून्य);
पूर्ण

अटल व्योम selinux_secmark_refcount_inc(व्योम)
अणु
	atomic_inc(&selinux_secmark_refcount);
पूर्ण

अटल व्योम selinux_secmark_refcount_dec(व्योम)
अणु
	atomic_dec(&selinux_secmark_refcount);
पूर्ण

अटल व्योम selinux_req_classअगरy_flow(स्थिर काष्ठा request_sock *req,
				      काष्ठा flowi_common *flic)
अणु
	flic->flowic_secid = req->secid;
पूर्ण

अटल पूर्णांक selinux_tun_dev_alloc_security(व्योम **security)
अणु
	काष्ठा tun_security_काष्ठा *tunsec;

	tunsec = kzalloc(माप(*tunsec), GFP_KERNEL);
	अगर (!tunsec)
		वापस -ENOMEM;
	tunsec->sid = current_sid();

	*security = tunsec;
	वापस 0;
पूर्ण

अटल व्योम selinux_tun_dev_मुक्त_security(व्योम *security)
अणु
	kमुक्त(security);
पूर्ण

अटल पूर्णांक selinux_tun_dev_create(व्योम)
अणु
	u32 sid = current_sid();

	/* we aren't taking पूर्णांकo account the "sockcreate" SID since the socket
	 * that is being created here is not a socket in the traditional sense,
	 * instead it is a निजी sock, accessible only to the kernel, and
	 * representing a wide range of network traffic spanning multiple
	 * connections unlike traditional sockets - check the TUN driver to
	 * get a better understanding of why this socket is special */

	वापस avc_has_perm(&selinux_state,
			    sid, sid, SECCLASS_TUN_SOCKET, TUN_SOCKET__CREATE,
			    शून्य);
पूर्ण

अटल पूर्णांक selinux_tun_dev_attach_queue(व्योम *security)
अणु
	काष्ठा tun_security_काष्ठा *tunsec = security;

	वापस avc_has_perm(&selinux_state,
			    current_sid(), tunsec->sid, SECCLASS_TUN_SOCKET,
			    TUN_SOCKET__ATTACH_QUEUE, शून्य);
पूर्ण

अटल पूर्णांक selinux_tun_dev_attach(काष्ठा sock *sk, व्योम *security)
अणु
	काष्ठा tun_security_काष्ठा *tunsec = security;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;

	/* we करोn't currently perक्रमm any NetLabel based labeling here and it
	 * isn't clear that we would want to करो so anyway; जबतक we could apply
	 * labeling without the support of the TUN user the resulting labeled
	 * traffic from the other end of the connection would almost certainly
	 * cause confusion to the TUN user that had no idea network labeling
	 * protocols were being used */

	sksec->sid = tunsec->sid;
	sksec->sclass = SECCLASS_TUN_SOCKET;

	वापस 0;
पूर्ण

अटल पूर्णांक selinux_tun_dev_खोलो(व्योम *security)
अणु
	काष्ठा tun_security_काष्ठा *tunsec = security;
	u32 sid = current_sid();
	पूर्णांक err;

	err = avc_has_perm(&selinux_state,
			   sid, tunsec->sid, SECCLASS_TUN_SOCKET,
			   TUN_SOCKET__RELABELFROM, शून्य);
	अगर (err)
		वापस err;
	err = avc_has_perm(&selinux_state,
			   sid, sid, SECCLASS_TUN_SOCKET,
			   TUN_SOCKET__RELABELTO, शून्य);
	अगर (err)
		वापस err;
	tunsec->sid = sid;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NETFILTER

अटल अचिन्हित पूर्णांक selinux_ip_क्रमward(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा net_device *indev,
				       u16 family)
अणु
	पूर्णांक err;
	अक्षर *addrp;
	u32 peer_sid;
	काष्ठा common_audit_data ad;
	काष्ठा lsm_network_audit net = अणु0,पूर्ण;
	u8 secmark_active;
	u8 netlbl_active;
	u8 peerlbl_active;

	अगर (!selinux_policycap_netpeer())
		वापस NF_ACCEPT;

	secmark_active = selinux_secmark_enabled();
	netlbl_active = netlbl_enabled();
	peerlbl_active = selinux_peerlbl_enabled();
	अगर (!secmark_active && !peerlbl_active)
		वापस NF_ACCEPT;

	अगर (selinux_skb_peerlbl_sid(skb, family, &peer_sid) != 0)
		वापस NF_DROP;

	ad.type = LSM_AUDIT_DATA_NET;
	ad.u.net = &net;
	ad.u.net->netअगर = indev->अगरindex;
	ad.u.net->family = family;
	अगर (selinux_parse_skb(skb, &ad, &addrp, 1, शून्य) != 0)
		वापस NF_DROP;

	अगर (peerlbl_active) अणु
		err = selinux_inet_sys_rcv_skb(dev_net(indev), indev->अगरindex,
					       addrp, family, peer_sid, &ad);
		अगर (err) अणु
			selinux_netlbl_err(skb, family, err, 1);
			वापस NF_DROP;
		पूर्ण
	पूर्ण

	अगर (secmark_active)
		अगर (avc_has_perm(&selinux_state,
				 peer_sid, skb->secmark,
				 SECCLASS_PACKET, PACKET__FORWARD_IN, &ad))
			वापस NF_DROP;

	अगर (netlbl_active)
		/* we करो this in the FORWARD path and not the POST_ROUTING
		 * path because we want to make sure we apply the necessary
		 * labeling beक्रमe IPsec is applied so we can leverage AH
		 * protection */
		अगर (selinux_netlbl_skbuff_setsid(skb, family, peer_sid) != 0)
			वापस NF_DROP;

	वापस NF_ACCEPT;
पूर्ण

अटल अचिन्हित पूर्णांक selinux_ipv4_क्रमward(व्योम *priv,
					 काष्ठा sk_buff *skb,
					 स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस selinux_ip_क्रमward(skb, state->in, PF_INET);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अचिन्हित पूर्णांक selinux_ipv6_क्रमward(व्योम *priv,
					 काष्ठा sk_buff *skb,
					 स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस selinux_ip_क्रमward(skb, state->in, PF_INET6);
पूर्ण
#पूर्ण_अगर	/* IPV6 */

अटल अचिन्हित पूर्णांक selinux_ip_output(काष्ठा sk_buff *skb,
				      u16 family)
अणु
	काष्ठा sock *sk;
	u32 sid;

	अगर (!netlbl_enabled())
		वापस NF_ACCEPT;

	/* we करो this in the LOCAL_OUT path and not the POST_ROUTING path
	 * because we want to make sure we apply the necessary labeling
	 * beक्रमe IPsec is applied so we can leverage AH protection */
	sk = skb->sk;
	अगर (sk) अणु
		काष्ठा sk_security_काष्ठा *sksec;

		अगर (sk_listener(sk))
			/* अगर the socket is the listening state then this
			 * packet is a SYN-ACK packet which means it needs to
			 * be labeled based on the connection/request_sock and
			 * not the parent socket.  unक्रमtunately, we can't
			 * lookup the request_sock yet as it isn't queued on
			 * the parent socket until after the SYN-ACK is sent.
			 * the "solution" is to simply pass the packet as-is
			 * as any IP option based labeling should be copied
			 * from the initial connection request (in the IP
			 * layer).  it is far from ideal, but until we get a
			 * security label in the packet itself this is the
			 * best we can करो. */
			वापस NF_ACCEPT;

		/* standard practice, label using the parent socket */
		sksec = sk->sk_security;
		sid = sksec->sid;
	पूर्ण अन्यथा
		sid = SECINITSID_KERNEL;
	अगर (selinux_netlbl_skbuff_setsid(skb, family, sid) != 0)
		वापस NF_DROP;

	वापस NF_ACCEPT;
पूर्ण

अटल अचिन्हित पूर्णांक selinux_ipv4_output(व्योम *priv,
					काष्ठा sk_buff *skb,
					स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस selinux_ip_output(skb, PF_INET);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अचिन्हित पूर्णांक selinux_ipv6_output(व्योम *priv,
					काष्ठा sk_buff *skb,
					स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस selinux_ip_output(skb, PF_INET6);
पूर्ण
#पूर्ण_अगर	/* IPV6 */

अटल अचिन्हित पूर्णांक selinux_ip_postroute_compat(काष्ठा sk_buff *skb,
						पूर्णांक अगरindex,
						u16 family)
अणु
	काष्ठा sock *sk = skb_to_full_sk(skb);
	काष्ठा sk_security_काष्ठा *sksec;
	काष्ठा common_audit_data ad;
	काष्ठा lsm_network_audit net = अणु0,पूर्ण;
	अक्षर *addrp;
	u8 proto;

	अगर (sk == शून्य)
		वापस NF_ACCEPT;
	sksec = sk->sk_security;

	ad.type = LSM_AUDIT_DATA_NET;
	ad.u.net = &net;
	ad.u.net->netअगर = अगरindex;
	ad.u.net->family = family;
	अगर (selinux_parse_skb(skb, &ad, &addrp, 0, &proto))
		वापस NF_DROP;

	अगर (selinux_secmark_enabled())
		अगर (avc_has_perm(&selinux_state,
				 sksec->sid, skb->secmark,
				 SECCLASS_PACKET, PACKET__SEND, &ad))
			वापस NF_DROP_ERR(-ECONNREFUSED);

	अगर (selinux_xfrm_postroute_last(sksec->sid, skb, &ad, proto))
		वापस NF_DROP_ERR(-ECONNREFUSED);

	वापस NF_ACCEPT;
पूर्ण

अटल अचिन्हित पूर्णांक selinux_ip_postroute(काष्ठा sk_buff *skb,
					 स्थिर काष्ठा net_device *outdev,
					 u16 family)
अणु
	u32 secmark_perm;
	u32 peer_sid;
	पूर्णांक अगरindex = outdev->अगरindex;
	काष्ठा sock *sk;
	काष्ठा common_audit_data ad;
	काष्ठा lsm_network_audit net = अणु0,पूर्ण;
	अक्षर *addrp;
	u8 secmark_active;
	u8 peerlbl_active;

	/* If any sort of compatibility mode is enabled then hanकरोff processing
	 * to the selinux_ip_postroute_compat() function to deal with the
	 * special handling.  We करो this in an attempt to keep this function
	 * as fast and as clean as possible. */
	अगर (!selinux_policycap_netpeer())
		वापस selinux_ip_postroute_compat(skb, अगरindex, family);

	secmark_active = selinux_secmark_enabled();
	peerlbl_active = selinux_peerlbl_enabled();
	अगर (!secmark_active && !peerlbl_active)
		वापस NF_ACCEPT;

	sk = skb_to_full_sk(skb);

#अगर_घोषित CONFIG_XFRM
	/* If skb->dst->xfrm is non-शून्य then the packet is undergoing an IPsec
	 * packet transक्रमmation so allow the packet to pass without any checks
	 * since we'll have another chance to perक्रमm access control checks
	 * when the packet is on it's final way out.
	 * NOTE: there appear to be some IPv6 multicast हालs where skb->dst
	 *       is शून्य, in this हाल go ahead and apply access control.
	 * NOTE: अगर this is a local socket (skb->sk != शून्य) that is in the
	 *       TCP listening state we cannot रुको until the XFRM processing
	 *       is करोne as we will miss out on the SA label अगर we करो;
	 *       unक्रमtunately, this means more work, but it is only once per
	 *       connection. */
	अगर (skb_dst(skb) != शून्य && skb_dst(skb)->xfrm != शून्य &&
	    !(sk && sk_listener(sk)))
		वापस NF_ACCEPT;
#पूर्ण_अगर

	अगर (sk == शून्य) अणु
		/* Without an associated socket the packet is either coming
		 * from the kernel or it is being क्रमwarded; check the packet
		 * to determine which and अगर the packet is being क्रमwarded
		 * query the packet directly to determine the security label. */
		अगर (skb->skb_iअगर) अणु
			secmark_perm = PACKET__FORWARD_OUT;
			अगर (selinux_skb_peerlbl_sid(skb, family, &peer_sid))
				वापस NF_DROP;
		पूर्ण अन्यथा अणु
			secmark_perm = PACKET__SEND;
			peer_sid = SECINITSID_KERNEL;
		पूर्ण
	पूर्ण अन्यथा अगर (sk_listener(sk)) अणु
		/* Locally generated packet but the associated socket is in the
		 * listening state which means this is a SYN-ACK packet.  In
		 * this particular हाल the correct security label is asचिन्हित
		 * to the connection/request_sock but unक्रमtunately we can't
		 * query the request_sock as it isn't queued on the parent
		 * socket until after the SYN-ACK packet is sent; the only
		 * viable choice is to regenerate the label like we करो in
		 * selinux_inet_conn_request().  See also selinux_ip_output()
		 * क्रम similar problems. */
		u32 skb_sid;
		काष्ठा sk_security_काष्ठा *sksec;

		sksec = sk->sk_security;
		अगर (selinux_skb_peerlbl_sid(skb, family, &skb_sid))
			वापस NF_DROP;
		/* At this poपूर्णांक, अगर the वापसed skb peerlbl is SECSID_शून्य
		 * and the packet has been through at least one XFRM
		 * transक्रमmation then we must be dealing with the "final"
		 * क्रमm of labeled IPsec packet; since we've alपढ़ोy applied
		 * all of our access controls on this packet we can safely
		 * pass the packet. */
		अगर (skb_sid == SECSID_शून्य) अणु
			चयन (family) अणु
			हाल PF_INET:
				अगर (IPCB(skb)->flags & IPSKB_XFRM_TRANSFORMED)
					वापस NF_ACCEPT;
				अवरोध;
			हाल PF_INET6:
				अगर (IP6CB(skb)->flags & IP6SKB_XFRM_TRANSFORMED)
					वापस NF_ACCEPT;
				अवरोध;
			शेष:
				वापस NF_DROP_ERR(-ECONNREFUSED);
			पूर्ण
		पूर्ण
		अगर (selinux_conn_sid(sksec->sid, skb_sid, &peer_sid))
			वापस NF_DROP;
		secmark_perm = PACKET__SEND;
	पूर्ण अन्यथा अणु
		/* Locally generated packet, fetch the security label from the
		 * associated socket. */
		काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
		peer_sid = sksec->sid;
		secmark_perm = PACKET__SEND;
	पूर्ण

	ad.type = LSM_AUDIT_DATA_NET;
	ad.u.net = &net;
	ad.u.net->netअगर = अगरindex;
	ad.u.net->family = family;
	अगर (selinux_parse_skb(skb, &ad, &addrp, 0, शून्य))
		वापस NF_DROP;

	अगर (secmark_active)
		अगर (avc_has_perm(&selinux_state,
				 peer_sid, skb->secmark,
				 SECCLASS_PACKET, secmark_perm, &ad))
			वापस NF_DROP_ERR(-ECONNREFUSED);

	अगर (peerlbl_active) अणु
		u32 अगर_sid;
		u32 node_sid;

		अगर (sel_netअगर_sid(dev_net(outdev), अगरindex, &अगर_sid))
			वापस NF_DROP;
		अगर (avc_has_perm(&selinux_state,
				 peer_sid, अगर_sid,
				 SECCLASS_NETIF, NETIF__EGRESS, &ad))
			वापस NF_DROP_ERR(-ECONNREFUSED);

		अगर (sel_netnode_sid(addrp, family, &node_sid))
			वापस NF_DROP;
		अगर (avc_has_perm(&selinux_state,
				 peer_sid, node_sid,
				 SECCLASS_NODE, NODE__SENDTO, &ad))
			वापस NF_DROP_ERR(-ECONNREFUSED);
	पूर्ण

	वापस NF_ACCEPT;
पूर्ण

अटल अचिन्हित पूर्णांक selinux_ipv4_postroute(व्योम *priv,
					   काष्ठा sk_buff *skb,
					   स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस selinux_ip_postroute(skb, state->out, PF_INET);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अचिन्हित पूर्णांक selinux_ipv6_postroute(व्योम *priv,
					   काष्ठा sk_buff *skb,
					   स्थिर काष्ठा nf_hook_state *state)
अणु
	वापस selinux_ip_postroute(skb, state->out, PF_INET6);
पूर्ण
#पूर्ण_अगर	/* IPV6 */

#पूर्ण_अगर	/* CONFIG_NETFILTER */

अटल पूर्णांक selinux_netlink_send(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक msg_len;
	अचिन्हित पूर्णांक data_len = skb->len;
	अचिन्हित अक्षर *data = skb->data;
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_security_काष्ठा *sksec = sk->sk_security;
	u16 sclass = sksec->sclass;
	u32 perm;

	जबतक (data_len >= nlmsg_total_size(0)) अणु
		nlh = (काष्ठा nlmsghdr *)data;

		/* NOTE: the nlmsg_len field isn't reliably set by some netlink
		 *       users which means we can't reject skb's with bogus
		 *       length fields; our solution is to follow what
		 *       netlink_rcv_skb() करोes and simply skip processing at
		 *       messages with length fields that are clearly junk
		 */
		अगर (nlh->nlmsg_len < NLMSG_HDRLEN || nlh->nlmsg_len > data_len)
			वापस 0;

		rc = selinux_nlmsg_lookup(sclass, nlh->nlmsg_type, &perm);
		अगर (rc == 0) अणु
			rc = sock_has_perm(sk, perm);
			अगर (rc)
				वापस rc;
		पूर्ण अन्यथा अगर (rc == -EINVAL) अणु
			/* -EINVAL is a missing msg/perm mapping */
			pr_warn_ratelimited("SELinux: unrecognized netlink"
				" message: protocol=%hu nlmsg_type=%hu sclass=%s"
				" pid=%d comm=%s\n",
				sk->sk_protocol, nlh->nlmsg_type,
				secclass_map[sclass - 1].name,
				task_pid_nr(current), current->comm);
			अगर (enक्रमcing_enabled(&selinux_state) &&
			    !security_get_allow_unknown(&selinux_state))
				वापस rc;
			rc = 0;
		पूर्ण अन्यथा अगर (rc == -ENOENT) अणु
			/* -ENOENT is a missing socket/class mapping, ignore */
			rc = 0;
		पूर्ण अन्यथा अणु
			वापस rc;
		पूर्ण

		/* move to the next message after applying netlink padding */
		msg_len = NLMSG_ALIGN(nlh->nlmsg_len);
		अगर (msg_len >= data_len)
			वापस 0;
		data_len -= msg_len;
		data += msg_len;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम ipc_init_security(काष्ठा ipc_security_काष्ठा *isec, u16 sclass)
अणु
	isec->sclass = sclass;
	isec->sid = current_sid();
पूर्ण

अटल पूर्णांक ipc_has_perm(काष्ठा kern_ipc_perm *ipc_perms,
			u32 perms)
अणु
	काष्ठा ipc_security_काष्ठा *isec;
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();

	isec = selinux_ipc(ipc_perms);

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = ipc_perms->key;

	वापस avc_has_perm(&selinux_state,
			    sid, isec->sid, isec->sclass, perms, &ad);
पूर्ण

अटल पूर्णांक selinux_msg_msg_alloc_security(काष्ठा msg_msg *msg)
अणु
	काष्ठा msg_security_काष्ठा *msec;

	msec = selinux_msg_msg(msg);
	msec->sid = SECINITSID_UNLABELED;

	वापस 0;
पूर्ण

/* message queue security operations */
अटल पूर्णांक selinux_msg_queue_alloc_security(काष्ठा kern_ipc_perm *msq)
अणु
	काष्ठा ipc_security_काष्ठा *isec;
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();
	पूर्णांक rc;

	isec = selinux_ipc(msq);
	ipc_init_security(isec, SECCLASS_MSGQ);

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = msq->key;

	rc = avc_has_perm(&selinux_state,
			  sid, isec->sid, SECCLASS_MSGQ,
			  MSGQ__CREATE, &ad);
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_msg_queue_associate(काष्ठा kern_ipc_perm *msq, पूर्णांक msqflg)
अणु
	काष्ठा ipc_security_काष्ठा *isec;
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();

	isec = selinux_ipc(msq);

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = msq->key;

	वापस avc_has_perm(&selinux_state,
			    sid, isec->sid, SECCLASS_MSGQ,
			    MSGQ__ASSOCIATE, &ad);
पूर्ण

अटल पूर्णांक selinux_msg_queue_msgctl(काष्ठा kern_ipc_perm *msq, पूर्णांक cmd)
अणु
	पूर्णांक err;
	पूर्णांक perms;

	चयन (cmd) अणु
	हाल IPC_INFO:
	हाल MSG_INFO:
		/* No specअगरic object, just general प्रणाली-wide inक्रमmation. */
		वापस avc_has_perm(&selinux_state,
				    current_sid(), SECINITSID_KERNEL,
				    SECCLASS_SYSTEM, SYSTEM__IPC_INFO, शून्य);
	हाल IPC_STAT:
	हाल MSG_STAT:
	हाल MSG_STAT_ANY:
		perms = MSGQ__GETATTR | MSGQ__ASSOCIATE;
		अवरोध;
	हाल IPC_SET:
		perms = MSGQ__SETATTR;
		अवरोध;
	हाल IPC_RMID:
		perms = MSGQ__DESTROY;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	err = ipc_has_perm(msq, perms);
	वापस err;
पूर्ण

अटल पूर्णांक selinux_msg_queue_msgsnd(काष्ठा kern_ipc_perm *msq, काष्ठा msg_msg *msg, पूर्णांक msqflg)
अणु
	काष्ठा ipc_security_काष्ठा *isec;
	काष्ठा msg_security_काष्ठा *msec;
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();
	पूर्णांक rc;

	isec = selinux_ipc(msq);
	msec = selinux_msg_msg(msg);

	/*
	 * First समय through, need to assign label to the message
	 */
	अगर (msec->sid == SECINITSID_UNLABELED) अणु
		/*
		 * Compute new sid based on current process and
		 * message queue this message will be stored in
		 */
		rc = security_transition_sid(&selinux_state, sid, isec->sid,
					     SECCLASS_MSG, शून्य, &msec->sid);
		अगर (rc)
			वापस rc;
	पूर्ण

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = msq->key;

	/* Can this process ग_लिखो to the queue? */
	rc = avc_has_perm(&selinux_state,
			  sid, isec->sid, SECCLASS_MSGQ,
			  MSGQ__WRITE, &ad);
	अगर (!rc)
		/* Can this process send the message */
		rc = avc_has_perm(&selinux_state,
				  sid, msec->sid, SECCLASS_MSG,
				  MSG__SEND, &ad);
	अगर (!rc)
		/* Can the message be put in the queue? */
		rc = avc_has_perm(&selinux_state,
				  msec->sid, isec->sid, SECCLASS_MSGQ,
				  MSGQ__ENQUEUE, &ad);

	वापस rc;
पूर्ण

अटल पूर्णांक selinux_msg_queue_msgrcv(काष्ठा kern_ipc_perm *msq, काष्ठा msg_msg *msg,
				    काष्ठा task_काष्ठा *target,
				    दीर्घ type, पूर्णांक mode)
अणु
	काष्ठा ipc_security_काष्ठा *isec;
	काष्ठा msg_security_काष्ठा *msec;
	काष्ठा common_audit_data ad;
	u32 sid = task_sid_subj(target);
	पूर्णांक rc;

	isec = selinux_ipc(msq);
	msec = selinux_msg_msg(msg);

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = msq->key;

	rc = avc_has_perm(&selinux_state,
			  sid, isec->sid,
			  SECCLASS_MSGQ, MSGQ__READ, &ad);
	अगर (!rc)
		rc = avc_has_perm(&selinux_state,
				  sid, msec->sid,
				  SECCLASS_MSG, MSG__RECEIVE, &ad);
	वापस rc;
पूर्ण

/* Shared Memory security operations */
अटल पूर्णांक selinux_shm_alloc_security(काष्ठा kern_ipc_perm *shp)
अणु
	काष्ठा ipc_security_काष्ठा *isec;
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();
	पूर्णांक rc;

	isec = selinux_ipc(shp);
	ipc_init_security(isec, SECCLASS_SHM);

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = shp->key;

	rc = avc_has_perm(&selinux_state,
			  sid, isec->sid, SECCLASS_SHM,
			  SHM__CREATE, &ad);
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_shm_associate(काष्ठा kern_ipc_perm *shp, पूर्णांक shmflg)
अणु
	काष्ठा ipc_security_काष्ठा *isec;
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();

	isec = selinux_ipc(shp);

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = shp->key;

	वापस avc_has_perm(&selinux_state,
			    sid, isec->sid, SECCLASS_SHM,
			    SHM__ASSOCIATE, &ad);
पूर्ण

/* Note, at this poपूर्णांक, shp is locked करोwn */
अटल पूर्णांक selinux_shm_shmctl(काष्ठा kern_ipc_perm *shp, पूर्णांक cmd)
अणु
	पूर्णांक perms;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल IPC_INFO:
	हाल SHM_INFO:
		/* No specअगरic object, just general प्रणाली-wide inक्रमmation. */
		वापस avc_has_perm(&selinux_state,
				    current_sid(), SECINITSID_KERNEL,
				    SECCLASS_SYSTEM, SYSTEM__IPC_INFO, शून्य);
	हाल IPC_STAT:
	हाल SHM_STAT:
	हाल SHM_STAT_ANY:
		perms = SHM__GETATTR | SHM__ASSOCIATE;
		अवरोध;
	हाल IPC_SET:
		perms = SHM__SETATTR;
		अवरोध;
	हाल SHM_LOCK:
	हाल SHM_UNLOCK:
		perms = SHM__LOCK;
		अवरोध;
	हाल IPC_RMID:
		perms = SHM__DESTROY;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	err = ipc_has_perm(shp, perms);
	वापस err;
पूर्ण

अटल पूर्णांक selinux_shm_shmat(काष्ठा kern_ipc_perm *shp,
			     अक्षर __user *shmaddr, पूर्णांक shmflg)
अणु
	u32 perms;

	अगर (shmflg & SHM_RDONLY)
		perms = SHM__READ;
	अन्यथा
		perms = SHM__READ | SHM__WRITE;

	वापस ipc_has_perm(shp, perms);
पूर्ण

/* Semaphore security operations */
अटल पूर्णांक selinux_sem_alloc_security(काष्ठा kern_ipc_perm *sma)
अणु
	काष्ठा ipc_security_काष्ठा *isec;
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();
	पूर्णांक rc;

	isec = selinux_ipc(sma);
	ipc_init_security(isec, SECCLASS_SEM);

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = sma->key;

	rc = avc_has_perm(&selinux_state,
			  sid, isec->sid, SECCLASS_SEM,
			  SEM__CREATE, &ad);
	वापस rc;
पूर्ण

अटल पूर्णांक selinux_sem_associate(काष्ठा kern_ipc_perm *sma, पूर्णांक semflg)
अणु
	काष्ठा ipc_security_काष्ठा *isec;
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();

	isec = selinux_ipc(sma);

	ad.type = LSM_AUDIT_DATA_IPC;
	ad.u.ipc_id = sma->key;

	वापस avc_has_perm(&selinux_state,
			    sid, isec->sid, SECCLASS_SEM,
			    SEM__ASSOCIATE, &ad);
पूर्ण

/* Note, at this poपूर्णांक, sma is locked करोwn */
अटल पूर्णांक selinux_sem_semctl(काष्ठा kern_ipc_perm *sma, पूर्णांक cmd)
अणु
	पूर्णांक err;
	u32 perms;

	चयन (cmd) अणु
	हाल IPC_INFO:
	हाल SEM_INFO:
		/* No specअगरic object, just general प्रणाली-wide inक्रमmation. */
		वापस avc_has_perm(&selinux_state,
				    current_sid(), SECINITSID_KERNEL,
				    SECCLASS_SYSTEM, SYSTEM__IPC_INFO, शून्य);
	हाल GETPID:
	हाल GETNCNT:
	हाल GETZCNT:
		perms = SEM__GETATTR;
		अवरोध;
	हाल GETVAL:
	हाल GETALL:
		perms = SEM__READ;
		अवरोध;
	हाल SETVAL:
	हाल SETALL:
		perms = SEM__WRITE;
		अवरोध;
	हाल IPC_RMID:
		perms = SEM__DESTROY;
		अवरोध;
	हाल IPC_SET:
		perms = SEM__SETATTR;
		अवरोध;
	हाल IPC_STAT:
	हाल SEM_STAT:
	हाल SEM_STAT_ANY:
		perms = SEM__GETATTR | SEM__ASSOCIATE;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	err = ipc_has_perm(sma, perms);
	वापस err;
पूर्ण

अटल पूर्णांक selinux_sem_semop(काष्ठा kern_ipc_perm *sma,
			     काष्ठा sembuf *sops, अचिन्हित nsops, पूर्णांक alter)
अणु
	u32 perms;

	अगर (alter)
		perms = SEM__READ | SEM__WRITE;
	अन्यथा
		perms = SEM__READ;

	वापस ipc_has_perm(sma, perms);
पूर्ण

अटल पूर्णांक selinux_ipc_permission(काष्ठा kern_ipc_perm *ipcp, लघु flag)
अणु
	u32 av = 0;

	av = 0;
	अगर (flag & S_IRUGO)
		av |= IPC__UNIX_READ;
	अगर (flag & S_IWUGO)
		av |= IPC__UNIX_WRITE;

	अगर (av == 0)
		वापस 0;

	वापस ipc_has_perm(ipcp, av);
पूर्ण

अटल व्योम selinux_ipc_माला_लोecid(काष्ठा kern_ipc_perm *ipcp, u32 *secid)
अणु
	काष्ठा ipc_security_काष्ठा *isec = selinux_ipc(ipcp);
	*secid = isec->sid;
पूर्ण

अटल व्योम selinux_d_instantiate(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	अगर (inode)
		inode_करोinit_with_dentry(inode, dentry);
पूर्ण

अटल पूर्णांक selinux_getprocattr(काष्ठा task_काष्ठा *p,
			       अक्षर *name, अक्षर **value)
अणु
	स्थिर काष्ठा task_security_काष्ठा *__tsec;
	u32 sid;
	पूर्णांक error;
	अचिन्हित len;

	rcu_पढ़ो_lock();
	__tsec = selinux_cred(__task_cred(p));

	अगर (current != p) अणु
		error = avc_has_perm(&selinux_state,
				     current_sid(), __tsec->sid,
				     SECCLASS_PROCESS, PROCESS__GETATTR, शून्य);
		अगर (error)
			जाओ bad;
	पूर्ण

	अगर (!म_भेद(name, "current"))
		sid = __tsec->sid;
	अन्यथा अगर (!म_भेद(name, "prev"))
		sid = __tsec->osid;
	अन्यथा अगर (!म_भेद(name, "exec"))
		sid = __tsec->exec_sid;
	अन्यथा अगर (!म_भेद(name, "fscreate"))
		sid = __tsec->create_sid;
	अन्यथा अगर (!म_भेद(name, "keycreate"))
		sid = __tsec->keycreate_sid;
	अन्यथा अगर (!म_भेद(name, "sockcreate"))
		sid = __tsec->sockcreate_sid;
	अन्यथा अणु
		error = -EINVAL;
		जाओ bad;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!sid)
		वापस 0;

	error = security_sid_to_context(&selinux_state, sid, value, &len);
	अगर (error)
		वापस error;
	वापस len;

bad:
	rcu_पढ़ो_unlock();
	वापस error;
पूर्ण

अटल पूर्णांक selinux_setprocattr(स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	काष्ठा task_security_काष्ठा *tsec;
	काष्ठा cred *new;
	u32 mysid = current_sid(), sid = 0, ptsid;
	पूर्णांक error;
	अक्षर *str = value;

	/*
	 * Basic control over ability to set these attributes at all.
	 */
	अगर (!म_भेद(name, "exec"))
		error = avc_has_perm(&selinux_state,
				     mysid, mysid, SECCLASS_PROCESS,
				     PROCESS__SETEXEC, शून्य);
	अन्यथा अगर (!म_भेद(name, "fscreate"))
		error = avc_has_perm(&selinux_state,
				     mysid, mysid, SECCLASS_PROCESS,
				     PROCESS__SETFSCREATE, शून्य);
	अन्यथा अगर (!म_भेद(name, "keycreate"))
		error = avc_has_perm(&selinux_state,
				     mysid, mysid, SECCLASS_PROCESS,
				     PROCESS__SETKEYCREATE, शून्य);
	अन्यथा अगर (!म_भेद(name, "sockcreate"))
		error = avc_has_perm(&selinux_state,
				     mysid, mysid, SECCLASS_PROCESS,
				     PROCESS__SETSOCKCREATE, शून्य);
	अन्यथा अगर (!म_भेद(name, "current"))
		error = avc_has_perm(&selinux_state,
				     mysid, mysid, SECCLASS_PROCESS,
				     PROCESS__SETCURRENT, शून्य);
	अन्यथा
		error = -EINVAL;
	अगर (error)
		वापस error;

	/* Obtain a SID क्रम the context, अगर one was specअगरied. */
	अगर (size && str[0] && str[0] != '\n') अणु
		अगर (str[size-1] == '\n') अणु
			str[size-1] = 0;
			size--;
		पूर्ण
		error = security_context_to_sid(&selinux_state, value, size,
						&sid, GFP_KERNEL);
		अगर (error == -EINVAL && !म_भेद(name, "fscreate")) अणु
			अगर (!has_cap_mac_admin(true)) अणु
				काष्ठा audit_buffer *ab;
				माप_प्रकार audit_size;

				/* We strip a nul only अगर it is at the end, otherwise the
				 * context contains a nul and we should audit that */
				अगर (str[size - 1] == '\0')
					audit_size = size - 1;
				अन्यथा
					audit_size = size;
				ab = audit_log_start(audit_context(),
						     GFP_ATOMIC,
						     AUDIT_SELINUX_ERR);
				audit_log_क्रमmat(ab, "op=fscreate invalid_context=");
				audit_log_n_untrustedstring(ab, value, audit_size);
				audit_log_end(ab);

				वापस error;
			पूर्ण
			error = security_context_to_sid_क्रमce(
						      &selinux_state,
						      value, size, &sid);
		पूर्ण
		अगर (error)
			वापस error;
	पूर्ण

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;

	/* Permission checking based on the specअगरied context is
	   perक्रमmed during the actual operation (execve,
	   खोलो/सूची_गढ़ो/...), when we know the full context of the
	   operation.  See selinux_bprm_creds_क्रम_exec क्रम the execve
	   checks and may_create क्रम the file creation checks. The
	   operation will then fail अगर the context is not permitted. */
	tsec = selinux_cred(new);
	अगर (!म_भेद(name, "exec")) अणु
		tsec->exec_sid = sid;
	पूर्ण अन्यथा अगर (!म_भेद(name, "fscreate")) अणु
		tsec->create_sid = sid;
	पूर्ण अन्यथा अगर (!म_भेद(name, "keycreate")) अणु
		अगर (sid) अणु
			error = avc_has_perm(&selinux_state, mysid, sid,
					     SECCLASS_KEY, KEY__CREATE, शून्य);
			अगर (error)
				जाओ पात_change;
		पूर्ण
		tsec->keycreate_sid = sid;
	पूर्ण अन्यथा अगर (!म_भेद(name, "sockcreate")) अणु
		tsec->sockcreate_sid = sid;
	पूर्ण अन्यथा अगर (!म_भेद(name, "current")) अणु
		error = -EINVAL;
		अगर (sid == 0)
			जाओ पात_change;

		/* Only allow single thपढ़ोed processes to change context */
		error = -EPERM;
		अगर (!current_is_single_thपढ़ोed()) अणु
			error = security_bounded_transition(&selinux_state,
							    tsec->sid, sid);
			अगर (error)
				जाओ पात_change;
		पूर्ण

		/* Check permissions क्रम the transition. */
		error = avc_has_perm(&selinux_state,
				     tsec->sid, sid, SECCLASS_PROCESS,
				     PROCESS__DYNTRANSITION, शून्य);
		अगर (error)
			जाओ पात_change;

		/* Check क्रम ptracing, and update the task SID अगर ok.
		   Otherwise, leave SID unchanged and fail. */
		ptsid = ptrace_parent_sid();
		अगर (ptsid != 0) अणु
			error = avc_has_perm(&selinux_state,
					     ptsid, sid, SECCLASS_PROCESS,
					     PROCESS__PTRACE, शून्य);
			अगर (error)
				जाओ पात_change;
		पूर्ण

		tsec->sid = sid;
	पूर्ण अन्यथा अणु
		error = -EINVAL;
		जाओ पात_change;
	पूर्ण

	commit_creds(new);
	वापस size;

पात_change:
	पात_creds(new);
	वापस error;
पूर्ण

अटल पूर्णांक selinux_ismaclabel(स्थिर अक्षर *name)
अणु
	वापस (म_भेद(name, XATTR_SELINUX_SUFFIX) == 0);
पूर्ण

अटल पूर्णांक selinux_secid_to_secctx(u32 secid, अक्षर **secdata, u32 *seclen)
अणु
	वापस security_sid_to_context(&selinux_state, secid,
				       secdata, seclen);
पूर्ण

अटल पूर्णांक selinux_secctx_to_secid(स्थिर अक्षर *secdata, u32 seclen, u32 *secid)
अणु
	वापस security_context_to_sid(&selinux_state, secdata, seclen,
				       secid, GFP_KERNEL);
पूर्ण

अटल व्योम selinux_release_secctx(अक्षर *secdata, u32 seclen)
अणु
	kमुक्त(secdata);
पूर्ण

अटल व्योम selinux_inode_invalidate_secctx(काष्ठा inode *inode)
अणु
	काष्ठा inode_security_काष्ठा *isec = selinux_inode(inode);

	spin_lock(&isec->lock);
	isec->initialized = LABEL_INVALID;
	spin_unlock(&isec->lock);
पूर्ण

/*
 *	called with inode->i_mutex locked
 */
अटल पूर्णांक selinux_inode_notअगरysecctx(काष्ठा inode *inode, व्योम *ctx, u32 ctxlen)
अणु
	पूर्णांक rc = selinux_inode_setsecurity(inode, XATTR_SELINUX_SUFFIX,
					   ctx, ctxlen, 0);
	/* Do not वापस error when suppressing label (SBLABEL_MNT not set). */
	वापस rc == -EOPNOTSUPP ? 0 : rc;
पूर्ण

/*
 *	called with inode->i_mutex locked
 */
अटल पूर्णांक selinux_inode_setsecctx(काष्ठा dentry *dentry, व्योम *ctx, u32 ctxlen)
अणु
	वापस __vfs_setxattr_noperm(&init_user_ns, dentry, XATTR_NAME_SELINUX,
				     ctx, ctxlen, 0);
पूर्ण

अटल पूर्णांक selinux_inode_माला_लोecctx(काष्ठा inode *inode, व्योम **ctx, u32 *ctxlen)
अणु
	पूर्णांक len = 0;
	len = selinux_inode_माला_लोecurity(&init_user_ns, inode,
					XATTR_SELINUX_SUFFIX, ctx, true);
	अगर (len < 0)
		वापस len;
	*ctxlen = len;
	वापस 0;
पूर्ण
#अगर_घोषित CONFIG_KEYS

अटल पूर्णांक selinux_key_alloc(काष्ठा key *k, स्थिर काष्ठा cred *cred,
			     अचिन्हित दीर्घ flags)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec;
	काष्ठा key_security_काष्ठा *ksec;

	ksec = kzalloc(माप(काष्ठा key_security_काष्ठा), GFP_KERNEL);
	अगर (!ksec)
		वापस -ENOMEM;

	tsec = selinux_cred(cred);
	अगर (tsec->keycreate_sid)
		ksec->sid = tsec->keycreate_sid;
	अन्यथा
		ksec->sid = tsec->sid;

	k->security = ksec;
	वापस 0;
पूर्ण

अटल व्योम selinux_key_मुक्त(काष्ठा key *k)
अणु
	काष्ठा key_security_काष्ठा *ksec = k->security;

	k->security = शून्य;
	kमुक्त(ksec);
पूर्ण

अटल पूर्णांक selinux_key_permission(key_ref_t key_ref,
				  स्थिर काष्ठा cred *cred,
				  क्रमागत key_need_perm need_perm)
अणु
	काष्ठा key *key;
	काष्ठा key_security_काष्ठा *ksec;
	u32 perm, sid;

	चयन (need_perm) अणु
	हाल KEY_NEED_VIEW:
		perm = KEY__VIEW;
		अवरोध;
	हाल KEY_NEED_READ:
		perm = KEY__READ;
		अवरोध;
	हाल KEY_NEED_WRITE:
		perm = KEY__WRITE;
		अवरोध;
	हाल KEY_NEED_SEARCH:
		perm = KEY__SEARCH;
		अवरोध;
	हाल KEY_NEED_LINK:
		perm = KEY__LINK;
		अवरोध;
	हाल KEY_NEED_SETATTR:
		perm = KEY__SETATTR;
		अवरोध;
	हाल KEY_NEED_UNLINK:
	हाल KEY_SYSADMIN_OVERRIDE:
	हाल KEY_AUTHTOKEN_OVERRIDE:
	हाल KEY_DEFER_PERM_CHECK:
		वापस 0;
	शेष:
		WARN_ON(1);
		वापस -EPERM;

	पूर्ण

	sid = cred_sid(cred);
	key = key_ref_to_ptr(key_ref);
	ksec = key->security;

	वापस avc_has_perm(&selinux_state,
			    sid, ksec->sid, SECCLASS_KEY, perm, शून्य);
पूर्ण

अटल पूर्णांक selinux_key_माला_लोecurity(काष्ठा key *key, अक्षर **_buffer)
अणु
	काष्ठा key_security_काष्ठा *ksec = key->security;
	अक्षर *context = शून्य;
	अचिन्हित len;
	पूर्णांक rc;

	rc = security_sid_to_context(&selinux_state, ksec->sid,
				     &context, &len);
	अगर (!rc)
		rc = len;
	*_buffer = context;
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_KEY_NOTIFICATIONS
अटल पूर्णांक selinux_watch_key(काष्ठा key *key)
अणु
	काष्ठा key_security_काष्ठा *ksec = key->security;
	u32 sid = current_sid();

	वापस avc_has_perm(&selinux_state,
			    sid, ksec->sid, SECCLASS_KEY, KEY__VIEW, शून्य);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY_INFINIBAND
अटल पूर्णांक selinux_ib_pkey_access(व्योम *ib_sec, u64 subnet_prefix, u16 pkey_val)
अणु
	काष्ठा common_audit_data ad;
	पूर्णांक err;
	u32 sid = 0;
	काष्ठा ib_security_काष्ठा *sec = ib_sec;
	काष्ठा lsm_ibpkey_audit ibpkey;

	err = sel_ib_pkey_sid(subnet_prefix, pkey_val, &sid);
	अगर (err)
		वापस err;

	ad.type = LSM_AUDIT_DATA_IBPKEY;
	ibpkey.subnet_prefix = subnet_prefix;
	ibpkey.pkey = pkey_val;
	ad.u.ibpkey = &ibpkey;
	वापस avc_has_perm(&selinux_state,
			    sec->sid, sid,
			    SECCLASS_INFINIBAND_PKEY,
			    INFINIBAND_PKEY__ACCESS, &ad);
पूर्ण

अटल पूर्णांक selinux_ib_endport_manage_subnet(व्योम *ib_sec, स्थिर अक्षर *dev_name,
					    u8 port_num)
अणु
	काष्ठा common_audit_data ad;
	पूर्णांक err;
	u32 sid = 0;
	काष्ठा ib_security_काष्ठा *sec = ib_sec;
	काष्ठा lsm_ibendport_audit ibendport;

	err = security_ib_endport_sid(&selinux_state, dev_name, port_num,
				      &sid);

	अगर (err)
		वापस err;

	ad.type = LSM_AUDIT_DATA_IBENDPORT;
	म_नकलन(ibendport.dev_name, dev_name, माप(ibendport.dev_name));
	ibendport.port = port_num;
	ad.u.ibendport = &ibendport;
	वापस avc_has_perm(&selinux_state,
			    sec->sid, sid,
			    SECCLASS_INFINIBAND_ENDPORT,
			    INFINIBAND_ENDPORT__MANAGE_SUBNET, &ad);
पूर्ण

अटल पूर्णांक selinux_ib_alloc_security(व्योम **ib_sec)
अणु
	काष्ठा ib_security_काष्ठा *sec;

	sec = kzalloc(माप(*sec), GFP_KERNEL);
	अगर (!sec)
		वापस -ENOMEM;
	sec->sid = current_sid();

	*ib_sec = sec;
	वापस 0;
पूर्ण

अटल व्योम selinux_ib_मुक्त_security(व्योम *ib_sec)
अणु
	kमुक्त(ib_sec);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BPF_SYSCALL
अटल पूर्णांक selinux_bpf(पूर्णांक cmd, जोड़ bpf_attr *attr,
				     अचिन्हित पूर्णांक size)
अणु
	u32 sid = current_sid();
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल BPF_MAP_CREATE:
		ret = avc_has_perm(&selinux_state,
				   sid, sid, SECCLASS_BPF, BPF__MAP_CREATE,
				   शून्य);
		अवरोध;
	हाल BPF_PROG_LOAD:
		ret = avc_has_perm(&selinux_state,
				   sid, sid, SECCLASS_BPF, BPF__PROG_LOAD,
				   शून्य);
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 bpf_map_भ_शेषe_to_av(भ_शेषe_t भ_शेषe)
अणु
	u32 av = 0;

	अगर (भ_शेषe & FMODE_READ)
		av |= BPF__MAP_READ;
	अगर (भ_शेषe & FMODE_WRITE)
		av |= BPF__MAP_WRITE;
	वापस av;
पूर्ण

/* This function will check the file pass through unix socket or binder to see
 * अगर it is a bpf related object. And apply correspinding checks on the bpf
 * object based on the type. The bpf maps and programs, not like other files and
 * socket, are using a shared anonymous inode inside the kernel as their inode.
 * So checking that inode cannot identअगरy अगर the process have privilege to
 * access the bpf object and that's why we have to add this additional check in
 * selinux_file_receive and selinux_binder_transfer_files.
 */
अटल पूर्णांक bpf_fd_pass(काष्ठा file *file, u32 sid)
अणु
	काष्ठा bpf_security_काष्ठा *bpfsec;
	काष्ठा bpf_prog *prog;
	काष्ठा bpf_map *map;
	पूर्णांक ret;

	अगर (file->f_op == &bpf_map_fops) अणु
		map = file->निजी_data;
		bpfsec = map->security;
		ret = avc_has_perm(&selinux_state,
				   sid, bpfsec->sid, SECCLASS_BPF,
				   bpf_map_भ_शेषe_to_av(file->f_mode), शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (file->f_op == &bpf_prog_fops) अणु
		prog = file->निजी_data;
		bpfsec = prog->aux->security;
		ret = avc_has_perm(&selinux_state,
				   sid, bpfsec->sid, SECCLASS_BPF,
				   BPF__PROG_RUN, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक selinux_bpf_map(काष्ठा bpf_map *map, भ_शेषe_t भ_शेषe)
अणु
	u32 sid = current_sid();
	काष्ठा bpf_security_काष्ठा *bpfsec;

	bpfsec = map->security;
	वापस avc_has_perm(&selinux_state,
			    sid, bpfsec->sid, SECCLASS_BPF,
			    bpf_map_भ_शेषe_to_av(भ_शेषe), शून्य);
पूर्ण

अटल पूर्णांक selinux_bpf_prog(काष्ठा bpf_prog *prog)
अणु
	u32 sid = current_sid();
	काष्ठा bpf_security_काष्ठा *bpfsec;

	bpfsec = prog->aux->security;
	वापस avc_has_perm(&selinux_state,
			    sid, bpfsec->sid, SECCLASS_BPF,
			    BPF__PROG_RUN, शून्य);
पूर्ण

अटल पूर्णांक selinux_bpf_map_alloc(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_security_काष्ठा *bpfsec;

	bpfsec = kzalloc(माप(*bpfsec), GFP_KERNEL);
	अगर (!bpfsec)
		वापस -ENOMEM;

	bpfsec->sid = current_sid();
	map->security = bpfsec;

	वापस 0;
पूर्ण

अटल व्योम selinux_bpf_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_security_काष्ठा *bpfsec = map->security;

	map->security = शून्य;
	kमुक्त(bpfsec);
पूर्ण

अटल पूर्णांक selinux_bpf_prog_alloc(काष्ठा bpf_prog_aux *aux)
अणु
	काष्ठा bpf_security_काष्ठा *bpfsec;

	bpfsec = kzalloc(माप(*bpfsec), GFP_KERNEL);
	अगर (!bpfsec)
		वापस -ENOMEM;

	bpfsec->sid = current_sid();
	aux->security = bpfsec;

	वापस 0;
पूर्ण

अटल व्योम selinux_bpf_prog_मुक्त(काष्ठा bpf_prog_aux *aux)
अणु
	काष्ठा bpf_security_काष्ठा *bpfsec = aux->security;

	aux->security = शून्य;
	kमुक्त(bpfsec);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक selinux_lockकरोwn(क्रमागत lockकरोwn_reason what)
अणु
	काष्ठा common_audit_data ad;
	u32 sid = current_sid();
	पूर्णांक invalid_reason = (what <= LOCKDOWN_NONE) ||
			     (what == LOCKDOWN_INTEGRITY_MAX) ||
			     (what >= LOCKDOWN_CONFIDENTIALITY_MAX);

	अगर (WARN(invalid_reason, "Invalid lockdown reason")) अणु
		audit_log(audit_context(),
			  GFP_ATOMIC, AUDIT_SELINUX_ERR,
			  "lockdown_reason=invalid");
		वापस -EINVAL;
	पूर्ण

	ad.type = LSM_AUDIT_DATA_LOCKDOWN;
	ad.u.reason = what;

	अगर (what <= LOCKDOWN_INTEGRITY_MAX)
		वापस avc_has_perm(&selinux_state,
				    sid, sid, SECCLASS_LOCKDOWN,
				    LOCKDOWN__INTEGRITY, &ad);
	अन्यथा
		वापस avc_has_perm(&selinux_state,
				    sid, sid, SECCLASS_LOCKDOWN,
				    LOCKDOWN__CONFIDENTIALITY, &ad);
पूर्ण

काष्ठा lsm_blob_sizes selinux_blob_sizes __lsm_ro_after_init = अणु
	.lbs_cred = माप(काष्ठा task_security_काष्ठा),
	.lbs_file = माप(काष्ठा file_security_काष्ठा),
	.lbs_inode = माप(काष्ठा inode_security_काष्ठा),
	.lbs_ipc = माप(काष्ठा ipc_security_काष्ठा),
	.lbs_msg_msg = माप(काष्ठा msg_security_काष्ठा),
	.lbs_superblock = माप(काष्ठा superblock_security_काष्ठा),
पूर्ण;

#अगर_घोषित CONFIG_PERF_EVENTS
अटल पूर्णांक selinux_perf_event_खोलो(काष्ठा perf_event_attr *attr, पूर्णांक type)
अणु
	u32 requested, sid = current_sid();

	अगर (type == PERF_SECURITY_OPEN)
		requested = PERF_EVENT__OPEN;
	अन्यथा अगर (type == PERF_SECURITY_CPU)
		requested = PERF_EVENT__CPU;
	अन्यथा अगर (type == PERF_SECURITY_KERNEL)
		requested = PERF_EVENT__KERNEL;
	अन्यथा अगर (type == PERF_SECURITY_TRACEPOINT)
		requested = PERF_EVENT__TRACEPOINT;
	अन्यथा
		वापस -EINVAL;

	वापस avc_has_perm(&selinux_state, sid, sid, SECCLASS_PERF_EVENT,
			    requested, शून्य);
पूर्ण

अटल पूर्णांक selinux_perf_event_alloc(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_security_काष्ठा *perfsec;

	perfsec = kzalloc(माप(*perfsec), GFP_KERNEL);
	अगर (!perfsec)
		वापस -ENOMEM;

	perfsec->sid = current_sid();
	event->security = perfsec;

	वापस 0;
पूर्ण

अटल व्योम selinux_perf_event_मुक्त(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_security_काष्ठा *perfsec = event->security;

	event->security = शून्य;
	kमुक्त(perfsec);
पूर्ण

अटल पूर्णांक selinux_perf_event_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_security_काष्ठा *perfsec = event->security;
	u32 sid = current_sid();

	वापस avc_has_perm(&selinux_state, sid, perfsec->sid,
			    SECCLASS_PERF_EVENT, PERF_EVENT__READ, शून्य);
पूर्ण

अटल पूर्णांक selinux_perf_event_ग_लिखो(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_security_काष्ठा *perfsec = event->security;
	u32 sid = current_sid();

	वापस avc_has_perm(&selinux_state, sid, perfsec->sid,
			    SECCLASS_PERF_EVENT, PERF_EVENT__WRITE, शून्य);
पूर्ण
#पूर्ण_अगर

/*
 * IMPORTANT NOTE: When adding new hooks, please be careful to keep this order:
 * 1. any hooks that करोn't beदीर्घ to (2.) or (3.) below,
 * 2. hooks that both access काष्ठाures allocated by other hooks, and allocate
 *    काष्ठाures that can be later accessed by other hooks (mostly "cloning"
 *    hooks),
 * 3. hooks that only allocate काष्ठाures that can be later accessed by other
 *    hooks ("allocating" hooks).
 *
 * Please follow block comment delimiters in the list to keep this order.
 *
 * This ordering is needed क्रम SELinux runसमय disable to work at least somewhat
 * safely. Breaking the ordering rules above might lead to शून्य poपूर्णांकer derefs
 * when disabling SELinux at runसमय.
 */
अटल काष्ठा security_hook_list selinux_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(binder_set_context_mgr, selinux_binder_set_context_mgr),
	LSM_HOOK_INIT(binder_transaction, selinux_binder_transaction),
	LSM_HOOK_INIT(binder_transfer_binder, selinux_binder_transfer_binder),
	LSM_HOOK_INIT(binder_transfer_file, selinux_binder_transfer_file),

	LSM_HOOK_INIT(ptrace_access_check, selinux_ptrace_access_check),
	LSM_HOOK_INIT(ptrace_traceme, selinux_ptrace_traceme),
	LSM_HOOK_INIT(capget, selinux_capget),
	LSM_HOOK_INIT(capset, selinux_capset),
	LSM_HOOK_INIT(capable, selinux_capable),
	LSM_HOOK_INIT(quotactl, selinux_quotactl),
	LSM_HOOK_INIT(quota_on, selinux_quota_on),
	LSM_HOOK_INIT(syslog, selinux_syslog),
	LSM_HOOK_INIT(vm_enough_memory, selinux_vm_enough_memory),

	LSM_HOOK_INIT(netlink_send, selinux_netlink_send),

	LSM_HOOK_INIT(bprm_creds_क्रम_exec, selinux_bprm_creds_क्रम_exec),
	LSM_HOOK_INIT(bprm_committing_creds, selinux_bprm_committing_creds),
	LSM_HOOK_INIT(bprm_committed_creds, selinux_bprm_committed_creds),

	LSM_HOOK_INIT(sb_मुक्त_mnt_opts, selinux_मुक्त_mnt_opts),
	LSM_HOOK_INIT(sb_mnt_opts_compat, selinux_sb_mnt_opts_compat),
	LSM_HOOK_INIT(sb_remount, selinux_sb_remount),
	LSM_HOOK_INIT(sb_kern_mount, selinux_sb_kern_mount),
	LSM_HOOK_INIT(sb_show_options, selinux_sb_show_options),
	LSM_HOOK_INIT(sb_statfs, selinux_sb_statfs),
	LSM_HOOK_INIT(sb_mount, selinux_mount),
	LSM_HOOK_INIT(sb_umount, selinux_umount),
	LSM_HOOK_INIT(sb_set_mnt_opts, selinux_set_mnt_opts),
	LSM_HOOK_INIT(sb_clone_mnt_opts, selinux_sb_clone_mnt_opts),

	LSM_HOOK_INIT(move_mount, selinux_move_mount),

	LSM_HOOK_INIT(dentry_init_security, selinux_dentry_init_security),
	LSM_HOOK_INIT(dentry_create_files_as, selinux_dentry_create_files_as),

	LSM_HOOK_INIT(inode_मुक्त_security, selinux_inode_मुक्त_security),
	LSM_HOOK_INIT(inode_init_security, selinux_inode_init_security),
	LSM_HOOK_INIT(inode_init_security_anon, selinux_inode_init_security_anon),
	LSM_HOOK_INIT(inode_create, selinux_inode_create),
	LSM_HOOK_INIT(inode_link, selinux_inode_link),
	LSM_HOOK_INIT(inode_unlink, selinux_inode_unlink),
	LSM_HOOK_INIT(inode_symlink, selinux_inode_symlink),
	LSM_HOOK_INIT(inode_सूची_गढ़ो, selinux_inode_सूची_गढ़ो),
	LSM_HOOK_INIT(inode_सूची_हटाओ, selinux_inode_सूची_हटाओ),
	LSM_HOOK_INIT(inode_mknod, selinux_inode_mknod),
	LSM_HOOK_INIT(inode_नाम, selinux_inode_नाम),
	LSM_HOOK_INIT(inode_पढ़ोlink, selinux_inode_पढ़ोlink),
	LSM_HOOK_INIT(inode_follow_link, selinux_inode_follow_link),
	LSM_HOOK_INIT(inode_permission, selinux_inode_permission),
	LSM_HOOK_INIT(inode_setattr, selinux_inode_setattr),
	LSM_HOOK_INIT(inode_getattr, selinux_inode_getattr),
	LSM_HOOK_INIT(inode_setxattr, selinux_inode_setxattr),
	LSM_HOOK_INIT(inode_post_setxattr, selinux_inode_post_setxattr),
	LSM_HOOK_INIT(inode_getxattr, selinux_inode_getxattr),
	LSM_HOOK_INIT(inode_listxattr, selinux_inode_listxattr),
	LSM_HOOK_INIT(inode_हटाओxattr, selinux_inode_हटाओxattr),
	LSM_HOOK_INIT(inode_माला_लोecurity, selinux_inode_माला_लोecurity),
	LSM_HOOK_INIT(inode_setsecurity, selinux_inode_setsecurity),
	LSM_HOOK_INIT(inode_listsecurity, selinux_inode_listsecurity),
	LSM_HOOK_INIT(inode_माला_लोecid, selinux_inode_माला_लोecid),
	LSM_HOOK_INIT(inode_copy_up, selinux_inode_copy_up),
	LSM_HOOK_INIT(inode_copy_up_xattr, selinux_inode_copy_up_xattr),
	LSM_HOOK_INIT(path_notअगरy, selinux_path_notअगरy),

	LSM_HOOK_INIT(kernfs_init_security, selinux_kernfs_init_security),

	LSM_HOOK_INIT(file_permission, selinux_file_permission),
	LSM_HOOK_INIT(file_alloc_security, selinux_file_alloc_security),
	LSM_HOOK_INIT(file_ioctl, selinux_file_ioctl),
	LSM_HOOK_INIT(mmap_file, selinux_mmap_file),
	LSM_HOOK_INIT(mmap_addr, selinux_mmap_addr),
	LSM_HOOK_INIT(file_mprotect, selinux_file_mprotect),
	LSM_HOOK_INIT(file_lock, selinux_file_lock),
	LSM_HOOK_INIT(file_fcntl, selinux_file_fcntl),
	LSM_HOOK_INIT(file_set_fowner, selinux_file_set_fowner),
	LSM_HOOK_INIT(file_send_sigiotask, selinux_file_send_sigiotask),
	LSM_HOOK_INIT(file_receive, selinux_file_receive),

	LSM_HOOK_INIT(file_खोलो, selinux_file_खोलो),

	LSM_HOOK_INIT(task_alloc, selinux_task_alloc),
	LSM_HOOK_INIT(cred_prepare, selinux_cred_prepare),
	LSM_HOOK_INIT(cred_transfer, selinux_cred_transfer),
	LSM_HOOK_INIT(cred_माला_लोecid, selinux_cred_माला_लोecid),
	LSM_HOOK_INIT(kernel_act_as, selinux_kernel_act_as),
	LSM_HOOK_INIT(kernel_create_files_as, selinux_kernel_create_files_as),
	LSM_HOOK_INIT(kernel_module_request, selinux_kernel_module_request),
	LSM_HOOK_INIT(kernel_load_data, selinux_kernel_load_data),
	LSM_HOOK_INIT(kernel_पढ़ो_file, selinux_kernel_पढ़ो_file),
	LSM_HOOK_INIT(task_setpgid, selinux_task_setpgid),
	LSM_HOOK_INIT(task_getpgid, selinux_task_getpgid),
	LSM_HOOK_INIT(task_माला_लोid, selinux_task_माला_लोid),
	LSM_HOOK_INIT(task_माला_लोecid_subj, selinux_task_माला_लोecid_subj),
	LSM_HOOK_INIT(task_माला_लोecid_obj, selinux_task_माला_लोecid_obj),
	LSM_HOOK_INIT(task_setnice, selinux_task_setnice),
	LSM_HOOK_INIT(task_setioprio, selinux_task_setioprio),
	LSM_HOOK_INIT(task_getioprio, selinux_task_getioprio),
	LSM_HOOK_INIT(task_prlimit, selinux_task_prlimit),
	LSM_HOOK_INIT(task_setrlimit, selinux_task_setrlimit),
	LSM_HOOK_INIT(task_setscheduler, selinux_task_setscheduler),
	LSM_HOOK_INIT(task_माला_लोcheduler, selinux_task_माला_लोcheduler),
	LSM_HOOK_INIT(task_movememory, selinux_task_movememory),
	LSM_HOOK_INIT(task_समाप्त, selinux_task_समाप्त),
	LSM_HOOK_INIT(task_to_inode, selinux_task_to_inode),

	LSM_HOOK_INIT(ipc_permission, selinux_ipc_permission),
	LSM_HOOK_INIT(ipc_माला_लोecid, selinux_ipc_माला_लोecid),

	LSM_HOOK_INIT(msg_queue_associate, selinux_msg_queue_associate),
	LSM_HOOK_INIT(msg_queue_msgctl, selinux_msg_queue_msgctl),
	LSM_HOOK_INIT(msg_queue_msgsnd, selinux_msg_queue_msgsnd),
	LSM_HOOK_INIT(msg_queue_msgrcv, selinux_msg_queue_msgrcv),

	LSM_HOOK_INIT(shm_associate, selinux_shm_associate),
	LSM_HOOK_INIT(shm_shmctl, selinux_shm_shmctl),
	LSM_HOOK_INIT(shm_shmat, selinux_shm_shmat),

	LSM_HOOK_INIT(sem_associate, selinux_sem_associate),
	LSM_HOOK_INIT(sem_semctl, selinux_sem_semctl),
	LSM_HOOK_INIT(sem_semop, selinux_sem_semop),

	LSM_HOOK_INIT(d_instantiate, selinux_d_instantiate),

	LSM_HOOK_INIT(getprocattr, selinux_getprocattr),
	LSM_HOOK_INIT(setprocattr, selinux_setprocattr),

	LSM_HOOK_INIT(ismaclabel, selinux_ismaclabel),
	LSM_HOOK_INIT(secctx_to_secid, selinux_secctx_to_secid),
	LSM_HOOK_INIT(release_secctx, selinux_release_secctx),
	LSM_HOOK_INIT(inode_invalidate_secctx, selinux_inode_invalidate_secctx),
	LSM_HOOK_INIT(inode_notअगरysecctx, selinux_inode_notअगरysecctx),
	LSM_HOOK_INIT(inode_setsecctx, selinux_inode_setsecctx),

	LSM_HOOK_INIT(unix_stream_connect, selinux_socket_unix_stream_connect),
	LSM_HOOK_INIT(unix_may_send, selinux_socket_unix_may_send),

	LSM_HOOK_INIT(socket_create, selinux_socket_create),
	LSM_HOOK_INIT(socket_post_create, selinux_socket_post_create),
	LSM_HOOK_INIT(socket_socketpair, selinux_socket_socketpair),
	LSM_HOOK_INIT(socket_bind, selinux_socket_bind),
	LSM_HOOK_INIT(socket_connect, selinux_socket_connect),
	LSM_HOOK_INIT(socket_listen, selinux_socket_listen),
	LSM_HOOK_INIT(socket_accept, selinux_socket_accept),
	LSM_HOOK_INIT(socket_sendmsg, selinux_socket_sendmsg),
	LSM_HOOK_INIT(socket_recvmsg, selinux_socket_recvmsg),
	LSM_HOOK_INIT(socket_माला_लोockname, selinux_socket_माला_लोockname),
	LSM_HOOK_INIT(socket_getpeername, selinux_socket_getpeername),
	LSM_HOOK_INIT(socket_माला_लोockopt, selinux_socket_माला_लोockopt),
	LSM_HOOK_INIT(socket_setsockopt, selinux_socket_setsockopt),
	LSM_HOOK_INIT(socket_shutकरोwn, selinux_socket_shutकरोwn),
	LSM_HOOK_INIT(socket_sock_rcv_skb, selinux_socket_sock_rcv_skb),
	LSM_HOOK_INIT(socket_getpeersec_stream,
			selinux_socket_getpeersec_stream),
	LSM_HOOK_INIT(socket_getpeersec_dgram, selinux_socket_getpeersec_dgram),
	LSM_HOOK_INIT(sk_मुक्त_security, selinux_sk_मुक्त_security),
	LSM_HOOK_INIT(sk_clone_security, selinux_sk_clone_security),
	LSM_HOOK_INIT(sk_माला_लोecid, selinux_sk_माला_लोecid),
	LSM_HOOK_INIT(sock_graft, selinux_sock_graft),
	LSM_HOOK_INIT(sctp_assoc_request, selinux_sctp_assoc_request),
	LSM_HOOK_INIT(sctp_sk_clone, selinux_sctp_sk_clone),
	LSM_HOOK_INIT(sctp_bind_connect, selinux_sctp_bind_connect),
	LSM_HOOK_INIT(inet_conn_request, selinux_inet_conn_request),
	LSM_HOOK_INIT(inet_csk_clone, selinux_inet_csk_clone),
	LSM_HOOK_INIT(inet_conn_established, selinux_inet_conn_established),
	LSM_HOOK_INIT(secmark_relabel_packet, selinux_secmark_relabel_packet),
	LSM_HOOK_INIT(secmark_refcount_inc, selinux_secmark_refcount_inc),
	LSM_HOOK_INIT(secmark_refcount_dec, selinux_secmark_refcount_dec),
	LSM_HOOK_INIT(req_classअगरy_flow, selinux_req_classअगरy_flow),
	LSM_HOOK_INIT(tun_dev_मुक्त_security, selinux_tun_dev_मुक्त_security),
	LSM_HOOK_INIT(tun_dev_create, selinux_tun_dev_create),
	LSM_HOOK_INIT(tun_dev_attach_queue, selinux_tun_dev_attach_queue),
	LSM_HOOK_INIT(tun_dev_attach, selinux_tun_dev_attach),
	LSM_HOOK_INIT(tun_dev_खोलो, selinux_tun_dev_खोलो),
#अगर_घोषित CONFIG_SECURITY_INFINIBAND
	LSM_HOOK_INIT(ib_pkey_access, selinux_ib_pkey_access),
	LSM_HOOK_INIT(ib_endport_manage_subnet,
		      selinux_ib_endport_manage_subnet),
	LSM_HOOK_INIT(ib_मुक्त_security, selinux_ib_मुक्त_security),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY_NETWORK_XFRM
	LSM_HOOK_INIT(xfrm_policy_मुक्त_security, selinux_xfrm_policy_मुक्त),
	LSM_HOOK_INIT(xfrm_policy_delete_security, selinux_xfrm_policy_delete),
	LSM_HOOK_INIT(xfrm_state_मुक्त_security, selinux_xfrm_state_मुक्त),
	LSM_HOOK_INIT(xfrm_state_delete_security, selinux_xfrm_state_delete),
	LSM_HOOK_INIT(xfrm_policy_lookup, selinux_xfrm_policy_lookup),
	LSM_HOOK_INIT(xfrm_state_pol_flow_match,
			selinux_xfrm_state_pol_flow_match),
	LSM_HOOK_INIT(xfrm_decode_session, selinux_xfrm_decode_session),
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEYS
	LSM_HOOK_INIT(key_मुक्त, selinux_key_मुक्त),
	LSM_HOOK_INIT(key_permission, selinux_key_permission),
	LSM_HOOK_INIT(key_माला_लोecurity, selinux_key_माला_लोecurity),
#अगर_घोषित CONFIG_KEY_NOTIFICATIONS
	LSM_HOOK_INIT(watch_key, selinux_watch_key),
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_AUDIT
	LSM_HOOK_INIT(audit_rule_known, selinux_audit_rule_known),
	LSM_HOOK_INIT(audit_rule_match, selinux_audit_rule_match),
	LSM_HOOK_INIT(audit_rule_मुक्त, selinux_audit_rule_मुक्त),
#पूर्ण_अगर

#अगर_घोषित CONFIG_BPF_SYSCALL
	LSM_HOOK_INIT(bpf, selinux_bpf),
	LSM_HOOK_INIT(bpf_map, selinux_bpf_map),
	LSM_HOOK_INIT(bpf_prog, selinux_bpf_prog),
	LSM_HOOK_INIT(bpf_map_मुक्त_security, selinux_bpf_map_मुक्त),
	LSM_HOOK_INIT(bpf_prog_मुक्त_security, selinux_bpf_prog_मुक्त),
#पूर्ण_अगर

#अगर_घोषित CONFIG_PERF_EVENTS
	LSM_HOOK_INIT(perf_event_खोलो, selinux_perf_event_खोलो),
	LSM_HOOK_INIT(perf_event_मुक्त, selinux_perf_event_मुक्त),
	LSM_HOOK_INIT(perf_event_पढ़ो, selinux_perf_event_पढ़ो),
	LSM_HOOK_INIT(perf_event_ग_लिखो, selinux_perf_event_ग_लिखो),
#पूर्ण_अगर

	LSM_HOOK_INIT(locked_करोwn, selinux_lockकरोwn),

	/*
	 * PUT "CLONING" (ACCESSING + ALLOCATING) HOOKS HERE
	 */
	LSM_HOOK_INIT(fs_context_dup, selinux_fs_context_dup),
	LSM_HOOK_INIT(fs_context_parse_param, selinux_fs_context_parse_param),
	LSM_HOOK_INIT(sb_eat_lsm_opts, selinux_sb_eat_lsm_opts),
	LSM_HOOK_INIT(sb_add_mnt_opt, selinux_add_mnt_opt),
#अगर_घोषित CONFIG_SECURITY_NETWORK_XFRM
	LSM_HOOK_INIT(xfrm_policy_clone_security, selinux_xfrm_policy_clone),
#पूर्ण_अगर

	/*
	 * PUT "ALLOCATING" HOOKS HERE
	 */
	LSM_HOOK_INIT(msg_msg_alloc_security, selinux_msg_msg_alloc_security),
	LSM_HOOK_INIT(msg_queue_alloc_security,
		      selinux_msg_queue_alloc_security),
	LSM_HOOK_INIT(shm_alloc_security, selinux_shm_alloc_security),
	LSM_HOOK_INIT(sb_alloc_security, selinux_sb_alloc_security),
	LSM_HOOK_INIT(inode_alloc_security, selinux_inode_alloc_security),
	LSM_HOOK_INIT(sem_alloc_security, selinux_sem_alloc_security),
	LSM_HOOK_INIT(secid_to_secctx, selinux_secid_to_secctx),
	LSM_HOOK_INIT(inode_माला_लोecctx, selinux_inode_माला_लोecctx),
	LSM_HOOK_INIT(sk_alloc_security, selinux_sk_alloc_security),
	LSM_HOOK_INIT(tun_dev_alloc_security, selinux_tun_dev_alloc_security),
#अगर_घोषित CONFIG_SECURITY_INFINIBAND
	LSM_HOOK_INIT(ib_alloc_security, selinux_ib_alloc_security),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY_NETWORK_XFRM
	LSM_HOOK_INIT(xfrm_policy_alloc_security, selinux_xfrm_policy_alloc),
	LSM_HOOK_INIT(xfrm_state_alloc, selinux_xfrm_state_alloc),
	LSM_HOOK_INIT(xfrm_state_alloc_acquire,
		      selinux_xfrm_state_alloc_acquire),
#पूर्ण_अगर
#अगर_घोषित CONFIG_KEYS
	LSM_HOOK_INIT(key_alloc, selinux_key_alloc),
#पूर्ण_अगर
#अगर_घोषित CONFIG_AUDIT
	LSM_HOOK_INIT(audit_rule_init, selinux_audit_rule_init),
#पूर्ण_अगर
#अगर_घोषित CONFIG_BPF_SYSCALL
	LSM_HOOK_INIT(bpf_map_alloc_security, selinux_bpf_map_alloc),
	LSM_HOOK_INIT(bpf_prog_alloc_security, selinux_bpf_prog_alloc),
#पूर्ण_अगर
#अगर_घोषित CONFIG_PERF_EVENTS
	LSM_HOOK_INIT(perf_event_alloc, selinux_perf_event_alloc),
#पूर्ण_अगर
पूर्ण;

अटल __init पूर्णांक selinux_init(व्योम)
अणु
	pr_info("SELinux:  Initializing.\n");

	स_रखो(&selinux_state, 0, माप(selinux_state));
	enक्रमcing_set(&selinux_state, selinux_enक्रमcing_boot);
	checkreqprot_set(&selinux_state, selinux_checkreqprot_boot);
	selinux_avc_init(&selinux_state.avc);
	mutex_init(&selinux_state.status_lock);
	mutex_init(&selinux_state.policy_mutex);

	/* Set the security state क्रम the initial task. */
	cred_init_security();

	शेष_noexec = !(VM_DATA_DEFAULT_FLAGS & VM_EXEC);

	avc_init();

	avtab_cache_init();

	ebiपंचांगap_cache_init();

	hashtab_cache_init();

	security_add_hooks(selinux_hooks, ARRAY_SIZE(selinux_hooks), "selinux");

	अगर (avc_add_callback(selinux_netcache_avc_callback, AVC_CALLBACK_RESET))
		panic("SELinux: Unable to register AVC netcache callback\n");

	अगर (avc_add_callback(selinux_lsm_notअगरier_avc_callback, AVC_CALLBACK_RESET))
		panic("SELinux: Unable to register AVC LSM notifier callback\n");

	अगर (selinux_enक्रमcing_boot)
		pr_debug("SELinux:  Starting in enforcing mode\n");
	अन्यथा
		pr_debug("SELinux:  Starting in permissive mode\n");

	fs_validate_description("selinux", selinux_fs_parameters);

	वापस 0;
पूर्ण

अटल व्योम delayed_superblock_init(काष्ठा super_block *sb, व्योम *unused)
अणु
	selinux_set_mnt_opts(sb, शून्य, 0, शून्य);
पूर्ण

व्योम selinux_complete_init(व्योम)
अणु
	pr_debug("SELinux:  Completing initialization.\n");

	/* Set up any superblocks initialized prior to the policy load. */
	pr_debug("SELinux:  Setting up existing superblocks.\n");
	iterate_supers(delayed_superblock_init, शून्य);
पूर्ण

/* SELinux requires early initialization in order to label
   all processes and objects when they are created. */
DEFINE_LSM(selinux) = अणु
	.name = "selinux",
	.flags = LSM_FLAG_LEGACY_MAJOR | LSM_FLAG_EXCLUSIVE,
	.enabled = &selinux_enabled_boot,
	.blobs = &selinux_blob_sizes,
	.init = selinux_init,
पूर्ण;

#अगर defined(CONFIG_NETFILTER)

अटल स्थिर काष्ठा nf_hook_ops selinux_nf_ops[] = अणु
	अणु
		.hook =		selinux_ipv4_postroute,
		.pf =		NFPROTO_IPV4,
		.hooknum =	NF_INET_POST_ROUTING,
		.priority =	NF_IP_PRI_SELINUX_LAST,
	पूर्ण,
	अणु
		.hook =		selinux_ipv4_क्रमward,
		.pf =		NFPROTO_IPV4,
		.hooknum =	NF_INET_FORWARD,
		.priority =	NF_IP_PRI_SELINUX_FIRST,
	पूर्ण,
	अणु
		.hook =		selinux_ipv4_output,
		.pf =		NFPROTO_IPV4,
		.hooknum =	NF_INET_LOCAL_OUT,
		.priority =	NF_IP_PRI_SELINUX_FIRST,
	पूर्ण,
#अगर IS_ENABLED(CONFIG_IPV6)
	अणु
		.hook =		selinux_ipv6_postroute,
		.pf =		NFPROTO_IPV6,
		.hooknum =	NF_INET_POST_ROUTING,
		.priority =	NF_IP6_PRI_SELINUX_LAST,
	पूर्ण,
	अणु
		.hook =		selinux_ipv6_क्रमward,
		.pf =		NFPROTO_IPV6,
		.hooknum =	NF_INET_FORWARD,
		.priority =	NF_IP6_PRI_SELINUX_FIRST,
	पूर्ण,
	अणु
		.hook =		selinux_ipv6_output,
		.pf =		NFPROTO_IPV6,
		.hooknum =	NF_INET_LOCAL_OUT,
		.priority =	NF_IP6_PRI_SELINUX_FIRST,
	पूर्ण,
#पूर्ण_अगर	/* IPV6 */
पूर्ण;

अटल पूर्णांक __net_init selinux_nf_रेजिस्टर(काष्ठा net *net)
अणु
	वापस nf_रेजिस्टर_net_hooks(net, selinux_nf_ops,
				     ARRAY_SIZE(selinux_nf_ops));
पूर्ण

अटल व्योम __net_निकास selinux_nf_unरेजिस्टर(काष्ठा net *net)
अणु
	nf_unरेजिस्टर_net_hooks(net, selinux_nf_ops,
				ARRAY_SIZE(selinux_nf_ops));
पूर्ण

अटल काष्ठा pernet_operations selinux_net_ops = अणु
	.init = selinux_nf_रेजिस्टर,
	.निकास = selinux_nf_unरेजिस्टर,
पूर्ण;

अटल पूर्णांक __init selinux_nf_ip_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!selinux_enabled_boot)
		वापस 0;

	pr_debug("SELinux:  Registering netfilter hooks\n");

	err = रेजिस्टर_pernet_subsys(&selinux_net_ops);
	अगर (err)
		panic("SELinux: register_pernet_subsys: error %d\n", err);

	वापस 0;
पूर्ण
__initcall(selinux_nf_ip_init);

#अगर_घोषित CONFIG_SECURITY_SELINUX_DISABLE
अटल व्योम selinux_nf_ip_निकास(व्योम)
अणु
	pr_debug("SELinux:  Unregistering netfilter hooks\n");

	unरेजिस्टर_pernet_subsys(&selinux_net_ops);
पूर्ण
#पूर्ण_अगर

#अन्यथा /* CONFIG_NETFILTER */

#अगर_घोषित CONFIG_SECURITY_SELINUX_DISABLE
#घोषणा selinux_nf_ip_निकास()
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_NETFILTER */

#अगर_घोषित CONFIG_SECURITY_SELINUX_DISABLE
पूर्णांक selinux_disable(काष्ठा selinux_state *state)
अणु
	अगर (selinux_initialized(state)) अणु
		/* Not permitted after initial policy load. */
		वापस -EINVAL;
	पूर्ण

	अगर (selinux_disabled(state)) अणु
		/* Only करो this once. */
		वापस -EINVAL;
	पूर्ण

	selinux_mark_disabled(state);

	pr_info("SELinux:  Disabled at runtime.\n");

	/*
	 * Unरेजिस्टर netfilter hooks.
	 * Must be करोne beक्रमe security_delete_hooks() to aव्योम अवरोधing
	 * runसमय disable.
	 */
	selinux_nf_ip_निकास();

	security_delete_hooks(selinux_hooks, ARRAY_SIZE(selinux_hooks));

	/* Try to destroy the avc node cache */
	avc_disable();

	/* Unरेजिस्टर selinuxfs. */
	निकास_sel_fs();

	वापस 0;
पूर्ण
#पूर्ण_अगर
