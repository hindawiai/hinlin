<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2008, Christoph Hellwig
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_qm.h"


अटल व्योम
xfs_qm_fill_state(
	काष्ठा qc_type_state	*tstate,
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_inode	*ip,
	xfs_ino_t		ino,
	काष्ठा xfs_def_quota	*defq)
अणु
	bool			tempqip = false;

	tstate->ino = ino;
	अगर (!ip && ino == शून्यFSINO)
		वापस;
	अगर (!ip) अणु
		अगर (xfs_iget(mp, शून्य, ino, 0, 0, &ip))
			वापस;
		tempqip = true;
	पूर्ण
	tstate->flags |= QCI_SYSखाता;
	tstate->blocks = ip->i_nblocks;
	tstate->nextents = ip->i_df.अगर_nextents;
	tstate->spc_समयlimit = (u32)defq->blk.समय;
	tstate->ino_समयlimit = (u32)defq->ino.समय;
	tstate->rt_spc_समयlimit = (u32)defq->rtb.समय;
	tstate->spc_warnlimit = defq->blk.warn;
	tstate->ino_warnlimit = defq->ino.warn;
	tstate->rt_spc_warnlimit = defq->rtb.warn;
	अगर (tempqip)
		xfs_irele(ip);
पूर्ण

/*
 * Return quota status inक्रमmation, such as enक्रमcements, quota file inode
 * numbers etc.
 */
अटल पूर्णांक
xfs_fs_get_quota_state(
	काष्ठा super_block	*sb,
	काष्ठा qc_state		*state)
अणु
	काष्ठा xfs_mount *mp = XFS_M(sb);
	काष्ठा xfs_quotainfo *q = mp->m_quotainfo;

	स_रखो(state, 0, माप(*state));
	अगर (!XFS_IS_QUOTA_RUNNING(mp))
		वापस 0;
	state->s_incoredqs = q->qi_dquots;
	अगर (XFS_IS_UQUOTA_RUNNING(mp))
		state->s_state[USRQUOTA].flags |= QCI_ACCT_ENABLED;
	अगर (XFS_IS_UQUOTA_ENFORCED(mp))
		state->s_state[USRQUOTA].flags |= QCI_LIMITS_ENFORCED;
	अगर (XFS_IS_GQUOTA_RUNNING(mp))
		state->s_state[GRPQUOTA].flags |= QCI_ACCT_ENABLED;
	अगर (XFS_IS_GQUOTA_ENFORCED(mp))
		state->s_state[GRPQUOTA].flags |= QCI_LIMITS_ENFORCED;
	अगर (XFS_IS_PQUOTA_RUNNING(mp))
		state->s_state[PRJQUOTA].flags |= QCI_ACCT_ENABLED;
	अगर (XFS_IS_PQUOTA_ENFORCED(mp))
		state->s_state[PRJQUOTA].flags |= QCI_LIMITS_ENFORCED;

	xfs_qm_fill_state(&state->s_state[USRQUOTA], mp, q->qi_uquotaip,
			  mp->m_sb.sb_uquotino, &q->qi_usr_शेष);
	xfs_qm_fill_state(&state->s_state[GRPQUOTA], mp, q->qi_gquotaip,
			  mp->m_sb.sb_gquotino, &q->qi_grp_शेष);
	xfs_qm_fill_state(&state->s_state[PRJQUOTA], mp, q->qi_pquotaip,
			  mp->m_sb.sb_pquotino, &q->qi_prj_शेष);
	वापस 0;
पूर्ण

STATIC xfs_dqtype_t
xfs_quota_type(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल USRQUOTA:
		वापस XFS_DQTYPE_USER;
	हाल GRPQUOTA:
		वापस XFS_DQTYPE_GROUP;
	शेष:
		वापस XFS_DQTYPE_PROJ;
	पूर्ण
पूर्ण

#घोषणा XFS_QC_SETINFO_MASK (QC_TIMER_MASK | QC_WARNS_MASK)

/*
 * Adjust quota समयrs & warnings
 */
अटल पूर्णांक
xfs_fs_set_info(
	काष्ठा super_block	*sb,
	पूर्णांक			type,
	काष्ठा qc_info		*info)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);
	काष्ठा qc_dqblk		newlim;

	अगर (sb_rकरोnly(sb))
		वापस -EROFS;
	अगर (!XFS_IS_QUOTA_RUNNING(mp))
		वापस -ENOSYS;
	अगर (!XFS_IS_QUOTA_ON(mp))
		वापस -ESRCH;
	अगर (info->i_fieldmask & ~XFS_QC_SETINFO_MASK)
		वापस -EINVAL;
	अगर ((info->i_fieldmask & XFS_QC_SETINFO_MASK) == 0)
		वापस 0;

	newlim.d_fieldmask = info->i_fieldmask;
	newlim.d_spc_समयr = info->i_spc_समयlimit;
	newlim.d_ino_समयr = info->i_ino_समयlimit;
	newlim.d_rt_spc_समयr = info->i_rt_spc_समयlimit;
	newlim.d_ino_warns = info->i_ino_warnlimit;
	newlim.d_spc_warns = info->i_spc_warnlimit;
	newlim.d_rt_spc_warns = info->i_rt_spc_warnlimit;

	वापस xfs_qm_scall_setqlim(mp, 0, xfs_quota_type(type), &newlim);
पूर्ण

