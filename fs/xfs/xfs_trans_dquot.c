<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002 Silicon Graphics, Inc.
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
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_qm.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_error.h"

STATIC व्योम	xfs_trans_alloc_dqinfo(xfs_trans_t *);

/*
 * Add the locked dquot to the transaction.
 * The dquot must be locked, and it cannot be associated with any
 * transaction.
 */
व्योम
xfs_trans_dqjoin(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_dquot	*dqp)
अणु
	ASSERT(XFS_DQ_IS_LOCKED(dqp));
	ASSERT(dqp->q_logitem.qli_dquot == dqp);

	/*
	 * Get a log_item_desc to poपूर्णांक at the new item.
	 */
	xfs_trans_add_item(tp, &dqp->q_logitem.qli_item);
पूर्ण

/*
 * This is called to mark the dquot as needing
 * to be logged when the transaction is committed.  The dquot must
 * alपढ़ोy be associated with the given transaction.
 * Note that it marks the entire transaction as dirty. In the ordinary
 * हाल, this माला_लो called via xfs_trans_commit, after the transaction
 * is alपढ़ोy dirty. However, there's nothing stop this from getting
 * called directly, as करोne by xfs_qm_scall_setqlim. Hence, the TRANS_सूचीTY
 * flag.
 */
व्योम
xfs_trans_log_dquot(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_dquot	*dqp)
अणु
	ASSERT(XFS_DQ_IS_LOCKED(dqp));

	/* Upgrade the dquot to bigसमय क्रमmat अगर possible. */
	अगर (dqp->q_id != 0 &&
	    xfs_sb_version_hasbigसमय(&tp->t_mountp->m_sb) &&
	    !(dqp->q_type & XFS_DQTYPE_BIGTIME))
		dqp->q_type |= XFS_DQTYPE_BIGTIME;

	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &dqp->q_logitem.qli_item.li_flags);
पूर्ण

/*
 * Carry क्रमward whatever is left of the quota blk reservation to
 * the spanky new transaction
 */
व्योम
xfs_trans_dup_dqinfo(
	काष्ठा xfs_trans	*otp,
	काष्ठा xfs_trans	*ntp)
अणु
	काष्ठा xfs_dqtrx	*oq, *nq;
	पूर्णांक			i, j;
	काष्ठा xfs_dqtrx	*oqa, *nqa;
	uपूर्णांक64_t		blk_res_used;

	अगर (!otp->t_dqinfo)
		वापस;

	xfs_trans_alloc_dqinfo(ntp);

	क्रम (j = 0; j < XFS_QM_TRANS_DQTYPES; j++) अणु
		oqa = otp->t_dqinfo->dqs[j];
		nqa = ntp->t_dqinfo->dqs[j];
		क्रम (i = 0; i < XFS_QM_TRANS_MAXDQS; i++) अणु
			blk_res_used = 0;

			अगर (oqa[i].qt_dquot == शून्य)
				अवरोध;
			oq = &oqa[i];
			nq = &nqa[i];

			अगर (oq->qt_blk_res && oq->qt_bcount_delta > 0)
				blk_res_used = oq->qt_bcount_delta;

			nq->qt_dquot = oq->qt_dquot;
			nq->qt_bcount_delta = nq->qt_icount_delta = 0;
			nq->qt_rtbcount_delta = 0;

			/*
			 * Transfer whatever is left of the reservations.
			 */
			nq->qt_blk_res = oq->qt_blk_res - blk_res_used;
			oq->qt_blk_res = blk_res_used;

			nq->qt_rtblk_res = oq->qt_rtblk_res -
				oq->qt_rtblk_res_used;
			oq->qt_rtblk_res = oq->qt_rtblk_res_used;

			nq->qt_ino_res = oq->qt_ino_res - oq->qt_ino_res_used;
			oq->qt_ino_res = oq->qt_ino_res_used;

		पूर्ण
	पूर्ण
पूर्ण

/*
 * Wrap around mod_dquot to account क्रम both user and group quotas.
 */
