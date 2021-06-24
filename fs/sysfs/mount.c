<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/sysfs/symlink.c - operations क्रम initializing and mounting sysfs
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007 Tejun Heo <teheo@suse.de>
 *
 * Please see Documentation/fileप्रणालीs/sysfs.rst क्रम more inक्रमmation.
 */

#समावेश <linux/fs.h>
#समावेश <linux/magic.h>
#समावेश <linux/mount.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/fs_context.h>
#समावेश <net/net_namespace.h>

#समावेश "sysfs.h"

अटल काष्ठा kernfs_root *sysfs_root;
काष्ठा kernfs_node *sysfs_root_kn;

अटल पूर्णांक sysfs_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा kernfs_fs_context *kfc = fc->fs_निजी;
	पूर्णांक ret;

	ret = kernfs_get_tree(fc);
	अगर (ret)
		वापस ret;

	अगर (kfc->new_sb_created)
		fc->root->d_sb->s_अगरlags |= SB_I_USERNS_VISIBLE;
	वापस 0;
पूर्ण

अटल व्योम sysfs_fs_context_मुक्त(काष्ठा fs_context *fc)
अणु
	काष्ठा kernfs_fs_context *kfc = fc->fs_निजी;

	अगर (kfc->ns_tag)
		kobj_ns_drop(KOBJ_NS_TYPE_NET, kfc->ns_tag);
	kernfs_मुक्त_fs_context(fc);
	kमुक्त(kfc);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations sysfs_fs_context_ops = अणु
	.मुक्त		= sysfs_fs_context_मुक्त,
	.get_tree	= sysfs_get_tree,
पूर्ण;

अटल पूर्णांक sysfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा kernfs_fs_context *kfc;
	काष्ठा net *netns;

	अगर (!(fc->sb_flags & SB_KERNMOUNT)) अणु
		अगर (!kobj_ns_current_may_mount(KOBJ_NS_TYPE_NET))
			वापस -EPERM;
	पूर्ण

	kfc = kzalloc(माप(काष्ठा kernfs_fs_context), GFP_KERNEL);
	अगर (!kfc)
		वापस -ENOMEM;

	kfc->ns_tag = netns = kobj_ns_grab_current(KOBJ_NS_TYPE_NET);
	kfc->root = sysfs_root;
	kfc->magic = SYSFS_MAGIC;
	fc->fs_निजी = kfc;
	fc->ops = &sysfs_fs_context_ops;
	अगर (netns) अणु
		put_user_ns(fc->user_ns);
		fc->user_ns = get_user_ns(netns->user_ns);
	पूर्ण
	fc->global = true;
	वापस 0;
पूर्ण

अटल व्योम sysfs_समाप्त_sb(काष्ठा super_block *sb)
अणु
	व्योम *ns = (व्योम *)kernfs_super_ns(sb);

	kernfs_समाप्त_sb(sb);
	kobj_ns_drop(KOBJ_NS_TYPE_NET, ns);
पूर्ण

अटल काष्ठा file_प्रणाली_type sysfs_fs_type = अणु
	.name			= "sysfs",
	.init_fs_context	= sysfs_init_fs_context,
	.समाप्त_sb		= sysfs_समाप्त_sb,
	.fs_flags		= FS_USERNS_MOUNT,
पूर्ण;

पूर्णांक __init sysfs_init(व्योम)
अणु
	पूर्णांक err;

	sysfs_root = kernfs_create_root(शून्य, KERNFS_ROOT_EXTRA_OPEN_PERM_CHECK,
					शून्य);
	अगर (IS_ERR(sysfs_root))
		वापस PTR_ERR(sysfs_root);

	sysfs_root_kn = sysfs_root->kn;

	err = रेजिस्टर_fileप्रणाली(&sysfs_fs_type);
	अगर (err) अणु
		kernfs_destroy_root(sysfs_root);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
