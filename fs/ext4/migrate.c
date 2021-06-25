<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright IBM Corporation, 2007
 * Author Aneesh Kumar K.V <aneesh.kumar@linux.vnet.ibm.com>
 *
 */

#समावेश <linux/slab.h>
#समावेश "ext4_jbd2.h"
#समावेश "ext4_extents.h"

/*
 * The contiguous blocks details which can be
 * represented by a single extent
 */
काष्ठा migrate_काष्ठा अणु
	ext4_lblk_t first_block, last_block, curr_block;
	ext4_fsblk_t first_pblock, last_pblock;
पूर्ण;

अटल पूर्णांक finish_range(handle_t *handle, काष्ठा inode *inode,
				काष्ठा migrate_काष्ठा *lb)

अणु
	पूर्णांक retval = 0, needed;
	काष्ठा ext4_extent newext;
	काष्ठा ext4_ext_path *path;
	अगर (lb->first_pblock == 0)
		वापस 0;

	/* Add the extent to temp inode*/
	newext.ee_block = cpu_to_le32(lb->first_block);
	newext.ee_len   = cpu_to_le16(lb->last_block - lb->first_block + 1);
	ext4_ext_store_pblock(&newext, lb->first_pblock);
	/* Locking only क्रम convenience since we are operating on temp inode */
	करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	path = ext4_find_extent(inode, lb->first_block, शून्य, 0);
	अगर (IS_ERR(path)) अणु
		retval = PTR_ERR(path);
		path = शून्य;
		जाओ err_out;
	पूर्ण

	/*
	 * Calculate the credit needed to inserting this extent
	 * Since we are करोing this in loop we may accumulate extra
	 * credit. But below we try to not accumulate too much
	 * of them by restarting the journal.
	 */
	needed = ext4_ext_calc_credits_क्रम_single_extent(inode,
		    lb->last_block - lb->first_block + 1, path);

	retval = ext4_datasem_ensure_credits(handle, inode, needed, needed, 0);
	अगर (retval < 0)
		जाओ err_out;
	retval = ext4_ext_insert_extent(handle, inode, &path, &newext, 0);
err_out:
	up_ग_लिखो((&EXT4_I(inode)->i_data_sem));
	ext4_ext_drop_refs(path);
	kमुक्त(path);
	lb->first_pblock = 0;
	वापस retval;
पूर्ण

अटल पूर्णांक update_extent_range(handle_t *handle, काष्ठा inode *inode,
			       ext4_fsblk_t pblock, काष्ठा migrate_काष्ठा *lb)
अणु
	पूर्णांक retval;
	/*
	 * See अगर we can add on to the existing range (अगर it exists)
	 */
	अगर (lb->first_pblock &&
		(lb->last_pblock+1 == pblock) &&
		(lb->last_block+1 == lb->curr_block)) अणु
		lb->last_pblock = pblock;
		lb->last_block = lb->curr_block;
		lb->curr_block++;
		वापस 0;
	पूर्ण
	/*
	 * Start a new range.
	 */
	retval = finish_range(handle, inode, lb);
	lb->first_pblock = lb->last_pblock = pblock;
	lb->first_block = lb->last_block = lb->curr_block;
	lb->curr_block++;
	वापस retval;
पूर्ण

अटल पूर्णांक update_ind_extent_range(handle_t *handle, काष्ठा inode *inode,
				   ext4_fsblk_t pblock,
				   काष्ठा migrate_काष्ठा *lb)
अणु
	काष्ठा buffer_head *bh;
	__le32 *i_data;
	पूर्णांक i, retval = 0;
	अचिन्हित दीर्घ max_entries = inode->i_sb->s_blocksize >> 2;

	bh = ext4_sb_bपढ़ो(inode->i_sb, pblock, 0);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);

	i_data = (__le32 *)bh->b_data;
	क्रम (i = 0; i < max_entries; i++) अणु
		अगर (i_data[i]) अणु
			retval = update_extent_range(handle, inode,
						le32_to_cpu(i_data[i]), lb);
			अगर (retval)
				अवरोध;
		पूर्ण अन्यथा अणु
			lb->curr_block++;
		पूर्ण
	पूर्ण
	put_bh(bh);
	वापस retval;

पूर्ण

अटल पूर्णांक update_dind_extent_range(handle_t *handle, काष्ठा inode *inode,
				    ext4_fsblk_t pblock,
				    काष्ठा migrate_काष्ठा *lb)
