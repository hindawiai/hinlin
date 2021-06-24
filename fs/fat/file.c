<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/fat/file.c
 *
 *  Written 1992,1993 by Werner Almesberger
 *
 *  regular file handling primitives क्रम fat-based fileप्रणालीs
 */

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/compat.h>
#समावेश <linux/mount.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/security.h>
#समावेश <linux/fभाग.स>
#समावेश "fat.h"

अटल दीर्घ fat_fallocate(काष्ठा file *file, पूर्णांक mode,
			  loff_t offset, loff_t len);

अटल पूर्णांक fat_ioctl_get_attributes(काष्ठा inode *inode, u32 __user *user_attr)
अणु
	u32 attr;

	inode_lock_shared(inode);
	attr = fat_make_attrs(inode);
	inode_unlock_shared(inode);

	वापस put_user(attr, user_attr);
पूर्ण

अटल पूर्णांक fat_ioctl_set_attributes(काष्ठा file *file, u32 __user *user_attr)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	पूर्णांक is_dir = S_ISसूची(inode->i_mode);
	u32 attr, oldattr;
	काष्ठा iattr ia;
	पूर्णांक err;

	err = get_user(attr, user_attr);
	अगर (err)
		जाओ out;

	err = mnt_want_ग_लिखो_file(file);
	अगर (err)
		जाओ out;
	inode_lock(inode);

	/*
	 * ATTR_VOLUME and ATTR_सूची cannot be changed; this also
	 * prevents the user from turning us पूर्णांकo a VFAT
	 * दीर्घname entry.  Also, we obviously can't set
	 * any of the NTFS attributes in the high 24 bits.
	 */
	attr &= 0xff & ~(ATTR_VOLUME | ATTR_सूची);
	/* Merge in ATTR_VOLUME and ATTR_सूची */
	attr |= (MSDOS_I(inode)->i_attrs & ATTR_VOLUME) |
		(is_dir ? ATTR_सूची : 0);
	oldattr = fat_make_attrs(inode);

	/* Equivalent to a chmod() */
	ia.ia_valid = ATTR_MODE | ATTR_CTIME;
	ia.ia_स_समय = current_समय(inode);
	अगर (is_dir)
		ia.ia_mode = fat_make_mode(sbi, attr, S_IRWXUGO);
	अन्यथा अणु
		ia.ia_mode = fat_make_mode(sbi, attr,
			S_IRUGO | S_IWUGO | (inode->i_mode & S_IXUGO));
	पूर्ण

	/* The root directory has no attributes */
	अगर (inode->i_ino == MSDOS_ROOT_INO && attr != ATTR_सूची) अणु
		err = -EINVAL;
		जाओ out_unlock_inode;
	पूर्ण

	अगर (sbi->options.sys_immutable &&
	    ((attr | oldattr) & ATTR_SYS) &&
	    !capable(CAP_LINUX_IMMUTABLE)) अणु
		err = -EPERM;
		जाओ out_unlock_inode;
	पूर्ण

	/*
	 * The security check is questionable...  We single
	 * out the RO attribute क्रम checking by the security
	 * module, just because it maps to a file mode.
	 */
	err = security_inode_setattr(file->f_path.dentry, &ia);
	अगर (err)
		जाओ out_unlock_inode;

	/* This MUST be करोne beक्रमe करोing anything irreversible... */
	err = fat_setattr(file_mnt_user_ns(file), file->f_path.dentry, &ia);
	अगर (err)
		जाओ out_unlock_inode;

	fsnotअगरy_change(file->f_path.dentry, ia.ia_valid);
	अगर (sbi->options.sys_immutable) अणु
		अगर (attr & ATTR_SYS)
			inode->i_flags |= S_IMMUTABLE;
		अन्यथा
			inode->i_flags &= ~S_IMMUTABLE;
	पूर्ण

	fat_save_attrs(inode, attr);
	mark_inode_dirty(inode);
out_unlock_inode:
	inode_unlock(inode);
	mnt_drop_ग_लिखो_file(file);
out:
	वापस err;
पूर्ण

