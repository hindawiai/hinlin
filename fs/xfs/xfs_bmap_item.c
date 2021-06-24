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
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_bmap_item.h"
#समावेश "xfs_log.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_error.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_log_recover.h"
#समावेश "xfs_quota.h"

kmem_zone_t	*xfs_bui_zone;
kmem_zone_t	*xfs_bud_zone;

अटल स्थिर काष्ठा xfs_item_ops xfs_bui_item_ops;

अटल अंतरभूत काष्ठा xfs_bui_log_item *BUI_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_bui_log_item, bui_item);
पूर्ण

STATIC व्योम
xfs_bui_item_मुक्त(
	काष्ठा xfs_bui_log_item	*buip)
अणु
	kmem_cache_मुक्त(xfs_bui_zone, buip);
पूर्ण

/*
 * Freeing the BUI requires that we हटाओ it from the AIL अगर it has alपढ़ोy
 * been placed there. However, the BUI may not yet have been placed in the AIL
 * when called by xfs_bui_release() from BUD processing due to the ordering of
 * committed vs unpin operations in bulk insert operations. Hence the reference
 * count to ensure only the last caller मुक्तs the BUI.
 */
STATIC व्योम
xfs_bui_release(
	काष्ठा xfs_bui_log_item	*buip)
अणु
	ASSERT(atomic_पढ़ो(&buip->bui_refcount) > 0);
	अगर (atomic_dec_and_test(&buip->bui_refcount)) अणु
		xfs_trans_ail_delete(&buip->bui_item, SHUTDOWN_LOG_IO_ERROR);
		xfs_bui_item_मुक्त(buip);
	पूर्ण
पूर्ण


STATIC व्योम
xfs_bui_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	काष्ठा xfs_bui_log_item	*buip = BUI_ITEM(lip);

	*nvecs += 1;
	*nbytes += xfs_bui_log_क्रमmat_माप(buip->bui_क्रमmat.bui_nextents);
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the
 * given bui log item. We use only 1 iovec, and we poपूर्णांक that
 * at the bui_log_क्रमmat काष्ठाure embedded in the bui item.
 * It is at this poपूर्णांक that we निश्चित that all of the extent
 * slots in the bui item have been filled.
 */
STATIC व्योम
xfs_bui_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_bui_log_item	*buip = BUI_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;

	ASSERT(atomic_पढ़ो(&buip->bui_next_extent) ==
			buip->bui_क्रमmat.bui_nextents);

	buip->bui_क्रमmat.bui_type = XFS_LI_BUI;
	buip->bui_क्रमmat.bui_size = 1;

	xlog_copy_iovec(lv, &vecp, XLOG_REG_TYPE_BUI_FORMAT, &buip->bui_क्रमmat,
			xfs_bui_log_क्रमmat_माप(buip->bui_क्रमmat.bui_nextents));
पूर्ण

/*
 * The unpin operation is the last place an BUI is manipulated in the log. It is
 * either inserted in the AIL or पातed in the event of a log I/O error. In
 * either हाल, the BUI transaction has been successfully committed to make it
 * this far. Thereक्रमe, we expect whoever committed the BUI to either स्थिरruct
 * and commit the BUD or drop the BUD's reference in the event of error. Simply
 * drop the log's BUI reference now that the log is करोne with it.
 */
STATIC व्योम
xfs_bui_item_unpin(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			हटाओ)
अणु
	काष्ठा xfs_bui_log_item	*buip = BUI_ITEM(lip);

	xfs_bui_release(buip);
पूर्ण

/*
 * The BUI has been either committed or पातed अगर the transaction has been
 * cancelled. If the transaction was cancelled, an BUD isn't going to be
 * स्थिरructed and thus we मुक्त the BUI here directly.
 */
STATIC व्योम
xfs_bui_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	xfs_bui_release(BUI_ITEM(lip));
पूर्ण

/*
 * Allocate and initialize an bui item with the given number of extents.
 */
STATIC काष्ठा xfs_bui_log_item *
xfs_bui_init(
	काष्ठा xfs_mount		*mp)

