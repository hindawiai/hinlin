<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */


#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_qm.h"
#समावेश "xfs_icache.h"

STATIC पूर्णांक
xfs_qm_log_quotaoff(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_qoff_logitem	**qoffstartp,
	uपूर्णांक			flags)
अणु
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;
	काष्ठा xfs_qoff_logitem	*qoffi;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_qm_quotaoff, 0, 0, 0, &tp);
	अगर (error)
		जाओ out;

	qoffi = xfs_trans_get_qoff_item(tp, शून्य, flags & XFS_ALL_QUOTA_ACCT);
	xfs_trans_log_quotaoff_item(tp, qoffi);

	spin_lock(&mp->m_sb_lock);
	mp->m_sb.sb_qflags = (mp->m_qflags & ~(flags)) & XFS_MOUNT_QUOTA_ALL;
	spin_unlock(&mp->m_sb_lock);

	xfs_log_sb(tp);

	/*
	 * We have to make sure that the transaction is secure on disk beक्रमe we
	 * वापस and actually stop quota accounting. So, make it synchronous.
	 * We करोn't care about quotoff's perक्रमmance.
	 */
	xfs_trans_set_sync(tp);
	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ out;

	*qoffstartp = qoffi;
out:
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_qm_log_quotaoff_end(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_qoff_logitem	**startqoff,
	uपूर्णांक			flags)
अणु
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;
	काष्ठा xfs_qoff_logitem	*qoffi;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_qm_equotaoff, 0, 0, 0, &tp);
	अगर (error)
		वापस error;

	qoffi = xfs_trans_get_qoff_item(tp, *startqoff,
					flags & XFS_ALL_QUOTA_ACCT);
	xfs_trans_log_quotaoff_item(tp, qoffi);
	*startqoff = शून्य;

	/*
	 * We have to make sure that the transaction is secure on disk beक्रमe we
	 * वापस and actually stop quota accounting. So, make it synchronous.
	 * We करोn't care about quotoff's perक्रमmance.
	 */
	xfs_trans_set_sync(tp);
	वापस xfs_trans_commit(tp);
पूर्ण

/*
 * Turn off quota accounting and/or enक्रमcement क्रम all udquots and/or
 * gdquots. Called only at unmount समय.
 *
 * This assumes that there are no dquots of this file प्रणाली cached
 * incore, and modअगरies the ondisk dquot directly. Thereक्रमe, क्रम example,
 * it is an error to call this twice, without purging the cache.
 */
पूर्णांक
xfs_qm_scall_quotaoff(
	xfs_mount_t		*mp,
	uपूर्णांक			flags)