व्योम
xfs_trans_mod_dquot_byino(
	xfs_trans_t	*tp,
	xfs_inode_t	*ip,
	uपूर्णांक		field,
	पूर्णांक64_t		delta)
अणु
	xfs_mount_t	*mp = tp->t_mountp;

	अगर (!XFS_IS_QUOTA_RUNNING(mp) ||
	    !XFS_IS_QUOTA_ON(mp) ||
	    xfs_is_quota_inode(&mp->m_sb, ip->i_ino))
		वापस;

	अगर (XFS_IS_UQUOTA_ON(mp) && ip->i_udquot)
		(व्योम) xfs_trans_mod_dquot(tp, ip->i_udquot, field, delta);
	अगर (XFS_IS_GQUOTA_ON(mp) && ip->i_gdquot)
		(व्योम) xfs_trans_mod_dquot(tp, ip->i_gdquot, field, delta);
	अगर (XFS_IS_PQUOTA_ON(mp) && ip->i_pdquot)
		(व्योम) xfs_trans_mod_dquot(tp, ip->i_pdquot, field, delta);
पूर्ण

STATIC काष्ठा xfs_dqtrx *
xfs_trans_get_dqtrx(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_dquot	*dqp)
अणु
	पूर्णांक			i;
	काष्ठा xfs_dqtrx	*qa;

	चयन (xfs_dquot_type(dqp)) अणु
	हाल XFS_DQTYPE_USER:
		qa = tp->t_dqinfo->dqs[XFS_QM_TRANS_USR];
		अवरोध;
	हाल XFS_DQTYPE_GROUP:
		qa = tp->t_dqinfo->dqs[XFS_QM_TRANS_GRP];
		अवरोध;
	हाल XFS_DQTYPE_PROJ:
		qa = tp->t_dqinfo->dqs[XFS_QM_TRANS_PRJ];
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < XFS_QM_TRANS_MAXDQS; i++) अणु
		अगर (qa[i].qt_dquot == शून्य ||
		    qa[i].qt_dquot == dqp)
			वापस &qa[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Make the changes in the transaction काष्ठाure.
 * The moral equivalent to xfs_trans_mod_sb().
 * We करोn't touch any fields in the dquot, so we don't care
 * अगर it's locked or not (most of the time it won't be).
 */
व्योम
xfs_trans_mod_dquot(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_dquot	*dqp,
	uपूर्णांक			field,
	पूर्णांक64_t			delta)
अणु
	काष्ठा xfs_dqtrx	*qtrx;

	ASSERT(tp);
	ASSERT(XFS_IS_QUOTA_RUNNING(tp->t_mountp));
	qtrx = शून्य;

	अगर (!delta)
		वापस;

	अगर (tp->t_dqinfo == शून्य)
		xfs_trans_alloc_dqinfo(tp);
	/*
	 * Find either the first मुक्त slot or the slot that beदीर्घs
	 * to this dquot.
	 */
	qtrx = xfs_trans_get_dqtrx(tp, dqp);
	ASSERT(qtrx);
	अगर (qtrx->qt_dquot == शून्य)
		qtrx->qt_dquot = dqp;

	trace_xfs_trans_mod_dquot_beक्रमe(qtrx);
	trace_xfs_trans_mod_dquot(tp, dqp, field, delta);

	चयन (field) अणु
	/* regular disk blk reservation */
	हाल XFS_TRANS_DQ_RES_BLKS:
		qtrx->qt_blk_res += delta;
		अवरोध;

	/* inode reservation */
	हाल XFS_TRANS_DQ_RES_INOS:
		qtrx->qt_ino_res += delta;
		अवरोध;

	/* disk blocks used. */
	हाल XFS_TRANS_DQ_BCOUNT:
		qtrx->qt_bcount_delta += delta;
		अवरोध;

	हाल XFS_TRANS_DQ_DELBCOUNT:
		qtrx->qt_delbcnt_delta += delta;
		अवरोध;

	/* Inode Count */
	हाल XFS_TRANS_DQ_ICOUNT:
		अगर (qtrx->qt_ino_res && delta > 0) अणु
			qtrx->qt_ino_res_used += delta;
			ASSERT(qtrx->qt_ino_res >= qtrx->qt_ino_res_used);
		पूर्ण
		qtrx->qt_icount_delta += delta;
		अवरोध;

	/* rtblk reservation */
	हाल XFS_TRANS_DQ_RES_RTBLKS:
		qtrx->qt_rtblk_res += delta;
		अवरोध;

	/* rtblk count */
	हाल XFS_TRANS_DQ_RTBCOUNT:
		अगर (qtrx->qt_rtblk_res && delta > 0) अणु
			qtrx->qt_rtblk_res_used += delta;
			ASSERT(qtrx->qt_rtblk_res >= qtrx->qt_rtblk_res_used);
		पूर्ण
		qtrx->qt_rtbcount_delta += delta;
		अवरोध;

	हाल XFS_TRANS_DQ_DELRTBCOUNT:
		qtrx->qt_delrtb_delta += delta;
		अवरोध;

	शेष:
		ASSERT(0);
	पूर्ण

	trace_xfs_trans_mod_dquot_after(qtrx);
