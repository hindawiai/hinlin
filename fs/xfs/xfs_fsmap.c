<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_bit.h"
#समावेश <linux/fsmap.h>
#समावेश "xfs_fsmap.h"
#समावेश "xfs_refcount.h"
#समावेश "xfs_refcount_btree.h"
#समावेश "xfs_alloc_btree.h"
#समावेश "xfs_rtalloc.h"

/* Convert an xfs_fsmap to an fsmap. */
अटल व्योम
xfs_fsmap_from_पूर्णांकernal(
	काष्ठा fsmap		*dest,
	काष्ठा xfs_fsmap	*src)
अणु
	dest->fmr_device = src->fmr_device;
	dest->fmr_flags = src->fmr_flags;
	dest->fmr_physical = BBTOB(src->fmr_physical);
	dest->fmr_owner = src->fmr_owner;
	dest->fmr_offset = BBTOB(src->fmr_offset);
	dest->fmr_length = BBTOB(src->fmr_length);
	dest->fmr_reserved[0] = 0;
	dest->fmr_reserved[1] = 0;
	dest->fmr_reserved[2] = 0;
पूर्ण

/* Convert an fsmap to an xfs_fsmap. */
व्योम
xfs_fsmap_to_पूर्णांकernal(
	काष्ठा xfs_fsmap	*dest,
	काष्ठा fsmap		*src)
अणु
	dest->fmr_device = src->fmr_device;
	dest->fmr_flags = src->fmr_flags;
	dest->fmr_physical = BTOBBT(src->fmr_physical);
	dest->fmr_owner = src->fmr_owner;
	dest->fmr_offset = BTOBBT(src->fmr_offset);
	dest->fmr_length = BTOBBT(src->fmr_length);
पूर्ण

/* Convert an fsmap owner पूर्णांकo an rmapbt owner. */
अटल पूर्णांक
xfs_fsmap_owner_to_rmap(
	काष्ठा xfs_rmap_irec	*dest,
	काष्ठा xfs_fsmap	*src)
अणु
	अगर (!(src->fmr_flags & FMR_OF_SPECIAL_OWNER)) अणु
		dest->rm_owner = src->fmr_owner;
		वापस 0;
	पूर्ण

	चयन (src->fmr_owner) अणु
	हाल 0:			/* "lowest owner id possible" */
	हाल -1ULL:		/* "highest owner id possible" */
		dest->rm_owner = 0;
		अवरोध;
	हाल XFS_FMR_OWN_FREE:
		dest->rm_owner = XFS_RMAP_OWN_शून्य;
		अवरोध;
	हाल XFS_FMR_OWN_UNKNOWN:
		dest->rm_owner = XFS_RMAP_OWN_UNKNOWN;
		अवरोध;
	हाल XFS_FMR_OWN_FS:
		dest->rm_owner = XFS_RMAP_OWN_FS;
		अवरोध;
	हाल XFS_FMR_OWN_LOG:
		dest->rm_owner = XFS_RMAP_OWN_LOG;
		अवरोध;
	हाल XFS_FMR_OWN_AG:
		dest->rm_owner = XFS_RMAP_OWN_AG;
		अवरोध;
	हाल XFS_FMR_OWN_INOBT:
		dest->rm_owner = XFS_RMAP_OWN_INOBT;
		अवरोध;
	हाल XFS_FMR_OWN_INODES:
		dest->rm_owner = XFS_RMAP_OWN_INODES;
		अवरोध;
	हाल XFS_FMR_OWN_REFC:
		dest->rm_owner = XFS_RMAP_OWN_REFC;
		अवरोध;
	हाल XFS_FMR_OWN_COW:
		dest->rm_owner = XFS_RMAP_OWN_COW;
		अवरोध;
	हाल XFS_FMR_OWN_DEFECTIVE:	/* not implemented */
		/* fall through */
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Convert an rmapbt owner पूर्णांकo an fsmap owner. */
अटल पूर्णांक
xfs_fsmap_owner_from_rmap(
	काष्ठा xfs_fsmap	*dest,
	काष्ठा xfs_rmap_irec	*src)
