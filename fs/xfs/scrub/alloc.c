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
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_rmap.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/btree.h"

/*
 * Set us up to scrub मुक्त space btrees.
 */
पूर्णांक
xchk_setup_ag_allocbt(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_setup_ag_btree(sc, false);
पूर्ण

/* Free space btree scrubber. */
/*
 * Ensure there's a corresponding cntbt/bnobt record matching this
 * bnobt/cntbt record, respectively.
 */
STATIC व्योम
xchk_allocbt_xref_other(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len)
अणु
	काष्ठा xfs_btree_cur	**pcur;
	xfs_agblock_t		fbno;
	xfs_extlen_t		flen;
	पूर्णांक			has_otherrec;
	पूर्णांक			error;

	अगर (sc->sm->sm_type == XFS_SCRUB_TYPE_BNOBT)
		pcur = &sc->sa.cnt_cur;
	अन्यथा
		pcur = &sc->sa.bno_cur;
	अगर (!*pcur || xchk_skip_xref(sc->sm))
		वापस;

	error = xfs_alloc_lookup_le(*pcur, agbno, len, &has_otherrec);
	अगर (!xchk_should_check_xref(sc, &error, pcur))
		वापस;
	अगर (!has_otherrec) अणु
		xchk_btree_xref_set_corrupt(sc, *pcur, 0);
		वापस;
	पूर्ण

	error = xfs_alloc_get_rec(*pcur, &fbno, &flen, &has_otherrec);
	अगर (!xchk_should_check_xref(sc, &error, pcur))
		वापस;
	अगर (!has_otherrec) अणु
		xchk_btree_xref_set_corrupt(sc, *pcur, 0);
		वापस;
	पूर्ण

	अगर (fbno != agbno || flen != len)
		xchk_btree_xref_set_corrupt(sc, *pcur, 0);
पूर्ण

/* Cross-reference with the other btrees. */
STATIC व्योम
xchk_allocbt_xref(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len)
अणु
	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस;

	xchk_allocbt_xref_other(sc, agbno, len);
	xchk_xref_is_not_inode_chunk(sc, agbno, len);
	xchk_xref_has_no_owner(sc, agbno, len);
	xchk_xref_is_not_shared(sc, agbno, len);
पूर्ण

/* Scrub a bnobt/cntbt record. */
STATIC पूर्णांक
xchk_allocbt_rec(
	काष्ठा xchk_btree	*bs,
	जोड़ xfs_btree_rec	*rec)
अणु
	काष्ठा xfs_mount	*mp = bs->cur->bc_mp;
	xfs_agnumber_t		agno = bs->cur->bc_ag.agno;
	xfs_agblock_t		bno;
	xfs_extlen_t		len;

	bno = be32_to_cpu(rec->alloc.ar_startblock);
	len = be32_to_cpu(rec->alloc.ar_blockcount);

	अगर (bno + len <= bno ||
	    !xfs_verअगरy_agbno(mp, agno, bno) ||
	    !xfs_verअगरy_agbno(mp, agno, bno + len - 1))
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	xchk_allocbt_xref(bs->sc, bno, len);

	वापस 0;
पूर्ण

/* Scrub the मुक्तspace btrees क्रम some AG. */
STATIC पूर्णांक
xchk_allocbt(
	काष्ठा xfs_scrub	*sc,
	xfs_btnum_t		which)
अणु
	काष्ठा xfs_btree_cur	*cur;

	cur = which == XFS_BTNUM_BNO ? sc->sa.bno_cur : sc->sa.cnt_cur;
	वापस xchk_btree(sc, cur, xchk_allocbt_rec, &XFS_RMAP_OINFO_AG, शून्य);
पूर्ण

पूर्णांक
xchk_bnobt(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_allocbt(sc, XFS_BTNUM_BNO);
पूर्ण

पूर्णांक
xchk_cntbt(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_allocbt(sc, XFS_BTNUM_CNT);
पूर्ण

/* xref check that the extent is not मुक्त */
व्योम
xchk_xref_is_used_space(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len)
अणु
	bool			is_मुक्तsp;
	पूर्णांक			error;

	अगर (!sc->sa.bno_cur || xchk_skip_xref(sc->sm))
		वापस;

	error = xfs_alloc_has_record(sc->sa.bno_cur, agbno, len, &is_मुक्तsp);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.bno_cur))
		वापस;
	अगर (is_मुक्तsp)
		xchk_btree_xref_set_corrupt(sc, sc->sa.bno_cur, 0);
पूर्ण