पूर्ण


/*
 * Given an array of dqtrx काष्ठाures, lock all the dquots associated and join
 * them to the transaction, provided they have been modअगरied.  We know that the
 * highest number of dquots of one type - usr, grp and prj - involved in a
 * transaction is 3 so we करोn't need to make this very generic.
 */
STATIC व्योम
xfs_trans_dqlockedjoin(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_dqtrx	*q)
अणु
	ASSERT(q[0].qt_dquot != शून्य);
	अगर (q[1].qt_dquot == शून्य) अणु
		xfs_dqlock(q[0].qt_dquot);
		xfs_trans_dqjoin(tp, q[0].qt_dquot);
	पूर्ण अन्यथा अणु
		ASSERT(XFS_QM_TRANS_MAXDQS == 2);
		xfs_dqlock2(q[0].qt_dquot, q[1].qt_dquot);
		xfs_trans_dqjoin(tp, q[0].qt_dquot);
		xfs_trans_dqjoin(tp, q[1].qt_dquot);
	पूर्ण
पूर्ण

/* Apply dqtrx changes to the quota reservation counters. */
अटल अंतरभूत व्योम
xfs_apply_quota_reservation_deltas(
	काष्ठा xfs_dquot_res	*res,
	uपूर्णांक64_t		reserved,
	पूर्णांक64_t			res_used,
	पूर्णांक64_t			count_delta)
अणु
	अगर (reserved != 0) अणु
		/*
		 * Subtle math here: If reserved > res_used (the normal हाल),
		 * we're simply subtracting the unused transaction quota
		 * reservation from the dquot reservation.
		 *
		 * If, however, res_used > reserved, then we have allocated
		 * more quota blocks than were reserved क्रम the transaction.
		 * We must add that excess to the dquot reservation since it
		 * tracks (usage + resv) and by definition we didn't reserve
		 * that excess.
		 */
		res->reserved -= असल(reserved - res_used);
	पूर्ण अन्यथा अगर (count_delta != 0) अणु
		/*
		 * These blks were never reserved, either inside a transaction
		 * or outside one (in a delayed allocation). Also, this isn't
		 * always a negative number since we someबार deliberately
		 * skip quota reservations.
		 */
		res->reserved += count_delta;
	पूर्ण
पूर्ण

/*
 * Called by xfs_trans_commit() and similar in spirit to
 * xfs_trans_apply_sb_deltas().
 * Go thru all the dquots beदीर्घing to this transaction and modअगरy the
 * INCORE dquot to reflect the actual usages.
 * Unreserve just the reservations करोne by this transaction.
 * dquot is still left locked at निकास.
 */
व्योम
xfs_trans_apply_dquot_deltas(
	काष्ठा xfs_trans	*tp)