अणु
	काष्ठा buffer_head *bh;
	__le32 *i_data;
	पूर्णांक i, retval = 0;
	अचिन्हित दीर्घ max_entries = inode->i_sb->s_blocksize >> 2;

	bh = ext4_sb_bपढ़ो(inode->i_sb, pblock, 0);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);

	i_data = (__le32 *)bh->b_data;
	क्रम (i = 0; i < max_entries; i++) अणु
		अगर (i_data[i]) अणु
			retval = update_ind_extent_range(handle, inode,
						le32_to_cpu(i_data[i]), lb);
			अगर (retval)
				अवरोध;
		पूर्ण अन्यथा अणु
			/* Only update the file block number */
			lb->curr_block += max_entries;
		पूर्ण
	पूर्ण
	put_bh(bh);
	वापस retval;

पूर्ण

अटल पूर्णांक update_tind_extent_range(handle_t *handle, काष्ठा inode *inode,
				    ext4_fsblk_t pblock,
				    काष्ठा migrate_काष्ठा *lb)
अणु
	काष्ठा buffer_head *bh;
	__le32 *i_data;
	पूर्णांक i, retval = 0;
	अचिन्हित दीर्घ max_entries = inode->i_sb->s_blocksize >> 2;

	bh = ext4_sb_bपढ़ो(inode->i_sb, pblock, 0);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);

	i_data = (__le32 *)bh->b_data;
	क्रम (i = 0; i < max_entries; i++) अणु
		अगर (i_data[i]) अणु
			retval = update_dind_extent_range(handle, inode,
						le32_to_cpu(i_data[i]), lb);
			अगर (retval)
				अवरोध;
		पूर्ण अन्यथा अणु
			/* Only update the file block number */
			lb->curr_block += max_entries * max_entries;
		पूर्ण
	पूर्ण
	put_bh(bh);
	वापस retval;

पूर्ण

अटल पूर्णांक मुक्त_dind_blocks(handle_t *handle,
				काष्ठा inode *inode, __le32 i_data)
अणु
	पूर्णांक i;
	__le32 *पंचांगp_idata;
	काष्ठा buffer_head *bh;
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित दीर्घ max_entries = inode->i_sb->s_blocksize >> 2;
	पूर्णांक err;

	bh = ext4_sb_bपढ़ो(sb, le32_to_cpu(i_data), 0);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);

	पंचांगp_idata = (__le32 *)bh->b_data;
	क्रम (i = 0; i < max_entries; i++) अणु
		अगर (पंचांगp_idata[i]) अणु
			err = ext4_journal_ensure_credits(handle,
				EXT4_RESERVE_TRANS_BLOCKS,
				ext4_मुक्त_metadata_revoke_credits(sb, 1));
			अगर (err < 0) अणु
				put_bh(bh);
				वापस err;
			पूर्ण
			ext4_मुक्त_blocks(handle, inode, शून्य,
					 le32_to_cpu(पंचांगp_idata[i]), 1,
					 EXT4_FREE_BLOCKS_METADATA |
					 EXT4_FREE_BLOCKS_FORGET);
		पूर्ण
	पूर्ण
	put_bh(bh);
	err = ext4_journal_ensure_credits(handle, EXT4_RESERVE_TRANS_BLOCKS,
				ext4_मुक्त_metadata_revoke_credits(sb, 1));
	अगर (err < 0)
		वापस err;
	ext4_मुक्त_blocks(handle, inode, शून्य, le32_to_cpu(i_data), 1,
			 EXT4_FREE_BLOCKS_METADATA |
			 EXT4_FREE_BLOCKS_FORGET);
	वापस 0;
पूर्ण

अटल पूर्णांक मुक्त_tind_blocks(handle_t *handle,
				काष्ठा inode *inode, __le32 i_data)
