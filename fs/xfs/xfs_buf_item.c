<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
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
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_inode_item.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_dquot_item.h"
#समावेश "xfs_dquot.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_log.h"


kmem_zone_t	*xfs_buf_item_zone;

अटल अंतरभूत काष्ठा xfs_buf_log_item *BUF_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_buf_log_item, bli_item);
पूर्ण

/* Is this log iovec plausibly large enough to contain the buffer log क्रमmat? */
bool
xfs_buf_log_check_iovec(
	काष्ठा xfs_log_iovec		*iovec)
अणु
	काष्ठा xfs_buf_log_क्रमmat	*blfp = iovec->i_addr;
	अक्षर				*bmp_end;
	अक्षर				*item_end;

	अगर (दुरत्व(काष्ठा xfs_buf_log_क्रमmat, blf_data_map) > iovec->i_len)
		वापस false;

	item_end = (अक्षर *)iovec->i_addr + iovec->i_len;
	bmp_end = (अक्षर *)&blfp->blf_data_map[blfp->blf_map_size];
	वापस bmp_end <= item_end;
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_buf_log_क्रमmat_size(
	काष्ठा xfs_buf_log_क्रमmat *blfp)
अणु
	वापस दुरत्व(काष्ठा xfs_buf_log_क्रमmat, blf_data_map) +
			(blfp->blf_map_size * माप(blfp->blf_data_map[0]));
पूर्ण

अटल अंतरभूत bool
xfs_buf_item_straddle(
	काष्ठा xfs_buf		*bp,
	uपूर्णांक			offset,
	पूर्णांक			first_bit,
	पूर्णांक			nbits)
अणु
	व्योम			*first, *last;

	first = xfs_buf_offset(bp, offset + (first_bit << XFS_BLF_SHIFT));
	last = xfs_buf_offset(bp,
			offset + ((first_bit + nbits) << XFS_BLF_SHIFT));

	अगर (last - first != nbits * XFS_BLF_CHUNK)
		वापस true;
	वापस false;
पूर्ण

/*
 * This वापसs the number of log iovecs needed to log the
 * given buf log item.
 *
 * It calculates this as 1 iovec क्रम the buf log क्रमmat काष्ठाure
 * and 1 क्रम each stretch of non-contiguous chunks to be logged.
 * Contiguous chunks are logged in a single iovec.
 *
 * If the XFS_BLI_STALE flag has been set, then log nothing.
 */
STATIC व्योम
xfs_buf_item_size_segment(
	काष्ठा xfs_buf_log_item		*bip,
	काष्ठा xfs_buf_log_क्रमmat	*blfp,
	uपूर्णांक				offset,
	पूर्णांक				*nvecs,
	पूर्णांक				*nbytes)
अणु
	काष्ठा xfs_buf			*bp = bip->bli_buf;
	पूर्णांक				first_bit;
	पूर्णांक				nbits;
	पूर्णांक				next_bit;
	पूर्णांक				last_bit;

	first_bit = xfs_next_bit(blfp->blf_data_map, blfp->blf_map_size, 0);
	अगर (first_bit == -1)
		वापस;

	(*nvecs)++;
	*nbytes += xfs_buf_log_क्रमmat_size(blfp);

	करो अणु
		nbits = xfs_contig_bits(blfp->blf_data_map,
					blfp->blf_map_size, first_bit);
		ASSERT(nbits > 0);

		/*
		 * Straddling a page is rare because we करोn't log contiguous
		 * chunks of unmapped buffers anywhere.
		 */
		अगर (nbits > 1 &&
		    xfs_buf_item_straddle(bp, offset, first_bit, nbits))
			जाओ slow_scan;

		(*nvecs)++;
		*nbytes += nbits * XFS_BLF_CHUNK;

		/*
		 * This takes the bit number to start looking from and
		 * वापसs the next set bit from there.  It वापसs -1
		 * अगर there are no more bits set or the start bit is
		 * beyond the end of the biपंचांगap.
		 */
		first_bit = xfs_next_bit(blfp->blf_data_map, blfp->blf_map_size,
					(uपूर्णांक)first_bit + nbits + 1);
	पूर्ण जबतक (first_bit != -1);

	वापस;

slow_scan:
	/* Count the first bit we jumped out of the above loop from */
	(*nvecs)++;
	*nbytes += XFS_BLF_CHUNK;
	last_bit = first_bit;
	जबतक (last_bit != -1) अणु
		/*
		 * This takes the bit number to start looking from and
		 * वापसs the next set bit from there.  It वापसs -1
		 * अगर there are no more bits set or the start bit is
		 * beyond the end of the biपंचांगap.
		 */
		next_bit = xfs_next_bit(blfp->blf_data_map, blfp->blf_map_size,
					last_bit + 1);
		/*
		 * If we run out of bits, leave the loop,
		 * अन्यथा अगर we find a new set of bits bump the number of vecs,
		 * अन्यथा keep scanning the current set of bits.
		 */
		अगर (next_bit == -1) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (next_bit != last_bit + 1 ||
		           xfs_buf_item_straddle(bp, offset, first_bit, nbits)) अणु
			last_bit = next_bit;
			first_bit = next_bit;
			(*nvecs)++;
			nbits = 1;
		पूर्ण अन्यथा अणु
			last_bit++;
			nbits++;
		पूर्ण
		*nbytes += XFS_BLF_CHUNK;
	पूर्ण
