<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/indirect.c
 *
 *  from
 *
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
 *  Goal-directed block allocation by Stephen Tweedie
 *	(sct@redhat.com), 1993, 1998
 */

#समावेश "ext4_jbd2.h"
#समावेश "truncate.h"
#समावेश <linux/dax.h>
#समावेश <linux/uपन.स>

#समावेश <trace/events/ext4.h>

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

/**
 *	ext4_block_to_path - parse the block number पूर्णांकo array of offsets
 *	@inode: inode in question (we are only पूर्णांकerested in its superblock)
 *	@i_block: block number to be parsed
 *	@offsets: array to store the offsets in
 *	@boundary: set this non-zero अगर the referred-to block is likely to be
 *	       followed (on disk) by an indirect block.
 *
 *	To store the locations of file's data ext4 uses a data काष्ठाure common
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

अटल पूर्णांक ext4_block_to_path(काष्ठा inode *inode,
			      ext4_lblk_t i_block,
			      ext4_lblk_t offsets[4], पूर्णांक *boundary)
अणु
	पूर्णांक ptrs = EXT4_ADDR_PER_BLOCK(inode->i_sb);
	पूर्णांक ptrs_bits = EXT4_ADDR_PER_BLOCK_BITS(inode->i_sb);
	स्थिर दीर्घ direct_blocks = EXT4_Nसूची_BLOCKS,
		indirect_blocks = ptrs,
		द्विगुन_blocks = (1 << (ptrs_bits * 2));
	पूर्णांक n = 0;
	पूर्णांक final = 0;

	अगर (i_block < direct_blocks) अणु
		offsets[n++] = i_block;
		final = direct_blocks;
	पूर्ण अन्यथा अगर ((i_block -= direct_blocks) < indirect_blocks) अणु
		offsets[n++] = EXT4_IND_BLOCK;
		offsets[n++] = i_block;
		final = ptrs;
	पूर्ण अन्यथा अगर ((i_block -= indirect_blocks) < द्विगुन_blocks) अणु
		offsets[n++] = EXT4_DIND_BLOCK;
		offsets[n++] = i_block >> ptrs_bits;
		offsets[n++] = i_block & (ptrs - 1);
		final = ptrs;
	पूर्ण अन्यथा अगर (((i_block -= द्विगुन_blocks) >> (ptrs_bits * 2)) < ptrs) अणु
		offsets[n++] = EXT4_TIND_BLOCK;
		offsets[n++] = i_block >> (ptrs_bits * 2);
		offsets[n++] = (i_block >> ptrs_bits) & (ptrs - 1);
		offsets[n++] = i_block & (ptrs - 1);
		final = ptrs;
	पूर्ण अन्यथा अणु
		ext4_warning(inode->i_sb, "block %lu > max in inode %lu",
			     i_block + direct_blocks +
			     indirect_blocks + द्विगुन_blocks, inode->i_ino);
	पूर्ण
	अगर (boundary)
		*boundary = final - 1 - (i_block & (ptrs - 1));
	वापस n;
पूर्ण

/**
 *	ext4_get_branch - पढ़ो the chain of indirect blocks leading to data
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
 *	or when it पढ़ोs all @depth-1 indirect blocks successfully and finds
 *	the whole chain, all way to the data (वापसs %शून्य, *err == 0).
 *
 *      Need to be called with
 *      करोwn_पढ़ो(&EXT4_I(inode)->i_data_sem)
 */
अटल Indirect *ext4_get_branch(काष्ठा inode *inode, पूर्णांक depth,
				 ext4_lblk_t  *offsets,
				 Indirect chain[4], पूर्णांक *err)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	Indirect *p = chain;
	काष्ठा buffer_head *bh;
	पूर्णांक ret = -EIO;

	*err = 0;
	/* i_data is not going away, no lock needed */
	add_chain(chain, शून्य, EXT4_I(inode)->i_data + *offsets);
	अगर (!p->key)
		जाओ no_block;
	जबतक (--depth) अणु
		bh = sb_getblk(sb, le32_to_cpu(p->key));
		अगर (unlikely(!bh)) अणु
			ret = -ENOMEM;
			जाओ failure;
		पूर्ण

		अगर (!bh_uptodate_or_lock(bh)) अणु
			अगर (ext4_पढ़ो_bh(bh, 0, शून्य) < 0) अणु
				put_bh(bh);
				जाओ failure;
			पूर्ण
			/* validate block references */
			अगर (ext4_check_indirect_blockref(inode, bh)) अणु
				put_bh(bh);
				जाओ failure;
			पूर्ण
		पूर्ण

		add_chain(++p, bh, (__le32 *)bh->b_data + *++offsets);
		/* Reader: end */
		अगर (!p->key)
			जाओ no_block;
	पूर्ण
	वापस शून्य;

failure:
	*err = ret;
no_block:
	वापस p;
पूर्ण

/**
 *	ext4_find_near - find a place क्रम allocation with sufficient locality
 *	@inode: owner
 *	@ind: descriptor of indirect block.
 *
 *	This function वापसs the preferred place क्रम block allocation.
 *	It is used when heuristic क्रम sequential allocation fails.
 *	Rules are:
 *	  + अगर there is a block to the left of our position - allocate near it.
 *	  + अगर poपूर्णांकer will live in indirect block - allocate near that block.
 *	  + अगर poपूर्णांकer will live in inode - allocate in the same
 *	    cylinder group.
 *
 * In the latter हाल we colour the starting block by the callers PID to
 * prevent it from clashing with concurrent allocations क्रम a dअगरferent inode
 * in the same block group.   The PID is used here so that functionally related
 * files will be बंद-by on-disk.
 *
 *	Caller must make sure that @ind is valid and will stay that way.
 */
अटल ext4_fsblk_t ext4_find_near(काष्ठा inode *inode, Indirect *ind)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	__le32 *start = ind->bh ? (__le32 *) ind->bh->b_data : ei->i_data;
	__le32 *p;

	/* Try to find previous block */
	क्रम (p = ind->p - 1; p >= start; p--) अणु
		अगर (*p)
			वापस le32_to_cpu(*p);
	पूर्ण

	/* No such thing, so let's try location of indirect block */
	अगर (ind->bh)
		वापस ind->bh->b_blocknr;

	/*
	 * It is going to be referred to from the inode itself? OK, just put it
	 * पूर्णांकo the same cylinder group then.
	 */
	वापस ext4_inode_to_goal_block(inode);
पूर्ण

/**
 *	ext4_find_goal - find a preferred place क्रम allocation.
 *	@inode: owner
 *	@block:  block we want
 *	@partial: poपूर्णांकer to the last triple within a chain
 *
 *	Normally this function find the preferred place क्रम block allocation,
 *	वापसs it.
 *	Because this is only used क्रम non-extent files, we limit the block nr
 *	to 32 bits.
 */
