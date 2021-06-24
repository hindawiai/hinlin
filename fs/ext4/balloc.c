<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/balloc.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  Enhanced block allocation by Stephen Tweedie (sct@redhat.com), 1993
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#समावेश <linux/समय.स>
#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/buffer_head.h>
#समावेश "ext4.h"
#समावेश "ext4_jbd2.h"
#समावेश "mballoc.h"

#समावेश <trace/events/ext4.h>

अटल अचिन्हित ext4_num_base_meta_clusters(काष्ठा super_block *sb,
					    ext4_group_t block_group);
/*
 * balloc.c contains the blocks allocation and deallocation routines
 */

/*
 * Calculate block group number क्रम a given block number
 */
ext4_group_t ext4_get_group_number(काष्ठा super_block *sb,
				   ext4_fsblk_t block)
अणु
	ext4_group_t group;

	अगर (test_opt2(sb, STD_GROUP_SIZE))
		group = (block -
			 le32_to_cpu(EXT4_SB(sb)->s_es->s_first_data_block)) >>
			(EXT4_BLOCK_SIZE_BITS(sb) + EXT4_CLUSTER_BITS(sb) + 3);
	अन्यथा
		ext4_get_group_no_and_offset(sb, block, &group, शून्य);
	वापस group;
पूर्ण

/*
 * Calculate the block group number and offset पूर्णांकo the block/cluster
 * allocation biपंचांगap, given a block number
 */
व्योम ext4_get_group_no_and_offset(काष्ठा super_block *sb, ext4_fsblk_t blocknr,
		ext4_group_t *blockgrpp, ext4_grpblk_t *offsetp)
अणु
	काष्ठा ext4_super_block *es = EXT4_SB(sb)->s_es;
	ext4_grpblk_t offset;

	blocknr = blocknr - le32_to_cpu(es->s_first_data_block);
	offset = करो_भाग(blocknr, EXT4_BLOCKS_PER_GROUP(sb)) >>
		EXT4_SB(sb)->s_cluster_bits;
	अगर (offsetp)
		*offsetp = offset;
	अगर (blockgrpp)
		*blockgrpp = blocknr;

पूर्ण

/*
 * Check whether the 'block' lives within the 'block_group'. Returns 1 अगर so
 * and 0 otherwise.
 */
अटल अंतरभूत पूर्णांक ext4_block_in_group(काष्ठा super_block *sb,
				      ext4_fsblk_t block,
				      ext4_group_t block_group)
अणु
	ext4_group_t actual_group;

	actual_group = ext4_get_group_number(sb, block);
	वापस (actual_group == block_group) ? 1 : 0;
पूर्ण

/* Return the number of clusters used क्रम file प्रणाली metadata; this
 * represents the overhead needed by the file प्रणाली.
 */
अटल अचिन्हित ext4_num_overhead_clusters(काष्ठा super_block *sb,
					   ext4_group_t block_group,
					   काष्ठा ext4_group_desc *gdp)
अणु
	अचिन्हित num_clusters;
	पूर्णांक block_cluster = -1, inode_cluster = -1, itbl_cluster = -1, i, c;
	ext4_fsblk_t start = ext4_group_first_block_no(sb, block_group);
	ext4_fsblk_t itbl_blk;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	/* This is the number of clusters used by the superblock,
	 * block group descriptors, and reserved block group
	 * descriptor blocks */
	num_clusters = ext4_num_base_meta_clusters(sb, block_group);

	/*
	 * For the allocation biपंचांगaps and inode table, we first need
	 * to check to see अगर the block is in the block group.  If it
	 * is, then check to see अगर the cluster is alपढ़ोy accounted
	 * क्रम in the clusters used क्रम the base metadata cluster, or
	 * अगर we can increment the base metadata cluster to include
	 * that block.  Otherwise, we will have to track the cluster
	 * used क्रम the allocation biपंचांगap or inode table explicitly.
	 * Normally all of these blocks are contiguous, so the special
	 * हाल handling shouldn't be necessary except क्रम *very*
	 * unusual file प्रणाली layouts.
	 */
	अगर (ext4_block_in_group(sb, ext4_block_biपंचांगap(sb, gdp), block_group)) अणु
		block_cluster = EXT4_B2C(sbi,
					 ext4_block_biपंचांगap(sb, gdp) - start);
		अगर (block_cluster < num_clusters)
			block_cluster = -1;
		अन्यथा अगर (block_cluster == num_clusters) अणु
			num_clusters++;
			block_cluster = -1;
		पूर्ण
	पूर्ण

	अगर (ext4_block_in_group(sb, ext4_inode_biपंचांगap(sb, gdp), block_group)) अणु
		inode_cluster = EXT4_B2C(sbi,
					 ext4_inode_biपंचांगap(sb, gdp) - start);
		अगर (inode_cluster < num_clusters)
			inode_cluster = -1;
		अन्यथा अगर (inode_cluster == num_clusters) अणु
			num_clusters++;
			inode_cluster = -1;
		पूर्ण
	पूर्ण

	itbl_blk = ext4_inode_table(sb, gdp);
	क्रम (i = 0; i < sbi->s_itb_per_group; i++) अणु
		अगर (ext4_block_in_group(sb, itbl_blk + i, block_group)) अणु
			c = EXT4_B2C(sbi, itbl_blk + i - start);
			अगर ((c < num_clusters) || (c == inode_cluster) ||
			    (c == block_cluster) || (c == itbl_cluster))
				जारी;
			अगर (c == num_clusters) अणु
				num_clusters++;
				जारी;
			पूर्ण
			num_clusters++;
			itbl_cluster = c;
		पूर्ण
	पूर्ण

	अगर (block_cluster != -1)
		num_clusters++;
	अगर (inode_cluster != -1)
		num_clusters++;

	वापस num_clusters;
