<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_alloc_btree.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_ialloc_btree.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "xfs_refcount_btree.h"
#समावेश "xfs_extent_busy.h"
#समावेश "xfs_ag_resv.h"
#समावेश "xfs_quota.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/trace.h"
#समावेश "scrub/repair.h"
#समावेश "scrub/bitmap.h"

/*
 * Attempt to repair some metadata, अगर the metadata is corrupt and userspace
 * told us to fix it.  This function वापसs -EAGAIN to mean "re-run scrub",
 * and will set *fixed to true अगर it thinks it repaired anything.
 */
पूर्णांक
xrep_attempt(
	काष्ठा xfs_scrub	*sc)
अणु
	पूर्णांक			error = 0;

	trace_xrep_attempt(XFS_I(file_inode(sc->file)), sc->sm, error);

	xchk_ag_btcur_मुक्त(&sc->sa);

	/* Repair whatever's broken. */
	ASSERT(sc->ops->repair);
	error = sc->ops->repair(sc);
	trace_xrep_करोne(XFS_I(file_inode(sc->file)), sc->sm, error);
	चयन (error) अणु
	हाल 0:
		/*
		 * Repair succeeded.  Commit the fixes and perक्रमm a second
		 * scrub so that we can tell userspace अगर we fixed the problem.
		 */
		sc->sm->sm_flags &= ~XFS_SCRUB_FLAGS_OUT;
		sc->flags |= XREP_ALREADY_FIXED;
		वापस -EAGAIN;
	हाल -EDEADLOCK:
	हाल -EAGAIN:
		/* Tell the caller to try again having grabbed all the locks. */
		अगर (!(sc->flags & XCHK_TRY_HARDER)) अणु
			sc->flags |= XCHK_TRY_HARDER;
			वापस -EAGAIN;
		पूर्ण
		/*
		 * We tried harder but still couldn't grab all the resources
		 * we needed to fix it.  The corruption has not been fixed,
		 * so report back to userspace.
		 */
		वापस -EFSCORRUPTED;
	शेष:
		वापस error;
	पूर्ण
पूर्ण

/*
 * Complain about unfixable problems in the fileप्रणाली.  We करोn't log
 * corruptions when IFLAG_REPAIR wasn't set on the assumption that the driver
 * program is xfs_scrub, which will call back with IFLAG_REPAIR set अगर the
 * administrator isn't running xfs_scrub in no-repairs mode.
 *
 * Use this helper function because _ratelimited silently declares a अटल
 * काष्ठाure to track rate limiting inक्रमmation.
 */
