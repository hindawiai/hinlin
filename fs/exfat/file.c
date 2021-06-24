<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/cred.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/blkdev.h>

#समावेश "exfat_raw.h"
#समावेश "exfat_fs.h"

अटल पूर्णांक exfat_cont_expand(काष्ठा inode *inode, loff_t size)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	loff_t start = i_size_पढ़ो(inode), count = size - i_size_पढ़ो(inode);
	पूर्णांक err, err2;

	err = generic_cont_expand_simple(inode, size);
	अगर (err)
		वापस err;

	inode->i_स_समय = inode->i_mसमय = current_समय(inode);
	mark_inode_dirty(inode);

	अगर (!IS_SYNC(inode))
		वापस 0;

	err = filemap_fdataग_लिखो_range(mapping, start, start + count - 1);
	err2 = sync_mapping_buffers(mapping);
	अगर (!err)
		err = err2;
	err2 = ग_लिखो_inode_now(inode, 1);
	अगर (!err)
		err = err2;
	अगर (err)
		वापस err;

	वापस filemap_fdataरुको_range(mapping, start, start + count - 1);
पूर्ण

अटल bool exfat_allow_set_समय(काष्ठा exfat_sb_info *sbi, काष्ठा inode *inode)
अणु
	mode_t allow_uसमय = sbi->options.allow_uसमय;

	अगर (!uid_eq(current_fsuid(), inode->i_uid)) अणु
		अगर (in_group_p(inode->i_gid))
			allow_uसमय >>= 3;
		अगर (allow_uसमय & MAY_WRITE)
			वापस true;
	पूर्ण

	/* use a शेष check */
	वापस false;
पूर्ण

अटल पूर्णांक exfat_sanitize_mode(स्थिर काष्ठा exfat_sb_info *sbi,
		काष्ठा inode *inode, umode_t *mode_ptr)
अणु
	mode_t i_mode, mask, perm;

	i_mode = inode->i_mode;

	mask = (S_ISREG(i_mode) || S_ISLNK(i_mode)) ?
		sbi->options.fs_fmask : sbi->options.fs_dmask;
	perm = *mode_ptr & ~(S_IFMT | mask);

	/* Of the r and x bits, all (subject to umask) must be present.*/
	अगर ((perm & 0555) != (i_mode & 0555))
		वापस -EPERM;

	अगर (exfat_mode_can_hold_ro(inode)) अणु
		/*
		 * Of the w bits, either all (subject to umask) or none must
		 * be present.
		 */
		अगर ((perm & 0222) && ((perm & 0222) != (0222 & ~mask)))
			वापस -EPERM;
	पूर्ण अन्यथा अणु
		/*
		 * If exfat_mode_can_hold_ro(inode) is false, can't change
		 * w bits.
		 */
		अगर ((perm & 0222) != (0222 & ~mask))
			वापस -EPERM;
	पूर्ण

	*mode_ptr &= S_IFMT | perm;

	वापस 0;
पूर्ण

