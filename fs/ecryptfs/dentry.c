<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 *
 * Copyright (C) 1997-2003 Erez Zaकरोk
 * Copyright (C) 2001-2003 Stony Brook University
 * Copyright (C) 2004-2006 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 */

#समावेश <linux/dcache.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_stack.h>
#समावेश <linux/slab.h>
#समावेश "ecryptfs_kernel.h"

/**
 * ecryptfs_d_revalidate - revalidate an ecryptfs dentry
 * @dentry: The ecryptfs dentry
 * @flags: lookup flags
 *
 * Called when the VFS needs to revalidate a dentry. This
 * is called whenever a name lookup finds a dentry in the
 * dcache. Most fileप्रणालीs leave this as शून्य, because all their
 * dentries in the dcache are valid.
 *
 * Returns 1 अगर valid, 0 otherwise.
 *
 */
अटल पूर्णांक ecryptfs_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *lower_dentry = ecryptfs_dentry_to_lower(dentry);
	पूर्णांक rc = 1;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	अगर (lower_dentry->d_flags & DCACHE_OP_REVALIDATE)
		rc = lower_dentry->d_op->d_revalidate(lower_dentry, flags);

	अगर (d_really_is_positive(dentry)) अणु
		काष्ठा inode *inode = d_inode(dentry);

		fsstack_copy_attr_all(inode, ecryptfs_inode_to_lower(inode));
		अगर (!inode->i_nlink)
			वापस 0;
	पूर्ण
	वापस rc;
पूर्ण

काष्ठा kmem_cache *ecryptfs_dentry_info_cache;

अटल व्योम ecryptfs_dentry_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	kmem_cache_मुक्त(ecryptfs_dentry_info_cache,
		container_of(head, काष्ठा ecryptfs_dentry_info, rcu));
पूर्ण

/**
 * ecryptfs_d_release
 * @dentry: The ecryptfs dentry
 *
 * Called when a dentry is really deallocated.
 */
अटल व्योम ecryptfs_d_release(काष्ठा dentry *dentry)
अणु
	काष्ठा ecryptfs_dentry_info *p = dentry->d_fsdata;
	अगर (p) अणु
		path_put(&p->lower_path);
		call_rcu(&p->rcu, ecryptfs_dentry_मुक्त_rcu);
	पूर्ण
पूर्ण

स्थिर काष्ठा dentry_operations ecryptfs_करोps = अणु
	.d_revalidate = ecryptfs_d_revalidate,
	.d_release = ecryptfs_d_release,
पूर्ण;
