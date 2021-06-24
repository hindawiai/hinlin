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
#समावेश "xfs_btree.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_refcount.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/btree.h"

/*
 * Set us up to scrub reference count btrees.
 */
पूर्णांक
xchk_setup_ag_refcountbt(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_setup_ag_btree(sc, false);
पूर्ण

/* Reference count btree scrubber. */

/*
 * Confirming Reference Counts via Reverse Mappings
 *
 * We want to count the reverse mappings overlapping a refcount record
 * (bno, len, refcount), allowing क्रम the possibility that some of the
 * overlap may come from smaller adjoining reverse mappings, जबतक some
 * comes from single extents which overlap the range entirely.  The
 * outer loop is as follows:
 *
 * 1. For all reverse mappings overlapping the refcount extent,
 *    a. If a given rmap completely overlaps, mark it as seen.
 *    b. Otherwise, record the fragment (in agbno order) क्रम later
 *       processing.
 *
 * Once we've seen all the rmaps, we know that क्रम all blocks in the
 * refcount record we want to find $refcount owners and we've alपढ़ोy
 * visited $seen extents that overlap all the blocks.  Thereक्रमe, we
 * need to find ($refcount - $seen) owners क्रम every block in the
 * extent; call that quantity $target_nr.  Proceed as follows:
 *
 * 2. Pull the first $target_nr fragments from the list; all of them
 *    should start at or beक्रमe the start of the extent.
 *    Call this subset of fragments the working set.
 * 3. Until there are no more unprocessed fragments,
 *    a. Find the लघुest fragments in the set and हटाओ them.
 *    b. Note the block number of the end of these fragments.
 *    c. Pull the same number of fragments from the list.  All of these
 *       fragments should start at the block number recorded in the
 *       previous step.
 *    d. Put those fragments in the set.
 * 4. Check that there are $target_nr fragments reमुख्यing in the list,
 *    and that they all end at or beyond the end of the refcount extent.
 *
 * If the refcount is correct, all the check conditions in the algorithm
 * should always hold true.  If not, the refcount is incorrect.
 */
काष्ठा xchk_refcnt_frag अणु
	काष्ठा list_head	list;
	काष्ठा xfs_rmap_irec	rm;
पूर्ण;

काष्ठा xchk_refcnt_check अणु
	काष्ठा xfs_scrub	*sc;
	काष्ठा list_head	fragments;

	/* refcount extent we're examining */
	xfs_agblock_t		bno;
	xfs_extlen_t		len;
	xfs_nlink_t		refcount;

	/* number of owners seen */
	xfs_nlink_t		seen;
पूर्ण;

/*
 * Decide अगर the given rmap is large enough that we can redeem it
 * towards refcount verअगरication now, or अगर it's a fragment, in
 * which हाल we'll hang onto it in the hopes that we'll later
 * discover that we've collected exactly the correct number of
 * fragments as the refcountbt says we should have.
 */
STATIC पूर्णांक
xchk_refcountbt_rmap_check(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_rmap_irec		*rec,
	व्योम				*priv)
अणु
	काष्ठा xchk_refcnt_check	*refchk = priv;
	काष्ठा xchk_refcnt_frag		*frag;
	xfs_agblock_t			rm_last;
	xfs_agblock_t			rc_last;
	पूर्णांक				error = 0;

	अगर (xchk_should_terminate(refchk->sc, &error))
		वापस error;

	rm_last = rec->rm_startblock + rec->rm_blockcount - 1;
	rc_last = refchk->bno + refchk->len - 1;

	/* Confirm that a single-owner refc extent is a CoW stage. */
	अगर (refchk->refcount == 1 && rec->rm_owner != XFS_RMAP_OWN_COW) अणु
		xchk_btree_xref_set_corrupt(refchk->sc, cur, 0);
		वापस 0;
	पूर्ण

	अगर (rec->rm_startblock <= refchk->bno && rm_last >= rc_last) अणु
		/*
		 * The rmap overlaps the refcount record, so we can confirm
		 * one refcount owner seen.
		 */
		refchk->seen++;
	पूर्ण अन्यथा अणु
		/*
		 * This rmap covers only part of the refcount record, so
		 * save the fragment क्रम later processing.  If the rmapbt
		 * is healthy each rmap_irec we see will be in agbno order
		 * so we करोn't need insertion sort here.
		 */
		frag = kmem_alloc(माप(काष्ठा xchk_refcnt_frag),
				KM_MAYFAIL);
		अगर (!frag)
			वापस -ENOMEM;
		स_नकल(&frag->rm, rec, माप(frag->rm));
		list_add_tail(&frag->list, &refchk->fragments);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Given a bunch of rmap fragments, iterate through them, keeping
 * a running tally of the refcount.  If this ever deviates from
 * what we expect (which is the refcountbt's refcount minus the
 * number of extents that totally covered the refcountbt extent),
 * we have a refcountbt error.
 */
STATIC व्योम
xchk_refcountbt_process_rmap_fragments(
	काष्ठा xchk_refcnt_check	*refchk)
अणु
	काष्ठा list_head		worklist;
	काष्ठा xchk_refcnt_frag		*frag;
	काष्ठा xchk_refcnt_frag		*n;
	xfs_agblock_t			bno;
	xfs_agblock_t			rbno;
	xfs_agblock_t			next_rbno;
	xfs_nlink_t			nr;
	xfs_nlink_t			target_nr;

	target_nr = refchk->refcount - refchk->seen;
	अगर (target_nr == 0)
		वापस;

	/*
	 * There are (refchk->rc.rc_refcount - refchk->nr refcount)
	 * references we haven't found yet.  Pull that many off the
	 * fragment list and figure out where the smallest rmap ends
	 * (and thereक्रमe the next rmap should start).  All the rmaps
	 * we pull off should start at or beक्रमe the beginning of the
	 * refcount record's range.
	 */
	INIT_LIST_HEAD(&worklist);
	rbno = शून्यAGBLOCK;

	/* Make sure the fragments actually /are/ in agbno order. */
	bno = 0;
	list_क्रम_each_entry(frag, &refchk->fragments, list) अणु
		अगर (frag->rm.rm_startblock < bno)
			जाओ करोne;
		bno = frag->rm.rm_startblock;
	पूर्ण

	/*
	 * Find all the rmaps that start at or beक्रमe the refc extent,
	 * and put them on the worklist.
	 */
	nr = 0;
	list_क्रम_each_entry_safe(frag, n, &refchk->fragments, list) अणु
		अगर (frag->rm.rm_startblock > refchk->bno || nr > target_nr)
			अवरोध;
		bno = frag->rm.rm_startblock + frag->rm.rm_blockcount;
		अगर (bno < rbno)
			rbno = bno;
		list_move_tail(&frag->list, &worklist);
		nr++;
	पूर्ण

	/*
	 * We should have found exactly $target_nr rmap fragments starting
	 * at or beक्रमe the refcount extent.
	 */
	अगर (nr != target_nr)
		जाओ करोne;

	जबतक (!list_empty(&refchk->fragments)) अणु
		/* Discard any fragments ending at rbno from the worklist. */
		nr = 0;
		next_rbno = शून्यAGBLOCK;
		list_क्रम_each_entry_safe(frag, n, &worklist, list) अणु
			bno = frag->rm.rm_startblock + frag->rm.rm_blockcount;
			अगर (bno != rbno) अणु
				अगर (bno < next_rbno)
					next_rbno = bno;
				जारी;
			पूर्ण
			list_del(&frag->list);
			kmem_मुक्त(frag);
			nr++;
		पूर्ण

		/* Try to add nr rmaps starting at rbno to the worklist. */
		list_क्रम_each_entry_safe(frag, n, &refchk->fragments, list) अणु
			bno = frag->rm.rm_startblock + frag->rm.rm_blockcount;
			अगर (frag->rm.rm_startblock != rbno)
				जाओ करोne;
			list_move_tail(&frag->list, &worklist);
			अगर (next_rbno > bno)
				next_rbno = bno;
			nr--;
			अगर (nr == 0)
				अवरोध;
		पूर्ण

		/*
		 * If we get here and nr > 0, this means that we added fewer
		 * items to the worklist than we discarded because the fragment
		 * list ran out of items.  Thereक्रमe, we cannot मुख्यtain the
		 * required refcount.  Something is wrong, so we're करोne.
		 */
		अगर (nr)
			जाओ करोne;

		rbno = next_rbno;
	पूर्ण

	/*
	 * Make sure the last extent we processed ends at or beyond
	 * the end of the refcount extent.
	 */
	अगर (rbno < refchk->bno + refchk->len)
		जाओ करोne;

	/* Actually record us having seen the reमुख्यing refcount. */
	refchk->seen = refchk->refcount;
करोne:
	/* Delete fragments and work list. */
	list_क्रम_each_entry_safe(frag, n, &worklist, list) अणु
		list_del(&frag->list);
		kmem_मुक्त(frag);
	पूर्ण
	list_क्रम_each_entry_safe(frag, n, &refchk->fragments, list) अणु
		list_del(&frag->list);
		kmem_मुक्त(frag);
	पूर्ण
पूर्ण

/* Use the rmap entries covering this extent to verअगरy the refcount. */
STATIC व्योम
xchk_refcountbt_xref_rmap(
	काष्ठा xfs_scrub		*sc,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	xfs_nlink_t			refcount)
अणु
	काष्ठा xchk_refcnt_check	refchk = अणु
		.sc = sc,
		.bno = bno,
		.len = len,
		.refcount = refcount,
		.seen = 0,
	पूर्ण;
	काष्ठा xfs_rmap_irec		low;
	काष्ठा xfs_rmap_irec		high;
	काष्ठा xchk_refcnt_frag		*frag;
	काष्ठा xchk_refcnt_frag		*n;
	पूर्णांक				error;

	अगर (!sc->sa.rmap_cur || xchk_skip_xref(sc->sm))
		वापस;

	/* Cross-reference with the rmapbt to confirm the refcount. */
	स_रखो(&low, 0, माप(low));
	low.rm_startblock = bno;
	स_रखो(&high, 0xFF, माप(high));
	high.rm_startblock = bno + len - 1;

	INIT_LIST_HEAD(&refchk.fragments);
	error = xfs_rmap_query_range(sc->sa.rmap_cur, &low, &high,
			&xchk_refcountbt_rmap_check, &refchk);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.rmap_cur))
		जाओ out_मुक्त;

	xchk_refcountbt_process_rmap_fragments(&refchk);
	अगर (refcount != refchk.seen)
		xchk_btree_xref_set_corrupt(sc, sc->sa.rmap_cur, 0);