अणु
	काष्ठा xfs_quotainfo	*q = mp->m_quotainfo;
	uपूर्णांक			dqtype;
	पूर्णांक			error;
	uपूर्णांक			inactivate_flags;
	काष्ठा xfs_qoff_logitem	*qoffstart = शून्य;

	/*
	 * No file प्रणाली can have quotas enabled on disk but not in core.
	 * Note that quota utilities (like quotaoff) _expect_
	 * त्रुटि_सं == -EEXIST here.
	 */
	अगर ((mp->m_qflags & flags) == 0)
		वापस -EEXIST;
	error = 0;

	flags &= (XFS_ALL_QUOTA_ACCT | XFS_ALL_QUOTA_ENFD);

	/*
	 * We करोn't want to deal with two quotaoffs messing up each other,
	 * so we're going to serialize it. quotaoff isn't exactly a perक्रमmance
	 * critical thing.
	 * If quotaoff, then we must be dealing with the root fileप्रणाली.
	 */
	ASSERT(q);
	mutex_lock(&q->qi_quotaofflock);

	/*
	 * If we're just turning off quota enक्रमcement, change mp and go.
	 */
	अगर ((flags & XFS_ALL_QUOTA_ACCT) == 0) अणु
		mp->m_qflags &= ~(flags);

		spin_lock(&mp->m_sb_lock);
		mp->m_sb.sb_qflags = mp->m_qflags;
		spin_unlock(&mp->m_sb_lock);
		mutex_unlock(&q->qi_quotaofflock);

		/* XXX what to करो अगर error ? Revert back to old vals incore ? */
		वापस xfs_sync_sb(mp, false);
	पूर्ण

	dqtype = 0;
	inactivate_flags = 0;
	/*
	 * If accounting is off, we must turn enक्रमcement off, clear the
	 * quota 'CHKD' certअगरicate to make it known that we have to
	 * करो a quotacheck the next समय this quota is turned on.
	 */
	अगर (flags & XFS_UQUOTA_ACCT) अणु
		dqtype |= XFS_QMOPT_UQUOTA;
		flags |= (XFS_UQUOTA_CHKD | XFS_UQUOTA_ENFD);
		inactivate_flags |= XFS_UQUOTA_ACTIVE;
	पूर्ण
	अगर (flags & XFS_GQUOTA_ACCT) अणु
		dqtype |= XFS_QMOPT_GQUOTA;
		flags |= (XFS_GQUOTA_CHKD | XFS_GQUOTA_ENFD);
		inactivate_flags |= XFS_GQUOTA_ACTIVE;
	पूर्ण
	अगर (flags & XFS_PQUOTA_ACCT) अणु
		dqtype |= XFS_QMOPT_PQUOTA;
		flags |= (XFS_PQUOTA_CHKD | XFS_PQUOTA_ENFD);
		inactivate_flags |= XFS_PQUOTA_ACTIVE;
	पूर्ण

	/*
	 * Nothing to करो?  Don't complain. This happens when we're just
	 * turning off quota enक्रमcement.
	 */
	अगर ((mp->m_qflags & flags) == 0)
		जाओ out_unlock;

	/*
	 * Write the LI_QUOTAOFF log record, and करो SB changes atomically,
	 * and synchronously. If we fail to ग_लिखो, we should पात the
	 * operation as it cannot be recovered safely अगर we crash.
	 */
	error = xfs_qm_log_quotaoff(mp, &qoffstart, flags);
	अगर (error)
		जाओ out_unlock;

	/*
	 * Next we clear the XFS_MOUNT_*DQ_ACTIVE bit(s) in the mount काष्ठा
	 * to take care of the race between dqget and quotaoff. We करोn't take
	 * any special locks to reset these bits. All processes need to check
	 * these bits *after* taking inode lock(s) to see अगर the particular
	 * quota type is in the process of being turned off. If *ACTIVE, it is
	 * guaranteed that all dquot काष्ठाures and all quotainode ptrs will all
	 * stay valid as दीर्घ as that inode is kept locked.
	 *
	 * There is no turning back after this.
	 */
	mp->m_qflags &= ~inactivate_flags;

	/*
	 * Give back all the dquot reference(s) held by inodes.
	 * Here we go thru every single incore inode in this file प्रणाली, and
	 * करो a dqrele on the i_udquot/i_gdquot that it may have.
	 * Essentially, as दीर्घ as somebody has an inode locked, this guarantees
	 * that quotas will not be turned off. This is handy because in a
	 * transaction once we lock the inode(s) and check क्रम quotaon, we can
	 * depend on the quota inodes (and other things) being valid as दीर्घ as
	 * we keep the lock(s).
	 */
	xfs_qm_dqrele_all_inodes(mp, flags);

	/*
	 * Next we make the changes in the quota flag in the mount काष्ठा.
	 * This isn't रक्षित by a particular lock directly, because we
	 * करोn't want to take a mrlock every समय we depend on quotas being on.
	 */
	mp->m_qflags &= ~flags;

	/*
	 * Go through all the dquots of this file प्रणाली and purge them,
	 * according to what was turned off.
	 */
	xfs_qm_dqpurge_all(mp, dqtype);

	/*
	 * Transactions that had started beक्रमe ACTIVE state bit was cleared
	 * could have logged many dquots, so they'd have higher LSNs than
	 * the first QUOTAOFF log record करोes. If we happen to crash when
	 * the tail of the log has gone past the QUOTAOFF record, but
	 * beक्रमe the last dquot modअगरication, those dquots __will__
	 * recover, and that's not good.
	 *
	 * So, we have QUOTAOFF start and end logitems; the start
	 * logitem won't get overwritten until the end logitem appears...
	 */
	error = xfs_qm_log_quotaoff_end(mp, &qoffstart, flags);
	अगर (error) अणु
		/* We're screwed now. Shutकरोwn is the only option. */
		xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
		जाओ out_unlock;
	पूर्ण

	/*
	 * If all quotas are completely turned off, बंद shop.
	 */
	अगर (mp->m_qflags == 0) अणु
		mutex_unlock(&q->qi_quotaofflock);
		xfs_qm_destroy_quotainfo(mp);
		वापस 0;
	पूर्ण

	/*
	 * Release our quotainode references अगर we करोn't need them anymore.
	 */
	अगर ((dqtype & XFS_QMOPT_UQUOTA) && q->qi_uquotaip) अणु
		xfs_irele(q->qi_uquotaip);
		q->qi_uquotaip = शून्य;
	पूर्ण
	अगर ((dqtype & XFS_QMOPT_GQUOTA) && q->qi_gquotaip) अणु
		xfs_irele(q->qi_gquotaip);
		q->qi_gquotaip = शून्य;
	पूर्ण
	अगर ((dqtype & XFS_QMOPT_PQUOTA) && q->qi_pquotaip) अणु
		xfs_irele(q->qi_pquotaip);
		q->qi_pquotaip = शून्य;
	पूर्ण

