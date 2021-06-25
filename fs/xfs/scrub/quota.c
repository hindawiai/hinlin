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
#समावेश "xfs_inode.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_qm.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"

/* Convert a scrub type code to a DQ flag, or वापस 0 अगर error. */
अटल अंतरभूत xfs_dqtype_t
xchk_quota_to_dqtype(
	काष्ठा xfs_scrub	*sc)
अणु
	चयन (sc->sm->sm_type) अणु
	हाल XFS_SCRUB_TYPE_UQUOTA:
		वापस XFS_DQTYPE_USER;
	हाल XFS_SCRUB_TYPE_GQUOTA:
		वापस XFS_DQTYPE_GROUP;
	हाल XFS_SCRUB_TYPE_PQUOTA:
		वापस XFS_DQTYPE_PROJ;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Set us up to scrub a quota. */
पूर्णांक
xchk_setup_quota(
	काष्ठा xfs_scrub	*sc)
अणु
	xfs_dqtype_t		dqtype;
	पूर्णांक			error;

	अगर (!XFS_IS_QUOTA_RUNNING(sc->mp) || !XFS_IS_QUOTA_ON(sc->mp))
		वापस -ENOENT;

	dqtype = xchk_quota_to_dqtype(sc);
	अगर (dqtype == 0)
		वापस -EINVAL;
	sc->flags |= XCHK_HAS_QUOTAOFFLOCK;
	mutex_lock(&sc->mp->m_quotainfo->qi_quotaofflock);
	अगर (!xfs_this_quota_on(sc->mp, dqtype))
		वापस -ENOENT;
	error = xchk_setup_fs(sc);
	अगर (error)
		वापस error;
	sc->ip = xfs_quota_inode(sc->mp, dqtype);
	xfs_ilock(sc->ip, XFS_ILOCK_EXCL);
	sc->ilock_flags = XFS_ILOCK_EXCL;
	वापस 0;
पूर्ण

/* Quotas. */

काष्ठा xchk_quota_info अणु
	काष्ठा xfs_scrub	*sc;
	xfs_dqid_t		last_id;
पूर्ण;

/* Scrub the fields in an inभागidual quota item. */
STATIC पूर्णांक
xchk_quota_item(
	काष्ठा xfs_dquot	*dq,
	xfs_dqtype_t		dqtype,
	व्योम			*priv)
अणु
	काष्ठा xchk_quota_info	*sqi = priv;
	काष्ठा xfs_scrub	*sc = sqi->sc;
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_quotainfo	*qi = mp->m_quotainfo;
	xfs_fileoff_t		offset;
	xfs_ino_t		fs_icount;
	पूर्णांक			error = 0;

	अगर (xchk_should_terminate(sc, &error))
		वापस -ECANCELED;

	/*
	 * Except क्रम the root dquot, the actual dquot we got must either have
	 * the same or higher id as we saw beक्रमe.
	 */
	offset = dq->q_id / qi->qi_dqperchunk;
	अगर (dq->q_id && dq->q_id <= sqi->last_id)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, offset);

	sqi->last_id = dq->q_id;

	/*
	 * Warn अगर the hard limits are larger than the fs.
	 * Administrators can करो this, though in production this seems
	 * suspect, which is why we flag it क्रम review.
	 *
	 * Complain about corruption अगर the soft limit is greater than
	 * the hard limit.
	 */
	अगर (dq->q_blk.hardlimit > mp->m_sb.sb_dblocks)
		xchk_fblock_set_warning(sc, XFS_DATA_FORK, offset);
	अगर (dq->q_blk.softlimit > dq->q_blk.hardlimit)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, offset);

	अगर (dq->q_ino.hardlimit > M_IGEO(mp)->maxicount)
		xchk_fblock_set_warning(sc, XFS_DATA_FORK, offset);
	अगर (dq->q_ino.softlimit > dq->q_ino.hardlimit)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, offset);

	अगर (dq->q_rtb.hardlimit > mp->m_sb.sb_rblocks)
		xchk_fblock_set_warning(sc, XFS_DATA_FORK, offset);
	अगर (dq->q_rtb.softlimit > dq->q_rtb.hardlimit)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, offset);

	/* Check the resource counts. */
	fs_icount = percpu_counter_sum(&mp->m_icount);

	/*
	 * Check that usage करोesn't exceed physical limits.  However, on
	 * a reflink fileप्रणाली we're allowed to exceed physical space
	 * अगर there are no quota limits.
	 */
	अगर (xfs_sb_version_hasreflink(&mp->m_sb)) अणु
		अगर (mp->m_sb.sb_dblocks < dq->q_blk.count)
			xchk_fblock_set_warning(sc, XFS_DATA_FORK,
					offset);
	पूर्ण अन्यथा अणु
		अगर (mp->m_sb.sb_dblocks < dq->q_blk.count)
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK,
					offset);
	पूर्ण
	अगर (dq->q_ino.count > fs_icount || dq->q_rtb.count > mp->m_sb.sb_rblocks)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, offset);

	/*
	 * We can violate the hard limits अगर the admin suddenly sets a
	 * lower limit than the actual usage.  However, we flag it क्रम
	 * admin review.
	 */
	अगर (dq->q_id == 0)
		जाओ out;

	अगर (dq->q_blk.hardlimit != 0 &&
	    dq->q_blk.count > dq->q_blk.hardlimit)
		xchk_fblock_set_warning(sc, XFS_DATA_FORK, offset);

	अगर (dq->q_ino.hardlimit != 0 &&
	    dq->q_ino.count > dq->q_ino.hardlimit)
		xchk_fblock_set_warning(sc, XFS_DATA_FORK, offset);

	अगर (dq->q_rtb.hardlimit != 0 &&
	    dq->q_rtb.count > dq->q_rtb.hardlimit)
		xchk_fblock_set_warning(sc, XFS_DATA_FORK, offset);