अटल ext4_fsblk_t ext4_find_goal(काष्ठा inode *inode, ext4_lblk_t block,
				   Indirect *partial)
अणु
	ext4_fsblk_t goal;

	/*
	 * XXX need to get goal block from mballoc's data काष्ठाures
	 */

	goal = ext4_find_near(inode, partial);
	goal = goal & EXT4_MAX_BLOCK_खाता_PHYS;
	वापस goal;
पूर्ण

/**
 *	ext4_blks_to_allocate - Look up the block map and count the number
 *	of direct blocks need to be allocated क्रम the given branch.
 *
 *	@branch: chain of indirect blocks
 *	@k: number of blocks need क्रम indirect blocks
 *	@blks: number of data blocks to be mapped.
 *	@blocks_to_boundary:  the offset in the indirect block
 *
 *	वापस the total number of blocks to be allocate, including the
 *	direct and indirect blocks.
 */
अटल पूर्णांक ext4_blks_to_allocate(Indirect *branch, पूर्णांक k, अचिन्हित पूर्णांक blks,
				 पूर्णांक blocks_to_boundary)
अणु
	अचिन्हित पूर्णांक count = 0;

	/*
	 * Simple हाल, [t,d]Indirect block(s) has not allocated yet
	 * then it's clear blocks on that path have not allocated
	 */
	अगर (k > 0) अणु
		/* right now we करोn't handle cross boundary allocation */
		अगर (blks < blocks_to_boundary + 1)
			count += blks;
		अन्यथा
			count += blocks_to_boundary + 1;
		वापस count;
	पूर्ण

	count++;
	जबतक (count < blks && count <= blocks_to_boundary &&
		le32_to_cpu(*(branch[0].p + count)) == 0) अणु
		count++;
	पूर्ण
	वापस count;
पूर्ण

/**
 * ext4_alloc_branch() - allocate and set up a chain of blocks
 * @handle: handle क्रम this transaction
 * @ar: काष्ठाure describing the allocation request
 * @indirect_blks: number of allocated indirect blocks
 * @offsets: offsets (in the blocks) to store the poपूर्णांकers to next.
 * @branch: place to store the chain in.
 *
 *	This function allocates blocks, zeroes out all but the last one,
 *	links them पूर्णांकo chain and (अगर we are synchronous) ग_लिखोs them to disk.
 *	In other words, it prepares a branch that can be spliced onto the
 *	inode. It stores the inक्रमmation about that chain in the branch[], in
 *	the same क्रमmat as ext4_get_branch() would करो. We are calling it after
 *	we had पढ़ो the existing part of chain and partial poपूर्णांकs to the last
 *	triple of that (one with zero ->key). Upon the निकास we have the same
 *	picture as after the successful ext4_get_block(), except that in one
 *	place chain is disconnected - *branch->p is still zero (we did not
 *	set the last link), but branch->key contains the number that should
 *	be placed पूर्णांकo *branch->p to fill that gap.
 *
 *	If allocation fails we मुक्त all blocks we've allocated (and क्रमget
 *	their buffer_heads) and वापस the error value the from failed
 *	ext4_alloc_block() (normally -ENOSPC). Otherwise we set the chain
 *	as described above and वापस 0.
 */
अटल पूर्णांक ext4_alloc_branch(handle_t *handle,
			     काष्ठा ext4_allocation_request *ar,
			     पूर्णांक indirect_blks, ext4_lblk_t *offsets,
			     Indirect *branch)
अणु
	काष्ठा buffer_head *		bh;
	ext4_fsblk_t			b, new_blocks[4];
	__le32				*p;
	पूर्णांक				i, j, err, len = 1;

	क्रम (i = 0; i <= indirect_blks; i++) अणु
		अगर (i == indirect_blks) अणु
			new_blocks[i] = ext4_mb_new_blocks(handle, ar, &err);
		पूर्ण अन्यथा अणु
			ar->goal = new_blocks[i] = ext4_new_meta_blocks(handle,
					ar->inode, ar->goal,
					ar->flags & EXT4_MB_DELALLOC_RESERVED,
					शून्य, &err);
			/* Simplअगरy error cleanup... */
			branch[i+1].bh = शून्य;
		पूर्ण
		अगर (err) अणु
			i--;
			जाओ failed;
		पूर्ण
		branch[i].key = cpu_to_le32(new_blocks[i]);
		अगर (i == 0)
			जारी;

		bh = branch[i].bh = sb_getblk(ar->inode->i_sb, new_blocks[i-1]);
		अगर (unlikely(!bh)) अणु
			err = -ENOMEM;
			जाओ failed;
		पूर्ण
		lock_buffer(bh);
		BUFFER_TRACE(bh, "call get_create_access");
		err = ext4_journal_get_create_access(handle, bh);
		अगर (err) अणु
			unlock_buffer(bh);
			जाओ failed;
		पूर्ण

		स_रखो(bh->b_data, 0, bh->b_size);
		p = branch[i].p = (__le32 *) bh->b_data + offsets[i];
		b = new_blocks[i];

		अगर (i == indirect_blks)
			len = ar->len;
		क्रम (j = 0; j < len; j++)
			*p++ = cpu_to_le32(b++);

		BUFFER_TRACE(bh, "marking uptodate");
		set_buffer_uptodate(bh);
		unlock_buffer(bh);

		BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
		err = ext4_handle_dirty_metadata(handle, ar->inode, bh);
		अगर (err)
			जाओ failed;
	पूर्ण
	वापस 0;
failed:
	अगर (i == indirect_blks) अणु
		/* Free data blocks */
		ext4_मुक्त_blocks(handle, ar->inode, शून्य, new_blocks[i],
				 ar->len, 0);
		i--;
	पूर्ण
	क्रम (; i >= 0; i--) अणु
		/*
		 * We want to ext4_क्रमget() only freshly allocated indirect
		 * blocks. Buffer क्रम new_blocks[i] is at branch[i+1].bh
		 * (buffer at branch[0].bh is indirect block / inode alपढ़ोy
		 * existing beक्रमe ext4_alloc_branch() was called). Also
		 * because blocks are freshly allocated, we करोn't need to
		 * revoke them which is why we करोn't set
		 * EXT4_FREE_BLOCKS_METADATA.
		 */
		ext4_मुक्त_blocks(handle, ar->inode, branch[i+1].bh,
				 new_blocks[i], 1,
				 branch[i+1].bh ? EXT4_FREE_BLOCKS_FORGET : 0);
	पूर्ण
	वापस err;