अणु
	काष्ठा xfs_bui_log_item		*buip;

	buip = kmem_cache_zalloc(xfs_bui_zone, GFP_KERNEL | __GFP_NOFAIL);

	xfs_log_item_init(mp, &buip->bui_item, XFS_LI_BUI, &xfs_bui_item_ops);
	buip->bui_क्रमmat.bui_nextents = XFS_BUI_MAX_FAST_EXTENTS;
	buip->bui_क्रमmat.bui_id = (uपूर्णांकptr_t)(व्योम *)buip;
	atomic_set(&buip->bui_next_extent, 0);
	atomic_set(&buip->bui_refcount, 2);

	वापस buip;
पूर्ण

अटल अंतरभूत काष्ठा xfs_bud_log_item *BUD_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_bud_log_item, bud_item);
पूर्ण

STATIC व्योम
xfs_bud_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	*nvecs += 1;
	*nbytes += माप(काष्ठा xfs_bud_log_क्रमmat);
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the
 * given bud log item. We use only 1 iovec, and we poपूर्णांक that
 * at the bud_log_क्रमmat काष्ठाure embedded in the bud item.
 * It is at this poपूर्णांक that we निश्चित that all of the extent
 * slots in the bud item have been filled.
 */
STATIC व्योम
xfs_bud_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_bud_log_item	*budp = BUD_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;

	budp->bud_क्रमmat.bud_type = XFS_LI_BUD;
	budp->bud_क्रमmat.bud_size = 1;

	xlog_copy_iovec(lv, &vecp, XLOG_REG_TYPE_BUD_FORMAT, &budp->bud_क्रमmat,
			माप(काष्ठा xfs_bud_log_क्रमmat));
पूर्ण

/*
 * The BUD is either committed or पातed अगर the transaction is cancelled. If
 * the transaction is cancelled, drop our reference to the BUI and मुक्त the
 * BUD.
 */
STATIC व्योम
xfs_bud_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_bud_log_item	*budp = BUD_ITEM(lip);

	xfs_bui_release(budp->bud_buip);
	kmem_cache_मुक्त(xfs_bud_zone, budp);
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_bud_item_ops = अणु
	.flags		= XFS_ITEM_RELEASE_WHEN_COMMITTED,
	.iop_size	= xfs_bud_item_size,
	.iop_क्रमmat	= xfs_bud_item_क्रमmat,
	.iop_release	= xfs_bud_item_release,
पूर्ण;

अटल काष्ठा xfs_bud_log_item *
xfs_trans_get_bud(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_bui_log_item		*buip)
अणु
	काष्ठा xfs_bud_log_item		*budp;

	budp = kmem_cache_zalloc(xfs_bud_zone, GFP_KERNEL | __GFP_NOFAIL);
	xfs_log_item_init(tp->t_mountp, &budp->bud_item, XFS_LI_BUD,
			  &xfs_bud_item_ops);
	budp->bud_buip = buip;
	budp->bud_क्रमmat.bud_bui_id = buip->bui_क्रमmat.bui_id;

	xfs_trans_add_item(tp, &budp->bud_item);
	वापस budp;
पूर्ण

/*
 * Finish an bmap update and log it to the BUD. Note that the
 * transaction is marked dirty regardless of whether the bmap update
 * succeeds or fails to support the BUI/BUD lअगरecycle rules.
 */
अटल पूर्णांक
xfs_trans_log_finish_bmap_update(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_bud_log_item		*budp,
	क्रमागत xfs_bmap_पूर्णांकent_type	type,
	काष्ठा xfs_inode		*ip,
	पूर्णांक				whichविभाजन,
	xfs_fileoff_t			startoff,
	xfs_fsblock_t			startblock,
	xfs_filblks_t			*blockcount,
	xfs_exntst_t			state)
अणु
	पूर्णांक				error;

	error = xfs_bmap_finish_one(tp, ip, type, whichविभाजन, startoff,
			startblock, blockcount, state);

	/*
	 * Mark the transaction dirty, even on error. This ensures the
	 * transaction is पातed, which:
	 *
	 * 1.) releases the BUI and मुक्तs the BUD
	 * 2.) shuts करोwn the fileप्रणाली
	 */
	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &budp->bud_item.li_flags);

	वापस error;
पूर्ण

/* Sort bmap पूर्णांकents by inode. */
अटल पूर्णांक
xfs_bmap_update_dअगरf_items(
	व्योम				*priv,
	स्थिर काष्ठा list_head		*a,
	स्थिर काष्ठा list_head		*b)
