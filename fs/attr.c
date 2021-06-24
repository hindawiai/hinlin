<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/attr.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  changes by Thomas Schoebel-Theuer
 */

#समावेश <linux/export.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/capability.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/security.h>
#समावेश <linux/evm.h>
#समावेश <linux/ima.h>

/**
 * chown_ok - verअगरy permissions to chown inode
 * @mnt_userns:	user namespace of the mount @inode was found from
 * @inode:	inode to check permissions on
 * @uid:	uid to chown @inode to
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 */
अटल bool chown_ok(काष्ठा user_namespace *mnt_userns,
		     स्थिर काष्ठा inode *inode,
		     kuid_t uid)
अणु
	kuid_t kuid = i_uid_पूर्णांकo_mnt(mnt_userns, inode);
	अगर (uid_eq(current_fsuid(), kuid) && uid_eq(uid, kuid))
		वापस true;
	अगर (capable_wrt_inode_uidgid(mnt_userns, inode, CAP_CHOWN))
		वापस true;
	अगर (uid_eq(kuid, INVALID_UID) &&
	    ns_capable(inode->i_sb->s_user_ns, CAP_CHOWN))
		वापस true;
	वापस false;
पूर्ण

/**
 * chgrp_ok - verअगरy permissions to chgrp inode
 * @mnt_userns:	user namespace of the mount @inode was found from
 * @inode:	inode to check permissions on
 * @gid:	gid to chown @inode to
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 */
अटल bool chgrp_ok(काष्ठा user_namespace *mnt_userns,
		     स्थिर काष्ठा inode *inode, kgid_t gid)
अणु
	kgid_t kgid = i_gid_पूर्णांकo_mnt(mnt_userns, inode);
	अगर (uid_eq(current_fsuid(), i_uid_पूर्णांकo_mnt(mnt_userns, inode)) &&
	    (in_group_p(gid) || gid_eq(gid, kgid)))
		वापस true;
	अगर (capable_wrt_inode_uidgid(mnt_userns, inode, CAP_CHOWN))
		वापस true;
	अगर (gid_eq(kgid, INVALID_GID) &&
	    ns_capable(inode->i_sb->s_user_ns, CAP_CHOWN))
		वापस true;
	वापस false;
पूर्ण

/**
 * setattr_prepare - check अगर attribute changes to a dentry are allowed
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dentry:	dentry to check
 * @attr:	attributes to change
 *
 * Check अगर we are allowed to change the attributes contained in @attr
 * in the given dentry.  This includes the normal unix access permission
 * checks, as well as checks क्रम rlimits and others. The function also clears
 * SGID bit from mode अगर user is not allowed to set it. Also file capabilities
 * and IMA extended attributes are cleared अगर ATTR_KILL_PRIV is set.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 *
 * Should be called as the first thing in ->setattr implementations,
 * possibly after taking additional locks.
 */