अणु
	पूर्णांक i, retval = 0;
	__le32 *पंचांगp_idata;
	काष्ठा buffer_head *bh;
	अचिन्हित दीर्घ max_entries = inode->i_sb->s_blocksize >> 2;

	bh = ext4_sb_bपढ़ो(inode->i_sb, le32_to_cpu(i_data), 0);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);

	पंचांगp_idata = (__le32 *)bh->b_data;
	क्रम (i = 0; i < max_entries; i++) अणु
		अगर (पंचांगp_idata[i]) अणु
			retval = मुक्त_dind_blocks(handle,
					inode, पंचांगp_idata[i]);
			अगर (retval) अणु
				put_bh(bh);
				वापस retval;
			पूर्ण
		पूर्ण
	पूर्ण
	put_bh(bh);
	retval = ext4_journal_ensure_credits(handle, EXT4_RESERVE_TRANS_BLOCKS,
			ext4_मुक्त_metadata_revoke_credits(inode->i_sb, 1));
	अगर (retval < 0)
		वापस retval;
	ext4_मुक्त_blocks(handle, inode, शून्य, le32_to_cpu(i_data), 1,
			 EXT4_FREE_BLOCKS_METADATA |
			 EXT4_FREE_BLOCKS_FORGET);
	वापस 0;
पूर्ण

अटल पूर्णांक मुक्त_ind_block(handle_t *handle, काष्ठा inode *inode, __le32 *i_data)
अणु
	पूर्णांक retval;

	/* ei->i_data[EXT4_IND_BLOCK] */
	अगर (i_data[0]) अणु
		retval = ext4_journal_ensure_credits(handle,
			EXT4_RESERVE_TRANS_BLOCKS,
			ext4_मुक्त_metadata_revoke_credits(inode->i_sb, 1));
		अगर (retval < 0)
			वापस retval;
		ext4_मुक्त_blocks(handle, inode, शून्य,
				le32_to_cpu(i_data[0]), 1,
				 EXT4_FREE_BLOCKS_METADATA |
				 EXT4_FREE_BLOCKS_FORGET);
	पूर्ण

	/* ei->i_data[EXT4_DIND_BLOCK] */
	अगर (i_data[1]) अणु
		retval = मुक्त_dind_blocks(handle, inode, i_data[1]);
		अगर (retval)
			वापस retval;
	पूर्ण

	/* ei->i_data[EXT4_TIND_BLOCK] */
	अगर (i_data[2]) अणु
		retval = मुक्त_tind_blocks(handle, inode, i_data[2]);
		अगर (retval)
			वापस retval;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_ext_swap_inode_data(handle_t *handle, काष्ठा inode *inode,
						काष्ठा inode *पंचांगp_inode)
अणु
	पूर्णांक retval, retval2 = 0;
	__le32	i_data[3];
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_inode_info *पंचांगp_ei = EXT4_I(पंचांगp_inode);

	/*
	 * One credit accounted क्रम writing the
	 * i_data field of the original inode
	 */
	retval = ext4_journal_ensure_credits(handle, 1, 0);
	अगर (retval < 0)
		जाओ err_out;

	i_data[0] = ei->i_data[EXT4_IND_BLOCK];
	i_data[1] = ei->i_data[EXT4_DIND_BLOCK];
	i_data[2] = ei->i_data[EXT4_TIND_BLOCK];

	करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	/*
	 * अगर EXT4_STATE_EXT_MIGRATE is cleared a block allocation
	 * happened after we started the migrate. We need to
	 * fail the migrate
	 */
	अगर (!ext4_test_inode_state(inode, EXT4_STATE_EXT_MIGRATE)) अणु
		retval = -EAGAIN;
		up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
		जाओ err_out;
	पूर्ण अन्यथा
		ext4_clear_inode_state(inode, EXT4_STATE_EXT_MIGRATE);
	/*
	 * We have the extent map build with the पंचांगp inode.
	 * Now copy the i_data across
	 */
	ext4_set_inode_flag(inode, EXT4_INODE_EXTENTS);
	स_नकल(ei->i_data, पंचांगp_ei->i_data, माप(ei->i_data));

	/*
	 * Update i_blocks with the new blocks that got
	 * allocated जबतक adding extents क्रम extent index
	 * blocks.
	 *
	 * While converting to extents we need not
	 * update the original inode i_blocks क्रम extent blocks
	 * via quota APIs. The quota update happened via पंचांगp_inode alपढ़ोy.
	 */
	spin_lock(&inode->i_lock);
	inode->i_blocks += पंचांगp_inode->i_blocks;
	spin_unlock(&inode->i_lock);
	up_ग_लिखो(&EXT4_I(inode)->i_data_sem);

	/*
	 * We mark the inode dirty after, because we decrement the
	 * i_blocks when मुक्तing the indirect meta-data blocks
	 */
	retval = मुक्त_ind_block(handle, inode, i_data);
	retval2 = ext4_mark_inode_dirty(handle, inode);
	अगर (unlikely(retval2 && !retval))
		retval = retval2;

