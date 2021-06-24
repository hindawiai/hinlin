<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * Copyright (c) 2016-2018 Christoph Hellwig.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_util.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_inode_item.h"
#समावेश "xfs_iomap.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_dquot_item.h"
#समावेश "xfs_dquot.h"
#समावेश "xfs_reflink.h"


#घोषणा XFS_ALLOC_ALIGN(mp, off) \
	(((off) >> mp->m_allocsize_log) << mp->m_allocsize_log)

अटल पूर्णांक
xfs_alert_fsblock_zero(
	xfs_inode_t	*ip,
	xfs_bmbt_irec_t	*imap)
अणु
	xfs_alert_tag(ip->i_mount, XFS_PTAG_FSBLOCK_ZERO,
			"Access to block zero in inode %llu "
			"start_block: %llx start_off: %llx "
			"blkcnt: %llx extent-state: %x",
		(अचिन्हित दीर्घ दीर्घ)ip->i_ino,
		(अचिन्हित दीर्घ दीर्घ)imap->br_startblock,
		(अचिन्हित दीर्घ दीर्घ)imap->br_startoff,
		(अचिन्हित दीर्घ दीर्घ)imap->br_blockcount,
		imap->br_state);
	वापस -EFSCORRUPTED;
पूर्ण

पूर्णांक
xfs_bmbt_to_iomap(
	काष्ठा xfs_inode	*ip,
	काष्ठा iomap		*iomap,
	काष्ठा xfs_bmbt_irec	*imap,
	u16			flags)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_buftarg	*target = xfs_inode_buftarg(ip);

	अगर (unlikely(!xfs_valid_startblock(ip, imap->br_startblock)))
		वापस xfs_alert_fsblock_zero(ip, imap);

	अगर (imap->br_startblock == HOLESTARTBLOCK) अणु
		iomap->addr = IOMAP_शून्य_ADDR;
		iomap->type = IOMAP_HOLE;
	पूर्ण अन्यथा अगर (imap->br_startblock == DELAYSTARTBLOCK ||
		   isnullstartblock(imap->br_startblock)) अणु
		iomap->addr = IOMAP_शून्य_ADDR;
		iomap->type = IOMAP_DELALLOC;
	पूर्ण अन्यथा अणु
		iomap->addr = BBTOB(xfs_fsb_to_db(ip, imap->br_startblock));
		अगर (imap->br_state == XFS_EXT_UNWRITTEN)
			iomap->type = IOMAP_UNWRITTEN;
		अन्यथा
			iomap->type = IOMAP_MAPPED;
	पूर्ण
	iomap->offset = XFS_FSB_TO_B(mp, imap->br_startoff);
	iomap->length = XFS_FSB_TO_B(mp, imap->br_blockcount);
	iomap->bdev = target->bt_bdev;
	iomap->dax_dev = target->bt_daxdev;
	iomap->flags = flags;

	अगर (xfs_ipincount(ip) &&
	    (ip->i_itemp->ili_fsync_fields & ~XFS_ILOG_TIMESTAMP))
		iomap->flags |= IOMAP_F_सूचीTY;
	वापस 0;
पूर्ण

अटल व्योम
xfs_hole_to_iomap(
	काष्ठा xfs_inode	*ip,
	काष्ठा iomap		*iomap,
	xfs_fileoff_t		offset_fsb,
	xfs_fileoff_t		end_fsb)
अणु
	काष्ठा xfs_buftarg	*target = xfs_inode_buftarg(ip);

	iomap->addr = IOMAP_शून्य_ADDR;
	iomap->type = IOMAP_HOLE;
	iomap->offset = XFS_FSB_TO_B(ip->i_mount, offset_fsb);
	iomap->length = XFS_FSB_TO_B(ip->i_mount, end_fsb - offset_fsb);
	iomap->bdev = target->bt_bdev;
	iomap->dax_dev = target->bt_daxdev;
पूर्ण

अटल अंतरभूत xfs_fileoff_t
xfs_iomap_end_fsb(
	काष्ठा xfs_mount	*mp,
	loff_t			offset,
	loff_t			count)
अणु
	ASSERT(offset <= mp->m_super->s_maxbytes);
	वापस min(XFS_B_TO_FSB(mp, offset + count),
		   XFS_B_TO_FSB(mp, mp->m_super->s_maxbytes));
पूर्ण

अटल xfs_extlen_t
xfs_eof_alignment(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_extlen_t		align = 0;

	अगर (!XFS_IS_REALTIME_INODE(ip)) अणु
		/*
		 * Round up the allocation request to a stripe unit
		 * (m_dalign) boundary अगर the file size is >= stripe unit
		 * size, and we are allocating past the allocation eof.
		 *
		 * If mounted with the "-o swalloc" option the alignment is
		 * increased from the strip unit size to the stripe width.
		 */
		अगर (mp->m_swidth && (mp->m_flags & XFS_MOUNT_SWALLOC))
			align = mp->m_swidth;
		अन्यथा अगर (mp->m_dalign)
			align = mp->m_dalign;

		अगर (align && XFS_ISIZE(ip) < XFS_FSB_TO_B(mp, align))
			align = 0;
	पूर्ण

	वापस align;
पूर्ण

/*
 * Check अगर last_fsb is outside the last extent, and अगर so grow it to the next
 * stripe unit boundary.
 */
xfs_fileoff_t
xfs_iomap_eof_align_last_fsb(
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		end_fsb)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, XFS_DATA_FORK);
	xfs_extlen_t		extsz = xfs_get_extsz_hपूर्णांक(ip);
	xfs_extlen_t		align = xfs_eof_alignment(ip);
	काष्ठा xfs_bmbt_irec	irec;
	काष्ठा xfs_iext_cursor	icur;

	ASSERT(!xfs_need_iपढ़ो_extents(अगरp));

	/*
	 * Always round up the allocation request to the extent hपूर्णांक boundary.
	 */
	अगर (extsz) अणु
		अगर (align)
			align = roundup_64(align, extsz);
		अन्यथा
			align = extsz;
	पूर्ण

	अगर (align) अणु
		xfs_fileoff_t	aligned_end_fsb = roundup_64(end_fsb, align);

		xfs_iext_last(अगरp, &icur);
		अगर (!xfs_iext_get_extent(अगरp, &icur, &irec) ||
		    aligned_end_fsb >= irec.br_startoff + irec.br_blockcount)
			वापस aligned_end_fsb;
	पूर्ण

	वापस end_fsb;
