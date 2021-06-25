<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_सूची2_PRIV_H__
#घोषणा __XFS_सूची2_PRIV_H__

काष्ठा dir_context;

/*
 * In-core version of the leaf and मुक्त block headers to असलtract the
 * dअगरferences in the v2 and v3 disk क्रमmat of the headers.
 */
काष्ठा xfs_dir3_icleaf_hdr अणु
	uपूर्णांक32_t		क्रमw;
	uपूर्णांक32_t		back;
	uपूर्णांक16_t		magic;
	uपूर्णांक16_t		count;
	uपूर्णांक16_t		stale;

	/*
	 * Poपूर्णांकer to the on-disk क्रमmat entries, which are behind the
	 * variable size (v4 vs v5) header in the on-disk block.
	 */
	काष्ठा xfs_dir2_leaf_entry *ents;
पूर्ण;

काष्ठा xfs_dir3_icमुक्त_hdr अणु
	uपूर्णांक32_t		magic;
	uपूर्णांक32_t		firstdb;
	uपूर्णांक32_t		nvalid;
	uपूर्णांक32_t		nused;

	/*
	 * Poपूर्णांकer to the on-disk क्रमmat entries, which are behind the
	 * variable size (v4 vs v5) header in the on-disk block.
	 */
	__be16			*bests;
पूर्ण;

/* xfs_dir2.c */
xfs_dahash_t xfs_ascii_ci_hashname(काष्ठा xfs_name *name);
क्रमागत xfs_dacmp xfs_ascii_ci_compname(काष्ठा xfs_da_args *args,
		स्थिर अचिन्हित अक्षर *name, पूर्णांक len);
बाह्य पूर्णांक xfs_dir2_grow_inode(काष्ठा xfs_da_args *args, पूर्णांक space,
				xfs_dir2_db_t *dbp);
बाह्य पूर्णांक xfs_dir_cilookup_result(काष्ठा xfs_da_args *args,
				स्थिर अचिन्हित अक्षर *name, पूर्णांक len);


/* xfs_dir2_block.c */
बाह्य पूर्णांक xfs_dir3_block_पढ़ो(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
			       काष्ठा xfs_buf **bpp);
