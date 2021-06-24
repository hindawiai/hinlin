<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003 Silicon Graphics, Inc.
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
#समावेश "xfs_quota.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_qm.h"
#समावेश "xfs_log.h"

अटल अंतरभूत काष्ठा xfs_dq_logitem *DQUOT_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_dq_logitem, qli_item);
पूर्ण

/*
 * वापसs the number of iovecs needed to log the given dquot item.
 */
STATIC व्योम
xfs_qm_dquot_logitem_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	*nvecs += 2;
	*nbytes += माप(काष्ठा xfs_dq_logक्रमmat) +
		   माप(काष्ठा xfs_disk_dquot);
पूर्ण

/*
 * fills in the vector of log iovecs क्रम the given dquot log item.
 */
STATIC व्योम
xfs_qm_dquot_logitem_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_disk_dquot	ddq;
	काष्ठा xfs_dq_logitem	*qlip = DQUOT_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;
	काष्ठा xfs_dq_logक्रमmat	*qlf;

	qlf = xlog_prepare_iovec(lv, &vecp, XLOG_REG_TYPE_QFORMAT);
	qlf->qlf_type = XFS_LI_DQUOT;
	qlf->qlf_size = 2;
	qlf->qlf_id = qlip->qli_dquot->q_id;
	qlf->qlf_blkno = qlip->qli_dquot->q_blkno;
	qlf->qlf_len = 1;
	qlf->qlf_boffset = qlip->qli_dquot->q_bufoffset;
	xlog_finish_iovec(lv, vecp, माप(काष्ठा xfs_dq_logक्रमmat));

	xfs_dquot_to_disk(&ddq, qlip->qli_dquot);

	xlog_copy_iovec(lv, &vecp, XLOG_REG_TYPE_DQUOT, &ddq,
			माप(काष्ठा xfs_disk_dquot));
पूर्ण

/*
 * Increment the pin count of the given dquot.
 */
