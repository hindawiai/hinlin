<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/iomap.h>
#समावेश <linux/kसमय.स>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "bmap.h"
#समावेश "glock.h"
#समावेश "inode.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "rgrp.h"
#समावेश "log.h"
#समावेश "super.h"
#समावेश "trans.h"
#समावेश "dir.h"
#समावेश "util.h"
#समावेश "aops.h"
#समावेश "trace_gfs2.h"

/* This करोesn't need to be that large as max 64 bit poपूर्णांकers in a 4k
 * block is 512, so __u16 is fine क्रम that. It saves stack space to
 * keep it small.
 */
काष्ठा metapath अणु
	काष्ठा buffer_head *mp_bh[GFS2_MAX_META_HEIGHT];
	__u16 mp_list[GFS2_MAX_META_HEIGHT];
	पूर्णांक mp_fheight; /* find_metapath height */
	पूर्णांक mp_aheight; /* actual height (lookup height) */
पूर्ण;

अटल पूर्णांक punch_hole(काष्ठा gfs2_inode *ip, u64 offset, u64 length);

/**
 * gfs2_unstuffer_page - unstuff a stuffed inode पूर्णांकo a block cached by a page
 * @ip: the inode
 * @dibh: the dinode buffer
 * @block: the block number that was allocated
 * @page: The (optional) page. This is looked up अगर @page is शून्य
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_unstuffer_page(काष्ठा gfs2_inode *ip, काष्ठा buffer_head *dibh,
			       u64 block, काष्ठा page *page)
अणु
	काष्ठा inode *inode = &ip->i_inode;
	पूर्णांक release = 0;

	अगर (!page || page->index) अणु
		page = find_or_create_page(inode->i_mapping, 0, GFP_NOFS);
		अगर (!page)
			वापस -ENOMEM;
		release = 1;
	पूर्ण

	अगर (!PageUptodate(page)) अणु
		व्योम *kaddr = kmap(page);
		u64 dsize = i_size_पढ़ो(inode);
 
		अगर (dsize > gfs2_max_stuffed_size(ip))
			dsize = gfs2_max_stuffed_size(ip);

		स_नकल(kaddr, dibh->b_data + माप(काष्ठा gfs2_dinode), dsize);
		स_रखो(kaddr + dsize, 0, PAGE_SIZE - dsize);
		kunmap(page);

		SetPageUptodate(page);
	पूर्ण

	अगर (gfs2_is_jdata(ip)) अणु
		काष्ठा buffer_head *bh;

		अगर (!page_has_buffers(page))
			create_empty_buffers(page, BIT(inode->i_blkbits),
					     BIT(BH_Uptodate));

		bh = page_buffers(page);
		अगर (!buffer_mapped(bh))
			map_bh(bh, inode->i_sb, block);

		set_buffer_uptodate(bh);
		gfs2_trans_add_data(ip->i_gl, bh);
	पूर्ण अन्यथा अणु
		set_page_dirty(page);
		gfs2_ordered_add_inode(ip);
	पूर्ण

	अगर (release) अणु
		unlock_page(page);
		put_page(page);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * gfs2_unstuff_dinode - Unstuff a dinode when the data has grown too big
 * @ip: The GFS2 inode to unstuff
 * @page: The (optional) page. This is looked up अगर the @page is शून्य
 *
 * This routine unstuffs a dinode and वापसs it to a "normal" state such
 * that the height can be grown in the traditional way.
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_unstuff_dinode(काष्ठा gfs2_inode *ip, काष्ठा page *page)
अणु
	काष्ठा buffer_head *bh, *dibh;
	काष्ठा gfs2_dinode *di;
	u64 block = 0;
	पूर्णांक isdir = gfs2_is_dir(ip);
	पूर्णांक error;

	करोwn_ग_लिखो(&ip->i_rw_mutex);

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error)
		जाओ out;

	अगर (i_size_पढ़ो(&ip->i_inode)) अणु
		/* Get a मुक्त block, fill it with the stuffed data,
		   and ग_लिखो it out to disk */

		अचिन्हित पूर्णांक n = 1;
		error = gfs2_alloc_blocks(ip, &block, &n, 0, शून्य);
		अगर (error)
			जाओ out_brअन्यथा;
		अगर (isdir) अणु
			gfs2_trans_हटाओ_revoke(GFS2_SB(&ip->i_inode), block, 1);
			error = gfs2_dir_get_new_buffer(ip, block, &bh);
			अगर (error)
				जाओ out_brअन्यथा;
			gfs2_buffer_copy_tail(bh, माप(काष्ठा gfs2_meta_header),
					      dibh, माप(काष्ठा gfs2_dinode));
			brअन्यथा(bh);
		पूर्ण अन्यथा अणु
			error = gfs2_unstuffer_page(ip, dibh, block, page);
			अगर (error)
				जाओ out_brअन्यथा;
		पूर्ण
	पूर्ण

	/*  Set up the poपूर्णांकer to the new block  */

	gfs2_trans_add_meta(ip->i_gl, dibh);
	di = (काष्ठा gfs2_dinode *)dibh->b_data;
	gfs2_buffer_clear_tail(dibh, माप(काष्ठा gfs2_dinode));

	अगर (i_size_पढ़ो(&ip->i_inode)) अणु
		*(__be64 *)(di + 1) = cpu_to_be64(block);
		gfs2_add_inode_blocks(&ip->i_inode, 1);
		di->di_blocks = cpu_to_be64(gfs2_get_inode_blocks(&ip->i_inode));
	पूर्ण

	ip->i_height = 1;
	di->di_height = cpu_to_be16(1);

out_brअन्यथा:
	brअन्यथा(dibh);
out:
	up_ग_लिखो(&ip->i_rw_mutex);
	वापस error;
पूर्ण


/**
 * find_metapath - Find path through the metadata tree
 * @sdp: The superblock
 * @block: The disk block to look up
 * @mp: The metapath to वापस the result in
 * @height: The pre-calculated height of the metadata tree
 *
 *   This routine वापसs a काष्ठा metapath काष्ठाure that defines a path
 *   through the metadata of inode "ip" to get to block "block".
 *
 *   Example:
 *   Given:  "ip" is a height 3 file, "offset" is 101342453, and this is a
 *   fileप्रणाली with a blocksize of 4096.
 *
 *   find_metapath() would वापस a काष्ठा metapath काष्ठाure set to:
 *   mp_fheight = 3, mp_list[0] = 0, mp_list[1] = 48, and mp_list[2] = 165.
 *
 *   That means that in order to get to the block containing the byte at
 *   offset 101342453, we would load the indirect block poपूर्णांकed to by poपूर्णांकer
 *   0 in the dinode.  We would then load the indirect block poपूर्णांकed to by
 *   poपूर्णांकer 48 in that indirect block.  We would then load the data block
 *   poपूर्णांकed to by poपूर्णांकer 165 in that indirect block.
 *
 *             ----------------------------------------
 *             | Dinode |                             |
 *             |        |                            4|
 *             |        |0 1 2 3 4 5                 9|
 *             |        |                            6|
 *             ----------------------------------------
 *                       |
 *                       |
 *                       V
 *             ----------------------------------------
 *             | Indirect Block                       |
 *             |                                     5|
 *             |            4 4 4 4 4 5 5            1|
 *             |0           5 6 7 8 9 0 1            2|
 *             ----------------------------------------
 *                                |
 *                                |
 *                                V
 *             ----------------------------------------
 *             | Indirect Block                       |
 *             |                         1 1 1 1 1   5|
 *             |                         6 6 6 6 6   1|
 *             |0                        3 4 5 6 7   2|
 *             ----------------------------------------
 *                                           |
 *                                           |
 *                                           V
 *             ----------------------------------------
 *             | Data block containing offset         |
 *             |            101342453                 |
 *             |                                      |
 *             |                                      |
 *             ----------------------------------------
 *
 */

अटल व्योम find_metapath(स्थिर काष्ठा gfs2_sbd *sdp, u64 block,
			  काष्ठा metapath *mp, अचिन्हित पूर्णांक height)
अणु
	अचिन्हित पूर्णांक i;

	mp->mp_fheight = height;
	क्रम (i = height; i--;)
		mp->mp_list[i] = करो_भाग(block, sdp->sd_inptrs);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक metapath_branch_start(स्थिर काष्ठा metapath *mp)
अणु
	अगर (mp->mp_list[0] == 0)
		वापस 2;
	वापस 1;
पूर्ण

/**
 * metaptr1 - Return the first possible metadata poपूर्णांकer in a metapath buffer
 * @height: The metadata height (0 = dinode)
 * @mp: The metapath
 */
अटल अंतरभूत __be64 *metaptr1(अचिन्हित पूर्णांक height, स्थिर काष्ठा metapath *mp)
अणु
	काष्ठा buffer_head *bh = mp->mp_bh[height];
	अगर (height == 0)
		वापस ((__be64 *)(bh->b_data + माप(काष्ठा gfs2_dinode)));
	वापस ((__be64 *)(bh->b_data + माप(काष्ठा gfs2_meta_header)));
पूर्ण

/**
 * metapoपूर्णांकer - Return poपूर्णांकer to start of metadata in a buffer
 * @height: The metadata height (0 = dinode)
 * @mp: The metapath
 *
 * Return a poपूर्णांकer to the block number of the next height of the metadata
 * tree given a buffer containing the poपूर्णांकer to the current height of the
 * metadata tree.
 */

अटल अंतरभूत __be64 *metapoपूर्णांकer(अचिन्हित पूर्णांक height, स्थिर काष्ठा metapath *mp)
अणु
	__be64 *p = metaptr1(height, mp);
	वापस p + mp->mp_list[height];
पूर्ण

अटल अंतरभूत स्थिर __be64 *metaend(अचिन्हित पूर्णांक height, स्थिर काष्ठा metapath *mp)
अणु
	स्थिर काष्ठा buffer_head *bh = mp->mp_bh[height];
	वापस (स्थिर __be64 *)(bh->b_data + bh->b_size);
पूर्ण

अटल व्योम clone_metapath(काष्ठा metapath *clone, काष्ठा metapath *mp)
अणु
	अचिन्हित पूर्णांक hgt;

	*clone = *mp;
	क्रम (hgt = 0; hgt < mp->mp_aheight; hgt++)
		get_bh(clone->mp_bh[hgt]);
पूर्ण

अटल व्योम gfs2_metapath_ra(काष्ठा gfs2_glock *gl, __be64 *start, __be64 *end)
अणु
	स्थिर __be64 *t;

	क्रम (t = start; t < end; t++) अणु
		काष्ठा buffer_head *rabh;

		अगर (!*t)
			जारी;

		rabh = gfs2_getbuf(gl, be64_to_cpu(*t), CREATE);
		अगर (trylock_buffer(rabh)) अणु
			अगर (!buffer_uptodate(rabh)) अणु
				rabh->b_end_io = end_buffer_पढ़ो_sync;
				submit_bh(REQ_OP_READ,
					  REQ_RAHEAD | REQ_META | REQ_PRIO,
					  rabh);
				जारी;
			पूर्ण
			unlock_buffer(rabh);
		पूर्ण
		brअन्यथा(rabh);
	पूर्ण
पूर्ण

अटल पूर्णांक __fillup_metapath(काष्ठा gfs2_inode *ip, काष्ठा metapath *mp,
			     अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक h)
अणु
	क्रम (; x < h; x++) अणु
		__be64 *ptr = metapoपूर्णांकer(x, mp);
		u64 dblock = be64_to_cpu(*ptr);
		पूर्णांक ret;

		अगर (!dblock)
			अवरोध;
		ret = gfs2_meta_buffer(ip, GFS2_METATYPE_IN, dblock, &mp->mp_bh[x + 1]);
		अगर (ret)
			वापस ret;
	पूर्ण
	mp->mp_aheight = x + 1;
	वापस 0;
