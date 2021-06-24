<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/fs.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/अक्रमom.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "lops.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "rgrp.h"
#समावेश "super.h"
#समावेश "trans.h"
#समावेश "util.h"
#समावेश "log.h"
#समावेश "inode.h"
#समावेश "trace_gfs2.h"
#समावेश "dir.h"

#घोषणा BFITNOENT ((u32)~0)
#घोषणा NO_BLOCK ((u64)~0)

काष्ठा gfs2_rbm अणु
	काष्ठा gfs2_rgrpd *rgd;
	u32 offset;		/* The offset is biपंचांगap relative */
	पूर्णांक bii;		/* Biपंचांगap index */
पूर्ण;

अटल अंतरभूत काष्ठा gfs2_biपंचांगap *rbm_bi(स्थिर काष्ठा gfs2_rbm *rbm)
अणु
	वापस rbm->rgd->rd_bits + rbm->bii;
पूर्ण

अटल अंतरभूत u64 gfs2_rbm_to_block(स्थिर काष्ठा gfs2_rbm *rbm)
अणु
	BUG_ON(rbm->offset >= rbm->rgd->rd_data);
	वापस rbm->rgd->rd_data0 + (rbm_bi(rbm)->bi_start * GFS2_NBBY) +
		rbm->offset;
पूर्ण

/*
 * These routines are used by the resource group routines (rgrp.c)
 * to keep track of block allocation.  Each block is represented by two
 * bits.  So, each byte represents GFS2_NBBY (i.e. 4) blocks.
 *
 * 0 = Free
 * 1 = Used (not metadata)
 * 2 = Unlinked (still in use) inode
 * 3 = Used (metadata)
 */

काष्ठा gfs2_extent अणु
	काष्ठा gfs2_rbm rbm;
	u32 len;
पूर्ण;

अटल स्थिर अक्षर valid_change[16] = अणु
	        /* current */
	/* n */ 0, 1, 1, 1,
	/* e */ 1, 0, 0, 0,
	/* w */ 0, 0, 0, 1,
	        1, 0, 0, 0
पूर्ण;

अटल पूर्णांक gfs2_rbm_find(काष्ठा gfs2_rbm *rbm, u8 state, u32 *minext,
			 काष्ठा gfs2_blkreserv *rs, bool nowrap);


/**
 * gfs2_setbit - Set a bit in the biपंचांगaps
 * @rbm: The position of the bit to set
 * @करो_clone: Also set the clone biपंचांगap, अगर it exists
 * @new_state: the new state of the block
 *
 */

अटल अंतरभूत व्योम gfs2_setbit(स्थिर काष्ठा gfs2_rbm *rbm, bool करो_clone,
			       अचिन्हित अक्षर new_state)
अणु
	अचिन्हित अक्षर *byte1, *byte2, *end, cur_state;
	काष्ठा gfs2_biपंचांगap *bi = rbm_bi(rbm);
	अचिन्हित पूर्णांक buflen = bi->bi_bytes;
	स्थिर अचिन्हित पूर्णांक bit = (rbm->offset % GFS2_NBBY) * GFS2_BIT_SIZE;

	byte1 = bi->bi_bh->b_data + bi->bi_offset + (rbm->offset / GFS2_NBBY);
	end = bi->bi_bh->b_data + bi->bi_offset + buflen;

	BUG_ON(byte1 >= end);

	cur_state = (*byte1 >> bit) & GFS2_BIT_MASK;

	अगर (unlikely(!valid_change[new_state * 4 + cur_state])) अणु
		काष्ठा gfs2_sbd *sdp = rbm->rgd->rd_sbd;

		fs_warn(sdp, "buf_blk = 0x%x old_state=%d, new_state=%d\n",
			rbm->offset, cur_state, new_state);
		fs_warn(sdp, "rgrp=0x%llx bi_start=0x%x biblk: 0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)rbm->rgd->rd_addr, bi->bi_start,
			(अचिन्हित दीर्घ दीर्घ)bi->bi_bh->b_blocknr);
		fs_warn(sdp, "bi_offset=0x%x bi_bytes=0x%x block=0x%llx\n",
			bi->bi_offset, bi->bi_bytes,
			(अचिन्हित दीर्घ दीर्घ)gfs2_rbm_to_block(rbm));
		dump_stack();
		gfs2_consist_rgrpd(rbm->rgd);
		वापस;
	पूर्ण
	*byte1 ^= (cur_state ^ new_state) << bit;

	अगर (करो_clone && bi->bi_clone) अणु
		byte2 = bi->bi_clone + bi->bi_offset + (rbm->offset / GFS2_NBBY);
		cur_state = (*byte2 >> bit) & GFS2_BIT_MASK;
		*byte2 ^= (cur_state ^ new_state) << bit;
	पूर्ण
पूर्ण

/**
 * gfs2_testbit - test a bit in the biपंचांगaps
 * @rbm: The bit to test
 * @use_clone: If true, test the clone biपंचांगap, not the official biपंचांगap.
 *
 * Some callers like gfs2_unaligned_extlen need to test the clone biपंचांगaps,
 * not the "real" biपंचांगaps, to aव्योम allocating recently मुक्तd blocks.
 *
 * Returns: The two bit block state of the requested bit
 */

अटल अंतरभूत u8 gfs2_testbit(स्थिर काष्ठा gfs2_rbm *rbm, bool use_clone)
अणु
	काष्ठा gfs2_biपंचांगap *bi = rbm_bi(rbm);
	स्थिर u8 *buffer;
	स्थिर u8 *byte;
	अचिन्हित पूर्णांक bit;

	अगर (use_clone && bi->bi_clone)
		buffer = bi->bi_clone;
	अन्यथा
		buffer = bi->bi_bh->b_data;
	buffer += bi->bi_offset;
	byte = buffer + (rbm->offset / GFS2_NBBY);
	bit = (rbm->offset % GFS2_NBBY) * GFS2_BIT_SIZE;

	वापस (*byte >> bit) & GFS2_BIT_MASK;
पूर्ण

/**
 * gfs2_bit_search
 * @ptr: Poपूर्णांकer to biपंचांगap data
 * @mask: Mask to use (normally 0x55555.... but adjusted क्रम search start)
 * @state: The state we are searching क्रम
 *
 * We xor the biपंचांगap data with a patter which is the bitwise opposite
 * of what we are looking क्रम, this gives rise to a pattern of ones
 * wherever there is a match. Since we have two bits per entry, we
 * take this pattern, shअगरt it करोwn by one place and then and it with
 * the original. All the even bit positions (0,2,4, etc) then represent
 * successful matches, so we mask with 0x55555..... to हटाओ the unwanted
 * odd bit positions.
 *
 * This allows searching of a whole u64 at once (32 blocks) with a
 * single test (on 64 bit arches).
 */

अटल अंतरभूत u64 gfs2_bit_search(स्थिर __le64 *ptr, u64 mask, u8 state)
अणु
	u64 पंचांगp;
	अटल स्थिर u64 search[] = अणु
		[0] = 0xffffffffffffffffULL,
		[1] = 0xaaaaaaaaaaaaaaaaULL,
		[2] = 0x5555555555555555ULL,
		[3] = 0x0000000000000000ULL,
	पूर्ण;
	पंचांगp = le64_to_cpu(*ptr) ^ search[state];
	पंचांगp &= (पंचांगp >> 1);
	पंचांगp &= mask;
	वापस पंचांगp;
पूर्ण

/**
 * rs_cmp - multi-block reservation range compare
 * @start: start of the new reservation
 * @len: number of blocks in the new reservation
 * @rs: existing reservation to compare against
 *
 * वापसs: 1 अगर the block range is beyond the reach of the reservation
 *         -1 अगर the block range is beक्रमe the start of the reservation
 *          0 अगर the block range overlaps with the reservation
 */
अटल अंतरभूत पूर्णांक rs_cmp(u64 start, u32 len, काष्ठा gfs2_blkreserv *rs)
अणु
	अगर (start >= rs->rs_start + rs->rs_requested)
		वापस 1;
	अगर (rs->rs_start >= start + len)
		वापस -1;
	वापस 0;
पूर्ण

/**
 * gfs2_bitfit - Search an rgrp's biपंचांगap buffer to find a bit-pair representing
 *       a block in a given allocation state.
 * @buf: the buffer that holds the biपंचांगaps
 * @len: the length (in bytes) of the buffer
 * @goal: start search at this block's bit-pair (within @buffer)
 * @state: GFS2_BLKST_XXX the state of the block we're looking क्रम.
 *
 * Scope of @goal and वापसed block number is only within this biपंचांगap buffer,
 * not entire rgrp or fileप्रणाली.  @buffer will be offset from the actual
 * beginning of a biपंचांगap block buffer, skipping any header काष्ठाures, but
 * headers are always a multiple of 64 bits दीर्घ so that the buffer is
 * always aligned to a 64 bit boundary.
 *
 * The size of the buffer is in bytes, but is it assumed that it is
 * always ok to पढ़ो a complete multiple of 64 bits at the end
 * of the block in हाल the end is no aligned to a natural boundary.
 *
 * Return: the block number (biपंचांगap buffer scope) that was found
 */

अटल u32 gfs2_bitfit(स्थिर u8 *buf, स्थिर अचिन्हित पूर्णांक len,
		       u32 goal, u8 state)
अणु
	u32 spoपूर्णांक = (goal << 1) & ((8*माप(u64)) - 1);
	स्थिर __le64 *ptr = ((__le64 *)buf) + (goal >> 5);
	स्थिर __le64 *end = (__le64 *)(buf + ALIGN(len, माप(u64)));
	u64 पंचांगp;
	u64 mask = 0x5555555555555555ULL;
	u32 bit;

	/* Mask off bits we करोn't care about at the start of the search */
	mask <<= spoपूर्णांक;
	पंचांगp = gfs2_bit_search(ptr, mask, state);
	ptr++;
	जबतक(पंचांगp == 0 && ptr < end) अणु
		पंचांगp = gfs2_bit_search(ptr, 0x5555555555555555ULL, state);
		ptr++;
	पूर्ण
	/* Mask off any bits which are more than len bytes from the start */
	अगर (ptr == end && (len & (माप(u64) - 1)))
		पंचांगp &= (((u64)~0) >> (64 - 8*(len & (माप(u64) - 1))));
	/* Didn't find anything, so वापस */
	अगर (पंचांगp == 0)
		वापस BFITNOENT;
	ptr--;
	bit = __ffs64(पंचांगp);
	bit /= 2;	/* two bits per entry in the biपंचांगap */
	वापस (((स्थिर अचिन्हित अक्षर *)ptr - buf) * GFS2_NBBY) + bit;
पूर्ण

/**
 * gfs2_rbm_from_block - Set the rbm based upon rgd and block number
 * @rbm: The rbm with rgd alपढ़ोy set correctly
 * @block: The block number (fileप्रणाली relative)
 *
 * This sets the bi and offset members of an rbm based on a
 * resource group and a fileप्रणाली relative block number. The
 * resource group must be set in the rbm on entry, the bi and
 * offset members will be set by this function.
 *
 * Returns: 0 on success, or an error code
 */

अटल पूर्णांक gfs2_rbm_from_block(काष्ठा gfs2_rbm *rbm, u64 block)
अणु
	अगर (!rgrp_contains_block(rbm->rgd, block))
		वापस -E2BIG;
	rbm->bii = 0;
	rbm->offset = block - rbm->rgd->rd_data0;
	/* Check अगर the block is within the first block */
	अगर (rbm->offset < rbm_bi(rbm)->bi_blocks)
		वापस 0;

	/* Adjust क्रम the size dअगरf between gfs2_meta_header and gfs2_rgrp */
	rbm->offset += (माप(काष्ठा gfs2_rgrp) -
			माप(काष्ठा gfs2_meta_header)) * GFS2_NBBY;
	rbm->bii = rbm->offset / rbm->rgd->rd_sbd->sd_blocks_per_biपंचांगap;
	rbm->offset -= rbm->bii * rbm->rgd->rd_sbd->sd_blocks_per_biपंचांगap;
	वापस 0;
पूर्ण

/**
 * gfs2_rbm_add - add a number of blocks to an rbm
 * @rbm: The rbm with rgd alपढ़ोy set correctly
 * @blocks: The number of blocks to add to rpm
 *
 * This function takes an existing rbm काष्ठाure and adds a number of blocks to
 * it.
 *
 * Returns: True अगर the new rbm would poपूर्णांक past the end of the rgrp.
 */

अटल bool gfs2_rbm_add(काष्ठा gfs2_rbm *rbm, u32 blocks)
अणु
	काष्ठा gfs2_rgrpd *rgd = rbm->rgd;
	काष्ठा gfs2_biपंचांगap *bi = rgd->rd_bits + rbm->bii;

	अगर (rbm->offset + blocks < bi->bi_blocks) अणु
		rbm->offset += blocks;
		वापस false;
	पूर्ण
	blocks -= bi->bi_blocks - rbm->offset;

	क्रम(;;) अणु
		bi++;
		अगर (bi == rgd->rd_bits + rgd->rd_length)
			वापस true;
		अगर (blocks < bi->bi_blocks) अणु
			rbm->offset = blocks;
			rbm->bii = bi - rgd->rd_bits;
			वापस false;
		पूर्ण
		blocks -= bi->bi_blocks;
	पूर्ण
पूर्ण

/**
 * gfs2_unaligned_extlen - Look क्रम मुक्त blocks which are not byte aligned
 * @rbm: Position to search (value/result)
 * @n_unaligned: Number of unaligned blocks to check
 * @len: Decremented क्रम each block found (terminate on zero)
 *
 * Returns: true अगर a non-मुक्त block is encountered or the end of the resource
 *	    group is reached.
 */