व्योम
xrep_failure(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_alert_ratelimited(mp,
"Corruption not fixed during online repair.  Unmount and run xfs_repair.");
पूर्ण

/*
 * Repair probe -- userspace uses this to probe अगर we're willing to repair a
 * given mountpoपूर्णांक.
 */
पूर्णांक
xrep_probe(
	काष्ठा xfs_scrub	*sc)
अणु
	पूर्णांक			error = 0;

	अगर (xchk_should_terminate(sc, &error))
		वापस error;

	वापस 0;
पूर्ण

/*
 * Roll a transaction, keeping the AG headers locked and reinitializing
 * the btree cursors.
 */
पूर्णांक
xrep_roll_ag_trans(
	काष्ठा xfs_scrub	*sc)
अणु
	पूर्णांक			error;

	/* Keep the AG header buffers locked so we can keep going. */
	अगर (sc->sa.agi_bp)
		xfs_trans_bhold(sc->tp, sc->sa.agi_bp);
	अगर (sc->sa.agf_bp)
		xfs_trans_bhold(sc->tp, sc->sa.agf_bp);
	अगर (sc->sa.agfl_bp)
		xfs_trans_bhold(sc->tp, sc->sa.agfl_bp);

	/*
	 * Roll the transaction.  We still own the buffer and the buffer lock
	 * regardless of whether or not the roll succeeds.  If the roll fails,
	 * the buffers will be released during tearकरोwn on our way out of the
	 * kernel.  If it succeeds, we join them to the new transaction and
	 * move on.
	 */
	error = xfs_trans_roll(&sc->tp);
	अगर (error)
		वापस error;

	/* Join AG headers to the new transaction. */
	अगर (sc->sa.agi_bp)
		xfs_trans_bjoin(sc->tp, sc->sa.agi_bp);
	अगर (sc->sa.agf_bp)
		xfs_trans_bjoin(sc->tp, sc->sa.agf_bp);
	अगर (sc->sa.agfl_bp)
		xfs_trans_bjoin(sc->tp, sc->sa.agfl_bp);

	वापस 0;
पूर्ण

/*
 * Does the given AG have enough space to rebuild a btree?  Neither AG
 * reservation can be critical, and we must have enough space (factoring
 * in AG reservations) to स्थिरruct a whole btree.
 */
bool
xrep_ag_has_space(
	काष्ठा xfs_perag	*pag,
	xfs_extlen_t		nr_blocks,
	क्रमागत xfs_ag_resv_type	type)
अणु
	वापस  !xfs_ag_resv_critical(pag, XFS_AG_RESV_RMAPBT) &&
		!xfs_ag_resv_critical(pag, XFS_AG_RESV_METADATA) &&
		pag->pagf_मुक्तblks > xfs_ag_resv_needed(pag, type) + nr_blocks;
पूर्ण

/*
 * Figure out how many blocks to reserve क्रम an AG repair.  We calculate the
 * worst हाल estimate क्रम the number of blocks we'd need to rebuild one of
 * any type of per-AG btree.
 */
xfs_extlen_t
xrep_calc_ag_resblks(
	काष्ठा xfs_scrub		*sc)
अणु
	काष्ठा xfs_mount		*mp = sc->mp;
	काष्ठा xfs_scrub_metadata	*sm = sc->sm;
	काष्ठा xfs_perag		*pag;
	काष्ठा xfs_buf			*bp;
	xfs_agino_t			icount = शून्यAGINO;
	xfs_extlen_t			aglen = शून्यAGBLOCK;
	xfs_extlen_t			usedlen;
	xfs_extlen_t			मुक्तlen;
	xfs_extlen_t			bnobt_sz;
	xfs_extlen_t			inobt_sz;
	xfs_extlen_t			rmapbt_sz;
	xfs_extlen_t			refcbt_sz;
	पूर्णांक				error;

	अगर (!(sm->sm_flags & XFS_SCRUB_IFLAG_REPAIR))
		वापस 0;

	pag = xfs_perag_get(mp, sm->sm_agno);
	अगर (pag->pagi_init) अणु
		/* Use in-core icount अगर possible. */
		icount = pag->pagi_count;
	पूर्ण अन्यथा अणु
		/* Try to get the actual counters from disk. */
		error = xfs_ialloc_पढ़ो_agi(mp, शून्य, sm->sm_agno, &bp);
		अगर (!error) अणु
			icount = pag->pagi_count;
			xfs_buf_rअन्यथा(bp);
		पूर्ण
	पूर्ण

	/* Now grab the block counters from the AGF. */
	error = xfs_alloc_पढ़ो_agf(mp, शून्य, sm->sm_agno, 0, &bp);
	अगर (error) अणु
		aglen = xfs_ag_block_count(mp, sm->sm_agno);
		मुक्तlen = aglen;
		usedlen = aglen;
	पूर्ण अन्यथा अणु
		काष्ठा xfs_agf	*agf = bp->b_addr;

		aglen = be32_to_cpu(agf->agf_length);
		मुक्तlen = be32_to_cpu(agf->agf_मुक्तblks);
		usedlen = aglen - मुक्तlen;
		xfs_buf_rअन्यथा(bp);
	पूर्ण
	xfs_perag_put(pag);

	/* If the icount is impossible, make some worst-हाल assumptions. */
	अगर (icount == शून्यAGINO ||
	    !xfs_verअगरy_agino(mp, sm->sm_agno, icount)) अणु
		xfs_agino_t	first, last;

		xfs_agino_range(mp, sm->sm_agno, &first, &last);
		icount = last - first + 1;
	पूर्ण

	/* If the block counts are impossible, make worst-हाल assumptions. */
	अगर (aglen == शून्यAGBLOCK ||
	    aglen != xfs_ag_block_count(mp, sm->sm_agno) ||
	    मुक्तlen >= aglen) अणु
		aglen = xfs_ag_block_count(mp, sm->sm_agno);
		मुक्तlen = aglen;
		usedlen = aglen;
	पूर्ण

	trace_xrep_calc_ag_resblks(mp, sm->sm_agno, icount, aglen,
			मुक्तlen, usedlen);

	/*
	 * Figure out how many blocks we'd need worst हाल to rebuild
	 * each type of btree.  Note that we can only rebuild the
	 * bnobt/cntbt or inobt/finobt as pairs.
	 */
	bnobt_sz = 2 * xfs_allocbt_calc_size(mp, मुक्तlen);
	अगर (xfs_sb_version_hassparseinodes(&mp->m_sb))
		inobt_sz = xfs_iallocbt_calc_size(mp, icount /
				XFS_INODES_PER_HOLEMASK_BIT);
	अन्यथा
		inobt_sz = xfs_iallocbt_calc_size(mp, icount /
				XFS_INODES_PER_CHUNK);
	अगर (xfs_sb_version_hasfinobt(&mp->m_sb))
		inobt_sz *= 2;
	अगर (xfs_sb_version_hasreflink(&mp->m_sb))
		refcbt_sz = xfs_refcountbt_calc_size(mp, usedlen);
	अन्यथा
		refcbt_sz = 0;
	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb)) अणु
		/*
		 * Guess how many blocks we need to rebuild the rmapbt.
		 * For non-reflink fileप्रणालीs we can't have more records than
		 * used blocks.  However, with reflink it's possible to have
		 * more than one rmap record per AG block.  We करोn't know how
		 * many rmaps there could be in the AG, so we start off with
		 * what we hope is an generous over-estimation.
		 */
		अगर (xfs_sb_version_hasreflink(&mp->m_sb))
			rmapbt_sz = xfs_rmapbt_calc_size(mp,
					(अचिन्हित दीर्घ दीर्घ)aglen * 2);
		अन्यथा
			rmapbt_sz = xfs_rmapbt_calc_size(mp, usedlen);
	पूर्ण अन्यथा अणु
		rmapbt_sz = 0;
	पूर्ण

	trace_xrep_calc_ag_resblks_btsize(mp, sm->sm_agno, bnobt_sz,
			inobt_sz, rmapbt_sz, refcbt_sz);

	वापस max(max(bnobt_sz, inobt_sz), max(rmapbt_sz, refcbt_sz));
