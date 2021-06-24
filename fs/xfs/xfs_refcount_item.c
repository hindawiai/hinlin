<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_refcount_item.h"
#समावेश "xfs_log.h"
#समावेश "xfs_refcount.h"
#समावेश "xfs_error.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_log_recover.h"

kmem_zone_t	*xfs_cui_zone;
kmem_zone_t	*xfs_cud_zone;

अटल स्थिर काष्ठा xfs_item_ops xfs_cui_item_ops;

अटल अंतरभूत काष्ठा xfs_cui_log_item *CUI_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_cui_log_item, cui_item);
पूर्ण

STATIC व्योम
xfs_cui_item_मुक्त(
	काष्ठा xfs_cui_log_item	*cuip)
अणु
	अगर (cuip->cui_क्रमmat.cui_nextents > XFS_CUI_MAX_FAST_EXTENTS)
		kmem_मुक्त(cuip);
	अन्यथा
		kmem_cache_मुक्त(xfs_cui_zone, cuip);
पूर्ण

/*
 * Freeing the CUI requires that we हटाओ it from the AIL अगर it has alपढ़ोy
 * been placed there. However, the CUI may not yet have been placed in the AIL
 * when called by xfs_cui_release() from CUD processing due to the ordering of
 * committed vs unpin operations in bulk insert operations. Hence the reference
 * count to ensure only the last caller मुक्तs the CUI.
 */
STATIC व्योम
xfs_cui_release(
	काष्ठा xfs_cui_log_item	*cuip)
अणु
	ASSERT(atomic_पढ़ो(&cuip->cui_refcount) > 0);
	अगर (atomic_dec_and_test(&cuip->cui_refcount)) अणु
		xfs_trans_ail_delete(&cuip->cui_item, SHUTDOWN_LOG_IO_ERROR);
		xfs_cui_item_मुक्त(cuip);
	पूर्ण
पूर्ण


STATIC व्योम
xfs_cui_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	काष्ठा xfs_cui_log_item	*cuip = CUI_ITEM(lip);

	*nvecs += 1;
	*nbytes += xfs_cui_log_क्रमmat_माप(cuip->cui_क्रमmat.cui_nextents);
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the
 * given cui log item. We use only 1 iovec, and we poपूर्णांक that
 * at the cui_log_क्रमmat काष्ठाure embedded in the cui item.
 * It is at this poपूर्णांक that we निश्चित that all of the extent
 * slots in the cui item have been filled.
 */
STATIC व्योम
xfs_cui_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_cui_log_item	*cuip = CUI_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;

	ASSERT(atomic_पढ़ो(&cuip->cui_next_extent) ==
			cuip->cui_क्रमmat.cui_nextents);

	cuip->cui_क्रमmat.cui_type = XFS_LI_CUI;
	cuip->cui_क्रमmat.cui_size = 1;

	xlog_copy_iovec(lv, &vecp, XLOG_REG_TYPE_CUI_FORMAT, &cuip->cui_क्रमmat,
			xfs_cui_log_क्रमmat_माप(cuip->cui_क्रमmat.cui_nextents));
पूर्ण

/*
 * The unpin operation is the last place an CUI is manipulated in the log. It is
 * either inserted in the AIL or पातed in the event of a log I/O error. In
 * either हाल, the CUI transaction has been successfully committed to make it
 * this far. Thereक्रमe, we expect whoever committed the CUI to either स्थिरruct
 * and commit the CUD or drop the CUD's reference in the event of error. Simply
 * drop the log's CUI reference now that the log is करोne with it.
 */
STATIC व्योम
xfs_cui_item_unpin(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			हटाओ)
अणु
	काष्ठा xfs_cui_log_item	*cuip = CUI_ITEM(lip);

	xfs_cui_release(cuip);
पूर्ण

/*
 * The CUI has been either committed or पातed अगर the transaction has been
 * cancelled. If the transaction was cancelled, an CUD isn't going to be
 * स्थिरructed and thus we मुक्त the CUI here directly.
 */
STATIC व्योम
xfs_cui_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	xfs_cui_release(CUI_ITEM(lip));
पूर्ण

/*
 * Allocate and initialize an cui item with the given number of extents.
 */
STATIC काष्ठा xfs_cui_log_item *
xfs_cui_init(
	काष्ठा xfs_mount		*mp,
	uपूर्णांक				nextents)

