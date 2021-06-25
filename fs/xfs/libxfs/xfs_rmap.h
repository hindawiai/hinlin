<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_RMAP_H__
#घोषणा __XFS_RMAP_H__

अटल अंतरभूत व्योम
xfs_rmap_ino_bmbt_owner(
	काष्ठा xfs_owner_info	*oi,
	xfs_ino_t		ino,
	पूर्णांक			whichविभाजन)
अणु
	oi->oi_owner = ino;
	oi->oi_offset = 0;
	oi->oi_flags = XFS_OWNER_INFO_BMBT_BLOCK;
	अगर (whichविभाजन == XFS_ATTR_FORK)
		oi->oi_flags |= XFS_OWNER_INFO_ATTR_FORK;
पूर्ण

अटल अंतरभूत व्योम
xfs_rmap_ino_owner(
	काष्ठा xfs_owner_info	*oi,
	xfs_ino_t		ino,
	पूर्णांक			whichविभाजन,
	xfs_fileoff_t		offset)
अणु
	oi->oi_owner = ino;
	oi->oi_offset = offset;
	oi->oi_flags = 0;
	अगर (whichविभाजन == XFS_ATTR_FORK)
		oi->oi_flags |= XFS_OWNER_INFO_ATTR_FORK;
पूर्ण

अटल अंतरभूत bool
xfs_rmap_should_skip_owner_update(
	स्थिर काष्ठा xfs_owner_info	*oi)
अणु
	वापस oi->oi_owner == XFS_RMAP_OWN_शून्य;
पूर्ण

/* Reverse mapping functions. */

काष्ठा xfs_buf;

अटल अंतरभूत __u64
xfs_rmap_irec_offset_pack(
	स्थिर काष्ठा xfs_rmap_irec	*irec)
अणु
	__u64			x;

	x = XFS_RMAP_OFF(irec->rm_offset);
	अगर (irec->rm_flags & XFS_RMAP_ATTR_FORK)
		x |= XFS_RMAP_OFF_ATTR_FORK;
	अगर (irec->rm_flags & XFS_RMAP_BMBT_BLOCK)
		x |= XFS_RMAP_OFF_BMBT_BLOCK;
	अगर (irec->rm_flags & XFS_RMAP_UNWRITTEN)
		x |= XFS_RMAP_OFF_UNWRITTEN;
	वापस x;
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_rmap_irec_offset_unpack(
	__u64			offset,
	काष्ठा xfs_rmap_irec	*irec)
अणु
	अगर (offset & ~(XFS_RMAP_OFF_MASK | XFS_RMAP_OFF_FLAGS))
		वापस -EFSCORRUPTED;
	irec->rm_offset = XFS_RMAP_OFF(offset);
	irec->rm_flags = 0;
	अगर (offset & XFS_RMAP_OFF_ATTR_FORK)
		irec->rm_flags |= XFS_RMAP_ATTR_FORK;
	अगर (offset & XFS_RMAP_OFF_BMBT_BLOCK)
		irec->rm_flags |= XFS_RMAP_BMBT_BLOCK;
	अगर (offset & XFS_RMAP_OFF_UNWRITTEN)
		irec->rm_flags |= XFS_RMAP_UNWRITTEN;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
xfs_owner_info_unpack(
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	uपूर्णांक64_t			*owner,
	uपूर्णांक64_t			*offset,
	अचिन्हित पूर्णांक			*flags)
अणु
	अचिन्हित पूर्णांक			r = 0;

	*owner = oinfo->oi_owner;
	*offset = oinfo->oi_offset;
	अगर (oinfo->oi_flags & XFS_OWNER_INFO_ATTR_FORK)
		r |= XFS_RMAP_ATTR_FORK;
	अगर (oinfo->oi_flags & XFS_OWNER_INFO_BMBT_BLOCK)
		r |= XFS_RMAP_BMBT_BLOCK;
	*flags = r;
