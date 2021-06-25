<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext2/balloc.c
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

#समावेश "ext2.h"
#समावेश <linux/quotaops.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/capability.h>

/*
 * balloc.c contains the blocks allocation and deallocation routines
 */

/*
 * The मुक्त blocks are managed by biपंचांगaps.  A file प्रणाली contains several
 * blocks groups.  Each group contains 1 biपंचांगap block क्रम blocks, 1 biपंचांगap
 * block क्रम inodes, N blocks क्रम the inode table and data blocks.
 *
 * The file प्रणाली contains group descriptors which are located after the
 * super block.  Each descriptor contains the number of the biपंचांगap block and
 * the मुक्त blocks count in the block.  The descriptors are loaded in memory
 * when a file प्रणाली is mounted (see ext2_fill_super).
 */


#घोषणा in_range(b, first, len)	((b) >= (first) && (b) <= (first) + (len) - 1)

काष्ठा ext2_group_desc * ext2_get_group_desc(काष्ठा super_block * sb,
					     अचिन्हित पूर्णांक block_group,
					     काष्ठा buffer_head ** bh)
अणु
	अचिन्हित दीर्घ group_desc;
	अचिन्हित दीर्घ offset;
	काष्ठा ext2_group_desc * desc;
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);

	अगर (block_group >= sbi->s_groups_count) अणु
		ext2_error (sb, "ext2_get_group_desc",
			    "block_group >= groups_count - "
			    "block_group = %d, groups_count = %lu",
			    block_group, sbi->s_groups_count);

		वापस शून्य;
	पूर्ण

	group_desc = block_group >> EXT2_DESC_PER_BLOCK_BITS(sb);
	offset = block_group & (EXT2_DESC_PER_BLOCK(sb) - 1);
	अगर (!sbi->s_group_desc[group_desc]) अणु
		ext2_error (sb, "ext2_get_group_desc",
			    "Group descriptor not loaded - "
			    "block_group = %d, group_desc = %lu, desc = %lu",
			     block_group, group_desc, offset);
		वापस शून्य;
	पूर्ण

	desc = (काष्ठा ext2_group_desc *) sbi->s_group_desc[group_desc]->b_data;
	अगर (bh)
		*bh = sbi->s_group_desc[group_desc];
	वापस desc + offset;
पूर्ण

अटल पूर्णांक ext2_valid_block_biपंचांगap(काष्ठा super_block *sb,
					काष्ठा ext2_group_desc *desc,
					अचिन्हित पूर्णांक block_group,
					काष्ठा buffer_head *bh)
अणु
	ext2_grpblk_t offset;
	ext2_grpblk_t next_zero_bit;
	ext2_fsblk_t biपंचांगap_blk;
	ext2_fsblk_t group_first_block;

	group_first_block = ext2_group_first_block_no(sb, block_group);

	/* check whether block biपंचांगap block number is set */
	biपंचांगap_blk = le32_to_cpu(desc->bg_block_biपंचांगap);
	offset = biपंचांगap_blk - group_first_block;
	अगर (!ext2_test_bit(offset, bh->b_data))
		/* bad block biपंचांगap */
		जाओ err_out;

	/* check whether the inode biपंचांगap block number is set */
	biपंचांगap_blk = le32_to_cpu(desc->bg_inode_biपंचांगap);
	offset = biपंचांगap_blk - group_first_block;
	अगर (!ext2_test_bit(offset, bh->b_data))
		/* bad block biपंचांगap */
		जाओ err_out;

	/* check whether the inode table block number is set */
	biपंचांगap_blk = le32_to_cpu(desc->bg_inode_table);
	offset = biपंचांगap_blk - group_first_block;
	next_zero_bit = ext2_find_next_zero_bit(bh->b_data,
				offset + EXT2_SB(sb)->s_itb_per_group,
				offset);
	अगर (next_zero_bit >= offset + EXT2_SB(sb)->s_itb_per_group)
		/* good biपंचांगap क्रम inode tables */
		वापस 1;

err_out:
	ext2_error(sb, __func__,
			"Invalid block bitmap - "
			"block_group = %d, block = %lu",
			block_group, biपंचांगap_blk);
	वापस 0;
पूर्ण

/*
 * Read the biपंचांगap क्रम a given block_group,and validate the
 * bits क्रम block/inode/inode tables are set in the biपंचांगaps
 *
 * Return buffer_head on success or शून्य in हाल of failure.
 */
अटल काष्ठा buffer_head *
पढ़ो_block_biपंचांगap(काष्ठा super_block *sb, अचिन्हित पूर्णांक block_group)
अणु
	काष्ठा ext2_group_desc * desc;
	काष्ठा buffer_head * bh = शून्य;
	ext2_fsblk_t biपंचांगap_blk;

	desc = ext2_get_group_desc(sb, block_group, शून्य);
	अगर (!desc)
		वापस शून्य;
	biपंचांगap_blk = le32_to_cpu(desc->bg_block_biपंचांगap);
	bh = sb_getblk(sb, biपंचांगap_blk);
	अगर (unlikely(!bh)) अणु
		ext2_error(sb, __func__,
			    "Cannot read block bitmap - "
			    "block_group = %d, block_bitmap = %u",
			    block_group, le32_to_cpu(desc->bg_block_biपंचांगap));
		वापस शून्य;
	पूर्ण
	अगर (likely(bh_uptodate_or_lock(bh)))
		वापस bh;

	अगर (bh_submit_पढ़ो(bh) < 0) अणु
		brअन्यथा(bh);
		ext2_error(sb, __func__,
			    "Cannot read block bitmap - "
			    "block_group = %d, block_bitmap = %u",
			    block_group, le32_to_cpu(desc->bg_block_biपंचांगap));
		वापस शून्य;
	पूर्ण

	ext2_valid_block_biपंचांगap(sb, desc, block_group, bh);
	/*
	 * file प्रणाली mounted not to panic on error, जारी with corrupt
	 * biपंचांगap
	 */
	वापस bh;
पूर्ण

अटल व्योम group_adjust_blocks(काष्ठा super_block *sb, पूर्णांक group_no,
	काष्ठा ext2_group_desc *desc, काष्ठा buffer_head *bh, पूर्णांक count)
अणु
	अगर (count) अणु
		काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);
		अचिन्हित मुक्त_blocks;

		spin_lock(sb_bgl_lock(sbi, group_no));
		मुक्त_blocks = le16_to_cpu(desc->bg_मुक्त_blocks_count);
		desc->bg_मुक्त_blocks_count = cpu_to_le16(मुक्त_blocks + count);
		spin_unlock(sb_bgl_lock(sbi, group_no));
		mark_buffer_dirty(bh);
	पूर्ण
पूर्ण

/*
 * The reservation winकरोw काष्ठाure operations
 * --------------------------------------------
 * Operations include:
 * dump, find, add, हटाओ, is_empty, find_next_reservable_winकरोw, etc.
 *
 * We use a red-black tree to represent per-fileप्रणाली reservation
 * winकरोws.
 *
 */

/**
 * __rsv_winकरोw_dump() -- Dump the fileप्रणाली block allocation reservation map
 * @root:		root of per-fileप्रणाली reservation rb tree
 * @verbose:		verbose mode
 * @fn:			function which wishes to dump the reservation map
 *
 * If verbose is turned on, it will prपूर्णांक the whole block reservation
 * winकरोws(start, end). Otherwise, it will only prपूर्णांक out the "bad" winकरोws,
 * those winकरोws that overlap with their immediate neighbors.
 */
#अगर 1
अटल व्योम __rsv_winकरोw_dump(काष्ठा rb_root *root, पूर्णांक verbose,
			      स्थिर अक्षर *fn)
अणु
	काष्ठा rb_node *n;
	काष्ठा ext2_reserve_winकरोw_node *rsv, *prev;
	पूर्णांक bad;

