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
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_inode_item.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_log.h"

/*
 * Deferred Operations in XFS
 *
 * Due to the way locking rules work in XFS, certain transactions (block
 * mapping and unmapping, typically) have permanent reservations so that
 * we can roll the transaction to adhere to AG locking order rules and
 * to unlock buffers between metadata updates.  Prior to rmap/reflink,
 * the mapping code had a mechanism to perक्रमm these deferrals क्रम
 * extents that were going to be मुक्तd; this code makes that facility
 * more generic.
 *
 * When adding the reverse mapping and reflink features, it became
 * necessary to perक्रमm complex remapping multi-transactions to comply
 * with AG locking order rules, and to be able to spपढ़ो a single
 * refcount update operation (an operation on an n-block extent can
 * update as many as n records!) among multiple transactions.  XFS can
 * roll a transaction to facilitate this, but using this facility
 * requires us to log "intent" items in हाल log recovery needs to
 * reकरो the operation, and to log "done" items to indicate that reकरो
 * is not necessary.
 *
 * Deferred work is tracked in xfs_defer_pending items.  Each pending
 * item tracks one type of deferred work.  Incoming work items (which
 * have not yet had an पूर्णांकent logged) are attached to a pending item
 * on the करोp_पूर्णांकake list, where they रुको क्रम the caller to finish
 * the deferred operations.
 *
 * Finishing a set of deferred operations is an involved process.  To
 * start, we define "rolling a deferred-op transaction" as follows:
 *
 * > For each xfs_defer_pending item on the करोp_पूर्णांकake list,
 *   - Sort the work items in AG order.  XFS locking
 *     order rules require us to lock buffers in AG order.
 *   - Create a log पूर्णांकent item क्रम that type.
 *   - Attach it to the pending item.
 *   - Move the pending item from the करोp_पूर्णांकake list to the
 *     करोp_pending list.
 * > Roll the transaction.
 *
 * NOTE: To aव्योम exceeding the transaction reservation, we limit the
 * number of items that we attach to a given xfs_defer_pending.
 *
 * The actual finishing process looks like this:
 *
 * > For each xfs_defer_pending in the करोp_pending list,
 *   - Roll the deferred-op transaction as above.
 *   - Create a log करोne item क्रम that type, and attach it to the
 *     log पूर्णांकent item.
 *   - For each work item attached to the log पूर्णांकent item,
 *     * Perक्रमm the described action.
 *     * Attach the work item to the log करोne item.
 *     * If the result of करोing the work was -EAGAIN, ->finish work
 *       wants a new transaction.  See the "Requesting a Fresh
 *       Transaction जबतक Finishing Deferred Work" section below क्रम
 *       details.
 *
 * The key here is that we must log an पूर्णांकent item क्रम all pending
 * work items every समय we roll the transaction, and that we must log
 * a करोne item as soon as the work is completed.  With this mechanism
 * we can perक्रमm complex remapping operations, chaining पूर्णांकent items
 * as needed.
 *
 * Requesting a Fresh Transaction जबतक Finishing Deferred Work
 *
 * If ->finish_item decides that it needs a fresh transaction to
 * finish the work, it must ask its caller (xfs_defer_finish) क्रम a
 * continuation.  The most likely cause of this circumstance are the
 * refcount adjust functions deciding that they've logged enough items
 * to be at risk of exceeding the transaction reservation.
 *
 * To get a fresh transaction, we want to log the existing log करोne
 * item to prevent the log पूर्णांकent item from replaying, immediately log
 * a new log पूर्णांकent item with the unfinished work items, roll the
 * transaction, and re-call ->finish_item wherever it left off.  The
 * log करोne item and the new log पूर्णांकent item must be in the same
 * transaction or atomicity cannot be guaranteed; defer_finish ensures
 * that this happens.
 *
 * This requires some coordination between ->finish_item and
 * defer_finish.  Upon deciding to request a new transaction,
 * ->finish_item should update the current work item to reflect the
 * unfinished work.  Next, it should reset the log करोne item's list
 * count to the number of items finished, and वापस -EAGAIN.
 * defer_finish sees the -EAGAIN, logs the new log पूर्णांकent item
 * with the reमुख्यing work items, and leaves the xfs_defer_pending
 * item at the head of the करोp_work queue.  Then it rolls the
 * transaction and picks up processing where it left off.  It is
 * required that ->finish_item must be careful to leave enough
 * transaction reservation to fit the new log पूर्णांकent item.
 *
 * This is an example of remapping the extent (E, E+B) पूर्णांकo file X at
 * offset A and dealing with the extent (C, C+B) alपढ़ोy being mapped
 * there:
 * +-------------------------------------------------+
 * | Unmap file X startblock C offset A length B     | t0
 * | Intent to reduce refcount क्रम extent (C, B)     |
 * | Intent to हटाओ rmap (X, C, A, B)              |
 * | Intent to मुक्त extent (D, 1) (bmbt block)       |
 * | Intent to map (X, A, B) at startblock E         |
 * +-------------------------------------------------+
 * | Map file X startblock E offset A length B       | t1
 * | Done mapping (X, E, A, B)                       |
 * | Intent to increase refcount क्रम extent (E, B)   |
 * | Intent to add rmap (X, E, A, B)                 |
 * +-------------------------------------------------+
 * | Reduce refcount क्रम extent (C, B)               | t2
 * | Done reducing refcount क्रम extent (C, 9)        |
 * | Intent to reduce refcount क्रम extent (C+9, B-9) |
 * | (ran out of space after 9 refcount updates)     |
 * +-------------------------------------------------+
 * | Reduce refcount क्रम extent (C+9, B+9)           | t3
 * | Done reducing refcount क्रम extent (C+9, B-9)    |
 * | Increase refcount क्रम extent (E, B)             |
 * | Done increasing refcount क्रम extent (E, B)      |
 * | Intent to मुक्त extent (C, B)                    |
 * | Intent to मुक्त extent (F, 1) (refcountbt block) |
 * | Intent to हटाओ rmap (F, 1, REFC)              |
 * +-------------------------------------------------+
 * | Remove rmap (X, C, A, B)                        | t4
 * | Done removing rmap (X, C, A, B)                 |
 * | Add rmap (X, E, A, B)                           |
 * | Done adding rmap (X, E, A, B)                   |
 * | Remove rmap (F, 1, REFC)                        |
 * | Done removing rmap (F, 1, REFC)                 |
 * +-------------------------------------------------+
 * | Free extent (C, B)                              | t5
 * | Done मुक्तing extent (C, B)                      |
 * | Free extent (D, 1)                              |
 * | Done मुक्तing extent (D, 1)                      |
 * | Free extent (F, 1)                              |
 * | Done मुक्तing extent (F, 1)                      |
 * +-------------------------------------------------+
 *
 * If we should crash beक्रमe t2 commits, log recovery replays
 * the following पूर्णांकent items:
 *
 * - Intent to reduce refcount क्रम extent (C, B)
 * - Intent to हटाओ rmap (X, C, A, B)
 * - Intent to मुक्त extent (D, 1) (bmbt block)
 * - Intent to increase refcount क्रम extent (E, B)
 * - Intent to add rmap (X, E, A, B)
 *
 * In the process of recovering, it should also generate and take care
 * of these पूर्णांकent items:
 *
 * - Intent to मुक्त extent (C, B)
 * - Intent to मुक्त extent (F, 1) (refcountbt block)
 * - Intent to हटाओ rmap (F, 1, REFC)
 *
 * Note that the continuation requested between t2 and t3 is likely to
 * reoccur.
 */

