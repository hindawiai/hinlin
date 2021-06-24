<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Red Hat, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_RMAP_BTREE_H__
#घोषणा __XFS_RMAP_BTREE_H__

काष्ठा xfs_buf;
काष्ठा xfs_btree_cur;
काष्ठा xfs_mount;
काष्ठा xbtree_afakeroot;

/* rmaps only exist on crc enabled fileप्रणालीs */
#घोषणा XFS_RMAP_BLOCK_LEN	XFS_BTREE_SBLOCK_CRC_LEN

/*
 * Record, key, and poपूर्णांकer address macros क्रम btree blocks.
 *
 * (note that some of these may appear unused, but they are used in userspace)
 */
#घोषणा XFS_RMAP_REC_ADDR(block, index) \
	((काष्ठा xfs_rmap_rec *) \
		((अक्षर *)(block) + XFS_RMAP_BLOCK_LEN + \
		 (((index) - 1) * माप(काष्ठा xfs_rmap_rec))))

#घोषणा XFS_RMAP_KEY_ADDR(block, index) \
	((काष्ठा xfs_rmap_key *) \
		((अक्षर *)(block) + XFS_RMAP_BLOCK_LEN + \
		 ((index) - 1) * 2 * माप(काष्ठा xfs_rmap_key)))

#घोषणा XFS_RMAP_HIGH_KEY_ADDR(block, index) \
	((काष्ठा xfs_rmap_key *) \
		((अक्षर *)(block) + XFS_RMAP_BLOCK_LEN + \
		 माप(काष्ठा xfs_rmap_key) + \
		 ((index) - 1) * 2 * माप(काष्ठा xfs_rmap_key)))

#घोषणा XFS_RMAP_PTR_ADDR(block, index, maxrecs) \
	((xfs_rmap_ptr_t *) \
		((अक्षर *)(block) + XFS_RMAP_BLOCK_LEN + \
		 (maxrecs) * 2 * माप(काष्ठा xfs_rmap_key) + \
		 ((index) - 1) * माप(xfs_rmap_ptr_t)))

काष्ठा xfs_btree_cur *xfs_rmapbt_init_cursor(काष्ठा xfs_mount *mp,
				काष्ठा xfs_trans *tp, काष्ठा xfs_buf *bp,
				xfs_agnumber_t agno);
काष्ठा xfs_btree_cur *xfs_rmapbt_stage_cursor(काष्ठा xfs_mount *mp,
		काष्ठा xbtree_afakeroot *afake, xfs_agnumber_t agno);
व्योम xfs_rmapbt_commit_staged_btree(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_trans *tp, काष्ठा xfs_buf *agbp);
पूर्णांक xfs_rmapbt_maxrecs(पूर्णांक blocklen, पूर्णांक leaf);
बाह्य व्योम xfs_rmapbt_compute_maxlevels(काष्ठा xfs_mount *mp);

बाह्य xfs_extlen_t xfs_rmapbt_calc_size(काष्ठा xfs_mount *mp,
		अचिन्हित दीर्घ दीर्घ len);
बाह्य xfs_extlen_t xfs_rmapbt_max_size(काष्ठा xfs_mount *mp,
		xfs_agblock_t agblocks);

बाह्य पूर्णांक xfs_rmapbt_calc_reserves(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		xfs_agnumber_t agno, xfs_extlen_t *ask, xfs_extlen_t *used);

#पूर्ण_अगर	/* __XFS_RMAP_BTREE_H__ */
