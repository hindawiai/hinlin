<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_REFCOUNT_BTREE_H__
#घोषणा	__XFS_REFCOUNT_BTREE_H__

/*
 * Reference Count Btree on-disk काष्ठाures
 */

काष्ठा xfs_buf;
काष्ठा xfs_btree_cur;
काष्ठा xfs_mount;
काष्ठा xbtree_afakeroot;

/*
 * Btree block header size
 */
#घोषणा XFS_REFCOUNT_BLOCK_LEN	XFS_BTREE_SBLOCK_CRC_LEN

/*
 * Record, key, and poपूर्णांकer address macros क्रम btree blocks.
 *
 * (note that some of these may appear unused, but they are used in userspace)
 */
#घोषणा XFS_REFCOUNT_REC_ADDR(block, index) \
	((काष्ठा xfs_refcount_rec *) \
		((अक्षर *)(block) + \
		 XFS_REFCOUNT_BLOCK_LEN + \
		 (((index) - 1) * माप(काष्ठा xfs_refcount_rec))))

#घोषणा XFS_REFCOUNT_KEY_ADDR(block, index) \
	((काष्ठा xfs_refcount_key *) \
		((अक्षर *)(block) + \
		 XFS_REFCOUNT_BLOCK_LEN + \
		 ((index) - 1) * माप(काष्ठा xfs_refcount_key)))

#घोषणा XFS_REFCOUNT_PTR_ADDR(block, index, maxrecs) \
	((xfs_refcount_ptr_t *) \
		((अक्षर *)(block) + \
		 XFS_REFCOUNT_BLOCK_LEN + \
		 (maxrecs) * माप(काष्ठा xfs_refcount_key) + \
		 ((index) - 1) * माप(xfs_refcount_ptr_t)))

बाह्य काष्ठा xfs_btree_cur *xfs_refcountbt_init_cursor(काष्ठा xfs_mount *mp,
		काष्ठा xfs_trans *tp, काष्ठा xfs_buf *agbp,
		xfs_agnumber_t agno);
काष्ठा xfs_btree_cur *xfs_refcountbt_stage_cursor(काष्ठा xfs_mount *mp,
		काष्ठा xbtree_afakeroot *afake, xfs_agnumber_t agno);
बाह्य पूर्णांक xfs_refcountbt_maxrecs(पूर्णांक blocklen, bool leaf);
बाह्य व्योम xfs_refcountbt_compute_maxlevels(काष्ठा xfs_mount *mp);

बाह्य xfs_extlen_t xfs_refcountbt_calc_size(काष्ठा xfs_mount *mp,
		अचिन्हित दीर्घ दीर्घ len);
बाह्य xfs_extlen_t xfs_refcountbt_max_size(काष्ठा xfs_mount *mp,
		xfs_agblock_t agblocks);

बाह्य पूर्णांक xfs_refcountbt_calc_reserves(काष्ठा xfs_mount *mp,
		काष्ठा xfs_trans *tp, xfs_agnumber_t agno, xfs_extlen_t *ask,
		xfs_extlen_t *used);

व्योम xfs_refcountbt_commit_staged_btree(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_trans *tp, काष्ठा xfs_buf *agbp);

#पूर्ण_अगर	/* __XFS_REFCOUNT_BTREE_H__ */
