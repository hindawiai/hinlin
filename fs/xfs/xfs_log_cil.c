<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2010 Red Hat, Inc. All Rights Reserved.
 */

#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_extent_busy.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_log.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_trace.h"

काष्ठा workqueue_काष्ठा *xfs_discard_wq;

/*
 * Allocate a new ticket. Failing to get a new ticket makes it really hard to
 * recover, so we करोn't allow failure here. Also, we allocate in a context that
 * we करोn't want to be issuing transactions from, so we need to tell the
 * allocation code this as well.
 *
 * We करोn't reserve any space क्रम the ticket - we are going to steal whatever
 * space we require from transactions as they commit. To ensure we reserve all
 * the space required, we need to set the current reservation of the ticket to
 * zero so that we know to steal the initial transaction overhead from the
 * first transaction commit.
 */
अटल काष्ठा xlog_ticket *
xlog_cil_ticket_alloc(
	काष्ठा xlog	*log)
अणु
	काष्ठा xlog_ticket *tic;

	tic = xlog_ticket_alloc(log, 0, 1, XFS_TRANSACTION, 0);

	/*
	 * set the current reservation to zero so we know to steal the basic
	 * transaction overhead reservation from the first transaction commit.
	 */
	tic->t_curr_res = 0;
	वापस tic;
पूर्ण

/*
 * After the first stage of log recovery is करोne, we know where the head and
 * tail of the log are. We need this log initialisation करोne beक्रमe we can
 * initialise the first CIL checkpoपूर्णांक context.
 *
 * Here we allocate a log ticket to track space usage during a CIL push.  This
 * ticket is passed to xlog_ग_लिखो() directly so that we करोn't slowly leak log
 * space by failing to account क्रम space used by log headers and additional
 * region headers क्रम split regions.
 */
व्योम
xlog_cil_init_post_recovery(
	काष्ठा xlog	*log)
अणु
	log->l_cilp->xc_ctx->ticket = xlog_cil_ticket_alloc(log);
	log->l_cilp->xc_ctx->sequence = 1;
पूर्ण

अटल अंतरभूत पूर्णांक
xlog_cil_iovec_space(
	uपूर्णांक	niovecs)
अणु
	वापस round_up((माप(काष्ठा xfs_log_vec) +
					niovecs * माप(काष्ठा xfs_log_iovec)),
			माप(uपूर्णांक64_t));
पूर्ण

/*
 * Allocate or pin log vector buffers क्रम CIL insertion.
 *
 * The CIL currently uses disposable buffers क्रम copying a snapshot of the
 * modअगरied items पूर्णांकo the log during a push. The biggest problem with this is
 * the requirement to allocate the disposable buffer during the commit अगर:
 *	a) करोes not exist; or
 *	b) it is too small
 *
 * If we करो this allocation within xlog_cil_insert_क्रमmat_items(), it is करोne
 * under the xc_ctx_lock, which means that a CIL push cannot occur during
 * the memory allocation. This means that we have a potential deadlock situation
 * under low memory conditions when we have lots of dirty metadata pinned in
 * the CIL and we need a CIL commit to occur to मुक्त memory.
 *
 * To aव्योम this, we need to move the memory allocation outside the
 * xc_ctx_lock, but because the log vector buffers are disposable, that खोलोs
 * up a TOCTOU race condition w.r.t. the CIL committing and removing the log
 * vector buffers between the check and the क्रमmatting of the item पूर्णांकo the
 * log vector buffer within the xc_ctx_lock.
 *
 * Because the log vector buffer needs to be unchanged during the CIL push
 * process, we cannot share the buffer between the transaction commit (which
 * modअगरies the buffer) and the CIL push context that is writing the changes
 * पूर्णांकo the log. This means skipping pपुनः_स्मृतिation of buffer space is
 * unreliable, but we most definitely करो not want to be allocating and मुक्तing
 * buffers unnecessarily during commits when overग_लिखोs can be करोne safely.
 *
 * The simplest solution to this problem is to allocate a shaकरोw buffer when a
 * log item is committed क्रम the second समय, and then to only use this buffer
 * अगर necessary. The buffer can reमुख्य attached to the log item until such समय
 * it is needed, and this is the buffer that is पुनः_स्मृतिated to match the size of
 * the incoming modअगरication. Then during the क्रमmatting of the item we can swap
 * the active buffer with the new one अगर we can't reuse the existing buffer. We
 * करोn't मुक्त the old buffer as it may be reused on the next modअगरication अगर
 * it's size is right, otherwise we'll मुक्त and पुनः_स्मृतिate it at that poपूर्णांक.
 *
 * This function builds a vector क्रम the changes in each log item in the
 * transaction. It then works out the length of the buffer needed क्रम each log
 * item, allocates them and attaches the vector to the log item in preparation
 * क्रम the क्रमmatting step which occurs under the xc_ctx_lock.
 *
 * While this means the memory footprपूर्णांक goes up, it aव्योमs the repeated
 * alloc/मुक्त pattern that repeated modअगरications of an item would otherwise
 * cause, and hence minimises the CPU overhead of such behaviour.
 */
अटल व्योम
xlog_cil_alloc_shaकरोw_bufs(
	काष्ठा xlog		*log,
	काष्ठा xfs_trans	*tp)
