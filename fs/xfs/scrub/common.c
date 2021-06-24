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
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_alloc_btree.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_ialloc_btree.h"
#समावेश "xfs_refcount_btree.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "xfs_log.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_reflink.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/trace.h"
#समावेश "scrub/repair.h"
#समावेश "scrub/health.h"

/* Common code क्रम the metadata scrubbers. */

/*
 * Handling operational errors.
 *
 * The *_process_error() family of functions are used to process error वापस
 * codes from functions called as part of a scrub operation.
 *
 * If there's no error, we return true to tell the caller that it's ok
 * to move on to the next check in its list.
 *
 * For non-verअगरier errors (e.g. ENOMEM) we वापस false to tell the
 * caller that something bad happened, and we preserve *error so that
 * the caller can वापस the *error up the stack to userspace.
 *
 * Verअगरier errors (EFSBADCRC/EFSCORRUPTED) are recorded by setting
 * OFLAG_CORRUPT in sm_flags and the *error is cleared.  In other words,
 * we track verअगरier errors (and failed scrub checks) via OFLAG_CORRUPT,
 * not via वापस codes.  We वापस false to tell the caller that
 * something bad happened.  Since the error has been cleared, the caller
 * will (presumably) वापस that zero and scrubbing will move on to
 * whatever's next.
 *
 * ftrace can be used to record the precise metadata location and the
 * approximate code location of the failed operation.
 */

/* Check क्रम operational errors. */
अटल bool
__xchk_process_error(
	काष्ठा xfs_scrub	*sc,
	xfs_agnumber_t		agno,
	xfs_agblock_t		bno,
	पूर्णांक			*error,
	__u32			errflag,
	व्योम			*ret_ip)
अणु
	चयन (*error) अणु
	हाल 0:
		वापस true;
	हाल -EDEADLOCK:
		/* Used to restart an op with deadlock aव्योमance. */
		trace_xchk_deadlock_retry(
				sc->ip ? sc->ip : XFS_I(file_inode(sc->file)),
				sc->sm, *error);
		अवरोध;
	हाल -EFSBADCRC:
	हाल -EFSCORRUPTED:
		/* Note the badness but करोn't पात. */
		sc->sm->sm_flags |= errflag;
		*error = 0;
		/* fall through */
	शेष:
		trace_xchk_op_error(sc, agno, bno, *error,
				ret_ip);
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

bool
xchk_process_error(
	काष्ठा xfs_scrub	*sc,
	xfs_agnumber_t		agno,
	xfs_agblock_t		bno,
	पूर्णांक			*error)
अणु
	वापस __xchk_process_error(sc, agno, bno, error,
			XFS_SCRUB_OFLAG_CORRUPT, __वापस_address);
पूर्ण

bool
xchk_xref_process_error(
	काष्ठा xfs_scrub	*sc,
	xfs_agnumber_t		agno,
	xfs_agblock_t		bno,
	पूर्णांक			*error)
अणु
	वापस __xchk_process_error(sc, agno, bno, error,
			XFS_SCRUB_OFLAG_XFAIL, __वापस_address);
पूर्ण

/* Check क्रम operational errors क्रम a file offset. */
अटल bool
__xchk_fblock_process_error(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			whichविभाजन,
	xfs_fileoff_t		offset,
	पूर्णांक			*error,
	__u32			errflag,
	व्योम			*ret_ip)
अणु
	चयन (*error) अणु
	हाल 0:
		वापस true;
	हाल -EDEADLOCK:
		/* Used to restart an op with deadlock aव्योमance. */
		trace_xchk_deadlock_retry(sc->ip, sc->sm, *error);
		अवरोध;
	हाल -EFSBADCRC:
	हाल -EFSCORRUPTED:
		/* Note the badness but करोn't पात. */
		sc->sm->sm_flags |= errflag;
		*error = 0;
		/* fall through */
	शेष:
		trace_xchk_file_op_error(sc, whichविभाजन, offset, *error,
				ret_ip);
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

bool
xchk_fblock_process_error(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			whichविभाजन,
	xfs_fileoff_t		offset,
	पूर्णांक			*error)
अणु
	वापस __xchk_fblock_process_error(sc, whichविभाजन, offset, error,
			XFS_SCRUB_OFLAG_CORRUPT, __वापस_address);
