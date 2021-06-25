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
#समावेश "xfs_rmap_item.h"
#समावेश "xfs_log.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_error.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_log_recover.h"

kmem_zone_t	*xfs_rui_zone;
kmem_zone_t	*xfs_rud_zone;

अटल स्थिर काष्ठा xfs_item_ops xfs_rui_item_ops;

अटल अंतरभूत काष्ठा xfs_rui_log_item *RUI_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_rui_log_item, rui_item);
पूर्ण

STATIC व्योम
xfs_rui_item_मुक्त(
	काष्ठा xfs_rui_log_item	*ruip)
अणु
	अगर (ruip->rui_क्रमmat.rui_nextents > XFS_RUI_MAX_FAST_EXTENTS)
		kmem_मुक्त(ruip);
	अन्यथा
		kmem_cache_मुक्त(xfs_rui_zone, ruip);
पूर्ण

/*
 * Freeing the RUI requires that we हटाओ it from the AIL अगर it has alपढ़ोy
 * been placed there. However, the RUI may not yet have been placed in the AIL
 * when called by xfs_rui_release() from RUD processing due to the ordering of
 * committed vs unpin operations in bulk insert operations. Hence the reference
 * count to ensure only the last caller मुक्तs the RUI.
 */
STATIC व्योम
xfs_rui_release(
	काष्ठा xfs_rui_log_item	*ruip)
अणु
	ASSERT(atomic_पढ़ो(&ruip->rui_refcount) > 0);
	अगर (atomic_dec_and_test(&ruip->rui_refcount)) अणु
		xfs_trans_ail_delete(&ruip->rui_item, SHUTDOWN_LOG_IO_ERROR);
		xfs_rui_item_मुक्त(ruip);
	पूर्ण
पूर्ण

STATIC व्योम
xfs_rui_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	काष्ठा xfs_rui_log_item	*ruip = RUI_ITEM(lip);

	*nvecs += 1;
	*nbytes += xfs_rui_log_क्रमmat_माप(ruip->rui_क्रमmat.rui_nextents);
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the
 * given rui log item. We use only 1 iovec, and we poपूर्णांक that
 * at the rui_log_क्रमmat काष्ठाure embedded in the rui item.
 * It is at this poपूर्णांक that we निश्चित that all of the extent
 * slots in the rui item have been filled.
 */
STATIC व्योम
xfs_rui_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_rui_log_item	*ruip = RUI_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;

	ASSERT(atomic_पढ़ो(&ruip->rui_next_extent) ==
			ruip->rui_क्रमmat.rui_nextents);

	ruip->rui_क्रमmat.rui_type = XFS_LI_RUI;
	ruip->rui_क्रमmat.rui_size = 1;

	xlog_copy_iovec(lv, &vecp, XLOG_REG_TYPE_RUI_FORMAT, &ruip->rui_क्रमmat,
			xfs_rui_log_क्रमmat_माप(ruip->rui_क्रमmat.rui_nextents));
पूर्ण

/*
 * The unpin operation is the last place an RUI is manipulated in the log. It is
 * either inserted in the AIL or पातed in the event of a log I/O error. In
 * either हाल, the RUI transaction has been successfully committed to make it
 * this far. Thereक्रमe, we expect whoever committed the RUI to either स्थिरruct
 * and commit the RUD or drop the RUD's reference in the event of error. Simply
 * drop the log's RUI reference now that the log is करोne with it.
 */
STATIC व्योम
xfs_rui_item_unpin(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			हटाओ)
अणु
	काष्ठा xfs_rui_log_item	*ruip = RUI_ITEM(lip);

	xfs_rui_release(ruip);
पूर्ण

/*
 * The RUI has been either committed or पातed अगर the transaction has been
 * cancelled. If the transaction was cancelled, an RUD isn't going to be
 * स्थिरructed and thus we मुक्त the RUI here directly.
 */
STATIC व्योम
xfs_rui_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	xfs_rui_release(RUI_ITEM(lip));
पूर्ण

