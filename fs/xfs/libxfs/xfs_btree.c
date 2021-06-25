<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_log.h"
#समावेश "xfs_btree_staging.h"

/*
 * Cursor allocation zone.
 */
kmem_zone_t	*xfs_btree_cur_zone;

/*
 * Btree magic numbers.
 */
अटल स्थिर uपूर्णांक32_t xfs_magics[2][XFS_BTNUM_MAX] = अणु
	अणु XFS_ABTB_MAGIC, XFS_ABTC_MAGIC, 0, XFS_BMAP_MAGIC, XFS_IBT_MAGIC,
	  XFS_FIBT_MAGIC, 0 पूर्ण,
	अणु XFS_ABTB_CRC_MAGIC, XFS_ABTC_CRC_MAGIC, XFS_RMAP_CRC_MAGIC,
	  XFS_BMAP_CRC_MAGIC, XFS_IBT_CRC_MAGIC, XFS_FIBT_CRC_MAGIC,
	  XFS_REFC_CRC_MAGIC पूर्ण
पूर्ण;

uपूर्णांक32_t
xfs_btree_magic(
	पूर्णांक			crc,
	xfs_btnum_t		btnum)
अणु
	uपूर्णांक32_t		magic = xfs_magics[crc][btnum];

	/* Ensure we asked क्रम crc क्रम crc-only magics. */
	ASSERT(magic != 0);
	वापस magic;
पूर्ण

/*
 * Check a दीर्घ btree block header.  Return the address of the failing check,
 * or शून्य अगर everything is ok.
 */
