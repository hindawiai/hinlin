<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
  File: fs/xattr.c

  Extended attribute handling.

  Copyright (C) 2001 by Andreas Gruenbacher <a.gruenbacher@computer.org>
  Copyright (C) 2001 SGI - Silicon Graphics, Inc <linux-xfs@oss.sgi.com>
  Copyright (c) 2004 Red Hat, Inc., James Morris <jmorris@redhat.com>
 */
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/xattr.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/security.h>
#समावेश <linux/evm.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/export.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/audit.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/posix_acl_xattr.h>

#समावेश <linux/uaccess.h>

अटल स्थिर अक्षर *
म_भेद_prefix(स्थिर अक्षर *a, स्थिर अक्षर *a_prefix)
अणु
	जबतक (*a_prefix && *a == *a_prefix) अणु
		a++;
		a_prefix++;
	पूर्ण
	वापस *a_prefix ? शून्य : a;
पूर्ण

/*
 * In order to implement dअगरferent sets of xattr operations क्रम each xattr
 * prefix, a fileप्रणाली should create a null-terminated array of काष्ठा
 * xattr_handler (one क्रम each prefix) and hang a poपूर्णांकer to it off of the
 * s_xattr field of the superblock.
 */
#घोषणा क्रम_each_xattr_handler(handlers, handler)		\
	अगर (handlers)						\
		क्रम ((handler) = *(handlers)++;			\
			(handler) != शून्य;			\
			(handler) = *(handlers)++)

/*
 * Find the xattr_handler with the matching prefix.
 */
अटल स्थिर काष्ठा xattr_handler *
xattr_resolve_name(काष्ठा inode *inode, स्थिर अक्षर **name)
अणु
	स्थिर काष्ठा xattr_handler **handlers = inode->i_sb->s_xattr;
	स्थिर काष्ठा xattr_handler *handler;

	अगर (!(inode->i_opflags & IOP_XATTR)) अणु
		अगर (unlikely(is_bad_inode(inode)))
			वापस ERR_PTR(-EIO);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण
	क्रम_each_xattr_handler(handlers, handler) अणु
		स्थिर अक्षर *n;

		n = म_भेद_prefix(*name, xattr_prefix(handler));
		अगर (n) अणु
			अगर (!handler->prefix ^ !*n) अणु
				अगर (*n)
					जारी;
				वापस ERR_PTR(-EINVAL);
			पूर्ण
			*name = n;
			वापस handler;
		पूर्ण
	पूर्ण
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

/*
 * Check permissions क्रम extended attribute access.  This is a bit complicated
 * because dअगरferent namespaces have very dअगरferent rules.
 */
अटल पूर्णांक
xattr_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		 स्थिर अक्षर *name, पूर्णांक mask)
अणु
	/*
	 * We can never set or हटाओ an extended attribute on a पढ़ो-only
	 * fileप्रणाली  or on an immutable / append-only inode.
	 */
	अगर (mask & MAY_WRITE) अणु
		अगर (IS_IMMUTABLE(inode) || IS_APPEND(inode))
			वापस -EPERM;
		/*
		 * Updating an xattr will likely cause i_uid and i_gid
		 * to be ग_लिखोn back improperly अगर their true value is
		 * unknown to the vfs.
		 */
		अगर (HAS_UNMAPPED_ID(mnt_userns, inode))
			वापस -EPERM;
	पूर्ण

	/*
	 * No restriction क्रम security.* and प्रणाली.* from the VFS.  Decision
	 * on these is left to the underlying fileप्रणाली / security module.
	 */
	अगर (!म_भेदन(name, XATTR_SECURITY_PREFIX, XATTR_SECURITY_PREFIX_LEN) ||
	    !म_भेदन(name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN))
		वापस 0;

	/*
	 * The trusted.* namespace can only be accessed by privileged users.
	 */
	अगर (!म_भेदन(name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN)) अणु
		अगर (!capable(CAP_SYS_ADMIN))
			वापस (mask & MAY_WRITE) ? -EPERM : -ENODATA;
		वापस 0;
	पूर्ण

	/*
	 * In the user.* namespace, only regular files and directories can have
	 * extended attributes. For sticky directories, only the owner and
	 * privileged users can ग_लिखो attributes.
	 */
	अगर (!म_भेदन(name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN)) अणु
		अगर (!S_ISREG(inode->i_mode) && !S_ISसूची(inode->i_mode))
			वापस (mask & MAY_WRITE) ? -EPERM : -ENODATA;
		अगर (S_ISसूची(inode->i_mode) && (inode->i_mode & S_ISVTX) &&
		    (mask & MAY_WRITE) &&
		    !inode_owner_or_capable(mnt_userns, inode))
			वापस -EPERM;
	पूर्ण

	वापस inode_permission(mnt_userns, inode, mask);
