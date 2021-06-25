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
#समावेश "xfs_inode.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_reflink.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_bmap_util.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/btree.h"

/*
 * Grab total control of the inode metadata.  It करोesn't matter here अगर
 * the file data is still changing; exclusive access to the metadata is
 * the goal.
 */
पूर्णांक
xchk_setup_inode(
	काष्ठा xfs_scrub	*sc)
अणु
	पूर्णांक			error;

	/*
	 * Try to get the inode.  If the verअगरiers fail, we try again
	 * in raw mode.
	 */
	error = xchk_get_inode(sc);
	चयन (error) अणु
	हाल 0:
		अवरोध;
	हाल -EFSCORRUPTED:
	हाल -EFSBADCRC:
		वापस xchk_trans_alloc(sc, 0);
	शेष:
		वापस error;
	पूर्ण

	/* Got the inode, lock it and we're पढ़ोy to go. */
	sc->ilock_flags = XFS_IOLOCK_EXCL | XFS_MMAPLOCK_EXCL;
	xfs_ilock(sc->ip, sc->ilock_flags);
	error = xchk_trans_alloc(sc, 0);
	अगर (error)
		जाओ out;
	sc->ilock_flags |= XFS_ILOCK_EXCL;
	xfs_ilock(sc->ip, XFS_ILOCK_EXCL);

out:
	/* scrub tearकरोwn will unlock and release the inode क्रम us */
	वापस error;
पूर्ण

/* Inode core */

/* Validate di_extsize hपूर्णांक. */
STATIC व्योम
xchk_inode_extsize(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_dinode	*dip,
	xfs_ino_t		ino,
	uपूर्णांक16_t		mode,
	uपूर्णांक16_t		flags)
अणु
	xfs_failaddr_t		fa;

	fa = xfs_inode_validate_extsize(sc->mp, be32_to_cpu(dip->di_extsize),
			mode, flags);
	अगर (fa)
		xchk_ino_set_corrupt(sc, ino);
पूर्ण

/*
 * Validate di_cowextsize hपूर्णांक.
 *
 * The rules are करोcumented at xfs_ioctl_setattr_check_cowextsize().
 * These functions must be kept in sync with each other.
 */
STATIC व्योम
xchk_inode_cowextsize(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_dinode	*dip,
	xfs_ino_t		ino,
	uपूर्णांक16_t		mode,
	uपूर्णांक16_t		flags,
	uपूर्णांक64_t		flags2)
अणु
	xfs_failaddr_t		fa;

	fa = xfs_inode_validate_cowextsize(sc->mp,
			be32_to_cpu(dip->di_cowextsize), mode, flags,
			flags2);
	अगर (fa)
		xchk_ino_set_corrupt(sc, ino);
पूर्ण

/* Make sure the di_flags make sense क्रम the inode. */
STATIC व्योम
xchk_inode_flags(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_dinode	*dip,
	xfs_ino_t		ino,
	uपूर्णांक16_t		mode,
	uपूर्णांक16_t		flags)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;

	/* di_flags are all taken, last bit cannot be used */
	अगर (flags & ~XFS_DIFLAG_ANY)
		जाओ bad;

	/* rt flags require rt device */
	अगर ((flags & XFS_DIFLAG_REALTIME) && !mp->m_rtdev_targp)
		जाओ bad;

	/* new rt biपंचांगap flag only valid क्रम rbmino */
	अगर ((flags & XFS_DIFLAG_NEWRTBM) && ino != mp->m_sb.sb_rbmino)
		जाओ bad;

	/* directory-only flags */
	अगर ((flags & (XFS_DIFLAG_RTINHERIT |
		     XFS_DIFLAG_EXTSZINHERIT |
		     XFS_DIFLAG_PROJINHERIT |
		     XFS_DIFLAG_NOSYMLINKS)) &&
	    !S_ISसूची(mode))
		जाओ bad;

	/* file-only flags */
	अगर ((flags & (XFS_DIFLAG_REALTIME | FS_XFLAG_EXTSIZE)) &&
	    !S_ISREG(mode))
		जाओ bad;

	/* filestreams and rt make no sense */
	अगर ((flags & XFS_DIFLAG_खाताSTREAM) && (flags & XFS_DIFLAG_REALTIME))
		जाओ bad;

	वापस;