xfs_failaddr_t
__xfs_btree_check_lblock(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	पूर्णांक			level,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	xfs_btnum_t		btnum = cur->bc_btnum;
	पूर्णांक			crc = xfs_sb_version_hascrc(&mp->m_sb);

	अगर (crc) अणु
		अगर (!uuid_equal(&block->bb_u.l.bb_uuid, &mp->m_sb.sb_meta_uuid))
			वापस __this_address;
		अगर (block->bb_u.l.bb_blkno !=
		    cpu_to_be64(bp ? bp->b_bn : XFS_BUF_DADDR_शून्य))
			वापस __this_address;
		अगर (block->bb_u.l.bb_pad != cpu_to_be32(0))
			वापस __this_address;
	पूर्ण

	अगर (be32_to_cpu(block->bb_magic) != xfs_btree_magic(crc, btnum))
		वापस __this_address;
	अगर (be16_to_cpu(block->bb_level) != level)
		वापस __this_address;
	अगर (be16_to_cpu(block->bb_numrecs) >
	    cur->bc_ops->get_maxrecs(cur, level))
		वापस __this_address;
	अगर (block->bb_u.l.bb_leftsib != cpu_to_be64(शून्यFSBLOCK) &&
	    !xfs_btree_check_lptr(cur, be64_to_cpu(block->bb_u.l.bb_leftsib),
			level + 1))
		वापस __this_address;
	अगर (block->bb_u.l.bb_rightsib != cpu_to_be64(शून्यFSBLOCK) &&
	    !xfs_btree_check_lptr(cur, be64_to_cpu(block->bb_u.l.bb_rightsib),
			level + 1))
		वापस __this_address;

	वापस शून्य;
पूर्ण

/* Check a दीर्घ btree block header. */
अटल पूर्णांक
xfs_btree_check_lblock(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	पूर्णांक			level,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	xfs_failaddr_t		fa;

	fa = __xfs_btree_check_lblock(cur, block, level, bp);
	अगर (XFS_IS_CORRUPT(mp, fa != शून्य) ||
	    XFS_TEST_ERROR(false, mp, XFS_ERRTAG_BTREE_CHECK_LBLOCK)) अणु
		अगर (bp)
			trace_xfs_btree_corrupt(bp, _RET_IP_);
		वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Check a लघु btree block header.  Return the address of the failing check,
 * or शून्य अगर everything is ok.
 */
xfs_failaddr_t
__xfs_btree_check_sblock(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	पूर्णांक			level,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	xfs_btnum_t		btnum = cur->bc_btnum;
	पूर्णांक			crc = xfs_sb_version_hascrc(&mp->m_sb);

	अगर (crc) अणु
		अगर (!uuid_equal(&block->bb_u.s.bb_uuid, &mp->m_sb.sb_meta_uuid))
			वापस __this_address;
		अगर (block->bb_u.s.bb_blkno !=
		    cpu_to_be64(bp ? bp->b_bn : XFS_BUF_DADDR_शून्य))
			वापस __this_address;
	पूर्ण

	अगर (be32_to_cpu(block->bb_magic) != xfs_btree_magic(crc, btnum))
		वापस __this_address;
	अगर (be16_to_cpu(block->bb_level) != level)
		वापस __this_address;
	अगर (be16_to_cpu(block->bb_numrecs) >
	    cur->bc_ops->get_maxrecs(cur, level))
		वापस __this_address;
	अगर (block->bb_u.s.bb_leftsib != cpu_to_be32(शून्यAGBLOCK) &&
	    !xfs_btree_check_sptr(cur, be32_to_cpu(block->bb_u.s.bb_leftsib),
			level + 1))
		वापस __this_address;
	अगर (block->bb_u.s.bb_rightsib != cpu_to_be32(शून्यAGBLOCK) &&
	    !xfs_btree_check_sptr(cur, be32_to_cpu(block->bb_u.s.bb_rightsib),
			level + 1))
		वापस __this_address;

	वापस शून्य;
पूर्ण

/* Check a लघु btree block header. */
STATIC पूर्णांक
xfs_btree_check_sblock(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	पूर्णांक			level,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	xfs_failaddr_t		fa;

	fa = __xfs_btree_check_sblock(cur, block, level, bp);
	अगर (XFS_IS_CORRUPT(mp, fa != शून्य) ||
	    XFS_TEST_ERROR(false, mp, XFS_ERRTAG_BTREE_CHECK_SBLOCK)) अणु
		अगर (bp)
			trace_xfs_btree_corrupt(bp, _RET_IP_);
		वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Debug routine: check that block header is ok.
 */
पूर्णांक
xfs_btree_check_block(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	काष्ठा xfs_btree_block	*block,	/* generic btree block poपूर्णांकer */
	पूर्णांक			level,	/* level of the btree block */
	काष्ठा xfs_buf		*bp)	/* buffer containing block, अगर any */
अणु
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		वापस xfs_btree_check_lblock(cur, block, level, bp);
	अन्यथा
		वापस xfs_btree_check_sblock(cur, block, level, bp);
पूर्ण

/* Check that this दीर्घ poपूर्णांकer is valid and poपूर्णांकs within the fs. */
bool
xfs_btree_check_lptr(
	काष्ठा xfs_btree_cur	*cur,
	xfs_fsblock_t		fsbno,
	पूर्णांक			level)
अणु
	अगर (level <= 0)
		वापस false;
	वापस xfs_verअगरy_fsbno(cur->bc_mp, fsbno);
पूर्ण

/* Check that this लघु poपूर्णांकer is valid and poपूर्णांकs within the AG. */
bool
xfs_btree_check_sptr(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		agbno,
	पूर्णांक			level)
अणु
	अगर (level <= 0)
		वापस false;
	वापस xfs_verअगरy_agbno(cur->bc_mp, cur->bc_ag.agno, agbno);
पूर्ण

/*
 * Check that a given (indexed) btree poपूर्णांकer at a certain level of a
 * btree is valid and करोesn't poपूर्णांक past where it should.
 */
अटल पूर्णांक
xfs_btree_check_ptr(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr,
	पूर्णांक			index,
	पूर्णांक			level)
अणु
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS) अणु
		अगर (xfs_btree_check_lptr(cur, be64_to_cpu((&ptr->l)[index]),
				level))
			वापस 0;
		xfs_err(cur->bc_mp,
"Inode %llu fork %d: Corrupt btree %d pointer at level %d index %d.",
				cur->bc_ino.ip->i_ino,
				cur->bc_ino.whichविभाजन, cur->bc_btnum,
				level, index);
	पूर्ण अन्यथा अणु
		अगर (xfs_btree_check_sptr(cur, be32_to_cpu((&ptr->s)[index]),
				level))
			वापस 0;
		xfs_err(cur->bc_mp,
"AG %u: Corrupt btree %d pointer at level %d index %d.",
				cur->bc_ag.agno, cur->bc_btnum,
				level, index);
	पूर्ण

	वापस -EFSCORRUPTED;
पूर्ण

#अगर_घोषित DEBUG
# define xfs_btree_debug_check_ptr	xfs_btree_check_ptr
#अन्यथा
# define xfs_btree_debug_check_ptr(...)	(0)
#पूर्ण_अगर

/*
 * Calculate CRC on the whole btree block and stuff it पूर्णांकo the
 * दीर्घ-क्रमm btree header.
 *
 * Prior to calculting the CRC, pull the LSN out of the buffer log item and put
 * it पूर्णांकo the buffer so recovery knows what the last modअगरication was that made
 * it to disk.
 */
व्योम
xfs_btree_lblock_calc_crc(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	अगर (!xfs_sb_version_hascrc(&bp->b_mount->m_sb))
		वापस;
	अगर (bip)
		block->bb_u.l.bb_lsn = cpu_to_be64(bip->bli_item.li_lsn);
	xfs_buf_update_cksum(bp, XFS_BTREE_LBLOCK_CRC_OFF);
पूर्ण

bool
xfs_btree_lblock_verअगरy_crc(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	काष्ठा xfs_mount	*mp = bp->b_mount;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		अगर (!xfs_log_check_lsn(mp, be64_to_cpu(block->bb_u.l.bb_lsn)))
			वापस false;
		वापस xfs_buf_verअगरy_cksum(bp, XFS_BTREE_LBLOCK_CRC_OFF);
	पूर्ण

	वापस true;
पूर्ण

/*
 * Calculate CRC on the whole btree block and stuff it पूर्णांकo the
 * लघु-क्रमm btree header.
 *
 * Prior to calculting the CRC, pull the LSN out of the buffer log item and put
 * it पूर्णांकo the buffer so recovery knows what the last modअगरication was that made
 * it to disk.
 */
व्योम
xfs_btree_sblock_calc_crc(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	अगर (!xfs_sb_version_hascrc(&bp->b_mount->m_sb))
		वापस;
	अगर (bip)
		block->bb_u.s.bb_lsn = cpu_to_be64(bip->bli_item.li_lsn);
	xfs_buf_update_cksum(bp, XFS_BTREE_SBLOCK_CRC_OFF);
पूर्ण

bool
xfs_btree_sblock_verअगरy_crc(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_btree_block  *block = XFS_BUF_TO_BLOCK(bp);
	काष्ठा xfs_mount	*mp = bp->b_mount;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		अगर (!xfs_log_check_lsn(mp, be64_to_cpu(block->bb_u.s.bb_lsn)))
			वापस false;
		वापस xfs_buf_verअगरy_cksum(bp, XFS_BTREE_SBLOCK_CRC_OFF);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
xfs_btree_मुक्त_block(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp)
अणु
	पूर्णांक			error;

	error = cur->bc_ops->मुक्त_block(cur, bp);
	अगर (!error) अणु
		xfs_trans_binval(cur->bc_tp, bp);
		XFS_BTREE_STATS_INC(cur, मुक्त);
	पूर्ण
	वापस error;
पूर्ण

/*
 * Delete the btree cursor.
 */
व्योम
xfs_btree_del_cursor(
	काष्ठा xfs_btree_cur	*cur,		/* btree cursor */
	पूर्णांक			error)		/* del because of error */
अणु
	पूर्णांक			i;		/* btree level */

	/*
	 * Clear the buffer poपूर्णांकers and release the buffers. If we're करोing
	 * this because of an error, inspect all of the entries in the bc_bufs
	 * array क्रम buffers to be unlocked. This is because some of the btree
	 * code works from level n करोwn to 0, and अगर we get an error aदीर्घ the
	 * way we won't have initialized all the entries करोwn to 0.
	 */
	क्रम (i = 0; i < cur->bc_nlevels; i++) अणु
		अगर (cur->bc_bufs[i])
			xfs_trans_brअन्यथा(cur->bc_tp, cur->bc_bufs[i]);
		अन्यथा अगर (!error)
			अवरोध;
	पूर्ण

	ASSERT(cur->bc_btnum != XFS_BTNUM_BMAP || cur->bc_ino.allocated == 0 ||
	       XFS_FORCED_SHUTDOWN(cur->bc_mp));
	अगर (unlikely(cur->bc_flags & XFS_BTREE_STAGING))
		kmem_मुक्त(cur->bc_ops);
	kmem_cache_मुक्त(xfs_btree_cur_zone, cur);
पूर्ण

/*
 * Duplicate the btree cursor.
 * Allocate a new one, copy the record, re-get the buffers.
 */
पूर्णांक					/* error */
xfs_btree_dup_cursor(
	xfs_btree_cur_t	*cur,		/* input cursor */
	xfs_btree_cur_t	**ncur)		/* output cursor */
अणु
	काष्ठा xfs_buf	*bp;		/* btree block's buffer poपूर्णांकer */
	पूर्णांक		error;		/* error वापस value */
	पूर्णांक		i;		/* level number of btree block */
	xfs_mount_t	*mp;		/* mount काष्ठाure क्रम fileप्रणाली */
	xfs_btree_cur_t	*new;		/* new cursor value */
	xfs_trans_t	*tp;		/* transaction poपूर्णांकer, can be शून्य */

	tp = cur->bc_tp;
	mp = cur->bc_mp;

	/*
	 * Allocate a new cursor like the old one.
	 */
	new = cur->bc_ops->dup_cursor(cur);

	/*
	 * Copy the record currently in the cursor.
	 */
	new->bc_rec = cur->bc_rec;

	/*
	 * For each level current, re-get the buffer and copy the ptr value.
	 */
	क्रम (i = 0; i < new->bc_nlevels; i++) अणु
		new->bc_ptrs[i] = cur->bc_ptrs[i];
		new->bc_ra[i] = cur->bc_ra[i];
		bp = cur->bc_bufs[i];
		अगर (bp) अणु
			error = xfs_trans_पढ़ो_buf(mp, tp, mp->m_ddev_targp,
						   XFS_BUF_ADDR(bp), mp->m_bsize,
						   0, &bp,
						   cur->bc_ops->buf_ops);
			अगर (error) अणु
				xfs_btree_del_cursor(new, error);
				*ncur = शून्य;
				वापस error;
			पूर्ण
		पूर्ण
		new->bc_bufs[i] = bp;
	पूर्ण
	*ncur = new;
	वापस 0;
पूर्ण

/*
 * XFS btree block layout and addressing:
 *
 * There are two types of blocks in the btree: leaf and non-leaf blocks.
 *
 * The leaf record start with a header then followed by records containing
 * the values.  A non-leaf block also starts with the same header, and
 * then first contains lookup keys followed by an equal number of poपूर्णांकers
 * to the btree blocks at the previous level.
 *
 *		+--------+-------+-------+-------+-------+-------+-------+
 * Leaf:	| header | rec 1 | rec 2 | rec 3 | rec 4 | rec 5 | rec N |
 *		+--------+-------+-------+-------+-------+-------+-------+
 *
 *		+--------+-------+-------+-------+-------+-------+-------+
 * Non-Leaf:	| header | key 1 | key 2 | key N | ptr 1 | ptr 2 | ptr N |
 *		+--------+-------+-------+-------+-------+-------+-------+
 *
 * The header is called काष्ठा xfs_btree_block क्रम reasons better left unknown
 * and comes in dअगरferent versions क्रम लघु (32bit) and दीर्घ (64bit) block
 * poपूर्णांकers.  The record and key काष्ठाures are defined by the btree instances
 * and opaque to the btree core.  The block poपूर्णांकers are simple disk endian
 * पूर्णांकegers, available in a लघु (32bit) and दीर्घ (64bit) variant.
 *
 * The helpers below calculate the offset of a given record, key or poपूर्णांकer
 * पूर्णांकo a btree block (xfs_btree_*_offset) or वापस a poपूर्णांकer to the given
 * record, key or poपूर्णांकer (xfs_btree_*_addr).  Note that all addressing
 * inside the btree block is करोne using indices starting at one, not zero!
 *
 * If XFS_BTREE_OVERLAPPING is set, then this btree supports keys containing
 * overlapping पूर्णांकervals.  In such a tree, records are still sorted lowest to
 * highest and indexed by the smallest key value that refers to the record.
 * However, nodes are dअगरferent: each poपूर्णांकer has two associated keys -- one
 * indexing the lowest key available in the block(s) below (the same behavior
 * as the key in a regular btree) and another indexing the highest key
 * available in the block(s) below.  Because records are /not/ sorted by the
 * highest key, all leaf block updates require us to compute the highest key
 * that matches any record in the leaf and to recursively update the high keys
 * in the nodes going further up in the tree, अगर necessary.  Nodes look like
 * this:
 *
 *		+--------+-----+-----+-----+-----+-----+-------+-------+-----+
 * Non-Leaf:	| header | lo1 | hi1 | lo2 | hi2 | ... | ptr 1 | ptr 2 | ... |
 *		+--------+-----+-----+-----+-----+-----+-------+-------+-----+
 *
 * To perक्रमm an पूर्णांकerval query on an overlapped tree, perक्रमm the usual
 * depth-first search and use the low and high keys to decide अगर we can skip
 * that particular node.  If a leaf node is reached, वापस the records that
 * पूर्णांकersect the पूर्णांकerval.  Note that an पूर्णांकerval query may वापस numerous
 * entries.  For a non-overlapped tree, simply search क्रम the record associated
 * with the lowest key and iterate क्रमward until a non-matching record is
 * found.  Section 14.3 ("Interval Trees") of _Introduction to Algorithms_ by
 * Cormen, Leiserson, Rivest, and Stein (2nd or 3rd ed. only) discuss this in
 * more detail.
 *
 * Why करो we care about overlapping पूर्णांकervals?  Let's say you have a bunch of
 * reverse mapping records on a reflink fileप्रणाली:
 *
 * 1: +- file A startblock B offset C length D -----------+
 * 2:      +- file E startblock F offset G length H --------------+
 * 3:      +- file I startblock F offset J length K --+
 * 4:                                                        +- file L... --+
 *
 * Now say we want to map block (B+D) पूर्णांकo file A at offset (C+D).  Ideally,
 * we'd simply increment the length of record 1.  But how करो we find the record
 * that ends at (B+D-1) (i.e. record 1)?  A LE lookup of (B+D-1) would वापस
 * record 3 because the keys are ordered first by startblock.  An पूर्णांकerval
 * query would वापस records 1 and 2 because they both overlap (B+D-1), and
 * from that we can pick out record 1 as the appropriate left neighbor.
 *
 * In the non-overlapped हाल you can करो a LE lookup and decrement the cursor
 * because a record's पूर्णांकerval must end beक्रमe the next record.
 */

/*
 * Return size of the btree block header क्रम this btree instance.
 */
अटल अंतरभूत माप_प्रकार xfs_btree_block_len(काष्ठा xfs_btree_cur *cur)
अणु
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS) अणु
		अगर (cur->bc_flags & XFS_BTREE_CRC_BLOCKS)
			वापस XFS_BTREE_LBLOCK_CRC_LEN;
		वापस XFS_BTREE_LBLOCK_LEN;
	पूर्ण
	अगर (cur->bc_flags & XFS_BTREE_CRC_BLOCKS)
		वापस XFS_BTREE_SBLOCK_CRC_LEN;
	वापस XFS_BTREE_SBLOCK_LEN;
पूर्ण

/*
 * Return size of btree block poपूर्णांकers क्रम this btree instance.
 */
अटल अंतरभूत माप_प्रकार xfs_btree_ptr_len(काष्ठा xfs_btree_cur *cur)
अणु
	वापस (cur->bc_flags & XFS_BTREE_LONG_PTRS) ?
		माप(__be64) : माप(__be32);
पूर्ण

/*
 * Calculate offset of the n-th record in a btree block.
 */
STATIC माप_प्रकार
xfs_btree_rec_offset(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			n)
अणु
	वापस xfs_btree_block_len(cur) +
		(n - 1) * cur->bc_ops->rec_len;
पूर्ण

/*
 * Calculate offset of the n-th key in a btree block.
 */
STATIC माप_प्रकार
xfs_btree_key_offset(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			n)
अणु
	वापस xfs_btree_block_len(cur) +
		(n - 1) * cur->bc_ops->key_len;
पूर्ण

/*
 * Calculate offset of the n-th high key in a btree block.
 */
STATIC माप_प्रकार
xfs_btree_high_key_offset(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			n)
अणु
	वापस xfs_btree_block_len(cur) +
		(n - 1) * cur->bc_ops->key_len + (cur->bc_ops->key_len / 2);
पूर्ण

/*
 * Calculate offset of the n-th block poपूर्णांकer in a btree block.
 */
STATIC माप_प्रकार
xfs_btree_ptr_offset(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			n,
	पूर्णांक			level)
अणु
	वापस xfs_btree_block_len(cur) +
		cur->bc_ops->get_maxrecs(cur, level) * cur->bc_ops->key_len +
		(n - 1) * xfs_btree_ptr_len(cur);
पूर्ण

/*
 * Return a poपूर्णांकer to the n-th record in the btree block.
 */
जोड़ xfs_btree_rec *
xfs_btree_rec_addr(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			n,
	काष्ठा xfs_btree_block	*block)
अणु
	वापस (जोड़ xfs_btree_rec *)
		((अक्षर *)block + xfs_btree_rec_offset(cur, n));
पूर्ण

/*
 * Return a poपूर्णांकer to the n-th key in the btree block.
 */
जोड़ xfs_btree_key *
xfs_btree_key_addr(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			n,
	काष्ठा xfs_btree_block	*block)
अणु
	वापस (जोड़ xfs_btree_key *)
		((अक्षर *)block + xfs_btree_key_offset(cur, n));
पूर्ण

/*
 * Return a poपूर्णांकer to the n-th high key in the btree block.
 */
जोड़ xfs_btree_key *
xfs_btree_high_key_addr(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			n,
	काष्ठा xfs_btree_block	*block)
अणु
	वापस (जोड़ xfs_btree_key *)
		((अक्षर *)block + xfs_btree_high_key_offset(cur, n));
पूर्ण

/*
 * Return a poपूर्णांकer to the n-th block poपूर्णांकer in the btree block.
 */
जोड़ xfs_btree_ptr *
xfs_btree_ptr_addr(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			n,
	काष्ठा xfs_btree_block	*block)
अणु
	पूर्णांक			level = xfs_btree_get_level(block);

	ASSERT(block->bb_level != 0);

	वापस (जोड़ xfs_btree_ptr *)
		((अक्षर *)block + xfs_btree_ptr_offset(cur, n, level));
पूर्ण

काष्ठा xfs_अगरork *
xfs_btree_अगरork_ptr(
	काष्ठा xfs_btree_cur	*cur)
अणु
	ASSERT(cur->bc_flags & XFS_BTREE_ROOT_IN_INODE);

	अगर (cur->bc_flags & XFS_BTREE_STAGING)
		वापस cur->bc_ino.अगरake->अगर_विभाजन;
	वापस XFS_IFORK_PTR(cur->bc_ino.ip, cur->bc_ino.whichविभाजन);
पूर्ण

/*
 * Get the root block which is stored in the inode.
 *
 * For now this btree implementation assumes the btree root is always
 * stored in the अगर_broot field of an inode विभाजन.
 */
STATIC काष्ठा xfs_btree_block *
xfs_btree_get_iroot(
	काष्ठा xfs_btree_cur	*cur)
अणु
	काष्ठा xfs_अगरork	*अगरp = xfs_btree_अगरork_ptr(cur);

	वापस (काष्ठा xfs_btree_block *)अगरp->अगर_broot;
पूर्ण

/*
 * Retrieve the block poपूर्णांकer from the cursor at the given level.
 * This may be an inode btree root or from a buffer.
 */
काष्ठा xfs_btree_block *		/* generic btree block poपूर्णांकer */
xfs_btree_get_block(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	पूर्णांक			level,	/* level in btree */
	काष्ठा xfs_buf		**bpp)	/* buffer containing the block */
अणु
	अगर ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    (level == cur->bc_nlevels - 1)) अणु
		*bpp = शून्य;
		वापस xfs_btree_get_iroot(cur);
	पूर्ण

	*bpp = cur->bc_bufs[level];
	वापस XFS_BUF_TO_BLOCK(*bpp);
पूर्ण

/*
 * Change the cursor to poपूर्णांक to the first record at the given level.
 * Other levels are unaffected.
 */
STATIC पूर्णांक				/* success=1, failure=0 */
xfs_btree_firstrec(
	xfs_btree_cur_t		*cur,	/* btree cursor */
	पूर्णांक			level)	/* level to change */
अणु
	काष्ठा xfs_btree_block	*block;	/* generic btree block poपूर्णांकer */
	काष्ठा xfs_buf		*bp;	/* buffer containing block */

	/*
	 * Get the block poपूर्णांकer क्रम this level.
	 */
	block = xfs_btree_get_block(cur, level, &bp);
	अगर (xfs_btree_check_block(cur, block, level, bp))
		वापस 0;
	/*
	 * It's empty, there is no such record.
	 */
	अगर (!block->bb_numrecs)
		वापस 0;
	/*
	 * Set the ptr value to 1, that's the first record/key.
	 */
	cur->bc_ptrs[level] = 1;
	वापस 1;
पूर्ण

/*
 * Change the cursor to poपूर्णांक to the last record in the current block
 * at the given level.  Other levels are unaffected.
 */
STATIC पूर्णांक				/* success=1, failure=0 */
xfs_btree_lastrec(
	xfs_btree_cur_t		*cur,	/* btree cursor */
	पूर्णांक			level)	/* level to change */
अणु
	काष्ठा xfs_btree_block	*block;	/* generic btree block poपूर्णांकer */
	काष्ठा xfs_buf		*bp;	/* buffer containing block */

	/*
	 * Get the block poपूर्णांकer क्रम this level.
	 */
	block = xfs_btree_get_block(cur, level, &bp);
	अगर (xfs_btree_check_block(cur, block, level, bp))
		वापस 0;
	/*
	 * It's empty, there is no such record.
	 */
	अगर (!block->bb_numrecs)
		वापस 0;
	/*
	 * Set the ptr value to numrecs, that's the last record/key.
	 */
	cur->bc_ptrs[level] = be16_to_cpu(block->bb_numrecs);
	वापस 1;
पूर्ण

/*
 * Compute first and last byte offsets क्रम the fields given.
 * Interprets the offsets table, which contains काष्ठा field offsets.
 */
व्योम
xfs_btree_offsets(
	पूर्णांक64_t		fields,		/* biपंचांगask of fields */
	स्थिर लघु	*offsets,	/* table of field offsets */
	पूर्णांक		nbits,		/* number of bits to inspect */
	पूर्णांक		*first,		/* output: first byte offset */
	पूर्णांक		*last)		/* output: last byte offset */
अणु
	पूर्णांक		i;		/* current bit number */
	पूर्णांक64_t		imask;		/* mask क्रम current bit number */

	ASSERT(fields != 0);
	/*
	 * Find the lowest bit, so the first byte offset.
	 */
	क्रम (i = 0, imask = 1LL; ; i++, imask <<= 1) अणु
		अगर (imask & fields) अणु
			*first = offsets[i];
			अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * Find the highest bit, so the last byte offset.
	 */
	क्रम (i = nbits - 1, imask = 1LL << i; ; i--, imask >>= 1) अणु
		अगर (imask & fields) अणु
			*last = offsets[i + 1] - 1;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Get a buffer क्रम the block, वापस it पढ़ो in.
 * Long-क्रमm addressing.
 */
पूर्णांक
xfs_btree_पढ़ो_bufl(
	काष्ठा xfs_mount	*mp,		/* file प्रणाली mount poपूर्णांक */
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	xfs_fsblock_t		fsbno,		/* file प्रणाली block number */
	काष्ठा xfs_buf		**bpp,		/* buffer क्रम fsbno */
	पूर्णांक			refval,		/* ref count value क्रम buffer */
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	काष्ठा xfs_buf		*bp;		/* वापस value */
	xfs_daddr_t		d;		/* real disk block address */
	पूर्णांक			error;

	अगर (!xfs_verअगरy_fsbno(mp, fsbno))
		वापस -EFSCORRUPTED;
	d = XFS_FSB_TO_DADDR(mp, fsbno);
	error = xfs_trans_पढ़ो_buf(mp, tp, mp->m_ddev_targp, d,
				   mp->m_bsize, 0, &bp, ops);
	अगर (error)
		वापस error;
	अगर (bp)
		xfs_buf_set_ref(bp, refval);
	*bpp = bp;
	वापस 0;
पूर्ण

/*
 * Read-ahead the block, करोn't wait for it, don't वापस a buffer.
 * Long-क्रमm addressing.
 */
/* ARGSUSED */
व्योम
xfs_btree_पढ़ोa_bufl(
	काष्ठा xfs_mount	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_fsblock_t		fsbno,		/* file प्रणाली block number */
	xfs_extlen_t		count,		/* count of fileप्रणाली blocks */
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	xfs_daddr_t		d;

	ASSERT(fsbno != शून्यFSBLOCK);
	d = XFS_FSB_TO_DADDR(mp, fsbno);
	xfs_buf_पढ़ोahead(mp->m_ddev_targp, d, mp->m_bsize * count, ops);
पूर्ण

/*
 * Read-ahead the block, करोn't wait for it, don't वापस a buffer.
 * Short-क्रमm addressing.
 */
/* ARGSUSED */
व्योम
xfs_btree_पढ़ोa_bufs(
	काष्ठा xfs_mount	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_agnumber_t		agno,		/* allocation group number */
	xfs_agblock_t		agbno,		/* allocation group block number */
	xfs_extlen_t		count,		/* count of fileप्रणाली blocks */
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	xfs_daddr_t		d;

	ASSERT(agno != शून्यAGNUMBER);
	ASSERT(agbno != शून्यAGBLOCK);
	d = XFS_AGB_TO_DADDR(mp, agno, agbno);
	xfs_buf_पढ़ोahead(mp->m_ddev_targp, d, mp->m_bsize * count, ops);
पूर्ण

STATIC पूर्णांक
xfs_btree_पढ़ोahead_lblock(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			lr,
	काष्ठा xfs_btree_block	*block)
अणु
	पूर्णांक			rval = 0;
	xfs_fsblock_t		left = be64_to_cpu(block->bb_u.l.bb_leftsib);
	xfs_fsblock_t		right = be64_to_cpu(block->bb_u.l.bb_rightsib);

	अगर ((lr & XFS_BTCUR_LEFTRA) && left != शून्यFSBLOCK) अणु
		xfs_btree_पढ़ोa_bufl(cur->bc_mp, left, 1,
				     cur->bc_ops->buf_ops);
		rval++;
	पूर्ण

	अगर ((lr & XFS_BTCUR_RIGHTRA) && right != शून्यFSBLOCK) अणु
		xfs_btree_पढ़ोa_bufl(cur->bc_mp, right, 1,
				     cur->bc_ops->buf_ops);
		rval++;
	पूर्ण

	वापस rval;
पूर्ण

STATIC पूर्णांक
xfs_btree_पढ़ोahead_sblock(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			lr,
	काष्ठा xfs_btree_block *block)
अणु
	पूर्णांक			rval = 0;
	xfs_agblock_t		left = be32_to_cpu(block->bb_u.s.bb_leftsib);
	xfs_agblock_t		right = be32_to_cpu(block->bb_u.s.bb_rightsib);


	अगर ((lr & XFS_BTCUR_LEFTRA) && left != शून्यAGBLOCK) अणु
		xfs_btree_पढ़ोa_bufs(cur->bc_mp, cur->bc_ag.agno,
				     left, 1, cur->bc_ops->buf_ops);
		rval++;
	पूर्ण

	अगर ((lr & XFS_BTCUR_RIGHTRA) && right != शून्यAGBLOCK) अणु
		xfs_btree_पढ़ोa_bufs(cur->bc_mp, cur->bc_ag.agno,
				     right, 1, cur->bc_ops->buf_ops);
		rval++;
	पूर्ण

	वापस rval;
पूर्ण

/*
 * Read-ahead btree blocks, at the given level.
 * Bits in lr are set from XFS_BTCUR_अणुLEFT,RIGHTपूर्णRA.
 */
STATIC पूर्णांक
xfs_btree_पढ़ोahead(
	काष्ठा xfs_btree_cur	*cur,		/* btree cursor */
	पूर्णांक			lev,		/* level in btree */
	पूर्णांक			lr)		/* left/right bits */
अणु
	काष्ठा xfs_btree_block	*block;

	/*
	 * No पढ़ोahead needed अगर we are at the root level and the
	 * btree root is stored in the inode.
	 */
	अगर ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    (lev == cur->bc_nlevels - 1))
		वापस 0;

	अगर ((cur->bc_ra[lev] | lr) == cur->bc_ra[lev])
		वापस 0;

	cur->bc_ra[lev] |= lr;
	block = XFS_BUF_TO_BLOCK(cur->bc_bufs[lev]);

	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		वापस xfs_btree_पढ़ोahead_lblock(cur, lr, block);
	वापस xfs_btree_पढ़ोahead_sblock(cur, lr, block);
पूर्ण

STATIC पूर्णांक
xfs_btree_ptr_to_daddr(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr,
	xfs_daddr_t		*daddr)
अणु
	xfs_fsblock_t		fsbno;
	xfs_agblock_t		agbno;
	पूर्णांक			error;

	error = xfs_btree_check_ptr(cur, ptr, 0, 1);
	अगर (error)
		वापस error;

	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS) अणु
		fsbno = be64_to_cpu(ptr->l);
		*daddr = XFS_FSB_TO_DADDR(cur->bc_mp, fsbno);
	पूर्ण अन्यथा अणु
		agbno = be32_to_cpu(ptr->s);
		*daddr = XFS_AGB_TO_DADDR(cur->bc_mp, cur->bc_ag.agno,
				agbno);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Readahead @count btree blocks at the given @ptr location.
 *
 * We करोn't need to care about दीर्घ or लघु क्रमm btrees here as we have a
 * method of converting the ptr directly to a daddr available to us.
 */
STATIC व्योम
xfs_btree_पढ़ोahead_ptr(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr,
	xfs_extlen_t		count)
अणु
	xfs_daddr_t		daddr;

	अगर (xfs_btree_ptr_to_daddr(cur, ptr, &daddr))
		वापस;
	xfs_buf_पढ़ोahead(cur->bc_mp->m_ddev_targp, daddr,
			  cur->bc_mp->m_bsize * count, cur->bc_ops->buf_ops);
पूर्ण

/*
 * Set the buffer क्रम level "lev" in the cursor to bp, releasing
 * any previous buffer.
 */
STATIC व्योम
xfs_btree_रखो_बफ(
	xfs_btree_cur_t		*cur,	/* btree cursor */
	पूर्णांक			lev,	/* level in btree */
	काष्ठा xfs_buf		*bp)	/* new buffer to set */
अणु
	काष्ठा xfs_btree_block	*b;	/* btree block */

	अगर (cur->bc_bufs[lev])
		xfs_trans_brअन्यथा(cur->bc_tp, cur->bc_bufs[lev]);
	cur->bc_bufs[lev] = bp;
	cur->bc_ra[lev] = 0;

	b = XFS_BUF_TO_BLOCK(bp);
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS) अणु
		अगर (b->bb_u.l.bb_leftsib == cpu_to_be64(शून्यFSBLOCK))
			cur->bc_ra[lev] |= XFS_BTCUR_LEFTRA;
		अगर (b->bb_u.l.bb_rightsib == cpu_to_be64(शून्यFSBLOCK))
			cur->bc_ra[lev] |= XFS_BTCUR_RIGHTRA;
	पूर्ण अन्यथा अणु
		अगर (b->bb_u.s.bb_leftsib == cpu_to_be32(शून्यAGBLOCK))
			cur->bc_ra[lev] |= XFS_BTCUR_LEFTRA;
		अगर (b->bb_u.s.bb_rightsib == cpu_to_be32(शून्यAGBLOCK))
			cur->bc_ra[lev] |= XFS_BTCUR_RIGHTRA;
	पूर्ण
पूर्ण

bool
xfs_btree_ptr_is_null(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		वापस ptr->l == cpu_to_be64(शून्यFSBLOCK);
	अन्यथा
		वापस ptr->s == cpu_to_be32(शून्यAGBLOCK);
पूर्ण

व्योम
xfs_btree_set_ptr_null(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		ptr->l = cpu_to_be64(शून्यFSBLOCK);
	अन्यथा
		ptr->s = cpu_to_be32(शून्यAGBLOCK);
पूर्ण

/*
 * Get/set/init sibling poपूर्णांकers
 */
व्योम
xfs_btree_get_sibling(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	जोड़ xfs_btree_ptr	*ptr,
	पूर्णांक			lr)
अणु
	ASSERT(lr == XFS_BB_LEFTSIB || lr == XFS_BB_RIGHTSIB);

	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS) अणु
		अगर (lr == XFS_BB_RIGHTSIB)
			ptr->l = block->bb_u.l.bb_rightsib;
		अन्यथा
			ptr->l = block->bb_u.l.bb_leftsib;
	पूर्ण अन्यथा अणु
		अगर (lr == XFS_BB_RIGHTSIB)
			ptr->s = block->bb_u.s.bb_rightsib;
		अन्यथा
			ptr->s = block->bb_u.s.bb_leftsib;
	पूर्ण
पूर्ण

व्योम
xfs_btree_set_sibling(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	जोड़ xfs_btree_ptr	*ptr,
	पूर्णांक			lr)
अणु
	ASSERT(lr == XFS_BB_LEFTSIB || lr == XFS_BB_RIGHTSIB);

	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS) अणु
		अगर (lr == XFS_BB_RIGHTSIB)
			block->bb_u.l.bb_rightsib = ptr->l;
		अन्यथा
			block->bb_u.l.bb_leftsib = ptr->l;
	पूर्ण अन्यथा अणु
		अगर (lr == XFS_BB_RIGHTSIB)
			block->bb_u.s.bb_rightsib = ptr->s;
		अन्यथा
			block->bb_u.s.bb_leftsib = ptr->s;
	पूर्ण
पूर्ण

व्योम
xfs_btree_init_block_पूर्णांक(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_btree_block	*buf,
	xfs_daddr_t		blkno,
	xfs_btnum_t		btnum,
	__u16			level,
	__u16			numrecs,
	__u64			owner,
	अचिन्हित पूर्णांक		flags)
अणु
	पूर्णांक			crc = xfs_sb_version_hascrc(&mp->m_sb);
	__u32			magic = xfs_btree_magic(crc, btnum);

	buf->bb_magic = cpu_to_be32(magic);
	buf->bb_level = cpu_to_be16(level);
	buf->bb_numrecs = cpu_to_be16(numrecs);

	अगर (flags & XFS_BTREE_LONG_PTRS) अणु
		buf->bb_u.l.bb_leftsib = cpu_to_be64(शून्यFSBLOCK);
		buf->bb_u.l.bb_rightsib = cpu_to_be64(शून्यFSBLOCK);
		अगर (crc) अणु
			buf->bb_u.l.bb_blkno = cpu_to_be64(blkno);
			buf->bb_u.l.bb_owner = cpu_to_be64(owner);
			uuid_copy(&buf->bb_u.l.bb_uuid, &mp->m_sb.sb_meta_uuid);
			buf->bb_u.l.bb_pad = 0;
			buf->bb_u.l.bb_lsn = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* owner is a 32 bit value on लघु blocks */
		__u32 __owner = (__u32)owner;

		buf->bb_u.s.bb_leftsib = cpu_to_be32(शून्यAGBLOCK);
		buf->bb_u.s.bb_rightsib = cpu_to_be32(शून्यAGBLOCK);
		अगर (crc) अणु
			buf->bb_u.s.bb_blkno = cpu_to_be64(blkno);
			buf->bb_u.s.bb_owner = cpu_to_be32(__owner);
			uuid_copy(&buf->bb_u.s.bb_uuid, &mp->m_sb.sb_meta_uuid);
			buf->bb_u.s.bb_lsn = 0;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
xfs_btree_init_block(
	काष्ठा xfs_mount *mp,
	काष्ठा xfs_buf	*bp,
	xfs_btnum_t	btnum,
	__u16		level,
	__u16		numrecs,
	__u64		owner)
अणु
	xfs_btree_init_block_पूर्णांक(mp, XFS_BUF_TO_BLOCK(bp), bp->b_bn,
				 btnum, level, numrecs, owner, 0);
पूर्ण

व्योम
xfs_btree_init_block_cur(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp,
	पूर्णांक			level,
	पूर्णांक			numrecs)
अणु
	__u64			owner;

	/*
	 * we can pull the owner from the cursor right now as the dअगरferent
	 * owners align directly with the poपूर्णांकer size of the btree. This may
	 * change in future, but is safe क्रम current users of the generic btree
	 * code.
	 */
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		owner = cur->bc_ino.ip->i_ino;
	अन्यथा
		owner = cur->bc_ag.agno;

	xfs_btree_init_block_पूर्णांक(cur->bc_mp, XFS_BUF_TO_BLOCK(bp), bp->b_bn,
				 cur->bc_btnum, level, numrecs,
				 owner, cur->bc_flags);
पूर्ण

/*
 * Return true अगर ptr is the last record in the btree and
 * we need to track updates to this record.  The decision
 * will be further refined in the update_lastrec method.
 */
STATIC पूर्णांक
xfs_btree_is_lastrec(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	पूर्णांक			level)
अणु
	जोड़ xfs_btree_ptr	ptr;

	अगर (level > 0)
		वापस 0;
	अगर (!(cur->bc_flags & XFS_BTREE_LASTREC_UPDATE))
		वापस 0;

	xfs_btree_get_sibling(cur, block, &ptr, XFS_BB_RIGHTSIB);
	अगर (!xfs_btree_ptr_is_null(cur, &ptr))
		वापस 0;
	वापस 1;
पूर्ण

STATIC व्योम
xfs_btree_buf_to_ptr(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		ptr->l = cpu_to_be64(XFS_DADDR_TO_FSB(cur->bc_mp,
					XFS_BUF_ADDR(bp)));
	अन्यथा अणु
		ptr->s = cpu_to_be32(xfs_daddr_to_agbno(cur->bc_mp,
					XFS_BUF_ADDR(bp)));
	पूर्ण
पूर्ण

STATIC व्योम
xfs_btree_set_refs(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp)
अणु
	चयन (cur->bc_btnum) अणु
	हाल XFS_BTNUM_BNO:
	हाल XFS_BTNUM_CNT:
		xfs_buf_set_ref(bp, XFS_ALLOC_BTREE_REF);
		अवरोध;
	हाल XFS_BTNUM_INO:
	हाल XFS_BTNUM_FINO:
		xfs_buf_set_ref(bp, XFS_INO_BTREE_REF);
		अवरोध;
	हाल XFS_BTNUM_BMAP:
		xfs_buf_set_ref(bp, XFS_BMAP_BTREE_REF);
		अवरोध;
	हाल XFS_BTNUM_RMAP:
		xfs_buf_set_ref(bp, XFS_RMAP_BTREE_REF);
		अवरोध;
	हाल XFS_BTNUM_REFC:
		xfs_buf_set_ref(bp, XFS_REFC_BTREE_REF);
		अवरोध;
	शेष:
		ASSERT(0);
	पूर्ण
पूर्ण

पूर्णांक
xfs_btree_get_buf_block(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr,
	काष्ठा xfs_btree_block	**block,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	xfs_daddr_t		d;
	पूर्णांक			error;

	error = xfs_btree_ptr_to_daddr(cur, ptr, &d);
	अगर (error)
		वापस error;
	error = xfs_trans_get_buf(cur->bc_tp, mp->m_ddev_targp, d, mp->m_bsize,
			0, bpp);
	अगर (error)
		वापस error;

	(*bpp)->b_ops = cur->bc_ops->buf_ops;
	*block = XFS_BUF_TO_BLOCK(*bpp);
	वापस 0;
पूर्ण

/*
 * Read in the buffer at the given ptr and वापस the buffer and
 * the block poपूर्णांकer within the buffer.
 */
STATIC पूर्णांक
xfs_btree_पढ़ो_buf_block(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr,
	पूर्णांक			flags,
	काष्ठा xfs_btree_block	**block,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	xfs_daddr_t		d;
	पूर्णांक			error;

	/* need to sort out how callers deal with failures first */
	ASSERT(!(flags & XBF_TRYLOCK));

	error = xfs_btree_ptr_to_daddr(cur, ptr, &d);
	अगर (error)
		वापस error;
	error = xfs_trans_पढ़ो_buf(mp, cur->bc_tp, mp->m_ddev_targp, d,
				   mp->m_bsize, flags, bpp,
				   cur->bc_ops->buf_ops);
	अगर (error)
		वापस error;

	xfs_btree_set_refs(cur, *bpp);
	*block = XFS_BUF_TO_BLOCK(*bpp);
	वापस 0;
पूर्ण

/*
 * Copy keys from one btree block to another.
 */
व्योम
xfs_btree_copy_keys(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*dst_key,
	जोड़ xfs_btree_key	*src_key,
	पूर्णांक			numkeys)
अणु
	ASSERT(numkeys >= 0);
	स_नकल(dst_key, src_key, numkeys * cur->bc_ops->key_len);
पूर्ण

/*
 * Copy records from one btree block to another.
 */
STATIC व्योम
xfs_btree_copy_recs(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*dst_rec,
	जोड़ xfs_btree_rec	*src_rec,
	पूर्णांक			numrecs)
अणु
	ASSERT(numrecs >= 0);
	स_नकल(dst_rec, src_rec, numrecs * cur->bc_ops->rec_len);
पूर्ण

/*
 * Copy block poपूर्णांकers from one btree block to another.
 */
व्योम
xfs_btree_copy_ptrs(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*dst_ptr,
	स्थिर जोड़ xfs_btree_ptr *src_ptr,
	पूर्णांक			numptrs)
अणु
	ASSERT(numptrs >= 0);
	स_नकल(dst_ptr, src_ptr, numptrs * xfs_btree_ptr_len(cur));
पूर्ण

/*
 * Shअगरt keys one index left/right inside a single btree block.
 */
STATIC व्योम
xfs_btree_shअगरt_keys(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*key,
	पूर्णांक			dir,
	पूर्णांक			numkeys)
अणु
	अक्षर			*dst_key;

	ASSERT(numkeys >= 0);
	ASSERT(dir == 1 || dir == -1);

	dst_key = (अक्षर *)key + (dir * cur->bc_ops->key_len);
	स_हटाओ(dst_key, key, numkeys * cur->bc_ops->key_len);
पूर्ण

/*
 * Shअगरt records one index left/right inside a single btree block.
 */
STATIC व्योम
xfs_btree_shअगरt_recs(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*rec,
	पूर्णांक			dir,
	पूर्णांक			numrecs)
अणु
	अक्षर			*dst_rec;

	ASSERT(numrecs >= 0);
	ASSERT(dir == 1 || dir == -1);

	dst_rec = (अक्षर *)rec + (dir * cur->bc_ops->rec_len);
	स_हटाओ(dst_rec, rec, numrecs * cur->bc_ops->rec_len);
पूर्ण

/*
 * Shअगरt block poपूर्णांकers one index left/right inside a single btree block.
 */
STATIC व्योम
xfs_btree_shअगरt_ptrs(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr,
	पूर्णांक			dir,
	पूर्णांक			numptrs)
अणु
	अक्षर			*dst_ptr;

	ASSERT(numptrs >= 0);
	ASSERT(dir == 1 || dir == -1);

	dst_ptr = (अक्षर *)ptr + (dir * xfs_btree_ptr_len(cur));
	स_हटाओ(dst_ptr, ptr, numptrs * xfs_btree_ptr_len(cur));
पूर्ण

/*
 * Log key values from the btree block.
 */
STATIC व्योम
xfs_btree_log_keys(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp,
	पूर्णांक			first,
	पूर्णांक			last)
अणु

	अगर (bp) अणु
		xfs_trans_buf_set_type(cur->bc_tp, bp, XFS_BLFT_BTREE_BUF);
		xfs_trans_log_buf(cur->bc_tp, bp,
				  xfs_btree_key_offset(cur, first),
				  xfs_btree_key_offset(cur, last + 1) - 1);
	पूर्ण अन्यथा अणु
		xfs_trans_log_inode(cur->bc_tp, cur->bc_ino.ip,
				xfs_ilog_fbroot(cur->bc_ino.whichविभाजन));
	पूर्ण
पूर्ण

/*
 * Log record values from the btree block.
 */
व्योम
xfs_btree_log_recs(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp,
	पूर्णांक			first,
	पूर्णांक			last)
अणु

	xfs_trans_buf_set_type(cur->bc_tp, bp, XFS_BLFT_BTREE_BUF);
	xfs_trans_log_buf(cur->bc_tp, bp,
			  xfs_btree_rec_offset(cur, first),
			  xfs_btree_rec_offset(cur, last + 1) - 1);

पूर्ण

/*
 * Log block poपूर्णांकer fields from a btree block (nonleaf).
 */
STATIC व्योम
xfs_btree_log_ptrs(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	काष्ठा xfs_buf		*bp,	/* buffer containing btree block */
	पूर्णांक			first,	/* index of first poपूर्णांकer to log */
	पूर्णांक			last)	/* index of last poपूर्णांकer to log */
अणु

	अगर (bp) अणु
		काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
		पूर्णांक			level = xfs_btree_get_level(block);

		xfs_trans_buf_set_type(cur->bc_tp, bp, XFS_BLFT_BTREE_BUF);
		xfs_trans_log_buf(cur->bc_tp, bp,
				xfs_btree_ptr_offset(cur, first, level),
				xfs_btree_ptr_offset(cur, last + 1, level) - 1);
	पूर्ण अन्यथा अणु
		xfs_trans_log_inode(cur->bc_tp, cur->bc_ino.ip,
			xfs_ilog_fbroot(cur->bc_ino.whichविभाजन));
	पूर्ण

पूर्ण

/*
 * Log fields from a btree block header.
 */
व्योम
xfs_btree_log_block(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	काष्ठा xfs_buf		*bp,	/* buffer containing btree block */
	पूर्णांक			fields)	/* mask of fields: XFS_BB_... */
अणु
	पूर्णांक			first;	/* first byte offset logged */
	पूर्णांक			last;	/* last byte offset logged */
	अटल स्थिर लघु	soffsets[] = अणु	/* table of offsets (लघु) */
		दुरत्व(काष्ठा xfs_btree_block, bb_magic),
		दुरत्व(काष्ठा xfs_btree_block, bb_level),
		दुरत्व(काष्ठा xfs_btree_block, bb_numrecs),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.s.bb_leftsib),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.s.bb_rightsib),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.s.bb_blkno),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.s.bb_lsn),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.s.bb_uuid),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.s.bb_owner),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.s.bb_crc),
		XFS_BTREE_SBLOCK_CRC_LEN
	पूर्ण;
	अटल स्थिर लघु	loffsets[] = अणु	/* table of offsets (दीर्घ) */
		दुरत्व(काष्ठा xfs_btree_block, bb_magic),
		दुरत्व(काष्ठा xfs_btree_block, bb_level),
		दुरत्व(काष्ठा xfs_btree_block, bb_numrecs),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.l.bb_leftsib),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.l.bb_rightsib),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.l.bb_blkno),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.l.bb_lsn),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.l.bb_uuid),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.l.bb_owner),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.l.bb_crc),
		दुरत्व(काष्ठा xfs_btree_block, bb_u.l.bb_pad),
		XFS_BTREE_LBLOCK_CRC_LEN
	पूर्ण;

	अगर (bp) अणु
		पूर्णांक nbits;

		अगर (cur->bc_flags & XFS_BTREE_CRC_BLOCKS) अणु
			/*
			 * We करोn't log the CRC when updating a btree
			 * block but instead recreate it during log
			 * recovery.  As the log buffers have checksums
			 * of their own this is safe and aव्योमs logging a crc
			 * update in a lot of places.
			 */
			अगर (fields == XFS_BB_ALL_BITS)
				fields = XFS_BB_ALL_BITS_CRC;
			nbits = XFS_BB_NUM_BITS_CRC;
		पूर्ण अन्यथा अणु
			nbits = XFS_BB_NUM_BITS;
		पूर्ण
		xfs_btree_offsets(fields,
				  (cur->bc_flags & XFS_BTREE_LONG_PTRS) ?
					loffsets : soffsets,
				  nbits, &first, &last);
		xfs_trans_buf_set_type(cur->bc_tp, bp, XFS_BLFT_BTREE_BUF);
		xfs_trans_log_buf(cur->bc_tp, bp, first, last);
	पूर्ण अन्यथा अणु
		xfs_trans_log_inode(cur->bc_tp, cur->bc_ino.ip,
			xfs_ilog_fbroot(cur->bc_ino.whichविभाजन));
	पूर्ण
