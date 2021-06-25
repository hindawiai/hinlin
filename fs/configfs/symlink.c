<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * symlink.c - operations क्रम configfs symlinks.
 *
 * Based on sysfs:
 * 	sysfs is Copyright (C) 2001, 2002, 2003 Patrick Mochel
 *
 * configfs Copyright (C) 2005 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>

#समावेश <linux/configfs.h>
#समावेश "configfs_internal.h"

/* Protects attachments of new symlinks */
DEFINE_MUTEX(configfs_symlink_mutex);

अटल पूर्णांक item_depth(काष्ठा config_item * item)
अणु
	काष्ठा config_item * p = item;
	पूर्णांक depth = 0;
	करो अणु depth++; पूर्ण जबतक ((p = p->ci_parent) && !configfs_is_root(p));
	वापस depth;
पूर्ण

अटल पूर्णांक item_path_length(काष्ठा config_item * item)
अणु
	काष्ठा config_item * p = item;
	पूर्णांक length = 1;
	करो अणु
		length += म_माप(config_item_name(p)) + 1;
		p = p->ci_parent;
	पूर्ण जबतक (p && !configfs_is_root(p));
	वापस length;
पूर्ण

अटल व्योम fill_item_path(काष्ठा config_item * item, अक्षर * buffer, पूर्णांक length)
अणु
	काष्ठा config_item * p;

	--length;
	क्रम (p = item; p && !configfs_is_root(p); p = p->ci_parent) अणु
		पूर्णांक cur = म_माप(config_item_name(p));

		/* back up enough to prपूर्णांक this bus id with '/' */
		length -= cur;
		स_नकल(buffer + length, config_item_name(p), cur);
		*(buffer + --length) = '/';
	पूर्ण
पूर्ण

अटल पूर्णांक configfs_get_target_path(काष्ठा config_item *item,
		काष्ठा config_item *target, अक्षर *path)
अणु
	पूर्णांक depth, size;
	अक्षर *s;

	depth = item_depth(item);
	size = item_path_length(target) + depth * 3 - 1;
	अगर (size > PATH_MAX)
		वापस -ENAMETOOLONG;

	pr_debug("%s: depth = %d, size = %d\n", __func__, depth, size);

	क्रम (s = path; depth--; s += 3)
		म_नकल(s,"../");

	fill_item_path(target, path, size);
	pr_debug("%s: path = '%s'\n", __func__, path);
	वापस 0;
पूर्ण

अटल पूर्णांक create_link(काष्ठा config_item *parent_item,
		       काष्ठा config_item *item,
		       काष्ठा dentry *dentry)
अणु
	काष्ठा configfs_dirent *target_sd = item->ci_dentry->d_fsdata;
	अक्षर *body;
	पूर्णांक ret;

	अगर (!configfs_dirent_is_पढ़ोy(target_sd))
		वापस -ENOENT;

	body = kzalloc(PAGE_SIZE, GFP_KERNEL);
	अगर (!body)
		वापस -ENOMEM;

	configfs_get(target_sd);
	spin_lock(&configfs_dirent_lock);
	अगर (target_sd->s_type & CONFIGFS_USET_DROPPING) अणु
		spin_unlock(&configfs_dirent_lock);
		configfs_put(target_sd);
		kमुक्त(body);
		वापस -ENOENT;
	पूर्ण
	target_sd->s_links++;
	spin_unlock(&configfs_dirent_lock);
	ret = configfs_get_target_path(parent_item, item, body);
	अगर (!ret)
		ret = configfs_create_link(target_sd, parent_item->ci_dentry,
					   dentry, body);
	अगर (ret) अणु
		spin_lock(&configfs_dirent_lock);
		target_sd->s_links--;
		spin_unlock(&configfs_dirent_lock);
		configfs_put(target_sd);
		kमुक्त(body);
	पूर्ण
	वापस ret;
पूर्ण


अटल पूर्णांक get_target(स्थिर अक्षर *symname, काष्ठा path *path,
		      काष्ठा config_item **target, काष्ठा super_block *sb)
अणु
	पूर्णांक ret;

	ret = kern_path(symname, LOOKUP_FOLLOW|LOOKUP_सूचीECTORY, path);
	अगर (!ret) अणु
		अगर (path->dentry->d_sb == sb) अणु
			*target = configfs_get_config_item(path->dentry);
			अगर (!*target) अणु
				ret = -ENOENT;
				path_put(path);
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = -EPERM;
			path_put(path);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण


