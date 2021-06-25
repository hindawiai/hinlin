<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext4/ioctl.c
 *
 * Copyright (C) 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 */

#समावेश <linux/fs.h>
#समावेश <linux/capability.h>
#समावेश <linux/समय.स>
#समावेश <linux/compat.h>
#समावेश <linux/mount.h>
#समावेश <linux/file.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/uuid.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/iversion.h>
#समावेश <linux/fileattr.h>
#समावेश "ext4_jbd2.h"
#समावेश "ext4.h"
#समावेश <linux/fsmap.h>
#समावेश "fsmap.h"
#समावेश <trace/events/ext4.h>

/**
 * Swap memory between @a and @b क्रम @len bytes.
 *
 * @a:          poपूर्णांकer to first memory area
 * @b:          poपूर्णांकer to second memory area
 * @len:        number of bytes to swap
 *
 */
अटल व्योम memswap(व्योम *a, व्योम *b, माप_प्रकार len)
अणु
	अचिन्हित अक्षर *ap, *bp;

	ap = (अचिन्हित अक्षर *)a;
	bp = (अचिन्हित अक्षर *)b;
	जबतक (len-- > 0) अणु
		swap(*ap, *bp);
		ap++;
		bp++;
	पूर्ण
पूर्ण

/**
 * Swap i_data and associated attributes between @inode1 and @inode2.
 * This function is used क्रम the primary swap between inode1 and inode2
 * and also to revert this primary swap in हाल of errors.
 *
 * Thereक्रमe you have to make sure, that calling this method twice
 * will revert all changes.
 *
 * @inode1:     poपूर्णांकer to first inode
 * @inode2:     poपूर्णांकer to second inode
 */
अटल व्योम swap_inode_data(काष्ठा inode *inode1, काष्ठा inode *inode2)
अणु
	loff_t isize;
	काष्ठा ext4_inode_info *ei1;
	काष्ठा ext4_inode_info *ei2;
	अचिन्हित दीर्घ पंचांगp;

	ei1 = EXT4_I(inode1);
	ei2 = EXT4_I(inode2);

	swap(inode1->i_version, inode2->i_version);
	swap(inode1->i_aसमय, inode2->i_aसमय);
	swap(inode1->i_mसमय, inode2->i_mसमय);

	memswap(ei1->i_data, ei2->i_data, माप(ei1->i_data));
	पंचांगp = ei1->i_flags & EXT4_FL_SHOULD_SWAP;
	ei1->i_flags = (ei2->i_flags & EXT4_FL_SHOULD_SWAP) |
		(ei1->i_flags & ~EXT4_FL_SHOULD_SWAP);
	ei2->i_flags = पंचांगp | (ei2->i_flags & ~EXT4_FL_SHOULD_SWAP);
	swap(ei1->i_disksize, ei2->i_disksize);
	ext4_es_हटाओ_extent(inode1, 0, EXT_MAX_BLOCKS);
	ext4_es_हटाओ_extent(inode2, 0, EXT_MAX_BLOCKS);

	isize = i_size_पढ़ो(inode1);
	i_size_ग_लिखो(inode1, i_size_पढ़ो(inode2));
	i_size_ग_लिखो(inode2, isize);
पूर्ण

व्योम ext4_reset_inode_seed(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	__le32 inum = cpu_to_le32(inode->i_ino);
	__le32 gen = cpu_to_le32(inode->i_generation);
	__u32 csum;

	अगर (!ext4_has_metadata_csum(inode->i_sb))
		वापस;

	csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)&inum, माप(inum));
	ei->i_csum_seed = ext4_chksum(sbi, csum, (__u8 *)&gen, माप(gen));
पूर्ण

/**
 * Swap the inक्रमmation from the given @inode and the inode
 * EXT4_BOOT_LOADER_INO. It will basically swap i_data and all other
 * important fields of the inodes.
 *
 * @sb:         the super block of the fileप्रणाली
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode:      the inode to swap with EXT4_BOOT_LOADER_INO
 *
 */
अटल दीर्घ swap_inode_boot_loader(काष्ठा super_block *sb,
				काष्ठा user_namespace *mnt_userns,
				काष्ठा inode *inode)