/*
 * Allocate and initialize an rui item with the given number of extents.
 */
STATIC काष्ठा xfs_rui_log_item *
xfs_rui_init(
	काष्ठा xfs_mount		*mp,
	uपूर्णांक				nextents)

अणु
	काष्ठा xfs_rui_log_item		*ruip;

	ASSERT(nextents > 0);
	अगर (nextents > XFS_RUI_MAX_FAST_EXTENTS)
		ruip = kmem_zalloc(xfs_rui_log_item_माप(nextents), 0);
	अन्यथा
		ruip = kmem_cache_zalloc(xfs_rui_zone,
					 GFP_KERNEL | __GFP_NOFAIL);

	xfs_log_item_init(mp, &ruip->rui_item, XFS_LI_RUI, &xfs_rui_item_ops);
	ruip->rui_क्रमmat.rui_nextents = nextents;
	ruip->rui_क्रमmat.rui_id = (uपूर्णांकptr_t)(व्योम *)ruip;
	atomic_set(&ruip->rui_next_extent, 0);
	atomic_set(&ruip->rui_refcount, 2);

	वापस ruip;
पूर्ण

/*
 * Copy an RUI क्रमmat buffer from the given buf, and पूर्णांकo the destination
 * RUI क्रमmat काष्ठाure.  The RUI/RUD items were deचिन्हित not to need any
 * special alignment handling.
 */
STATIC पूर्णांक
xfs_rui_copy_क्रमmat(
	काष्ठा xfs_log_iovec		*buf,
	काष्ठा xfs_rui_log_क्रमmat	*dst_rui_fmt)
अणु
	काष्ठा xfs_rui_log_क्रमmat	*src_rui_fmt;
	uपूर्णांक				len;

	src_rui_fmt = buf->i_addr;
	len = xfs_rui_log_क्रमmat_माप(src_rui_fmt->rui_nextents);

	अगर (buf->i_len != len) अणु
		XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, शून्य);
		वापस -EFSCORRUPTED;
	पूर्ण

	स_नकल(dst_rui_fmt, src_rui_fmt, len);
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा xfs_rud_log_item *RUD_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_rud_log_item, rud_item);
पूर्ण

STATIC व्योम
xfs_rud_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	*nvecs += 1;
	*nbytes += माप(काष्ठा xfs_rud_log_क्रमmat);
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the
 * given rud log item. We use only 1 iovec, and we poपूर्णांक that
 * at the rud_log_क्रमmat काष्ठाure embedded in the rud item.
 * It is at this poपूर्णांक that we निश्चित that all of the extent
 * slots in the rud item have been filled.
 */
STATIC व्योम
xfs_rud_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_rud_log_item	*rudp = RUD_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;

	rudp->rud_क्रमmat.rud_type = XFS_LI_RUD;
	rudp->rud_क्रमmat.rud_size = 1;

	xlog_copy_iovec(lv, &vecp, XLOG_REG_TYPE_RUD_FORMAT, &rudp->rud_क्रमmat,
			माप(काष्ठा xfs_rud_log_क्रमmat));
पूर्ण

/*
 * The RUD is either committed or पातed अगर the transaction is cancelled. If
 * the transaction is cancelled, drop our reference to the RUI and मुक्त the
 * RUD.
 */
STATIC व्योम
xfs_rud_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_rud_log_item	*rudp = RUD_ITEM(lip);

	xfs_rui_release(rudp->rud_ruip);
	kmem_cache_मुक्त(xfs_rud_zone, rudp);
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_rud_item_ops = अणु
	.flags		= XFS_ITEM_RELEASE_WHEN_COMMITTED,
	.iop_size	= xfs_rud_item_size,
	.iop_क्रमmat	= xfs_rud_item_क्रमmat,
	.iop_release	= xfs_rud_item_release,
पूर्ण;