अणु
	dest->fmr_flags = 0;
	अगर (!XFS_RMAP_NON_INODE_OWNER(src->rm_owner)) अणु
		dest->fmr_owner = src->rm_owner;
		वापस 0;
	पूर्ण
	dest->fmr_flags |= FMR_OF_SPECIAL_OWNER;

	चयन (src->rm_owner) अणु
	हाल XFS_RMAP_OWN_FS:
		dest->fmr_owner = XFS_FMR_OWN_FS;
		अवरोध;
	हाल XFS_RMAP_OWN_LOG:
		dest->fmr_owner = XFS_FMR_OWN_LOG;
		अवरोध;
	हाल XFS_RMAP_OWN_AG:
		dest->fmr_owner = XFS_FMR_OWN_AG;
		अवरोध;
	हाल XFS_RMAP_OWN_INOBT:
		dest->fmr_owner = XFS_FMR_OWN_INOBT;
		अवरोध;
	हाल XFS_RMAP_OWN_INODES:
		dest->fmr_owner = XFS_FMR_OWN_INODES;
		अवरोध;
	हाल XFS_RMAP_OWN_REFC:
		dest->fmr_owner = XFS_FMR_OWN_REFC;
		अवरोध;
	हाल XFS_RMAP_OWN_COW:
		dest->fmr_owner = XFS_FMR_OWN_COW;
		अवरोध;
	हाल XFS_RMAP_OWN_शून्य:	/* "free" */
		dest->fmr_owner = XFS_FMR_OWN_FREE;
		अवरोध;
	शेष:
		ASSERT(0);
		वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

/* getfsmap query state */
काष्ठा xfs_getfsmap_info अणु
	काष्ठा xfs_fsmap_head	*head;
	काष्ठा fsmap		*fsmap_recs;	/* mapping records */
	काष्ठा xfs_buf		*agf_bp;	/* AGF, क्रम refcount queries */
	xfs_daddr_t		next_daddr;	/* next daddr we expect */
	u64			missing_owner;	/* owner of holes */
	u32			dev;		/* device id */
	xfs_agnumber_t		agno;		/* AG number, अगर applicable */
	काष्ठा xfs_rmap_irec	low;		/* low rmap key */
	काष्ठा xfs_rmap_irec	high;		/* high rmap key */
	bool			last;		/* last extent? */
पूर्ण;

/* Associate a device with a getfsmap handler. */
काष्ठा xfs_getfsmap_dev अणु
	u32			dev;
	पूर्णांक			(*fn)(काष्ठा xfs_trans *tp,
				      काष्ठा xfs_fsmap *keys,
				      काष्ठा xfs_getfsmap_info *info);
पूर्ण;

/* Compare two getfsmap device handlers. */
अटल पूर्णांक
xfs_getfsmap_dev_compare(
	स्थिर व्योम			*p1,
	स्थिर व्योम			*p2)
अणु
	स्थिर काष्ठा xfs_getfsmap_dev	*d1 = p1;
	स्थिर काष्ठा xfs_getfsmap_dev	*d2 = p2;

	वापस d1->dev - d2->dev;
पूर्ण

/* Decide अगर this mapping is shared. */
STATIC पूर्णांक
xfs_getfsmap_is_shared(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_getfsmap_info	*info,
	काष्ठा xfs_rmap_irec		*rec,
	bool				*stat)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_btree_cur		*cur;
	xfs_agblock_t			fbno;
	xfs_extlen_t			flen;
	पूर्णांक				error;

	*stat = false;
	अगर (!xfs_sb_version_hasreflink(&mp->m_sb))
		वापस 0;
	/* rt files will have agno set to शून्यAGNUMBER */
	अगर (info->agno == शून्यAGNUMBER)
		वापस 0;

	/* Are there any shared blocks here? */
	flen = 0;
	cur = xfs_refcountbt_init_cursor(mp, tp, info->agf_bp,
			info->agno);

	error = xfs_refcount_find_shared(cur, rec->rm_startblock,
			rec->rm_blockcount, &fbno, &flen, false);

	xfs_btree_del_cursor(cur, error);
	अगर (error)
		वापस error;

	*stat = flen > 0;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
xfs_getfsmap_क्रमmat(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_fsmap		*xfm,
	काष्ठा xfs_getfsmap_info	*info)
अणु
	काष्ठा fsmap			*rec;

	trace_xfs_getfsmap_mapping(mp, xfm);

	rec = &info->fsmap_recs[info->head->fmh_entries++];
	xfs_fsmap_from_पूर्णांकernal(rec, xfm);
पूर्ण

/*
 * Format a reverse mapping क्रम getfsmap, having translated rm_startblock
 * पूर्णांकo the appropriate daddr units.
 */
STATIC पूर्णांक
xfs_getfsmap_helper(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_getfsmap_info	*info,
	काष्ठा xfs_rmap_irec		*rec,
	xfs_daddr_t			rec_daddr)