out_unlock:
	अगर (error && qoffstart)
		xfs_qm_qoff_logitem_rअन्यथा(qoffstart);
	mutex_unlock(&q->qi_quotaofflock);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_qm_scall_trunc_qfile(
	काष्ठा xfs_mount	*mp,
	xfs_ino_t		ino)
अणु
	काष्ठा xfs_inode	*ip;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;

	अगर (ino == शून्यFSINO)
		वापस 0;

	error = xfs_iget(mp, शून्य, ino, 0, 0, &ip);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_IOLOCK_EXCL);

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate, 0, 0, 0, &tp);
	अगर (error) अणु
		xfs_iunlock(ip, XFS_IOLOCK_EXCL);
		जाओ out_put;
	पूर्ण

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	ip->i_disk_size = 0;
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	error = xfs_itruncate_extents(&tp, ip, XFS_DATA_FORK, 0);
	अगर (error) अणु
		xfs_trans_cancel(tp);
		जाओ out_unlock;
	पूर्ण

	ASSERT(ip->i_df.अगर_nextents == 0);

	xfs_trans_ichgसमय(tp, ip, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	error = xfs_trans_commit(tp);

out_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL | XFS_IOLOCK_EXCL);
out_put:
	xfs_irele(ip);
	वापस error;
पूर्ण

पूर्णांक
xfs_qm_scall_trunc_qfiles(
	xfs_mount_t	*mp,
	uपूर्णांक		flags)
अणु
	पूर्णांक		error = -EINVAL;

	अगर (!xfs_sb_version_hasquota(&mp->m_sb) || flags == 0 ||
	    (flags & ~XFS_QMOPT_QUOTALL)) अणु
		xfs_debug(mp, "%s: flags=%x m_qflags=%x",
			__func__, flags, mp->m_qflags);
		वापस -EINVAL;
	पूर्ण

	अगर (flags & XFS_QMOPT_UQUOTA) अणु
		error = xfs_qm_scall_trunc_qfile(mp, mp->m_sb.sb_uquotino);
		अगर (error)
			वापस error;
	पूर्ण
	अगर (flags & XFS_QMOPT_GQUOTA) अणु
		error = xfs_qm_scall_trunc_qfile(mp, mp->m_sb.sb_gquotino);
		अगर (error)
			वापस error;
	पूर्ण
	अगर (flags & XFS_QMOPT_PQUOTA)
		error = xfs_qm_scall_trunc_qfile(mp, mp->m_sb.sb_pquotino);

	वापस error;
पूर्ण

/*
 * Switch on (a given) quota enक्रमcement क्रम a fileप्रणाली.  This takes
 * effect immediately.
 * (Switching on quota accounting must be करोne at mount समय.)
 */
पूर्णांक
xfs_qm_scall_quotaon(
	xfs_mount_t	*mp,
	uपूर्णांक		flags)