अणु
	काष्ठा xfs_bmap_पूर्णांकent		*ba;
	काष्ठा xfs_bmap_पूर्णांकent		*bb;

	ba = container_of(a, काष्ठा xfs_bmap_पूर्णांकent, bi_list);
	bb = container_of(b, काष्ठा xfs_bmap_पूर्णांकent, bi_list);
	वापस ba->bi_owner->i_ino - bb->bi_owner->i_ino;
पूर्ण

/* Set the map extent flags क्रम this mapping. */
अटल व्योम
xfs_trans_set_bmap_flags(
	काष्ठा xfs_map_extent		*bmap,
	क्रमागत xfs_bmap_पूर्णांकent_type	type,
	पूर्णांक				whichविभाजन,
	xfs_exntst_t			state)
अणु
	bmap->me_flags = 0;
	चयन (type) अणु
	हाल XFS_BMAP_MAP:
	हाल XFS_BMAP_UNMAP:
		bmap->me_flags = type;
		अवरोध;
	शेष:
		ASSERT(0);
	पूर्ण
	अगर (state == XFS_EXT_UNWRITTEN)
		bmap->me_flags |= XFS_BMAP_EXTENT_UNWRITTEN;
	अगर (whichविभाजन == XFS_ATTR_FORK)
		bmap->me_flags |= XFS_BMAP_EXTENT_ATTR_FORK;
पूर्ण

/* Log bmap updates in the पूर्णांकent item. */
STATIC व्योम
xfs_bmap_update_log_item(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_bui_log_item		*buip,
	काष्ठा xfs_bmap_पूर्णांकent		*bmap)
अणु
	uपूर्णांक				next_extent;
	काष्ठा xfs_map_extent		*map;

	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &buip->bui_item.li_flags);

	/*
	 * atomic_inc_वापस gives us the value after the increment;
	 * we want to use it as an array index so we need to subtract 1 from
	 * it.
	 */
	next_extent = atomic_inc_वापस(&buip->bui_next_extent) - 1;
	ASSERT(next_extent < buip->bui_क्रमmat.bui_nextents);
	map = &buip->bui_क्रमmat.bui_extents[next_extent];
	map->me_owner = bmap->bi_owner->i_ino;
	map->me_startblock = bmap->bi_bmap.br_startblock;
	map->me_startoff = bmap->bi_bmap.br_startoff;
	map->me_len = bmap->bi_bmap.br_blockcount;
	xfs_trans_set_bmap_flags(map, bmap->bi_type, bmap->bi_whichविभाजन,
			bmap->bi_bmap.br_state);
पूर्ण

अटल काष्ठा xfs_log_item *
xfs_bmap_update_create_पूर्णांकent(
	काष्ठा xfs_trans		*tp,
	काष्ठा list_head		*items,
	अचिन्हित पूर्णांक			count,
	bool				sort)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_bui_log_item		*buip = xfs_bui_init(mp);
	काष्ठा xfs_bmap_पूर्णांकent		*bmap;

	ASSERT(count == XFS_BUI_MAX_FAST_EXTENTS);

	xfs_trans_add_item(tp, &buip->bui_item);
	अगर (sort)
		list_sort(mp, items, xfs_bmap_update_dअगरf_items);
	list_क्रम_each_entry(bmap, items, bi_list)
		xfs_bmap_update_log_item(tp, buip, bmap);
	वापस &buip->bui_item;
पूर्ण

/* Get an BUD so we can process all the deferred rmap updates. */
अटल काष्ठा xfs_log_item *
xfs_bmap_update_create_करोne(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_log_item		*पूर्णांकent,
	अचिन्हित पूर्णांक			count)
अणु
	वापस &xfs_trans_get_bud(tp, BUI_ITEM(पूर्णांकent))->bud_item;
पूर्ण

/* Process a deferred rmap update. */
STATIC पूर्णांक
xfs_bmap_update_finish_item(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_log_item		*करोne,
	काष्ठा list_head		*item,
	काष्ठा xfs_btree_cur		**state)