bad:
	xchk_ino_set_corrupt(sc, ino);
पूर्ण

/* Make sure the di_flags2 make sense क्रम the inode. */
STATIC व्योम
xchk_inode_flags2(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_dinode	*dip,
	xfs_ino_t		ino,
	uपूर्णांक16_t		mode,
	uपूर्णांक16_t		flags,
	uपूर्णांक64_t		flags2)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;

	/* Unknown di_flags2 could be from a future kernel */
	अगर (flags2 & ~XFS_DIFLAG2_ANY)
		xchk_ino_set_warning(sc, ino);

	/* reflink flag requires reflink feature */
	अगर ((flags2 & XFS_DIFLAG2_REFLINK) &&
	    !xfs_sb_version_hasreflink(&mp->m_sb))
		जाओ bad;

	/* cowextsize flag is checked w.r.t. mode separately */

	/* file/dir-only flags */
	अगर ((flags2 & XFS_DIFLAG2_DAX) && !(S_ISREG(mode) || S_ISसूची(mode)))
		जाओ bad;

	/* file-only flags */
	अगर ((flags2 & XFS_DIFLAG2_REFLINK) && !S_ISREG(mode))
		जाओ bad;

	/* realसमय and reflink make no sense, currently */
	अगर ((flags & XFS_DIFLAG_REALTIME) && (flags2 & XFS_DIFLAG2_REFLINK))
		जाओ bad;

	/* no bigसमय अगरlag without the bigसमय feature */
	अगर (xfs_dinode_has_bigसमय(dip) &&
	    !xfs_sb_version_hasbigसमय(&mp->m_sb))
		जाओ bad;

	वापस;
bad:
	xchk_ino_set_corrupt(sc, ino);
पूर्ण

अटल अंतरभूत व्योम
xchk_dinode_nsec(
	काष्ठा xfs_scrub	*sc,
	xfs_ino_t		ino,
	काष्ठा xfs_dinode	*dip,
	स्थिर xfs_बारtamp_t	ts)
अणु
	काष्ठा बारpec64	tv;

	tv = xfs_inode_from_disk_ts(dip, ts);
	अगर (tv.tv_nsec < 0 || tv.tv_nsec >= NSEC_PER_SEC)
		xchk_ino_set_corrupt(sc, ino);
पूर्ण

