<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
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
#समावेश "xfs_buf_item.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_trace.h"

/*
 * Check to see अगर a buffer matching the given parameters is alपढ़ोy
 * a part of the given transaction.
 */
STATIC काष्ठा xfs_buf *
xfs_trans_buf_item_match(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buftarg	*target,
	काष्ठा xfs_buf_map	*map,
	पूर्णांक			nmaps)
अणु
	काष्ठा xfs_log_item	*lip;
	काष्ठा xfs_buf_log_item	*blip;
	पूर्णांक			len = 0;
	पूर्णांक			i;

	क्रम (i = 0; i < nmaps; i++)
		len += map[i].bm_len;

	list_क्रम_each_entry(lip, &tp->t_items, li_trans) अणु
		blip = (काष्ठा xfs_buf_log_item *)lip;
		अगर (blip->bli_item.li_type == XFS_LI_BUF &&
		    blip->bli_buf->b_target == target &&
		    XFS_BUF_ADDR(blip->bli_buf) == map[0].bm_bn &&
		    blip->bli_buf->b_length == len) अणु
			ASSERT(blip->bli_buf->b_map_count == nmaps);
			वापस blip->bli_buf;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Add the locked buffer to the transaction.
 *
 * The buffer must be locked, and it cannot be associated with any
 * transaction.
 *
 * If the buffer करोes not yet have a buf log item associated with it,
 * then allocate one क्रम it.  Then add the buf item to the transaction.
 */
STATIC व्योम
_xfs_trans_bjoin(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp,
	पूर्णांक			reset_recur)
अणु
	काष्ठा xfs_buf_log_item	*bip;

	ASSERT(bp->b_transp == शून्य);

	/*
	 * The xfs_buf_log_item poपूर्णांकer is stored in b_log_item.  If
	 * it करोesn't have one yet, then allocate one and initialize it.
	 * The checks to see अगर one is there are in xfs_buf_item_init().
	 */
	xfs_buf_item_init(bp, tp->t_mountp);
	bip = bp->b_log_item;
	ASSERT(!(bip->bli_flags & XFS_BLI_STALE));
	ASSERT(!(bip->__bli_क्रमmat.blf_flags & XFS_BLF_CANCEL));
	ASSERT(!(bip->bli_flags & XFS_BLI_LOGGED));
	अगर (reset_recur)
		bip->bli_recur = 0;

	/*
	 * Take a reference क्रम this transaction on the buf item.
	 */
	atomic_inc(&bip->bli_refcount);

	/*
	 * Attach the item to the transaction so we can find it in
	 * xfs_trans_get_buf() and मित्रs.
	 */
	xfs_trans_add_item(tp, &bip->bli_item);
	bp->b_transp = tp;

पूर्ण

व्योम
xfs_trans_bjoin(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp)
अणु
	_xfs_trans_bjoin(tp, bp, 0);
	trace_xfs_trans_bjoin(bp->b_log_item);
पूर्ण

/*
 * Get and lock the buffer क्रम the caller अगर it is not alपढ़ोy
 * locked within the given transaction.  If it is alपढ़ोy locked
 * within the transaction, just increment its lock recursion count
 * and वापस a poपूर्णांकer to it.
 *
 * If the transaction poपूर्णांकer is शून्य, make this just a normal
 * get_buf() call.
 */
पूर्णांक
xfs_trans_get_buf_map(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buftarg	*target,
	काष्ठा xfs_buf_map	*map,
	पूर्णांक			nmaps,
	xfs_buf_flags_t		flags,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_buf_log_item	*bip;
	पूर्णांक			error;

	*bpp = शून्य;
	अगर (!tp)
		वापस xfs_buf_get_map(target, map, nmaps, flags, bpp);

	/*
	 * If we find the buffer in the cache with this transaction
	 * poपूर्णांकer in its b_fsनिजी2 field, then we know we alपढ़ोy
	 * have it locked.  In this हाल we just increment the lock
	 * recursion count and वापस the buffer to the caller.
	 */
	bp = xfs_trans_buf_item_match(tp, target, map, nmaps);
	अगर (bp != शून्य) अणु
		ASSERT(xfs_buf_islocked(bp));
		अगर (XFS_FORCED_SHUTDOWN(tp->t_mountp)) अणु
			xfs_buf_stale(bp);
			bp->b_flags |= XBF_DONE;
		पूर्ण

		ASSERT(bp->b_transp == tp);
		bip = bp->b_log_item;
		ASSERT(bip != शून्य);
		ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);
		bip->bli_recur++;
		trace_xfs_trans_get_buf_recur(bip);
		*bpp = bp;
		वापस 0;
	पूर्ण

	error = xfs_buf_get_map(target, map, nmaps, flags, &bp);
	अगर (error)
		वापस error;

	ASSERT(!bp->b_error);

	_xfs_trans_bjoin(tp, bp, 1);
	trace_xfs_trans_get_buf(bp->b_log_item);
	*bpp = bp;
	वापस 0;
