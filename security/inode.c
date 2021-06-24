<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  inode.c - securityfs
 *
 *  Copyright (C) 2005 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 *
 *  Based on fs/debugfs/inode.c which had the following copyright notice:
 *    Copyright (C) 2004 Greg Kroah-Harपंचांगan <greg@kroah.com>
 *    Copyright (C) 2004 IBM Inc.
 */

/* #घोषणा DEBUG */
#समावेश <linux/sysfs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/init.h>
#समावेश <linux/namei.h>
#समावेश <linux/security.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/magic.h>

अटल काष्ठा vfsmount *mount;
अटल पूर्णांक mount_count;

अटल व्योम securityfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	अगर (S_ISLNK(inode->i_mode))
		kमुक्त(inode->i_link);
	मुक्त_inode_nonrcu(inode);
पूर्ण

अटल स्थिर काष्ठा super_operations securityfs_super_operations = अणु
	.statfs		= simple_statfs,
	.मुक्त_inode	= securityfs_मुक्त_inode,
पूर्ण;

अटल पूर्णांक securityfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	अटल स्थिर काष्ठा tree_descr files[] = अणुअणु""पूर्णपूर्ण;
	पूर्णांक error;

	error = simple_fill_super(sb, SECURITYFS_MAGIC, files);
	अगर (error)
		वापस error;

	sb->s_op = &securityfs_super_operations;

	वापस 0;
पूर्ण

अटल पूर्णांक securityfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, securityfs_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations securityfs_context_ops = अणु
	.get_tree	= securityfs_get_tree,
पूर्ण;

अटल पूर्णांक securityfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &securityfs_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type fs_type = अणु
	.owner =	THIS_MODULE,
	.name =		"securityfs",
	.init_fs_context = securityfs_init_fs_context,
	.समाप्त_sb =	समाप्त_litter_super,
पूर्ण;

/**
 * securityfs_create_dentry - create a dentry in the securityfs fileप्रणाली
 *
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the securityfs fileप्रणाली.
 * @data: a poपूर्णांकer to something that the caller will want to get to later
 *        on.  The inode.i_निजी poपूर्णांकer will poपूर्णांक to this value on
 *        the खोलो() call.
 * @fops: a poपूर्णांकer to a काष्ठा file_operations that should be used क्रम
 *        this file.
 * @iops: a poपूर्णांक to a काष्ठा of inode_operations that should be used क्रम
 *        this file/dir
 *
 * This is the basic "create a file/dir/symlink" function क्रम
 * securityfs.  It allows क्रम a wide range of flexibility in creating
 * a file, or a directory (अगर you want to create a directory, the
 * securityfs_create_dir() function is recommended to be used
 * instead).
 *
 * This function वापसs a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the securityfs_हटाओ() function when the
 * file is to be हटाओd (no स्वतःmatic cleanup happens अगर your module
 * is unloaded, you are responsible here).  If an error occurs, the
 * function will वापस the error value (via ERR_PTR).
 *
 * If securityfs is not enabled in the kernel, the value %-ENODEV is
 * वापसed.
 */
अटल काष्ठा dentry *securityfs_create_dentry(स्थिर अक्षर *name, umode_t mode,
					काष्ठा dentry *parent, व्योम *data,
					स्थिर काष्ठा file_operations *fops,
					स्थिर काष्ठा inode_operations *iops)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *dir, *inode;
	पूर्णांक error;

	अगर (!(mode & S_IFMT))
		mode = (mode & S_IALLUGO) | S_IFREG;

	pr_debug("securityfs: creating file '%s'\n",name);

	error = simple_pin_fs(&fs_type, &mount, &mount_count);
	अगर (error)
		वापस ERR_PTR(error);

	अगर (!parent)
		parent = mount->mnt_root;

	dir = d_inode(parent);

	inode_lock(dir);
	dentry = lookup_one_len(name, parent, म_माप(name));
	अगर (IS_ERR(dentry))
		जाओ out;

	अगर (d_really_is_positive(dentry)) अणु
		error = -EEXIST;
		जाओ out1;
	पूर्ण

	inode = new_inode(dir->i_sb);
	अगर (!inode) अणु
		error = -ENOMEM;
		जाओ out1;
	पूर्ण

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	inode->i_निजी = data;
	अगर (S_ISसूची(mode)) अणु
		inode->i_op = &simple_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
		inc_nlink(inode);
		inc_nlink(dir);
	पूर्ण अन्यथा अगर (S_ISLNK(mode)) अणु
		inode->i_op = iops ? iops : &simple_symlink_inode_operations;
		inode->i_link = data;
	पूर्ण अन्यथा अणु
		inode->i_fop = fops;
	पूर्ण
	d_instantiate(dentry, inode);
	dget(dentry);
	inode_unlock(dir);
	वापस dentry;

out1:
	dput(dentry);
	dentry = ERR_PTR(error);
out:
	inode_unlock(dir);
	simple_release_fs(&mount, &mount_count);
	वापस dentry;
पूर्ण

/**
 * securityfs_create_file - create a file in the securityfs fileप्रणाली
 *
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the securityfs fileप्रणाली.
 * @data: a poपूर्णांकer to something that the caller will want to get to later
 *        on.  The inode.i_निजी poपूर्णांकer will poपूर्णांक to this value on
 *        the खोलो() call.
 * @fops: a poपूर्णांकer to a काष्ठा file_operations that should be used क्रम
 *        this file.
 *
 * This function creates a file in securityfs with the given @name.
 *
 * This function वापसs a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the securityfs_हटाओ() function when the file is
 * to be हटाओd (no स्वतःmatic cleanup happens अगर your module is unloaded,
 * you are responsible here).  If an error occurs, the function will वापस
 * the error value (via ERR_PTR).
 *
 * If securityfs is not enabled in the kernel, the value %-ENODEV is
 * वापसed.
 */