/* Scrub all the ondisk inode fields. */
STATIC व्योम
xchk_dinode(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_dinode	*dip,
	xfs_ino_t		ino)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	माप_प्रकार			विभाजन_recs;
	अचिन्हित दीर्घ दीर्घ	isize;
	uपूर्णांक64_t		flags2;
	uपूर्णांक32_t		nextents;
	uपूर्णांक16_t		flags;
	uपूर्णांक16_t		mode;

	flags = be16_to_cpu(dip->di_flags);
	अगर (dip->di_version >= 3)
		flags2 = be64_to_cpu(dip->di_flags2);
	अन्यथा
		flags2 = 0;

	/* di_mode */
	mode = be16_to_cpu(dip->di_mode);
	चयन (mode & S_IFMT) अणु
	हाल S_IFLNK:
	हाल S_IFREG:
	हाल S_IFसूची:
	हाल S_IFCHR:
	हाल S_IFBLK:
	हाल S_IFIFO:
	हाल S_IFSOCK:
		/* mode is recognized */
		अवरोध;
	शेष:
		xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	पूर्ण

	/* v1/v2 fields */
	चयन (dip->di_version) अणु
	हाल 1:
		/*
		 * We स्वतःconvert v1 inodes पूर्णांकo v2 inodes on ग_लिखोout,
		 * so just mark this inode क्रम preening.
		 */
		xchk_ino_set_preen(sc, ino);
		अवरोध;
	हाल 2:
	हाल 3:
		अगर (dip->di_onlink != 0)
			xchk_ino_set_corrupt(sc, ino);

		अगर (dip->di_mode == 0 && sc->ip)
			xchk_ino_set_corrupt(sc, ino);

		अगर (dip->di_projid_hi != 0 &&
		    !xfs_sb_version_hasprojid32bit(&mp->m_sb))
			xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	शेष:
		xchk_ino_set_corrupt(sc, ino);
		वापस;
	पूर्ण

	/*
	 * di_uid/di_gid -- -1 isn't invalid, but there's no way that
	 * userspace could have created that.
	 */
	अगर (dip->di_uid == cpu_to_be32(-1U) ||
	    dip->di_gid == cpu_to_be32(-1U))
		xchk_ino_set_warning(sc, ino);

	/* di_क्रमmat */
	चयन (dip->di_क्रमmat) अणु
	हाल XFS_DINODE_FMT_DEV:
		अगर (!S_ISCHR(mode) && !S_ISBLK(mode) &&
		    !S_ISFIFO(mode) && !S_ISSOCK(mode))
			xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	हाल XFS_DINODE_FMT_LOCAL:
		अगर (!S_ISसूची(mode) && !S_ISLNK(mode))
			xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	हाल XFS_DINODE_FMT_EXTENTS:
		अगर (!S_ISREG(mode) && !S_ISसूची(mode) && !S_ISLNK(mode))
			xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		अगर (!S_ISREG(mode) && !S_ISसूची(mode))
			xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	हाल XFS_DINODE_FMT_UUID:
	शेष:
		xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	पूर्ण

	/* di_[amc]समय.nsec */
	xchk_dinode_nsec(sc, ino, dip, dip->di_aसमय);
	xchk_dinode_nsec(sc, ino, dip, dip->di_mसमय);
	xchk_dinode_nsec(sc, ino, dip, dip->di_स_समय);

	/*
	 * di_size.  xfs_dinode_verअगरy checks क्रम things that screw up
	 * the VFS such as the upper bit being set and zero-length
	 * symlinks/directories, but we can करो more here.
	 */
	isize = be64_to_cpu(dip->di_size);
	अगर (isize & (1ULL << 63))
		xchk_ino_set_corrupt(sc, ino);

	/* Devices, fअगरos, and sockets must have zero size */
	अगर (!S_ISसूची(mode) && !S_ISREG(mode) && !S_ISLNK(mode) && isize != 0)
		xchk_ino_set_corrupt(sc, ino);

	/* Directories can't be larger than the data section size (32G) */
	अगर (S_ISसूची(mode) && (isize == 0 || isize >= XFS_सूची2_SPACE_SIZE))
		xchk_ino_set_corrupt(sc, ino);

	/* Symlinks can't be larger than SYMLINK_MAXLEN */
	अगर (S_ISLNK(mode) && (isize == 0 || isize >= XFS_SYMLINK_MAXLEN))
		xchk_ino_set_corrupt(sc, ino);

	/*
	 * Warn अगर the running kernel can't handle the kinds of offsets
	 * needed to deal with the file size.  In other words, अगर the
	 * pagecache can't cache all the blocks in this file due to
	 * overly large offsets, flag the inode क्रम admin review.
	 */
	अगर (isize >= mp->m_super->s_maxbytes)
		xchk_ino_set_warning(sc, ino);

	/* di_nblocks */
	अगर (flags2 & XFS_DIFLAG2_REFLINK) अणु
		; /* nblocks can exceed dblocks */
	पूर्ण अन्यथा अगर (flags & XFS_DIFLAG_REALTIME) अणु
		/*
		 * nblocks is the sum of data extents (in the rtdev),
		 * attr extents (in the datadev), and both विभाजनs' bmbt
		 * blocks (in the datadev).  This clumsy check is the
		 * best we can करो without cross-referencing with the
		 * inode विभाजनs.
		 */
		अगर (be64_to_cpu(dip->di_nblocks) >=
		    mp->m_sb.sb_dblocks + mp->m_sb.sb_rblocks)
			xchk_ino_set_corrupt(sc, ino);
	पूर्ण अन्यथा अणु
		अगर (be64_to_cpu(dip->di_nblocks) >= mp->m_sb.sb_dblocks)
			xchk_ino_set_corrupt(sc, ino);
	पूर्ण

	xchk_inode_flags(sc, dip, ino, mode, flags);

	xchk_inode_extsize(sc, dip, ino, mode, flags);

	/* di_nextents */
	nextents = be32_to_cpu(dip->di_nextents);
	विभाजन_recs =  XFS_DFORK_DSIZE(dip, mp) / माप(काष्ठा xfs_bmbt_rec);
	चयन (dip->di_क्रमmat) अणु
	हाल XFS_DINODE_FMT_EXTENTS:
		अगर (nextents > विभाजन_recs)
			xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		अगर (nextents <= विभाजन_recs)
			xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	शेष:
		अगर (nextents != 0)
			xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	पूर्ण

	/* di_विभाजनoff */
	अगर (XFS_DFORK_APTR(dip) >= (अक्षर *)dip + mp->m_sb.sb_inodesize)
		xchk_ino_set_corrupt(sc, ino);
	अगर (dip->di_anextents != 0 && dip->di_विभाजनoff == 0)
		xchk_ino_set_corrupt(sc, ino);
	अगर (dip->di_विभाजनoff == 0 && dip->di_aक्रमmat != XFS_DINODE_FMT_EXTENTS)
		xchk_ino_set_corrupt(sc, ino);

	/* di_aक्रमmat */
	अगर (dip->di_aक्रमmat != XFS_DINODE_FMT_LOCAL &&
	    dip->di_aक्रमmat != XFS_DINODE_FMT_EXTENTS &&
	    dip->di_aक्रमmat != XFS_DINODE_FMT_BTREE)
		xchk_ino_set_corrupt(sc, ino);

	/* di_anextents */
	nextents = be16_to_cpu(dip->di_anextents);
	विभाजन_recs =  XFS_DFORK_ASIZE(dip, mp) / माप(काष्ठा xfs_bmbt_rec);
	चयन (dip->di_aक्रमmat) अणु
	हाल XFS_DINODE_FMT_EXTENTS:
		अगर (nextents > विभाजन_recs)
			xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		अगर (nextents <= विभाजन_recs)
			xchk_ino_set_corrupt(sc, ino);
		अवरोध;
	शेष:
		अगर (nextents != 0)
			xchk_ino_set_corrupt(sc, ino);
	पूर्ण

	अगर (dip->di_version >= 3) अणु
		xchk_dinode_nsec(sc, ino, dip, dip->di_crसमय);
		xchk_inode_flags2(sc, dip, ino, mode, flags, flags2);
		xchk_inode_cowextsize(sc, dip, ino, mode, flags,
				flags2);
	पूर्ण