पूर्ण

/* Allocate a block in an AG. */
पूर्णांक
xrep_alloc_ag_block(
	काष्ठा xfs_scrub		*sc,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	xfs_fsblock_t			*fsbno,
	क्रमागत xfs_ag_resv_type		resv)
अणु
	काष्ठा xfs_alloc_arg		args = अणु0पूर्ण;
	xfs_agblock_t			bno;
	पूर्णांक				error;

	चयन (resv) अणु
	हाल XFS_AG_RESV_AGFL:
	हाल XFS_AG_RESV_RMAPBT:
		error = xfs_alloc_get_मुक्तlist(sc->tp, sc->sa.agf_bp, &bno, 1);
		अगर (error)
			वापस error;
		अगर (bno == शून्यAGBLOCK)
			वापस -ENOSPC;
		xfs_extent_busy_reuse(sc->mp, sc->sa.agno, bno,
				1, false);
		*fsbno = XFS_AGB_TO_FSB(sc->mp, sc->sa.agno, bno);
		अगर (resv == XFS_AG_RESV_RMAPBT)
			xfs_ag_resv_rmapbt_alloc(sc->mp, sc->sa.agno);
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	args.tp = sc->tp;
	args.mp = sc->mp;
	args.oinfo = *oinfo;
	args.fsbno = XFS_AGB_TO_FSB(args.mp, sc->sa.agno, 0);
	args.minlen = 1;
	args.maxlen = 1;
	args.prod = 1;
	args.type = XFS_ALLOCTYPE_THIS_AG;
	args.resv = resv;

	error = xfs_alloc_vextent(&args);
	अगर (error)
		वापस error;
	अगर (args.fsbno == शून्यFSBLOCK)
		वापस -ENOSPC;
	ASSERT(args.len == 1);
	*fsbno = args.fsbno;

	वापस 0;
पूर्ण

/* Initialize a new AG btree root block with zero entries. */
पूर्णांक
xrep_init_btblock(
	काष्ठा xfs_scrub		*sc,
	xfs_fsblock_t			fsb,
	काष्ठा xfs_buf			**bpp,
	xfs_btnum_t			btnum,
	स्थिर काष्ठा xfs_buf_ops	*ops)
अणु
	काष्ठा xfs_trans		*tp = sc->tp;
	काष्ठा xfs_mount		*mp = sc->mp;
	काष्ठा xfs_buf			*bp;
	पूर्णांक				error;

	trace_xrep_init_btblock(mp, XFS_FSB_TO_AGNO(mp, fsb),
			XFS_FSB_TO_AGBNO(mp, fsb), btnum);

	ASSERT(XFS_FSB_TO_AGNO(mp, fsb) == sc->sa.agno);
	error = xfs_trans_get_buf(tp, mp->m_ddev_targp,
			XFS_FSB_TO_DADDR(mp, fsb), XFS_FSB_TO_BB(mp, 1), 0,
			&bp);
	अगर (error)
		वापस error;
	xfs_buf_zero(bp, 0, BBTOB(bp->b_length));
	xfs_btree_init_block(mp, bp, btnum, 0, 0, sc->sa.agno);
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_BTREE_BUF);
	xfs_trans_log_buf(tp, bp, 0, BBTOB(bp->b_length) - 1);
	bp->b_ops = ops;
	*bpp = bp;

	वापस 0;
पूर्ण