अटल काष्ठा xfs_rud_log_item *
xfs_trans_get_rud(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_rui_log_item		*ruip)
अणु
	काष्ठा xfs_rud_log_item		*rudp;

	rudp = kmem_cache_zalloc(xfs_rud_zone, GFP_KERNEL | __GFP_NOFAIL);
	xfs_log_item_init(tp->t_mountp, &rudp->rud_item, XFS_LI_RUD,
			  &xfs_rud_item_ops);
	rudp->rud_ruip = ruip;
	rudp->rud_क्रमmat.rud_rui_id = ruip->rui_क्रमmat.rui_id;

	xfs_trans_add_item(tp, &rudp->rud_item);
	वापस rudp;
पूर्ण

/* Set the map extent flags क्रम this reverse mapping. */
अटल व्योम
xfs_trans_set_rmap_flags(
	काष्ठा xfs_map_extent		*rmap,
	क्रमागत xfs_rmap_पूर्णांकent_type	type,
	पूर्णांक				whichविभाजन,
	xfs_exntst_t			state)
अणु
	rmap->me_flags = 0;
	अगर (state == XFS_EXT_UNWRITTEN)
		rmap->me_flags |= XFS_RMAP_EXTENT_UNWRITTEN;
	अगर (whichविभाजन == XFS_ATTR_FORK)
		rmap->me_flags |= XFS_RMAP_EXTENT_ATTR_FORK;
	चयन (type) अणु
	हाल XFS_RMAP_MAP:
		rmap->me_flags |= XFS_RMAP_EXTENT_MAP;
		अवरोध;
	हाल XFS_RMAP_MAP_SHARED:
		rmap->me_flags |= XFS_RMAP_EXTENT_MAP_SHARED;
		अवरोध;
	हाल XFS_RMAP_UNMAP:
		rmap->me_flags |= XFS_RMAP_EXTENT_UNMAP;
		अवरोध;
	हाल XFS_RMAP_UNMAP_SHARED:
		rmap->me_flags |= XFS_RMAP_EXTENT_UNMAP_SHARED;
		अवरोध;
	हाल XFS_RMAP_CONVERT:
		rmap->me_flags |= XFS_RMAP_EXTENT_CONVERT;
		अवरोध;
	हाल XFS_RMAP_CONVERT_SHARED:
		rmap->me_flags |= XFS_RMAP_EXTENT_CONVERT_SHARED;
		अवरोध;
	हाल XFS_RMAP_ALLOC:
		rmap->me_flags |= XFS_RMAP_EXTENT_ALLOC;
		अवरोध;
	हाल XFS_RMAP_FREE:
		rmap->me_flags |= XFS_RMAP_EXTENT_FREE;
		अवरोध;
	शेष:
		ASSERT(0);
	पूर्ण
पूर्ण

/*
 * Finish an rmap update and log it to the RUD. Note that the transaction is
 * marked dirty regardless of whether the rmap update succeeds or fails to
 * support the RUI/RUD lअगरecycle rules.
 */
अटल पूर्णांक
xfs_trans_log_finish_rmap_update(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_rud_log_item		*rudp,
	क्रमागत xfs_rmap_पूर्णांकent_type	type,
	uपूर्णांक64_t			owner,
	पूर्णांक				whichविभाजन,
	xfs_fileoff_t			startoff,
	xfs_fsblock_t			startblock,
	xfs_filblks_t			blockcount,
	xfs_exntst_t			state,
	काष्ठा xfs_btree_cur		**pcur)
अणु
	पूर्णांक				error;

	error = xfs_rmap_finish_one(tp, type, owner, whichविभाजन, startoff,
			startblock, blockcount, state, pcur);

	/*
	 * Mark the transaction dirty, even on error. This ensures the
	 * transaction is पातed, which:
	 *
	 * 1.) releases the RUI and मुक्तs the RUD
	 * 2.) shuts करोwn the fileप्रणाली
	 */
	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &rudp->rud_item.li_flags);

	वापस error;
पूर्ण

