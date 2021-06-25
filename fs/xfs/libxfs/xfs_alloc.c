<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_alloc_btree.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_extent_busy.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_log.h"
#समावेश "xfs_ag_resv.h"
#समावेश "xfs_bmap.h"

बाह्य kmem_zone_t	*xfs_bmap_मुक्त_item_zone;

काष्ठा workqueue_काष्ठा *xfs_alloc_wq;

#घोषणा XFS_ABSDIFF(a,b)	(((a) <= (b)) ? ((b) - (a)) : ((a) - (b)))

#घोषणा	XFSA_FIXUP_BNO_OK	1
#घोषणा	XFSA_FIXUP_CNT_OK	2

STATIC पूर्णांक xfs_alloc_ag_vextent_exact(xfs_alloc_arg_t *);
STATIC पूर्णांक xfs_alloc_ag_vextent_near(xfs_alloc_arg_t *);
STATIC पूर्णांक xfs_alloc_ag_vextent_size(xfs_alloc_arg_t *);

/*
 * Size of the AGFL.  For CRC-enabled filesystes we steal a couple of slots in
 * the beginning of the block क्रम a proper header with the location inक्रमmation
 * and CRC.
 */
अचिन्हित पूर्णांक
xfs_agfl_size(
	काष्ठा xfs_mount	*mp)
अणु
	अचिन्हित पूर्णांक		size = mp->m_sb.sb_sectsize;

	अगर (xfs_sb_version_hascrc(&mp->m_sb))
		size -= माप(काष्ठा xfs_agfl);

	वापस size / माप(xfs_agblock_t);
पूर्ण

अचिन्हित पूर्णांक
xfs_refc_block(
	काष्ठा xfs_mount	*mp)
अणु
	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस XFS_RMAP_BLOCK(mp) + 1;
	अगर (xfs_sb_version_hasfinobt(&mp->m_sb))
		वापस XFS_FIBT_BLOCK(mp) + 1;
	वापस XFS_IBT_BLOCK(mp) + 1;
पूर्ण

xfs_extlen_t
xfs_pपुनः_स्मृति_blocks(
	काष्ठा xfs_mount	*mp)
अणु
	अगर (xfs_sb_version_hasreflink(&mp->m_sb))
		वापस xfs_refc_block(mp) + 1;
	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस XFS_RMAP_BLOCK(mp) + 1;
	अगर (xfs_sb_version_hasfinobt(&mp->m_sb))
		वापस XFS_FIBT_BLOCK(mp) + 1;
	वापस XFS_IBT_BLOCK(mp) + 1;
पूर्ण

/*
 * In order to aव्योम ENOSPC-related deadlock caused by out-of-order locking of
 * AGF buffer (PV 947395), we place स्थिरraपूर्णांकs on the relationship among
 * actual allocations क्रम data blocks, मुक्तlist blocks, and potential file data
 * bmap btree blocks. However, these restrictions may result in no actual space
 * allocated क्रम a delayed extent, क्रम example, a data block in a certain AG is
 * allocated but there is no additional block क्रम the additional bmap btree
 * block due to a split of the bmap btree of the file. The result of this may
 * lead to an infinite loop when the file माला_लो flushed to disk and all delayed
 * extents need to be actually allocated. To get around this, we explicitly set
 * aside a few blocks which will not be reserved in delayed allocation.
 *
 * We need to reserve 4 fsbs _per AG_ क्रम the मुक्तlist and 4 more to handle a
 * potential split of the file's bmap btree.
 */
अचिन्हित पूर्णांक
xfs_alloc_set_aside(
	काष्ठा xfs_mount	*mp)
अणु
	वापस mp->m_sb.sb_agcount * (XFS_ALLOC_AGFL_RESERVE + 4);
पूर्ण

/*
 * When deciding how much space to allocate out of an AG, we limit the
 * allocation maximum size to the size the AG. However, we cannot use all the
 * blocks in the AG - some are permanently used by metadata. These
 * blocks are generally:
 *	- the AG superblock, AGF, AGI and AGFL
 *	- the AGF (bno and cnt) and AGI btree root blocks, and optionally
 *	  the AGI मुक्त inode and rmap btree root blocks.
 *	- blocks on the AGFL according to xfs_alloc_set_aside() limits
 *	- the rmapbt root block
 *
 * The AG headers are sector sized, so the amount of space they take up is
 * dependent on fileप्रणाली geometry. The others are all single blocks.
 */
अचिन्हित पूर्णांक
xfs_alloc_ag_max_usable(
	काष्ठा xfs_mount	*mp)
अणु
	अचिन्हित पूर्णांक		blocks;

	blocks = XFS_BB_TO_FSB(mp, XFS_FSS_TO_BB(mp, 4)); /* ag headers */
	blocks += XFS_ALLOC_AGFL_RESERVE;
	blocks += 3;			/* AGF, AGI btree root blocks */
	अगर (xfs_sb_version_hasfinobt(&mp->m_sb))
		blocks++;		/* finobt root block */
	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb))
		blocks++; 		/* rmap root block */
	अगर (xfs_sb_version_hasreflink(&mp->m_sb))
		blocks++;		/* refcount root block */

	वापस mp->m_sb.sb_agblocks - blocks;
पूर्ण

/*
 * Lookup the record equal to [bno, len] in the btree given by cur.
 */
STATIC पूर्णांक				/* error */
xfs_alloc_lookup_eq(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		bno,	/* starting block of extent */
	xfs_extlen_t		len,	/* length of extent */
	पूर्णांक			*stat)	/* success/failure */
अणु
	पूर्णांक			error;

	cur->bc_rec.a.ar_startblock = bno;
	cur->bc_rec.a.ar_blockcount = len;
	error = xfs_btree_lookup(cur, XFS_LOOKUP_EQ, stat);
	cur->bc_ag.abt.active = (*stat == 1);
	वापस error;
पूर्ण

/*
 * Lookup the first record greater than or equal to [bno, len]
 * in the btree given by cur.
 */
पूर्णांक				/* error */
xfs_alloc_lookup_ge(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		bno,	/* starting block of extent */
	xfs_extlen_t		len,	/* length of extent */
	पूर्णांक			*stat)	/* success/failure */
अणु
	पूर्णांक			error;

	cur->bc_rec.a.ar_startblock = bno;
	cur->bc_rec.a.ar_blockcount = len;
	error = xfs_btree_lookup(cur, XFS_LOOKUP_GE, stat);
	cur->bc_ag.abt.active = (*stat == 1);
	वापस error;
पूर्ण

/*
 * Lookup the first record less than or equal to [bno, len]
 * in the btree given by cur.
 */
पूर्णांक					/* error */
xfs_alloc_lookup_le(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		bno,	/* starting block of extent */
	xfs_extlen_t		len,	/* length of extent */
	पूर्णांक			*stat)	/* success/failure */
अणु
	पूर्णांक			error;
	cur->bc_rec.a.ar_startblock = bno;
	cur->bc_rec.a.ar_blockcount = len;
	error = xfs_btree_lookup(cur, XFS_LOOKUP_LE, stat);
	cur->bc_ag.abt.active = (*stat == 1);
	वापस error;
पूर्ण

अटल अंतरभूत bool
xfs_alloc_cur_active(
	काष्ठा xfs_btree_cur	*cur)
अणु
	वापस cur && cur->bc_ag.abt.active;
पूर्ण

/*
 * Update the record referred to by cur to the value given
 * by [bno, len].
 * This either works (वापस 0) or माला_लो an EFSCORRUPTED error.
 */
STATIC पूर्णांक				/* error */
xfs_alloc_update(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		bno,	/* starting block of extent */
	xfs_extlen_t		len)	/* length of extent */
अणु
	जोड़ xfs_btree_rec	rec;

	rec.alloc.ar_startblock = cpu_to_be32(bno);
	rec.alloc.ar_blockcount = cpu_to_be32(len);
	वापस xfs_btree_update(cur, &rec);
पूर्ण

/*
 * Get the data from the poपूर्णांकed-to record.
 */
पूर्णांक					/* error */
xfs_alloc_get_rec(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agblock_t		*bno,	/* output: starting block of extent */
	xfs_extlen_t		*len,	/* output: length of extent */
	पूर्णांक			*stat)	/* output: success/failure */
अणु
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	xfs_agnumber_t		agno = cur->bc_ag.agno;
	जोड़ xfs_btree_rec	*rec;
	पूर्णांक			error;

	error = xfs_btree_get_rec(cur, &rec, stat);
	अगर (error || !(*stat))
		वापस error;

	*bno = be32_to_cpu(rec->alloc.ar_startblock);
	*len = be32_to_cpu(rec->alloc.ar_blockcount);

	अगर (*len == 0)
		जाओ out_bad_rec;

	/* check क्रम valid extent range, including overflow */
	अगर (!xfs_verअगरy_agbno(mp, agno, *bno))
		जाओ out_bad_rec;
	अगर (*bno > *bno + *len)
		जाओ out_bad_rec;
	अगर (!xfs_verअगरy_agbno(mp, agno, *bno + *len - 1))
		जाओ out_bad_rec;

	वापस 0;

out_bad_rec:
	xfs_warn(mp,
		"%s Freespace BTree record corruption in AG %d detected!",
		cur->bc_btnum == XFS_BTNUM_BNO ? "Block" : "Size", agno);
	xfs_warn(mp,
		"start block 0x%x block count 0x%x", *bno, *len);
	वापस -EFSCORRUPTED;
पूर्ण

/*
 * Compute aligned version of the found extent.
 * Takes alignment and min length पूर्णांकo account.
 */
STATIC bool
xfs_alloc_compute_aligned(
	xfs_alloc_arg_t	*args,		/* allocation argument काष्ठाure */
	xfs_agblock_t	foundbno,	/* starting block in found extent */
	xfs_extlen_t	foundlen,	/* length in found extent */
	xfs_agblock_t	*resbno,	/* result block number */
	xfs_extlen_t	*reslen,	/* result length */
	अचिन्हित	*busy_gen)
अणु
	xfs_agblock_t	bno = foundbno;
	xfs_extlen_t	len = foundlen;
	xfs_extlen_t	dअगरf;
	bool		busy;

	/* Trim busy sections out of found extent */
	busy = xfs_extent_busy_trim(args, &bno, &len, busy_gen);

	/*
	 * If we have a largish extent that happens to start beक्रमe min_agbno,
	 * see अगर we can shअगरt it पूर्णांकo range...
	 */
	अगर (bno < args->min_agbno && bno + len > args->min_agbno) अणु
		dअगरf = args->min_agbno - bno;
		अगर (len > dअगरf) अणु
			bno += dअगरf;
			len -= dअगरf;
		पूर्ण
	पूर्ण

	अगर (args->alignment > 1 && len >= args->minlen) अणु
		xfs_agblock_t	aligned_bno = roundup(bno, args->alignment);

		dअगरf = aligned_bno - bno;

		*resbno = aligned_bno;
		*reslen = dअगरf >= len ? 0 : len - dअगरf;
	पूर्ण अन्यथा अणु
		*resbno = bno;
		*reslen = len;
	पूर्ण

	वापस busy;
पूर्ण

/*
 * Compute best start block and dअगरf क्रम "near" allocations.
 * मुक्तlen >= wantlen alपढ़ोy checked by caller.
 */
STATIC xfs_extlen_t			/* dअगरference value (असलolute) */
xfs_alloc_compute_dअगरf(
	xfs_agblock_t	wantbno,	/* target starting block */
	xfs_extlen_t	wantlen,	/* target length */
	xfs_extlen_t	alignment,	/* target alignment */
	पूर्णांक		datatype,	/* are we allocating data? */
	xfs_agblock_t	मुक्तbno,	/* मुक्तspace's starting block */
	xfs_extlen_t	मुक्तlen,	/* मुक्तspace's length */
	xfs_agblock_t	*newbnop)	/* result: best start block from मुक्त */
अणु
	xfs_agblock_t	मुक्तend;	/* end of मुक्तspace extent */
	xfs_agblock_t	newbno1;	/* वापस block number */
	xfs_agblock_t	newbno2;	/* other new block number */
	xfs_extlen_t	newlen1=0;	/* length with newbno1 */
	xfs_extlen_t	newlen2=0;	/* length with newbno2 */
	xfs_agblock_t	wantend;	/* end of target extent */
	bool		userdata = datatype & XFS_ALLOC_USERDATA;

	ASSERT(मुक्तlen >= wantlen);
	मुक्तend = मुक्तbno + मुक्तlen;
	wantend = wantbno + wantlen;
	/*
	 * We want to allocate from the start of a मुक्त extent अगर it is past
	 * the desired block or अगर we are allocating user data and the मुक्त
	 * extent is beक्रमe desired block. The second हाल is there to allow
	 * क्रम contiguous allocation from the reमुख्यing मुक्त space अगर the file
	 * grows in the लघु term.
	 */
	अगर (मुक्तbno >= wantbno || (userdata && मुक्तend < wantend)) अणु
		अगर ((newbno1 = roundup(मुक्तbno, alignment)) >= मुक्तend)
			newbno1 = शून्यAGBLOCK;
	पूर्ण अन्यथा अगर (मुक्तend >= wantend && alignment > 1) अणु
		newbno1 = roundup(wantbno, alignment);
		newbno2 = newbno1 - alignment;
		अगर (newbno1 >= मुक्तend)
			newbno1 = शून्यAGBLOCK;
		अन्यथा
			newlen1 = XFS_EXTLEN_MIN(wantlen, मुक्तend - newbno1);
		अगर (newbno2 < मुक्तbno)
			newbno2 = शून्यAGBLOCK;
		अन्यथा
			newlen2 = XFS_EXTLEN_MIN(wantlen, मुक्तend - newbno2);
		अगर (newbno1 != शून्यAGBLOCK && newbno2 != शून्यAGBLOCK) अणु
			अगर (newlen1 < newlen2 ||
			    (newlen1 == newlen2 &&
			     XFS_ABSDIFF(newbno1, wantbno) >
			     XFS_ABSDIFF(newbno2, wantbno)))
				newbno1 = newbno2;
		पूर्ण अन्यथा अगर (newbno2 != शून्यAGBLOCK)
			newbno1 = newbno2;
	पूर्ण अन्यथा अगर (मुक्तend >= wantend) अणु
		newbno1 = wantbno;
	पूर्ण अन्यथा अगर (alignment > 1) अणु
		newbno1 = roundup(मुक्तend - wantlen, alignment);
		अगर (newbno1 > मुक्तend - wantlen &&
		    newbno1 - alignment >= मुक्तbno)
			newbno1 -= alignment;
		अन्यथा अगर (newbno1 >= मुक्तend)
			newbno1 = शून्यAGBLOCK;
	पूर्ण अन्यथा
		newbno1 = मुक्तend - wantlen;
	*newbnop = newbno1;
	वापस newbno1 == शून्यAGBLOCK ? 0 : XFS_ABSDIFF(newbno1, wantbno);
पूर्ण

/*
 * Fix up the length, based on mod and prod.
 * len should be k * prod + mod क्रम some k.
 * If len is too small it is वापसed unchanged.
 * If len hits maxlen it is left alone.
 */
STATIC व्योम
xfs_alloc_fix_len(
	xfs_alloc_arg_t	*args)		/* allocation argument काष्ठाure */
अणु
	xfs_extlen_t	k;
	xfs_extlen_t	rlen;

	ASSERT(args->mod < args->prod);
	rlen = args->len;
	ASSERT(rlen >= args->minlen);
	ASSERT(rlen <= args->maxlen);
	अगर (args->prod <= 1 || rlen < args->mod || rlen == args->maxlen ||
	    (args->mod == 0 && rlen < args->prod))
		वापस;
	k = rlen % args->prod;
	अगर (k == args->mod)
		वापस;
	अगर (k > args->mod)
		rlen = rlen - (k - args->mod);
	अन्यथा
		rlen = rlen - args->prod + (args->mod - k);
	/* casts to (पूर्णांक) catch length underflows */
	अगर ((पूर्णांक)rlen < (पूर्णांक)args->minlen)
		वापस;
	ASSERT(rlen >= args->minlen && rlen <= args->maxlen);
	ASSERT(rlen % args->prod == args->mod);
	ASSERT(args->pag->pagf_मुक्तblks + args->pag->pagf_flcount >=
		rlen + args->minleft);
	args->len = rlen;