पूर्ण

/*
 * Increment cursor by one record at the level.
 * For nonzero levels the leaf-ward inक्रमmation is untouched.
 */
पूर्णांक						/* error */
xfs_btree_increment(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	पूर्णांक			*stat)		/* success/failure */
अणु
	काष्ठा xfs_btree_block	*block;
	जोड़ xfs_btree_ptr	ptr;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			lev;

	ASSERT(level < cur->bc_nlevels);

	/* Read-ahead to the right at this level. */
	xfs_btree_पढ़ोahead(cur, level, XFS_BTCUR_RIGHTRA);

	/* Get a poपूर्णांकer to the btree block. */
	block = xfs_btree_get_block(cur, level, &bp);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, block, level, bp);
	अगर (error)
		जाओ error0;
#पूर्ण_अगर

	/* We're करोne अगर we reमुख्य in the block after the increment. */
	अगर (++cur->bc_ptrs[level] <= xfs_btree_get_numrecs(block))
		जाओ out1;

	/* Fail अगर we just went off the right edge of the tree. */
	xfs_btree_get_sibling(cur, block, &ptr, XFS_BB_RIGHTSIB);
	अगर (xfs_btree_ptr_is_null(cur, &ptr))
		जाओ out0;

	XFS_BTREE_STATS_INC(cur, increment);

	/*
	 * March up the tree incrementing poपूर्णांकers.
	 * Stop when we करोn't go off the right edge of a block.
	 */
	क्रम (lev = level + 1; lev < cur->bc_nlevels; lev++) अणु
		block = xfs_btree_get_block(cur, lev, &bp);

#अगर_घोषित DEBUG
		error = xfs_btree_check_block(cur, block, lev, bp);
		अगर (error)
			जाओ error0;
#पूर्ण_अगर

		अगर (++cur->bc_ptrs[lev] <= xfs_btree_get_numrecs(block))
			अवरोध;

		/* Read-ahead the right block क्रम the next loop. */
		xfs_btree_पढ़ोahead(cur, lev, XFS_BTCUR_RIGHTRA);
	पूर्ण

	/*
	 * If we went off the root then we are either seriously
	 * confused or have the tree root in an inode.
	 */
	अगर (lev == cur->bc_nlevels) अणु
		अगर (cur->bc_flags & XFS_BTREE_ROOT_IN_INODE)
			जाओ out0;
		ASSERT(0);
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण
	ASSERT(lev < cur->bc_nlevels);

	/*
	 * Now walk back करोwn the tree, fixing up the cursor's buffer
	 * poपूर्णांकers and key numbers.
	 */
	क्रम (block = xfs_btree_get_block(cur, lev, &bp); lev > level; ) अणु
		जोड़ xfs_btree_ptr	*ptrp;

		ptrp = xfs_btree_ptr_addr(cur, cur->bc_ptrs[lev], block);
		--lev;
		error = xfs_btree_पढ़ो_buf_block(cur, ptrp, 0, &block, &bp);
		अगर (error)
			जाओ error0;

		xfs_btree_रखो_बफ(cur, lev, bp);
		cur->bc_ptrs[lev] = 1;
	पूर्ण
out1:
	*stat = 1;
	वापस 0;

out0:
	*stat = 0;
	वापस 0;

error0:
	वापस error;
पूर्ण

/*
 * Decrement cursor by one record at the level.
 * For nonzero levels the leaf-ward inक्रमmation is untouched.
 */
पूर्णांक						/* error */
xfs_btree_decrement(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	पूर्णांक			*stat)		/* success/failure */
अणु
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			lev;
	जोड़ xfs_btree_ptr	ptr;

	ASSERT(level < cur->bc_nlevels);

	/* Read-ahead to the left at this level. */
	xfs_btree_पढ़ोahead(cur, level, XFS_BTCUR_LEFTRA);

	/* We're करोne अगर we reमुख्य in the block after the decrement. */
	अगर (--cur->bc_ptrs[level] > 0)
		जाओ out1;

	/* Get a poपूर्णांकer to the btree block. */
	block = xfs_btree_get_block(cur, level, &bp);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, block, level, bp);
	अगर (error)
		जाओ error0;
#पूर्ण_अगर

	/* Fail अगर we just went off the left edge of the tree. */
	xfs_btree_get_sibling(cur, block, &ptr, XFS_BB_LEFTSIB);
	अगर (xfs_btree_ptr_is_null(cur, &ptr))
		जाओ out0;

	XFS_BTREE_STATS_INC(cur, decrement);

	/*
	 * March up the tree decrementing poपूर्णांकers.
	 * Stop when we करोn't go off the left edge of a block.
	 */
	क्रम (lev = level + 1; lev < cur->bc_nlevels; lev++) अणु
		अगर (--cur->bc_ptrs[lev] > 0)
			अवरोध;
		/* Read-ahead the left block क्रम the next loop. */
		xfs_btree_पढ़ोahead(cur, lev, XFS_BTCUR_LEFTRA);
	पूर्ण

	/*
	 * If we went off the root then we are seriously confused.
	 * or the root of the tree is in an inode.
	 */
	अगर (lev == cur->bc_nlevels) अणु
		अगर (cur->bc_flags & XFS_BTREE_ROOT_IN_INODE)
			जाओ out0;
		ASSERT(0);
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण
	ASSERT(lev < cur->bc_nlevels);

	/*
	 * Now walk back करोwn the tree, fixing up the cursor's buffer
	 * poपूर्णांकers and key numbers.
	 */
	क्रम (block = xfs_btree_get_block(cur, lev, &bp); lev > level; ) अणु
		जोड़ xfs_btree_ptr	*ptrp;

		ptrp = xfs_btree_ptr_addr(cur, cur->bc_ptrs[lev], block);
		--lev;
		error = xfs_btree_पढ़ो_buf_block(cur, ptrp, 0, &block, &bp);
		अगर (error)
			जाओ error0;
		xfs_btree_रखो_बफ(cur, lev, bp);
		cur->bc_ptrs[lev] = xfs_btree_get_numrecs(block);
	पूर्ण
out1:
	*stat = 1;
	वापस 0;

out0:
	*stat = 0;
	वापस 0;

error0:
	वापस error;
पूर्ण

पूर्णांक
xfs_btree_lookup_get_block(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	पूर्णांक			level,	/* level in the btree */
	जोड़ xfs_btree_ptr	*pp,	/* ptr to btree block */
	काष्ठा xfs_btree_block	**blkp) /* वापस btree block */
अणु
	काष्ठा xfs_buf		*bp;	/* buffer poपूर्णांकer क्रम btree block */
	xfs_daddr_t		daddr;
	पूर्णांक			error = 0;

	/* special हाल the root block अगर in an inode */
	अगर ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    (level == cur->bc_nlevels - 1)) अणु
		*blkp = xfs_btree_get_iroot(cur);
		वापस 0;
	पूर्ण

	/*
	 * If the old buffer at this level क्रम the disk address we are
	 * looking क्रम re-use it.
	 *
	 * Otherwise throw it away and get a new one.
	 */
	bp = cur->bc_bufs[level];
	error = xfs_btree_ptr_to_daddr(cur, pp, &daddr);
	अगर (error)
		वापस error;
	अगर (bp && XFS_BUF_ADDR(bp) == daddr) अणु
		*blkp = XFS_BUF_TO_BLOCK(bp);
		वापस 0;
	पूर्ण

	error = xfs_btree_पढ़ो_buf_block(cur, pp, 0, blkp, &bp);
	अगर (error)
		वापस error;

	/* Check the inode owner since the verअगरiers करोn't. */
	अगर (xfs_sb_version_hascrc(&cur->bc_mp->m_sb) &&
	    !(cur->bc_ino.flags & XFS_BTCUR_BMBT_INVALID_OWNER) &&
	    (cur->bc_flags & XFS_BTREE_LONG_PTRS) &&
	    be64_to_cpu((*blkp)->bb_u.l.bb_owner) !=
			cur->bc_ino.ip->i_ino)
		जाओ out_bad;

	/* Did we get the level we were looking क्रम? */
	अगर (be16_to_cpu((*blkp)->bb_level) != level)
		जाओ out_bad;

	/* Check that पूर्णांकernal nodes have at least one record. */
	अगर (level != 0 && be16_to_cpu((*blkp)->bb_numrecs) == 0)
		जाओ out_bad;

	xfs_btree_रखो_बफ(cur, level, bp);
	वापस 0;

out_bad:
	*blkp = शून्य;
	xfs_buf_mark_corrupt(bp);
	xfs_trans_brअन्यथा(cur->bc_tp, bp);
	वापस -EFSCORRUPTED;
पूर्ण

/*
 * Get current search key.  For level 0 we करोn't actually have a key
 * काष्ठाure so we make one up from the record.  For all other levels
 * we just वापस the right key.
 */
STATIC जोड़ xfs_btree_key *
xfs_lookup_get_search_key(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	पूर्णांक			keyno,
	काष्ठा xfs_btree_block	*block,
	जोड़ xfs_btree_key	*kp)
अणु
	अगर (level == 0) अणु
		cur->bc_ops->init_key_from_rec(kp,
				xfs_btree_rec_addr(cur, keyno, block));
		वापस kp;
	पूर्ण

	वापस xfs_btree_key_addr(cur, keyno, block);
पूर्ण

/*
 * Lookup the record.  The cursor is made to poपूर्णांक to it, based on dir.
 * stat is set to 0 अगर can't find any such record, 1 क्रम success.
 */
पूर्णांक					/* error */
xfs_btree_lookup(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_lookup_t		dir,	/* <=, ==, or >= */
	पूर्णांक			*stat)	/* success/failure */
अणु
	काष्ठा xfs_btree_block	*block;	/* current btree block */
	पूर्णांक64_t			dअगरf;	/* dअगरference क्रम the current key */
	पूर्णांक			error;	/* error वापस value */
	पूर्णांक			keyno;	/* current key number */
	पूर्णांक			level;	/* level in the btree */
	जोड़ xfs_btree_ptr	*pp;	/* ptr to btree block */
	जोड़ xfs_btree_ptr	ptr;	/* ptr to btree block */

	XFS_BTREE_STATS_INC(cur, lookup);

	/* No such thing as a zero-level tree. */
	अगर (XFS_IS_CORRUPT(cur->bc_mp, cur->bc_nlevels == 0))
		वापस -EFSCORRUPTED;

	block = शून्य;
	keyno = 0;

	/* initialise start poपूर्णांकer from cursor */
	cur->bc_ops->init_ptr_from_cur(cur, &ptr);
	pp = &ptr;

	/*
	 * Iterate over each level in the btree, starting at the root.
	 * For each level above the leaves, find the key we need, based
	 * on the lookup record, then follow the corresponding block
	 * poपूर्णांकer करोwn to the next level.
	 */
	क्रम (level = cur->bc_nlevels - 1, dअगरf = 1; level >= 0; level--) अणु
		/* Get the block we need to करो the lookup on. */
		error = xfs_btree_lookup_get_block(cur, level, pp, &block);
		अगर (error)
			जाओ error0;

		अगर (dअगरf == 0) अणु
			/*
			 * If we alपढ़ोy had a key match at a higher level, we
			 * know we need to use the first entry in this block.
			 */
			keyno = 1;
		पूर्ण अन्यथा अणु
			/* Otherwise search this block. Do a binary search. */

			पूर्णांक	high;	/* high entry number */
			पूर्णांक	low;	/* low entry number */

			/* Set low and high entry numbers, 1-based. */
			low = 1;
			high = xfs_btree_get_numrecs(block);
			अगर (!high) अणु
				/* Block is empty, must be an empty leaf. */
				अगर (level != 0 || cur->bc_nlevels != 1) अणु
					XFS_CORRUPTION_ERROR(__func__,
							XFS_ERRLEVEL_LOW,
							cur->bc_mp, block,
							माप(*block));
					वापस -EFSCORRUPTED;
				पूर्ण

				cur->bc_ptrs[0] = dir != XFS_LOOKUP_LE;
				*stat = 0;
				वापस 0;
			पूर्ण

			/* Binary search the block. */
			जबतक (low <= high) अणु
				जोड़ xfs_btree_key	key;
				जोड़ xfs_btree_key	*kp;

				XFS_BTREE_STATS_INC(cur, compare);

				/* keyno is average of low and high. */
				keyno = (low + high) >> 1;

				/* Get current search key */
				kp = xfs_lookup_get_search_key(cur, level,
						keyno, block, &key);

				/*
				 * Compute dअगरference to get next direction:
				 *  - less than, move right
				 *  - greater than, move left
				 *  - equal, we're करोne
				 */
				dअगरf = cur->bc_ops->key_dअगरf(cur, kp);
				अगर (dअगरf < 0)
					low = keyno + 1;
				अन्यथा अगर (dअगरf > 0)
					high = keyno - 1;
				अन्यथा
					अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * If there are more levels, set up क्रम the next level
		 * by getting the block number and filling in the cursor.
		 */
		अगर (level > 0) अणु
			/*
			 * If we moved left, need the previous key number,
			 * unless there isn't one.
			 */
			अगर (dअगरf > 0 && --keyno < 1)
				keyno = 1;
			pp = xfs_btree_ptr_addr(cur, keyno, block);

			error = xfs_btree_debug_check_ptr(cur, pp, 0, level);
			अगर (error)
				जाओ error0;

			cur->bc_ptrs[level] = keyno;
		पूर्ण
	पूर्ण

	/* Done with the search. See अगर we need to adjust the results. */
	अगर (dir != XFS_LOOKUP_LE && dअगरf < 0) अणु
		keyno++;
		/*
		 * If ge search and we went off the end of the block, but it's
		 * not the last block, we're in the wrong block.
		 */
		xfs_btree_get_sibling(cur, block, &ptr, XFS_BB_RIGHTSIB);
		अगर (dir == XFS_LOOKUP_GE &&
		    keyno > xfs_btree_get_numrecs(block) &&
		    !xfs_btree_ptr_is_null(cur, &ptr)) अणु
			पूर्णांक	i;

			cur->bc_ptrs[0] = keyno;
			error = xfs_btree_increment(cur, 0, &i);
			अगर (error)
				जाओ error0;
			अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1))
				वापस -EFSCORRUPTED;
			*stat = 1;
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (dir == XFS_LOOKUP_LE && dअगरf > 0)
		keyno--;
	cur->bc_ptrs[0] = keyno;

	/* Return अगर we succeeded or not. */
	अगर (keyno == 0 || keyno > xfs_btree_get_numrecs(block))
		*stat = 0;
	अन्यथा अगर (dir != XFS_LOOKUP_EQ || dअगरf == 0)
		*stat = 1;
	अन्यथा
		*stat = 0;
	वापस 0;