पूर्ण

/*
 * Look क्रम any handler that deals with the specअगरied namespace.
 */
पूर्णांक
xattr_supported_namespace(काष्ठा inode *inode, स्थिर अक्षर *prefix)
अणु
	स्थिर काष्ठा xattr_handler **handlers = inode->i_sb->s_xattr;
	स्थिर काष्ठा xattr_handler *handler;
	माप_प्रकार preflen;

	अगर (!(inode->i_opflags & IOP_XATTR)) अणु
		अगर (unlikely(is_bad_inode(inode)))
			वापस -EIO;
		वापस -EOPNOTSUPP;
	पूर्ण

	preflen = म_माप(prefix);

	क्रम_each_xattr_handler(handlers, handler) अणु
		अगर (!म_भेदन(xattr_prefix(handler), prefix, preflen))
			वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण
EXPORT_SYMBOL(xattr_supported_namespace);

पूर्णांक
__vfs_setxattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
	       काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *value,
	       माप_प्रकार size, पूर्णांक flags)
अणु
	स्थिर काष्ठा xattr_handler *handler;

	handler = xattr_resolve_name(inode, &name);
	अगर (IS_ERR(handler))
		वापस PTR_ERR(handler);
	अगर (!handler->set)
		वापस -EOPNOTSUPP;
	अगर (size == 0)
		value = "";  /* empty EA, करो not हटाओ */
	वापस handler->set(handler, mnt_userns, dentry, inode, name, value,
			    size, flags);
पूर्ण
EXPORT_SYMBOL(__vfs_setxattr);

/**
 *  __vfs_setxattr_noperm - perक्रमm setxattr operation without perक्रमming
 *  permission checks.
 *
 *  @mnt_userns: user namespace of the mount the inode was found from
 *  @dentry: object to perक्रमm setxattr on
 *  @name: xattr name to set
 *  @value: value to set @name to
 *  @size: size of @value
 *  @flags: flags to pass पूर्णांकo fileप्रणाली operations
 *
 *  वापसs the result of the पूर्णांकernal setxattr or setsecurity operations.
 *
 *  This function requires the caller to lock the inode's i_mutex beक्रमe it
 *  is executed. It also assumes that the caller will make the appropriate
 *  permission checks.
 */