अटल स्थिर काष्ठा xfs_defer_op_type *defer_op_types[] = अणु
	[XFS_DEFER_OPS_TYPE_BMAP]	= &xfs_bmap_update_defer_type,
	[XFS_DEFER_OPS_TYPE_REFCOUNT]	= &xfs_refcount_update_defer_type,
	[XFS_DEFER_OPS_TYPE_RMAP]	= &xfs_rmap_update_defer_type,
	[XFS_DEFER_OPS_TYPE_FREE]	= &xfs_extent_मुक्त_defer_type,
	[XFS_DEFER_OPS_TYPE_AGFL_FREE]	= &xfs_agfl_मुक्त_defer_type,
पूर्ण;

अटल व्योम
xfs_defer_create_पूर्णांकent(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_defer_pending	*dfp,
	bool				sort)
अणु
	स्थिर काष्ठा xfs_defer_op_type	*ops = defer_op_types[dfp->dfp_type];

	अगर (!dfp->dfp_पूर्णांकent)
		dfp->dfp_पूर्णांकent = ops->create_पूर्णांकent(tp, &dfp->dfp_work,
						     dfp->dfp_count, sort);
पूर्ण

/*
 * For each pending item in the पूर्णांकake list, log its पूर्णांकent item and the
 * associated extents, then add the entire पूर्णांकake list to the end of
 * the pending list.
 */