restart:
	n = rb_first(root);
	bad = 0;
	prev = शून्य;

	prपूर्णांकk("Block Allocation Reservation Windows Map (%s):\n", fn);
	जबतक (n) अणु
		rsv = rb_entry(n, काष्ठा ext2_reserve_winकरोw_node, rsv_node);
		अगर (verbose)
			prपूर्णांकk("reservation window 0x%p "
				"start: %lu, end: %lu\n",
				rsv, rsv->rsv_start, rsv->rsv_end);
		अगर (rsv->rsv_start && rsv->rsv_start >= rsv->rsv_end) अणु
			prपूर्णांकk("Bad reservation %p (start >= end)\n",
			       rsv);
			bad = 1;
		पूर्ण
		अगर (prev && prev->rsv_end >= rsv->rsv_start) अणु
			prपूर्णांकk("Bad reservation %p (prev->end >= start)\n",
			       rsv);
			bad = 1;
		पूर्ण
		अगर (bad) अणु
			अगर (!verbose) अणु
				prपूर्णांकk("Restarting reservation walk in verbose mode\n");
				verbose = 1;
				जाओ restart;
			पूर्ण
		पूर्ण
		n = rb_next(n);
		prev = rsv;
	पूर्ण
	prपूर्णांकk("Window map complete.\n");
	BUG_ON(bad);
पूर्ण
#घोषणा rsv_winकरोw_dump(root, verbose) \
	__rsv_winकरोw_dump((root), (verbose), __func__)
#अन्यथा
#घोषणा rsv_winकरोw_dump(root, verbose) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * goal_in_my_reservation()
 * @rsv:		inode's reservation winकरोw
 * @grp_goal:		given goal block relative to the allocation block group
 * @group:		the current allocation block group
 * @sb:			fileप्रणाली super block
 *
 * Test अगर the given goal block (group relative) is within the file's
 * own block reservation winकरोw range.
 *
 * If the reservation winकरोw is outside the goal allocation group, वापस 0;
 * grp_goal (given goal block) could be -1, which means no specअगरic
 * goal block. In this हाल, always वापस 1.
 * If the goal block is within the reservation winकरोw, वापस 1;
 * otherwise, वापस 0;
 */
अटल पूर्णांक
goal_in_my_reservation(काष्ठा ext2_reserve_winकरोw *rsv, ext2_grpblk_t grp_goal,
			अचिन्हित पूर्णांक group, काष्ठा super_block * sb)
अणु
	ext2_fsblk_t group_first_block, group_last_block;

	group_first_block = ext2_group_first_block_no(sb, group);
	group_last_block = ext2_group_last_block_no(sb, group);

	अगर ((rsv->_rsv_start > group_last_block) ||
	    (rsv->_rsv_end < group_first_block))
		वापस 0;
	अगर ((grp_goal >= 0) && ((grp_goal + group_first_block < rsv->_rsv_start)
		|| (grp_goal + group_first_block > rsv->_rsv_end)))
		वापस 0;
	वापस 1;
पूर्ण

/**
 * search_reserve_winकरोw()
 * @root:		root of reservation tree
 * @goal:		target allocation block
 *
 * Find the reserved winकरोw which includes the goal, or the previous one
 * अगर the goal is not in any winकरोw.
 * Returns शून्य अगर there are no winकरोws or अगर all winकरोws start after the goal.
 */
अटल काष्ठा ext2_reserve_winकरोw_node *
search_reserve_winकरोw(काष्ठा rb_root *root, ext2_fsblk_t goal)
अणु
	काष्ठा rb_node *n = root->rb_node;
	काष्ठा ext2_reserve_winकरोw_node *rsv;

	अगर (!n)
		वापस शून्य;

	करो अणु
		rsv = rb_entry(n, काष्ठा ext2_reserve_winकरोw_node, rsv_node);

		अगर (goal < rsv->rsv_start)
			n = n->rb_left;
		अन्यथा अगर (goal > rsv->rsv_end)
			n = n->rb_right;
		अन्यथा
			वापस rsv;
	पूर्ण जबतक (n);
	/*
	 * We've fallen off the end of the tree: the goal wasn't inside
	 * any particular node.  OK, the previous node must be to one
	 * side of the पूर्णांकerval containing the goal.  If it's the RHS,
	 * we need to back up one.
	 */
	अगर (rsv->rsv_start > goal) अणु
		n = rb_prev(&rsv->rsv_node);
		rsv = rb_entry(n, काष्ठा ext2_reserve_winकरोw_node, rsv_node);
	पूर्ण
	वापस rsv;
पूर्ण

/*
 * ext2_rsv_winकरोw_add() -- Insert a winकरोw to the block reservation rb tree.
 * @sb:			super block
 * @rsv:		reservation winकरोw to add
 *
 * Must be called with rsv_lock held.
 */
व्योम ext2_rsv_winकरोw_add(काष्ठा super_block *sb,
		    काष्ठा ext2_reserve_winकरोw_node *rsv)
अणु
	काष्ठा rb_root *root = &EXT2_SB(sb)->s_rsv_winकरोw_root;
	काष्ठा rb_node *node = &rsv->rsv_node;
	ext2_fsblk_t start = rsv->rsv_start;

	काष्ठा rb_node ** p = &root->rb_node;
	काष्ठा rb_node * parent = शून्य;
	काष्ठा ext2_reserve_winकरोw_node *this;

	जबतक (*p)
	अणु
		parent = *p;
		this = rb_entry(parent, काष्ठा ext2_reserve_winकरोw_node, rsv_node);

		अगर (start < this->rsv_start)
			p = &(*p)->rb_left;
		अन्यथा अगर (start > this->rsv_end)
			p = &(*p)->rb_right;
		अन्यथा अणु
			rsv_winकरोw_dump(root, 1);
			BUG();
		पूर्ण
	पूर्ण

	rb_link_node(node, parent, p);
	rb_insert_color(node, root);
पूर्ण

/**
 * rsv_winकरोw_हटाओ() -- unlink a winकरोw from the reservation rb tree
 * @sb:			super block
 * @rsv:		reservation winकरोw to हटाओ
 *
 * Mark the block reservation winकरोw as not allocated, and unlink it
 * from the fileप्रणाली reservation winकरोw rb tree. Must be called with
 * rsv_lock held.
 */
अटल व्योम rsv_winकरोw_हटाओ(काष्ठा super_block *sb,
			      काष्ठा ext2_reserve_winकरोw_node *rsv)
अणु
	rsv->rsv_start = EXT2_RESERVE_WINDOW_NOT_ALLOCATED;
	rsv->rsv_end = EXT2_RESERVE_WINDOW_NOT_ALLOCATED;
	rsv->rsv_alloc_hit = 0;
	rb_erase(&rsv->rsv_node, &EXT2_SB(sb)->s_rsv_winकरोw_root);
पूर्ण

/*
 * rsv_is_empty() -- Check अगर the reservation winकरोw is allocated.
 * @rsv:		given reservation winकरोw to check
 *
 * वापसs 1 अगर the end block is EXT2_RESERVE_WINDOW_NOT_ALLOCATED.
 */
अटल अंतरभूत पूर्णांक rsv_is_empty(काष्ठा ext2_reserve_winकरोw *rsv)
अणु
	/* a valid reservation end block could not be 0 */
	वापस (rsv->_rsv_end == EXT2_RESERVE_WINDOW_NOT_ALLOCATED);
पूर्ण

