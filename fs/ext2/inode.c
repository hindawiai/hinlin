<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext2/inode.c
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
 *  Goal-directed block allocation by Stephen Tweedie
 * 	(sct@dcs.ed.ac.uk), 1993, 1998
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 *  64-bit file support on 64-bit platक्रमms by Jakub Jelinek
 * 	(jj@sunsite.ms.mff.cuni.cz)
 *
 *  Assorted race fixes, reग_लिखो of ext2_get_block() by Al Viro, 2000
 */

#समावेश <linux/समय.स>
#समावेश <linux/highuid.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/dax.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mpage.h>
#समावेश <linux/fiemap.h>
#समावेश <linux/iomap.h>
#समावेश <linux/namei.h>
#समावेश <linux/uपन.स>
#समावेश "ext2.h"
#समावेश "acl.h"
#समावेश "xattr.h"

अटल पूर्णांक __ext2_ग_लिखो_inode(काष्ठा inode *inode, पूर्णांक करो_sync);

/*
 * Test whether an inode is a fast symlink.
 */
अटल अंतरभूत पूर्णांक ext2_inode_is_fast_symlink(काष्ठा inode *inode)
अणु
	पूर्णांक ea_blocks = EXT2_I(inode)->i_file_acl ?
		(inode->i_sb->s_blocksize >> 9) : 0;

	वापस (S_ISLNK(inode->i_mode) &&
		inode->i_blocks - ea_blocks == 0);
पूर्ण

अटल व्योम ext2_truncate_blocks(काष्ठा inode *inode, loff_t offset);

अटल व्योम ext2_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		ext2_truncate_blocks(inode, inode->i_size);
	पूर्ण
पूर्ण

/*
 * Called at the last iput() अगर i_nlink is zero.
 */
व्योम ext2_evict_inode(काष्ठा inode * inode)
अणु
	काष्ठा ext2_block_alloc_info *rsv;
	पूर्णांक want_delete = 0;

	अगर (!inode->i_nlink && !is_bad_inode(inode)) अणु
		want_delete = 1;
		dquot_initialize(inode);
	पूर्ण अन्यथा अणु
		dquot_drop(inode);
	पूर्ण

	truncate_inode_pages_final(&inode->i_data);

	अगर (want_delete) अणु
		sb_start_पूर्णांकग_लिखो(inode->i_sb);
		/* set dसमय */
		EXT2_I(inode)->i_dसमय	= kसमय_get_real_seconds();
		mark_inode_dirty(inode);
		__ext2_ग_लिखो_inode(inode, inode_needs_sync(inode));
		/* truncate to 0 */
		inode->i_size = 0;
		अगर (inode->i_blocks)
			ext2_truncate_blocks(inode, 0);
		ext2_xattr_delete_inode(inode);
	पूर्ण

	invalidate_inode_buffers(inode);
	clear_inode(inode);

	ext2_discard_reservation(inode);
	rsv = EXT2_I(inode)->i_block_alloc_info;
	EXT2_I(inode)->i_block_alloc_info = शून्य;
	अगर (unlikely(rsv))
		kमुक्त(rsv);

	अगर (want_delete) अणु
		ext2_मुक्त_inode(inode);
		sb_end_पूर्णांकग_लिखो(inode->i_sb);
	पूर्ण
पूर्ण

प्रकार काष्ठा अणु
	__le32	*p;
	__le32	key;
	काष्ठा buffer_head *bh;
पूर्ण Indirect;

अटल अंतरभूत व्योम add_chain(Indirect *p, काष्ठा buffer_head *bh, __le32 *v)
अणु
	p->key = *(p->p = v);
	p->bh = bh;
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_chain(Indirect *from, Indirect *to)
अणु
	जबतक (from <= to && from->key == *from->p)
		from++;
	वापस (from > to);
पूर्ण

/**
 *	ext2_block_to_path - parse the block number पूर्णांकo array of offsets
 *	@inode: inode in question (we are only पूर्णांकerested in its superblock)
 *	@i_block: block number to be parsed
 *	@offsets: array to store the offsets in
 *      @boundary: set this non-zero अगर the referred-to block is likely to be
 *             followed (on disk) by an indirect block.
 *	To store the locations of file's data ext2 uses a data काष्ठाure common
 *	क्रम UNIX fileप्रणालीs - tree of poपूर्णांकers anchored in the inode, with
 *	data blocks at leaves and indirect blocks in पूर्णांकermediate nodes.
 *	This function translates the block number पूर्णांकo path in that tree -
 *	वापस value is the path length and @offsets[n] is the offset of
 *	poपूर्णांकer to (n+1)th node in the nth one. If @block is out of range
 *	(negative or too large) warning is prपूर्णांकed and zero वापसed.
 *
 *	Note: function करोesn't find node addresses, so no IO is needed. All
 *	we need to know is the capacity of indirect blocks (taken from the
 *	inode->i_sb).
 */

/*
 * Portability note: the last comparison (check that we fit पूर्णांकo triple
 * indirect block) is spelled dअगरferently, because otherwise on an
 * architecture with 32-bit दीर्घs and 8Kb pages we might get पूर्णांकo trouble
 * अगर our fileप्रणाली had 8Kb blocks. We might use दीर्घ दीर्घ, but that would
 * समाप्त us on x86. Oh, well, at least the sign propagation करोes not matter -
 * i_block would have to be negative in the very beginning, so we would not
 * get there at all.
 */

अटल पूर्णांक ext2_block_to_path(काष्ठा inode *inode,
			दीर्घ i_block, पूर्णांक offsets[4], पूर्णांक *boundary)
अणु
	पूर्णांक ptrs = EXT2_ADDR_PER_BLOCK(inode->i_sb);
	पूर्णांक ptrs_bits = EXT2_ADDR_PER_BLOCK_BITS(inode->i_sb);
	स्थिर दीर्घ direct_blocks = EXT2_Nसूची_BLOCKS,
		indirect_blocks = ptrs,
		द्विगुन_blocks = (1 << (ptrs_bits * 2));
	पूर्णांक n = 0;
	पूर्णांक final = 0;

	अगर (i_block < 0) अणु
		ext2_msg(inode->i_sb, KERN_WARNING,
			"warning: %s: block < 0", __func__);
	पूर्ण अन्यथा अगर (i_block < direct_blocks) अणु
		offsets[n++] = i_block;
		final = direct_blocks;
	पूर्ण अन्यथा अगर ( (i_block -= direct_blocks) < indirect_blocks) अणु
		offsets[n++] = EXT2_IND_BLOCK;
		offsets[n++] = i_block;
		final = ptrs;
	पूर्ण अन्यथा अगर ((i_block -= indirect_blocks) < द्विगुन_blocks) अणु
		offsets[n++] = EXT2_DIND_BLOCK;
		offsets[n++] = i_block >> ptrs_bits;
		offsets[n++] = i_block & (ptrs - 1);
		final = ptrs;
	पूर्ण अन्यथा अगर (((i_block -= द्विगुन_blocks) >> (ptrs_bits * 2)) < ptrs) अणु
		offsets[n++] = EXT2_TIND_BLOCK;
		offsets[n++] = i_block >> (ptrs_bits * 2);
		offsets[n++] = (i_block >> ptrs_bits) & (ptrs - 1);
		offsets[n++] = i_block & (ptrs - 1);
		final = ptrs;
	पूर्ण अन्यथा अणु
		ext2_msg(inode->i_sb, KERN_WARNING,
			"warning: %s: block is too big", __func__);
	पूर्ण
	अगर (boundary)
		*boundary = final - 1 - (i_block & (ptrs - 1));

	वापस n;
पूर्ण