अणु
	काष्ठा xfs_bmap_पूर्णांकent		*bmap;
	xfs_filblks_t			count;
	पूर्णांक				error;

	bmap = container_of(item, काष्ठा xfs_bmap_पूर्णांकent, bi_list);
	count = bmap->bi_bmap.br_blockcount;
	error = xfs_trans_log_finish_bmap_update(tp, BUD_ITEM(करोne),
			bmap->bi_type,
			bmap->bi_owner, bmap->bi_whichविभाजन,
			bmap->bi_bmap.br_startoff,
			bmap->bi_bmap.br_startblock,
			&count,
			bmap->bi_bmap.br_state);
	अगर (!error && count > 0) अणु
		ASSERT(bmap->bi_type == XFS_BMAP_UNMAP);
		bmap->bi_bmap.br_blockcount = count;
		वापस -EAGAIN;
	पूर्ण
	kmem_मुक्त(bmap);
	वापस error;
पूर्ण

/* Abort all pending BUIs. */
STATIC व्योम
xfs_bmap_update_पात_पूर्णांकent(
	काष्ठा xfs_log_item		*पूर्णांकent)
अणु
	xfs_bui_release(BUI_ITEM(पूर्णांकent));
पूर्ण

/* Cancel a deferred rmap update. */
STATIC व्योम
xfs_bmap_update_cancel_item(
	काष्ठा list_head		*item)
अणु
	काष्ठा xfs_bmap_पूर्णांकent		*bmap;

	bmap = container_of(item, काष्ठा xfs_bmap_पूर्णांकent, bi_list);
	kmem_मुक्त(bmap);
पूर्ण

स्थिर काष्ठा xfs_defer_op_type xfs_bmap_update_defer_type = अणु
	.max_items	= XFS_BUI_MAX_FAST_EXTENTS,
	.create_पूर्णांकent	= xfs_bmap_update_create_पूर्णांकent,
	.पात_पूर्णांकent	= xfs_bmap_update_पात_पूर्णांकent,
	.create_करोne	= xfs_bmap_update_create_करोne,
	.finish_item	= xfs_bmap_update_finish_item,
	.cancel_item	= xfs_bmap_update_cancel_item,
पूर्ण;

/* Is this recovered BUI ok? */
अटल अंतरभूत bool
xfs_bui_validate(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_bui_log_item		*buip)
अणु
	काष्ठा xfs_map_extent		*bmap;

	/* Only one mapping operation per BUI... */
	अगर (buip->bui_क्रमmat.bui_nextents != XFS_BUI_MAX_FAST_EXTENTS)
		वापस false;

	bmap = &buip->bui_क्रमmat.bui_extents[0];

	अगर (bmap->me_flags & ~XFS_BMAP_EXTENT_FLAGS)
		वापस false;

	चयन (bmap->me_flags & XFS_BMAP_EXTENT_TYPE_MASK) अणु
	हाल XFS_BMAP_MAP:
	हाल XFS_BMAP_UNMAP:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (!xfs_verअगरy_ino(mp, bmap->me_owner))
		वापस false;

	अगर (!xfs_verअगरy_fileext(mp, bmap->me_startoff, bmap->me_len))
		वापस false;

	वापस xfs_verअगरy_fsbext(mp, bmap->me_startblock, bmap->me_len);
पूर्ण

/*
 * Process a bmap update पूर्णांकent item that was recovered from the log.
 * We need to update some inode's bmbt.
 */
STATIC पूर्णांक
xfs_bui_item_recover(
	काष्ठा xfs_log_item		*lip,
	काष्ठा list_head		*capture_list)