पूर्ण

/**
 * lookup_metapath - Walk the metadata tree to a specअगरic poपूर्णांक
 * @ip: The inode
 * @mp: The metapath
 *
 * Assumes that the inode's buffer has alपढ़ोy been looked up and
 * hooked onto mp->mp_bh[0] and that the metapath has been initialised
 * by find_metapath().
 *
 * If this function encounters part of the tree which has not been
 * allocated, it वापसs the current height of the tree at the poपूर्णांक
 * at which it found the unallocated block. Blocks which are found are
 * added to the mp->mp_bh[] list.
 *
 * Returns: error
 */

अटल पूर्णांक lookup_metapath(काष्ठा gfs2_inode *ip, काष्ठा metapath *mp)
अणु
	वापस __fillup_metapath(ip, mp, 0, ip->i_height - 1);
पूर्ण

/**
 * fillup_metapath - fill up buffers क्रम the metadata path to a specअगरic height
 * @ip: The inode
 * @mp: The metapath
 * @h: The height to which it should be mapped
 *
 * Similar to lookup_metapath, but करोes lookups क्रम a range of heights
 *
 * Returns: error or the number of buffers filled
 */

अटल पूर्णांक fillup_metapath(काष्ठा gfs2_inode *ip, काष्ठा metapath *mp, पूर्णांक h)
अणु
	अचिन्हित पूर्णांक x = 0;
	पूर्णांक ret;

	अगर (h) अणु
		/* find the first buffer we need to look up. */
		क्रम (x = h - 1; x > 0; x--) अणु
			अगर (mp->mp_bh[x])
				अवरोध;
		पूर्ण
	पूर्ण
	ret = __fillup_metapath(ip, mp, x, h);
	अगर (ret)
		वापस ret;
	वापस mp->mp_aheight - x - 1;
पूर्ण

अटल sector_t metapath_to_block(काष्ठा gfs2_sbd *sdp, काष्ठा metapath *mp)
अणु
	sector_t factor = 1, block = 0;
	पूर्णांक hgt;

	क्रम (hgt = mp->mp_fheight - 1; hgt >= 0; hgt--) अणु
		अगर (hgt < mp->mp_aheight)
			block += mp->mp_list[hgt] * factor;
		factor *= sdp->sd_inptrs;
	पूर्ण
	वापस block;
पूर्ण

अटल व्योम release_metapath(काष्ठा metapath *mp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < GFS2_MAX_META_HEIGHT; i++) अणु
		अगर (mp->mp_bh[i] == शून्य)
			अवरोध;
		brअन्यथा(mp->mp_bh[i]);
		mp->mp_bh[i] = शून्य;
	पूर्ण
पूर्ण

/**
 * gfs2_extent_length - Returns length of an extent of blocks
 * @bh: The metadata block
 * @ptr: Current position in @bh
 * @limit: Max extent length to वापस
 * @eob: Set to 1 अगर we hit "end of block"
 *
 * Returns: The length of the extent (minimum of one block)
 */

अटल अंतरभूत अचिन्हित पूर्णांक gfs2_extent_length(काष्ठा buffer_head *bh, __be64 *ptr, माप_प्रकार limit, पूर्णांक *eob)
अणु
	स्थिर __be64 *end = (__be64 *)(bh->b_data + bh->b_size);
	स्थिर __be64 *first = ptr;
	u64 d = be64_to_cpu(*ptr);

	*eob = 0;
	करो अणु
		ptr++;
		अगर (ptr >= end)
			अवरोध;
		d++;
	पूर्ण जबतक(be64_to_cpu(*ptr) == d);
	अगर (ptr >= end)
		*eob = 1;
	वापस ptr - first;
पूर्ण

क्रमागत walker_status अणु WALK_STOP, WALK_FOLLOW, WALK_CONTINUE पूर्ण;

/*
 * gfs2_metadata_walker - walk an indirect block
 * @mp: Metapath to indirect block
 * @ptrs: Number of poपूर्णांकers to look at
 *
 * When वापसing WALK_FOLLOW, the walker must update @mp to poपूर्णांक at the right
 * indirect block to follow.
 */
प्रकार क्रमागत walker_status (*gfs2_metadata_walker)(काष्ठा metapath *mp,
						   अचिन्हित पूर्णांक ptrs);

/*
 * gfs2_walk_metadata - walk a tree of indirect blocks
 * @inode: The inode
 * @mp: Starting poपूर्णांक of walk
 * @max_len: Maximum number of blocks to walk
 * @walker: Called during the walk
 *
 * Returns 1 अगर the walk was stopped by @walker, 0 अगर we went past @max_len or
 * past the end of metadata, and a negative error code otherwise.
 */

अटल पूर्णांक gfs2_walk_metadata(काष्ठा inode *inode, काष्ठा metapath *mp,
		u64 max_len, gfs2_metadata_walker walker)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	u64 factor = 1;
	अचिन्हित पूर्णांक hgt;
	पूर्णांक ret;

	/*
	 * The walk starts in the lowest allocated indirect block, which may be
	 * beक्रमe the position indicated by @mp.  Adjust @max_len accordingly
	 * to aव्योम a लघु walk.
	 */
	क्रम (hgt = mp->mp_fheight - 1; hgt >= mp->mp_aheight; hgt--) अणु
		max_len += mp->mp_list[hgt] * factor;
		mp->mp_list[hgt] = 0;
		factor *= sdp->sd_inptrs;
	पूर्ण

	क्रम (;;) अणु
		u16 start = mp->mp_list[hgt];
		क्रमागत walker_status status;
		अचिन्हित पूर्णांक ptrs;
		u64 len;

		/* Walk indirect block. */
		ptrs = (hgt >= 1 ? sdp->sd_inptrs : sdp->sd_diptrs) - start;
		len = ptrs * factor;
		अगर (len > max_len)
			ptrs = DIV_ROUND_UP_ULL(max_len, factor);
		status = walker(mp, ptrs);
		चयन (status) अणु
		हाल WALK_STOP:
			वापस 1;
		हाल WALK_FOLLOW:
			BUG_ON(mp->mp_aheight == mp->mp_fheight);
			ptrs = mp->mp_list[hgt] - start;
			len = ptrs * factor;
			अवरोध;
		हाल WALK_CONTINUE:
			अवरोध;
		पूर्ण
		अगर (len >= max_len)
			अवरोध;
		max_len -= len;
		अगर (status == WALK_FOLLOW)
			जाओ fill_up_metapath;

lower_metapath:
		/* Decrease height of metapath. */
		brअन्यथा(mp->mp_bh[hgt]);
		mp->mp_bh[hgt] = शून्य;
		mp->mp_list[hgt] = 0;
		अगर (!hgt)
			अवरोध;
		hgt--;
		factor *= sdp->sd_inptrs;

		/* Advance in metadata tree. */
		(mp->mp_list[hgt])++;
		अगर (hgt) अणु
			अगर (mp->mp_list[hgt] >= sdp->sd_inptrs)
				जाओ lower_metapath;
		पूर्ण अन्यथा अणु
			अगर (mp->mp_list[hgt] >= sdp->sd_diptrs)
				अवरोध;
		पूर्ण

fill_up_metapath:
		/* Increase height of metapath. */
		ret = fillup_metapath(ip, mp, ip->i_height - 1);
		अगर (ret < 0)
			वापस ret;
		hgt += ret;
		क्रम (; ret; ret--)
			करो_भाग(factor, sdp->sd_inptrs);
		mp->mp_aheight = hgt + 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत walker_status gfs2_hole_walker(काष्ठा metapath *mp,
					   अचिन्हित पूर्णांक ptrs)
अणु
	स्थिर __be64 *start, *ptr, *end;
	अचिन्हित पूर्णांक hgt;

	hgt = mp->mp_aheight - 1;
	start = metapoपूर्णांकer(hgt, mp);
	end = start + ptrs;

	क्रम (ptr = start; ptr < end; ptr++) अणु
		अगर (*ptr) अणु
			mp->mp_list[hgt] += ptr - start;
			अगर (mp->mp_aheight == mp->mp_fheight)
				वापस WALK_STOP;
			वापस WALK_FOLLOW;
		पूर्ण
	पूर्ण
	वापस WALK_CONTINUE;
पूर्ण

/**
 * gfs2_hole_size - figure out the size of a hole
 * @inode: The inode
 * @lblock: The logical starting block number
 * @len: How far to look (in blocks)
 * @mp: The metapath at lblock
 * @iomap: The iomap to store the hole size in
 *
 * This function modअगरies @mp.
 *
 * Returns: त्रुटि_सं on error
 */
अटल पूर्णांक gfs2_hole_size(काष्ठा inode *inode, sector_t lblock, u64 len,
			  काष्ठा metapath *mp, काष्ठा iomap *iomap)
अणु
	काष्ठा metapath clone;
	u64 hole_size;
	पूर्णांक ret;

	clone_metapath(&clone, mp);
	ret = gfs2_walk_metadata(inode, &clone, len, gfs2_hole_walker);
	अगर (ret < 0)
		जाओ out;

	अगर (ret == 1)
		hole_size = metapath_to_block(GFS2_SB(inode), &clone) - lblock;
	अन्यथा
		hole_size = len;
	iomap->length = hole_size << inode->i_blkbits;
	ret = 0;

out:
	release_metapath(&clone);
	वापस ret;
पूर्ण

अटल अंतरभूत __be64 *gfs2_indirect_init(काष्ठा metapath *mp,
					 काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक i,
					 अचिन्हित offset, u64 bn)
अणु
	__be64 *ptr = (__be64 *)(mp->mp_bh[i - 1]->b_data +
		       ((i > 1) ? माप(काष्ठा gfs2_meta_header) :
				 माप(काष्ठा gfs2_dinode)));
	BUG_ON(i < 1);
	BUG_ON(mp->mp_bh[i] != शून्य);
	mp->mp_bh[i] = gfs2_meta_new(gl, bn);
	gfs2_trans_add_meta(gl, mp->mp_bh[i]);
	gfs2_metatype_set(mp->mp_bh[i], GFS2_METATYPE_IN, GFS2_FORMAT_IN);
	gfs2_buffer_clear_tail(mp->mp_bh[i], माप(काष्ठा gfs2_meta_header));
	ptr += offset;
	*ptr = cpu_to_be64(bn);
	वापस ptr;
पूर्ण

क्रमागत alloc_state अणु
	ALLOC_DATA = 0,
	ALLOC_GROW_DEPTH = 1,
	ALLOC_GROW_HEIGHT = 2,
	/* ALLOC_UNSTUFF = 3,   TBD and rather complicated */
पूर्ण;

/**
 * __gfs2_iomap_alloc - Build a metadata tree of the requested height
 * @inode: The GFS2 inode
 * @iomap: The iomap काष्ठाure
 * @mp: The metapath, with proper height inक्रमmation calculated
 *
 * In this routine we may have to alloc:
 *   i) Indirect blocks to grow the metadata tree height
 *  ii) Indirect blocks to fill in lower part of the metadata tree
 * iii) Data blocks
 *
 * This function is called after __gfs2_iomap_get, which works out the
 * total number of blocks which we need via gfs2_alloc_size.
 *
 * We then करो the actual allocation asking क्रम an extent at a समय (अगर
 * enough contiguous मुक्त blocks are available, there will only be one
 * allocation request per call) and uses the state machine to initialise
 * the blocks in order.
 *
 * Right now, this function will allocate at most one indirect block
 * worth of data -- with a शेष block size of 4K, that's slightly
 * less than 2M.  If this limitation is ever हटाओd to allow huge
 * allocations, we would probably still want to limit the iomap size we
 * वापस to aव्योम stalling other tasks during huge ग_लिखोs; the next
 * iomap iteration would then find the blocks alपढ़ोy allocated.
 *
 * Returns: त्रुटि_सं on error
 */

