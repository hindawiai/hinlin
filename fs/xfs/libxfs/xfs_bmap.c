<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_util.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_rtalloc.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_attr_leaf.h"
#समावेश "xfs_filestream.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_ag_resv.h"
#समावेश "xfs_refcount.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_iomap.h"


kmem_zone_t		*xfs_bmap_मुक्त_item_zone;

/*
 * Miscellaneous helper functions
 */

/*
 * Compute and fill in the value of the maximum depth of a bmap btree
 * in this fileप्रणाली.  Done once, during mount.
 */
व्योम
xfs_bmap_compute_maxlevels(
	xfs_mount_t	*mp,		/* file प्रणाली mount काष्ठाure */
	पूर्णांक		whichविभाजन)	/* data or attr विभाजन */
अणु
	पूर्णांक		level;		/* btree level */
	uपूर्णांक		maxblocks;	/* max blocks at this level */
	uपूर्णांक		maxleafents;	/* max leaf entries possible */
	पूर्णांक		maxrootrecs;	/* max records in root block */
	पूर्णांक		minleafrecs;	/* min records in leaf block */
	पूर्णांक		minnoderecs;	/* min records in node block */
	पूर्णांक		sz;		/* root block size */

	/*
	 * The maximum number of extents in a file, hence the maximum number of
	 * leaf entries, is controlled by the size of the on-disk extent count,
	 * either a चिन्हित 32-bit number क्रम the data विभाजन, or a चिन्हित 16-bit
	 * number क्रम the attr विभाजन.
	 *
	 * Note that we can no दीर्घer assume that अगर we are in ATTR1 that the
	 * विभाजन offset of all the inodes will be
	 * (xfs_शेष_attroffset(ip) >> 3) because we could have mounted with
	 * ATTR2 and then mounted back with ATTR1, keeping the i_विभाजनoff's fixed
	 * but probably at various positions. Thereक्रमe, क्रम both ATTR1 and
	 * ATTR2 we have to assume the worst हाल scenario of a minimum size
	 * available.
	 */
	अगर (whichविभाजन == XFS_DATA_FORK) अणु
		maxleafents = MAXEXTNUM;
		sz = XFS_BMDR_SPACE_CALC(MINDBTPTRS);
	पूर्ण अन्यथा अणु
		maxleafents = MAXAEXTNUM;
		sz = XFS_BMDR_SPACE_CALC(MINABTPTRS);
	पूर्ण
	maxrootrecs = xfs_bmdr_maxrecs(sz, 0);
	minleafrecs = mp->m_bmap_dmnr[0];
	minnoderecs = mp->m_bmap_dmnr[1];
	maxblocks = (maxleafents + minleafrecs - 1) / minleafrecs;
	क्रम (level = 1; maxblocks > 1; level++) अणु
		अगर (maxblocks <= maxrootrecs)
			maxblocks = 1;
		अन्यथा
			maxblocks = (maxblocks + minnoderecs - 1) / minnoderecs;
	पूर्ण
	mp->m_bm_maxlevels[whichविभाजन] = level;
पूर्ण

अचिन्हित पूर्णांक
xfs_bmap_compute_attr_offset(
	काष्ठा xfs_mount	*mp)
अणु
	अगर (mp->m_sb.sb_inodesize == 256)
		वापस XFS_LITINO(mp) - XFS_BMDR_SPACE_CALC(MINABTPTRS);
	वापस XFS_BMDR_SPACE_CALC(6 * MINABTPTRS);
पूर्ण

STATIC पूर्णांक				/* error */
xfs_bmbt_lookup_eq(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_bmbt_irec	*irec,
	पूर्णांक			*stat)	/* success/failure */
अणु
	cur->bc_rec.b = *irec;
	वापस xfs_btree_lookup(cur, XFS_LOOKUP_EQ, stat);
पूर्ण

STATIC पूर्णांक				/* error */
xfs_bmbt_lookup_first(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			*stat)	/* success/failure */
अणु
	cur->bc_rec.b.br_startoff = 0;
	cur->bc_rec.b.br_startblock = 0;
	cur->bc_rec.b.br_blockcount = 0;
	वापस xfs_btree_lookup(cur, XFS_LOOKUP_GE, stat);
पूर्ण

/*
 * Check अगर the inode needs to be converted to btree क्रमmat.
 */
अटल अंतरभूत bool xfs_bmap_needs_btree(काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन)
अणु
	काष्ठा xfs_अगरork *अगरp = XFS_IFORK_PTR(ip, whichविभाजन);

	वापस whichविभाजन != XFS_COW_FORK &&
		अगरp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS &&
		अगरp->अगर_nextents > XFS_IFORK_MAXEXT(ip, whichविभाजन);
पूर्ण

/*
 * Check अगर the inode should be converted to extent क्रमmat.
 */
अटल अंतरभूत bool xfs_bmap_wants_extents(काष्ठा xfs_inode *ip, पूर्णांक whichविभाजन)
अणु
	काष्ठा xfs_अगरork *अगरp = XFS_IFORK_PTR(ip, whichविभाजन);

	वापस whichविभाजन != XFS_COW_FORK &&
		अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE &&
		अगरp->अगर_nextents <= XFS_IFORK_MAXEXT(ip, whichविभाजन);
पूर्ण

/*
 * Update the record referred to by cur to the value given by irec
 * This either works (वापस 0) or माला_लो an EFSCORRUPTED error.
 */
STATIC पूर्णांक
xfs_bmbt_update(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_bmbt_irec	*irec)
अणु
	जोड़ xfs_btree_rec	rec;

	xfs_bmbt_disk_set_all(&rec.bmbt, irec);
	वापस xfs_btree_update(cur, &rec);
पूर्ण

/*
 * Compute the worst-हाल number of indirect blocks that will be used
 * क्रम ip's delayed extent of length "len".
 */
STATIC xfs_filblks_t
xfs_bmap_worst_indlen(
	xfs_inode_t	*ip,		/* incore inode poपूर्णांकer */
	xfs_filblks_t	len)		/* delayed extent length */
अणु
	पूर्णांक		level;		/* btree level number */
	पूर्णांक		maxrecs;	/* maximum record count at this level */
	xfs_mount_t	*mp;		/* mount काष्ठाure */
	xfs_filblks_t	rval;		/* वापस value */

	mp = ip->i_mount;
	maxrecs = mp->m_bmap_dmxr[0];
	क्रम (level = 0, rval = 0;
	     level < XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK);
	     level++) अणु
		len += maxrecs - 1;
		करो_भाग(len, maxrecs);
		rval += len;
		अगर (len == 1)
			वापस rval + XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK) -
				level - 1;
		अगर (level == 0)
			maxrecs = mp->m_bmap_dmxr[1];
	पूर्ण
	वापस rval;
पूर्ण

/*
 * Calculate the शेष attribute विभाजन offset क्रम newly created inodes.
 */
uपूर्णांक
xfs_शेष_attroffset(
	काष्ठा xfs_inode	*ip)
अणु
	अगर (ip->i_df.अगर_क्रमmat == XFS_DINODE_FMT_DEV)
		वापस roundup(माप(xfs_dev_t), 8);
	वापस M_IGEO(ip->i_mount)->attr_विभाजन_offset;
पूर्ण

/*
 * Helper routine to reset inode i_विभाजनoff field when चयनing attribute विभाजन
 * from local to extent क्रमmat - we reset it where possible to make space
 * available क्रम अंतरभूत data विभाजन extents.
 */
STATIC व्योम
xfs_bmap_विभाजनoff_reset(
	xfs_inode_t	*ip,
	पूर्णांक		whichविभाजन)
अणु
	अगर (whichविभाजन == XFS_ATTR_FORK &&
	    ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_DEV &&
	    ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_BTREE) अणु
		uपूर्णांक	dfl_विभाजनoff = xfs_शेष_attroffset(ip) >> 3;

		अगर (dfl_विभाजनoff > ip->i_विभाजनoff)
			ip->i_विभाजनoff = dfl_विभाजनoff;
	पूर्ण
पूर्ण

#अगर_घोषित DEBUG
STATIC काष्ठा xfs_buf *
xfs_bmap_get_bp(
	काष्ठा xfs_btree_cur	*cur,
	xfs_fsblock_t		bno)
अणु
	काष्ठा xfs_log_item	*lip;
	पूर्णांक			i;

	अगर (!cur)
		वापस शून्य;

	क्रम (i = 0; i < XFS_BTREE_MAXLEVELS; i++) अणु
		अगर (!cur->bc_bufs[i])
			अवरोध;
		अगर (XFS_BUF_ADDR(cur->bc_bufs[i]) == bno)
			वापस cur->bc_bufs[i];
	पूर्ण

	/* Chase करोwn all the log items to see अगर the bp is there */
	list_क्रम_each_entry(lip, &cur->bc_tp->t_items, li_trans) अणु
		काष्ठा xfs_buf_log_item	*bip = (काष्ठा xfs_buf_log_item *)lip;

		अगर (bip->bli_item.li_type == XFS_LI_BUF &&
		    XFS_BUF_ADDR(bip->bli_buf) == bno)
			वापस bip->bli_buf;
	पूर्ण

	वापस शून्य;
पूर्ण

STATIC व्योम
xfs_check_block(
	काष्ठा xfs_btree_block	*block,
	xfs_mount_t		*mp,
	पूर्णांक			root,
	लघु			sz)
अणु
	पूर्णांक			i, j, dmxr;
	__be64			*pp, *thispa;	/* poपूर्णांकer to block address */
	xfs_bmbt_key_t		*prevp, *keyp;

	ASSERT(be16_to_cpu(block->bb_level) > 0);

	prevp = शून्य;
	क्रम( i = 1; i <= xfs_btree_get_numrecs(block); i++) अणु
		dmxr = mp->m_bmap_dmxr[0];
		keyp = XFS_BMBT_KEY_ADDR(mp, block, i);

		अगर (prevp) अणु
			ASSERT(be64_to_cpu(prevp->br_startoff) <
			       be64_to_cpu(keyp->br_startoff));
		पूर्ण
		prevp = keyp;

		/*
		 * Compare the block numbers to see अगर there are dups.
		 */
		अगर (root)
			pp = XFS_BMAP_BROOT_PTR_ADDR(mp, block, i, sz);
		अन्यथा
			pp = XFS_BMBT_PTR_ADDR(mp, block, i, dmxr);

		क्रम (j = i+1; j <= be16_to_cpu(block->bb_numrecs); j++) अणु
			अगर (root)
				thispa = XFS_BMAP_BROOT_PTR_ADDR(mp, block, j, sz);
			अन्यथा
				thispa = XFS_BMBT_PTR_ADDR(mp, block, j, dmxr);
			अगर (*thispa == *pp) अणु
				xfs_warn(mp, "%s: thispa(%d) == pp(%d) %Ld",
					__func__, j, i,
					(अचिन्हित दीर्घ दीर्घ)be64_to_cpu(*thispa));
				xfs_err(mp, "%s: ptrs are equal in node\n",
					__func__);
				xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Check that the extents क्रम the inode ip are in the right order in all
 * btree leaves. THis becomes prohibitively expensive क्रम large extent count
 * files, so करोn't bother with inodes that have more than 10,000 extents in
 * them. The btree record ordering checks will still be करोne, so क्रम such large
 * bmapbt स्थिरructs that is going to catch most corruptions.
 */
STATIC व्योम
xfs_bmap_check_leaf_extents(
	xfs_btree_cur_t		*cur,	/* btree cursor or null */
	xfs_inode_t		*ip,		/* incore inode poपूर्णांकer */
	पूर्णांक			whichविभाजन)	/* data or attr विभाजन */
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_btree_block	*block;	/* current btree block */
	xfs_fsblock_t		bno;	/* block # of "block" */
	काष्ठा xfs_buf		*bp;	/* buffer क्रम "block" */
	पूर्णांक			error;	/* error वापस value */
	xfs_extnum_t		i=0, j;	/* index पूर्णांकo the extents list */
	पूर्णांक			level;	/* btree level, क्रम checking */
	__be64			*pp;	/* poपूर्णांकer to block address */
	xfs_bmbt_rec_t		*ep;	/* poपूर्णांकer to current extent */
	xfs_bmbt_rec_t		last = अणु0, 0पूर्ण; /* last extent in prev block */
	xfs_bmbt_rec_t		*nextp;	/* poपूर्णांकer to next extent */
	पूर्णांक			bp_release = 0;

	अगर (अगरp->अगर_क्रमmat != XFS_DINODE_FMT_BTREE)
		वापस;

	/* skip large extent count inodes */
	अगर (ip->i_df.अगर_nextents > 10000)
		वापस;

	bno = शून्यFSBLOCK;
	block = अगरp->अगर_broot;
	/*
	 * Root level must use BMAP_BROOT_PTR_ADDR macro to get ptr out.
	 */
	level = be16_to_cpu(block->bb_level);
	ASSERT(level > 0);
	xfs_check_block(block, mp, 1, अगरp->अगर_broot_bytes);
	pp = XFS_BMAP_BROOT_PTR_ADDR(mp, block, 1, अगरp->अगर_broot_bytes);
	bno = be64_to_cpu(*pp);

	ASSERT(bno != शून्यFSBLOCK);
	ASSERT(XFS_FSB_TO_AGNO(mp, bno) < mp->m_sb.sb_agcount);
	ASSERT(XFS_FSB_TO_AGBNO(mp, bno) < mp->m_sb.sb_agblocks);

	/*
	 * Go करोwn the tree until leaf level is reached, following the first
	 * poपूर्णांकer (lefपंचांगost) at each level.
	 */
	जबतक (level-- > 0) अणु
		/* See अगर buf is in cur first */
		bp_release = 0;
		bp = xfs_bmap_get_bp(cur, XFS_FSB_TO_DADDR(mp, bno));
		अगर (!bp) अणु
			bp_release = 1;
			error = xfs_btree_पढ़ो_bufl(mp, शून्य, bno, &bp,
						XFS_BMAP_BTREE_REF,
						&xfs_bmbt_buf_ops);
			अगर (error)
				जाओ error_norअन्यथा;
		पूर्ण
		block = XFS_BUF_TO_BLOCK(bp);
		अगर (level == 0)
			अवरोध;

		/*
		 * Check this block क्रम basic sanity (increasing keys and
		 * no duplicate blocks).
		 */

		xfs_check_block(block, mp, 0, 0);
		pp = XFS_BMBT_PTR_ADDR(mp, block, 1, mp->m_bmap_dmxr[1]);
		bno = be64_to_cpu(*pp);
		अगर (XFS_IS_CORRUPT(mp, !xfs_verअगरy_fsbno(mp, bno))) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		अगर (bp_release) अणु
			bp_release = 0;
			xfs_trans_brअन्यथा(शून्य, bp);
		पूर्ण
	पूर्ण

	/*
	 * Here with bp and block set to the lefपंचांगost leaf node in the tree.
	 */
	i = 0;

	/*
	 * Loop over all leaf nodes checking that all extents are in the right order.
	 */
	क्रम (;;) अणु
		xfs_fsblock_t	nextbno;
		xfs_extnum_t	num_recs;


		num_recs = xfs_btree_get_numrecs(block);

		/*
		 * Read-ahead the next leaf block, अगर any.
		 */

		nextbno = be64_to_cpu(block->bb_u.l.bb_rightsib);

		/*
		 * Check all the extents to make sure they are OK.
		 * If we had a previous block, the last entry should
		 * conक्रमm with the first entry in this one.
		 */

		ep = XFS_BMBT_REC_ADDR(mp, block, 1);
		अगर (i) अणु
			ASSERT(xfs_bmbt_disk_get_startoff(&last) +
			       xfs_bmbt_disk_get_blockcount(&last) <=
			       xfs_bmbt_disk_get_startoff(ep));
		पूर्ण
		क्रम (j = 1; j < num_recs; j++) अणु
			nextp = XFS_BMBT_REC_ADDR(mp, block, j + 1);
			ASSERT(xfs_bmbt_disk_get_startoff(ep) +
			       xfs_bmbt_disk_get_blockcount(ep) <=
			       xfs_bmbt_disk_get_startoff(nextp));
			ep = nextp;
		पूर्ण

		last = *ep;
		i += num_recs;
		अगर (bp_release) अणु
			bp_release = 0;
			xfs_trans_brअन्यथा(शून्य, bp);
		पूर्ण
		bno = nextbno;
		/*
		 * If we've reached the end, stop.
		 */
		अगर (bno == शून्यFSBLOCK)
			अवरोध;

		bp_release = 0;
		bp = xfs_bmap_get_bp(cur, XFS_FSB_TO_DADDR(mp, bno));
		अगर (!bp) अणु
			bp_release = 1;
			error = xfs_btree_पढ़ो_bufl(mp, शून्य, bno, &bp,
						XFS_BMAP_BTREE_REF,
						&xfs_bmbt_buf_ops);
			अगर (error)
				जाओ error_norअन्यथा;
		पूर्ण
		block = XFS_BUF_TO_BLOCK(bp);
	पूर्ण

	वापस;

error0:
	xfs_warn(mp, "%s: at error0", __func__);
	अगर (bp_release)
		xfs_trans_brअन्यथा(शून्य, bp);
error_norअन्यथा:
	xfs_warn(mp, "%s: BAD after btree leaves for %d extents",
		__func__, i);
	xfs_err(mp, "%s: CORRUPTED BTREE OR SOMETHING", __func__);
	xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
	वापस;
पूर्ण

/*
 * Validate that the bmbt_irecs being वापसed from bmapi are valid
 * given the caller's original parameters.  Specअगरically check the
 * ranges of the वापसed irecs to ensure that they only extend beyond
 * the given parameters अगर the XFS_BMAPI_ENTIRE flag was set.
 */
STATIC व्योम
xfs_bmap_validate_ret(
	xfs_fileoff_t		bno,
	xfs_filblks_t		len,
	पूर्णांक			flags,
	xfs_bmbt_irec_t		*mval,
	पूर्णांक			nmap,
	पूर्णांक			ret_nmap)
अणु
	पूर्णांक			i;		/* index to map values */

	ASSERT(ret_nmap <= nmap);

	क्रम (i = 0; i < ret_nmap; i++) अणु
		ASSERT(mval[i].br_blockcount > 0);
		अगर (!(flags & XFS_BMAPI_ENTIRE)) अणु
			ASSERT(mval[i].br_startoff >= bno);
			ASSERT(mval[i].br_blockcount <= len);
			ASSERT(mval[i].br_startoff + mval[i].br_blockcount <=
			       bno + len);
		पूर्ण अन्यथा अणु
			ASSERT(mval[i].br_startoff < bno + len);
			ASSERT(mval[i].br_startoff + mval[i].br_blockcount >
			       bno);
		पूर्ण
		ASSERT(i == 0 ||
		       mval[i - 1].br_startoff + mval[i - 1].br_blockcount ==
		       mval[i].br_startoff);
		ASSERT(mval[i].br_startblock != DELAYSTARTBLOCK &&
		       mval[i].br_startblock != HOLESTARTBLOCK);
		ASSERT(mval[i].br_state == XFS_EXT_NORM ||
		       mval[i].br_state == XFS_EXT_UNWRITTEN);
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा xfs_bmap_check_leaf_extents(cur, ip, whichविभाजन)		करो अणु पूर्ण जबतक (0)
#घोषणा	xfs_bmap_validate_ret(bno,len,flags,mval,onmap,nmap)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG */

/*
 * bmap मुक्त list manipulation functions
 */

/*
 * Add the extent to the list of extents to be मुक्त at transaction end.
 * The list is मुख्यtained sorted (by block number).
 */
व्योम
__xfs_bmap_add_मुक्त(
	काष्ठा xfs_trans		*tp,
	xfs_fsblock_t			bno,
	xfs_filblks_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	bool				skip_discard)
अणु
	काष्ठा xfs_extent_मुक्त_item	*new;		/* new element */
#अगर_घोषित DEBUG
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	xfs_agnumber_t			agno;
	xfs_agblock_t			agbno;

	ASSERT(bno != शून्यFSBLOCK);
	ASSERT(len > 0);
	ASSERT(len <= MAXEXTLEN);
	ASSERT(!isnullstartblock(bno));
	agno = XFS_FSB_TO_AGNO(mp, bno);
	agbno = XFS_FSB_TO_AGBNO(mp, bno);
	ASSERT(agno < mp->m_sb.sb_agcount);
	ASSERT(agbno < mp->m_sb.sb_agblocks);
	ASSERT(len < mp->m_sb.sb_agblocks);
	ASSERT(agbno + len <= mp->m_sb.sb_agblocks);
#पूर्ण_अगर
	ASSERT(xfs_bmap_मुक्त_item_zone != शून्य);

	new = kmem_cache_alloc(xfs_bmap_मुक्त_item_zone,
			       GFP_KERNEL | __GFP_NOFAIL);
	new->xefi_startblock = bno;
	new->xefi_blockcount = (xfs_extlen_t)len;
	अगर (oinfo)
		new->xefi_oinfo = *oinfo;
	अन्यथा
		new->xefi_oinfo = XFS_RMAP_OINFO_SKIP_UPDATE;
	new->xefi_skip_discard = skip_discard;
	trace_xfs_bmap_मुक्त_defer(tp->t_mountp,
			XFS_FSB_TO_AGNO(tp->t_mountp, bno), 0,
			XFS_FSB_TO_AGBNO(tp->t_mountp, bno), len);
	xfs_defer_add(tp, XFS_DEFER_OPS_TYPE_FREE, &new->xefi_list);
पूर्ण

/*
 * Inode विभाजन क्रमmat manipulation functions
 */

/*
 * Convert the inode क्रमmat to extent क्रमmat अगर it currently is in btree क्रमmat,
 * but the extent list is small enough that it fits पूर्णांकo the extent क्रमmat.
 *
 * Since the extents are alपढ़ोy in-core, all we have to करो is give up the space
 * क्रम the btree root and pitch the leaf block.
 */
STATIC पूर्णांक				/* error */
xfs_bmap_btree_to_extents(
	काष्ठा xfs_trans	*tp,	/* transaction poपूर्णांकer */
	काष्ठा xfs_inode	*ip,	/* incore inode poपूर्णांकer */
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	पूर्णांक			*logflagsp, /* inode logging flags */
	पूर्णांक			whichविभाजन)  /* data or attr विभाजन */
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_btree_block	*rblock = अगरp->अगर_broot;
	काष्ठा xfs_btree_block	*cblock;/* child btree block */
	xfs_fsblock_t		cbno;	/* child block number */
	काष्ठा xfs_buf		*cbp;	/* child block's buffer */
	पूर्णांक			error;	/* error वापस value */
	__be64			*pp;	/* ptr to block address */
	काष्ठा xfs_owner_info	oinfo;

	/* check अगर we actually need the extent क्रमmat first: */
	अगर (!xfs_bmap_wants_extents(ip, whichविभाजन))
		वापस 0;

	ASSERT(cur);
	ASSERT(whichविभाजन != XFS_COW_FORK);
	ASSERT(अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE);
	ASSERT(be16_to_cpu(rblock->bb_level) == 1);
	ASSERT(be16_to_cpu(rblock->bb_numrecs) == 1);
	ASSERT(xfs_bmbt_maxrecs(mp, अगरp->अगर_broot_bytes, 0) == 1);

	pp = XFS_BMAP_BROOT_PTR_ADDR(mp, rblock, 1, अगरp->अगर_broot_bytes);
	cbno = be64_to_cpu(*pp);
#अगर_घोषित DEBUG
	अगर (XFS_IS_CORRUPT(cur->bc_mp, !xfs_btree_check_lptr(cur, cbno, 1)))
		वापस -EFSCORRUPTED;
#पूर्ण_अगर
	error = xfs_btree_पढ़ो_bufl(mp, tp, cbno, &cbp, XFS_BMAP_BTREE_REF,
				&xfs_bmbt_buf_ops);
	अगर (error)
		वापस error;
	cblock = XFS_BUF_TO_BLOCK(cbp);
	अगर ((error = xfs_btree_check_block(cur, cblock, 0, cbp)))
		वापस error;
	xfs_rmap_ino_bmbt_owner(&oinfo, ip->i_ino, whichविभाजन);
	xfs_bmap_add_मुक्त(cur->bc_tp, cbno, 1, &oinfo);
	ip->i_nblocks--;
	xfs_trans_mod_dquot_byino(tp, ip, XFS_TRANS_DQ_BCOUNT, -1L);
	xfs_trans_binval(tp, cbp);
	अगर (cur->bc_bufs[0] == cbp)
		cur->bc_bufs[0] = शून्य;
	xfs_iroot_पुनः_स्मृति(ip, -1, whichविभाजन);
	ASSERT(अगरp->अगर_broot == शून्य);
	अगरp->अगर_क्रमmat = XFS_DINODE_FMT_EXTENTS;
	*logflagsp |= XFS_ILOG_CORE | xfs_ilog_fext(whichविभाजन);
	वापस 0;
पूर्ण

/*
 * Convert an extents-क्रमmat file पूर्णांकo a btree-क्रमmat file.
 * The new file will have a root block (in the inode) and a single child block.
 */
STATIC पूर्णांक					/* error */
xfs_bmap_extents_to_btree(
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_inode	*ip,		/* incore inode poपूर्णांकer */
	काष्ठा xfs_btree_cur	**curp,		/* cursor वापसed to caller */
	पूर्णांक			wasdel,		/* converting a delayed alloc */
	पूर्णांक			*logflagsp,	/* inode logging flags */
	पूर्णांक			whichविभाजन)	/* data or attr विभाजन */