पूर्ण

/**
 * ext4_splice_branch() - splice the allocated branch onto inode.
 * @handle: handle क्रम this transaction
 * @ar: काष्ठाure describing the allocation request
 * @where: location of missing link
 * @num:   number of indirect blocks we are adding
 *
 * This function fills the missing link and करोes all housekeeping needed in
 * inode (->i_blocks, etc.). In हाल of success we end up with the full
 * chain to new block and वापस 0.
 */
अटल पूर्णांक ext4_splice_branch(handle_t *handle,
			      काष्ठा ext4_allocation_request *ar,
			      Indirect *where, पूर्णांक num)
अणु
	पूर्णांक i;
	पूर्णांक err = 0;
	ext4_fsblk_t current_block;

	/*
	 * If we're splicing पूर्णांकo a [td]indirect block (as opposed to the
	 * inode) then we need to get ग_लिखो access to the [td]indirect block
	 * beक्रमe the splice.
	 */
	अगर (where->bh) अणु
		BUFFER_TRACE(where->bh, "get_write_access");
		err = ext4_journal_get_ग_लिखो_access(handle, where->bh);
		अगर (err)
			जाओ err_out;
	पूर्ण
	/* That's it */

	*where->p = where->key;

	/*
	 * Update the host buffer_head or inode to poपूर्णांक to more just allocated
	 * direct blocks blocks
	 */
	अगर (num == 0 && ar->len > 1) अणु
		current_block = le32_to_cpu(where->key) + 1;
		क्रम (i = 1; i < ar->len; i++)
			*(where->p + i) = cpu_to_le32(current_block++);
	पूर्ण

	/* We are करोne with atomic stuff, now करो the rest of housekeeping */
	/* had we spliced it onto indirect block? */
	अगर (where->bh) अणु
		/*
		 * If we spliced it onto an indirect block, we haven't
		 * altered the inode.  Note however that अगर it is being spliced
		 * onto an indirect block at the very end of the file (the
		 * file is growing) then we *will* alter the inode to reflect
		 * the new i_size.  But that is not करोne here - it is करोne in
		 * generic_commit_ग_लिखो->__mark_inode_dirty->ext4_dirty_inode.
		 */
		jbd_debug(5, "splicing indirect only\n");
		BUFFER_TRACE(where->bh, "call ext4_handle_dirty_metadata");
		err = ext4_handle_dirty_metadata(handle, ar->inode, where->bh);
		अगर (err)
			जाओ err_out;
	पूर्ण अन्यथा अणु
		/*
		 * OK, we spliced it पूर्णांकo the inode itself on a direct block.
		 */
		err = ext4_mark_inode_dirty(handle, ar->inode);
		अगर (unlikely(err))
			जाओ err_out;
		jbd_debug(5, "splicing direct\n");
	पूर्ण
	वापस err;

err_out:
	क्रम (i = 1; i <= num; i++) अणु
		/*
		 * branch[i].bh is newly allocated, so there is no
		 * need to revoke the block, which is why we करोn't
		 * need to set EXT4_FREE_BLOCKS_METADATA.
		 */
		ext4_मुक्त_blocks(handle, ar->inode, where[i].bh, 0, 1,
				 EXT4_FREE_BLOCKS_FORGET);
	पूर्ण
	ext4_मुक्त_blocks(handle, ar->inode, शून्य, le32_to_cpu(where[num].key),
			 ar->len, 0);

	वापस err;
पूर्ण

/*
 * The ext4_ind_map_blocks() function handles non-extents inodes
 * (i.e., using the traditional indirect/द्विगुन-indirect i_blocks
 * scheme) क्रम ext4_map_blocks().
 *
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
 *
 * The ext4_ind_get_blocks() function should be called with
 * करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem) अगर allocating fileप्रणाली
 * blocks (i.e., flags has EXT4_GET_BLOCKS_CREATE set) or
 * करोwn_पढ़ो(&EXT4_I(inode)->i_data_sem) अगर not allocating file प्रणाली
 * blocks.
 */
पूर्णांक ext4_ind_map_blocks(handle_t *handle, काष्ठा inode *inode,
			काष्ठा ext4_map_blocks *map,
			पूर्णांक flags)
अणु
	काष्ठा ext4_allocation_request ar;
	पूर्णांक err = -EIO;
	ext4_lblk_t offsets[4];
	Indirect chain[4];
	Indirect *partial;
	पूर्णांक indirect_blks;
	पूर्णांक blocks_to_boundary = 0;
	पूर्णांक depth;
	पूर्णांक count = 0;
	ext4_fsblk_t first_block = 0;

	trace_ext4_ind_map_blocks_enter(inode, map->m_lblk, map->m_len, flags);
	ASSERT(!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)));
	ASSERT(handle != शून्य || (flags & EXT4_GET_BLOCKS_CREATE) == 0);
	depth = ext4_block_to_path(inode, map->m_lblk, offsets,
				   &blocks_to_boundary);

	अगर (depth == 0)
		जाओ out;

	partial = ext4_get_branch(inode, depth, offsets, chain, &err);

	/* Simplest हाल - block found, no allocation needed */
	अगर (!partial) अणु
		first_block = le32_to_cpu(chain[depth - 1].key);
		count++;
		/*map more blocks*/
		जबतक (count < map->m_len && count <= blocks_to_boundary) अणु
			ext4_fsblk_t blk;

			blk = le32_to_cpu(*(chain[depth-1].p + count));

			अगर (blk == first_block + count)
				count++;
			अन्यथा
				अवरोध;
		पूर्ण
		जाओ got_it;
	पूर्ण

	/* Next simple हाल - plain lookup failed */
	अगर ((flags & EXT4_GET_BLOCKS_CREATE) == 0) अणु
		अचिन्हित epb = inode->i_sb->s_blocksize / माप(u32);
		पूर्णांक i;

		/*
		 * Count number blocks in a subtree under 'partial'. At each
		 * level we count number of complete empty subtrees beyond
		 * current offset and then descend पूर्णांकo the subtree only
		 * partially beyond current offset.
		 */
		count = 0;
		क्रम (i = partial - chain + 1; i < depth; i++)
			count = count * epb + (epb - offsets[i] - 1);
		count++;
		/* Fill in size of a hole we found */
		map->m_pblk = 0;
		map->m_len = min_t(अचिन्हित पूर्णांक, map->m_len, count);
		जाओ cleanup;
	पूर्ण

	/* Failed पढ़ो of indirect block */
	अगर (err == -EIO)
		जाओ cleanup;

	/*
	 * Okay, we need to करो block allocation.
	*/
	अगर (ext4_has_feature_bigalloc(inode->i_sb)) अणु
		EXT4_ERROR_INODE(inode, "Can't allocate blocks for "
				 "non-extent mapped inodes with bigalloc");
		err = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	/* Set up क्रम the direct block allocation */
	स_रखो(&ar, 0, माप(ar));
	ar.inode = inode;
	ar.logical = map->m_lblk;
	अगर (S_ISREG(inode->i_mode))
		ar.flags = EXT4_MB_HINT_DATA;
	अगर (flags & EXT4_GET_BLOCKS_DELALLOC_RESERVE)
		ar.flags |= EXT4_MB_DELALLOC_RESERVED;
	अगर (flags & EXT4_GET_BLOCKS_METADATA_NOFAIL)
		ar.flags |= EXT4_MB_USE_RESERVED;

	ar.goal = ext4_find_goal(inode, map->m_lblk, partial);

	/* the number of blocks need to allocate क्रम [d,t]indirect blocks */
	indirect_blks = (chain + depth) - partial - 1;

	/*
	 * Next look up the indirect map to count the totoal number of
	 * direct blocks to allocate क्रम this branch.
	 */
	ar.len = ext4_blks_to_allocate(partial, indirect_blks,
				       map->m_len, blocks_to_boundary);

	/*
	 * Block out ext4_truncate जबतक we alter the tree
	 */
	err = ext4_alloc_branch(handle, &ar, indirect_blks,
				offsets + (partial - chain), partial);

	/*
	 * The ext4_splice_branch call will मुक्त and क्रमget any buffers
	 * on the new chain अगर there is a failure, but that risks using
	 * up transaction credits, especially क्रम biपंचांगaps where the
	 * credits cannot be वापसed.  Can we handle this somehow?  We
	 * may need to वापस -EAGAIN upwards in the worst हाल.  --sct
	 */
	अगर (!err)
		err = ext4_splice_branch(handle, &ar, partial, indirect_blks);
	अगर (err)
		जाओ cleanup;

	map->m_flags |= EXT4_MAP_NEW;

	ext4_update_inode_fsync_trans(handle, inode, 1);
	count = ar.len;
