<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * Copyright (C) 2017 Oracle.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_format.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_mount.h"

/* Find the size of the AG, in blocks. */
अंतरभूत xfs_agblock_t
xfs_ag_block_count(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno)
अणु
	ASSERT(agno < mp->m_sb.sb_agcount);

	अगर (agno < mp->m_sb.sb_agcount - 1)
		वापस mp->m_sb.sb_agblocks;
	वापस mp->m_sb.sb_dblocks - (agno * mp->m_sb.sb_agblocks);
पूर्ण

/*
 * Verअगरy that an AG block number poपूर्णांकer neither poपूर्णांकs outside the AG
 * nor poपूर्णांकs at अटल metadata.
 */
अंतरभूत bool
xfs_verअगरy_agbno(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		agbno)
अणु
	xfs_agblock_t		eoag;

	eoag = xfs_ag_block_count(mp, agno);
	अगर (agbno >= eoag)
		वापस false;
	अगर (agbno <= XFS_AGFL_BLOCK(mp))
		वापस false;
	वापस true;
पूर्ण

/*
 * Verअगरy that an FS block number poपूर्णांकer neither poपूर्णांकs outside the
 * fileप्रणाली nor poपूर्णांकs at अटल AG metadata.
 */
अंतरभूत bool
xfs_verअगरy_fsbno(
	काष्ठा xfs_mount	*mp,
	xfs_fsblock_t		fsbno)
अणु
	xfs_agnumber_t		agno = XFS_FSB_TO_AGNO(mp, fsbno);

	अगर (agno >= mp->m_sb.sb_agcount)
		वापस false;
	वापस xfs_verअगरy_agbno(mp, agno, XFS_FSB_TO_AGBNO(mp, fsbno));
पूर्ण

/*
 * Verअगरy that a data device extent is fully contained inside the fileप्रणाली,
 * करोes not cross an AG boundary, and करोes not poपूर्णांक at अटल metadata.
 */
bool
xfs_verअगरy_fsbext(
	काष्ठा xfs_mount	*mp,
	xfs_fsblock_t		fsbno,
	xfs_fsblock_t		len)
अणु
	अगर (fsbno + len <= fsbno)
		वापस false;

	अगर (!xfs_verअगरy_fsbno(mp, fsbno))
		वापस false;

	अगर (!xfs_verअगरy_fsbno(mp, fsbno + len - 1))
		वापस false;

	वापस  XFS_FSB_TO_AGNO(mp, fsbno) ==
		XFS_FSB_TO_AGNO(mp, fsbno + len - 1);
पूर्ण

/* Calculate the first and last possible inode number in an AG. */
अंतरभूत व्योम
xfs_agino_range(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno,
	xfs_agino_t		*first,
	xfs_agino_t		*last)
अणु
	xfs_agblock_t		bno;
	xfs_agblock_t		eoag;

	eoag = xfs_ag_block_count(mp, agno);

	/*
	 * Calculate the first inode, which will be in the first
	 * cluster-aligned block after the AGFL.
	 */
	bno = round_up(XFS_AGFL_BLOCK(mp) + 1, M_IGEO(mp)->cluster_align);
	*first = XFS_AGB_TO_AGINO(mp, bno);

	/*
	 * Calculate the last inode, which will be at the end of the
	 * last (aligned) cluster that can be allocated in the AG.
	 */
	bno = round_करोwn(eoag, M_IGEO(mp)->cluster_align);
	*last = XFS_AGB_TO_AGINO(mp, bno) - 1;
पूर्ण

/*
 * Verअगरy that an AG inode number poपूर्णांकer neither poपूर्णांकs outside the AG
 * nor poपूर्णांकs at अटल metadata.
 */
अंतरभूत bool
xfs_verअगरy_agino(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno,
	xfs_agino_t		agino)
अणु
	xfs_agino_t		first;
	xfs_agino_t		last;

	xfs_agino_range(mp, agno, &first, &last);
	वापस agino >= first && agino <= last;
पूर्ण

/*
 * Verअगरy that an AG inode number poपूर्णांकer neither poपूर्णांकs outside the AG
 * nor poपूर्णांकs at अटल metadata, or is शून्यAGINO.
 */
bool
xfs_verअगरy_agino_or_null(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno,
	xfs_agino_t		agino)
अणु
	वापस agino == शून्यAGINO || xfs_verअगरy_agino(mp, agno, agino);
पूर्ण

/*
 * Verअगरy that an FS inode number poपूर्णांकer neither poपूर्णांकs outside the
 * fileप्रणाली nor poपूर्णांकs at अटल AG metadata.
 */
