<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * Copyright (c) 2008 Dave Chinner
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_log.h"

#अगर_घोषित DEBUG
/*
 * Check that the list is sorted as it should be.
 *
 * Called with the ail lock held, but we करोn't want to निश्चित fail with it
 * held otherwise we'll lock everything up and won't be able to debug the
 * cause. Hence we sample and check the state under the AIL lock and वापस अगर
 * everything is fine, otherwise we drop the lock and run the ASSERT checks.
 * Asserts may not be fatal, so pick the lock back up and जारी onwards.
 */
STATIC व्योम
xfs_ail_check(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_log_item	*lip)
	__must_hold(&ailp->ail_lock)
अणु
	काष्ठा xfs_log_item	*prev_lip;
	काष्ठा xfs_log_item	*next_lip;
	xfs_lsn_t		prev_lsn = शून्यCOMMITLSN;
	xfs_lsn_t		next_lsn = शून्यCOMMITLSN;
	xfs_lsn_t		lsn;
	bool			in_ail;


	अगर (list_empty(&ailp->ail_head))
		वापस;

	/*
	 * Sample then check the next and previous entries are valid.
	 */
	in_ail = test_bit(XFS_LI_IN_AIL, &lip->li_flags);
	prev_lip = list_entry(lip->li_ail.prev, काष्ठा xfs_log_item, li_ail);
	अगर (&prev_lip->li_ail != &ailp->ail_head)
		prev_lsn = prev_lip->li_lsn;
	next_lip = list_entry(lip->li_ail.next, काष्ठा xfs_log_item, li_ail);
	अगर (&next_lip->li_ail != &ailp->ail_head)
		next_lsn = next_lip->li_lsn;
	lsn = lip->li_lsn;

	अगर (in_ail &&
	    (prev_lsn == शून्यCOMMITLSN || XFS_LSN_CMP(prev_lsn, lsn) <= 0) &&
	    (next_lsn == शून्यCOMMITLSN || XFS_LSN_CMP(next_lsn, lsn) >= 0))
		वापस;

	spin_unlock(&ailp->ail_lock);
	ASSERT(in_ail);
	ASSERT(prev_lsn == शून्यCOMMITLSN || XFS_LSN_CMP(prev_lsn, lsn) <= 0);
	ASSERT(next_lsn == शून्यCOMMITLSN || XFS_LSN_CMP(next_lsn, lsn) >= 0);
	spin_lock(&ailp->ail_lock);
पूर्ण
#अन्यथा /* !DEBUG */
#घोषणा	xfs_ail_check(a,l)
#पूर्ण_अगर /* DEBUG */

/*
 * Return a poपूर्णांकer to the last item in the AIL.  If the AIL is empty, then
 * वापस शून्य.
 */
अटल काष्ठा xfs_log_item *
xfs_ail_max(
	काष्ठा xfs_ail  *ailp)
अणु
	अगर (list_empty(&ailp->ail_head))
		वापस शून्य;

	वापस list_entry(ailp->ail_head.prev, काष्ठा xfs_log_item, li_ail);
पूर्ण

/*
 * Return a poपूर्णांकer to the item which follows the given item in the AIL.  If
 * the given item is the last item in the list, then वापस शून्य.
 */
अटल काष्ठा xfs_log_item *
xfs_ail_next(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_log_item	*lip)
अणु
	अगर (lip->li_ail.next == &ailp->ail_head)
		वापस शून्य;

	वापस list_first_entry(&lip->li_ail, काष्ठा xfs_log_item, li_ail);
पूर्ण

/*
 * This is called by the log manager code to determine the LSN of the tail of
 * the log.  This is exactly the LSN of the first item in the AIL.  If the AIL
 * is empty, then this function वापसs 0.
 *
 * We need the AIL lock in order to get a coherent पढ़ो of the lsn of the last
 * item in the AIL.
 */
अटल xfs_lsn_t
__xfs_ail_min_lsn(
	काष्ठा xfs_ail		*ailp)
अणु
	काष्ठा xfs_log_item	*lip = xfs_ail_min(ailp);

	अगर (lip)
		वापस lip->li_lsn;
	वापस 0;
पूर्ण

