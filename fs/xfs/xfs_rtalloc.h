<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_RTALLOC_H__
#घोषणा	__XFS_RTALLOC_H__

/* kernel only definitions and functions */

काष्ठा xfs_mount;
काष्ठा xfs_trans;

/*
 * XXX: Most of the realसमय allocation functions deal in units of realसमय
 * extents, not realसमय blocks.  This looks funny when paired with the type
 * name and screams क्रम a larger cleanup.
 */
काष्ठा xfs_rtalloc_rec अणु
	xfs_rtblock_t		ar_startext;
	xfs_rtblock_t		ar_extcount;
पूर्ण;

प्रकार पूर्णांक (*xfs_rtalloc_query_range_fn)(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_rtalloc_rec	*rec,
	व्योम			*priv);

#अगर_घोषित CONFIG_XFS_RT
/*
 * Function prototypes क्रम exported functions.
 */

/*
 * Allocate an extent in the realसमय subvolume, with the usual allocation
 * parameters.  The length units are all in realसमय extents, as is the
 * result block number.
 */
पूर्णांक					/* error */
xfs_rtallocate_extent(
	काष्ठा xfs_trans	*tp,	/* transaction poपूर्णांकer */
	xfs_rtblock_t		bno,	/* starting block number to allocate */
	xfs_extlen_t		minlen,	/* minimum length to allocate */
	xfs_extlen_t		maxlen,	/* maximum length to allocate */
	xfs_extlen_t		*len,	/* out: actual length allocated */
	पूर्णांक			wasdel,	/* was a delayed allocation extent */
	xfs_extlen_t		prod,	/* extent product factor */
	xfs_rtblock_t		*rtblock); /* out: start block allocated */

/*
 * Free an extent in the realसमय subvolume.  Length is expressed in
 * realसमय extents, as is the block number.
 */
पूर्णांक					/* error */
xfs_rtमुक्त_extent(
	काष्ठा xfs_trans	*tp,	/* transaction poपूर्णांकer */
	xfs_rtblock_t		bno,	/* starting block number to मुक्त */
	xfs_extlen_t		len);	/* length of extent मुक्तd */

/*
 * Initialize realसमय fields in the mount काष्ठाure.
 */
पूर्णांक					/* error */
xfs_rपंचांगount_init(
	काष्ठा xfs_mount	*mp);	/* file प्रणाली mount काष्ठाure */
व्योम
xfs_rtunmount_inodes(
	काष्ठा xfs_mount	*mp);

/*
 * Get the biपंचांगap and summary inodes पूर्णांकo the mount काष्ठाure
 * at mount समय.
 */
पूर्णांक					/* error */
xfs_rपंचांगount_inodes(
	काष्ठा xfs_mount	*mp);	/* file प्रणाली mount काष्ठाure */

/*
 * Pick an extent क्रम allocation at the start of a new realसमय file.
 * Use the sequence number stored in the aसमय field of the biपंचांगap inode.
 * Translate this to a fraction of the rtextents, and वापस the product
 * of rtextents and the fraction.
 * The fraction sequence is 0, 1/2, 1/4, 3/4, 1/8, ..., 7/8, 1/16, ...
 */
पूर्णांक					/* error */
xfs_rtpick_extent(
	काष्ठा xfs_mount	*mp,	/* file प्रणाली mount poपूर्णांक */
	काष्ठा xfs_trans	*tp,	/* transaction poपूर्णांकer */
	xfs_extlen_t		len,	/* allocation length (rtextents) */
	xfs_rtblock_t		*pick);	/* result rt extent */

/*
 * Grow the realसमय area of the fileप्रणाली.
 */
पूर्णांक
xfs_growfs_rt(
	काष्ठा xfs_mount	*mp,	/* file प्रणाली mount काष्ठाure */
	xfs_growfs_rt_t		*in);	/* user supplied growfs काष्ठा */

/*
 * From xfs_rtbiपंचांगap.c
 */