/* resize the file length */
पूर्णांक __exfat_truncate(काष्ठा inode *inode, loff_t new_size)
अणु
	अचिन्हित पूर्णांक num_clusters_new, num_clusters_phys;
	अचिन्हित पूर्णांक last_clu = EXFAT_FREE_CLUSTER;
	काष्ठा exfat_chain clu;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	पूर्णांक evict = (ei->dir.dir == सूची_DELETED) ? 1 : 0;

	/* check अगर the given file ID is खोलोed */
	अगर (ei->type != TYPE_खाता && ei->type != TYPE_सूची)
		वापस -EPERM;

	exfat_set_volume_dirty(sb);

	num_clusters_new = EXFAT_B_TO_CLU_ROUND_UP(i_size_पढ़ो(inode), sbi);
	num_clusters_phys =
		EXFAT_B_TO_CLU_ROUND_UP(EXFAT_I(inode)->i_size_ondisk, sbi);

	exfat_chain_set(&clu, ei->start_clu, num_clusters_phys, ei->flags);

	अगर (new_size > 0) अणु
		/*
		 * Truncate FAT chain num_clusters after the first cluster
		 * num_clusters = min(new, phys);
		 */
		अचिन्हित पूर्णांक num_clusters =
			min(num_clusters_new, num_clusters_phys);

		/*
		 * Follow FAT chain
		 * (defensive coding - works fine even with corrupted FAT table
		 */
		अगर (clu.flags == ALLOC_NO_FAT_CHAIN) अणु
			clu.dir += num_clusters;
			clu.size -= num_clusters;
		पूर्ण अन्यथा अणु
			जबतक (num_clusters > 0) अणु
				last_clu = clu.dir;
				अगर (exfat_get_next_cluster(sb, &(clu.dir)))
					वापस -EIO;

				num_clusters--;
				clu.size--;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		ei->flags = ALLOC_NO_FAT_CHAIN;
		ei->start_clu = EXFAT_खातापूर्ण_CLUSTER;
	पूर्ण

	i_size_ग_लिखो(inode, new_size);

	अगर (ei->type == TYPE_खाता)
		ei->attr |= ATTR_ARCHIVE;

	/* update the directory entry */
	अगर (!evict) अणु
		काष्ठा बारpec64 ts;
		काष्ठा exfat_dentry *ep, *ep2;
		काष्ठा exfat_entry_set_cache *es;
		पूर्णांक err;

		es = exfat_get_dentry_set(sb, &(ei->dir), ei->entry,
				ES_ALL_ENTRIES);
		अगर (!es)
			वापस -EIO;
		ep = exfat_get_dentry_cached(es, 0);
		ep2 = exfat_get_dentry_cached(es, 1);

		ts = current_समय(inode);
		exfat_set_entry_समय(sbi, &ts,
				&ep->dentry.file.modअगरy_tz,
				&ep->dentry.file.modअगरy_समय,
				&ep->dentry.file.modअगरy_date,
				&ep->dentry.file.modअगरy_समय_cs);
		ep->dentry.file.attr = cpu_to_le16(ei->attr);

		/* File size should be zero अगर there is no cluster allocated */
		अगर (ei->start_clu == EXFAT_खातापूर्ण_CLUSTER) अणु
			ep2->dentry.stream.valid_size = 0;
			ep2->dentry.stream.size = 0;
		पूर्ण अन्यथा अणु
			ep2->dentry.stream.valid_size = cpu_to_le64(new_size);
			ep2->dentry.stream.size = ep2->dentry.stream.valid_size;
		पूर्ण

		अगर (new_size == 0) अणु
			/* Any directory can not be truncated to zero */
			WARN_ON(ei->type != TYPE_खाता);

			ep2->dentry.stream.flags = ALLOC_FAT_CHAIN;
			ep2->dentry.stream.start_clu = EXFAT_FREE_CLUSTER;
		पूर्ण

		exfat_update_dir_chksum_with_entry_set(es);
		err = exfat_मुक्त_dentry_set(es, inode_needs_sync(inode));
		अगर (err)
			वापस err;
	पूर्ण

	/* cut off from the FAT chain */
	अगर (ei->flags == ALLOC_FAT_CHAIN && last_clu != EXFAT_FREE_CLUSTER &&
			last_clu != EXFAT_खातापूर्ण_CLUSTER) अणु
		अगर (exfat_ent_set(sb, last_clu, EXFAT_खातापूर्ण_CLUSTER))
			वापस -EIO;
	पूर्ण

	/* invalidate cache and मुक्त the clusters */
	/* clear exfat cache */
	exfat_cache_inval_inode(inode);

	/* hपूर्णांक inक्रमmation */
	ei->hपूर्णांक_bmap.off = EXFAT_खातापूर्ण_CLUSTER;
	ei->hपूर्णांक_bmap.clu = EXFAT_खातापूर्ण_CLUSTER;

	/* hपूर्णांक_stat will be used अगर this is directory. */
	ei->hपूर्णांक_stat.eidx = 0;
	ei->hपूर्णांक_stat.clu = ei->start_clu;
	ei->hपूर्णांक_femp.eidx = EXFAT_HINT_NONE;

	/* मुक्त the clusters */
	अगर (exfat_मुक्त_cluster(inode, &clu))
		वापस -EIO;

	exfat_clear_volume_dirty(sb);

	वापस 0;
पूर्ण

व्योम exfat_truncate(काष्ठा inode *inode, loff_t size)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	अचिन्हित पूर्णांक blocksize = i_blocksize(inode);
	loff_t aligned_size;
	पूर्णांक err;

	mutex_lock(&sbi->s_lock);
	अगर (EXFAT_I(inode)->start_clu == 0) अणु
		/*
		 * Empty start_clu != ~0 (not allocated)
		 */
		exfat_fs_error(sb, "tried to truncate zeroed cluster.");
		जाओ ग_लिखो_size;
	पूर्ण

	err = __exfat_truncate(inode, i_size_पढ़ो(inode));
	अगर (err)
		जाओ ग_लिखो_size;

	inode->i_स_समय = inode->i_mसमय = current_समय(inode);
	अगर (IS_सूचीSYNC(inode))
		exfat_sync_inode(inode);
	अन्यथा
		mark_inode_dirty(inode);

	inode->i_blocks = ((i_size_पढ़ो(inode) + (sbi->cluster_size - 1)) &
			~(sbi->cluster_size - 1)) >> inode->i_blkbits;
ग_लिखो_size:
	aligned_size = i_size_पढ़ो(inode);
	अगर (aligned_size & (blocksize - 1)) अणु
		aligned_size |= (blocksize - 1);
		aligned_size++;
	पूर्ण

	अगर (EXFAT_I(inode)->i_size_ondisk > i_size_पढ़ो(inode))
		EXFAT_I(inode)->i_size_ondisk = aligned_size;

	अगर (EXFAT_I(inode)->i_size_aligned > i_size_पढ़ो(inode))
		EXFAT_I(inode)->i_size_aligned = aligned_size;
	mutex_unlock(&sbi->s_lock);
पूर्ण