got_it:
	map->m_flags |= EXT4_MAP_MAPPED;
	map->m_pblk = le32_to_cpu(chain[depth-1].key);
	map->m_len = count;
	अगर (count > blocks_to_boundary)
		map->m_flags |= EXT4_MAP_BOUNDARY;
	err = count;
	/* Clean up and निकास */
	partial = chain + depth - 1;	/* the whole chain */
cleanup:
	जबतक (partial > chain) अणु
		BUFFER_TRACE(partial->bh, "call brelse");
		brअन्यथा(partial->bh);
		partial--;
	पूर्ण
out:
	trace_ext4_ind_map_blocks_निकास(inode, flags, map, err);
	वापस err;
पूर्ण

/*
 * Calculate number of indirect blocks touched by mapping @nrblocks logically
 * contiguous blocks
 */
पूर्णांक ext4_ind_trans_blocks(काष्ठा inode *inode, पूर्णांक nrblocks)
अणु
	/*
	 * With N contiguous data blocks, we need at most
	 * N/EXT4_ADDR_PER_BLOCK(inode->i_sb) + 1 indirect blocks,
	 * 2 dindirect blocks, and 1 tindirect block
	 */
	वापस DIV_ROUND_UP(nrblocks, EXT4_ADDR_PER_BLOCK(inode->i_sb)) + 4;
पूर्ण

अटल पूर्णांक ext4_ind_trunc_restart_fn(handle_t *handle, काष्ठा inode *inode,
				     काष्ठा buffer_head *bh, पूर्णांक *dropped)
अणु
	पूर्णांक err;

	अगर (bh) अणु
		BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
		err = ext4_handle_dirty_metadata(handle, inode, bh);
		अगर (unlikely(err))
			वापस err;
	पूर्ण
	err = ext4_mark_inode_dirty(handle, inode);
	अगर (unlikely(err))
		वापस err;
	/*
	 * Drop i_data_sem to aव्योम deadlock with ext4_map_blocks.  At this
	 * moment, get_block can be called only क्रम blocks inside i_size since
	 * page cache has been alपढ़ोy dropped and ग_लिखोs are blocked by
	 * i_mutex. So we can safely drop the i_data_sem here.
	 */
	BUG_ON(EXT4_JOURNAL(inode) == शून्य);
	ext4_discard_pपुनः_स्मृतिations(inode, 0);
	up_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	*dropped = 1;
	वापस 0;
पूर्ण

/*
 * Truncate transactions can be complex and असलolutely huge.  So we need to
 * be able to restart the transaction at a convenient checkpoपूर्णांक to make
 * sure we करोn't overflow the journal.
 *
 * Try to extend this transaction क्रम the purposes of truncation.  If
 * extend fails, we restart transaction.
 */
अटल पूर्णांक ext4_ind_truncate_ensure_credits(handle_t *handle,
					    काष्ठा inode *inode,
					    काष्ठा buffer_head *bh,
					    पूर्णांक revoke_creds)
अणु
	पूर्णांक ret;
	पूर्णांक dropped = 0;

	ret = ext4_journal_ensure_credits_fn(handle, EXT4_RESERVE_TRANS_BLOCKS,
			ext4_blocks_क्रम_truncate(inode), revoke_creds,
			ext4_ind_trunc_restart_fn(handle, inode, bh, &dropped));
	अगर (dropped)
		करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
	अगर (ret <= 0)
		वापस ret;
	अगर (bh) अणु
		BUFFER_TRACE(bh, "retaking write access");
		ret = ext4_journal_get_ग_लिखो_access(handle, bh);
		अगर (unlikely(ret))
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

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
 *	ext4_find_shared - find the indirect blocks क्रम partial truncation.
 *	@inode:	  inode in question
 *	@depth:	  depth of the affected branch
 *	@offsets: offsets of poपूर्णांकers in that branch (see ext4_block_to_path)
 *	@chain:	  place to store the poपूर्णांकers to partial indirect blocks
 *	@top:	  place to the (detached) top of branch
 *
 *	This is a helper function used by ext4_truncate().
 *
 *	When we करो truncate() we may have to clean the ends of several
 *	indirect blocks but leave the blocks themselves alive. Block is
 *	partially truncated अगर some data below the new i_size is referred
 *	from it (and it is on the path to the first completely truncated
 *	data block, indeed).  We have to मुक्त the top of that path aदीर्घ
 *	with everything to the right of the path. Since no allocation
 *	past the truncation poपूर्णांक is possible until ext4_truncate()
 *	finishes, we may safely करो the latter, but top of branch may
 *	require special attention - pageout below the truncation poपूर्णांक
 *	might try to populate it.
 *
 *	We atomically detach the top of branch from the tree, store the
 *	block number of its root in *@top, poपूर्णांकers to buffer_heads of
 *	partially truncated blocks - in @chain[].bh and poपूर्णांकers to
 *	their last elements that should not be हटाओd - in
 *	@chain[].p. Return value is the poपूर्णांकer to last filled element
 *	of @chain.
 *
 *	The work left to caller to करो the actual मुक्तing of subtrees:
 *		a) मुक्त the subtree starting from *@top
 *		b) मुक्त the subtrees whose roots are stored in
 *			(@chain[i].p+1 .. end of @chain[i].bh->b_data)
 *		c) मुक्त the subtrees growing from the inode past the @chain[0].
 *			(no partially truncated stuff there).  */