पूर्णांक __vfs_setxattr_noperm(काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, स्थिर अक्षर *name,
			  स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	पूर्णांक error = -EAGAIN;
	पूर्णांक issec = !म_भेदन(name, XATTR_SECURITY_PREFIX,
				   XATTR_SECURITY_PREFIX_LEN);

	अगर (issec)
		inode->i_flags &= ~S_NOSEC;
	अगर (inode->i_opflags & IOP_XATTR) अणु
		error = __vfs_setxattr(mnt_userns, dentry, inode, name, value,
				       size, flags);
		अगर (!error) अणु
			fsnotअगरy_xattr(dentry);
			security_inode_post_setxattr(dentry, name, value,
						     size, flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unlikely(is_bad_inode(inode)))
			वापस -EIO;
	पूर्ण
	अगर (error == -EAGAIN) अणु
		error = -EOPNOTSUPP;

		अगर (issec) अणु
			स्थिर अक्षर *suffix = name + XATTR_SECURITY_PREFIX_LEN;

			error = security_inode_setsecurity(inode, suffix, value,
							   size, flags);
			अगर (!error)
				fsnotअगरy_xattr(dentry);
		पूर्ण
	पूर्ण

	वापस error;
पूर्ण

/**
 * __vfs_setxattr_locked - set an extended attribute जबतक holding the inode
 * lock
 *
 *  @mnt_userns: user namespace of the mount of the target inode
 *  @dentry: object to perक्रमm setxattr on
 *  @name: xattr name to set
 *  @value: value to set @name to
 *  @size: size of @value
 *  @flags: flags to pass पूर्णांकo fileप्रणाली operations
 *  @delegated_inode: on वापस, will contain an inode poपूर्णांकer that
 *  a delegation was broken on, शून्य अगर none.
 */
पूर्णांक
__vfs_setxattr_locked(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		      स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size,
		      पूर्णांक flags, काष्ठा inode **delegated_inode)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	पूर्णांक error;

	error = xattr_permission(mnt_userns, inode, name, MAY_WRITE);
	अगर (error)
		वापस error;

	error = security_inode_setxattr(mnt_userns, dentry, name, value, size,
					flags);
	अगर (error)
		जाओ out;

	error = try_अवरोध_deleg(inode, delegated_inode);
	अगर (error)
		जाओ out;

	error = __vfs_setxattr_noperm(mnt_userns, dentry, name, value,
				      size, flags);

out:
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(__vfs_setxattr_locked);

पूर्णांक
vfs_setxattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
	     स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	काष्ठा inode *delegated_inode = शून्य;
	स्थिर व्योम  *orig_value = value;
	पूर्णांक error;

	अगर (size && म_भेद(name, XATTR_NAME_CAPS) == 0) अणु
		error = cap_convert_nscap(mnt_userns, dentry, &value, size);
		अगर (error < 0)
			वापस error;
		size = error;
	पूर्ण

retry_deleg:
	inode_lock(inode);
	error = __vfs_setxattr_locked(mnt_userns, dentry, name, value, size,
				      flags, &delegated_inode);
	inode_unlock(inode);

	अगर (delegated_inode) अणु
		error = अवरोध_deleg_रुको(&delegated_inode);
		अगर (!error)
			जाओ retry_deleg;
	पूर्ण
	अगर (value != orig_value)
		kमुक्त(value);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(vfs_setxattr);

अटल sमाप_प्रकार
xattr_माला_लोecurity(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		  स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	व्योम *buffer = शून्य;
	sमाप_प्रकार len;

	अगर (!value || !size) अणु
		len = security_inode_माला_लोecurity(mnt_userns, inode, name,
						 &buffer, false);
		जाओ out_noalloc;
	पूर्ण

	len = security_inode_माला_लोecurity(mnt_userns, inode, name, &buffer,
					 true);
	अगर (len < 0)
		वापस len;
	अगर (size < len) अणु
		len = -दुस्फल;
		जाओ out;
	पूर्ण
	स_नकल(value, buffer, len);
out:
	kमुक्त(buffer);
out_noalloc:
	वापस len;
पूर्ण

/*
 * vfs_getxattr_alloc - allocate memory, अगर necessary, beक्रमe calling getxattr
 *
 * Allocate memory, अगर not alपढ़ोy allocated, or re-allocate correct size,
 * beक्रमe retrieving the extended attribute.
 *
 * Returns the result of alloc, अगर failed, or the getxattr operation.
 */
sमाप_प्रकार
vfs_getxattr_alloc(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		   स्थिर अक्षर *name, अक्षर **xattr_value, माप_प्रकार xattr_size,
		   gfp_t flags)
अणु
	स्थिर काष्ठा xattr_handler *handler;
	काष्ठा inode *inode = dentry->d_inode;
	अक्षर *value = *xattr_value;
	पूर्णांक error;

	error = xattr_permission(mnt_userns, inode, name, MAY_READ);
	अगर (error)
		वापस error;

	handler = xattr_resolve_name(inode, &name);
	अगर (IS_ERR(handler))
		वापस PTR_ERR(handler);
	अगर (!handler->get)
		वापस -EOPNOTSUPP;
	error = handler->get(handler, dentry, inode, name, शून्य, 0);
	अगर (error < 0)
		वापस error;

	अगर (!value || (error > xattr_size)) अणु
		value = kपुनः_स्मृति(*xattr_value, error + 1, flags);
		अगर (!value)
			वापस -ENOMEM;
		स_रखो(value, 0, error + 1);
	पूर्ण

	error = handler->get(handler, dentry, inode, name, value, error);
	*xattr_value = value;
	वापस error;
पूर्ण

sमाप_प्रकार
__vfs_getxattr(काष्ठा dentry *dentry, काष्ठा inode *inode, स्थिर अक्षर *name,
	       व्योम *value, माप_प्रकार size)
अणु
	स्थिर काष्ठा xattr_handler *handler;

	handler = xattr_resolve_name(inode, &name);
	अगर (IS_ERR(handler))
		वापस PTR_ERR(handler);
	अगर (!handler->get)
		वापस -EOPNOTSUPP;
	वापस handler->get(handler, dentry, inode, name, value, size);
पूर्ण
EXPORT_SYMBOL(__vfs_getxattr);

sमाप_प्रकार
vfs_getxattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
	     स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	पूर्णांक error;

	error = xattr_permission(mnt_userns, inode, name, MAY_READ);
	अगर (error)
		वापस error;

	error = security_inode_getxattr(dentry, name);
	अगर (error)
		वापस error;

	अगर (!म_भेदन(name, XATTR_SECURITY_PREFIX,
				XATTR_SECURITY_PREFIX_LEN)) अणु
		स्थिर अक्षर *suffix = name + XATTR_SECURITY_PREFIX_LEN;
		पूर्णांक ret = xattr_माला_लोecurity(mnt_userns, inode, suffix, value,
					    size);
		/*
		 * Only overग_लिखो the वापस value अगर a security module
		 * is actually active.
		 */
		अगर (ret == -EOPNOTSUPP)
			जाओ nolsm;
		वापस ret;
	पूर्ण
nolsm:
	वापस __vfs_getxattr(dentry, inode, name, value, size);
पूर्ण
EXPORT_SYMBOL_GPL(vfs_getxattr);

sमाप_प्रकार
vfs_listxattr(काष्ठा dentry *dentry, अक्षर *list, माप_प्रकार size)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	sमाप_प्रकार error;

	error = security_inode_listxattr(dentry);
	अगर (error)
		वापस error;
	अगर (inode->i_op->listxattr && (inode->i_opflags & IOP_XATTR)) अणु
		error = inode->i_op->listxattr(dentry, list, size);
	पूर्ण अन्यथा अणु
		error = security_inode_listsecurity(inode, list, size);
		अगर (size && error > size)
			error = -दुस्फल;
	पूर्ण
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(vfs_listxattr);

पूर्णांक
__vfs_हटाओxattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		  स्थिर अक्षर *name)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	स्थिर काष्ठा xattr_handler *handler;

	handler = xattr_resolve_name(inode, &name);
	अगर (IS_ERR(handler))
		वापस PTR_ERR(handler);
	अगर (!handler->set)
		वापस -EOPNOTSUPP;
	वापस handler->set(handler, mnt_userns, dentry, inode, name, शून्य, 0,
			    XATTR_REPLACE);
पूर्ण
EXPORT_SYMBOL(__vfs_हटाओxattr);

/**
 * __vfs_हटाओxattr_locked - set an extended attribute जबतक holding the inode
 * lock
 *
 *  @mnt_userns: user namespace of the mount of the target inode
 *  @dentry: object to perक्रमm setxattr on
 *  @name: name of xattr to हटाओ
 *  @delegated_inode: on वापस, will contain an inode poपूर्णांकer that
 *  a delegation was broken on, शून्य अगर none.
 */
पूर्णांक
__vfs_हटाओxattr_locked(काष्ठा user_namespace *mnt_userns,
			 काष्ठा dentry *dentry, स्थिर अक्षर *name,
			 काष्ठा inode **delegated_inode)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	पूर्णांक error;

	error = xattr_permission(mnt_userns, inode, name, MAY_WRITE);
	अगर (error)
		वापस error;

	error = security_inode_हटाओxattr(mnt_userns, dentry, name);
	अगर (error)
		जाओ out;

	error = try_अवरोध_deleg(inode, delegated_inode);
	अगर (error)
		जाओ out;

	error = __vfs_हटाओxattr(mnt_userns, dentry, name);

	अगर (!error) अणु
		fsnotअगरy_xattr(dentry);
		evm_inode_post_हटाओxattr(dentry, name);
	पूर्ण

out:
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(__vfs_हटाओxattr_locked);

पूर्णांक
vfs_हटाओxattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		स्थिर अक्षर *name)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	काष्ठा inode *delegated_inode = शून्य;
	पूर्णांक error;