अणु
	काष्ठा xfs_fsmap		fmr;
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	bool				shared;
	पूर्णांक				error;

	अगर (fatal_संकेत_pending(current))
		वापस -EINTR;

	/*
	 * Filter out records that start beक्रमe our startpoपूर्णांक, अगर the
	 * caller requested that.
	 */
	अगर (xfs_rmap_compare(rec, &info->low) < 0) अणु
		rec_daddr += XFS_FSB_TO_BB(mp, rec->rm_blockcount);
		अगर (info->next_daddr < rec_daddr)
			info->next_daddr = rec_daddr;
		वापस 0;
	पूर्ण

	/* Are we just counting mappings? */
	अगर (info->head->fmh_count == 0) अणु
		अगर (info->head->fmh_entries == अच_पूर्णांक_उच्च)
			वापस -ECANCELED;

		अगर (rec_daddr > info->next_daddr)
			info->head->fmh_entries++;

		अगर (info->last)
			वापस 0;

		info->head->fmh_entries++;

		rec_daddr += XFS_FSB_TO_BB(mp, rec->rm_blockcount);
		अगर (info->next_daddr < rec_daddr)
			info->next_daddr = rec_daddr;
		वापस 0;
	पूर्ण

	/*
	 * If the record starts past the last physical block we saw,
	 * then we've found a gap.  Report the gap as being owned by
	 * whatever the caller specअगरied is the missing owner.
	 */
	अगर (rec_daddr > info->next_daddr) अणु
		अगर (info->head->fmh_entries >= info->head->fmh_count)
			वापस -ECANCELED;

		fmr.fmr_device = info->dev;
		fmr.fmr_physical = info->next_daddr;
		fmr.fmr_owner = info->missing_owner;
		fmr.fmr_offset = 0;
		fmr.fmr_length = rec_daddr - info->next_daddr;
		fmr.fmr_flags = FMR_OF_SPECIAL_OWNER;
		xfs_getfsmap_क्रमmat(mp, &fmr, info);
	पूर्ण

	अगर (info->last)
		जाओ out;

	/* Fill out the extent we found */
	अगर (info->head->fmh_entries >= info->head->fmh_count)
		वापस -ECANCELED;

	trace_xfs_fsmap_mapping(mp, info->dev, info->agno, rec);

	fmr.fmr_device = info->dev;
	fmr.fmr_physical = rec_daddr;
	error = xfs_fsmap_owner_from_rmap(&fmr, rec);
	अगर (error)
		वापस error;
	fmr.fmr_offset = XFS_FSB_TO_BB(mp, rec->rm_offset);
	fmr.fmr_length = XFS_FSB_TO_BB(mp, rec->rm_blockcount);
	अगर (rec->rm_flags & XFS_RMAP_UNWRITTEN)
		fmr.fmr_flags |= FMR_OF_PREALLOC;
	अगर (rec->rm_flags & XFS_RMAP_ATTR_FORK)
		fmr.fmr_flags |= FMR_OF_ATTR_FORK;
	अगर (rec->rm_flags & XFS_RMAP_BMBT_BLOCK)
		fmr.fmr_flags |= FMR_OF_EXTENT_MAP;
	अगर (fmr.fmr_flags == 0) अणु
		error = xfs_getfsmap_is_shared(tp, info, rec, &shared);
		अगर (error)
			वापस error;
		अगर (shared)
			fmr.fmr_flags |= FMR_OF_SHARED;
	पूर्ण

	xfs_getfsmap_क्रमmat(mp, &fmr, info);
out:
	rec_daddr += XFS_FSB_TO_BB(mp, rec->rm_blockcount);
	अगर (info->next_daddr < rec_daddr)
		info->next_daddr = rec_daddr;
	वापस 0;
पूर्ण

/* Transक्रमm a rmapbt irec पूर्णांकo a fsmap */
STATIC पूर्णांक
xfs_getfsmap_datadev_helper(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_rmap_irec		*rec,
	व्योम				*priv)
अणु
	काष्ठा xfs_mount		*mp = cur->bc_mp;
	काष्ठा xfs_getfsmap_info	*info = priv;
	xfs_fsblock_t			fsb;
	xfs_daddr_t			rec_daddr;

	fsb = XFS_AGB_TO_FSB(mp, cur->bc_ag.agno, rec->rm_startblock);
	rec_daddr = XFS_FSB_TO_DADDR(mp, fsb);

	वापस xfs_getfsmap_helper(cur->bc_tp, info, rec, rec_daddr);
पूर्ण

/* Transक्रमm a bnobt irec पूर्णांकo a fsmap */
STATIC पूर्णांक
xfs_getfsmap_datadev_bnobt_helper(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_alloc_rec_incore	*rec,
	व्योम				*priv)
अणु
	काष्ठा xfs_mount		*mp = cur->bc_mp;
	काष्ठा xfs_getfsmap_info	*info = priv;
	काष्ठा xfs_rmap_irec		irec;
	xfs_daddr_t			rec_daddr;

	rec_daddr = XFS_AGB_TO_DADDR(mp, cur->bc_ag.agno,
			rec->ar_startblock);

	irec.rm_startblock = rec->ar_startblock;
	irec.rm_blockcount = rec->ar_blockcount;
	irec.rm_owner = XFS_RMAP_OWN_शून्य;	/* "free" */
	irec.rm_offset = 0;
	irec.rm_flags = 0;

	वापस xfs_getfsmap_helper(cur->bc_tp, info, &irec, rec_daddr);