अटल पूर्णांक fat_ioctl_get_volume_id(काष्ठा inode *inode, u32 __user *user_attr)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	वापस put_user(sbi->vol_id, user_attr);
पूर्ण

अटल पूर्णांक fat_ioctl_fitrim(काष्ठा inode *inode, अचिन्हित दीर्घ arg)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा fstrim_range __user *user_range;
	काष्ठा fstrim_range range;
	काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!blk_queue_discard(q))
		वापस -EOPNOTSUPP;

	user_range = (काष्ठा fstrim_range __user *)arg;
	अगर (copy_from_user(&range, user_range, माप(range)))
		वापस -EFAULT;

	range.minlen = max_t(अचिन्हित पूर्णांक, range.minlen,
			     q->limits.discard_granularity);

	err = fat_trim_fs(inode, &range);
	अगर (err < 0)
		वापस err;

	अगर (copy_to_user(user_range, &range, माप(range)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

दीर्घ fat_generic_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	u32 __user *user_attr = (u32 __user *)arg;

	चयन (cmd) अणु
	हाल FAT_IOCTL_GET_ATTRIBUTES:
		वापस fat_ioctl_get_attributes(inode, user_attr);
	हाल FAT_IOCTL_SET_ATTRIBUTES:
		वापस fat_ioctl_set_attributes(filp, user_attr);
	हाल FAT_IOCTL_GET_VOLUME_ID:
		वापस fat_ioctl_get_volume_id(inode, user_attr);
	हाल FITRIM:
		वापस fat_ioctl_fitrim(inode, arg);
	शेष:
		वापस -ENOTTY;	/* Inappropriate ioctl क्रम device */
	पूर्ण
पूर्ण

अटल पूर्णांक fat_file_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अगर ((filp->f_mode & FMODE_WRITE) &&
	     MSDOS_SB(inode->i_sb)->options.flush) अणु
		fat_flush_inodes(inode->i_sb, inode, शून्य);
		congestion_रुको(BLK_RW_ASYNC, HZ/10);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक fat_file_fsync(काष्ठा file *filp, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	पूर्णांक err;

	err = __generic_file_fsync(filp, start, end, datasync);
	अगर (err)
		वापस err;

	err = sync_mapping_buffers(MSDOS_SB(inode->i_sb)->fat_inode->i_mapping);
	अगर (err)
		वापस err;

	वापस blkdev_issue_flush(inode->i_sb->s_bdev);
पूर्ण


स्थिर काष्ठा file_operations fat_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.mmap		= generic_file_mmap,
	.release	= fat_file_release,
	.unlocked_ioctl	= fat_generic_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.fsync		= fat_file_fsync,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.fallocate	= fat_fallocate,
पूर्ण;

अटल पूर्णांक fat_cont_expand(काष्ठा inode *inode, loff_t size)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	loff_t start = inode->i_size, count = size - inode->i_size;
	पूर्णांक err;

	err = generic_cont_expand_simple(inode, size);
	अगर (err)
		जाओ out;

	fat_truncate_समय(inode, शून्य, S_CTIME|S_MTIME);
	mark_inode_dirty(inode);
	अगर (IS_SYNC(inode)) अणु
		पूर्णांक err2;

		/*
		 * Opencode syncing since we करोn't have a file खोलो to use
		 * standard fsync path.
		 */
		err = filemap_fdataग_लिखो_range(mapping, start,
					       start + count - 1);
		err2 = sync_mapping_buffers(mapping);
		अगर (!err)
			err = err2;
		err2 = ग_लिखो_inode_now(inode, 1);
		अगर (!err)
			err = err2;
		अगर (!err) अणु
			err =  filemap_fdataरुको_range(mapping, start,
						       start + count - 1);
		पूर्ण
	पूर्ण
out:
	वापस err;
पूर्ण

/*
 * Pपुनः_स्मृतिate space क्रम a file. This implements fat's fallocate file
 * operation, which माला_लो called from sys_fallocate प्रणाली call. User
 * space requests len bytes at offset. If FALLOC_FL_KEEP_SIZE is set
 * we just allocate clusters without zeroing them out. Otherwise we
 * allocate and zero out clusters via an expanding truncate.
 */
अटल दीर्घ fat_fallocate(काष्ठा file *file, पूर्णांक mode,
			  loff_t offset, loff_t len)
अणु
	पूर्णांक nr_cluster; /* Number of clusters to be allocated */
	loff_t mm_bytes; /* Number of bytes to be allocated क्रम file */
	loff_t ondisksize; /* block aligned on-disk size in bytes*/
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	पूर्णांक err = 0;

	/* No support क्रम hole punch or other fallocate flags. */
	अगर (mode & ~FALLOC_FL_KEEP_SIZE)
		वापस -EOPNOTSUPP;

	/* No support क्रम dir */
	अगर (!S_ISREG(inode->i_mode))
		वापस -EOPNOTSUPP;

	inode_lock(inode);
	अगर (mode & FALLOC_FL_KEEP_SIZE) अणु
		ondisksize = inode->i_blocks << 9;
		अगर ((offset + len) <= ondisksize)
			जाओ error;

		/* First compute the number of clusters to be allocated */
		mm_bytes = offset + len - ondisksize;
		nr_cluster = (mm_bytes + (sbi->cluster_size - 1)) >>
			sbi->cluster_bits;

		/* Start the allocation.We are not zeroing out the clusters */
		जबतक (nr_cluster-- > 0) अणु
			err = fat_add_cluster(inode);
			अगर (err)
				जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((offset + len) <= i_size_पढ़ो(inode))
			जाओ error;

		/* This is just an expanding truncate */
		err = fat_cont_expand(inode, (offset + len));
	पूर्ण

error:
	inode_unlock(inode);
	वापस err;
पूर्ण

/* Free all clusters after the skip'th cluster. */
अटल पूर्णांक fat_मुक्त(काष्ठा inode *inode, पूर्णांक skip)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक err, रुको, मुक्त_start, i_start, i_logstart;

	अगर (MSDOS_I(inode)->i_start == 0)
		वापस 0;

	fat_cache_inval_inode(inode);

	रुको = IS_सूचीSYNC(inode);
	i_start = मुक्त_start = MSDOS_I(inode)->i_start;
	i_logstart = MSDOS_I(inode)->i_logstart;

	/* First, we ग_लिखो the new file size. */
	अगर (!skip) अणु
		MSDOS_I(inode)->i_start = 0;
		MSDOS_I(inode)->i_logstart = 0;
	पूर्ण
	MSDOS_I(inode)->i_attrs |= ATTR_ARCH;
	fat_truncate_समय(inode, शून्य, S_CTIME|S_MTIME);
	अगर (रुको) अणु
		err = fat_sync_inode(inode);
		अगर (err) अणु
			MSDOS_I(inode)->i_start = i_start;
			MSDOS_I(inode)->i_logstart = i_logstart;
			वापस err;
		पूर्ण
	पूर्ण अन्यथा
		mark_inode_dirty(inode);

	/* Write a new खातापूर्ण, and get the reमुख्यing cluster chain क्रम मुक्तing. */
	अगर (skip) अणु
		काष्ठा fat_entry fatent;
		पूर्णांक ret, fclus, dclus;

		ret = fat_get_cluster(inode, skip - 1, &fclus, &dclus);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret == FAT_ENT_खातापूर्ण)
			वापस 0;

		fatent_init(&fatent);
		ret = fat_ent_पढ़ो(inode, &fatent, dclus);
		अगर (ret == FAT_ENT_खातापूर्ण) अणु
			fatent_brअन्यथा(&fatent);
			वापस 0;
		पूर्ण अन्यथा अगर (ret == FAT_ENT_FREE) अणु
			fat_fs_error(sb,
				     "%s: invalid cluster chain (i_pos %lld)",
				     __func__, MSDOS_I(inode)->i_pos);
			ret = -EIO;
		पूर्ण अन्यथा अगर (ret > 0) अणु
			err = fat_ent_ग_लिखो(inode, &fatent, FAT_ENT_खातापूर्ण, रुको);
			अगर (err)
				ret = err;
		पूर्ण
		fatent_brअन्यथा(&fatent);
		अगर (ret < 0)
			वापस ret;

		मुक्त_start = ret;
	पूर्ण
	inode->i_blocks = skip << (MSDOS_SB(sb)->cluster_bits - 9);

	/* Freeing the reमुख्यed cluster chain */
	वापस fat_मुक्त_clusters(inode, मुक्त_start);
पूर्ण

व्योम fat_truncate_blocks(काष्ठा inode *inode, loff_t offset)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(inode->i_sb);
	स्थिर अचिन्हित पूर्णांक cluster_size = sbi->cluster_size;
	पूर्णांक nr_clusters;

	/*
	 * This protects against truncating a file bigger than it was then
	 * trying to ग_लिखो पूर्णांकo the hole.
	 */
	अगर (MSDOS_I(inode)->mmu_निजी > offset)
		MSDOS_I(inode)->mmu_निजी = offset;

	nr_clusters = (offset + (cluster_size - 1)) >> sbi->cluster_bits;

	fat_मुक्त(inode, nr_clusters);
	fat_flush_inodes(inode->i_sb, inode, शून्य);
पूर्ण

पूर्णांक fat_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	generic_fillattr(mnt_userns, inode, stat);
	stat->blksize = MSDOS_SB(inode->i_sb)->cluster_size;

	अगर (MSDOS_SB(inode->i_sb)->options.nfs == FAT_NFS_NOSTALE_RO) अणु
		/* Use i_pos क्रम ino. This is used as fileid of nfs. */
		stat->ino = fat_i_pos_पढ़ो(MSDOS_SB(inode->i_sb), inode);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fat_getattr);

अटल पूर्णांक fat_sanitize_mode(स्थिर काष्ठा msकरोs_sb_info *sbi,
			     काष्ठा inode *inode, umode_t *mode_ptr)
अणु
	umode_t mask, perm;

	/*
	 * Note, the basic check is alपढ़ोy करोne by a caller of
	 * (attr->ia_mode & ~FAT_VALID_MODE)
	 */

	अगर (S_ISREG(inode->i_mode))
		mask = sbi->options.fs_fmask;
	अन्यथा
		mask = sbi->options.fs_dmask;

	perm = *mode_ptr & ~(S_IFMT | mask);

	/*
	 * Of the r and x bits, all (subject to umask) must be present. Of the
	 * w bits, either all (subject to umask) or none must be present.
	 *
	 * If fat_mode_can_hold_ro(inode) is false, can't change w bits.
	 */
	अगर ((perm & (S_IRUGO | S_IXUGO)) != (inode->i_mode & (S_IRUGO|S_IXUGO)))
		वापस -EPERM;
	अगर (fat_mode_can_hold_ro(inode)) अणु
		अगर ((perm & S_IWUGO) && ((perm & S_IWUGO) != (S_IWUGO & ~mask)))
			वापस -EPERM;
	पूर्ण अन्यथा अणु
		अगर ((perm & S_IWUGO) != (S_IWUGO & ~mask))
			वापस -EPERM;
	पूर्ण

	*mode_ptr &= S_IFMT | perm;

	वापस 0;
पूर्ण

अटल पूर्णांक fat_allow_set_समय(काष्ठा user_namespace *mnt_userns,
			      काष्ठा msकरोs_sb_info *sbi, काष्ठा inode *inode)
अणु
	umode_t allow_uसमय = sbi->options.allow_uसमय;

	अगर (!uid_eq(current_fsuid(), i_uid_पूर्णांकo_mnt(mnt_userns, inode))) अणु
		अगर (in_group_p(i_gid_पूर्णांकo_mnt(mnt_userns, inode)))
			allow_uसमय >>= 3;
		अगर (allow_uसमय & MAY_WRITE)
			वापस 1;
	पूर्ण

	/* use a शेष check */
	वापस 0;
पूर्ण

#घोषणा TIMES_SET_FLAGS	(ATTR_MTIME_SET | ATTR_ATIME_SET | ATTR_TIMES_SET)
/* valid file mode bits */
#घोषणा FAT_VALID_MODE	(S_IFREG | S_IFसूची | S_IRWXUGO)

पूर्णांक fat_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		काष्ठा iattr *attr)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(dentry->d_sb);
	काष्ठा inode *inode = d_inode(dentry);
	अचिन्हित पूर्णांक ia_valid;
	पूर्णांक error;

	/* Check क्रम setting the inode समय. */
	ia_valid = attr->ia_valid;
	अगर (ia_valid & TIMES_SET_FLAGS) अणु
		अगर (fat_allow_set_समय(mnt_userns, sbi, inode))
			attr->ia_valid &= ~TIMES_SET_FLAGS;
	पूर्ण

	error = setattr_prepare(mnt_userns, dentry, attr);
	attr->ia_valid = ia_valid;
	अगर (error) अणु
		अगर (sbi->options.quiet)
			error = 0;
		जाओ out;
	पूर्ण

	/*
	 * Expand the file. Since inode_setattr() updates ->i_size
	 * beक्रमe calling the ->truncate(), but FAT needs to fill the
	 * hole beक्रमe it. XXX: this is no दीर्घer true with new truncate
	 * sequence.
	 */
	अगर (attr->ia_valid & ATTR_SIZE) अणु
		inode_dio_रुको(inode);

		अगर (attr->ia_size > inode->i_size) अणु
			error = fat_cont_expand(inode, attr->ia_size);
			अगर (error || attr->ia_valid == ATTR_SIZE)
				जाओ out;
			attr->ia_valid &= ~ATTR_SIZE;
		पूर्ण
	पूर्ण

	अगर (((attr->ia_valid & ATTR_UID) &&
	     (!uid_eq(attr->ia_uid, sbi->options.fs_uid))) ||
	    ((attr->ia_valid & ATTR_GID) &&
	     (!gid_eq(attr->ia_gid, sbi->options.fs_gid))) ||
	    ((attr->ia_valid & ATTR_MODE) &&
	     (attr->ia_mode & ~FAT_VALID_MODE)))
		error = -EPERM;

	अगर (error) अणु
		अगर (sbi->options.quiet)
			error = 0;
		जाओ out;
	पूर्ण

	/*
	 * We करोn't वापस -EPERM here. Yes, strange, but this is too
	 * old behavior.
	 */
	अगर (attr->ia_valid & ATTR_MODE) अणु
		अगर (fat_sanitize_mode(sbi, inode, &attr->ia_mode) < 0)
			attr->ia_valid &= ~ATTR_MODE;
	पूर्ण

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		error = fat_block_truncate_page(inode, attr->ia_size);
		अगर (error)
			जाओ out;
		करोwn_ग_लिखो(&MSDOS_I(inode)->truncate_lock);
		truncate_setsize(inode, attr->ia_size);
		fat_truncate_blocks(inode, attr->ia_size);
		up_ग_लिखो(&MSDOS_I(inode)->truncate_lock);
	पूर्ण

	/*
	 * setattr_copy can't truncate these appropriately, so we'll
	 * copy them ourselves
	 */
	अगर (attr->ia_valid & ATTR_ATIME)
		fat_truncate_समय(inode, &attr->ia_aसमय, S_ATIME);
	अगर (attr->ia_valid & ATTR_CTIME)
		fat_truncate_समय(inode, &attr->ia_स_समय, S_CTIME);
	अगर (attr->ia_valid & ATTR_MTIME)
		fat_truncate_समय(inode, &attr->ia_mसमय, S_MTIME);
	attr->ia_valid &= ~(ATTR_ATIME|ATTR_CTIME|ATTR_MTIME);

	setattr_copy(mnt_userns, inode, attr);
	mark_inode_dirty(inode);
out:
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(fat_setattr);

स्थिर काष्ठा inode_operations fat_file_inode_operations = अणु
	.setattr	= fat_setattr,
	.getattr	= fat_getattr,
	.update_समय	= fat_update_समय,
पूर्ण;
