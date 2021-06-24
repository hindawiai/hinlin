<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Quota code necessary even when VFS quota support is not compiled
 * पूर्णांकo the kernel.  The पूर्णांकeresting stuff is over in dquot.c, here
 * we have symbols क्रम initial quotactl(2) handling, the sysctl(2)
 * variables, etc - things needed even when quota support disabled.
 */

#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/current.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/capability.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/types.h>
#समावेश <linux/mount.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/nospec.h>
#समावेश "compat.h"
#समावेश "../internal.h"

अटल पूर्णांक check_quotactl_permission(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक cmd,
				     qid_t id)
अणु
	चयन (cmd) अणु
	/* these commands करो not require any special privilegues */
	हाल Q_GETFMT:
	हाल Q_SYNC:
	हाल Q_GETINFO:
	हाल Q_XGETQSTAT:
	हाल Q_XGETQSTATV:
	हाल Q_XQUOTASYNC:
		अवरोध;
	/* allow to query inक्रमmation क्रम dquots we "own" */
	हाल Q_GETQUOTA:
	हाल Q_XGETQUOTA:
		अगर ((type == USRQUOTA && uid_eq(current_euid(), make_kuid(current_user_ns(), id))) ||
		    (type == GRPQUOTA && in_egroup_p(make_kgid(current_user_ns(), id))))
			अवरोध;
		fallthrough;
	शेष:
		अगर (!capable(CAP_SYS_ADMIN))
			वापस -EPERM;
	पूर्ण

	वापस security_quotactl(cmd, type, id, sb);
पूर्ण

अटल व्योम quota_sync_one(काष्ठा super_block *sb, व्योम *arg)
अणु
	पूर्णांक type = *(पूर्णांक *)arg;

	अगर (sb->s_qcop && sb->s_qcop->quota_sync &&
	    (sb->s_quota_types & (1 << type)))
		sb->s_qcop->quota_sync(sb, type);
पूर्ण

अटल पूर्णांक quota_sync_all(पूर्णांक type)
अणु
	पूर्णांक ret;

	ret = security_quotactl(Q_SYNC, type, 0, शून्य);
	अगर (!ret)
		iterate_supers(quota_sync_one, &type);
	वापस ret;
पूर्ण

अचिन्हित पूर्णांक qtype_enक्रमce_flag(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल USRQUOTA:
		वापस FS_QUOTA_UDQ_ENFD;
	हाल GRPQUOTA:
		वापस FS_QUOTA_GDQ_ENFD;
	हाल PRJQUOTA:
		वापस FS_QUOTA_PDQ_ENFD;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक quota_quotaon(काष्ठा super_block *sb, पूर्णांक type, qid_t id,
		         स्थिर काष्ठा path *path)
अणु
	अगर (!sb->s_qcop->quota_on && !sb->s_qcop->quota_enable)
		वापस -ENOSYS;
	अगर (sb->s_qcop->quota_enable)
		वापस sb->s_qcop->quota_enable(sb, qtype_enक्रमce_flag(type));
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);
	वापस sb->s_qcop->quota_on(sb, type, id, path);
पूर्ण

अटल पूर्णांक quota_quotaoff(काष्ठा super_block *sb, पूर्णांक type)
अणु
	अगर (!sb->s_qcop->quota_off && !sb->s_qcop->quota_disable)
		वापस -ENOSYS;
	अगर (sb->s_qcop->quota_disable)
		वापस sb->s_qcop->quota_disable(sb, qtype_enक्रमce_flag(type));
	वापस sb->s_qcop->quota_off(sb, type);
पूर्ण

