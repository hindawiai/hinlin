<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
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
#समावेश "xfs_extfree_item.h"
#समावेश "xfs_log.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_error.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_log_recover.h"

kmem_zone_t	*xfs_efi_zone;
kmem_zone_t	*xfs_efd_zone;

अटल स्थिर काष्ठा xfs_item_ops xfs_efi_item_ops;

अटल अंतरभूत काष्ठा xfs_efi_log_item *EFI_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_efi_log_item, efi_item);
पूर्ण

STATIC व्योम
xfs_efi_item_मुक्त(
	काष्ठा xfs_efi_log_item	*efip)
अणु
	kmem_मुक्त(efip->efi_item.li_lv_shaकरोw);
	अगर (efip->efi_क्रमmat.efi_nextents > XFS_EFI_MAX_FAST_EXTENTS)
		kmem_मुक्त(efip);
	अन्यथा
		kmem_cache_मुक्त(xfs_efi_zone, efip);
पूर्ण

/*
 * Freeing the efi requires that we हटाओ it from the AIL अगर it has alपढ़ोy
 * been placed there. However, the EFI may not yet have been placed in the AIL
 * when called by xfs_efi_release() from EFD processing due to the ordering of
 * committed vs unpin operations in bulk insert operations. Hence the reference
 * count to ensure only the last caller मुक्तs the EFI.
 */
STATIC व्योम
xfs_efi_release(
	काष्ठा xfs_efi_log_item	*efip)
अणु
	ASSERT(atomic_पढ़ो(&efip->efi_refcount) > 0);
	अगर (atomic_dec_and_test(&efip->efi_refcount)) अणु
		xfs_trans_ail_delete(&efip->efi_item, SHUTDOWN_LOG_IO_ERROR);
		xfs_efi_item_मुक्त(efip);
	पूर्ण
पूर्ण

/*
 * This वापसs the number of iovecs needed to log the given efi item.
 * We only need 1 iovec क्रम an efi item.  It just logs the efi_log_क्रमmat
 * काष्ठाure.
 */
अटल अंतरभूत पूर्णांक
xfs_efi_item_माप(
	काष्ठा xfs_efi_log_item *efip)
अणु
	वापस माप(काष्ठा xfs_efi_log_क्रमmat) +
	       (efip->efi_क्रमmat.efi_nextents - 1) * माप(xfs_extent_t);
पूर्ण

STATIC व्योम
xfs_efi_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	*nvecs += 1;
	*nbytes += xfs_efi_item_माप(EFI_ITEM(lip));
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the
 * given efi log item. We use only 1 iovec, and we poपूर्णांक that
 * at the efi_log_क्रमmat काष्ठाure embedded in the efi item.
 * It is at this poपूर्णांक that we निश्चित that all of the extent
 * slots in the efi item have been filled.
 */
STATIC व्योम
xfs_efi_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_efi_log_item	*efip = EFI_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;

	ASSERT(atomic_पढ़ो(&efip->efi_next_extent) ==
				efip->efi_क्रमmat.efi_nextents);

	efip->efi_क्रमmat.efi_type = XFS_LI_EFI;
	efip->efi_क्रमmat.efi_size = 1;

	xlog_copy_iovec(lv, &vecp, XLOG_REG_TYPE_EFI_FORMAT,
			&efip->efi_क्रमmat,
			xfs_efi_item_माप(efip));
पूर्ण


/*
 * The unpin operation is the last place an EFI is manipulated in the log. It is
 * either inserted in the AIL or पातed in the event of a log I/O error. In
 * either हाल, the EFI transaction has been successfully committed to make it
 * this far. Thereक्रमe, we expect whoever committed the EFI to either स्थिरruct
 * and commit the EFD or drop the EFD's reference in the event of error. Simply
 * drop the log's EFI reference now that the log is करोne with it.
 */
STATIC व्योम
xfs_efi_item_unpin(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			हटाओ)
अणु
	काष्ठा xfs_efi_log_item	*efip = EFI_ITEM(lip);
	xfs_efi_release(efip);
पूर्ण

/*
 * The EFI has been either committed or पातed अगर the transaction has been
 * cancelled. If the transaction was cancelled, an EFD isn't going to be
 * स्थिरructed and thus we मुक्त the EFI here directly.
 */
STATIC व्योम
xfs_efi_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	xfs_efi_release(EFI_ITEM(lip));
पूर्ण