/**
 * ext2_init_block_alloc_info()
 * @inode:		file inode काष्ठाure
 *
 * Allocate and initialize the  reservation winकरोw काष्ठाure, and
 * link the winकरोw to the ext2 inode काष्ठाure at last
 *
 * The reservation winकरोw काष्ठाure is only dynamically allocated
 * and linked to ext2 inode the first समय the खोलो file
 * needs a new block. So, beक्रमe every ext2_new_block(s) call, क्रम
 * regular files, we should check whether the reservation winकरोw
 * काष्ठाure exists or not. In the latter हाल, this function is called.
 * Fail to करो so will result in block reservation being turned off क्रम that
 * खोलो file.
 *
 * This function is called from ext2_get_blocks_handle(), also called
 * when setting the reservation winकरोw size through ioctl beक्रमe the file
 * is खोलो क्रम ग_लिखो (needs block allocation).
 *
 * Needs truncate_mutex protection prior to calling this function.
 */
व्योम ext2_init_block_alloc_info(काष्ठा inode *inode)
अणु
	काष्ठा ext2_inode_info *ei = EXT2_I(inode);
	काष्ठा ext2_block_alloc_info *block_i;
	काष्ठा super_block *sb = inode->i_sb;

	block_i = kदो_स्मृति(माप(*block_i), GFP_NOFS);
	अगर (block_i) अणु
		काष्ठा ext2_reserve_winकरोw_node *rsv = &block_i->rsv_winकरोw_node;

		rsv->rsv_start = EXT2_RESERVE_WINDOW_NOT_ALLOCATED;
		rsv->rsv_end = EXT2_RESERVE_WINDOW_NOT_ALLOCATED;

	 	/*
		 * अगर fileप्रणाली is mounted with NORESERVATION, the goal
		 * reservation winकरोw size is set to zero to indicate
		 * block reservation is off
		 */
		अगर (!test_opt(sb, RESERVATION))
			rsv->rsv_goal_size = 0;
		अन्यथा
			rsv->rsv_goal_size = EXT2_DEFAULT_RESERVE_BLOCKS;
		rsv->rsv_alloc_hit = 0;
		block_i->last_alloc_logical_block = 0;
		block_i->last_alloc_physical_block = 0;
	पूर्ण
	ei->i_block_alloc_info = block_i;
पूर्ण

/**
 * ext2_discard_reservation()
 * @inode:		inode
 *
 * Discard(मुक्त) block reservation winकरोw on last file बंद, or truncate
 * or at last iput().
 *
 * It is being called in three हालs:
 * 	ext2_release_file(): last ग_लिखोr बंदs the file
 * 	ext2_clear_inode(): last iput(), when nobody links to this file.
 * 	ext2_truncate(): when the block indirect map is about to change.
 */
व्योम ext2_discard_reservation(काष्ठा inode *inode)
अणु
	काष्ठा ext2_inode_info *ei = EXT2_I(inode);
	काष्ठा ext2_block_alloc_info *block_i = ei->i_block_alloc_info;
	काष्ठा ext2_reserve_winकरोw_node *rsv;
	spinlock_t *rsv_lock = &EXT2_SB(inode->i_sb)->s_rsv_winकरोw_lock;

	अगर (!block_i)
		वापस;

	rsv = &block_i->rsv_winकरोw_node;
	अगर (!rsv_is_empty(&rsv->rsv_winकरोw)) अणु
		spin_lock(rsv_lock);
		अगर (!rsv_is_empty(&rsv->rsv_winकरोw))
			rsv_winकरोw_हटाओ(inode->i_sb, rsv);
		spin_unlock(rsv_lock);
	पूर्ण
पूर्ण

/**
 * ext2_मुक्त_blocks() -- Free given blocks and update quota and i_blocks
 * @inode:		inode
 * @block:		start physical block to मुक्त
 * @count:		number of blocks to मुक्त
 */
व्योम ext2_मुक्त_blocks (काष्ठा inode * inode, अचिन्हित दीर्घ block,
		       अचिन्हित दीर्घ count)
अणु
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा buffer_head * bh2;
	अचिन्हित दीर्घ block_group;
	अचिन्हित दीर्घ bit;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ overflow;
	काष्ठा super_block * sb = inode->i_sb;
	काष्ठा ext2_sb_info * sbi = EXT2_SB(sb);
	काष्ठा ext2_group_desc * desc;
	काष्ठा ext2_super_block * es = sbi->s_es;
	अचिन्हित मुक्तd = 0, group_मुक्तd;

	अगर (!ext2_data_block_valid(sbi, block, count)) अणु
		ext2_error (sb, "ext2_free_blocks",
			    "Freeing blocks not in datazone - "
			    "block = %lu, count = %lu", block, count);
		जाओ error_वापस;
	पूर्ण

	ext2_debug ("freeing block(s) %lu-%lu\n", block, block + count - 1);

करो_more:
	overflow = 0;
	block_group = (block - le32_to_cpu(es->s_first_data_block)) /
		      EXT2_BLOCKS_PER_GROUP(sb);
	bit = (block - le32_to_cpu(es->s_first_data_block)) %
		      EXT2_BLOCKS_PER_GROUP(sb);
	/*
	 * Check to see अगर we are मुक्तing blocks across a group
	 * boundary.
	 */
	अगर (bit + count > EXT2_BLOCKS_PER_GROUP(sb)) अणु
		overflow = bit + count - EXT2_BLOCKS_PER_GROUP(sb);
		count -= overflow;
	पूर्ण
	brअन्यथा(biपंचांगap_bh);
	biपंचांगap_bh = पढ़ो_block_biपंचांगap(sb, block_group);
	अगर (!biपंचांगap_bh)
		जाओ error_वापस;

	desc = ext2_get_group_desc (sb, block_group, &bh2);
	अगर (!desc)
		जाओ error_वापस;

	अगर (in_range (le32_to_cpu(desc->bg_block_biपंचांगap), block, count) ||
	    in_range (le32_to_cpu(desc->bg_inode_biपंचांगap), block, count) ||
	    in_range (block, le32_to_cpu(desc->bg_inode_table),
		      sbi->s_itb_per_group) ||
	    in_range (block + count - 1, le32_to_cpu(desc->bg_inode_table),
		      sbi->s_itb_per_group)) अणु
		ext2_error (sb, "ext2_free_blocks",
			    "Freeing blocks in system zones - "
			    "Block = %lu, count = %lu",
			    block, count);
		जाओ error_वापस;
	पूर्ण

	क्रम (i = 0, group_मुक्तd = 0; i < count; i++) अणु
		अगर (!ext2_clear_bit_atomic(sb_bgl_lock(sbi, block_group),
						bit + i, biपंचांगap_bh->b_data)) अणु
			ext2_error(sb, __func__,
				"bit already cleared for block %lu", block + i);
		पूर्ण अन्यथा अणु
			group_मुक्तd++;
		पूर्ण
	पूर्ण

	mark_buffer_dirty(biपंचांगap_bh);
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		sync_dirty_buffer(biपंचांगap_bh);

	group_adjust_blocks(sb, block_group, desc, bh2, group_मुक्तd);
	मुक्तd += group_मुक्तd;

	अगर (overflow) अणु
		block += count;
		count = overflow;
		जाओ करो_more;
	पूर्ण
error_वापस:
	brअन्यथा(biपंचांगap_bh);
	अगर (मुक्तd) अणु
		percpu_counter_add(&sbi->s_मुक्तblocks_counter, मुक्तd);
		dquot_मुक्त_block_nodirty(inode, मुक्तd);
		mark_inode_dirty(inode);
	पूर्ण
पूर्ण

/**
 * biपंचांगap_search_next_usable_block()
 * @start:		the starting block (group relative) of the search
 * @bh:			bufferhead contains the block group biपंचांगap
 * @maxblocks:		the ending block (group relative) of the reservation
 *
 * The biपंचांगap search --- search क्रमward through the actual biपंचांगap on disk until
 * we find a bit मुक्त.
 */
