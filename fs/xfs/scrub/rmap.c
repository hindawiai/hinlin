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
#समावेश "xfs_rmap.h"
#समावेश "xfs_refcount.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/btree.h"

/*
 * Set us up to scrub reverse mapping btrees.
 */
पूर्णांक
xchk_setup_ag_rmapbt(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_setup_ag_btree(sc, false);
पूर्ण

/* Reverse-mapping scrubber. */

/* Cross-reference a rmap against the refcount btree. */
STATIC व्योम
xchk_rmapbt_xref_refc(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_rmap_irec	*irec)
अणु
	xfs_agblock_t		fbno;
	xfs_extlen_t		flen;
	bool			non_inode;
	bool			is_bmbt;
	bool			is_attr;
	bool			is_unwritten;
	पूर्णांक			error;

	अगर (!sc->sa.refc_cur || xchk_skip_xref(sc->sm))
		वापस;

	non_inode = XFS_RMAP_NON_INODE_OWNER(irec->rm_owner);
	is_bmbt = irec->rm_flags & XFS_RMAP_BMBT_BLOCK;
	is_attr = irec->rm_flags & XFS_RMAP_ATTR_FORK;
	is_unwritten = irec->rm_flags & XFS_RMAP_UNWRITTEN;

	/* If this is shared, must be a data विभाजन extent. */
	error = xfs_refcount_find_shared(sc->sa.refc_cur, irec->rm_startblock,
			irec->rm_blockcount, &fbno, &flen, false);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.refc_cur))
		वापस;
	अगर (flen != 0 && (non_inode || is_attr || is_bmbt || is_unwritten))
		xchk_btree_xref_set_corrupt(sc, sc->sa.refc_cur, 0);
पूर्ण

/* Cross-reference with the other btrees. */
STATIC व्योम
xchk_rmapbt_xref(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_rmap_irec	*irec)
अणु
	xfs_agblock_t		agbno = irec->rm_startblock;
	xfs_extlen_t		len = irec->rm_blockcount;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस;

	xchk_xref_is_used_space(sc, agbno, len);
	अगर (irec->rm_owner == XFS_RMAP_OWN_INODES)
		xchk_xref_is_inode_chunk(sc, agbno, len);
	अन्यथा
		xchk_xref_is_not_inode_chunk(sc, agbno, len);
	अगर (irec->rm_owner == XFS_RMAP_OWN_COW)
		xchk_xref_is_cow_staging(sc, irec->rm_startblock,
				irec->rm_blockcount);
	अन्यथा
		xchk_rmapbt_xref_refc(sc, irec);
पूर्ण

/* Scrub an rmapbt record. */
STATIC पूर्णांक
xchk_rmapbt_rec(
	काष्ठा xchk_btree	*bs,
	जोड़ xfs_btree_rec	*rec)
अणु
	काष्ठा xfs_mount	*mp = bs->cur->bc_mp;
	काष्ठा xfs_rmap_irec	irec;
	xfs_agnumber_t		agno = bs->cur->bc_ag.agno;
	bool			non_inode;
	bool			is_unwritten;
	bool			is_bmbt;
	bool			is_attr;
	पूर्णांक			error;

	error = xfs_rmap_btrec_to_irec(rec, &irec);
	अगर (!xchk_btree_process_error(bs->sc, bs->cur, 0, &error))
		जाओ out;

	/* Check extent. */
	अगर (irec.rm_startblock + irec.rm_blockcount <= irec.rm_startblock)
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	अगर (irec.rm_owner == XFS_RMAP_OWN_FS) अणु
		/*
		 * xfs_verअगरy_agbno वापसs false क्रम अटल fs metadata.
		 * Since that only exists at the start of the AG, validate
		 * that by hand.
		 */
		अगर (irec.rm_startblock != 0 ||
		    irec.rm_blockcount != XFS_AGFL_BLOCK(mp) + 1)
			xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
	पूर्ण अन्यथा अणु
		/*
		 * Otherwise we must poपूर्णांक somewhere past the अटल metadata
		 * but beक्रमe the end of the FS.  Run the regular check.
		 */
		अगर (!xfs_verअगरy_agbno(mp, agno, irec.rm_startblock) ||
		    !xfs_verअगरy_agbno(mp, agno, irec.rm_startblock +
				irec.rm_blockcount - 1))
			xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
	पूर्ण

	/* Check flags. */
	non_inode = XFS_RMAP_NON_INODE_OWNER(irec.rm_owner);
	is_bmbt = irec.rm_flags & XFS_RMAP_BMBT_BLOCK;
	is_attr = irec.rm_flags & XFS_RMAP_ATTR_FORK;
	is_unwritten = irec.rm_flags & XFS_RMAP_UNWRITTEN;

	अगर (is_bmbt && irec.rm_offset != 0)
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	अगर (non_inode && irec.rm_offset != 0)
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	अगर (is_unwritten && (is_bmbt || non_inode || is_attr))
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	अगर (non_inode && (is_bmbt || is_unwritten || is_attr))
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	अगर (!non_inode) अणु
		अगर (!xfs_verअगरy_ino(mp, irec.rm_owner))
			xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
	पूर्ण अन्यथा अणु
		/* Non-inode owner within the magic values? */
		अगर (irec.rm_owner <= XFS_RMAP_OWN_MIN ||
		    irec.rm_owner > XFS_RMAP_OWN_FS)
			xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
	पूर्ण

	xchk_rmapbt_xref(bs->sc, &irec);
out:
	वापस error;
पूर्ण

/* Scrub the rmap btree क्रम some AG. */
पूर्णांक
xchk_rmapbt(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_btree(sc, sc->sa.rmap_cur, xchk_rmapbt_rec,
			&XFS_RMAP_OINFO_AG, शून्य);
पूर्ण

/* xref check that the extent is owned by a given owner */
अटल अंतरभूत व्योम
xchk_xref_check_owner(
	काष्ठा xfs_scrub		*sc,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo,
	bool				should_have_rmap)
अणु
	bool				has_rmap;
	पूर्णांक				error;

	अगर (!sc->sa.rmap_cur || xchk_skip_xref(sc->sm))
		वापस;

	error = xfs_rmap_record_exists(sc->sa.rmap_cur, bno, len, oinfo,
			&has_rmap);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.rmap_cur))
		वापस;
	अगर (has_rmap != should_have_rmap)
		xchk_btree_xref_set_corrupt(sc, sc->sa.rmap_cur, 0);
पूर्ण

/* xref check that the extent is owned by a given owner */
व्योम
xchk_xref_is_owned_by(
	काष्ठा xfs_scrub		*sc,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	xchk_xref_check_owner(sc, bno, len, oinfo, true);
पूर्ण

/* xref check that the extent is not owned by a given owner */
व्योम
xchk_xref_is_not_owned_by(
	काष्ठा xfs_scrub		*sc,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	स्थिर काष्ठा xfs_owner_info	*oinfo)
अणु
	xchk_xref_check_owner(sc, bno, len, oinfo, false);
पूर्ण

/* xref check that the extent has no reverse mapping at all */
व्योम
xchk_xref_has_no_owner(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		bno,
	xfs_extlen_t		len)
अणु
	bool			has_rmap;
	पूर्णांक			error;

	अगर (!sc->sa.rmap_cur || xchk_skip_xref(sc->sm))
		वापस;

	error = xfs_rmap_has_record(sc->sa.rmap_cur, bno, len, &has_rmap);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.rmap_cur))
		वापस;
	अगर (has_rmap)
		xchk_btree_xref_set_corrupt(sc, sc->sa.rmap_cur, 0);
पूर्ण