पूर्णांक setattr_prepare(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		    काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	अचिन्हित पूर्णांक ia_valid = attr->ia_valid;

	/*
	 * First check size स्थिरraपूर्णांकs.  These can't be overriden using
	 * ATTR_FORCE.
	 */
	अगर (ia_valid & ATTR_SIZE) अणु
		पूर्णांक error = inode_newsize_ok(inode, attr->ia_size);
		अगर (error)
			वापस error;
	पूर्ण

	/* If क्रमce is set करो it anyway. */
	अगर (ia_valid & ATTR_FORCE)
		जाओ समाप्त_priv;

	/* Make sure a caller can chown. */
	अगर ((ia_valid & ATTR_UID) && !chown_ok(mnt_userns, inode, attr->ia_uid))
		वापस -EPERM;

	/* Make sure caller can chgrp. */
	अगर ((ia_valid & ATTR_GID) && !chgrp_ok(mnt_userns, inode, attr->ia_gid))
		वापस -EPERM;

	/* Make sure a caller can chmod. */
	अगर (ia_valid & ATTR_MODE) अणु
		अगर (!inode_owner_or_capable(mnt_userns, inode))
			वापस -EPERM;
		/* Also check the setgid bit! */
               अगर (!in_group_p((ia_valid & ATTR_GID) ? attr->ia_gid :
                                i_gid_पूर्णांकo_mnt(mnt_userns, inode)) &&
                    !capable_wrt_inode_uidgid(mnt_userns, inode, CAP_FSETID))
			attr->ia_mode &= ~S_ISGID;
	पूर्ण

	/* Check क्रम setting the inode समय. */
	अगर (ia_valid & (ATTR_MTIME_SET | ATTR_ATIME_SET | ATTR_TIMES_SET)) अणु
		अगर (!inode_owner_or_capable(mnt_userns, inode))
			वापस -EPERM;
	पूर्ण

समाप्त_priv:
	/* User has permission क्रम the change */
	अगर (ia_valid & ATTR_KILL_PRIV) अणु
		पूर्णांक error;

		error = security_inode_समाप्तpriv(mnt_userns, dentry);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(setattr_prepare);

/**
 * inode_newsize_ok - may this inode be truncated to a given size
 * @inode:	the inode to be truncated
 * @offset:	the new size to assign to the inode
 *
 * inode_newsize_ok must be called with i_mutex held.
 *
 * inode_newsize_ok will check fileप्रणाली limits and ulimits to check that the
 * new inode size is within limits. inode_newsize_ok will also send SIGXFSZ
 * when necessary. Caller must not proceed with inode size change अगर failure is
 * वापसed. @inode must be a file (not directory), with appropriate
 * permissions to allow truncate (inode_newsize_ok करोes NOT check these
 * conditions).
 *
 * Return: 0 on success, -ve त्रुटि_सं on failure
 */
पूर्णांक inode_newsize_ok(स्थिर काष्ठा inode *inode, loff_t offset)
अणु
	अगर (inode->i_size < offset) अणु
		अचिन्हित दीर्घ limit;

		limit = rlimit(RLIMIT_FSIZE);
		अगर (limit != RLIM_अनन्त && offset > limit)
			जाओ out_sig;
		अगर (offset > inode->i_sb->s_maxbytes)
			जाओ out_big;
	पूर्ण अन्यथा अणु
		/*
		 * truncation of in-use swapfiles is disallowed - it would
		 * cause subsequent swapout to scribble on the now-मुक्तd
		 * blocks.
		 */
		अगर (IS_SWAPखाता(inode))
			वापस -ETXTBSY;
	पूर्ण

	वापस 0;
out_sig:
	send_sig(SIGXFSZ, current, 0);
out_big:
	वापस -EFBIG;
पूर्ण
EXPORT_SYMBOL(inode_newsize_ok);

/**
 * setattr_copy - copy simple metadata updates पूर्णांकo the generic inode
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode:	the inode to be updated
 * @attr:	the new attributes
 *
 * setattr_copy must be called with i_mutex held.
 *
 * setattr_copy updates the inode's metadata with that specअगरied
 * in attr on idmapped mounts. If file ownership is changed setattr_copy
 * करोesn't map ia_uid and ia_gid. It will asssume the caller has alपढ़ोy
 * provided the पूर्णांकended values. Necessary permission checks to determine
 * whether or not the S_ISGID property needs to be हटाओd are perक्रमmed with
 * the correct idmapped mount permission helpers.
 * Noticeably missing is inode size update, which is more complex
 * as it requires pagecache updates.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 *
 * The inode is not marked as dirty after this operation. The rationale is
 * that क्रम "simple" fileप्रणालीs, the काष्ठा inode is the inode storage.
 * The caller is मुक्त to mark the inode dirty afterwards अगर needed.
 */
व्योम setattr_copy(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		  स्थिर काष्ठा iattr *attr)
अणु
	अचिन्हित पूर्णांक ia_valid = attr->ia_valid;

	अगर (ia_valid & ATTR_UID)
		inode->i_uid = attr->ia_uid;
	अगर (ia_valid & ATTR_GID)
		inode->i_gid = attr->ia_gid;
	अगर (ia_valid & ATTR_ATIME)
		inode->i_aसमय = attr->ia_aसमय;
	अगर (ia_valid & ATTR_MTIME)
		inode->i_mसमय = attr->ia_mसमय;
	अगर (ia_valid & ATTR_CTIME)
		inode->i_स_समय = attr->ia_स_समय;
	अगर (ia_valid & ATTR_MODE) अणु
		umode_t mode = attr->ia_mode;
		kgid_t kgid = i_gid_पूर्णांकo_mnt(mnt_userns, inode);
		अगर (!in_group_p(kgid) &&
		    !capable_wrt_inode_uidgid(mnt_userns, inode, CAP_FSETID))
			mode &= ~S_ISGID;
		inode->i_mode = mode;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(setattr_copy);

/**
 * notअगरy_change - modअगरy attributes of a filesytem object
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @dentry:	object affected
 * @attr:	new attributes
 * @delegated_inode: वापसs inode, अगर the inode is delegated
 *
 * The caller must hold the i_mutex on the affected object.
 *
 * If notअगरy_change discovers a delegation in need of अवरोधing,
 * it will वापस -EWOULDBLOCK and वापस a reference to the inode in
 * delegated_inode.  The caller should then अवरोध the delegation and
 * retry.  Because अवरोधing a delegation may take a दीर्घ समय, the
 * caller should drop the i_mutex beक्रमe करोing so.
 *
 * If file ownership is changed notअगरy_change() करोesn't map ia_uid and
 * ia_gid. It will asssume the caller has alपढ़ोy provided the पूर्णांकended values.
 *
 * Alternatively, a caller may pass शून्य क्रम delegated_inode.  This may
 * be appropriate क्रम callers that expect the underlying fileप्रणाली not
 * to be NFS exported.  Also, passing शून्य is fine क्रम callers holding
 * the file खोलो क्रम ग_लिखो, as there can be no conflicting delegation in
 * that हाल.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then
 * take care to map the inode according to @mnt_userns beक्रमe checking
 * permissions. On non-idmapped mounts or अगर permission checking is to be
 * perक्रमmed on the raw inode simply passs init_user_ns.
 */
पूर्णांक notअगरy_change(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		  काष्ठा iattr *attr, काष्ठा inode **delegated_inode)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	umode_t mode = inode->i_mode;
	पूर्णांक error;
	काष्ठा बारpec64 now;
	अचिन्हित पूर्णांक ia_valid = attr->ia_valid;

	WARN_ON_ONCE(!inode_is_locked(inode));

	अगर (ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID | ATTR_TIMES_SET)) अणु
		अगर (IS_IMMUTABLE(inode) || IS_APPEND(inode))
			वापस -EPERM;
	पूर्ण

	/*
	 * If uबार(2) and मित्रs are called with बार == शून्य (or both
	 * बार are UTIME_NOW), then we need to check क्रम ग_लिखो permission
	 */
	अगर (ia_valid & ATTR_TOUCH) अणु
		अगर (IS_IMMUTABLE(inode))
			वापस -EPERM;

		अगर (!inode_owner_or_capable(mnt_userns, inode)) अणु
			error = inode_permission(mnt_userns, inode, MAY_WRITE);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	अगर ((ia_valid & ATTR_MODE)) अणु
		umode_t amode = attr->ia_mode;
		/* Flag setting रक्षित by i_mutex */
		अगर (is_sxid(amode))
			inode->i_flags &= ~S_NOSEC;
	पूर्ण

	now = current_समय(inode);

	attr->ia_स_समय = now;
	अगर (!(ia_valid & ATTR_ATIME_SET))
		attr->ia_aसमय = now;
	अन्यथा
		attr->ia_aसमय = बारtamp_truncate(attr->ia_aसमय, inode);
	अगर (!(ia_valid & ATTR_MTIME_SET))
		attr->ia_mसमय = now;
	अन्यथा
		attr->ia_mसमय = बारtamp_truncate(attr->ia_mसमय, inode);

	अगर (ia_valid & ATTR_KILL_PRIV) अणु
		error = security_inode_need_समाप्तpriv(dentry);
		अगर (error < 0)
			वापस error;
		अगर (error == 0)
			ia_valid = attr->ia_valid &= ~ATTR_KILL_PRIV;
	पूर्ण

	/*
	 * We now pass ATTR_KILL_S*ID to the lower level setattr function so
	 * that the function has the ability to reपूर्णांकerpret a mode change
	 * that's due to these bits. This adds an implicit restriction that
	 * no function will ever call notअगरy_change with both ATTR_MODE and
	 * ATTR_KILL_S*ID set.
	 */
	अगर ((ia_valid & (ATTR_KILL_SUID|ATTR_KILL_SGID)) &&
	    (ia_valid & ATTR_MODE))
		BUG();

	अगर (ia_valid & ATTR_KILL_SUID) अणु
		अगर (mode & S_ISUID) अणु
			ia_valid = attr->ia_valid |= ATTR_MODE;
			attr->ia_mode = (inode->i_mode & ~S_ISUID);
		पूर्ण
	पूर्ण
	अगर (ia_valid & ATTR_KILL_SGID) अणु
		अगर ((mode & (S_ISGID | S_IXGRP)) == (S_ISGID | S_IXGRP)) अणु
			अगर (!(ia_valid & ATTR_MODE)) अणु
				ia_valid = attr->ia_valid |= ATTR_MODE;
				attr->ia_mode = inode->i_mode;
			पूर्ण
			attr->ia_mode &= ~S_ISGID;
		पूर्ण
	पूर्ण
	अगर (!(attr->ia_valid & ~(ATTR_KILL_SUID | ATTR_KILL_SGID)))
		वापस 0;

	/*
	 * Verअगरy that uid/gid changes are valid in the target
	 * namespace of the superblock.
	 */
	अगर (ia_valid & ATTR_UID &&
	    !kuid_has_mapping(inode->i_sb->s_user_ns, attr->ia_uid))
		वापस -EOVERFLOW;
	अगर (ia_valid & ATTR_GID &&
	    !kgid_has_mapping(inode->i_sb->s_user_ns, attr->ia_gid))
		वापस -EOVERFLOW;

	/* Don't allow modअगरications of files with invalid uids or
	 * gids unless those uids & gids are being made valid.
	 */
	अगर (!(ia_valid & ATTR_UID) &&
	    !uid_valid(i_uid_पूर्णांकo_mnt(mnt_userns, inode)))
		वापस -EOVERFLOW;
	अगर (!(ia_valid & ATTR_GID) &&
	    !gid_valid(i_gid_पूर्णांकo_mnt(mnt_userns, inode)))
		वापस -EOVERFLOW;

	error = security_inode_setattr(dentry, attr);
	अगर (error)
		वापस error;
	error = try_अवरोध_deleg(inode, delegated_inode);
	अगर (error)
		वापस error;

	अगर (inode->i_op->setattr)
		error = inode->i_op->setattr(mnt_userns, dentry, attr);
	अन्यथा
		error = simple_setattr(mnt_userns, dentry, attr);

	अगर (!error) अणु
		fsnotअगरy_change(dentry, ia_valid);
		ima_inode_post_setattr(mnt_userns, dentry);
		evm_inode_post_setattr(dentry, ia_valid);
	पूर्ण

	वापस error;
पूर्ण
EXPORT_SYMBOL(notअगरy_change);