xfs_lsn_t
xfs_ail_min_lsn(
	काष्ठा xfs_ail		*ailp)
अणु
	xfs_lsn_t		lsn;

	spin_lock(&ailp->ail_lock);
	lsn = __xfs_ail_min_lsn(ailp);
	spin_unlock(&ailp->ail_lock);

	वापस lsn;
पूर्ण

/*
 * Return the maximum lsn held in the AIL, or zero अगर the AIL is empty.
 */
अटल xfs_lsn_t
xfs_ail_max_lsn(
	काष्ठा xfs_ail		*ailp)
अणु
	xfs_lsn_t       	lsn = 0;
	काष्ठा xfs_log_item	*lip;

	spin_lock(&ailp->ail_lock);
	lip = xfs_ail_max(ailp);
	अगर (lip)
		lsn = lip->li_lsn;
	spin_unlock(&ailp->ail_lock);

	वापस lsn;
पूर्ण

/*
 * The cursor keeps track of where our current traversal is up to by tracking
 * the next item in the list क्रम us. However, क्रम this to be safe, removing an
 * object from the AIL needs to invalidate any cursor that poपूर्णांकs to it. hence
 * the traversal cursor needs to be linked to the काष्ठा xfs_ail so that
 * deletion can search all the active cursors क्रम invalidation.
 */
STATIC व्योम
xfs_trans_ail_cursor_init(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_ail_cursor	*cur)
अणु
	cur->item = शून्य;
	list_add_tail(&cur->list, &ailp->ail_cursors);
पूर्ण

/*
 * Get the next item in the traversal and advance the cursor.  If the cursor
 * was invalidated (indicated by a lip of 1), restart the traversal.
 */
काष्ठा xfs_log_item *
xfs_trans_ail_cursor_next(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_ail_cursor	*cur)
अणु
	काष्ठा xfs_log_item	*lip = cur->item;

	अगर ((uपूर्णांकptr_t)lip & 1)
		lip = xfs_ail_min(ailp);
	अगर (lip)
		cur->item = xfs_ail_next(ailp, lip);
	वापस lip;
पूर्ण

/*
 * When the traversal is complete, we need to हटाओ the cursor from the list
 * of traversing cursors.
 */
व्योम
xfs_trans_ail_cursor_करोne(
	काष्ठा xfs_ail_cursor	*cur)
अणु
	cur->item = शून्य;
	list_del_init(&cur->list);
पूर्ण

/*
 * Invalidate any cursor that is poपूर्णांकing to this item. This is called when an
 * item is हटाओd from the AIL. Any cursor poपूर्णांकing to this object is now
 * invalid and the traversal needs to be terminated so it करोesn't reference a
 * मुक्तd object. We set the low bit of the cursor item poपूर्णांकer so we can
 * distinguish between an invalidation and the end of the list when getting the
 * next item from the cursor.
 */
