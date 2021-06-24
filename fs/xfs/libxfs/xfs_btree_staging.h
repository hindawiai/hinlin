<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2020 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_BTREE_STAGING_H__
#घोषणा __XFS_BTREE_STAGING_H__

/* Fake root क्रम an AG-rooted btree. */
काष्ठा xbtree_afakeroot अणु
	/* AG block number of the new btree root. */
	xfs_agblock_t		af_root;

	/* Height of the new btree. */
	अचिन्हित पूर्णांक		af_levels;

	/* Number of blocks used by the btree. */
	अचिन्हित पूर्णांक		af_blocks;
पूर्ण;

/* Cursor पूर्णांकeractions with fake roots क्रम AG-rooted btrees. */
व्योम xfs_btree_stage_afakeroot(काष्ठा xfs_btree_cur *cur,
		काष्ठा xbtree_afakeroot *afake);
व्योम xfs_btree_commit_afakeroot(काष्ठा xfs_btree_cur *cur, काष्ठा xfs_trans *tp,
		काष्ठा xfs_buf *agbp, स्थिर काष्ठा xfs_btree_ops *ops);

/* Fake root क्रम an inode-rooted btree. */
काष्ठा xbtree_अगरakeroot अणु
	/* Fake inode विभाजन. */
	काष्ठा xfs_अगरork	*अगर_विभाजन;

	/* Number of blocks used by the btree. */
	पूर्णांक64_t			अगर_blocks;

	/* Height of the new btree. */
	अचिन्हित पूर्णांक		अगर_levels;

	/* Number of bytes available क्रम this विभाजन in the inode. */
	अचिन्हित पूर्णांक		अगर_विभाजन_size;

	/* Fork क्रमmat. */
	अचिन्हित पूर्णांक		अगर_क्रमmat;

	/* Number of records. */
	अचिन्हित पूर्णांक		अगर_extents;
पूर्ण;

/* Cursor पूर्णांकeractions with fake roots क्रम inode-rooted btrees. */
व्योम xfs_btree_stage_अगरakeroot(काष्ठा xfs_btree_cur *cur,
		काष्ठा xbtree_अगरakeroot *अगरake,
		काष्ठा xfs_btree_ops **new_ops);
व्योम xfs_btree_commit_अगरakeroot(काष्ठा xfs_btree_cur *cur, काष्ठा xfs_trans *tp,
		पूर्णांक whichविभाजन, स्थिर काष्ठा xfs_btree_ops *ops);

/* Bulk loading of staged btrees. */
प्रकार पूर्णांक (*xfs_btree_bload_get_record_fn)(काष्ठा xfs_btree_cur *cur, व्योम *priv);
प्रकार पूर्णांक (*xfs_btree_bload_claim_block_fn)(काष्ठा xfs_btree_cur *cur,
		जोड़ xfs_btree_ptr *ptr, व्योम *priv);
प्रकार माप_प्रकार (*xfs_btree_bload_iroot_size_fn)(काष्ठा xfs_btree_cur *cur,
		अचिन्हित पूर्णांक nr_this_level, व्योम *priv);

काष्ठा xfs_btree_bload अणु
	/*
	 * This function will be called nr_records बार to load records पूर्णांकo
	 * the btree.  The function करोes this by setting the cursor's bc_rec
	 * field in in-core क्रमmat.  Records must be वापसed in sort order.
	 */
	xfs_btree_bload_get_record_fn	get_record;

	/*
	 * This function will be called nr_blocks बार to obtain a poपूर्णांकer
	 * to a new btree block on disk.  Callers must pपुनः_स्मृतिate all space
	 * क्रम the new btree beक्रमe calling xfs_btree_bload, and this function
	 * is what claims that reservation.
	 */
	xfs_btree_bload_claim_block_fn	claim_block;

	/*
	 * This function should वापस the size of the in-core btree root
	 * block.  It is only necessary क्रम XFS_BTREE_ROOT_IN_INODE btree
	 * types.
	 */
	xfs_btree_bload_iroot_size_fn	iroot_size;

	/*
	 * The caller should set this to the number of records that will be
	 * stored in the new btree.
	 */
	uपूर्णांक64_t			nr_records;

	/*
	 * Number of मुक्त records to leave in each leaf block.  If the caller
	 * sets this to -1, the slack value will be calculated to be halfway
	 * between maxrecs and minrecs.  This typically leaves the block 75%
	 * full.  Note that slack values are not enक्रमced on inode root blocks.
	 */
	पूर्णांक				leaf_slack;

	/*
	 * Number of मुक्त key/ptrs pairs to leave in each node block.  This
	 * field has the same semantics as leaf_slack.
	 */
	पूर्णांक				node_slack;

	/*
	 * The xfs_btree_bload_compute_geometry function will set this to the
	 * number of btree blocks needed to store nr_records records.
	 */
	uपूर्णांक64_t			nr_blocks;

	/*
	 * The xfs_btree_bload_compute_geometry function will set this to the
	 * height of the new btree.
	 */
	अचिन्हित पूर्णांक			btree_height;
पूर्ण;

पूर्णांक xfs_btree_bload_compute_geometry(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_btree_bload *bbl, uपूर्णांक64_t nr_records);
पूर्णांक xfs_btree_bload(काष्ठा xfs_btree_cur *cur, काष्ठा xfs_btree_bload *bbl,
		व्योम *priv);

#पूर्ण_अगर	/* __XFS_BTREE_STAGING_H__ */
