<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित	__XFS_BMAP_ITEM_H__
#घोषणा	__XFS_BMAP_ITEM_H__

/*
 * There are (currently) two pairs of bmap btree reकरो item types: map & unmap.
 * The common abbreviations क्रम these are BUI (bmap update पूर्णांकent) and BUD
 * (bmap update करोne).  The reकरो item type is encoded in the flags field of
 * each xfs_map_extent.
 *
 * *I items should be recorded in the *first* of a series of rolled
 * transactions, and the *D items should be recorded in the same transaction
 * that records the associated bmbt updates.
 *
 * Should the प्रणाली crash after the commit of the first transaction but
 * beक्रमe the commit of the final transaction in a series, log recovery will
 * use the reकरो inक्रमmation recorded by the पूर्णांकent items to replay the
 * bmbt metadata updates in the non-first transaction.
 */

/* kernel only BUI/BUD definitions */

काष्ठा xfs_mount;
काष्ठा kmem_zone;

/*
 * Max number of extents in fast allocation path.
 */
#घोषणा	XFS_BUI_MAX_FAST_EXTENTS	1

/*
 * This is the "bmap update intent" log item.  It is used to log the fact that
 * some reverse mappings need to change.  It is used in conjunction with the
 * "bmap update done" log item described below.
 *
 * These log items follow the same rules as काष्ठा xfs_efi_log_item; see the
 * comments about that काष्ठाure (in xfs_extमुक्त_item.h) क्रम more details.
 */
काष्ठा xfs_bui_log_item अणु
	काष्ठा xfs_log_item		bui_item;
	atomic_t			bui_refcount;
	atomic_t			bui_next_extent;
	काष्ठा xfs_bui_log_क्रमmat	bui_क्रमmat;
पूर्ण;

अटल अंतरभूत माप_प्रकार
xfs_bui_log_item_माप(
	अचिन्हित पूर्णांक		nr)
अणु
	वापस दुरत्व(काष्ठा xfs_bui_log_item, bui_क्रमmat) +
			xfs_bui_log_क्रमmat_माप(nr);
पूर्ण

/*
 * This is the "bmap update done" log item.  It is used to log the fact that
 * some bmbt updates mentioned in an earlier bui item have been perक्रमmed.
 */
काष्ठा xfs_bud_log_item अणु
	काष्ठा xfs_log_item		bud_item;
	काष्ठा xfs_bui_log_item		*bud_buip;
	काष्ठा xfs_bud_log_क्रमmat	bud_क्रमmat;
पूर्ण;

बाह्य काष्ठा kmem_zone	*xfs_bui_zone;
बाह्य काष्ठा kmem_zone	*xfs_bud_zone;

#पूर्ण_अगर	/* __XFS_BMAP_ITEM_H__ */