/*
 * Allocate and initialize an efi item with the given number of extents.
 */
STATIC काष्ठा xfs_efi_log_item *
xfs_efi_init(
	काष्ठा xfs_mount	*mp,
	uपूर्णांक			nextents)

अणु
	काष्ठा xfs_efi_log_item	*efip;
	uपूर्णांक			size;

	ASSERT(nextents > 0);
	अगर (nextents > XFS_EFI_MAX_FAST_EXTENTS) अणु
		size = (uपूर्णांक)(माप(काष्ठा xfs_efi_log_item) +
			((nextents - 1) * माप(xfs_extent_t)));
		efip = kmem_zalloc(size, 0);
	पूर्ण अन्यथा अणु
		efip = kmem_cache_zalloc(xfs_efi_zone,
					 GFP_KERNEL | __GFP_NOFAIL);
	पूर्ण

	xfs_log_item_init(mp, &efip->efi_item, XFS_LI_EFI, &xfs_efi_item_ops);
	efip->efi_क्रमmat.efi_nextents = nextents;
	efip->efi_क्रमmat.efi_id = (uपूर्णांकptr_t)(व्योम *)efip;
	atomic_set(&efip->efi_next_extent, 0);
	atomic_set(&efip->efi_refcount, 2);

	वापस efip;
पूर्ण

/*
 * Copy an EFI क्रमmat buffer from the given buf, and पूर्णांकo the destination
 * EFI क्रमmat काष्ठाure.
 * The given buffer can be in 32 bit or 64 bit क्रमm (which has dअगरferent padding),
 * one of which will be the native क्रमmat क्रम this kernel.
 * It will handle the conversion of क्रमmats अगर necessary.
 */
STATIC पूर्णांक
xfs_efi_copy_क्रमmat(xfs_log_iovec_t *buf, xfs_efi_log_क्रमmat_t *dst_efi_fmt)
अणु
	xfs_efi_log_क्रमmat_t *src_efi_fmt = buf->i_addr;
	uपूर्णांक i;
	uपूर्णांक len = माप(xfs_efi_log_क्रमmat_t) + 
		(src_efi_fmt->efi_nextents - 1) * माप(xfs_extent_t);  
	uपूर्णांक len32 = माप(xfs_efi_log_क्रमmat_32_t) + 
		(src_efi_fmt->efi_nextents - 1) * माप(xfs_extent_32_t);  
	uपूर्णांक len64 = माप(xfs_efi_log_क्रमmat_64_t) + 
		(src_efi_fmt->efi_nextents - 1) * माप(xfs_extent_64_t);  

	अगर (buf->i_len == len) अणु
		स_नकल((अक्षर *)dst_efi_fmt, (अक्षर*)src_efi_fmt, len);
		वापस 0;
	पूर्ण अन्यथा अगर (buf->i_len == len32) अणु
		xfs_efi_log_क्रमmat_32_t *src_efi_fmt_32 = buf->i_addr;

		dst_efi_fmt->efi_type     = src_efi_fmt_32->efi_type;
		dst_efi_fmt->efi_size     = src_efi_fmt_32->efi_size;
		dst_efi_fmt->efi_nextents = src_efi_fmt_32->efi_nextents;
		dst_efi_fmt->efi_id       = src_efi_fmt_32->efi_id;
		क्रम (i = 0; i < dst_efi_fmt->efi_nextents; i++) अणु
			dst_efi_fmt->efi_extents[i].ext_start =
				src_efi_fmt_32->efi_extents[i].ext_start;
			dst_efi_fmt->efi_extents[i].ext_len =
				src_efi_fmt_32->efi_extents[i].ext_len;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अगर (buf->i_len == len64) अणु
		xfs_efi_log_क्रमmat_64_t *src_efi_fmt_64 = buf->i_addr;

		dst_efi_fmt->efi_type     = src_efi_fmt_64->efi_type;
		dst_efi_fmt->efi_size     = src_efi_fmt_64->efi_size;
		dst_efi_fmt->efi_nextents = src_efi_fmt_64->efi_nextents;
		dst_efi_fmt->efi_id       = src_efi_fmt_64->efi_id;
		क्रम (i = 0; i < dst_efi_fmt->efi_nextents; i++) अणु
			dst_efi_fmt->efi_extents[i].ext_start =
				src_efi_fmt_64->efi_extents[i].ext_start;
			dst_efi_fmt->efi_extents[i].ext_len =
				src_efi_fmt_64->efi_extents[i].ext_len;
		पूर्ण
		वापस 0;
	पूर्ण
	XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, शून्य);
	वापस -EFSCORRUPTED;