अणु
	पूर्णांक			i, j;
	काष्ठा xfs_dquot	*dqp;
	काष्ठा xfs_dqtrx	*qtrx, *qa;
	पूर्णांक64_t			totalbdelta;
	पूर्णांक64_t			totalrtbdelta;

	अगर (!tp->t_dqinfo)
		वापस;

	ASSERT(tp->t_dqinfo);
	क्रम (j = 0; j < XFS_QM_TRANS_DQTYPES; j++) अणु
		qa = tp->t_dqinfo->dqs[j];
		अगर (qa[0].qt_dquot == शून्य)
			जारी;

		/*
		 * Lock all of the dquots and join them to the transaction.
		 */
		xfs_trans_dqlockedjoin(tp, qa);

		क्रम (i = 0; i < XFS_QM_TRANS_MAXDQS; i++) अणु
			uपूर्णांक64_t	blk_res_used;

			qtrx = &qa[i];
			/*
			 * The array of dquots is filled
			 * sequentially, not sparsely.
			 */
			अगर ((dqp = qtrx->qt_dquot) == शून्य)
				अवरोध;

			ASSERT(XFS_DQ_IS_LOCKED(dqp));

			/*
			 * adjust the actual number of blocks used
			 */

			/*
			 * The issue here is - someबार we करोn't make a blkquota
			 * reservation पूर्णांकentionally to be fair to users
			 * (when the amount is small). On the other hand,
			 * delayed allocs करो make reservations, but that's
			 * outside of a transaction, so we have no
			 * idea how much was really reserved.
			 * So, here we've accumulated delayed allocation blks and
			 * non-delay blks. The assumption is that the
			 * delayed ones are always reserved (outside of a
			 * transaction), and the others may or may not have
			 * quota reservations.
			 */
			totalbdelta = qtrx->qt_bcount_delta +
				qtrx->qt_delbcnt_delta;
			totalrtbdelta = qtrx->qt_rtbcount_delta +
				qtrx->qt_delrtb_delta;

			अगर (totalbdelta != 0 || totalrtbdelta != 0 ||
			    qtrx->qt_icount_delta != 0) अणु
				trace_xfs_trans_apply_dquot_deltas_beक्रमe(dqp);
				trace_xfs_trans_apply_dquot_deltas(qtrx);
			पूर्ण

#अगर_घोषित DEBUG
			अगर (totalbdelta < 0)
				ASSERT(dqp->q_blk.count >= -totalbdelta);

			अगर (totalrtbdelta < 0)
				ASSERT(dqp->q_rtb.count >= -totalrtbdelta);

			अगर (qtrx->qt_icount_delta < 0)
				ASSERT(dqp->q_ino.count >= -qtrx->qt_icount_delta);
#पूर्ण_अगर
			अगर (totalbdelta)
				dqp->q_blk.count += totalbdelta;

			अगर (qtrx->qt_icount_delta)
				dqp->q_ino.count += qtrx->qt_icount_delta;

			अगर (totalrtbdelta)
				dqp->q_rtb.count += totalrtbdelta;

			अगर (totalbdelta != 0 || totalrtbdelta != 0 ||
			    qtrx->qt_icount_delta != 0)
				trace_xfs_trans_apply_dquot_deltas_after(dqp);

			/*
			 * Get any शेष limits in use.
			 * Start/reset the समयr(s) अगर needed.
			 */
			अगर (dqp->q_id) अणु
				xfs_qm_adjust_dqlimits(dqp);
				xfs_qm_adjust_dqसमयrs(dqp);
			पूर्ण

			dqp->q_flags |= XFS_DQFLAG_सूचीTY;
			/*
			 * add this to the list of items to get logged
			 */
			xfs_trans_log_dquot(tp, dqp);
			/*
			 * Take off what's left of the original reservation.
			 * In हाल of delayed allocations, there's no
			 * reservation that a transaction काष्ठाure knows of.
			 */
			blk_res_used = max_t(पूर्णांक64_t, 0, qtrx->qt_bcount_delta);
			xfs_apply_quota_reservation_deltas(&dqp->q_blk,
					qtrx->qt_blk_res, blk_res_used,
					qtrx->qt_bcount_delta);

			/*
			 * Adjust the RT reservation.
			 */
			xfs_apply_quota_reservation_deltas(&dqp->q_rtb,
					qtrx->qt_rtblk_res,
					qtrx->qt_rtblk_res_used,
					qtrx->qt_rtbcount_delta);

			/*
			 * Adjust the inode reservation.
			 */
			ASSERT(qtrx->qt_ino_res >= qtrx->qt_ino_res_used);
			xfs_apply_quota_reservation_deltas(&dqp->q_ino,
					qtrx->qt_ino_res,
					qtrx->qt_ino_res_used,
					qtrx->qt_icount_delta);

			ASSERT(dqp->q_blk.reserved >= dqp->q_blk.count);
			ASSERT(dqp->q_ino.reserved >= dqp->q_ino.count);
			ASSERT(dqp->q_rtb.reserved >= dqp->q_rtb.count);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Release the reservations, and adjust the dquots accordingly.
 * This is called only when the transaction is being पातed. If by
 * any chance we have करोne dquot modअगरications incore (ie. deltas) alपढ़ोy,
 * we simply throw those away, since that's the expected behavior
 * when a transaction is curtailed without a commit.
 */
