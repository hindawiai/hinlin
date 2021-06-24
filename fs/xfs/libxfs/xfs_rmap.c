<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Red Hat, Inc.
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
#समावेश "xfs_defer.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_inode.h"

/*
 * Lookup the first record less than or equal to [bno, len, owner, offset]
 * in the btree given by cur.
 */
पूर्णांक
xfs_rmap_lookup_le(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	xfs_extlen_t		len,
	uपूर्णांक64_t		owner,
	uपूर्णांक64_t		offset,
	अचिन्हित पूर्णांक		flags,
	पूर्णांक			*stat)
अणु
	cur->bc_rec.r.rm_startblock = bno;
	cur->bc_rec.r.rm_blockcount = len;
	cur->bc_rec.r.rm_owner = owner;
	cur->bc_rec.r.rm_offset = offset;
	cur->bc_rec.r.rm_flags = flags;
	वापस xfs_btree_lookup(cur, XFS_LOOKUP_LE, stat);
पूर्ण

/*
 * Lookup the record exactly matching [bno, len, owner, offset]
 * in the btree given by cur.
 */
पूर्णांक
xfs_rmap_lookup_eq(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	xfs_extlen_t		len,
	uपूर्णांक64_t		owner,
	uपूर्णांक64_t		offset,
	अचिन्हित पूर्णांक		flags,
	पूर्णांक			*stat)
अणु
	cur->bc_rec.r.rm_startblock = bno;
	cur->bc_rec.r.rm_blockcount = len;
	cur->bc_rec.r.rm_owner = owner;
	cur->bc_rec.r.rm_offset = offset;
	cur->bc_rec.r.rm_flags = flags;
	वापस xfs_btree_lookup(cur, XFS_LOOKUP_EQ, stat);
पूर्ण

/*
 * Update the record referred to by cur to the value given
 * by [bno, len, owner, offset].
 * This either works (वापस 0) or माला_लो an EFSCORRUPTED error.
 */