STATIC व्योम
xfs_qm_dquot_logitem_pin(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_dquot	*dqp = DQUOT_ITEM(lip)->qli_dquot;

	ASSERT(XFS_DQ_IS_LOCKED(dqp));
	atomic_inc(&dqp->q_pincount);
पूर्ण

/*
 * Decrement the pin count of the given dquot, and wake up
 * anyone in xfs_dqरुको_unpin() अगर the count goes to 0.	 The
 * dquot must have been previously pinned with a call to
 * xfs_qm_dquot_logitem_pin().
 */
STATIC व्योम
xfs_qm_dquot_logitem_unpin(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			हटाओ)
अणु
	काष्ठा xfs_dquot	*dqp = DQUOT_ITEM(lip)->qli_dquot;

	ASSERT(atomic_पढ़ो(&dqp->q_pincount) > 0);
	अगर (atomic_dec_and_test(&dqp->q_pincount))
		wake_up(&dqp->q_pinरुको);
पूर्ण

/*
 * This is called to रुको क्रम the given dquot to be unpinned.
 * Most of these pin/unpin routines are plagiarized from inode code.
 */
व्योम
xfs_qm_dqunpin_रुको(
	काष्ठा xfs_dquot	*dqp)
अणु
	ASSERT(XFS_DQ_IS_LOCKED(dqp));
	अगर (atomic_पढ़ो(&dqp->q_pincount) == 0)
		वापस;

	/*
	 * Give the log a push so we करोn't रुको here too दीर्घ.
	 */
	xfs_log_क्रमce(dqp->q_mount, 0);
	रुको_event(dqp->q_pinरुको, (atomic_पढ़ो(&dqp->q_pincount) == 0));
पूर्ण

STATIC uपूर्णांक
xfs_qm_dquot_logitem_push(
	काष्ठा xfs_log_item	*lip,
	काष्ठा list_head	*buffer_list)
		__releases(&lip->li_ailp->ail_lock)
		__acquires(&lip->li_ailp->ail_lock)
अणु
	काष्ठा xfs_dquot	*dqp = DQUOT_ITEM(lip)->qli_dquot;
	काष्ठा xfs_buf		*bp = lip->li_buf;
	uपूर्णांक			rval = XFS_ITEM_SUCCESS;
	पूर्णांक			error;

	अगर (atomic_पढ़ो(&dqp->q_pincount) > 0)
		वापस XFS_ITEM_PINNED;

	अगर (!xfs_dqlock_noरुको(dqp))
		वापस XFS_ITEM_LOCKED;

	/*
	 * Re-check the pincount now that we stabilized the value by
	 * taking the quota lock.
	 */
	अगर (atomic_पढ़ो(&dqp->q_pincount) > 0) अणु
		rval = XFS_ITEM_PINNED;
		जाओ out_unlock;
	पूर्ण

	/*
	 * Someone अन्यथा is alपढ़ोy flushing the dquot.  Nothing we can करो
	 * here but रुको क्रम the flush to finish and हटाओ the item from
	 * the AIL.
	 */
	अगर (!xfs_dqflock_noरुको(dqp)) अणु
		rval = XFS_ITEM_FLUSHING;
		जाओ out_unlock;
	पूर्ण

	spin_unlock(&lip->li_ailp->ail_lock);

	error = xfs_qm_dqflush(dqp, &bp);
	अगर (!error) अणु
		अगर (!xfs_buf_delwri_queue(bp, buffer_list))
			rval = XFS_ITEM_FLUSHING;
		xfs_buf_rअन्यथा(bp);
	पूर्ण अन्यथा अगर (error == -EAGAIN)
		rval = XFS_ITEM_LOCKED;

	spin_lock(&lip->li_ailp->ail_lock);
out_unlock:
	xfs_dqunlock(dqp);
	वापस rval;
पूर्ण

STATIC व्योम
xfs_qm_dquot_logitem_release(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_dquot	*dqp = DQUOT_ITEM(lip)->qli_dquot;

	ASSERT(XFS_DQ_IS_LOCKED(dqp));

	/*
	 * dquots are never 'held' from getting unlocked at the end of
	 * a transaction.  Their locking and unlocking is hidden inside the
	 * transaction layer, within trans_commit. Hence, no LI_HOLD flag
	 * क्रम the logitem.
	 */
	xfs_dqunlock(dqp);
पूर्ण

STATIC व्योम
xfs_qm_dquot_logitem_committing(
	काष्ठा xfs_log_item	*lip,
	xfs_lsn_t		commit_lsn)
अणु
	वापस xfs_qm_dquot_logitem_release(lip);
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_dquot_item_ops = अणु
	.iop_size	= xfs_qm_dquot_logitem_size,
	.iop_क्रमmat	= xfs_qm_dquot_logitem_क्रमmat,
	.iop_pin	= xfs_qm_dquot_logitem_pin,
	.iop_unpin	= xfs_qm_dquot_logitem_unpin,
	.iop_release	= xfs_qm_dquot_logitem_release,
	.iop_committing	= xfs_qm_dquot_logitem_committing,
	.iop_push	= xfs_qm_dquot_logitem_push,
पूर्ण;

/*
 * Initialize the dquot log item क्रम a newly allocated dquot.
 * The dquot isn't locked at this point, but it isn't on any of the lists
 * either, so we करोn't care.
 */
व्योम
xfs_qm_dquot_logitem_init(
	काष्ठा xfs_dquot	*dqp)
अणु
	काष्ठा xfs_dq_logitem	*lp = &dqp->q_logitem;

	xfs_log_item_init(dqp->q_mount, &lp->qli_item, XFS_LI_DQUOT,
					&xfs_dquot_item_ops);
	lp->qli_dquot = dqp;
पूर्ण

/*------------------  QUOTAOFF LOG ITEMS  -------------------*/

अटल अंतरभूत काष्ठा xfs_qoff_logitem *QOFF_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_qoff_logitem, qql_item);
पूर्ण


/*
 * This वापसs the number of iovecs needed to log the given quotaoff item.
 * We only need 1 iovec क्रम an quotaoff item.  It just logs the
 * quotaoff_log_क्रमmat काष्ठाure.
 */
STATIC व्योम
xfs_qm_qoff_logitem_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	*nvecs += 1;
	*nbytes += माप(काष्ठा xfs_qoff_logitem);
पूर्ण

STATIC व्योम
xfs_qm_qoff_logitem_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_qoff_logitem	*qflip = QOFF_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;
	काष्ठा xfs_qoff_logक्रमmat *qlf;

	qlf = xlog_prepare_iovec(lv, &vecp, XLOG_REG_TYPE_QUOTAOFF);
	qlf->qf_type = XFS_LI_QUOTAOFF;
	qlf->qf_size = 1;
	qlf->qf_flags = qflip->qql_flags;
	xlog_finish_iovec(lv, vecp, माप(काष्ठा xfs_qoff_logitem));
पूर्ण

/*
 * There isn't much you can करो to push a quotaoff item.  It is simply
 * stuck रुकोing क्रम the log to be flushed to disk.
 */
STATIC uपूर्णांक
xfs_qm_qoff_logitem_push(
	काष्ठा xfs_log_item	*lip,
	काष्ठा list_head	*buffer_list)
अणु
	वापस XFS_ITEM_LOCKED;
पूर्ण

STATIC xfs_lsn_t
xfs_qm_qoffend_logitem_committed(
	काष्ठा xfs_log_item	*lip,
	xfs_lsn_t		lsn)
अणु
	काष्ठा xfs_qoff_logitem	*qfe = QOFF_ITEM(lip);
	काष्ठा xfs_qoff_logitem	*qfs = qfe->qql_start_lip;

	xfs_qm_qoff_logitem_rअन्यथा(qfs);

	kmem_मुक्त(lip->li_lv_shaकरोw);
	kmem_मुक्त(qfe);
	वापस (xfs_lsn_t)-1;
पूर्ण

STATIC व्योम
xfs_qm_qoff_logitem_release(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_qoff_logitem	*qoff = QOFF_ITEM(lip);

	अगर (test_bit(XFS_LI_ABORTED, &lip->li_flags)) अणु
		अगर (qoff->qql_start_lip)
			xfs_qm_qoff_logitem_rअन्यथा(qoff->qql_start_lip);
		xfs_qm_qoff_logitem_rअन्यथा(qoff);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_qm_qoffend_logitem_ops = अणु
	.iop_size	= xfs_qm_qoff_logitem_size,
	.iop_क्रमmat	= xfs_qm_qoff_logitem_क्रमmat,
	.iop_committed	= xfs_qm_qoffend_logitem_committed,
	.iop_push	= xfs_qm_qoff_logitem_push,
	.iop_release	= xfs_qm_qoff_logitem_release,
पूर्ण;

अटल स्थिर काष्ठा xfs_item_ops xfs_qm_qoff_logitem_ops = अणु
	.iop_size	= xfs_qm_qoff_logitem_size,
	.iop_क्रमmat	= xfs_qm_qoff_logitem_क्रमmat,
	.iop_push	= xfs_qm_qoff_logitem_push,
	.iop_release	= xfs_qm_qoff_logitem_release,
पूर्ण;

/*
 * Delete the quotaoff पूर्णांकent from the AIL and मुक्त it. On success,
 * this should only be called क्रम the start item. It can be used क्रम
 * either on shutकरोwn or पात.
 */
व्योम
xfs_qm_qoff_logitem_rअन्यथा(
	काष्ठा xfs_qoff_logitem	*qoff)
अणु
	काष्ठा xfs_log_item	*lip = &qoff->qql_item;

	ASSERT(test_bit(XFS_LI_IN_AIL, &lip->li_flags) ||
	       test_bit(XFS_LI_ABORTED, &lip->li_flags) ||
	       XFS_FORCED_SHUTDOWN(lip->li_mountp));
	xfs_trans_ail_delete(lip, 0);
	kmem_मुक्त(lip->li_lv_shaकरोw);
	kmem_मुक्त(qoff);
पूर्ण

/*
 * Allocate and initialize an quotaoff item of the correct quota type(s).
 */
काष्ठा xfs_qoff_logitem *
xfs_qm_qoff_logitem_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_qoff_logitem	*start,
	uपूर्णांक			flags)
अणु
	काष्ठा xfs_qoff_logitem	*qf;

	qf = kmem_zalloc(माप(काष्ठा xfs_qoff_logitem), 0);

	xfs_log_item_init(mp, &qf->qql_item, XFS_LI_QUOTAOFF, start ?
			&xfs_qm_qoffend_logitem_ops : &xfs_qm_qoff_logitem_ops);
	qf->qql_item.li_mountp = mp;
	qf->qql_start_lip = start;
	qf->qql_flags = flags;
	वापस qf;
पूर्ण