पूर्ण

bool
xchk_fblock_xref_process_error(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			whichविभाजन,
	xfs_fileoff_t		offset,
	पूर्णांक			*error)
अणु
	वापस __xchk_fblock_process_error(sc, whichविभाजन, offset, error,
			XFS_SCRUB_OFLAG_XFAIL, __वापस_address);
पूर्ण

/*
 * Handling scrub corruption/optimization/warning checks.
 *
 * The *_set_अणुcorrupt,preen,warningपूर्ण() family of functions are used to
 * record the presence of metadata that is incorrect (corrupt), could be
 * optimized somehow (preen), or should be flagged क्रम administrative
 * review but is not incorrect (warn).
 *
 * ftrace can be used to record the precise metadata location and
 * approximate code location of the failed check.
 */

/* Record a block which could be optimized. */
व्योम
xchk_block_set_preen(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*bp)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_PREEN;
	trace_xchk_block_preen(sc, bp->b_bn, __वापस_address);
पूर्ण

/*
 * Record an inode which could be optimized.  The trace data will
 * include the block given by bp अगर bp is given; otherwise it will use
 * the block location of the inode record itself.
 */
व्योम
xchk_ino_set_preen(
	काष्ठा xfs_scrub	*sc,
	xfs_ino_t		ino)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_PREEN;
	trace_xchk_ino_preen(sc, ino, __वापस_address);
पूर्ण

/* Record something being wrong with the fileप्रणाली primary superblock. */
व्योम
xchk_set_corrupt(
	काष्ठा xfs_scrub	*sc)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_CORRUPT;
	trace_xchk_fs_error(sc, 0, __वापस_address);
पूर्ण

/* Record a corrupt block. */
व्योम
xchk_block_set_corrupt(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*bp)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_CORRUPT;
	trace_xchk_block_error(sc, bp->b_bn, __वापस_address);
पूर्ण

/* Record a corruption जबतक cross-referencing. */
व्योम
xchk_block_xref_set_corrupt(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*bp)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_XCORRUPT;
	trace_xchk_block_error(sc, bp->b_bn, __वापस_address);
पूर्ण

/*
 * Record a corrupt inode.  The trace data will include the block given
 * by bp अगर bp is given; otherwise it will use the block location of the
 * inode record itself.
 */
व्योम
xchk_ino_set_corrupt(
	काष्ठा xfs_scrub	*sc,
	xfs_ino_t		ino)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_CORRUPT;
	trace_xchk_ino_error(sc, ino, __वापस_address);
पूर्ण

/* Record a corruption जबतक cross-referencing with an inode. */
व्योम
xchk_ino_xref_set_corrupt(
	काष्ठा xfs_scrub	*sc,
	xfs_ino_t		ino)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_XCORRUPT;
	trace_xchk_ino_error(sc, ino, __वापस_address);
पूर्ण

/* Record corruption in a block indexed by a file विभाजन. */
व्योम
xchk_fblock_set_corrupt(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			whichविभाजन,
	xfs_fileoff_t		offset)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_CORRUPT;
	trace_xchk_fblock_error(sc, whichविभाजन, offset, __वापस_address);
पूर्ण

/* Record a corruption जबतक cross-referencing a विभाजन block. */
व्योम
xchk_fblock_xref_set_corrupt(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			whichविभाजन,
	xfs_fileoff_t		offset)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_XCORRUPT;
	trace_xchk_fblock_error(sc, whichविभाजन, offset, __वापस_address);
पूर्ण

/*
 * Warn about inodes that need administrative review but is not
 * incorrect.
 */
व्योम
xchk_ino_set_warning(
	काष्ठा xfs_scrub	*sc,
	xfs_ino_t		ino)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_WARNING;
	trace_xchk_ino_warning(sc, ino, __वापस_address);
पूर्ण

/* Warn about a block indexed by a file विभाजन that needs review. */
व्योम
xchk_fblock_set_warning(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			whichविभाजन,
	xfs_fileoff_t		offset)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_WARNING;
	trace_xchk_fblock_warning(sc, whichविभाजन, offset, __वापस_address);
पूर्ण

/* Signal an incomplete scrub. */
व्योम
xchk_set_incomplete(
	काष्ठा xfs_scrub	*sc)
