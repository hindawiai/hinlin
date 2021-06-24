<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_qm.h"


STATIC व्योम
xfs_fill_statvfs_from_dquot(
	काष्ठा kstatfs		*statp,
	काष्ठा xfs_dquot	*dqp)
अणु
	uपूर्णांक64_t		limit;

	limit = dqp->q_blk.softlimit ?
		dqp->q_blk.softlimit :
		dqp->q_blk.hardlimit;
	अगर (limit && statp->f_blocks > limit) अणु
		statp->f_blocks = limit;
		statp->f_bमुक्त = statp->f_bavail =
			(statp->f_blocks > dqp->q_blk.reserved) ?
			 (statp->f_blocks - dqp->q_blk.reserved) : 0;
	पूर्ण

	limit = dqp->q_ino.softlimit ?
		dqp->q_ino.softlimit :
		dqp->q_ino.hardlimit;
	अगर (limit && statp->f_files > limit) अणु
		statp->f_files = limit;
		statp->f_fमुक्त =
			(statp->f_files > dqp->q_ino.reserved) ?
			 (statp->f_files - dqp->q_ino.reserved) : 0;
	पूर्ण
पूर्ण


/*
 * Directory tree accounting is implemented using project quotas, where
 * the project identअगरier is inherited from parent directories.
 * A statvfs (df, etc.) of a directory that is using project quota should
 * वापस a statvfs of the project, not the entire fileप्रणाली.
 * This makes such trees appear as अगर they are fileप्रणालीs in themselves.
 */
व्योम
xfs_qm_statvfs(
	काष्ठा xfs_inode	*ip,
	काष्ठा kstatfs		*statp)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_dquot	*dqp;

	अगर (!xfs_qm_dqget(mp, ip->i_projid, XFS_DQTYPE_PROJ, false, &dqp)) अणु
		xfs_fill_statvfs_from_dquot(statp, dqp);
		xfs_qm_dqput(dqp);
	पूर्ण
पूर्ण

पूर्णांक
xfs_qm_newmount(
	xfs_mount_t	*mp,
	uपूर्णांक		*needquotamount,
	uपूर्णांक		*quotaflags)
अणु
	uपूर्णांक		quotaondisk;
	uपूर्णांक		uquotaondisk = 0, gquotaondisk = 0, pquotaondisk = 0;

	quotaondisk = xfs_sb_version_hasquota(&mp->m_sb) &&
				(mp->m_sb.sb_qflags & XFS_ALL_QUOTA_ACCT);

	अगर (quotaondisk) अणु
		uquotaondisk = mp->m_sb.sb_qflags & XFS_UQUOTA_ACCT;
		pquotaondisk = mp->m_sb.sb_qflags & XFS_PQUOTA_ACCT;
		gquotaondisk = mp->m_sb.sb_qflags & XFS_GQUOTA_ACCT;
	पूर्ण

	/*
	 * If the device itself is पढ़ो-only, we can't allow
	 * the user to change the state of quota on the mount -
	 * this would generate a transaction on the ro device,
	 * which would lead to an I/O error and shutकरोwn
	 */

	अगर (((uquotaondisk && !XFS_IS_UQUOTA_ON(mp)) ||
	    (!uquotaondisk &&  XFS_IS_UQUOTA_ON(mp)) ||
	     (gquotaondisk && !XFS_IS_GQUOTA_ON(mp)) ||
	    (!gquotaondisk &&  XFS_IS_GQUOTA_ON(mp)) ||
	     (pquotaondisk && !XFS_IS_PQUOTA_ON(mp)) ||
	    (!pquotaondisk &&  XFS_IS_PQUOTA_ON(mp)))  &&
	    xfs_dev_is_पढ़ो_only(mp, "changing quota state")) अणु
		xfs_warn(mp, "please mount with%s%s%s%s.",
			(!quotaondisk ? "out quota" : ""),
			(uquotaondisk ? " usrquota" : ""),
			(gquotaondisk ? " grpquota" : ""),
			(pquotaondisk ? " prjquota" : ""));
		वापस -EPERM;
	पूर्ण

	अगर (XFS_IS_QUOTA_ON(mp) || quotaondisk) अणु
		/*
		 * Call mount_quotas at this poपूर्णांक only अगर we won't have to करो
		 * a quotacheck.
		 */
		अगर (quotaondisk && !XFS_QM_NEED_QUOTACHECK(mp)) अणु
			/*
			 * If an error occurred, qm_mount_quotas code
			 * has alपढ़ोy disabled quotas. So, just finish
			 * mounting, and get on with the boring lअगरe
			 * without disk quotas.
			 */
			xfs_qm_mount_quotas(mp);
		पूर्ण अन्यथा अणु
			/*
			 * Clear the quota flags, but remember them. This
			 * is so that the quota code करोesn't get invoked
			 * beक्रमe we're पढ़ोy. This can happen when an
			 * inode goes inactive and wants to मुक्त blocks,
			 * or via xfs_log_mount_finish.
			 */
			*needquotamount = true;
			*quotaflags = mp->m_qflags;
			mp->m_qflags = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