पूर्ण

पूर्णांक
xfs_iomap_ग_लिखो_direct(
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		offset_fsb,
	xfs_fileoff_t		count_fsb,
	काष्ठा xfs_bmbt_irec	*imap)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	xfs_filblks_t		resaligned;
	पूर्णांक			nimaps;
	अचिन्हित पूर्णांक		dblocks, rblocks;
	bool			क्रमce = false;
	पूर्णांक			error;
	पूर्णांक			bmapi_flags = XFS_BMAPI_PREALLOC;
	पूर्णांक			nr_exts = XFS_IEXT_ADD_NOSPLIT_CNT;

	ASSERT(count_fsb > 0);

	resaligned = xfs_aligned_fsb_count(offset_fsb, count_fsb,
					   xfs_get_extsz_hपूर्णांक(ip));
	अगर (unlikely(XFS_IS_REALTIME_INODE(ip))) अणु
		dblocks = XFS_DIOSTRAT_SPACE_RES(mp, 0);
		rblocks = resaligned;
	पूर्ण अन्यथा अणु
		dblocks = XFS_DIOSTRAT_SPACE_RES(mp, resaligned);
		rblocks = 0;
	पूर्ण

	error = xfs_qm_dqattach(ip);
	अगर (error)
		वापस error;

	/*
	 * For DAX, we करो not allocate unwritten extents, but instead we zero
	 * the block beक्रमe we commit the transaction.  Ideally we'd like to करो
	 * this outside the transaction context, but अगर we commit and then crash
	 * we may not have zeroed the blocks and this will be exposed on
	 * recovery of the allocation. Hence we must zero beक्रमe commit.
	 *
	 * Further, अगर we are mapping unwritten extents here, we need to zero
	 * and convert them to written so that we करोn't need an unwritten extent
	 * callback क्रम DAX. This also means that we need to be able to dip पूर्णांकo
	 * the reserve block pool क्रम bmbt block allocation अगर there is no space
	 * left but we need to करो unwritten extent conversion.
	 */
	अगर (IS_DAX(VFS_I(ip))) अणु
		bmapi_flags = XFS_BMAPI_CONVERT | XFS_BMAPI_ZERO;
		अगर (imap->br_state == XFS_EXT_UNWRITTEN) अणु
			क्रमce = true;
			nr_exts = XFS_IEXT_WRITE_UNWRITTEN_CNT;
			dblocks = XFS_DIOSTRAT_SPACE_RES(mp, 0) << 1;
		पूर्ण
	पूर्ण

	error = xfs_trans_alloc_inode(ip, &M_RES(mp)->tr_ग_लिखो, dblocks,
			rblocks, क्रमce, &tp);
	अगर (error)
		वापस error;

	error = xfs_iext_count_may_overflow(ip, XFS_DATA_FORK, nr_exts);
	अगर (error)
		जाओ out_trans_cancel;

	/*
	 * From this poपूर्णांक onwards we overग_लिखो the imap poपूर्णांकer that the
	 * caller gave to us.
	 */
	nimaps = 1;
	error = xfs_bmapi_ग_लिखो(tp, ip, offset_fsb, count_fsb, bmapi_flags, 0,
				imap, &nimaps);
	अगर (error)
		जाओ out_trans_cancel;

	/*
	 * Complete the transaction
	 */
	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ out_unlock;

	/*
	 * Copy any maps to caller's array and वापस any error.
	 */
	अगर (nimaps == 0) अणु
		error = -ENOSPC;
		जाओ out_unlock;
	पूर्ण

	अगर (unlikely(!xfs_valid_startblock(ip, imap->br_startblock)))
		error = xfs_alert_fsblock_zero(ip, imap);

out_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;

out_trans_cancel:
	xfs_trans_cancel(tp);
	जाओ out_unlock;
पूर्ण

STATIC bool
xfs_quota_need_throttle(
	काष्ठा xfs_inode	*ip,
	xfs_dqtype_t		type,
	xfs_fsblock_t		alloc_blocks)
अणु
	काष्ठा xfs_dquot	*dq = xfs_inode_dquot(ip, type);

	अगर (!dq || !xfs_this_quota_on(ip->i_mount, type))
		वापस false;

	/* no hi watermark, no throttle */
	अगर (!dq->q_pपुनः_स्मृति_hi_wmark)
		वापस false;

	/* under the lo watermark, no throttle */
	अगर (dq->q_blk.reserved + alloc_blocks < dq->q_pपुनः_स्मृति_lo_wmark)
		वापस false;

	वापस true;
पूर्ण

STATIC व्योम
xfs_quota_calc_throttle(
	काष्ठा xfs_inode	*ip,
	xfs_dqtype_t		type,
	xfs_fsblock_t		*qblocks,
	पूर्णांक			*qshअगरt,
	पूर्णांक64_t			*qमुक्तsp)
अणु
	काष्ठा xfs_dquot	*dq = xfs_inode_dquot(ip, type);
	पूर्णांक64_t			मुक्तsp;
	पूर्णांक			shअगरt = 0;

	/* no dq, or over hi wmark, squash the pपुनः_स्मृति completely */
	अगर (!dq || dq->q_blk.reserved >= dq->q_pपुनः_स्मृति_hi_wmark) अणु
		*qblocks = 0;
		*qमुक्तsp = 0;
		वापस;
	पूर्ण

	मुक्तsp = dq->q_pपुनः_स्मृति_hi_wmark - dq->q_blk.reserved;
	अगर (मुक्तsp < dq->q_low_space[XFS_QLOWSP_5_PCNT]) अणु
		shअगरt = 2;
		अगर (मुक्तsp < dq->q_low_space[XFS_QLOWSP_3_PCNT])
			shअगरt += 2;
		अगर (मुक्तsp < dq->q_low_space[XFS_QLOWSP_1_PCNT])
			shअगरt += 2;
	पूर्ण

	अगर (मुक्तsp < *qमुक्तsp)
		*qमुक्तsp = मुक्तsp;

	/* only overग_लिखो the throttle values अगर we are more aggressive */
	अगर ((मुक्तsp >> shअगरt) < (*qblocks >> *qshअगरt)) अणु
		*qblocks = मुक्तsp;
		*qshअगरt = shअगरt;
	पूर्ण
पूर्ण

/*
 * If we करोn't have a user specअगरied pपुनः_स्मृतिation size, dynamically increase
 * the pपुनः_स्मृतिation size as the size of the file grows.  Cap the maximum size
 * at a single extent or less अगर the fileप्रणाली is near full. The बंदr the
 * fileप्रणाली is to being full, the smaller the maximum pपुनः_स्मृतिation.
 */