error0:
	वापस error;
पूर्ण

/* Find the high key storage area from a regular key. */
जोड़ xfs_btree_key *
xfs_btree_high_key_from_key(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*key)
अणु
	ASSERT(cur->bc_flags & XFS_BTREE_OVERLAPPING);
	वापस (जोड़ xfs_btree_key *)((अक्षर *)key +
			(cur->bc_ops->key_len / 2));
पूर्ण

/* Determine the low (and high अगर overlapped) keys of a leaf block */
STATIC व्योम
xfs_btree_get_leaf_keys(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	जोड़ xfs_btree_key	*key)
अणु
	जोड़ xfs_btree_key	max_hkey;
	जोड़ xfs_btree_key	hkey;
	जोड़ xfs_btree_rec	*rec;
	जोड़ xfs_btree_key	*high;
	पूर्णांक			n;

	rec = xfs_btree_rec_addr(cur, 1, block);
	cur->bc_ops->init_key_from_rec(key, rec);

	अगर (cur->bc_flags & XFS_BTREE_OVERLAPPING) अणु

		cur->bc_ops->init_high_key_from_rec(&max_hkey, rec);
		क्रम (n = 2; n <= xfs_btree_get_numrecs(block); n++) अणु
			rec = xfs_btree_rec_addr(cur, n, block);
			cur->bc_ops->init_high_key_from_rec(&hkey, rec);
			अगर (cur->bc_ops->dअगरf_two_keys(cur, &hkey, &max_hkey)
					> 0)
				max_hkey = hkey;
		पूर्ण

		high = xfs_btree_high_key_from_key(cur, key);
		स_नकल(high, &max_hkey, cur->bc_ops->key_len / 2);
	पूर्ण
पूर्ण

/* Determine the low (and high अगर overlapped) keys of a node block */
STATIC व्योम
xfs_btree_get_node_keys(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	जोड़ xfs_btree_key	*key)
अणु
	जोड़ xfs_btree_key	*hkey;
	जोड़ xfs_btree_key	*max_hkey;
	जोड़ xfs_btree_key	*high;
	पूर्णांक			n;

	अगर (cur->bc_flags & XFS_BTREE_OVERLAPPING) अणु
		स_नकल(key, xfs_btree_key_addr(cur, 1, block),
				cur->bc_ops->key_len / 2);

		max_hkey = xfs_btree_high_key_addr(cur, 1, block);
		क्रम (n = 2; n <= xfs_btree_get_numrecs(block); n++) अणु
			hkey = xfs_btree_high_key_addr(cur, n, block);
			अगर (cur->bc_ops->dअगरf_two_keys(cur, hkey, max_hkey) > 0)
				max_hkey = hkey;
		पूर्ण

		high = xfs_btree_high_key_from_key(cur, key);
		स_नकल(high, max_hkey, cur->bc_ops->key_len / 2);
	पूर्ण अन्यथा अणु
		स_नकल(key, xfs_btree_key_addr(cur, 1, block),
				cur->bc_ops->key_len);
	पूर्ण
पूर्ण

/* Derive the keys क्रम any btree block. */
व्योम
xfs_btree_get_keys(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	जोड़ xfs_btree_key	*key)
अणु
	अगर (be16_to_cpu(block->bb_level) == 0)
		xfs_btree_get_leaf_keys(cur, block, key);
	अन्यथा
		xfs_btree_get_node_keys(cur, block, key);
पूर्ण

/*
 * Decide अगर we need to update the parent keys of a btree block.  For
 * a standard btree this is only necessary अगर we're updating the first
 * record/key.  For an overlapping btree, we must always update the
 * keys because the highest key can be in any of the records or keys
 * in the block.
 */
अटल अंतरभूत bool
xfs_btree_needs_key_update(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			ptr)
अणु
	वापस (cur->bc_flags & XFS_BTREE_OVERLAPPING) || ptr == 1;
पूर्ण

/*
 * Update the low and high parent keys of the given level, progressing
 * towards the root.  If क्रमce_all is false, stop अगर the keys क्रम a given
 * level करो not need updating.
 */
STATIC पूर्णांक
__xfs_btree_updkeys(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	काष्ठा xfs_btree_block	*block,
	काष्ठा xfs_buf		*bp0,
	bool			क्रमce_all)
अणु
	जोड़ xfs_btree_key	key;	/* keys from current level */
	जोड़ xfs_btree_key	*lkey;	/* keys from the next level up */
	जोड़ xfs_btree_key	*hkey;
	जोड़ xfs_btree_key	*nlkey;	/* keys from the next level up */
	जोड़ xfs_btree_key	*nhkey;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			ptr;

	ASSERT(cur->bc_flags & XFS_BTREE_OVERLAPPING);

	/* Exit अगर there aren't any parent levels to update. */
	अगर (level + 1 >= cur->bc_nlevels)
		वापस 0;

	trace_xfs_btree_updkeys(cur, level, bp0);

	lkey = &key;
	hkey = xfs_btree_high_key_from_key(cur, lkey);
	xfs_btree_get_keys(cur, block, lkey);
	क्रम (level++; level < cur->bc_nlevels; level++) अणु
#अगर_घोषित DEBUG
		पूर्णांक		error;
#पूर्ण_अगर
		block = xfs_btree_get_block(cur, level, &bp);
		trace_xfs_btree_updkeys(cur, level, bp);
#अगर_घोषित DEBUG
		error = xfs_btree_check_block(cur, block, level, bp);
		अगर (error)
			वापस error;
#पूर्ण_अगर
		ptr = cur->bc_ptrs[level];
		nlkey = xfs_btree_key_addr(cur, ptr, block);
		nhkey = xfs_btree_high_key_addr(cur, ptr, block);
		अगर (!क्रमce_all &&
		    !(cur->bc_ops->dअगरf_two_keys(cur, nlkey, lkey) != 0 ||
		      cur->bc_ops->dअगरf_two_keys(cur, nhkey, hkey) != 0))
			अवरोध;
		xfs_btree_copy_keys(cur, nlkey, lkey, 1);
		xfs_btree_log_keys(cur, bp, ptr, ptr);
		अगर (level + 1 >= cur->bc_nlevels)
			अवरोध;
		xfs_btree_get_node_keys(cur, block, lkey);
	पूर्ण

	वापस 0;
पूर्ण

/* Update all the keys from some level in cursor back to the root. */
STATIC पूर्णांक
xfs_btree_updkeys_क्रमce(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_btree_block	*block;

	block = xfs_btree_get_block(cur, level, &bp);
	वापस __xfs_btree_updkeys(cur, level, block, bp, true);
पूर्ण

/*
 * Update the parent keys of the given level, progressing towards the root.
 */
STATIC पूर्णांक
xfs_btree_update_keys(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_buf		*bp;
	जोड़ xfs_btree_key	*kp;
	जोड़ xfs_btree_key	key;
	पूर्णांक			ptr;

	ASSERT(level >= 0);

	block = xfs_btree_get_block(cur, level, &bp);
	अगर (cur->bc_flags & XFS_BTREE_OVERLAPPING)
		वापस __xfs_btree_updkeys(cur, level, block, bp, false);

	/*
	 * Go up the tree from this level toward the root.
	 * At each level, update the key value to the value input.
	 * Stop when we reach a level where the cursor isn't poपूर्णांकing
	 * at the first entry in the block.
	 */
	xfs_btree_get_keys(cur, block, &key);
	क्रम (level++, ptr = 1; ptr == 1 && level < cur->bc_nlevels; level++) अणु
#अगर_घोषित DEBUG
		पूर्णांक		error;
#पूर्ण_अगर
		block = xfs_btree_get_block(cur, level, &bp);
#अगर_घोषित DEBUG
		error = xfs_btree_check_block(cur, block, level, bp);
		अगर (error)
			वापस error;
#पूर्ण_अगर
		ptr = cur->bc_ptrs[level];
		kp = xfs_btree_key_addr(cur, ptr, block);
		xfs_btree_copy_keys(cur, kp, &key, 1);
		xfs_btree_log_keys(cur, bp, ptr, ptr);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Update the record referred to by cur to the value in the
 * given record. This either works (वापस 0) or माला_लो an
 * EFSCORRUPTED error.
 */
पूर्णांक
xfs_btree_update(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*rec)
अणु
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;
	पूर्णांक			ptr;
	जोड़ xfs_btree_rec	*rp;

	/* Pick up the current block. */
	block = xfs_btree_get_block(cur, 0, &bp);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, block, 0, bp);
	अगर (error)
		जाओ error0;
#पूर्ण_अगर
	/* Get the address of the rec to be updated. */
	ptr = cur->bc_ptrs[0];
	rp = xfs_btree_rec_addr(cur, ptr, block);

	/* Fill in the new contents and log them. */
	xfs_btree_copy_recs(cur, rp, rec, 1);
	xfs_btree_log_recs(cur, bp, ptr, ptr);

	/*
	 * If we are tracking the last record in the tree and
	 * we are at the far right edge of the tree, update it.
	 */
	अगर (xfs_btree_is_lastrec(cur, block, 0)) अणु
		cur->bc_ops->update_lastrec(cur, block, rec,
					    ptr, LASTREC_UPDATE);
	पूर्ण

	/* Pass new key value up to our parent. */
	अगर (xfs_btree_needs_key_update(cur, ptr)) अणु
		error = xfs_btree_update_keys(cur, 0);
		अगर (error)
			जाओ error0;
	पूर्ण

	वापस 0;

error0:
	वापस error;
पूर्ण

/*
 * Move 1 record left from cur/level अगर possible.
 * Update cur to reflect the new path.
 */
STATIC पूर्णांक					/* error */
xfs_btree_lshअगरt(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	पूर्णांक			*stat)		/* success/failure */
अणु
	काष्ठा xfs_buf		*lbp;		/* left buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*left;		/* left btree block */
	पूर्णांक			lrecs;		/* left record count */
	काष्ठा xfs_buf		*rbp;		/* right buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*right;		/* right btree block */
	काष्ठा xfs_btree_cur	*tcur;		/* temporary btree cursor */
	पूर्णांक			rrecs;		/* right record count */
	जोड़ xfs_btree_ptr	lptr;		/* left btree poपूर्णांकer */
	जोड़ xfs_btree_key	*rkp = शून्य;	/* right btree key */
	जोड़ xfs_btree_ptr	*rpp = शून्य;	/* right address poपूर्णांकer */
	जोड़ xfs_btree_rec	*rrp = शून्य;	/* right record poपूर्णांकer */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			i;

	अगर ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    level == cur->bc_nlevels - 1)
		जाओ out0;

	/* Set up variables क्रम this block as "right". */
	right = xfs_btree_get_block(cur, level, &rbp);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, right, level, rbp);
	अगर (error)
		जाओ error0;