अणु
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_INCOMPLETE;
	trace_xchk_incomplete(sc, __वापस_address);
पूर्ण

/*
 * rmap scrubbing -- compute the number of blocks with a given owner,
 * at least according to the reverse mapping data.
 */

काष्ठा xchk_rmap_ownedby_info अणु
	स्थिर काष्ठा xfs_owner_info	*oinfo;
	xfs_filblks_t			*blocks;
पूर्ण;

STATIC पूर्णांक
xchk_count_rmap_ownedby_irec(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_rmap_irec		*rec,
	व्योम				*priv)
अणु
	काष्ठा xchk_rmap_ownedby_info	*sroi = priv;
	bool				irec_attr;
	bool				oinfo_attr;

	irec_attr = rec->rm_flags & XFS_RMAP_ATTR_FORK;
	oinfo_attr = sroi->oinfo->oi_flags & XFS_OWNER_INFO_ATTR_FORK;

	अगर (rec->rm_owner != sroi->oinfo->oi_owner)
		वापस 0;

	अगर (XFS_RMAP_NON_INODE_OWNER(rec->rm_owner) || irec_attr == oinfo_attr)
		(*sroi->blocks) += rec->rm_blockcount;

	वापस 0;
पूर्ण

/*
 * Calculate the number of blocks the rmap thinks are owned by something.
 * The caller should pass us an rmapbt cursor.
 */
पूर्णांक
xchk_count_rmap_ownedby_ag(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xfs_btree_cur		*cur,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	xfs_filblks_t			*blocks)
अणु
	काष्ठा xchk_rmap_ownedby_info	sroi = अणु
		.oinfo			= oinfo,
		.blocks			= blocks,
	पूर्ण;

	*blocks = 0;
	वापस xfs_rmap_query_all(cur, xchk_count_rmap_ownedby_irec,
			&sroi);
पूर्ण

/*
 * AG scrubbing
 *
 * These helpers facilitate locking an allocation group's header
 * buffers, setting up cursors क्रम all btrees that are present, and
 * cleaning everything up once we're through.
 */

/* Decide अगर we want to वापस an AG header पढ़ो failure. */
अटल अंतरभूत bool
want_ag_पढ़ो_header_failure(
	काष्ठा xfs_scrub	*sc,
	अचिन्हित पूर्णांक		type)
अणु
	/* Return all AG header पढ़ो failures when scanning btrees. */
	अगर (sc->sm->sm_type != XFS_SCRUB_TYPE_AGF &&
	    sc->sm->sm_type != XFS_SCRUB_TYPE_AGFL &&
	    sc->sm->sm_type != XFS_SCRUB_TYPE_AGI)
		वापस true;
	/*
	 * If we're scanning a given type of AG header, we only want to
	 * see पढ़ो failures from that specअगरic header.  We'd like the
	 * other headers to cross-check them, but this isn't required.
	 */
	अगर (sc->sm->sm_type == type)
		वापस true;
	वापस false;
पूर्ण

/*
 * Grab all the headers क्रम an AG.
 *
 * The headers should be released by xchk_ag_मुक्त, but as a fail
 * safe we attach all the buffers we grab to the scrub transaction so
 * they'll all be मुक्तd when we cancel it.
 */
पूर्णांक
xchk_ag_पढ़ो_headers(
	काष्ठा xfs_scrub	*sc,
	xfs_agnumber_t		agno,
	काष्ठा xchk_ag		*sa)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	पूर्णांक			error;

	sa->agno = agno;

	error = xfs_ialloc_पढ़ो_agi(mp, sc->tp, agno, &sa->agi_bp);
	अगर (error && want_ag_पढ़ो_header_failure(sc, XFS_SCRUB_TYPE_AGI))
		जाओ out;

	error = xfs_alloc_पढ़ो_agf(mp, sc->tp, agno, 0, &sa->agf_bp);
	अगर (error && want_ag_पढ़ो_header_failure(sc, XFS_SCRUB_TYPE_AGF))
		जाओ out;

	error = xfs_alloc_पढ़ो_agfl(mp, sc->tp, agno, &sa->agfl_bp);
	अगर (error && want_ag_पढ़ो_header_failure(sc, XFS_SCRUB_TYPE_AGFL))
		जाओ out;
	error = 0;