व्योम
xfs_trans_unreserve_and_mod_dquots(
	काष्ठा xfs_trans	*tp)
अणु
	पूर्णांक			i, j;
	काष्ठा xfs_dquot	*dqp;
	काष्ठा xfs_dqtrx	*qtrx, *qa;
	bool			locked;

	अगर (!tp->t_dqinfo)
		वापस;

	क्रम (j = 0; j < XFS_QM_TRANS_DQTYPES; j++) अणु
		qa = tp->t_dqinfo->dqs[j];

		क्रम (i = 0; i < XFS_QM_TRANS_MAXDQS; i++) अणु
			qtrx = &qa[i];
			/*
			 * We assume that the array of dquots is filled
			 * sequentially, not sparsely.
			 */
			अगर ((dqp = qtrx->qt_dquot) == शून्य)
				अवरोध;
			/*
			 * Unreserve the original reservation. We करोn't care
			 * about the number of blocks used field, or deltas.
			 * Also we करोn't bother to zero the fields.
			 */
			locked = false;
			अगर (qtrx->qt_blk_res) अणु
				xfs_dqlock(dqp);
				locked = true;
				dqp->q_blk.reserved -=
					(xfs_qcnt_t)qtrx->qt_blk_res;
			पूर्ण
			अगर (qtrx->qt_ino_res) अणु
				अगर (!locked) अणु
					xfs_dqlock(dqp);
					locked = true;
				पूर्ण
				dqp->q_ino.reserved -=
					(xfs_qcnt_t)qtrx->qt_ino_res;
			पूर्ण

			अगर (qtrx->qt_rtblk_res) अणु
				अगर (!locked) अणु
					xfs_dqlock(dqp);
					locked = true;
				पूर्ण
				dqp->q_rtb.reserved -=
					(xfs_qcnt_t)qtrx->qt_rtblk_res;
			पूर्ण
			अगर (locked)
				xfs_dqunlock(dqp);

		पूर्ण
	पूर्ण
पूर्ण

STATIC व्योम
xfs_quota_warn(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dquot	*dqp,
	पूर्णांक			type)
अणु
	क्रमागत quota_type		qtype;

	चयन (xfs_dquot_type(dqp)) अणु
	हाल XFS_DQTYPE_PROJ:
		qtype = PRJQUOTA;
		अवरोध;
	हाल XFS_DQTYPE_USER:
		qtype = USRQUOTA;
		अवरोध;
	हाल XFS_DQTYPE_GROUP:
		qtype = GRPQUOTA;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	quota_send_warning(make_kqid(&init_user_ns, qtype, dqp->q_id),
			   mp->m_super->s_dev, type);
पूर्ण

/*
 * Decide अगर we can make an additional reservation against a quota resource.
 * Returns an inode QUOTA_NL_ warning code and whether or not it's fatal.
 *
 * Note that we assume that the numeric dअगरference between the inode and block
 * warning codes will always be 3 since it's userspace ABI now, and will never
 * decrease the quota reservation, so the *BELOW messages are irrelevant.
 */