/* Sort rmap पूर्णांकents by AG. */
अटल पूर्णांक
xfs_rmap_update_dअगरf_items(
	व्योम				*priv,
	स्थिर काष्ठा list_head		*a,
	स्थिर काष्ठा list_head		*b)
अणु
	काष्ठा xfs_mount		*mp = priv;
	काष्ठा xfs_rmap_पूर्णांकent		*ra;
	काष्ठा xfs_rmap_पूर्णांकent		*rb;

	ra = container_of(a, काष्ठा xfs_rmap_पूर्णांकent, ri_list);
	rb = container_of(b, काष्ठा xfs_rmap_पूर्णांकent, ri_list);
	वापस  XFS_FSB_TO_AGNO(mp, ra->ri_bmap.br_startblock) -
		XFS_FSB_TO_AGNO(mp, rb->ri_bmap.br_startblock);
पूर्ण

/* Log rmap updates in the पूर्णांकent item. */
STATIC व्योम
xfs_rmap_update_log_item(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_rui_log_item		*ruip,
	काष्ठा xfs_rmap_पूर्णांकent		*rmap)
अणु
	uपूर्णांक				next_extent;
	काष्ठा xfs_map_extent		*map;

	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &ruip->rui_item.li_flags);

	/*
	 * atomic_inc_वापस gives us the value after the increment;
	 * we want to use it as an array index so we need to subtract 1 from
	 * it.
	 */
	next_extent = atomic_inc_वापस(&ruip->rui_next_extent) - 1;
	ASSERT(next_extent < ruip->rui_क्रमmat.rui_nextents);
	map = &ruip->rui_क्रमmat.rui_extents[next_extent];
	map->me_owner = rmap->ri_owner;
	map->me_startblock = rmap->ri_bmap.br_startblock;
	map->me_startoff = rmap->ri_bmap.br_startoff;
	map->me_len = rmap->ri_bmap.br_blockcount;
	xfs_trans_set_rmap_flags(map, rmap->ri_type, rmap->ri_whichविभाजन,
			rmap->ri_bmap.br_state);
पूर्ण

अटल काष्ठा xfs_log_item *
xfs_rmap_update_create_पूर्णांकent(
	काष्ठा xfs_trans		*tp,
	काष्ठा list_head		*items,
	अचिन्हित पूर्णांक			count,
	bool				sort)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_rui_log_item		*ruip = xfs_rui_init(mp, count);
	काष्ठा xfs_rmap_पूर्णांकent		*rmap;

	ASSERT(count > 0);

	xfs_trans_add_item(tp, &ruip->rui_item);
	अगर (sort)
		list_sort(mp, items, xfs_rmap_update_dअगरf_items);
	list_क्रम_each_entry(rmap, items, ri_list)
		xfs_rmap_update_log_item(tp, ruip, rmap);
	वापस &ruip->rui_item;
पूर्ण

/* Get an RUD so we can process all the deferred rmap updates. */
अटल काष्ठा xfs_log_item *
xfs_rmap_update_create_करोne(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_log_item		*पूर्णांकent,
	अचिन्हित पूर्णांक			count)
अणु
	वापस &xfs_trans_get_rud(tp, RUI_ITEM(पूर्णांकent))->rud_item;
पूर्ण

/* Process a deferred rmap update. */
STATIC पूर्णांक
xfs_rmap_update_finish_item(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_log_item		*करोne,
	काष्ठा list_head		*item,
	काष्ठा xfs_btree_cur		**state)
अणु
	काष्ठा xfs_rmap_पूर्णांकent		*rmap;
	पूर्णांक				error;

	rmap = container_of(item, काष्ठा xfs_rmap_पूर्णांकent, ri_list);
	error = xfs_trans_log_finish_rmap_update(tp, RUD_ITEM(करोne),
			rmap->ri_type, rmap->ri_owner, rmap->ri_whichविभाजन,
			rmap->ri_bmap.br_startoff, rmap->ri_bmap.br_startblock,
			rmap->ri_bmap.br_blockcount, rmap->ri_bmap.br_state,
			state);
	kmem_मुक्त(rmap);
	वापस error;