#पूर्ण_अगर

	/* If we've got no left sibling then we can't shअगरt an entry left. */
	xfs_btree_get_sibling(cur, right, &lptr, XFS_BB_LEFTSIB);
	अगर (xfs_btree_ptr_is_null(cur, &lptr))
		जाओ out0;

	/*
	 * If the cursor entry is the one that would be moved, करोn't
	 * करो it... it's too complicated.
	 */
	अगर (cur->bc_ptrs[level] <= 1)
		जाओ out0;

	/* Set up the left neighbor as "left". */
	error = xfs_btree_पढ़ो_buf_block(cur, &lptr, 0, &left, &lbp);
	अगर (error)
		जाओ error0;

	/* If it's full, it can't take another entry. */
	lrecs = xfs_btree_get_numrecs(left);
	अगर (lrecs == cur->bc_ops->get_maxrecs(cur, level))
		जाओ out0;

	rrecs = xfs_btree_get_numrecs(right);

	/*
	 * We add one entry to the left side and हटाओ one क्रम the right side.
	 * Account क्रम it here, the changes will be updated on disk and logged
	 * later.
	 */
	lrecs++;
	rrecs--;

	XFS_BTREE_STATS_INC(cur, lshअगरt);
	XFS_BTREE_STATS_ADD(cur, moves, 1);

	/*
	 * If non-leaf, copy a key and a ptr to the left block.
	 * Log the changes to the left block.
	 */
	अगर (level > 0) अणु
		/* It's a non-leaf.  Move keys and poपूर्णांकers. */
		जोड़ xfs_btree_key	*lkp;	/* left btree key */
		जोड़ xfs_btree_ptr	*lpp;	/* left address poपूर्णांकer */

		lkp = xfs_btree_key_addr(cur, lrecs, left);
		rkp = xfs_btree_key_addr(cur, 1, right);

		lpp = xfs_btree_ptr_addr(cur, lrecs, left);
		rpp = xfs_btree_ptr_addr(cur, 1, right);

		error = xfs_btree_debug_check_ptr(cur, rpp, 0, level);
		अगर (error)
			जाओ error0;

		xfs_btree_copy_keys(cur, lkp, rkp, 1);
		xfs_btree_copy_ptrs(cur, lpp, rpp, 1);

		xfs_btree_log_keys(cur, lbp, lrecs, lrecs);
		xfs_btree_log_ptrs(cur, lbp, lrecs, lrecs);

		ASSERT(cur->bc_ops->keys_inorder(cur,
			xfs_btree_key_addr(cur, lrecs - 1, left), lkp));
	पूर्ण अन्यथा अणु
		/* It's a leaf.  Move records.  */
		जोड़ xfs_btree_rec	*lrp;	/* left record poपूर्णांकer */

		lrp = xfs_btree_rec_addr(cur, lrecs, left);
		rrp = xfs_btree_rec_addr(cur, 1, right);

		xfs_btree_copy_recs(cur, lrp, rrp, 1);
		xfs_btree_log_recs(cur, lbp, lrecs, lrecs);

		ASSERT(cur->bc_ops->recs_inorder(cur,
			xfs_btree_rec_addr(cur, lrecs - 1, left), lrp));
	पूर्ण

	xfs_btree_set_numrecs(left, lrecs);
	xfs_btree_log_block(cur, lbp, XFS_BB_NUMRECS);

	xfs_btree_set_numrecs(right, rrecs);
	xfs_btree_log_block(cur, rbp, XFS_BB_NUMRECS);

	/*
	 * Slide the contents of right करोwn one entry.
	 */
	XFS_BTREE_STATS_ADD(cur, moves, rrecs - 1);
	अगर (level > 0) अणु
		/* It's a nonleaf. operate on keys and ptrs */
		क्रम (i = 0; i < rrecs; i++) अणु
			error = xfs_btree_debug_check_ptr(cur, rpp, i + 1, level);
			अगर (error)
				जाओ error0;
		पूर्ण

		xfs_btree_shअगरt_keys(cur,
				xfs_btree_key_addr(cur, 2, right),
				-1, rrecs);
		xfs_btree_shअगरt_ptrs(cur,
				xfs_btree_ptr_addr(cur, 2, right),
				-1, rrecs);

		xfs_btree_log_keys(cur, rbp, 1, rrecs);
		xfs_btree_log_ptrs(cur, rbp, 1, rrecs);
	पूर्ण अन्यथा अणु
		/* It's a leaf. operate on records */
		xfs_btree_shअगरt_recs(cur,
			xfs_btree_rec_addr(cur, 2, right),
			-1, rrecs);
		xfs_btree_log_recs(cur, rbp, 1, rrecs);
	पूर्ण

	/*
	 * Using a temporary cursor, update the parent key values of the
	 * block on the left.
	 */
	अगर (cur->bc_flags & XFS_BTREE_OVERLAPPING) अणु
		error = xfs_btree_dup_cursor(cur, &tcur);
		अगर (error)
			जाओ error0;
		i = xfs_btree_firstrec(tcur, level);
		अगर (XFS_IS_CORRUPT(tcur->bc_mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण

		error = xfs_btree_decrement(tcur, level, &i);
		अगर (error)
			जाओ error1;

		/* Update the parent high keys of the left block, अगर needed. */
		error = xfs_btree_update_keys(tcur, level);
		अगर (error)
			जाओ error1;

		xfs_btree_del_cursor(tcur, XFS_BTREE_NOERROR);
	पूर्ण

	/* Update the parent keys of the right block. */
	error = xfs_btree_update_keys(cur, level);
	अगर (error)
		जाओ error0;

	/* Slide the cursor value left one. */
	cur->bc_ptrs[level]--;

	*stat = 1;
	वापस 0;

out0:
	*stat = 0;
	वापस 0;

error0:
	वापस error;

error1:
	xfs_btree_del_cursor(tcur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/*
 * Move 1 record right from cur/level अगर possible.
 * Update cur to reflect the new path.
 */
STATIC पूर्णांक					/* error */
xfs_btree_rshअगरt(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	पूर्णांक			*stat)		/* success/failure */
अणु
	काष्ठा xfs_buf		*lbp;		/* left buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*left;		/* left btree block */
	काष्ठा xfs_buf		*rbp;		/* right buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*right;		/* right btree block */
	काष्ठा xfs_btree_cur	*tcur;		/* temporary btree cursor */
	जोड़ xfs_btree_ptr	rptr;		/* right block poपूर्णांकer */
	जोड़ xfs_btree_key	*rkp;		/* right btree key */
	पूर्णांक			rrecs;		/* right record count */
	पूर्णांक			lrecs;		/* left record count */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			i;		/* loop counter */

	अगर ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    (level == cur->bc_nlevels - 1))
		जाओ out0;

	/* Set up variables क्रम this block as "left". */
	left = xfs_btree_get_block(cur, level, &lbp);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, left, level, lbp);
	अगर (error)
		जाओ error0;
#पूर्ण_अगर

	/* If we've got no right sibling then we can't shअगरt an entry right. */
	xfs_btree_get_sibling(cur, left, &rptr, XFS_BB_RIGHTSIB);
	अगर (xfs_btree_ptr_is_null(cur, &rptr))
		जाओ out0;

	/*
	 * If the cursor entry is the one that would be moved, करोn't
	 * करो it... it's too complicated.
	 */
	lrecs = xfs_btree_get_numrecs(left);
	अगर (cur->bc_ptrs[level] >= lrecs)
		जाओ out0;

	/* Set up the right neighbor as "right". */
	error = xfs_btree_पढ़ो_buf_block(cur, &rptr, 0, &right, &rbp);
	अगर (error)
		जाओ error0;

	/* If it's full, it can't take another entry. */
	rrecs = xfs_btree_get_numrecs(right);
	अगर (rrecs == cur->bc_ops->get_maxrecs(cur, level))
		जाओ out0;

	XFS_BTREE_STATS_INC(cur, rshअगरt);
	XFS_BTREE_STATS_ADD(cur, moves, rrecs);

	/*
	 * Make a hole at the start of the right neighbor block, then
	 * copy the last left block entry to the hole.
	 */
	अगर (level > 0) अणु
		/* It's a nonleaf. make a hole in the keys and ptrs */
		जोड़ xfs_btree_key	*lkp;
		जोड़ xfs_btree_ptr	*lpp;
		जोड़ xfs_btree_ptr	*rpp;

		lkp = xfs_btree_key_addr(cur, lrecs, left);
		lpp = xfs_btree_ptr_addr(cur, lrecs, left);
		rkp = xfs_btree_key_addr(cur, 1, right);
		rpp = xfs_btree_ptr_addr(cur, 1, right);

		क्रम (i = rrecs - 1; i >= 0; i--) अणु
			error = xfs_btree_debug_check_ptr(cur, rpp, i, level);
			अगर (error)
				जाओ error0;
		पूर्ण

		xfs_btree_shअगरt_keys(cur, rkp, 1, rrecs);
		xfs_btree_shअगरt_ptrs(cur, rpp, 1, rrecs);

		error = xfs_btree_debug_check_ptr(cur, lpp, 0, level);
		अगर (error)
			जाओ error0;

		/* Now put the new data in, and log it. */
		xfs_btree_copy_keys(cur, rkp, lkp, 1);
		xfs_btree_copy_ptrs(cur, rpp, lpp, 1);

		xfs_btree_log_keys(cur, rbp, 1, rrecs + 1);
		xfs_btree_log_ptrs(cur, rbp, 1, rrecs + 1);

		ASSERT(cur->bc_ops->keys_inorder(cur, rkp,
			xfs_btree_key_addr(cur, 2, right)));
	पूर्ण अन्यथा अणु
		/* It's a leaf. make a hole in the records */
		जोड़ xfs_btree_rec	*lrp;
		जोड़ xfs_btree_rec	*rrp;

		lrp = xfs_btree_rec_addr(cur, lrecs, left);
		rrp = xfs_btree_rec_addr(cur, 1, right);

		xfs_btree_shअगरt_recs(cur, rrp, 1, rrecs);

		/* Now put the new data in, and log it. */
		xfs_btree_copy_recs(cur, rrp, lrp, 1);
		xfs_btree_log_recs(cur, rbp, 1, rrecs + 1);
	पूर्ण

	/*
	 * Decrement and log left's numrecs, bump and log right's numrecs.
	 */
	xfs_btree_set_numrecs(left, --lrecs);
	xfs_btree_log_block(cur, lbp, XFS_BB_NUMRECS);

	xfs_btree_set_numrecs(right, ++rrecs);
	xfs_btree_log_block(cur, rbp, XFS_BB_NUMRECS);

	/*
	 * Using a temporary cursor, update the parent key values of the
	 * block on the right.
	 */
	error = xfs_btree_dup_cursor(cur, &tcur);
	अगर (error)
		जाओ error0;
	i = xfs_btree_lastrec(tcur, level);
	अगर (XFS_IS_CORRUPT(tcur->bc_mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण

	error = xfs_btree_increment(tcur, level, &i);
	अगर (error)
		जाओ error1;

	/* Update the parent high keys of the left block, अगर needed. */
	अगर (cur->bc_flags & XFS_BTREE_OVERLAPPING) अणु
		error = xfs_btree_update_keys(cur, level);
		अगर (error)
			जाओ error1;
	पूर्ण

	/* Update the parent keys of the right block. */
	error = xfs_btree_update_keys(tcur, level);
	अगर (error)
		जाओ error1;

	xfs_btree_del_cursor(tcur, XFS_BTREE_NOERROR);

	*stat = 1;
	वापस 0;

out0:
	*stat = 0;
	वापस 0;

error0:
	वापस error;

error1:
	xfs_btree_del_cursor(tcur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/*
 * Split cur/level block in half.
 * Return new block number and the key to its first
 * record (to be inserted पूर्णांकo parent).
 */
STATIC पूर्णांक					/* error */
__xfs_btree_split(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	जोड़ xfs_btree_ptr	*ptrp,
	जोड़ xfs_btree_key	*key,
	काष्ठा xfs_btree_cur	**curp,
	पूर्णांक			*stat)		/* success/failure */
अणु
	जोड़ xfs_btree_ptr	lptr;		/* left sibling block ptr */
	काष्ठा xfs_buf		*lbp;		/* left buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*left;		/* left btree block */
	जोड़ xfs_btree_ptr	rptr;		/* right sibling block ptr */
	काष्ठा xfs_buf		*rbp;		/* right buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*right;		/* right btree block */
	जोड़ xfs_btree_ptr	rrptr;		/* right-right sibling ptr */
	काष्ठा xfs_buf		*rrbp;		/* right-right buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*rrblock;	/* right-right btree block */
	पूर्णांक			lrecs;
	पूर्णांक			rrecs;
	पूर्णांक			src_index;
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			i;

	XFS_BTREE_STATS_INC(cur, split);

	/* Set up left block (current one). */
	left = xfs_btree_get_block(cur, level, &lbp);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, left, level, lbp);
	अगर (error)
		जाओ error0;
#पूर्ण_अगर

	xfs_btree_buf_to_ptr(cur, lbp, &lptr);

	/* Allocate the new block. If we can't do it, we're toast. Give up. */
	error = cur->bc_ops->alloc_block(cur, &lptr, &rptr, stat);
	अगर (error)
		जाओ error0;
	अगर (*stat == 0)
		जाओ out0;
	XFS_BTREE_STATS_INC(cur, alloc);

	/* Set up the new block as "right". */
	error = xfs_btree_get_buf_block(cur, &rptr, &right, &rbp);
	अगर (error)
		जाओ error0;

	/* Fill in the btree header क्रम the new right block. */
	xfs_btree_init_block_cur(cur, rbp, xfs_btree_get_level(left), 0);

	/*
	 * Split the entries between the old and the new block evenly.
	 * Make sure that अगर there's an odd number of entries now, that
	 * each new block will have the same number of entries.
	 */
	lrecs = xfs_btree_get_numrecs(left);
	rrecs = lrecs / 2;
	अगर ((lrecs & 1) && cur->bc_ptrs[level] <= rrecs + 1)
		rrecs++;
	src_index = (lrecs - rrecs + 1);

	XFS_BTREE_STATS_ADD(cur, moves, rrecs);

	/* Adjust numrecs क्रम the later get_*_keys() calls. */
	lrecs -= rrecs;
	xfs_btree_set_numrecs(left, lrecs);
	xfs_btree_set_numrecs(right, xfs_btree_get_numrecs(right) + rrecs);

	/*
	 * Copy btree block entries from the left block over to the
	 * new block, the right. Update the right block and log the
	 * changes.
	 */
	अगर (level > 0) अणु
		/* It's a non-leaf.  Move keys and poपूर्णांकers. */
		जोड़ xfs_btree_key	*lkp;	/* left btree key */
		जोड़ xfs_btree_ptr	*lpp;	/* left address poपूर्णांकer */
		जोड़ xfs_btree_key	*rkp;	/* right btree key */
		जोड़ xfs_btree_ptr	*rpp;	/* right address poपूर्णांकer */

		lkp = xfs_btree_key_addr(cur, src_index, left);
		lpp = xfs_btree_ptr_addr(cur, src_index, left);
		rkp = xfs_btree_key_addr(cur, 1, right);
		rpp = xfs_btree_ptr_addr(cur, 1, right);

		क्रम (i = src_index; i < rrecs; i++) अणु
			error = xfs_btree_debug_check_ptr(cur, lpp, i, level);
			अगर (error)
				जाओ error0;
		पूर्ण

		/* Copy the keys & poपूर्णांकers to the new block. */
		xfs_btree_copy_keys(cur, rkp, lkp, rrecs);
		xfs_btree_copy_ptrs(cur, rpp, lpp, rrecs);

		xfs_btree_log_keys(cur, rbp, 1, rrecs);
		xfs_btree_log_ptrs(cur, rbp, 1, rrecs);

		/* Stash the keys of the new block क्रम later insertion. */
		xfs_btree_get_node_keys(cur, right, key);
	पूर्ण अन्यथा अणु
		/* It's a leaf.  Move records.  */
		जोड़ xfs_btree_rec	*lrp;	/* left record poपूर्णांकer */
		जोड़ xfs_btree_rec	*rrp;	/* right record poपूर्णांकer */

		lrp = xfs_btree_rec_addr(cur, src_index, left);
		rrp = xfs_btree_rec_addr(cur, 1, right);

		/* Copy records to the new block. */
		xfs_btree_copy_recs(cur, rrp, lrp, rrecs);
		xfs_btree_log_recs(cur, rbp, 1, rrecs);

		/* Stash the keys of the new block क्रम later insertion. */
		xfs_btree_get_leaf_keys(cur, right, key);
	पूर्ण

	/*
	 * Find the left block number by looking in the buffer.
	 * Adjust sibling poपूर्णांकers.
	 */
	xfs_btree_get_sibling(cur, left, &rrptr, XFS_BB_RIGHTSIB);
	xfs_btree_set_sibling(cur, right, &rrptr, XFS_BB_RIGHTSIB);
	xfs_btree_set_sibling(cur, right, &lptr, XFS_BB_LEFTSIB);
	xfs_btree_set_sibling(cur, left, &rptr, XFS_BB_RIGHTSIB);

	xfs_btree_log_block(cur, rbp, XFS_BB_ALL_BITS);
	xfs_btree_log_block(cur, lbp, XFS_BB_NUMRECS | XFS_BB_RIGHTSIB);

	/*
	 * If there's a block to the new block's right, make that block
	 * poपूर्णांक back to right instead of to left.
	 */
	अगर (!xfs_btree_ptr_is_null(cur, &rrptr)) अणु
		error = xfs_btree_पढ़ो_buf_block(cur, &rrptr,
							0, &rrblock, &rrbp);
		अगर (error)
			जाओ error0;
		xfs_btree_set_sibling(cur, rrblock, &rptr, XFS_BB_LEFTSIB);
		xfs_btree_log_block(cur, rrbp, XFS_BB_LEFTSIB);
	पूर्ण

	/* Update the parent high keys of the left block, अगर needed. */
	अगर (cur->bc_flags & XFS_BTREE_OVERLAPPING) अणु
		error = xfs_btree_update_keys(cur, level);
		अगर (error)
			जाओ error0;
	पूर्ण

	/*
	 * If the cursor is really in the right block, move it there.
	 * If it's just pointing past the last entry in left, then we'll
	 * insert there, so करोn't change anything in that हाल.
	 */
	अगर (cur->bc_ptrs[level] > lrecs + 1) अणु
		xfs_btree_रखो_बफ(cur, level, rbp);
		cur->bc_ptrs[level] -= lrecs;
	पूर्ण
	/*
	 * If there are more levels, we'll need another cursor which refers
	 * the right block, no matter where this cursor was.
	 */
	अगर (level + 1 < cur->bc_nlevels) अणु
		error = xfs_btree_dup_cursor(cur, curp);
		अगर (error)
			जाओ error0;
		(*curp)->bc_ptrs[level + 1]++;
	पूर्ण
	*ptrp = rptr;
	*stat = 1;
	वापस 0;
out0:
	*stat = 0;
	वापस 0;

error0:
	वापस error;
पूर्ण

काष्ठा xfs_btree_split_args अणु
	काष्ठा xfs_btree_cur	*cur;
	पूर्णांक			level;
	जोड़ xfs_btree_ptr	*ptrp;
	जोड़ xfs_btree_key	*key;
	काष्ठा xfs_btree_cur	**curp;
	पूर्णांक			*stat;		/* success/failure */
	पूर्णांक			result;
	bool			kswapd;	/* allocation in kswapd context */
	काष्ठा completion	*करोne;
	काष्ठा work_काष्ठा	work;
पूर्ण;

/*
 * Stack चयनing पूर्णांकerfaces क्रम allocation
 */
अटल व्योम
xfs_btree_split_worker(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xfs_btree_split_args	*args = container_of(work,
						काष्ठा xfs_btree_split_args, work);
	अचिन्हित दीर्घ		pflags;
	अचिन्हित दीर्घ		new_pflags = 0;

	/*
	 * we are in a transaction context here, but may also be करोing work
	 * in kswapd context, and hence we may need to inherit that state
	 * temporarily to ensure that we करोn't block रुकोing क्रम memory reclaim
	 * in any way.
	 */
	अगर (args->kswapd)
		new_pflags |= PF_MEMALLOC | PF_SWAPWRITE | PF_KSWAPD;

	current_set_flags_nested(&pflags, new_pflags);
	xfs_trans_set_context(args->cur->bc_tp);

	args->result = __xfs_btree_split(args->cur, args->level, args->ptrp,
					 args->key, args->curp, args->stat);

	xfs_trans_clear_context(args->cur->bc_tp);
	current_restore_flags_nested(&pflags, new_pflags);

	/*
	 * Do not access args after complete() has run here. We करोn't own args
	 * and the owner may run and मुक्त args beक्रमe we वापस here.
	 */
	complete(args->करोne);

पूर्ण

/*
 * BMBT split requests often come in with little stack to work on. Push
 * them off to a worker thपढ़ो so there is lots of stack to use. For the other
 * btree types, just call directly to aव्योम the context चयन overhead here.
 */
STATIC पूर्णांक					/* error */
xfs_btree_split(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	जोड़ xfs_btree_ptr	*ptrp,
	जोड़ xfs_btree_key	*key,
	काष्ठा xfs_btree_cur	**curp,
	पूर्णांक			*stat)		/* success/failure */
अणु
	काष्ठा xfs_btree_split_args	args;
	DECLARE_COMPLETION_ONSTACK(करोne);

	अगर (cur->bc_btnum != XFS_BTNUM_BMAP)
		वापस __xfs_btree_split(cur, level, ptrp, key, curp, stat);

	args.cur = cur;
	args.level = level;
	args.ptrp = ptrp;
	args.key = key;
	args.curp = curp;
	args.stat = stat;
	args.करोne = &करोne;
	args.kswapd = current_is_kswapd();
	INIT_WORK_ONSTACK(&args.work, xfs_btree_split_worker);
	queue_work(xfs_alloc_wq, &args.work);
	रुको_क्रम_completion(&करोne);
	destroy_work_on_stack(&args.work);
	वापस args.result;
पूर्ण


/*
 * Copy the old inode root contents पूर्णांकo a real block and make the
 * broot poपूर्णांक to it.
 */
पूर्णांक						/* error */
xfs_btree_new_iroot(
	काष्ठा xfs_btree_cur	*cur,		/* btree cursor */
	पूर्णांक			*logflags,	/* logging flags क्रम inode */
	पूर्णांक			*stat)		/* वापस status - 0 fail */
अणु
	काष्ठा xfs_buf		*cbp;		/* buffer क्रम cblock */
	काष्ठा xfs_btree_block	*block;		/* btree block */
	काष्ठा xfs_btree_block	*cblock;	/* child btree block */
	जोड़ xfs_btree_key	*ckp;		/* child key poपूर्णांकer */
	जोड़ xfs_btree_ptr	*cpp;		/* child ptr poपूर्णांकer */
	जोड़ xfs_btree_key	*kp;		/* poपूर्णांकer to btree key */
	जोड़ xfs_btree_ptr	*pp;		/* poपूर्णांकer to block addr */
	जोड़ xfs_btree_ptr	nptr;		/* new block addr */
	पूर्णांक			level;		/* btree level */
	पूर्णांक			error;		/* error वापस code */
	पूर्णांक			i;		/* loop counter */

	XFS_BTREE_STATS_INC(cur, newroot);

	ASSERT(cur->bc_flags & XFS_BTREE_ROOT_IN_INODE);

	level = cur->bc_nlevels - 1;

	block = xfs_btree_get_iroot(cur);
	pp = xfs_btree_ptr_addr(cur, 1, block);

	/* Allocate the new block. If we can't do it, we're toast. Give up. */
	error = cur->bc_ops->alloc_block(cur, pp, &nptr, stat);
	अगर (error)
		जाओ error0;
	अगर (*stat == 0)
		वापस 0;

	XFS_BTREE_STATS_INC(cur, alloc);

	/* Copy the root पूर्णांकo a real block. */
	error = xfs_btree_get_buf_block(cur, &nptr, &cblock, &cbp);
	अगर (error)
		जाओ error0;

	/*
	 * we can't just स_नकल() the root in क्रम CRC enabled btree blocks.
	 * In that हाल have to also ensure the blkno reमुख्यs correct
	 */
	स_नकल(cblock, block, xfs_btree_block_len(cur));
	अगर (cur->bc_flags & XFS_BTREE_CRC_BLOCKS) अणु
		अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS)
			cblock->bb_u.l.bb_blkno = cpu_to_be64(cbp->b_bn);
		अन्यथा
			cblock->bb_u.s.bb_blkno = cpu_to_be64(cbp->b_bn);
	पूर्ण

	be16_add_cpu(&block->bb_level, 1);
	xfs_btree_set_numrecs(block, 1);
	cur->bc_nlevels++;
	cur->bc_ptrs[level + 1] = 1;

	kp = xfs_btree_key_addr(cur, 1, block);
	ckp = xfs_btree_key_addr(cur, 1, cblock);
	xfs_btree_copy_keys(cur, ckp, kp, xfs_btree_get_numrecs(cblock));

	cpp = xfs_btree_ptr_addr(cur, 1, cblock);
	क्रम (i = 0; i < be16_to_cpu(cblock->bb_numrecs); i++) अणु
		error = xfs_btree_debug_check_ptr(cur, pp, i, level);
		अगर (error)
			जाओ error0;
	पूर्ण

	xfs_btree_copy_ptrs(cur, cpp, pp, xfs_btree_get_numrecs(cblock));

	error = xfs_btree_debug_check_ptr(cur, &nptr, 0, level);
	अगर (error)
		जाओ error0;

	xfs_btree_copy_ptrs(cur, pp, &nptr, 1);

	xfs_iroot_पुनः_स्मृति(cur->bc_ino.ip,
			  1 - xfs_btree_get_numrecs(cblock),
			  cur->bc_ino.whichविभाजन);

	xfs_btree_रखो_बफ(cur, level, cbp);

	/*
	 * Do all this logging at the end so that
	 * the root is at the right level.
	 */
	xfs_btree_log_block(cur, cbp, XFS_BB_ALL_BITS);
	xfs_btree_log_keys(cur, cbp, 1, be16_to_cpu(cblock->bb_numrecs));
	xfs_btree_log_ptrs(cur, cbp, 1, be16_to_cpu(cblock->bb_numrecs));

	*logflags |=
		XFS_ILOG_CORE | xfs_ilog_fbroot(cur->bc_ino.whichविभाजन);
	*stat = 1;
	वापस 0;
error0:
	वापस error;
पूर्ण

/*
 * Allocate a new root block, fill it in.
 */
STATIC पूर्णांक				/* error */
xfs_btree_new_root(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	पूर्णांक			*stat)	/* success/failure */
अणु
	काष्ठा xfs_btree_block	*block;	/* one half of the old root block */
	काष्ठा xfs_buf		*bp;	/* buffer containing block */
	पूर्णांक			error;	/* error वापस value */
	काष्ठा xfs_buf		*lbp;	/* left buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*left;	/* left btree block */
	काष्ठा xfs_buf		*nbp;	/* new (root) buffer */
	काष्ठा xfs_btree_block	*new;	/* new (root) btree block */
	पूर्णांक			nptr;	/* new value क्रम key index, 1 or 2 */
	काष्ठा xfs_buf		*rbp;	/* right buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*right;	/* right btree block */
	जोड़ xfs_btree_ptr	rptr;
	जोड़ xfs_btree_ptr	lptr;

	XFS_BTREE_STATS_INC(cur, newroot);

	/* initialise our start poपूर्णांक from the cursor */
	cur->bc_ops->init_ptr_from_cur(cur, &rptr);

	/* Allocate the new block. If we can't do it, we're toast. Give up. */
	error = cur->bc_ops->alloc_block(cur, &rptr, &lptr, stat);
	अगर (error)
		जाओ error0;
	अगर (*stat == 0)
		जाओ out0;
	XFS_BTREE_STATS_INC(cur, alloc);

	/* Set up the new block. */
	error = xfs_btree_get_buf_block(cur, &lptr, &new, &nbp);
	अगर (error)
		जाओ error0;

	/* Set the root in the holding काष्ठाure  increasing the level by 1. */
	cur->bc_ops->set_root(cur, &lptr, 1);

	/*
	 * At the previous root level there are now two blocks: the old root,
	 * and the new block generated when it was split.  We करोn't know which
	 * one the cursor is poपूर्णांकing at, so we set up variables "left" and
	 * "right" क्रम each हाल.
	 */
	block = xfs_btree_get_block(cur, cur->bc_nlevels - 1, &bp);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, block, cur->bc_nlevels - 1, bp);
	अगर (error)
		जाओ error0;
#पूर्ण_अगर

	xfs_btree_get_sibling(cur, block, &rptr, XFS_BB_RIGHTSIB);
	अगर (!xfs_btree_ptr_is_null(cur, &rptr)) अणु
		/* Our block is left, pick up the right block. */
		lbp = bp;
		xfs_btree_buf_to_ptr(cur, lbp, &lptr);
		left = block;
		error = xfs_btree_पढ़ो_buf_block(cur, &rptr, 0, &right, &rbp);
		अगर (error)
			जाओ error0;
		bp = rbp;
		nptr = 1;
	पूर्ण अन्यथा अणु
		/* Our block is right, pick up the left block. */
		rbp = bp;
		xfs_btree_buf_to_ptr(cur, rbp, &rptr);
		right = block;
		xfs_btree_get_sibling(cur, right, &lptr, XFS_BB_LEFTSIB);
		error = xfs_btree_पढ़ो_buf_block(cur, &lptr, 0, &left, &lbp);
		अगर (error)
			जाओ error0;
		bp = lbp;
		nptr = 2;
	पूर्ण

	/* Fill in the new block's btree header and log it. */
	xfs_btree_init_block_cur(cur, nbp, cur->bc_nlevels, 2);
	xfs_btree_log_block(cur, nbp, XFS_BB_ALL_BITS);
	ASSERT(!xfs_btree_ptr_is_null(cur, &lptr) &&
			!xfs_btree_ptr_is_null(cur, &rptr));

	/* Fill in the key data in the new root. */
	अगर (xfs_btree_get_level(left) > 0) अणु
		/*
		 * Get the keys क्रम the left block's keys and put them directly
		 * in the parent block.  Do the same क्रम the right block.
		 */
		xfs_btree_get_node_keys(cur, left,
				xfs_btree_key_addr(cur, 1, new));
		xfs_btree_get_node_keys(cur, right,
				xfs_btree_key_addr(cur, 2, new));
	पूर्ण अन्यथा अणु
		/*
		 * Get the keys क्रम the left block's records and put them
		 * directly in the parent block.  Do the same क्रम the right
		 * block.
		 */
		xfs_btree_get_leaf_keys(cur, left,
			xfs_btree_key_addr(cur, 1, new));
		xfs_btree_get_leaf_keys(cur, right,
			xfs_btree_key_addr(cur, 2, new));
	पूर्ण
	xfs_btree_log_keys(cur, nbp, 1, 2);

	/* Fill in the poपूर्णांकer data in the new root. */
	xfs_btree_copy_ptrs(cur,
		xfs_btree_ptr_addr(cur, 1, new), &lptr, 1);
	xfs_btree_copy_ptrs(cur,
		xfs_btree_ptr_addr(cur, 2, new), &rptr, 1);
	xfs_btree_log_ptrs(cur, nbp, 1, 2);

	/* Fix up the cursor. */
	xfs_btree_रखो_बफ(cur, cur->bc_nlevels, nbp);
	cur->bc_ptrs[cur->bc_nlevels] = nptr;
	cur->bc_nlevels++;
	*stat = 1;
	वापस 0;
error0:
	वापस error;
out0:
	*stat = 0;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_btree_make_block_unfull(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	पूर्णांक			level,	/* btree level */
	पूर्णांक			numrecs,/* # of recs in block */
	पूर्णांक			*oindex,/* old tree index */
	पूर्णांक			*index,	/* new tree index */
	जोड़ xfs_btree_ptr	*nptr,	/* new btree ptr */
	काष्ठा xfs_btree_cur	**ncur,	/* new btree cursor */
	जोड़ xfs_btree_key	*key,	/* key of new block */
	पूर्णांक			*stat)
अणु
	पूर्णांक			error = 0;

	अगर ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    level == cur->bc_nlevels - 1) अणु
		काष्ठा xfs_inode *ip = cur->bc_ino.ip;

		अगर (numrecs < cur->bc_ops->get_dmaxrecs(cur, level)) अणु
			/* A root block that can be made bigger. */
			xfs_iroot_पुनः_स्मृति(ip, 1, cur->bc_ino.whichविभाजन);
			*stat = 1;
		पूर्ण अन्यथा अणु
			/* A root block that needs replacing */
			पूर्णांक	logflags = 0;

			error = xfs_btree_new_iroot(cur, &logflags, stat);
			अगर (error || *stat == 0)
				वापस error;

			xfs_trans_log_inode(cur->bc_tp, ip, logflags);
		पूर्ण

		वापस 0;
	पूर्ण

	/* First, try shअगरting an entry to the right neighbor. */
	error = xfs_btree_rshअगरt(cur, level, stat);
	अगर (error || *stat)
		वापस error;

	/* Next, try shअगरting an entry to the left neighbor. */
	error = xfs_btree_lshअगरt(cur, level, stat);
	अगर (error)
		वापस error;

	अगर (*stat) अणु
		*oindex = *index = cur->bc_ptrs[level];
		वापस 0;
	पूर्ण

	/*
	 * Next, try splitting the current block in half.
	 *
	 * If this works we have to re-set our variables because we
	 * could be in a dअगरferent block now.
	 */
	error = xfs_btree_split(cur, level, nptr, key, ncur, stat);
	अगर (error || *stat == 0)
		वापस error;


	*index = cur->bc_ptrs[level];
	वापस 0;
पूर्ण

/*
 * Insert one record/level.  Return inक्रमmation to the caller
 * allowing the next level up to proceed अगर necessary.
 */
STATIC पूर्णांक
xfs_btree_insrec(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	पूर्णांक			level,	/* level to insert record at */
	जोड़ xfs_btree_ptr	*ptrp,	/* i/o: block number inserted */
	जोड़ xfs_btree_rec	*rec,	/* record to insert */
	जोड़ xfs_btree_key	*key,	/* i/o: block key क्रम ptrp */
	काष्ठा xfs_btree_cur	**curp,	/* output: new cursor replacing cur */
	पूर्णांक			*stat)	/* success/failure */
अणु
	काष्ठा xfs_btree_block	*block;	/* btree block */
	काष्ठा xfs_buf		*bp;	/* buffer क्रम block */
	जोड़ xfs_btree_ptr	nptr;	/* new block ptr */
	काष्ठा xfs_btree_cur	*ncur;	/* new btree cursor */
	जोड़ xfs_btree_key	nkey;	/* new block key */
	जोड़ xfs_btree_key	*lkey;
	पूर्णांक			optr;	/* old key/record index */
	पूर्णांक			ptr;	/* key/record index */
	पूर्णांक			numrecs;/* number of records */
	पूर्णांक			error;	/* error वापस value */
	पूर्णांक			i;
	xfs_daddr_t		old_bn;

	ncur = शून्य;
	lkey = &nkey;

	/*
	 * If we have an बाह्यal root poपूर्णांकer, and we've made it to the
	 * root level, allocate a new root block and we're करोne.
	 */
	अगर (!(cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    (level >= cur->bc_nlevels)) अणु
		error = xfs_btree_new_root(cur, stat);
		xfs_btree_set_ptr_null(cur, ptrp);

		वापस error;
	पूर्ण

	/* If we're off the left edge, वापस failure. */
	ptr = cur->bc_ptrs[level];
	अगर (ptr == 0) अणु
		*stat = 0;
		वापस 0;
	पूर्ण

	optr = ptr;

	XFS_BTREE_STATS_INC(cur, insrec);

	/* Get poपूर्णांकers to the btree buffer and block. */
	block = xfs_btree_get_block(cur, level, &bp);
	old_bn = bp ? bp->b_bn : XFS_BUF_DADDR_शून्य;
	numrecs = xfs_btree_get_numrecs(block);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, block, level, bp);
	अगर (error)
		जाओ error0;

	/* Check that the new entry is being inserted in the right place. */
	अगर (ptr <= numrecs) अणु
		अगर (level == 0) अणु
			ASSERT(cur->bc_ops->recs_inorder(cur, rec,
				xfs_btree_rec_addr(cur, ptr, block)));
		पूर्ण अन्यथा अणु
			ASSERT(cur->bc_ops->keys_inorder(cur, key,
				xfs_btree_key_addr(cur, ptr, block)));
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * If the block is full, we can't insert the new entry until we
	 * make the block un-full.
	 */
	xfs_btree_set_ptr_null(cur, &nptr);
	अगर (numrecs == cur->bc_ops->get_maxrecs(cur, level)) अणु
		error = xfs_btree_make_block_unfull(cur, level, numrecs,
					&optr, &ptr, &nptr, &ncur, lkey, stat);
		अगर (error || *stat == 0)
			जाओ error0;
	पूर्ण

	/*
	 * The current block may have changed अगर the block was
	 * previously full and we have just made space in it.
	 */
	block = xfs_btree_get_block(cur, level, &bp);
	numrecs = xfs_btree_get_numrecs(block);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, block, level, bp);
	अगर (error)
		वापस error;