अटल पूर्णांक __gfs2_iomap_alloc(काष्ठा inode *inode, काष्ठा iomap *iomap,
			      काष्ठा metapath *mp)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा buffer_head *dibh = mp->mp_bh[0];
	u64 bn;
	अचिन्हित n, i, blks, alloced = 0, iblks = 0, branch_start = 0;
	माप_प्रकार dblks = iomap->length >> inode->i_blkbits;
	स्थिर अचिन्हित end_of_metadata = mp->mp_fheight - 1;
	पूर्णांक ret;
	क्रमागत alloc_state state;
	__be64 *ptr;
	__be64 zero_bn = 0;

	BUG_ON(mp->mp_aheight < 1);
	BUG_ON(dibh == शून्य);
	BUG_ON(dblks < 1);

	gfs2_trans_add_meta(ip->i_gl, dibh);

	करोwn_ग_लिखो(&ip->i_rw_mutex);

	अगर (mp->mp_fheight == mp->mp_aheight) अणु
		/* Bottom indirect block exists */
		state = ALLOC_DATA;
	पूर्ण अन्यथा अणु
		/* Need to allocate indirect blocks */
		अगर (mp->mp_fheight == ip->i_height) अणु
			/* Writing पूर्णांकo existing tree, extend tree करोwn */
			iblks = mp->mp_fheight - mp->mp_aheight;
			state = ALLOC_GROW_DEPTH;
		पूर्ण अन्यथा अणु
			/* Building up tree height */
			state = ALLOC_GROW_HEIGHT;
			iblks = mp->mp_fheight - ip->i_height;
			branch_start = metapath_branch_start(mp);
			iblks += (mp->mp_fheight - branch_start);
		पूर्ण
	पूर्ण

	/* start of the second part of the function (state machine) */

	blks = dblks + iblks;
	i = mp->mp_aheight;
	करो अणु
		n = blks - alloced;
		ret = gfs2_alloc_blocks(ip, &bn, &n, 0, शून्य);
		अगर (ret)
			जाओ out;
		alloced += n;
		अगर (state != ALLOC_DATA || gfs2_is_jdata(ip))
			gfs2_trans_हटाओ_revoke(sdp, bn, n);
		चयन (state) अणु
		/* Growing height of tree */
		हाल ALLOC_GROW_HEIGHT:
			अगर (i == 1) अणु
				ptr = (__be64 *)(dibh->b_data +
						 माप(काष्ठा gfs2_dinode));
				zero_bn = *ptr;
			पूर्ण
			क्रम (; i - 1 < mp->mp_fheight - ip->i_height && n > 0;
			     i++, n--)
				gfs2_indirect_init(mp, ip->i_gl, i, 0, bn++);
			अगर (i - 1 == mp->mp_fheight - ip->i_height) अणु
				i--;
				gfs2_buffer_copy_tail(mp->mp_bh[i],
						माप(काष्ठा gfs2_meta_header),
						dibh, माप(काष्ठा gfs2_dinode));
				gfs2_buffer_clear_tail(dibh,
						माप(काष्ठा gfs2_dinode) +
						माप(__be64));
				ptr = (__be64 *)(mp->mp_bh[i]->b_data +
					माप(काष्ठा gfs2_meta_header));
				*ptr = zero_bn;
				state = ALLOC_GROW_DEPTH;
				क्रम(i = branch_start; i < mp->mp_fheight; i++) अणु
					अगर (mp->mp_bh[i] == शून्य)
						अवरोध;
					brअन्यथा(mp->mp_bh[i]);
					mp->mp_bh[i] = शून्य;
				पूर्ण
				i = branch_start;
			पूर्ण
			अगर (n == 0)
				अवरोध;
			fallthrough;	/* To branching from existing tree */
		हाल ALLOC_GROW_DEPTH:
			अगर (i > 1 && i < mp->mp_fheight)
				gfs2_trans_add_meta(ip->i_gl, mp->mp_bh[i-1]);
			क्रम (; i < mp->mp_fheight && n > 0; i++, n--)
				gfs2_indirect_init(mp, ip->i_gl, i,
						   mp->mp_list[i-1], bn++);
			अगर (i == mp->mp_fheight)
				state = ALLOC_DATA;
			अगर (n == 0)
				अवरोध;
			fallthrough;	/* To tree complete, adding data blocks */
		हाल ALLOC_DATA:
			BUG_ON(n > dblks);
			BUG_ON(mp->mp_bh[end_of_metadata] == शून्य);
			gfs2_trans_add_meta(ip->i_gl, mp->mp_bh[end_of_metadata]);
			dblks = n;
			ptr = metapoपूर्णांकer(end_of_metadata, mp);
			iomap->addr = bn << inode->i_blkbits;
			iomap->flags |= IOMAP_F_MERGED | IOMAP_F_NEW;
			जबतक (n-- > 0)
				*ptr++ = cpu_to_be64(bn++);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (iomap->addr == IOMAP_शून्य_ADDR);

	iomap->type = IOMAP_MAPPED;
	iomap->length = (u64)dblks << inode->i_blkbits;
	ip->i_height = mp->mp_fheight;
	gfs2_add_inode_blocks(&ip->i_inode, alloced);
	gfs2_dinode_out(ip, dibh->b_data);
out:
	up_ग_लिखो(&ip->i_rw_mutex);
	वापस ret;
पूर्ण

#घोषणा IOMAP_F_GFS2_BOUNDARY IOMAP_F_PRIVATE

/**
 * gfs2_alloc_size - Compute the maximum allocation size
 * @inode: The inode
 * @mp: The metapath
 * @size: Requested size in blocks
 *
 * Compute the maximum size of the next allocation at @mp.
 *
 * Returns: size in blocks
 */
अटल u64 gfs2_alloc_size(काष्ठा inode *inode, काष्ठा metapath *mp, u64 size)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	स्थिर __be64 *first, *ptr, *end;

	/*
	 * For ग_लिखोs to stuffed files, this function is called twice via
	 * __gfs2_iomap_get, beक्रमe and after unstuffing. The size we वापस the
	 * first समय needs to be large enough to get the reservation and
	 * allocation sizes right.  The size we वापस the second समय must
	 * be exact or अन्यथा __gfs2_iomap_alloc won't करो the right thing.
	 */

	अगर (gfs2_is_stuffed(ip) || mp->mp_fheight != mp->mp_aheight) अणु
		अचिन्हित पूर्णांक maxsize = mp->mp_fheight > 1 ?
			sdp->sd_inptrs : sdp->sd_diptrs;
		maxsize -= mp->mp_list[mp->mp_fheight - 1];
		अगर (size > maxsize)
			size = maxsize;
		वापस size;
	पूर्ण

	first = metapoपूर्णांकer(ip->i_height - 1, mp);
	end = metaend(ip->i_height - 1, mp);
	अगर (end - first > size)
		end = first + size;
	क्रम (ptr = first; ptr < end; ptr++) अणु
		अगर (*ptr)
			अवरोध;
	पूर्ण
	वापस ptr - first;
पूर्ण

/**
 * __gfs2_iomap_get - Map blocks from an inode to disk blocks
 * @inode: The inode
 * @pos: Starting position in bytes
 * @length: Length to map, in bytes
 * @flags: iomap flags
 * @iomap: The iomap काष्ठाure
 * @mp: The metapath
 *
 * Returns: त्रुटि_सं
 */
अटल पूर्णांक __gfs2_iomap_get(काष्ठा inode *inode, loff_t pos, loff_t length,
			    अचिन्हित flags, काष्ठा iomap *iomap,
			    काष्ठा metapath *mp)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	loff_t size = i_size_पढ़ो(inode);
	__be64 *ptr;
	sector_t lblock;
	sector_t lblock_stop;
	पूर्णांक ret;
	पूर्णांक eob;
	u64 len;
	काष्ठा buffer_head *dibh = शून्य, *bh;
	u8 height;

	अगर (!length)
		वापस -EINVAL;

	करोwn_पढ़ो(&ip->i_rw_mutex);

	ret = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (ret)
		जाओ unlock;
	mp->mp_bh[0] = dibh;

	अगर (gfs2_is_stuffed(ip)) अणु
		अगर (flags & IOMAP_WRITE) अणु
			loff_t max_size = gfs2_max_stuffed_size(ip);

			अगर (pos + length > max_size)
				जाओ unstuff;
			iomap->length = max_size;
		पूर्ण अन्यथा अणु
			अगर (pos >= size) अणु
				अगर (flags & IOMAP_REPORT) अणु
					ret = -ENOENT;
					जाओ unlock;
				पूर्ण अन्यथा अणु
					iomap->offset = pos;
					iomap->length = length;
					जाओ hole_found;
				पूर्ण
			पूर्ण
			iomap->length = size;
		पूर्ण
		iomap->addr = (ip->i_no_addr << inode->i_blkbits) +
			      माप(काष्ठा gfs2_dinode);
		iomap->type = IOMAP_INLINE;
		iomap->अंतरभूत_data = dibh->b_data + माप(काष्ठा gfs2_dinode);
		जाओ out;
	पूर्ण

unstuff:
	lblock = pos >> inode->i_blkbits;
	iomap->offset = lblock << inode->i_blkbits;
	lblock_stop = (pos + length - 1) >> inode->i_blkbits;
	len = lblock_stop - lblock + 1;
	iomap->length = len << inode->i_blkbits;

	height = ip->i_height;
	जबतक ((lblock + 1) * sdp->sd_sb.sb_bsize > sdp->sd_heightsize[height])
		height++;
	find_metapath(sdp, lblock, mp, height);
	अगर (height > ip->i_height || gfs2_is_stuffed(ip))
		जाओ करो_alloc;

	ret = lookup_metapath(ip, mp);
	अगर (ret)
		जाओ unlock;

	अगर (mp->mp_aheight != ip->i_height)
		जाओ करो_alloc;

	ptr = metapoपूर्णांकer(ip->i_height - 1, mp);
	अगर (*ptr == 0)
		जाओ करो_alloc;

	bh = mp->mp_bh[ip->i_height - 1];
	len = gfs2_extent_length(bh, ptr, len, &eob);

	iomap->addr = be64_to_cpu(*ptr) << inode->i_blkbits;
	iomap->length = len << inode->i_blkbits;
	iomap->type = IOMAP_MAPPED;
	iomap->flags |= IOMAP_F_MERGED;
	अगर (eob)
		iomap->flags |= IOMAP_F_GFS2_BOUNDARY;

out:
	iomap->bdev = inode->i_sb->s_bdev;
unlock:
	up_पढ़ो(&ip->i_rw_mutex);
	वापस ret;

करो_alloc:
	अगर (flags & IOMAP_REPORT) अणु
		अगर (pos >= size)
			ret = -ENOENT;
		अन्यथा अगर (height == ip->i_height)
			ret = gfs2_hole_size(inode, lblock, len, mp, iomap);
		अन्यथा
			iomap->length = size - pos;
	पूर्ण अन्यथा अगर (flags & IOMAP_WRITE) अणु
		u64 alloc_size;

		अगर (flags & IOMAP_सूचीECT)
			जाओ out;  /* (see gfs2_file_direct_ग_लिखो) */

		len = gfs2_alloc_size(inode, mp, len);
		alloc_size = len << inode->i_blkbits;
		अगर (alloc_size < iomap->length)
			iomap->length = alloc_size;
	पूर्ण अन्यथा अणु
		अगर (pos < size && height == ip->i_height)
			ret = gfs2_hole_size(inode, lblock, len, mp, iomap);
	पूर्ण
