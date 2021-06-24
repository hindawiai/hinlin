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
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_qm.h"
#समावेश "xfs_log.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_log_recover.h"

STATIC व्योम
xlog_recover_dquot_ra_pass2(
	काष्ठा xlog			*log,
	काष्ठा xlog_recover_item	*item)
अणु
	काष्ठा xfs_mount	*mp = log->l_mp;
	काष्ठा xfs_disk_dquot	*recddq;
	काष्ठा xfs_dq_logक्रमmat	*dq_f;
	uपूर्णांक			type;

	अगर (mp->m_qflags == 0)
		वापस;

	recddq = item->ri_buf[1].i_addr;
	अगर (recddq == शून्य)
		वापस;
	अगर (item->ri_buf[1].i_len < माप(काष्ठा xfs_disk_dquot))
		वापस;

	type = recddq->d_type & XFS_DQTYPE_REC_MASK;
	ASSERT(type);
	अगर (log->l_quotaoffs_flag & type)
		वापस;

	dq_f = item->ri_buf[0].i_addr;
	ASSERT(dq_f);
	ASSERT(dq_f->qlf_len == 1);

	xlog_buf_पढ़ोahead(log, dq_f->qlf_blkno,
			XFS_FSB_TO_BB(mp, dq_f->qlf_len),
			&xfs_dquot_buf_ra_ops);
पूर्ण

/*
 * Recover a dquot record
 */
STATIC पूर्णांक
xlog_recover_dquot_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			current_lsn)
अणु
	काष्ठा xfs_mount		*mp = log->l_mp;
	काष्ठा xfs_buf			*bp;
	काष्ठा xfs_disk_dquot		*ddq, *recddq;
	काष्ठा xfs_dq_logक्रमmat		*dq_f;
	xfs_failaddr_t			fa;
	पूर्णांक				error;
	uपूर्णांक				type;

	/*
	 * Fileप्रणालीs are required to send in quota flags at mount समय.
	 */
	अगर (mp->m_qflags == 0)
		वापस 0;

	recddq = item->ri_buf[1].i_addr;
	अगर (recddq == शून्य) अणु
		xfs_alert(log->l_mp, "NULL dquot in %s.", __func__);
		वापस -EFSCORRUPTED;
	पूर्ण
	अगर (item->ri_buf[1].i_len < माप(काष्ठा xfs_disk_dquot)) अणु
		xfs_alert(log->l_mp, "dquot too small (%d) in %s.",
			item->ri_buf[1].i_len, __func__);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * This type of quotas was turned off, so ignore this record.
	 */
	type = recddq->d_type & XFS_DQTYPE_REC_MASK;
	ASSERT(type);
	अगर (log->l_quotaoffs_flag & type)
		वापस 0;

	/*
	 * At this poपूर्णांक we know that quota was _not_ turned off.
	 * Since the mount flags are not indicating to us otherwise, this
	 * must mean that quota is on, and the dquot needs to be replayed.
	 * Remember that we may not have fully recovered the superblock yet,
	 * so we can't करो the usual trick of looking at the SB quota bits.
	 *
	 * The other possibility, of course, is that the quota subप्रणाली was
	 * हटाओd since the last mount - ENOSYS.
	 */
	dq_f = item->ri_buf[0].i_addr;
	ASSERT(dq_f);
	fa = xfs_dquot_verअगरy(mp, recddq, dq_f->qlf_id);
	अगर (fa) अणु
		xfs_alert(mp, "corrupt dquot ID 0x%x in log at %pS",
				dq_f->qlf_id, fa);
		वापस -EFSCORRUPTED;
	पूर्ण
	ASSERT(dq_f->qlf_len == 1);

	/*
	 * At this poपूर्णांक we are assuming that the dquots have been allocated
	 * and hence the buffer has valid dquots stamped in it. It should,
	 * thereक्रमe, pass verअगरier validation. If the dquot is bad, then the
	 * we'll return an error here, so we don't need to specअगरically check
	 * the dquot in the buffer after the verअगरier has run.
	 */
	error = xfs_trans_पढ़ो_buf(mp, शून्य, mp->m_ddev_targp, dq_f->qlf_blkno,
				   XFS_FSB_TO_BB(mp, dq_f->qlf_len), 0, &bp,
				   &xfs_dquot_buf_ops);
	अगर (error)
		वापस error;

	ASSERT(bp);
	ddq = xfs_buf_offset(bp, dq_f->qlf_boffset);

	/*
	 * If the dquot has an LSN in it, recover the dquot only अगर it's less
	 * than the lsn of the transaction we are replaying.
	 */
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dqblk *dqb = (काष्ठा xfs_dqblk *)ddq;
		xfs_lsn_t	lsn = be64_to_cpu(dqb->dd_lsn);

		अगर (lsn && lsn != -1 && XFS_LSN_CMP(lsn, current_lsn) >= 0) अणु
			जाओ out_release;
		पूर्ण
	पूर्ण

	स_नकल(ddq, recddq, item->ri_buf[1].i_len);
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		xfs_update_cksum((अक्षर *)ddq, माप(काष्ठा xfs_dqblk),
				 XFS_DQUOT_CRC_OFF);
	पूर्ण

	ASSERT(dq_f->qlf_size == 2);
	ASSERT(bp->b_mount == mp);
	bp->b_flags |= _XBF_LOGRECOVERY;
	xfs_buf_delwri_queue(bp, buffer_list);

out_release:
	xfs_buf_rअन्यथा(bp);
	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_dquot_item_ops = अणु
	.item_type		= XFS_LI_DQUOT,
	.ra_pass2		= xlog_recover_dquot_ra_pass2,
	.commit_pass2		= xlog_recover_dquot_commit_pass2,
पूर्ण;

/*
 * Recover QUOTAOFF records. We simply make a note of it in the xlog
 * काष्ठाure, so that we know not to करो any dquot item or dquot buffer recovery,
 * of that type.
 */
STATIC पूर्णांक
xlog_recover_quotaoff_commit_pass1(
	काष्ठा xlog			*log,
	काष्ठा xlog_recover_item	*item)
अणु
	काष्ठा xfs_qoff_logक्रमmat	*qoff_f = item->ri_buf[0].i_addr;
	ASSERT(qoff_f);

	/*
	 * The logitem क्रमmat's flag tells us अगर this was user quotaoff,
	 * group/project quotaoff or both.
	 */
	अगर (qoff_f->qf_flags & XFS_UQUOTA_ACCT)
		log->l_quotaoffs_flag |= XFS_DQTYPE_USER;
	अगर (qoff_f->qf_flags & XFS_PQUOTA_ACCT)
		log->l_quotaoffs_flag |= XFS_DQTYPE_PROJ;
	अगर (qoff_f->qf_flags & XFS_GQUOTA_ACCT)
		log->l_quotaoffs_flag |= XFS_DQTYPE_GROUP;

	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_quotaoff_item_ops = अणु
	.item_type		= XFS_LI_QUOTAOFF,
	.commit_pass1		= xlog_recover_quotaoff_commit_pass1,
	/* nothing to commit in pass2 */
पूर्ण;