पूर्ण

/*
 * Get and lock the superblock buffer क्रम the given transaction.
 */
काष्ठा xfs_buf *
xfs_trans_माला_लोb(
	काष्ठा xfs_trans	*tp)
अणु
	काष्ठा xfs_buf		*bp = tp->t_mountp->m_sb_bp;

	/*
	 * Just increment the lock recursion count अगर the buffer is alपढ़ोy
	 * attached to this transaction.
	 */
	अगर (bp->b_transp == tp) अणु
		काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

		ASSERT(bip != शून्य);
		ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);
		bip->bli_recur++;

		trace_xfs_trans_माला_लोb_recur(bip);
	पूर्ण अन्यथा अणु
		xfs_buf_lock(bp);
		xfs_buf_hold(bp);
		_xfs_trans_bjoin(tp, bp, 1);

		trace_xfs_trans_माला_लोb(bp->b_log_item);
	पूर्ण

	वापस bp;
पूर्ण

/*
 * Get and lock the buffer क्रम the caller अगर it is not alपढ़ोy
 * locked within the given transaction.  If it has not yet been
 * पढ़ो in, पढ़ो it from disk. If it is alपढ़ोy locked
 * within the transaction and alपढ़ोy पढ़ो in, just increment its
 * lock recursion count and वापस a poपूर्णांकer to it.
 *
 * If the transaction poपूर्णांकer is शून्य, make this just a normal
 * पढ़ो_buf() call.
 */
