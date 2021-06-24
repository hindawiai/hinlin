<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_ialloc_btree.h"
#समावेश "xfs_iwalk.h"
#समावेश "xfs_itable.h"
#समावेश "xfs_error.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_health.h"

/*
 * Bulk Stat
 * =========
 *
 * Use the inode walking functions to fill out काष्ठा xfs_bulkstat क्रम every
 * allocated inode, then pass the stat inक्रमmation to some बाह्यally provided
 * iteration function.
 */

काष्ठा xfs_bstat_chunk अणु
	bulkstat_one_fmt_pf	क्रमmatter;
	काष्ठा xfs_ibulk	*breq;
	काष्ठा xfs_bulkstat	*buf;
पूर्ण;

/*
 * Fill out the bulkstat info क्रम a single inode and report it somewhere.
 *
 * bc->breq->lastino is effectively the inode cursor as we walk through the
 * fileप्रणाली.  Thereक्रमe, we update it any समय we need to move the cursor
 * क्रमward, regardless of whether or not we're sending any bstat inक्रमmation
 * back to userspace.  If the inode is पूर्णांकernal metadata or, has been मुक्तd
 * out from under us, we just simply keep going.
 *
 * However, अगर any other type of error happens we want to stop right where we
 * are so that userspace will call back with exact number of the bad inode and
 * we can send back an error code.
 *
 * Note that अगर the क्रमmatter tells us there's no space left in the buffer we
 * move the cursor क्रमward and पात the walk.
 */
STATIC पूर्णांक
xfs_bulkstat_one_पूर्णांक(
	काष्ठा xfs_mount	*mp,
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा xfs_trans	*tp,
	xfs_ino_t		ino,
	काष्ठा xfs_bstat_chunk	*bc)
