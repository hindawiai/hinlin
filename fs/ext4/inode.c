<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/inode.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/inode.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  64-bit file support on 64-bit platक्रमms by Jakub Jelinek
 *	(jj@sunsite.ms.mff.cuni.cz)
 *
 *  Assorted race fixes, reग_लिखो of ext4_get_block() by Al Viro, 2000
 */

#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/समय.स>
#समावेश <linux/highuid.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/dax.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/माला.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/mpage.h>
#समावेश <linux/namei.h>
#समावेश <linux/uपन.स>
#समावेश <linux/bपन.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/iomap.h>
#समावेश <linux/iversion.h>

#समावेश "ext4_jbd2.h"
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश "truncate.h"

#समावेश <trace/events/ext4.h>

अटल __u32 ext4_inode_csum(काष्ठा inode *inode, काष्ठा ext4_inode *raw,
			      काष्ठा ext4_inode_info *ei)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	__u32 csum;
	__u16 dummy_csum = 0;
	पूर्णांक offset = दुरत्व(काष्ठा ext4_inode, i_checksum_lo);
	अचिन्हित पूर्णांक csum_size = माप(dummy_csum);

	csum = ext4_chksum(sbi, ei->i_csum_seed, (__u8 *)raw, offset);
	csum = ext4_chksum(sbi, csum, (__u8 *)&dummy_csum, csum_size);
	offset += csum_size;
	csum = ext4_chksum(sbi, csum, (__u8 *)raw + offset,
			   EXT4_GOOD_OLD_INODE_SIZE - offset);

	अगर (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE) अणु
		offset = दुरत्व(काष्ठा ext4_inode, i_checksum_hi);
		csum = ext4_chksum(sbi, csum, (__u8 *)raw +
				   EXT4_GOOD_OLD_INODE_SIZE,
				   offset - EXT4_GOOD_OLD_INODE_SIZE);
		अगर (EXT4_FITS_IN_INODE(raw, ei, i_checksum_hi)) अणु
			csum = ext4_chksum(sbi, csum, (__u8 *)&dummy_csum,
					   csum_size);
			offset += csum_size;
		पूर्ण
		csum = ext4_chksum(sbi, csum, (__u8 *)raw + offset,
				   EXT4_INODE_SIZE(inode->i_sb) - offset);
	पूर्ण

	वापस csum;
पूर्ण

अटल पूर्णांक ext4_inode_csum_verअगरy(काष्ठा inode *inode, काष्ठा ext4_inode *raw,
				  काष्ठा ext4_inode_info *ei)
अणु
	__u32 provided, calculated;

	अगर (EXT4_SB(inode->i_sb)->s_es->s_creator_os !=
	    cpu_to_le32(EXT4_OS_LINUX) ||
	    !ext4_has_metadata_csum(inode->i_sb))
		वापस 1;

	provided = le16_to_cpu(raw->i_checksum_lo);
	calculated = ext4_inode_csum(inode, raw, ei);
	अगर (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE &&
	    EXT4_FITS_IN_INODE(raw, ei, i_checksum_hi))
		provided |= ((__u32)le16_to_cpu(raw->i_checksum_hi)) << 16;
	अन्यथा
		calculated &= 0xFFFF;

	वापस provided == calculated;
पूर्ण

व्योम ext4_inode_csum_set(काष्ठा inode *inode, काष्ठा ext4_inode *raw,
			 काष्ठा ext4_inode_info *ei)
अणु
	__u32 csum;

	अगर (EXT4_SB(inode->i_sb)->s_es->s_creator_os !=
	    cpu_to_le32(EXT4_OS_LINUX) ||
	    !ext4_has_metadata_csum(inode->i_sb))
		वापस;

	csum = ext4_inode_csum(inode, raw, ei);
	raw->i_checksum_lo = cpu_to_le16(csum & 0xFFFF);
	अगर (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE &&
	    EXT4_FITS_IN_INODE(raw, ei, i_checksum_hi))
		raw->i_checksum_hi = cpu_to_le16(csum >> 16);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_begin_ordered_truncate(काष्ठा inode *inode,
					      loff_t new_size)
अणु
	trace_ext4_begin_ordered_truncate(inode, new_size);
	/*
	 * If jinode is zero, then we never खोलोed the file क्रम
	 * writing, so there's no need to call
	 * jbd2_journal_begin_ordered_truncate() since there's no
	 * outstanding ग_लिखोs we need to flush.
	 */
	अगर (!EXT4_I(inode)->jinode)
		वापस 0;
	वापस jbd2_journal_begin_ordered_truncate(EXT4_JOURNAL(inode),
						   EXT4_I(inode)->jinode,
						   new_size);
पूर्ण

अटल व्योम ext4_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				अचिन्हित पूर्णांक length);
अटल पूर्णांक __ext4_journalled_ग_लिखोpage(काष्ठा page *page, अचिन्हित पूर्णांक len);
अटल पूर्णांक ext4_bh_delay_or_unwritten(handle_t *handle, काष्ठा buffer_head *bh);
अटल पूर्णांक ext4_meta_trans_blocks(काष्ठा inode *inode, पूर्णांक lblocks,
				  पूर्णांक pextents);

/*
 * Test whether an inode is a fast symlink.
 * A fast symlink has its symlink data stored in ext4_inode_info->i_data.
 */
पूर्णांक ext4_inode_is_fast_symlink(काष्ठा inode *inode)
अणु
	अगर (!(EXT4_I(inode)->i_flags & EXT4_EA_INODE_FL)) अणु
		पूर्णांक ea_blocks = EXT4_I(inode)->i_file_acl ?
				EXT4_CLUSTER_SIZE(inode->i_sb) >> 9 : 0;

		अगर (ext4_has_अंतरभूत_data(inode))
			वापस 0;

		वापस (S_ISLNK(inode->i_mode) && inode->i_blocks - ea_blocks == 0);
	पूर्ण
	वापस S_ISLNK(inode->i_mode) && inode->i_size &&
	       (inode->i_size < EXT4_N_BLOCKS * 4);
पूर्ण

/*
 * Called at the last iput() अगर i_nlink is zero.
 */
व्योम ext4_evict_inode(काष्ठा inode *inode)
अणु
	handle_t *handle;
	पूर्णांक err;
	/*
	 * Credits क्रम final inode cleanup and मुक्तing:
	 * sb + inode (ext4_orphan_del()), block biपंचांगap, group descriptor
	 * (xattr block मुक्तing), biपंचांगap, group descriptor (inode मुक्तing)
	 */
	पूर्णांक extra_credits = 6;
	काष्ठा ext4_xattr_inode_array *ea_inode_array = शून्य;
	bool मुक्तze_रक्षित = false;

	trace_ext4_evict_inode(inode);

	अगर (inode->i_nlink) अणु
		/*
		 * When journalling data dirty buffers are tracked only in the
		 * journal. So although mm thinks everything is clean and
		 * पढ़ोy क्रम reaping the inode might still have some pages to
		 * ग_लिखो in the running transaction or रुकोing to be
		 * checkpoपूर्णांकed. Thus calling jbd2_journal_invalidatepage()
		 * (via truncate_inode_pages()) to discard these buffers can
		 * cause data loss. Also even अगर we did not discard these
		 * buffers, we would have no way to find them after the inode
		 * is reaped and thus user could see stale data अगर he tries to
		 * पढ़ो them beक्रमe the transaction is checkpoपूर्णांकed. So be
		 * careful and क्रमce everything to disk here... We use
		 * ei->i_datasync_tid to store the newest transaction
		 * containing inode's data.
		 *
		 * Note that directories करो not have this problem because they
		 * करोn't use page cache.
		 */
		अगर (inode->i_ino != EXT4_JOURNAL_INO &&
		    ext4_should_journal_data(inode) &&
		    (S_ISLNK(inode->i_mode) || S_ISREG(inode->i_mode)) &&
		    inode->i_data.nrpages) अणु
			journal_t *journal = EXT4_SB(inode->i_sb)->s_journal;
			tid_t commit_tid = EXT4_I(inode)->i_datasync_tid;

			jbd2_complete_transaction(journal, commit_tid);
			filemap_ग_लिखो_and_रुको(&inode->i_data);
		पूर्ण
		truncate_inode_pages_final(&inode->i_data);

		जाओ no_delete;
	पूर्ण

	अगर (is_bad_inode(inode))
		जाओ no_delete;
	dquot_initialize(inode);

	अगर (ext4_should_order_data(inode))
		ext4_begin_ordered_truncate(inode, 0);
	truncate_inode_pages_final(&inode->i_data);

	/*
	 * For inodes with journalled data, transaction commit could have
	 * dirtied the inode. Flush worker is ignoring it because of I_FREEING
	 * flag but we still need to हटाओ the inode from the ग_लिखोback lists.
	 */
	अगर (!list_empty_careful(&inode->i_io_list)) अणु
		WARN_ON_ONCE(!ext4_should_journal_data(inode));
		inode_io_list_del(inode);
	पूर्ण

	/*
	 * Protect us against मुक्तzing - iput() caller didn't have to have any
	 * protection against it. When we are in a running transaction though,
	 * we are alपढ़ोy रक्षित against मुक्तzing and we cannot grab further
	 * protection due to lock ordering स्थिरraपूर्णांकs.
	 */
	अगर (!ext4_journal_current_handle()) अणु
		sb_start_पूर्णांकग_लिखो(inode->i_sb);
		मुक्तze_रक्षित = true;
	पूर्ण

	अगर (!IS_NOQUOTA(inode))
		extra_credits += EXT4_MAXQUOTAS_DEL_BLOCKS(inode->i_sb);

	/*
	 * Block biपंचांगap, group descriptor, and inode are accounted in both
	 * ext4_blocks_क्रम_truncate() and extra_credits. So subtract 3.
	 */
	handle = ext4_journal_start(inode, EXT4_HT_TRUNCATE,
			 ext4_blocks_क्रम_truncate(inode) + extra_credits - 3);
	अगर (IS_ERR(handle)) अणु
		ext4_std_error(inode->i_sb, PTR_ERR(handle));
		/*
		 * If we're going to skip the normal cleanup, we still need to
		 * make sure that the in-core orphan linked list is properly
		 * cleaned up.
		 */
		ext4_orphan_del(शून्य, inode);
		अगर (मुक्तze_रक्षित)
			sb_end_पूर्णांकग_लिखो(inode->i_sb);
		जाओ no_delete;
	पूर्ण

	अगर (IS_SYNC(inode))
		ext4_handle_sync(handle);

	/*
	 * Set inode->i_size to 0 beक्रमe calling ext4_truncate(). We need
	 * special handling of symlinks here because i_size is used to
	 * determine whether ext4_inode_info->i_data contains symlink data or
	 * block mappings. Setting i_size to 0 will हटाओ its fast symlink
	 * status. Erase i_data so that it becomes a valid empty block map.
	 */
	अगर (ext4_inode_is_fast_symlink(inode))
		स_रखो(EXT4_I(inode)->i_data, 0, माप(EXT4_I(inode)->i_data));
	inode->i_size = 0;
	err = ext4_mark_inode_dirty(handle, inode);
	अगर (err) अणु
		ext4_warning(inode->i_sb,
			     "couldn't mark inode dirty (err %d)", err);
		जाओ stop_handle;
	पूर्ण
	अगर (inode->i_blocks) अणु
		err = ext4_truncate(inode);
		अगर (err) अणु
			ext4_error_err(inode->i_sb, -err,
				       "couldn't truncate inode %lu (err %d)",
				       inode->i_ino, err);
			जाओ stop_handle;
		पूर्ण
	पूर्ण

	/* Remove xattr references. */
	err = ext4_xattr_delete_inode(handle, inode, &ea_inode_array,
				      extra_credits);
	अगर (err) अणु
		ext4_warning(inode->i_sb, "xattr delete (err %d)", err);
stop_handle:
		ext4_journal_stop(handle);
		ext4_orphan_del(शून्य, inode);
		अगर (मुक्तze_रक्षित)
			sb_end_पूर्णांकग_लिखो(inode->i_sb);
		ext4_xattr_inode_array_मुक्त(ea_inode_array);
		जाओ no_delete;
	पूर्ण

	/*
	 * Kill off the orphan record which ext4_truncate created.
	 * AKPM: I think this can be inside the above `अगर'.
	 * Note that ext4_orphan_del() has to be able to cope with the
	 * deletion of a non-existent orphan - this is because we करोn't
	 * know अगर ext4_truncate() actually created an orphan record.
	 * (Well, we could करो this अगर we need to, but heck - it works)
	 */
	ext4_orphan_del(handle, inode);
	EXT4_I(inode)->i_dसमय	= (__u32)kसमय_get_real_seconds();

	/*
	 * One subtle ordering requirement: अगर anything has gone wrong
	 * (transaction पात, IO errors, whatever), then we can still
	 * करो these next steps (the fs will alपढ़ोy have been marked as
	 * having errors), but we can't मुक्त the inode अगर the mark_dirty
	 * fails.
	 */
	अगर (ext4_mark_inode_dirty(handle, inode))
		/* If that failed, just करो the required in-core inode clear. */
		ext4_clear_inode(inode);
	अन्यथा
		ext4_मुक्त_inode(handle, inode);
	ext4_journal_stop(handle);
	अगर (मुक्तze_रक्षित)
		sb_end_पूर्णांकग_लिखो(inode->i_sb);
	ext4_xattr_inode_array_मुक्त(ea_inode_array);
	वापस;
no_delete:
	अगर (!list_empty(&EXT4_I(inode)->i_fc_list))
		ext4_fc_mark_ineligible(inode->i_sb, EXT4_FC_REASON_NOMEM);
	ext4_clear_inode(inode);	/* We must guarantee clearing of inode... */
पूर्ण

#अगर_घोषित CONFIG_QUOTA
qमाप_प्रकार *ext4_get_reserved_space(काष्ठा inode *inode)
अणु
	वापस &EXT4_I(inode)->i_reserved_quota;
पूर्ण
#पूर्ण_अगर

/*
 * Called with i_data_sem करोwn, which is important since we can call
 * ext4_discard_pपुनः_स्मृतिations() from here.
 */
व्योम ext4_da_update_reserve_space(काष्ठा inode *inode,
					पूर्णांक used, पूर्णांक quota_claim)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	spin_lock(&ei->i_block_reservation_lock);
	trace_ext4_da_update_reserve_space(inode, used, quota_claim);
	अगर (unlikely(used > ei->i_reserved_data_blocks)) अणु
		ext4_warning(inode->i_sb, "%s: ino %lu, used %d "
			 "with only %d reserved data blocks",
			 __func__, inode->i_ino, used,
			 ei->i_reserved_data_blocks);
		WARN_ON(1);
		used = ei->i_reserved_data_blocks;
	पूर्ण

	/* Update per-inode reservations */
	ei->i_reserved_data_blocks -= used;
	percpu_counter_sub(&sbi->s_dirtyclusters_counter, used);

	spin_unlock(&EXT4_I(inode)->i_block_reservation_lock);

	/* Update quota subप्रणाली क्रम data blocks */
	अगर (quota_claim)
		dquot_claim_block(inode, EXT4_C2B(sbi, used));
	अन्यथा अणु
		/*
		 * We did fallocate with an offset that is alपढ़ोy delayed
		 * allocated. So on delayed allocated ग_लिखोback we should
		 * not re-claim the quota क्रम fallocated blocks.
		 */
		dquot_release_reservation_block(inode, EXT4_C2B(sbi, used));
	पूर्ण

	/*
	 * If we have करोne all the pending block allocations and अगर
	 * there aren't any ग_लिखोrs on the inode, we can discard the
	 * inode's pपुनः_स्मृतिations.
	 */
	अगर ((ei->i_reserved_data_blocks == 0) &&
	    !inode_is_खोलो_क्रम_ग_लिखो(inode))
		ext4_discard_pपुनः_स्मृतिations(inode, 0);
पूर्ण

अटल पूर्णांक __check_block_validity(काष्ठा inode *inode, स्थिर अक्षर *func,
				अचिन्हित पूर्णांक line,
				काष्ठा ext4_map_blocks *map)
अणु
	अगर (ext4_has_feature_journal(inode->i_sb) &&
	    (inode->i_ino ==
	     le32_to_cpu(EXT4_SB(inode->i_sb)->s_es->s_journal_inum)))
		वापस 0;
	अगर (!ext4_inode_block_valid(inode, map->m_pblk, map->m_len)) अणु
		ext4_error_inode(inode, func, line, map->m_pblk,
				 "lblock %lu mapped to illegal pblock %llu "
				 "(length %d)", (अचिन्हित दीर्घ) map->m_lblk,
				 map->m_pblk, map->m_len);
		वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ext4_issue_zeroout(काष्ठा inode *inode, ext4_lblk_t lblk, ext4_fsblk_t pblk,
		       ext4_lblk_t len)
अणु
	पूर्णांक ret;

	अगर (IS_ENCRYPTED(inode) && S_ISREG(inode->i_mode))
		वापस fscrypt_zeroout_range(inode, lblk, pblk, len);

	ret = sb_issue_zeroout(inode->i_sb, pblk, len, GFP_NOFS);
	अगर (ret > 0)
		ret = 0;

	वापस ret;
पूर्ण

#घोषणा check_block_validity(inode, map)	\
	__check_block_validity((inode), __func__, __LINE__, (map))

#अगर_घोषित ES_AGGRESSIVE_TEST
अटल व्योम ext4_map_blocks_es_recheck(handle_t *handle,
				       काष्ठा inode *inode,
				       काष्ठा ext4_map_blocks *es_map,
				       काष्ठा ext4_map_blocks *map,
				       पूर्णांक flags)
अणु
	पूर्णांक retval;

	map->m_flags = 0;
	/*
	 * There is a race winकरोw that the result is not the same.
	 * e.g. xfstests #223 when dioपढ़ो_nolock enables.  The reason
	 * is that we lookup a block mapping in extent status tree with
	 * out taking i_data_sem.  So at the समय the unwritten extent
	 * could be converted.
	 */
	करोwn_पढ़ो(&EXT4_I(inode)->i_data_sem);
	अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) अणु
		retval = ext4_ext_map_blocks(handle, inode, map, 0);
	पूर्ण अन्यथा अणु
		retval = ext4_ind_map_blocks(handle, inode, map, 0);
	पूर्ण
	up_पढ़ो((&EXT4_I(inode)->i_data_sem));

	/*
	 * We करोn't check m_len because extent will be collpased in status
	 * tree.  So the m_len might not equal.
	 */
	अगर (es_map->m_lblk != map->m_lblk ||
	    es_map->m_flags != map->m_flags ||
	    es_map->m_pblk != map->m_pblk) अणु
		prपूर्णांकk("ES cache assertion failed for inode: %lu "
		       "es_cached ex [%d/%d/%llu/%x] != "
		       "found ex [%d/%d/%llu/%x] retval %d flags %x\n",
		       inode->i_ino, es_map->m_lblk, es_map->m_len,
		       es_map->m_pblk, es_map->m_flags, map->m_lblk,
		       map->m_len, map->m_pblk, map->m_flags,
		       retval, flags);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* ES_AGGRESSIVE_TEST */

/*
 * The ext4_map_blocks() function tries to look up the requested blocks,
 * and वापसs अगर the blocks are alपढ़ोy mapped.
 *
 * Otherwise it takes the ग_लिखो lock of the i_data_sem and allocate blocks
 * and store the allocated blocks in the result buffer head and mark it
 * mapped.
 *
 * If file type is extents based, it will call ext4_ext_map_blocks(),
 * Otherwise, call with ext4_ind_map_blocks() to handle indirect mapping
 * based files
 *
 * On success, it वापसs the number of blocks being mapped or allocated.  अगर
 * create==0 and the blocks are pre-allocated and unwritten, the resulting @map
 * is marked as unwritten. If the create == 1, it will mark @map as mapped.
 *
 * It वापसs 0 अगर plain look up failed (blocks have not been allocated), in
 * that हाल, @map is वापसed as unmapped but we still करो fill map->m_len to
 * indicate the length of a hole starting at map->m_lblk.
 *
 * It वापसs the error in हाल of allocation failure.
 */
पूर्णांक ext4_map_blocks(handle_t *handle, काष्ठा inode *inode,
		    काष्ठा ext4_map_blocks *map, पूर्णांक flags)
अणु
	काष्ठा extent_status es;
	पूर्णांक retval;
	पूर्णांक ret = 0;
#अगर_घोषित ES_AGGRESSIVE_TEST
	काष्ठा ext4_map_blocks orig_map;

	स_नकल(&orig_map, map, माप(*map));
#पूर्ण_अगर

	map->m_flags = 0;
	ext_debug(inode, "flag 0x%x, max_blocks %u, logical block %lu\n",
		  flags, map->m_len, (अचिन्हित दीर्घ) map->m_lblk);

	/*
	 * ext4_map_blocks वापसs an पूर्णांक, and m_len is an अचिन्हित पूर्णांक
	 */
	अगर (unlikely(map->m_len > पूर्णांक_उच्च))
		map->m_len = पूर्णांक_उच्च;

	/* We can handle the block number less than EXT_MAX_BLOCKS */
	अगर (unlikely(map->m_lblk >= EXT_MAX_BLOCKS))
		वापस -EFSCORRUPTED;

	/* Lookup extent status tree firstly */
	अगर (!(EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY) &&
	    ext4_es_lookup_extent(inode, map->m_lblk, शून्य, &es)) अणु
		अगर (ext4_es_is_written(&es) || ext4_es_is_unwritten(&es)) अणु
			map->m_pblk = ext4_es_pblock(&es) +
					map->m_lblk - es.es_lblk;
			map->m_flags |= ext4_es_is_written(&es) ?
					EXT4_MAP_MAPPED : EXT4_MAP_UNWRITTEN;
			retval = es.es_len - (map->m_lblk - es.es_lblk);
			अगर (retval > map->m_len)
				retval = map->m_len;
			map->m_len = retval;
		पूर्ण अन्यथा अगर (ext4_es_is_delayed(&es) || ext4_es_is_hole(&es)) अणु
			map->m_pblk = 0;
			retval = es.es_len - (map->m_lblk - es.es_lblk);
			अगर (retval > map->m_len)
				retval = map->m_len;
			map->m_len = retval;
			retval = 0;
		पूर्ण अन्यथा अणु
			BUG();
		पूर्ण
#अगर_घोषित ES_AGGRESSIVE_TEST
		ext4_map_blocks_es_recheck(handle, inode, map,
					   &orig_map, flags);
#पूर्ण_अगर
		जाओ found;
	पूर्ण

	/*
	 * Try to see अगर we can get the block without requesting a new
	 * file प्रणाली block.
	 */
	करोwn_पढ़ो(&EXT4_I(inode)->i_data_sem);
	अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) अणु
		retval = ext4_ext_map_blocks(handle, inode, map, 0);
	पूर्ण अन्यथा अणु
		retval = ext4_ind_map_blocks(handle, inode, map, 0);
	पूर्ण
	अगर (retval > 0) अणु
		अचिन्हित पूर्णांक status;

		अगर (unlikely(retval != map->m_len)) अणु
			ext4_warning(inode->i_sb,
				     "ES len assertion failed for inode "
				     "%lu: retval %d != map->m_len %d",
				     inode->i_ino, retval, map->m_len);
			WARN_ON(1);
		पूर्ण

		status = map->m_flags & EXT4_MAP_UNWRITTEN ?
				EXTENT_STATUS_UNWRITTEN : EXTENT_STATUS_WRITTEN;
		अगर (!(flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE) &&
		    !(status & EXTENT_STATUS_WRITTEN) &&
		    ext4_es_scan_range(inode, &ext4_es_is_delayed, map->m_lblk,
				       map->m_lblk + map->m_len - 1))
			status |= EXTENT_STATUS_DELAYED;
		ret = ext4_es_insert_extent(inode, map->m_lblk,
					    map->m_len, map->m_pblk, status);
		अगर (ret < 0)
			retval = ret;
	पूर्ण
	up_पढ़ो((&EXT4_I(inode)->i_data_sem));

found:
	अगर (retval > 0 && map->m_flags & EXT4_MAP_MAPPED) अणु
		ret = check_block_validity(inode, map);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	/* If it is only a block(s) look up */
	अगर ((flags & EXT4_GET_BLOCKS_CREATE) == 0)
		वापस retval;

	/*
	 * Returns अगर the blocks have alपढ़ोy allocated
	 *
	 * Note that अगर blocks have been pपुनः_स्मृतिated
	 * ext4_ext_get_block() वापसs the create = 0
	 * with buffer head unmapped.
	 */
	अगर (retval > 0 && map->m_flags & EXT4_MAP_MAPPED)
		/*
		 * If we need to convert extent to unwritten
		 * we जारी and करो the actual work in
		 * ext4_ext_map_blocks()
		 */
		अगर (!(flags & EXT4_GET_BLOCKS_CONVERT_UNWRITTEN))
			वापस retval;

	/*
	 * Here we clear m_flags because after allocating an new extent,
	 * it will be set again.
	 */
	map->m_flags &= ~EXT4_MAP_FLAGS;

	/*
	 * New blocks allocate and/or writing to unwritten extent
	 * will possibly result in updating i_data, so we take
	 * the ग_लिखो lock of i_data_sem, and call get_block()
	 * with create == 1 flag.
	 */
	करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);

	/*
	 * We need to check क्रम EXT4 here because migrate
	 * could have changed the inode type in between
	 */
	अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) अणु
		retval = ext4_ext_map_blocks(handle, inode, map, flags);
	पूर्ण अन्यथा अणु
		retval = ext4_ind_map_blocks(handle, inode, map, flags);

		अगर (retval > 0 && map->m_flags & EXT4_MAP_NEW) अणु
			/*
			 * We allocated new blocks which will result in
			 * i_data's क्रमmat changing.  Force the migrate
			 * to fail by clearing migrate flags
			 */
			ext4_clear_inode_state(inode, EXT4_STATE_EXT_MIGRATE);
		पूर्ण

		/*
		 * Update reserved blocks/metadata blocks after successful
		 * block allocation which had been deferred till now. We करोn't
		 * support fallocate क्रम non extent files. So we can update
		 * reserve space here.
		 */
		अगर ((retval > 0) &&
			(flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE))
			ext4_da_update_reserve_space(inode, retval, 1);
	पूर्ण

	अगर (retval > 0) अणु
		अचिन्हित पूर्णांक status;

		अगर (unlikely(retval != map->m_len)) अणु
			ext4_warning(inode->i_sb,
				     "ES len assertion failed for inode "
				     "%lu: retval %d != map->m_len %d",
				     inode->i_ino, retval, map->m_len);
			WARN_ON(1);
		पूर्ण

		/*
		 * We have to zeroout blocks beक्रमe inserting them पूर्णांकo extent
		 * status tree. Otherwise someone could look them up there and
		 * use them beक्रमe they are really zeroed. We also have to
		 * unmap metadata beक्रमe zeroing as otherwise ग_लिखोback can
		 * overग_लिखो zeros with stale data from block device.
		 */
		अगर (flags & EXT4_GET_BLOCKS_ZERO &&
		    map->m_flags & EXT4_MAP_MAPPED &&
		    map->m_flags & EXT4_MAP_NEW) अणु
			ret = ext4_issue_zeroout(inode, map->m_lblk,
						 map->m_pblk, map->m_len);
			अगर (ret) अणु
				retval = ret;
				जाओ out_sem;
			पूर्ण
		पूर्ण

		/*
		 * If the extent has been zeroed out, we करोn't need to update
		 * extent status tree.
		 */
		अगर ((flags & EXT4_GET_BLOCKS_PRE_IO) &&
		    ext4_es_lookup_extent(inode, map->m_lblk, शून्य, &es)) अणु
			अगर (ext4_es_is_written(&es))
				जाओ out_sem;
		पूर्ण
		status = map->m_flags & EXT4_MAP_UNWRITTEN ?
				EXTENT_STATUS_UNWRITTEN : EXTENT_STATUS_WRITTEN;
		अगर (!(flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE) &&
		    !(status & EXTENT_STATUS_WRITTEN) &&
		    ext4_es_scan_range(inode, &ext4_es_is_delayed, map->m_lblk,
				       map->m_lblk + map->m_len - 1))
			status |= EXTENT_STATUS_DELAYED;
		ret = ext4_es_insert_extent(inode, map->m_lblk, map->m_len,
					    map->m_pblk, status);
		अगर (ret < 0) अणु
			retval = ret;
			जाओ out_sem;
		पूर्ण
	पूर्ण

out_sem:
	up_ग_लिखो((&EXT4_I(inode)->i_data_sem));
	अगर (retval > 0 && map->m_flags & EXT4_MAP_MAPPED) अणु
		ret = check_block_validity(inode, map);
		अगर (ret != 0)
			वापस ret;

		/*
		 * Inodes with freshly allocated blocks where contents will be
		 * visible after transaction commit must be on transaction's
		 * ordered data list.
		 */
		अगर (map->m_flags & EXT4_MAP_NEW &&
		    !(map->m_flags & EXT4_MAP_UNWRITTEN) &&
		    !(flags & EXT4_GET_BLOCKS_ZERO) &&
		    !ext4_is_quota_file(inode) &&
		    ext4_should_order_data(inode)) अणु
			loff_t start_byte =
				(loff_t)map->m_lblk << inode->i_blkbits;
			loff_t length = (loff_t)map->m_len << inode->i_blkbits;

			अगर (flags & EXT4_GET_BLOCKS_IO_SUBMIT)
				ret = ext4_jbd2_inode_add_रुको(handle, inode,
						start_byte, length);
			अन्यथा
				ret = ext4_jbd2_inode_add_ग_लिखो(handle, inode,
						start_byte, length);
			अगर (ret)
				वापस ret;
		पूर्ण
		ext4_fc_track_range(handle, inode, map->m_lblk,
			    map->m_lblk + map->m_len - 1);
	पूर्ण

	अगर (retval < 0)
		ext_debug(inode, "failed with err %d\n", retval);
	वापस retval;