अणु
	handle_t *handle;
	पूर्णांक err;
	काष्ठा inode *inode_bl;
	काष्ठा ext4_inode_info *ei_bl;
	qमाप_प्रकार size, size_bl, dअगरf;
	blkcnt_t blocks;
	अचिन्हित लघु bytes;

	inode_bl = ext4_iget(sb, EXT4_BOOT_LOADER_INO, EXT4_IGET_SPECIAL);
	अगर (IS_ERR(inode_bl))
		वापस PTR_ERR(inode_bl);
	ei_bl = EXT4_I(inode_bl);

	/* Protect orig inodes against a truncate and make sure,
	 * that only 1 swap_inode_boot_loader is running. */
	lock_two_nondirectories(inode, inode_bl);

	अगर (inode->i_nlink != 1 || !S_ISREG(inode->i_mode) ||
	    IS_SWAPखाता(inode) || IS_ENCRYPTED(inode) ||
	    (EXT4_I(inode)->i_flags & EXT4_JOURNAL_DATA_FL) ||
	    ext4_has_अंतरभूत_data(inode)) अणु
		err = -EINVAL;
		जाओ journal_err_out;
	पूर्ण

	अगर (IS_RDONLY(inode) || IS_APPEND(inode) || IS_IMMUTABLE(inode) ||
	    !inode_owner_or_capable(mnt_userns, inode) ||
	    !capable(CAP_SYS_ADMIN)) अणु
		err = -EPERM;
		जाओ journal_err_out;
	पूर्ण

	करोwn_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
	err = filemap_ग_लिखो_and_रुको(inode->i_mapping);
	अगर (err)
		जाओ err_out;

	err = filemap_ग_लिखो_and_रुको(inode_bl->i_mapping);
	अगर (err)
		जाओ err_out;

	/* Wait क्रम all existing dio workers */
	inode_dio_रुको(inode);
	inode_dio_रुको(inode_bl);

	truncate_inode_pages(&inode->i_data, 0);
	truncate_inode_pages(&inode_bl->i_data, 0);

	handle = ext4_journal_start(inode_bl, EXT4_HT_MOVE_EXTENTS, 2);
	अगर (IS_ERR(handle)) अणु
		err = -EINVAL;
		जाओ err_out;
	पूर्ण
	ext4_fc_start_ineligible(sb, EXT4_FC_REASON_SWAP_BOOT);

	/* Protect extent tree against block allocations via delalloc */
	ext4_द्विगुन_करोwn_ग_लिखो_data_sem(inode, inode_bl);

	अगर (inode_bl->i_nlink == 0) अणु
		/* this inode has never been used as a BOOT_LOADER */
		set_nlink(inode_bl, 1);
		i_uid_ग_लिखो(inode_bl, 0);
		i_gid_ग_लिखो(inode_bl, 0);
		inode_bl->i_flags = 0;
		ei_bl->i_flags = 0;
		inode_set_iversion(inode_bl, 1);
		i_size_ग_लिखो(inode_bl, 0);
		inode_bl->i_mode = S_IFREG;
		अगर (ext4_has_feature_extents(sb)) अणु
			ext4_set_inode_flag(inode_bl, EXT4_INODE_EXTENTS);
			ext4_ext_tree_init(handle, inode_bl);
		पूर्ण अन्यथा
			स_रखो(ei_bl->i_data, 0, माप(ei_bl->i_data));
	पूर्ण

	err = dquot_initialize(inode);
	अगर (err)
		जाओ err_out1;

	size = (qमाप_प्रकार)(inode->i_blocks) * (1 << 9) + inode->i_bytes;
	size_bl = (qमाप_प्रकार)(inode_bl->i_blocks) * (1 << 9) + inode_bl->i_bytes;
	dअगरf = size - size_bl;
	swap_inode_data(inode, inode_bl);

	inode->i_स_समय = inode_bl->i_स_समय = current_समय(inode);

	inode->i_generation = pअक्रमom_u32();
	inode_bl->i_generation = pअक्रमom_u32();
	ext4_reset_inode_seed(inode);
	ext4_reset_inode_seed(inode_bl);

	ext4_discard_pपुनः_स्मृतिations(inode, 0);

	err = ext4_mark_inode_dirty(handle, inode);
	अगर (err < 0) अणु
		/* No need to update quota inक्रमmation. */
		ext4_warning(inode->i_sb,
			"couldn't mark inode #%lu dirty (err %d)",
			inode->i_ino, err);
		/* Revert all changes: */
		swap_inode_data(inode, inode_bl);
		ext4_mark_inode_dirty(handle, inode);
		जाओ err_out1;
	पूर्ण

	blocks = inode_bl->i_blocks;
	bytes = inode_bl->i_bytes;
	inode_bl->i_blocks = inode->i_blocks;
	inode_bl->i_bytes = inode->i_bytes;
	err = ext4_mark_inode_dirty(handle, inode_bl);
	अगर (err < 0) अणु
		/* No need to update quota inक्रमmation. */
		ext4_warning(inode_bl->i_sb,
			"couldn't mark inode #%lu dirty (err %d)",
			inode_bl->i_ino, err);
		जाओ revert;
	पूर्ण

	/* Bootloader inode should not be counted पूर्णांकo quota inक्रमmation. */
	अगर (dअगरf > 0)
		dquot_मुक्त_space(inode, dअगरf);
	अन्यथा
		err = dquot_alloc_space(inode, -1 * dअगरf);

	अगर (err < 0) अणु
revert:
		/* Revert all changes: */
		inode_bl->i_blocks = blocks;
		inode_bl->i_bytes = bytes;
		swap_inode_data(inode, inode_bl);
		ext4_mark_inode_dirty(handle, inode);
		ext4_mark_inode_dirty(handle, inode_bl);
	पूर्ण

err_out1:
	ext4_journal_stop(handle);
	ext4_fc_stop_ineligible(sb);
	ext4_द्विगुन_up_ग_लिखो_data_sem(inode, inode_bl);

err_out:
	up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
journal_err_out:
	unlock_two_nondirectories(inode, inode_bl);
	iput(inode_bl);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_FS_ENCRYPTION
अटल पूर्णांक uuid_is_zero(__u8 u[16])
अणु
	पूर्णांक	i;

	क्रम (i = 0; i < 16; i++)
		अगर (u[i])
			वापस 0;
	वापस 1;
पूर्ण
#पूर्ण_अगर

/*
 * If immutable is set and we are not clearing it, we're not allowed to change
 * anything अन्यथा in the inode.  Don't error out if we're only trying to set
 * immutable on an immutable file.
 */