अटल अंतरभूत पूर्णांक
xfs_dqresv_check(
	काष्ठा xfs_dquot_res	*res,
	काष्ठा xfs_quota_limits	*qlim,
	पूर्णांक64_t			delta,
	bool			*fatal)
अणु
	xfs_qcnt_t		hardlimit = res->hardlimit;
	xfs_qcnt_t		softlimit = res->softlimit;
	xfs_qcnt_t		total_count = res->reserved + delta;

	BUILD_BUG_ON(QUOTA_NL_BHARDWARN     != QUOTA_NL_IHARDWARN + 3);
	BUILD_BUG_ON(QUOTA_NL_BSOFTLONGWARN != QUOTA_NL_ISOFTLONGWARN + 3);
	BUILD_BUG_ON(QUOTA_NL_BSOFTWARN     != QUOTA_NL_ISOFTWARN + 3);

	*fatal = false;
	अगर (delta <= 0)
		वापस QUOTA_NL_NOWARN;

	अगर (!hardlimit)
		hardlimit = qlim->hard;
	अगर (!softlimit)
		softlimit = qlim->soft;

	अगर (hardlimit && total_count > hardlimit) अणु
		*fatal = true;
		वापस QUOTA_NL_IHARDWARN;
	पूर्ण

	अगर (softlimit && total_count > softlimit) अणु
		समय64_t	now = kसमय_get_real_seconds();

		अगर ((res->समयr != 0 && now > res->समयr) ||
		    (res->warnings != 0 && res->warnings >= qlim->warn)) अणु
			*fatal = true;
			वापस QUOTA_NL_ISOFTLONGWARN;
		पूर्ण

		res->warnings++;
		वापस QUOTA_NL_ISOFTWARN;
	पूर्ण

	वापस QUOTA_NL_NOWARN;
पूर्ण

/*
 * This reserves disk blocks and inodes against a dquot.
 * Flags indicate अगर the dquot is to be locked here and also
 * अगर the blk reservation is क्रम RT or regular blocks.
 * Sending in XFS_QMOPT_FORCE_RES flag skips the quota check.
 */
STATIC पूर्णांक
xfs_trans_dqresv(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dquot	*dqp,
	पूर्णांक64_t			nblks,
	दीर्घ			ninos,
	uपूर्णांक			flags)
अणु
	काष्ठा xfs_quotainfo	*q = mp->m_quotainfo;
	काष्ठा xfs_def_quota	*defq;
	काष्ठा xfs_dquot_res	*blkres;
	काष्ठा xfs_quota_limits	*qlim;

	xfs_dqlock(dqp);

	defq = xfs_get_defquota(q, xfs_dquot_type(dqp));

	अगर (flags & XFS_TRANS_DQ_RES_BLKS) अणु
		blkres = &dqp->q_blk;
		qlim = &defq->blk;
	पूर्ण अन्यथा अणु
		blkres = &dqp->q_rtb;
		qlim = &defq->rtb;
	पूर्ण

	अगर ((flags & XFS_QMOPT_FORCE_RES) == 0 && dqp->q_id &&
	    xfs_dquot_is_enक्रमced(dqp)) अणु
		पूर्णांक		quota_nl;
		bool		fatal;

		/*
		 * dquot is locked alपढ़ोy. See अगर we'd go over the hardlimit
		 * or exceed the समयlimit अगर we'd reserve resources.
		 */
		quota_nl = xfs_dqresv_check(blkres, qlim, nblks, &fatal);
		अगर (quota_nl != QUOTA_NL_NOWARN) अणु
			/*
			 * Quota block warning codes are 3 more than the inode
			 * codes, which we check above.
			 */
			xfs_quota_warn(mp, dqp, quota_nl + 3);
			अगर (fatal)
				जाओ error_वापस;
		पूर्ण

		quota_nl = xfs_dqresv_check(&dqp->q_ino, &defq->ino, ninos,
				&fatal);
		अगर (quota_nl != QUOTA_NL_NOWARN) अणु
			xfs_quota_warn(mp, dqp, quota_nl);
			अगर (fatal)
				जाओ error_वापस;
		पूर्ण
	पूर्ण

	/*
	 * Change the reservation, but not the actual usage.
	 * Note that q_blk.reserved = q_blk.count + resv
	 */
	blkres->reserved += (xfs_qcnt_t)nblks;
	dqp->q_ino.reserved += (xfs_qcnt_t)ninos;

	/*
	 * note the reservation amt in the trans काष्ठा too,
	 * so that the transaction knows how much was reserved by
	 * it against this particular dquot.
	 * We करोn't करो this when we are reserving क्रम a delayed allocation,
	 * because we करोn't have the luxury of a transaction envelope then.
	 */
	अगर (tp) अणु
		ASSERT(flags & XFS_QMOPT_RESBLK_MASK);
		xfs_trans_mod_dquot(tp, dqp, flags & XFS_QMOPT_RESBLK_MASK,
				    nblks);
		xfs_trans_mod_dquot(tp, dqp, XFS_TRANS_DQ_RES_INOS, ninos);
	पूर्ण

	अगर (XFS_IS_CORRUPT(mp, dqp->q_blk.reserved < dqp->q_blk.count) ||
	    XFS_IS_CORRUPT(mp, dqp->q_rtb.reserved < dqp->q_rtb.count) ||
	    XFS_IS_CORRUPT(mp, dqp->q_ino.reserved < dqp->q_ino.count))
		जाओ error_corrupt;

	xfs_dqunlock(dqp);
	वापस 0;