पूर्ण

/*
 * Update EXT4_MAP_FLAGS in bh->b_state. For buffer heads attached to pages
 * we have to be careful as someone अन्यथा may be manipulating b_state as well.
 */
अटल व्योम ext4_update_bh_state(काष्ठा buffer_head *bh, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ old_state;
	अचिन्हित दीर्घ new_state;

	flags &= EXT4_MAP_FLAGS;

	/* Dummy buffer_head? Set non-atomically. */
	अगर (!bh->b_page) अणु
		bh->b_state = (bh->b_state & ~EXT4_MAP_FLAGS) | flags;
		वापस;
	पूर्ण
	/*
	 * Someone अन्यथा may be modअगरying b_state. Be careful! This is ugly but
	 * once we get rid of using bh as a container क्रम mapping inक्रमmation
	 * to pass to / from get_block functions, this can go away.
	 */
	करो अणु
		old_state = READ_ONCE(bh->b_state);
		new_state = (old_state & ~EXT4_MAP_FLAGS) | flags;
	पूर्ण जबतक (unlikely(
		 cmpxchg(&bh->b_state, old_state, new_state) != old_state));
पूर्ण

अटल पूर्णांक _ext4_get_block(काष्ठा inode *inode, sector_t iblock,
			   काष्ठा buffer_head *bh, पूर्णांक flags)
अणु
	काष्ठा ext4_map_blocks map;
	पूर्णांक ret = 0;

	अगर (ext4_has_अंतरभूत_data(inode))
		वापस -दुस्फल;

	map.m_lblk = iblock;
	map.m_len = bh->b_size >> inode->i_blkbits;

	ret = ext4_map_blocks(ext4_journal_current_handle(), inode, &map,
			      flags);
	अगर (ret > 0) अणु
		map_bh(bh, inode->i_sb, map.m_pblk);
		ext4_update_bh_state(bh, map.m_flags);
		bh->b_size = inode->i_sb->s_blocksize * map.m_len;
		ret = 0;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		/* hole हाल, need to fill in bh->b_size */
		bh->b_size = inode->i_sb->s_blocksize * map.m_len;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ext4_get_block(काष्ठा inode *inode, sector_t iblock,
		   काष्ठा buffer_head *bh, पूर्णांक create)
अणु
	वापस _ext4_get_block(inode, iblock, bh,
			       create ? EXT4_GET_BLOCKS_CREATE : 0);
पूर्ण

/*
 * Get block function used when preparing क्रम buffered ग_लिखो अगर we require
 * creating an unwritten extent अगर blocks haven't been allocated.  The extent
 * will be converted to written after the IO is complete.
 */
पूर्णांक ext4_get_block_unwritten(काष्ठा inode *inode, sector_t iblock,
			     काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	ext4_debug("ext4_get_block_unwritten: inode %lu, create flag %d\n",
		   inode->i_ino, create);
	वापस _ext4_get_block(inode, iblock, bh_result,
			       EXT4_GET_BLOCKS_IO_CREATE_EXT);
पूर्ण

/* Maximum number of blocks we map क्रम direct IO at once. */
#घोषणा DIO_MAX_BLOCKS 4096

/*
 * `handle' can be शून्य अगर create is zero
 */
काष्ठा buffer_head *ext4_getblk(handle_t *handle, काष्ठा inode *inode,
				ext4_lblk_t block, पूर्णांक map_flags)
अणु
	काष्ठा ext4_map_blocks map;
	काष्ठा buffer_head *bh;
	पूर्णांक create = map_flags & EXT4_GET_BLOCKS_CREATE;
	पूर्णांक err;

	ASSERT((EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
		    || handle != शून्य || create == 0);

	map.m_lblk = block;
	map.m_len = 1;
	err = ext4_map_blocks(handle, inode, &map, map_flags);

	अगर (err == 0)
		वापस create ? ERR_PTR(-ENOSPC) : शून्य;
	अगर (err < 0)
		वापस ERR_PTR(err);

	bh = sb_getblk(inode->i_sb, map.m_pblk);
	अगर (unlikely(!bh))
		वापस ERR_PTR(-ENOMEM);
	अगर (map.m_flags & EXT4_MAP_NEW) अणु
		ASSERT(create != 0);
		ASSERT((EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
			    || (handle != शून्य));

		/*
		 * Now that we करो not always journal data, we should
		 * keep in mind whether this should always journal the
		 * new buffer as metadata.  For now, regular file
		 * ग_लिखोs use ext4_get_block instead, so it's not a
		 * problem.
		 */
		lock_buffer(bh);
		BUFFER_TRACE(bh, "call get_create_access");
		err = ext4_journal_get_create_access(handle, bh);
		अगर (unlikely(err)) अणु
			unlock_buffer(bh);
			जाओ errout;
		पूर्ण
		अगर (!buffer_uptodate(bh)) अणु
			स_रखो(bh->b_data, 0, inode->i_sb->s_blocksize);
			set_buffer_uptodate(bh);
		पूर्ण
		unlock_buffer(bh);
		BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
		err = ext4_handle_dirty_metadata(handle, inode, bh);
		अगर (unlikely(err))
			जाओ errout;
	पूर्ण अन्यथा
		BUFFER_TRACE(bh, "not a new buffer");
	वापस bh;
errout:
	brअन्यथा(bh);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा buffer_head *ext4_bपढ़ो(handle_t *handle, काष्ठा inode *inode,
			       ext4_lblk_t block, पूर्णांक map_flags)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक ret;

	bh = ext4_getblk(handle, inode, block, map_flags);
	अगर (IS_ERR(bh))
		वापस bh;
	अगर (!bh || ext4_buffer_uptodate(bh))
		वापस bh;

	ret = ext4_पढ़ो_bh_lock(bh, REQ_META | REQ_PRIO, true);
	अगर (ret) अणु
		put_bh(bh);
		वापस ERR_PTR(ret);
	पूर्ण
	वापस bh;
पूर्ण

/* Read a contiguous batch of blocks. */
पूर्णांक ext4_bपढ़ो_batch(काष्ठा inode *inode, ext4_lblk_t block, पूर्णांक bh_count,
		     bool रुको, काष्ठा buffer_head **bhs)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < bh_count; i++) अणु
		bhs[i] = ext4_getblk(शून्य, inode, block + i, 0 /* map_flags */);
		अगर (IS_ERR(bhs[i])) अणु
			err = PTR_ERR(bhs[i]);
			bh_count = i;
			जाओ out_brअन्यथा;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < bh_count; i++)
		/* Note that शून्य bhs[i] is valid because of holes. */
		अगर (bhs[i] && !ext4_buffer_uptodate(bhs[i]))
			ext4_पढ़ो_bh_lock(bhs[i], REQ_META | REQ_PRIO, false);

	अगर (!रुको)
		वापस 0;

	क्रम (i = 0; i < bh_count; i++)
		अगर (bhs[i])
			रुको_on_buffer(bhs[i]);

	क्रम (i = 0; i < bh_count; i++) अणु
		अगर (bhs[i] && !buffer_uptodate(bhs[i])) अणु
			err = -EIO;
			जाओ out_brअन्यथा;
		पूर्ण
	पूर्ण
	वापस 0;

out_brअन्यथा:
	क्रम (i = 0; i < bh_count; i++) अणु
		brअन्यथा(bhs[i]);
		bhs[i] = शून्य;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक ext4_walk_page_buffers(handle_t *handle,
			   काष्ठा buffer_head *head,
			   अचिन्हित from,
			   अचिन्हित to,
			   पूर्णांक *partial,
			   पूर्णांक (*fn)(handle_t *handle,
				     काष्ठा buffer_head *bh))
अणु
	काष्ठा buffer_head *bh;
	अचिन्हित block_start, block_end;
	अचिन्हित blocksize = head->b_size;
	पूर्णांक err, ret = 0;
	काष्ठा buffer_head *next;

	क्रम (bh = head, block_start = 0;
	     ret == 0 && (bh != head || !block_start);
	     block_start = block_end, bh = next) अणु
		next = bh->b_this_page;
		block_end = block_start + blocksize;
		अगर (block_end <= from || block_start >= to) अणु
			अगर (partial && !buffer_uptodate(bh))
				*partial = 1;
			जारी;
		पूर्ण
		err = (*fn)(handle, bh);
		अगर (!ret)
			ret = err;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * To preserve ordering, it is essential that the hole instantiation and
 * the data ग_लिखो be encapsulated in a single transaction.  We cannot
 * बंद off a transaction and start a new one between the ext4_get_block()
 * and the commit_ग_लिखो().  So करोing the jbd2_journal_start at the start of
 * prepare_ग_लिखो() is the right place.
 *
 * Also, this function can nest inside ext4_ग_लिखोpage().  In that हाल, we
 * *know* that ext4_ग_लिखोpage() has generated enough buffer credits to करो the
 * whole page.  So we won't block on the journal in that हाल, which is good,
 * because the caller may be PF_MEMALLOC.
 *
 * By accident, ext4 can be reentered when a transaction is खोलो via
 * quota file ग_लिखोs.  If we were to commit the transaction जबतक thus
 * reentered, there can be a deadlock - we would be holding a quota
 * lock, and the commit would never complete अगर another thपढ़ो had a
 * transaction खोलो and was blocking on the quota lock - a ranking
 * violation.
 *
 * So what we करो is to rely on the fact that jbd2_journal_stop/journal_start
 * will _not_ run commit under these circumstances because handle->h_ref
 * is elevated.  We'll still have enough credits क्रम the tiny quotafile
 * ग_लिखो.
 */
पूर्णांक करो_journal_get_ग_लिखो_access(handle_t *handle,
				काष्ठा buffer_head *bh)
अणु
	पूर्णांक dirty = buffer_dirty(bh);
	पूर्णांक ret;

	अगर (!buffer_mapped(bh) || buffer_मुक्तd(bh))
		वापस 0;
	/*
	 * __block_ग_लिखो_begin() could have dirtied some buffers. Clean
	 * the dirty bit as jbd2_journal_get_ग_लिखो_access() could complain
	 * otherwise about fs पूर्णांकegrity issues. Setting of the dirty bit
	 * by __block_ग_लिखो_begin() isn't a real problem here as we clear
	 * the bit beक्रमe releasing a page lock and thus ग_लिखोback cannot
	 * ever ग_लिखो the buffer.
	 */
	अगर (dirty)
		clear_buffer_dirty(bh);
	BUFFER_TRACE(bh, "get write access");
	ret = ext4_journal_get_ग_लिखो_access(handle, bh);
	अगर (!ret && dirty)
		ret = ext4_handle_dirty_metadata(handle, शून्य, bh);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_FS_ENCRYPTION
अटल पूर्णांक ext4_block_ग_लिखो_begin(काष्ठा page *page, loff_t pos, अचिन्हित len,
				  get_block_t *get_block)
अणु
	अचिन्हित from = pos & (PAGE_SIZE - 1);
	अचिन्हित to = from + len;
	काष्ठा inode *inode = page->mapping->host;
	अचिन्हित block_start, block_end;
	sector_t block;
	पूर्णांक err = 0;
	अचिन्हित blocksize = inode->i_sb->s_blocksize;
	अचिन्हित bbits;
	काष्ठा buffer_head *bh, *head, *रुको[2];
	पूर्णांक nr_रुको = 0;
	पूर्णांक i;

	BUG_ON(!PageLocked(page));
	BUG_ON(from > PAGE_SIZE);
	BUG_ON(to > PAGE_SIZE);
	BUG_ON(from > to);

	अगर (!page_has_buffers(page))
		create_empty_buffers(page, blocksize, 0);
	head = page_buffers(page);
	bbits = ilog2(blocksize);
	block = (sector_t)page->index << (PAGE_SHIFT - bbits);

	क्रम (bh = head, block_start = 0; bh != head || !block_start;
	    block++, block_start = block_end, bh = bh->b_this_page) अणु
		block_end = block_start + blocksize;
		अगर (block_end <= from || block_start >= to) अणु
			अगर (PageUptodate(page)) अणु
				set_buffer_uptodate(bh);
			पूर्ण
			जारी;
		पूर्ण
		अगर (buffer_new(bh))
			clear_buffer_new(bh);
		अगर (!buffer_mapped(bh)) अणु
			WARN_ON(bh->b_size != blocksize);
			err = get_block(inode, block, bh, 1);
			अगर (err)
				अवरोध;
			अगर (buffer_new(bh)) अणु
				अगर (PageUptodate(page)) अणु
					clear_buffer_new(bh);
					set_buffer_uptodate(bh);
					mark_buffer_dirty(bh);
					जारी;
				पूर्ण
				अगर (block_end > to || block_start < from)
					zero_user_segments(page, to, block_end,
							   block_start, from);
				जारी;
			पूर्ण
		पूर्ण
		अगर (PageUptodate(page)) अणु
			set_buffer_uptodate(bh);
			जारी;
		पूर्ण
		अगर (!buffer_uptodate(bh) && !buffer_delay(bh) &&
		    !buffer_unwritten(bh) &&
		    (block_start < from || block_end > to)) अणु
			ext4_पढ़ो_bh_lock(bh, 0, false);
			रुको[nr_रुको++] = bh;
		पूर्ण
	पूर्ण
	/*
	 * If we issued पढ़ो requests, let them complete.
	 */
	क्रम (i = 0; i < nr_रुको; i++) अणु
		रुको_on_buffer(रुको[i]);
		अगर (!buffer_uptodate(रुको[i]))
			err = -EIO;
	पूर्ण
	अगर (unlikely(err)) अणु
		page_zero_new_buffers(page, from, to);
	पूर्ण अन्यथा अगर (fscrypt_inode_uses_fs_layer_crypto(inode)) अणु
		क्रम (i = 0; i < nr_रुको; i++) अणु
			पूर्णांक err2;

			err2 = fscrypt_decrypt_pagecache_blocks(page, blocksize,
								bh_offset(रुको[i]));
			अगर (err2) अणु
				clear_buffer_uptodate(रुको[i]);
				err = err2;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ext4_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			    loff_t pos, अचिन्हित len, अचिन्हित flags,
			    काष्ठा page **pagep, व्योम **fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	पूर्णांक ret, needed_blocks;
	handle_t *handle;
	पूर्णांक retries = 0;
	काष्ठा page *page;
	pgoff_t index;
	अचिन्हित from, to;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

	trace_ext4_ग_लिखो_begin(inode, pos, len, flags);
	/*
	 * Reserve one block more क्रम addition to orphan list in हाल
	 * we allocate blocks but ग_लिखो fails क्रम some reason
	 */
	needed_blocks = ext4_ग_लिखोpage_trans_blocks(inode) + 1;
	index = pos >> PAGE_SHIFT;
	from = pos & (PAGE_SIZE - 1);
	to = from + len;

	अगर (ext4_test_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA)) अणु
		ret = ext4_try_to_ग_लिखो_अंतरभूत_data(mapping, inode, pos, len,
						    flags, pagep);
		अगर (ret < 0)
			वापस ret;
		अगर (ret == 1)
			वापस 0;
	पूर्ण

	/*
	 * grab_cache_page_ग_लिखो_begin() can take a दीर्घ समय अगर the
	 * प्रणाली is thrashing due to memory pressure, or अगर the page
	 * is being written back.  So grab it first beक्रमe we start
	 * the transaction handle.  This also allows us to allocate
	 * the page (अगर needed) without using GFP_NOFS.
	 */
retry_grab:
	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;
	unlock_page(page);

retry_journal:
	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE, needed_blocks);
	अगर (IS_ERR(handle)) अणु
		put_page(page);
		वापस PTR_ERR(handle);
	पूर्ण

	lock_page(page);
	अगर (page->mapping != mapping) अणु
		/* The page got truncated from under us */
		unlock_page(page);
		put_page(page);
		ext4_journal_stop(handle);
		जाओ retry_grab;
	पूर्ण
	/* In हाल ग_लिखोback began जबतक the page was unlocked */
	रुको_क्रम_stable_page(page);

#अगर_घोषित CONFIG_FS_ENCRYPTION
	अगर (ext4_should_dioपढ़ो_nolock(inode))
		ret = ext4_block_ग_लिखो_begin(page, pos, len,
					     ext4_get_block_unwritten);
	अन्यथा
		ret = ext4_block_ग_लिखो_begin(page, pos, len,
					     ext4_get_block);
#अन्यथा
	अगर (ext4_should_dioपढ़ो_nolock(inode))
		ret = __block_ग_लिखो_begin(page, pos, len,
					  ext4_get_block_unwritten);
	अन्यथा
		ret = __block_ग_लिखो_begin(page, pos, len, ext4_get_block);
#पूर्ण_अगर
	अगर (!ret && ext4_should_journal_data(inode)) अणु
		ret = ext4_walk_page_buffers(handle, page_buffers(page),
					     from, to, शून्य,
					     करो_journal_get_ग_लिखो_access);
	पूर्ण

	अगर (ret) अणु
		bool extended = (pos + len > inode->i_size) &&
				!ext4_verity_in_progress(inode);

		unlock_page(page);
		/*
		 * __block_ग_लिखो_begin may have instantiated a few blocks
		 * outside i_size.  Trim these off again. Don't need
		 * i_size_पढ़ो because we hold i_mutex.
		 *
		 * Add inode to orphan list in हाल we crash beक्रमe
		 * truncate finishes
		 */
		अगर (extended && ext4_can_truncate(inode))
			ext4_orphan_add(handle, inode);

		ext4_journal_stop(handle);
		अगर (extended) अणु
			ext4_truncate_failed_ग_लिखो(inode);
			/*
			 * If truncate failed early the inode might
			 * still be on the orphan list; we need to
			 * make sure the inode is हटाओd from the
			 * orphan list in that हाल.
			 */
			अगर (inode->i_nlink)
				ext4_orphan_del(शून्य, inode);
		पूर्ण

		अगर (ret == -ENOSPC &&
		    ext4_should_retry_alloc(inode->i_sb, &retries))
			जाओ retry_journal;
		put_page(page);
		वापस ret;
	पूर्ण
	*pagep = page;
	वापस ret;
पूर्ण

