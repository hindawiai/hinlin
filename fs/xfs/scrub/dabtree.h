<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_SCRUB_DABTREE_H__
#घोषणा __XFS_SCRUB_DABTREE_H__

/* dir/attr btree */

काष्ठा xchk_da_btree अणु
	काष्ठा xfs_da_args	dargs;
	xfs_dahash_t		hashes[XFS_DA_NODE_MAXDEPTH];
	पूर्णांक			maxrecs[XFS_DA_NODE_MAXDEPTH];
	काष्ठा xfs_da_state	*state;
	काष्ठा xfs_scrub	*sc;
	व्योम			*निजी;

	/*
	 * Lowest and highest directory block address in which we expect
	 * to find dir/attr btree node blocks.  For a directory this
	 * (presumably) means between LEAF_OFFSET and FREE_OFFSET; क्रम
	 * attributes there is no limit.
	 */
	xfs_dablk_t		lowest;
	xfs_dablk_t		highest;

	पूर्णांक			tree_level;
पूर्ण;

प्रकार पूर्णांक (*xchk_da_btree_rec_fn)(काष्ठा xchk_da_btree *ds, पूर्णांक level);

/* Check क्रम da btree operation errors. */
bool xchk_da_process_error(काष्ठा xchk_da_btree *ds, पूर्णांक level, पूर्णांक *error);

/* Check क्रम da btree corruption. */
व्योम xchk_da_set_corrupt(काष्ठा xchk_da_btree *ds, पूर्णांक level);

पूर्णांक xchk_da_btree_hash(काष्ठा xchk_da_btree *ds, पूर्णांक level, __be32 *hashp);
पूर्णांक xchk_da_btree(काष्ठा xfs_scrub *sc, पूर्णांक whichविभाजन,
		xchk_da_btree_rec_fn scrub_fn, व्योम *निजी);

#पूर्ण_अगर /* __XFS_SCRUB_DABTREE_H__ */