STATIC व्योम
xfs_defer_create_पूर्णांकents(
	काष्ठा xfs_trans		*tp)
अणु
	काष्ठा xfs_defer_pending	*dfp;

	list_क्रम_each_entry(dfp, &tp->t_dfops, dfp_list) अणु
		trace_xfs_defer_create_पूर्णांकent(tp->t_mountp, dfp);
		xfs_defer_create_पूर्णांकent(tp, dfp, true);
	पूर्ण
पूर्ण

/* Abort all the पूर्णांकents that were committed. */
STATIC व्योम
xfs_defer_trans_पात(
	काष्ठा xfs_trans		*tp,
	काष्ठा list_head		*करोp_pending)
अणु
	काष्ठा xfs_defer_pending	*dfp;
	स्थिर काष्ठा xfs_defer_op_type	*ops;

	trace_xfs_defer_trans_पात(tp, _RET_IP_);

	/* Abort पूर्णांकent items that करोn't have a करोne item. */
	list_क्रम_each_entry(dfp, करोp_pending, dfp_list) अणु
		ops = defer_op_types[dfp->dfp_type];
		trace_xfs_defer_pending_पात(tp->t_mountp, dfp);
		अगर (dfp->dfp_पूर्णांकent && !dfp->dfp_करोne) अणु
			ops->पात_पूर्णांकent(dfp->dfp_पूर्णांकent);
			dfp->dfp_पूर्णांकent = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/* Roll a transaction so we can करो some deferred op processing. */
STATIC पूर्णांक
xfs_defer_trans_roll(
	काष्ठा xfs_trans		**tpp)