/* For ग_लिखो_end() in data=journal mode */
अटल पूर्णांक ग_लिखो_end_fn(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret;
	अगर (!buffer_mapped(bh) || buffer_मुक्तd(bh))
		वापस 0;
	set_buffer_uptodate(bh);
	ret = ext4_handle_dirty_metadata(handle, शून्य, bh);
	clear_buffer_meta(bh);
	clear_buffer_prio(bh);
	वापस ret;
पूर्ण

/*
 * We need to pick up the new inode size which generic_commit_ग_लिखो gave us
 * `file' can be शून्य - eg, when called from page_symlink().
 *
 * ext4 never places buffers on inode->i_mapping->निजी_list.  metadata
 * buffers are managed पूर्णांकernally.
 */
अटल पूर्णांक ext4_ग_लिखो_end(काष्ठा file *file,
			  काष्ठा address_space *mapping,
			  loff_t pos, अचिन्हित len, अचिन्हित copied,
			  काष्ठा page *page, व्योम *fsdata)
अणु
	handle_t *handle = ext4_journal_current_handle();
	काष्ठा inode *inode = mapping->host;
	loff_t old_size = inode->i_size;
	पूर्णांक ret = 0, ret2;
	पूर्णांक i_size_changed = 0;
	पूर्णांक अंतरभूत_data = ext4_has_अंतरभूत_data(inode);
	bool verity = ext4_verity_in_progress(inode);

	trace_ext4_ग_लिखो_end(inode, pos, len, copied);
	अगर (अंतरभूत_data) अणु
		ret = ext4_ग_लिखो_अंतरभूत_data_end(inode, pos, len,
						 copied, page);
		अगर (ret < 0) अणु
			unlock_page(page);
			put_page(page);
			जाओ errout;
		पूर्ण
		copied = ret;
	पूर्ण अन्यथा
		copied = block_ग_लिखो_end(file, mapping, pos,
					 len, copied, page, fsdata);
	/*
	 * it's important to update i_size जबतक still holding page lock:
	 * page ग_लिखोout could otherwise come in and zero beyond i_size.
	 *
	 * If FS_IOC_ENABLE_VERITY is running on this inode, then Merkle tree
	 * blocks are being written past खातापूर्ण, so skip the i_size update.
	 */
	अगर (!verity)
		i_size_changed = ext4_update_inode_size(inode, pos + copied);
	unlock_page(page);
	put_page(page);

	अगर (old_size < pos && !verity)
		pagecache_isize_extended(inode, old_size, pos);
	/*
	 * Don't mark the inode dirty under page lock. First, it unnecessarily
	 * makes the holding समय of page lock दीर्घer. Second, it क्रमces lock
	 * ordering of page lock and transaction start क्रम journaling
	 * fileप्रणालीs.
	 */
	अगर (i_size_changed || अंतरभूत_data)
		ret = ext4_mark_inode_dirty(handle, inode);

	अगर (pos + len > inode->i_size && !verity && ext4_can_truncate(inode))
		/* अगर we have allocated more blocks and copied
		 * less. We will have blocks allocated outside
		 * inode->i_size. So truncate them
		 */
		ext4_orphan_add(handle, inode);
errout:
	ret2 = ext4_journal_stop(handle);
	अगर (!ret)
		ret = ret2;

	अगर (pos + len > inode->i_size && !verity) अणु
		ext4_truncate_failed_ग_लिखो(inode);
		/*
		 * If truncate failed early the inode might still be
		 * on the orphan list; we need to make sure the inode
		 * is हटाओd from the orphan list in that हाल.
		 */
		अगर (inode->i_nlink)
			ext4_orphan_del(शून्य, inode);
	पूर्ण

	वापस ret ? ret : copied;
पूर्ण

/*
 * This is a निजी version of page_zero_new_buffers() which करोesn't
 * set the buffer to be dirty, since in data=journalled mode we need
 * to call ext4_handle_dirty_metadata() instead.
 */
अटल व्योम ext4_journalled_zero_new_buffers(handle_t *handle,
					    काष्ठा page *page,
					    अचिन्हित from, अचिन्हित to)
अणु
	अचिन्हित पूर्णांक block_start = 0, block_end;
	काष्ठा buffer_head *head, *bh;

	bh = head = page_buffers(page);
	करो अणु
		block_end = block_start + bh->b_size;
		अगर (buffer_new(bh)) अणु
			अगर (block_end > from && block_start < to) अणु
				अगर (!PageUptodate(page)) अणु
					अचिन्हित start, size;

					start = max(from, block_start);
					size = min(to, block_end) - start;

					zero_user(page, start, size);
					ग_लिखो_end_fn(handle, bh);
				पूर्ण
				clear_buffer_new(bh);
			पूर्ण
		पूर्ण
		block_start = block_end;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
पूर्ण

अटल पूर्णांक ext4_journalled_ग_लिखो_end(काष्ठा file *file,
				     काष्ठा address_space *mapping,
				     loff_t pos, अचिन्हित len, अचिन्हित copied,
				     काष्ठा page *page, व्योम *fsdata)
अणु
	handle_t *handle = ext4_journal_current_handle();
	काष्ठा inode *inode = mapping->host;
	loff_t old_size = inode->i_size;
	पूर्णांक ret = 0, ret2;
	पूर्णांक partial = 0;
	अचिन्हित from, to;
	पूर्णांक size_changed = 0;
	पूर्णांक अंतरभूत_data = ext4_has_अंतरभूत_data(inode);
	bool verity = ext4_verity_in_progress(inode);

	trace_ext4_journalled_ग_लिखो_end(inode, pos, len, copied);
	from = pos & (PAGE_SIZE - 1);
	to = from + len;

	BUG_ON(!ext4_handle_valid(handle));

	अगर (अंतरभूत_data) अणु
		ret = ext4_ग_लिखो_अंतरभूत_data_end(inode, pos, len,
						 copied, page);
		अगर (ret < 0) अणु
			unlock_page(page);
			put_page(page);
			जाओ errout;
		पूर्ण
		copied = ret;
	पूर्ण अन्यथा अगर (unlikely(copied < len) && !PageUptodate(page)) अणु
		copied = 0;
		ext4_journalled_zero_new_buffers(handle, page, from, to);
	पूर्ण अन्यथा अणु
		अगर (unlikely(copied < len))
			ext4_journalled_zero_new_buffers(handle, page,
							 from + copied, to);
		ret = ext4_walk_page_buffers(handle, page_buffers(page), from,
					     from + copied, &partial,
					     ग_लिखो_end_fn);
		अगर (!partial)
			SetPageUptodate(page);
	पूर्ण
	अगर (!verity)
		size_changed = ext4_update_inode_size(inode, pos + copied);
	ext4_set_inode_state(inode, EXT4_STATE_JDATA);
	EXT4_I(inode)->i_datasync_tid = handle->h_transaction->t_tid;
	unlock_page(page);
	put_page(page);

	अगर (old_size < pos && !verity)
		pagecache_isize_extended(inode, old_size, pos);

	अगर (size_changed || अंतरभूत_data) अणु
		ret2 = ext4_mark_inode_dirty(handle, inode);
		अगर (!ret)
			ret = ret2;
	पूर्ण

	अगर (pos + len > inode->i_size && !verity && ext4_can_truncate(inode))
		/* अगर we have allocated more blocks and copied
		 * less. We will have blocks allocated outside
		 * inode->i_size. So truncate them
		 */
		ext4_orphan_add(handle, inode);

errout:
	ret2 = ext4_journal_stop(handle);
	अगर (!ret)
		ret = ret2;
	अगर (pos + len > inode->i_size && !verity) अणु
		ext4_truncate_failed_ग_लिखो(inode);
		/*
		 * If truncate failed early the inode might still be
		 * on the orphan list; we need to make sure the inode
		 * is हटाओd from the orphan list in that हाल.
		 */
		अगर (inode->i_nlink)
			ext4_orphan_del(शून्य, inode);
	पूर्ण

	वापस ret ? ret : copied;
पूर्ण

/*
 * Reserve space क्रम a single cluster
 */
अटल पूर्णांक ext4_da_reserve_space(काष्ठा inode *inode)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	पूर्णांक ret;

	/*
	 * We will अक्षरge metadata quota at ग_लिखोout समय; this saves
	 * us from metadata over-estimation, though we may go over by
	 * a small amount in the end.  Here we just reserve क्रम data.
	 */
	ret = dquot_reserve_block(inode, EXT4_C2B(sbi, 1));
	अगर (ret)
		वापस ret;

	spin_lock(&ei->i_block_reservation_lock);
	अगर (ext4_claim_मुक्त_clusters(sbi, 1, 0)) अणु
		spin_unlock(&ei->i_block_reservation_lock);
		dquot_release_reservation_block(inode, EXT4_C2B(sbi, 1));
		वापस -ENOSPC;
	पूर्ण
	ei->i_reserved_data_blocks++;
	trace_ext4_da_reserve_space(inode);
	spin_unlock(&ei->i_block_reservation_lock);

	वापस 0;       /* success */
पूर्ण

व्योम ext4_da_release_space(काष्ठा inode *inode, पूर्णांक to_मुक्त)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	अगर (!to_मुक्त)
		वापस;		/* Nothing to release, निकास */

	spin_lock(&EXT4_I(inode)->i_block_reservation_lock);

	trace_ext4_da_release_space(inode, to_मुक्त);
	अगर (unlikely(to_मुक्त > ei->i_reserved_data_blocks)) अणु
		/*
		 * अगर there aren't enough reserved blocks, then the
		 * counter is messed up somewhere.  Since this
		 * function is called from invalidate page, it's
		 * harmless to वापस without any action.
		 */
		ext4_warning(inode->i_sb, "ext4_da_release_space: "
			 "ino %lu, to_free %d with only %d reserved "
			 "data blocks", inode->i_ino, to_मुक्त,
			 ei->i_reserved_data_blocks);
		WARN_ON(1);
		to_मुक्त = ei->i_reserved_data_blocks;
	पूर्ण
	ei->i_reserved_data_blocks -= to_मुक्त;

	/* update fs dirty data blocks counter */
	percpu_counter_sub(&sbi->s_dirtyclusters_counter, to_मुक्त);

	spin_unlock(&EXT4_I(inode)->i_block_reservation_lock);

	dquot_release_reservation_block(inode, EXT4_C2B(sbi, to_मुक्त));
पूर्ण

/*
 * Delayed allocation stuff
 */

काष्ठा mpage_da_data अणु
	काष्ठा inode *inode;
	काष्ठा ग_लिखोback_control *wbc;

	pgoff_t first_page;	/* The first page to ग_लिखो */
	pgoff_t next_page;	/* Current page to examine */
	pgoff_t last_page;	/* Last page to examine */
	/*
	 * Extent to map - this can be after first_page because that can be
	 * fully mapped. We somewhat abuse m_flags to store whether the extent
	 * is delalloc or unwritten.
	 */
	काष्ठा ext4_map_blocks map;
	काष्ठा ext4_io_submit io_submit;	/* IO submission data */
	अचिन्हित पूर्णांक करो_map:1;
	अचिन्हित पूर्णांक scanned_until_end:1;
पूर्ण;

अटल व्योम mpage_release_unused_pages(काष्ठा mpage_da_data *mpd,
				       bool invalidate)
अणु
	पूर्णांक nr_pages, i;
	pgoff_t index, end;
	काष्ठा pagevec pvec;
	काष्ठा inode *inode = mpd->inode;
	काष्ठा address_space *mapping = inode->i_mapping;

	/* This is necessary when next_page == 0. */
	अगर (mpd->first_page >= mpd->next_page)
		वापस;

	mpd->scanned_until_end = 0;
	index = mpd->first_page;
	end   = mpd->next_page - 1;
	अगर (invalidate) अणु
		ext4_lblk_t start, last;
		start = index << (PAGE_SHIFT - inode->i_blkbits);
		last = end << (PAGE_SHIFT - inode->i_blkbits);
		ext4_es_हटाओ_extent(inode, start, last - start + 1);
	पूर्ण

	pagevec_init(&pvec);
	जबतक (index <= end) अणु
		nr_pages = pagevec_lookup_range(&pvec, mapping, &index, end);
		अगर (nr_pages == 0)
			अवरोध;
		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			BUG_ON(!PageLocked(page));
			BUG_ON(PageWriteback(page));
			अगर (invalidate) अणु
				अगर (page_mapped(page))
					clear_page_dirty_क्रम_io(page);
				block_invalidatepage(page, 0, PAGE_SIZE);
				ClearPageUptodate(page);
			पूर्ण
			unlock_page(page);
		पूर्ण
		pagevec_release(&pvec);
	पूर्ण
पूर्ण

अटल व्योम ext4_prपूर्णांक_मुक्त_blocks(काष्ठा inode *inode)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	ext4_msg(sb, KERN_CRIT, "Total free blocks count %lld",
	       EXT4_C2B(EXT4_SB(inode->i_sb),
			ext4_count_मुक्त_clusters(sb)));
	ext4_msg(sb, KERN_CRIT, "Free/Dirty block details");
	ext4_msg(sb, KERN_CRIT, "free_blocks=%lld",
	       (दीर्घ दीर्घ) EXT4_C2B(EXT4_SB(sb),
		percpu_counter_sum(&sbi->s_मुक्तclusters_counter)));
	ext4_msg(sb, KERN_CRIT, "dirty_blocks=%lld",
	       (दीर्घ दीर्घ) EXT4_C2B(EXT4_SB(sb),
		percpu_counter_sum(&sbi->s_dirtyclusters_counter)));
	ext4_msg(sb, KERN_CRIT, "Block reservation details");
	ext4_msg(sb, KERN_CRIT, "i_reserved_data_blocks=%u",
		 ei->i_reserved_data_blocks);
	वापस;
पूर्ण

अटल पूर्णांक ext4_bh_delay_or_unwritten(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	वापस (buffer_delay(bh) || buffer_unwritten(bh)) && buffer_dirty(bh);
पूर्ण

/*
 * ext4_insert_delayed_block - adds a delayed block to the extents status
 *                             tree, incrementing the reserved cluster/block
 *                             count or making a pending reservation
 *                             where needed
 *
 * @inode - file containing the newly added block
 * @lblk - logical block to be added
 *
 * Returns 0 on success, negative error code on failure.
 */
अटल पूर्णांक ext4_insert_delayed_block(काष्ठा inode *inode, ext4_lblk_t lblk)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	पूर्णांक ret;
	bool allocated = false;

	/*
	 * If the cluster containing lblk is shared with a delayed,
	 * written, or unwritten extent in a bigalloc file प्रणाली, it's
	 * alपढ़ोy been accounted क्रम and करोes not need to be reserved.
	 * A pending reservation must be made क्रम the cluster अगर it's
	 * shared with a written or unwritten extent and करोesn't alपढ़ोy
	 * have one.  Written and unwritten extents can be purged from the
	 * extents status tree अगर the प्रणाली is under memory pressure, so
	 * it's necessary to examine the extent tree अगर a search of the
	 * extents status tree करोesn't get a match.
	 */
	अगर (sbi->s_cluster_ratio == 1) अणु
		ret = ext4_da_reserve_space(inode);
		अगर (ret != 0)   /* ENOSPC */
			जाओ errout;
	पूर्ण अन्यथा अणु   /* bigalloc */
		अगर (!ext4_es_scan_clu(inode, &ext4_es_is_delonly, lblk)) अणु
			अगर (!ext4_es_scan_clu(inode,
					      &ext4_es_is_mapped, lblk)) अणु
				ret = ext4_clu_mapped(inode,
						      EXT4_B2C(sbi, lblk));
				अगर (ret < 0)
					जाओ errout;
				अगर (ret == 0) अणु
					ret = ext4_da_reserve_space(inode);
					अगर (ret != 0)   /* ENOSPC */
						जाओ errout;
				पूर्ण अन्यथा अणु
					allocated = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				allocated = true;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = ext4_es_insert_delayed_block(inode, lblk, allocated);

errout:
	वापस ret;
पूर्ण

/*
 * This function is grअसल code from the very beginning of
 * ext4_map_blocks, but assumes that the caller is from delayed ग_लिखो
 * समय. This function looks up the requested blocks and sets the
 * buffer delay bit under the protection of i_data_sem.
 */
अटल पूर्णांक ext4_da_map_blocks(काष्ठा inode *inode, sector_t iblock,
			      काष्ठा ext4_map_blocks *map,
			      काष्ठा buffer_head *bh)
अणु
	काष्ठा extent_status es;
	पूर्णांक retval;
	sector_t invalid_block = ~((sector_t) 0xffff);
#अगर_घोषित ES_AGGRESSIVE_TEST
	काष्ठा ext4_map_blocks orig_map;

	स_नकल(&orig_map, map, माप(*map));
#पूर्ण_अगर

	अगर (invalid_block < ext4_blocks_count(EXT4_SB(inode->i_sb)->s_es))
		invalid_block = ~0;

	map->m_flags = 0;
	ext_debug(inode, "max_blocks %u, logical block %lu\n", map->m_len,
		  (अचिन्हित दीर्घ) map->m_lblk);

	/* Lookup extent status tree firstly */
	अगर (ext4_es_lookup_extent(inode, iblock, शून्य, &es)) अणु
		अगर (ext4_es_is_hole(&es)) अणु
			retval = 0;
			करोwn_पढ़ो(&EXT4_I(inode)->i_data_sem);
			जाओ add_delayed;
		पूर्ण

		/*
		 * Delayed extent could be allocated by fallocate.
		 * So we need to check it.
		 */
		अगर (ext4_es_is_delayed(&es) && !ext4_es_is_unwritten(&es)) अणु
			map_bh(bh, inode->i_sb, invalid_block);
			set_buffer_new(bh);
			set_buffer_delay(bh);
			वापस 0;
		पूर्ण

		map->m_pblk = ext4_es_pblock(&es) + iblock - es.es_lblk;
		retval = es.es_len - (iblock - es.es_lblk);
		अगर (retval > map->m_len)
			retval = map->m_len;
		map->m_len = retval;
		अगर (ext4_es_is_written(&es))
			map->m_flags |= EXT4_MAP_MAPPED;
		अन्यथा अगर (ext4_es_is_unwritten(&es))
			map->m_flags |= EXT4_MAP_UNWRITTEN;
		अन्यथा
			BUG();

#अगर_घोषित ES_AGGRESSIVE_TEST
		ext4_map_blocks_es_recheck(शून्य, inode, map, &orig_map, 0);
#पूर्ण_अगर
		वापस retval;
	पूर्ण

	/*
	 * Try to see अगर we can get the block without requesting a new
	 * file प्रणाली block.
	 */
	करोwn_पढ़ो(&EXT4_I(inode)->i_data_sem);
	अगर (ext4_has_अंतरभूत_data(inode))
		retval = 0;
	अन्यथा अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		retval = ext4_ext_map_blocks(शून्य, inode, map, 0);
	अन्यथा
		retval = ext4_ind_map_blocks(शून्य, inode, map, 0);

add_delayed:
	अगर (retval == 0) अणु
		पूर्णांक ret;

		/*
		 * XXX: __block_prepare_ग_लिखो() unmaps passed block,
		 * is it OK?
		 */

		ret = ext4_insert_delayed_block(inode, map->m_lblk);
		अगर (ret != 0) अणु
			retval = ret;
			जाओ out_unlock;
		पूर्ण

		map_bh(bh, inode->i_sb, invalid_block);
		set_buffer_new(bh);
		set_buffer_delay(bh);
	पूर्ण अन्यथा अगर (retval > 0) अणु
		पूर्णांक ret;
		अचिन्हित पूर्णांक status;

		अगर (unlikely(retval != map->m_len)) अणु
			ext4_warning(inode->i_sb,
				     "ES len assertion failed for inode "
				     "%lu: retval %d != map->m_len %d",
				     inode->i_ino, retval, map->m_len);
			WARN_ON(1);
		पूर्ण

		status = map->m_flags & EXT4_MAP_UNWRITTEN ?
				EXTENT_STATUS_UNWRITTEN : EXTENT_STATUS_WRITTEN;
		ret = ext4_es_insert_extent(inode, map->m_lblk, map->m_len,
					    map->m_pblk, status);
		अगर (ret != 0)
			retval = ret;
	पूर्ण

out_unlock:
	up_पढ़ो((&EXT4_I(inode)->i_data_sem));

	वापस retval;
पूर्ण

/*
 * This is a special get_block_t callback which is used by
 * ext4_da_ग_लिखो_begin().  It will either वापस mapped block or
 * reserve space क्रम a single block.
 *
 * For delayed buffer_head we have BH_Mapped, BH_New, BH_Delay set.
 * We also have b_blocknr = -1 and b_bdev initialized properly
 *
 * For unwritten buffer_head we have BH_Mapped, BH_New, BH_Unwritten set.
 * We also have b_blocknr = physicalblock mapping unwritten extent and b_bdev
 * initialized properly.
 */
पूर्णांक ext4_da_get_block_prep(काष्ठा inode *inode, sector_t iblock,
			   काष्ठा buffer_head *bh, पूर्णांक create)
अणु
	काष्ठा ext4_map_blocks map;
	पूर्णांक ret = 0;

	BUG_ON(create == 0);
	BUG_ON(bh->b_size != inode->i_sb->s_blocksize);

	map.m_lblk = iblock;
	map.m_len = 1;

	/*
	 * first, we need to know whether the block is allocated alपढ़ोy
	 * pपुनः_स्मृतिated blocks are unmapped but should treated
	 * the same as allocated blocks.
	 */
	ret = ext4_da_map_blocks(inode, iblock, &map, bh);
	अगर (ret <= 0)
		वापस ret;

	map_bh(bh, inode->i_sb, map.m_pblk);
	ext4_update_bh_state(bh, map.m_flags);

	अगर (buffer_unwritten(bh)) अणु
		/* A delayed ग_लिखो to unwritten bh should be marked
		 * new and mapped.  Mapped ensures that we करोn't करो
		 * get_block multiple बार when we ग_लिखो to the same
		 * offset and new ensures that we करो proper zero out
		 * क्रम partial ग_लिखो.
		 */
		set_buffer_new(bh);
		set_buffer_mapped(bh);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bget_one(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	get_bh(bh);
	वापस 0;
पूर्ण

अटल पूर्णांक bput_one(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	put_bh(bh);
	वापस 0;
पूर्ण

अटल पूर्णांक __ext4_journalled_ग_लिखोpage(काष्ठा page *page,
				       अचिन्हित पूर्णांक len)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा inode *inode = mapping->host;
	काष्ठा buffer_head *page_bufs = शून्य;
	handle_t *handle = शून्य;
	पूर्णांक ret = 0, err = 0;
	पूर्णांक अंतरभूत_data = ext4_has_अंतरभूत_data(inode);
	काष्ठा buffer_head *inode_bh = शून्य;

	ClearPageChecked(page);

	अगर (अंतरभूत_data) अणु
		BUG_ON(page->index != 0);
		BUG_ON(len > ext4_get_max_अंतरभूत_size(inode));
		inode_bh = ext4_journalled_ग_लिखो_अंतरभूत_data(inode, len, page);
		अगर (inode_bh == शून्य)
			जाओ out;
	पूर्ण अन्यथा अणु
		page_bufs = page_buffers(page);
		अगर (!page_bufs) अणु
			BUG();
			जाओ out;
		पूर्ण
		ext4_walk_page_buffers(handle, page_bufs, 0, len,
				       शून्य, bget_one);
	पूर्ण
	/*
	 * We need to release the page lock beक्रमe we start the
	 * journal, so grab a reference so the page won't disappear
	 * out from under us.
	 */
	get_page(page);
	unlock_page(page);

	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE,
				    ext4_ग_लिखोpage_trans_blocks(inode));
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		put_page(page);
		जाओ out_no_pagelock;
	पूर्ण
	BUG_ON(!ext4_handle_valid(handle));

	lock_page(page);
	put_page(page);
	अगर (page->mapping != mapping) अणु
		/* The page got truncated from under us */
		ext4_journal_stop(handle);
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (अंतरभूत_data) अणु
		ret = ext4_mark_inode_dirty(handle, inode);
	पूर्ण अन्यथा अणु
		ret = ext4_walk_page_buffers(handle, page_bufs, 0, len, शून्य,
					     करो_journal_get_ग_लिखो_access);

		err = ext4_walk_page_buffers(handle, page_bufs, 0, len, शून्य,
					     ग_लिखो_end_fn);
	पूर्ण
	अगर (ret == 0)
		ret = err;
	err = ext4_jbd2_inode_add_ग_लिखो(handle, inode, page_offset(page), len);
	अगर (ret == 0)
		ret = err;
	EXT4_I(inode)->i_datasync_tid = handle->h_transaction->t_tid;
	err = ext4_journal_stop(handle);
	अगर (!ret)
		ret = err;

	ext4_set_inode_state(inode, EXT4_STATE_JDATA);
out:
	unlock_page(page);
out_no_pagelock:
	अगर (!अंतरभूत_data && page_bufs)
		ext4_walk_page_buffers(शून्य, page_bufs, 0, len,
				       शून्य, bput_one);
	brअन्यथा(inode_bh);
	वापस ret;
पूर्ण

/*
 * Note that we करोn't need to start a transaction unless we're journaling data
 * because we should have holes filled from ext4_page_mkग_लिखो(). We even करोn't
 * need to file the inode to the transaction's list in ordered mode because अगर
 * we are writing back data added by ग_लिखो(), the inode is alपढ़ोy there and अगर
 * we are writing back data modअगरied via mmap(), no one guarantees in which
 * transaction the data will hit the disk. In हाल we are journaling data, we
 * cannot start transaction directly because transaction start ranks above page
 * lock so we have to करो some magic.
 *
 * This function can get called via...
 *   - ext4_ग_लिखोpages after taking page lock (have journal handle)
 *   - journal_submit_inode_data_buffers (no journal handle)
 *   - shrink_page_list via the kswapd/direct reclaim (no journal handle)
 *   - grab_page_cache when करोing ग_लिखो_begin (have journal handle)
 *
 * We करोn't करो any block allocation in this function. If we have page with
 * multiple blocks we need to ग_लिखो those buffer_heads that are mapped. This
 * is important क्रम mmaped based ग_लिखो. So अगर we करो with blocksize 1K
 * truncate(f, 1024);
 * a = mmap(f, 0, 4096);
 * a[0] = 'a';
 * truncate(f, 4096);
 * we have in the page first buffer_head mapped via page_mkग_लिखो call back
 * but other buffer_heads would be unmapped but dirty (dirty करोne via the
 * करो_wp_page). So ग_लिखोpage should ग_लिखो the first block. If we modअगरy
 * the mmap area beyond 1024 we will again get a page_fault and the
 * page_mkग_लिखो callback will करो the block allocation and mark the
 * buffer_heads mapped.
 *
 * We redirty the page अगर we have any buffer_heads that is either delay or
 * unwritten in the page.
 *
 * We can get recursively called as show below.
 *
 *	ext4_ग_लिखोpage() -> kदो_स्मृति() -> __alloc_pages() -> page_launder() ->
 *		ext4_ग_लिखोpage()
 *
 * But since we करोn't करो any block allocation we should not deadlock.
 * Page also have the dirty flag cleared so we करोn't get recurive page_lock.
 */
अटल पूर्णांक ext4_ग_लिखोpage(काष्ठा page *page,
			  काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret = 0;
	loff_t size;
	अचिन्हित पूर्णांक len;
	काष्ठा buffer_head *page_bufs = शून्य;
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा ext4_io_submit io_submit;
	bool keep_toग_लिखो = false;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb)))) अणु
		inode->i_mapping->a_ops->invalidatepage(page, 0, PAGE_SIZE);
		unlock_page(page);
		वापस -EIO;
	पूर्ण

	trace_ext4_ग_लिखोpage(page);
	size = i_size_पढ़ो(inode);
	अगर (page->index == size >> PAGE_SHIFT &&
	    !ext4_verity_in_progress(inode))
		len = size & ~PAGE_MASK;
	अन्यथा
		len = PAGE_SIZE;

	page_bufs = page_buffers(page);
	/*
	 * We cannot करो block allocation or other extent handling in this
	 * function. If there are buffers needing that, we have to redirty
	 * the page. But we may reach here when we करो a journal commit via
	 * journal_submit_inode_data_buffers() and in that हाल we must ग_लिखो
	 * allocated buffers to achieve data=ordered mode guarantees.
	 *
	 * Also, अगर there is only one buffer per page (the fs block
	 * size == the page size), अगर one buffer needs block
	 * allocation or needs to modअगरy the extent tree to clear the
	 * unwritten flag, we know that the page can't be written at
	 * all, so we might as well refuse the ग_लिखो immediately.
	 * Unक्रमtunately अगर the block size != page size, we can't as
	 * easily detect this हाल using ext4_walk_page_buffers(), but
	 * क्रम the extremely common हाल, this is an optimization that
	 * skips a useless round trip through ext4_bio_ग_लिखो_page().
	 */
	अगर (ext4_walk_page_buffers(शून्य, page_bufs, 0, len, शून्य,
				   ext4_bh_delay_or_unwritten)) अणु
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		अगर ((current->flags & PF_MEMALLOC) ||
		    (inode->i_sb->s_blocksize == PAGE_SIZE)) अणु
			/*
			 * For memory cleaning there's no poपूर्णांक in writing only
			 * some buffers. So just bail out. Warn अगर we came here
			 * from direct reclaim.
			 */
			WARN_ON_ONCE((current->flags & (PF_MEMALLOC|PF_KSWAPD))
							== PF_MEMALLOC);
			unlock_page(page);
			वापस 0;
		पूर्ण
		keep_toग_लिखो = true;
	पूर्ण

	अगर (PageChecked(page) && ext4_should_journal_data(inode))
		/*
		 * It's mmapped pagecache.  Add buffers and journal it.  There
		 * करोesn't seem much poपूर्णांक in redirtying the page here.
		 */
		वापस __ext4_journalled_ग_लिखोpage(page, len);

	ext4_io_submit_init(&io_submit, wbc);
	io_submit.io_end = ext4_init_io_end(inode, GFP_NOFS);
	अगर (!io_submit.io_end) अणु
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		unlock_page(page);
		वापस -ENOMEM;
	पूर्ण
	ret = ext4_bio_ग_लिखो_page(&io_submit, page, len, keep_toग_लिखो);
	ext4_io_submit(&io_submit);
	/* Drop io_end reference we got from init */
	ext4_put_io_end_defer(io_submit.io_end);
	वापस ret;
पूर्ण

अटल पूर्णांक mpage_submit_page(काष्ठा mpage_da_data *mpd, काष्ठा page *page)
अणु
	पूर्णांक len;
	loff_t size;
	पूर्णांक err;

	BUG_ON(page->index != mpd->first_page);
	clear_page_dirty_क्रम_io(page);
	/*
	 * We have to be very careful here!  Nothing protects ग_लिखोback path
	 * against i_size changes and the page can be ग_लिखोably mapped पूर्णांकo
	 * page tables. So an application can be growing i_size and writing
	 * data through mmap जबतक ग_लिखोback runs. clear_page_dirty_क्रम_io()
	 * ग_लिखो-protects our page in page tables and the page cannot get
	 * written to again until we release page lock. So only after
	 * clear_page_dirty_क्रम_io() we are safe to sample i_size क्रम
	 * ext4_bio_ग_लिखो_page() to zero-out tail of the written page. We rely
	 * on the barrier provided by TestClearPageDirty in
	 * clear_page_dirty_क्रम_io() to make sure i_size is really sampled only
	 * after page tables are updated.
	 */
	size = i_size_पढ़ो(mpd->inode);
	अगर (page->index == size >> PAGE_SHIFT &&
	    !ext4_verity_in_progress(mpd->inode))
		len = size & ~PAGE_MASK;
	अन्यथा
		len = PAGE_SIZE;
	err = ext4_bio_ग_लिखो_page(&mpd->io_submit, page, len, false);
	अगर (!err)
		mpd->wbc->nr_to_ग_लिखो--;
	mpd->first_page++;

	वापस err;
पूर्ण

#घोषणा BH_FLAGS (BIT(BH_Unwritten) | BIT(BH_Delay))

/*
 * mballoc gives us at most this number of blocks...
 * XXX: That seems to be only a limitation of ext4_mb_normalize_request().
 * The rest of mballoc seems to handle chunks up to full group size.
 */
#घोषणा MAX_WRITEPAGES_EXTENT_LEN 2048

/*
 * mpage_add_bh_to_extent - try to add bh to extent of blocks to map
 *
 * @mpd - extent of blocks
 * @lblk - logical number of the block in the file
 * @bh - buffer head we want to add to the extent
 *
 * The function is used to collect contig. blocks in the same state. If the
 * buffer करोesn't require mapping for writeback and we haven't started the
 * extent of buffers to map yet, the function वापसs 'true' immediately - the
 * caller can ग_लिखो the buffer right away. Otherwise the function वापसs true
 * अगर the block has been added to the extent, false अगर the block couldn't be
 * added.
 */
अटल bool mpage_add_bh_to_extent(काष्ठा mpage_da_data *mpd, ext4_lblk_t lblk,
				   काष्ठा buffer_head *bh)
अणु
	काष्ठा ext4_map_blocks *map = &mpd->map;

	/* Buffer that करोesn't need mapping क्रम ग_लिखोback? */
	अगर (!buffer_dirty(bh) || !buffer_mapped(bh) ||
	    (!buffer_delay(bh) && !buffer_unwritten(bh))) अणु
		/* So far no extent to map => we ग_लिखो the buffer right away */
		अगर (map->m_len == 0)
			वापस true;
		वापस false;
	पूर्ण

	/* First block in the extent? */
	अगर (map->m_len == 0) अणु
		/* We cannot map unless handle is started... */
		अगर (!mpd->करो_map)
			वापस false;
		map->m_lblk = lblk;
		map->m_len = 1;
		map->m_flags = bh->b_state & BH_FLAGS;
		वापस true;
	पूर्ण

	/* Don't go larger than mballoc is willing to allocate */
	अगर (map->m_len >= MAX_WRITEPAGES_EXTENT_LEN)
		वापस false;

	/* Can we merge the block to our big extent? */
	अगर (lblk == map->m_lblk + map->m_len &&
	    (bh->b_state & BH_FLAGS) == map->m_flags) अणु
		map->m_len++;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * mpage_process_page_bufs - submit page buffers क्रम IO or add them to extent
 *
 * @mpd - extent of blocks क्रम mapping
 * @head - the first buffer in the page
 * @bh - buffer we should start processing from
 * @lblk - logical number of the block in the file corresponding to @bh
 *
 * Walk through page buffers from @bh upto @head (exclusive) and either submit
 * the page क्रम IO अगर all buffers in this page were mapped and there's no
 * accumulated extent of buffers to map or add buffers in the page to the
 * extent of buffers to map. The function वापसs 1 अगर the caller can जारी
 * by processing the next page, 0 अगर it should stop adding buffers to the
 * extent to map because we cannot extend it anymore. It can also वापस value
 * < 0 in हाल of error during IO submission.
 */
अटल पूर्णांक mpage_process_page_bufs(काष्ठा mpage_da_data *mpd,
				   काष्ठा buffer_head *head,
				   काष्ठा buffer_head *bh,
				   ext4_lblk_t lblk)
अणु
	काष्ठा inode *inode = mpd->inode;
	पूर्णांक err;
	ext4_lblk_t blocks = (i_size_पढ़ो(inode) + i_blocksize(inode) - 1)
							>> inode->i_blkbits;

	अगर (ext4_verity_in_progress(inode))
		blocks = EXT_MAX_BLOCKS;

	करो अणु
		BUG_ON(buffer_locked(bh));

		अगर (lblk >= blocks || !mpage_add_bh_to_extent(mpd, lblk, bh)) अणु
			/* Found extent to map? */
			अगर (mpd->map.m_len)
				वापस 0;
			/* Buffer needs mapping and handle is not started? */
			अगर (!mpd->करो_map)
				वापस 0;
			/* Everything mapped so far and we hit खातापूर्ण */
			अवरोध;
		पूर्ण
	पूर्ण जबतक (lblk++, (bh = bh->b_this_page) != head);
	/* So far everything mapped? Submit the page क्रम IO. */
	अगर (mpd->map.m_len == 0) अणु
		err = mpage_submit_page(mpd, head->b_page);
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (lblk >= blocks) अणु
		mpd->scanned_until_end = 1;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * mpage_process_page - update page buffers corresponding to changed extent and
 *		       may submit fully mapped page क्रम IO
 *
 * @mpd		- description of extent to map, on वापस next extent to map
 * @m_lblk	- logical block mapping.
 * @m_pblk	- corresponding physical mapping.
 * @map_bh	- determines on वापस whether this page requires any further
 *		  mapping or not.
 * Scan given page buffers corresponding to changed extent and update buffer
 * state according to new extent state.
 * We map delalloc buffers to their physical location, clear unwritten bits.
 * If the given page is not fully mapped, we update @map to the next extent in
 * the given page that needs mapping & वापस @map_bh as true.
 */
अटल पूर्णांक mpage_process_page(काष्ठा mpage_da_data *mpd, काष्ठा page *page,
			      ext4_lblk_t *m_lblk, ext4_fsblk_t *m_pblk,
			      bool *map_bh)
अणु
	काष्ठा buffer_head *head, *bh;
	ext4_io_end_t *io_end = mpd->io_submit.io_end;
	ext4_lblk_t lblk = *m_lblk;
	ext4_fsblk_t pblock = *m_pblk;
	पूर्णांक err = 0;
	पूर्णांक blkbits = mpd->inode->i_blkbits;
	sमाप_प्रकार io_end_size = 0;
	काष्ठा ext4_io_end_vec *io_end_vec = ext4_last_io_end_vec(io_end);

	bh = head = page_buffers(page);
	करो अणु
		अगर (lblk < mpd->map.m_lblk)
			जारी;
		अगर (lblk >= mpd->map.m_lblk + mpd->map.m_len) अणु
			/*
			 * Buffer after end of mapped extent.
			 * Find next buffer in the page to map.
			 */
			mpd->map.m_len = 0;
			mpd->map.m_flags = 0;
			io_end_vec->size += io_end_size;
			io_end_size = 0;

			err = mpage_process_page_bufs(mpd, head, bh, lblk);
			अगर (err > 0)
				err = 0;
			अगर (!err && mpd->map.m_len && mpd->map.m_lblk > lblk) अणु
				io_end_vec = ext4_alloc_io_end_vec(io_end);
				अगर (IS_ERR(io_end_vec)) अणु
					err = PTR_ERR(io_end_vec);
					जाओ out;
				पूर्ण
				io_end_vec->offset = (loff_t)mpd->map.m_lblk << blkbits;
			पूर्ण
			*map_bh = true;
			जाओ out;
		पूर्ण
		अगर (buffer_delay(bh)) अणु
			clear_buffer_delay(bh);
			bh->b_blocknr = pblock++;
		पूर्ण
		clear_buffer_unwritten(bh);
		io_end_size += (1 << blkbits);
	पूर्ण जबतक (lblk++, (bh = bh->b_this_page) != head);

	io_end_vec->size += io_end_size;
	io_end_size = 0;
	*map_bh = false;
out:
	*m_lblk = lblk;
	*m_pblk = pblock;
	वापस err;
पूर्ण

/*
 * mpage_map_buffers - update buffers corresponding to changed extent and
 *		       submit fully mapped pages क्रम IO
 *
 * @mpd - description of extent to map, on वापस next extent to map
 *
 * Scan buffers corresponding to changed extent (we expect corresponding pages
 * to be alपढ़ोy locked) and update buffer state according to new extent state.
 * We map delalloc buffers to their physical location, clear unwritten bits,
 * and mark buffers as uninit when we perक्रमm ग_लिखोs to unwritten extents
 * and करो extent conversion after IO is finished. If the last page is not fully
 * mapped, we update @map to the next extent in the last page that needs
 * mapping. Otherwise we submit the page क्रम IO.
 */
अटल पूर्णांक mpage_map_and_submit_buffers(काष्ठा mpage_da_data *mpd)
अणु
	काष्ठा pagevec pvec;
	पूर्णांक nr_pages, i;
	काष्ठा inode *inode = mpd->inode;
	पूर्णांक bpp_bits = PAGE_SHIFT - inode->i_blkbits;
	pgoff_t start, end;
	ext4_lblk_t lblk;
	ext4_fsblk_t pblock;
	पूर्णांक err;
	bool map_bh = false;

	start = mpd->map.m_lblk >> bpp_bits;
	end = (mpd->map.m_lblk + mpd->map.m_len - 1) >> bpp_bits;
	lblk = start << bpp_bits;
	pblock = mpd->map.m_pblk;

	pagevec_init(&pvec);
	जबतक (start <= end) अणु
		nr_pages = pagevec_lookup_range(&pvec, inode->i_mapping,
						&start, end);
		अगर (nr_pages == 0)
			अवरोध;
		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			err = mpage_process_page(mpd, page, &lblk, &pblock,
						 &map_bh);
			/*
			 * If map_bh is true, means page may require further bh
			 * mapping, or maybe the page was submitted क्रम IO.
			 * So we वापस to call further extent mapping.
			 */
			अगर (err < 0 || map_bh)
				जाओ out;
			/* Page fully mapped - let IO run! */
			err = mpage_submit_page(mpd, page);
			अगर (err < 0)
				जाओ out;
		पूर्ण
		pagevec_release(&pvec);
	पूर्ण
	/* Extent fully mapped and matches with page boundary. We are करोne. */
	mpd->map.m_len = 0;
	mpd->map.m_flags = 0;
	वापस 0;