/*
 * Reस्थिरructing per-AG Btrees
 *
 * When a space btree is corrupt, we करोn't bother trying to fix it.  Instead,
 * we scan secondary space metadata to derive the records that should be in
 * the damaged btree, initialize a fresh btree root, and insert the records.
 * Note that क्रम rebuilding the rmapbt we scan all the primary data to
 * generate the new records.
 *
 * However, that leaves the matter of removing all the metadata describing the
 * old broken काष्ठाure.  For primary metadata we use the rmap data to collect
 * every extent with a matching rmap owner (biपंचांगap); we then iterate all other
 * metadata काष्ठाures with the same rmap owner to collect the extents that
 * cannot be हटाओd (sublist).  We then subtract sublist from biपंचांगap to
 * derive the blocks that were used by the old btree.  These blocks can be
 * reaped.
 *
 * For rmapbt reस्थिरructions we must use dअगरferent tactics क्रम extent
 * collection.  First we iterate all primary metadata (this excludes the old
 * rmapbt, obviously) to generate new rmap records.  The gaps in the rmap
 * records are collected as biपंचांगap.  The bnobt records are collected as
 * sublist.  As with the other btrees we subtract sublist from biपंचांगap, and the
 * result (since the rmapbt lives in the मुक्त space) are the blocks from the
 * old rmapbt.
 *
 * Disposal of Blocks from Old per-AG Btrees
 *
 * Now that we've स्थिरructed a new btree to replace the damaged one, we want
 * to dispose of the blocks that (we think) the old btree was using.
 * Previously, we used the rmapbt to collect the extents (biपंचांगap) with the
 * rmap owner corresponding to the tree we rebuilt, collected extents क्रम any
 * blocks with the same rmap owner that are owned by another data काष्ठाure
 * (sublist), and subtracted sublist from biपंचांगap.  In theory the extents
 * reमुख्यing in biपंचांगap are the old btree's blocks.
 *
 * Unक्रमtunately, it's possible that the btree was crosslinked with other
 * blocks on disk.  The rmap data can tell us अगर there are multiple owners, so
 * अगर the rmapbt says there is an owner of this block other than @oinfo, then
 * the block is crosslinked.  Remove the reverse mapping and जारी.
 *
 * If there is one rmap record, we can मुक्त the block, which हटाओs the
 * reverse mapping but करोesn't add the block to the मुक्त space.  Our repair
 * strategy is to hope the other metadata objects crosslinked on this block
 * will be rebuilt (atop dअगरferent blocks), thereby removing all the cross
 * links.
 *
 * If there are no rmap records at all, we also मुक्त the block.  If the btree
 * being rebuilt lives in the मुक्त space (bnobt/cntbt/rmapbt) then there isn't
 * supposed to be a rmap record and everything is ok.  For other btrees there
 * had to have been an rmap entry क्रम the block to have ended up on @biपंचांगap,
 * so अगर it's gone now there's something wrong and the fs will shut करोwn.
 *
 * Note: If there are multiple rmap records with only the same rmap owner as
 * the btree we're trying to rebuild and the block is indeed owned by another
 * data काष्ठाure with the same rmap owner, then the block will be in sublist
 * and thereक्रमe करोesn't need disposal.  If there are multiple rmap records
 * with only the same rmap owner but the block is not owned by something with
 * the same rmap owner, the block will be मुक्तd.
 *
 * The caller is responsible क्रम locking the AG headers क्रम the entire rebuild
 * operation so that nothing अन्यथा can sneak in and change the AG state जबतक
 * we're not looking.  We also assume that the caller alपढ़ोy invalidated any
 * buffers associated with @biपंचांगap.
 */

/*
 * Invalidate buffers क्रम per-AG btree blocks we're dumping.  This function
 * is not पूर्णांकended क्रम use with file data repairs; we have bunmapi क्रम that.
 */
पूर्णांक
xrep_invalidate_blocks(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xbiपंचांगap		*biपंचांगap)
अणु
	काष्ठा xbiपंचांगap_range	*bmr;
	काष्ठा xbiपंचांगap_range	*n;
	काष्ठा xfs_buf		*bp;
	xfs_fsblock_t		fsbno;

	/*
	 * For each block in each extent, see अगर there's an incore buffer क्रम
	 * exactly that block; अगर so, invalidate it.  The buffer cache only
	 * lets us look क्रम one buffer at a समय, so we have to look one block
	 * at a समय.  Aव्योम invalidating AG headers and post-खातापूर्णS blocks
	 * because we never own those; and अगर we can't TRYLOCK the buffer we
	 * assume it's owned by someone अन्यथा.
	 */
	क्रम_each_xbiपंचांगap_block(fsbno, bmr, n, biपंचांगap) अणु
		/* Skip AG headers and post-खातापूर्णS blocks */
		अगर (!xfs_verअगरy_fsbno(sc->mp, fsbno))
			जारी;
		bp = xfs_buf_incore(sc->mp->m_ddev_targp,
				XFS_FSB_TO_DADDR(sc->mp, fsbno),
				XFS_FSB_TO_BB(sc->mp, 1), XBF_TRYLOCK);
		अगर (bp) अणु
			xfs_trans_bjoin(sc->tp, bp);
			xfs_trans_binval(sc->tp, bp);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Ensure the मुक्तlist is the correct size. */
पूर्णांक
xrep_fix_मुक्तlist(
	काष्ठा xfs_scrub	*sc,
	bool			can_shrink)