out_मुक्त:
	list_क्रम_each_entry_safe(frag, n, &refchk.fragments, list) अणु
		list_del(&frag->list);
		kmem_मुक्त(frag);
	पूर्ण
पूर्ण

/* Cross-reference with the other btrees. */
STATIC व्योम
xchk_refcountbt_xref(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len,
	xfs_nlink_t		refcount)
अणु
	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस;

	xchk_xref_is_used_space(sc, agbno, len);
	xchk_xref_is_not_inode_chunk(sc, agbno, len);
	xchk_refcountbt_xref_rmap(sc, agbno, len, refcount);
पूर्ण

/* Scrub a refcountbt record. */
STATIC पूर्णांक
xchk_refcountbt_rec(
	काष्ठा xchk_btree	*bs,
	जोड़ xfs_btree_rec	*rec)
अणु
	काष्ठा xfs_mount	*mp = bs->cur->bc_mp;
	xfs_agblock_t		*cow_blocks = bs->निजी;
	xfs_agnumber_t		agno = bs->cur->bc_ag.agno;
	xfs_agblock_t		bno;
	xfs_extlen_t		len;
	xfs_nlink_t		refcount;
	bool			has_cowflag;

	bno = be32_to_cpu(rec->refc.rc_startblock);
	len = be32_to_cpu(rec->refc.rc_blockcount);
	refcount = be32_to_cpu(rec->refc.rc_refcount);

	/* Only CoW records can have refcount == 1. */
	has_cowflag = (bno & XFS_REFC_COW_START);
	अगर ((refcount == 1 && !has_cowflag) || (refcount != 1 && has_cowflag))
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
	अगर (has_cowflag)
		(*cow_blocks) += len;

	/* Check the extent. */
	bno &= ~XFS_REFC_COW_START;
	अगर (bno + len <= bno ||
	    !xfs_verअगरy_agbno(mp, agno, bno) ||
	    !xfs_verअगरy_agbno(mp, agno, bno + len - 1))
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	अगर (refcount == 0)
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	xchk_refcountbt_xref(bs->sc, bno, len, refcount);

	वापस 0;