अणु
	काष्ठा xfs_btree_block	*ablock;	/* allocated (child) bt block */
	काष्ठा xfs_buf		*abp;		/* buffer क्रम ablock */
	काष्ठा xfs_alloc_arg	args;		/* allocation arguments */
	काष्ठा xfs_bmbt_rec	*arp;		/* child record poपूर्णांकer */
	काष्ठा xfs_btree_block	*block;		/* btree root block */
	काष्ठा xfs_btree_cur	*cur;		/* bmap btree cursor */
	पूर्णांक			error;		/* error वापस value */
	काष्ठा xfs_अगरork	*अगरp;		/* inode विभाजन poपूर्णांकer */
	काष्ठा xfs_bmbt_key	*kp;		/* root block key poपूर्णांकer */
	काष्ठा xfs_mount	*mp;		/* mount काष्ठाure */
	xfs_bmbt_ptr_t		*pp;		/* root block address poपूर्णांकer */
	काष्ठा xfs_iext_cursor	icur;
	काष्ठा xfs_bmbt_irec	rec;
	xfs_extnum_t		cnt = 0;

	mp = ip->i_mount;
	ASSERT(whichविभाजन != XFS_COW_FORK);
	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	ASSERT(अगरp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS);

	/*
	 * Make space in the inode incore. This needs to be unकरोne अगर we fail
	 * to expand the root.
	 */
	xfs_iroot_पुनः_स्मृति(ip, 1, whichविभाजन);

	/*
	 * Fill in the root.
	 */
	block = अगरp->अगर_broot;
	xfs_btree_init_block_पूर्णांक(mp, block, XFS_BUF_DADDR_शून्य,
				 XFS_BTNUM_BMAP, 1, 1, ip->i_ino,
				 XFS_BTREE_LONG_PTRS);
	/*
	 * Need a cursor.  Can't allocate until bb_level is filled in.
	 */
	cur = xfs_bmbt_init_cursor(mp, tp, ip, whichविभाजन);
	cur->bc_ino.flags = wasdel ? XFS_BTCUR_BMBT_WASDEL : 0;
	/*
	 * Convert to a btree with two levels, one record in root.
	 */
	अगरp->अगर_क्रमmat = XFS_DINODE_FMT_BTREE;
	स_रखो(&args, 0, माप(args));
	args.tp = tp;
	args.mp = mp;
	xfs_rmap_ino_bmbt_owner(&args.oinfo, ip->i_ino, whichविभाजन);
	अगर (tp->t_firstblock == शून्यFSBLOCK) अणु
		args.type = XFS_ALLOCTYPE_START_BNO;
		args.fsbno = XFS_INO_TO_FSB(mp, ip->i_ino);
	पूर्ण अन्यथा अगर (tp->t_flags & XFS_TRANS_LOWMODE) अणु
		args.type = XFS_ALLOCTYPE_START_BNO;
		args.fsbno = tp->t_firstblock;
	पूर्ण अन्यथा अणु
		args.type = XFS_ALLOCTYPE_NEAR_BNO;
		args.fsbno = tp->t_firstblock;
	पूर्ण
	args.minlen = args.maxlen = args.prod = 1;
	args.wasdel = wasdel;
	*logflagsp = 0;
	error = xfs_alloc_vextent(&args);
	अगर (error)
		जाओ out_root_पुनः_स्मृति;

	अगर (WARN_ON_ONCE(args.fsbno == शून्यFSBLOCK)) अणु
		error = -ENOSPC;
		जाओ out_root_पुनः_स्मृति;
	पूर्ण

	/*
	 * Allocation can't fail, the space was reserved.
	 */
	ASSERT(tp->t_firstblock == शून्यFSBLOCK ||
	       args.agno >= XFS_FSB_TO_AGNO(mp, tp->t_firstblock));
	tp->t_firstblock = args.fsbno;
	cur->bc_ino.allocated++;
	ip->i_nblocks++;
	xfs_trans_mod_dquot_byino(tp, ip, XFS_TRANS_DQ_BCOUNT, 1L);
	error = xfs_trans_get_buf(tp, mp->m_ddev_targp,
			XFS_FSB_TO_DADDR(mp, args.fsbno),
			mp->m_bsize, 0, &abp);
	अगर (error)
		जाओ out_unreserve_dquot;

	/*
	 * Fill in the child block.
	 */
	abp->b_ops = &xfs_bmbt_buf_ops;
	ablock = XFS_BUF_TO_BLOCK(abp);
	xfs_btree_init_block_पूर्णांक(mp, ablock, abp->b_bn,
				XFS_BTNUM_BMAP, 0, 0, ip->i_ino,
				XFS_BTREE_LONG_PTRS);

	क्रम_each_xfs_iext(अगरp, &icur, &rec) अणु
		अगर (isnullstartblock(rec.br_startblock))
			जारी;
		arp = XFS_BMBT_REC_ADDR(mp, ablock, 1 + cnt);
		xfs_bmbt_disk_set_all(arp, &rec);
		cnt++;
	पूर्ण
	ASSERT(cnt == अगरp->अगर_nextents);
	xfs_btree_set_numrecs(ablock, cnt);

	/*
	 * Fill in the root key and poपूर्णांकer.
	 */
	kp = XFS_BMBT_KEY_ADDR(mp, block, 1);
	arp = XFS_BMBT_REC_ADDR(mp, ablock, 1);
	kp->br_startoff = cpu_to_be64(xfs_bmbt_disk_get_startoff(arp));
	pp = XFS_BMBT_PTR_ADDR(mp, block, 1, xfs_bmbt_get_maxrecs(cur,
						be16_to_cpu(block->bb_level)));
	*pp = cpu_to_be64(args.fsbno);

	/*
	 * Do all this logging at the end so that
	 * the root is at the right level.
	 */
	xfs_btree_log_block(cur, abp, XFS_BB_ALL_BITS);
	xfs_btree_log_recs(cur, abp, 1, be16_to_cpu(ablock->bb_numrecs));
	ASSERT(*curp == शून्य);
	*curp = cur;
	*logflagsp = XFS_ILOG_CORE | xfs_ilog_fbroot(whichविभाजन);
	वापस 0;

out_unreserve_dquot:
	xfs_trans_mod_dquot_byino(tp, ip, XFS_TRANS_DQ_BCOUNT, -1L);
out_root_पुनः_स्मृति:
	xfs_iroot_पुनः_स्मृति(ip, -1, whichविभाजन);
	अगरp->अगर_क्रमmat = XFS_DINODE_FMT_EXTENTS;
	ASSERT(अगरp->अगर_broot == शून्य);
	xfs_btree_del_cursor(cur, XFS_BTREE_ERROR);

	वापस error;
पूर्ण

/*
 * Convert a local file to an extents file.
 * This code is out of bounds क्रम data विभाजनs of regular files,
 * since the file data needs to get logged so things will stay consistent.
 * (The bmap-level manipulations are ok, though).
 */
