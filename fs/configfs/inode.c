<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * inode.c - basic inode and dentry operations.
 *
 * Based on sysfs:
 * 	sysfs is Copyright (C) 2001, 2002, 2003 Patrick Mochel
 *
 * configfs Copyright (C) 2005 Oracle.  All rights reserved.
 *
 * Please see Documentation/fileप्रणालीs/configfs.rst क्रम more
 * inक्रमmation.
 */

#अघोषित DEBUG

#समावेश <linux/pagemap.h>
#समावेश <linux/namei.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/capability.h>
#समावेश <linux/sched.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/slab.h>

#समावेश <linux/configfs.h>
#समावेश "configfs_internal.h"

#अगर_घोषित CONFIG_LOCKDEP
अटल काष्ठा lock_class_key शेष_group_class[MAX_LOCK_DEPTH];
#पूर्ण_अगर

अटल स्थिर काष्ठा address_space_operations configfs_aops = अणु
	.पढ़ोpage	= simple_पढ़ोpage,
	.ग_लिखो_begin	= simple_ग_लिखो_begin,
	.ग_लिखो_end	= simple_ग_लिखो_end,
पूर्ण;

अटल स्थिर काष्ठा inode_operations configfs_inode_operations =अणु
	.setattr	= configfs_setattr,
पूर्ण;

पूर्णांक configfs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		     काष्ठा iattr *iattr)
अणु
	काष्ठा inode * inode = d_inode(dentry);
	काष्ठा configfs_dirent * sd = dentry->d_fsdata;
	काष्ठा iattr * sd_iattr;
	अचिन्हित पूर्णांक ia_valid = iattr->ia_valid;
	पूर्णांक error;

	अगर (!sd)
		वापस -EINVAL;

	sd_iattr = sd->s_iattr;
	अगर (!sd_iattr) अणु
		/* setting attributes क्रम the first समय, allocate now */
		sd_iattr = kzalloc(माप(काष्ठा iattr), GFP_KERNEL);
		अगर (!sd_iattr)
			वापस -ENOMEM;
		/* assign शेष attributes */
		sd_iattr->ia_mode = sd->s_mode;
		sd_iattr->ia_uid = GLOBAL_ROOT_UID;
		sd_iattr->ia_gid = GLOBAL_ROOT_GID;
		sd_iattr->ia_aसमय = sd_iattr->ia_mसमय =
			sd_iattr->ia_स_समय = current_समय(inode);
		sd->s_iattr = sd_iattr;
	पूर्ण
	/* attributes were changed atleast once in past */

	error = simple_setattr(mnt_userns, dentry, iattr);
	अगर (error)
		वापस error;

	अगर (ia_valid & ATTR_UID)
		sd_iattr->ia_uid = iattr->ia_uid;
	अगर (ia_valid & ATTR_GID)
		sd_iattr->ia_gid = iattr->ia_gid;
	अगर (ia_valid & ATTR_ATIME)
		sd_iattr->ia_aसमय = iattr->ia_aसमय;
	अगर (ia_valid & ATTR_MTIME)
		sd_iattr->ia_mसमय = iattr->ia_mसमय;
	अगर (ia_valid & ATTR_CTIME)
		sd_iattr->ia_स_समय = iattr->ia_स_समय;
	अगर (ia_valid & ATTR_MODE) अणु
		umode_t mode = iattr->ia_mode;

		अगर (!in_group_p(inode->i_gid) && !capable(CAP_FSETID))
			mode &= ~S_ISGID;
		sd_iattr->ia_mode = sd->s_mode = mode;
	पूर्ण

	वापस error;
पूर्ण

अटल अंतरभूत व्योम set_शेष_inode_attr(काष्ठा inode * inode, umode_t mode)
अणु
	inode->i_mode = mode;
	inode->i_aसमय = inode->i_mसमय =
		inode->i_स_समय = current_समय(inode);
पूर्ण

अटल अंतरभूत व्योम set_inode_attr(काष्ठा inode * inode, काष्ठा iattr * iattr)
अणु
	inode->i_mode = iattr->ia_mode;
	inode->i_uid = iattr->ia_uid;
	inode->i_gid = iattr->ia_gid;
	inode->i_aसमय = iattr->ia_aसमय;
	inode->i_mसमय = iattr->ia_mसमय;
	inode->i_स_समय = iattr->ia_स_समय;
पूर्ण

काष्ठा inode *configfs_new_inode(umode_t mode, काष्ठा configfs_dirent *sd,
				 काष्ठा super_block *s)