पूर्णांक configfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	पूर्णांक ret;
	काष्ठा path path;
	काष्ठा configfs_dirent *sd;
	काष्ठा config_item *parent_item;
	काष्ठा config_item *target_item = शून्य;
	स्थिर काष्ठा config_item_type *type;

	sd = dentry->d_parent->d_fsdata;
	/*
	 * Fake invisibility अगर dir beदीर्घs to a group/शेष groups hierarchy
	 * being attached
	 */
	अगर (!configfs_dirent_is_पढ़ोy(sd))
		वापस -ENOENT;

	parent_item = configfs_get_config_item(dentry->d_parent);
	type = parent_item->ci_type;

	ret = -EPERM;
	अगर (!type || !type->ct_item_ops ||
	    !type->ct_item_ops->allow_link)
		जाओ out_put;

	/*
	 * This is really sick.  What they wanted was a hybrid of
	 * link(2) and symlink(2) - they wanted the target resolved
	 * at syscall समय (as link(2) would've करोne), be a directory
	 * (which link(2) would've refused to करो) *AND* be a deep
	 * fucking magic, making the target busy from सूची_हटाओ POV.
	 * symlink(2) is nothing of that sort, and the locking it
	 * माला_लो matches the normal symlink(2) semantics.  Without
	 * attempts to resolve the target (which might very well
	 * not even exist yet) करोne prior to locking the parent
	 * directory.  This perversion, OTOH, needs to resolve
	 * the target, which would lead to obvious deadlocks अगर
	 * attempted with any directories locked.
	 *
	 * Unक्रमtunately, that garbage is userland ABI and we should've
	 * said "no" back in 2005.  Too late now, so we get to
	 * play very ugly games with locking.
	 *
	 * Try *ANYTHING* of that sort in new code, and you will
	 * really regret it.  Just ask yourself - what could a BOFH
	 * करो to me and करो I want to find it out first-hand?
	 *
	 *  AV, a thoroughly annoyed bastard.
	 */
	inode_unlock(dir);
	ret = get_target(symname, &path, &target_item, dentry->d_sb);
	inode_lock(dir);
	अगर (ret)
		जाओ out_put;

	अगर (dentry->d_inode || d_unhashed(dentry))
		ret = -EEXIST;
	अन्यथा
		ret = inode_permission(&init_user_ns, dir,
				       MAY_WRITE | MAY_EXEC);
	अगर (!ret)
		ret = type->ct_item_ops->allow_link(parent_item, target_item);
	अगर (!ret) अणु
		mutex_lock(&configfs_symlink_mutex);
		ret = create_link(parent_item, target_item, dentry);
		mutex_unlock(&configfs_symlink_mutex);
		अगर (ret && type->ct_item_ops->drop_link)
			type->ct_item_ops->drop_link(parent_item,
						     target_item);
	पूर्ण

	config_item_put(target_item);
	path_put(&path);

out_put:
	config_item_put(parent_item);
	वापस ret;
पूर्ण

पूर्णांक configfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा configfs_dirent *sd = dentry->d_fsdata, *target_sd;
	काष्ठा config_item *parent_item;
	स्थिर काष्ठा config_item_type *type;
	पूर्णांक ret;

	ret = -EPERM;  /* What lack-of-symlink वापसs */
	अगर (!(sd->s_type & CONFIGFS_ITEM_LINK))
		जाओ out;

	target_sd = sd->s_element;

	parent_item = configfs_get_config_item(dentry->d_parent);
	type = parent_item->ci_type;

	spin_lock(&configfs_dirent_lock);
	list_del_init(&sd->s_sibling);
	spin_unlock(&configfs_dirent_lock);
	configfs_drop_dentry(sd, dentry->d_parent);
	dput(dentry);
	configfs_put(sd);

	/*
	 * drop_link() must be called beक्रमe
	 * decrementing target's ->s_links, so that the order of
	 * drop_link(this, target) and drop_item(target) is preserved.
	 */
	अगर (type && type->ct_item_ops &&
	    type->ct_item_ops->drop_link)
		type->ct_item_ops->drop_link(parent_item,
					       target_sd->s_element);

	spin_lock(&configfs_dirent_lock);
	target_sd->s_links--;
	spin_unlock(&configfs_dirent_lock);
	configfs_put(target_sd);

	config_item_put(parent_item);

	ret = 0;

out:
	वापस ret;
पूर्ण

स्थिर काष्ठा inode_operations configfs_symlink_inode_operations = अणु
	.get_link = simple_get_link,
	.setattr = configfs_setattr,
पूर्ण;