अणु
	काष्ठा xfs_cui_log_item		*cuip;

	ASSERT(nextents > 0);
	अगर (nextents > XFS_CUI_MAX_FAST_EXTENTS)
		cuip = kmem_zalloc(xfs_cui_log_item_माप(nextents),
				0);
	अन्यथा
		cuip = kmem_cache_zalloc(xfs_cui_zone,
					 GFP_KERNEL | __GFP_NOFAIL);

	xfs_log_item_init(mp, &cuip->cui_item, XFS_LI_CUI, &xfs_cui_item_ops);
	cuip->cui_क्रमmat.cui_nextents = nextents;
	cuip->cui_क्रमmat.cui_id = (uपूर्णांकptr_t)(व्योम *)cuip;
	atomic_set(&cuip->cui_next_extent, 0);
	atomic_set(&cuip->cui_refcount, 2);

	वापस cuip;
पूर्ण

अटल अंतरभूत काष्ठा xfs_cud_log_item *CUD_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_cud_log_item, cud_item);
पूर्ण

STATIC व्योम
xfs_cud_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	*nvecs += 1;
	*nbytes += माप(काष्ठा xfs_cud_log_क्रमmat);
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the
 * given cud log item. We use only 1 iovec, and we poपूर्णांक that
 * at the cud_log_क्रमmat काष्ठाure embedded in the cud item.
 * It is at this poपूर्णांक that we निश्चित that all of the extent
 * slots in the cud item have been filled.
 */
STATIC व्योम
xfs_cud_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_cud_log_item	*cudp = CUD_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;

	cudp->cud_क्रमmat.cud_type = XFS_LI_CUD;
	cudp->cud_क्रमmat.cud_size = 1;

	xlog_copy_iovec(lv, &vecp, XLOG_REG_TYPE_CUD_FORMAT, &cudp->cud_क्रमmat,
			माप(काष्ठा xfs_cud_log_क्रमmat));
पूर्ण

/*
 * The CUD is either committed or पातed अगर the transaction is cancelled. If
 * the transaction is cancelled, drop our reference to the CUI and मुक्त the
 * CUD.
 */
STATIC व्योम
xfs_cud_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_cud_log_item	*cudp = CUD_ITEM(lip);

	xfs_cui_release(cudp->cud_cuip);
	kmem_cache_मुक्त(xfs_cud_zone, cudp);
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_cud_item_ops = अणु
	.flags		= XFS_ITEM_RELEASE_WHEN_COMMITTED,
	.iop_size	= xfs_cud_item_size,
	.iop_क्रमmat	= xfs_cud_item_क्रमmat,
	.iop_release	= xfs_cud_item_release,
पूर्ण;

अटल काष्ठा xfs_cud_log_item *
xfs_trans_get_cud(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_cui_log_item		*cuip)
अणु
	काष्ठा xfs_cud_log_item		*cudp;

	cudp = kmem_cache_zalloc(xfs_cud_zone, GFP_KERNEL | __GFP_NOFAIL);
	xfs_log_item_init(tp->t_mountp, &cudp->cud_item, XFS_LI_CUD,
			  &xfs_cud_item_ops);
	cudp->cud_cuip = cuip;
	cudp->cud_क्रमmat.cud_cui_id = cuip->cui_क्रमmat.cui_id;

	xfs_trans_add_item(tp, &cudp->cud_item);
	वापस cudp;
पूर्ण

/*
 * Finish an refcount update and log it to the CUD. Note that the
 * transaction is marked dirty regardless of whether the refcount
 * update succeeds or fails to support the CUI/CUD lअगरecycle rules.
 */
अटल पूर्णांक
xfs_trans_log_finish_refcount_update(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_cud_log_item		*cudp,
	क्रमागत xfs_refcount_पूर्णांकent_type	type,
	xfs_fsblock_t			startblock,
	xfs_extlen_t			blockcount,
	xfs_fsblock_t			*new_fsb,
	xfs_extlen_t			*new_len,
	काष्ठा xfs_btree_cur		**pcur)
अणु
	पूर्णांक				error;

	error = xfs_refcount_finish_one(tp, type, startblock,
			blockcount, new_fsb, new_len, pcur);

	/*
	 * Mark the transaction dirty, even on error. This ensures the
	 * transaction is पातed, which:
	 *
	 * 1.) releases the CUI and मुक्तs the CUD
	 * 2.) shuts करोwn the fileप्रणाली
	 */
	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &cudp->cud_item.li_flags);

	वापस error;
पूर्ण