/**
 *	ext2_get_branch - पढ़ो the chain of indirect blocks leading to data
 *	@inode: inode in question
 *	@depth: depth of the chain (1 - direct poपूर्णांकer, etc.)
 *	@offsets: offsets of poपूर्णांकers in inode/indirect blocks
 *	@chain: place to store the result
 *	@err: here we store the error value
 *
 *	Function fills the array of triples <key, p, bh> and वापसs %शून्य
 *	अगर everything went OK or the poपूर्णांकer to the last filled triple
 *	(incomplete one) otherwise. Upon the वापस chain[i].key contains
 *	the number of (i+1)-th block in the chain (as it is stored in memory,
 *	i.e. little-endian 32-bit), chain[i].p contains the address of that
 *	number (it poपूर्णांकs पूर्णांकo काष्ठा inode क्रम i==0 and पूर्णांकo the bh->b_data
 *	क्रम i>0) and chain[i].bh poपूर्णांकs to the buffer_head of i-th indirect
 *	block क्रम i>0 and शून्य क्रम i==0. In other words, it holds the block
 *	numbers of the chain, addresses they were taken from (and where we can
 *	verअगरy that chain did not change) and buffer_heads hosting these
 *	numbers.
 *
 *	Function stops when it stumbles upon zero poपूर्णांकer (असलent block)
 *		(poपूर्णांकer to last triple वापसed, *@err == 0)
 *	or when it माला_लो an IO error पढ़ोing an indirect block
 *		(ditto, *@err == -EIO)
 *	or when it notices that chain had been changed जबतक it was पढ़ोing
 *		(ditto, *@err == -EAGAIN)
 *	or when it पढ़ोs all @depth-1 indirect blocks successfully and finds
 *	the whole chain, all way to the data (वापसs %शून्य, *err == 0).
 */
अटल Indirect *ext2_get_branch(काष्ठा inode *inode,
				 पूर्णांक depth,
				 पूर्णांक *offsets,
				 Indirect chain[4],
				 पूर्णांक *err)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	Indirect *p = chain;
	काष्ठा buffer_head *bh;

	*err = 0;
	/* i_data is not going away, no lock needed */
	add_chain (chain, शून्य, EXT2_I(inode)->i_data + *offsets);
	अगर (!p->key)
		जाओ no_block;
	जबतक (--depth) अणु
		bh = sb_bपढ़ो(sb, le32_to_cpu(p->key));
		अगर (!bh)
			जाओ failure;
		पढ़ो_lock(&EXT2_I(inode)->i_meta_lock);
		अगर (!verअगरy_chain(chain, p))
			जाओ changed;
		add_chain(++p, bh, (__le32*)bh->b_data + *++offsets);
		पढ़ो_unlock(&EXT2_I(inode)->i_meta_lock);
		अगर (!p->key)
			जाओ no_block;
	पूर्ण
	वापस शून्य;

changed:
	पढ़ो_unlock(&EXT2_I(inode)->i_meta_lock);
	brअन्यथा(bh);
	*err = -EAGAIN;
	जाओ no_block;
failure:
	*err = -EIO;
no_block:
	वापस p;
पूर्ण

/**
 *	ext2_find_near - find a place क्रम allocation with sufficient locality
 *	@inode: owner
 *	@ind: descriptor of indirect block.
 *
 *	This function वापसs the preferred place क्रम block allocation.
 *	It is used when heuristic क्रम sequential allocation fails.
 *	Rules are:
 *	  + अगर there is a block to the left of our position - allocate near it.
 *	  + अगर poपूर्णांकer will live in indirect block - allocate near that block.
 *	  + अगर poपूर्णांकer will live in inode - allocate in the same cylinder group.
 *
 * In the latter हाल we colour the starting block by the callers PID to
 * prevent it from clashing with concurrent allocations क्रम a dअगरferent inode
 * in the same block group.   The PID is used here so that functionally related
 * files will be बंद-by on-disk.
 *
 *	Caller must make sure that @ind is valid and will stay that way.
 */

अटल ext2_fsblk_t ext2_find_near(काष्ठा inode *inode, Indirect *ind)
अणु
	काष्ठा ext2_inode_info *ei = EXT2_I(inode);
	__le32 *start = ind->bh ? (__le32 *) ind->bh->b_data : ei->i_data;
	__le32 *p;
	ext2_fsblk_t bg_start;
	ext2_fsblk_t colour;

	/* Try to find previous block */
	क्रम (p = ind->p - 1; p >= start; p--)
		अगर (*p)
			वापस le32_to_cpu(*p);

	/* No such thing, so let's try location of indirect block */
	अगर (ind->bh)
		वापस ind->bh->b_blocknr;

	/*
	 * It is going to be referred from inode itself? OK, just put it पूर्णांकo
	 * the same cylinder group then.
	 */
	bg_start = ext2_group_first_block_no(inode->i_sb, ei->i_block_group);
	colour = (current->pid % 16) *
			(EXT2_BLOCKS_PER_GROUP(inode->i_sb) / 16);
	वापस bg_start + colour;
पूर्ण

/**
 *	ext2_find_goal - find a preferred place क्रम allocation.
 *	@inode: owner
 *	@block:  block we want
 *	@partial: poपूर्णांकer to the last triple within a chain
 *
 *	Returns preferred place क्रम a block (the goal).
 */

अटल अंतरभूत ext2_fsblk_t ext2_find_goal(काष्ठा inode *inode, दीर्घ block,
					  Indirect *partial)
अणु
	काष्ठा ext2_block_alloc_info *block_i;

	block_i = EXT2_I(inode)->i_block_alloc_info;

	/*
	 * try the heuristic क्रम sequential allocation,
	 * failing that at least try to get decent locality.
	 */
	अगर (block_i && (block == block_i->last_alloc_logical_block + 1)
		&& (block_i->last_alloc_physical_block != 0)) अणु
		वापस block_i->last_alloc_physical_block + 1;
	पूर्ण

	वापस ext2_find_near(inode, partial);
पूर्ण

/**
 *	ext2_blks_to_allocate: Look up the block map and count the number
 *	of direct blocks need to be allocated क्रम the given branch.
 *
 * 	@branch: chain of indirect blocks
 *	@k: number of blocks need क्रम indirect blocks
 *	@blks: number of data blocks to be mapped.
 *	@blocks_to_boundary:  the offset in the indirect block
 *
 *	वापस the number of direct blocks to allocate.
 */
अटल पूर्णांक
ext2_blks_to_allocate(Indirect * branch, पूर्णांक k, अचिन्हित दीर्घ blks,
		पूर्णांक blocks_to_boundary)
अणु
	अचिन्हित दीर्घ count = 0;

	/*
	 * Simple हाल, [t,d]Indirect block(s) has not allocated yet
	 * then it's clear blocks on that path have not allocated
	 */
	अगर (k > 0) अणु
		/* right now करोn't hanel cross boundary allocation */
		अगर (blks < blocks_to_boundary + 1)
			count += blks;
		अन्यथा
			count += blocks_to_boundary + 1;
		वापस count;
	पूर्ण

	count++;
	जबतक (count < blks && count <= blocks_to_boundary
		&& le32_to_cpu(*(branch[0].p + count)) == 0) अणु
		count++;
	पूर्ण
	वापस count;
पूर्ण

/**
 *	ext2_alloc_blocks: multiple allocate blocks needed क्रम a branch
 *	@indirect_blks: the number of blocks need to allocate क्रम indirect
 *			blocks
 *	@blks: the number of blocks need to allocate क्रम direct blocks
 *	@new_blocks: on वापस it will store the new block numbers क्रम
 *	the indirect blocks(अगर needed) and the first direct block,
 */
अटल पूर्णांक ext2_alloc_blocks(काष्ठा inode *inode,
			ext2_fsblk_t goal, पूर्णांक indirect_blks, पूर्णांक blks,
			ext2_fsblk_t new_blocks[4], पूर्णांक *err)
अणु
	पूर्णांक target, i;
	अचिन्हित दीर्घ count = 0;
	पूर्णांक index = 0;
	ext2_fsblk_t current_block = 0;
	पूर्णांक ret = 0;

	/*
	 * Here we try to allocate the requested multiple blocks at once,
	 * on a best-efक्रमt basis.
	 * To build a branch, we should allocate blocks क्रम
	 * the indirect blocks(अगर not allocated yet), and at least
	 * the first direct block of this branch.  That's the
	 * minimum number of blocks need to allocate(required)
	 */
	target = blks + indirect_blks;

	जबतक (1) अणु
		count = target;
		/* allocating blocks क्रम indirect blocks and direct blocks */
		current_block = ext2_new_blocks(inode,goal,&count,err);
		अगर (*err)
			जाओ failed_out;

		target -= count;
		/* allocate blocks क्रम indirect blocks */
		जबतक (index < indirect_blks && count) अणु
			new_blocks[index++] = current_block++;
			count--;
		पूर्ण

		अगर (count > 0)
			अवरोध;
	पूर्ण

	/* save the new block number क्रम the first direct block */
	new_blocks[index] = current_block;

	/* total number of blocks allocated क्रम direct blocks */
	ret = count;
	*err = 0;
	वापस ret;
