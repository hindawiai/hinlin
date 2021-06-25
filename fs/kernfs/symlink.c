<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/kernfs/symlink.c - kernfs symlink implementation
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007, 2013 Tejun Heo <tj@kernel.org>
 */

#समावेश <linux/fs.h>
#समावेश <linux/gfp.h>
#समावेश <linux/namei.h>

#समावेश "kernfs-internal.h"

/**
 * kernfs_create_link - create a symlink
 * @parent: directory to create the symlink in
 * @name: name of the symlink
 * @target: target node क्रम the symlink to poपूर्णांक to
 *
 * Returns the created node on success, ERR_PTR() value on error.
 * Ownership of the link matches ownership of the target.
 */
काष्ठा kernfs_node *kernfs_create_link(काष्ठा kernfs_node *parent,
				       स्थिर अक्षर *name,
				       काष्ठा kernfs_node *target)
अणु
	काष्ठा kernfs_node *kn;
	पूर्णांक error;
	kuid_t uid = GLOBAL_ROOT_UID;
	kgid_t gid = GLOBAL_ROOT_GID;

	अगर (target->iattr) अणु
		uid = target->iattr->ia_uid;
		gid = target->iattr->ia_gid;
	पूर्ण

	kn = kernfs_new_node(parent, name, S_IFLNK|S_IRWXUGO, uid, gid,
			     KERNFS_LINK);
	अगर (!kn)
		वापस ERR_PTR(-ENOMEM);

	अगर (kernfs_ns_enabled(parent))
		kn->ns = target->ns;
	kn->symlink.target_kn = target;
	kernfs_get(target);	/* ref owned by symlink */

	error = kernfs_add_one(kn);
	अगर (!error)
		वापस kn;

	kernfs_put(kn);
	वापस ERR_PTR(error);
पूर्ण

अटल पूर्णांक kernfs_get_target_path(काष्ठा kernfs_node *parent,
				  काष्ठा kernfs_node *target, अक्षर *path)
अणु
	काष्ठा kernfs_node *base, *kn;
	अक्षर *s = path;
	पूर्णांक len = 0;

	/* go up to the root, stop at the base */
	base = parent;
	जबतक (base->parent) अणु
		kn = target->parent;
		जबतक (kn->parent && base != kn)
			kn = kn->parent;

		अगर (base == kn)
			अवरोध;

		अगर ((s - path) + 3 >= PATH_MAX)
			वापस -ENAMETOOLONG;

		म_नकल(s, "../");
		s += 3;
		base = base->parent;
	पूर्ण

	/* determine end of target string क्रम reverse fillup */
	kn = target;
	जबतक (kn->parent && kn != base) अणु
		len += म_माप(kn->name) + 1;
		kn = kn->parent;
	पूर्ण

	/* check limits */
	अगर (len < 2)
		वापस -EINVAL;
	len--;
	अगर ((s - path) + len >= PATH_MAX)
		वापस -ENAMETOOLONG;

	/* reverse fillup of target string from target to base */
	kn = target;
	जबतक (kn->parent && kn != base) अणु
		पूर्णांक slen = म_माप(kn->name);

		len -= slen;
		स_नकल(s + len, kn->name, slen);
		अगर (len)
			s[--len] = '/';

		kn = kn->parent;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kernfs_getlink(काष्ठा inode *inode, अक्षर *path)
अणु
	काष्ठा kernfs_node *kn = inode->i_निजी;
	काष्ठा kernfs_node *parent = kn->parent;
	काष्ठा kernfs_node *target = kn->symlink.target_kn;
	पूर्णांक error;

	mutex_lock(&kernfs_mutex);
	error = kernfs_get_target_path(parent, target, path);
	mutex_unlock(&kernfs_mutex);

	वापस error;
पूर्ण

अटल स्थिर अक्षर *kernfs_iop_get_link(काष्ठा dentry *dentry,
				       काष्ठा inode *inode,
				       काष्ठा delayed_call *करोne)
अणु
	अक्षर *body;
	पूर्णांक error;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);
	body = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!body)
		वापस ERR_PTR(-ENOMEM);
	error = kernfs_getlink(inode, body);
	अगर (unlikely(error < 0)) अणु
		kमुक्त(body);
		वापस ERR_PTR(error);
	पूर्ण
	set_delayed_call(करोne, kमुक्त_link, body);
	वापस body;
पूर्ण

स्थिर काष्ठा inode_operations kernfs_symlink_iops = अणु
	.listxattr	= kernfs_iop_listxattr,
	.get_link	= kernfs_iop_get_link,
	.setattr	= kernfs_iop_setattr,
	.getattr	= kernfs_iop_getattr,
	.permission	= kernfs_iop_permission,
पूर्ण;
