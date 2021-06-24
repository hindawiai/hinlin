<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2002
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */

#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/quotaops.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_inode.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_txnmgr.h"
#समावेश "jfs_xattr.h"
#समावेश "jfs_acl.h"
#समावेश "jfs_debug.h"

पूर्णांक jfs_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	पूर्णांक rc = 0;

	rc = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (rc)
		वापस rc;

	inode_lock(inode);
	अगर (!(inode->i_state & I_सूचीTY_ALL) ||
	    (datasync && !(inode->i_state & I_सूचीTY_DATASYNC))) अणु
		/* Make sure committed changes hit the disk */
		jfs_flush_journal(JFS_SBI(inode->i_sb)->log, 1);
		inode_unlock(inode);
		वापस rc;
	पूर्ण

	rc |= jfs_commit_inode(inode, 1);
	inode_unlock(inode);

	वापस rc ? -EIO : 0;
पूर्ण

अटल पूर्णांक jfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक rc;

	अगर ((rc = dquot_file_खोलो(inode, file)))
		वापस rc;

	/*
	 * We attempt to allow only one "active" file खोलो per aggregate
	 * group.  Otherwise, appending to files in parallel can cause
	 * fragmentation within the files.
	 *
	 * If the file is empty, it was probably just created and going
	 * to be written to.  If it has a size, we'll hold off until the
	 * file is actually grown.
	 */
	अगर (S_ISREG(inode->i_mode) && file->f_mode & FMODE_WRITE &&
	    (inode->i_size == 0)) अणु
		काष्ठा jfs_inode_info *ji = JFS_IP(inode);
		spin_lock_irq(&ji->ag_lock);
		अगर (ji->active_ag == -1) अणु
			काष्ठा jfs_sb_info *jfs_sb = JFS_SBI(inode->i_sb);
			ji->active_ag = BLKTOAG(addressPXD(&ji->ixpxd), jfs_sb);
			atomic_inc(&jfs_sb->bmap->db_active[ji->active_ag]);
		पूर्ण
		spin_unlock_irq(&ji->ag_lock);
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक jfs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा jfs_inode_info *ji = JFS_IP(inode);

	spin_lock_irq(&ji->ag_lock);
	अगर (ji->active_ag != -1) अणु
		काष्ठा bmap *bmap = JFS_SBI(inode->i_sb)->bmap;
		atomic_dec(&bmap->db_active[ji->active_ag]);
		ji->active_ag = -1;
	पूर्ण
	spin_unlock_irq(&ji->ag_lock);

	वापस 0;
पूर्ण

पूर्णांक jfs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		काष्ठा iattr *iattr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक rc;

	rc = setattr_prepare(&init_user_ns, dentry, iattr);
	अगर (rc)
		वापस rc;

	अगर (is_quota_modअगरication(inode, iattr)) अणु
		rc = dquot_initialize(inode);
		अगर (rc)
			वापस rc;
	पूर्ण
	अगर ((iattr->ia_valid & ATTR_UID && !uid_eq(iattr->ia_uid, inode->i_uid)) ||
	    (iattr->ia_valid & ATTR_GID && !gid_eq(iattr->ia_gid, inode->i_gid))) अणु
		rc = dquot_transfer(inode, iattr);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर ((iattr->ia_valid & ATTR_SIZE) &&
	    iattr->ia_size != i_size_पढ़ो(inode)) अणु
		inode_dio_रुको(inode);

		rc = inode_newsize_ok(inode, iattr->ia_size);
		अगर (rc)
			वापस rc;

		truncate_setsize(inode, iattr->ia_size);
		jfs_truncate(inode);
	पूर्ण

	setattr_copy(&init_user_ns, inode, iattr);
	mark_inode_dirty(inode);

	अगर (iattr->ia_valid & ATTR_MODE)
		rc = posix_acl_chmod(&init_user_ns, inode, inode->i_mode);
	वापस rc;
पूर्ण

स्थिर काष्ठा inode_operations jfs_file_inode_operations = अणु
	.listxattr	= jfs_listxattr,
	.setattr	= jfs_setattr,
	.fileattr_get	= jfs_fileattr_get,
	.fileattr_set	= jfs_fileattr_set,
#अगर_घोषित CONFIG_JFS_POSIX_ACL
	.get_acl	= jfs_get_acl,
	.set_acl	= jfs_set_acl,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा file_operations jfs_file_operations = अणु
	.खोलो		= jfs_खोलो,
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.mmap		= generic_file_mmap,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.fsync		= jfs_fsync,
	.release	= jfs_release,
	.unlocked_ioctl = jfs_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;
