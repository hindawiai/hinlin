<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Common capabilities, needed by capability.o.
 */

#समावेश <linux/capability.h>
#समावेश <linux/audit.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/file.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netlink.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/xattr.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/mount.h>
#समावेश <linux/sched.h>
#समावेश <linux/prctl.h>
#समावेश <linux/securebits.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/personality.h>

/*
 * If a non-root user executes a setuid-root binary in
 * !secure(SECURE_NOROOT) mode, then we उठाओ capabilities.
 * However अगर fE is also set, then the पूर्णांकent is क्रम only
 * the file capabilities to be applied, and the setuid-root
 * bit is left on either to change the uid (plausible) or
 * to get full privilege on a kernel without file capabilities
 * support.  So in that हाल we करो not उठाओ capabilities.
 *
 * Warn अगर that happens, once per boot.
 */
अटल व्योम warn_setuid_and_fcaps_mixed(स्थिर अक्षर *fname)
अणु
	अटल पूर्णांक warned;
	अगर (!warned) अणु
		prपूर्णांकk(KERN_INFO "warning: `%s' has both setuid-root and"
			" effective capabilities. Therefore not raising all"
			" capabilities.\n", fname);
		warned = 1;
	पूर्ण
पूर्ण

/**
 * cap_capable - Determine whether a task has a particular effective capability
 * @cred: The credentials to use
 * @targ_ns:  The user namespace in which we need the capability
 * @cap: The capability to check क्रम
 * @opts: Biपंचांगask of options defined in include/linux/security.h
 *
 * Determine whether the nominated task has the specअगरied capability amongst
 * its effective set, वापसing 0 अगर it करोes, -ve अगर it करोes not.
 *
 * NOTE WELL: cap_has_capability() cannot be used like the kernel's capable()
 * and has_capability() functions.  That is, it has the reverse semantics:
 * cap_has_capability() वापसs 0 when a task has a capability, but the
 * kernel's capable() and has_capability() वापसs 1 क्रम this हाल.
 */
पूर्णांक cap_capable(स्थिर काष्ठा cred *cred, काष्ठा user_namespace *targ_ns,
		पूर्णांक cap, अचिन्हित पूर्णांक opts)
अणु
	काष्ठा user_namespace *ns = targ_ns;

	/* See अगर cred has the capability in the target user namespace
	 * by examining the target user namespace and all of the target
	 * user namespace's parents.
	 */
	क्रम (;;) अणु
		/* Do we have the necessary capabilities? */
		अगर (ns == cred->user_ns)
			वापस cap_उठाओd(cred->cap_effective, cap) ? 0 : -EPERM;

		/*
		 * If we're already at a lower level than we're looking क्रम,
		 * we're करोne searching.
		 */
		अगर (ns->level <= cred->user_ns->level)
			वापस -EPERM;

		/* 
		 * The owner of the user namespace in the parent of the
		 * user namespace has all caps.
		 */
		अगर ((ns->parent == cred->user_ns) && uid_eq(ns->owner, cred->euid))
			वापस 0;

		/*
		 * If you have a capability in a parent user ns, then you have
		 * it over all children user namespaces as well.
		 */
		ns = ns->parent;
	पूर्ण

	/* We never get here */
पूर्ण

/**
 * cap_समय_रखो - Determine whether the current process may set the प्रणाली घड़ी
 * @ts: The समय to set
 * @tz: The समयzone to set
 *
 * Determine whether the current process may set the प्रणाली घड़ी and समयzone
 * inक्रमmation, वापसing 0 अगर permission granted, -ve अगर denied.
 */
पूर्णांक cap_समय_रखो(स्थिर काष्ठा बारpec64 *ts, स्थिर काष्ठा समयzone *tz)
अणु
	अगर (!capable(CAP_SYS_TIME))
		वापस -EPERM;
	वापस 0;
पूर्ण

/**
 * cap_ptrace_access_check - Determine whether the current process may access
 *			   another
 * @child: The process to be accessed
 * @mode: The mode of attachment.
 *
 * If we are in the same or an ancestor user_ns and have all the target
 * task's capabilities, then ptrace access is allowed.
 * If we have the ptrace capability to the target user_ns, then ptrace
 * access is allowed.
 * Else denied.
 *
 * Determine whether a process may access another, वापसing 0 अगर permission
 * granted, -ve अगर denied.
 */