पूर्ण

अटल अंतरभूत काष्ठा xfs_efd_log_item *EFD_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_efd_log_item, efd_item);
पूर्ण

STATIC व्योम
xfs_efd_item_मुक्त(काष्ठा xfs_efd_log_item *efdp)
अणु
	kmem_मुक्त(efdp->efd_item.li_lv_shaकरोw);
	अगर (efdp->efd_क्रमmat.efd_nextents > XFS_EFD_MAX_FAST_EXTENTS)
		kmem_मुक्त(efdp);
	अन्यथा
		kmem_cache_मुक्त(xfs_efd_zone, efdp);
पूर्ण

/*
 * This वापसs the number of iovecs needed to log the given efd item.
 * We only need 1 iovec क्रम an efd item.  It just logs the efd_log_क्रमmat
 * काष्ठाure.
 */
अटल अंतरभूत पूर्णांक
xfs_efd_item_माप(
	काष्ठा xfs_efd_log_item *efdp)
अणु
	वापस माप(xfs_efd_log_क्रमmat_t) +
	       (efdp->efd_क्रमmat.efd_nextents - 1) * माप(xfs_extent_t);
पूर्ण

STATIC व्योम
xfs_efd_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	*nvecs += 1;
	*nbytes += xfs_efd_item_माप(EFD_ITEM(lip));
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the
 * given efd log item. We use only 1 iovec, and we poपूर्णांक that
 * at the efd_log_क्रमmat काष्ठाure embedded in the efd item.
 * It is at this poपूर्णांक that we निश्चित that all of the extent
 * slots in the efd item have been filled.
 */
STATIC व्योम
xfs_efd_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_efd_log_item	*efdp = EFD_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;

	ASSERT(efdp->efd_next_extent == efdp->efd_क्रमmat.efd_nextents);

	efdp->efd_क्रमmat.efd_type = XFS_LI_EFD;
	efdp->efd_क्रमmat.efd_size = 1;

	xlog_copy_iovec(lv, &vecp, XLOG_REG_TYPE_EFD_FORMAT,
			&efdp->efd_क्रमmat,
			xfs_efd_item_माप(efdp));
पूर्ण

/*
 * The EFD is either committed or पातed अगर the transaction is cancelled. If
 * the transaction is cancelled, drop our reference to the EFI and मुक्त the EFD.
 */
STATIC व्योम
xfs_efd_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_efd_log_item	*efdp = EFD_ITEM(lip);

	xfs_efi_release(efdp->efd_efip);
	xfs_efd_item_मुक्त(efdp);
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_efd_item_ops = अणु
	.flags		= XFS_ITEM_RELEASE_WHEN_COMMITTED,
	.iop_size	= xfs_efd_item_size,
	.iop_क्रमmat	= xfs_efd_item_क्रमmat,
	.iop_release	= xfs_efd_item_release,
पूर्ण;

/*
 * Allocate an "extent free done" log item that will hold nextents worth of
 * extents.  The caller must use all nextents extents, because we are not
 * flexible about this at all.
 */
अटल काष्ठा xfs_efd_log_item *
xfs_trans_get_efd(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_efi_log_item		*efip,
	अचिन्हित पूर्णांक			nextents)
अणु
	काष्ठा xfs_efd_log_item		*efdp;

	ASSERT(nextents > 0);

	अगर (nextents > XFS_EFD_MAX_FAST_EXTENTS) अणु
		efdp = kmem_zalloc(माप(काष्ठा xfs_efd_log_item) +
				(nextents - 1) * माप(काष्ठा xfs_extent),
				0);
	पूर्ण अन्यथा अणु
		efdp = kmem_cache_zalloc(xfs_efd_zone,
					GFP_KERNEL | __GFP_NOFAIL);
	पूर्ण

	xfs_log_item_init(tp->t_mountp, &efdp->efd_item, XFS_LI_EFD,
			  &xfs_efd_item_ops);
	efdp->efd_efip = efip;
	efdp->efd_क्रमmat.efd_nextents = nextents;
	efdp->efd_क्रमmat.efd_efi_id = efip->efi_क्रमmat.efi_id;

	xfs_trans_add_item(tp, &efdp->efd_item);
	वापस efdp;