#पूर्ण_अगर

	/*
	 * At this poपूर्णांक we know there's room क्रम our new entry in the block
	 * we're poपूर्णांकing at.
	 */
	XFS_BTREE_STATS_ADD(cur, moves, numrecs - ptr + 1);

	अगर (level > 0) अणु
		/* It's a nonleaf. make a hole in the keys and ptrs */
		जोड़ xfs_btree_key	*kp;
		जोड़ xfs_btree_ptr	*pp;

		kp = xfs_btree_key_addr(cur, ptr, block);
		pp = xfs_btree_ptr_addr(cur, ptr, block);

		क्रम (i = numrecs - ptr; i >= 0; i--) अणु
			error = xfs_btree_debug_check_ptr(cur, pp, i, level);
			अगर (error)
				वापस error;
		पूर्ण

		xfs_btree_shअगरt_keys(cur, kp, 1, numrecs - ptr + 1);
		xfs_btree_shअगरt_ptrs(cur, pp, 1, numrecs - ptr + 1);

		error = xfs_btree_debug_check_ptr(cur, ptrp, 0, level);
		अगर (error)
			जाओ error0;

		/* Now put the new data in, bump numrecs and log it. */
		xfs_btree_copy_keys(cur, kp, key, 1);
		xfs_btree_copy_ptrs(cur, pp, ptrp, 1);
		numrecs++;
		xfs_btree_set_numrecs(block, numrecs);
		xfs_btree_log_ptrs(cur, bp, ptr, numrecs);
		xfs_btree_log_keys(cur, bp, ptr, numrecs);
#अगर_घोषित DEBUG
		अगर (ptr < numrecs) अणु
			ASSERT(cur->bc_ops->keys_inorder(cur, kp,
				xfs_btree_key_addr(cur, ptr + 1, block)));
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* It's a leaf. make a hole in the records */
		जोड़ xfs_btree_rec             *rp;

		rp = xfs_btree_rec_addr(cur, ptr, block);

		xfs_btree_shअगरt_recs(cur, rp, 1, numrecs - ptr + 1);

		/* Now put the new data in, bump numrecs and log it. */
		xfs_btree_copy_recs(cur, rp, rec, 1);
		xfs_btree_set_numrecs(block, ++numrecs);
		xfs_btree_log_recs(cur, bp, ptr, numrecs);
#अगर_घोषित DEBUG
		अगर (ptr < numrecs) अणु
			ASSERT(cur->bc_ops->recs_inorder(cur, rp,
				xfs_btree_rec_addr(cur, ptr + 1, block)));
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Log the new number of records in the btree header. */
	xfs_btree_log_block(cur, bp, XFS_BB_NUMRECS);

	/*
	 * If we just inserted पूर्णांकo a new tree block, we have to
	 * recalculate nkey here because nkey is out of date.
	 *
	 * Otherwise we're just updating an existing block (having shoved
	 * some records पूर्णांकo the new tree block), so use the regular key
	 * update mechanism.
	 */
	अगर (bp && bp->b_bn != old_bn) अणु
		xfs_btree_get_keys(cur, block, lkey);
	पूर्ण अन्यथा अगर (xfs_btree_needs_key_update(cur, optr)) अणु
		error = xfs_btree_update_keys(cur, level);
		अगर (error)
			जाओ error0;
	पूर्ण

	/*
	 * If we are tracking the last record in the tree and
	 * we are at the far right edge of the tree, update it.
	 */
	अगर (xfs_btree_is_lastrec(cur, block, level)) अणु
		cur->bc_ops->update_lastrec(cur, block, rec,
					    ptr, LASTREC_INSREC);
	पूर्ण

	/*
	 * Return the new block number, अगर any.
	 * If there is one, give back a record value and a cursor too.
	 */
	*ptrp = nptr;
	अगर (!xfs_btree_ptr_is_null(cur, &nptr)) अणु
		xfs_btree_copy_keys(cur, key, lkey, 1);
		*curp = ncur;
	पूर्ण

	*stat = 1;
	वापस 0;

error0:
	वापस error;
पूर्ण

/*
 * Insert the record at the poपूर्णांक referenced by cur.
 *
 * A multi-level split of the tree on insert will invalidate the original
 * cursor.  All callers of this function should assume that the cursor is
 * no दीर्घer valid and revalidate it.
 */
पूर्णांक
xfs_btree_insert(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			*stat)
अणु
	पूर्णांक			error;	/* error वापस value */
	पूर्णांक			i;	/* result value, 0 क्रम failure */
	पूर्णांक			level;	/* current level number in btree */
	जोड़ xfs_btree_ptr	nptr;	/* new block number (split result) */
	काष्ठा xfs_btree_cur	*ncur;	/* new cursor (split result) */
	काष्ठा xfs_btree_cur	*pcur;	/* previous level's cursor */
	जोड़ xfs_btree_key	bkey;	/* key of block to insert */
	जोड़ xfs_btree_key	*key;
	जोड़ xfs_btree_rec	rec;	/* record to insert */

	level = 0;
	ncur = शून्य;
	pcur = cur;
	key = &bkey;

	xfs_btree_set_ptr_null(cur, &nptr);

	/* Make a key out of the record data to be inserted, and save it. */
	cur->bc_ops->init_rec_from_cur(cur, &rec);
	cur->bc_ops->init_key_from_rec(key, &rec);

	/*
	 * Loop going up the tree, starting at the leaf level.
	 * Stop when we करोn't get a split block, that must mean that
	 * the insert is finished with this level.
	 */
	करो अणु
		/*
		 * Insert nrec/nptr पूर्णांकo this level of the tree.
		 * Note अगर we fail, nptr will be null.
		 */
		error = xfs_btree_insrec(pcur, level, &nptr, &rec, key,
				&ncur, &i);
		अगर (error) अणु
			अगर (pcur != cur)
				xfs_btree_del_cursor(pcur, XFS_BTREE_ERROR);
			जाओ error0;
		पूर्ण

		अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		level++;

		/*
		 * See अगर the cursor we just used is trash.
		 * Can't trash the caller's cursor, but otherwise we should
		 * अगर ncur is a new cursor or we're about to be करोne.
		 */
		अगर (pcur != cur &&
		    (ncur || xfs_btree_ptr_is_null(cur, &nptr))) अणु
			/* Save the state from the cursor beक्रमe we trash it */
			अगर (cur->bc_ops->update_cursor)
				cur->bc_ops->update_cursor(pcur, cur);
			cur->bc_nlevels = pcur->bc_nlevels;
			xfs_btree_del_cursor(pcur, XFS_BTREE_NOERROR);
		पूर्ण
		/* If we got a new cursor, चयन to it. */
		अगर (ncur) अणु
			pcur = ncur;
			ncur = शून्य;
		पूर्ण
	पूर्ण जबतक (!xfs_btree_ptr_is_null(cur, &nptr));

	*stat = i;
	वापस 0;
error0:
	वापस error;
पूर्ण

/*
 * Try to merge a non-leaf block back पूर्णांकo the inode root.
 *
 * Note: the समाप्तroot names comes from the fact that we're effectively
 * समाप्तing the old root block.  But because we can't just delete the
 * inode we have to copy the single block it was poपूर्णांकing to पूर्णांकo the
 * inode.
 */
STATIC पूर्णांक
xfs_btree_समाप्त_iroot(
	काष्ठा xfs_btree_cur	*cur)
अणु
	पूर्णांक			whichविभाजन = cur->bc_ino.whichविभाजन;
	काष्ठा xfs_inode	*ip = cur->bc_ino.ip;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_btree_block	*cblock;
	जोड़ xfs_btree_key	*kp;
	जोड़ xfs_btree_key	*ckp;
	जोड़ xfs_btree_ptr	*pp;
	जोड़ xfs_btree_ptr	*cpp;
	काष्ठा xfs_buf		*cbp;
	पूर्णांक			level;
	पूर्णांक			index;
	पूर्णांक			numrecs;
	पूर्णांक			error;
#अगर_घोषित DEBUG
	जोड़ xfs_btree_ptr	ptr;
#पूर्ण_अगर
	पूर्णांक			i;

	ASSERT(cur->bc_flags & XFS_BTREE_ROOT_IN_INODE);
	ASSERT(cur->bc_nlevels > 1);

	/*
	 * Don't deal with the root block needs to be a leaf हाल.
	 * We're just going to turn the thing back पूर्णांकo extents anyway.
	 */
	level = cur->bc_nlevels - 1;
	अगर (level == 1)
		जाओ out0;

	/*
	 * Give up अगर the root has multiple children.
	 */
	block = xfs_btree_get_iroot(cur);
	अगर (xfs_btree_get_numrecs(block) != 1)
		जाओ out0;

	cblock = xfs_btree_get_block(cur, level - 1, &cbp);
	numrecs = xfs_btree_get_numrecs(cblock);

	/*
	 * Only करो this अगर the next level will fit.
	 * Then the data must be copied up to the inode,
	 * instead of मुक्तing the root you मुक्त the next level.
	 */
	अगर (numrecs > cur->bc_ops->get_dmaxrecs(cur, level))
		जाओ out0;

	XFS_BTREE_STATS_INC(cur, समाप्तroot);

#अगर_घोषित DEBUG
	xfs_btree_get_sibling(cur, block, &ptr, XFS_BB_LEFTSIB);
	ASSERT(xfs_btree_ptr_is_null(cur, &ptr));
	xfs_btree_get_sibling(cur, block, &ptr, XFS_BB_RIGHTSIB);
	ASSERT(xfs_btree_ptr_is_null(cur, &ptr));
#पूर्ण_अगर

	index = numrecs - cur->bc_ops->get_maxrecs(cur, level);
	अगर (index) अणु
		xfs_iroot_पुनः_स्मृति(cur->bc_ino.ip, index,
				  cur->bc_ino.whichविभाजन);
		block = अगरp->अगर_broot;
	पूर्ण

	be16_add_cpu(&block->bb_numrecs, index);
	ASSERT(block->bb_numrecs == cblock->bb_numrecs);

	kp = xfs_btree_key_addr(cur, 1, block);
	ckp = xfs_btree_key_addr(cur, 1, cblock);
	xfs_btree_copy_keys(cur, kp, ckp, numrecs);

	pp = xfs_btree_ptr_addr(cur, 1, block);
	cpp = xfs_btree_ptr_addr(cur, 1, cblock);

	क्रम (i = 0; i < numrecs; i++) अणु
		error = xfs_btree_debug_check_ptr(cur, cpp, i, level - 1);
		अगर (error)
			वापस error;
	पूर्ण

	xfs_btree_copy_ptrs(cur, pp, cpp, numrecs);

	error = xfs_btree_मुक्त_block(cur, cbp);
	अगर (error)
		वापस error;

	cur->bc_bufs[level - 1] = शून्य;
	be16_add_cpu(&block->bb_level, -1);
	xfs_trans_log_inode(cur->bc_tp, ip,
		XFS_ILOG_CORE | xfs_ilog_fbroot(cur->bc_ino.whichविभाजन));
	cur->bc_nlevels--;
out0:
	वापस 0;
पूर्ण

/*
 * Kill the current root node, and replace it with it's only child node.
 */
STATIC पूर्णांक
xfs_btree_समाप्त_root(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp,
	पूर्णांक			level,
	जोड़ xfs_btree_ptr	*newroot)
अणु
	पूर्णांक			error;

	XFS_BTREE_STATS_INC(cur, समाप्तroot);

	/*
	 * Update the root poपूर्णांकer, decreasing the level by 1 and then
	 * मुक्त the old root.
	 */
	cur->bc_ops->set_root(cur, newroot, -1);

	error = xfs_btree_मुक्त_block(cur, bp);
	अगर (error)
		वापस error;

	cur->bc_bufs[level] = शून्य;
	cur->bc_ra[level] = 0;
	cur->bc_nlevels--;

	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_btree_dec_cursor(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	पूर्णांक			*stat)
अणु
	पूर्णांक			error;
	पूर्णांक			i;

	अगर (level > 0) अणु
		error = xfs_btree_decrement(cur, level, &i);
		अगर (error)
			वापस error;
	पूर्ण

	*stat = 1;
	वापस 0;
पूर्ण

/*
 * Single level of the btree record deletion routine.
 * Delete record poपूर्णांकed to by cur/level.
 * Remove the record from its block then rebalance the tree.
 * Return 0 क्रम error, 1 क्रम करोne, 2 to go on to the next level.
 */
STATIC पूर्णांक					/* error */
xfs_btree_delrec(
	काष्ठा xfs_btree_cur	*cur,		/* btree cursor */
	पूर्णांक			level,		/* level removing record from */
	पूर्णांक			*stat)		/* fail/करोne/go-on */
अणु
	काष्ठा xfs_btree_block	*block;		/* btree block */
	जोड़ xfs_btree_ptr	cptr;		/* current block ptr */
	काष्ठा xfs_buf		*bp;		/* buffer क्रम block */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			i;		/* loop counter */
	जोड़ xfs_btree_ptr	lptr;		/* left sibling block ptr */
	काष्ठा xfs_buf		*lbp;		/* left buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*left;		/* left btree block */
	पूर्णांक			lrecs = 0;	/* left record count */
	पूर्णांक			ptr;		/* key/record index */
	जोड़ xfs_btree_ptr	rptr;		/* right sibling block ptr */
	काष्ठा xfs_buf		*rbp;		/* right buffer poपूर्णांकer */
	काष्ठा xfs_btree_block	*right;		/* right btree block */
	काष्ठा xfs_btree_block	*rrblock;	/* right-right btree block */
	काष्ठा xfs_buf		*rrbp;		/* right-right buffer poपूर्णांकer */
	पूर्णांक			rrecs = 0;	/* right record count */
	काष्ठा xfs_btree_cur	*tcur;		/* temporary btree cursor */
	पूर्णांक			numrecs;	/* temporary numrec count */

	tcur = शून्य;

	/* Get the index of the entry being deleted, check क्रम nothing there. */
	ptr = cur->bc_ptrs[level];
	अगर (ptr == 0) अणु
		*stat = 0;
		वापस 0;
	पूर्ण

	/* Get the buffer & block containing the record or key/ptr. */
	block = xfs_btree_get_block(cur, level, &bp);
	numrecs = xfs_btree_get_numrecs(block);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, block, level, bp);
	अगर (error)
		जाओ error0;