पूर्ण

/* Abort all pending RUIs. */
STATIC व्योम
xfs_rmap_update_पात_पूर्णांकent(
	काष्ठा xfs_log_item	*पूर्णांकent)
अणु
	xfs_rui_release(RUI_ITEM(पूर्णांकent));
पूर्ण

/* Cancel a deferred rmap update. */
STATIC व्योम
xfs_rmap_update_cancel_item(
	काष्ठा list_head		*item)
अणु
	काष्ठा xfs_rmap_पूर्णांकent		*rmap;

	rmap = container_of(item, काष्ठा xfs_rmap_पूर्णांकent, ri_list);
	kmem_मुक्त(rmap);
पूर्ण

स्थिर काष्ठा xfs_defer_op_type xfs_rmap_update_defer_type = अणु
	.max_items	= XFS_RUI_MAX_FAST_EXTENTS,
	.create_पूर्णांकent	= xfs_rmap_update_create_पूर्णांकent,
	.पात_पूर्णांकent	= xfs_rmap_update_पात_पूर्णांकent,
	.create_करोne	= xfs_rmap_update_create_करोne,
	.finish_item	= xfs_rmap_update_finish_item,
	.finish_cleanup = xfs_rmap_finish_one_cleanup,
	.cancel_item	= xfs_rmap_update_cancel_item,
पूर्ण;