अणु
	पूर्णांक		error;
	uपूर्णांक		qf;

	/*
	 * Switching on quota accounting must be करोne at mount समय,
	 * only consider quota enक्रमcement stuff here.
	 */
	flags &= XFS_ALL_QUOTA_ENFD;

	अगर (flags == 0) अणु
		xfs_debug(mp, "%s: zero flags, m_qflags=%x",
			__func__, mp->m_qflags);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Can't enक्रमce without accounting. We check the superblock
	 * qflags here instead of m_qflags because rootfs can have
	 * quota acct on ondisk without m_qflags' knowing.
	 */
	अगर (((mp->m_sb.sb_qflags & XFS_UQUOTA_ACCT) == 0 &&
	     (flags & XFS_UQUOTA_ENFD)) ||
	    ((mp->m_sb.sb_qflags & XFS_GQUOTA_ACCT) == 0 &&
	     (flags & XFS_GQUOTA_ENFD)) ||
	    ((mp->m_sb.sb_qflags & XFS_PQUOTA_ACCT) == 0 &&
	     (flags & XFS_PQUOTA_ENFD))) अणु
		xfs_debug(mp,
			"%s: Can't enforce without acct, flags=%x sbflags=%x",
			__func__, flags, mp->m_sb.sb_qflags);
		वापस -EINVAL;
	पूर्ण
	/*
	 * If everything's up to-date incore, then don't waste समय.
	 */
	अगर ((mp->m_qflags & flags) == flags)
		वापस -EEXIST;

	/*
	 * Change sb_qflags on disk but not incore mp->qflags
	 * अगर this is the root fileप्रणाली.
	 */
	spin_lock(&mp->m_sb_lock);
	qf = mp->m_sb.sb_qflags;
	mp->m_sb.sb_qflags = qf | flags;
	spin_unlock(&mp->m_sb_lock);

	/*
	 * There's nothing to change if it's the same.
	 */
	अगर ((qf & flags) == flags)
		वापस -EEXIST;

	error = xfs_sync_sb(mp, false);
	अगर (error)
		वापस error;
	/*
	 * If we aren't trying to चयन on quota enक्रमcement, we are करोne.
	 */
	अगर  (((mp->m_sb.sb_qflags & XFS_UQUOTA_ACCT) !=
	     (mp->m_qflags & XFS_UQUOTA_ACCT)) ||
	     ((mp->m_sb.sb_qflags & XFS_PQUOTA_ACCT) !=
	     (mp->m_qflags & XFS_PQUOTA_ACCT)) ||
	     ((mp->m_sb.sb_qflags & XFS_GQUOTA_ACCT) !=
	     (mp->m_qflags & XFS_GQUOTA_ACCT)))
		वापस 0;

	अगर (! XFS_IS_QUOTA_RUNNING(mp))
		वापस -ESRCH;

	/*
	 * Switch on quota enक्रमcement in core.
	 */
	mutex_lock(&mp->m_quotainfo->qi_quotaofflock);
	mp->m_qflags |= (flags & XFS_ALL_QUOTA_ENFD);
	mutex_unlock(&mp->m_quotainfo->qi_quotaofflock);

	वापस 0;
पूर्ण

#घोषणा XFS_QC_MASK \
	(QC_LIMIT_MASK | QC_TIMER_MASK | QC_WARNS_MASK)

/*
 * Adjust limits of this quota, and the शेषs अगर passed in.  Returns true
 * अगर the new limits made sense and were applied, false otherwise.
 */
अटल अंतरभूत bool
xfs_setqlim_limits(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dquot_res	*res,
	काष्ठा xfs_quota_limits	*qlim,
	xfs_qcnt_t		hard,
	xfs_qcnt_t		soft,
	स्थिर अक्षर		*tag)
अणु
	/* The hard limit can't be less than the soft limit. */
	अगर (hard != 0 && hard < soft) अणु
		xfs_debug(mp, "%shard %lld < %ssoft %lld", tag, hard, tag,
				soft);
		वापस false;
	पूर्ण

	res->hardlimit = hard;
	res->softlimit = soft;
	अगर (qlim) अणु
		qlim->hard = hard;
		qlim->soft = soft;
	पूर्ण

	वापस true;
पूर्ण

अटल अंतरभूत व्योम
xfs_setqlim_warns(
	काष्ठा xfs_dquot_res	*res,
	काष्ठा xfs_quota_limits	*qlim,
	पूर्णांक			warns)
अणु
	res->warnings = warns;
	अगर (qlim)
		qlim->warn = warns;
पूर्ण

अटल अंतरभूत व्योम
xfs_setqlim_समयr(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dquot_res	*res,
	काष्ठा xfs_quota_limits	*qlim,
	s64			समयr)