/* Sort refcount पूर्णांकents by AG. */
अटल पूर्णांक
xfs_refcount_update_dअगरf_items(
	व्योम				*priv,
	स्थिर काष्ठा list_head		*a,
	स्थिर काष्ठा list_head		*b)
अणु
	काष्ठा xfs_mount		*mp = priv;
	काष्ठा xfs_refcount_पूर्णांकent	*ra;
	काष्ठा xfs_refcount_पूर्णांकent	*rb;

	ra = container_of(a, काष्ठा xfs_refcount_पूर्णांकent, ri_list);
	rb = container_of(b, काष्ठा xfs_refcount_पूर्णांकent, ri_list);
	वापस  XFS_FSB_TO_AGNO(mp, ra->ri_startblock) -
		XFS_FSB_TO_AGNO(mp, rb->ri_startblock);
पूर्ण

/* Set the phys extent flags क्रम this reverse mapping. */
अटल व्योम
xfs_trans_set_refcount_flags(
	काष्ठा xfs_phys_extent		*refc,
	क्रमागत xfs_refcount_पूर्णांकent_type	type)
अणु
	refc->pe_flags = 0;
	चयन (type) अणु
	हाल XFS_REFCOUNT_INCREASE:
	हाल XFS_REFCOUNT_DECREASE:
	हाल XFS_REFCOUNT_ALLOC_COW:
	हाल XFS_REFCOUNT_FREE_COW:
		refc->pe_flags |= type;
		अवरोध;
	शेष:
		ASSERT(0);
	पूर्ण
पूर्ण

/* Log refcount updates in the पूर्णांकent item. */
STATIC व्योम
xfs_refcount_update_log_item(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_cui_log_item		*cuip,
	काष्ठा xfs_refcount_पूर्णांकent	*refc)
अणु
	uपूर्णांक				next_extent;
	काष्ठा xfs_phys_extent		*ext;

	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &cuip->cui_item.li_flags);

	/*
	 * atomic_inc_वापस gives us the value after the increment;
	 * we want to use it as an array index so we need to subtract 1 from
	 * it.
	 */
	next_extent = atomic_inc_वापस(&cuip->cui_next_extent) - 1;
	ASSERT(next_extent < cuip->cui_क्रमmat.cui_nextents);
	ext = &cuip->cui_क्रमmat.cui_extents[next_extent];
	ext->pe_startblock = refc->ri_startblock;
	ext->pe_len = refc->ri_blockcount;
	xfs_trans_set_refcount_flags(ext, refc->ri_type);
पूर्ण

अटल काष्ठा xfs_log_item *
xfs_refcount_update_create_पूर्णांकent(
	काष्ठा xfs_trans		*tp,
	काष्ठा list_head		*items,
	अचिन्हित पूर्णांक			count,
	bool				sort)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_cui_log_item		*cuip = xfs_cui_init(mp, count);
	काष्ठा xfs_refcount_पूर्णांकent	*refc;

	ASSERT(count > 0);

	xfs_trans_add_item(tp, &cuip->cui_item);
	अगर (sort)
		list_sort(mp, items, xfs_refcount_update_dअगरf_items);
	list_क्रम_each_entry(refc, items, ri_list)
		xfs_refcount_update_log_item(tp, cuip, refc);
	वापस &cuip->cui_item;
पूर्ण

/* Get an CUD so we can process all the deferred refcount updates. */
अटल काष्ठा xfs_log_item *
xfs_refcount_update_create_करोne(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_log_item		*पूर्णांकent,
	अचिन्हित पूर्णांक			count)
अणु
	वापस &xfs_trans_get_cud(tp, CUI_ITEM(पूर्णांकent))->cud_item;
पूर्ण

/* Process a deferred refcount update. */
STATIC पूर्णांक
xfs_refcount_update_finish_item(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_log_item		*करोne,
	काष्ठा list_head		*item,
	काष्ठा xfs_btree_cur		**state)
अणु
	काष्ठा xfs_refcount_पूर्णांकent	*refc;
	xfs_fsblock_t			new_fsb;
	xfs_extlen_t			new_aglen;
	पूर्णांक				error;

	refc = container_of(item, काष्ठा xfs_refcount_पूर्णांकent, ri_list);
	error = xfs_trans_log_finish_refcount_update(tp, CUD_ITEM(करोne),
			refc->ri_type, refc->ri_startblock, refc->ri_blockcount,
			&new_fsb, &new_aglen, state);

	/* Did we run out of reservation?  Requeue what we didn't finish. */
	अगर (!error && new_aglen > 0) अणु
		ASSERT(refc->ri_type == XFS_REFCOUNT_INCREASE ||
		       refc->ri_type == XFS_REFCOUNT_DECREASE);
		refc->ri_startblock = new_fsb;
		refc->ri_blockcount = new_aglen;
		वापस -EAGAIN;
	पूर्ण
	kmem_मुक्त(refc);
	वापस error;
