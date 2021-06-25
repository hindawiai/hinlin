<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2019 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_health.h"
#समावेश "xfs_btree.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/trace.h"

/*
 * FS Summary Counters
 * ===================
 *
 * The basics of fileप्रणाली summary counter checking are that we iterate the
 * AGs counting the number of मुक्त blocks, मुक्त space btree blocks, per-AG
 * reservations, inodes, delayed allocation reservations, and मुक्त inodes.
 * Then we compare what we computed against the in-core counters.
 *
 * However, the reality is that summary counters are a tricky beast to check.
 * While we /could/ मुक्तze the fileप्रणाली and scramble around the AGs counting
 * the मुक्त blocks, in practice we prefer not करो that क्रम a scan because
 * मुक्तzing is costly.  To get around this, we added a per-cpu counter of the
 * delalloc reservations so that we can rotor around the AGs relatively
 * quickly, and we allow the counts to be slightly off because we're not taking
 * any locks जबतक we करो this.
 *
 * So the first thing we करो is warm up the buffer cache in the setup routine by
 * walking all the AGs to make sure the incore per-AG काष्ठाure has been
 * initialized.  The expected value calculation then iterates the incore per-AG
 * काष्ठाures as quickly as it can.  We snapshot the percpu counters beक्रमe and
 * after this operation and use the dअगरference in counter values to guess at
 * our tolerance क्रम mismatch between expected and actual counter values.
 */

/*
 * Since the expected value computation is lockless but only browses incore
 * values, the percpu counters should be fairly बंद to each other.  However,
 * we'll allow ourselves to be off by at least this (arbitrary) amount.
 */
#घोषणा XCHK_FSCOUNT_MIN_VARIANCE	(512)

/*
 * Make sure the per-AG काष्ठाure has been initialized from the on-disk header
 * contents and trust that the incore counters match the ondisk counters.  (The
 * AGF and AGI scrubbers check them, and a normal xfs_scrub run checks the
 * summary counters after checking all AG headers).  Do this from the setup
 * function so that the inner AG aggregation loop runs as quickly as possible.
 *
 * This function runs during the setup phase /beक्रमe/ we start checking any
 * metadata.
 */