out:
	pagevec_release(&pvec);
	वापस err;
पूर्ण

अटल पूर्णांक mpage_map_one_extent(handle_t *handle, काष्ठा mpage_da_data *mpd)
अणु
	काष्ठा inode *inode = mpd->inode;
	काष्ठा ext4_map_blocks *map = &mpd->map;
	पूर्णांक get_blocks_flags;
	पूर्णांक err, dioपढ़ो_nolock;

	trace_ext4_da_ग_लिखो_pages_extent(inode, map);
	/*
	 * Call ext4_map_blocks() to allocate any delayed allocation blocks, or
	 * to convert an unwritten extent to be initialized (in the हाल
	 * where we have written पूर्णांकo one or more pपुनः_स्मृतिated blocks).  It is
	 * possible that we're going to need more metadata blocks than
	 * previously reserved. However we must not fail because we're in
	 * ग_लिखोback and there is nothing we can करो about it so it might result
	 * in data loss.  So use reserved blocks to allocate metadata अगर
	 * possible.
	 *
	 * We pass in the magic EXT4_GET_BLOCKS_DELALLOC_RESERVE अगर
	 * the blocks in question are delalloc blocks.  This indicates
	 * that the blocks and quotas has alपढ़ोy been checked when
	 * the data was copied पूर्णांकo the page cache.
	 */
	get_blocks_flags = EXT4_GET_BLOCKS_CREATE |
			   EXT4_GET_BLOCKS_METADATA_NOFAIL |
			   EXT4_GET_BLOCKS_IO_SUBMIT;
	dioपढ़ो_nolock = ext4_should_dioपढ़ो_nolock(inode);
	अगर (dioपढ़ो_nolock)
		get_blocks_flags |= EXT4_GET_BLOCKS_IO_CREATE_EXT;
	अगर (map->m_flags & BIT(BH_Delay))
		get_blocks_flags |= EXT4_GET_BLOCKS_DELALLOC_RESERVE;

	err = ext4_map_blocks(handle, inode, map, get_blocks_flags);
	अगर (err < 0)
		वापस err;
	अगर (dioपढ़ो_nolock && (map->m_flags & EXT4_MAP_UNWRITTEN)) अणु
		अगर (!mpd->io_submit.io_end->handle &&
		    ext4_handle_valid(handle)) अणु
			mpd->io_submit.io_end->handle = handle->h_rsv_handle;
			handle->h_rsv_handle = शून्य;
		पूर्ण
		ext4_set_io_unwritten_flag(inode, mpd->io_submit.io_end);
	पूर्ण

	BUG_ON(map->m_len == 0);
	वापस 0;
पूर्ण

/*
 * mpage_map_and_submit_extent - map extent starting at mpd->lblk of length
 *				 mpd->len and submit pages underlying it क्रम IO
 *
 * @handle - handle क्रम journal operations
 * @mpd - extent to map
 * @give_up_on_ग_लिखो - we set this to true अगरf there is a fatal error and there
 *                     is no hope of writing the data. The caller should discard
 *                     dirty pages to aव्योम infinite loops.
 *
 * The function maps extent starting at mpd->lblk of length mpd->len. If it is
 * delayed, blocks are allocated, अगर it is unwritten, we may need to convert
 * them to initialized or split the described range from larger unwritten
 * extent. Note that we need not map all the described range since allocation
 * can वापस less blocks or the range is covered by more unwritten extents. We
 * cannot map more because we are limited by reserved transaction credits. On
 * the other hand we always make sure that the last touched page is fully
 * mapped so that it can be written out (and thus क्रमward progress is
 * guaranteed). After mapping we submit all mapped pages क्रम IO.
 */
अटल पूर्णांक mpage_map_and_submit_extent(handle_t *handle,
				       काष्ठा mpage_da_data *mpd,
				       bool *give_up_on_ग_लिखो)
अणु
	काष्ठा inode *inode = mpd->inode;
	काष्ठा ext4_map_blocks *map = &mpd->map;
	पूर्णांक err;
	loff_t disksize;
	पूर्णांक progress = 0;
	ext4_io_end_t *io_end = mpd->io_submit.io_end;
	काष्ठा ext4_io_end_vec *io_end_vec;

	io_end_vec = ext4_alloc_io_end_vec(io_end);
	अगर (IS_ERR(io_end_vec))
		वापस PTR_ERR(io_end_vec);
	io_end_vec->offset = ((loff_t)map->m_lblk) << inode->i_blkbits;
	करो अणु
		err = mpage_map_one_extent(handle, mpd);
		अगर (err < 0) अणु
			काष्ठा super_block *sb = inode->i_sb;

			अगर (ext4_क्रमced_shutकरोwn(EXT4_SB(sb)) ||
			    ext4_test_mount_flag(sb, EXT4_MF_FS_ABORTED))
				जाओ invalidate_dirty_pages;
			/*
			 * Let the uper layers retry transient errors.
			 * In the हाल of ENOSPC, अगर ext4_count_मुक्त_blocks()
			 * is non-zero, a commit should मुक्त up blocks.
			 */
			अगर ((err == -ENOMEM) ||
			    (err == -ENOSPC && ext4_count_मुक्त_clusters(sb))) अणु
				अगर (progress)
					जाओ update_disksize;
				वापस err;
			पूर्ण
			ext4_msg(sb, KERN_CRIT,
				 "Delayed block allocation failed for "
				 "inode %lu at logical offset %llu with"
				 " max blocks %u with error %d",
				 inode->i_ino,
				 (अचिन्हित दीर्घ दीर्घ)map->m_lblk,
				 (अचिन्हित)map->m_len, -err);
			ext4_msg(sb, KERN_CRIT,
				 "This should not happen!! Data will "
				 "be lost\n");
			अगर (err == -ENOSPC)
				ext4_prपूर्णांक_मुक्त_blocks(inode);
		invalidate_dirty_pages:
			*give_up_on_ग_लिखो = true;
			वापस err;
		पूर्ण
		progress = 1;
		/*
		 * Update buffer state, submit mapped pages, and get us new
		 * extent to map
		 */
		err = mpage_map_and_submit_buffers(mpd);
		अगर (err < 0)
			जाओ update_disksize;
	पूर्ण जबतक (map->m_len);

update_disksize:
	/*
	 * Update on-disk size after IO is submitted.  Races with
	 * truncate are aव्योमed by checking i_size under i_data_sem.
	 */
	disksize = ((loff_t)mpd->first_page) << PAGE_SHIFT;
	अगर (disksize > READ_ONCE(EXT4_I(inode)->i_disksize)) अणु
		पूर्णांक err2;
		loff_t i_size;

		करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		i_size = i_size_पढ़ो(inode);
		अगर (disksize > i_size)
			disksize = i_size;
		अगर (disksize > EXT4_I(inode)->i_disksize)
			EXT4_I(inode)->i_disksize = disksize;
		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		err2 = ext4_mark_inode_dirty(handle, inode);
		अगर (err2) अणु
			ext4_error_err(inode->i_sb, -err2,
				       "Failed to mark inode %lu dirty",
				       inode->i_ino);
		पूर्ण
		अगर (!err)
			err = err2;
	पूर्ण
	वापस err;
पूर्ण

/*
 * Calculate the total number of credits to reserve क्रम one ग_लिखोpages
 * iteration. This is called from ext4_ग_लिखोpages(). We map an extent of
 * up to MAX_WRITEPAGES_EXTENT_LEN blocks and then we go on and finish mapping
 * the last partial page. So in total we can map MAX_WRITEPAGES_EXTENT_LEN +
 * bpp - 1 blocks in bpp dअगरferent extents.
 */
अटल पूर्णांक ext4_da_ग_लिखोpages_trans_blocks(काष्ठा inode *inode)
अणु
	पूर्णांक bpp = ext4_journal_blocks_per_page(inode);

	वापस ext4_meta_trans_blocks(inode,
				MAX_WRITEPAGES_EXTENT_LEN + bpp - 1, bpp);
पूर्ण

/*
 * mpage_prepare_extent_to_map - find & lock contiguous range of dirty pages
 * 				 and underlying extent to map
 *
 * @mpd - where to look क्रम pages
 *
 * Walk dirty pages in the mapping. If they are fully mapped, submit them क्रम
 * IO immediately. When we find a page which isn't mapped we start accumulating
 * extent of buffers underlying these pages that needs mapping (क्रमmed by
 * either delayed or unwritten buffers). We also lock the pages containing
 * these buffers. The extent found is वापसed in @mpd काष्ठाure (starting at
 * mpd->lblk with length mpd->len blocks).
 *
 * Note that this function can attach bios to one io_end काष्ठाure which are
 * neither logically nor physically contiguous. Although it may seem as an
 * unnecessary complication, it is actually inevitable in blocksize < pagesize
 * हाल as we need to track IO to all buffers underlying a page in one io_end.
 */
अटल पूर्णांक mpage_prepare_extent_to_map(काष्ठा mpage_da_data *mpd)
अणु
	काष्ठा address_space *mapping = mpd->inode->i_mapping;
	काष्ठा pagevec pvec;
	अचिन्हित पूर्णांक nr_pages;
	दीर्घ left = mpd->wbc->nr_to_ग_लिखो;
	pgoff_t index = mpd->first_page;
	pgoff_t end = mpd->last_page;
	xa_mark_t tag;
	पूर्णांक i, err = 0;
	पूर्णांक blkbits = mpd->inode->i_blkbits;
	ext4_lblk_t lblk;
	काष्ठा buffer_head *head;

	अगर (mpd->wbc->sync_mode == WB_SYNC_ALL || mpd->wbc->tagged_ग_लिखोpages)
		tag = PAGECACHE_TAG_TOWRITE;
	अन्यथा
		tag = PAGECACHE_TAG_सूचीTY;

	pagevec_init(&pvec);
	mpd->map.m_len = 0;
	mpd->next_page = index;
	जबतक (index <= end) अणु
		nr_pages = pagevec_lookup_range_tag(&pvec, mapping, &index, end,
				tag);
		अगर (nr_pages == 0)
			अवरोध;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			/*
			 * Accumulated enough dirty pages? This करोesn't apply
			 * to WB_SYNC_ALL mode. For पूर्णांकegrity sync we have to
			 * keep going because someone may be concurrently
			 * dirtying pages, and we might have synced a lot of
			 * newly appeared dirty pages, but have not synced all
			 * of the old dirty pages.
			 */
			अगर (mpd->wbc->sync_mode == WB_SYNC_NONE && left <= 0)
				जाओ out;

			/* If we can't merge this page, we are करोne. */
			अगर (mpd->map.m_len > 0 && mpd->next_page != page->index)
				जाओ out;

			lock_page(page);
			/*
			 * If the page is no दीर्घer dirty, or its mapping no
			 * दीर्घer corresponds to inode we are writing (which
			 * means it has been truncated or invalidated), or the
			 * page is alपढ़ोy under ग_लिखोback and we are not करोing
			 * a data पूर्णांकegrity ग_लिखोback, skip the page
			 */
			अगर (!PageDirty(page) ||
			    (PageWriteback(page) &&
			     (mpd->wbc->sync_mode == WB_SYNC_NONE)) ||
			    unlikely(page->mapping != mapping)) अणु
				unlock_page(page);
				जारी;
			पूर्ण

			रुको_on_page_ग_लिखोback(page);
			BUG_ON(PageWriteback(page));

			अगर (mpd->map.m_len == 0)
				mpd->first_page = page->index;
			mpd->next_page = page->index + 1;
			/* Add all dirty buffers to mpd */
			lblk = ((ext4_lblk_t)page->index) <<
				(PAGE_SHIFT - blkbits);
			head = page_buffers(page);
			err = mpage_process_page_bufs(mpd, head, head, lblk);
			अगर (err <= 0)
				जाओ out;
			err = 0;
			left--;
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
	mpd->scanned_until_end = 1;
	वापस 0;
out:
	pagevec_release(&pvec);
	वापस err;
पूर्ण

अटल पूर्णांक ext4_ग_लिखोpages(काष्ठा address_space *mapping,
			   काष्ठा ग_लिखोback_control *wbc)
अणु
	pgoff_t	ग_लिखोback_index = 0;
	दीर्घ nr_to_ग_लिखो = wbc->nr_to_ग_लिखो;
	पूर्णांक range_whole = 0;
	पूर्णांक cycled = 1;
	handle_t *handle = शून्य;
	काष्ठा mpage_da_data mpd;
	काष्ठा inode *inode = mapping->host;
	पूर्णांक needed_blocks, rsv_blocks = 0, ret = 0;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(mapping->host->i_sb);
	काष्ठा blk_plug plug;
	bool give_up_on_ग_लिखो = false;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

	percpu_करोwn_पढ़ो(&sbi->s_ग_लिखोpages_rwsem);
	trace_ext4_ग_लिखोpages(inode, wbc);

	/*
	 * No pages to ग_लिखो? This is मुख्यly a kludge to aव्योम starting
	 * a transaction क्रम special inodes like journal inode on last iput()
	 * because that could violate lock ordering on umount
	 */
	अगर (!mapping->nrpages || !mapping_tagged(mapping, PAGECACHE_TAG_सूचीTY))
		जाओ out_ग_लिखोpages;

	अगर (ext4_should_journal_data(inode)) अणु
		ret = generic_ग_लिखोpages(mapping, wbc);
		जाओ out_ग_लिखोpages;
	पूर्ण

	/*
	 * If the fileप्रणाली has पातed, it is पढ़ो-only, so वापस
	 * right away instead of dumping stack traces later on that
	 * will obscure the real source of the problem.  We test
	 * EXT4_MF_FS_ABORTED instead of sb->s_flag's SB_RDONLY because
	 * the latter could be true अगर the fileप्रणाली is mounted
	 * पढ़ो-only, and in that हाल, ext4_ग_लिखोpages should
	 * *never* be called, so अगर that ever happens, we would want
	 * the stack trace.
	 */
	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(mapping->host->i_sb)) ||
		     ext4_test_mount_flag(inode->i_sb, EXT4_MF_FS_ABORTED))) अणु
		ret = -EROFS;
		जाओ out_ग_लिखोpages;
	पूर्ण

	/*
	 * If we have अंतरभूत data and arrive here, it means that
	 * we will soon create the block क्रम the 1st page, so
	 * we'd better clear the अंतरभूत data here.
	 */
	अगर (ext4_has_अंतरभूत_data(inode)) अणु
		/* Just inode will be modअगरied... */
		handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
		अगर (IS_ERR(handle)) अणु
			ret = PTR_ERR(handle);
			जाओ out_ग_लिखोpages;
		पूर्ण
		BUG_ON(ext4_test_inode_state(inode,
				EXT4_STATE_MAY_INLINE_DATA));
		ext4_destroy_अंतरभूत_data(handle, inode);
		ext4_journal_stop(handle);
	पूर्ण

	अगर (ext4_should_dioपढ़ो_nolock(inode)) अणु
		/*
		 * We may need to convert up to one extent per block in
		 * the page and we may dirty the inode.
		 */
		rsv_blocks = 1 + ext4_chunk_trans_blocks(inode,
						PAGE_SIZE >> inode->i_blkbits);
	पूर्ण

	अगर (wbc->range_start == 0 && wbc->range_end == Lदीर्घ_उच्च)
		range_whole = 1;

	अगर (wbc->range_cyclic) अणु
		ग_लिखोback_index = mapping->ग_लिखोback_index;
		अगर (ग_लिखोback_index)
			cycled = 0;
		mpd.first_page = ग_लिखोback_index;
		mpd.last_page = -1;
	पूर्ण अन्यथा अणु
		mpd.first_page = wbc->range_start >> PAGE_SHIFT;
		mpd.last_page = wbc->range_end >> PAGE_SHIFT;
	पूर्ण

	mpd.inode = inode;
	mpd.wbc = wbc;
	ext4_io_submit_init(&mpd.io_submit, wbc);
retry:
	अगर (wbc->sync_mode == WB_SYNC_ALL || wbc->tagged_ग_लिखोpages)
		tag_pages_क्रम_ग_लिखोback(mapping, mpd.first_page, mpd.last_page);
	blk_start_plug(&plug);

	/*
	 * First ग_लिखोback pages that करोn't need mapping - we can aव्योम
	 * starting a transaction unnecessarily and also aव्योम being blocked
	 * in the block layer on device congestion जबतक having transaction
	 * started.
	 */
	mpd.करो_map = 0;
	mpd.scanned_until_end = 0;
	mpd.io_submit.io_end = ext4_init_io_end(inode, GFP_KERNEL);
	अगर (!mpd.io_submit.io_end) अणु
		ret = -ENOMEM;
		जाओ unplug;
	पूर्ण
	ret = mpage_prepare_extent_to_map(&mpd);
	/* Unlock pages we didn't use */
	mpage_release_unused_pages(&mpd, false);
	/* Submit prepared bio */
	ext4_io_submit(&mpd.io_submit);
	ext4_put_io_end_defer(mpd.io_submit.io_end);
	mpd.io_submit.io_end = शून्य;
	अगर (ret < 0)
		जाओ unplug;

	जबतक (!mpd.scanned_until_end && wbc->nr_to_ग_लिखो > 0) अणु
		/* For each extent of pages we use new io_end */
		mpd.io_submit.io_end = ext4_init_io_end(inode, GFP_KERNEL);
		अगर (!mpd.io_submit.io_end) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		/*
		 * We have two स्थिरraपूर्णांकs: We find one extent to map and we
		 * must always ग_लिखो out whole page (makes a dअगरference when
		 * blocksize < pagesize) so that we करोn't block on IO when we
		 * try to ग_लिखो out the rest of the page. Journalled mode is
		 * not supported by delalloc.
		 */
		BUG_ON(ext4_should_journal_data(inode));
		needed_blocks = ext4_da_ग_लिखोpages_trans_blocks(inode);

		/* start a new transaction */
		handle = ext4_journal_start_with_reserve(inode,
				EXT4_HT_WRITE_PAGE, needed_blocks, rsv_blocks);
		अगर (IS_ERR(handle)) अणु
			ret = PTR_ERR(handle);
			ext4_msg(inode->i_sb, KERN_CRIT, "%s: jbd2_start: "
			       "%ld pages, ino %lu; err %d", __func__,
				wbc->nr_to_ग_लिखो, inode->i_ino, ret);
			/* Release allocated io_end */
			ext4_put_io_end(mpd.io_submit.io_end);
			mpd.io_submit.io_end = शून्य;
			अवरोध;
		पूर्ण
		mpd.करो_map = 1;

		trace_ext4_da_ग_लिखो_pages(inode, mpd.first_page, mpd.wbc);
		ret = mpage_prepare_extent_to_map(&mpd);
		अगर (!ret && mpd.map.m_len)
			ret = mpage_map_and_submit_extent(handle, &mpd,
					&give_up_on_ग_लिखो);
		/*
		 * Caution: If the handle is synchronous,
		 * ext4_journal_stop() can रुको क्रम transaction commit
		 * to finish which may depend on ग_लिखोback of pages to
		 * complete or on page lock to be released.  In that
		 * हाल, we have to रुको until after we have
		 * submitted all the IO, released page locks we hold,
		 * and dropped io_end reference (क्रम extent conversion
		 * to be able to complete) beक्रमe stopping the handle.
		 */
		अगर (!ext4_handle_valid(handle) || handle->h_sync == 0) अणु
			ext4_journal_stop(handle);
			handle = शून्य;
			mpd.करो_map = 0;
		पूर्ण
		/* Unlock pages we didn't use */
		mpage_release_unused_pages(&mpd, give_up_on_ग_लिखो);
		/* Submit prepared bio */
		ext4_io_submit(&mpd.io_submit);

		/*
		 * Drop our io_end reference we got from init. We have
		 * to be careful and use deferred io_end finishing अगर
		 * we are still holding the transaction as we can
		 * release the last reference to io_end which may end
		 * up करोing unwritten extent conversion.
		 */
		अगर (handle) अणु
			ext4_put_io_end_defer(mpd.io_submit.io_end);
			ext4_journal_stop(handle);
		पूर्ण अन्यथा
			ext4_put_io_end(mpd.io_submit.io_end);
		mpd.io_submit.io_end = शून्य;

		अगर (ret == -ENOSPC && sbi->s_journal) अणु
			/*
			 * Commit the transaction which would
			 * मुक्त blocks released in the transaction
			 * and try again
			 */
			jbd2_journal_क्रमce_commit_nested(sbi->s_journal);
			ret = 0;
			जारी;
		पूर्ण
		/* Fatal error - ENOMEM, EIO... */
		अगर (ret)
			अवरोध;
	पूर्ण
unplug:
	blk_finish_plug(&plug);
	अगर (!ret && !cycled && wbc->nr_to_ग_लिखो > 0) अणु
		cycled = 1;
		mpd.last_page = ग_लिखोback_index - 1;
		mpd.first_page = 0;
		जाओ retry;
	पूर्ण

	/* Update index */
	अगर (wbc->range_cyclic || (range_whole && wbc->nr_to_ग_लिखो > 0))
		/*
		 * Set the ग_लिखोback_index so that range_cyclic
		 * mode will ग_लिखो it back later
		 */
		mapping->ग_लिखोback_index = mpd.first_page;

out_ग_लिखोpages:
	trace_ext4_ग_लिखोpages_result(inode, wbc, ret,
				     nr_to_ग_लिखो - wbc->nr_to_ग_लिखो);
	percpu_up_पढ़ो(&sbi->s_ग_लिखोpages_rwsem);
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_dax_ग_लिखोpages(काष्ठा address_space *mapping,
			       काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret;
	दीर्घ nr_to_ग_लिखो = wbc->nr_to_ग_लिखो;
	काष्ठा inode *inode = mapping->host;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(mapping->host->i_sb);

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

	percpu_करोwn_पढ़ो(&sbi->s_ग_लिखोpages_rwsem);
	trace_ext4_ग_लिखोpages(inode, wbc);

	ret = dax_ग_लिखोback_mapping_range(mapping, sbi->s_daxdev, wbc);
	trace_ext4_ग_लिखोpages_result(inode, wbc, ret,
				     nr_to_ग_लिखो - wbc->nr_to_ग_लिखो);
	percpu_up_पढ़ो(&sbi->s_ग_लिखोpages_rwsem);
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_nonda_चयन(काष्ठा super_block *sb)
अणु
	s64 मुक्त_clusters, dirty_clusters;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	/*
	 * चयन to non delalloc mode अगर we are running low
	 * on मुक्त block. The मुक्त block accounting via percpu
	 * counters can get slightly wrong with percpu_counter_batch getting
	 * accumulated on each CPU without updating global counters
	 * Delalloc need an accurate मुक्त block accounting. So चयन
	 * to non delalloc when we are near to error range.
	 */
	मुक्त_clusters =
		percpu_counter_पढ़ो_positive(&sbi->s_मुक्तclusters_counter);
	dirty_clusters =
		percpu_counter_पढ़ो_positive(&sbi->s_dirtyclusters_counter);
	/*
	 * Start pushing delalloc when 1/2 of मुक्त blocks are dirty.
	 */
	अगर (dirty_clusters && (मुक्त_clusters < 2 * dirty_clusters))
		try_to_ग_लिखोback_inodes_sb(sb, WB_REASON_FS_FREE_SPACE);

	अगर (2 * मुक्त_clusters < 3 * dirty_clusters ||
	    मुक्त_clusters < (dirty_clusters + EXT4_FREECLUSTERS_WATERMARK)) अणु
		/*
		 * मुक्त block count is less than 150% of dirty blocks
		 * or मुक्त blocks is less than watermark
		 */
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* We always reserve क्रम an inode update; the superblock could be there too */
अटल पूर्णांक ext4_da_ग_लिखो_credits(काष्ठा inode *inode, loff_t pos, अचिन्हित len)
अणु
	अगर (likely(ext4_has_feature_large_file(inode->i_sb)))
		वापस 1;

	अगर (pos + len <= 0x7fffffffULL)
		वापस 1;

	/* We might need to update the superblock to set LARGE_खाता */
	वापस 2;
पूर्ण

अटल पूर्णांक ext4_da_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			       loff_t pos, अचिन्हित len, अचिन्हित flags,
			       काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret, retries = 0;
	काष्ठा page *page;
	pgoff_t index;
	काष्ठा inode *inode = mapping->host;
	handle_t *handle;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

	index = pos >> PAGE_SHIFT;

	अगर (ext4_nonda_चयन(inode->i_sb) || S_ISLNK(inode->i_mode) ||
	    ext4_verity_in_progress(inode)) अणु
		*fsdata = (व्योम *)FALL_BACK_TO_NONDELALLOC;
		वापस ext4_ग_लिखो_begin(file, mapping, pos,
					len, flags, pagep, fsdata);
	पूर्ण
	*fsdata = (व्योम *)0;
	trace_ext4_da_ग_लिखो_begin(inode, pos, len, flags);

	अगर (ext4_test_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA)) अणु
		ret = ext4_da_ग_लिखो_अंतरभूत_data_begin(mapping, inode,
						      pos, len, flags,
						      pagep, fsdata);
		अगर (ret < 0)
			वापस ret;
		अगर (ret == 1)
			वापस 0;
	पूर्ण

	/*
	 * grab_cache_page_ग_लिखो_begin() can take a दीर्घ समय अगर the
	 * प्रणाली is thrashing due to memory pressure, or अगर the page
	 * is being written back.  So grab it first beक्रमe we start
	 * the transaction handle.  This also allows us to allocate
	 * the page (अगर needed) without using GFP_NOFS.
	 */
retry_grab:
	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;
	unlock_page(page);

	/*
	 * With delayed allocation, we करोn't log the i_disksize update
	 * अगर there is delayed block allocation. But we still need
	 * to journalling the i_disksize update अगर ग_लिखोs to the end
	 * of file which has an alपढ़ोy mapped buffer.
	 */
retry_journal:
	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE,
				ext4_da_ग_लिखो_credits(inode, pos, len));
	अगर (IS_ERR(handle)) अणु
		put_page(page);
		वापस PTR_ERR(handle);
	पूर्ण

	lock_page(page);
	अगर (page->mapping != mapping) अणु
		/* The page got truncated from under us */
		unlock_page(page);
		put_page(page);
		ext4_journal_stop(handle);
		जाओ retry_grab;
	पूर्ण
	/* In हाल ग_लिखोback began जबतक the page was unlocked */
	रुको_क्रम_stable_page(page);

#अगर_घोषित CONFIG_FS_ENCRYPTION
	ret = ext4_block_ग_लिखो_begin(page, pos, len,
				     ext4_da_get_block_prep);
#अन्यथा
	ret = __block_ग_लिखो_begin(page, pos, len, ext4_da_get_block_prep);
#पूर्ण_अगर
	अगर (ret < 0) अणु
		unlock_page(page);
		ext4_journal_stop(handle);
		/*
		 * block_ग_लिखो_begin may have instantiated a few blocks
		 * outside i_size.  Trim these off again. Don't need
		 * i_size_पढ़ो because we hold i_mutex.
		 */
		अगर (pos + len > inode->i_size)
			ext4_truncate_failed_ग_लिखो(inode);

		अगर (ret == -ENOSPC &&
		    ext4_should_retry_alloc(inode->i_sb, &retries))
			जाओ retry_journal;

		put_page(page);
		वापस ret;
	पूर्ण

	*pagep = page;
	वापस ret;
पूर्ण

/*
 * Check अगर we should update i_disksize
 * when ग_लिखो to the end of file but not require block allocation
 */
अटल पूर्णांक ext4_da_should_update_i_disksize(काष्ठा page *page,
					    अचिन्हित दीर्घ offset)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा inode *inode = page->mapping->host;
	अचिन्हित पूर्णांक idx;
	पूर्णांक i;

	bh = page_buffers(page);
	idx = offset >> inode->i_blkbits;

	क्रम (i = 0; i < idx; i++)
		bh = bh->b_this_page;

	अगर (!buffer_mapped(bh) || (buffer_delay(bh)) || buffer_unwritten(bh))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक ext4_da_ग_लिखो_end(काष्ठा file *file,
			     काष्ठा address_space *mapping,
			     loff_t pos, अचिन्हित len, अचिन्हित copied,
			     काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	पूर्णांक ret = 0, ret2;
	handle_t *handle = ext4_journal_current_handle();
	loff_t new_i_size;
	अचिन्हित दीर्घ start, end;
	पूर्णांक ग_लिखो_mode = (पूर्णांक)(अचिन्हित दीर्घ)fsdata;

	अगर (ग_लिखो_mode == FALL_BACK_TO_NONDELALLOC)
		वापस ext4_ग_लिखो_end(file, mapping, pos,
				      len, copied, page, fsdata);

	trace_ext4_da_ग_लिखो_end(inode, pos, len, copied);
	start = pos & (PAGE_SIZE - 1);
	end = start + copied - 1;

	/*
	 * generic_ग_लिखो_end() will run mark_inode_dirty() अगर i_size
	 * changes.  So let's piggyback the i_disksize mark_inode_dirty
	 * पूर्णांकo that.
	 */
	new_i_size = pos + copied;
	अगर (copied && new_i_size > EXT4_I(inode)->i_disksize) अणु
		अगर (ext4_has_अंतरभूत_data(inode) ||
		    ext4_da_should_update_i_disksize(page, end)) अणु
			ext4_update_i_disksize(inode, new_i_size);
			/* We need to mark inode dirty even अगर
			 * new_i_size is less that inode->i_size
			 * bu greater than i_disksize.(hपूर्णांक delalloc)
			 */
			ret = ext4_mark_inode_dirty(handle, inode);
		पूर्ण
	पूर्ण

	अगर (ग_लिखो_mode != CONVERT_INLINE_DATA &&
	    ext4_test_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA) &&
	    ext4_has_अंतरभूत_data(inode))
		ret2 = ext4_da_ग_लिखो_अंतरभूत_data_end(inode, pos, len, copied,
						     page);
	अन्यथा
		ret2 = generic_ग_लिखो_end(file, mapping, pos, len, copied,
							page, fsdata);

	copied = ret2;
	अगर (ret2 < 0)
		ret = ret2;
	ret2 = ext4_journal_stop(handle);
	अगर (unlikely(ret2 && !ret))
		ret = ret2;

	वापस ret ? ret : copied;