पूर्ण

/*
 * Make sure the finobt करोesn't think this inode is मुक्त.
 * We करोn't have to check the inobt ourselves because we got the inode via
 * IGET_UNTRUSTED, which checks the inobt क्रम us.
 */
अटल व्योम
xchk_inode_xref_finobt(
	काष्ठा xfs_scrub		*sc,
	xfs_ino_t			ino)
अणु
	काष्ठा xfs_inobt_rec_incore	rec;
	xfs_agino_t			agino;
	पूर्णांक				has_record;
	पूर्णांक				error;

	अगर (!sc->sa.fino_cur || xchk_skip_xref(sc->sm))
		वापस;

	agino = XFS_INO_TO_AGINO(sc->mp, ino);

	/*
	 * Try to get the finobt record.  If we can't get it, then we're
	 * in good shape.
	 */
	error = xfs_inobt_lookup(sc->sa.fino_cur, agino, XFS_LOOKUP_LE,
			&has_record);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.fino_cur) ||
	    !has_record)
		वापस;

	error = xfs_inobt_get_rec(sc->sa.fino_cur, &rec, &has_record);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.fino_cur) ||
	    !has_record)
		वापस;

	/*
	 * Otherwise, make sure this record either करोesn't cover this inode,
	 * or that it करोes but it's marked present.
	 */
	अगर (rec.ir_startino > agino ||
	    rec.ir_startino + XFS_INODES_PER_CHUNK <= agino)
		वापस;

	अगर (rec.ir_मुक्त & XFS_INOBT_MASK(agino - rec.ir_startino))
		xchk_btree_xref_set_corrupt(sc, sc->sa.fino_cur, 0);
पूर्ण

