<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000,2002,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_TRANS_PRIV_H__
#घोषणा	__XFS_TRANS_PRIV_H__

काष्ठा xfs_log_item;
काष्ठा xfs_mount;
काष्ठा xfs_trans;
काष्ठा xfs_ail;
काष्ठा xfs_log_vec;


व्योम	xfs_trans_init(काष्ठा xfs_mount *);
व्योम	xfs_trans_add_item(काष्ठा xfs_trans *, काष्ठा xfs_log_item *);
व्योम	xfs_trans_del_item(काष्ठा xfs_log_item *);
व्योम	xfs_trans_unreserve_and_mod_sb(काष्ठा xfs_trans *tp);

व्योम	xfs_trans_committed_bulk(काष्ठा xfs_ail *ailp, काष्ठा xfs_log_vec *lv,
				xfs_lsn_t commit_lsn, bool पातed);
/*
 * AIL traversal cursor.
 *
 * Rather than using a generation number क्रम detecting changes in the ail, use
 * a cursor that is रक्षित by the ail lock. The aild cursor exists in the
 * काष्ठा xfs_ail, but other traversals can declare it on the stack and link it
 * to the ail list.
 *
 * When an object is deleted from or moved पूर्णांक the AIL, the cursor list is
 * searched to see अगर the object is a designated cursor item. If it is, it is
 * deleted from the cursor so that the next समय the cursor is used traversal
 * will वापस to the start.
 *
 * This means a traversal colliding with a removal will cause a restart of the
 * list scan, rather than any insertion or deletion anywhere in the list. The
 * low bit of the item poपूर्णांकer is set अगर the cursor has been invalidated so
 * that we can tell the dअगरference between invalidation and reaching the end
 * of the list to trigger traversal restarts.
 */
काष्ठा xfs_ail_cursor अणु
	काष्ठा list_head	list;
	काष्ठा xfs_log_item	*item;
पूर्ण;

/*
 * Private AIL काष्ठाures.
 *
 * Eventually we need to drive the locking in here as well.
 */
काष्ठा xfs_ail अणु
	काष्ठा xfs_mount	*ail_mount;
	काष्ठा task_काष्ठा	*ail_task;
	काष्ठा list_head	ail_head;
	xfs_lsn_t		ail_target;
	xfs_lsn_t		ail_target_prev;
	काष्ठा list_head	ail_cursors;
	spinlock_t		ail_lock;
	xfs_lsn_t		ail_last_pushed_lsn;
	पूर्णांक			ail_log_flush;
	काष्ठा list_head	ail_buf_list;
	रुको_queue_head_t	ail_empty;
पूर्ण;

/*
 * From xfs_trans_ail.c
 */
व्योम	xfs_trans_ail_update_bulk(काष्ठा xfs_ail *ailp,
				काष्ठा xfs_ail_cursor *cur,
				काष्ठा xfs_log_item **log_items, पूर्णांक nr_items,
				xfs_lsn_t lsn) __releases(ailp->ail_lock);
/*
 * Return a poपूर्णांकer to the first item in the AIL.  If the AIL is empty, then
 * वापस शून्य.
 */
अटल अंतरभूत काष्ठा xfs_log_item *
xfs_ail_min(
	काष्ठा xfs_ail  *ailp)
अणु
	वापस list_first_entry_or_null(&ailp->ail_head, काष्ठा xfs_log_item,
					li_ail);
पूर्ण

अटल अंतरभूत व्योम
xfs_trans_ail_update(
	काष्ठा xfs_ail		*ailp,
	काष्ठा xfs_log_item	*lip,
	xfs_lsn_t		lsn) __releases(ailp->ail_lock)
अणु
	xfs_trans_ail_update_bulk(ailp, शून्य, &lip, 1, lsn);
पूर्ण

व्योम xfs_trans_ail_insert(काष्ठा xfs_ail *ailp, काष्ठा xfs_log_item *lip,
		xfs_lsn_t lsn);

xfs_lsn_t xfs_ail_delete_one(काष्ठा xfs_ail *ailp, काष्ठा xfs_log_item *lip);
व्योम xfs_ail_update_finish(काष्ठा xfs_ail *ailp, xfs_lsn_t old_lsn)
			__releases(ailp->ail_lock);
व्योम xfs_trans_ail_delete(काष्ठा xfs_log_item *lip, पूर्णांक shutकरोwn_type);

व्योम			xfs_ail_push(काष्ठा xfs_ail *, xfs_lsn_t);
व्योम			xfs_ail_push_all(काष्ठा xfs_ail *);
व्योम			xfs_ail_push_all_sync(काष्ठा xfs_ail *);
काष्ठा xfs_log_item	*xfs_ail_min(काष्ठा xfs_ail  *ailp);
xfs_lsn_t		xfs_ail_min_lsn(काष्ठा xfs_ail *ailp);

काष्ठा xfs_log_item *	xfs_trans_ail_cursor_first(काष्ठा xfs_ail *ailp,
					काष्ठा xfs_ail_cursor *cur,
					xfs_lsn_t lsn);
काष्ठा xfs_log_item *	xfs_trans_ail_cursor_last(काष्ठा xfs_ail *ailp,
					काष्ठा xfs_ail_cursor *cur,
					xfs_lsn_t lsn);
काष्ठा xfs_log_item *	xfs_trans_ail_cursor_next(काष्ठा xfs_ail *ailp,
					काष्ठा xfs_ail_cursor *cur);
व्योम			xfs_trans_ail_cursor_करोne(काष्ठा xfs_ail_cursor *cur);

#अगर BITS_PER_LONG != 64
अटल अंतरभूत व्योम
xfs_trans_ail_copy_lsn(
	काष्ठा xfs_ail	*ailp,
	xfs_lsn_t	*dst,
	xfs_lsn_t	*src)
अणु
	ASSERT(माप(xfs_lsn_t) == 8);	/* करोn't lock अगर it shrinks */
	spin_lock(&ailp->ail_lock);
	*dst = *src;
	spin_unlock(&ailp->ail_lock);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
xfs_trans_ail_copy_lsn(
	काष्ठा xfs_ail	*ailp,
	xfs_lsn_t	*dst,
	xfs_lsn_t	*src)
अणु
	ASSERT(माप(xfs_lsn_t) == 8);
	*dst = *src;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम
xfs_clear_li_failed(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_buf	*bp = lip->li_buf;

	ASSERT(test_bit(XFS_LI_IN_AIL, &lip->li_flags));
	lockdep_निश्चित_held(&lip->li_ailp->ail_lock);

	अगर (test_and_clear_bit(XFS_LI_FAILED, &lip->li_flags)) अणु
		lip->li_buf = शून्य;
		xfs_buf_rele(bp);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
xfs_set_li_failed(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_buf		*bp)
अणु
	lockdep_निश्चित_held(&lip->li_ailp->ail_lock);

	अगर (!test_and_set_bit(XFS_LI_FAILED, &lip->li_flags)) अणु
		xfs_buf_hold(bp);
		lip->li_buf = bp;
	पूर्ण
पूर्ण

#पूर्ण_अगर	/* __XFS_TRANS_PRIV_H__ */