retry_deleg:
	inode_lock(inode);
	error = __vfs_हटाओxattr_locked(mnt_userns, dentry,
					 name, &delegated_inode);
	inode_unlock(inode);

	अगर (delegated_inode) अणु
		error = अवरोध_deleg_रुको(&delegated_inode);
		अगर (!error)
			जाओ retry_deleg;
	पूर्ण

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(vfs_हटाओxattr);

/*
 * Extended attribute SET operations
 */
अटल दीर्घ
setxattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *d,
	 स्थिर अक्षर __user *name, स्थिर व्योम __user *value, माप_प्रकार size,
	 पूर्णांक flags)
अणु
	पूर्णांक error;
	व्योम *kvalue = शून्य;
	अक्षर kname[XATTR_NAME_MAX + 1];

	अगर (flags & ~(XATTR_CREATE|XATTR_REPLACE))
		वापस -EINVAL;

	error = म_नकलन_from_user(kname, name, माप(kname));
	अगर (error == 0 || error == माप(kname))
		error = -दुस्फल;
	अगर (error < 0)
		वापस error;

	अगर (size) अणु
		अगर (size > XATTR_SIZE_MAX)
			वापस -E2BIG;
		kvalue = kvदो_स्मृति(size, GFP_KERNEL);
		अगर (!kvalue)
			वापस -ENOMEM;
		अगर (copy_from_user(kvalue, value, size)) अणु
			error = -EFAULT;
			जाओ out;
		पूर्ण
		अगर ((म_भेद(kname, XATTR_NAME_POSIX_ACL_ACCESS) == 0) ||
		    (म_भेद(kname, XATTR_NAME_POSIX_ACL_DEFAULT) == 0))
			posix_acl_fix_xattr_from_user(mnt_userns, kvalue, size);
	पूर्ण

	error = vfs_setxattr(mnt_userns, d, kname, kvalue, size, flags);
out:
	kvमुक्त(kvalue);

	वापस error;
पूर्ण

अटल पूर्णांक path_setxattr(स्थिर अक्षर __user *pathname,
			 स्थिर अक्षर __user *name, स्थिर व्योम __user *value,
			 माप_प्रकार size, पूर्णांक flags, अचिन्हित पूर्णांक lookup_flags)