अटल Indirect *ext4_find_shared(काष्ठा inode *inode, पूर्णांक depth,
				  ext4_lblk_t offsets[4], Indirect chain[4],
				  __le32 *top)
अणु
	Indirect *partial, *p;
	पूर्णांक k, err;

	*top = 0;
	/* Make k index the deepest non-null offset + 1 */
	क्रम (k = depth; k > 1 && !offsets[k-1]; k--)
		;
	partial = ext4_get_branch(inode, k, offsets, chain, &err);
	/* Writer: poपूर्णांकers */
	अगर (!partial)
		partial = chain + k-1;
	/*
	 * If the branch acquired continuation since we've looked at it -
	 * fine, it should all survive and (new) top करोesn't beदीर्घ to us.
	 */
	अगर (!partial->key && *partial->p)
		/* Writer: end */
		जाओ no_top;
	क्रम (p = partial; (p > chain) && all_zeroes((__le32 *) p->bh->b_data, p->p); p--)
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
		/* Nope, करोn't करो this in ext4.  Must leave the tree पूर्णांकact */
#अगर 0
		*p->p = 0;
#पूर्ण_अगर
	पूर्ण
	/* Writer: end */

	जबतक (partial > p) अणु
		brअन्यथा(partial->bh);
		partial--;
	पूर्ण
no_top:
	वापस partial;
पूर्ण

/*
 * Zero a number of block poपूर्णांकers in either an inode or an indirect block.
 * If we restart the transaction we must again get ग_लिखो access to the
 * indirect block क्रम further modअगरication.
 *
 * We release `count' blocks on disk, but (last - first) may be greater
 * than `count' because there can be holes in there.
 *
 * Return 0 on success, 1 on invalid block range
 * and < 0 on fatal error.
 */
अटल पूर्णांक ext4_clear_blocks(handle_t *handle, काष्ठा inode *inode,
			     काष्ठा buffer_head *bh,
			     ext4_fsblk_t block_to_मुक्त,
			     अचिन्हित दीर्घ count, __le32 *first,
			     __le32 *last)
अणु
	__le32 *p;
	पूर्णांक	flags = EXT4_FREE_BLOCKS_VALIDATED;
	पूर्णांक	err;

	अगर (S_ISसूची(inode->i_mode) || S_ISLNK(inode->i_mode) ||
	    ext4_test_inode_flag(inode, EXT4_INODE_EA_INODE))
		flags |= EXT4_FREE_BLOCKS_FORGET | EXT4_FREE_BLOCKS_METADATA;
	अन्यथा अगर (ext4_should_journal_data(inode))
		flags |= EXT4_FREE_BLOCKS_FORGET;

	अगर (!ext4_inode_block_valid(inode, block_to_मुक्त, count)) अणु
		EXT4_ERROR_INODE(inode, "attempt to clear invalid "
				 "blocks %llu len %lu",
				 (अचिन्हित दीर्घ दीर्घ) block_to_मुक्त, count);
		वापस 1;
	पूर्ण

	err = ext4_ind_truncate_ensure_credits(handle, inode, bh,
				ext4_मुक्त_data_revoke_credits(inode, count));
	अगर (err < 0)
		जाओ out_err;

	क्रम (p = first; p < last; p++)
		*p = 0;

	ext4_मुक्त_blocks(handle, inode, शून्य, block_to_मुक्त, count, flags);
	वापस 0;
out_err:
	ext4_std_error(inode->i_sb, err);
	वापस err;
पूर्ण

/**
 * ext4_मुक्त_data - मुक्त a list of data blocks
 * @handle:	handle क्रम this transaction
 * @inode:	inode we are dealing with
 * @this_bh:	indirect buffer_head which contains *@first and *@last
 * @first:	array of block numbers
 * @last:	poपूर्णांकs immediately past the end of array
 *
 * We are मुक्तing all blocks referred from that array (numbers are stored as
 * little-endian 32-bit) and updating @inode->i_blocks appropriately.
 *
 * We accumulate contiguous runs of blocks to मुक्त.  Conveniently, अगर these
 * blocks are contiguous then releasing them at one समय will only affect one
 * or two biपंचांगap blocks (+ group descriptor(s) and superblock) and we won't
 * actually use a lot of journal space.
 *
 * @this_bh will be %शून्य अगर @first and @last poपूर्णांक पूर्णांकo the inode's direct
 * block poपूर्णांकers.
 */
अटल व्योम ext4_मुक्त_data(handle_t *handle, काष्ठा inode *inode,
			   काष्ठा buffer_head *this_bh,
			   __le32 *first, __le32 *last)