अणु
	काष्ठा xfs_trans		*tp = *tpp;
	काष्ठा xfs_buf_log_item		*bli;
	काष्ठा xfs_inode_log_item	*ili;
	काष्ठा xfs_log_item		*lip;
	काष्ठा xfs_buf			*bplist[XFS_DEFER_OPS_NR_BUFS];
	काष्ठा xfs_inode		*iplist[XFS_DEFER_OPS_NR_INODES];
	अचिन्हित पूर्णांक			ordered = 0; /* biपंचांगap */
	पूर्णांक				bpcount = 0, ipcount = 0;
	पूर्णांक				i;
	पूर्णांक				error;

	BUILD_BUG_ON(NBBY * माप(ordered) < XFS_DEFER_OPS_NR_BUFS);

	list_क्रम_each_entry(lip, &tp->t_items, li_trans) अणु
		चयन (lip->li_type) अणु
		हाल XFS_LI_BUF:
			bli = container_of(lip, काष्ठा xfs_buf_log_item,
					   bli_item);
			अगर (bli->bli_flags & XFS_BLI_HOLD) अणु
				अगर (bpcount >= XFS_DEFER_OPS_NR_BUFS) अणु
					ASSERT(0);
					वापस -EFSCORRUPTED;
				पूर्ण
				अगर (bli->bli_flags & XFS_BLI_ORDERED)
					ordered |= (1U << bpcount);
				अन्यथा
					xfs_trans_dirty_buf(tp, bli->bli_buf);
				bplist[bpcount++] = bli->bli_buf;
			पूर्ण
			अवरोध;
		हाल XFS_LI_INODE:
			ili = container_of(lip, काष्ठा xfs_inode_log_item,
					   ili_item);
			अगर (ili->ili_lock_flags == 0) अणु
				अगर (ipcount >= XFS_DEFER_OPS_NR_INODES) अणु
					ASSERT(0);
					वापस -EFSCORRUPTED;
				पूर्ण
				xfs_trans_log_inode(tp, ili->ili_inode,
						    XFS_ILOG_CORE);
				iplist[ipcount++] = ili->ili_inode;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	trace_xfs_defer_trans_roll(tp, _RET_IP_);

	/*
	 * Roll the transaction.  Rolling always given a new transaction (even
	 * अगर committing the old one fails!) to hand back to the caller, so we
	 * join the held resources to the new transaction so that we always
	 * वापस with the held resources joined to @tpp, no matter what
	 * happened.
	 */
	error = xfs_trans_roll(tpp);
	tp = *tpp;

	/* Rejoin the joined inodes. */
	क्रम (i = 0; i < ipcount; i++)
		xfs_trans_ijoin(tp, iplist[i], 0);

	/* Rejoin the buffers and dirty them so the log moves क्रमward. */
	क्रम (i = 0; i < bpcount; i++) अणु
		xfs_trans_bjoin(tp, bplist[i]);
		अगर (ordered & (1U << i))
			xfs_trans_ordered_buf(tp, bplist[i]);
		xfs_trans_bhold(tp, bplist[i]);
	पूर्ण

	अगर (error)
		trace_xfs_defer_trans_roll_error(tp, error);
	वापस error;
पूर्ण

/*
 * Free up any items left in the list.
 */
अटल व्योम
xfs_defer_cancel_list(
	काष्ठा xfs_mount		*mp,
	काष्ठा list_head		*करोp_list)
अणु
	काष्ठा xfs_defer_pending	*dfp;
	काष्ठा xfs_defer_pending	*pli;
	काष्ठा list_head		*pwi;
	काष्ठा list_head		*n;
	स्थिर काष्ठा xfs_defer_op_type	*ops;

	/*
	 * Free the pending items.  Caller should alपढ़ोy have arranged
	 * क्रम the पूर्णांकent items to be released.
	 */
	list_क्रम_each_entry_safe(dfp, pli, करोp_list, dfp_list) अणु
		ops = defer_op_types[dfp->dfp_type];
		trace_xfs_defer_cancel_list(mp, dfp);
		list_del(&dfp->dfp_list);
		list_क्रम_each_safe(pwi, n, &dfp->dfp_work) अणु
			list_del(pwi);
			dfp->dfp_count--;
			ops->cancel_item(pwi);
		पूर्ण
		ASSERT(dfp->dfp_count == 0);
		kmem_मुक्त(dfp);
	पूर्ण
पूर्ण

/*
 * Prevent a log पूर्णांकent item from pinning the tail of the log by logging a
 * करोne item to release the पूर्णांकent item; and then log a new पूर्णांकent item.
 * The caller should provide a fresh transaction and roll it after we're करोne.
 */
अटल पूर्णांक
xfs_defer_relog(
	काष्ठा xfs_trans		**tpp,
	काष्ठा list_head		*dfops)