अणु
	काष्ठा path path;
	पूर्णांक error;

retry:
	error = user_path_at(AT_FDCWD, pathname, lookup_flags, &path);
	अगर (error)
		वापस error;
	error = mnt_want_ग_लिखो(path.mnt);
	अगर (!error) अणु
		error = setxattr(mnt_user_ns(path.mnt), path.dentry, name,
				 value, size, flags);
		mnt_drop_ग_लिखो(path.mnt);
	पूर्ण
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE5(setxattr, स्थिर अक्षर __user *, pathname,
		स्थिर अक्षर __user *, name, स्थिर व्योम __user *, value,
		माप_प्रकार, size, पूर्णांक, flags)
अणु
	वापस path_setxattr(pathname, name, value, size, flags, LOOKUP_FOLLOW);
पूर्ण

SYSCALL_DEFINE5(lsetxattr, स्थिर अक्षर __user *, pathname,
		स्थिर अक्षर __user *, name, स्थिर व्योम __user *, value,
		माप_प्रकार, size, पूर्णांक, flags)
अणु
	वापस path_setxattr(pathname, name, value, size, flags, 0);
पूर्ण

SYSCALL_DEFINE5(fsetxattr, पूर्णांक, fd, स्थिर अक्षर __user *, name,
		स्थिर व्योम __user *,value, माप_प्रकार, size, पूर्णांक, flags)
अणु
	काष्ठा fd f = fdget(fd);
	पूर्णांक error = -EBADF;

	अगर (!f.file)
		वापस error;
	audit_file(f.file);
	error = mnt_want_ग_लिखो_file(f.file);
	अगर (!error) अणु
		error = setxattr(file_mnt_user_ns(f.file),
				 f.file->f_path.dentry, name,
				 value, size, flags);
		mnt_drop_ग_लिखो_file(f.file);
	पूर्ण
	fdput(f);
	वापस error;
पूर्ण

/*
 * Extended attribute GET operations
 */
अटल sमाप_प्रकार
getxattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *d,
	 स्थिर अक्षर __user *name, व्योम __user *value, माप_प्रकार size)
अणु
	sमाप_प्रकार error;
	व्योम *kvalue = शून्य;
	अक्षर kname[XATTR_NAME_MAX + 1];

	error = म_नकलन_from_user(kname, name, माप(kname));
	अगर (error == 0 || error == माप(kname))
		error = -दुस्फल;
	अगर (error < 0)
		वापस error;

	अगर (size) अणु
		अगर (size > XATTR_SIZE_MAX)
			size = XATTR_SIZE_MAX;
		kvalue = kvzalloc(size, GFP_KERNEL);
		अगर (!kvalue)
			वापस -ENOMEM;
	पूर्ण

	error = vfs_getxattr(mnt_userns, d, kname, kvalue, size);
	अगर (error > 0) अणु
		अगर ((म_भेद(kname, XATTR_NAME_POSIX_ACL_ACCESS) == 0) ||
		    (म_भेद(kname, XATTR_NAME_POSIX_ACL_DEFAULT) == 0))
			posix_acl_fix_xattr_to_user(mnt_userns, kvalue, error);
		अगर (size && copy_to_user(value, kvalue, error))
			error = -EFAULT;
	पूर्ण अन्यथा अगर (error == -दुस्फल && size >= XATTR_SIZE_MAX) अणु
		/* The file प्रणाली tried to वापसed a value bigger
		   than XATTR_SIZE_MAX bytes. Not possible. */
		error = -E2BIG;
	पूर्ण

	kvमुक्त(kvalue);

	वापस error;
पूर्ण

अटल sमाप_प्रकार path_getxattr(स्थिर अक्षर __user *pathname,
			     स्थिर अक्षर __user *name, व्योम __user *value,
			     माप_प्रकार size, अचिन्हित पूर्णांक lookup_flags)
अणु
	काष्ठा path path;
	sमाप_प्रकार error;
retry:
	error = user_path_at(AT_FDCWD, pathname, lookup_flags, &path);
	अगर (error)
		वापस error;
	error = getxattr(mnt_user_ns(path.mnt), path.dentry, name, value, size);
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE4(getxattr, स्थिर अक्षर __user *, pathname,
		स्थिर अक्षर __user *, name, व्योम __user *, value, माप_प्रकार, size)
अणु
	वापस path_getxattr(pathname, name, value, size, LOOKUP_FOLLOW);
पूर्ण

SYSCALL_DEFINE4(lgetxattr, स्थिर अक्षर __user *, pathname,
		स्थिर अक्षर __user *, name, व्योम __user *, value, माप_प्रकार, size)
अणु
	वापस path_getxattr(pathname, name, value, size, 0);