अणु
	ext4_fsblk_t block_to_मुक्त = 0;    /* Starting block # of a run */
	अचिन्हित दीर्घ count = 0;	    /* Number of blocks in the run */
	__le32 *block_to_मुक्त_p = शून्य;	    /* Poपूर्णांकer पूर्णांकo inode/ind
					       corresponding to
					       block_to_मुक्त */
	ext4_fsblk_t nr;		    /* Current block # */
	__le32 *p;			    /* Poपूर्णांकer पूर्णांकo inode/ind
					       क्रम current block */
	पूर्णांक err = 0;

	अगर (this_bh) अणु				/* For indirect block */
		BUFFER_TRACE(this_bh, "get_write_access");
		err = ext4_journal_get_ग_लिखो_access(handle, this_bh);
		/* Important: अगर we can't update the indirect poपूर्णांकers
		 * to the blocks, we can't मुक्त them. */
		अगर (err)
			वापस;
	पूर्ण

	क्रम (p = first; p < last; p++) अणु
		nr = le32_to_cpu(*p);
		अगर (nr) अणु
			/* accumulate blocks to मुक्त अगर they're contiguous */
			अगर (count == 0) अणु
				block_to_मुक्त = nr;
				block_to_मुक्त_p = p;
				count = 1;
			पूर्ण अन्यथा अगर (nr == block_to_मुक्त + count) अणु
				count++;
			पूर्ण अन्यथा अणु
				err = ext4_clear_blocks(handle, inode, this_bh,
						        block_to_मुक्त, count,
						        block_to_मुक्त_p, p);
				अगर (err)
					अवरोध;
				block_to_मुक्त = nr;
				block_to_मुक्त_p = p;
				count = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!err && count > 0)
		err = ext4_clear_blocks(handle, inode, this_bh, block_to_मुक्त,
					count, block_to_मुक्त_p, p);
	अगर (err < 0)
		/* fatal error */
		वापस;

	अगर (this_bh) अणु
		BUFFER_TRACE(this_bh, "call ext4_handle_dirty_metadata");

		/*
		 * The buffer head should have an attached journal head at this
		 * poपूर्णांक. However, अगर the data is corrupted and an indirect
		 * block poपूर्णांकed to itself, it would have been detached when
		 * the block was cleared. Check क्रम this instead of OOPSing.
		 */
		अगर ((EXT4_JOURNAL(inode) == शून्य) || bh2jh(this_bh))
			ext4_handle_dirty_metadata(handle, inode, this_bh);
		अन्यथा
			EXT4_ERROR_INODE(inode,
					 "circular indirect block detected at "
					 "block %llu",
				(अचिन्हित दीर्घ दीर्घ) this_bh->b_blocknr);
	पूर्ण
पूर्ण

/**
 *	ext4_मुक्त_branches - मुक्त an array of branches
 *	@handle: JBD handle क्रम this transaction
 *	@inode:	inode we are dealing with
 *	@parent_bh: the buffer_head which contains *@first and *@last
 *	@first:	array of block numbers
 *	@last:	poपूर्णांकer immediately past the end of array
 *	@depth:	depth of the branches to मुक्त
 *
 *	We are मुक्तing all blocks referred from these branches (numbers are
 *	stored as little-endian 32-bit) and updating @inode->i_blocks
 *	appropriately.
 */
अटल व्योम ext4_मुक्त_branches(handle_t *handle, काष्ठा inode *inode,
			       काष्ठा buffer_head *parent_bh,
			       __le32 *first, __le32 *last, पूर्णांक depth)
अणु
	ext4_fsblk_t nr;
	__le32 *p;

	अगर (ext4_handle_is_पातed(handle))
		वापस;

	अगर (depth--) अणु
		काष्ठा buffer_head *bh;
		पूर्णांक addr_per_block = EXT4_ADDR_PER_BLOCK(inode->i_sb);
		p = last;
		जबतक (--p >= first) अणु
			nr = le32_to_cpu(*p);
			अगर (!nr)
				जारी;		/* A hole */

			अगर (!ext4_inode_block_valid(inode, nr, 1)) अणु
				EXT4_ERROR_INODE(inode,
						 "invalid indirect mapped "
						 "block %lu (level %d)",
						 (अचिन्हित दीर्घ) nr, depth);
				अवरोध;
			पूर्ण

			/* Go पढ़ो the buffer क्रम the next level करोwn */
			bh = ext4_sb_bपढ़ो(inode->i_sb, nr, 0);

			/*
			 * A पढ़ो failure? Report error and clear slot
			 * (should be rare).
			 */
			अगर (IS_ERR(bh)) अणु
				ext4_error_inode_block(inode, nr, -PTR_ERR(bh),
						       "Read failure");
				जारी;
			पूर्ण

			/* This zaps the entire block.  Bottom up. */
			BUFFER_TRACE(bh, "free child branches");
			ext4_मुक्त_branches(handle, inode, bh,
					(__le32 *) bh->b_data,
					(__le32 *) bh->b_data + addr_per_block,
					depth);
			brअन्यथा(bh);

			/*
			 * Everything below this poपूर्णांकer has been
			 * released.  Now let this top-of-subtree go.
			 *
			 * We want the मुक्तing of this indirect block to be
			 * atomic in the journal with the updating of the
			 * biपंचांगap block which owns it.  So make some room in
			 * the journal.
			 *
			 * We zero the parent poपूर्णांकer *after* मुक्तing its
			 * poपूर्णांकee in the biपंचांगaps, so अगर extend_transaction()
			 * क्रम some reason fails to put the biपंचांगap changes and
			 * the release पूर्णांकo the same transaction, recovery
			 * will merely complain about releasing a मुक्त block,
			 * rather than leaking blocks.
			 */
			अगर (ext4_handle_is_पातed(handle))
				वापस;
			अगर (ext4_ind_truncate_ensure_credits(handle, inode,
					शून्य,
					ext4_मुक्त_metadata_revoke_credits(
							inode->i_sb, 1)) < 0)
				वापस;

			/*
			 * The क्रमget flag here is critical because अगर
			 * we are journaling (and not करोing data
			 * journaling), we have to make sure a revoke
			 * record is written to prevent the journal
			 * replay from overwriting the (क्रमmer)
			 * indirect block अगर it माला_लो पुनः_स्मृतिated as a
			 * data block.  This must happen in the same
			 * transaction where the data blocks are
			 * actually मुक्तd.
			 */
			ext4_मुक्त_blocks(handle, inode, शून्य, nr, 1,
					 EXT4_FREE_BLOCKS_METADATA|
					 EXT4_FREE_BLOCKS_FORGET);

			अगर (parent_bh) अणु
				/*
				 * The block which we have just मुक्तd is
				 * poपूर्णांकed to by an indirect block: journal it
				 */
				BUFFER_TRACE(parent_bh, "get_write_access");
				अगर (!ext4_journal_get_ग_लिखो_access(handle,
								   parent_bh))अणु
					*p = 0;
					BUFFER_TRACE(parent_bh,
					"call ext4_handle_dirty_metadata");
					ext4_handle_dirty_metadata(handle,
								   inode,
								   parent_bh);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We have reached the bottom of the tree. */
		BUFFER_TRACE(parent_bh, "free data blocks");
		ext4_मुक्त_data(handle, inode, parent_bh, first, last);
	पूर्ण
पूर्ण