अणु
	काष्ठा xlog			*log = (*tpp)->t_mountp->m_log;
	काष्ठा xfs_defer_pending	*dfp;
	xfs_lsn_t			threshold_lsn = शून्यCOMMITLSN;


	ASSERT((*tpp)->t_flags & XFS_TRANS_PERM_LOG_RES);

	list_क्रम_each_entry(dfp, dfops, dfp_list) अणु
		/*
		 * If the log पूर्णांकent item क्रम this deferred op is not a part of
		 * the current log checkpoपूर्णांक, relog the पूर्णांकent item to keep
		 * the log tail moving क्रमward.  We're ok with this being racy
		 * because an incorrect decision means we'll be a little slower
		 * at pushing the tail.
		 */
		अगर (dfp->dfp_पूर्णांकent == शून्य ||
		    xfs_log_item_in_current_chkpt(dfp->dfp_पूर्णांकent))
			जारी;

		/*
		 * Figure out where we need the tail to be in order to मुख्यtain
		 * the minimum required मुक्त space in the log.  Only sample
		 * the log threshold once per call.
		 */
		अगर (threshold_lsn == शून्यCOMMITLSN) अणु
			threshold_lsn = xlog_grant_push_threshold(log, 0);
			अगर (threshold_lsn == शून्यCOMMITLSN)
				अवरोध;
		पूर्ण
		अगर (XFS_LSN_CMP(dfp->dfp_पूर्णांकent->li_lsn, threshold_lsn) >= 0)
			जारी;

		trace_xfs_defer_relog_पूर्णांकent((*tpp)->t_mountp, dfp);
		XFS_STATS_INC((*tpp)->t_mountp, defer_relog);
		dfp->dfp_पूर्णांकent = xfs_trans_item_relog(dfp->dfp_पूर्णांकent, *tpp);
	पूर्ण

	अगर ((*tpp)->t_flags & XFS_TRANS_सूचीTY)
		वापस xfs_defer_trans_roll(tpp);
	वापस 0;
पूर्ण

/*
 * Log an पूर्णांकent-करोne item क्रम the first pending पूर्णांकent, and finish the work
 * items.
 */
अटल पूर्णांक
xfs_defer_finish_one(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_defer_pending	*dfp)
अणु
	स्थिर काष्ठा xfs_defer_op_type	*ops = defer_op_types[dfp->dfp_type];
	काष्ठा xfs_btree_cur		*state = शून्य;
	काष्ठा list_head		*li, *n;
	पूर्णांक				error;

	trace_xfs_defer_pending_finish(tp->t_mountp, dfp);

	dfp->dfp_करोne = ops->create_करोne(tp, dfp->dfp_पूर्णांकent, dfp->dfp_count);
	list_क्रम_each_safe(li, n, &dfp->dfp_work) अणु
		list_del(li);
		dfp->dfp_count--;
		error = ops->finish_item(tp, dfp->dfp_करोne, li, &state);
		अगर (error == -EAGAIN) अणु
			/*
			 * Caller wants a fresh transaction; put the work item
			 * back on the list and log a new log पूर्णांकent item to
			 * replace the old one.  See "Requesting a Fresh
			 * Transaction जबतक Finishing Deferred Work" above.
			 */
			list_add(li, &dfp->dfp_work);
			dfp->dfp_count++;
			dfp->dfp_करोne = शून्य;
			dfp->dfp_पूर्णांकent = शून्य;
			xfs_defer_create_पूर्णांकent(tp, dfp, false);
		पूर्ण

		अगर (error)
			जाओ out;
	पूर्ण

	/* Done with the dfp, मुक्त it. */
	list_del(&dfp->dfp_list);
	kmem_मुक्त(dfp);
out:
	अगर (ops->finish_cleanup)
		ops->finish_cleanup(tp, state, error);
	वापस error;
पूर्ण

