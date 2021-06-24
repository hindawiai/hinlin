<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/resize.c
 *
 * Support क्रम resizing an ext4 fileप्रणाली जबतक it is mounted.
 *
 * Copyright (C) 2001, 2002 Andreas Dilger <adilger@clusterfs.com>
 *
 * This could probably be made पूर्णांकo a module, because it is not often in use.
 */


#घोषणा EXT4FS_DEBUG

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>

#समावेश "ext4_jbd2.h"

काष्ठा ext4_rcu_ptr अणु
	काष्ठा rcu_head rcu;
	व्योम *ptr;
पूर्ण;

अटल व्योम ext4_rcu_ptr_callback(काष्ठा rcu_head *head)
अणु
	काष्ठा ext4_rcu_ptr *ptr;

	ptr = container_of(head, काष्ठा ext4_rcu_ptr, rcu);
	kvमुक्त(ptr->ptr);
	kमुक्त(ptr);
पूर्ण

व्योम ext4_kvमुक्त_array_rcu(व्योम *to_मुक्त)
अणु
	काष्ठा ext4_rcu_ptr *ptr = kzalloc(माप(*ptr), GFP_KERNEL);

	अगर (ptr) अणु
		ptr->ptr = to_मुक्त;
		call_rcu(&ptr->rcu, ext4_rcu_ptr_callback);
		वापस;
	पूर्ण
	synchronize_rcu();
	kvमुक्त(to_मुक्त);
पूर्ण