व्योम ext4_ind_truncate(handle_t *handle, काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	__le32 *i_data = ei->i_data;
	पूर्णांक addr_per_block = EXT4_ADDR_PER_BLOCK(inode->i_sb);
	ext4_lblk_t offsets[4];
	Indirect chain[4];
	Indirect *partial;
	__le32 nr = 0;
	पूर्णांक n = 0;
	ext4_lblk_t last_block, max_block;
	अचिन्हित blocksize = inode->i_sb->s_blocksize;

	last_block = (inode->i_size + blocksize-1)
					>> EXT4_BLOCK_SIZE_BITS(inode->i_sb);
	max_block = (EXT4_SB(inode->i_sb)->s_biपंचांगap_maxbytes + blocksize-1)
					>> EXT4_BLOCK_SIZE_BITS(inode->i_sb);

	अगर (last_block != max_block) अणु
		n = ext4_block_to_path(inode, last_block, offsets, शून्य);
		अगर (n == 0)
			वापस;
	पूर्ण

	ext4_es_हटाओ_extent(inode, last_block, EXT_MAX_BLOCKS - last_block);

	/*
	 * The orphan list entry will now protect us from any crash which
	 * occurs beक्रमe the truncate completes, so it is now safe to propagate
	 * the new, लघुer inode size (held क्रम now in i_size) पूर्णांकo the
	 * on-disk inode. We करो this via i_disksize, which is the value which
	 * ext4 *really* ग_लिखोs onto the disk inode.
	 */
	ei->i_disksize = inode->i_size;

	अगर (last_block == max_block) अणु
		/*
		 * It is unnecessary to मुक्त any data blocks अगर last_block is
		 * equal to the indirect block limit.
		 */
		वापस;
	पूर्ण अन्यथा अगर (n == 1) अणु		/* direct blocks */
		ext4_मुक्त_data(handle, inode, शून्य, i_data+offsets[0],
			       i_data + EXT4_Nसूची_BLOCKS);
		जाओ करो_indirects;
	पूर्ण

	partial = ext4_find_shared(inode, n, offsets, chain, &nr);
	/* Kill the top of shared branch (not detached) */
	अगर (nr) अणु
		अगर (partial == chain) अणु
			/* Shared branch grows from the inode */
			ext4_मुक्त_branches(handle, inode, शून्य,
					   &nr, &nr+1, (chain+n-1) - partial);
			*partial->p = 0;
			/*
			 * We mark the inode dirty prior to restart,
			 * and prior to stop.  No need क्रम it here.
			 */
		पूर्ण अन्यथा अणु
			/* Shared branch grows from an indirect block */
			BUFFER_TRACE(partial->bh, "get_write_access");
			ext4_मुक्त_branches(handle, inode, partial->bh,
					partial->p,
					partial->p+1, (chain+n-1) - partial);
		पूर्ण
	पूर्ण
	/* Clear the ends of indirect blocks on the shared branch */
	जबतक (partial > chain) अणु
		ext4_मुक्त_branches(handle, inode, partial->bh, partial->p + 1,
				   (__le32*)partial->bh->b_data+addr_per_block,
				   (chain+n-1) - partial);
		BUFFER_TRACE(partial->bh, "call brelse");
		brअन्यथा(partial->bh);
		partial--;
	पूर्ण
करो_indirects:
	/* Kill the reमुख्यing (whole) subtrees */
	चयन (offsets[0]) अणु
	शेष:
		nr = i_data[EXT4_IND_BLOCK];
		अगर (nr) अणु
			ext4_मुक्त_branches(handle, inode, शून्य, &nr, &nr+1, 1);
			i_data[EXT4_IND_BLOCK] = 0;
		पूर्ण
		fallthrough;
	हाल EXT4_IND_BLOCK:
		nr = i_data[EXT4_DIND_BLOCK];
		अगर (nr) अणु
			ext4_मुक्त_branches(handle, inode, शून्य, &nr, &nr+1, 2);
			i_data[EXT4_DIND_BLOCK] = 0;
		पूर्ण
		fallthrough;
	हाल EXT4_DIND_BLOCK:
		nr = i_data[EXT4_TIND_BLOCK];
		अगर (nr) अणु
			ext4_मुक्त_branches(handle, inode, शून्य, &nr, &nr+1, 3);
			i_data[EXT4_TIND_BLOCK] = 0;
		पूर्ण
		fallthrough;
	हाल EXT4_TIND_BLOCK:
		;
	पूर्ण
पूर्ण

/**
 *	ext4_ind_हटाओ_space - हटाओ space from the range
 *	@handle: JBD handle क्रम this transaction
 *	@inode:	inode we are dealing with
 *	@start:	First block to हटाओ
 *	@end:	One block after the last block to हटाओ (exclusive)
 *
 *	Free the blocks in the defined range (end is exclusive endpoपूर्णांक of
 *	range). This is used by ext4_punch_hole().
 */
पूर्णांक ext4_ind_हटाओ_space(handle_t *handle, काष्ठा inode *inode,
			  ext4_lblk_t start, ext4_lblk_t end)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	__le32 *i_data = ei->i_data;
	पूर्णांक addr_per_block = EXT4_ADDR_PER_BLOCK(inode->i_sb);
	ext4_lblk_t offsets[4], offsets2[4];
	Indirect chain[4], chain2[4];
	Indirect *partial, *partial2;
	Indirect *p = शून्य, *p2 = शून्य;
	ext4_lblk_t max_block;
	__le32 nr = 0, nr2 = 0;
	पूर्णांक n = 0, n2 = 0;
	अचिन्हित blocksize = inode->i_sb->s_blocksize;

	max_block = (EXT4_SB(inode->i_sb)->s_biपंचांगap_maxbytes + blocksize-1)
					>> EXT4_BLOCK_SIZE_BITS(inode->i_sb);
	अगर (end >= max_block)
		end = max_block;
	अगर ((start >= end) || (start > max_block))
		वापस 0;

	n = ext4_block_to_path(inode, start, offsets, शून्य);
	n2 = ext4_block_to_path(inode, end, offsets2, शून्य);

	BUG_ON(n > n2);

	अगर ((n == 1) && (n == n2)) अणु
		/* We're punching only within direct block range */
		ext4_मुक्त_data(handle, inode, शून्य, i_data + offsets[0],
			       i_data + offsets2[0]);
		वापस 0;
	पूर्ण अन्यथा अगर (n2 > n) अणु
		/*
		 * Start and end are on a dअगरferent levels so we're going to
		 * मुक्त partial block at start, and partial block at end of
		 * the range. If there are some levels in between then
		 * करो_indirects label will take care of that.
		 */

		अगर (n == 1) अणु
			/*
			 * Start is at the direct block level, मुक्त
			 * everything to the end of the level.
			 */
			ext4_मुक्त_data(handle, inode, शून्य, i_data + offsets[0],
				       i_data + EXT4_Nसूची_BLOCKS);
			जाओ end_range;
		पूर्ण


		partial = p = ext4_find_shared(inode, n, offsets, chain, &nr);
		अगर (nr) अणु
			अगर (partial == chain) अणु
				/* Shared branch grows from the inode */
				ext4_मुक्त_branches(handle, inode, शून्य,
					   &nr, &nr+1, (chain+n-1) - partial);
				*partial->p = 0;
			पूर्ण अन्यथा अणु
				/* Shared branch grows from an indirect block */
				BUFFER_TRACE(partial->bh, "get_write_access");
				ext4_मुक्त_branches(handle, inode, partial->bh,
					partial->p,
					partial->p+1, (chain+n-1) - partial);
			पूर्ण
		पूर्ण

		/*
		 * Clear the ends of indirect blocks on the shared branch
		 * at the start of the range
		 */
		जबतक (partial > chain) अणु
			ext4_मुक्त_branches(handle, inode, partial->bh,
				partial->p + 1,
				(__le32 *)partial->bh->b_data+addr_per_block,
				(chain+n-1) - partial);
			partial--;
		पूर्ण

end_range:
		partial2 = p2 = ext4_find_shared(inode, n2, offsets2, chain2, &nr2);
		अगर (nr2) अणु
			अगर (partial2 == chain2) अणु
				/*
				 * Remember, end is exclusive so here we're at
				 * the start of the next level we're not going
				 * to मुक्त. Everything was covered by the start
				 * of the range.
				 */
				जाओ करो_indirects;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * ext4_find_shared वापसs Indirect काष्ठाure which
			 * poपूर्णांकs to the last element which should not be
			 * हटाओd by truncate. But this is end of the range
			 * in punch_hole so we need to poपूर्णांक to the next element
			 */
			partial2->p++;
		पूर्ण

		/*
		 * Clear the ends of indirect blocks on the shared branch
		 * at the end of the range
		 */
		जबतक (partial2 > chain2) अणु
			ext4_मुक्त_branches(handle, inode, partial2->bh,
					   (__le32 *)partial2->bh->b_data,
					   partial2->p,
					   (chain2+n2-1) - partial2);
			partial2--;
		पूर्ण
		जाओ करो_indirects;
	पूर्ण

	/* Punch happened within the same level (n == n2) */
	partial = p = ext4_find_shared(inode, n, offsets, chain, &nr);
	partial2 = p2 = ext4_find_shared(inode, n2, offsets2, chain2, &nr2);

	/* Free top, but only अगर partial2 isn't its subtree. */
	अगर (nr) अणु
		पूर्णांक level = min(partial - chain, partial2 - chain2);
		पूर्णांक i;
		पूर्णांक subtree = 1;

		क्रम (i = 0; i <= level; i++) अणु
			अगर (offsets[i] != offsets2[i]) अणु
				subtree = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!subtree) अणु
			अगर (partial == chain) अणु
				/* Shared branch grows from the inode */
				ext4_मुक्त_branches(handle, inode, शून्य,
						   &nr, &nr+1,
						   (chain+n-1) - partial);
				*partial->p = 0;
			पूर्ण अन्यथा अणु
				/* Shared branch grows from an indirect block */
				BUFFER_TRACE(partial->bh, "get_write_access");
				ext4_मुक्त_branches(handle, inode, partial->bh,
						   partial->p,
						   partial->p+1,
						   (chain+n-1) - partial);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!nr2) अणु
		/*
		 * ext4_find_shared वापसs Indirect काष्ठाure which
		 * poपूर्णांकs to the last element which should not be
		 * हटाओd by truncate. But this is end of the range
		 * in punch_hole so we need to poपूर्णांक to the next element
		 */
		partial2->p++;
	पूर्ण

	जबतक (partial > chain || partial2 > chain2) अणु
		पूर्णांक depth = (chain+n-1) - partial;
		पूर्णांक depth2 = (chain2+n2-1) - partial2;

		अगर (partial > chain && partial2 > chain2 &&
		    partial->bh->b_blocknr == partial2->bh->b_blocknr) अणु
			/*
			 * We've converged on the same block. Clear the range,
			 * then we're करोne.
			 */
			ext4_मुक्त_branches(handle, inode, partial->bh,
					   partial->p + 1,
					   partial2->p,
					   (chain+n-1) - partial);
			जाओ cleanup;
		पूर्ण

		/*
		 * The start and end partial branches may not be at the same
		 * level even though the punch happened within one level. So, we
		 * give them a chance to arrive at the same level, then walk
		 * them in step with each other until we converge on the same
		 * block.
		 */
		अगर (partial > chain && depth <= depth2) अणु
			ext4_मुक्त_branches(handle, inode, partial->bh,
					   partial->p + 1,
					   (__le32 *)partial->bh->b_data+addr_per_block,
					   (chain+n-1) - partial);
			partial--;
		पूर्ण
		अगर (partial2 > chain2 && depth2 <= depth) अणु
			ext4_मुक्त_branches(handle, inode, partial2->bh,
					   (__le32 *)partial2->bh->b_data,
					   partial2->p,
					   (chain2+n2-1) - partial2);
			partial2--;
		पूर्ण
	पूर्ण