अणु
	काष्ठा xfs_log_item	*lip;

	list_क्रम_each_entry(lip, &tp->t_items, li_trans) अणु
		काष्ठा xfs_log_vec *lv;
		पूर्णांक	niovecs = 0;
		पूर्णांक	nbytes = 0;
		पूर्णांक	buf_size;
		bool	ordered = false;

		/* Skip items which aren't dirty in this transaction. */
		अगर (!test_bit(XFS_LI_सूचीTY, &lip->li_flags))
			जारी;

		/* get number of vecs and size of data to be stored */
		lip->li_ops->iop_size(lip, &niovecs, &nbytes);

		/*
		 * Ordered items need to be tracked but we करो not wish to ग_लिखो
		 * them. We need a logvec to track the object, but we करो not
		 * need an iovec or buffer to be allocated क्रम copying data.
		 */
		अगर (niovecs == XFS_LOG_VEC_ORDERED) अणु
			ordered = true;
			niovecs = 0;
			nbytes = 0;
		पूर्ण

		/*
		 * We 64-bit align the length of each iovec so that the start
		 * of the next one is naturally aligned.  We'll need to
		 * account क्रम that slack space here. Then round nbytes up
		 * to 64-bit alignment so that the initial buffer alignment is
		 * easy to calculate and verअगरy.
		 */
		nbytes += niovecs * माप(uपूर्णांक64_t);
		nbytes = round_up(nbytes, माप(uपूर्णांक64_t));

		/*
		 * The data buffer needs to start 64-bit aligned, so round up
		 * that space to ensure we can align it appropriately and not
		 * overrun the buffer.
		 */
		buf_size = nbytes + xlog_cil_iovec_space(niovecs);

		/*
		 * अगर we have no shaकरोw buffer, or it is too small, we need to
		 * पुनः_स्मृतिate it.
		 */
		अगर (!lip->li_lv_shaकरोw ||
		    buf_size > lip->li_lv_shaकरोw->lv_size) अणु

			/*
			 * We मुक्त and allocate here as a पुनः_स्मृति would copy
			 * unnecessary data. We करोn't use kmem_zalloc() क्रम the
			 * same reason - we करोn't need to zero the data area in
			 * the buffer, only the log vector header and the iovec
			 * storage.
			 */
			kmem_मुक्त(lip->li_lv_shaकरोw);

			lv = kmem_alloc_large(buf_size, KM_NOFS);
			स_रखो(lv, 0, xlog_cil_iovec_space(niovecs));

			lv->lv_item = lip;
			lv->lv_size = buf_size;
			अगर (ordered)
				lv->lv_buf_len = XFS_LOG_VEC_ORDERED;
			अन्यथा
				lv->lv_iovecp = (काष्ठा xfs_log_iovec *)&lv[1];
			lip->li_lv_shaकरोw = lv;
		पूर्ण अन्यथा अणु
			/* same or smaller, optimise common overग_लिखो हाल */
			lv = lip->li_lv_shaकरोw;
			अगर (ordered)
				lv->lv_buf_len = XFS_LOG_VEC_ORDERED;
			अन्यथा
				lv->lv_buf_len = 0;
			lv->lv_bytes = 0;
			lv->lv_next = शून्य;
		पूर्ण

		/* Ensure the lv is set up according to ->iop_size */
		lv->lv_niovecs = niovecs;

		/* The allocated data region lies beyond the iovec region */
		lv->lv_buf = (अक्षर *)lv + xlog_cil_iovec_space(niovecs);
	पूर्ण

पूर्ण

/*
 * Prepare the log item क्रम insertion पूर्णांकo the CIL. Calculate the dअगरference in
 * log space and vectors it will consume, and अगर it is a new item pin it as
 * well.
 */
STATIC व्योम
xfs_cil_prepare_item(
	काष्ठा xlog		*log,
	काष्ठा xfs_log_vec	*lv,
	काष्ठा xfs_log_vec	*old_lv,
	पूर्णांक			*dअगरf_len,
	पूर्णांक			*dअगरf_iovecs)
अणु
	/* Account क्रम the new LV being passed in */
	अगर (lv->lv_buf_len != XFS_LOG_VEC_ORDERED) अणु
		*dअगरf_len += lv->lv_bytes;
		*dअगरf_iovecs += lv->lv_niovecs;
	पूर्ण

	/*
	 * If there is no old LV, this is the first समय we've seen the item in
	 * this CIL context and so we need to pin it. If we are replacing the
	 * old_lv, then हटाओ the space it accounts क्रम and make it the shaकरोw
	 * buffer क्रम later मुक्तing. In both हालs we are now चयनing to the
	 * shaकरोw buffer, so update the poपूर्णांकer to it appropriately.
	 */
	अगर (!old_lv) अणु
		अगर (lv->lv_item->li_ops->iop_pin)
			lv->lv_item->li_ops->iop_pin(lv->lv_item);
		lv->lv_item->li_lv_shaकरोw = शून्य;
	पूर्ण अन्यथा अगर (old_lv != lv) अणु
		ASSERT(lv->lv_buf_len != XFS_LOG_VEC_ORDERED);

		*dअगरf_len -= old_lv->lv_bytes;
		*dअगरf_iovecs -= old_lv->lv_niovecs;
		lv->lv_item->li_lv_shaकरोw = old_lv;
	पूर्ण

	/* attach new log vector to log item */
	lv->lv_item->li_lv = lv;

	/*
	 * If this is the first समय the item is being committed to the
	 * CIL, store the sequence number on the log item so we can
	 * tell in future commits whether this is the first checkpoपूर्णांक
	 * the item is being committed पूर्णांकo.
	 */
	अगर (!lv->lv_item->li_seq)
		lv->lv_item->li_seq = log->l_cilp->xc_ctx->sequence;
पूर्ण

/*
 * Format log item पूर्णांकo a flat buffers
 *
 * For delayed logging, we need to hold a क्रमmatted buffer containing all the
 * changes on the log item. This enables us to relog the item in memory and
 * ग_लिखो it out asynchronously without needing to relock the object that was
 * modअगरied at the समय it माला_लो written पूर्णांकo the iclog.
 *
 * This function takes the prepared log vectors attached to each log item, and
 * क्रमmats the changes पूर्णांकo the log vector buffer. The buffer it uses is
 * dependent on the current state of the vector in the CIL - the shaकरोw lv is
 * guaranteed to be large enough क्रम the current modअगरication, but we will only
 * use that अगर we can't reuse the existing lv. If we can't reuse the existing
 * lv, then simple swap it out क्रम the shaकरोw lv. We करोn't मुक्त it - that is
 * करोne lazily either by th enext modअगरication or the मुक्तing of the log item.
 *
 * We करोn't set up region headers during this process; we simply copy the
 * regions पूर्णांकo the flat buffer. We can करो this because we still have to करो a
 * क्रमmatting step to ग_लिखो the regions पूर्णांकo the iclog buffer.  Writing the
 * ophdrs during the iclog ग_लिखो means that we can support splitting large
 * regions across iclog boundares without needing a change in the क्रमmat of the
 * item/region encapsulation.
 *
 * Hence what we need to करो now is change the reग_लिखो the vector array to poपूर्णांक
 * to the copied region inside the buffer we just allocated. This allows us to
 * क्रमmat the regions पूर्णांकo the iclog as though they are being क्रमmatted
 * directly out of the objects themselves.
 */