अटल पूर्णांक quota_getfmt(काष्ठा super_block *sb, पूर्णांक type, व्योम __user *addr)
अणु
	__u32 fmt;

	अगर (!sb_has_quota_active(sb, type))
		वापस -ESRCH;
	fmt = sb_dqopt(sb)->info[type].dqi_क्रमmat->qf_fmt_id;
	अगर (copy_to_user(addr, &fmt, माप(fmt)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक quota_getinfo(काष्ठा super_block *sb, पूर्णांक type, व्योम __user *addr)
अणु
	काष्ठा qc_state state;
	काष्ठा qc_type_state *tstate;
	काष्ठा अगर_dqinfo uinfo;
	पूर्णांक ret;

	अगर (!sb->s_qcop->get_state)
		वापस -ENOSYS;
	ret = sb->s_qcop->get_state(sb, &state);
	अगर (ret)
		वापस ret;
	tstate = state.s_state + type;
	अगर (!(tstate->flags & QCI_ACCT_ENABLED))
		वापस -ESRCH;
	स_रखो(&uinfo, 0, माप(uinfo));
	uinfo.dqi_bgrace = tstate->spc_समयlimit;
	uinfo.dqi_igrace = tstate->ino_समयlimit;
	अगर (tstate->flags & QCI_SYSखाता)
		uinfo.dqi_flags |= DQF_SYS_खाता;
	अगर (tstate->flags & QCI_ROOT_SQUASH)
		uinfo.dqi_flags |= DQF_ROOT_SQUASH;
	uinfo.dqi_valid = IIF_ALL;
	अगर (copy_to_user(addr, &uinfo, माप(uinfo)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक quota_setinfo(काष्ठा super_block *sb, पूर्णांक type, व्योम __user *addr)
अणु
	काष्ठा अगर_dqinfo info;
	काष्ठा qc_info qinfo;

	अगर (copy_from_user(&info, addr, माप(info)))
		वापस -EFAULT;
	अगर (!sb->s_qcop->set_info)
		वापस -ENOSYS;
	अगर (info.dqi_valid & ~(IIF_FLAGS | IIF_BGRACE | IIF_IGRACE))
		वापस -EINVAL;
	स_रखो(&qinfo, 0, माप(qinfo));
	अगर (info.dqi_valid & IIF_FLAGS) अणु
		अगर (info.dqi_flags & ~DQF_SETINFO_MASK)
			वापस -EINVAL;
		अगर (info.dqi_flags & DQF_ROOT_SQUASH)
			qinfo.i_flags |= QCI_ROOT_SQUASH;
		qinfo.i_fieldmask |= QC_FLAGS;
	पूर्ण
	अगर (info.dqi_valid & IIF_BGRACE) अणु
		qinfo.i_spc_समयlimit = info.dqi_bgrace;
		qinfo.i_fieldmask |= QC_SPC_TIMER;
	पूर्ण
	अगर (info.dqi_valid & IIF_IGRACE) अणु
		qinfo.i_ino_समयlimit = info.dqi_igrace;
		qinfo.i_fieldmask |= QC_INO_TIMER;
	पूर्ण
	वापस sb->s_qcop->set_info(sb, type, &qinfo);
पूर्ण

अटल अंतरभूत qमाप_प्रकार qbtos(qमाप_प्रकार blocks)
अणु
	वापस blocks << QIF_DQBLKSIZE_BITS;
पूर्ण

अटल अंतरभूत qमाप_प्रकार stoqb(qमाप_प्रकार space)
अणु
	वापस (space + QIF_DQBLKSIZE - 1) >> QIF_DQBLKSIZE_BITS;
पूर्ण

अटल व्योम copy_to_अगर_dqblk(काष्ठा अगर_dqblk *dst, काष्ठा qc_dqblk *src)
अणु
	स_रखो(dst, 0, माप(*dst));
	dst->dqb_bhardlimit = stoqb(src->d_spc_hardlimit);
	dst->dqb_bsoftlimit = stoqb(src->d_spc_softlimit);
	dst->dqb_curspace = src->d_space;
	dst->dqb_ihardlimit = src->d_ino_hardlimit;
	dst->dqb_isoftlimit = src->d_ino_softlimit;
	dst->dqb_curinodes = src->d_ino_count;
	dst->dqb_bसमय = src->d_spc_समयr;
	dst->dqb_iसमय = src->d_ino_समयr;
	dst->dqb_valid = QIF_ALL;
पूर्ण

अटल पूर्णांक quota_getquota(काष्ठा super_block *sb, पूर्णांक type, qid_t id,
			  व्योम __user *addr)
अणु
	काष्ठा kqid qid;
	काष्ठा qc_dqblk fdq;
	काष्ठा अगर_dqblk idq;
	पूर्णांक ret;

	अगर (!sb->s_qcop->get_dqblk)
		वापस -ENOSYS;
	qid = make_kqid(current_user_ns(), type, id);
	अगर (!qid_has_mapping(sb->s_user_ns, qid))
		वापस -EINVAL;
	ret = sb->s_qcop->get_dqblk(sb, qid, &fdq);
	अगर (ret)
		वापस ret;
	copy_to_अगर_dqblk(&idq, &fdq);

	अगर (compat_need_64bit_alignment_fixup()) अणु
		काष्ठा compat_अगर_dqblk __user *compat_dqblk = addr;

		अगर (copy_to_user(compat_dqblk, &idq, माप(*compat_dqblk)))
			वापस -EFAULT;
		अगर (put_user(idq.dqb_valid, &compat_dqblk->dqb_valid))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (copy_to_user(addr, &idq, माप(idq)))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return quota क्रम next active quota >= this id, अगर any exists,
 * otherwise वापस -ENOENT via ->get_nextdqblk
 */
अटल पूर्णांक quota_getnextquota(काष्ठा super_block *sb, पूर्णांक type, qid_t id,
			  व्योम __user *addr)
अणु
	काष्ठा kqid qid;
	काष्ठा qc_dqblk fdq;
	काष्ठा अगर_nextdqblk idq;
	पूर्णांक ret;

	अगर (!sb->s_qcop->get_nextdqblk)
		वापस -ENOSYS;
	qid = make_kqid(current_user_ns(), type, id);
	अगर (!qid_has_mapping(sb->s_user_ns, qid))
		वापस -EINVAL;
	ret = sb->s_qcop->get_nextdqblk(sb, &qid, &fdq);
	अगर (ret)
		वापस ret;
	/* काष्ठा अगर_nextdqblk is a superset of काष्ठा अगर_dqblk */
	copy_to_अगर_dqblk((काष्ठा अगर_dqblk *)&idq, &fdq);
	idq.dqb_id = from_kqid(current_user_ns(), qid);
	अगर (copy_to_user(addr, &idq, माप(idq)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम copy_from_अगर_dqblk(काष्ठा qc_dqblk *dst, काष्ठा अगर_dqblk *src)
अणु
	dst->d_spc_hardlimit = qbtos(src->dqb_bhardlimit);
	dst->d_spc_softlimit = qbtos(src->dqb_bsoftlimit);
	dst->d_space = src->dqb_curspace;
	dst->d_ino_hardlimit = src->dqb_ihardlimit;
	dst->d_ino_softlimit = src->dqb_isoftlimit;
	dst->d_ino_count = src->dqb_curinodes;
	dst->d_spc_समयr = src->dqb_bसमय;
	dst->d_ino_समयr = src->dqb_iसमय;

	dst->d_fieldmask = 0;
	अगर (src->dqb_valid & QIF_BLIMITS)
		dst->d_fieldmask |= QC_SPC_SOFT | QC_SPC_HARD;
	अगर (src->dqb_valid & QIF_SPACE)
		dst->d_fieldmask |= QC_SPACE;
	अगर (src->dqb_valid & QIF_ILIMITS)
		dst->d_fieldmask |= QC_INO_SOFT | QC_INO_HARD;
	अगर (src->dqb_valid & QIF_INODES)
		dst->d_fieldmask |= QC_INO_COUNT;
	अगर (src->dqb_valid & QIF_BTIME)
		dst->d_fieldmask |= QC_SPC_TIMER;
	अगर (src->dqb_valid & QIF_ITIME)
		dst->d_fieldmask |= QC_INO_TIMER;
पूर्ण

अटल पूर्णांक quota_setquota(काष्ठा super_block *sb, पूर्णांक type, qid_t id,
			  व्योम __user *addr)
अणु
	काष्ठा qc_dqblk fdq;
	काष्ठा अगर_dqblk idq;
	काष्ठा kqid qid;

	अगर (compat_need_64bit_alignment_fixup()) अणु
		काष्ठा compat_अगर_dqblk __user *compat_dqblk = addr;

		अगर (copy_from_user(&idq, compat_dqblk, माप(*compat_dqblk)) ||
		    get_user(idq.dqb_valid, &compat_dqblk->dqb_valid))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (copy_from_user(&idq, addr, माप(idq)))
			वापस -EFAULT;
	पूर्ण
	अगर (!sb->s_qcop->set_dqblk)
		वापस -ENOSYS;
	qid = make_kqid(current_user_ns(), type, id);
	अगर (!qid_has_mapping(sb->s_user_ns, qid))
		वापस -EINVAL;
	copy_from_अगर_dqblk(&fdq, &idq);
	वापस sb->s_qcop->set_dqblk(sb, qid, &fdq);
पूर्ण

अटल पूर्णांक quota_enable(काष्ठा super_block *sb, व्योम __user *addr)
अणु
	__u32 flags;

	अगर (copy_from_user(&flags, addr, माप(flags)))
		वापस -EFAULT;
	अगर (!sb->s_qcop->quota_enable)
		वापस -ENOSYS;
	वापस sb->s_qcop->quota_enable(sb, flags);
पूर्ण

अटल पूर्णांक quota_disable(काष्ठा super_block *sb, व्योम __user *addr)
अणु
	__u32 flags;

	अगर (copy_from_user(&flags, addr, माप(flags)))
		वापस -EFAULT;
	अगर (!sb->s_qcop->quota_disable)
		वापस -ENOSYS;
	वापस sb->s_qcop->quota_disable(sb, flags);
पूर्ण

अटल पूर्णांक quota_state_to_flags(काष्ठा qc_state *state)
अणु
	पूर्णांक flags = 0;

	अगर (state->s_state[USRQUOTA].flags & QCI_ACCT_ENABLED)
		flags |= FS_QUOTA_UDQ_ACCT;
	अगर (state->s_state[USRQUOTA].flags & QCI_LIMITS_ENFORCED)
		flags |= FS_QUOTA_UDQ_ENFD;
	अगर (state->s_state[GRPQUOTA].flags & QCI_ACCT_ENABLED)
		flags |= FS_QUOTA_GDQ_ACCT;
	अगर (state->s_state[GRPQUOTA].flags & QCI_LIMITS_ENFORCED)
		flags |= FS_QUOTA_GDQ_ENFD;
	अगर (state->s_state[PRJQUOTA].flags & QCI_ACCT_ENABLED)
		flags |= FS_QUOTA_PDQ_ACCT;
	अगर (state->s_state[PRJQUOTA].flags & QCI_LIMITS_ENFORCED)
		flags |= FS_QUOTA_PDQ_ENFD;
	वापस flags;
पूर्ण

अटल पूर्णांक quota_माला_लोtate(काष्ठा super_block *sb, पूर्णांक type,
			  काष्ठा fs_quota_stat *fqs)
अणु
	काष्ठा qc_state state;
	पूर्णांक ret;

	स_रखो(&state, 0, माप (काष्ठा qc_state));
	ret = sb->s_qcop->get_state(sb, &state);
	अगर (ret < 0)
		वापस ret;

	स_रखो(fqs, 0, माप(*fqs));
	fqs->qs_version = FS_QSTAT_VERSION;
	fqs->qs_flags = quota_state_to_flags(&state);
	/* No quota enabled? */
	अगर (!fqs->qs_flags)
		वापस -ENOSYS;
	fqs->qs_incoredqs = state.s_incoredqs;

	fqs->qs_bसमयlimit = state.s_state[type].spc_समयlimit;
	fqs->qs_iसमयlimit = state.s_state[type].ino_समयlimit;
	fqs->qs_rtbसमयlimit = state.s_state[type].rt_spc_समयlimit;
	fqs->qs_bwarnlimit = state.s_state[type].spc_warnlimit;
	fqs->qs_iwarnlimit = state.s_state[type].ino_warnlimit;

	/* Inodes may be allocated even अगर inactive; copy out अगर present */
	अगर (state.s_state[USRQUOTA].ino) अणु
		fqs->qs_uquota.qfs_ino = state.s_state[USRQUOTA].ino;
		fqs->qs_uquota.qfs_nblks = state.s_state[USRQUOTA].blocks;
		fqs->qs_uquota.qfs_nextents = state.s_state[USRQUOTA].nextents;
	पूर्ण
	अगर (state.s_state[GRPQUOTA].ino) अणु
		fqs->qs_gquota.qfs_ino = state.s_state[GRPQUOTA].ino;
		fqs->qs_gquota.qfs_nblks = state.s_state[GRPQUOTA].blocks;
		fqs->qs_gquota.qfs_nextents = state.s_state[GRPQUOTA].nextents;
	पूर्ण
	अगर (state.s_state[PRJQUOTA].ino) अणु
		/*
		 * Q_XGETQSTAT करोesn't have room क्रम both group and project
		 * quotas.  So, allow the project quota values to be copied out
		 * only अगर there is no group quota inक्रमmation available.
		 */
		अगर (!(state.s_state[GRPQUOTA].flags & QCI_ACCT_ENABLED)) अणु
			fqs->qs_gquota.qfs_ino = state.s_state[PRJQUOTA].ino;
			fqs->qs_gquota.qfs_nblks =
					state.s_state[PRJQUOTA].blocks;
			fqs->qs_gquota.qfs_nextents =
					state.s_state[PRJQUOTA].nextents;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक compat_copy_fs_qfilestat(काष्ठा compat_fs_qfilestat __user *to,
		काष्ठा fs_qfilestat *from)
अणु
	अगर (copy_to_user(to, from, माप(*to)) ||
	    put_user(from->qfs_nextents, &to->qfs_nextents))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक compat_copy_fs_quota_stat(काष्ठा compat_fs_quota_stat __user *to,
		काष्ठा fs_quota_stat *from)
अणु
	अगर (put_user(from->qs_version, &to->qs_version) ||
	    put_user(from->qs_flags, &to->qs_flags) ||
	    put_user(from->qs_pad, &to->qs_pad) ||
	    compat_copy_fs_qfilestat(&to->qs_uquota, &from->qs_uquota) ||
	    compat_copy_fs_qfilestat(&to->qs_gquota, &from->qs_gquota) ||
	    put_user(from->qs_incoredqs, &to->qs_incoredqs) ||
	    put_user(from->qs_bसमयlimit, &to->qs_bसमयlimit) ||
	    put_user(from->qs_iसमयlimit, &to->qs_iसमयlimit) ||
	    put_user(from->qs_rtbसमयlimit, &to->qs_rtbसमयlimit) ||
	    put_user(from->qs_bwarnlimit, &to->qs_bwarnlimit) ||
	    put_user(from->qs_iwarnlimit, &to->qs_iwarnlimit))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक quota_getxstate(काष्ठा super_block *sb, पूर्णांक type, व्योम __user *addr)
अणु
	काष्ठा fs_quota_stat fqs;
	पूर्णांक ret;

	अगर (!sb->s_qcop->get_state)
		वापस -ENOSYS;
	ret = quota_माला_लोtate(sb, type, &fqs);
	अगर (ret)
		वापस ret;

	अगर (compat_need_64bit_alignment_fixup())
		वापस compat_copy_fs_quota_stat(addr, &fqs);
	अगर (copy_to_user(addr, &fqs, माप(fqs)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक quota_माला_लोtatev(काष्ठा super_block *sb, पूर्णांक type,
			   काष्ठा fs_quota_statv *fqs)
अणु
	काष्ठा qc_state state;
	पूर्णांक ret;

	स_रखो(&state, 0, माप (काष्ठा qc_state));
	ret = sb->s_qcop->get_state(sb, &state);
	अगर (ret < 0)
		वापस ret;

	स_रखो(fqs, 0, माप(*fqs));
	fqs->qs_version = FS_QSTAT_VERSION;
	fqs->qs_flags = quota_state_to_flags(&state);
	/* No quota enabled? */
	अगर (!fqs->qs_flags)
		वापस -ENOSYS;
	fqs->qs_incoredqs = state.s_incoredqs;

	fqs->qs_bसमयlimit = state.s_state[type].spc_समयlimit;
	fqs->qs_iसमयlimit = state.s_state[type].ino_समयlimit;
	fqs->qs_rtbसमयlimit = state.s_state[type].rt_spc_समयlimit;
	fqs->qs_bwarnlimit = state.s_state[type].spc_warnlimit;
	fqs->qs_iwarnlimit = state.s_state[type].ino_warnlimit;
	fqs->qs_rtbwarnlimit = state.s_state[type].rt_spc_warnlimit;

	/* Inodes may be allocated even अगर inactive; copy out अगर present */
	अगर (state.s_state[USRQUOTA].ino) अणु
		fqs->qs_uquota.qfs_ino = state.s_state[USRQUOTA].ino;
		fqs->qs_uquota.qfs_nblks = state.s_state[USRQUOTA].blocks;
		fqs->qs_uquota.qfs_nextents = state.s_state[USRQUOTA].nextents;
	पूर्ण
	अगर (state.s_state[GRPQUOTA].ino) अणु
		fqs->qs_gquota.qfs_ino = state.s_state[GRPQUOTA].ino;
		fqs->qs_gquota.qfs_nblks = state.s_state[GRPQUOTA].blocks;
		fqs->qs_gquota.qfs_nextents = state.s_state[GRPQUOTA].nextents;
	पूर्ण
	अगर (state.s_state[PRJQUOTA].ino) अणु
		fqs->qs_pquota.qfs_ino = state.s_state[PRJQUOTA].ino;
		fqs->qs_pquota.qfs_nblks = state.s_state[PRJQUOTA].blocks;
		fqs->qs_pquota.qfs_nextents = state.s_state[PRJQUOTA].nextents;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक quota_getxstatev(काष्ठा super_block *sb, पूर्णांक type, व्योम __user *addr)
अणु
	काष्ठा fs_quota_statv fqs;
	पूर्णांक ret;

	अगर (!sb->s_qcop->get_state)
		वापस -ENOSYS;

	स_रखो(&fqs, 0, माप(fqs));
	अगर (copy_from_user(&fqs, addr, 1)) /* Just पढ़ो qs_version */
		वापस -EFAULT;

	/* If this kernel करोesn't support user specअगरied version, fail */
	चयन (fqs.qs_version) अणु
	हाल FS_QSTATV_VERSION1:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ret = quota_माला_लोtatev(sb, type, &fqs);
	अगर (!ret && copy_to_user(addr, &fqs, माप(fqs)))
		वापस -EFAULT;
	वापस ret;
पूर्ण

/*
 * XFS defines BBTOB and BTOBB macros inside fs/xfs/ and we cannot move them
 * out of there as xfsprogs rely on definitions being in that header file. So
 * just define same functions here क्रम quota purposes.
 */
#घोषणा XFS_BB_SHIFT 9

अटल अंतरभूत u64 quota_bbtob(u64 blocks)
अणु
	वापस blocks << XFS_BB_SHIFT;
पूर्ण

अटल अंतरभूत u64 quota_btobb(u64 bytes)
अणु
	वापस (bytes + (1 << XFS_BB_SHIFT) - 1) >> XFS_BB_SHIFT;
पूर्ण

अटल अंतरभूत s64 copy_from_xfs_dqblk_ts(स्थिर काष्ठा fs_disk_quota *d,
		__s32 समयr, __s8 समयr_hi)
अणु
	अगर (d->d_fieldmask & FS_DQ_BIGTIME)
		वापस (u32)समयr | (s64)समयr_hi << 32;
	वापस समयr;
पूर्ण

अटल व्योम copy_from_xfs_dqblk(काष्ठा qc_dqblk *dst, काष्ठा fs_disk_quota *src)
अणु
	dst->d_spc_hardlimit = quota_bbtob(src->d_blk_hardlimit);
	dst->d_spc_softlimit = quota_bbtob(src->d_blk_softlimit);
	dst->d_ino_hardlimit = src->d_ino_hardlimit;
	dst->d_ino_softlimit = src->d_ino_softlimit;
	dst->d_space = quota_bbtob(src->d_bcount);
	dst->d_ino_count = src->d_icount;
	dst->d_ino_समयr = copy_from_xfs_dqblk_ts(src, src->d_iसमयr,
						  src->d_iसमयr_hi);
	dst->d_spc_समयr = copy_from_xfs_dqblk_ts(src, src->d_bसमयr,
						  src->d_bसमयr_hi);
	dst->d_ino_warns = src->d_iwarns;
	dst->d_spc_warns = src->d_bwarns;
	dst->d_rt_spc_hardlimit = quota_bbtob(src->d_rtb_hardlimit);
	dst->d_rt_spc_softlimit = quota_bbtob(src->d_rtb_softlimit);
	dst->d_rt_space = quota_bbtob(src->d_rtbcount);
	dst->d_rt_spc_समयr = copy_from_xfs_dqblk_ts(src, src->d_rtbसमयr,
						     src->d_rtbसमयr_hi);
	dst->d_rt_spc_warns = src->d_rtbwarns;
	dst->d_fieldmask = 0;
	अगर (src->d_fieldmask & FS_DQ_ISOFT)
		dst->d_fieldmask |= QC_INO_SOFT;
	अगर (src->d_fieldmask & FS_DQ_IHARD)
		dst->d_fieldmask |= QC_INO_HARD;
	अगर (src->d_fieldmask & FS_DQ_BSOFT)
		dst->d_fieldmask |= QC_SPC_SOFT;
	अगर (src->d_fieldmask & FS_DQ_BHARD)
		dst->d_fieldmask |= QC_SPC_HARD;
	अगर (src->d_fieldmask & FS_DQ_RTBSOFT)
		dst->d_fieldmask |= QC_RT_SPC_SOFT;
	अगर (src->d_fieldmask & FS_DQ_RTBHARD)
		dst->d_fieldmask |= QC_RT_SPC_HARD;
	अगर (src->d_fieldmask & FS_DQ_BTIMER)
		dst->d_fieldmask |= QC_SPC_TIMER;
	अगर (src->d_fieldmask & FS_DQ_ITIMER)
		dst->d_fieldmask |= QC_INO_TIMER;
	अगर (src->d_fieldmask & FS_DQ_RTBTIMER)
		dst->d_fieldmask |= QC_RT_SPC_TIMER;
	अगर (src->d_fieldmask & FS_DQ_BWARNS)
		dst->d_fieldmask |= QC_SPC_WARNS;
	अगर (src->d_fieldmask & FS_DQ_IWARNS)
		dst->d_fieldmask |= QC_INO_WARNS;
	अगर (src->d_fieldmask & FS_DQ_RTBWARNS)
		dst->d_fieldmask |= QC_RT_SPC_WARNS;
	अगर (src->d_fieldmask & FS_DQ_BCOUNT)
		dst->d_fieldmask |= QC_SPACE;
	अगर (src->d_fieldmask & FS_DQ_ICOUNT)
		dst->d_fieldmask |= QC_INO_COUNT;
	अगर (src->d_fieldmask & FS_DQ_RTBCOUNT)
		dst->d_fieldmask |= QC_RT_SPACE;
पूर्ण

अटल व्योम copy_qcinfo_from_xfs_dqblk(काष्ठा qc_info *dst,
				       काष्ठा fs_disk_quota *src)
अणु
	स_रखो(dst, 0, माप(*dst));
	dst->i_spc_समयlimit = src->d_bसमयr;
	dst->i_ino_समयlimit = src->d_iसमयr;
	dst->i_rt_spc_समयlimit = src->d_rtbसमयr;
	dst->i_ino_warnlimit = src->d_iwarns;
	dst->i_spc_warnlimit = src->d_bwarns;
	dst->i_rt_spc_warnlimit = src->d_rtbwarns;
	अगर (src->d_fieldmask & FS_DQ_BWARNS)
		dst->i_fieldmask |= QC_SPC_WARNS;
	अगर (src->d_fieldmask & FS_DQ_IWARNS)
		dst->i_fieldmask |= QC_INO_WARNS;
	अगर (src->d_fieldmask & FS_DQ_RTBWARNS)
		dst->i_fieldmask |= QC_RT_SPC_WARNS;
	अगर (src->d_fieldmask & FS_DQ_BTIMER)
		dst->i_fieldmask |= QC_SPC_TIMER;
	अगर (src->d_fieldmask & FS_DQ_ITIMER)
		dst->i_fieldmask |= QC_INO_TIMER;
	अगर (src->d_fieldmask & FS_DQ_RTBTIMER)
		dst->i_fieldmask |= QC_RT_SPC_TIMER;
पूर्ण

अटल पूर्णांक quota_setxquota(काष्ठा super_block *sb, पूर्णांक type, qid_t id,
			   व्योम __user *addr)
अणु
	काष्ठा fs_disk_quota fdq;
	काष्ठा qc_dqblk qdq;
	काष्ठा kqid qid;

	अगर (copy_from_user(&fdq, addr, माप(fdq)))
		वापस -EFAULT;
	अगर (!sb->s_qcop->set_dqblk)
		वापस -ENOSYS;
	qid = make_kqid(current_user_ns(), type, id);
	अगर (!qid_has_mapping(sb->s_user_ns, qid))
		वापस -EINVAL;
	/* Are we actually setting समयr / warning limits क्रम all users? */
	अगर (from_kqid(sb->s_user_ns, qid) == 0 &&
	    fdq.d_fieldmask & (FS_DQ_WARNS_MASK | FS_DQ_TIMER_MASK)) अणु
		काष्ठा qc_info qinfo;
		पूर्णांक ret;

		अगर (!sb->s_qcop->set_info)
			वापस -EINVAL;
		copy_qcinfo_from_xfs_dqblk(&qinfo, &fdq);
		ret = sb->s_qcop->set_info(sb, type, &qinfo);
		अगर (ret)
			वापस ret;
		/* These are alपढ़ोy करोne */
		fdq.d_fieldmask &= ~(FS_DQ_WARNS_MASK | FS_DQ_TIMER_MASK);
	पूर्ण
	copy_from_xfs_dqblk(&qdq, &fdq);
	वापस sb->s_qcop->set_dqblk(sb, qid, &qdq);
पूर्ण

अटल अंतरभूत व्योम copy_to_xfs_dqblk_ts(स्थिर काष्ठा fs_disk_quota *d,
		__s32 *समयr_lo, __s8 *समयr_hi, s64 समयr)
अणु
	*समयr_lo = समयr;
	अगर (d->d_fieldmask & FS_DQ_BIGTIME)
		*समयr_hi = समयr >> 32;
पूर्ण

अटल अंतरभूत bool want_bigसमय(s64 समयr)
अणु
	वापस समयr > S32_MAX || समयr < S32_MIN;
पूर्ण

अटल व्योम copy_to_xfs_dqblk(काष्ठा fs_disk_quota *dst, काष्ठा qc_dqblk *src,
			      पूर्णांक type, qid_t id)
अणु
	स_रखो(dst, 0, माप(*dst));
	अगर (want_bigसमय(src->d_ino_समयr) || want_bigसमय(src->d_spc_समयr) ||
	    want_bigसमय(src->d_rt_spc_समयr))
		dst->d_fieldmask |= FS_DQ_BIGTIME;
	dst->d_version = FS_DQUOT_VERSION;
	dst->d_id = id;
	अगर (type == USRQUOTA)
		dst->d_flags = FS_USER_QUOTA;
	अन्यथा अगर (type == PRJQUOTA)
		dst->d_flags = FS_PROJ_QUOTA;
	अन्यथा
		dst->d_flags = FS_GROUP_QUOTA;
	dst->d_blk_hardlimit = quota_btobb(src->d_spc_hardlimit);
	dst->d_blk_softlimit = quota_btobb(src->d_spc_softlimit);
	dst->d_ino_hardlimit = src->d_ino_hardlimit;
	dst->d_ino_softlimit = src->d_ino_softlimit;
	dst->d_bcount = quota_btobb(src->d_space);
	dst->d_icount = src->d_ino_count;
	copy_to_xfs_dqblk_ts(dst, &dst->d_iसमयr, &dst->d_iसमयr_hi,
			     src->d_ino_समयr);
	copy_to_xfs_dqblk_ts(dst, &dst->d_bसमयr, &dst->d_bसमयr_hi,
			     src->d_spc_समयr);
	dst->d_iwarns = src->d_ino_warns;
	dst->d_bwarns = src->d_spc_warns;
	dst->d_rtb_hardlimit = quota_btobb(src->d_rt_spc_hardlimit);
	dst->d_rtb_softlimit = quota_btobb(src->d_rt_spc_softlimit);
	dst->d_rtbcount = quota_btobb(src->d_rt_space);
	copy_to_xfs_dqblk_ts(dst, &dst->d_rtbसमयr, &dst->d_rtbसमयr_hi,
			     src->d_rt_spc_समयr);
	dst->d_rtbwarns = src->d_rt_spc_warns;
पूर्ण

अटल पूर्णांक quota_getxquota(काष्ठा super_block *sb, पूर्णांक type, qid_t id,
			   व्योम __user *addr)
अणु
	काष्ठा fs_disk_quota fdq;
	काष्ठा qc_dqblk qdq;
	काष्ठा kqid qid;
	पूर्णांक ret;

	अगर (!sb->s_qcop->get_dqblk)
		वापस -ENOSYS;
	qid = make_kqid(current_user_ns(), type, id);
	अगर (!qid_has_mapping(sb->s_user_ns, qid))
		वापस -EINVAL;
	ret = sb->s_qcop->get_dqblk(sb, qid, &qdq);
	अगर (ret)
		वापस ret;
	copy_to_xfs_dqblk(&fdq, &qdq, type, id);
	अगर (copy_to_user(addr, &fdq, माप(fdq)))
		वापस -EFAULT;
	वापस ret;
पूर्ण

/*
 * Return quota क्रम next active quota >= this id, अगर any exists,
 * otherwise वापस -ENOENT via ->get_nextdqblk.
 */
अटल पूर्णांक quota_getnextxquota(काष्ठा super_block *sb, पूर्णांक type, qid_t id,
			    व्योम __user *addr)
अणु
	काष्ठा fs_disk_quota fdq;
	काष्ठा qc_dqblk qdq;
	काष्ठा kqid qid;
	qid_t id_out;
	पूर्णांक ret;

	अगर (!sb->s_qcop->get_nextdqblk)
		वापस -ENOSYS;
	qid = make_kqid(current_user_ns(), type, id);
	अगर (!qid_has_mapping(sb->s_user_ns, qid))
		वापस -EINVAL;
	ret = sb->s_qcop->get_nextdqblk(sb, &qid, &qdq);
	अगर (ret)
		वापस ret;
	id_out = from_kqid(current_user_ns(), qid);
	copy_to_xfs_dqblk(&fdq, &qdq, type, id_out);
	अगर (copy_to_user(addr, &fdq, माप(fdq)))
		वापस -EFAULT;
	वापस ret;
पूर्ण

अटल पूर्णांक quota_rmxquota(काष्ठा super_block *sb, व्योम __user *addr)
अणु
	__u32 flags;

	अगर (copy_from_user(&flags, addr, माप(flags)))
		वापस -EFAULT;
	अगर (!sb->s_qcop->rm_xquota)
		वापस -ENOSYS;
	वापस sb->s_qcop->rm_xquota(sb, flags);
पूर्ण

/* Copy parameters and call proper function */
अटल पूर्णांक करो_quotactl(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक cmd, qid_t id,
		       व्योम __user *addr, स्थिर काष्ठा path *path)
अणु
	पूर्णांक ret;

	type = array_index_nospec(type, MAXQUOTAS);
	/*
	 * Quota not supported on this fs? Check this beक्रमe s_quota_types
	 * since they needn't be set अगर quota is not supported at all.
	 */
	अगर (!sb->s_qcop)
		वापस -ENOSYS;
	अगर (!(sb->s_quota_types & (1 << type)))
		वापस -EINVAL;

	ret = check_quotactl_permission(sb, type, cmd, id);
	अगर (ret < 0)
		वापस ret;

	चयन (cmd) अणु
	हाल Q_QUOTAON:
		वापस quota_quotaon(sb, type, id, path);
	हाल Q_QUOTAOFF:
		वापस quota_quotaoff(sb, type);
	हाल Q_GETFMT:
		वापस quota_getfmt(sb, type, addr);
	हाल Q_GETINFO:
		वापस quota_getinfo(sb, type, addr);
	हाल Q_SETINFO:
		वापस quota_setinfo(sb, type, addr);
	हाल Q_GETQUOTA:
		वापस quota_getquota(sb, type, id, addr);
	हाल Q_GETNEXTQUOTA:
		वापस quota_getnextquota(sb, type, id, addr);
	हाल Q_SETQUOTA:
		वापस quota_setquota(sb, type, id, addr);
	हाल Q_SYNC:
		अगर (!sb->s_qcop->quota_sync)
			वापस -ENOSYS;
		वापस sb->s_qcop->quota_sync(sb, type);
	हाल Q_XQUOTAON:
		वापस quota_enable(sb, addr);
	हाल Q_XQUOTAOFF:
		वापस quota_disable(sb, addr);
	हाल Q_XQUOTARM:
		वापस quota_rmxquota(sb, addr);
	हाल Q_XGETQSTAT:
		वापस quota_getxstate(sb, type, addr);
	हाल Q_XGETQSTATV:
		वापस quota_getxstatev(sb, type, addr);
	हाल Q_XSETQLIM:
		वापस quota_setxquota(sb, type, id, addr);
	हाल Q_XGETQUOTA:
		वापस quota_getxquota(sb, type, id, addr);
	हाल Q_XGETNEXTQUOTA:
		वापस quota_getnextxquota(sb, type, id, addr);
	हाल Q_XQUOTASYNC:
		अगर (sb_rकरोnly(sb))
			वापस -EROFS;
		/* XFS quotas are fully coherent now, making this call a noop */
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Return 1 अगर 'cmd' will block on frozen fileप्रणाली */
अटल पूर्णांक quotactl_cmd_ग_लिखो(पूर्णांक cmd)
अणु
	/*
	 * We cannot allow Q_GETQUOTA and Q_GETNEXTQUOTA without ग_लिखो access
	 * as dquot_acquire() may allocate space क्रम new काष्ठाure and OCFS2
	 * needs to increment on-disk use count.
	 */
	चयन (cmd) अणु
	हाल Q_GETFMT:
	हाल Q_GETINFO:
	हाल Q_SYNC:
	हाल Q_XGETQSTAT:
	हाल Q_XGETQSTATV:
	हाल Q_XGETQUOTA:
	हाल Q_XGETNEXTQUOTA:
	हाल Q_XQUOTASYNC:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/* Return true अगर quotactl command is manipulating quota on/off state */
अटल bool quotactl_cmd_onoff(पूर्णांक cmd)
अणु
	वापस (cmd == Q_QUOTAON) || (cmd == Q_QUOTAOFF) ||
		 (cmd == Q_XQUOTAON) || (cmd == Q_XQUOTAOFF);
पूर्ण

/*
 * look up a superblock on which quota ops will be perक्रमmed
 * - use the name of a block device to find the superblock thereon
 */
अटल काष्ठा super_block *quotactl_block(स्थिर अक्षर __user *special, पूर्णांक cmd)
अणु
#अगर_घोषित CONFIG_BLOCK
	काष्ठा super_block *sb;
	काष्ठा filename *पंचांगp = getname(special);
	bool excl = false, thawed = false;
	पूर्णांक error;
	dev_t dev;

	अगर (IS_ERR(पंचांगp))
		वापस ERR_CAST(पंचांगp);
	error = lookup_bdev(पंचांगp->name, &dev);
	putname(पंचांगp);
	अगर (error)
		वापस ERR_PTR(error);

	अगर (quotactl_cmd_onoff(cmd)) अणु
		excl = true;
		thawed = true;
	पूर्ण अन्यथा अगर (quotactl_cmd_ग_लिखो(cmd)) अणु
		thawed = true;
	पूर्ण

retry:
	sb = user_get_super(dev, excl);
	अगर (!sb)
		वापस ERR_PTR(-ENODEV);
	अगर (thawed && sb->s_ग_लिखोrs.frozen != SB_UNFROZEN) अणु
		अगर (excl)
			up_ग_लिखो(&sb->s_umount);
		अन्यथा
			up_पढ़ो(&sb->s_umount);
		रुको_event(sb->s_ग_लिखोrs.रुको_unfrozen,
			   sb->s_ग_लिखोrs.frozen == SB_UNFROZEN);
		put_super(sb);
		जाओ retry;
	पूर्ण
	वापस sb;

#अन्यथा
	वापस ERR_PTR(-ENODEV);
#पूर्ण_अगर
पूर्ण

/*
 * This is the प्रणाली call पूर्णांकerface. This communicates with
 * the user-level programs. Currently this only supports diskquota
 * calls. Maybe we need to add the process quotas etc. in the future,
 * but we probably should use rlimits क्रम that.
 */
SYSCALL_DEFINE4(quotactl, अचिन्हित पूर्णांक, cmd, स्थिर अक्षर __user *, special,
		qid_t, id, व्योम __user *, addr)
अणु
	uपूर्णांक cmds, type;
	काष्ठा super_block *sb = शून्य;
	काष्ठा path path, *pathp = शून्य;
	पूर्णांक ret;

	cmds = cmd >> SUBCMDSHIFT;
	type = cmd & SUBCMDMASK;

	अगर (type >= MAXQUOTAS)
		वापस -EINVAL;

	/*
	 * As a special हाल Q_SYNC can be called without a specअगरic device.
	 * It will iterate all superblocks that have quota enabled and call
	 * the sync action on each of them.
	 */
	अगर (!special) अणु
		अगर (cmds == Q_SYNC)
			वापस quota_sync_all(type);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Path क्रम quotaon has to be resolved beक्रमe grabbing superblock
	 * because that माला_लो s_umount sem which is also possibly needed by path
	 * resolution (think about स्वतःfs) and thus deadlocks could arise.
	 */
	अगर (cmds == Q_QUOTAON) अणु
		ret = user_path_at(AT_FDCWD, addr, LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT, &path);
		अगर (ret)
			pathp = ERR_PTR(ret);
		अन्यथा
			pathp = &path;
	पूर्ण

	sb = quotactl_block(special, cmds);
	अगर (IS_ERR(sb)) अणु
		ret = PTR_ERR(sb);
		जाओ out;
	पूर्ण

	ret = करो_quotactl(sb, type, cmds, id, addr, pathp);

	अगर (!quotactl_cmd_onoff(cmds))
		drop_super(sb);
	अन्यथा
		drop_super_exclusive(sb);
out:
	अगर (pathp && !IS_ERR(pathp))
		path_put(pathp);
	वापस ret;
पूर्ण

SYSCALL_DEFINE4(quotactl_path, अचिन्हित पूर्णांक, cmd, स्थिर अक्षर __user *,
		mountpoपूर्णांक, qid_t, id, व्योम __user *, addr)
अणु
	काष्ठा super_block *sb;
	काष्ठा path mountpath;
	अचिन्हित पूर्णांक cmds = cmd >> SUBCMDSHIFT;
	अचिन्हित पूर्णांक type = cmd & SUBCMDMASK;
	पूर्णांक ret;

	अगर (type >= MAXQUOTAS)
		वापस -EINVAL;

	ret = user_path_at(AT_FDCWD, mountpoपूर्णांक,
			     LOOKUP_FOLLOW | LOOKUP_AUTOMOUNT, &mountpath);
	अगर (ret)
		वापस ret;

	sb = mountpath.mnt->mnt_sb;

	अगर (quotactl_cmd_ग_लिखो(cmds)) अणु
		ret = mnt_want_ग_लिखो(mountpath.mnt);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (quotactl_cmd_onoff(cmds))
		करोwn_ग_लिखो(&sb->s_umount);
	अन्यथा
		करोwn_पढ़ो(&sb->s_umount);

	ret = करो_quotactl(sb, type, cmds, id, addr, ERR_PTR(-EINVAL));

	अगर (quotactl_cmd_onoff(cmds))
		up_ग_लिखो(&sb->s_umount);
	अन्यथा
		up_पढ़ो(&sb->s_umount);

	अगर (quotactl_cmd_ग_लिखो(cmds))
		mnt_drop_ग_लिखो(mountpath.mnt);
out:
	path_put(&mountpath);

	वापस ret;
पूर्ण