failed_out:
	क्रम (i = 0; i <index; i++)
		ext2_मुक्त_blocks(inode, new_blocks[i], 1);
	अगर (index)
		mark_inode_dirty(inode);
	वापस ret;
पूर्ण

/**
 *	ext2_alloc_branch - allocate and set up a chain of blocks.
 *	@inode: owner
 *	@indirect_blks: depth of the chain (number of blocks to allocate)
 *	@blks: number of allocated direct blocks
 *	@goal: preferred place क्रम allocation
 *	@offsets: offsets (in the blocks) to store the poपूर्णांकers to next.
 *	@branch: place to store the chain in.
 *
 *	This function allocates @num blocks, zeroes out all but the last one,
 *	links them पूर्णांकo chain and (अगर we are synchronous) ग_लिखोs them to disk.
 *	In other words, it prepares a branch that can be spliced onto the
 *	inode. It stores the inक्रमmation about that chain in the branch[], in
 *	the same क्रमmat as ext2_get_branch() would करो. We are calling it after
 *	we had पढ़ो the existing part of chain and partial poपूर्णांकs to the last
 *	triple of that (one with zero ->key). Upon the निकास we have the same
 *	picture as after the successful ext2_get_block(), except that in one
 *	place chain is disconnected - *branch->p is still zero (we did not
 *	set the last link), but branch->key contains the number that should
 *	be placed पूर्णांकo *branch->p to fill that gap.
 *
 *	If allocation fails we मुक्त all blocks we've allocated (and क्रमget
 *	their buffer_heads) and वापस the error value the from failed
 *	ext2_alloc_block() (normally -ENOSPC). Otherwise we set the chain
 *	as described above and वापस 0.
 */

अटल पूर्णांक ext2_alloc_branch(काष्ठा inode *inode,
			पूर्णांक indirect_blks, पूर्णांक *blks, ext2_fsblk_t goal,
			पूर्णांक *offsets, Indirect *branch)
अणु
	पूर्णांक blocksize = inode->i_sb->s_blocksize;
	पूर्णांक i, n = 0;
	पूर्णांक err = 0;
	काष्ठा buffer_head *bh;
	पूर्णांक num;
	ext2_fsblk_t new_blocks[4];
	ext2_fsblk_t current_block;

	num = ext2_alloc_blocks(inode, goal, indirect_blks,
				*blks, new_blocks, &err);
	अगर (err)
		वापस err;

	branch[0].key = cpu_to_le32(new_blocks[0]);
	/*
	 * metadata blocks and data blocks are allocated.
	 */
	क्रम (n = 1; n <= indirect_blks;  n++) अणु
		/*
		 * Get buffer_head क्रम parent block, zero it out
		 * and set the poपूर्णांकer to new one, then send
		 * parent to disk.
		 */
		bh = sb_getblk(inode->i_sb, new_blocks[n-1]);
		अगर (unlikely(!bh)) अणु
			err = -ENOMEM;
			जाओ failed;
		पूर्ण
		branch[n].bh = bh;
		lock_buffer(bh);
		स_रखो(bh->b_data, 0, blocksize);
		branch[n].p = (__le32 *) bh->b_data + offsets[n];
		branch[n].key = cpu_to_le32(new_blocks[n]);
		*branch[n].p = branch[n].key;
		अगर ( n == indirect_blks) अणु
			current_block = new_blocks[n];
			/*
			 * End of chain, update the last new metablock of
			 * the chain to poपूर्णांक to the new allocated
			 * data blocks numbers
			 */
			क्रम (i=1; i < num; i++)
				*(branch[n].p + i) = cpu_to_le32(++current_block);
		पूर्ण
		set_buffer_uptodate(bh);
		unlock_buffer(bh);
		mark_buffer_dirty_inode(bh, inode);
		/* We used to sync bh here अगर IS_SYNC(inode).
		 * But we now rely upon generic_ग_लिखो_sync()
		 * and b_inode_buffers.  But not क्रम directories.
		 */
		अगर (S_ISसूची(inode->i_mode) && IS_सूचीSYNC(inode))
			sync_dirty_buffer(bh);
	पूर्ण
	*blks = num;
	वापस err;

failed:
	क्रम (i = 1; i < n; i++)
		bक्रमget(branch[i].bh);
	क्रम (i = 0; i < indirect_blks; i++)
		ext2_मुक्त_blocks(inode, new_blocks[i], 1);
	ext2_मुक्त_blocks(inode, new_blocks[i], num);
	वापस err;
पूर्ण

/**
 * ext2_splice_branch - splice the allocated branch onto inode.
 * @inode: owner
 * @block: (logical) number of block we are adding
 * @where: location of missing link
 * @num:   number of indirect blocks we are adding
 * @blks:  number of direct blocks we are adding
 *
 * This function fills the missing link and करोes all housekeeping needed in
 * inode (->i_blocks, etc.). In हाल of success we end up with the full
 * chain to new block and वापस 0.
 */
अटल व्योम ext2_splice_branch(काष्ठा inode *inode,
			दीर्घ block, Indirect *where, पूर्णांक num, पूर्णांक blks)
अणु
	पूर्णांक i;
	काष्ठा ext2_block_alloc_info *block_i;
	ext2_fsblk_t current_block;

	block_i = EXT2_I(inode)->i_block_alloc_info;

	/* XXX LOCKING probably should have i_meta_lock ?*/
	/* That's it */

	*where->p = where->key;

	/*
	 * Update the host buffer_head or inode to poपूर्णांक to more just allocated
	 * direct blocks blocks
	 */
	अगर (num == 0 && blks > 1) अणु
		current_block = le32_to_cpu(where->key) + 1;
		क्रम (i = 1; i < blks; i++)
			*(where->p + i ) = cpu_to_le32(current_block++);
	पूर्ण

	/*
	 * update the most recently allocated logical & physical block
	 * in i_block_alloc_info, to assist find the proper goal block क्रम next
	 * allocation
	 */
	अगर (block_i) अणु
		block_i->last_alloc_logical_block = block + blks - 1;
		block_i->last_alloc_physical_block =
				le32_to_cpu(where[num].key) + blks - 1;
	पूर्ण

	/* We are करोne with atomic stuff, now करो the rest of housekeeping */

	/* had we spliced it onto indirect block? */
	अगर (where->bh)
		mark_buffer_dirty_inode(where->bh, inode);

	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
पूर्ण

/*
 * Allocation strategy is simple: अगर we have to allocate something, we will
 * have to go the whole way to leaf. So let's करो it beक्रमe attaching anything
 * to tree, set linkage between the newborn blocks, ग_लिखो them अगर sync is
 * required, recheck the path, मुक्त and repeat अगर check fails, otherwise
 * set the last missing link (that will protect us from any truncate-generated
 * removals - all blocks on the path are immune now) and possibly क्रमce the
 * ग_लिखो on the parent block.
 * That has a nice additional property: no special recovery from the failed
 * allocations is needed - we simply release blocks and करो not touch anything
 * reachable from inode.
 *
 * `handle' can be शून्य अगर create == 0.
 *
 * वापस > 0, # of blocks mapped or allocated.
 * वापस = 0, अगर plain lookup failed.
 * वापस < 0, error हाल.
 */
अटल पूर्णांक ext2_get_blocks(काष्ठा inode *inode,
			   sector_t iblock, अचिन्हित दीर्घ maxblocks,
			   u32 *bno, bool *new, bool *boundary,
			   पूर्णांक create)