अटल व्योम
xlog_cil_insert_क्रमmat_items(
	काष्ठा xlog		*log,
	काष्ठा xfs_trans	*tp,
	पूर्णांक			*dअगरf_len,
	पूर्णांक			*dअगरf_iovecs)
अणु
	काष्ठा xfs_log_item	*lip;


	/* Bail out अगर we didn't find a log item.  */
	अगर (list_empty(&tp->t_items)) अणु
		ASSERT(0);
		वापस;
	पूर्ण

	list_क्रम_each_entry(lip, &tp->t_items, li_trans) अणु
		काष्ठा xfs_log_vec *lv;
		काष्ठा xfs_log_vec *old_lv = शून्य;
		काष्ठा xfs_log_vec *shaकरोw;
		bool	ordered = false;

		/* Skip items which aren't dirty in this transaction. */
		अगर (!test_bit(XFS_LI_सूचीTY, &lip->li_flags))
			जारी;

		/*
		 * The क्रमmatting size inक्रमmation is alपढ़ोy attached to
		 * the shaकरोw lv on the log item.
		 */
		shaकरोw = lip->li_lv_shaकरोw;
		अगर (shaकरोw->lv_buf_len == XFS_LOG_VEC_ORDERED)
			ordered = true;

		/* Skip items that करो not have any vectors क्रम writing */
		अगर (!shaकरोw->lv_niovecs && !ordered)
			जारी;

		/* compare to existing item size */
		old_lv = lip->li_lv;
		अगर (lip->li_lv && shaकरोw->lv_size <= lip->li_lv->lv_size) अणु
			/* same or smaller, optimise common overग_लिखो हाल */
			lv = lip->li_lv;
			lv->lv_next = शून्य;

			अगर (ordered)
				जाओ insert;

			/*
			 * set the item up as though it is a new insertion so
			 * that the space reservation accounting is correct.
			 */
			*dअगरf_iovecs -= lv->lv_niovecs;
			*dअगरf_len -= lv->lv_bytes;

			/* Ensure the lv is set up according to ->iop_size */
			lv->lv_niovecs = shaकरोw->lv_niovecs;

			/* reset the lv buffer inक्रमmation क्रम new क्रमmatting */
			lv->lv_buf_len = 0;
			lv->lv_bytes = 0;
			lv->lv_buf = (अक्षर *)lv +
					xlog_cil_iovec_space(lv->lv_niovecs);
		पूर्ण अन्यथा अणु
			/* चयन to shaकरोw buffer! */
			lv = shaकरोw;
			lv->lv_item = lip;
			अगर (ordered) अणु
				/* track as an ordered logvec */
				ASSERT(lip->li_lv == शून्य);
				जाओ insert;
			पूर्ण
		पूर्ण

		ASSERT(IS_ALIGNED((अचिन्हित दीर्घ)lv->lv_buf, माप(uपूर्णांक64_t)));
		lip->li_ops->iop_क्रमmat(lip, lv);
insert:
		xfs_cil_prepare_item(log, lv, old_lv, dअगरf_len, dअगरf_iovecs);
	पूर्ण
पूर्ण

/*
 * Insert the log items पूर्णांकo the CIL and calculate the dअगरference in space
 * consumed by the item. Add the space to the checkpoपूर्णांक ticket and calculate
 * अगर the change requires additional log metadata. If it करोes, take that space
 * as well. Remove the amount of space we added to the checkpoपूर्णांक ticket from
 * the current transaction ticket so that the accounting works out correctly.
 */
अटल व्योम
xlog_cil_insert_items(
	काष्ठा xlog		*log,
	काष्ठा xfs_trans	*tp)
अणु
	काष्ठा xfs_cil		*cil = log->l_cilp;
	काष्ठा xfs_cil_ctx	*ctx = cil->xc_ctx;
	काष्ठा xfs_log_item	*lip;
	पूर्णांक			len = 0;
	पूर्णांक			dअगरf_iovecs = 0;
	पूर्णांक			iclog_space;
	पूर्णांक			iovhdr_res = 0, split_res = 0, ctx_res = 0;

	ASSERT(tp);

	/*
	 * We can करो this safely because the context can't checkpoपूर्णांक until we
	 * are करोne so it करोesn't matter exactly how we update the CIL.
	 */
	xlog_cil_insert_क्रमmat_items(log, tp, &len, &dअगरf_iovecs);

	spin_lock(&cil->xc_cil_lock);

	/* account क्रम space used by new iovec headers  */
	iovhdr_res = dअगरf_iovecs * माप(xlog_op_header_t);
	len += iovhdr_res;
	ctx->nvecs += dअगरf_iovecs;

	/* attach the transaction to the CIL अगर it has any busy extents */
	अगर (!list_empty(&tp->t_busy))
		list_splice_init(&tp->t_busy, &ctx->busy_extents);

	/*
	 * Now transfer enough transaction reservation to the context ticket
	 * क्रम the checkpoपूर्णांक. The context ticket is special - the unit
	 * reservation has to grow as well as the current reservation as we
	 * steal from tickets so we can correctly determine the space used
	 * during the transaction commit.
	 */
	अगर (ctx->ticket->t_curr_res == 0) अणु
		ctx_res = ctx->ticket->t_unit_res;
		ctx->ticket->t_curr_res = ctx_res;
		tp->t_ticket->t_curr_res -= ctx_res;
	पूर्ण

	/* करो we need space क्रम more log record headers? */
	iclog_space = log->l_iclog_size - log->l_iclog_hsize;
	अगर (len > 0 && (ctx->space_used / iclog_space !=
				(ctx->space_used + len) / iclog_space)) अणु
		split_res = (len + iclog_space - 1) / iclog_space;
		/* need to take पूर्णांकo account split region headers, too */
		split_res *= log->l_iclog_hsize + माप(काष्ठा xlog_op_header);
		ctx->ticket->t_unit_res += split_res;
		ctx->ticket->t_curr_res += split_res;
		tp->t_ticket->t_curr_res -= split_res;
		ASSERT(tp->t_ticket->t_curr_res >= len);
	पूर्ण
	tp->t_ticket->t_curr_res -= len;
	ctx->space_used += len;

	/*
	 * If we've overrun the reservation, dump the tx details beक्रमe we move
	 * the log items. Shutकरोwn is imminent...
	 */
	अगर (WARN_ON(tp->t_ticket->t_curr_res < 0)) अणु
		xfs_warn(log->l_mp, "Transaction log reservation overrun:");
		xfs_warn(log->l_mp,
			 "  log items: %d bytes (iov hdrs: %d bytes)",
			 len, iovhdr_res);
		xfs_warn(log->l_mp, "  split region headers: %d bytes",
			 split_res);
		xfs_warn(log->l_mp, "  ctx ticket: %d bytes", ctx_res);
		xlog_prपूर्णांक_trans(tp);
	पूर्ण

	/*
	 * Now (re-)position everything modअगरied at the tail of the CIL.
	 * We करो this here so we only need to take the CIL lock once during
	 * the transaction commit.
	 */
	list_क्रम_each_entry(lip, &tp->t_items, li_trans) अणु

		/* Skip items which aren't dirty in this transaction. */
		अगर (!test_bit(XFS_LI_सूचीTY, &lip->li_flags))
			जारी;

		/*
		 * Only move the item अगर it isn't alपढ़ोy at the tail. This is
		 * to prevent a transient list_empty() state when reinserting
		 * an item that is alपढ़ोy the only item in the CIL.
		 */
		अगर (!list_is_last(&lip->li_cil, &cil->xc_cil))
			list_move_tail(&lip->li_cil, &cil->xc_cil);
	पूर्ण

	spin_unlock(&cil->xc_cil_lock);

	अगर (tp->t_ticket->t_curr_res < 0)
		xfs_क्रमce_shutकरोwn(log->l_mp, SHUTDOWN_LOG_IO_ERROR);