अणु
	काष्ठा user_namespace	*sb_userns = mp->m_super->s_user_ns;
	काष्ठा xfs_inode	*ip;		/* incore inode poपूर्णांकer */
	काष्ठा inode		*inode;
	काष्ठा xfs_bulkstat	*buf = bc->buf;
	पूर्णांक			error = -EINVAL;

	अगर (xfs_पूर्णांकernal_inum(mp, ino))
		जाओ out_advance;

	error = xfs_iget(mp, tp, ino,
			 (XFS_IGET_DONTCACHE | XFS_IGET_UNTRUSTED),
			 XFS_ILOCK_SHARED, &ip);
	अगर (error == -ENOENT || error == -EINVAL)
		जाओ out_advance;
	अगर (error)
		जाओ out;

	ASSERT(ip != शून्य);
	ASSERT(ip->i_imap.im_blkno != 0);
	inode = VFS_I(ip);

	/* xfs_iget वापसs the following without needing
	 * further change.
	 */
	buf->bs_projectid = ip->i_projid;
	buf->bs_ino = ino;
	buf->bs_uid = from_kuid(sb_userns, i_uid_पूर्णांकo_mnt(mnt_userns, inode));
	buf->bs_gid = from_kgid(sb_userns, i_gid_पूर्णांकo_mnt(mnt_userns, inode));
	buf->bs_size = ip->i_disk_size;

	buf->bs_nlink = inode->i_nlink;
	buf->bs_aसमय = inode->i_aसमय.tv_sec;
	buf->bs_aसमय_nsec = inode->i_aसमय.tv_nsec;
	buf->bs_mसमय = inode->i_mसमय.tv_sec;
	buf->bs_mसमय_nsec = inode->i_mसमय.tv_nsec;
	buf->bs_स_समय = inode->i_स_समय.tv_sec;
	buf->bs_स_समय_nsec = inode->i_स_समय.tv_nsec;
	buf->bs_gen = inode->i_generation;
	buf->bs_mode = inode->i_mode;

	buf->bs_xflags = xfs_ip2xflags(ip);
	buf->bs_extsize_blks = ip->i_extsize;
	buf->bs_extents = xfs_अगरork_nextents(&ip->i_df);
	xfs_bulkstat_health(ip, buf);
	buf->bs_aextents = xfs_अगरork_nextents(ip->i_afp);
	buf->bs_विभाजनoff = XFS_IFORK_BOFF(ip);
	buf->bs_version = XFS_BULKSTAT_VERSION_V5;

	अगर (xfs_sb_version_has_v3inode(&mp->m_sb)) अणु
		buf->bs_bसमय = ip->i_crसमय.tv_sec;
		buf->bs_bसमय_nsec = ip->i_crसमय.tv_nsec;
		अगर (ip->i_dअगरlags2 & XFS_DIFLAG2_COWEXTSIZE)
			buf->bs_cowextsize_blks = ip->i_cowextsize;
	पूर्ण

	चयन (ip->i_df.अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_DEV:
		buf->bs_rdev = sysv_encode_dev(inode->i_rdev);
		buf->bs_blksize = BLKDEV_IOSIZE;
		buf->bs_blocks = 0;
		अवरोध;
	हाल XFS_DINODE_FMT_LOCAL:
		buf->bs_rdev = 0;
		buf->bs_blksize = mp->m_sb.sb_blocksize;
		buf->bs_blocks = 0;
		अवरोध;
	हाल XFS_DINODE_FMT_EXTENTS:
	हाल XFS_DINODE_FMT_BTREE:
		buf->bs_rdev = 0;
		buf->bs_blksize = mp->m_sb.sb_blocksize;
		buf->bs_blocks = ip->i_nblocks + ip->i_delayed_blks;
		अवरोध;
	पूर्ण
	xfs_iunlock(ip, XFS_ILOCK_SHARED);
	xfs_irele(ip);

	error = bc->क्रमmatter(bc->breq, buf);
	अगर (error == -ECANCELED)
		जाओ out_advance;
	अगर (error)
		जाओ out;

out_advance:
	/*
	 * Advance the cursor to the inode that comes after the one we just
	 * looked at.  We want the caller to move aदीर्घ अगर the bulkstat
	 * inक्रमmation was copied successfully; अगर we tried to grab the inode
	 * but it's no longer allocated; or if it's पूर्णांकernal metadata.
	 */
	bc->breq->startino = ino + 1;
out:
	वापस error;
पूर्ण

/* Bulkstat a single inode. */
पूर्णांक
xfs_bulkstat_one(
	काष्ठा xfs_ibulk	*breq,
	bulkstat_one_fmt_pf	क्रमmatter)
अणु
	काष्ठा xfs_bstat_chunk	bc = अणु
		.क्रमmatter	= क्रमmatter,
		.breq		= breq,
	पूर्ण;
	पूर्णांक			error;

	अगर (breq->mnt_userns != &init_user_ns) अणु
		xfs_warn_ratelimited(breq->mp,
			"bulkstat not supported inside of idmapped mounts.");
		वापस -EINVAL;
	पूर्ण

	ASSERT(breq->icount == 1);

	bc.buf = kmem_zalloc(माप(काष्ठा xfs_bulkstat),
			KM_MAYFAIL);
	अगर (!bc.buf)
		वापस -ENOMEM;

	error = xfs_bulkstat_one_पूर्णांक(breq->mp, breq->mnt_userns, शून्य,
				     breq->startino, &bc);

	kmem_मुक्त(bc.buf);

	/*
	 * If we reported one inode to userspace then we पात because we hit
	 * the end of the buffer.  Don't leak that back to userspace.
	 */
	अगर (error == -ECANCELED)
		error = 0;

	वापस error;
पूर्ण

अटल पूर्णांक
xfs_bulkstat_iwalk(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_ino_t		ino,
	व्योम			*data)
अणु
	काष्ठा xfs_bstat_chunk	*bc = data;
	पूर्णांक			error;

	error = xfs_bulkstat_one_पूर्णांक(mp, bc->breq->mnt_userns, tp, ino, data);
	/* bulkstat just skips over missing inodes */
	अगर (error == -ENOENT || error == -EINVAL)
		वापस 0;
	वापस error;
पूर्ण

/*
 * Check the incoming lastino parameter.
 *
 * We allow any inode value that could map to physical space inside the
 * fileप्रणाली because अगर there are no inodes there, bulkstat moves on to the
 * next chunk.  In other words, the magic agino value of zero takes us to the
 * first chunk in the AG, and an agino value past the end of the AG takes us to
 * the first chunk in the next AG.
 *
 * Thereक्रमe we can end early अगर the requested inode is beyond the end of the
 * fileप्रणाली or करोesn't map properly.
 */
अटल अंतरभूत bool
xfs_bulkstat_alपढ़ोy_करोne(
	काष्ठा xfs_mount	*mp,
	xfs_ino_t		startino)
अणु
	xfs_agnumber_t		agno = XFS_INO_TO_AGNO(mp, startino);
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, startino);

	वापस agno >= mp->m_sb.sb_agcount ||
	       startino != XFS_AGINO_TO_INO(mp, agno, agino);