अणु
	पूर्णांक err;
	पूर्णांक offsets[4];
	Indirect chain[4];
	Indirect *partial;
	ext2_fsblk_t goal;
	पूर्णांक indirect_blks;
	पूर्णांक blocks_to_boundary = 0;
	पूर्णांक depth;
	काष्ठा ext2_inode_info *ei = EXT2_I(inode);
	पूर्णांक count = 0;
	ext2_fsblk_t first_block = 0;

	BUG_ON(maxblocks == 0);

	depth = ext2_block_to_path(inode,iblock,offsets,&blocks_to_boundary);

	अगर (depth == 0)
		वापस -EIO;

	partial = ext2_get_branch(inode, depth, offsets, chain, &err);
	/* Simplest हाल - block found, no allocation needed */
	अगर (!partial) अणु
		first_block = le32_to_cpu(chain[depth - 1].key);
		count++;
		/*map more blocks*/
		जबतक (count < maxblocks && count <= blocks_to_boundary) अणु
			ext2_fsblk_t blk;

			अगर (!verअगरy_chain(chain, chain + depth - 1)) अणु
				/*
				 * Indirect block might be हटाओd by
				 * truncate जबतक we were पढ़ोing it.
				 * Handling of that हाल: क्रमget what we've
				 * got now, go to reपढ़ो.
				 */
				err = -EAGAIN;
				count = 0;
				partial = chain + depth - 1;
				अवरोध;
			पूर्ण
			blk = le32_to_cpu(*(chain[depth-1].p + count));
			अगर (blk == first_block + count)
				count++;
			अन्यथा
				अवरोध;
		पूर्ण
		अगर (err != -EAGAIN)
			जाओ got_it;
	पूर्ण

	/* Next simple हाल - plain lookup or failed पढ़ो of indirect block */
	अगर (!create || err == -EIO)
		जाओ cleanup;

	mutex_lock(&ei->truncate_mutex);
	/*
	 * If the indirect block is missing जबतक we are पढ़ोing
	 * the chain(ext2_get_branch() वापसs -EAGAIN err), or
	 * अगर the chain has been changed after we grab the semaphore,
	 * (either because another process truncated this branch, or
	 * another get_block allocated this branch) re-grab the chain to see अगर
	 * the request block has been allocated or not.
	 *
	 * Since we alपढ़ोy block the truncate/other get_block
	 * at this poपूर्णांक, we will have the current copy of the chain when we
	 * splice the branch पूर्णांकo the tree.
	 */
	अगर (err == -EAGAIN || !verअगरy_chain(chain, partial)) अणु
		जबतक (partial > chain) अणु
			brअन्यथा(partial->bh);
			partial--;
		पूर्ण
		partial = ext2_get_branch(inode, depth, offsets, chain, &err);
		अगर (!partial) अणु
			count++;
			mutex_unlock(&ei->truncate_mutex);
			जाओ got_it;
		पूर्ण

		अगर (err) अणु
			mutex_unlock(&ei->truncate_mutex);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/*
	 * Okay, we need to करो block allocation.  Lazily initialize the block
	 * allocation info here अगर necessary
	*/
	अगर (S_ISREG(inode->i_mode) && (!ei->i_block_alloc_info))
		ext2_init_block_alloc_info(inode);

	goal = ext2_find_goal(inode, iblock, partial);

	/* the number of blocks need to allocate क्रम [d,t]indirect blocks */
	indirect_blks = (chain + depth) - partial - 1;
	/*
	 * Next look up the indirect map to count the total number of
	 * direct blocks to allocate क्रम this branch.
	 */
	count = ext2_blks_to_allocate(partial, indirect_blks,
					maxblocks, blocks_to_boundary);
	/*
	 * XXX ???? Block out ext2_truncate जबतक we alter the tree
	 */
	err = ext2_alloc_branch(inode, indirect_blks, &count, goal,
				offsets + (partial - chain), partial);

	अगर (err) अणु
		mutex_unlock(&ei->truncate_mutex);
		जाओ cleanup;
	पूर्ण

	अगर (IS_DAX(inode)) अणु
		/*
		 * We must unmap blocks beक्रमe zeroing so that ग_लिखोback cannot
		 * overग_लिखो zeros with stale data from block device page cache.
		 */
		clean_bdev_aliases(inode->i_sb->s_bdev,
				   le32_to_cpu(chain[depth-1].key),
				   count);
		/*
		 * block must be initialised beक्रमe we put it in the tree
		 * so that it's not found by another thread before it's
		 * initialised
		 */
		err = sb_issue_zeroout(inode->i_sb,
				le32_to_cpu(chain[depth-1].key), count,
				GFP_NOFS);
		अगर (err) अणु
			mutex_unlock(&ei->truncate_mutex);
			जाओ cleanup;
		पूर्ण
	पूर्ण
	*new = true;

	ext2_splice_branch(inode, iblock, partial, indirect_blks, count);
	mutex_unlock(&ei->truncate_mutex);
got_it:
	अगर (count > blocks_to_boundary)
		*boundary = true;
	err = count;
	/* Clean up and निकास */
	partial = chain + depth - 1;	/* the whole chain */
cleanup:
	जबतक (partial > chain) अणु
		brअन्यथा(partial->bh);
		partial--;
	पूर्ण
	अगर (err > 0)
		*bno = le32_to_cpu(chain[depth-1].key);
	वापस err;
पूर्ण

पूर्णांक ext2_get_block(काष्ठा inode *inode, sector_t iblock,
		काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	अचिन्हित max_blocks = bh_result->b_size >> inode->i_blkbits;
	bool new = false, boundary = false;
	u32 bno;
	पूर्णांक ret;

	ret = ext2_get_blocks(inode, iblock, max_blocks, &bno, &new, &boundary,
			create);
	अगर (ret <= 0)
		वापस ret;

	map_bh(bh_result, inode->i_sb, bno);
	bh_result->b_size = (ret << inode->i_blkbits);
	अगर (new)
		set_buffer_new(bh_result);
	अगर (boundary)
		set_buffer_boundary(bh_result);
	वापस 0;

पूर्ण

#अगर_घोषित CONFIG_FS_DAX
अटल पूर्णांक ext2_iomap_begin(काष्ठा inode *inode, loff_t offset, loff_t length,
		अचिन्हित flags, काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	अचिन्हित पूर्णांक blkbits = inode->i_blkbits;
	अचिन्हित दीर्घ first_block = offset >> blkbits;
	अचिन्हित दीर्घ max_blocks = (length + (1 << blkbits) - 1) >> blkbits;
	काष्ठा ext2_sb_info *sbi = EXT2_SB(inode->i_sb);
	bool new = false, boundary = false;
	u32 bno;
	पूर्णांक ret;

	ret = ext2_get_blocks(inode, first_block, max_blocks,
			&bno, &new, &boundary, flags & IOMAP_WRITE);
	अगर (ret < 0)
		वापस ret;

	iomap->flags = 0;
	iomap->bdev = inode->i_sb->s_bdev;
	iomap->offset = (u64)first_block << blkbits;
	iomap->dax_dev = sbi->s_daxdev;

	अगर (ret == 0) अणु
		iomap->type = IOMAP_HOLE;
		iomap->addr = IOMAP_शून्य_ADDR;
		iomap->length = 1 << blkbits;
	पूर्ण अन्यथा अणु
		iomap->type = IOMAP_MAPPED;
		iomap->addr = (u64)bno << blkbits;
		iomap->length = (u64)ret << blkbits;
		iomap->flags |= IOMAP_F_MERGED;
	पूर्ण

	अगर (new)
		iomap->flags |= IOMAP_F_NEW;
	वापस 0;
पूर्ण

अटल पूर्णांक
ext2_iomap_end(काष्ठा inode *inode, loff_t offset, loff_t length,
		sमाप_प्रकार written, अचिन्हित flags, काष्ठा iomap *iomap)
अणु
	अगर (iomap->type == IOMAP_MAPPED &&
	    written < length &&
	    (flags & IOMAP_WRITE))
		ext2_ग_लिखो_failed(inode->i_mapping, offset + length);
	वापस 0;
पूर्ण

स्थिर काष्ठा iomap_ops ext2_iomap_ops = अणु
	.iomap_begin		= ext2_iomap_begin,
	.iomap_end		= ext2_iomap_end,
पूर्ण;
#अन्यथा
/* Define empty ops क्रम !CONFIG_FS_DAX हाल to aव्योम ugly अगरdefs */
स्थिर काष्ठा iomap_ops ext2_iomap_ops;
#पूर्ण_अगर /* CONFIG_FS_DAX */

पूर्णांक ext2_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		u64 start, u64 len)
अणु
	वापस generic_block_fiemap(inode, fieinfo, start, len,
				    ext2_get_block);
पूर्ण

अटल पूर्णांक ext2_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, ext2_get_block, wbc);
पूर्ण

अटल पूर्णांक ext2_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस mpage_पढ़ोpage(page, ext2_get_block);
पूर्ण

अटल व्योम ext2_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, ext2_get_block);
पूर्ण