पूर्ण

अटल अंतरभूत व्योम
xfs_owner_info_pack(
	काष्ठा xfs_owner_info	*oinfo,
	uपूर्णांक64_t		owner,
	uपूर्णांक64_t		offset,
	अचिन्हित पूर्णांक		flags)
अणु
	oinfo->oi_owner = owner;
	oinfo->oi_offset = XFS_RMAP_OFF(offset);
	oinfo->oi_flags = 0;
	अगर (flags & XFS_RMAP_ATTR_FORK)
		oinfo->oi_flags |= XFS_OWNER_INFO_ATTR_FORK;
	अगर (flags & XFS_RMAP_BMBT_BLOCK)
		oinfo->oi_flags |= XFS_OWNER_INFO_BMBT_BLOCK;
पूर्ण

पूर्णांक xfs_rmap_alloc(काष्ठा xfs_trans *tp, काष्ठा xfs_buf *agbp,
		   xfs_agnumber_t agno, xfs_agblock_t bno, xfs_extlen_t len,
		   स्थिर काष्ठा xfs_owner_info *oinfo);
पूर्णांक xfs_rmap_मुक्त(काष्ठा xfs_trans *tp, काष्ठा xfs_buf *agbp,
		  xfs_agnumber_t agno, xfs_agblock_t bno, xfs_extlen_t len,
		  स्थिर काष्ठा xfs_owner_info *oinfo);

पूर्णांक xfs_rmap_lookup_le(काष्ठा xfs_btree_cur *cur, xfs_agblock_t bno,
		xfs_extlen_t len, uपूर्णांक64_t owner, uपूर्णांक64_t offset,
		अचिन्हित पूर्णांक flags, पूर्णांक *stat);
पूर्णांक xfs_rmap_lookup_eq(काष्ठा xfs_btree_cur *cur, xfs_agblock_t bno,
		xfs_extlen_t len, uपूर्णांक64_t owner, uपूर्णांक64_t offset,
		अचिन्हित पूर्णांक flags, पूर्णांक *stat);
पूर्णांक xfs_rmap_insert(काष्ठा xfs_btree_cur *rcur, xfs_agblock_t agbno,
		xfs_extlen_t len, uपूर्णांक64_t owner, uपूर्णांक64_t offset,
		अचिन्हित पूर्णांक flags);
पूर्णांक xfs_rmap_get_rec(काष्ठा xfs_btree_cur *cur, काष्ठा xfs_rmap_irec *irec,
		पूर्णांक *stat);

प्रकार पूर्णांक (*xfs_rmap_query_range_fn)(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_rmap_irec	*rec,
	व्योम			*priv);

पूर्णांक xfs_rmap_query_range(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_rmap_irec *low_rec, काष्ठा xfs_rmap_irec *high_rec,
		xfs_rmap_query_range_fn fn, व्योम *priv);
पूर्णांक xfs_rmap_query_all(काष्ठा xfs_btree_cur *cur, xfs_rmap_query_range_fn fn,
		व्योम *priv);

क्रमागत xfs_rmap_पूर्णांकent_type अणु
	XFS_RMAP_MAP,
	XFS_RMAP_MAP_SHARED,
	XFS_RMAP_UNMAP,
	XFS_RMAP_UNMAP_SHARED,
	XFS_RMAP_CONVERT,
	XFS_RMAP_CONVERT_SHARED,
	XFS_RMAP_ALLOC,
	XFS_RMAP_FREE,
पूर्ण;

काष्ठा xfs_rmap_पूर्णांकent अणु
	काष्ठा list_head			ri_list;
	क्रमागत xfs_rmap_पूर्णांकent_type		ri_type;
	uपूर्णांक64_t				ri_owner;
	पूर्णांक					ri_whichविभाजन;
	काष्ठा xfs_bmbt_irec			ri_bmap;
पूर्ण;