/* Is this recovered RUI ok? */
अटल अंतरभूत bool
xfs_rui_validate_map(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_map_extent		*rmap)
अणु
	अगर (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस false;

	अगर (rmap->me_flags & ~XFS_RMAP_EXTENT_FLAGS)
		वापस false;

	चयन (rmap->me_flags & XFS_RMAP_EXTENT_TYPE_MASK) अणु
	हाल XFS_RMAP_EXTENT_MAP:
	हाल XFS_RMAP_EXTENT_MAP_SHARED:
	हाल XFS_RMAP_EXTENT_UNMAP:
	हाल XFS_RMAP_EXTENT_UNMAP_SHARED:
	हाल XFS_RMAP_EXTENT_CONVERT:
	हाल XFS_RMAP_EXTENT_CONVERT_SHARED:
	हाल XFS_RMAP_EXTENT_ALLOC:
	हाल XFS_RMAP_EXTENT_FREE:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (!XFS_RMAP_NON_INODE_OWNER(rmap->me_owner) &&
	    !xfs_verअगरy_ino(mp, rmap->me_owner))
		वापस false;

	अगर (!xfs_verअगरy_fileext(mp, rmap->me_startoff, rmap->me_len))
		वापस false;

	वापस xfs_verअगरy_fsbext(mp, rmap->me_startblock, rmap->me_len);
पूर्ण

/*
 * Process an rmap update पूर्णांकent item that was recovered from the log.
 * We need to update the rmapbt.
 */
STATIC पूर्णांक
xfs_rui_item_recover(
	काष्ठा xfs_log_item		*lip,
	काष्ठा list_head		*capture_list)
अणु
	काष्ठा xfs_rui_log_item		*ruip = RUI_ITEM(lip);
	काष्ठा xfs_map_extent		*rmap;
	काष्ठा xfs_rud_log_item		*rudp;
	काष्ठा xfs_trans		*tp;
	काष्ठा xfs_btree_cur		*rcur = शून्य;
	काष्ठा xfs_mount		*mp = lip->li_mountp;
	क्रमागत xfs_rmap_पूर्णांकent_type	type;
	xfs_exntst_t			state;
	पूर्णांक				i;
	पूर्णांक				whichविभाजन;
	पूर्णांक				error = 0;

	/*
	 * First check the validity of the extents described by the
	 * RUI.  If any are bad, then assume that all are bad and
	 * just toss the RUI.
	 */
	क्रम (i = 0; i < ruip->rui_क्रमmat.rui_nextents; i++) अणु
		अगर (!xfs_rui_validate_map(mp,
					&ruip->rui_क्रमmat.rui_extents[i])) अणु
			XFS_CORRUPTION_ERROR(__func__, XFS_ERRLEVEL_LOW, mp,
					&ruip->rui_क्रमmat,
					माप(ruip->rui_क्रमmat));
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate,
			mp->m_rmap_maxlevels, 0, XFS_TRANS_RESERVE, &tp);
	अगर (error)
		वापस error;
	rudp = xfs_trans_get_rud(tp, ruip);

	क्रम (i = 0; i < ruip->rui_क्रमmat.rui_nextents; i++) अणु
		rmap = &ruip->rui_क्रमmat.rui_extents[i];
		state = (rmap->me_flags & XFS_RMAP_EXTENT_UNWRITTEN) ?
				XFS_EXT_UNWRITTEN : XFS_EXT_NORM;
		whichविभाजन = (rmap->me_flags & XFS_RMAP_EXTENT_ATTR_FORK) ?
				XFS_ATTR_FORK : XFS_DATA_FORK;
		चयन (rmap->me_flags & XFS_RMAP_EXTENT_TYPE_MASK) अणु
		हाल XFS_RMAP_EXTENT_MAP:
			type = XFS_RMAP_MAP;
			अवरोध;
		हाल XFS_RMAP_EXTENT_MAP_SHARED:
			type = XFS_RMAP_MAP_SHARED;
			अवरोध;
		हाल XFS_RMAP_EXTENT_UNMAP:
			type = XFS_RMAP_UNMAP;
			अवरोध;
		हाल XFS_RMAP_EXTENT_UNMAP_SHARED:
			type = XFS_RMAP_UNMAP_SHARED;
			अवरोध;
		हाल XFS_RMAP_EXTENT_CONVERT:
			type = XFS_RMAP_CONVERT;
			अवरोध;
		हाल XFS_RMAP_EXTENT_CONVERT_SHARED:
			type = XFS_RMAP_CONVERT_SHARED;
			अवरोध;
		हाल XFS_RMAP_EXTENT_ALLOC:
			type = XFS_RMAP_ALLOC;
			अवरोध;
		हाल XFS_RMAP_EXTENT_FREE:
			type = XFS_RMAP_FREE;
			अवरोध;
		शेष:
			XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, शून्य);
			error = -EFSCORRUPTED;
			जाओ पात_error;
		पूर्ण
		error = xfs_trans_log_finish_rmap_update(tp, rudp, type,
				rmap->me_owner, whichविभाजन,
				rmap->me_startoff, rmap->me_startblock,
				rmap->me_len, state, &rcur);
		अगर (error)
			जाओ पात_error;

	पूर्ण

	xfs_rmap_finish_one_cleanup(tp, rcur, error);
	वापस xfs_defer_ops_capture_and_commit(tp, शून्य, capture_list);

पात_error:
	xfs_rmap_finish_one_cleanup(tp, rcur, error);
	xfs_trans_cancel(tp);
	वापस error;
पूर्ण

STATIC bool
xfs_rui_item_match(
	काष्ठा xfs_log_item	*lip,
	uपूर्णांक64_t		पूर्णांकent_id)
अणु
	वापस RUI_ITEM(lip)->rui_क्रमmat.rui_id == पूर्णांकent_id;
पूर्ण

/* Relog an पूर्णांकent item to push the log tail क्रमward. */
अटल काष्ठा xfs_log_item *
xfs_rui_item_relog(
	काष्ठा xfs_log_item		*पूर्णांकent,
	काष्ठा xfs_trans		*tp)