STATIC xfs_fsblock_t
xfs_iomap_pपुनः_स्मृति_size(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	loff_t			offset,
	loff_t			count,
	काष्ठा xfs_iext_cursor	*icur)
अणु
	काष्ठा xfs_iext_cursor	ncur = *icur;
	काष्ठा xfs_bmbt_irec	prev, got;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	xfs_fileoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	पूर्णांक64_t			मुक्तsp;
	xfs_fsblock_t		qblocks;
	xfs_fsblock_t		alloc_blocks = 0;
	xfs_extlen_t		plen;
	पूर्णांक			shअगरt = 0;
	पूर्णांक			qshअगरt = 0;

	/*
	 * As an exception we करोn't करो any pपुनः_स्मृतिation at all अगर the file is
	 * smaller than the minimum pपुनः_स्मृतिation and we are using the शेष
	 * dynamic pपुनः_स्मृतिation scheme, as it is likely this is the only ग_लिखो
	 * to the file that is going to be करोne.
	 */
	अगर (XFS_ISIZE(ip) < XFS_FSB_TO_B(mp, mp->m_allocsize_blocks))
		वापस 0;

	/*
	 * Use the minimum pपुनः_स्मृतिation size क्रम small files or अगर we are
	 * writing right after a hole.
	 */
	अगर (XFS_ISIZE(ip) < XFS_FSB_TO_B(mp, mp->m_dalign) ||
	    !xfs_iext_prev_extent(अगरp, &ncur, &prev) ||
	    prev.br_startoff + prev.br_blockcount < offset_fsb)
		वापस mp->m_allocsize_blocks;

	/*
	 * Take the size of the preceding data extents as the basis क्रम the
	 * pपुनः_स्मृतिation size. Note that we करोn't care अगर the previous extents
	 * are written or not.
	 */
	plen = prev.br_blockcount;
	जबतक (xfs_iext_prev_extent(अगरp, &ncur, &got)) अणु
		अगर (plen > MAXEXTLEN / 2 ||
		    isnullstartblock(got.br_startblock) ||
		    got.br_startoff + got.br_blockcount != prev.br_startoff ||
		    got.br_startblock + got.br_blockcount != prev.br_startblock)
			अवरोध;
		plen += got.br_blockcount;
		prev = got;
	पूर्ण

	/*
	 * If the size of the extents is greater than half the maximum extent
	 * length, then use the current offset as the basis.  This ensures that
	 * क्रम large files the pपुनः_स्मृतिation size always extends to MAXEXTLEN
	 * rather than falling लघु due to things like stripe unit/width
	 * alignment of real extents.
	 */
	alloc_blocks = plen * 2;
	अगर (alloc_blocks > MAXEXTLEN)
		alloc_blocks = XFS_B_TO_FSB(mp, offset);
	qblocks = alloc_blocks;

	/*
	 * MAXEXTLEN is not a घातer of two value but we round the pपुनः_स्मृति करोwn
	 * to the nearest घातer of two value after throttling. To prevent the
	 * round करोwn from unconditionally reducing the maximum supported
	 * pपुनः_स्मृति size, we round up first, apply appropriate throttling,
	 * round करोwn and cap the value to MAXEXTLEN.
	 */
	alloc_blocks = XFS_खाताOFF_MIN(roundup_घात_of_two(MAXEXTLEN),
				       alloc_blocks);

	मुक्तsp = percpu_counter_पढ़ो_positive(&mp->m_fdblocks);
	अगर (मुक्तsp < mp->m_low_space[XFS_LOWSP_5_PCNT]) अणु
		shअगरt = 2;
		अगर (मुक्तsp < mp->m_low_space[XFS_LOWSP_4_PCNT])
			shअगरt++;
		अगर (मुक्तsp < mp->m_low_space[XFS_LOWSP_3_PCNT])
			shअगरt++;
		अगर (मुक्तsp < mp->m_low_space[XFS_LOWSP_2_PCNT])
			shअगरt++;
		अगर (मुक्तsp < mp->m_low_space[XFS_LOWSP_1_PCNT])
			shअगरt++;
	पूर्ण

	/*
	 * Check each quota to cap the pपुनः_स्मृति size, provide a shअगरt value to
	 * throttle with and adjust amount of available space.
	 */
	अगर (xfs_quota_need_throttle(ip, XFS_DQTYPE_USER, alloc_blocks))
		xfs_quota_calc_throttle(ip, XFS_DQTYPE_USER, &qblocks, &qshअगरt,
					&मुक्तsp);
	अगर (xfs_quota_need_throttle(ip, XFS_DQTYPE_GROUP, alloc_blocks))
		xfs_quota_calc_throttle(ip, XFS_DQTYPE_GROUP, &qblocks, &qshअगरt,
					&मुक्तsp);
	अगर (xfs_quota_need_throttle(ip, XFS_DQTYPE_PROJ, alloc_blocks))
		xfs_quota_calc_throttle(ip, XFS_DQTYPE_PROJ, &qblocks, &qshअगरt,
					&मुक्तsp);

	/*
	 * The final pपुनः_स्मृति size is set to the minimum of मुक्त space available
	 * in each of the quotas and the overall fileप्रणाली.
	 *
	 * The shअगरt throttle value is set to the maximum value as determined by
	 * the global low मुक्त space values and per-quota low मुक्त space values.
	 */
	alloc_blocks = min(alloc_blocks, qblocks);
	shअगरt = max(shअगरt, qshअगरt);

	अगर (shअगरt)
		alloc_blocks >>= shअगरt;
	/*
	 * roundकरोwn_घात_of_two() वापसs an undefined result अगर we pass in
	 * alloc_blocks = 0.
	 */
	अगर (alloc_blocks)
		alloc_blocks = roundकरोwn_घात_of_two(alloc_blocks);
	अगर (alloc_blocks > MAXEXTLEN)
		alloc_blocks = MAXEXTLEN;

	/*
	 * If we are still trying to allocate more space than is
	 * available, squash the pपुनः_स्मृति hard. This can happen अगर we
	 * have a large file on a small fileप्रणाली and the above
	 * lowspace thresholds are smaller than MAXEXTLEN.
	 */
	जबतक (alloc_blocks && alloc_blocks >= मुक्तsp)
		alloc_blocks >>= 4;
	अगर (alloc_blocks < mp->m_allocsize_blocks)
		alloc_blocks = mp->m_allocsize_blocks;
	trace_xfs_iomap_pपुनः_स्मृति_size(ip, alloc_blocks, shअगरt,
				      mp->m_allocsize_blocks);
	वापस alloc_blocks;