STATIC पूर्णांक
xfs_rmap_update(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_rmap_irec	*irec)
अणु
	जोड़ xfs_btree_rec	rec;
	पूर्णांक			error;

	trace_xfs_rmap_update(cur->bc_mp, cur->bc_ag.agno,
			irec->rm_startblock, irec->rm_blockcount,
			irec->rm_owner, irec->rm_offset, irec->rm_flags);

	rec.rmap.rm_startblock = cpu_to_be32(irec->rm_startblock);
	rec.rmap.rm_blockcount = cpu_to_be32(irec->rm_blockcount);
	rec.rmap.rm_owner = cpu_to_be64(irec->rm_owner);
	rec.rmap.rm_offset = cpu_to_be64(
			xfs_rmap_irec_offset_pack(irec));
	error = xfs_btree_update(cur, &rec);
	अगर (error)
		trace_xfs_rmap_update_error(cur->bc_mp,
				cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

पूर्णांक
xfs_rmap_insert(
	काष्ठा xfs_btree_cur	*rcur,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len,
	uपूर्णांक64_t		owner,
	uपूर्णांक64_t		offset,
	अचिन्हित पूर्णांक		flags)
अणु
	पूर्णांक			i;
	पूर्णांक			error;

	trace_xfs_rmap_insert(rcur->bc_mp, rcur->bc_ag.agno, agbno,
			len, owner, offset, flags);

	error = xfs_rmap_lookup_eq(rcur, agbno, len, owner, offset, flags, &i);
	अगर (error)
		जाओ करोne;
	अगर (XFS_IS_CORRUPT(rcur->bc_mp, i != 0)) अणु
		error = -EFSCORRUPTED;
		जाओ करोne;
	पूर्ण

	rcur->bc_rec.r.rm_startblock = agbno;
	rcur->bc_rec.r.rm_blockcount = len;
	rcur->bc_rec.r.rm_owner = owner;
	rcur->bc_rec.r.rm_offset = offset;
	rcur->bc_rec.r.rm_flags = flags;
	error = xfs_btree_insert(rcur, &i);
	अगर (error)
		जाओ करोne;
	अगर (XFS_IS_CORRUPT(rcur->bc_mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ करोne;
	पूर्ण
करोne:
	अगर (error)
		trace_xfs_rmap_insert_error(rcur->bc_mp,
				rcur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_rmap_delete(
	काष्ठा xfs_btree_cur	*rcur,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len,
	uपूर्णांक64_t		owner,
	uपूर्णांक64_t		offset,
	अचिन्हित पूर्णांक		flags)
अणु
	पूर्णांक			i;
	पूर्णांक			error;

	trace_xfs_rmap_delete(rcur->bc_mp, rcur->bc_ag.agno, agbno,
			len, owner, offset, flags);

	error = xfs_rmap_lookup_eq(rcur, agbno, len, owner, offset, flags, &i);
	अगर (error)
		जाओ करोne;
	अगर (XFS_IS_CORRUPT(rcur->bc_mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ करोne;
	पूर्ण

	error = xfs_btree_delete(rcur, &i);
	अगर (error)
		जाओ करोne;
	अगर (XFS_IS_CORRUPT(rcur->bc_mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ करोne;
	पूर्ण
करोne:
	अगर (error)
		trace_xfs_rmap_delete_error(rcur->bc_mp,
				rcur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/* Convert an पूर्णांकernal btree record to an rmap record. */
पूर्णांक
xfs_rmap_btrec_to_irec(
	जोड़ xfs_btree_rec	*rec,
	काष्ठा xfs_rmap_irec	*irec)
अणु
	irec->rm_startblock = be32_to_cpu(rec->rmap.rm_startblock);
	irec->rm_blockcount = be32_to_cpu(rec->rmap.rm_blockcount);
	irec->rm_owner = be64_to_cpu(rec->rmap.rm_owner);
	वापस xfs_rmap_irec_offset_unpack(be64_to_cpu(rec->rmap.rm_offset),
			irec);
पूर्ण

/*
 * Get the data from the poपूर्णांकed-to record.
 */
पूर्णांक
xfs_rmap_get_rec(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_rmap_irec	*irec,
	पूर्णांक			*stat)
अणु
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	xfs_agnumber_t		agno = cur->bc_ag.agno;
	जोड़ xfs_btree_rec	*rec;
	पूर्णांक			error;

	error = xfs_btree_get_rec(cur, &rec, stat);
	अगर (error || !*stat)
		वापस error;

	अगर (xfs_rmap_btrec_to_irec(rec, irec))
		जाओ out_bad_rec;

	अगर (irec->rm_blockcount == 0)
		जाओ out_bad_rec;
	अगर (irec->rm_startblock <= XFS_AGFL_BLOCK(mp)) अणु
		अगर (irec->rm_owner != XFS_RMAP_OWN_FS)
			जाओ out_bad_rec;
		अगर (irec->rm_blockcount != XFS_AGFL_BLOCK(mp) + 1)
			जाओ out_bad_rec;
	पूर्ण अन्यथा अणु
		/* check क्रम valid extent range, including overflow */
		अगर (!xfs_verअगरy_agbno(mp, agno, irec->rm_startblock))
			जाओ out_bad_rec;
		अगर (irec->rm_startblock >
				irec->rm_startblock + irec->rm_blockcount)
			जाओ out_bad_rec;
		अगर (!xfs_verअगरy_agbno(mp, agno,
				irec->rm_startblock + irec->rm_blockcount - 1))
			जाओ out_bad_rec;
	पूर्ण

	अगर (!(xfs_verअगरy_ino(mp, irec->rm_owner) ||
	      (irec->rm_owner <= XFS_RMAP_OWN_FS &&
	       irec->rm_owner >= XFS_RMAP_OWN_MIN)))
		जाओ out_bad_rec;

	वापस 0;
out_bad_rec:
	xfs_warn(mp,
		"Reverse Mapping BTree record corruption in AG %d detected!",
		agno);
	xfs_warn(mp,
		"Owner 0x%llx, flags 0x%x, start block 0x%x block count 0x%x",
		irec->rm_owner, irec->rm_flags, irec->rm_startblock,
		irec->rm_blockcount);
	वापस -EFSCORRUPTED;
पूर्ण

काष्ठा xfs_find_left_neighbor_info अणु
	काष्ठा xfs_rmap_irec	high;
	काष्ठा xfs_rmap_irec	*irec;
	पूर्णांक			*stat;
पूर्ण;

/* For each rmap given, figure out अगर it matches the key we want. */
STATIC पूर्णांक
xfs_rmap_find_left_neighbor_helper(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_rmap_irec	*rec,
	व्योम			*priv)
अणु
	काष्ठा xfs_find_left_neighbor_info	*info = priv;

	trace_xfs_rmap_find_left_neighbor_candidate(cur->bc_mp,
			cur->bc_ag.agno, rec->rm_startblock,
			rec->rm_blockcount, rec->rm_owner, rec->rm_offset,
			rec->rm_flags);

	अगर (rec->rm_owner != info->high.rm_owner)
		वापस 0;
	अगर (!XFS_RMAP_NON_INODE_OWNER(rec->rm_owner) &&
	    !(rec->rm_flags & XFS_RMAP_BMBT_BLOCK) &&
	    rec->rm_offset + rec->rm_blockcount - 1 != info->high.rm_offset)
		वापस 0;

	*info->irec = *rec;
	*info->stat = 1;
	वापस -ECANCELED;
पूर्ण

/*
 * Find the record to the left of the given extent, being careful only to
 * वापस a match with the same owner and adjacent physical and logical
 * block ranges.
 */
पूर्णांक
xfs_rmap_find_left_neighbor(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	uपूर्णांक64_t		owner,
	uपूर्णांक64_t		offset,
	अचिन्हित पूर्णांक		flags,
	काष्ठा xfs_rmap_irec	*irec,
	पूर्णांक			*stat)
अणु
	काष्ठा xfs_find_left_neighbor_info	info;
	पूर्णांक			error;

	*stat = 0;
	अगर (bno == 0)
		वापस 0;
	info.high.rm_startblock = bno - 1;
	info.high.rm_owner = owner;
	अगर (!XFS_RMAP_NON_INODE_OWNER(owner) &&
	    !(flags & XFS_RMAP_BMBT_BLOCK)) अणु
		अगर (offset == 0)
			वापस 0;
		info.high.rm_offset = offset - 1;
	पूर्ण अन्यथा
		info.high.rm_offset = 0;
	info.high.rm_flags = flags;
	info.high.rm_blockcount = 0;
	info.irec = irec;
	info.stat = stat;

	trace_xfs_rmap_find_left_neighbor_query(cur->bc_mp,
			cur->bc_ag.agno, bno, 0, owner, offset, flags);

	error = xfs_rmap_query_range(cur, &info.high, &info.high,
			xfs_rmap_find_left_neighbor_helper, &info);
	अगर (error == -ECANCELED)
		error = 0;
	अगर (*stat)
		trace_xfs_rmap_find_left_neighbor_result(cur->bc_mp,
				cur->bc_ag.agno, irec->rm_startblock,
				irec->rm_blockcount, irec->rm_owner,
				irec->rm_offset, irec->rm_flags);
	वापस error;
पूर्ण

/* For each rmap given, figure out अगर it matches the key we want. */
STATIC पूर्णांक
xfs_rmap_lookup_le_range_helper(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_rmap_irec	*rec,
	व्योम			*priv)
अणु
	काष्ठा xfs_find_left_neighbor_info	*info = priv;

	trace_xfs_rmap_lookup_le_range_candidate(cur->bc_mp,
			cur->bc_ag.agno, rec->rm_startblock,
			rec->rm_blockcount, rec->rm_owner, rec->rm_offset,
			rec->rm_flags);

	अगर (rec->rm_owner != info->high.rm_owner)
		वापस 0;
	अगर (!XFS_RMAP_NON_INODE_OWNER(rec->rm_owner) &&
	    !(rec->rm_flags & XFS_RMAP_BMBT_BLOCK) &&
	    (rec->rm_offset > info->high.rm_offset ||
	     rec->rm_offset + rec->rm_blockcount <= info->high.rm_offset))
		वापस 0;

	*info->irec = *rec;
	*info->stat = 1;
	वापस -ECANCELED;
पूर्ण

/*
 * Find the record to the left of the given extent, being careful only to
 * वापस a match with the same owner and overlapping physical and logical
 * block ranges.  This is the overlapping-पूर्णांकerval version of
 * xfs_rmap_lookup_le.
 */
पूर्णांक
xfs_rmap_lookup_le_range(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	uपूर्णांक64_t		owner,
	uपूर्णांक64_t		offset,
	अचिन्हित पूर्णांक		flags,
	काष्ठा xfs_rmap_irec	*irec,
	पूर्णांक			*stat)
अणु
	काष्ठा xfs_find_left_neighbor_info	info;
	पूर्णांक			error;

	info.high.rm_startblock = bno;
	info.high.rm_owner = owner;
	अगर (!XFS_RMAP_NON_INODE_OWNER(owner) && !(flags & XFS_RMAP_BMBT_BLOCK))
		info.high.rm_offset = offset;
	अन्यथा
		info.high.rm_offset = 0;
	info.high.rm_flags = flags;
	info.high.rm_blockcount = 0;
	*stat = 0;
	info.irec = irec;
	info.stat = stat;

	trace_xfs_rmap_lookup_le_range(cur->bc_mp,
			cur->bc_ag.agno, bno, 0, owner, offset, flags);
	error = xfs_rmap_query_range(cur, &info.high, &info.high,
			xfs_rmap_lookup_le_range_helper, &info);
	अगर (error == -ECANCELED)
		error = 0;
	अगर (*stat)
		trace_xfs_rmap_lookup_le_range_result(cur->bc_mp,
				cur->bc_ag.agno, irec->rm_startblock,
				irec->rm_blockcount, irec->rm_owner,
				irec->rm_offset, irec->rm_flags);
	वापस error;
पूर्ण

/*
 * Perक्रमm all the relevant owner checks क्रम a removal op.  If we're करोing an
 * unknown-owner removal then we have no owner inक्रमmation to check.
 */
अटल पूर्णांक
xfs_rmap_मुक्त_check_owner(
	काष्ठा xfs_mount	*mp,
	uपूर्णांक64_t		ltoff,
	काष्ठा xfs_rmap_irec	*rec,
	xfs_filblks_t		len,
	uपूर्णांक64_t		owner,
	uपूर्णांक64_t		offset,
	अचिन्हित पूर्णांक		flags)
अणु
	पूर्णांक			error = 0;

	अगर (owner == XFS_RMAP_OWN_UNKNOWN)
		वापस 0;

	/* Make sure the unwritten flag matches. */
	अगर (XFS_IS_CORRUPT(mp,
			   (flags & XFS_RMAP_UNWRITTEN) !=
			   (rec->rm_flags & XFS_RMAP_UNWRITTEN))) अणु
		error = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	/* Make sure the owner matches what we expect to find in the tree. */
	अगर (XFS_IS_CORRUPT(mp, owner != rec->rm_owner)) अणु
		error = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	/* Check the offset, अगर necessary. */
	अगर (XFS_RMAP_NON_INODE_OWNER(owner))
		जाओ out;

	अगर (flags & XFS_RMAP_BMBT_BLOCK) अणु
		अगर (XFS_IS_CORRUPT(mp,
				   !(rec->rm_flags & XFS_RMAP_BMBT_BLOCK))) अणु
			error = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (XFS_IS_CORRUPT(mp, rec->rm_offset > offset)) अणु
			error = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
		अगर (XFS_IS_CORRUPT(mp,
				   offset + len > ltoff + rec->rm_blockcount)) अणु
			error = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस error;
पूर्ण

/*
 * Find the extent in the rmap btree and हटाओ it.
 *
 * The record we find should always be an exact match क्रम the extent that we're
 * looking क्रम, since we insert them पूर्णांकo the btree without modअगरication.
 *
 * Special Case #1: when growing the fileप्रणाली, we "free" an extent when
 * growing the last AG. This extent is new space and so it is not tracked as
 * used space in the btree. The growfs code will pass in an owner of
 * XFS_RMAP_OWN_शून्य to indicate that it expected that there is no owner of this
 * extent. We verअगरy that - the extent lookup result in a record that करोes not
 * overlap.
 *
 * Special Case #2: EFIs करो not record the owner of the extent, so when
 * recovering EFIs from the log we pass in XFS_RMAP_OWN_UNKNOWN to tell the rmap
 * btree to ignore the owner (i.e. wildcard match) so we करोn't trigger
 * corruption checks during log recovery.
 */
STATIC पूर्णांक
xfs_rmap_unmap(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	bool				unwritten,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	काष्ठा xfs_mount		*mp = cur->bc_mp;
	काष्ठा xfs_rmap_irec		ltrec;
	uपूर्णांक64_t			ltoff;
	पूर्णांक				error = 0;
	पूर्णांक				i;
	uपूर्णांक64_t			owner;
	uपूर्णांक64_t			offset;
	अचिन्हित पूर्णांक			flags;
	bool				ignore_off;

	xfs_owner_info_unpack(oinfo, &owner, &offset, &flags);
	ignore_off = XFS_RMAP_NON_INODE_OWNER(owner) ||
			(flags & XFS_RMAP_BMBT_BLOCK);
	अगर (unwritten)
		flags |= XFS_RMAP_UNWRITTEN;
	trace_xfs_rmap_unmap(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);

	/*
	 * We should always have a left record because there's a अटल record
	 * क्रम the AG headers at rm_startblock == 0 created by mkfs/growfs that
	 * will not ever be हटाओd from the tree.
	 */
	error = xfs_rmap_lookup_le(cur, bno, len, owner, offset, flags, &i);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	error = xfs_rmap_get_rec(cur, &ltrec, &i);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण
	trace_xfs_rmap_lookup_le_range_result(cur->bc_mp,
			cur->bc_ag.agno, ltrec.rm_startblock,
			ltrec.rm_blockcount, ltrec.rm_owner,
			ltrec.rm_offset, ltrec.rm_flags);
	ltoff = ltrec.rm_offset;

	/*
	 * For growfs, the incoming extent must be beyond the left record we
	 * just found as it is new space and won't be used by anyone. This is
	 * just a corruption check as we करोn't actually करो anything with this
	 * extent.  Note that we need to use >= instead of > because it might
	 * be the हाल that the "left" extent goes all the way to खातापूर्णS.
	 */
	अगर (owner == XFS_RMAP_OWN_शून्य) अणु
		अगर (XFS_IS_CORRUPT(mp,
				   bno <
				   ltrec.rm_startblock + ltrec.rm_blockcount)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		जाओ out_करोne;
	पूर्ण

	/*
	 * If we're करोing an unknown-owner removal क्रम EFI recovery, we expect
	 * to find the full range in the rmapbt or nothing at all.  If we
	 * करोn't find any rmaps overlapping either end of the range, we're
	 * करोne.  Hopefully this means that the EFI creator alपढ़ोy queued
	 * (and finished) a RUI to हटाओ the rmap.
	 */
	अगर (owner == XFS_RMAP_OWN_UNKNOWN &&
	    ltrec.rm_startblock + ltrec.rm_blockcount <= bno) अणु
		काष्ठा xfs_rmap_irec    rtrec;

		error = xfs_btree_increment(cur, 0, &i);
		अगर (error)
			जाओ out_error;
		अगर (i == 0)
			जाओ out_करोne;
		error = xfs_rmap_get_rec(cur, &rtrec, &i);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		अगर (rtrec.rm_startblock >= bno + len)
			जाओ out_करोne;
	पूर्ण

	/* Make sure the extent we found covers the entire मुक्तing range. */
	अगर (XFS_IS_CORRUPT(mp,
			   ltrec.rm_startblock > bno ||
			   ltrec.rm_startblock + ltrec.rm_blockcount <
			   bno + len)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	/* Check owner inक्रमmation. */
	error = xfs_rmap_मुक्त_check_owner(mp, ltoff, &ltrec, len, owner,
			offset, flags);
	अगर (error)
		जाओ out_error;

	अगर (ltrec.rm_startblock == bno && ltrec.rm_blockcount == len) अणु
		/* exact match, simply हटाओ the record from rmap tree */
		trace_xfs_rmap_delete(mp, cur->bc_ag.agno,
				ltrec.rm_startblock, ltrec.rm_blockcount,
				ltrec.rm_owner, ltrec.rm_offset,
				ltrec.rm_flags);
		error = xfs_btree_delete(cur, &i);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
	पूर्ण अन्यथा अगर (ltrec.rm_startblock == bno) अणु
		/*
		 * overlap left hand side of extent: move the start, trim the
		 * length and update the current record.
		 *
		 *       ltbno                ltlen
		 * Orig:    |oooooooooooooooooooo|
		 * Freeing: |fffffffff|
		 * Result:            |rrrrrrrrrr|
		 *         bno       len
		 */
		ltrec.rm_startblock += len;
		ltrec.rm_blockcount -= len;
		अगर (!ignore_off)
			ltrec.rm_offset += len;
		error = xfs_rmap_update(cur, &ltrec);
		अगर (error)
			जाओ out_error;
	पूर्ण अन्यथा अगर (ltrec.rm_startblock + ltrec.rm_blockcount == bno + len) अणु
		/*
		 * overlap right hand side of extent: trim the length and update
		 * the current record.
		 *
		 *       ltbno                ltlen
		 * Orig:    |oooooooooooooooooooo|
		 * Freeing:            |fffffffff|
		 * Result:  |rrrrrrrrrr|
		 *                    bno       len
		 */
		ltrec.rm_blockcount -= len;
		error = xfs_rmap_update(cur, &ltrec);
		अगर (error)
			जाओ out_error;
	पूर्ण अन्यथा अणु

		/*
		 * overlap middle of extent: trim the length of the existing
		 * record to the length of the new left-extent size, increment
		 * the insertion position so we can insert a new record
		 * containing the reमुख्यing right-extent space.
		 *
		 *       ltbno                ltlen
		 * Orig:    |oooooooooooooooooooo|
		 * Freeing:       |fffffffff|
		 * Result:  |rrrrr|         |rrrr|
		 *               bno       len
		 */
		xfs_extlen_t	orig_len = ltrec.rm_blockcount;

		ltrec.rm_blockcount = bno - ltrec.rm_startblock;
		error = xfs_rmap_update(cur, &ltrec);
		अगर (error)
			जाओ out_error;

		error = xfs_btree_increment(cur, 0, &i);
		अगर (error)
			जाओ out_error;

		cur->bc_rec.r.rm_startblock = bno + len;
		cur->bc_rec.r.rm_blockcount = orig_len - len -
						     ltrec.rm_blockcount;
		cur->bc_rec.r.rm_owner = ltrec.rm_owner;
		अगर (ignore_off)
			cur->bc_rec.r.rm_offset = 0;
		अन्यथा
			cur->bc_rec.r.rm_offset = offset + len;
		cur->bc_rec.r.rm_flags = flags;
		trace_xfs_rmap_insert(mp, cur->bc_ag.agno,
				cur->bc_rec.r.rm_startblock,
				cur->bc_rec.r.rm_blockcount,
				cur->bc_rec.r.rm_owner,
				cur->bc_rec.r.rm_offset,
				cur->bc_rec.r.rm_flags);
		error = xfs_btree_insert(cur, &i);
		अगर (error)
			जाओ out_error;
	पूर्ण

out_करोne:
	trace_xfs_rmap_unmap_करोne(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);
out_error:
	अगर (error)
		trace_xfs_rmap_unmap_error(mp, cur->bc_ag.agno,
				error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Remove a reference to an extent in the rmap btree.
 */
पूर्णांक
xfs_rmap_मुक्त(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_buf			*agbp,
	xfs_agnumber_t			agno,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_btree_cur		*cur;
	पूर्णांक				error;

	अगर (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस 0;

	cur = xfs_rmapbt_init_cursor(mp, tp, agbp, agno);

	error = xfs_rmap_unmap(cur, bno, len, false, oinfo);

	xfs_btree_del_cursor(cur, error);
	वापस error;
पूर्ण

/*
 * A mergeable rmap must have the same owner and the same values क्रम
 * the unwritten, attr_विभाजन, and bmbt flags.  The startblock and
 * offset are checked separately.
 */
अटल bool
xfs_rmap_is_mergeable(
	काष्ठा xfs_rmap_irec	*irec,
	uपूर्णांक64_t		owner,
	अचिन्हित पूर्णांक		flags)
अणु
	अगर (irec->rm_owner == XFS_RMAP_OWN_शून्य)
		वापस false;
	अगर (irec->rm_owner != owner)
		वापस false;
	अगर ((flags & XFS_RMAP_UNWRITTEN) ^
	    (irec->rm_flags & XFS_RMAP_UNWRITTEN))
		वापस false;
	अगर ((flags & XFS_RMAP_ATTR_FORK) ^
	    (irec->rm_flags & XFS_RMAP_ATTR_FORK))
		वापस false;
	अगर ((flags & XFS_RMAP_BMBT_BLOCK) ^
	    (irec->rm_flags & XFS_RMAP_BMBT_BLOCK))
		वापस false;
	वापस true;
पूर्ण

/*
 * When we allocate a new block, the first thing we करो is add a reference to
 * the extent in the rmap btree. This takes the क्रमm of a [agbno, length,
 * owner, offset] record.  Flags are encoded in the high bits of the offset
 * field.
 */
STATIC पूर्णांक
xfs_rmap_map(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	bool				unwritten,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	काष्ठा xfs_mount		*mp = cur->bc_mp;
	काष्ठा xfs_rmap_irec		ltrec;
	काष्ठा xfs_rmap_irec		gtrec;
	पूर्णांक				have_gt;
	पूर्णांक				have_lt;
	पूर्णांक				error = 0;
	पूर्णांक				i;
	uपूर्णांक64_t			owner;
	uपूर्णांक64_t			offset;
	अचिन्हित पूर्णांक			flags = 0;
	bool				ignore_off;

	xfs_owner_info_unpack(oinfo, &owner, &offset, &flags);
	ASSERT(owner != 0);
	ignore_off = XFS_RMAP_NON_INODE_OWNER(owner) ||
			(flags & XFS_RMAP_BMBT_BLOCK);
	अगर (unwritten)
		flags |= XFS_RMAP_UNWRITTEN;
	trace_xfs_rmap_map(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);
	ASSERT(!xfs_rmap_should_skip_owner_update(oinfo));

	/*
	 * For the initial lookup, look क्रम an exact match or the left-adjacent
	 * record क्रम our insertion poपूर्णांक. This will also give us the record क्रम
	 * start block contiguity tests.
	 */
	error = xfs_rmap_lookup_le(cur, bno, len, owner, offset, flags,
			&have_lt);
	अगर (error)
		जाओ out_error;
	अगर (have_lt) अणु
		error = xfs_rmap_get_rec(cur, &ltrec, &have_lt);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(mp, have_lt != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		trace_xfs_rmap_lookup_le_range_result(cur->bc_mp,
				cur->bc_ag.agno, ltrec.rm_startblock,
				ltrec.rm_blockcount, ltrec.rm_owner,
				ltrec.rm_offset, ltrec.rm_flags);

		अगर (!xfs_rmap_is_mergeable(&ltrec, owner, flags))
			have_lt = 0;
	पूर्ण

	अगर (XFS_IS_CORRUPT(mp,
			   have_lt != 0 &&
			   ltrec.rm_startblock + ltrec.rm_blockcount > bno)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	/*
	 * Increment the cursor to see अगर we have a right-adjacent record to our
	 * insertion poपूर्णांक. This will give us the record क्रम end block
	 * contiguity tests.
	 */
	error = xfs_btree_increment(cur, 0, &have_gt);
	अगर (error)
		जाओ out_error;
	अगर (have_gt) अणु
		error = xfs_rmap_get_rec(cur, &gtrec, &have_gt);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(mp, have_gt != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		अगर (XFS_IS_CORRUPT(mp, bno + len > gtrec.rm_startblock)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		trace_xfs_rmap_find_right_neighbor_result(cur->bc_mp,
			cur->bc_ag.agno, gtrec.rm_startblock,
			gtrec.rm_blockcount, gtrec.rm_owner,
			gtrec.rm_offset, gtrec.rm_flags);
		अगर (!xfs_rmap_is_mergeable(&gtrec, owner, flags))
			have_gt = 0;
	पूर्ण

	/*
	 * Note: cursor currently poपूर्णांकs one record to the right of ltrec, even
	 * अगर there is no record in the tree to the right.
	 */
	अगर (have_lt &&
	    ltrec.rm_startblock + ltrec.rm_blockcount == bno &&
	    (ignore_off || ltrec.rm_offset + ltrec.rm_blockcount == offset)) अणु
		/*
		 * left edge contiguous, merge पूर्णांकo left record.
		 *
		 *       ltbno     ltlen
		 * orig:   |ooooooooo|
		 * adding:           |aaaaaaaaa|
		 * result: |rrrrrrrrrrrrrrrrrrr|
		 *                  bno       len
		 */
		ltrec.rm_blockcount += len;
		अगर (have_gt &&
		    bno + len == gtrec.rm_startblock &&
		    (ignore_off || offset + len == gtrec.rm_offset) &&
		    (अचिन्हित दीर्घ)ltrec.rm_blockcount + len +
				gtrec.rm_blockcount <= XFS_RMAP_LEN_MAX) अणु
			/*
			 * right edge also contiguous, delete right record
			 * and merge पूर्णांकo left record.
			 *
			 *       ltbno     ltlen    gtbno     gtlen
			 * orig:   |ooooooooo|         |ooooooooo|
			 * adding:           |aaaaaaaaa|
			 * result: |rrrrrrrrrrrrrrrrrrrrrrrrrrrrr|
			 */
			ltrec.rm_blockcount += gtrec.rm_blockcount;
			trace_xfs_rmap_delete(mp, cur->bc_ag.agno,
					gtrec.rm_startblock,
					gtrec.rm_blockcount,
					gtrec.rm_owner,
					gtrec.rm_offset,
					gtrec.rm_flags);
			error = xfs_btree_delete(cur, &i);
			अगर (error)
				जाओ out_error;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ out_error;
			पूर्ण
		पूर्ण

		/* poपूर्णांक the cursor back to the left record and update */
		error = xfs_btree_decrement(cur, 0, &have_gt);
		अगर (error)
			जाओ out_error;
		error = xfs_rmap_update(cur, &ltrec);
		अगर (error)
			जाओ out_error;
	पूर्ण अन्यथा अगर (have_gt &&
		   bno + len == gtrec.rm_startblock &&
		   (ignore_off || offset + len == gtrec.rm_offset)) अणु
		/*
		 * right edge contiguous, merge पूर्णांकo right record.
		 *
		 *                 gtbno     gtlen
		 * Orig:             |ooooooooo|
		 * adding: |aaaaaaaaa|
		 * Result: |rrrrrrrrrrrrrrrrrrr|
		 *        bno       len
		 */
		gtrec.rm_startblock = bno;
		gtrec.rm_blockcount += len;
		अगर (!ignore_off)
			gtrec.rm_offset = offset;
		error = xfs_rmap_update(cur, &gtrec);
		अगर (error)
			जाओ out_error;
	पूर्ण अन्यथा अणु
		/*
		 * no contiguous edge with identical owner, insert
		 * new record at current cursor position.
		 */
		cur->bc_rec.r.rm_startblock = bno;
		cur->bc_rec.r.rm_blockcount = len;
		cur->bc_rec.r.rm_owner = owner;
		cur->bc_rec.r.rm_offset = offset;
		cur->bc_rec.r.rm_flags = flags;
		trace_xfs_rmap_insert(mp, cur->bc_ag.agno, bno, len,
			owner, offset, flags);
		error = xfs_btree_insert(cur, &i);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
	पूर्ण

	trace_xfs_rmap_map_करोne(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);
out_error:
	अगर (error)
		trace_xfs_rmap_map_error(mp, cur->bc_ag.agno,
				error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Add a reference to an extent in the rmap btree.
 */
पूर्णांक
xfs_rmap_alloc(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_buf			*agbp,
	xfs_agnumber_t			agno,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_btree_cur		*cur;
	पूर्णांक				error;

	अगर (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस 0;

	cur = xfs_rmapbt_init_cursor(mp, tp, agbp, agno);
	error = xfs_rmap_map(cur, bno, len, false, oinfo);

	xfs_btree_del_cursor(cur, error);
	वापस error;
पूर्ण

#घोषणा RMAP_LEFT_CONTIG	(1 << 0)
#घोषणा RMAP_RIGHT_CONTIG	(1 << 1)
#घोषणा RMAP_LEFT_FILLING	(1 << 2)
#घोषणा RMAP_RIGHT_FILLING	(1 << 3)
#घोषणा RMAP_LEFT_VALID		(1 << 6)
#घोषणा RMAP_RIGHT_VALID	(1 << 7)

#घोषणा LEFT		r[0]
#घोषणा RIGHT		r[1]
#घोषणा PREV		r[2]
#घोषणा NEW		r[3]

/*
 * Convert an unwritten extent to a real extent or vice versa.
 * Does not handle overlapping extents.
 */
STATIC पूर्णांक
xfs_rmap_convert(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	bool				unwritten,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	काष्ठा xfs_mount		*mp = cur->bc_mp;
	काष्ठा xfs_rmap_irec		r[4];	/* neighbor extent entries */
						/* left is 0, right is 1, */
						/* prev is 2, new is 3 */
	uपूर्णांक64_t		owner;
	uपूर्णांक64_t		offset;
	uपूर्णांक64_t		new_enकरोff;
	अचिन्हित पूर्णांक		oldext;
	अचिन्हित पूर्णांक		newext;
	अचिन्हित पूर्णांक		flags = 0;
	पूर्णांक			i;
	पूर्णांक			state = 0;
	पूर्णांक			error;

	xfs_owner_info_unpack(oinfo, &owner, &offset, &flags);
	ASSERT(!(XFS_RMAP_NON_INODE_OWNER(owner) ||
			(flags & (XFS_RMAP_ATTR_FORK | XFS_RMAP_BMBT_BLOCK))));
	oldext = unwritten ? XFS_RMAP_UNWRITTEN : 0;
	new_enकरोff = offset + len;
	trace_xfs_rmap_convert(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);

	/*
	 * For the initial lookup, look क्रम an exact match or the left-adjacent
	 * record क्रम our insertion poपूर्णांक. This will also give us the record क्रम
	 * start block contiguity tests.
	 */
	error = xfs_rmap_lookup_le(cur, bno, len, owner, offset, oldext, &i);
	अगर (error)
		जाओ करोne;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ करोne;
	पूर्ण

	error = xfs_rmap_get_rec(cur, &PREV, &i);
	अगर (error)
		जाओ करोne;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ करोne;
	पूर्ण
	trace_xfs_rmap_lookup_le_range_result(cur->bc_mp,
			cur->bc_ag.agno, PREV.rm_startblock,
			PREV.rm_blockcount, PREV.rm_owner,
			PREV.rm_offset, PREV.rm_flags);

	ASSERT(PREV.rm_offset <= offset);
	ASSERT(PREV.rm_offset + PREV.rm_blockcount >= new_enकरोff);
	ASSERT((PREV.rm_flags & XFS_RMAP_UNWRITTEN) == oldext);
	newext = ~oldext & XFS_RMAP_UNWRITTEN;

	/*
	 * Set flags determining what part of the previous oldext allocation
	 * extent is being replaced by a newext allocation.
	 */
	अगर (PREV.rm_offset == offset)
		state |= RMAP_LEFT_FILLING;
	अगर (PREV.rm_offset + PREV.rm_blockcount == new_enकरोff)
		state |= RMAP_RIGHT_FILLING;

	/*
	 * Decrement the cursor to see अगर we have a left-adjacent record to our
	 * insertion poपूर्णांक. This will give us the record क्रम end block
	 * contiguity tests.
	 */
	error = xfs_btree_decrement(cur, 0, &i);
	अगर (error)
		जाओ करोne;
	अगर (i) अणु
		state |= RMAP_LEFT_VALID;
		error = xfs_rmap_get_rec(cur, &LEFT, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		अगर (XFS_IS_CORRUPT(mp,
				   LEFT.rm_startblock + LEFT.rm_blockcount >
				   bno)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		trace_xfs_rmap_find_left_neighbor_result(cur->bc_mp,
				cur->bc_ag.agno, LEFT.rm_startblock,
				LEFT.rm_blockcount, LEFT.rm_owner,
				LEFT.rm_offset, LEFT.rm_flags);
		अगर (LEFT.rm_startblock + LEFT.rm_blockcount == bno &&
		    LEFT.rm_offset + LEFT.rm_blockcount == offset &&
		    xfs_rmap_is_mergeable(&LEFT, owner, newext))
			state |= RMAP_LEFT_CONTIG;
	पूर्ण

	/*
	 * Increment the cursor to see अगर we have a right-adjacent record to our
	 * insertion poपूर्णांक. This will give us the record क्रम end block
	 * contiguity tests.
	 */
	error = xfs_btree_increment(cur, 0, &i);
	अगर (error)
		जाओ करोne;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ करोne;
	पूर्ण
	error = xfs_btree_increment(cur, 0, &i);
	अगर (error)
		जाओ करोne;
	अगर (i) अणु
		state |= RMAP_RIGHT_VALID;
		error = xfs_rmap_get_rec(cur, &RIGHT, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		अगर (XFS_IS_CORRUPT(mp, bno + len > RIGHT.rm_startblock)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		trace_xfs_rmap_find_right_neighbor_result(cur->bc_mp,
				cur->bc_ag.agno, RIGHT.rm_startblock,
				RIGHT.rm_blockcount, RIGHT.rm_owner,
				RIGHT.rm_offset, RIGHT.rm_flags);
		अगर (bno + len == RIGHT.rm_startblock &&
		    offset + len == RIGHT.rm_offset &&
		    xfs_rmap_is_mergeable(&RIGHT, owner, newext))
			state |= RMAP_RIGHT_CONTIG;
	पूर्ण

	/* check that left + prev + right is not too दीर्घ */
	अगर ((state & (RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG |
			 RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG)) ==
	    (RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG |
	     RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG) &&
	    (अचिन्हित दीर्घ)LEFT.rm_blockcount + len +
	     RIGHT.rm_blockcount > XFS_RMAP_LEN_MAX)
		state &= ~RMAP_RIGHT_CONTIG;

	trace_xfs_rmap_convert_state(mp, cur->bc_ag.agno, state,
			_RET_IP_);

	/* reset the cursor back to PREV */
	error = xfs_rmap_lookup_le(cur, bno, len, owner, offset, oldext, &i);
	अगर (error)
		जाओ करोne;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ करोne;
	पूर्ण

	/*
	 * Switch out based on the FILLING and CONTIG state bits.
	 */
	चयन (state & (RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG |
			 RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG)) अणु
	हाल RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG |
	     RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * The left and right neighbors are both contiguous with new.
		 */
		error = xfs_btree_increment(cur, 0, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		trace_xfs_rmap_delete(mp, cur->bc_ag.agno,
				RIGHT.rm_startblock, RIGHT.rm_blockcount,
				RIGHT.rm_owner, RIGHT.rm_offset,
				RIGHT.rm_flags);
		error = xfs_btree_delete(cur, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		error = xfs_btree_decrement(cur, 0, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		trace_xfs_rmap_delete(mp, cur->bc_ag.agno,
				PREV.rm_startblock, PREV.rm_blockcount,
				PREV.rm_owner, PREV.rm_offset,
				PREV.rm_flags);
		error = xfs_btree_delete(cur, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		error = xfs_btree_decrement(cur, 0, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW = LEFT;
		NEW.rm_blockcount += PREV.rm_blockcount + RIGHT.rm_blockcount;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING | RMAP_RIGHT_FILLING | RMAP_LEFT_CONTIG:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * The left neighbor is contiguous, the right is not.
		 */
		trace_xfs_rmap_delete(mp, cur->bc_ag.agno,
				PREV.rm_startblock, PREV.rm_blockcount,
				PREV.rm_owner, PREV.rm_offset,
				PREV.rm_flags);
		error = xfs_btree_delete(cur, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		error = xfs_btree_decrement(cur, 0, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW = LEFT;
		NEW.rm_blockcount += PREV.rm_blockcount;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING | RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * The right neighbor is contiguous, the left is not.
		 */
		error = xfs_btree_increment(cur, 0, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		trace_xfs_rmap_delete(mp, cur->bc_ag.agno,
				RIGHT.rm_startblock, RIGHT.rm_blockcount,
				RIGHT.rm_owner, RIGHT.rm_offset,
				RIGHT.rm_flags);
		error = xfs_btree_delete(cur, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		error = xfs_btree_decrement(cur, 0, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW = PREV;
		NEW.rm_blockcount = len + RIGHT.rm_blockcount;
		NEW.rm_flags = newext;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING | RMAP_RIGHT_FILLING:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * Neither the left nor right neighbors are contiguous with
		 * the new one.
		 */
		NEW = PREV;
		NEW.rm_flags = newext;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG:
		/*
		 * Setting the first part of a previous oldext extent to newext.
		 * The left neighbor is contiguous.
		 */
		NEW = PREV;
		NEW.rm_offset += len;
		NEW.rm_startblock += len;
		NEW.rm_blockcount -= len;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		error = xfs_btree_decrement(cur, 0, &i);
		अगर (error)
			जाओ करोne;
		NEW = LEFT;
		NEW.rm_blockcount += len;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING:
		/*
		 * Setting the first part of a previous oldext extent to newext.
		 * The left neighbor is not contiguous.
		 */
		NEW = PREV;
		NEW.rm_startblock += len;
		NEW.rm_offset += len;
		NEW.rm_blockcount -= len;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		NEW.rm_startblock = bno;
		NEW.rm_owner = owner;
		NEW.rm_offset = offset;
		NEW.rm_blockcount = len;
		NEW.rm_flags = newext;
		cur->bc_rec.r = NEW;
		trace_xfs_rmap_insert(mp, cur->bc_ag.agno, bno,
				len, owner, offset, newext);
		error = xfs_btree_insert(cur, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		अवरोध;

	हाल RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG:
		/*
		 * Setting the last part of a previous oldext extent to newext.
		 * The right neighbor is contiguous with the new allocation.
		 */
		NEW = PREV;
		NEW.rm_blockcount -= len;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		error = xfs_btree_increment(cur, 0, &i);
		अगर (error)
			जाओ करोne;
		NEW = RIGHT;
		NEW.rm_offset = offset;
		NEW.rm_startblock = bno;
		NEW.rm_blockcount += len;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_RIGHT_FILLING:
		/*
		 * Setting the last part of a previous oldext extent to newext.
		 * The right neighbor is not contiguous.
		 */
		NEW = PREV;
		NEW.rm_blockcount -= len;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		error = xfs_rmap_lookup_eq(cur, bno, len, owner, offset,
				oldext, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW.rm_startblock = bno;
		NEW.rm_owner = owner;
		NEW.rm_offset = offset;
		NEW.rm_blockcount = len;
		NEW.rm_flags = newext;
		cur->bc_rec.r = NEW;
		trace_xfs_rmap_insert(mp, cur->bc_ag.agno, bno,
				len, owner, offset, newext);
		error = xfs_btree_insert(cur, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		अवरोध;

	हाल 0:
		/*
		 * Setting the middle part of a previous oldext extent to
		 * newext.  Contiguity is impossible here.
		 * One extent becomes three extents.
		 */
		/* new right extent - oldext */
		NEW.rm_startblock = bno + len;
		NEW.rm_owner = owner;
		NEW.rm_offset = new_enकरोff;
		NEW.rm_blockcount = PREV.rm_offset + PREV.rm_blockcount -
				new_enकरोff;
		NEW.rm_flags = PREV.rm_flags;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		/* new left extent - oldext */
		NEW = PREV;
		NEW.rm_blockcount = offset - PREV.rm_offset;
		cur->bc_rec.r = NEW;
		trace_xfs_rmap_insert(mp, cur->bc_ag.agno,
				NEW.rm_startblock, NEW.rm_blockcount,
				NEW.rm_owner, NEW.rm_offset,
				NEW.rm_flags);
		error = xfs_btree_insert(cur, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		/*
		 * Reset the cursor to the position of the new extent
		 * we are about to insert as we can't trust it after
		 * the previous insert.
		 */
		error = xfs_rmap_lookup_eq(cur, bno, len, owner, offset,
				oldext, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		/* new middle extent - newext */
		cur->bc_rec.r.rm_flags &= ~XFS_RMAP_UNWRITTEN;
		cur->bc_rec.r.rm_flags |= newext;
		trace_xfs_rmap_insert(mp, cur->bc_ag.agno, bno, len,
				owner, offset, newext);
		error = xfs_btree_insert(cur, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		अवरोध;

	हाल RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG | RMAP_RIGHT_CONTIG:
	हाल RMAP_RIGHT_FILLING | RMAP_LEFT_CONTIG | RMAP_RIGHT_CONTIG:
	हाल RMAP_LEFT_FILLING | RMAP_RIGHT_CONTIG:
	हाल RMAP_RIGHT_FILLING | RMAP_LEFT_CONTIG:
	हाल RMAP_LEFT_CONTIG | RMAP_RIGHT_CONTIG:
	हाल RMAP_LEFT_CONTIG:
	हाल RMAP_RIGHT_CONTIG:
		/*
		 * These हालs are all impossible.
		 */
		ASSERT(0);
	पूर्ण

	trace_xfs_rmap_convert_करोne(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);
करोne:
	अगर (error)
		trace_xfs_rmap_convert_error(cur->bc_mp,
				cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Convert an unwritten extent to a real extent or vice versa.  If there is no
 * possibility of overlapping extents, delegate to the simpler convert
 * function.
 */
STATIC पूर्णांक
xfs_rmap_convert_shared(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	bool				unwritten,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	काष्ठा xfs_mount		*mp = cur->bc_mp;
	काष्ठा xfs_rmap_irec		r[4];	/* neighbor extent entries */
						/* left is 0, right is 1, */
						/* prev is 2, new is 3 */
	uपूर्णांक64_t		owner;
	uपूर्णांक64_t		offset;
	uपूर्णांक64_t		new_enकरोff;
	अचिन्हित पूर्णांक		oldext;
	अचिन्हित पूर्णांक		newext;
	अचिन्हित पूर्णांक		flags = 0;
	पूर्णांक			i;
	पूर्णांक			state = 0;
	पूर्णांक			error;

	xfs_owner_info_unpack(oinfo, &owner, &offset, &flags);
	ASSERT(!(XFS_RMAP_NON_INODE_OWNER(owner) ||
			(flags & (XFS_RMAP_ATTR_FORK | XFS_RMAP_BMBT_BLOCK))));
	oldext = unwritten ? XFS_RMAP_UNWRITTEN : 0;
	new_enकरोff = offset + len;
	trace_xfs_rmap_convert(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);

	/*
	 * For the initial lookup, look क्रम and exact match or the left-adjacent
	 * record क्रम our insertion poपूर्णांक. This will also give us the record क्रम
	 * start block contiguity tests.
	 */
	error = xfs_rmap_lookup_le_range(cur, bno, owner, offset, oldext,
			&PREV, &i);
	अगर (error)
		जाओ करोne;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ करोne;
	पूर्ण

	ASSERT(PREV.rm_offset <= offset);
	ASSERT(PREV.rm_offset + PREV.rm_blockcount >= new_enकरोff);
	ASSERT((PREV.rm_flags & XFS_RMAP_UNWRITTEN) == oldext);
	newext = ~oldext & XFS_RMAP_UNWRITTEN;

	/*
	 * Set flags determining what part of the previous oldext allocation
	 * extent is being replaced by a newext allocation.
	 */
	अगर (PREV.rm_offset == offset)
		state |= RMAP_LEFT_FILLING;
	अगर (PREV.rm_offset + PREV.rm_blockcount == new_enकरोff)
		state |= RMAP_RIGHT_FILLING;

	/* Is there a left record that abuts our range? */
	error = xfs_rmap_find_left_neighbor(cur, bno, owner, offset, newext,
			&LEFT, &i);
	अगर (error)
		जाओ करोne;
	अगर (i) अणु
		state |= RMAP_LEFT_VALID;
		अगर (XFS_IS_CORRUPT(mp,
				   LEFT.rm_startblock + LEFT.rm_blockcount >
				   bno)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		अगर (xfs_rmap_is_mergeable(&LEFT, owner, newext))
			state |= RMAP_LEFT_CONTIG;
	पूर्ण

	/* Is there a right record that abuts our range? */
	error = xfs_rmap_lookup_eq(cur, bno + len, len, owner, offset + len,
			newext, &i);
	अगर (error)
		जाओ करोne;
	अगर (i) अणु
		state |= RMAP_RIGHT_VALID;
		error = xfs_rmap_get_rec(cur, &RIGHT, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		अगर (XFS_IS_CORRUPT(mp, bno + len > RIGHT.rm_startblock)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		trace_xfs_rmap_find_right_neighbor_result(cur->bc_mp,
				cur->bc_ag.agno, RIGHT.rm_startblock,
				RIGHT.rm_blockcount, RIGHT.rm_owner,
				RIGHT.rm_offset, RIGHT.rm_flags);
		अगर (xfs_rmap_is_mergeable(&RIGHT, owner, newext))
			state |= RMAP_RIGHT_CONTIG;
	पूर्ण

	/* check that left + prev + right is not too दीर्घ */
	अगर ((state & (RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG |
			 RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG)) ==
	    (RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG |
	     RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG) &&
	    (अचिन्हित दीर्घ)LEFT.rm_blockcount + len +
	     RIGHT.rm_blockcount > XFS_RMAP_LEN_MAX)
		state &= ~RMAP_RIGHT_CONTIG;

	trace_xfs_rmap_convert_state(mp, cur->bc_ag.agno, state,
			_RET_IP_);
	/*
	 * Switch out based on the FILLING and CONTIG state bits.
	 */
	चयन (state & (RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG |
			 RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG)) अणु
	हाल RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG |
	     RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * The left and right neighbors are both contiguous with new.
		 */
		error = xfs_rmap_delete(cur, RIGHT.rm_startblock,
				RIGHT.rm_blockcount, RIGHT.rm_owner,
				RIGHT.rm_offset, RIGHT.rm_flags);
		अगर (error)
			जाओ करोne;
		error = xfs_rmap_delete(cur, PREV.rm_startblock,
				PREV.rm_blockcount, PREV.rm_owner,
				PREV.rm_offset, PREV.rm_flags);
		अगर (error)
			जाओ करोne;
		NEW = LEFT;
		error = xfs_rmap_lookup_eq(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW.rm_blockcount += PREV.rm_blockcount + RIGHT.rm_blockcount;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING | RMAP_RIGHT_FILLING | RMAP_LEFT_CONTIG:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * The left neighbor is contiguous, the right is not.
		 */
		error = xfs_rmap_delete(cur, PREV.rm_startblock,
				PREV.rm_blockcount, PREV.rm_owner,
				PREV.rm_offset, PREV.rm_flags);
		अगर (error)
			जाओ करोne;
		NEW = LEFT;
		error = xfs_rmap_lookup_eq(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW.rm_blockcount += PREV.rm_blockcount;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING | RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * The right neighbor is contiguous, the left is not.
		 */
		error = xfs_rmap_delete(cur, RIGHT.rm_startblock,
				RIGHT.rm_blockcount, RIGHT.rm_owner,
				RIGHT.rm_offset, RIGHT.rm_flags);
		अगर (error)
			जाओ करोne;
		NEW = PREV;
		error = xfs_rmap_lookup_eq(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW.rm_blockcount += RIGHT.rm_blockcount;
		NEW.rm_flags = RIGHT.rm_flags;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING | RMAP_RIGHT_FILLING:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * Neither the left nor right neighbors are contiguous with
		 * the new one.
		 */
		NEW = PREV;
		error = xfs_rmap_lookup_eq(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW.rm_flags = newext;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG:
		/*
		 * Setting the first part of a previous oldext extent to newext.
		 * The left neighbor is contiguous.
		 */
		NEW = PREV;
		error = xfs_rmap_delete(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags);
		अगर (error)
			जाओ करोne;
		NEW.rm_offset += len;
		NEW.rm_startblock += len;
		NEW.rm_blockcount -= len;
		error = xfs_rmap_insert(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags);
		अगर (error)
			जाओ करोne;
		NEW = LEFT;
		error = xfs_rmap_lookup_eq(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW.rm_blockcount += len;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING:
		/*
		 * Setting the first part of a previous oldext extent to newext.
		 * The left neighbor is not contiguous.
		 */
		NEW = PREV;
		error = xfs_rmap_delete(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags);
		अगर (error)
			जाओ करोne;
		NEW.rm_offset += len;
		NEW.rm_startblock += len;
		NEW.rm_blockcount -= len;
		error = xfs_rmap_insert(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags);
		अगर (error)
			जाओ करोne;
		error = xfs_rmap_insert(cur, bno, len, owner, offset, newext);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_RIGHT_FILLING | RMAP_RIGHT_CONTIG:
		/*
		 * Setting the last part of a previous oldext extent to newext.
		 * The right neighbor is contiguous with the new allocation.
		 */
		NEW = PREV;
		error = xfs_rmap_lookup_eq(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW.rm_blockcount = offset - NEW.rm_offset;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		NEW = RIGHT;
		error = xfs_rmap_delete(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags);
		अगर (error)
			जाओ करोne;
		NEW.rm_offset = offset;
		NEW.rm_startblock = bno;
		NEW.rm_blockcount += len;
		error = xfs_rmap_insert(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_RIGHT_FILLING:
		/*
		 * Setting the last part of a previous oldext extent to newext.
		 * The right neighbor is not contiguous.
		 */
		NEW = PREV;
		error = xfs_rmap_lookup_eq(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW.rm_blockcount -= len;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		error = xfs_rmap_insert(cur, bno, len, owner, offset, newext);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल 0:
		/*
		 * Setting the middle part of a previous oldext extent to
		 * newext.  Contiguity is impossible here.
		 * One extent becomes three extents.
		 */
		/* new right extent - oldext */
		NEW.rm_startblock = bno + len;
		NEW.rm_owner = owner;
		NEW.rm_offset = new_enकरोff;
		NEW.rm_blockcount = PREV.rm_offset + PREV.rm_blockcount -
				new_enकरोff;
		NEW.rm_flags = PREV.rm_flags;
		error = xfs_rmap_insert(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner, NEW.rm_offset,
				NEW.rm_flags);
		अगर (error)
			जाओ करोne;
		/* new left extent - oldext */
		NEW = PREV;
		error = xfs_rmap_lookup_eq(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner,
				NEW.rm_offset, NEW.rm_flags, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		NEW.rm_blockcount = offset - NEW.rm_offset;
		error = xfs_rmap_update(cur, &NEW);
		अगर (error)
			जाओ करोne;
		/* new middle extent - newext */
		NEW.rm_startblock = bno;
		NEW.rm_blockcount = len;
		NEW.rm_owner = owner;
		NEW.rm_offset = offset;
		NEW.rm_flags = newext;
		error = xfs_rmap_insert(cur, NEW.rm_startblock,
				NEW.rm_blockcount, NEW.rm_owner, NEW.rm_offset,
				NEW.rm_flags);
		अगर (error)
			जाओ करोne;
		अवरोध;

	हाल RMAP_LEFT_FILLING | RMAP_LEFT_CONTIG | RMAP_RIGHT_CONTIG:
	हाल RMAP_RIGHT_FILLING | RMAP_LEFT_CONTIG | RMAP_RIGHT_CONTIG:
	हाल RMAP_LEFT_FILLING | RMAP_RIGHT_CONTIG:
	हाल RMAP_RIGHT_FILLING | RMAP_LEFT_CONTIG:
	हाल RMAP_LEFT_CONTIG | RMAP_RIGHT_CONTIG:
	हाल RMAP_LEFT_CONTIG:
	हाल RMAP_RIGHT_CONTIG:
		/*
		 * These हालs are all impossible.
		 */
		ASSERT(0);
	पूर्ण

	trace_xfs_rmap_convert_करोne(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);
करोne:
	अगर (error)
		trace_xfs_rmap_convert_error(cur->bc_mp,
				cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

#अघोषित	NEW
#अघोषित	LEFT
#अघोषित	RIGHT
#अघोषित	PREV

/*
 * Find an extent in the rmap btree and unmap it.  For rmap extent types that
 * can overlap (data विभाजन rmaps on reflink fileप्रणालीs) we must be careful
 * that the prev/next records in the btree might beदीर्घ to another owner.
 * Thereक्रमe we must use delete+insert to alter any of the key fields.
 *
 * For every other situation there can only be one owner क्रम a given extent,
 * so we can call the regular _मुक्त function.
 */
STATIC पूर्णांक
xfs_rmap_unmap_shared(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	bool				unwritten,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	काष्ठा xfs_mount		*mp = cur->bc_mp;
	काष्ठा xfs_rmap_irec		ltrec;
	uपूर्णांक64_t			ltoff;
	पूर्णांक				error = 0;
	पूर्णांक				i;
	uपूर्णांक64_t			owner;
	uपूर्णांक64_t			offset;
	अचिन्हित पूर्णांक			flags;

	xfs_owner_info_unpack(oinfo, &owner, &offset, &flags);
	अगर (unwritten)
		flags |= XFS_RMAP_UNWRITTEN;
	trace_xfs_rmap_unmap(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);

	/*
	 * We should always have a left record because there's a अटल record
	 * क्रम the AG headers at rm_startblock == 0 created by mkfs/growfs that
	 * will not ever be हटाओd from the tree.
	 */
	error = xfs_rmap_lookup_le_range(cur, bno, owner, offset, flags,
			&ltrec, &i);
	अगर (error)
		जाओ out_error;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण
	ltoff = ltrec.rm_offset;

	/* Make sure the extent we found covers the entire मुक्तing range. */
	अगर (XFS_IS_CORRUPT(mp,
			   ltrec.rm_startblock > bno ||
			   ltrec.rm_startblock + ltrec.rm_blockcount <
			   bno + len)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	/* Make sure the owner matches what we expect to find in the tree. */
	अगर (XFS_IS_CORRUPT(mp, owner != ltrec.rm_owner)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	/* Make sure the unwritten flag matches. */
	अगर (XFS_IS_CORRUPT(mp,
			   (flags & XFS_RMAP_UNWRITTEN) !=
			   (ltrec.rm_flags & XFS_RMAP_UNWRITTEN))) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	/* Check the offset. */
	अगर (XFS_IS_CORRUPT(mp, ltrec.rm_offset > offset)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण
	अगर (XFS_IS_CORRUPT(mp, offset > ltoff + ltrec.rm_blockcount)) अणु
		error = -EFSCORRUPTED;
		जाओ out_error;
	पूर्ण

	अगर (ltrec.rm_startblock == bno && ltrec.rm_blockcount == len) अणु
		/* Exact match, simply हटाओ the record from rmap tree. */
		error = xfs_rmap_delete(cur, ltrec.rm_startblock,
				ltrec.rm_blockcount, ltrec.rm_owner,
				ltrec.rm_offset, ltrec.rm_flags);
		अगर (error)
			जाओ out_error;
	पूर्ण अन्यथा अगर (ltrec.rm_startblock == bno) अणु
		/*
		 * Overlap left hand side of extent: move the start, trim the
		 * length and update the current record.
		 *
		 *       ltbno                ltlen
		 * Orig:    |oooooooooooooooooooo|
		 * Freeing: |fffffffff|
		 * Result:            |rrrrrrrrrr|
		 *         bno       len
		 */

		/* Delete prev rmap. */
		error = xfs_rmap_delete(cur, ltrec.rm_startblock,
				ltrec.rm_blockcount, ltrec.rm_owner,
				ltrec.rm_offset, ltrec.rm_flags);
		अगर (error)
			जाओ out_error;

		/* Add an rmap at the new offset. */
		ltrec.rm_startblock += len;
		ltrec.rm_blockcount -= len;
		ltrec.rm_offset += len;
		error = xfs_rmap_insert(cur, ltrec.rm_startblock,
				ltrec.rm_blockcount, ltrec.rm_owner,
				ltrec.rm_offset, ltrec.rm_flags);
		अगर (error)
			जाओ out_error;
	पूर्ण अन्यथा अगर (ltrec.rm_startblock + ltrec.rm_blockcount == bno + len) अणु
		/*
		 * Overlap right hand side of extent: trim the length and
		 * update the current record.
		 *
		 *       ltbno                ltlen
		 * Orig:    |oooooooooooooooooooo|
		 * Freeing:            |fffffffff|
		 * Result:  |rrrrrrrrrr|
		 *                    bno       len
		 */
		error = xfs_rmap_lookup_eq(cur, ltrec.rm_startblock,
				ltrec.rm_blockcount, ltrec.rm_owner,
				ltrec.rm_offset, ltrec.rm_flags, &i);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		ltrec.rm_blockcount -= len;
		error = xfs_rmap_update(cur, &ltrec);
		अगर (error)
			जाओ out_error;
	पूर्ण अन्यथा अणु
		/*
		 * Overlap middle of extent: trim the length of the existing
		 * record to the length of the new left-extent size, increment
		 * the insertion position so we can insert a new record
		 * containing the reमुख्यing right-extent space.
		 *
		 *       ltbno                ltlen
		 * Orig:    |oooooooooooooooooooo|
		 * Freeing:       |fffffffff|
		 * Result:  |rrrrr|         |rrrr|
		 *               bno       len
		 */
		xfs_extlen_t	orig_len = ltrec.rm_blockcount;

		/* Shrink the left side of the rmap */
		error = xfs_rmap_lookup_eq(cur, ltrec.rm_startblock,
				ltrec.rm_blockcount, ltrec.rm_owner,
				ltrec.rm_offset, ltrec.rm_flags, &i);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		ltrec.rm_blockcount = bno - ltrec.rm_startblock;
		error = xfs_rmap_update(cur, &ltrec);
		अगर (error)
			जाओ out_error;

		/* Add an rmap at the new offset */
		error = xfs_rmap_insert(cur, bno + len,
				orig_len - len - ltrec.rm_blockcount,
				ltrec.rm_owner, offset + len,
				ltrec.rm_flags);
		अगर (error)
			जाओ out_error;
	पूर्ण

	trace_xfs_rmap_unmap_करोne(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);
out_error:
	अगर (error)
		trace_xfs_rmap_unmap_error(cur->bc_mp,
				cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Find an extent in the rmap btree and map it.  For rmap extent types that
 * can overlap (data विभाजन rmaps on reflink fileप्रणालीs) we must be careful
 * that the prev/next records in the btree might beदीर्घ to another owner.
 * Thereक्रमe we must use delete+insert to alter any of the key fields.
 *
 * For every other situation there can only be one owner क्रम a given extent,
 * so we can call the regular _alloc function.
 */
STATIC पूर्णांक
xfs_rmap_map_shared(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	bool				unwritten,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	काष्ठा xfs_mount		*mp = cur->bc_mp;
	काष्ठा xfs_rmap_irec		ltrec;
	काष्ठा xfs_rmap_irec		gtrec;
	पूर्णांक				have_gt;
	पूर्णांक				have_lt;
	पूर्णांक				error = 0;
	पूर्णांक				i;
	uपूर्णांक64_t			owner;
	uपूर्णांक64_t			offset;
	अचिन्हित पूर्णांक			flags = 0;

	xfs_owner_info_unpack(oinfo, &owner, &offset, &flags);
	अगर (unwritten)
		flags |= XFS_RMAP_UNWRITTEN;
	trace_xfs_rmap_map(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);

	/* Is there a left record that abuts our range? */
	error = xfs_rmap_find_left_neighbor(cur, bno, owner, offset, flags,
			&ltrec, &have_lt);
	अगर (error)
		जाओ out_error;
	अगर (have_lt &&
	    !xfs_rmap_is_mergeable(&ltrec, owner, flags))
		have_lt = 0;

	/* Is there a right record that abuts our range? */
	error = xfs_rmap_lookup_eq(cur, bno + len, len, owner, offset + len,
			flags, &have_gt);
	अगर (error)
		जाओ out_error;
	अगर (have_gt) अणु
		error = xfs_rmap_get_rec(cur, &gtrec, &have_gt);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(mp, have_gt != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण
		trace_xfs_rmap_find_right_neighbor_result(cur->bc_mp,
			cur->bc_ag.agno, gtrec.rm_startblock,
			gtrec.rm_blockcount, gtrec.rm_owner,
			gtrec.rm_offset, gtrec.rm_flags);

		अगर (!xfs_rmap_is_mergeable(&gtrec, owner, flags))
			have_gt = 0;
	पूर्ण

	अगर (have_lt &&
	    ltrec.rm_startblock + ltrec.rm_blockcount == bno &&
	    ltrec.rm_offset + ltrec.rm_blockcount == offset) अणु
		/*
		 * Left edge contiguous, merge पूर्णांकo left record.
		 *
		 *       ltbno     ltlen
		 * orig:   |ooooooooo|
		 * adding:           |aaaaaaaaa|
		 * result: |rrrrrrrrrrrrrrrrrrr|
		 *                  bno       len
		 */
		ltrec.rm_blockcount += len;
		अगर (have_gt &&
		    bno + len == gtrec.rm_startblock &&
		    offset + len == gtrec.rm_offset) अणु
			/*
			 * Right edge also contiguous, delete right record
			 * and merge पूर्णांकo left record.
			 *
			 *       ltbno     ltlen    gtbno     gtlen
			 * orig:   |ooooooooo|         |ooooooooo|
			 * adding:           |aaaaaaaaa|
			 * result: |rrrrrrrrrrrrrrrrrrrrrrrrrrrrr|
			 */
			ltrec.rm_blockcount += gtrec.rm_blockcount;
			error = xfs_rmap_delete(cur, gtrec.rm_startblock,
					gtrec.rm_blockcount, gtrec.rm_owner,
					gtrec.rm_offset, gtrec.rm_flags);
			अगर (error)
				जाओ out_error;
		पूर्ण

		/* Poपूर्णांक the cursor back to the left record and update. */
		error = xfs_rmap_lookup_eq(cur, ltrec.rm_startblock,
				ltrec.rm_blockcount, ltrec.rm_owner,
				ltrec.rm_offset, ltrec.rm_flags, &i);
		अगर (error)
			जाओ out_error;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_error;
		पूर्ण

		error = xfs_rmap_update(cur, &ltrec);
		अगर (error)
			जाओ out_error;
	पूर्ण अन्यथा अगर (have_gt &&
		   bno + len == gtrec.rm_startblock &&
		   offset + len == gtrec.rm_offset) अणु
		/*
		 * Right edge contiguous, merge पूर्णांकo right record.
		 *
		 *                 gtbno     gtlen
		 * Orig:             |ooooooooo|
		 * adding: |aaaaaaaaa|
		 * Result: |rrrrrrrrrrrrrrrrrrr|
		 *        bno       len
		 */
		/* Delete the old record. */
		error = xfs_rmap_delete(cur, gtrec.rm_startblock,
				gtrec.rm_blockcount, gtrec.rm_owner,
				gtrec.rm_offset, gtrec.rm_flags);
		अगर (error)
			जाओ out_error;

		/* Move the start and re-add it. */
		gtrec.rm_startblock = bno;
		gtrec.rm_blockcount += len;
		gtrec.rm_offset = offset;
		error = xfs_rmap_insert(cur, gtrec.rm_startblock,
				gtrec.rm_blockcount, gtrec.rm_owner,
				gtrec.rm_offset, gtrec.rm_flags);
		अगर (error)
			जाओ out_error;
	पूर्ण अन्यथा अणु
		/*
		 * No contiguous edge with identical owner, insert
		 * new record at current cursor position.
		 */
		error = xfs_rmap_insert(cur, bno, len, owner, offset, flags);
		अगर (error)
			जाओ out_error;
	पूर्ण

	trace_xfs_rmap_map_करोne(mp, cur->bc_ag.agno, bno, len,
			unwritten, oinfo);
out_error:
	अगर (error)
		trace_xfs_rmap_map_error(cur->bc_mp,
				cur->bc_ag.agno, error, _RET_IP_);
	वापस error;
पूर्ण

/* Insert a raw rmap पूर्णांकo the rmapbt. */
पूर्णांक
xfs_rmap_map_raw(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_rmap_irec	*rmap)
अणु
	काष्ठा xfs_owner_info	oinfo;

	oinfo.oi_owner = rmap->rm_owner;
	oinfo.oi_offset = rmap->rm_offset;
	oinfo.oi_flags = 0;
	अगर (rmap->rm_flags & XFS_RMAP_ATTR_FORK)
		oinfo.oi_flags |= XFS_OWNER_INFO_ATTR_FORK;
	अगर (rmap->rm_flags & XFS_RMAP_BMBT_BLOCK)
		oinfo.oi_flags |= XFS_OWNER_INFO_BMBT_BLOCK;

	अगर (rmap->rm_flags || XFS_RMAP_NON_INODE_OWNER(rmap->rm_owner))
		वापस xfs_rmap_map(cur, rmap->rm_startblock,
				rmap->rm_blockcount,
				rmap->rm_flags & XFS_RMAP_UNWRITTEN,
				&oinfo);

	वापस xfs_rmap_map_shared(cur, rmap->rm_startblock,
			rmap->rm_blockcount,
			rmap->rm_flags & XFS_RMAP_UNWRITTEN,
			&oinfo);
पूर्ण

काष्ठा xfs_rmap_query_range_info अणु
	xfs_rmap_query_range_fn	fn;
	व्योम				*priv;
पूर्ण;

/* Format btree record and pass to our callback. */
STATIC पूर्णांक
xfs_rmap_query_range_helper(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*rec,
	व्योम			*priv)
अणु
	काष्ठा xfs_rmap_query_range_info	*query = priv;
	काष्ठा xfs_rmap_irec			irec;
	पूर्णांक					error;

	error = xfs_rmap_btrec_to_irec(rec, &irec);
	अगर (error)
		वापस error;
	वापस query->fn(cur, &irec, query->priv);
पूर्ण

/* Find all rmaps between two keys. */
पूर्णांक
xfs_rmap_query_range(
	काष्ठा xfs_btree_cur			*cur,
	काष्ठा xfs_rmap_irec			*low_rec,
	काष्ठा xfs_rmap_irec			*high_rec,
	xfs_rmap_query_range_fn			fn,
	व्योम					*priv)
अणु
	जोड़ xfs_btree_irec			low_brec;
	जोड़ xfs_btree_irec			high_brec;
	काष्ठा xfs_rmap_query_range_info	query;

	low_brec.r = *low_rec;
	high_brec.r = *high_rec;
	query.priv = priv;
	query.fn = fn;
	वापस xfs_btree_query_range(cur, &low_brec, &high_brec,
			xfs_rmap_query_range_helper, &query);
पूर्ण

/* Find all rmaps. */
पूर्णांक
xfs_rmap_query_all(
	काष्ठा xfs_btree_cur			*cur,
	xfs_rmap_query_range_fn			fn,
	व्योम					*priv)
अणु
	काष्ठा xfs_rmap_query_range_info	query;

	query.priv = priv;
	query.fn = fn;
	वापस xfs_btree_query_all(cur, xfs_rmap_query_range_helper, &query);
पूर्ण

/* Clean up after calling xfs_rmap_finish_one. */
व्योम
xfs_rmap_finish_one_cleanup(
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
 * Process one of the deferred rmap operations.  We pass back the
 * btree cursor to मुख्यtain our lock on the rmapbt between calls.
 * This saves समय and eliminates a buffer deadlock between the
 * superblock and the AGF because we'll always grab them in the same
 * order.
 */
पूर्णांक
xfs_rmap_finish_one(
	काष्ठा xfs_trans		*tp,
	क्रमागत xfs_rmap_पूर्णांकent_type	type,
	uपूर्णांक64_t			owner,
	पूर्णांक				whichविभाजन,
	xfs_fileoff_t			startoff,
	xfs_fsblock_t			startblock,
	xfs_filblks_t			blockcount,
	xfs_exntst_t			state,
	काष्ठा xfs_btree_cur		**pcur)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_btree_cur		*rcur;
	काष्ठा xfs_buf			*agbp = शून्य;
	पूर्णांक				error = 0;
	xfs_agnumber_t			agno;
	काष्ठा xfs_owner_info		oinfo;
	xfs_agblock_t			bno;
	bool				unwritten;

	agno = XFS_FSB_TO_AGNO(mp, startblock);
	ASSERT(agno != शून्यAGNUMBER);
	bno = XFS_FSB_TO_AGBNO(mp, startblock);

	trace_xfs_rmap_deferred(mp, agno, type, bno, owner, whichविभाजन,
			startoff, blockcount, state);

	अगर (XFS_TEST_ERROR(false, mp,
			XFS_ERRTAG_RMAP_FINISH_ONE))
		वापस -EIO;

	/*
	 * If we haven't gotten a cursor or the cursor AG doesn't match
	 * the startblock, get one now.
	 */
	rcur = *pcur;
	अगर (rcur != शून्य && rcur->bc_ag.agno != agno) अणु
		xfs_rmap_finish_one_cleanup(tp, rcur, 0);
		rcur = शून्य;
		*pcur = शून्य;
	पूर्ण
	अगर (rcur == शून्य) अणु
		/*
		 * Refresh the मुक्तlist beक्रमe we start changing the
		 * rmapbt, because a shape change could cause us to
		 * allocate blocks.
		 */
		error = xfs_मुक्त_extent_fix_मुक्तlist(tp, agno, &agbp);
		अगर (error)
			वापस error;
		अगर (XFS_IS_CORRUPT(tp->t_mountp, !agbp))
			वापस -EFSCORRUPTED;

		rcur = xfs_rmapbt_init_cursor(mp, tp, agbp, agno);
	पूर्ण
	*pcur = rcur;

	xfs_rmap_ino_owner(&oinfo, owner, whichविभाजन, startoff);
	unwritten = state == XFS_EXT_UNWRITTEN;
	bno = XFS_FSB_TO_AGBNO(rcur->bc_mp, startblock);

	चयन (type) अणु
	हाल XFS_RMAP_ALLOC:
	हाल XFS_RMAP_MAP:
		error = xfs_rmap_map(rcur, bno, blockcount, unwritten, &oinfo);
		अवरोध;
	हाल XFS_RMAP_MAP_SHARED:
		error = xfs_rmap_map_shared(rcur, bno, blockcount, unwritten,
				&oinfo);
		अवरोध;
	हाल XFS_RMAP_FREE:
	हाल XFS_RMAP_UNMAP:
		error = xfs_rmap_unmap(rcur, bno, blockcount, unwritten,
				&oinfo);
		अवरोध;
	हाल XFS_RMAP_UNMAP_SHARED:
		error = xfs_rmap_unmap_shared(rcur, bno, blockcount, unwritten,
				&oinfo);
		अवरोध;
	हाल XFS_RMAP_CONVERT:
		error = xfs_rmap_convert(rcur, bno, blockcount, !unwritten,
				&oinfo);
		अवरोध;
	हाल XFS_RMAP_CONVERT_SHARED:
		error = xfs_rmap_convert_shared(rcur, bno, blockcount,
				!unwritten, &oinfo);
		अवरोध;
	शेष:
		ASSERT(0);
		error = -EFSCORRUPTED;
	पूर्ण
	वापस error;
पूर्ण

/*
 * Don't defer an rmap if we aren't an rmap fileप्रणाली.
 */
अटल bool
xfs_rmap_update_is_needed(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			whichविभाजन)
अणु
	वापस xfs_sb_version_hasrmapbt(&mp->m_sb) && whichविभाजन != XFS_COW_FORK;
पूर्ण

/*
 * Record a rmap पूर्णांकent; the list is kept sorted first by AG and then by
 * increasing age.
 */
अटल व्योम
__xfs_rmap_add(
	काष्ठा xfs_trans		*tp,
	क्रमागत xfs_rmap_पूर्णांकent_type	type,
	uपूर्णांक64_t			owner,
	पूर्णांक				whichविभाजन,
	काष्ठा xfs_bmbt_irec		*bmap)
अणु
	काष्ठा xfs_rmap_पूर्णांकent		*ri;

	trace_xfs_rmap_defer(tp->t_mountp,
			XFS_FSB_TO_AGNO(tp->t_mountp, bmap->br_startblock),
			type,
			XFS_FSB_TO_AGBNO(tp->t_mountp, bmap->br_startblock),
			owner, whichविभाजन,
			bmap->br_startoff,
			bmap->br_blockcount,
			bmap->br_state);

	ri = kmem_alloc(माप(काष्ठा xfs_rmap_पूर्णांकent), KM_NOFS);
	INIT_LIST_HEAD(&ri->ri_list);
	ri->ri_type = type;
	ri->ri_owner = owner;
	ri->ri_whichविभाजन = whichविभाजन;
	ri->ri_bmap = *bmap;

	xfs_defer_add(tp, XFS_DEFER_OPS_TYPE_RMAP, &ri->ri_list);
पूर्ण

/* Map an extent पूर्णांकo a file. */
व्योम
xfs_rmap_map_extent(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_bmbt_irec	*PREV)
अणु
	क्रमागत xfs_rmap_पूर्णांकent_type type = XFS_RMAP_MAP;

	अगर (!xfs_rmap_update_is_needed(tp->t_mountp, whichविभाजन))
		वापस;

	अगर (whichविभाजन != XFS_ATTR_FORK && xfs_is_reflink_inode(ip))
		type = XFS_RMAP_MAP_SHARED;

	__xfs_rmap_add(tp, type, ip->i_ino, whichविभाजन, PREV);
पूर्ण

/* Unmap an extent out of a file. */
व्योम
xfs_rmap_unmap_extent(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_bmbt_irec	*PREV)
अणु
	क्रमागत xfs_rmap_पूर्णांकent_type type = XFS_RMAP_UNMAP;

	अगर (!xfs_rmap_update_is_needed(tp->t_mountp, whichविभाजन))
		वापस;

	अगर (whichविभाजन != XFS_ATTR_FORK && xfs_is_reflink_inode(ip))
		type = XFS_RMAP_UNMAP_SHARED;

	__xfs_rmap_add(tp, type, ip->i_ino, whichविभाजन, PREV);
पूर्ण

/*
 * Convert a data विभाजन extent from unwritten to real or vice versa.
 *
 * Note that tp can be शून्य here as no transaction is used क्रम COW विभाजन
 * unwritten conversion.
 */
व्योम
xfs_rmap_convert_extent(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_bmbt_irec	*PREV)
अणु
	क्रमागत xfs_rmap_पूर्णांकent_type type = XFS_RMAP_CONVERT;

	अगर (!xfs_rmap_update_is_needed(mp, whichविभाजन))
		वापस;

	अगर (whichविभाजन != XFS_ATTR_FORK && xfs_is_reflink_inode(ip))
		type = XFS_RMAP_CONVERT_SHARED;

	__xfs_rmap_add(tp, type, ip->i_ino, whichविभाजन, PREV);
पूर्ण

/* Schedule the creation of an rmap क्रम non-file data. */
व्योम
xfs_rmap_alloc_extent(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		bno,
	xfs_extlen_t		len,
	uपूर्णांक64_t		owner)
अणु
	काष्ठा xfs_bmbt_irec	bmap;

	अगर (!xfs_rmap_update_is_needed(tp->t_mountp, XFS_DATA_FORK))
		वापस;

	bmap.br_startblock = XFS_AGB_TO_FSB(tp->t_mountp, agno, bno);
	bmap.br_blockcount = len;
	bmap.br_startoff = 0;
	bmap.br_state = XFS_EXT_NORM;

	__xfs_rmap_add(tp, XFS_RMAP_ALLOC, owner, XFS_DATA_FORK, &bmap);
पूर्ण

/* Schedule the deletion of an rmap क्रम non-file data. */
व्योम
xfs_rmap_मुक्त_extent(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		bno,
	xfs_extlen_t		len,
	uपूर्णांक64_t		owner)
अणु
	काष्ठा xfs_bmbt_irec	bmap;

	अगर (!xfs_rmap_update_is_needed(tp->t_mountp, XFS_DATA_FORK))
		वापस;

	bmap.br_startblock = XFS_AGB_TO_FSB(tp->t_mountp, agno, bno);
	bmap.br_blockcount = len;
	bmap.br_startoff = 0;
	bmap.br_state = XFS_EXT_NORM;

	__xfs_rmap_add(tp, XFS_RMAP_FREE, owner, XFS_DATA_FORK, &bmap);
पूर्ण

/* Compare rmap records.  Returns -1 अगर a < b, 1 अगर a > b, and 0 अगर equal. */
पूर्णांक
xfs_rmap_compare(
	स्थिर काष्ठा xfs_rmap_irec	*a,
	स्थिर काष्ठा xfs_rmap_irec	*b)
अणु
	__u64				oa;
	__u64				ob;

	oa = xfs_rmap_irec_offset_pack(a);
	ob = xfs_rmap_irec_offset_pack(b);

	अगर (a->rm_startblock < b->rm_startblock)
		वापस -1;
	अन्यथा अगर (a->rm_startblock > b->rm_startblock)
		वापस 1;
	अन्यथा अगर (a->rm_owner < b->rm_owner)
		वापस -1;
	अन्यथा अगर (a->rm_owner > b->rm_owner)
		वापस 1;
	अन्यथा अगर (oa < ob)
		वापस -1;
	अन्यथा अगर (oa > ob)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* Is there a record covering a given extent? */
पूर्णांक
xfs_rmap_has_record(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	xfs_extlen_t		len,
	bool			*exists)
अणु
	जोड़ xfs_btree_irec	low;
	जोड़ xfs_btree_irec	high;

	स_रखो(&low, 0, माप(low));
	low.r.rm_startblock = bno;
	स_रखो(&high, 0xFF, माप(high));
	high.r.rm_startblock = bno + len - 1;

	वापस xfs_btree_has_record(cur, &low, &high, exists);
पूर्ण

/*
 * Is there a record क्रम this owner completely covering a given physical
 * extent?  If so, *has_rmap will be set to true.  If there is no record
 * or the record only covers part of the range, we set *has_rmap to false.
 * This function करोesn't perक्रमm range lookups or offset checks, so it is
 * not suitable क्रम checking data विभाजन blocks.
 */
पूर्णांक
xfs_rmap_record_exists(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	bool				*has_rmap)
अणु
	uपूर्णांक64_t			owner;
	uपूर्णांक64_t			offset;
	अचिन्हित पूर्णांक			flags;
	पूर्णांक				has_record;
	काष्ठा xfs_rmap_irec		irec;
	पूर्णांक				error;

	xfs_owner_info_unpack(oinfo, &owner, &offset, &flags);
	ASSERT(XFS_RMAP_NON_INODE_OWNER(owner) ||
	       (flags & XFS_RMAP_BMBT_BLOCK));

	error = xfs_rmap_lookup_le(cur, bno, len, owner, offset, flags,
			&has_record);
	अगर (error)
		वापस error;
	अगर (!has_record) अणु
		*has_rmap = false;
		वापस 0;
	पूर्ण

	error = xfs_rmap_get_rec(cur, &irec, &has_record);
	अगर (error)
		वापस error;
	अगर (!has_record) अणु
		*has_rmap = false;
		वापस 0;
	पूर्ण

	*has_rmap = (irec.rm_owner == owner && irec.rm_startblock <= bno &&
		     irec.rm_startblock + irec.rm_blockcount >= bno + len);
	वापस 0;
पूर्ण

काष्ठा xfs_rmap_key_state अणु
	uपूर्णांक64_t			owner;
	uपूर्णांक64_t			offset;
	अचिन्हित पूर्णांक			flags;
पूर्ण;

/* For each rmap given, figure out अगर it करोesn't match the key we want. */
STATIC पूर्णांक
xfs_rmap_has_other_keys_helper(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_rmap_irec		*rec,
	व्योम				*priv)
अणु
	काष्ठा xfs_rmap_key_state	*rks = priv;

	अगर (rks->owner == rec->rm_owner && rks->offset == rec->rm_offset &&
	    ((rks->flags & rec->rm_flags) & XFS_RMAP_KEY_FLAGS) == rks->flags)
		वापस 0;
	वापस -ECANCELED;
पूर्ण

/*
 * Given an extent and some owner info, can we find records overlapping
 * the extent whose owner info करोes not match the given owner?
 */
पूर्णांक
xfs_rmap_has_other_keys(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	bool				*has_rmap)
अणु
	काष्ठा xfs_rmap_irec		low = अणु0पूर्ण;
	काष्ठा xfs_rmap_irec		high;
	काष्ठा xfs_rmap_key_state	rks;
	पूर्णांक				error;

	xfs_owner_info_unpack(oinfo, &rks.owner, &rks.offset, &rks.flags);
	*has_rmap = false;

	low.rm_startblock = bno;
	स_रखो(&high, 0xFF, माप(high));
	high.rm_startblock = bno + len - 1;

	error = xfs_rmap_query_range(cur, &low, &high,
			xfs_rmap_has_other_keys_helper, &rks);
	अगर (error == -ECANCELED) अणु
		*has_rmap = true;
		वापस 0;
	पूर्ण

	वापस error;
पूर्ण

स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_SKIP_UPDATE = अणु
	.oi_owner = XFS_RMAP_OWN_शून्य,
पूर्ण;
स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_ANY_OWNER = अणु
	.oi_owner = XFS_RMAP_OWN_UNKNOWN,
पूर्ण;
स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_FS = अणु
	.oi_owner = XFS_RMAP_OWN_FS,
पूर्ण;
स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_LOG = अणु
	.oi_owner = XFS_RMAP_OWN_LOG,
पूर्ण;
स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_AG = अणु
	.oi_owner = XFS_RMAP_OWN_AG,
पूर्ण;
स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_INOBT = अणु
	.oi_owner = XFS_RMAP_OWN_INOBT,
पूर्ण;
स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_INODES = अणु
	.oi_owner = XFS_RMAP_OWN_INODES,
पूर्ण;
स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_REFC = अणु
	.oi_owner = XFS_RMAP_OWN_REFC,
पूर्ण;
स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_COW = अणु
	.oi_owner = XFS_RMAP_OWN_COW,
पूर्ण;