अटल ext2_grpblk_t
biपंचांगap_search_next_usable_block(ext2_grpblk_t start, काष्ठा buffer_head *bh,
					ext2_grpblk_t maxblocks)
अणु
	ext2_grpblk_t next;

	next = ext2_find_next_zero_bit(bh->b_data, maxblocks, start);
	अगर (next >= maxblocks)
		वापस -1;
	वापस next;
पूर्ण

/**
 * find_next_usable_block()
 * @start:		the starting block (group relative) to find next
 * 			allocatable block in biपंचांगap.
 * @bh:			bufferhead contains the block group biपंचांगap
 * @maxblocks:		the ending block (group relative) क्रम the search
 *
 * Find an allocatable block in a biपंचांगap.  We perक्रमm the "most
 * appropriate allocation" algorithm of looking क्रम a मुक्त block near
 * the initial goal; then क्रम a मुक्त byte somewhere in the biपंचांगap;
 * then क्रम any मुक्त bit in the biपंचांगap.
 */
अटल ext2_grpblk_t
find_next_usable_block(पूर्णांक start, काष्ठा buffer_head *bh, पूर्णांक maxblocks)
अणु
	ext2_grpblk_t here, next;
	अक्षर *p, *r;

	अगर (start > 0) अणु
		/*
		 * The goal was occupied; search क्रमward क्रम a मुक्त 
		 * block within the next XX blocks.
		 *
		 * end_goal is more or less अक्रमom, but it has to be
		 * less than EXT2_BLOCKS_PER_GROUP. Aligning up to the
		 * next 64-bit boundary is simple..
		 */
		ext2_grpblk_t end_goal = (start + 63) & ~63;
		अगर (end_goal > maxblocks)
			end_goal = maxblocks;
		here = ext2_find_next_zero_bit(bh->b_data, end_goal, start);
		अगर (here < end_goal)
			वापस here;
		ext2_debug("Bit not found near goal\n");
	पूर्ण

	here = start;
	अगर (here < 0)
		here = 0;

	p = ((अक्षर *)bh->b_data) + (here >> 3);
	r = memscan(p, 0, ((maxblocks + 7) >> 3) - (here >> 3));
	next = (r - ((अक्षर *)bh->b_data)) << 3;

	अगर (next < maxblocks && next >= here)
		वापस next;

	here = biपंचांगap_search_next_usable_block(here, bh, maxblocks);
	वापस here;
पूर्ण

/**
 * ext2_try_to_allocate()
 * @sb:			superblock
 * @group:		given allocation block group
 * @biपंचांगap_bh:		bufferhead holds the block biपंचांगap
 * @grp_goal:		given target block within the group
 * @count:		target number of blocks to allocate
 * @my_rsv:		reservation winकरोw
 *
 * Attempt to allocate blocks within a give range. Set the range of allocation
 * first, then find the first मुक्त bit(s) from the biपंचांगap (within the range),
 * and at last, allocate the blocks by claiming the found मुक्त bit as allocated.
 *
 * To set the range of this allocation:
 * 	अगर there is a reservation winकरोw, only try to allocate block(s)
 * 	from the file's own reservation winकरोw;
 * 	Otherwise, the allocation range starts from the give goal block,
 * 	ends at the block group's last block.
 *
 * If we failed to allocate the desired block then we may end up crossing to a
 * new biपंचांगap.
 */
अटल पूर्णांक
ext2_try_to_allocate(काष्ठा super_block *sb, पूर्णांक group,
			काष्ठा buffer_head *biपंचांगap_bh, ext2_grpblk_t grp_goal,
			अचिन्हित दीर्घ *count,
			काष्ठा ext2_reserve_winकरोw *my_rsv)
अणु
	ext2_fsblk_t group_first_block = ext2_group_first_block_no(sb, group);
	ext2_fsblk_t group_last_block = ext2_group_last_block_no(sb, group);
       	ext2_grpblk_t start, end;
	अचिन्हित दीर्घ num = 0;

	start = 0;
	end = group_last_block - group_first_block + 1;
	/* we करो allocation within the reservation winकरोw अगर we have a winकरोw */
	अगर (my_rsv) अणु
		अगर (my_rsv->_rsv_start >= group_first_block)
			start = my_rsv->_rsv_start - group_first_block;
		अगर (my_rsv->_rsv_end < group_last_block)
			end = my_rsv->_rsv_end - group_first_block + 1;
		अगर (grp_goal < start || grp_goal >= end)
			grp_goal = -1;
	पूर्ण
	BUG_ON(start > EXT2_BLOCKS_PER_GROUP(sb));

	अगर (grp_goal < 0) अणु
		grp_goal = find_next_usable_block(start, biपंचांगap_bh, end);
		अगर (grp_goal < 0)
			जाओ fail_access;
		अगर (!my_rsv) अणु
			पूर्णांक i;

			क्रम (i = 0; i < 7 && grp_goal > start &&
					!ext2_test_bit(grp_goal - 1,
					     		biपंचांगap_bh->b_data);
			     		i++, grp_goal--)
				;
		पूर्ण
	पूर्ण

	क्रम (; num < *count && grp_goal < end; grp_goal++) अणु
		अगर (ext2_set_bit_atomic(sb_bgl_lock(EXT2_SB(sb), group),
					grp_goal, biपंचांगap_bh->b_data)) अणु
			अगर (num == 0)
				जारी;
			अवरोध;
		पूर्ण
		num++;
	पूर्ण

	अगर (num == 0)
		जाओ fail_access;

	*count = num;
	वापस grp_goal - num;
fail_access:
	वापस -1;
पूर्ण

/**
 * 	find_next_reservable_winकरोw():
 *		find a reservable space within the given range.
 *		It करोes not allocate the reservation winकरोw क्रम now:
 *		alloc_new_reservation() will करो the work later.
 *
 * 	@search_head: the head of the searching list;
 *		This is not necessarily the list head of the whole fileप्रणाली
 *
 *		We have both head and start_block to assist the search
 *		क्रम the reservable space. The list starts from head,
 *		but we will shअगरt to the place where start_block is,
 *		then start from there, when looking क्रम a reservable space.
 *
 *	@sb: the super block.
 *
 * 	@start_block: the first block we consider to start the real search from
 *
 * 	@last_block:
 *		the maximum block number that our goal reservable space
 *		could start from. This is normally the last block in this
 *		group. The search will end when we found the start of next
 *		possible reservable space is out of this boundary.
 *		This could handle the cross boundary reservation winकरोw
 *		request.
 *
 * 	basically we search from the given range, rather than the whole
 * 	reservation द्विगुन linked list, (start_block, last_block)
 * 	to find a मुक्त region that is of my size and has not
 * 	been reserved.
 *
 */
अटल पूर्णांक find_next_reservable_winकरोw(
				काष्ठा ext2_reserve_winकरोw_node *search_head,
				काष्ठा ext2_reserve_winकरोw_node *my_rsv,
				काष्ठा super_block * sb,
				ext2_fsblk_t start_block,
				ext2_fsblk_t last_block)