पूर्ण

/* Set rmap flags based on the getfsmap flags */
अटल व्योम
xfs_getfsmap_set_irec_flags(
	काष्ठा xfs_rmap_irec	*irec,
	काष्ठा xfs_fsmap	*fmr)
अणु
	irec->rm_flags = 0;
	अगर (fmr->fmr_flags & FMR_OF_ATTR_FORK)
		irec->rm_flags |= XFS_RMAP_ATTR_FORK;
	अगर (fmr->fmr_flags & FMR_OF_EXTENT_MAP)
		irec->rm_flags |= XFS_RMAP_BMBT_BLOCK;
	अगर (fmr->fmr_flags & FMR_OF_PREALLOC)
		irec->rm_flags |= XFS_RMAP_UNWRITTEN;
पूर्ण

/* Execute a getfsmap query against the log device. */
STATIC पूर्णांक
xfs_getfsmap_logdev(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_fsmap		*keys,
	काष्ठा xfs_getfsmap_info	*info)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_rmap_irec		rmap;
	पूर्णांक				error;

	/* Set up search keys */
	info->low.rm_startblock = XFS_BB_TO_FSBT(mp, keys[0].fmr_physical);
	info->low.rm_offset = XFS_BB_TO_FSBT(mp, keys[0].fmr_offset);
	error = xfs_fsmap_owner_to_rmap(&info->low, keys);
	अगर (error)
		वापस error;
	info->low.rm_blockcount = 0;
	xfs_getfsmap_set_irec_flags(&info->low, &keys[0]);

	error = xfs_fsmap_owner_to_rmap(&info->high, keys + 1);
	अगर (error)
		वापस error;
	info->high.rm_startblock = -1U;
	info->high.rm_owner = ULदीर्घ_उच्च;
	info->high.rm_offset = ULदीर्घ_उच्च;
	info->high.rm_blockcount = 0;
	info->high.rm_flags = XFS_RMAP_KEY_FLAGS | XFS_RMAP_REC_FLAGS;
	info->missing_owner = XFS_FMR_OWN_FREE;

	trace_xfs_fsmap_low_key(mp, info->dev, info->agno, &info->low);
	trace_xfs_fsmap_high_key(mp, info->dev, info->agno, &info->high);

	अगर (keys[0].fmr_physical > 0)
		वापस 0;

	/* Fabricate an rmap entry क्रम the बाह्यal log device. */
	rmap.rm_startblock = 0;
	rmap.rm_blockcount = mp->m_sb.sb_logblocks;
	rmap.rm_owner = XFS_RMAP_OWN_LOG;
	rmap.rm_offset = 0;
	rmap.rm_flags = 0;

	वापस xfs_getfsmap_helper(tp, info, &rmap, 0);
पूर्ण

#अगर_घोषित CONFIG_XFS_RT
/* Transक्रमm a rtbiपंचांगap "record" पूर्णांकo a fsmap */
STATIC पूर्णांक
xfs_getfsmap_rtdev_rtbiपंचांगap_helper(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_rtalloc_rec		*rec,
	व्योम				*priv)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_getfsmap_info	*info = priv;
	काष्ठा xfs_rmap_irec		irec;
	xfs_daddr_t			rec_daddr;

	irec.rm_startblock = rec->ar_startext * mp->m_sb.sb_rextsize;
	rec_daddr = XFS_FSB_TO_BB(mp, irec.rm_startblock);
	irec.rm_blockcount = rec->ar_extcount * mp->m_sb.sb_rextsize;
	irec.rm_owner = XFS_RMAP_OWN_शून्य;	/* "free" */
	irec.rm_offset = 0;
	irec.rm_flags = 0;

	वापस xfs_getfsmap_helper(tp, info, &irec, rec_daddr);
पूर्ण

/* Execute a getfsmap query against the realसमय device. */
STATIC पूर्णांक
__xfs_getfsmap_rtdev(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_fsmap		*keys,
	पूर्णांक				(*query_fn)(काष्ठा xfs_trans *,
						    काष्ठा xfs_getfsmap_info *),
	काष्ठा xfs_getfsmap_info	*info)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	xfs_fsblock_t			start_fsb;
	xfs_fsblock_t			end_fsb;
	xfs_daddr_t			eofs;
	पूर्णांक				error = 0;

	eofs = XFS_FSB_TO_BB(mp, mp->m_sb.sb_rblocks);
	अगर (keys[0].fmr_physical >= eofs)
		वापस 0;
	अगर (keys[1].fmr_physical >= eofs)
		keys[1].fmr_physical = eofs - 1;
	start_fsb = XFS_BB_TO_FSBT(mp, keys[0].fmr_physical);
	end_fsb = XFS_BB_TO_FSB(mp, keys[1].fmr_physical);

	/* Set up search keys */
	info->low.rm_startblock = start_fsb;
	error = xfs_fsmap_owner_to_rmap(&info->low, &keys[0]);
	अगर (error)
		वापस error;
	info->low.rm_offset = XFS_BB_TO_FSBT(mp, keys[0].fmr_offset);
	info->low.rm_blockcount = 0;
	xfs_getfsmap_set_irec_flags(&info->low, &keys[0]);

	info->high.rm_startblock = end_fsb;
	error = xfs_fsmap_owner_to_rmap(&info->high, &keys[1]);
	अगर (error)
		वापस error;
	info->high.rm_offset = XFS_BB_TO_FSBT(mp, keys[1].fmr_offset);
	info->high.rm_blockcount = 0;
	xfs_getfsmap_set_irec_flags(&info->high, &keys[1]);

	trace_xfs_fsmap_low_key(mp, info->dev, info->agno, &info->low);
	trace_xfs_fsmap_high_key(mp, info->dev, info->agno, &info->high);

	वापस query_fn(tp, info);
