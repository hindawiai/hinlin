<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_refcount_btree.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_refcount.h"
#समावेश "xfs_rmap.h"

/* Allowable refcount adjusपंचांगent amounts. */
क्रमागत xfs_refc_adjust_op अणु
	XFS_REFCOUNT_ADJUST_INCREASE	= 1,
	XFS_REFCOUNT_ADJUST_DECREASE	= -1,
	XFS_REFCOUNT_ADJUST_COW_ALLOC	= 0,
	XFS_REFCOUNT_ADJUST_COW_FREE	= -1,
पूर्ण;

STATIC पूर्णांक __xfs_refcount_cow_alloc(काष्ठा xfs_btree_cur *rcur,
		xfs_agblock_t agbno, xfs_extlen_t aglen);
STATIC पूर्णांक __xfs_refcount_cow_मुक्त(काष्ठा xfs_btree_cur *rcur,
		xfs_agblock_t agbno, xfs_extlen_t aglen);

/*
 * Look up the first record less than or equal to [bno, len] in the btree
 * given by cur.
 */
पूर्णांक
xfs_refcount_lookup_le(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	पूर्णांक			*stat)
अणु
	trace_xfs_refcount_lookup(cur->bc_mp, cur->bc_ag.agno, bno,
			XFS_LOOKUP_LE);
	cur->bc_rec.rc.rc_startblock = bno;
	cur->bc_rec.rc.rc_blockcount = 0;
	वापस xfs_btree_lookup(cur, XFS_LOOKUP_LE, stat);
पूर्ण

/*
 * Look up the first record greater than or equal to [bno, len] in the btree
 * given by cur.
 */
पूर्णांक
xfs_refcount_lookup_ge(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	पूर्णांक			*stat)
अणु
	trace_xfs_refcount_lookup(cur->bc_mp, cur->bc_ag.agno, bno,
			XFS_LOOKUP_GE);
	cur->bc_rec.rc.rc_startblock = bno;
	cur->bc_rec.rc.rc_blockcount = 0;
	वापस xfs_btree_lookup(cur, XFS_LOOKUP_GE, stat);
पूर्ण

/*
 * Look up the first record equal to [bno, len] in the btree
 * given by cur.
 */
पूर्णांक
xfs_refcount_lookup_eq(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	पूर्णांक			*stat)
अणु
	trace_xfs_refcount_lookup(cur->bc_mp, cur->bc_ag.agno, bno,
			XFS_LOOKUP_LE);
	cur->bc_rec.rc.rc_startblock = bno;
	cur->bc_rec.rc.rc_blockcount = 0;
	वापस xfs_btree_lookup(cur, XFS_LOOKUP_EQ, stat);
पूर्ण

/* Convert on-disk record to in-core क्रमmat. */
व्योम
xfs_refcount_btrec_to_irec(
	जोड़ xfs_btree_rec		*rec,
	काष्ठा xfs_refcount_irec	*irec)
अणु
	irec->rc_startblock = be32_to_cpu(rec->refc.rc_startblock);
	irec->rc_blockcount = be32_to_cpu(rec->refc.rc_blockcount);
	irec->rc_refcount = be32_to_cpu(rec->refc.rc_refcount);
पूर्ण

/*
 * Get the data from the poपूर्णांकed-to record.
 */
पूर्णांक
xfs_refcount_get_rec(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_refcount_irec	*irec,
	पूर्णांक				*stat)
अणु
	काष्ठा xfs_mount		*mp = cur->bc_mp;
	xfs_agnumber_t			agno = cur->bc_ag.agno;
	जोड़ xfs_btree_rec		*rec;
	पूर्णांक				error;
	xfs_agblock_t			realstart;

	error = xfs_btree_get_rec(cur, &rec, stat);
	अगर (error || !*stat)
		वापस error;

	xfs_refcount_btrec_to_irec(rec, irec);

	agno = cur->bc_ag.agno;
	अगर (irec->rc_blockcount == 0 || irec->rc_blockcount > MAXREFCEXTLEN)
		जाओ out_bad_rec;

	/* handle special COW-staging state */
	realstart = irec->rc_startblock;
	अगर (realstart & XFS_REFC_COW_START) अणु
		अगर (irec->rc_refcount != 1)
			जाओ out_bad_rec;
		realstart &= ~XFS_REFC_COW_START;
	पूर्ण अन्यथा अगर (irec->rc_refcount < 2) अणु
		जाओ out_bad_rec;
	पूर्ण

	/* check क्रम valid extent range, including overflow */
	अगर (!xfs_verअगरy_agbno(mp, agno, realstart))
		जाओ out_bad_rec;
	अगर (realstart > realstart + irec->rc_blockcount)
		जाओ out_bad_rec;
	अगर (!xfs_verअगरy_agbno(mp, agno, realstart + irec->rc_blockcount - 1))
		जाओ out_bad_rec;

	अगर (irec->rc_refcount == 0 || irec->rc_refcount > MAXREFCOUNT)
		जाओ out_bad_rec;

	trace_xfs_refcount_get(cur->bc_mp, cur->bc_ag.agno, irec);
	वापस 0;

out_bad_rec:
	xfs_warn(mp,
		"Refcount BTree record corruption in AG %d detected!", agno);
	xfs_warn(mp,
		"Start block 0x%x, block count 0x%x, references 0x%x",
		irec->rc_startblock, irec->rc_blockcount, irec->rc_refcount);
	वापस -EFSCORRUPTED;
पूर्ण

/*
 * Update the record referred to by cur to the value given
 * by [bno, len, refcount].
 * This either works (वापस 0) or माला_लो an EFSCORRUPTED error.
 */
