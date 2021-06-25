<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mount.c - operations क्रम initializing and mounting configfs.
 *
 * Based on sysfs:
 * 	sysfs is Copyright (C) 2001, 2002, 2003 Patrick Mochel
 *
 * configfs Copyright (C) 2005 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>

#समावेश <linux/configfs.h>
#समावेश "configfs_internal.h"

/* Ranकरोm magic number */
#घोषणा CONFIGFS_MAGIC 0x62656570

अटल काष्ठा vfsmount *configfs_mount = शून्य;
काष्ठा kmem_cache *configfs_dir_cachep;
अटल पूर्णांक configfs_mnt_count = 0;


अटल व्योम configfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	अगर (S_ISLNK(inode->i_mode))
		kमुक्त(inode->i_link);
	मुक्त_inode_nonrcu(inode);
पूर्ण

अटल स्थिर काष्ठा super_operations configfs_ops = अणु
	.statfs		= simple_statfs,
	.drop_inode	= generic_delete_inode,
	.मुक्त_inode	= configfs_मुक्त_inode,
पूर्ण;

अटल काष्ठा config_group configfs_root_group = अणु
	.cg_item = अणु
		.ci_namebuf	= "root",
		.ci_name	= configfs_root_group.cg_item.ci_namebuf,
	पूर्ण,
पूर्ण;

पूर्णांक configfs_is_root(काष्ठा config_item *item)
अणु
	वापस item == &configfs_root_group.cg_item;
पूर्ण

अटल काष्ठा configfs_dirent configfs_root = अणु
	.s_sibling	= LIST_HEAD_INIT(configfs_root.s_sibling),
	.s_children	= LIST_HEAD_INIT(configfs_root.s_children),
	.s_element	= &configfs_root_group.cg_item,
	.s_type		= CONFIGFS_ROOT,
	.s_iattr	= शून्य,
पूर्ण;

अटल पूर्णांक configfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा inode *inode;
	काष्ठा dentry *root;

	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = CONFIGFS_MAGIC;
	sb->s_op = &configfs_ops;
	sb->s_समय_gran = 1;

	inode = configfs_new_inode(S_IFसूची | S_IRWXU | S_IRUGO | S_IXUGO,
				   &configfs_root, sb);
	अगर (inode) अणु
		inode->i_op = &configfs_root_inode_operations;
		inode->i_fop = &configfs_dir_operations;
		/* directory inodes start off with i_nlink == 2 (क्रम "." entry) */
		inc_nlink(inode);
	पूर्ण अन्यथा अणु
		pr_debug("could not get root inode\n");
		वापस -ENOMEM;
	पूर्ण

	root = d_make_root(inode);
	अगर (!root) अणु
		pr_debug("%s: could not get root dentry!\n",__func__);
		वापस -ENOMEM;
	पूर्ण
	config_group_init(&configfs_root_group);
	configfs_root_group.cg_item.ci_dentry = root;
	root->d_fsdata = &configfs_root;
	sb->s_root = root;
	sb->s_d_op = &configfs_dentry_ops; /* the rest get that */
	वापस 0;
पूर्ण

अटल पूर्णांक configfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, configfs_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations configfs_context_ops = अणु
	.get_tree	= configfs_get_tree,
पूर्ण;

अटल पूर्णांक configfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &configfs_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type configfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "configfs",
	.init_fs_context = configfs_init_fs_context,
	.समाप्त_sb	= समाप्त_litter_super,
पूर्ण;
MODULE_ALIAS_FS("configfs");

काष्ठा dentry *configfs_pin_fs(व्योम)
अणु
	पूर्णांक err = simple_pin_fs(&configfs_fs_type, &configfs_mount,
			     &configfs_mnt_count);
	वापस err ? ERR_PTR(err) : configfs_mount->mnt_root;
पूर्ण

व्योम configfs_release_fs(व्योम)
अणु
	simple_release_fs(&configfs_mount, &configfs_mnt_count);
पूर्ण


अटल पूर्णांक __init configfs_init(व्योम)
अणु
	पूर्णांक err = -ENOMEM;

	configfs_dir_cachep = kmem_cache_create("configfs_dir_cache",
						माप(काष्ठा configfs_dirent),
						0, 0, शून्य);
	अगर (!configfs_dir_cachep)
		जाओ out;

	err = sysfs_create_mount_poपूर्णांक(kernel_kobj, "config");
	अगर (err)
		जाओ out2;

	err = रेजिस्टर_fileप्रणाली(&configfs_fs_type);
	अगर (err)
		जाओ out3;

	वापस 0;
out3:
	pr_err("Unable to register filesystem!\n");
	sysfs_हटाओ_mount_poपूर्णांक(kernel_kobj, "config");
out2:
	kmem_cache_destroy(configfs_dir_cachep);
	configfs_dir_cachep = शून्य;
out:
	वापस err;
पूर्ण

अटल व्योम __निकास configfs_निकास(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&configfs_fs_type);
	sysfs_हटाओ_mount_poपूर्णांक(kernel_kobj, "config");
	kmem_cache_destroy(configfs_dir_cachep);
	configfs_dir_cachep = शून्य;
पूर्ण

MODULE_AUTHOR("Oracle");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.2");
MODULE_DESCRIPTION("Simple RAM filesystem for user driven kernel subsystem configuration.");

core_initcall(configfs_init);
module_निकास(configfs_निकास);