पूर्ण

/* Abort all pending CUIs. */
STATIC व्योम
xfs_refcount_update_पात_पूर्णांकent(
	काष्ठा xfs_log_item		*पूर्णांकent)
अणु
	xfs_cui_release(CUI_ITEM(पूर्णांकent));
पूर्ण

/* Cancel a deferred refcount update. */
STATIC व्योम
xfs_refcount_update_cancel_item(
	काष्ठा list_head		*item)
अणु
	काष्ठा xfs_refcount_पूर्णांकent	*refc;

	refc = container_of(item, काष्ठा xfs_refcount_पूर्णांकent, ri_list);
	kmem_मुक्त(refc);
पूर्ण

स्थिर काष्ठा xfs_defer_op_type xfs_refcount_update_defer_type = अणु
	.max_items	= XFS_CUI_MAX_FAST_EXTENTS,
	.create_पूर्णांकent	= xfs_refcount_update_create_पूर्णांकent,
	.पात_पूर्णांकent	= xfs_refcount_update_पात_पूर्णांकent,
	.create_करोne	= xfs_refcount_update_create_करोne,
	.finish_item	= xfs_refcount_update_finish_item,
	.finish_cleanup = xfs_refcount_finish_one_cleanup,
	.cancel_item	= xfs_refcount_update_cancel_item,
पूर्ण;

/* Is this recovered CUI ok? */
अटल अंतरभूत bool
xfs_cui_validate_phys(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_phys_extent		*refc)
अणु
	अगर (!xfs_sb_version_hasreflink(&mp->m_sb))
		वापस false;

	अगर (refc->pe_flags & ~XFS_REFCOUNT_EXTENT_FLAGS)
		वापस false;

	चयन (refc->pe_flags & XFS_REFCOUNT_EXTENT_TYPE_MASK) अणु
	हाल XFS_REFCOUNT_INCREASE:
	हाल XFS_REFCOUNT_DECREASE:
	हाल XFS_REFCOUNT_ALLOC_COW:
	हाल XFS_REFCOUNT_FREE_COW:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस xfs_verअगरy_fsbext(mp, refc->pe_startblock, refc->pe_len);
पूर्ण

/*
 * Process a refcount update पूर्णांकent item that was recovered from the log.
 * We need to update the refcountbt.
 */
STATIC पूर्णांक
xfs_cui_item_recover(
	काष्ठा xfs_log_item		*lip,
	काष्ठा list_head		*capture_list)