पूर्ण

/*
 * This वापसs the number of log iovecs needed to log the given buf log item.
 *
 * It calculates this as 1 iovec क्रम the buf log क्रमmat काष्ठाure and 1 क्रम each
 * stretch of non-contiguous chunks to be logged.  Contiguous chunks are logged
 * in a single iovec.
 *
 * Discontiguous buffers need a क्रमmat काष्ठाure per region that is being
 * logged. This makes the changes in the buffer appear to log recovery as though
 * they came from separate buffers, just like would occur अगर multiple buffers
 * were used instead of a single discontiguous buffer. This enables
 * discontiguous buffers to be in-memory स्थिरructs, completely transparent to
 * what ends up on disk.
 *
 * If the XFS_BLI_STALE flag has been set, then log nothing but the buf log
 * क्रमmat काष्ठाures.
 */
STATIC व्योम
xfs_buf_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	काष्ठा xfs_buf_log_item	*bip = BUF_ITEM(lip);
	काष्ठा xfs_buf		*bp = bip->bli_buf;
	पूर्णांक			i;
	पूर्णांक			bytes;
	uपूर्णांक			offset = 0;

	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);
	अगर (bip->bli_flags & XFS_BLI_STALE) अणु
		/*
		 * The buffer is stale, so all we need to log
		 * is the buf log क्रमmat काष्ठाure with the
		 * cancel flag in it.
		 */
		trace_xfs_buf_item_size_stale(bip);
		ASSERT(bip->__bli_क्रमmat.blf_flags & XFS_BLF_CANCEL);
		*nvecs += bip->bli_क्रमmat_count;
		क्रम (i = 0; i < bip->bli_क्रमmat_count; i++) अणु
			*nbytes += xfs_buf_log_क्रमmat_size(&bip->bli_क्रमmats[i]);
		पूर्ण
		वापस;
	पूर्ण

	ASSERT(bip->bli_flags & XFS_BLI_LOGGED);

	अगर (bip->bli_flags & XFS_BLI_ORDERED) अणु
		/*
		 * The buffer has been logged just to order it.
		 * It is not being included in the transaction
		 * commit, so no vectors are used at all.
		 */
		trace_xfs_buf_item_size_ordered(bip);
		*nvecs = XFS_LOG_VEC_ORDERED;
		वापस;
	पूर्ण

	/*
	 * The vector count is based on the number of buffer vectors we have
	 * dirty bits in. This will only be greater than one when we have a
	 * compound buffer with more than one segment dirty. Hence क्रम compound
	 * buffers we need to track which segment the dirty bits correspond to,
	 * and when we move from one segment to the next increment the vector
	 * count क्रम the extra buf log क्रमmat काष्ठाure that will need to be
	 * written.
	 */
	bytes = 0;
	क्रम (i = 0; i < bip->bli_क्रमmat_count; i++) अणु
		xfs_buf_item_size_segment(bip, &bip->bli_क्रमmats[i], offset,
					  nvecs, &bytes);
		offset += BBTOB(bp->b_maps[i].bm_len);
	पूर्ण

	/*
	 * Round up the buffer size required to minimise the number of memory
	 * allocations that need to be करोne as this item grows when relogged by
	 * repeated modअगरications.
	 */
	*nbytes = round_up(bytes, 512);
	trace_xfs_buf_item_size(bip);
पूर्ण

अटल अंतरभूत व्योम
xfs_buf_item_copy_iovec(
	काष्ठा xfs_log_vec	*lv,
	काष्ठा xfs_log_iovec	**vecp,
	काष्ठा xfs_buf		*bp,
	uपूर्णांक			offset,
	पूर्णांक			first_bit,
	uपूर्णांक			nbits)
अणु
	offset += first_bit * XFS_BLF_CHUNK;
	xlog_copy_iovec(lv, vecp, XLOG_REG_TYPE_BCHUNK,
			xfs_buf_offset(bp, offset),
			nbits * XFS_BLF_CHUNK);
पूर्ण

अटल व्योम
xfs_buf_item_क्रमmat_segment(
	काष्ठा xfs_buf_log_item	*bip,
	काष्ठा xfs_log_vec	*lv,
	काष्ठा xfs_log_iovec	**vecp,
	uपूर्णांक			offset,
	काष्ठा xfs_buf_log_क्रमmat *blfp)
