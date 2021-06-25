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
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_util.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_refcount_btree.h"
#समावेश "xfs_refcount.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_reflink.h"
#समावेश "xfs_iomap.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_ag_resv.h"

/*
 * Copy on Write of Shared Blocks
 *
 * XFS must preserve "the usual" file semantics even when two files share
 * the same physical blocks.  This means that a ग_लिखो to one file must not
 * alter the blocks in a dअगरferent file; the way that we'll करो that is
 * through the use of a copy-on-ग_लिखो mechanism.  At a high level, that
 * means that when we want to ग_लिखो to a shared block, we allocate a new
 * block, ग_लिखो the data to the new block, and अगर that succeeds we map the
 * new block पूर्णांकo the file.
 *
 * XFS provides a "delayed allocation" mechanism that defers the allocation
 * of disk blocks to dirty-but-not-yet-mapped file blocks as दीर्घ as
 * possible.  This reduces fragmentation by enabling the fileप्रणाली to ask
 * क्रम bigger chunks less often, which is exactly what we want क्रम CoW.
 *
 * The delalloc mechanism begins when the kernel wants to make a block
 * writable (ग_लिखो_begin or page_mkग_लिखो).  If the offset is not mapped, we
 * create a delalloc mapping, which is a regular in-core extent, but without
 * a real startblock.  (For delalloc mappings, the startblock encodes both
 * a flag that this is a delalloc mapping, and a worst-हाल estimate of how
 * many blocks might be required to put the mapping पूर्णांकo the BMBT.)  delalloc
 * mappings are a reservation against the मुक्त space in the fileप्रणाली;
 * adjacent mappings can also be combined पूर्णांकo fewer larger mappings.
 *
 * As an optimization, the CoW extent size hपूर्णांक (cowextsz) creates
 * outsized aligned delalloc reservations in the hope of landing out of
 * order nearby CoW ग_लिखोs in a single extent on disk, thereby reducing
 * fragmentation and improving future perक्रमmance.
 *
 * D: --RRRRRRSSSRRRRRRRR--- (data विभाजन)
 * C: ------DDDDDDD--------- (CoW विभाजन)
 *
 * When dirty pages are being written out (typically in ग_लिखोpage), the
 * delalloc reservations are converted पूर्णांकo unwritten mappings by
 * allocating blocks and replacing the delalloc mapping with real ones.
 * A delalloc mapping can be replaced by several unwritten ones अगर the
 * मुक्त space is fragmented.
 *
 * D: --RRRRRRSSSRRRRRRRR---
 * C: ------UUUUUUU---------
 *
 * We want to adapt the delalloc mechanism क्रम copy-on-ग_लिखो, since the
 * ग_लिखो paths are similar.  The first two steps (creating the reservation
 * and allocating the blocks) are exactly the same as delalloc except that
 * the mappings must be stored in a separate CoW विभाजन because we करो not want
 * to disturb the mapping in the data विभाजन until we're sure that the ग_लिखो
 * succeeded.  IO completion in this हाल is the process of removing the old
 * mapping from the data विभाजन and moving the new mapping from the CoW विभाजन to
 * the data विभाजन.  This will be discussed लघुly.
 *
 * For now, unaligned directio ग_लिखोs will be bounced back to the page cache.
 * Block-aligned directio ग_लिखोs will use the same mechanism as buffered
 * ग_लिखोs.
 *
 * Just prior to submitting the actual disk ग_लिखो requests, we convert
 * the extents representing the range of the file actually being written
 * (as opposed to extra pieces created क्रम the cowextsize hपूर्णांक) to real
 * extents.  This will become important in the next step:
 *
 * D: --RRRRRRSSSRRRRRRRR---
 * C: ------UUrrUUU---------
 *
 * CoW remapping must be करोne after the data block ग_लिखो completes,
 * because we करोn't want to destroy the old data fork map until we're sure
 * the new block has been written.  Since the new mappings are kept in a
 * separate विभाजन, we can simply iterate these mappings to find the ones
 * that cover the file blocks that we just CoW'd.  For each extent, simply
 * unmap the corresponding range in the data विभाजन, map the new range पूर्णांकo
 * the data विभाजन, and हटाओ the extent from the CoW विभाजन.  Because of
 * the presence of the cowextsize hपूर्णांक, however, we must be careful
 * only to remap the blocks that we've actually written out --  we must
 * never remap delalloc reservations nor CoW staging blocks that have
 * yet to be written.  This corresponds exactly to the real extents in
 * the CoW विभाजन:
 *
 * D: --RRRRRRrrSRRRRRRRR---
 * C: ------UU--UUU---------
 *
 * Since the remapping operation can be applied to an arbitrary file
 * range, we record the need क्रम the remap step as a flag in the ioend
 * instead of declaring a new IO type.  This is required क्रम direct io
 * because we only have ioend क्रम the whole dio, and we have to be able to
 * remember the presence of unwritten blocks and CoW blocks with a single
 * ioend काष्ठाure.  Better yet, the more ground we can cover with one
 * ioend, the better.
 */

/*
 * Given an AG extent, find the lowest-numbered run of shared blocks
 * within that range and वापस the range in fbno/flen.  If
 * find_end_of_shared is true, वापस the दीर्घest contiguous extent of
 * shared blocks.  If there are no shared extents, fbno and flen will
 * be set to शून्यAGBLOCK and 0, respectively.
 */
पूर्णांक
xfs_reflink_find_shared(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		agbno,
	xfs_extlen_t		aglen,
	xfs_agblock_t		*fbno,
	xfs_extlen_t		*flen,
	bool			find_end_of_shared)
अणु
	काष्ठा xfs_buf		*agbp;
	काष्ठा xfs_btree_cur	*cur;
	पूर्णांक			error;

	error = xfs_alloc_पढ़ो_agf(mp, tp, agno, 0, &agbp);
	अगर (error)
		वापस error;

	cur = xfs_refcountbt_init_cursor(mp, tp, agbp, agno);

	error = xfs_refcount_find_shared(cur, agbno, aglen, fbno, flen,
			find_end_of_shared);

	xfs_btree_del_cursor(cur, error);

	xfs_trans_brअन्यथा(tp, agbp);
	वापस error;
पूर्ण

/*
 * Trim the mapping to the next block where there's a change in the
 * shared/unshared status.  More specअगरically, this means that we
 * find the lowest-numbered extent of shared blocks that coincides with
 * the given block mapping.  If the shared extent overlaps the start of
 * the mapping, trim the mapping to the end of the shared extent.  If
 * the shared region पूर्णांकersects the mapping, trim the mapping to the
 * start of the shared extent.  If there are no shared regions that
 * overlap, just वापस the original extent.
 */
पूर्णांक
xfs_reflink_trim_around_shared(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_bmbt_irec	*irec,
	bool			*shared)