अटल पूर्णांक
ext2_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
		loff_t pos, अचिन्हित len, अचिन्हित flags,
		काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	ret = block_ग_लिखो_begin(mapping, pos, len, flags, pagep,
				ext2_get_block);
	अगर (ret < 0)
		ext2_ग_लिखो_failed(mapping, pos + len);
	वापस ret;
पूर्ण

अटल पूर्णांक ext2_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	पूर्णांक ret;

	ret = generic_ग_लिखो_end(file, mapping, pos, len, copied, page, fsdata);
	अगर (ret < len)
		ext2_ग_लिखो_failed(mapping, pos + len);
	वापस ret;
पूर्ण

अटल पूर्णांक
ext2_nobh_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
		loff_t pos, अचिन्हित len, अचिन्हित flags,
		काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	ret = nobh_ग_लिखो_begin(mapping, pos, len, flags, pagep, fsdata,
			       ext2_get_block);
	अगर (ret < 0)
		ext2_ग_लिखो_failed(mapping, pos + len);
	वापस ret;
पूर्ण

अटल पूर्णांक ext2_nobh_ग_लिखोpage(काष्ठा page *page,
			काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस nobh_ग_लिखोpage(page, ext2_get_block, wbc);
पूर्ण

अटल sector_t ext2_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping,block,ext2_get_block);
पूर्ण

अटल sमाप_प्रकार
ext2_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	माप_प्रकार count = iov_iter_count(iter);
	loff_t offset = iocb->ki_pos;
	sमाप_प्रकार ret;

	ret = blockdev_direct_IO(iocb, inode, iter, ext2_get_block);
	अगर (ret < 0 && iov_iter_rw(iter) == WRITE)
		ext2_ग_लिखो_failed(mapping, offset + count);
	वापस ret;
पूर्ण