अणु
	काष्ठा xfs_alloc_arg	args = अणु0पूर्ण;

	args.mp = sc->mp;
	args.tp = sc->tp;
	args.agno = sc->sa.agno;
	args.alignment = 1;
	args.pag = sc->sa.pag;

	वापस xfs_alloc_fix_मुक्तlist(&args,
			can_shrink ? 0 : XFS_ALLOC_FLAG_NOSHRINK);
पूर्ण

/*
 * Put a block back on the AGFL.
 */
STATIC पूर्णांक
xrep_put_मुक्तlist(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		agbno)
अणु
	पूर्णांक			error;

	/* Make sure there's space on the मुक्तlist. */
	error = xrep_fix_मुक्तlist(sc, true);
	अगर (error)
		वापस error;

	/*
	 * Since we're "freeing" a lost block onto the AGFL, we have to
	 * create an rmap क्रम the block prior to merging it or अन्यथा other
	 * parts will अवरोध.
	 */
	error = xfs_rmap_alloc(sc->tp, sc->sa.agf_bp, sc->sa.agno, agbno, 1,
			&XFS_RMAP_OINFO_AG);
	अगर (error)
		वापस error;

	/* Put the block on the AGFL. */
	error = xfs_alloc_put_मुक्तlist(sc->tp, sc->sa.agf_bp, sc->sa.agfl_bp,
			agbno, 0);
	अगर (error)
		वापस error;
	xfs_extent_busy_insert(sc->tp, sc->sa.agno, agbno, 1,
			XFS_EXTENT_BUSY_SKIP_DISCARD);

	वापस 0;
पूर्ण

/* Dispose of a single block. */
STATIC पूर्णांक
xrep_reap_block(
	काष्ठा xfs_scrub		*sc,
	xfs_fsblock_t			fsbno,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	क्रमागत xfs_ag_resv_type		resv)
अणु
	काष्ठा xfs_btree_cur		*cur;
	काष्ठा xfs_buf			*agf_bp = शून्य;
	xfs_agnumber_t			agno;
	xfs_agblock_t			agbno;
	bool				has_other_rmap;
	पूर्णांक				error;

	agno = XFS_FSB_TO_AGNO(sc->mp, fsbno);
	agbno = XFS_FSB_TO_AGBNO(sc->mp, fsbno);

	/*
	 * If we are repairing per-inode metadata, we need to पढ़ो in the AGF
	 * buffer.  Otherwise, we're repairing a per-AG काष्ठाure, so reuse
	 * the AGF buffer that the setup functions alपढ़ोy grabbed.
	 */
	अगर (sc->ip) अणु
		error = xfs_alloc_पढ़ो_agf(sc->mp, sc->tp, agno, 0, &agf_bp);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		agf_bp = sc->sa.agf_bp;
	पूर्ण
	cur = xfs_rmapbt_init_cursor(sc->mp, sc->tp, agf_bp, agno);

	/* Can we find any other rmappings? */
	error = xfs_rmap_has_other_keys(cur, agbno, 1, oinfo, &has_other_rmap);
	xfs_btree_del_cursor(cur, error);
	अगर (error)
		जाओ out_मुक्त;

	/*
	 * If there are other rmappings, this block is cross linked and must
	 * not be मुक्तd.  Remove the reverse mapping and move on.  Otherwise,
	 * we were the only owner of the block, so मुक्त the extent, which will
	 * also हटाओ the rmap.
	 *
	 * XXX: XFS करोesn't support detecting the हाल where a single block
	 * metadata काष्ठाure is crosslinked with a multi-block काष्ठाure
	 * because the buffer cache करोesn't detect aliasing problems, so we
	 * can't fix 100% of crosslinking problems (yet).  The verअगरiers will
	 * blow on ग_लिखोout, the fileप्रणाली will shut करोwn, and the admin माला_लो
	 * to run xfs_repair.
	 */
	अगर (has_other_rmap)
		error = xfs_rmap_मुक्त(sc->tp, agf_bp, agno, agbno, 1, oinfo);
	अन्यथा अगर (resv == XFS_AG_RESV_AGFL)
		error = xrep_put_मुक्तlist(sc, agbno);
	अन्यथा
		error = xfs_मुक्त_extent(sc->tp, fsbno, 1, oinfo, resv);
	अगर (agf_bp != sc->sa.agf_bp)
		xfs_trans_brअन्यथा(sc->tp, agf_bp);
	अगर (error)
		वापस error;

	अगर (sc->ip)
		वापस xfs_trans_roll_inode(&sc->tp, sc->ip);
	वापस xrep_roll_ag_trans(sc);

out_मुक्त:
	अगर (agf_bp != sc->sa.agf_bp)
		xfs_trans_brअन्यथा(sc->tp, agf_bp);
	वापस error;
पूर्ण