अणु
	काष्ठा xfs_rud_log_item		*rudp;
	काष्ठा xfs_rui_log_item		*ruip;
	काष्ठा xfs_map_extent		*extp;
	अचिन्हित पूर्णांक			count;

	count = RUI_ITEM(पूर्णांकent)->rui_क्रमmat.rui_nextents;
	extp = RUI_ITEM(पूर्णांकent)->rui_क्रमmat.rui_extents;

	tp->t_flags |= XFS_TRANS_सूचीTY;
	rudp = xfs_trans_get_rud(tp, RUI_ITEM(पूर्णांकent));
	set_bit(XFS_LI_सूचीTY, &rudp->rud_item.li_flags);

	ruip = xfs_rui_init(tp->t_mountp, count);
	स_नकल(ruip->rui_क्रमmat.rui_extents, extp, count * माप(*extp));
	atomic_set(&ruip->rui_next_extent, count);
	xfs_trans_add_item(tp, &ruip->rui_item);
	set_bit(XFS_LI_सूचीTY, &ruip->rui_item.li_flags);
	वापस &ruip->rui_item;
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_rui_item_ops = अणु
	.iop_size	= xfs_rui_item_size,
	.iop_क्रमmat	= xfs_rui_item_क्रमmat,
	.iop_unpin	= xfs_rui_item_unpin,
	.iop_release	= xfs_rui_item_release,
	.iop_recover	= xfs_rui_item_recover,
	.iop_match	= xfs_rui_item_match,
	.iop_relog	= xfs_rui_item_relog,
पूर्ण;

/*
 * This routine is called to create an in-core extent rmap update
 * item from the rui क्रमmat काष्ठाure which was logged on disk.
 * It allocates an in-core rui, copies the extents from the क्रमmat
 * काष्ठाure पूर्णांकo it, and adds the rui to the AIL with the given
 * LSN.
 */
STATIC पूर्णांक
xlog_recover_rui_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			lsn)
अणु
	पूर्णांक				error;
	काष्ठा xfs_mount		*mp = log->l_mp;
	काष्ठा xfs_rui_log_item		*ruip;
	काष्ठा xfs_rui_log_क्रमmat	*rui_क्रमmatp;

	rui_क्रमmatp = item->ri_buf[0].i_addr;

	ruip = xfs_rui_init(mp, rui_क्रमmatp->rui_nextents);
	error = xfs_rui_copy_क्रमmat(&item->ri_buf[0], &ruip->rui_क्रमmat);
	अगर (error) अणु
		xfs_rui_item_मुक्त(ruip);
		वापस error;
	पूर्ण
	atomic_set(&ruip->rui_next_extent, rui_क्रमmatp->rui_nextents);
	/*
	 * Insert the पूर्णांकent पूर्णांकo the AIL directly and drop one reference so
	 * that finishing or canceling the work will drop the other.
	 */
	xfs_trans_ail_insert(log->l_ailp, &ruip->rui_item, lsn);
	xfs_rui_release(ruip);
	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_rui_item_ops = अणु
	.item_type		= XFS_LI_RUI,
	.commit_pass2		= xlog_recover_rui_commit_pass2,
पूर्ण;

/*
 * This routine is called when an RUD क्रमmat काष्ठाure is found in a committed
 * transaction in the log. Its purpose is to cancel the corresponding RUI अगर it
 * was still in the log. To करो this it searches the AIL क्रम the RUI with an id
 * equal to that in the RUD क्रमmat काष्ठाure. If we find it we drop the RUD
 * reference, which हटाओs the RUI from the AIL and मुक्तs it.
 */
STATIC पूर्णांक
xlog_recover_rud_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			lsn)
अणु
	काष्ठा xfs_rud_log_क्रमmat	*rud_क्रमmatp;

	rud_क्रमmatp = item->ri_buf[0].i_addr;
	ASSERT(item->ri_buf[0].i_len == माप(काष्ठा xfs_rud_log_क्रमmat));

	xlog_recover_release_पूर्णांकent(log, XFS_LI_RUI, rud_क्रमmatp->rud_rui_id);
	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_rud_item_ops = अणु
	.item_type		= XFS_LI_RUD,
	.commit_pass2		= xlog_recover_rud_commit_pass2,
पूर्ण;