अणु
	xfs_agnumber_t		agno;
	xfs_agblock_t		agbno;
	xfs_extlen_t		aglen;
	xfs_agblock_t		fbno;
	xfs_extlen_t		flen;
	पूर्णांक			error = 0;

	/* Holes, unwritten, and delalloc extents cannot be shared */
	अगर (!xfs_is_cow_inode(ip) || !xfs_bmap_is_written_extent(irec)) अणु
		*shared = false;
		वापस 0;
	पूर्ण

	trace_xfs_reflink_trim_around_shared(ip, irec);

	agno = XFS_FSB_TO_AGNO(ip->i_mount, irec->br_startblock);
	agbno = XFS_FSB_TO_AGBNO(ip->i_mount, irec->br_startblock);
	aglen = irec->br_blockcount;

	error = xfs_reflink_find_shared(ip->i_mount, शून्य, agno, agbno,
			aglen, &fbno, &flen, true);
	अगर (error)
		वापस error;

	*shared = false;
	अगर (fbno == शून्यAGBLOCK) अणु
		/* No shared blocks at all. */
		वापस 0;
	पूर्ण अन्यथा अगर (fbno == agbno) अणु
		/*
		 * The start of this extent is shared.  Truncate the
		 * mapping at the end of the shared region so that a
		 * subsequent iteration starts at the start of the
		 * unshared region.
		 */
		irec->br_blockcount = flen;
		*shared = true;
		वापस 0;
	पूर्ण अन्यथा अणु
		/*
		 * There's a shared extent midway through this extent.
		 * Truncate the mapping at the start of the shared
		 * extent so that a subsequent iteration starts at the
		 * start of the shared region.
		 */
		irec->br_blockcount = fbno - agbno;
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक
xfs_bmap_trim_cow(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_bmbt_irec	*imap,
	bool			*shared)
अणु
	/* We can't update any real extents in always COW mode. */
	अगर (xfs_is_always_cow_inode(ip) &&
	    !isnullstartblock(imap->br_startblock)) अणु
		*shared = true;
		वापस 0;
	पूर्ण

	/* Trim the mapping to the nearest shared extent boundary. */
	वापस xfs_reflink_trim_around_shared(ip, imap, shared);
पूर्ण

अटल पूर्णांक
xfs_reflink_convert_cow_locked(
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		offset_fsb,
	xfs_filblks_t		count_fsb)
अणु
	काष्ठा xfs_iext_cursor	icur;
	काष्ठा xfs_bmbt_irec	got;
	काष्ठा xfs_btree_cur	*dummy_cur = शून्य;
	पूर्णांक			dummy_logflags;
	पूर्णांक			error = 0;

	अगर (!xfs_iext_lookup_extent(ip, ip->i_cowfp, offset_fsb, &icur, &got))
		वापस 0;

	करो अणु
		अगर (got.br_startoff >= offset_fsb + count_fsb)
			अवरोध;
		अगर (got.br_state == XFS_EXT_NORM)
			जारी;
		अगर (WARN_ON_ONCE(isnullstartblock(got.br_startblock)))
			वापस -EIO;

		xfs_trim_extent(&got, offset_fsb, count_fsb);
		अगर (!got.br_blockcount)
			जारी;

		got.br_state = XFS_EXT_NORM;
		error = xfs_bmap_add_extent_unwritten_real(शून्य, ip,
				XFS_COW_FORK, &icur, &dummy_cur, &got,
				&dummy_logflags);
		अगर (error)
			वापस error;
	पूर्ण जबतक (xfs_iext_next_extent(ip->i_cowfp, &icur, &got));

	वापस error;
पूर्ण

/* Convert all of the unwritten CoW extents in a file's range to real ones. */
पूर्णांक
xfs_reflink_convert_cow(
	काष्ठा xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		count)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fileoff_t		end_fsb = XFS_B_TO_FSB(mp, offset + count);
	xfs_filblks_t		count_fsb = end_fsb - offset_fsb;
	पूर्णांक			error;

	ASSERT(count != 0);

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	error = xfs_reflink_convert_cow_locked(ip, offset_fsb, count_fsb);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

/*
 * Find the extent that maps the given range in the COW विभाजन. Even अगर the extent
 * is not shared we might have a pपुनः_स्मृतिation क्रम it in the COW विभाजन. If so we
 * use it that rather than trigger a new allocation.
 */
अटल पूर्णांक
xfs_find_trim_cow_extent(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_bmbt_irec	*imap,
	काष्ठा xfs_bmbt_irec	*cmap,
	bool			*shared,
	bool			*found)
अणु
	xfs_fileoff_t		offset_fsb = imap->br_startoff;
	xfs_filblks_t		count_fsb = imap->br_blockcount;
	काष्ठा xfs_iext_cursor	icur;

	*found = false;

	/*
	 * If we करोn't find an overlapping extent, trim the range we need to
	 * allocate to fit the hole we found.
	 */
	अगर (!xfs_iext_lookup_extent(ip, ip->i_cowfp, offset_fsb, &icur, cmap))
		cmap->br_startoff = offset_fsb + count_fsb;
	अगर (cmap->br_startoff > offset_fsb) अणु
		xfs_trim_extent(imap, imap->br_startoff,
				cmap->br_startoff - imap->br_startoff);
		वापस xfs_bmap_trim_cow(ip, imap, shared);
	पूर्ण

	*shared = true;
	अगर (isnullstartblock(cmap->br_startblock)) अणु
		xfs_trim_extent(imap, cmap->br_startoff, cmap->br_blockcount);
		वापस 0;
	पूर्ण

	/* real extent found - no need to allocate */
	xfs_trim_extent(cmap, offset_fsb, count_fsb);
	*found = true;
	वापस 0;
पूर्ण

/* Allocate all CoW reservations covering a range of blocks in a file. */
पूर्णांक
xfs_reflink_allocate_cow(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_bmbt_irec	*imap,
	काष्ठा xfs_bmbt_irec	*cmap,
	bool			*shared,
	uपूर्णांक			*lockmode,
	bool			convert_now)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		offset_fsb = imap->br_startoff;
	xfs_filblks_t		count_fsb = imap->br_blockcount;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			nimaps, error = 0;
	bool			found;
	xfs_filblks_t		resaligned;
	xfs_extlen_t		resblks = 0;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	अगर (!ip->i_cowfp) अणु
		ASSERT(!xfs_is_reflink_inode(ip));
		xfs_अगरork_init_cow(ip);
	पूर्ण

	error = xfs_find_trim_cow_extent(ip, imap, cmap, shared, &found);
	अगर (error || !*shared)
		वापस error;
	अगर (found)
		जाओ convert;

	resaligned = xfs_aligned_fsb_count(imap->br_startoff,
		imap->br_blockcount, xfs_get_cowextsz_hपूर्णांक(ip));
	resblks = XFS_DIOSTRAT_SPACE_RES(mp, resaligned);

	xfs_iunlock(ip, *lockmode);
	*lockmode = 0;

	error = xfs_trans_alloc_inode(ip, &M_RES(mp)->tr_ग_लिखो, resblks, 0,
			false, &tp);
	अगर (error)
		वापस error;

	*lockmode = XFS_ILOCK_EXCL;

	/*
	 * Check क्रम an overlapping extent again now that we dropped the ilock.
	 */
	error = xfs_find_trim_cow_extent(ip, imap, cmap, shared, &found);
	अगर (error || !*shared)
		जाओ out_trans_cancel;
	अगर (found) अणु
		xfs_trans_cancel(tp);
		जाओ convert;
	पूर्ण

	/* Allocate the entire reservation as unwritten blocks. */
	nimaps = 1;
	error = xfs_bmapi_ग_लिखो(tp, ip, imap->br_startoff, imap->br_blockcount,
			XFS_BMAPI_COWFORK | XFS_BMAPI_PREALLOC, 0, cmap,
			&nimaps);
	अगर (error)
		जाओ out_trans_cancel;

	xfs_inode_set_cowblocks_tag(ip);
	error = xfs_trans_commit(tp);
	अगर (error)
		वापस error;

	/*
	 * Allocation succeeded but the requested range was not even partially
	 * satisfied?  Bail out!
	 */
	अगर (nimaps == 0)
		वापस -ENOSPC;