out:
	वापस error;
पूर्ण

/* Release all the AG btree cursors. */
व्योम
xchk_ag_btcur_मुक्त(
	काष्ठा xchk_ag		*sa)
अणु
	अगर (sa->refc_cur)
		xfs_btree_del_cursor(sa->refc_cur, XFS_BTREE_ERROR);
	अगर (sa->rmap_cur)
		xfs_btree_del_cursor(sa->rmap_cur, XFS_BTREE_ERROR);
	अगर (sa->fino_cur)
		xfs_btree_del_cursor(sa->fino_cur, XFS_BTREE_ERROR);
	अगर (sa->ino_cur)
		xfs_btree_del_cursor(sa->ino_cur, XFS_BTREE_ERROR);
	अगर (sa->cnt_cur)
		xfs_btree_del_cursor(sa->cnt_cur, XFS_BTREE_ERROR);
	अगर (sa->bno_cur)
		xfs_btree_del_cursor(sa->bno_cur, XFS_BTREE_ERROR);

	sa->refc_cur = शून्य;
	sa->rmap_cur = शून्य;
	sa->fino_cur = शून्य;
	sa->ino_cur = शून्य;
	sa->bno_cur = शून्य;
	sa->cnt_cur = शून्य;
पूर्ण

/* Initialize all the btree cursors क्रम an AG. */
व्योम
xchk_ag_btcur_init(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xchk_ag		*sa)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	xfs_agnumber_t		agno = sa->agno;

	xchk_perag_get(sc->mp, sa);
	अगर (sa->agf_bp &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_BNO)) अणु
		/* Set up a bnobt cursor क्रम cross-referencing. */
		sa->bno_cur = xfs_allocbt_init_cursor(mp, sc->tp, sa->agf_bp,
				agno, XFS_BTNUM_BNO);
	पूर्ण

	अगर (sa->agf_bp &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_CNT)) अणु
		/* Set up a cntbt cursor क्रम cross-referencing. */
		sa->cnt_cur = xfs_allocbt_init_cursor(mp, sc->tp, sa->agf_bp,
				agno, XFS_BTNUM_CNT);
	पूर्ण

	/* Set up a inobt cursor क्रम cross-referencing. */
	अगर (sa->agi_bp &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_INO)) अणु
		sa->ino_cur = xfs_inobt_init_cursor(mp, sc->tp, sa->agi_bp,
					agno, XFS_BTNUM_INO);
	पूर्ण

	/* Set up a finobt cursor क्रम cross-referencing. */
	अगर (sa->agi_bp && xfs_sb_version_hasfinobt(&mp->m_sb) &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_FINO)) अणु
		sa->fino_cur = xfs_inobt_init_cursor(mp, sc->tp, sa->agi_bp,
				agno, XFS_BTNUM_FINO);
	पूर्ण

	/* Set up a rmapbt cursor क्रम cross-referencing. */
	अगर (sa->agf_bp && xfs_sb_version_hasrmapbt(&mp->m_sb) &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_RMAP)) अणु
		sa->rmap_cur = xfs_rmapbt_init_cursor(mp, sc->tp, sa->agf_bp,
				agno);
	पूर्ण

	/* Set up a refcountbt cursor क्रम cross-referencing. */
	अगर (sa->agf_bp && xfs_sb_version_hasreflink(&mp->m_sb) &&
	    xchk_ag_btree_healthy_enough(sc, sa->pag, XFS_BTNUM_REFC)) अणु
		sa->refc_cur = xfs_refcountbt_init_cursor(mp, sc->tp,
				sa->agf_bp, agno);
	पूर्ण
पूर्ण

/* Release the AG header context and btree cursors. */
व्योम
xchk_ag_मुक्त(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xchk_ag		*sa)
अणु
	xchk_ag_btcur_मुक्त(sa);
	अगर (sa->agfl_bp) अणु
		xfs_trans_brअन्यथा(sc->tp, sa->agfl_bp);
		sa->agfl_bp = शून्य;
	पूर्ण
	अगर (sa->agf_bp) अणु
		xfs_trans_brअन्यथा(sc->tp, sa->agf_bp);
		sa->agf_bp = शून्य;
	पूर्ण
	अगर (sa->agi_bp) अणु
		xfs_trans_brअन्यथा(sc->tp, sa->agi_bp);
		sa->agi_bp = शून्य;
	पूर्ण
	अगर (sa->pag) अणु
		xfs_perag_put(sa->pag);
		sa->pag = शून्य;
	पूर्ण
	sa->agno = शून्यAGNUMBER;