/*
 * Finish all the pending work.  This involves logging पूर्णांकent items क्रम
 * any work items that wandered in since the last transaction roll (अगर
 * one has even happened), rolling the transaction, and finishing the
 * work items in the first item on the logged-and-pending list.
 *
 * If an inode is provided, relog it to the new transaction.
 */
पूर्णांक
xfs_defer_finish_noroll(
	काष्ठा xfs_trans		**tp)
अणु
	काष्ठा xfs_defer_pending	*dfp;
	पूर्णांक				error = 0;
	LIST_HEAD(करोp_pending);

	ASSERT((*tp)->t_flags & XFS_TRANS_PERM_LOG_RES);

	trace_xfs_defer_finish(*tp, _RET_IP_);

	/* Until we run out of pending work to finish... */
	जबतक (!list_empty(&करोp_pending) || !list_empty(&(*tp)->t_dfops)) अणु
		/*
		 * Deferred items that are created in the process of finishing
		 * other deferred work items should be queued at the head of
		 * the pending list, which माला_दो them ahead of the deferred work
		 * that was created by the caller.  This keeps the number of
		 * pending work items to a minimum, which decreases the amount
		 * of समय that any one पूर्णांकent item can stick around in memory,
		 * pinning the log tail.
		 */
		xfs_defer_create_पूर्णांकents(*tp);
		list_splice_init(&(*tp)->t_dfops, &करोp_pending);

		error = xfs_defer_trans_roll(tp);
		अगर (error)
			जाओ out_shutकरोwn;

		/* Possibly relog पूर्णांकent items to keep the log moving. */
		error = xfs_defer_relog(tp, &करोp_pending);
		अगर (error)
			जाओ out_shutकरोwn;

		dfp = list_first_entry(&करोp_pending, काष्ठा xfs_defer_pending,
				       dfp_list);
		error = xfs_defer_finish_one(*tp, dfp);
		अगर (error && error != -EAGAIN)
			जाओ out_shutकरोwn;
	पूर्ण

	trace_xfs_defer_finish_करोne(*tp, _RET_IP_);
	वापस 0;

out_shutकरोwn:
	xfs_defer_trans_पात(*tp, &करोp_pending);
	xfs_क्रमce_shutकरोwn((*tp)->t_mountp, SHUTDOWN_CORRUPT_INCORE);
	trace_xfs_defer_finish_error(*tp, error);
	xfs_defer_cancel_list((*tp)->t_mountp, &करोp_pending);
	xfs_defer_cancel(*tp);
	वापस error;
पूर्ण

पूर्णांक
xfs_defer_finish(
	काष्ठा xfs_trans	**tp)
अणु
	पूर्णांक			error;

	/*
	 * Finish and roll the transaction once more to aव्योम वापसing to the
	 * caller with a dirty transaction.
	 */
	error = xfs_defer_finish_noroll(tp);
	अगर (error)
		वापस error;
	अगर ((*tp)->t_flags & XFS_TRANS_सूचीTY) अणु
		error = xfs_defer_trans_roll(tp);
		अगर (error) अणु
			xfs_क्रमce_shutकरोwn((*tp)->t_mountp,
					   SHUTDOWN_CORRUPT_INCORE);
			वापस error;
		पूर्ण
	पूर्ण

	/* Reset LOWMODE now that we've finished all the dfops. */
	ASSERT(list_empty(&(*tp)->t_dfops));
	(*tp)->t_flags &= ~XFS_TRANS_LOWMODE;
	वापस 0;
पूर्ण

व्योम
xfs_defer_cancel(
	काष्ठा xfs_trans	*tp)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;

	trace_xfs_defer_cancel(tp, _RET_IP_);
	xfs_defer_cancel_list(mp, &tp->t_dfops);
पूर्ण

/* Add an item क्रम later deferred processing. */
व्योम
xfs_defer_add(
	काष्ठा xfs_trans		*tp,
	क्रमागत xfs_defer_ops_type		type,
	काष्ठा list_head		*li)
