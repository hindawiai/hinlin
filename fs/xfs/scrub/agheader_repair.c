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
#समावेश "xfs_alloc.h"
#समावेश "xfs_alloc_btree.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_ialloc_btree.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "xfs_refcount_btree.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/trace.h"
#समावेश "scrub/repair.h"
#समावेश "scrub/bitmap.h"

/* Superblock */

/* Repair the superblock. */
पूर्णांक
xrep_superblock(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_buf		*bp;
	xfs_agnumber_t		agno;
	पूर्णांक			error;

	/* Don't try to repair AG 0's sb; let xfs_repair deal with it. */
	agno = sc->sm->sm_agno;
	अगर (agno == 0)
		वापस -EOPNOTSUPP;

	error = xfs_sb_get_secondary(mp, sc->tp, agno, &bp);
	अगर (error)
		वापस error;

	/* Copy AG 0's superblock to this one. */
	xfs_buf_zero(bp, 0, BBTOB(bp->b_length));
	xfs_sb_to_disk(bp->b_addr, &mp->m_sb);

	/* Write this to disk. */
	xfs_trans_buf_set_type(sc->tp, bp, XFS_BLFT_SB_BUF);
	xfs_trans_log_buf(sc->tp, bp, 0, BBTOB(bp->b_length) - 1);
	वापस error;
पूर्ण

/* AGF */

काष्ठा xrep_agf_allocbt अणु
	काष्ठा xfs_scrub	*sc;
	xfs_agblock_t		मुक्तblks;
	xfs_agblock_t		दीर्घest;
पूर्ण;

/* Record मुक्त space shape inक्रमmation. */
STATIC पूर्णांक
xrep_agf_walk_allocbt(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_alloc_rec_incore	*rec,
	व्योम				*priv)
अणु
	काष्ठा xrep_agf_allocbt		*raa = priv;
	पूर्णांक				error = 0;

	अगर (xchk_should_terminate(raa->sc, &error))
		वापस error;

	raa->मुक्तblks += rec->ar_blockcount;
	अगर (rec->ar_blockcount > raa->दीर्घest)
		raa->दीर्घest = rec->ar_blockcount;
	वापस error;
पूर्ण

/* Does this AGFL block look sane? */
STATIC पूर्णांक
xrep_agf_check_agfl_block(
	काष्ठा xfs_mount	*mp,
	xfs_agblock_t		agbno,
	व्योम			*priv)
अणु
	काष्ठा xfs_scrub	*sc = priv;

	अगर (!xfs_verअगरy_agbno(mp, sc->sa.agno, agbno))
		वापस -EFSCORRUPTED;
	वापस 0;
पूर्ण

/*
 * Offset within the xrep_find_ag_btree array क्रम each btree type.  Aव्योम the
 * XFS_BTNUM_ names here to aव्योम creating a sparse array.
 */
क्रमागत अणु
	XREP_AGF_BNOBT = 0,
	XREP_AGF_CNTBT,
	XREP_AGF_RMAPBT,
	XREP_AGF_REFCOUNTBT,
	XREP_AGF_END,
	XREP_AGF_MAX
पूर्ण;

/* Check a btree root candidate. */
अटल अंतरभूत bool
xrep_check_btree_root(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xrep_find_ag_btree	*fab)
अणु
	काष्ठा xfs_mount		*mp = sc->mp;
	xfs_agnumber_t			agno = sc->sm->sm_agno;

	वापस xfs_verअगरy_agbno(mp, agno, fab->root) &&
	       fab->height <= XFS_BTREE_MAXLEVELS;
पूर्ण

/*
 * Given the btree roots described by *fab, find the roots, check them क्रम
 * sanity, and pass the root data back out via *fab.
 *
 * This is /also/ a chicken and egg problem because we have to use the rmapbt
 * (rooted in the AGF) to find the btrees rooted in the AGF.  We also have no
 * idea अगर the btrees make any sense.  If we hit obvious corruptions in those
 * btrees we'll bail out.
 */
STATIC पूर्णांक
xrep_agf_find_btrees(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xfs_buf			*agf_bp,
	काष्ठा xrep_find_ag_btree	*fab,
	काष्ठा xfs_buf			*agfl_bp)
अणु
	काष्ठा xfs_agf			*old_agf = agf_bp->b_addr;
	पूर्णांक				error;

	/* Go find the root data. */
	error = xrep_find_ag_btree_roots(sc, agf_bp, fab, agfl_bp);
	अगर (error)
		वापस error;

	/* We must find the bnobt, cntbt, and rmapbt roots. */
	अगर (!xrep_check_btree_root(sc, &fab[XREP_AGF_BNOBT]) ||
	    !xrep_check_btree_root(sc, &fab[XREP_AGF_CNTBT]) ||
	    !xrep_check_btree_root(sc, &fab[XREP_AGF_RMAPBT]))
		वापस -EFSCORRUPTED;

	/*
	 * We relied on the rmapbt to reस्थिरruct the AGF.  If we get a
	 * dअगरferent root then something's seriously wrong.
	 */
	अगर (fab[XREP_AGF_RMAPBT].root !=
	    be32_to_cpu(old_agf->agf_roots[XFS_BTNUM_RMAPi]))
		वापस -EFSCORRUPTED;

	/* We must find the refcountbt root अगर that feature is enabled. */
	अगर (xfs_sb_version_hasreflink(&sc->mp->m_sb) &&
	    !xrep_check_btree_root(sc, &fab[XREP_AGF_REFCOUNTBT]))
		वापस -EFSCORRUPTED;

	वापस 0;
पूर्ण

/*
 * Reinitialize the AGF header, making an in-core copy of the old contents so
 * that we know which in-core state needs to be reinitialized.
 */
STATIC व्योम
xrep_agf_init_header(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*agf_bp,
	काष्ठा xfs_agf		*old_agf)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_agf		*agf = agf_bp->b_addr;

	स_नकल(old_agf, agf, माप(*old_agf));
	स_रखो(agf, 0, BBTOB(agf_bp->b_length));
	agf->agf_magicnum = cpu_to_be32(XFS_AGF_MAGIC);
	agf->agf_versionnum = cpu_to_be32(XFS_AGF_VERSION);
	agf->agf_seqno = cpu_to_be32(sc->sa.agno);
	agf->agf_length = cpu_to_be32(xfs_ag_block_count(mp, sc->sa.agno));
	agf->agf_flfirst = old_agf->agf_flfirst;
	agf->agf_fllast = old_agf->agf_fllast;
	agf->agf_flcount = old_agf->agf_flcount;
	अगर (xfs_sb_version_hascrc(&mp->m_sb))
		uuid_copy(&agf->agf_uuid, &mp->m_sb.sb_meta_uuid);

	/* Mark the incore AGF data stale until we're करोne fixing things. */
	ASSERT(sc->sa.pag->pagf_init);
	sc->sa.pag->pagf_init = 0;
पूर्ण

/* Set btree root inक्रमmation in an AGF. */
STATIC व्योम
xrep_agf_set_roots(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xfs_agf			*agf,
	काष्ठा xrep_find_ag_btree	*fab)
अणु
	agf->agf_roots[XFS_BTNUM_BNOi] =
			cpu_to_be32(fab[XREP_AGF_BNOBT].root);
	agf->agf_levels[XFS_BTNUM_BNOi] =
			cpu_to_be32(fab[XREP_AGF_BNOBT].height);

	agf->agf_roots[XFS_BTNUM_CNTi] =
			cpu_to_be32(fab[XREP_AGF_CNTBT].root);
	agf->agf_levels[XFS_BTNUM_CNTi] =
			cpu_to_be32(fab[XREP_AGF_CNTBT].height);

	agf->agf_roots[XFS_BTNUM_RMAPi] =
			cpu_to_be32(fab[XREP_AGF_RMAPBT].root);
	agf->agf_levels[XFS_BTNUM_RMAPi] =
			cpu_to_be32(fab[XREP_AGF_RMAPBT].height);

	अगर (xfs_sb_version_hasreflink(&sc->mp->m_sb)) अणु
		agf->agf_refcount_root =
				cpu_to_be32(fab[XREP_AGF_REFCOUNTBT].root);
		agf->agf_refcount_level =
				cpu_to_be32(fab[XREP_AGF_REFCOUNTBT].height);
	पूर्ण
पूर्ण

/* Update all AGF fields which derive from btree contents. */
STATIC पूर्णांक
xrep_agf_calc_from_btrees(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*agf_bp)
अणु
	काष्ठा xrep_agf_allocbt	raa = अणु .sc = sc पूर्ण;
	काष्ठा xfs_btree_cur	*cur = शून्य;
	काष्ठा xfs_agf		*agf = agf_bp->b_addr;
	काष्ठा xfs_mount	*mp = sc->mp;
	xfs_agblock_t		btreeblks;
	xfs_agblock_t		blocks;
	पूर्णांक			error;

	/* Update the AGF counters from the bnobt. */
	cur = xfs_allocbt_init_cursor(mp, sc->tp, agf_bp, sc->sa.agno,
			XFS_BTNUM_BNO);
	error = xfs_alloc_query_all(cur, xrep_agf_walk_allocbt, &raa);
	अगर (error)
		जाओ err;
	error = xfs_btree_count_blocks(cur, &blocks);
	अगर (error)
		जाओ err;
	xfs_btree_del_cursor(cur, error);
	btreeblks = blocks - 1;
	agf->agf_मुक्तblks = cpu_to_be32(raa.मुक्तblks);
	agf->agf_दीर्घest = cpu_to_be32(raa.दीर्घest);

	/* Update the AGF counters from the cntbt. */
	cur = xfs_allocbt_init_cursor(mp, sc->tp, agf_bp, sc->sa.agno,
			XFS_BTNUM_CNT);
	error = xfs_btree_count_blocks(cur, &blocks);
	अगर (error)
		जाओ err;
	xfs_btree_del_cursor(cur, error);
	btreeblks += blocks - 1;

	/* Update the AGF counters from the rmapbt. */
	cur = xfs_rmapbt_init_cursor(mp, sc->tp, agf_bp, sc->sa.agno);
	error = xfs_btree_count_blocks(cur, &blocks);
	अगर (error)
		जाओ err;
	xfs_btree_del_cursor(cur, error);
	agf->agf_rmap_blocks = cpu_to_be32(blocks);
	btreeblks += blocks - 1;

	agf->agf_btreeblks = cpu_to_be32(btreeblks);

	/* Update the AGF counters from the refcountbt. */
	अगर (xfs_sb_version_hasreflink(&mp->m_sb)) अणु
		cur = xfs_refcountbt_init_cursor(mp, sc->tp, agf_bp,
				sc->sa.agno);
		error = xfs_btree_count_blocks(cur, &blocks);
		अगर (error)
			जाओ err;
		xfs_btree_del_cursor(cur, error);
		agf->agf_refcount_blocks = cpu_to_be32(blocks);
	पूर्ण

	वापस 0;
err:
	xfs_btree_del_cursor(cur, error);
	वापस error;
पूर्ण

/* Commit the new AGF and reinitialize the incore state. */
STATIC पूर्णांक
xrep_agf_commit_new(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*agf_bp)
अणु
	काष्ठा xfs_perag	*pag;
	काष्ठा xfs_agf		*agf = agf_bp->b_addr;

	/* Trigger fdblocks recalculation */
	xfs_क्रमce_summary_recalc(sc->mp);

	/* Write this to disk. */
	xfs_trans_buf_set_type(sc->tp, agf_bp, XFS_BLFT_AGF_BUF);
	xfs_trans_log_buf(sc->tp, agf_bp, 0, BBTOB(agf_bp->b_length) - 1);

	/* Now reinitialize the in-core counters we changed. */
	pag = sc->sa.pag;
	pag->pagf_btreeblks = be32_to_cpu(agf->agf_btreeblks);
	pag->pagf_मुक्तblks = be32_to_cpu(agf->agf_मुक्तblks);
	pag->pagf_दीर्घest = be32_to_cpu(agf->agf_दीर्घest);
	pag->pagf_levels[XFS_BTNUM_BNOi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNOi]);
	pag->pagf_levels[XFS_BTNUM_CNTi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNTi]);
	pag->pagf_levels[XFS_BTNUM_RMAPi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_RMAPi]);
	pag->pagf_refcount_level = be32_to_cpu(agf->agf_refcount_level);
	pag->pagf_init = 1;

	वापस 0;