अणु
	काष्ठा xfs_buf		*bp = bip->bli_buf;
	uपूर्णांक			base_size;
	पूर्णांक			first_bit;
	पूर्णांक			last_bit;
	पूर्णांक			next_bit;
	uपूर्णांक			nbits;

	/* copy the flags across from the base क्रमmat item */
	blfp->blf_flags = bip->__bli_क्रमmat.blf_flags;

	/*
	 * Base size is the actual size of the ondisk काष्ठाure - it reflects
	 * the actual size of the dirty biपंचांगap rather than the size of the in
	 * memory काष्ठाure.
	 */
	base_size = xfs_buf_log_क्रमmat_size(blfp);

	first_bit = xfs_next_bit(blfp->blf_data_map, blfp->blf_map_size, 0);
	अगर (!(bip->bli_flags & XFS_BLI_STALE) && first_bit == -1) अणु
		/*
		 * If the map is not be dirty in the transaction, mark
		 * the size as zero and करो not advance the vector poपूर्णांकer.
		 */
		वापस;
	पूर्ण

	blfp = xlog_copy_iovec(lv, vecp, XLOG_REG_TYPE_BFORMAT, blfp, base_size);
	blfp->blf_size = 1;

	अगर (bip->bli_flags & XFS_BLI_STALE) अणु
		/*
		 * The buffer is stale, so all we need to log
		 * is the buf log क्रमmat काष्ठाure with the
		 * cancel flag in it.
		 */
		trace_xfs_buf_item_क्रमmat_stale(bip);
		ASSERT(blfp->blf_flags & XFS_BLF_CANCEL);
		वापस;
	पूर्ण


	/*
	 * Fill in an iovec क्रम each set of contiguous chunks.
	 */
	करो अणु
		ASSERT(first_bit >= 0);
		nbits = xfs_contig_bits(blfp->blf_data_map,
					blfp->blf_map_size, first_bit);
		ASSERT(nbits > 0);

		/*
		 * Straddling a page is rare because we करोn't log contiguous
		 * chunks of unmapped buffers anywhere.
		 */
		अगर (nbits > 1 &&
		    xfs_buf_item_straddle(bp, offset, first_bit, nbits))
			जाओ slow_scan;

		xfs_buf_item_copy_iovec(lv, vecp, bp, offset,
					first_bit, nbits);
		blfp->blf_size++;

		/*
		 * This takes the bit number to start looking from and
		 * वापसs the next set bit from there.  It वापसs -1
		 * अगर there are no more bits set or the start bit is
		 * beyond the end of the biपंचांगap.
		 */
		first_bit = xfs_next_bit(blfp->blf_data_map, blfp->blf_map_size,
					(uपूर्णांक)first_bit + nbits + 1);
	पूर्ण जबतक (first_bit != -1);

	वापस;

slow_scan:
	ASSERT(bp->b_addr == शून्य);
	last_bit = first_bit;
	nbits = 1;
	क्रम (;;) अणु
		/*
		 * This takes the bit number to start looking from and
		 * वापसs the next set bit from there.  It वापसs -1
		 * अगर there are no more bits set or the start bit is
		 * beyond the end of the biपंचांगap.
		 */
		next_bit = xfs_next_bit(blfp->blf_data_map, blfp->blf_map_size,
					(uपूर्णांक)last_bit + 1);
		/*
		 * If we run out of bits fill in the last iovec and get out of
		 * the loop.  Else अगर we start a new set of bits then fill in
		 * the iovec क्रम the series we were looking at and start
		 * counting the bits in the new one.  Else we're still in the
		 * same set of bits so just keep counting and scanning.
		 */
		अगर (next_bit == -1) अणु
			xfs_buf_item_copy_iovec(lv, vecp, bp, offset,
						first_bit, nbits);
			blfp->blf_size++;
			अवरोध;
		पूर्ण अन्यथा अगर (next_bit != last_bit + 1 ||
		           xfs_buf_item_straddle(bp, offset, first_bit, nbits)) अणु
			xfs_buf_item_copy_iovec(lv, vecp, bp, offset,
						first_bit, nbits);
			blfp->blf_size++;
			first_bit = next_bit;
			last_bit = next_bit;
			nbits = 1;
		पूर्ण अन्यथा अणु
			last_bit++;
			nbits++;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the
 * given log buf item.  It fills the first entry with a buf log
 * क्रमmat काष्ठाure, and the rest poपूर्णांक to contiguous chunks
 * within the buffer.
 */