अटल पूर्णांक
ext2_ग_लिखोpages(काष्ठा address_space *mapping, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस mpage_ग_लिखोpages(mapping, wbc, ext2_get_block);
पूर्ण

अटल पूर्णांक
ext2_dax_ग_लिखोpages(काष्ठा address_space *mapping, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा ext2_sb_info *sbi = EXT2_SB(mapping->host->i_sb);

	वापस dax_ग_लिखोback_mapping_range(mapping, sbi->s_daxdev, wbc);
पूर्ण

स्थिर काष्ठा address_space_operations ext2_aops = अणु
	.पढ़ोpage		= ext2_पढ़ोpage,
	.पढ़ोahead		= ext2_पढ़ोahead,
	.ग_लिखोpage		= ext2_ग_लिखोpage,
	.ग_लिखो_begin		= ext2_ग_लिखो_begin,
	.ग_लिखो_end		= ext2_ग_लिखो_end,
	.bmap			= ext2_bmap,
	.direct_IO		= ext2_direct_IO,
	.ग_लिखोpages		= ext2_ग_लिखोpages,
	.migratepage		= buffer_migrate_page,
	.is_partially_uptodate	= block_is_partially_uptodate,
	.error_हटाओ_page	= generic_error_हटाओ_page,
पूर्ण;

स्थिर काष्ठा address_space_operations ext2_nobh_aops = अणु
	.पढ़ोpage		= ext2_पढ़ोpage,
	.पढ़ोahead		= ext2_पढ़ोahead,
	.ग_लिखोpage		= ext2_nobh_ग_लिखोpage,
	.ग_लिखो_begin		= ext2_nobh_ग_लिखो_begin,
	.ग_लिखो_end		= nobh_ग_लिखो_end,
	.bmap			= ext2_bmap,
	.direct_IO		= ext2_direct_IO,
	.ग_लिखोpages		= ext2_ग_लिखोpages,
	.migratepage		= buffer_migrate_page,
	.error_हटाओ_page	= generic_error_हटाओ_page,
पूर्ण;

अटल स्थिर काष्ठा address_space_operations ext2_dax_aops = अणु
	.ग_लिखोpages		= ext2_dax_ग_लिखोpages,
	.direct_IO		= noop_direct_IO,
	.set_page_dirty		= noop_set_page_dirty,
	.invalidatepage		= noop_invalidatepage,
पूर्ण;

/*
 * Probably it should be a library function... search क्रम first non-zero word
 * or स_भेद with zero_page, whatever is better क्रम particular architecture.
 * Linus?
 */
अटल अंतरभूत पूर्णांक all_zeroes(__le32 *p, __le32 *q)
अणु
	जबतक (p < q)
		अगर (*p++)
			वापस 0;
	वापस 1;
पूर्ण

/**
 *	ext2_find_shared - find the indirect blocks क्रम partial truncation.
 *	@inode:	  inode in question
 *	@depth:	  depth of the affected branch
 *	@offsets: offsets of poपूर्णांकers in that branch (see ext2_block_to_path)
 *	@chain:	  place to store the poपूर्णांकers to partial indirect blocks
 *	@top:	  place to the (detached) top of branch
 *
 *	This is a helper function used by ext2_truncate().
 *
 *	When we करो truncate() we may have to clean the ends of several indirect
 *	blocks but leave the blocks themselves alive. Block is partially
 *	truncated अगर some data below the new i_size is referred from it (and
 *	it is on the path to the first completely truncated data block, indeed).
 *	We have to मुक्त the top of that path aदीर्घ with everything to the right
 *	of the path. Since no allocation past the truncation poपूर्णांक is possible
 *	until ext2_truncate() finishes, we may safely करो the latter, but top
 *	of branch may require special attention - pageout below the truncation
 *	poपूर्णांक might try to populate it.
 *
 *	We atomically detach the top of branch from the tree, store the block
 *	number of its root in *@top, poपूर्णांकers to buffer_heads of partially
 *	truncated blocks - in @chain[].bh and poपूर्णांकers to their last elements
 *	that should not be हटाओd - in @chain[].p. Return value is the poपूर्णांकer
 *	to last filled element of @chain.
 *
 *	The work left to caller to करो the actual मुक्तing of subtrees:
 *		a) मुक्त the subtree starting from *@top
 *		b) मुक्त the subtrees whose roots are stored in
 *			(@chain[i].p+1 .. end of @chain[i].bh->b_data)
 *		c) मुक्त the subtrees growing from the inode past the @chain[0].p
 *			(no partially truncated stuff there).
 */

अटल Indirect *ext2_find_shared(काष्ठा inode *inode,
				पूर्णांक depth,
				पूर्णांक offsets[4],
				Indirect chain[4],
				__le32 *top)
अणु
	Indirect *partial, *p;
	पूर्णांक k, err;

	*top = 0;
	क्रम (k = depth; k > 1 && !offsets[k-1]; k--)
		;
	partial = ext2_get_branch(inode, k, offsets, chain, &err);
	अगर (!partial)
		partial = chain + k-1;
	/*
	 * If the branch acquired continuation since we've looked at it -
	 * fine, it should all survive and (new) top करोesn't beदीर्घ to us.
	 */
	ग_लिखो_lock(&EXT2_I(inode)->i_meta_lock);
	अगर (!partial->key && *partial->p) अणु
		ग_लिखो_unlock(&EXT2_I(inode)->i_meta_lock);
		जाओ no_top;
	पूर्ण
	क्रम (p=partial; p>chain && all_zeroes((__le32*)p->bh->b_data,p->p); p--)
		;
	/*
	 * OK, we've found the last block that must survive. The rest of our
	 * branch should be detached beक्रमe unlocking. However, अगर that rest
	 * of branch is all ours and करोes not grow immediately from the inode
	 * it's easier to cheat and just decrement partial->p.
	 */
	अगर (p == chain + k - 1 && p > chain) अणु
		p->p--;
	पूर्ण अन्यथा अणु
		*top = *p->p;
		*p->p = 0;
	पूर्ण
	ग_लिखो_unlock(&EXT2_I(inode)->i_meta_lock);

	जबतक(partial > p)
	अणु
		brअन्यथा(partial->bh);
		partial--;
	पूर्ण
no_top:
	वापस partial;
पूर्ण

/**
 *	ext2_मुक्त_data - मुक्त a list of data blocks
 *	@inode:	inode we are dealing with
 *	@p:	array of block numbers
 *	@q:	poपूर्णांकs immediately past the end of array
 *
 *	We are मुक्तing all blocks referred from that array (numbers are
 *	stored as little-endian 32-bit) and updating @inode->i_blocks
 *	appropriately.
 */
अटल अंतरभूत व्योम ext2_मुक्त_data(काष्ठा inode *inode, __le32 *p, __le32 *q)
अणु
	अचिन्हित दीर्घ block_to_मुक्त = 0, count = 0;
	अचिन्हित दीर्घ nr;

	क्रम ( ; p < q ; p++) अणु
		nr = le32_to_cpu(*p);
		अगर (nr) अणु
			*p = 0;
			/* accumulate blocks to मुक्त अगर they're contiguous */
			अगर (count == 0)
				जाओ मुक्त_this;
			अन्यथा अगर (block_to_मुक्त == nr - count)
				count++;
			अन्यथा अणु
				ext2_मुक्त_blocks (inode, block_to_मुक्त, count);
				mark_inode_dirty(inode);
			मुक्त_this:
				block_to_मुक्त = nr;
				count = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (count > 0) अणु
		ext2_मुक्त_blocks (inode, block_to_मुक्त, count);
		mark_inode_dirty(inode);
	पूर्ण
पूर्ण

/**
 *	ext2_मुक्त_branches - मुक्त an array of branches
 *	@inode:	inode we are dealing with
 *	@p:	array of block numbers
 *	@q:	poपूर्णांकer immediately past the end of array
 *	@depth:	depth of the branches to मुक्त
 *
 *	We are मुक्तing all blocks referred from these branches (numbers are
 *	stored as little-endian 32-bit) and updating @inode->i_blocks
 *	appropriately.
 */
अटल व्योम ext2_मुक्त_branches(काष्ठा inode *inode, __le32 *p, __le32 *q, पूर्णांक depth)
अणु
	काष्ठा buffer_head * bh;
	अचिन्हित दीर्घ nr;

	अगर (depth--) अणु
		पूर्णांक addr_per_block = EXT2_ADDR_PER_BLOCK(inode->i_sb);
		क्रम ( ; p < q ; p++) अणु
			nr = le32_to_cpu(*p);
			अगर (!nr)
				जारी;
			*p = 0;
			bh = sb_bपढ़ो(inode->i_sb, nr);
			/*
			 * A पढ़ो failure? Report error and clear slot
			 * (should be rare).
			 */ 
			अगर (!bh) अणु
				ext2_error(inode->i_sb, "ext2_free_branches",
					"Read failure, inode=%ld, block=%ld",
					inode->i_ino, nr);
				जारी;
			पूर्ण
			ext2_मुक्त_branches(inode,
					   (__le32*)bh->b_data,
					   (__le32*)bh->b_data + addr_per_block,
					   depth);
			bक्रमget(bh);
			ext2_मुक्त_blocks(inode, nr, 1);
			mark_inode_dirty(inode);
		पूर्ण
	पूर्ण अन्यथा
		ext2_मुक्त_data(inode, p, q);
पूर्ण

/* dax_sem must be held when calling this function */
अटल व्योम __ext2_truncate_blocks(काष्ठा inode *inode, loff_t offset)
अणु
	__le32 *i_data = EXT2_I(inode)->i_data;
	काष्ठा ext2_inode_info *ei = EXT2_I(inode);
	पूर्णांक addr_per_block = EXT2_ADDR_PER_BLOCK(inode->i_sb);
	पूर्णांक offsets[4];
	Indirect chain[4];
	Indirect *partial;
	__le32 nr = 0;
	पूर्णांक n;
	दीर्घ iblock;
	अचिन्हित blocksize;
	blocksize = inode->i_sb->s_blocksize;
	iblock = (offset + blocksize-1) >> EXT2_BLOCK_SIZE_BITS(inode->i_sb);

#अगर_घोषित CONFIG_FS_DAX
	WARN_ON(!rwsem_is_locked(&ei->dax_sem));
#पूर्ण_अगर

	n = ext2_block_to_path(inode, iblock, offsets, शून्य);
	अगर (n == 0)
		वापस;

	/*
	 * From here we block out all ext2_get_block() callers who want to
	 * modअगरy the block allocation tree.
	 */
	mutex_lock(&ei->truncate_mutex);

	अगर (n == 1) अणु
		ext2_मुक्त_data(inode, i_data+offsets[0],
					i_data + EXT2_Nसूची_BLOCKS);
		जाओ करो_indirects;
	पूर्ण

	partial = ext2_find_shared(inode, n, offsets, chain, &nr);
	/* Kill the top of shared branch (alपढ़ोy detached) */
	अगर (nr) अणु
		अगर (partial == chain)
			mark_inode_dirty(inode);
		अन्यथा
			mark_buffer_dirty_inode(partial->bh, inode);
		ext2_मुक्त_branches(inode, &nr, &nr+1, (chain+n-1) - partial);
	पूर्ण
	/* Clear the ends of indirect blocks on the shared branch */
	जबतक (partial > chain) अणु
		ext2_मुक्त_branches(inode,
				   partial->p + 1,
				   (__le32*)partial->bh->b_data+addr_per_block,
				   (chain+n-1) - partial);
		mark_buffer_dirty_inode(partial->bh, inode);
		brअन्यथा (partial->bh);
		partial--;
	पूर्ण
करो_indirects:
	/* Kill the reमुख्यing (whole) subtrees */
	चयन (offsets[0]) अणु
		शेष:
			nr = i_data[EXT2_IND_BLOCK];
			अगर (nr) अणु
				i_data[EXT2_IND_BLOCK] = 0;
				mark_inode_dirty(inode);
				ext2_मुक्त_branches(inode, &nr, &nr+1, 1);
			पूर्ण
			fallthrough;
		हाल EXT2_IND_BLOCK:
			nr = i_data[EXT2_DIND_BLOCK];
			अगर (nr) अणु
				i_data[EXT2_DIND_BLOCK] = 0;
				mark_inode_dirty(inode);
				ext2_मुक्त_branches(inode, &nr, &nr+1, 2);
			पूर्ण
			fallthrough;
		हाल EXT2_DIND_BLOCK:
			nr = i_data[EXT2_TIND_BLOCK];
			अगर (nr) अणु
				i_data[EXT2_TIND_BLOCK] = 0;
				mark_inode_dirty(inode);
				ext2_मुक्त_branches(inode, &nr, &nr+1, 3);
			पूर्ण
			अवरोध;
		हाल EXT2_TIND_BLOCK:
			;
	पूर्ण

	ext2_discard_reservation(inode);

	mutex_unlock(&ei->truncate_mutex);
पूर्ण

अटल व्योम ext2_truncate_blocks(काष्ठा inode *inode, loff_t offset)
अणु
	अगर (!(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
	    S_ISLNK(inode->i_mode)))
		वापस;
	अगर (ext2_inode_is_fast_symlink(inode))
		वापस;

	dax_sem_करोwn_ग_लिखो(EXT2_I(inode));
	__ext2_truncate_blocks(inode, offset);
	dax_sem_up_ग_लिखो(EXT2_I(inode));
पूर्ण

अटल पूर्णांक ext2_setsize(काष्ठा inode *inode, loff_t newsize)
अणु
	पूर्णांक error;

	अगर (!(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
	    S_ISLNK(inode->i_mode)))
		वापस -EINVAL;
	अगर (ext2_inode_is_fast_symlink(inode))
		वापस -EINVAL;
	अगर (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		वापस -EPERM;

	inode_dio_रुको(inode);

	अगर (IS_DAX(inode)) अणु
		error = iomap_zero_range(inode, newsize,
					 PAGE_ALIGN(newsize) - newsize, शून्य,
					 &ext2_iomap_ops);
	पूर्ण अन्यथा अगर (test_opt(inode->i_sb, NOBH))
		error = nobh_truncate_page(inode->i_mapping,
				newsize, ext2_get_block);
	अन्यथा
		error = block_truncate_page(inode->i_mapping,
				newsize, ext2_get_block);
	अगर (error)
		वापस error;

	dax_sem_करोwn_ग_लिखो(EXT2_I(inode));
	truncate_setsize(inode, newsize);
	__ext2_truncate_blocks(inode, newsize);
	dax_sem_up_ग_लिखो(EXT2_I(inode));

	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	अगर (inode_needs_sync(inode)) अणु
		sync_mapping_buffers(inode->i_mapping);
		sync_inode_metadata(inode, 1);
	पूर्ण अन्यथा अणु
		mark_inode_dirty(inode);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ext2_inode *ext2_get_inode(काष्ठा super_block *sb, ino_t ino,
					काष्ठा buffer_head **p)
अणु
	काष्ठा buffer_head * bh;
	अचिन्हित दीर्घ block_group;
	अचिन्हित दीर्घ block;
	अचिन्हित दीर्घ offset;
	काष्ठा ext2_group_desc * gdp;

	*p = शून्य;
	अगर ((ino != EXT2_ROOT_INO && ino < EXT2_FIRST_INO(sb)) ||
	    ino > le32_to_cpu(EXT2_SB(sb)->s_es->s_inodes_count))
		जाओ Einval;

	block_group = (ino - 1) / EXT2_INODES_PER_GROUP(sb);
	gdp = ext2_get_group_desc(sb, block_group, शून्य);
	अगर (!gdp)
		जाओ Egdp;
	/*
	 * Figure out the offset within the block group inode table
	 */
	offset = ((ino - 1) % EXT2_INODES_PER_GROUP(sb)) * EXT2_INODE_SIZE(sb);
	block = le32_to_cpu(gdp->bg_inode_table) +
		(offset >> EXT2_BLOCK_SIZE_BITS(sb));
	अगर (!(bh = sb_bपढ़ो(sb, block)))
		जाओ Eio;

	*p = bh;
	offset &= (EXT2_BLOCK_SIZE(sb) - 1);
	वापस (काष्ठा ext2_inode *) (bh->b_data + offset);

Einval:
	ext2_error(sb, "ext2_get_inode", "bad inode number: %lu",
		   (अचिन्हित दीर्घ) ino);
	वापस ERR_PTR(-EINVAL);
Eio:
	ext2_error(sb, "ext2_get_inode",
		   "unable to read inode block - inode=%lu, block=%lu",
		   (अचिन्हित दीर्घ) ino, block);
Egdp:
	वापस ERR_PTR(-EIO);
पूर्ण

व्योम ext2_set_inode_flags(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक flags = EXT2_I(inode)->i_flags;

	inode->i_flags &= ~(S_SYNC | S_APPEND | S_IMMUTABLE | S_NOATIME |
				S_सूचीSYNC | S_DAX);
	अगर (flags & EXT2_SYNC_FL)
		inode->i_flags |= S_SYNC;
	अगर (flags & EXT2_APPEND_FL)
		inode->i_flags |= S_APPEND;
	अगर (flags & EXT2_IMMUTABLE_FL)
		inode->i_flags |= S_IMMUTABLE;
	अगर (flags & EXT2_NOATIME_FL)
		inode->i_flags |= S_NOATIME;
	अगर (flags & EXT2_सूचीSYNC_FL)
		inode->i_flags |= S_सूचीSYNC;
	अगर (test_opt(inode->i_sb, DAX) && S_ISREG(inode->i_mode))
		inode->i_flags |= S_DAX;
पूर्ण

व्योम ext2_set_file_ops(काष्ठा inode *inode)
अणु
	inode->i_op = &ext2_file_inode_operations;
	inode->i_fop = &ext2_file_operations;
	अगर (IS_DAX(inode))
		inode->i_mapping->a_ops = &ext2_dax_aops;
	अन्यथा अगर (test_opt(inode->i_sb, NOBH))
		inode->i_mapping->a_ops = &ext2_nobh_aops;
	अन्यथा
		inode->i_mapping->a_ops = &ext2_aops;
पूर्ण

काष्ठा inode *ext2_iget (काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा ext2_inode_info *ei;
	काष्ठा buffer_head * bh = शून्य;
	काष्ठा ext2_inode *raw_inode;
	काष्ठा inode *inode;
	दीर्घ ret = -EIO;
	पूर्णांक n;
	uid_t i_uid;
	gid_t i_gid;

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	ei = EXT2_I(inode);
	ei->i_block_alloc_info = शून्य;

	raw_inode = ext2_get_inode(inode->i_sb, ino, &bh);
	अगर (IS_ERR(raw_inode)) अणु
		ret = PTR_ERR(raw_inode);
 		जाओ bad_inode;
	पूर्ण

	inode->i_mode = le16_to_cpu(raw_inode->i_mode);
	i_uid = (uid_t)le16_to_cpu(raw_inode->i_uid_low);
	i_gid = (gid_t)le16_to_cpu(raw_inode->i_gid_low);
	अगर (!(test_opt (inode->i_sb, NO_UID32))) अणु
		i_uid |= le16_to_cpu(raw_inode->i_uid_high) << 16;
		i_gid |= le16_to_cpu(raw_inode->i_gid_high) << 16;
	पूर्ण
	i_uid_ग_लिखो(inode, i_uid);
	i_gid_ग_लिखो(inode, i_gid);
	set_nlink(inode, le16_to_cpu(raw_inode->i_links_count));
	inode->i_size = le32_to_cpu(raw_inode->i_size);
	inode->i_aसमय.tv_sec = (चिन्हित)le32_to_cpu(raw_inode->i_aसमय);
	inode->i_स_समय.tv_sec = (चिन्हित)le32_to_cpu(raw_inode->i_स_समय);
	inode->i_mसमय.tv_sec = (चिन्हित)le32_to_cpu(raw_inode->i_mसमय);
	inode->i_aसमय.tv_nsec = inode->i_mसमय.tv_nsec = inode->i_स_समय.tv_nsec = 0;
	ei->i_dसमय = le32_to_cpu(raw_inode->i_dसमय);
	/* We now have enough fields to check अगर the inode was active or not.
	 * This is needed because nfsd might try to access dead inodes
	 * the test is that same one that e2fsck uses
	 * NeilBrown 1999oct15
	 */
	अगर (inode->i_nlink == 0 && (inode->i_mode == 0 || ei->i_dसमय)) अणु
		/* this inode is deleted */
		ret = -ESTALE;
		जाओ bad_inode;
	पूर्ण
	inode->i_blocks = le32_to_cpu(raw_inode->i_blocks);
	ei->i_flags = le32_to_cpu(raw_inode->i_flags);
	ext2_set_inode_flags(inode);
	ei->i_faddr = le32_to_cpu(raw_inode->i_faddr);
	ei->i_frag_no = raw_inode->i_frag;
	ei->i_frag_size = raw_inode->i_fsize;
	ei->i_file_acl = le32_to_cpu(raw_inode->i_file_acl);
	ei->i_dir_acl = 0;

	अगर (ei->i_file_acl &&
	    !ext2_data_block_valid(EXT2_SB(sb), ei->i_file_acl, 1)) अणु
		ext2_error(sb, "ext2_iget", "bad extended attribute block %u",
			   ei->i_file_acl);
		ret = -EFSCORRUPTED;
		जाओ bad_inode;
	पूर्ण

	अगर (S_ISREG(inode->i_mode))
		inode->i_size |= ((__u64)le32_to_cpu(raw_inode->i_size_high)) << 32;
	अन्यथा
		ei->i_dir_acl = le32_to_cpu(raw_inode->i_dir_acl);
	अगर (i_size_पढ़ो(inode) < 0) अणु
		ret = -EFSCORRUPTED;
		जाओ bad_inode;
	पूर्ण
	ei->i_dसमय = 0;
	inode->i_generation = le32_to_cpu(raw_inode->i_generation);
	ei->i_state = 0;
	ei->i_block_group = (ino - 1) / EXT2_INODES_PER_GROUP(inode->i_sb);
	ei->i_dir_start_lookup = 0;

	/*
	 * NOTE! The in-memory inode i_data array is in little-endian order
	 * even on big-endian machines: we करो NOT byteswap the block numbers!
	 */
	क्रम (n = 0; n < EXT2_N_BLOCKS; n++)
		ei->i_data[n] = raw_inode->i_block[n];

	अगर (S_ISREG(inode->i_mode)) अणु
		ext2_set_file_ops(inode);
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &ext2_dir_inode_operations;
		inode->i_fop = &ext2_dir_operations;
		अगर (test_opt(inode->i_sb, NOBH))
			inode->i_mapping->a_ops = &ext2_nobh_aops;
		अन्यथा
			inode->i_mapping->a_ops = &ext2_aops;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		अगर (ext2_inode_is_fast_symlink(inode)) अणु
			inode->i_link = (अक्षर *)ei->i_data;
			inode->i_op = &ext2_fast_symlink_inode_operations;
			nd_terminate_link(ei->i_data, inode->i_size,
				माप(ei->i_data) - 1);
		पूर्ण अन्यथा अणु
			inode->i_op = &ext2_symlink_inode_operations;
			inode_nohighmem(inode);
			अगर (test_opt(inode->i_sb, NOBH))
				inode->i_mapping->a_ops = &ext2_nobh_aops;
			अन्यथा
				inode->i_mapping->a_ops = &ext2_aops;
		पूर्ण
	पूर्ण अन्यथा अणु
		inode->i_op = &ext2_special_inode_operations;
		अगर (raw_inode->i_block[0])
			init_special_inode(inode, inode->i_mode,
			   old_decode_dev(le32_to_cpu(raw_inode->i_block[0])));
		अन्यथा 
			init_special_inode(inode, inode->i_mode,
			   new_decode_dev(le32_to_cpu(raw_inode->i_block[1])));
	पूर्ण
	brअन्यथा (bh);
	unlock_new_inode(inode);
	वापस inode;
	
bad_inode:
	brअन्यथा(bh);
	iget_failed(inode);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक __ext2_ग_लिखो_inode(काष्ठा inode *inode, पूर्णांक करो_sync)
अणु
	काष्ठा ext2_inode_info *ei = EXT2_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	ino_t ino = inode->i_ino;
	uid_t uid = i_uid_पढ़ो(inode);
	gid_t gid = i_gid_पढ़ो(inode);
	काष्ठा buffer_head * bh;
	काष्ठा ext2_inode * raw_inode = ext2_get_inode(sb, ino, &bh);
	पूर्णांक n;
	पूर्णांक err = 0;

	अगर (IS_ERR(raw_inode))
 		वापस -EIO;

	/* For fields not not tracking in the in-memory inode,
	 * initialise them to zero क्रम new inodes. */
	अगर (ei->i_state & EXT2_STATE_NEW)
		स_रखो(raw_inode, 0, EXT2_SB(sb)->s_inode_size);

	raw_inode->i_mode = cpu_to_le16(inode->i_mode);
	अगर (!(test_opt(sb, NO_UID32))) अणु
		raw_inode->i_uid_low = cpu_to_le16(low_16_bits(uid));
		raw_inode->i_gid_low = cpu_to_le16(low_16_bits(gid));
/*
 * Fix up पूर्णांकeroperability with old kernels. Otherwise, old inodes get
 * re-used with the upper 16 bits of the uid/gid पूर्णांकact
 */
		अगर (!ei->i_dसमय) अणु
			raw_inode->i_uid_high = cpu_to_le16(high_16_bits(uid));
			raw_inode->i_gid_high = cpu_to_le16(high_16_bits(gid));
		पूर्ण अन्यथा अणु
			raw_inode->i_uid_high = 0;
			raw_inode->i_gid_high = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		raw_inode->i_uid_low = cpu_to_le16(fs_high2lowuid(uid));
		raw_inode->i_gid_low = cpu_to_le16(fs_high2lowgid(gid));
		raw_inode->i_uid_high = 0;
		raw_inode->i_gid_high = 0;
	पूर्ण
	raw_inode->i_links_count = cpu_to_le16(inode->i_nlink);
	raw_inode->i_size = cpu_to_le32(inode->i_size);
	raw_inode->i_aसमय = cpu_to_le32(inode->i_aसमय.tv_sec);
	raw_inode->i_स_समय = cpu_to_le32(inode->i_स_समय.tv_sec);
	raw_inode->i_mसमय = cpu_to_le32(inode->i_mसमय.tv_sec);

	raw_inode->i_blocks = cpu_to_le32(inode->i_blocks);
	raw_inode->i_dसमय = cpu_to_le32(ei->i_dसमय);
	raw_inode->i_flags = cpu_to_le32(ei->i_flags);
	raw_inode->i_faddr = cpu_to_le32(ei->i_faddr);
	raw_inode->i_frag = ei->i_frag_no;
	raw_inode->i_fsize = ei->i_frag_size;
	raw_inode->i_file_acl = cpu_to_le32(ei->i_file_acl);
	अगर (!S_ISREG(inode->i_mode))
		raw_inode->i_dir_acl = cpu_to_le32(ei->i_dir_acl);
	अन्यथा अणु
		raw_inode->i_size_high = cpu_to_le32(inode->i_size >> 32);
		अगर (inode->i_size > 0x7fffffffULL) अणु
			अगर (!EXT2_HAS_RO_COMPAT_FEATURE(sb,
					EXT2_FEATURE_RO_COMPAT_LARGE_खाता) ||
			    EXT2_SB(sb)->s_es->s_rev_level ==
					cpu_to_le32(EXT2_GOOD_OLD_REV)) अणु
			       /* If this is the first large file
				* created, add a flag to the superblock.
				*/
				spin_lock(&EXT2_SB(sb)->s_lock);
				ext2_update_dynamic_rev(sb);
				EXT2_SET_RO_COMPAT_FEATURE(sb,
					EXT2_FEATURE_RO_COMPAT_LARGE_खाता);
				spin_unlock(&EXT2_SB(sb)->s_lock);
				ext2_sync_super(sb, EXT2_SB(sb)->s_es, 1);
			पूर्ण
		पूर्ण
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
	पूर्ण अन्यथा क्रम (n = 0; n < EXT2_N_BLOCKS; n++)
		raw_inode->i_block[n] = ei->i_data[n];
	mark_buffer_dirty(bh);
	अगर (करो_sync) अणु
		sync_dirty_buffer(bh);
		अगर (buffer_req(bh) && !buffer_uptodate(bh)) अणु
			prपूर्णांकk ("IO error syncing ext2 inode [%s:%08lx]\n",
				sb->s_id, (अचिन्हित दीर्घ) ino);
			err = -EIO;
		पूर्ण
	पूर्ण
	ei->i_state &= ~EXT2_STATE_NEW;
	brअन्यथा (bh);
	वापस err;
पूर्ण

पूर्णांक ext2_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस __ext2_ग_लिखो_inode(inode, wbc->sync_mode == WB_SYNC_ALL);
पूर्ण

पूर्णांक ext2_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		 काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा ext2_inode_info *ei = EXT2_I(inode);
	अचिन्हित पूर्णांक flags;

	flags = ei->i_flags & EXT2_FL_USER_VISIBLE;
	अगर (flags & EXT2_APPEND_FL)
		stat->attributes |= STATX_ATTR_APPEND;
	अगर (flags & EXT2_COMPR_FL)
		stat->attributes |= STATX_ATTR_COMPRESSED;
	अगर (flags & EXT2_IMMUTABLE_FL)
		stat->attributes |= STATX_ATTR_IMMUTABLE;
	अगर (flags & EXT2_NODUMP_FL)
		stat->attributes |= STATX_ATTR_NODUMP;
	stat->attributes_mask |= (STATX_ATTR_APPEND |
			STATX_ATTR_COMPRESSED |
			STATX_ATTR_ENCRYPTED |
			STATX_ATTR_IMMUTABLE |
			STATX_ATTR_NODUMP);

	generic_fillattr(&init_user_ns, inode, stat);
	वापस 0;
पूर्ण

पूर्णांक ext2_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		 काष्ठा iattr *iattr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error;

	error = setattr_prepare(&init_user_ns, dentry, iattr);
	अगर (error)
		वापस error;

	अगर (is_quota_modअगरication(inode, iattr)) अणु
		error = dquot_initialize(inode);
		अगर (error)
			वापस error;
	पूर्ण
	अगर ((iattr->ia_valid & ATTR_UID && !uid_eq(iattr->ia_uid, inode->i_uid)) ||
	    (iattr->ia_valid & ATTR_GID && !gid_eq(iattr->ia_gid, inode->i_gid))) अणु
		error = dquot_transfer(inode, iattr);
		अगर (error)
			वापस error;
	पूर्ण
	अगर (iattr->ia_valid & ATTR_SIZE && iattr->ia_size != inode->i_size) अणु
		error = ext2_setsize(inode, iattr->ia_size);
		अगर (error)
			वापस error;
	पूर्ण
	setattr_copy(&init_user_ns, inode, iattr);
	अगर (iattr->ia_valid & ATTR_MODE)
		error = posix_acl_chmod(&init_user_ns, inode, inode->i_mode);
	mark_inode_dirty(inode);

	वापस error;
पूर्ण