error_वापस:
	xfs_dqunlock(dqp);
	अगर (xfs_dquot_type(dqp) == XFS_DQTYPE_PROJ)
		वापस -ENOSPC;
	वापस -EDQUOT;
error_corrupt:
	xfs_dqunlock(dqp);
	xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
	वापस -EFSCORRUPTED;
पूर्ण


/*
 * Given dquot(s), make disk block and/or inode reservations against them.
 * The fact that this करोes the reservation against user, group and
 * project quotas is important, because this follows a all-or-nothing
 * approach.
 *
 * flags = XFS_QMOPT_FORCE_RES evades limit enक्रमcement. Used by chown.
 *	   XFS_QMOPT_ENOSPC वापसs ENOSPC not EDQUOT.  Used by pquota.
 *	   XFS_TRANS_DQ_RES_BLKS reserves regular disk blocks
 *	   XFS_TRANS_DQ_RES_RTBLKS reserves realसमय disk blocks
 * dquots are unlocked on वापस, अगर they were not locked by caller.
 */
पूर्णांक
xfs_trans_reserve_quota_bydquots(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dquot	*udqp,
	काष्ठा xfs_dquot	*gdqp,
	काष्ठा xfs_dquot	*pdqp,
	पूर्णांक64_t			nblks,
	दीर्घ			ninos,
	uपूर्णांक			flags)
अणु
	पूर्णांक		error;

	अगर (!XFS_IS_QUOTA_RUNNING(mp) || !XFS_IS_QUOTA_ON(mp))
		वापस 0;

	ASSERT(flags & XFS_QMOPT_RESBLK_MASK);

	अगर (udqp) अणु
		error = xfs_trans_dqresv(tp, mp, udqp, nblks, ninos, flags);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (gdqp) अणु
		error = xfs_trans_dqresv(tp, mp, gdqp, nblks, ninos, flags);
		अगर (error)
			जाओ unwind_usr;
	पूर्ण

	अगर (pdqp) अणु
		error = xfs_trans_dqresv(tp, mp, pdqp, nblks, ninos, flags);
		अगर (error)
			जाओ unwind_grp;
	पूर्ण

	/*
	 * Didn't change anything critical, so, no need to log
	 */
	वापस 0;

unwind_grp:
	flags |= XFS_QMOPT_FORCE_RES;
	अगर (gdqp)
		xfs_trans_dqresv(tp, mp, gdqp, -nblks, -ninos, flags);