पूर्ण

SYSCALL_DEFINE4(fgetxattr, पूर्णांक, fd, स्थिर अक्षर __user *, name,
		व्योम __user *, value, माप_प्रकार, size)
अणु
	काष्ठा fd f = fdget(fd);
	sमाप_प्रकार error = -EBADF;

	अगर (!f.file)
		वापस error;
	audit_file(f.file);
	error = getxattr(file_mnt_user_ns(f.file), f.file->f_path.dentry,
			 name, value, size);
	fdput(f);
	वापस error;
पूर्ण

/*
 * Extended attribute LIST operations
 */
अटल sमाप_प्रकार
listxattr(काष्ठा dentry *d, अक्षर __user *list, माप_प्रकार size)
अणु
	sमाप_प्रकार error;
	अक्षर *klist = शून्य;

	अगर (size) अणु
		अगर (size > XATTR_LIST_MAX)
			size = XATTR_LIST_MAX;
		klist = kvदो_स्मृति(size, GFP_KERNEL);
		अगर (!klist)
			वापस -ENOMEM;
	पूर्ण

	error = vfs_listxattr(d, klist, size);
	अगर (error > 0) अणु
		अगर (size && copy_to_user(list, klist, error))
			error = -EFAULT;
	पूर्ण अन्यथा अगर (error == -दुस्फल && size >= XATTR_LIST_MAX) अणु
		/* The file प्रणाली tried to वापसed a list bigger
		   than XATTR_LIST_MAX bytes. Not possible. */
		error = -E2BIG;
	पूर्ण

	kvमुक्त(klist);

	वापस error;
पूर्ण

अटल sमाप_प्रकार path_listxattr(स्थिर अक्षर __user *pathname, अक्षर __user *list,
			      माप_प्रकार size, अचिन्हित पूर्णांक lookup_flags)
अणु
	काष्ठा path path;
	sमाप_प्रकार error;
retry:
	error = user_path_at(AT_FDCWD, pathname, lookup_flags, &path);
	अगर (error)
		वापस error;
	error = listxattr(path.dentry, list, size);
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE3(listxattr, स्थिर अक्षर __user *, pathname, अक्षर __user *, list,
		माप_प्रकार, size)
अणु
	वापस path_listxattr(pathname, list, size, LOOKUP_FOLLOW);
पूर्ण

SYSCALL_DEFINE3(llistxattr, स्थिर अक्षर __user *, pathname, अक्षर __user *, list,
		माप_प्रकार, size)
अणु
	वापस path_listxattr(pathname, list, size, 0);
पूर्ण

SYSCALL_DEFINE3(flistxattr, पूर्णांक, fd, अक्षर __user *, list, माप_प्रकार, size)
अणु
	काष्ठा fd f = fdget(fd);
	sमाप_प्रकार error = -EBADF;

	अगर (!f.file)
		वापस error;
	audit_file(f.file);
	error = listxattr(f.file->f_path.dentry, list, size);
	fdput(f);
	वापस error;
पूर्ण

/*
 * Extended attribute REMOVE operations
 */
अटल दीर्घ
हटाओxattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *d,
	    स्थिर अक्षर __user *name)
अणु
	पूर्णांक error;
	अक्षर kname[XATTR_NAME_MAX + 1];

	error = म_नकलन_from_user(kname, name, माप(kname));
	अगर (error == 0 || error == माप(kname))
		error = -दुस्फल;
	अगर (error < 0)
		वापस error;

	वापस vfs_हटाओxattr(mnt_userns, d, kname);
पूर्ण

अटल पूर्णांक path_हटाओxattr(स्थिर अक्षर __user *pathname,
			    स्थिर अक्षर __user *name, अचिन्हित पूर्णांक lookup_flags)
अणु
	काष्ठा path path;
	पूर्णांक error;
retry:
	error = user_path_at(AT_FDCWD, pathname, lookup_flags, &path);
	अगर (error)
		वापस error;
	error = mnt_want_ग_लिखो(path.mnt);
	अगर (!error) अणु
		error = हटाओxattr(mnt_user_ns(path.mnt), path.dentry, name);
		mnt_drop_ग_लिखो(path.mnt);
	पूर्ण
	path_put(&path);
	अगर (retry_estale(error, lookup_flags)) अणु
		lookup_flags |= LOOKUP_REVAL;
		जाओ retry;
	पूर्ण
	वापस error;
पूर्ण

SYSCALL_DEFINE2(हटाओxattr, स्थिर अक्षर __user *, pathname,
		स्थिर अक्षर __user *, name)
अणु
	वापस path_हटाओxattr(pathname, name, LOOKUP_FOLLOW);
पूर्ण

SYSCALL_DEFINE2(lहटाओxattr, स्थिर अक्षर __user *, pathname,
		स्थिर अक्षर __user *, name)