पूर्णांक xfs_rtbuf_get(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		  xfs_rtblock_t block, पूर्णांक issum, काष्ठा xfs_buf **bpp);
पूर्णांक xfs_rtcheck_range(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		      xfs_rtblock_t start, xfs_extlen_t len, पूर्णांक val,
		      xfs_rtblock_t *new, पूर्णांक *stat);
पूर्णांक xfs_rtfind_back(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		    xfs_rtblock_t start, xfs_rtblock_t limit,
		    xfs_rtblock_t *rtblock);
पूर्णांक xfs_rtfind_क्रमw(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		    xfs_rtblock_t start, xfs_rtblock_t limit,
		    xfs_rtblock_t *rtblock);
पूर्णांक xfs_rपंचांगodअगरy_range(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		       xfs_rtblock_t start, xfs_extlen_t len, पूर्णांक val);
पूर्णांक xfs_rपंचांगodअगरy_summary_पूर्णांक(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
			     पूर्णांक log, xfs_rtblock_t bbno, पूर्णांक delta,
			     काष्ठा xfs_buf **rbpp, xfs_fsblock_t *rsb,
			     xfs_suminfo_t *sum);
पूर्णांक xfs_rपंचांगodअगरy_summary(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp, पूर्णांक log,
			 xfs_rtblock_t bbno, पूर्णांक delta, काष्ठा xfs_buf **rbpp,
			 xfs_fsblock_t *rsb);
पूर्णांक xfs_rtमुक्त_range(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		     xfs_rtblock_t start, xfs_extlen_t len,
		     काष्ठा xfs_buf **rbpp, xfs_fsblock_t *rsb);
पूर्णांक xfs_rtalloc_query_range(काष्ठा xfs_trans *tp,
			    काष्ठा xfs_rtalloc_rec *low_rec,
			    काष्ठा xfs_rtalloc_rec *high_rec,
			    xfs_rtalloc_query_range_fn fn,
			    व्योम *priv);
पूर्णांक xfs_rtalloc_query_all(काष्ठा xfs_trans *tp,
			  xfs_rtalloc_query_range_fn fn,
			  व्योम *priv);
bool xfs_verअगरy_rtbno(काष्ठा xfs_mount *mp, xfs_rtblock_t rtbno);
पूर्णांक xfs_rtalloc_extent_is_मुक्त(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
			       xfs_rtblock_t start, xfs_extlen_t len,
			       bool *is_मुक्त);
#अन्यथा
# define xfs_rtallocate_extent(t,b,min,max,l,f,p,rb)    (ENOSYS)
# define xfs_rtमुक्त_extent(t,b,l)                       (ENOSYS)
# define xfs_rtpick_extent(m,t,l,rb)                    (ENOSYS)
# define xfs_growfs_rt(mp,in)                           (ENOSYS)
# define xfs_rtalloc_query_range(t,l,h,f,p)             (ENOSYS)
# define xfs_rtalloc_query_all(t,f,p)                   (ENOSYS)
# define xfs_rtbuf_get(m,t,b,i,p)                       (ENOSYS)
# define xfs_verअगरy_rtbno(m, r)			(false)
# define xfs_rtalloc_extent_is_मुक्त(m,t,s,l,i)          (ENOSYS)
अटल अंतरभूत पूर्णांक		/* error */
xfs_rपंचांगount_init(
	xfs_mount_t	*mp)	/* file प्रणाली mount काष्ठाure */
अणु
	अगर (mp->m_sb.sb_rblocks == 0)
		वापस 0;

	xfs_warn(mp, "Not built with CONFIG_XFS_RT");
	वापस -ENOSYS;
पूर्ण
# define xfs_rपंचांगount_inodes(m)  (((mp)->m_sb.sb_rblocks == 0)? 0 : (ENOSYS))
# define xfs_rtunmount_inodes(m)
#पूर्ण_अगर	/* CONFIG_XFS_RT */

#पूर्ण_अगर	/* __XFS_RTALLOC_H__ */