पूर्ण

/* Actually query the realसमय biपंचांगap. */
STATIC पूर्णांक
xfs_getfsmap_rtdev_rtbiपंचांगap_query(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_getfsmap_info	*info)
अणु
	काष्ठा xfs_rtalloc_rec		alow = अणु 0 पूर्ण;
	काष्ठा xfs_rtalloc_rec		ahigh = अणु 0 पूर्ण;
	पूर्णांक				error;

	xfs_ilock(tp->t_mountp->m_rbmip, XFS_ILOCK_SHARED);

	alow.ar_startext = info->low.rm_startblock;
	ahigh.ar_startext = info->high.rm_startblock;
	करो_भाग(alow.ar_startext, tp->t_mountp->m_sb.sb_rextsize);
	अगर (करो_भाग(ahigh.ar_startext, tp->t_mountp->m_sb.sb_rextsize))
		ahigh.ar_startext++;
	error = xfs_rtalloc_query_range(tp, &alow, &ahigh,
			xfs_getfsmap_rtdev_rtbiपंचांगap_helper, info);
	अगर (error)
		जाओ err;

	/* Report any gaps at the end of the rtbiपंचांगap */
	info->last = true;
	error = xfs_getfsmap_rtdev_rtbiपंचांगap_helper(tp, &ahigh, info);
	अगर (error)
		जाओ err;
err:
	xfs_iunlock(tp->t_mountp->m_rbmip, XFS_ILOCK_SHARED);
	वापस error;
पूर्ण

/* Execute a getfsmap query against the realसमय device rtbiपंचांगap. */
STATIC पूर्णांक
xfs_getfsmap_rtdev_rtbiपंचांगap(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_fsmap		*keys,
	काष्ठा xfs_getfsmap_info	*info)
अणु
	info->missing_owner = XFS_FMR_OWN_UNKNOWN;
	वापस __xfs_getfsmap_rtdev(tp, keys, xfs_getfsmap_rtdev_rtbiपंचांगap_query,
			info);
पूर्ण
#पूर्ण_अगर /* CONFIG_XFS_RT */

