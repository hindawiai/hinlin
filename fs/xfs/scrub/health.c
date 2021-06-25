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
#समावेश "xfs_btree.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_health.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/health.h"

/*
 * Scrub and In-Core Fileप्रणाली Health Assessments
 * ===============================================
 *
 * Online scrub and repair have the समय and the ability to perक्रमm stronger
 * checks than we can करो from the metadata verअगरiers, because they can
 * cross-reference records between data काष्ठाures.  Thereक्रमe, scrub is in a
 * good position to update the online fileप्रणाली health assessments to reflect
 * the good/bad state of the data काष्ठाure.
 *
 * We thereक्रमe extend scrub in the following ways to achieve this:
 *
 * 1. Create a "sick_mask" field in the scrub context.  When we're setting up a
 * scrub call, set this to the शेष XFS_SICK_* flag(s) क्रम the selected
 * scrub type (call it A).  Scrub and repair functions can override the शेष
 * sick_mask value अगर they choose.
 *
 * 2. If the scrubber वापसs a runसमय error code, we निकास making no changes
 * to the incore sick state.
 *
 * 3. If the scrubber finds that A is clean, use sick_mask to clear the incore
 * sick flags beक्रमe निकासing.
 *
 * 4. If the scrubber finds that A is corrupt, use sick_mask to set the incore
 * sick flags.  If the user didn't want to repair then we निकास, leaving the
 * metadata काष्ठाure unfixed and the sick flag set.
 *
 * 5. Now we know that A is corrupt and the user wants to repair, so run the
 * repairer.  If the repairer वापसs an error code, we निकास with that error
 * code, having made no further changes to the incore sick state.
 *
 * 6. If repair rebuilds A correctly and the subsequent re-scrub of A is clean,
 * use sick_mask to clear the incore sick flags.  This should have the effect
 * that A is no दीर्घer marked sick.
 *
 * 7. If repair rebuilds A incorrectly, the re-scrub will find it corrupt and
 * use sick_mask to set the incore sick flags.  This should have no बाह्यally
 * visible effect since we alपढ़ोy set them in step (4).
 *
 * There are some complications to this story, however.  For certain types of
 * complementary metadata indices (e.g. inobt/finobt), it is easier to rebuild
 * both काष्ठाures at the same समय.  The following principles apply to this
 * type of repair strategy:
 *
 * 8. Any repair function that rebuilds multiple काष्ठाures should update
 * sick_mask_visible to reflect whatever other काष्ठाures are rebuilt, and
 * verअगरy that all the rebuilt काष्ठाures can pass a scrub check.  The outcomes
 * of 5-7 still apply, but with a sick_mask that covers everything being
 * rebuilt.
 */

/* Map our scrub type to a sick mask and a set of health update functions. */

क्रमागत xchk_health_group अणु
	XHG_FS = 1,
	XHG_RT,
	XHG_AG,
	XHG_INO,
पूर्ण;

काष्ठा xchk_health_map अणु
	क्रमागत xchk_health_group	group;
	अचिन्हित पूर्णांक		sick_mask;
पूर्ण;

अटल स्थिर काष्ठा xchk_health_map type_to_health_flag[XFS_SCRUB_TYPE_NR] = अणु
	[XFS_SCRUB_TYPE_SB]		= अणु XHG_AG,  XFS_SICK_AG_SB पूर्ण,
	[XFS_SCRUB_TYPE_AGF]		= अणु XHG_AG,  XFS_SICK_AG_AGF पूर्ण,
	[XFS_SCRUB_TYPE_AGFL]		= अणु XHG_AG,  XFS_SICK_AG_AGFL पूर्ण,
	[XFS_SCRUB_TYPE_AGI]		= अणु XHG_AG,  XFS_SICK_AG_AGI पूर्ण,
	[XFS_SCRUB_TYPE_BNOBT]		= अणु XHG_AG,  XFS_SICK_AG_BNOBT पूर्ण,
	[XFS_SCRUB_TYPE_CNTBT]		= अणु XHG_AG,  XFS_SICK_AG_CNTBT पूर्ण,
	[XFS_SCRUB_TYPE_INOBT]		= अणु XHG_AG,  XFS_SICK_AG_INOBT पूर्ण,
	[XFS_SCRUB_TYPE_FINOBT]		= अणु XHG_AG,  XFS_SICK_AG_FINOBT पूर्ण,
	[XFS_SCRUB_TYPE_RMAPBT]		= अणु XHG_AG,  XFS_SICK_AG_RMAPBT पूर्ण,
	[XFS_SCRUB_TYPE_REFCNTBT]	= अणु XHG_AG,  XFS_SICK_AG_REFCNTBT पूर्ण,
	[XFS_SCRUB_TYPE_INODE]		= अणु XHG_INO, XFS_SICK_INO_CORE पूर्ण,
	[XFS_SCRUB_TYPE_BMBTD]		= अणु XHG_INO, XFS_SICK_INO_BMBTD पूर्ण,
	[XFS_SCRUB_TYPE_BMBTA]		= अणु XHG_INO, XFS_SICK_INO_BMBTA पूर्ण,
	[XFS_SCRUB_TYPE_BMBTC]		= अणु XHG_INO, XFS_SICK_INO_BMBTC पूर्ण,
	[XFS_SCRUB_TYPE_सूची]		= अणु XHG_INO, XFS_SICK_INO_सूची पूर्ण,
	[XFS_SCRUB_TYPE_XATTR]		= अणु XHG_INO, XFS_SICK_INO_XATTR पूर्ण,
	[XFS_SCRUB_TYPE_SYMLINK]	= अणु XHG_INO, XFS_SICK_INO_SYMLINK पूर्ण,
	[XFS_SCRUB_TYPE_PARENT]		= अणु XHG_INO, XFS_SICK_INO_PARENT पूर्ण,
	[XFS_SCRUB_TYPE_RTBITMAP]	= अणु XHG_RT,  XFS_SICK_RT_BITMAP पूर्ण,
	[XFS_SCRUB_TYPE_RTSUM]		= अणु XHG_RT,  XFS_SICK_RT_SUMMARY पूर्ण,
	[XFS_SCRUB_TYPE_UQUOTA]		= अणु XHG_FS,  XFS_SICK_FS_UQUOTA पूर्ण,
	[XFS_SCRUB_TYPE_GQUOTA]		= अणु XHG_FS,  XFS_SICK_FS_GQUOTA पूर्ण,
	[XFS_SCRUB_TYPE_PQUOTA]		= अणु XHG_FS,  XFS_SICK_FS_PQUOTA पूर्ण,
	[XFS_SCRUB_TYPE_FSCOUNTERS]	= अणु XHG_FS,  XFS_SICK_FS_COUNTERS पूर्ण,