STATIC व्योम
xfs_buf_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_buf_log_item	*bip = BUF_ITEM(lip);
	काष्ठा xfs_buf		*bp = bip->bli_buf;
	काष्ठा xfs_log_iovec	*vecp = शून्य;
	uपूर्णांक			offset = 0;
	पूर्णांक			i;

	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);
	ASSERT((bip->bli_flags & XFS_BLI_LOGGED) ||
	       (bip->bli_flags & XFS_BLI_STALE));
	ASSERT((bip->bli_flags & XFS_BLI_STALE) ||
	       (xfs_blft_from_flags(&bip->__bli_क्रमmat) > XFS_BLFT_UNKNOWN_BUF
	        && xfs_blft_from_flags(&bip->__bli_क्रमmat) < XFS_BLFT_MAX_BUF));
	ASSERT(!(bip->bli_flags & XFS_BLI_ORDERED) ||
	       (bip->bli_flags & XFS_BLI_STALE));


	/*
	 * If it is an inode buffer, transfer the in-memory state to the
	 * क्रमmat flags and clear the in-memory state.
	 *
	 * For buffer based inode allocation, we करो not transfer
	 * this state अगर the inode buffer allocation has not yet been committed
	 * to the log as setting the XFS_BLI_INODE_BUF flag will prevent
	 * correct replay of the inode allocation.
	 *
	 * For icreate item based inode allocation, the buffers aren't written
	 * to the journal during allocation, and hence we should always tag the
	 * buffer as an inode buffer so that the correct unlinked list replay
	 * occurs during recovery.
	 */
	अगर (bip->bli_flags & XFS_BLI_INODE_BUF) अणु
		अगर (xfs_sb_version_has_v3inode(&lip->li_mountp->m_sb) ||
		    !((bip->bli_flags & XFS_BLI_INODE_ALLOC_BUF) &&
		      xfs_log_item_in_current_chkpt(lip)))
			bip->__bli_क्रमmat.blf_flags |= XFS_BLF_INODE_BUF;
		bip->bli_flags &= ~XFS_BLI_INODE_BUF;
	पूर्ण

	क्रम (i = 0; i < bip->bli_क्रमmat_count; i++) अणु
		xfs_buf_item_क्रमmat_segment(bip, lv, &vecp, offset,
					    &bip->bli_क्रमmats[i]);
		offset += BBTOB(bp->b_maps[i].bm_len);
	पूर्ण

	/*
	 * Check to make sure everything is consistent.
	 */
	trace_xfs_buf_item_क्रमmat(bip);
पूर्ण

/*
 * This is called to pin the buffer associated with the buf log item in memory
 * so it cannot be written out.
 *
 * We also always take a reference to the buffer log item here so that the bli
 * is held जबतक the item is pinned in memory. This means that we can
 * unconditionally drop the reference count a transaction holds when the
 * transaction is completed.
 */
STATIC व्योम
xfs_buf_item_pin(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_buf_log_item	*bip = BUF_ITEM(lip);

	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);
	ASSERT((bip->bli_flags & XFS_BLI_LOGGED) ||
	       (bip->bli_flags & XFS_BLI_ORDERED) ||
	       (bip->bli_flags & XFS_BLI_STALE));

	trace_xfs_buf_item_pin(bip);

	atomic_inc(&bip->bli_refcount);
	atomic_inc(&bip->bli_buf->b_pin_count);
पूर्ण

/*
 * This is called to unpin the buffer associated with the buf log
 * item which was previously pinned with a call to xfs_buf_item_pin().
 *
 * Also drop the reference to the buf item क्रम the current transaction.
 * If the XFS_BLI_STALE flag is set and we are the last reference,
 * then मुक्त up the buf log item and unlock the buffer.
 *
 * If the हटाओ flag is set we are called from uncommit in the
 * क्रमced-shutकरोwn path.  If that is true and the reference count on
 * the log item is going to drop to zero we need to मुक्त the item's
 * descriptor in the transaction.
 */
STATIC व्योम
xfs_buf_item_unpin(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			हटाओ)
अणु
	काष्ठा xfs_buf_log_item	*bip = BUF_ITEM(lip);
	काष्ठा xfs_buf		*bp = bip->bli_buf;
	पूर्णांक			stale = bip->bli_flags & XFS_BLI_STALE;
	पूर्णांक			मुक्तd;

	ASSERT(bp->b_log_item == bip);
	ASSERT(atomic_पढ़ो(&bip->bli_refcount) > 0);

	trace_xfs_buf_item_unpin(bip);

	मुक्तd = atomic_dec_and_test(&bip->bli_refcount);

	अगर (atomic_dec_and_test(&bp->b_pin_count))
		wake_up_all(&bp->b_रुकोers);

	अगर (मुक्तd && stale) अणु
		ASSERT(bip->bli_flags & XFS_BLI_STALE);
		ASSERT(xfs_buf_islocked(bp));
		ASSERT(bp->b_flags & XBF_STALE);
		ASSERT(bip->__bli_क्रमmat.blf_flags & XFS_BLF_CANCEL);

		trace_xfs_buf_item_unpin_stale(bip);

		अगर (हटाओ) अणु
			/*
			 * If we are in a transaction context, we have to
			 * हटाओ the log item from the transaction as we are
			 * about to release our reference to the buffer.  If we
			 * करोn't, the unlock that occurs later in
			 * xfs_trans_uncommit() will try to reference the
			 * buffer which we no दीर्घer have a hold on.
			 */
			अगर (!list_empty(&lip->li_trans))
				xfs_trans_del_item(lip);

			/*
			 * Since the transaction no दीर्घer refers to the buffer,
			 * the buffer should no दीर्घer refer to the transaction.
			 */
			bp->b_transp = शून्य;
		पूर्ण

		/*
		 * If we get called here because of an IO error, we may or may
		 * not have the item on the AIL. xfs_trans_ail_delete() will
		 * take care of that situation. xfs_trans_ail_delete() drops
		 * the AIL lock.
		 */
		अगर (bip->bli_flags & XFS_BLI_STALE_INODE) अणु
			xfs_buf_item_करोne(bp);
			xfs_buf_inode_ioकरोne(bp);
			ASSERT(list_empty(&bp->b_li_list));
		पूर्ण अन्यथा अणु
			xfs_trans_ail_delete(lip, SHUTDOWN_LOG_IO_ERROR);
			xfs_buf_item_rअन्यथा(bp);
			ASSERT(bp->b_log_item == शून्य);
		पूर्ण
		xfs_buf_rअन्यथा(bp);
	पूर्ण अन्यथा अगर (मुक्तd && हटाओ) अणु
		/*
		 * The buffer must be locked and held by the caller to simulate
		 * an async I/O failure.
		 */
		xfs_buf_lock(bp);
		xfs_buf_hold(bp);
		bp->b_flags |= XBF_ASYNC;
		xfs_buf_ioend_fail(bp);
	पूर्ण