hole_found:
	iomap->addr = IOMAP_शून्य_ADDR;
	iomap->type = IOMAP_HOLE;
	जाओ out;
पूर्ण

अटल पूर्णांक gfs2_ग_लिखो_lock(काष्ठा inode *inode)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	पूर्णांक error;

	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &ip->i_gh);
	error = gfs2_glock_nq(&ip->i_gh);
	अगर (error)
		जाओ out_uninit;
	अगर (&ip->i_inode == sdp->sd_rindex) अणु
		काष्ठा gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);

		error = gfs2_glock_nq_init(m_ip->i_gl, LM_ST_EXCLUSIVE,
					   GL_NOCACHE, &m_ip->i_gh);
		अगर (error)
			जाओ out_unlock;
	पूर्ण
	वापस 0;

out_unlock:
	gfs2_glock_dq(&ip->i_gh);
out_uninit:
	gfs2_holder_uninit(&ip->i_gh);
	वापस error;
पूर्ण

अटल व्योम gfs2_ग_लिखो_unlock(काष्ठा inode *inode)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);

	अगर (&ip->i_inode == sdp->sd_rindex) अणु
		काष्ठा gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);

		gfs2_glock_dq_uninit(&m_ip->i_gh);
	पूर्ण
	gfs2_glock_dq_uninit(&ip->i_gh);
पूर्ण

अटल पूर्णांक gfs2_iomap_page_prepare(काष्ठा inode *inode, loff_t pos,
				   अचिन्हित len, काष्ठा iomap *iomap)
अणु
	अचिन्हित पूर्णांक blockmask = i_blocksize(inode) - 1;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	अचिन्हित पूर्णांक blocks;

	blocks = ((pos & blockmask) + len + blockmask) >> inode->i_blkbits;
	वापस gfs2_trans_begin(sdp, RES_DINODE + blocks, 0);
पूर्ण

अटल व्योम gfs2_iomap_page_करोne(काष्ठा inode *inode, loff_t pos,
				 अचिन्हित copied, काष्ठा page *page,
				 काष्ठा iomap *iomap)
अणु
	काष्ठा gfs2_trans *tr = current->journal_info;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);

	अगर (page && !gfs2_is_stuffed(ip))
		gfs2_page_add_databufs(ip, page, offset_in_page(pos), copied);

	अगर (tr->tr_num_buf_new)
		__mark_inode_dirty(inode, I_सूचीTY_DATASYNC);

	gfs2_trans_end(sdp);
पूर्ण

अटल स्थिर काष्ठा iomap_page_ops gfs2_iomap_page_ops = अणु
	.page_prepare = gfs2_iomap_page_prepare,
	.page_करोne = gfs2_iomap_page_करोne,
पूर्ण;

अटल पूर्णांक gfs2_iomap_begin_ग_लिखो(काष्ठा inode *inode, loff_t pos,
				  loff_t length, अचिन्हित flags,
				  काष्ठा iomap *iomap,
				  काष्ठा metapath *mp)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	bool unstuff;
	पूर्णांक ret;

	unstuff = gfs2_is_stuffed(ip) &&
		  pos + length > gfs2_max_stuffed_size(ip);

	अगर (unstuff || iomap->type == IOMAP_HOLE) अणु
		अचिन्हित पूर्णांक data_blocks, ind_blocks;
		काष्ठा gfs2_alloc_parms ap = अणुपूर्ण;
		अचिन्हित पूर्णांक rblocks;
		काष्ठा gfs2_trans *tr;

		gfs2_ग_लिखो_calc_reserv(ip, iomap->length, &data_blocks,
				       &ind_blocks);
		ap.target = data_blocks + ind_blocks;
		ret = gfs2_quota_lock_check(ip, &ap);
		अगर (ret)
			वापस ret;

		ret = gfs2_inplace_reserve(ip, &ap);
		अगर (ret)
			जाओ out_qunlock;

		rblocks = RES_DINODE + ind_blocks;
		अगर (gfs2_is_jdata(ip))
			rblocks += data_blocks;
		अगर (ind_blocks || data_blocks)
			rblocks += RES_STATFS + RES_QUOTA;
		अगर (inode == sdp->sd_rindex)
			rblocks += 2 * RES_STATFS;
		rblocks += gfs2_rg_blocks(ip, data_blocks + ind_blocks);

		ret = gfs2_trans_begin(sdp, rblocks,
				       iomap->length >> inode->i_blkbits);
		अगर (ret)
			जाओ out_trans_fail;

		अगर (unstuff) अणु
			ret = gfs2_unstuff_dinode(ip, शून्य);
			अगर (ret)
				जाओ out_trans_end;
			release_metapath(mp);
			ret = __gfs2_iomap_get(inode, iomap->offset,
					       iomap->length, flags, iomap, mp);
			अगर (ret)
				जाओ out_trans_end;
		पूर्ण

		अगर (iomap->type == IOMAP_HOLE) अणु
			ret = __gfs2_iomap_alloc(inode, iomap, mp);
			अगर (ret) अणु
				gfs2_trans_end(sdp);
				gfs2_inplace_release(ip);
				punch_hole(ip, iomap->offset, iomap->length);
				जाओ out_qunlock;
			पूर्ण
		पूर्ण

		tr = current->journal_info;
		अगर (tr->tr_num_buf_new)
			__mark_inode_dirty(inode, I_सूचीTY_DATASYNC);

		gfs2_trans_end(sdp);
	पूर्ण

	अगर (gfs2_is_stuffed(ip) || gfs2_is_jdata(ip))
		iomap->page_ops = &gfs2_iomap_page_ops;
	वापस 0;

out_trans_end:
	gfs2_trans_end(sdp);
out_trans_fail:
	gfs2_inplace_release(ip);
out_qunlock:
	gfs2_quota_unlock(ip);
	वापस ret;
पूर्ण

अटल अंतरभूत bool gfs2_iomap_need_ग_लिखो_lock(अचिन्हित flags)
अणु
	वापस (flags & IOMAP_WRITE) && !(flags & IOMAP_सूचीECT);
पूर्ण

अटल पूर्णांक gfs2_iomap_begin(काष्ठा inode *inode, loff_t pos, loff_t length,
			    अचिन्हित flags, काष्ठा iomap *iomap,
			    काष्ठा iomap *srcmap)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा metapath mp = अणु .mp_aheight = 1, पूर्ण;
	पूर्णांक ret;

	अगर (gfs2_is_jdata(ip))
		iomap->flags |= IOMAP_F_BUFFER_HEAD;

	trace_gfs2_iomap_start(ip, pos, length, flags);
	अगर (gfs2_iomap_need_ग_लिखो_lock(flags)) अणु
		ret = gfs2_ग_लिखो_lock(inode);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = __gfs2_iomap_get(inode, pos, length, flags, iomap, &mp);
	अगर (ret)
		जाओ out_unlock;

	चयन(flags & (IOMAP_WRITE | IOMAP_ZERO)) अणु
	हाल IOMAP_WRITE:
		अगर (flags & IOMAP_सूचीECT) अणु
			/*
			 * Silently fall back to buffered I/O क्रम stuffed files
			 * or अगर we've got a hole (see gfs2_file_direct_ग_लिखो).
			 */
			अगर (iomap->type != IOMAP_MAPPED)
				ret = -ENOTBLK;
			जाओ out_unlock;
		पूर्ण
		अवरोध;
	हाल IOMAP_ZERO:
		अगर (iomap->type == IOMAP_HOLE)
			जाओ out_unlock;
		अवरोध;
	शेष:
		जाओ out_unlock;
	पूर्ण

	ret = gfs2_iomap_begin_ग_लिखो(inode, pos, length, flags, iomap, &mp);

out_unlock:
	अगर (ret && gfs2_iomap_need_ग_लिखो_lock(flags))
		gfs2_ग_लिखो_unlock(inode);
	release_metapath(&mp);
out:
	trace_gfs2_iomap_end(ip, iomap, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक gfs2_iomap_end(काष्ठा inode *inode, loff_t pos, loff_t length,
			  sमाप_प्रकार written, अचिन्हित flags, काष्ठा iomap *iomap)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);

	चयन (flags & (IOMAP_WRITE | IOMAP_ZERO)) अणु
	हाल IOMAP_WRITE:
		अगर (flags & IOMAP_सूचीECT)
			वापस 0;
		अवरोध;
	हाल IOMAP_ZERO:
		 अगर (iomap->type == IOMAP_HOLE)
			 वापस 0;
		 अवरोध;
	शेष:
		 वापस 0;
	पूर्ण

	अगर (!gfs2_is_stuffed(ip))
		gfs2_ordered_add_inode(ip);

	अगर (inode == sdp->sd_rindex)
		adjust_fs_space(inode);

	gfs2_inplace_release(ip);

	अगर (ip->i_qadata && ip->i_qadata->qa_qd_num)
		gfs2_quota_unlock(ip);

	अगर (length != written && (iomap->flags & IOMAP_F_NEW)) अणु
		/* Deallocate blocks that were just allocated. */
		loff_t blockmask = i_blocksize(inode) - 1;
		loff_t end = (pos + length) & ~blockmask;

		pos = (pos + written + blockmask) & ~blockmask;
		अगर (pos < end) अणु
			truncate_pagecache_range(inode, pos, end - 1);
			punch_hole(ip, pos, end - pos);
		पूर्ण
	पूर्ण

	अगर (unlikely(!written))
		जाओ out_unlock;

	अगर (iomap->flags & IOMAP_F_SIZE_CHANGED)
		mark_inode_dirty(inode);
	set_bit(GLF_सूचीTY, &ip->i_gl->gl_flags);

out_unlock:
	अगर (gfs2_iomap_need_ग_लिखो_lock(flags))
		gfs2_ग_लिखो_unlock(inode);
	वापस 0;
पूर्ण

स्थिर काष्ठा iomap_ops gfs2_iomap_ops = अणु
	.iomap_begin = gfs2_iomap_begin,
	.iomap_end = gfs2_iomap_end,
पूर्ण;