अणु
	काष्ठा rb_node *next;
	काष्ठा ext2_reserve_winकरोw_node *rsv, *prev;
	ext2_fsblk_t cur;
	पूर्णांक size = my_rsv->rsv_goal_size;

	/* TODO: make the start of the reservation winकरोw byte-aligned */
	/* cur = *start_block & ~7;*/
	cur = start_block;
	rsv = search_head;
	अगर (!rsv)
		वापस -1;

	जबतक (1) अणु
		अगर (cur <= rsv->rsv_end)
			cur = rsv->rsv_end + 1;

		/* TODO?
		 * in the हाल we could not find a reservable space
		 * that is what is expected, during the re-search, we could
		 * remember what's the largest reservable space we could have
		 * and वापस that one.
		 *
		 * For now it will fail अगर we could not find the reservable
		 * space with expected-size (or more)...
		 */
		अगर (cur > last_block)
			वापस -1;		/* fail */

		prev = rsv;
		next = rb_next(&rsv->rsv_node);
		rsv = rb_entry(next,काष्ठा ext2_reserve_winकरोw_node,rsv_node);

		/*
		 * Reached the last reservation, we can just append to the
		 * previous one.
		 */
		अगर (!next)
			अवरोध;

		अगर (cur + size <= rsv->rsv_start) अणु
			/*
			 * Found a reserveable space big enough.  We could
			 * have a reservation across the group boundary here
		 	 */
			अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * we come here either :
	 * when we reach the end of the whole list,
	 * and there is empty reservable space after last entry in the list.
	 * append it to the end of the list.
	 *
	 * or we found one reservable space in the middle of the list,
	 * वापस the reservation winकरोw that we could append to.
	 * succeed.
	 */

	अगर ((prev != my_rsv) && (!rsv_is_empty(&my_rsv->rsv_winकरोw)))
		rsv_winकरोw_हटाओ(sb, my_rsv);

	/*
	 * Let's book the whole available winकरोw क्रम now.  We will check the
	 * disk biपंचांगap later and then, अगर there are मुक्त blocks then we adjust
	 * the winकरोw size अगर it's larger than requested.
	 * Otherwise, we will हटाओ this node from the tree next समय
	 * call find_next_reservable_winकरोw.
	 */
	my_rsv->rsv_start = cur;
	my_rsv->rsv_end = cur + size - 1;
	my_rsv->rsv_alloc_hit = 0;

	अगर (prev != my_rsv)
		ext2_rsv_winकरोw_add(sb, my_rsv);

	वापस 0;
पूर्ण

/**
 * 	alloc_new_reservation()--allocate a new reservation winकरोw
 *
 *		To make a new reservation, we search part of the fileप्रणाली
 *		reservation list (the list that inside the group). We try to
 *		allocate a new reservation winकरोw near the allocation goal,
 *		or the beginning of the group, अगर there is no goal.
 *
 *		We first find a reservable space after the goal, then from
 *		there, we check the biपंचांगap क्रम the first मुक्त block after
 *		it. If there is no मुक्त block until the end of group, then the
 *		whole group is full, we failed. Otherwise, check अगर the मुक्त
 *		block is inside the expected reservable space, अगर so, we
 *		succeed.
 *		If the first मुक्त block is outside the reservable space, then
 *		start from the first मुक्त block, we search क्रम next available
 *		space, and go on.
 *
 *	on succeed, a new reservation will be found and inserted पूर्णांकo the list
 *	It contains at least one मुक्त block, and it करोes not overlap with other
 *	reservation winकरोws.
 *
 *	failed: we failed to find a reservation winकरोw in this group
 *
 *	@my_rsv: the reservation
 *
 *	@grp_goal: The goal (group-relative).  It is where the search क्रम a
 *		मुक्त reservable space should start from.
 *		अगर we have a goal(goal >0 ), then start from there,
 *		no goal(goal = -1), we start from the first block
 *		of the group.
 *
 *	@sb: the super block
 *	@group: the group we are trying to allocate in
 *	@biपंचांगap_bh: the block group block biपंचांगap
 *
 */
अटल पूर्णांक alloc_new_reservation(काष्ठा ext2_reserve_winकरोw_node *my_rsv,
		ext2_grpblk_t grp_goal, काष्ठा super_block *sb,
		अचिन्हित पूर्णांक group, काष्ठा buffer_head *biपंचांगap_bh)
अणु
	काष्ठा ext2_reserve_winकरोw_node *search_head;
	ext2_fsblk_t group_first_block, group_end_block, start_block;
	ext2_grpblk_t first_मुक्त_block;
	काष्ठा rb_root *fs_rsv_root = &EXT2_SB(sb)->s_rsv_winकरोw_root;
	अचिन्हित दीर्घ size;
	पूर्णांक ret;
	spinlock_t *rsv_lock = &EXT2_SB(sb)->s_rsv_winकरोw_lock;

	group_first_block = ext2_group_first_block_no(sb, group);
	group_end_block = ext2_group_last_block_no(sb, group);

	अगर (grp_goal < 0)
		start_block = group_first_block;
	अन्यथा
		start_block = grp_goal + group_first_block;

	size = my_rsv->rsv_goal_size;

	अगर (!rsv_is_empty(&my_rsv->rsv_winकरोw)) अणु
		/*
		 * अगर the old reservation is cross group boundary
		 * and अगर the goal is inside the old reservation winकरोw,
		 * we will come here when we just failed to allocate from
		 * the first part of the winकरोw. We still have another part
		 * that beदीर्घs to the next group. In this हाल, there is no
		 * poपूर्णांक to discard our winकरोw and try to allocate a new one
		 * in this group(which will fail). we should
		 * keep the reservation winकरोw, just simply move on.
		 *
		 * Maybe we could shअगरt the start block of the reservation
		 * winकरोw to the first block of next group.
		 */

		अगर ((my_rsv->rsv_start <= group_end_block) &&
				(my_rsv->rsv_end > group_end_block) &&
				(start_block >= my_rsv->rsv_start))
			वापस -1;

		अगर ((my_rsv->rsv_alloc_hit >
		     (my_rsv->rsv_end - my_rsv->rsv_start + 1) / 2)) अणु
			/*
			 * अगर the previously allocation hit ratio is
			 * greater than 1/2, then we द्विगुन the size of
			 * the reservation winकरोw the next समय,
			 * otherwise we keep the same size winकरोw
			 */
			size = size * 2;
			अगर (size > EXT2_MAX_RESERVE_BLOCKS)
				size = EXT2_MAX_RESERVE_BLOCKS;
			my_rsv->rsv_goal_size= size;
		पूर्ण
	पूर्ण

	spin_lock(rsv_lock);
	/*
	 * shअगरt the search start to the winकरोw near the goal block
	 */
	search_head = search_reserve_winकरोw(fs_rsv_root, start_block);

	/*
	 * find_next_reservable_winकरोw() simply finds a reservable winकरोw
	 * inside the given range(start_block, group_end_block).
	 *
	 * To make sure the reservation winकरोw has a मुक्त bit inside it, we
	 * need to check the biपंचांगap after we found a reservable winकरोw.
	 */
retry:
	ret = find_next_reservable_winकरोw(search_head, my_rsv, sb,
						start_block, group_end_block);

	अगर (ret == -1) अणु
		अगर (!rsv_is_empty(&my_rsv->rsv_winकरोw))
			rsv_winकरोw_हटाओ(sb, my_rsv);
		spin_unlock(rsv_lock);
		वापस -1;
	पूर्ण

	/*
	 * On success, find_next_reservable_winकरोw() वापसs the
	 * reservation winकरोw where there is a reservable space after it.
	 * Beक्रमe we reserve this reservable space, we need
	 * to make sure there is at least a मुक्त block inside this region.
	 *
	 * Search the first मुक्त bit on the block biपंचांगap.  Search starts from
	 * the start block of the reservable space we just found.
	 */
	spin_unlock(rsv_lock);
	first_मुक्त_block = biपंचांगap_search_next_usable_block(
			my_rsv->rsv_start - group_first_block,
			biपंचांगap_bh, group_end_block - group_first_block + 1);

	अगर (first_मुक्त_block < 0) अणु
		/*
		 * no मुक्त block left on the biपंचांगap, no poपूर्णांक
		 * to reserve the space. वापस failed.
		 */
		spin_lock(rsv_lock);
		अगर (!rsv_is_empty(&my_rsv->rsv_winकरोw))
			rsv_winकरोw_हटाओ(sb, my_rsv);
		spin_unlock(rsv_lock);
		वापस -1;		/* failed */
	पूर्ण

	start_block = first_मुक्त_block + group_first_block;
	/*
	 * check अगर the first मुक्त block is within the
	 * मुक्त space we just reserved
	 */
	अगर (start_block >= my_rsv->rsv_start && start_block <= my_rsv->rsv_end)
		वापस 0;		/* success */
	/*
	 * अगर the first मुक्त bit we found is out of the reservable space
	 * जारी search क्रम next reservable space,
	 * start from where the मुक्त block is,
	 * we also shअगरt the list head to where we stopped last समय
	 */
	search_head = my_rsv;
	spin_lock(rsv_lock);
	जाओ retry;