पूर्ण

STATIC uपूर्णांक
xfs_buf_item_push(
	काष्ठा xfs_log_item	*lip,
	काष्ठा list_head	*buffer_list)
अणु
	काष्ठा xfs_buf_log_item	*bip = BUF_ITEM(lip);
	काष्ठा xfs_buf		*bp = bip->bli_buf;
	uपूर्णांक			rval = XFS_ITEM_SUCCESS;

	अगर (xfs_buf_ispinned(bp))
		वापस XFS_ITEM_PINNED;
	अगर (!xfs_buf_trylock(bp)) अणु
		/*
		 * If we have just raced with a buffer being pinned and it has
		 * been marked stale, we could end up stalling until someone अन्यथा
		 * issues a log क्रमce to unpin the stale buffer. Check क्रम the
		 * race condition here so xfsaild recognizes the buffer is pinned
		 * and queues a log क्रमce to move it aदीर्घ.
		 */
		अगर (xfs_buf_ispinned(bp))
			वापस XFS_ITEM_PINNED;
		वापस XFS_ITEM_LOCKED;
	पूर्ण

	ASSERT(!(bip->bli_flags & XFS_BLI_STALE));

	trace_xfs_buf_item_push(bip);

	/* has a previous flush failed due to IO errors? */
	अगर (bp->b_flags & XBF_WRITE_FAIL) अणु
		xfs_buf_alert_ratelimited(bp, "XFS: Failing async write",
	    "Failing async write on buffer block 0x%llx. Retrying async write.",
					  (दीर्घ दीर्घ)bp->b_bn);
	पूर्ण

	अगर (!xfs_buf_delwri_queue(bp, buffer_list))
		rval = XFS_ITEM_FLUSHING;
	xfs_buf_unlock(bp);
	वापस rval;
पूर्ण

/*
 * Drop the buffer log item refcount and take appropriate action. This helper
 * determines whether the bli must be मुक्तd or not, since a decrement to zero
 * करोes not necessarily mean the bli is unused.
 *
 * Return true अगर the bli is मुक्तd, false otherwise.
 */
bool
xfs_buf_item_put(
	काष्ठा xfs_buf_log_item	*bip)
अणु
	काष्ठा xfs_log_item	*lip = &bip->bli_item;
	bool			पातed;
	bool			dirty;

	/* drop the bli ref and वापस अगर it wasn't the last one */
	अगर (!atomic_dec_and_test(&bip->bli_refcount))
		वापस false;

	/*
	 * We dropped the last ref and must मुक्त the item अगर clean or पातed.
	 * If the bli is dirty and non-पातed, the buffer was clean in the
	 * transaction but still aरुकोing ग_लिखोback from previous changes. In
	 * that हाल, the bli is मुक्तd on buffer ग_लिखोback completion.
	 */
	पातed = test_bit(XFS_LI_ABORTED, &lip->li_flags) ||
		  XFS_FORCED_SHUTDOWN(lip->li_mountp);
	dirty = bip->bli_flags & XFS_BLI_सूचीTY;
	अगर (dirty && !पातed)
		वापस false;

	/*
	 * The bli is पातed or clean. An पातed item may be in the AIL
	 * regardless of dirty state.  For example, consider an पातed
	 * transaction that invalidated a dirty bli and cleared the dirty
	 * state.
	 */
	अगर (पातed)
		xfs_trans_ail_delete(lip, 0);
	xfs_buf_item_rअन्यथा(bip->bli_buf);
	वापस true;
पूर्ण