अणु
	अगर (qlim) अणु
		/* Set the length of the शेष grace period. */
		res->समयr = xfs_dquot_set_grace_period(समयr);
		qlim->समय = res->समयr;
	पूर्ण अन्यथा अणु
		/* Set the grace period expiration on a quota. */
		res->समयr = xfs_dquot_set_समयout(mp, समयr);
	पूर्ण
पूर्ण

/*
 * Adjust quota limits, and start/stop समयrs accordingly.
 */
पूर्णांक
xfs_qm_scall_setqlim(
	काष्ठा xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	काष्ठा qc_dqblk		*newlim)
अणु
	काष्ठा xfs_quotainfo	*q = mp->m_quotainfo;
	काष्ठा xfs_dquot	*dqp;
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_def_quota	*defq;
	काष्ठा xfs_dquot_res	*res;
	काष्ठा xfs_quota_limits	*qlim;
	पूर्णांक			error;
	xfs_qcnt_t		hard, soft;

	अगर (newlim->d_fieldmask & ~XFS_QC_MASK)
		वापस -EINVAL;
	अगर ((newlim->d_fieldmask & XFS_QC_MASK) == 0)
		वापस 0;

	/*
	 * We करोn't want to race with a quotaoff so take the quotaoff lock.
	 * We करोn't hold an inode lock, so there's nothing अन्यथा to stop
	 * a quotaoff from happening.
	 */
	mutex_lock(&q->qi_quotaofflock);

	/*
	 * Get the dquot (locked) beक्रमe we start, as we need to करो a
	 * transaction to allocate it अगर it करोesn't exist. Once we have the
	 * dquot, unlock it so we can start the next transaction safely. We hold
	 * a reference to the dquot, so it's safe to करो this unlock/lock without
	 * it being reclaimed in the mean समय.
	 */
	error = xfs_qm_dqget(mp, id, type, true, &dqp);
	अगर (error) अणु
		ASSERT(error != -ENOENT);
		जाओ out_unlock;
	पूर्ण

	defq = xfs_get_defquota(q, xfs_dquot_type(dqp));
	xfs_dqunlock(dqp);

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_qm_setqlim, 0, 0, 0, &tp);
	अगर (error)
		जाओ out_rele;

	xfs_dqlock(dqp);
	xfs_trans_dqjoin(tp, dqp);

	/*
	 * Update quota limits, warnings, and समयrs, and the शेषs
	 * अगर we're touching id == 0.
	 *
	 * Make sure that hardlimits are >= soft limits beक्रमe changing.
	 *
	 * Update warnings counter(s) अगर requested.
	 *
	 * Timelimits क्रम the super user set the relative समय the other users
	 * can be over quota क्रम this file प्रणाली. If it is zero a शेष is
	 * used.  Ditto क्रम the शेष soft and hard limit values (alपढ़ोy
	 * करोne, above), and क्रम warnings.
	 *
	 * For other IDs, userspace can bump out the grace period अगर over
	 * the soft limit.
	 */

	/* Blocks on the data device. */
	hard = (newlim->d_fieldmask & QC_SPC_HARD) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newlim->d_spc_hardlimit) :
			dqp->q_blk.hardlimit;
	soft = (newlim->d_fieldmask & QC_SPC_SOFT) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newlim->d_spc_softlimit) :
			dqp->q_blk.softlimit;
	res = &dqp->q_blk;
	qlim = id == 0 ? &defq->blk : शून्य;

	अगर (xfs_setqlim_limits(mp, res, qlim, hard, soft, "blk"))
		xfs_dquot_set_pपुनः_स्मृति_limits(dqp);
	अगर (newlim->d_fieldmask & QC_SPC_WARNS)
		xfs_setqlim_warns(res, qlim, newlim->d_spc_warns);
	अगर (newlim->d_fieldmask & QC_SPC_TIMER)
		xfs_setqlim_समयr(mp, res, qlim, newlim->d_spc_समयr);

	/* Blocks on the realसमय device. */
	hard = (newlim->d_fieldmask & QC_RT_SPC_HARD) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newlim->d_rt_spc_hardlimit) :
			dqp->q_rtb.hardlimit;
	soft = (newlim->d_fieldmask & QC_RT_SPC_SOFT) ?
		(xfs_qcnt_t) XFS_B_TO_FSB(mp, newlim->d_rt_spc_softlimit) :
			dqp->q_rtb.softlimit;
	res = &dqp->q_rtb;
	qlim = id == 0 ? &defq->rtb : शून्य;

	xfs_setqlim_limits(mp, res, qlim, hard, soft, "rtb");
	अगर (newlim->d_fieldmask & QC_RT_SPC_WARNS)
		xfs_setqlim_warns(res, qlim, newlim->d_rt_spc_warns);
	अगर (newlim->d_fieldmask & QC_RT_SPC_TIMER)
		xfs_setqlim_समयr(mp, res, qlim, newlim->d_rt_spc_समयr);

	/* Inodes */
	hard = (newlim->d_fieldmask & QC_INO_HARD) ?
		(xfs_qcnt_t) newlim->d_ino_hardlimit :
			dqp->q_ino.hardlimit;
	soft = (newlim->d_fieldmask & QC_INO_SOFT) ?
		(xfs_qcnt_t) newlim->d_ino_softlimit :
			dqp->q_ino.softlimit;
	res = &dqp->q_ino;
	qlim = id == 0 ? &defq->ino : शून्य;

	xfs_setqlim_limits(mp, res, qlim, hard, soft, "ino");
	अगर (newlim->d_fieldmask & QC_INO_WARNS)
		xfs_setqlim_warns(res, qlim, newlim->d_ino_warns);
	अगर (newlim->d_fieldmask & QC_INO_TIMER)
		xfs_setqlim_समयr(mp, res, qlim, newlim->d_ino_समयr);

	अगर (id != 0) अणु
		/*
		 * If the user is now over quota, start the समयlimit.
		 * The user will not be 'warned'.
		 * Note that we keep the समयrs ticking, whether enक्रमcement
		 * is on or off. We करोn't really want to bother with iterating
		 * over all ondisk dquots and turning the समयrs on/off.
		 */
		xfs_qm_adjust_dqसमयrs(dqp);
	पूर्ण
	dqp->q_flags |= XFS_DQFLAG_सूचीTY;
	xfs_trans_log_dquot(tp, dqp);

	error = xfs_trans_commit(tp);