पूर्ण

/*
 * For scrub, grab the AGI and the AGF headers, in that order.  Locking
 * order requires us to get the AGI beक्रमe the AGF.  We use the
 * transaction to aव्योम deadlocking on crosslinked metadata buffers;
 * either the caller passes one in (bmap scrub) or we have to create a
 * transaction ourselves.
 */
पूर्णांक
xchk_ag_init(
	काष्ठा xfs_scrub	*sc,
	xfs_agnumber_t		agno,
	काष्ठा xchk_ag		*sa)
अणु
	पूर्णांक			error;

	error = xchk_ag_पढ़ो_headers(sc, agno, sa);
	अगर (error)
		वापस error;

	xchk_ag_btcur_init(sc, sa);
	वापस 0;
पूर्ण

/*
 * Grab the per-ag काष्ठाure अगर we haven't alपढ़ोy gotten it.  Tearकरोwn of the
 * xchk_ag will release it क्रम us.
 */
व्योम
xchk_perag_get(
	काष्ठा xfs_mount	*mp,
	काष्ठा xchk_ag		*sa)
अणु
	अगर (!sa->pag)
		sa->pag = xfs_perag_get(mp, sa->agno);
पूर्ण

/* Per-scrubber setup functions */

/*
 * Grab an empty transaction so that we can re-grab locked buffers अगर
 * one of our btrees turns out to be cyclic.
 *
 * If we're going to repair something, we need to ask क्रम the largest possible
 * log reservation so that we can handle the worst हाल scenario क्रम metadata
 * updates जबतक rebuilding a metadata item.  We also need to reserve as many
 * blocks in the head transaction as we think we're going to need to rebuild
 * the metadata object.
 */
पूर्णांक
xchk_trans_alloc(
	काष्ठा xfs_scrub	*sc,
	uपूर्णांक			resblks)
अणु
	अगर (sc->sm->sm_flags & XFS_SCRUB_IFLAG_REPAIR)
		वापस xfs_trans_alloc(sc->mp, &M_RES(sc->mp)->tr_itruncate,
				resblks, 0, 0, &sc->tp);

	वापस xfs_trans_alloc_empty(sc->mp, &sc->tp);
पूर्ण

/* Set us up with a transaction and an empty context. */
पूर्णांक
xchk_setup_fs(
	काष्ठा xfs_scrub	*sc)
अणु
	uपूर्णांक			resblks;

	resblks = xrep_calc_ag_resblks(sc);
	वापस xchk_trans_alloc(sc, resblks);
पूर्ण

/* Set us up with AG headers and btree cursors. */
पूर्णांक
xchk_setup_ag_btree(
	काष्ठा xfs_scrub	*sc,
	bool			क्रमce_log)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	पूर्णांक			error;

	/*
	 * If the caller asks us to checkpont the log, करो so.  This
	 * expensive operation should be perक्रमmed infrequently and only
	 * as a last resort.  Any caller that sets क्रमce_log should
	 * करोcument why they need to करो so.
	 */
	अगर (क्रमce_log) अणु
		error = xchk_checkpoपूर्णांक_log(mp);
		अगर (error)
			वापस error;
	पूर्ण

	error = xchk_setup_fs(sc);
	अगर (error)
		वापस error;

	वापस xchk_ag_init(sc, sc->sm->sm_agno, &sc->sa);
पूर्ण

