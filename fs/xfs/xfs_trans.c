<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * Copyright (C) 2010 Red Hat, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_extent_busy.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_log.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_error.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_dquot_item.h"
#समावेश "xfs_dquot.h"
#समावेश "xfs_icache.h"

kmem_zone_t	*xfs_trans_zone;

#अगर defined(CONFIG_TRACEPOINTS)
अटल व्योम
xfs_trans_trace_reservations(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_trans_res	resv;
	काष्ठा xfs_trans_res	*res;
	काष्ठा xfs_trans_res	*end_res;
	पूर्णांक			i;

	res = (काष्ठा xfs_trans_res *)M_RES(mp);
	end_res = (काष्ठा xfs_trans_res *)(M_RES(mp) + 1);
	क्रम (i = 0; res < end_res; i++, res++)
		trace_xfs_trans_resv_calc(mp, i, res);
	xfs_log_get_max_trans_res(mp, &resv);
	trace_xfs_trans_resv_calc(mp, -1, &resv);
पूर्ण
#अन्यथा
# define xfs_trans_trace_reservations(mp)
#पूर्ण_अगर

/*
 * Initialize the precomputed transaction reservation values
 * in the mount काष्ठाure.
 */
व्योम
xfs_trans_init(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_trans_resv_calc(mp, M_RES(mp));
	xfs_trans_trace_reservations(mp);
पूर्ण

/*
 * Free the transaction काष्ठाure.  If there is more clean up
 * to करो when the काष्ठाure is मुक्तd, add it here.
 */
STATIC व्योम
xfs_trans_मुक्त(
	काष्ठा xfs_trans	*tp)
अणु
	xfs_extent_busy_sort(&tp->t_busy);
	xfs_extent_busy_clear(tp->t_mountp, &tp->t_busy, false);

	trace_xfs_trans_मुक्त(tp, _RET_IP_);
	xfs_trans_clear_context(tp);
	अगर (!(tp->t_flags & XFS_TRANS_NO_WRITECOUNT))
		sb_end_पूर्णांकग_लिखो(tp->t_mountp->m_super);
	xfs_trans_मुक्त_dqinfo(tp);
	kmem_cache_मुक्त(xfs_trans_zone, tp);
पूर्ण

/*
 * This is called to create a new transaction which will share the
 * permanent log reservation of the given transaction.  The reमुख्यing
 * unused block and rt extent reservations are also inherited.  This
 * implies that the original transaction is no दीर्घer allowed to allocate
 * blocks.  Locks and log items, however, are no inherited.  They must
 * be added to the new transaction explicitly.
 */
STATIC काष्ठा xfs_trans *
xfs_trans_dup(
	काष्ठा xfs_trans	*tp)
अणु
	काष्ठा xfs_trans	*ntp;

	trace_xfs_trans_dup(tp, _RET_IP_);

	ntp = kmem_cache_zalloc(xfs_trans_zone, GFP_KERNEL | __GFP_NOFAIL);

	/*
	 * Initialize the new transaction काष्ठाure.
	 */
	ntp->t_magic = XFS_TRANS_HEADER_MAGIC;
	ntp->t_mountp = tp->t_mountp;
	INIT_LIST_HEAD(&ntp->t_items);
	INIT_LIST_HEAD(&ntp->t_busy);
	INIT_LIST_HEAD(&ntp->t_dfops);
	ntp->t_firstblock = शून्यFSBLOCK;

	ASSERT(tp->t_flags & XFS_TRANS_PERM_LOG_RES);
	ASSERT(tp->t_ticket != शून्य);

	ntp->t_flags = XFS_TRANS_PERM_LOG_RES |
		       (tp->t_flags & XFS_TRANS_RESERVE) |
		       (tp->t_flags & XFS_TRANS_NO_WRITECOUNT) |
		       (tp->t_flags & XFS_TRANS_RES_FDBLKS);
	/* We gave our ग_लिखोr reference to the new transaction */
	tp->t_flags |= XFS_TRANS_NO_WRITECOUNT;
	ntp->t_ticket = xfs_log_ticket_get(tp->t_ticket);

	ASSERT(tp->t_blk_res >= tp->t_blk_res_used);
	ntp->t_blk_res = tp->t_blk_res - tp->t_blk_res_used;
	tp->t_blk_res = tp->t_blk_res_used;

	ntp->t_rtx_res = tp->t_rtx_res - tp->t_rtx_res_used;
	tp->t_rtx_res = tp->t_rtx_res_used;

	xfs_trans_चयन_context(tp, ntp);

	/* move deferred ops over to the new tp */
	xfs_defer_move(ntp, tp);

	xfs_trans_dup_dqinfo(tp, ntp);
	वापस ntp;
पूर्ण

/*
 * This is called to reserve मुक्त disk blocks and log space क्रम the
 * given transaction.  This must be करोne beक्रमe allocating any resources
 * within the transaction.
 *
 * This will वापस ENOSPC अगर there are not enough blocks available.
 * It will sleep रुकोing क्रम available log space.
 * The only valid value क्रम the flags parameter is XFS_RES_LOG_PERM, which
 * is used by दीर्घ running transactions.  If any one of the reservations
 * fails then they will all be backed out.
 *
 * This करोes not करो quota reservations. That typically is करोne by the
 * caller afterwards.
 */
अटल पूर्णांक
xfs_trans_reserve(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_trans_res	*resp,
	uपूर्णांक			blocks,
	uपूर्णांक			rtextents)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	पूर्णांक			error = 0;
	bool			rsvd = (tp->t_flags & XFS_TRANS_RESERVE) != 0;

	/*
	 * Attempt to reserve the needed disk blocks by decrementing
	 * the number needed from the number available.  This will
	 * fail अगर the count would go below zero.
	 */
	अगर (blocks > 0) अणु
		error = xfs_mod_fdblocks(mp, -((पूर्णांक64_t)blocks), rsvd);
		अगर (error != 0)
			वापस -ENOSPC;
		tp->t_blk_res += blocks;
	पूर्ण

	/*
	 * Reserve the log space needed क्रम this transaction.
	 */
	अगर (resp->tr_logres > 0) अणु
		bool	permanent = false;

		ASSERT(tp->t_log_res == 0 ||
		       tp->t_log_res == resp->tr_logres);
		ASSERT(tp->t_log_count == 0 ||
		       tp->t_log_count == resp->tr_logcount);

		अगर (resp->tr_logflags & XFS_TRANS_PERM_LOG_RES) अणु
			tp->t_flags |= XFS_TRANS_PERM_LOG_RES;
			permanent = true;
		पूर्ण अन्यथा अणु
			ASSERT(tp->t_ticket == शून्य);
			ASSERT(!(tp->t_flags & XFS_TRANS_PERM_LOG_RES));
		पूर्ण

		अगर (tp->t_ticket != शून्य) अणु
			ASSERT(resp->tr_logflags & XFS_TRANS_PERM_LOG_RES);
			error = xfs_log_regrant(mp, tp->t_ticket);
		पूर्ण अन्यथा अणु
			error = xfs_log_reserve(mp,
						resp->tr_logres,
						resp->tr_logcount,
						&tp->t_ticket, XFS_TRANSACTION,
						permanent);
		पूर्ण

		अगर (error)
			जाओ unकरो_blocks;

		tp->t_log_res = resp->tr_logres;
		tp->t_log_count = resp->tr_logcount;
	पूर्ण

	/*
	 * Attempt to reserve the needed realसमय extents by decrementing
	 * the number needed from the number available.  This will
	 * fail अगर the count would go below zero.
	 */
	अगर (rtextents > 0) अणु
		error = xfs_mod_frextents(mp, -((पूर्णांक64_t)rtextents));
		अगर (error) अणु
			error = -ENOSPC;
			जाओ unकरो_log;
		पूर्ण
		tp->t_rtx_res += rtextents;
	पूर्ण

	वापस 0;

	/*
	 * Error हालs jump to one of these labels to unकरो any
	 * reservations which have alपढ़ोy been perक्रमmed.
	 */
unकरो_log:
	अगर (resp->tr_logres > 0) अणु
		xfs_log_ticket_ungrant(mp->m_log, tp->t_ticket);
		tp->t_ticket = शून्य;
		tp->t_log_res = 0;
		tp->t_flags &= ~XFS_TRANS_PERM_LOG_RES;
	पूर्ण

unकरो_blocks:
	अगर (blocks > 0) अणु
		xfs_mod_fdblocks(mp, (पूर्णांक64_t)blocks, rsvd);
		tp->t_blk_res = 0;
	पूर्ण
	वापस error;
पूर्ण

पूर्णांक
xfs_trans_alloc(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans_res	*resp,
	uपूर्णांक			blocks,
	uपूर्णांक			rtextents,
	uपूर्णांक			flags,
	काष्ठा xfs_trans	**tpp)
अणु
	काष्ठा xfs_trans	*tp;
	bool			want_retry = true;
	पूर्णांक			error;

	/*
	 * Allocate the handle beक्रमe we करो our मुक्तze accounting and setting up
	 * GFP_NOFS allocation context so that we aव्योम lockdep false positives
	 * by करोing GFP_KERNEL allocations inside sb_start_पूर्णांकग_लिखो().
	 */
retry:
	tp = kmem_cache_zalloc(xfs_trans_zone, GFP_KERNEL | __GFP_NOFAIL);
	अगर (!(flags & XFS_TRANS_NO_WRITECOUNT))
		sb_start_पूर्णांकग_लिखो(mp->m_super);
	xfs_trans_set_context(tp);

	/*
	 * Zero-reservation ("empty") transactions can't modअगरy anything, so
	 * they're allowed to run while we're frozen.
	 */
	WARN_ON(resp->tr_logres > 0 &&
		mp->m_super->s_ग_लिखोrs.frozen == SB_FREEZE_COMPLETE);
	ASSERT(!(flags & XFS_TRANS_RES_FDBLKS) ||
	       xfs_sb_version_haslazysbcount(&mp->m_sb));

	tp->t_magic = XFS_TRANS_HEADER_MAGIC;
	tp->t_flags = flags;
	tp->t_mountp = mp;
	INIT_LIST_HEAD(&tp->t_items);
	INIT_LIST_HEAD(&tp->t_busy);
	INIT_LIST_HEAD(&tp->t_dfops);
	tp->t_firstblock = शून्यFSBLOCK;

	error = xfs_trans_reserve(tp, resp, blocks, rtextents);
	अगर (error == -ENOSPC && want_retry) अणु
		xfs_trans_cancel(tp);

		/*
		 * We weren't able to reserve enough space क्रम the transaction.
		 * Flush the other speculative space allocations to मुक्त space.
		 * Do not perक्रमm a synchronous scan because callers can hold
		 * other locks.
		 */
		error = xfs_blockgc_मुक्त_space(mp, शून्य);
		अगर (error)
			वापस error;

		want_retry = false;
		जाओ retry;
	पूर्ण
	अगर (error) अणु
		xfs_trans_cancel(tp);
		वापस error;
	पूर्ण

	trace_xfs_trans_alloc(tp, _RET_IP_);

	*tpp = tp;
	वापस 0;
पूर्ण

/*
 * Create an empty transaction with no reservation.  This is a defensive
 * mechanism क्रम routines that query metadata without actually modअगरying them --
 * अगर the metadata being queried is somehow cross-linked (think a btree block
 * poपूर्णांकer that poपूर्णांकs higher in the tree), we risk deadlock.  However, blocks
 * grabbed as part of a transaction can be re-grabbed.  The verअगरiers will
 * notice the corrupt block and the operation will fail back to userspace
 * without deadlocking.
 *
 * Note the zero-length reservation; this transaction MUST be cancelled without
 * any dirty data.
 *
 * Callers should obtain मुक्तze protection to aव्योम a conflict with fs मुक्तzing
 * where we can be grabbing buffers at the same समय that मुक्तze is trying to
 * drain the buffer LRU list.
 */
पूर्णांक
xfs_trans_alloc_empty(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_trans		**tpp)
अणु
	काष्ठा xfs_trans_res		resv = अणु0पूर्ण;

	वापस xfs_trans_alloc(mp, &resv, 0, 0, XFS_TRANS_NO_WRITECOUNT, tpp);
पूर्ण

/*
 * Record the indicated change to the given field क्रम application
 * to the file प्रणाली's superblock when the transaction commits.
 * For now, just store the change in the transaction काष्ठाure.
 *
 * Mark the transaction काष्ठाure to indicate that the superblock
 * needs to be updated beक्रमe committing.
 *
 * Because we may not be keeping track of allocated/मुक्त inodes and
 * used fileप्रणाली blocks in the superblock, we करो not mark the
 * superblock dirty in this transaction अगर we modअगरy these fields.
 * We still need to update the transaction deltas so that they get
 * applied to the incore superblock, but we करोn't want them to
 * cause the superblock to get locked and logged अगर these are the
 * only fields in the superblock that the transaction modअगरies.
 */
व्योम
xfs_trans_mod_sb(
	xfs_trans_t	*tp,
	uपूर्णांक		field,
	पूर्णांक64_t		delta)
अणु
	uपूर्णांक32_t	flags = (XFS_TRANS_सूचीTY|XFS_TRANS_SB_सूचीTY);
	xfs_mount_t	*mp = tp->t_mountp;

	चयन (field) अणु
	हाल XFS_TRANS_SB_ICOUNT:
		tp->t_icount_delta += delta;
		अगर (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_सूचीTY;
		अवरोध;
	हाल XFS_TRANS_SB_IFREE:
		tp->t_अगरree_delta += delta;
		अगर (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_सूचीTY;
		अवरोध;
	हाल XFS_TRANS_SB_FDBLOCKS:
		/*
		 * Track the number of blocks allocated in the transaction.
		 * Make sure it करोes not exceed the number reserved. If so,
		 * shutकरोwn as this can lead to accounting inconsistency.
		 */
		अगर (delta < 0) अणु
			tp->t_blk_res_used += (uपूर्णांक)-delta;
			अगर (tp->t_blk_res_used > tp->t_blk_res)
				xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
		पूर्ण अन्यथा अगर (delta > 0 && (tp->t_flags & XFS_TRANS_RES_FDBLKS)) अणु
			पूर्णांक64_t	blkres_delta;

			/*
			 * Return मुक्तd blocks directly to the reservation
			 * instead of the global pool, being careful not to
			 * overflow the trans counter. This is used to preserve
			 * reservation across chains of transaction rolls that
			 * repeatedly मुक्त and allocate blocks.
			 */
			blkres_delta = min_t(पूर्णांक64_t, delta,
					     अच_पूर्णांक_उच्च - tp->t_blk_res);
			tp->t_blk_res += blkres_delta;
			delta -= blkres_delta;
		पूर्ण
		tp->t_fdblocks_delta += delta;
		अगर (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_सूचीTY;
		अवरोध;
	हाल XFS_TRANS_SB_RES_FDBLOCKS:
		/*
		 * The allocation has alपढ़ोy been applied to the
		 * in-core superblock's counter.  This should only
		 * be applied to the on-disk superblock.
		 */
		tp->t_res_fdblocks_delta += delta;
		अगर (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_सूचीTY;
		अवरोध;
	हाल XFS_TRANS_SB_FREXTENTS:
		/*
		 * Track the number of blocks allocated in the
		 * transaction.  Make sure it करोes not exceed the
		 * number reserved.
		 */
		अगर (delta < 0) अणु
			tp->t_rtx_res_used += (uपूर्णांक)-delta;
			ASSERT(tp->t_rtx_res_used <= tp->t_rtx_res);
		पूर्ण
		tp->t_frextents_delta += delta;
		अवरोध;
	हाल XFS_TRANS_SB_RES_FREXTENTS:
		/*
		 * The allocation has alपढ़ोy been applied to the
		 * in-core superblock's counter.  This should only
		 * be applied to the on-disk superblock.
		 */
		ASSERT(delta < 0);
		tp->t_res_frextents_delta += delta;
		अवरोध;
	हाल XFS_TRANS_SB_DBLOCKS:
		tp->t_dblocks_delta += delta;
		अवरोध;
	हाल XFS_TRANS_SB_AGCOUNT:
		ASSERT(delta > 0);
		tp->t_agcount_delta += delta;
		अवरोध;
	हाल XFS_TRANS_SB_IMAXPCT:
		tp->t_imaxpct_delta += delta;
		अवरोध;
	हाल XFS_TRANS_SB_REXTSIZE:
		tp->t_rextsize_delta += delta;
		अवरोध;
	हाल XFS_TRANS_SB_RBMBLOCKS:
		tp->t_rbmblocks_delta += delta;
		अवरोध;
	हाल XFS_TRANS_SB_RBLOCKS:
		tp->t_rblocks_delta += delta;
		अवरोध;
	हाल XFS_TRANS_SB_REXTENTS:
		tp->t_rextents_delta += delta;
		अवरोध;
	हाल XFS_TRANS_SB_REXTSLOG:
		tp->t_rextslog_delta += delta;
		अवरोध;
	शेष:
		ASSERT(0);
		वापस;
	पूर्ण

	tp->t_flags |= flags;
पूर्ण

/*
 * xfs_trans_apply_sb_deltas() is called from the commit code
 * to bring the superblock buffer पूर्णांकo the current transaction
 * and modअगरy it as requested by earlier calls to xfs_trans_mod_sb().
 *
 * For now we just look at each field allowed to change and change
 * it अगर necessary.
 */
STATIC व्योम
xfs_trans_apply_sb_deltas(
	xfs_trans_t	*tp)
अणु
	xfs_dsb_t	*sbp;
	काष्ठा xfs_buf	*bp;
	पूर्णांक		whole = 0;

	bp = xfs_trans_माला_लोb(tp);
	sbp = bp->b_addr;

	/*
	 * Only update the superblock counters अगर we are logging them
	 */
	अगर (!xfs_sb_version_haslazysbcount(&(tp->t_mountp->m_sb))) अणु
		अगर (tp->t_icount_delta)
			be64_add_cpu(&sbp->sb_icount, tp->t_icount_delta);
		अगर (tp->t_अगरree_delta)
			be64_add_cpu(&sbp->sb_अगरree, tp->t_अगरree_delta);
		अगर (tp->t_fdblocks_delta)
			be64_add_cpu(&sbp->sb_fdblocks, tp->t_fdblocks_delta);
		अगर (tp->t_res_fdblocks_delta)
			be64_add_cpu(&sbp->sb_fdblocks, tp->t_res_fdblocks_delta);
	पूर्ण

	अगर (tp->t_frextents_delta)
		be64_add_cpu(&sbp->sb_frextents, tp->t_frextents_delta);
	अगर (tp->t_res_frextents_delta)
		be64_add_cpu(&sbp->sb_frextents, tp->t_res_frextents_delta);

	अगर (tp->t_dblocks_delta) अणु
		be64_add_cpu(&sbp->sb_dblocks, tp->t_dblocks_delta);
		whole = 1;
	पूर्ण
	अगर (tp->t_agcount_delta) अणु
		be32_add_cpu(&sbp->sb_agcount, tp->t_agcount_delta);
		whole = 1;
	पूर्ण
	अगर (tp->t_imaxpct_delta) अणु
		sbp->sb_imax_pct += tp->t_imaxpct_delta;
		whole = 1;
	पूर्ण
	अगर (tp->t_rextsize_delta) अणु
		be32_add_cpu(&sbp->sb_rextsize, tp->t_rextsize_delta);
		whole = 1;
	पूर्ण
	अगर (tp->t_rbmblocks_delta) अणु
		be32_add_cpu(&sbp->sb_rbmblocks, tp->t_rbmblocks_delta);
		whole = 1;
	पूर्ण
	अगर (tp->t_rblocks_delta) अणु
		be64_add_cpu(&sbp->sb_rblocks, tp->t_rblocks_delta);
		whole = 1;
	पूर्ण
	अगर (tp->t_rextents_delta) अणु
		be64_add_cpu(&sbp->sb_rextents, tp->t_rextents_delta);
		whole = 1;
	पूर्ण
	अगर (tp->t_rextslog_delta) अणु
		sbp->sb_rextslog += tp->t_rextslog_delta;
		whole = 1;
	पूर्ण

	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_SB_BUF);
	अगर (whole)
		/*
		 * Log the whole thing, the fields are noncontiguous.
		 */
		xfs_trans_log_buf(tp, bp, 0, माप(xfs_dsb_t) - 1);
	अन्यथा
		/*
		 * Since all the modअगरiable fields are contiguous, we
		 * can get away with this.
		 */
		xfs_trans_log_buf(tp, bp, दुरत्व(xfs_dsb_t, sb_icount),
				  दुरत्व(xfs_dsb_t, sb_frextents) +
				  माप(sbp->sb_frextents) - 1);
पूर्ण

/*
 * xfs_trans_unreserve_and_mod_sb() is called to release unused reservations and
 * apply superblock counter changes to the in-core superblock.  The
 * t_res_fdblocks_delta and t_res_frextents_delta fields are explicitly NOT
 * applied to the in-core superblock.  The idea is that that has alपढ़ोy been
 * करोne.
 *
 * If we are not logging superblock counters, then the inode allocated/मुक्त and
 * used block counts are not updated in the on disk superblock. In this हाल,
 * XFS_TRANS_SB_सूचीTY will not be set when the transaction is updated but we
 * still need to update the incore superblock with the changes.
 *
 * Deltas क्रम the inode count are +/-64, hence we use a large batch size of 128
 * so we करोn't need to take the counter lock on every update.
 */
#घोषणा XFS_ICOUNT_BATCH	128

व्योम
xfs_trans_unreserve_and_mod_sb(
	काष्ठा xfs_trans	*tp)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	bool			rsvd = (tp->t_flags & XFS_TRANS_RESERVE) != 0;
	पूर्णांक64_t			blkdelta = 0;
	पूर्णांक64_t			rtxdelta = 0;
	पूर्णांक64_t			idelta = 0;
	पूर्णांक64_t			अगरreedelta = 0;
	पूर्णांक			error;

	/* calculate deltas */
	अगर (tp->t_blk_res > 0)
		blkdelta = tp->t_blk_res;
	अगर ((tp->t_fdblocks_delta != 0) &&
	    (xfs_sb_version_haslazysbcount(&mp->m_sb) ||
	     (tp->t_flags & XFS_TRANS_SB_सूचीTY)))
	        blkdelta += tp->t_fdblocks_delta;

	अगर (tp->t_rtx_res > 0)
		rtxdelta = tp->t_rtx_res;
	अगर ((tp->t_frextents_delta != 0) &&
	    (tp->t_flags & XFS_TRANS_SB_सूचीTY))
		rtxdelta += tp->t_frextents_delta;

	अगर (xfs_sb_version_haslazysbcount(&mp->m_sb) ||
	     (tp->t_flags & XFS_TRANS_SB_सूचीTY)) अणु
		idelta = tp->t_icount_delta;
		अगरreedelta = tp->t_अगरree_delta;
	पूर्ण

	/* apply the per-cpu counters */
	अगर (blkdelta) अणु
		error = xfs_mod_fdblocks(mp, blkdelta, rsvd);
		ASSERT(!error);
	पूर्ण

	अगर (idelta)
		percpu_counter_add_batch(&mp->m_icount, idelta,
					 XFS_ICOUNT_BATCH);

	अगर (अगरreedelta)
		percpu_counter_add(&mp->m_अगरree, अगरreedelta);

	अगर (rtxdelta == 0 && !(tp->t_flags & XFS_TRANS_SB_सूचीTY))
		वापस;

	/* apply reमुख्यing deltas */
	spin_lock(&mp->m_sb_lock);
	mp->m_sb.sb_fdblocks += tp->t_fdblocks_delta + tp->t_res_fdblocks_delta;
	mp->m_sb.sb_icount += idelta;
	mp->m_sb.sb_अगरree += अगरreedelta;
	mp->m_sb.sb_frextents += rtxdelta;
	mp->m_sb.sb_dblocks += tp->t_dblocks_delta;
	mp->m_sb.sb_agcount += tp->t_agcount_delta;
	mp->m_sb.sb_imax_pct += tp->t_imaxpct_delta;
	mp->m_sb.sb_rextsize += tp->t_rextsize_delta;
	mp->m_sb.sb_rbmblocks += tp->t_rbmblocks_delta;
	mp->m_sb.sb_rblocks += tp->t_rblocks_delta;
	mp->m_sb.sb_rextents += tp->t_rextents_delta;
	mp->m_sb.sb_rextslog += tp->t_rextslog_delta;
	spin_unlock(&mp->m_sb_lock);

	/*
	 * Debug checks outside of the spinlock so they करोn't lock up the
	 * machine अगर they fail.
	 */
	ASSERT(mp->m_sb.sb_imax_pct >= 0);
	ASSERT(mp->m_sb.sb_rextslog >= 0);
	वापस;
पूर्ण

/* Add the given log item to the transaction's list of log items. */
व्योम
xfs_trans_add_item(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_log_item	*lip)
अणु
	ASSERT(lip->li_mountp == tp->t_mountp);
	ASSERT(lip->li_ailp == tp->t_mountp->m_ail);
	ASSERT(list_empty(&lip->li_trans));
	ASSERT(!test_bit(XFS_LI_सूचीTY, &lip->li_flags));

	list_add_tail(&lip->li_trans, &tp->t_items);
	trace_xfs_trans_add_item(tp, _RET_IP_);
पूर्ण

/*
 * Unlink the log item from the transaction. the log item is no दीर्घer
 * considered dirty in this transaction, as the linked transaction has
 * finished, either by पात or commit completion.
 */
व्योम
xfs_trans_del_item(
	काष्ठा xfs_log_item	*lip)
अणु
	clear_bit(XFS_LI_सूचीTY, &lip->li_flags);
	list_del_init(&lip->li_trans);
पूर्ण

/* Detach and unlock all of the items in a transaction */
अटल व्योम
xfs_trans_मुक्त_items(
	काष्ठा xfs_trans	*tp,
	bool			पात)
अणु
	काष्ठा xfs_log_item	*lip, *next;

	trace_xfs_trans_मुक्त_items(tp, _RET_IP_);

	list_क्रम_each_entry_safe(lip, next, &tp->t_items, li_trans) अणु
		xfs_trans_del_item(lip);
		अगर (पात)
			set_bit(XFS_LI_ABORTED, &lip->li_flags);
		अगर (lip->li_ops->iop_release)
			lip->li_ops->iop_release(lip);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
xfs_log_item_batch_insert(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_ail_cursor	*cur,
	काष्ठा xfs_log_item	**log_items,
	पूर्णांक			nr_items,
	xfs_lsn_t		commit_lsn)
अणु
	पूर्णांक	i;

	spin_lock(&ailp->ail_lock);
	/* xfs_trans_ail_update_bulk drops ailp->ail_lock */
	xfs_trans_ail_update_bulk(ailp, cur, log_items, nr_items, commit_lsn);

	क्रम (i = 0; i < nr_items; i++) अणु
		काष्ठा xfs_log_item *lip = log_items[i];

		अगर (lip->li_ops->iop_unpin)
			lip->li_ops->iop_unpin(lip, 0);
	पूर्ण
पूर्ण

/*
 * Bulk operation version of xfs_trans_committed that takes a log vector of
 * items to insert पूर्णांकo the AIL. This uses bulk AIL insertion techniques to
 * minimise lock traffic.
 *
 * If we are called with the पातed flag set, it is because a log ग_लिखो during
 * a CIL checkpoपूर्णांक commit has failed. In this हाल, all the items in the
 * checkpoपूर्णांक have alपढ़ोy gone through iop_committed and iop_committing, which
 * means that checkpoपूर्णांक commit पात handling is treated exactly the same
 * as an iclog ग_लिखो error even though we haven't started any IO yet. Hence in
 * this हाल all we need to करो is iop_committed processing, followed by an
 * iop_unpin(पातed) call.
 *
 * The AIL cursor is used to optimise the insert process. If commit_lsn is not
 * at the end of the AIL, the insert cursor aव्योमs the need to walk
 * the AIL to find the insertion poपूर्णांक on every xfs_log_item_batch_insert()
 * call. This saves a lot of needless list walking and is a net win, even
 * though it slightly increases that amount of AIL lock traffic to set it up
 * and tear it करोwn.
 */
व्योम
xfs_trans_committed_bulk(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_log_vec	*log_vector,
	xfs_lsn_t		commit_lsn,
	bool			पातed)
अणु
#घोषणा LOG_ITEM_BATCH_SIZE	32
	काष्ठा xfs_log_item	*log_items[LOG_ITEM_BATCH_SIZE];
	काष्ठा xfs_log_vec	*lv;
	काष्ठा xfs_ail_cursor	cur;
	पूर्णांक			i = 0;

	spin_lock(&ailp->ail_lock);
	xfs_trans_ail_cursor_last(ailp, &cur, commit_lsn);
	spin_unlock(&ailp->ail_lock);

	/* unpin all the log items */
	क्रम (lv = log_vector; lv; lv = lv->lv_next ) अणु
		काष्ठा xfs_log_item	*lip = lv->lv_item;
		xfs_lsn_t		item_lsn;

		अगर (पातed)
			set_bit(XFS_LI_ABORTED, &lip->li_flags);

		अगर (lip->li_ops->flags & XFS_ITEM_RELEASE_WHEN_COMMITTED) अणु
			lip->li_ops->iop_release(lip);
			जारी;
		पूर्ण

		अगर (lip->li_ops->iop_committed)
			item_lsn = lip->li_ops->iop_committed(lip, commit_lsn);
		अन्यथा
			item_lsn = commit_lsn;

		/* item_lsn of -1 means the item needs no further processing */
		अगर (XFS_LSN_CMP(item_lsn, (xfs_lsn_t)-1) == 0)
			जारी;

		/*
		 * अगर we are पातing the operation, no poपूर्णांक in inserting the
		 * object पूर्णांकo the AIL as we are in a shutकरोwn situation.
		 */
		अगर (पातed) अणु
			ASSERT(XFS_FORCED_SHUTDOWN(ailp->ail_mount));
			अगर (lip->li_ops->iop_unpin)
				lip->li_ops->iop_unpin(lip, 1);
			जारी;
		पूर्ण

		अगर (item_lsn != commit_lsn) अणु

			/*
			 * Not a bulk update option due to unusual item_lsn.
			 * Push पूर्णांकo AIL immediately, rechecking the lsn once
			 * we have the ail lock. Then unpin the item. This करोes
			 * not affect the AIL cursor the bulk insert path is
			 * using.
			 */
			spin_lock(&ailp->ail_lock);
			अगर (XFS_LSN_CMP(item_lsn, lip->li_lsn) > 0)
				xfs_trans_ail_update(ailp, lip, item_lsn);
			अन्यथा
				spin_unlock(&ailp->ail_lock);
			अगर (lip->li_ops->iop_unpin)
				lip->li_ops->iop_unpin(lip, 0);
			जारी;
		पूर्ण

		/* Item is a candidate क्रम bulk AIL insert.  */
		log_items[i++] = lv->lv_item;
		अगर (i >= LOG_ITEM_BATCH_SIZE) अणु
			xfs_log_item_batch_insert(ailp, &cur, log_items,
					LOG_ITEM_BATCH_SIZE, commit_lsn);
			i = 0;
		पूर्ण
	पूर्ण

	/* make sure we insert the reमुख्यder! */
	अगर (i)
		xfs_log_item_batch_insert(ailp, &cur, log_items, i, commit_lsn);

	spin_lock(&ailp->ail_lock);
	xfs_trans_ail_cursor_करोne(&cur);
	spin_unlock(&ailp->ail_lock);
पूर्ण

/*
 * Commit the given transaction to the log.
 *
 * XFS disk error handling mechanism is not based on a typical
 * transaction पात mechanism. Logically after the fileप्रणाली
 * माला_लो marked 'SHUTDOWN', we can't let any new transactions
 * be durable - ie. committed to disk - because some metadata might
 * be inconsistent. In such हालs, this वापसs an error, and the
 * caller may assume that all locked objects joined to the transaction
 * have alपढ़ोy been unlocked as अगर the commit had succeeded.
 * Do not reference the transaction काष्ठाure after this call.
 */
अटल पूर्णांक
__xfs_trans_commit(
	काष्ठा xfs_trans	*tp,
	bool			regrant)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	xfs_lsn_t		commit_lsn = -1;
	पूर्णांक			error = 0;
	पूर्णांक			sync = tp->t_flags & XFS_TRANS_SYNC;

	trace_xfs_trans_commit(tp, _RET_IP_);

	/*
	 * Finish deferred items on final commit. Only permanent transactions
	 * should ever have deferred ops.
	 */
	WARN_ON_ONCE(!list_empty(&tp->t_dfops) &&
		     !(tp->t_flags & XFS_TRANS_PERM_LOG_RES));
	अगर (!regrant && (tp->t_flags & XFS_TRANS_PERM_LOG_RES)) अणु
		error = xfs_defer_finish_noroll(&tp);
		अगर (error)
			जाओ out_unreserve;
	पूर्ण

	/*
	 * If there is nothing to be logged by the transaction,
	 * then unlock all of the items associated with the
	 * transaction and मुक्त the transaction काष्ठाure.
	 * Also make sure to वापस any reserved blocks to
	 * the मुक्त pool.
	 */
	अगर (!(tp->t_flags & XFS_TRANS_सूचीTY))
		जाओ out_unreserve;

	अगर (XFS_FORCED_SHUTDOWN(mp)) अणु
		error = -EIO;
		जाओ out_unreserve;
	पूर्ण

	ASSERT(tp->t_ticket != शून्य);

	/*
	 * If we need to update the superblock, then करो it now.
	 */
	अगर (tp->t_flags & XFS_TRANS_SB_सूचीTY)
		xfs_trans_apply_sb_deltas(tp);
	xfs_trans_apply_dquot_deltas(tp);

	xfs_log_commit_cil(mp, tp, &commit_lsn, regrant);

	xfs_trans_मुक्त(tp);

	/*
	 * If the transaction needs to be synchronous, then क्रमce the
	 * log out now and रुको क्रम it.
	 */
	अगर (sync) अणु
		error = xfs_log_क्रमce_lsn(mp, commit_lsn, XFS_LOG_SYNC, शून्य);
		XFS_STATS_INC(mp, xs_trans_sync);
	पूर्ण अन्यथा अणु
		XFS_STATS_INC(mp, xs_trans_async);
	पूर्ण

	वापस error;

out_unreserve:
	xfs_trans_unreserve_and_mod_sb(tp);

	/*
	 * It is indeed possible क्रम the transaction to be not dirty but
	 * the dqinfo portion to be.  All that means is that we have some
	 * (non-persistent) quota reservations that need to be unreserved.
	 */
	xfs_trans_unreserve_and_mod_dquots(tp);
	अगर (tp->t_ticket) अणु
		अगर (regrant && !XLOG_FORCED_SHUTDOWN(mp->m_log))
			xfs_log_ticket_regrant(mp->m_log, tp->t_ticket);
		अन्यथा
			xfs_log_ticket_ungrant(mp->m_log, tp->t_ticket);
		tp->t_ticket = शून्य;
	पूर्ण
	xfs_trans_मुक्त_items(tp, !!error);
	xfs_trans_मुक्त(tp);

	XFS_STATS_INC(mp, xs_trans_empty);
	वापस error;
पूर्ण

पूर्णांक
xfs_trans_commit(
	काष्ठा xfs_trans	*tp)
अणु
	वापस __xfs_trans_commit(tp, false);
पूर्ण

/*
 * Unlock all of the transaction's items and मुक्त the transaction.
 * The transaction must not have modअगरied any of its items, because
 * there is no way to restore them to their previous state.
 *
 * If the transaction has made a log reservation, make sure to release
 * it as well.
 */
व्योम
xfs_trans_cancel(
	काष्ठा xfs_trans	*tp)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	bool			dirty = (tp->t_flags & XFS_TRANS_सूचीTY);

	trace_xfs_trans_cancel(tp, _RET_IP_);

	अगर (tp->t_flags & XFS_TRANS_PERM_LOG_RES)
		xfs_defer_cancel(tp);

	/*
	 * See अगर the caller is relying on us to shut करोwn the
	 * fileप्रणाली.  This happens in paths where we detect
	 * corruption and decide to give up.
	 */
	अगर (dirty && !XFS_FORCED_SHUTDOWN(mp)) अणु
		XFS_ERROR_REPORT("xfs_trans_cancel", XFS_ERRLEVEL_LOW, mp);
		xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
	पूर्ण
#अगर_घोषित DEBUG
	अगर (!dirty && !XFS_FORCED_SHUTDOWN(mp)) अणु
		काष्ठा xfs_log_item *lip;

		list_क्रम_each_entry(lip, &tp->t_items, li_trans)
			ASSERT(!xlog_item_is_पूर्णांकent_करोne(lip));
	पूर्ण
#पूर्ण_अगर
	xfs_trans_unreserve_and_mod_sb(tp);
	xfs_trans_unreserve_and_mod_dquots(tp);

	अगर (tp->t_ticket) अणु
		xfs_log_ticket_ungrant(mp->m_log, tp->t_ticket);
		tp->t_ticket = शून्य;
	पूर्ण

	xfs_trans_मुक्त_items(tp, dirty);
	xfs_trans_मुक्त(tp);
पूर्ण

/*
 * Roll from one trans in the sequence of PERMANENT transactions to
 * the next: permanent transactions are only flushed out when
 * committed with xfs_trans_commit(), but we still want as soon
 * as possible to let chunks of it go to the log. So we commit the
 * chunk we've been working on and get a new transaction to जारी.
 */
पूर्णांक
xfs_trans_roll(
	काष्ठा xfs_trans	**tpp)
अणु
	काष्ठा xfs_trans	*trans = *tpp;
	काष्ठा xfs_trans_res	tres;
	पूर्णांक			error;

	trace_xfs_trans_roll(trans, _RET_IP_);

	/*
	 * Copy the critical parameters from one trans to the next.
	 */
	tres.tr_logres = trans->t_log_res;
	tres.tr_logcount = trans->t_log_count;

	*tpp = xfs_trans_dup(trans);

	/*
	 * Commit the current transaction.
	 * If this commit failed, then it'd just unlock those items that
	 * are not marked ihold. That also means that a fileप्रणाली shutकरोwn
	 * is in progress. The caller takes the responsibility to cancel
	 * the duplicate transaction that माला_लो वापसed.
	 */
	error = __xfs_trans_commit(trans, true);
	अगर (error)
		वापस error;

	/*
	 * Reserve space in the log क्रम the next transaction.
	 * This also pushes items in the "AIL", the list of logged items,
	 * out to disk अगर they are taking up space at the tail of the log
	 * that we want to use.  This requires that either nothing be locked
	 * across this call, or that anything that is locked be logged in
	 * the prior and the next transactions.
	 */
	tres.tr_logflags = XFS_TRANS_PERM_LOG_RES;
	वापस xfs_trans_reserve(*tpp, &tres, 0, 0);
पूर्ण

/*
 * Allocate an transaction, lock and join the inode to it, and reserve quota.
 *
 * The caller must ensure that the on-disk dquots attached to this inode have
 * alपढ़ोy been allocated and initialized.  The caller is responsible क्रम
 * releasing ILOCK_EXCL अगर a new transaction is वापसed.
 */
पूर्णांक
xfs_trans_alloc_inode(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_trans_res	*resv,
	अचिन्हित पूर्णांक		dblocks,
	अचिन्हित पूर्णांक		rblocks,
	bool			क्रमce,
	काष्ठा xfs_trans	**tpp)
अणु
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	bool			retried = false;
	पूर्णांक			error;

retry:
	error = xfs_trans_alloc(mp, resv, dblocks,
			rblocks / mp->m_sb.sb_rextsize,
			क्रमce ? XFS_TRANS_RESERVE : 0, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	error = xfs_qm_dqattach_locked(ip, false);
	अगर (error) अणु
		/* Caller should have allocated the dquots! */
		ASSERT(error != -ENOENT);
		जाओ out_cancel;
	पूर्ण

	error = xfs_trans_reserve_quota_nblks(tp, ip, dblocks, rblocks, क्रमce);
	अगर ((error == -EDQUOT || error == -ENOSPC) && !retried) अणु
		xfs_trans_cancel(tp);
		xfs_iunlock(ip, XFS_ILOCK_EXCL);
		xfs_blockgc_मुक्त_quota(ip, 0);
		retried = true;
		जाओ retry;
	पूर्ण
	अगर (error)
		जाओ out_cancel;

	*tpp = tp;
	वापस 0;

out_cancel:
	xfs_trans_cancel(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

/*
 * Allocate an transaction in preparation क्रम inode creation by reserving quota
 * against the given dquots.  Callers are not required to hold any inode locks.
 */
पूर्णांक
xfs_trans_alloc_icreate(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans_res	*resv,
	काष्ठा xfs_dquot	*udqp,
	काष्ठा xfs_dquot	*gdqp,
	काष्ठा xfs_dquot	*pdqp,
	अचिन्हित पूर्णांक		dblocks,
	काष्ठा xfs_trans	**tpp)
अणु
	काष्ठा xfs_trans	*tp;
	bool			retried = false;
	पूर्णांक			error;

retry:
	error = xfs_trans_alloc(mp, resv, dblocks, 0, 0, &tp);
	अगर (error)
		वापस error;

	error = xfs_trans_reserve_quota_icreate(tp, udqp, gdqp, pdqp, dblocks);
	अगर ((error == -EDQUOT || error == -ENOSPC) && !retried) अणु
		xfs_trans_cancel(tp);
		xfs_blockgc_मुक्त_dquots(mp, udqp, gdqp, pdqp, 0);
		retried = true;
		जाओ retry;
	पूर्ण
	अगर (error) अणु
		xfs_trans_cancel(tp);
		वापस error;
	पूर्ण

	*tpp = tp;
	वापस 0;
पूर्ण

/*
 * Allocate an transaction, lock and join the inode to it, and reserve quota
 * in preparation क्रम inode attribute changes that include uid, gid, or prid
 * changes.
 *
 * The caller must ensure that the on-disk dquots attached to this inode have
 * alपढ़ोy been allocated and initialized.  The ILOCK will be dropped when the
 * transaction is committed or cancelled.
 */
पूर्णांक
xfs_trans_alloc_ichange(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_dquot	*new_udqp,
	काष्ठा xfs_dquot	*new_gdqp,
	काष्ठा xfs_dquot	*new_pdqp,
	bool			क्रमce,
	काष्ठा xfs_trans	**tpp)
अणु
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_dquot	*udqp;
	काष्ठा xfs_dquot	*gdqp;
	काष्ठा xfs_dquot	*pdqp;
	bool			retried = false;
	पूर्णांक			error;

retry:
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ichange, 0, 0, 0, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);

	error = xfs_qm_dqattach_locked(ip, false);
	अगर (error) अणु
		/* Caller should have allocated the dquots! */
		ASSERT(error != -ENOENT);
		जाओ out_cancel;
	पूर्ण

	/*
	 * For each quota type, skip quota reservations अगर the inode's dquots
	 * now match the ones that came from the caller, or the caller didn't
	 * pass one in.  The inode's dquots can change अगर we drop the ILOCK to
	 * perक्रमm a blockgc scan, so we must preserve the caller's arguments.
	 */
	udqp = (new_udqp != ip->i_udquot) ? new_udqp : शून्य;
	gdqp = (new_gdqp != ip->i_gdquot) ? new_gdqp : शून्य;
	pdqp = (new_pdqp != ip->i_pdquot) ? new_pdqp : शून्य;
	अगर (udqp || gdqp || pdqp) अणु
		अचिन्हित पूर्णांक	qflags = XFS_QMOPT_RES_REGBLKS;

		अगर (क्रमce)
			qflags |= XFS_QMOPT_FORCE_RES;

		/*
		 * Reserve enough quota to handle blocks on disk and reserved
		 * क्रम a delayed allocation.  We'll actually transfer the
		 * delalloc reservation between dquots at chown समय, even
		 * though that part is only semi-transactional.
		 */
		error = xfs_trans_reserve_quota_bydquots(tp, mp, udqp, gdqp,
				pdqp, ip->i_nblocks + ip->i_delayed_blks,
				1, qflags);
		अगर ((error == -EDQUOT || error == -ENOSPC) && !retried) अणु
			xfs_trans_cancel(tp);
			xfs_blockgc_मुक्त_dquots(mp, udqp, gdqp, pdqp, 0);
			retried = true;
			जाओ retry;
		पूर्ण
		अगर (error)
			जाओ out_cancel;
	पूर्ण

	*tpp = tp;
	वापस 0;

out_cancel:
	xfs_trans_cancel(tp);
	वापस error;
पूर्ण