पूर्ण

/*
 * Free an extent and log it to the EFD. Note that the transaction is marked
 * dirty regardless of whether the extent मुक्त succeeds or fails to support the
 * EFI/EFD lअगरecycle rules.
 */
अटल पूर्णांक
xfs_trans_मुक्त_extent(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_efd_log_item		*efdp,
	xfs_fsblock_t			start_block,
	xfs_extlen_t			ext_len,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	bool				skip_discard)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_extent		*extp;
	uपूर्णांक				next_extent;
	xfs_agnumber_t			agno = XFS_FSB_TO_AGNO(mp, start_block);
	xfs_agblock_t			agbno = XFS_FSB_TO_AGBNO(mp,
								start_block);
	पूर्णांक				error;

	trace_xfs_bmap_मुक्त_deferred(tp->t_mountp, agno, 0, agbno, ext_len);

	error = __xfs_मुक्त_extent(tp, start_block, ext_len,
				  oinfo, XFS_AG_RESV_NONE, skip_discard);
	/*
	 * Mark the transaction dirty, even on error. This ensures the
	 * transaction is पातed, which:
	 *
	 * 1.) releases the EFI and मुक्तs the EFD
	 * 2.) shuts करोwn the fileप्रणाली
	 */
	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &efdp->efd_item.li_flags);

	next_extent = efdp->efd_next_extent;
	ASSERT(next_extent < efdp->efd_क्रमmat.efd_nextents);
	extp = &(efdp->efd_क्रमmat.efd_extents[next_extent]);
	extp->ext_start = start_block;
	extp->ext_len = ext_len;
	efdp->efd_next_extent++;

	वापस error;
पूर्ण

/* Sort bmap items by AG. */
अटल पूर्णांक
xfs_extent_मुक्त_dअगरf_items(
	व्योम				*priv,
	स्थिर काष्ठा list_head		*a,
	स्थिर काष्ठा list_head		*b)
अणु
	काष्ठा xfs_mount		*mp = priv;
	काष्ठा xfs_extent_मुक्त_item	*ra;
	काष्ठा xfs_extent_मुक्त_item	*rb;

	ra = container_of(a, काष्ठा xfs_extent_मुक्त_item, xefi_list);
	rb = container_of(b, काष्ठा xfs_extent_मुक्त_item, xefi_list);
	वापस  XFS_FSB_TO_AGNO(mp, ra->xefi_startblock) -
		XFS_FSB_TO_AGNO(mp, rb->xefi_startblock);
पूर्ण

/* Log a मुक्त extent to the पूर्णांकent item. */
STATIC व्योम
xfs_extent_मुक्त_log_item(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_efi_log_item		*efip,
	काष्ठा xfs_extent_मुक्त_item	*मुक्त)
अणु
	uपूर्णांक				next_extent;
	काष्ठा xfs_extent		*extp;

	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &efip->efi_item.li_flags);

	/*
	 * atomic_inc_वापस gives us the value after the increment;
	 * we want to use it as an array index so we need to subtract 1 from
	 * it.
	 */
	next_extent = atomic_inc_वापस(&efip->efi_next_extent) - 1;
	ASSERT(next_extent < efip->efi_क्रमmat.efi_nextents);
	extp = &efip->efi_क्रमmat.efi_extents[next_extent];
	extp->ext_start = मुक्त->xefi_startblock;
	extp->ext_len = मुक्त->xefi_blockcount;
पूर्ण

अटल काष्ठा xfs_log_item *
xfs_extent_मुक्त_create_पूर्णांकent(
	काष्ठा xfs_trans		*tp,
	काष्ठा list_head		*items,
	अचिन्हित पूर्णांक			count,
	bool				sort)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_efi_log_item		*efip = xfs_efi_init(mp, count);
	काष्ठा xfs_extent_मुक्त_item	*मुक्त;

	ASSERT(count > 0);

	xfs_trans_add_item(tp, &efip->efi_item);
	अगर (sort)
		list_sort(mp, items, xfs_extent_मुक्त_dअगरf_items);
	list_क्रम_each_entry(मुक्त, items, xefi_list)
		xfs_extent_मुक्त_log_item(tp, efip, मुक्त);
	वापस &efip->efi_item;