पूर्ण

/*
 * Force all delayed allocation blocks to be allocated क्रम a given inode.
 */
पूर्णांक ext4_alloc_da_blocks(काष्ठा inode *inode)
अणु
	trace_ext4_alloc_da_blocks(inode);

	अगर (!EXT4_I(inode)->i_reserved_data_blocks)
		वापस 0;

	/*
	 * We करो something simple क्रम now.  The filemap_flush() will
	 * also start triggering a ग_लिखो of the data blocks, which is
	 * not strictly speaking necessary (and क्रम users of
	 * laptop_mode, not even desirable).  However, to करो otherwise
	 * would require replicating code paths in:
	 *
	 * ext4_ग_लिखोpages() ->
	 *    ग_लिखो_cache_pages() ---> (via passed in callback function)
	 *        __mpage_da_ग_लिखोpage() -->
	 *           mpage_add_bh_to_extent()
	 *           mpage_da_map_blocks()
	 *
	 * The problem is that ग_लिखो_cache_pages(), located in
	 * mm/page-ग_लिखोback.c, marks pages clean in preparation क्रम
	 * करोing I/O, which is not desirable अगर we're not planning on
	 * करोing I/O at all.
	 *
	 * We could call ग_लिखो_cache_pages(), and then redirty all of
	 * the pages by calling redirty_page_क्रम_ग_लिखोpage() but that
	 * would be ugly in the extreme.  So instead we would need to
	 * replicate parts of the code in the above functions,
	 * simplअगरying them because we wouldn't actually पूर्णांकend to
	 * ग_लिखो out the pages, but rather only collect contiguous
	 * logical block extents, call the multi-block allocator, and
	 * then update the buffer heads with the block allocations.
	 *
	 * For now, though, we'll cheat by calling filemap_flush(),
	 * which will map the blocks, and start the I/O, but not
	 * actually रुको क्रम the I/O to complete.
	 */
	वापस filemap_flush(inode->i_mapping);
पूर्ण

/*
 * bmap() is special.  It माला_लो used by applications such as lilo and by
 * the swapper to find the on-disk block of a specअगरic piece of data.
 *
 * Naturally, this is dangerous अगर the block concerned is still in the
 * journal.  If somebody makes a swapfile on an ext4 data-journaling
 * fileप्रणाली and enables swap, then they may get a nasty shock when the
 * data getting swapped to that swapfile suddenly माला_लो overwritten by
 * the original zero's written out previously to the journal and
 * aरुकोing ग_लिखोback in the kernel's buffer cache.
 *
 * So, अगर we see any bmap calls here on a modअगरied, data-journaled file,
 * take extra steps to flush any blocks which might be in the cache.
 */
अटल sector_t ext4_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	काष्ठा inode *inode = mapping->host;
	journal_t *journal;
	पूर्णांक err;

	/*
	 * We can get here क्रम an अंतरभूत file via the FIBMAP ioctl
	 */
	अगर (ext4_has_अंतरभूत_data(inode))
		वापस 0;

	अगर (mapping_tagged(mapping, PAGECACHE_TAG_सूचीTY) &&
			test_opt(inode->i_sb, DELALLOC)) अणु
		/*
		 * With delalloc we want to sync the file
		 * so that we can make sure we allocate
		 * blocks क्रम file
		 */
		filemap_ग_लिखो_and_रुको(mapping);
	पूर्ण

	अगर (EXT4_JOURNAL(inode) &&
	    ext4_test_inode_state(inode, EXT4_STATE_JDATA)) अणु
		/*
		 * This is a REALLY heavyweight approach, but the use of
		 * bmap on dirty files is expected to be extremely rare:
		 * only अगर we run lilo or swapon on a freshly made file
		 * करो we expect this to happen.
		 *
		 * (bmap requires CAP_SYS_RAWIO so this करोes not
		 * represent an unprivileged user DOS attack --- we'd be
		 * in trouble अगर mortal users could trigger this path at
		 * will.)
		 *
		 * NB. EXT4_STATE_JDATA is not set on files other than
		 * regular files.  If somebody wants to bmap a directory
		 * or symlink and माला_लो confused because the buffer
		 * hasn't yet been flushed to disk, they deserve
		 * everything they get.
		 */

		ext4_clear_inode_state(inode, EXT4_STATE_JDATA);
		journal = EXT4_JOURNAL(inode);
		jbd2_journal_lock_updates(journal);
		err = jbd2_journal_flush(journal);
		jbd2_journal_unlock_updates(journal);

		अगर (err)
			वापस 0;
	पूर्ण

	वापस iomap_bmap(mapping, block, &ext4_iomap_ops);
पूर्ण

अटल पूर्णांक ext4_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	पूर्णांक ret = -EAGAIN;
	काष्ठा inode *inode = page->mapping->host;

	trace_ext4_पढ़ोpage(page);

	अगर (ext4_has_अंतरभूत_data(inode))
		ret = ext4_पढ़ोpage_अंतरभूत(inode, page);

	अगर (ret == -EAGAIN)
		वापस ext4_mpage_पढ़ोpages(inode, शून्य, page);

	वापस ret;
पूर्ण

अटल व्योम ext4_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	काष्ठा inode *inode = rac->mapping->host;

	/* If the file has अंतरभूत data, no need to करो पढ़ोahead. */
	अगर (ext4_has_अंतरभूत_data(inode))
		वापस;

	ext4_mpage_पढ़ोpages(inode, rac, शून्य);
पूर्ण

अटल व्योम ext4_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				अचिन्हित पूर्णांक length)
अणु
	trace_ext4_invalidatepage(page, offset, length);

	/* No journalling happens on data buffers when this function is used */
	WARN_ON(page_has_buffers(page) && buffer_jbd(page_buffers(page)));

	block_invalidatepage(page, offset, length);
पूर्ण

अटल पूर्णांक __ext4_journalled_invalidatepage(काष्ठा page *page,
					    अचिन्हित पूर्णांक offset,
					    अचिन्हित पूर्णांक length)
अणु
	journal_t *journal = EXT4_JOURNAL(page->mapping->host);

	trace_ext4_journalled_invalidatepage(page, offset, length);

	/*
	 * If it's a full truncate we just क्रमget about the pending dirtying
	 */
	अगर (offset == 0 && length == PAGE_SIZE)
		ClearPageChecked(page);

	वापस jbd2_journal_invalidatepage(journal, page, offset, length);
पूर्ण

/* Wrapper क्रम aops... */
अटल व्योम ext4_journalled_invalidatepage(काष्ठा page *page,
					   अचिन्हित पूर्णांक offset,
					   अचिन्हित पूर्णांक length)
अणु
	WARN_ON(__ext4_journalled_invalidatepage(page, offset, length) < 0);
पूर्ण

अटल पूर्णांक ext4_releasepage(काष्ठा page *page, gfp_t रुको)
अणु
	journal_t *journal = EXT4_JOURNAL(page->mapping->host);

	trace_ext4_releasepage(page);

	/* Page has dirty journalled data -> cannot release */
	अगर (PageChecked(page))
		वापस 0;
	अगर (journal)
		वापस jbd2_journal_try_to_मुक्त_buffers(journal, page);
	अन्यथा
		वापस try_to_मुक्त_buffers(page);
पूर्ण

अटल bool ext4_inode_datasync_dirty(काष्ठा inode *inode)
अणु
	journal_t *journal = EXT4_SB(inode->i_sb)->s_journal;

	अगर (journal) अणु
		अगर (jbd2_transaction_committed(journal,
			EXT4_I(inode)->i_datasync_tid))
			वापस false;
		अगर (test_opt2(inode->i_sb, JOURNAL_FAST_COMMIT))
			वापस !list_empty(&EXT4_I(inode)->i_fc_list);
		वापस true;
	पूर्ण

	/* Any metadata buffers to ग_लिखो? */
	अगर (!list_empty(&inode->i_mapping->निजी_list))
		वापस true;
	वापस inode->i_state & I_सूचीTY_DATASYNC;
पूर्ण

अटल व्योम ext4_set_iomap(काष्ठा inode *inode, काष्ठा iomap *iomap,
			   काष्ठा ext4_map_blocks *map, loff_t offset,
			   loff_t length)
अणु
	u8 blkbits = inode->i_blkbits;

	/*
	 * Writes that span खातापूर्ण might trigger an I/O size update on completion,
	 * so consider them to be dirty क्रम the purpose of O_DSYNC, even अगर
	 * there is no other metadata changes being made or are pending.
	 */
	iomap->flags = 0;
	अगर (ext4_inode_datasync_dirty(inode) ||
	    offset + length > i_size_पढ़ो(inode))
		iomap->flags |= IOMAP_F_सूचीTY;

	अगर (map->m_flags & EXT4_MAP_NEW)
		iomap->flags |= IOMAP_F_NEW;

	iomap->bdev = inode->i_sb->s_bdev;
	iomap->dax_dev = EXT4_SB(inode->i_sb)->s_daxdev;
	iomap->offset = (u64) map->m_lblk << blkbits;
	iomap->length = (u64) map->m_len << blkbits;

	अगर ((map->m_flags & EXT4_MAP_MAPPED) &&
	    !ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		iomap->flags |= IOMAP_F_MERGED;

	/*
	 * Flags passed to ext4_map_blocks() क्रम direct I/O ग_लिखोs can result
	 * in m_flags having both EXT4_MAP_MAPPED and EXT4_MAP_UNWRITTEN bits
	 * set. In order क्रम any allocated unwritten extents to be converted
	 * पूर्णांकo written extents correctly within the ->end_io() handler, we
	 * need to ensure that the iomap->type is set appropriately. Hence, the
	 * reason why we need to check whether the EXT4_MAP_UNWRITTEN bit has
	 * been set first.
	 */
	अगर (map->m_flags & EXT4_MAP_UNWRITTEN) अणु
		iomap->type = IOMAP_UNWRITTEN;
		iomap->addr = (u64) map->m_pblk << blkbits;
	पूर्ण अन्यथा अगर (map->m_flags & EXT4_MAP_MAPPED) अणु
		iomap->type = IOMAP_MAPPED;
		iomap->addr = (u64) map->m_pblk << blkbits;
	पूर्ण अन्यथा अणु
		iomap->type = IOMAP_HOLE;
		iomap->addr = IOMAP_शून्य_ADDR;
	पूर्ण
पूर्ण

अटल पूर्णांक ext4_iomap_alloc(काष्ठा inode *inode, काष्ठा ext4_map_blocks *map,
			    अचिन्हित पूर्णांक flags)
अणु
	handle_t *handle;
	u8 blkbits = inode->i_blkbits;
	पूर्णांक ret, dio_credits, m_flags = 0, retries = 0;

	/*
	 * Trim the mapping request to the maximum value that we can map at
	 * once क्रम direct I/O.
	 */
	अगर (map->m_len > DIO_MAX_BLOCKS)
		map->m_len = DIO_MAX_BLOCKS;
	dio_credits = ext4_chunk_trans_blocks(inode, map->m_len);

retry:
	/*
	 * Either we allocate blocks and then करोn't get an unwritten extent, so
	 * in that हाल we have reserved enough credits. Or, the blocks are
	 * alपढ़ोy allocated and unwritten. In that हाल, the extent conversion
	 * fits पूर्णांकo the credits as well.
	 */
	handle = ext4_journal_start(inode, EXT4_HT_MAP_BLOCKS, dio_credits);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	/*
	 * DAX and direct I/O are the only two operations that are currently
	 * supported with IOMAP_WRITE.
	 */
	WARN_ON(!IS_DAX(inode) && !(flags & IOMAP_सूचीECT));
	अगर (IS_DAX(inode))
		m_flags = EXT4_GET_BLOCKS_CREATE_ZERO;
	/*
	 * We use i_size instead of i_disksize here because delalloc ग_लिखोback
	 * can complete at any poपूर्णांक during the I/O and subsequently push the
	 * i_disksize out to i_size. This could be beyond where direct I/O is
	 * happening and thus expose allocated blocks to direct I/O पढ़ोs.
	 */
	अन्यथा अगर ((map->m_lblk * (1 << blkbits)) >= i_size_पढ़ो(inode))
		m_flags = EXT4_GET_BLOCKS_CREATE;
	अन्यथा अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		m_flags = EXT4_GET_BLOCKS_IO_CREATE_EXT;

	ret = ext4_map_blocks(handle, inode, map, m_flags);

	/*
	 * We cannot fill holes in indirect tree based inodes as that could
	 * expose stale data in the हाल of a crash. Use the magic error code
	 * to fallback to buffered I/O.
	 */
	अगर (!m_flags && !ret)
		ret = -ENOTBLK;

	ext4_journal_stop(handle);
	अगर (ret == -ENOSPC && ext4_should_retry_alloc(inode->i_sb, &retries))
		जाओ retry;

	वापस ret;
पूर्ण


अटल पूर्णांक ext4_iomap_begin(काष्ठा inode *inode, loff_t offset, loff_t length,
		अचिन्हित flags, काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	पूर्णांक ret;
	काष्ठा ext4_map_blocks map;
	u8 blkbits = inode->i_blkbits;

	अगर ((offset >> blkbits) > EXT4_MAX_LOGICAL_BLOCK)
		वापस -EINVAL;

	अगर (WARN_ON_ONCE(ext4_has_अंतरभूत_data(inode)))
		वापस -दुस्फल;

	/*
	 * Calculate the first and last logical blocks respectively.
	 */
	map.m_lblk = offset >> blkbits;
	map.m_len = min_t(loff_t, (offset + length - 1) >> blkbits,
			  EXT4_MAX_LOGICAL_BLOCK) - map.m_lblk + 1;

	अगर (flags & IOMAP_WRITE) अणु
		/*
		 * We check here अगर the blocks are alपढ़ोy allocated, then we
		 * करोn't need to start a journal txn and we can directly वापस
		 * the mapping inक्रमmation. This could boost perक्रमmance
		 * especially in multi-thपढ़ोed overग_लिखो requests.
		 */
		अगर (offset + length <= i_size_पढ़ो(inode)) अणु
			ret = ext4_map_blocks(शून्य, inode, &map, 0);
			अगर (ret > 0 && (map.m_flags & EXT4_MAP_MAPPED))
				जाओ out;
		पूर्ण
		ret = ext4_iomap_alloc(inode, &map, flags);
	पूर्ण अन्यथा अणु
		ret = ext4_map_blocks(शून्य, inode, &map, 0);
	पूर्ण

	अगर (ret < 0)
		वापस ret;
out:
	ext4_set_iomap(inode, iomap, &map, offset, length);

	वापस 0;
पूर्ण

अटल पूर्णांक ext4_iomap_overग_लिखो_begin(काष्ठा inode *inode, loff_t offset,
		loff_t length, अचिन्हित flags, काष्ठा iomap *iomap,
		काष्ठा iomap *srcmap)
अणु
	पूर्णांक ret;

	/*
	 * Even क्रम ग_लिखोs we करोn't need to allocate blocks, so just pretend
	 * we are पढ़ोing to save overhead of starting a transaction.
	 */
	flags &= ~IOMAP_WRITE;
	ret = ext4_iomap_begin(inode, offset, length, flags, iomap, srcmap);
	WARN_ON_ONCE(iomap->type != IOMAP_MAPPED);
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_iomap_end(काष्ठा inode *inode, loff_t offset, loff_t length,
			  sमाप_प्रकार written, अचिन्हित flags, काष्ठा iomap *iomap)
अणु
	/*
	 * Check to see whether an error occurred जबतक writing out the data to
	 * the allocated blocks. If so, वापस the magic error code so that we
	 * fallback to buffered I/O and attempt to complete the reमुख्यder of
	 * the I/O. Any blocks that may have been allocated in preparation क्रम
	 * the direct I/O will be reused during buffered I/O.
	 */
	अगर (flags & (IOMAP_WRITE | IOMAP_सूचीECT) && written == 0)
		वापस -ENOTBLK;

	वापस 0;
पूर्ण

स्थिर काष्ठा iomap_ops ext4_iomap_ops = अणु
	.iomap_begin		= ext4_iomap_begin,
	.iomap_end		= ext4_iomap_end,
पूर्ण;

स्थिर काष्ठा iomap_ops ext4_iomap_overग_लिखो_ops = अणु
	.iomap_begin		= ext4_iomap_overग_लिखो_begin,
	.iomap_end		= ext4_iomap_end,
पूर्ण;

अटल bool ext4_iomap_is_delalloc(काष्ठा inode *inode,
				   काष्ठा ext4_map_blocks *map)
अणु
	काष्ठा extent_status es;
	ext4_lblk_t offset = 0, end = map->m_lblk + map->m_len - 1;

	ext4_es_find_extent_range(inode, &ext4_es_is_delayed,
				  map->m_lblk, end, &es);

	अगर (!es.es_len || es.es_lblk > end)
		वापस false;

	अगर (es.es_lblk > map->m_lblk) अणु
		map->m_len = es.es_lblk - map->m_lblk;
		वापस false;
	पूर्ण

	offset = map->m_lblk - es.es_lblk;
	map->m_len = es.es_len - offset;

	वापस true;
पूर्ण

अटल पूर्णांक ext4_iomap_begin_report(काष्ठा inode *inode, loff_t offset,
				   loff_t length, अचिन्हित पूर्णांक flags,
				   काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	पूर्णांक ret;
	bool delalloc = false;
	काष्ठा ext4_map_blocks map;
	u8 blkbits = inode->i_blkbits;

	अगर ((offset >> blkbits) > EXT4_MAX_LOGICAL_BLOCK)
		वापस -EINVAL;

	अगर (ext4_has_अंतरभूत_data(inode)) अणु
		ret = ext4_अंतरभूत_data_iomap(inode, iomap);
		अगर (ret != -EAGAIN) अणु
			अगर (ret == 0 && offset >= iomap->length)
				ret = -ENOENT;
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Calculate the first and last logical block respectively.
	 */
	map.m_lblk = offset >> blkbits;
	map.m_len = min_t(loff_t, (offset + length - 1) >> blkbits,
			  EXT4_MAX_LOGICAL_BLOCK) - map.m_lblk + 1;

	/*
	 * Fiemap callers may call क्रम offset beyond s_biपंचांगap_maxbytes.
	 * So handle it here itself instead of querying ext4_map_blocks().
	 * Since ext4_map_blocks() will warn about it and will वापस
	 * -EIO error.
	 */
	अगर (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))) अणु
		काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

		अगर (offset >= sbi->s_biपंचांगap_maxbytes) अणु
			map.m_flags = 0;
			जाओ set_iomap;
		पूर्ण
	पूर्ण

	ret = ext4_map_blocks(शून्य, inode, &map, 0);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == 0)
		delalloc = ext4_iomap_is_delalloc(inode, &map);

set_iomap:
	ext4_set_iomap(inode, iomap, &map, offset, length);
	अगर (delalloc && iomap->type == IOMAP_HOLE)
		iomap->type = IOMAP_DELALLOC;

	वापस 0;
पूर्ण

स्थिर काष्ठा iomap_ops ext4_iomap_report_ops = अणु
	.iomap_begin = ext4_iomap_begin_report,
पूर्ण;

/*
 * Pages can be marked dirty completely asynchronously from ext4's journalling
 * activity.  By filemap_sync_pte(), try_to_unmap_one(), etc.  We cannot करो
 * much here because ->set_page_dirty is called under VFS locks.  The page is
 * not necessarily locked.
 *
 * We cannot just dirty the page and leave attached buffers clean, because the
 * buffers' dirty state is "definitive".  We cannot just set the buffers dirty
 * or jbddirty because all the journalling code will explode.
 *
 * So what we करो is to mark the page "pending dirty" and next समय ग_लिखोpage
 * is called, propagate that पूर्णांकo the buffers appropriately.
 */
अटल पूर्णांक ext4_journalled_set_page_dirty(काष्ठा page *page)
अणु
	SetPageChecked(page);
	वापस __set_page_dirty_nobuffers(page);
पूर्ण

अटल पूर्णांक ext4_set_page_dirty(काष्ठा page *page)
अणु
	WARN_ON_ONCE(!PageLocked(page) && !PageDirty(page));
	WARN_ON_ONCE(!page_has_buffers(page));
	वापस __set_page_dirty_buffers(page);
पूर्ण

अटल पूर्णांक ext4_iomap_swap_activate(काष्ठा swap_info_काष्ठा *sis,
				    काष्ठा file *file, sector_t *span)
अणु
	वापस iomap_swapfile_activate(sis, file, span,
				       &ext4_iomap_report_ops);
पूर्ण

अटल स्थिर काष्ठा address_space_operations ext4_aops = अणु
	.पढ़ोpage		= ext4_पढ़ोpage,
	.पढ़ोahead		= ext4_पढ़ोahead,
	.ग_लिखोpage		= ext4_ग_लिखोpage,
	.ग_लिखोpages		= ext4_ग_लिखोpages,
	.ग_लिखो_begin		= ext4_ग_लिखो_begin,
	.ग_लिखो_end		= ext4_ग_लिखो_end,
	.set_page_dirty		= ext4_set_page_dirty,
	.bmap			= ext4_bmap,
	.invalidatepage		= ext4_invalidatepage,
	.releasepage		= ext4_releasepage,
	.direct_IO		= noop_direct_IO,
	.migratepage		= buffer_migrate_page,
	.is_partially_uptodate  = block_is_partially_uptodate,
	.error_हटाओ_page	= generic_error_हटाओ_page,
	.swap_activate		= ext4_iomap_swap_activate,
पूर्ण;

अटल स्थिर काष्ठा address_space_operations ext4_journalled_aops = अणु
	.पढ़ोpage		= ext4_पढ़ोpage,
	.पढ़ोahead		= ext4_पढ़ोahead,
	.ग_लिखोpage		= ext4_ग_लिखोpage,
	.ग_लिखोpages		= ext4_ग_लिखोpages,
	.ग_लिखो_begin		= ext4_ग_लिखो_begin,
	.ग_लिखो_end		= ext4_journalled_ग_लिखो_end,
	.set_page_dirty		= ext4_journalled_set_page_dirty,
	.bmap			= ext4_bmap,
	.invalidatepage		= ext4_journalled_invalidatepage,
	.releasepage		= ext4_releasepage,
	.direct_IO		= noop_direct_IO,
	.is_partially_uptodate  = block_is_partially_uptodate,
	.error_हटाओ_page	= generic_error_हटाओ_page,
	.swap_activate		= ext4_iomap_swap_activate,
पूर्ण;

अटल स्थिर काष्ठा address_space_operations ext4_da_aops = अणु
	.पढ़ोpage		= ext4_पढ़ोpage,
	.पढ़ोahead		= ext4_पढ़ोahead,
	.ग_लिखोpage		= ext4_ग_लिखोpage,
	.ग_लिखोpages		= ext4_ग_लिखोpages,
	.ग_लिखो_begin		= ext4_da_ग_लिखो_begin,
	.ग_लिखो_end		= ext4_da_ग_लिखो_end,
	.set_page_dirty		= ext4_set_page_dirty,
	.bmap			= ext4_bmap,
	.invalidatepage		= ext4_invalidatepage,
	.releasepage		= ext4_releasepage,
	.direct_IO		= noop_direct_IO,
	.migratepage		= buffer_migrate_page,
	.is_partially_uptodate  = block_is_partially_uptodate,
	.error_हटाओ_page	= generic_error_हटाओ_page,
	.swap_activate		= ext4_iomap_swap_activate,
पूर्ण;

अटल स्थिर काष्ठा address_space_operations ext4_dax_aops = अणु
	.ग_लिखोpages		= ext4_dax_ग_लिखोpages,
	.direct_IO		= noop_direct_IO,
	.set_page_dirty		= noop_set_page_dirty,
	.bmap			= ext4_bmap,
	.invalidatepage		= noop_invalidatepage,
	.swap_activate		= ext4_iomap_swap_activate,
पूर्ण;

व्योम ext4_set_aops(काष्ठा inode *inode)
अणु
	चयन (ext4_inode_journal_mode(inode)) अणु
	हाल EXT4_INODE_ORDERED_DATA_MODE:
	हाल EXT4_INODE_WRITEBACK_DATA_MODE:
		अवरोध;
	हाल EXT4_INODE_JOURNAL_DATA_MODE:
		inode->i_mapping->a_ops = &ext4_journalled_aops;
		वापस;
	शेष:
		BUG();
	पूर्ण
	अगर (IS_DAX(inode))
		inode->i_mapping->a_ops = &ext4_dax_aops;
	अन्यथा अगर (test_opt(inode->i_sb, DELALLOC))
		inode->i_mapping->a_ops = &ext4_da_aops;
	अन्यथा
		inode->i_mapping->a_ops = &ext4_aops;
पूर्ण

अटल पूर्णांक __ext4_block_zero_page_range(handle_t *handle,
		काष्ठा address_space *mapping, loff_t from, loff_t length)
अणु
	ext4_fsblk_t index = from >> PAGE_SHIFT;
	अचिन्हित offset = from & (PAGE_SIZE-1);
	अचिन्हित blocksize, pos;
	ext4_lblk_t iblock;
	काष्ठा inode *inode = mapping->host;
	काष्ठा buffer_head *bh;
	काष्ठा page *page;
	पूर्णांक err = 0;

	page = find_or_create_page(mapping, from >> PAGE_SHIFT,
				   mapping_gfp_स्थिरraपूर्णांक(mapping, ~__GFP_FS));
	अगर (!page)
		वापस -ENOMEM;

	blocksize = inode->i_sb->s_blocksize;

	iblock = index << (PAGE_SHIFT - inode->i_sb->s_blocksize_bits);

	अगर (!page_has_buffers(page))
		create_empty_buffers(page, blocksize, 0);

	/* Find the buffer that contains "offset" */
	bh = page_buffers(page);
	pos = blocksize;
	जबतक (offset >= pos) अणु
		bh = bh->b_this_page;
		iblock++;
		pos += blocksize;
	पूर्ण
	अगर (buffer_मुक्तd(bh)) अणु
		BUFFER_TRACE(bh, "freed: skip");
		जाओ unlock;
	पूर्ण
	अगर (!buffer_mapped(bh)) अणु
		BUFFER_TRACE(bh, "unmapped");
		ext4_get_block(inode, iblock, bh, 0);
		/* unmapped? It's a hole - nothing to करो */
		अगर (!buffer_mapped(bh)) अणु
			BUFFER_TRACE(bh, "still unmapped");
			जाओ unlock;
		पूर्ण
	पूर्ण

	/* Ok, it's mapped. Make sure it's up-to-date */
	अगर (PageUptodate(page))
		set_buffer_uptodate(bh);

	अगर (!buffer_uptodate(bh)) अणु
		err = ext4_पढ़ो_bh_lock(bh, 0, true);
		अगर (err)
			जाओ unlock;
		अगर (fscrypt_inode_uses_fs_layer_crypto(inode)) अणु
			/* We expect the key to be set. */
			BUG_ON(!fscrypt_has_encryption_key(inode));
			err = fscrypt_decrypt_pagecache_blocks(page, blocksize,
							       bh_offset(bh));
			अगर (err) अणु
				clear_buffer_uptodate(bh);
				जाओ unlock;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (ext4_should_journal_data(inode)) अणु
		BUFFER_TRACE(bh, "get write access");
		err = ext4_journal_get_ग_लिखो_access(handle, bh);
		अगर (err)
			जाओ unlock;
	पूर्ण
	zero_user(page, offset, length);
	BUFFER_TRACE(bh, "zeroed end of block");

	अगर (ext4_should_journal_data(inode)) अणु
		err = ext4_handle_dirty_metadata(handle, inode, bh);
	पूर्ण अन्यथा अणु
		err = 0;
		mark_buffer_dirty(bh);
		अगर (ext4_should_order_data(inode))
			err = ext4_jbd2_inode_add_ग_लिखो(handle, inode, from,
					length);
	पूर्ण

unlock:
	unlock_page(page);
	put_page(page);
	वापस err;
पूर्ण

/*
 * ext4_block_zero_page_range() zeros out a mapping of length 'length'
 * starting from file offset 'from'.  The range to be zero'd must
 * be contained with in one block.  If the specअगरied range exceeds
 * the end of the block it will be लघुened to end of the block
 * that corresponds to 'from'
 */
अटल पूर्णांक ext4_block_zero_page_range(handle_t *handle,
		काष्ठा address_space *mapping, loff_t from, loff_t length)
अणु
	काष्ठा inode *inode = mapping->host;
	अचिन्हित offset = from & (PAGE_SIZE-1);
	अचिन्हित blocksize = inode->i_sb->s_blocksize;
	अचिन्हित max = blocksize - (offset & (blocksize - 1));

	/*
	 * correct length अगर it करोes not fall between
	 * 'from' and the end of the block
	 */
	अगर (length > max || length < 0)
		length = max;

	अगर (IS_DAX(inode)) अणु
		वापस iomap_zero_range(inode, from, length, शून्य,
					&ext4_iomap_ops);
	पूर्ण
	वापस __ext4_block_zero_page_range(handle, mapping, from, length);
पूर्ण

/*
 * ext4_block_truncate_page() zeroes out a mapping from file offset `from'
 * up to the end of the block which corresponds to `from'.
 * This required during truncate. We need to physically zero the tail end
 * of that block so it करोesn't yield old data अगर the file is later grown.
 */
अटल पूर्णांक ext4_block_truncate_page(handle_t *handle,
		काष्ठा address_space *mapping, loff_t from)