#पूर्ण_अगर

	/* Fail अगर we're off the end of the block. */
	अगर (ptr > numrecs) अणु
		*stat = 0;
		वापस 0;
	पूर्ण

	XFS_BTREE_STATS_INC(cur, delrec);
	XFS_BTREE_STATS_ADD(cur, moves, numrecs - ptr);

	/* Excise the entries being deleted. */
	अगर (level > 0) अणु
		/* It's a nonleaf. operate on keys and ptrs */
		जोड़ xfs_btree_key	*lkp;
		जोड़ xfs_btree_ptr	*lpp;

		lkp = xfs_btree_key_addr(cur, ptr + 1, block);
		lpp = xfs_btree_ptr_addr(cur, ptr + 1, block);

		क्रम (i = 0; i < numrecs - ptr; i++) अणु
			error = xfs_btree_debug_check_ptr(cur, lpp, i, level);
			अगर (error)
				जाओ error0;
		पूर्ण

		अगर (ptr < numrecs) अणु
			xfs_btree_shअगरt_keys(cur, lkp, -1, numrecs - ptr);
			xfs_btree_shअगरt_ptrs(cur, lpp, -1, numrecs - ptr);
			xfs_btree_log_keys(cur, bp, ptr, numrecs - 1);
			xfs_btree_log_ptrs(cur, bp, ptr, numrecs - 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* It's a leaf. operate on records */
		अगर (ptr < numrecs) अणु
			xfs_btree_shअगरt_recs(cur,
				xfs_btree_rec_addr(cur, ptr + 1, block),
				-1, numrecs - ptr);
			xfs_btree_log_recs(cur, bp, ptr, numrecs - 1);
		पूर्ण
	पूर्ण

	/*
	 * Decrement and log the number of entries in the block.
	 */
	xfs_btree_set_numrecs(block, --numrecs);
	xfs_btree_log_block(cur, bp, XFS_BB_NUMRECS);

	/*
	 * If we are tracking the last record in the tree and
	 * we are at the far right edge of the tree, update it.
	 */
	अगर (xfs_btree_is_lastrec(cur, block, level)) अणु
		cur->bc_ops->update_lastrec(cur, block, शून्य,
					    ptr, LASTREC_DELREC);
	पूर्ण

	/*
	 * We're at the root level.  First, shrink the root block in-memory.
	 * Try to get rid of the next level करोwn.  If we can't then there's
	 * nothing left to करो.
	 */
	अगर (level == cur->bc_nlevels - 1) अणु
		अगर (cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) अणु
			xfs_iroot_पुनः_स्मृति(cur->bc_ino.ip, -1,
					  cur->bc_ino.whichविभाजन);

			error = xfs_btree_समाप्त_iroot(cur);
			अगर (error)
				जाओ error0;

			error = xfs_btree_dec_cursor(cur, level, stat);
			अगर (error)
				जाओ error0;
			*stat = 1;
			वापस 0;
		पूर्ण

		/*
		 * If this is the root level, and there's only one entry left,
		 * and it's NOT the leaf level, then we can get rid of this
		 * level.
		 */
		अगर (numrecs == 1 && level > 0) अणु
			जोड़ xfs_btree_ptr	*pp;
			/*
			 * pp is still set to the first poपूर्णांकer in the block.
			 * Make it the new root of the btree.
			 */
			pp = xfs_btree_ptr_addr(cur, 1, block);
			error = xfs_btree_समाप्त_root(cur, bp, level, pp);
			अगर (error)
				जाओ error0;
		पूर्ण अन्यथा अगर (level > 0) अणु
			error = xfs_btree_dec_cursor(cur, level, stat);
			अगर (error)
				जाओ error0;
		पूर्ण
		*stat = 1;
		वापस 0;
	पूर्ण

	/*
	 * If we deleted the lefपंचांगost entry in the block, update the
	 * key values above us in the tree.
	 */
	अगर (xfs_btree_needs_key_update(cur, ptr)) अणु
		error = xfs_btree_update_keys(cur, level);
		अगर (error)
			जाओ error0;
	पूर्ण

	/*
	 * If the number of records reमुख्यing in the block is at least
	 * the minimum, we're करोne.
	 */
	अगर (numrecs >= cur->bc_ops->get_minrecs(cur, level)) अणु
		error = xfs_btree_dec_cursor(cur, level, stat);
		अगर (error)
			जाओ error0;
		वापस 0;
	पूर्ण

	/*
	 * Otherwise, we have to move some records around to keep the
	 * tree balanced.  Look at the left and right sibling blocks to
	 * see अगर we can re-balance by moving only one record.
	 */
	xfs_btree_get_sibling(cur, block, &rptr, XFS_BB_RIGHTSIB);
	xfs_btree_get_sibling(cur, block, &lptr, XFS_BB_LEFTSIB);

	अगर (cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) अणु
		/*
		 * One child of root, need to get a chance to copy its contents
		 * पूर्णांकo the root and delete it. Can't go up to next level,
		 * there's nothing to delete there.
		 */
		अगर (xfs_btree_ptr_is_null(cur, &rptr) &&
		    xfs_btree_ptr_is_null(cur, &lptr) &&
		    level == cur->bc_nlevels - 2) अणु
			error = xfs_btree_समाप्त_iroot(cur);
			अगर (!error)
				error = xfs_btree_dec_cursor(cur, level, stat);
			अगर (error)
				जाओ error0;
			वापस 0;
		पूर्ण
	पूर्ण

	ASSERT(!xfs_btree_ptr_is_null(cur, &rptr) ||
	       !xfs_btree_ptr_is_null(cur, &lptr));

	/*
	 * Duplicate the cursor so our btree manipulations here won't
	 * disrupt the next level up.
	 */
	error = xfs_btree_dup_cursor(cur, &tcur);
	अगर (error)
		जाओ error0;

	/*
	 * If there's a right sibling, see if it's ok to shअगरt an entry
	 * out of it.
	 */
	अगर (!xfs_btree_ptr_is_null(cur, &rptr)) अणु
		/*
		 * Move the temp cursor to the last entry in the next block.
		 * Actually any entry but the first would suffice.
		 */
		i = xfs_btree_lastrec(tcur, level);
		अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण

		error = xfs_btree_increment(tcur, level, &i);
		अगर (error)
			जाओ error0;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण

		i = xfs_btree_lastrec(tcur, level);
		अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण

		/* Grab a poपूर्णांकer to the block. */
		right = xfs_btree_get_block(tcur, level, &rbp);
#अगर_घोषित DEBUG
		error = xfs_btree_check_block(tcur, right, level, rbp);
		अगर (error)
			जाओ error0;
#पूर्ण_अगर
		/* Grab the current block number, क्रम future use. */
		xfs_btree_get_sibling(tcur, right, &cptr, XFS_BB_LEFTSIB);

		/*
		 * If right block is full enough so that removing one entry
		 * won't make it too empty, and left-shअगरting an entry out
		 * of right to us works, we're करोne.
		 */
		अगर (xfs_btree_get_numrecs(right) - 1 >=
		    cur->bc_ops->get_minrecs(tcur, level)) अणु
			error = xfs_btree_lshअगरt(tcur, level, &i);
			अगर (error)
				जाओ error0;
			अगर (i) अणु
				ASSERT(xfs_btree_get_numrecs(block) >=
				       cur->bc_ops->get_minrecs(tcur, level));

				xfs_btree_del_cursor(tcur, XFS_BTREE_NOERROR);
				tcur = शून्य;

				error = xfs_btree_dec_cursor(cur, level, stat);
				अगर (error)
					जाओ error0;
				वापस 0;
			पूर्ण
		पूर्ण

		/*
		 * Otherwise, grab the number of records in right क्रम
		 * future reference, and fix up the temp cursor to poपूर्णांक
		 * to our block again (last record).
		 */
		rrecs = xfs_btree_get_numrecs(right);
		अगर (!xfs_btree_ptr_is_null(cur, &lptr)) अणु
			i = xfs_btree_firstrec(tcur, level);
			अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ error0;
			पूर्ण

			error = xfs_btree_decrement(tcur, level, &i);
			अगर (error)
				जाओ error0;
			अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ error0;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If there's a left sibling, see if it's ok to shअगरt an entry
	 * out of it.
	 */
	अगर (!xfs_btree_ptr_is_null(cur, &lptr)) अणु
		/*
		 * Move the temp cursor to the first entry in the
		 * previous block.
		 */
		i = xfs_btree_firstrec(tcur, level);
		अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण

		error = xfs_btree_decrement(tcur, level, &i);
		अगर (error)
			जाओ error0;
		i = xfs_btree_firstrec(tcur, level);
		अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण

		/* Grab a poपूर्णांकer to the block. */
		left = xfs_btree_get_block(tcur, level, &lbp);
#अगर_घोषित DEBUG
		error = xfs_btree_check_block(cur, left, level, lbp);
		अगर (error)
			जाओ error0;
#पूर्ण_अगर
		/* Grab the current block number, क्रम future use. */
		xfs_btree_get_sibling(tcur, left, &cptr, XFS_BB_RIGHTSIB);

		/*
		 * If left block is full enough so that removing one entry
		 * won't make it too empty, and right-shअगरting an entry out
		 * of left to us works, we're करोne.
		 */
		अगर (xfs_btree_get_numrecs(left) - 1 >=
		    cur->bc_ops->get_minrecs(tcur, level)) अणु
			error = xfs_btree_rshअगरt(tcur, level, &i);
			अगर (error)
				जाओ error0;
			अगर (i) अणु
				ASSERT(xfs_btree_get_numrecs(block) >=
				       cur->bc_ops->get_minrecs(tcur, level));
				xfs_btree_del_cursor(tcur, XFS_BTREE_NOERROR);
				tcur = शून्य;
				अगर (level == 0)
					cur->bc_ptrs[0]++;

				*stat = 1;
				वापस 0;
			पूर्ण
		पूर्ण

		/*
		 * Otherwise, grab the number of records in right क्रम
		 * future reference.
		 */
		lrecs = xfs_btree_get_numrecs(left);
	पूर्ण

	/* Delete the temp cursor, we're करोne with it. */
	xfs_btree_del_cursor(tcur, XFS_BTREE_NOERROR);
	tcur = शून्य;

	/* If here, we need to करो a join to keep the tree balanced. */
	ASSERT(!xfs_btree_ptr_is_null(cur, &cptr));

	अगर (!xfs_btree_ptr_is_null(cur, &lptr) &&
	    lrecs + xfs_btree_get_numrecs(block) <=
			cur->bc_ops->get_maxrecs(cur, level)) अणु
		/*
		 * Set "right" to be the starting block,
		 * "left" to be the left neighbor.
		 */
		rptr = cptr;
		right = block;
		rbp = bp;
		error = xfs_btree_पढ़ो_buf_block(cur, &lptr, 0, &left, &lbp);
		अगर (error)
			जाओ error0;

	/*
	 * If that won't work, see अगर we can join with the right neighbor block.
	 */
	पूर्ण अन्यथा अगर (!xfs_btree_ptr_is_null(cur, &rptr) &&
		   rrecs + xfs_btree_get_numrecs(block) <=
			cur->bc_ops->get_maxrecs(cur, level)) अणु
		/*
		 * Set "left" to be the starting block,
		 * "right" to be the right neighbor.
		 */
		lptr = cptr;
		left = block;
		lbp = bp;
		error = xfs_btree_पढ़ो_buf_block(cur, &rptr, 0, &right, &rbp);
		अगर (error)
			जाओ error0;

	/*
	 * Otherwise, we can't fix the imbalance.
	 * Just वापस.  This is probably a logic error, but it's not fatal.
	 */
	पूर्ण अन्यथा अणु
		error = xfs_btree_dec_cursor(cur, level, stat);
		अगर (error)
			जाओ error0;
		वापस 0;
	पूर्ण

	rrecs = xfs_btree_get_numrecs(right);
	lrecs = xfs_btree_get_numrecs(left);

	/*
	 * We're now going to join "left" and "right" by moving all the stuff
	 * in "right" to "left" and deleting "right".
	 */
	XFS_BTREE_STATS_ADD(cur, moves, rrecs);
	अगर (level > 0) अणु
		/* It's a non-leaf.  Move keys and poपूर्णांकers. */
		जोड़ xfs_btree_key	*lkp;	/* left btree key */
		जोड़ xfs_btree_ptr	*lpp;	/* left address poपूर्णांकer */
		जोड़ xfs_btree_key	*rkp;	/* right btree key */
		जोड़ xfs_btree_ptr	*rpp;	/* right address poपूर्णांकer */

		lkp = xfs_btree_key_addr(cur, lrecs + 1, left);
		lpp = xfs_btree_ptr_addr(cur, lrecs + 1, left);
		rkp = xfs_btree_key_addr(cur, 1, right);
		rpp = xfs_btree_ptr_addr(cur, 1, right);

		क्रम (i = 1; i < rrecs; i++) अणु
			error = xfs_btree_debug_check_ptr(cur, rpp, i, level);
			अगर (error)
				जाओ error0;
		पूर्ण

		xfs_btree_copy_keys(cur, lkp, rkp, rrecs);
		xfs_btree_copy_ptrs(cur, lpp, rpp, rrecs);

		xfs_btree_log_keys(cur, lbp, lrecs + 1, lrecs + rrecs);
		xfs_btree_log_ptrs(cur, lbp, lrecs + 1, lrecs + rrecs);
	पूर्ण अन्यथा अणु
		/* It's a leaf.  Move records.  */
		जोड़ xfs_btree_rec	*lrp;	/* left record poपूर्णांकer */
		जोड़ xfs_btree_rec	*rrp;	/* right record poपूर्णांकer */

		lrp = xfs_btree_rec_addr(cur, lrecs + 1, left);
		rrp = xfs_btree_rec_addr(cur, 1, right);

		xfs_btree_copy_recs(cur, lrp, rrp, rrecs);
		xfs_btree_log_recs(cur, lbp, lrecs + 1, lrecs + rrecs);
	पूर्ण

	XFS_BTREE_STATS_INC(cur, join);

	/*
	 * Fix up the number of records and right block poपूर्णांकer in the
	 * surviving block, and log it.
	 */
	xfs_btree_set_numrecs(left, lrecs + rrecs);
	xfs_btree_get_sibling(cur, right, &cptr, XFS_BB_RIGHTSIB);
	xfs_btree_set_sibling(cur, left, &cptr, XFS_BB_RIGHTSIB);
	xfs_btree_log_block(cur, lbp, XFS_BB_NUMRECS | XFS_BB_RIGHTSIB);

	/* If there is a right sibling, poपूर्णांक it to the reमुख्यing block. */
	xfs_btree_get_sibling(cur, left, &cptr, XFS_BB_RIGHTSIB);
	अगर (!xfs_btree_ptr_is_null(cur, &cptr)) अणु
		error = xfs_btree_पढ़ो_buf_block(cur, &cptr, 0, &rrblock, &rrbp);
		अगर (error)
			जाओ error0;
		xfs_btree_set_sibling(cur, rrblock, &lptr, XFS_BB_LEFTSIB);
		xfs_btree_log_block(cur, rrbp, XFS_BB_LEFTSIB);
	पूर्ण

	/* Free the deleted block. */
	error = xfs_btree_मुक्त_block(cur, rbp);
	अगर (error)
		जाओ error0;

	/*
	 * If we joined with the left neighbor, set the buffer in the
	 * cursor to the left block, and fix up the index.
	 */
	अगर (bp != lbp) अणु
		cur->bc_bufs[level] = lbp;
		cur->bc_ptrs[level] += lrecs;
		cur->bc_ra[level] = 0;
	पूर्ण
	/*
	 * If we joined with the right neighbor and there's a level above
	 * us, increment the cursor at that level.
	 */
	अन्यथा अगर ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) ||
		   (level + 1 < cur->bc_nlevels)) अणु
		error = xfs_btree_increment(cur, level + 1, &i);
		अगर (error)
			जाओ error0;
	पूर्ण

	/*
	 * Readjust the ptr at this level अगर it's not a leaf, since it's
	 * still poपूर्णांकing at the deletion poपूर्णांक, which makes the cursor
	 * inconsistent.  If this makes the ptr 0, the caller fixes it up.
	 * We can't use decrement because it would change the next level up.
	 */
	अगर (level > 0)
		cur->bc_ptrs[level]--;

	/*
	 * We combined blocks, so we have to update the parent keys अगर the
	 * btree supports overlapped पूर्णांकervals.  However, bc_ptrs[level + 1]
	 * poपूर्णांकs to the old block so that the caller knows which record to
	 * delete.  Thereक्रमe, the caller must be savvy enough to call updkeys
	 * क्रम us अगर we वापस stat == 2.  The other निकास poपूर्णांकs from this
	 * function करोn't require deletions further up the tree, so they can
	 * call updkeys directly.
	 */

	/* Return value means the next level up has something to करो. */
	*stat = 2;
	वापस 0;

error0:
	अगर (tcur)
		xfs_btree_del_cursor(tcur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/*
 * Delete the record poपूर्णांकed to by cur.
 * The cursor refers to the place where the record was (could be inserted)
 * when the operation वापसs.
 */
पूर्णांक					/* error */
xfs_btree_delete(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			*stat)	/* success/failure */
अणु
	पूर्णांक			error;	/* error वापस value */
	पूर्णांक			level;
	पूर्णांक			i;
	bool			joined = false;

	/*
	 * Go up the tree, starting at leaf level.
	 *
	 * If 2 is वापसed then a join was करोne; go to the next level.
	 * Otherwise we are करोne.
	 */
	क्रम (level = 0, i = 2; i == 2; level++) अणु
		error = xfs_btree_delrec(cur, level, &i);
		अगर (error)
			जाओ error0;
		अगर (i == 2)
			joined = true;
	पूर्ण

	/*
	 * If we combined blocks as part of deleting the record, delrec won't
	 * have updated the parent high keys so we have to करो that here.
	 */
	अगर (joined && (cur->bc_flags & XFS_BTREE_OVERLAPPING)) अणु
		error = xfs_btree_updkeys_क्रमce(cur, 0);
		अगर (error)
			जाओ error0;
	पूर्ण

	अगर (i == 0) अणु
		क्रम (level = 1; level < cur->bc_nlevels; level++) अणु
			अगर (cur->bc_ptrs[level] == 0) अणु
				error = xfs_btree_decrement(cur, level, &i);
				अगर (error)
					जाओ error0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	*stat = i;
	वापस 0;
error0:
	वापस error;
पूर्ण

/*
 * Get the data from the poपूर्णांकed-to record.
 */
पूर्णांक					/* error */
xfs_btree_get_rec(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	जोड़ xfs_btree_rec	**recp,	/* output: btree record */
	पूर्णांक			*stat)	/* output: success/failure */
अणु
	काष्ठा xfs_btree_block	*block;	/* btree block */
	काष्ठा xfs_buf		*bp;	/* buffer poपूर्णांकer */
	पूर्णांक			ptr;	/* record number */
#अगर_घोषित DEBUG
	पूर्णांक			error;	/* error वापस value */
#पूर्ण_अगर

	ptr = cur->bc_ptrs[0];
	block = xfs_btree_get_block(cur, 0, &bp);

#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, block, 0, bp);
	अगर (error)
		वापस error;
#पूर्ण_अगर

	/*
	 * Off the right end or left end, वापस failure.
	 */
	अगर (ptr > xfs_btree_get_numrecs(block) || ptr <= 0) अणु
		*stat = 0;
		वापस 0;
	पूर्ण

	/*
	 * Poपूर्णांक to the record and extract its data.
	 */
	*recp = xfs_btree_rec_addr(cur, ptr, block);
	*stat = 1;
	वापस 0;
पूर्ण

/* Visit a block in a btree. */
STATIC पूर्णांक
xfs_btree_visit_block(
	काष्ठा xfs_btree_cur		*cur,
	पूर्णांक				level,
	xfs_btree_visit_blocks_fn	fn,
	व्योम				*data)
अणु
	काष्ठा xfs_btree_block		*block;
	काष्ठा xfs_buf			*bp;
	जोड़ xfs_btree_ptr		rptr;
	पूर्णांक				error;

	/* करो right sibling पढ़ोahead */
	xfs_btree_पढ़ोahead(cur, level, XFS_BTCUR_RIGHTRA);
	block = xfs_btree_get_block(cur, level, &bp);

	/* process the block */
	error = fn(cur, level, data);
	अगर (error)
		वापस error;

	/* now पढ़ो rh sibling block क्रम next iteration */
	xfs_btree_get_sibling(cur, block, &rptr, XFS_BB_RIGHTSIB);
	अगर (xfs_btree_ptr_is_null(cur, &rptr))
		वापस -ENOENT;

	वापस xfs_btree_lookup_get_block(cur, level, &rptr, &block);
पूर्ण


/* Visit every block in a btree. */
पूर्णांक
xfs_btree_visit_blocks(
	काष्ठा xfs_btree_cur		*cur,
	xfs_btree_visit_blocks_fn	fn,
	अचिन्हित पूर्णांक			flags,
	व्योम				*data)
अणु
	जोड़ xfs_btree_ptr		lptr;
	पूर्णांक				level;
	काष्ठा xfs_btree_block		*block = शून्य;
	पूर्णांक				error = 0;

	cur->bc_ops->init_ptr_from_cur(cur, &lptr);

	/* क्रम each level */
	क्रम (level = cur->bc_nlevels - 1; level >= 0; level--) अणु
		/* grab the left hand block */
		error = xfs_btree_lookup_get_block(cur, level, &lptr, &block);
		अगर (error)
			वापस error;

		/* पढ़ोahead the left most block क्रम the next level करोwn */
		अगर (level > 0) अणु
			जोड़ xfs_btree_ptr     *ptr;

			ptr = xfs_btree_ptr_addr(cur, 1, block);
			xfs_btree_पढ़ोahead_ptr(cur, ptr, 1);

			/* save क्रम the next iteration of the loop */
			xfs_btree_copy_ptrs(cur, &lptr, ptr, 1);

			अगर (!(flags & XFS_BTREE_VISIT_LEAVES))
				जारी;
		पूर्ण अन्यथा अगर (!(flags & XFS_BTREE_VISIT_RECORDS)) अणु
			जारी;
		पूर्ण

		/* क्रम each buffer in the level */
		करो अणु
			error = xfs_btree_visit_block(cur, level, fn, data);
		पूर्ण जबतक (!error);

		अगर (error != -ENOENT)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Change the owner of a btree.
 *
 * The mechanism we use here is ordered buffer logging. Because we करोn't know
 * how many buffers were are going to need to modअगरy, we करोn't really want to
 * have to make transaction reservations क्रम the worst हाल of every buffer in a
 * full size btree as that may be more space that we can fit in the log....
 *
 * We करो the btree walk in the most optimal manner possible - we have sibling
 * poपूर्णांकers so we can just walk all the blocks on each level from left to right
 * in a single pass, and then move to the next level and करो the same. We can
 * also करो पढ़ोahead on the sibling poपूर्णांकers to get IO moving more quickly,
 * though क्रम slow disks this is unlikely to make much dअगरference to perक्रमmance
 * as the amount of CPU work we have to करो beक्रमe moving to the next block is
 * relatively small.
 *
 * For each btree block that we load, modअगरy the owner appropriately, set the
 * buffer as an ordered buffer and log it appropriately. We need to ensure that
 * we mark the region we change dirty so that अगर the buffer is relogged in
 * a subsequent transaction the changes we make here as an ordered buffer are
 * correctly relogged in that transaction.  If we are in recovery context, then
 * just queue the modअगरied buffer as delayed ग_लिखो buffer so the transaction
 * recovery completion ग_लिखोs the changes to disk.
 */
काष्ठा xfs_btree_block_change_owner_info अणु
	uपूर्णांक64_t		new_owner;
	काष्ठा list_head	*buffer_list;
पूर्ण;

अटल पूर्णांक
xfs_btree_block_change_owner(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	व्योम			*data)
अणु
	काष्ठा xfs_btree_block_change_owner_info	*bbcoi = data;
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_buf		*bp;

	/* modअगरy the owner */
	block = xfs_btree_get_block(cur, level, &bp);
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS) अणु
		अगर (block->bb_u.l.bb_owner == cpu_to_be64(bbcoi->new_owner))
			वापस 0;
		block->bb_u.l.bb_owner = cpu_to_be64(bbcoi->new_owner);
	पूर्ण अन्यथा अणु
		अगर (block->bb_u.s.bb_owner == cpu_to_be32(bbcoi->new_owner))
			वापस 0;
		block->bb_u.s.bb_owner = cpu_to_be32(bbcoi->new_owner);
	पूर्ण

	/*
	 * If the block is a root block hosted in an inode, we might not have a
	 * buffer poपूर्णांकer here and we shouldn't attempt to log the change as the
	 * inक्रमmation is alपढ़ोy held in the inode and discarded when the root
	 * block is क्रमmatted पूर्णांकo the on-disk inode विभाजन. We still change it,
	 * though, so everything is consistent in memory.
	 */
	अगर (!bp) अणु
		ASSERT(cur->bc_flags & XFS_BTREE_ROOT_IN_INODE);
		ASSERT(level == cur->bc_nlevels - 1);
		वापस 0;
	पूर्ण

	अगर (cur->bc_tp) अणु
		अगर (!xfs_trans_ordered_buf(cur->bc_tp, bp)) अणु
			xfs_btree_log_block(cur, bp, XFS_BB_OWNER);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण अन्यथा अणु
		xfs_buf_delwri_queue(bp, bbcoi->buffer_list);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