पूर्ण

अटल अचिन्हित पूर्णांक num_clusters_in_group(काष्ठा super_block *sb,
					  ext4_group_t block_group)
अणु
	अचिन्हित पूर्णांक blocks;

	अगर (block_group == ext4_get_groups_count(sb) - 1) अणु
		/*
		 * Even though mke2fs always initializes the first and
		 * last group, just in हाल some other tool was used,
		 * we need to make sure we calculate the right मुक्त
		 * blocks.
		 */
		blocks = ext4_blocks_count(EXT4_SB(sb)->s_es) -
			ext4_group_first_block_no(sb, block_group);
	पूर्ण अन्यथा
		blocks = EXT4_BLOCKS_PER_GROUP(sb);
	वापस EXT4_NUM_B2C(EXT4_SB(sb), blocks);
पूर्ण

/* Initializes an uninitialized block biपंचांगap */
अटल पूर्णांक ext4_init_block_biपंचांगap(काष्ठा super_block *sb,
				   काष्ठा buffer_head *bh,
				   ext4_group_t block_group,
				   काष्ठा ext4_group_desc *gdp)
अणु
	अचिन्हित पूर्णांक bit, bit_max;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsblk_t start, पंचांगp;

	ASSERT(buffer_locked(bh));

	/* If checksum is bad mark all blocks used to prevent allocation
	 * essentially implementing a per-group पढ़ो-only flag. */
	अगर (!ext4_group_desc_csum_verअगरy(sb, block_group, gdp)) अणु
		ext4_mark_group_biपंचांगap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT |
					EXT4_GROUP_INFO_IBITMAP_CORRUPT);
		वापस -EFSBADCRC;
	पूर्ण
	स_रखो(bh->b_data, 0, sb->s_blocksize);

	bit_max = ext4_num_base_meta_clusters(sb, block_group);
	अगर ((bit_max >> 3) >= bh->b_size)
		वापस -EFSCORRUPTED;

	क्रम (bit = 0; bit < bit_max; bit++)
		ext4_set_bit(bit, bh->b_data);

	start = ext4_group_first_block_no(sb, block_group);

	/* Set bits क्रम block and inode biपंचांगaps, and inode table */
	पंचांगp = ext4_block_biपंचांगap(sb, gdp);
	अगर (ext4_block_in_group(sb, पंचांगp, block_group))
		ext4_set_bit(EXT4_B2C(sbi, पंचांगp - start), bh->b_data);

	पंचांगp = ext4_inode_biपंचांगap(sb, gdp);
	अगर (ext4_block_in_group(sb, पंचांगp, block_group))
		ext4_set_bit(EXT4_B2C(sbi, पंचांगp - start), bh->b_data);

	पंचांगp = ext4_inode_table(sb, gdp);
	क्रम (; पंचांगp < ext4_inode_table(sb, gdp) +
		     sbi->s_itb_per_group; पंचांगp++) अणु
		अगर (ext4_block_in_group(sb, पंचांगp, block_group))
			ext4_set_bit(EXT4_B2C(sbi, पंचांगp - start), bh->b_data);
	पूर्ण

	/*
	 * Also अगर the number of blocks within the group is less than
	 * the blocksize * 8 ( which is the size of biपंचांगap ), set rest
	 * of the block biपंचांगap to 1
	 */
	ext4_mark_biपंचांगap_end(num_clusters_in_group(sb, block_group),
			     sb->s_blocksize * 8, bh->b_data);
	वापस 0;
पूर्ण

/* Return the number of मुक्त blocks in a block group.  It is used when
 * the block biपंचांगap is uninitialized, so we can't just count the bits
 * in the biपंचांगap. */