अणु
	अचिन्हित offset = from & (PAGE_SIZE-1);
	अचिन्हित length;
	अचिन्हित blocksize;
	काष्ठा inode *inode = mapping->host;

	/* If we are processing an encrypted inode during orphan list handling */
	अगर (IS_ENCRYPTED(inode) && !fscrypt_has_encryption_key(inode))
		वापस 0;

	blocksize = inode->i_sb->s_blocksize;
	length = blocksize - (offset & (blocksize - 1));

	वापस ext4_block_zero_page_range(handle, mapping, from, length);
पूर्ण

पूर्णांक ext4_zero_partial_blocks(handle_t *handle, काष्ठा inode *inode,
			     loff_t lstart, loff_t length)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा address_space *mapping = inode->i_mapping;
	अचिन्हित partial_start, partial_end;
	ext4_fsblk_t start, end;
	loff_t byte_end = (lstart + length - 1);
	पूर्णांक err = 0;

	partial_start = lstart & (sb->s_blocksize - 1);
	partial_end = byte_end & (sb->s_blocksize - 1);

	start = lstart >> sb->s_blocksize_bits;
	end = byte_end >> sb->s_blocksize_bits;

	/* Handle partial zero within the single block */
	अगर (start == end &&
	    (partial_start || (partial_end != sb->s_blocksize - 1))) अणु
		err = ext4_block_zero_page_range(handle, mapping,
						 lstart, length);
		वापस err;
	पूर्ण
	/* Handle partial zero out on the start of the range */
	अगर (partial_start) अणु
		err = ext4_block_zero_page_range(handle, mapping,
						 lstart, sb->s_blocksize);
		अगर (err)
			वापस err;
	पूर्ण
	/* Handle partial zero out on the end of the range */
	अगर (partial_end != sb->s_blocksize - 1)
		err = ext4_block_zero_page_range(handle, mapping,
						 byte_end - partial_end,
						 partial_end + 1);
	वापस err;
पूर्ण

पूर्णांक ext4_can_truncate(काष्ठा inode *inode)
अणु
	अगर (S_ISREG(inode->i_mode))
		वापस 1;
	अगर (S_ISसूची(inode->i_mode))
		वापस 1;
	अगर (S_ISLNK(inode->i_mode))
		वापस !ext4_inode_is_fast_symlink(inode);
	वापस 0;
पूर्ण

/*
 * We have to make sure i_disksize माला_लो properly updated beक्रमe we truncate
 * page cache due to hole punching or zero range. Otherwise i_disksize update
 * can get lost as it may have been postponed to submission of ग_लिखोback but
 * that will never happen after we truncate page cache.
 */
पूर्णांक ext4_update_disksize_beक्रमe_punch(काष्ठा inode *inode, loff_t offset,
				      loff_t len)
अणु
	handle_t *handle;
	पूर्णांक ret;

	loff_t size = i_size_पढ़ो(inode);

	WARN_ON(!inode_is_locked(inode));
	अगर (offset > size || offset + len < size)
		वापस 0;

	अगर (EXT4_I(inode)->i_disksize >= size)
		वापस 0;

	handle = ext4_journal_start(inode, EXT4_HT_MISC, 1);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);
	ext4_update_i_disksize(inode, size);
	ret = ext4_mark_inode_dirty(handle, inode);
	ext4_journal_stop(handle);

	वापस ret;
पूर्ण

अटल व्योम ext4_रुको_dax_page(काष्ठा ext4_inode_info *ei)
अणु
	up_ग_लिखो(&ei->i_mmap_sem);
	schedule();
	करोwn_ग_लिखो(&ei->i_mmap_sem);
पूर्ण

पूर्णांक ext4_अवरोध_layouts(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा page *page;
	पूर्णांक error;

	अगर (WARN_ON_ONCE(!rwsem_is_locked(&ei->i_mmap_sem)))
		वापस -EINVAL;

	करो अणु
		page = dax_layout_busy_page(inode->i_mapping);
		अगर (!page)
			वापस 0;

		error = ___रुको_var_event(&page->_refcount,
				atomic_पढ़ो(&page->_refcount) == 1,
				TASK_INTERRUPTIBLE, 0, 0,
				ext4_रुको_dax_page(ei));
	पूर्ण जबतक (error == 0);

	वापस error;
पूर्ण

/*
 * ext4_punch_hole: punches a hole in a file by releasing the blocks
 * associated with the given offset and length
 *
 * @inode:  File inode
 * @offset: The offset where the hole will begin
 * @len:    The length of the hole
 *
 * Returns: 0 on success or negative on failure
 */

पूर्णांक ext4_punch_hole(काष्ठा inode *inode, loff_t offset, loff_t length)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	ext4_lblk_t first_block, stop_block;
	काष्ठा address_space *mapping = inode->i_mapping;
	loff_t first_block_offset, last_block_offset;
	handle_t *handle;
	अचिन्हित पूर्णांक credits;
	पूर्णांक ret = 0, ret2 = 0;

	trace_ext4_punch_hole(inode, offset, length, 0);

	ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
	अगर (ext4_has_अंतरभूत_data(inode)) अणु
		करोwn_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
		ret = ext4_convert_अंतरभूत_data(inode);
		up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Write out all dirty pages to aव्योम race conditions
	 * Then release them.
	 */
	अगर (mapping_tagged(mapping, PAGECACHE_TAG_सूचीTY)) अणु
		ret = filemap_ग_लिखो_and_रुको_range(mapping, offset,
						   offset + length - 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	inode_lock(inode);

	/* No need to punch hole beyond i_size */
	अगर (offset >= inode->i_size)
		जाओ out_mutex;

	/*
	 * If the hole extends beyond i_size, set the hole
	 * to end after the page that contains i_size
	 */
	अगर (offset + length > inode->i_size) अणु
		length = inode->i_size +
		   PAGE_SIZE - (inode->i_size & (PAGE_SIZE - 1)) -
		   offset;
	पूर्ण

	अगर (offset & (sb->s_blocksize - 1) ||
	    (offset + length) & (sb->s_blocksize - 1)) अणु
		/*
		 * Attach jinode to inode क्रम jbd2 अगर we करो any zeroing of
		 * partial block
		 */
		ret = ext4_inode_attach_jinode(inode);
		अगर (ret < 0)
			जाओ out_mutex;

	पूर्ण

	/* Wait all existing dio workers, newcomers will block on i_mutex */
	inode_dio_रुको(inode);

	/*
	 * Prevent page faults from reinstantiating pages we have released from
	 * page cache.
	 */
	करोwn_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);

	ret = ext4_अवरोध_layouts(inode);
	अगर (ret)
		जाओ out_dio;

	first_block_offset = round_up(offset, sb->s_blocksize);
	last_block_offset = round_करोwn((offset + length), sb->s_blocksize) - 1;

	/* Now release the pages and zero block aligned part of pages*/
	अगर (last_block_offset > first_block_offset) अणु
		ret = ext4_update_disksize_beक्रमe_punch(inode, offset, length);
		अगर (ret)
			जाओ out_dio;
		truncate_pagecache_range(inode, first_block_offset,
					 last_block_offset);
	पूर्ण

	अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		credits = ext4_ग_लिखोpage_trans_blocks(inode);
	अन्यथा
		credits = ext4_blocks_क्रम_truncate(inode);
	handle = ext4_journal_start(inode, EXT4_HT_TRUNCATE, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		ext4_std_error(sb, ret);
		जाओ out_dio;
	पूर्ण

	ret = ext4_zero_partial_blocks(handle, inode, offset,
				       length);
	अगर (ret)
		जाओ out_stop;

	first_block = (offset + sb->s_blocksize - 1) >>
		EXT4_BLOCK_SIZE_BITS(sb);
	stop_block = (offset + length) >> EXT4_BLOCK_SIZE_BITS(sb);

	/* If there are blocks to हटाओ, करो it */
	अगर (stop_block > first_block) अणु

		करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		ext4_discard_pपुनः_स्मृतिations(inode, 0);

		ret = ext4_es_हटाओ_extent(inode, first_block,
					    stop_block - first_block);
		अगर (ret) अणु
			up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
			जाओ out_stop;
		पूर्ण

		अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
			ret = ext4_ext_हटाओ_space(inode, first_block,
						    stop_block - 1);
		अन्यथा
			ret = ext4_ind_हटाओ_space(handle, inode, first_block,
						    stop_block);

		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	पूर्ण
	ext4_fc_track_range(handle, inode, first_block, stop_block);
	अगर (IS_SYNC(inode))
		ext4_handle_sync(handle);

	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	ret2 = ext4_mark_inode_dirty(handle, inode);
	अगर (unlikely(ret2))
		ret = ret2;
	अगर (ret >= 0)
		ext4_update_inode_fsync_trans(handle, inode, 1);
out_stop:
	ext4_journal_stop(handle);
out_dio:
	up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
out_mutex:
	inode_unlock(inode);
	वापस ret;
पूर्ण

पूर्णांक ext4_inode_attach_jinode(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा jbd2_inode *jinode;

	अगर (ei->jinode || !EXT4_SB(inode->i_sb)->s_journal)
		वापस 0;

	jinode = jbd2_alloc_inode(GFP_KERNEL);
	spin_lock(&inode->i_lock);
	अगर (!ei->jinode) अणु
		अगर (!jinode) अणु
			spin_unlock(&inode->i_lock);
			वापस -ENOMEM;
		पूर्ण
		ei->jinode = jinode;
		jbd2_journal_init_jbd_inode(ei->jinode, inode);
		jinode = शून्य;
	पूर्ण
	spin_unlock(&inode->i_lock);
	अगर (unlikely(jinode != शून्य))
		jbd2_मुक्त_inode(jinode);
	वापस 0;
पूर्ण

/*
 * ext4_truncate()
 *
 * We block out ext4_get_block() block instantiations across the entire
 * transaction, and VFS/VM ensures that ext4_truncate() cannot run
 * simultaneously on behalf of the same inode.
 *
 * As we work through the truncate and commit bits of it to the journal there
 * is one core, guiding principle: the file's tree must always be consistent on
 * disk.  We must be able to restart the truncate after a crash.
 *
 * The file's tree may be transiently inconsistent in memory (although it
 * probably isn't), but whenever we बंद off and commit a journal transaction,
 * the contents of (the fileप्रणाली + the journal) must be consistent and
 * restartable.  It's pretty simple, really: bottom up, right to left (although
 * left-to-right works OK too).
 *
 * Note that at recovery समय, journal replay occurs *beक्रमe* the restart of
 * truncate against the orphan inode list.
 *
 * The committed inode has the new, desired i_size (which is the same as
 * i_disksize in this हाल).  After a crash, ext4_orphan_cleanup() will see
 * that this inode's truncate did not complete and it will again call
 * ext4_truncate() to have another go.  So there will be instantiated blocks
 * to the right of the truncation poपूर्णांक in a crashed ext4 fileप्रणाली.  But
 * that's fine - as दीर्घ as they are linked from the inode, the post-crash
 * ext4_truncate() run will find them and release them.
 */
पूर्णांक ext4_truncate(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	अचिन्हित पूर्णांक credits;
	पूर्णांक err = 0, err2;
	handle_t *handle;
	काष्ठा address_space *mapping = inode->i_mapping;

	/*
	 * There is a possibility that we're either मुक्तing the inode
	 * or it's a completely new inode. In those हालs we might not
	 * have i_mutex locked because it's not necessary.
	 */
	अगर (!(inode->i_state & (I_NEW|I_FREEING)))
		WARN_ON(!inode_is_locked(inode));
	trace_ext4_truncate_enter(inode);

	अगर (!ext4_can_truncate(inode))
		जाओ out_trace;

	अगर (inode->i_size == 0 && !test_opt(inode->i_sb, NO_AUTO_DA_ALLOC))
		ext4_set_inode_state(inode, EXT4_STATE_DA_ALLOC_CLOSE);

	अगर (ext4_has_अंतरभूत_data(inode)) अणु
		पूर्णांक has_अंतरभूत = 1;

		err = ext4_अंतरभूत_data_truncate(inode, &has_अंतरभूत);
		अगर (err || has_अंतरभूत)
			जाओ out_trace;
	पूर्ण

	/* If we zero-out tail of the page, we have to create jinode क्रम jbd2 */
	अगर (inode->i_size & (inode->i_sb->s_blocksize - 1)) अणु
		अगर (ext4_inode_attach_jinode(inode) < 0)
			जाओ out_trace;
	पूर्ण

	अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		credits = ext4_ग_लिखोpage_trans_blocks(inode);
	अन्यथा
		credits = ext4_blocks_क्रम_truncate(inode);

	handle = ext4_journal_start(inode, EXT4_HT_TRUNCATE, credits);
	अगर (IS_ERR(handle)) अणु
		err = PTR_ERR(handle);
		जाओ out_trace;
	पूर्ण

	अगर (inode->i_size & (inode->i_sb->s_blocksize - 1))
		ext4_block_truncate_page(handle, mapping, inode->i_size);

	/*
	 * We add the inode to the orphan list, so that अगर this
	 * truncate spans multiple transactions, and we crash, we will
	 * resume the truncate when the fileप्रणाली recovers.  It also
	 * marks the inode dirty, to catch the new size.
	 *
	 * Implication: the file must always be in a sane, consistent
	 * truncatable state जबतक each transaction commits.
	 */
	err = ext4_orphan_add(handle, inode);
	अगर (err)
		जाओ out_stop;

	करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);

	ext4_discard_pपुनः_स्मृतिations(inode, 0);

	अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		err = ext4_ext_truncate(handle, inode);
	अन्यथा
		ext4_ind_truncate(handle, inode);

	up_ग_लिखो(&ei->i_data_sem);
	अगर (err)
		जाओ out_stop;

	अगर (IS_SYNC(inode))
		ext4_handle_sync(handle);

out_stop:
	/*
	 * If this was a simple ftruncate() and the file will reमुख्य alive,
	 * then we need to clear up the orphan record which we created above.
	 * However, अगर this was a real unlink then we were called by
	 * ext4_evict_inode(), and we allow that function to clean up the
	 * orphan info क्रम us.
	 */
	अगर (inode->i_nlink)
		ext4_orphan_del(handle, inode);

	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	err2 = ext4_mark_inode_dirty(handle, inode);
	अगर (unlikely(err2 && !err))
		err = err2;
	ext4_journal_stop(handle);

out_trace:
	trace_ext4_truncate_निकास(inode);
	वापस err;
पूर्ण

/*
 * ext4_get_inode_loc वापसs with an extra refcount against the inode's
 * underlying buffer_head on success. If 'in_mem' is true, we have all
 * data in memory that is needed to recreate the on-disk version of this
 * inode.
 */
अटल पूर्णांक __ext4_get_inode_loc(काष्ठा super_block *sb, अचिन्हित दीर्घ ino,
				काष्ठा ext4_iloc *iloc, पूर्णांक in_mem,
				ext4_fsblk_t *ret_block)
अणु
	काष्ठा ext4_group_desc	*gdp;
	काष्ठा buffer_head	*bh;
	ext4_fsblk_t		block;
	काष्ठा blk_plug		plug;
	पूर्णांक			inodes_per_block, inode_offset;

	iloc->bh = शून्य;
	अगर (ino < EXT4_ROOT_INO ||
	    ino > le32_to_cpu(EXT4_SB(sb)->s_es->s_inodes_count))
		वापस -EFSCORRUPTED;

	iloc->block_group = (ino - 1) / EXT4_INODES_PER_GROUP(sb);
	gdp = ext4_get_group_desc(sb, iloc->block_group, शून्य);
	अगर (!gdp)
		वापस -EIO;

	/*
	 * Figure out the offset within the block group inode table
	 */
	inodes_per_block = EXT4_SB(sb)->s_inodes_per_block;
	inode_offset = ((ino - 1) %
			EXT4_INODES_PER_GROUP(sb));
	block = ext4_inode_table(sb, gdp) + (inode_offset / inodes_per_block);
	iloc->offset = (inode_offset % inodes_per_block) * EXT4_INODE_SIZE(sb);

	bh = sb_getblk(sb, block);
	अगर (unlikely(!bh))
		वापस -ENOMEM;
	अगर (ext4_simulate_fail(sb, EXT4_SIM_INODE_EIO))
		जाओ simulate_eio;
	अगर (!buffer_uptodate(bh)) अणु
		lock_buffer(bh);

		अगर (ext4_buffer_uptodate(bh)) अणु
			/* someone brought it uptodate जबतक we रुकोed */
			unlock_buffer(bh);
			जाओ has_buffer;
		पूर्ण

		/*
		 * If we have all inक्रमmation of the inode in memory and this
		 * is the only valid inode in the block, we need not पढ़ो the
		 * block.
		 */
		अगर (in_mem) अणु
			काष्ठा buffer_head *biपंचांगap_bh;
			पूर्णांक i, start;

			start = inode_offset & ~(inodes_per_block - 1);

			/* Is the inode biपंचांगap in cache? */
			biपंचांगap_bh = sb_getblk(sb, ext4_inode_biपंचांगap(sb, gdp));
			अगर (unlikely(!biपंचांगap_bh))
				जाओ make_io;

			/*
			 * If the inode biपंचांगap isn't in cache then the
			 * optimisation may end up perक्रमming two पढ़ोs instead
			 * of one, so skip it.
			 */
			अगर (!buffer_uptodate(biपंचांगap_bh)) अणु
				brअन्यथा(biपंचांगap_bh);
				जाओ make_io;
			पूर्ण
			क्रम (i = start; i < start + inodes_per_block; i++) अणु
				अगर (i == inode_offset)
					जारी;
				अगर (ext4_test_bit(i, biपंचांगap_bh->b_data))
					अवरोध;
			पूर्ण
			brअन्यथा(biपंचांगap_bh);
			अगर (i == start + inodes_per_block) अणु
				/* all other inodes are मुक्त, so skip I/O */
				स_रखो(bh->b_data, 0, bh->b_size);
				set_buffer_uptodate(bh);
				unlock_buffer(bh);
				जाओ has_buffer;
			पूर्ण
		पूर्ण

make_io:
		/*
		 * If we need to करो any I/O, try to pre-पढ़ोahead extra
		 * blocks from the inode table.
		 */
		blk_start_plug(&plug);
		अगर (EXT4_SB(sb)->s_inode_पढ़ोahead_blks) अणु
			ext4_fsblk_t b, end, table;
			अचिन्हित num;
			__u32 ra_blks = EXT4_SB(sb)->s_inode_पढ़ोahead_blks;

			table = ext4_inode_table(sb, gdp);
			/* s_inode_पढ़ोahead_blks is always a घातer of 2 */
			b = block & ~((ext4_fsblk_t) ra_blks - 1);
			अगर (table > b)
				b = table;
			end = b + ra_blks;
			num = EXT4_INODES_PER_GROUP(sb);
			अगर (ext4_has_group_desc_csum(sb))
				num -= ext4_itable_unused_count(sb, gdp);
			table += num / inodes_per_block;
			अगर (end > table)
				end = table;
			जबतक (b <= end)
				ext4_sb_bपढ़ोahead_unmovable(sb, b++);
		पूर्ण

		/*
		 * There are other valid inodes in the buffer, this inode
		 * has in-inode xattrs, or we करोn't have this inode in memory.
		 * Read the block from disk.
		 */
		trace_ext4_load_inode(sb, ino);
		ext4_पढ़ो_bh_noरुको(bh, REQ_META | REQ_PRIO, शून्य);
		blk_finish_plug(&plug);
		रुको_on_buffer(bh);
		अगर (!buffer_uptodate(bh)) अणु
		simulate_eio:
			अगर (ret_block)
				*ret_block = block;
			brअन्यथा(bh);
			वापस -EIO;
		पूर्ण
	पूर्ण
has_buffer:
	iloc->bh = bh;
	वापस 0;
पूर्ण

अटल पूर्णांक __ext4_get_inode_loc_noinmem(काष्ठा inode *inode,
					काष्ठा ext4_iloc *iloc)
अणु
	ext4_fsblk_t err_blk;
	पूर्णांक ret;

	ret = __ext4_get_inode_loc(inode->i_sb, inode->i_ino, iloc, 0,
					&err_blk);

	अगर (ret == -EIO)
		ext4_error_inode_block(inode, err_blk, EIO,
					"unable to read itable block");

	वापस ret;
पूर्ण

पूर्णांक ext4_get_inode_loc(काष्ठा inode *inode, काष्ठा ext4_iloc *iloc)
अणु
	ext4_fsblk_t err_blk;
	पूर्णांक ret;

	/* We have all inode data except xattrs in memory here. */
	ret = __ext4_get_inode_loc(inode->i_sb, inode->i_ino, iloc,
		!ext4_test_inode_state(inode, EXT4_STATE_XATTR), &err_blk);

	अगर (ret == -EIO)
		ext4_error_inode_block(inode, err_blk, EIO,
					"unable to read itable block");

	वापस ret;
पूर्ण


पूर्णांक ext4_get_fc_inode_loc(काष्ठा super_block *sb, अचिन्हित दीर्घ ino,
			  काष्ठा ext4_iloc *iloc)
अणु
	वापस __ext4_get_inode_loc(sb, ino, iloc, 0, शून्य);
पूर्ण

अटल bool ext4_should_enable_dax(काष्ठा inode *inode)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	अगर (test_opt2(inode->i_sb, DAX_NEVER))
		वापस false;
	अगर (!S_ISREG(inode->i_mode))
		वापस false;
	अगर (ext4_should_journal_data(inode))
		वापस false;
	अगर (ext4_has_अंतरभूत_data(inode))
		वापस false;
	अगर (ext4_test_inode_flag(inode, EXT4_INODE_ENCRYPT))
		वापस false;
	अगर (ext4_test_inode_flag(inode, EXT4_INODE_VERITY))
		वापस false;
	अगर (!test_bit(EXT4_FLAGS_BDEV_IS_DAX, &sbi->s_ext4_flags))
		वापस false;
	अगर (test_opt(inode->i_sb, DAX_ALWAYS))
		वापस true;

	वापस ext4_test_inode_flag(inode, EXT4_INODE_DAX);
पूर्ण

व्योम ext4_set_inode_flags(काष्ठा inode *inode, bool init)
अणु
	अचिन्हित पूर्णांक flags = EXT4_I(inode)->i_flags;
	अचिन्हित पूर्णांक new_fl = 0;

	WARN_ON_ONCE(IS_DAX(inode) && init);

	अगर (flags & EXT4_SYNC_FL)
		new_fl |= S_SYNC;
	अगर (flags & EXT4_APPEND_FL)
		new_fl |= S_APPEND;
	अगर (flags & EXT4_IMMUTABLE_FL)
		new_fl |= S_IMMUTABLE;
	अगर (flags & EXT4_NOATIME_FL)
		new_fl |= S_NOATIME;
	अगर (flags & EXT4_सूचीSYNC_FL)
		new_fl |= S_सूचीSYNC;

	/* Because of the way inode_set_flags() works we must preserve S_DAX
	 * here अगर alपढ़ोy set. */
	new_fl |= (inode->i_flags & S_DAX);
	अगर (init && ext4_should_enable_dax(inode))
		new_fl |= S_DAX;

	अगर (flags & EXT4_ENCRYPT_FL)
		new_fl |= S_ENCRYPTED;
	अगर (flags & EXT4_CASEFOLD_FL)
		new_fl |= S_CASEFOLD;
	अगर (flags & EXT4_VERITY_FL)
		new_fl |= S_VERITY;
	inode_set_flags(inode, new_fl,
			S_SYNC|S_APPEND|S_IMMUTABLE|S_NOATIME|S_सूचीSYNC|S_DAX|
			S_ENCRYPTED|S_CASEFOLD|S_VERITY);
पूर्ण

अटल blkcnt_t ext4_inode_blocks(काष्ठा ext4_inode *raw_inode,
				  काष्ठा ext4_inode_info *ei)
अणु
	blkcnt_t i_blocks ;
	काष्ठा inode *inode = &(ei->vfs_inode);
	काष्ठा super_block *sb = inode->i_sb;

	अगर (ext4_has_feature_huge_file(sb)) अणु
		/* we are using combined 48 bit field */
		i_blocks = ((u64)le16_to_cpu(raw_inode->i_blocks_high)) << 32 |
					le32_to_cpu(raw_inode->i_blocks_lo);
		अगर (ext4_test_inode_flag(inode, EXT4_INODE_HUGE_खाता)) अणु
			/* i_blocks represent file प्रणाली block size */
			वापस i_blocks  << (inode->i_blkbits - 9);
		पूर्ण अन्यथा अणु
			वापस i_blocks;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस le32_to_cpu(raw_inode->i_blocks_lo);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ext4_iget_extra_inode(काष्ठा inode *inode,
					 काष्ठा ext4_inode *raw_inode,
					 काष्ठा ext4_inode_info *ei)
अणु
	__le32 *magic = (व्योम *)raw_inode +
			EXT4_GOOD_OLD_INODE_SIZE + ei->i_extra_isize;

	अगर (EXT4_GOOD_OLD_INODE_SIZE + ei->i_extra_isize + माप(__le32) <=
	    EXT4_INODE_SIZE(inode->i_sb) &&
	    *magic == cpu_to_le32(EXT4_XATTR_MAGIC)) अणु
		ext4_set_inode_state(inode, EXT4_STATE_XATTR);
		वापस ext4_find_अंतरभूत_data_nolock(inode);
	पूर्ण अन्यथा
		EXT4_I(inode)->i_अंतरभूत_off = 0;
	वापस 0;
पूर्ण

पूर्णांक ext4_get_projid(काष्ठा inode *inode, kprojid_t *projid)
अणु
	अगर (!ext4_has_feature_project(inode->i_sb))
		वापस -EOPNOTSUPP;
	*projid = EXT4_I(inode)->i_projid;
	वापस 0;
पूर्ण

/*
 * ext4 has self-managed i_version क्रम ea inodes, it stores the lower 32bit of
 * refcount in i_version, so use raw values अगर inode has EXT4_EA_INODE_FL flag
 * set.
 */
अटल अंतरभूत व्योम ext4_inode_set_iversion_queried(काष्ठा inode *inode, u64 val)
अणु
	अगर (unlikely(EXT4_I(inode)->i_flags & EXT4_EA_INODE_FL))
		inode_set_iversion_raw(inode, val);
	अन्यथा
		inode_set_iversion_queried(inode, val);
पूर्ण
अटल अंतरभूत u64 ext4_inode_peek_iversion(स्थिर काष्ठा inode *inode)
अणु
	अगर (unlikely(EXT4_I(inode)->i_flags & EXT4_EA_INODE_FL))
		वापस inode_peek_iversion_raw(inode);
	अन्यथा
		वापस inode_peek_iversion(inode);
पूर्ण

काष्ठा inode *__ext4_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino,
			  ext4_iget_flags flags, स्थिर अक्षर *function,
			  अचिन्हित पूर्णांक line)
अणु
	काष्ठा ext4_iloc iloc;
	काष्ठा ext4_inode *raw_inode;
	काष्ठा ext4_inode_info *ei;
	काष्ठा inode *inode;
	journal_t *journal = EXT4_SB(sb)->s_journal;
	दीर्घ ret;
	loff_t size;
	पूर्णांक block;
	uid_t i_uid;
	gid_t i_gid;
	projid_t i_projid;

	अगर ((!(flags & EXT4_IGET_SPECIAL) &&
	     (ino < EXT4_FIRST_INO(sb) && ino != EXT4_ROOT_INO)) ||
	    (ino < EXT4_ROOT_INO) ||
	    (ino > le32_to_cpu(EXT4_SB(sb)->s_es->s_inodes_count))) अणु
		अगर (flags & EXT4_IGET_HANDLE)
			वापस ERR_PTR(-ESTALE);
		__ext4_error(sb, function, line, false, EFSCORRUPTED, 0,
			     "inode #%lu: comm %s: iget: illegal inode #",
			     ino, current->comm);
		वापस ERR_PTR(-EFSCORRUPTED);
	पूर्ण

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	ei = EXT4_I(inode);
	iloc.bh = शून्य;

	ret = __ext4_get_inode_loc_noinmem(inode, &iloc);
	अगर (ret < 0)
		जाओ bad_inode;
	raw_inode = ext4_raw_inode(&iloc);

	अगर ((ino == EXT4_ROOT_INO) && (raw_inode->i_links_count == 0)) अणु
		ext4_error_inode(inode, function, line, 0,
				 "iget: root inode unallocated");
		ret = -EFSCORRUPTED;
		जाओ bad_inode;
	पूर्ण

	अगर ((flags & EXT4_IGET_HANDLE) &&
	    (raw_inode->i_links_count == 0) && (raw_inode->i_mode == 0)) अणु
		ret = -ESTALE;
		जाओ bad_inode;
	पूर्ण

	अगर (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE) अणु
		ei->i_extra_isize = le16_to_cpu(raw_inode->i_extra_isize);
		अगर (EXT4_GOOD_OLD_INODE_SIZE + ei->i_extra_isize >
			EXT4_INODE_SIZE(inode->i_sb) ||
		    (ei->i_extra_isize & 3)) अणु
			ext4_error_inode(inode, function, line, 0,
					 "iget: bad extra_isize %u "
					 "(inode size %u)",
					 ei->i_extra_isize,
					 EXT4_INODE_SIZE(inode->i_sb));
			ret = -EFSCORRUPTED;
			जाओ bad_inode;
		पूर्ण
	पूर्ण अन्यथा
		ei->i_extra_isize = 0;

	/* Precompute checksum seed क्रम inode metadata */
	अगर (ext4_has_metadata_csum(sb)) अणु
		काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
		__u32 csum;
		__le32 inum = cpu_to_le32(inode->i_ino);
		__le32 gen = raw_inode->i_generation;
		csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)&inum,
				   माप(inum));
		ei->i_csum_seed = ext4_chksum(sbi, csum, (__u8 *)&gen,
					      माप(gen));
	पूर्ण

	अगर ((!ext4_inode_csum_verअगरy(inode, raw_inode, ei) ||
	    ext4_simulate_fail(sb, EXT4_SIM_INODE_CRC)) &&
	     (!(EXT4_SB(sb)->s_mount_state & EXT4_FC_REPLAY))) अणु
		ext4_error_inode_err(inode, function, line, 0,
				EFSBADCRC, "iget: checksum invalid");
		ret = -EFSBADCRC;
		जाओ bad_inode;
	पूर्ण

	inode->i_mode = le16_to_cpu(raw_inode->i_mode);
	i_uid = (uid_t)le16_to_cpu(raw_inode->i_uid_low);
	i_gid = (gid_t)le16_to_cpu(raw_inode->i_gid_low);
	अगर (ext4_has_feature_project(sb) &&
	    EXT4_INODE_SIZE(sb) > EXT4_GOOD_OLD_INODE_SIZE &&
	    EXT4_FITS_IN_INODE(raw_inode, ei, i_projid))
		i_projid = (projid_t)le32_to_cpu(raw_inode->i_projid);
	अन्यथा
		i_projid = EXT4_DEF_PROJID;

	अगर (!(test_opt(inode->i_sb, NO_UID32))) अणु
		i_uid |= le16_to_cpu(raw_inode->i_uid_high) << 16;
		i_gid |= le16_to_cpu(raw_inode->i_gid_high) << 16;
	पूर्ण
	i_uid_ग_लिखो(inode, i_uid);
	i_gid_ग_लिखो(inode, i_gid);
	ei->i_projid = make_kprojid(&init_user_ns, i_projid);
	set_nlink(inode, le16_to_cpu(raw_inode->i_links_count));

	ext4_clear_state_flags(ei);	/* Only relevant on 32-bit archs */
	ei->i_अंतरभूत_off = 0;
	ei->i_dir_start_lookup = 0;
	ei->i_dसमय = le32_to_cpu(raw_inode->i_dसमय);
	/* We now have enough fields to check अगर the inode was active or not.
	 * This is needed because nfsd might try to access dead inodes
	 * the test is that same one that e2fsck uses
	 * NeilBrown 1999oct15
	 */
	अगर (inode->i_nlink == 0) अणु
		अगर ((inode->i_mode == 0 ||
		     !(EXT4_SB(inode->i_sb)->s_mount_state & EXT4_ORPHAN_FS)) &&
		    ino != EXT4_BOOT_LOADER_INO) अणु
			/* this inode is deleted */
			ret = -ESTALE;
			जाओ bad_inode;
		पूर्ण
		/* The only unlinked inodes we let through here have
		 * valid i_mode and are being पढ़ो by the orphan
		 * recovery code: that's fine, we're about to complete
		 * the process of deleting those.
		 * OR it is the EXT4_BOOT_LOADER_INO which is
		 * not initialized on a new fileप्रणाली. */
	पूर्ण
	ei->i_flags = le32_to_cpu(raw_inode->i_flags);
	ext4_set_inode_flags(inode, true);
	inode->i_blocks = ext4_inode_blocks(raw_inode, ei);
	ei->i_file_acl = le32_to_cpu(raw_inode->i_file_acl_lo);
	अगर (ext4_has_feature_64bit(sb))
		ei->i_file_acl |=
			((__u64)le16_to_cpu(raw_inode->i_file_acl_high)) << 32;
	inode->i_size = ext4_isize(sb, raw_inode);
	अगर ((size = i_size_पढ़ो(inode)) < 0) अणु
		ext4_error_inode(inode, function, line, 0,
				 "iget: bad i_size value: %lld", size);
		ret = -EFSCORRUPTED;
		जाओ bad_inode;
	पूर्ण
	/*
	 * If dir_index is not enabled but there's dir with INDEX flag set,
	 * we'd normally treat htree data as empty space. But with metadata
	 * checksumming that corrupts checksums so क्रमbid that.
	 */
	अगर (!ext4_has_feature_dir_index(sb) && ext4_has_metadata_csum(sb) &&
	    ext4_test_inode_flag(inode, EXT4_INODE_INDEX)) अणु
		ext4_error_inode(inode, function, line, 0,
			 "iget: Dir with htree data on filesystem without dir_index feature.");
		ret = -EFSCORRUPTED;
		जाओ bad_inode;
	पूर्ण
	ei->i_disksize = inode->i_size;