पूर्ण

/*
 * Update the two btrees, logically removing from मुक्तspace the extent
 * starting at rbno, rlen blocks.  The extent is contained within the
 * actual (current) मुक्त extent fbno क्रम flen blocks.
 * Flags are passed in indicating whether the cursors are set to the
 * relevant records.
 */
STATIC पूर्णांक				/* error code */
xfs_alloc_fixup_trees(
	xfs_btree_cur_t	*cnt_cur,	/* cursor क्रम by-size btree */
	xfs_btree_cur_t	*bno_cur,	/* cursor क्रम by-block btree */
	xfs_agblock_t	fbno,		/* starting block of मुक्त extent */
	xfs_extlen_t	flen,		/* length of मुक्त extent */
	xfs_agblock_t	rbno,		/* starting block of वापसed extent */
	xfs_extlen_t	rlen,		/* length of वापसed extent */
	पूर्णांक		flags)		/* flags, XFSA_FIXUP_... */
अणु
	पूर्णांक		error;		/* error code */
	पूर्णांक		i;		/* operation results */
	xfs_agblock_t	nfbno1;		/* first new मुक्त startblock */
	xfs_agblock_t	nfbno2;		/* second new मुक्त startblock */
	xfs_extlen_t	nflen1=0;	/* first new मुक्त length */
	xfs_extlen_t	nflen2=0;	/* second new मुक्त length */
	काष्ठा xfs_mount *mp;

	mp = cnt_cur->bc_mp;

	/*
	 * Look up the record in the by-size tree अगर necessary.
	 */
	अगर (flags & XFSA_FIXUP_CNT_OK) अणु
