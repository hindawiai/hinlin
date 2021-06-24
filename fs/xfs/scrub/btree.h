<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_SCRUB_BTREE_H__
#घोषणा __XFS_SCRUB_BTREE_H__

/* btree scrub */

/* Check क्रम btree operation errors. */
bool xchk_btree_process_error(काष्ठा xfs_scrub *sc,
		काष्ठा xfs_btree_cur *cur, पूर्णांक level, पूर्णांक *error);

/* Check क्रम btree xref operation errors. */
bool xchk_btree_xref_process_error(काष्ठा xfs_scrub *sc,
		काष्ठा xfs_btree_cur *cur, पूर्णांक level, पूर्णांक *error);

/* Check क्रम btree corruption. */
व्योम xchk_btree_set_corrupt(काष्ठा xfs_scrub *sc,
		काष्ठा xfs_btree_cur *cur, पूर्णांक level);

/* Check क्रम btree xref discrepancies. */
व्योम xchk_btree_xref_set_corrupt(काष्ठा xfs_scrub *sc,
		काष्ठा xfs_btree_cur *cur, पूर्णांक level);

काष्ठा xchk_btree;
प्रकार पूर्णांक (*xchk_btree_rec_fn)(
	काष्ठा xchk_btree	*bs,
	जोड़ xfs_btree_rec	*rec);

काष्ठा xchk_btree अणु
	/* caller-provided scrub state */
	काष्ठा xfs_scrub		*sc;
	काष्ठा xfs_btree_cur		*cur;
	xchk_btree_rec_fn		scrub_rec;
	स्थिर काष्ठा xfs_owner_info	*oinfo;
	व्योम				*निजी;

	/* पूर्णांकernal scrub state */
	जोड़ xfs_btree_rec		lastrec;
	bool				firstrec;
	जोड़ xfs_btree_key		lastkey[XFS_BTREE_MAXLEVELS];
	bool				firstkey[XFS_BTREE_MAXLEVELS];
	काष्ठा list_head		to_check;
पूर्ण;
पूर्णांक xchk_btree(काष्ठा xfs_scrub *sc, काष्ठा xfs_btree_cur *cur,
		xchk_btree_rec_fn scrub_fn, स्थिर काष्ठा xfs_owner_info *oinfo,
		व्योम *निजी);

#पूर्ण_अगर /* __XFS_SCRUB_BTREE_H__ */