out_rele:
	xfs_qm_dqrele(dqp);
out_unlock:
	mutex_unlock(&q->qi_quotaofflock);
	वापस error;
पूर्ण

/* Fill out the quota context. */
अटल व्योम
xfs_qm_scall_getquota_fill_qc(
	काष्ठा xfs_mount	*mp,
	xfs_dqtype_t		type,
	स्थिर काष्ठा xfs_dquot	*dqp,
	काष्ठा qc_dqblk		*dst)
अणु
	स_रखो(dst, 0, माप(*dst));
	dst->d_spc_hardlimit = XFS_FSB_TO_B(mp, dqp->q_blk.hardlimit);
	dst->d_spc_softlimit = XFS_FSB_TO_B(mp, dqp->q_blk.softlimit);
	dst->d_ino_hardlimit = dqp->q_ino.hardlimit;
	dst->d_ino_softlimit = dqp->q_ino.softlimit;
	dst->d_space = XFS_FSB_TO_B(mp, dqp->q_blk.reserved);
	dst->d_ino_count = dqp->q_ino.reserved;
	dst->d_spc_समयr = dqp->q_blk.समयr;
	dst->d_ino_समयr = dqp->q_ino.समयr;
	dst->d_ino_warns = dqp->q_ino.warnings;
	dst->d_spc_warns = dqp->q_blk.warnings;
	dst->d_rt_spc_hardlimit = XFS_FSB_TO_B(mp, dqp->q_rtb.hardlimit);
	dst->d_rt_spc_softlimit = XFS_FSB_TO_B(mp, dqp->q_rtb.softlimit);
	dst->d_rt_space = XFS_FSB_TO_B(mp, dqp->q_rtb.reserved);
	dst->d_rt_spc_समयr = dqp->q_rtb.समयr;
	dst->d_rt_spc_warns = dqp->q_rtb.warnings;

	/*
	 * Internally, we करोn't reset all the समयrs when quota enक्रमcement
	 * माला_लो turned off. No need to confuse the user level code,
	 * so वापस zeroes in that हाल.
	 */
	अगर (!xfs_dquot_is_enक्रमced(dqp)) अणु
		dst->d_spc_समयr = 0;
		dst->d_ino_समयr = 0;
		dst->d_rt_spc_समयr = 0;
	पूर्ण