STATIC पूर्णांक
xfs_refcount_update(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_refcount_irec	*irec)
अणु
	जोड़ xfs_btree_rec	rec;
	पूर्णांक			error;

	trace_xfs_refcount_update(cur->bc_mp, cur->bc_ag.agno, irec);
	rec.refc.rc_startblock = cpu_to_be32(irec->rc_startblock);
	rec.refc.rc_blockcount = cpu_to_be32(irec->rc_blockcount);
	rec.refc.rc_refcount = cpu_to_be32(irec->rc_refcount);
	error = xfs_btree_update(cur, &rec);
	अगर (error)
		trace_xfs_refcount_update_error(cur->bc_mp,
				cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Insert the record referred to by cur to the value given
 * by [bno, len, refcount].
 * This either works (वापस 0) or माला_लो an EFSCORRUPTED error.
 */
पूर्णांक
xfs_refcount_insert(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_refcount_irec	*irec,
	पूर्णांक				*i)
अणु
	पूर्णांक				error;

	trace_xfs_refcount_insert(cur->bc_mp, cur->bc_ag.agno, irec);
	cur->bc_rec.rc.rc_startblock = irec->rc_startblock;
	cur->bc_rec.rc.rc_blockcount = irec->rc_blockcount;
	cur->bc_rec.rc.rc_refcount = irec->rc_refcount;
	error = xfs_btree_insert(cur, i);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, *i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

out_error:
	अगर (error)
		trace_xfs_refcount_insert_error(cur->bc_mp,
				cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Remove the record referred to by cur, then set the poपूर्णांकer to the spot
 * where the record could be re-inserted, in हाल we want to increment or
 * decrement the cursor.
 * This either works (वापस 0) or माला_लो an EFSCORRUPTED error.
 */
STATIC पूर्णांक
xfs_refcount_delete(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			*i)
अणु
	काष्ठा xfs_refcount_irec	irec;
	पूर्णांक			found_rec;
	पूर्णांक			error;

	error = xfs_refcount_get_rec(cur, &irec, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण
	trace_xfs_refcount_delete(cur->bc_mp, cur->bc_ag.agno, &irec);
	error = xfs_btree_delete(cur, i);
	अगर (XFS_IS_CORRUPT(cur->bc_mp, *i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण
	अगर (error)
		जाओ out_error;
	error = xfs_refcount_lookup_ge(cur, irec.rc_startblock, &found_rec);
out_error:
	अगर (error)
		trace_xfs_refcount_delete_error(cur->bc_mp,
				cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Adjusting the Reference Count
 *
 * As stated अन्यथाwhere, the reference count btree (refcbt) stores
 * >1 reference counts क्रम extents of physical blocks.  In this
 * operation, we're either raising or lowering the reference count of
 * some subrange stored in the tree:
 *
 *      <------ adjusपंचांगent range ------>
 * ----+   +---+-----+ +--+--------+---------
 *  2  |   | 3 |  4  | |17|   55   |   10
 * ----+   +---+-----+ +--+--------+---------
 * X axis is physical blocks number;
 * reference counts are the numbers inside the rectangles
 *
 * The first thing we need to करो is to ensure that there are no
 * refcount extents crossing either boundary of the range to be
 * adjusted.  For any extent that करोes cross a boundary, split it पूर्णांकo
 * two extents so that we can increment the refcount of one of the
 * pieces later:
 *
 *      <------ adjusपंचांगent range ------>
 * ----+   +---+-----+ +--+--------+----+----
 *  2  |   | 3 |  2  | |17|   55   | 10 | 10
 * ----+   +---+-----+ +--+--------+----+----
 *
 * For this next step, let's assume that all the physical blocks in
 * the adjusपंचांगent range are mapped to a file and are thereक्रमe in use
 * at least once.  Thereक्रमe, we can infer that any gap in the
 * refcount tree within the adjusपंचांगent range represents a physical
 * extent with refcount == 1:
 *
 *      <------ adjusपंचांगent range ------>
 * ----+---+---+-----+-+--+--------+----+----
 *  2  |"1"| 3 |  2  |1|17|   55   | 10 | 10
 * ----+---+---+-----+-+--+--------+----+----
 *      ^
 *
 * For each extent that falls within the पूर्णांकerval range, figure out
 * which extent is to the left or the right of that extent.  Now we
 * have a left, current, and right extent.  If the new reference count
 * of the center extent enables us to merge left, center, and right
 * पूर्णांकo one record covering all three, करो so.  If the center extent is
 * at the left end of the range, abuts the left extent, and its new
 * reference count matches the left extent's record, then merge them.
 * If the center extent is at the right end of the range, abuts the
 * right extent, and the reference counts match, merge those.  In the
 * example, we can left merge (assuming an increment operation):
 *
 *      <------ adjusपंचांगent range ------>
 * --------+---+-----+-+--+--------+----+----
 *    2    | 3 |  2  |1|17|   55   | 10 | 10
 * --------+---+-----+-+--+--------+----+----
 *          ^
 *
 * For all other extents within the range, adjust the reference count
 * or delete it अगर the refcount falls below 2.  If we were
 * incrementing, the end result looks like this:
 *
 *      <------ adjusपंचांगent range ------>
 * --------+---+-----+-+--+--------+----+----
 *    2    | 4 |  3  |2|18|   56   | 11 | 10
 * --------+---+-----+-+--+--------+----+----
 *
 * The result of a decrement operation looks as such:
 *
 *      <------ adjusपंचांगent range ------>
 * ----+   +---+       +--+--------+----+----
 *  2  |   | 2 |       |16|   54   |  9 | 10
 * ----+   +---+       +--+--------+----+----
 *      DDDD    111111DD
 *
 * The blocks marked "D" are मुक्तd; the blocks marked "1" are only
 * referenced once and thereक्रमe the record is हटाओd from the
 * refcount btree.
 */

/* Next block after this extent. */
अटल अंतरभूत xfs_agblock_t
xfs_refc_next(
	काष्ठा xfs_refcount_irec	*rc)
अणु
	वापस rc->rc_startblock + rc->rc_blockcount;
पूर्ण

/*
 * Split a refcount extent that crosses agbno.
 */
STATIC पूर्णांक
xfs_refcount_split_extent(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agblock_t			agbno,
	bool				*shape_changed)
अणु
	काष्ठा xfs_refcount_irec	rcext, पंचांगp;
	पूर्णांक				found_rec;
	पूर्णांक				error;

	*shape_changed = false;
	error = xfs_refcount_lookup_le(cur, agbno, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (!found_rec)
		वापस 0;

	error = xfs_refcount_get_rec(cur, &rcext, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण
	अगर (rcext.rc_startblock == agbno || xfs_refc_next(&rcext) <= agbno)
		वापस 0;

	*shape_changed = true;
	trace_xfs_refcount_split_extent(cur->bc_mp, cur->bc_ag.agno,
			&rcext, agbno);

	/* Establish the right extent. */
	पंचांगp = rcext;
	पंचांगp.rc_startblock = agbno;
	पंचांगp.rc_blockcount -= (agbno - rcext.rc_startblock);
	error = xfs_refcount_update(cur, &पंचांगp);
	अगर (error)
		जाओ out_error;

	/* Insert the left extent. */
	पंचांगp = rcext;
	पंचांगp.rc_blockcount = agbno - rcext.rc_startblock;
	error = xfs_refcount_insert(cur, &पंचांगp, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण
	वापस error;

out_error:
	trace_xfs_refcount_split_extent_error(cur->bc_mp,
			cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Merge the left, center, and right extents.
 */
STATIC पूर्णांक
xfs_refcount_merge_center_extents(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_refcount_irec	*left,
	काष्ठा xfs_refcount_irec	*center,
	काष्ठा xfs_refcount_irec	*right,
	अचिन्हित दीर्घ दीर्घ		extlen,
	xfs_extlen_t			*aglen)
अणु
	पूर्णांक				error;
	पूर्णांक				found_rec;

	trace_xfs_refcount_merge_center_extents(cur->bc_mp,
			cur->bc_ag.agno, left, center, right);

	/*
	 * Make sure the center and right extents are not in the btree.
	 * If the center extent was synthesized, the first delete call
	 * हटाओs the right extent and we skip the second deletion.
	 * If center and right were in the btree, then the first delete
	 * call हटाओs the center and the second one हटाओs the right
	 * extent.
	 */
	error = xfs_refcount_lookup_ge(cur, center->rc_startblock,
			&found_rec);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	error = xfs_refcount_delete(cur, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	अगर (center->rc_refcount > 1) अणु
		error = xfs_refcount_delete(cur, &found_rec);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
	पूर्ण

	/* Enlarge the left extent. */
	error = xfs_refcount_lookup_le(cur, left->rc_startblock,
			&found_rec);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	left->rc_blockcount = extlen;
	error = xfs_refcount_update(cur, left);
	अगर (error)
		जाओ out_error;

	*aglen = 0;
	वापस error;

out_error:
	trace_xfs_refcount_merge_center_extents_error(cur->bc_mp,
			cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Merge with the left extent.
 */
STATIC पूर्णांक
xfs_refcount_merge_left_extent(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_refcount_irec	*left,
	काष्ठा xfs_refcount_irec	*cleft,
	xfs_agblock_t			*agbno,
	xfs_extlen_t			*aglen)
अणु
	पूर्णांक				error;
	पूर्णांक				found_rec;

	trace_xfs_refcount_merge_left_extent(cur->bc_mp,
			cur->bc_ag.agno, left, cleft);

	/* If the extent at agbno (cleft) wasn't synthesized, हटाओ it. */
	अगर (cleft->rc_refcount > 1) अणु
		error = xfs_refcount_lookup_le(cur, cleft->rc_startblock,
				&found_rec);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण

		error = xfs_refcount_delete(cur, &found_rec);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
	पूर्ण

	/* Enlarge the left extent. */
	error = xfs_refcount_lookup_le(cur, left->rc_startblock,
			&found_rec);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	left->rc_blockcount += cleft->rc_blockcount;
	error = xfs_refcount_update(cur, left);
	अगर (error)
		जाओ out_error;

	*agbno += cleft->rc_blockcount;
	*aglen -= cleft->rc_blockcount;
	वापस error;

out_error:
	trace_xfs_refcount_merge_left_extent_error(cur->bc_mp,
			cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Merge with the right extent.
 */
STATIC पूर्णांक
xfs_refcount_merge_right_extent(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_refcount_irec	*right,
	काष्ठा xfs_refcount_irec	*cright,
	xfs_extlen_t			*aglen)
अणु
	पूर्णांक				error;
	पूर्णांक				found_rec;

	trace_xfs_refcount_merge_right_extent(cur->bc_mp,
			cur->bc_ag.agno, cright, right);

	/*
	 * If the extent ending at agbno+aglen (cright) wasn't synthesized,
	 * हटाओ it.
	 */
	अगर (cright->rc_refcount > 1) अणु
		error = xfs_refcount_lookup_le(cur, cright->rc_startblock,
			&found_rec);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण

		error = xfs_refcount_delete(cur, &found_rec);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
	पूर्ण

	/* Enlarge the right extent. */
	error = xfs_refcount_lookup_le(cur, right->rc_startblock,
			&found_rec);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	right->rc_startblock -= cright->rc_blockcount;
	right->rc_blockcount += cright->rc_blockcount;
	error = xfs_refcount_update(cur, right);
	अगर (error)
		जाओ out_error;

	*aglen -= cright->rc_blockcount;
	वापस error;

out_error:
	trace_xfs_refcount_merge_right_extent_error(cur->bc_mp,
			cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

#घोषणा XFS_FIND_RCEXT_SHARED	1
#घोषणा XFS_FIND_RCEXT_COW	2
/*
 * Find the left extent and the one after it (cleft).  This function assumes
 * that we've alपढ़ोy split any extent crossing agbno.
 */
STATIC पूर्णांक
xfs_refcount_find_left_extents(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_refcount_irec	*left,
	काष्ठा xfs_refcount_irec	*cleft,
	xfs_agblock_t			agbno,
	xfs_extlen_t			aglen,
	पूर्णांक				flags)
अणु
	काष्ठा xfs_refcount_irec	पंचांगp;
	पूर्णांक				error;
	पूर्णांक				found_rec;

	left->rc_startblock = cleft->rc_startblock = शून्यAGBLOCK;
	error = xfs_refcount_lookup_le(cur, agbno - 1, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (!found_rec)
		वापस 0;

	error = xfs_refcount_get_rec(cur, &पंचांगp, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	अगर (xfs_refc_next(&पंचांगp) != agbno)
		वापस 0;
	अगर ((flags & XFS_FIND_RCEXT_SHARED) && पंचांगp.rc_refcount < 2)
		वापस 0;
	अगर ((flags & XFS_FIND_RCEXT_COW) && पंचांगp.rc_refcount > 1)
		वापस 0;
	/* We have a left extent; retrieve (or invent) the next right one */
	*left = पंचांगp;

	error = xfs_btree_increment(cur, 0, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (found_rec) अणु
		error = xfs_refcount_get_rec(cur, &पंचांगp, &found_rec);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण

		/* अगर पंचांगp starts at the end of our range, just use that */
		अगर (पंचांगp.rc_startblock == agbno)
			*cleft = पंचांगp;
		अन्यथा अणु
			/*
			 * There's a gap in the refcntbt at the start of the
			 * range we're पूर्णांकerested in (refcount == 1) so
			 * synthesize the implied extent and pass it back.
			 * We assume here that the agbno/aglen range was
			 * passed in from a data विभाजन extent mapping and
			 * thereक्रमe is allocated to exactly one owner.
			 */
			cleft->rc_startblock = agbno;
			cleft->rc_blockcount = min(aglen,
					पंचांगp.rc_startblock - agbno);
			cleft->rc_refcount = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * No extents, so pretend that there's one covering the whole
		 * range.
		 */
		cleft->rc_startblock = agbno;
		cleft->rc_blockcount = aglen;
		cleft->rc_refcount = 1;
	पूर्ण
	trace_xfs_refcount_find_left_extent(cur->bc_mp, cur->bc_ag.agno,
			left, cleft, agbno);
	वापस error;

out_error:
	trace_xfs_refcount_find_left_extent_error(cur->bc_mp,
			cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Find the right extent and the one beक्रमe it (cright).  This function
 * assumes that we've alपढ़ोy split any extents crossing agbno + aglen.
 */
STATIC पूर्णांक
xfs_refcount_find_right_extents(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_refcount_irec	*right,
	काष्ठा xfs_refcount_irec	*cright,
	xfs_agblock_t			agbno,
	xfs_extlen_t			aglen,
	पूर्णांक				flags)
अणु
	काष्ठा xfs_refcount_irec	पंचांगp;
	पूर्णांक				error;
	पूर्णांक				found_rec;

	right->rc_startblock = cright->rc_startblock = शून्यAGBLOCK;
	error = xfs_refcount_lookup_ge(cur, agbno + aglen, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (!found_rec)
		वापस 0;

	error = xfs_refcount_get_rec(cur, &पंचांगp, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	अगर (पंचांगp.rc_startblock != agbno + aglen)
		वापस 0;
	अगर ((flags & XFS_FIND_RCEXT_SHARED) && पंचांगp.rc_refcount < 2)
		वापस 0;
	अगर ((flags & XFS_FIND_RCEXT_COW) && पंचांगp.rc_refcount > 1)
		वापस 0;
	/* We have a right extent; retrieve (or invent) the next left one */
	*right = पंचांगp;

	error = xfs_btree_decrement(cur, 0, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (found_rec) अणु
		error = xfs_refcount_get_rec(cur, &पंचांगp, &found_rec);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण

		/* अगर पंचांगp ends at the end of our range, just use that */
		अगर (xfs_refc_next(&पंचांगp) == agbno + aglen)
			*cright = पंचांगp;
		अन्यथा अणु
			/*
			 * There's a gap in the refcntbt at the end of the
			 * range we're पूर्णांकerested in (refcount == 1) so
			 * create the implied extent and pass it back.
			 * We assume here that the agbno/aglen range was
			 * passed in from a data विभाजन extent mapping and
			 * thereक्रमe is allocated to exactly one owner.
			 */
			cright->rc_startblock = max(agbno, xfs_refc_next(&पंचांगp));
			cright->rc_blockcount = right->rc_startblock -
					cright->rc_startblock;
			cright->rc_refcount = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * No extents, so pretend that there's one covering the whole
		 * range.
		 */
		cright->rc_startblock = agbno;
		cright->rc_blockcount = aglen;
		cright->rc_refcount = 1;
	पूर्ण
	trace_xfs_refcount_find_right_extent(cur->bc_mp, cur->bc_ag.agno,
			cright, right, agbno + aglen);
	वापस error;

out_error:
	trace_xfs_refcount_find_right_extent_error(cur->bc_mp,
			cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/* Is this extent valid? */
अटल अंतरभूत bool
xfs_refc_valid(
	काष्ठा xfs_refcount_irec	*rc)
अणु
	वापस rc->rc_startblock != शून्यAGBLOCK;
पूर्ण

/*
 * Try to merge with any extents on the boundaries of the adjusपंचांगent range.
 */
STATIC पूर्णांक
xfs_refcount_merge_extents(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		*agbno,
	xfs_extlen_t		*aglen,
	क्रमागत xfs_refc_adjust_op adjust,
	पूर्णांक			flags,
	bool			*shape_changed)
अणु
	काष्ठा xfs_refcount_irec	left = अणु0पूर्ण, cleft = अणु0पूर्ण;
	काष्ठा xfs_refcount_irec	cright = अणु0पूर्ण, right = अणु0पूर्ण;
	पूर्णांक				error;
	अचिन्हित दीर्घ दीर्घ		ulen;
	bool				cequal;

	*shape_changed = false;
	/*
	 * Find the extent just below agbno [left], just above agbno [cleft],
	 * just below (agbno + aglen) [cright], and just above (agbno + aglen)
	 * [right].
	 */
	error = xfs_refcount_find_left_extents(cur, &left, &cleft, *agbno,
			*aglen, flags);
	अगर (error)
		वापस error;
	error = xfs_refcount_find_right_extents(cur, &right, &cright, *agbno,
			*aglen, flags);
	अगर (error)
		वापस error;

	/* No left or right extent to merge; निकास. */
	अगर (!xfs_refc_valid(&left) && !xfs_refc_valid(&right))
		वापस 0;

	cequal = (cleft.rc_startblock == cright.rc_startblock) &&
		 (cleft.rc_blockcount == cright.rc_blockcount);

	/* Try to merge left, cleft, and right.  cleft must == cright. */
	ulen = (अचिन्हित दीर्घ दीर्घ)left.rc_blockcount + cleft.rc_blockcount +
			right.rc_blockcount;
	अगर (xfs_refc_valid(&left) && xfs_refc_valid(&right) &&
	    xfs_refc_valid(&cleft) && xfs_refc_valid(&cright) && cequal &&
	    left.rc_refcount == cleft.rc_refcount + adjust &&
	    right.rc_refcount == cleft.rc_refcount + adjust &&
	    ulen < MAXREFCEXTLEN) अणु
		*shape_changed = true;
		वापस xfs_refcount_merge_center_extents(cur, &left, &cleft,
				&right, ulen, aglen);
	पूर्ण

	/* Try to merge left and cleft. */
	ulen = (अचिन्हित दीर्घ दीर्घ)left.rc_blockcount + cleft.rc_blockcount;
	अगर (xfs_refc_valid(&left) && xfs_refc_valid(&cleft) &&
	    left.rc_refcount == cleft.rc_refcount + adjust &&
	    ulen < MAXREFCEXTLEN) अणु
		*shape_changed = true;
		error = xfs_refcount_merge_left_extent(cur, &left, &cleft,
				agbno, aglen);
		अगर (error)
			वापस error;

		/*
		 * If we just merged left + cleft and cleft == cright,
		 * we no दीर्घer have a cright to merge with right.  We're करोne.
		 */
		अगर (cequal)
			वापस 0;
	पूर्ण

	/* Try to merge cright and right. */
	ulen = (अचिन्हित दीर्घ दीर्घ)right.rc_blockcount + cright.rc_blockcount;
	अगर (xfs_refc_valid(&right) && xfs_refc_valid(&cright) &&
	    right.rc_refcount == cright.rc_refcount + adjust &&
	    ulen < MAXREFCEXTLEN) अणु
		*shape_changed = true;
		वापस xfs_refcount_merge_right_extent(cur, &right, &cright,
				aglen);
	पूर्ण

	वापस error;
पूर्ण

/*
 * XXX: This is a pretty hand-wavy estimate.  The penalty क्रम guessing
 * true incorrectly is a shutकरोwn FS; the penalty क्रम guessing false
 * incorrectly is more transaction rolls than might be necessary.
 * Be conservative here.
 */
अटल bool
xfs_refcount_still_have_space(
	काष्ठा xfs_btree_cur		*cur)
अणु
	अचिन्हित दीर्घ			overhead;

	overhead = cur->bc_ag.refc.shape_changes *
			xfs_allocमुक्त_log_count(cur->bc_mp, 1);
	overhead *= cur->bc_mp->m_sb.sb_blocksize;

	/*
	 * Only allow 2 refcount extent updates per transaction अगर the
	 * refcount जारी update "error" has been injected.
	 */
	अगर (cur->bc_ag.refc.nr_ops > 2 &&
	    XFS_TEST_ERROR(false, cur->bc_mp,
			XFS_ERRTAG_REFCOUNT_CONTINUE_UPDATE))
		वापस false;

	अगर (cur->bc_ag.refc.nr_ops == 0)
		वापस true;
	अन्यथा अगर (overhead > cur->bc_tp->t_log_res)
		वापस false;
	वापस  cur->bc_tp->t_log_res - overhead >
		cur->bc_ag.refc.nr_ops * XFS_REFCOUNT_ITEM_OVERHEAD;
पूर्ण

/*
 * Adjust the refcounts of middle extents.  At this poपूर्णांक we should have
 * split extents that crossed the adjusपंचांगent range; merged with adjacent
 * extents; and updated agbno/aglen to reflect the merges.  Thereक्रमe,
 * all we have to करो is update the extents inside [agbno, agbno + aglen].
 */
STATIC पूर्णांक
xfs_refcount_adjust_extents(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		*agbno,
	xfs_extlen_t		*aglen,
	क्रमागत xfs_refc_adjust_op	adj,
	काष्ठा xfs_owner_info	*oinfo)
अणु
	काष्ठा xfs_refcount_irec	ext, पंचांगp;
	पूर्णांक				error;
	पूर्णांक				found_rec, found_पंचांगp;
	xfs_fsblock_t			fsbno;

	/* Merging did all the work alपढ़ोy. */
	अगर (*aglen == 0)
		वापस 0;

	error = xfs_refcount_lookup_ge(cur, *agbno, &found_rec);
	अगर (error)
		जाओ out_error;

	जबतक (*aglen > 0 && xfs_refcount_still_have_space(cur)) अणु
		error = xfs_refcount_get_rec(cur, &ext, &found_rec);
		अगर (error)
			जाओ out_error;
		अगर (!found_rec) अणु
			ext.rc_startblock = cur->bc_mp->m_sb.sb_agblocks;
			ext.rc_blockcount = 0;
			ext.rc_refcount = 0;
		पूर्ण

		/*
		 * Deal with a hole in the refcount tree; अगर a file maps to
		 * these blocks and there's no refcountbt record, pretend that
		 * there is one with refcount == 1.
		 */
		अगर (ext.rc_startblock != *agbno) अणु
			पंचांगp.rc_startblock = *agbno;
			पंचांगp.rc_blockcount = min(*aglen,
					ext.rc_startblock - *agbno);
			पंचांगp.rc_refcount = 1 + adj;
			trace_xfs_refcount_modअगरy_extent(cur->bc_mp,
					cur->bc_ag.agno, &पंचांगp);

			/*
			 * Either cover the hole (increment) or
			 * delete the range (decrement).
			 */
			अगर (पंचांगp.rc_refcount) अणु
				error = xfs_refcount_insert(cur, &पंचांगp,
						&found_पंचांगp);
				अगर (error)
					जाओ out_error;
				अगर (XFS_IS_CORRUPT(cur->bc_mp,
						   found_पंचांगp != 1)) अणु
					error = -EFSCORRUPTED;
					जाओ out_error;
				पूर्ण
				cur->bc_ag.refc.nr_ops++;
			पूर्ण अन्यथा अणु
				fsbno = XFS_AGB_TO_FSB(cur->bc_mp,
						cur->bc_ag.agno,
						पंचांगp.rc_startblock);
				xfs_bmap_add_मुक्त(cur->bc_tp, fsbno,
						  पंचांगp.rc_blockcount, oinfo);
			पूर्ण

			(*agbno) += पंचांगp.rc_blockcount;
			(*aglen) -= पंचांगp.rc_blockcount;

			error = xfs_refcount_lookup_ge(cur, *agbno,
					&found_rec);
			अगर (error)
				जाओ out_error;
		पूर्ण

		/* Stop अगर there's nothing left to modअगरy */
		अगर (*aglen == 0 || !xfs_refcount_still_have_space(cur))
			अवरोध;

		/*
		 * Adjust the reference count and either update the tree
		 * (incr) or मुक्त the blocks (decr).
		 */
		अगर (ext.rc_refcount == MAXREFCOUNT)
			जाओ skip;
		ext.rc_refcount += adj;
		trace_xfs_refcount_modअगरy_extent(cur->bc_mp,
				cur->bc_ag.agno, &ext);
		अगर (ext.rc_refcount > 1) अणु
			error = xfs_refcount_update(cur, &ext);
			अगर (error)
				जाओ out_error;
			cur->bc_ag.refc.nr_ops++;
		पूर्ण अन्यथा अगर (ext.rc_refcount == 1) अणु
			error = xfs_refcount_delete(cur, &found_rec);
			अगर (error)
				जाओ out_error;
			अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ out_error;
			पूर्ण
			cur->bc_ag.refc.nr_ops++;
			जाओ advloop;
		पूर्ण अन्यथा अणु
			fsbno = XFS_AGB_TO_FSB(cur->bc_mp,
					cur->bc_ag.agno,
					ext.rc_startblock);
			xfs_bmap_add_मुक्त(cur->bc_tp, fsbno, ext.rc_blockcount,
					  oinfo);
		पूर्ण

skip:
		error = xfs_btree_increment(cur, 0, &found_rec);
		अगर (error)
			जाओ out_error;

advloop:
		(*agbno) += ext.rc_blockcount;
		(*aglen) -= ext.rc_blockcount;
	पूर्ण

	वापस error;
out_error:
	trace_xfs_refcount_modअगरy_extent_error(cur->bc_mp,
			cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/* Adjust the reference count of a range of AG blocks. */
STATIC पूर्णांक
xfs_refcount_adjust(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		agbno,
	xfs_extlen_t		aglen,
	xfs_agblock_t		*new_agbno,
	xfs_extlen_t		*new_aglen,
	क्रमागत xfs_refc_adjust_op	adj,
	काष्ठा xfs_owner_info	*oinfo)
अणु
	bool			shape_changed;
	पूर्णांक			shape_changes = 0;
	पूर्णांक			error;

	*new_agbno = agbno;
	*new_aglen = aglen;
	अगर (adj == XFS_REFCOUNT_ADJUST_INCREASE)
		trace_xfs_refcount_increase(cur->bc_mp, cur->bc_ag.agno,
				agbno, aglen);
	अन्यथा
		trace_xfs_refcount_decrease(cur->bc_mp, cur->bc_ag.agno,
				agbno, aglen);

	/*
	 * Ensure that no rcextents cross the boundary of the adjusपंचांगent range.
	 */
	error = xfs_refcount_split_extent(cur, agbno, &shape_changed);
	अगर (error)
		जाओ out_error;
	अगर (shape_changed)
		shape_changes++;

	error = xfs_refcount_split_extent(cur, agbno + aglen, &shape_changed);
	अगर (error)
		जाओ out_error;
	अगर (shape_changed)
		shape_changes++;

	/*
	 * Try to merge with the left or right extents of the range.
	 */
	error = xfs_refcount_merge_extents(cur, new_agbno, new_aglen, adj,
			XFS_FIND_RCEXT_SHARED, &shape_changed);
	अगर (error)
		जाओ out_error;
	अगर (shape_changed)
		shape_changes++;
	अगर (shape_changes)
		cur->bc_ag.refc.shape_changes++;

	/* Now that we've taken care of the ends, adjust the middle extents */
	error = xfs_refcount_adjust_extents(cur, new_agbno, new_aglen,
			adj, oinfo);
	अगर (error)
		जाओ out_error;

	वापस 0;

out_error:
	trace_xfs_refcount_adjust_error(cur->bc_mp, cur->bc_ag.agno,
			error, _RET_IP_);
	वापस error;
पूर्ण

/* Clean up after calling xfs_refcount_finish_one. */
व्योम
xfs_refcount_finish_one_cleanup(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_btree_cur	*rcur,
	पूर्णांक			error)
अणु
	काष्ठा xfs_buf		*agbp;

	अगर (rcur == शून्य)
		वापस;
	agbp = rcur->bc_ag.agbp;
	xfs_btree_del_cursor(rcur, error);
	अगर (error)
		xfs_trans_brअन्यथा(tp, agbp);
पूर्ण

/*
 * Process one of the deferred refcount operations.  We pass back the
 * btree cursor to मुख्यtain our lock on the btree between calls.
 * This saves समय and eliminates a buffer deadlock between the
 * superblock and the AGF because we'll always grab them in the same
 * order.
 */
पूर्णांक
xfs_refcount_finish_one(
	काष्ठा xfs_trans		*tp,
	क्रमागत xfs_refcount_पूर्णांकent_type	type,
	xfs_fsblock_t			startblock,
	xfs_extlen_t			blockcount,
	xfs_fsblock_t			*new_fsb,
	xfs_extlen_t			*new_len,
	काष्ठा xfs_btree_cur		**pcur)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_btree_cur		*rcur;
	काष्ठा xfs_buf			*agbp = शून्य;
	पूर्णांक				error = 0;
	xfs_agnumber_t			agno;
	xfs_agblock_t			bno;
	xfs_agblock_t			new_agbno;
	अचिन्हित दीर्घ			nr_ops = 0;
	पूर्णांक				shape_changes = 0;

	agno = XFS_FSB_TO_AGNO(mp, startblock);
	ASSERT(agno != शून्यAGNUMBER);
	bno = XFS_FSB_TO_AGBNO(mp, startblock);

	trace_xfs_refcount_deferred(mp, XFS_FSB_TO_AGNO(mp, startblock),
			type, XFS_FSB_TO_AGBNO(mp, startblock),
			blockcount);

	अगर (XFS_TEST_ERROR(false, mp,
			XFS_ERRTAG_REFCOUNT_FINISH_ONE))
		वापस -EIO;

	/*
	 * If we haven't gotten a cursor or the cursor AG doesn't match
	 * the startblock, get one now.
	 */
	rcur = *pcur;
	अगर (rcur != शून्य && rcur->bc_ag.agno != agno) अणु
		nr_ops = rcur->bc_ag.refc.nr_ops;
		shape_changes = rcur->bc_ag.refc.shape_changes;
		xfs_refcount_finish_one_cleanup(tp, rcur, 0);
		rcur = शून्य;
		*pcur = शून्य;
	पूर्ण
	अगर (rcur == शून्य) अणु
		error = xfs_alloc_पढ़ो_agf(tp->t_mountp, tp, agno,
				XFS_ALLOC_FLAG_FREEING, &agbp);
		अगर (error)
			वापस error;

		rcur = xfs_refcountbt_init_cursor(mp, tp, agbp, agno);
		rcur->bc_ag.refc.nr_ops = nr_ops;
		rcur->bc_ag.refc.shape_changes = shape_changes;
	पूर्ण
	*pcur = rcur;

	चयन (type) अणु
	हाल XFS_REFCOUNT_INCREASE:
		error = xfs_refcount_adjust(rcur, bno, blockcount, &new_agbno,
			new_len, XFS_REFCOUNT_ADJUST_INCREASE, शून्य);
		*new_fsb = XFS_AGB_TO_FSB(mp, agno, new_agbno);
		अवरोध;
	हाल XFS_REFCOUNT_DECREASE:
		error = xfs_refcount_adjust(rcur, bno, blockcount, &new_agbno,
			new_len, XFS_REFCOUNT_ADJUST_DECREASE, शून्य);
		*new_fsb = XFS_AGB_TO_FSB(mp, agno, new_agbno);
		अवरोध;
	हाल XFS_REFCOUNT_ALLOC_COW:
		*new_fsb = startblock + blockcount;
		*new_len = 0;
		error = __xfs_refcount_cow_alloc(rcur, bno, blockcount);
		अवरोध;
	हाल XFS_REFCOUNT_FREE_COW:
		*new_fsb = startblock + blockcount;
		*new_len = 0;
		error = __xfs_refcount_cow_मुक्त(rcur, bno, blockcount);
		अवरोध;
	शेष:
		ASSERT(0);
		error = -EFSCORRUPTED;
	पूर्ण
	अगर (!error && *new_len > 0)
		trace_xfs_refcount_finish_one_leftover(mp, agno, type,
				bno, blockcount, new_agbno, *new_len);
	वापस error;
पूर्ण

/*
 * Record a refcount पूर्णांकent क्रम later processing.
 */
अटल व्योम
__xfs_refcount_add(
	काष्ठा xfs_trans		*tp,
	क्रमागत xfs_refcount_पूर्णांकent_type	type,
	xfs_fsblock_t			startblock,
	xfs_extlen_t			blockcount)
अणु
	काष्ठा xfs_refcount_पूर्णांकent	*ri;

	trace_xfs_refcount_defer(tp->t_mountp,
			XFS_FSB_TO_AGNO(tp->t_mountp, startblock),
			type, XFS_FSB_TO_AGBNO(tp->t_mountp, startblock),
			blockcount);

	ri = kmem_alloc(माप(काष्ठा xfs_refcount_पूर्णांकent),
			KM_NOFS);
	INIT_LIST_HEAD(&ri->ri_list);
	ri->ri_type = type;
	ri->ri_startblock = startblock;
	ri->ri_blockcount = blockcount;

	xfs_defer_add(tp, XFS_DEFER_OPS_TYPE_REFCOUNT, &ri->ri_list);
पूर्ण

/*
 * Increase the reference count of the blocks backing a file's extent.
 */
व्योम
xfs_refcount_increase_extent(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_bmbt_irec		*PREV)
अणु
	अगर (!xfs_sb_version_hasreflink(&tp->t_mountp->m_sb))
		वापस;

	__xfs_refcount_add(tp, XFS_REFCOUNT_INCREASE, PREV->br_startblock,
			PREV->br_blockcount);
पूर्ण

/*
 * Decrease the reference count of the blocks backing a file's extent.
 */
व्योम
xfs_refcount_decrease_extent(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_bmbt_irec		*PREV)
अणु
	अगर (!xfs_sb_version_hasreflink(&tp->t_mountp->m_sb))
		वापस;

	__xfs_refcount_add(tp, XFS_REFCOUNT_DECREASE, PREV->br_startblock,
			PREV->br_blockcount);
पूर्ण

/*
 * Given an AG extent, find the lowest-numbered run of shared blocks
 * within that range and वापस the range in fbno/flen.  If
 * find_end_of_shared is set, वापस the दीर्घest contiguous extent of
 * shared blocks; अगर not, just वापस the first extent we find.  If no
 * shared blocks are found, fbno and flen will be set to शून्यAGBLOCK
 * and 0, respectively.
 */
पूर्णांक
xfs_refcount_find_shared(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agblock_t			agbno,
	xfs_extlen_t			aglen,
	xfs_agblock_t			*fbno,
	xfs_extlen_t			*flen,
	bool				find_end_of_shared)
अणु
	काष्ठा xfs_refcount_irec	पंचांगp;
	पूर्णांक				i;
	पूर्णांक				have;
	पूर्णांक				error;

	trace_xfs_refcount_find_shared(cur->bc_mp, cur->bc_ag.agno,
			agbno, aglen);

	/* By शेष, skip the whole range */
	*fbno = शून्यAGBLOCK;
	*flen = 0;

	/* Try to find a refcount extent that crosses the start */
	error = xfs_refcount_lookup_le(cur, agbno, &have);
	अगर (error)
		जाओ out_error;
	अगर (!have) अणु
		/* No left extent, look at the next one */
		error = xfs_btree_increment(cur, 0, &have);
		अगर (error)
			जाओ out_error;
		अगर (!have)
			जाओ करोne;
	पूर्ण
	error = xfs_refcount_get_rec(cur, &पंचांगp, &i);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	/* If the extent ends beक्रमe the start, look at the next one */
	अगर (पंचांगp.rc_startblock + पंचांगp.rc_blockcount <= agbno) अणु
		error = xfs_btree_increment(cur, 0, &have);
		अगर (error)
			जाओ out_error;
		अगर (!have)
			जाओ करोne;
		error = xfs_refcount_get_rec(cur, &पंचांगp, &i);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
	पूर्ण

	/* If the extent starts after the range we want, bail out */
	अगर (पंचांगp.rc_startblock >= agbno + aglen)
		जाओ करोne;

	/* We found the start of a shared extent! */
	अगर (पंचांगp.rc_startblock < agbno) अणु
		पंचांगp.rc_blockcount -= (agbno - पंचांगp.rc_startblock);
		पंचांगp.rc_startblock = agbno;
	पूर्ण

	*fbno = पंचांगp.rc_startblock;
	*flen = min(पंचांगp.rc_blockcount, agbno + aglen - *fbno);
	अगर (!find_end_of_shared)
		जाओ करोne;

	/* Otherwise, find the end of this shared extent */
	जबतक (*fbno + *flen < agbno + aglen) अणु
		error = xfs_btree_increment(cur, 0, &have);
		अगर (error)
			जाओ out_error;
		अगर (!have)
			अवरोध;
		error = xfs_refcount_get_rec(cur, &पंचांगp, &i);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		अगर (पंचांगp.rc_startblock >= agbno + aglen ||
		    पंचांगp.rc_startblock != *fbno + *flen)
			अवरोध;
		*flen = min(*flen + पंचांगp.rc_blockcount, agbno + aglen - *fbno);
	पूर्ण

करोne:
	trace_xfs_refcount_find_shared_result(cur->bc_mp,
			cur->bc_ag.agno, *fbno, *flen);

out_error:
	अगर (error)
		trace_xfs_refcount_find_shared_error(cur->bc_mp,
				cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Recovering CoW Blocks After a Crash
 *
 * Due to the way that the copy on ग_लिखो mechanism works, there's a winकरोw of
 * opportunity in which we can lose track of allocated blocks during a crash.
 * Because CoW uses delayed allocation in the in-core CoW विभाजन, ग_लिखोback
 * causes blocks to be allocated and stored in the CoW विभाजन.  The blocks are
 * no दीर्घer in the मुक्त space btree but are not otherwise recorded anywhere
 * until the ग_लिखो completes and the blocks are mapped पूर्णांकo the file.  A crash
 * in between allocation and remapping results in the replacement blocks being
 * lost.  This situation is exacerbated by the CoW extent size hपूर्णांक because
 * allocations can hang around क्रम दीर्घ समय.
 *
 * However, there is a place where we can record these allocations beक्रमe they
 * become mappings -- the reference count btree.  The btree करोes not record
 * extents with refcount == 1, so we can record allocations with a refcount of
 * 1.  Blocks being used क्रम CoW ग_लिखोout cannot be shared, so there should be
 * no conflict with shared block records.  These mappings should be created
 * when we allocate blocks to the CoW विभाजन and deleted when they're हटाओd
 * from the CoW विभाजन.
 *
 * Minor nit: records क्रम in-progress CoW allocations and records क्रम shared
 * extents must never be merged, to preserve the property that (except क्रम CoW
 * allocations) there are no refcount btree entries with refcount == 1.  The
 * only समय this could potentially happen is when unsharing a block that's
 * adjacent to CoW allocations, so we must be careful to aव्योम this.
 *
 * At mount समय we recover lost CoW allocations by searching the refcount
 * btree क्रम these refcount == 1 mappings.  These represent CoW allocations
 * that were in progress at the समय the fileप्रणाली went करोwn, so we can मुक्त
 * them to get the space back.
 *
 * This mechanism is superior to creating EFIs क्रम unmapped CoW extents क्रम
 * several reasons -- first, EFIs pin the tail of the log and would have to be
 * periodically relogged to aव्योम filling up the log.  Second, CoW completions
 * will have to file an EFD and create new EFIs क्रम whatever reमुख्यs in the
 * CoW विभाजन; this partially takes care of (1) but extent-size reservations
 * will have to periodically relog even अगर there's no ग_लिखोout in progress.
 * This can happen अगर the CoW extent size hपूर्णांक is set, which you really want.
 * Third, EFIs cannot currently be स्वतःmatically relogged पूर्णांकo newer
 * transactions to advance the log tail.  Fourth, stuffing the log full of
 * EFIs places an upper bound on the number of CoW allocations that can be
 * held fileप्रणाली-wide at any given समय.  Recording them in the refcount
 * btree करोesn't require us to maintain any state in memory and doesn't pin
 * the log.
 */
/*
 * Adjust the refcounts of CoW allocations.  These allocations are "magic"
 * in that they're not referenced anywhere अन्यथा in the fileप्रणाली, so we
 * stash them in the refcount btree with a refcount of 1 until either file
 * remapping (or CoW cancellation) happens.
 */
STATIC पूर्णांक
xfs_refcount_adjust_cow_extents(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		agbno,
	xfs_extlen_t		aglen,
	क्रमागत xfs_refc_adjust_op	adj)
अणु
	काष्ठा xfs_refcount_irec	ext, पंचांगp;
	पूर्णांक				error;
	पूर्णांक				found_rec, found_पंचांगp;

	अगर (aglen == 0)
		वापस 0;

	/* Find any overlapping refcount records */
	error = xfs_refcount_lookup_ge(cur, agbno, &found_rec);
	अगर (error)
		जाओ out_error;
	error = xfs_refcount_get_rec(cur, &ext, &found_rec);
	अगर (error)
		जाओ out_error;
	अगर (!found_rec) अणु
		ext.rc_startblock = cur->bc_mp->m_sb.sb_agblocks +
				XFS_REFC_COW_START;
		ext.rc_blockcount = 0;
		ext.rc_refcount = 0;
	पूर्ण

	चयन (adj) अणु
	हाल XFS_REFCOUNT_ADJUST_COW_ALLOC:
		/* Adding a CoW reservation, there should be nothing here. */
		अगर (XFS_IS_CORRUPT(cur->bc_mp,
				   agbno + aglen > ext.rc_startblock)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण

		पंचांगp.rc_startblock = agbno;
		पंचांगp.rc_blockcount = aglen;
		पंचांगp.rc_refcount = 1;
		trace_xfs_refcount_modअगरy_extent(cur->bc_mp,
				cur->bc_ag.agno, &पंचांगp);

		error = xfs_refcount_insert(cur, &पंचांगp,
				&found_पंचांगp);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, found_पंचांगp != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		अवरोध;
	हाल XFS_REFCOUNT_ADJUST_COW_FREE:
		/* Removing a CoW reservation, there should be one extent. */
		अगर (XFS_IS_CORRUPT(cur->bc_mp, ext.rc_startblock != agbno)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		अगर (XFS_IS_CORRUPT(cur->bc_mp, ext.rc_blockcount != aglen)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		अगर (XFS_IS_CORRUPT(cur->bc_mp, ext.rc_refcount != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण

		ext.rc_refcount = 0;
		trace_xfs_refcount_modअगरy_extent(cur->bc_mp,
				cur->bc_ag.agno, &ext);
		error = xfs_refcount_delete(cur, &found_rec);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, found_rec != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		अवरोध;
	शेष:
		ASSERT(0);
	पूर्ण

	वापस error;
out_error:
	trace_xfs_refcount_modअगरy_extent_error(cur->bc_mp,
			cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Add or हटाओ refcount btree entries क्रम CoW reservations.
 */
STATIC पूर्णांक
xfs_refcount_adjust_cow(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		agbno,
	xfs_extlen_t		aglen,
	क्रमागत xfs_refc_adjust_op	adj)
अणु
	bool			shape_changed;
	पूर्णांक			error;

	agbno += XFS_REFC_COW_START;

	/*
	 * Ensure that no rcextents cross the boundary of the adjusपंचांगent range.
	 */
	error = xfs_refcount_split_extent(cur, agbno, &shape_changed);
	अगर (error)
		जाओ out_error;

	error = xfs_refcount_split_extent(cur, agbno + aglen, &shape_changed);
	अगर (error)
		जाओ out_error;

	/*
	 * Try to merge with the left or right extents of the range.
	 */
	error = xfs_refcount_merge_extents(cur, &agbno, &aglen, adj,
			XFS_FIND_RCEXT_COW, &shape_changed);
	अगर (error)
		जाओ out_error;

	/* Now that we've taken care of the ends, adjust the middle extents */
	error = xfs_refcount_adjust_cow_extents(cur, agbno, aglen, adj);
	अगर (error)
		जाओ out_error;

	वापस 0;

out_error:
	trace_xfs_refcount_adjust_cow_error(cur->bc_mp, cur->bc_ag.agno,
			error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Record a CoW allocation in the refcount btree.
 */
STATIC पूर्णांक
__xfs_refcount_cow_alloc(
	काष्ठा xfs_btree_cur	*rcur,
	xfs_agblock_t		agbno,
	xfs_extlen_t		aglen)
अणु
	trace_xfs_refcount_cow_increase(rcur->bc_mp, rcur->bc_ag.agno,
			agbno, aglen);

	/* Add refcount btree reservation */
	वापस xfs_refcount_adjust_cow(rcur, agbno, aglen,
			XFS_REFCOUNT_ADJUST_COW_ALLOC);
पूर्ण

/*
 * Remove a CoW allocation from the refcount btree.
 */
STATIC पूर्णांक
__xfs_refcount_cow_मुक्त(
	काष्ठा xfs_btree_cur	*rcur,
	xfs_agblock_t		agbno,
	xfs_extlen_t		aglen)
अणु
	trace_xfs_refcount_cow_decrease(rcur->bc_mp, rcur->bc_ag.agno,
			agbno, aglen);

	/* Remove refcount btree reservation */
	वापस xfs_refcount_adjust_cow(rcur, agbno, aglen,
			XFS_REFCOUNT_ADJUST_COW_FREE);
पूर्ण

/* Record a CoW staging extent in the refcount btree. */
व्योम
xfs_refcount_alloc_cow_extent(
	काष्ठा xfs_trans		*tp,
	xfs_fsblock_t			fsb,
	xfs_extlen_t			len)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;

	अगर (!xfs_sb_version_hasreflink(&mp->m_sb))
		वापस;

	__xfs_refcount_add(tp, XFS_REFCOUNT_ALLOC_COW, fsb, len);

	/* Add rmap entry */
	xfs_rmap_alloc_extent(tp, XFS_FSB_TO_AGNO(mp, fsb),
			XFS_FSB_TO_AGBNO(mp, fsb), len, XFS_RMAP_OWN_COW);
पूर्ण

/* Forget a CoW staging event in the refcount btree. */
व्योम
xfs_refcount_मुक्त_cow_extent(
	काष्ठा xfs_trans		*tp,
	xfs_fsblock_t			fsb,
	xfs_extlen_t			len)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;

	अगर (!xfs_sb_version_hasreflink(&mp->m_sb))
		वापस;

	/* Remove rmap entry */
	xfs_rmap_मुक्त_extent(tp, XFS_FSB_TO_AGNO(mp, fsb),
			XFS_FSB_TO_AGBNO(mp, fsb), len, XFS_RMAP_OWN_COW);
	__xfs_refcount_add(tp, XFS_REFCOUNT_FREE_COW, fsb, len);
पूर्ण

काष्ठा xfs_refcount_recovery अणु
	काष्ठा list_head		rr_list;
	काष्ठा xfs_refcount_irec	rr_rrec;
पूर्ण;

/* Stuff an extent on the recovery list. */
STATIC पूर्णांक
xfs_refcount_recover_extent(
	काष्ठा xfs_btree_cur		*cur,
	जोड़ xfs_btree_rec		*rec,
	व्योम				*priv)
अणु
	काष्ठा list_head		*debris = priv;
	काष्ठा xfs_refcount_recovery	*rr;

	अगर (XFS_IS_CORRUPT(cur->bc_mp,
			   be32_to_cpu(rec->refc.rc_refcount) != 1))
		वापस -EFSCORRUPTED;

	rr = kmem_alloc(माप(काष्ठा xfs_refcount_recovery), 0);
	xfs_refcount_btrec_to_irec(rec, &rr->rr_rrec);
	list_add_tail(&rr->rr_list, debris);

	वापस 0;
पूर्ण

/* Find and हटाओ leftover CoW reservations. */
पूर्णांक
xfs_refcount_recover_cow_leftovers(
	काष्ठा xfs_mount		*mp,
	xfs_agnumber_t			agno)
अणु
	काष्ठा xfs_trans		*tp;
	काष्ठा xfs_btree_cur		*cur;
	काष्ठा xfs_buf			*agbp;
	काष्ठा xfs_refcount_recovery	*rr, *n;
	काष्ठा list_head		debris;
	जोड़ xfs_btree_irec		low;
	जोड़ xfs_btree_irec		high;
	xfs_fsblock_t			fsb;
	xfs_agblock_t			agbno;
	पूर्णांक				error;

	अगर (mp->m_sb.sb_agblocks >= XFS_REFC_COW_START)
		वापस -EOPNOTSUPP;

	INIT_LIST_HEAD(&debris);

	/*
	 * In this first part, we use an empty transaction to gather up
	 * all the leftover CoW extents so that we can subsequently
	 * delete them.  The empty transaction is used to aव्योम
	 * a buffer lock deadlock अगर there happens to be a loop in the
	 * refcountbt because we're allowed to re-grab a buffer that is
	 * alपढ़ोy attached to our transaction.  When we're करोne
	 * recording the CoW debris we cancel the (empty) transaction
	 * and everything goes away cleanly.
	 */
	error = xfs_trans_alloc_empty(mp, &tp);
	अगर (error)
		वापस error;

	error = xfs_alloc_पढ़ो_agf(mp, tp, agno, 0, &agbp);
	अगर (error)
		जाओ out_trans;
	cur = xfs_refcountbt_init_cursor(mp, tp, agbp, agno);

	/* Find all the leftover CoW staging extents. */
	स_रखो(&low, 0, माप(low));
	स_रखो(&high, 0, माप(high));
	low.rc.rc_startblock = XFS_REFC_COW_START;
	high.rc.rc_startblock = -1U;
	error = xfs_btree_query_range(cur, &low, &high,
			xfs_refcount_recover_extent, &debris);
	xfs_btree_del_cursor(cur, error);
	xfs_trans_brअन्यथा(tp, agbp);
	xfs_trans_cancel(tp);
	अगर (error)
		जाओ out_मुक्त;

	/* Now iterate the list to मुक्त the leftovers */
	list_क्रम_each_entry_safe(rr, n, &debris, rr_list) अणु
		/* Set up transaction. */
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ग_लिखो, 0, 0, 0, &tp);
		अगर (error)
			जाओ out_मुक्त;

		trace_xfs_refcount_recover_extent(mp, agno, &rr->rr_rrec);

		/* Free the orphan record */
		agbno = rr->rr_rrec.rc_startblock - XFS_REFC_COW_START;
		fsb = XFS_AGB_TO_FSB(mp, agno, agbno);
		xfs_refcount_मुक्त_cow_extent(tp, fsb,
				rr->rr_rrec.rc_blockcount);

		/* Free the block. */
		xfs_bmap_add_मुक्त(tp, fsb, rr->rr_rrec.rc_blockcount, शून्य);

		error = xfs_trans_commit(tp);
		अगर (error)
			जाओ out_मुक्त;

		list_del(&rr->rr_list);
		kmem_मुक्त(rr);
	पूर्ण

	वापस error;
out_trans:
	xfs_trans_cancel(tp);
out_मुक्त:
	/* Free the leftover list */
	list_क्रम_each_entry_safe(rr, n, &debris, rr_list) अणु
		list_del(&rr->rr_list);
		kmem_मुक्त(rr);
	पूर्ण
	वापस error;
पूर्ण

/* Is there a record covering a given extent? */
पूर्णांक
xfs_refcount_has_record(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	xfs_extlen_t		len,
	bool			*exists)
अणु
	जोड़ xfs_btree_irec	low;
	जोड़ xfs_btree_irec	high;

	स_रखो(&low, 0, माप(low));
	low.rc.rc_startblock = bno;
	स_रखो(&high, 0xFF, माप(high));
	high.rc.rc_startblock = bno + len - 1;

	वापस xfs_btree_has_record(cur, &low, &high, exists);
पूर्ण
