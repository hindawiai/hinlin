<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_ALLOC_BTREE_H__
#घोषणा	__XFS_ALLOC_BTREE_H__

/*
 * Freespace on-disk काष्ठाures
 */

काष्ठा xfs_buf;
काष्ठा xfs_btree_cur;
काष्ठा xfs_mount;
काष्ठा xbtree_afakeroot;

/*
 * Btree block header size depends on a superblock flag.
 */
#घोषणा XFS_ALLOC_BLOCK_LEN(mp) \
	(xfs_sb_version_hascrc(&((mp)->m_sb)) ? \
		XFS_BTREE_SBLOCK_CRC_LEN : XFS_BTREE_SBLOCK_LEN)

/*
 * Record, key, and poपूर्णांकer address macros क्रम btree blocks.
 *
 * (note that some of these may appear unused, but they are used in userspace)
 */
#घोषणा XFS_ALLOC_REC_ADDR(mp, block, index) \
	((xfs_alloc_rec_t *) \
		((अक्षर *)(block) + \
		 XFS_ALLOC_BLOCK_LEN(mp) + \
		 (((index) - 1) * माप(xfs_alloc_rec_t))))

#घोषणा XFS_ALLOC_KEY_ADDR(mp, block, index) \
	((xfs_alloc_key_t *) \
		((अक्षर *)(block) + \
		 XFS_ALLOC_BLOCK_LEN(mp) + \
		 ((index) - 1) * माप(xfs_alloc_key_t)))

#घोषणा XFS_ALLOC_PTR_ADDR(mp, block, index, maxrecs) \
	((xfs_alloc_ptr_t *) \
		((अक्षर *)(block) + \
		 XFS_ALLOC_BLOCK_LEN(mp) + \
		 (maxrecs) * माप(xfs_alloc_key_t) + \
		 ((index) - 1) * माप(xfs_alloc_ptr_t)))

बाह्य काष्ठा xfs_btree_cur *xfs_allocbt_init_cursor(काष्ठा xfs_mount *,
		काष्ठा xfs_trans *, काष्ठा xfs_buf *,
		xfs_agnumber_t, xfs_btnum_t);
काष्ठा xfs_btree_cur *xfs_allocbt_stage_cursor(काष्ठा xfs_mount *mp,
		काष्ठा xbtree_afakeroot *afake, xfs_agnumber_t agno,
		xfs_btnum_t btnum);
बाह्य पूर्णांक xfs_allocbt_maxrecs(काष्ठा xfs_mount *, पूर्णांक, पूर्णांक);
बाह्य xfs_extlen_t xfs_allocbt_calc_size(काष्ठा xfs_mount *mp,
		अचिन्हित दीर्घ दीर्घ len);

व्योम xfs_allocbt_commit_staged_btree(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_trans *tp, काष्ठा xfs_buf *agbp);

#पूर्ण_अगर	/* __XFS_ALLOC_BTREE_H__ */