बाह्य पूर्णांक xfs_dir2_block_addname(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_block_lookup(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_block_हटाओname(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_block_replace(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_leaf_to_block(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *lbp, काष्ठा xfs_buf *dbp);

/* xfs_dir2_data.c */
काष्ठा xfs_dir2_data_मुक्त *xfs_dir2_data_bestमुक्त_p(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir2_data_hdr *hdr);
__be16 *xfs_dir2_data_entry_tag_p(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir2_data_entry *dep);
uपूर्णांक8_t xfs_dir2_data_get_ftype(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir2_data_entry *dep);
व्योम xfs_dir2_data_put_ftype(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir2_data_entry *dep, uपूर्णांक8_t ftype);

#अगर_घोषित DEBUG
बाह्य व्योम xfs_dir3_data_check(काष्ठा xfs_inode *dp, काष्ठा xfs_buf *bp);
#अन्यथा
#घोषणा	xfs_dir3_data_check(dp,bp)
#पूर्ण_अगर

बाह्य xfs_failaddr_t __xfs_dir3_data_check(काष्ठा xfs_inode *dp,
		काष्ठा xfs_buf *bp);
पूर्णांक xfs_dir3_data_पढ़ो(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
		xfs_dablk_t bno, अचिन्हित पूर्णांक flags, काष्ठा xfs_buf **bpp);
पूर्णांक xfs_dir3_data_पढ़ोahead(काष्ठा xfs_inode *dp, xfs_dablk_t bno,
		अचिन्हित पूर्णांक flags);

बाह्य काष्ठा xfs_dir2_data_मुक्त *
xfs_dir2_data_मुक्तinsert(काष्ठा xfs_dir2_data_hdr *hdr,
		काष्ठा xfs_dir2_data_मुक्त *bf, काष्ठा xfs_dir2_data_unused *dup,
		पूर्णांक *loghead);
बाह्य पूर्णांक xfs_dir3_data_init(काष्ठा xfs_da_args *args, xfs_dir2_db_t blkno,
		काष्ठा xfs_buf **bpp);

/* xfs_dir2_leaf.c */
व्योम xfs_dir2_leaf_hdr_from_disk(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir3_icleaf_hdr *to, काष्ठा xfs_dir2_leaf *from);
व्योम xfs_dir2_leaf_hdr_to_disk(काष्ठा xfs_mount *mp, काष्ठा xfs_dir2_leaf *to,
		काष्ठा xfs_dir3_icleaf_hdr *from);
पूर्णांक xfs_dir3_leaf_पढ़ो(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
		xfs_dablk_t fbno, काष्ठा xfs_buf **bpp);
पूर्णांक xfs_dir3_leafn_पढ़ो(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
		xfs_dablk_t fbno, काष्ठा xfs_buf **bpp);
बाह्य पूर्णांक xfs_dir2_block_to_leaf(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *dbp);
बाह्य पूर्णांक xfs_dir2_leaf_addname(काष्ठा xfs_da_args *args);
बाह्य व्योम xfs_dir3_leaf_compact(काष्ठा xfs_da_args *args,
		काष्ठा xfs_dir3_icleaf_hdr *leafhdr, काष्ठा xfs_buf *bp);
बाह्य व्योम xfs_dir3_leaf_compact_x1(काष्ठा xfs_dir3_icleaf_hdr *leafhdr,
		काष्ठा xfs_dir2_leaf_entry *ents, पूर्णांक *indexp,
		पूर्णांक *lowstalep, पूर्णांक *highstalep, पूर्णांक *lowlogp, पूर्णांक *highlogp);
बाह्य पूर्णांक xfs_dir3_leaf_get_buf(काष्ठा xfs_da_args *args, xfs_dir2_db_t bno,
		काष्ठा xfs_buf **bpp, uपूर्णांक16_t magic);
बाह्य व्योम xfs_dir3_leaf_log_ents(काष्ठा xfs_da_args *args,
		काष्ठा xfs_dir3_icleaf_hdr *hdr, काष्ठा xfs_buf *bp, पूर्णांक first,
		पूर्णांक last);
बाह्य व्योम xfs_dir3_leaf_log_header(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *bp);
बाह्य पूर्णांक xfs_dir2_leaf_lookup(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_leaf_हटाओname(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_leaf_replace(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_leaf_search_hash(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *lbp);
बाह्य पूर्णांक xfs_dir2_leaf_trim_data(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *lbp, xfs_dir2_db_t db);
बाह्य काष्ठा xfs_dir2_leaf_entry *
xfs_dir3_leaf_find_entry(काष्ठा xfs_dir3_icleaf_hdr *leafhdr,
		काष्ठा xfs_dir2_leaf_entry *ents, पूर्णांक index, पूर्णांक compact,
		पूर्णांक lowstale, पूर्णांक highstale, पूर्णांक *lfloglow, पूर्णांक *lfloghigh);
बाह्य पूर्णांक xfs_dir2_node_to_leaf(काष्ठा xfs_da_state *state);

बाह्य xfs_failaddr_t xfs_dir3_leaf_check_पूर्णांक(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir3_icleaf_hdr *hdr, काष्ठा xfs_dir2_leaf *leaf,
		bool expensive_checks);

/* xfs_dir2_node.c */
व्योम xfs_dir2_मुक्त_hdr_from_disk(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir3_icमुक्त_hdr *to, काष्ठा xfs_dir2_मुक्त *from);
बाह्य पूर्णांक xfs_dir2_leaf_to_node(काष्ठा xfs_da_args *args,
		काष्ठा xfs_buf *lbp);
बाह्य xfs_dahash_t xfs_dir2_leaf_lasthash(काष्ठा xfs_inode *dp,
		काष्ठा xfs_buf *bp, पूर्णांक *count);
बाह्य पूर्णांक xfs_dir2_leafn_lookup_पूर्णांक(काष्ठा xfs_buf *bp,
		काष्ठा xfs_da_args *args, पूर्णांक *indexp,
		काष्ठा xfs_da_state *state);
बाह्य पूर्णांक xfs_dir2_leafn_order(काष्ठा xfs_inode *dp, काष्ठा xfs_buf *leaf1_bp,
		काष्ठा xfs_buf *leaf2_bp);
बाह्य पूर्णांक xfs_dir2_leafn_split(काष्ठा xfs_da_state *state,
	काष्ठा xfs_da_state_blk *oldblk, काष्ठा xfs_da_state_blk *newblk);
बाह्य पूर्णांक xfs_dir2_leafn_toosmall(काष्ठा xfs_da_state *state, पूर्णांक *action);
बाह्य व्योम xfs_dir2_leafn_unbalance(काष्ठा xfs_da_state *state,
		काष्ठा xfs_da_state_blk *drop_blk,
		काष्ठा xfs_da_state_blk *save_blk);
बाह्य पूर्णांक xfs_dir2_node_addname(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_node_lookup(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_node_हटाओname(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_node_replace(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_node_trim_मुक्त(काष्ठा xfs_da_args *args, xfs_fileoff_t fo,
		पूर्णांक *rvalp);
बाह्य पूर्णांक xfs_dir2_मुक्त_पढ़ो(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
		xfs_dablk_t fbno, काष्ठा xfs_buf **bpp);

/* xfs_dir2_sf.c */
xfs_ino_t xfs_dir2_sf_get_ino(काष्ठा xfs_mount *mp, काष्ठा xfs_dir2_sf_hdr *hdr,
		काष्ठा xfs_dir2_sf_entry *sfep);
xfs_ino_t xfs_dir2_sf_get_parent_ino(काष्ठा xfs_dir2_sf_hdr *hdr);
व्योम xfs_dir2_sf_put_parent_ino(काष्ठा xfs_dir2_sf_hdr *hdr, xfs_ino_t ino);
uपूर्णांक8_t xfs_dir2_sf_get_ftype(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir2_sf_entry *sfep);
काष्ठा xfs_dir2_sf_entry *xfs_dir2_sf_nextentry(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir2_sf_hdr *hdr, काष्ठा xfs_dir2_sf_entry *sfep);
बाह्य पूर्णांक xfs_dir2_block_sfsize(काष्ठा xfs_inode *dp,
		काष्ठा xfs_dir2_data_hdr *block, काष्ठा xfs_dir2_sf_hdr *sfhp);
बाह्य पूर्णांक xfs_dir2_block_to_sf(काष्ठा xfs_da_args *args, काष्ठा xfs_buf *bp,
		पूर्णांक size, xfs_dir2_sf_hdr_t *sfhp);
बाह्य पूर्णांक xfs_dir2_sf_addname(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_sf_create(काष्ठा xfs_da_args *args, xfs_ino_t pino);
बाह्य पूर्णांक xfs_dir2_sf_lookup(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_sf_हटाओname(काष्ठा xfs_da_args *args);
बाह्य पूर्णांक xfs_dir2_sf_replace(काष्ठा xfs_da_args *args);
बाह्य xfs_failaddr_t xfs_dir2_sf_verअगरy(काष्ठा xfs_inode *ip);
पूर्णांक xfs_dir2_sf_entsize(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir2_sf_hdr *hdr, पूर्णांक len);
व्योम xfs_dir2_sf_put_ino(काष्ठा xfs_mount *mp, काष्ठा xfs_dir2_sf_hdr *hdr,
		काष्ठा xfs_dir2_sf_entry *sfep, xfs_ino_t ino);
व्योम xfs_dir2_sf_put_ftype(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dir2_sf_entry *sfep, uपूर्णांक8_t ftype);

/* xfs_dir2_सूची_पढ़ो.c */
बाह्य पूर्णांक xfs_सूची_पढ़ो(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *dp,
		       काष्ठा dir_context *ctx, माप_प्रकार bufsize);

अटल अंतरभूत अचिन्हित पूर्णांक
xfs_dir2_data_entsize(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		namelen)
अणु
	अचिन्हित पूर्णांक		len;

	len = दुरत्व(काष्ठा xfs_dir2_data_entry, name[0]) + namelen +
			माप(xfs_dir2_data_off_t) /* tag */;
	अगर (xfs_sb_version_hasftype(&mp->m_sb))
		len += माप(uपूर्णांक8_t);
	वापस round_up(len, XFS_सूची2_DATA_ALIGN);
पूर्ण

xfs_dahash_t xfs_dir2_hashname(काष्ठा xfs_mount *mp, काष्ठा xfs_name *name);
क्रमागत xfs_dacmp xfs_dir2_compname(काष्ठा xfs_da_args *args,
		स्थिर अचिन्हित अक्षर *name, पूर्णांक len);

#पूर्ण_अगर /* __XFS_सूची2_PRIV_H__ */