पूर्ण

पूर्णांक
xfs_iomap_ग_लिखो_unwritten(
	xfs_inode_t	*ip,
	xfs_off_t	offset,
	xfs_off_t	count,
	bool		update_isize)
अणु
	xfs_mount_t	*mp = ip->i_mount;
	xfs_fileoff_t	offset_fsb;
	xfs_filblks_t	count_fsb;
	xfs_filblks_t	numblks_fsb;
	पूर्णांक		nimaps;
	xfs_trans_t	*tp;
	xfs_bmbt_irec_t imap;
	काष्ठा inode	*inode = VFS_I(ip);
	xfs_fमाप_प्रकार	i_size;
	uपूर्णांक		resblks;
	पूर्णांक		error;

	trace_xfs_unwritten_convert(ip, offset, count);

	offset_fsb = XFS_B_TO_FSBT(mp, offset);
	count_fsb = XFS_B_TO_FSB(mp, (xfs_ufमाप_प्रकार)offset + count);
	count_fsb = (xfs_filblks_t)(count_fsb - offset_fsb);

	/*
	 * Reserve enough blocks in this transaction क्रम two complete extent
	 * btree splits.  We may be converting the middle part of an unwritten
	 * extent and in this हाल we will insert two new extents in the btree
	 * each of which could cause a full split.
	 *
	 * This reservation amount will be used in the first call to
	 * xfs_bmbt_split() to select an AG with enough space to satisfy the
	 * rest of the operation.
	 */
	resblks = XFS_DIOSTRAT_SPACE_RES(mp, 0) << 1;

	/* Attach dquots so that bmbt splits are accounted correctly. */
	error = xfs_qm_dqattach(ip);
	अगर (error)
		वापस error;

	करो अणु
		/*
		 * Set up a transaction to convert the range of extents
		 * from unwritten to real. Do allocations in a loop until
		 * we have covered the range passed in.
		 *
		 * Note that we can't risk to recursing back पूर्णांकo the fileप्रणाली
		 * here as we might be asked to ग_लिखो out the same inode that we
		 * complete here and might deadlock on the iolock.
		 */
		error = xfs_trans_alloc_inode(ip, &M_RES(mp)->tr_ग_लिखो, resblks,
				0, true, &tp);
		अगर (error)
			वापस error;

		error = xfs_iext_count_may_overflow(ip, XFS_DATA_FORK,
				XFS_IEXT_WRITE_UNWRITTEN_CNT);
		अगर (error)
			जाओ error_on_bmapi_transaction;

		/*
		 * Modअगरy the unwritten extent state of the buffer.
		 */
		nimaps = 1;
		error = xfs_bmapi_ग_लिखो(tp, ip, offset_fsb, count_fsb,
					XFS_BMAPI_CONVERT, resblks, &imap,
					&nimaps);
		अगर (error)
			जाओ error_on_bmapi_transaction;

		/*
		 * Log the updated inode size as we go.  We have to be careful
		 * to only log it up to the actual ग_लिखो offset अगर it is
		 * halfway पूर्णांकo a block.
		 */
		i_size = XFS_FSB_TO_B(mp, offset_fsb + count_fsb);
		अगर (i_size > offset + count)
			i_size = offset + count;
		अगर (update_isize && i_size > i_size_पढ़ो(inode))
			i_size_ग_लिखो(inode, i_size);
		i_size = xfs_new_eof(ip, i_size);
		अगर (i_size) अणु
			ip->i_disk_size = i_size;
			xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
		पूर्ण

		error = xfs_trans_commit(tp);
		xfs_iunlock(ip, XFS_ILOCK_EXCL);
		अगर (error)
			वापस error;

		अगर (unlikely(!xfs_valid_startblock(ip, imap.br_startblock)))
			वापस xfs_alert_fsblock_zero(ip, &imap);

		अगर ((numblks_fsb = imap.br_blockcount) == 0) अणु
			/*
			 * The numblks_fsb value should always get
			 * smaller, otherwise the loop is stuck.
			 */
			ASSERT(imap.br_blockcount);
			अवरोध;
		पूर्ण
		offset_fsb += numblks_fsb;
		count_fsb -= numblks_fsb;
	पूर्ण जबतक (count_fsb > 0);

	वापस 0;