/* Dispose of every block of every extent in the biपंचांगap. */
पूर्णांक
xrep_reap_extents(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xbiपंचांगap			*biपंचांगap,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	क्रमागत xfs_ag_resv_type		type)
अणु
	काष्ठा xbiपंचांगap_range		*bmr;
	काष्ठा xbiपंचांगap_range		*n;
	xfs_fsblock_t			fsbno;
	पूर्णांक				error = 0;

	ASSERT(xfs_sb_version_hasrmapbt(&sc->mp->m_sb));

	क्रम_each_xbiपंचांगap_block(fsbno, bmr, n, biपंचांगap) अणु
		ASSERT(sc->ip != शून्य ||
		       XFS_FSB_TO_AGNO(sc->mp, fsbno) == sc->sa.agno);
		trace_xrep_dispose_btree_extent(sc->mp,
				XFS_FSB_TO_AGNO(sc->mp, fsbno),
				XFS_FSB_TO_AGBNO(sc->mp, fsbno), 1);

		error = xrep_reap_block(sc, fsbno, oinfo, type);
		अगर (error)
			अवरोध;
	पूर्ण

	वापस error;
पूर्ण

/*
 * Finding per-AG Btree Roots क्रम AGF/AGI Reस्थिरruction
 *
 * If the AGF or AGI become slightly corrupted, it may be necessary to rebuild
 * the AG headers by using the rmap data to rummage through the AG looking क्रम
 * btree roots.  This is not guaranteed to work अगर the AG is heavily damaged
 * or the rmap data are corrupt.
 *
 * Callers of xrep_find_ag_btree_roots must lock the AGF and AGFL
 * buffers अगर the AGF is being rebuilt; or the AGF and AGI buffers अगर the
 * AGI is being rebuilt.  It must मुख्यtain these locks until it's safe क्रम
 * other thपढ़ोs to change the btrees' shapes.  The caller provides
 * inक्रमmation about the btrees to look क्रम by passing in an array of
 * xrep_find_ag_btree with the (rmap owner, buf_ops, magic) fields set.
 * The (root, height) fields will be set on वापस अगर anything is found.  The
 * last element of the array should have a शून्य buf_ops to mark the end of the
 * array.
 *
 * For every rmapbt record matching any of the rmap owners in btree_info,
 * पढ़ो each block referenced by the rmap record.  If the block is a btree
 * block from this fileप्रणाली matching any of the magic numbers and has a
 * level higher than what we've alपढ़ोy seen, remember the block and the
 * height of the tree required to have such a block.  When the call completes,
 * we वापस the highest block we've found क्रम each btree description; those
 * should be the roots.
 */

काष्ठा xrep_findroot अणु
	काष्ठा xfs_scrub		*sc;
	काष्ठा xfs_buf			*agfl_bp;
	काष्ठा xfs_agf			*agf;
	काष्ठा xrep_find_ag_btree	*btree_info;
पूर्ण;

/* See अगर our block is in the AGFL. */
STATIC पूर्णांक
xrep_findroot_agfl_walk(
	काष्ठा xfs_mount	*mp,
	xfs_agblock_t		bno,
	व्योम			*priv)
अणु
	xfs_agblock_t		*agbno = priv;

	वापस (*agbno == bno) ? -ECANCELED : 0;
पूर्ण

/* Does this block match the btree inक्रमmation passed in? */
STATIC पूर्णांक
xrep_findroot_block(
	काष्ठा xrep_findroot		*ri,
	काष्ठा xrep_find_ag_btree	*fab,
	uपूर्णांक64_t			owner,
	xfs_agblock_t			agbno,
	bool				*करोne_with_block)
