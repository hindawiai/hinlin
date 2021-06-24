<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/kernfs/inode.c - kernfs inode implementation
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007, 2013 Tejun Heo <tj@kernel.org>
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/xattr.h>
#समावेश <linux/security.h>

#समावेश "kernfs-internal.h"

अटल स्थिर काष्ठा address_space_operations kernfs_aops = अणु
	.पढ़ोpage	= simple_पढ़ोpage,
	.ग_लिखो_begin	= simple_ग_लिखो_begin,
	.ग_लिखो_end	= simple_ग_लिखो_end,
पूर्ण;

अटल स्थिर काष्ठा inode_operations kernfs_iops = अणु
	.permission	= kernfs_iop_permission,
	.setattr	= kernfs_iop_setattr,
	.getattr	= kernfs_iop_getattr,
	.listxattr	= kernfs_iop_listxattr,
पूर्ण;

अटल काष्ठा kernfs_iattrs *__kernfs_iattrs(काष्ठा kernfs_node *kn, पूर्णांक alloc)
अणु
	अटल DEFINE_MUTEX(iattr_mutex);
	काष्ठा kernfs_iattrs *ret;

	mutex_lock(&iattr_mutex);

	अगर (kn->iattr || !alloc)
		जाओ out_unlock;

	kn->iattr = kmem_cache_zalloc(kernfs_iattrs_cache, GFP_KERNEL);
	अगर (!kn->iattr)
		जाओ out_unlock;

	/* assign शेष attributes */
	kn->iattr->ia_uid = GLOBAL_ROOT_UID;
	kn->iattr->ia_gid = GLOBAL_ROOT_GID;

	kसमय_get_real_ts64(&kn->iattr->ia_aसमय);
	kn->iattr->ia_mसमय = kn->iattr->ia_aसमय;
	kn->iattr->ia_स_समय = kn->iattr->ia_aसमय;

	simple_xattrs_init(&kn->iattr->xattrs);
	atomic_set(&kn->iattr->nr_user_xattrs, 0);
	atomic_set(&kn->iattr->user_xattr_size, 0);
out_unlock:
	ret = kn->iattr;
	mutex_unlock(&iattr_mutex);
	वापस ret;
पूर्ण

अटल काष्ठा kernfs_iattrs *kernfs_iattrs(काष्ठा kernfs_node *kn)
अणु
	वापस __kernfs_iattrs(kn, 1);
पूर्ण

अटल काष्ठा kernfs_iattrs *kernfs_iattrs_noalloc(काष्ठा kernfs_node *kn)
अणु
	वापस __kernfs_iattrs(kn, 0);
पूर्ण

पूर्णांक __kernfs_setattr(काष्ठा kernfs_node *kn, स्थिर काष्ठा iattr *iattr)
अणु
	काष्ठा kernfs_iattrs *attrs;
	अचिन्हित पूर्णांक ia_valid = iattr->ia_valid;

	attrs = kernfs_iattrs(kn);
	अगर (!attrs)
		वापस -ENOMEM;

	अगर (ia_valid & ATTR_UID)
		attrs->ia_uid = iattr->ia_uid;
	अगर (ia_valid & ATTR_GID)
		attrs->ia_gid = iattr->ia_gid;
	अगर (ia_valid & ATTR_ATIME)
		attrs->ia_aसमय = iattr->ia_aसमय;
	अगर (ia_valid & ATTR_MTIME)
		attrs->ia_mसमय = iattr->ia_mसमय;
	अगर (ia_valid & ATTR_CTIME)
		attrs->ia_स_समय = iattr->ia_स_समय;
	अगर (ia_valid & ATTR_MODE)
		kn->mode = iattr->ia_mode;
	वापस 0;
पूर्ण