अणु
	काष्ठा xfs_defer_pending	*dfp = शून्य;
	स्थिर काष्ठा xfs_defer_op_type	*ops;

	ASSERT(tp->t_flags & XFS_TRANS_PERM_LOG_RES);
	BUILD_BUG_ON(ARRAY_SIZE(defer_op_types) != XFS_DEFER_OPS_TYPE_MAX);

	/*
	 * Add the item to a pending item at the end of the पूर्णांकake list.
	 * If the last pending item has the same type, reuse it.  Else,
	 * create a new pending item at the end of the पूर्णांकake list.
	 */
	अगर (!list_empty(&tp->t_dfops)) अणु
		dfp = list_last_entry(&tp->t_dfops,
				काष्ठा xfs_defer_pending, dfp_list);
		ops = defer_op_types[dfp->dfp_type];
		अगर (dfp->dfp_type != type ||
		    (ops->max_items && dfp->dfp_count >= ops->max_items))
			dfp = शून्य;
	पूर्ण
	अगर (!dfp) अणु
		dfp = kmem_alloc(माप(काष्ठा xfs_defer_pending),
				KM_NOFS);
		dfp->dfp_type = type;
		dfp->dfp_पूर्णांकent = शून्य;
		dfp->dfp_करोne = शून्य;
		dfp->dfp_count = 0;
		INIT_LIST_HEAD(&dfp->dfp_work);
		list_add_tail(&dfp->dfp_list, &tp->t_dfops);
	पूर्ण

	list_add_tail(li, &dfp->dfp_work);
	dfp->dfp_count++;
पूर्ण

/*
 * Move deferred ops from one transaction to another and reset the source to
 * initial state. This is primarily used to carry state क्रमward across
 * transaction rolls with pending dfops.
 */
व्योम
xfs_defer_move(
	काष्ठा xfs_trans	*dtp,
	काष्ठा xfs_trans	*stp)
अणु
	list_splice_init(&stp->t_dfops, &dtp->t_dfops);

	/*
	 * Low मुक्त space mode was historically controlled by a dfops field.
	 * This meant that low mode state potentially carried across multiple
	 * transaction rolls. Transfer low mode on a dfops move to preserve
	 * that behavior.
	 */
	dtp->t_flags |= (stp->t_flags & XFS_TRANS_LOWMODE);
	stp->t_flags &= ~XFS_TRANS_LOWMODE;
पूर्ण

/*
 * Prepare a chain of fresh deferred ops work items to be completed later.  Log
 * recovery requires the ability to put off until later the actual finishing
 * work so that it can process unfinished items recovered from the log in
 * correct order.
 *
 * Create and log पूर्णांकent items क्रम all the work that we're capturing so that we
 * can be assured that the items will get replayed अगर the प्रणाली goes करोwn
 * beक्रमe log recovery माला_लो a chance to finish the work it put off.  The entire
 * deferred ops state is transferred to the capture काष्ठाure and the
 * transaction is then पढ़ोy क्रम the caller to commit it.  If there are no
 * पूर्णांकent items to capture, this function वापसs शून्य.
 *
 * If capture_ip is not शून्य, the capture काष्ठाure will obtain an extra
 * reference to the inode.
 */
