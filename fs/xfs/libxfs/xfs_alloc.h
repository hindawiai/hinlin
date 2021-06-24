<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_ALLOC_H__
#घोषणा	__XFS_ALLOC_H__

काष्ठा xfs_buf;
काष्ठा xfs_btree_cur;
काष्ठा xfs_mount;
काष्ठा xfs_perag;
काष्ठा xfs_trans;

बाह्य काष्ठा workqueue_काष्ठा *xfs_alloc_wq;

अचिन्हित पूर्णांक xfs_agfl_size(काष्ठा xfs_mount *mp);

/*
 * Freespace allocation types.  Argument to xfs_alloc_[v]extent.
 */
#घोषणा XFS_ALLOCTYPE_FIRST_AG	0x02	/* ... start at ag 0 */
#घोषणा XFS_ALLOCTYPE_THIS_AG	0x08	/* anywhere in this a.g. */
#घोषणा XFS_ALLOCTYPE_START_BNO	0x10	/* near this block अन्यथा anywhere */
#घोषणा XFS_ALLOCTYPE_NEAR_BNO	0x20	/* in this a.g. and near this block */
#घोषणा XFS_ALLOCTYPE_THIS_BNO	0x40	/* at exactly this block */

/* this should become an क्रमागत again when the tracing code is fixed */
प्रकार अचिन्हित पूर्णांक xfs_alloctype_t;

#घोषणा XFS_ALLOC_TYPES \
	अणु XFS_ALLOCTYPE_FIRST_AG,	"FIRST_AG" पूर्ण, \
	अणु XFS_ALLOCTYPE_THIS_AG,	"THIS_AG" पूर्ण, \
	अणु XFS_ALLOCTYPE_START_BNO,	"START_BNO" पूर्ण, \
	अणु XFS_ALLOCTYPE_NEAR_BNO,	"NEAR_BNO" पूर्ण, \
	अणु XFS_ALLOCTYPE_THIS_BNO,	"THIS_BNO" पूर्ण

/*
 * Flags क्रम xfs_alloc_fix_मुक्तlist.
 */
#घोषणा	XFS_ALLOC_FLAG_TRYLOCK	0x00000001  /* use trylock क्रम buffer locking */
#घोषणा	XFS_ALLOC_FLAG_FREEING	0x00000002  /* indicate caller is मुक्तing extents*/
#घोषणा	XFS_ALLOC_FLAG_NORMAP	0x00000004  /* करोn't modअगरy the rmapbt */
#घोषणा	XFS_ALLOC_FLAG_NOSHRINK	0x00000008  /* करोn't shrink the मुक्तlist */
#घोषणा	XFS_ALLOC_FLAG_CHECK	0x00000010  /* test only, करोn't modअगरy args */

/*
 * Argument काष्ठाure क्रम xfs_alloc routines.
 * This is turned पूर्णांकo a काष्ठाure to aव्योम having 20 arguments passed
 * करोwn several levels of the stack.
 */
प्रकार काष्ठा xfs_alloc_arg अणु
	काष्ठा xfs_trans *tp;		/* transaction poपूर्णांकer */
	काष्ठा xfs_mount *mp;		/* file प्रणाली mount poपूर्णांक */
	काष्ठा xfs_buf	*agbp;		/* buffer क्रम a.g. मुक्तlist header */
	काष्ठा xfs_perag *pag;		/* per-ag काष्ठा क्रम this agno */
	xfs_fsblock_t	fsbno;		/* file प्रणाली block number */
	xfs_agnumber_t	agno;		/* allocation group number */
	xfs_agblock_t	agbno;		/* allocation group-relative block # */
	xfs_extlen_t	minlen;		/* minimum size of extent */
	xfs_extlen_t	maxlen;		/* maximum size of extent */
	xfs_extlen_t	mod;		/* mod value क्रम extent size */
	xfs_extlen_t	prod;		/* prod value क्रम extent size */
	xfs_extlen_t	minleft;	/* min blocks must be left after us */
	xfs_extlen_t	total;		/* total blocks needed in xaction */
	xfs_extlen_t	alignment;	/* align answer to multiple of this */
	xfs_extlen_t	minalignslop;	/* slop क्रम minlen+alignment calcs */
	xfs_agblock_t	min_agbno;	/* set an agbno range क्रम NEAR allocs */
	xfs_agblock_t	max_agbno;	/* ... */
	xfs_extlen_t	len;		/* output: actual size of extent */
	xfs_alloctype_t	type;		/* allocation type XFS_ALLOCTYPE_... */
	xfs_alloctype_t	otype;		/* original allocation type */
	पूर्णांक		datatype;	/* mask defining data type treaपंचांगent */
	अक्षर		wasdel;		/* set अगर allocation was prev delayed */
	अक्षर		wasfromfl;	/* set अगर allocation is from मुक्तlist */
	काष्ठा xfs_owner_info	oinfo;	/* owner of blocks being allocated */
	क्रमागत xfs_ag_resv_type	resv;	/* block reservation to use */