अणु
	वापस path_हटाओxattr(pathname, name, 0);
पूर्ण

SYSCALL_DEFINE2(fहटाओxattr, पूर्णांक, fd, स्थिर अक्षर __user *, name)
अणु
	काष्ठा fd f = fdget(fd);
	पूर्णांक error = -EBADF;

	अगर (!f.file)
		वापस error;
	audit_file(f.file);
	error = mnt_want_ग_लिखो_file(f.file);
	अगर (!error) अणु
		error = हटाओxattr(file_mnt_user_ns(f.file),
				    f.file->f_path.dentry, name);
		mnt_drop_ग_लिखो_file(f.file);
	पूर्ण
	fdput(f);
	वापस error;
पूर्ण

/*
 * Combine the results of the list() operation from every xattr_handler in the
 * list.
 */
sमाप_प्रकार
generic_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	स्थिर काष्ठा xattr_handler *handler, **handlers = dentry->d_sb->s_xattr;
	अचिन्हित पूर्णांक size = 0;

	अगर (!buffer) अणु
		क्रम_each_xattr_handler(handlers, handler) अणु
			अगर (!handler->name ||
			    (handler->list && !handler->list(dentry)))
				जारी;
			size += म_माप(handler->name) + 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अक्षर *buf = buffer;
		माप_प्रकार len;

		क्रम_each_xattr_handler(handlers, handler) अणु
			अगर (!handler->name ||
			    (handler->list && !handler->list(dentry)))
				जारी;
			len = म_माप(handler->name);
			अगर (len + 1 > buffer_size)
				वापस -दुस्फल;
			स_नकल(buf, handler->name, len + 1);
			buf += len + 1;
			buffer_size -= len + 1;
		पूर्ण
		size = buf - buffer;
	पूर्ण
	वापस size;
पूर्ण
EXPORT_SYMBOL(generic_listxattr);

/**
 * xattr_full_name  -  Compute full attribute name from suffix
 *
 * @handler:	handler of the xattr_handler operation
 * @name:	name passed to the xattr_handler operation
 *
 * The get and set xattr handler operations are called with the reमुख्यder of
 * the attribute name after skipping the handler's prefix: क्रम example, "foo"
 * is passed to the get operation of a handler with prefix "user." to get
 * attribute "user.foo".  The full name is still "there" in the name though.
 *
 * Note: the list xattr handler operation when called from the vfs is passed a
 * शून्य name; some file प्रणालीs use this operation पूर्णांकernally, with varying
 * semantics.
 */
स्थिर अक्षर *xattr_full_name(स्थिर काष्ठा xattr_handler *handler,
			    स्थिर अक्षर *name)
अणु
	माप_प्रकार prefix_len = म_माप(xattr_prefix(handler));

	वापस name - prefix_len;
पूर्ण
EXPORT_SYMBOL(xattr_full_name);

/*
 * Allocate new xattr and copy in the value; but leave the name to callers.
 */
काष्ठा simple_xattr *simple_xattr_alloc(स्थिर व्योम *value, माप_प्रकार size)
अणु
	काष्ठा simple_xattr *new_xattr;
	माप_प्रकार len;

	/* wrap around? */
	len = माप(*new_xattr) + size;
	अगर (len < माप(*new_xattr))
		वापस शून्य;

	new_xattr = kvदो_स्मृति(len, GFP_KERNEL);
	अगर (!new_xattr)
		वापस शून्य;

	new_xattr->size = size;
	स_नकल(new_xattr->value, value, size);
	वापस new_xattr;
पूर्ण

/*
 * xattr GET operation क्रम in-memory/pseuकरो fileप्रणालीs
 */