/**
 * gfs2_block_map - Map one or more blocks of an inode to a disk block
 * @inode: The inode
 * @lblock: The logical block number
 * @bh_map: The bh to be mapped
 * @create: True अगर its ok to alloc blocks to satअगरy the request
 *
 * The size of the requested mapping is defined in bh_map->b_size.
 *
 * Clears buffer_mapped(bh_map) and leaves bh_map->b_size unchanged
 * when @lblock is not mapped.  Sets buffer_mapped(bh_map) and
 * bh_map->b_size to indicate the size of the mapping when @lblock and
 * successive blocks are mapped, up to the requested size.
 *
 * Sets buffer_boundary() अगर a पढ़ो of metadata will be required
 * beक्रमe the next block can be mapped. Sets buffer_new() अगर new
 * blocks were allocated.
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_block_map(काष्ठा inode *inode, sector_t lblock,
		   काष्ठा buffer_head *bh_map, पूर्णांक create)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	loff_t pos = (loff_t)lblock << inode->i_blkbits;
	loff_t length = bh_map->b_size;
	काष्ठा iomap iomap = अणु पूर्ण;
	पूर्णांक ret;

	clear_buffer_mapped(bh_map);
	clear_buffer_new(bh_map);
	clear_buffer_boundary(bh_map);
	trace_gfs2_bmap(ip, bh_map, lblock, create, 1);

	अगर (!create)
		ret = gfs2_iomap_get(inode, pos, length, &iomap);
	अन्यथा
		ret = gfs2_iomap_alloc(inode, pos, length, &iomap);
	अगर (ret)
		जाओ out;

	अगर (iomap.length > bh_map->b_size) अणु
		iomap.length = bh_map->b_size;
		iomap.flags &= ~IOMAP_F_GFS2_BOUNDARY;
	पूर्ण
	अगर (iomap.addr != IOMAP_शून्य_ADDR)
		map_bh(bh_map, inode->i_sb, iomap.addr >> inode->i_blkbits);
	bh_map->b_size = iomap.length;
	अगर (iomap.flags & IOMAP_F_GFS2_BOUNDARY)
		set_buffer_boundary(bh_map);
	अगर (iomap.flags & IOMAP_F_NEW)
		set_buffer_new(bh_map);

out:
	trace_gfs2_bmap(ip, bh_map, lblock, create, ret);
	वापस ret;
पूर्ण

पूर्णांक gfs2_get_extent(काष्ठा inode *inode, u64 lblock, u64 *dblock,
		    अचिन्हित पूर्णांक *extlen)
अणु
	अचिन्हित पूर्णांक blkbits = inode->i_blkbits;
	काष्ठा iomap iomap = अणु पूर्ण;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret;

	ret = gfs2_iomap_get(inode, lblock << blkbits, *extlen << blkbits,
			     &iomap);
	अगर (ret)
		वापस ret;
	अगर (iomap.type != IOMAP_MAPPED)
		वापस -EIO;
	*dblock = iomap.addr >> blkbits;
	len = iomap.length >> blkbits;
	अगर (len < *extlen)
		*extlen = len;
	वापस 0;
पूर्ण

पूर्णांक gfs2_alloc_extent(काष्ठा inode *inode, u64 lblock, u64 *dblock,
		      अचिन्हित पूर्णांक *extlen, bool *new)
अणु
	अचिन्हित पूर्णांक blkbits = inode->i_blkbits;
	काष्ठा iomap iomap = अणु पूर्ण;
	अचिन्हित पूर्णांक len;
	पूर्णांक ret;

	ret = gfs2_iomap_alloc(inode, lblock << blkbits, *extlen << blkbits,
			       &iomap);
	अगर (ret)
		वापस ret;
	अगर (iomap.type != IOMAP_MAPPED)
		वापस -EIO;
	*dblock = iomap.addr >> blkbits;
	len = iomap.length >> blkbits;
	अगर (len < *extlen)
		*extlen = len;
	*new = iomap.flags & IOMAP_F_NEW;
	वापस 0;
पूर्ण

/*
 * NOTE: Never call gfs2_block_zero_range with an खोलो transaction because it
 * uses iomap ग_लिखो to perक्रमm its actions, which begin their own transactions
 * (iomap_begin, page_prepare, etc.)
 */
अटल पूर्णांक gfs2_block_zero_range(काष्ठा inode *inode, loff_t from,
				 अचिन्हित पूर्णांक length)
अणु
	BUG_ON(current->journal_info);
	वापस iomap_zero_range(inode, from, length, शून्य, &gfs2_iomap_ops);
पूर्ण

#घोषणा GFS2_JTRUNC_REVOKES 8192

/**
 * gfs2_journaled_truncate - Wrapper क्रम truncate_pagecache क्रम jdata files
 * @inode: The inode being truncated
 * @oldsize: The original (larger) size
 * @newsize: The new smaller size
 *
 * With jdata files, we have to journal a revoke क्रम each block which is
 * truncated. As a result, we need to split this पूर्णांकo separate transactions
 * अगर the number of pages being truncated माला_लो too large.
 */

अटल पूर्णांक gfs2_journaled_truncate(काष्ठा inode *inode, u64 oldsize, u64 newsize)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	u64 max_chunk = GFS2_JTRUNC_REVOKES * sdp->sd_vfs->s_blocksize;
	u64 chunk;
	पूर्णांक error;

	जबतक (oldsize != newsize) अणु
		काष्ठा gfs2_trans *tr;
		अचिन्हित पूर्णांक offs;

		chunk = oldsize - newsize;
		अगर (chunk > max_chunk)
			chunk = max_chunk;

		offs = oldsize & ~PAGE_MASK;
		अगर (offs && chunk > PAGE_SIZE)
			chunk = offs + ((chunk - offs) & PAGE_MASK);

		truncate_pagecache(inode, oldsize - chunk);
		oldsize -= chunk;

		tr = current->journal_info;
		अगर (!test_bit(TR_TOUCHED, &tr->tr_flags))
			जारी;

		gfs2_trans_end(sdp);
		error = gfs2_trans_begin(sdp, RES_DINODE, GFS2_JTRUNC_REVOKES);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक trunc_start(काष्ठा inode *inode, u64 newsize)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा buffer_head *dibh = शून्य;
	पूर्णांक journaled = gfs2_is_jdata(ip);
	u64 oldsize = inode->i_size;
	पूर्णांक error;

	अगर (!gfs2_is_stuffed(ip)) अणु
		अचिन्हित पूर्णांक blocksize = i_blocksize(inode);
		अचिन्हित पूर्णांक offs = newsize & (blocksize - 1);
		अगर (offs) अणु
			error = gfs2_block_zero_range(inode, newsize,
						      blocksize - offs);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण
	अगर (journaled)
		error = gfs2_trans_begin(sdp, RES_DINODE + RES_JDATA, GFS2_JTRUNC_REVOKES);
	अन्यथा
		error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	अगर (error)
		वापस error;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error)
		जाओ out;

	gfs2_trans_add_meta(ip->i_gl, dibh);

	अगर (gfs2_is_stuffed(ip))
		gfs2_buffer_clear_tail(dibh, माप(काष्ठा gfs2_dinode) + newsize);
	अन्यथा
		ip->i_diskflags |= GFS2_DIF_TRUNC_IN_PROG;

	i_size_ग_लिखो(inode, newsize);
	ip->i_inode.i_mसमय = ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
	gfs2_dinode_out(ip, dibh->b_data);

	अगर (journaled)
		error = gfs2_journaled_truncate(inode, oldsize, newsize);
	अन्यथा
		truncate_pagecache(inode, newsize);

out:
	brअन्यथा(dibh);
	अगर (current->journal_info)
		gfs2_trans_end(sdp);
	वापस error;
पूर्ण

पूर्णांक gfs2_iomap_get(काष्ठा inode *inode, loff_t pos, loff_t length,
		   काष्ठा iomap *iomap)
अणु
	काष्ठा metapath mp = अणु .mp_aheight = 1, पूर्ण;
	पूर्णांक ret;

	ret = __gfs2_iomap_get(inode, pos, length, 0, iomap, &mp);
	release_metapath(&mp);
	वापस ret;
पूर्ण

पूर्णांक gfs2_iomap_alloc(काष्ठा inode *inode, loff_t pos, loff_t length,
		     काष्ठा iomap *iomap)
अणु
	काष्ठा metapath mp = अणु .mp_aheight = 1, पूर्ण;
	पूर्णांक ret;

	ret = __gfs2_iomap_get(inode, pos, length, IOMAP_WRITE, iomap, &mp);
	अगर (!ret && iomap->type == IOMAP_HOLE)
		ret = __gfs2_iomap_alloc(inode, iomap, &mp);
	release_metapath(&mp);
	वापस ret;
पूर्ण

/**
 * sweep_bh_क्रम_rgrps - find an rgrp in a meta buffer and मुक्त blocks therein
 * @ip: inode
 * @rd_gh: holder of resource group glock
 * @bh: buffer head to sweep
 * @start: starting poपूर्णांक in bh
 * @end: end poपूर्णांक in bh
 * @meta: true अगर bh poपूर्णांकs to metadata (rather than data)
 * @btotal: place to keep count of total blocks मुक्तd
 *
 * We sweep a metadata buffer (provided by the metapath) क्रम blocks we need to
 * मुक्त, and मुक्त them all. However, we करो it one rgrp at a समय. If this
 * block has references to multiple rgrps, we अवरोध it पूर्णांकo inभागidual
 * transactions. This allows other processes to use the rgrps जबतक we're
 * focused on a single one, क्रम better concurrency / perक्रमmance.
 * At every transaction boundary, we reग_लिखो the inode पूर्णांकo the journal.
 * That way the biपंचांगaps are kept consistent with the inode and we can recover
 * अगर we're पूर्णांकerrupted by घातer-outages.
 *
 * Returns: 0, or वापस code अगर an error occurred.
 *          *btotal has the total number of blocks मुक्तd
 */
अटल पूर्णांक sweep_bh_क्रम_rgrps(काष्ठा gfs2_inode *ip, काष्ठा gfs2_holder *rd_gh,
			      काष्ठा buffer_head *bh, __be64 *start, __be64 *end,
			      bool meta, u32 *btotal)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_rgrpd *rgd;
	काष्ठा gfs2_trans *tr;
	__be64 *p;
	पूर्णांक blks_outside_rgrp;
	u64 bn, bstart, isize_blks;
	s64 blen; /* needs to be s64 or gfs2_add_inode_blocks अवरोधs */
	पूर्णांक ret = 0;
	bool buf_in_tr = false; /* buffer was added to transaction */

more_rgrps:
	rgd = शून्य;
	अगर (gfs2_holder_initialized(rd_gh)) अणु
		rgd = gfs2_glock2rgrp(rd_gh->gh_gl);
		gfs2_निश्चित_withdraw(sdp,
			     gfs2_glock_is_locked_by_me(rd_gh->gh_gl));
	पूर्ण
	blks_outside_rgrp = 0;
	bstart = 0;
	blen = 0;

	क्रम (p = start; p < end; p++) अणु
		अगर (!*p)
			जारी;
		bn = be64_to_cpu(*p);

		अगर (rgd) अणु
			अगर (!rgrp_contains_block(rgd, bn)) अणु
				blks_outside_rgrp++;
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			rgd = gfs2_blk2rgrpd(sdp, bn, true);
			अगर (unlikely(!rgd)) अणु
				ret = -EIO;
				जाओ out;
			पूर्ण
			ret = gfs2_glock_nq_init(rgd->rd_gl, LM_ST_EXCLUSIVE,
						 LM_FLAG_NODE_SCOPE, rd_gh);
			अगर (ret)
				जाओ out;

			/* Must be करोne with the rgrp glock held: */
			अगर (gfs2_rs_active(&ip->i_res) &&
			    rgd == ip->i_res.rs_rgd)
				gfs2_rs_deltree(&ip->i_res);
		पूर्ण

		/* The size of our transactions will be unknown until we
		   actually process all the metadata blocks that relate to
		   the rgrp. So we estimate. We know it can't be more than
		   the dinode's i_blocks and we don't want to exceed the
		   journal flush threshold, sd_log_thresh2. */
		अगर (current->journal_info == शून्य) अणु
			अचिन्हित पूर्णांक jblocks_rqsted, revokes;

			jblocks_rqsted = rgd->rd_length + RES_DINODE +
				RES_INसूचीECT;
			isize_blks = gfs2_get_inode_blocks(&ip->i_inode);
			अगर (isize_blks > atomic_पढ़ो(&sdp->sd_log_thresh2))
				jblocks_rqsted +=
					atomic_पढ़ो(&sdp->sd_log_thresh2);
			अन्यथा
				jblocks_rqsted += isize_blks;
			revokes = jblocks_rqsted;
			अगर (meta)
				revokes += end - start;
			अन्यथा अगर (ip->i_depth)
				revokes += sdp->sd_inptrs;
			ret = gfs2_trans_begin(sdp, jblocks_rqsted, revokes);
			अगर (ret)
				जाओ out_unlock;
			करोwn_ग_लिखो(&ip->i_rw_mutex);
		पूर्ण
		/* check अगर we will exceed the transaction blocks requested */
		tr = current->journal_info;
		अगर (tr->tr_num_buf_new + RES_STATFS +
		    RES_QUOTA >= atomic_पढ़ो(&sdp->sd_log_thresh2)) अणु
			/* We set blks_outside_rgrp to ensure the loop will
			   be repeated क्रम the same rgrp, but with a new
			   transaction. */
			blks_outside_rgrp++;
			/* This next part is tricky. If the buffer was added
			   to the transaction, we've alपढ़ोy set some block
			   poपूर्णांकers to 0, so we better follow through and मुक्त
			   them, or we will पूर्णांकroduce corruption (so अवरोध).
			   This may be impossible, or at least rare, but I
			   decided to cover the हाल regardless.

			   If the buffer was not added to the transaction
			   (this call), करोing so would exceed our transaction
			   size, so we need to end the transaction and start a
			   new one (so जाओ). */

			अगर (buf_in_tr)
				अवरोध;
			जाओ out_unlock;
		पूर्ण

		gfs2_trans_add_meta(ip->i_gl, bh);
		buf_in_tr = true;
		*p = 0;
		अगर (bstart + blen == bn) अणु
			blen++;
			जारी;
		पूर्ण
		अगर (bstart) अणु
			__gfs2_मुक्त_blocks(ip, rgd, bstart, (u32)blen, meta);
			(*btotal) += blen;
			gfs2_add_inode_blocks(&ip->i_inode, -blen);
		पूर्ण
		bstart = bn;
		blen = 1;
	पूर्ण
	अगर (bstart) अणु
		__gfs2_मुक्त_blocks(ip, rgd, bstart, (u32)blen, meta);
		(*btotal) += blen;
		gfs2_add_inode_blocks(&ip->i_inode, -blen);
	पूर्ण