पूर्ण;

/* Return the health status mask क्रम this scrub type. */
अचिन्हित पूर्णांक
xchk_health_mask_क्रम_scrub_type(
	__u32			scrub_type)
अणु
	वापस type_to_health_flag[scrub_type].sick_mask;
पूर्ण

/*
 * Update fileप्रणाली health assessments based on what we found and did.
 *
 * If the scrubber finds errors, we mark sick whatever's mentioned in
 * sick_mask, no matter whether this is a first scan or an
 * evaluation of repair effectiveness.
 *
 * Otherwise, no direct corruption was found, so mark whatever's in
 * sick_mask as healthy.
 */
व्योम
xchk_update_health(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_perag	*pag;
	bool			bad;

	अगर (!sc->sick_mask)
		वापस;

	bad = (sc->sm->sm_flags & (XFS_SCRUB_OFLAG_CORRUPT |
				   XFS_SCRUB_OFLAG_XCORRUPT));
	चयन (type_to_health_flag[sc->sm->sm_type].group) अणु
	हाल XHG_AG:
		pag = xfs_perag_get(sc->mp, sc->sm->sm_agno);
		अगर (bad)
			xfs_ag_mark_sick(pag, sc->sick_mask);
		अन्यथा
			xfs_ag_mark_healthy(pag, sc->sick_mask);
		xfs_perag_put(pag);
		अवरोध;
	हाल XHG_INO:
		अगर (!sc->ip)
			वापस;
		अगर (bad)
			xfs_inode_mark_sick(sc->ip, sc->sick_mask);
		अन्यथा
			xfs_inode_mark_healthy(sc->ip, sc->sick_mask);
		अवरोध;
	हाल XHG_FS:
		अगर (bad)
			xfs_fs_mark_sick(sc->mp, sc->sick_mask);
		अन्यथा
			xfs_fs_mark_healthy(sc->mp, sc->sick_mask);
		अवरोध;
	हाल XHG_RT:
		अगर (bad)
			xfs_rt_mark_sick(sc->mp, sc->sick_mask);
		अन्यथा
			xfs_rt_mark_healthy(sc->mp, sc->sick_mask);
		अवरोध;
	शेष:
		ASSERT(0);
		अवरोध;
	पूर्ण
पूर्ण

/* Is the given per-AG btree healthy enough क्रम scanning? */
bool
xchk_ag_btree_healthy_enough(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_perag	*pag,
	xfs_btnum_t		btnum)
अणु
	अचिन्हित पूर्णांक		mask = 0;

	/*
	 * We always want the cursor अगर it's the same type as whatever we're
	 * scrubbing, even अगर we alपढ़ोy know the काष्ठाure is corrupt.
	 *
	 * Otherwise, we're only पूर्णांकerested in the btree क्रम cross-referencing.
	 * If we know the btree is bad then करोn't bother, just set XFAIL.
	 */
	चयन (btnum) अणु
	हाल XFS_BTNUM_BNO:
		अगर (sc->sm->sm_type == XFS_SCRUB_TYPE_BNOBT)
			वापस true;
		mask = XFS_SICK_AG_BNOBT;
		अवरोध;
	हाल XFS_BTNUM_CNT:
		अगर (sc->sm->sm_type == XFS_SCRUB_TYPE_CNTBT)
			वापस true;
		mask = XFS_SICK_AG_CNTBT;
		अवरोध;
	हाल XFS_BTNUM_INO:
		अगर (sc->sm->sm_type == XFS_SCRUB_TYPE_INOBT)
			वापस true;
		mask = XFS_SICK_AG_INOBT;
		अवरोध;
	हाल XFS_BTNUM_FINO:
		अगर (sc->sm->sm_type == XFS_SCRUB_TYPE_FINOBT)
			वापस true;
		mask = XFS_SICK_AG_FINOBT;
		अवरोध;
	हाल XFS_BTNUM_RMAP:
		अगर (sc->sm->sm_type == XFS_SCRUB_TYPE_RMAPBT)
			वापस true;
		mask = XFS_SICK_AG_RMAPBT;
		अवरोध;
	हाल XFS_BTNUM_REFC:
		अगर (sc->sm->sm_type == XFS_SCRUB_TYPE_REFCNTBT)
			वापस true;
		mask = XFS_SICK_AG_REFCNTBT;
		अवरोध;
	शेष:
		ASSERT(0);
		वापस true;
	पूर्ण

	अगर (xfs_ag_has_sickness(pag, mask)) अणु
		sc->sm->sm_flags |= XFS_SCRUB_OFLAG_XFAIL;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