अटल काष्ठा xfs_defer_capture *
xfs_defer_ops_capture(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_inode		*capture_ip)
अणु
	काष्ठा xfs_defer_capture	*dfc;

	अगर (list_empty(&tp->t_dfops))
		वापस शून्य;

	/* Create an object to capture the defer ops. */
	dfc = kmem_zalloc(माप(*dfc), KM_NOFS);
	INIT_LIST_HEAD(&dfc->dfc_list);
	INIT_LIST_HEAD(&dfc->dfc_dfops);

	xfs_defer_create_पूर्णांकents(tp);

	/* Move the dfops chain and transaction state to the capture काष्ठा. */
	list_splice_init(&tp->t_dfops, &dfc->dfc_dfops);
	dfc->dfc_tpflags = tp->t_flags & XFS_TRANS_LOWMODE;
	tp->t_flags &= ~XFS_TRANS_LOWMODE;

	/* Capture the reमुख्यing block reservations aदीर्घ with the dfops. */
	dfc->dfc_blkres = tp->t_blk_res - tp->t_blk_res_used;
	dfc->dfc_rtxres = tp->t_rtx_res - tp->t_rtx_res_used;

	/* Preserve the log reservation size. */
	dfc->dfc_logres = tp->t_log_res;

	/*
	 * Grab an extra reference to this inode and attach it to the capture
	 * काष्ठाure.
	 */
	अगर (capture_ip) अणु
		ihold(VFS_I(capture_ip));
		dfc->dfc_capture_ip = capture_ip;
	पूर्ण

	वापस dfc;
पूर्ण

/* Release all resources that we used to capture deferred ops. */
व्योम
xfs_defer_ops_release(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_defer_capture	*dfc)
अणु
	xfs_defer_cancel_list(mp, &dfc->dfc_dfops);
	अगर (dfc->dfc_capture_ip)
		xfs_irele(dfc->dfc_capture_ip);
	kmem_मुक्त(dfc);
पूर्ण

/*
 * Capture any deferred ops and commit the transaction.  This is the last step
 * needed to finish a log पूर्णांकent item that we recovered from the log.  If any
 * of the deferred ops operate on an inode, the caller must pass in that inode
 * so that the reference can be transferred to the capture काष्ठाure.  The
 * caller must hold ILOCK_EXCL on the inode, and must unlock it beक्रमe calling
 * xfs_defer_ops_जारी.
 */
पूर्णांक
xfs_defer_ops_capture_and_commit(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_inode		*capture_ip,
	काष्ठा list_head		*capture_list)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_defer_capture	*dfc;
	पूर्णांक				error;

	ASSERT(!capture_ip || xfs_isilocked(capture_ip, XFS_ILOCK_EXCL));

	/* If we करोn't capture anything, commit transaction and निकास. */
	dfc = xfs_defer_ops_capture(tp, capture_ip);
	अगर (!dfc)
		वापस xfs_trans_commit(tp);

	/* Commit the transaction and add the capture काष्ठाure to the list. */
	error = xfs_trans_commit(tp);
	अगर (error) अणु
		xfs_defer_ops_release(mp, dfc);
		वापस error;
	पूर्ण

	list_add_tail(&dfc->dfc_list, capture_list);
	वापस 0;
पूर्ण

/*
 * Attach a chain of captured deferred ops to a new transaction and मुक्त the
 * capture काष्ठाure.  If an inode was captured, it will be passed back to the
 * caller with ILOCK_EXCL held and joined to the transaction with lockflags==0.
 * The caller now owns the inode reference.
 */
व्योम
xfs_defer_ops_जारी(
	काष्ठा xfs_defer_capture	*dfc,
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_inode		**captured_ipp)
अणु
	ASSERT(tp->t_flags & XFS_TRANS_PERM_LOG_RES);
	ASSERT(!(tp->t_flags & XFS_TRANS_सूचीTY));

	/* Lock and join the captured inode to the new transaction. */
	अगर (dfc->dfc_capture_ip) अणु
		xfs_ilock(dfc->dfc_capture_ip, XFS_ILOCK_EXCL);
		xfs_trans_ijoin(tp, dfc->dfc_capture_ip, 0);
	पूर्ण
	*captured_ipp = dfc->dfc_capture_ip;

	/* Move captured dfops chain and state to the transaction. */
	list_splice_init(&dfc->dfc_dfops, &tp->t_dfops);
	tp->t_flags |= dfc->dfc_tpflags;

	kmem_मुक्त(dfc);
पूर्ण