पूर्णांक cap_ptrace_access_check(काष्ठा task_काष्ठा *child, अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा cred *cred, *child_cred;
	स्थिर kernel_cap_t *caller_caps;

	rcu_पढ़ो_lock();
	cred = current_cred();
	child_cred = __task_cred(child);
	अगर (mode & PTRACE_MODE_FSCREDS)
		caller_caps = &cred->cap_effective;
	अन्यथा
		caller_caps = &cred->cap_permitted;
	अगर (cred->user_ns == child_cred->user_ns &&
	    cap_issubset(child_cred->cap_permitted, *caller_caps))
		जाओ out;
	अगर (ns_capable(child_cred->user_ns, CAP_SYS_PTRACE))
		जाओ out;
	ret = -EPERM;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * cap_ptrace_traceme - Determine whether another process may trace the current
 * @parent: The task proposed to be the tracer
 *
 * If parent is in the same or an ancestor user_ns and has all current's
 * capabilities, then ptrace access is allowed.
 * If parent has the ptrace capability to current's user_ns, then ptrace
 * access is allowed.
 * Else denied.
 *
 * Determine whether the nominated task is permitted to trace the current
 * process, वापसing 0 अगर permission is granted, -ve अगर denied.
 */
पूर्णांक cap_ptrace_traceme(काष्ठा task_काष्ठा *parent)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा cred *cred, *child_cred;

	rcu_पढ़ो_lock();
	cred = __task_cred(parent);
	child_cred = current_cred();
	अगर (cred->user_ns == child_cred->user_ns &&
	    cap_issubset(child_cred->cap_permitted, cred->cap_permitted))
		जाओ out;
	अगर (has_ns_capability(parent, child_cred->user_ns, CAP_SYS_PTRACE))
		जाओ out;
	ret = -EPERM;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * cap_capget - Retrieve a task's capability sets
 * @target: The task from which to retrieve the capability sets
 * @effective: The place to record the effective set
 * @inheritable: The place to record the inheritable set
 * @permitted: The place to record the permitted set
 *
 * This function retrieves the capabilities of the nominated task and वापसs
 * them to the caller.
 */
पूर्णांक cap_capget(काष्ठा task_काष्ठा *target, kernel_cap_t *effective,
	       kernel_cap_t *inheritable, kernel_cap_t *permitted)
अणु
	स्थिर काष्ठा cred *cred;

	/* Derived from kernel/capability.c:sys_capget. */
	rcu_पढ़ो_lock();
	cred = __task_cred(target);
	*effective   = cred->cap_effective;
	*inheritable = cred->cap_inheritable;
	*permitted   = cred->cap_permitted;
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

/*
 * Determine whether the inheritable capabilities are limited to the old
 * permitted set.  Returns 1 अगर they are limited, 0 अगर they are not.
 */
अटल अंतरभूत पूर्णांक cap_inh_is_capped(व्योम)
अणु
	/* they are so limited unless the current task has the CAP_SETPCAP
	 * capability
	 */
	अगर (cap_capable(current_cred(), current_cred()->user_ns,
			CAP_SETPCAP, CAP_OPT_NONE) == 0)
		वापस 0;
	वापस 1;
पूर्ण

/**
 * cap_capset - Validate and apply proposed changes to current's capabilities
 * @new: The proposed new credentials; alterations should be made here
 * @old: The current task's current credentials
 * @effective: A poपूर्णांकer to the proposed new effective capabilities set
 * @inheritable: A poपूर्णांकer to the proposed new inheritable capabilities set
 * @permitted: A poपूर्णांकer to the proposed new permitted capabilities set
 *
 * This function validates and applies a proposed mass change to the current
 * process's capability sets.  The changes are made to the proposed new
 * credentials, and assuming no error, will be committed by the caller of LSM.
 */
पूर्णांक cap_capset(काष्ठा cred *new,
	       स्थिर काष्ठा cred *old,
	       स्थिर kernel_cap_t *effective,
	       स्थिर kernel_cap_t *inheritable,
	       स्थिर kernel_cap_t *permitted)
अणु
	अगर (cap_inh_is_capped() &&
	    !cap_issubset(*inheritable,
			  cap_combine(old->cap_inheritable,
				      old->cap_permitted)))
		/* incapable of using this inheritable set */
		वापस -EPERM;

	अगर (!cap_issubset(*inheritable,
			  cap_combine(old->cap_inheritable,
				      old->cap_bset)))
		/* no new pI capabilities outside bounding set */
		वापस -EPERM;

	/* verअगरy restrictions on target's new Permitted set */
	अगर (!cap_issubset(*permitted, old->cap_permitted))
		वापस -EPERM;

	/* verअगरy the _new_Effective_ is a subset of the _new_Permitted_ */
	अगर (!cap_issubset(*effective, *permitted))
		वापस -EPERM;

	new->cap_effective   = *effective;
	new->cap_inheritable = *inheritable;
	new->cap_permitted   = *permitted;

	/*
	 * Mask off ambient bits that are no दीर्घer both permitted and
	 * inheritable.
	 */
	new->cap_ambient = cap_पूर्णांकersect(new->cap_ambient,
					 cap_पूर्णांकersect(*permitted,
						       *inheritable));
	अगर (WARN_ON(!cap_ambient_invariant_ok(new)))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 * cap_inode_need_समाप्तpriv - Determine अगर inode change affects privileges
 * @dentry: The inode/dentry in being changed with change marked ATTR_KILL_PRIV
 *
 * Determine अगर an inode having a change applied that's marked ATTR_KILL_PRIV
 * affects the security markings on that inode, and अगर it is, should
 * inode_समाप्तpriv() be invoked or the change rejected.
 *
 * Return: 1 अगर security.capability has a value, meaning inode_समाप्तpriv()
 * is required, 0 otherwise, meaning inode_समाप्तpriv() is not required.
 */
पूर्णांक cap_inode_need_समाप्तpriv(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);
	पूर्णांक error;

	error = __vfs_getxattr(dentry, inode, XATTR_NAME_CAPS, शून्य, 0);
	वापस error > 0;
पूर्ण

/**
 * cap_inode_समाप्तpriv - Erase the security markings on an inode
 *
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dentry:	The inode/dentry to alter
 *
 * Erase the privilege-enhancing security markings on an inode.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 *
 * Return: 0 अगर successful, -ve on error.
 */
पूर्णांक cap_inode_समाप्तpriv(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry)
अणु
	पूर्णांक error;

	error = __vfs_हटाओxattr(mnt_userns, dentry, XATTR_NAME_CAPS);
	अगर (error == -EOPNOTSUPP)
		error = 0;
	वापस error;
पूर्ण

अटल bool rootid_owns_currentns(kuid_t kroot)
अणु
	काष्ठा user_namespace *ns;

	अगर (!uid_valid(kroot))
		वापस false;

	क्रम (ns = current_user_ns(); ; ns = ns->parent) अणु
		अगर (from_kuid(ns, kroot) == 0)
			वापस true;
		अगर (ns == &init_user_ns)
			अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल __u32 sansflags(__u32 m)
अणु
	वापस m & ~VFS_CAP_FLAGS_EFFECTIVE;
पूर्ण

अटल bool is_v2header(माप_प्रकार size, स्थिर काष्ठा vfs_cap_data *cap)
अणु
	अगर (size != XATTR_CAPS_SZ_2)
		वापस false;
	वापस sansflags(le32_to_cpu(cap->magic_etc)) == VFS_CAP_REVISION_2;
पूर्ण

अटल bool is_v3header(माप_प्रकार size, स्थिर काष्ठा vfs_cap_data *cap)
अणु
	अगर (size != XATTR_CAPS_SZ_3)
		वापस false;
	वापस sansflags(le32_to_cpu(cap->magic_etc)) == VFS_CAP_REVISION_3;
पूर्ण

/*
 * माला_लोecurity: We are called क्रम security.* beक्रमe any attempt to पढ़ो the
 * xattr from the inode itself.
 *
 * This gives us a chance to पढ़ो the on-disk value and convert it.  If we
 * वापस -EOPNOTSUPP, then vfs_getxattr() will call the i_op handler.
 *
 * Note we are not called by vfs_getxattr_alloc(), but that is only called
 * by the पूर्णांकegrity subप्रणाली, which really wants the unconverted values -
 * so that's good.
 */
पूर्णांक cap_inode_माला_लोecurity(काष्ठा user_namespace *mnt_userns,
			  काष्ठा inode *inode, स्थिर अक्षर *name, व्योम **buffer,
			  bool alloc)
अणु
	पूर्णांक size, ret;
	kuid_t kroot;
	u32 nsmagic, magic;
	uid_t root, mappedroot;
	अक्षर *पंचांगpbuf = शून्य;
	काष्ठा vfs_cap_data *cap;
	काष्ठा vfs_ns_cap_data *nscap = शून्य;
	काष्ठा dentry *dentry;
	काष्ठा user_namespace *fs_ns;

	अगर (म_भेद(name, "capability") != 0)
		वापस -EOPNOTSUPP;

	dentry = d_find_any_alias(inode);
	अगर (!dentry)
		वापस -EINVAL;

	size = माप(काष्ठा vfs_ns_cap_data);
	ret = (पूर्णांक)vfs_getxattr_alloc(mnt_userns, dentry, XATTR_NAME_CAPS,
				      &पंचांगpbuf, size, GFP_NOFS);
	dput(dentry);

	अगर (ret < 0 || !पंचांगpbuf)
		वापस ret;

	fs_ns = inode->i_sb->s_user_ns;
	cap = (काष्ठा vfs_cap_data *) पंचांगpbuf;
	अगर (is_v2header((माप_प्रकार) ret, cap)) अणु
		root = 0;
	पूर्ण अन्यथा अगर (is_v3header((माप_प्रकार) ret, cap)) अणु
		nscap = (काष्ठा vfs_ns_cap_data *) पंचांगpbuf;
		root = le32_to_cpu(nscap->rootid);
	पूर्ण अन्यथा अणु
		size = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	kroot = make_kuid(fs_ns, root);

	/* If this is an idmapped mount shअगरt the kuid. */
	kroot = kuid_पूर्णांकo_mnt(mnt_userns, kroot);

	/* If the root kuid maps to a valid uid in current ns, then वापस
	 * this as a nscap. */
	mappedroot = from_kuid(current_user_ns(), kroot);
	अगर (mappedroot != (uid_t)-1 && mappedroot != (uid_t)0) अणु
		size = माप(काष्ठा vfs_ns_cap_data);
		अगर (alloc) अणु
			अगर (!nscap) अणु
				/* v2 -> v3 conversion */
				nscap = kzalloc(size, GFP_ATOMIC);
				अगर (!nscap) अणु
					size = -ENOMEM;
					जाओ out_मुक्त;
				पूर्ण
				nsmagic = VFS_CAP_REVISION_3;
				magic = le32_to_cpu(cap->magic_etc);
				अगर (magic & VFS_CAP_FLAGS_EFFECTIVE)
					nsmagic |= VFS_CAP_FLAGS_EFFECTIVE;
				स_नकल(&nscap->data, &cap->data, माप(__le32) * 2 * VFS_CAP_U32);
				nscap->magic_etc = cpu_to_le32(nsmagic);
			पूर्ण अन्यथा अणु
				/* use allocated v3 buffer */
				पंचांगpbuf = शून्य;
			पूर्ण
			nscap->rootid = cpu_to_le32(mappedroot);
			*buffer = nscap;
		पूर्ण
		जाओ out_मुक्त;
	पूर्ण

	अगर (!rootid_owns_currentns(kroot)) अणु
		size = -EOVERFLOW;
		जाओ out_मुक्त;
	पूर्ण

	/* This comes from a parent namespace.  Return as a v2 capability */
	size = माप(काष्ठा vfs_cap_data);
	अगर (alloc) अणु
		अगर (nscap) अणु
			/* v3 -> v2 conversion */
			cap = kzalloc(size, GFP_ATOMIC);
			अगर (!cap) अणु
				size = -ENOMEM;
				जाओ out_मुक्त;
			पूर्ण
			magic = VFS_CAP_REVISION_2;
			nsmagic = le32_to_cpu(nscap->magic_etc);
			अगर (nsmagic & VFS_CAP_FLAGS_EFFECTIVE)
				magic |= VFS_CAP_FLAGS_EFFECTIVE;
			स_नकल(&cap->data, &nscap->data, माप(__le32) * 2 * VFS_CAP_U32);
			cap->magic_etc = cpu_to_le32(magic);
		पूर्ण अन्यथा अणु
			/* use unconverted v2 */
			पंचांगpbuf = शून्य;
		पूर्ण
		*buffer = cap;
	पूर्ण
out_मुक्त:
	kमुक्त(पंचांगpbuf);
	वापस size;
पूर्ण

/**
 * rootid_from_xattr - translate root uid of vfs caps
 *
 * @value:	vfs caps value which may be modअगरied by this function
 * @size:	size of @ivalue
 * @task_ns:	user namespace of the caller
 * @mnt_userns:	user namespace of the mount the inode was found from
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 */
अटल kuid_t rootid_from_xattr(स्थिर व्योम *value, माप_प्रकार size,
				काष्ठा user_namespace *task_ns,
				काष्ठा user_namespace *mnt_userns)
अणु
	स्थिर काष्ठा vfs_ns_cap_data *nscap = value;
	kuid_t rootkid;
	uid_t rootid = 0;

	अगर (size == XATTR_CAPS_SZ_3)
		rootid = le32_to_cpu(nscap->rootid);

	rootkid = make_kuid(task_ns, rootid);
	वापस kuid_from_mnt(mnt_userns, rootkid);
पूर्ण

अटल bool validheader(माप_प्रकार size, स्थिर काष्ठा vfs_cap_data *cap)
अणु
	वापस is_v2header(size, cap) || is_v3header(size, cap);
पूर्ण

/**
 * cap_convert_nscap - check vfs caps
 *
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dentry:	used to retrieve inode to check permissions on
 * @ivalue:	vfs caps value which may be modअगरied by this function
 * @size:	size of @ivalue
 *
 * User requested a ग_लिखो of security.capability.  If needed, update the
 * xattr to change from v2 to v3, or to fixup the v3 rootid.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 *
 * Return: On success, वापस the new size; on error, वापस < 0.
 */
पूर्णांक cap_convert_nscap(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		      स्थिर व्योम **ivalue, माप_प्रकार size)
अणु
	काष्ठा vfs_ns_cap_data *nscap;
	uid_t nsrootid;
	स्थिर काष्ठा vfs_cap_data *cap = *ivalue;
	__u32 magic, nsmagic;
	काष्ठा inode *inode = d_backing_inode(dentry);
	काष्ठा user_namespace *task_ns = current_user_ns(),
		*fs_ns = inode->i_sb->s_user_ns;
	kuid_t rootid;
	माप_प्रकार newsize;

	अगर (!*ivalue)
		वापस -EINVAL;
	अगर (!validheader(size, cap))
		वापस -EINVAL;
	अगर (!capable_wrt_inode_uidgid(mnt_userns, inode, CAP_SETFCAP))
		वापस -EPERM;
	अगर (size == XATTR_CAPS_SZ_2 && (mnt_userns == &init_user_ns))
		अगर (ns_capable(inode->i_sb->s_user_ns, CAP_SETFCAP))
			/* user is privileged, just ग_लिखो the v2 */
			वापस size;

	rootid = rootid_from_xattr(*ivalue, size, task_ns, mnt_userns);
	अगर (!uid_valid(rootid))
		वापस -EINVAL;

	nsrootid = from_kuid(fs_ns, rootid);
	अगर (nsrootid == -1)
		वापस -EINVAL;

	newsize = माप(काष्ठा vfs_ns_cap_data);
	nscap = kदो_स्मृति(newsize, GFP_ATOMIC);
	अगर (!nscap)
		वापस -ENOMEM;
	nscap->rootid = cpu_to_le32(nsrootid);
	nsmagic = VFS_CAP_REVISION_3;
	magic = le32_to_cpu(cap->magic_etc);
	अगर (magic & VFS_CAP_FLAGS_EFFECTIVE)
		nsmagic |= VFS_CAP_FLAGS_EFFECTIVE;
	nscap->magic_etc = cpu_to_le32(nsmagic);
	स_नकल(&nscap->data, &cap->data, माप(__le32) * 2 * VFS_CAP_U32);

	*ivalue = nscap;
	वापस newsize;
पूर्ण

/*
 * Calculate the new process capability sets from the capability sets attached
 * to a file.
 */
अटल अंतरभूत पूर्णांक bprm_caps_from_vfs_caps(काष्ठा cpu_vfs_cap_data *caps,
					  काष्ठा linux_binprm *bprm,
					  bool *effective,
					  bool *has_fcap)
अणु
	काष्ठा cred *new = bprm->cred;
	अचिन्हित i;
	पूर्णांक ret = 0;

	अगर (caps->magic_etc & VFS_CAP_FLAGS_EFFECTIVE)
		*effective = true;

	अगर (caps->magic_etc & VFS_CAP_REVISION_MASK)
		*has_fcap = true;

	CAP_FOR_EACH_U32(i) अणु
		__u32 permitted = caps->permitted.cap[i];
		__u32 inheritable = caps->inheritable.cap[i];

		/*
		 * pP' = (X & fP) | (pI & fI)
		 * The addition of pA' is handled later.
		 */
		new->cap_permitted.cap[i] =
			(new->cap_bset.cap[i] & permitted) |
			(new->cap_inheritable.cap[i] & inheritable);

		अगर (permitted & ~new->cap_permitted.cap[i])
			/* insufficient to execute correctly */
			ret = -EPERM;
	पूर्ण

	/*
	 * For legacy apps, with no पूर्णांकernal support क्रम recognizing they
	 * करो not have enough capabilities, we वापस an error अगर they are
	 * missing some "forced" (aka file-permitted) capabilities.
	 */
	वापस *effective ? ret : 0;
पूर्ण

/**
 * get_vfs_caps_from_disk - retrieve vfs caps from disk
 *
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dentry:	dentry from which @inode is retrieved
 * @cpu_caps:	vfs capabilities
 *
 * Extract the on-exec-apply capability sets क्रम an executable file.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 */
पूर्णांक get_vfs_caps_from_disk(काष्ठा user_namespace *mnt_userns,
			   स्थिर काष्ठा dentry *dentry,
			   काष्ठा cpu_vfs_cap_data *cpu_caps)
अणु
	काष्ठा inode *inode = d_backing_inode(dentry);
	__u32 magic_etc;
	अचिन्हित tocopy, i;
	पूर्णांक size;
	काष्ठा vfs_ns_cap_data data, *nscaps = &data;
	काष्ठा vfs_cap_data *caps = (काष्ठा vfs_cap_data *) &data;
	kuid_t rootkuid;
	काष्ठा user_namespace *fs_ns;

	स_रखो(cpu_caps, 0, माप(काष्ठा cpu_vfs_cap_data));

	अगर (!inode)
		वापस -ENODATA;

	fs_ns = inode->i_sb->s_user_ns;
	size = __vfs_getxattr((काष्ठा dentry *)dentry, inode,
			      XATTR_NAME_CAPS, &data, XATTR_CAPS_SZ);
	अगर (size == -ENODATA || size == -EOPNOTSUPP)
		/* no data, that's ok */
		वापस -ENODATA;

	अगर (size < 0)
		वापस size;

	अगर (size < माप(magic_etc))
		वापस -EINVAL;

	cpu_caps->magic_etc = magic_etc = le32_to_cpu(caps->magic_etc);

	rootkuid = make_kuid(fs_ns, 0);
	चयन (magic_etc & VFS_CAP_REVISION_MASK) अणु
	हाल VFS_CAP_REVISION_1:
		अगर (size != XATTR_CAPS_SZ_1)
			वापस -EINVAL;
		tocopy = VFS_CAP_U32_1;
		अवरोध;
	हाल VFS_CAP_REVISION_2:
		अगर (size != XATTR_CAPS_SZ_2)
			वापस -EINVAL;
		tocopy = VFS_CAP_U32_2;
		अवरोध;
	हाल VFS_CAP_REVISION_3:
		अगर (size != XATTR_CAPS_SZ_3)
			वापस -EINVAL;
		tocopy = VFS_CAP_U32_3;
		rootkuid = make_kuid(fs_ns, le32_to_cpu(nscaps->rootid));
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	/* Limit the caps to the mounter of the fileप्रणाली
	 * or the more limited uid specअगरied in the xattr.
	 */
	rootkuid = kuid_पूर्णांकo_mnt(mnt_userns, rootkuid);
	अगर (!rootid_owns_currentns(rootkuid))
		वापस -ENODATA;

	CAP_FOR_EACH_U32(i) अणु
		अगर (i >= tocopy)
			अवरोध;
		cpu_caps->permitted.cap[i] = le32_to_cpu(caps->data[i].permitted);
		cpu_caps->inheritable.cap[i] = le32_to_cpu(caps->data[i].inheritable);
	पूर्ण

	cpu_caps->permitted.cap[CAP_LAST_U32] &= CAP_LAST_U32_VALID_MASK;
	cpu_caps->inheritable.cap[CAP_LAST_U32] &= CAP_LAST_U32_VALID_MASK;

	cpu_caps->rootid = rootkuid;

	वापस 0;
पूर्ण

/*
 * Attempt to get the on-exec apply capability sets क्रम an executable file from
 * its xattrs and, अगर present, apply them to the proposed credentials being
 * स्थिरructed by execve().
 */
अटल पूर्णांक get_file_caps(काष्ठा linux_binprm *bprm, काष्ठा file *file,
			 bool *effective, bool *has_fcap)
अणु
	पूर्णांक rc = 0;
	काष्ठा cpu_vfs_cap_data vcaps;

	cap_clear(bprm->cred->cap_permitted);

	अगर (!file_caps_enabled)
		वापस 0;

	अगर (!mnt_may_suid(file->f_path.mnt))
		वापस 0;

	/*
	 * This check is redundant with mnt_may_suid() but is kept to make
	 * explicit that capability bits are limited to s_user_ns and its
	 * descendants.
	 */
	अगर (!current_in_userns(file->f_path.mnt->mnt_sb->s_user_ns))
		वापस 0;

	rc = get_vfs_caps_from_disk(file_mnt_user_ns(file),
				    file->f_path.dentry, &vcaps);
	अगर (rc < 0) अणु
		अगर (rc == -EINVAL)
			prपूर्णांकk(KERN_NOTICE "Invalid argument reading file caps for %s\n",
					bprm->filename);
		अन्यथा अगर (rc == -ENODATA)
			rc = 0;
		जाओ out;
	पूर्ण

	rc = bprm_caps_from_vfs_caps(&vcaps, bprm, effective, has_fcap);

out:
	अगर (rc)
		cap_clear(bprm->cred->cap_permitted);

	वापस rc;
पूर्ण

अटल अंतरभूत bool root_privileged(व्योम) अणु वापस !issecure(SECURE_NOROOT); पूर्ण

अटल अंतरभूत bool __is_real(kuid_t uid, काष्ठा cred *cred)
अणु वापस uid_eq(cred->uid, uid); पूर्ण

अटल अंतरभूत bool __is_eff(kuid_t uid, काष्ठा cred *cred)
अणु वापस uid_eq(cred->euid, uid); पूर्ण

अटल अंतरभूत bool __is_suid(kuid_t uid, काष्ठा cred *cred)
अणु वापस !__is_real(uid, cred) && __is_eff(uid, cred); पूर्ण

/*
 * handle_privileged_root - Handle हाल of privileged root
 * @bprm: The execution parameters, including the proposed creds
 * @has_fcap: Are any file capabilities set?
 * @effective: Do we have effective root privilege?
 * @root_uid: This namespace' root UID WRT initial USER namespace
 *
 * Handle the हाल where root is privileged and hasn't been neutered by
 * SECURE_NOROOT.  If file capabilities are set, they won't be combined with
 * set UID root and nothing is changed.  If we are root, cap_permitted is
 * updated.  If we have become set UID root, the effective bit is set.
 */
अटल व्योम handle_privileged_root(काष्ठा linux_binprm *bprm, bool has_fcap,
				   bool *effective, kuid_t root_uid)
अणु
	स्थिर काष्ठा cred *old = current_cred();
	काष्ठा cred *new = bprm->cred;

	अगर (!root_privileged())
		वापस;
	/*
	 * If the legacy file capability is set, then करोn't set privs
	 * क्रम a setuid root binary run by a non-root user.  Do set it
	 * क्रम a root user just to cause least surprise to an admin.
	 */
	अगर (has_fcap && __is_suid(root_uid, new)) अणु
		warn_setuid_and_fcaps_mixed(bprm->filename);
		वापस;
	पूर्ण
	/*
	 * To support inheritance of root-permissions and suid-root
	 * executables under compatibility mode, we override the
	 * capability sets क्रम the file.
	 */
	अगर (__is_eff(root_uid, new) || __is_real(root_uid, new)) अणु
		/* pP' = (cap_bset & ~0) | (pI & ~0) */
		new->cap_permitted = cap_combine(old->cap_bset,
						 old->cap_inheritable);
	पूर्ण
	/*
	 * If only the real uid is 0, we करो not set the effective bit.
	 */
	अगर (__is_eff(root_uid, new))
		*effective = true;
पूर्ण

#घोषणा __cap_gained(field, target, source) \
	!cap_issubset(target->cap_##field, source->cap_##field)
#घोषणा __cap_grew(target, source, cred) \
	!cap_issubset(cred->cap_##target, cred->cap_##source)
#घोषणा __cap_full(field, cred) \
	cap_issubset(CAP_FULL_SET, cred->cap_##field)

अटल अंतरभूत bool __is_setuid(काष्ठा cred *new, स्थिर काष्ठा cred *old)
अणु वापस !uid_eq(new->euid, old->uid); पूर्ण

अटल अंतरभूत bool __is_setgid(काष्ठा cred *new, स्थिर काष्ठा cred *old)
अणु वापस !gid_eq(new->egid, old->gid); पूर्ण

/*
 * 1) Audit candidate अगर current->cap_effective is set
 *
 * We करो not bother to audit अगर 3 things are true:
 *   1) cap_effective has all caps
 *   2) we became root *OR* are were alपढ़ोy root
 *   3) root is supposed to have all caps (SECURE_NOROOT)
 * Since this is just a normal root execing a process.
 *
 * Number 1 above might fail अगर you करोn't have a full bset, but I think
 * that is पूर्णांकeresting inक्रमmation to audit.
 *
 * A number of other conditions require logging:
 * 2) something prevented setuid root getting all caps
 * 3) non-setuid root माला_लो fcaps
 * 4) non-setuid root माला_लो ambient
 */
अटल अंतरभूत bool nonroot_उठाओd_pE(काष्ठा cred *new, स्थिर काष्ठा cred *old,
				     kuid_t root, bool has_fcap)
अणु
	bool ret = false;

	अगर ((__cap_grew(effective, ambient, new) &&
	     !(__cap_full(effective, new) &&
	       (__is_eff(root, new) || __is_real(root, new)) &&
	       root_privileged())) ||
	    (root_privileged() &&
	     __is_suid(root, new) &&
	     !__cap_full(effective, new)) ||
	    (!__is_setuid(new, old) &&
	     ((has_fcap &&
	       __cap_gained(permitted, new, old)) ||
	      __cap_gained(ambient, new, old))))

		ret = true;

	वापस ret;
पूर्ण

/**
 * cap_bprm_creds_from_file - Set up the proposed credentials क्रम execve().
 * @bprm: The execution parameters, including the proposed creds
 * @file: The file to pull the credentials from
 *
 * Set up the proposed credentials क्रम a new execution context being
 * स्थिरructed by execve().  The proposed creds in @bprm->cred is altered,
 * which won't take effect immediately.
 *
 * Return: 0 अगर successful, -ve on error.
 */
पूर्णांक cap_bprm_creds_from_file(काष्ठा linux_binprm *bprm, काष्ठा file *file)
अणु
	/* Process setpcap binaries and capabilities क्रम uid 0 */
	स्थिर काष्ठा cred *old = current_cred();
	काष्ठा cred *new = bprm->cred;
	bool effective = false, has_fcap = false, is_setid;
	पूर्णांक ret;
	kuid_t root_uid;

	अगर (WARN_ON(!cap_ambient_invariant_ok(old)))
		वापस -EPERM;

	ret = get_file_caps(bprm, file, &effective, &has_fcap);
	अगर (ret < 0)
		वापस ret;

	root_uid = make_kuid(new->user_ns, 0);

	handle_privileged_root(bprm, has_fcap, &effective, root_uid);

	/* अगर we have fs caps, clear dangerous personality flags */
	अगर (__cap_gained(permitted, new, old))
		bprm->per_clear |= PER_CLEAR_ON_SETID;

	/* Don't let someone trace a set[ug]id/setpcap binary with the revised
	 * credentials unless they have the appropriate permit.
	 *
	 * In addition, अगर NO_NEW_PRIVS, then ensure we get no new privs.
	 */
	is_setid = __is_setuid(new, old) || __is_setgid(new, old);

	अगर ((is_setid || __cap_gained(permitted, new, old)) &&
	    ((bprm->unsafe & ~LSM_UNSAFE_PTRACE) ||
	     !ptracer_capable(current, new->user_ns))) अणु
		/* करोwngrade; they get no more than they had, and maybe less */
		अगर (!ns_capable(new->user_ns, CAP_SETUID) ||
		    (bprm->unsafe & LSM_UNSAFE_NO_NEW_PRIVS)) अणु
			new->euid = new->uid;
			new->egid = new->gid;
		पूर्ण
		new->cap_permitted = cap_पूर्णांकersect(new->cap_permitted,
						   old->cap_permitted);
	पूर्ण

	new->suid = new->fsuid = new->euid;
	new->sgid = new->fsgid = new->egid;

	/* File caps or setid cancels ambient. */
	अगर (has_fcap || is_setid)
		cap_clear(new->cap_ambient);

	/*
	 * Now that we've computed pA', update pP' to give:
	 *   pP' = (X & fP) | (pI & fI) | pA'
	 */
	new->cap_permitted = cap_combine(new->cap_permitted, new->cap_ambient);

	/*
	 * Set pE' = (fE ? pP' : pA').  Because pA' is zero अगर fE is set,
	 * this is the same as pE' = (fE ? pP' : 0) | pA'.
	 */
	अगर (effective)
		new->cap_effective = new->cap_permitted;
	अन्यथा
		new->cap_effective = new->cap_ambient;

	अगर (WARN_ON(!cap_ambient_invariant_ok(new)))
		वापस -EPERM;

	अगर (nonroot_उठाओd_pE(new, old, root_uid, has_fcap)) अणु
		ret = audit_log_bprm_fcaps(bprm, new, old);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	new->securebits &= ~issecure_mask(SECURE_KEEP_CAPS);

	अगर (WARN_ON(!cap_ambient_invariant_ok(new)))
		वापस -EPERM;

	/* Check क्रम privilege-elevated exec. */
	अगर (is_setid ||
	    (!__is_real(root_uid, new) &&
	     (effective ||
	      __cap_grew(permitted, ambient, new))))
		bprm->secureexec = 1;

	वापस 0;
पूर्ण

/**
 * cap_inode_setxattr - Determine whether an xattr may be altered
 * @dentry: The inode/dentry being altered
 * @name: The name of the xattr to be changed
 * @value: The value that the xattr will be changed to
 * @size: The size of value
 * @flags: The replacement flag
 *
 * Determine whether an xattr may be altered or set on an inode, वापसing 0 अगर
 * permission is granted, -ve अगर denied.
 *
 * This is used to make sure security xattrs करोn't get updated or set by those
 * who aren't privileged to करो so.
 */
पूर्णांक cap_inode_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name,
		       स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा user_namespace *user_ns = dentry->d_sb->s_user_ns;

	/* Ignore non-security xattrs */
	अगर (म_भेदन(name, XATTR_SECURITY_PREFIX,
			XATTR_SECURITY_PREFIX_LEN) != 0)
		वापस 0;

	/*
	 * For XATTR_NAME_CAPS the check will be करोne in
	 * cap_convert_nscap(), called by setxattr()
	 */
	अगर (म_भेद(name, XATTR_NAME_CAPS) == 0)
		वापस 0;

	अगर (!ns_capable(user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;
	वापस 0;
पूर्ण

/**
 * cap_inode_हटाओxattr - Determine whether an xattr may be हटाओd
 *
 * @mnt_userns:	User namespace of the mount the inode was found from
 * @dentry:	The inode/dentry being altered
 * @name:	The name of the xattr to be changed
 *
 * Determine whether an xattr may be हटाओd from an inode, वापसing 0 अगर
 * permission is granted, -ve अगर denied.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 *
 * This is used to make sure security xattrs करोn't get हटाओd by those who
 * aren't privileged to हटाओ them.
 */
पूर्णांक cap_inode_हटाओxattr(काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, स्थिर अक्षर *name)
अणु
	काष्ठा user_namespace *user_ns = dentry->d_sb->s_user_ns;

	/* Ignore non-security xattrs */
	अगर (म_भेदन(name, XATTR_SECURITY_PREFIX,
			XATTR_SECURITY_PREFIX_LEN) != 0)
		वापस 0;

	अगर (म_भेद(name, XATTR_NAME_CAPS) == 0) अणु
		/* security.capability माला_लो namespaced */
		काष्ठा inode *inode = d_backing_inode(dentry);
		अगर (!inode)
			वापस -EINVAL;
		अगर (!capable_wrt_inode_uidgid(mnt_userns, inode, CAP_SETFCAP))
			वापस -EPERM;
		वापस 0;
	पूर्ण

	अगर (!ns_capable(user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;
	वापस 0;
पूर्ण

/*
 * cap_emulate_setxuid() fixes the effective / permitted capabilities of
 * a process after a call to setuid, setreuid, or setresuid.
 *
 *  1) When set*uiding _from_ one of अणुr,e,sपूर्णuid == 0 _to_ all of
 *  अणुr,e,sपूर्णuid != 0, the permitted and effective capabilities are
 *  cleared.
 *
 *  2) When set*uiding _from_ euid == 0 _to_ euid != 0, the effective
 *  capabilities of the process are cleared.
 *
 *  3) When set*uiding _from_ euid != 0 _to_ euid == 0, the effective
 *  capabilities are set to the permitted capabilities.
 *
 *  fsuid is handled अन्यथाwhere. fsuid == 0 and अणुr,e,sपूर्णuid!= 0 should
 *  never happen.
 *
 *  -astor
 *
 * cevans - New behaviour, Oct '99
 * A process may, via prctl(), elect to keep its capabilities when it
 * calls setuid() and चयनes away from uid==0. Both permitted and
 * effective sets will be retained.
 * Without this change, it was impossible क्रम a daemon to drop only some
 * of its privilege. The call to setuid(!=0) would drop all privileges!
 * Keeping uid 0 is not an option because uid 0 owns too many vital
 * files..
 * Thanks to Olaf Kirch and Peter Benie क्रम spotting this.
 */
अटल अंतरभूत व्योम cap_emulate_setxuid(काष्ठा cred *new, स्थिर काष्ठा cred *old)
अणु
	kuid_t root_uid = make_kuid(old->user_ns, 0);

	अगर ((uid_eq(old->uid, root_uid) ||
	     uid_eq(old->euid, root_uid) ||
	     uid_eq(old->suid, root_uid)) &&
	    (!uid_eq(new->uid, root_uid) &&
	     !uid_eq(new->euid, root_uid) &&
	     !uid_eq(new->suid, root_uid))) अणु
		अगर (!issecure(SECURE_KEEP_CAPS)) अणु
			cap_clear(new->cap_permitted);
			cap_clear(new->cap_effective);
		पूर्ण

		/*
		 * Pre-ambient programs expect setresuid to nonroot followed
		 * by exec to drop capabilities.  We should make sure that
		 * this reमुख्यs the हाल.
		 */
		cap_clear(new->cap_ambient);
	पूर्ण
	अगर (uid_eq(old->euid, root_uid) && !uid_eq(new->euid, root_uid))
		cap_clear(new->cap_effective);
	अगर (!uid_eq(old->euid, root_uid) && uid_eq(new->euid, root_uid))
		new->cap_effective = new->cap_permitted;
पूर्ण

/**
 * cap_task_fix_setuid - Fix up the results of setuid() call
 * @new: The proposed credentials
 * @old: The current task's current credentials
 * @flags: Indications of what has changed
 *
 * Fix up the results of setuid() call beक्रमe the credential changes are
 * actually applied.
 *
 * Return: 0 to grant the changes, -ve to deny them.
 */
पूर्णांक cap_task_fix_setuid(काष्ठा cred *new, स्थिर काष्ठा cred *old, पूर्णांक flags)
अणु
	चयन (flags) अणु
	हाल LSM_SETID_RE:
	हाल LSM_SETID_ID:
	हाल LSM_SETID_RES:
		/* juggle the capabilities to follow [RES]UID changes unless
		 * otherwise suppressed */
		अगर (!issecure(SECURE_NO_SETUID_FIXUP))
			cap_emulate_setxuid(new, old);
		अवरोध;

	हाल LSM_SETID_FS:
		/* juggle the capabilties to follow FSUID changes, unless
		 * otherwise suppressed
		 *
		 * FIXME - is fsuser used क्रम all CAP_FS_MASK capabilities?
		 *          अगर not, we might be a bit too harsh here.
		 */
		अगर (!issecure(SECURE_NO_SETUID_FIXUP)) अणु
			kuid_t root_uid = make_kuid(old->user_ns, 0);
			अगर (uid_eq(old->fsuid, root_uid) && !uid_eq(new->fsuid, root_uid))
				new->cap_effective =
					cap_drop_fs_set(new->cap_effective);

			अगर (!uid_eq(old->fsuid, root_uid) && uid_eq(new->fsuid, root_uid))
				new->cap_effective =
					cap_उठाओ_fs_set(new->cap_effective,
							 new->cap_permitted);
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Rationale: code calling task_setscheduler, task_setioprio, and
 * task_setnice, assumes that
 *   . अगर capable(cap_sys_nice), then those actions should be allowed
 *   . अगर not capable(cap_sys_nice), but acting on your own processes,
 *   	then those actions should be allowed
 * This is insufficient now since you can call code without suid, but
 * yet with increased caps.
 * So we check क्रम increased caps on the target process.
 */
अटल पूर्णांक cap_safe_nice(काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक is_subset, ret = 0;

	rcu_पढ़ो_lock();
	is_subset = cap_issubset(__task_cred(p)->cap_permitted,
				 current_cred()->cap_permitted);
	अगर (!is_subset && !ns_capable(__task_cred(p)->user_ns, CAP_SYS_NICE))
		ret = -EPERM;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/**
 * cap_task_setscheduler - Detemine अगर scheduler policy change is permitted
 * @p: The task to affect
 *
 * Detemine अगर the requested scheduler policy change is permitted क्रम the
 * specअगरied task.
 *
 * Return: 0 अगर permission is granted, -ve अगर denied.
 */
पूर्णांक cap_task_setscheduler(काष्ठा task_काष्ठा *p)
अणु
	वापस cap_safe_nice(p);
पूर्ण

/**
 * cap_task_setioprio - Detemine अगर I/O priority change is permitted
 * @p: The task to affect
 * @ioprio: The I/O priority to set
 *
 * Detemine अगर the requested I/O priority change is permitted क्रम the specअगरied
 * task.
 *
 * Return: 0 अगर permission is granted, -ve अगर denied.
 */
पूर्णांक cap_task_setioprio(काष्ठा task_काष्ठा *p, पूर्णांक ioprio)
अणु
	वापस cap_safe_nice(p);
पूर्ण

/**
 * cap_task_setnice - Detemine अगर task priority change is permitted
 * @p: The task to affect
 * @nice: The nice value to set
 *
 * Detemine अगर the requested task priority change is permitted क्रम the
 * specअगरied task.
 *
 * Return: 0 अगर permission is granted, -ve अगर denied.
 */
पूर्णांक cap_task_setnice(काष्ठा task_काष्ठा *p, पूर्णांक nice)
अणु
	वापस cap_safe_nice(p);
पूर्ण

/*
 * Implement PR_CAPBSET_DROP.  Attempt to हटाओ the specअगरied capability from
 * the current task's bounding set.  Returns 0 on success, -ve on error.
 */
अटल पूर्णांक cap_prctl_drop(अचिन्हित दीर्घ cap)
अणु
	काष्ठा cred *new;

	अगर (!ns_capable(current_user_ns(), CAP_SETPCAP))
		वापस -EPERM;
	अगर (!cap_valid(cap))
		वापस -EINVAL;

	new = prepare_creds();
	अगर (!new)
		वापस -ENOMEM;
	cap_lower(new->cap_bset, cap);
	वापस commit_creds(new);
पूर्ण

/**
 * cap_task_prctl - Implement process control functions क्रम this security module
 * @option: The process control function requested
 * @arg2: The argument data क्रम this function
 * @arg3: The argument data क्रम this function
 * @arg4: The argument data क्रम this function
 * @arg5: The argument data क्रम this function
 *
 * Allow process control functions (sys_prctl()) to alter capabilities; may
 * also deny access to other functions not otherwise implemented here.
 *
 * Return: 0 or +ve on success, -ENOSYS अगर this function is not implemented
 * here, other -ve on error.  If -ENOSYS is वापसed, sys_prctl() and other LSM
 * modules will consider perक्रमming the function.
 */
पूर्णांक cap_task_prctl(पूर्णांक option, अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
		   अचिन्हित दीर्घ arg4, अचिन्हित दीर्घ arg5)
अणु
	स्थिर काष्ठा cred *old = current_cred();
	काष्ठा cred *new;

	चयन (option) अणु
	हाल PR_CAPBSET_READ:
		अगर (!cap_valid(arg2))
			वापस -EINVAL;
		वापस !!cap_उठाओd(old->cap_bset, arg2);

	हाल PR_CAPBSET_DROP:
		वापस cap_prctl_drop(arg2);

	/*
	 * The next four prctl's reमुख्य to assist with transitioning a
	 * प्रणाली from legacy UID=0 based privilege (when fileप्रणाली
	 * capabilities are not in use) to a प्रणाली using fileप्रणाली
	 * capabilities only - as the POSIX.1e draft पूर्णांकended.
	 *
	 * Note:
	 *
	 *  PR_SET_SECUREBITS =
	 *      issecure_mask(SECURE_KEEP_CAPS_LOCKED)
	 *    | issecure_mask(SECURE_NOROOT)
	 *    | issecure_mask(SECURE_NOROOT_LOCKED)
	 *    | issecure_mask(SECURE_NO_SETUID_FIXUP)
	 *    | issecure_mask(SECURE_NO_SETUID_FIXUP_LOCKED)
	 *
	 * will ensure that the current process and all of its
	 * children will be locked पूर्णांकo a pure
	 * capability-based-privilege environment.
	 */
	हाल PR_SET_SECUREBITS:
		अगर ((((old->securebits & SECURE_ALL_LOCKS) >> 1)
		     & (old->securebits ^ arg2))			/*[1]*/
		    || ((old->securebits & SECURE_ALL_LOCKS & ~arg2))	/*[2]*/
		    || (arg2 & ~(SECURE_ALL_LOCKS | SECURE_ALL_BITS))	/*[3]*/
		    || (cap_capable(current_cred(),
				    current_cred()->user_ns,
				    CAP_SETPCAP,
				    CAP_OPT_NONE) != 0)			/*[4]*/
			/*
			 * [1] no changing of bits that are locked
			 * [2] no unlocking of locks
			 * [3] no setting of unsupported bits
			 * [4] करोing anything requires privilege (go पढ़ो about
			 *     the "sendmail capabilities bug")
			 */
		    )
			/* cannot change a locked bit */
			वापस -EPERM;

		new = prepare_creds();
		अगर (!new)
			वापस -ENOMEM;
		new->securebits = arg2;
		वापस commit_creds(new);

	हाल PR_GET_SECUREBITS:
		वापस old->securebits;

	हाल PR_GET_KEEPCAPS:
		वापस !!issecure(SECURE_KEEP_CAPS);

	हाल PR_SET_KEEPCAPS:
		अगर (arg2 > 1) /* Note, we rely on arg2 being अचिन्हित here */
			वापस -EINVAL;
		अगर (issecure(SECURE_KEEP_CAPS_LOCKED))
			वापस -EPERM;

		new = prepare_creds();
		अगर (!new)
			वापस -ENOMEM;
		अगर (arg2)
			new->securebits |= issecure_mask(SECURE_KEEP_CAPS);
		अन्यथा
			new->securebits &= ~issecure_mask(SECURE_KEEP_CAPS);
		वापस commit_creds(new);

	हाल PR_CAP_AMBIENT:
		अगर (arg2 == PR_CAP_AMBIENT_CLEAR_ALL) अणु
			अगर (arg3 | arg4 | arg5)
				वापस -EINVAL;

			new = prepare_creds();
			अगर (!new)
				वापस -ENOMEM;
			cap_clear(new->cap_ambient);
			वापस commit_creds(new);
		पूर्ण

		अगर (((!cap_valid(arg3)) | arg4 | arg5))
			वापस -EINVAL;

		अगर (arg2 == PR_CAP_AMBIENT_IS_SET) अणु
			वापस !!cap_उठाओd(current_cred()->cap_ambient, arg3);
		पूर्ण अन्यथा अगर (arg2 != PR_CAP_AMBIENT_RAISE &&
			   arg2 != PR_CAP_AMBIENT_LOWER) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (arg2 == PR_CAP_AMBIENT_RAISE &&
			    (!cap_उठाओd(current_cred()->cap_permitted, arg3) ||
			     !cap_उठाओd(current_cred()->cap_inheritable,
					 arg3) ||
			     issecure(SECURE_NO_CAP_AMBIENT_RAISE)))
				वापस -EPERM;

			new = prepare_creds();
			अगर (!new)
				वापस -ENOMEM;
			अगर (arg2 == PR_CAP_AMBIENT_RAISE)
				cap_उठाओ(new->cap_ambient, arg3);
			अन्यथा
				cap_lower(new->cap_ambient, arg3);
			वापस commit_creds(new);
		पूर्ण

	शेष:
		/* No functionality available - जारी with शेष */
		वापस -ENOSYS;
	पूर्ण
पूर्ण

/**
 * cap_vm_enough_memory - Determine whether a new भव mapping is permitted
 * @mm: The VM space in which the new mapping is to be made
 * @pages: The size of the mapping
 *
 * Determine whether the allocation of a new भव mapping by the current
 * task is permitted.
 *
 * Return: 1 अगर permission is granted, 0 अगर not.
 */
पूर्णांक cap_vm_enough_memory(काष्ठा mm_काष्ठा *mm, दीर्घ pages)
अणु
	पूर्णांक cap_sys_admin = 0;

	अगर (cap_capable(current_cred(), &init_user_ns,
				CAP_SYS_ADMIN, CAP_OPT_NOAUDIT) == 0)
		cap_sys_admin = 1;

	वापस cap_sys_admin;
पूर्ण

/**
 * cap_mmap_addr - check अगर able to map given addr
 * @addr: address attempting to be mapped
 *
 * If the process is attempting to map memory below dac_mmap_min_addr they need
 * CAP_SYS_RAWIO.  The other parameters to this function are unused by the
 * capability security module.
 *
 * Return: 0 अगर this mapping should be allowed or -EPERM अगर not.
 */
पूर्णांक cap_mmap_addr(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक ret = 0;

	अगर (addr < dac_mmap_min_addr) अणु
		ret = cap_capable(current_cred(), &init_user_ns, CAP_SYS_RAWIO,
				  CAP_OPT_NONE);
		/* set PF_SUPERPRIV अगर it turns out we allow the low mmap */
		अगर (ret == 0)
			current->flags |= PF_SUPERPRIV;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक cap_mmap_file(काष्ठा file *file, अचिन्हित दीर्घ reqprot,
		  अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SECURITY

अटल काष्ठा security_hook_list capability_hooks[] __lsm_ro_after_init = अणु
	LSM_HOOK_INIT(capable, cap_capable),
	LSM_HOOK_INIT(समय_रखो, cap_समय_रखो),
	LSM_HOOK_INIT(ptrace_access_check, cap_ptrace_access_check),
	LSM_HOOK_INIT(ptrace_traceme, cap_ptrace_traceme),
	LSM_HOOK_INIT(capget, cap_capget),
	LSM_HOOK_INIT(capset, cap_capset),
	LSM_HOOK_INIT(bprm_creds_from_file, cap_bprm_creds_from_file),
	LSM_HOOK_INIT(inode_need_समाप्तpriv, cap_inode_need_समाप्तpriv),
	LSM_HOOK_INIT(inode_समाप्तpriv, cap_inode_समाप्तpriv),
	LSM_HOOK_INIT(inode_माला_लोecurity, cap_inode_माला_लोecurity),
	LSM_HOOK_INIT(mmap_addr, cap_mmap_addr),
	LSM_HOOK_INIT(mmap_file, cap_mmap_file),
	LSM_HOOK_INIT(task_fix_setuid, cap_task_fix_setuid),
	LSM_HOOK_INIT(task_prctl, cap_task_prctl),
	LSM_HOOK_INIT(task_setscheduler, cap_task_setscheduler),
	LSM_HOOK_INIT(task_setioprio, cap_task_setioprio),
	LSM_HOOK_INIT(task_setnice, cap_task_setnice),
	LSM_HOOK_INIT(vm_enough_memory, cap_vm_enough_memory),
पूर्ण;

अटल पूर्णांक __init capability_init(व्योम)
अणु
	security_add_hooks(capability_hooks, ARRAY_SIZE(capability_hooks),
				"capability");
	वापस 0;
पूर्ण

DEFINE_LSM(capability) = अणु
	.name = "capability",
	.order = LSM_ORDER_FIRST,
	.init = capability_init,
पूर्ण;

#पूर्ण_अगर /* CONFIG_SECURITY */