पूर्ण

/* Get an EFD so we can process all the मुक्त extents. */
अटल काष्ठा xfs_log_item *
xfs_extent_मुक्त_create_करोne(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_log_item		*पूर्णांकent,
	अचिन्हित पूर्णांक			count)
अणु
	वापस &xfs_trans_get_efd(tp, EFI_ITEM(पूर्णांकent), count)->efd_item;
पूर्ण

/* Process a मुक्त extent. */
STATIC पूर्णांक
xfs_extent_मुक्त_finish_item(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_log_item		*करोne,
	काष्ठा list_head		*item,
	काष्ठा xfs_btree_cur		**state)
अणु
	काष्ठा xfs_extent_मुक्त_item	*मुक्त;
	पूर्णांक				error;

	मुक्त = container_of(item, काष्ठा xfs_extent_मुक्त_item, xefi_list);
	error = xfs_trans_मुक्त_extent(tp, EFD_ITEM(करोne),
			मुक्त->xefi_startblock,
			मुक्त->xefi_blockcount,
			&मुक्त->xefi_oinfo, मुक्त->xefi_skip_discard);
	kmem_मुक्त(मुक्त);
	वापस error;
पूर्ण

/* Abort all pending EFIs. */
STATIC व्योम
xfs_extent_मुक्त_पात_पूर्णांकent(
	काष्ठा xfs_log_item		*पूर्णांकent)
अणु
	xfs_efi_release(EFI_ITEM(पूर्णांकent));
पूर्ण

/* Cancel a मुक्त extent. */
STATIC व्योम
xfs_extent_मुक्त_cancel_item(
	काष्ठा list_head		*item)
अणु
	काष्ठा xfs_extent_मुक्त_item	*मुक्त;

	मुक्त = container_of(item, काष्ठा xfs_extent_मुक्त_item, xefi_list);
	kmem_मुक्त(मुक्त);
पूर्ण

स्थिर काष्ठा xfs_defer_op_type xfs_extent_मुक्त_defer_type = अणु
	.max_items	= XFS_EFI_MAX_FAST_EXTENTS,
	.create_पूर्णांकent	= xfs_extent_मुक्त_create_पूर्णांकent,
	.पात_पूर्णांकent	= xfs_extent_मुक्त_पात_पूर्णांकent,
	.create_करोne	= xfs_extent_मुक्त_create_करोne,
	.finish_item	= xfs_extent_मुक्त_finish_item,
	.cancel_item	= xfs_extent_मुक्त_cancel_item,
पूर्ण;

/*
 * AGFL blocks are accounted dअगरferently in the reserve pools and are not
 * inserted पूर्णांकo the busy extent list.
 */
STATIC पूर्णांक
xfs_agfl_मुक्त_finish_item(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_log_item		*करोne,
	काष्ठा list_head		*item,
	काष्ठा xfs_btree_cur		**state)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_efd_log_item		*efdp = EFD_ITEM(करोne);
	काष्ठा xfs_extent_मुक्त_item	*मुक्त;
	काष्ठा xfs_extent		*extp;
	काष्ठा xfs_buf			*agbp;
	पूर्णांक				error;
	xfs_agnumber_t			agno;
	xfs_agblock_t			agbno;
	uपूर्णांक				next_extent;

	मुक्त = container_of(item, काष्ठा xfs_extent_मुक्त_item, xefi_list);
	ASSERT(मुक्त->xefi_blockcount == 1);
	agno = XFS_FSB_TO_AGNO(mp, मुक्त->xefi_startblock);
	agbno = XFS_FSB_TO_AGBNO(mp, मुक्त->xefi_startblock);

	trace_xfs_agfl_मुक्त_deferred(mp, agno, 0, agbno, मुक्त->xefi_blockcount);

	error = xfs_alloc_पढ़ो_agf(mp, tp, agno, 0, &agbp);
	अगर (!error)
		error = xfs_मुक्त_agfl_block(tp, agno, agbno, agbp,
					    &मुक्त->xefi_oinfo);

	/*
	 * Mark the transaction dirty, even on error. This ensures the
	 * transaction is पातed, which:
	 *
	 * 1.) releases the EFI and मुक्तs the EFD
	 * 2.) shuts करोwn the fileप्रणाली
	 */
	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &efdp->efd_item.li_flags);

	next_extent = efdp->efd_next_extent;
	ASSERT(next_extent < efdp->efd_क्रमmat.efd_nextents);
	extp = &(efdp->efd_क्रमmat.efd_extents[next_extent]);
	extp->ext_start = मुक्त->xefi_startblock;
	extp->ext_len = मुक्त->xefi_blockcount;
	efdp->efd_next_extent++;

	kmem_मुक्त(मुक्त);
	वापस error;