convert:
	xfs_trim_extent(cmap, offset_fsb, count_fsb);
	/*
	 * COW विभाजन extents are supposed to reमुख्य unwritten until we're पढ़ोy
	 * to initiate a disk ग_लिखो.  For direct I/O we are going to ग_लिखो the
	 * data and need the conversion, but क्रम buffered ग_लिखोs we're करोne.
	 */
	अगर (!convert_now || cmap->br_state == XFS_EXT_NORM)
		वापस 0;
	trace_xfs_reflink_convert_cow(ip, cmap);
	वापस xfs_reflink_convert_cow_locked(ip, offset_fsb, count_fsb);

out_trans_cancel:
	xfs_trans_cancel(tp);
	वापस error;
पूर्ण

/*
 * Cancel CoW reservations क्रम some block range of an inode.
 *
 * If cancel_real is true this function cancels all COW विभाजन extents क्रम the
 * inode; अगर cancel_real is false, real extents are not cleared.
 *
 * Caller must have alपढ़ोy joined the inode to the current transaction. The
 * inode will be joined to the transaction वापसed to the caller.
 */
पूर्णांक
xfs_reflink_cancel_cow_blocks(
	काष्ठा xfs_inode		*ip,
	काष्ठा xfs_trans		**tpp,
	xfs_fileoff_t			offset_fsb,
	xfs_fileoff_t			end_fsb,
	bool				cancel_real)
अणु
	काष्ठा xfs_अगरork		*अगरp = XFS_IFORK_PTR(ip, XFS_COW_FORK);
	काष्ठा xfs_bmbt_irec		got, del;
	काष्ठा xfs_iext_cursor		icur;
	पूर्णांक				error = 0;

	अगर (!xfs_inode_has_cow_data(ip))
		वापस 0;
	अगर (!xfs_iext_lookup_extent_beक्रमe(ip, अगरp, &end_fsb, &icur, &got))
		वापस 0;

	/* Walk backwards until we're out of the I/O range... */
	जबतक (got.br_startoff + got.br_blockcount > offset_fsb) अणु
		del = got;
		xfs_trim_extent(&del, offset_fsb, end_fsb - offset_fsb);

		/* Extent delete may have bumped ext क्रमward */
		अगर (!del.br_blockcount) अणु
			xfs_iext_prev(अगरp, &icur);
			जाओ next_extent;
		पूर्ण

		trace_xfs_reflink_cancel_cow(ip, &del);

		अगर (isnullstartblock(del.br_startblock)) अणु
			error = xfs_bmap_del_extent_delay(ip, XFS_COW_FORK,
					&icur, &got, &del);
			अगर (error)
				अवरोध;
		पूर्ण अन्यथा अगर (del.br_state == XFS_EXT_UNWRITTEN || cancel_real) अणु
			ASSERT((*tpp)->t_firstblock == शून्यFSBLOCK);

			/* Free the CoW orphan record. */
			xfs_refcount_मुक्त_cow_extent(*tpp, del.br_startblock,
					del.br_blockcount);

			xfs_bmap_add_मुक्त(*tpp, del.br_startblock,
					  del.br_blockcount, शून्य);

			/* Roll the transaction */
			error = xfs_defer_finish(tpp);
			अगर (error)
				अवरोध;

			/* Remove the mapping from the CoW विभाजन. */
			xfs_bmap_del_extent_cow(ip, &icur, &got, &del);

			/* Remove the quota reservation */
			error = xfs_quota_unreserve_blkres(ip,
					del.br_blockcount);
			अगर (error)
				अवरोध;
		पूर्ण अन्यथा अणु
			/* Didn't करो anything, push cursor back. */
			xfs_iext_prev(अगरp, &icur);
		पूर्ण
next_extent:
		अगर (!xfs_iext_get_extent(अगरp, &icur, &got))
			अवरोध;
	पूर्ण

	/* clear tag अगर cow विभाजन is emptied */
	अगर (!अगरp->अगर_bytes)
		xfs_inode_clear_cowblocks_tag(ip);
	वापस error;
पूर्ण

/*
 * Cancel CoW reservations क्रम some byte range of an inode.
 *
 * If cancel_real is true this function cancels all COW विभाजन extents क्रम the
 * inode; अगर cancel_real is false, real extents are not cleared.
 */
पूर्णांक
xfs_reflink_cancel_cow_range(
	काष्ठा xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		count,
	bool			cancel_real)
अणु
	काष्ठा xfs_trans	*tp;
	xfs_fileoff_t		offset_fsb;
	xfs_fileoff_t		end_fsb;
	पूर्णांक			error;

	trace_xfs_reflink_cancel_cow_range(ip, offset, count);
	ASSERT(ip->i_cowfp);

	offset_fsb = XFS_B_TO_FSBT(ip->i_mount, offset);
	अगर (count == शून्यखाताOFF)
		end_fsb = शून्यखाताOFF;
	अन्यथा
		end_fsb = XFS_B_TO_FSB(ip->i_mount, offset + count);

	/* Start a rolling transaction to हटाओ the mappings */
	error = xfs_trans_alloc(ip->i_mount, &M_RES(ip->i_mount)->tr_ग_लिखो,
			0, 0, 0, &tp);
	अगर (error)
		जाओ out;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	/* Scrape out the old CoW reservations */
	error = xfs_reflink_cancel_cow_blocks(ip, &tp, offset_fsb, end_fsb,
			cancel_real);
	अगर (error)
		जाओ out_cancel;

	error = xfs_trans_commit(tp);

	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;