अणु
	काष्ठा xfs_bmbt_irec		irec;
	काष्ठा xfs_cui_log_item		*cuip = CUI_ITEM(lip);
	काष्ठा xfs_phys_extent		*refc;
	काष्ठा xfs_cud_log_item		*cudp;
	काष्ठा xfs_trans		*tp;
	काष्ठा xfs_btree_cur		*rcur = शून्य;
	काष्ठा xfs_mount		*mp = lip->li_mountp;
	xfs_fsblock_t			new_fsb;
	xfs_extlen_t			new_len;
	अचिन्हित पूर्णांक			refc_type;
	bool				requeue_only = false;
	क्रमागत xfs_refcount_पूर्णांकent_type	type;
	पूर्णांक				i;
	पूर्णांक				error = 0;

	/*
	 * First check the validity of the extents described by the
	 * CUI.  If any are bad, then assume that all are bad and
	 * just toss the CUI.
	 */
	क्रम (i = 0; i < cuip->cui_क्रमmat.cui_nextents; i++) अणु
		अगर (!xfs_cui_validate_phys(mp,
					&cuip->cui_क्रमmat.cui_extents[i])) अणु
			XFS_CORRUPTION_ERROR(__func__, XFS_ERRLEVEL_LOW, mp,
					&cuip->cui_क्रमmat,
					माप(cuip->cui_क्रमmat));
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण

	/*
	 * Under normal operation, refcount updates are deferred, so we
	 * wouldn't be adding them directly to a transaction.  All
	 * refcount updates manage reservation usage पूर्णांकernally and
	 * dynamically by deferring work that won't fit in the
	 * transaction.  Normally, any work that needs to be deferred
	 * माला_लो attached to the same defer_ops that scheduled the
	 * refcount update.  However, we're in log recovery here, so we
	 * use the passed in defer_ops and to finish up any work that
	 * करोesn't fit.  We need to reserve enough blocks to handle a
	 * full btree split on either end of the refcount range.
	 */
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate,
			mp->m_refc_maxlevels * 2, 0, XFS_TRANS_RESERVE, &tp);
	अगर (error)
		वापस error;

	cudp = xfs_trans_get_cud(tp, cuip);

	क्रम (i = 0; i < cuip->cui_क्रमmat.cui_nextents; i++) अणु
		refc = &cuip->cui_क्रमmat.cui_extents[i];
		refc_type = refc->pe_flags & XFS_REFCOUNT_EXTENT_TYPE_MASK;
		चयन (refc_type) अणु
		हाल XFS_REFCOUNT_INCREASE:
		हाल XFS_REFCOUNT_DECREASE:
		हाल XFS_REFCOUNT_ALLOC_COW:
		हाल XFS_REFCOUNT_FREE_COW:
			type = refc_type;
			अवरोध;
		शेष:
			XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, mp);
			error = -EFSCORRUPTED;
			जाओ पात_error;
		पूर्ण
		अगर (requeue_only) अणु
			new_fsb = refc->pe_startblock;
			new_len = refc->pe_len;
		पूर्ण अन्यथा
			error = xfs_trans_log_finish_refcount_update(tp, cudp,
				type, refc->pe_startblock, refc->pe_len,
				&new_fsb, &new_len, &rcur);
		अगर (error)
			जाओ पात_error;

		/* Requeue what we didn't finish. */
		अगर (new_len > 0) अणु
			irec.br_startblock = new_fsb;
			irec.br_blockcount = new_len;
			चयन (type) अणु
			हाल XFS_REFCOUNT_INCREASE:
				xfs_refcount_increase_extent(tp, &irec);
				अवरोध;
			हाल XFS_REFCOUNT_DECREASE:
				xfs_refcount_decrease_extent(tp, &irec);
				अवरोध;
			हाल XFS_REFCOUNT_ALLOC_COW:
				xfs_refcount_alloc_cow_extent(tp,
						irec.br_startblock,
						irec.br_blockcount);
				अवरोध;
			हाल XFS_REFCOUNT_FREE_COW:
				xfs_refcount_मुक्त_cow_extent(tp,
						irec.br_startblock,
						irec.br_blockcount);
				अवरोध;
			शेष:
				ASSERT(0);
			पूर्ण
			requeue_only = true;
		पूर्ण
	पूर्ण

	xfs_refcount_finish_one_cleanup(tp, rcur, error);
	वापस xfs_defer_ops_capture_and_commit(tp, शून्य, capture_list);

पात_error:
	xfs_refcount_finish_one_cleanup(tp, rcur, error);
	xfs_trans_cancel(tp);
	वापस error;
पूर्ण

STATIC bool
xfs_cui_item_match(
	काष्ठा xfs_log_item	*lip,
	uपूर्णांक64_t		पूर्णांकent_id)
अणु
	वापस CUI_ITEM(lip)->cui_क्रमmat.cui_id == पूर्णांकent_id;
पूर्ण

/* Relog an पूर्णांकent item to push the log tail क्रमward. */
अटल काष्ठा xfs_log_item *
xfs_cui_item_relog(
	काष्ठा xfs_log_item		*पूर्णांकent,
	काष्ठा xfs_trans		*tp)
अणु
	काष्ठा xfs_cud_log_item		*cudp;
	काष्ठा xfs_cui_log_item		*cuip;
	काष्ठा xfs_phys_extent		*extp;
	अचिन्हित पूर्णांक			count;

	count = CUI_ITEM(पूर्णांकent)->cui_क्रमmat.cui_nextents;
	extp = CUI_ITEM(पूर्णांकent)->cui_क्रमmat.cui_extents;

	tp->t_flags |= XFS_TRANS_सूचीTY;
	cudp = xfs_trans_get_cud(tp, CUI_ITEM(पूर्णांकent));
	set_bit(XFS_LI_सूचीTY, &cudp->cud_item.li_flags);

	cuip = xfs_cui_init(tp->t_mountp, count);
	स_नकल(cuip->cui_क्रमmat.cui_extents, extp, count * माप(*extp));
	atomic_set(&cuip->cui_next_extent, count);
	xfs_trans_add_item(tp, &cuip->cui_item);
	set_bit(XFS_LI_सूचीTY, &cuip->cui_item.li_flags);
	वापस &cuip->cui_item;
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_cui_item_ops = अणु
	.iop_size	= xfs_cui_item_size,
	.iop_क्रमmat	= xfs_cui_item_क्रमmat,
	.iop_unpin	= xfs_cui_item_unpin,
	.iop_release	= xfs_cui_item_release,
	.iop_recover	= xfs_cui_item_recover,
	.iop_match	= xfs_cui_item_match,
	.iop_relog	= xfs_cui_item_relog,