/* Execute a getfsmap query against the regular data device. */
STATIC पूर्णांक
__xfs_getfsmap_datadev(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_fsmap		*keys,
	काष्ठा xfs_getfsmap_info	*info,
	पूर्णांक				(*query_fn)(काष्ठा xfs_trans *,
						    काष्ठा xfs_getfsmap_info *,
						    काष्ठा xfs_btree_cur **,
						    व्योम *),
	व्योम				*priv)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_btree_cur		*bt_cur = शून्य;
	xfs_fsblock_t			start_fsb;
	xfs_fsblock_t			end_fsb;
	xfs_agnumber_t			start_ag;
	xfs_agnumber_t			end_ag;
	xfs_daddr_t			eofs;
	पूर्णांक				error = 0;

	eofs = XFS_FSB_TO_BB(mp, mp->m_sb.sb_dblocks);
	अगर (keys[0].fmr_physical >= eofs)
		वापस 0;
	अगर (keys[1].fmr_physical >= eofs)
		keys[1].fmr_physical = eofs - 1;
	start_fsb = XFS_DADDR_TO_FSB(mp, keys[0].fmr_physical);
	end_fsb = XFS_DADDR_TO_FSB(mp, keys[1].fmr_physical);

	/*
	 * Convert the fsmap low/high keys to AG based keys.  Initialize
	 * low to the fsmap low key and max out the high key to the end
	 * of the AG.
	 */
	info->low.rm_startblock = XFS_FSB_TO_AGBNO(mp, start_fsb);
	info->low.rm_offset = XFS_BB_TO_FSBT(mp, keys[0].fmr_offset);
	error = xfs_fsmap_owner_to_rmap(&info->low, &keys[0]);
	अगर (error)
		वापस error;
	info->low.rm_blockcount = 0;
	xfs_getfsmap_set_irec_flags(&info->low, &keys[0]);

	info->high.rm_startblock = -1U;
	info->high.rm_owner = ULदीर्घ_उच्च;
	info->high.rm_offset = ULदीर्घ_उच्च;
	info->high.rm_blockcount = 0;
	info->high.rm_flags = XFS_RMAP_KEY_FLAGS | XFS_RMAP_REC_FLAGS;

	start_ag = XFS_FSB_TO_AGNO(mp, start_fsb);
	end_ag = XFS_FSB_TO_AGNO(mp, end_fsb);

	/* Query each AG */
	क्रम (info->agno = start_ag; info->agno <= end_ag; info->agno++) अणु
		/*
		 * Set the AG high key from the fsmap high key अगर this
		 * is the last AG that we're querying.
		 */
		अगर (info->agno == end_ag) अणु
			info->high.rm_startblock = XFS_FSB_TO_AGBNO(mp,
					end_fsb);
			info->high.rm_offset = XFS_BB_TO_FSBT(mp,
					keys[1].fmr_offset);
			error = xfs_fsmap_owner_to_rmap(&info->high, &keys[1]);
			अगर (error)
				जाओ err;
			xfs_getfsmap_set_irec_flags(&info->high, &keys[1]);
		पूर्ण

		अगर (bt_cur) अणु
			xfs_btree_del_cursor(bt_cur, XFS_BTREE_NOERROR);
			bt_cur = शून्य;
			xfs_trans_brअन्यथा(tp, info->agf_bp);
			info->agf_bp = शून्य;
		पूर्ण

		error = xfs_alloc_पढ़ो_agf(mp, tp, info->agno, 0,
				&info->agf_bp);
		अगर (error)
			जाओ err;

		trace_xfs_fsmap_low_key(mp, info->dev, info->agno, &info->low);
		trace_xfs_fsmap_high_key(mp, info->dev, info->agno,
				&info->high);

		error = query_fn(tp, info, &bt_cur, priv);
		अगर (error)
			जाओ err;

		/*
		 * Set the AG low key to the start of the AG prior to
		 * moving on to the next AG.
		 */
		अगर (info->agno == start_ag) अणु
			info->low.rm_startblock = 0;
			info->low.rm_owner = 0;
			info->low.rm_offset = 0;
			info->low.rm_flags = 0;
		पूर्ण
	पूर्ण

	/* Report any gap at the end of the AG */
	info->last = true;
	error = query_fn(tp, info, &bt_cur, priv);
	अगर (error)
		जाओ err;

err:
	अगर (bt_cur)
		xfs_btree_del_cursor(bt_cur, error < 0 ? XFS_BTREE_ERROR :
							 XFS_BTREE_NOERROR);
	अगर (info->agf_bp) अणु
		xfs_trans_brअन्यथा(tp, info->agf_bp);
		info->agf_bp = शून्य;
	पूर्ण

	वापस error;
पूर्ण

/* Actually query the rmap btree. */
STATIC पूर्णांक
xfs_getfsmap_datadev_rmapbt_query(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_getfsmap_info	*info,
	काष्ठा xfs_btree_cur		**curpp,
	व्योम				*priv)
अणु
	/* Report any gap at the end of the last AG. */
	अगर (info->last)
		वापस xfs_getfsmap_datadev_helper(*curpp, &info->high, info);

	/* Allocate cursor क्रम this AG and query_range it. */
	*curpp = xfs_rmapbt_init_cursor(tp->t_mountp, tp, info->agf_bp,
			info->agno);
	वापस xfs_rmap_query_range(*curpp, &info->low, &info->high,
			xfs_getfsmap_datadev_helper, info);
पूर्ण

/* Execute a getfsmap query against the regular data device rmapbt. */
STATIC पूर्णांक
xfs_getfsmap_datadev_rmapbt(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_fsmap		*keys,
	काष्ठा xfs_getfsmap_info	*info)
अणु
	info->missing_owner = XFS_FMR_OWN_FREE;
	वापस __xfs_getfsmap_datadev(tp, keys, info,
			xfs_getfsmap_datadev_rmapbt_query, शून्य);
पूर्ण

/* Actually query the bno btree. */
STATIC पूर्णांक
xfs_getfsmap_datadev_bnobt_query(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_getfsmap_info	*info,
	काष्ठा xfs_btree_cur		**curpp,
	व्योम				*priv)
अणु
	काष्ठा xfs_alloc_rec_incore	*key = priv;

	/* Report any gap at the end of the last AG. */
	अगर (info->last)
		वापस xfs_getfsmap_datadev_bnobt_helper(*curpp, &key[1], info);

	/* Allocate cursor क्रम this AG and query_range it. */
	*curpp = xfs_allocbt_init_cursor(tp->t_mountp, tp, info->agf_bp,
			info->agno, XFS_BTNUM_BNO);
	key->ar_startblock = info->low.rm_startblock;
	key[1].ar_startblock = info->high.rm_startblock;
	वापस xfs_alloc_query_range(*curpp, key, &key[1],
			xfs_getfsmap_datadev_bnobt_helper, info);