#अगर_घोषित DEBUG
	bool		alloc_minlen_only; /* allocate exact minlen extent */
#पूर्ण_अगर
पूर्ण xfs_alloc_arg_t;

/*
 * Defines क्रम datatype
 */
#घोषणा XFS_ALLOC_USERDATA		(1 << 0)/* allocation is क्रम user data*/
#घोषणा XFS_ALLOC_INITIAL_USER_DATA	(1 << 1)/* special हाल start of file */
#घोषणा XFS_ALLOC_NOBUSY		(1 << 2)/* Busy extents not allowed */

/* मुक्तspace limit calculations */
#घोषणा XFS_ALLOC_AGFL_RESERVE	4
अचिन्हित पूर्णांक xfs_alloc_set_aside(काष्ठा xfs_mount *mp);
अचिन्हित पूर्णांक xfs_alloc_ag_max_usable(काष्ठा xfs_mount *mp);

xfs_extlen_t xfs_alloc_दीर्घest_मुक्त_extent(काष्ठा xfs_perag *pag,
		xfs_extlen_t need, xfs_extlen_t reserved);
अचिन्हित पूर्णांक xfs_alloc_min_मुक्तlist(काष्ठा xfs_mount *mp,
		काष्ठा xfs_perag *pag);

/*
 * Compute and fill in value of m_ag_maxlevels.
 */
व्योम
xfs_alloc_compute_maxlevels(
	काष्ठा xfs_mount	*mp);	/* file प्रणाली mount काष्ठाure */

/*
 * Get a block from the मुक्तlist.
 * Returns with the buffer क्रम the block gotten.
 */
पूर्णांक				/* error */
xfs_alloc_get_मुक्तlist(
	काष्ठा xfs_trans *tp,	/* transaction poपूर्णांकer */
	काष्ठा xfs_buf	*agbp,	/* buffer containing the agf काष्ठाure */
	xfs_agblock_t	*bnop,	/* block address retrieved from मुक्तlist */
	पूर्णांक		btreeblk); /* destination is a AGF btree */

/*
 * Log the given fields from the agf काष्ठाure.
 */
व्योम
xfs_alloc_log_agf(
	काष्ठा xfs_trans *tp,	/* transaction poपूर्णांकer */
	काष्ठा xfs_buf	*bp,	/* buffer क्रम a.g. मुक्तlist header */
	पूर्णांक		fields);/* mask of fields to be logged (XFS_AGF_...) */

/*
 * Interface क्रम inode allocation to क्रमce the pag data to be initialized.
 */
पूर्णांक				/* error */
xfs_alloc_pagf_init(
	काष्ठा xfs_mount *mp,	/* file प्रणाली mount काष्ठाure */
	काष्ठा xfs_trans *tp,	/* transaction poपूर्णांकer */
	xfs_agnumber_t	agno,	/* allocation group number */
	पूर्णांक		flags);	/* XFS_ALLOC_FLAGS_... */

/*
 * Put the block on the मुक्तlist क्रम the allocation group.
 */
पूर्णांक				/* error */
xfs_alloc_put_मुक्तlist(
	काष्ठा xfs_trans *tp,	/* transaction poपूर्णांकer */
	काष्ठा xfs_buf	*agbp,	/* buffer क्रम a.g. मुक्तlist header */
	काष्ठा xfs_buf	*agflbp,/* buffer क्रम a.g. मुक्त block array */
	xfs_agblock_t	bno,	/* block being मुक्तd */
	पूर्णांक		btreeblk); /* owner was a AGF btree */

/*
 * Read in the allocation group header (मुक्त/alloc section).
 */
पूर्णांक					/* error  */
xfs_alloc_पढ़ो_agf(
	काष्ठा xfs_mount *mp,		/* mount poपूर्णांक काष्ठाure */
	काष्ठा xfs_trans *tp,		/* transaction poपूर्णांकer */
	xfs_agnumber_t	agno,		/* allocation group number */
	पूर्णांक		flags,		/* XFS_ALLOC_FLAG_... */
	काष्ठा xfs_buf	**bpp);		/* buffer क्रम the ag मुक्तlist header */