पूर्णांक
xfs_trans_पढ़ो_buf_map(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buftarg	*target,
	काष्ठा xfs_buf_map	*map,
	पूर्णांक			nmaps,
	xfs_buf_flags_t		flags,
	काष्ठा xfs_buf		**bpp,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	काष्ठा xfs_buf		*bp = शून्य;
	काष्ठा xfs_buf_log_item	*bip;
	पूर्णांक			error;

	*bpp = शून्य;
	/*
	 * If we find the buffer in the cache with this transaction
	 * poपूर्णांकer in its b_fsनिजी2 field, then we know we alपढ़ोy
	 * have it locked.  If it is alपढ़ोy पढ़ो in we just increment
	 * the lock recursion count and वापस the buffer to the caller.
	 * If the buffer is not yet पढ़ो in, then we पढ़ो it in, increment
	 * the lock recursion count, and वापस it to the caller.
	 */
	अगर (tp)
		bp = xfs_trans_buf_item_match(tp, target, map, nmaps);
	अगर (bp) अणु
		ASSERT(xfs_buf_islocked(bp));
		ASSERT(bp->b_transp == tp);
		ASSERT(bp->b_log_item != शून्य);
		ASSERT(!bp->b_error);
		ASSERT(bp->b_flags & XBF_DONE);

		/*
		 * We never locked this buf ourselves, so we shouldn't
		 * brअन्यथा it either. Just get out.
		 */
		अगर (XFS_FORCED_SHUTDOWN(mp)) अणु
			trace_xfs_trans_पढ़ो_buf_shut(bp, _RET_IP_);
			वापस -EIO;
		पूर्ण

		/*
		 * Check अगर the caller is trying to पढ़ो a buffer that is
		 * alपढ़ोy attached to the transaction yet has no buffer ops
		 * asचिन्हित.  Ops are usually attached when the buffer is
		 * attached to the transaction, or by the पढ़ो caller अगर
		 * special circumstances.  That didn't happen, which is not
		 * how this is supposed to go.
		 *
		 * If the buffer passes verअगरication we'll let this go, but अगर
		 * not we have to shut करोwn.  Let the transaction cleanup code
		 * release this buffer when it समाप्तs the tranaction.
		 */
		ASSERT(bp->b_ops != शून्य);
		error = xfs_buf_reverअगरy(bp, ops);
		अगर (error) अणु
			xfs_buf_ioerror_alert(bp, __वापस_address);

			अगर (tp->t_flags & XFS_TRANS_सूचीTY)
				xfs_क्रमce_shutकरोwn(tp->t_mountp,
						SHUTDOWN_META_IO_ERROR);

			/* bad CRC means corrupted metadata */
			अगर (error == -EFSBADCRC)
				error = -EFSCORRUPTED;
			वापस error;
		पूर्ण

		bip = bp->b_log_item;
		bip->bli_recur++;

		ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);
		trace_xfs_trans_पढ़ो_buf_recur(bip);
		ASSERT(bp->b_ops != शून्य || ops == शून्य);
		*bpp = bp;
		वापस 0;
	पूर्ण

	error = xfs_buf_पढ़ो_map(target, map, nmaps, flags, &bp, ops,
			__वापस_address);
	चयन (error) अणु
	हाल 0:
		अवरोध;
	शेष:
		अगर (tp && (tp->t_flags & XFS_TRANS_सूचीTY))
			xfs_क्रमce_shutकरोwn(tp->t_mountp, SHUTDOWN_META_IO_ERROR);
		/* fall through */
	हाल -ENOMEM:
	हाल -EAGAIN:
		वापस error;
	पूर्ण

	अगर (XFS_FORCED_SHUTDOWN(mp)) अणु
		xfs_buf_rअन्यथा(bp);
		trace_xfs_trans_पढ़ो_buf_shut(bp, _RET_IP_);
		वापस -EIO;
	पूर्ण

	अगर (tp) अणु
		_xfs_trans_bjoin(tp, bp, 1);
		trace_xfs_trans_पढ़ो_buf(bp->b_log_item);
	पूर्ण
	ASSERT(bp->b_ops != शून्य || ops == शून्य);
	*bpp = bp;
	वापस 0;

पूर्ण

/* Has this buffer been dirtied by anyone? */
bool
xfs_trans_buf_is_dirty(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	अगर (!bip)
		वापस false;
	ASSERT(bip->bli_item.li_type == XFS_LI_BUF);
	वापस test_bit(XFS_LI_सूचीTY, &bip->bli_item.li_flags);
पूर्ण

/*
 * Release a buffer previously joined to the transaction. If the buffer is
 * modअगरied within this transaction, decrement the recursion count but करो not
 * release the buffer even अगर the count goes to 0. If the buffer is not modअगरied
 * within the transaction, decrement the recursion count and release the buffer
 * अगर the recursion count goes to 0.
 *
 * If the buffer is to be released and it was not alपढ़ोy dirty beक्रमe this
 * transaction began, then also मुक्त the buf_log_item associated with it.
 *
 * If the transaction poपूर्णांकer is शून्य, this is a normal xfs_buf_rअन्यथा() call.
 */
व्योम
xfs_trans_brअन्यथा(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);

	अगर (!tp) अणु
		xfs_buf_rअन्यथा(bp);
		वापस;
	पूर्ण

	trace_xfs_trans_brअन्यथा(bip);
	ASSERT(bip->bli_item.li_type == XFS_LI_BUF);
	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);

	/*
	 * If the release is क्रम a recursive lookup, then decrement the count
	 * and वापस.
	 */
	अगर (bip->bli_recur > 0) अणु
		bip->bli_recur--;
		वापस;
	पूर्ण

	/*
	 * If the buffer is invalidated or dirty in this transaction, we can't
	 * release it until we commit.
	 */
	अगर (test_bit(XFS_LI_सूचीTY, &bip->bli_item.li_flags))
		वापस;
	अगर (bip->bli_flags & XFS_BLI_STALE)
		वापस;

	/*
	 * Unlink the log item from the transaction and clear the hold flag, अगर
	 * set. We wouldn't want the next user of the buffer to get confused.
	 */
	ASSERT(!(bip->bli_flags & XFS_BLI_LOGGED));
	xfs_trans_del_item(&bip->bli_item);
	bip->bli_flags &= ~XFS_BLI_HOLD;

	/* drop the reference to the bli */
	xfs_buf_item_put(bip);

	bp->b_transp = शून्य;
	xfs_buf_rअन्यथा(bp);