cleanup:
	जबतक (p && p > chain) अणु
		BUFFER_TRACE(p->bh, "call brelse");
		brअन्यथा(p->bh);
		p--;
	पूर्ण
	जबतक (p2 && p2 > chain2) अणु
		BUFFER_TRACE(p2->bh, "call brelse");
		brअन्यथा(p2->bh);
		p2--;
	पूर्ण
	वापस 0;

करो_indirects:
	/* Kill the reमुख्यing (whole) subtrees */
	चयन (offsets[0]) अणु
	शेष:
		अगर (++n >= n2)
			अवरोध;
		nr = i_data[EXT4_IND_BLOCK];
		अगर (nr) अणु
			ext4_मुक्त_branches(handle, inode, शून्य, &nr, &nr+1, 1);
			i_data[EXT4_IND_BLOCK] = 0;
		पूर्ण
		fallthrough;
	हाल EXT4_IND_BLOCK:
		अगर (++n >= n2)
			अवरोध;
		nr = i_data[EXT4_DIND_BLOCK];
		अगर (nr) अणु
			ext4_मुक्त_branches(handle, inode, शून्य, &nr, &nr+1, 2);
			i_data[EXT4_DIND_BLOCK] = 0;
		पूर्ण
		fallthrough;
	हाल EXT4_DIND_BLOCK:
		अगर (++n >= n2)
			अवरोध;
		nr = i_data[EXT4_TIND_BLOCK];
		अगर (nr) अणु
			ext4_मुक्त_branches(handle, inode, शून्य, &nr, &nr+1, 3);
			i_data[EXT4_TIND_BLOCK] = 0;
		पूर्ण
		fallthrough;
	हाल EXT4_TIND_BLOCK:
		;
	पूर्ण
	जाओ cleanup;
पूर्ण