STATIC पूर्णांक
xchk_fscount_warmup(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_buf		*agi_bp = शून्य;
	काष्ठा xfs_buf		*agf_bp = शून्य;
	काष्ठा xfs_perag	*pag = शून्य;
	xfs_agnumber_t		agno;
	पूर्णांक			error = 0;

	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		pag = xfs_perag_get(mp, agno);

		अगर (pag->pagi_init && pag->pagf_init)
			जाओ next_loop_perag;

		/* Lock both AG headers. */
		error = xfs_ialloc_पढ़ो_agi(mp, sc->tp, agno, &agi_bp);
		अगर (error)
			अवरोध;
		error = xfs_alloc_पढ़ो_agf(mp, sc->tp, agno, 0, &agf_bp);
		अगर (error)
			अवरोध;

		/*
		 * These are supposed to be initialized by the header पढ़ो
		 * function.
		 */
		error = -EFSCORRUPTED;
		अगर (!pag->pagi_init || !pag->pagf_init)
			अवरोध;

		xfs_buf_rअन्यथा(agf_bp);
		agf_bp = शून्य;
		xfs_buf_rअन्यथा(agi_bp);
		agi_bp = शून्य;
next_loop_perag:
		xfs_perag_put(pag);
		pag = शून्य;
		error = 0;

		अगर (xchk_should_terminate(sc, &error))
			अवरोध;
	पूर्ण

	अगर (agf_bp)
		xfs_buf_rअन्यथा(agf_bp);
	अगर (agi_bp)
		xfs_buf_rअन्यथा(agi_bp);
	अगर (pag)
		xfs_perag_put(pag);
	वापस error;
पूर्ण

पूर्णांक
xchk_setup_fscounters(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xchk_fscounters	*fsc;
	पूर्णांक			error;

	sc->buf = kmem_zalloc(माप(काष्ठा xchk_fscounters), 0);
	अगर (!sc->buf)
		वापस -ENOMEM;
	fsc = sc->buf;

	xfs_icount_range(sc->mp, &fsc->icount_min, &fsc->icount_max);

	/* We must get the incore counters set up beक्रमe we can proceed. */
	error = xchk_fscount_warmup(sc);
	अगर (error)
		वापस error;

	/*
	 * Pause background reclaim जबतक we're scrubbing to reduce the
	 * likelihood of background perturbations to the counters throwing off
	 * our calculations.
	 */
	xchk_stop_reaping(sc);

	वापस xchk_trans_alloc(sc, 0);
पूर्ण

/* Count मुक्त space btree blocks manually क्रम pre-lazysbcount fileप्रणालीs. */
अटल पूर्णांक
xchk_fscount_btreeblks(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xchk_fscounters	*fsc,
	xfs_agnumber_t		agno)
अणु
	xfs_extlen_t		blocks;
	पूर्णांक			error;

	error = xchk_ag_init(sc, agno, &sc->sa);
	अगर (error)
		वापस error;

	error = xfs_btree_count_blocks(sc->sa.bno_cur, &blocks);
	अगर (error)
		जाओ out_मुक्त;
	fsc->fdblocks += blocks - 1;

	error = xfs_btree_count_blocks(sc->sa.cnt_cur, &blocks);
	अगर (error)
		जाओ out_मुक्त;
	fsc->fdblocks += blocks - 1;

out_मुक्त:
	xchk_ag_मुक्त(sc, &sc->sa);
	वापस error;
पूर्ण

/*
 * Calculate what the global in-core counters ought to be from the incore
 * per-AG काष्ठाure.  Callers can compare this to the actual in-core counters
 * to estimate by how much both in-core and on-disk counters need to be
 * adjusted.
 */
STATIC पूर्णांक
xchk_fscount_aggregate_agcounts(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xchk_fscounters	*fsc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_perag	*pag;
	uपूर्णांक64_t		delayed;
	xfs_agnumber_t		agno;
	पूर्णांक			tries = 8;
	पूर्णांक			error = 0;

retry:
	fsc->icount = 0;
	fsc->अगरree = 0;
	fsc->fdblocks = 0;

	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		pag = xfs_perag_get(mp, agno);

		/* This somehow got unset since the warmup? */
		अगर (!pag->pagi_init || !pag->pagf_init) अणु
			xfs_perag_put(pag);
			वापस -EFSCORRUPTED;
		पूर्ण

		/* Count all the inodes */
		fsc->icount += pag->pagi_count;
		fsc->अगरree += pag->pagi_मुक्तcount;

		/* Add up the मुक्त/मुक्तlist/bnobt/cntbt blocks */
		fsc->fdblocks += pag->pagf_मुक्तblks;
		fsc->fdblocks += pag->pagf_flcount;
		अगर (xfs_sb_version_haslazysbcount(&sc->mp->m_sb)) अणु
			fsc->fdblocks += pag->pagf_btreeblks;
		पूर्ण अन्यथा अणु
			error = xchk_fscount_btreeblks(sc, fsc, agno);
			अगर (error) अणु
				xfs_perag_put(pag);
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * Per-AG reservations are taken out of the incore counters,
		 * so they must be left out of the मुक्त blocks computation.
		 */
		fsc->fdblocks -= pag->pag_meta_resv.ar_reserved;
		fsc->fdblocks -= pag->pag_rmapbt_resv.ar_orig_reserved;

		xfs_perag_put(pag);

		अगर (xchk_should_terminate(sc, &error))
			अवरोध;
	पूर्ण

	अगर (error)
		वापस error;

	/*
	 * The global incore space reservation is taken from the incore
	 * counters, so leave that out of the computation.
	 */
	fsc->fdblocks -= mp->m_resblks_avail;

	/*
	 * Delayed allocation reservations are taken out of the incore counters
	 * but not recorded on disk, so leave them and their indlen blocks out
	 * of the computation.
	 */
	delayed = percpu_counter_sum(&mp->m_delalloc_blks);
	fsc->fdblocks -= delayed;

	trace_xchk_fscounters_calc(mp, fsc->icount, fsc->अगरree, fsc->fdblocks,
			delayed);


	/* Bail out अगर the values we compute are totally nonsense. */
	अगर (fsc->icount < fsc->icount_min || fsc->icount > fsc->icount_max ||
	    fsc->fdblocks > mp->m_sb.sb_dblocks ||
	    fsc->अगरree > fsc->icount_max)
		वापस -EFSCORRUPTED;

	/*
	 * If अगरree > icount then we probably had some perturbation in the
	 * counters जबतक we were calculating things.  We'll try a few बार
	 * to मुख्यtain अगरree <= icount beक्रमe giving up.
	 */
	अगर (fsc->अगरree > fsc->icount) अणु
		अगर (tries--)
			जाओ retry;
		xchk_set_incomplete(sc);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Is the @counter reasonably बंद to the @expected value?
 *
 * We neither locked nor froze anything in the fileप्रणाली जबतक aggregating the
 * per-AG data to compute the @expected value, which means that the counter
 * could have changed.  We know the @old_value of the summation of the counter
 * beक्रमe the aggregation, and we re-sum the counter now.  If the expected
 * value falls between the two summations, we're ok.
 *
 * Otherwise, we /might/ have a problem.  If the change in the summations is
 * more than we want to tolerate, the fileप्रणाली is probably busy and we should
 * just send back INCOMPLETE and see अगर userspace will try again.
 */
अटल अंतरभूत bool
xchk_fscount_within_range(
	काष्ठा xfs_scrub	*sc,
	स्थिर पूर्णांक64_t		old_value,
	काष्ठा percpu_counter	*counter,
	uपूर्णांक64_t		expected)
अणु
	पूर्णांक64_t			min_value, max_value;
	पूर्णांक64_t			curr_value = percpu_counter_sum(counter);

	trace_xchk_fscounters_within_range(sc->mp, expected, curr_value,
			old_value);

	/* Negative values are always wrong. */
	अगर (curr_value < 0)
		वापस false;

	/* Exact matches are always ok. */
	अगर (curr_value == expected)
		वापस true;

	min_value = min(old_value, curr_value);
	max_value = max(old_value, curr_value);

	/* Within the beक्रमe-and-after range is ok. */
	अगर (expected >= min_value && expected <= max_value)
		वापस true;

	/*
	 * If the dअगरference between the two summations is too large, the fs
	 * might just be busy and so we'll mark the scrub incomplete.  Return
	 * true here so that we करोn't mark the counter corrupt.
	 *
	 * XXX: In the future when userspace can grant scrub permission to
	 * quiesce the fileप्रणाली to solve the outsized variance problem, this
	 * check should be moved up and the वापस code changed to संकेत to
	 * userspace that we need quiesce permission.
	 */
	अगर (max_value - min_value >= XCHK_FSCOUNT_MIN_VARIANCE) अणु
		xchk_set_incomplete(sc);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Check the superblock counters. */
पूर्णांक
xchk_fscounters(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xchk_fscounters	*fsc = sc->buf;
	पूर्णांक64_t			icount, अगरree, fdblocks;
	पूर्णांक			error;

	/* Snapshot the percpu counters. */
	icount = percpu_counter_sum(&mp->m_icount);
	अगरree = percpu_counter_sum(&mp->m_अगरree);
	fdblocks = percpu_counter_sum(&mp->m_fdblocks);

	/* No negative values, please! */
	अगर (icount < 0 || अगरree < 0 || fdblocks < 0)
		xchk_set_corrupt(sc);

	/* See अगर icount is obviously wrong. */
	अगर (icount < fsc->icount_min || icount > fsc->icount_max)
		xchk_set_corrupt(sc);

	/* See अगर fdblocks is obviously wrong. */
	अगर (fdblocks > mp->m_sb.sb_dblocks)
		xchk_set_corrupt(sc);

	/*
	 * If अगरree exceeds icount by more than the minimum variance then
	 * something's probably wrong with the counters.
	 */
	अगर (अगरree > icount && अगरree - icount > XCHK_FSCOUNT_MIN_VARIANCE)
		xchk_set_corrupt(sc);

	/* Walk the incore AG headers to calculate the expected counters. */
	error = xchk_fscount_aggregate_agcounts(sc, fsc);
	अगर (!xchk_process_error(sc, 0, XFS_SB_BLOCK(mp), &error))
		वापस error;
	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_INCOMPLETE)
		वापस 0;

	/* Compare the in-core counters with whatever we counted. */
	अगर (!xchk_fscount_within_range(sc, icount, &mp->m_icount, fsc->icount))
		xchk_set_corrupt(sc);

	अगर (!xchk_fscount_within_range(sc, अगरree, &mp->m_अगरree, fsc->अगरree))
		xchk_set_corrupt(sc);

	अगर (!xchk_fscount_within_range(sc, fdblocks, &mp->m_fdblocks,
			fsc->fdblocks))
		xchk_set_corrupt(sc);

	वापस 0;
पूर्ण