अचिन्हित ext4_मुक्त_clusters_after_init(काष्ठा super_block *sb,
				       ext4_group_t block_group,
				       काष्ठा ext4_group_desc *gdp)
अणु
	वापस num_clusters_in_group(sb, block_group) -
		ext4_num_overhead_clusters(sb, block_group, gdp);
पूर्ण

/*
 * The मुक्त blocks are managed by biपंचांगaps.  A file प्रणाली contains several
 * blocks groups.  Each group contains 1 biपंचांगap block क्रम blocks, 1 biपंचांगap
 * block क्रम inodes, N blocks क्रम the inode table and data blocks.
 *
 * The file प्रणाली contains group descriptors which are located after the
 * super block.  Each descriptor contains the number of the biपंचांगap block and
 * the मुक्त blocks count in the block.  The descriptors are loaded in memory
 * when a file प्रणाली is mounted (see ext4_fill_super).
 */

/**
 * ext4_get_group_desc() -- load group descriptor from disk
 * @sb:			super block
 * @block_group:	given block group
 * @bh:			poपूर्णांकer to the buffer head to store the block
 *			group descriptor
 */
काष्ठा ext4_group_desc * ext4_get_group_desc(काष्ठा super_block *sb,
					     ext4_group_t block_group,
					     काष्ठा buffer_head **bh)
अणु
	अचिन्हित पूर्णांक group_desc;
	अचिन्हित पूर्णांक offset;
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	काष्ठा ext4_group_desc *desc;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा buffer_head *bh_p;

	अगर (block_group >= ngroups) अणु
		ext4_error(sb, "block_group >= groups_count - block_group = %u,"
			   " groups_count = %u", block_group, ngroups);

		वापस शून्य;
	पूर्ण

	group_desc = block_group >> EXT4_DESC_PER_BLOCK_BITS(sb);
	offset = block_group & (EXT4_DESC_PER_BLOCK(sb) - 1);
	bh_p = sbi_array_rcu_deref(sbi, s_group_desc, group_desc);
	/*
	 * sbi_array_rcu_deref वापसs with rcu unlocked, this is ok since
	 * the poपूर्णांकer being dereferenced won't be dereferenced again. By
	 * looking at the usage in add_new_gdb() the value isn't modअगरied,
	 * just the poपूर्णांकer, and so it reमुख्यs valid.
	 */
	अगर (!bh_p) अणु
		ext4_error(sb, "Group descriptor not loaded - "
			   "block_group = %u, group_desc = %u, desc = %u",
			   block_group, group_desc, offset);
		वापस शून्य;
	पूर्ण

	desc = (काष्ठा ext4_group_desc *)(
		(__u8 *)bh_p->b_data +
		offset * EXT4_DESC_SIZE(sb));
	अगर (bh)
		*bh = bh_p;
	वापस desc;
पूर्ण

/*
 * Return the block number which was discovered to be invalid, or 0 अगर
 * the block biपंचांगap is valid.
 */
अटल ext4_fsblk_t ext4_valid_block_biपंचांगap(काष्ठा super_block *sb,
					    काष्ठा ext4_group_desc *desc,
					    ext4_group_t block_group,
					    काष्ठा buffer_head *bh)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_grpblk_t offset;
	ext4_grpblk_t next_zero_bit;
	ext4_grpblk_t max_bit = EXT4_CLUSTERS_PER_GROUP(sb);
	ext4_fsblk_t blk;
	ext4_fsblk_t group_first_block;

	अगर (ext4_has_feature_flex_bg(sb)) अणु
		/* with FLEX_BG, the inode/block biपंचांगaps and itable
		 * blocks may not be in the group at all
		 * so the biपंचांगap validation will be skipped क्रम those groups
		 * or it has to also पढ़ो the block group where the biपंचांगaps
		 * are located to verअगरy they are set.
		 */
		वापस 0;
	पूर्ण
	group_first_block = ext4_group_first_block_no(sb, block_group);

	/* check whether block biपंचांगap block number is set */
	blk = ext4_block_biपंचांगap(sb, desc);
	offset = blk - group_first_block;
	अगर (offset < 0 || EXT4_B2C(sbi, offset) >= max_bit ||
	    !ext4_test_bit(EXT4_B2C(sbi, offset), bh->b_data))
		/* bad block biपंचांगap */
		वापस blk;

	/* check whether the inode biपंचांगap block number is set */
	blk = ext4_inode_biपंचांगap(sb, desc);
	offset = blk - group_first_block;
	अगर (offset < 0 || EXT4_B2C(sbi, offset) >= max_bit ||
	    !ext4_test_bit(EXT4_B2C(sbi, offset), bh->b_data))
		/* bad block biपंचांगap */
		वापस blk;

	/* check whether the inode table block number is set */
	blk = ext4_inode_table(sb, desc);
	offset = blk - group_first_block;
	अगर (offset < 0 || EXT4_B2C(sbi, offset) >= max_bit ||
	    EXT4_B2C(sbi, offset + sbi->s_itb_per_group) >= max_bit)
		वापस blk;
	next_zero_bit = ext4_find_next_zero_bit(bh->b_data,
			EXT4_B2C(sbi, offset + sbi->s_itb_per_group),
			EXT4_B2C(sbi, offset));
	अगर (next_zero_bit <
	    EXT4_B2C(sbi, offset + sbi->s_itb_per_group))
		/* bad biपंचांगap क्रम inode tables */
		वापस blk;
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_validate_block_biपंचांगap(काष्ठा super_block *sb,
				      काष्ठा ext4_group_desc *desc,
				      ext4_group_t block_group,
				      काष्ठा buffer_head *bh)