अणु
	काष्ठा xfs_mount		*mp = ri->sc->mp;
	काष्ठा xfs_buf			*bp;
	काष्ठा xfs_btree_block		*btblock;
	xfs_daddr_t			daddr;
	पूर्णांक				block_level;
	पूर्णांक				error = 0;

	daddr = XFS_AGB_TO_DADDR(mp, ri->sc->sa.agno, agbno);

	/*
	 * Blocks in the AGFL have stale contents that might just happen to
	 * have a matching magic and uuid.  We करोn't want to pull these blocks
	 * in as part of a tree root, so we have to filter out the AGFL stuff
	 * here.  If the AGFL looks insane we'll just refuse to repair.
	 */
	अगर (owner == XFS_RMAP_OWN_AG) अणु
		error = xfs_agfl_walk(mp, ri->agf, ri->agfl_bp,
				xrep_findroot_agfl_walk, &agbno);
		अगर (error == -ECANCELED)
			वापस 0;
		अगर (error)
			वापस error;
	पूर्ण

	/*
	 * Read the buffer पूर्णांकo memory so that we can see अगर it's a match क्रम
	 * our btree type.  We have no clue अगर it is beक्रमehand, and we want to
	 * aव्योम xfs_trans_पढ़ो_buf's behavior of dumping the DONE state (which
	 * will cause needless disk पढ़ोs in subsequent calls to this function)
	 * and logging metadata verअगरier failures.
	 *
	 * Thereक्रमe, pass in शून्य buffer ops.  If the buffer was alपढ़ोy in
	 * memory from some other caller it will alपढ़ोy have b_ops asचिन्हित.
	 * If it was in memory from a previous unsuccessful findroot_block
	 * call, the buffer won't have b_ops but it should be clean and पढ़ोy
	 * क्रम us to try to verअगरy अगर the पढ़ो call succeeds.  The same applies
	 * अगर the buffer wasn't in memory at all.
	 *
	 * Note: If we never match a btree type with this buffer, it will be
	 * left in memory with शून्य b_ops.  This shouldn't be a problem unless
	 * the buffer माला_लो written.
	 */
	error = xfs_trans_पढ़ो_buf(mp, ri->sc->tp, mp->m_ddev_targp, daddr,
			mp->m_bsize, 0, &bp, शून्य);
	अगर (error)
		वापस error;

	/* Ensure the block magic matches the btree type we're looking क्रम. */
	btblock = XFS_BUF_TO_BLOCK(bp);
	ASSERT(fab->buf_ops->magic[1] != 0);
	अगर (btblock->bb_magic != fab->buf_ops->magic[1])
		जाओ out;

	/*
	 * If the buffer alपढ़ोy has ops applied and they're not the ones क्रम
	 * this btree type, we know this block करोesn't match the btree and we
	 * can bail out.
	 *
	 * If the buffer ops match ours, someone अन्यथा has alपढ़ोy validated
	 * the block क्रम us, so we can move on to checking अगर this is a root
	 * block candidate.
	 *
	 * If the buffer करोes not have ops, nobody has successfully validated
	 * the contents and the buffer cannot be dirty.  If the magic, uuid,
	 * and काष्ठाure match this btree type then we'll move on to checking
	 * अगर it's a root block candidate.  If there is no match, bail out.
	 */
	अगर (bp->b_ops) अणु
		अगर (bp->b_ops != fab->buf_ops)
			जाओ out;
	पूर्ण अन्यथा अणु
		ASSERT(!xfs_trans_buf_is_dirty(bp));
		अगर (!uuid_equal(&btblock->bb_u.s.bb_uuid,
				&mp->m_sb.sb_meta_uuid))
			जाओ out;
		/*
		 * Read verअगरiers can reference b_ops, so we set the poपूर्णांकer
		 * here.  If the verअगरier fails we'll reset the buffer state
		 * to what it was beक्रमe we touched the buffer.
		 */
		bp->b_ops = fab->buf_ops;
		fab->buf_ops->verअगरy_पढ़ो(bp);
		अगर (bp->b_error) अणु
			bp->b_ops = शून्य;
			bp->b_error = 0;
			जाओ out;
		पूर्ण

		/*
		 * Some पढ़ो verअगरiers will (re)set b_ops, so we must be
		 * careful not to change b_ops after running the verअगरier.
		 */
	पूर्ण

	/*
	 * This block passes the magic/uuid and verअगरier tests क्रम this btree
	 * type.  We करोn't need the caller to try the other tree types.
	 */
	*करोne_with_block = true;

	/*
	 * Compare this btree block's level to the height of the current
	 * candidate root block.
	 *
	 * If the level matches the root we found previously, throw away both
	 * blocks because there can't be two candidate roots.
	 *
	 * If level is lower in the tree than the root we found previously,
	 * ignore this block.
	 */
	block_level = xfs_btree_get_level(btblock);
	अगर (block_level + 1 == fab->height) अणु
		fab->root = शून्यAGBLOCK;
		जाओ out;
	पूर्ण अन्यथा अगर (block_level < fab->height) अणु
		जाओ out;
	पूर्ण

	/*
	 * This is the highest block in the tree that we've found so far.
	 * Update the btree height to reflect what we've learned from this
	 * block.
	 */
	fab->height = block_level + 1;

	/*
	 * If this block करोesn't have sibling pointers, then it's the new root
	 * block candidate.  Otherwise, the root will be found farther up the
	 * tree.
	 */
	अगर (btblock->bb_u.s.bb_leftsib == cpu_to_be32(शून्यAGBLOCK) &&
	    btblock->bb_u.s.bb_rightsib == cpu_to_be32(शून्यAGBLOCK))
		fab->root = agbno;
	अन्यथा
		fab->root = शून्यAGBLOCK;

	trace_xrep_findroot_block(mp, ri->sc->sa.agno, agbno,
			be32_to_cpu(btblock->bb_magic), fab->height - 1);
out:
	xfs_trans_brअन्यथा(ri->sc->tp, bp);
	वापस error;
पूर्ण

/*
 * Do any of the blocks in this rmap record match one of the btrees we're
 * looking क्रम?
 */