/* functions क्रम updating the rmapbt based on bmbt map/unmap operations */
व्योम xfs_rmap_map_extent(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		पूर्णांक whichविभाजन, काष्ठा xfs_bmbt_irec *imap);
व्योम xfs_rmap_unmap_extent(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		पूर्णांक whichविभाजन, काष्ठा xfs_bmbt_irec *imap);
व्योम xfs_rmap_convert_extent(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन,
		काष्ठा xfs_bmbt_irec *imap);
व्योम xfs_rmap_alloc_extent(काष्ठा xfs_trans *tp, xfs_agnumber_t agno,
		xfs_agblock_t bno, xfs_extlen_t len, uपूर्णांक64_t owner);
व्योम xfs_rmap_मुक्त_extent(काष्ठा xfs_trans *tp, xfs_agnumber_t agno,
		xfs_agblock_t bno, xfs_extlen_t len, uपूर्णांक64_t owner);

व्योम xfs_rmap_finish_one_cleanup(काष्ठा xfs_trans *tp,
		काष्ठा xfs_btree_cur *rcur, पूर्णांक error);
पूर्णांक xfs_rmap_finish_one(काष्ठा xfs_trans *tp, क्रमागत xfs_rmap_पूर्णांकent_type type,
		uपूर्णांक64_t owner, पूर्णांक whichविभाजन, xfs_fileoff_t startoff,
		xfs_fsblock_t startblock, xfs_filblks_t blockcount,
		xfs_exntst_t state, काष्ठा xfs_btree_cur **pcur);

पूर्णांक xfs_rmap_find_left_neighbor(काष्ठा xfs_btree_cur *cur, xfs_agblock_t bno,
		uपूर्णांक64_t owner, uपूर्णांक64_t offset, अचिन्हित पूर्णांक flags,
		काष्ठा xfs_rmap_irec *irec, पूर्णांक	*stat);
पूर्णांक xfs_rmap_lookup_le_range(काष्ठा xfs_btree_cur *cur, xfs_agblock_t bno,
		uपूर्णांक64_t owner, uपूर्णांक64_t offset, अचिन्हित पूर्णांक flags,
		काष्ठा xfs_rmap_irec *irec, पूर्णांक	*stat);
पूर्णांक xfs_rmap_compare(स्थिर काष्ठा xfs_rmap_irec *a,
		स्थिर काष्ठा xfs_rmap_irec *b);
जोड़ xfs_btree_rec;
पूर्णांक xfs_rmap_btrec_to_irec(जोड़ xfs_btree_rec *rec,
		काष्ठा xfs_rmap_irec *irec);
पूर्णांक xfs_rmap_has_record(काष्ठा xfs_btree_cur *cur, xfs_agblock_t bno,
		xfs_extlen_t len, bool *exists);
पूर्णांक xfs_rmap_record_exists(काष्ठा xfs_btree_cur *cur, xfs_agblock_t bno,
		xfs_extlen_t len, स्थिर काष्ठा xfs_owner_info *oinfo,
		bool *has_rmap);
पूर्णांक xfs_rmap_has_other_keys(काष्ठा xfs_btree_cur *cur, xfs_agblock_t bno,
		xfs_extlen_t len, स्थिर काष्ठा xfs_owner_info *oinfo,
		bool *has_rmap);
पूर्णांक xfs_rmap_map_raw(काष्ठा xfs_btree_cur *cur, काष्ठा xfs_rmap_irec *rmap);

बाह्य स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_SKIP_UPDATE;
बाह्य स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_ANY_OWNER;
बाह्य स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_FS;
बाह्य स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_LOG;
बाह्य स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_AG;
बाह्य स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_INOBT;
बाह्य स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_INODES;
बाह्य स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_REFC;
बाह्य स्थिर काष्ठा xfs_owner_info XFS_RMAP_OINFO_COW;

#पूर्ण_अगर	/* __XFS_RMAP_H__ */