out_cancel:
	xfs_trans_cancel(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
out:
	trace_xfs_reflink_cancel_cow_range_error(ip, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Remap part of the CoW विभाजन पूर्णांकo the data विभाजन.
 *
 * We aim to remap the range starting at @offset_fsb and ending at @end_fsb
 * पूर्णांकo the data विभाजन; this function will remap what it can (at the end of the
 * range) and update @end_fsb appropriately.  Each remap माला_लो its own
 * transaction because we can end up merging and splitting bmbt blocks क्रम
 * every remap operation and we'd like to keep the block reservation
 * requirements as low as possible.
 */
STATIC पूर्णांक
xfs_reflink_end_cow_extent(
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		offset_fsb,
	xfs_fileoff_t		*end_fsb)
अणु
	काष्ठा xfs_bmbt_irec	got, del;
	काष्ठा xfs_iext_cursor	icur;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, XFS_COW_FORK);
	xfs_filblks_t		rlen;
	अचिन्हित पूर्णांक		resblks;
	पूर्णांक			error;

	/* No COW extents?  That's easy! */
	अगर (अगरp->अगर_bytes == 0) अणु
		*end_fsb = offset_fsb;
		वापस 0;
	पूर्ण

	resblks = XFS_EXTENTADD_SPACE_RES(mp, XFS_DATA_FORK);
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ग_लिखो, resblks, 0,
			XFS_TRANS_RESERVE, &tp);
	अगर (error)
		वापस error;

	/*
	 * Lock the inode.  We have to ijoin without स्वतःmatic unlock because
	 * the lead transaction is the refcountbt record deletion; the data
	 * विभाजन update follows as a deferred log item.
	 */
	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	error = xfs_iext_count_may_overflow(ip, XFS_DATA_FORK,
			XFS_IEXT_REFLINK_END_COW_CNT);
	अगर (error)
		जाओ out_cancel;

	/*
	 * In हाल of racing, overlapping AIO ग_लिखोs no COW extents might be
	 * left by the समय I/O completes क्रम the loser of the race.  In that
	 * हाल we are करोne.
	 */
	अगर (!xfs_iext_lookup_extent_beक्रमe(ip, अगरp, end_fsb, &icur, &got) ||
	    got.br_startoff + got.br_blockcount <= offset_fsb) अणु
		*end_fsb = offset_fsb;
		जाओ out_cancel;
	पूर्ण

	/*
	 * Structure copy @got पूर्णांकo @del, then trim @del to the range that we
	 * were asked to remap.  We preserve @got क्रम the eventual CoW विभाजन
	 * deletion; from now on @del represents the mapping that we're
	 * actually remapping.
	 */
	del = got;
	xfs_trim_extent(&del, offset_fsb, *end_fsb - offset_fsb);

	ASSERT(del.br_blockcount > 0);

	/*
	 * Only remap real extents that contain data.  With AIO, speculative
	 * pपुनः_स्मृतिations can leak पूर्णांकo the range we are called upon, and we
	 * need to skip them.
	 */
	अगर (!xfs_bmap_is_written_extent(&got)) अणु
		*end_fsb = del.br_startoff;
		जाओ out_cancel;
	पूर्ण

	/* Unmap the old blocks in the data विभाजन. */
	rlen = del.br_blockcount;
	error = __xfs_bunmapi(tp, ip, del.br_startoff, &rlen, 0, 1);
	अगर (error)
		जाओ out_cancel;

	/* Trim the extent to whatever got unmapped. */
	xfs_trim_extent(&del, del.br_startoff + rlen, del.br_blockcount - rlen);
	trace_xfs_reflink_cow_remap(ip, &del);

	/* Free the CoW orphan record. */
	xfs_refcount_मुक्त_cow_extent(tp, del.br_startblock, del.br_blockcount);

	/* Map the new blocks पूर्णांकo the data विभाजन. */
	xfs_bmap_map_extent(tp, ip, &del);

	/* Charge this new data विभाजन mapping to the on-disk quota. */
	xfs_trans_mod_dquot_byino(tp, ip, XFS_TRANS_DQ_DELBCOUNT,
			(दीर्घ)del.br_blockcount);

	/* Remove the mapping from the CoW विभाजन. */
	xfs_bmap_del_extent_cow(ip, &icur, &got, &del);

	error = xfs_trans_commit(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	अगर (error)
		वापस error;

	/* Update the caller about how much progress we made. */
	*end_fsb = del.br_startoff;
	वापस 0;

out_cancel:
	xfs_trans_cancel(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

/*
 * Remap parts of a file's data विभाजन after a successful CoW.
 */
पूर्णांक
xfs_reflink_end_cow(
	काष्ठा xfs_inode		*ip,
	xfs_off_t			offset,
	xfs_off_t			count)
अणु
	xfs_fileoff_t			offset_fsb;
	xfs_fileoff_t			end_fsb;
	पूर्णांक				error = 0;

	trace_xfs_reflink_end_cow(ip, offset, count);

	offset_fsb = XFS_B_TO_FSBT(ip->i_mount, offset);
	end_fsb = XFS_B_TO_FSB(ip->i_mount, offset + count);

	/*
	 * Walk backwards until we're out of the I/O range.  The loop function
	 * repeatedly cycles the ILOCK to allocate one transaction per remapped
	 * extent.
	 *
	 * If we're being called by ग_लिखोback then the pages will still
	 * have PageWriteback set, which prevents races with reflink remapping
	 * and truncate.  Reflink remapping prevents races with ग_लिखोback by
	 * taking the iolock and mmaplock beक्रमe flushing the pages and
	 * remapping, which means there won't be any further ग_लिखोback or page
	 * cache dirtying until the reflink completes.
	 *
	 * We should never have two thपढ़ोs issuing ग_लिखोback क्रम the same file
	 * region.  There are also have post-eof checks in the ग_लिखोback
	 * preparation code so that we करोn't bother writing out pages that are
	 * about to be truncated.
	 *
	 * If we're being called as part of directio ग_लिखो completion, the dio
	 * count is still elevated, which reflink and truncate will रुको क्रम.
	 * Reflink remapping takes the iolock and mmaplock and रुकोs क्रम
	 * pending dio to finish, which should prevent any directio until the
	 * remap completes.  Multiple concurrent directio ग_लिखोs to the same
	 * region are handled by end_cow processing only occurring क्रम the
	 * thपढ़ोs which succeed; the outcome of multiple overlapping direct
	 * ग_लिखोs is not well defined anyway.
	 *
	 * It's possible that a buffered ग_लिखो and a direct ग_लिखो could collide
	 * here (the buffered ग_लिखो stumbles in after the dio flushes and
	 * invalidates the page cache and immediately queues ग_लिखोback), but we
	 * have never supported this 100%.  If either disk ग_लिखो succeeds the
	 * blocks will be remapped.
	 */
	जबतक (end_fsb > offset_fsb && !error)
		error = xfs_reflink_end_cow_extent(ip, offset_fsb, &end_fsb);

	अगर (error)
		trace_xfs_reflink_end_cow_error(ip, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Free leftover CoW reservations that didn't get cleaned out.
 */
पूर्णांक
xfs_reflink_recover_cow(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_agnumber_t		agno;
	पूर्णांक			error = 0;

	अगर (!xfs_sb_version_hasreflink(&mp->m_sb))
		वापस 0;

	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		error = xfs_refcount_recover_cow_leftovers(mp, agno);
		अगर (error)
			अवरोध;
	पूर्ण

	वापस error;
पूर्ण

/*
 * Reflinking (Block) Ranges of Two Files Together
 *
 * First, ensure that the reflink flag is set on both inodes.  The flag is an
 * optimization to aव्योम unnecessary refcount btree lookups in the ग_लिखो path.
 *
 * Now we can iteratively remap the range of extents (and holes) in src to the
 * corresponding ranges in dest.  Let drange and srange denote the ranges of
 * logical blocks in dest and src touched by the reflink operation.
 *
 * While the length of drange is greater than zero,
 *    - Read src's bmbt at the start of srange ("imap")
 *    - If imap करोesn't exist, make imap appear to start at the end of srange
 *      with zero length.
 *    - If imap starts beक्रमe srange, advance imap to start at srange.
 *    - If imap goes beyond srange, truncate imap to end at the end of srange.
 *    - Punch (imap start - srange start + imap len) blocks from dest at
 *      offset (drange start).
 *    - If imap poपूर्णांकs to a real range of pblks,
 *         > Increase the refcount of the imap's pblks
 *         > Map imap's pblks पूर्णांकo dest at the offset
 *           (drange start + imap start - srange start)
 *    - Advance drange and srange by (imap start - srange start + imap len)
 *
 * Finally, अगर the reflink made dest दीर्घer, update both the in-core and
 * on-disk file sizes.
 *
 * ASCII Art Demonstration:
 *
 * Let's say we want to reflink this source file:
 *
 * ----SSSSSSS-SSSSS----SSSSSS (src file)
 *   <-------------------->
 *
 * पूर्णांकo this destination file:
 *
 * --DDDDDDDDDDDDDDDDDDD--DDD (dest file)
 *        <-------------------->
 * '-' means a hole, and 'S' and 'D' are written blocks in the src and dest.
 * Observe that the range has dअगरferent logical offsets in either file.
 *
 * Consider that the first extent in the source file करोesn't line up with our
 * reflink range.  Unmapping  and remapping are separate operations, so we can
 * unmap more blocks from the destination file than we remap.
 *
 * ----SSSSSSS-SSSSS----SSSSSS
 *   <------->
 * --DDDDD---------DDDDD--DDD
 *        <------->
 *
 * Now remap the source extent पूर्णांकo the destination file:
 *
 * ----SSSSSSS-SSSSS----SSSSSS
 *   <------->
 * --DDDDD--SSSSSSSDDDDD--DDD
 *        <------->
 *
 * Do likewise with the second hole and extent in our range.  Holes in the
 * unmap range करोn't affect our operation.
 *
 * ----SSSSSSS-SSSSS----SSSSSS
 *            <---->
 * --DDDDD--SSSSSSS-SSSSS-DDD
 *                 <---->
 *
 * Finally, unmap and remap part of the third extent.  This will increase the
 * size of the destination file.
 *
 * ----SSSSSSS-SSSSS----SSSSSS
 *                  <----->
 * --DDDDD--SSSSSSS-SSSSS----SSS
 *                       <----->
 *
 * Once we update the destination file's i_size, we're करोne.
 */

/*
 * Ensure the reflink bit is set in both inodes.
 */
STATIC पूर्णांक
xfs_reflink_set_inode_flag(
	काष्ठा xfs_inode	*src,
	काष्ठा xfs_inode	*dest)
अणु
	काष्ठा xfs_mount	*mp = src->i_mount;
	पूर्णांक			error;
	काष्ठा xfs_trans	*tp;

	अगर (xfs_is_reflink_inode(src) && xfs_is_reflink_inode(dest))
		वापस 0;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ichange, 0, 0, 0, &tp);
	अगर (error)
		जाओ out_error;

	/* Lock both files against IO */
	अगर (src->i_ino == dest->i_ino)
		xfs_ilock(src, XFS_ILOCK_EXCL);
	अन्यथा
		xfs_lock_two_inodes(src, XFS_ILOCK_EXCL, dest, XFS_ILOCK_EXCL);

	अगर (!xfs_is_reflink_inode(src)) अणु
		trace_xfs_reflink_set_inode_flag(src);
		xfs_trans_ijoin(tp, src, XFS_ILOCK_EXCL);
		src->i_dअगरlags2 |= XFS_DIFLAG2_REFLINK;
		xfs_trans_log_inode(tp, src, XFS_ILOG_CORE);
		xfs_अगरork_init_cow(src);
	पूर्ण अन्यथा
		xfs_iunlock(src, XFS_ILOCK_EXCL);

	अगर (src->i_ino == dest->i_ino)
		जाओ commit_flags;

	अगर (!xfs_is_reflink_inode(dest)) अणु
		trace_xfs_reflink_set_inode_flag(dest);
		xfs_trans_ijoin(tp, dest, XFS_ILOCK_EXCL);
		dest->i_dअगरlags2 |= XFS_DIFLAG2_REFLINK;
		xfs_trans_log_inode(tp, dest, XFS_ILOG_CORE);
		xfs_अगरork_init_cow(dest);
	पूर्ण अन्यथा
		xfs_iunlock(dest, XFS_ILOCK_EXCL);

commit_flags:
	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ out_error;
	वापस error;

out_error:
	trace_xfs_reflink_set_inode_flag_error(dest, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Update destination inode size & cowextsize hपूर्णांक, अगर necessary.
 */
पूर्णांक
xfs_reflink_update_dest(
	काष्ठा xfs_inode	*dest,
	xfs_off_t		newlen,
	xfs_extlen_t		cowextsize,
	अचिन्हित पूर्णांक		remap_flags)
अणु
	काष्ठा xfs_mount	*mp = dest->i_mount;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;

	अगर (newlen <= i_size_पढ़ो(VFS_I(dest)) && cowextsize == 0)
		वापस 0;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ichange, 0, 0, 0, &tp);
	अगर (error)
		जाओ out_error;

	xfs_ilock(dest, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, dest, XFS_ILOCK_EXCL);

	अगर (newlen > i_size_पढ़ो(VFS_I(dest))) अणु
		trace_xfs_reflink_update_inode_size(dest, newlen);
		i_size_ग_लिखो(VFS_I(dest), newlen);
		dest->i_disk_size = newlen;
	पूर्ण

	अगर (cowextsize) अणु
		dest->i_cowextsize = cowextsize;
		dest->i_dअगरlags2 |= XFS_DIFLAG2_COWEXTSIZE;
	पूर्ण

	xfs_trans_log_inode(tp, dest, XFS_ILOG_CORE);

	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ out_error;
	वापस error;

out_error:
	trace_xfs_reflink_update_inode_size_error(dest, error, _RET_IP_);
	वापस error;
पूर्ण

/*
 * Do we have enough reserve in this AG to handle a reflink?  The refcount
 * btree alपढ़ोy reserved all the space it needs, but the rmap btree can grow
 * infinitely, so we won't allow more reflinks when the AG is करोwn to the
 * btree reserves.
 */
अटल पूर्णांक
xfs_reflink_ag_has_मुक्त_space(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno)
अणु
	काष्ठा xfs_perag	*pag;
	पूर्णांक			error = 0;

	अगर (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस 0;

	pag = xfs_perag_get(mp, agno);
	अगर (xfs_ag_resv_critical(pag, XFS_AG_RESV_RMAPBT) ||
	    xfs_ag_resv_critical(pag, XFS_AG_RESV_METADATA))
		error = -ENOSPC;
	xfs_perag_put(pag);
	वापस error;
पूर्ण

/*
 * Remap the given extent पूर्णांकo the file.  The dmap blockcount will be set to
 * the number of blocks that were actually remapped.
 */
STATIC पूर्णांक
xfs_reflink_remap_extent(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_bmbt_irec	*dmap,
	xfs_off_t		new_isize)
अणु
	काष्ठा xfs_bmbt_irec	smap;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	xfs_off_t		newlen;
	पूर्णांक64_t			qdelta = 0;
	अचिन्हित पूर्णांक		resblks;
	bool			quota_reserved = true;
	bool			smap_real;
	bool			dmap_written = xfs_bmap_is_written_extent(dmap);
	पूर्णांक			iext_delta = 0;
	पूर्णांक			nimaps;
	पूर्णांक			error;

	/*
	 * Start a rolling transaction to चयन the mappings.
	 *
	 * Adding a written extent to the extent map can cause a bmbt split,
	 * and removing a mapped extent from the extent can cause a bmbt split.
	 * The two operations cannot both cause a split since they operate on
	 * the same index in the bmap btree, so we only need a reservation क्रम
	 * one bmbt split अगर either thing is happening.  However, we haven't
	 * locked the inode yet, so we reserve assuming this is the हाल.
	 *
	 * The first allocation call tries to reserve enough space to handle
	 * mapping dmap पूर्णांकo a sparse part of the file plus the bmbt split.  We
	 * haven't locked the inode or पढ़ो the existing mapping yet, so we करो
	 * not know क्रम sure that we need the space.  This should succeed most
	 * of the समय.
	 *
	 * If the first attempt fails, try again but reserving only enough
	 * space to handle a bmbt split.  This is the hard minimum requirement,
	 * and we revisit quota reservations later when we know more about what
	 * we're remapping.
	 */
	resblks = XFS_EXTENTADD_SPACE_RES(mp, XFS_DATA_FORK);
	error = xfs_trans_alloc_inode(ip, &M_RES(mp)->tr_ग_लिखो,
			resblks + dmap->br_blockcount, 0, false, &tp);
	अगर (error == -EDQUOT || error == -ENOSPC) अणु
		quota_reserved = false;
		error = xfs_trans_alloc_inode(ip, &M_RES(mp)->tr_ग_लिखो,
				resblks, 0, false, &tp);
	पूर्ण
	अगर (error)
		जाओ out;

	/*
	 * Read what's currently mapped in the destination file पूर्णांकo smap.
	 * If smap isn't a hole, we will have to हटाओ it beक्रमe we can add
	 * dmap to the destination file.
	 */
	nimaps = 1;
	error = xfs_bmapi_पढ़ो(ip, dmap->br_startoff, dmap->br_blockcount,
			&smap, &nimaps, 0);
	अगर (error)
		जाओ out_cancel;
	ASSERT(nimaps == 1 && smap.br_startoff == dmap->br_startoff);
	smap_real = xfs_bmap_is_real_extent(&smap);

	/*
	 * We can only remap as many blocks as the smaller of the two extent
	 * maps, because we can only remap one extent at a समय.
	 */
	dmap->br_blockcount = min(dmap->br_blockcount, smap.br_blockcount);
	ASSERT(dmap->br_blockcount == smap.br_blockcount);

	trace_xfs_reflink_remap_extent_dest(ip, &smap);

	/*
	 * Two extents mapped to the same physical block must not have
	 * dअगरferent states; that's fileप्रणाली corruption.  Move on to the next
	 * extent अगर they're both holes or both the same physical extent.
	 */
	अगर (dmap->br_startblock == smap.br_startblock) अणु
		अगर (dmap->br_state != smap.br_state)
			error = -EFSCORRUPTED;
		जाओ out_cancel;
	पूर्ण

	/* If both extents are unwritten, leave them alone. */
	अगर (dmap->br_state == XFS_EXT_UNWRITTEN &&
	    smap.br_state == XFS_EXT_UNWRITTEN)
		जाओ out_cancel;

	/* No reflinking अगर the AG of the dest mapping is low on space. */
	अगर (dmap_written) अणु
		error = xfs_reflink_ag_has_मुक्त_space(mp,
				XFS_FSB_TO_AGNO(mp, dmap->br_startblock));
		अगर (error)
			जाओ out_cancel;
	पूर्ण

	/*
	 * Increase quota reservation अगर we think the quota block counter क्रम
	 * this file could increase.
	 *
	 * If we are mapping a written extent पूर्णांकo the file, we need to have
	 * enough quota block count reservation to handle the blocks in that
	 * extent.  We log only the delta to the quota block counts, so अगर the
	 * extent we're unmapping also has blocks allocated to it, we don't
	 * need a quota reservation क्रम the extent itself.
	 *
	 * Note that अगर we're replacing a delalloc reservation with a written
	 * extent, we have to take the full quota reservation because removing
	 * the delalloc reservation gives the block count back to the quota
	 * count.  This is suboptimal, but the VFS flushed the dest range
	 * beक्रमe we started.  That should have हटाओd all the delalloc
	 * reservations, but we code defensively.
	 *
	 * xfs_trans_alloc_inode above alपढ़ोy tried to grab an even larger
	 * quota reservation, and kicked off a blockgc scan अगर it couldn't.
	 * If we can't get a potentially smaller quota reservation now, we're
	 * करोne.
	 */
	अगर (!quota_reserved && !smap_real && dmap_written) अणु
		error = xfs_trans_reserve_quota_nblks(tp, ip,
				dmap->br_blockcount, 0, false);
		अगर (error)
			जाओ out_cancel;
	पूर्ण

	अगर (smap_real)
		++iext_delta;

	अगर (dmap_written)
		++iext_delta;

	error = xfs_iext_count_may_overflow(ip, XFS_DATA_FORK, iext_delta);
	अगर (error)
		जाओ out_cancel;

	अगर (smap_real) अणु
		/*
		 * If the extent we're unmapping is backed by storage (written
		 * or not), unmap the extent and drop its refcount.
		 */
		xfs_bmap_unmap_extent(tp, ip, &smap);
		xfs_refcount_decrease_extent(tp, &smap);
		qdelta -= smap.br_blockcount;
	पूर्ण अन्यथा अगर (smap.br_startblock == DELAYSTARTBLOCK) अणु
		xfs_filblks_t	len = smap.br_blockcount;

		/*
		 * If the extent we're unmapping is a delalloc reservation,
		 * we can use the regular bunmapi function to release the
		 * incore state.  Dropping the delalloc reservation takes care
		 * of the quota reservation क्रम us.
		 */
		error = __xfs_bunmapi(शून्य, ip, smap.br_startoff, &len, 0, 1);
		अगर (error)
			जाओ out_cancel;
		ASSERT(len == 0);
	पूर्ण

	/*
	 * If the extent we're sharing is backed by written storage, increase
	 * its refcount and map it पूर्णांकo the file.
	 */
	अगर (dmap_written) अणु
		xfs_refcount_increase_extent(tp, dmap);
		xfs_bmap_map_extent(tp, ip, dmap);
		qdelta += dmap->br_blockcount;
	पूर्ण

	xfs_trans_mod_dquot_byino(tp, ip, XFS_TRANS_DQ_BCOUNT, qdelta);

	/* Update dest isize अगर needed. */
	newlen = XFS_FSB_TO_B(mp, dmap->br_startoff + dmap->br_blockcount);
	newlen = min_t(xfs_off_t, newlen, new_isize);
	अगर (newlen > i_size_पढ़ो(VFS_I(ip))) अणु
		trace_xfs_reflink_update_inode_size(ip, newlen);
		i_size_ग_लिखो(VFS_I(ip), newlen);
		ip->i_disk_size = newlen;
		xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	पूर्ण

	/* Commit everything and unlock. */
	error = xfs_trans_commit(tp);
	जाओ out_unlock;

out_cancel:
	xfs_trans_cancel(tp);
out_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
out:
	अगर (error)
		trace_xfs_reflink_remap_extent_error(ip, error, _RET_IP_);
	वापस error;
पूर्ण

/* Remap a range of one file to the other. */
पूर्णांक
xfs_reflink_remap_blocks(
	काष्ठा xfs_inode	*src,
	loff_t			pos_in,
	काष्ठा xfs_inode	*dest,
	loff_t			pos_out,
	loff_t			remap_len,
	loff_t			*remapped)
अणु
	काष्ठा xfs_bmbt_irec	imap;
	काष्ठा xfs_mount	*mp = src->i_mount;
	xfs_fileoff_t		srcoff = XFS_B_TO_FSBT(mp, pos_in);
	xfs_fileoff_t		destoff = XFS_B_TO_FSBT(mp, pos_out);
	xfs_filblks_t		len;
	xfs_filblks_t		remapped_len = 0;
	xfs_off_t		new_isize = pos_out + remap_len;
	पूर्णांक			nimaps;
	पूर्णांक			error = 0;

	len = min_t(xfs_filblks_t, XFS_B_TO_FSB(mp, remap_len),
			XFS_MAX_खाताOFF);

	trace_xfs_reflink_remap_blocks(src, srcoff, len, dest, destoff);

	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक	lock_mode;

		/* Read extent from the source file */
		nimaps = 1;
		lock_mode = xfs_ilock_data_map_shared(src);
		error = xfs_bmapi_पढ़ो(src, srcoff, len, &imap, &nimaps, 0);
		xfs_iunlock(src, lock_mode);
		अगर (error)
			अवरोध;
		/*
		 * The caller supposedly flushed all dirty pages in the source
		 * file range, which means that ग_लिखोback should have allocated
		 * or deleted all delalloc reservations in that range.  If we
		 * find one, that's a good sign that something is seriously
		 * wrong here.
		 */
		ASSERT(nimaps == 1 && imap.br_startoff == srcoff);
		अगर (imap.br_startblock == DELAYSTARTBLOCK) अणु
			ASSERT(imap.br_startblock != DELAYSTARTBLOCK);
			error = -EFSCORRUPTED;
			अवरोध;
		पूर्ण

		trace_xfs_reflink_remap_extent_src(src, &imap);

		/* Remap पूर्णांकo the destination file at the given offset. */
		imap.br_startoff = destoff;
		error = xfs_reflink_remap_extent(dest, &imap, new_isize);
		अगर (error)
			अवरोध;

		अगर (fatal_संकेत_pending(current)) अणु
			error = -EINTR;
			अवरोध;
		पूर्ण

		/* Advance drange/srange */
		srcoff += imap.br_blockcount;
		destoff += imap.br_blockcount;
		len -= imap.br_blockcount;
		remapped_len += imap.br_blockcount;
	पूर्ण

	अगर (error)
		trace_xfs_reflink_remap_blocks_error(dest, error, _RET_IP_);
	*remapped = min_t(loff_t, remap_len,
			  XFS_FSB_TO_B(src->i_mount, remapped_len));
	वापस error;
पूर्ण

/*
 * If we're reflinking to a point past the destination file's खातापूर्ण, we must
 * zero any speculative post-खातापूर्ण pपुनः_स्मृतिations that sit between the old खातापूर्ण
 * and the destination file offset.
 */
अटल पूर्णांक
xfs_reflink_zero_posteof(
	काष्ठा xfs_inode	*ip,
	loff_t			pos)
अणु
	loff_t			isize = i_size_पढ़ो(VFS_I(ip));

	अगर (pos <= isize)
		वापस 0;

	trace_xfs_zero_eof(ip, isize, pos - isize);
	वापस iomap_zero_range(VFS_I(ip), isize, pos - isize, शून्य,
			&xfs_buffered_ग_लिखो_iomap_ops);
पूर्ण

/*
 * Prepare two files क्रम range cloning.  Upon a successful वापस both inodes
 * will have the iolock and mmaplock held, the page cache of the out file will
 * be truncated, and any leases on the out file will have been broken.  This
 * function borrows heavily from xfs_file_aio_ग_लिखो_checks.
 *
 * The VFS allows partial खातापूर्ण blocks to "match" क्रम dedupe even though it hasn't
 * checked that the bytes beyond खातापूर्ण physically match. Hence we cannot use the
 * खातापूर्ण block in the source dedupe range because it's not a complete block match,
 * hence can पूर्णांकroduce a corruption पूर्णांकo the file that has it's block replaced.
 *
 * In similar fashion, the VFS file cloning also allows partial खातापूर्ण blocks to be
 * "block aligned" क्रम the purposes of cloning entire files.  However, अगर the
 * source file range includes the खातापूर्ण block and it lands within the existing खातापूर्ण
 * of the destination file, then we can expose stale data from beyond the source
 * file खातापूर्ण in the destination file.
 *
 * XFS करोesn't support partial block sharing, so in both हालs we have check
 * these हालs ourselves. For dedupe, we can simply round the length to dedupe
 * करोwn to the previous whole block and ignore the partial खातापूर्ण block. While this
 * means we can't dedupe the last block of a file, this is an acceptible
 * tradeoff क्रम simplicity on implementation.
 *
 * For cloning, we want to share the partial खातापूर्ण block अगर it is also the new खातापूर्ण
 * block of the destination file. If the partial खातापूर्ण block lies inside the
 * existing destination खातापूर्ण, then we have to पात the clone to aव्योम exposing
 * stale data in the destination file. Hence we reject these clone attempts with
 * -EINVAL in this हाल.
 */
पूर्णांक
xfs_reflink_remap_prep(
	काष्ठा file		*file_in,
	loff_t			pos_in,
	काष्ठा file		*file_out,
	loff_t			pos_out,
	loff_t			*len,
	अचिन्हित पूर्णांक		remap_flags)
अणु
	काष्ठा inode		*inode_in = file_inode(file_in);
	काष्ठा xfs_inode	*src = XFS_I(inode_in);
	काष्ठा inode		*inode_out = file_inode(file_out);
	काष्ठा xfs_inode	*dest = XFS_I(inode_out);
	पूर्णांक			ret;

	/* Lock both files against IO */
	ret = xfs_ilock2_io_mmap(src, dest);
	अगर (ret)
		वापस ret;

	/* Check file eligibility and prepare क्रम block sharing. */
	ret = -EINVAL;
	/* Don't reflink realसमय inodes */
	अगर (XFS_IS_REALTIME_INODE(src) || XFS_IS_REALTIME_INODE(dest))
		जाओ out_unlock;

	/* Don't share DAX file data क्रम now. */
	अगर (IS_DAX(inode_in) || IS_DAX(inode_out))
		जाओ out_unlock;

	ret = generic_remap_file_range_prep(file_in, pos_in, file_out, pos_out,
			len, remap_flags);
	अगर (ret || *len == 0)
		जाओ out_unlock;

	/* Attach dquots to dest inode beक्रमe changing block map */
	ret = xfs_qm_dqattach(dest);
	अगर (ret)
		जाओ out_unlock;

	/*
	 * Zero existing post-eof speculative pपुनः_स्मृतिations in the destination
	 * file.
	 */
	ret = xfs_reflink_zero_posteof(dest, pos_out);
	अगर (ret)
		जाओ out_unlock;

	/* Set flags and remap blocks. */
	ret = xfs_reflink_set_inode_flag(src, dest);
	अगर (ret)
		जाओ out_unlock;

	/*
	 * If pos_out > खातापूर्ण, we may have dirtied blocks between खातापूर्ण and
	 * pos_out. In that हाल, we need to extend the flush and unmap to cover
	 * from खातापूर्ण to the end of the copy length.
	 */
	अगर (pos_out > XFS_ISIZE(dest)) अणु
		loff_t	flen = *len + (pos_out - XFS_ISIZE(dest));
		ret = xfs_flush_unmap_range(dest, XFS_ISIZE(dest), flen);
	पूर्ण अन्यथा अणु
		ret = xfs_flush_unmap_range(dest, pos_out, *len);
	पूर्ण
	अगर (ret)
		जाओ out_unlock;

	वापस 0;
out_unlock:
	xfs_iunlock2_io_mmap(src, dest);
	वापस ret;
पूर्ण

/* Does this inode need the reflink flag? */
पूर्णांक
xfs_reflink_inode_has_shared_extents(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_inode		*ip,
	bool				*has_shared)
अणु
	काष्ठा xfs_bmbt_irec		got;
	काष्ठा xfs_mount		*mp = ip->i_mount;
	काष्ठा xfs_अगरork		*अगरp;
	xfs_agnumber_t			agno;
	xfs_agblock_t			agbno;
	xfs_extlen_t			aglen;
	xfs_agblock_t			rbno;
	xfs_extlen_t			rlen;
	काष्ठा xfs_iext_cursor		icur;
	bool				found;
	पूर्णांक				error;

	अगरp = XFS_IFORK_PTR(ip, XFS_DATA_FORK);
	error = xfs_iपढ़ो_extents(tp, ip, XFS_DATA_FORK);
	अगर (error)
		वापस error;

	*has_shared = false;
	found = xfs_iext_lookup_extent(ip, अगरp, 0, &icur, &got);
	जबतक (found) अणु
		अगर (isnullstartblock(got.br_startblock) ||
		    got.br_state != XFS_EXT_NORM)
			जाओ next;
		agno = XFS_FSB_TO_AGNO(mp, got.br_startblock);
		agbno = XFS_FSB_TO_AGBNO(mp, got.br_startblock);
		aglen = got.br_blockcount;

		error = xfs_reflink_find_shared(mp, tp, agno, agbno, aglen,
				&rbno, &rlen, false);
		अगर (error)
			वापस error;
		/* Is there still a shared block here? */
		अगर (rbno != शून्यAGBLOCK) अणु
			*has_shared = true;
			वापस 0;
		पूर्ण
next:
		found = xfs_iext_next_extent(अगरp, &icur, &got);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Clear the inode reflink flag अगर there are no shared extents.
 *
 * The caller is responsible क्रम joining the inode to the transaction passed in.
 * The inode will be joined to the transaction that is वापसed to the caller.
 */
पूर्णांक
xfs_reflink_clear_inode_flag(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_trans	**tpp)
अणु
	bool			needs_flag;
	पूर्णांक			error = 0;

	ASSERT(xfs_is_reflink_inode(ip));

	error = xfs_reflink_inode_has_shared_extents(*tpp, ip, &needs_flag);
	अगर (error || needs_flag)
		वापस error;

	/*
	 * We didn't find any shared blocks so turn off the reflink flag.
	 * First, get rid of any leftover CoW mappings.
	 */
	error = xfs_reflink_cancel_cow_blocks(ip, tpp, 0, XFS_MAX_खाताOFF,
			true);
	अगर (error)
		वापस error;

	/* Clear the inode flag. */
	trace_xfs_reflink_unset_inode_flag(ip);
	ip->i_dअगरlags2 &= ~XFS_DIFLAG2_REFLINK;
	xfs_inode_clear_cowblocks_tag(ip);
	xfs_trans_log_inode(*tpp, ip, XFS_ILOG_CORE);

	वापस error;
पूर्ण

/*
 * Clear the inode reflink flag अगर there are no shared extents and the size
 * hasn't changed.
 */
STATIC पूर्णांक
xfs_reflink_try_clear_inode_flag(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error = 0;

	/* Start a rolling transaction to हटाओ the mappings */
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ग_लिखो, 0, 0, 0, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	error = xfs_reflink_clear_inode_flag(ip, &tp);
	अगर (error)
		जाओ cancel;

	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ out;

	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस 0;
cancel:
	xfs_trans_cancel(tp);
out:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

/*
 * Pre-COW all shared blocks within a given byte range of a file and turn off
 * the reflink flag अगर we unshare all of the file's blocks.
 */
पूर्णांक
xfs_reflink_unshare(
	काष्ठा xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		len)
अणु
	काष्ठा inode		*inode = VFS_I(ip);
	पूर्णांक			error;

	अगर (!xfs_is_reflink_inode(ip))
		वापस 0;

	trace_xfs_reflink_unshare(ip, offset, len);

	inode_dio_रुको(inode);

	error = iomap_file_unshare(inode, offset, len,
			&xfs_buffered_ग_लिखो_iomap_ops);
	अगर (error)
		जाओ out;

	error = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, offset,
			offset + len - 1);
	अगर (error)
		जाओ out;

	/* Turn off the reflink flag अगर possible. */
	error = xfs_reflink_try_clear_inode_flag(ip);
	अगर (error)
		जाओ out;
	वापस 0;

out:
	trace_xfs_reflink_unshare_error(ip, error, _RET_IP_);
	वापस error;
पूर्ण