अटल bool gfs2_unaligned_extlen(काष्ठा gfs2_rbm *rbm, u32 n_unaligned, u32 *len)
अणु
	u32 n;
	u8 res;

	क्रम (n = 0; n < n_unaligned; n++) अणु
		res = gfs2_testbit(rbm, true);
		अगर (res != GFS2_BLKST_FREE)
			वापस true;
		(*len)--;
		अगर (*len == 0)
			वापस true;
		अगर (gfs2_rbm_add(rbm, 1))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * gfs2_मुक्त_extlen - Return extent length of मुक्त blocks
 * @rrbm: Starting position
 * @len: Max length to check
 *
 * Starting at the block specअगरied by the rbm, see how many मुक्त blocks
 * there are, not पढ़ोing more than len blocks ahead. This can be करोne
 * using स_प्रथम_inv when the blocks are byte aligned, but has to be करोne
 * on a block by block basis in हाल of unaligned blocks. Also this
 * function can cope with biपंचांगap boundaries (although it must stop on
 * a resource group boundary)
 *
 * Returns: Number of मुक्त blocks in the extent
 */

अटल u32 gfs2_मुक्त_extlen(स्थिर काष्ठा gfs2_rbm *rrbm, u32 len)
अणु
	काष्ठा gfs2_rbm rbm = *rrbm;
	u32 n_unaligned = rbm.offset & 3;
	u32 size = len;
	u32 bytes;
	u32 chunk_size;
	u8 *ptr, *start, *end;
	u64 block;
	काष्ठा gfs2_biपंचांगap *bi;

	अगर (n_unaligned &&
	    gfs2_unaligned_extlen(&rbm, 4 - n_unaligned, &len))
		जाओ out;

	n_unaligned = len & 3;
	/* Start is now byte aligned */
	जबतक (len > 3) अणु
		bi = rbm_bi(&rbm);
		start = bi->bi_bh->b_data;
		अगर (bi->bi_clone)
			start = bi->bi_clone;
		start += bi->bi_offset;
		end = start + bi->bi_bytes;
		BUG_ON(rbm.offset & 3);
		start += (rbm.offset / GFS2_NBBY);
		bytes = min_t(u32, len / GFS2_NBBY, (end - start));
		ptr = स_प्रथम_inv(start, 0, bytes);
		chunk_size = ((ptr == शून्य) ? bytes : (ptr - start));
		chunk_size *= GFS2_NBBY;
		BUG_ON(len < chunk_size);
		len -= chunk_size;
		block = gfs2_rbm_to_block(&rbm);
		अगर (gfs2_rbm_from_block(&rbm, block + chunk_size)) अणु
			n_unaligned = 0;
			अवरोध;
		पूर्ण
		अगर (ptr) अणु
			n_unaligned = 3;
			अवरोध;
		पूर्ण
		n_unaligned = len & 3;
	पूर्ण

	/* Deal with any bits left over at the end */
	अगर (n_unaligned)
		gfs2_unaligned_extlen(&rbm, n_unaligned, &len);
out:
	वापस size - len;
पूर्ण

/**
 * gfs2_bitcount - count the number of bits in a certain state
 * @rgd: the resource group descriptor
 * @buffer: the buffer that holds the biपंचांगaps
 * @buflen: the length (in bytes) of the buffer
 * @state: the state of the block we're looking क्रम
 *
 * Returns: The number of bits
 */

अटल u32 gfs2_bitcount(काष्ठा gfs2_rgrpd *rgd, स्थिर u8 *buffer,
			 अचिन्हित पूर्णांक buflen, u8 state)
अणु
	स्थिर u8 *byte = buffer;
	स्थिर u8 *end = buffer + buflen;
	स्थिर u8 state1 = state << 2;
	स्थिर u8 state2 = state << 4;
	स्थिर u8 state3 = state << 6;
	u32 count = 0;

	क्रम (; byte < end; byte++) अणु
		अगर (((*byte) & 0x03) == state)
			count++;
		अगर (((*byte) & 0x0C) == state1)
			count++;
		अगर (((*byte) & 0x30) == state2)
			count++;
		अगर (((*byte) & 0xC0) == state3)
			count++;
	पूर्ण

	वापस count;
पूर्ण

/**
 * gfs2_rgrp_verअगरy - Verअगरy that a resource group is consistent
 * @rgd: the rgrp
 *
 */