व्योम
xfs_bmap_local_to_extents_empty(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);

	ASSERT(whichविभाजन != XFS_COW_FORK);
	ASSERT(अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	ASSERT(अगरp->अगर_bytes == 0);
	ASSERT(अगरp->अगर_nextents == 0);

	xfs_bmap_विभाजनoff_reset(ip, whichविभाजन);
	अगरp->अगर_u1.अगर_root = शून्य;
	अगरp->अगर_height = 0;
	अगरp->अगर_क्रमmat = XFS_DINODE_FMT_EXTENTS;
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
पूर्ण


STATIC पूर्णांक				/* error */
xfs_bmap_local_to_extents(
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_inode_t	*ip,		/* incore inode poपूर्णांकer */
	xfs_extlen_t	total,		/* total blocks needed by transaction */
	पूर्णांक		*logflagsp,	/* inode logging flags */
	पूर्णांक		whichविभाजन,
	व्योम		(*init_fn)(काष्ठा xfs_trans *tp,
				   काष्ठा xfs_buf *bp,
				   काष्ठा xfs_inode *ip,
				   काष्ठा xfs_अगरork *अगरp))
अणु
	पूर्णांक		error = 0;
	पूर्णांक		flags;		/* logging flags वापसed */
	काष्ठा xfs_अगरork *अगरp;		/* inode विभाजन poपूर्णांकer */
	xfs_alloc_arg_t	args;		/* allocation arguments */
	काष्ठा xfs_buf	*bp;		/* buffer क्रम extent block */
	काष्ठा xfs_bmbt_irec rec;
	काष्ठा xfs_iext_cursor icur;

	/*
	 * We करोn't want to deal with the हाल of keeping inode data अंतरभूत yet.
	 * So sending the data विभाजन of a regular inode is invalid.
	 */
	ASSERT(!(S_ISREG(VFS_I(ip)->i_mode) && whichविभाजन == XFS_DATA_FORK));
	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	ASSERT(अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);

	अगर (!अगरp->अगर_bytes) अणु
		xfs_bmap_local_to_extents_empty(tp, ip, whichविभाजन);
		flags = XFS_ILOG_CORE;
		जाओ करोne;
	पूर्ण

	flags = 0;
	error = 0;
	स_रखो(&args, 0, माप(args));
	args.tp = tp;
	args.mp = ip->i_mount;
	xfs_rmap_ino_owner(&args.oinfo, ip->i_ino, whichविभाजन, 0);
	/*
	 * Allocate a block.  We know we need only one, since the
	 * file currently fits in an inode.
	 */
	अगर (tp->t_firstblock == शून्यFSBLOCK) अणु
		args.fsbno = XFS_INO_TO_FSB(args.mp, ip->i_ino);
		args.type = XFS_ALLOCTYPE_START_BNO;
	पूर्ण अन्यथा अणु
		args.fsbno = tp->t_firstblock;
		args.type = XFS_ALLOCTYPE_NEAR_BNO;
	पूर्ण
	args.total = total;
	args.minlen = args.maxlen = args.prod = 1;
	error = xfs_alloc_vextent(&args);
	अगर (error)
		जाओ करोne;

	/* Can't fail, the space was reserved. */
	ASSERT(args.fsbno != शून्यFSBLOCK);
	ASSERT(args.len == 1);
	tp->t_firstblock = args.fsbno;
	error = xfs_trans_get_buf(tp, args.mp->m_ddev_targp,
			XFS_FSB_TO_DADDR(args.mp, args.fsbno),
			args.mp->m_bsize, 0, &bp);
	अगर (error)
		जाओ करोne;

	/*
	 * Initialize the block, copy the data and log the remote buffer.
	 *
	 * The callout is responsible क्रम logging because the remote क्रमmat
	 * might dअगरfer from the local क्रमmat and thus we करोn't know how much to
	 * log here. Note that init_fn must also set the buffer log item type
	 * correctly.
	 */
	init_fn(tp, bp, ip, अगरp);

	/* account क्रम the change in विभाजन size */
	xfs_idata_पुनः_स्मृति(ip, -अगरp->अगर_bytes, whichविभाजन);
	xfs_bmap_local_to_extents_empty(tp, ip, whichविभाजन);
	flags |= XFS_ILOG_CORE;

	अगरp->अगर_u1.अगर_root = शून्य;
	अगरp->अगर_height = 0;

	rec.br_startoff = 0;
	rec.br_startblock = args.fsbno;
	rec.br_blockcount = 1;
	rec.br_state = XFS_EXT_NORM;
	xfs_iext_first(अगरp, &icur);
	xfs_iext_insert(ip, &icur, &rec, 0);

	अगरp->अगर_nextents = 1;
	ip->i_nblocks = 1;
	xfs_trans_mod_dquot_byino(tp, ip,
		XFS_TRANS_DQ_BCOUNT, 1L);
	flags |= xfs_ilog_fext(whichविभाजन);

करोne:
	*logflagsp = flags;
	वापस error;
पूर्ण

/*
 * Called from xfs_bmap_add_attrविभाजन to handle btree क्रमmat files.
 */
STATIC पूर्णांक					/* error */
xfs_bmap_add_attrविभाजन_btree(
	xfs_trans_t		*tp,		/* transaction poपूर्णांकer */
	xfs_inode_t		*ip,		/* incore inode poपूर्णांकer */
	पूर्णांक			*flags)		/* inode logging flags */
अणु
	काष्ठा xfs_btree_block	*block = ip->i_df.अगर_broot;
	xfs_btree_cur_t		*cur;		/* btree cursor */
	पूर्णांक			error;		/* error वापस value */
	xfs_mount_t		*mp;		/* file प्रणाली mount काष्ठा */
	पूर्णांक			stat;		/* newroot status */

	mp = ip->i_mount;

	अगर (XFS_BMAP_BMDR_SPACE(block) <= XFS_IFORK_DSIZE(ip))
		*flags |= XFS_ILOG_DBROOT;
	अन्यथा अणु
		cur = xfs_bmbt_init_cursor(mp, tp, ip, XFS_DATA_FORK);
		error = xfs_bmbt_lookup_first(cur, &stat);
		अगर (error)
			जाओ error0;
		/* must be at least one entry */
		अगर (XFS_IS_CORRUPT(mp, stat != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		अगर ((error = xfs_btree_new_iroot(cur, flags, &stat)))
			जाओ error0;
		अगर (stat == 0) अणु
			xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
			वापस -ENOSPC;
		पूर्ण
		cur->bc_ino.allocated = 0;
		xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
	पूर्ण
	वापस 0;
error0:
	xfs_btree_del_cursor(cur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/*
 * Called from xfs_bmap_add_attrविभाजन to handle extents क्रमmat files.
 */
STATIC पूर्णांक					/* error */
xfs_bmap_add_attrविभाजन_extents(
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_inode	*ip,		/* incore inode poपूर्णांकer */
	पूर्णांक			*flags)		/* inode logging flags */
अणु
	xfs_btree_cur_t		*cur;		/* bmap btree cursor */
	पूर्णांक			error;		/* error वापस value */

	अगर (ip->i_df.अगर_nextents * माप(काष्ठा xfs_bmbt_rec) <=
	    XFS_IFORK_DSIZE(ip))
		वापस 0;
	cur = शून्य;
	error = xfs_bmap_extents_to_btree(tp, ip, &cur, 0, flags,
					  XFS_DATA_FORK);
	अगर (cur) अणु
		cur->bc_ino.allocated = 0;
		xfs_btree_del_cursor(cur, error);
	पूर्ण
	वापस error;
पूर्ण

/*
 * Called from xfs_bmap_add_attrविभाजन to handle local क्रमmat files. Each
 * dअगरferent data विभाजन content type needs a dअगरferent callout to करो the
 * conversion. Some are basic and only require special block initialisation
 * callouts क्रम the data क्रमmating, others (directories) are so specialised they
 * handle everything themselves.
 *
 * XXX (dgc): investigate whether directory conversion can use the generic
 * क्रमmatting callout. It should be possible - it's just a very complex
 * क्रमmatter.
 */
STATIC पूर्णांक					/* error */
xfs_bmap_add_attrविभाजन_local(
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_inode	*ip,		/* incore inode poपूर्णांकer */
	पूर्णांक			*flags)		/* inode logging flags */
अणु
	काष्ठा xfs_da_args	dargs;		/* args क्रम dir/attr code */

	अगर (ip->i_df.अगर_bytes <= XFS_IFORK_DSIZE(ip))
		वापस 0;

	अगर (S_ISसूची(VFS_I(ip)->i_mode)) अणु
		स_रखो(&dargs, 0, माप(dargs));
		dargs.geo = ip->i_mount->m_dir_geo;
		dargs.dp = ip;
		dargs.total = dargs.geo->fsbcount;
		dargs.whichविभाजन = XFS_DATA_FORK;
		dargs.trans = tp;
		वापस xfs_dir2_sf_to_block(&dargs);
	पूर्ण

	अगर (S_ISLNK(VFS_I(ip)->i_mode))
		वापस xfs_bmap_local_to_extents(tp, ip, 1, flags,
						 XFS_DATA_FORK,
						 xfs_symlink_local_to_remote);

	/* should only be called क्रम types that support local क्रमmat data */
	ASSERT(0);
	वापस -EFSCORRUPTED;
पूर्ण

/*
 * Set an inode attr विभाजन offset based on the क्रमmat of the data विभाजन.
 */
पूर्णांक
xfs_bmap_set_attrविभाजनoff(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			size,
	पूर्णांक			*version)
अणु
	पूर्णांक			शेष_size = xfs_शेष_attroffset(ip) >> 3;

	चयन (ip->i_df.अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_DEV:
		ip->i_विभाजनoff = शेष_size;
		अवरोध;
	हाल XFS_DINODE_FMT_LOCAL:
	हाल XFS_DINODE_FMT_EXTENTS:
	हाल XFS_DINODE_FMT_BTREE:
		ip->i_विभाजनoff = xfs_attr_लघुक्रमm_bytesfit(ip, size);
		अगर (!ip->i_विभाजनoff)
			ip->i_विभाजनoff = शेष_size;
		अन्यथा अगर ((ip->i_mount->m_flags & XFS_MOUNT_ATTR2) && version)
			*version = 2;
		अवरोध;
	शेष:
		ASSERT(0);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Convert inode from non-attributed to attributed.
 * Must not be in a transaction, ip must not be locked.
 */
पूर्णांक						/* error code */
xfs_bmap_add_attrविभाजन(
	xfs_inode_t		*ip,		/* incore inode poपूर्णांकer */
	पूर्णांक			size,		/* space new attribute needs */
	पूर्णांक			rsvd)		/* xact may use reserved blks */
अणु
	xfs_mount_t		*mp;		/* mount काष्ठाure */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	पूर्णांक			blks;		/* space reservation */
	पूर्णांक			version = 1;	/* superblock attr version */
	पूर्णांक			logflags;	/* logging flags */
	पूर्णांक			error;		/* error वापस value */

	ASSERT(XFS_IFORK_Q(ip) == 0);

	mp = ip->i_mount;
	ASSERT(!XFS_NOT_DQATTACHED(mp, ip));

	blks = XFS_ADDAFORK_SPACE_RES(mp);

	error = xfs_trans_alloc_inode(ip, &M_RES(mp)->tr_addaविभाजन, blks, 0,
			rsvd, &tp);
	अगर (error)
		वापस error;
	अगर (XFS_IFORK_Q(ip))
		जाओ trans_cancel;

	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	error = xfs_bmap_set_attrविभाजनoff(ip, size, &version);
	अगर (error)
		जाओ trans_cancel;
	ASSERT(ip->i_afp == शून्य);

	ip->i_afp = xfs_अगरork_alloc(XFS_DINODE_FMT_EXTENTS, 0);
	logflags = 0;
	चयन (ip->i_df.अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_LOCAL:
		error = xfs_bmap_add_attrविभाजन_local(tp, ip, &logflags);
		अवरोध;
	हाल XFS_DINODE_FMT_EXTENTS:
		error = xfs_bmap_add_attrविभाजन_extents(tp, ip, &logflags);
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		error = xfs_bmap_add_attrविभाजन_btree(tp, ip, &logflags);
		अवरोध;
	शेष:
		error = 0;
		अवरोध;
	पूर्ण
	अगर (logflags)
		xfs_trans_log_inode(tp, ip, logflags);
	अगर (error)
		जाओ trans_cancel;
	अगर (!xfs_sb_version_hasattr(&mp->m_sb) ||
	   (!xfs_sb_version_hasattr2(&mp->m_sb) && version == 2)) अणु
		bool log_sb = false;

		spin_lock(&mp->m_sb_lock);
		अगर (!xfs_sb_version_hasattr(&mp->m_sb)) अणु
			xfs_sb_version_addattr(&mp->m_sb);
			log_sb = true;
		पूर्ण
		अगर (!xfs_sb_version_hasattr2(&mp->m_sb) && version == 2) अणु
			xfs_sb_version_addattr2(&mp->m_sb);
			log_sb = true;
		पूर्ण
		spin_unlock(&mp->m_sb_lock);
		अगर (log_sb)
			xfs_log_sb(tp);
	पूर्ण

	error = xfs_trans_commit(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;

trans_cancel:
	xfs_trans_cancel(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

/*
 * Internal and बाह्यal extent tree search functions.
 */

काष्ठा xfs_iपढ़ो_state अणु
	काष्ठा xfs_iext_cursor	icur;
	xfs_extnum_t		loaded;
पूर्ण;

/* Stuff every bmbt record from this block पूर्णांकo the incore extent map. */
अटल पूर्णांक
xfs_iपढ़ो_bmbt_block(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	व्योम			*priv)
अणु
	काष्ठा xfs_iपढ़ो_state	*ir = priv;
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	काष्ठा xfs_inode	*ip = cur->bc_ino.ip;
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_bmbt_rec	*frp;
	xfs_extnum_t		num_recs;
	xfs_extnum_t		j;
	पूर्णांक			whichविभाजन = cur->bc_ino.whichविभाजन;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);

	block = xfs_btree_get_block(cur, level, &bp);

	/* Abort अगर we find more records than nextents. */
	num_recs = xfs_btree_get_numrecs(block);
	अगर (unlikely(ir->loaded + num_recs > अगरp->अगर_nextents)) अणु
		xfs_warn(ip->i_mount, "corrupt dinode %llu, (btree extents).",
				(अचिन्हित दीर्घ दीर्घ)ip->i_ino);
		xfs_inode_verअगरier_error(ip, -EFSCORRUPTED, __func__, block,
				माप(*block), __this_address);
		वापस -EFSCORRUPTED;
	पूर्ण

	/* Copy records पूर्णांकo the incore cache. */
	frp = XFS_BMBT_REC_ADDR(mp, block, 1);
	क्रम (j = 0; j < num_recs; j++, frp++, ir->loaded++) अणु
		काष्ठा xfs_bmbt_irec	new;
		xfs_failaddr_t		fa;

		xfs_bmbt_disk_get_all(frp, &new);
		fa = xfs_bmap_validate_extent(ip, whichविभाजन, &new);
		अगर (fa) अणु
			xfs_inode_verअगरier_error(ip, -EFSCORRUPTED,
					"xfs_iread_extents(2)", frp,
					माप(*frp), fa);
			वापस -EFSCORRUPTED;
		पूर्ण
		xfs_iext_insert(ip, &ir->icur, &new,
				xfs_bmap_विभाजन_to_state(whichविभाजन));
		trace_xfs_पढ़ो_extent(ip, &ir->icur,
				xfs_bmap_विभाजन_to_state(whichविभाजन), _THIS_IP_);
		xfs_iext_next(अगरp, &ir->icur);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Read in extents from a btree-क्रमmat inode.
 */
पूर्णांक
xfs_iपढ़ो_extents(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_iपढ़ो_state	ir;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_btree_cur	*cur;
	पूर्णांक			error;

	अगर (!xfs_need_iपढ़ो_extents(अगरp))
		वापस 0;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	ir.loaded = 0;
	xfs_iext_first(अगरp, &ir.icur);
	cur = xfs_bmbt_init_cursor(mp, tp, ip, whichविभाजन);
	error = xfs_btree_visit_blocks(cur, xfs_iपढ़ो_bmbt_block,
			XFS_BTREE_VISIT_RECORDS, &ir);
	xfs_btree_del_cursor(cur, error);
	अगर (error)
		जाओ out;

	अगर (XFS_IS_CORRUPT(mp, ir.loaded != अगरp->अगर_nextents)) अणु
		error = -EFSCORRUPTED;
		जाओ out;
	पूर्ण
	ASSERT(ir.loaded == xfs_iext_count(अगरp));
	वापस 0;
out:
	xfs_iext_destroy(अगरp);
	वापस error;
पूर्ण

/*
 * Returns the relative block number of the first unused block(s) in the given
 * विभाजन with at least "len" logically contiguous blocks मुक्त.  This is the
 * lowest-address hole अगर the विभाजन has holes, अन्यथा the first block past the end
 * of विभाजन.  Return 0 अगर the विभाजन is currently local (in-inode).
 */
पूर्णांक						/* error */
xfs_bmap_first_unused(
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_inode	*ip,		/* incore inode */
	xfs_extlen_t		len,		/* size of hole to find */
	xfs_fileoff_t		*first_unused,	/* unused block */
	पूर्णांक			whichविभाजन)	/* data or attr विभाजन */
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_bmbt_irec	got;
	काष्ठा xfs_iext_cursor	icur;
	xfs_fileoff_t		lastaddr = 0;
	xfs_fileoff_t		lowest, max;
	पूर्णांक			error;

	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL) अणु
		*first_unused = 0;
		वापस 0;
	पूर्ण

	ASSERT(xfs_अगरork_has_extents(अगरp));

	error = xfs_iपढ़ो_extents(tp, ip, whichविभाजन);
	अगर (error)
		वापस error;

	lowest = max = *first_unused;
	क्रम_each_xfs_iext(अगरp, &icur, &got) अणु
		/*
		 * See अगर the hole beक्रमe this extent will work.
		 */
		अगर (got.br_startoff >= lowest + len &&
		    got.br_startoff - max >= len)
			अवरोध;
		lastaddr = got.br_startoff + got.br_blockcount;
		max = XFS_खाताOFF_MAX(lastaddr, lowest);
	पूर्ण

	*first_unused = max;
	वापस 0;
पूर्ण

/*
 * Returns the file-relative block number of the last block - 1 beक्रमe
 * last_block (input value) in the file.
 * This is not based on i_size, it is based on the extent records.
 * Returns 0 क्रम local files, as they करो not have extent records.
 */
पूर्णांक						/* error */
xfs_bmap_last_beक्रमe(
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_inode	*ip,		/* incore inode */
	xfs_fileoff_t		*last_block,	/* last block */
	पूर्णांक			whichविभाजन)	/* data or attr विभाजन */
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_bmbt_irec	got;
	काष्ठा xfs_iext_cursor	icur;
	पूर्णांक			error;

	चयन (अगरp->अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_LOCAL:
		*last_block = 0;
		वापस 0;
	हाल XFS_DINODE_FMT_BTREE:
	हाल XFS_DINODE_FMT_EXTENTS:
		अवरोध;
	शेष:
		ASSERT(0);
		वापस -EFSCORRUPTED;
	पूर्ण

	error = xfs_iपढ़ो_extents(tp, ip, whichविभाजन);
	अगर (error)
		वापस error;

	अगर (!xfs_iext_lookup_extent_beक्रमe(ip, अगरp, last_block, &icur, &got))
		*last_block = 0;
	वापस 0;
पूर्ण

पूर्णांक
xfs_bmap_last_extent(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_bmbt_irec	*rec,
	पूर्णांक			*is_empty)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_iext_cursor	icur;
	पूर्णांक			error;

	error = xfs_iपढ़ो_extents(tp, ip, whichविभाजन);
	अगर (error)
		वापस error;

	xfs_iext_last(अगरp, &icur);
	अगर (!xfs_iext_get_extent(अगरp, &icur, rec))
		*is_empty = 1;
	अन्यथा
		*is_empty = 0;
	वापस 0;
पूर्ण

/*
 * Check the last inode extent to determine whether this allocation will result
 * in blocks being allocated at the end of the file. When we allocate new data
 * blocks at the end of the file which करो not start at the previous data block,
 * we will try to align the new blocks at stripe unit boundaries.
 *
 * Returns 1 in bma->aeof अगर the file (विभाजन) is empty as any new ग_लिखो will be
 * at, or past the खातापूर्ण.
 */
STATIC पूर्णांक
xfs_bmap_isaeof(
	काष्ठा xfs_bदो_स्मृतिa	*bma,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_bmbt_irec	rec;
	पूर्णांक			is_empty;
	पूर्णांक			error;

	bma->aeof = false;
	error = xfs_bmap_last_extent(शून्य, bma->ip, whichविभाजन, &rec,
				     &is_empty);
	अगर (error)
		वापस error;

	अगर (is_empty) अणु
		bma->aeof = true;
		वापस 0;
	पूर्ण

	/*
	 * Check अगर we are allocation or past the last extent, or at least पूर्णांकo
	 * the last delayed allocated extent.
	 */
	bma->aeof = bma->offset >= rec.br_startoff + rec.br_blockcount ||
		(bma->offset >= rec.br_startoff &&
		 isnullstartblock(rec.br_startblock));
	वापस 0;
पूर्ण

/*
 * Returns the file-relative block number of the first block past eof in
 * the file.  This is not based on i_size, it is based on the extent records.
 * Returns 0 क्रम local files, as they करो not have extent records.
 */
पूर्णांक
xfs_bmap_last_offset(
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		*last_block,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_bmbt_irec	rec;
	पूर्णांक			is_empty;
	पूर्णांक			error;

	*last_block = 0;

	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL)
		वापस 0;

	अगर (XFS_IS_CORRUPT(ip->i_mount, !xfs_अगरork_has_extents(अगरp)))
		वापस -EFSCORRUPTED;

	error = xfs_bmap_last_extent(शून्य, ip, whichविभाजन, &rec, &is_empty);
	अगर (error || is_empty)
		वापस error;

	*last_block = rec.br_startoff + rec.br_blockcount;
	वापस 0;
पूर्ण

/*
 * Extent tree manipulation functions used during allocation.
 */

/*
 * Convert a delayed allocation to a real allocation.
 */
STATIC पूर्णांक				/* error */
xfs_bmap_add_extent_delay_real(
	काष्ठा xfs_bदो_स्मृतिa	*bma,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_mount	*mp = bma->ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(bma->ip, whichविभाजन);
	काष्ठा xfs_bmbt_irec	*new = &bma->got;
	पूर्णांक			error;	/* error वापस value */
	पूर्णांक			i;	/* temp state */
	xfs_fileoff_t		new_enकरोff;	/* end offset of new entry */
	xfs_bmbt_irec_t		r[3];	/* neighbor extent entries */
					/* left is 0, right is 1, prev is 2 */
	पूर्णांक			rval=0;	/* वापस value (logging flags) */
	पूर्णांक			state = xfs_bmap_विभाजन_to_state(whichविभाजन);
	xfs_filblks_t		da_new; /* new count del alloc blocks used */
	xfs_filblks_t		da_old; /* old count del alloc blocks used */
	xfs_filblks_t		temp=0;	/* value क्रम da_new calculations */
	पूर्णांक			पंचांगp_rval;	/* partial logging flags */
	काष्ठा xfs_bmbt_irec	old;

	ASSERT(whichविभाजन != XFS_ATTR_FORK);
	ASSERT(!isnullstartblock(new->br_startblock));
	ASSERT(!bma->cur ||
	       (bma->cur->bc_ino.flags & XFS_BTCUR_BMBT_WASDEL));

	XFS_STATS_INC(mp, xs_add_exlist);

#घोषणा	LEFT		r[0]
#घोषणा	RIGHT		r[1]
#घोषणा	PREV		r[2]

	/*
	 * Set up a bunch of variables to make the tests simpler.
	 */
	xfs_iext_get_extent(अगरp, &bma->icur, &PREV);
	new_enकरोff = new->br_startoff + new->br_blockcount;
	ASSERT(isnullstartblock(PREV.br_startblock));
	ASSERT(PREV.br_startoff <= new->br_startoff);
	ASSERT(PREV.br_startoff + PREV.br_blockcount >= new_enकरोff);

	da_old = startblockval(PREV.br_startblock);
	da_new = 0;

	/*
	 * Set flags determining what part of the previous delayed allocation
	 * extent is being replaced by a real allocation.
	 */
	अगर (PREV.br_startoff == new->br_startoff)
		state |= BMAP_LEFT_FILLING;
	अगर (PREV.br_startoff + PREV.br_blockcount == new_enकरोff)
		state |= BMAP_RIGHT_FILLING;

	/*
	 * Check and set flags अगर this segment has a left neighbor.
	 * Don't set contiguous अगर the combined extent would be too large.
	 */
	अगर (xfs_iext_peek_prev_extent(अगरp, &bma->icur, &LEFT)) अणु
		state |= BMAP_LEFT_VALID;
		अगर (isnullstartblock(LEFT.br_startblock))
			state |= BMAP_LEFT_DELAY;
	पूर्ण

	अगर ((state & BMAP_LEFT_VALID) && !(state & BMAP_LEFT_DELAY) &&
	    LEFT.br_startoff + LEFT.br_blockcount == new->br_startoff &&
	    LEFT.br_startblock + LEFT.br_blockcount == new->br_startblock &&
	    LEFT.br_state == new->br_state &&
	    LEFT.br_blockcount + new->br_blockcount <= MAXEXTLEN)
		state |= BMAP_LEFT_CONTIG;

	/*
	 * Check and set flags अगर this segment has a right neighbor.
	 * Don't set contiguous अगर the combined extent would be too large.
	 * Also check क्रम all-three-contiguous being too large.
	 */
	अगर (xfs_iext_peek_next_extent(अगरp, &bma->icur, &RIGHT)) अणु
		state |= BMAP_RIGHT_VALID;
		अगर (isnullstartblock(RIGHT.br_startblock))
			state |= BMAP_RIGHT_DELAY;
	पूर्ण

	अगर ((state & BMAP_RIGHT_VALID) && !(state & BMAP_RIGHT_DELAY) &&
	    new_enकरोff == RIGHT.br_startoff &&
	    new->br_startblock + new->br_blockcount == RIGHT.br_startblock &&
	    new->br_state == RIGHT.br_state &&
	    new->br_blockcount + RIGHT.br_blockcount <= MAXEXTLEN &&
	    ((state & (BMAP_LEFT_CONTIG | BMAP_LEFT_FILLING |
		       BMAP_RIGHT_FILLING)) !=
		      (BMAP_LEFT_CONTIG | BMAP_LEFT_FILLING |
		       BMAP_RIGHT_FILLING) ||
	     LEFT.br_blockcount + new->br_blockcount + RIGHT.br_blockcount
			<= MAXEXTLEN))
		state |= BMAP_RIGHT_CONTIG;

	error = 0;
	/*
	 * Switch out based on the FILLING and CONTIG state bits.
	 */
	चयन (state & (BMAP_LEFT_FILLING | BMAP_LEFT_CONTIG |
			 BMAP_RIGHT_FILLING | BMAP_RIGHT_CONTIG)) अणु
	हाल BMAP_LEFT_FILLING | BMAP_LEFT_CONTIG |
	     BMAP_RIGHT_FILLING | BMAP_RIGHT_CONTIG:
		/*
		 * Filling in all of a previously delayed allocation extent.
		 * The left and right neighbors are both contiguous with new.
		 */
		LEFT.br_blockcount += PREV.br_blockcount + RIGHT.br_blockcount;

		xfs_iext_हटाओ(bma->ip, &bma->icur, state);
		xfs_iext_हटाओ(bma->ip, &bma->icur, state);
		xfs_iext_prev(अगरp, &bma->icur);
		xfs_iext_update_extent(bma->ip, state, &bma->icur, &LEFT);
		अगरp->अगर_nextents--;

		अगर (bma->cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(bma->cur, &RIGHT, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_btree_delete(bma->cur, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_btree_decrement(bma->cur, 0, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(bma->cur, &LEFT);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING | BMAP_LEFT_CONTIG:
		/*
		 * Filling in all of a previously delayed allocation extent.
		 * The left neighbor is contiguous, the right is not.
		 */
		old = LEFT;
		LEFT.br_blockcount += PREV.br_blockcount;

		xfs_iext_हटाओ(bma->ip, &bma->icur, state);
		xfs_iext_prev(अगरp, &bma->icur);
		xfs_iext_update_extent(bma->ip, state, &bma->icur, &LEFT);

		अगर (bma->cur == शून्य)
			rval = XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = 0;
			error = xfs_bmbt_lookup_eq(bma->cur, &old, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(bma->cur, &LEFT);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING | BMAP_RIGHT_CONTIG:
		/*
		 * Filling in all of a previously delayed allocation extent.
		 * The right neighbor is contiguous, the left is not. Take care
		 * with delay -> unwritten extent allocation here because the
		 * delalloc record we are overwriting is always written.
		 */
		PREV.br_startblock = new->br_startblock;
		PREV.br_blockcount += RIGHT.br_blockcount;
		PREV.br_state = new->br_state;

		xfs_iext_next(अगरp, &bma->icur);
		xfs_iext_हटाओ(bma->ip, &bma->icur, state);
		xfs_iext_prev(अगरp, &bma->icur);
		xfs_iext_update_extent(bma->ip, state, &bma->icur, &PREV);

		अगर (bma->cur == शून्य)
			rval = XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = 0;
			error = xfs_bmbt_lookup_eq(bma->cur, &RIGHT, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(bma->cur, &PREV);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING:
		/*
		 * Filling in all of a previously delayed allocation extent.
		 * Neither the left nor right neighbors are contiguous with
		 * the new one.
		 */
		PREV.br_startblock = new->br_startblock;
		PREV.br_state = new->br_state;
		xfs_iext_update_extent(bma->ip, state, &bma->icur, &PREV);
		अगरp->अगर_nextents++;

		अगर (bma->cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(bma->cur, new, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_btree_insert(bma->cur, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING | BMAP_LEFT_CONTIG:
		/*
		 * Filling in the first part of a previous delayed allocation.
		 * The left neighbor is contiguous.
		 */
		old = LEFT;
		temp = PREV.br_blockcount - new->br_blockcount;
		da_new = XFS_FILBLKS_MIN(xfs_bmap_worst_indlen(bma->ip, temp),
				startblockval(PREV.br_startblock));

		LEFT.br_blockcount += new->br_blockcount;

		PREV.br_blockcount = temp;
		PREV.br_startoff += new->br_blockcount;
		PREV.br_startblock = nullstartblock(da_new);

		xfs_iext_update_extent(bma->ip, state, &bma->icur, &PREV);
		xfs_iext_prev(अगरp, &bma->icur);
		xfs_iext_update_extent(bma->ip, state, &bma->icur, &LEFT);

		अगर (bma->cur == शून्य)
			rval = XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = 0;
			error = xfs_bmbt_lookup_eq(bma->cur, &old, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(bma->cur, &LEFT);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING:
		/*
		 * Filling in the first part of a previous delayed allocation.
		 * The left neighbor is not contiguous.
		 */
		xfs_iext_update_extent(bma->ip, state, &bma->icur, new);
		अगरp->अगर_nextents++;

		अगर (bma->cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(bma->cur, new, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_btree_insert(bma->cur, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
		पूर्ण

		अगर (xfs_bmap_needs_btree(bma->ip, whichविभाजन)) अणु
			error = xfs_bmap_extents_to_btree(bma->tp, bma->ip,
					&bma->cur, 1, &पंचांगp_rval, whichविभाजन);
			rval |= पंचांगp_rval;
			अगर (error)
				जाओ करोne;
		पूर्ण

		temp = PREV.br_blockcount - new->br_blockcount;
		da_new = XFS_FILBLKS_MIN(xfs_bmap_worst_indlen(bma->ip, temp),
			startblockval(PREV.br_startblock) -
			(bma->cur ? bma->cur->bc_ino.allocated : 0));

		PREV.br_startoff = new_enकरोff;
		PREV.br_blockcount = temp;
		PREV.br_startblock = nullstartblock(da_new);
		xfs_iext_next(अगरp, &bma->icur);
		xfs_iext_insert(bma->ip, &bma->icur, &PREV, state);
		xfs_iext_prev(अगरp, &bma->icur);
		अवरोध;

	हाल BMAP_RIGHT_FILLING | BMAP_RIGHT_CONTIG:
		/*
		 * Filling in the last part of a previous delayed allocation.
		 * The right neighbor is contiguous with the new allocation.
		 */
		old = RIGHT;
		RIGHT.br_startoff = new->br_startoff;
		RIGHT.br_startblock = new->br_startblock;
		RIGHT.br_blockcount += new->br_blockcount;

		अगर (bma->cur == शून्य)
			rval = XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = 0;
			error = xfs_bmbt_lookup_eq(bma->cur, &old, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(bma->cur, &RIGHT);
			अगर (error)
				जाओ करोne;
		पूर्ण

		temp = PREV.br_blockcount - new->br_blockcount;
		da_new = XFS_FILBLKS_MIN(xfs_bmap_worst_indlen(bma->ip, temp),
			startblockval(PREV.br_startblock));

		PREV.br_blockcount = temp;
		PREV.br_startblock = nullstartblock(da_new);

		xfs_iext_update_extent(bma->ip, state, &bma->icur, &PREV);
		xfs_iext_next(अगरp, &bma->icur);
		xfs_iext_update_extent(bma->ip, state, &bma->icur, &RIGHT);
		अवरोध;

	हाल BMAP_RIGHT_FILLING:
		/*
		 * Filling in the last part of a previous delayed allocation.
		 * The right neighbor is not contiguous.
		 */
		xfs_iext_update_extent(bma->ip, state, &bma->icur, new);
		अगरp->अगर_nextents++;

		अगर (bma->cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(bma->cur, new, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_btree_insert(bma->cur, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
		पूर्ण

		अगर (xfs_bmap_needs_btree(bma->ip, whichविभाजन)) अणु
			error = xfs_bmap_extents_to_btree(bma->tp, bma->ip,
				&bma->cur, 1, &पंचांगp_rval, whichविभाजन);
			rval |= पंचांगp_rval;
			अगर (error)
				जाओ करोne;
		पूर्ण

		temp = PREV.br_blockcount - new->br_blockcount;
		da_new = XFS_FILBLKS_MIN(xfs_bmap_worst_indlen(bma->ip, temp),
			startblockval(PREV.br_startblock) -
			(bma->cur ? bma->cur->bc_ino.allocated : 0));

		PREV.br_startblock = nullstartblock(da_new);
		PREV.br_blockcount = temp;
		xfs_iext_insert(bma->ip, &bma->icur, &PREV, state);
		xfs_iext_next(अगरp, &bma->icur);
		अवरोध;

	हाल 0:
		/*
		 * Filling in the middle part of a previous delayed allocation.
		 * Contiguity is impossible here.
		 * This हाल is aव्योमed almost all the समय.
		 *
		 * We start with a delayed allocation:
		 *
		 * +ddddddddddddddddddddddddddddddddddddddddddddddddddddddd+
		 *  PREV @ idx
		 *
	         * and we are allocating:
		 *                     +rrrrrrrrrrrrrrrrr+
		 *			      new
		 *
		 * and we set it up क्रम insertion as:
		 * +ddddddddddddddddddd+rrrrrrrrrrrrrrrrr+ddddddddddddddddd+
		 *                            new
		 *  PREV @ idx          LEFT              RIGHT
		 *                      inserted at idx + 1
		 */
		old = PREV;

		/* LEFT is the new middle */
		LEFT = *new;

		/* RIGHT is the new right */
		RIGHT.br_state = PREV.br_state;
		RIGHT.br_startoff = new_enकरोff;
		RIGHT.br_blockcount =
			PREV.br_startoff + PREV.br_blockcount - new_enकरोff;
		RIGHT.br_startblock =
			nullstartblock(xfs_bmap_worst_indlen(bma->ip,
					RIGHT.br_blockcount));

		/* truncate PREV */
		PREV.br_blockcount = new->br_startoff - PREV.br_startoff;
		PREV.br_startblock =
			nullstartblock(xfs_bmap_worst_indlen(bma->ip,
					PREV.br_blockcount));
		xfs_iext_update_extent(bma->ip, state, &bma->icur, &PREV);

		xfs_iext_next(अगरp, &bma->icur);
		xfs_iext_insert(bma->ip, &bma->icur, &RIGHT, state);
		xfs_iext_insert(bma->ip, &bma->icur, &LEFT, state);
		अगरp->अगर_nextents++;

		अगर (bma->cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(bma->cur, new, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_btree_insert(bma->cur, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
		पूर्ण

		अगर (xfs_bmap_needs_btree(bma->ip, whichविभाजन)) अणु
			error = xfs_bmap_extents_to_btree(bma->tp, bma->ip,
					&bma->cur, 1, &पंचांगp_rval, whichविभाजन);
			rval |= पंचांगp_rval;
			अगर (error)
				जाओ करोne;
		पूर्ण

		da_new = startblockval(PREV.br_startblock) +
			 startblockval(RIGHT.br_startblock);
		अवरोध;

	हाल BMAP_LEFT_FILLING | BMAP_LEFT_CONTIG | BMAP_RIGHT_CONTIG:
	हाल BMAP_RIGHT_FILLING | BMAP_LEFT_CONTIG | BMAP_RIGHT_CONTIG:
	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_CONTIG:
	हाल BMAP_RIGHT_FILLING | BMAP_LEFT_CONTIG:
	हाल BMAP_LEFT_CONTIG | BMAP_RIGHT_CONTIG:
	हाल BMAP_LEFT_CONTIG:
	हाल BMAP_RIGHT_CONTIG:
		/*
		 * These हालs are all impossible.
		 */
		ASSERT(0);
	पूर्ण

	/* add reverse mapping unless caller opted out */
	अगर (!(bma->flags & XFS_BMAPI_NORMAP))
		xfs_rmap_map_extent(bma->tp, bma->ip, whichविभाजन, new);

	/* convert to a btree अगर necessary */
	अगर (xfs_bmap_needs_btree(bma->ip, whichविभाजन)) अणु
		पूर्णांक	पंचांगp_logflags;	/* partial log flag वापस val */

		ASSERT(bma->cur == शून्य);
		error = xfs_bmap_extents_to_btree(bma->tp, bma->ip,
				&bma->cur, da_old > 0, &पंचांगp_logflags,
				whichविभाजन);
		bma->logflags |= पंचांगp_logflags;
		अगर (error)
			जाओ करोne;
	पूर्ण

	अगर (da_new != da_old)
		xfs_mod_delalloc(mp, (पूर्णांक64_t)da_new - da_old);

	अगर (bma->cur) अणु
		da_new += bma->cur->bc_ino.allocated;
		bma->cur->bc_ino.allocated = 0;
	पूर्ण

	/* adjust क्रम changes in reserved delayed indirect blocks */
	अगर (da_new != da_old) अणु
		ASSERT(state == 0 || da_new < da_old);
		error = xfs_mod_fdblocks(mp, (पूर्णांक64_t)(da_old - da_new),
				false);
	पूर्ण

	xfs_bmap_check_leaf_extents(bma->cur, bma->ip, whichविभाजन);
करोne:
	अगर (whichविभाजन != XFS_COW_FORK)
		bma->logflags |= rval;
	वापस error;
#अघोषित	LEFT
#अघोषित	RIGHT
#अघोषित	PREV
पूर्ण

/*
 * Convert an unwritten allocation to a real allocation or vice versa.
 */
पूर्णांक					/* error */
xfs_bmap_add_extent_unwritten_real(
	काष्ठा xfs_trans	*tp,
	xfs_inode_t		*ip,	/* incore inode poपूर्णांकer */
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_iext_cursor	*icur,
	xfs_btree_cur_t		**curp,	/* अगर *curp is null, not a btree */
	xfs_bmbt_irec_t		*new,	/* new data to add to file extents */
	पूर्णांक			*logflagsp) /* inode logging flags */
अणु
	xfs_btree_cur_t		*cur;	/* btree cursor */
	पूर्णांक			error;	/* error वापस value */
	पूर्णांक			i;	/* temp state */
	काष्ठा xfs_अगरork	*अगरp;	/* inode विभाजन poपूर्णांकer */
	xfs_fileoff_t		new_enकरोff;	/* end offset of new entry */
	xfs_bmbt_irec_t		r[3];	/* neighbor extent entries */
					/* left is 0, right is 1, prev is 2 */
	पूर्णांक			rval=0;	/* वापस value (logging flags) */
	पूर्णांक			state = xfs_bmap_विभाजन_to_state(whichविभाजन);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_bmbt_irec	old;

	*logflagsp = 0;

	cur = *curp;
	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);

	ASSERT(!isnullstartblock(new->br_startblock));

	XFS_STATS_INC(mp, xs_add_exlist);

#घोषणा	LEFT		r[0]
#घोषणा	RIGHT		r[1]
#घोषणा	PREV		r[2]

	/*
	 * Set up a bunch of variables to make the tests simpler.
	 */
	error = 0;
	xfs_iext_get_extent(अगरp, icur, &PREV);
	ASSERT(new->br_state != PREV.br_state);
	new_enकरोff = new->br_startoff + new->br_blockcount;
	ASSERT(PREV.br_startoff <= new->br_startoff);
	ASSERT(PREV.br_startoff + PREV.br_blockcount >= new_enकरोff);

	/*
	 * Set flags determining what part of the previous oldext allocation
	 * extent is being replaced by a newext allocation.
	 */
	अगर (PREV.br_startoff == new->br_startoff)
		state |= BMAP_LEFT_FILLING;
	अगर (PREV.br_startoff + PREV.br_blockcount == new_enकरोff)
		state |= BMAP_RIGHT_FILLING;

	/*
	 * Check and set flags अगर this segment has a left neighbor.
	 * Don't set contiguous अगर the combined extent would be too large.
	 */
	अगर (xfs_iext_peek_prev_extent(अगरp, icur, &LEFT)) अणु
		state |= BMAP_LEFT_VALID;
		अगर (isnullstartblock(LEFT.br_startblock))
			state |= BMAP_LEFT_DELAY;
	पूर्ण

	अगर ((state & BMAP_LEFT_VALID) && !(state & BMAP_LEFT_DELAY) &&
	    LEFT.br_startoff + LEFT.br_blockcount == new->br_startoff &&
	    LEFT.br_startblock + LEFT.br_blockcount == new->br_startblock &&
	    LEFT.br_state == new->br_state &&
	    LEFT.br_blockcount + new->br_blockcount <= MAXEXTLEN)
		state |= BMAP_LEFT_CONTIG;

	/*
	 * Check and set flags अगर this segment has a right neighbor.
	 * Don't set contiguous अगर the combined extent would be too large.
	 * Also check क्रम all-three-contiguous being too large.
	 */
	अगर (xfs_iext_peek_next_extent(अगरp, icur, &RIGHT)) अणु
		state |= BMAP_RIGHT_VALID;
		अगर (isnullstartblock(RIGHT.br_startblock))
			state |= BMAP_RIGHT_DELAY;
	पूर्ण

	अगर ((state & BMAP_RIGHT_VALID) && !(state & BMAP_RIGHT_DELAY) &&
	    new_enकरोff == RIGHT.br_startoff &&
	    new->br_startblock + new->br_blockcount == RIGHT.br_startblock &&
	    new->br_state == RIGHT.br_state &&
	    new->br_blockcount + RIGHT.br_blockcount <= MAXEXTLEN &&
	    ((state & (BMAP_LEFT_CONTIG | BMAP_LEFT_FILLING |
		       BMAP_RIGHT_FILLING)) !=
		      (BMAP_LEFT_CONTIG | BMAP_LEFT_FILLING |
		       BMAP_RIGHT_FILLING) ||
	     LEFT.br_blockcount + new->br_blockcount + RIGHT.br_blockcount
			<= MAXEXTLEN))
		state |= BMAP_RIGHT_CONTIG;

	/*
	 * Switch out based on the FILLING and CONTIG state bits.
	 */
	चयन (state & (BMAP_LEFT_FILLING | BMAP_LEFT_CONTIG |
			 BMAP_RIGHT_FILLING | BMAP_RIGHT_CONTIG)) अणु
	हाल BMAP_LEFT_FILLING | BMAP_LEFT_CONTIG |
	     BMAP_RIGHT_FILLING | BMAP_RIGHT_CONTIG:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * The left and right neighbors are both contiguous with new.
		 */
		LEFT.br_blockcount += PREV.br_blockcount + RIGHT.br_blockcount;

		xfs_iext_हटाओ(ip, icur, state);
		xfs_iext_हटाओ(ip, icur, state);
		xfs_iext_prev(अगरp, icur);
		xfs_iext_update_extent(ip, state, icur, &LEFT);
		अगरp->अगर_nextents -= 2;
		अगर (cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(cur, &RIGHT, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			अगर ((error = xfs_btree_delete(cur, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			अगर ((error = xfs_btree_decrement(cur, 0, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			अगर ((error = xfs_btree_delete(cur, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			अगर ((error = xfs_btree_decrement(cur, 0, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &LEFT);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING | BMAP_LEFT_CONTIG:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * The left neighbor is contiguous, the right is not.
		 */
		LEFT.br_blockcount += PREV.br_blockcount;

		xfs_iext_हटाओ(ip, icur, state);
		xfs_iext_prev(अगरp, icur);
		xfs_iext_update_extent(ip, state, icur, &LEFT);
		अगरp->अगर_nextents--;
		अगर (cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(cur, &PREV, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			अगर ((error = xfs_btree_delete(cur, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			अगर ((error = xfs_btree_decrement(cur, 0, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &LEFT);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING | BMAP_RIGHT_CONTIG:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * The right neighbor is contiguous, the left is not.
		 */
		PREV.br_blockcount += RIGHT.br_blockcount;
		PREV.br_state = new->br_state;

		xfs_iext_next(अगरp, icur);
		xfs_iext_हटाओ(ip, icur, state);
		xfs_iext_prev(अगरp, icur);
		xfs_iext_update_extent(ip, state, icur, &PREV);
		अगरp->अगर_nextents--;

		अगर (cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(cur, &RIGHT, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			अगर ((error = xfs_btree_delete(cur, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			अगर ((error = xfs_btree_decrement(cur, 0, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &PREV);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING:
		/*
		 * Setting all of a previous oldext extent to newext.
		 * Neither the left nor right neighbors are contiguous with
		 * the new one.
		 */
		PREV.br_state = new->br_state;
		xfs_iext_update_extent(ip, state, icur, &PREV);

		अगर (cur == शून्य)
			rval = XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = 0;
			error = xfs_bmbt_lookup_eq(cur, new, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &PREV);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING | BMAP_LEFT_CONTIG:
		/*
		 * Setting the first part of a previous oldext extent to newext.
		 * The left neighbor is contiguous.
		 */
		LEFT.br_blockcount += new->br_blockcount;

		old = PREV;
		PREV.br_startoff += new->br_blockcount;
		PREV.br_startblock += new->br_blockcount;
		PREV.br_blockcount -= new->br_blockcount;

		xfs_iext_update_extent(ip, state, icur, &PREV);
		xfs_iext_prev(अगरp, icur);
		xfs_iext_update_extent(ip, state, icur, &LEFT);

		अगर (cur == शून्य)
			rval = XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = 0;
			error = xfs_bmbt_lookup_eq(cur, &old, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &PREV);
			अगर (error)
				जाओ करोne;
			error = xfs_btree_decrement(cur, 0, &i);
			अगर (error)
				जाओ करोne;
			error = xfs_bmbt_update(cur, &LEFT);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING:
		/*
		 * Setting the first part of a previous oldext extent to newext.
		 * The left neighbor is not contiguous.
		 */
		old = PREV;
		PREV.br_startoff += new->br_blockcount;
		PREV.br_startblock += new->br_blockcount;
		PREV.br_blockcount -= new->br_blockcount;

		xfs_iext_update_extent(ip, state, icur, &PREV);
		xfs_iext_insert(ip, icur, new, state);
		अगरp->अगर_nextents++;

		अगर (cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(cur, &old, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &PREV);
			अगर (error)
				जाओ करोne;
			cur->bc_rec.b = *new;
			अगर ((error = xfs_btree_insert(cur, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BMAP_RIGHT_FILLING | BMAP_RIGHT_CONTIG:
		/*
		 * Setting the last part of a previous oldext extent to newext.
		 * The right neighbor is contiguous with the new allocation.
		 */
		old = PREV;
		PREV.br_blockcount -= new->br_blockcount;

		RIGHT.br_startoff = new->br_startoff;
		RIGHT.br_startblock = new->br_startblock;
		RIGHT.br_blockcount += new->br_blockcount;

		xfs_iext_update_extent(ip, state, icur, &PREV);
		xfs_iext_next(अगरp, icur);
		xfs_iext_update_extent(ip, state, icur, &RIGHT);

		अगर (cur == शून्य)
			rval = XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = 0;
			error = xfs_bmbt_lookup_eq(cur, &old, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &PREV);
			अगर (error)
				जाओ करोne;
			error = xfs_btree_increment(cur, 0, &i);
			अगर (error)
				जाओ करोne;
			error = xfs_bmbt_update(cur, &RIGHT);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_RIGHT_FILLING:
		/*
		 * Setting the last part of a previous oldext extent to newext.
		 * The right neighbor is not contiguous.
		 */
		old = PREV;
		PREV.br_blockcount -= new->br_blockcount;

		xfs_iext_update_extent(ip, state, icur, &PREV);
		xfs_iext_next(अगरp, icur);
		xfs_iext_insert(ip, icur, new, state);
		अगरp->अगर_nextents++;

		अगर (cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(cur, &old, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &PREV);
			अगर (error)
				जाओ करोne;
			error = xfs_bmbt_lookup_eq(cur, new, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			अगर ((error = xfs_btree_insert(cur, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 0:
		/*
		 * Setting the middle part of a previous oldext extent to
		 * newext.  Contiguity is impossible here.
		 * One extent becomes three extents.
		 */
		old = PREV;
		PREV.br_blockcount = new->br_startoff - PREV.br_startoff;

		r[0] = *new;
		r[1].br_startoff = new_enकरोff;
		r[1].br_blockcount =
			old.br_startoff + old.br_blockcount - new_enकरोff;
		r[1].br_startblock = new->br_startblock + new->br_blockcount;
		r[1].br_state = PREV.br_state;

		xfs_iext_update_extent(ip, state, icur, &PREV);
		xfs_iext_next(अगरp, icur);
		xfs_iext_insert(ip, icur, &r[1], state);
		xfs_iext_insert(ip, icur, &r[0], state);
		अगरp->अगर_nextents += 2;

		अगर (cur == शून्य)
			rval = XFS_ILOG_CORE | XFS_ILOG_DEXT;
		अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(cur, &old, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			/* new right extent - oldext */
			error = xfs_bmbt_update(cur, &r[1]);
			अगर (error)
				जाओ करोne;
			/* new left extent - oldext */
			cur->bc_rec.b = PREV;
			अगर ((error = xfs_btree_insert(cur, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			/*
			 * Reset the cursor to the position of the new extent
			 * we are about to insert as we can't trust it after
			 * the previous insert.
			 */
			error = xfs_bmbt_lookup_eq(cur, new, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			/* new middle extent - newext */
			अगर ((error = xfs_btree_insert(cur, &i)))
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_FILLING | BMAP_LEFT_CONTIG | BMAP_RIGHT_CONTIG:
	हाल BMAP_RIGHT_FILLING | BMAP_LEFT_CONTIG | BMAP_RIGHT_CONTIG:
	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_CONTIG:
	हाल BMAP_RIGHT_FILLING | BMAP_LEFT_CONTIG:
	हाल BMAP_LEFT_CONTIG | BMAP_RIGHT_CONTIG:
	हाल BMAP_LEFT_CONTIG:
	हाल BMAP_RIGHT_CONTIG:
		/*
		 * These हालs are all impossible.
		 */
		ASSERT(0);
	पूर्ण

	/* update reverse mappings */
	xfs_rmap_convert_extent(mp, tp, ip, whichविभाजन, new);

	/* convert to a btree अगर necessary */
	अगर (xfs_bmap_needs_btree(ip, whichविभाजन)) अणु
		पूर्णांक	पंचांगp_logflags;	/* partial log flag वापस val */

		ASSERT(cur == शून्य);
		error = xfs_bmap_extents_to_btree(tp, ip, &cur, 0,
				&पंचांगp_logflags, whichविभाजन);
		*logflagsp |= पंचांगp_logflags;
		अगर (error)
			जाओ करोne;
	पूर्ण

	/* clear out the allocated field, करोne with it now in any हाल. */
	अगर (cur) अणु
		cur->bc_ino.allocated = 0;
		*curp = cur;
	पूर्ण

	xfs_bmap_check_leaf_extents(*curp, ip, whichविभाजन);
करोne:
	*logflagsp |= rval;
	वापस error;
#अघोषित	LEFT
#अघोषित	RIGHT
#अघोषित	PREV
पूर्ण

/*
 * Convert a hole to a delayed allocation.
 */
STATIC व्योम
xfs_bmap_add_extent_hole_delay(
	xfs_inode_t		*ip,	/* incore inode poपूर्णांकer */
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_iext_cursor	*icur,
	xfs_bmbt_irec_t		*new)	/* new data to add to file extents */
अणु
	काष्ठा xfs_अगरork	*अगरp;	/* inode विभाजन poपूर्णांकer */
	xfs_bmbt_irec_t		left;	/* left neighbor extent entry */
	xfs_filblks_t		newlen=0;	/* new indirect size */
	xfs_filblks_t		oldlen=0;	/* old indirect size */
	xfs_bmbt_irec_t		right;	/* right neighbor extent entry */
	पूर्णांक			state = xfs_bmap_विभाजन_to_state(whichविभाजन);
	xfs_filblks_t		temp;	 /* temp क्रम indirect calculations */

	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	ASSERT(isnullstartblock(new->br_startblock));

	/*
	 * Check and set flags अगर this segment has a left neighbor
	 */
	अगर (xfs_iext_peek_prev_extent(अगरp, icur, &left)) अणु
		state |= BMAP_LEFT_VALID;
		अगर (isnullstartblock(left.br_startblock))
			state |= BMAP_LEFT_DELAY;
	पूर्ण

	/*
	 * Check and set flags अगर the current (right) segment exists.
	 * If it करोesn't exist, we're converting the hole at end-of-file.
	 */
	अगर (xfs_iext_get_extent(अगरp, icur, &right)) अणु
		state |= BMAP_RIGHT_VALID;
		अगर (isnullstartblock(right.br_startblock))
			state |= BMAP_RIGHT_DELAY;
	पूर्ण

	/*
	 * Set contiguity flags on the left and right neighbors.
	 * Don't let extents get too large, even अगर the pieces are contiguous.
	 */
	अगर ((state & BMAP_LEFT_VALID) && (state & BMAP_LEFT_DELAY) &&
	    left.br_startoff + left.br_blockcount == new->br_startoff &&
	    left.br_blockcount + new->br_blockcount <= MAXEXTLEN)
		state |= BMAP_LEFT_CONTIG;

	अगर ((state & BMAP_RIGHT_VALID) && (state & BMAP_RIGHT_DELAY) &&
	    new->br_startoff + new->br_blockcount == right.br_startoff &&
	    new->br_blockcount + right.br_blockcount <= MAXEXTLEN &&
	    (!(state & BMAP_LEFT_CONTIG) ||
	     (left.br_blockcount + new->br_blockcount +
	      right.br_blockcount <= MAXEXTLEN)))
		state |= BMAP_RIGHT_CONTIG;

	/*
	 * Switch out based on the contiguity flags.
	 */
	चयन (state & (BMAP_LEFT_CONTIG | BMAP_RIGHT_CONTIG)) अणु
	हाल BMAP_LEFT_CONTIG | BMAP_RIGHT_CONTIG:
		/*
		 * New allocation is contiguous with delayed allocations
		 * on the left and on the right.
		 * Merge all three पूर्णांकo a single extent record.
		 */
		temp = left.br_blockcount + new->br_blockcount +
			right.br_blockcount;

		oldlen = startblockval(left.br_startblock) +
			startblockval(new->br_startblock) +
			startblockval(right.br_startblock);
		newlen = XFS_FILBLKS_MIN(xfs_bmap_worst_indlen(ip, temp),
					 oldlen);
		left.br_startblock = nullstartblock(newlen);
		left.br_blockcount = temp;

		xfs_iext_हटाओ(ip, icur, state);
		xfs_iext_prev(अगरp, icur);
		xfs_iext_update_extent(ip, state, icur, &left);
		अवरोध;

	हाल BMAP_LEFT_CONTIG:
		/*
		 * New allocation is contiguous with a delayed allocation
		 * on the left.
		 * Merge the new allocation with the left neighbor.
		 */
		temp = left.br_blockcount + new->br_blockcount;

		oldlen = startblockval(left.br_startblock) +
			startblockval(new->br_startblock);
		newlen = XFS_FILBLKS_MIN(xfs_bmap_worst_indlen(ip, temp),
					 oldlen);
		left.br_blockcount = temp;
		left.br_startblock = nullstartblock(newlen);

		xfs_iext_prev(अगरp, icur);
		xfs_iext_update_extent(ip, state, icur, &left);
		अवरोध;

	हाल BMAP_RIGHT_CONTIG:
		/*
		 * New allocation is contiguous with a delayed allocation
		 * on the right.
		 * Merge the new allocation with the right neighbor.
		 */
		temp = new->br_blockcount + right.br_blockcount;
		oldlen = startblockval(new->br_startblock) +
			startblockval(right.br_startblock);
		newlen = XFS_FILBLKS_MIN(xfs_bmap_worst_indlen(ip, temp),
					 oldlen);
		right.br_startoff = new->br_startoff;
		right.br_startblock = nullstartblock(newlen);
		right.br_blockcount = temp;
		xfs_iext_update_extent(ip, state, icur, &right);
		अवरोध;

	हाल 0:
		/*
		 * New allocation is not contiguous with another
		 * delayed allocation.
		 * Insert a new entry.
		 */
		oldlen = newlen = 0;
		xfs_iext_insert(ip, icur, new, state);
		अवरोध;
	पूर्ण
	अगर (oldlen != newlen) अणु
		ASSERT(oldlen > newlen);
		xfs_mod_fdblocks(ip->i_mount, (पूर्णांक64_t)(oldlen - newlen),
				 false);
		/*
		 * Nothing to करो क्रम disk quota accounting here.
		 */
		xfs_mod_delalloc(ip->i_mount, (पूर्णांक64_t)newlen - oldlen);
	पूर्ण
पूर्ण

/*
 * Convert a hole to a real allocation.
 */
STATIC पूर्णांक				/* error */
xfs_bmap_add_extent_hole_real(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_iext_cursor	*icur,
	काष्ठा xfs_btree_cur	**curp,
	काष्ठा xfs_bmbt_irec	*new,
	पूर्णांक			*logflagsp,
	पूर्णांक			flags)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_btree_cur	*cur = *curp;
	पूर्णांक			error;	/* error वापस value */
	पूर्णांक			i;	/* temp state */
	xfs_bmbt_irec_t		left;	/* left neighbor extent entry */
	xfs_bmbt_irec_t		right;	/* right neighbor extent entry */
	पूर्णांक			rval=0;	/* वापस value (logging flags) */
	पूर्णांक			state = xfs_bmap_विभाजन_to_state(whichविभाजन);
	काष्ठा xfs_bmbt_irec	old;

	ASSERT(!isnullstartblock(new->br_startblock));
	ASSERT(!cur || !(cur->bc_ino.flags & XFS_BTCUR_BMBT_WASDEL));

	XFS_STATS_INC(mp, xs_add_exlist);

	/*
	 * Check and set flags अगर this segment has a left neighbor.
	 */
	अगर (xfs_iext_peek_prev_extent(अगरp, icur, &left)) अणु
		state |= BMAP_LEFT_VALID;
		अगर (isnullstartblock(left.br_startblock))
			state |= BMAP_LEFT_DELAY;
	पूर्ण

	/*
	 * Check and set flags अगर this segment has a current value.
	 * Not true अगर we're inserting पूर्णांकo the "hole" at eof.
	 */
	अगर (xfs_iext_get_extent(अगरp, icur, &right)) अणु
		state |= BMAP_RIGHT_VALID;
		अगर (isnullstartblock(right.br_startblock))
			state |= BMAP_RIGHT_DELAY;
	पूर्ण

	/*
	 * We're inserting a real allocation between "left" and "right".
	 * Set the contiguity flags.  Don't let extents get too large.
	 */
	अगर ((state & BMAP_LEFT_VALID) && !(state & BMAP_LEFT_DELAY) &&
	    left.br_startoff + left.br_blockcount == new->br_startoff &&
	    left.br_startblock + left.br_blockcount == new->br_startblock &&
	    left.br_state == new->br_state &&
	    left.br_blockcount + new->br_blockcount <= MAXEXTLEN)
		state |= BMAP_LEFT_CONTIG;

	अगर ((state & BMAP_RIGHT_VALID) && !(state & BMAP_RIGHT_DELAY) &&
	    new->br_startoff + new->br_blockcount == right.br_startoff &&
	    new->br_startblock + new->br_blockcount == right.br_startblock &&
	    new->br_state == right.br_state &&
	    new->br_blockcount + right.br_blockcount <= MAXEXTLEN &&
	    (!(state & BMAP_LEFT_CONTIG) ||
	     left.br_blockcount + new->br_blockcount +
	     right.br_blockcount <= MAXEXTLEN))
		state |= BMAP_RIGHT_CONTIG;

	error = 0;
	/*
	 * Select which हाल we're in here, and implement it.
	 */
	चयन (state & (BMAP_LEFT_CONTIG | BMAP_RIGHT_CONTIG)) अणु
	हाल BMAP_LEFT_CONTIG | BMAP_RIGHT_CONTIG:
		/*
		 * New allocation is contiguous with real allocations on the
		 * left and on the right.
		 * Merge all three पूर्णांकo a single extent record.
		 */
		left.br_blockcount += new->br_blockcount + right.br_blockcount;

		xfs_iext_हटाओ(ip, icur, state);
		xfs_iext_prev(अगरp, icur);
		xfs_iext_update_extent(ip, state, icur, &left);
		अगरp->अगर_nextents--;

		अगर (cur == शून्य) अणु
			rval = XFS_ILOG_CORE | xfs_ilog_fext(whichविभाजन);
		पूर्ण अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(cur, &right, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_btree_delete(cur, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_btree_decrement(cur, 0, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &left);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_LEFT_CONTIG:
		/*
		 * New allocation is contiguous with a real allocation
		 * on the left.
		 * Merge the new allocation with the left neighbor.
		 */
		old = left;
		left.br_blockcount += new->br_blockcount;

		xfs_iext_prev(अगरp, icur);
		xfs_iext_update_extent(ip, state, icur, &left);

		अगर (cur == शून्य) अणु
			rval = xfs_ilog_fext(whichविभाजन);
		पूर्ण अन्यथा अणु
			rval = 0;
			error = xfs_bmbt_lookup_eq(cur, &old, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &left);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल BMAP_RIGHT_CONTIG:
		/*
		 * New allocation is contiguous with a real allocation
		 * on the right.
		 * Merge the new allocation with the right neighbor.
		 */
		old = right;

		right.br_startoff = new->br_startoff;
		right.br_startblock = new->br_startblock;
		right.br_blockcount += new->br_blockcount;
		xfs_iext_update_extent(ip, state, icur, &right);

		अगर (cur == शून्य) अणु
			rval = xfs_ilog_fext(whichविभाजन);
		पूर्ण अन्यथा अणु
			rval = 0;
			error = xfs_bmbt_lookup_eq(cur, &old, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_bmbt_update(cur, &right);
			अगर (error)
				जाओ करोne;
		पूर्ण
		अवरोध;

	हाल 0:
		/*
		 * New allocation is not contiguous with another
		 * real allocation.
		 * Insert a new entry.
		 */
		xfs_iext_insert(ip, icur, new, state);
		अगरp->अगर_nextents++;

		अगर (cur == शून्य) अणु
			rval = XFS_ILOG_CORE | xfs_ilog_fext(whichविभाजन);
		पूर्ण अन्यथा अणु
			rval = XFS_ILOG_CORE;
			error = xfs_bmbt_lookup_eq(cur, new, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
			error = xfs_btree_insert(cur, &i);
			अगर (error)
				जाओ करोne;
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	/* add reverse mapping unless caller opted out */
	अगर (!(flags & XFS_BMAPI_NORMAP))
		xfs_rmap_map_extent(tp, ip, whichविभाजन, new);

	/* convert to a btree अगर necessary */
	अगर (xfs_bmap_needs_btree(ip, whichविभाजन)) अणु
		पूर्णांक	पंचांगp_logflags;	/* partial log flag वापस val */

		ASSERT(cur == शून्य);
		error = xfs_bmap_extents_to_btree(tp, ip, curp, 0,
				&पंचांगp_logflags, whichविभाजन);
		*logflagsp |= पंचांगp_logflags;
		cur = *curp;
		अगर (error)
			जाओ करोne;
	पूर्ण

	/* clear out the allocated field, करोne with it now in any हाल. */
	अगर (cur)
		cur->bc_ino.allocated = 0;

	xfs_bmap_check_leaf_extents(cur, ip, whichविभाजन);
करोne:
	*logflagsp |= rval;
	वापस error;
पूर्ण

/*
 * Functions used in the extent पढ़ो, allocate and हटाओ paths
 */

/*
 * Adjust the size of the new extent based on i_extsize and rt extsize.
 */
पूर्णांक
xfs_bmap_extsize_align(
	xfs_mount_t	*mp,
	xfs_bmbt_irec_t	*gotp,		/* next extent poपूर्णांकer */
	xfs_bmbt_irec_t	*prevp,		/* previous extent poपूर्णांकer */
	xfs_extlen_t	extsz,		/* align to this extent size */
	पूर्णांक		rt,		/* is this a realसमय inode? */
	पूर्णांक		eof,		/* is extent at end-of-file? */
	पूर्णांक		delay,		/* creating delalloc extent? */
	पूर्णांक		convert,	/* overwriting unwritten extent? */
	xfs_fileoff_t	*offp,		/* in/out: aligned offset */
	xfs_extlen_t	*lenp)		/* in/out: aligned length */
अणु
	xfs_fileoff_t	orig_off;	/* original offset */
	xfs_extlen_t	orig_alen;	/* original length */
	xfs_fileoff_t	orig_end;	/* original off+len */
	xfs_fileoff_t	nexto;		/* next file offset */
	xfs_fileoff_t	prevo;		/* previous file offset */
	xfs_fileoff_t	align_off;	/* temp क्रम offset */
	xfs_extlen_t	align_alen;	/* temp क्रम length */
	xfs_extlen_t	temp;		/* temp क्रम calculations */

	अगर (convert)
		वापस 0;

	orig_off = align_off = *offp;
	orig_alen = align_alen = *lenp;
	orig_end = orig_off + orig_alen;

	/*
	 * If this request overlaps an existing extent, then करोn't
	 * attempt to perक्रमm any additional alignment.
	 */
	अगर (!delay && !eof &&
	    (orig_off >= gotp->br_startoff) &&
	    (orig_end <= gotp->br_startoff + gotp->br_blockcount)) अणु
		वापस 0;
	पूर्ण

	/*
	 * If the file offset is unaligned vs. the extent size
	 * we need to align it.  This will be possible unless
	 * the file was previously written with a kernel that didn't
	 * perक्रमm this alignment, or अगर a truncate shot us in the
	 * foot.
	 */
	भाग_u64_rem(orig_off, extsz, &temp);
	अगर (temp) अणु
		align_alen += temp;
		align_off -= temp;
	पूर्ण

	/* Same adjusपंचांगent क्रम the end of the requested area. */
	temp = (align_alen % extsz);
	अगर (temp)
		align_alen += extsz - temp;

	/*
	 * For large extent hपूर्णांक sizes, the aligned extent might be larger than
	 * MAXEXTLEN. In that हाल, reduce the size by an extsz so that it pulls
	 * the length back under MAXEXTLEN. The outer allocation loops handle
	 * लघु allocation just fine, so it is safe to करो this. We only want to
	 * करो it when we are क्रमced to, though, because it means more allocation
	 * operations are required.
	 */
	जबतक (align_alen > MAXEXTLEN)
		align_alen -= extsz;
	ASSERT(align_alen <= MAXEXTLEN);

	/*
	 * If the previous block overlaps with this proposed allocation
	 * then move the start क्रमward without adjusting the length.
	 */
	अगर (prevp->br_startoff != शून्यखाताOFF) अणु
		अगर (prevp->br_startblock == HOLESTARTBLOCK)
			prevo = prevp->br_startoff;
		अन्यथा
			prevo = prevp->br_startoff + prevp->br_blockcount;
	पूर्ण अन्यथा
		prevo = 0;
	अगर (align_off != orig_off && align_off < prevo)
		align_off = prevo;
	/*
	 * If the next block overlaps with this proposed allocation
	 * then move the start back without adjusting the length,
	 * but not beक्रमe offset 0.
	 * This may of course make the start overlap previous block,
	 * and अगर we hit the offset 0 limit then the next block
	 * can still overlap too.
	 */
	अगर (!eof && gotp->br_startoff != शून्यखाताOFF) अणु
		अगर ((delay && gotp->br_startblock == HOLESTARTBLOCK) ||
		    (!delay && gotp->br_startblock == DELAYSTARTBLOCK))
			nexto = gotp->br_startoff + gotp->br_blockcount;
		अन्यथा
			nexto = gotp->br_startoff;
	पूर्ण अन्यथा
		nexto = शून्यखाताOFF;
	अगर (!eof &&
	    align_off + align_alen != orig_end &&
	    align_off + align_alen > nexto)
		align_off = nexto > align_alen ? nexto - align_alen : 0;
	/*
	 * If we're now overlapping the next or previous extent that
	 * means we can't fit an extsz piece in this hole.  Just move
	 * the start क्रमward to the first valid spot and set
	 * the length so we hit the end.
	 */
	अगर (align_off != orig_off && align_off < prevo)
		align_off = prevo;
	अगर (align_off + align_alen != orig_end &&
	    align_off + align_alen > nexto &&
	    nexto != शून्यखाताOFF) अणु
		ASSERT(nexto > prevo);
		align_alen = nexto - align_off;
	पूर्ण

	/*
	 * If realसमय, and the result isn't a multiple of the realसमय
	 * extent size we need to हटाओ blocks until it is.
	 */
	अगर (rt && (temp = (align_alen % mp->m_sb.sb_rextsize))) अणु
		/*
		 * We're not covering the original request, or
		 * we won't be able to once we fix the length.
		 */
		अगर (orig_off < align_off ||
		    orig_end > align_off + align_alen ||
		    align_alen - temp < orig_alen)
			वापस -EINVAL;
		/*
		 * Try to fix it by moving the start up.
		 */
		अगर (align_off + temp <= orig_off) अणु
			align_alen -= temp;
			align_off += temp;
		पूर्ण
		/*
		 * Try to fix it by moving the end in.
		 */
		अन्यथा अगर (align_off + align_alen - temp >= orig_end)
			align_alen -= temp;
		/*
		 * Set the start to the minimum then trim the length.
		 */
		अन्यथा अणु
			align_alen -= orig_off - align_off;
			align_off = orig_off;
			align_alen -= align_alen % mp->m_sb.sb_rextsize;
		पूर्ण
		/*
		 * Result करोesn't cover the request, fail it.
		 */
		अगर (orig_off < align_off || orig_end > align_off + align_alen)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		ASSERT(orig_off >= align_off);
		/* see MAXEXTLEN handling above */
		ASSERT(orig_end <= align_off + align_alen ||
		       align_alen + extsz > MAXEXTLEN);
	पूर्ण

#अगर_घोषित DEBUG
	अगर (!eof && gotp->br_startoff != शून्यखाताOFF)
		ASSERT(align_off + align_alen <= gotp->br_startoff);
	अगर (prevp->br_startoff != शून्यखाताOFF)
		ASSERT(align_off >= prevp->br_startoff + prevp->br_blockcount);
#पूर्ण_अगर

	*lenp = align_alen;
	*offp = align_off;
	वापस 0;
पूर्ण

#घोषणा XFS_ALLOC_GAP_UNITS	4

व्योम
xfs_bmap_adjacent(
	काष्ठा xfs_bदो_स्मृतिa	*ap)	/* bmap alloc argument काष्ठा */
अणु
	xfs_fsblock_t	adjust;		/* adjusपंचांगent to block numbers */
	xfs_agnumber_t	fb_agno;	/* ag number of ap->firstblock */
	xfs_mount_t	*mp;		/* mount poपूर्णांक काष्ठाure */
	पूर्णांक		nullfb;		/* true अगर ap->firstblock isn't set */
	पूर्णांक		rt;		/* true अगर inode is realसमय */

#घोषणा	ISVALID(x,y)	\
	(rt ? \
		(x) < mp->m_sb.sb_rblocks : \
		XFS_FSB_TO_AGNO(mp, x) == XFS_FSB_TO_AGNO(mp, y) && \
		XFS_FSB_TO_AGNO(mp, x) < mp->m_sb.sb_agcount && \
		XFS_FSB_TO_AGBNO(mp, x) < mp->m_sb.sb_agblocks)

	mp = ap->ip->i_mount;
	nullfb = ap->tp->t_firstblock == शून्यFSBLOCK;
	rt = XFS_IS_REALTIME_INODE(ap->ip) &&
		(ap->datatype & XFS_ALLOC_USERDATA);
	fb_agno = nullfb ? शून्यAGNUMBER : XFS_FSB_TO_AGNO(mp,
							ap->tp->t_firstblock);
	/*
	 * If allocating at eof, and there's a previous real block,
	 * try to use its last block as our starting poपूर्णांक.
	 */
	अगर (ap->eof && ap->prev.br_startoff != शून्यखाताOFF &&
	    !isnullstartblock(ap->prev.br_startblock) &&
	    ISVALID(ap->prev.br_startblock + ap->prev.br_blockcount,
		    ap->prev.br_startblock)) अणु
		ap->blkno = ap->prev.br_startblock + ap->prev.br_blockcount;
		/*
		 * Adjust क्रम the gap between prevp and us.
		 */
		adjust = ap->offset -
			(ap->prev.br_startoff + ap->prev.br_blockcount);
		अगर (adjust &&
		    ISVALID(ap->blkno + adjust, ap->prev.br_startblock))
			ap->blkno += adjust;
	पूर्ण
	/*
	 * If not at eof, then compare the two neighbor blocks.
	 * Figure out whether either one gives us a good starting poपूर्णांक,
	 * and pick the better one.
	 */
	अन्यथा अगर (!ap->eof) अणु
		xfs_fsblock_t	gotbno;		/* right side block number */
		xfs_fsblock_t	gotdअगरf=0;	/* right side dअगरference */
		xfs_fsblock_t	prevbno;	/* left side block number */
		xfs_fsblock_t	prevdअगरf=0;	/* left side dअगरference */

		/*
		 * If there's a previous (left) block, select a requested
		 * start block based on it.
		 */
		अगर (ap->prev.br_startoff != शून्यखाताOFF &&
		    !isnullstartblock(ap->prev.br_startblock) &&
		    (prevbno = ap->prev.br_startblock +
			       ap->prev.br_blockcount) &&
		    ISVALID(prevbno, ap->prev.br_startblock)) अणु
			/*
			 * Calculate gap to end of previous block.
			 */
			adjust = prevdअगरf = ap->offset -
				(ap->prev.br_startoff +
				 ap->prev.br_blockcount);
			/*
			 * Figure the startblock based on the previous block's
			 * end and the gap size.
			 * Heuristic!
			 * If the gap is large relative to the piece we're
			 * allocating, or using it gives us an invalid block
			 * number, then just use the end of the previous block.
			 */
			अगर (prevdअगरf <= XFS_ALLOC_GAP_UNITS * ap->length &&
			    ISVALID(prevbno + prevdअगरf,
				    ap->prev.br_startblock))
				prevbno += adjust;
			अन्यथा
				prevdअगरf += adjust;
			/*
			 * If the firstblock क्रमbids it, can't use it,
			 * must use शेष.
			 */
			अगर (!rt && !nullfb &&
			    XFS_FSB_TO_AGNO(mp, prevbno) != fb_agno)
				prevbno = शून्यFSBLOCK;
		पूर्ण
		/*
		 * No previous block or can't follow it, just शेष.
		 */
		अन्यथा
			prevbno = शून्यFSBLOCK;
		/*
		 * If there's a following (right) block, select a requested
		 * start block based on it.
		 */
		अगर (!isnullstartblock(ap->got.br_startblock)) अणु
			/*
			 * Calculate gap to start of next block.
			 */
			adjust = gotdअगरf = ap->got.br_startoff - ap->offset;
			/*
			 * Figure the startblock based on the next block's
			 * start and the gap size.
			 */
			gotbno = ap->got.br_startblock;
			/*
			 * Heuristic!
			 * If the gap is large relative to the piece we're
			 * allocating, or using it gives us an invalid block
			 * number, then just use the start of the next block
			 * offset by our length.
			 */
			अगर (gotdअगरf <= XFS_ALLOC_GAP_UNITS * ap->length &&
			    ISVALID(gotbno - gotdअगरf, gotbno))
				gotbno -= adjust;
			अन्यथा अगर (ISVALID(gotbno - ap->length, gotbno)) अणु
				gotbno -= ap->length;
				gotdअगरf += adjust - ap->length;
			पूर्ण अन्यथा
				gotdअगरf += adjust;
			/*
			 * If the firstblock क्रमbids it, can't use it,
			 * must use शेष.
			 */
			अगर (!rt && !nullfb &&
			    XFS_FSB_TO_AGNO(mp, gotbno) != fb_agno)
				gotbno = शून्यFSBLOCK;
		पूर्ण
		/*
		 * No next block, just शेष.
		 */
		अन्यथा
			gotbno = शून्यFSBLOCK;
		/*
		 * If both valid, pick the better one, अन्यथा the only good
		 * one, अन्यथा ap->blkno is alपढ़ोy set (to 0 or the inode block).
		 */
		अगर (prevbno != शून्यFSBLOCK && gotbno != शून्यFSBLOCK)
			ap->blkno = prevdअगरf <= gotdअगरf ? prevbno : gotbno;
		अन्यथा अगर (prevbno != शून्यFSBLOCK)
			ap->blkno = prevbno;
		अन्यथा अगर (gotbno != शून्यFSBLOCK)
			ap->blkno = gotbno;
	पूर्ण
#अघोषित ISVALID
पूर्ण

अटल पूर्णांक
xfs_bmap_दीर्घest_मुक्त_extent(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		ag,
	xfs_extlen_t		*blen,
	पूर्णांक			*notinit)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_perag	*pag;
	xfs_extlen_t		दीर्घest;
	पूर्णांक			error = 0;

	pag = xfs_perag_get(mp, ag);
	अगर (!pag->pagf_init) अणु
		error = xfs_alloc_pagf_init(mp, tp, ag, XFS_ALLOC_FLAG_TRYLOCK);
		अगर (error) अणु
			/* Couldn't lock the AGF, so skip this AG. */
			अगर (error == -EAGAIN) अणु
				*notinit = 1;
				error = 0;
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण

	दीर्घest = xfs_alloc_दीर्घest_मुक्त_extent(pag,
				xfs_alloc_min_मुक्तlist(mp, pag),
				xfs_ag_resv_needed(pag, XFS_AG_RESV_NONE));
	अगर (*blen < दीर्घest)
		*blen = दीर्घest;

out:
	xfs_perag_put(pag);
	वापस error;
पूर्ण

अटल व्योम
xfs_bmap_select_minlen(
	काष्ठा xfs_bदो_स्मृतिa	*ap,
	काष्ठा xfs_alloc_arg	*args,
	xfs_extlen_t		*blen,
	पूर्णांक			notinit)
अणु
	अगर (notinit || *blen < ap->minlen) अणु
		/*
		 * Since we did a BUF_TRYLOCK above, it is possible that
		 * there is space क्रम this request.
		 */
		args->minlen = ap->minlen;
	पूर्ण अन्यथा अगर (*blen < args->maxlen) अणु
		/*
		 * If the best seen length is less than the request length,
		 * use the best as the minimum.
		 */
		args->minlen = *blen;
	पूर्ण अन्यथा अणु
		/*
		 * Otherwise we've seen an extent as big as maxlen, use that
		 * as the minimum.
		 */
		args->minlen = args->maxlen;
	पूर्ण
पूर्ण

STATIC पूर्णांक
xfs_bmap_btalloc_nullfb(
	काष्ठा xfs_bदो_स्मृतिa	*ap,
	काष्ठा xfs_alloc_arg	*args,
	xfs_extlen_t		*blen)
अणु
	काष्ठा xfs_mount	*mp = ap->ip->i_mount;
	xfs_agnumber_t		ag, startag;
	पूर्णांक			notinit = 0;
	पूर्णांक			error;

	args->type = XFS_ALLOCTYPE_START_BNO;
	args->total = ap->total;

	startag = ag = XFS_FSB_TO_AGNO(mp, args->fsbno);
	अगर (startag == शून्यAGNUMBER)
		startag = ag = 0;

	जबतक (*blen < args->maxlen) अणु
		error = xfs_bmap_दीर्घest_मुक्त_extent(args->tp, ag, blen,
						     &notinit);
		अगर (error)
			वापस error;

		अगर (++ag == mp->m_sb.sb_agcount)
			ag = 0;
		अगर (ag == startag)
			अवरोध;
	पूर्ण

	xfs_bmap_select_minlen(ap, args, blen, notinit);
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_bmap_btalloc_filestreams(
	काष्ठा xfs_bदो_स्मृतिa	*ap,
	काष्ठा xfs_alloc_arg	*args,
	xfs_extlen_t		*blen)
अणु
	काष्ठा xfs_mount	*mp = ap->ip->i_mount;
	xfs_agnumber_t		ag;
	पूर्णांक			notinit = 0;
	पूर्णांक			error;

	args->type = XFS_ALLOCTYPE_NEAR_BNO;
	args->total = ap->total;

	ag = XFS_FSB_TO_AGNO(mp, args->fsbno);
	अगर (ag == शून्यAGNUMBER)
		ag = 0;

	error = xfs_bmap_दीर्घest_मुक्त_extent(args->tp, ag, blen, &notinit);
	अगर (error)
		वापस error;

	अगर (*blen < args->maxlen) अणु
		error = xfs_filestream_new_ag(ap, &ag);
		अगर (error)
			वापस error;

		error = xfs_bmap_दीर्घest_मुक्त_extent(args->tp, ag, blen,
						     &notinit);
		अगर (error)
			वापस error;

	पूर्ण

	xfs_bmap_select_minlen(ap, args, blen, notinit);

	/*
	 * Set the failure fallback हाल to look in the selected AG as stream
	 * may have moved.
	 */
	ap->blkno = args->fsbno = XFS_AGB_TO_FSB(mp, ag, 0);
	वापस 0;
पूर्ण

/* Update all inode and quota accounting क्रम the allocation we just did. */
अटल व्योम
xfs_bmap_btalloc_accounting(
	काष्ठा xfs_bदो_स्मृतिa	*ap,
	काष्ठा xfs_alloc_arg	*args)
अणु
	अगर (ap->flags & XFS_BMAPI_COWFORK) अणु
		/*
		 * COW विभाजन blocks are in-core only and thus are treated as
		 * in-core quota reservation (like delalloc blocks) even when
		 * converted to real blocks. The quota reservation is not
		 * accounted to disk until blocks are remapped to the data
		 * विभाजन. So अगर these blocks were previously delalloc, we
		 * alपढ़ोy have quota reservation and there's nothing to करो
		 * yet.
		 */
		अगर (ap->wasdel) अणु
			xfs_mod_delalloc(ap->ip->i_mount, -(पूर्णांक64_t)args->len);
			वापस;
		पूर्ण

		/*
		 * Otherwise, we've allocated blocks in a hole. The transaction
		 * has acquired in-core quota reservation क्रम this extent.
		 * Rather than account these as real blocks, however, we reduce
		 * the transaction quota reservation based on the allocation.
		 * This essentially transfers the transaction quota reservation
		 * to that of a delalloc extent.
		 */
		ap->ip->i_delayed_blks += args->len;
		xfs_trans_mod_dquot_byino(ap->tp, ap->ip, XFS_TRANS_DQ_RES_BLKS,
				-(दीर्घ)args->len);
		वापस;
	पूर्ण

	/* data/attr विभाजन only */
	ap->ip->i_nblocks += args->len;
	xfs_trans_log_inode(ap->tp, ap->ip, XFS_ILOG_CORE);
	अगर (ap->wasdel) अणु
		ap->ip->i_delayed_blks -= args->len;
		xfs_mod_delalloc(ap->ip->i_mount, -(पूर्णांक64_t)args->len);
	पूर्ण
	xfs_trans_mod_dquot_byino(ap->tp, ap->ip,
		ap->wasdel ? XFS_TRANS_DQ_DELBCOUNT : XFS_TRANS_DQ_BCOUNT,
		args->len);
पूर्ण

अटल पूर्णांक
xfs_bmap_compute_alignments(
	काष्ठा xfs_bदो_स्मृतिa	*ap,
	काष्ठा xfs_alloc_arg	*args)
अणु
	काष्ठा xfs_mount	*mp = args->mp;
	xfs_extlen_t		align = 0; /* minimum allocation alignment */
	पूर्णांक			stripe_align = 0;

	/* stripe alignment क्रम allocation is determined by mount parameters */
	अगर (mp->m_swidth && (mp->m_flags & XFS_MOUNT_SWALLOC))
		stripe_align = mp->m_swidth;
	अन्यथा अगर (mp->m_dalign)
		stripe_align = mp->m_dalign;

	अगर (ap->flags & XFS_BMAPI_COWFORK)
		align = xfs_get_cowextsz_hपूर्णांक(ap->ip);
	अन्यथा अगर (ap->datatype & XFS_ALLOC_USERDATA)
		align = xfs_get_extsz_hपूर्णांक(ap->ip);
	अगर (align) अणु
		अगर (xfs_bmap_extsize_align(mp, &ap->got, &ap->prev, align, 0,
					ap->eof, 0, ap->conv, &ap->offset,
					&ap->length))
			ASSERT(0);
		ASSERT(ap->length);
	पूर्ण

	/* apply extent size hपूर्णांकs अगर obtained earlier */
	अगर (align) अणु
		args->prod = align;
		भाग_u64_rem(ap->offset, args->prod, &args->mod);
		अगर (args->mod)
			args->mod = args->prod - args->mod;
	पूर्ण अन्यथा अगर (mp->m_sb.sb_blocksize >= PAGE_SIZE) अणु
		args->prod = 1;
		args->mod = 0;
	पूर्ण अन्यथा अणु
		args->prod = PAGE_SIZE >> mp->m_sb.sb_blocklog;
		भाग_u64_rem(ap->offset, args->prod, &args->mod);
		अगर (args->mod)
			args->mod = args->prod - args->mod;
	पूर्ण

	वापस stripe_align;
पूर्ण

अटल व्योम
xfs_bmap_process_allocated_extent(
	काष्ठा xfs_bदो_स्मृतिa	*ap,
	काष्ठा xfs_alloc_arg	*args,
	xfs_fileoff_t		orig_offset,
	xfs_extlen_t		orig_length)
अणु
	पूर्णांक			nullfb;

	nullfb = ap->tp->t_firstblock == शून्यFSBLOCK;

	/*
	 * check the allocation happened at the same or higher AG than
	 * the first block that was allocated.
	 */
	ASSERT(nullfb ||
		XFS_FSB_TO_AGNO(args->mp, ap->tp->t_firstblock) <=
		XFS_FSB_TO_AGNO(args->mp, args->fsbno));

	ap->blkno = args->fsbno;
	अगर (nullfb)
		ap->tp->t_firstblock = args->fsbno;
	ap->length = args->len;
	/*
	 * If the extent size hपूर्णांक is active, we tried to round the
	 * caller's allocation request offset करोwn to extsz and the
	 * length up to another extsz boundary.  If we found a मुक्त
	 * extent we mapped it in starting at this new offset.  If the
	 * newly mapped space isn't दीर्घ enough to cover any of the
	 * range of offsets that was originally requested, move the
	 * mapping up so that we can fill as much of the caller's
	 * original request as possible.  Free space is apparently
	 * very fragmented so we're unlikely to be able to satisfy the
	 * hपूर्णांकs anyway.
	 */
	अगर (ap->length <= orig_length)
		ap->offset = orig_offset;
	अन्यथा अगर (ap->offset + ap->length < orig_offset + orig_length)
		ap->offset = orig_offset + orig_length - ap->length;
	xfs_bmap_btalloc_accounting(ap, args);
पूर्ण

#अगर_घोषित DEBUG
अटल पूर्णांक
xfs_bmap_exact_minlen_extent_alloc(
	काष्ठा xfs_bदो_स्मृतिa	*ap)
अणु
	काष्ठा xfs_mount	*mp = ap->ip->i_mount;
	काष्ठा xfs_alloc_arg	args = अणु .tp = ap->tp, .mp = mp पूर्ण;
	xfs_fileoff_t		orig_offset;
	xfs_extlen_t		orig_length;
	पूर्णांक			error;

	ASSERT(ap->length);

	अगर (ap->minlen != 1) अणु
		ap->blkno = शून्यFSBLOCK;
		ap->length = 0;
		वापस 0;
	पूर्ण

	orig_offset = ap->offset;
	orig_length = ap->length;

	args.alloc_minlen_only = 1;

	xfs_bmap_compute_alignments(ap, &args);

	अगर (ap->tp->t_firstblock == शून्यFSBLOCK) अणु
		/*
		 * Unlike the दीर्घest extent available in an AG, we करोn't track
		 * the length of an AG's लघुest extent.
		 * XFS_ERRTAG_BMAP_ALLOC_MINLEN_EXTENT is a debug only knob and
		 * hence we can afक्रमd to start traversing from the 0th AG since
		 * we need not be concerned about a drop in perक्रमmance in
		 * "debug only" code paths.
		 */
		ap->blkno = XFS_AGB_TO_FSB(mp, 0, 0);
	पूर्ण अन्यथा अणु
		ap->blkno = ap->tp->t_firstblock;
	पूर्ण

	args.fsbno = ap->blkno;
	args.oinfo = XFS_RMAP_OINFO_SKIP_UPDATE;
	args.type = XFS_ALLOCTYPE_FIRST_AG;
	args.minlen = args.maxlen = ap->minlen;
	args.total = ap->total;

	args.alignment = 1;
	args.minalignslop = 0;

	args.minleft = ap->minleft;
	args.wasdel = ap->wasdel;
	args.resv = XFS_AG_RESV_NONE;
	args.datatype = ap->datatype;

	error = xfs_alloc_vextent(&args);
	अगर (error)
		वापस error;

	अगर (args.fsbno != शून्यFSBLOCK) अणु
		xfs_bmap_process_allocated_extent(ap, &args, orig_offset,
			orig_length);
	पूर्ण अन्यथा अणु
		ap->blkno = शून्यFSBLOCK;
		ap->length = 0;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा

#घोषणा xfs_bmap_exact_minlen_extent_alloc(bma) (-EFSCORRUPTED)

#पूर्ण_अगर

STATIC पूर्णांक
xfs_bmap_btalloc(
	काष्ठा xfs_bदो_स्मृतिa	*ap)
अणु
	काष्ठा xfs_mount	*mp = ap->ip->i_mount;
	काष्ठा xfs_alloc_arg	args = अणु .tp = ap->tp, .mp = mp पूर्ण;
	xfs_alloctype_t		atype = 0;
	xfs_agnumber_t		fb_agno;	/* ag number of ap->firstblock */
	xfs_agnumber_t		ag;
	xfs_fileoff_t		orig_offset;
	xfs_extlen_t		orig_length;
	xfs_extlen_t		blen;
	xfs_extlen_t		nexपंचांगinlen = 0;
	पूर्णांक			nullfb; /* true अगर ap->firstblock isn't set */
	पूर्णांक			isaligned;
	पूर्णांक			tryagain;
	पूर्णांक			error;
	पूर्णांक			stripe_align;

	ASSERT(ap->length);
	orig_offset = ap->offset;
	orig_length = ap->length;

	stripe_align = xfs_bmap_compute_alignments(ap, &args);

	nullfb = ap->tp->t_firstblock == शून्यFSBLOCK;
	fb_agno = nullfb ? शून्यAGNUMBER : XFS_FSB_TO_AGNO(mp,
							ap->tp->t_firstblock);
	अगर (nullfb) अणु
		अगर ((ap->datatype & XFS_ALLOC_USERDATA) &&
		    xfs_inode_is_filestream(ap->ip)) अणु
			ag = xfs_filestream_lookup_ag(ap->ip);
			ag = (ag != शून्यAGNUMBER) ? ag : 0;
			ap->blkno = XFS_AGB_TO_FSB(mp, ag, 0);
		पूर्ण अन्यथा अणु
			ap->blkno = XFS_INO_TO_FSB(mp, ap->ip->i_ino);
		पूर्ण
	पूर्ण अन्यथा
		ap->blkno = ap->tp->t_firstblock;

	xfs_bmap_adjacent(ap);

	/*
	 * If allowed, use ap->blkno; otherwise must use firstblock since
	 * it's in the right allocation group.
	 */
	अगर (nullfb || XFS_FSB_TO_AGNO(mp, ap->blkno) == fb_agno)
		;
	अन्यथा
		ap->blkno = ap->tp->t_firstblock;
	/*
	 * Normal allocation, करोne through xfs_alloc_vextent.
	 */
	tryagain = isaligned = 0;
	args.fsbno = ap->blkno;
	args.oinfo = XFS_RMAP_OINFO_SKIP_UPDATE;

	/* Trim the allocation back to the maximum an AG can fit. */
	args.maxlen = min(ap->length, mp->m_ag_max_usable);
	blen = 0;
	अगर (nullfb) अणु
		/*
		 * Search क्रम an allocation group with a single extent large
		 * enough क्रम the request.  If one isn't found, then adjust
		 * the minimum allocation size to the largest space found.
		 */
		अगर ((ap->datatype & XFS_ALLOC_USERDATA) &&
		    xfs_inode_is_filestream(ap->ip))
			error = xfs_bmap_btalloc_filestreams(ap, &args, &blen);
		अन्यथा
			error = xfs_bmap_btalloc_nullfb(ap, &args, &blen);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अगर (ap->tp->t_flags & XFS_TRANS_LOWMODE) अणु
		अगर (xfs_inode_is_filestream(ap->ip))
			args.type = XFS_ALLOCTYPE_FIRST_AG;
		अन्यथा
			args.type = XFS_ALLOCTYPE_START_BNO;
		args.total = args.minlen = ap->minlen;
	पूर्ण अन्यथा अणु
		args.type = XFS_ALLOCTYPE_NEAR_BNO;
		args.total = ap->total;
		args.minlen = ap->minlen;
	पूर्ण

	/*
	 * If we are not low on available data blocks, and the underlying
	 * logical volume manager is a stripe, and the file offset is zero then
	 * try to allocate data blocks on stripe unit boundary. NOTE: ap->aeof
	 * is only set अगर the allocation length is >= the stripe unit and the
	 * allocation offset is at the end of file.
	 */
	अगर (!(ap->tp->t_flags & XFS_TRANS_LOWMODE) && ap->aeof) अणु
		अगर (!ap->offset) अणु
			args.alignment = stripe_align;
			atype = args.type;
			isaligned = 1;
			/*
			 * Adjust minlen to try and preserve alignment अगर we
			 * can't guarantee an aligned maxlen extent.
			 */
			अगर (blen > args.alignment &&
			    blen <= args.maxlen + args.alignment)
				args.minlen = blen - args.alignment;
			args.minalignslop = 0;
		पूर्ण अन्यथा अणु
			/*
			 * First try an exact bno allocation.
			 * If it fails then करो a near or start bno
			 * allocation with alignment turned on.
			 */
			atype = args.type;
			tryagain = 1;
			args.type = XFS_ALLOCTYPE_THIS_BNO;
			args.alignment = 1;
			/*
			 * Compute the minlen+alignment क्रम the
			 * next हाल.  Set slop so that the value
			 * of minlen+alignment+slop करोesn't go up
			 * between the calls.
			 */
			अगर (blen > stripe_align && blen <= args.maxlen)
				nexपंचांगinlen = blen - stripe_align;
			अन्यथा
				nexपंचांगinlen = args.minlen;
			अगर (nexपंचांगinlen + stripe_align > args.minlen + 1)
				args.minalignslop =
					nexपंचांगinlen + stripe_align -
					args.minlen - 1;
			अन्यथा
				args.minalignslop = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		args.alignment = 1;
		args.minalignslop = 0;
	पूर्ण
	args.minleft = ap->minleft;
	args.wasdel = ap->wasdel;
	args.resv = XFS_AG_RESV_NONE;
	args.datatype = ap->datatype;

	error = xfs_alloc_vextent(&args);
	अगर (error)
		वापस error;

	अगर (tryagain && args.fsbno == शून्यFSBLOCK) अणु
		/*
		 * Exact allocation failed. Now try with alignment
		 * turned on.
		 */
		args.type = atype;
		args.fsbno = ap->blkno;
		args.alignment = stripe_align;
		args.minlen = nexपंचांगinlen;
		args.minalignslop = 0;
		isaligned = 1;
		अगर ((error = xfs_alloc_vextent(&args)))
			वापस error;
	पूर्ण
	अगर (isaligned && args.fsbno == शून्यFSBLOCK) अणु
		/*
		 * allocation failed, so turn off alignment and
		 * try again.
		 */
		args.type = atype;
		args.fsbno = ap->blkno;
		args.alignment = 0;
		अगर ((error = xfs_alloc_vextent(&args)))
			वापस error;
	पूर्ण
	अगर (args.fsbno == शून्यFSBLOCK && nullfb &&
	    args.minlen > ap->minlen) अणु
		args.minlen = ap->minlen;
		args.type = XFS_ALLOCTYPE_START_BNO;
		args.fsbno = ap->blkno;
		अगर ((error = xfs_alloc_vextent(&args)))
			वापस error;
	पूर्ण
	अगर (args.fsbno == शून्यFSBLOCK && nullfb) अणु
		args.fsbno = 0;
		args.type = XFS_ALLOCTYPE_FIRST_AG;
		args.total = ap->minlen;
		अगर ((error = xfs_alloc_vextent(&args)))
			वापस error;
		ap->tp->t_flags |= XFS_TRANS_LOWMODE;
	पूर्ण

	अगर (args.fsbno != शून्यFSBLOCK) अणु
		xfs_bmap_process_allocated_extent(ap, &args, orig_offset,
			orig_length);
	पूर्ण अन्यथा अणु
		ap->blkno = शून्यFSBLOCK;
		ap->length = 0;
	पूर्ण
	वापस 0;
पूर्ण

/* Trim extent to fit a logical block range. */
व्योम
xfs_trim_extent(
	काष्ठा xfs_bmbt_irec	*irec,
	xfs_fileoff_t		bno,
	xfs_filblks_t		len)
अणु
	xfs_fileoff_t		distance;
	xfs_fileoff_t		end = bno + len;

	अगर (irec->br_startoff + irec->br_blockcount <= bno ||
	    irec->br_startoff >= end) अणु
		irec->br_blockcount = 0;
		वापस;
	पूर्ण

	अगर (irec->br_startoff < bno) अणु
		distance = bno - irec->br_startoff;
		अगर (isnullstartblock(irec->br_startblock))
			irec->br_startblock = DELAYSTARTBLOCK;
		अगर (irec->br_startblock != DELAYSTARTBLOCK &&
		    irec->br_startblock != HOLESTARTBLOCK)
			irec->br_startblock += distance;
		irec->br_startoff += distance;
		irec->br_blockcount -= distance;
	पूर्ण

	अगर (end < irec->br_startoff + irec->br_blockcount) अणु
		distance = irec->br_startoff + irec->br_blockcount - end;
		irec->br_blockcount -= distance;
	पूर्ण
पूर्ण

/*
 * Trim the वापसed map to the required bounds
 */
STATIC व्योम
xfs_bmapi_trim_map(
	काष्ठा xfs_bmbt_irec	*mval,
	काष्ठा xfs_bmbt_irec	*got,
	xfs_fileoff_t		*bno,
	xfs_filblks_t		len,
	xfs_fileoff_t		obno,
	xfs_fileoff_t		end,
	पूर्णांक			n,
	पूर्णांक			flags)
अणु
	अगर ((flags & XFS_BMAPI_ENTIRE) ||
	    got->br_startoff + got->br_blockcount <= obno) अणु
		*mval = *got;
		अगर (isnullstartblock(got->br_startblock))
			mval->br_startblock = DELAYSTARTBLOCK;
		वापस;
	पूर्ण

	अगर (obno > *bno)
		*bno = obno;
	ASSERT((*bno >= obno) || (n == 0));
	ASSERT(*bno < end);
	mval->br_startoff = *bno;
	अगर (isnullstartblock(got->br_startblock))
		mval->br_startblock = DELAYSTARTBLOCK;
	अन्यथा
		mval->br_startblock = got->br_startblock +
					(*bno - got->br_startoff);
	/*
	 * Return the minimum of what we got and what we asked क्रम क्रम
	 * the length.  We can use the len variable here because it is
	 * modअगरied below and we could have been there beक्रमe coming
	 * here अगर the first part of the allocation didn't overlap what
	 * was asked क्रम.
	 */
	mval->br_blockcount = XFS_FILBLKS_MIN(end - *bno,
			got->br_blockcount - (*bno - got->br_startoff));
	mval->br_state = got->br_state;
	ASSERT(mval->br_blockcount <= len);
	वापस;
पूर्ण

/*
 * Update and validate the extent map to वापस
 */
STATIC व्योम
xfs_bmapi_update_map(
	काष्ठा xfs_bmbt_irec	**map,
	xfs_fileoff_t		*bno,
	xfs_filblks_t		*len,
	xfs_fileoff_t		obno,
	xfs_fileoff_t		end,
	पूर्णांक			*n,
	पूर्णांक			flags)
अणु
	xfs_bmbt_irec_t	*mval = *map;

	ASSERT((flags & XFS_BMAPI_ENTIRE) ||
	       ((mval->br_startoff + mval->br_blockcount) <= end));
	ASSERT((flags & XFS_BMAPI_ENTIRE) || (mval->br_blockcount <= *len) ||
	       (mval->br_startoff < obno));

	*bno = mval->br_startoff + mval->br_blockcount;
	*len = end - *bno;
	अगर (*n > 0 && mval->br_startoff == mval[-1].br_startoff) अणु
		/* update previous map with new inक्रमmation */
		ASSERT(mval->br_startblock == mval[-1].br_startblock);
		ASSERT(mval->br_blockcount > mval[-1].br_blockcount);
		ASSERT(mval->br_state == mval[-1].br_state);
		mval[-1].br_blockcount = mval->br_blockcount;
		mval[-1].br_state = mval->br_state;
	पूर्ण अन्यथा अगर (*n > 0 && mval->br_startblock != DELAYSTARTBLOCK &&
		   mval[-1].br_startblock != DELAYSTARTBLOCK &&
		   mval[-1].br_startblock != HOLESTARTBLOCK &&
		   mval->br_startblock == mval[-1].br_startblock +
					  mval[-1].br_blockcount &&
		   mval[-1].br_state == mval->br_state) अणु
		ASSERT(mval->br_startoff ==
		       mval[-1].br_startoff + mval[-1].br_blockcount);
		mval[-1].br_blockcount += mval->br_blockcount;
	पूर्ण अन्यथा अगर (*n > 0 &&
		   mval->br_startblock == DELAYSTARTBLOCK &&
		   mval[-1].br_startblock == DELAYSTARTBLOCK &&
		   mval->br_startoff ==
		   mval[-1].br_startoff + mval[-1].br_blockcount) अणु
		mval[-1].br_blockcount += mval->br_blockcount;
		mval[-1].br_state = mval->br_state;
	पूर्ण अन्यथा अगर (!((*n == 0) &&
		     ((mval->br_startoff + mval->br_blockcount) <=
		      obno))) अणु
		mval++;
		(*n)++;
	पूर्ण
	*map = mval;
पूर्ण

/*
 * Map file blocks to fileप्रणाली blocks without allocation.
 */
पूर्णांक
xfs_bmapi_पढ़ो(
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		bno,
	xfs_filblks_t		len,
	काष्ठा xfs_bmbt_irec	*mval,
	पूर्णांक			*nmap,
	पूर्णांक			flags)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			whichविभाजन = xfs_bmapi_whichविभाजन(flags);
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_bmbt_irec	got;
	xfs_fileoff_t		obno;
	xfs_fileoff_t		end;
	काष्ठा xfs_iext_cursor	icur;
	पूर्णांक			error;
	bool			eof = false;
	पूर्णांक			n = 0;

	ASSERT(*nmap >= 1);
	ASSERT(!(flags & ~(XFS_BMAPI_ATTRFORK | XFS_BMAPI_ENTIRE)));
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_SHARED|XFS_ILOCK_EXCL));

	अगर (WARN_ON_ONCE(!अगरp))
		वापस -EFSCORRUPTED;

	अगर (XFS_IS_CORRUPT(mp, !xfs_अगरork_has_extents(अगरp)) ||
	    XFS_TEST_ERROR(false, mp, XFS_ERRTAG_BMAPIFORMAT))
		वापस -EFSCORRUPTED;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	XFS_STATS_INC(mp, xs_blk_mapr);

	error = xfs_iपढ़ो_extents(शून्य, ip, whichविभाजन);
	अगर (error)
		वापस error;

	अगर (!xfs_iext_lookup_extent(ip, अगरp, bno, &icur, &got))
		eof = true;
	end = bno + len;
	obno = bno;

	जबतक (bno < end && n < *nmap) अणु
		/* Reading past eof, act as though there's a hole up to end. */
		अगर (eof)
			got.br_startoff = end;
		अगर (got.br_startoff > bno) अणु
			/* Reading in a hole.  */
			mval->br_startoff = bno;
			mval->br_startblock = HOLESTARTBLOCK;
			mval->br_blockcount =
				XFS_FILBLKS_MIN(len, got.br_startoff - bno);
			mval->br_state = XFS_EXT_NORM;
			bno += mval->br_blockcount;
			len -= mval->br_blockcount;
			mval++;
			n++;
			जारी;
		पूर्ण

		/* set up the extent map to वापस. */
		xfs_bmapi_trim_map(mval, &got, &bno, len, obno, end, n, flags);
		xfs_bmapi_update_map(&mval, &bno, &len, obno, end, &n, flags);

		/* If we're करोne, stop now. */
		अगर (bno >= end || n >= *nmap)
			अवरोध;

		/* Else go on to the next record. */
		अगर (!xfs_iext_next_extent(अगरp, &icur, &got))
			eof = true;
	पूर्ण
	*nmap = n;
	वापस 0;
पूर्ण

/*
 * Add a delayed allocation extent to an inode. Blocks are reserved from the
 * global pool and the extent inserted पूर्णांकo the inode in-core extent tree.
 *
 * On entry, got refers to the first extent beyond the offset of the extent to
 * allocate or eof is specअगरied अगर no such extent exists. On वापस, got refers
 * to the extent record that was inserted to the inode विभाजन.
 *
 * Note that the allocated extent may have been merged with contiguous extents
 * during insertion पूर्णांकo the inode विभाजन. Thus, got करोes not reflect the current
 * state of the inode विभाजन on वापस. If necessary, the caller can use lastx to
 * look up the updated record in the inode विभाजन.
 */
पूर्णांक
xfs_bmapi_reserve_delalloc(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	xfs_fileoff_t		off,
	xfs_filblks_t		len,
	xfs_filblks_t		pपुनः_स्मृति,
	काष्ठा xfs_bmbt_irec	*got,
	काष्ठा xfs_iext_cursor	*icur,
	पूर्णांक			eof)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	xfs_extlen_t		alen;
	xfs_extlen_t		indlen;
	पूर्णांक			error;
	xfs_fileoff_t		aoff = off;

	/*
	 * Cap the alloc length. Keep track of pपुनः_स्मृति so we know whether to
	 * tag the inode beक्रमe we वापस.
	 */
	alen = XFS_FILBLKS_MIN(len + pपुनः_स्मृति, MAXEXTLEN);
	अगर (!eof)
		alen = XFS_FILBLKS_MIN(alen, got->br_startoff - aoff);
	अगर (pपुनः_स्मृति && alen >= len)
		pपुनः_स्मृति = alen - len;

	/* Figure out the extent size, adjust alen */
	अगर (whichविभाजन == XFS_COW_FORK) अणु
		काष्ठा xfs_bmbt_irec	prev;
		xfs_extlen_t		extsz = xfs_get_cowextsz_hपूर्णांक(ip);

		अगर (!xfs_iext_peek_prev_extent(अगरp, icur, &prev))
			prev.br_startoff = शून्यखाताOFF;

		error = xfs_bmap_extsize_align(mp, got, &prev, extsz, 0, eof,
					       1, 0, &aoff, &alen);
		ASSERT(!error);
	पूर्ण

	/*
	 * Make a transaction-less quota reservation क्रम delayed allocation
	 * blocks.  This number माला_लो adjusted later.  We वापस अगर we haven't
	 * allocated blocks alपढ़ोy inside this loop.
	 */
	error = xfs_quota_reserve_blkres(ip, alen);
	अगर (error)
		वापस error;

	/*
	 * Split changing sb क्रम alen and indlen since they could be coming
	 * from dअगरferent places.
	 */
	indlen = (xfs_extlen_t)xfs_bmap_worst_indlen(ip, alen);
	ASSERT(indlen > 0);

	error = xfs_mod_fdblocks(mp, -((पूर्णांक64_t)alen), false);
	अगर (error)
		जाओ out_unreserve_quota;

	error = xfs_mod_fdblocks(mp, -((पूर्णांक64_t)indlen), false);
	अगर (error)
		जाओ out_unreserve_blocks;


	ip->i_delayed_blks += alen;
	xfs_mod_delalloc(ip->i_mount, alen + indlen);

	got->br_startoff = aoff;
	got->br_startblock = nullstartblock(indlen);
	got->br_blockcount = alen;
	got->br_state = XFS_EXT_NORM;

	xfs_bmap_add_extent_hole_delay(ip, whichविभाजन, icur, got);

	/*
	 * Tag the inode अगर blocks were pपुनः_स्मृतिated. Note that COW विभाजन
	 * pपुनः_स्मृतिation can occur at the start or end of the extent, even when
	 * pपुनः_स्मृति == 0, so we must also check the aligned offset and length.
	 */
	अगर (whichविभाजन == XFS_DATA_FORK && pपुनः_स्मृति)
		xfs_inode_set_eofblocks_tag(ip);
	अगर (whichविभाजन == XFS_COW_FORK && (pपुनः_स्मृति || aoff < off || alen > len))
		xfs_inode_set_cowblocks_tag(ip);

	वापस 0;

out_unreserve_blocks:
	xfs_mod_fdblocks(mp, alen, false);
out_unreserve_quota:
	अगर (XFS_IS_QUOTA_ON(mp))
		xfs_quota_unreserve_blkres(ip, alen);
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_bmap_alloc_userdata(
	काष्ठा xfs_bदो_स्मृतिa	*bma)
अणु
	काष्ठा xfs_mount	*mp = bma->ip->i_mount;
	पूर्णांक			whichविभाजन = xfs_bmapi_whichविभाजन(bma->flags);
	पूर्णांक			error;

	/*
	 * Set the data type being allocated. For the data विभाजन, the first data
	 * in the file is treated dअगरferently to all other allocations. For the
	 * attribute विभाजन, we only need to ensure the allocated range is not on
	 * the busy list.
	 */
	bma->datatype = XFS_ALLOC_NOBUSY;
	अगर (whichविभाजन == XFS_DATA_FORK) अणु
		bma->datatype |= XFS_ALLOC_USERDATA;
		अगर (bma->offset == 0)
			bma->datatype |= XFS_ALLOC_INITIAL_USER_DATA;

		अगर (mp->m_dalign && bma->length >= mp->m_dalign) अणु
			error = xfs_bmap_isaeof(bma, whichविभाजन);
			अगर (error)
				वापस error;
		पूर्ण

		अगर (XFS_IS_REALTIME_INODE(bma->ip))
			वापस xfs_bmap_rtalloc(bma);
	पूर्ण

	अगर (unlikely(XFS_TEST_ERROR(false, mp,
			XFS_ERRTAG_BMAP_ALLOC_MINLEN_EXTENT)))
		वापस xfs_bmap_exact_minlen_extent_alloc(bma);

	वापस xfs_bmap_btalloc(bma);
पूर्ण

अटल पूर्णांक
xfs_bmapi_allocate(
	काष्ठा xfs_bदो_स्मृतिa	*bma)
अणु
	काष्ठा xfs_mount	*mp = bma->ip->i_mount;
	पूर्णांक			whichविभाजन = xfs_bmapi_whichविभाजन(bma->flags);
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(bma->ip, whichविभाजन);
	पूर्णांक			पंचांगp_logflags = 0;
	पूर्णांक			error;

	ASSERT(bma->length > 0);

	/*
	 * For the wasdelay हाल, we could also just allocate the stuff asked
	 * क्रम in this bmap call but that wouldn't be as good.
	 */
	अगर (bma->wasdel) अणु
		bma->length = (xfs_extlen_t)bma->got.br_blockcount;
		bma->offset = bma->got.br_startoff;
		अगर (!xfs_iext_peek_prev_extent(अगरp, &bma->icur, &bma->prev))
			bma->prev.br_startoff = शून्यखाताOFF;
	पूर्ण अन्यथा अणु
		bma->length = XFS_FILBLKS_MIN(bma->length, MAXEXTLEN);
		अगर (!bma->eof)
			bma->length = XFS_FILBLKS_MIN(bma->length,
					bma->got.br_startoff - bma->offset);
	पूर्ण

	अगर (bma->flags & XFS_BMAPI_CONTIG)
		bma->minlen = bma->length;
	अन्यथा
		bma->minlen = 1;

	अगर (bma->flags & XFS_BMAPI_METADATA) अणु
		अगर (unlikely(XFS_TEST_ERROR(false, mp,
				XFS_ERRTAG_BMAP_ALLOC_MINLEN_EXTENT)))
			error = xfs_bmap_exact_minlen_extent_alloc(bma);
		अन्यथा
			error = xfs_bmap_btalloc(bma);
	पूर्ण अन्यथा अणु
		error = xfs_bmap_alloc_userdata(bma);
	पूर्ण
	अगर (error || bma->blkno == शून्यFSBLOCK)
		वापस error;

	अगर (bma->flags & XFS_BMAPI_ZERO) अणु
		error = xfs_zero_extent(bma->ip, bma->blkno, bma->length);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE && !bma->cur)
		bma->cur = xfs_bmbt_init_cursor(mp, bma->tp, bma->ip, whichविभाजन);
	/*
	 * Bump the number of extents we've allocated
	 * in this call.
	 */
	bma->nallocs++;

	अगर (bma->cur)
		bma->cur->bc_ino.flags =
			bma->wasdel ? XFS_BTCUR_BMBT_WASDEL : 0;

	bma->got.br_startoff = bma->offset;
	bma->got.br_startblock = bma->blkno;
	bma->got.br_blockcount = bma->length;
	bma->got.br_state = XFS_EXT_NORM;

	अगर (bma->flags & XFS_BMAPI_PREALLOC)
		bma->got.br_state = XFS_EXT_UNWRITTEN;

	अगर (bma->wasdel)
		error = xfs_bmap_add_extent_delay_real(bma, whichविभाजन);
	अन्यथा
		error = xfs_bmap_add_extent_hole_real(bma->tp, bma->ip,
				whichविभाजन, &bma->icur, &bma->cur, &bma->got,
				&bma->logflags, bma->flags);

	bma->logflags |= पंचांगp_logflags;
	अगर (error)
		वापस error;

	/*
	 * Update our extent poपूर्णांकer, given that xfs_bmap_add_extent_delay_real
	 * or xfs_bmap_add_extent_hole_real might have merged it पूर्णांकo one of
	 * the neighbouring ones.
	 */
	xfs_iext_get_extent(अगरp, &bma->icur, &bma->got);

	ASSERT(bma->got.br_startoff <= bma->offset);
	ASSERT(bma->got.br_startoff + bma->got.br_blockcount >=
	       bma->offset + bma->length);
	ASSERT(bma->got.br_state == XFS_EXT_NORM ||
	       bma->got.br_state == XFS_EXT_UNWRITTEN);
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_bmapi_convert_unwritten(
	काष्ठा xfs_bदो_स्मृतिa	*bma,
	काष्ठा xfs_bmbt_irec	*mval,
	xfs_filblks_t		len,
	पूर्णांक			flags)
अणु
	पूर्णांक			whichविभाजन = xfs_bmapi_whichविभाजन(flags);
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(bma->ip, whichविभाजन);
	पूर्णांक			पंचांगp_logflags = 0;
	पूर्णांक			error;

	/* check अगर we need to करो unwritten->real conversion */
	अगर (mval->br_state == XFS_EXT_UNWRITTEN &&
	    (flags & XFS_BMAPI_PREALLOC))
		वापस 0;

	/* check अगर we need to करो real->unwritten conversion */
	अगर (mval->br_state == XFS_EXT_NORM &&
	    (flags & (XFS_BMAPI_PREALLOC | XFS_BMAPI_CONVERT)) !=
			(XFS_BMAPI_PREALLOC | XFS_BMAPI_CONVERT))
		वापस 0;

	/*
	 * Modअगरy (by adding) the state flag, अगर writing.
	 */
	ASSERT(mval->br_blockcount <= len);
	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE && !bma->cur) अणु
		bma->cur = xfs_bmbt_init_cursor(bma->ip->i_mount, bma->tp,
					bma->ip, whichविभाजन);
	पूर्ण
	mval->br_state = (mval->br_state == XFS_EXT_UNWRITTEN)
				? XFS_EXT_NORM : XFS_EXT_UNWRITTEN;

	/*
	 * Beक्रमe insertion पूर्णांकo the bmbt, zero the range being converted
	 * अगर required.
	 */
	अगर (flags & XFS_BMAPI_ZERO) अणु
		error = xfs_zero_extent(bma->ip, mval->br_startblock,
					mval->br_blockcount);
		अगर (error)
			वापस error;
	पूर्ण

	error = xfs_bmap_add_extent_unwritten_real(bma->tp, bma->ip, whichविभाजन,
			&bma->icur, &bma->cur, mval, &पंचांगp_logflags);
	/*
	 * Log the inode core unconditionally in the unwritten extent conversion
	 * path because the conversion might not have करोne so (e.g., अगर the
	 * extent count hasn't changed). We need to make sure the inode is dirty
	 * in the transaction क्रम the sake of fsync(), even अगर nothing has
	 * changed, because fsync() will not क्रमce the log क्रम this transaction
	 * unless it sees the inode pinned.
	 *
	 * Note: If we're only converting cow fork extents, there aren't
	 * any on-disk updates to make, so we करोn't need to log anything.
	 */
	अगर (whichविभाजन != XFS_COW_FORK)
		bma->logflags |= पंचांगp_logflags | XFS_ILOG_CORE;
	अगर (error)
		वापस error;

	/*
	 * Update our extent poपूर्णांकer, given that
	 * xfs_bmap_add_extent_unwritten_real might have merged it पूर्णांकo one
	 * of the neighbouring ones.
	 */
	xfs_iext_get_extent(अगरp, &bma->icur, &bma->got);

	/*
	 * We may have combined previously unwritten space with written space,
	 * so generate another request.
	 */
	अगर (mval->br_blockcount < len)
		वापस -EAGAIN;
	वापस 0;
पूर्ण

अटल अंतरभूत xfs_extlen_t
xfs_bmapi_minleft(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			विभाजन)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, विभाजन);

	अगर (tp && tp->t_firstblock != शून्यFSBLOCK)
		वापस 0;
	अगर (अगरp->अगर_क्रमmat != XFS_DINODE_FMT_BTREE)
		वापस 1;
	वापस be16_to_cpu(अगरp->अगर_broot->bb_level) + 1;
पूर्ण

/*
 * Log whatever the flags say, even अगर error.  Otherwise we might miss detecting
 * a हाल where the data is changed, there's an error, and it's not logged so we
 * करोn't shutdown when we should.  Don't bother logging extents/btree changes अगर
 * we converted to the other क्रमmat.
 */
अटल व्योम
xfs_bmapi_finish(
	काष्ठा xfs_bदो_स्मृतिa	*bma,
	पूर्णांक			whichविभाजन,
	पूर्णांक			error)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(bma->ip, whichविभाजन);

	अगर ((bma->logflags & xfs_ilog_fext(whichविभाजन)) &&
	    अगरp->अगर_क्रमmat != XFS_DINODE_FMT_EXTENTS)
		bma->logflags &= ~xfs_ilog_fext(whichविभाजन);
	अन्यथा अगर ((bma->logflags & xfs_ilog_fbroot(whichविभाजन)) &&
		 अगरp->अगर_क्रमmat != XFS_DINODE_FMT_BTREE)
		bma->logflags &= ~xfs_ilog_fbroot(whichविभाजन);

	अगर (bma->logflags)
		xfs_trans_log_inode(bma->tp, bma->ip, bma->logflags);
	अगर (bma->cur)
		xfs_btree_del_cursor(bma->cur, error);
पूर्ण

/*
 * Map file blocks to fileप्रणाली blocks, and allocate blocks or convert the
 * extent state अगर necessary.  Details behaviour is controlled by the flags
 * parameter.  Only allocates blocks from a single allocation group, to aव्योम
 * locking problems.
 */
पूर्णांक
xfs_bmapi_ग_लिखो(
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_inode	*ip,		/* incore inode */
	xfs_fileoff_t		bno,		/* starting file offs. mapped */
	xfs_filblks_t		len,		/* length to map in file */
	पूर्णांक			flags,		/* XFS_BMAPI_... */
	xfs_extlen_t		total,		/* total blocks needed */
	काष्ठा xfs_bmbt_irec	*mval,		/* output: map values */
	पूर्णांक			*nmap)		/* i/o: mval size/count */
अणु
	काष्ठा xfs_bदो_स्मृतिa	bma = अणु
		.tp		= tp,
		.ip		= ip,
		.total		= total,
	पूर्ण;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			whichविभाजन = xfs_bmapi_whichविभाजन(flags);
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	xfs_fileoff_t		end;		/* end of mapped file region */
	bool			eof = false;	/* after the end of extents */
	पूर्णांक			error;		/* error वापस */
	पूर्णांक			n;		/* current extent index */
	xfs_fileoff_t		obno;		/* old block number (offset) */

#अगर_घोषित DEBUG
	xfs_fileoff_t		orig_bno;	/* original block number value */
	पूर्णांक			orig_flags;	/* original flags arg value */
	xfs_filblks_t		orig_len;	/* original value of len arg */
	काष्ठा xfs_bmbt_irec	*orig_mval;	/* original value of mval */
	पूर्णांक			orig_nmap;	/* original value of *nmap */

	orig_bno = bno;
	orig_len = len;
	orig_flags = flags;
	orig_mval = mval;
	orig_nmap = *nmap;
#पूर्ण_अगर

	ASSERT(*nmap >= 1);
	ASSERT(*nmap <= XFS_BMAP_MAX_NMAP);
	ASSERT(tp != शून्य);
	ASSERT(len > 0);
	ASSERT(अगरp->अगर_क्रमmat != XFS_DINODE_FMT_LOCAL);
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT(!(flags & XFS_BMAPI_REMAP));

	/* zeroing is क्रम currently only क्रम data extents, not metadata */
	ASSERT((flags & (XFS_BMAPI_METADATA | XFS_BMAPI_ZERO)) !=
			(XFS_BMAPI_METADATA | XFS_BMAPI_ZERO));
	/*
	 * we can allocate unwritten extents or pre-zero allocated blocks,
	 * but it makes no sense to करो both at once. This would result in
	 * zeroing the unwritten extent twice, but it still being an
	 * unwritten extent....
	 */
	ASSERT((flags & (XFS_BMAPI_PREALLOC | XFS_BMAPI_ZERO)) !=
			(XFS_BMAPI_PREALLOC | XFS_BMAPI_ZERO));

	अगर (XFS_IS_CORRUPT(mp, !xfs_अगरork_has_extents(अगरp)) ||
	    XFS_TEST_ERROR(false, mp, XFS_ERRTAG_BMAPIFORMAT)) अणु
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	XFS_STATS_INC(mp, xs_blk_mapw);

	error = xfs_iपढ़ो_extents(tp, ip, whichविभाजन);
	अगर (error)
		जाओ error0;

	अगर (!xfs_iext_lookup_extent(ip, अगरp, bno, &bma.icur, &bma.got))
		eof = true;
	अगर (!xfs_iext_peek_prev_extent(अगरp, &bma.icur, &bma.prev))
		bma.prev.br_startoff = शून्यखाताOFF;
	bma.minleft = xfs_bmapi_minleft(tp, ip, whichविभाजन);

	n = 0;
	end = bno + len;
	obno = bno;
	जबतक (bno < end && n < *nmap) अणु
		bool			need_alloc = false, wasdelay = false;

		/* in hole or beyond खातापूर्ण? */
		अगर (eof || bma.got.br_startoff > bno) अणु
			/*
			 * CoW विभाजन conversions should /never/ hit खातापूर्ण or
			 * holes.  There should always be something क्रम us
			 * to work on.
			 */
			ASSERT(!((flags & XFS_BMAPI_CONVERT) &&
			         (flags & XFS_BMAPI_COWFORK)));

			need_alloc = true;
		पूर्ण अन्यथा अगर (isnullstartblock(bma.got.br_startblock)) अणु
			wasdelay = true;
		पूर्ण

		/*
		 * First, deal with the hole beक्रमe the allocated space
		 * that we found, अगर any.
		 */
		अगर (need_alloc || wasdelay) अणु
			bma.eof = eof;
			bma.conv = !!(flags & XFS_BMAPI_CONVERT);
			bma.wasdel = wasdelay;
			bma.offset = bno;
			bma.flags = flags;

			/*
			 * There's a 32/64 bit type mismatch between the
			 * allocation length request (which can be 64 bits in
			 * length) and the bma length request, which is
			 * xfs_extlen_t and thereक्रमe 32 bits. Hence we have to
			 * check क्रम 32-bit overflows and handle them here.
			 */
			अगर (len > (xfs_filblks_t)MAXEXTLEN)
				bma.length = MAXEXTLEN;
			अन्यथा
				bma.length = len;

			ASSERT(len > 0);
			ASSERT(bma.length > 0);
			error = xfs_bmapi_allocate(&bma);
			अगर (error)
				जाओ error0;
			अगर (bma.blkno == शून्यFSBLOCK)
				अवरोध;

			/*
			 * If this is a CoW allocation, record the data in
			 * the refcount btree क्रम orphan recovery.
			 */
			अगर (whichविभाजन == XFS_COW_FORK)
				xfs_refcount_alloc_cow_extent(tp, bma.blkno,
						bma.length);
		पूर्ण

		/* Deal with the allocated space we found.  */
		xfs_bmapi_trim_map(mval, &bma.got, &bno, len, obno,
							end, n, flags);

		/* Execute unwritten extent conversion अगर necessary */
		error = xfs_bmapi_convert_unwritten(&bma, mval, len, flags);
		अगर (error == -EAGAIN)
			जारी;
		अगर (error)
			जाओ error0;

		/* update the extent map to वापस */
		xfs_bmapi_update_map(&mval, &bno, &len, obno, end, &n, flags);

		/*
		 * If we're done, stop now.  Stop when we've allocated
		 * XFS_BMAP_MAX_NMAP extents no matter what.  Otherwise
		 * the transaction may get too big.
		 */
		अगर (bno >= end || n >= *nmap || bma.nallocs >= *nmap)
			अवरोध;

		/* Else go on to the next record. */
		bma.prev = bma.got;
		अगर (!xfs_iext_next_extent(अगरp, &bma.icur, &bma.got))
			eof = true;
	पूर्ण
	*nmap = n;

	error = xfs_bmap_btree_to_extents(tp, ip, bma.cur, &bma.logflags,
			whichविभाजन);
	अगर (error)
		जाओ error0;

	ASSERT(अगरp->अगर_क्रमmat != XFS_DINODE_FMT_BTREE ||
	       अगरp->अगर_nextents > XFS_IFORK_MAXEXT(ip, whichविभाजन));
	xfs_bmapi_finish(&bma, whichविभाजन, 0);
	xfs_bmap_validate_ret(orig_bno, orig_len, orig_flags, orig_mval,
		orig_nmap, *nmap);
	वापस 0;
error0:
	xfs_bmapi_finish(&bma, whichविभाजन, error);
	वापस error;
पूर्ण

/*
 * Convert an existing delalloc extent to real blocks based on file offset. This
 * attempts to allocate the entire delalloc extent and may require multiple
 * invocations to allocate the target offset अगर a large enough physical extent
 * is not available.
 */
पूर्णांक
xfs_bmapi_convert_delalloc(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	xfs_off_t		offset,
	काष्ठा iomap		*iomap,
	अचिन्हित पूर्णांक		*seq)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	काष्ठा xfs_bदो_स्मृतिa	bma = अणु शून्य पूर्ण;
	uपूर्णांक16_t		flags = 0;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;

	अगर (whichविभाजन == XFS_COW_FORK)
		flags |= IOMAP_F_SHARED;

	/*
	 * Space क्रम the extent and indirect blocks was reserved when the
	 * delalloc extent was created so there's no need to करो so here.
	 */
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ग_लिखो, 0, 0,
				XFS_TRANS_RESERVE, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);

	error = xfs_iext_count_may_overflow(ip, whichविभाजन,
			XFS_IEXT_ADD_NOSPLIT_CNT);
	अगर (error)
		जाओ out_trans_cancel;

	xfs_trans_ijoin(tp, ip, 0);

	अगर (!xfs_iext_lookup_extent(ip, अगरp, offset_fsb, &bma.icur, &bma.got) ||
	    bma.got.br_startoff > offset_fsb) अणु
		/*
		 * No extent found in the range we are trying to convert.  This
		 * should only happen क्रम the COW विभाजन, where another thपढ़ो
		 * might have moved the extent to the data विभाजन in the meanसमय.
		 */
		WARN_ON_ONCE(whichविभाजन != XFS_COW_FORK);
		error = -EAGAIN;
		जाओ out_trans_cancel;
	पूर्ण

	/*
	 * If we find a real extent here we raced with another thपढ़ो converting
	 * the extent.  Just वापस the real extent at this offset.
	 */
	अगर (!isnullstartblock(bma.got.br_startblock)) अणु
		xfs_bmbt_to_iomap(ip, iomap, &bma.got, flags);
		*seq = READ_ONCE(अगरp->अगर_seq);
		जाओ out_trans_cancel;
	पूर्ण

	bma.tp = tp;
	bma.ip = ip;
	bma.wasdel = true;
	bma.offset = bma.got.br_startoff;
	bma.length = max_t(xfs_filblks_t, bma.got.br_blockcount, MAXEXTLEN);
	bma.minleft = xfs_bmapi_minleft(tp, ip, whichविभाजन);

	/*
	 * When we're converting the delalloc reservations backing dirty pages
	 * in the page cache, we must be careful about how we create the new
	 * extents:
	 *
	 * New CoW विभाजन extents are created unwritten, turned पूर्णांकo real extents
	 * when we're about to ग_लिखो the data to disk, and mapped पूर्णांकo the data
	 * विभाजन after the ग_लिखो finishes.  End of story.
	 *
	 * New data विभाजन extents must be mapped in as unwritten and converted
	 * to real extents after the ग_लिखो succeeds to aव्योम exposing stale
	 * disk contents अगर we crash.
	 */
	bma.flags = XFS_BMAPI_PREALLOC;
	अगर (whichविभाजन == XFS_COW_FORK)
		bma.flags |= XFS_BMAPI_COWFORK;

	अगर (!xfs_iext_peek_prev_extent(अगरp, &bma.icur, &bma.prev))
		bma.prev.br_startoff = शून्यखाताOFF;

	error = xfs_bmapi_allocate(&bma);
	अगर (error)
		जाओ out_finish;

	error = -ENOSPC;
	अगर (WARN_ON_ONCE(bma.blkno == शून्यFSBLOCK))
		जाओ out_finish;
	error = -EFSCORRUPTED;
	अगर (WARN_ON_ONCE(!xfs_valid_startblock(ip, bma.got.br_startblock)))
		जाओ out_finish;

	XFS_STATS_ADD(mp, xs_xstrat_bytes, XFS_FSB_TO_B(mp, bma.length));
	XFS_STATS_INC(mp, xs_xstrat_quick);

	ASSERT(!isnullstartblock(bma.got.br_startblock));
	xfs_bmbt_to_iomap(ip, iomap, &bma.got, flags);
	*seq = READ_ONCE(अगरp->अगर_seq);

	अगर (whichविभाजन == XFS_COW_FORK)
		xfs_refcount_alloc_cow_extent(tp, bma.blkno, bma.length);

	error = xfs_bmap_btree_to_extents(tp, ip, bma.cur, &bma.logflags,
			whichविभाजन);
	अगर (error)
		जाओ out_finish;

	xfs_bmapi_finish(&bma, whichविभाजन, 0);
	error = xfs_trans_commit(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;

out_finish:
	xfs_bmapi_finish(&bma, whichविभाजन, error);
out_trans_cancel:
	xfs_trans_cancel(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

पूर्णांक
xfs_bmapi_remap(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		bno,
	xfs_filblks_t		len,
	xfs_fsblock_t		startblock,
	पूर्णांक			flags)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp;
	काष्ठा xfs_btree_cur	*cur = शून्य;
	काष्ठा xfs_bmbt_irec	got;
	काष्ठा xfs_iext_cursor	icur;
	पूर्णांक			whichविभाजन = xfs_bmapi_whichविभाजन(flags);
	पूर्णांक			logflags = 0, error;

	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	ASSERT(len > 0);
	ASSERT(len <= (xfs_filblks_t)MAXEXTLEN);
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT(!(flags & ~(XFS_BMAPI_ATTRFORK | XFS_BMAPI_PREALLOC |
			   XFS_BMAPI_NORMAP)));
	ASSERT((flags & (XFS_BMAPI_ATTRFORK | XFS_BMAPI_PREALLOC)) !=
			(XFS_BMAPI_ATTRFORK | XFS_BMAPI_PREALLOC));

	अगर (XFS_IS_CORRUPT(mp, !xfs_अगरork_has_extents(अगरp)) ||
	    XFS_TEST_ERROR(false, mp, XFS_ERRTAG_BMAPIFORMAT)) अणु
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	error = xfs_iपढ़ो_extents(tp, ip, whichविभाजन);
	अगर (error)
		वापस error;

	अगर (xfs_iext_lookup_extent(ip, अगरp, bno, &icur, &got)) अणु
		/* make sure we only reflink पूर्णांकo a hole. */
		ASSERT(got.br_startoff > bno);
		ASSERT(got.br_startoff - bno >= len);
	पूर्ण

	ip->i_nblocks += len;
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE) अणु
		cur = xfs_bmbt_init_cursor(mp, tp, ip, whichविभाजन);
		cur->bc_ino.flags = 0;
	पूर्ण

	got.br_startoff = bno;
	got.br_startblock = startblock;
	got.br_blockcount = len;
	अगर (flags & XFS_BMAPI_PREALLOC)
		got.br_state = XFS_EXT_UNWRITTEN;
	अन्यथा
		got.br_state = XFS_EXT_NORM;

	error = xfs_bmap_add_extent_hole_real(tp, ip, whichविभाजन, &icur,
			&cur, &got, &logflags, flags);
	अगर (error)
		जाओ error0;

	error = xfs_bmap_btree_to_extents(tp, ip, cur, &logflags, whichविभाजन);

error0:
	अगर (ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_EXTENTS)
		logflags &= ~XFS_ILOG_DEXT;
	अन्यथा अगर (ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_BTREE)
		logflags &= ~XFS_ILOG_DBROOT;

	अगर (logflags)
		xfs_trans_log_inode(tp, ip, logflags);
	अगर (cur)
		xfs_btree_del_cursor(cur, error);
	वापस error;
पूर्ण

/*
 * When a delalloc extent is split (e.g., due to a hole punch), the original
 * indlen reservation must be shared across the two new extents that are left
 * behind.
 *
 * Given the original reservation and the worst हाल indlen क्रम the two new
 * extents (as calculated by xfs_bmap_worst_indlen()), split the original
 * reservation fairly across the two new extents. If necessary, steal available
 * blocks from a deleted extent to make up a reservation deficiency (e.g., अगर
 * ores == 1). The number of stolen blocks is वापसed. The availability and
 * subsequent accounting of stolen blocks is the responsibility of the caller.
 */
अटल xfs_filblks_t
xfs_bmap_split_indlen(
	xfs_filblks_t			ores,		/* original res. */
	xfs_filblks_t			*indlen1,	/* ext1 worst indlen */
	xfs_filblks_t			*indlen2,	/* ext2 worst indlen */
	xfs_filblks_t			avail)		/* stealable blocks */
अणु
	xfs_filblks_t			len1 = *indlen1;
	xfs_filblks_t			len2 = *indlen2;
	xfs_filblks_t			nres = len1 + len2; /* new total res. */
	xfs_filblks_t			stolen = 0;
	xfs_filblks_t			resfactor;

	/*
	 * Steal as many blocks as we can to try and satisfy the worst हाल
	 * indlen क्रम both new extents.
	 */
	अगर (ores < nres && avail)
		stolen = XFS_FILBLKS_MIN(nres - ores, avail);
	ores += stolen;

	 /* nothing अन्यथा to करो अगर we've satisfied the new reservation */
	अगर (ores >= nres)
		वापस stolen;

	/*
	 * We can't meet the total required reservation क्रम the two extents.
	 * Calculate the percent of the overall लघुage between both extents
	 * and apply this percentage to each of the requested indlen values.
	 * This distributes the लघुage fairly and reduces the chances that one
	 * of the two extents is left with nothing when extents are repeatedly
	 * split.
	 */
	resfactor = (ores * 100);
	करो_भाग(resfactor, nres);
	len1 *= resfactor;
	करो_भाग(len1, 100);
	len2 *= resfactor;
	करो_भाग(len2, 100);
	ASSERT(len1 + len2 <= ores);
	ASSERT(len1 < *indlen1 && len2 < *indlen2);

	/*
	 * Hand out the reमुख्यder to each extent. If one of the two reservations
	 * is zero, we want to make sure that one माला_लो a block first. The loop
	 * below starts with len1, so hand len2 a block right off the bat अगर it
	 * is zero.
	 */
	ores -= (len1 + len2);
	ASSERT((*indlen1 - len1) + (*indlen2 - len2) >= ores);
	अगर (ores && !len2 && *indlen2) अणु
		len2++;
		ores--;
	पूर्ण
	जबतक (ores) अणु
		अगर (len1 < *indlen1) अणु
			len1++;
			ores--;
		पूर्ण
		अगर (!ores)
			अवरोध;
		अगर (len2 < *indlen2) अणु
			len2++;
			ores--;
		पूर्ण
	पूर्ण

	*indlen1 = len1;
	*indlen2 = len2;

	वापस stolen;
पूर्ण

पूर्णांक
xfs_bmap_del_extent_delay(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_iext_cursor	*icur,
	काष्ठा xfs_bmbt_irec	*got,
	काष्ठा xfs_bmbt_irec	*del)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_bmbt_irec	new;
	पूर्णांक64_t			da_old, da_new, da_dअगरf = 0;
	xfs_fileoff_t		del_enकरोff, got_enकरोff;
	xfs_filblks_t		got_indlen, new_indlen, stolen;
	पूर्णांक			state = xfs_bmap_विभाजन_to_state(whichविभाजन);
	पूर्णांक			error = 0;
	bool			isrt;

	XFS_STATS_INC(mp, xs_del_exlist);

	isrt = (whichविभाजन == XFS_DATA_FORK) && XFS_IS_REALTIME_INODE(ip);
	del_enकरोff = del->br_startoff + del->br_blockcount;
	got_enकरोff = got->br_startoff + got->br_blockcount;
	da_old = startblockval(got->br_startblock);
	da_new = 0;

	ASSERT(del->br_blockcount > 0);
	ASSERT(got->br_startoff <= del->br_startoff);
	ASSERT(got_enकरोff >= del_enकरोff);

	अगर (isrt) अणु
		uपूर्णांक64_t rtexts = XFS_FSB_TO_B(mp, del->br_blockcount);

		करो_भाग(rtexts, mp->m_sb.sb_rextsize);
		xfs_mod_frextents(mp, rtexts);
	पूर्ण

	/*
	 * Update the inode delalloc counter now and रुको to update the
	 * sb counters as we might have to borrow some blocks क्रम the
	 * indirect block accounting.
	 */
	ASSERT(!isrt);
	error = xfs_quota_unreserve_blkres(ip, del->br_blockcount);
	अगर (error)
		वापस error;
	ip->i_delayed_blks -= del->br_blockcount;

	अगर (got->br_startoff == del->br_startoff)
		state |= BMAP_LEFT_FILLING;
	अगर (got_enकरोff == del_enकरोff)
		state |= BMAP_RIGHT_FILLING;

	चयन (state & (BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING)) अणु
	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING:
		/*
		 * Matches the whole extent.  Delete the entry.
		 */
		xfs_iext_हटाओ(ip, icur, state);
		xfs_iext_prev(अगरp, icur);
		अवरोध;
	हाल BMAP_LEFT_FILLING:
		/*
		 * Deleting the first part of the extent.
		 */
		got->br_startoff = del_enकरोff;
		got->br_blockcount -= del->br_blockcount;
		da_new = XFS_FILBLKS_MIN(xfs_bmap_worst_indlen(ip,
				got->br_blockcount), da_old);
		got->br_startblock = nullstartblock((पूर्णांक)da_new);
		xfs_iext_update_extent(ip, state, icur, got);
		अवरोध;
	हाल BMAP_RIGHT_FILLING:
		/*
		 * Deleting the last part of the extent.
		 */
		got->br_blockcount = got->br_blockcount - del->br_blockcount;
		da_new = XFS_FILBLKS_MIN(xfs_bmap_worst_indlen(ip,
				got->br_blockcount), da_old);
		got->br_startblock = nullstartblock((पूर्णांक)da_new);
		xfs_iext_update_extent(ip, state, icur, got);
		अवरोध;
	हाल 0:
		/*
		 * Deleting the middle of the extent.
		 *
		 * Distribute the original indlen reservation across the two new
		 * extents.  Steal blocks from the deleted extent अगर necessary.
		 * Stealing blocks simply fudges the fdblocks accounting below.
		 * Warn अगर either of the new indlen reservations is zero as this
		 * can lead to delalloc problems.
		 */
		got->br_blockcount = del->br_startoff - got->br_startoff;
		got_indlen = xfs_bmap_worst_indlen(ip, got->br_blockcount);

		new.br_blockcount = got_enकरोff - del_enकरोff;
		new_indlen = xfs_bmap_worst_indlen(ip, new.br_blockcount);

		WARN_ON_ONCE(!got_indlen || !new_indlen);
		stolen = xfs_bmap_split_indlen(da_old, &got_indlen, &new_indlen,
						       del->br_blockcount);

		got->br_startblock = nullstartblock((पूर्णांक)got_indlen);

		new.br_startoff = del_enकरोff;
		new.br_state = got->br_state;
		new.br_startblock = nullstartblock((पूर्णांक)new_indlen);

		xfs_iext_update_extent(ip, state, icur, got);
		xfs_iext_next(अगरp, icur);
		xfs_iext_insert(ip, icur, &new, state);

		da_new = got_indlen + new_indlen - stolen;
		del->br_blockcount -= stolen;
		अवरोध;
	पूर्ण

	ASSERT(da_old >= da_new);
	da_dअगरf = da_old - da_new;
	अगर (!isrt)
		da_dअगरf += del->br_blockcount;
	अगर (da_dअगरf) अणु
		xfs_mod_fdblocks(mp, da_dअगरf, false);
		xfs_mod_delalloc(mp, -da_dअगरf);
	पूर्ण
	वापस error;
पूर्ण

व्योम
xfs_bmap_del_extent_cow(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_iext_cursor	*icur,
	काष्ठा xfs_bmbt_irec	*got,
	काष्ठा xfs_bmbt_irec	*del)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, XFS_COW_FORK);
	काष्ठा xfs_bmbt_irec	new;
	xfs_fileoff_t		del_enकरोff, got_enकरोff;
	पूर्णांक			state = BMAP_COWFORK;

	XFS_STATS_INC(mp, xs_del_exlist);

	del_enकरोff = del->br_startoff + del->br_blockcount;
	got_enकरोff = got->br_startoff + got->br_blockcount;

	ASSERT(del->br_blockcount > 0);
	ASSERT(got->br_startoff <= del->br_startoff);
	ASSERT(got_enकरोff >= del_enकरोff);
	ASSERT(!isnullstartblock(got->br_startblock));

	अगर (got->br_startoff == del->br_startoff)
		state |= BMAP_LEFT_FILLING;
	अगर (got_enकरोff == del_enकरोff)
		state |= BMAP_RIGHT_FILLING;

	चयन (state & (BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING)) अणु
	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING:
		/*
		 * Matches the whole extent.  Delete the entry.
		 */
		xfs_iext_हटाओ(ip, icur, state);
		xfs_iext_prev(अगरp, icur);
		अवरोध;
	हाल BMAP_LEFT_FILLING:
		/*
		 * Deleting the first part of the extent.
		 */
		got->br_startoff = del_enकरोff;
		got->br_blockcount -= del->br_blockcount;
		got->br_startblock = del->br_startblock + del->br_blockcount;
		xfs_iext_update_extent(ip, state, icur, got);
		अवरोध;
	हाल BMAP_RIGHT_FILLING:
		/*
		 * Deleting the last part of the extent.
		 */
		got->br_blockcount -= del->br_blockcount;
		xfs_iext_update_extent(ip, state, icur, got);
		अवरोध;
	हाल 0:
		/*
		 * Deleting the middle of the extent.
		 */
		got->br_blockcount = del->br_startoff - got->br_startoff;

		new.br_startoff = del_enकरोff;
		new.br_blockcount = got_enकरोff - del_enकरोff;
		new.br_state = got->br_state;
		new.br_startblock = del->br_startblock + del->br_blockcount;

		xfs_iext_update_extent(ip, state, icur, got);
		xfs_iext_next(अगरp, icur);
		xfs_iext_insert(ip, icur, &new, state);
		अवरोध;
	पूर्ण
	ip->i_delayed_blks -= del->br_blockcount;
पूर्ण

/*
 * Called by xfs_bmapi to update file extent records and the btree
 * after removing space.
 */
STATIC पूर्णांक				/* error */
xfs_bmap_del_extent_real(
	xfs_inode_t		*ip,	/* incore inode poपूर्णांकer */
	xfs_trans_t		*tp,	/* current transaction poपूर्णांकer */
	काष्ठा xfs_iext_cursor	*icur,
	xfs_btree_cur_t		*cur,	/* अगर null, not a btree */
	xfs_bmbt_irec_t		*del,	/* data to हटाओ from extents */
	पूर्णांक			*logflagsp, /* inode logging flags */
	पूर्णांक			whichविभाजन, /* data or attr विभाजन */
	पूर्णांक			bflags)	/* bmapi flags */
अणु
	xfs_fsblock_t		del_endblock=0;	/* first block past del */
	xfs_fileoff_t		del_enकरोff;	/* first offset past del */
	पूर्णांक			करो_fx;	/* मुक्त extent at end of routine */
	पूर्णांक			error;	/* error वापस value */
	पूर्णांक			flags = 0;/* inode logging flags */
	काष्ठा xfs_bmbt_irec	got;	/* current extent entry */
	xfs_fileoff_t		got_enकरोff;	/* first offset past got */
	पूर्णांक			i;	/* temp state */
	काष्ठा xfs_अगरork	*अगरp;	/* inode विभाजन poपूर्णांकer */
	xfs_mount_t		*mp;	/* mount काष्ठाure */
	xfs_filblks_t		nblks;	/* quota/sb block count */
	xfs_bmbt_irec_t		new;	/* new record to be inserted */
	/* REFERENCED */
	uपूर्णांक			qfield;	/* quota field to update */
	पूर्णांक			state = xfs_bmap_विभाजन_to_state(whichविभाजन);
	काष्ठा xfs_bmbt_irec	old;

	mp = ip->i_mount;
	XFS_STATS_INC(mp, xs_del_exlist);

	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	ASSERT(del->br_blockcount > 0);
	xfs_iext_get_extent(अगरp, icur, &got);
	ASSERT(got.br_startoff <= del->br_startoff);
	del_enकरोff = del->br_startoff + del->br_blockcount;
	got_enकरोff = got.br_startoff + got.br_blockcount;
	ASSERT(got_enकरोff >= del_enकरोff);
	ASSERT(!isnullstartblock(got.br_startblock));
	qfield = 0;
	error = 0;

	/*
	 * If it's the हाल where the directory code is running with no block
	 * reservation, and the deleted block is in the middle of its extent,
	 * and the resulting insert of an extent would cause transक्रमmation to
	 * btree क्रमmat, then reject it.  The calling code will then swap blocks
	 * around instead.  We have to करो this now, rather than रुकोing क्रम the
	 * conversion to btree क्रमmat, since the transaction will be dirty then.
	 */
	अगर (tp->t_blk_res == 0 &&
	    अगरp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS &&
	    अगरp->अगर_nextents >= XFS_IFORK_MAXEXT(ip, whichविभाजन) &&
	    del->br_startoff > got.br_startoff && del_enकरोff < got_enकरोff)
		वापस -ENOSPC;

	flags = XFS_ILOG_CORE;
	अगर (whichविभाजन == XFS_DATA_FORK && XFS_IS_REALTIME_INODE(ip)) अणु
		xfs_filblks_t	len;
		xfs_extlen_t	mod;

		len = भाग_u64_rem(del->br_blockcount, mp->m_sb.sb_rextsize,
				  &mod);
		ASSERT(mod == 0);

		अगर (!(bflags & XFS_BMAPI_REMAP)) अणु
			xfs_fsblock_t	bno;

			bno = भाग_u64_rem(del->br_startblock,
					mp->m_sb.sb_rextsize, &mod);
			ASSERT(mod == 0);

			error = xfs_rtमुक्त_extent(tp, bno, (xfs_extlen_t)len);
			अगर (error)
				जाओ करोne;
		पूर्ण

		करो_fx = 0;
		nblks = len * mp->m_sb.sb_rextsize;
		qfield = XFS_TRANS_DQ_RTBCOUNT;
	पूर्ण अन्यथा अणु
		करो_fx = 1;
		nblks = del->br_blockcount;
		qfield = XFS_TRANS_DQ_BCOUNT;
	पूर्ण

	del_endblock = del->br_startblock + del->br_blockcount;
	अगर (cur) अणु
		error = xfs_bmbt_lookup_eq(cur, &got, &i);
		अगर (error)
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (got.br_startoff == del->br_startoff)
		state |= BMAP_LEFT_FILLING;
	अगर (got_enकरोff == del_enकरोff)
		state |= BMAP_RIGHT_FILLING;

	चयन (state & (BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING)) अणु
	हाल BMAP_LEFT_FILLING | BMAP_RIGHT_FILLING:
		/*
		 * Matches the whole extent.  Delete the entry.
		 */
		xfs_iext_हटाओ(ip, icur, state);
		xfs_iext_prev(अगरp, icur);
		अगरp->अगर_nextents--;

		flags |= XFS_ILOG_CORE;
		अगर (!cur) अणु
			flags |= xfs_ilog_fext(whichविभाजन);
			अवरोध;
		पूर्ण
		अगर ((error = xfs_btree_delete(cur, &i)))
			जाओ करोne;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		अवरोध;
	हाल BMAP_LEFT_FILLING:
		/*
		 * Deleting the first part of the extent.
		 */
		got.br_startoff = del_enकरोff;
		got.br_startblock = del_endblock;
		got.br_blockcount -= del->br_blockcount;
		xfs_iext_update_extent(ip, state, icur, &got);
		अगर (!cur) अणु
			flags |= xfs_ilog_fext(whichविभाजन);
			अवरोध;
		पूर्ण
		error = xfs_bmbt_update(cur, &got);
		अगर (error)
			जाओ करोne;
		अवरोध;
	हाल BMAP_RIGHT_FILLING:
		/*
		 * Deleting the last part of the extent.
		 */
		got.br_blockcount -= del->br_blockcount;
		xfs_iext_update_extent(ip, state, icur, &got);
		अगर (!cur) अणु
			flags |= xfs_ilog_fext(whichविभाजन);
			अवरोध;
		पूर्ण
		error = xfs_bmbt_update(cur, &got);
		अगर (error)
			जाओ करोne;
		अवरोध;
	हाल 0:
		/*
		 * Deleting the middle of the extent.
		 */

		/*
		 * For directories, -ENOSPC is वापसed since a directory entry
		 * हटाओ operation must not fail due to low extent count
		 * availability. -ENOSPC will be handled by higher layers of XFS
		 * by letting the corresponding empty Data/Free blocks to linger
		 * until a future हटाओ operation. Dabtree blocks would be
		 * swapped with the last block in the leaf space and then the
		 * new last block will be unmapped.
		 *
		 * The above logic also applies to the source directory entry of
		 * a नाम operation.
		 */
		error = xfs_iext_count_may_overflow(ip, whichविभाजन, 1);
		अगर (error) अणु
			ASSERT(S_ISसूची(VFS_I(ip)->i_mode) &&
				whichविभाजन == XFS_DATA_FORK);
			error = -ENOSPC;
			जाओ करोne;
		पूर्ण

		old = got;

		got.br_blockcount = del->br_startoff - got.br_startoff;
		xfs_iext_update_extent(ip, state, icur, &got);

		new.br_startoff = del_enकरोff;
		new.br_blockcount = got_enकरोff - del_enकरोff;
		new.br_state = got.br_state;
		new.br_startblock = del_endblock;

		flags |= XFS_ILOG_CORE;
		अगर (cur) अणु
			error = xfs_bmbt_update(cur, &got);
			अगर (error)
				जाओ करोne;
			error = xfs_btree_increment(cur, 0, &i);
			अगर (error)
				जाओ करोne;
			cur->bc_rec.b = new;
			error = xfs_btree_insert(cur, &i);
			अगर (error && error != -ENOSPC)
				जाओ करोne;
			/*
			 * If get no-space back from btree insert, it tried a
			 * split, and we have a zero block reservation.  Fix up
			 * our state and वापस the error.
			 */
			अगर (error == -ENOSPC) अणु
				/*
				 * Reset the cursor, करोn't trust it after any
				 * insert operation.
				 */
				error = xfs_bmbt_lookup_eq(cur, &got, &i);
				अगर (error)
					जाओ करोne;
				अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
					error = -EFSCORRUPTED;
					जाओ करोne;
				पूर्ण
				/*
				 * Update the btree record back
				 * to the original value.
				 */
				error = xfs_bmbt_update(cur, &old);
				अगर (error)
					जाओ करोne;
				/*
				 * Reset the extent record back
				 * to the original value.
				 */
				xfs_iext_update_extent(ip, state, icur, &old);
				flags = 0;
				error = -ENOSPC;
				जाओ करोne;
			पूर्ण
			अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ करोne;
			पूर्ण
		पूर्ण अन्यथा
			flags |= xfs_ilog_fext(whichविभाजन);

		अगरp->अगर_nextents++;
		xfs_iext_next(अगरp, icur);
		xfs_iext_insert(ip, icur, &new, state);
		अवरोध;
	पूर्ण

	/* हटाओ reverse mapping */
	xfs_rmap_unmap_extent(tp, ip, whichविभाजन, del);

	/*
	 * If we need to, add to list of extents to delete.
	 */
	अगर (करो_fx && !(bflags & XFS_BMAPI_REMAP)) अणु
		अगर (xfs_is_reflink_inode(ip) && whichविभाजन == XFS_DATA_FORK) अणु
			xfs_refcount_decrease_extent(tp, del);
		पूर्ण अन्यथा अणु
			__xfs_bmap_add_मुक्त(tp, del->br_startblock,
					del->br_blockcount, शून्य,
					(bflags & XFS_BMAPI_NODISCARD) ||
					del->br_state == XFS_EXT_UNWRITTEN);
		पूर्ण
	पूर्ण

	/*
	 * Adjust inode # blocks in the file.
	 */
	अगर (nblks)
		ip->i_nblocks -= nblks;
	/*
	 * Adjust quota data.
	 */
	अगर (qfield && !(bflags & XFS_BMAPI_REMAP))
		xfs_trans_mod_dquot_byino(tp, ip, qfield, (दीर्घ)-nblks);

करोne:
	*logflagsp = flags;
	वापस error;
पूर्ण

/*
 * Unmap (हटाओ) blocks from a file.
 * If nexts is nonzero then the number of extents to हटाओ is limited to
 * that value.  If not all extents in the block range can be हटाओd then
 * *करोne is set.
 */
पूर्णांक						/* error */
__xfs_bunmapi(
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_inode	*ip,		/* incore inode */
	xfs_fileoff_t		start,		/* first file offset deleted */
	xfs_filblks_t		*rlen,		/* i/o: amount reमुख्यing */
	पूर्णांक			flags,		/* misc flags */
	xfs_extnum_t		nexts)		/* number of extents max */
अणु
	काष्ठा xfs_btree_cur	*cur;		/* bmap btree cursor */
	काष्ठा xfs_bmbt_irec	del;		/* extent being deleted */
	पूर्णांक			error;		/* error वापस value */
	xfs_extnum_t		extno;		/* extent number in list */
	काष्ठा xfs_bmbt_irec	got;		/* current extent record */
	काष्ठा xfs_अगरork	*अगरp;		/* inode विभाजन poपूर्णांकer */
	पूर्णांक			isrt;		/* मुक्तing in rt area */
	पूर्णांक			logflags;	/* transaction logging flags */
	xfs_extlen_t		mod;		/* rt extent offset */
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			पंचांगp_logflags;	/* partial logging flags */
	पूर्णांक			wasdel;		/* was a delayed alloc extent */
	पूर्णांक			whichविभाजन;	/* data or attribute विभाजन */
	xfs_fsblock_t		sum;
	xfs_filblks_t		len = *rlen;	/* length to unmap in file */
	xfs_fileoff_t		max_len;
	xfs_fileoff_t		end;
	काष्ठा xfs_iext_cursor	icur;
	bool			करोne = false;

	trace_xfs_bunmap(ip, start, len, flags, _RET_IP_);

	whichविभाजन = xfs_bmapi_whichविभाजन(flags);
	ASSERT(whichविभाजन != XFS_COW_FORK);
	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	अगर (XFS_IS_CORRUPT(mp, !xfs_अगरork_has_extents(अगरp)))
		वापस -EFSCORRUPTED;
	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT(len > 0);
	ASSERT(nexts >= 0);

	/*
	 * Guesstimate how many blocks we can unmap without running the risk of
	 * blowing out the transaction with a mix of EFIs and reflink
	 * adjusपंचांगents.
	 */
	अगर (tp && xfs_is_reflink_inode(ip) && whichविभाजन == XFS_DATA_FORK)
		max_len = min(len, xfs_refcount_max_unmap(tp->t_log_res));
	अन्यथा
		max_len = len;

	error = xfs_iपढ़ो_extents(tp, ip, whichविभाजन);
	अगर (error)
		वापस error;

	अगर (xfs_iext_count(अगरp) == 0) अणु
		*rlen = 0;
		वापस 0;
	पूर्ण
	XFS_STATS_INC(mp, xs_blk_unmap);
	isrt = (whichविभाजन == XFS_DATA_FORK) && XFS_IS_REALTIME_INODE(ip);
	end = start + len;

	अगर (!xfs_iext_lookup_extent_beक्रमe(ip, अगरp, &end, &icur, &got)) अणु
		*rlen = 0;
		वापस 0;
	पूर्ण
	end--;

	logflags = 0;
	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE) अणु
		ASSERT(अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE);
		cur = xfs_bmbt_init_cursor(mp, tp, ip, whichविभाजन);
		cur->bc_ino.flags = 0;
	पूर्ण अन्यथा
		cur = शून्य;

	अगर (isrt) अणु
		/*
		 * Synchronize by locking the biपंचांगap inode.
		 */
		xfs_ilock(mp->m_rbmip, XFS_ILOCK_EXCL|XFS_ILOCK_RTBITMAP);
		xfs_trans_ijoin(tp, mp->m_rbmip, XFS_ILOCK_EXCL);
		xfs_ilock(mp->m_rsumip, XFS_ILOCK_EXCL|XFS_ILOCK_RTSUM);
		xfs_trans_ijoin(tp, mp->m_rsumip, XFS_ILOCK_EXCL);
	पूर्ण

	extno = 0;
	जबतक (end != (xfs_fileoff_t)-1 && end >= start &&
	       (nexts == 0 || extno < nexts) && max_len > 0) अणु
		/*
		 * Is the found extent after a hole in which end lives?
		 * Just back up to the previous extent, अगर so.
		 */
		अगर (got.br_startoff > end &&
		    !xfs_iext_prev_extent(अगरp, &icur, &got)) अणु
			करोne = true;
			अवरोध;
		पूर्ण
		/*
		 * Is the last block of this extent beक्रमe the range
		 * we're supposed to delete?  If so, we're करोne.
		 */
		end = XFS_खाताOFF_MIN(end,
			got.br_startoff + got.br_blockcount - 1);
		अगर (end < start)
			अवरोध;
		/*
		 * Then deal with the (possibly delayed) allocated space
		 * we found.
		 */
		del = got;
		wasdel = isnullstartblock(del.br_startblock);

		अगर (got.br_startoff < start) अणु
			del.br_startoff = start;
			del.br_blockcount -= start - got.br_startoff;
			अगर (!wasdel)
				del.br_startblock += start - got.br_startoff;
		पूर्ण
		अगर (del.br_startoff + del.br_blockcount > end + 1)
			del.br_blockcount = end + 1 - del.br_startoff;

		/* How much can we safely unmap? */
		अगर (max_len < del.br_blockcount) अणु
			del.br_startoff += del.br_blockcount - max_len;
			अगर (!wasdel)
				del.br_startblock += del.br_blockcount - max_len;
			del.br_blockcount = max_len;
		पूर्ण

		अगर (!isrt)
			जाओ delete;

		sum = del.br_startblock + del.br_blockcount;
		भाग_u64_rem(sum, mp->m_sb.sb_rextsize, &mod);
		अगर (mod) अणु
			/*
			 * Realसमय extent not lined up at the end.
			 * The extent could have been split पूर्णांकo written
			 * and unwritten pieces, or we could just be
			 * unmapping part of it.  But we can't really
			 * get rid of part of a realसमय extent.
			 */
			अगर (del.br_state == XFS_EXT_UNWRITTEN) अणु
				/*
				 * This piece is unwritten, or we're not
				 * using unwritten extents.  Skip over it.
				 */
				ASSERT(end >= mod);
				end -= mod > del.br_blockcount ?
					del.br_blockcount : mod;
				अगर (end < got.br_startoff &&
				    !xfs_iext_prev_extent(अगरp, &icur, &got)) अणु
					करोne = true;
					अवरोध;
				पूर्ण
				जारी;
			पूर्ण
			/*
			 * It's written, turn it unwritten.
			 * This is better than zeroing it.
			 */
			ASSERT(del.br_state == XFS_EXT_NORM);
			ASSERT(tp->t_blk_res > 0);
			/*
			 * If this spans a realसमय extent boundary,
			 * chop it back to the start of the one we end at.
			 */
			अगर (del.br_blockcount > mod) अणु
				del.br_startoff += del.br_blockcount - mod;
				del.br_startblock += del.br_blockcount - mod;
				del.br_blockcount = mod;
			पूर्ण
			del.br_state = XFS_EXT_UNWRITTEN;
			error = xfs_bmap_add_extent_unwritten_real(tp, ip,
					whichविभाजन, &icur, &cur, &del,
					&logflags);
			अगर (error)
				जाओ error0;
			जाओ nodelete;
		पूर्ण
		भाग_u64_rem(del.br_startblock, mp->m_sb.sb_rextsize, &mod);
		अगर (mod) अणु
			xfs_extlen_t off = mp->m_sb.sb_rextsize - mod;

			/*
			 * Realसमय extent is lined up at the end but not
			 * at the front.  We'll get rid of full extents अगर
			 * we can.
			 */
			अगर (del.br_blockcount > off) अणु
				del.br_blockcount -= off;
				del.br_startoff += off;
				del.br_startblock += off;
			पूर्ण अन्यथा अगर (del.br_startoff == start &&
				   (del.br_state == XFS_EXT_UNWRITTEN ||
				    tp->t_blk_res == 0)) अणु
				/*
				 * Can't make it unwritten.  There isn't
				 * a full extent here so just skip it.
				 */
				ASSERT(end >= del.br_blockcount);
				end -= del.br_blockcount;
				अगर (got.br_startoff > end &&
				    !xfs_iext_prev_extent(अगरp, &icur, &got)) अणु
					करोne = true;
					अवरोध;
				पूर्ण
				जारी;
			पूर्ण अन्यथा अगर (del.br_state == XFS_EXT_UNWRITTEN) अणु
				काष्ठा xfs_bmbt_irec	prev;
				xfs_fileoff_t		unग_लिखो_start;

				/*
				 * This one is alपढ़ोy unwritten.
				 * It must have a written left neighbor.
				 * Unग_लिखो the समाप्तed part of that one and
				 * try again.
				 */
				अगर (!xfs_iext_prev_extent(अगरp, &icur, &prev))
					ASSERT(0);
				ASSERT(prev.br_state == XFS_EXT_NORM);
				ASSERT(!isnullstartblock(prev.br_startblock));
				ASSERT(del.br_startblock ==
				       prev.br_startblock + prev.br_blockcount);
				unग_लिखो_start = max3(start,
						     del.br_startoff - mod,
						     prev.br_startoff);
				mod = unग_लिखो_start - prev.br_startoff;
				prev.br_startoff = unग_लिखो_start;
				prev.br_startblock += mod;
				prev.br_blockcount -= mod;
				prev.br_state = XFS_EXT_UNWRITTEN;
				error = xfs_bmap_add_extent_unwritten_real(tp,
						ip, whichविभाजन, &icur, &cur,
						&prev, &logflags);
				अगर (error)
					जाओ error0;
				जाओ nodelete;
			पूर्ण अन्यथा अणु
				ASSERT(del.br_state == XFS_EXT_NORM);
				del.br_state = XFS_EXT_UNWRITTEN;
				error = xfs_bmap_add_extent_unwritten_real(tp,
						ip, whichविभाजन, &icur, &cur,
						&del, &logflags);
				अगर (error)
					जाओ error0;
				जाओ nodelete;
			पूर्ण
		पूर्ण

delete:
		अगर (wasdel) अणु
			error = xfs_bmap_del_extent_delay(ip, whichविभाजन, &icur,
					&got, &del);
		पूर्ण अन्यथा अणु
			error = xfs_bmap_del_extent_real(ip, tp, &icur, cur,
					&del, &पंचांगp_logflags, whichविभाजन,
					flags);
			logflags |= पंचांगp_logflags;
		पूर्ण

		अगर (error)
			जाओ error0;

		max_len -= del.br_blockcount;
		end = del.br_startoff - 1;
nodelete:
		/*
		 * If not करोne go on to the next (previous) record.
		 */
		अगर (end != (xfs_fileoff_t)-1 && end >= start) अणु
			अगर (!xfs_iext_get_extent(अगरp, &icur, &got) ||
			    (got.br_startoff > end &&
			     !xfs_iext_prev_extent(अगरp, &icur, &got))) अणु
				करोne = true;
				अवरोध;
			पूर्ण
			extno++;
		पूर्ण
	पूर्ण
	अगर (करोne || end == (xfs_fileoff_t)-1 || end < start)
		*rlen = 0;
	अन्यथा
		*rlen = end - start + 1;

	/*
	 * Convert to a btree अगर necessary.
	 */
	अगर (xfs_bmap_needs_btree(ip, whichविभाजन)) अणु
		ASSERT(cur == शून्य);
		error = xfs_bmap_extents_to_btree(tp, ip, &cur, 0,
				&पंचांगp_logflags, whichविभाजन);
		logflags |= पंचांगp_logflags;
	पूर्ण अन्यथा अणु
		error = xfs_bmap_btree_to_extents(tp, ip, cur, &logflags,
			whichविभाजन);
	पूर्ण

error0:
	/*
	 * Log everything.  Do this after conversion, there's no poपूर्णांक in
	 * logging the extent records अगर we've converted to btree क्रमmat.
	 */
	अगर ((logflags & xfs_ilog_fext(whichविभाजन)) &&
	    अगरp->अगर_क्रमmat != XFS_DINODE_FMT_EXTENTS)
		logflags &= ~xfs_ilog_fext(whichविभाजन);
	अन्यथा अगर ((logflags & xfs_ilog_fbroot(whichविभाजन)) &&
		 अगरp->अगर_क्रमmat != XFS_DINODE_FMT_BTREE)
		logflags &= ~xfs_ilog_fbroot(whichविभाजन);
	/*
	 * Log inode even in the error हाल, अगर the transaction
	 * is dirty we'll need to shut करोwn the fileप्रणाली.
	 */
	अगर (logflags)
		xfs_trans_log_inode(tp, ip, logflags);
	अगर (cur) अणु
		अगर (!error)
			cur->bc_ino.allocated = 0;
		xfs_btree_del_cursor(cur, error);
	पूर्ण
	वापस error;
पूर्ण

/* Unmap a range of a file. */
पूर्णांक
xfs_bunmapi(
	xfs_trans_t		*tp,
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		bno,
	xfs_filblks_t		len,
	पूर्णांक			flags,
	xfs_extnum_t		nexts,
	पूर्णांक			*करोne)
अणु
	पूर्णांक			error;

	error = __xfs_bunmapi(tp, ip, bno, &len, flags, nexts);
	*करोne = (len == 0);
	वापस error;
पूर्ण

/*
 * Determine whether an extent shअगरt can be accomplished by a merge with the
 * extent that precedes the target hole of the shअगरt.
 */
STATIC bool
xfs_bmse_can_merge(
	काष्ठा xfs_bmbt_irec	*left,	/* preceding extent */
	काष्ठा xfs_bmbt_irec	*got,	/* current extent to shअगरt */
	xfs_fileoff_t		shअगरt)	/* shअगरt fsb */
अणु
	xfs_fileoff_t		startoff;

	startoff = got->br_startoff - shअगरt;

	/*
	 * The extent, once shअगरted, must be adjacent in-file and on-disk with
	 * the preceding extent.
	 */
	अगर ((left->br_startoff + left->br_blockcount != startoff) ||
	    (left->br_startblock + left->br_blockcount != got->br_startblock) ||
	    (left->br_state != got->br_state) ||
	    (left->br_blockcount + got->br_blockcount > MAXEXTLEN))
		वापस false;

	वापस true;
पूर्ण

/*
 * A bmap extent shअगरt adjusts the file offset of an extent to fill a preceding
 * hole in the file. If an extent shअगरt would result in the extent being fully
 * adjacent to the extent that currently precedes the hole, we can merge with
 * the preceding extent rather than करो the shअगरt.
 *
 * This function assumes the caller has verअगरied a shअगरt-by-merge is possible
 * with the provided extents via xfs_bmse_can_merge().
 */
STATIC पूर्णांक
xfs_bmse_merge(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_inode		*ip,
	पूर्णांक				whichविभाजन,
	xfs_fileoff_t			shअगरt,		/* shअगरt fsb */
	काष्ठा xfs_iext_cursor		*icur,
	काष्ठा xfs_bmbt_irec		*got,		/* extent to shअगरt */
	काष्ठा xfs_bmbt_irec		*left,		/* preceding extent */
	काष्ठा xfs_btree_cur		*cur,
	पूर्णांक				*logflags)	/* output */
अणु
	काष्ठा xfs_अगरork		*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_bmbt_irec		new;
	xfs_filblks_t			blockcount;
	पूर्णांक				error, i;
	काष्ठा xfs_mount		*mp = ip->i_mount;

	blockcount = left->br_blockcount + got->br_blockcount;

	ASSERT(xfs_isilocked(ip, XFS_IOLOCK_EXCL));
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT(xfs_bmse_can_merge(left, got, shअगरt));

	new = *left;
	new.br_blockcount = blockcount;

	/*
	 * Update the on-disk extent count, the btree अगर necessary and log the
	 * inode.
	 */
	अगरp->अगर_nextents--;
	*logflags |= XFS_ILOG_CORE;
	अगर (!cur) अणु
		*logflags |= XFS_ILOG_DEXT;
		जाओ करोne;
	पूर्ण

	/* lookup and हटाओ the extent to merge */
	error = xfs_bmbt_lookup_eq(cur, got, &i);
	अगर (error)
		वापस error;
	अगर (XFS_IS_CORRUPT(mp, i != 1))
		वापस -EFSCORRUPTED;

	error = xfs_btree_delete(cur, &i);
	अगर (error)
		वापस error;
	अगर (XFS_IS_CORRUPT(mp, i != 1))
		वापस -EFSCORRUPTED;

	/* lookup and update size of the previous extent */
	error = xfs_bmbt_lookup_eq(cur, left, &i);
	अगर (error)
		वापस error;
	अगर (XFS_IS_CORRUPT(mp, i != 1))
		वापस -EFSCORRUPTED;

	error = xfs_bmbt_update(cur, &new);
	अगर (error)
		वापस error;

	/* change to extent क्रमmat अगर required after extent removal */
	error = xfs_bmap_btree_to_extents(tp, ip, cur, logflags, whichविभाजन);
	अगर (error)
		वापस error;

करोne:
	xfs_iext_हटाओ(ip, icur, 0);
	xfs_iext_prev(अगरp, icur);
	xfs_iext_update_extent(ip, xfs_bmap_विभाजन_to_state(whichविभाजन), icur,
			&new);

	/* update reverse mapping. rmap functions merge the rmaps क्रम us */
	xfs_rmap_unmap_extent(tp, ip, whichविभाजन, got);
	स_नकल(&new, got, माप(new));
	new.br_startoff = left->br_startoff + left->br_blockcount;
	xfs_rmap_map_extent(tp, ip, whichविभाजन, &new);
	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_bmap_shअगरt_update_extent(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_iext_cursor	*icur,
	काष्ठा xfs_bmbt_irec	*got,
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			*logflags,
	xfs_fileoff_t		startoff)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_bmbt_irec	prev = *got;
	पूर्णांक			error, i;

	*logflags |= XFS_ILOG_CORE;

	got->br_startoff = startoff;

	अगर (cur) अणु
		error = xfs_bmbt_lookup_eq(cur, &prev, &i);
		अगर (error)
			वापस error;
		अगर (XFS_IS_CORRUPT(mp, i != 1))
			वापस -EFSCORRUPTED;

		error = xfs_bmbt_update(cur, got);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		*logflags |= XFS_ILOG_DEXT;
	पूर्ण

	xfs_iext_update_extent(ip, xfs_bmap_विभाजन_to_state(whichविभाजन), icur,
			got);

	/* update reverse mapping */
	xfs_rmap_unmap_extent(tp, ip, whichविभाजन, &prev);
	xfs_rmap_map_extent(tp, ip, whichविभाजन, got);
	वापस 0;
पूर्ण

पूर्णांक
xfs_bmap_collapse_extents(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		*next_fsb,
	xfs_fileoff_t		offset_shअगरt_fsb,
	bool			*करोne)
अणु
	पूर्णांक			whichविभाजन = XFS_DATA_FORK;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_btree_cur	*cur = शून्य;
	काष्ठा xfs_bmbt_irec	got, prev;
	काष्ठा xfs_iext_cursor	icur;
	xfs_fileoff_t		new_startoff;
	पूर्णांक			error = 0;
	पूर्णांक			logflags = 0;

	अगर (XFS_IS_CORRUPT(mp, !xfs_अगरork_has_extents(अगरp)) ||
	    XFS_TEST_ERROR(false, mp, XFS_ERRTAG_BMAPIFORMAT)) अणु
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	ASSERT(xfs_isilocked(ip, XFS_IOLOCK_EXCL | XFS_ILOCK_EXCL));

	error = xfs_iपढ़ो_extents(tp, ip, whichविभाजन);
	अगर (error)
		वापस error;

	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE) अणु
		cur = xfs_bmbt_init_cursor(mp, tp, ip, whichविभाजन);
		cur->bc_ino.flags = 0;
	पूर्ण

	अगर (!xfs_iext_lookup_extent(ip, अगरp, *next_fsb, &icur, &got)) अणु
		*करोne = true;
		जाओ del_cursor;
	पूर्ण
	अगर (XFS_IS_CORRUPT(mp, isnullstartblock(got.br_startblock))) अणु
		error = -EFSCORRUPTED;
		जाओ del_cursor;
	पूर्ण

	new_startoff = got.br_startoff - offset_shअगरt_fsb;
	अगर (xfs_iext_peek_prev_extent(अगरp, &icur, &prev)) अणु
		अगर (new_startoff < prev.br_startoff + prev.br_blockcount) अणु
			error = -EINVAL;
			जाओ del_cursor;
		पूर्ण

		अगर (xfs_bmse_can_merge(&prev, &got, offset_shअगरt_fsb)) अणु
			error = xfs_bmse_merge(tp, ip, whichविभाजन,
					offset_shअगरt_fsb, &icur, &got, &prev,
					cur, &logflags);
			अगर (error)
				जाओ del_cursor;
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (got.br_startoff < offset_shअगरt_fsb) अणु
			error = -EINVAL;
			जाओ del_cursor;
		पूर्ण
	पूर्ण

	error = xfs_bmap_shअगरt_update_extent(tp, ip, whichविभाजन, &icur, &got,
			cur, &logflags, new_startoff);
	अगर (error)
		जाओ del_cursor;

करोne:
	अगर (!xfs_iext_next_extent(अगरp, &icur, &got)) अणु
		*करोne = true;
		जाओ del_cursor;
	पूर्ण

	*next_fsb = got.br_startoff;
del_cursor:
	अगर (cur)
		xfs_btree_del_cursor(cur, error);
	अगर (logflags)
		xfs_trans_log_inode(tp, ip, logflags);
	वापस error;
पूर्ण

/* Make sure we won't be right-shअगरting an extent past the maximum bound. */
पूर्णांक
xfs_bmap_can_insert_extents(
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		off,
	xfs_fileoff_t		shअगरt)
अणु
	काष्ठा xfs_bmbt_irec	got;
	पूर्णांक			is_empty;
	पूर्णांक			error = 0;

	ASSERT(xfs_isilocked(ip, XFS_IOLOCK_EXCL));

	अगर (XFS_FORCED_SHUTDOWN(ip->i_mount))
		वापस -EIO;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	error = xfs_bmap_last_extent(शून्य, ip, XFS_DATA_FORK, &got, &is_empty);
	अगर (!error && !is_empty && got.br_startoff >= off &&
	    ((got.br_startoff + shअगरt) & BMBT_STARTOFF_MASK) < got.br_startoff)
		error = -EINVAL;
	xfs_iunlock(ip, XFS_ILOCK_EXCL);

	वापस error;
पूर्ण

पूर्णांक
xfs_bmap_insert_extents(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		*next_fsb,
	xfs_fileoff_t		offset_shअगरt_fsb,
	bool			*करोne,
	xfs_fileoff_t		stop_fsb)
अणु
	पूर्णांक			whichविभाजन = XFS_DATA_FORK;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_btree_cur	*cur = शून्य;
	काष्ठा xfs_bmbt_irec	got, next;
	काष्ठा xfs_iext_cursor	icur;
	xfs_fileoff_t		new_startoff;
	पूर्णांक			error = 0;
	पूर्णांक			logflags = 0;

	अगर (XFS_IS_CORRUPT(mp, !xfs_अगरork_has_extents(अगरp)) ||
	    XFS_TEST_ERROR(false, mp, XFS_ERRTAG_BMAPIFORMAT)) अणु
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	ASSERT(xfs_isilocked(ip, XFS_IOLOCK_EXCL | XFS_ILOCK_EXCL));

	error = xfs_iपढ़ो_extents(tp, ip, whichविभाजन);
	अगर (error)
		वापस error;

	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE) अणु
		cur = xfs_bmbt_init_cursor(mp, tp, ip, whichविभाजन);
		cur->bc_ino.flags = 0;
	पूर्ण

	अगर (*next_fsb == शून्यFSBLOCK) अणु
		xfs_iext_last(अगरp, &icur);
		अगर (!xfs_iext_get_extent(अगरp, &icur, &got) ||
		    stop_fsb > got.br_startoff) अणु
			*करोne = true;
			जाओ del_cursor;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!xfs_iext_lookup_extent(ip, अगरp, *next_fsb, &icur, &got)) अणु
			*करोne = true;
			जाओ del_cursor;
		पूर्ण
	पूर्ण
	अगर (XFS_IS_CORRUPT(mp, isnullstartblock(got.br_startblock))) अणु
		error = -EFSCORRUPTED;
		जाओ del_cursor;
	पूर्ण

	अगर (XFS_IS_CORRUPT(mp, stop_fsb > got.br_startoff)) अणु
		error = -EFSCORRUPTED;
		जाओ del_cursor;
	पूर्ण

	new_startoff = got.br_startoff + offset_shअगरt_fsb;
	अगर (xfs_iext_peek_next_extent(अगरp, &icur, &next)) अणु
		अगर (new_startoff + got.br_blockcount > next.br_startoff) अणु
			error = -EINVAL;
			जाओ del_cursor;
		पूर्ण

		/*
		 * Unlike a left shअगरt (which involves a hole punch), a right
		 * shअगरt करोes not modअगरy extent neighbors in any way.  We should
		 * never find mergeable extents in this scenario.  Check anyways
		 * and warn अगर we encounter two extents that could be one.
		 */
		अगर (xfs_bmse_can_merge(&got, &next, offset_shअगरt_fsb))
			WARN_ON_ONCE(1);
	पूर्ण

	error = xfs_bmap_shअगरt_update_extent(tp, ip, whichविभाजन, &icur, &got,
			cur, &logflags, new_startoff);
	अगर (error)
		जाओ del_cursor;

	अगर (!xfs_iext_prev_extent(अगरp, &icur, &got) ||
	    stop_fsb >= got.br_startoff + got.br_blockcount) अणु
		*करोne = true;
		जाओ del_cursor;
	पूर्ण

	*next_fsb = got.br_startoff;
del_cursor:
	अगर (cur)
		xfs_btree_del_cursor(cur, error);
	अगर (logflags)
		xfs_trans_log_inode(tp, ip, logflags);
	वापस error;
पूर्ण

/*
 * Splits an extent पूर्णांकo two extents at split_fsb block such that it is the
 * first block of the current_ext. @ext is a target extent to be split.
 * @split_fsb is a block where the extents is split.  If split_fsb lies in a
 * hole or the first block of extents, just वापस 0.
 */
पूर्णांक
xfs_bmap_split_extent(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		split_fsb)
अणु
	पूर्णांक				whichविभाजन = XFS_DATA_FORK;
	काष्ठा xfs_अगरork		*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_btree_cur		*cur = शून्य;
	काष्ठा xfs_bmbt_irec		got;
	काष्ठा xfs_bmbt_irec		new; /* split extent */
	काष्ठा xfs_mount		*mp = ip->i_mount;
	xfs_fsblock_t			gotblkcnt; /* new block count क्रम got */
	काष्ठा xfs_iext_cursor		icur;
	पूर्णांक				error = 0;
	पूर्णांक				logflags = 0;
	पूर्णांक				i = 0;

	अगर (XFS_IS_CORRUPT(mp, !xfs_अगरork_has_extents(अगरp)) ||
	    XFS_TEST_ERROR(false, mp, XFS_ERRTAG_BMAPIFORMAT)) अणु
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	/* Read in all the extents */
	error = xfs_iपढ़ो_extents(tp, ip, whichविभाजन);
	अगर (error)
		वापस error;

	/*
	 * If there are not extents, or split_fsb lies in a hole we are करोne.
	 */
	अगर (!xfs_iext_lookup_extent(ip, अगरp, split_fsb, &icur, &got) ||
	    got.br_startoff >= split_fsb)
		वापस 0;

	gotblkcnt = split_fsb - got.br_startoff;
	new.br_startoff = split_fsb;
	new.br_startblock = got.br_startblock + gotblkcnt;
	new.br_blockcount = got.br_blockcount - gotblkcnt;
	new.br_state = got.br_state;

	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE) अणु
		cur = xfs_bmbt_init_cursor(mp, tp, ip, whichविभाजन);
		cur->bc_ino.flags = 0;
		error = xfs_bmbt_lookup_eq(cur, &got, &i);
		अगर (error)
			जाओ del_cursor;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ del_cursor;
		पूर्ण
	पूर्ण

	got.br_blockcount = gotblkcnt;
	xfs_iext_update_extent(ip, xfs_bmap_विभाजन_to_state(whichविभाजन), &icur,
			&got);

	logflags = XFS_ILOG_CORE;
	अगर (cur) अणु
		error = xfs_bmbt_update(cur, &got);
		अगर (error)
			जाओ del_cursor;
	पूर्ण अन्यथा
		logflags |= XFS_ILOG_DEXT;

	/* Add new extent */
	xfs_iext_next(अगरp, &icur);
	xfs_iext_insert(ip, &icur, &new, 0);
	अगरp->अगर_nextents++;

	अगर (cur) अणु
		error = xfs_bmbt_lookup_eq(cur, &new, &i);
		अगर (error)
			जाओ del_cursor;
		अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
			error = -EFSCORRUPTED;
			जाओ del_cursor;
		पूर्ण
		error = xfs_btree_insert(cur, &i);
		अगर (error)
			जाओ del_cursor;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ del_cursor;
		पूर्ण
	पूर्ण

	/*
	 * Convert to a btree अगर necessary.
	 */
	अगर (xfs_bmap_needs_btree(ip, whichविभाजन)) अणु
		पूर्णांक पंचांगp_logflags; /* partial log flag वापस val */

		ASSERT(cur == शून्य);
		error = xfs_bmap_extents_to_btree(tp, ip, &cur, 0,
				&पंचांगp_logflags, whichविभाजन);
		logflags |= पंचांगp_logflags;
	पूर्ण

del_cursor:
	अगर (cur) अणु
		cur->bc_ino.allocated = 0;
		xfs_btree_del_cursor(cur, error);
	पूर्ण

	अगर (logflags)
		xfs_trans_log_inode(tp, ip, logflags);
	वापस error;
पूर्ण

/* Deferred mapping is only क्रम real extents in the data विभाजन. */
अटल bool
xfs_bmap_is_update_needed(
	काष्ठा xfs_bmbt_irec	*bmap)
अणु
	वापस  bmap->br_startblock != HOLESTARTBLOCK &&
		bmap->br_startblock != DELAYSTARTBLOCK;
पूर्ण

/* Record a bmap पूर्णांकent. */
अटल पूर्णांक
__xfs_bmap_add(
	काष्ठा xfs_trans		*tp,
	क्रमागत xfs_bmap_पूर्णांकent_type	type,
	काष्ठा xfs_inode		*ip,
	पूर्णांक				whichविभाजन,
	काष्ठा xfs_bmbt_irec		*bmap)
अणु
	काष्ठा xfs_bmap_पूर्णांकent		*bi;

	trace_xfs_bmap_defer(tp->t_mountp,
			XFS_FSB_TO_AGNO(tp->t_mountp, bmap->br_startblock),
			type,
			XFS_FSB_TO_AGBNO(tp->t_mountp, bmap->br_startblock),
			ip->i_ino, whichविभाजन,
			bmap->br_startoff,
			bmap->br_blockcount,
			bmap->br_state);

	bi = kmem_alloc(माप(काष्ठा xfs_bmap_पूर्णांकent), KM_NOFS);
	INIT_LIST_HEAD(&bi->bi_list);
	bi->bi_type = type;
	bi->bi_owner = ip;
	bi->bi_whichविभाजन = whichविभाजन;
	bi->bi_bmap = *bmap;

	xfs_defer_add(tp, XFS_DEFER_OPS_TYPE_BMAP, &bi->bi_list);
	वापस 0;
पूर्ण

/* Map an extent पूर्णांकo a file. */
व्योम
xfs_bmap_map_extent(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_bmbt_irec	*PREV)
अणु
	अगर (!xfs_bmap_is_update_needed(PREV))
		वापस;

	__xfs_bmap_add(tp, XFS_BMAP_MAP, ip, XFS_DATA_FORK, PREV);
पूर्ण

/* Unmap an extent out of a file. */
व्योम
xfs_bmap_unmap_extent(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_bmbt_irec	*PREV)
अणु
	अगर (!xfs_bmap_is_update_needed(PREV))
		वापस;

	__xfs_bmap_add(tp, XFS_BMAP_UNMAP, ip, XFS_DATA_FORK, PREV);
पूर्ण

/*
 * Process one of the deferred bmap operations.  We pass back the
 * btree cursor to मुख्यtain our lock on the bmapbt between calls.
 */
पूर्णांक
xfs_bmap_finish_one(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_inode		*ip,
	क्रमागत xfs_bmap_पूर्णांकent_type	type,
	पूर्णांक				whichविभाजन,
	xfs_fileoff_t			startoff,
	xfs_fsblock_t			startblock,
	xfs_filblks_t			*blockcount,
	xfs_exntst_t			state)
अणु
	पूर्णांक				error = 0;

	ASSERT(tp->t_firstblock == शून्यFSBLOCK);

	trace_xfs_bmap_deferred(tp->t_mountp,
			XFS_FSB_TO_AGNO(tp->t_mountp, startblock), type,
			XFS_FSB_TO_AGBNO(tp->t_mountp, startblock),
			ip->i_ino, whichविभाजन, startoff, *blockcount, state);

	अगर (WARN_ON_ONCE(whichविभाजन != XFS_DATA_FORK))
		वापस -EFSCORRUPTED;

	अगर (XFS_TEST_ERROR(false, tp->t_mountp,
			XFS_ERRTAG_BMAP_FINISH_ONE))
		वापस -EIO;

	चयन (type) अणु
	हाल XFS_BMAP_MAP:
		error = xfs_bmapi_remap(tp, ip, startoff, *blockcount,
				startblock, 0);
		*blockcount = 0;
		अवरोध;
	हाल XFS_BMAP_UNMAP:
		error = __xfs_bunmapi(tp, ip, startoff, blockcount,
				XFS_BMAPI_REMAP, 1);
		अवरोध;
	शेष:
		ASSERT(0);
		error = -EFSCORRUPTED;
	पूर्ण

	वापस error;
पूर्ण

/* Check that an inode's extent करोes not have invalid flags or bad ranges. */
xfs_failaddr_t
xfs_bmap_validate_extent(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_bmbt_irec	*irec)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;

	अगर (!xfs_verअगरy_fileext(mp, irec->br_startoff, irec->br_blockcount))
		वापस __this_address;

	अगर (XFS_IS_REALTIME_INODE(ip) && whichविभाजन == XFS_DATA_FORK) अणु
		अगर (!xfs_verअगरy_rtext(mp, irec->br_startblock,
					  irec->br_blockcount))
			वापस __this_address;
	पूर्ण अन्यथा अणु
		अगर (!xfs_verअगरy_fsbext(mp, irec->br_startblock,
					   irec->br_blockcount))
			वापस __this_address;
	पूर्ण
	अगर (irec->br_state != XFS_EXT_NORM && whichविभाजन != XFS_DATA_FORK)
		वापस __this_address;
	वापस शून्य;
पूर्ण
