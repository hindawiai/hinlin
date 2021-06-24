<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_IALLOC_BTREE_H__
#घोषणा	__XFS_IALLOC_BTREE_H__

/*
 * Inode map on-disk काष्ठाures
 */

काष्ठा xfs_buf;
काष्ठा xfs_btree_cur;
काष्ठा xfs_mount;

/*
 * Btree block header size depends on a superblock flag.
 */
#घोषणा XFS_INOBT_BLOCK_LEN(mp) \
	(xfs_sb_version_hascrc(&((mp)->m_sb)) ? \
		XFS_BTREE_SBLOCK_CRC_LEN : XFS_BTREE_SBLOCK_LEN)

/*
 * Record, key, and poपूर्णांकer address macros क्रम btree blocks.
 *
 * (note that some of these may appear unused, but they are used in userspace)
 */
#घोषणा XFS_INOBT_REC_ADDR(mp, block, index) \
	((xfs_inobt_rec_t *) \
		((अक्षर *)(block) + \
		 XFS_INOBT_BLOCK_LEN(mp) + \
		 (((index) - 1) * माप(xfs_inobt_rec_t))))

#घोषणा XFS_INOBT_KEY_ADDR(mp, block, index) \
	((xfs_inobt_key_t *) \
		((अक्षर *)(block) + \
		 XFS_INOBT_BLOCK_LEN(mp) + \
		 ((index) - 1) * माप(xfs_inobt_key_t)))

#घोषणा XFS_INOBT_PTR_ADDR(mp, block, index, maxrecs) \
	((xfs_inobt_ptr_t *) \
		((अक्षर *)(block) + \
		 XFS_INOBT_BLOCK_LEN(mp) + \
		 (maxrecs) * माप(xfs_inobt_key_t) + \
		 ((index) - 1) * माप(xfs_inobt_ptr_t)))

बाह्य काष्ठा xfs_btree_cur *xfs_inobt_init_cursor(काष्ठा xfs_mount *,
		काष्ठा xfs_trans *, काष्ठा xfs_buf *, xfs_agnumber_t,
		xfs_btnum_t);
काष्ठा xfs_btree_cur *xfs_inobt_stage_cursor(काष्ठा xfs_mount *mp,
		काष्ठा xbtree_afakeroot *afake, xfs_agnumber_t agno,
		xfs_btnum_t btnum);
बाह्य पूर्णांक xfs_inobt_maxrecs(काष्ठा xfs_mount *, पूर्णांक, पूर्णांक);

/* ir_holemask to inode allocation biपंचांगap conversion */
uपूर्णांक64_t xfs_inobt_irec_to_allocmask(काष्ठा xfs_inobt_rec_incore *);

#अगर defined(DEBUG) || defined(XFS_WARN)
पूर्णांक xfs_inobt_rec_check_count(काष्ठा xfs_mount *,
			      काष्ठा xfs_inobt_rec_incore *);
#अन्यथा
#घोषणा xfs_inobt_rec_check_count(mp, rec)	0
#पूर्ण_अगर	/* DEBUG */

पूर्णांक xfs_finobt_calc_reserves(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		xfs_agnumber_t agno, xfs_extlen_t *ask, xfs_extlen_t *used);
बाह्य xfs_extlen_t xfs_iallocbt_calc_size(काष्ठा xfs_mount *mp,
		अचिन्हित दीर्घ दीर्घ len);
पूर्णांक xfs_inobt_cur(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		xfs_agnumber_t agno, xfs_btnum_t btnum,
		काष्ठा xfs_btree_cur **curpp, काष्ठा xfs_buf **agi_bpp);

व्योम xfs_inobt_commit_staged_btree(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_trans *tp, काष्ठा xfs_buf *agbp);

#पूर्ण_अगर	/* __XFS_IALLOC_BTREE_H__ */