पूर्ण

/* Repair the AGF. v5 fileप्रणालीs only. */
पूर्णांक
xrep_agf(
	काष्ठा xfs_scrub		*sc)
अणु
	काष्ठा xrep_find_ag_btree	fab[XREP_AGF_MAX] = अणु
		[XREP_AGF_BNOBT] = अणु
			.rmap_owner = XFS_RMAP_OWN_AG,
			.buf_ops = &xfs_bnobt_buf_ops,
		पूर्ण,
		[XREP_AGF_CNTBT] = अणु
			.rmap_owner = XFS_RMAP_OWN_AG,
			.buf_ops = &xfs_cntbt_buf_ops,
		पूर्ण,
		[XREP_AGF_RMAPBT] = अणु
			.rmap_owner = XFS_RMAP_OWN_AG,
			.buf_ops = &xfs_rmapbt_buf_ops,
		पूर्ण,
		[XREP_AGF_REFCOUNTBT] = अणु
			.rmap_owner = XFS_RMAP_OWN_REFC,
			.buf_ops = &xfs_refcountbt_buf_ops,
		पूर्ण,
		[XREP_AGF_END] = अणु
			.buf_ops = शून्य,
		पूर्ण,
	पूर्ण;
	काष्ठा xfs_agf			old_agf;
	काष्ठा xfs_mount		*mp = sc->mp;
	काष्ठा xfs_buf			*agf_bp;
	काष्ठा xfs_buf			*agfl_bp;
	काष्ठा xfs_agf			*agf;
	पूर्णांक				error;

	/* We require the rmapbt to rebuild anything. */
	अगर (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस -EOPNOTSUPP;

	xchk_perag_get(sc->mp, &sc->sa);
	/*
	 * Make sure we have the AGF buffer, as scrub might have decided it
	 * was corrupt after xfs_alloc_पढ़ो_agf failed with -EFSCORRUPTED.
	 */
	error = xfs_trans_पढ़ो_buf(mp, sc->tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, sc->sa.agno, XFS_AGF_DADDR(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &agf_bp, शून्य);
	अगर (error)
		वापस error;
	agf_bp->b_ops = &xfs_agf_buf_ops;
	agf = agf_bp->b_addr;

	/*
	 * Load the AGFL so that we can screen out OWN_AG blocks that are on
	 * the AGFL now; these blocks might have once been part of the
	 * bno/cnt/rmap btrees but are not now.  This is a chicken and egg
	 * problem: the AGF is corrupt, so we have to trust the AGFL contents
	 * because we can't करो any serious cross-referencing with any of the
	 * btrees rooted in the AGF.  If the AGFL contents are obviously bad
	 * then we'll bail out.
	 */
	error = xfs_alloc_पढ़ो_agfl(mp, sc->tp, sc->sa.agno, &agfl_bp);
	अगर (error)
		वापस error;

	/*
	 * Spot-check the AGFL blocks; अगर they're obviously corrupt then
	 * there's nothing we can करो but bail out.
	 */
	error = xfs_agfl_walk(sc->mp, agf_bp->b_addr, agfl_bp,
			xrep_agf_check_agfl_block, sc);
	अगर (error)
		वापस error;

	/*
	 * Find the AGF btree roots.  This is also a chicken-and-egg situation;
	 * see the function क्रम more details.
	 */
	error = xrep_agf_find_btrees(sc, agf_bp, fab, agfl_bp);
	अगर (error)
		वापस error;

	/* Start rewriting the header and implant the btrees we found. */
	xrep_agf_init_header(sc, agf_bp, &old_agf);
	xrep_agf_set_roots(sc, agf, fab);
	error = xrep_agf_calc_from_btrees(sc, agf_bp);
	अगर (error)
		जाओ out_revert;

	/* Commit the changes and reinitialize incore state. */
	वापस xrep_agf_commit_new(sc, agf_bp);

out_revert:
	/* Mark the incore AGF state stale and revert the AGF. */
	sc->sa.pag->pagf_init = 0;
	स_नकल(agf, &old_agf, माप(old_agf));
	वापस error;
पूर्ण

/* AGFL */

काष्ठा xrep_agfl अणु
	/* Biपंचांगap of other OWN_AG metadata blocks. */
	काष्ठा xbiपंचांगap		agmetablocks;

	/* Biपंचांगap of मुक्त space. */
	काष्ठा xbiपंचांगap		*मुक्तsp;

	काष्ठा xfs_scrub	*sc;
पूर्ण;

/* Record all OWN_AG (मुक्त space btree) inक्रमmation from the rmap data. */
STATIC पूर्णांक
xrep_agfl_walk_rmap(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_rmap_irec	*rec,
	व्योम			*priv)
अणु
	काष्ठा xrep_agfl	*ra = priv;
	xfs_fsblock_t		fsb;
	पूर्णांक			error = 0;

	अगर (xchk_should_terminate(ra->sc, &error))
		वापस error;

	/* Record all the OWN_AG blocks. */
	अगर (rec->rm_owner == XFS_RMAP_OWN_AG) अणु
		fsb = XFS_AGB_TO_FSB(cur->bc_mp, cur->bc_ag.agno,
				rec->rm_startblock);
		error = xbiपंचांगap_set(ra->मुक्तsp, fsb, rec->rm_blockcount);
		अगर (error)
			वापस error;
	पूर्ण

	वापस xbiपंचांगap_set_btcur_path(&ra->agmetablocks, cur);
पूर्ण

/*
 * Map out all the non-AGFL OWN_AG space in this AG so that we can deduce
 * which blocks beदीर्घ to the AGFL.
 *
 * Compute the set of old AGFL blocks by subtracting from the list of OWN_AG
 * blocks the list of blocks owned by all other OWN_AG metadata (bnobt, cntbt,
 * rmapbt).  These are the old AGFL blocks, so वापस that list and the number
 * of blocks we're actually going to put back on the AGFL.
 */
STATIC पूर्णांक
xrep_agfl_collect_blocks(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*agf_bp,
	काष्ठा xbiपंचांगap		*agfl_extents,
	xfs_agblock_t		*flcount)
अणु
	काष्ठा xrep_agfl	ra;
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_btree_cur	*cur;
	पूर्णांक			error;

	ra.sc = sc;
	ra.मुक्तsp = agfl_extents;
	xbiपंचांगap_init(&ra.agmetablocks);

	/* Find all space used by the मुक्त space btrees & rmapbt. */
	cur = xfs_rmapbt_init_cursor(mp, sc->tp, agf_bp, sc->sa.agno);
	error = xfs_rmap_query_all(cur, xrep_agfl_walk_rmap, &ra);
	अगर (error)
		जाओ err;
	xfs_btree_del_cursor(cur, error);

	/* Find all blocks currently being used by the bnobt. */
	cur = xfs_allocbt_init_cursor(mp, sc->tp, agf_bp, sc->sa.agno,
			XFS_BTNUM_BNO);
	error = xbiपंचांगap_set_btblocks(&ra.agmetablocks, cur);
	अगर (error)
		जाओ err;
	xfs_btree_del_cursor(cur, error);

	/* Find all blocks currently being used by the cntbt. */
	cur = xfs_allocbt_init_cursor(mp, sc->tp, agf_bp, sc->sa.agno,
			XFS_BTNUM_CNT);
	error = xbiपंचांगap_set_btblocks(&ra.agmetablocks, cur);
	अगर (error)
		जाओ err;

	xfs_btree_del_cursor(cur, error);

	/*
	 * Drop the मुक्तsp meta blocks that are in use by btrees.
	 * The reमुख्यing blocks /should/ be AGFL blocks.
	 */
	error = xbiपंचांगap_disजोड़(agfl_extents, &ra.agmetablocks);
	xbiपंचांगap_destroy(&ra.agmetablocks);
	अगर (error)
		वापस error;

	/*
	 * Calculate the new AGFL size.  If we found more blocks than fit in
	 * the AGFL we'll मुक्त them later.
	 */
	*flcount = min_t(uपूर्णांक64_t, xbiपंचांगap_hweight(agfl_extents),
			 xfs_agfl_size(mp));
	वापस 0;

err:
	xbiपंचांगap_destroy(&ra.agmetablocks);
	xfs_btree_del_cursor(cur, error);
	वापस error;
पूर्ण

/* Update the AGF and reset the in-core state. */
STATIC व्योम
xrep_agfl_update_agf(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*agf_bp,
	xfs_agblock_t		flcount)
अणु
	काष्ठा xfs_agf		*agf = agf_bp->b_addr;

	ASSERT(flcount <= xfs_agfl_size(sc->mp));

	/* Trigger fdblocks recalculation */
	xfs_क्रमce_summary_recalc(sc->mp);

	/* Update the AGF counters. */
	अगर (sc->sa.pag->pagf_init)
		sc->sa.pag->pagf_flcount = flcount;
	agf->agf_flfirst = cpu_to_be32(0);
	agf->agf_flcount = cpu_to_be32(flcount);
	agf->agf_fllast = cpu_to_be32(flcount - 1);

	xfs_alloc_log_agf(sc->tp, agf_bp,
			XFS_AGF_FLFIRST | XFS_AGF_FLLAST | XFS_AGF_FLCOUNT);
पूर्ण

/* Write out a totally new AGFL. */
STATIC व्योम
xrep_agfl_init_header(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*agfl_bp,
	काष्ठा xbiपंचांगap		*agfl_extents,
	xfs_agblock_t		flcount)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	__be32			*agfl_bno;
	काष्ठा xbiपंचांगap_range	*br;
	काष्ठा xbiपंचांगap_range	*n;
	काष्ठा xfs_agfl		*agfl;
	xfs_agblock_t		agbno;
	अचिन्हित पूर्णांक		fl_off;

	ASSERT(flcount <= xfs_agfl_size(mp));

	/*
	 * Start rewriting the header by setting the bno[] array to
	 * शून्यAGBLOCK, then setting AGFL header fields.
	 */
	agfl = XFS_BUF_TO_AGFL(agfl_bp);
	स_रखो(agfl, 0xFF, BBTOB(agfl_bp->b_length));
	agfl->agfl_magicnum = cpu_to_be32(XFS_AGFL_MAGIC);
	agfl->agfl_seqno = cpu_to_be32(sc->sa.agno);
	uuid_copy(&agfl->agfl_uuid, &mp->m_sb.sb_meta_uuid);

	/*
	 * Fill the AGFL with the reमुख्यing blocks.  If agfl_extents has more
	 * blocks than fit in the AGFL, they will be मुक्तd in a subsequent
	 * step.
	 */
	fl_off = 0;
	agfl_bno = xfs_buf_to_agfl_bno(agfl_bp);
	क्रम_each_xbiपंचांगap_extent(br, n, agfl_extents) अणु
		agbno = XFS_FSB_TO_AGBNO(mp, br->start);

		trace_xrep_agfl_insert(mp, sc->sa.agno, agbno, br->len);

		जबतक (br->len > 0 && fl_off < flcount) अणु
			agfl_bno[fl_off] = cpu_to_be32(agbno);
			fl_off++;
			agbno++;

			/*
			 * We've now used br->start by putting it in the AGFL,
			 * so bump br so that we करोn't reap the block later.
			 */
			br->start++;
			br->len--;
		पूर्ण

		अगर (br->len)
			अवरोध;
		list_del(&br->list);
		kmem_मुक्त(br);
	पूर्ण

	/* Write new AGFL to disk. */
	xfs_trans_buf_set_type(sc->tp, agfl_bp, XFS_BLFT_AGFL_BUF);
	xfs_trans_log_buf(sc->tp, agfl_bp, 0, BBTOB(agfl_bp->b_length) - 1);
पूर्ण

/* Repair the AGFL. */
पूर्णांक
xrep_agfl(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xbiपंचांगap		agfl_extents;
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_buf		*agf_bp;
	काष्ठा xfs_buf		*agfl_bp;
	xfs_agblock_t		flcount;
	पूर्णांक			error;

	/* We require the rmapbt to rebuild anything. */
	अगर (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस -EOPNOTSUPP;

	xchk_perag_get(sc->mp, &sc->sa);
	xbiपंचांगap_init(&agfl_extents);

	/*
	 * Read the AGF so that we can query the rmapbt.  We hope that there's
	 * nothing wrong with the AGF, but all the AG header repair functions
	 * have this chicken-and-egg problem.
	 */
	error = xfs_alloc_पढ़ो_agf(mp, sc->tp, sc->sa.agno, 0, &agf_bp);
	अगर (error)
		वापस error;

	/*
	 * Make sure we have the AGFL buffer, as scrub might have decided it
	 * was corrupt after xfs_alloc_पढ़ो_agfl failed with -EFSCORRUPTED.
	 */
	error = xfs_trans_पढ़ो_buf(mp, sc->tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, sc->sa.agno, XFS_AGFL_DADDR(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &agfl_bp, शून्य);
	अगर (error)
		वापस error;
	agfl_bp->b_ops = &xfs_agfl_buf_ops;

	/* Gather all the extents we're going to put on the new AGFL. */
	error = xrep_agfl_collect_blocks(sc, agf_bp, &agfl_extents, &flcount);
	अगर (error)
		जाओ err;

	/*
	 * Update AGF and AGFL.  We reset the global मुक्त block counter when
	 * we adjust the AGF flcount (which can fail) so aव्योम updating any
	 * buffers until we know that part works.
	 */
	xrep_agfl_update_agf(sc, agf_bp, flcount);
	xrep_agfl_init_header(sc, agfl_bp, &agfl_extents, flcount);

	/*
	 * Ok, the AGFL should be पढ़ोy to go now.  Roll the transaction to
	 * make the new AGFL permanent beक्रमe we start using it to वापस
	 * मुक्तspace overflow to the मुक्तspace btrees.
	 */
	sc->sa.agf_bp = agf_bp;
	sc->sa.agfl_bp = agfl_bp;
	error = xrep_roll_ag_trans(sc);
	अगर (error)
		जाओ err;

	/* Dump any AGFL overflow. */
	error = xrep_reap_extents(sc, &agfl_extents, &XFS_RMAP_OINFO_AG,
			XFS_AG_RESV_AGFL);
err:
	xbiपंचांगap_destroy(&agfl_extents);
	वापस error;
पूर्ण

/* AGI */

/*
 * Offset within the xrep_find_ag_btree array क्रम each btree type.  Aव्योम the
 * XFS_BTNUM_ names here to aव्योम creating a sparse array.
 */
क्रमागत अणु
	XREP_AGI_INOBT = 0,
	XREP_AGI_FINOBT,
	XREP_AGI_END,
	XREP_AGI_MAX
पूर्ण;

/*
 * Given the inode btree roots described by *fab, find the roots, check them
 * क्रम sanity, and pass the root data back out via *fab.
 */
STATIC पूर्णांक
xrep_agi_find_btrees(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xrep_find_ag_btree	*fab)
अणु
	काष्ठा xfs_buf			*agf_bp;
	काष्ठा xfs_mount		*mp = sc->mp;
	पूर्णांक				error;

	/* Read the AGF. */
	error = xfs_alloc_पढ़ो_agf(mp, sc->tp, sc->sa.agno, 0, &agf_bp);
	अगर (error)
		वापस error;

	/* Find the btree roots. */
	error = xrep_find_ag_btree_roots(sc, agf_bp, fab, शून्य);
	अगर (error)
		वापस error;

	/* We must find the inobt root. */
	अगर (!xrep_check_btree_root(sc, &fab[XREP_AGI_INOBT]))
		वापस -EFSCORRUPTED;

	/* We must find the finobt root अगर that feature is enabled. */
	अगर (xfs_sb_version_hasfinobt(&mp->m_sb) &&
	    !xrep_check_btree_root(sc, &fab[XREP_AGI_FINOBT]))
		वापस -EFSCORRUPTED;

	वापस 0;
पूर्ण

/*
 * Reinitialize the AGI header, making an in-core copy of the old contents so
 * that we know which in-core state needs to be reinitialized.
 */
STATIC व्योम
xrep_agi_init_header(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*agi_bp,
	काष्ठा xfs_agi		*old_agi)
अणु
	काष्ठा xfs_agi		*agi = agi_bp->b_addr;
	काष्ठा xfs_mount	*mp = sc->mp;

	स_नकल(old_agi, agi, माप(*old_agi));
	स_रखो(agi, 0, BBTOB(agi_bp->b_length));
	agi->agi_magicnum = cpu_to_be32(XFS_AGI_MAGIC);
	agi->agi_versionnum = cpu_to_be32(XFS_AGI_VERSION);
	agi->agi_seqno = cpu_to_be32(sc->sa.agno);
	agi->agi_length = cpu_to_be32(xfs_ag_block_count(mp, sc->sa.agno));
	agi->agi_newino = cpu_to_be32(शून्यAGINO);
	agi->agi_dirino = cpu_to_be32(शून्यAGINO);
	अगर (xfs_sb_version_hascrc(&mp->m_sb))
		uuid_copy(&agi->agi_uuid, &mp->m_sb.sb_meta_uuid);

	/* We करोn't know how to fix the unlinked list yet. */
	स_नकल(&agi->agi_unlinked, &old_agi->agi_unlinked,
			माप(agi->agi_unlinked));

	/* Mark the incore AGF data stale until we're करोne fixing things. */
	ASSERT(sc->sa.pag->pagi_init);
	sc->sa.pag->pagi_init = 0;
पूर्ण

/* Set btree root inक्रमmation in an AGI. */
STATIC व्योम
xrep_agi_set_roots(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xfs_agi			*agi,
	काष्ठा xrep_find_ag_btree	*fab)
अणु
	agi->agi_root = cpu_to_be32(fab[XREP_AGI_INOBT].root);
	agi->agi_level = cpu_to_be32(fab[XREP_AGI_INOBT].height);

	अगर (xfs_sb_version_hasfinobt(&sc->mp->m_sb)) अणु
		agi->agi_मुक्त_root = cpu_to_be32(fab[XREP_AGI_FINOBT].root);
		agi->agi_मुक्त_level = cpu_to_be32(fab[XREP_AGI_FINOBT].height);
	पूर्ण
पूर्ण

/* Update the AGI counters. */
STATIC पूर्णांक
xrep_agi_calc_from_btrees(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*agi_bp)
अणु
	काष्ठा xfs_btree_cur	*cur;
	काष्ठा xfs_agi		*agi = agi_bp->b_addr;
	काष्ठा xfs_mount	*mp = sc->mp;
	xfs_agino_t		count;
	xfs_agino_t		मुक्तcount;
	पूर्णांक			error;

	cur = xfs_inobt_init_cursor(mp, sc->tp, agi_bp, sc->sa.agno,
			XFS_BTNUM_INO);
	error = xfs_ialloc_count_inodes(cur, &count, &मुक्तcount);
	अगर (error)
		जाओ err;
	अगर (xfs_sb_version_hasinobtcounts(&mp->m_sb)) अणु
		xfs_agblock_t	blocks;

		error = xfs_btree_count_blocks(cur, &blocks);
		अगर (error)
			जाओ err;
		agi->agi_iblocks = cpu_to_be32(blocks);
	पूर्ण
	xfs_btree_del_cursor(cur, error);

	agi->agi_count = cpu_to_be32(count);
	agi->agi_मुक्तcount = cpu_to_be32(मुक्तcount);

	अगर (xfs_sb_version_hasfinobt(&mp->m_sb) &&
	    xfs_sb_version_hasinobtcounts(&mp->m_sb)) अणु
		xfs_agblock_t	blocks;

		cur = xfs_inobt_init_cursor(mp, sc->tp, agi_bp, sc->sa.agno,
				XFS_BTNUM_FINO);
		error = xfs_btree_count_blocks(cur, &blocks);
		अगर (error)
			जाओ err;
		xfs_btree_del_cursor(cur, error);
		agi->agi_fblocks = cpu_to_be32(blocks);
	पूर्ण

	वापस 0;
err:
	xfs_btree_del_cursor(cur, error);
	वापस error;
पूर्ण

/* Trigger reinitialization of the in-core data. */
STATIC पूर्णांक
xrep_agi_commit_new(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*agi_bp)
अणु
	काष्ठा xfs_perag	*pag;
	काष्ठा xfs_agi		*agi = agi_bp->b_addr;

	/* Trigger inode count recalculation */
	xfs_क्रमce_summary_recalc(sc->mp);

	/* Write this to disk. */
	xfs_trans_buf_set_type(sc->tp, agi_bp, XFS_BLFT_AGI_BUF);
	xfs_trans_log_buf(sc->tp, agi_bp, 0, BBTOB(agi_bp->b_length) - 1);

	/* Now reinitialize the in-core counters अगर necessary. */
	pag = sc->sa.pag;
	pag->pagi_count = be32_to_cpu(agi->agi_count);
	pag->pagi_मुक्तcount = be32_to_cpu(agi->agi_मुक्तcount);
	pag->pagi_init = 1;

	वापस 0;
पूर्ण

/* Repair the AGI. */
पूर्णांक
xrep_agi(
	काष्ठा xfs_scrub		*sc)
अणु
	काष्ठा xrep_find_ag_btree	fab[XREP_AGI_MAX] = अणु
		[XREP_AGI_INOBT] = अणु
			.rmap_owner = XFS_RMAP_OWN_INOBT,
			.buf_ops = &xfs_inobt_buf_ops,
		पूर्ण,
		[XREP_AGI_FINOBT] = अणु
			.rmap_owner = XFS_RMAP_OWN_INOBT,
			.buf_ops = &xfs_finobt_buf_ops,
		पूर्ण,
		[XREP_AGI_END] = अणु
			.buf_ops = शून्य
		पूर्ण,
	पूर्ण;
	काष्ठा xfs_agi			old_agi;
	काष्ठा xfs_mount		*mp = sc->mp;
	काष्ठा xfs_buf			*agi_bp;
	काष्ठा xfs_agi			*agi;
	पूर्णांक				error;

	/* We require the rmapbt to rebuild anything. */
	अगर (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस -EOPNOTSUPP;

	xchk_perag_get(sc->mp, &sc->sa);
	/*
	 * Make sure we have the AGI buffer, as scrub might have decided it
	 * was corrupt after xfs_ialloc_पढ़ो_agi failed with -EFSCORRUPTED.
	 */
	error = xfs_trans_पढ़ो_buf(mp, sc->tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, sc->sa.agno, XFS_AGI_DADDR(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &agi_bp, शून्य);
	अगर (error)
		वापस error;
	agi_bp->b_ops = &xfs_agi_buf_ops;
	agi = agi_bp->b_addr;

	/* Find the AGI btree roots. */
	error = xrep_agi_find_btrees(sc, fab);
	अगर (error)
		वापस error;

	/* Start rewriting the header and implant the btrees we found. */
	xrep_agi_init_header(sc, agi_bp, &old_agi);
	xrep_agi_set_roots(sc, agi, fab);
	error = xrep_agi_calc_from_btrees(sc, agi_bp);
	अगर (error)
		जाओ out_revert;

	/* Reinitialize in-core state. */
	वापस xrep_agi_commit_new(sc, agi_bp);

out_revert:
	/* Mark the incore AGI state stale and revert the AGI. */
	sc->sa.pag->pagi_init = 0;
	स_नकल(agi, &old_agi, माप(old_agi));
	वापस error;
पूर्ण