#अगर_घोषित DEBUG
		अगर ((error = xfs_alloc_get_rec(cnt_cur, &nfbno1, &nflen1, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp,
				   i != 1 ||
				   nfbno1 != fbno ||
				   nflen1 != flen))
			वापस -EFSCORRUPTED;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		अगर ((error = xfs_alloc_lookup_eq(cnt_cur, fbno, flen, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp, i != 1))
			वापस -EFSCORRUPTED;
	पूर्ण
	/*
	 * Look up the record in the by-block tree अगर necessary.
	 */
	अगर (flags & XFSA_FIXUP_BNO_OK) अणु
#अगर_घोषित DEBUG
		अगर ((error = xfs_alloc_get_rec(bno_cur, &nfbno1, &nflen1, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp,
				   i != 1 ||
				   nfbno1 != fbno ||
				   nflen1 != flen))
			वापस -EFSCORRUPTED;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		अगर ((error = xfs_alloc_lookup_eq(bno_cur, fbno, flen, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp, i != 1))
			वापस -EFSCORRUPTED;
	पूर्ण

#अगर_घोषित DEBUG
	अगर (bno_cur->bc_nlevels == 1 && cnt_cur->bc_nlevels == 1) अणु
		काष्ठा xfs_btree_block	*bnoblock;
		काष्ठा xfs_btree_block	*cntblock;

		bnoblock = XFS_BUF_TO_BLOCK(bno_cur->bc_bufs[0]);
		cntblock = XFS_BUF_TO_BLOCK(cnt_cur->bc_bufs[0]);

		अगर (XFS_IS_CORRUPT(mp,
				   bnoblock->bb_numrecs !=
				   cntblock->bb_numrecs))
			वापस -EFSCORRUPTED;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Deal with all four हालs: the allocated record is contained
	 * within the मुक्तspace record, so we can have new मुक्तspace
	 * at either (or both) end, or no मुक्तspace reमुख्यing.
	 */
	अगर (rbno == fbno && rlen == flen)
		nfbno1 = nfbno2 = शून्यAGBLOCK;
	अन्यथा अगर (rbno == fbno) अणु
		nfbno1 = rbno + rlen;
		nflen1 = flen - rlen;
		nfbno2 = शून्यAGBLOCK;
	पूर्ण अन्यथा अगर (rbno + rlen == fbno + flen) अणु
		nfbno1 = fbno;
		nflen1 = flen - rlen;
		nfbno2 = शून्यAGBLOCK;
	पूर्ण अन्यथा अणु
		nfbno1 = fbno;
		nflen1 = rbno - fbno;
		nfbno2 = rbno + rlen;
		nflen2 = (fbno + flen) - nfbno2;
	पूर्ण
	/*
	 * Delete the entry from the by-size btree.
	 */
	अगर ((error = xfs_btree_delete(cnt_cur, &i)))
		वापस error;
	अगर (XFS_IS_CORRUPT(mp, i != 1))
		वापस -EFSCORRUPTED;
	/*
	 * Add new by-size btree entry(s).
	 */
	अगर (nfbno1 != शून्यAGBLOCK) अणु
		अगर ((error = xfs_alloc_lookup_eq(cnt_cur, nfbno1, nflen1, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp, i != 0))
			वापस -EFSCORRUPTED;
		अगर ((error = xfs_btree_insert(cnt_cur, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp, i != 1))
			वापस -EFSCORRUPTED;
	पूर्ण
	अगर (nfbno2 != शून्यAGBLOCK) अणु
		अगर ((error = xfs_alloc_lookup_eq(cnt_cur, nfbno2, nflen2, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp, i != 0))
			वापस -EFSCORRUPTED;
		अगर ((error = xfs_btree_insert(cnt_cur, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp, i != 1))
			वापस -EFSCORRUPTED;
	पूर्ण
	/*
	 * Fix up the by-block btree entry(s).
	 */
	अगर (nfbno1 == शून्यAGBLOCK) अणु
		/*
		 * No reमुख्यing मुक्तspace, just delete the by-block tree entry.
		 */
		अगर ((error = xfs_btree_delete(bno_cur, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp, i != 1))
			वापस -EFSCORRUPTED;
	पूर्ण अन्यथा अणु
		/*
		 * Update the by-block entry to start later|be लघुer.
		 */
		अगर ((error = xfs_alloc_update(bno_cur, nfbno1, nflen1)))
			वापस error;
	पूर्ण
	अगर (nfbno2 != शून्यAGBLOCK) अणु
		/*
		 * 2 resulting मुक्त entries, need to add one.
		 */
		अगर ((error = xfs_alloc_lookup_eq(bno_cur, nfbno2, nflen2, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp, i != 0))
			वापस -EFSCORRUPTED;
		अगर ((error = xfs_btree_insert(bno_cur, &i)))
			वापस error;
		अगर (XFS_IS_CORRUPT(mp, i != 1))
			वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

अटल xfs_failaddr_t
xfs_agfl_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount *mp = bp->b_mount;
	काष्ठा xfs_agfl	*agfl = XFS_BUF_TO_AGFL(bp);
	__be32		*agfl_bno = xfs_buf_to_agfl_bno(bp);
	पूर्णांक		i;

	/*
	 * There is no verअगरication of non-crc AGFLs because mkfs करोes not
	 * initialise the AGFL to zero or शून्य. Hence the only valid part of the
	 * AGFL is what the AGF says is active. We can't get to the AGF, so we
	 * can't verअगरy just those entries are valid.
	 */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस शून्य;

	अगर (!xfs_verअगरy_magic(bp, agfl->agfl_magicnum))
		वापस __this_address;
	अगर (!uuid_equal(&agfl->agfl_uuid, &mp->m_sb.sb_meta_uuid))
		वापस __this_address;
	/*
	 * during growfs operations, the perag is not fully initialised,
	 * so we can't use it for any useful checking. growfs ensures we can't
	 * use it by using uncached buffers that करोn't have the perag attached
	 * so we can detect and aव्योम this problem.
	 */
	अगर (bp->b_pag && be32_to_cpu(agfl->agfl_seqno) != bp->b_pag->pag_agno)
		वापस __this_address;

	क्रम (i = 0; i < xfs_agfl_size(mp); i++) अणु
		अगर (be32_to_cpu(agfl_bno[i]) != शून्यAGBLOCK &&
		    be32_to_cpu(agfl_bno[i]) >= mp->m_sb.sb_agblocks)
			वापस __this_address;
	पूर्ण

	अगर (!xfs_log_check_lsn(mp, be64_to_cpu(XFS_BUF_TO_AGFL(bp)->agfl_lsn)))
		वापस __this_address;
	वापस शून्य;
पूर्ण

अटल व्योम
xfs_agfl_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount *mp = bp->b_mount;
	xfs_failaddr_t	fa;

	/*
	 * There is no verअगरication of non-crc AGFLs because mkfs करोes not
	 * initialise the AGFL to zero or शून्य. Hence the only valid part of the
	 * AGFL is what the AGF says is active. We can't get to the AGF, so we
	 * can't verअगरy just those entries are valid.
	 */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (!xfs_buf_verअगरy_cksum(bp, XFS_AGFL_CRC_OFF))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_agfl_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण
पूर्ण

अटल व्योम
xfs_agfl_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	xfs_failaddr_t		fa;

	/* no verअगरication of non-crc AGFLs */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	fa = xfs_agfl_verअगरy(bp);
	अगर (fa) अणु
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण

	अगर (bip)
		XFS_BUF_TO_AGFL(bp)->agfl_lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_AGFL_CRC_OFF);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_agfl_buf_ops = अणु
	.name = "xfs_agfl",
	.magic = अणु cpu_to_be32(XFS_AGFL_MAGIC), cpu_to_be32(XFS_AGFL_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_agfl_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_agfl_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_agfl_verअगरy,
पूर्ण;

/*
 * Read in the allocation group मुक्त block array.
 */
पूर्णांक					/* error */
xfs_alloc_पढ़ो_agfl(
	xfs_mount_t	*mp,		/* mount poपूर्णांक काष्ठाure */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_agnumber_t	agno,		/* allocation group number */
	काष्ठा xfs_buf	**bpp)		/* buffer क्रम the ag मुक्त block array */
अणु
	काष्ठा xfs_buf	*bp;		/* वापस value */
	पूर्णांक		error;

	ASSERT(agno != शून्यAGNUMBER);
	error = xfs_trans_पढ़ो_buf(
			mp, tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, agno, XFS_AGFL_DADDR(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &bp, &xfs_agfl_buf_ops);
	अगर (error)
		वापस error;
	xfs_buf_set_ref(bp, XFS_AGFL_REF);
	*bpp = bp;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_alloc_update_counters(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp,
	दीर्घ			len)
अणु
	काष्ठा xfs_agf		*agf = agbp->b_addr;

	agbp->b_pag->pagf_मुक्तblks += len;
	be32_add_cpu(&agf->agf_मुक्तblks, len);

	अगर (unlikely(be32_to_cpu(agf->agf_मुक्तblks) >
		     be32_to_cpu(agf->agf_length))) अणु
		xfs_buf_mark_corrupt(agbp);
		वापस -EFSCORRUPTED;
	पूर्ण

	xfs_alloc_log_agf(tp, agbp, XFS_AGF_FREEBLKS);
	वापस 0;
पूर्ण

/*
 * Block allocation algorithm and data काष्ठाures.
 */
काष्ठा xfs_alloc_cur अणु
	काष्ठा xfs_btree_cur		*cnt;	/* btree cursors */
	काष्ठा xfs_btree_cur		*bnolt;
	काष्ठा xfs_btree_cur		*bnogt;
	xfs_extlen_t			cur_len;/* current search length */
	xfs_agblock_t			rec_bno;/* extent startblock */
	xfs_extlen_t			rec_len;/* extent length */
	xfs_agblock_t			bno;	/* alloc bno */
	xfs_extlen_t			len;	/* alloc len */
	xfs_extlen_t			dअगरf;	/* dअगरf from search bno */
	अचिन्हित पूर्णांक			busy_gen;/* busy state */
	bool				busy;
पूर्ण;

/*
 * Set up cursors, etc. in the extent allocation cursor. This function can be
 * called multiple बार to reset an initialized काष्ठाure without having to
 * पुनः_स्मृतिate cursors.
 */
अटल पूर्णांक
xfs_alloc_cur_setup(
	काष्ठा xfs_alloc_arg	*args,
	काष्ठा xfs_alloc_cur	*acur)
अणु
	पूर्णांक			error;
	पूर्णांक			i;

	ASSERT(args->alignment == 1 || args->type != XFS_ALLOCTYPE_THIS_BNO);

	acur->cur_len = args->maxlen;
	acur->rec_bno = 0;
	acur->rec_len = 0;
	acur->bno = 0;
	acur->len = 0;
	acur->dअगरf = -1;
	acur->busy = false;
	acur->busy_gen = 0;

	/*
	 * Perक्रमm an initial cntbt lookup to check क्रम availability of maxlen
	 * extents. If this fails, we'll वापस -ENOSPC to संकेत the caller to
	 * attempt a small allocation.
	 */
	अगर (!acur->cnt)
		acur->cnt = xfs_allocbt_init_cursor(args->mp, args->tp,
					args->agbp, args->agno, XFS_BTNUM_CNT);
	error = xfs_alloc_lookup_ge(acur->cnt, 0, args->maxlen, &i);
	अगर (error)
		वापस error;

	/*
	 * Allocate the bnobt left and right search cursors.
	 */
	अगर (!acur->bnolt)
		acur->bnolt = xfs_allocbt_init_cursor(args->mp, args->tp,
					args->agbp, args->agno, XFS_BTNUM_BNO);
	अगर (!acur->bnogt)
		acur->bnogt = xfs_allocbt_init_cursor(args->mp, args->tp,
					args->agbp, args->agno, XFS_BTNUM_BNO);
	वापस i == 1 ? 0 : -ENOSPC;
पूर्ण

अटल व्योम
xfs_alloc_cur_बंद(
	काष्ठा xfs_alloc_cur	*acur,
	bool			error)
अणु
	पूर्णांक			cur_error = XFS_BTREE_NOERROR;

	अगर (error)
		cur_error = XFS_BTREE_ERROR;

	अगर (acur->cnt)
		xfs_btree_del_cursor(acur->cnt, cur_error);
	अगर (acur->bnolt)
		xfs_btree_del_cursor(acur->bnolt, cur_error);
	अगर (acur->bnogt)
		xfs_btree_del_cursor(acur->bnogt, cur_error);
	acur->cnt = acur->bnolt = acur->bnogt = शून्य;
पूर्ण

/*
 * Check an extent क्रम allocation and track the best available candidate in the
 * allocation काष्ठाure. The cursor is deactivated अगर it has entered an out of
 * range state based on allocation arguments. Optionally वापस the extent
 * extent geometry and allocation status अगर requested by the caller.
 */
अटल पूर्णांक
xfs_alloc_cur_check(
	काष्ठा xfs_alloc_arg	*args,
	काष्ठा xfs_alloc_cur	*acur,
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			*new)
अणु
	पूर्णांक			error, i;
	xfs_agblock_t		bno, bnoa, bnew;
	xfs_extlen_t		len, lena, dअगरf = -1;
	bool			busy;
	अचिन्हित		busy_gen = 0;
	bool			deactivate = false;
	bool			isbnobt = cur->bc_btnum == XFS_BTNUM_BNO;

	*new = 0;

	error = xfs_alloc_get_rec(cur, &bno, &len, &i);
	अगर (error)
		वापस error;
	अगर (XFS_IS_CORRUPT(args->mp, i != 1))
		वापस -EFSCORRUPTED;

	/*
	 * Check minlen and deactivate a cntbt cursor अगर out of acceptable size
	 * range (i.e., walking backwards looking क्रम a minlen extent).
	 */
	अगर (len < args->minlen) अणु
		deactivate = !isbnobt;
		जाओ out;
	पूर्ण

	busy = xfs_alloc_compute_aligned(args, bno, len, &bnoa, &lena,
					 &busy_gen);
	acur->busy |= busy;
	अगर (busy)
		acur->busy_gen = busy_gen;
	/* deactivate a bnobt cursor outside of locality range */
	अगर (bnoa < args->min_agbno || bnoa > args->max_agbno) अणु
		deactivate = isbnobt;
		जाओ out;
	पूर्ण
	अगर (lena < args->minlen)
		जाओ out;

	args->len = XFS_EXTLEN_MIN(lena, args->maxlen);
	xfs_alloc_fix_len(args);
	ASSERT(args->len >= args->minlen);
	अगर (args->len < acur->len)
		जाओ out;

	/*
	 * We have an aligned record that satisfies minlen and beats or matches
	 * the candidate extent size. Compare locality क्रम near allocation mode.
	 */
	ASSERT(args->type == XFS_ALLOCTYPE_NEAR_BNO);
	dअगरf = xfs_alloc_compute_dअगरf(args->agbno, args->len,
				      args->alignment, args->datatype,
				      bnoa, lena, &bnew);
	अगर (bnew == शून्यAGBLOCK)
		जाओ out;

	/*
	 * Deactivate a bnobt cursor with worse locality than the current best.
	 */
	अगर (dअगरf > acur->dअगरf) अणु
		deactivate = isbnobt;
		जाओ out;
	पूर्ण

	ASSERT(args->len > acur->len ||
	       (args->len == acur->len && dअगरf <= acur->dअगरf));
	acur->rec_bno = bno;
	acur->rec_len = len;
	acur->bno = bnew;
	acur->len = args->len;
	acur->dअगरf = dअगरf;
	*new = 1;

	/*
	 * We're करोne अगर we found a perfect allocation. This only deactivates
	 * the current cursor, but this is just an optimization to terminate a
	 * cntbt search that otherwise runs to the edge of the tree.
	 */
	अगर (acur->dअगरf == 0 && acur->len == args->maxlen)
		deactivate = true;
out:
	अगर (deactivate)
		cur->bc_ag.abt.active = false;
	trace_xfs_alloc_cur_check(args->mp, cur->bc_btnum, bno, len, dअगरf,
				  *new);
	वापस 0;
पूर्ण

/*
 * Complete an allocation of a candidate extent. Remove the extent from both
 * trees and update the args काष्ठाure.
 */
STATIC पूर्णांक
xfs_alloc_cur_finish(
	काष्ठा xfs_alloc_arg	*args,
	काष्ठा xfs_alloc_cur	*acur)
अणु
	काष्ठा xfs_agf __maybe_unused *agf = args->agbp->b_addr;
	पूर्णांक			error;

	ASSERT(acur->cnt && acur->bnolt);
	ASSERT(acur->bno >= acur->rec_bno);
	ASSERT(acur->bno + acur->len <= acur->rec_bno + acur->rec_len);
	ASSERT(acur->rec_bno + acur->rec_len <= be32_to_cpu(agf->agf_length));

	error = xfs_alloc_fixup_trees(acur->cnt, acur->bnolt, acur->rec_bno,
				      acur->rec_len, acur->bno, acur->len, 0);
	अगर (error)
		वापस error;

	args->agbno = acur->bno;
	args->len = acur->len;
	args->wasfromfl = 0;

	trace_xfs_alloc_cur(args);
	वापस 0;
पूर्ण

/*
 * Locality allocation lookup algorithm. This expects a cntbt cursor and uses
 * bno optimized lookup to search क्रम extents with ideal size and locality.
 */
STATIC पूर्णांक
xfs_alloc_cntbt_iter(
	काष्ठा xfs_alloc_arg		*args,
	काष्ठा xfs_alloc_cur		*acur)
अणु
	काष्ठा xfs_btree_cur	*cur = acur->cnt;
	xfs_agblock_t		bno;
	xfs_extlen_t		len, cur_len;
	पूर्णांक			error;
	पूर्णांक			i;

	अगर (!xfs_alloc_cur_active(cur))
		वापस 0;

	/* locality optimized lookup */
	cur_len = acur->cur_len;
	error = xfs_alloc_lookup_ge(cur, args->agbno, cur_len, &i);
	अगर (error)
		वापस error;
	अगर (i == 0)
		वापस 0;
	error = xfs_alloc_get_rec(cur, &bno, &len, &i);
	अगर (error)
		वापस error;

	/* check the current record and update search length from it */
	error = xfs_alloc_cur_check(args, acur, cur, &i);
	अगर (error)
		वापस error;
	ASSERT(len >= acur->cur_len);
	acur->cur_len = len;

	/*
	 * We looked up the first record >= [agbno, len] above. The agbno is a
	 * secondary key and so the current record may lie just beक्रमe or after
	 * agbno. If it is past agbno, check the previous record too so दीर्घ as
	 * the length matches as it may be बंदr. Don't check a smaller record
	 * because that could deactivate our cursor.
	 */
	अगर (bno > args->agbno) अणु
		error = xfs_btree_decrement(cur, 0, &i);
		अगर (!error && i) अणु
			error = xfs_alloc_get_rec(cur, &bno, &len, &i);
			अगर (!error && i && len == acur->cur_len)
				error = xfs_alloc_cur_check(args, acur, cur,
							    &i);
		पूर्ण
		अगर (error)
			वापस error;
	पूर्ण

	/*
	 * Increment the search key until we find at least one allocation
	 * candidate or अगर the extent we found was larger. Otherwise, द्विगुन the
	 * search key to optimize the search. Efficiency is more important here
	 * than असलolute best locality.
	 */
	cur_len <<= 1;
	अगर (!acur->len || acur->cur_len >= cur_len)
		acur->cur_len++;
	अन्यथा
		acur->cur_len = cur_len;

	वापस error;
पूर्ण

/*
 * Deal with the हाल where only small मुक्तspaces reमुख्य. Either वापस the
 * contents of the last मुक्तspace record, or allocate space from the मुक्तlist अगर
 * there is nothing in the tree.
 */
STATIC पूर्णांक			/* error */
xfs_alloc_ag_vextent_small(
	काष्ठा xfs_alloc_arg	*args,	/* allocation argument काष्ठाure */
	काष्ठा xfs_btree_cur	*ccur,	/* optional by-size cursor */
	xfs_agblock_t		*fbnop,	/* result block number */
	xfs_extlen_t		*flenp,	/* result length */
	पूर्णांक			*stat)	/* status: 0-मुक्तlist, 1-normal/none */
अणु
	काष्ठा xfs_agf		*agf = args->agbp->b_addr;
	पूर्णांक			error = 0;
	xfs_agblock_t		fbno = शून्यAGBLOCK;
	xfs_extlen_t		flen = 0;
	पूर्णांक			i = 0;

	/*
	 * If a cntbt cursor is provided, try to allocate the largest record in
	 * the tree. Try the AGFL अगर the cntbt is empty, otherwise fail the
	 * allocation. Make sure to respect minleft even when pulling from the
	 * मुक्तlist.
	 */
	अगर (ccur)
		error = xfs_btree_decrement(ccur, 0, &i);
	अगर (error)
		जाओ error;
	अगर (i) अणु
		error = xfs_alloc_get_rec(ccur, &fbno, &flen, &i);
		अगर (error)
			जाओ error;
		अगर (XFS_IS_CORRUPT(args->mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error;
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (args->minlen != 1 || args->alignment != 1 ||
	    args->resv == XFS_AG_RESV_AGFL ||
	    be32_to_cpu(agf->agf_flcount) <= args->minleft)
		जाओ out;

	error = xfs_alloc_get_मुक्तlist(args->tp, args->agbp, &fbno, 0);
	अगर (error)
		जाओ error;
	अगर (fbno == शून्यAGBLOCK)
		जाओ out;

	xfs_extent_busy_reuse(args->mp, args->agno, fbno, 1,
			      (args->datatype & XFS_ALLOC_NOBUSY));

	अगर (args->datatype & XFS_ALLOC_USERDATA) अणु
		काष्ठा xfs_buf	*bp;

		error = xfs_trans_get_buf(args->tp, args->mp->m_ddev_targp,
				XFS_AGB_TO_DADDR(args->mp, args->agno, fbno),
				args->mp->m_bsize, 0, &bp);
		अगर (error)
			जाओ error;
		xfs_trans_binval(args->tp, bp);
	पूर्ण
	*fbnop = args->agbno = fbno;
	*flenp = args->len = 1;
	अगर (XFS_IS_CORRUPT(args->mp, fbno >= be32_to_cpu(agf->agf_length))) अणु
		error = -EFSCORRUPTED;
		जाओ error;
	पूर्ण
	args->wasfromfl = 1;
	trace_xfs_alloc_small_मुक्तlist(args);

	/*
	 * If we're feeding an AGFL block to something that doesn't live in the
	 * मुक्त space, we need to clear out the OWN_AG rmap.
	 */
	error = xfs_rmap_मुक्त(args->tp, args->agbp, args->agno, fbno, 1,
			      &XFS_RMAP_OINFO_AG);
	अगर (error)
		जाओ error;

	*stat = 0;
	वापस 0;

out:
	/*
	 * Can't करो the allocation, give up.
	 */
	अगर (flen < args->minlen) अणु
		args->agbno = शून्यAGBLOCK;
		trace_xfs_alloc_small_notenough(args);
		flen = 0;
	पूर्ण
	*fbnop = fbno;
	*flenp = flen;
	*stat = 1;
	trace_xfs_alloc_small_करोne(args);
	वापस 0;

error:
	trace_xfs_alloc_small_error(args);
	वापस error;
पूर्ण

/*
 * Allocate a variable extent in the allocation group agno.
 * Type and bno are used to determine where in the allocation group the
 * extent will start.
 * Extent's length (वापसed in *len) will be between minlen and maxlen,
 * and of the क्रमm k * prod + mod unless there's nothing that large.
 * Return the starting a.g. block, or शून्यAGBLOCK अगर we can't करो it.
 */
STATIC पूर्णांक			/* error */
xfs_alloc_ag_vextent(
	xfs_alloc_arg_t	*args)	/* argument काष्ठाure क्रम allocation */
अणु
	पूर्णांक		error=0;

	ASSERT(args->minlen > 0);
	ASSERT(args->maxlen > 0);
	ASSERT(args->minlen <= args->maxlen);
	ASSERT(args->mod < args->prod);
	ASSERT(args->alignment > 0);

	/*
	 * Branch to correct routine based on the type.
	 */
	args->wasfromfl = 0;
	चयन (args->type) अणु
	हाल XFS_ALLOCTYPE_THIS_AG:
		error = xfs_alloc_ag_vextent_size(args);
		अवरोध;
	हाल XFS_ALLOCTYPE_NEAR_BNO:
		error = xfs_alloc_ag_vextent_near(args);
		अवरोध;
	हाल XFS_ALLOCTYPE_THIS_BNO:
		error = xfs_alloc_ag_vextent_exact(args);
		अवरोध;
	शेष:
		ASSERT(0);
		/* NOTREACHED */
	पूर्ण

	अगर (error || args->agbno == शून्यAGBLOCK)
		वापस error;

	ASSERT(args->len >= args->minlen);
	ASSERT(args->len <= args->maxlen);
	ASSERT(!args->wasfromfl || args->resv != XFS_AG_RESV_AGFL);
	ASSERT(args->agbno % args->alignment == 0);

	/* अगर not file data, insert new block पूर्णांकo the reverse map btree */
	अगर (!xfs_rmap_should_skip_owner_update(&args->oinfo)) अणु
		error = xfs_rmap_alloc(args->tp, args->agbp, args->agno,
				       args->agbno, args->len, &args->oinfo);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (!args->wasfromfl) अणु
		error = xfs_alloc_update_counters(args->tp, args->agbp,
						  -((दीर्घ)(args->len)));
		अगर (error)
			वापस error;

		ASSERT(!xfs_extent_busy_search(args->mp, args->agno,
					      args->agbno, args->len));
	पूर्ण

	xfs_ag_resv_alloc_extent(args->pag, args->resv, args);

	XFS_STATS_INC(args->mp, xs_allocx);
	XFS_STATS_ADD(args->mp, xs_allocb, args->len);
	वापस error;
पूर्ण

/*
 * Allocate a variable extent at exactly agno/bno.
 * Extent's length (वापसed in *len) will be between minlen and maxlen,
 * and of the क्रमm k * prod + mod unless there's nothing that large.
 * Return the starting a.g. block (bno), or शून्यAGBLOCK अगर we can't करो it.
 */
STATIC पूर्णांक			/* error */
xfs_alloc_ag_vextent_exact(
	xfs_alloc_arg_t	*args)	/* allocation argument काष्ठाure */
अणु
	काष्ठा xfs_agf __maybe_unused *agf = args->agbp->b_addr;
	xfs_btree_cur_t	*bno_cur;/* by block-number btree cursor */
	xfs_btree_cur_t	*cnt_cur;/* by count btree cursor */
	पूर्णांक		error;
	xfs_agblock_t	fbno;	/* start block of found extent */
	xfs_extlen_t	flen;	/* length of found extent */
	xfs_agblock_t	tbno;	/* start block of busy extent */
	xfs_extlen_t	tlen;	/* length of busy extent */
	xfs_agblock_t	tend;	/* end block of busy extent */
	पूर्णांक		i;	/* success/failure of operation */
	अचिन्हित	busy_gen;

	ASSERT(args->alignment == 1);

	/*
	 * Allocate/initialize a cursor क्रम the by-number मुक्तspace btree.
	 */
	bno_cur = xfs_allocbt_init_cursor(args->mp, args->tp, args->agbp,
					  args->agno, XFS_BTNUM_BNO);

	/*
	 * Lookup bno and minlen in the btree (minlen is irrelevant, really).
	 * Look क्रम the बंदst मुक्त block <= bno, it must contain bno
	 * अगर any मुक्त block करोes.
	 */
	error = xfs_alloc_lookup_le(bno_cur, args->agbno, args->minlen, &i);
	अगर (error)
		जाओ error0;
	अगर (!i)
		जाओ not_found;

	/*
	 * Grab the मुक्तspace record.
	 */
	error = xfs_alloc_get_rec(bno_cur, &fbno, &flen, &i);
	अगर (error)
		जाओ error0;
	अगर (XFS_IS_CORRUPT(args->mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण
	ASSERT(fbno <= args->agbno);

	/*
	 * Check क्रम overlapping busy extents.
	 */
	tbno = fbno;
	tlen = flen;
	xfs_extent_busy_trim(args, &tbno, &tlen, &busy_gen);

	/*
	 * Give up अगर the start of the extent is busy, or the मुक्तspace isn't
	 * दीर्घ enough क्रम the minimum request.
	 */
	अगर (tbno > args->agbno)
		जाओ not_found;
	अगर (tlen < args->minlen)
		जाओ not_found;
	tend = tbno + tlen;
	अगर (tend < args->agbno + args->minlen)
		जाओ not_found;

	/*
	 * End of extent will be smaller of the मुक्तspace end and the
	 * maximal requested end.
	 *
	 * Fix the length according to mod and prod अगर given.
	 */
	args->len = XFS_AGBLOCK_MIN(tend, args->agbno + args->maxlen)
						- args->agbno;
	xfs_alloc_fix_len(args);
	ASSERT(args->agbno + args->len <= tend);

	/*
	 * We are allocating agbno क्रम args->len
	 * Allocate/initialize a cursor क्रम the by-size btree.
	 */
	cnt_cur = xfs_allocbt_init_cursor(args->mp, args->tp, args->agbp,
		args->agno, XFS_BTNUM_CNT);
	ASSERT(args->agbno + args->len <= be32_to_cpu(agf->agf_length));
	error = xfs_alloc_fixup_trees(cnt_cur, bno_cur, fbno, flen, args->agbno,
				      args->len, XFSA_FIXUP_BNO_OK);
	अगर (error) अणु
		xfs_btree_del_cursor(cnt_cur, XFS_BTREE_ERROR);
		जाओ error0;
	पूर्ण

	xfs_btree_del_cursor(bno_cur, XFS_BTREE_NOERROR);
	xfs_btree_del_cursor(cnt_cur, XFS_BTREE_NOERROR);

	args->wasfromfl = 0;
	trace_xfs_alloc_exact_करोne(args);
	वापस 0;

not_found:
	/* Didn't find it, वापस null. */
	xfs_btree_del_cursor(bno_cur, XFS_BTREE_NOERROR);
	args->agbno = शून्यAGBLOCK;
	trace_xfs_alloc_exact_notfound(args);
	वापस 0;

error0:
	xfs_btree_del_cursor(bno_cur, XFS_BTREE_ERROR);
	trace_xfs_alloc_exact_error(args);
	वापस error;
पूर्ण

/*
 * Search a given number of btree records in a given direction. Check each
 * record against the good extent we've alपढ़ोy found.
 */
STATIC पूर्णांक
xfs_alloc_walk_iter(
	काष्ठा xfs_alloc_arg	*args,
	काष्ठा xfs_alloc_cur	*acur,
	काष्ठा xfs_btree_cur	*cur,
	bool			increment,
	bool			find_one, /* quit on first candidate */
	पूर्णांक			count,    /* rec count (-1 क्रम infinite) */
	पूर्णांक			*stat)
अणु
	पूर्णांक			error;
	पूर्णांक			i;

	*stat = 0;

	/*
	 * Search so दीर्घ as the cursor is active or we find a better extent.
	 * The cursor is deactivated अगर it extends beyond the range of the
	 * current allocation candidate.
	 */
	जबतक (xfs_alloc_cur_active(cur) && count) अणु
		error = xfs_alloc_cur_check(args, acur, cur, &i);
		अगर (error)
			वापस error;
		अगर (i == 1) अणु
			*stat = 1;
			अगर (find_one)
				अवरोध;
		पूर्ण
		अगर (!xfs_alloc_cur_active(cur))
			अवरोध;

		अगर (increment)
			error = xfs_btree_increment(cur, 0, &i);
		अन्यथा
			error = xfs_btree_decrement(cur, 0, &i);
		अगर (error)
			वापस error;
		अगर (i == 0)
			cur->bc_ag.abt.active = false;

		अगर (count > 0)
			count--;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Search the by-bno and by-size btrees in parallel in search of an extent with
 * ideal locality based on the NEAR mode ->agbno locality hपूर्णांक.
 */
STATIC पूर्णांक
xfs_alloc_ag_vextent_locality(
	काष्ठा xfs_alloc_arg	*args,
	काष्ठा xfs_alloc_cur	*acur,
	पूर्णांक			*stat)
अणु
	काष्ठा xfs_btree_cur	*fbcur = शून्य;
	पूर्णांक			error;
	पूर्णांक			i;
	bool			fbinc;

	ASSERT(acur->len == 0);
	ASSERT(args->type == XFS_ALLOCTYPE_NEAR_BNO);

	*stat = 0;

	error = xfs_alloc_lookup_ge(acur->cnt, args->agbno, acur->cur_len, &i);
	अगर (error)
		वापस error;
	error = xfs_alloc_lookup_le(acur->bnolt, args->agbno, 0, &i);
	अगर (error)
		वापस error;
	error = xfs_alloc_lookup_ge(acur->bnogt, args->agbno, 0, &i);
	अगर (error)
		वापस error;

	/*
	 * Search the bnobt and cntbt in parallel. Search the bnobt left and
	 * right and lookup the बंदst extent to the locality hपूर्णांक क्रम each
	 * extent size key in the cntbt. The entire search terminates
	 * immediately on a bnobt hit because that means we've found best हाल
	 * locality. Otherwise the search जारीs until the cntbt cursor runs
	 * off the end of the tree. If no allocation candidate is found at this
	 * poपूर्णांक, give up on locality, walk backwards from the end of the cntbt
	 * and take the first available extent.
	 *
	 * The parallel tree searches balance each other out to provide fairly
	 * consistent perक्रमmance क्रम various situations. The bnobt search can
	 * have pathological behavior in the worst हाल scenario of larger
	 * allocation requests and fragmented मुक्त space. On the other hand, the
	 * bnobt is able to satisfy most smaller allocation requests much more
	 * quickly than the cntbt. The cntbt search can sअगरt through fragmented
	 * मुक्त space and sets of मुक्त extents क्रम larger allocation requests
	 * more quickly than the bnobt. Since the locality hपूर्णांक is just a hपूर्णांक
	 * and we करोn't want to scan the entire bnobt क्रम perfect locality, the
	 * cntbt search essentially bounds the bnobt search such that we can
	 * find good enough locality at reasonable perक्रमmance in most हालs.
	 */
	जबतक (xfs_alloc_cur_active(acur->bnolt) ||
	       xfs_alloc_cur_active(acur->bnogt) ||
	       xfs_alloc_cur_active(acur->cnt)) अणु

		trace_xfs_alloc_cur_lookup(args);

		/*
		 * Search the bnobt left and right. In the हाल of a hit, finish
		 * the search in the opposite direction and we're करोne.
		 */
		error = xfs_alloc_walk_iter(args, acur, acur->bnolt, false,
					    true, 1, &i);
		अगर (error)
			वापस error;
		अगर (i == 1) अणु
			trace_xfs_alloc_cur_left(args);
			fbcur = acur->bnogt;
			fbinc = true;
			अवरोध;
		पूर्ण
		error = xfs_alloc_walk_iter(args, acur, acur->bnogt, true, true,
					    1, &i);
		अगर (error)
			वापस error;
		अगर (i == 1) अणु
			trace_xfs_alloc_cur_right(args);
			fbcur = acur->bnolt;
			fbinc = false;
			अवरोध;
		पूर्ण

		/*
		 * Check the extent with best locality based on the current
		 * extent size search key and keep track of the best candidate.
		 */
		error = xfs_alloc_cntbt_iter(args, acur);
		अगर (error)
			वापस error;
		अगर (!xfs_alloc_cur_active(acur->cnt)) अणु
			trace_xfs_alloc_cur_lookup_करोne(args);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If we failed to find anything due to busy extents, वापस empty
	 * handed so the caller can flush and retry. If no busy extents were
	 * found, walk backwards from the end of the cntbt as a last resort.
	 */
	अगर (!xfs_alloc_cur_active(acur->cnt) && !acur->len && !acur->busy) अणु
		error = xfs_btree_decrement(acur->cnt, 0, &i);
		अगर (error)
			वापस error;
		अगर (i) अणु
			acur->cnt->bc_ag.abt.active = true;
			fbcur = acur->cnt;
			fbinc = false;
		पूर्ण
	पूर्ण

	/*
	 * Search in the opposite direction क्रम a better entry in the हाल of
	 * a bnobt hit or walk backwards from the end of the cntbt.
	 */
	अगर (fbcur) अणु
		error = xfs_alloc_walk_iter(args, acur, fbcur, fbinc, true, -1,
					    &i);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (acur->len)
		*stat = 1;

	वापस 0;
पूर्ण

/* Check the last block of the cnt btree क्रम allocations. */
अटल पूर्णांक
xfs_alloc_ag_vextent_lastblock(
	काष्ठा xfs_alloc_arg	*args,
	काष्ठा xfs_alloc_cur	*acur,
	xfs_agblock_t		*bno,
	xfs_extlen_t		*len,
	bool			*allocated)
अणु
	पूर्णांक			error;
	पूर्णांक			i;

#अगर_घोषित DEBUG
	/* Ranकरोmly करोn't execute the first algorithm. */
	अगर (pअक्रमom_u32() & 1)
		वापस 0;
#पूर्ण_अगर

	/*
	 * Start from the entry that lookup found, sequence through all larger
	 * मुक्त blocks.  If we're actually poपूर्णांकing at a record smaller than
	 * maxlen, go to the start of this block, and skip all those smaller
	 * than minlen.
	 */
	अगर (*len || args->alignment > 1) अणु
		acur->cnt->bc_ptrs[0] = 1;
		करो अणु
			error = xfs_alloc_get_rec(acur->cnt, bno, len, &i);
			अगर (error)
				वापस error;
			अगर (XFS_IS_CORRUPT(args->mp, i != 1))
				वापस -EFSCORRUPTED;
			अगर (*len >= args->minlen)
				अवरोध;
			error = xfs_btree_increment(acur->cnt, 0, &i);
			अगर (error)
				वापस error;
		पूर्ण जबतक (i);
		ASSERT(*len >= args->minlen);
		अगर (!i)
			वापस 0;
	पूर्ण

	error = xfs_alloc_walk_iter(args, acur, acur->cnt, true, false, -1, &i);
	अगर (error)
		वापस error;

	/*
	 * It didn't work.  We COULD be in a case where there's a good record
	 * somewhere, so try again.
	 */
	अगर (acur->len == 0)
		वापस 0;

	trace_xfs_alloc_near_first(args);
	*allocated = true;
	वापस 0;
पूर्ण

/*
 * Allocate a variable extent near bno in the allocation group agno.
 * Extent's length (वापसed in len) will be between minlen and maxlen,
 * and of the क्रमm k * prod + mod unless there's nothing that large.
 * Return the starting a.g. block, or शून्यAGBLOCK अगर we can't करो it.
 */
STATIC पूर्णांक
xfs_alloc_ag_vextent_near(
	काष्ठा xfs_alloc_arg	*args)
अणु
	काष्ठा xfs_alloc_cur	acur = अणुपूर्ण;
	पूर्णांक			error;		/* error code */
	पूर्णांक			i;		/* result code, temporary */
	xfs_agblock_t		bno;
	xfs_extlen_t		len;

	/* handle uninitialized agbno range so caller करोesn't have to */
	अगर (!args->min_agbno && !args->max_agbno)
		args->max_agbno = args->mp->m_sb.sb_agblocks - 1;
	ASSERT(args->min_agbno <= args->max_agbno);

	/* clamp agbno to the range अगर it's outside */
	अगर (args->agbno < args->min_agbno)
		args->agbno = args->min_agbno;
	अगर (args->agbno > args->max_agbno)
		args->agbno = args->max_agbno;

restart:
	len = 0;

	/*
	 * Set up cursors and see अगर there are any मुक्त extents as big as
	 * maxlen. If not, pick the last entry in the tree unless the tree is
	 * empty.
	 */
	error = xfs_alloc_cur_setup(args, &acur);
	अगर (error == -ENOSPC) अणु
		error = xfs_alloc_ag_vextent_small(args, acur.cnt, &bno,
				&len, &i);
		अगर (error)
			जाओ out;
		अगर (i == 0 || len == 0) अणु
			trace_xfs_alloc_near_noentry(args);
			जाओ out;
		पूर्ण
		ASSERT(i == 1);
	पूर्ण अन्यथा अगर (error) अणु
		जाओ out;
	पूर्ण

	/*
	 * First algorithm.
	 * If the requested extent is large wrt the मुक्तspaces available
	 * in this a.g., then the cursor will be poपूर्णांकing to a btree entry
	 * near the right edge of the tree.  If it's in the last btree leaf
	 * block, then we just examine all the entries in that block
	 * that are big enough, and pick the best one.
	 */
	अगर (xfs_btree_islastblock(acur.cnt, 0)) अणु
		bool		allocated = false;

		error = xfs_alloc_ag_vextent_lastblock(args, &acur, &bno, &len,
				&allocated);
		अगर (error)
			जाओ out;
		अगर (allocated)
			जाओ alloc_finish;
	पूर्ण

	/*
	 * Second algorithm. Combined cntbt and bnobt search to find ideal
	 * locality.
	 */
	error = xfs_alloc_ag_vextent_locality(args, &acur, &i);
	अगर (error)
		जाओ out;

	/*
	 * If we couldn't get anything, give up.
	 */
	अगर (!acur.len) अणु
		अगर (acur.busy) अणु
			trace_xfs_alloc_near_busy(args);
			xfs_extent_busy_flush(args->mp, args->pag,
					      acur.busy_gen);
			जाओ restart;
		पूर्ण
		trace_xfs_alloc_size_neither(args);
		args->agbno = शून्यAGBLOCK;
		जाओ out;
	पूर्ण

alloc_finish:
	/* fix up btrees on a successful allocation */
	error = xfs_alloc_cur_finish(args, &acur);

out:
	xfs_alloc_cur_बंद(&acur, error);
	वापस error;
पूर्ण

/*
 * Allocate a variable extent anywhere in the allocation group agno.
 * Extent's length (वापसed in len) will be between minlen and maxlen,
 * and of the क्रमm k * prod + mod unless there's nothing that large.
 * Return the starting a.g. block, or शून्यAGBLOCK अगर we can't करो it.
 */
STATIC पूर्णांक				/* error */
xfs_alloc_ag_vextent_size(
	xfs_alloc_arg_t	*args)		/* allocation argument काष्ठाure */
अणु
	काष्ठा xfs_agf	*agf = args->agbp->b_addr;
	xfs_btree_cur_t	*bno_cur;	/* cursor क्रम bno btree */
	xfs_btree_cur_t	*cnt_cur;	/* cursor क्रम cnt btree */
	पूर्णांक		error;		/* error result */
	xfs_agblock_t	fbno;		/* start of found मुक्तspace */
	xfs_extlen_t	flen;		/* length of found मुक्तspace */
	पूर्णांक		i;		/* temp status variable */
	xfs_agblock_t	rbno;		/* वापसed block number */
	xfs_extlen_t	rlen;		/* length of वापसed extent */
	bool		busy;
	अचिन्हित	busy_gen;

restart:
	/*
	 * Allocate and initialize a cursor क्रम the by-size btree.
	 */
	cnt_cur = xfs_allocbt_init_cursor(args->mp, args->tp, args->agbp,
		args->agno, XFS_BTNUM_CNT);
	bno_cur = शून्य;
	busy = false;

	/*
	 * Look क्रम an entry >= maxlen+alignment-1 blocks.
	 */
	अगर ((error = xfs_alloc_lookup_ge(cnt_cur, 0,
			args->maxlen + args->alignment - 1, &i)))
		जाओ error0;

	/*
	 * If none then we have to settle क्रम a smaller extent. In the हाल that
	 * there are no large extents, this will वापस the last entry in the
	 * tree unless the tree is empty. In the हाल that there are only busy
	 * large extents, this will वापस the largest small extent unless there
	 * are no smaller extents available.
	 */
	अगर (!i) अणु
		error = xfs_alloc_ag_vextent_small(args, cnt_cur,
						   &fbno, &flen, &i);
		अगर (error)
			जाओ error0;
		अगर (i == 0 || flen == 0) अणु
			xfs_btree_del_cursor(cnt_cur, XFS_BTREE_NOERROR);
			trace_xfs_alloc_size_noentry(args);
			वापस 0;
		पूर्ण
		ASSERT(i == 1);
		busy = xfs_alloc_compute_aligned(args, fbno, flen, &rbno,
				&rlen, &busy_gen);
	पूर्ण अन्यथा अणु
		/*
		 * Search क्रम a non-busy extent that is large enough.
		 */
		क्रम (;;) अणु
			error = xfs_alloc_get_rec(cnt_cur, &fbno, &flen, &i);
			अगर (error)
				जाओ error0;
			अगर (XFS_IS_CORRUPT(args->mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ error0;
			पूर्ण

			busy = xfs_alloc_compute_aligned(args, fbno, flen,
					&rbno, &rlen, &busy_gen);

			अगर (rlen >= args->maxlen)
				अवरोध;

			error = xfs_btree_increment(cnt_cur, 0, &i);
			अगर (error)
				जाओ error0;
			अगर (i == 0) अणु
				/*
				 * Our only valid extents must have been busy.
				 * Make it unbusy by क्रमcing the log out and
				 * retrying.
				 */
				xfs_btree_del_cursor(cnt_cur,
						     XFS_BTREE_NOERROR);
				trace_xfs_alloc_size_busy(args);
				xfs_extent_busy_flush(args->mp,
							args->pag, busy_gen);
				जाओ restart;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * In the first हाल above, we got the last entry in the
	 * by-size btree.  Now we check to see अगर the space hits maxlen
	 * once aligned; अगर not, we search left क्रम something better.
	 * This can't happen in the second हाल above.
	 */
	rlen = XFS_EXTLEN_MIN(args->maxlen, rlen);
	अगर (XFS_IS_CORRUPT(args->mp,
			   rlen != 0 &&
			   (rlen > flen ||
			    rbno + rlen > fbno + flen))) अणु
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण
	अगर (rlen < args->maxlen) अणु
		xfs_agblock_t	bestfbno;
		xfs_extlen_t	bestflen;
		xfs_agblock_t	bestrbno;
		xfs_extlen_t	beम_माप;

		beम_माप = rlen;
		bestrbno = rbno;
		bestflen = flen;
		bestfbno = fbno;
		क्रम (;;) अणु
			अगर ((error = xfs_btree_decrement(cnt_cur, 0, &i)))
				जाओ error0;
			अगर (i == 0)
				अवरोध;
			अगर ((error = xfs_alloc_get_rec(cnt_cur, &fbno, &flen,
					&i)))
				जाओ error0;
			अगर (XFS_IS_CORRUPT(args->mp, i != 1)) अणु
				error = -EFSCORRUPTED;
				जाओ error0;
			पूर्ण
			अगर (flen < beम_माप)
				अवरोध;
			busy = xfs_alloc_compute_aligned(args, fbno, flen,
					&rbno, &rlen, &busy_gen);
			rlen = XFS_EXTLEN_MIN(args->maxlen, rlen);
			अगर (XFS_IS_CORRUPT(args->mp,
					   rlen != 0 &&
					   (rlen > flen ||
					    rbno + rlen > fbno + flen))) अणु
				error = -EFSCORRUPTED;
				जाओ error0;
			पूर्ण
			अगर (rlen > beम_माप) अणु
				beम_माप = rlen;
				bestrbno = rbno;
				bestflen = flen;
				bestfbno = fbno;
				अगर (rlen == args->maxlen)
					अवरोध;
			पूर्ण
		पूर्ण
		अगर ((error = xfs_alloc_lookup_eq(cnt_cur, bestfbno, bestflen,
				&i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(args->mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		rlen = beम_माप;
		rbno = bestrbno;
		flen = bestflen;
		fbno = bestfbno;
	पूर्ण
	args->wasfromfl = 0;
	/*
	 * Fix up the length.
	 */
	args->len = rlen;
	अगर (rlen < args->minlen) अणु
		अगर (busy) अणु
			xfs_btree_del_cursor(cnt_cur, XFS_BTREE_NOERROR);
			trace_xfs_alloc_size_busy(args);
			xfs_extent_busy_flush(args->mp, args->pag, busy_gen);
			जाओ restart;
		पूर्ण
		जाओ out_nominleft;
	पूर्ण
	xfs_alloc_fix_len(args);

	rlen = args->len;
	अगर (XFS_IS_CORRUPT(args->mp, rlen > flen)) अणु
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण
	/*
	 * Allocate and initialize a cursor क्रम the by-block tree.
	 */
	bno_cur = xfs_allocbt_init_cursor(args->mp, args->tp, args->agbp,
		args->agno, XFS_BTNUM_BNO);
	अगर ((error = xfs_alloc_fixup_trees(cnt_cur, bno_cur, fbno, flen,
			rbno, rlen, XFSA_FIXUP_CNT_OK)))
		जाओ error0;
	xfs_btree_del_cursor(cnt_cur, XFS_BTREE_NOERROR);
	xfs_btree_del_cursor(bno_cur, XFS_BTREE_NOERROR);
	cnt_cur = bno_cur = शून्य;
	args->len = rlen;
	args->agbno = rbno;
	अगर (XFS_IS_CORRUPT(args->mp,
			   args->agbno + args->len >
			   be32_to_cpu(agf->agf_length))) अणु
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण
	trace_xfs_alloc_size_करोne(args);
	वापस 0;

error0:
	trace_xfs_alloc_size_error(args);
	अगर (cnt_cur)
		xfs_btree_del_cursor(cnt_cur, XFS_BTREE_ERROR);
	अगर (bno_cur)
		xfs_btree_del_cursor(bno_cur, XFS_BTREE_ERROR);
	वापस error;

out_nominleft:
	xfs_btree_del_cursor(cnt_cur, XFS_BTREE_NOERROR);
	trace_xfs_alloc_size_nominleft(args);
	args->agbno = शून्यAGBLOCK;
	वापस 0;
पूर्ण

/*
 * Free the extent starting at agno/bno क्रम length.
 */
STATIC पूर्णांक
xfs_मुक्त_ag_extent(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_buf			*agbp,
	xfs_agnumber_t			agno,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	क्रमागत xfs_ag_resv_type		type)
अणु
	काष्ठा xfs_mount		*mp;
	काष्ठा xfs_btree_cur		*bno_cur;
	काष्ठा xfs_btree_cur		*cnt_cur;
	xfs_agblock_t			gtbno; /* start of right neighbor */
	xfs_extlen_t			gtlen; /* length of right neighbor */
	xfs_agblock_t			ltbno; /* start of left neighbor */
	xfs_extlen_t			ltlen; /* length of left neighbor */
	xfs_agblock_t			nbno; /* new starting block of मुक्तsp */
	xfs_extlen_t			nlen; /* new length of मुक्तspace */
	पूर्णांक				haveleft; /* have a left neighbor */
	पूर्णांक				haveright; /* have a right neighbor */
	पूर्णांक				i;
	पूर्णांक				error;

	bno_cur = cnt_cur = शून्य;
	mp = tp->t_mountp;

	अगर (!xfs_rmap_should_skip_owner_update(oinfo)) अणु
		error = xfs_rmap_मुक्त(tp, agbp, agno, bno, len, oinfo);
		अगर (error)
			जाओ error0;
	पूर्ण

	/*
	 * Allocate and initialize a cursor क्रम the by-block btree.
	 */
	bno_cur = xfs_allocbt_init_cursor(mp, tp, agbp, agno, XFS_BTNUM_BNO);
	/*
	 * Look क्रम a neighboring block on the left (lower block numbers)
	 * that is contiguous with this space.
	 */
	अगर ((error = xfs_alloc_lookup_le(bno_cur, bno, len, &haveleft)))
		जाओ error0;
	अगर (haveleft) अणु
		/*
		 * There is a block to our left.
		 */
		अगर ((error = xfs_alloc_get_rec(bno_cur, &ltbno, &ltlen, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		/*
		 * It's not contiguous, though.
		 */
		अगर (ltbno + ltlen < bno)
			haveleft = 0;
		अन्यथा अणु
			/*
			 * If this failure happens the request to मुक्त this
			 * space was invalid, it's (partly) alपढ़ोy मुक्त.
			 * Very bad.
			 */
			अगर (XFS_IS_CORRUPT(mp, ltbno + ltlen > bno)) अणु
				error = -EFSCORRUPTED;
				जाओ error0;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * Look क्रम a neighboring block on the right (higher block numbers)
	 * that is contiguous with this space.
	 */
	अगर ((error = xfs_btree_increment(bno_cur, 0, &haveright)))
		जाओ error0;
	अगर (haveright) अणु
		/*
		 * There is a block to our right.
		 */
		अगर ((error = xfs_alloc_get_rec(bno_cur, &gtbno, &gtlen, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		/*
		 * It's not contiguous, though.
		 */
		अगर (bno + len < gtbno)
			haveright = 0;
		अन्यथा अणु
			/*
			 * If this failure happens the request to मुक्त this
			 * space was invalid, it's (partly) alपढ़ोy मुक्त.
			 * Very bad.
			 */
			अगर (XFS_IS_CORRUPT(mp, bno + len > gtbno)) अणु
				error = -EFSCORRUPTED;
				जाओ error0;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * Now allocate and initialize a cursor क्रम the by-size tree.
	 */
	cnt_cur = xfs_allocbt_init_cursor(mp, tp, agbp, agno, XFS_BTNUM_CNT);
	/*
	 * Have both left and right contiguous neighbors.
	 * Merge all three पूर्णांकo a single मुक्त block.
	 */
	अगर (haveleft && haveright) अणु
		/*
		 * Delete the old by-size entry on the left.
		 */
		अगर ((error = xfs_alloc_lookup_eq(cnt_cur, ltbno, ltlen, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		अगर ((error = xfs_btree_delete(cnt_cur, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		/*
		 * Delete the old by-size entry on the right.
		 */
		अगर ((error = xfs_alloc_lookup_eq(cnt_cur, gtbno, gtlen, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		अगर ((error = xfs_btree_delete(cnt_cur, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		/*
		 * Delete the old by-block entry क्रम the right block.
		 */
		अगर ((error = xfs_btree_delete(bno_cur, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		/*
		 * Move the by-block cursor back to the left neighbor.
		 */
		अगर ((error = xfs_btree_decrement(bno_cur, 0, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
#अगर_घोषित DEBUG
		/*
		 * Check that this is the right record: delete didn't
		 * mangle the cursor.
		 */
		अणु
			xfs_agblock_t	xxbno;
			xfs_extlen_t	xxlen;

			अगर ((error = xfs_alloc_get_rec(bno_cur, &xxbno, &xxlen,
					&i)))
				जाओ error0;
			अगर (XFS_IS_CORRUPT(mp,
					   i != 1 ||
					   xxbno != ltbno ||
					   xxlen != ltlen)) अणु
				error = -EFSCORRUPTED;
				जाओ error0;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		/*
		 * Update reमुख्यing by-block entry to the new, joined block.
		 */
		nbno = ltbno;
		nlen = len + ltlen + gtlen;
		अगर ((error = xfs_alloc_update(bno_cur, nbno, nlen)))
			जाओ error0;
	पूर्ण
	/*
	 * Have only a left contiguous neighbor.
	 * Merge it together with the new मुक्तspace.
	 */
	अन्यथा अगर (haveleft) अणु
		/*
		 * Delete the old by-size entry on the left.
		 */
		अगर ((error = xfs_alloc_lookup_eq(cnt_cur, ltbno, ltlen, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		अगर ((error = xfs_btree_delete(cnt_cur, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		/*
		 * Back up the by-block cursor to the left neighbor, and
		 * update its length.
		 */
		अगर ((error = xfs_btree_decrement(bno_cur, 0, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		nbno = ltbno;
		nlen = len + ltlen;
		अगर ((error = xfs_alloc_update(bno_cur, nbno, nlen)))
			जाओ error0;
	पूर्ण
	/*
	 * Have only a right contiguous neighbor.
	 * Merge it together with the new मुक्तspace.
	 */
	अन्यथा अगर (haveright) अणु
		/*
		 * Delete the old by-size entry on the right.
		 */
		अगर ((error = xfs_alloc_lookup_eq(cnt_cur, gtbno, gtlen, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		अगर ((error = xfs_btree_delete(cnt_cur, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		/*
		 * Update the starting block and length of the right
		 * neighbor in the by-block tree.
		 */
		nbno = bno;
		nlen = len + gtlen;
		अगर ((error = xfs_alloc_update(bno_cur, nbno, nlen)))
			जाओ error0;
	पूर्ण
	/*
	 * No contiguous neighbors.
	 * Insert the new मुक्तspace पूर्णांकo the by-block tree.
	 */
	अन्यथा अणु
		nbno = bno;
		nlen = len;
		अगर ((error = xfs_btree_insert(bno_cur, &i)))
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
	पूर्ण
	xfs_btree_del_cursor(bno_cur, XFS_BTREE_NOERROR);
	bno_cur = शून्य;
	/*
	 * In all हालs we need to insert the new मुक्तspace in the by-size tree.
	 */
	अगर ((error = xfs_alloc_lookup_eq(cnt_cur, nbno, nlen, &i)))
		जाओ error0;
	अगर (XFS_IS_CORRUPT(mp, i != 0)) अणु
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण
	अगर ((error = xfs_btree_insert(cnt_cur, &i)))
		जाओ error0;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण
	xfs_btree_del_cursor(cnt_cur, XFS_BTREE_NOERROR);
	cnt_cur = शून्य;

	/*
	 * Update the मुक्तspace totals in the ag and superblock.
	 */
	error = xfs_alloc_update_counters(tp, agbp, len);
	xfs_ag_resv_मुक्त_extent(agbp->b_pag, type, tp, len);
	अगर (error)
		जाओ error0;

	XFS_STATS_INC(mp, xs_मुक्तx);
	XFS_STATS_ADD(mp, xs_मुक्तb, len);

	trace_xfs_मुक्त_extent(mp, agno, bno, len, type, haveleft, haveright);

	वापस 0;

 error0:
	trace_xfs_मुक्त_extent(mp, agno, bno, len, type, -1, -1);
	अगर (bno_cur)
		xfs_btree_del_cursor(bno_cur, XFS_BTREE_ERROR);
	अगर (cnt_cur)
		xfs_btree_del_cursor(cnt_cur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/*
 * Visible (exported) allocation/मुक्त functions.
 * Some of these are used just by xfs_alloc_btree.c and this file.
 */

/*
 * Compute and fill in value of m_ag_maxlevels.
 */
व्योम
xfs_alloc_compute_maxlevels(
	xfs_mount_t	*mp)	/* file प्रणाली mount काष्ठाure */
अणु
	mp->m_ag_maxlevels = xfs_btree_compute_maxlevels(mp->m_alloc_mnr,
			(mp->m_sb.sb_agblocks + 1) / 2);
पूर्ण

/*
 * Find the length of the दीर्घest extent in an AG.  The 'need' parameter
 * specअगरies how much space we're going to need क्रम the AGFL and the
 * 'reserved' parameter tells us how many blocks in this AG are reserved क्रम
 * other callers.
 */
xfs_extlen_t
xfs_alloc_दीर्घest_मुक्त_extent(
	काष्ठा xfs_perag	*pag,
	xfs_extlen_t		need,
	xfs_extlen_t		reserved)
अणु
	xfs_extlen_t		delta = 0;

	/*
	 * If the AGFL needs a reअक्षरge, we'll have to subtract that from the
	 * दीर्घest extent.
	 */
	अगर (need > pag->pagf_flcount)
		delta = need - pag->pagf_flcount;

	/*
	 * If we cannot मुख्यtain others' reservations with space from the
	 * not-दीर्घest मुक्तsp extents, we'll have to subtract /that/ from
	 * the दीर्घest extent too.
	 */
	अगर (pag->pagf_मुक्तblks - pag->pagf_दीर्घest < reserved)
		delta += reserved - (pag->pagf_मुक्तblks - pag->pagf_दीर्घest);

	/*
	 * If the दीर्घest extent is दीर्घ enough to satisfy all the
	 * reservations and AGFL rules in place, we can वापस this extent.
	 */
	अगर (pag->pagf_दीर्घest > delta)
		वापस min_t(xfs_extlen_t, pag->pag_mount->m_ag_max_usable,
				pag->pagf_दीर्घest - delta);

	/* Otherwise, let the caller try क्रम 1 block अगर there's space. */
	वापस pag->pagf_flcount > 0 || pag->pagf_दीर्घest > 0;
पूर्ण

/*
 * Compute the minimum length of the AGFL in the given AG.  If @pag is शून्य,
 * वापस the largest possible minimum length.
 */
अचिन्हित पूर्णांक
xfs_alloc_min_मुक्तlist(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_perag	*pag)
अणु
	/* AG btrees have at least 1 level. */
	अटल स्थिर uपूर्णांक8_t	fake_levels[XFS_BTNUM_AGF] = अणु1, 1, 1पूर्ण;
	स्थिर uपूर्णांक8_t		*levels = pag ? pag->pagf_levels : fake_levels;
	अचिन्हित पूर्णांक		min_मुक्त;

	ASSERT(mp->m_ag_maxlevels > 0);

	/* space needed by-bno मुक्तspace btree */
	min_मुक्त = min_t(अचिन्हित पूर्णांक, levels[XFS_BTNUM_BNOi] + 1,
				       mp->m_ag_maxlevels);
	/* space needed by-size मुक्तspace btree */
	min_मुक्त += min_t(अचिन्हित पूर्णांक, levels[XFS_BTNUM_CNTi] + 1,
				       mp->m_ag_maxlevels);
	/* space needed reverse mapping used space btree */
	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb))
		min_मुक्त += min_t(अचिन्हित पूर्णांक, levels[XFS_BTNUM_RMAPi] + 1,
						mp->m_rmap_maxlevels);

	वापस min_मुक्त;
पूर्ण

/*
 * Check अगर the operation we are fixing up the मुक्तlist क्रम should go ahead or
 * not. If we are मुक्तing blocks, we always allow it, otherwise the allocation
 * is dependent on whether the size and shape of मुक्त space available will
 * permit the requested allocation to take place.
 */
अटल bool
xfs_alloc_space_available(
	काष्ठा xfs_alloc_arg	*args,
	xfs_extlen_t		min_मुक्त,
	पूर्णांक			flags)
अणु
	काष्ठा xfs_perag	*pag = args->pag;
	xfs_extlen_t		alloc_len, दीर्घest;
	xfs_extlen_t		reservation; /* blocks that are still reserved */
	पूर्णांक			available;
	xfs_extlen_t		agflcount;

	अगर (flags & XFS_ALLOC_FLAG_FREEING)
		वापस true;

	reservation = xfs_ag_resv_needed(pag, args->resv);

	/* करो we have enough contiguous मुक्त space क्रम the allocation? */
	alloc_len = args->minlen + (args->alignment - 1) + args->minalignslop;
	दीर्घest = xfs_alloc_दीर्घest_मुक्त_extent(pag, min_मुक्त, reservation);
	अगर (दीर्घest < alloc_len)
		वापस false;

	/*
	 * Do we have enough मुक्त space reमुख्यing क्रम the allocation? Don't
	 * account extra agfl blocks because we are about to defer मुक्त them,
	 * making them unavailable until the current transaction commits.
	 */
	agflcount = min_t(xfs_extlen_t, pag->pagf_flcount, min_मुक्त);
	available = (पूर्णांक)(pag->pagf_मुक्तblks + agflcount -
			  reservation - min_मुक्त - args->minleft);
	अगर (available < (पूर्णांक)max(args->total, alloc_len))
		वापस false;

	/*
	 * Clamp maxlen to the amount of मुक्त space available क्रम the actual
	 * extent allocation.
	 */
	अगर (available < (पूर्णांक)args->maxlen && !(flags & XFS_ALLOC_FLAG_CHECK)) अणु
		args->maxlen = available;
		ASSERT(args->maxlen > 0);
		ASSERT(args->maxlen >= args->minlen);
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक
xfs_मुक्त_agfl_block(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		agbno,
	काष्ठा xfs_buf		*agbp,
	काष्ठा xfs_owner_info	*oinfo)
अणु
	पूर्णांक			error;
	काष्ठा xfs_buf		*bp;

	error = xfs_मुक्त_ag_extent(tp, agbp, agno, agbno, 1, oinfo,
				   XFS_AG_RESV_AGFL);
	अगर (error)
		वापस error;

	error = xfs_trans_get_buf(tp, tp->t_mountp->m_ddev_targp,
			XFS_AGB_TO_DADDR(tp->t_mountp, agno, agbno),
			tp->t_mountp->m_bsize, 0, &bp);
	अगर (error)
		वापस error;
	xfs_trans_binval(tp, bp);

	वापस 0;
पूर्ण

/*
 * Check the agfl fields of the agf क्रम inconsistency or corruption. The purpose
 * is to detect an agfl header padding mismatch between current and early v5
 * kernels. This problem manअगरests as a 1-slot size dअगरference between the
 * on-disk flcount and the active [first, last] range of a wrapped agfl. This
 * may also catch variants of agfl count corruption unrelated to padding. Either
 * way, we'll reset the agfl and warn the user.
 *
 * Return true अगर a reset is required beक्रमe the agfl can be used, false
 * otherwise.
 */
अटल bool
xfs_agfl_needs_reset(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_agf		*agf)
अणु
	uपूर्णांक32_t		f = be32_to_cpu(agf->agf_flfirst);
	uपूर्णांक32_t		l = be32_to_cpu(agf->agf_fllast);
	uपूर्णांक32_t		c = be32_to_cpu(agf->agf_flcount);
	पूर्णांक			agfl_size = xfs_agfl_size(mp);
	पूर्णांक			active;

	/* no agfl header on v4 supers */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस false;

	/*
	 * The agf पढ़ो verअगरier catches severe corruption of these fields.
	 * Repeat some sanity checks to cover a packed -> unpacked mismatch अगर
	 * the verअगरier allows it.
	 */
	अगर (f >= agfl_size || l >= agfl_size)
		वापस true;
	अगर (c > agfl_size)
		वापस true;

	/*
	 * Check consistency between the on-disk count and the active range. An
	 * agfl padding mismatch manअगरests as an inconsistent flcount.
	 */
	अगर (c && l >= f)
		active = l - f + 1;
	अन्यथा अगर (c)
		active = agfl_size - f + l + 1;
	अन्यथा
		active = 0;

	वापस active != c;
पूर्ण

/*
 * Reset the agfl to an empty state. Ignore/drop any existing blocks since the
 * agfl content cannot be trusted. Warn the user that a repair is required to
 * recover leaked blocks.
 *
 * The purpose of this mechanism is to handle fileप्रणालीs affected by the agfl
 * header padding mismatch problem. A reset keeps the fileप्रणाली online with a
 * relatively minor मुक्त space accounting inconsistency rather than suffer the
 * inevitable crash from use of an invalid agfl block.
 */
अटल व्योम
xfs_agfl_reset(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp,
	काष्ठा xfs_perag	*pag)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_agf		*agf = agbp->b_addr;

	ASSERT(pag->pagf_agflreset);
	trace_xfs_agfl_reset(mp, agf, 0, _RET_IP_);

	xfs_warn(mp,
	       "WARNING: Reset corrupted AGFL on AG %u. %d blocks leaked. "
	       "Please unmount and run xfs_repair.",
	         pag->pag_agno, pag->pagf_flcount);

	agf->agf_flfirst = 0;
	agf->agf_fllast = cpu_to_be32(xfs_agfl_size(mp) - 1);
	agf->agf_flcount = 0;
	xfs_alloc_log_agf(tp, agbp, XFS_AGF_FLFIRST | XFS_AGF_FLLAST |
				    XFS_AGF_FLCOUNT);

	pag->pagf_flcount = 0;
	pag->pagf_agflreset = false;
पूर्ण

/*
 * Defer an AGFL block मुक्त. This is effectively equivalent to
 * xfs_bmap_add_मुक्त() with some special handling particular to AGFL blocks.
 *
 * Deferring AGFL मुक्तs helps prevent log reservation overruns due to too many
 * allocation operations in a transaction. AGFL मुक्तs are prone to this problem
 * because क्रम one they are always मुक्तd one at a समय. Further, an immediate
 * AGFL block मुक्त can cause a btree join and require another block मुक्त beक्रमe
 * the real allocation can proceed. Deferring the मुक्त disconnects मुक्तing up
 * the AGFL slot from मुक्तing the block.
 */
STATIC व्योम
xfs_defer_agfl_block(
	काष्ठा xfs_trans		*tp,
	xfs_agnumber_t			agno,
	xfs_fsblock_t			agbno,
	काष्ठा xfs_owner_info		*oinfo)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_extent_मुक्त_item	*new;		/* new element */

	ASSERT(xfs_bmap_मुक्त_item_zone != शून्य);
	ASSERT(oinfo != शून्य);

	new = kmem_cache_alloc(xfs_bmap_मुक्त_item_zone,
			       GFP_KERNEL | __GFP_NOFAIL);
	new->xefi_startblock = XFS_AGB_TO_FSB(mp, agno, agbno);
	new->xefi_blockcount = 1;
	new->xefi_oinfo = *oinfo;
	new->xefi_skip_discard = false;

	trace_xfs_agfl_मुक्त_defer(mp, agno, 0, agbno, 1);

	xfs_defer_add(tp, XFS_DEFER_OPS_TYPE_AGFL_FREE, &new->xefi_list);
पूर्ण

#अगर_घोषित DEBUG
/*
 * Check अगर an AGF has a मुक्त extent record whose length is equal to
 * args->minlen.
 */
STATIC पूर्णांक
xfs_exact_minlen_extent_available(
	काष्ठा xfs_alloc_arg	*args,
	काष्ठा xfs_buf		*agbp,
	पूर्णांक			*stat)
अणु
	काष्ठा xfs_btree_cur	*cnt_cur;
	xfs_agblock_t		fbno;
	xfs_extlen_t		flen;
	पूर्णांक			error = 0;

	cnt_cur = xfs_allocbt_init_cursor(args->mp, args->tp, agbp,
			args->agno, XFS_BTNUM_CNT);
	error = xfs_alloc_lookup_ge(cnt_cur, 0, args->minlen, stat);
	अगर (error)
		जाओ out;

	अगर (*stat == 0) अणु
		error = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	error = xfs_alloc_get_rec(cnt_cur, &fbno, &flen, stat);
	अगर (error)
		जाओ out;

	अगर (*stat == 1 && flen != args->minlen)
		*stat = 0;

out:
	xfs_btree_del_cursor(cnt_cur, error);

	वापस error;
पूर्ण
#पूर्ण_अगर

/*
 * Decide whether to use this allocation group क्रम this allocation.
 * If so, fix up the btree मुक्तlist's size.
 */
पूर्णांक			/* error */
xfs_alloc_fix_मुक्तlist(
	काष्ठा xfs_alloc_arg	*args,	/* allocation argument काष्ठाure */
	पूर्णांक			flags)	/* XFS_ALLOC_FLAG_... */
अणु
	काष्ठा xfs_mount	*mp = args->mp;
	काष्ठा xfs_perag	*pag = args->pag;
	काष्ठा xfs_trans	*tp = args->tp;
	काष्ठा xfs_buf		*agbp = शून्य;
	काष्ठा xfs_buf		*agflbp = शून्य;
	काष्ठा xfs_alloc_arg	targs;	/* local allocation arguments */
	xfs_agblock_t		bno;	/* मुक्तlist block */
	xfs_extlen_t		need;	/* total blocks needed in मुक्तlist */
	पूर्णांक			error = 0;

	/* deferred ops (AGFL block मुक्तs) require permanent transactions */
	ASSERT(tp->t_flags & XFS_TRANS_PERM_LOG_RES);

	अगर (!pag->pagf_init) अणु
		error = xfs_alloc_पढ़ो_agf(mp, tp, args->agno, flags, &agbp);
		अगर (error) अणु
			/* Couldn't lock the AGF so skip this AG. */
			अगर (error == -EAGAIN)
				error = 0;
			जाओ out_no_agbp;
		पूर्ण
	पूर्ण

	/*
	 * If this is a metadata preferred pag and we are user data then try
	 * somewhere अन्यथा अगर we are not being asked to try harder at this
	 * poपूर्णांक
	 */
	अगर (pag->pagf_metadata && (args->datatype & XFS_ALLOC_USERDATA) &&
	    (flags & XFS_ALLOC_FLAG_TRYLOCK)) अणु
		ASSERT(!(flags & XFS_ALLOC_FLAG_FREEING));
		जाओ out_agbp_rअन्यथा;
	पूर्ण

	need = xfs_alloc_min_मुक्तlist(mp, pag);
	अगर (!xfs_alloc_space_available(args, need, flags |
			XFS_ALLOC_FLAG_CHECK))
		जाओ out_agbp_rअन्यथा;

	/*
	 * Get the a.g. मुक्तspace buffer.
	 * Can fail अगर we're not blocking on locks, and it's held.
	 */
	अगर (!agbp) अणु
		error = xfs_alloc_पढ़ो_agf(mp, tp, args->agno, flags, &agbp);
		अगर (error) अणु
			/* Couldn't lock the AGF so skip this AG. */
			अगर (error == -EAGAIN)
				error = 0;
			जाओ out_no_agbp;
		पूर्ण
	पूर्ण

	/* reset a padding mismatched agfl beक्रमe final मुक्त space check */
	अगर (pag->pagf_agflreset)
		xfs_agfl_reset(tp, agbp, pag);

	/* If there isn't enough total space or single-extent, reject it. */
	need = xfs_alloc_min_मुक्तlist(mp, pag);
	अगर (!xfs_alloc_space_available(args, need, flags))
		जाओ out_agbp_rअन्यथा;

#अगर_घोषित DEBUG
	अगर (args->alloc_minlen_only) अणु
		पूर्णांक stat;

		error = xfs_exact_minlen_extent_available(args, agbp, &stat);
		अगर (error || !stat)
			जाओ out_agbp_rअन्यथा;
	पूर्ण
#पूर्ण_अगर
	/*
	 * Make the मुक्तlist लघुer अगर it's too दीर्घ.
	 *
	 * Note that from this poपूर्णांक onwards, we will always release the agf and
	 * agfl buffers on error. This handles the हाल where we error out and
	 * the buffers are clean or may not have been joined to the transaction
	 * and hence need to be released manually. If they have been joined to
	 * the transaction, then xfs_trans_brअन्यथा() will handle them
	 * appropriately based on the recursion count and dirty state of the
	 * buffer.
	 *
	 * XXX (dgc): When we have lots of मुक्त space, करोes this buy us
	 * anything other than extra overhead when we need to put more blocks
	 * back on the मुक्त list? Maybe we should only करो this when space is
	 * getting low or the AGFL is more than half full?
	 *
	 * The NOSHRINK flag prevents the AGFL from being shrunk अगर it's too
	 * big; the NORMAP flag prevents AGFL expand/shrink operations from
	 * updating the rmapbt.  Both flags are used in xfs_repair जबतक we're
	 * rebuilding the rmapbt, and neither are used by the kernel.  They're
	 * both required to ensure that rmaps are correctly recorded क्रम the
	 * regenerated AGFL, bnobt, and cntbt.  See repair/phase5.c and
	 * repair/rmap.c in xfsprogs क्रम details.
	 */
	स_रखो(&targs, 0, माप(targs));
	/* काष्ठा copy below */
	अगर (flags & XFS_ALLOC_FLAG_NORMAP)
		targs.oinfo = XFS_RMAP_OINFO_SKIP_UPDATE;
	अन्यथा
		targs.oinfo = XFS_RMAP_OINFO_AG;
	जबतक (!(flags & XFS_ALLOC_FLAG_NOSHRINK) && pag->pagf_flcount > need) अणु
		error = xfs_alloc_get_मुक्तlist(tp, agbp, &bno, 0);
		अगर (error)
			जाओ out_agbp_rअन्यथा;

		/* defer agfl मुक्तs */
		xfs_defer_agfl_block(tp, args->agno, bno, &targs.oinfo);
	पूर्ण

	targs.tp = tp;
	targs.mp = mp;
	targs.agbp = agbp;
	targs.agno = args->agno;
	targs.alignment = targs.minlen = targs.prod = 1;
	targs.type = XFS_ALLOCTYPE_THIS_AG;
	targs.pag = pag;
	error = xfs_alloc_पढ़ो_agfl(mp, tp, targs.agno, &agflbp);
	अगर (error)
		जाओ out_agbp_rअन्यथा;

	/* Make the मुक्तlist दीर्घer अगर it's too लघु. */
	जबतक (pag->pagf_flcount < need) अणु
		targs.agbno = 0;
		targs.maxlen = need - pag->pagf_flcount;
		targs.resv = XFS_AG_RESV_AGFL;

		/* Allocate as many blocks as possible at once. */
		error = xfs_alloc_ag_vextent(&targs);
		अगर (error)
			जाओ out_agflbp_rअन्यथा;

		/*
		 * Stop अगर we run out.  Won't happen अगर callers are obeying
		 * the restrictions correctly.  Can happen क्रम मुक्त calls
		 * on a completely full ag.
		 */
		अगर (targs.agbno == शून्यAGBLOCK) अणु
			अगर (flags & XFS_ALLOC_FLAG_FREEING)
				अवरोध;
			जाओ out_agflbp_rअन्यथा;
		पूर्ण
		/*
		 * Put each allocated block on the list.
		 */
		क्रम (bno = targs.agbno; bno < targs.agbno + targs.len; bno++) अणु
			error = xfs_alloc_put_मुक्तlist(tp, agbp,
							agflbp, bno, 0);
			अगर (error)
				जाओ out_agflbp_rअन्यथा;
		पूर्ण
	पूर्ण
	xfs_trans_brअन्यथा(tp, agflbp);
	args->agbp = agbp;
	वापस 0;

out_agflbp_rअन्यथा:
	xfs_trans_brअन्यथा(tp, agflbp);
out_agbp_rअन्यथा:
	अगर (agbp)
		xfs_trans_brअन्यथा(tp, agbp);
out_no_agbp:
	args->agbp = शून्य;
	वापस error;
पूर्ण

/*
 * Get a block from the मुक्तlist.
 * Returns with the buffer क्रम the block gotten.
 */
पूर्णांक				/* error */
xfs_alloc_get_मुक्तlist(
	xfs_trans_t	*tp,	/* transaction poपूर्णांकer */
	काष्ठा xfs_buf	*agbp,	/* buffer containing the agf काष्ठाure */
	xfs_agblock_t	*bnop,	/* block address retrieved from मुक्तlist */
	पूर्णांक		btreeblk) /* destination is a AGF btree */
अणु
	काष्ठा xfs_agf	*agf = agbp->b_addr;
	काष्ठा xfs_buf	*agflbp;/* buffer क्रम a.g. मुक्तlist काष्ठाure */
	xfs_agblock_t	bno;	/* block number वापसed */
	__be32		*agfl_bno;
	पूर्णांक		error;
	पूर्णांक		logflags;
	xfs_mount_t	*mp = tp->t_mountp;
	xfs_perag_t	*pag;	/* per allocation group data */

	/*
	 * Freelist is empty, give up.
	 */
	अगर (!agf->agf_flcount) अणु
		*bnop = शून्यAGBLOCK;
		वापस 0;
	पूर्ण
	/*
	 * Read the array of मुक्त blocks.
	 */
	error = xfs_alloc_पढ़ो_agfl(mp, tp, be32_to_cpu(agf->agf_seqno),
				    &agflbp);
	अगर (error)
		वापस error;


	/*
	 * Get the block number and update the data काष्ठाures.
	 */
	agfl_bno = xfs_buf_to_agfl_bno(agflbp);
	bno = be32_to_cpu(agfl_bno[be32_to_cpu(agf->agf_flfirst)]);
	be32_add_cpu(&agf->agf_flfirst, 1);
	xfs_trans_brअन्यथा(tp, agflbp);
	अगर (be32_to_cpu(agf->agf_flfirst) == xfs_agfl_size(mp))
		agf->agf_flfirst = 0;

	pag = agbp->b_pag;
	ASSERT(!pag->pagf_agflreset);
	be32_add_cpu(&agf->agf_flcount, -1);
	pag->pagf_flcount--;

	logflags = XFS_AGF_FLFIRST | XFS_AGF_FLCOUNT;
	अगर (btreeblk) अणु
		be32_add_cpu(&agf->agf_btreeblks, 1);
		pag->pagf_btreeblks++;
		logflags |= XFS_AGF_BTREEBLKS;
	पूर्ण

	xfs_alloc_log_agf(tp, agbp, logflags);
	*bnop = bno;

	वापस 0;
पूर्ण

/*
 * Log the given fields from the agf काष्ठाure.
 */
व्योम
xfs_alloc_log_agf(
	xfs_trans_t	*tp,	/* transaction poपूर्णांकer */
	काष्ठा xfs_buf	*bp,	/* buffer क्रम a.g. मुक्तlist header */
	पूर्णांक		fields)	/* mask of fields to be logged (XFS_AGF_...) */
अणु
	पूर्णांक	first;		/* first byte offset */
	पूर्णांक	last;		/* last byte offset */
	अटल स्थिर लघु	offsets[] = अणु
		दुरत्व(xfs_agf_t, agf_magicnum),
		दुरत्व(xfs_agf_t, agf_versionnum),
		दुरत्व(xfs_agf_t, agf_seqno),
		दुरत्व(xfs_agf_t, agf_length),
		दुरत्व(xfs_agf_t, agf_roots[0]),
		दुरत्व(xfs_agf_t, agf_levels[0]),
		दुरत्व(xfs_agf_t, agf_flfirst),
		दुरत्व(xfs_agf_t, agf_fllast),
		दुरत्व(xfs_agf_t, agf_flcount),
		दुरत्व(xfs_agf_t, agf_मुक्तblks),
		दुरत्व(xfs_agf_t, agf_दीर्घest),
		दुरत्व(xfs_agf_t, agf_btreeblks),
		दुरत्व(xfs_agf_t, agf_uuid),
		दुरत्व(xfs_agf_t, agf_rmap_blocks),
		दुरत्व(xfs_agf_t, agf_refcount_blocks),
		दुरत्व(xfs_agf_t, agf_refcount_root),
		दुरत्व(xfs_agf_t, agf_refcount_level),
		/* needed so that we करोn't log the whole rest of the काष्ठाure: */
		दुरत्व(xfs_agf_t, agf_spare64),
		माप(xfs_agf_t)
	पूर्ण;

	trace_xfs_agf(tp->t_mountp, bp->b_addr, fields, _RET_IP_);

	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_AGF_BUF);

	xfs_btree_offsets(fields, offsets, XFS_AGF_NUM_BITS, &first, &last);
	xfs_trans_log_buf(tp, bp, (uपूर्णांक)first, (uपूर्णांक)last);
पूर्ण

/*
 * Interface क्रम inode allocation to क्रमce the pag data to be initialized.
 */
पूर्णांक					/* error */
xfs_alloc_pagf_init(
	xfs_mount_t		*mp,	/* file प्रणाली mount काष्ठाure */
	xfs_trans_t		*tp,	/* transaction poपूर्णांकer */
	xfs_agnumber_t		agno,	/* allocation group number */
	पूर्णांक			flags)	/* XFS_ALLOC_FLAGS_... */
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	error = xfs_alloc_पढ़ो_agf(mp, tp, agno, flags, &bp);
	अगर (!error)
		xfs_trans_brअन्यथा(tp, bp);
	वापस error;
पूर्ण

/*
 * Put the block on the मुक्तlist क्रम the allocation group.
 */
पूर्णांक					/* error */
xfs_alloc_put_मुक्तlist(
	xfs_trans_t		*tp,	/* transaction poपूर्णांकer */
	काष्ठा xfs_buf		*agbp,	/* buffer क्रम a.g. मुक्तlist header */
	काष्ठा xfs_buf		*agflbp,/* buffer क्रम a.g. मुक्त block array */
	xfs_agblock_t		bno,	/* block being मुक्तd */
	पूर्णांक			btreeblk) /* block came from a AGF btree */
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	__be32			*blockp;/* poपूर्णांकer to array entry */
	पूर्णांक			error;
	पूर्णांक			logflags;
	xfs_perag_t		*pag;	/* per allocation group data */
	__be32			*agfl_bno;
	पूर्णांक			startoff;

	अगर (!agflbp && (error = xfs_alloc_पढ़ो_agfl(mp, tp,
			be32_to_cpu(agf->agf_seqno), &agflbp)))
		वापस error;
	be32_add_cpu(&agf->agf_fllast, 1);
	अगर (be32_to_cpu(agf->agf_fllast) == xfs_agfl_size(mp))
		agf->agf_fllast = 0;

	pag = agbp->b_pag;
	ASSERT(!pag->pagf_agflreset);
	be32_add_cpu(&agf->agf_flcount, 1);
	pag->pagf_flcount++;

	logflags = XFS_AGF_FLLAST | XFS_AGF_FLCOUNT;
	अगर (btreeblk) अणु
		be32_add_cpu(&agf->agf_btreeblks, -1);
		pag->pagf_btreeblks--;
		logflags |= XFS_AGF_BTREEBLKS;
	पूर्ण

	xfs_alloc_log_agf(tp, agbp, logflags);

	ASSERT(be32_to_cpu(agf->agf_flcount) <= xfs_agfl_size(mp));

	agfl_bno = xfs_buf_to_agfl_bno(agflbp);
	blockp = &agfl_bno[be32_to_cpu(agf->agf_fllast)];
	*blockp = cpu_to_be32(bno);
	startoff = (अक्षर *)blockp - (अक्षर *)agflbp->b_addr;

	xfs_alloc_log_agf(tp, agbp, logflags);

	xfs_trans_buf_set_type(tp, agflbp, XFS_BLFT_AGFL_BUF);
	xfs_trans_log_buf(tp, agflbp, startoff,
			  startoff + माप(xfs_agblock_t) - 1);
	वापस 0;
पूर्ण

अटल xfs_failaddr_t
xfs_agf_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_agf		*agf = bp->b_addr;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		अगर (!uuid_equal(&agf->agf_uuid, &mp->m_sb.sb_meta_uuid))
			वापस __this_address;
		अगर (!xfs_log_check_lsn(mp, be64_to_cpu(agf->agf_lsn)))
			वापस __this_address;
	पूर्ण

	अगर (!xfs_verअगरy_magic(bp, agf->agf_magicnum))
		वापस __this_address;

	अगर (!(XFS_AGF_GOOD_VERSION(be32_to_cpu(agf->agf_versionnum)) &&
	      be32_to_cpu(agf->agf_मुक्तblks) <= be32_to_cpu(agf->agf_length) &&
	      be32_to_cpu(agf->agf_flfirst) < xfs_agfl_size(mp) &&
	      be32_to_cpu(agf->agf_fllast) < xfs_agfl_size(mp) &&
	      be32_to_cpu(agf->agf_flcount) <= xfs_agfl_size(mp)))
		वापस __this_address;

	अगर (be32_to_cpu(agf->agf_length) > mp->m_sb.sb_dblocks)
		वापस __this_address;

	अगर (be32_to_cpu(agf->agf_मुक्तblks) < be32_to_cpu(agf->agf_दीर्घest) ||
	    be32_to_cpu(agf->agf_मुक्तblks) > be32_to_cpu(agf->agf_length))
		वापस __this_address;

	अगर (be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNO]) < 1 ||
	    be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNT]) < 1 ||
	    be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNO]) > mp->m_ag_maxlevels ||
	    be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNT]) > mp->m_ag_maxlevels)
		वापस __this_address;

	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb) &&
	    (be32_to_cpu(agf->agf_levels[XFS_BTNUM_RMAP]) < 1 ||
	     be32_to_cpu(agf->agf_levels[XFS_BTNUM_RMAP]) > mp->m_rmap_maxlevels))
		वापस __this_address;

	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb) &&
	    be32_to_cpu(agf->agf_rmap_blocks) > be32_to_cpu(agf->agf_length))
		वापस __this_address;

	/*
	 * during growfs operations, the perag is not fully initialised,
	 * so we can't use it for any useful checking. growfs ensures we can't
	 * use it by using uncached buffers that करोn't have the perag attached
	 * so we can detect and aव्योम this problem.
	 */
	अगर (bp->b_pag && be32_to_cpu(agf->agf_seqno) != bp->b_pag->pag_agno)
		वापस __this_address;

	अगर (xfs_sb_version_haslazysbcount(&mp->m_sb) &&
	    be32_to_cpu(agf->agf_btreeblks) > be32_to_cpu(agf->agf_length))
		वापस __this_address;

	अगर (xfs_sb_version_hasreflink(&mp->m_sb) &&
	    be32_to_cpu(agf->agf_refcount_blocks) >
	    be32_to_cpu(agf->agf_length))
		वापस __this_address;

	अगर (xfs_sb_version_hasreflink(&mp->m_sb) &&
	    (be32_to_cpu(agf->agf_refcount_level) < 1 ||
	     be32_to_cpu(agf->agf_refcount_level) > mp->m_refc_maxlevels))
		वापस __this_address;

	वापस शून्य;

पूर्ण

अटल व्योम
xfs_agf_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount *mp = bp->b_mount;
	xfs_failaddr_t	fa;

	अगर (xfs_sb_version_hascrc(&mp->m_sb) &&
	    !xfs_buf_verअगरy_cksum(bp, XFS_AGF_CRC_OFF))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_agf_verअगरy(bp);
		अगर (XFS_TEST_ERROR(fa, mp, XFS_ERRTAG_ALLOC_READ_AGF))
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण
पूर्ण

अटल व्योम
xfs_agf_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	काष्ठा xfs_agf		*agf = bp->b_addr;
	xfs_failaddr_t		fa;

	fa = xfs_agf_verअगरy(bp);
	अगर (fa) अणु
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (bip)
		agf->agf_lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_AGF_CRC_OFF);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_agf_buf_ops = अणु
	.name = "xfs_agf",
	.magic = अणु cpu_to_be32(XFS_AGF_MAGIC), cpu_to_be32(XFS_AGF_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_agf_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_agf_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_agf_verअगरy,
पूर्ण;

/*
 * Read in the allocation group header (मुक्त/alloc section).
 */
पूर्णांक					/* error */
xfs_पढ़ो_agf(
	काष्ठा xfs_mount	*mp,	/* mount poपूर्णांक काष्ठाure */
	काष्ठा xfs_trans	*tp,	/* transaction poपूर्णांकer */
	xfs_agnumber_t		agno,	/* allocation group number */
	पूर्णांक			flags,	/* XFS_BUF_ */
	काष्ठा xfs_buf		**bpp)	/* buffer क्रम the ag मुक्तlist header */
अणु
	पूर्णांक		error;

	trace_xfs_पढ़ो_agf(mp, agno);

	ASSERT(agno != शून्यAGNUMBER);
	error = xfs_trans_पढ़ो_buf(mp, tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, agno, XFS_AGF_DADDR(mp)),
			XFS_FSS_TO_BB(mp, 1), flags, bpp, &xfs_agf_buf_ops);
	अगर (error)
		वापस error;

	ASSERT(!(*bpp)->b_error);
	xfs_buf_set_ref(*bpp, XFS_AGF_REF);
	वापस 0;
पूर्ण

/*
 * Read in the allocation group header (मुक्त/alloc section).
 */
पूर्णांक					/* error */
xfs_alloc_पढ़ो_agf(
	काष्ठा xfs_mount	*mp,	/* mount poपूर्णांक काष्ठाure */
	काष्ठा xfs_trans	*tp,	/* transaction poपूर्णांकer */
	xfs_agnumber_t		agno,	/* allocation group number */
	पूर्णांक			flags,	/* XFS_ALLOC_FLAG_... */
	काष्ठा xfs_buf		**bpp)	/* buffer क्रम the ag मुक्तlist header */
अणु
	काष्ठा xfs_agf		*agf;		/* ag मुक्तlist header */
	काष्ठा xfs_perag	*pag;		/* per allocation group data */
	पूर्णांक			error;
	पूर्णांक			allocbt_blks;

	trace_xfs_alloc_पढ़ो_agf(mp, agno);

	/* We करोn't support trylock when मुक्तing. */
	ASSERT((flags & (XFS_ALLOC_FLAG_FREEING | XFS_ALLOC_FLAG_TRYLOCK)) !=
			(XFS_ALLOC_FLAG_FREEING | XFS_ALLOC_FLAG_TRYLOCK));
	ASSERT(agno != शून्यAGNUMBER);
	error = xfs_पढ़ो_agf(mp, tp, agno,
			(flags & XFS_ALLOC_FLAG_TRYLOCK) ? XBF_TRYLOCK : 0,
			bpp);
	अगर (error)
		वापस error;
	ASSERT(!(*bpp)->b_error);

	agf = (*bpp)->b_addr;
	pag = (*bpp)->b_pag;
	अगर (!pag->pagf_init) अणु
		pag->pagf_मुक्तblks = be32_to_cpu(agf->agf_मुक्तblks);
		pag->pagf_btreeblks = be32_to_cpu(agf->agf_btreeblks);
		pag->pagf_flcount = be32_to_cpu(agf->agf_flcount);
		pag->pagf_दीर्घest = be32_to_cpu(agf->agf_दीर्घest);
		pag->pagf_levels[XFS_BTNUM_BNOi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNOi]);
		pag->pagf_levels[XFS_BTNUM_CNTi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNTi]);
		pag->pagf_levels[XFS_BTNUM_RMAPi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_RMAPi]);
		pag->pagf_refcount_level = be32_to_cpu(agf->agf_refcount_level);
		pag->pagf_init = 1;
		pag->pagf_agflreset = xfs_agfl_needs_reset(mp, agf);

		/*
		 * Update the in-core allocbt counter. Filter out the rmapbt
		 * subset of the btreeblks counter because the rmapbt is managed
		 * by perag reservation. Subtract one क्रम the rmapbt root block
		 * because the rmap counter includes it जबतक the btreeblks
		 * counter only tracks non-root blocks.
		 */
		allocbt_blks = pag->pagf_btreeblks;
		अगर (xfs_sb_version_hasrmapbt(&mp->m_sb))
			allocbt_blks -= be32_to_cpu(agf->agf_rmap_blocks) - 1;
		अगर (allocbt_blks > 0)
			atomic64_add(allocbt_blks, &mp->m_allocbt_blks);
	पूर्ण
#अगर_घोषित DEBUG
	अन्यथा अगर (!XFS_FORCED_SHUTDOWN(mp)) अणु
		ASSERT(pag->pagf_मुक्तblks == be32_to_cpu(agf->agf_मुक्तblks));
		ASSERT(pag->pagf_btreeblks == be32_to_cpu(agf->agf_btreeblks));
		ASSERT(pag->pagf_flcount == be32_to_cpu(agf->agf_flcount));
		ASSERT(pag->pagf_दीर्घest == be32_to_cpu(agf->agf_दीर्घest));
		ASSERT(pag->pagf_levels[XFS_BTNUM_BNOi] ==
		       be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNOi]));
		ASSERT(pag->pagf_levels[XFS_BTNUM_CNTi] ==
		       be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNTi]));
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Allocate an extent (variable-size).
 * Depending on the allocation type, we either look in a single allocation
 * group or loop over the allocation groups to find the result.
 */
पूर्णांक				/* error */
xfs_alloc_vextent(
	काष्ठा xfs_alloc_arg	*args)	/* allocation argument काष्ठाure */
अणु
	xfs_agblock_t		agsize;	/* allocation group size */
	पूर्णांक			error;
	पूर्णांक			flags;	/* XFS_ALLOC_FLAG_... locking flags */
	काष्ठा xfs_mount	*mp;	/* mount काष्ठाure poपूर्णांकer */
	xfs_agnumber_t		sagno;	/* starting allocation group number */
	xfs_alloctype_t		type;	/* input allocation type */
	पूर्णांक			bump_rotor = 0;
	xfs_agnumber_t		rotorstep = xfs_rotorstep; /* inode32 agf stepper */

	mp = args->mp;
	type = args->otype = args->type;
	args->agbno = शून्यAGBLOCK;
	/*
	 * Just fix this up, क्रम the हाल where the last a.g. is लघुer
	 * (or there's only one a.g.) and the caller couldn't easily figure
	 * that out (xfs_bmap_alloc).
	 */
	agsize = mp->m_sb.sb_agblocks;
	अगर (args->maxlen > agsize)
		args->maxlen = agsize;
	अगर (args->alignment == 0)
		args->alignment = 1;
	ASSERT(XFS_FSB_TO_AGNO(mp, args->fsbno) < mp->m_sb.sb_agcount);
	ASSERT(XFS_FSB_TO_AGBNO(mp, args->fsbno) < agsize);
	ASSERT(args->minlen <= args->maxlen);
	ASSERT(args->minlen <= agsize);
	ASSERT(args->mod < args->prod);
	अगर (XFS_FSB_TO_AGNO(mp, args->fsbno) >= mp->m_sb.sb_agcount ||
	    XFS_FSB_TO_AGBNO(mp, args->fsbno) >= agsize ||
	    args->minlen > args->maxlen || args->minlen > agsize ||
	    args->mod >= args->prod) अणु
		args->fsbno = शून्यFSBLOCK;
		trace_xfs_alloc_vextent_badargs(args);
		वापस 0;
	पूर्ण

	चयन (type) अणु
	हाल XFS_ALLOCTYPE_THIS_AG:
	हाल XFS_ALLOCTYPE_NEAR_BNO:
	हाल XFS_ALLOCTYPE_THIS_BNO:
		/*
		 * These three क्रमce us पूर्णांकo a single a.g.
		 */
		args->agno = XFS_FSB_TO_AGNO(mp, args->fsbno);
		args->pag = xfs_perag_get(mp, args->agno);
		error = xfs_alloc_fix_मुक्तlist(args, 0);
		अगर (error) अणु
			trace_xfs_alloc_vextent_nofix(args);
			जाओ error0;
		पूर्ण
		अगर (!args->agbp) अणु
			trace_xfs_alloc_vextent_noagbp(args);
			अवरोध;
		पूर्ण
		args->agbno = XFS_FSB_TO_AGBNO(mp, args->fsbno);
		अगर ((error = xfs_alloc_ag_vextent(args)))
			जाओ error0;
		अवरोध;
	हाल XFS_ALLOCTYPE_START_BNO:
		/*
		 * Try near allocation first, then anywhere-in-ag after
		 * the first a.g. fails.
		 */
		अगर ((args->datatype & XFS_ALLOC_INITIAL_USER_DATA) &&
		    (mp->m_flags & XFS_MOUNT_32BITINODES)) अणु
			args->fsbno = XFS_AGB_TO_FSB(mp,
					((mp->m_agfrotor / rotorstep) %
					mp->m_sb.sb_agcount), 0);
			bump_rotor = 1;
		पूर्ण
		args->agbno = XFS_FSB_TO_AGBNO(mp, args->fsbno);
		args->type = XFS_ALLOCTYPE_NEAR_BNO;
		/* FALLTHROUGH */
	हाल XFS_ALLOCTYPE_FIRST_AG:
		/*
		 * Rotate through the allocation groups looking क्रम a winner.
		 */
		अगर (type == XFS_ALLOCTYPE_FIRST_AG) अणु
			/*
			 * Start with allocation group given by bno.
			 */
			args->agno = XFS_FSB_TO_AGNO(mp, args->fsbno);
			args->type = XFS_ALLOCTYPE_THIS_AG;
			sagno = 0;
			flags = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Start with the given allocation group.
			 */
			args->agno = sagno = XFS_FSB_TO_AGNO(mp, args->fsbno);
			flags = XFS_ALLOC_FLAG_TRYLOCK;
		पूर्ण
		/*
		 * Loop over allocation groups twice; first समय with
		 * trylock set, second समय without.
		 */
		क्रम (;;) अणु
			args->pag = xfs_perag_get(mp, args->agno);
			error = xfs_alloc_fix_मुक्तlist(args, flags);
			अगर (error) अणु
				trace_xfs_alloc_vextent_nofix(args);
				जाओ error0;
			पूर्ण
			/*
			 * If we get a buffer back then the allocation will fly.
			 */
			अगर (args->agbp) अणु
				अगर ((error = xfs_alloc_ag_vextent(args)))
					जाओ error0;
				अवरोध;
			पूर्ण

			trace_xfs_alloc_vextent_loopfailed(args);

			/*
			 * Didn't work, figure out the next iteration.
			 */
			अगर (args->agno == sagno &&
			    type == XFS_ALLOCTYPE_START_BNO)
				args->type = XFS_ALLOCTYPE_THIS_AG;
			/*
			* For the first allocation, we can try any AG to get
			* space.  However, अगर we alपढ़ोy have allocated a
			* block, we करोn't want to try AGs whose number is below
			* sagno. Otherwise, we may end up with out-of-order
			* locking of AGF, which might cause deadlock.
			*/
			अगर (++(args->agno) == mp->m_sb.sb_agcount) अणु
				अगर (args->tp->t_firstblock != शून्यFSBLOCK)
					args->agno = sagno;
				अन्यथा
					args->agno = 0;
			पूर्ण
			/*
			 * Reached the starting a.g., must either be करोne
			 * or चयन to non-trylock mode.
			 */
			अगर (args->agno == sagno) अणु
				अगर (flags == 0) अणु
					args->agbno = शून्यAGBLOCK;
					trace_xfs_alloc_vextent_allfailed(args);
					अवरोध;
				पूर्ण

				flags = 0;
				अगर (type == XFS_ALLOCTYPE_START_BNO) अणु
					args->agbno = XFS_FSB_TO_AGBNO(mp,
						args->fsbno);
					args->type = XFS_ALLOCTYPE_NEAR_BNO;
				पूर्ण
			पूर्ण
			xfs_perag_put(args->pag);
		पूर्ण
		अगर (bump_rotor) अणु
			अगर (args->agno == sagno)
				mp->m_agfrotor = (mp->m_agfrotor + 1) %
					(mp->m_sb.sb_agcount * rotorstep);
			अन्यथा
				mp->m_agfrotor = (args->agno * rotorstep + 1) %
					(mp->m_sb.sb_agcount * rotorstep);
		पूर्ण
		अवरोध;
	शेष:
		ASSERT(0);
		/* NOTREACHED */
	पूर्ण
	अगर (args->agbno == शून्यAGBLOCK)
		args->fsbno = शून्यFSBLOCK;
	अन्यथा अणु
		args->fsbno = XFS_AGB_TO_FSB(mp, args->agno, args->agbno);
#अगर_घोषित DEBUG
		ASSERT(args->len >= args->minlen);
		ASSERT(args->len <= args->maxlen);
		ASSERT(args->agbno % args->alignment == 0);
		XFS_AG_CHECK_DADDR(mp, XFS_FSB_TO_DADDR(mp, args->fsbno),
			args->len);
#पूर्ण_अगर

	पूर्ण
	xfs_perag_put(args->pag);
	वापस 0;
error0:
	xfs_perag_put(args->pag);
	वापस error;
पूर्ण

/* Ensure that the मुक्तlist is at full capacity. */
पूर्णांक
xfs_मुक्त_extent_fix_मुक्तlist(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	काष्ठा xfs_buf		**agbp)
अणु
	काष्ठा xfs_alloc_arg	args;
	पूर्णांक			error;

	स_रखो(&args, 0, माप(काष्ठा xfs_alloc_arg));
	args.tp = tp;
	args.mp = tp->t_mountp;
	args.agno = agno;

	/*
	 * validate that the block number is legal - the enables us to detect
	 * and handle a silent fileप्रणाली corruption rather than crashing.
	 */
	अगर (args.agno >= args.mp->m_sb.sb_agcount)
		वापस -EFSCORRUPTED;

	args.pag = xfs_perag_get(args.mp, args.agno);
	ASSERT(args.pag);

	error = xfs_alloc_fix_मुक्तlist(&args, XFS_ALLOC_FLAG_FREEING);
	अगर (error)
		जाओ out;

	*agbp = args.agbp;
out:
	xfs_perag_put(args.pag);
	वापस error;
पूर्ण

/*
 * Free an extent.
 * Just अवरोध up the extent address and hand off to xfs_मुक्त_ag_extent
 * after fixing up the मुक्तlist.
 */
पूर्णांक
__xfs_मुक्त_extent(
	काष्ठा xfs_trans		*tp,
	xfs_fsblock_t			bno,
	xfs_extlen_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	क्रमागत xfs_ag_resv_type		type,
	bool				skip_discard)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_buf			*agbp;
	xfs_agnumber_t			agno = XFS_FSB_TO_AGNO(mp, bno);
	xfs_agblock_t			agbno = XFS_FSB_TO_AGBNO(mp, bno);
	काष्ठा xfs_agf			*agf;
	पूर्णांक				error;
	अचिन्हित पूर्णांक			busy_flags = 0;

	ASSERT(len != 0);
	ASSERT(type != XFS_AG_RESV_AGFL);

	अगर (XFS_TEST_ERROR(false, mp,
			XFS_ERRTAG_FREE_EXTENT))
		वापस -EIO;

	error = xfs_मुक्त_extent_fix_मुक्तlist(tp, agno, &agbp);
	अगर (error)
		वापस error;
	agf = agbp->b_addr;

	अगर (XFS_IS_CORRUPT(mp, agbno >= mp->m_sb.sb_agblocks)) अणु
		error = -EFSCORRUPTED;
		जाओ err;
	पूर्ण

	/* validate the extent size is legal now we have the agf locked */
	अगर (XFS_IS_CORRUPT(mp, agbno + len > be32_to_cpu(agf->agf_length))) अणु
		error = -EFSCORRUPTED;
		जाओ err;
	पूर्ण

	error = xfs_मुक्त_ag_extent(tp, agbp, agno, agbno, len, oinfo, type);
	अगर (error)
		जाओ err;

	अगर (skip_discard)
		busy_flags |= XFS_EXTENT_BUSY_SKIP_DISCARD;
	xfs_extent_busy_insert(tp, agno, agbno, len, busy_flags);
	वापस 0;

err:
	xfs_trans_brअन्यथा(tp, agbp);
	वापस error;
पूर्ण

काष्ठा xfs_alloc_query_range_info अणु
	xfs_alloc_query_range_fn	fn;
	व्योम				*priv;
पूर्ण;

/* Format btree record and pass to our callback. */
STATIC पूर्णांक
xfs_alloc_query_range_helper(
	काष्ठा xfs_btree_cur		*cur,
	जोड़ xfs_btree_rec		*rec,
	व्योम				*priv)
अणु
	काष्ठा xfs_alloc_query_range_info	*query = priv;
	काष्ठा xfs_alloc_rec_incore		irec;

	irec.ar_startblock = be32_to_cpu(rec->alloc.ar_startblock);
	irec.ar_blockcount = be32_to_cpu(rec->alloc.ar_blockcount);
	वापस query->fn(cur, &irec, query->priv);
पूर्ण

/* Find all मुक्त space within a given range of blocks. */
पूर्णांक
xfs_alloc_query_range(
	काष्ठा xfs_btree_cur			*cur,
	काष्ठा xfs_alloc_rec_incore		*low_rec,
	काष्ठा xfs_alloc_rec_incore		*high_rec,
	xfs_alloc_query_range_fn		fn,
	व्योम					*priv)
अणु
	जोड़ xfs_btree_irec			low_brec;
	जोड़ xfs_btree_irec			high_brec;
	काष्ठा xfs_alloc_query_range_info	query;

	ASSERT(cur->bc_btnum == XFS_BTNUM_BNO);
	low_brec.a = *low_rec;
	high_brec.a = *high_rec;
	query.priv = priv;
	query.fn = fn;
	वापस xfs_btree_query_range(cur, &low_brec, &high_brec,
			xfs_alloc_query_range_helper, &query);
पूर्ण

/* Find all मुक्त space records. */
पूर्णांक
xfs_alloc_query_all(
	काष्ठा xfs_btree_cur			*cur,
	xfs_alloc_query_range_fn		fn,
	व्योम					*priv)
अणु
	काष्ठा xfs_alloc_query_range_info	query;

	ASSERT(cur->bc_btnum == XFS_BTNUM_BNO);
	query.priv = priv;
	query.fn = fn;
	वापस xfs_btree_query_all(cur, xfs_alloc_query_range_helper, &query);
पूर्ण

/* Is there a record covering a given extent? */
पूर्णांक
xfs_alloc_has_record(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	xfs_extlen_t		len,
	bool			*exists)
अणु
	जोड़ xfs_btree_irec	low;
	जोड़ xfs_btree_irec	high;

	स_रखो(&low, 0, माप(low));
	low.a.ar_startblock = bno;
	स_रखो(&high, 0xFF, माप(high));
	high.a.ar_startblock = bno + len - 1;

	वापस xfs_btree_has_record(cur, &low, &high, exists);
पूर्ण

/*
 * Walk all the blocks in the AGFL.  The @walk_fn can वापस any negative
 * error code or XFS_ITER_*.
 */
पूर्णांक
xfs_agfl_walk(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_agf		*agf,
	काष्ठा xfs_buf		*agflbp,
	xfs_agfl_walk_fn	walk_fn,
	व्योम			*priv)
अणु
	__be32			*agfl_bno;
	अचिन्हित पूर्णांक		i;
	पूर्णांक			error;

	agfl_bno = xfs_buf_to_agfl_bno(agflbp);
	i = be32_to_cpu(agf->agf_flfirst);

	/* Nothing to walk in an empty AGFL. */
	अगर (agf->agf_flcount == cpu_to_be32(0))
		वापस 0;

	/* Otherwise, walk from first to last, wrapping as needed. */
	क्रम (;;) अणु
		error = walk_fn(mp, be32_to_cpu(agfl_bno[i]), priv);
		अगर (error)
			वापस error;
		अगर (i == be32_to_cpu(agf->agf_fllast))
			अवरोध;
		अगर (++i == xfs_agfl_size(mp))
			i = 0;
	पूर्ण

	वापस 0;
पूर्ण