unwind_usr:
	flags |= XFS_QMOPT_FORCE_RES;
	अगर (udqp)
		xfs_trans_dqresv(tp, mp, udqp, -nblks, -ninos, flags);
	वापस error;
पूर्ण


/*
 * Lock the dquot and change the reservation अगर we can.
 * This करोesn't change the actual usage, just the reservation.
 * The inode sent in is locked.
 */
पूर्णांक
xfs_trans_reserve_quota_nblks(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक64_t			dblocks,
	पूर्णांक64_t			rblocks,
	bool			क्रमce)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	अचिन्हित पूर्णांक		qflags = 0;
	पूर्णांक			error;

	अगर (!XFS_IS_QUOTA_RUNNING(mp) || !XFS_IS_QUOTA_ON(mp))
		वापस 0;

	ASSERT(!xfs_is_quota_inode(&mp->m_sb, ip->i_ino));
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	अगर (क्रमce)
		qflags |= XFS_QMOPT_FORCE_RES;

	/* Reserve data device quota against the inode's dquots. */
	error = xfs_trans_reserve_quota_bydquots(tp, mp, ip->i_udquot,
			ip->i_gdquot, ip->i_pdquot, dblocks, 0,
			XFS_QMOPT_RES_REGBLKS | qflags);
	अगर (error)
		वापस error;

	/* Do the same but क्रम realसमय blocks. */
	error = xfs_trans_reserve_quota_bydquots(tp, mp, ip->i_udquot,
			ip->i_gdquot, ip->i_pdquot, rblocks, 0,
			XFS_QMOPT_RES_RTBLKS | qflags);
	अगर (error) अणु
		xfs_trans_reserve_quota_bydquots(tp, mp, ip->i_udquot,
				ip->i_gdquot, ip->i_pdquot, -dblocks, 0,
				XFS_QMOPT_RES_REGBLKS);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/* Change the quota reservations क्रम an inode creation activity. */
पूर्णांक
xfs_trans_reserve_quota_icreate(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_dquot	*udqp,
	काष्ठा xfs_dquot	*gdqp,
	काष्ठा xfs_dquot	*pdqp,
	पूर्णांक64_t			dblocks)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;

	अगर (!XFS_IS_QUOTA_RUNNING(mp) || !XFS_IS_QUOTA_ON(mp))
		वापस 0;

	वापस xfs_trans_reserve_quota_bydquots(tp, mp, udqp, gdqp, pdqp,
			dblocks, 1, XFS_QMOPT_RES_REGBLKS);
पूर्ण

/*
 * This routine is called to allocate a quotaoff log item.
 */
काष्ठा xfs_qoff_logitem *
xfs_trans_get_qoff_item(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_qoff_logitem	*startqoff,
	uपूर्णांक			flags)
अणु
	काष्ठा xfs_qoff_logitem	*q;

	ASSERT(tp != शून्य);

	q = xfs_qm_qoff_logitem_init(tp->t_mountp, startqoff, flags);
	ASSERT(q != शून्य);

	/*
	 * Get a log_item_desc to poपूर्णांक at the new item.
	 */
	xfs_trans_add_item(tp, &q->qql_item);
	वापस q;
पूर्ण


/*
 * This is called to mark the quotaoff logitem as needing
 * to be logged when the transaction is committed.  The logitem must
 * alपढ़ोy be associated with the given transaction.
 */
व्योम
xfs_trans_log_quotaoff_item(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_qoff_logitem	*qlp)
अणु
	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &qlp->qql_item.li_flags);
पूर्ण

STATIC व्योम
xfs_trans_alloc_dqinfo(
	xfs_trans_t	*tp)
अणु
	tp->t_dqinfo = kmem_cache_zalloc(xfs_qm_dqtrxzone,
					 GFP_KERNEL | __GFP_NOFAIL);
पूर्ण

व्योम
xfs_trans_मुक्त_dqinfo(
	xfs_trans_t	*tp)
अणु
	अगर (!tp->t_dqinfo)
		वापस;
	kmem_cache_मुक्त(xfs_qm_dqtrxzone, tp->t_dqinfo);
	tp->t_dqinfo = शून्य;
पूर्ण