पूर्णांक ext4_resize_begin(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक ret = 0;

	अगर (!capable(CAP_SYS_RESOURCE))
		वापस -EPERM;

	/*
	 * If we are not using the primary superblock/GDT copy करोn't resize,
         * because the user tools have no way of handling this.  Probably a
         * bad समय to करो it anyways.
         */
	अगर (EXT4_B2C(sbi, sbi->s_sbh->b_blocknr) !=
	    le32_to_cpu(EXT4_SB(sb)->s_es->s_first_data_block)) अणु
		ext4_warning(sb, "won't resize using backup superblock at %llu",
			(अचिन्हित दीर्घ दीर्घ)EXT4_SB(sb)->s_sbh->b_blocknr);
		वापस -EPERM;
	पूर्ण

	/*
	 * We are not allowed to करो online-resizing on a fileप्रणाली mounted
	 * with error, because it can destroy the fileप्रणाली easily.
	 */
	अगर (EXT4_SB(sb)->s_mount_state & EXT4_ERROR_FS) अणु
		ext4_warning(sb, "There are errors in the filesystem, "
			     "so online resizing is not allowed");
		वापस -EPERM;
	पूर्ण

	अगर (test_and_set_bit_lock(EXT4_FLAGS_RESIZING,
				  &EXT4_SB(sb)->s_ext4_flags))
		ret = -EBUSY;

	वापस ret;
पूर्ण

व्योम ext4_resize_end(काष्ठा super_block *sb)
अणु
	clear_bit_unlock(EXT4_FLAGS_RESIZING, &EXT4_SB(sb)->s_ext4_flags);
	smp_mb__after_atomic();
पूर्ण

अटल ext4_group_t ext4_meta_bg_first_group(काष्ठा super_block *sb,
					     ext4_group_t group) अणु
	वापस (group >> EXT4_DESC_PER_BLOCK_BITS(sb)) <<
	       EXT4_DESC_PER_BLOCK_BITS(sb);
पूर्ण

अटल ext4_fsblk_t ext4_meta_bg_first_block_no(काष्ठा super_block *sb,
					     ext4_group_t group) अणु
	group = ext4_meta_bg_first_group(sb, group);
	वापस ext4_group_first_block_no(sb, group);
पूर्ण

अटल ext4_grpblk_t ext4_group_overhead_blocks(काष्ठा super_block *sb,
						ext4_group_t group) अणु
	ext4_grpblk_t overhead;
	overhead = ext4_bg_num_gdb(sb, group);
	अगर (ext4_bg_has_super(sb, group))
		overhead += 1 +
			  le16_to_cpu(EXT4_SB(sb)->s_es->s_reserved_gdt_blocks);
	वापस overhead;
पूर्ण

#घोषणा outside(b, first, last)	((b) < (first) || (b) >= (last))
#घोषणा inside(b, first, last)	((b) >= (first) && (b) < (last))

अटल पूर्णांक verअगरy_group_input(काष्ठा super_block *sb,
			      काष्ठा ext4_new_group_data *input)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	ext4_fsblk_t start = ext4_blocks_count(es);
	ext4_fsblk_t end = start + input->blocks_count;
	ext4_group_t group = input->group;
	ext4_fsblk_t itend = input->inode_table + sbi->s_itb_per_group;
	अचिन्हित overhead;
	ext4_fsblk_t metaend;
	काष्ठा buffer_head *bh = शून्य;
	ext4_grpblk_t मुक्त_blocks_count, offset;
	पूर्णांक err = -EINVAL;

	अगर (group != sbi->s_groups_count) अणु
		ext4_warning(sb, "Cannot add at group %u (only %u groups)",
			     input->group, sbi->s_groups_count);
		वापस -EINVAL;
	पूर्ण

	overhead = ext4_group_overhead_blocks(sb, group);
	metaend = start + overhead;
	input->मुक्त_clusters_count = मुक्त_blocks_count =
		input->blocks_count - 2 - overhead - sbi->s_itb_per_group;

	अगर (test_opt(sb, DEBUG))
		prपूर्णांकk(KERN_DEBUG "EXT4-fs: adding %s group %u: %u blocks "
		       "(%d free, %u reserved)\n",
		       ext4_bg_has_super(sb, input->group) ? "normal" :
		       "no-super", input->group, input->blocks_count,
		       मुक्त_blocks_count, input->reserved_blocks);

	ext4_get_group_no_and_offset(sb, start, शून्य, &offset);
	अगर (offset != 0)
			ext4_warning(sb, "Last group not full");
	अन्यथा अगर (input->reserved_blocks > input->blocks_count / 5)
		ext4_warning(sb, "Reserved blocks too high (%u)",
			     input->reserved_blocks);
	अन्यथा अगर (मुक्त_blocks_count < 0)
		ext4_warning(sb, "Bad blocks count %u",
			     input->blocks_count);
	अन्यथा अगर (IS_ERR(bh = ext4_sb_bपढ़ो(sb, end - 1, 0))) अणु
		err = PTR_ERR(bh);
		bh = शून्य;
		ext4_warning(sb, "Cannot read last block (%llu)",
			     end - 1);
	पूर्ण अन्यथा अगर (outside(input->block_biपंचांगap, start, end))
		ext4_warning(sb, "Block bitmap not in group (block %llu)",
			     (अचिन्हित दीर्घ दीर्घ)input->block_biपंचांगap);
	अन्यथा अगर (outside(input->inode_biपंचांगap, start, end))
		ext4_warning(sb, "Inode bitmap not in group (block %llu)",
			     (अचिन्हित दीर्घ दीर्घ)input->inode_biपंचांगap);
	अन्यथा अगर (outside(input->inode_table, start, end) ||
		 outside(itend - 1, start, end))
		ext4_warning(sb, "Inode table not in group (blocks %llu-%llu)",
			     (अचिन्हित दीर्घ दीर्घ)input->inode_table, itend - 1);
	अन्यथा अगर (input->inode_biपंचांगap == input->block_biपंचांगap)
		ext4_warning(sb, "Block bitmap same as inode bitmap (%llu)",
			     (अचिन्हित दीर्घ दीर्घ)input->block_biपंचांगap);
	अन्यथा अगर (inside(input->block_biपंचांगap, input->inode_table, itend))
		ext4_warning(sb, "Block bitmap (%llu) in inode table "
			     "(%llu-%llu)",
			     (अचिन्हित दीर्घ दीर्घ)input->block_biपंचांगap,
			     (अचिन्हित दीर्घ दीर्घ)input->inode_table, itend - 1);
	अन्यथा अगर (inside(input->inode_biपंचांगap, input->inode_table, itend))
		ext4_warning(sb, "Inode bitmap (%llu) in inode table "
			     "(%llu-%llu)",
			     (अचिन्हित दीर्घ दीर्घ)input->inode_biपंचांगap,
			     (अचिन्हित दीर्घ दीर्घ)input->inode_table, itend - 1);
	अन्यथा अगर (inside(input->block_biपंचांगap, start, metaend))
		ext4_warning(sb, "Block bitmap (%llu) in GDT table (%llu-%llu)",
			     (अचिन्हित दीर्घ दीर्घ)input->block_biपंचांगap,
			     start, metaend - 1);
	अन्यथा अगर (inside(input->inode_biपंचांगap, start, metaend))
		ext4_warning(sb, "Inode bitmap (%llu) in GDT table (%llu-%llu)",
			     (अचिन्हित दीर्घ दीर्घ)input->inode_biपंचांगap,
			     start, metaend - 1);
	अन्यथा अगर (inside(input->inode_table, start, metaend) ||
		 inside(itend - 1, start, metaend))
		ext4_warning(sb, "Inode table (%llu-%llu) overlaps GDT table "
			     "(%llu-%llu)",
			     (अचिन्हित दीर्घ दीर्घ)input->inode_table,
			     itend - 1, start, metaend - 1);
	अन्यथा
		err = 0;
	brअन्यथा(bh);

	वापस err;
पूर्ण

/*
 * ext4_new_flex_group_data is used by 64bit-resize पूर्णांकerface to add a flex
 * group each समय.
 */
काष्ठा ext4_new_flex_group_data अणु
	काष्ठा ext4_new_group_data *groups;	/* new_group_data क्रम groups
						   in the flex group */
	__u16 *bg_flags;			/* block group flags of groups
						   in @groups */
	ext4_group_t count;			/* number of groups in @groups
						 */
पूर्ण;

/*
 * alloc_flex_gd() allocates a ext4_new_flex_group_data with size of
 * @flexbg_size.
 *
 * Returns शून्य on failure otherwise address of the allocated काष्ठाure.
 */
अटल काष्ठा ext4_new_flex_group_data *alloc_flex_gd(अचिन्हित दीर्घ flexbg_size)
अणु
	काष्ठा ext4_new_flex_group_data *flex_gd;

	flex_gd = kदो_स्मृति(माप(*flex_gd), GFP_NOFS);
	अगर (flex_gd == शून्य)
		जाओ out3;

	अगर (flexbg_size >= अच_पूर्णांक_उच्च / माप(काष्ठा ext4_new_group_data))
		जाओ out2;
	flex_gd->count = flexbg_size;

	flex_gd->groups = kदो_स्मृति_array(flexbg_size,
					माप(काष्ठा ext4_new_group_data),
					GFP_NOFS);
	अगर (flex_gd->groups == शून्य)
		जाओ out2;

	flex_gd->bg_flags = kदो_स्मृति_array(flexbg_size, माप(__u16),
					  GFP_NOFS);
	अगर (flex_gd->bg_flags == शून्य)
		जाओ out1;

	वापस flex_gd;

out1:
	kमुक्त(flex_gd->groups);
out2:
	kमुक्त(flex_gd);
out3:
	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_flex_gd(काष्ठा ext4_new_flex_group_data *flex_gd)
अणु
	kमुक्त(flex_gd->bg_flags);
	kमुक्त(flex_gd->groups);
	kमुक्त(flex_gd);
पूर्ण

/*
 * ext4_alloc_group_tables() allocates block biपंचांगaps, inode biपंचांगaps
 * and inode tables क्रम a flex group.
 *
 * This function is used by 64bit-resize.  Note that this function allocates
 * group tables from the 1st group of groups contained by @flexgd, which may
 * be a partial of a flex group.
 *
 * @sb: super block of fs to which the groups beदीर्घs
 *
 * Returns 0 on a successful allocation of the metadata blocks in the
 * block group.
 */
अटल पूर्णांक ext4_alloc_group_tables(काष्ठा super_block *sb,
				काष्ठा ext4_new_flex_group_data *flex_gd,
				पूर्णांक flexbg_size)
अणु
	काष्ठा ext4_new_group_data *group_data = flex_gd->groups;
	ext4_fsblk_t start_blk;
	ext4_fsblk_t last_blk;
	ext4_group_t src_group;
	ext4_group_t bb_index = 0;
	ext4_group_t ib_index = 0;
	ext4_group_t it_index = 0;
	ext4_group_t group;
	ext4_group_t last_group;
	अचिन्हित overhead;
	__u16 uninit_mask = (flexbg_size > 1) ? ~EXT4_BG_BLOCK_UNINIT : ~0;
	पूर्णांक i;

	BUG_ON(flex_gd->count == 0 || group_data == शून्य);

	src_group = group_data[0].group;
	last_group  = src_group + flex_gd->count - 1;

	BUG_ON((flexbg_size > 1) && ((src_group & ~(flexbg_size - 1)) !=
	       (last_group & ~(flexbg_size - 1))));
next_group:
	group = group_data[0].group;
	अगर (src_group >= group_data[0].group + flex_gd->count)
		वापस -ENOSPC;
	start_blk = ext4_group_first_block_no(sb, src_group);
	last_blk = start_blk + group_data[src_group - group].blocks_count;

	overhead = ext4_group_overhead_blocks(sb, src_group);

	start_blk += overhead;

	/* We collect contiguous blocks as much as possible. */
	src_group++;
	क्रम (; src_group <= last_group; src_group++) अणु
		overhead = ext4_group_overhead_blocks(sb, src_group);
		अगर (overhead == 0)
			last_blk += group_data[src_group - group].blocks_count;
		अन्यथा
			अवरोध;
	पूर्ण

	/* Allocate block biपंचांगaps */
	क्रम (; bb_index < flex_gd->count; bb_index++) अणु
		अगर (start_blk >= last_blk)
			जाओ next_group;
		group_data[bb_index].block_biपंचांगap = start_blk++;
		group = ext4_get_group_number(sb, start_blk - 1);
		group -= group_data[0].group;
		group_data[group].mdata_blocks++;
		flex_gd->bg_flags[group] &= uninit_mask;
	पूर्ण

	/* Allocate inode biपंचांगaps */
	क्रम (; ib_index < flex_gd->count; ib_index++) अणु
		अगर (start_blk >= last_blk)
			जाओ next_group;
		group_data[ib_index].inode_biपंचांगap = start_blk++;
		group = ext4_get_group_number(sb, start_blk - 1);
		group -= group_data[0].group;
		group_data[group].mdata_blocks++;
		flex_gd->bg_flags[group] &= uninit_mask;
	पूर्ण

	/* Allocate inode tables */
	क्रम (; it_index < flex_gd->count; it_index++) अणु
		अचिन्हित पूर्णांक itb = EXT4_SB(sb)->s_itb_per_group;
		ext4_fsblk_t next_group_start;

		अगर (start_blk + itb > last_blk)
			जाओ next_group;
		group_data[it_index].inode_table = start_blk;
		group = ext4_get_group_number(sb, start_blk);
		next_group_start = ext4_group_first_block_no(sb, group + 1);
		group -= group_data[0].group;

		अगर (start_blk + itb > next_group_start) अणु
			flex_gd->bg_flags[group + 1] &= uninit_mask;
			overhead = start_blk + itb - next_group_start;
			group_data[group + 1].mdata_blocks += overhead;
			itb -= overhead;
		पूर्ण

		group_data[group].mdata_blocks += itb;
		flex_gd->bg_flags[group] &= uninit_mask;
		start_blk += EXT4_SB(sb)->s_itb_per_group;
	पूर्ण

	/* Update मुक्त clusters count to exclude metadata blocks */
	क्रम (i = 0; i < flex_gd->count; i++) अणु
		group_data[i].मुक्त_clusters_count -=
				EXT4_NUM_B2C(EXT4_SB(sb),
					     group_data[i].mdata_blocks);
	पूर्ण

	अगर (test_opt(sb, DEBUG)) अणु
		पूर्णांक i;
		group = group_data[0].group;

		prपूर्णांकk(KERN_DEBUG "EXT4-fs: adding a flex group with "
		       "%d groups, flexbg size is %d:\n", flex_gd->count,
		       flexbg_size);

		क्रम (i = 0; i < flex_gd->count; i++) अणु
			ext4_debug(
			       "adding %s group %u: %u blocks (%d free, %d mdata blocks)\n",
			       ext4_bg_has_super(sb, group + i) ? "normal" :
			       "no-super", group + i,
			       group_data[i].blocks_count,
			       group_data[i].मुक्त_clusters_count,
			       group_data[i].mdata_blocks);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा buffer_head *bclean(handle_t *handle, काष्ठा super_block *sb,
				  ext4_fsblk_t blk)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक err;

	bh = sb_getblk(sb, blk);
	अगर (unlikely(!bh))
		वापस ERR_PTR(-ENOMEM);
	BUFFER_TRACE(bh, "get_write_access");
	अगर ((err = ext4_journal_get_ग_लिखो_access(handle, bh))) अणु
		brअन्यथा(bh);
		bh = ERR_PTR(err);
	पूर्ण अन्यथा अणु
		स_रखो(bh->b_data, 0, sb->s_blocksize);
		set_buffer_uptodate(bh);
	पूर्ण

	वापस bh;
पूर्ण

अटल पूर्णांक ext4_resize_ensure_credits_batch(handle_t *handle, पूर्णांक credits)
अणु
	वापस ext4_journal_ensure_credits_fn(handle, credits,
		EXT4_MAX_TRANS_DATA, 0, 0);
पूर्ण

/*
 * set_flexbg_block_biपंचांगap() mark clusters [@first_cluster, @last_cluster] used.
 *
 * Helper function क्रम ext4_setup_new_group_blocks() which set .
 *
 * @sb: super block
 * @handle: journal handle
 * @flex_gd: flex group data
 */
अटल पूर्णांक set_flexbg_block_biपंचांगap(काष्ठा super_block *sb, handle_t *handle,
			काष्ठा ext4_new_flex_group_data *flex_gd,
			ext4_fsblk_t first_cluster, ext4_fsblk_t last_cluster)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_group_t count = last_cluster - first_cluster + 1;
	ext4_group_t count2;

	ext4_debug("mark clusters [%llu-%llu] used\n", first_cluster,
		   last_cluster);
	क्रम (count2 = count; count > 0;
	     count -= count2, first_cluster += count2) अणु
		ext4_fsblk_t start;
		काष्ठा buffer_head *bh;
		ext4_group_t group;
		पूर्णांक err;

		group = ext4_get_group_number(sb, EXT4_C2B(sbi, first_cluster));
		start = EXT4_B2C(sbi, ext4_group_first_block_no(sb, group));
		group -= flex_gd->groups[0].group;

		count2 = EXT4_CLUSTERS_PER_GROUP(sb) - (first_cluster - start);
		अगर (count2 > count)
			count2 = count;

		अगर (flex_gd->bg_flags[group] & EXT4_BG_BLOCK_UNINIT) अणु
			BUG_ON(flex_gd->count > 1);
			जारी;
		पूर्ण

		err = ext4_resize_ensure_credits_batch(handle, 1);
		अगर (err < 0)
			वापस err;

		bh = sb_getblk(sb, flex_gd->groups[group].block_biपंचांगap);
		अगर (unlikely(!bh))
			वापस -ENOMEM;

		BUFFER_TRACE(bh, "get_write_access");
		err = ext4_journal_get_ग_लिखो_access(handle, bh);
		अगर (err) अणु
			brअन्यथा(bh);
			वापस err;
		पूर्ण
		ext4_debug("mark block bitmap %#04llx (+%llu/%u)\n",
			   first_cluster, first_cluster - start, count2);
		ext4_set_bits(bh->b_data, first_cluster - start, count2);

		err = ext4_handle_dirty_metadata(handle, शून्य, bh);
		brअन्यथा(bh);
		अगर (unlikely(err))
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set up the block and inode biपंचांगaps, and the inode table क्रम the new groups.
 * This करोesn't need to be part of the मुख्य transaction, since we are only
 * changing blocks outside the actual fileप्रणाली.  We still करो journaling to
 * ensure the recovery is correct in हाल of a failure just after resize.
 * If any part of this fails, we simply पात the resize.
 *
 * setup_new_flex_group_blocks handles a flex group as follow:
 *  1. copy super block and GDT, and initialize group tables अगर necessary.
 *     In this step, we only set bits in blocks biपंचांगaps क्रम blocks taken by
 *     super block and GDT.
 *  2. allocate group tables in block biपंचांगaps, that is, set bits in block
 *     biपंचांगap क्रम blocks taken by group tables.
 */
अटल पूर्णांक setup_new_flex_group_blocks(काष्ठा super_block *sb,
				काष्ठा ext4_new_flex_group_data *flex_gd)
अणु
	पूर्णांक group_table_count[] = अणु1, 1, EXT4_SB(sb)->s_itb_per_groupपूर्ण;
	ext4_fsblk_t start;
	ext4_fsblk_t block;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	काष्ठा ext4_new_group_data *group_data = flex_gd->groups;
	__u16 *bg_flags = flex_gd->bg_flags;
	handle_t *handle;
	ext4_group_t group, count;
	काष्ठा buffer_head *bh = शून्य;
	पूर्णांक reserved_gdb, i, j, err = 0, err2;
	पूर्णांक meta_bg;

	BUG_ON(!flex_gd->count || !group_data ||
	       group_data[0].group != sbi->s_groups_count);

	reserved_gdb = le16_to_cpu(es->s_reserved_gdt_blocks);
	meta_bg = ext4_has_feature_meta_bg(sb);

	/* This transaction may be extended/restarted aदीर्घ the way */
	handle = ext4_journal_start_sb(sb, EXT4_HT_RESIZE, EXT4_MAX_TRANS_DATA);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	group = group_data[0].group;
	क्रम (i = 0; i < flex_gd->count; i++, group++) अणु
		अचिन्हित दीर्घ gdblocks;
		ext4_grpblk_t overhead;

		gdblocks = ext4_bg_num_gdb(sb, group);
		start = ext4_group_first_block_no(sb, group);

		अगर (meta_bg == 0 && !ext4_bg_has_super(sb, group))
			जाओ handle_itb;

		अगर (meta_bg == 1) अणु
			ext4_group_t first_group;
			first_group = ext4_meta_bg_first_group(sb, group);
			अगर (first_group != group + 1 &&
			    first_group != group + EXT4_DESC_PER_BLOCK(sb) - 1)
				जाओ handle_itb;
		पूर्ण

		block = start + ext4_bg_has_super(sb, group);
		/* Copy all of the GDT blocks पूर्णांकo the backup in this group */
		क्रम (j = 0; j < gdblocks; j++, block++) अणु
			काष्ठा buffer_head *gdb;

			ext4_debug("update backup group %#04llx\n", block);
			err = ext4_resize_ensure_credits_batch(handle, 1);
			अगर (err < 0)
				जाओ out;

			gdb = sb_getblk(sb, block);
			अगर (unlikely(!gdb)) अणु
				err = -ENOMEM;
				जाओ out;
			पूर्ण

			BUFFER_TRACE(gdb, "get_write_access");
			err = ext4_journal_get_ग_लिखो_access(handle, gdb);
			अगर (err) अणु
				brअन्यथा(gdb);
				जाओ out;
			पूर्ण
			स_नकल(gdb->b_data, sbi_array_rcu_deref(sbi,
				s_group_desc, j)->b_data, gdb->b_size);
			set_buffer_uptodate(gdb);

			err = ext4_handle_dirty_metadata(handle, शून्य, gdb);
			अगर (unlikely(err)) अणु
				brअन्यथा(gdb);
				जाओ out;
			पूर्ण
			brअन्यथा(gdb);
		पूर्ण

		/* Zero out all of the reserved backup group descriptor
		 * table blocks
		 */
		अगर (ext4_bg_has_super(sb, group)) अणु
			err = sb_issue_zeroout(sb, gdblocks + start + 1,
					reserved_gdb, GFP_NOFS);
			अगर (err)
				जाओ out;
		पूर्ण

handle_itb:
		/* Initialize group tables of the grop @group */
		अगर (!(bg_flags[i] & EXT4_BG_INODE_ZEROED))
			जाओ handle_bb;

		/* Zero out all of the inode table blocks */
		block = group_data[i].inode_table;
		ext4_debug("clear inode table blocks %#04llx -> %#04lx\n",
			   block, sbi->s_itb_per_group);
		err = sb_issue_zeroout(sb, block, sbi->s_itb_per_group,
				       GFP_NOFS);
		अगर (err)
			जाओ out;

handle_bb:
		अगर (bg_flags[i] & EXT4_BG_BLOCK_UNINIT)
			जाओ handle_ib;

		/* Initialize block biपंचांगap of the @group */
		block = group_data[i].block_biपंचांगap;
		err = ext4_resize_ensure_credits_batch(handle, 1);
		अगर (err < 0)
			जाओ out;

		bh = bclean(handle, sb, block);
		अगर (IS_ERR(bh)) अणु
			err = PTR_ERR(bh);
			जाओ out;
		पूर्ण
		overhead = ext4_group_overhead_blocks(sb, group);
		अगर (overhead != 0) अणु
			ext4_debug("mark backup superblock %#04llx (+0)\n",
				   start);
			ext4_set_bits(bh->b_data, 0,
				      EXT4_NUM_B2C(sbi, overhead));
		पूर्ण
		ext4_mark_biपंचांगap_end(EXT4_B2C(sbi, group_data[i].blocks_count),
				     sb->s_blocksize * 8, bh->b_data);
		err = ext4_handle_dirty_metadata(handle, शून्य, bh);
		brअन्यथा(bh);
		अगर (err)
			जाओ out;

handle_ib:
		अगर (bg_flags[i] & EXT4_BG_INODE_UNINIT)
			जारी;

		/* Initialize inode biपंचांगap of the @group */
		block = group_data[i].inode_biपंचांगap;
		err = ext4_resize_ensure_credits_batch(handle, 1);
		अगर (err < 0)
			जाओ out;
		/* Mark unused entries in inode biपंचांगap used */
		bh = bclean(handle, sb, block);
		अगर (IS_ERR(bh)) अणु
			err = PTR_ERR(bh);
			जाओ out;
		पूर्ण

		ext4_mark_biपंचांगap_end(EXT4_INODES_PER_GROUP(sb),
				     sb->s_blocksize * 8, bh->b_data);
		err = ext4_handle_dirty_metadata(handle, शून्य, bh);
		brअन्यथा(bh);
		अगर (err)
			जाओ out;
	पूर्ण

	/* Mark group tables in block biपंचांगap */
	क्रम (j = 0; j < GROUP_TABLE_COUNT; j++) अणु
		count = group_table_count[j];
		start = (&group_data[0].block_biपंचांगap)[j];
		block = start;
		क्रम (i = 1; i < flex_gd->count; i++) अणु
			block += group_table_count[j];
			अगर (block == (&group_data[i].block_biपंचांगap)[j]) अणु
				count += group_table_count[j];
				जारी;
			पूर्ण
			err = set_flexbg_block_biपंचांगap(sb, handle,
						      flex_gd,
						      EXT4_B2C(sbi, start),
						      EXT4_B2C(sbi,
							       start + count
							       - 1));
			अगर (err)
				जाओ out;
			count = group_table_count[j];
			start = (&group_data[i].block_biपंचांगap)[j];
			block = start;
		पूर्ण

		अगर (count) अणु
			err = set_flexbg_block_biपंचांगap(sb, handle,
						      flex_gd,
						      EXT4_B2C(sbi, start),
						      EXT4_B2C(sbi,
							       start + count
							       - 1));
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	err2 = ext4_journal_stop(handle);
	अगर (err2 && !err)
		err = err2;

	वापस err;
पूर्ण

/*
 * Iterate through the groups which hold BACKUP superblock/GDT copies in an
 * ext4 fileप्रणाली.  The counters should be initialized to 1, 5, and 7 beक्रमe
 * calling this क्रम the first समय.  In a sparse fileप्रणाली it will be the
 * sequence of घातers of 3, 5, and 7: 1, 3, 5, 7, 9, 25, 27, 49, 81, ...
 * For a non-sparse fileप्रणाली it will be every group: 1, 2, 3, 4, ...
 */
अटल अचिन्हित ext4_list_backups(काष्ठा super_block *sb, अचिन्हित *three,
				  अचिन्हित *five, अचिन्हित *seven)
अणु
	अचिन्हित *min = three;
	पूर्णांक mult = 3;
	अचिन्हित ret;

	अगर (!ext4_has_feature_sparse_super(sb)) अणु
		ret = *min;
		*min += 1;
		वापस ret;
	पूर्ण

	अगर (*five < *min) अणु
		min = five;
		mult = 5;
	पूर्ण
	अगर (*seven < *min) अणु
		min = seven;
		mult = 7;
	पूर्ण

	ret = *min;
	*min *= mult;

	वापस ret;
पूर्ण

/*
 * Check that all of the backup GDT blocks are held in the primary GDT block.
 * It is assumed that they are stored in group order.  Returns the number of
 * groups in current fileप्रणाली that have BACKUPS, or -ve error code.
 */
अटल पूर्णांक verअगरy_reserved_gdb(काष्ठा super_block *sb,
			       ext4_group_t end,
			       काष्ठा buffer_head *primary)
अणु
	स्थिर ext4_fsblk_t blk = primary->b_blocknr;
	अचिन्हित three = 1;
	अचिन्हित five = 5;
	अचिन्हित seven = 7;
	अचिन्हित grp;
	__le32 *p = (__le32 *)primary->b_data;
	पूर्णांक gdbackups = 0;

	जबतक ((grp = ext4_list_backups(sb, &three, &five, &seven)) < end) अणु
		अगर (le32_to_cpu(*p++) !=
		    grp * EXT4_BLOCKS_PER_GROUP(sb) + blk)अणु
			ext4_warning(sb, "reserved GDT %llu"
				     " missing grp %d (%llu)",
				     blk, grp,
				     grp *
				     (ext4_fsblk_t)EXT4_BLOCKS_PER_GROUP(sb) +
				     blk);
			वापस -EINVAL;
		पूर्ण
		अगर (++gdbackups > EXT4_ADDR_PER_BLOCK(sb))
			वापस -EFBIG;
	पूर्ण

	वापस gdbackups;
पूर्ण

/*
 * Called when we need to bring a reserved group descriptor table block पूर्णांकo
 * use from the resize inode.  The primary copy of the new GDT block currently
 * is an indirect block (under the द्विगुन indirect block in the resize inode).
 * The new backup GDT blocks will be stored as leaf blocks in this indirect
 * block, in group order.  Even though we know all the block numbers we need,
 * we check to ensure that the resize inode has actually reserved these blocks.
 *
 * Don't need to update the block biपंचांगaps because the blocks are still in use.
 *
 * We get all of the error हालs out of the way, so that we are sure to not
 * fail once we start modअगरying the data on disk, because JBD has no rollback.
 */
अटल पूर्णांक add_new_gdb(handle_t *handle, काष्ठा inode *inode,
		       ext4_group_t group)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ext4_super_block *es = EXT4_SB(sb)->s_es;
	अचिन्हित दीर्घ gdb_num = group / EXT4_DESC_PER_BLOCK(sb);
	ext4_fsblk_t gdblock = EXT4_SB(sb)->s_sbh->b_blocknr + 1 + gdb_num;
	काष्ठा buffer_head **o_group_desc, **n_group_desc = शून्य;
	काष्ठा buffer_head *dind = शून्य;
	काष्ठा buffer_head *gdb_bh = शून्य;
	पूर्णांक gdbackups;
	काष्ठा ext4_iloc iloc = अणु .bh = शून्य पूर्ण;
	__le32 *data;
	पूर्णांक err;

	अगर (test_opt(sb, DEBUG))
		prपूर्णांकk(KERN_DEBUG
		       "EXT4-fs: ext4_add_new_gdb: adding group block %lu\n",
		       gdb_num);

	gdb_bh = ext4_sb_bपढ़ो(sb, gdblock, 0);
	अगर (IS_ERR(gdb_bh))
		वापस PTR_ERR(gdb_bh);

	gdbackups = verअगरy_reserved_gdb(sb, group, gdb_bh);
	अगर (gdbackups < 0) अणु
		err = gdbackups;
		जाओ errout;
	पूर्ण

	data = EXT4_I(inode)->i_data + EXT4_DIND_BLOCK;
	dind = ext4_sb_bपढ़ो(sb, le32_to_cpu(*data), 0);
	अगर (IS_ERR(dind)) अणु
		err = PTR_ERR(dind);
		dind = शून्य;
		जाओ errout;
	पूर्ण

	data = (__le32 *)dind->b_data;
	अगर (le32_to_cpu(data[gdb_num % EXT4_ADDR_PER_BLOCK(sb)]) != gdblock) अणु
		ext4_warning(sb, "new group %u GDT block %llu not reserved",
			     group, gdblock);
		err = -EINVAL;
		जाओ errout;
	पूर्ण

	BUFFER_TRACE(EXT4_SB(sb)->s_sbh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, EXT4_SB(sb)->s_sbh);
	अगर (unlikely(err))
		जाओ errout;

	BUFFER_TRACE(gdb_bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, gdb_bh);
	अगर (unlikely(err))
		जाओ errout;

	BUFFER_TRACE(dind, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, dind);
	अगर (unlikely(err)) अणु
		ext4_std_error(sb, err);
		जाओ errout;
	पूर्ण

	/* ext4_reserve_inode_ग_लिखो() माला_लो a reference on the iloc */
	err = ext4_reserve_inode_ग_लिखो(handle, inode, &iloc);
	अगर (unlikely(err))
		जाओ errout;

	n_group_desc = kvदो_स्मृति((gdb_num + 1) * माप(काष्ठा buffer_head *),
				GFP_KERNEL);
	अगर (!n_group_desc) अणु
		err = -ENOMEM;
		ext4_warning(sb, "not enough memory for %lu groups",
			     gdb_num + 1);
		जाओ errout;
	पूर्ण

	/*
	 * Finally, we have all of the possible failures behind us...
	 *
	 * Remove new GDT block from inode द्विगुन-indirect block and clear out
	 * the new GDT block क्रम use (which also "frees" the backup GDT blocks
	 * from the reserved inode).  We करोn't need to change the biपंचांगaps क्रम
	 * these blocks, because they are marked as in-use from being in the
	 * reserved inode, and will become GDT blocks (primary and backup).
	 */
	data[gdb_num % EXT4_ADDR_PER_BLOCK(sb)] = 0;
	err = ext4_handle_dirty_metadata(handle, शून्य, dind);
	अगर (unlikely(err)) अणु
		ext4_std_error(sb, err);
		जाओ errout;
	पूर्ण
	inode->i_blocks -= (gdbackups + 1) * sb->s_blocksize >>
			   (9 - EXT4_SB(sb)->s_cluster_bits);
	ext4_mark_iloc_dirty(handle, inode, &iloc);
	स_रखो(gdb_bh->b_data, 0, sb->s_blocksize);
	err = ext4_handle_dirty_metadata(handle, शून्य, gdb_bh);
	अगर (unlikely(err)) अणु
		ext4_std_error(sb, err);
		iloc.bh = शून्य;
		जाओ errout;
	पूर्ण
	brअन्यथा(dind);

	rcu_पढ़ो_lock();
	o_group_desc = rcu_dereference(EXT4_SB(sb)->s_group_desc);
	स_नकल(n_group_desc, o_group_desc,
	       EXT4_SB(sb)->s_gdb_count * माप(काष्ठा buffer_head *));
	rcu_पढ़ो_unlock();
	n_group_desc[gdb_num] = gdb_bh;
	rcu_assign_poपूर्णांकer(EXT4_SB(sb)->s_group_desc, n_group_desc);
	EXT4_SB(sb)->s_gdb_count++;
	ext4_kvमुक्त_array_rcu(o_group_desc);

	lock_buffer(EXT4_SB(sb)->s_sbh);
	le16_add_cpu(&es->s_reserved_gdt_blocks, -1);
	ext4_superblock_csum_set(sb);
	unlock_buffer(EXT4_SB(sb)->s_sbh);
	err = ext4_handle_dirty_metadata(handle, शून्य, EXT4_SB(sb)->s_sbh);
	अगर (err)
		ext4_std_error(sb, err);
	वापस err;
errout:
	kvमुक्त(n_group_desc);
	brअन्यथा(iloc.bh);
	brअन्यथा(dind);
	brअन्यथा(gdb_bh);

	ext4_debug("leaving with error %d\n", err);
	वापस err;
पूर्ण

/*
 * add_new_gdb_meta_bg is the sister of add_new_gdb.
 */
अटल पूर्णांक add_new_gdb_meta_bg(काष्ठा super_block *sb,
			       handle_t *handle, ext4_group_t group) अणु
	ext4_fsblk_t gdblock;
	काष्ठा buffer_head *gdb_bh;
	काष्ठा buffer_head **o_group_desc, **n_group_desc;
	अचिन्हित दीर्घ gdb_num = group / EXT4_DESC_PER_BLOCK(sb);
	पूर्णांक err;

	gdblock = ext4_meta_bg_first_block_no(sb, group) +
		   ext4_bg_has_super(sb, group);
	gdb_bh = ext4_sb_bपढ़ो(sb, gdblock, 0);
	अगर (IS_ERR(gdb_bh))
		वापस PTR_ERR(gdb_bh);
	n_group_desc = kvदो_स्मृति((gdb_num + 1) * माप(काष्ठा buffer_head *),
				GFP_KERNEL);
	अगर (!n_group_desc) अणु
		brअन्यथा(gdb_bh);
		err = -ENOMEM;
		ext4_warning(sb, "not enough memory for %lu groups",
			     gdb_num + 1);
		वापस err;
	पूर्ण

	rcu_पढ़ो_lock();
	o_group_desc = rcu_dereference(EXT4_SB(sb)->s_group_desc);
	स_नकल(n_group_desc, o_group_desc,
	       EXT4_SB(sb)->s_gdb_count * माप(काष्ठा buffer_head *));
	rcu_पढ़ो_unlock();
	n_group_desc[gdb_num] = gdb_bh;

	BUFFER_TRACE(gdb_bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, gdb_bh);
	अगर (err) अणु
		kvमुक्त(n_group_desc);
		brअन्यथा(gdb_bh);
		वापस err;
	पूर्ण

	rcu_assign_poपूर्णांकer(EXT4_SB(sb)->s_group_desc, n_group_desc);
	EXT4_SB(sb)->s_gdb_count++;
	ext4_kvमुक्त_array_rcu(o_group_desc);
	वापस err;
पूर्ण

/*
 * Called when we are adding a new group which has a backup copy of each of
 * the GDT blocks (i.e. sparse group) and there are reserved GDT blocks.
 * We need to add these reserved backup GDT blocks to the resize inode, so
 * that they are kept क्रम future resizing and not allocated to files.
 *
 * Each reserved backup GDT block will go पूर्णांकo a dअगरferent indirect block.
 * The indirect blocks are actually the primary reserved GDT blocks,
 * so we know in advance what their block numbers are.  We only get the
 * द्विगुन-indirect block to verअगरy it is poपूर्णांकing to the primary reserved
 * GDT blocks so we करोn't overग_लिखो a data block by accident.  The reserved
 * backup GDT blocks are stored in their reserved primary GDT block.
 */
अटल पूर्णांक reserve_backup_gdb(handle_t *handle, काष्ठा inode *inode,
			      ext4_group_t group)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक reserved_gdb =le16_to_cpu(EXT4_SB(sb)->s_es->s_reserved_gdt_blocks);
	पूर्णांक cluster_bits = EXT4_SB(sb)->s_cluster_bits;
	काष्ठा buffer_head **primary;
	काष्ठा buffer_head *dind;
	काष्ठा ext4_iloc iloc;
	ext4_fsblk_t blk;
	__le32 *data, *end;
	पूर्णांक gdbackups = 0;
	पूर्णांक res, i;
	पूर्णांक err;

	primary = kदो_स्मृति_array(reserved_gdb, माप(*primary), GFP_NOFS);
	अगर (!primary)
		वापस -ENOMEM;

	data = EXT4_I(inode)->i_data + EXT4_DIND_BLOCK;
	dind = ext4_sb_bपढ़ो(sb, le32_to_cpu(*data), 0);
	अगर (IS_ERR(dind)) अणु
		err = PTR_ERR(dind);
		dind = शून्य;
		जाओ निकास_मुक्त;
	पूर्ण

	blk = EXT4_SB(sb)->s_sbh->b_blocknr + 1 + EXT4_SB(sb)->s_gdb_count;
	data = (__le32 *)dind->b_data + (EXT4_SB(sb)->s_gdb_count %
					 EXT4_ADDR_PER_BLOCK(sb));
	end = (__le32 *)dind->b_data + EXT4_ADDR_PER_BLOCK(sb);

	/* Get each reserved primary GDT block and verअगरy it holds backups */
	क्रम (res = 0; res < reserved_gdb; res++, blk++) अणु
		अगर (le32_to_cpu(*data) != blk) अणु
			ext4_warning(sb, "reserved block %llu"
				     " not at offset %ld",
				     blk,
				     (दीर्घ)(data - (__le32 *)dind->b_data));
			err = -EINVAL;
			जाओ निकास_bh;
		पूर्ण
		primary[res] = ext4_sb_bपढ़ो(sb, blk, 0);
		अगर (IS_ERR(primary[res])) अणु
			err = PTR_ERR(primary[res]);
			primary[res] = शून्य;
			जाओ निकास_bh;
		पूर्ण
		gdbackups = verअगरy_reserved_gdb(sb, group, primary[res]);
		अगर (gdbackups < 0) अणु
			brअन्यथा(primary[res]);
			err = gdbackups;
			जाओ निकास_bh;
		पूर्ण
		अगर (++data >= end)
			data = (__le32 *)dind->b_data;
	पूर्ण

	क्रम (i = 0; i < reserved_gdb; i++) अणु
		BUFFER_TRACE(primary[i], "get_write_access");
		अगर ((err = ext4_journal_get_ग_लिखो_access(handle, primary[i])))
			जाओ निकास_bh;
	पूर्ण

	अगर ((err = ext4_reserve_inode_ग_लिखो(handle, inode, &iloc)))
		जाओ निकास_bh;

	/*
	 * Finally we can add each of the reserved backup GDT blocks from
	 * the new group to its reserved primary GDT block.
	 */
	blk = group * EXT4_BLOCKS_PER_GROUP(sb);
	क्रम (i = 0; i < reserved_gdb; i++) अणु
		पूर्णांक err2;
		data = (__le32 *)primary[i]->b_data;
		/* prपूर्णांकk("reserving backup %lu[%u] = %lu\n",
		       primary[i]->b_blocknr, gdbackups,
		       blk + primary[i]->b_blocknr); */
		data[gdbackups] = cpu_to_le32(blk + primary[i]->b_blocknr);
		err2 = ext4_handle_dirty_metadata(handle, शून्य, primary[i]);
		अगर (!err)
			err = err2;
	पूर्ण

	inode->i_blocks += reserved_gdb * sb->s_blocksize >> (9 - cluster_bits);
	ext4_mark_iloc_dirty(handle, inode, &iloc);

निकास_bh:
	जबतक (--res >= 0)
		brअन्यथा(primary[res]);
	brअन्यथा(dind);

निकास_मुक्त:
	kमुक्त(primary);

	वापस err;
पूर्ण

/*
 * Update the backup copies of the ext4 metadata.  These करोn't need to be part
 * of the मुख्य resize transaction, because e2fsck will re-ग_लिखो them अगर there
 * is a problem (basically only OOM will cause a problem).  However, we
 * _should_ update the backups अगर possible, in हाल the primary माला_लो trashed
 * क्रम some reason and we need to run e2fsck from a backup superblock.  The
 * important part is that the new block and inode counts are in the backup
 * superblocks, and the location of the new group metadata in the GDT backups.
 *
 * We करो not need take the s_resize_lock क्रम this, because these
 * blocks are not otherwise touched by the fileप्रणाली code when it is
 * mounted.  We करोn't need to worry about last changing from
 * sbi->s_groups_count, because the worst that can happen is that we
 * करो not copy the full number of backups at this समय.  The resize
 * which changed s_groups_count will backup again.
 */
अटल व्योम update_backups(काष्ठा super_block *sb, sector_t blk_off, अक्षर *data,
			   पूर्णांक size, पूर्णांक meta_bg)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_group_t last;
	स्थिर पूर्णांक bpg = EXT4_BLOCKS_PER_GROUP(sb);
	अचिन्हित three = 1;
	अचिन्हित five = 5;
	अचिन्हित seven = 7;
	ext4_group_t group = 0;
	पूर्णांक rest = sb->s_blocksize - size;
	handle_t *handle;
	पूर्णांक err = 0, err2;

	handle = ext4_journal_start_sb(sb, EXT4_HT_RESIZE, EXT4_MAX_TRANS_DATA);
	अगर (IS_ERR(handle)) अणु
		group = 1;
		err = PTR_ERR(handle);
		जाओ निकास_err;
	पूर्ण

	अगर (meta_bg == 0) अणु
		group = ext4_list_backups(sb, &three, &five, &seven);
		last = sbi->s_groups_count;
	पूर्ण अन्यथा अणु
		group = ext4_get_group_number(sb, blk_off) + 1;
		last = (ext4_group_t)(group + EXT4_DESC_PER_BLOCK(sb) - 2);
	पूर्ण

	जबतक (group < sbi->s_groups_count) अणु
		काष्ठा buffer_head *bh;
		ext4_fsblk_t backup_block;

		/* Out of journal space, and can't get more - पात - so sad */
		err = ext4_resize_ensure_credits_batch(handle, 1);
		अगर (err < 0)
			अवरोध;

		अगर (meta_bg == 0)
			backup_block = ((ext4_fsblk_t)group) * bpg + blk_off;
		अन्यथा
			backup_block = (ext4_group_first_block_no(sb, group) +
					ext4_bg_has_super(sb, group));

		bh = sb_getblk(sb, backup_block);
		अगर (unlikely(!bh)) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण
		ext4_debug("update metadata backup %llu(+%llu)\n",
			   backup_block, backup_block -
			   ext4_group_first_block_no(sb, group));
		BUFFER_TRACE(bh, "get_write_access");
		अगर ((err = ext4_journal_get_ग_लिखो_access(handle, bh))) अणु
			brअन्यथा(bh);
			अवरोध;
		पूर्ण
		lock_buffer(bh);
		स_नकल(bh->b_data, data, size);
		अगर (rest)
			स_रखो(bh->b_data + size, 0, rest);
		set_buffer_uptodate(bh);
		unlock_buffer(bh);
		err = ext4_handle_dirty_metadata(handle, शून्य, bh);
		अगर (unlikely(err))
			ext4_std_error(sb, err);
		brअन्यथा(bh);

		अगर (meta_bg == 0)
			group = ext4_list_backups(sb, &three, &five, &seven);
		अन्यथा अगर (group == last)
			अवरोध;
		अन्यथा
			group = last;
	पूर्ण
	अगर ((err2 = ext4_journal_stop(handle)) && !err)
		err = err2;

	/*
	 * Ugh! Need to have e2fsck ग_लिखो the backup copies.  It is too
	 * late to revert the resize, we shouldn't fail just because of
	 * the backup copies (they are only needed in हाल of corruption).
	 *
	 * However, अगर we got here we have a journal problem too, so we
	 * can't really start a transaction to mark the superblock.
	 * Chicken out and just set the flag on the hope it will be written
	 * to disk, and अगर not - we will simply रुको until next fsck.
	 */
निकास_err:
	अगर (err) अणु
		ext4_warning(sb, "can't update backup for group %u (err %d), "
			     "forcing fsck on next reboot", group, err);
		sbi->s_mount_state &= ~EXT4_VALID_FS;
		sbi->s_es->s_state &= cpu_to_le16(~EXT4_VALID_FS);
		mark_buffer_dirty(sbi->s_sbh);
	पूर्ण
पूर्ण

/*
 * ext4_add_new_descs() adds @count group descriptor of groups
 * starting at @group
 *
 * @handle: journal handle
 * @sb: super block
 * @group: the group no. of the first group desc to be added
 * @resize_inode: the resize inode
 * @count: number of group descriptors to be added
 */
अटल पूर्णांक ext4_add_new_descs(handle_t *handle, काष्ठा super_block *sb,
			      ext4_group_t group, काष्ठा inode *resize_inode,
			      ext4_group_t count)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	काष्ठा buffer_head *gdb_bh;
	पूर्णांक i, gdb_off, gdb_num, err = 0;
	पूर्णांक meta_bg;

	meta_bg = ext4_has_feature_meta_bg(sb);
	क्रम (i = 0; i < count; i++, group++) अणु
		पूर्णांक reserved_gdb = ext4_bg_has_super(sb, group) ?
			le16_to_cpu(es->s_reserved_gdt_blocks) : 0;

		gdb_off = group % EXT4_DESC_PER_BLOCK(sb);
		gdb_num = group / EXT4_DESC_PER_BLOCK(sb);

		/*
		 * We will only either add reserved group blocks to a backup group
		 * or हटाओ reserved blocks क्रम the first group in a new group block.
		 * Doing both would be mean more complex code, and sane people करोn't
		 * use non-sparse fileप्रणालीs anymore.  This is alपढ़ोy checked above.
		 */
		अगर (gdb_off) अणु
			gdb_bh = sbi_array_rcu_deref(sbi, s_group_desc,
						     gdb_num);
			BUFFER_TRACE(gdb_bh, "get_write_access");
			err = ext4_journal_get_ग_लिखो_access(handle, gdb_bh);

			अगर (!err && reserved_gdb && ext4_bg_num_gdb(sb, group))
				err = reserve_backup_gdb(handle, resize_inode, group);
		पूर्ण अन्यथा अगर (meta_bg != 0) अणु
			err = add_new_gdb_meta_bg(sb, handle, group);
		पूर्ण अन्यथा अणु
			err = add_new_gdb(handle, resize_inode, group);
		पूर्ण
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा buffer_head *ext4_get_biपंचांगap(काष्ठा super_block *sb, __u64 block)
अणु
	काष्ठा buffer_head *bh = sb_getblk(sb, block);
	अगर (unlikely(!bh))
		वापस शून्य;
	अगर (!bh_uptodate_or_lock(bh)) अणु
		अगर (ext4_पढ़ो_bh(bh, 0, शून्य) < 0) अणु
			brअन्यथा(bh);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस bh;
पूर्ण

अटल पूर्णांक ext4_set_biपंचांगap_checksums(काष्ठा super_block *sb,
				     ext4_group_t group,
				     काष्ठा ext4_group_desc *gdp,
				     काष्ठा ext4_new_group_data *group_data)
अणु
	काष्ठा buffer_head *bh;

	अगर (!ext4_has_metadata_csum(sb))
		वापस 0;

	bh = ext4_get_biपंचांगap(sb, group_data->inode_biपंचांगap);
	अगर (!bh)
		वापस -EIO;
	ext4_inode_biपंचांगap_csum_set(sb, group, gdp, bh,
				   EXT4_INODES_PER_GROUP(sb) / 8);
	brअन्यथा(bh);

	bh = ext4_get_biपंचांगap(sb, group_data->block_biपंचांगap);
	अगर (!bh)
		वापस -EIO;
	ext4_block_biपंचांगap_csum_set(sb, group, gdp, bh);
	brअन्यथा(bh);

	वापस 0;
पूर्ण

/*
 * ext4_setup_new_descs() will set up the group descriptor descriptors of a flex bg
 */
अटल पूर्णांक ext4_setup_new_descs(handle_t *handle, काष्ठा super_block *sb,
				काष्ठा ext4_new_flex_group_data *flex_gd)
अणु
	काष्ठा ext4_new_group_data	*group_data = flex_gd->groups;
	काष्ठा ext4_group_desc		*gdp;
	काष्ठा ext4_sb_info		*sbi = EXT4_SB(sb);
	काष्ठा buffer_head		*gdb_bh;
	ext4_group_t			group;
	__u16				*bg_flags = flex_gd->bg_flags;
	पूर्णांक				i, gdb_off, gdb_num, err = 0;


	क्रम (i = 0; i < flex_gd->count; i++, group_data++, bg_flags++) अणु
		group = group_data->group;

		gdb_off = group % EXT4_DESC_PER_BLOCK(sb);
		gdb_num = group / EXT4_DESC_PER_BLOCK(sb);

		/*
		 * get_ग_लिखो_access() has been called on gdb_bh by ext4_add_new_desc().
		 */
		gdb_bh = sbi_array_rcu_deref(sbi, s_group_desc, gdb_num);
		/* Update group descriptor block क्रम new group */
		gdp = (काष्ठा ext4_group_desc *)(gdb_bh->b_data +
						 gdb_off * EXT4_DESC_SIZE(sb));

		स_रखो(gdp, 0, EXT4_DESC_SIZE(sb));
		ext4_block_biपंचांगap_set(sb, gdp, group_data->block_biपंचांगap);
		ext4_inode_biपंचांगap_set(sb, gdp, group_data->inode_biपंचांगap);
		err = ext4_set_biपंचांगap_checksums(sb, group, gdp, group_data);
		अगर (err) अणु
			ext4_std_error(sb, err);
			अवरोध;
		पूर्ण

		ext4_inode_table_set(sb, gdp, group_data->inode_table);
		ext4_मुक्त_group_clusters_set(sb, gdp,
					     group_data->मुक्त_clusters_count);
		ext4_मुक्त_inodes_set(sb, gdp, EXT4_INODES_PER_GROUP(sb));
		अगर (ext4_has_group_desc_csum(sb))
			ext4_itable_unused_set(sb, gdp,
					       EXT4_INODES_PER_GROUP(sb));
		gdp->bg_flags = cpu_to_le16(*bg_flags);
		ext4_group_desc_csum_set(sb, group, gdp);

		err = ext4_handle_dirty_metadata(handle, शून्य, gdb_bh);
		अगर (unlikely(err)) अणु
			ext4_std_error(sb, err);
			अवरोध;
		पूर्ण

		/*
		 * We can allocate memory क्रम mb_alloc based on the new group
		 * descriptor
		 */
		err = ext4_mb_add_groupinfo(sb, group, gdp);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/*
 * ext4_update_super() updates the super block so that the newly added
 * groups can be seen by the fileप्रणाली.
 *
 * @sb: super block
 * @flex_gd: new added groups
 */
अटल व्योम ext4_update_super(काष्ठा super_block *sb,
			     काष्ठा ext4_new_flex_group_data *flex_gd)
अणु
	ext4_fsblk_t blocks_count = 0;
	ext4_fsblk_t मुक्त_blocks = 0;
	ext4_fsblk_t reserved_blocks = 0;
	काष्ठा ext4_new_group_data *group_data = flex_gd->groups;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	पूर्णांक i;

	BUG_ON(flex_gd->count == 0 || group_data == शून्य);
	/*
	 * Make the new blocks and inodes valid next.  We करो this beक्रमe
	 * increasing the group count so that once the group is enabled,
	 * all of its blocks and inodes are alपढ़ोy valid.
	 *
	 * We always allocate group-by-group, then block-by-block or
	 * inode-by-inode within a group, so enabling these
	 * blocks/inodes beक्रमe the group is live won't actually let us
	 * allocate the new space yet.
	 */
	क्रम (i = 0; i < flex_gd->count; i++) अणु
		blocks_count += group_data[i].blocks_count;
		मुक्त_blocks += EXT4_C2B(sbi, group_data[i].मुक्त_clusters_count);
	पूर्ण

	reserved_blocks = ext4_r_blocks_count(es) * 100;
	reserved_blocks = भाग64_u64(reserved_blocks, ext4_blocks_count(es));
	reserved_blocks *= blocks_count;
	करो_भाग(reserved_blocks, 100);

	lock_buffer(sbi->s_sbh);
	ext4_blocks_count_set(es, ext4_blocks_count(es) + blocks_count);
	ext4_मुक्त_blocks_count_set(es, ext4_मुक्त_blocks_count(es) + मुक्त_blocks);
	le32_add_cpu(&es->s_inodes_count, EXT4_INODES_PER_GROUP(sb) *
		     flex_gd->count);
	le32_add_cpu(&es->s_मुक्त_inodes_count, EXT4_INODES_PER_GROUP(sb) *
		     flex_gd->count);

	ext4_debug("free blocks count %llu", ext4_मुक्त_blocks_count(es));
	/*
	 * We need to protect s_groups_count against other CPUs seeing
	 * inconsistent state in the superblock.
	 *
	 * The precise rules we use are:
	 *
	 * * Writers must perक्रमm a smp_wmb() after updating all
	 *   dependent data and beक्रमe modअगरying the groups count
	 *
	 * * Readers must perक्रमm an smp_rmb() after पढ़ोing the groups
	 *   count and beक्रमe पढ़ोing any dependent data.
	 *
	 * NB. These rules can be relaxed when checking the group count
	 * जबतक मुक्तing data, as we can only allocate from a block
	 * group after serialising against the group count, and we can
	 * only then मुक्त after serialising in turn against that
	 * allocation.
	 */
	smp_wmb();

	/* Update the global fs size fields */
	sbi->s_groups_count += flex_gd->count;
	sbi->s_blockfile_groups = min_t(ext4_group_t, sbi->s_groups_count,
			(EXT4_MAX_BLOCK_खाता_PHYS / EXT4_BLOCKS_PER_GROUP(sb)));

	/* Update the reserved block counts only once the new group is
	 * active. */
	ext4_r_blocks_count_set(es, ext4_r_blocks_count(es) +
				reserved_blocks);
	ext4_superblock_csum_set(sb);
	unlock_buffer(sbi->s_sbh);

	/* Update the मुक्त space counts */
	percpu_counter_add(&sbi->s_मुक्तclusters_counter,
			   EXT4_NUM_B2C(sbi, मुक्त_blocks));
	percpu_counter_add(&sbi->s_मुक्तinodes_counter,
			   EXT4_INODES_PER_GROUP(sb) * flex_gd->count);

	ext4_debug("free blocks count %llu",
		   percpu_counter_पढ़ो(&sbi->s_मुक्तclusters_counter));
	अगर (ext4_has_feature_flex_bg(sb) && sbi->s_log_groups_per_flex) अणु
		ext4_group_t flex_group;
		काष्ठा flex_groups *fg;

		flex_group = ext4_flex_group(sbi, group_data[0].group);
		fg = sbi_array_rcu_deref(sbi, s_flex_groups, flex_group);
		atomic64_add(EXT4_NUM_B2C(sbi, मुक्त_blocks),
			     &fg->मुक्त_clusters);
		atomic_add(EXT4_INODES_PER_GROUP(sb) * flex_gd->count,
			   &fg->मुक्त_inodes);
	पूर्ण

	/*
	 * Update the fs overhead inक्रमmation
	 */
	ext4_calculate_overhead(sb);

	अगर (test_opt(sb, DEBUG))
		prपूर्णांकk(KERN_DEBUG "EXT4-fs: added group %u:"
		       "%llu blocks(%llu free %llu reserved)\n", flex_gd->count,
		       blocks_count, मुक्त_blocks, reserved_blocks);
पूर्ण

/* Add a flex group to an fs. Ensure we handle all possible error conditions
 * _beक्रमe_ we start modअगरying the fileप्रणाली, because we cannot पात the
 * transaction and not have it ग_लिखो the data to disk.
 */
अटल पूर्णांक ext4_flex_group_add(काष्ठा super_block *sb,
			       काष्ठा inode *resize_inode,
			       काष्ठा ext4_new_flex_group_data *flex_gd)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	ext4_fsblk_t o_blocks_count;
	ext4_grpblk_t last;
	ext4_group_t group;
	handle_t *handle;
	अचिन्हित reserved_gdb;
	पूर्णांक err = 0, err2 = 0, credit;

	BUG_ON(!flex_gd->count || !flex_gd->groups || !flex_gd->bg_flags);

	reserved_gdb = le16_to_cpu(es->s_reserved_gdt_blocks);
	o_blocks_count = ext4_blocks_count(es);
	ext4_get_group_no_and_offset(sb, o_blocks_count, &group, &last);
	BUG_ON(last);

	err = setup_new_flex_group_blocks(sb, flex_gd);
	अगर (err)
		जाओ निकास;
	/*
	 * We will always be modअगरying at least the superblock and  GDT
	 * blocks.  If we are adding a group past the last current GDT block,
	 * we will also modअगरy the inode and the dindirect block.  If we
	 * are adding a group with superblock/GDT backups  we will also
	 * modअगरy each of the reserved GDT dindirect blocks.
	 */
	credit = 3;	/* sb, resize inode, resize inode dindirect */
	/* GDT blocks */
	credit += 1 + DIV_ROUND_UP(flex_gd->count, EXT4_DESC_PER_BLOCK(sb));
	credit += reserved_gdb;	/* Reserved GDT dindirect blocks */
	handle = ext4_journal_start_sb(sb, EXT4_HT_RESIZE, credit);
	अगर (IS_ERR(handle)) अणु
		err = PTR_ERR(handle);
		जाओ निकास;
	पूर्ण

	BUFFER_TRACE(sbi->s_sbh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, sbi->s_sbh);
	अगर (err)
		जाओ निकास_journal;

	group = flex_gd->groups[0].group;
	BUG_ON(group != sbi->s_groups_count);
	err = ext4_add_new_descs(handle, sb, group,
				resize_inode, flex_gd->count);
	अगर (err)
		जाओ निकास_journal;

	err = ext4_setup_new_descs(handle, sb, flex_gd);
	अगर (err)
		जाओ निकास_journal;

	ext4_update_super(sb, flex_gd);

	err = ext4_handle_dirty_metadata(handle, शून्य, sbi->s_sbh);

निकास_journal:
	err2 = ext4_journal_stop(handle);
	अगर (!err)
		err = err2;

	अगर (!err) अणु
		पूर्णांक gdb_num = group / EXT4_DESC_PER_BLOCK(sb);
		पूर्णांक gdb_num_end = ((group + flex_gd->count - 1) /
				   EXT4_DESC_PER_BLOCK(sb));
		पूर्णांक meta_bg = ext4_has_feature_meta_bg(sb);
		sector_t old_gdb = 0;

		update_backups(sb, sbi->s_sbh->b_blocknr, (अक्षर *)es,
			       माप(काष्ठा ext4_super_block), 0);
		क्रम (; gdb_num <= gdb_num_end; gdb_num++) अणु
			काष्ठा buffer_head *gdb_bh;

			gdb_bh = sbi_array_rcu_deref(sbi, s_group_desc,
						     gdb_num);
			अगर (old_gdb == gdb_bh->b_blocknr)
				जारी;
			update_backups(sb, gdb_bh->b_blocknr, gdb_bh->b_data,
				       gdb_bh->b_size, meta_bg);
			old_gdb = gdb_bh->b_blocknr;
		पूर्ण
	पूर्ण
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक ext4_setup_next_flex_gd(काष्ठा super_block *sb,
				    काष्ठा ext4_new_flex_group_data *flex_gd,
				    ext4_fsblk_t n_blocks_count,
				    अचिन्हित दीर्घ flexbg_size)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	काष्ठा ext4_new_group_data *group_data = flex_gd->groups;
	ext4_fsblk_t o_blocks_count;
	ext4_group_t n_group;
	ext4_group_t group;
	ext4_group_t last_group;
	ext4_grpblk_t last;
	ext4_grpblk_t clusters_per_group;
	अचिन्हित दीर्घ i;

	clusters_per_group = EXT4_CLUSTERS_PER_GROUP(sb);

	o_blocks_count = ext4_blocks_count(es);

	अगर (o_blocks_count == n_blocks_count)
		वापस 0;

	ext4_get_group_no_and_offset(sb, o_blocks_count, &group, &last);
	BUG_ON(last);
	ext4_get_group_no_and_offset(sb, n_blocks_count - 1, &n_group, &last);

	last_group = group | (flexbg_size - 1);
	अगर (last_group > n_group)
		last_group = n_group;

	flex_gd->count = last_group - group + 1;

	क्रम (i = 0; i < flex_gd->count; i++) अणु
		पूर्णांक overhead;

		group_data[i].group = group + i;
		group_data[i].blocks_count = EXT4_BLOCKS_PER_GROUP(sb);
		overhead = ext4_group_overhead_blocks(sb, group + i);
		group_data[i].mdata_blocks = overhead;
		group_data[i].मुक्त_clusters_count = EXT4_CLUSTERS_PER_GROUP(sb);
		अगर (ext4_has_group_desc_csum(sb)) अणु
			flex_gd->bg_flags[i] = EXT4_BG_BLOCK_UNINIT |
					       EXT4_BG_INODE_UNINIT;
			अगर (!test_opt(sb, INIT_INODE_TABLE))
				flex_gd->bg_flags[i] |= EXT4_BG_INODE_ZEROED;
		पूर्ण अन्यथा
			flex_gd->bg_flags[i] = EXT4_BG_INODE_ZEROED;
	पूर्ण

	अगर (last_group == n_group && ext4_has_group_desc_csum(sb))
		/* We need to initialize block biपंचांगap of last group. */
		flex_gd->bg_flags[i - 1] &= ~EXT4_BG_BLOCK_UNINIT;

	अगर ((last_group == n_group) && (last != clusters_per_group - 1)) अणु
		group_data[i - 1].blocks_count = EXT4_C2B(sbi, last + 1);
		group_data[i - 1].मुक्त_clusters_count -= clusters_per_group -
						       last - 1;
	पूर्ण

	वापस 1;
पूर्ण

/* Add group descriptor data to an existing or new group descriptor block.
 * Ensure we handle all possible error conditions _beक्रमe_ we start modअगरying
 * the fileप्रणाली, because we cannot पात the transaction and not have it
 * ग_लिखो the data to disk.
 *
 * If we are on a GDT block boundary, we need to get the reserved GDT block.
 * Otherwise, we may need to add backup GDT blocks क्रम a sparse group.
 *
 * We only need to hold the superblock lock जबतक we are actually adding
 * in the new group's counts to the superblock.  Prior to that we have
 * not really "added" the group at all.  We re-check that we are still
 * adding in the last group in हाल things have changed since verअगरying.
 */
पूर्णांक ext4_group_add(काष्ठा super_block *sb, काष्ठा ext4_new_group_data *input)
अणु
	काष्ठा ext4_new_flex_group_data flex_gd;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	पूर्णांक reserved_gdb = ext4_bg_has_super(sb, input->group) ?
		le16_to_cpu(es->s_reserved_gdt_blocks) : 0;
	काष्ठा inode *inode = शून्य;
	पूर्णांक gdb_off;
	पूर्णांक err;
	__u16 bg_flags = 0;

	gdb_off = input->group % EXT4_DESC_PER_BLOCK(sb);

	अगर (gdb_off == 0 && !ext4_has_feature_sparse_super(sb)) अणु
		ext4_warning(sb, "Can't resize non-sparse filesystem further");
		वापस -EPERM;
	पूर्ण

	अगर (ext4_blocks_count(es) + input->blocks_count <
	    ext4_blocks_count(es)) अणु
		ext4_warning(sb, "blocks_count overflow");
		वापस -EINVAL;
	पूर्ण

	अगर (le32_to_cpu(es->s_inodes_count) + EXT4_INODES_PER_GROUP(sb) <
	    le32_to_cpu(es->s_inodes_count)) अणु
		ext4_warning(sb, "inodes_count overflow");
		वापस -EINVAL;
	पूर्ण

	अगर (reserved_gdb || gdb_off == 0) अणु
		अगर (!ext4_has_feature_resize_inode(sb) ||
		    !le16_to_cpu(es->s_reserved_gdt_blocks)) अणु
			ext4_warning(sb,
				     "No reserved GDT blocks, can't resize");
			वापस -EPERM;
		पूर्ण
		inode = ext4_iget(sb, EXT4_RESIZE_INO, EXT4_IGET_SPECIAL);
		अगर (IS_ERR(inode)) अणु
			ext4_warning(sb, "Error opening resize inode");
			वापस PTR_ERR(inode);
		पूर्ण
	पूर्ण


	err = verअगरy_group_input(sb, input);
	अगर (err)
		जाओ out;

	err = ext4_alloc_flex_bg_array(sb, input->group + 1);
	अगर (err)
		जाओ out;

	err = ext4_mb_alloc_groupinfo(sb, input->group + 1);
	अगर (err)
		जाओ out;

	flex_gd.count = 1;
	flex_gd.groups = input;
	flex_gd.bg_flags = &bg_flags;
	err = ext4_flex_group_add(sb, inode, &flex_gd);
out:
	iput(inode);
	वापस err;
पूर्ण /* ext4_group_add */

/*
 * extend a group without checking assuming that checking has been करोne.
 */
अटल पूर्णांक ext4_group_extend_no_check(काष्ठा super_block *sb,
				      ext4_fsblk_t o_blocks_count, ext4_grpblk_t add)
अणु
	काष्ठा ext4_super_block *es = EXT4_SB(sb)->s_es;
	handle_t *handle;
	पूर्णांक err = 0, err2;

	/* We will update the superblock, one block biपंचांगap, and
	 * one group descriptor via ext4_group_add_blocks().
	 */
	handle = ext4_journal_start_sb(sb, EXT4_HT_RESIZE, 3);
	अगर (IS_ERR(handle)) अणु
		err = PTR_ERR(handle);
		ext4_warning(sb, "error %d on journal start", err);
		वापस err;
	पूर्ण

	BUFFER_TRACE(EXT4_SB(sb)->s_sbh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, EXT4_SB(sb)->s_sbh);
	अगर (err) अणु
		ext4_warning(sb, "error %d on journal write access", err);
		जाओ errout;
	पूर्ण

	lock_buffer(EXT4_SB(sb)->s_sbh);
	ext4_blocks_count_set(es, o_blocks_count + add);
	ext4_मुक्त_blocks_count_set(es, ext4_मुक्त_blocks_count(es) + add);
	ext4_superblock_csum_set(sb);
	unlock_buffer(EXT4_SB(sb)->s_sbh);
	ext4_debug("freeing blocks %llu through %llu\n", o_blocks_count,
		   o_blocks_count + add);
	/* We add the blocks to the biपंचांगap and set the group need init bit */
	err = ext4_group_add_blocks(handle, sb, o_blocks_count, add);
	अगर (err)
		जाओ errout;
	ext4_handle_dirty_metadata(handle, शून्य, EXT4_SB(sb)->s_sbh);
	ext4_debug("freed blocks %llu through %llu\n", o_blocks_count,
		   o_blocks_count + add);
errout:
	err2 = ext4_journal_stop(handle);
	अगर (err2 && !err)
		err = err2;

	अगर (!err) अणु
		अगर (test_opt(sb, DEBUG))
			prपूर्णांकk(KERN_DEBUG "EXT4-fs: extended group to %llu "
			       "blocks\n", ext4_blocks_count(es));
		update_backups(sb, EXT4_SB(sb)->s_sbh->b_blocknr,
			       (अक्षर *)es, माप(काष्ठा ext4_super_block), 0);
	पूर्ण
	वापस err;
पूर्ण

/*
 * Extend the fileप्रणाली to the new number of blocks specअगरied.  This entry
 * poपूर्णांक is only used to extend the current fileप्रणाली to the end of the last
 * existing group.  It can be accessed via ioctl, or by "remount,resize=<size>"
 * क्रम emergencies (because it has no dependencies on reserved blocks).
 *
 * If we _really_ wanted, we could use शेष values to call ext4_group_add()
 * allow the "remount" trick to work क्रम arbitrary resizing, assuming enough
 * GDT blocks are reserved to grow to the desired size.
 */
पूर्णांक ext4_group_extend(काष्ठा super_block *sb, काष्ठा ext4_super_block *es,
		      ext4_fsblk_t n_blocks_count)
अणु
	ext4_fsblk_t o_blocks_count;
	ext4_grpblk_t last;
	ext4_grpblk_t add;
	काष्ठा buffer_head *bh;
	पूर्णांक err;
	ext4_group_t group;

	o_blocks_count = ext4_blocks_count(es);

	अगर (test_opt(sb, DEBUG))
		ext4_msg(sb, KERN_DEBUG,
			 "extending last group from %llu to %llu blocks",
			 o_blocks_count, n_blocks_count);

	अगर (n_blocks_count == 0 || n_blocks_count == o_blocks_count)
		वापस 0;

	अगर (n_blocks_count > (sector_t)(~0ULL) >> (sb->s_blocksize_bits - 9)) अणु
		ext4_msg(sb, KERN_ERR,
			 "filesystem too large to resize to %llu blocks safely",
			 n_blocks_count);
		वापस -EINVAL;
	पूर्ण

	अगर (n_blocks_count < o_blocks_count) अणु
		ext4_warning(sb, "can't shrink FS - resize aborted");
		वापस -EINVAL;
	पूर्ण

	/* Handle the reमुख्यing blocks in the last group only. */
	ext4_get_group_no_and_offset(sb, o_blocks_count, &group, &last);

	अगर (last == 0) अणु
		ext4_warning(sb, "need to use ext2online to resize further");
		वापस -EPERM;
	पूर्ण

	add = EXT4_BLOCKS_PER_GROUP(sb) - last;

	अगर (o_blocks_count + add < o_blocks_count) अणु
		ext4_warning(sb, "blocks_count overflow");
		वापस -EINVAL;
	पूर्ण

	अगर (o_blocks_count + add > n_blocks_count)
		add = n_blocks_count - o_blocks_count;

	अगर (o_blocks_count + add < n_blocks_count)
		ext4_warning(sb, "will only finish group (%llu blocks, %u new)",
			     o_blocks_count + add, add);

	/* See अगर the device is actually as big as what was requested */
	bh = ext4_sb_bपढ़ो(sb, o_blocks_count + add - 1, 0);
	अगर (IS_ERR(bh)) अणु
		ext4_warning(sb, "can't read last block, resize aborted");
		वापस -ENOSPC;
	पूर्ण
	brअन्यथा(bh);

	err = ext4_group_extend_no_check(sb, o_blocks_count, add);
	वापस err;
पूर्ण /* ext4_group_extend */


अटल पूर्णांक num_desc_blocks(काष्ठा super_block *sb, ext4_group_t groups)
अणु
	वापस (groups + EXT4_DESC_PER_BLOCK(sb) - 1) / EXT4_DESC_PER_BLOCK(sb);
पूर्ण

/*
 * Release the resize inode and drop the resize_inode feature अगर there
 * are no more reserved gdt blocks, and then convert the file प्रणाली
 * to enable meta_bg
 */
अटल पूर्णांक ext4_convert_meta_bg(काष्ठा super_block *sb, काष्ठा inode *inode)
अणु
	handle_t *handle;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	ext4_fsblk_t nr;
	पूर्णांक i, ret, err = 0;
	पूर्णांक credits = 1;

	ext4_msg(sb, KERN_INFO, "Converting file system to meta_bg");
	अगर (inode) अणु
		अगर (es->s_reserved_gdt_blocks) अणु
			ext4_error(sb, "Unexpected non-zero "
				   "s_reserved_gdt_blocks");
			वापस -EPERM;
		पूर्ण

		/* Do a quick sanity check of the resize inode */
		अगर (inode->i_blocks != 1 << (inode->i_blkbits -
					     (9 - sbi->s_cluster_bits)))
			जाओ invalid_resize_inode;
		क्रम (i = 0; i < EXT4_N_BLOCKS; i++) अणु
			अगर (i == EXT4_DIND_BLOCK) अणु
				अगर (ei->i_data[i])
					जारी;
				अन्यथा
					जाओ invalid_resize_inode;
			पूर्ण
			अगर (ei->i_data[i])
				जाओ invalid_resize_inode;
		पूर्ण
		credits += 3;	/* block biपंचांगap, bg descriptor, resize inode */
	पूर्ण

	handle = ext4_journal_start_sb(sb, EXT4_HT_RESIZE, credits);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	BUFFER_TRACE(sbi->s_sbh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, sbi->s_sbh);
	अगर (err)
		जाओ errout;

	lock_buffer(sbi->s_sbh);
	ext4_clear_feature_resize_inode(sb);
	ext4_set_feature_meta_bg(sb);
	sbi->s_es->s_first_meta_bg =
		cpu_to_le32(num_desc_blocks(sb, sbi->s_groups_count));
	ext4_superblock_csum_set(sb);
	unlock_buffer(sbi->s_sbh);

	err = ext4_handle_dirty_metadata(handle, शून्य, sbi->s_sbh);
	अगर (err) अणु
		ext4_std_error(sb, err);
		जाओ errout;
	पूर्ण

	अगर (inode) अणु
		nr = le32_to_cpu(ei->i_data[EXT4_DIND_BLOCK]);
		ext4_मुक्त_blocks(handle, inode, शून्य, nr, 1,
				 EXT4_FREE_BLOCKS_METADATA |
				 EXT4_FREE_BLOCKS_FORGET);
		ei->i_data[EXT4_DIND_BLOCK] = 0;
		inode->i_blocks = 0;

		err = ext4_mark_inode_dirty(handle, inode);
		अगर (err)
			ext4_std_error(sb, err);
	पूर्ण

errout:
	ret = ext4_journal_stop(handle);
	अगर (!err)
		err = ret;
	वापस ret;

invalid_resize_inode:
	ext4_error(sb, "corrupted/inconsistent resize inode");
	वापस -EINVAL;
पूर्ण

/*
 * ext4_resize_fs() resizes a fs to new size specअगरied by @n_blocks_count
 *
 * @sb: super block of the fs to be resized
 * @n_blocks_count: the number of blocks resides in the resized fs
 */
पूर्णांक ext4_resize_fs(काष्ठा super_block *sb, ext4_fsblk_t n_blocks_count)
अणु
	काष्ठा ext4_new_flex_group_data *flex_gd = शून्य;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	काष्ठा buffer_head *bh;
	काष्ठा inode *resize_inode = शून्य;
	ext4_grpblk_t add, offset;
	अचिन्हित दीर्घ n_desc_blocks;
	अचिन्हित दीर्घ o_desc_blocks;
	ext4_group_t o_group;
	ext4_group_t n_group;
	ext4_fsblk_t o_blocks_count;
	ext4_fsblk_t n_blocks_count_retry = 0;
	अचिन्हित दीर्घ last_update_समय = 0;
	पूर्णांक err = 0, flexbg_size = 1 << sbi->s_log_groups_per_flex;
	पूर्णांक meta_bg;

	/* See अगर the device is actually as big as what was requested */
	bh = ext4_sb_bपढ़ो(sb, n_blocks_count - 1, 0);
	अगर (IS_ERR(bh)) अणु
		ext4_warning(sb, "can't read last block, resize aborted");
		वापस -ENOSPC;
	पूर्ण
	brअन्यथा(bh);

retry:
	o_blocks_count = ext4_blocks_count(es);

	ext4_msg(sb, KERN_INFO, "resizing filesystem from %llu "
		 "to %llu blocks", o_blocks_count, n_blocks_count);

	अगर (n_blocks_count < o_blocks_count) अणु
		/* On-line shrinking not supported */
		ext4_warning(sb, "can't shrink FS - resize aborted");
		वापस -EINVAL;
	पूर्ण

	अगर (n_blocks_count == o_blocks_count)
		/* Nothing need to करो */
		वापस 0;

	n_group = ext4_get_group_number(sb, n_blocks_count - 1);
	अगर (n_group >= (0xFFFFFFFFUL / EXT4_INODES_PER_GROUP(sb))) अणु
		ext4_warning(sb, "resize would cause inodes_count overflow");
		वापस -EINVAL;
	पूर्ण
	ext4_get_group_no_and_offset(sb, o_blocks_count - 1, &o_group, &offset);

	n_desc_blocks = num_desc_blocks(sb, n_group + 1);
	o_desc_blocks = num_desc_blocks(sb, sbi->s_groups_count);

	meta_bg = ext4_has_feature_meta_bg(sb);

	अगर (ext4_has_feature_resize_inode(sb)) अणु
		अगर (meta_bg) अणु
			ext4_error(sb, "resize_inode and meta_bg enabled "
				   "simultaneously");
			वापस -EINVAL;
		पूर्ण
		अगर (n_desc_blocks > o_desc_blocks +
		    le16_to_cpu(es->s_reserved_gdt_blocks)) अणु
			n_blocks_count_retry = n_blocks_count;
			n_desc_blocks = o_desc_blocks +
				le16_to_cpu(es->s_reserved_gdt_blocks);
			n_group = n_desc_blocks * EXT4_DESC_PER_BLOCK(sb);
			n_blocks_count = (ext4_fsblk_t)n_group *
				EXT4_BLOCKS_PER_GROUP(sb) +
				le32_to_cpu(es->s_first_data_block);
			n_group--; /* set to last group number */
		पूर्ण

		अगर (!resize_inode)
			resize_inode = ext4_iget(sb, EXT4_RESIZE_INO,
						 EXT4_IGET_SPECIAL);
		अगर (IS_ERR(resize_inode)) अणु
			ext4_warning(sb, "Error opening resize inode");
			वापस PTR_ERR(resize_inode);
		पूर्ण
	पूर्ण

	अगर ((!resize_inode && !meta_bg) || n_blocks_count == o_blocks_count) अणु
		err = ext4_convert_meta_bg(sb, resize_inode);
		अगर (err)
			जाओ out;
		अगर (resize_inode) अणु
			iput(resize_inode);
			resize_inode = शून्य;
		पूर्ण
		अगर (n_blocks_count_retry) अणु
			n_blocks_count = n_blocks_count_retry;
			n_blocks_count_retry = 0;
			जाओ retry;
		पूर्ण
	पूर्ण

	/*
	 * Make sure the last group has enough space so that it's
	 * guaranteed to have enough space क्रम all metadata blocks
	 * that it might need to hold.  (We might not need to store
	 * the inode table blocks in the last block group, but there
	 * will be हालs where this might be needed.)
	 */
	अगर ((ext4_group_first_block_no(sb, n_group) +
	     ext4_group_overhead_blocks(sb, n_group) + 2 +
	     sbi->s_itb_per_group + sbi->s_cluster_ratio) >= n_blocks_count) अणु
		n_blocks_count = ext4_group_first_block_no(sb, n_group);
		n_group--;
		n_blocks_count_retry = 0;
		अगर (resize_inode) अणु
			iput(resize_inode);
			resize_inode = शून्य;
		पूर्ण
		जाओ retry;
	पूर्ण

	/* extend the last group */
	अगर (n_group == o_group)
		add = n_blocks_count - o_blocks_count;
	अन्यथा
		add = EXT4_C2B(sbi, EXT4_CLUSTERS_PER_GROUP(sb) - (offset + 1));
	अगर (add > 0) अणु
		err = ext4_group_extend_no_check(sb, o_blocks_count, add);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (ext4_blocks_count(es) == n_blocks_count)
		जाओ out;

	err = ext4_alloc_flex_bg_array(sb, n_group + 1);
	अगर (err)
		जाओ out;

	err = ext4_mb_alloc_groupinfo(sb, n_group + 1);
	अगर (err)
		जाओ out;

	flex_gd = alloc_flex_gd(flexbg_size);
	अगर (flex_gd == शून्य) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Add flex groups. Note that a regular group is a
	 * flex group with 1 group.
	 */
	जबतक (ext4_setup_next_flex_gd(sb, flex_gd, n_blocks_count,
					      flexbg_size)) अणु
		अगर (jअगरfies - last_update_समय > HZ * 10) अणु
			अगर (last_update_समय)
				ext4_msg(sb, KERN_INFO,
					 "resized to %llu blocks",
					 ext4_blocks_count(es));
			last_update_समय = jअगरfies;
		पूर्ण
		अगर (ext4_alloc_group_tables(sb, flex_gd, flexbg_size) != 0)
			अवरोध;
		err = ext4_flex_group_add(sb, resize_inode, flex_gd);
		अगर (unlikely(err))
			अवरोध;
	पूर्ण

	अगर (!err && n_blocks_count_retry) अणु
		n_blocks_count = n_blocks_count_retry;
		n_blocks_count_retry = 0;
		मुक्त_flex_gd(flex_gd);
		flex_gd = शून्य;
		अगर (resize_inode) अणु
			iput(resize_inode);
			resize_inode = शून्य;
		पूर्ण
		जाओ retry;
	पूर्ण

out:
	अगर (flex_gd)
		मुक्त_flex_gd(flex_gd);
	अगर (resize_inode != शून्य)
		iput(resize_inode);
	अगर (err)
		ext4_warning(sb, "error (%d) occurred during "
			     "file system resize", err);
	ext4_msg(sb, KERN_INFO, "resized filesystem to %llu",
		 ext4_blocks_count(es));
	वापस err;
पूर्ण