#अगर_घोषित CONFIG_QUOTA
	ei->i_reserved_quota = 0;
#पूर्ण_अगर
	inode->i_generation = le32_to_cpu(raw_inode->i_generation);
	ei->i_block_group = iloc.block_group;
	ei->i_last_alloc_group = ~0;
	/*
	 * NOTE! The in-memory inode i_data array is in little-endian order
	 * even on big-endian machines: we करो NOT byteswap the block numbers!
	 */
	क्रम (block = 0; block < EXT4_N_BLOCKS; block++)
		ei->i_data[block] = raw_inode->i_block[block];
	INIT_LIST_HEAD(&ei->i_orphan);
	ext4_fc_init_inode(&ei->vfs_inode);

	/*
	 * Set transaction id's of transactions that have to be committed
	 * to finish f[data]sync. We set them to currently running transaction
	 * as we cannot be sure that the inode or some of its metadata isn't
	 * part of the transaction - the inode could have been reclaimed and
	 * now it is reपढ़ो from disk.
	 */
	अगर (journal) अणु
		transaction_t *transaction;
		tid_t tid;

		पढ़ो_lock(&journal->j_state_lock);
		अगर (journal->j_running_transaction)
			transaction = journal->j_running_transaction;
		अन्यथा
			transaction = journal->j_committing_transaction;
		अगर (transaction)
			tid = transaction->t_tid;
		अन्यथा
			tid = journal->j_commit_sequence;
		पढ़ो_unlock(&journal->j_state_lock);
		ei->i_sync_tid = tid;
		ei->i_datasync_tid = tid;
	पूर्ण

	अगर (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE) अणु
		अगर (ei->i_extra_isize == 0) अणु
			/* The extra space is currently unused. Use it. */
			BUILD_BUG_ON(माप(काष्ठा ext4_inode) & 3);
			ei->i_extra_isize = माप(काष्ठा ext4_inode) -
					    EXT4_GOOD_OLD_INODE_SIZE;
		पूर्ण अन्यथा अणु
			ret = ext4_iget_extra_inode(inode, raw_inode, ei);
			अगर (ret)
				जाओ bad_inode;
		पूर्ण
	पूर्ण

	EXT4_INODE_GET_XTIME(i_स_समय, inode, raw_inode);
	EXT4_INODE_GET_XTIME(i_mसमय, inode, raw_inode);
	EXT4_INODE_GET_XTIME(i_aसमय, inode, raw_inode);
	EXT4_EINODE_GET_XTIME(i_crसमय, ei, raw_inode);

	अगर (likely(!test_opt2(inode->i_sb, HURD_COMPAT))) अणु
		u64 ivers = le32_to_cpu(raw_inode->i_disk_version);

		अगर (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE) अणु
			अगर (EXT4_FITS_IN_INODE(raw_inode, ei, i_version_hi))
				ivers |=
		    (__u64)(le32_to_cpu(raw_inode->i_version_hi)) << 32;
		पूर्ण
		ext4_inode_set_iversion_queried(inode, ivers);
	पूर्ण

	ret = 0;
	अगर (ei->i_file_acl &&
	    !ext4_inode_block_valid(inode, ei->i_file_acl, 1)) अणु
		ext4_error_inode(inode, function, line, 0,
				 "iget: bad extended attribute block %llu",
				 ei->i_file_acl);
		ret = -EFSCORRUPTED;
		जाओ bad_inode;
	पूर्ण अन्यथा अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		/* validate the block references in the inode */
		अगर (!(EXT4_SB(sb)->s_mount_state & EXT4_FC_REPLAY) &&
			(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
			(S_ISLNK(inode->i_mode) &&
			!ext4_inode_is_fast_symlink(inode)))) अणु
			अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
				ret = ext4_ext_check_inode(inode);
			अन्यथा
				ret = ext4_ind_check_inode(inode);
		पूर्ण
	पूर्ण
	अगर (ret)
		जाओ bad_inode;

	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_op = &ext4_file_inode_operations;
		inode->i_fop = &ext4_file_operations;
		ext4_set_aops(inode);
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &ext4_dir_inode_operations;
		inode->i_fop = &ext4_dir_operations;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		/* VFS करोes not allow setting these so must be corruption */
		अगर (IS_APPEND(inode) || IS_IMMUTABLE(inode)) अणु
			ext4_error_inode(inode, function, line, 0,
					 "iget: immutable or append flags "
					 "not allowed on symlinks");
			ret = -EFSCORRUPTED;
			जाओ bad_inode;
		पूर्ण
		अगर (IS_ENCRYPTED(inode)) अणु
			inode->i_op = &ext4_encrypted_symlink_inode_operations;
			ext4_set_aops(inode);
		पूर्ण अन्यथा अगर (ext4_inode_is_fast_symlink(inode)) अणु
			inode->i_link = (अक्षर *)ei->i_data;
			inode->i_op = &ext4_fast_symlink_inode_operations;
			nd_terminate_link(ei->i_data, inode->i_size,
				माप(ei->i_data) - 1);
		पूर्ण अन्यथा अणु
			inode->i_op = &ext4_symlink_inode_operations;
			ext4_set_aops(inode);
		पूर्ण
		inode_nohighmem(inode);
	पूर्ण अन्यथा अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode) ||
	      S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) अणु
		inode->i_op = &ext4_special_inode_operations;
		अगर (raw_inode->i_block[0])
			init_special_inode(inode, inode->i_mode,
			   old_decode_dev(le32_to_cpu(raw_inode->i_block[0])));
		अन्यथा
			init_special_inode(inode, inode->i_mode,
			   new_decode_dev(le32_to_cpu(raw_inode->i_block[1])));
	पूर्ण अन्यथा अगर (ino == EXT4_BOOT_LOADER_INO) अणु
		make_bad_inode(inode);
	पूर्ण अन्यथा अणु
		ret = -EFSCORRUPTED;
		ext4_error_inode(inode, function, line, 0,
				 "iget: bogus i_mode (%o)", inode->i_mode);
		जाओ bad_inode;
	पूर्ण
	अगर (IS_CASEFOLDED(inode) && !ext4_has_feature_हालfold(inode->i_sb))
		ext4_error_inode(inode, function, line, 0,
				 "casefold flag without casefold feature");
	brअन्यथा(iloc.bh);

	unlock_new_inode(inode);
	वापस inode;

bad_inode:
	brअन्यथा(iloc.bh);
	iget_failed(inode);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक ext4_inode_blocks_set(handle_t *handle,
				काष्ठा ext4_inode *raw_inode,
				काष्ठा ext4_inode_info *ei)
अणु
	काष्ठा inode *inode = &(ei->vfs_inode);
	u64 i_blocks = READ_ONCE(inode->i_blocks);
	काष्ठा super_block *sb = inode->i_sb;

	अगर (i_blocks <= ~0U) अणु
		/*
		 * i_blocks can be represented in a 32 bit variable
		 * as multiple of 512 bytes
		 */
		raw_inode->i_blocks_lo   = cpu_to_le32(i_blocks);
		raw_inode->i_blocks_high = 0;
		ext4_clear_inode_flag(inode, EXT4_INODE_HUGE_खाता);
		वापस 0;
	पूर्ण
	अगर (!ext4_has_feature_huge_file(sb))
		वापस -EFBIG;

	अगर (i_blocks <= 0xffffffffffffULL) अणु
		/*
		 * i_blocks can be represented in a 48 bit variable
		 * as multiple of 512 bytes
		 */
		raw_inode->i_blocks_lo   = cpu_to_le32(i_blocks);
		raw_inode->i_blocks_high = cpu_to_le16(i_blocks >> 32);
		ext4_clear_inode_flag(inode, EXT4_INODE_HUGE_खाता);
	पूर्ण अन्यथा अणु
		ext4_set_inode_flag(inode, EXT4_INODE_HUGE_खाता);
		/* i_block is stored in file प्रणाली block size */
		i_blocks = i_blocks >> (inode->i_blkbits - 9);
		raw_inode->i_blocks_lo   = cpu_to_le32(i_blocks);
		raw_inode->i_blocks_high = cpu_to_le16(i_blocks >> 32);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __ext4_update_other_inode_समय(काष्ठा super_block *sb,
					   अचिन्हित दीर्घ orig_ino,
					   अचिन्हित दीर्घ ino,
					   काष्ठा ext4_inode *raw_inode)
अणु
	काष्ठा inode *inode;

	inode = find_inode_by_ino_rcu(sb, ino);
	अगर (!inode)
		वापस;

	अगर (!inode_is_dirtyसमय_only(inode))
		वापस;

	spin_lock(&inode->i_lock);
	अगर (inode_is_dirtyसमय_only(inode)) अणु
		काष्ठा ext4_inode_info	*ei = EXT4_I(inode);

		inode->i_state &= ~I_सूचीTY_TIME;
		spin_unlock(&inode->i_lock);

		spin_lock(&ei->i_raw_lock);
		EXT4_INODE_SET_XTIME(i_स_समय, inode, raw_inode);
		EXT4_INODE_SET_XTIME(i_mसमय, inode, raw_inode);
		EXT4_INODE_SET_XTIME(i_aसमय, inode, raw_inode);
		ext4_inode_csum_set(inode, raw_inode, ei);
		spin_unlock(&ei->i_raw_lock);
		trace_ext4_other_inode_update_समय(inode, orig_ino);
		वापस;
	पूर्ण
	spin_unlock(&inode->i_lock);
पूर्ण

/*
 * Opportunistically update the other समय fields क्रम other inodes in
 * the same inode table block.
 */
अटल व्योम ext4_update_other_inodes_समय(काष्ठा super_block *sb,
					  अचिन्हित दीर्घ orig_ino, अक्षर *buf)
अणु
	अचिन्हित दीर्घ ino;
	पूर्णांक i, inodes_per_block = EXT4_SB(sb)->s_inodes_per_block;
	पूर्णांक inode_size = EXT4_INODE_SIZE(sb);

	/*
	 * Calculate the first inode in the inode table block.  Inode
	 * numbers are one-based.  That is, the first inode in a block
	 * (assuming 4k blocks and 256 byte inodes) is (n*16 + 1).
	 */
	ino = ((orig_ino - 1) & ~(inodes_per_block - 1)) + 1;
	rcu_पढ़ो_lock();
	क्रम (i = 0; i < inodes_per_block; i++, ino++, buf += inode_size) अणु
		अगर (ino == orig_ino)
			जारी;
		__ext4_update_other_inode_समय(sb, orig_ino, ino,
					       (काष्ठा ext4_inode *)buf);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Post the काष्ठा inode info पूर्णांकo an on-disk inode location in the
 * buffer-cache.  This gobbles the caller's reference to the
 * buffer_head in the inode location काष्ठा.
 *
 * The caller must have ग_लिखो access to iloc->bh.
 */
अटल पूर्णांक ext4_करो_update_inode(handle_t *handle,
				काष्ठा inode *inode,
				काष्ठा ext4_iloc *iloc)
अणु
	काष्ठा ext4_inode *raw_inode = ext4_raw_inode(iloc);
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा buffer_head *bh = iloc->bh;
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक err = 0, block;
	पूर्णांक need_datasync = 0, set_large_file = 0;
	uid_t i_uid;
	gid_t i_gid;
	projid_t i_projid;

	spin_lock(&ei->i_raw_lock);

	/* For fields not tracked in the in-memory inode,
	 * initialise them to zero क्रम new inodes. */
	अगर (ext4_test_inode_state(inode, EXT4_STATE_NEW))
		स_रखो(raw_inode, 0, EXT4_SB(inode->i_sb)->s_inode_size);

	err = ext4_inode_blocks_set(handle, raw_inode, ei);
	अगर (err) अणु
		spin_unlock(&ei->i_raw_lock);
		जाओ out_brअन्यथा;
	पूर्ण

	raw_inode->i_mode = cpu_to_le16(inode->i_mode);
	i_uid = i_uid_पढ़ो(inode);
	i_gid = i_gid_पढ़ो(inode);
	i_projid = from_kprojid(&init_user_ns, ei->i_projid);
	अगर (!(test_opt(inode->i_sb, NO_UID32))) अणु
		raw_inode->i_uid_low = cpu_to_le16(low_16_bits(i_uid));
		raw_inode->i_gid_low = cpu_to_le16(low_16_bits(i_gid));
/*
 * Fix up पूर्णांकeroperability with old kernels. Otherwise, old inodes get
 * re-used with the upper 16 bits of the uid/gid पूर्णांकact
 */
		अगर (ei->i_dसमय && list_empty(&ei->i_orphan)) अणु
			raw_inode->i_uid_high = 0;
			raw_inode->i_gid_high = 0;
		पूर्ण अन्यथा अणु
			raw_inode->i_uid_high =
				cpu_to_le16(high_16_bits(i_uid));
			raw_inode->i_gid_high =
				cpu_to_le16(high_16_bits(i_gid));
		पूर्ण
	पूर्ण अन्यथा अणु
		raw_inode->i_uid_low = cpu_to_le16(fs_high2lowuid(i_uid));
		raw_inode->i_gid_low = cpu_to_le16(fs_high2lowgid(i_gid));
		raw_inode->i_uid_high = 0;
		raw_inode->i_gid_high = 0;
	पूर्ण
	raw_inode->i_links_count = cpu_to_le16(inode->i_nlink);

	EXT4_INODE_SET_XTIME(i_स_समय, inode, raw_inode);
	EXT4_INODE_SET_XTIME(i_mसमय, inode, raw_inode);
	EXT4_INODE_SET_XTIME(i_aसमय, inode, raw_inode);
	EXT4_EINODE_SET_XTIME(i_crसमय, ei, raw_inode);

	raw_inode->i_dसमय = cpu_to_le32(ei->i_dसमय);
	raw_inode->i_flags = cpu_to_le32(ei->i_flags & 0xFFFFFFFF);
	अगर (likely(!test_opt2(inode->i_sb, HURD_COMPAT)))
		raw_inode->i_file_acl_high =
			cpu_to_le16(ei->i_file_acl >> 32);
	raw_inode->i_file_acl_lo = cpu_to_le32(ei->i_file_acl);
	अगर (READ_ONCE(ei->i_disksize) != ext4_isize(inode->i_sb, raw_inode)) अणु
		ext4_isize_set(raw_inode, ei->i_disksize);
		need_datasync = 1;
	पूर्ण
	अगर (ei->i_disksize > 0x7fffffffULL) अणु
		अगर (!ext4_has_feature_large_file(sb) ||
				EXT4_SB(sb)->s_es->s_rev_level ==
		    cpu_to_le32(EXT4_GOOD_OLD_REV))
			set_large_file = 1;
	पूर्ण
	raw_inode->i_generation = cpu_to_le32(inode->i_generation);
	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) अणु
		अगर (old_valid_dev(inode->i_rdev)) अणु
			raw_inode->i_block[0] =
				cpu_to_le32(old_encode_dev(inode->i_rdev));
			raw_inode->i_block[1] = 0;
		पूर्ण अन्यथा अणु
			raw_inode->i_block[0] = 0;
			raw_inode->i_block[1] =
				cpu_to_le32(new_encode_dev(inode->i_rdev));
			raw_inode->i_block[2] = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (!ext4_has_अंतरभूत_data(inode)) अणु
		क्रम (block = 0; block < EXT4_N_BLOCKS; block++)
			raw_inode->i_block[block] = ei->i_data[block];
	पूर्ण

	अगर (likely(!test_opt2(inode->i_sb, HURD_COMPAT))) अणु
		u64 ivers = ext4_inode_peek_iversion(inode);

		raw_inode->i_disk_version = cpu_to_le32(ivers);
		अगर (ei->i_extra_isize) अणु
			अगर (EXT4_FITS_IN_INODE(raw_inode, ei, i_version_hi))
				raw_inode->i_version_hi =
					cpu_to_le32(ivers >> 32);
			raw_inode->i_extra_isize =
				cpu_to_le16(ei->i_extra_isize);
		पूर्ण
	पूर्ण

	BUG_ON(!ext4_has_feature_project(inode->i_sb) &&
	       i_projid != EXT4_DEF_PROJID);

	अगर (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE &&
	    EXT4_FITS_IN_INODE(raw_inode, ei, i_projid))
		raw_inode->i_projid = cpu_to_le32(i_projid);

	ext4_inode_csum_set(inode, raw_inode, ei);
	spin_unlock(&ei->i_raw_lock);
	अगर (inode->i_sb->s_flags & SB_LAZYTIME)
		ext4_update_other_inodes_समय(inode->i_sb, inode->i_ino,
					      bh->b_data);

	BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_metadata(handle, शून्य, bh);
	अगर (err)
		जाओ out_brअन्यथा;
	ext4_clear_inode_state(inode, EXT4_STATE_NEW);
	अगर (set_large_file) अणु
		BUFFER_TRACE(EXT4_SB(sb)->s_sbh, "get write access");
		err = ext4_journal_get_ग_लिखो_access(handle, EXT4_SB(sb)->s_sbh);
		अगर (err)
			जाओ out_brअन्यथा;
		lock_buffer(EXT4_SB(sb)->s_sbh);
		ext4_set_feature_large_file(sb);
		ext4_superblock_csum_set(sb);
		unlock_buffer(EXT4_SB(sb)->s_sbh);
		ext4_handle_sync(handle);
		err = ext4_handle_dirty_metadata(handle, शून्य,
						 EXT4_SB(sb)->s_sbh);
	पूर्ण
	ext4_update_inode_fsync_trans(handle, inode, need_datasync);
out_brअन्यथा:
	brअन्यथा(bh);
	ext4_std_error(inode->i_sb, err);
	वापस err;
पूर्ण

/*
 * ext4_ग_लिखो_inode()
 *
 * We are called from a few places:
 *
 * - Within generic_file_aio_ग_लिखो() -> generic_ग_लिखो_sync() क्रम O_SYNC files.
 *   Here, there will be no transaction running. We रुको क्रम any running
 *   transaction to commit.
 *
 * - Within flush work (sys_sync(), kupdate and such).
 *   We रुको on commit, अगर told to.
 *
 * - Within iput_final() -> ग_लिखो_inode_now()
 *   We रुको on commit, अगर told to.
 *
 * In all हालs it is actually safe क्रम us to वापस without करोing anything,
 * because the inode has been copied पूर्णांकo a raw inode buffer in
 * ext4_mark_inode_dirty().  This is a correctness thing क्रम WB_SYNC_ALL
 * ग_लिखोback.
 *
 * Note that we are असलolutely dependent upon all inode dirtiers करोing the
 * right thing: they *must* call mark_inode_dirty() after dirtying info in
 * which we are पूर्णांकerested.
 *
 * It would be a bug क्रम them to not करो this.  The code:
 *
 *	mark_inode_dirty(inode)
 *	stuff();
 *	inode->i_size = expr;
 *
 * is in error because ग_लिखो_inode() could occur जबतक `stuff()' is running,
 * and the new i_size will be lost.  Plus the inode will no दीर्घer be on the
 * superblock's dirty inode list.
 */
पूर्णांक ext4_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक err;

	अगर (WARN_ON_ONCE(current->flags & PF_MEMALLOC) ||
	    sb_rकरोnly(inode->i_sb))
		वापस 0;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

	अगर (EXT4_SB(inode->i_sb)->s_journal) अणु
		अगर (ext4_journal_current_handle()) अणु
			jbd_debug(1, "called recursively, non-PF_MEMALLOC!\n");
			dump_stack();
			वापस -EIO;
		पूर्ण

		/*
		 * No need to क्रमce transaction in WB_SYNC_NONE mode. Also
		 * ext4_sync_fs() will क्रमce the commit after everything is
		 * written.
		 */
		अगर (wbc->sync_mode != WB_SYNC_ALL || wbc->क्रम_sync)
			वापस 0;

		err = ext4_fc_commit(EXT4_SB(inode->i_sb)->s_journal,
						EXT4_I(inode)->i_sync_tid);
	पूर्ण अन्यथा अणु
		काष्ठा ext4_iloc iloc;

		err = __ext4_get_inode_loc_noinmem(inode, &iloc);
		अगर (err)
			वापस err;
		/*
		 * sync(2) will flush the whole buffer cache. No need to करो
		 * it here separately क्रम each inode.
		 */
		अगर (wbc->sync_mode == WB_SYNC_ALL && !wbc->क्रम_sync)
			sync_dirty_buffer(iloc.bh);
		अगर (buffer_req(iloc.bh) && !buffer_uptodate(iloc.bh)) अणु
			ext4_error_inode_block(inode, iloc.bh->b_blocknr, EIO,
					       "IO error syncing inode");
			err = -EIO;
		पूर्ण
		brअन्यथा(iloc.bh);
	पूर्ण
	वापस err;
पूर्ण

/*
 * In data=journal mode ext4_journalled_invalidatepage() may fail to invalidate
 * buffers that are attached to a page stradding i_size and are undergoing
 * commit. In that हाल we have to रुको क्रम commit to finish and try again.
 */
अटल व्योम ext4_रुको_क्रम_tail_page_commit(काष्ठा inode *inode)
अणु
	काष्ठा page *page;
	अचिन्हित offset;
	journal_t *journal = EXT4_SB(inode->i_sb)->s_journal;
	tid_t commit_tid = 0;
	पूर्णांक ret;

	offset = inode->i_size & (PAGE_SIZE - 1);
	/*
	 * If the page is fully truncated, we करोn't need to रुको क्रम any commit
	 * (and we even should not as __ext4_journalled_invalidatepage() may
	 * strip all buffers from the page but keep the page dirty which can then
	 * confuse e.g. concurrent ext4_ग_लिखोpage() seeing dirty page without
	 * buffers). Also we करोn't need to रुको क्रम any commit अगर all buffers in
	 * the page reमुख्य valid. This is most beneficial क्रम the common हाल of
	 * blocksize == PAGESIZE.
	 */
	अगर (!offset || offset > (PAGE_SIZE - i_blocksize(inode)))
		वापस;
	जबतक (1) अणु
		page = find_lock_page(inode->i_mapping,
				      inode->i_size >> PAGE_SHIFT);
		अगर (!page)
			वापस;
		ret = __ext4_journalled_invalidatepage(page, offset,
						PAGE_SIZE - offset);
		unlock_page(page);
		put_page(page);
		अगर (ret != -EBUSY)
			वापस;
		commit_tid = 0;
		पढ़ो_lock(&journal->j_state_lock);
		अगर (journal->j_committing_transaction)
			commit_tid = journal->j_committing_transaction->t_tid;
		पढ़ो_unlock(&journal->j_state_lock);
		अगर (commit_tid)
			jbd2_log_रुको_commit(journal, commit_tid);
	पूर्ण
पूर्ण

/*
 * ext4_setattr()
 *
 * Called from notअगरy_change.
 *
 * We want to trap VFS attempts to truncate the file as soon as
 * possible.  In particular, we want to make sure that when the VFS
 * shrinks i_size, we put the inode on the orphan list and modअगरy
 * i_disksize immediately, so that during the subsequent flushing of
 * dirty pages and मुक्तing of disk blocks, we can guarantee that any
 * commit will leave the blocks being flushed in an unused state on
 * disk.  (On recovery, the inode will get truncated and the blocks will
 * be मुक्तd, so we have a strong guarantee that no future commit will
 * leave these blocks visible to the user.)
 *
 * Another thing we have to assure is that अगर we are in ordered mode
 * and inode is still attached to the committing transaction, we must
 * we start ग_लिखोout of all the dirty pages which are being truncated.
 * This way we are sure that all the data written in the previous
 * transaction are alपढ़ोy on disk (truncate रुकोs क्रम pages under
 * ग_लिखोback).
 *
 * Called with inode->i_mutex करोwn.
 */