/**
 * kernfs_setattr - set iattr on a node
 * @kn: target node
 * @iattr: iattr to set
 *
 * Returns 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक kernfs_setattr(काष्ठा kernfs_node *kn, स्थिर काष्ठा iattr *iattr)
अणु
	पूर्णांक ret;

	mutex_lock(&kernfs_mutex);
	ret = __kernfs_setattr(kn, iattr);
	mutex_unlock(&kernfs_mutex);
	वापस ret;
पूर्ण

पूर्णांक kernfs_iop_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		       काष्ठा iattr *iattr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा kernfs_node *kn = inode->i_निजी;
	पूर्णांक error;

	अगर (!kn)
		वापस -EINVAL;

	mutex_lock(&kernfs_mutex);
	error = setattr_prepare(&init_user_ns, dentry, iattr);
	अगर (error)
		जाओ out;

	error = __kernfs_setattr(kn, iattr);
	अगर (error)
		जाओ out;

	/* this ignores size changes */
	setattr_copy(&init_user_ns, inode, iattr);

out:
	mutex_unlock(&kernfs_mutex);
	वापस error;
पूर्ण

sमाप_प्रकार kernfs_iop_listxattr(काष्ठा dentry *dentry, अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा kernfs_node *kn = kernfs_dentry_node(dentry);
	काष्ठा kernfs_iattrs *attrs;

	attrs = kernfs_iattrs(kn);
	अगर (!attrs)
		वापस -ENOMEM;

	वापस simple_xattr_list(d_inode(dentry), &attrs->xattrs, buf, size);
पूर्ण

अटल अंतरभूत व्योम set_शेष_inode_attr(काष्ठा inode *inode, umode_t mode)
अणु
	inode->i_mode = mode;
	inode->i_aसमय = inode->i_mसमय =
		inode->i_स_समय = current_समय(inode);
पूर्ण

अटल अंतरभूत व्योम set_inode_attr(काष्ठा inode *inode,
				  काष्ठा kernfs_iattrs *attrs)
अणु
	inode->i_uid = attrs->ia_uid;
	inode->i_gid = attrs->ia_gid;
	inode->i_aसमय = attrs->ia_aसमय;
	inode->i_mसमय = attrs->ia_mसमय;
	inode->i_स_समय = attrs->ia_स_समय;
पूर्ण

अटल व्योम kernfs_refresh_inode(काष्ठा kernfs_node *kn, काष्ठा inode *inode)
अणु
	काष्ठा kernfs_iattrs *attrs = kn->iattr;

	inode->i_mode = kn->mode;
	अगर (attrs)
		/*
		 * kernfs_node has non-शेष attributes get them from
		 * persistent copy in kernfs_node.
		 */
		set_inode_attr(inode, attrs);

	अगर (kernfs_type(kn) == KERNFS_सूची)
		set_nlink(inode, kn->dir.subdirs + 2);
पूर्ण

पूर्णांक kernfs_iop_getattr(काष्ठा user_namespace *mnt_userns,
		       स्थिर काष्ठा path *path, काष्ठा kstat *stat,
		       u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा kernfs_node *kn = inode->i_निजी;

	mutex_lock(&kernfs_mutex);
	kernfs_refresh_inode(kn, inode);
	mutex_unlock(&kernfs_mutex);

	generic_fillattr(&init_user_ns, inode, stat);
	वापस 0;
पूर्ण

अटल व्योम kernfs_init_inode(काष्ठा kernfs_node *kn, काष्ठा inode *inode)
अणु
	kernfs_get(kn);
	inode->i_निजी = kn;
	inode->i_mapping->a_ops = &kernfs_aops;
	inode->i_op = &kernfs_iops;
	inode->i_generation = kernfs_gen(kn);

	set_शेष_inode_attr(inode, kn->mode);
	kernfs_refresh_inode(kn, inode);

	/* initialize inode according to type */
	चयन (kernfs_type(kn)) अणु
	हाल KERNFS_सूची:
		inode->i_op = &kernfs_dir_iops;
		inode->i_fop = &kernfs_dir_fops;
		अगर (kn->flags & KERNFS_EMPTY_सूची)
			make_empty_dir_inode(inode);
		अवरोध;
	हाल KERNFS_खाता:
		inode->i_size = kn->attr.size;
		inode->i_fop = &kernfs_file_fops;
		अवरोध;
	हाल KERNFS_LINK:
		inode->i_op = &kernfs_symlink_iops;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	unlock_new_inode(inode);
पूर्ण

/**
 *	kernfs_get_inode - get inode क्रम kernfs_node
 *	@sb: super block
 *	@kn: kernfs_node to allocate inode क्रम
 *
 *	Get inode क्रम @kn.  If such inode करोesn't exist, a new inode is
 *	allocated and basics are initialized.  New inode is वापसed
 *	locked.
 *
 *	LOCKING:
 *	Kernel thपढ़ो context (may sleep).
 *
 *	RETURNS:
 *	Poपूर्णांकer to allocated inode on success, शून्य on failure.
 */
काष्ठा inode *kernfs_get_inode(काष्ठा super_block *sb, काष्ठा kernfs_node *kn)
अणु
	काष्ठा inode *inode;

	inode = iget_locked(sb, kernfs_ino(kn));
	अगर (inode && (inode->i_state & I_NEW))
		kernfs_init_inode(kn, inode);

	वापस inode;
पूर्ण

/*
 * The kernfs_node serves as both an inode and a directory entry क्रम
 * kernfs.  To prevent the kernfs inode numbers from being मुक्तd
 * prematurely we take a reference to kernfs_node from the kernfs inode.  A
 * super_operations.evict_inode() implementation is needed to drop that
 * reference upon inode deकाष्ठाion.
 */
व्योम kernfs_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा kernfs_node *kn = inode->i_निजी;

	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	kernfs_put(kn);
पूर्ण

पूर्णांक kernfs_iop_permission(काष्ठा user_namespace *mnt_userns,
			  काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा kernfs_node *kn;

	अगर (mask & MAY_NOT_BLOCK)
		वापस -ECHILD;

	kn = inode->i_निजी;

	mutex_lock(&kernfs_mutex);
	kernfs_refresh_inode(kn, inode);
	mutex_unlock(&kernfs_mutex);

	वापस generic_permission(&init_user_ns, inode, mask);
पूर्ण

पूर्णांक kernfs_xattr_get(काष्ठा kernfs_node *kn, स्थिर अक्षर *name,
		     व्योम *value, माप_प्रकार size)
अणु
	काष्ठा kernfs_iattrs *attrs = kernfs_iattrs_noalloc(kn);
	अगर (!attrs)
		वापस -ENODATA;

	वापस simple_xattr_get(&attrs->xattrs, name, value, size);
पूर्ण

पूर्णांक kernfs_xattr_set(काष्ठा kernfs_node *kn, स्थिर अक्षर *name,
		     स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा kernfs_iattrs *attrs = kernfs_iattrs(kn);
	अगर (!attrs)
		वापस -ENOMEM;

	वापस simple_xattr_set(&attrs->xattrs, name, value, size, flags, शून्य);
पूर्ण

अटल पूर्णांक kernfs_vfs_xattr_get(स्थिर काष्ठा xattr_handler *handler,
				काष्ठा dentry *unused, काष्ठा inode *inode,
				स्थिर अक्षर *suffix, व्योम *value, माप_प्रकार size)
अणु
	स्थिर अक्षर *name = xattr_full_name(handler, suffix);
	काष्ठा kernfs_node *kn = inode->i_निजी;

	वापस kernfs_xattr_get(kn, name, value, size);
पूर्ण

अटल पूर्णांक kernfs_vfs_xattr_set(स्थिर काष्ठा xattr_handler *handler,
				काष्ठा user_namespace *mnt_userns,
				काष्ठा dentry *unused, काष्ठा inode *inode,
				स्थिर अक्षर *suffix, स्थिर व्योम *value,
				माप_प्रकार size, पूर्णांक flags)
अणु
	स्थिर अक्षर *name = xattr_full_name(handler, suffix);
	काष्ठा kernfs_node *kn = inode->i_निजी;

	वापस kernfs_xattr_set(kn, name, value, size, flags);
पूर्ण

अटल पूर्णांक kernfs_vfs_user_xattr_add(काष्ठा kernfs_node *kn,
				     स्थिर अक्षर *full_name,
				     काष्ठा simple_xattrs *xattrs,
				     स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	atomic_t *sz = &kn->iattr->user_xattr_size;
	atomic_t *nr = &kn->iattr->nr_user_xattrs;
	sमाप_प्रकार हटाओd_size;
	पूर्णांक ret;

	अगर (atomic_inc_वापस(nr) > KERNFS_MAX_USER_XATTRS) अणु
		ret = -ENOSPC;
		जाओ dec_count_out;
	पूर्ण

	अगर (atomic_add_वापस(size, sz) > KERNFS_USER_XATTR_SIZE_LIMIT) अणु
		ret = -ENOSPC;
		जाओ dec_size_out;
	पूर्ण

	ret = simple_xattr_set(xattrs, full_name, value, size, flags,
			       &हटाओd_size);

	अगर (!ret && हटाओd_size >= 0)
		size = हटाओd_size;
	अन्यथा अगर (!ret)
		वापस 0;
dec_size_out:
	atomic_sub(size, sz);
dec_count_out:
	atomic_dec(nr);
	वापस ret;
पूर्ण

अटल पूर्णांक kernfs_vfs_user_xattr_rm(काष्ठा kernfs_node *kn,
				    स्थिर अक्षर *full_name,
				    काष्ठा simple_xattrs *xattrs,
				    स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	atomic_t *sz = &kn->iattr->user_xattr_size;
	atomic_t *nr = &kn->iattr->nr_user_xattrs;
	sमाप_प्रकार हटाओd_size;
	पूर्णांक ret;

	ret = simple_xattr_set(xattrs, full_name, value, size, flags,
			       &हटाओd_size);

	अगर (हटाओd_size >= 0) अणु
		atomic_sub(हटाओd_size, sz);
		atomic_dec(nr);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kernfs_vfs_user_xattr_set(स्थिर काष्ठा xattr_handler *handler,
				     काष्ठा user_namespace *mnt_userns,
				     काष्ठा dentry *unused, काष्ठा inode *inode,
				     स्थिर अक्षर *suffix, स्थिर व्योम *value,
				     माप_प्रकार size, पूर्णांक flags)
अणु
	स्थिर अक्षर *full_name = xattr_full_name(handler, suffix);
	काष्ठा kernfs_node *kn = inode->i_निजी;
	काष्ठा kernfs_iattrs *attrs;

	अगर (!(kernfs_root(kn)->flags & KERNFS_ROOT_SUPPORT_USER_XATTR))
		वापस -EOPNOTSUPP;

	attrs = kernfs_iattrs(kn);
	अगर (!attrs)
		वापस -ENOMEM;

	अगर (value)
		वापस kernfs_vfs_user_xattr_add(kn, full_name, &attrs->xattrs,
						 value, size, flags);
	अन्यथा
		वापस kernfs_vfs_user_xattr_rm(kn, full_name, &attrs->xattrs,
						value, size, flags);

पूर्ण

अटल स्थिर काष्ठा xattr_handler kernfs_trusted_xattr_handler = अणु
	.prefix = XATTR_TRUSTED_PREFIX,
	.get = kernfs_vfs_xattr_get,
	.set = kernfs_vfs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler kernfs_security_xattr_handler = अणु
	.prefix = XATTR_SECURITY_PREFIX,
	.get = kernfs_vfs_xattr_get,
	.set = kernfs_vfs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler kernfs_user_xattr_handler = अणु
	.prefix = XATTR_USER_PREFIX,
	.get = kernfs_vfs_xattr_get,
	.set = kernfs_vfs_user_xattr_set,
पूर्ण;

स्थिर काष्ठा xattr_handler *kernfs_xattr_handlers[] = अणु
	&kernfs_trusted_xattr_handler,
	&kernfs_security_xattr_handler,
	&kernfs_user_xattr_handler,
	शून्य
पूर्ण;
