<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000,2002-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_BMAP_BTREE_H__
#घोषणा __XFS_BMAP_BTREE_H__

काष्ठा xfs_btree_cur;
काष्ठा xfs_btree_block;
काष्ठा xfs_mount;
काष्ठा xfs_inode;
काष्ठा xfs_trans;

/*
 * Btree block header size depends on a superblock flag.
 */
#घोषणा XFS_BMBT_BLOCK_LEN(mp) \
	(xfs_sb_version_hascrc(&((mp)->m_sb)) ? \
		XFS_BTREE_LBLOCK_CRC_LEN : XFS_BTREE_LBLOCK_LEN)

#घोषणा XFS_BMBT_REC_ADDR(mp, block, index) \
	((xfs_bmbt_rec_t *) \
		((अक्षर *)(block) + \
		 XFS_BMBT_BLOCK_LEN(mp) + \
		 ((index) - 1) * माप(xfs_bmbt_rec_t)))

#घोषणा XFS_BMBT_KEY_ADDR(mp, block, index) \
	((xfs_bmbt_key_t *) \
		((अक्षर *)(block) + \
		 XFS_BMBT_BLOCK_LEN(mp) + \
		 ((index) - 1) * माप(xfs_bmbt_key_t)))

#घोषणा XFS_BMBT_PTR_ADDR(mp, block, index, maxrecs) \
	((xfs_bmbt_ptr_t *) \
		((अक्षर *)(block) + \
		 XFS_BMBT_BLOCK_LEN(mp) + \
		 (maxrecs) * माप(xfs_bmbt_key_t) + \
		 ((index) - 1) * माप(xfs_bmbt_ptr_t)))

#घोषणा XFS_BMDR_REC_ADDR(block, index) \
	((xfs_bmdr_rec_t *) \
		((अक्षर *)(block) + \
		 माप(काष्ठा xfs_bmdr_block) + \
	         ((index) - 1) * माप(xfs_bmdr_rec_t)))

#घोषणा XFS_BMDR_KEY_ADDR(block, index) \
	((xfs_bmdr_key_t *) \
		((अक्षर *)(block) + \
		 माप(काष्ठा xfs_bmdr_block) + \
		 ((index) - 1) * माप(xfs_bmdr_key_t)))

#घोषणा XFS_BMDR_PTR_ADDR(block, index, maxrecs) \
	((xfs_bmdr_ptr_t *) \
		((अक्षर *)(block) + \
		 माप(काष्ठा xfs_bmdr_block) + \
		 (maxrecs) * माप(xfs_bmdr_key_t) + \
		 ((index) - 1) * माप(xfs_bmdr_ptr_t)))

/*
 * These are to be used when we know the size of the block and
 * we करोn't have a cursor.
 */
#घोषणा XFS_BMAP_BROOT_PTR_ADDR(mp, bb, i, sz) \
	XFS_BMBT_PTR_ADDR(mp, bb, i, xfs_bmbt_maxrecs(mp, sz, 0))

#घोषणा XFS_BMAP_BROOT_SPACE_CALC(mp, nrecs) \
	(पूर्णांक)(XFS_BMBT_BLOCK_LEN(mp) + \
	       ((nrecs) * (माप(xfs_bmbt_key_t) + माप(xfs_bmbt_ptr_t))))

#घोषणा XFS_BMAP_BROOT_SPACE(mp, bb) \
	(XFS_BMAP_BROOT_SPACE_CALC(mp, be16_to_cpu((bb)->bb_numrecs)))
#घोषणा XFS_BMDR_SPACE_CALC(nrecs) \
	(पूर्णांक)(माप(xfs_bmdr_block_t) + \
	       ((nrecs) * (माप(xfs_bmbt_key_t) + माप(xfs_bmbt_ptr_t))))
#घोषणा XFS_BMAP_BMDR_SPACE(bb) \
	(XFS_BMDR_SPACE_CALC(be16_to_cpu((bb)->bb_numrecs)))

/*
 * Maximum number of bmap btree levels.
 */
#घोषणा XFS_BM_MAXLEVELS(mp,w)		((mp)->m_bm_maxlevels[(w)])

/*
 * Prototypes क्रम xfs_bmap.c to call.
 */
बाह्य व्योम xfs_bmdr_to_bmbt(काष्ठा xfs_inode *, xfs_bmdr_block_t *, पूर्णांक,
			काष्ठा xfs_btree_block *, पूर्णांक);

व्योम xfs_bmbt_disk_set_all(काष्ठा xfs_bmbt_rec *r, काष्ठा xfs_bmbt_irec *s);
बाह्य xfs_filblks_t xfs_bmbt_disk_get_blockcount(xfs_bmbt_rec_t *r);
बाह्य xfs_fileoff_t xfs_bmbt_disk_get_startoff(xfs_bmbt_rec_t *r);
बाह्य व्योम xfs_bmbt_disk_get_all(xfs_bmbt_rec_t *r, xfs_bmbt_irec_t *s);

बाह्य व्योम xfs_bmbt_to_bmdr(काष्ठा xfs_mount *, काष्ठा xfs_btree_block *, पूर्णांक,
			xfs_bmdr_block_t *, पूर्णांक);

बाह्य पूर्णांक xfs_bmbt_get_maxrecs(काष्ठा xfs_btree_cur *, पूर्णांक level);
बाह्य पूर्णांक xfs_bmdr_maxrecs(पूर्णांक blocklen, पूर्णांक leaf);
बाह्य पूर्णांक xfs_bmbt_maxrecs(काष्ठा xfs_mount *, पूर्णांक blocklen, पूर्णांक leaf);

बाह्य पूर्णांक xfs_bmbt_change_owner(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
				 पूर्णांक whichविभाजन, xfs_ino_t new_owner,
				 काष्ठा list_head *buffer_list);

बाह्य काष्ठा xfs_btree_cur *xfs_bmbt_init_cursor(काष्ठा xfs_mount *,
		काष्ठा xfs_trans *, काष्ठा xfs_inode *, पूर्णांक);

बाह्य अचिन्हित दीर्घ दीर्घ xfs_bmbt_calc_size(काष्ठा xfs_mount *mp,
		अचिन्हित दीर्घ दीर्घ len);

#पूर्ण_अगर	/* __XFS_BMAP_BTREE_H__ */