अणु
	ext4_fsblk_t	blk;
	काष्ठा ext4_group_info *grp;

	अगर (EXT4_SB(sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस 0;

	grp = ext4_get_group_info(sb, block_group);

	अगर (buffer_verअगरied(bh))
		वापस 0;
	अगर (EXT4_MB_GRP_BBITMAP_CORRUPT(grp))
		वापस -EFSCORRUPTED;

	ext4_lock_group(sb, block_group);
	अगर (buffer_verअगरied(bh))
		जाओ verअगरied;
	अगर (unlikely(!ext4_block_biपंचांगap_csum_verअगरy(sb, block_group,
						    desc, bh) ||
		     ext4_simulate_fail(sb, EXT4_SIM_BBITMAP_CRC))) अणु
		ext4_unlock_group(sb, block_group);
		ext4_error(sb, "bg %u: bad block bitmap checksum", block_group);
		ext4_mark_group_biपंचांगap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		वापस -EFSBADCRC;
	पूर्ण
	blk = ext4_valid_block_biपंचांगap(sb, desc, block_group, bh);
	अगर (unlikely(blk != 0)) अणु
		ext4_unlock_group(sb, block_group);
		ext4_error(sb, "bg %u: block %llu: invalid block bitmap",
			   block_group, blk);
		ext4_mark_group_biपंचांगap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		वापस -EFSCORRUPTED;
	पूर्ण
	set_buffer_verअगरied(bh);
verअगरied:
	ext4_unlock_group(sb, block_group);
	वापस 0;
पूर्ण

/**
 * ext4_पढ़ो_block_biपंचांगap_noरुको()
 * @sb:			super block
 * @block_group:	given block group
 *
 * Read the biपंचांगap क्रम a given block_group,and validate the
 * bits क्रम block/inode/inode tables are set in the biपंचांगaps
 *
 * Return buffer_head on success or an ERR_PTR in हाल of failure.
 */
काष्ठा buffer_head *
ext4_पढ़ो_block_biपंचांगap_noरुको(काष्ठा super_block *sb, ext4_group_t block_group,
			      bool ignore_locked)
अणु
	काष्ठा ext4_group_desc *desc;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा buffer_head *bh;
	ext4_fsblk_t biपंचांगap_blk;
	पूर्णांक err;

	desc = ext4_get_group_desc(sb, block_group, शून्य);
	अगर (!desc)
		वापस ERR_PTR(-EFSCORRUPTED);
	biपंचांगap_blk = ext4_block_biपंचांगap(sb, desc);
	अगर ((biपंचांगap_blk <= le32_to_cpu(sbi->s_es->s_first_data_block)) ||
	    (biपंचांगap_blk >= ext4_blocks_count(sbi->s_es))) अणु
		ext4_error(sb, "Invalid block bitmap block %llu in "
			   "block_group %u", biपंचांगap_blk, block_group);
		ext4_mark_group_biपंचांगap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		वापस ERR_PTR(-EFSCORRUPTED);
	पूर्ण
	bh = sb_getblk(sb, biपंचांगap_blk);
	अगर (unlikely(!bh)) अणु
		ext4_warning(sb, "Cannot get buffer for block bitmap - "
			     "block_group = %u, block_bitmap = %llu",
			     block_group, biपंचांगap_blk);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (ignore_locked && buffer_locked(bh)) अणु
		/* buffer under IO alपढ़ोy, वापस अगर called क्रम prefetching */
		put_bh(bh);
		वापस शून्य;
	पूर्ण

	अगर (biपंचांगap_uptodate(bh))
		जाओ verअगरy;

	lock_buffer(bh);
	अगर (biपंचांगap_uptodate(bh)) अणु
		unlock_buffer(bh);
		जाओ verअगरy;
	पूर्ण
	ext4_lock_group(sb, block_group);
	अगर (ext4_has_group_desc_csum(sb) &&
	    (desc->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))) अणु
		अगर (block_group == 0) अणु
			ext4_unlock_group(sb, block_group);
			unlock_buffer(bh);
			ext4_error(sb, "Block bitmap for bg 0 marked "
				   "uninitialized");
			err = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
		err = ext4_init_block_biपंचांगap(sb, bh, block_group, desc);
		set_biपंचांगap_uptodate(bh);
		set_buffer_uptodate(bh);
		set_buffer_verअगरied(bh);
		ext4_unlock_group(sb, block_group);
		unlock_buffer(bh);
		अगर (err) अणु
			ext4_error(sb, "Failed to init block bitmap for group "
				   "%u: %d", block_group, err);
			जाओ out;
		पूर्ण
		जाओ verअगरy;
	पूर्ण
	ext4_unlock_group(sb, block_group);
	अगर (buffer_uptodate(bh)) अणु
		/*
		 * अगर not uninit अगर bh is uptodate,
		 * biपंचांगap is also uptodate
		 */
		set_biपंचांगap_uptodate(bh);
		unlock_buffer(bh);
		जाओ verअगरy;
	पूर्ण
	/*
	 * submit the buffer_head क्रम पढ़ोing
	 */
	set_buffer_new(bh);
	trace_ext4_पढ़ो_block_biपंचांगap_load(sb, block_group, ignore_locked);
	ext4_पढ़ो_bh_noरुको(bh, REQ_META | REQ_PRIO |
			    (ignore_locked ? REQ_RAHEAD : 0),
			    ext4_end_biपंचांगap_पढ़ो);
	वापस bh;
verअगरy:
	err = ext4_validate_block_biपंचांगap(sb, desc, block_group, bh);
	अगर (err)
		जाओ out;
	वापस bh;
out:
	put_bh(bh);
	वापस ERR_PTR(err);
पूर्ण

/* Returns 0 on success, -त्रुटि_सं on error */
पूर्णांक ext4_रुको_block_biपंचांगap(काष्ठा super_block *sb, ext4_group_t block_group,
			   काष्ठा buffer_head *bh)
अणु
	काष्ठा ext4_group_desc *desc;

	अगर (!buffer_new(bh))
		वापस 0;
	desc = ext4_get_group_desc(sb, block_group, शून्य);
	अगर (!desc)
		वापस -EFSCORRUPTED;
	रुको_on_buffer(bh);
	ext4_simulate_fail_bh(sb, bh, EXT4_SIM_BBITMAP_EIO);
	अगर (!buffer_uptodate(bh)) अणु
		ext4_error_err(sb, EIO, "Cannot read block bitmap - "
			       "block_group = %u, block_bitmap = %llu",
			       block_group, (अचिन्हित दीर्घ दीर्घ) bh->b_blocknr);
		ext4_mark_group_biपंचांगap_corrupted(sb, block_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		वापस -EIO;
	पूर्ण
	clear_buffer_new(bh);
	/* Panic or remount fs पढ़ो-only अगर block biपंचांगap is invalid */
	वापस ext4_validate_block_biपंचांगap(sb, desc, block_group, bh);
पूर्ण

काष्ठा buffer_head *
ext4_पढ़ो_block_biपंचांगap(काष्ठा super_block *sb, ext4_group_t block_group)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक err;

	bh = ext4_पढ़ो_block_biपंचांगap_noरुको(sb, block_group, false);
	अगर (IS_ERR(bh))
		वापस bh;
	err = ext4_रुको_block_biपंचांगap(sb, block_group, bh);
	अगर (err) अणु
		put_bh(bh);
		वापस ERR_PTR(err);
	पूर्ण
	वापस bh;
पूर्ण

/**
 * ext4_has_मुक्त_clusters()
 * @sbi:	in-core super block काष्ठाure.
 * @nclusters:	number of needed blocks
 * @flags:	flags from ext4_mb_new_blocks()
 *
 * Check अगर fileप्रणाली has nclusters मुक्त & available क्रम allocation.
 * On success वापस 1, वापस 0 on failure.
 */
अटल पूर्णांक ext4_has_मुक्त_clusters(काष्ठा ext4_sb_info *sbi,
				  s64 nclusters, अचिन्हित पूर्णांक flags)
अणु
	s64 मुक्त_clusters, dirty_clusters, rsv, resv_clusters;
	काष्ठा percpu_counter *fcc = &sbi->s_मुक्तclusters_counter;
	काष्ठा percpu_counter *dcc = &sbi->s_dirtyclusters_counter;

	मुक्त_clusters  = percpu_counter_पढ़ो_positive(fcc);
	dirty_clusters = percpu_counter_पढ़ो_positive(dcc);
	resv_clusters = atomic64_पढ़ो(&sbi->s_resv_clusters);

	/*
	 * r_blocks_count should always be multiple of the cluster ratio so
	 * we are safe to करो a plane bit shअगरt only.
	 */
	rsv = (ext4_r_blocks_count(sbi->s_es) >> sbi->s_cluster_bits) +
	      resv_clusters;

	अगर (मुक्त_clusters - (nclusters + rsv + dirty_clusters) <
					EXT4_FREECLUSTERS_WATERMARK) अणु
		मुक्त_clusters  = percpu_counter_sum_positive(fcc);
		dirty_clusters = percpu_counter_sum_positive(dcc);
	पूर्ण
	/* Check whether we have space after accounting क्रम current
	 * dirty clusters & root reserved clusters.
	 */
	अगर (मुक्त_clusters >= (rsv + nclusters + dirty_clusters))
		वापस 1;

	/* Hm, nope.  Are (enough) root reserved clusters available? */
	अगर (uid_eq(sbi->s_resuid, current_fsuid()) ||
	    (!gid_eq(sbi->s_resgid, GLOBAL_ROOT_GID) && in_group_p(sbi->s_resgid)) ||
	    capable(CAP_SYS_RESOURCE) ||
	    (flags & EXT4_MB_USE_ROOT_BLOCKS)) अणु

		अगर (मुक्त_clusters >= (nclusters + dirty_clusters +
				      resv_clusters))
			वापस 1;
	पूर्ण
	/* No मुक्त blocks. Let's see अगर we can dip पूर्णांकo reserved pool */
	अगर (flags & EXT4_MB_USE_RESERVED) अणु
		अगर (मुक्त_clusters >= (nclusters + dirty_clusters))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ext4_claim_मुक्त_clusters(काष्ठा ext4_sb_info *sbi,
			     s64 nclusters, अचिन्हित पूर्णांक flags)
अणु
	अगर (ext4_has_मुक्त_clusters(sbi, nclusters, flags)) अणु
		percpu_counter_add(&sbi->s_dirtyclusters_counter, nclusters);
		वापस 0;
	पूर्ण अन्यथा
		वापस -ENOSPC;
पूर्ण

/**
 * ext4_should_retry_alloc() - check अगर a block allocation should be retried
 * @sb:			superblock
 * @retries:		number of retry attempts made so far
 *
 * ext4_should_retry_alloc() is called when ENOSPC is वापसed जबतक
 * attempting to allocate blocks.  If there's an indication that a pending
 * journal transaction might मुक्त some space and allow another attempt to
 * succeed, this function will रुको क्रम the current or committing transaction
 * to complete and then वापस TRUE.
 */
पूर्णांक ext4_should_retry_alloc(काष्ठा super_block *sb, पूर्णांक *retries)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (!sbi->s_journal)
		वापस 0;

	अगर (++(*retries) > 3) अणु
		percpu_counter_inc(&sbi->s_sra_exceeded_retry_limit);
		वापस 0;
	पूर्ण

	/*
	 * अगर there's no indication that blocks are about to be freed it's
	 * possible we just missed a transaction commit that did so
	 */
	smp_mb();
	अगर (sbi->s_mb_मुक्त_pending == 0)
		वापस ext4_has_मुक्त_clusters(sbi, 1, 0);

	/*
	 * it's possible we've just missed a transaction commit here,
	 * so ignore the वापसed status
	 */
	jbd_debug(1, "%s: retrying operation after ENOSPC\n", sb->s_id);
	(व्योम) jbd2_journal_क्रमce_commit_nested(sbi->s_journal);
	वापस 1;
पूर्ण

/*
 * ext4_new_meta_blocks() -- allocate block क्रम meta data (indexing) blocks
 *
 * @handle:             handle to this transaction
 * @inode:              file inode
 * @goal:               given target block(fileप्रणाली wide)
 * @count:		poपूर्णांकer to total number of clusters needed
 * @errp:               error code
 *
 * Return 1st allocated block number on success, *count stores total account
 * error stores in errp poपूर्णांकer
 */
ext4_fsblk_t ext4_new_meta_blocks(handle_t *handle, काष्ठा inode *inode,
				  ext4_fsblk_t goal, अचिन्हित पूर्णांक flags,
				  अचिन्हित दीर्घ *count, पूर्णांक *errp)
अणु
	काष्ठा ext4_allocation_request ar;
	ext4_fsblk_t ret;

	स_रखो(&ar, 0, माप(ar));
	/* Fill with neighbour allocated blocks */
	ar.inode = inode;
	ar.goal = goal;
	ar.len = count ? *count : 1;
	ar.flags = flags;

	ret = ext4_mb_new_blocks(handle, &ar, errp);
	अगर (count)
		*count = ar.len;
	/*
	 * Account क्रम the allocated meta blocks.  We will never
	 * fail EDQUOT क्रम metdata, but we करो account क्रम it.
	 */
	अगर (!(*errp) && (flags & EXT4_MB_DELALLOC_RESERVED)) अणु
		dquot_alloc_block_nofail(inode,
				EXT4_C2B(EXT4_SB(inode->i_sb), ar.len));
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ext4_count_मुक्त_clusters() -- count fileप्रणाली मुक्त clusters
 * @sb:		superblock
 *
 * Adds up the number of मुक्त clusters from each block group.
 */
ext4_fsblk_t ext4_count_मुक्त_clusters(काष्ठा super_block *sb)
अणु
	ext4_fsblk_t desc_count;
	काष्ठा ext4_group_desc *gdp;
	ext4_group_t i;
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	काष्ठा ext4_group_info *grp;
#अगर_घोषित EXT4FS_DEBUG
	काष्ठा ext4_super_block *es;
	ext4_fsblk_t biपंचांगap_count;
	अचिन्हित पूर्णांक x;
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;

	es = EXT4_SB(sb)->s_es;
	desc_count = 0;
	biपंचांगap_count = 0;
	gdp = शून्य;

	क्रम (i = 0; i < ngroups; i++) अणु
		gdp = ext4_get_group_desc(sb, i, शून्य);
		अगर (!gdp)
			जारी;
		grp = शून्य;
		अगर (EXT4_SB(sb)->s_group_info)
			grp = ext4_get_group_info(sb, i);
		अगर (!grp || !EXT4_MB_GRP_BBITMAP_CORRUPT(grp))
			desc_count += ext4_मुक्त_group_clusters(sb, gdp);
		brअन्यथा(biपंचांगap_bh);
		biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, i);
		अगर (IS_ERR(biपंचांगap_bh)) अणु
			biपंचांगap_bh = शून्य;
			जारी;
		पूर्ण

		x = ext4_count_मुक्त(biपंचांगap_bh->b_data,
				    EXT4_CLUSTERS_PER_GROUP(sb) / 8);
		prपूर्णांकk(KERN_DEBUG "group %u: stored = %d, counted = %u\n",
			i, ext4_मुक्त_group_clusters(sb, gdp), x);
		biपंचांगap_count += x;
	पूर्ण
	brअन्यथा(biपंचांगap_bh);
	prपूर्णांकk(KERN_DEBUG "ext4_count_free_clusters: stored = %llu"
	       ", computed = %llu, %llu\n",
	       EXT4_NUM_B2C(EXT4_SB(sb), ext4_मुक्त_blocks_count(es)),
	       desc_count, biपंचांगap_count);
	वापस biपंचांगap_count;
#अन्यथा
	desc_count = 0;
	क्रम (i = 0; i < ngroups; i++) अणु
		gdp = ext4_get_group_desc(sb, i, शून्य);
		अगर (!gdp)
			जारी;
		grp = शून्य;
		अगर (EXT4_SB(sb)->s_group_info)
			grp = ext4_get_group_info(sb, i);
		अगर (!grp || !EXT4_MB_GRP_BBITMAP_CORRUPT(grp))
			desc_count += ext4_मुक्त_group_clusters(sb, gdp);
	पूर्ण

	वापस desc_count;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक test_root(ext4_group_t a, पूर्णांक b)
अणु
	जबतक (1) अणु
		अगर (a < b)
			वापस 0;
		अगर (a == b)
			वापस 1;
		अगर ((a % b) != 0)
			वापस 0;
		a = a / b;
	पूर्ण
पूर्ण

/**
 *	ext4_bg_has_super - number of blocks used by the superblock in group
 *	@sb: superblock क्रम fileप्रणाली
 *	@group: group number to check
 *
 *	Return the number of blocks used by the superblock (primary or backup)
 *	in this group.  Currently this will be only 0 or 1.
 */
पूर्णांक ext4_bg_has_super(काष्ठा super_block *sb, ext4_group_t group)
अणु
	काष्ठा ext4_super_block *es = EXT4_SB(sb)->s_es;

	अगर (group == 0)
		वापस 1;
	अगर (ext4_has_feature_sparse_super2(sb)) अणु
		अगर (group == le32_to_cpu(es->s_backup_bgs[0]) ||
		    group == le32_to_cpu(es->s_backup_bgs[1]))
			वापस 1;
		वापस 0;
	पूर्ण
	अगर ((group <= 1) || !ext4_has_feature_sparse_super(sb))
		वापस 1;
	अगर (!(group & 1))
		वापस 0;
	अगर (test_root(group, 3) || (test_root(group, 5)) ||
	    test_root(group, 7))
		वापस 1;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ext4_bg_num_gdb_meta(काष्ठा super_block *sb,
					ext4_group_t group)
अणु
	अचिन्हित दीर्घ metagroup = group / EXT4_DESC_PER_BLOCK(sb);
	ext4_group_t first = metagroup * EXT4_DESC_PER_BLOCK(sb);
	ext4_group_t last = first + EXT4_DESC_PER_BLOCK(sb) - 1;

	अगर (group == first || group == first + 1 || group == last)
		वापस 1;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ext4_bg_num_gdb_nometa(काष्ठा super_block *sb,
					ext4_group_t group)
अणु
	अगर (!ext4_bg_has_super(sb, group))
		वापस 0;

	अगर (ext4_has_feature_meta_bg(sb))
		वापस le32_to_cpu(EXT4_SB(sb)->s_es->s_first_meta_bg);
	अन्यथा
		वापस EXT4_SB(sb)->s_gdb_count;
पूर्ण

/**
 *	ext4_bg_num_gdb - number of blocks used by the group table in group
 *	@sb: superblock क्रम fileप्रणाली
 *	@group: group number to check
 *
 *	Return the number of blocks used by the group descriptor table
 *	(primary or backup) in this group.  In the future there may be a
 *	dअगरferent number of descriptor blocks in each group.
 */
अचिन्हित दीर्घ ext4_bg_num_gdb(काष्ठा super_block *sb, ext4_group_t group)
अणु
	अचिन्हित दीर्घ first_meta_bg =
			le32_to_cpu(EXT4_SB(sb)->s_es->s_first_meta_bg);
	अचिन्हित दीर्घ metagroup = group / EXT4_DESC_PER_BLOCK(sb);

	अगर (!ext4_has_feature_meta_bg(sb) || metagroup < first_meta_bg)
		वापस ext4_bg_num_gdb_nometa(sb, group);

	वापस ext4_bg_num_gdb_meta(sb,group);

पूर्ण

/*
 * This function वापसs the number of file प्रणाली metadata clusters at
 * the beginning of a block group, including the reserved gdt blocks.
 */
अटल अचिन्हित ext4_num_base_meta_clusters(काष्ठा super_block *sb,
				     ext4_group_t block_group)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	अचिन्हित num;

	/* Check क्रम superblock and gdt backups in this group */
	num = ext4_bg_has_super(sb, block_group);

	अगर (!ext4_has_feature_meta_bg(sb) ||
	    block_group < le32_to_cpu(sbi->s_es->s_first_meta_bg) *
			  sbi->s_desc_per_block) अणु
		अगर (num) अणु
			num += ext4_bg_num_gdb(sb, block_group);
			num += le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks);
		पूर्ण
	पूर्ण अन्यथा अणु /* For META_BG_BLOCK_GROUPS */
		num += ext4_bg_num_gdb(sb, block_group);
	पूर्ण
	वापस EXT4_NUM_B2C(sbi, num);