STATIC पूर्णांक
xrep_findroot_rmap(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_rmap_irec		*rec,
	व्योम				*priv)
अणु
	काष्ठा xrep_findroot		*ri = priv;
	काष्ठा xrep_find_ag_btree	*fab;
	xfs_agblock_t			b;
	bool				करोne;
	पूर्णांक				error = 0;

	/* Ignore anything that isn't AG metadata. */
	अगर (!XFS_RMAP_NON_INODE_OWNER(rec->rm_owner))
		वापस 0;

	/* Otherwise scan each block + btree type. */
	क्रम (b = 0; b < rec->rm_blockcount; b++) अणु
		करोne = false;
		क्रम (fab = ri->btree_info; fab->buf_ops; fab++) अणु
			अगर (rec->rm_owner != fab->rmap_owner)
				जारी;
			error = xrep_findroot_block(ri, fab,
					rec->rm_owner, rec->rm_startblock + b,
					&करोne);
			अगर (error)
				वापस error;
			अगर (करोne)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Find the roots of the per-AG btrees described in btree_info. */
पूर्णांक
xrep_find_ag_btree_roots(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xfs_buf			*agf_bp,
	काष्ठा xrep_find_ag_btree	*btree_info,
	काष्ठा xfs_buf			*agfl_bp)
अणु
	काष्ठा xfs_mount		*mp = sc->mp;
	काष्ठा xrep_findroot		ri;
	काष्ठा xrep_find_ag_btree	*fab;
	काष्ठा xfs_btree_cur		*cur;
	पूर्णांक				error;

	ASSERT(xfs_buf_islocked(agf_bp));
	ASSERT(agfl_bp == शून्य || xfs_buf_islocked(agfl_bp));

	ri.sc = sc;
	ri.btree_info = btree_info;
	ri.agf = agf_bp->b_addr;
	ri.agfl_bp = agfl_bp;
	क्रम (fab = btree_info; fab->buf_ops; fab++) अणु
		ASSERT(agfl_bp || fab->rmap_owner != XFS_RMAP_OWN_AG);
		ASSERT(XFS_RMAP_NON_INODE_OWNER(fab->rmap_owner));
		fab->root = शून्यAGBLOCK;
		fab->height = 0;
	पूर्ण

	cur = xfs_rmapbt_init_cursor(mp, sc->tp, agf_bp, sc->sa.agno);
	error = xfs_rmap_query_all(cur, xrep_findroot_rmap, &ri);
	xfs_btree_del_cursor(cur, error);

	वापस error;
पूर्ण

/* Force a quotacheck the next समय we mount. */
व्योम
xrep_क्रमce_quotacheck(
	काष्ठा xfs_scrub	*sc,
	xfs_dqtype_t		type)
अणु
	uपूर्णांक			flag;

	flag = xfs_quota_chkd_flag(type);
	अगर (!(flag & sc->mp->m_qflags))
		वापस;

	sc->mp->m_qflags &= ~flag;
	spin_lock(&sc->mp->m_sb_lock);
	sc->mp->m_sb.sb_qflags &= ~flag;
	spin_unlock(&sc->mp->m_sb_lock);
	xfs_log_sb(sc->tp);
पूर्ण

/*
 * Attach dquots to this inode, or schedule quotacheck to fix them.
 *
 * This function ensures that the appropriate dquots are attached to an inode.
 * We cannot allow the dquot code to allocate an on-disk dquot block here
 * because we're alपढ़ोy in transaction context with the inode locked.  The
 * on-disk dquot should alपढ़ोy exist anyway.  If the quota code संकेतs
 * corruption or missing quota inक्रमmation, schedule quotacheck, which will
 * repair corruptions in the quota metadata.
 */
पूर्णांक
xrep_ino_dqattach(
	काष्ठा xfs_scrub	*sc)
अणु
	पूर्णांक			error;

	error = xfs_qm_dqattach_locked(sc->ip, false);
	चयन (error) अणु
	हाल -EFSBADCRC:
	हाल -EFSCORRUPTED:
	हाल -ENOENT:
		xfs_err_ratelimited(sc->mp,
"inode %llu repair encountered quota error %d, quotacheck forced.",
				(अचिन्हित दीर्घ दीर्घ)sc->ip->i_ino, error);
		अगर (XFS_IS_UQUOTA_ON(sc->mp) && !sc->ip->i_udquot)
			xrep_क्रमce_quotacheck(sc, XFS_DQTYPE_USER);
		अगर (XFS_IS_GQUOTA_ON(sc->mp) && !sc->ip->i_gdquot)
			xrep_क्रमce_quotacheck(sc, XFS_DQTYPE_GROUP);
		अगर (XFS_IS_PQUOTA_ON(sc->mp) && !sc->ip->i_pdquot)
			xrep_क्रमce_quotacheck(sc, XFS_DQTYPE_PROJ);
		/* fall through */
	हाल -ESRCH:
		error = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस error;
पूर्ण
