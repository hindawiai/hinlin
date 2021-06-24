<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_DEFER_H__
#घोषणा	__XFS_DEFER_H__

काष्ठा xfs_btree_cur;
काष्ठा xfs_defer_op_type;
काष्ठा xfs_defer_capture;

/*
 * Header क्रम deferred operation list.
 */
क्रमागत xfs_defer_ops_type अणु
	XFS_DEFER_OPS_TYPE_BMAP,
	XFS_DEFER_OPS_TYPE_REFCOUNT,
	XFS_DEFER_OPS_TYPE_RMAP,
	XFS_DEFER_OPS_TYPE_FREE,
	XFS_DEFER_OPS_TYPE_AGFL_FREE,
	XFS_DEFER_OPS_TYPE_MAX,
पूर्ण;

/*
 * Save a log पूर्णांकent item and a list of extents, so that we can replay
 * whatever action had to happen to the extent list and file the log करोne
 * item.
 */
काष्ठा xfs_defer_pending अणु
	काष्ठा list_head		dfp_list;	/* pending items */
	काष्ठा list_head		dfp_work;	/* work items */
	काष्ठा xfs_log_item		*dfp_पूर्णांकent;	/* log पूर्णांकent item */
	काष्ठा xfs_log_item		*dfp_करोne;	/* log करोne item */
	अचिन्हित पूर्णांक			dfp_count;	/* # extent items */
	क्रमागत xfs_defer_ops_type		dfp_type;
पूर्ण;

व्योम xfs_defer_add(काष्ठा xfs_trans *tp, क्रमागत xfs_defer_ops_type type,
		काष्ठा list_head *h);
पूर्णांक xfs_defer_finish_noroll(काष्ठा xfs_trans **tp);
पूर्णांक xfs_defer_finish(काष्ठा xfs_trans **tp);
व्योम xfs_defer_cancel(काष्ठा xfs_trans *);
व्योम xfs_defer_move(काष्ठा xfs_trans *dtp, काष्ठा xfs_trans *stp);

/* Description of a deferred type. */
काष्ठा xfs_defer_op_type अणु
	काष्ठा xfs_log_item *(*create_पूर्णांकent)(काष्ठा xfs_trans *tp,
			काष्ठा list_head *items, अचिन्हित पूर्णांक count, bool sort);
	व्योम (*पात_पूर्णांकent)(काष्ठा xfs_log_item *पूर्णांकent);
	काष्ठा xfs_log_item *(*create_करोne)(काष्ठा xfs_trans *tp,
			काष्ठा xfs_log_item *पूर्णांकent, अचिन्हित पूर्णांक count);
	पूर्णांक (*finish_item)(काष्ठा xfs_trans *tp, काष्ठा xfs_log_item *करोne,
			काष्ठा list_head *item, काष्ठा xfs_btree_cur **state);
	व्योम (*finish_cleanup)(काष्ठा xfs_trans *tp,
			काष्ठा xfs_btree_cur *state, पूर्णांक error);
	व्योम (*cancel_item)(काष्ठा list_head *item);
	अचिन्हित पूर्णांक		max_items;
पूर्ण;

बाह्य स्थिर काष्ठा xfs_defer_op_type xfs_bmap_update_defer_type;
बाह्य स्थिर काष्ठा xfs_defer_op_type xfs_refcount_update_defer_type;
बाह्य स्थिर काष्ठा xfs_defer_op_type xfs_rmap_update_defer_type;
बाह्य स्थिर काष्ठा xfs_defer_op_type xfs_extent_मुक्त_defer_type;
बाह्य स्थिर काष्ठा xfs_defer_op_type xfs_agfl_मुक्त_defer_type;

/*
 * This काष्ठाure enables a dfops user to detach the chain of deferred
 * operations from a transaction so that they can be जारीd later.
 */
काष्ठा xfs_defer_capture अणु
	/* List of other capture काष्ठाures. */
	काष्ठा list_head	dfc_list;

	/* Deferred ops state saved from the transaction. */
	काष्ठा list_head	dfc_dfops;
	अचिन्हित पूर्णांक		dfc_tpflags;

	/* Block reservations क्रम the data and rt devices. */
	अचिन्हित पूर्णांक		dfc_blkres;
	अचिन्हित पूर्णांक		dfc_rtxres;

	/* Log reservation saved from the transaction. */
	अचिन्हित पूर्णांक		dfc_logres;

	/*
	 * An inode reference that must be मुख्यtained to complete the deferred
	 * work.
	 */
	काष्ठा xfs_inode	*dfc_capture_ip;
पूर्ण;

/*
 * Functions to capture a chain of deferred operations and जारी them later.
 * This करोesn't normally happen except log recovery.
 */
पूर्णांक xfs_defer_ops_capture_and_commit(काष्ठा xfs_trans *tp,
		काष्ठा xfs_inode *capture_ip, काष्ठा list_head *capture_list);
व्योम xfs_defer_ops_जारी(काष्ठा xfs_defer_capture *d, काष्ठा xfs_trans *tp,
		काष्ठा xfs_inode **captured_ipp);
व्योम xfs_defer_ops_release(काष्ठा xfs_mount *mp, काष्ठा xfs_defer_capture *d);

#पूर्ण_अगर /* __XFS_DEFER_H__ */