xfs_btree_change_owner(
	काष्ठा xfs_btree_cur	*cur,
	uपूर्णांक64_t		new_owner,
	काष्ठा list_head	*buffer_list)
अणु
	काष्ठा xfs_btree_block_change_owner_info	bbcoi;

	bbcoi.new_owner = new_owner;
	bbcoi.buffer_list = buffer_list;

	वापस xfs_btree_visit_blocks(cur, xfs_btree_block_change_owner,
			XFS_BTREE_VISIT_ALL, &bbcoi);
पूर्ण

/* Verअगरy the v5 fields of a दीर्घ-क्रमmat btree block. */
xfs_failaddr_t
xfs_btree_lblock_v5hdr_verअगरy(
	काष्ठा xfs_buf		*bp,
	uपूर्णांक64_t		owner)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस __this_address;
	अगर (!uuid_equal(&block->bb_u.l.bb_uuid, &mp->m_sb.sb_meta_uuid))
		वापस __this_address;
	अगर (block->bb_u.l.bb_blkno != cpu_to_be64(bp->b_bn))
		वापस __this_address;
	अगर (owner != XFS_RMAP_OWN_UNKNOWN &&
	    be64_to_cpu(block->bb_u.l.bb_owner) != owner)
		वापस __this_address;
	वापस शून्य;
पूर्ण

/* Verअगरy a दीर्घ-क्रमmat btree block. */
xfs_failaddr_t
xfs_btree_lblock_verअगरy(
	काष्ठा xfs_buf		*bp,
	अचिन्हित पूर्णांक		max_recs)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);

	/* numrecs verअगरication */
	अगर (be16_to_cpu(block->bb_numrecs) > max_recs)
		वापस __this_address;

	/* sibling poपूर्णांकer verअगरication */
	अगर (block->bb_u.l.bb_leftsib != cpu_to_be64(शून्यFSBLOCK) &&
	    !xfs_verअगरy_fsbno(mp, be64_to_cpu(block->bb_u.l.bb_leftsib)))
		वापस __this_address;
	अगर (block->bb_u.l.bb_rightsib != cpu_to_be64(शून्यFSBLOCK) &&
	    !xfs_verअगरy_fsbno(mp, be64_to_cpu(block->bb_u.l.bb_rightsib)))
		वापस __this_address;

	वापस शून्य;
पूर्ण

/**
 * xfs_btree_sblock_v5hdr_verअगरy() -- verअगरy the v5 fields of a लघु-क्रमmat
 *				      btree block
 *
 * @bp: buffer containing the btree block
 */
xfs_failaddr_t
xfs_btree_sblock_v5hdr_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	काष्ठा xfs_perag	*pag = bp->b_pag;

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस __this_address;
	अगर (!uuid_equal(&block->bb_u.s.bb_uuid, &mp->m_sb.sb_meta_uuid))
		वापस __this_address;
	अगर (block->bb_u.s.bb_blkno != cpu_to_be64(bp->b_bn))
		वापस __this_address;
	अगर (pag && be32_to_cpu(block->bb_u.s.bb_owner) != pag->pag_agno)
		वापस __this_address;
	वापस शून्य;
पूर्ण

/**
 * xfs_btree_sblock_verअगरy() -- verअगरy a लघु-क्रमmat btree block
 *
 * @bp: buffer containing the btree block
 * @max_recs: maximum records allowed in this btree node
 */
xfs_failaddr_t
xfs_btree_sblock_verअगरy(
	काष्ठा xfs_buf		*bp,
	अचिन्हित पूर्णांक		max_recs)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	xfs_agblock_t		agno;

	/* numrecs verअगरication */
	अगर (be16_to_cpu(block->bb_numrecs) > max_recs)
		वापस __this_address;

	/* sibling poपूर्णांकer verअगरication */
	agno = xfs_daddr_to_agno(mp, XFS_BUF_ADDR(bp));
	अगर (block->bb_u.s.bb_leftsib != cpu_to_be32(शून्यAGBLOCK) &&
	    !xfs_verअगरy_agbno(mp, agno, be32_to_cpu(block->bb_u.s.bb_leftsib)))
		वापस __this_address;
	अगर (block->bb_u.s.bb_rightsib != cpu_to_be32(शून्यAGBLOCK) &&
	    !xfs_verअगरy_agbno(mp, agno, be32_to_cpu(block->bb_u.s.bb_rightsib)))
		वापस __this_address;

	वापस शून्य;
पूर्ण

/*
 * Calculate the number of btree levels needed to store a given number of
 * records in a लघु-क्रमmat btree.
 */
uपूर्णांक
xfs_btree_compute_maxlevels(
	uपूर्णांक			*limits,
	अचिन्हित दीर्घ		len)
अणु
	uपूर्णांक			level;
	अचिन्हित दीर्घ		maxblocks;

	maxblocks = (len + limits[0] - 1) / limits[0];
	क्रम (level = 1; maxblocks > 1; level++)
		maxblocks = (maxblocks + limits[1] - 1) / limits[1];
	वापस level;
पूर्ण

/*
 * Query a regular btree क्रम all records overlapping a given पूर्णांकerval.
 * Start with a LE lookup of the key of low_rec and वापस all records
 * until we find a record with a key greater than the key of high_rec.
 */
STATIC पूर्णांक
xfs_btree_simple_query_range(
	काष्ठा xfs_btree_cur		*cur,
	जोड़ xfs_btree_key		*low_key,
	जोड़ xfs_btree_key		*high_key,
	xfs_btree_query_range_fn	fn,
	व्योम				*priv)
अणु
	जोड़ xfs_btree_rec		*recp;
	जोड़ xfs_btree_key		rec_key;
	पूर्णांक64_t				dअगरf;
	पूर्णांक				stat;
	bool				firstrec = true;
	पूर्णांक				error;

	ASSERT(cur->bc_ops->init_high_key_from_rec);
	ASSERT(cur->bc_ops->dअगरf_two_keys);

	/*
	 * Find the lefपंचांगost record.  The btree cursor must be set
	 * to the low record used to generate low_key.
	 */
	stat = 0;
	error = xfs_btree_lookup(cur, XFS_LOOKUP_LE, &stat);
	अगर (error)
		जाओ out;

	/* Nothing?  See अगर there's anything to the right. */
	अगर (!stat) अणु
		error = xfs_btree_increment(cur, 0, &stat);
		अगर (error)
			जाओ out;
	पूर्ण

	जबतक (stat) अणु
		/* Find the record. */
		error = xfs_btree_get_rec(cur, &recp, &stat);
		अगर (error || !stat)
			अवरोध;

		/* Skip अगर high_key(rec) < low_key. */
		अगर (firstrec) अणु
			cur->bc_ops->init_high_key_from_rec(&rec_key, recp);
			firstrec = false;
			dअगरf = cur->bc_ops->dअगरf_two_keys(cur, low_key,
					&rec_key);
			अगर (dअगरf > 0)
				जाओ advloop;
		पूर्ण

		/* Stop अगर high_key < low_key(rec). */
		cur->bc_ops->init_key_from_rec(&rec_key, recp);
		dअगरf = cur->bc_ops->dअगरf_two_keys(cur, &rec_key, high_key);
		अगर (dअगरf > 0)
			अवरोध;

		/* Callback */
		error = fn(cur, recp, priv);
		अगर (error)
			अवरोध;

advloop:
		/* Move on to the next record. */
		error = xfs_btree_increment(cur, 0, &stat);
		अगर (error)
			अवरोध;
	पूर्ण

out:
	वापस error;
पूर्ण

/*
 * Query an overlapped पूर्णांकerval btree क्रम all records overlapping a given
 * पूर्णांकerval.  This function roughly follows the algorithm given in
 * "Interval Trees" of _Introduction to Algorithms_, which is section
 * 14.3 in the 2nd and 3rd editions.
 *
 * First, generate keys क्रम the low and high records passed in.
 *
 * For any leaf node, generate the high and low keys क्रम the record.
 * If the record keys overlap with the query low/high keys, pass the
 * record to the function iterator.
 *
 * For any पूर्णांकernal node, compare the low and high keys of each
 * poपूर्णांकer against the query low/high keys.  If there's an overlap,
 * follow the poपूर्णांकer.
 *
 * As an optimization, we stop scanning a block when we find a low key
 * that is greater than the query's high key.
 */
STATIC पूर्णांक
xfs_btree_overlapped_query_range(
	काष्ठा xfs_btree_cur		*cur,
	जोड़ xfs_btree_key		*low_key,
	जोड़ xfs_btree_key		*high_key,
	xfs_btree_query_range_fn	fn,
	व्योम				*priv)
अणु
	जोड़ xfs_btree_ptr		ptr;
	जोड़ xfs_btree_ptr		*pp;
	जोड़ xfs_btree_key		rec_key;
	जोड़ xfs_btree_key		rec_hkey;
	जोड़ xfs_btree_key		*lkp;
	जोड़ xfs_btree_key		*hkp;
	जोड़ xfs_btree_rec		*recp;
	काष्ठा xfs_btree_block		*block;
	पूर्णांक64_t				ldअगरf;
	पूर्णांक64_t				hdअगरf;
	पूर्णांक				level;
	काष्ठा xfs_buf			*bp;
	पूर्णांक				i;
	पूर्णांक				error;

	/* Load the root of the btree. */
	level = cur->bc_nlevels - 1;
	cur->bc_ops->init_ptr_from_cur(cur, &ptr);
	error = xfs_btree_lookup_get_block(cur, level, &ptr, &block);
	अगर (error)
		वापस error;
	xfs_btree_get_block(cur, level, &bp);
	trace_xfs_btree_overlapped_query_range(cur, level, bp);
#अगर_घोषित DEBUG
	error = xfs_btree_check_block(cur, block, level, bp);
	अगर (error)
		जाओ out;
#पूर्ण_अगर
	cur->bc_ptrs[level] = 1;

	जबतक (level < cur->bc_nlevels) अणु
		block = xfs_btree_get_block(cur, level, &bp);

		/* End of node, pop back towards the root. */
		अगर (cur->bc_ptrs[level] > be16_to_cpu(block->bb_numrecs)) अणु
pop_up:
			अगर (level < cur->bc_nlevels - 1)
				cur->bc_ptrs[level + 1]++;
			level++;
			जारी;
		पूर्ण

		अगर (level == 0) अणु
			/* Handle a leaf node. */
			recp = xfs_btree_rec_addr(cur, cur->bc_ptrs[0], block);

			cur->bc_ops->init_high_key_from_rec(&rec_hkey, recp);
			ldअगरf = cur->bc_ops->dअगरf_two_keys(cur, &rec_hkey,
					low_key);

			cur->bc_ops->init_key_from_rec(&rec_key, recp);
			hdअगरf = cur->bc_ops->dअगरf_two_keys(cur, high_key,
					&rec_key);

			/*
			 * If (record's high key >= query's low key) and
			 *    (query's high key >= record's low key), then
			 * this record overlaps the query range; callback.
			 */
			अगर (ldअगरf >= 0 && hdअगरf >= 0) अणु
				error = fn(cur, recp, priv);
				अगर (error)
					अवरोध;
			पूर्ण अन्यथा अगर (hdअगरf < 0) अणु
				/* Record is larger than high key; pop. */
				जाओ pop_up;
			पूर्ण
			cur->bc_ptrs[level]++;
			जारी;
		पूर्ण

		/* Handle an पूर्णांकernal node. */
		lkp = xfs_btree_key_addr(cur, cur->bc_ptrs[level], block);
		hkp = xfs_btree_high_key_addr(cur, cur->bc_ptrs[level], block);
		pp = xfs_btree_ptr_addr(cur, cur->bc_ptrs[level], block);

		ldअगरf = cur->bc_ops->dअगरf_two_keys(cur, hkp, low_key);
		hdअगरf = cur->bc_ops->dअगरf_two_keys(cur, high_key, lkp);

		/*
		 * If (poपूर्णांकer's high key >= query's low key) and
		 *    (query's high key >= pointer's low key), then
		 * this record overlaps the query range; follow poपूर्णांकer.
		 */
		अगर (ldअगरf >= 0 && hdअगरf >= 0) अणु
			level--;
			error = xfs_btree_lookup_get_block(cur, level, pp,
					&block);
			अगर (error)
				जाओ out;
			xfs_btree_get_block(cur, level, &bp);
			trace_xfs_btree_overlapped_query_range(cur, level, bp);
#अगर_घोषित DEBUG
			error = xfs_btree_check_block(cur, block, level, bp);
			अगर (error)
				जाओ out;
#पूर्ण_अगर
			cur->bc_ptrs[level] = 1;
			जारी;
		पूर्ण अन्यथा अगर (hdअगरf < 0) अणु
			/* The low key is larger than the upper range; pop. */
			जाओ pop_up;
		पूर्ण
		cur->bc_ptrs[level]++;
	पूर्ण

out:
	/*
	 * If we करोn't end this function with the cursor poपूर्णांकing at a record
	 * block, a subsequent non-error cursor deletion will not release
	 * node-level buffers, causing a buffer leak.  This is quite possible
	 * with a zero-results range query, so release the buffers अगर we
	 * failed to वापस any results.
	 */
	अगर (cur->bc_bufs[0] == शून्य) अणु
		क्रम (i = 0; i < cur->bc_nlevels; i++) अणु
			अगर (cur->bc_bufs[i]) अणु
				xfs_trans_brअन्यथा(cur->bc_tp, cur->bc_bufs[i]);
				cur->bc_bufs[i] = शून्य;
				cur->bc_ptrs[i] = 0;
				cur->bc_ra[i] = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस error;
पूर्ण

/*
 * Query a btree क्रम all records overlapping a given पूर्णांकerval of keys.  The
 * supplied function will be called with each record found; वापस one of the
 * XFS_BTREE_QUERY_RANGE_अणुCONTINUE,ABORTपूर्ण values or the usual negative error
 * code.  This function वापसs -ECANCELED, zero, or a negative error code.
 */
पूर्णांक
xfs_btree_query_range(
	काष्ठा xfs_btree_cur		*cur,
	जोड़ xfs_btree_irec		*low_rec,
	जोड़ xfs_btree_irec		*high_rec,
	xfs_btree_query_range_fn	fn,
	व्योम				*priv)
अणु
	जोड़ xfs_btree_rec		rec;
	जोड़ xfs_btree_key		low_key;
	जोड़ xfs_btree_key		high_key;

	/* Find the keys of both ends of the पूर्णांकerval. */
	cur->bc_rec = *high_rec;
	cur->bc_ops->init_rec_from_cur(cur, &rec);
	cur->bc_ops->init_key_from_rec(&high_key, &rec);

	cur->bc_rec = *low_rec;
	cur->bc_ops->init_rec_from_cur(cur, &rec);
	cur->bc_ops->init_key_from_rec(&low_key, &rec);

	/* Enक्रमce low key < high key. */
	अगर (cur->bc_ops->dअगरf_two_keys(cur, &low_key, &high_key) > 0)
		वापस -EINVAL;

	अगर (!(cur->bc_flags & XFS_BTREE_OVERLAPPING))
		वापस xfs_btree_simple_query_range(cur, &low_key,
				&high_key, fn, priv);
	वापस xfs_btree_overlapped_query_range(cur, &low_key, &high_key,
			fn, priv);
पूर्ण

/* Query a btree क्रम all records. */
पूर्णांक
xfs_btree_query_all(
	काष्ठा xfs_btree_cur		*cur,
	xfs_btree_query_range_fn	fn,
	व्योम				*priv)
अणु
	जोड़ xfs_btree_key		low_key;
	जोड़ xfs_btree_key		high_key;

	स_रखो(&cur->bc_rec, 0, माप(cur->bc_rec));
	स_रखो(&low_key, 0, माप(low_key));
	स_रखो(&high_key, 0xFF, माप(high_key));

	वापस xfs_btree_simple_query_range(cur, &low_key, &high_key, fn, priv);
पूर्ण

/*
 * Calculate the number of blocks needed to store a given number of records
 * in a लघु-क्रमmat (per-AG metadata) btree.
 */
अचिन्हित दीर्घ दीर्घ
xfs_btree_calc_size(
	uपूर्णांक			*limits,
	अचिन्हित दीर्घ दीर्घ	len)
अणु
	पूर्णांक			level;
	पूर्णांक			maxrecs;
	अचिन्हित दीर्घ दीर्घ	rval;

	maxrecs = limits[0];
	क्रम (level = 0, rval = 0; len > 1; level++) अणु
		len += maxrecs - 1;
		करो_भाग(len, maxrecs);
		maxrecs = limits[1];
		rval += len;
	पूर्ण
	वापस rval;
पूर्ण

अटल पूर्णांक
xfs_btree_count_blocks_helper(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	व्योम			*data)
अणु
	xfs_extlen_t		*blocks = data;
	(*blocks)++;

	वापस 0;
पूर्ण

/* Count the blocks in a btree and वापस the result in *blocks. */
पूर्णांक
xfs_btree_count_blocks(
	काष्ठा xfs_btree_cur	*cur,
	xfs_extlen_t		*blocks)
अणु
	*blocks = 0;
	वापस xfs_btree_visit_blocks(cur, xfs_btree_count_blocks_helper,
			XFS_BTREE_VISIT_ALL, blocks);
पूर्ण

/* Compare two btree poपूर्णांकers. */
पूर्णांक64_t
xfs_btree_dअगरf_two_ptrs(
	काष्ठा xfs_btree_cur		*cur,
	स्थिर जोड़ xfs_btree_ptr	*a,
	स्थिर जोड़ xfs_btree_ptr	*b)
अणु
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		वापस (पूर्णांक64_t)be64_to_cpu(a->l) - be64_to_cpu(b->l);
	वापस (पूर्णांक64_t)be32_to_cpu(a->s) - be32_to_cpu(b->s);
पूर्ण

/* If there's an extent, we're करोne. */
STATIC पूर्णांक
xfs_btree_has_record_helper(
	काष्ठा xfs_btree_cur		*cur,
	जोड़ xfs_btree_rec		*rec,
	व्योम				*priv)
अणु
	वापस -ECANCELED;
पूर्ण

/* Is there a record covering a given range of keys? */
पूर्णांक
xfs_btree_has_record(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_irec	*low,
	जोड़ xfs_btree_irec	*high,
	bool			*exists)
अणु
	पूर्णांक			error;

	error = xfs_btree_query_range(cur, low, high,
			&xfs_btree_has_record_helper, शून्य);
	अगर (error == -ECANCELED) अणु
		*exists = true;
		वापस 0;
	पूर्ण
	*exists = false;
	वापस error;
पूर्ण

/* Are there more records in this btree? */
bool
xfs_btree_has_more_records(
	काष्ठा xfs_btree_cur	*cur)
अणु
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_buf		*bp;

	block = xfs_btree_get_block(cur, 0, &bp);

	/* There are still records in this block. */
	अगर (cur->bc_ptrs[0] < xfs_btree_get_numrecs(block))
		वापस true;

	/* There are more record blocks. */
	अगर (cur->bc_flags & XFS_BTREE_LONG_PTRS)
		वापस block->bb_u.l.bb_rightsib != cpu_to_be64(शून्यFSBLOCK);
	अन्यथा
		वापस block->bb_u.s.bb_rightsib != cpu_to_be32(शून्यAGBLOCK);
पूर्ण