/* Push everything out of the log onto disk. */
पूर्णांक
xchk_checkpoपूर्णांक_log(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक			error;

	error = xfs_log_क्रमce(mp, XFS_LOG_SYNC);
	अगर (error)
		वापस error;
	xfs_ail_push_all_sync(mp->m_ail);
	वापस 0;
पूर्ण

/*
 * Given an inode and the scrub control काष्ठाure, grab either the
 * inode referenced in the control काष्ठाure or the inode passed in.
 * The inode is not locked.
 */
पूर्णांक
xchk_get_inode(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_imap		imap;
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_inode	*ip_in = XFS_I(file_inode(sc->file));
	काष्ठा xfs_inode	*ip = शून्य;
	पूर्णांक			error;

	/* We want to scan the inode we alपढ़ोy had खोलोed. */
	अगर (sc->sm->sm_ino == 0 || sc->sm->sm_ino == ip_in->i_ino) अणु
		sc->ip = ip_in;
		वापस 0;
	पूर्ण

	/* Look up the inode, see अगर the generation number matches. */
	अगर (xfs_पूर्णांकernal_inum(mp, sc->sm->sm_ino))
		वापस -ENOENT;
	error = xfs_iget(mp, शून्य, sc->sm->sm_ino,
			XFS_IGET_UNTRUSTED | XFS_IGET_DONTCACHE, 0, &ip);
	चयन (error) अणु
	हाल -ENOENT:
		/* Inode करोesn't exist, just bail out. */
		वापस error;
	हाल 0:
		/* Got an inode, जारी. */
		अवरोध;
	हाल -EINVAL:
		/*
		 * -EINVAL with IGET_UNTRUSTED could mean one of several
		 * things: userspace gave us an inode number that करोesn't
		 * correspond to fs space, or करोesn't have an inobt entry;
		 * or it could simply mean that the inode buffer failed the
		 * पढ़ो verअगरiers.
		 *
		 * Try just the inode mapping lookup -- अगर it succeeds, then
		 * the inode buffer verअगरier failed and something needs fixing.
		 * Otherwise, we really couldn't find it so tell userspace
		 * that it no दीर्घer exists.
		 */
		error = xfs_imap(sc->mp, sc->tp, sc->sm->sm_ino, &imap,
				XFS_IGET_UNTRUSTED | XFS_IGET_DONTCACHE);
		अगर (error)
			वापस -ENOENT;
		error = -EFSCORRUPTED;
		/* fall through */
	शेष:
		trace_xchk_op_error(sc,
				XFS_INO_TO_AGNO(mp, sc->sm->sm_ino),
				XFS_INO_TO_AGBNO(mp, sc->sm->sm_ino),
				error, __वापस_address);
		वापस error;
	पूर्ण
	अगर (VFS_I(ip)->i_generation != sc->sm->sm_gen) अणु
		xfs_irele(ip);
		वापस -ENOENT;
	पूर्ण

	sc->ip = ip;
	वापस 0;
पूर्ण

/* Set us up to scrub a file's contents. */
पूर्णांक
xchk_setup_inode_contents(
	काष्ठा xfs_scrub	*sc,
	अचिन्हित पूर्णांक		resblks)
अणु
	पूर्णांक			error;

	error = xchk_get_inode(sc);
	अगर (error)
		वापस error;

	/* Got the inode, lock it and we're पढ़ोy to go. */
	sc->ilock_flags = XFS_IOLOCK_EXCL | XFS_MMAPLOCK_EXCL;
	xfs_ilock(sc->ip, sc->ilock_flags);
	error = xchk_trans_alloc(sc, resblks);
	अगर (error)
		जाओ out;
	sc->ilock_flags |= XFS_ILOCK_EXCL;
	xfs_ilock(sc->ip, XFS_ILOCK_EXCL);

out:
	/* scrub tearकरोwn will unlock and release the inode क्रम us */
	वापस error;
पूर्ण

/*
 * Predicate that decides अगर we need to evaluate the cross-reference check.
 * If there was an error accessing the cross-reference btree, just delete
 * the cursor and skip the check.
 */
bool
xchk_should_check_xref(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			*error,
	काष्ठा xfs_btree_cur	**curpp)
अणु
	/* No poपूर्णांक in xref अगर we alपढ़ोy know we're corrupt. */
	अगर (xchk_skip_xref(sc->sm))
		वापस false;

	अगर (*error == 0)
		वापस true;

	अगर (curpp) अणु
		/* If we've alपढ़ोy given up on xref, just bail out. */
		अगर (!*curpp)
			वापस false;

		/* xref error, delete cursor and bail out. */
		xfs_btree_del_cursor(*curpp, XFS_BTREE_ERROR);
		*curpp = शून्य;
	पूर्ण

	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_XFAIL;
	trace_xchk_xref_error(sc, *error, __वापस_address);

	/*
	 * Errors encountered during cross-referencing with another
	 * data काष्ठाure should not cause this scrubber to पात.
	 */
	*error = 0;
	वापस false;
पूर्ण

/* Run the काष्ठाure verअगरiers on in-memory buffers to detect bad memory. */
व्योम
xchk_buffer_recheck(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*bp)
अणु
	xfs_failaddr_t		fa;

	अगर (bp->b_ops == शून्य) अणु
		xchk_block_set_corrupt(sc, bp);
		वापस;
	पूर्ण
	अगर (bp->b_ops->verअगरy_काष्ठा == शून्य) अणु
		xchk_set_incomplete(sc);
		वापस;
	पूर्ण
	fa = bp->b_ops->verअगरy_काष्ठा(bp);
	अगर (!fa)
		वापस;
	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_CORRUPT;
	trace_xchk_block_error(sc, bp->b_bn, fa);
पूर्ण

/*
 * Scrub the attr/data विभाजनs of a metadata inode.  The metadata inode must be
 * poपूर्णांकed to by sc->ip and the ILOCK must be held.
 */
पूर्णांक
xchk_metadata_inode_विभाजनs(
	काष्ठा xfs_scrub	*sc)
अणु
	__u32			smtype;
	bool			shared;
	पूर्णांक			error;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस 0;

	/* Metadata inodes करोn't live on the rt device. */
	अगर (sc->ip->i_dअगरlags & XFS_DIFLAG_REALTIME) अणु
		xchk_ino_set_corrupt(sc, sc->ip->i_ino);
		वापस 0;
	पूर्ण

	/* They should never participate in reflink. */
	अगर (xfs_is_reflink_inode(sc->ip)) अणु
		xchk_ino_set_corrupt(sc, sc->ip->i_ino);
		वापस 0;
	पूर्ण

	/* They also should never have extended attributes. */
	अगर (xfs_inode_hasattr(sc->ip)) अणु
		xchk_ino_set_corrupt(sc, sc->ip->i_ino);
		वापस 0;
	पूर्ण

	/* Invoke the data विभाजन scrubber. */
	smtype = sc->sm->sm_type;
	sc->sm->sm_type = XFS_SCRUB_TYPE_BMBTD;
	error = xchk_bmap_data(sc);
	sc->sm->sm_type = smtype;
	अगर (error || (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
		वापस error;

	/* Look क्रम incorrect shared blocks. */
	अगर (xfs_sb_version_hasreflink(&sc->mp->m_sb)) अणु
		error = xfs_reflink_inode_has_shared_extents(sc->tp, sc->ip,
				&shared);
		अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, 0,
				&error))
			वापस error;
		अगर (shared)
			xchk_ino_set_corrupt(sc, sc->ip->i_ino);
	पूर्ण

	वापस error;
पूर्ण

/*
 * Try to lock an inode in violation of the usual locking order rules.  For
 * example, trying to get the IOLOCK जबतक in transaction context, or just
 * plain अवरोधing AG-order or inode-order inode locking rules.  Either way,
 * the only way to aव्योम an ABBA deadlock is to use trylock and back off अगर
 * we can't.
 */
पूर्णांक
xchk_ilock_inverted(
	काष्ठा xfs_inode	*ip,
	uपूर्णांक			lock_mode)
अणु
	पूर्णांक			i;

	क्रम (i = 0; i < 20; i++) अणु
		अगर (xfs_ilock_noरुको(ip, lock_mode))
			वापस 0;
		delay(1);
	पूर्ण
	वापस -EDEADLOCK;
पूर्ण

/* Pause background reaping of resources. */
व्योम
xchk_stop_reaping(
	काष्ठा xfs_scrub	*sc)
अणु
	sc->flags |= XCHK_REAPING_DISABLED;
	xfs_blockgc_stop(sc->mp);
पूर्ण

/* Restart background reaping of resources. */
व्योम
xchk_start_reaping(
	काष्ठा xfs_scrub	*sc)
अणु
	xfs_blockgc_start(sc->mp);
	sc->flags &= ~XCHK_REAPING_DISABLED;
पूर्ण