काष्ठा dentry *securityfs_create_file(स्थिर अक्षर *name, umode_t mode,
				      काष्ठा dentry *parent, व्योम *data,
				      स्थिर काष्ठा file_operations *fops)
अणु
	वापस securityfs_create_dentry(name, mode, parent, data, fops, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(securityfs_create_file);

/**
 * securityfs_create_dir - create a directory in the securityfs fileप्रणाली
 *
 * @name: a poपूर्णांकer to a string containing the name of the directory to
 *        create.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          directory will be created in the root of the securityfs fileप्रणाली.
 *
 * This function creates a directory in securityfs with the given @name.
 *
 * This function वापसs a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the securityfs_हटाओ() function when the file is
 * to be हटाओd (no स्वतःmatic cleanup happens अगर your module is unloaded,
 * you are responsible here).  If an error occurs, the function will वापस
 * the error value (via ERR_PTR).
 *
 * If securityfs is not enabled in the kernel, the value %-ENODEV is
 * वापसed.
 */
काष्ठा dentry *securityfs_create_dir(स्थिर अक्षर *name, काष्ठा dentry *parent)
अणु
	वापस securityfs_create_file(name, S_IFसूची | 0755, parent, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(securityfs_create_dir);

/**
 * securityfs_create_symlink - create a symlink in the securityfs fileप्रणाली
 *
 * @name: a poपूर्णांकer to a string containing the name of the symlink to
 *        create.
 * @parent: a poपूर्णांकer to the parent dentry क्रम the symlink.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          directory will be created in the root of the securityfs fileप्रणाली.
 * @target: a poपूर्णांकer to a string containing the name of the symlink's target.
 *          If this parameter is %शून्य, then the @iops parameter needs to be
 *          setup to handle .पढ़ोlink and .get_link inode_operations.
 * @iops: a poपूर्णांकer to the काष्ठा inode_operations to use क्रम the symlink. If
 *        this parameter is %शून्य, then the शेष simple_symlink_inode
 *        operations will be used.
 *
 * This function creates a symlink in securityfs with the given @name.
 *
 * This function वापसs a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the securityfs_हटाओ() function when the file is
 * to be हटाओd (no स्वतःmatic cleanup happens अगर your module is unloaded,
 * you are responsible here).  If an error occurs, the function will वापस
 * the error value (via ERR_PTR).
 *
 * If securityfs is not enabled in the kernel, the value %-ENODEV is
 * वापसed.
 */
काष्ठा dentry *securityfs_create_symlink(स्थिर अक्षर *name,
					 काष्ठा dentry *parent,
					 स्थिर अक्षर *target,
					 स्थिर काष्ठा inode_operations *iops)
अणु
	काष्ठा dentry *dent;
	अक्षर *link = शून्य;

	अगर (target) अणु
		link = kstrdup(target, GFP_KERNEL);
		अगर (!link)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण
	dent = securityfs_create_dentry(name, S_IFLNK | 0444, parent,
					link, शून्य, iops);
	अगर (IS_ERR(dent))
		kमुक्त(link);

	वापस dent;
पूर्ण
EXPORT_SYMBOL_GPL(securityfs_create_symlink);

/**
 * securityfs_हटाओ - हटाओs a file or directory from the securityfs fileप्रणाली
 *
 * @dentry: a poपूर्णांकer to a the dentry of the file or directory to be हटाओd.
 *
 * This function हटाओs a file or directory in securityfs that was previously
 * created with a call to another securityfs function (like
 * securityfs_create_file() or variants thereof.)
 *
 * This function is required to be called in order क्रम the file to be
 * हटाओd. No स्वतःmatic cleanup of files will happen when a module is
 * हटाओd; you are responsible here.
 */
व्योम securityfs_हटाओ(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *dir;

	अगर (!dentry || IS_ERR(dentry))
		वापस;

	dir = d_inode(dentry->d_parent);
	inode_lock(dir);
	अगर (simple_positive(dentry)) अणु
		अगर (d_is_dir(dentry))
			simple_सूची_हटाओ(dir, dentry);
		अन्यथा
			simple_unlink(dir, dentry);
		dput(dentry);
	पूर्ण
	inode_unlock(dir);
	simple_release_fs(&mount, &mount_count);
पूर्ण
EXPORT_SYMBOL_GPL(securityfs_हटाओ);

#अगर_घोषित CONFIG_SECURITY
अटल काष्ठा dentry *lsm_dentry;
अटल sमाप_प्रकार lsm_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, lsm_names,
		म_माप(lsm_names));
पूर्ण

अटल स्थिर काष्ठा file_operations lsm_ops = अणु
	.पढ़ो = lsm_पढ़ो,
	.llseek = generic_file_llseek,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init securityfs_init(व्योम)
अणु
	पूर्णांक retval;

	retval = sysfs_create_mount_poपूर्णांक(kernel_kobj, "security");
	अगर (retval)
		वापस retval;

	retval = रेजिस्टर_fileप्रणाली(&fs_type);
	अगर (retval) अणु
		sysfs_हटाओ_mount_poपूर्णांक(kernel_kobj, "security");
		वापस retval;
	पूर्ण
#अगर_घोषित CONFIG_SECURITY
	lsm_dentry = securityfs_create_file("lsm", 0444, शून्य, शून्य,
						&lsm_ops);
#पूर्ण_अगर
	वापस 0;
पूर्ण
core_initcall(securityfs_init);