पूर्ण

/**
 * try_to_extend_reservation()
 * @my_rsv:		given reservation winकरोw
 * @sb:			super block
 * @size:		the delta to extend
 *
 * Attempt to expand the reservation winकरोw large enough to have
 * required number of मुक्त blocks
 *
 * Since ext2_try_to_allocate() will always allocate blocks within
 * the reservation winकरोw range, अगर the winकरोw size is too small,
 * multiple blocks allocation has to stop at the end of the reservation
 * winकरोw. To make this more efficient, given the total number of
 * blocks needed and the current size of the winकरोw, we try to
 * expand the reservation winकरोw size अगर necessary on a best-efक्रमt
 * basis beक्रमe ext2_new_blocks() tries to allocate blocks.
 */
अटल व्योम try_to_extend_reservation(काष्ठा ext2_reserve_winकरोw_node *my_rsv,
			काष्ठा super_block *sb, पूर्णांक size)
अणु
	काष्ठा ext2_reserve_winकरोw_node *next_rsv;
	काष्ठा rb_node *next;
	spinlock_t *rsv_lock = &EXT2_SB(sb)->s_rsv_winकरोw_lock;

	अगर (!spin_trylock(rsv_lock))
		वापस;

	next = rb_next(&my_rsv->rsv_node);

	अगर (!next)
		my_rsv->rsv_end += size;
	अन्यथा अणु
		next_rsv = rb_entry(next, काष्ठा ext2_reserve_winकरोw_node, rsv_node);

		अगर ((next_rsv->rsv_start - my_rsv->rsv_end - 1) >= size)
			my_rsv->rsv_end += size;
		अन्यथा
			my_rsv->rsv_end = next_rsv->rsv_start - 1;
	पूर्ण
	spin_unlock(rsv_lock);
पूर्ण

/**
 * ext2_try_to_allocate_with_rsv()
 * @sb:			superblock
 * @group:		given allocation block group
 * @biपंचांगap_bh:		bufferhead holds the block biपंचांगap
 * @grp_goal:		given target block within the group
 * @count:		target number of blocks to allocate
 * @my_rsv:		reservation winकरोw
 *
 * This is the मुख्य function used to allocate a new block and its reservation
 * winकरोw.
 *
 * Each समय when a new block allocation is need, first try to allocate from
 * its own reservation.  If it करोes not have a reservation winकरोw, instead of
 * looking क्रम a मुक्त bit on biपंचांगap first, then look up the reservation list to
 * see अगर it is inside somebody अन्यथा's reservation winकरोw, we try to allocate a
 * reservation winकरोw क्रम it starting from the goal first. Then करो the block
 * allocation within the reservation winकरोw.
 *
 * This will aव्योम keeping on searching the reservation list again and
 * again when somebody is looking क्रम a मुक्त block (without
 * reservation), and there are lots of मुक्त blocks, but they are all
 * being reserved.
 *
 * We use a red-black tree क्रम the per-fileप्रणाली reservation list.
 */
अटल ext2_grpblk_t
ext2_try_to_allocate_with_rsv(काष्ठा super_block *sb, अचिन्हित पूर्णांक group,
			काष्ठा buffer_head *biपंचांगap_bh, ext2_grpblk_t grp_goal,
			काष्ठा ext2_reserve_winकरोw_node * my_rsv,
			अचिन्हित दीर्घ *count)
अणु
	ext2_fsblk_t group_first_block, group_last_block;
	ext2_grpblk_t ret = 0;
	अचिन्हित दीर्घ num = *count;

	/*
	 * we करोn't deal with reservation when
	 * fileप्रणाली is mounted without reservation
	 * or the file is not a regular file
	 * or last attempt to allocate a block with reservation turned on failed
	 */
	अगर (my_rsv == शून्य) अणु
		वापस ext2_try_to_allocate(sb, group, biपंचांगap_bh,
						grp_goal, count, शून्य);
	पूर्ण
	/*
	 * grp_goal is a group relative block number (अगर there is a goal)
	 * 0 <= grp_goal < EXT2_BLOCKS_PER_GROUP(sb)
	 * first block is a fileप्रणाली wide block number
	 * first block is the block number of the first block in this group
	 */
	group_first_block = ext2_group_first_block_no(sb, group);
	group_last_block = ext2_group_last_block_no(sb, group);

	/*
	 * Basically we will allocate a new block from inode's reservation
	 * winकरोw.
	 *
	 * We need to allocate a new reservation winकरोw, अगर:
	 * a) inode करोes not have a reservation winकरोw; or
	 * b) last attempt to allocate a block from existing reservation
	 *    failed; or
	 * c) we come here with a goal and with a reservation winकरोw
	 *
	 * We करो not need to allocate a new reservation winकरोw अगर we come here
	 * at the beginning with a goal and the goal is inside the winकरोw, or
	 * we करोn't have a goal but alपढ़ोy have a reservation winकरोw.
	 * then we could go to allocate from the reservation winकरोw directly.
	 */
	जबतक (1) अणु
		अगर (rsv_is_empty(&my_rsv->rsv_winकरोw) || (ret < 0) ||
			!goal_in_my_reservation(&my_rsv->rsv_winकरोw,
						grp_goal, group, sb)) अणु
			अगर (my_rsv->rsv_goal_size < *count)
				my_rsv->rsv_goal_size = *count;
			ret = alloc_new_reservation(my_rsv, grp_goal, sb,
							group, biपंचांगap_bh);
			अगर (ret < 0)
				अवरोध;			/* failed */

			अगर (!goal_in_my_reservation(&my_rsv->rsv_winकरोw,
							grp_goal, group, sb))
				grp_goal = -1;
		पूर्ण अन्यथा अगर (grp_goal >= 0) अणु
			पूर्णांक curr = my_rsv->rsv_end -
					(grp_goal + group_first_block) + 1;

			अगर (curr < *count)
				try_to_extend_reservation(my_rsv, sb,
							*count - curr);
		पूर्ण

		अगर ((my_rsv->rsv_start > group_last_block) ||
				(my_rsv->rsv_end < group_first_block)) अणु
			rsv_winकरोw_dump(&EXT2_SB(sb)->s_rsv_winकरोw_root, 1);
			BUG();
		पूर्ण
		ret = ext2_try_to_allocate(sb, group, biपंचांगap_bh, grp_goal,
					   &num, &my_rsv->rsv_winकरोw);
		अगर (ret >= 0) अणु
			my_rsv->rsv_alloc_hit += num;
			*count = num;
			अवरोध;				/* succeed */
		पूर्ण
		num = *count;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ext2_has_मुक्त_blocks()
 * @sbi:		in-core super block काष्ठाure.
 *
 * Check अगर fileप्रणाली has at least 1 मुक्त block available क्रम allocation.
 */