err_out:
	वापस retval;
पूर्ण

अटल पूर्णांक मुक्त_ext_idx(handle_t *handle, काष्ठा inode *inode,
					काष्ठा ext4_extent_idx *ix)
अणु
	पूर्णांक i, retval = 0;
	ext4_fsblk_t block;
	काष्ठा buffer_head *bh;
	काष्ठा ext4_extent_header *eh;

	block = ext4_idx_pblock(ix);
	bh = ext4_sb_bपढ़ो(inode->i_sb, block, 0);
	अगर (IS_ERR(bh))
		वापस PTR_ERR(bh);

	eh = (काष्ठा ext4_extent_header *)bh->b_data;
	अगर (eh->eh_depth != 0) अणु
		ix = EXT_FIRST_INDEX(eh);
		क्रम (i = 0; i < le16_to_cpu(eh->eh_entries); i++, ix++) अणु
			retval = मुक्त_ext_idx(handle, inode, ix);
			अगर (retval) अणु
				put_bh(bh);
				वापस retval;
			पूर्ण
		पूर्ण
	पूर्ण
	put_bh(bh);
	retval = ext4_journal_ensure_credits(handle, EXT4_RESERVE_TRANS_BLOCKS,
			ext4_मुक्त_metadata_revoke_credits(inode->i_sb, 1));
	अगर (retval < 0)
		वापस retval;
	ext4_मुक्त_blocks(handle, inode, शून्य, block, 1,
			 EXT4_FREE_BLOCKS_METADATA | EXT4_FREE_BLOCKS_FORGET);
	वापस 0;
पूर्ण

/*
 * Free the extent meta data blocks only
 */
अटल पूर्णांक मुक्त_ext_block(handle_t *handle, काष्ठा inode *inode)
अणु
	पूर्णांक i, retval = 0;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_extent_header *eh = (काष्ठा ext4_extent_header *)ei->i_data;
	काष्ठा ext4_extent_idx *ix;
	अगर (eh->eh_depth == 0)
		/*
		 * No extra blocks allocated क्रम extent meta data
		 */
		वापस 0;
	ix = EXT_FIRST_INDEX(eh);
	क्रम (i = 0; i < le16_to_cpu(eh->eh_entries); i++, ix++) अणु
		retval = मुक्त_ext_idx(handle, inode, ix);
		अगर (retval)
			वापस retval;
	पूर्ण
	वापस retval;
पूर्ण