out_unlock:
	अगर (!ret && blks_outside_rgrp) अणु /* If buffer still has non-zero blocks
					    outside the rgrp we just processed,
					    करो it all over again. */
		अगर (current->journal_info) अणु
			काष्ठा buffer_head *dibh;

			ret = gfs2_meta_inode_buffer(ip, &dibh);
			अगर (ret)
				जाओ out;

			/* Every transaction boundary, we reग_लिखो the dinode
			   to keep its di_blocks current in हाल of failure. */
			ip->i_inode.i_mसमय = ip->i_inode.i_स_समय =
				current_समय(&ip->i_inode);
			gfs2_trans_add_meta(ip->i_gl, dibh);
			gfs2_dinode_out(ip, dibh->b_data);
			brअन्यथा(dibh);
			up_ग_लिखो(&ip->i_rw_mutex);
			gfs2_trans_end(sdp);
			buf_in_tr = false;
		पूर्ण
		gfs2_glock_dq_uninit(rd_gh);
		cond_resched();
		जाओ more_rgrps;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल bool mp_eq_to_hgt(काष्ठा metapath *mp, __u16 *list, अचिन्हित पूर्णांक h)
अणु
	अगर (स_भेद(mp->mp_list, list, h * माप(mp->mp_list[0])))
		वापस false;
	वापस true;
पूर्ण

/**
 * find_nonnull_ptr - find a non-null poपूर्णांकer given a metapath and height
 * @sdp: The superblock
 * @mp: starting metapath
 * @h: desired height to search
 * @end_list: See punch_hole().
 * @end_aligned: See punch_hole().
 *
 * Assumes the metapath is valid (with buffers) out to height h.
 * Returns: true अगर a non-null poपूर्णांकer was found in the metapath buffer
 *          false अगर all reमुख्यing poपूर्णांकers are शून्य in the buffer
 */
अटल bool find_nonnull_ptr(काष्ठा gfs2_sbd *sdp, काष्ठा metapath *mp,
			     अचिन्हित पूर्णांक h,
			     __u16 *end_list, अचिन्हित पूर्णांक end_aligned)
अणु
	काष्ठा buffer_head *bh = mp->mp_bh[h];
	__be64 *first, *ptr, *end;

	first = metaptr1(h, mp);
	ptr = first + mp->mp_list[h];
	end = (__be64 *)(bh->b_data + bh->b_size);
	अगर (end_list && mp_eq_to_hgt(mp, end_list, h)) अणु
		bool keep_end = h < end_aligned;
		end = first + end_list[h] + keep_end;
	पूर्ण

	जबतक (ptr < end) अणु
		अगर (*ptr) अणु /* अगर we have a non-null poपूर्णांकer */
			mp->mp_list[h] = ptr - first;
			h++;
			अगर (h < GFS2_MAX_META_HEIGHT)
				mp->mp_list[h] = 0;
			वापस true;
		पूर्ण
		ptr++;
	पूर्ण
	वापस false;
पूर्ण

क्रमागत dealloc_states अणु
	DEALLOC_MP_FULL = 0,    /* Strip a metapath with all buffers पढ़ो in */
	DEALLOC_MP_LOWER = 1,   /* lower the metapath strip height */
	DEALLOC_FILL_MP = 2,  /* Fill in the metapath to the given height. */
	DEALLOC_DONE = 3,       /* process complete */
पूर्ण;

अटल अंतरभूत व्योम
metapoपूर्णांकer_range(काष्ठा metapath *mp, पूर्णांक height,
		  __u16 *start_list, अचिन्हित पूर्णांक start_aligned,
		  __u16 *end_list, अचिन्हित पूर्णांक end_aligned,
		  __be64 **start, __be64 **end)
अणु
	काष्ठा buffer_head *bh = mp->mp_bh[height];
	__be64 *first;

	first = metaptr1(height, mp);
	*start = first;
	अगर (mp_eq_to_hgt(mp, start_list, height)) अणु
		bool keep_start = height < start_aligned;
		*start = first + start_list[height] + keep_start;
	पूर्ण
	*end = (__be64 *)(bh->b_data + bh->b_size);
	अगर (end_list && mp_eq_to_hgt(mp, end_list, height)) अणु
		bool keep_end = height < end_aligned;
		*end = first + end_list[height] + keep_end;
	पूर्ण
पूर्ण

अटल अंतरभूत bool walk_करोne(काष्ठा gfs2_sbd *sdp,
			     काष्ठा metapath *mp, पूर्णांक height,
			     __u16 *end_list, अचिन्हित पूर्णांक end_aligned)
अणु
	__u16 end;

	अगर (end_list) अणु
		bool keep_end = height < end_aligned;
		अगर (!mp_eq_to_hgt(mp, end_list, height))
			वापस false;
		end = end_list[height] + keep_end;
	पूर्ण अन्यथा
		end = (height > 0) ? sdp->sd_inptrs : sdp->sd_diptrs;
	वापस mp->mp_list[height] >= end;
पूर्ण

/**
 * punch_hole - deallocate blocks in a file
 * @ip: inode to truncate
 * @offset: the start of the hole
 * @length: the size of the hole (or 0 क्रम truncate)
 *
 * Punch a hole पूर्णांकo a file or truncate a file at a given position.  This
 * function operates in whole blocks (@offset and @length are rounded
 * accordingly); partially filled blocks must be cleared otherwise.
 *
 * This function works from the bottom up, and from the right to the left. In
 * other words, it strips off the highest layer (data) beक्रमe stripping any of
 * the metadata. Doing it this way is best in हाल the operation is पूर्णांकerrupted
 * by घातer failure, etc.  The dinode is rewritten in every transaction to
 * guarantee पूर्णांकegrity.
 */