पूर्ण
/**
 *	ext4_inode_to_goal_block - वापस a hपूर्णांक क्रम block allocation
 *	@inode: inode क्रम block allocation
 *
 *	Return the ideal location to start allocating blocks क्रम a
 *	newly created inode.
 */
ext4_fsblk_t ext4_inode_to_goal_block(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	ext4_group_t block_group;
	ext4_grpblk_t colour;
	पूर्णांक flex_size = ext4_flex_bg_size(EXT4_SB(inode->i_sb));
	ext4_fsblk_t bg_start;
	ext4_fsblk_t last_block;

	block_group = ei->i_block_group;
	अगर (flex_size >= EXT4_FLEX_SIZE_सूची_ALLOC_SCHEME) अणु
		/*
		 * If there are at least EXT4_FLEX_SIZE_सूची_ALLOC_SCHEME
		 * block groups per flexgroup, reserve the first block
		 * group क्रम directories and special files.  Regular
		 * files will start at the second block group.  This
		 * tends to speed up directory access and improves
		 * fsck बार.
		 */
		block_group &= ~(flex_size-1);
		अगर (S_ISREG(inode->i_mode))
			block_group++;
	पूर्ण
	bg_start = ext4_group_first_block_no(inode->i_sb, block_group);
	last_block = ext4_blocks_count(EXT4_SB(inode->i_sb)->s_es) - 1;

	/*
	 * If we are करोing delayed allocation, we करोn't need take
	 * colour पूर्णांकo account.
	 */
	अगर (test_opt(inode->i_sb, DELALLOC))
		वापस bg_start;

	अगर (bg_start + EXT4_BLOCKS_PER_GROUP(inode->i_sb) <= last_block)
		colour = (task_pid_nr(current) % 16) *
			(EXT4_BLOCKS_PER_GROUP(inode->i_sb) / 16);
	अन्यथा
		colour = (task_pid_nr(current) % 16) *
			((last_block - bg_start) / 16);
	वापस bg_start + colour;
पूर्ण