पूर्णांक ext4_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		 काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error, rc = 0;
	पूर्णांक orphan = 0;
	स्थिर अचिन्हित पूर्णांक ia_valid = attr->ia_valid;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

	अगर (unlikely(IS_IMMUTABLE(inode)))
		वापस -EPERM;

	अगर (unlikely(IS_APPEND(inode) &&
		     (ia_valid & (ATTR_MODE | ATTR_UID |
				  ATTR_GID | ATTR_TIMES_SET))))
		वापस -EPERM;

	error = setattr_prepare(mnt_userns, dentry, attr);
	अगर (error)
		वापस error;

	error = fscrypt_prepare_setattr(dentry, attr);
	अगर (error)
		वापस error;

	error = fsverity_prepare_setattr(dentry, attr);
	अगर (error)
		वापस error;

	अगर (is_quota_modअगरication(inode, attr)) अणु
		error = dquot_initialize(inode);
		अगर (error)
			वापस error;
	पूर्ण
	ext4_fc_start_update(inode);
	अगर ((ia_valid & ATTR_UID && !uid_eq(attr->ia_uid, inode->i_uid)) ||
	    (ia_valid & ATTR_GID && !gid_eq(attr->ia_gid, inode->i_gid))) अणु
		handle_t *handle;

		/* (user+group)*(old+new) काष्ठाure, inode ग_लिखो (sb,
		 * inode block, ? - but truncate inode update has it) */
		handle = ext4_journal_start(inode, EXT4_HT_QUOTA,
			(EXT4_MAXQUOTAS_INIT_BLOCKS(inode->i_sb) +
			 EXT4_MAXQUOTAS_DEL_BLOCKS(inode->i_sb)) + 3);
		अगर (IS_ERR(handle)) अणु
			error = PTR_ERR(handle);
			जाओ err_out;
		पूर्ण

		/* dquot_transfer() calls back ext4_get_inode_usage() which
		 * counts xattr inode references.
		 */
		करोwn_पढ़ो(&EXT4_I(inode)->xattr_sem);
		error = dquot_transfer(inode, attr);
		up_पढ़ो(&EXT4_I(inode)->xattr_sem);

		अगर (error) अणु
			ext4_journal_stop(handle);
			ext4_fc_stop_update(inode);
			वापस error;
		पूर्ण
		/* Update corresponding info in inode so that everything is in
		 * one transaction */
		अगर (attr->ia_valid & ATTR_UID)
			inode->i_uid = attr->ia_uid;
		अगर (attr->ia_valid & ATTR_GID)
			inode->i_gid = attr->ia_gid;
		error = ext4_mark_inode_dirty(handle, inode);
		ext4_journal_stop(handle);
		अगर (unlikely(error)) अणु
			ext4_fc_stop_update(inode);
			वापस error;
		पूर्ण
	पूर्ण

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		handle_t *handle;
		loff_t oldsize = inode->i_size;
		पूर्णांक shrink = (attr->ia_size < inode->i_size);

		अगर (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))) अणु
			काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

			अगर (attr->ia_size > sbi->s_biपंचांगap_maxbytes) अणु
				ext4_fc_stop_update(inode);
				वापस -EFBIG;
			पूर्ण
		पूर्ण
		अगर (!S_ISREG(inode->i_mode)) अणु
			ext4_fc_stop_update(inode);
			वापस -EINVAL;
		पूर्ण

		अगर (IS_I_VERSION(inode) && attr->ia_size != inode->i_size)
			inode_inc_iversion(inode);

		अगर (shrink) अणु
			अगर (ext4_should_order_data(inode)) अणु
				error = ext4_begin_ordered_truncate(inode,
							    attr->ia_size);
				अगर (error)
					जाओ err_out;
			पूर्ण
			/*
			 * Blocks are going to be हटाओd from the inode. Wait
			 * क्रम dio in flight.
			 */
			inode_dio_रुको(inode);
		पूर्ण

		करोwn_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);

		rc = ext4_अवरोध_layouts(inode);
		अगर (rc) अणु
			up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
			जाओ err_out;
		पूर्ण

		अगर (attr->ia_size != inode->i_size) अणु
			handle = ext4_journal_start(inode, EXT4_HT_INODE, 3);
			अगर (IS_ERR(handle)) अणु
				error = PTR_ERR(handle);
				जाओ out_mmap_sem;
			पूर्ण
			अगर (ext4_handle_valid(handle) && shrink) अणु
				error = ext4_orphan_add(handle, inode);
				orphan = 1;
			पूर्ण
			/*
			 * Update c/mसमय on truncate up, ext4_truncate() will
			 * update c/mसमय in shrink हाल below
			 */
			अगर (!shrink) अणु
				inode->i_mसमय = current_समय(inode);
				inode->i_स_समय = inode->i_mसमय;
			पूर्ण

			अगर (shrink)
				ext4_fc_track_range(handle, inode,
					(attr->ia_size > 0 ? attr->ia_size - 1 : 0) >>
					inode->i_sb->s_blocksize_bits,
					(oldsize > 0 ? oldsize - 1 : 0) >>
					inode->i_sb->s_blocksize_bits);
			अन्यथा
				ext4_fc_track_range(
					handle, inode,
					(oldsize > 0 ? oldsize - 1 : oldsize) >>
					inode->i_sb->s_blocksize_bits,
					(attr->ia_size > 0 ? attr->ia_size - 1 : 0) >>
					inode->i_sb->s_blocksize_bits);

			करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
			EXT4_I(inode)->i_disksize = attr->ia_size;
			rc = ext4_mark_inode_dirty(handle, inode);
			अगर (!error)
				error = rc;
			/*
			 * We have to update i_size under i_data_sem together
			 * with i_disksize to aव्योम races with ग_लिखोback code
			 * running ext4_wb_update_i_disksize().
			 */
			अगर (!error)
				i_size_ग_लिखो(inode, attr->ia_size);
			up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
			ext4_journal_stop(handle);
			अगर (error)
				जाओ out_mmap_sem;
			अगर (!shrink) अणु
				pagecache_isize_extended(inode, oldsize,
							 inode->i_size);
			पूर्ण अन्यथा अगर (ext4_should_journal_data(inode)) अणु
				ext4_रुको_क्रम_tail_page_commit(inode);
			पूर्ण
		पूर्ण

		/*
		 * Truncate pagecache after we've रुकोed क्रम commit
		 * in data=journal mode to make pages मुक्तable.
		 */
		truncate_pagecache(inode, inode->i_size);
		/*
		 * Call ext4_truncate() even अगर i_size didn't change to
		 * truncate possible pपुनः_स्मृतिated blocks.
		 */
		अगर (attr->ia_size <= oldsize) अणु
			rc = ext4_truncate(inode);
			अगर (rc)
				error = rc;
		पूर्ण
out_mmap_sem:
		up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
	पूर्ण

	अगर (!error) अणु
		setattr_copy(mnt_userns, inode, attr);
		mark_inode_dirty(inode);
	पूर्ण

	/*
	 * If the call to ext4_truncate failed to get a transaction handle at
	 * all, we need to clean up the in-core orphan list manually.
	 */
	अगर (orphan && inode->i_nlink)
		ext4_orphan_del(शून्य, inode);

	अगर (!error && (ia_valid & ATTR_MODE))
		rc = posix_acl_chmod(mnt_userns, inode, inode->i_mode);

err_out:
	अगर  (error)
		ext4_std_error(inode->i_sb, error);
	अगर (!error)
		error = rc;
	ext4_fc_stop_update(inode);
	वापस error;
पूर्ण

पूर्णांक ext4_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		 काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा ext4_inode *raw_inode;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	अचिन्हित पूर्णांक flags;

	अगर ((request_mask & STATX_BTIME) &&
	    EXT4_FITS_IN_INODE(raw_inode, ei, i_crसमय)) अणु
		stat->result_mask |= STATX_BTIME;
		stat->bसमय.tv_sec = ei->i_crसमय.tv_sec;
		stat->bसमय.tv_nsec = ei->i_crसमय.tv_nsec;
	पूर्ण

	flags = ei->i_flags & EXT4_FL_USER_VISIBLE;
	अगर (flags & EXT4_APPEND_FL)
		stat->attributes |= STATX_ATTR_APPEND;
	अगर (flags & EXT4_COMPR_FL)
		stat->attributes |= STATX_ATTR_COMPRESSED;
	अगर (flags & EXT4_ENCRYPT_FL)
		stat->attributes |= STATX_ATTR_ENCRYPTED;
	अगर (flags & EXT4_IMMUTABLE_FL)
		stat->attributes |= STATX_ATTR_IMMUTABLE;
	अगर (flags & EXT4_NODUMP_FL)
		stat->attributes |= STATX_ATTR_NODUMP;
	अगर (flags & EXT4_VERITY_FL)
		stat->attributes |= STATX_ATTR_VERITY;

	stat->attributes_mask |= (STATX_ATTR_APPEND |
				  STATX_ATTR_COMPRESSED |
				  STATX_ATTR_ENCRYPTED |
				  STATX_ATTR_IMMUTABLE |
				  STATX_ATTR_NODUMP |
				  STATX_ATTR_VERITY);

	generic_fillattr(mnt_userns, inode, stat);
	वापस 0;
पूर्ण

पूर्णांक ext4_file_getattr(काष्ठा user_namespace *mnt_userns,
		      स्थिर काष्ठा path *path, काष्ठा kstat *stat,
		      u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	u64 delalloc_blocks;

	ext4_getattr(mnt_userns, path, stat, request_mask, query_flags);

	/*
	 * If there is अंतरभूत data in the inode, the inode will normally not
	 * have data blocks allocated (it may have an बाह्यal xattr block).
	 * Report at least one sector क्रम such files, so tools like tar, rsync,
	 * others करोn't incorrectly think the file is completely sparse.
	 */
	अगर (unlikely(ext4_has_अंतरभूत_data(inode)))
		stat->blocks += (stat->size + 511) >> 9;

	/*
	 * We can't update i_blocks अगर the block allocation is delayed
	 * otherwise in the हाल of प्रणाली crash beक्रमe the real block
	 * allocation is करोne, we will have i_blocks inconsistent with
	 * on-disk file blocks.
	 * We always keep i_blocks updated together with real
	 * allocation. But to not confuse with user, stat
	 * will वापस the blocks that include the delayed allocation
	 * blocks क्रम this file.
	 */
	delalloc_blocks = EXT4_C2B(EXT4_SB(inode->i_sb),
				   EXT4_I(inode)->i_reserved_data_blocks);
	stat->blocks += delalloc_blocks << (inode->i_sb->s_blocksize_bits - 9);
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_index_trans_blocks(काष्ठा inode *inode, पूर्णांक lblocks,
				   पूर्णांक pextents)
अणु
	अगर (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
		वापस ext4_ind_trans_blocks(inode, lblocks);
	वापस ext4_ext_index_trans_blocks(inode, pextents);
पूर्ण

/*
 * Account क्रम index blocks, block groups biपंचांगaps and block group
 * descriptor blocks अगर modअगरy datablocks and index blocks
 * worse हाल, the indexs blocks spपढ़ो over dअगरferent block groups
 *
 * If datablocks are discontiguous, they are possible to spपढ़ो over
 * dअगरferent block groups too. If they are contiguous, with flexbg,
 * they could still across block group boundary.
 *
 * Also account क्रम superblock, inode, quota and xattr blocks
 */
अटल पूर्णांक ext4_meta_trans_blocks(काष्ठा inode *inode, पूर्णांक lblocks,
				  पूर्णांक pextents)
अणु
	ext4_group_t groups, ngroups = ext4_get_groups_count(inode->i_sb);
	पूर्णांक gdpblocks;
	पूर्णांक idxblocks;
	पूर्णांक ret = 0;

	/*
	 * How many index blocks need to touch to map @lblocks logical blocks
	 * to @pextents physical extents?
	 */
	idxblocks = ext4_index_trans_blocks(inode, lblocks, pextents);

	ret = idxblocks;

	/*
	 * Now let's see how many group biपंचांगaps and group descriptors need
	 * to account
	 */
	groups = idxblocks + pextents;
	gdpblocks = groups;
	अगर (groups > ngroups)
		groups = ngroups;
	अगर (groups > EXT4_SB(inode->i_sb)->s_gdb_count)
		gdpblocks = EXT4_SB(inode->i_sb)->s_gdb_count;

	/* biपंचांगaps and block group descriptor blocks */
	ret += groups + gdpblocks;

	/* Blocks क्रम super block, inode, quota and xattr blocks */
	ret += EXT4_META_TRANS_BLOCKS(inode->i_sb);

	वापस ret;
पूर्ण

/*
 * Calculate the total number of credits to reserve to fit
 * the modअगरication of a single pages पूर्णांकo a single transaction,
 * which may include multiple chunks of block allocations.
 *
 * This could be called via ext4_ग_लिखो_begin()
 *
 * We need to consider the worse हाल, when
 * one new block per extent.
 */
पूर्णांक ext4_ग_लिखोpage_trans_blocks(काष्ठा inode *inode)
अणु
	पूर्णांक bpp = ext4_journal_blocks_per_page(inode);
	पूर्णांक ret;

	ret = ext4_meta_trans_blocks(inode, bpp, bpp);

	/* Account क्रम data blocks क्रम journalled mode */
	अगर (ext4_should_journal_data(inode))
		ret += bpp;
	वापस ret;
पूर्ण

/*
 * Calculate the journal credits क्रम a chunk of data modअगरication.
 *
 * This is called from DIO, fallocate or whoever calling
 * ext4_map_blocks() to map/allocate a chunk of contiguous disk blocks.
 *
 * journal buffers क्रम data blocks are not included here, as DIO
 * and fallocate करो no need to journal data buffers.
 */
पूर्णांक ext4_chunk_trans_blocks(काष्ठा inode *inode, पूर्णांक nrblocks)
अणु
	वापस ext4_meta_trans_blocks(inode, nrblocks, 1);
पूर्ण

/*
 * The caller must have previously called ext4_reserve_inode_ग_लिखो().
 * Give this, we know that the caller alपढ़ोy has ग_लिखो access to iloc->bh.
 */
पूर्णांक ext4_mark_iloc_dirty(handle_t *handle,
			 काष्ठा inode *inode, काष्ठा ext4_iloc *iloc)
अणु
	पूर्णांक err = 0;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb)))) अणु
		put_bh(iloc->bh);
		वापस -EIO;
	पूर्ण
	ext4_fc_track_inode(handle, inode);

	अगर (IS_I_VERSION(inode))
		inode_inc_iversion(inode);

	/* the करो_update_inode consumes one bh->b_count */
	get_bh(iloc->bh);

	/* ext4_करो_update_inode() करोes jbd2_journal_dirty_metadata */
	err = ext4_करो_update_inode(handle, inode, iloc);
	put_bh(iloc->bh);
	वापस err;
पूर्ण

/*
 * On success, We end up with an outstanding reference count against
 * iloc->bh.  This _must_ be cleaned up later.
 */

पूर्णांक
ext4_reserve_inode_ग_लिखो(handle_t *handle, काष्ठा inode *inode,
			 काष्ठा ext4_iloc *iloc)
अणु
	पूर्णांक err;

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))))
		वापस -EIO;

	err = ext4_get_inode_loc(inode, iloc);
	अगर (!err) अणु
		BUFFER_TRACE(iloc->bh, "get_write_access");
		err = ext4_journal_get_ग_लिखो_access(handle, iloc->bh);
		अगर (err) अणु
			brअन्यथा(iloc->bh);
			iloc->bh = शून्य;
		पूर्ण
	पूर्ण
	ext4_std_error(inode->i_sb, err);
	वापस err;
पूर्ण

अटल पूर्णांक __ext4_expand_extra_isize(काष्ठा inode *inode,
				     अचिन्हित पूर्णांक new_extra_isize,
				     काष्ठा ext4_iloc *iloc,
				     handle_t *handle, पूर्णांक *no_expand)
अणु
	काष्ठा ext4_inode *raw_inode;
	काष्ठा ext4_xattr_ibody_header *header;
	अचिन्हित पूर्णांक inode_size = EXT4_INODE_SIZE(inode->i_sb);
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	पूर्णांक error;

	/* this was checked at iget समय, but द्विगुन check क्रम good measure */
	अगर ((EXT4_GOOD_OLD_INODE_SIZE + ei->i_extra_isize > inode_size) ||
	    (ei->i_extra_isize & 3)) अणु
		EXT4_ERROR_INODE(inode, "bad extra_isize %u (inode size %u)",
				 ei->i_extra_isize,
				 EXT4_INODE_SIZE(inode->i_sb));
		वापस -EFSCORRUPTED;
	पूर्ण
	अगर ((new_extra_isize < ei->i_extra_isize) ||
	    (new_extra_isize < 4) ||
	    (new_extra_isize > inode_size - EXT4_GOOD_OLD_INODE_SIZE))
		वापस -EINVAL;	/* Should never happen */

	raw_inode = ext4_raw_inode(iloc);

	header = IHDR(inode, raw_inode);

	/* No extended attributes present */
	अगर (!ext4_test_inode_state(inode, EXT4_STATE_XATTR) ||
	    header->h_magic != cpu_to_le32(EXT4_XATTR_MAGIC)) अणु
		स_रखो((व्योम *)raw_inode + EXT4_GOOD_OLD_INODE_SIZE +
		       EXT4_I(inode)->i_extra_isize, 0,
		       new_extra_isize - EXT4_I(inode)->i_extra_isize);
		EXT4_I(inode)->i_extra_isize = new_extra_isize;
		वापस 0;
	पूर्ण

	/* try to expand with EAs present */
	error = ext4_expand_extra_isize_ea(inode, new_extra_isize,
					   raw_inode, handle);
	अगर (error) अणु
		/*
		 * Inode size expansion failed; करोn't try again
		 */
		*no_expand = 1;
	पूर्ण

	वापस error;
पूर्ण

/*
 * Expand an inode by new_extra_isize bytes.
 * Returns 0 on success or negative error number on failure.
 */
अटल पूर्णांक ext4_try_to_expand_extra_isize(काष्ठा inode *inode,
					  अचिन्हित पूर्णांक new_extra_isize,
					  काष्ठा ext4_iloc iloc,
					  handle_t *handle)
अणु
	पूर्णांक no_expand;
	पूर्णांक error;

	अगर (ext4_test_inode_state(inode, EXT4_STATE_NO_EXPAND))
		वापस -EOVERFLOW;

	/*
	 * In nojournal mode, we can immediately attempt to expand
	 * the inode.  When journaled, we first need to obtain extra
	 * buffer credits since we may ग_लिखो पूर्णांकo the EA block
	 * with this same handle. If journal_extend fails, then it will
	 * only result in a minor loss of functionality क्रम that inode.
	 * If this is felt to be critical, then e2fsck should be run to
	 * क्रमce a large enough s_min_extra_isize.
	 */
	अगर (ext4_journal_extend(handle,
				EXT4_DATA_TRANS_BLOCKS(inode->i_sb), 0) != 0)
		वापस -ENOSPC;

	अगर (ext4_ग_लिखो_trylock_xattr(inode, &no_expand) == 0)
		वापस -EBUSY;

	error = __ext4_expand_extra_isize(inode, new_extra_isize, &iloc,
					  handle, &no_expand);
	ext4_ग_लिखो_unlock_xattr(inode, &no_expand);

	वापस error;
पूर्ण

पूर्णांक ext4_expand_extra_isize(काष्ठा inode *inode,
			    अचिन्हित पूर्णांक new_extra_isize,
			    काष्ठा ext4_iloc *iloc)
अणु
	handle_t *handle;
	पूर्णांक no_expand;
	पूर्णांक error, rc;

	अगर (ext4_test_inode_state(inode, EXT4_STATE_NO_EXPAND)) अणु
		brअन्यथा(iloc->bh);
		वापस -EOVERFLOW;
	पूर्ण

	handle = ext4_journal_start(inode, EXT4_HT_INODE,
				    EXT4_DATA_TRANS_BLOCKS(inode->i_sb));
	अगर (IS_ERR(handle)) अणु
		error = PTR_ERR(handle);
		brअन्यथा(iloc->bh);
		वापस error;
	पूर्ण

	ext4_ग_लिखो_lock_xattr(inode, &no_expand);

	BUFFER_TRACE(iloc->bh, "get_write_access");
	error = ext4_journal_get_ग_लिखो_access(handle, iloc->bh);
	अगर (error) अणु
		brअन्यथा(iloc->bh);
		जाओ out_unlock;
	पूर्ण

	error = __ext4_expand_extra_isize(inode, new_extra_isize, iloc,
					  handle, &no_expand);

	rc = ext4_mark_iloc_dirty(handle, inode, iloc);
	अगर (!error)
		error = rc;

out_unlock:
	ext4_ग_लिखो_unlock_xattr(inode, &no_expand);
	ext4_journal_stop(handle);
	वापस error;
पूर्ण

/*
 * What we करो here is to mark the in-core inode as clean with respect to inode
 * dirtiness (it may still be data-dirty).
 * This means that the in-core inode may be reaped by prune_icache
 * without having to perक्रमm any I/O.  This is a very good thing,
 * because *any* task may call prune_icache - even ones which
 * have a transaction खोलो against a dअगरferent journal.
 *
 * Is this cheating?  Not really.  Sure, we haven't written the
 * inode out, but prune_icache isn't a user-visible syncing function.
 * Whenever the user wants stuff synced (sys_sync, sys_msync, sys_fsync)
 * we start and रुको on commits.
 */
पूर्णांक __ext4_mark_inode_dirty(handle_t *handle, काष्ठा inode *inode,
				स्थिर अक्षर *func, अचिन्हित पूर्णांक line)
अणु
	काष्ठा ext4_iloc iloc;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	पूर्णांक err;

	might_sleep();
	trace_ext4_mark_inode_dirty(inode, _RET_IP_);
	err = ext4_reserve_inode_ग_लिखो(handle, inode, &iloc);
	अगर (err)
		जाओ out;

	अगर (EXT4_I(inode)->i_extra_isize < sbi->s_want_extra_isize)
		ext4_try_to_expand_extra_isize(inode, sbi->s_want_extra_isize,
					       iloc, handle);

	err = ext4_mark_iloc_dirty(handle, inode, &iloc);
out:
	अगर (unlikely(err))
		ext4_error_inode_err(inode, func, line, 0, err,
					"mark_inode_dirty error");
	वापस err;
पूर्ण

/*
 * ext4_dirty_inode() is called from __mark_inode_dirty()
 *
 * We're really पूर्णांकerested in the हाल where a file is being extended.
 * i_size has been changed by generic_commit_ग_लिखो() and we thus need
 * to include the updated inode in the current transaction.
 *
 * Also, dquot_alloc_block() will always dirty the inode when blocks
 * are allocated to the file.
 *
 * If the inode is marked synchronous, we करोn't honour that here - करोing
 * so would cause a commit on aसमय updates, which we करोn't bother करोing.
 * We handle synchronous inodes at the highest possible level.
 */
व्योम ext4_dirty_inode(काष्ठा inode *inode, पूर्णांक flags)
अणु
	handle_t *handle;

	handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
	अगर (IS_ERR(handle))
		वापस;
	ext4_mark_inode_dirty(handle, inode);
	ext4_journal_stop(handle);
पूर्ण

पूर्णांक ext4_change_inode_journal_flag(काष्ठा inode *inode, पूर्णांक val)
अणु
	journal_t *journal;
	handle_t *handle;
	पूर्णांक err;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	/*
	 * We have to be very careful here: changing a data block's
	 * journaling status dynamically is dangerous.  If we ग_लिखो a
	 * data block to the journal, change the status and then delete
	 * that block, we risk क्रमgetting to revoke the old log record
	 * from the journal and so a subsequent replay can corrupt data.
	 * So, first we make sure that the journal is empty and that
	 * nobody is changing anything.
	 */

	journal = EXT4_JOURNAL(inode);
	अगर (!journal)
		वापस 0;
	अगर (is_journal_पातed(journal))
		वापस -EROFS;

	/* Wait क्रम all existing dio workers */
	inode_dio_रुको(inode);

	/*
	 * Beक्रमe flushing the journal and चयनing inode's aops, we have
	 * to flush all dirty data the inode has. There can be outstanding
	 * delayed allocations, there can be unwritten extents created by
	 * fallocate or buffered ग_लिखोs in dioपढ़ो_nolock mode covered by
	 * dirty data which can be converted only after flushing the dirty
	 * data (and journalled aops करोn't know how to handle these हालs).
	 */
	अगर (val) अणु
		करोwn_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
		err = filemap_ग_लिखो_and_रुको(inode->i_mapping);
		अगर (err < 0) अणु
			up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);
			वापस err;
		पूर्ण
	पूर्ण

	percpu_करोwn_ग_लिखो(&sbi->s_ग_लिखोpages_rwsem);
	jbd2_journal_lock_updates(journal);

	/*
	 * OK, there are no updates running now, and all cached data is
	 * synced to disk.  We are now in a completely consistent state
	 * which करोesn't have anything in the journal, and we know that
	 * no fileप्रणाली updates are running, so it is safe to modअगरy
	 * the inode's in-core data-journaling state flag now.
	 */

	अगर (val)
		ext4_set_inode_flag(inode, EXT4_INODE_JOURNAL_DATA);
	अन्यथा अणु
		err = jbd2_journal_flush(journal);
		अगर (err < 0) अणु
			jbd2_journal_unlock_updates(journal);
			percpu_up_ग_लिखो(&sbi->s_ग_लिखोpages_rwsem);
			वापस err;
		पूर्ण
		ext4_clear_inode_flag(inode, EXT4_INODE_JOURNAL_DATA);
	पूर्ण
	ext4_set_aops(inode);

	jbd2_journal_unlock_updates(journal);
	percpu_up_ग_लिखो(&sbi->s_ग_लिखोpages_rwsem);

	अगर (val)
		up_ग_लिखो(&EXT4_I(inode)->i_mmap_sem);

	/* Finally we can mark the inode as dirty. */

	handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	ext4_fc_mark_ineligible(inode->i_sb,
		EXT4_FC_REASON_JOURNAL_FLAG_CHANGE);
	err = ext4_mark_inode_dirty(handle, inode);
	ext4_handle_sync(handle);
	ext4_journal_stop(handle);
	ext4_std_error(inode->i_sb, err);

	वापस err;
पूर्ण

अटल पूर्णांक ext4_bh_unmapped(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	वापस !buffer_mapped(bh);
पूर्ण

vm_fault_t ext4_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा page *page = vmf->page;
	loff_t size;
	अचिन्हित दीर्घ len;
	पूर्णांक err;
	vm_fault_t ret;
	काष्ठा file *file = vma->vm_file;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा address_space *mapping = inode->i_mapping;
	handle_t *handle;
	get_block_t *get_block;
	पूर्णांक retries = 0;

	अगर (unlikely(IS_IMMUTABLE(inode)))
		वापस VM_FAULT_SIGBUS;

	sb_start_pagefault(inode->i_sb);
	file_update_समय(vma->vm_file);

	करोwn_पढ़ो(&EXT4_I(inode)->i_mmap_sem);

	err = ext4_convert_अंतरभूत_data(inode);
	अगर (err)
		जाओ out_ret;

	/*
	 * On data journalling we skip straight to the transaction handle:
	 * there's no delalloc; page truncated will be checked later; the
	 * early वापस w/ all buffers mapped (calculates size/len) can't
	 * be used; and there's no dioपढ़ो_nolock, so only ext4_get_block.
	 */
	अगर (ext4_should_journal_data(inode))
		जाओ retry_alloc;

	/* Delalloc हाल is easy... */
	अगर (test_opt(inode->i_sb, DELALLOC) &&
	    !ext4_nonda_चयन(inode->i_sb)) अणु
		करो अणु
			err = block_page_mkग_लिखो(vma, vmf,
						   ext4_da_get_block_prep);
		पूर्ण जबतक (err == -ENOSPC &&
		       ext4_should_retry_alloc(inode->i_sb, &retries));
		जाओ out_ret;
	पूर्ण

	lock_page(page);
	size = i_size_पढ़ो(inode);
	/* Page got truncated from under us? */
	अगर (page->mapping != mapping || page_offset(page) > size) अणु
		unlock_page(page);
		ret = VM_FAULT_NOPAGE;
		जाओ out;
	पूर्ण

	अगर (page->index == size >> PAGE_SHIFT)
		len = size & ~PAGE_MASK;
	अन्यथा
		len = PAGE_SIZE;
	/*
	 * Return अगर we have all the buffers mapped. This aव्योमs the need to करो
	 * journal_start/journal_stop which can block and take a दीर्घ समय
	 *
	 * This cannot be करोne क्रम data journalling, as we have to add the
	 * inode to the transaction's list to ग_लिखोprotect pages on commit.
	 */
	अगर (page_has_buffers(page)) अणु
		अगर (!ext4_walk_page_buffers(शून्य, page_buffers(page),
					    0, len, शून्य,
					    ext4_bh_unmapped)) अणु
			/* Wait so that we करोn't change page under IO */
			रुको_क्रम_stable_page(page);
			ret = VM_FAULT_LOCKED;
			जाओ out;
		पूर्ण
	पूर्ण
	unlock_page(page);
	/* OK, we need to fill the hole... */
	अगर (ext4_should_dioपढ़ो_nolock(inode))
		get_block = ext4_get_block_unwritten;
	अन्यथा
		get_block = ext4_get_block;
retry_alloc:
	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE,
				    ext4_ग_लिखोpage_trans_blocks(inode));
	अगर (IS_ERR(handle)) अणु
		ret = VM_FAULT_SIGBUS;
		जाओ out;
	पूर्ण
	/*
	 * Data journalling can't use block_page_mkग_लिखो() because it
	 * will set_buffer_dirty() beक्रमe करो_journal_get_ग_लिखो_access()
	 * thus might hit warning messages क्रम dirty metadata buffers.
	 */
	अगर (!ext4_should_journal_data(inode)) अणु
		err = block_page_mkग_लिखो(vma, vmf, get_block);
	पूर्ण अन्यथा अणु
		lock_page(page);
		size = i_size_पढ़ो(inode);
		/* Page got truncated from under us? */
		अगर (page->mapping != mapping || page_offset(page) > size) अणु
			ret = VM_FAULT_NOPAGE;
			जाओ out_error;
		पूर्ण

		अगर (page->index == size >> PAGE_SHIFT)
			len = size & ~PAGE_MASK;
		अन्यथा
			len = PAGE_SIZE;

		err = __block_ग_लिखो_begin(page, 0, len, ext4_get_block);
		अगर (!err) अणु
			ret = VM_FAULT_SIGBUS;
			अगर (ext4_walk_page_buffers(handle, page_buffers(page),
					0, len, शून्य, करो_journal_get_ग_लिखो_access))
				जाओ out_error;
			अगर (ext4_walk_page_buffers(handle, page_buffers(page),
					0, len, शून्य, ग_लिखो_end_fn))
				जाओ out_error;
			अगर (ext4_jbd2_inode_add_ग_लिखो(handle, inode,
						      page_offset(page), len))
				जाओ out_error;
			ext4_set_inode_state(inode, EXT4_STATE_JDATA);
		पूर्ण अन्यथा अणु
			unlock_page(page);
		पूर्ण
	पूर्ण
	ext4_journal_stop(handle);
	अगर (err == -ENOSPC && ext4_should_retry_alloc(inode->i_sb, &retries))
		जाओ retry_alloc;
out_ret:
	ret = block_page_mkग_लिखो_वापस(err);
out:
	up_पढ़ो(&EXT4_I(inode)->i_mmap_sem);
	sb_end_pagefault(inode->i_sb);
	वापस ret;
out_error:
	unlock_page(page);
	ext4_journal_stop(handle);
	जाओ out;
पूर्ण

vm_fault_t ext4_filemap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	vm_fault_t ret;

	करोwn_पढ़ो(&EXT4_I(inode)->i_mmap_sem);
	ret = filemap_fault(vmf);
	up_पढ़ो(&EXT4_I(inode)->i_mmap_sem);

	वापस ret;
पूर्ण