अटल पूर्णांक ext2_has_मुक्त_blocks(काष्ठा ext2_sb_info *sbi)
अणु
	ext2_fsblk_t मुक्त_blocks, root_blocks;

	मुक्त_blocks = percpu_counter_पढ़ो_positive(&sbi->s_मुक्तblocks_counter);
	root_blocks = le32_to_cpu(sbi->s_es->s_r_blocks_count);
	अगर (मुक्त_blocks < root_blocks + 1 && !capable(CAP_SYS_RESOURCE) &&
		!uid_eq(sbi->s_resuid, current_fsuid()) &&
		(gid_eq(sbi->s_resgid, GLOBAL_ROOT_GID) ||
		 !in_group_p (sbi->s_resgid))) अणु
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Returns 1 अगर the passed-in block region is valid; 0 अगर some part overlaps
 * with fileप्रणाली metadata blocks.
 */
पूर्णांक ext2_data_block_valid(काष्ठा ext2_sb_info *sbi, ext2_fsblk_t start_blk,
			  अचिन्हित पूर्णांक count)
अणु
	अगर ((start_blk <= le32_to_cpu(sbi->s_es->s_first_data_block)) ||
	    (start_blk + count - 1 < start_blk) ||
	    (start_blk + count - 1 >= le32_to_cpu(sbi->s_es->s_blocks_count)))
		वापस 0;

	/* Ensure we करो not step over superblock */
	अगर ((start_blk <= sbi->s_sb_block) &&
	    (start_blk + count - 1 >= sbi->s_sb_block))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * ext2_new_blocks() -- core block(s) allocation function
 * @inode:		file inode
 * @goal:		given target block(fileप्रणाली wide)
 * @count:		target number of blocks to allocate
 * @errp:		error code
 *
 * ext2_new_blocks uses a goal block to assist allocation.  If the goal is
 * मुक्त, or there is a मुक्त block within 32 blocks of the goal, that block
 * is allocated.  Otherwise a क्रमward search is made क्रम a मुक्त block; within 
 * each block group the search first looks क्रम an entire मुक्त byte in the block
 * biपंचांगap, and then क्रम any मुक्त bit अगर that fails.
 * This function also updates quota and i_blocks field.
 */
ext2_fsblk_t ext2_new_blocks(काष्ठा inode *inode, ext2_fsblk_t goal,
		    अचिन्हित दीर्घ *count, पूर्णांक *errp)
अणु
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा buffer_head *gdp_bh;
	पूर्णांक group_no;
	पूर्णांक goal_group;
	ext2_grpblk_t grp_target_blk;	/* blockgroup relative goal block */
	ext2_grpblk_t grp_alloc_blk;	/* blockgroup-relative allocated block*/
	ext2_fsblk_t ret_block;		/* filesyetem-wide allocated block */
	पूर्णांक bgi;			/* blockgroup iteration index */
	पूर्णांक perक्रमmed_allocation = 0;
	ext2_grpblk_t मुक्त_blocks;	/* number of मुक्त blocks in a group */
	काष्ठा super_block *sb;
	काष्ठा ext2_group_desc *gdp;
	काष्ठा ext2_super_block *es;
	काष्ठा ext2_sb_info *sbi;
	काष्ठा ext2_reserve_winकरोw_node *my_rsv = शून्य;
	काष्ठा ext2_block_alloc_info *block_i;
	अचिन्हित लघु winकरोwsz = 0;
	अचिन्हित दीर्घ ngroups;
	अचिन्हित दीर्घ num = *count;
	पूर्णांक ret;

	*errp = -ENOSPC;
	sb = inode->i_sb;

	/*
	 * Check quota क्रम allocation of this block.
	 */
	ret = dquot_alloc_block(inode, num);
	अगर (ret) अणु
		*errp = ret;
		वापस 0;
	पूर्ण

	sbi = EXT2_SB(sb);
	es = EXT2_SB(sb)->s_es;
	ext2_debug("goal=%lu.\n", goal);
	/*
	 * Allocate a block from reservation only when
	 * fileप्रणाली is mounted with reservation(शेष,-o reservation), and
	 * it's a regular file, and
	 * the desired winकरोw size is greater than 0 (One could use ioctl
	 * command EXT2_IOC_SETRSVSZ to set the winकरोw size to 0 to turn off
	 * reservation on that particular file)
	 */
	block_i = EXT2_I(inode)->i_block_alloc_info;
	अगर (block_i) अणु
		winकरोwsz = block_i->rsv_winकरोw_node.rsv_goal_size;
		अगर (winकरोwsz > 0)
			my_rsv = &block_i->rsv_winकरोw_node;
	पूर्ण

	अगर (!ext2_has_मुक्त_blocks(sbi)) अणु
		*errp = -ENOSPC;
		जाओ out;
	पूर्ण

	/*
	 * First, test whether the goal block is मुक्त.
	 */
	अगर (goal < le32_to_cpu(es->s_first_data_block) ||
	    goal >= le32_to_cpu(es->s_blocks_count))
		goal = le32_to_cpu(es->s_first_data_block);
	group_no = (goal - le32_to_cpu(es->s_first_data_block)) /
			EXT2_BLOCKS_PER_GROUP(sb);
	goal_group = group_no;
retry_alloc:
	gdp = ext2_get_group_desc(sb, group_no, &gdp_bh);
	अगर (!gdp)
		जाओ io_error;

	मुक्त_blocks = le16_to_cpu(gdp->bg_मुक्त_blocks_count);
	/*
	 * अगर there is not enough मुक्त blocks to make a new resevation
	 * turn off reservation क्रम this allocation
	 */
	अगर (my_rsv && (मुक्त_blocks < winकरोwsz)
		&& (मुक्त_blocks > 0)
		&& (rsv_is_empty(&my_rsv->rsv_winकरोw)))
		my_rsv = शून्य;

	अगर (मुक्त_blocks > 0) अणु
		grp_target_blk = ((goal - le32_to_cpu(es->s_first_data_block)) %
				EXT2_BLOCKS_PER_GROUP(sb));
		/*
		 * In हाल we retry allocation (due to fs reservation not
		 * working out or fs corruption), the biपंचांगap_bh is non-null
		 * poपूर्णांकer and we have to release it beक्रमe calling
		 * पढ़ो_block_biपंचांगap().
		 */
		brअन्यथा(biपंचांगap_bh);
		biपंचांगap_bh = पढ़ो_block_biपंचांगap(sb, group_no);
		अगर (!biपंचांगap_bh)
			जाओ io_error;
		grp_alloc_blk = ext2_try_to_allocate_with_rsv(sb, group_no,
					biपंचांगap_bh, grp_target_blk,
					my_rsv, &num);
		अगर (grp_alloc_blk >= 0)
			जाओ allocated;
	पूर्ण

	ngroups = EXT2_SB(sb)->s_groups_count;
	smp_rmb();

	/*
	 * Now search the rest of the groups.  We assume that
	 * group_no and gdp correctly poपूर्णांक to the last group visited.
	 */
	क्रम (bgi = 0; bgi < ngroups; bgi++) अणु
		group_no++;
		अगर (group_no >= ngroups)
			group_no = 0;
		gdp = ext2_get_group_desc(sb, group_no, &gdp_bh);
		अगर (!gdp)
			जाओ io_error;

		मुक्त_blocks = le16_to_cpu(gdp->bg_मुक्त_blocks_count);
		/*
		 * skip this group (and aव्योम loading biपंचांगap) अगर there
		 * are no मुक्त blocks
		 */
		अगर (!मुक्त_blocks)
			जारी;
		/*
		 * skip this group अगर the number of
		 * मुक्त blocks is less than half of the reservation
		 * winकरोw size.
		 */
		अगर (my_rsv && (मुक्त_blocks <= (winकरोwsz/2)))
			जारी;

		brअन्यथा(biपंचांगap_bh);
		biपंचांगap_bh = पढ़ो_block_biपंचांगap(sb, group_no);
		अगर (!biपंचांगap_bh)
			जाओ io_error;
		/*
		 * try to allocate block(s) from this group, without a goal(-1).
		 */
		grp_alloc_blk = ext2_try_to_allocate_with_rsv(sb, group_no,
					biपंचांगap_bh, -1, my_rsv, &num);
		अगर (grp_alloc_blk >= 0)
			जाओ allocated;
	पूर्ण
	/*
	 * We may end up a bogus earlier ENOSPC error due to
	 * fileप्रणाली is "full" of reservations, but
	 * there maybe indeed मुक्त blocks available on disk
	 * In this हाल, we just क्रमget about the reservations
	 * just करो block allocation as without reservations.
	 */
	अगर (my_rsv) अणु
		my_rsv = शून्य;
		winकरोwsz = 0;
		group_no = goal_group;
		जाओ retry_alloc;
	पूर्ण
	/* No space left on the device */
	*errp = -ENOSPC;
	जाओ out;