अटल पूर्णांक punch_hole(काष्ठा gfs2_inode *ip, u64 offset, u64 length)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	u64 maxsize = sdp->sd_heightsize[ip->i_height];
	काष्ठा metapath mp = अणुपूर्ण;
	काष्ठा buffer_head *dibh, *bh;
	काष्ठा gfs2_holder rd_gh;
	अचिन्हित पूर्णांक bsize_shअगरt = sdp->sd_sb.sb_bsize_shअगरt;
	u64 lblock = (offset + (1 << bsize_shअगरt) - 1) >> bsize_shअगरt;
	__u16 start_list[GFS2_MAX_META_HEIGHT];
	__u16 __end_list[GFS2_MAX_META_HEIGHT], *end_list = शून्य;
	अचिन्हित पूर्णांक start_aligned, end_aligned;
	अचिन्हित पूर्णांक strip_h = ip->i_height - 1;
	u32 btotal = 0;
	पूर्णांक ret, state;
	पूर्णांक mp_h; /* metapath buffers are पढ़ो in to this height */
	u64 prev_bnr = 0;
	__be64 *start, *end;

	अगर (offset >= maxsize) अणु
		/*
		 * The starting poपूर्णांक lies beyond the allocated meta-data;
		 * there are no blocks करो deallocate.
		 */
		वापस 0;
	पूर्ण

	/*
	 * The start position of the hole is defined by lblock, start_list, and
	 * start_aligned.  The end position of the hole is defined by lend,
	 * end_list, and end_aligned.
	 *
	 * start_aligned and end_aligned define करोwn to which height the start
	 * and end positions are aligned to the metadata tree (i.e., the
	 * position is a multiple of the metadata granularity at the height
	 * above).  This determines at which heights additional meta poपूर्णांकers
	 * needs to be preserved क्रम the reमुख्यing data.
	 */

	अगर (length) अणु
		u64 end_offset = offset + length;
		u64 lend;

		/*
		 * Clip the end at the maximum file size क्रम the given height:
		 * that's how far the metadata goes; files bigger than that
		 * will have additional layers of indirection.
		 */
		अगर (end_offset > maxsize)
			end_offset = maxsize;
		lend = end_offset >> bsize_shअगरt;

		अगर (lblock >= lend)
			वापस 0;

		find_metapath(sdp, lend, &mp, ip->i_height);
		end_list = __end_list;
		स_नकल(end_list, mp.mp_list, माप(mp.mp_list));

		क्रम (mp_h = ip->i_height - 1; mp_h > 0; mp_h--) अणु
			अगर (end_list[mp_h])
				अवरोध;
		पूर्ण
		end_aligned = mp_h;
	पूर्ण

	find_metapath(sdp, lblock, &mp, ip->i_height);
	स_नकल(start_list, mp.mp_list, माप(start_list));

	क्रम (mp_h = ip->i_height - 1; mp_h > 0; mp_h--) अणु
		अगर (start_list[mp_h])
			अवरोध;
	पूर्ण
	start_aligned = mp_h;

	ret = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (ret)
		वापस ret;

	mp.mp_bh[0] = dibh;
	ret = lookup_metapath(ip, &mp);
	अगर (ret)
		जाओ out_metapath;

	/* issue पढ़ो-ahead on metadata */
	क्रम (mp_h = 0; mp_h < mp.mp_aheight - 1; mp_h++) अणु
		metapoपूर्णांकer_range(&mp, mp_h, start_list, start_aligned,
				  end_list, end_aligned, &start, &end);
		gfs2_metapath_ra(ip->i_gl, start, end);
	पूर्ण

	अगर (mp.mp_aheight == ip->i_height)
		state = DEALLOC_MP_FULL; /* We have a complete metapath */
	अन्यथा
		state = DEALLOC_FILL_MP; /* deal with partial metapath */

	ret = gfs2_rindex_update(sdp);
	अगर (ret)
		जाओ out_metapath;

	ret = gfs2_quota_hold(ip, NO_UID_QUOTA_CHANGE, NO_GID_QUOTA_CHANGE);
	अगर (ret)
		जाओ out_metapath;
	gfs2_holder_mark_uninitialized(&rd_gh);

	mp_h = strip_h;

	जबतक (state != DEALLOC_DONE) अणु
		चयन (state) अणु
		/* Truncate a full metapath at the given strip height.
		 * Note that strip_h == mp_h in order to be in this state. */
		हाल DEALLOC_MP_FULL:
			bh = mp.mp_bh[mp_h];
			gfs2_निश्चित_withdraw(sdp, bh);
			अगर (gfs2_निश्चित_withdraw(sdp,
						 prev_bnr != bh->b_blocknr)) अणु
				fs_emerg(sdp, "inode %llu, block:%llu, i_h:%u,"
					 "s_h:%u, mp_h:%u\n",
				       (अचिन्हित दीर्घ दीर्घ)ip->i_no_addr,
				       prev_bnr, ip->i_height, strip_h, mp_h);
			पूर्ण
			prev_bnr = bh->b_blocknr;

			अगर (gfs2_metatype_check(sdp, bh,
						(mp_h ? GFS2_METATYPE_IN :
							GFS2_METATYPE_DI))) अणु
				ret = -EIO;
				जाओ out;
			पूर्ण

			/*
			 * Below, passing end_aligned as 0 gives us the
			 * metapoपूर्णांकer range excluding the end poपूर्णांक: the end
			 * poपूर्णांक is the first metapath we must not deallocate!
			 */

			metapoपूर्णांकer_range(&mp, mp_h, start_list, start_aligned,
					  end_list, 0 /* end_aligned */,
					  &start, &end);
			ret = sweep_bh_क्रम_rgrps(ip, &rd_gh, mp.mp_bh[mp_h],
						 start, end,
						 mp_h != ip->i_height - 1,
						 &btotal);

			/* If we hit an error or just swept dinode buffer,
			   just निकास. */
			अगर (ret || !mp_h) अणु
				state = DEALLOC_DONE;
				अवरोध;
			पूर्ण
			state = DEALLOC_MP_LOWER;
			अवरोध;

		/* lower the metapath strip height */
		हाल DEALLOC_MP_LOWER:
			/* We're करोne with the current buffer, so release it,
			   unless it's the dinode buffer. Then back up to the
			   previous poपूर्णांकer. */
			अगर (mp_h) अणु
				brअन्यथा(mp.mp_bh[mp_h]);
				mp.mp_bh[mp_h] = शून्य;
			पूर्ण
			/* If we can't get any lower in height, we've stripped
			   off all we can. Next step is to back up and start
			   stripping the previous level of metadata. */
			अगर (mp_h == 0) अणु
				strip_h--;
				स_नकल(mp.mp_list, start_list, माप(start_list));
				mp_h = strip_h;
				state = DEALLOC_FILL_MP;
				अवरोध;
			पूर्ण
			mp.mp_list[mp_h] = 0;
			mp_h--; /* search one metadata height करोwn */
			mp.mp_list[mp_h]++;
			अगर (walk_करोne(sdp, &mp, mp_h, end_list, end_aligned))
				अवरोध;
			/* Here we've found a part of the metapath that is not
			 * allocated. We need to search at that height क्रम the
			 * next non-null poपूर्णांकer. */
			अगर (find_nonnull_ptr(sdp, &mp, mp_h, end_list, end_aligned)) अणु
				state = DEALLOC_FILL_MP;
				mp_h++;
			पूर्ण
			/* No more non-null poपूर्णांकers at this height. Back up
			   to the previous height and try again. */
			अवरोध; /* loop around in the same state */

		/* Fill the metapath with buffers to the given height. */
		हाल DEALLOC_FILL_MP:
			/* Fill the buffers out to the current height. */
			ret = fillup_metapath(ip, &mp, mp_h);
			अगर (ret < 0)
				जाओ out;

			/* On the first pass, issue पढ़ो-ahead on metadata. */
			अगर (mp.mp_aheight > 1 && strip_h == ip->i_height - 1) अणु
				अचिन्हित पूर्णांक height = mp.mp_aheight - 1;

				/* No पढ़ो-ahead क्रम data blocks. */
				अगर (mp.mp_aheight - 1 == strip_h)
					height--;

				क्रम (; height >= mp.mp_aheight - ret; height--) अणु
					metapoपूर्णांकer_range(&mp, height,
							  start_list, start_aligned,
							  end_list, end_aligned,
							  &start, &end);
					gfs2_metapath_ra(ip->i_gl, start, end);
				पूर्ण
			पूर्ण

			/* If buffers found क्रम the entire strip height */
			अगर (mp.mp_aheight - 1 == strip_h) अणु
				state = DEALLOC_MP_FULL;
				अवरोध;
			पूर्ण
			अगर (mp.mp_aheight < ip->i_height) /* We have a partial height */
				mp_h = mp.mp_aheight - 1;

			/* If we find a non-null block poपूर्णांकer, crawl a bit
			   higher up in the metapath and try again, otherwise
			   we need to look lower क्रम a new starting poपूर्णांक. */
			अगर (find_nonnull_ptr(sdp, &mp, mp_h, end_list, end_aligned))
				mp_h++;
			अन्यथा
				state = DEALLOC_MP_LOWER;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (btotal) अणु
		अगर (current->journal_info == शून्य) अणु
			ret = gfs2_trans_begin(sdp, RES_DINODE + RES_STATFS +
					       RES_QUOTA, 0);
			अगर (ret)
				जाओ out;
			करोwn_ग_लिखो(&ip->i_rw_mutex);
		पूर्ण
		gfs2_statfs_change(sdp, 0, +btotal, 0);
		gfs2_quota_change(ip, -(s64)btotal, ip->i_inode.i_uid,
				  ip->i_inode.i_gid);
		ip->i_inode.i_mसमय = ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
		gfs2_trans_add_meta(ip->i_gl, dibh);
		gfs2_dinode_out(ip, dibh->b_data);
		up_ग_लिखो(&ip->i_rw_mutex);
		gfs2_trans_end(sdp);
	पूर्ण

out:
	अगर (gfs2_holder_initialized(&rd_gh))
		gfs2_glock_dq_uninit(&rd_gh);
	अगर (current->journal_info) अणु
		up_ग_लिखो(&ip->i_rw_mutex);
		gfs2_trans_end(sdp);
		cond_resched();
	पूर्ण
	gfs2_quota_unhold(ip);
out_metapath:
	release_metapath(&mp);
	वापस ret;
पूर्ण

अटल पूर्णांक trunc_end(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा buffer_head *dibh;
	पूर्णांक error;

	error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	अगर (error)
		वापस error;

	करोwn_ग_लिखो(&ip->i_rw_mutex);

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error)
		जाओ out;

	अगर (!i_size_पढ़ो(&ip->i_inode)) अणु
		ip->i_height = 0;
		ip->i_goal = ip->i_no_addr;
		gfs2_buffer_clear_tail(dibh, माप(काष्ठा gfs2_dinode));
		gfs2_ordered_del_inode(ip);
	पूर्ण
	ip->i_inode.i_mसमय = ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
	ip->i_diskflags &= ~GFS2_DIF_TRUNC_IN_PROG;

	gfs2_trans_add_meta(ip->i_gl, dibh);
	gfs2_dinode_out(ip, dibh->b_data);
	brअन्यथा(dibh);

out:
	up_ग_लिखो(&ip->i_rw_mutex);
	gfs2_trans_end(sdp);
	वापस error;
पूर्ण

/**
 * करो_shrink - make a file smaller
 * @inode: the inode
 * @newsize: the size to make the file
 *
 * Called with an exclusive lock on @inode. The @size must
 * be equal to or smaller than the current inode size.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक करो_shrink(काष्ठा inode *inode, u64 newsize)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	पूर्णांक error;

	error = trunc_start(inode, newsize);
	अगर (error < 0)
		वापस error;
	अगर (gfs2_is_stuffed(ip))
		वापस 0;

	error = punch_hole(ip, newsize, 0);
	अगर (error == 0)
		error = trunc_end(ip);

	वापस error;
पूर्ण

व्योम gfs2_trim_blocks(काष्ठा inode *inode)
अणु
	पूर्णांक ret;

	ret = करो_shrink(inode, inode->i_size);
	WARN_ON(ret != 0);
पूर्ण

/**
 * करो_grow - Touch and update inode size
 * @inode: The inode
 * @size: The new size
 *
 * This function updates the बारtamps on the inode and
 * may also increase the size of the inode. This function
 * must not be called with @size any smaller than the current
 * inode size.
 *
 * Although it is not strictly required to unstuff files here,
 * earlier versions of GFS2 have a bug in the stuffed file पढ़ोing
 * code which will result in a buffer overrun अगर the size is larger
 * than the max stuffed file size. In order to prevent this from
 * occurring, such files are unstuffed, but in other हालs we can
 * just update the inode size directly.
 *
 * Returns: 0 on success, or -ve on error
 */

अटल पूर्णांक करो_grow(काष्ठा inode *inode, u64 size)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_alloc_parms ap = अणु .target = 1, पूर्ण;
	काष्ठा buffer_head *dibh;
	पूर्णांक error;
	पूर्णांक unstuff = 0;

	अगर (gfs2_is_stuffed(ip) && size > gfs2_max_stuffed_size(ip)) अणु
		error = gfs2_quota_lock_check(ip, &ap);
		अगर (error)
			वापस error;

		error = gfs2_inplace_reserve(ip, &ap);
		अगर (error)
			जाओ करो_grow_qunlock;
		unstuff = 1;
	पूर्ण

	error = gfs2_trans_begin(sdp, RES_DINODE + RES_STATFS + RES_RG_BIT +
				 (unstuff &&
				  gfs2_is_jdata(ip) ? RES_JDATA : 0) +
				 (sdp->sd_args.ar_quota == GFS2_QUOTA_OFF ?
				  0 : RES_QUOTA), 0);
	अगर (error)
		जाओ करो_grow_release;

	अगर (unstuff) अणु
		error = gfs2_unstuff_dinode(ip, शून्य);
		अगर (error)
			जाओ करो_end_trans;
	पूर्ण

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error)
		जाओ करो_end_trans;

	truncate_setsize(inode, size);
	ip->i_inode.i_mसमय = ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
	gfs2_trans_add_meta(ip->i_gl, dibh);
	gfs2_dinode_out(ip, dibh->b_data);
	brअन्यथा(dibh);

करो_end_trans:
	gfs2_trans_end(sdp);
करो_grow_release:
	अगर (unstuff) अणु
		gfs2_inplace_release(ip);
करो_grow_qunlock:
		gfs2_quota_unlock(ip);
	पूर्ण
	वापस error;
पूर्ण

/**
 * gfs2_setattr_size - make a file a given size
 * @inode: the inode
 * @newsize: the size to make the file
 *
 * The file size can grow, shrink, or stay the same size. This
 * is called holding i_rwsem and an exclusive glock on the inode
 * in question.
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_setattr_size(काष्ठा inode *inode, u64 newsize)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	पूर्णांक ret;

	BUG_ON(!S_ISREG(inode->i_mode));

	ret = inode_newsize_ok(inode, newsize);
	अगर (ret)
		वापस ret;

	inode_dio_रुको(inode);

	ret = gfs2_qa_get(ip);
	अगर (ret)
		जाओ out;

	अगर (newsize >= inode->i_size) अणु
		ret = करो_grow(inode, newsize);
		जाओ out;
	पूर्ण

	ret = करो_shrink(inode, newsize);
out:
	gfs2_rs_delete(ip, शून्य);
	gfs2_qa_put(ip);
	वापस ret;
पूर्ण

पूर्णांक gfs2_truncatei_resume(काष्ठा gfs2_inode *ip)
अणु
	पूर्णांक error;
	error = punch_hole(ip, i_size_पढ़ो(&ip->i_inode), 0);
	अगर (!error)
		error = trunc_end(ip);
	वापस error;
पूर्ण

पूर्णांक gfs2_file_dealloc(काष्ठा gfs2_inode *ip)
अणु
	वापस punch_hole(ip, 0, 0);
पूर्ण

/**
 * gfs2_मुक्त_journal_extents - Free cached journal bmap info
 * @jd: The journal
 *
 */