/* Cross reference the inode fields with the विभाजनs. */
STATIC व्योम
xchk_inode_xref_bmap(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_dinode	*dip)
अणु
	xfs_extnum_t		nextents;
	xfs_filblks_t		count;
	xfs_filblks_t		acount;
	पूर्णांक			error;

	अगर (xchk_skip_xref(sc->sm))
		वापस;

	/* Walk all the extents to check nextents/naextents/nblocks. */
	error = xfs_bmap_count_blocks(sc->tp, sc->ip, XFS_DATA_FORK,
			&nextents, &count);
	अगर (!xchk_should_check_xref(sc, &error, शून्य))
		वापस;
	अगर (nextents < be32_to_cpu(dip->di_nextents))
		xchk_ino_xref_set_corrupt(sc, sc->ip->i_ino);

	error = xfs_bmap_count_blocks(sc->tp, sc->ip, XFS_ATTR_FORK,
			&nextents, &acount);
	अगर (!xchk_should_check_xref(sc, &error, शून्य))
		वापस;
	अगर (nextents != be16_to_cpu(dip->di_anextents))
		xchk_ino_xref_set_corrupt(sc, sc->ip->i_ino);

	/* Check nblocks against the inode. */
	अगर (count + acount != be64_to_cpu(dip->di_nblocks))
		xchk_ino_xref_set_corrupt(sc, sc->ip->i_ino);
पूर्ण

/* Cross-reference with the other btrees. */
STATIC व्योम
xchk_inode_xref(
	काष्ठा xfs_scrub	*sc,
	xfs_ino_t		ino,
	काष्ठा xfs_dinode	*dip)
अणु
	xfs_agnumber_t		agno;
	xfs_agblock_t		agbno;
	पूर्णांक			error;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस;

	agno = XFS_INO_TO_AGNO(sc->mp, ino);
	agbno = XFS_INO_TO_AGBNO(sc->mp, ino);

	error = xchk_ag_init(sc, agno, &sc->sa);
	अगर (!xchk_xref_process_error(sc, agno, agbno, &error))
		वापस;

	xchk_xref_is_used_space(sc, agbno, 1);
	xchk_inode_xref_finobt(sc, ino);
	xchk_xref_is_owned_by(sc, agbno, 1, &XFS_RMAP_OINFO_INODES);
	xchk_xref_is_not_shared(sc, agbno, 1);
	xchk_inode_xref_bmap(sc, dip);

	xchk_ag_मुक्त(sc, &sc->sa);
पूर्ण

/*
 * If the reflink अगरlag disagrees with a scan क्रम shared data विभाजन extents,
 * either flag an error (shared extents w/ no flag) or a preen (flag set w/o
 * any shared extents).  We alपढ़ोy checked क्रम reflink अगरlag set on a non
 * reflink fileप्रणाली.
 */
अटल व्योम
xchk_inode_check_reflink_अगरlag(
	काष्ठा xfs_scrub	*sc,
	xfs_ino_t		ino)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	bool			has_shared;
	पूर्णांक			error;

	अगर (!xfs_sb_version_hasreflink(&mp->m_sb))
		वापस;

	error = xfs_reflink_inode_has_shared_extents(sc->tp, sc->ip,
			&has_shared);
	अगर (!xchk_xref_process_error(sc, XFS_INO_TO_AGNO(mp, ino),
			XFS_INO_TO_AGBNO(mp, ino), &error))
		वापस;
	अगर (xfs_is_reflink_inode(sc->ip) && !has_shared)
		xchk_ino_set_preen(sc, ino);
	अन्यथा अगर (!xfs_is_reflink_inode(sc->ip) && has_shared)
		xchk_ino_set_corrupt(sc, ino);
पूर्ण

/* Scrub an inode. */
पूर्णांक
xchk_inode(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_dinode	di;
	पूर्णांक			error = 0;

	/*
	 * If sc->ip is शून्य, that means that the setup function called
	 * xfs_iget to look up the inode.  xfs_iget वापसed a EFSCORRUPTED
	 * and a शून्य inode, so flag the corruption error and वापस.
	 */
	अगर (!sc->ip) अणु
		xchk_ino_set_corrupt(sc, sc->sm->sm_ino);
		वापस 0;
	पूर्ण

	/* Scrub the inode core. */
	xfs_inode_to_disk(sc->ip, &di, 0);
	xchk_dinode(sc, &di, sc->ip->i_ino);
	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	/*
	 * Look क्रम discrepancies between file's data blocks and the reflink
	 * अगरlag.  We alपढ़ोy checked the अगरlag against the file mode when
	 * we scrubbed the dinode.
	 */
	अगर (S_ISREG(VFS_I(sc->ip)->i_mode))
		xchk_inode_check_reflink_अगरlag(sc, sc->ip->i_ino);

	xchk_inode_xref(sc, sc->ip->i_ino, &di);
out:
	वापस error;
पूर्ण
