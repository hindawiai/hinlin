<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Landlock LSM - Fileप्रणाली management and hooks
 *
 * Copyright तऊ 2017-2020 Mickaथ+l Salaथञn <mic@digikod.net>
 * Copyright तऊ 2018-2020 ANSSI
 */

#अगर_अघोषित _SECURITY_LANDLOCK_FS_H
#घोषणा _SECURITY_LANDLOCK_FS_H

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/rcupdate.h>

#समावेश "ruleset.h"
#समावेश "setup.h"

/**
 * काष्ठा landlock_inode_security - Inode security blob
 *
 * Enable to reference a &काष्ठा landlock_object tied to an inode (i.e.
 * underlying object).
 */
काष्ठा landlock_inode_security अणु
	/**
	 * @object: Weak poपूर्णांकer to an allocated object.  All assignments of a
	 * new object are रक्षित by the underlying inode->i_lock.  However,
	 * atomically disassociating @object from the inode is only रक्षित
	 * by @object->lock, from the समय @object's usage refcount drops to
	 * zero to the समय this poपूर्णांकer is nulled out (cf. release_inode() and
	 * hook_sb_delete()).  Indeed, such disassociation करोesn't require
	 * inode->i_lock thanks to the careful rcu_access_poपूर्णांकer() check
	 * perक्रमmed by get_inode_object().
	 */
	काष्ठा landlock_object __rcu *object;
पूर्ण;

/**
 * काष्ठा landlock_superblock_security - Superblock security blob
 *
 * Enable hook_sb_delete() to रुको क्रम concurrent calls to release_inode().
 */
काष्ठा landlock_superblock_security अणु
	/**
	 * @inode_refs: Number of pending inodes (from this superblock) that
	 * are being released by release_inode().
	 * Cf. काष्ठा super_block->s_fsnotअगरy_inode_refs .
	 */
	atomic_दीर्घ_t inode_refs;
पूर्ण;

अटल अंतरभूत काष्ठा landlock_inode_security *landlock_inode(
		स्थिर काष्ठा inode *स्थिर inode)
अणु
	वापस inode->i_security + landlock_blob_sizes.lbs_inode;
पूर्ण

अटल अंतरभूत काष्ठा landlock_superblock_security *landlock_superblock(
		स्थिर काष्ठा super_block *स्थिर superblock)
अणु
	वापस superblock->s_security + landlock_blob_sizes.lbs_superblock;
पूर्ण

__init व्योम landlock_add_fs_hooks(व्योम);

पूर्णांक landlock_append_fs_rule(काष्ठा landlock_ruleset *स्थिर ruleset,
		स्थिर काष्ठा path *स्थिर path, u32 access_hierarchy);

#पूर्ण_अगर /* _SECURITY_LANDLOCK_FS_H */
