<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_REFCOUNT_H__
#घोषणा __XFS_REFCOUNT_H__

बाह्य पूर्णांक xfs_refcount_lookup_le(काष्ठा xfs_btree_cur *cur,
		xfs_agblock_t bno, पूर्णांक *stat);
बाह्य पूर्णांक xfs_refcount_lookup_ge(काष्ठा xfs_btree_cur *cur,
		xfs_agblock_t bno, पूर्णांक *stat);
बाह्य पूर्णांक xfs_refcount_lookup_eq(काष्ठा xfs_btree_cur *cur,
		xfs_agblock_t bno, पूर्णांक *stat);
बाह्य पूर्णांक xfs_refcount_get_rec(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_refcount_irec *irec, पूर्णांक *stat);

क्रमागत xfs_refcount_पूर्णांकent_type अणु
	XFS_REFCOUNT_INCREASE = 1,
	XFS_REFCOUNT_DECREASE,
	XFS_REFCOUNT_ALLOC_COW,
	XFS_REFCOUNT_FREE_COW,
पूर्ण;

काष्ठा xfs_refcount_पूर्णांकent अणु
	काष्ठा list_head			ri_list;
	क्रमागत xfs_refcount_पूर्णांकent_type		ri_type;
	xfs_fsblock_t				ri_startblock;
	xfs_extlen_t				ri_blockcount;
पूर्ण;

व्योम xfs_refcount_increase_extent(काष्ठा xfs_trans *tp,
		काष्ठा xfs_bmbt_irec *irec);
व्योम xfs_refcount_decrease_extent(काष्ठा xfs_trans *tp,
		काष्ठा xfs_bmbt_irec *irec);

बाह्य व्योम xfs_refcount_finish_one_cleanup(काष्ठा xfs_trans *tp,
		काष्ठा xfs_btree_cur *rcur, पूर्णांक error);
बाह्य पूर्णांक xfs_refcount_finish_one(काष्ठा xfs_trans *tp,
		क्रमागत xfs_refcount_पूर्णांकent_type type, xfs_fsblock_t startblock,
		xfs_extlen_t blockcount, xfs_fsblock_t *new_fsb,
		xfs_extlen_t *new_len, काष्ठा xfs_btree_cur **pcur);

बाह्य पूर्णांक xfs_refcount_find_shared(काष्ठा xfs_btree_cur *cur,
		xfs_agblock_t agbno, xfs_extlen_t aglen, xfs_agblock_t *fbno,
		xfs_extlen_t *flen, bool find_end_of_shared);

व्योम xfs_refcount_alloc_cow_extent(काष्ठा xfs_trans *tp, xfs_fsblock_t fsb,
		xfs_extlen_t len);
व्योम xfs_refcount_मुक्त_cow_extent(काष्ठा xfs_trans *tp, xfs_fsblock_t fsb,
		xfs_extlen_t len);
बाह्य पूर्णांक xfs_refcount_recover_cow_leftovers(काष्ठा xfs_mount *mp,
		xfs_agnumber_t agno);

/*
 * While we're adjusting the refcounts records of an extent, we have
 * to keep an eye on the number of extents we're dirtying -- run too
 * many in a single transaction and we'll exceed the transaction's
 * reservation and crash the fs.  Each record adds 12 bytes to the
 * log (plus any key updates) so we'll conservatively assume 32 bytes
 * per record.  We must also leave space क्रम btree splits on both ends
 * of the range and space क्रम the CUD and a new CUI.
 */
#घोषणा XFS_REFCOUNT_ITEM_OVERHEAD	32

अटल अंतरभूत xfs_fileoff_t xfs_refcount_max_unmap(पूर्णांक log_res)
अणु
	वापस (log_res * 3 / 4) / XFS_REFCOUNT_ITEM_OVERHEAD;
पूर्ण

बाह्य पूर्णांक xfs_refcount_has_record(काष्ठा xfs_btree_cur *cur,
		xfs_agblock_t bno, xfs_extlen_t len, bool *exists);
जोड़ xfs_btree_rec;
बाह्य व्योम xfs_refcount_btrec_to_irec(जोड़ xfs_btree_rec *rec,
		काष्ठा xfs_refcount_irec *irec);
बाह्य पूर्णांक xfs_refcount_insert(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_refcount_irec *irec, पूर्णांक *stat);

#पूर्ण_अगर	/* __XFS_REFCOUNT_H__ */