पूर्ण

/* Return stat inक्रमmation in bulk (by-inode) क्रम the fileप्रणाली. */
पूर्णांक
xfs_bulkstat(
	काष्ठा xfs_ibulk	*breq,
	bulkstat_one_fmt_pf	क्रमmatter)
अणु
	काष्ठा xfs_bstat_chunk	bc = अणु
		.क्रमmatter	= क्रमmatter,
		.breq		= breq,
	पूर्ण;
	पूर्णांक			error;

	अगर (breq->mnt_userns != &init_user_ns) अणु
		xfs_warn_ratelimited(breq->mp,
			"bulkstat not supported inside of idmapped mounts.");
		वापस -EINVAL;
	पूर्ण
	अगर (xfs_bulkstat_alपढ़ोy_करोne(breq->mp, breq->startino))
		वापस 0;

	bc.buf = kmem_zalloc(माप(काष्ठा xfs_bulkstat),
			KM_MAYFAIL);
	अगर (!bc.buf)
		वापस -ENOMEM;

	error = xfs_iwalk(breq->mp, शून्य, breq->startino, breq->flags,
			xfs_bulkstat_iwalk, breq->icount, &bc);

	kmem_मुक्त(bc.buf);

	/*
	 * We found some inodes, so clear the error status and वापस them.
	 * The lastino poपूर्णांकer will poपूर्णांक directly at the inode that triggered
	 * any error that occurred, so on the next call the error will be
	 * triggered again and propagated to userspace as there will be no
	 * क्रमmatted inodes in the buffer.
	 */
	अगर (breq->ocount > 0)
		error = 0;

	वापस error;
पूर्ण

/* Convert bulkstat (v5) to bstat (v1). */
व्योम
xfs_bulkstat_to_bstat(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_bstat		*bs1,
	स्थिर काष्ठा xfs_bulkstat	*bstat)
अणु
	/* स_रखो is needed here because of padding holes in the काष्ठाure. */
	स_रखो(bs1, 0, माप(काष्ठा xfs_bstat));
	bs1->bs_ino = bstat->bs_ino;
	bs1->bs_mode = bstat->bs_mode;
	bs1->bs_nlink = bstat->bs_nlink;
	bs1->bs_uid = bstat->bs_uid;
	bs1->bs_gid = bstat->bs_gid;
	bs1->bs_rdev = bstat->bs_rdev;
	bs1->bs_blksize = bstat->bs_blksize;
	bs1->bs_size = bstat->bs_size;
	bs1->bs_aसमय.tv_sec = bstat->bs_aसमय;
	bs1->bs_mसमय.tv_sec = bstat->bs_mसमय;
	bs1->bs_स_समय.tv_sec = bstat->bs_स_समय;
	bs1->bs_aसमय.tv_nsec = bstat->bs_aसमय_nsec;
	bs1->bs_mसमय.tv_nsec = bstat->bs_mसमय_nsec;
	bs1->bs_स_समय.tv_nsec = bstat->bs_स_समय_nsec;
	bs1->bs_blocks = bstat->bs_blocks;
	bs1->bs_xflags = bstat->bs_xflags;
	bs1->bs_extsize = XFS_FSB_TO_B(mp, bstat->bs_extsize_blks);
	bs1->bs_extents = bstat->bs_extents;
	bs1->bs_gen = bstat->bs_gen;
	bs1->bs_projid_lo = bstat->bs_projectid & 0xFFFF;
	bs1->bs_विभाजनoff = bstat->bs_विभाजनoff;
	bs1->bs_projid_hi = bstat->bs_projectid >> 16;
	bs1->bs_sick = bstat->bs_sick;
	bs1->bs_checked = bstat->bs_checked;
	bs1->bs_cowextsize = XFS_FSB_TO_B(mp, bstat->bs_cowextsize_blks);
	bs1->bs_dmevmask = 0;
	bs1->bs_dmstate = 0;
	bs1->bs_aextents = bstat->bs_aextents;