पूर्ण

/*
 * Mark the buffer as not needing to be unlocked when the buf item's
 * iop_committing() routine is called.  The buffer must alपढ़ोy be locked
 * and associated with the given transaction.
 */
/* ARGSUSED */
व्योम
xfs_trans_bhold(
	xfs_trans_t		*tp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != शून्य);
	ASSERT(!(bip->bli_flags & XFS_BLI_STALE));
	ASSERT(!(bip->__bli_क्रमmat.blf_flags & XFS_BLF_CANCEL));
	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);

	bip->bli_flags |= XFS_BLI_HOLD;
	trace_xfs_trans_bhold(bip);
पूर्ण

/*
 * Cancel the previous buffer hold request made on this buffer
 * क्रम this transaction.
 */
व्योम
xfs_trans_bhold_release(
	xfs_trans_t		*tp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != शून्य);
	ASSERT(!(bip->bli_flags & XFS_BLI_STALE));
	ASSERT(!(bip->__bli_क्रमmat.blf_flags & XFS_BLF_CANCEL));
	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);
	ASSERT(bip->bli_flags & XFS_BLI_HOLD);

	bip->bli_flags &= ~XFS_BLI_HOLD;
	trace_xfs_trans_bhold_release(bip);
पूर्ण

/*
 * Mark a buffer dirty in the transaction.
 */
व्योम
xfs_trans_dirty_buf(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != शून्य);

	/*
	 * Mark the buffer as needing to be written out eventually,
	 * and set its ioकरोne function to हटाओ the buffer's buf log
	 * item from the AIL and मुक्त it when the buffer is flushed
	 * to disk.
	 */
	bp->b_flags |= XBF_DONE;

	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);

	/*
	 * If we invalidated the buffer within this transaction, then
	 * cancel the invalidation now that we're dirtying the buffer
	 * again.  There are no races with the code in xfs_buf_item_unpin(),
	 * because we have a reference to the buffer this entire समय.
	 */
	अगर (bip->bli_flags & XFS_BLI_STALE) अणु
		bip->bli_flags &= ~XFS_BLI_STALE;
		ASSERT(bp->b_flags & XBF_STALE);
		bp->b_flags &= ~XBF_STALE;
		bip->__bli_क्रमmat.blf_flags &= ~XFS_BLF_CANCEL;
	पूर्ण
	bip->bli_flags |= XFS_BLI_सूचीTY | XFS_BLI_LOGGED;

	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &bip->bli_item.li_flags);
पूर्ण

/*
 * This is called to mark bytes first through last inclusive of the given
 * buffer as needing to be logged when the transaction is committed.
 * The buffer must alपढ़ोy be associated with the given transaction.
 *
 * First and last are numbers relative to the beginning of this buffer,
 * so the first byte in the buffer is numbered 0 regardless of the
 * value of b_blkno.
 */
व्योम
xfs_trans_log_buf(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp,
	uपूर्णांक			first,
	uपूर्णांक			last)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(first <= last && last < BBTOB(bp->b_length));
	ASSERT(!(bip->bli_flags & XFS_BLI_ORDERED));

	xfs_trans_dirty_buf(tp, bp);

	trace_xfs_trans_log_buf(bip);
	xfs_buf_item_log(bip, first, last);
पूर्ण


/*
 * Invalidate a buffer that is being used within a transaction.
 *
 * Typically this is because the blocks in the buffer are being मुक्तd, so we
 * need to prevent it from being written out when we're करोne.  Allowing it
 * to be written again might overग_लिखो data in the मुक्त blocks अगर they are
 * पुनः_स्मृतिated to a file.
 *
 * We prevent the buffer from being written out by marking it stale.  We can't
 * get rid of the buf log item at this poपूर्णांक because the buffer may still be
 * pinned by another transaction.  If that is the हाल, then we'll रुको until
 * the buffer is committed to disk क्रम the last समय (we can tell by the ref
 * count) and मुक्त it in xfs_buf_item_unpin().  Until that happens we will
 * keep the buffer locked so that the buffer and buf log item are not reused.
 *
 * We also set the XFS_BLF_CANCEL flag in the buf log क्रमmat काष्ठाure and log
 * the buf item.  This will be used at recovery समय to determine that copies
 * of the buffer in the log beक्रमe this should not be replayed.
 *
 * We mark the item descriptor and the transaction dirty so that we'll hold
 * the buffer until after the commit.
 *
 * Since we're invalidating the buffer, we also clear the state about which
 * parts of the buffer have been logged.  We also clear the flag indicating
 * that this is an inode buffer since the data in the buffer will no दीर्घer
 * be valid.
 *
 * We set the stale bit in the buffer as well since we're getting rid of it.
 */