पूर्णांक exfat_getattr(काष्ठा user_namespace *mnt_uerns, स्थिर काष्ठा path *path,
		  काष्ठा kstat *stat, अचिन्हित पूर्णांक request_mask,
		  अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_backing_inode(path->dentry);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);

	generic_fillattr(&init_user_ns, inode, stat);
	exfat_truncate_aसमय(&stat->aसमय);
	stat->result_mask |= STATX_BTIME;
	stat->bसमय.tv_sec = ei->i_crसमय.tv_sec;
	stat->bसमय.tv_nsec = ei->i_crसमय.tv_nsec;
	stat->blksize = EXFAT_SB(inode->i_sb)->cluster_size;
	वापस 0;
पूर्ण

पूर्णांक exfat_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		  काष्ठा iattr *attr)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(dentry->d_sb);
	काष्ठा inode *inode = dentry->d_inode;
	अचिन्हित पूर्णांक ia_valid;
	पूर्णांक error;

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size > i_size_पढ़ो(inode)) अणु
		error = exfat_cont_expand(inode, attr->ia_size);
		अगर (error || attr->ia_valid == ATTR_SIZE)
			वापस error;
		attr->ia_valid &= ~ATTR_SIZE;
	पूर्ण

	/* Check क्रम setting the inode समय. */
	ia_valid = attr->ia_valid;
	अगर ((ia_valid & (ATTR_MTIME_SET | ATTR_ATIME_SET | ATTR_TIMES_SET)) &&
	    exfat_allow_set_समय(sbi, inode)) अणु
		attr->ia_valid &= ~(ATTR_MTIME_SET | ATTR_ATIME_SET |
				ATTR_TIMES_SET);
	पूर्ण

	error = setattr_prepare(&init_user_ns, dentry, attr);
	attr->ia_valid = ia_valid;
	अगर (error)
		जाओ out;

	अगर (((attr->ia_valid & ATTR_UID) &&
	     !uid_eq(attr->ia_uid, sbi->options.fs_uid)) ||
	    ((attr->ia_valid & ATTR_GID) &&
	     !gid_eq(attr->ia_gid, sbi->options.fs_gid)) ||
	    ((attr->ia_valid & ATTR_MODE) &&
	     (attr->ia_mode & ~(S_IFREG | S_IFLNK | S_IFसूची | 0777)))) अणु
		error = -EPERM;
		जाओ out;
	पूर्ण

	/*
	 * We करोn't वापस -EPERM here. Yes, strange, but this is too
	 * old behavior.
	 */
	अगर (attr->ia_valid & ATTR_MODE) अणु
		अगर (exfat_sanitize_mode(sbi, inode, &attr->ia_mode) < 0)
			attr->ia_valid &= ~ATTR_MODE;
	पूर्ण

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		error = exfat_block_truncate_page(inode, attr->ia_size);
		अगर (error)
			जाओ out;

		करोwn_ग_लिखो(&EXFAT_I(inode)->truncate_lock);
		truncate_setsize(inode, attr->ia_size);
		exfat_truncate(inode, attr->ia_size);
		up_ग_लिखो(&EXFAT_I(inode)->truncate_lock);
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);
	exfat_truncate_aसमय(&inode->i_aसमय);
	mark_inode_dirty(inode);

out:
	वापस error;
पूर्ण

अटल पूर्णांक exfat_ioctl_fitrim(काष्ठा inode *inode, अचिन्हित दीर्घ arg)
अणु
	काष्ठा request_queue *q = bdev_get_queue(inode->i_sb->s_bdev);
	काष्ठा fstrim_range range;
	पूर्णांक ret = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!blk_queue_discard(q))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&range, (काष्ठा fstrim_range __user *)arg, माप(range)))
		वापस -EFAULT;

	range.minlen = max_t(अचिन्हित पूर्णांक, range.minlen,
				q->limits.discard_granularity);

	ret = exfat_trim_fs(inode, &range);
	अगर (ret < 0)
		वापस ret;

	अगर (copy_to_user((काष्ठा fstrim_range __user *)arg, &range, माप(range)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

दीर्घ exfat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);

	चयन (cmd) अणु
	हाल FITRIM:
		वापस exfat_ioctl_fitrim(inode, arg);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
दीर्घ exfat_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	वापस exfat_ioctl(filp, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

पूर्णांक exfat_file_fsync(काष्ठा file *filp, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	पूर्णांक err;

	err = __generic_file_fsync(filp, start, end, datasync);
	अगर (err)
		वापस err;

	err = sync_blockdev(inode->i_sb->s_bdev);
	अगर (err)
		वापस err;

	वापस blkdev_issue_flush(inode->i_sb->s_bdev);
पूर्ण

स्थिर काष्ठा file_operations exfat_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.unlocked_ioctl = exfat_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = exfat_compat_ioctl,
#पूर्ण_अगर
	.mmap		= generic_file_mmap,
	.fsync		= exfat_file_fsync,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
पूर्ण;

स्थिर काष्ठा inode_operations exfat_file_inode_operations = अणु
	.setattr     = exfat_setattr,
	.getattr     = exfat_getattr,
पूर्ण;