पूर्णांक simple_xattr_get(काष्ठा simple_xattrs *xattrs, स्थिर अक्षर *name,
		     व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा simple_xattr *xattr;
	पूर्णांक ret = -ENODATA;

	spin_lock(&xattrs->lock);
	list_क्रम_each_entry(xattr, &xattrs->head, list) अणु
		अगर (म_भेद(name, xattr->name))
			जारी;

		ret = xattr->size;
		अगर (buffer) अणु
			अगर (size < xattr->size)
				ret = -दुस्फल;
			अन्यथा
				स_नकल(buffer, xattr->value, xattr->size);
		पूर्ण
		अवरोध;
	पूर्ण
	spin_unlock(&xattrs->lock);
	वापस ret;
पूर्ण

/**
 * simple_xattr_set - xattr SET operation क्रम in-memory/pseuकरो fileप्रणालीs
 * @xattrs: target simple_xattr list
 * @name: name of the extended attribute
 * @value: value of the xattr. If %शून्य, will हटाओ the attribute.
 * @size: size of the new xattr
 * @flags: %XATTR_अणुCREATE|REPLACEपूर्ण
 * @हटाओd_size: वापसs size of the हटाओd xattr, -1 अगर none हटाओd
 *
 * %XATTR_CREATE is set, the xattr shouldn't exist alपढ़ोy; otherwise fails
 * with -EEXIST.  If %XATTR_REPLACE is set, the xattr should exist;
 * otherwise, fails with -ENODATA.
 *
 * Returns 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक simple_xattr_set(काष्ठा simple_xattrs *xattrs, स्थिर अक्षर *name,
		     स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags,
		     sमाप_प्रकार *हटाओd_size)
अणु
	काष्ठा simple_xattr *xattr;
	काष्ठा simple_xattr *new_xattr = शून्य;
	पूर्णांक err = 0;

	अगर (हटाओd_size)
		*हटाओd_size = -1;

	/* value == शून्य means हटाओ */
	अगर (value) अणु
		new_xattr = simple_xattr_alloc(value, size);
		अगर (!new_xattr)
			वापस -ENOMEM;

		new_xattr->name = kstrdup(name, GFP_KERNEL);
		अगर (!new_xattr->name) अणु
			kvमुक्त(new_xattr);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	spin_lock(&xattrs->lock);
	list_क्रम_each_entry(xattr, &xattrs->head, list) अणु
		अगर (!म_भेद(name, xattr->name)) अणु
			अगर (flags & XATTR_CREATE) अणु
				xattr = new_xattr;
				err = -EEXIST;
			पूर्ण अन्यथा अगर (new_xattr) अणु
				list_replace(&xattr->list, &new_xattr->list);
				अगर (हटाओd_size)
					*हटाओd_size = xattr->size;
			पूर्ण अन्यथा अणु
				list_del(&xattr->list);
				अगर (हटाओd_size)
					*हटाओd_size = xattr->size;
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (flags & XATTR_REPLACE) अणु
		xattr = new_xattr;
		err = -ENODATA;
	पूर्ण अन्यथा अणु
		list_add(&new_xattr->list, &xattrs->head);
		xattr = शून्य;
	पूर्ण
out:
	spin_unlock(&xattrs->lock);
	अगर (xattr) अणु
		kमुक्त(xattr->name);
		kvमुक्त(xattr);
	पूर्ण
	वापस err;

पूर्ण

अटल bool xattr_is_trusted(स्थिर अक्षर *name)
अणु
	वापस !म_भेदन(name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN);
पूर्ण

अटल पूर्णांक xattr_list_one(अक्षर **buffer, sमाप_प्रकार *reमुख्यing_size,
			  स्थिर अक्षर *name)
अणु
	माप_प्रकार len = म_माप(name) + 1;
	अगर (*buffer) अणु
		अगर (*reमुख्यing_size < len)
			वापस -दुस्फल;
		स_नकल(*buffer, name, len);
		*buffer += len;
	पूर्ण
	*reमुख्यing_size -= len;
	वापस 0;
पूर्ण

/*
 * xattr LIST operation क्रम in-memory/pseuकरो fileप्रणालीs
 */
sमाप_प्रकार simple_xattr_list(काष्ठा inode *inode, काष्ठा simple_xattrs *xattrs,
			  अक्षर *buffer, माप_प्रकार size)
अणु
	bool trusted = capable(CAP_SYS_ADMIN);
	काष्ठा simple_xattr *xattr;
	sमाप_प्रकार reमुख्यing_size = size;
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_FS_POSIX_ACL
	अगर (IS_POSIXACL(inode)) अणु
		अगर (inode->i_acl) अणु
			err = xattr_list_one(&buffer, &reमुख्यing_size,
					     XATTR_NAME_POSIX_ACL_ACCESS);
			अगर (err)
				वापस err;
		पूर्ण
		अगर (inode->i_शेष_acl) अणु
			err = xattr_list_one(&buffer, &reमुख्यing_size,
					     XATTR_NAME_POSIX_ACL_DEFAULT);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	spin_lock(&xattrs->lock);
	list_क्रम_each_entry(xattr, &xattrs->head, list) अणु
		/* skip "trusted." attributes क्रम unprivileged callers */
		अगर (!trusted && xattr_is_trusted(xattr->name))
			जारी;

		err = xattr_list_one(&buffer, &reमुख्यing_size, xattr->name);
		अगर (err)
			अवरोध;
	पूर्ण
	spin_unlock(&xattrs->lock);

	वापस err ? err : size - reमुख्यing_size;
पूर्ण

/*
 * Adds an extended attribute to the list
 */
व्योम simple_xattr_list_add(काष्ठा simple_xattrs *xattrs,
			   काष्ठा simple_xattr *new_xattr)
अणु
	spin_lock(&xattrs->lock);
	list_add(&new_xattr->list, &xattrs->head);
	spin_unlock(&xattrs->lock);
पूर्ण