पूर्ण

/* Make sure we have as many refc blocks as the rmap says. */
STATIC व्योम
xchk_refcount_xref_rmap(
	काष्ठा xfs_scrub	*sc,
	xfs_filblks_t		cow_blocks)
अणु
	xfs_extlen_t		refcbt_blocks = 0;
	xfs_filblks_t		blocks;
	पूर्णांक			error;

	अगर (!sc->sa.rmap_cur || xchk_skip_xref(sc->sm))
		वापस;

	/* Check that we saw as many refcbt blocks as the rmap knows about. */
	error = xfs_btree_count_blocks(sc->sa.refc_cur, &refcbt_blocks);
	अगर (!xchk_btree_process_error(sc, sc->sa.refc_cur, 0, &error))
		वापस;
	error = xchk_count_rmap_ownedby_ag(sc, sc->sa.rmap_cur,
			&XFS_RMAP_OINFO_REFC, &blocks);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.rmap_cur))
		वापस;
	अगर (blocks != refcbt_blocks)
		xchk_btree_xref_set_corrupt(sc, sc->sa.rmap_cur, 0);

	/* Check that we saw as many cow blocks as the rmap knows about. */
	error = xchk_count_rmap_ownedby_ag(sc, sc->sa.rmap_cur,
			&XFS_RMAP_OINFO_COW, &blocks);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.rmap_cur))
		वापस;
	अगर (blocks != cow_blocks)
		xchk_btree_xref_set_corrupt(sc, sc->sa.rmap_cur, 0);