व्योम gfs2_मुक्त_journal_extents(काष्ठा gfs2_jdesc *jd)
अणु
	काष्ठा gfs2_journal_extent *jext;

	जबतक(!list_empty(&jd->extent_list)) अणु
		jext = list_first_entry(&jd->extent_list, काष्ठा gfs2_journal_extent, list);
		list_del(&jext->list);
		kमुक्त(jext);
	पूर्ण
पूर्ण

/**
 * gfs2_add_jextent - Add or merge a new extent to extent cache
 * @jd: The journal descriptor
 * @lblock: The logical block at start of new extent
 * @dblock: The physical block at start of new extent
 * @blocks: Size of extent in fs blocks
 *
 * Returns: 0 on success or -ENOMEM
 */

अटल पूर्णांक gfs2_add_jextent(काष्ठा gfs2_jdesc *jd, u64 lblock, u64 dblock, u64 blocks)
अणु
	काष्ठा gfs2_journal_extent *jext;

	अगर (!list_empty(&jd->extent_list)) अणु
		jext = list_last_entry(&jd->extent_list, काष्ठा gfs2_journal_extent, list);
		अगर ((jext->dblock + jext->blocks) == dblock) अणु
			jext->blocks += blocks;
			वापस 0;
		पूर्ण
	पूर्ण

	jext = kzalloc(माप(काष्ठा gfs2_journal_extent), GFP_NOFS);
	अगर (jext == शून्य)
		वापस -ENOMEM;
	jext->dblock = dblock;
	jext->lblock = lblock;
	jext->blocks = blocks;
	list_add_tail(&jext->list, &jd->extent_list);
	jd->nr_extents++;
	वापस 0;
पूर्ण

/**
 * gfs2_map_journal_extents - Cache journal bmap info
 * @sdp: The super block
 * @jd: The journal to map
 *
 * Create a reusable "extent" mapping from all logical
 * blocks to all physical blocks क्रम the given journal.  This will save
 * us समय when writing journal blocks.  Most journals will have only one
 * extent that maps all their logical blocks.  That's because gfs2.mkfs
 * arranges the journal blocks sequentially to maximize perक्रमmance.
 * So the extent would map the first block क्रम the entire file length.
 * However, gfs2_jadd can happen जबतक file activity is happening, so
 * those journals may not be sequential.  Less likely is the हाल where
 * the users created their own journals by mounting the metafs and
 * laying it out.  But it's still possible.  These journals might have
 * several extents.
 *
 * Returns: 0 on success, or error on failure
 */

पूर्णांक gfs2_map_journal_extents(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_jdesc *jd)
अणु
	u64 lblock = 0;
	u64 lblock_stop;
	काष्ठा gfs2_inode *ip = GFS2_I(jd->jd_inode);
	काष्ठा buffer_head bh;
	अचिन्हित पूर्णांक shअगरt = sdp->sd_sb.sb_bsize_shअगरt;
	u64 size;
	पूर्णांक rc;
	kसमय_प्रकार start, end;

	start = kसमय_get();
	lblock_stop = i_size_पढ़ो(jd->jd_inode) >> shअगरt;
	size = (lblock_stop - lblock) << shअगरt;
	jd->nr_extents = 0;
	WARN_ON(!list_empty(&jd->extent_list));

	करो अणु
		bh.b_state = 0;
		bh.b_blocknr = 0;
		bh.b_size = size;
		rc = gfs2_block_map(jd->jd_inode, lblock, &bh, 0);
		अगर (rc || !buffer_mapped(&bh))
			जाओ fail;
		rc = gfs2_add_jextent(jd, lblock, bh.b_blocknr, bh.b_size >> shअगरt);
		अगर (rc)
			जाओ fail;
		size -= bh.b_size;
		lblock += (bh.b_size >> ip->i_inode.i_blkbits);
	पूर्ण जबतक(size > 0);

	end = kसमय_get();
	fs_info(sdp, "journal %d mapped with %u extents in %lldms\n", jd->jd_jid,
		jd->nr_extents, kसमय_ms_delta(end, start));
	वापस 0;

fail:
	fs_warn(sdp, "error %d mapping journal %u at offset %llu (extent %u)\n",
		rc, jd->jd_jid,
		(अचिन्हित दीर्घ दीर्घ)(i_size_पढ़ो(jd->jd_inode) - size),
		jd->nr_extents);
	fs_warn(sdp, "bmap=%d lblock=%llu block=%llu, state=0x%08lx, size=%llu\n",
		rc, (अचिन्हित दीर्घ दीर्घ)lblock, (अचिन्हित दीर्घ दीर्घ)bh.b_blocknr,
		bh.b_state, (अचिन्हित दीर्घ दीर्घ)bh.b_size);
	gfs2_मुक्त_journal_extents(jd);
	वापस rc;
पूर्ण

/**
 * gfs2_ग_लिखो_alloc_required - figure out अगर a ग_लिखो will require an allocation
 * @ip: the file being written to
 * @offset: the offset to ग_लिखो to
 * @len: the number of bytes being written
 *
 * Returns: 1 अगर an alloc is required, 0 otherwise
 */

पूर्णांक gfs2_ग_लिखो_alloc_required(काष्ठा gfs2_inode *ip, u64 offset,
			      अचिन्हित पूर्णांक len)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा buffer_head bh;
	अचिन्हित पूर्णांक shअगरt;
	u64 lblock, lblock_stop, size;
	u64 end_of_file;

	अगर (!len)
		वापस 0;

	अगर (gfs2_is_stuffed(ip)) अणु
		अगर (offset + len > gfs2_max_stuffed_size(ip))
			वापस 1;
		वापस 0;
	पूर्ण

	shअगरt = sdp->sd_sb.sb_bsize_shअगरt;
	BUG_ON(gfs2_is_dir(ip));
	end_of_file = (i_size_पढ़ो(&ip->i_inode) + sdp->sd_sb.sb_bsize - 1) >> shअगरt;
	lblock = offset >> shअगरt;
	lblock_stop = (offset + len + sdp->sd_sb.sb_bsize - 1) >> shअगरt;
	अगर (lblock_stop > end_of_file && ip != GFS2_I(sdp->sd_rindex))
		वापस 1;

	size = (lblock_stop - lblock) << shअगरt;
	करो अणु
		bh.b_state = 0;
		bh.b_size = size;
		gfs2_block_map(&ip->i_inode, lblock, &bh, 0);
		अगर (!buffer_mapped(&bh))
			वापस 1;
		size -= bh.b_size;
		lblock += (bh.b_size >> ip->i_inode.i_blkbits);
	पूर्ण जबतक(size > 0);

	वापस 0;
पूर्ण

अटल पूर्णांक stuffed_zero_range(काष्ठा inode *inode, loff_t offset, loff_t length)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा buffer_head *dibh;
	पूर्णांक error;

	अगर (offset >= inode->i_size)
		वापस 0;
	अगर (offset + length > inode->i_size)
		length = inode->i_size - offset;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error)
		वापस error;
	gfs2_trans_add_meta(ip->i_gl, dibh);
	स_रखो(dibh->b_data + माप(काष्ठा gfs2_dinode) + offset, 0,
	       length);
	brअन्यथा(dibh);
	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_journaled_truncate_range(काष्ठा inode *inode, loff_t offset,
					 loff_t length)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	loff_t max_chunk = GFS2_JTRUNC_REVOKES * sdp->sd_vfs->s_blocksize;
	पूर्णांक error;

	जबतक (length) अणु
		काष्ठा gfs2_trans *tr;
		loff_t chunk;
		अचिन्हित पूर्णांक offs;

		chunk = length;
		अगर (chunk > max_chunk)
			chunk = max_chunk;

		offs = offset & ~PAGE_MASK;
		अगर (offs && chunk > PAGE_SIZE)
			chunk = offs + ((chunk - offs) & PAGE_MASK);

		truncate_pagecache_range(inode, offset, chunk);
		offset += chunk;
		length -= chunk;

		tr = current->journal_info;
		अगर (!test_bit(TR_TOUCHED, &tr->tr_flags))
			जारी;

		gfs2_trans_end(sdp);
		error = gfs2_trans_begin(sdp, RES_DINODE, GFS2_JTRUNC_REVOKES);
		अगर (error)
			वापस error;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __gfs2_punch_hole(काष्ठा file *file, loff_t offset, loff_t length)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	अचिन्हित पूर्णांक blocksize = i_blocksize(inode);
	loff_t start, end;
	पूर्णांक error;

	अगर (!gfs2_is_stuffed(ip)) अणु
		अचिन्हित पूर्णांक start_off, end_len;

		start_off = offset & (blocksize - 1);
		end_len = (offset + length) & (blocksize - 1);
		अगर (start_off) अणु
			अचिन्हित पूर्णांक len = length;
			अगर (length > blocksize - start_off)
				len = blocksize - start_off;
			error = gfs2_block_zero_range(inode, offset, len);
			अगर (error)
				जाओ out;
			अगर (start_off + length < blocksize)
				end_len = 0;
		पूर्ण
		अगर (end_len) अणु
			error = gfs2_block_zero_range(inode,
				offset + length - end_len, end_len);
			अगर (error)
				जाओ out;
		पूर्ण
	पूर्ण

	start = round_करोwn(offset, blocksize);
	end = round_up(offset + length, blocksize) - 1;
	error = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, start, end);
	अगर (error)
		वापस error;

	अगर (gfs2_is_jdata(ip))
		error = gfs2_trans_begin(sdp, RES_DINODE + 2 * RES_JDATA,
					 GFS2_JTRUNC_REVOKES);
	अन्यथा
		error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	अगर (error)
		वापस error;

	अगर (gfs2_is_stuffed(ip)) अणु
		error = stuffed_zero_range(inode, offset, length);
		अगर (error)
			जाओ out;
	पूर्ण

	अगर (gfs2_is_jdata(ip)) अणु
		BUG_ON(!current->journal_info);
		gfs2_journaled_truncate_range(inode, offset, length);
	पूर्ण अन्यथा
		truncate_pagecache_range(inode, offset, offset + length - 1);

	file_update_समय(file);
	mark_inode_dirty(inode);

	अगर (current->journal_info)
		gfs2_trans_end(sdp);

	अगर (!gfs2_is_stuffed(ip))
		error = punch_hole(ip, offset, length);

out:
	अगर (current->journal_info)
		gfs2_trans_end(sdp);
	वापस error;
पूर्ण

अटल पूर्णांक gfs2_map_blocks(काष्ठा iomap_ग_लिखोpage_ctx *wpc, काष्ठा inode *inode,
		loff_t offset)
अणु
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(gfs2_is_stuffed(GFS2_I(inode))))
		वापस -EIO;

	अगर (offset >= wpc->iomap.offset &&
	    offset < wpc->iomap.offset + wpc->iomap.length)
		वापस 0;

	स_रखो(&wpc->iomap, 0, माप(wpc->iomap));
	ret = gfs2_iomap_get(inode, offset, पूर्णांक_उच्च, &wpc->iomap);
	वापस ret;
पूर्ण

स्थिर काष्ठा iomap_ग_लिखोback_ops gfs2_ग_लिखोback_ops = अणु
	.map_blocks		= gfs2_map_blocks,
पूर्ण;