error_on_bmapi_transaction:
	xfs_trans_cancel(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

अटल अंतरभूत bool
imap_needs_alloc(
	काष्ठा inode		*inode,
	अचिन्हित		flags,
	काष्ठा xfs_bmbt_irec	*imap,
	पूर्णांक			nimaps)
अणु
	/* करोn't allocate blocks when just zeroing */
	अगर (flags & IOMAP_ZERO)
		वापस false;
	अगर (!nimaps ||
	    imap->br_startblock == HOLESTARTBLOCK ||
	    imap->br_startblock == DELAYSTARTBLOCK)
		वापस true;
	/* we convert unwritten extents beक्रमe copying the data क्रम DAX */
	अगर (IS_DAX(inode) && imap->br_state == XFS_EXT_UNWRITTEN)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool
imap_needs_cow(
	काष्ठा xfs_inode	*ip,
	अचिन्हित पूर्णांक		flags,
	काष्ठा xfs_bmbt_irec	*imap,
	पूर्णांक			nimaps)
अणु
	अगर (!xfs_is_cow_inode(ip))
		वापस false;

	/* when zeroing we करोn't have to COW holes or unwritten extents */
	अगर (flags & IOMAP_ZERO) अणु
		अगर (!nimaps ||
		    imap->br_startblock == HOLESTARTBLOCK ||
		    imap->br_state == XFS_EXT_UNWRITTEN)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
xfs_ilock_क्रम_iomap(
	काष्ठा xfs_inode	*ip,
	अचिन्हित		flags,
	अचिन्हित		*lockmode)
अणु
	अचिन्हित		mode = XFS_ILOCK_SHARED;
	bool			is_ग_लिखो = flags & (IOMAP_WRITE | IOMAP_ZERO);

	/*
	 * COW ग_लिखोs may allocate delalloc space or convert unwritten COW
	 * extents, so we need to make sure to take the lock exclusively here.
	 */
	अगर (xfs_is_cow_inode(ip) && is_ग_लिखो)
		mode = XFS_ILOCK_EXCL;

	/*
	 * Extents not yet cached requires exclusive access, करोn't block.  This
	 * is an खोलोcoded xfs_ilock_data_map_shared() call but with
	 * non-blocking behaviour.
	 */
	अगर (xfs_need_iपढ़ो_extents(&ip->i_df)) अणु
		अगर (flags & IOMAP_NOWAIT)
			वापस -EAGAIN;
		mode = XFS_ILOCK_EXCL;
	पूर्ण

relock:
	अगर (flags & IOMAP_NOWAIT) अणु
		अगर (!xfs_ilock_noरुको(ip, mode))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		xfs_ilock(ip, mode);
	पूर्ण

	/*
	 * The reflink अगरlag could have changed since the earlier unlocked
	 * check, so अगर we got ILOCK_SHARED क्रम a ग_लिखो and but we're now a
	 * reflink inode we have to चयन to ILOCK_EXCL and relock.
	 */
	अगर (mode == XFS_ILOCK_SHARED && is_ग_लिखो && xfs_is_cow_inode(ip)) अणु
		xfs_iunlock(ip, mode);
		mode = XFS_ILOCK_EXCL;
		जाओ relock;
	पूर्ण

	*lockmode = mode;
	वापस 0;
पूर्ण

/*
 * Check that the imap we are going to वापस to the caller spans the entire
 * range that the caller requested क्रम the IO.
 */
अटल bool
imap_spans_range(
	काष्ठा xfs_bmbt_irec	*imap,
	xfs_fileoff_t		offset_fsb,
	xfs_fileoff_t		end_fsb)
अणु
	अगर (imap->br_startoff > offset_fsb)
		वापस false;
	अगर (imap->br_startoff + imap->br_blockcount < end_fsb)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक
xfs_direct_ग_लिखो_iomap_begin(
	काष्ठा inode		*inode,
	loff_t			offset,
	loff_t			length,
	अचिन्हित		flags,
	काष्ठा iomap		*iomap,
	काष्ठा iomap		*srcmap)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_bmbt_irec	imap, cmap;
	xfs_fileoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fileoff_t		end_fsb = xfs_iomap_end_fsb(mp, offset, length);
	पूर्णांक			nimaps = 1, error = 0;
	bool			shared = false;
	u16			iomap_flags = 0;
	अचिन्हित		lockmode;

	ASSERT(flags & (IOMAP_WRITE | IOMAP_ZERO));

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	/*
	 * Writes that span खातापूर्ण might trigger an IO size update on completion,
	 * so consider them to be dirty क्रम the purposes of O_DSYNC even अगर
	 * there is no other metadata changes pending or have been made here.
	 */
	अगर (offset + length > i_size_पढ़ो(inode))
		iomap_flags |= IOMAP_F_सूचीTY;

	error = xfs_ilock_क्रम_iomap(ip, flags, &lockmode);
	अगर (error)
		वापस error;

	error = xfs_bmapi_पढ़ो(ip, offset_fsb, end_fsb - offset_fsb, &imap,
			       &nimaps, 0);
	अगर (error)
		जाओ out_unlock;

	अगर (imap_needs_cow(ip, flags, &imap, nimaps)) अणु
		error = -EAGAIN;
		अगर (flags & IOMAP_NOWAIT)
			जाओ out_unlock;

		/* may drop and re-acquire the ilock */
		error = xfs_reflink_allocate_cow(ip, &imap, &cmap, &shared,
				&lockmode, flags & IOMAP_सूचीECT);
		अगर (error)
			जाओ out_unlock;
		अगर (shared)
			जाओ out_found_cow;
		end_fsb = imap.br_startoff + imap.br_blockcount;
		length = XFS_FSB_TO_B(mp, end_fsb) - offset;
	पूर्ण

	अगर (imap_needs_alloc(inode, flags, &imap, nimaps))
		जाओ allocate_blocks;

	/*
	 * NOWAIT and OVERWRITE I/O needs to span the entire requested I/O with
	 * a single map so that we aव्योम partial IO failures due to the rest of
	 * the I/O range not covered by this map triggering an EAGAIN condition
	 * when it is subsequently mapped and पातing the I/O.
	 */
	अगर (flags & (IOMAP_NOWAIT | IOMAP_OVERWRITE_ONLY)) अणु
		error = -EAGAIN;
		अगर (!imap_spans_range(&imap, offset_fsb, end_fsb))
			जाओ out_unlock;
	पूर्ण

	/*
	 * For overग_लिखो only I/O, we cannot convert unwritten extents without
	 * requiring sub-block zeroing.  This can only be करोne under an
	 * exclusive IOLOCK, hence वापस -EAGAIN अगर this is not a written
	 * extent to tell the caller to try again.
	 */
	अगर (flags & IOMAP_OVERWRITE_ONLY) अणु
		error = -EAGAIN;
		अगर (imap.br_state != XFS_EXT_NORM &&
	            ((offset | length) & mp->m_blockmask))
			जाओ out_unlock;
	पूर्ण

	xfs_iunlock(ip, lockmode);
	trace_xfs_iomap_found(ip, offset, length, XFS_DATA_FORK, &imap);
	वापस xfs_bmbt_to_iomap(ip, iomap, &imap, iomap_flags);

allocate_blocks:
	error = -EAGAIN;
	अगर (flags & (IOMAP_NOWAIT | IOMAP_OVERWRITE_ONLY))
		जाओ out_unlock;

	/*
	 * We cap the maximum length we map to a sane size  to keep the chunks
	 * of work करोne where somewhat symmetric with the work ग_लिखोback करोes.
	 * This is a completely arbitrary number pulled out of thin air as a
	 * best guess क्रम initial testing.
	 *
	 * Note that the values needs to be less than 32-bits wide until the
	 * lower level functions are updated.
	 */
	length = min_t(loff_t, length, 1024 * PAGE_SIZE);
	end_fsb = xfs_iomap_end_fsb(mp, offset, length);

	अगर (offset + length > XFS_ISIZE(ip))
		end_fsb = xfs_iomap_eof_align_last_fsb(ip, end_fsb);
	अन्यथा अगर (nimaps && imap.br_startblock == HOLESTARTBLOCK)
		end_fsb = min(end_fsb, imap.br_startoff + imap.br_blockcount);
	xfs_iunlock(ip, lockmode);

	error = xfs_iomap_ग_लिखो_direct(ip, offset_fsb, end_fsb - offset_fsb,
			&imap);
	अगर (error)
		वापस error;

	trace_xfs_iomap_alloc(ip, offset, length, XFS_DATA_FORK, &imap);
	वापस xfs_bmbt_to_iomap(ip, iomap, &imap, iomap_flags | IOMAP_F_NEW);

out_found_cow:
	xfs_iunlock(ip, lockmode);
	length = XFS_FSB_TO_B(mp, cmap.br_startoff + cmap.br_blockcount);
	trace_xfs_iomap_found(ip, offset, length - offset, XFS_COW_FORK, &cmap);
	अगर (imap.br_startblock != HOLESTARTBLOCK) अणु
		error = xfs_bmbt_to_iomap(ip, srcmap, &imap, 0);
		अगर (error)
			वापस error;
	पूर्ण
	वापस xfs_bmbt_to_iomap(ip, iomap, &cmap, IOMAP_F_SHARED);

out_unlock:
	अगर (lockmode)
		xfs_iunlock(ip, lockmode);
	वापस error;
पूर्ण

स्थिर काष्ठा iomap_ops xfs_direct_ग_लिखो_iomap_ops = अणु
	.iomap_begin		= xfs_direct_ग_लिखो_iomap_begin,
पूर्ण;

अटल पूर्णांक
xfs_buffered_ग_लिखो_iomap_begin(
	काष्ठा inode		*inode,
	loff_t			offset,
	loff_t			count,
	अचिन्हित		flags,
	काष्ठा iomap		*iomap,
	काष्ठा iomap		*srcmap)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fileoff_t		end_fsb = xfs_iomap_end_fsb(mp, offset, count);
	काष्ठा xfs_bmbt_irec	imap, cmap;
	काष्ठा xfs_iext_cursor	icur, ccur;
	xfs_fsblock_t		pपुनः_स्मृति_blocks = 0;
	bool			eof = false, cow_eof = false, shared = false;
	पूर्णांक			allocविभाजन = XFS_DATA_FORK;
	पूर्णांक			error = 0;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	/* we can't use delayed allocations when using extent size hपूर्णांकs */
	अगर (xfs_get_extsz_hपूर्णांक(ip))
		वापस xfs_direct_ग_लिखो_iomap_begin(inode, offset, count,
				flags, iomap, srcmap);

	ASSERT(!XFS_IS_REALTIME_INODE(ip));

	xfs_ilock(ip, XFS_ILOCK_EXCL);

	अगर (XFS_IS_CORRUPT(mp, !xfs_अगरork_has_extents(&ip->i_df)) ||
	    XFS_TEST_ERROR(false, mp, XFS_ERRTAG_BMAPIFORMAT)) अणु
		error = -EFSCORRUPTED;
		जाओ out_unlock;
	पूर्ण

	XFS_STATS_INC(mp, xs_blk_mapw);

	error = xfs_iपढ़ो_extents(शून्य, ip, XFS_DATA_FORK);
	अगर (error)
		जाओ out_unlock;

	/*
	 * Search the data विभाजन first to look up our source mapping.  We
	 * always need the data विभाजन map, as we have to वापस it to the
	 * iomap code so that the higher level ग_लिखो code can पढ़ो data in to
	 * perक्रमm पढ़ो-modअगरy-ग_लिखो cycles क्रम unaligned ग_लिखोs.
	 */
	eof = !xfs_iext_lookup_extent(ip, &ip->i_df, offset_fsb, &icur, &imap);
	अगर (eof)
		imap.br_startoff = end_fsb; /* fake hole until the end */

	/* We never need to allocate blocks क्रम zeroing a hole. */
	अगर ((flags & IOMAP_ZERO) && imap.br_startoff > offset_fsb) अणु
		xfs_hole_to_iomap(ip, iomap, offset_fsb, imap.br_startoff);
		जाओ out_unlock;
	पूर्ण

	/*
	 * Search the COW विभाजन extent list even अगर we did not find a data विभाजन
	 * extent.  This serves two purposes: first this implements the
	 * speculative pपुनः_स्मृतिation using cowextsize, so that we also unshare
	 * block adjacent to shared blocks instead of just the shared blocks
	 * themselves.  Second the lookup in the extent list is generally faster
	 * than going out to the shared extent tree.
	 */
	अगर (xfs_is_cow_inode(ip)) अणु
		अगर (!ip->i_cowfp) अणु
			ASSERT(!xfs_is_reflink_inode(ip));
			xfs_अगरork_init_cow(ip);
		पूर्ण
		cow_eof = !xfs_iext_lookup_extent(ip, ip->i_cowfp, offset_fsb,
				&ccur, &cmap);
		अगर (!cow_eof && cmap.br_startoff <= offset_fsb) अणु
			trace_xfs_reflink_cow_found(ip, &cmap);
			जाओ found_cow;
		पूर्ण
	पूर्ण

	अगर (imap.br_startoff <= offset_fsb) अणु
		/*
		 * For reflink files we may need a delalloc reservation when
		 * overwriting shared extents.   This includes zeroing of
		 * existing extents that contain data.
		 */
		अगर (!xfs_is_cow_inode(ip) ||
		    ((flags & IOMAP_ZERO) && imap.br_state != XFS_EXT_NORM)) अणु
			trace_xfs_iomap_found(ip, offset, count, XFS_DATA_FORK,
					&imap);
			जाओ found_imap;
		पूर्ण

		xfs_trim_extent(&imap, offset_fsb, end_fsb - offset_fsb);

		/* Trim the mapping to the nearest shared extent boundary. */
		error = xfs_bmap_trim_cow(ip, &imap, &shared);
		अगर (error)
			जाओ out_unlock;

		/* Not shared?  Just report the (potentially capped) extent. */
		अगर (!shared) अणु
			trace_xfs_iomap_found(ip, offset, count, XFS_DATA_FORK,
					&imap);
			जाओ found_imap;
		पूर्ण

		/*
		 * Fork all the shared blocks from our ग_लिखो offset until the
		 * end of the extent.
		 */
		allocविभाजन = XFS_COW_FORK;
		end_fsb = imap.br_startoff + imap.br_blockcount;
	पूर्ण अन्यथा अणु
		/*
		 * We cap the maximum length we map here to MAX_WRITEBACK_PAGES
		 * pages to keep the chunks of work करोne where somewhat
		 * symmetric with the work ग_लिखोback करोes.  This is a completely
		 * arbitrary number pulled out of thin air.
		 *
		 * Note that the values needs to be less than 32-bits wide until
		 * the lower level functions are updated.
		 */
		count = min_t(loff_t, count, 1024 * PAGE_SIZE);
		end_fsb = xfs_iomap_end_fsb(mp, offset, count);

		अगर (xfs_is_always_cow_inode(ip))
			allocविभाजन = XFS_COW_FORK;
	पूर्ण

	error = xfs_qm_dqattach_locked(ip, false);
	अगर (error)
		जाओ out_unlock;

	अगर (eof && offset + count > XFS_ISIZE(ip)) अणु
		/*
		 * Determine the initial size of the pपुनः_स्मृतिation.
		 * We clean up any extra pपुनः_स्मृतिation when the file is बंदd.
		 */
		अगर (mp->m_flags & XFS_MOUNT_ALLOCSIZE)
			pपुनः_स्मृति_blocks = mp->m_allocsize_blocks;
		अन्यथा
			pपुनः_स्मृति_blocks = xfs_iomap_pपुनः_स्मृति_size(ip, allocविभाजन,
						offset, count, &icur);
		अगर (pपुनः_स्मृति_blocks) अणु
			xfs_extlen_t	align;
			xfs_off_t	end_offset;
			xfs_fileoff_t	p_end_fsb;

			end_offset = XFS_ALLOC_ALIGN(mp, offset + count - 1);
			p_end_fsb = XFS_B_TO_FSBT(mp, end_offset) +
					pपुनः_स्मृति_blocks;

			align = xfs_eof_alignment(ip);
			अगर (align)
				p_end_fsb = roundup_64(p_end_fsb, align);

			p_end_fsb = min(p_end_fsb,
				XFS_B_TO_FSB(mp, mp->m_super->s_maxbytes));
			ASSERT(p_end_fsb > offset_fsb);
			pपुनः_स्मृति_blocks = p_end_fsb - end_fsb;
		पूर्ण
	पूर्ण

retry:
	error = xfs_bmapi_reserve_delalloc(ip, allocविभाजन, offset_fsb,
			end_fsb - offset_fsb, pपुनः_स्मृति_blocks,
			allocविभाजन == XFS_DATA_FORK ? &imap : &cmap,
			allocविभाजन == XFS_DATA_FORK ? &icur : &ccur,
			allocविभाजन == XFS_DATA_FORK ? eof : cow_eof);
	चयन (error) अणु
	हाल 0:
		अवरोध;
	हाल -ENOSPC:
	हाल -EDQUOT:
		/* retry without any pपुनः_स्मृतिation */
		trace_xfs_delalloc_enospc(ip, offset, count);
		अगर (pपुनः_स्मृति_blocks) अणु
			pपुनः_स्मृति_blocks = 0;
			जाओ retry;
		पूर्ण
		/*FALLTHRU*/
	शेष:
		जाओ out_unlock;
	पूर्ण

	अगर (allocविभाजन == XFS_COW_FORK) अणु
		trace_xfs_iomap_alloc(ip, offset, count, allocविभाजन, &cmap);
		जाओ found_cow;
	पूर्ण

	/*
	 * Flag newly allocated delalloc blocks with IOMAP_F_NEW so we punch
	 * them out अगर the ग_लिखो happens to fail.
	 */
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	trace_xfs_iomap_alloc(ip, offset, count, allocविभाजन, &imap);
	वापस xfs_bmbt_to_iomap(ip, iomap, &imap, IOMAP_F_NEW);

found_imap:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस xfs_bmbt_to_iomap(ip, iomap, &imap, 0);

found_cow:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	अगर (imap.br_startoff <= offset_fsb) अणु
		error = xfs_bmbt_to_iomap(ip, srcmap, &imap, 0);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		xfs_trim_extent(&cmap, offset_fsb,
				imap.br_startoff - offset_fsb);
	पूर्ण
	वापस xfs_bmbt_to_iomap(ip, iomap, &cmap, IOMAP_F_SHARED);

out_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_buffered_ग_लिखो_iomap_end(
	काष्ठा inode		*inode,
	loff_t			offset,
	loff_t			length,
	sमाप_प्रकार			written,
	अचिन्हित		flags,
	काष्ठा iomap		*iomap)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		start_fsb;
	xfs_fileoff_t		end_fsb;
	पूर्णांक			error = 0;

	अगर (iomap->type != IOMAP_DELALLOC)
		वापस 0;

	/*
	 * Behave as अगर the ग_लिखो failed अगर drop ग_लिखोs is enabled. Set the NEW
	 * flag to क्रमce delalloc cleanup.
	 */
	अगर (XFS_TEST_ERROR(false, mp, XFS_ERRTAG_DROP_WRITES)) अणु
		iomap->flags |= IOMAP_F_NEW;
		written = 0;
	पूर्ण

	/*
	 * start_fsb refers to the first unused block after a लघु ग_लिखो. If
	 * nothing was written, round offset करोwn to poपूर्णांक at the first block in
	 * the range.
	 */
	अगर (unlikely(!written))
		start_fsb = XFS_B_TO_FSBT(mp, offset);
	अन्यथा
		start_fsb = XFS_B_TO_FSB(mp, offset + written);
	end_fsb = XFS_B_TO_FSB(mp, offset + length);

	/*
	 * Trim delalloc blocks अगर they were allocated by this ग_लिखो and we
	 * didn't manage to ग_लिखो the whole range.
	 *
	 * We करोn't need to care about racing delalloc as we hold i_mutex
	 * across the reserve/allocate/unreserve calls. If there are delalloc
	 * blocks in the range, they are ours.
	 */
	अगर ((iomap->flags & IOMAP_F_NEW) && start_fsb < end_fsb) अणु
		truncate_pagecache_range(VFS_I(ip), XFS_FSB_TO_B(mp, start_fsb),
					 XFS_FSB_TO_B(mp, end_fsb) - 1);

		error = xfs_bmap_punch_delalloc_range(ip, start_fsb,
					       end_fsb - start_fsb);
		अगर (error && !XFS_FORCED_SHUTDOWN(mp)) अणु
			xfs_alert(mp, "%s: unable to clean up ino %lld",
				__func__, ip->i_ino);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा iomap_ops xfs_buffered_ग_लिखो_iomap_ops = अणु
	.iomap_begin		= xfs_buffered_ग_लिखो_iomap_begin,
	.iomap_end		= xfs_buffered_ग_लिखो_iomap_end,
पूर्ण;

अटल पूर्णांक
xfs_पढ़ो_iomap_begin(
	काष्ठा inode		*inode,
	loff_t			offset,
	loff_t			length,
	अचिन्हित		flags,
	काष्ठा iomap		*iomap,
	काष्ठा iomap		*srcmap)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_bmbt_irec	imap;
	xfs_fileoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fileoff_t		end_fsb = xfs_iomap_end_fsb(mp, offset, length);
	पूर्णांक			nimaps = 1, error = 0;
	bool			shared = false;
	अचिन्हित		lockmode;

	ASSERT(!(flags & (IOMAP_WRITE | IOMAP_ZERO)));

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	error = xfs_ilock_क्रम_iomap(ip, flags, &lockmode);
	अगर (error)
		वापस error;
	error = xfs_bmapi_पढ़ो(ip, offset_fsb, end_fsb - offset_fsb, &imap,
			       &nimaps, 0);
	अगर (!error && (flags & IOMAP_REPORT))
		error = xfs_reflink_trim_around_shared(ip, &imap, &shared);
	xfs_iunlock(ip, lockmode);

	अगर (error)
		वापस error;
	trace_xfs_iomap_found(ip, offset, length, XFS_DATA_FORK, &imap);
	वापस xfs_bmbt_to_iomap(ip, iomap, &imap, shared ? IOMAP_F_SHARED : 0);
पूर्ण

स्थिर काष्ठा iomap_ops xfs_पढ़ो_iomap_ops = अणु
	.iomap_begin		= xfs_पढ़ो_iomap_begin,
पूर्ण;

अटल पूर्णांक
xfs_seek_iomap_begin(
	काष्ठा inode		*inode,
	loff_t			offset,
	loff_t			length,
	अचिन्हित		flags,
	काष्ठा iomap		*iomap,
	काष्ठा iomap		*srcmap)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fileoff_t		end_fsb = XFS_B_TO_FSB(mp, offset + length);
	xfs_fileoff_t		cow_fsb = शून्यखाताOFF, data_fsb = शून्यखाताOFF;
	काष्ठा xfs_iext_cursor	icur;
	काष्ठा xfs_bmbt_irec	imap, cmap;
	पूर्णांक			error = 0;
	अचिन्हित		lockmode;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	lockmode = xfs_ilock_data_map_shared(ip);
	error = xfs_iपढ़ो_extents(शून्य, ip, XFS_DATA_FORK);
	अगर (error)
		जाओ out_unlock;

	अगर (xfs_iext_lookup_extent(ip, &ip->i_df, offset_fsb, &icur, &imap)) अणु
		/*
		 * If we found a data extent we are करोne.
		 */
		अगर (imap.br_startoff <= offset_fsb)
			जाओ करोne;
		data_fsb = imap.br_startoff;
	पूर्ण अन्यथा अणु
		/*
		 * Fake a hole until the end of the file.
		 */
		data_fsb = xfs_iomap_end_fsb(mp, offset, length);
	पूर्ण

	/*
	 * If a COW विभाजन extent covers the hole, report it - capped to the next
	 * data विभाजन extent:
	 */
	अगर (xfs_inode_has_cow_data(ip) &&
	    xfs_iext_lookup_extent(ip, ip->i_cowfp, offset_fsb, &icur, &cmap))
		cow_fsb = cmap.br_startoff;
	अगर (cow_fsb != शून्यखाताOFF && cow_fsb <= offset_fsb) अणु
		अगर (data_fsb < cow_fsb + cmap.br_blockcount)
			end_fsb = min(end_fsb, data_fsb);
		xfs_trim_extent(&cmap, offset_fsb, end_fsb);
		error = xfs_bmbt_to_iomap(ip, iomap, &cmap, IOMAP_F_SHARED);
		/*
		 * This is a COW extent, so we must probe the page cache
		 * because there could be dirty page cache being backed
		 * by this extent.
		 */
		iomap->type = IOMAP_UNWRITTEN;
		जाओ out_unlock;
	पूर्ण

	/*
	 * Else report a hole, capped to the next found data or COW extent.
	 */
	अगर (cow_fsb != शून्यखाताOFF && cow_fsb < data_fsb)
		imap.br_blockcount = cow_fsb - offset_fsb;
	अन्यथा
		imap.br_blockcount = data_fsb - offset_fsb;
	imap.br_startoff = offset_fsb;
	imap.br_startblock = HOLESTARTBLOCK;
	imap.br_state = XFS_EXT_NORM;
करोne:
	xfs_trim_extent(&imap, offset_fsb, end_fsb);
	error = xfs_bmbt_to_iomap(ip, iomap, &imap, 0);
out_unlock:
	xfs_iunlock(ip, lockmode);
	वापस error;
पूर्ण

स्थिर काष्ठा iomap_ops xfs_seek_iomap_ops = अणु
	.iomap_begin		= xfs_seek_iomap_begin,
पूर्ण;

अटल पूर्णांक
xfs_xattr_iomap_begin(
	काष्ठा inode		*inode,
	loff_t			offset,
	loff_t			length,
	अचिन्हित		flags,
	काष्ठा iomap		*iomap,
	काष्ठा iomap		*srcmap)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fileoff_t		end_fsb = XFS_B_TO_FSB(mp, offset + length);
	काष्ठा xfs_bmbt_irec	imap;
	पूर्णांक			nimaps = 1, error = 0;
	अचिन्हित		lockmode;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	lockmode = xfs_ilock_attr_map_shared(ip);

	/* अगर there are no attribute विभाजन or extents, वापस ENOENT */
	अगर (!XFS_IFORK_Q(ip) || !ip->i_afp->अगर_nextents) अणु
		error = -ENOENT;
		जाओ out_unlock;
	पूर्ण

	ASSERT(ip->i_afp->अगर_क्रमmat != XFS_DINODE_FMT_LOCAL);
	error = xfs_bmapi_पढ़ो(ip, offset_fsb, end_fsb - offset_fsb, &imap,
			       &nimaps, XFS_BMAPI_ATTRFORK);
out_unlock:
	xfs_iunlock(ip, lockmode);

	अगर (error)
		वापस error;
	ASSERT(nimaps);
	वापस xfs_bmbt_to_iomap(ip, iomap, &imap, 0);
पूर्ण

स्थिर काष्ठा iomap_ops xfs_xattr_iomap_ops = अणु
	.iomap_begin		= xfs_xattr_iomap_begin,
पूर्ण;