पूर्ण

/* sub-type with special handling क्रम AGFL deferred मुक्तs */
स्थिर काष्ठा xfs_defer_op_type xfs_agfl_मुक्त_defer_type = अणु
	.max_items	= XFS_EFI_MAX_FAST_EXTENTS,
	.create_पूर्णांकent	= xfs_extent_मुक्त_create_पूर्णांकent,
	.पात_पूर्णांकent	= xfs_extent_मुक्त_पात_पूर्णांकent,
	.create_करोne	= xfs_extent_मुक्त_create_करोne,
	.finish_item	= xfs_agfl_मुक्त_finish_item,
	.cancel_item	= xfs_extent_मुक्त_cancel_item,
पूर्ण;

/* Is this recovered EFI ok? */
अटल अंतरभूत bool
xfs_efi_validate_ext(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_extent		*extp)
अणु
	वापस xfs_verअगरy_fsbext(mp, extp->ext_start, extp->ext_len);
पूर्ण

/*
 * Process an extent मुक्त पूर्णांकent item that was recovered from
 * the log.  We need to मुक्त the extents that it describes.
 */
STATIC पूर्णांक
xfs_efi_item_recover(
	काष्ठा xfs_log_item		*lip,
	काष्ठा list_head		*capture_list)
अणु
	काष्ठा xfs_efi_log_item		*efip = EFI_ITEM(lip);
	काष्ठा xfs_mount		*mp = lip->li_mountp;
	काष्ठा xfs_efd_log_item		*efdp;
	काष्ठा xfs_trans		*tp;
	काष्ठा xfs_extent		*extp;
	पूर्णांक				i;
	पूर्णांक				error = 0;

	/*
	 * First check the validity of the extents described by the
	 * EFI.  If any are bad, then assume that all are bad and
	 * just toss the EFI.
	 */
	क्रम (i = 0; i < efip->efi_क्रमmat.efi_nextents; i++) अणु
		अगर (!xfs_efi_validate_ext(mp,
					&efip->efi_क्रमmat.efi_extents[i])) अणु
			XFS_CORRUPTION_ERROR(__func__, XFS_ERRLEVEL_LOW, mp,
					&efip->efi_क्रमmat,
					माप(efip->efi_क्रमmat));
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate, 0, 0, 0, &tp);
	अगर (error)
		वापस error;
	efdp = xfs_trans_get_efd(tp, efip, efip->efi_क्रमmat.efi_nextents);

	क्रम (i = 0; i < efip->efi_क्रमmat.efi_nextents; i++) अणु
		extp = &efip->efi_क्रमmat.efi_extents[i];
		error = xfs_trans_मुक्त_extent(tp, efdp, extp->ext_start,
					      extp->ext_len,
					      &XFS_RMAP_OINFO_ANY_OWNER, false);
		अगर (error)
			जाओ पात_error;

	पूर्ण

	वापस xfs_defer_ops_capture_and_commit(tp, शून्य, capture_list);

पात_error:
	xfs_trans_cancel(tp);
	वापस error;
पूर्ण

STATIC bool
xfs_efi_item_match(
	काष्ठा xfs_log_item	*lip,
	uपूर्णांक64_t		पूर्णांकent_id)
अणु
	वापस EFI_ITEM(lip)->efi_क्रमmat.efi_id == पूर्णांकent_id;
पूर्ण

/* Relog an पूर्णांकent item to push the log tail क्रमward. */
अटल काष्ठा xfs_log_item *
xfs_efi_item_relog(
	काष्ठा xfs_log_item		*पूर्णांकent,
	काष्ठा xfs_trans		*tp)