अणु
	काष्ठा xfs_bmbt_irec		irec;
	काष्ठा xfs_bui_log_item		*buip = BUI_ITEM(lip);
	काष्ठा xfs_trans		*tp;
	काष्ठा xfs_inode		*ip = शून्य;
	काष्ठा xfs_mount		*mp = lip->li_mountp;
	काष्ठा xfs_map_extent		*bmap;
	काष्ठा xfs_bud_log_item		*budp;
	xfs_filblks_t			count;
	xfs_exntst_t			state;
	अचिन्हित पूर्णांक			bui_type;
	पूर्णांक				whichविभाजन;
	पूर्णांक				iext_delta;
	पूर्णांक				error = 0;

	अगर (!xfs_bui_validate(mp, buip)) अणु
		XFS_CORRUPTION_ERROR(__func__, XFS_ERRLEVEL_LOW, mp,
				&buip->bui_क्रमmat, माप(buip->bui_क्रमmat));
		वापस -EFSCORRUPTED;
	पूर्ण

	bmap = &buip->bui_क्रमmat.bui_extents[0];
	state = (bmap->me_flags & XFS_BMAP_EXTENT_UNWRITTEN) ?
			XFS_EXT_UNWRITTEN : XFS_EXT_NORM;
	whichविभाजन = (bmap->me_flags & XFS_BMAP_EXTENT_ATTR_FORK) ?
			XFS_ATTR_FORK : XFS_DATA_FORK;
	bui_type = bmap->me_flags & XFS_BMAP_EXTENT_TYPE_MASK;

	/* Grab the inode. */
	error = xfs_iget(mp, शून्य, bmap->me_owner, 0, 0, &ip);
	अगर (error)
		वापस error;

	error = xfs_qm_dqattach(ip);
	अगर (error)
		जाओ err_rele;

	अगर (VFS_I(ip)->i_nlink == 0)
		xfs_अगरlags_set(ip, XFS_IRECOVERY);

	/* Allocate transaction and करो the work. */
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate,
			XFS_EXTENTADD_SPACE_RES(mp, XFS_DATA_FORK), 0, 0, &tp);
	अगर (error)
		जाओ err_rele;

	budp = xfs_trans_get_bud(tp, buip);
	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	अगर (bui_type == XFS_BMAP_MAP)
		iext_delta = XFS_IEXT_ADD_NOSPLIT_CNT;
	अन्यथा
		iext_delta = XFS_IEXT_PUNCH_HOLE_CNT;

	error = xfs_iext_count_may_overflow(ip, whichविभाजन, iext_delta);
	अगर (error)
		जाओ err_cancel;

	count = bmap->me_len;
	error = xfs_trans_log_finish_bmap_update(tp, budp, bui_type, ip,
			whichविभाजन, bmap->me_startoff, bmap->me_startblock,
			&count, state);
	अगर (error)
		जाओ err_cancel;

	अगर (count > 0) अणु
		ASSERT(bui_type == XFS_BMAP_UNMAP);
		irec.br_startblock = bmap->me_startblock;
		irec.br_blockcount = count;
		irec.br_startoff = bmap->me_startoff;
		irec.br_state = state;
		xfs_bmap_unmap_extent(tp, ip, &irec);
	पूर्ण

	/*
	 * Commit transaction, which मुक्तs the transaction and saves the inode
	 * क्रम later replay activities.
	 */
	error = xfs_defer_ops_capture_and_commit(tp, ip, capture_list);
	अगर (error)
		जाओ err_unlock;

	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	xfs_irele(ip);
	वापस 0;

err_cancel:
	xfs_trans_cancel(tp);
err_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
err_rele:
	xfs_irele(ip);
	वापस error;
पूर्ण

STATIC bool
xfs_bui_item_match(
	काष्ठा xfs_log_item	*lip,
	uपूर्णांक64_t		पूर्णांकent_id)
अणु
	वापस BUI_ITEM(lip)->bui_क्रमmat.bui_id == पूर्णांकent_id;
पूर्ण

/* Relog an पूर्णांकent item to push the log tail क्रमward. */
अटल काष्ठा xfs_log_item *
xfs_bui_item_relog(
	काष्ठा xfs_log_item		*पूर्णांकent,
	काष्ठा xfs_trans		*tp)
अणु
	काष्ठा xfs_bud_log_item		*budp;
	काष्ठा xfs_bui_log_item		*buip;
	काष्ठा xfs_map_extent		*extp;
	अचिन्हित पूर्णांक			count;

	count = BUI_ITEM(पूर्णांकent)->bui_क्रमmat.bui_nextents;
	extp = BUI_ITEM(पूर्णांकent)->bui_क्रमmat.bui_extents;

	tp->t_flags |= XFS_TRANS_सूचीTY;
	budp = xfs_trans_get_bud(tp, BUI_ITEM(पूर्णांकent));
	set_bit(XFS_LI_सूचीTY, &budp->bud_item.li_flags);

	buip = xfs_bui_init(tp->t_mountp);
	स_नकल(buip->bui_क्रमmat.bui_extents, extp, count * माप(*extp));
	atomic_set(&buip->bui_next_extent, count);
	xfs_trans_add_item(tp, &buip->bui_item);
	set_bit(XFS_LI_सूचीTY, &buip->bui_item.li_flags);
	वापस &buip->bui_item;
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_bui_item_ops = अणु
	.iop_size	= xfs_bui_item_size,
	.iop_क्रमmat	= xfs_bui_item_क्रमmat,
	.iop_unpin	= xfs_bui_item_unpin,
	.iop_release	= xfs_bui_item_release,
	.iop_recover	= xfs_bui_item_recover,
	.iop_match	= xfs_bui_item_match,
	.iop_relog	= xfs_bui_item_relog,