व्योम
xfs_trans_binval(
	xfs_trans_t		*tp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	पूर्णांक			i;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != शून्य);
	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);

	trace_xfs_trans_binval(bip);

	अगर (bip->bli_flags & XFS_BLI_STALE) अणु
		/*
		 * If the buffer is alपढ़ोy invalidated, then
		 * just वापस.
		 */
		ASSERT(bp->b_flags & XBF_STALE);
		ASSERT(!(bip->bli_flags & (XFS_BLI_LOGGED | XFS_BLI_सूचीTY)));
		ASSERT(!(bip->__bli_क्रमmat.blf_flags & XFS_BLF_INODE_BUF));
		ASSERT(!(bip->__bli_क्रमmat.blf_flags & XFS_BLFT_MASK));
		ASSERT(bip->__bli_क्रमmat.blf_flags & XFS_BLF_CANCEL);
		ASSERT(test_bit(XFS_LI_सूचीTY, &bip->bli_item.li_flags));
		ASSERT(tp->t_flags & XFS_TRANS_सूचीTY);
		वापस;
	पूर्ण

	xfs_buf_stale(bp);

	bip->bli_flags |= XFS_BLI_STALE;
	bip->bli_flags &= ~(XFS_BLI_INODE_BUF | XFS_BLI_LOGGED | XFS_BLI_सूचीTY);
	bip->__bli_क्रमmat.blf_flags &= ~XFS_BLF_INODE_BUF;
	bip->__bli_क्रमmat.blf_flags |= XFS_BLF_CANCEL;
	bip->__bli_क्रमmat.blf_flags &= ~XFS_BLFT_MASK;
	क्रम (i = 0; i < bip->bli_क्रमmat_count; i++) अणु
		स_रखो(bip->bli_क्रमmats[i].blf_data_map, 0,
		       (bip->bli_क्रमmats[i].blf_map_size * माप(uपूर्णांक)));
	पूर्ण
	set_bit(XFS_LI_सूचीTY, &bip->bli_item.li_flags);
	tp->t_flags |= XFS_TRANS_सूचीTY;
पूर्ण

/*
 * This call is used to indicate that the buffer contains on-disk inodes which
 * must be handled specially during recovery.  They require special handling
 * because only the di_next_unlinked from the inodes in the buffer should be
 * recovered.  The rest of the data in the buffer is logged via the inodes
 * themselves.
 *
 * All we करो is set the XFS_BLI_INODE_BUF flag in the items flags so it can be
 * transferred to the buffer's log format structure so that we'll know what to
 * करो at recovery समय.
 */
व्योम
xfs_trans_inode_buf(
	xfs_trans_t		*tp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != शून्य);
	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);

	bip->bli_flags |= XFS_BLI_INODE_BUF;
	bp->b_flags |= _XBF_INODES;
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DINO_BUF);
पूर्ण

/*
 * This call is used to indicate that the buffer is going to
 * be staled and was an inode buffer. This means it माला_लो
 * special processing during unpin - where any inodes
 * associated with the buffer should be हटाओd from ail.
 * There is also special processing during recovery,
 * any replay of the inodes in the buffer needs to be
 * prevented as the buffer may have been reused.
 */
व्योम
xfs_trans_stale_inode_buf(
	xfs_trans_t		*tp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != शून्य);
	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);

	bip->bli_flags |= XFS_BLI_STALE_INODE;
	bp->b_flags |= _XBF_INODES;
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DINO_BUF);
पूर्ण