पूर्ण

/* Execute a getfsmap query against the regular data device's bnobt. */
STATIC पूर्णांक
xfs_getfsmap_datadev_bnobt(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_fsmap		*keys,
	काष्ठा xfs_getfsmap_info	*info)
अणु
	काष्ठा xfs_alloc_rec_incore	akeys[2];

	info->missing_owner = XFS_FMR_OWN_UNKNOWN;
	वापस __xfs_getfsmap_datadev(tp, keys, info,
			xfs_getfsmap_datadev_bnobt_query, &akeys[0]);
पूर्ण

/* Do we recognize the device? */
STATIC bool
xfs_getfsmap_is_valid_device(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_fsmap	*fm)
अणु
	अगर (fm->fmr_device == 0 || fm->fmr_device == अच_पूर्णांक_उच्च ||
	    fm->fmr_device == new_encode_dev(mp->m_ddev_targp->bt_dev))
		वापस true;
	अगर (mp->m_logdev_targp &&
	    fm->fmr_device == new_encode_dev(mp->m_logdev_targp->bt_dev))
		वापस true;
	अगर (mp->m_rtdev_targp &&
	    fm->fmr_device == new_encode_dev(mp->m_rtdev_targp->bt_dev))
		वापस true;
	वापस false;
पूर्ण

/* Ensure that the low key is less than the high key. */
STATIC bool
xfs_getfsmap_check_keys(
	काष्ठा xfs_fsmap		*low_key,
	काष्ठा xfs_fsmap		*high_key)
अणु
	अगर (low_key->fmr_device > high_key->fmr_device)
		वापस false;
	अगर (low_key->fmr_device < high_key->fmr_device)
		वापस true;

	अगर (low_key->fmr_physical > high_key->fmr_physical)
		वापस false;
	अगर (low_key->fmr_physical < high_key->fmr_physical)
		वापस true;

	अगर (low_key->fmr_owner > high_key->fmr_owner)
		वापस false;
	अगर (low_key->fmr_owner < high_key->fmr_owner)
		वापस true;

	अगर (low_key->fmr_offset > high_key->fmr_offset)
		वापस false;
	अगर (low_key->fmr_offset < high_key->fmr_offset)
		वापस true;

	वापस false;
पूर्ण

/*
 * There are only two devices अगर we didn't configure RT devices at build समय.
 */
#अगर_घोषित CONFIG_XFS_RT
#घोषणा XFS_GETFSMAP_DEVS	3
#अन्यथा
#घोषणा XFS_GETFSMAP_DEVS	2
#पूर्ण_अगर /* CONFIG_XFS_RT */

/*
 * Get fileप्रणाली's extents as described in head, and क्रमmat क्रम output. Fills
 * in the supplied records array until there are no more reverse mappings to
 * वापस or head.fmh_entries == head.fmh_count.  In the second हाल, this
 * function वापसs -ECANCELED to indicate that more records would have been
 * वापसed.
 *
 * Key to Confusion
 * ----------------
 * There are multiple levels of keys and counters at work here:
 * xfs_fsmap_head.fmh_keys	-- low and high fsmap keys passed in;
 * 				   these reflect fs-wide sector addrs.
 * dkeys			-- fmh_keys used to query each device;
 * 				   these are fmh_keys but w/ the low key
 * 				   bumped up by fmr_length.
 * xfs_getfsmap_info.next_daddr	-- next disk addr we expect to see; this
 *				   is how we detect gaps in the fsmap
				   records and report them.
 * xfs_getfsmap_info.low/high	-- per-AG low/high keys computed from
 * 				   dkeys; used to query the metadata.
 */
पूर्णांक
xfs_getfsmap(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_fsmap_head		*head,
	काष्ठा fsmap			*fsmap_recs)
अणु
	काष्ठा xfs_trans		*tp = शून्य;
	काष्ठा xfs_fsmap		dkeys[2];	/* per-dev keys */
	काष्ठा xfs_getfsmap_dev		handlers[XFS_GETFSMAP_DEVS];
	काष्ठा xfs_getfsmap_info	info = अणु शून्य पूर्ण;
	bool				use_rmap;
	पूर्णांक				i;
	पूर्णांक				error = 0;

	अगर (head->fmh_अगरlags & ~FMH_IF_VALID)
		वापस -EINVAL;
	अगर (!xfs_getfsmap_is_valid_device(mp, &head->fmh_keys[0]) ||
	    !xfs_getfsmap_is_valid_device(mp, &head->fmh_keys[1]))
		वापस -EINVAL;

	use_rmap = capable(CAP_SYS_ADMIN) &&
		   xfs_sb_version_hasrmapbt(&mp->m_sb);
	head->fmh_entries = 0;

	/* Set up our device handlers. */
	स_रखो(handlers, 0, माप(handlers));
	handlers[0].dev = new_encode_dev(mp->m_ddev_targp->bt_dev);
	अगर (use_rmap)
		handlers[0].fn = xfs_getfsmap_datadev_rmapbt;
	अन्यथा
		handlers[0].fn = xfs_getfsmap_datadev_bnobt;
	अगर (mp->m_logdev_targp != mp->m_ddev_targp) अणु
		handlers[1].dev = new_encode_dev(mp->m_logdev_targp->bt_dev);
		handlers[1].fn = xfs_getfsmap_logdev;
	पूर्ण