/*
 * Release the buffer associated with the buf log item.  If there is no dirty
 * logged data associated with the buffer recorded in the buf log item, then
 * मुक्त the buf log item and हटाओ the reference to it in the buffer.
 *
 * This call ignores the recursion count.  It is only called when the buffer
 * should REALLY be unlocked, regardless of the recursion count.
 *
 * We unconditionally drop the transaction's reference to the log item. If the
 * item was logged, then another reference was taken when it was pinned, so we
 * can safely drop the transaction reference now.  This also allows us to aव्योम
 * potential races with the unpin code मुक्तing the bli by not referencing the
 * bli after we've dropped the reference count.
 *
 * If the XFS_BLI_HOLD flag is set in the buf log item, then मुक्त the log item
 * अगर necessary but करो not unlock the buffer.  This is क्रम support of
 * xfs_trans_bhold(). Make sure the XFS_BLI_HOLD field is cleared अगर we करोn't
 * मुक्त the item.
 */
STATIC व्योम
xfs_buf_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_buf_log_item	*bip = BUF_ITEM(lip);
	काष्ठा xfs_buf		*bp = bip->bli_buf;
	bool			released;
	bool			hold = bip->bli_flags & XFS_BLI_HOLD;
	bool			stale = bip->bli_flags & XFS_BLI_STALE;
#अगर defined(DEBUG) || defined(XFS_WARN)
	bool			ordered = bip->bli_flags & XFS_BLI_ORDERED;
	bool			dirty = bip->bli_flags & XFS_BLI_सूचीTY;
	bool			पातed = test_bit(XFS_LI_ABORTED,
						   &lip->li_flags);
#पूर्ण_अगर

	trace_xfs_buf_item_release(bip);

	/*
	 * The bli dirty state should match whether the blf has logged segments
	 * except क्रम ordered buffers, where only the bli should be dirty.
	 */
	ASSERT((!ordered && dirty == xfs_buf_item_dirty_क्रमmat(bip)) ||
	       (ordered && dirty && !xfs_buf_item_dirty_क्रमmat(bip)));
	ASSERT(!stale || (bip->__bli_क्रमmat.blf_flags & XFS_BLF_CANCEL));

	/*
	 * Clear the buffer's association with this transaction and
	 * per-transaction state from the bli, which has been copied above.
	 */
	bp->b_transp = शून्य;
	bip->bli_flags &= ~(XFS_BLI_LOGGED | XFS_BLI_HOLD | XFS_BLI_ORDERED);

	/*
	 * Unref the item and unlock the buffer unless held or stale. Stale
	 * buffers reमुख्य locked until final unpin unless the bli is मुक्तd by
	 * the unref call. The latter implies shutकरोwn because buffer
	 * invalidation dirties the bli and transaction.
	 */
	released = xfs_buf_item_put(bip);
	अगर (hold || (stale && !released))
		वापस;
	ASSERT(!stale || पातed);
	xfs_buf_rअन्यथा(bp);
पूर्ण

STATIC व्योम
xfs_buf_item_committing(
	काष्ठा xfs_log_item	*lip,
	xfs_lsn_t		commit_lsn)
अणु
	वापस xfs_buf_item_release(lip);
पूर्ण

/*
 * This is called to find out where the oldest active copy of the
 * buf log item in the on disk log resides now that the last log
 * ग_लिखो of it completed at the given lsn.
 * We always re-log all the dirty data in a buffer, so usually the
 * latest copy in the on disk log is the only one that matters.  For
 * those हालs we simply वापस the given lsn.
 *
 * The one exception to this is क्रम buffers full of newly allocated
 * inodes.  These buffers are only relogged with the XFS_BLI_INODE_BUF
 * flag set, indicating that only the di_next_unlinked fields from the
 * inodes in the buffers will be replayed during recovery.  If the
 * original newly allocated inode images have not yet been flushed
 * when the buffer is so relogged, then we need to make sure that we
 * keep the old images in the 'active' portion of the log.  We करो this
 * by वापसing the original lsn of that transaction here rather than
 * the current one.
 */
STATIC xfs_lsn_t
xfs_buf_item_committed(
	काष्ठा xfs_log_item	*lip,
	xfs_lsn_t		lsn)
अणु
	काष्ठा xfs_buf_log_item	*bip = BUF_ITEM(lip);

	trace_xfs_buf_item_committed(bip);

	अगर ((bip->bli_flags & XFS_BLI_INODE_ALLOC_BUF) && lip->li_lsn != 0)
		वापस lip->li_lsn;
	वापस lsn;
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_buf_item_ops = अणु
	.iop_size	= xfs_buf_item_size,
	.iop_क्रमmat	= xfs_buf_item_क्रमmat,
	.iop_pin	= xfs_buf_item_pin,
	.iop_unpin	= xfs_buf_item_unpin,
	.iop_release	= xfs_buf_item_release,
	.iop_committing	= xfs_buf_item_committing,
	.iop_committed	= xfs_buf_item_committed,
	.iop_push	= xfs_buf_item_push,
पूर्ण;

STATIC व्योम
xfs_buf_item_get_क्रमmat(
	काष्ठा xfs_buf_log_item	*bip,
	पूर्णांक			count)
अणु
	ASSERT(bip->bli_क्रमmats == शून्य);
	bip->bli_क्रमmat_count = count;

	अगर (count == 1) अणु
		bip->bli_क्रमmats = &bip->__bli_क्रमmat;
		वापस;
	पूर्ण

	bip->bli_क्रमmats = kmem_zalloc(count * माप(काष्ठा xfs_buf_log_क्रमmat),
				0);