/*
 * Mark the buffer as being one which contains newly allocated
 * inodes.  We need to make sure that even अगर this buffer is
 * relogged as an 'inode buf' we still recover all of the inode
 * images in the face of a crash.  This works in coordination with
 * xfs_buf_item_committed() to ensure that the buffer reमुख्यs in the
 * AIL at its original location even after it has been relogged.
 */
/* ARGSUSED */
व्योम
xfs_trans_inode_alloc_buf(
	xfs_trans_t		*tp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != शून्य);
	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);

	bip->bli_flags |= XFS_BLI_INODE_ALLOC_BUF;
	bp->b_flags |= _XBF_INODES;
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DINO_BUF);
पूर्ण

/*
 * Mark the buffer as ordered क्रम this transaction. This means that the contents
 * of the buffer are not recorded in the transaction but it is tracked in the
 * AIL as though it was. This allows us to record logical changes in
 * transactions rather than the physical changes we make to the buffer without
 * changing ग_लिखोback ordering स्थिरraपूर्णांकs of metadata buffers.
 */
bool
xfs_trans_ordered_buf(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != शून्य);
	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);

	अगर (xfs_buf_item_dirty_क्रमmat(bip))
		वापस false;

	bip->bli_flags |= XFS_BLI_ORDERED;
	trace_xfs_buf_item_ordered(bip);

	/*
	 * We करोn't log a dirty range of an ordered buffer but it still needs
	 * to be marked dirty and that it has been logged.
	 */
	xfs_trans_dirty_buf(tp, bp);
	वापस true;
पूर्ण

/*
 * Set the type of the buffer क्रम log recovery so that it can correctly identअगरy
 * and hence attach the correct buffer ops to the buffer after replay.
 */
व्योम
xfs_trans_buf_set_type(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp,
	क्रमागत xfs_blft		type)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	अगर (!tp)
		वापस;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != शून्य);
	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);

	xfs_blft_to_flags(&bip->__bli_क्रमmat, type);
पूर्ण

व्योम
xfs_trans_buf_copy_type(
	काष्ठा xfs_buf		*dst_bp,
	काष्ठा xfs_buf		*src_bp)
अणु
	काष्ठा xfs_buf_log_item	*sbip = src_bp->b_log_item;
	काष्ठा xfs_buf_log_item	*dbip = dst_bp->b_log_item;
	क्रमागत xfs_blft		type;

	type = xfs_blft_from_flags(&sbip->__bli_क्रमmat);
	xfs_blft_to_flags(&dbip->__bli_क्रमmat, type);
पूर्ण

/*
 * Similar to xfs_trans_inode_buf(), this marks the buffer as a cluster of
 * dquots. However, unlike in inode buffer recovery, dquot buffers get
 * recovered in their entirety. (Hence, no XFS_BLI_DQUOT_ALLOC_BUF flag).
 * The only thing that makes dquot buffers dअगरferent from regular
 * buffers is that we must not replay dquot bufs when recovering
 * अगर a _corresponding_ quotaoff has happened. We also have to distinguish
 * between usr dquot bufs and grp dquot bufs, because usr and grp quotas
 * can be turned off independently.
 */
/* ARGSUSED */
व्योम
xfs_trans_dquot_buf(
	xfs_trans_t		*tp,
	काष्ठा xfs_buf		*bp,
	uपूर्णांक			type)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(type == XFS_BLF_UDQUOT_BUF ||
	       type == XFS_BLF_PDQUOT_BUF ||
	       type == XFS_BLF_GDQUOT_BUF);

	bip->__bli_क्रमmat.blf_flags |= type;

	चयन (type) अणु
	हाल XFS_BLF_UDQUOT_BUF:
		type = XFS_BLFT_UDQUOT_BUF;
		अवरोध;
	हाल XFS_BLF_PDQUOT_BUF:
		type = XFS_BLFT_PDQUOT_BUF;
		अवरोध;
	हाल XFS_BLF_GDQUOT_BUF:
		type = XFS_BLFT_GDQUOT_BUF;
		अवरोध;
	शेष:
		type = XFS_BLFT_UNKNOWN_BUF;
		अवरोध;
	पूर्ण

	bp->b_flags |= _XBF_DQUOTS;
	xfs_trans_buf_set_type(tp, bp, type);
पूर्ण