अटल अचिन्हित पूर्णांक
xfs_quota_flags(अचिन्हित पूर्णांक uflags)
अणु
	अचिन्हित पूर्णांक flags = 0;

	अगर (uflags & FS_QUOTA_UDQ_ACCT)
		flags |= XFS_UQUOTA_ACCT;
	अगर (uflags & FS_QUOTA_PDQ_ACCT)
		flags |= XFS_PQUOTA_ACCT;
	अगर (uflags & FS_QUOTA_GDQ_ACCT)
		flags |= XFS_GQUOTA_ACCT;
	अगर (uflags & FS_QUOTA_UDQ_ENFD)
		flags |= XFS_UQUOTA_ENFD;
	अगर (uflags & FS_QUOTA_GDQ_ENFD)
		flags |= XFS_GQUOTA_ENFD;
	अगर (uflags & FS_QUOTA_PDQ_ENFD)
		flags |= XFS_PQUOTA_ENFD;

	वापस flags;
पूर्ण

STATIC पूर्णांक
xfs_quota_enable(
	काष्ठा super_block	*sb,
	अचिन्हित पूर्णांक		uflags)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);

	अगर (sb_rकरोnly(sb))
		वापस -EROFS;
	अगर (!XFS_IS_QUOTA_RUNNING(mp))
		वापस -ENOSYS;

	वापस xfs_qm_scall_quotaon(mp, xfs_quota_flags(uflags));
पूर्ण

STATIC पूर्णांक
xfs_quota_disable(
	काष्ठा super_block	*sb,
	अचिन्हित पूर्णांक		uflags)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);

	अगर (sb_rकरोnly(sb))
		वापस -EROFS;
	अगर (!XFS_IS_QUOTA_RUNNING(mp))
		वापस -ENOSYS;
	अगर (!XFS_IS_QUOTA_ON(mp))
		वापस -EINVAL;

	वापस xfs_qm_scall_quotaoff(mp, xfs_quota_flags(uflags));
पूर्ण

STATIC पूर्णांक
xfs_fs_rm_xquota(
	काष्ठा super_block	*sb,
	अचिन्हित पूर्णांक		uflags)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);
	अचिन्हित पूर्णांक		flags = 0;

	अगर (sb_rकरोnly(sb))
		वापस -EROFS;

	अगर (XFS_IS_QUOTA_ON(mp))
		वापस -EINVAL;

	अगर (uflags & ~(FS_USER_QUOTA | FS_GROUP_QUOTA | FS_PROJ_QUOTA))
		वापस -EINVAL;

	अगर (uflags & FS_USER_QUOTA)
		flags |= XFS_QMOPT_UQUOTA;
	अगर (uflags & FS_GROUP_QUOTA)
		flags |= XFS_QMOPT_GQUOTA;
	अगर (uflags & FS_PROJ_QUOTA)
		flags |= XFS_QMOPT_PQUOTA;

	वापस xfs_qm_scall_trunc_qfiles(mp, flags);
पूर्ण

STATIC पूर्णांक
xfs_fs_get_dqblk(
	काष्ठा super_block	*sb,
	काष्ठा kqid		qid,
	काष्ठा qc_dqblk		*qdq)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);
	xfs_dqid_t		id;

	अगर (!XFS_IS_QUOTA_RUNNING(mp))
		वापस -ENOSYS;
	अगर (!XFS_IS_QUOTA_ON(mp))
		वापस -ESRCH;

	id = from_kqid(&init_user_ns, qid);
	वापस xfs_qm_scall_getquota(mp, id, xfs_quota_type(qid.type), qdq);
पूर्ण

/* Return quota info क्रम active quota >= this qid */
STATIC पूर्णांक
xfs_fs_get_nextdqblk(
	काष्ठा super_block	*sb,
	काष्ठा kqid		*qid,
	काष्ठा qc_dqblk		*qdq)
अणु
	पूर्णांक			ret;
	काष्ठा xfs_mount	*mp = XFS_M(sb);
	xfs_dqid_t		id;

	अगर (!XFS_IS_QUOTA_RUNNING(mp))
		वापस -ENOSYS;
	अगर (!XFS_IS_QUOTA_ON(mp))
		वापस -ESRCH;

	id = from_kqid(&init_user_ns, *qid);
	ret = xfs_qm_scall_getquota_next(mp, &id, xfs_quota_type(qid->type),
			qdq);
	अगर (ret)
		वापस ret;

	/* ID may be dअगरferent, so convert back what we got */
	*qid = make_kqid(current_user_ns(), qid->type, id);
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_fs_set_dqblk(
	काष्ठा super_block	*sb,
	काष्ठा kqid		qid,
	काष्ठा qc_dqblk		*qdq)
अणु
	काष्ठा xfs_mount	*mp = XFS_M(sb);

	अगर (sb_rकरोnly(sb))
		वापस -EROFS;
	अगर (!XFS_IS_QUOTA_RUNNING(mp))
		वापस -ENOSYS;
	अगर (!XFS_IS_QUOTA_ON(mp))
		वापस -ESRCH;

	वापस xfs_qm_scall_setqlim(mp, from_kqid(&init_user_ns, qid),
				     xfs_quota_type(qid.type), qdq);
पूर्ण

स्थिर काष्ठा quotactl_ops xfs_quotactl_operations = अणु
	.get_state		= xfs_fs_get_quota_state,
	.set_info		= xfs_fs_set_info,
	.quota_enable		= xfs_quota_enable,
	.quota_disable		= xfs_quota_disable,
	.rm_xquota		= xfs_fs_rm_xquota,
	.get_dqblk		= xfs_fs_get_dqblk,
	.get_nextdqblk		= xfs_fs_get_nextdqblk,
	.set_dqblk		= xfs_fs_set_dqblk,
पूर्ण;