पूर्ण;

/*
 * Copy an BUI क्रमmat buffer from the given buf, and पूर्णांकo the destination
 * BUI क्रमmat काष्ठाure.  The BUI/BUD items were deचिन्हित not to need any
 * special alignment handling.
 */
अटल पूर्णांक
xfs_bui_copy_क्रमmat(
	काष्ठा xfs_log_iovec		*buf,
	काष्ठा xfs_bui_log_क्रमmat	*dst_bui_fmt)
अणु
	काष्ठा xfs_bui_log_क्रमmat	*src_bui_fmt;
	uपूर्णांक				len;

	src_bui_fmt = buf->i_addr;
	len = xfs_bui_log_क्रमmat_माप(src_bui_fmt->bui_nextents);

	अगर (buf->i_len == len) अणु
		स_नकल(dst_bui_fmt, src_bui_fmt, len);
		वापस 0;
	पूर्ण
	XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, शून्य);
	वापस -EFSCORRUPTED;
पूर्ण

/*
 * This routine is called to create an in-core extent bmap update
 * item from the bui क्रमmat काष्ठाure which was logged on disk.
 * It allocates an in-core bui, copies the extents from the क्रमmat
 * काष्ठाure पूर्णांकo it, and adds the bui to the AIL with the given
 * LSN.
 */
STATIC पूर्णांक
xlog_recover_bui_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			lsn)
अणु
	पूर्णांक				error;
	काष्ठा xfs_mount		*mp = log->l_mp;
	काष्ठा xfs_bui_log_item		*buip;
	काष्ठा xfs_bui_log_क्रमmat	*bui_क्रमmatp;

	bui_क्रमmatp = item->ri_buf[0].i_addr;

	अगर (bui_क्रमmatp->bui_nextents != XFS_BUI_MAX_FAST_EXTENTS) अणु
		XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, log->l_mp);
		वापस -EFSCORRUPTED;
	पूर्ण
	buip = xfs_bui_init(mp);
	error = xfs_bui_copy_क्रमmat(&item->ri_buf[0], &buip->bui_क्रमmat);
	अगर (error) अणु
		xfs_bui_item_मुक्त(buip);
		वापस error;
	पूर्ण
	atomic_set(&buip->bui_next_extent, bui_क्रमmatp->bui_nextents);
	/*
	 * Insert the पूर्णांकent पूर्णांकo the AIL directly and drop one reference so
	 * that finishing or canceling the work will drop the other.
	 */
	xfs_trans_ail_insert(log->l_ailp, &buip->bui_item, lsn);
	xfs_bui_release(buip);
	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_bui_item_ops = अणु
	.item_type		= XFS_LI_BUI,
	.commit_pass2		= xlog_recover_bui_commit_pass2,
पूर्ण;

/*
 * This routine is called when an BUD क्रमmat काष्ठाure is found in a committed
 * transaction in the log. Its purpose is to cancel the corresponding BUI अगर it
 * was still in the log. To करो this it searches the AIL क्रम the BUI with an id
 * equal to that in the BUD क्रमmat काष्ठाure. If we find it we drop the BUD
 * reference, which हटाओs the BUI from the AIL and मुक्तs it.
 */
STATIC पूर्णांक
xlog_recover_bud_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			lsn)
अणु
	काष्ठा xfs_bud_log_क्रमmat	*bud_क्रमmatp;

	bud_क्रमmatp = item->ri_buf[0].i_addr;
	अगर (item->ri_buf[0].i_len != माप(काष्ठा xfs_bud_log_क्रमmat)) अणु
		XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, log->l_mp);
		वापस -EFSCORRUPTED;
	पूर्ण

	xlog_recover_release_पूर्णांकent(log, XFS_LI_BUI, bud_क्रमmatp->bud_bui_id);
	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_bud_item_ops = अणु
	.item_type		= XFS_LI_BUD,
	.commit_pass2		= xlog_recover_bud_commit_pass2,
पूर्ण;