पूर्ण

काष्ठा xfs_inumbers_chunk अणु
	inumbers_fmt_pf		क्रमmatter;
	काष्ठा xfs_ibulk	*breq;
पूर्ण;

/*
 * INUMBERS
 * ========
 * This is how we export inode btree records to userspace, so that XFS tools
 * can figure out where inodes are allocated.
 */

/*
 * Format the inode group काष्ठाure and report it somewhere.
 *
 * Similar to xfs_bulkstat_one_पूर्णांक, lastino is the inode cursor as we walk
 * through the fileप्रणाली so we move it क्रमward unless there was a runसमय
 * error.  If the क्रमmatter tells us the buffer is now full we also move the
 * cursor क्रमward and पात the walk.
 */
STATIC पूर्णांक
xfs_inumbers_walk(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	स्थिर काष्ठा xfs_inobt_rec_incore *irec,
	व्योम			*data)
अणु
	काष्ठा xfs_inumbers	inogrp = अणु
		.xi_startino	= XFS_AGINO_TO_INO(mp, agno, irec->ir_startino),
		.xi_alloccount	= irec->ir_count - irec->ir_मुक्तcount,
		.xi_allocmask	= ~irec->ir_मुक्त,
		.xi_version	= XFS_INUMBERS_VERSION_V5,
	पूर्ण;
	काष्ठा xfs_inumbers_chunk *ic = data;
	पूर्णांक			error;

	error = ic->क्रमmatter(ic->breq, &inogrp);
	अगर (error && error != -ECANCELED)
		वापस error;

	ic->breq->startino = XFS_AGINO_TO_INO(mp, agno, irec->ir_startino) +
			XFS_INODES_PER_CHUNK;
	वापस error;
पूर्ण

/*
 * Return inode number table क्रम the fileप्रणाली.
 */
पूर्णांक
xfs_inumbers(
	काष्ठा xfs_ibulk	*breq,
	inumbers_fmt_pf		क्रमmatter)
अणु
	काष्ठा xfs_inumbers_chunk ic = अणु
		.क्रमmatter	= क्रमmatter,
		.breq		= breq,
	पूर्ण;
	पूर्णांक			error = 0;

	अगर (xfs_bulkstat_alपढ़ोy_करोne(breq->mp, breq->startino))
		वापस 0;

	error = xfs_inobt_walk(breq->mp, शून्य, breq->startino, breq->flags,
			xfs_inumbers_walk, breq->icount, &ic);

	/*
	 * We found some inode groups, so clear the error status and वापस
	 * them.  The lastino poपूर्णांकer will poपूर्णांक directly at the inode that
	 * triggered any error that occurred, so on the next call the error
	 * will be triggered again and propagated to userspace as there will be
	 * no क्रमmatted inode groups in the buffer.
	 */
	अगर (breq->ocount > 0)
		error = 0;

	वापस error;
पूर्ण

/* Convert an inumbers (v5) काष्ठा to a inogrp (v1) काष्ठा. */
व्योम
xfs_inumbers_to_inogrp(
	काष्ठा xfs_inogrp		*ig1,
	स्थिर काष्ठा xfs_inumbers	*ig)
अणु
	/* स_रखो is needed here because of padding holes in the काष्ठाure. */
	स_रखो(ig1, 0, माप(काष्ठा xfs_inogrp));
	ig1->xi_startino = ig->xi_startino;
	ig1->xi_alloccount = ig->xi_alloccount;
	ig1->xi_allocmask = ig->xi_allocmask;
पूर्ण