#अगर_घोषित DEBUG
	अगर (xfs_dquot_is_enक्रमced(dqp) && dqp->q_id != 0) अणु
		अगर ((dst->d_space > dst->d_spc_softlimit) &&
		    (dst->d_spc_softlimit > 0)) अणु
			ASSERT(dst->d_spc_समयr != 0);
		पूर्ण
		अगर ((dst->d_ino_count > dqp->q_ino.softlimit) &&
		    (dqp->q_ino.softlimit > 0)) अणु
			ASSERT(dst->d_ino_समयr != 0);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* Return the quota inक्रमmation क्रम the dquot matching id. */
पूर्णांक
xfs_qm_scall_getquota(
	काष्ठा xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	काष्ठा qc_dqblk		*dst)
अणु
	काष्ठा xfs_dquot	*dqp;
	पूर्णांक			error;

	/*
	 * Try to get the dquot. We करोn't want it allocated on disk, so don't
	 * set करोalloc. If it करोesn't exist, we'll get ENOENT back.
	 */
	error = xfs_qm_dqget(mp, id, type, false, &dqp);
	अगर (error)
		वापस error;

	/*
	 * If everything's NULL, this dquot doesn't quite exist as far as
	 * our utility programs are concerned.
	 */
	अगर (XFS_IS_DQUOT_UNINITIALIZED(dqp)) अणु
		error = -ENOENT;
		जाओ out_put;
	पूर्ण

	xfs_qm_scall_getquota_fill_qc(mp, type, dqp, dst);

out_put:
	xfs_qm_dqput(dqp);
	वापस error;
पूर्ण

/*
 * Return the quota inक्रमmation क्रम the first initialized dquot whose id
 * is at least as high as id.
 */
पूर्णांक
xfs_qm_scall_getquota_next(
	काष्ठा xfs_mount	*mp,
	xfs_dqid_t		*id,
	xfs_dqtype_t		type,
	काष्ठा qc_dqblk		*dst)
अणु
	काष्ठा xfs_dquot	*dqp;
	पूर्णांक			error;

	error = xfs_qm_dqget_next(mp, *id, type, &dqp);
	अगर (error)
		वापस error;

	/* Fill in the ID we actually पढ़ो from disk */
	*id = dqp->q_id;

	xfs_qm_scall_getquota_fill_qc(mp, type, dqp, dst);

	xfs_qm_dqput(dqp);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_dqrele_inode(
	काष्ठा xfs_inode	*ip,
	व्योम			*args)
अणु
	uपूर्णांक			*flags = args;

	/* skip quota inodes */
	अगर (ip == ip->i_mount->m_quotainfo->qi_uquotaip ||
	    ip == ip->i_mount->m_quotainfo->qi_gquotaip ||
	    ip == ip->i_mount->m_quotainfo->qi_pquotaip) अणु
		ASSERT(ip->i_udquot == शून्य);
		ASSERT(ip->i_gdquot == शून्य);
		ASSERT(ip->i_pdquot == शून्य);
		वापस 0;
	पूर्ण

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	अगर ((*flags & XFS_UQUOTA_ACCT) && ip->i_udquot) अणु
		xfs_qm_dqrele(ip->i_udquot);
		ip->i_udquot = शून्य;
	पूर्ण
	अगर ((*flags & XFS_GQUOTA_ACCT) && ip->i_gdquot) अणु
		xfs_qm_dqrele(ip->i_gdquot);
		ip->i_gdquot = शून्य;
	पूर्ण
	अगर ((*flags & XFS_PQUOTA_ACCT) && ip->i_pdquot) अणु
		xfs_qm_dqrele(ip->i_pdquot);
		ip->i_pdquot = शून्य;
	पूर्ण
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस 0;
पूर्ण


/*
 * Go thru all the inodes in the file प्रणाली, releasing their dquots.
 *
 * Note that the mount काष्ठाure माला_लो modअगरied to indicate that quotas are off
 * AFTER this, in the हाल of quotaoff.
 */
व्योम
xfs_qm_dqrele_all_inodes(
	काष्ठा xfs_mount	*mp,
	uपूर्णांक			flags)
अणु
	ASSERT(mp->m_quotainfo);
	xfs_inode_walk(mp, XFS_INODE_WALK_INEW_WAIT, xfs_dqrele_inode,
			&flags, XFS_ICI_NO_TAG);
पूर्ण