पूर्ण

STATIC व्योम
xfs_buf_item_मुक्त_क्रमmat(
	काष्ठा xfs_buf_log_item	*bip)
अणु
	अगर (bip->bli_क्रमmats != &bip->__bli_क्रमmat) अणु
		kmem_मुक्त(bip->bli_क्रमmats);
		bip->bli_क्रमmats = शून्य;
	पूर्ण
पूर्ण

/*
 * Allocate a new buf log item to go with the given buffer.
 * Set the buffer's b_log_item field to poपूर्णांक to the new
 * buf log item.
 */
पूर्णांक
xfs_buf_item_init(
	काष्ठा xfs_buf	*bp,
	काष्ठा xfs_mount *mp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	पूर्णांक			chunks;
	पूर्णांक			map_size;
	पूर्णांक			i;

	/*
	 * Check to see अगर there is alपढ़ोy a buf log item क्रम
	 * this buffer. If we करो alपढ़ोy have one, there is
	 * nothing to करो here so वापस.
	 */
	ASSERT(bp->b_mount == mp);
	अगर (bip) अणु
		ASSERT(bip->bli_item.li_type == XFS_LI_BUF);
		ASSERT(!bp->b_transp);
		ASSERT(bip->bli_buf == bp);
		वापस 0;
	पूर्ण

	bip = kmem_cache_zalloc(xfs_buf_item_zone, GFP_KERNEL | __GFP_NOFAIL);
	xfs_log_item_init(mp, &bip->bli_item, XFS_LI_BUF, &xfs_buf_item_ops);
	bip->bli_buf = bp;

	/*
	 * chunks is the number of XFS_BLF_CHUNK size pieces the buffer
	 * can be भागided पूर्णांकo. Make sure not to truncate any pieces.
	 * map_size is the size of the biपंचांगap needed to describe the
	 * chunks of the buffer.
	 *
	 * Discontiguous buffer support follows the layout of the underlying
	 * buffer. This makes the implementation as simple as possible.
	 */
	xfs_buf_item_get_क्रमmat(bip, bp->b_map_count);

	क्रम (i = 0; i < bip->bli_क्रमmat_count; i++) अणु
		chunks = DIV_ROUND_UP(BBTOB(bp->b_maps[i].bm_len),
				      XFS_BLF_CHUNK);
		map_size = DIV_ROUND_UP(chunks, NBWORD);

		अगर (map_size > XFS_BLF_DATAMAP_SIZE) अणु
			kmem_cache_मुक्त(xfs_buf_item_zone, bip);
			xfs_err(mp,
	"buffer item dirty bitmap (%u uints) too small to reflect %u bytes!",
					map_size,
					BBTOB(bp->b_maps[i].bm_len));
			वापस -EFSCORRUPTED;
		पूर्ण

		bip->bli_क्रमmats[i].blf_type = XFS_LI_BUF;
		bip->bli_क्रमmats[i].blf_blkno = bp->b_maps[i].bm_bn;
		bip->bli_क्रमmats[i].blf_len = bp->b_maps[i].bm_len;
		bip->bli_क्रमmats[i].blf_map_size = map_size;
	पूर्ण

	bp->b_log_item = bip;
	xfs_buf_hold(bp);
	वापस 0;
पूर्ण


/*
 * Mark bytes first through last inclusive as dirty in the buf
 * item's biपंचांगap.
 */
अटल व्योम
xfs_buf_item_log_segment(
	uपूर्णांक			first,
	uपूर्णांक			last,
	uपूर्णांक			*map)
अणु
	uपूर्णांक		first_bit;
	uपूर्णांक		last_bit;
	uपूर्णांक		bits_to_set;
	uपूर्णांक		bits_set;
	uपूर्णांक		word_num;
	uपूर्णांक		*wordp;
	uपूर्णांक		bit;
	uपूर्णांक		end_bit;
	uपूर्णांक		mask;

	ASSERT(first < XFS_BLF_DATAMAP_SIZE * XFS_BLF_CHUNK * NBWORD);
	ASSERT(last < XFS_BLF_DATAMAP_SIZE * XFS_BLF_CHUNK * NBWORD);

	/*
	 * Convert byte offsets to bit numbers.
	 */
	first_bit = first >> XFS_BLF_SHIFT;
	last_bit = last >> XFS_BLF_SHIFT;

	/*
	 * Calculate the total number of bits to be set.
	 */
	bits_to_set = last_bit - first_bit + 1;

	/*
	 * Get a poपूर्णांकer to the first word in the biपंचांगap
	 * to set a bit in.
	 */
	word_num = first_bit >> BIT_TO_WORD_SHIFT;
	wordp = &map[word_num];

	/*
	 * Calculate the starting bit in the first word.
	 */
	bit = first_bit & (uपूर्णांक)(NBWORD - 1);

	/*
	 * First set any bits in the first word of our range.
	 * If it starts at bit 0 of the word, it will be
	 * set below rather than here.  That is what the variable
	 * bit tells us. The variable bits_set tracks the number
	 * of bits that have been set so far.  End_bit is the number
	 * of the last bit to be set in this word plus one.
	 */
	अगर (bit) अणु
		end_bit = min(bit + bits_to_set, (uपूर्णांक)NBWORD);
		mask = ((1U << (end_bit - bit)) - 1) << bit;
		*wordp |= mask;
		wordp++;
		bits_set = end_bit - bit;
	पूर्ण अन्यथा अणु
		bits_set = 0;
	पूर्ण

	/*
	 * Now set bits a whole word at a समय that are between
	 * first_bit and last_bit.
	 */
	जबतक ((bits_to_set - bits_set) >= NBWORD) अणु
		*wordp = 0xffffffff;
		bits_set += NBWORD;
		wordp++;
	पूर्ण

	/*
	 * Finally, set any bits left to be set in one last partial word.
	 */
	end_bit = bits_to_set - bits_set;
	अगर (end_bit) अणु
		mask = (1U << end_bit) - 1;
		*wordp |= mask;
	पूर्ण
पूर्ण

/*
 * Mark bytes first through last inclusive as dirty in the buf
 * item's biपंचांगap.
 */
व्योम
xfs_buf_item_log(
	काष्ठा xfs_buf_log_item	*bip,
	uपूर्णांक			first,
	uपूर्णांक			last)
अणु
	पूर्णांक			i;
	uपूर्णांक			start;
	uपूर्णांक			end;
	काष्ठा xfs_buf		*bp = bip->bli_buf;

	/*
	 * walk each buffer segment and mark them dirty appropriately.
	 */
	start = 0;
	क्रम (i = 0; i < bip->bli_क्रमmat_count; i++) अणु
		अगर (start > last)
			अवरोध;
		end = start + BBTOB(bp->b_maps[i].bm_len) - 1;

		/* skip to the map that includes the first byte to log */
		अगर (first > end) अणु
			start += BBTOB(bp->b_maps[i].bm_len);
			जारी;
		पूर्ण

		/*
		 * Trim the range to this segment and mark it in the biपंचांगap.
		 * Note that we must convert buffer offsets to segment relative
		 * offsets (e.g., the first byte of each segment is byte 0 of
		 * that segment).
		 */
		अगर (first < start)
			first = start;
		अगर (end > last)
			end = last;
		xfs_buf_item_log_segment(first - start, end - start,
					 &bip->bli_क्रमmats[i].blf_data_map[0]);

		start += BBTOB(bp->b_maps[i].bm_len);
	पूर्ण
पूर्ण


/*
 * Return true अगर the buffer has any ranges logged/dirtied by a transaction,
 * false otherwise.
 */
bool
xfs_buf_item_dirty_क्रमmat(
	काष्ठा xfs_buf_log_item	*bip)
अणु
	पूर्णांक			i;

	क्रम (i = 0; i < bip->bli_क्रमmat_count; i++) अणु
		अगर (!xfs_biपंचांगap_empty(bip->bli_क्रमmats[i].blf_data_map,
			     bip->bli_क्रमmats[i].blf_map_size))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

STATIC व्योम
xfs_buf_item_मुक्त(
	काष्ठा xfs_buf_log_item	*bip)
अणु
	xfs_buf_item_मुक्त_क्रमmat(bip);
	kmem_मुक्त(bip->bli_item.li_lv_shaकरोw);
	kmem_cache_मुक्त(xfs_buf_item_zone, bip);
पूर्ण

/*
 * xfs_buf_item_rअन्यथा() is called when the buf log item is no दीर्घer needed.
 */
व्योम
xfs_buf_item_rअन्यथा(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;

	trace_xfs_buf_item_rअन्यथा(bp, _RET_IP_);
	ASSERT(!test_bit(XFS_LI_IN_AIL, &bip->bli_item.li_flags));

	bp->b_log_item = शून्य;
	xfs_buf_rele(bp);
	xfs_buf_item_मुक्त(bip);
पूर्ण

व्योम
xfs_buf_item_करोne(
	काष्ठा xfs_buf		*bp)
अणु
	/*
	 * If we are क्रमcibly shutting करोwn, this may well be off the AIL
	 * alपढ़ोy. That's because we simulate the log-committed callbacks to
	 * unpin these buffers. Or we may never have put this item on AIL
	 * because of the transaction was पातed क्रमcibly.
	 * xfs_trans_ail_delete() takes care of these.
	 *
	 * Either way, AIL is useless अगर we're क्रमcing a shutकरोwn.
	 *
	 * Note that log recovery ग_लिखोs might have buffer items that are not on
	 * the AIL even when the file प्रणाली is not shut करोwn.
	 */
	xfs_trans_ail_delete(&bp->b_log_item->bli_item,
			     (bp->b_flags & _XBF_LOGRECOVERY) ? 0 :
			     SHUTDOWN_CORRUPT_INCORE);
	xfs_buf_item_rअन्यथा(bp);
पूर्ण