अटल पूर्णांक ext4_ioctl_check_immutable(काष्ठा inode *inode, __u32 new_projid,
				      अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	अचिन्हित पूर्णांक oldflags = ei->i_flags;

	अगर (!(oldflags & EXT4_IMMUTABLE_FL) || !(flags & EXT4_IMMUTABLE_FL))
		वापस 0;

	अगर ((oldflags & ~EXT4_IMMUTABLE_FL) != (flags & ~EXT4_IMMUTABLE_FL))
		वापस -EPERM;
	अगर (ext4_has_feature_project(inode->i_sb) &&
	    __kprojid_val(ei->i_projid) != new_projid)
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल व्योम ext4_dax_करोntcache(काष्ठा inode *inode, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	अगर (S_ISसूची(inode->i_mode))
		वापस;

	अगर (test_opt2(inode->i_sb, DAX_NEVER) ||
	    test_opt(inode->i_sb, DAX_ALWAYS))
		वापस;

	अगर ((ei->i_flags ^ flags) & EXT4_DAX_FL)
		d_mark_करोntcache(inode);
पूर्ण

अटल bool dax_compatible(काष्ठा inode *inode, अचिन्हित पूर्णांक oldflags,
			   अचिन्हित पूर्णांक flags)
अणु
	/* Allow the DAX flag to be changed on अंतरभूत directories */
	अगर (S_ISसूची(inode->i_mode)) अणु
		flags &= ~EXT4_INLINE_DATA_FL;
		oldflags &= ~EXT4_INLINE_DATA_FL;
	पूर्ण

	अगर (flags & EXT4_DAX_FL) अणु
		अगर ((oldflags & EXT4_DAX_MUT_EXCL) ||
		     ext4_test_inode_state(inode,
					  EXT4_STATE_VERITY_IN_PROGRESS)) अणु
			वापस false;
		पूर्ण
	पूर्ण

	अगर ((flags & EXT4_DAX_MUT_EXCL) && (oldflags & EXT4_DAX_FL))
			वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक ext4_ioctl_setflags(काष्ठा inode *inode,
			       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	handle_t *handle = शून्य;
	पूर्णांक err = -EPERM, migrate = 0;
	काष्ठा ext4_iloc iloc;
	अचिन्हित पूर्णांक oldflags, mask, i;
	काष्ठा super_block *sb = inode->i_sb;

	/* Is it quota file? Do not allow user to mess with it */
	अगर (ext4_is_quota_file(inode))
		जाओ flags_out;

	oldflags = ei->i_flags;
	/*
	 * The JOURNAL_DATA flag can only be changed by
	 * the relevant capability.
	 */
	अगर ((flags ^ oldflags) & (EXT4_JOURNAL_DATA_FL)) अणु
		अगर (!capable(CAP_SYS_RESOURCE))
			जाओ flags_out;
	पूर्ण

	अगर (!dax_compatible(inode, oldflags, flags)) अणु
		err = -EOPNOTSUPP;
		जाओ flags_out;
	पूर्ण

	अगर ((flags ^ oldflags) & EXT4_EXTENTS_FL)
		migrate = 1;

	अगर ((flags ^ oldflags) & EXT4_CASEFOLD_FL) अणु
		अगर (!ext4_has_feature_हालfold(sb)) अणु
			err = -EOPNOTSUPP;
			जाओ flags_out;
		पूर्ण

		अगर (!S_ISसूची(inode->i_mode)) अणु
			err = -ENOTसूची;
			जाओ flags_out;
		पूर्ण

		अगर (!ext4_empty_dir(inode)) अणु
			err = -ENOTEMPTY;
			जाओ flags_out;
		पूर्ण
	पूर्ण

	/*
	 * Wait क्रम all pending directio and then flush all the dirty pages
	 * क्रम this file.  The flush marks all the pages पढ़ोonly, so any
	 * subsequent attempt to ग_लिखो to the file (particularly mmap pages)
	 * will come through the fileप्रणाली and fail.
	 */
	अगर (S_ISREG(inode->i_mode) && !IS_IMMUTABLE(inode) &&
	    (flags & EXT4_IMMUTABLE_FL)) अणु
		inode_dio_रुको(inode);
		err = filemap_ग_लिखो_and_रुको(inode->i_mapping);
		अगर (err)
			जाओ flags_out;
	पूर्ण

	handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
	अगर (IS_ERR(handle)) अणु
		err = PTR_ERR(handle);
		जाओ flags_out;
	पूर्ण
	अगर (IS_SYNC(inode))
		ext4_handle_sync(handle);
	err = ext4_reserve_inode_ग_लिखो(handle, inode, &iloc);
	अगर (err)
		जाओ flags_err;

	ext4_dax_करोntcache(inode, flags);

	क्रम (i = 0, mask = 1; i < 32; i++, mask <<= 1) अणु
		अगर (!(mask & EXT4_FL_USER_MODIFIABLE))
			जारी;
		/* These flags get special treaपंचांगent later */
		अगर (mask == EXT4_JOURNAL_DATA_FL || mask == EXT4_EXTENTS_FL)
			जारी;
		अगर (mask & flags)
			ext4_set_inode_flag(inode, i);
		अन्यथा
			ext4_clear_inode_flag(inode, i);
	पूर्ण

	ext4_set_inode_flags(inode, false);

	inode->i_स_समय = current_समय(inode);

	err = ext4_mark_iloc_dirty(handle, inode, &iloc);
flags_err:
	ext4_journal_stop(handle);
	अगर (err)
		जाओ flags_out;

	अगर ((flags ^ oldflags) & (EXT4_JOURNAL_DATA_FL)) अणु
		/*
		 * Changes to the journaling mode can cause unsafe changes to
		 * S_DAX अगर the inode is DAX
		 */
		अगर (IS_DAX(inode)) अणु
			err = -EBUSY;
			जाओ flags_out;
		पूर्ण

		err = ext4_change_inode_journal_flag(inode,
						     flags & EXT4_JOURNAL_DATA_FL);
		अगर (err)
			जाओ flags_out;
	पूर्ण
	अगर (migrate) अणु
		अगर (flags & EXT4_EXTENTS_FL)
			err = ext4_ext_migrate(inode);
		अन्यथा
			err = ext4_ind_migrate(inode);
	पूर्ण

flags_out:
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक ext4_ioctl_setproject(काष्ठा inode *inode, __u32 projid)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	पूर्णांक err, rc;
	handle_t *handle;
	kprojid_t kprojid;
	काष्ठा ext4_iloc iloc;
	काष्ठा ext4_inode *raw_inode;
	काष्ठा dquot *transfer_to[MAXQUOTAS] = अणु पूर्ण;

	अगर (!ext4_has_feature_project(sb)) अणु
		अगर (projid != EXT4_DEF_PROJID)
			वापस -EOPNOTSUPP;
		अन्यथा
			वापस 0;
	पूर्ण

	अगर (EXT4_INODE_SIZE(sb) <= EXT4_GOOD_OLD_INODE_SIZE)
		वापस -EOPNOTSUPP;

	kprojid = make_kprojid(&init_user_ns, (projid_t)projid);

	अगर (projid_eq(kprojid, EXT4_I(inode)->i_projid))
		वापस 0;

	err = -EPERM;
	/* Is it quota file? Do not allow user to mess with it */
	अगर (ext4_is_quota_file(inode))
		वापस err;

	err = ext4_get_inode_loc(inode, &iloc);
	अगर (err)
		वापस err;

	raw_inode = ext4_raw_inode(&iloc);
	अगर (!EXT4_FITS_IN_INODE(raw_inode, ei, i_projid)) अणु
		err = ext4_expand_extra_isize(inode,
					      EXT4_SB(sb)->s_want_extra_isize,
					      &iloc);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		brअन्यथा(iloc.bh);
	पूर्ण

	err = dquot_initialize(inode);
	अगर (err)
		वापस err;

	handle = ext4_journal_start(inode, EXT4_HT_QUOTA,
		EXT4_QUOTA_INIT_BLOCKS(sb) +
		EXT4_QUOTA_DEL_BLOCKS(sb) + 3);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	err = ext4_reserve_inode_ग_लिखो(handle, inode, &iloc);
	अगर (err)
		जाओ out_stop;

	transfer_to[PRJQUOTA] = dqget(sb, make_kqid_projid(kprojid));
	अगर (!IS_ERR(transfer_to[PRJQUOTA])) अणु

		/* __dquot_transfer() calls back ext4_get_inode_usage() which
		 * counts xattr inode references.
		 */
		करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
		err = __dquot_transfer(inode, transfer_to);
		up_पढ़ो(&EXT4_I(inode)->xattr_sem);
		dqput(transfer_to[PRJQUOTA]);
		अगर (err)
			जाओ out_dirty;
	पूर्ण

	EXT4_I(inode)->i_projid = kprojid;
	inode->i_स_समय = current_समय(inode);
out_dirty:
	rc = ext4_mark_iloc_dirty(handle, inode, &iloc);
	अगर (!err)
		err = rc;
out_stop:
	ext4_journal_stop(handle);
	वापस err;
पूर्ण
#अन्यथा
अटल पूर्णांक ext4_ioctl_setproject(काष्ठा inode *inode, __u32 projid)
अणु
	अगर (projid != EXT4_DEF_PROJID)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ext4_shutकरोwn(काष्ठा super_block *sb, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	__u32 flags;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (get_user(flags, (__u32 __user *)arg))
		वापस -EFAULT;

	अगर (flags > EXT4_GOING_FLAGS_NOLOGFLUSH)
		वापस -EINVAL;

	अगर (ext4_क्रमced_shutकरोwn(sbi))
		वापस 0;

	ext4_msg(sb, KERN_ALERT, "shut down requested (%d)", flags);
	trace_ext4_shutकरोwn(sb, flags);

	चयन (flags) अणु
	हाल EXT4_GOING_FLAGS_DEFAULT:
		मुक्तze_bdev(sb->s_bdev);
		set_bit(EXT4_FLAGS_SHUTDOWN, &sbi->s_ext4_flags);
		thaw_bdev(sb->s_bdev);
		अवरोध;
	हाल EXT4_GOING_FLAGS_LOGFLUSH:
		set_bit(EXT4_FLAGS_SHUTDOWN, &sbi->s_ext4_flags);
		अगर (sbi->s_journal && !is_journal_पातed(sbi->s_journal)) अणु
			(व्योम) ext4_क्रमce_commit(sb);
			jbd2_journal_पात(sbi->s_journal, -ESHUTDOWN);
		पूर्ण
		अवरोध;
	हाल EXT4_GOING_FLAGS_NOLOGFLUSH:
		set_bit(EXT4_FLAGS_SHUTDOWN, &sbi->s_ext4_flags);
		अगर (sbi->s_journal && !is_journal_पातed(sbi->s_journal))
			jbd2_journal_पात(sbi->s_journal, -ESHUTDOWN);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	clear_opt(sb, DISCARD);
	वापस 0;
पूर्ण

काष्ठा getfsmap_info अणु
	काष्ठा super_block	*gi_sb;
	काष्ठा fsmap_head __user *gi_data;
	अचिन्हित पूर्णांक		gi_idx;
	__u32			gi_last_flags;
पूर्ण;

अटल पूर्णांक ext4_getfsmap_क्रमmat(काष्ठा ext4_fsmap *xfm, व्योम *priv)
अणु
	काष्ठा getfsmap_info *info = priv;
	काष्ठा fsmap fm;

	trace_ext4_getfsmap_mapping(info->gi_sb, xfm);

	info->gi_last_flags = xfm->fmr_flags;
	ext4_fsmap_from_पूर्णांकernal(info->gi_sb, &fm, xfm);
	अगर (copy_to_user(&info->gi_data->fmh_recs[info->gi_idx++], &fm,
			माप(काष्ठा fsmap)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ext4_ioc_getfsmap(काष्ठा super_block *sb,
			     काष्ठा fsmap_head __user *arg)
अणु
	काष्ठा getfsmap_info info = अणु शून्य पूर्ण;
	काष्ठा ext4_fsmap_head xhead = अणु0पूर्ण;
	काष्ठा fsmap_head head;
	bool पातed = false;
	पूर्णांक error;

	अगर (copy_from_user(&head, arg, माप(काष्ठा fsmap_head)))
		वापस -EFAULT;
	अगर (स_प्रथम_inv(head.fmh_reserved, 0, माप(head.fmh_reserved)) ||
	    स_प्रथम_inv(head.fmh_keys[0].fmr_reserved, 0,
		       माप(head.fmh_keys[0].fmr_reserved)) ||
	    स_प्रथम_inv(head.fmh_keys[1].fmr_reserved, 0,
		       माप(head.fmh_keys[1].fmr_reserved)))
		वापस -EINVAL;
	/*
	 * ext4 करोesn't report file extents at all, so the only valid
	 * file offsets are the magic ones (all zeroes or all ones).
	 */
	अगर (head.fmh_keys[0].fmr_offset ||
	    (head.fmh_keys[1].fmr_offset != 0 &&
	     head.fmh_keys[1].fmr_offset != -1ULL))
		वापस -EINVAL;

	xhead.fmh_अगरlags = head.fmh_अगरlags;
	xhead.fmh_count = head.fmh_count;
	ext4_fsmap_to_पूर्णांकernal(sb, &xhead.fmh_keys[0], &head.fmh_keys[0]);
	ext4_fsmap_to_पूर्णांकernal(sb, &xhead.fmh_keys[1], &head.fmh_keys[1]);

	trace_ext4_getfsmap_low_key(sb, &xhead.fmh_keys[0]);
	trace_ext4_getfsmap_high_key(sb, &xhead.fmh_keys[1]);

	info.gi_sb = sb;
	info.gi_data = arg;
	error = ext4_getfsmap(sb, &xhead, ext4_getfsmap_क्रमmat, &info);
	अगर (error == EXT4_QUERY_RANGE_ABORT) अणु
		error = 0;
		पातed = true;
	पूर्ण अन्यथा अगर (error)
		वापस error;

	/* If we didn't पात, set the "last" flag in the last fmx */
	अगर (!पातed && info.gi_idx) अणु
		info.gi_last_flags |= FMR_OF_LAST;
		अगर (copy_to_user(&info.gi_data->fmh_recs[info.gi_idx - 1].fmr_flags,
				 &info.gi_last_flags,
				 माप(info.gi_last_flags)))
			वापस -EFAULT;
	पूर्ण

	/* copy back header */
	head.fmh_entries = xhead.fmh_entries;
	head.fmh_oflags = xhead.fmh_oflags;
	अगर (copy_to_user(arg, &head, माप(काष्ठा fsmap_head)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ ext4_ioctl_group_add(काष्ठा file *file,
				 काष्ठा ext4_new_group_data *input)
अणु
	काष्ठा super_block *sb = file_inode(file)->i_sb;
	पूर्णांक err, err2=0;

	err = ext4_resize_begin(sb);
	अगर (err)
		वापस err;

	अगर (ext4_has_feature_bigalloc(sb)) अणु
		ext4_msg(sb, KERN_ERR,
			 "Online resizing not supported with bigalloc");
		err = -EOPNOTSUPP;
		जाओ group_add_out;
	पूर्ण

	err = mnt_want_ग_लिखो_file(file);
	अगर (err)
		जाओ group_add_out;

	err = ext4_group_add(sb, input);
	अगर (EXT4_SB(sb)->s_journal) अणु
		jbd2_journal_lock_updates(EXT4_SB(sb)->s_journal);
		err2 = jbd2_journal_flush(EXT4_SB(sb)->s_journal);
		jbd2_journal_unlock_updates(EXT4_SB(sb)->s_journal);
	पूर्ण
	अगर (err == 0)
		err = err2;
	mnt_drop_ग_लिखो_file(file);
	अगर (!err && ext4_has_group_desc_csum(sb) &&
	    test_opt(sb, INIT_INODE_TABLE))
		err = ext4_रेजिस्टर_li_request(sb, input->group);
group_add_out:
	ext4_resize_end(sb);
	वापस err;
पूर्ण

पूर्णांक ext4_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	u32 flags = ei->i_flags & EXT4_FL_USER_VISIBLE;

	अगर (S_ISREG(inode->i_mode))
		flags &= ~FS_PROJINHERIT_FL;

	fileattr_fill_flags(fa, flags);
	अगर (ext4_has_feature_project(inode->i_sb))
		fa->fsx_projid = from_kprojid(&init_user_ns, ei->i_projid);

	वापस 0;
पूर्ण

पूर्णांक ext4_fileattr_set(काष्ठा user_namespace *mnt_userns,
		      काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	u32 flags = fa->flags;
	पूर्णांक err = -EOPNOTSUPP;

	ext4_fc_start_update(inode);
	अगर (flags & ~EXT4_FL_USER_VISIBLE)
		जाओ out;

	/*
	 * chattr(1) grअसल flags via GETFLAGS, modअगरies the result and
	 * passes that to SETFLAGS. So we cannot easily make SETFLAGS
	 * more restrictive than just silently masking off visible but
	 * not settable flags as we always did.
	 */
	flags &= EXT4_FL_USER_MODIFIABLE;
	अगर (ext4_mask_flags(inode->i_mode, flags) != flags)
		जाओ out;
	err = ext4_ioctl_check_immutable(inode, fa->fsx_projid, flags);
	अगर (err)
		जाओ out;
	err = ext4_ioctl_setflags(inode, flags);
	अगर (err)
		जाओ out;
	err = ext4_ioctl_setproject(inode, fa->fsx_projid);
out:
	ext4_fc_stop_update(inode);
	वापस err;
पूर्ण

/* So that the fiemap access checks can't overflow on 32 bit machines. */
#घोषणा FIEMAP_MAX_EXTENTS	(अच_पूर्णांक_उच्च / माप(काष्ठा fiemap_extent))

अटल पूर्णांक ext4_ioctl_get_es_cache(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा fiemap fiemap;
	काष्ठा fiemap __user *ufiemap = (काष्ठा fiemap __user *) arg;
	काष्ठा fiemap_extent_info fieinfo = अणु 0, पूर्ण;
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक error;

	अगर (copy_from_user(&fiemap, ufiemap, माप(fiemap)))
		वापस -EFAULT;

	अगर (fiemap.fm_extent_count > FIEMAP_MAX_EXTENTS)
		वापस -EINVAL;

	fieinfo.fi_flags = fiemap.fm_flags;
	fieinfo.fi_extents_max = fiemap.fm_extent_count;
	fieinfo.fi_extents_start = ufiemap->fm_extents;

	error = ext4_get_es_cache(inode, &fieinfo, fiemap.fm_start,
			fiemap.fm_length);
	fiemap.fm_flags = fieinfo.fi_flags;
	fiemap.fm_mapped_extents = fieinfo.fi_extents_mapped;
	अगर (copy_to_user(ufiemap, &fiemap, माप(fiemap)))
		error = -EFAULT;

	वापस error;
पूर्ण

अटल दीर्घ __ext4_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा user_namespace *mnt_userns = file_mnt_user_ns(filp);

	ext4_debug("cmd = %u, arg = %lu\n", cmd, arg);

	चयन (cmd) अणु
	हाल FS_IOC_GETFSMAP:
		वापस ext4_ioc_getfsmap(sb, (व्योम __user *)arg);
	हाल EXT4_IOC_GETVERSION:
	हाल EXT4_IOC_GETVERSION_OLD:
		वापस put_user(inode->i_generation, (पूर्णांक __user *) arg);
	हाल EXT4_IOC_SETVERSION:
	हाल EXT4_IOC_SETVERSION_OLD: अणु
		handle_t *handle;
		काष्ठा ext4_iloc iloc;
		__u32 generation;
		पूर्णांक err;

		अगर (!inode_owner_or_capable(mnt_userns, inode))
			वापस -EPERM;

		अगर (ext4_has_metadata_csum(inode->i_sb)) अणु
			ext4_warning(sb, "Setting inode version is not "
				     "supported with metadata_csum enabled.");
			वापस -ENOTTY;
		पूर्ण

		err = mnt_want_ग_लिखो_file(filp);
		अगर (err)
			वापस err;
		अगर (get_user(generation, (पूर्णांक __user *) arg)) अणु
			err = -EFAULT;
			जाओ setversion_out;
		पूर्ण

		inode_lock(inode);
		handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
		अगर (IS_ERR(handle)) अणु
			err = PTR_ERR(handle);
			जाओ unlock_out;
		पूर्ण
		err = ext4_reserve_inode_ग_लिखो(handle, inode, &iloc);
		अगर (err == 0) अणु
			inode->i_स_समय = current_समय(inode);
			inode->i_generation = generation;
			err = ext4_mark_iloc_dirty(handle, inode, &iloc);
		पूर्ण
		ext4_journal_stop(handle);

unlock_out:
		inode_unlock(inode);
setversion_out:
		mnt_drop_ग_लिखो_file(filp);
		वापस err;
	पूर्ण
	हाल EXT4_IOC_GROUP_EXTEND: अणु
		ext4_fsblk_t n_blocks_count;
		पूर्णांक err, err2=0;

		err = ext4_resize_begin(sb);
		अगर (err)
			वापस err;

		अगर (get_user(n_blocks_count, (__u32 __user *)arg)) अणु
			err = -EFAULT;
			जाओ group_extend_out;
		पूर्ण

		अगर (ext4_has_feature_bigalloc(sb)) अणु
			ext4_msg(sb, KERN_ERR,
				 "Online resizing not supported with bigalloc");
			err = -EOPNOTSUPP;
			जाओ group_extend_out;
		पूर्ण

		err = mnt_want_ग_लिखो_file(filp);
		अगर (err)
			जाओ group_extend_out;

		err = ext4_group_extend(sb, EXT4_SB(sb)->s_es, n_blocks_count);
		अगर (EXT4_SB(sb)->s_journal) अणु
			jbd2_journal_lock_updates(EXT4_SB(sb)->s_journal);
			err2 = jbd2_journal_flush(EXT4_SB(sb)->s_journal);
			jbd2_journal_unlock_updates(EXT4_SB(sb)->s_journal);
		पूर्ण
		अगर (err == 0)
			err = err2;
		mnt_drop_ग_लिखो_file(filp);
group_extend_out:
		ext4_resize_end(sb);
		वापस err;
	पूर्ण

	हाल EXT4_IOC_MOVE_EXT: अणु
		काष्ठा move_extent me;
		काष्ठा fd करोnor;
		पूर्णांक err;

		अगर (!(filp->f_mode & FMODE_READ) ||
		    !(filp->f_mode & FMODE_WRITE))
			वापस -EBADF;

		अगर (copy_from_user(&me,
			(काष्ठा move_extent __user *)arg, माप(me)))
			वापस -EFAULT;
		me.moved_len = 0;

		करोnor = fdget(me.करोnor_fd);
		अगर (!करोnor.file)
			वापस -EBADF;

		अगर (!(करोnor.file->f_mode & FMODE_WRITE)) अणु
			err = -EBADF;
			जाओ mext_out;
		पूर्ण

		अगर (ext4_has_feature_bigalloc(sb)) अणु
			ext4_msg(sb, KERN_ERR,
				 "Online defrag not supported with bigalloc");
			err = -EOPNOTSUPP;
			जाओ mext_out;
		पूर्ण अन्यथा अगर (IS_DAX(inode)) अणु
			ext4_msg(sb, KERN_ERR,
				 "Online defrag not supported with DAX");
			err = -EOPNOTSUPP;
			जाओ mext_out;
		पूर्ण

		err = mnt_want_ग_लिखो_file(filp);
		अगर (err)
			जाओ mext_out;

		err = ext4_move_extents(filp, करोnor.file, me.orig_start,
					me.करोnor_start, me.len, &me.moved_len);
		mnt_drop_ग_लिखो_file(filp);

		अगर (copy_to_user((काष्ठा move_extent __user *)arg,
				 &me, माप(me)))
			err = -EFAULT;
mext_out:
		fdput(करोnor);
		वापस err;
	पूर्ण

	हाल EXT4_IOC_GROUP_ADD: अणु
		काष्ठा ext4_new_group_data input;

		अगर (copy_from_user(&input, (काष्ठा ext4_new_group_input __user *)arg,
				माप(input)))
			वापस -EFAULT;

		वापस ext4_ioctl_group_add(filp, &input);
	पूर्ण

	हाल EXT4_IOC_MIGRATE:
	अणु
		पूर्णांक err;
		अगर (!inode_owner_or_capable(mnt_userns, inode))
			वापस -EACCES;

		err = mnt_want_ग_लिखो_file(filp);
		अगर (err)
			वापस err;
		/*
		 * inode_mutex prevent ग_लिखो and truncate on the file.
		 * Read still goes through. We take i_data_sem in
		 * ext4_ext_swap_inode_data beक्रमe we चयन the
		 * inode क्रमmat to prevent पढ़ो.
		 */
		inode_lock((inode));
		err = ext4_ext_migrate(inode);
		inode_unlock((inode));
		mnt_drop_ग_लिखो_file(filp);
		वापस err;
	पूर्ण

	हाल EXT4_IOC_ALLOC_DA_BLKS:
	अणु
		पूर्णांक err;
		अगर (!inode_owner_or_capable(mnt_userns, inode))
			वापस -EACCES;

		err = mnt_want_ग_लिखो_file(filp);
		अगर (err)
			वापस err;
		err = ext4_alloc_da_blocks(inode);
		mnt_drop_ग_लिखो_file(filp);
		वापस err;
	पूर्ण

	हाल EXT4_IOC_SWAP_BOOT:
	अणु
		पूर्णांक err;
		अगर (!(filp->f_mode & FMODE_WRITE))
			वापस -EBADF;
		err = mnt_want_ग_लिखो_file(filp);
		अगर (err)
			वापस err;
		err = swap_inode_boot_loader(sb, mnt_userns, inode);
		mnt_drop_ग_लिखो_file(filp);
		वापस err;
	पूर्ण

	हाल EXT4_IOC_RESIZE_FS: अणु
		ext4_fsblk_t n_blocks_count;
		पूर्णांक err = 0, err2 = 0;
		ext4_group_t o_group = EXT4_SB(sb)->s_groups_count;

		अगर (copy_from_user(&n_blocks_count, (__u64 __user *)arg,
				   माप(__u64))) अणु
			वापस -EFAULT;
		पूर्ण

		err = ext4_resize_begin(sb);
		अगर (err)
			वापस err;

		err = mnt_want_ग_लिखो_file(filp);
		अगर (err)
			जाओ resizefs_out;

		err = ext4_resize_fs(sb, n_blocks_count);
		अगर (EXT4_SB(sb)->s_journal) अणु
			ext4_fc_mark_ineligible(sb, EXT4_FC_REASON_RESIZE);
			jbd2_journal_lock_updates(EXT4_SB(sb)->s_journal);
			err2 = jbd2_journal_flush(EXT4_SB(sb)->s_journal);
			jbd2_journal_unlock_updates(EXT4_SB(sb)->s_journal);
		पूर्ण
		अगर (err == 0)
			err = err2;
		mnt_drop_ग_लिखो_file(filp);
		अगर (!err && (o_group < EXT4_SB(sb)->s_groups_count) &&
		    ext4_has_group_desc_csum(sb) &&
		    test_opt(sb, INIT_INODE_TABLE))
			err = ext4_रेजिस्टर_li_request(sb, o_group);

resizefs_out:
		ext4_resize_end(sb);
		वापस err;
	पूर्ण

	हाल FITRIM:
	अणु
		काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);
		काष्ठा fstrim_range range;
		पूर्णांक ret = 0;

		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;

		अगर (!blk_queue_discard(q))
			वापस -EOPNOTSUPP;

		/*
		 * We haven't replayed the journal, so we cannot use our
		 * block-biपंचांगap-guided storage zapping commands.
		 */
		अगर (test_opt(sb, NOLOAD) && ext4_has_feature_journal(sb))
			वापस -EROFS;

		अगर (copy_from_user(&range, (काष्ठा fstrim_range __user *)arg,
		    माप(range)))
			वापस -EFAULT;

		range.minlen = max((अचिन्हित पूर्णांक)range.minlen,
				   q->limits.discard_granularity);
		ret = ext4_trim_fs(sb, &range);
		अगर (ret < 0)
			वापस ret;

		अगर (copy_to_user((काष्ठा fstrim_range __user *)arg, &range,
		    माप(range)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल EXT4_IOC_PRECACHE_EXTENTS:
		वापस ext4_ext_precache(inode);

	हाल FS_IOC_SET_ENCRYPTION_POLICY:
		अगर (!ext4_has_feature_encrypt(sb))
			वापस -EOPNOTSUPP;
		वापस fscrypt_ioctl_set_policy(filp, (स्थिर व्योम __user *)arg);

	हाल FS_IOC_GET_ENCRYPTION_PWSALT: अणु
#अगर_घोषित CONFIG_FS_ENCRYPTION
		पूर्णांक err, err2;
		काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
		handle_t *handle;

		अगर (!ext4_has_feature_encrypt(sb))
			वापस -EOPNOTSUPP;
		अगर (uuid_is_zero(sbi->s_es->s_encrypt_pw_salt)) अणु
			err = mnt_want_ग_लिखो_file(filp);
			अगर (err)
				वापस err;
			handle = ext4_journal_start_sb(sb, EXT4_HT_MISC, 1);
			अगर (IS_ERR(handle)) अणु
				err = PTR_ERR(handle);
				जाओ pwsalt_err_निकास;
			पूर्ण
			err = ext4_journal_get_ग_लिखो_access(handle, sbi->s_sbh);
			अगर (err)
				जाओ pwsalt_err_journal;
			lock_buffer(sbi->s_sbh);
			generate_अक्रमom_uuid(sbi->s_es->s_encrypt_pw_salt);
			ext4_superblock_csum_set(sb);
			unlock_buffer(sbi->s_sbh);
			err = ext4_handle_dirty_metadata(handle, शून्य,
							 sbi->s_sbh);
		pwsalt_err_journal:
			err2 = ext4_journal_stop(handle);
			अगर (err2 && !err)
				err = err2;
		pwsalt_err_निकास:
			mnt_drop_ग_लिखो_file(filp);
			अगर (err)
				वापस err;
		पूर्ण
		अगर (copy_to_user((व्योम __user *) arg,
				 sbi->s_es->s_encrypt_pw_salt, 16))
			वापस -EFAULT;
		वापस 0;
#अन्यथा
		वापस -EOPNOTSUPP;
#पूर्ण_अगर
	पूर्ण
	हाल FS_IOC_GET_ENCRYPTION_POLICY:
		अगर (!ext4_has_feature_encrypt(sb))
			वापस -EOPNOTSUPP;
		वापस fscrypt_ioctl_get_policy(filp, (व्योम __user *)arg);

	हाल FS_IOC_GET_ENCRYPTION_POLICY_EX:
		अगर (!ext4_has_feature_encrypt(sb))
			वापस -EOPNOTSUPP;
		वापस fscrypt_ioctl_get_policy_ex(filp, (व्योम __user *)arg);

	हाल FS_IOC_ADD_ENCRYPTION_KEY:
		अगर (!ext4_has_feature_encrypt(sb))
			वापस -EOPNOTSUPP;
		वापस fscrypt_ioctl_add_key(filp, (व्योम __user *)arg);

	हाल FS_IOC_REMOVE_ENCRYPTION_KEY:
		अगर (!ext4_has_feature_encrypt(sb))
			वापस -EOPNOTSUPP;
		वापस fscrypt_ioctl_हटाओ_key(filp, (व्योम __user *)arg);

	हाल FS_IOC_REMOVE_ENCRYPTION_KEY_ALL_USERS:
		अगर (!ext4_has_feature_encrypt(sb))
			वापस -EOPNOTSUPP;
		वापस fscrypt_ioctl_हटाओ_key_all_users(filp,
							  (व्योम __user *)arg);
	हाल FS_IOC_GET_ENCRYPTION_KEY_STATUS:
		अगर (!ext4_has_feature_encrypt(sb))
			वापस -EOPNOTSUPP;
		वापस fscrypt_ioctl_get_key_status(filp, (व्योम __user *)arg);

	हाल FS_IOC_GET_ENCRYPTION_NONCE:
		अगर (!ext4_has_feature_encrypt(sb))
			वापस -EOPNOTSUPP;
		वापस fscrypt_ioctl_get_nonce(filp, (व्योम __user *)arg);

	हाल EXT4_IOC_CLEAR_ES_CACHE:
	अणु
		अगर (!inode_owner_or_capable(mnt_userns, inode))
			वापस -EACCES;
		ext4_clear_inode_es(inode);
		वापस 0;
	पूर्ण

	हाल EXT4_IOC_GETSTATE:
	अणु
		__u32	state = 0;

		अगर (ext4_test_inode_state(inode, EXT4_STATE_EXT_PRECACHED))
			state |= EXT4_STATE_FLAG_EXT_PRECACHED;
		अगर (ext4_test_inode_state(inode, EXT4_STATE_NEW))
			state |= EXT4_STATE_FLAG_NEW;
		अगर (ext4_test_inode_state(inode, EXT4_STATE_NEWENTRY))
			state |= EXT4_STATE_FLAG_NEWENTRY;
		अगर (ext4_test_inode_state(inode, EXT4_STATE_DA_ALLOC_CLOSE))
			state |= EXT4_STATE_FLAG_DA_ALLOC_CLOSE;

		वापस put_user(state, (__u32 __user *) arg);
	पूर्ण

	हाल EXT4_IOC_GET_ES_CACHE:
		वापस ext4_ioctl_get_es_cache(filp, arg);

	हाल EXT4_IOC_SHUTDOWN:
		वापस ext4_shutकरोwn(sb, arg);

	हाल FS_IOC_ENABLE_VERITY:
		अगर (!ext4_has_feature_verity(sb))
			वापस -EOPNOTSUPP;
		वापस fsverity_ioctl_enable(filp, (स्थिर व्योम __user *)arg);

	हाल FS_IOC_MEASURE_VERITY:
		अगर (!ext4_has_feature_verity(sb))
			वापस -EOPNOTSUPP;
		वापस fsverity_ioctl_measure(filp, (व्योम __user *)arg);

	हाल FS_IOC_READ_VERITY_METADATA:
		अगर (!ext4_has_feature_verity(sb))
			वापस -EOPNOTSUPP;
		वापस fsverity_ioctl_पढ़ो_metadata(filp,
						    (स्थिर व्योम __user *)arg);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

दीर्घ ext4_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	ext4_fc_start_update(file_inode(filp));
	ret = __ext4_ioctl(filp, cmd, arg);
	ext4_fc_stop_update(file_inode(filp));

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
दीर्घ ext4_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	/* These are just misnamed, they actually get/put from/to user an पूर्णांक */
	चयन (cmd) अणु
	हाल EXT4_IOC32_GETVERSION:
		cmd = EXT4_IOC_GETVERSION;
		अवरोध;
	हाल EXT4_IOC32_SETVERSION:
		cmd = EXT4_IOC_SETVERSION;
		अवरोध;
	हाल EXT4_IOC32_GROUP_EXTEND:
		cmd = EXT4_IOC_GROUP_EXTEND;
		अवरोध;
	हाल EXT4_IOC32_GETVERSION_OLD:
		cmd = EXT4_IOC_GETVERSION_OLD;
		अवरोध;
	हाल EXT4_IOC32_SETVERSION_OLD:
		cmd = EXT4_IOC_SETVERSION_OLD;
		अवरोध;
	हाल EXT4_IOC32_GETRSVSZ:
		cmd = EXT4_IOC_GETRSVSZ;
		अवरोध;
	हाल EXT4_IOC32_SETRSVSZ:
		cmd = EXT4_IOC_SETRSVSZ;
		अवरोध;
	हाल EXT4_IOC32_GROUP_ADD: अणु
		काष्ठा compat_ext4_new_group_input __user *uinput;
		काष्ठा ext4_new_group_data input;
		पूर्णांक err;

		uinput = compat_ptr(arg);
		err = get_user(input.group, &uinput->group);
		err |= get_user(input.block_biपंचांगap, &uinput->block_biपंचांगap);
		err |= get_user(input.inode_biपंचांगap, &uinput->inode_biपंचांगap);
		err |= get_user(input.inode_table, &uinput->inode_table);
		err |= get_user(input.blocks_count, &uinput->blocks_count);
		err |= get_user(input.reserved_blocks,
				&uinput->reserved_blocks);
		अगर (err)
			वापस -EFAULT;
		वापस ext4_ioctl_group_add(file, &input);
	पूर्ण
	हाल EXT4_IOC_MOVE_EXT:
	हाल EXT4_IOC_RESIZE_FS:
	हाल FITRIM:
	हाल EXT4_IOC_PRECACHE_EXTENTS:
	हाल FS_IOC_SET_ENCRYPTION_POLICY:
	हाल FS_IOC_GET_ENCRYPTION_PWSALT:
	हाल FS_IOC_GET_ENCRYPTION_POLICY:
	हाल FS_IOC_GET_ENCRYPTION_POLICY_EX:
	हाल FS_IOC_ADD_ENCRYPTION_KEY:
	हाल FS_IOC_REMOVE_ENCRYPTION_KEY:
	हाल FS_IOC_REMOVE_ENCRYPTION_KEY_ALL_USERS:
	हाल FS_IOC_GET_ENCRYPTION_KEY_STATUS:
	हाल FS_IOC_GET_ENCRYPTION_NONCE:
	हाल EXT4_IOC_SHUTDOWN:
	हाल FS_IOC_GETFSMAP:
	हाल FS_IOC_ENABLE_VERITY:
	हाल FS_IOC_MEASURE_VERITY:
	हाल FS_IOC_READ_VERITY_METADATA:
	हाल EXT4_IOC_CLEAR_ES_CACHE:
	हाल EXT4_IOC_GETSTATE:
	हाल EXT4_IOC_GET_ES_CACHE:
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस ext4_ioctl(file, cmd, (अचिन्हित दीर्घ) compat_ptr(arg));
पूर्ण
#पूर्ण_अगर