अणु
	काष्ठा xfs_efd_log_item		*efdp;
	काष्ठा xfs_efi_log_item		*efip;
	काष्ठा xfs_extent		*extp;
	अचिन्हित पूर्णांक			count;

	count = EFI_ITEM(पूर्णांकent)->efi_क्रमmat.efi_nextents;
	extp = EFI_ITEM(पूर्णांकent)->efi_क्रमmat.efi_extents;

	tp->t_flags |= XFS_TRANS_सूचीTY;
	efdp = xfs_trans_get_efd(tp, EFI_ITEM(पूर्णांकent), count);
	efdp->efd_next_extent = count;
	स_नकल(efdp->efd_क्रमmat.efd_extents, extp, count * माप(*extp));
	set_bit(XFS_LI_सूचीTY, &efdp->efd_item.li_flags);

	efip = xfs_efi_init(tp->t_mountp, count);
	स_नकल(efip->efi_क्रमmat.efi_extents, extp, count * माप(*extp));
	atomic_set(&efip->efi_next_extent, count);
	xfs_trans_add_item(tp, &efip->efi_item);
	set_bit(XFS_LI_सूचीTY, &efip->efi_item.li_flags);
	वापस &efip->efi_item;
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_efi_item_ops = अणु
	.iop_size	= xfs_efi_item_size,
	.iop_क्रमmat	= xfs_efi_item_क्रमmat,
	.iop_unpin	= xfs_efi_item_unpin,
	.iop_release	= xfs_efi_item_release,
	.iop_recover	= xfs_efi_item_recover,
	.iop_match	= xfs_efi_item_match,
	.iop_relog	= xfs_efi_item_relog,
पूर्ण;

/*
 * This routine is called to create an in-core extent मुक्त पूर्णांकent
 * item from the efi क्रमmat काष्ठाure which was logged on disk.
 * It allocates an in-core efi, copies the extents from the क्रमmat
 * काष्ठाure पूर्णांकo it, and adds the efi to the AIL with the given
 * LSN.
 */
STATIC पूर्णांक
xlog_recover_efi_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			lsn)
अणु
	काष्ठा xfs_mount		*mp = log->l_mp;
	काष्ठा xfs_efi_log_item		*efip;
	काष्ठा xfs_efi_log_क्रमmat	*efi_क्रमmatp;
	पूर्णांक				error;

	efi_क्रमmatp = item->ri_buf[0].i_addr;

	efip = xfs_efi_init(mp, efi_क्रमmatp->efi_nextents);
	error = xfs_efi_copy_क्रमmat(&item->ri_buf[0], &efip->efi_क्रमmat);
	अगर (error) अणु
		xfs_efi_item_मुक्त(efip);
		वापस error;
	पूर्ण
	atomic_set(&efip->efi_next_extent, efi_क्रमmatp->efi_nextents);
	/*
	 * Insert the पूर्णांकent पूर्णांकo the AIL directly and drop one reference so
	 * that finishing or canceling the work will drop the other.
	 */
	xfs_trans_ail_insert(log->l_ailp, &efip->efi_item, lsn);
	xfs_efi_release(efip);
	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_efi_item_ops = अणु
	.item_type		= XFS_LI_EFI,
	.commit_pass2		= xlog_recover_efi_commit_pass2,
पूर्ण;

/*
 * This routine is called when an EFD क्रमmat काष्ठाure is found in a committed
 * transaction in the log. Its purpose is to cancel the corresponding EFI अगर it
 * was still in the log. To करो this it searches the AIL क्रम the EFI with an id
 * equal to that in the EFD क्रमmat काष्ठाure. If we find it we drop the EFD
 * reference, which हटाओs the EFI from the AIL and मुक्तs it.
 */
STATIC पूर्णांक
xlog_recover_efd_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			lsn)
अणु
	काष्ठा xfs_efd_log_क्रमmat	*efd_क्रमmatp;

	efd_क्रमmatp = item->ri_buf[0].i_addr;
	ASSERT((item->ri_buf[0].i_len == (माप(xfs_efd_log_क्रमmat_32_t) +
		((efd_क्रमmatp->efd_nextents - 1) * माप(xfs_extent_32_t)))) ||
	       (item->ri_buf[0].i_len == (माप(xfs_efd_log_क्रमmat_64_t) +
		((efd_क्रमmatp->efd_nextents - 1) * माप(xfs_extent_64_t)))));

	xlog_recover_release_पूर्णांकent(log, XFS_LI_EFI, efd_क्रमmatp->efd_efi_id);
	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_efd_item_ops = अणु
	.item_type		= XFS_LI_EFD,
	.commit_pass2		= xlog_recover_efd_commit_pass2,
पूर्ण;
