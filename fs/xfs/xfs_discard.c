<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 Red Hat, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_alloc_btree.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_discard.h"
#समावेश "xfs_error.h"
#समावेश "xfs_extent_busy.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_log.h"

STATIC पूर्णांक
xfs_trim_extents(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno,
	xfs_daddr_t		start,
	xfs_daddr_t		end,
	xfs_daddr_t		minlen,
	uपूर्णांक64_t		*blocks_trimmed)
अणु
	काष्ठा block_device	*bdev = mp->m_ddev_targp->bt_bdev;
	काष्ठा xfs_btree_cur	*cur;
	काष्ठा xfs_buf		*agbp;
	काष्ठा xfs_agf		*agf;
	काष्ठा xfs_perag	*pag;
	पूर्णांक			error;
	पूर्णांक			i;

	pag = xfs_perag_get(mp, agno);

	/*
	 * Force out the log.  This means any transactions that might have मुक्तd
	 * space beक्रमe we take the AGF buffer lock are now on disk, and the
	 * अस्थिर disk cache is flushed.
	 */
	xfs_log_क्रमce(mp, XFS_LOG_SYNC);

	error = xfs_alloc_पढ़ो_agf(mp, शून्य, agno, 0, &agbp);
	अगर (error)
		जाओ out_put_perag;
	agf = agbp->b_addr;

	cur = xfs_allocbt_init_cursor(mp, शून्य, agbp, agno, XFS_BTNUM_CNT);

	/*
	 * Look up the दीर्घest btree in the AGF and start with it.
	 */
	error = xfs_alloc_lookup_ge(cur, 0, be32_to_cpu(agf->agf_दीर्घest), &i);
	अगर (error)
		जाओ out_del_cursor;

	/*
	 * Loop until we are करोne with all extents that are large
	 * enough to be worth discarding.
	 */
	जबतक (i) अणु
		xfs_agblock_t	fbno;
		xfs_extlen_t	flen;
		xfs_daddr_t	dbno;
		xfs_extlen_t	dlen;

		error = xfs_alloc_get_rec(cur, &fbno, &flen, &i);
		अगर (error)
			जाओ out_del_cursor;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ out_del_cursor;
		पूर्ण
		ASSERT(flen <= be32_to_cpu(agf->agf_दीर्घest));

		/*
		 * use daddr क्रमmat क्रम all range/len calculations as that is
		 * the क्रमmat the range/len variables are supplied in by
		 * userspace.
		 */
		dbno = XFS_AGB_TO_DADDR(mp, agno, fbno);
		dlen = XFS_FSB_TO_BB(mp, flen);

		/*
		 * Too small?  Give up.
		 */
		अगर (dlen < minlen) अणु
			trace_xfs_discard_toosmall(mp, agno, fbno, flen);
			जाओ out_del_cursor;
		पूर्ण

		/*
		 * If the extent is entirely outside of the range we are
		 * supposed to discard skip it.  Do not bother to trim
		 * करोwn partially overlapping ranges क्रम now.
		 */
		अगर (dbno + dlen < start || dbno > end) अणु
			trace_xfs_discard_exclude(mp, agno, fbno, flen);
			जाओ next_extent;
		पूर्ण

		/*
		 * If any blocks in the range are still busy, skip the
		 * discard and try again the next समय.
		 */
		अगर (xfs_extent_busy_search(mp, agno, fbno, flen)) अणु
			trace_xfs_discard_busy(mp, agno, fbno, flen);
			जाओ next_extent;
		पूर्ण

		trace_xfs_discard_extent(mp, agno, fbno, flen);
		error = blkdev_issue_discard(bdev, dbno, dlen, GFP_NOFS, 0);
		अगर (error)
			जाओ out_del_cursor;
		*blocks_trimmed += flen;

next_extent:
		error = xfs_btree_decrement(cur, 0, &i);
		अगर (error)
			जाओ out_del_cursor;

		अगर (fatal_संकेत_pending(current)) अणु
			error = -ERESTARTSYS;
			जाओ out_del_cursor;
		पूर्ण
	पूर्ण

out_del_cursor:
	xfs_btree_del_cursor(cur, error);
	xfs_buf_rअन्यथा(agbp);
out_put_perag:
	xfs_perag_put(pag);
	वापस error;
पूर्ण

/*
 * trim a range of the fileप्रणाली.
 *
 * Note: the parameters passed from userspace are byte ranges पूर्णांकo the
 * fileप्रणाली which करोes not match to the क्रमmat we use क्रम fileप्रणाली block
 * addressing. FSB addressing is sparse (AGNO|AGBNO), जबतक the incoming क्रमmat
 * is a linear address range. Hence we need to use DADDR based conversions and
 * comparisons क्रम determining the correct offset and regions to trim.
 */
पूर्णांक
xfs_ioc_trim(
	काष्ठा xfs_mount		*mp,
	काष्ठा fstrim_range __user	*urange)
अणु
	काष्ठा request_queue	*q = bdev_get_queue(mp->m_ddev_targp->bt_bdev);
	अचिन्हित पूर्णांक		granularity = q->limits.discard_granularity;
	काष्ठा fstrim_range	range;
	xfs_daddr_t		start, end, minlen;
	xfs_agnumber_t		start_agno, end_agno, agno;
	uपूर्णांक64_t		blocks_trimmed = 0;
	पूर्णांक			error, last_error = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (!blk_queue_discard(q))
		वापस -EOPNOTSUPP;

	/*
	 * We haven't recovered the log, so we cannot use our bnobt-guided
	 * storage zapping commands.
	 */
	अगर (mp->m_flags & XFS_MOUNT_NORECOVERY)
		वापस -EROFS;

	अगर (copy_from_user(&range, urange, माप(range)))
		वापस -EFAULT;

	range.minlen = max_t(u64, granularity, range.minlen);
	minlen = BTOBB(range.minlen);
	/*
	 * Truncating करोwn the len isn't actually quite correct, but using
	 * BBTOB would mean we trivially get overflows क्रम values
	 * of ULदीर्घ_उच्च or slightly lower.  And ULदीर्घ_उच्च is the शेष
	 * used by the fstrim application.  In the end it really करोesn't
	 * matter as trimming blocks is an advisory पूर्णांकerface.
	 */
	अगर (range.start >= XFS_FSB_TO_B(mp, mp->m_sb.sb_dblocks) ||
	    range.minlen > XFS_FSB_TO_B(mp, mp->m_ag_max_usable) ||
	    range.len < mp->m_sb.sb_blocksize)
		वापस -EINVAL;

	start = BTOBB(range.start);
	end = start + BTOBBT(range.len) - 1;

	अगर (end > XFS_FSB_TO_BB(mp, mp->m_sb.sb_dblocks) - 1)
		end = XFS_FSB_TO_BB(mp, mp->m_sb.sb_dblocks)- 1;

	start_agno = xfs_daddr_to_agno(mp, start);
	end_agno = xfs_daddr_to_agno(mp, end);

	क्रम (agno = start_agno; agno <= end_agno; agno++) अणु
		error = xfs_trim_extents(mp, agno, start, end, minlen,
					  &blocks_trimmed);
		अगर (error) अणु
			last_error = error;
			अगर (error == -ERESTARTSYS)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (last_error)
		वापस last_error;

	range.len = XFS_FSB_TO_B(mp, blocks_trimmed);
	अगर (copy_to_user(urange, &range, माप(range)))
		वापस -EFAULT;
	वापस 0;
पूर्ण
