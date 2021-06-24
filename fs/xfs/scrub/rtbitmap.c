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
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_rtalloc.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_bmap.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"

/* Set us up with the realसमय metadata locked. */
पूर्णांक
xchk_setup_rt(
	काष्ठा xfs_scrub	*sc)
अणु
	पूर्णांक			error;

	error = xchk_setup_fs(sc);
	अगर (error)
		वापस error;

	sc->ilock_flags = XFS_ILOCK_EXCL | XFS_ILOCK_RTBITMAP;
	sc->ip = sc->mp->m_rbmip;
	xfs_ilock(sc->ip, sc->ilock_flags);

	वापस 0;
पूर्ण

/* Realसमय biपंचांगap. */

/* Scrub a मुक्त extent record from the realसमय biपंचांगap. */
STATIC पूर्णांक
xchk_rtbiपंचांगap_rec(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_rtalloc_rec	*rec,
	व्योम			*priv)
अणु
	काष्ठा xfs_scrub	*sc = priv;
	xfs_rtblock_t		startblock;
	xfs_rtblock_t		blockcount;

	startblock = rec->ar_startext * tp->t_mountp->m_sb.sb_rextsize;
	blockcount = rec->ar_extcount * tp->t_mountp->m_sb.sb_rextsize;

	अगर (!xfs_verअगरy_rtext(sc->mp, startblock, blockcount))
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
	वापस 0;
पूर्ण

/* Make sure the entire rtbiपंचांगap file is mapped with written extents. */
STATIC पूर्णांक
xchk_rtbiपंचांगap_check_extents(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_bmbt_irec	map;
	xfs_rtblock_t		off;
	पूर्णांक			nmap;
	पूर्णांक			error = 0;

	क्रम (off = 0; off < mp->m_sb.sb_rbmblocks;) अणु
		अगर (xchk_should_terminate(sc, &error) ||
		    (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
			अवरोध;

		/* Make sure we have a written extent. */
		nmap = 1;
		error = xfs_bmapi_पढ़ो(mp->m_rbmip, off,
				mp->m_sb.sb_rbmblocks - off, &map, &nmap,
				XFS_DATA_FORK);
		अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, off, &error))
			अवरोध;

		अगर (nmap != 1 || !xfs_bmap_is_written_extent(&map)) अणु
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, off);
			अवरोध;
		पूर्ण

		off += map.br_blockcount;
	पूर्ण

	वापस error;
पूर्ण

/* Scrub the realसमय biपंचांगap. */
पूर्णांक
xchk_rtbiपंचांगap(
	काष्ठा xfs_scrub	*sc)
अणु
	पूर्णांक			error;

	/* Is the size of the rtbiपंचांगap correct? */
	अगर (sc->mp->m_rbmip->i_disk_size !=
	    XFS_FSB_TO_B(sc->mp, sc->mp->m_sb.sb_rbmblocks)) अणु
		xchk_ino_set_corrupt(sc, sc->mp->m_rbmip->i_ino);
		वापस 0;
	पूर्ण

	/* Invoke the विभाजन scrubber. */
	error = xchk_metadata_inode_विभाजनs(sc);
	अगर (error || (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
		वापस error;

	error = xchk_rtbiपंचांगap_check_extents(sc);
	अगर (error || (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
		वापस error;

	error = xfs_rtalloc_query_all(sc->tp, xchk_rtbiपंचांगap_rec, sc);
	अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, 0, &error))
		जाओ out;

out:
	वापस error;
पूर्ण

/* Scrub the realसमय summary. */
पूर्णांक
xchk_rtsummary(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_inode	*rsumip = sc->mp->m_rsumip;
	काष्ठा xfs_inode	*old_ip = sc->ip;
	uपूर्णांक			old_ilock_flags = sc->ilock_flags;
	पूर्णांक			error = 0;

	/*
	 * We ILOCK'd the rt biपंचांगap ip in the setup routine, now lock the
	 * rt summary ip in compliance with the rt inode locking rules.
	 *
	 * Since we चयन sc->ip to rsumip we have to save the old ilock
	 * flags so that we करोn't mix up the inode state that @sc tracks.
	 */
	sc->ip = rsumip;
	sc->ilock_flags = XFS_ILOCK_EXCL | XFS_ILOCK_RTSUM;
	xfs_ilock(sc->ip, sc->ilock_flags);

	/* Invoke the विभाजन scrubber. */
	error = xchk_metadata_inode_विभाजनs(sc);
	अगर (error || (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
		जाओ out;

	/* XXX: implement this some day */
	xchk_set_incomplete(sc);
out:
	/* Switch back to the rtbiपंचांगap inode and lock flags. */
	xfs_iunlock(sc->ip, sc->ilock_flags);
	sc->ilock_flags = old_ilock_flags;
	sc->ip = old_ip;
	वापस error;
पूर्ण


/* xref check that the extent is not मुक्त in the rtbiपंचांगap */
व्योम
xchk_xref_is_used_rt_space(
	काष्ठा xfs_scrub	*sc,
	xfs_rtblock_t		fsbno,
	xfs_extlen_t		len)
अणु
	xfs_rtblock_t		startext;
	xfs_rtblock_t		endext;
	xfs_rtblock_t		extcount;
	bool			is_मुक्त;
	पूर्णांक			error;

	अगर (xchk_skip_xref(sc->sm))
		वापस;

	startext = fsbno;
	endext = fsbno + len - 1;
	करो_भाग(startext, sc->mp->m_sb.sb_rextsize);
	करो_भाग(endext, sc->mp->m_sb.sb_rextsize);
	extcount = endext - startext + 1;
	xfs_ilock(sc->mp->m_rbmip, XFS_ILOCK_SHARED | XFS_ILOCK_RTBITMAP);
	error = xfs_rtalloc_extent_is_मुक्त(sc->mp, sc->tp, startext, extcount,
			&is_मुक्त);
	अगर (!xchk_should_check_xref(sc, &error, शून्य))
		जाओ out_unlock;
	अगर (is_मुक्त)
		xchk_ino_xref_set_corrupt(sc, sc->mp->m_rbmip->i_ino);
out_unlock:
	xfs_iunlock(sc->mp->m_rbmip, XFS_ILOCK_SHARED | XFS_ILOCK_RTBITMAP);
पूर्ण