अणु
	काष्ठा inode * inode = new_inode(s);
	अगर (inode) अणु
		inode->i_ino = get_next_ino();
		inode->i_mapping->a_ops = &configfs_aops;
		inode->i_op = &configfs_inode_operations;

		अगर (sd->s_iattr) अणु
			/* sysfs_dirent has non-शेष attributes
			 * get them क्रम the new inode from persistent copy
			 * in sysfs_dirent
			 */
			set_inode_attr(inode, sd->s_iattr);
		पूर्ण अन्यथा
			set_शेष_inode_attr(inode, mode);
	पूर्ण
	वापस inode;
पूर्ण

#अगर_घोषित CONFIG_LOCKDEP

अटल व्योम configfs_set_inode_lock_class(काष्ठा configfs_dirent *sd,
					  काष्ठा inode *inode)
अणु
	पूर्णांक depth = sd->s_depth;

	अगर (depth > 0) अणु
		अगर (depth <= ARRAY_SIZE(शेष_group_class)) अणु
			lockdep_set_class(&inode->i_rwsem,
					  &शेष_group_class[depth - 1]);
		पूर्ण अन्यथा अणु
			/*
			 * In practice the maximum level of locking depth is
			 * alपढ़ोy reached. Just inक्रमm about possible reasons.
			 */
			pr_info("Too many levels of inodes for the locking correctness validator.\n");
			pr_info("Spurious warnings may appear.\n");
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_LOCKDEP */

अटल व्योम configfs_set_inode_lock_class(काष्ठा configfs_dirent *sd,
					  काष्ठा inode *inode)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_LOCKDEP */

काष्ठा inode *configfs_create(काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा configfs_dirent *sd;
	काष्ठा inode *p_inode;

	अगर (!dentry)
		वापस ERR_PTR(-ENOENT);

	अगर (d_really_is_positive(dentry))
		वापस ERR_PTR(-EEXIST);

	sd = dentry->d_fsdata;
	inode = configfs_new_inode(mode, sd, dentry->d_sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	p_inode = d_inode(dentry->d_parent);
	p_inode->i_mसमय = p_inode->i_स_समय = current_समय(p_inode);
	configfs_set_inode_lock_class(sd, inode);
	वापस inode;
पूर्ण

/*
 * Get the name क्रम corresponding element represented by the given configfs_dirent
 */
स्थिर अचिन्हित अक्षर * configfs_get_name(काष्ठा configfs_dirent *sd)
अणु
	काष्ठा configfs_attribute *attr;

	BUG_ON(!sd || !sd->s_element);

	/* These always have a dentry, so use that */
	अगर (sd->s_type & (CONFIGFS_सूची | CONFIGFS_ITEM_LINK))
		वापस sd->s_dentry->d_name.name;

	अगर (sd->s_type & (CONFIGFS_ITEM_ATTR | CONFIGFS_ITEM_BIN_ATTR)) अणु
		attr = sd->s_element;
		वापस attr->ca_name;
	पूर्ण
	वापस शून्य;
पूर्ण


/*
 * Unhashes the dentry corresponding to given configfs_dirent
 * Called with parent inode's i_mutex held.
 */
व्योम configfs_drop_dentry(काष्ठा configfs_dirent * sd, काष्ठा dentry * parent)
अणु
	काष्ठा dentry * dentry = sd->s_dentry;

	अगर (dentry) अणु
		spin_lock(&dentry->d_lock);
		अगर (simple_positive(dentry)) अणु
			dget_dlock(dentry);
			__d_drop(dentry);
			spin_unlock(&dentry->d_lock);
			simple_unlink(d_inode(parent), dentry);
		पूर्ण अन्यथा
			spin_unlock(&dentry->d_lock);
	पूर्ण
पूर्ण

व्योम configfs_hash_and_हटाओ(काष्ठा dentry * dir, स्थिर अक्षर * name)
अणु
	काष्ठा configfs_dirent * sd;
	काष्ठा configfs_dirent * parent_sd = dir->d_fsdata;

	अगर (d_really_is_negative(dir))
		/* no inode means this hasn't been made visible yet */
		वापस;

	inode_lock(d_inode(dir));
	list_क्रम_each_entry(sd, &parent_sd->s_children, s_sibling) अणु
		अगर (!sd->s_element)
			जारी;
		अगर (!म_भेद(configfs_get_name(sd), name)) अणु
			spin_lock(&configfs_dirent_lock);
			list_del_init(&sd->s_sibling);
			spin_unlock(&configfs_dirent_lock);
			configfs_drop_dentry(sd, dir);
			configfs_put(sd);
			अवरोध;
		पूर्ण
	पूर्ण
	inode_unlock(d_inode(dir));
पूर्ण
