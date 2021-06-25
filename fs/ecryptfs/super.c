<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * eCryptfs: Linux fileप्रणाली encryption layer
 *
 * Copyright (C) 1997-2003 Erez Zaकरोk
 * Copyright (C) 2001-2003 Stony Brook University
 * Copyright (C) 2004-2006 International Business Machines Corp.
 *   Author(s): Michael A. Halcrow <mahalcro@us.ibm.com>
 *              Michael C. Thompson <mcthomps@us.ibm.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/key.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/file.h>
#समावेश <linux/statfs.h>
#समावेश <linux/magic.h>
#समावेश "ecryptfs_kernel.h"

काष्ठा kmem_cache *ecryptfs_inode_info_cache;

/**
 * ecryptfs_alloc_inode - allocate an ecryptfs inode
 * @sb: Poपूर्णांकer to the ecryptfs super block
 *
 * Called to bring an inode पूर्णांकo existence.
 *
 * Only handle allocation, setting up काष्ठाures should be करोne in
 * ecryptfs_पढ़ो_inode. This is because the kernel, between now and
 * then, will 0 out the निजी data poपूर्णांकer.
 *
 * Returns a poपूर्णांकer to a newly allocated inode, शून्य otherwise
 */
अटल काष्ठा inode *ecryptfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा ecryptfs_inode_info *inode_info;
	काष्ठा inode *inode = शून्य;

	inode_info = kmem_cache_alloc(ecryptfs_inode_info_cache, GFP_KERNEL);
	अगर (unlikely(!inode_info))
		जाओ out;
	अगर (ecryptfs_init_crypt_stat(&inode_info->crypt_stat)) अणु
		kmem_cache_मुक्त(ecryptfs_inode_info_cache, inode_info);
		जाओ out;
	पूर्ण
	mutex_init(&inode_info->lower_file_mutex);
	atomic_set(&inode_info->lower_file_count, 0);
	inode_info->lower_file = शून्य;
	inode = &inode_info->vfs_inode;
out:
	वापस inode;
पूर्ण

अटल व्योम ecryptfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा ecryptfs_inode_info *inode_info;
	inode_info = ecryptfs_inode_to_निजी(inode);

	kmem_cache_मुक्त(ecryptfs_inode_info_cache, inode_info);
पूर्ण

/**
 * ecryptfs_destroy_inode
 * @inode: The ecryptfs inode
 *
 * This is used during the final deकाष्ठाion of the inode.  All
 * allocation of memory related to the inode, including allocated
 * memory in the crypt_stat काष्ठा, will be released here.
 * There should be no chance that this deallocation will be missed.
 */
अटल व्योम ecryptfs_destroy_inode(काष्ठा inode *inode)
अणु
	काष्ठा ecryptfs_inode_info *inode_info;

	inode_info = ecryptfs_inode_to_निजी(inode);
	BUG_ON(inode_info->lower_file);
	ecryptfs_destroy_crypt_stat(&inode_info->crypt_stat);
पूर्ण

/**
 * ecryptfs_statfs
 * @dentry: The ecryptfs dentry
 * @buf: The काष्ठा kstatfs to fill in with stats
 *
 * Get the fileप्रणाली statistics. Currently, we let this pass right through
 * to the lower fileप्रणाली and take no action ourselves.
 */
अटल पूर्णांक ecryptfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा dentry *lower_dentry = ecryptfs_dentry_to_lower(dentry);
	पूर्णांक rc;

	अगर (!lower_dentry->d_sb->s_op->statfs)
		वापस -ENOSYS;

	rc = lower_dentry->d_sb->s_op->statfs(lower_dentry, buf);
	अगर (rc)
		वापस rc;

	buf->f_type = ECRYPTFS_SUPER_MAGIC;
	rc = ecryptfs_set_f_namelen(&buf->f_namelen, buf->f_namelen,
	       &ecryptfs_superblock_to_निजी(dentry->d_sb)->mount_crypt_stat);

	वापस rc;
पूर्ण

/**
 * ecryptfs_evict_inode
 * @inode: The ecryptfs inode
 *
 * Called by iput() when the inode reference count reached zero
 * and the inode is not hashed anywhere.  Used to clear anything
 * that needs to be, beक्रमe the inode is completely destroyed and put
 * on the inode मुक्त list. We use this to drop out reference to the
 * lower inode.
 */
अटल व्योम ecryptfs_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	iput(ecryptfs_inode_to_lower(inode));
पूर्ण

/*
 * ecryptfs_show_options
 *
 * Prपूर्णांकs the mount options क्रम a given superblock.
 * Returns zero; करोes not fail.
 */
अटल पूर्णांक ecryptfs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा super_block *sb = root->d_sb;
	काष्ठा ecryptfs_mount_crypt_stat *mount_crypt_stat =
		&ecryptfs_superblock_to_निजी(sb)->mount_crypt_stat;
	काष्ठा ecryptfs_global_auth_tok *walker;

	mutex_lock(&mount_crypt_stat->global_auth_tok_list_mutex);
	list_क्रम_each_entry(walker,
			    &mount_crypt_stat->global_auth_tok_list,
			    mount_crypt_stat_list) अणु
		अगर (walker->flags & ECRYPTFS_AUTH_TOK_FNEK)
			seq_म_लिखो(m, ",ecryptfs_fnek_sig=%s", walker->sig);
		अन्यथा
			seq_म_लिखो(m, ",ecryptfs_sig=%s", walker->sig);
	पूर्ण
	mutex_unlock(&mount_crypt_stat->global_auth_tok_list_mutex);

	seq_म_लिखो(m, ",ecryptfs_cipher=%s",
		mount_crypt_stat->global_शेष_cipher_name);

	अगर (mount_crypt_stat->global_शेष_cipher_key_size)
		seq_म_लिखो(m, ",ecryptfs_key_bytes=%zd",
			   mount_crypt_stat->global_शेष_cipher_key_size);
	अगर (mount_crypt_stat->flags & ECRYPTFS_PLAINTEXT_PASSTHROUGH_ENABLED)
		seq_म_लिखो(m, ",ecryptfs_passthrough");
	अगर (mount_crypt_stat->flags & ECRYPTFS_XATTR_METADATA_ENABLED)
		seq_म_लिखो(m, ",ecryptfs_xattr_metadata");
	अगर (mount_crypt_stat->flags & ECRYPTFS_ENCRYPTED_VIEW_ENABLED)
		seq_म_लिखो(m, ",ecryptfs_encrypted_view");
	अगर (mount_crypt_stat->flags & ECRYPTFS_UNLINK_SIGS)
		seq_म_लिखो(m, ",ecryptfs_unlink_sigs");
	अगर (mount_crypt_stat->flags & ECRYPTFS_GLOBAL_MOUNT_AUTH_TOK_ONLY)
		seq_म_लिखो(m, ",ecryptfs_mount_auth_tok_only");

	वापस 0;
पूर्ण

स्थिर काष्ठा super_operations ecryptfs_sops = अणु
	.alloc_inode = ecryptfs_alloc_inode,
	.destroy_inode = ecryptfs_destroy_inode,
	.मुक्त_inode = ecryptfs_मुक्त_inode,
	.statfs = ecryptfs_statfs,
	.remount_fs = शून्य,
	.evict_inode = ecryptfs_evict_inode,
	.show_options = ecryptfs_show_options
पूर्ण;