STATIC व्योम
xfs_trans_ail_cursor_clear(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_ail_cursor	*cur;

	list_क्रम_each_entry(cur, &ailp->ail_cursors, list) अणु
		अगर (cur->item == lip)
			cur->item = (काष्ठा xfs_log_item *)
					((uपूर्णांकptr_t)cur->item | 1);
	पूर्ण
पूर्ण

/*
 * Find the first item in the AIL with the given @lsn by searching in ascending
 * LSN order and initialise the cursor to poपूर्णांक to the next item क्रम a
 * ascending traversal.  Pass a @lsn of zero to initialise the cursor to the
 * first item in the AIL. Returns शून्य अगर the list is empty.
 */
काष्ठा xfs_log_item *
xfs_trans_ail_cursor_first(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_ail_cursor	*cur,
	xfs_lsn_t		lsn)
अणु
	काष्ठा xfs_log_item	*lip;

	xfs_trans_ail_cursor_init(ailp, cur);

	अगर (lsn == 0) अणु
		lip = xfs_ail_min(ailp);
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(lip, &ailp->ail_head, li_ail) अणु
		अगर (XFS_LSN_CMP(lip->li_lsn, lsn) >= 0)
			जाओ out;
	पूर्ण
	वापस शून्य;

out:
	अगर (lip)
		cur->item = xfs_ail_next(ailp, lip);
	वापस lip;
पूर्ण

अटल काष्ठा xfs_log_item *
__xfs_trans_ail_cursor_last(
	काष्ठा xfs_ail		*ailp,
	xfs_lsn_t		lsn)
अणु
	काष्ठा xfs_log_item	*lip;

	list_क्रम_each_entry_reverse(lip, &ailp->ail_head, li_ail) अणु
		अगर (XFS_LSN_CMP(lip->li_lsn, lsn) <= 0)
			वापस lip;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Find the last item in the AIL with the given @lsn by searching in descending
 * LSN order and initialise the cursor to poपूर्णांक to that item.  If there is no
 * item with the value of @lsn, then it sets the cursor to the last item with an
 * LSN lower than @lsn.  Returns शून्य अगर the list is empty.
 */
काष्ठा xfs_log_item *
xfs_trans_ail_cursor_last(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_ail_cursor	*cur,
	xfs_lsn_t		lsn)
अणु
	xfs_trans_ail_cursor_init(ailp, cur);
	cur->item = __xfs_trans_ail_cursor_last(ailp, lsn);
	वापस cur->item;
पूर्ण

/*
 * Splice the log item list पूर्णांकo the AIL at the given LSN. We splice to the
 * tail of the given LSN to मुख्यtain insert order क्रम push traversals. The
 * cursor is optional, allowing repeated updates to the same LSN to aव्योम
 * repeated traversals.  This should not be called with an empty list.
 */
अटल व्योम
xfs_ail_splice(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_ail_cursor	*cur,
	काष्ठा list_head	*list,
	xfs_lsn_t		lsn)
अणु
	काष्ठा xfs_log_item	*lip;

	ASSERT(!list_empty(list));

	/*
	 * Use the cursor to determine the insertion poपूर्णांक अगर one is
	 * provided.  If not, or अगर the one we got is not valid,
	 * find the place in the AIL where the items beदीर्घ.
	 */
	lip = cur ? cur->item : शून्य;
	अगर (!lip || (uपूर्णांकptr_t)lip & 1)
		lip = __xfs_trans_ail_cursor_last(ailp, lsn);

	/*
	 * If a cursor is provided, we know we're processing the AIL
	 * in lsn order, and future items to be spliced in will
	 * follow the last one being inserted now.  Update the
	 * cursor to poपूर्णांक to that last item, now जबतक we have a
	 * reliable poपूर्णांकer to it.
	 */
	अगर (cur)
		cur->item = list_entry(list->prev, काष्ठा xfs_log_item, li_ail);

	/*
	 * Finally perक्रमm the splice.  Unless the AIL was empty,
	 * lip poपूर्णांकs to the item in the AIL _after_ which the new
	 * items should go.  If lip is null the AIL was empty, so
	 * the new items go at the head of the AIL.
	 */
	अगर (lip)
		list_splice(list, &lip->li_ail);
	अन्यथा
		list_splice(list, &ailp->ail_head);
पूर्ण

/*
 * Delete the given item from the AIL.  Return a poपूर्णांकer to the item.
 */
अटल व्योम
xfs_ail_delete(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_log_item	*lip)
अणु
	xfs_ail_check(ailp, lip);
	list_del(&lip->li_ail);
	xfs_trans_ail_cursor_clear(ailp, lip);
पूर्ण

/*
 * Requeue a failed buffer क्रम ग_लिखोback.
 *
 * We clear the log item failed state here as well, but we have to be careful
 * about reference counts because the only active reference counts on the buffer
 * may be the failed log items. Hence अगर we clear the log item failed state
 * beक्रमe queuing the buffer क्रम IO we can release all active references to
 * the buffer and मुक्त it, leading to use after मुक्त problems in
 * xfs_buf_delwri_queue. It makes no dअगरference to the buffer or log items which
 * order we process them in - the buffer is locked, and we own the buffer list
 * so nothing on them is going to change जबतक we are perक्रमming this action.
 *
 * Hence we can safely queue the buffer क्रम IO beक्रमe we clear the failed log
 * item state, thereक्रमe  always having an active reference to the buffer and
 * aव्योमing the transient zero-reference state that leads to use-after-मुक्त.
 */
अटल अंतरभूत पूर्णांक
xfsaild_resubmit_item(
	काष्ठा xfs_log_item	*lip,
	काष्ठा list_head	*buffer_list)
अणु
	काष्ठा xfs_buf		*bp = lip->li_buf;

	अगर (!xfs_buf_trylock(bp))
		वापस XFS_ITEM_LOCKED;

	अगर (!xfs_buf_delwri_queue(bp, buffer_list)) अणु
		xfs_buf_unlock(bp);
		वापस XFS_ITEM_FLUSHING;
	पूर्ण

	/* रक्षित by ail_lock */
	list_क्रम_each_entry(lip, &bp->b_li_list, li_bio_list) अणु
		अगर (bp->b_flags & _XBF_INODES)
			clear_bit(XFS_LI_FAILED, &lip->li_flags);
		अन्यथा
			xfs_clear_li_failed(lip);
	पूर्ण

	xfs_buf_unlock(bp);
	वापस XFS_ITEM_SUCCESS;
पूर्ण

अटल अंतरभूत uपूर्णांक
xfsaild_push_item(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_log_item	*lip)
अणु
	/*
	 * If log item pinning is enabled, skip the push and track the item as
	 * pinned. This can help induce head-behind-tail conditions.
	 */
	अगर (XFS_TEST_ERROR(false, ailp->ail_mount, XFS_ERRTAG_LOG_ITEM_PIN))
		वापस XFS_ITEM_PINNED;

	/*
	 * Consider the item pinned अगर a push callback is not defined so the
	 * caller will क्रमce the log. This should only happen क्रम पूर्णांकent items
	 * as they are unpinned once the associated करोne item is committed to
	 * the on-disk log.
	 */
	अगर (!lip->li_ops->iop_push)
		वापस XFS_ITEM_PINNED;
	अगर (test_bit(XFS_LI_FAILED, &lip->li_flags))
		वापस xfsaild_resubmit_item(lip, &ailp->ail_buf_list);
	वापस lip->li_ops->iop_push(lip, &ailp->ail_buf_list);
पूर्ण

अटल दीर्घ
xfsaild_push(
	काष्ठा xfs_ail		*ailp)
अणु
	xfs_mount_t		*mp = ailp->ail_mount;
	काष्ठा xfs_ail_cursor	cur;
	काष्ठा xfs_log_item	*lip;
	xfs_lsn_t		lsn;
	xfs_lsn_t		target;
	दीर्घ			tout;
	पूर्णांक			stuck = 0;
	पूर्णांक			flushing = 0;
	पूर्णांक			count = 0;

	/*
	 * If we encountered pinned items or did not finish writing out all
	 * buffers the last समय we ran, क्रमce the log first and रुको क्रम it
	 * beक्रमe pushing again.
	 */
	अगर (ailp->ail_log_flush && ailp->ail_last_pushed_lsn == 0 &&
	    (!list_empty_careful(&ailp->ail_buf_list) ||
	     xfs_ail_min_lsn(ailp))) अणु
		ailp->ail_log_flush = 0;

		XFS_STATS_INC(mp, xs_push_ail_flush);
		xfs_log_क्रमce(mp, XFS_LOG_SYNC);
	पूर्ण

	spin_lock(&ailp->ail_lock);

	/* barrier matches the ail_target update in xfs_ail_push() */
	smp_rmb();
	target = ailp->ail_target;
	ailp->ail_target_prev = target;

	/* we're करोne अगर the AIL is empty or our push has reached the end */
	lip = xfs_trans_ail_cursor_first(ailp, &cur, ailp->ail_last_pushed_lsn);
	अगर (!lip)
		जाओ out_करोne;

	XFS_STATS_INC(mp, xs_push_ail);

	lsn = lip->li_lsn;
	जबतक ((XFS_LSN_CMP(lip->li_lsn, target) <= 0)) अणु
		पूर्णांक	lock_result;

		/*
		 * Note that iop_push may unlock and reacquire the AIL lock.  We
		 * rely on the AIL cursor implementation to be able to deal with
		 * the dropped lock.
		 */
		lock_result = xfsaild_push_item(ailp, lip);
		चयन (lock_result) अणु
		हाल XFS_ITEM_SUCCESS:
			XFS_STATS_INC(mp, xs_push_ail_success);
			trace_xfs_ail_push(lip);

			ailp->ail_last_pushed_lsn = lsn;
			अवरोध;

		हाल XFS_ITEM_FLUSHING:
			/*
			 * The item or its backing buffer is alपढ़ोy being
			 * flushed.  The typical reason क्रम that is that an
			 * inode buffer is locked because we alपढ़ोy pushed the
			 * updates to it as part of inode clustering.
			 *
			 * We करो not want to stop flushing just because lots
			 * of items are alपढ़ोy being flushed, but we need to
			 * re-try the flushing relatively soon अगर most of the
			 * AIL is being flushed.
			 */
			XFS_STATS_INC(mp, xs_push_ail_flushing);
			trace_xfs_ail_flushing(lip);

			flushing++;
			ailp->ail_last_pushed_lsn = lsn;
			अवरोध;

		हाल XFS_ITEM_PINNED:
			XFS_STATS_INC(mp, xs_push_ail_pinned);
			trace_xfs_ail_pinned(lip);

			stuck++;
			ailp->ail_log_flush++;
			अवरोध;
		हाल XFS_ITEM_LOCKED:
			XFS_STATS_INC(mp, xs_push_ail_locked);
			trace_xfs_ail_locked(lip);

			stuck++;
			अवरोध;
		शेष:
			ASSERT(0);
			अवरोध;
		पूर्ण

		count++;

		/*
		 * Are there too many items we can't करो anything with?
		 *
		 * If we are skipping too many items because we can't flush
		 * them or they are alपढ़ोy being flushed, we back off and
		 * given them समय to complete whatever operation is being
		 * करोne. i.e. हटाओ pressure from the AIL जबतक we can't make
		 * progress so traversals करोn't slow करोwn further inserts and
		 * removals to/from the AIL.
		 *
		 * The value of 100 is an arbitrary magic number based on
		 * observation.
		 */
		अगर (stuck > 100)
			अवरोध;

		lip = xfs_trans_ail_cursor_next(ailp, &cur);
		अगर (lip == शून्य)
			अवरोध;
		lsn = lip->li_lsn;
	पूर्ण

out_करोne:
	xfs_trans_ail_cursor_करोne(&cur);
	spin_unlock(&ailp->ail_lock);

	अगर (xfs_buf_delwri_submit_noरुको(&ailp->ail_buf_list))
		ailp->ail_log_flush++;

	अगर (!count || XFS_LSN_CMP(lsn, target) >= 0) अणु
		/*
		 * We reached the target or the AIL is empty, so रुको a bit
		 * दीर्घer क्रम I/O to complete and हटाओ pushed items from the
		 * AIL beक्रमe we start the next scan from the start of the AIL.
		 */
		tout = 50;
		ailp->ail_last_pushed_lsn = 0;
	पूर्ण अन्यथा अगर (((stuck + flushing) * 100) / count > 90) अणु
		/*
		 * Either there is a lot of contention on the AIL or we are
		 * stuck due to operations in progress. "Stuck" in this हाल
		 * is defined as >90% of the items we tried to push were stuck.
		 *
		 * Backoff a bit more to allow some I/O to complete beक्रमe
		 * restarting from the start of the AIL. This prevents us from
		 * spinning on the same items, and अगर they are pinned will all
		 * the restart to issue a log क्रमce to unpin the stuck items.
		 */
		tout = 20;
		ailp->ail_last_pushed_lsn = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Assume we have more work to करो in a लघु जबतक.
		 */
		tout = 10;
	पूर्ण

	वापस tout;
पूर्ण

अटल पूर्णांक
xfsaild(
	व्योम		*data)
अणु
	काष्ठा xfs_ail	*ailp = data;
	दीर्घ		tout = 0;	/* milliseconds */
	अचिन्हित पूर्णांक	noreclaim_flag;

	noreclaim_flag = meदो_स्मृति_noreclaim_save();
	set_मुक्तzable();

	जबतक (1) अणु
		अगर (tout && tout <= 20)
			set_current_state(TASK_KILLABLE);
		अन्यथा
			set_current_state(TASK_INTERRUPTIBLE);

		/*
		 * Check kthपढ़ो_should_stop() after we set the task state to
		 * guarantee that we either see the stop bit and निकास or the
		 * task state is reset to runnable such that it's not scheduled
		 * out indefinitely and detects the stop bit at next iteration.
		 * A memory barrier is included in above task state set to
		 * serialize again kthपढ़ो_stop().
		 */
		अगर (kthपढ़ो_should_stop()) अणु
			__set_current_state(TASK_RUNNING);

			/*
			 * The caller क्रमces out the AIL beक्रमe stopping the
			 * thपढ़ो in the common हाल, which means the delwri
			 * queue is drained. In the shutकरोwn हाल, the queue may
			 * still hold relogged buffers that haven't been
			 * submitted because they were pinned since added to the
			 * queue.
			 *
			 * Log I/O error processing stales the underlying buffer
			 * and clears the delwri state, expecting the buf to be
			 * हटाओd on the next submission attempt. That won't
			 * happen अगर we're shutting करोwn, so this is the last
			 * opportunity to release such buffers from the queue.
			 */
			ASSERT(list_empty(&ailp->ail_buf_list) ||
			       XFS_FORCED_SHUTDOWN(ailp->ail_mount));
			xfs_buf_delwri_cancel(&ailp->ail_buf_list);
			अवरोध;
		पूर्ण

		spin_lock(&ailp->ail_lock);

		/*
		 * Idle अगर the AIL is empty and we are not racing with a target
		 * update. We check the AIL after we set the task to a sleep
		 * state to guarantee that we either catch an ail_target update
		 * or that a wake_up resets the state to TASK_RUNNING.
		 * Otherwise, we run the risk of sleeping indefinitely.
		 *
		 * The barrier matches the ail_target update in xfs_ail_push().
		 */
		smp_rmb();
		अगर (!xfs_ail_min(ailp) &&
		    ailp->ail_target == ailp->ail_target_prev &&
		    list_empty(&ailp->ail_buf_list)) अणु
			spin_unlock(&ailp->ail_lock);
			मुक्तzable_schedule();
			tout = 0;
			जारी;
		पूर्ण
		spin_unlock(&ailp->ail_lock);

		अगर (tout)
			मुक्तzable_schedule_समयout(msecs_to_jअगरfies(tout));

		__set_current_state(TASK_RUNNING);

		try_to_मुक्तze();

		tout = xfsaild_push(ailp);
	पूर्ण

	meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	वापस 0;
पूर्ण

/*
 * This routine is called to move the tail of the AIL क्रमward.  It करोes this by
 * trying to flush items in the AIL whose lsns are below the given
 * threshold_lsn.
 *
 * The push is run asynchronously in a workqueue, which means the caller needs
 * to handle रुकोing on the async flush क्रम space to become available.
 * We करोn't want to पूर्णांकerrupt any push that is in progress, hence we only queue
 * work अगर we set the pushing bit appropriately.
 *
 * We करो this unlocked - we only need to know whether there is anything in the
 * AIL at the समय we are called. We करोn't need to access the contents of
 * any of the objects, so the lock is not needed.
 */
व्योम
xfs_ail_push(
	काष्ठा xfs_ail		*ailp,
	xfs_lsn_t		threshold_lsn)
अणु
	काष्ठा xfs_log_item	*lip;

	lip = xfs_ail_min(ailp);
	अगर (!lip || XFS_FORCED_SHUTDOWN(ailp->ail_mount) ||
	    XFS_LSN_CMP(threshold_lsn, ailp->ail_target) <= 0)
		वापस;

	/*
	 * Ensure that the new target is noticed in push code beक्रमe it clears
	 * the XFS_AIL_PUSHING_BIT.
	 */
	smp_wmb();
	xfs_trans_ail_copy_lsn(ailp, &ailp->ail_target, &threshold_lsn);
	smp_wmb();

	wake_up_process(ailp->ail_task);
पूर्ण

/*
 * Push out all items in the AIL immediately
 */
व्योम
xfs_ail_push_all(
	काष्ठा xfs_ail  *ailp)
अणु
	xfs_lsn_t       threshold_lsn = xfs_ail_max_lsn(ailp);

	अगर (threshold_lsn)
		xfs_ail_push(ailp, threshold_lsn);
पूर्ण

/*
 * Push out all items in the AIL immediately and रुको until the AIL is empty.
 */
व्योम
xfs_ail_push_all_sync(
	काष्ठा xfs_ail  *ailp)
अणु
	काष्ठा xfs_log_item	*lip;
	DEFINE_WAIT(रुको);

	spin_lock(&ailp->ail_lock);
	जबतक ((lip = xfs_ail_max(ailp)) != शून्य) अणु
		prepare_to_रुको(&ailp->ail_empty, &रुको, TASK_UNINTERRUPTIBLE);
		ailp->ail_target = lip->li_lsn;
		wake_up_process(ailp->ail_task);
		spin_unlock(&ailp->ail_lock);
		schedule();
		spin_lock(&ailp->ail_lock);
	पूर्ण
	spin_unlock(&ailp->ail_lock);

	finish_रुको(&ailp->ail_empty, &रुको);
पूर्ण

व्योम
xfs_ail_update_finish(
	काष्ठा xfs_ail		*ailp,
	xfs_lsn_t		old_lsn) __releases(ailp->ail_lock)
अणु
	काष्ठा xfs_mount	*mp = ailp->ail_mount;

	/* अगर the tail lsn hasn't changed, don't करो updates or wakeups. */
	अगर (!old_lsn || old_lsn == __xfs_ail_min_lsn(ailp)) अणु
		spin_unlock(&ailp->ail_lock);
		वापस;
	पूर्ण

	अगर (!XFS_FORCED_SHUTDOWN(mp))
		xlog_assign_tail_lsn_locked(mp);

	अगर (list_empty(&ailp->ail_head))
		wake_up_all(&ailp->ail_empty);
	spin_unlock(&ailp->ail_lock);
	xfs_log_space_wake(mp);
पूर्ण

/*
 * xfs_trans_ail_update - bulk AIL insertion operation.
 *
 * @xfs_trans_ail_update takes an array of log items that all need to be
 * positioned at the same LSN in the AIL. If an item is not in the AIL, it will
 * be added.  Otherwise, it will be repositioned  by removing it and re-adding
 * it to the AIL. If we move the first item in the AIL, update the log tail to
 * match the new minimum LSN in the AIL.
 *
 * This function takes the AIL lock once to execute the update operations on
 * all the items in the array, and as such should not be called with the AIL
 * lock held. As a result, once we have the AIL lock, we need to check each log
 * item LSN to confirm it needs to be moved क्रमward in the AIL.
 *
 * To optimise the insert operation, we delete all the items from the AIL in
 * the first pass, moving them पूर्णांकo a temporary list, then splice the temporary
 * list पूर्णांकo the correct position in the AIL. This aव्योमs needing to करो an
 * insert operation on every item.
 *
 * This function must be called with the AIL lock held.  The lock is dropped
 * beक्रमe वापसing.
 */
व्योम
xfs_trans_ail_update_bulk(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_ail_cursor	*cur,
	काष्ठा xfs_log_item	**log_items,
	पूर्णांक			nr_items,
	xfs_lsn_t		lsn) __releases(ailp->ail_lock)
अणु
	काष्ठा xfs_log_item	*mlip;
	xfs_lsn_t		tail_lsn = 0;
	पूर्णांक			i;
	LIST_HEAD(पंचांगp);

	ASSERT(nr_items > 0);		/* Not required, but true. */
	mlip = xfs_ail_min(ailp);

	क्रम (i = 0; i < nr_items; i++) अणु
		काष्ठा xfs_log_item *lip = log_items[i];
		अगर (test_and_set_bit(XFS_LI_IN_AIL, &lip->li_flags)) अणु
			/* check अगर we really need to move the item */
			अगर (XFS_LSN_CMP(lsn, lip->li_lsn) <= 0)
				जारी;

			trace_xfs_ail_move(lip, lip->li_lsn, lsn);
			अगर (mlip == lip && !tail_lsn)
				tail_lsn = lip->li_lsn;

			xfs_ail_delete(ailp, lip);
		पूर्ण अन्यथा अणु
			trace_xfs_ail_insert(lip, 0, lsn);
		पूर्ण
		lip->li_lsn = lsn;
		list_add(&lip->li_ail, &पंचांगp);
	पूर्ण

	अगर (!list_empty(&पंचांगp))
		xfs_ail_splice(ailp, cur, &पंचांगp, lsn);

	xfs_ail_update_finish(ailp, tail_lsn);
पूर्ण

/* Insert a log item पूर्णांकo the AIL. */
व्योम
xfs_trans_ail_insert(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_log_item	*lip,
	xfs_lsn_t		lsn)
अणु
	spin_lock(&ailp->ail_lock);
	xfs_trans_ail_update_bulk(ailp, शून्य, &lip, 1, lsn);
पूर्ण

/*
 * Delete one log item from the AIL.
 *
 * If this item was at the tail of the AIL, वापस the LSN of the log item so
 * that we can use it to check अगर the LSN of the tail of the log has moved
 * when finishing up the AIL delete process in xfs_ail_update_finish().
 */
xfs_lsn_t
xfs_ail_delete_one(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_log_item	*mlip = xfs_ail_min(ailp);
	xfs_lsn_t		lsn = lip->li_lsn;

	trace_xfs_ail_delete(lip, mlip->li_lsn, lip->li_lsn);
	xfs_ail_delete(ailp, lip);
	clear_bit(XFS_LI_IN_AIL, &lip->li_flags);
	lip->li_lsn = 0;

	अगर (mlip == lip)
		वापस lsn;
	वापस 0;
पूर्ण

व्योम
xfs_trans_ail_delete(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			shutकरोwn_type)
अणु
	काष्ठा xfs_ail		*ailp = lip->li_ailp;
	काष्ठा xfs_mount	*mp = ailp->ail_mount;
	xfs_lsn_t		tail_lsn;

	spin_lock(&ailp->ail_lock);
	अगर (!test_bit(XFS_LI_IN_AIL, &lip->li_flags)) अणु
		spin_unlock(&ailp->ail_lock);
		अगर (shutकरोwn_type && !XFS_FORCED_SHUTDOWN(mp)) अणु
			xfs_alert_tag(mp, XFS_PTAG_AILDELETE,
	"%s: attempting to delete a log item that is not in the AIL",
					__func__);
			xfs_क्रमce_shutकरोwn(mp, shutकरोwn_type);
		पूर्ण
		वापस;
	पूर्ण

	/* xfs_ail_update_finish() drops the AIL lock */
	xfs_clear_li_failed(lip);
	tail_lsn = xfs_ail_delete_one(ailp, lip);
	xfs_ail_update_finish(ailp, tail_lsn);
पूर्ण

पूर्णांक
xfs_trans_ail_init(
	xfs_mount_t	*mp)
अणु
	काष्ठा xfs_ail	*ailp;

	ailp = kmem_zalloc(माप(काष्ठा xfs_ail), KM_MAYFAIL);
	अगर (!ailp)
		वापस -ENOMEM;

	ailp->ail_mount = mp;
	INIT_LIST_HEAD(&ailp->ail_head);
	INIT_LIST_HEAD(&ailp->ail_cursors);
	spin_lock_init(&ailp->ail_lock);
	INIT_LIST_HEAD(&ailp->ail_buf_list);
	init_रुकोqueue_head(&ailp->ail_empty);

	ailp->ail_task = kthपढ़ो_run(xfsaild, ailp, "xfsaild/%s",
			ailp->ail_mount->m_super->s_id);
	अगर (IS_ERR(ailp->ail_task))
		जाओ out_मुक्त_ailp;

	mp->m_ail = ailp;
	वापस 0;

out_मुक्त_ailp:
	kmem_मुक्त(ailp);
	वापस -ENOMEM;
पूर्ण

व्योम
xfs_trans_ail_destroy(
	xfs_mount_t	*mp)
अणु
	काष्ठा xfs_ail	*ailp = mp->m_ail;

	kthपढ़ो_stop(ailp->ail_task);
	kmem_मुक्त(ailp);
पूर्ण