पूर्णांक ext4_ext_migrate(काष्ठा inode *inode)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	handle_t *handle;
	पूर्णांक retval = 0, i;
	__le32 *i_data;
	काष्ठा ext4_inode_info *ei;
	काष्ठा inode *पंचांगp_inode = शून्य;
	काष्ठा migrate_काष्ठा lb;
	अचिन्हित दीर्घ max_entries;
	__u32 goal;
	uid_t owner[2];

	/*
	 * If the fileप्रणाली करोes not support extents, or the inode
	 * alपढ़ोy is extent-based, error out.
	 */
	अगर (!ext4_has_feature_extents(inode->i_sb) ||
	    (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
		वापस -EINVAL;

	अगर (S_ISLNK(inode->i_mode) && inode->i_blocks == 0)
		/*
		 * करोn't migrate fast symlink
		 */
		वापस retval;

	percpu_करोwn_ग_लिखो(&sbi->s_ग_लिखोpages_rwsem);

	/*
	 * Worst हाल we can touch the allocation biपंचांगaps, a bgd
	 * block, and a block to link in the orphan list.  We करो need
	 * need to worry about credits क्रम modअगरying the quota inode.
	 */
	handle = ext4_journal_start(inode, EXT4_HT_MIGRATE,
		4 + EXT4_MAXQUOTAS_TRANS_BLOCKS(inode->i_sb));

	अगर (IS_ERR(handle)) अणु
		retval = PTR_ERR(handle);
		जाओ out_unlock;
	पूर्ण
	goal = (((inode->i_ino - 1) / EXT4_INODES_PER_GROUP(inode->i_sb)) *
		EXT4_INODES_PER_GROUP(inode->i_sb)) + 1;
	owner[0] = i_uid_पढ़ो(inode);
	owner[1] = i_gid_पढ़ो(inode);
	पंचांगp_inode = ext4_new_inode(handle, d_inode(inode->i_sb->s_root),
				   S_IFREG, शून्य, goal, owner, 0);
	अगर (IS_ERR(पंचांगp_inode)) अणु
		retval = PTR_ERR(पंचांगp_inode);
		ext4_journal_stop(handle);
		जाओ out_unlock;
	पूर्ण
	i_size_ग_लिखो(पंचांगp_inode, i_size_पढ़ो(inode));
	/*
	 * Set the i_nlink to zero so it will be deleted later
	 * when we drop inode reference.
	 */
	clear_nlink(पंचांगp_inode);

	ext4_ext_tree_init(handle, पंचांगp_inode);
	ext4_orphan_add(handle, पंचांगp_inode);
	ext4_journal_stop(handle);

	/*
	 * start with one credit accounted क्रम
	 * superblock modअगरication.
	 *
	 * For the पंचांगp_inode we alपढ़ोy have committed the
	 * transaction that created the inode. Later as and
	 * when we add extents we extent the journal
	 */
	/*
	 * Even though we take i_mutex we can still cause block
	 * allocation via mmap ग_लिखो to holes. If we have allocated
	 * new blocks we fail migrate.  New block allocation will
	 * clear EXT4_STATE_EXT_MIGRATE flag.  The flag is updated
	 * with i_data_sem held to prevent racing with block
	 * allocation.
	 */
	करोwn_पढ़ो(&EXT4_I(inode)->i_data_sem);
	ext4_set_inode_state(inode, EXT4_STATE_EXT_MIGRATE);
	up_पढ़ो((&EXT4_I(inode)->i_data_sem));

	handle = ext4_journal_start(inode, EXT4_HT_MIGRATE, 1);
	अगर (IS_ERR(handle)) अणु
		/*
		 * It is impossible to update on-disk काष्ठाures without
		 * a handle, so just rollback in-core changes and live other
		 * work to orphan_list_cleanup()
		 */
		ext4_orphan_del(शून्य, पंचांगp_inode);
		retval = PTR_ERR(handle);
		जाओ out_पंचांगp_inode;
	पूर्ण

	ei = EXT4_I(inode);
	i_data = ei->i_data;
	स_रखो(&lb, 0, माप(lb));

	/* 32 bit block address 4 bytes */
	max_entries = inode->i_sb->s_blocksize >> 2;
	क्रम (i = 0; i < EXT4_Nसूची_BLOCKS; i++) अणु
		अगर (i_data[i]) अणु
			retval = update_extent_range(handle, पंचांगp_inode,
						le32_to_cpu(i_data[i]), &lb);
			अगर (retval)
				जाओ err_out;
		पूर्ण अन्यथा
			lb.curr_block++;
	पूर्ण
	अगर (i_data[EXT4_IND_BLOCK]) अणु
		retval = update_ind_extent_range(handle, पंचांगp_inode,
				le32_to_cpu(i_data[EXT4_IND_BLOCK]), &lb);
		अगर (retval)
			जाओ err_out;
	पूर्ण अन्यथा
		lb.curr_block += max_entries;
	अगर (i_data[EXT4_DIND_BLOCK]) अणु
		retval = update_dind_extent_range(handle, पंचांगp_inode,
				le32_to_cpu(i_data[EXT4_DIND_BLOCK]), &lb);
		अगर (retval)
			जाओ err_out;
	पूर्ण अन्यथा
		lb.curr_block += max_entries * max_entries;
	अगर (i_data[EXT4_TIND_BLOCK]) अणु
		retval = update_tind_extent_range(handle, पंचांगp_inode,
				le32_to_cpu(i_data[EXT4_TIND_BLOCK]), &lb);
		अगर (retval)
			जाओ err_out;
	पूर्ण
	/*
	 * Build the last extent
	 */
	retval = finish_range(handle, पंचांगp_inode, &lb);
err_out:
	अगर (retval)
		/*
		 * Failure हाल delete the extent inक्रमmation with the
		 * पंचांगp_inode
		 */
		मुक्त_ext_block(handle, पंचांगp_inode);
	अन्यथा अणु
		retval = ext4_ext_swap_inode_data(handle, inode, पंचांगp_inode);
		अगर (retval)
			/*
			 * अगर we fail to swap inode data मुक्त the extent
			 * details of the पंचांगp inode
			 */
			मुक्त_ext_block(handle, पंचांगp_inode);
	पूर्ण

	/* We mark the पंचांगp_inode dirty via ext4_ext_tree_init. */
	retval = ext4_journal_ensure_credits(handle, 1, 0);
	अगर (retval < 0)
		जाओ out_stop;
	/*
	 * Mark the पंचांगp_inode as of size zero
	 */
	i_size_ग_लिखो(पंचांगp_inode, 0);

	/*
	 * set the  i_blocks count to zero
	 * so that the ext4_evict_inode() करोes the
	 * right job
	 *
	 * We करोn't need to take the i_lock because
	 * the inode is not visible to user space.
	 */
	पंचांगp_inode->i_blocks = 0;

	/* Reset the extent details */
	ext4_ext_tree_init(handle, पंचांगp_inode);
out_stop:
	ext4_journal_stop(handle);
out_पंचांगp_inode:
	unlock_new_inode(पंचांगp_inode);
	iput(पंचांगp_inode);
out_unlock:
	percpu_up_ग_लिखो(&sbi->s_ग_लिखोpages_rwsem);
	वापस retval;
पूर्ण

/*
 * Migrate a simple extent-based inode to use the i_blocks[] array
 */
पूर्णांक ext4_ind_migrate(काष्ठा inode *inode)
अणु
	काष्ठा ext4_extent_header	*eh;
	काष्ठा ext4_sb_info		*sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_super_block		*es = sbi->s_es;
	काष्ठा ext4_inode_info		*ei = EXT4_I(inode);
	काष्ठा ext4_extent		*ex;
	अचिन्हित पूर्णांक			i, len;
	ext4_lblk_t			start, end;
	ext4_fsblk_t			blk;
	handle_t			*handle;
	पूर्णांक				ret, ret2 = 0;

	अगर (!ext4_has_feature_extents(inode->i_sb) ||
	    (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
		वापस -EINVAL;

	अगर (ext4_has_feature_bigalloc(inode->i_sb))
		वापस -EOPNOTSUPP;

	/*
	 * In order to get correct extent info, क्रमce all delayed allocation
	 * blocks to be allocated, otherwise delayed allocation blocks may not
	 * be reflected and bypass the checks on extent header.
	 */
	अगर (test_opt(inode->i_sb, DELALLOC))
		ext4_alloc_da_blocks(inode);

	percpu_करोwn_ग_लिखो(&sbi->s_ग_लिखोpages_rwsem);

	handle = ext4_journal_start(inode, EXT4_HT_MIGRATE, 1);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		जाओ out_unlock;
	पूर्ण

	करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	ret = ext4_ext_check_inode(inode);
	अगर (ret)
		जाओ errout;

	eh = ext_inode_hdr(inode);
	ex  = EXT_FIRST_EXTENT(eh);
	अगर (ext4_blocks_count(es) > EXT4_MAX_BLOCK_खाता_PHYS ||
	    eh->eh_depth != 0 || le16_to_cpu(eh->eh_entries) > 1) अणु
		ret = -EOPNOTSUPP;
		जाओ errout;
	पूर्ण
	अगर (eh->eh_entries == 0)
		blk = len = start = end = 0;
	अन्यथा अणु
		len = le16_to_cpu(ex->ee_len);
		blk = ext4_ext_pblock(ex);
		start = le32_to_cpu(ex->ee_block);
		end = start + len - 1;
		अगर (end >= EXT4_Nसूची_BLOCKS) अणु
			ret = -EOPNOTSUPP;
			जाओ errout;
		पूर्ण
	पूर्ण

	ext4_clear_inode_flag(inode, EXT4_INODE_EXTENTS);
	स_रखो(ei->i_data, 0, माप(ei->i_data));
	क्रम (i = start; i <= end; i++)
		ei->i_data[i] = cpu_to_le32(blk++);
	ret2 = ext4_mark_inode_dirty(handle, inode);
	अगर (unlikely(ret2 && !ret))
		ret = ret2;
errout:
	ext4_journal_stop(handle);
	up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
out_unlock:
	percpu_up_ग_लिखो(&sbi->s_ग_लिखोpages_rwsem);
	वापस ret;
पूर्ण
