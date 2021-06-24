<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित	__XFS_RMAP_ITEM_H__
#घोषणा	__XFS_RMAP_ITEM_H__

/*
 * There are (currently) three pairs of rmap btree reकरो item types: map, unmap,
 * and convert.  The common abbreviations क्रम these are RUI (rmap update
 * पूर्णांकent) and RUD (rmap update करोne).  The reकरो item type is encoded in the
 * flags field of each xfs_map_extent.
 *
 * *I items should be recorded in the *first* of a series of rolled
 * transactions, and the *D items should be recorded in the same transaction
 * that records the associated rmapbt updates.  Typically, the first
 * transaction will record a bmbt update, followed by some number of
 * transactions containing rmapbt updates, and finally transactions with any
 * bnobt/cntbt updates.
 *
 * Should the प्रणाली crash after the commit of the first transaction but
 * beक्रमe the commit of the final transaction in a series, log recovery will
 * use the reकरो inक्रमmation recorded by the पूर्णांकent items to replay the
 * (rmapbt/bnobt/cntbt) metadata updates in the non-first transaction.
 */

/* kernel only RUI/RUD definitions */

काष्ठा xfs_mount;
काष्ठा kmem_zone;

/*
 * Max number of extents in fast allocation path.
 */
#घोषणा	XFS_RUI_MAX_FAST_EXTENTS	16

/*
 * This is the "rmap update intent" log item.  It is used to log the fact that
 * some reverse mappings need to change.  It is used in conjunction with the
 * "rmap update done" log item described below.
 *
 * These log items follow the same rules as काष्ठा xfs_efi_log_item; see the
 * comments about that काष्ठाure (in xfs_extमुक्त_item.h) क्रम more details.
 */
काष्ठा xfs_rui_log_item अणु
	काष्ठा xfs_log_item		rui_item;
	atomic_t			rui_refcount;
	atomic_t			rui_next_extent;
	काष्ठा xfs_rui_log_क्रमmat	rui_क्रमmat;
पूर्ण;

अटल अंतरभूत माप_प्रकार
xfs_rui_log_item_माप(
	अचिन्हित पूर्णांक		nr)
अणु
	वापस दुरत्व(काष्ठा xfs_rui_log_item, rui_क्रमmat) +
			xfs_rui_log_क्रमmat_माप(nr);
पूर्ण

/*
 * This is the "rmap update done" log item.  It is used to log the fact that
 * some rmapbt updates mentioned in an earlier rui item have been perक्रमmed.
 */
काष्ठा xfs_rud_log_item अणु
	काष्ठा xfs_log_item		rud_item;
	काष्ठा xfs_rui_log_item		*rud_ruip;
	काष्ठा xfs_rud_log_क्रमmat	rud_क्रमmat;
पूर्ण;

बाह्य काष्ठा kmem_zone	*xfs_rui_zone;
बाह्य काष्ठा kmem_zone	*xfs_rud_zone;

#पूर्ण_अगर	/* __XFS_RMAP_ITEM_H__ */