पूर्ण;

/*
 * Copy an CUI क्रमmat buffer from the given buf, and पूर्णांकo the destination
 * CUI क्रमmat काष्ठाure.  The CUI/CUD items were deचिन्हित not to need any
 * special alignment handling.
 */
अटल पूर्णांक
xfs_cui_copy_क्रमmat(
	काष्ठा xfs_log_iovec		*buf,
	काष्ठा xfs_cui_log_क्रमmat	*dst_cui_fmt)
अणु
	काष्ठा xfs_cui_log_क्रमmat	*src_cui_fmt;
	uपूर्णांक				len;

	src_cui_fmt = buf->i_addr;
	len = xfs_cui_log_क्रमmat_माप(src_cui_fmt->cui_nextents);

	अगर (buf->i_len == len) अणु
		स_नकल(dst_cui_fmt, src_cui_fmt, len);
		वापस 0;
	पूर्ण
	XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, शून्य);
	वापस -EFSCORRUPTED;
पूर्ण

/*
 * This routine is called to create an in-core extent refcount update
 * item from the cui क्रमmat काष्ठाure which was logged on disk.
 * It allocates an in-core cui, copies the extents from the क्रमmat
 * काष्ठाure पूर्णांकo it, and adds the cui to the AIL with the given
 * LSN.
 */
STATIC पूर्णांक
xlog_recover_cui_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			lsn)
अणु
	पूर्णांक				error;
	काष्ठा xfs_mount		*mp = log->l_mp;
	काष्ठा xfs_cui_log_item		*cuip;
	काष्ठा xfs_cui_log_क्रमmat	*cui_क्रमmatp;

	cui_क्रमmatp = item->ri_buf[0].i_addr;

	cuip = xfs_cui_init(mp, cui_क्रमmatp->cui_nextents);
	error = xfs_cui_copy_क्रमmat(&item->ri_buf[0], &cuip->cui_क्रमmat);
	अगर (error) अणु
		xfs_cui_item_मुक्त(cuip);
		वापस error;
	पूर्ण
	atomic_set(&cuip->cui_next_extent, cui_क्रमmatp->cui_nextents);
	/*
	 * Insert the पूर्णांकent पूर्णांकo the AIL directly and drop one reference so
	 * that finishing or canceling the work will drop the other.
	 */
	xfs_trans_ail_insert(log->l_ailp, &cuip->cui_item, lsn);
	xfs_cui_release(cuip);
	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_cui_item_ops = अणु
	.item_type		= XFS_LI_CUI,
	.commit_pass2		= xlog_recover_cui_commit_pass2,
पूर्ण;

/*
 * This routine is called when an CUD क्रमmat काष्ठाure is found in a committed
 * transaction in the log. Its purpose is to cancel the corresponding CUI अगर it
 * was still in the log. To करो this it searches the AIL क्रम the CUI with an id
 * equal to that in the CUD क्रमmat काष्ठाure. If we find it we drop the CUD
 * reference, which हटाओs the CUI from the AIL and मुक्तs it.
 */
STATIC पूर्णांक
xlog_recover_cud_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			lsn)
अणु
	काष्ठा xfs_cud_log_क्रमmat	*cud_क्रमmatp;

	cud_क्रमmatp = item->ri_buf[0].i_addr;
	अगर (item->ri_buf[0].i_len != माप(काष्ठा xfs_cud_log_क्रमmat)) अणु
		XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, log->l_mp);
		वापस -EFSCORRUPTED;
	पूर्ण

	xlog_recover_release_पूर्णांकent(log, XFS_LI_CUI, cud_क्रमmatp->cud_cui_id);
	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_cud_item_ops = अणु
	.item_type		= XFS_LI_CUD,
	.commit_pass2		= xlog_recover_cud_commit_pass2,
पूर्ण;