व्योम gfs2_rgrp_verअगरy(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;
	काष्ठा gfs2_biपंचांगap *bi = शून्य;
	u32 length = rgd->rd_length;
	u32 count[4], पंचांगp;
	पूर्णांक buf, x;

	स_रखो(count, 0, 4 * माप(u32));

	/* Count # blocks in each of 4 possible allocation states */
	क्रम (buf = 0; buf < length; buf++) अणु
		bi = rgd->rd_bits + buf;
		क्रम (x = 0; x < 4; x++)
			count[x] += gfs2_bitcount(rgd,
						  bi->bi_bh->b_data +
						  bi->bi_offset,
						  bi->bi_bytes, x);
	पूर्ण

	अगर (count[0] != rgd->rd_मुक्त) अणु
		gfs2_lm(sdp, "free data mismatch:  %u != %u\n",
			count[0], rgd->rd_मुक्त);
		gfs2_consist_rgrpd(rgd);
		वापस;
	पूर्ण

	पंचांगp = rgd->rd_data - rgd->rd_मुक्त - rgd->rd_dinodes;
	अगर (count[1] != पंचांगp) अणु
		gfs2_lm(sdp, "used data mismatch:  %u != %u\n",
			count[1], पंचांगp);
		gfs2_consist_rgrpd(rgd);
		वापस;
	पूर्ण

	अगर (count[2] + count[3] != rgd->rd_dinodes) अणु
		gfs2_lm(sdp, "used metadata mismatch:  %u != %u\n",
			count[2] + count[3], rgd->rd_dinodes);
		gfs2_consist_rgrpd(rgd);
		वापस;
	पूर्ण
पूर्ण

/**
 * gfs2_blk2rgrpd - Find resource group क्रम a given data/meta block number
 * @sdp: The GFS2 superblock
 * @blk: The data block number
 * @exact: True अगर this needs to be an exact match
 *
 * The @exact argument should be set to true by most callers. The exception
 * is when we need to match blocks which are not represented by the rgrp
 * biपंचांगap, but which are part of the rgrp (i.e. padding blocks) which are
 * there क्रम alignment purposes. Another way of looking at it is that @exact
 * matches only valid data/metadata blocks, but with @exact false, it will
 * match any block within the extent of the rgrp.
 *
 * Returns: The resource group, or शून्य अगर not found
 */

काष्ठा gfs2_rgrpd *gfs2_blk2rgrpd(काष्ठा gfs2_sbd *sdp, u64 blk, bool exact)
अणु
	काष्ठा rb_node *n, *next;
	काष्ठा gfs2_rgrpd *cur;

	spin_lock(&sdp->sd_rindex_spin);
	n = sdp->sd_rindex_tree.rb_node;
	जबतक (n) अणु
		cur = rb_entry(n, काष्ठा gfs2_rgrpd, rd_node);
		next = शून्य;
		अगर (blk < cur->rd_addr)
			next = n->rb_left;
		अन्यथा अगर (blk >= cur->rd_data0 + cur->rd_data)
			next = n->rb_right;
		अगर (next == शून्य) अणु
			spin_unlock(&sdp->sd_rindex_spin);
			अगर (exact) अणु
				अगर (blk < cur->rd_addr)
					वापस शून्य;
				अगर (blk >= cur->rd_data0 + cur->rd_data)
					वापस शून्य;
			पूर्ण
			वापस cur;
		पूर्ण
		n = next;
	पूर्ण
	spin_unlock(&sdp->sd_rindex_spin);

	वापस शून्य;
पूर्ण

/**
 * gfs2_rgrpd_get_first - get the first Resource Group in the fileप्रणाली
 * @sdp: The GFS2 superblock
 *
 * Returns: The first rgrp in the fileप्रणाली
 */

काष्ठा gfs2_rgrpd *gfs2_rgrpd_get_first(काष्ठा gfs2_sbd *sdp)
अणु
	स्थिर काष्ठा rb_node *n;
	काष्ठा gfs2_rgrpd *rgd;

	spin_lock(&sdp->sd_rindex_spin);
	n = rb_first(&sdp->sd_rindex_tree);
	rgd = rb_entry(n, काष्ठा gfs2_rgrpd, rd_node);
	spin_unlock(&sdp->sd_rindex_spin);

	वापस rgd;
पूर्ण

/**
 * gfs2_rgrpd_get_next - get the next RG
 * @rgd: the resource group descriptor
 *
 * Returns: The next rgrp
 */

काष्ठा gfs2_rgrpd *gfs2_rgrpd_get_next(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;
	स्थिर काष्ठा rb_node *n;

	spin_lock(&sdp->sd_rindex_spin);
	n = rb_next(&rgd->rd_node);
	अगर (n == शून्य)
		n = rb_first(&sdp->sd_rindex_tree);

	अगर (unlikely(&rgd->rd_node == n)) अणु
		spin_unlock(&sdp->sd_rindex_spin);
		वापस शून्य;
	पूर्ण
	rgd = rb_entry(n, काष्ठा gfs2_rgrpd, rd_node);
	spin_unlock(&sdp->sd_rindex_spin);
	वापस rgd;
पूर्ण

व्योम check_and_update_goal(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	अगर (!ip->i_goal || gfs2_blk2rgrpd(sdp, ip->i_goal, 1) == शून्य)
		ip->i_goal = ip->i_no_addr;
पूर्ण

व्योम gfs2_मुक्त_clones(काष्ठा gfs2_rgrpd *rgd)
अणु
	पूर्णांक x;

	क्रम (x = 0; x < rgd->rd_length; x++) अणु
		काष्ठा gfs2_biपंचांगap *bi = rgd->rd_bits + x;
		kमुक्त(bi->bi_clone);
		bi->bi_clone = शून्य;
	पूर्ण
पूर्ण

अटल व्योम dump_rs(काष्ठा seq_file *seq, स्थिर काष्ठा gfs2_blkreserv *rs,
		    स्थिर अक्षर *fs_id_buf)
अणु
	काष्ठा gfs2_inode *ip = container_of(rs, काष्ठा gfs2_inode, i_res);

	gfs2_prपूर्णांक_dbg(seq, "%s  B: n:%llu s:%llu f:%u\n",
		       fs_id_buf,
		       (अचिन्हित दीर्घ दीर्घ)ip->i_no_addr,
		       (अचिन्हित दीर्घ दीर्घ)rs->rs_start,
		       rs->rs_requested);
पूर्ण

/**
 * __rs_deltree - हटाओ a multi-block reservation from the rgd tree
 * @rs: The reservation to हटाओ
 *
 */
अटल व्योम __rs_deltree(काष्ठा gfs2_blkreserv *rs)
अणु
	काष्ठा gfs2_rgrpd *rgd;

	अगर (!gfs2_rs_active(rs))
		वापस;

	rgd = rs->rs_rgd;
	trace_gfs2_rs(rs, TRACE_RS_TREEDEL);
	rb_erase(&rs->rs_node, &rgd->rd_rstree);
	RB_CLEAR_NODE(&rs->rs_node);

	अगर (rs->rs_requested) अणु
		/* वापस requested blocks to the rgrp */
		BUG_ON(rs->rs_rgd->rd_requested < rs->rs_requested);
		rs->rs_rgd->rd_requested -= rs->rs_requested;

		/* The rgrp extent failure poपूर्णांक is likely not to increase;
		   it will only करो so अगर the मुक्तd blocks are somehow
		   contiguous with a span of मुक्त blocks that follows. Still,
		   it will क्रमce the number to be recalculated later. */
		rgd->rd_extfail_pt += rs->rs_requested;
		rs->rs_requested = 0;
	पूर्ण
पूर्ण

/**
 * gfs2_rs_deltree - हटाओ a multi-block reservation from the rgd tree
 * @rs: The reservation to हटाओ
 *
 */
व्योम gfs2_rs_deltree(काष्ठा gfs2_blkreserv *rs)
अणु
	काष्ठा gfs2_rgrpd *rgd;

	rgd = rs->rs_rgd;
	अगर (rgd) अणु
		spin_lock(&rgd->rd_rsspin);
		__rs_deltree(rs);
		BUG_ON(rs->rs_requested);
		spin_unlock(&rgd->rd_rsspin);
	पूर्ण
पूर्ण

/**
 * gfs2_rs_delete - delete a multi-block reservation
 * @ip: The inode क्रम this reservation
 * @wcount: The inode's ग_लिखो count, or शून्य
 *
 */
व्योम gfs2_rs_delete(काष्ठा gfs2_inode *ip, atomic_t *wcount)
अणु
	करोwn_ग_लिखो(&ip->i_rw_mutex);
	अगर ((wcount == शून्य) || (atomic_पढ़ो(wcount) <= 1))
		gfs2_rs_deltree(&ip->i_res);
	up_ग_लिखो(&ip->i_rw_mutex);
पूर्ण

/**
 * वापस_all_reservations - वापस all reserved blocks back to the rgrp.
 * @rgd: the rgrp that needs its space back
 *
 * We previously reserved a bunch of blocks क्रम allocation. Now we need to
 * give them back. This leave the reservation काष्ठाures in tact, but हटाओs
 * all of their corresponding "no-fly zones".
 */
अटल व्योम वापस_all_reservations(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा rb_node *n;
	काष्ठा gfs2_blkreserv *rs;

	spin_lock(&rgd->rd_rsspin);
	जबतक ((n = rb_first(&rgd->rd_rstree))) अणु
		rs = rb_entry(n, काष्ठा gfs2_blkreserv, rs_node);
		__rs_deltree(rs);
	पूर्ण
	spin_unlock(&rgd->rd_rsspin);
पूर्ण

व्योम gfs2_clear_rgrpd(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा rb_node *n;
	काष्ठा gfs2_rgrpd *rgd;
	काष्ठा gfs2_glock *gl;

	जबतक ((n = rb_first(&sdp->sd_rindex_tree))) अणु
		rgd = rb_entry(n, काष्ठा gfs2_rgrpd, rd_node);
		gl = rgd->rd_gl;

		rb_erase(n, &sdp->sd_rindex_tree);

		अगर (gl) अणु
			अगर (gl->gl_state != LM_ST_UNLOCKED) अणु
				gfs2_glock_cb(gl, LM_ST_UNLOCKED);
				flush_delayed_work(&gl->gl_work);
			पूर्ण
			gfs2_rgrp_brअन्यथा(rgd);
			glock_clear_object(gl, rgd);
			gfs2_glock_put(gl);
		पूर्ण

		gfs2_मुक्त_clones(rgd);
		वापस_all_reservations(rgd);
		kमुक्त(rgd->rd_bits);
		rgd->rd_bits = शून्य;
		kmem_cache_मुक्त(gfs2_rgrpd_cachep, rgd);
	पूर्ण
पूर्ण

/**
 * compute_bitकाष्ठाs - Compute the biपंचांगap sizes
 * @rgd: The resource group descriptor
 *
 * Calculates biपंचांगap descriptors, one क्रम each block that contains biपंचांगap data
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक compute_bitकाष्ठाs(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;
	काष्ठा gfs2_biपंचांगap *bi;
	u32 length = rgd->rd_length; /* # blocks in hdr & biपंचांगap */
	u32 bytes_left, bytes;
	पूर्णांक x;

	अगर (!length)
		वापस -EINVAL;

	rgd->rd_bits = kसुस्मृति(length, माप(काष्ठा gfs2_biपंचांगap), GFP_NOFS);
	अगर (!rgd->rd_bits)
		वापस -ENOMEM;

	bytes_left = rgd->rd_bitbytes;

	क्रम (x = 0; x < length; x++) अणु
		bi = rgd->rd_bits + x;

		bi->bi_flags = 0;
		/* small rgrp; biपंचांगap stored completely in header block */
		अगर (length == 1) अणु
			bytes = bytes_left;
			bi->bi_offset = माप(काष्ठा gfs2_rgrp);
			bi->bi_start = 0;
			bi->bi_bytes = bytes;
			bi->bi_blocks = bytes * GFS2_NBBY;
		/* header block */
		पूर्ण अन्यथा अगर (x == 0) अणु
			bytes = sdp->sd_sb.sb_bsize - माप(काष्ठा gfs2_rgrp);
			bi->bi_offset = माप(काष्ठा gfs2_rgrp);
			bi->bi_start = 0;
			bi->bi_bytes = bytes;
			bi->bi_blocks = bytes * GFS2_NBBY;
		/* last block */
		पूर्ण अन्यथा अगर (x + 1 == length) अणु
			bytes = bytes_left;
			bi->bi_offset = माप(काष्ठा gfs2_meta_header);
			bi->bi_start = rgd->rd_bitbytes - bytes_left;
			bi->bi_bytes = bytes;
			bi->bi_blocks = bytes * GFS2_NBBY;
		/* other blocks */
		पूर्ण अन्यथा अणु
			bytes = sdp->sd_sb.sb_bsize -
				माप(काष्ठा gfs2_meta_header);
			bi->bi_offset = माप(काष्ठा gfs2_meta_header);
			bi->bi_start = rgd->rd_bitbytes - bytes_left;
			bi->bi_bytes = bytes;
			bi->bi_blocks = bytes * GFS2_NBBY;
		पूर्ण

		bytes_left -= bytes;
	पूर्ण

	अगर (bytes_left) अणु
		gfs2_consist_rgrpd(rgd);
		वापस -EIO;
	पूर्ण
	bi = rgd->rd_bits + (length - 1);
	अगर ((bi->bi_start + bi->bi_bytes) * GFS2_NBBY != rgd->rd_data) अणु
		gfs2_lm(sdp,
			"ri_addr = %llu\n"
			"ri_length = %u\n"
			"ri_data0 = %llu\n"
			"ri_data = %u\n"
			"ri_bitbytes = %u\n"
			"start=%u len=%u offset=%u\n",
			(अचिन्हित दीर्घ दीर्घ)rgd->rd_addr,
			rgd->rd_length,
			(अचिन्हित दीर्घ दीर्घ)rgd->rd_data0,
			rgd->rd_data,
			rgd->rd_bitbytes,
			bi->bi_start, bi->bi_bytes, bi->bi_offset);
		gfs2_consist_rgrpd(rgd);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * gfs2_ri_total - Total up the file प्रणाली space, according to the rindex.
 * @sdp: the fileप्रणाली
 *
 */
u64 gfs2_ri_total(काष्ठा gfs2_sbd *sdp)
अणु
	u64 total_data = 0;	
	काष्ठा inode *inode = sdp->sd_rindex;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	अक्षर buf[माप(काष्ठा gfs2_rindex)];
	पूर्णांक error, rgrps;

	क्रम (rgrps = 0;; rgrps++) अणु
		loff_t pos = rgrps * माप(काष्ठा gfs2_rindex);

		अगर (pos + माप(काष्ठा gfs2_rindex) > i_size_पढ़ो(inode))
			अवरोध;
		error = gfs2_पूर्णांकernal_पढ़ो(ip, buf, &pos,
					   माप(काष्ठा gfs2_rindex));
		अगर (error != माप(काष्ठा gfs2_rindex))
			अवरोध;
		total_data += be32_to_cpu(((काष्ठा gfs2_rindex *)buf)->ri_data);
	पूर्ण
	वापस total_data;
पूर्ण

अटल पूर्णांक rgd_insert(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;
	काष्ठा rb_node **newn = &sdp->sd_rindex_tree.rb_node, *parent = शून्य;

	/* Figure out where to put new node */
	जबतक (*newn) अणु
		काष्ठा gfs2_rgrpd *cur = rb_entry(*newn, काष्ठा gfs2_rgrpd,
						  rd_node);

		parent = *newn;
		अगर (rgd->rd_addr < cur->rd_addr)
			newn = &((*newn)->rb_left);
		अन्यथा अगर (rgd->rd_addr > cur->rd_addr)
			newn = &((*newn)->rb_right);
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	rb_link_node(&rgd->rd_node, parent, newn);
	rb_insert_color(&rgd->rd_node, &sdp->sd_rindex_tree);
	sdp->sd_rgrps++;
	वापस 0;
पूर्ण

/**
 * पढ़ो_rindex_entry - Pull in a new resource index entry from the disk
 * @ip: Poपूर्णांकer to the rindex inode
 *
 * Returns: 0 on success, > 0 on खातापूर्ण, error code otherwise
 */

अटल पूर्णांक पढ़ो_rindex_entry(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	loff_t pos = sdp->sd_rgrps * माप(काष्ठा gfs2_rindex);
	काष्ठा gfs2_rindex buf;
	पूर्णांक error;
	काष्ठा gfs2_rgrpd *rgd;

	अगर (pos >= i_size_पढ़ो(&ip->i_inode))
		वापस 1;

	error = gfs2_पूर्णांकernal_पढ़ो(ip, (अक्षर *)&buf, &pos,
				   माप(काष्ठा gfs2_rindex));

	अगर (error != माप(काष्ठा gfs2_rindex))
		वापस (error == 0) ? 1 : error;

	rgd = kmem_cache_zalloc(gfs2_rgrpd_cachep, GFP_NOFS);
	error = -ENOMEM;
	अगर (!rgd)
		वापस error;

	rgd->rd_sbd = sdp;
	rgd->rd_addr = be64_to_cpu(buf.ri_addr);
	rgd->rd_length = be32_to_cpu(buf.ri_length);
	rgd->rd_data0 = be64_to_cpu(buf.ri_data0);
	rgd->rd_data = be32_to_cpu(buf.ri_data);
	rgd->rd_bitbytes = be32_to_cpu(buf.ri_bitbytes);
	spin_lock_init(&rgd->rd_rsspin);
	mutex_init(&rgd->rd_mutex);

	error = compute_bitकाष्ठाs(rgd);
	अगर (error)
		जाओ fail;

	error = gfs2_glock_get(sdp, rgd->rd_addr,
			       &gfs2_rgrp_glops, CREATE, &rgd->rd_gl);
	अगर (error)
		जाओ fail;

	rgd->rd_rgl = (काष्ठा gfs2_rgrp_lvb *)rgd->rd_gl->gl_lksb.sb_lvbptr;
	rgd->rd_flags &= ~(GFS2_RDF_UPTODATE | GFS2_RDF_PREFERRED);
	अगर (rgd->rd_data > sdp->sd_max_rg_data)
		sdp->sd_max_rg_data = rgd->rd_data;
	spin_lock(&sdp->sd_rindex_spin);
	error = rgd_insert(rgd);
	spin_unlock(&sdp->sd_rindex_spin);
	अगर (!error) अणु
		glock_set_object(rgd->rd_gl, rgd);
		वापस 0;
	पूर्ण

	error = 0; /* someone अन्यथा पढ़ो in the rgrp; मुक्त it and ignore it */
	gfs2_glock_put(rgd->rd_gl);

fail:
	kमुक्त(rgd->rd_bits);
	rgd->rd_bits = शून्य;
	kmem_cache_मुक्त(gfs2_rgrpd_cachep, rgd);
	वापस error;
पूर्ण

/**
 * set_rgrp_preferences - Run all the rgrps, selecting some we prefer to use
 * @sdp: the GFS2 superblock
 *
 * The purpose of this function is to select a subset of the resource groups
 * and mark them as PREFERRED. We करो it in such a way that each node prefers
 * to use a unique set of rgrps to minimize glock contention.
 */
अटल व्योम set_rgrp_preferences(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_rgrpd *rgd, *first;
	पूर्णांक i;

	/* Skip an initial number of rgrps, based on this node's journal ID.
	   That should start each node out on its own set. */
	rgd = gfs2_rgrpd_get_first(sdp);
	क्रम (i = 0; i < sdp->sd_lockकाष्ठा.ls_jid; i++)
		rgd = gfs2_rgrpd_get_next(rgd);
	first = rgd;

	करो अणु
		rgd->rd_flags |= GFS2_RDF_PREFERRED;
		क्रम (i = 0; i < sdp->sd_journals; i++) अणु
			rgd = gfs2_rgrpd_get_next(rgd);
			अगर (!rgd || rgd == first)
				अवरोध;
		पूर्ण
	पूर्ण जबतक (rgd && rgd != first);
पूर्ण

/**
 * gfs2_ri_update - Pull in a new resource index from the disk
 * @ip: poपूर्णांकer to the rindex inode
 *
 * Returns: 0 on successful update, error code otherwise
 */

अटल पूर्णांक gfs2_ri_update(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	पूर्णांक error;

	करो अणु
		error = पढ़ो_rindex_entry(ip);
	पूर्ण जबतक (error == 0);

	अगर (error < 0)
		वापस error;

	अगर (RB_EMPTY_ROOT(&sdp->sd_rindex_tree)) अणु
		fs_err(sdp, "no resource groups found in the file system.\n");
		वापस -ENOENT;
	पूर्ण
	set_rgrp_preferences(sdp);

	sdp->sd_rindex_uptodate = 1;
	वापस 0;
पूर्ण

/**
 * gfs2_rindex_update - Update the rindex अगर required
 * @sdp: The GFS2 superblock
 *
 * We grab a lock on the rindex inode to make sure that it करोesn't
 * change whilst we are perक्रमming an operation. We keep this lock
 * क्रम quite दीर्घ periods of समय compared to other locks. This
 * करोesn't matter, since it is shared and it is very, very rarely
 * accessed in the exclusive mode (i.e. only when expanding the fileप्रणाली).
 *
 * This makes sure that we're using the latest copy of the resource index
 * special file, which might have been updated अगर someone expanded the
 * fileप्रणाली (via gfs2_grow utility), which adds new resource groups.
 *
 * Returns: 0 on succeess, error code otherwise
 */

पूर्णांक gfs2_rindex_update(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(sdp->sd_rindex);
	काष्ठा gfs2_glock *gl = ip->i_gl;
	काष्ठा gfs2_holder ri_gh;
	पूर्णांक error = 0;
	पूर्णांक unlock_required = 0;

	/* Read new copy from disk अगर we करोn't have the latest */
	अगर (!sdp->sd_rindex_uptodate) अणु
		अगर (!gfs2_glock_is_locked_by_me(gl)) अणु
			error = gfs2_glock_nq_init(gl, LM_ST_SHARED, 0, &ri_gh);
			अगर (error)
				वापस error;
			unlock_required = 1;
		पूर्ण
		अगर (!sdp->sd_rindex_uptodate)
			error = gfs2_ri_update(ip);
		अगर (unlock_required)
			gfs2_glock_dq_uninit(&ri_gh);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम gfs2_rgrp_in(काष्ठा gfs2_rgrpd *rgd, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा gfs2_rgrp *str = buf;
	u32 rg_flags;

	rg_flags = be32_to_cpu(str->rg_flags);
	rg_flags &= ~GFS2_RDF_MASK;
	rgd->rd_flags &= GFS2_RDF_MASK;
	rgd->rd_flags |= rg_flags;
	rgd->rd_मुक्त = be32_to_cpu(str->rg_मुक्त);
	rgd->rd_dinodes = be32_to_cpu(str->rg_dinodes);
	rgd->rd_igeneration = be64_to_cpu(str->rg_igeneration);
	/* rd_data0, rd_data and rd_bitbytes alपढ़ोy set from rindex */
पूर्ण

अटल व्योम gfs2_rgrp_ondisk2lvb(काष्ठा gfs2_rgrp_lvb *rgl, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा gfs2_rgrp *str = buf;

	rgl->rl_magic = cpu_to_be32(GFS2_MAGIC);
	rgl->rl_flags = str->rg_flags;
	rgl->rl_मुक्त = str->rg_मुक्त;
	rgl->rl_dinodes = str->rg_dinodes;
	rgl->rl_igeneration = str->rg_igeneration;
	rgl->__pad = 0UL;
पूर्ण

अटल व्योम gfs2_rgrp_out(काष्ठा gfs2_rgrpd *rgd, व्योम *buf)
अणु
	काष्ठा gfs2_rgrpd *next = gfs2_rgrpd_get_next(rgd);
	काष्ठा gfs2_rgrp *str = buf;
	u32 crc;

	str->rg_flags = cpu_to_be32(rgd->rd_flags & ~GFS2_RDF_MASK);
	str->rg_मुक्त = cpu_to_be32(rgd->rd_मुक्त);
	str->rg_dinodes = cpu_to_be32(rgd->rd_dinodes);
	अगर (next == शून्य)
		str->rg_skip = 0;
	अन्यथा अगर (next->rd_addr > rgd->rd_addr)
		str->rg_skip = cpu_to_be32(next->rd_addr - rgd->rd_addr);
	str->rg_igeneration = cpu_to_be64(rgd->rd_igeneration);
	str->rg_data0 = cpu_to_be64(rgd->rd_data0);
	str->rg_data = cpu_to_be32(rgd->rd_data);
	str->rg_bitbytes = cpu_to_be32(rgd->rd_bitbytes);
	str->rg_crc = 0;
	crc = gfs2_disk_hash(buf, माप(काष्ठा gfs2_rgrp));
	str->rg_crc = cpu_to_be32(crc);

	स_रखो(&str->rg_reserved, 0, माप(str->rg_reserved));
	gfs2_rgrp_ondisk2lvb(rgd->rd_rgl, buf);
पूर्ण

अटल पूर्णांक gfs2_rgrp_lvb_valid(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा gfs2_rgrp_lvb *rgl = rgd->rd_rgl;
	काष्ठा gfs2_rgrp *str = (काष्ठा gfs2_rgrp *)rgd->rd_bits[0].bi_bh->b_data;
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;
	पूर्णांक valid = 1;

	अगर (rgl->rl_flags != str->rg_flags) अणु
		fs_warn(sdp, "GFS2: rgd: %llu lvb flag mismatch %u/%u",
			(अचिन्हित दीर्घ दीर्घ)rgd->rd_addr,
		       be32_to_cpu(rgl->rl_flags), be32_to_cpu(str->rg_flags));
		valid = 0;
	पूर्ण
	अगर (rgl->rl_मुक्त != str->rg_मुक्त) अणु
		fs_warn(sdp, "GFS2: rgd: %llu lvb free mismatch %u/%u",
			(अचिन्हित दीर्घ दीर्घ)rgd->rd_addr,
			be32_to_cpu(rgl->rl_मुक्त), be32_to_cpu(str->rg_मुक्त));
		valid = 0;
	पूर्ण
	अगर (rgl->rl_dinodes != str->rg_dinodes) अणु
		fs_warn(sdp, "GFS2: rgd: %llu lvb dinode mismatch %u/%u",
			(अचिन्हित दीर्घ दीर्घ)rgd->rd_addr,
			be32_to_cpu(rgl->rl_dinodes),
			be32_to_cpu(str->rg_dinodes));
		valid = 0;
	पूर्ण
	अगर (rgl->rl_igeneration != str->rg_igeneration) अणु
		fs_warn(sdp, "GFS2: rgd: %llu lvb igen mismatch %llu/%llu",
			(अचिन्हित दीर्घ दीर्घ)rgd->rd_addr,
			(अचिन्हित दीर्घ दीर्घ)be64_to_cpu(rgl->rl_igeneration),
			(अचिन्हित दीर्घ दीर्घ)be64_to_cpu(str->rg_igeneration));
		valid = 0;
	पूर्ण
	वापस valid;
पूर्ण

अटल u32 count_unlinked(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा gfs2_biपंचांगap *bi;
	स्थिर u32 length = rgd->rd_length;
	स्थिर u8 *buffer = शून्य;
	u32 i, goal, count = 0;

	क्रम (i = 0, bi = rgd->rd_bits; i < length; i++, bi++) अणु
		goal = 0;
		buffer = bi->bi_bh->b_data + bi->bi_offset;
		WARN_ON(!buffer_uptodate(bi->bi_bh));
		जबतक (goal < bi->bi_blocks) अणु
			goal = gfs2_bitfit(buffer, bi->bi_bytes, goal,
					   GFS2_BLKST_UNLINKED);
			अगर (goal == BFITNOENT)
				अवरोध;
			count++;
			goal++;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम rgrp_set_biपंचांगap_flags(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा gfs2_biपंचांगap *bi;
	पूर्णांक x;

	अगर (rgd->rd_मुक्त) अणु
		क्रम (x = 0; x < rgd->rd_length; x++) अणु
			bi = rgd->rd_bits + x;
			clear_bit(GBF_FULL, &bi->bi_flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (x = 0; x < rgd->rd_length; x++) अणु
			bi = rgd->rd_bits + x;
			set_bit(GBF_FULL, &bi->bi_flags);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * gfs2_rgrp_bh_get - Read in a RG's header and biपंचांगaps
 * @rgd: the काष्ठा gfs2_rgrpd describing the RG to पढ़ो in
 *
 * Read in all of a Resource Group's header and biपंचांगap blocks.
 * Caller must eventually call gfs2_rgrp_brअन्यथा() to मुक्त the biपंचांगaps.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_rgrp_bh_get(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;
	काष्ठा gfs2_glock *gl = rgd->rd_gl;
	अचिन्हित पूर्णांक length = rgd->rd_length;
	काष्ठा gfs2_biपंचांगap *bi;
	अचिन्हित पूर्णांक x, y;
	पूर्णांक error;

	अगर (rgd->rd_bits[0].bi_bh != शून्य)
		वापस 0;

	क्रम (x = 0; x < length; x++) अणु
		bi = rgd->rd_bits + x;
		error = gfs2_meta_पढ़ो(gl, rgd->rd_addr + x, 0, 0, &bi->bi_bh);
		अगर (error)
			जाओ fail;
	पूर्ण

	क्रम (y = length; y--;) अणु
		bi = rgd->rd_bits + y;
		error = gfs2_meta_रुको(sdp, bi->bi_bh);
		अगर (error)
			जाओ fail;
		अगर (gfs2_metatype_check(sdp, bi->bi_bh, y ? GFS2_METATYPE_RB :
					      GFS2_METATYPE_RG)) अणु
			error = -EIO;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (!(rgd->rd_flags & GFS2_RDF_UPTODATE)) अणु
		gfs2_rgrp_in(rgd, (rgd->rd_bits[0].bi_bh)->b_data);
		rgrp_set_biपंचांगap_flags(rgd);
		rgd->rd_flags |= (GFS2_RDF_UPTODATE | GFS2_RDF_CHECK);
		rgd->rd_मुक्त_clone = rgd->rd_मुक्त;
		BUG_ON(rgd->rd_reserved);
		/* max out the rgrp allocation failure poपूर्णांक */
		rgd->rd_extfail_pt = rgd->rd_मुक्त;
	पूर्ण
	अगर (cpu_to_be32(GFS2_MAGIC) != rgd->rd_rgl->rl_magic) अणु
		rgd->rd_rgl->rl_unlinked = cpu_to_be32(count_unlinked(rgd));
		gfs2_rgrp_ondisk2lvb(rgd->rd_rgl,
				     rgd->rd_bits[0].bi_bh->b_data);
	पूर्ण
	अन्यथा अगर (sdp->sd_args.ar_rgrplvb) अणु
		अगर (!gfs2_rgrp_lvb_valid(rgd))अणु
			gfs2_consist_rgrpd(rgd);
			error = -EIO;
			जाओ fail;
		पूर्ण
		अगर (rgd->rd_rgl->rl_unlinked == 0)
			rgd->rd_flags &= ~GFS2_RDF_CHECK;
	पूर्ण
	वापस 0;

fail:
	जबतक (x--) अणु
		bi = rgd->rd_bits + x;
		brअन्यथा(bi->bi_bh);
		bi->bi_bh = शून्य;
		gfs2_निश्चित_warn(sdp, !bi->bi_clone);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक update_rgrp_lvb(काष्ठा gfs2_rgrpd *rgd)
अणु
	u32 rl_flags;

	अगर (rgd->rd_flags & GFS2_RDF_UPTODATE)
		वापस 0;

	अगर (cpu_to_be32(GFS2_MAGIC) != rgd->rd_rgl->rl_magic)
		वापस gfs2_rgrp_bh_get(rgd);

	rl_flags = be32_to_cpu(rgd->rd_rgl->rl_flags);
	rl_flags &= ~GFS2_RDF_MASK;
	rgd->rd_flags &= GFS2_RDF_MASK;
	rgd->rd_flags |= (rl_flags | GFS2_RDF_CHECK);
	अगर (rgd->rd_rgl->rl_unlinked == 0)
		rgd->rd_flags &= ~GFS2_RDF_CHECK;
	rgd->rd_मुक्त = be32_to_cpu(rgd->rd_rgl->rl_मुक्त);
	rgrp_set_biपंचांगap_flags(rgd);
	rgd->rd_मुक्त_clone = rgd->rd_मुक्त;
	BUG_ON(rgd->rd_reserved);
	/* max out the rgrp allocation failure poपूर्णांक */
	rgd->rd_extfail_pt = rgd->rd_मुक्त;
	rgd->rd_dinodes = be32_to_cpu(rgd->rd_rgl->rl_dinodes);
	rgd->rd_igeneration = be64_to_cpu(rgd->rd_rgl->rl_igeneration);
	वापस 0;
पूर्ण

पूर्णांक gfs2_rgrp_go_lock(काष्ठा gfs2_holder *gh)
अणु
	काष्ठा gfs2_rgrpd *rgd = gh->gh_gl->gl_object;
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;

	अगर (gh->gh_flags & GL_SKIP && sdp->sd_args.ar_rgrplvb)
		वापस 0;
	वापस gfs2_rgrp_bh_get(rgd);
पूर्ण

/**
 * gfs2_rgrp_brअन्यथा - Release RG biपंचांगaps पढ़ो in with gfs2_rgrp_bh_get()
 * @rgd: The resource group
 *
 */

व्योम gfs2_rgrp_brअन्यथा(काष्ठा gfs2_rgrpd *rgd)
अणु
	पूर्णांक x, length = rgd->rd_length;

	क्रम (x = 0; x < length; x++) अणु
		काष्ठा gfs2_biपंचांगap *bi = rgd->rd_bits + x;
		अगर (bi->bi_bh) अणु
			brअन्यथा(bi->bi_bh);
			bi->bi_bh = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक gfs2_rgrp_send_discards(काष्ठा gfs2_sbd *sdp, u64 offset,
			     काष्ठा buffer_head *bh,
			     स्थिर काष्ठा gfs2_biपंचांगap *bi, अचिन्हित minlen, u64 *ptrimmed)
अणु
	काष्ठा super_block *sb = sdp->sd_vfs;
	u64 blk;
	sector_t start = 0;
	sector_t nr_blks = 0;
	पूर्णांक rv;
	अचिन्हित पूर्णांक x;
	u32 trimmed = 0;
	u8 dअगरf;

	क्रम (x = 0; x < bi->bi_bytes; x++) अणु
		स्थिर u8 *clone = bi->bi_clone ? bi->bi_clone : bi->bi_bh->b_data;
		clone += bi->bi_offset;
		clone += x;
		अगर (bh) अणु
			स्थिर u8 *orig = bh->b_data + bi->bi_offset + x;
			dअगरf = ~(*orig | (*orig >> 1)) & (*clone | (*clone >> 1));
		पूर्ण अन्यथा अणु
			dअगरf = ~(*clone | (*clone >> 1));
		पूर्ण
		dअगरf &= 0x55;
		अगर (dअगरf == 0)
			जारी;
		blk = offset + ((bi->bi_start + x) * GFS2_NBBY);
		जबतक(dअगरf) अणु
			अगर (dअगरf & 1) अणु
				अगर (nr_blks == 0)
					जाओ start_new_extent;
				अगर ((start + nr_blks) != blk) अणु
					अगर (nr_blks >= minlen) अणु
						rv = sb_issue_discard(sb,
							start, nr_blks,
							GFP_NOFS, 0);
						अगर (rv)
							जाओ fail;
						trimmed += nr_blks;
					पूर्ण
					nr_blks = 0;
start_new_extent:
					start = blk;
				पूर्ण
				nr_blks++;
			पूर्ण
			dअगरf >>= 2;
			blk++;
		पूर्ण
	पूर्ण
	अगर (nr_blks >= minlen) अणु
		rv = sb_issue_discard(sb, start, nr_blks, GFP_NOFS, 0);
		अगर (rv)
			जाओ fail;
		trimmed += nr_blks;
	पूर्ण
	अगर (ptrimmed)
		*ptrimmed = trimmed;
	वापस 0;

fail:
	अगर (sdp->sd_args.ar_discard)
		fs_warn(sdp, "error %d on discard request, turning discards off for this filesystem\n", rv);
	sdp->sd_args.ar_discard = 0;
	वापस -EIO;
पूर्ण

/**
 * gfs2_fitrim - Generate discard requests क्रम unused bits of the fileप्रणाली
 * @filp: Any file on the fileप्रणाली
 * @argp: Poपूर्णांकer to the arguments (also used to pass result)
 *
 * Returns: 0 on success, otherwise error code
 */

पूर्णांक gfs2_fitrim(काष्ठा file *filp, व्योम __user *argp)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा request_queue *q = bdev_get_queue(sdp->sd_vfs->s_bdev);
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_rgrpd *rgd;
	काष्ठा gfs2_rgrpd *rgd_end;
	काष्ठा gfs2_holder gh;
	काष्ठा fstrim_range r;
	पूर्णांक ret = 0;
	u64 amt;
	u64 trimmed = 0;
	u64 start, end, minlen;
	अचिन्हित पूर्णांक x;
	अचिन्हित bs_shअगरt = sdp->sd_sb.sb_bsize_shअगरt;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags))
		वापस -EROFS;

	अगर (!blk_queue_discard(q))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&r, argp, माप(r)))
		वापस -EFAULT;

	ret = gfs2_rindex_update(sdp);
	अगर (ret)
		वापस ret;

	start = r.start >> bs_shअगरt;
	end = start + (r.len >> bs_shअगरt);
	minlen = max_t(u64, r.minlen,
		       q->limits.discard_granularity) >> bs_shअगरt;

	अगर (end <= start || minlen > sdp->sd_max_rg_data)
		वापस -EINVAL;

	rgd = gfs2_blk2rgrpd(sdp, start, 0);
	rgd_end = gfs2_blk2rgrpd(sdp, end, 0);

	अगर ((gfs2_rgrpd_get_first(sdp) == gfs2_rgrpd_get_next(rgd_end))
	    && (start > rgd_end->rd_data0 + rgd_end->rd_data))
		वापस -EINVAL; /* start is beyond the end of the fs */

	जबतक (1) अणु

		ret = gfs2_glock_nq_init(rgd->rd_gl, LM_ST_EXCLUSIVE,
					 LM_FLAG_NODE_SCOPE, &gh);
		अगर (ret)
			जाओ out;

		अगर (!(rgd->rd_flags & GFS2_RGF_TRIMMED)) अणु
			/* Trim each biपंचांगap in the rgrp */
			क्रम (x = 0; x < rgd->rd_length; x++) अणु
				काष्ठा gfs2_biपंचांगap *bi = rgd->rd_bits + x;
				rgrp_lock_local(rgd);
				ret = gfs2_rgrp_send_discards(sdp,
						rgd->rd_data0, शून्य, bi, minlen,
						&amt);
				rgrp_unlock_local(rgd);
				अगर (ret) अणु
					gfs2_glock_dq_uninit(&gh);
					जाओ out;
				पूर्ण
				trimmed += amt;
			पूर्ण

			/* Mark rgrp as having been trimmed */
			ret = gfs2_trans_begin(sdp, RES_RG_HDR, 0);
			अगर (ret == 0) अणु
				bh = rgd->rd_bits[0].bi_bh;
				rgrp_lock_local(rgd);
				rgd->rd_flags |= GFS2_RGF_TRIMMED;
				gfs2_trans_add_meta(rgd->rd_gl, bh);
				gfs2_rgrp_out(rgd, bh->b_data);
				rgrp_unlock_local(rgd);
				gfs2_trans_end(sdp);
			पूर्ण
		पूर्ण
		gfs2_glock_dq_uninit(&gh);

		अगर (rgd == rgd_end)
			अवरोध;

		rgd = gfs2_rgrpd_get_next(rgd);
	पूर्ण

out:
	r.len = trimmed << bs_shअगरt;
	अगर (copy_to_user(argp, &r, माप(r)))
		वापस -EFAULT;

	वापस ret;
पूर्ण

/**
 * rs_insert - insert a new multi-block reservation पूर्णांकo the rgrp's rb_tree
 * @ip: the inode काष्ठाure
 *
 */
अटल व्योम rs_insert(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा rb_node **newn, *parent = शून्य;
	पूर्णांक rc;
	काष्ठा gfs2_blkreserv *rs = &ip->i_res;
	काष्ठा gfs2_rgrpd *rgd = rs->rs_rgd;

	BUG_ON(gfs2_rs_active(rs));

	spin_lock(&rgd->rd_rsspin);
	newn = &rgd->rd_rstree.rb_node;
	जबतक (*newn) अणु
		काष्ठा gfs2_blkreserv *cur =
			rb_entry(*newn, काष्ठा gfs2_blkreserv, rs_node);

		parent = *newn;
		rc = rs_cmp(rs->rs_start, rs->rs_requested, cur);
		अगर (rc > 0)
			newn = &((*newn)->rb_right);
		अन्यथा अगर (rc < 0)
			newn = &((*newn)->rb_left);
		अन्यथा अणु
			spin_unlock(&rgd->rd_rsspin);
			WARN_ON(1);
			वापस;
		पूर्ण
	पूर्ण

	rb_link_node(&rs->rs_node, parent, newn);
	rb_insert_color(&rs->rs_node, &rgd->rd_rstree);

	/* Do our rgrp accounting क्रम the reservation */
	rgd->rd_requested += rs->rs_requested; /* blocks requested */
	spin_unlock(&rgd->rd_rsspin);
	trace_gfs2_rs(rs, TRACE_RS_INSERT);
पूर्ण

/**
 * rgd_मुक्त - वापस the number of मुक्त blocks we can allocate
 * @rgd: the resource group
 * @rs: The reservation to मुक्त
 *
 * This function वापसs the number of मुक्त blocks क्रम an rgrp.
 * That's the clone-मुक्त blocks (blocks that are मुक्त, not including those
 * still being used क्रम unlinked files that haven't been deleted.)
 *
 * It also subtracts any blocks reserved by someone अन्यथा, but करोes not
 * include मुक्त blocks that are still part of our current reservation,
 * because obviously we can (and will) allocate them.
 */
अटल अंतरभूत u32 rgd_मुक्त(काष्ठा gfs2_rgrpd *rgd, काष्ठा gfs2_blkreserv *rs)
अणु
	u32 tot_reserved, tot_मुक्त;

	अगर (WARN_ON_ONCE(rgd->rd_requested < rs->rs_requested))
		वापस 0;
	tot_reserved = rgd->rd_requested - rs->rs_requested;

	अगर (rgd->rd_मुक्त_clone < tot_reserved)
		tot_reserved = 0;

	tot_मुक्त = rgd->rd_मुक्त_clone - tot_reserved;

	वापस tot_मुक्त;
पूर्ण

/**
 * rg_mblk_search - find a group of multiple मुक्त blocks to क्रमm a reservation
 * @rgd: the resource group descriptor
 * @ip: poपूर्णांकer to the inode क्रम which we're reserving blocks
 * @ap: the allocation parameters
 *
 */

अटल व्योम rg_mblk_search(काष्ठा gfs2_rgrpd *rgd, काष्ठा gfs2_inode *ip,
			   स्थिर काष्ठा gfs2_alloc_parms *ap)
अणु
	काष्ठा gfs2_rbm rbm = अणु .rgd = rgd, पूर्ण;
	u64 goal;
	काष्ठा gfs2_blkreserv *rs = &ip->i_res;
	u32 extlen;
	u32 मुक्त_blocks, blocks_available;
	पूर्णांक ret;
	काष्ठा inode *inode = &ip->i_inode;

	spin_lock(&rgd->rd_rsspin);
	मुक्त_blocks = rgd_मुक्त(rgd, rs);
	अगर (rgd->rd_मुक्त_clone < rgd->rd_requested)
		मुक्त_blocks = 0;
	blocks_available = rgd->rd_मुक्त_clone - rgd->rd_reserved;
	अगर (rgd == rs->rs_rgd)
		blocks_available += rs->rs_reserved;
	spin_unlock(&rgd->rd_rsspin);

	अगर (S_ISसूची(inode->i_mode))
		extlen = 1;
	अन्यथा अणु
		extlen = max_t(u32, atomic_पढ़ो(&ip->i_sizehपूर्णांक), ap->target);
		extlen = clamp(extlen, (u32)RGRP_RSRV_MINBLKS, मुक्त_blocks);
	पूर्ण
	अगर (मुक्त_blocks < extlen || blocks_available < extlen)
		वापस;

	/* Find biपंचांगap block that contains bits क्रम goal block */
	अगर (rgrp_contains_block(rgd, ip->i_goal))
		goal = ip->i_goal;
	अन्यथा
		goal = rgd->rd_last_alloc + rgd->rd_data0;

	अगर (WARN_ON(gfs2_rbm_from_block(&rbm, goal)))
		वापस;

	ret = gfs2_rbm_find(&rbm, GFS2_BLKST_FREE, &extlen, &ip->i_res, true);
	अगर (ret == 0) अणु
		rs->rs_start = gfs2_rbm_to_block(&rbm);
		rs->rs_requested = extlen;
		rs_insert(ip);
	पूर्ण अन्यथा अणु
		अगर (goal == rgd->rd_last_alloc + rgd->rd_data0)
			rgd->rd_last_alloc = 0;
	पूर्ण
पूर्ण

/**
 * gfs2_next_unreserved_block - Return next block that is not reserved
 * @rgd: The resource group
 * @block: The starting block
 * @length: The required length
 * @ignore_rs: Reservation to ignore
 *
 * If the block करोes not appear in any reservation, then वापस the
 * block number unchanged. If it करोes appear in the reservation, then
 * keep looking through the tree of reservations in order to find the
 * first block number which is not reserved.
 */

अटल u64 gfs2_next_unreserved_block(काष्ठा gfs2_rgrpd *rgd, u64 block,
				      u32 length,
				      काष्ठा gfs2_blkreserv *ignore_rs)
अणु
	काष्ठा gfs2_blkreserv *rs;
	काष्ठा rb_node *n;
	पूर्णांक rc;

	spin_lock(&rgd->rd_rsspin);
	n = rgd->rd_rstree.rb_node;
	जबतक (n) अणु
		rs = rb_entry(n, काष्ठा gfs2_blkreserv, rs_node);
		rc = rs_cmp(block, length, rs);
		अगर (rc < 0)
			n = n->rb_left;
		अन्यथा अगर (rc > 0)
			n = n->rb_right;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (n) अणु
		जबतक (rs_cmp(block, length, rs) == 0 && rs != ignore_rs) अणु
			block = rs->rs_start + rs->rs_requested;
			n = n->rb_right;
			अगर (n == शून्य)
				अवरोध;
			rs = rb_entry(n, काष्ठा gfs2_blkreserv, rs_node);
		पूर्ण
	पूर्ण

	spin_unlock(&rgd->rd_rsspin);
	वापस block;
पूर्ण

/**
 * gfs2_reservation_check_and_update - Check क्रम reservations during block alloc
 * @rbm: The current position in the resource group
 * @rs: Our own reservation
 * @minext: The minimum extent length
 * @maxext: A poपूर्णांकer to the maximum extent काष्ठाure
 *
 * This checks the current position in the rgrp to see whether there is
 * a reservation covering this block. If not then this function is a
 * no-op. If there is, then the position is moved to the end of the
 * contiguous reservation(s) so that we are poपूर्णांकing at the first
 * non-reserved block.
 *
 * Returns: 0 अगर no reservation, 1 अगर @rbm has changed, otherwise an error
 */

अटल पूर्णांक gfs2_reservation_check_and_update(काष्ठा gfs2_rbm *rbm,
					     काष्ठा gfs2_blkreserv *rs,
					     u32 minext,
					     काष्ठा gfs2_extent *maxext)
अणु
	u64 block = gfs2_rbm_to_block(rbm);
	u32 extlen = 1;
	u64 nblock;

	/*
	 * If we have a minimum extent length, then skip over any extent
	 * which is less than the min extent length in size.
	 */
	अगर (minext > 1) अणु
		extlen = gfs2_मुक्त_extlen(rbm, minext);
		अगर (extlen <= maxext->len)
			जाओ fail;
	पूर्ण

	/*
	 * Check the extent which has been found against the reservations
	 * and skip अगर parts of it are alपढ़ोy reserved
	 */
	nblock = gfs2_next_unreserved_block(rbm->rgd, block, extlen, rs);
	अगर (nblock == block) अणु
		अगर (!minext || extlen >= minext)
			वापस 0;

		अगर (extlen > maxext->len) अणु
			maxext->len = extlen;
			maxext->rbm = *rbm;
		पूर्ण
	पूर्ण अन्यथा अणु
		u64 len = nblock - block;
		अगर (len >= (u64)1 << 32)
			वापस -E2BIG;
		extlen = len;
	पूर्ण
fail:
	अगर (gfs2_rbm_add(rbm, extlen))
		वापस -E2BIG;
	वापस 1;
पूर्ण

/**
 * gfs2_rbm_find - Look क्रम blocks of a particular state
 * @rbm: Value/result starting position and final position
 * @state: The state which we want to find
 * @minext: Poपूर्णांकer to the requested extent length
 *          This is updated to be the actual reservation size.
 * @rs: Our own reservation (शून्य to skip checking क्रम reservations)
 * @nowrap: Stop looking at the end of the rgrp, rather than wrapping
 *          around until we've reached the starting poपूर्णांक.
 *
 * Side effects:
 * - If looking क्रम मुक्त blocks, we set GBF_FULL on each biपंचांगap which
 *   has no मुक्त blocks in it.
 * - If looking क्रम मुक्त blocks, we set rd_extfail_pt on each rgrp which
 *   has come up लघु on a मुक्त block search.
 *
 * Returns: 0 on success, -ENOSPC अगर there is no block of the requested state
 */

अटल पूर्णांक gfs2_rbm_find(काष्ठा gfs2_rbm *rbm, u8 state, u32 *minext,
			 काष्ठा gfs2_blkreserv *rs, bool nowrap)
अणु
	bool scan_from_start = rbm->bii == 0 && rbm->offset == 0;
	काष्ठा buffer_head *bh;
	पूर्णांक last_bii;
	u32 offset;
	u8 *buffer;
	bool wrapped = false;
	पूर्णांक ret;
	काष्ठा gfs2_biपंचांगap *bi;
	काष्ठा gfs2_extent maxext = अणु .rbm.rgd = rbm->rgd, पूर्ण;

	/*
	 * Determine the last biपंचांगap to search.  If we're not starting at the
	 * beginning of a biपंचांगap, we need to search that biपंचांगap twice to scan
	 * the entire resource group.
	 */
	last_bii = rbm->bii - (rbm->offset == 0);

	जबतक(1) अणु
		bi = rbm_bi(rbm);
		अगर (test_bit(GBF_FULL, &bi->bi_flags) &&
		    (state == GFS2_BLKST_FREE))
			जाओ next_biपंचांगap;

		bh = bi->bi_bh;
		buffer = bh->b_data + bi->bi_offset;
		WARN_ON(!buffer_uptodate(bh));
		अगर (state != GFS2_BLKST_UNLINKED && bi->bi_clone)
			buffer = bi->bi_clone + bi->bi_offset;
		offset = gfs2_bitfit(buffer, bi->bi_bytes, rbm->offset, state);
		अगर (offset == BFITNOENT) अणु
			अगर (state == GFS2_BLKST_FREE && rbm->offset == 0)
				set_bit(GBF_FULL, &bi->bi_flags);
			जाओ next_biपंचांगap;
		पूर्ण
		rbm->offset = offset;
		अगर (!rs || !minext)
			वापस 0;

		ret = gfs2_reservation_check_and_update(rbm, rs, *minext,
							&maxext);
		अगर (ret == 0)
			वापस 0;
		अगर (ret > 0)
			जाओ next_iter;
		अगर (ret == -E2BIG) अणु
			rbm->bii = 0;
			rbm->offset = 0;
			जाओ res_covered_end_of_rgrp;
		पूर्ण
		वापस ret;

next_biपंचांगap:	/* Find next biपंचांगap in the rgrp */
		rbm->offset = 0;
		rbm->bii++;
		अगर (rbm->bii == rbm->rgd->rd_length)
			rbm->bii = 0;
res_covered_end_of_rgrp:
		अगर (rbm->bii == 0) अणु
			अगर (wrapped)
				अवरोध;
			wrapped = true;
			अगर (nowrap)
				अवरोध;
		पूर्ण
next_iter:
		/* Have we scanned the entire resource group? */
		अगर (wrapped && rbm->bii > last_bii)
			अवरोध;
	पूर्ण

	अगर (state != GFS2_BLKST_FREE)
		वापस -ENOSPC;

	/* If the extent was too small, and it's smaller than the smallest
	   to have failed beक्रमe, remember क्रम future reference that it's
	   useless to search this rgrp again क्रम this amount or more. */
	अगर (wrapped && (scan_from_start || rbm->bii > last_bii) &&
	    *minext < rbm->rgd->rd_extfail_pt)
		rbm->rgd->rd_extfail_pt = *minext - 1;

	/* If the maximum extent we found is big enough to fulfill the
	   minimum requirements, use it anyway. */
	अगर (maxext.len) अणु
		*rbm = maxext.rbm;
		*minext = maxext.len;
		वापस 0;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

/**
 * try_rgrp_unlink - Look क्रम any unlinked, allocated, but unused inodes
 * @rgd: The rgrp
 * @last_unlinked: block address of the last dinode we unlinked
 * @skip: block address we should explicitly not unlink
 *
 * Returns: 0 अगर no error
 *          The inode, अगर one has been found, in inode.
 */

अटल व्योम try_rgrp_unlink(काष्ठा gfs2_rgrpd *rgd, u64 *last_unlinked, u64 skip)
अणु
	u64 block;
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;
	काष्ठा gfs2_glock *gl;
	काष्ठा gfs2_inode *ip;
	पूर्णांक error;
	पूर्णांक found = 0;
	काष्ठा gfs2_rbm rbm = अणु .rgd = rgd, .bii = 0, .offset = 0 पूर्ण;

	जबतक (1) अणु
		error = gfs2_rbm_find(&rbm, GFS2_BLKST_UNLINKED, शून्य, शून्य,
				      true);
		अगर (error == -ENOSPC)
			अवरोध;
		अगर (WARN_ON_ONCE(error))
			अवरोध;

		block = gfs2_rbm_to_block(&rbm);
		अगर (gfs2_rbm_from_block(&rbm, block + 1))
			अवरोध;
		अगर (*last_unlinked != NO_BLOCK && block <= *last_unlinked)
			जारी;
		अगर (block == skip)
			जारी;
		*last_unlinked = block;

		error = gfs2_glock_get(sdp, block, &gfs2_iखोलो_glops, CREATE, &gl);
		अगर (error)
			जारी;

		/* If the inode is alपढ़ोy in cache, we can ignore it here
		 * because the existing inode disposal code will deal with
		 * it when all refs have gone away. Accessing gl_object like
		 * this is not safe in general. Here it is ok because we करो
		 * not dereference the poपूर्णांकer, and we only need an approx
		 * answer to whether it is शून्य or not.
		 */
		ip = gl->gl_object;

		अगर (ip || !gfs2_queue_delete_work(gl, 0))
			gfs2_glock_put(gl);
		अन्यथा
			found++;

		/* Limit reclaim to sensible number of tasks */
		अगर (found > NR_CPUS)
			वापस;
	पूर्ण

	rgd->rd_flags &= ~GFS2_RDF_CHECK;
	वापस;
पूर्ण

/**
 * gfs2_rgrp_congested - Use stats to figure out whether an rgrp is congested
 * @rgd: The rgrp in question
 * @loops: An indication of how picky we can be (0=very, 1=less so)
 *
 * This function uses the recently added glock statistics in order to
 * figure out whether a parciular resource group is suffering from
 * contention from multiple nodes. This is करोne purely on the basis
 * of timings, since this is the only data we have to work with and
 * our aim here is to reject a resource group which is highly contended
 * but (very important) not to करो this too often in order to ensure that
 * we करो not land up पूर्णांकroducing fragmentation by changing resource
 * groups when not actually required.
 *
 * The calculation is fairly simple, we want to know whether the SRTTB
 * (i.e. smoothed round trip समय क्रम blocking operations) to acquire
 * the lock क्रम this rgrp's glock is signअगरicantly greater than the
 * समय taken क्रम resource groups on average. We पूर्णांकroduce a margin in
 * the क्रमm of the variable @var which is computed as the sum of the two
 * respective variences, and multiplied by a factor depending on @loops
 * and whether we have a lot of data to base the decision on. This is
 * then tested against the square dअगरference of the means in order to
 * decide whether the result is statistically signअगरicant or not.
 *
 * Returns: A boolean verdict on the congestion status
 */

अटल bool gfs2_rgrp_congested(स्थिर काष्ठा gfs2_rgrpd *rgd, पूर्णांक loops)
अणु
	स्थिर काष्ठा gfs2_glock *gl = rgd->rd_gl;
	स्थिर काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा gfs2_lkstats *st;
	u64 r_dcount, l_dcount;
	u64 l_srttb, a_srttb = 0;
	s64 srttb_dअगरf;
	u64 sqr_dअगरf;
	u64 var;
	पूर्णांक cpu, nonzero = 0;

	preempt_disable();
	क्रम_each_present_cpu(cpu) अणु
		st = &per_cpu_ptr(sdp->sd_lkstats, cpu)->lkstats[LM_TYPE_RGRP];
		अगर (st->stats[GFS2_LKS_SRTTB]) अणु
			a_srttb += st->stats[GFS2_LKS_SRTTB];
			nonzero++;
		पूर्ण
	पूर्ण
	st = &this_cpu_ptr(sdp->sd_lkstats)->lkstats[LM_TYPE_RGRP];
	अगर (nonzero)
		करो_भाग(a_srttb, nonzero);
	r_dcount = st->stats[GFS2_LKS_DCOUNT];
	var = st->stats[GFS2_LKS_SRTTVARB] +
	      gl->gl_stats.stats[GFS2_LKS_SRTTVARB];
	preempt_enable();

	l_srttb = gl->gl_stats.stats[GFS2_LKS_SRTTB];
	l_dcount = gl->gl_stats.stats[GFS2_LKS_DCOUNT];

	अगर ((l_dcount < 1) || (r_dcount < 1) || (a_srttb == 0))
		वापस false;

	srttb_dअगरf = a_srttb - l_srttb;
	sqr_dअगरf = srttb_dअगरf * srttb_dअगरf;

	var *= 2;
	अगर (l_dcount < 8 || r_dcount < 8)
		var *= 2;
	अगर (loops == 1)
		var *= 2;

	वापस ((srttb_dअगरf < 0) && (sqr_dअगरf > var));
पूर्ण

/**
 * gfs2_rgrp_used_recently
 * @rs: The block reservation with the rgrp to test
 * @msecs: The समय limit in milliseconds
 *
 * Returns: True अगर the rgrp glock has been used within the समय limit
 */
अटल bool gfs2_rgrp_used_recently(स्थिर काष्ठा gfs2_blkreserv *rs,
				    u64 msecs)
अणु
	u64 tdअगरf;

	tdअगरf = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get_real(),
                            rs->rs_rgd->rd_gl->gl_dstamp));

	वापस tdअगरf > (msecs * 1000 * 1000);
पूर्ण

अटल u32 gfs2_orlov_skip(स्थिर काष्ठा gfs2_inode *ip)
अणु
	स्थिर काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	u32 skip;

	get_अक्रमom_bytes(&skip, माप(skip));
	वापस skip % sdp->sd_rgrps;
पूर्ण

अटल bool gfs2_select_rgrp(काष्ठा gfs2_rgrpd **pos, स्थिर काष्ठा gfs2_rgrpd *begin)
अणु
	काष्ठा gfs2_rgrpd *rgd = *pos;
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;

	rgd = gfs2_rgrpd_get_next(rgd);
	अगर (rgd == शून्य)
		rgd = gfs2_rgrpd_get_first(sdp);
	*pos = rgd;
	अगर (rgd != begin) /* If we didn't wrap */
		वापस true;
	वापस false;
पूर्ण

/**
 * fast_to_acquire - determine अगर a resource group will be fast to acquire
 * @rgd: The rgrp
 *
 * If this is one of our preferred rgrps, it should be quicker to acquire,
 * because we tried to set ourselves up as dlm lock master.
 */
अटल अंतरभूत पूर्णांक fast_to_acquire(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा gfs2_glock *gl = rgd->rd_gl;

	अगर (gl->gl_state != LM_ST_UNLOCKED && list_empty(&gl->gl_holders) &&
	    !test_bit(GLF_DEMOTE_IN_PROGRESS, &gl->gl_flags) &&
	    !test_bit(GLF_DEMOTE, &gl->gl_flags))
		वापस 1;
	अगर (rgd->rd_flags & GFS2_RDF_PREFERRED)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * gfs2_inplace_reserve - Reserve space in the fileप्रणाली
 * @ip: the inode to reserve space क्रम
 * @ap: the allocation parameters
 *
 * We try our best to find an rgrp that has at least ap->target blocks
 * available. After a couple of passes (loops == 2), the prospects of finding
 * such an rgrp diminish. At this stage, we वापस the first rgrp that has
 * at least ap->min_target blocks available.
 *
 * Returns: 0 on success,
 *          -ENOMEM अगर a suitable rgrp can't be found
 *          त्रुटि_सं otherwise
 */

पूर्णांक gfs2_inplace_reserve(काष्ठा gfs2_inode *ip, काष्ठा gfs2_alloc_parms *ap)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_rgrpd *begin = शून्य;
	काष्ठा gfs2_blkreserv *rs = &ip->i_res;
	पूर्णांक error = 0, flags = LM_FLAG_NODE_SCOPE;
	bool rg_locked;
	u64 last_unlinked = NO_BLOCK;
	u32 target = ap->target;
	पूर्णांक loops = 0;
	u32 मुक्त_blocks, blocks_available, skip = 0;

	BUG_ON(rs->rs_reserved);

	अगर (sdp->sd_args.ar_rgrplvb)
		flags |= GL_SKIP;
	अगर (gfs2_निश्चित_warn(sdp, target))
		वापस -EINVAL;
	अगर (gfs2_rs_active(rs)) अणु
		begin = rs->rs_rgd;
	पूर्ण अन्यथा अगर (rs->rs_rgd &&
		   rgrp_contains_block(rs->rs_rgd, ip->i_goal)) अणु
		begin = rs->rs_rgd;
	पूर्ण अन्यथा अणु
		check_and_update_goal(ip);
		rs->rs_rgd = begin = gfs2_blk2rgrpd(sdp, ip->i_goal, 1);
	पूर्ण
	अगर (S_ISसूची(ip->i_inode.i_mode) && (ap->aflags & GFS2_AF_ORLOV))
		skip = gfs2_orlov_skip(ip);
	अगर (rs->rs_rgd == शून्य)
		वापस -EBADSLT;

	जबतक (loops < 3) अणु
		काष्ठा gfs2_rgrpd *rgd;

		rg_locked = gfs2_glock_is_locked_by_me(rs->rs_rgd->rd_gl);
		अगर (rg_locked) अणु
			rgrp_lock_local(rs->rs_rgd);
		पूर्ण अन्यथा अणु
			अगर (skip && skip--)
				जाओ next_rgrp;
			अगर (!gfs2_rs_active(rs)) अणु
				अगर (loops == 0 &&
				    !fast_to_acquire(rs->rs_rgd))
					जाओ next_rgrp;
				अगर ((loops < 2) &&
				    gfs2_rgrp_used_recently(rs, 1000) &&
				    gfs2_rgrp_congested(rs->rs_rgd, loops))
					जाओ next_rgrp;
			पूर्ण
			error = gfs2_glock_nq_init(rs->rs_rgd->rd_gl,
						   LM_ST_EXCLUSIVE, flags,
						   &ip->i_rgd_gh);
			अगर (unlikely(error))
				वापस error;
			rgrp_lock_local(rs->rs_rgd);
			अगर (!gfs2_rs_active(rs) && (loops < 2) &&
			    gfs2_rgrp_congested(rs->rs_rgd, loops))
				जाओ skip_rgrp;
			अगर (sdp->sd_args.ar_rgrplvb) अणु
				error = update_rgrp_lvb(rs->rs_rgd);
				अगर (unlikely(error)) अणु
					rgrp_unlock_local(rs->rs_rgd);
					gfs2_glock_dq_uninit(&ip->i_rgd_gh);
					वापस error;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Skip unusable resource groups */
		अगर ((rs->rs_rgd->rd_flags & (GFS2_RGF_NOALLOC |
						 GFS2_RDF_ERROR)) ||
		    (loops == 0 && target > rs->rs_rgd->rd_extfail_pt))
			जाओ skip_rgrp;

		अगर (sdp->sd_args.ar_rgrplvb)
			gfs2_rgrp_bh_get(rs->rs_rgd);

		/* Get a reservation अगर we करोn't alपढ़ोy have one */
		अगर (!gfs2_rs_active(rs))
			rg_mblk_search(rs->rs_rgd, ip, ap);

		/* Skip rgrps when we can't get a reservation on first pass */
		अगर (!gfs2_rs_active(rs) && (loops < 1))
			जाओ check_rgrp;

		/* If rgrp has enough मुक्त space, use it */
		rgd = rs->rs_rgd;
		spin_lock(&rgd->rd_rsspin);
		मुक्त_blocks = rgd_मुक्त(rgd, rs);
		blocks_available = rgd->rd_मुक्त_clone - rgd->rd_reserved;
		अगर (मुक्त_blocks < target || blocks_available < target) अणु
			spin_unlock(&rgd->rd_rsspin);
			जाओ check_rgrp;
		पूर्ण
		rs->rs_reserved = ap->target;
		अगर (rs->rs_reserved > blocks_available)
			rs->rs_reserved = blocks_available;
		rgd->rd_reserved += rs->rs_reserved;
		spin_unlock(&rgd->rd_rsspin);
		rgrp_unlock_local(rs->rs_rgd);
		वापस 0;
check_rgrp:
		/* Check क्रम unlinked inodes which can be reclaimed */
		अगर (rs->rs_rgd->rd_flags & GFS2_RDF_CHECK)
			try_rgrp_unlink(rs->rs_rgd, &last_unlinked,
					ip->i_no_addr);
skip_rgrp:
		rgrp_unlock_local(rs->rs_rgd);

		/* Drop reservation, अगर we couldn't use reserved rgrp */
		अगर (gfs2_rs_active(rs))
			gfs2_rs_deltree(rs);

		/* Unlock rgrp अगर required */
		अगर (!rg_locked)
			gfs2_glock_dq_uninit(&ip->i_rgd_gh);
next_rgrp:
		/* Find the next rgrp, and जारी looking */
		अगर (gfs2_select_rgrp(&rs->rs_rgd, begin))
			जारी;
		अगर (skip)
			जारी;

		/* If we've scanned all the rgrps, but found no मुक्त blocks
		 * then this checks क्रम some less likely conditions beक्रमe
		 * trying again.
		 */
		loops++;
		/* Check that fs hasn't grown अगर writing to rindex */
		अगर (ip == GFS2_I(sdp->sd_rindex) && !sdp->sd_rindex_uptodate) अणु
			error = gfs2_ri_update(ip);
			अगर (error)
				वापस error;
		पूर्ण
		/* Flushing the log may release space */
		अगर (loops == 2) अणु
			अगर (ap->min_target)
				target = ap->min_target;
			gfs2_log_flush(sdp, शून्य, GFS2_LOG_HEAD_FLUSH_NORMAL |
				       GFS2_LFC_INPLACE_RESERVE);
		पूर्ण
	पूर्ण

	वापस -ENOSPC;
पूर्ण

/**
 * gfs2_inplace_release - release an inplace reservation
 * @ip: the inode the reservation was taken out on
 *
 * Release a reservation made by gfs2_inplace_reserve().
 */

व्योम gfs2_inplace_release(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_blkreserv *rs = &ip->i_res;

	अगर (rs->rs_reserved) अणु
		काष्ठा gfs2_rgrpd *rgd = rs->rs_rgd;

		spin_lock(&rgd->rd_rsspin);
		BUG_ON(rgd->rd_reserved < rs->rs_reserved);
		rgd->rd_reserved -= rs->rs_reserved;
		spin_unlock(&rgd->rd_rsspin);
		rs->rs_reserved = 0;
	पूर्ण
	अगर (gfs2_holder_initialized(&ip->i_rgd_gh))
		gfs2_glock_dq_uninit(&ip->i_rgd_gh);
पूर्ण

/**
 * gfs2_alloc_extent - allocate an extent from a given biपंचांगap
 * @rbm: the resource group inक्रमmation
 * @dinode: TRUE अगर the first block we allocate is क्रम a dinode
 * @n: The extent length (value/result)
 *
 * Add the biपंचांगap buffer to the transaction.
 * Set the found bits to @new_state to change block's allocation state.
 */
अटल व्योम gfs2_alloc_extent(स्थिर काष्ठा gfs2_rbm *rbm, bool dinode,
			     अचिन्हित पूर्णांक *n)
अणु
	काष्ठा gfs2_rbm pos = अणु .rgd = rbm->rgd, पूर्ण;
	स्थिर अचिन्हित पूर्णांक elen = *n;
	u64 block;
	पूर्णांक ret;

	*n = 1;
	block = gfs2_rbm_to_block(rbm);
	gfs2_trans_add_meta(rbm->rgd->rd_gl, rbm_bi(rbm)->bi_bh);
	gfs2_setbit(rbm, true, dinode ? GFS2_BLKST_DINODE : GFS2_BLKST_USED);
	block++;
	जबतक (*n < elen) अणु
		ret = gfs2_rbm_from_block(&pos, block);
		अगर (ret || gfs2_testbit(&pos, true) != GFS2_BLKST_FREE)
			अवरोध;
		gfs2_trans_add_meta(pos.rgd->rd_gl, rbm_bi(&pos)->bi_bh);
		gfs2_setbit(&pos, true, GFS2_BLKST_USED);
		(*n)++;
		block++;
	पूर्ण
पूर्ण

/**
 * rgblk_मुक्त - Change alloc state of given block(s)
 * @sdp: the fileप्रणाली
 * @rgd: the resource group the blocks are in
 * @bstart: the start of a run of blocks to मुक्त
 * @blen: the length of the block run (all must lie within ONE RG!)
 * @new_state: GFS2_BLKST_XXX the after-allocation block state
 */

अटल व्योम rgblk_मुक्त(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_rgrpd *rgd,
		       u64 bstart, u32 blen, अचिन्हित अक्षर new_state)
अणु
	काष्ठा gfs2_rbm rbm;
	काष्ठा gfs2_biपंचांगap *bi, *bi_prev = शून्य;

	rbm.rgd = rgd;
	अगर (WARN_ON_ONCE(gfs2_rbm_from_block(&rbm, bstart)))
		वापस;
	जबतक (blen--) अणु
		bi = rbm_bi(&rbm);
		अगर (bi != bi_prev) अणु
			अगर (!bi->bi_clone) अणु
				bi->bi_clone = kदो_स्मृति(bi->bi_bh->b_size,
						      GFP_NOFS | __GFP_NOFAIL);
				स_नकल(bi->bi_clone + bi->bi_offset,
				       bi->bi_bh->b_data + bi->bi_offset,
				       bi->bi_bytes);
			पूर्ण
			gfs2_trans_add_meta(rbm.rgd->rd_gl, bi->bi_bh);
			bi_prev = bi;
		पूर्ण
		gfs2_setbit(&rbm, false, new_state);
		gfs2_rbm_add(&rbm, 1);
	पूर्ण
पूर्ण

/**
 * gfs2_rgrp_dump - prपूर्णांक out an rgrp
 * @seq: The iterator
 * @rgd: The rgrp in question
 * @fs_id_buf: poपूर्णांकer to file प्रणाली id (अगर requested)
 *
 */

व्योम gfs2_rgrp_dump(काष्ठा seq_file *seq, काष्ठा gfs2_rgrpd *rgd,
		    स्थिर अक्षर *fs_id_buf)
अणु
	काष्ठा gfs2_blkreserv *trs;
	स्थिर काष्ठा rb_node *n;

	spin_lock(&rgd->rd_rsspin);
	gfs2_prपूर्णांक_dbg(seq, "%s R: n:%llu f:%02x b:%u/%u i:%u q:%u r:%u e:%u\n",
		       fs_id_buf,
		       (अचिन्हित दीर्घ दीर्घ)rgd->rd_addr, rgd->rd_flags,
		       rgd->rd_मुक्त, rgd->rd_मुक्त_clone, rgd->rd_dinodes,
		       rgd->rd_requested, rgd->rd_reserved, rgd->rd_extfail_pt);
	अगर (rgd->rd_sbd->sd_args.ar_rgrplvb) अणु
		काष्ठा gfs2_rgrp_lvb *rgl = rgd->rd_rgl;

		gfs2_prपूर्णांक_dbg(seq, "%s  L: f:%02x b:%u i:%u\n", fs_id_buf,
			       be32_to_cpu(rgl->rl_flags),
			       be32_to_cpu(rgl->rl_मुक्त),
			       be32_to_cpu(rgl->rl_dinodes));
	पूर्ण
	क्रम (n = rb_first(&rgd->rd_rstree); n; n = rb_next(&trs->rs_node)) अणु
		trs = rb_entry(n, काष्ठा gfs2_blkreserv, rs_node);
		dump_rs(seq, trs, fs_id_buf);
	पूर्ण
	spin_unlock(&rgd->rd_rsspin);
पूर्ण

अटल व्योम gfs2_rgrp_error(काष्ठा gfs2_rgrpd *rgd)
अणु
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;
	अक्षर fs_id_buf[माप(sdp->sd_fsname) + 7];

	fs_warn(sdp, "rgrp %llu has an error, marking it readonly until umount\n",
		(अचिन्हित दीर्घ दीर्घ)rgd->rd_addr);
	fs_warn(sdp, "umount on all nodes and run fsck.gfs2 to fix the error\n");
	प्र_लिखो(fs_id_buf, "fsid=%s: ", sdp->sd_fsname);
	gfs2_rgrp_dump(शून्य, rgd, fs_id_buf);
	rgd->rd_flags |= GFS2_RDF_ERROR;
पूर्ण

/**
 * gfs2_adjust_reservation - Adjust (or हटाओ) a reservation after allocation
 * @ip: The inode we have just allocated blocks क्रम
 * @rbm: The start of the allocated blocks
 * @len: The extent length
 *
 * Adjusts a reservation after an allocation has taken place. If the
 * reservation करोes not match the allocation, or अगर it is now empty
 * then it is हटाओd.
 */

अटल व्योम gfs2_adjust_reservation(काष्ठा gfs2_inode *ip,
				    स्थिर काष्ठा gfs2_rbm *rbm, अचिन्हित len)
अणु
	काष्ठा gfs2_blkreserv *rs = &ip->i_res;
	काष्ठा gfs2_rgrpd *rgd = rbm->rgd;

	BUG_ON(rs->rs_reserved < len);
	rs->rs_reserved -= len;
	अगर (gfs2_rs_active(rs)) अणु
		u64 start = gfs2_rbm_to_block(rbm);

		अगर (rs->rs_start == start) अणु
			अचिन्हित पूर्णांक rlen;

			rs->rs_start += len;
			rlen = min(rs->rs_requested, len);
			rs->rs_requested -= rlen;
			rgd->rd_requested -= rlen;
			trace_gfs2_rs(rs, TRACE_RS_CLAIM);
			अगर (rs->rs_start < rgd->rd_data0 + rgd->rd_data &&
			    rs->rs_requested)
				वापस;
			/* We used up our block reservation, so we should
			   reserve more blocks next समय. */
			atomic_add(RGRP_RSRV_ADDBLKS, &ip->i_sizehपूर्णांक);
		पूर्ण
		__rs_deltree(rs);
	पूर्ण
पूर्ण

/**
 * gfs2_set_alloc_start - Set starting poपूर्णांक क्रम block allocation
 * @rbm: The rbm which will be set to the required location
 * @ip: The gfs2 inode
 * @dinode: Flag to say अगर allocation includes a new inode
 *
 * This sets the starting poपूर्णांक from the reservation अगर one is active
 * otherwise it falls back to guessing a start poपूर्णांक based on the
 * inode's goal block or the last allocation poपूर्णांक in the rgrp.
 */

अटल व्योम gfs2_set_alloc_start(काष्ठा gfs2_rbm *rbm,
				 स्थिर काष्ठा gfs2_inode *ip, bool dinode)
अणु
	u64 goal;

	अगर (gfs2_rs_active(&ip->i_res)) अणु
		goal = ip->i_res.rs_start;
	पूर्ण अन्यथा अणु
		अगर (!dinode && rgrp_contains_block(rbm->rgd, ip->i_goal))
			goal = ip->i_goal;
		अन्यथा
			goal = rbm->rgd->rd_last_alloc + rbm->rgd->rd_data0;
	पूर्ण
	अगर (WARN_ON_ONCE(gfs2_rbm_from_block(rbm, goal))) अणु
		rbm->bii = 0;
		rbm->offset = 0;
	पूर्ण
पूर्ण

/**
 * gfs2_alloc_blocks - Allocate one or more blocks of data and/or a dinode
 * @ip: the inode to allocate the block क्रम
 * @bn: Used to वापस the starting block number
 * @nblocks: requested number of blocks/extent length (value/result)
 * @dinode: 1 अगर we're allocating a dinode block, अन्यथा 0
 * @generation: the generation number of the inode
 *
 * Returns: 0 or error
 */

पूर्णांक gfs2_alloc_blocks(काष्ठा gfs2_inode *ip, u64 *bn, अचिन्हित पूर्णांक *nblocks,
		      bool dinode, u64 *generation)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा buffer_head *dibh;
	काष्ठा gfs2_rbm rbm = अणु .rgd = ip->i_res.rs_rgd, पूर्ण;
	u64 block; /* block, within the file प्रणाली scope */
	u32 minext = 1;
	पूर्णांक error = -ENOSPC;

	BUG_ON(ip->i_res.rs_reserved < *nblocks);

	rgrp_lock_local(rbm.rgd);
	अगर (gfs2_rs_active(&ip->i_res)) अणु
		gfs2_set_alloc_start(&rbm, ip, dinode);
		error = gfs2_rbm_find(&rbm, GFS2_BLKST_FREE, &minext, &ip->i_res, false);
	पूर्ण
	अगर (error == -ENOSPC) अणु
		gfs2_set_alloc_start(&rbm, ip, dinode);
		error = gfs2_rbm_find(&rbm, GFS2_BLKST_FREE, &minext, शून्य, false);
	पूर्ण

	/* Since all blocks are reserved in advance, this shouldn't happen */
	अगर (error) अणु
		fs_warn(sdp, "inum=%llu error=%d, nblocks=%u, full=%d fail_pt=%d\n",
			(अचिन्हित दीर्घ दीर्घ)ip->i_no_addr, error, *nblocks,
			test_bit(GBF_FULL, &rbm.rgd->rd_bits->bi_flags),
			rbm.rgd->rd_extfail_pt);
		जाओ rgrp_error;
	पूर्ण

	gfs2_alloc_extent(&rbm, dinode, nblocks);
	block = gfs2_rbm_to_block(&rbm);
	rbm.rgd->rd_last_alloc = block - rbm.rgd->rd_data0;
	अगर (!dinode) अणु
		ip->i_goal = block + *nblocks - 1;
		error = gfs2_meta_inode_buffer(ip, &dibh);
		अगर (error == 0) अणु
			काष्ठा gfs2_dinode *di =
				(काष्ठा gfs2_dinode *)dibh->b_data;
			gfs2_trans_add_meta(ip->i_gl, dibh);
			di->di_goal_meta = di->di_goal_data =
				cpu_to_be64(ip->i_goal);
			brअन्यथा(dibh);
		पूर्ण
	पूर्ण
	spin_lock(&rbm.rgd->rd_rsspin);
	gfs2_adjust_reservation(ip, &rbm, *nblocks);
	अगर (rbm.rgd->rd_मुक्त < *nblocks || rbm.rgd->rd_reserved < *nblocks) अणु
		fs_warn(sdp, "nblocks=%u\n", *nblocks);
		spin_unlock(&rbm.rgd->rd_rsspin);
		जाओ rgrp_error;
	पूर्ण
	BUG_ON(rbm.rgd->rd_reserved < *nblocks);
	BUG_ON(rbm.rgd->rd_मुक्त_clone < *nblocks);
	BUG_ON(rbm.rgd->rd_मुक्त < *nblocks);
	rbm.rgd->rd_reserved -= *nblocks;
	rbm.rgd->rd_मुक्त_clone -= *nblocks;
	rbm.rgd->rd_मुक्त -= *nblocks;
	spin_unlock(&rbm.rgd->rd_rsspin);
	अगर (dinode) अणु
		rbm.rgd->rd_dinodes++;
		*generation = rbm.rgd->rd_igeneration++;
		अगर (*generation == 0)
			*generation = rbm.rgd->rd_igeneration++;
	पूर्ण

	gfs2_trans_add_meta(rbm.rgd->rd_gl, rbm.rgd->rd_bits[0].bi_bh);
	gfs2_rgrp_out(rbm.rgd, rbm.rgd->rd_bits[0].bi_bh->b_data);
	rgrp_unlock_local(rbm.rgd);

	gfs2_statfs_change(sdp, 0, -(s64)*nblocks, dinode ? 1 : 0);
	अगर (dinode)
		gfs2_trans_हटाओ_revoke(sdp, block, *nblocks);

	gfs2_quota_change(ip, *nblocks, ip->i_inode.i_uid, ip->i_inode.i_gid);

	trace_gfs2_block_alloc(ip, rbm.rgd, block, *nblocks,
			       dinode ? GFS2_BLKST_DINODE : GFS2_BLKST_USED);
	*bn = block;
	वापस 0;

rgrp_error:
	rgrp_unlock_local(rbm.rgd);
	gfs2_rgrp_error(rbm.rgd);
	वापस -EIO;
पूर्ण

/**
 * __gfs2_मुक्त_blocks - मुक्त a contiguous run of block(s)
 * @ip: the inode these blocks are being मुक्तd from
 * @rgd: the resource group the blocks are in
 * @bstart: first block of a run of contiguous blocks
 * @blen: the length of the block run
 * @meta: 1 अगर the blocks represent metadata
 *
 */

व्योम __gfs2_मुक्त_blocks(काष्ठा gfs2_inode *ip, काष्ठा gfs2_rgrpd *rgd,
			u64 bstart, u32 blen, पूर्णांक meta)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	rgrp_lock_local(rgd);
	rgblk_मुक्त(sdp, rgd, bstart, blen, GFS2_BLKST_FREE);
	trace_gfs2_block_alloc(ip, rgd, bstart, blen, GFS2_BLKST_FREE);
	rgd->rd_मुक्त += blen;
	rgd->rd_flags &= ~GFS2_RGF_TRIMMED;
	gfs2_trans_add_meta(rgd->rd_gl, rgd->rd_bits[0].bi_bh);
	gfs2_rgrp_out(rgd, rgd->rd_bits[0].bi_bh->b_data);
	rgrp_unlock_local(rgd);

	/* Directories keep their data in the metadata address space */
	अगर (meta || ip->i_depth || gfs2_is_jdata(ip))
		gfs2_journal_wipe(ip, bstart, blen);
पूर्ण

/**
 * gfs2_मुक्त_meta - मुक्त a contiguous run of data block(s)
 * @ip: the inode these blocks are being मुक्तd from
 * @rgd: the resource group the blocks are in
 * @bstart: first block of a run of contiguous blocks
 * @blen: the length of the block run
 *
 */

व्योम gfs2_मुक्त_meta(काष्ठा gfs2_inode *ip, काष्ठा gfs2_rgrpd *rgd,
		    u64 bstart, u32 blen)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	__gfs2_मुक्त_blocks(ip, rgd, bstart, blen, 1);
	gfs2_statfs_change(sdp, 0, +blen, 0);
	gfs2_quota_change(ip, -(s64)blen, ip->i_inode.i_uid, ip->i_inode.i_gid);
पूर्ण

व्योम gfs2_unlink_di(काष्ठा inode *inode)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_rgrpd *rgd;
	u64 blkno = ip->i_no_addr;

	rgd = gfs2_blk2rgrpd(sdp, blkno, true);
	अगर (!rgd)
		वापस;
	rgrp_lock_local(rgd);
	rgblk_मुक्त(sdp, rgd, blkno, 1, GFS2_BLKST_UNLINKED);
	trace_gfs2_block_alloc(ip, rgd, blkno, 1, GFS2_BLKST_UNLINKED);
	gfs2_trans_add_meta(rgd->rd_gl, rgd->rd_bits[0].bi_bh);
	gfs2_rgrp_out(rgd, rgd->rd_bits[0].bi_bh->b_data);
	be32_add_cpu(&rgd->rd_rgl->rl_unlinked, 1);
	rgrp_unlock_local(rgd);
पूर्ण

व्योम gfs2_मुक्त_di(काष्ठा gfs2_rgrpd *rgd, काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = rgd->rd_sbd;

	rgrp_lock_local(rgd);
	rgblk_मुक्त(sdp, rgd, ip->i_no_addr, 1, GFS2_BLKST_FREE);
	अगर (!rgd->rd_dinodes)
		gfs2_consist_rgrpd(rgd);
	rgd->rd_dinodes--;
	rgd->rd_मुक्त++;

	gfs2_trans_add_meta(rgd->rd_gl, rgd->rd_bits[0].bi_bh);
	gfs2_rgrp_out(rgd, rgd->rd_bits[0].bi_bh->b_data);
	rgrp_unlock_local(rgd);
	be32_add_cpu(&rgd->rd_rgl->rl_unlinked, -1);

	gfs2_statfs_change(sdp, 0, +1, -1);
	trace_gfs2_block_alloc(ip, rgd, ip->i_no_addr, 1, GFS2_BLKST_FREE);
	gfs2_quota_change(ip, -1, ip->i_inode.i_uid, ip->i_inode.i_gid);
	gfs2_journal_wipe(ip, ip->i_no_addr, 1);
पूर्ण

/**
 * gfs2_check_blk_type - Check the type of a block
 * @sdp: The superblock
 * @no_addr: The block number to check
 * @type: The block type we are looking क्रम
 *
 * The inode glock of @no_addr must be held.  The @type to check क्रम is either
 * GFS2_BLKST_DINODE or GFS2_BLKST_UNLINKED; checking क्रम type GFS2_BLKST_FREE
 * or GFS2_BLKST_USED would make no sense.
 *
 * Returns: 0 अगर the block type matches the expected type
 *          -ESTALE अगर it करोesn't match
 *          or -ve त्रुटि_सं अगर something went wrong जबतक checking
 */

पूर्णांक gfs2_check_blk_type(काष्ठा gfs2_sbd *sdp, u64 no_addr, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gfs2_rgrpd *rgd;
	काष्ठा gfs2_holder rgd_gh;
	काष्ठा gfs2_rbm rbm;
	पूर्णांक error = -EINVAL;

	rgd = gfs2_blk2rgrpd(sdp, no_addr, 1);
	अगर (!rgd)
		जाओ fail;

	error = gfs2_glock_nq_init(rgd->rd_gl, LM_ST_SHARED, 0, &rgd_gh);
	अगर (error)
		जाओ fail;

	rbm.rgd = rgd;
	error = gfs2_rbm_from_block(&rbm, no_addr);
	अगर (!WARN_ON_ONCE(error)) अणु
		/*
		 * No need to take the local resource group lock here; the
		 * inode glock of @no_addr provides the necessary
		 * synchronization in हाल the block is an inode.  (In हाल
		 * the block is not an inode, the block type will not match
		 * the @type we are looking क्रम.)
		 */
		अगर (gfs2_testbit(&rbm, false) != type)
			error = -ESTALE;
	पूर्ण

	gfs2_glock_dq_uninit(&rgd_gh);

fail:
	वापस error;
पूर्ण

/**
 * gfs2_rlist_add - add a RG to a list of RGs
 * @ip: the inode
 * @rlist: the list of resource groups
 * @block: the block
 *
 * Figure out what RG a block beदीर्घs to and add that RG to the list
 *
 * FIXME: Don't use NOFAIL
 *
 */

व्योम gfs2_rlist_add(काष्ठा gfs2_inode *ip, काष्ठा gfs2_rgrp_list *rlist,
		    u64 block)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_rgrpd *rgd;
	काष्ठा gfs2_rgrpd **पंचांगp;
	अचिन्हित पूर्णांक new_space;
	अचिन्हित पूर्णांक x;

	अगर (gfs2_निश्चित_warn(sdp, !rlist->rl_ghs))
		वापस;

	/*
	 * The resource group last accessed is kept in the last position.
	 */

	अगर (rlist->rl_rgrps) अणु
		rgd = rlist->rl_rgd[rlist->rl_rgrps - 1];
		अगर (rgrp_contains_block(rgd, block))
			वापस;
		rgd = gfs2_blk2rgrpd(sdp, block, 1);
	पूर्ण अन्यथा अणु
		rgd = ip->i_res.rs_rgd;
		अगर (!rgd || !rgrp_contains_block(rgd, block))
			rgd = gfs2_blk2rgrpd(sdp, block, 1);
	पूर्ण

	अगर (!rgd) अणु
		fs_err(sdp, "rlist_add: no rgrp for block %llu\n",
		       (अचिन्हित दीर्घ दीर्घ)block);
		वापस;
	पूर्ण

	क्रम (x = 0; x < rlist->rl_rgrps; x++) अणु
		अगर (rlist->rl_rgd[x] == rgd) अणु
			swap(rlist->rl_rgd[x],
			     rlist->rl_rgd[rlist->rl_rgrps - 1]);
			वापस;
		पूर्ण
	पूर्ण

	अगर (rlist->rl_rgrps == rlist->rl_space) अणु
		new_space = rlist->rl_space + 10;

		पंचांगp = kसुस्मृति(new_space, माप(काष्ठा gfs2_rgrpd *),
			      GFP_NOFS | __GFP_NOFAIL);

		अगर (rlist->rl_rgd) अणु
			स_नकल(पंचांगp, rlist->rl_rgd,
			       rlist->rl_space * माप(काष्ठा gfs2_rgrpd *));
			kमुक्त(rlist->rl_rgd);
		पूर्ण

		rlist->rl_space = new_space;
		rlist->rl_rgd = पंचांगp;
	पूर्ण

	rlist->rl_rgd[rlist->rl_rgrps++] = rgd;
पूर्ण

/**
 * gfs2_rlist_alloc - all RGs have been added to the rlist, now allocate
 *      and initialize an array of glock holders क्रम them
 * @rlist: the list of resource groups
 *
 * FIXME: Don't use NOFAIL
 *
 */

व्योम gfs2_rlist_alloc(काष्ठा gfs2_rgrp_list *rlist)
अणु
	अचिन्हित पूर्णांक x;

	rlist->rl_ghs = kदो_स्मृति_array(rlist->rl_rgrps,
				      माप(काष्ठा gfs2_holder),
				      GFP_NOFS | __GFP_NOFAIL);
	क्रम (x = 0; x < rlist->rl_rgrps; x++)
		gfs2_holder_init(rlist->rl_rgd[x]->rd_gl, LM_ST_EXCLUSIVE,
				 LM_FLAG_NODE_SCOPE, &rlist->rl_ghs[x]);
पूर्ण

/**
 * gfs2_rlist_मुक्त - मुक्त a resource group list
 * @rlist: the list of resource groups
 *
 */

व्योम gfs2_rlist_मुक्त(काष्ठा gfs2_rgrp_list *rlist)
अणु
	अचिन्हित पूर्णांक x;

	kमुक्त(rlist->rl_rgd);

	अगर (rlist->rl_ghs) अणु
		क्रम (x = 0; x < rlist->rl_rgrps; x++)
			gfs2_holder_uninit(&rlist->rl_ghs[x]);
		kमुक्त(rlist->rl_ghs);
		rlist->rl_ghs = शून्य;
	पूर्ण
पूर्ण

व्योम rgrp_lock_local(काष्ठा gfs2_rgrpd *rgd)
अणु
	BUG_ON(!gfs2_glock_is_held_excl(rgd->rd_gl) &&
	       !test_bit(SDF_NORECOVERY, &rgd->rd_sbd->sd_flags));
	mutex_lock(&rgd->rd_mutex);
पूर्ण

व्योम rgrp_unlock_local(काष्ठा gfs2_rgrpd *rgd)
अणु
	mutex_unlock(&rgd->rd_mutex);
पूर्ण