out:
	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस -ECANCELED;

	वापस 0;
पूर्ण

/* Check the quota's data विभाजन. */
STATIC पूर्णांक
xchk_quota_data_विभाजन(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_bmbt_irec	irec = अणु 0 पूर्ण;
	काष्ठा xfs_iext_cursor	icur;
	काष्ठा xfs_quotainfo	*qi = sc->mp->m_quotainfo;
	काष्ठा xfs_अगरork	*अगरp;
	xfs_fileoff_t		max_dqid_off;
	पूर्णांक			error = 0;

	/* Invoke the विभाजन scrubber. */
	error = xchk_metadata_inode_विभाजनs(sc);
	अगर (error || (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
		वापस error;

	/* Check क्रम data विभाजन problems that apply only to quota files. */
	max_dqid_off = ((xfs_dqid_t)-1) / qi->qi_dqperchunk;
	अगरp = XFS_IFORK_PTR(sc->ip, XFS_DATA_FORK);
	क्रम_each_xfs_iext(अगरp, &icur, &irec) अणु
		अगर (xchk_should_terminate(sc, &error))
			अवरोध;
		/*
		 * delalloc extents or blocks mapped above the highest
		 * quota id shouldn't happen.
		 */
		अगर (isnullstartblock(irec.br_startblock) ||
		    irec.br_startoff > max_dqid_off ||
		    irec.br_startoff + irec.br_blockcount - 1 > max_dqid_off) अणु
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK,
					irec.br_startoff);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस error;
पूर्ण

/* Scrub all of a quota type's items. */
पूर्णांक
xchk_quota(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xchk_quota_info	sqi;
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_quotainfo	*qi = mp->m_quotainfo;
	xfs_dqtype_t		dqtype;
	पूर्णांक			error = 0;

	dqtype = xchk_quota_to_dqtype(sc);

	/* Look क्रम problem extents. */
	error = xchk_quota_data_विभाजन(sc);
	अगर (error)
		जाओ out;
	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	/*
	 * Check all the quota items.  Now that we've checked the quota inode
	 * data विभाजन we have to drop ILOCK_EXCL to use the regular dquot
	 * functions.
	 */
	xfs_iunlock(sc->ip, sc->ilock_flags);
	sc->ilock_flags = 0;
	sqi.sc = sc;
	sqi.last_id = 0;
	error = xfs_qm_dqiterate(mp, dqtype, xchk_quota_item, &sqi);
	sc->ilock_flags = XFS_ILOCK_EXCL;
	xfs_ilock(sc->ip, sc->ilock_flags);
	अगर (error == -ECANCELED)
		error = 0;
	अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK,
			sqi.last_id * qi->qi_dqperchunk, &error))
		जाओ out;

out:
	वापस error;
पूर्ण