#अगर_घोषित CONFIG_XFS_RT
	अगर (mp->m_rtdev_targp) अणु
		handlers[2].dev = new_encode_dev(mp->m_rtdev_targp->bt_dev);
		handlers[2].fn = xfs_getfsmap_rtdev_rtbiपंचांगap;
	पूर्ण
#पूर्ण_अगर /* CONFIG_XFS_RT */

	xfs_sort(handlers, XFS_GETFSMAP_DEVS, माप(काष्ठा xfs_getfsmap_dev),
			xfs_getfsmap_dev_compare);

	/*
	 * To जारी where we left off, we allow userspace to use the
	 * last mapping from a previous call as the low key of the next.
	 * This is identअगरied by a non-zero length in the low key. We
	 * have to increment the low key in this scenario to ensure we
	 * करोn't वापस the same mapping again, and instead वापस the
	 * very next mapping.
	 *
	 * If the low key mapping refers to file data, the same physical
	 * blocks could be mapped to several other files/offsets.
	 * According to rmapbt record ordering, the minimal next
	 * possible record क्रम the block range is the next starting
	 * offset in the same inode. Thereक्रमe, bump the file offset to
	 * जारी the search appropriately.  For all other low key
	 * mapping types (attr blocks, metadata), bump the physical
	 * offset as there can be no other mapping क्रम the same physical
	 * block range.
	 */
	dkeys[0] = head->fmh_keys[0];
	अगर (dkeys[0].fmr_flags & (FMR_OF_SPECIAL_OWNER | FMR_OF_EXTENT_MAP)) अणु
		dkeys[0].fmr_physical += dkeys[0].fmr_length;
		dkeys[0].fmr_owner = 0;
		अगर (dkeys[0].fmr_offset)
			वापस -EINVAL;
	पूर्ण अन्यथा
		dkeys[0].fmr_offset += dkeys[0].fmr_length;
	dkeys[0].fmr_length = 0;
	स_रखो(&dkeys[1], 0xFF, माप(काष्ठा xfs_fsmap));

	अगर (!xfs_getfsmap_check_keys(dkeys, &head->fmh_keys[1]))
		वापस -EINVAL;

	info.next_daddr = head->fmh_keys[0].fmr_physical +
			  head->fmh_keys[0].fmr_length;
	info.fsmap_recs = fsmap_recs;
	info.head = head;

	/* For each device we support... */
	क्रम (i = 0; i < XFS_GETFSMAP_DEVS; i++) अणु
		/* Is this device within the range the user asked क्रम? */
		अगर (!handlers[i].fn)
			जारी;
		अगर (head->fmh_keys[0].fmr_device > handlers[i].dev)
			जारी;
		अगर (head->fmh_keys[1].fmr_device < handlers[i].dev)
			अवरोध;

		/*
		 * If this device number matches the high key, we have
		 * to pass the high key to the handler to limit the
		 * query results.  If the device number exceeds the
		 * low key, zero out the low key so that we get
		 * everything from the beginning.
		 */
		अगर (handlers[i].dev == head->fmh_keys[1].fmr_device)
			dkeys[1] = head->fmh_keys[1];
		अगर (handlers[i].dev > head->fmh_keys[0].fmr_device)
			स_रखो(&dkeys[0], 0, माप(काष्ठा xfs_fsmap));

		/*
		 * Grab an empty transaction so that we can use its recursive
		 * buffer locking abilities to detect cycles in the rmapbt
		 * without deadlocking.
		 */
		error = xfs_trans_alloc_empty(mp, &tp);
		अगर (error)
			अवरोध;

		info.dev = handlers[i].dev;
		info.last = false;
		info.agno = शून्यAGNUMBER;
		error = handlers[i].fn(tp, dkeys, &info);
		अगर (error)
			अवरोध;
		xfs_trans_cancel(tp);
		tp = शून्य;
		info.next_daddr = 0;
	पूर्ण

	अगर (tp)
		xfs_trans_cancel(tp);
	head->fmh_oflags = FMH_OF_DEV_T;
	वापस error;
पूर्ण