पूर्ण

/* Scrub the refcount btree क्रम some AG. */
पूर्णांक
xchk_refcountbt(
	काष्ठा xfs_scrub	*sc)
अणु
	xfs_agblock_t		cow_blocks = 0;
	पूर्णांक			error;

	error = xchk_btree(sc, sc->sa.refc_cur, xchk_refcountbt_rec,
			&XFS_RMAP_OINFO_REFC, &cow_blocks);
	अगर (error)
		वापस error;

	xchk_refcount_xref_rmap(sc, cow_blocks);

	वापस 0;
पूर्ण

/* xref check that a cow staging extent is marked in the refcountbt. */
व्योम
xchk_xref_is_cow_staging(
	काष्ठा xfs_scrub		*sc,
	xfs_agblock_t			agbno,
	xfs_extlen_t			len)
अणु
	काष्ठा xfs_refcount_irec	rc;
	bool				has_cowflag;
	पूर्णांक				has_refcount;
	पूर्णांक				error;

	अगर (!sc->sa.refc_cur || xchk_skip_xref(sc->sm))
		वापस;

	/* Find the CoW staging extent. */
	error = xfs_refcount_lookup_le(sc->sa.refc_cur,
			agbno + XFS_REFC_COW_START, &has_refcount);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.refc_cur))
		वापस;
	अगर (!has_refcount) अणु
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);
		वापस;
	पूर्ण

	error = xfs_refcount_get_rec(sc->sa.refc_cur, &rc, &has_refcount);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.refc_cur))
		वापस;
	अगर (!has_refcount) अणु
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);
		वापस;
	पूर्ण

	/* CoW flag must be set, refcount must be 1. */
	has_cowflag = (rc.rc_startblock & XFS_REFC_COW_START);
	अगर (!has_cowflag || rc.rc_refcount != 1)
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);

	/* Must be at least as दीर्घ as what was passed in */
	अगर (rc.rc_blockcount < len)
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);
पूर्ण

/*
 * xref check that the extent is not shared.  Only file data blocks
 * can have multiple owners.
 */
व्योम
xchk_xref_is_not_shared(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len)
अणु
	bool			shared;
	पूर्णांक			error;

	अगर (!sc->sa.refc_cur || xchk_skip_xref(sc->sm))
		वापस;

	error = xfs_refcount_has_record(sc->sa.refc_cur, agbno, len, &shared);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.refc_cur))
		वापस;
	अगर (shared)
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);
पूर्ण
