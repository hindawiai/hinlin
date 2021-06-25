<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_SCRUB_SCRUB_H__
#घोषणा __XFS_SCRUB_SCRUB_H__

काष्ठा xfs_scrub;

/* Type info and names क्रम the scrub types. */
क्रमागत xchk_type अणु
	ST_NONE = 1,	/* disabled */
	ST_PERAG,	/* per-AG metadata */
	ST_FS,		/* per-FS metadata */
	ST_INODE,	/* per-inode metadata */
पूर्ण;

काष्ठा xchk_meta_ops अणु
	/* Acquire whatever resources are needed क्रम the operation. */
	पूर्णांक		(*setup)(काष्ठा xfs_scrub *sc);

	/* Examine metadata क्रम errors. */
	पूर्णांक		(*scrub)(काष्ठा xfs_scrub *);

	/* Repair or optimize the metadata. */
	पूर्णांक		(*repair)(काष्ठा xfs_scrub *);

	/* Decide अगर we even have this piece of metadata. */
	bool		(*has)(काष्ठा xfs_sb *);

	/* type describing required/allowed inमाला_दो */
	क्रमागत xchk_type	type;
पूर्ण;

/* Buffer poपूर्णांकers and btree cursors क्रम an entire AG. */
काष्ठा xchk_ag अणु
	xfs_agnumber_t		agno;
	काष्ठा xfs_perag	*pag;

	/* AG btree roots */
	काष्ठा xfs_buf		*agf_bp;
	काष्ठा xfs_buf		*agfl_bp;
	काष्ठा xfs_buf		*agi_bp;

	/* AG btrees */
	काष्ठा xfs_btree_cur	*bno_cur;
	काष्ठा xfs_btree_cur	*cnt_cur;
	काष्ठा xfs_btree_cur	*ino_cur;
	काष्ठा xfs_btree_cur	*fino_cur;
	काष्ठा xfs_btree_cur	*rmap_cur;
	काष्ठा xfs_btree_cur	*refc_cur;
पूर्ण;

काष्ठा xfs_scrub अणु
	/* General scrub state. */
	काष्ठा xfs_mount		*mp;
	काष्ठा xfs_scrub_metadata	*sm;
	स्थिर काष्ठा xchk_meta_ops	*ops;
	काष्ठा xfs_trans		*tp;

	/* File that scrub was called with. */
	काष्ठा file			*file;

	/*
	 * File that is undergoing the scrub operation.  This can dअगरfer from
	 * the file that scrub was called with अगर we're checking file-based fs
	 * metadata (e.g. rt biपंचांगaps) or अगर we're करोing a scrub-by-handle क्रम
	 * something that can't be खोलोed directly (e.g. symlinks).
	 */
	काष्ठा xfs_inode		*ip;

	व्योम				*buf;
	uपूर्णांक				ilock_flags;

	/* See the XCHK/XREP state flags below. */
	अचिन्हित पूर्णांक			flags;

	/*
	 * The XFS_SICK_* flags that correspond to the metadata being scrubbed
	 * or repaired.  We will use this mask to update the in-core fs health
	 * status with whatever we find.
	 */
	अचिन्हित पूर्णांक			sick_mask;

	/* State tracking क्रम single-AG operations. */
	काष्ठा xchk_ag			sa;
पूर्ण;

/* XCHK state flags grow up from zero, XREP state flags grown करोwn from 2^31 */
#घोषणा XCHK_TRY_HARDER		(1 << 0)  /* can't get resources, try again */
#घोषणा XCHK_HAS_QUOTAOFFLOCK	(1 << 1)  /* we hold the quotaoff lock */
#घोषणा XCHK_REAPING_DISABLED	(1 << 2)  /* background block reaping छोड़ोd */
#घोषणा XREP_ALREADY_FIXED	(1 << 31) /* checking our repair work */

/* Metadata scrubbers */
पूर्णांक xchk_tester(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_superblock(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_agf(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_agfl(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_agi(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_bnobt(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_cntbt(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_inobt(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_finobt(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_rmapbt(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_refcountbt(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_inode(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_bmap_data(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_bmap_attr(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_bmap_cow(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_directory(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_xattr(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_symlink(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_parent(काष्ठा xfs_scrub *sc);
#अगर_घोषित CONFIG_XFS_RT
पूर्णांक xchk_rtbiपंचांगap(काष्ठा xfs_scrub *sc);
पूर्णांक xchk_rtsummary(काष्ठा xfs_scrub *sc);
#अन्यथा
अटल अंतरभूत पूर्णांक
xchk_rtbiपंचांगap(काष्ठा xfs_scrub *sc)
अणु
	वापस -ENOENT;
पूर्ण
अटल अंतरभूत पूर्णांक
xchk_rtsummary(काष्ठा xfs_scrub *sc)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_XFS_QUOTA
पूर्णांक xchk_quota(काष्ठा xfs_scrub *sc);
#अन्यथा
अटल अंतरभूत पूर्णांक
xchk_quota(काष्ठा xfs_scrub *sc)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर
पूर्णांक xchk_fscounters(काष्ठा xfs_scrub *sc);

/* cross-referencing helpers */
व्योम xchk_xref_is_used_space(काष्ठा xfs_scrub *sc, xfs_agblock_t agbno,
		xfs_extlen_t len);
व्योम xchk_xref_is_not_inode_chunk(काष्ठा xfs_scrub *sc, xfs_agblock_t agbno,
		xfs_extlen_t len);
व्योम xchk_xref_is_inode_chunk(काष्ठा xfs_scrub *sc, xfs_agblock_t agbno,
		xfs_extlen_t len);
व्योम xchk_xref_is_owned_by(काष्ठा xfs_scrub *sc, xfs_agblock_t agbno,
		xfs_extlen_t len, स्थिर काष्ठा xfs_owner_info *oinfo);
व्योम xchk_xref_is_not_owned_by(काष्ठा xfs_scrub *sc, xfs_agblock_t agbno,
		xfs_extlen_t len, स्थिर काष्ठा xfs_owner_info *oinfo);
व्योम xchk_xref_has_no_owner(काष्ठा xfs_scrub *sc, xfs_agblock_t agbno,
		xfs_extlen_t len);
व्योम xchk_xref_is_cow_staging(काष्ठा xfs_scrub *sc, xfs_agblock_t bno,
		xfs_extlen_t len);
व्योम xchk_xref_is_not_shared(काष्ठा xfs_scrub *sc, xfs_agblock_t bno,
		xfs_extlen_t len);
#अगर_घोषित CONFIG_XFS_RT
व्योम xchk_xref_is_used_rt_space(काष्ठा xfs_scrub *sc, xfs_rtblock_t rtbno,
		xfs_extlen_t len);
#अन्यथा
# define xchk_xref_is_used_rt_space(sc, rtbno, len) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा xchk_fscounters अणु
	uपूर्णांक64_t		icount;
	uपूर्णांक64_t		अगरree;
	uपूर्णांक64_t		fdblocks;
	अचिन्हित दीर्घ दीर्घ	icount_min;
	अचिन्हित दीर्घ दीर्घ	icount_max;
पूर्ण;

#पूर्ण_अगर	/* __XFS_SCRUB_SCRUB_H__ */