पूर्ण

अटल व्योम
xlog_cil_मुक्त_logvec(
	काष्ठा xfs_log_vec	*log_vector)
अणु
	काष्ठा xfs_log_vec	*lv;

	क्रम (lv = log_vector; lv; ) अणु
		काष्ठा xfs_log_vec *next = lv->lv_next;
		kmem_मुक्त(lv);
		lv = next;
	पूर्ण
पूर्ण

अटल व्योम
xlog_discard_endio_work(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xfs_cil_ctx	*ctx =
		container_of(work, काष्ठा xfs_cil_ctx, discard_endio_work);
	काष्ठा xfs_mount	*mp = ctx->cil->xc_log->l_mp;

	xfs_extent_busy_clear(mp, &ctx->busy_extents, false);
	kmem_मुक्त(ctx);
पूर्ण

/*
 * Queue up the actual completion to a thपढ़ो to aव्योम IRQ-safe locking क्रम
 * pagb_lock.  Note that we need a unbounded workqueue, otherwise we might
 * get the execution delayed up to 30 seconds क्रम weird reasons.
 */
अटल व्योम
xlog_discard_endio(
	काष्ठा bio		*bio)
अणु
	काष्ठा xfs_cil_ctx	*ctx = bio->bi_निजी;

	INIT_WORK(&ctx->discard_endio_work, xlog_discard_endio_work);
	queue_work(xfs_discard_wq, &ctx->discard_endio_work);
	bio_put(bio);
पूर्ण

अटल व्योम
xlog_discard_busy_extents(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_cil_ctx	*ctx)
अणु
	काष्ठा list_head	*list = &ctx->busy_extents;
	काष्ठा xfs_extent_busy	*busyp;
	काष्ठा bio		*bio = शून्य;
	काष्ठा blk_plug		plug;
	पूर्णांक			error = 0;

	ASSERT(mp->m_flags & XFS_MOUNT_DISCARD);

	blk_start_plug(&plug);
	list_क्रम_each_entry(busyp, list, list) अणु
		trace_xfs_discard_extent(mp, busyp->agno, busyp->bno,
					 busyp->length);

		error = __blkdev_issue_discard(mp->m_ddev_targp->bt_bdev,
				XFS_AGB_TO_DADDR(mp, busyp->agno, busyp->bno),
				XFS_FSB_TO_BB(mp, busyp->length),
				GFP_NOFS, 0, &bio);
		अगर (error && error != -EOPNOTSUPP) अणु
			xfs_info(mp,
	 "discard failed for extent [0x%llx,%u], error %d",
				 (अचिन्हित दीर्घ दीर्घ)busyp->bno,
				 busyp->length,
				 error);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (bio) अणु
		bio->bi_निजी = ctx;
		bio->bi_end_io = xlog_discard_endio;
		submit_bio(bio);
	पूर्ण अन्यथा अणु
		xlog_discard_endio_work(&ctx->discard_endio_work);
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

/*
 * Mark all items committed and clear busy extents. We मुक्त the log vector
 * chains in a separate pass so that we unpin the log items as quickly as
 * possible.
 */
अटल व्योम
xlog_cil_committed(
	काष्ठा xfs_cil_ctx	*ctx)
अणु
	काष्ठा xfs_mount	*mp = ctx->cil->xc_log->l_mp;
	bool			पात = XLOG_FORCED_SHUTDOWN(ctx->cil->xc_log);

	/*
	 * If the I/O failed, we're पातing the commit and alपढ़ोy shutकरोwn.
	 * Wake any commit रुकोers beक्रमe पातing the log items so we करोn't
	 * block async log pushers on callbacks. Async log pushers explicitly करो
	 * not रुको on log क्रमce completion because they may be holding locks
	 * required to unpin items.
	 */
	अगर (पात) अणु
		spin_lock(&ctx->cil->xc_push_lock);
		wake_up_all(&ctx->cil->xc_commit_रुको);
		spin_unlock(&ctx->cil->xc_push_lock);
	पूर्ण

	xfs_trans_committed_bulk(ctx->cil->xc_log->l_ailp, ctx->lv_chain,
					ctx->start_lsn, पात);

	xfs_extent_busy_sort(&ctx->busy_extents);
	xfs_extent_busy_clear(mp, &ctx->busy_extents,
			     (mp->m_flags & XFS_MOUNT_DISCARD) && !पात);

	spin_lock(&ctx->cil->xc_push_lock);
	list_del(&ctx->committing);
	spin_unlock(&ctx->cil->xc_push_lock);

	xlog_cil_मुक्त_logvec(ctx->lv_chain);

	अगर (!list_empty(&ctx->busy_extents))
		xlog_discard_busy_extents(mp, ctx);
	अन्यथा
		kmem_मुक्त(ctx);
पूर्ण

व्योम
xlog_cil_process_committed(
	काष्ठा list_head	*list)
अणु
	काष्ठा xfs_cil_ctx	*ctx;

	जबतक ((ctx = list_first_entry_or_null(list,
			काष्ठा xfs_cil_ctx, iclog_entry))) अणु
		list_del(&ctx->iclog_entry);
		xlog_cil_committed(ctx);
	पूर्ण
पूर्ण

/*
 * Push the Committed Item List to the log.
 *
 * If the current sequence is the same as xc_push_seq we need to करो a flush. If
 * xc_push_seq is less than the current sequence, then it has alपढ़ोy been
 * flushed and we करोn't need to करो anything - the caller will रुको क्रम it to
 * complete अगर necessary.
 *
 * xc_push_seq is checked unlocked against the sequence number क्रम a match.
 * Hence we can allow log क्रमces to run racily and not issue pushes क्रम the
 * same sequence twice.  If we get a race between multiple pushes क्रम the same
 * sequence they will block on the first one and then पात, hence aव्योमing
 * needless pushes.
 */
अटल व्योम
xlog_cil_push_work(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xfs_cil		*cil =
		container_of(work, काष्ठा xfs_cil, xc_push_work);
	काष्ठा xlog		*log = cil->xc_log;
	काष्ठा xfs_log_vec	*lv;
	काष्ठा xfs_cil_ctx	*ctx;
	काष्ठा xfs_cil_ctx	*new_ctx;
	काष्ठा xlog_in_core	*commit_iclog;
	काष्ठा xlog_ticket	*tic;
	पूर्णांक			num_iovecs;
	पूर्णांक			error = 0;
	काष्ठा xfs_trans_header thdr;
	काष्ठा xfs_log_iovec	lhdr;
	काष्ठा xfs_log_vec	lvhdr = अणु शून्य पूर्ण;
	xfs_lsn_t		commit_lsn;
	xfs_lsn_t		push_seq;

	new_ctx = kmem_zalloc(माप(*new_ctx), KM_NOFS);
	new_ctx->ticket = xlog_cil_ticket_alloc(log);

	करोwn_ग_लिखो(&cil->xc_ctx_lock);
	ctx = cil->xc_ctx;

	spin_lock(&cil->xc_push_lock);
	push_seq = cil->xc_push_seq;
	ASSERT(push_seq <= ctx->sequence);

	/*
	 * Wake up any background push रुकोers now this context is being pushed.
	 */
	अगर (ctx->space_used >= XLOG_CIL_BLOCKING_SPACE_LIMIT(log))
		wake_up_all(&cil->xc_push_रुको);

	/*
	 * Check अगर we've anything to push. If there is nothing, then we don't
	 * move on to a new sequence number and so we have to be able to push
	 * this sequence again later.
	 */
	अगर (list_empty(&cil->xc_cil)) अणु
		cil->xc_push_seq = 0;
		spin_unlock(&cil->xc_push_lock);
		जाओ out_skip;
	पूर्ण


	/* check क्रम a previously pushed sequence */
	अगर (push_seq < cil->xc_ctx->sequence) अणु
		spin_unlock(&cil->xc_push_lock);
		जाओ out_skip;
	पूर्ण

	/*
	 * We are now going to push this context, so add it to the committing
	 * list beक्रमe we करो anything अन्यथा. This ensures that anyone रुकोing on
	 * this push can easily detect the dअगरference between a "push in
	 * progress" and "CIL is empty, nothing to करो".
	 *
	 * IOWs, a रुको loop can now check क्रम:
	 *	the current sequence not being found on the committing list;
	 *	an empty CIL; and
	 *	an unchanged sequence number
	 * to detect a push that had nothing to करो and thereक्रमe करोes not need
	 * रुकोing on. If the CIL is not empty, we get put on the committing
	 * list beक्रमe emptying the CIL and bumping the sequence number. Hence
	 * an empty CIL and an unchanged sequence number means we jumped out
	 * above after करोing nothing.
	 *
	 * Hence the रुकोer will either find the commit sequence on the
	 * committing list or the sequence number will be unchanged and the CIL
	 * still dirty. In that latter हाल, the push has not yet started, and
	 * so the रुकोer will have to जारी trying to check the CIL
	 * committing list until it is found. In extreme हालs of delay, the
	 * sequence may fully commit between the attempts the रुको makes to रुको
	 * on the commit sequence.
	 */
	list_add(&ctx->committing, &cil->xc_committing);
	spin_unlock(&cil->xc_push_lock);

	/*
	 * pull all the log vectors off the items in the CIL, and
	 * हटाओ the items from the CIL. We करोn't need the CIL lock
	 * here because it's only needed on the transaction commit
	 * side which is currently locked out by the flush lock.
	 */
	lv = शून्य;
	num_iovecs = 0;
	जबतक (!list_empty(&cil->xc_cil)) अणु
		काष्ठा xfs_log_item	*item;

		item = list_first_entry(&cil->xc_cil,
					काष्ठा xfs_log_item, li_cil);
		list_del_init(&item->li_cil);
		अगर (!ctx->lv_chain)
			ctx->lv_chain = item->li_lv;
		अन्यथा
			lv->lv_next = item->li_lv;
		lv = item->li_lv;
		item->li_lv = शून्य;
		num_iovecs += lv->lv_niovecs;
	पूर्ण

	/*
	 * initialise the new context and attach it to the CIL. Then attach
	 * the current context to the CIL committing list so it can be found
	 * during log क्रमces to extract the commit lsn of the sequence that
	 * needs to be क्रमced.
	 */
	INIT_LIST_HEAD(&new_ctx->committing);
	INIT_LIST_HEAD(&new_ctx->busy_extents);
	new_ctx->sequence = ctx->sequence + 1;
	new_ctx->cil = cil;
	cil->xc_ctx = new_ctx;

	/*
	 * The चयन is now करोne, so we can drop the context lock and move out
	 * of a shared context. We can't just go straight to the commit record,
	 * though - we need to synchronise with previous and future commits so
	 * that the commit records are correctly ordered in the log to ensure
	 * that we process items during log IO completion in the correct order.
	 *
	 * For example, अगर we get an EFI in one checkpoपूर्णांक and the EFD in the
	 * next (e.g. due to log क्रमces), we करो not want the checkpoपूर्णांक with
	 * the EFD to be committed beक्रमe the checkpoपूर्णांक with the EFI.  Hence
	 * we must strictly order the commit records of the checkpoपूर्णांकs so
	 * that: a) the checkpoपूर्णांक callbacks are attached to the iclogs in the
	 * correct order; and b) the checkpoपूर्णांकs are replayed in correct order
	 * in log recovery.
	 *
	 * Hence we need to add this context to the committing context list so
	 * that higher sequences will रुको क्रम us to ग_लिखो out a commit record
	 * beक्रमe they करो.
	 *
	 * xfs_log_क्रमce_lsn requires us to mirror the new sequence पूर्णांकo the cil
	 * काष्ठाure atomically with the addition of this sequence to the
	 * committing list. This also ensures that we can करो unlocked checks
	 * against the current sequence in log क्रमces without risking
	 * deferencing a मुक्तd context poपूर्णांकer.
	 */
	spin_lock(&cil->xc_push_lock);
	cil->xc_current_sequence = new_ctx->sequence;
	spin_unlock(&cil->xc_push_lock);
	up_ग_लिखो(&cil->xc_ctx_lock);

	/*
	 * Build a checkpoपूर्णांक transaction header and ग_लिखो it to the log to
	 * begin the transaction. We need to account क्रम the space used by the
	 * transaction header here as it is not accounted क्रम in xlog_ग_लिखो().
	 *
	 * The LSN we need to pass to the log items on transaction commit is
	 * the LSN reported by the first log vector ग_लिखो. If we use the commit
	 * record lsn then we can move the tail beyond the grant ग_लिखो head.
	 */
	tic = ctx->ticket;
	thdr.th_magic = XFS_TRANS_HEADER_MAGIC;
	thdr.th_type = XFS_TRANS_CHECKPOINT;
	thdr.th_tid = tic->t_tid;
	thdr.th_num_items = num_iovecs;
	lhdr.i_addr = &thdr;
	lhdr.i_len = माप(xfs_trans_header_t);
	lhdr.i_type = XLOG_REG_TYPE_TRANSHDR;
	tic->t_curr_res -= lhdr.i_len + माप(xlog_op_header_t);

	lvhdr.lv_niovecs = 1;
	lvhdr.lv_iovecp = &lhdr;
	lvhdr.lv_next = ctx->lv_chain;

	error = xlog_ग_लिखो(log, &lvhdr, tic, &ctx->start_lsn, शून्य, 0, true);
	अगर (error)
		जाओ out_पात_मुक्त_ticket;

	/*
	 * now that we've written the checkpoपूर्णांक पूर्णांकo the log, strictly
	 * order the commit records so replay will get them in the right order.
	 */
restart:
	spin_lock(&cil->xc_push_lock);
	list_क्रम_each_entry(new_ctx, &cil->xc_committing, committing) अणु
		/*
		 * Aव्योम getting stuck in this loop because we were woken by the
		 * shutकरोwn, but then went back to sleep once alपढ़ोy in the
		 * shutकरोwn state.
		 */
		अगर (XLOG_FORCED_SHUTDOWN(log)) अणु
			spin_unlock(&cil->xc_push_lock);
			जाओ out_पात_मुक्त_ticket;
		पूर्ण

		/*
		 * Higher sequences will रुको क्रम this one so skip them.
		 * Don't रुको क्रम our own sequence, either.
		 */
		अगर (new_ctx->sequence >= ctx->sequence)
			जारी;
		अगर (!new_ctx->commit_lsn) अणु
			/*
			 * It is still being pushed! Wait क्रम the push to
			 * complete, then start again from the beginning.
			 */
			xlog_रुको(&cil->xc_commit_रुको, &cil->xc_push_lock);
			जाओ restart;
		पूर्ण
	पूर्ण
	spin_unlock(&cil->xc_push_lock);

	error = xlog_commit_record(log, tic, &commit_iclog, &commit_lsn);
	अगर (error)
		जाओ out_पात_मुक्त_ticket;

	xfs_log_ticket_ungrant(log, tic);

	spin_lock(&commit_iclog->ic_callback_lock);
	अगर (commit_iclog->ic_state == XLOG_STATE_IOERROR) अणु
		spin_unlock(&commit_iclog->ic_callback_lock);
		जाओ out_पात;
	पूर्ण
	ASSERT_ALWAYS(commit_iclog->ic_state == XLOG_STATE_ACTIVE ||
		      commit_iclog->ic_state == XLOG_STATE_WANT_SYNC);
	list_add_tail(&ctx->iclog_entry, &commit_iclog->ic_callbacks);
	spin_unlock(&commit_iclog->ic_callback_lock);

	/*
	 * now the checkpoपूर्णांक commit is complete and we've attached the
	 * callbacks to the iclog we can assign the commit LSN to the context
	 * and wake up anyone who is रुकोing क्रम the commit to complete.
	 */
	spin_lock(&cil->xc_push_lock);
	ctx->commit_lsn = commit_lsn;
	wake_up_all(&cil->xc_commit_रुको);
	spin_unlock(&cil->xc_push_lock);

	/* release the hounds! */
	xfs_log_release_iclog(commit_iclog);
	वापस;

out_skip:
	up_ग_लिखो(&cil->xc_ctx_lock);
	xfs_log_ticket_put(new_ctx->ticket);
	kmem_मुक्त(new_ctx);
	वापस;

out_पात_मुक्त_ticket:
	xfs_log_ticket_ungrant(log, tic);
out_पात:
	ASSERT(XLOG_FORCED_SHUTDOWN(log));
	xlog_cil_committed(ctx);
पूर्ण

/*
 * We need to push CIL every so often so we करोn't cache more than we can fit in
 * the log. The limit really is that a checkpoपूर्णांक can't be more than half the
 * log (the current checkpoपूर्णांक is not allowed to overग_लिखो the previous
 * checkpoपूर्णांक), but commit latency and memory usage limit this to a smaller
 * size.
 */
अटल व्योम
xlog_cil_push_background(
	काष्ठा xlog	*log) __releases(cil->xc_ctx_lock)
अणु
	काष्ठा xfs_cil	*cil = log->l_cilp;

	/*
	 * The cil won't be empty because we are called जबतक holding the
	 * context lock so whatever we added to the CIL will still be there
	 */
	ASSERT(!list_empty(&cil->xc_cil));

	/*
	 * करोn't do a background push if we haven't used up all the
	 * space available yet.
	 */
	अगर (cil->xc_ctx->space_used < XLOG_CIL_SPACE_LIMIT(log)) अणु
		up_पढ़ो(&cil->xc_ctx_lock);
		वापस;
	पूर्ण

	spin_lock(&cil->xc_push_lock);
	अगर (cil->xc_push_seq < cil->xc_current_sequence) अणु
		cil->xc_push_seq = cil->xc_current_sequence;
		queue_work(log->l_mp->m_cil_workqueue, &cil->xc_push_work);
	पूर्ण

	/*
	 * Drop the context lock now, we can't hold that अगर we need to sleep
	 * because we are over the blocking threshold. The push_lock is still
	 * held, so blocking threshold sleep/wakeup is still correctly
	 * serialised here.
	 */
	up_पढ़ो(&cil->xc_ctx_lock);

	/*
	 * If we are well over the space limit, throttle the work that is being
	 * करोne until the push work on this context has begun.
	 */
	अगर (cil->xc_ctx->space_used >= XLOG_CIL_BLOCKING_SPACE_LIMIT(log)) अणु
		trace_xfs_log_cil_रुको(log, cil->xc_ctx->ticket);
		ASSERT(cil->xc_ctx->space_used < log->l_logsize);
		xlog_रुको(&cil->xc_push_रुको, &cil->xc_push_lock);
		वापस;
	पूर्ण

	spin_unlock(&cil->xc_push_lock);

पूर्ण

/*
 * xlog_cil_push_now() is used to trigger an immediate CIL push to the sequence
 * number that is passed. When it वापसs, the work will be queued क्रम
 * @push_seq, but it won't be completed. The caller is expected to करो any
 * रुकोing क्रम push_seq to complete अगर it is required.
 */
अटल व्योम
xlog_cil_push_now(
	काष्ठा xlog	*log,
	xfs_lsn_t	push_seq)
अणु
	काष्ठा xfs_cil	*cil = log->l_cilp;

	अगर (!cil)
		वापस;

	ASSERT(push_seq && push_seq <= cil->xc_current_sequence);

	/* start on any pending background push to minimise रुको समय on it */
	flush_work(&cil->xc_push_work);

	/*
	 * If the CIL is empty or we've alपढ़ोy pushed the sequence then
	 * there's no work we need to करो.
	 */
	spin_lock(&cil->xc_push_lock);
	अगर (list_empty(&cil->xc_cil) || push_seq <= cil->xc_push_seq) अणु
		spin_unlock(&cil->xc_push_lock);
		वापस;
	पूर्ण

	cil->xc_push_seq = push_seq;
	queue_work(log->l_mp->m_cil_workqueue, &cil->xc_push_work);
	spin_unlock(&cil->xc_push_lock);
पूर्ण

bool
xlog_cil_empty(
	काष्ठा xlog	*log)
अणु
	काष्ठा xfs_cil	*cil = log->l_cilp;
	bool		empty = false;

	spin_lock(&cil->xc_push_lock);
	अगर (list_empty(&cil->xc_cil))
		empty = true;
	spin_unlock(&cil->xc_push_lock);
	वापस empty;
पूर्ण

/*
 * Commit a transaction with the given vector to the Committed Item List.
 *
 * To करो this, we need to क्रमmat the item, pin it in memory अगर required and
 * account क्रम the space used by the transaction. Once we have करोne that we
 * need to release the unused reservation क्रम the transaction, attach the
 * transaction to the checkpoपूर्णांक context so we carry the busy extents through
 * to checkpoपूर्णांक completion, and then unlock all the items in the transaction.
 *
 * Called with the context lock alपढ़ोy held in पढ़ो mode to lock out
 * background commit, वापसs without it held once background commits are
 * allowed again.
 */
व्योम
xfs_log_commit_cil(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_lsn_t		*commit_lsn,
	bool			regrant)
अणु
	काष्ठा xlog		*log = mp->m_log;
	काष्ठा xfs_cil		*cil = log->l_cilp;
	काष्ठा xfs_log_item	*lip, *next;
	xfs_lsn_t		xc_commit_lsn;

	/*
	 * Do all necessary memory allocation beक्रमe we lock the CIL.
	 * This ensures the allocation करोes not deadlock with a CIL
	 * push in memory reclaim (e.g. from kswapd).
	 */
	xlog_cil_alloc_shaकरोw_bufs(log, tp);

	/* lock out background commit */
	करोwn_पढ़ो(&cil->xc_ctx_lock);

	xlog_cil_insert_items(log, tp);

	xc_commit_lsn = cil->xc_ctx->sequence;
	अगर (commit_lsn)
		*commit_lsn = xc_commit_lsn;

	अगर (regrant && !XLOG_FORCED_SHUTDOWN(log))
		xfs_log_ticket_regrant(log, tp->t_ticket);
	अन्यथा
		xfs_log_ticket_ungrant(log, tp->t_ticket);
	tp->t_ticket = शून्य;
	xfs_trans_unreserve_and_mod_sb(tp);

	/*
	 * Once all the items of the transaction have been copied to the CIL,
	 * the items can be unlocked and possibly मुक्तd.
	 *
	 * This needs to be करोne beक्रमe we drop the CIL context lock because we
	 * have to update state in the log items and unlock them beक्रमe they go
	 * to disk. If we करोn't, then the CIL checkpoपूर्णांक can race with us and
	 * we can run checkpoपूर्णांक completion beक्रमe we've updated and unlocked
	 * the log items. This affects (at least) processing of stale buffers,
	 * inodes and EFIs.
	 */
	trace_xfs_trans_commit_items(tp, _RET_IP_);
	list_क्रम_each_entry_safe(lip, next, &tp->t_items, li_trans) अणु
		xfs_trans_del_item(lip);
		अगर (lip->li_ops->iop_committing)
			lip->li_ops->iop_committing(lip, xc_commit_lsn);
	पूर्ण

	/* xlog_cil_push_background() releases cil->xc_ctx_lock */
	xlog_cil_push_background(log);
पूर्ण

/*
 * Conditionally push the CIL based on the sequence passed in.
 *
 * We only need to push अगर we haven't alपढ़ोy pushed the sequence
 * number given. Hence the only समय we will trigger a push here is
 * अगर the push sequence is the same as the current context.
 *
 * We वापस the current commit lsn to allow the callers to determine अगर a
 * iclog flush is necessary following this call.
 */
xfs_lsn_t
xlog_cil_क्रमce_lsn(
	काष्ठा xlog	*log,
	xfs_lsn_t	sequence)
अणु
	काष्ठा xfs_cil		*cil = log->l_cilp;
	काष्ठा xfs_cil_ctx	*ctx;
	xfs_lsn_t		commit_lsn = शून्यCOMMITLSN;

	ASSERT(sequence <= cil->xc_current_sequence);

	/*
	 * check to see अगर we need to क्रमce out the current context.
	 * xlog_cil_push() handles racing pushes क्रम the same sequence,
	 * so no need to deal with it here.
	 */
restart:
	xlog_cil_push_now(log, sequence);

	/*
	 * See अगर we can find a previous sequence still committing.
	 * We need to रुको क्रम all previous sequence commits to complete
	 * beक्रमe allowing the क्रमce of push_seq to go ahead. Hence block
	 * on commits क्रम those as well.
	 */
	spin_lock(&cil->xc_push_lock);
	list_क्रम_each_entry(ctx, &cil->xc_committing, committing) अणु
		/*
		 * Aव्योम getting stuck in this loop because we were woken by the
		 * shutकरोwn, but then went back to sleep once alपढ़ोy in the
		 * shutकरोwn state.
		 */
		अगर (XLOG_FORCED_SHUTDOWN(log))
			जाओ out_shutकरोwn;
		अगर (ctx->sequence > sequence)
			जारी;
		अगर (!ctx->commit_lsn) अणु
			/*
			 * It is still being pushed! Wait क्रम the push to
			 * complete, then start again from the beginning.
			 */
			xlog_रुको(&cil->xc_commit_रुको, &cil->xc_push_lock);
			जाओ restart;
		पूर्ण
		अगर (ctx->sequence != sequence)
			जारी;
		/* found it! */
		commit_lsn = ctx->commit_lsn;
	पूर्ण

	/*
	 * The call to xlog_cil_push_now() executes the push in the background.
	 * Hence by the समय we have got here it our sequence may not have been
	 * pushed yet. This is true अगर the current sequence still matches the
	 * push sequence after the above रुको loop and the CIL still contains
	 * dirty objects. This is guaranteed by the push code first adding the
	 * context to the committing list beक्रमe emptying the CIL.
	 *
	 * Hence अगर we करोn't find the context in the committing list and the
	 * current sequence number is unchanged then the CIL contents are
	 * signअगरicant.  If the CIL is empty, अगर means there was nothing to push
	 * and that means there is nothing to रुको क्रम. If the CIL is not empty,
	 * it means we haven't yet started the push, because अगर it had started
	 * we would have found the context on the committing list.
	 */
	अगर (sequence == cil->xc_current_sequence &&
	    !list_empty(&cil->xc_cil)) अणु
		spin_unlock(&cil->xc_push_lock);
		जाओ restart;
	पूर्ण

	spin_unlock(&cil->xc_push_lock);
	वापस commit_lsn;

	/*
	 * We detected a shutकरोwn in progress. We need to trigger the log क्रमce
	 * to pass through it's iclog state machine error handling, even though
	 * we are alपढ़ोy in a shutकरोwn state. Hence we can't वापस
	 * शून्यCOMMITLSN here as that has special meaning to log क्रमces (i.e.
	 * LSN is alपढ़ोy stable), so we वापस a zero LSN instead.
	 */
out_shutकरोwn:
	spin_unlock(&cil->xc_push_lock);
	वापस 0;
पूर्ण

/*
 * Check अगर the current log item was first committed in this sequence.
 * We can't rely on just the log item being in the CIL, we have to check
 * the recorded commit sequence number.
 *
 * Note: क्रम this to be used in a non-racy manner, it has to be called with
 * CIL flushing locked out. As a result, it should only be used during the
 * transaction commit process when deciding what to क्रमmat पूर्णांकo the item.
 */
bool
xfs_log_item_in_current_chkpt(
	काष्ठा xfs_log_item *lip)
अणु
	काष्ठा xfs_cil_ctx *ctx;

	अगर (list_empty(&lip->li_cil))
		वापस false;

	ctx = lip->li_mountp->m_log->l_cilp->xc_ctx;

	/*
	 * li_seq is written on the first commit of a log item to record the
	 * first checkpoपूर्णांक it is written to. Hence अगर it is dअगरferent to the
	 * current sequence, we're in a new checkpoपूर्णांक.
	 */
	अगर (XFS_LSN_CMP(lip->li_seq, ctx->sequence) != 0)
		वापस false;
	वापस true;
पूर्ण

/*
 * Perक्रमm initial CIL काष्ठाure initialisation.
 */
पूर्णांक
xlog_cil_init(
	काष्ठा xlog	*log)
अणु
	काष्ठा xfs_cil	*cil;
	काष्ठा xfs_cil_ctx *ctx;

	cil = kmem_zalloc(माप(*cil), KM_MAYFAIL);
	अगर (!cil)
		वापस -ENOMEM;

	ctx = kmem_zalloc(माप(*ctx), KM_MAYFAIL);
	अगर (!ctx) अणु
		kmem_मुक्त(cil);
		वापस -ENOMEM;
	पूर्ण

	INIT_WORK(&cil->xc_push_work, xlog_cil_push_work);
	INIT_LIST_HEAD(&cil->xc_cil);
	INIT_LIST_HEAD(&cil->xc_committing);
	spin_lock_init(&cil->xc_cil_lock);
	spin_lock_init(&cil->xc_push_lock);
	init_रुकोqueue_head(&cil->xc_push_रुको);
	init_rwsem(&cil->xc_ctx_lock);
	init_रुकोqueue_head(&cil->xc_commit_रुको);

	INIT_LIST_HEAD(&ctx->committing);
	INIT_LIST_HEAD(&ctx->busy_extents);
	ctx->sequence = 1;
	ctx->cil = cil;
	cil->xc_ctx = ctx;
	cil->xc_current_sequence = ctx->sequence;

	cil->xc_log = log;
	log->l_cilp = cil;
	वापस 0;
पूर्ण

व्योम
xlog_cil_destroy(
	काष्ठा xlog	*log)
अणु
	अगर (log->l_cilp->xc_ctx) अणु
		अगर (log->l_cilp->xc_ctx->ticket)
			xfs_log_ticket_put(log->l_cilp->xc_ctx->ticket);
		kmem_मुक्त(log->l_cilp->xc_ctx);
	पूर्ण

	ASSERT(list_empty(&log->l_cilp->xc_cil));
	kmem_मुक्त(log->l_cilp);
पूर्ण