/*
 * Allocate an extent (variable-size).
 */
पूर्णांक				/* error */
xfs_alloc_vextent(
	xfs_alloc_arg_t	*args);	/* allocation argument काष्ठाure */

/*
 * Free an extent.
 */
पूर्णांक				/* error */
__xfs_मुक्त_extent(
	काष्ठा xfs_trans	*tp,	/* transaction poपूर्णांकer */
	xfs_fsblock_t		bno,	/* starting block number of extent */
	xfs_extlen_t		len,	/* length of extent */
	स्थिर काष्ठा xfs_owner_info	*oinfo,	/* extent owner */
	क्रमागत xfs_ag_resv_type	type,	/* block reservation type */
	bool			skip_discard);

अटल अंतरभूत पूर्णांक
xfs_मुक्त_extent(
	काष्ठा xfs_trans	*tp,
	xfs_fsblock_t		bno,
	xfs_extlen_t		len,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	क्रमागत xfs_ag_resv_type	type)
अणु
	वापस __xfs_मुक्त_extent(tp, bno, len, oinfo, type, false);
पूर्ण

पूर्णांक				/* error */
xfs_alloc_lookup_le(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		bno,	/* starting block of extent */
	xfs_extlen_t		len,	/* length of extent */
	पूर्णांक			*stat);	/* success/failure */

पूर्णांक				/* error */
xfs_alloc_lookup_ge(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		bno,	/* starting block of extent */
	xfs_extlen_t		len,	/* length of extent */
	पूर्णांक			*stat);	/* success/failure */

पूर्णांक					/* error */
xfs_alloc_get_rec(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		*bno,	/* output: starting block of extent */
	xfs_extlen_t		*len,	/* output: length of extent */
	पूर्णांक			*stat);	/* output: success/failure */

पूर्णांक xfs_पढ़ो_agf(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
			xfs_agnumber_t agno, पूर्णांक flags, काष्ठा xfs_buf **bpp);
पूर्णांक xfs_alloc_पढ़ो_agfl(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
			xfs_agnumber_t agno, काष्ठा xfs_buf **bpp);
पूर्णांक xfs_मुक्त_agfl_block(काष्ठा xfs_trans *, xfs_agnumber_t, xfs_agblock_t,
			काष्ठा xfs_buf *, काष्ठा xfs_owner_info *);
पूर्णांक xfs_alloc_fix_मुक्तlist(काष्ठा xfs_alloc_arg *args, पूर्णांक flags);
पूर्णांक xfs_मुक्त_extent_fix_मुक्तlist(काष्ठा xfs_trans *tp, xfs_agnumber_t agno,
		काष्ठा xfs_buf **agbp);

xfs_extlen_t xfs_pपुनः_स्मृति_blocks(काष्ठा xfs_mount *mp);

प्रकार पूर्णांक (*xfs_alloc_query_range_fn)(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_alloc_rec_incore	*rec,
	व्योम				*priv);

पूर्णांक xfs_alloc_query_range(काष्ठा xfs_btree_cur *cur,
		काष्ठा xfs_alloc_rec_incore *low_rec,
		काष्ठा xfs_alloc_rec_incore *high_rec,
		xfs_alloc_query_range_fn fn, व्योम *priv);
पूर्णांक xfs_alloc_query_all(काष्ठा xfs_btree_cur *cur, xfs_alloc_query_range_fn fn,
		व्योम *priv);

पूर्णांक xfs_alloc_has_record(काष्ठा xfs_btree_cur *cur, xfs_agblock_t bno,
		xfs_extlen_t len, bool *exist);

प्रकार पूर्णांक (*xfs_agfl_walk_fn)(काष्ठा xfs_mount *mp, xfs_agblock_t bno,
		व्योम *priv);
पूर्णांक xfs_agfl_walk(काष्ठा xfs_mount *mp, काष्ठा xfs_agf *agf,
		काष्ठा xfs_buf *agflbp, xfs_agfl_walk_fn walk_fn, व्योम *priv);

अटल अंतरभूत __be32 *
xfs_buf_to_agfl_bno(
	काष्ठा xfs_buf		*bp)
अणु
	अगर (xfs_sb_version_hascrc(&bp->b_mount->m_sb))
		वापस bp->b_addr + माप(काष्ठा xfs_agfl);
	वापस bp->b_addr;
पूर्ण

#पूर्ण_अगर	/* __XFS_ALLOC_H__ */