अंतरभूत bool
xfs_verअगरy_ino(
	काष्ठा xfs_mount	*mp,
	xfs_ino_t		ino)
अणु
	xfs_agnumber_t		agno = XFS_INO_TO_AGNO(mp, ino);
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, ino);

	अगर (agno >= mp->m_sb.sb_agcount)
		वापस false;
	अगर (XFS_AGINO_TO_INO(mp, agno, agino) != ino)
		वापस false;
	वापस xfs_verअगरy_agino(mp, agno, agino);
पूर्ण

/* Is this an पूर्णांकernal inode number? */
अंतरभूत bool
xfs_पूर्णांकernal_inum(
	काष्ठा xfs_mount	*mp,
	xfs_ino_t		ino)
अणु
	वापस ino == mp->m_sb.sb_rbmino || ino == mp->m_sb.sb_rsumino ||
		(xfs_sb_version_hasquota(&mp->m_sb) &&
		 xfs_is_quota_inode(&mp->m_sb, ino));
पूर्ण

/*
 * Verअगरy that a directory entry's inode number doesn't poपूर्णांक at an पूर्णांकernal
 * inode, empty space, or अटल AG metadata.
 */
bool
xfs_verअगरy_dir_ino(
	काष्ठा xfs_mount	*mp,
	xfs_ino_t		ino)
अणु
	अगर (xfs_पूर्णांकernal_inum(mp, ino))
		वापस false;
	वापस xfs_verअगरy_ino(mp, ino);
पूर्ण

/*
 * Verअगरy that an realसमय block number poपूर्णांकer करोesn't poपूर्णांक off the
 * end of the realसमय device.
 */
अंतरभूत bool
xfs_verअगरy_rtbno(
	काष्ठा xfs_mount	*mp,
	xfs_rtblock_t		rtbno)
अणु
	वापस rtbno < mp->m_sb.sb_rblocks;
पूर्ण

/* Verअगरy that a realसमय device extent is fully contained inside the volume. */
bool
xfs_verअगरy_rtext(
	काष्ठा xfs_mount	*mp,
	xfs_rtblock_t		rtbno,
	xfs_rtblock_t		len)
अणु
	अगर (rtbno + len <= rtbno)
		वापस false;

	अगर (!xfs_verअगरy_rtbno(mp, rtbno))
		वापस false;

	वापस xfs_verअगरy_rtbno(mp, rtbno + len - 1);
पूर्ण

/* Calculate the range of valid icount values. */
अंतरभूत व्योम
xfs_icount_range(
	काष्ठा xfs_mount	*mp,
	अचिन्हित दीर्घ दीर्घ	*min,
	अचिन्हित दीर्घ दीर्घ	*max)
अणु
	अचिन्हित दीर्घ दीर्घ	nr_inos = 0;
	xfs_agnumber_t		agno;

	/* root, rtbiपंचांगap, rtsum all live in the first chunk */
	*min = XFS_INODES_PER_CHUNK;

	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		xfs_agino_t	first, last;

		xfs_agino_range(mp, agno, &first, &last);
		nr_inos += last - first + 1;
	पूर्ण
	*max = nr_inos;
पूर्ण

/* Sanity-checking of inode counts. */
bool
xfs_verअगरy_icount(
	काष्ठा xfs_mount	*mp,
	अचिन्हित दीर्घ दीर्घ	icount)
अणु
	अचिन्हित दीर्घ दीर्घ	min, max;

	xfs_icount_range(mp, &min, &max);
	वापस icount >= min && icount <= max;
पूर्ण

/* Sanity-checking of dir/attr block offsets. */
bool
xfs_verअगरy_dablk(
	काष्ठा xfs_mount	*mp,
	xfs_fileoff_t		dabno)
अणु
	xfs_dablk_t		max_dablk = -1U;

	वापस dabno <= max_dablk;
पूर्ण

/* Check that a file block offset करोes not exceed the maximum. */
bool
xfs_verअगरy_fileoff(
	काष्ठा xfs_mount	*mp,
	xfs_fileoff_t		off)
अणु
	वापस off <= XFS_MAX_खाताOFF;
पूर्ण

/* Check that a range of file block offsets करो not exceed the maximum. */
bool
xfs_verअगरy_fileext(
	काष्ठा xfs_mount	*mp,
	xfs_fileoff_t		off,
	xfs_fileoff_t		len)
अणु
	अगर (off + len <= off)
		वापस false;

	अगर (!xfs_verअगरy_fileoff(mp, off))
		वापस false;

	वापस xfs_verअगरy_fileoff(mp, off + len - 1);
पूर्ण