allocated:

	ext2_debug("using block group %d(%d)\n",
			group_no, gdp->bg_मुक्त_blocks_count);

	ret_block = grp_alloc_blk + ext2_group_first_block_no(sb, group_no);

	अगर (in_range(le32_to_cpu(gdp->bg_block_biपंचांगap), ret_block, num) ||
	    in_range(le32_to_cpu(gdp->bg_inode_biपंचांगap), ret_block, num) ||
	    in_range(ret_block, le32_to_cpu(gdp->bg_inode_table),
		      EXT2_SB(sb)->s_itb_per_group) ||
	    in_range(ret_block + num - 1, le32_to_cpu(gdp->bg_inode_table),
		      EXT2_SB(sb)->s_itb_per_group)) अणु
		ext2_error(sb, "ext2_new_blocks",
			    "Allocating block in system zone - "
			    "blocks from "E2FSBLK", length %lu",
			    ret_block, num);
		/*
		 * ext2_try_to_allocate marked the blocks we allocated as in
		 * use.  So we may want to selectively mark some of the blocks
		 * as मुक्त
		 */
		num = *count;
		जाओ retry_alloc;
	पूर्ण

	perक्रमmed_allocation = 1;

	अगर (ret_block + num - 1 >= le32_to_cpu(es->s_blocks_count)) अणु
		ext2_error(sb, "ext2_new_blocks",
			    "block("E2FSBLK") >= blocks count(%d) - "
			    "block_group = %d, es == %p ", ret_block,
			le32_to_cpu(es->s_blocks_count), group_no, es);
		जाओ out;
	पूर्ण

	group_adjust_blocks(sb, group_no, gdp, gdp_bh, -num);
	percpu_counter_sub(&sbi->s_मुक्तblocks_counter, num);

	mark_buffer_dirty(biपंचांगap_bh);
	अगर (sb->s_flags & SB_SYNCHRONOUS)
		sync_dirty_buffer(biपंचांगap_bh);

	*errp = 0;
	brअन्यथा(biपंचांगap_bh);
	अगर (num < *count) अणु
		dquot_मुक्त_block_nodirty(inode, *count-num);
		mark_inode_dirty(inode);
		*count = num;
	पूर्ण
	वापस ret_block;

io_error:
	*errp = -EIO;
out:
	/*
	 * Unकरो the block allocation
	 */
	अगर (!perक्रमmed_allocation) अणु
		dquot_मुक्त_block_nodirty(inode, *count);
		mark_inode_dirty(inode);
	पूर्ण
	brअन्यथा(biपंचांगap_bh);
	वापस 0;
पूर्ण

ext2_fsblk_t ext2_new_block(काष्ठा inode *inode, अचिन्हित दीर्घ goal, पूर्णांक *errp)
अणु
	अचिन्हित दीर्घ count = 1;

	वापस ext2_new_blocks(inode, goal, &count, errp);
पूर्ण

#अगर_घोषित EXT2FS_DEBUG

अचिन्हित दीर्घ ext2_count_मुक्त(काष्ठा buffer_head *map, अचिन्हित पूर्णांक numअक्षरs)
अणु
	वापस numअक्षरs * BITS_PER_BYTE - memweight(map->b_data, numअक्षरs);
पूर्ण

#पूर्ण_अगर  /*  EXT2FS_DEBUG  */

अचिन्हित दीर्घ ext2_count_मुक्त_blocks (काष्ठा super_block * sb)
अणु
	काष्ठा ext2_group_desc * desc;
	अचिन्हित दीर्घ desc_count = 0;
	पूर्णांक i;
#अगर_घोषित EXT2FS_DEBUG
	अचिन्हित दीर्घ biपंचांगap_count, x;
	काष्ठा ext2_super_block *es;

	es = EXT2_SB(sb)->s_es;
	desc_count = 0;
	biपंचांगap_count = 0;
	desc = शून्य;
	क्रम (i = 0; i < EXT2_SB(sb)->s_groups_count; i++) अणु
		काष्ठा buffer_head *biपंचांगap_bh;
		desc = ext2_get_group_desc (sb, i, शून्य);
		अगर (!desc)
			जारी;
		desc_count += le16_to_cpu(desc->bg_मुक्त_blocks_count);
		biपंचांगap_bh = पढ़ो_block_biपंचांगap(sb, i);
		अगर (!biपंचांगap_bh)
			जारी;
		
		x = ext2_count_मुक्त(biपंचांगap_bh, sb->s_blocksize);
		prपूर्णांकk ("group %d: stored = %d, counted = %lu\n",
			i, le16_to_cpu(desc->bg_मुक्त_blocks_count), x);
		biपंचांगap_count += x;
		brअन्यथा(biपंचांगap_bh);
	पूर्ण
	prपूर्णांकk("ext2_count_free_blocks: stored = %lu, computed = %lu, %lu\n",
		(दीर्घ)le32_to_cpu(es->s_मुक्त_blocks_count),
		desc_count, biपंचांगap_count);
	वापस biपंचांगap_count;
#अन्यथा
        क्रम (i = 0; i < EXT2_SB(sb)->s_groups_count; i++) अणु
                desc = ext2_get_group_desc (sb, i, शून्य);
                अगर (!desc)
                        जारी;
                desc_count += le16_to_cpu(desc->bg_मुक्त_blocks_count);
	पूर्ण
	वापस desc_count;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक test_root(पूर्णांक a, पूर्णांक b)
अणु
	पूर्णांक num = b;

	जबतक (a > num)
		num *= b;
	वापस num == a;
पूर्ण

अटल पूर्णांक ext2_group_sparse(पूर्णांक group)
अणु
	अगर (group <= 1)
		वापस 1;
	वापस (test_root(group, 3) || test_root(group, 5) ||
		test_root(group, 7));
पूर्ण

/**
 *	ext2_bg_has_super - number of blocks used by the superblock in group
 *	@sb: superblock क्रम fileप्रणाली
 *	@group: group number to check
 *
 *	Return the number of blocks used by the superblock (primary or backup)
 *	in this group.  Currently this will be only 0 or 1.
 */
पूर्णांक ext2_bg_has_super(काष्ठा super_block *sb, पूर्णांक group)
अणु
	अगर (EXT2_HAS_RO_COMPAT_FEATURE(sb,EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER)&&
	    !ext2_group_sparse(group))
		वापस 0;
	वापस 1;
पूर्ण

/**
 *	ext2_bg_num_gdb - number of blocks used by the group table in group
 *	@sb: superblock क्रम fileप्रणाली
 *	@group: group number to check
 *
 *	Return the number of blocks used by the group descriptor table
 *	(primary or backup) in this group.  In the future there may be a
 *	dअगरferent number of descriptor blocks in each group.
 */
अचिन्हित दीर्घ ext2_bg_num_gdb(काष्ठा super_block *sb, पूर्णांक group)
अणु
	वापस ext2_bg_has_super(sb, group) ? EXT2_SB(sb)->s_gdb_count : 0;
पूर्ण

