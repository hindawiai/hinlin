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
#समावेश "xfs_bit.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_iwalk.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_util.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_qm.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_error.h"

/*
 * The global quota manager. There is only one of these क्रम the entire
 * प्रणाली, _not_ one per file प्रणाली. XQM keeps track of the overall
 * quota functionality, including मुख्यtaining the मुक्तlist and hash
 * tables of dquots.
 */
STATIC पूर्णांक	xfs_qm_init_quotainos(काष्ठा xfs_mount *mp);
STATIC पूर्णांक	xfs_qm_init_quotainfo(काष्ठा xfs_mount *mp);

STATIC व्योम	xfs_qm_destroy_quotainos(काष्ठा xfs_quotainfo *qi);
STATIC व्योम	xfs_qm_dqमुक्त_one(काष्ठा xfs_dquot *dqp);
/*
 * We use the batch lookup पूर्णांकerface to iterate over the dquots as it
 * currently is the only पूर्णांकerface पूर्णांकo the radix tree code that allows
 * fuzzy lookups instead of exact matches.  Holding the lock over multiple
 * operations is fine as all callers are used either during mount/umount
 * or quotaoff.
 */
#घोषणा XFS_DQ_LOOKUP_BATCH	32

STATIC पूर्णांक
xfs_qm_dquot_walk(
	काष्ठा xfs_mount	*mp,
	xfs_dqtype_t		type,
	पूर्णांक			(*execute)(काष्ठा xfs_dquot *dqp, व्योम *data),
	व्योम			*data)
अणु
	काष्ठा xfs_quotainfo	*qi = mp->m_quotainfo;
	काष्ठा radix_tree_root	*tree = xfs_dquot_tree(qi, type);
	uपूर्णांक32_t		next_index;
	पूर्णांक			last_error = 0;
	पूर्णांक			skipped;
	पूर्णांक			nr_found;

restart:
	skipped = 0;
	next_index = 0;
	nr_found = 0;

	जबतक (1) अणु
		काष्ठा xfs_dquot *batch[XFS_DQ_LOOKUP_BATCH];
		पूर्णांक		error = 0;
		पूर्णांक		i;

		mutex_lock(&qi->qi_tree_lock);
		nr_found = radix_tree_gang_lookup(tree, (व्योम **)batch,
					next_index, XFS_DQ_LOOKUP_BATCH);
		अगर (!nr_found) अणु
			mutex_unlock(&qi->qi_tree_lock);
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < nr_found; i++) अणु
			काष्ठा xfs_dquot *dqp = batch[i];

			next_index = dqp->q_id + 1;

			error = execute(batch[i], data);
			अगर (error == -EAGAIN) अणु
				skipped++;
				जारी;
			पूर्ण
			अगर (error && last_error != -EFSCORRUPTED)
				last_error = error;
		पूर्ण

		mutex_unlock(&qi->qi_tree_lock);

		/* bail out अगर the fileप्रणाली is corrupted.  */
		अगर (last_error == -EFSCORRUPTED) अणु
			skipped = 0;
			अवरोध;
		पूर्ण
		/* we're करोne अगर id overflows back to zero */
		अगर (!next_index)
			अवरोध;
	पूर्ण

	अगर (skipped) अणु
		delay(1);
		जाओ restart;
	पूर्ण

	वापस last_error;
पूर्ण


/*
 * Purge a dquot from all tracking data काष्ठाures and मुक्त it.
 */
STATIC पूर्णांक
xfs_qm_dqpurge(
	काष्ठा xfs_dquot	*dqp,
	व्योम			*data)
अणु
	काष्ठा xfs_mount	*mp = dqp->q_mount;
	काष्ठा xfs_quotainfo	*qi = mp->m_quotainfo;
	पूर्णांक			error = -EAGAIN;

	xfs_dqlock(dqp);
	अगर ((dqp->q_flags & XFS_DQFLAG_FREEING) || dqp->q_nrefs != 0)
		जाओ out_unlock;

	dqp->q_flags |= XFS_DQFLAG_FREEING;

	xfs_dqflock(dqp);

	/*
	 * If we are turning this type of quotas off, we करोn't care
	 * about the dirty metadata sitting in this dquot. OTOH, अगर
	 * we're unmounting, we करो care, so we flush it and रुको.
	 */
	अगर (XFS_DQ_IS_सूचीTY(dqp)) अणु
		काष्ठा xfs_buf	*bp = शून्य;

		/*
		 * We करोn't care about getting disk errors here. We need
		 * to purge this dquot anyway, so we go ahead regardless.
		 */
		error = xfs_qm_dqflush(dqp, &bp);
		अगर (!error) अणु
			error = xfs_bग_लिखो(bp);
			xfs_buf_rअन्यथा(bp);
		पूर्ण अन्यथा अगर (error == -EAGAIN) अणु
			dqp->q_flags &= ~XFS_DQFLAG_FREEING;
			जाओ out_unlock;
		पूर्ण
		xfs_dqflock(dqp);
	पूर्ण

	ASSERT(atomic_पढ़ो(&dqp->q_pincount) == 0);
	ASSERT(XFS_FORCED_SHUTDOWN(mp) ||
		!test_bit(XFS_LI_IN_AIL, &dqp->q_logitem.qli_item.li_flags));

	xfs_dqfunlock(dqp);
	xfs_dqunlock(dqp);

	radix_tree_delete(xfs_dquot_tree(qi, xfs_dquot_type(dqp)), dqp->q_id);
	qi->qi_dquots--;

	/*
	 * We move dquots to the मुक्तlist as soon as their reference count
	 * hits zero, so it really should be on the मुक्तlist here.
	 */
	ASSERT(!list_empty(&dqp->q_lru));
	list_lru_del(&qi->qi_lru, &dqp->q_lru);
	XFS_STATS_DEC(mp, xs_qm_dquot_unused);

	xfs_qm_dqdestroy(dqp);
	वापस 0;

out_unlock:
	xfs_dqunlock(dqp);
	वापस error;
पूर्ण

/*
 * Purge the dquot cache.
 */
व्योम
xfs_qm_dqpurge_all(
	काष्ठा xfs_mount	*mp,
	uपूर्णांक			flags)
अणु
	अगर (flags & XFS_QMOPT_UQUOTA)
		xfs_qm_dquot_walk(mp, XFS_DQTYPE_USER, xfs_qm_dqpurge, शून्य);
	अगर (flags & XFS_QMOPT_GQUOTA)
		xfs_qm_dquot_walk(mp, XFS_DQTYPE_GROUP, xfs_qm_dqpurge, शून्य);
	अगर (flags & XFS_QMOPT_PQUOTA)
		xfs_qm_dquot_walk(mp, XFS_DQTYPE_PROJ, xfs_qm_dqpurge, शून्य);
पूर्ण

/*
 * Just destroy the quotainfo काष्ठाure.
 */
व्योम
xfs_qm_unmount(
	काष्ठा xfs_mount	*mp)
अणु
	अगर (mp->m_quotainfo) अणु
		xfs_qm_dqpurge_all(mp, XFS_QMOPT_QUOTALL);
		xfs_qm_destroy_quotainfo(mp);
	पूर्ण
पूर्ण

/*
 * Called from the vfsops layer.
 */
व्योम
xfs_qm_unmount_quotas(
	xfs_mount_t	*mp)
अणु
	/*
	 * Release the dquots that root inode, et al might be holding,
	 * beक्रमe we flush quotas and blow away the quotainfo काष्ठाure.
	 */
	ASSERT(mp->m_rootip);
	xfs_qm_dqdetach(mp->m_rootip);
	अगर (mp->m_rbmip)
		xfs_qm_dqdetach(mp->m_rbmip);
	अगर (mp->m_rsumip)
		xfs_qm_dqdetach(mp->m_rsumip);

	/*
	 * Release the quota inodes.
	 */
	अगर (mp->m_quotainfo) अणु
		अगर (mp->m_quotainfo->qi_uquotaip) अणु
			xfs_irele(mp->m_quotainfo->qi_uquotaip);
			mp->m_quotainfo->qi_uquotaip = शून्य;
		पूर्ण
		अगर (mp->m_quotainfo->qi_gquotaip) अणु
			xfs_irele(mp->m_quotainfo->qi_gquotaip);
			mp->m_quotainfo->qi_gquotaip = शून्य;
		पूर्ण
		अगर (mp->m_quotainfo->qi_pquotaip) अणु
			xfs_irele(mp->m_quotainfo->qi_pquotaip);
			mp->m_quotainfo->qi_pquotaip = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

STATIC पूर्णांक
xfs_qm_dqattach_one(
	काष्ठा xfs_inode	*ip,
	xfs_dqtype_t		type,
	bool			करोalloc,
	काष्ठा xfs_dquot	**IO_idqpp)
अणु
	काष्ठा xfs_dquot	*dqp;
	पूर्णांक			error;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	error = 0;

	/*
	 * See अगर we alपढ़ोy have it in the inode itself. IO_idqpp is &i_udquot
	 * or &i_gdquot. This made the code look weird, but made the logic a lot
	 * simpler.
	 */
	dqp = *IO_idqpp;
	अगर (dqp) अणु
		trace_xfs_dqattach_found(dqp);
		वापस 0;
	पूर्ण

	/*
	 * Find the dquot from somewhere. This bumps the reference count of
	 * dquot and वापसs it locked.  This can वापस ENOENT अगर dquot didn't
	 * exist on disk and we didn't ask it to allocate; ESRCH अगर quotas got
	 * turned off suddenly.
	 */
	error = xfs_qm_dqget_inode(ip, type, करोalloc, &dqp);
	अगर (error)
		वापस error;

	trace_xfs_dqattach_get(dqp);

	/*
	 * dqget may have dropped and re-acquired the ilock, but it guarantees
	 * that the dquot वापसed is the one that should go in the inode.
	 */
	*IO_idqpp = dqp;
	xfs_dqunlock(dqp);
	वापस 0;
पूर्ण

अटल bool
xfs_qm_need_dqattach(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;

	अगर (!XFS_IS_QUOTA_RUNNING(mp))
		वापस false;
	अगर (!XFS_IS_QUOTA_ON(mp))
		वापस false;
	अगर (!XFS_NOT_DQATTACHED(mp, ip))
		वापस false;
	अगर (xfs_is_quota_inode(&mp->m_sb, ip->i_ino))
		वापस false;
	वापस true;
पूर्ण

/*
 * Given a locked inode, attach dquot(s) to it, taking U/G/P-QUOTAON
 * पूर्णांकo account.
 * If @करोalloc is true, the dquot(s) will be allocated अगर needed.
 * Inode may get unlocked and relocked in here, and the caller must deal with
 * the consequences.
 */
पूर्णांक
xfs_qm_dqattach_locked(
	xfs_inode_t	*ip,
	bool		करोalloc)
अणु
	xfs_mount_t	*mp = ip->i_mount;
	पूर्णांक		error = 0;

	अगर (!xfs_qm_need_dqattach(ip))
		वापस 0;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	अगर (XFS_IS_UQUOTA_ON(mp) && !ip->i_udquot) अणु
		error = xfs_qm_dqattach_one(ip, XFS_DQTYPE_USER,
				करोalloc, &ip->i_udquot);
		अगर (error)
			जाओ करोne;
		ASSERT(ip->i_udquot);
	पूर्ण

	अगर (XFS_IS_GQUOTA_ON(mp) && !ip->i_gdquot) अणु
		error = xfs_qm_dqattach_one(ip, XFS_DQTYPE_GROUP,
				करोalloc, &ip->i_gdquot);
		अगर (error)
			जाओ करोne;
		ASSERT(ip->i_gdquot);
	पूर्ण

	अगर (XFS_IS_PQUOTA_ON(mp) && !ip->i_pdquot) अणु
		error = xfs_qm_dqattach_one(ip, XFS_DQTYPE_PROJ,
				करोalloc, &ip->i_pdquot);
		अगर (error)
			जाओ करोne;
		ASSERT(ip->i_pdquot);
	पूर्ण

करोne:
	/*
	 * Don't worry about the dquots that we may have attached beक्रमe any
	 * error - they'll get detached later अगर it has not alपढ़ोy been करोne.
	 */
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	वापस error;
पूर्ण

पूर्णांक
xfs_qm_dqattach(
	काष्ठा xfs_inode	*ip)
अणु
	पूर्णांक			error;

	अगर (!xfs_qm_need_dqattach(ip))
		वापस 0;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	error = xfs_qm_dqattach_locked(ip, false);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);

	वापस error;
पूर्ण

/*
 * Release dquots (and their references) अगर any.
 * The inode should be locked EXCL except when this's called by
 * xfs_ireclaim.
 */
व्योम
xfs_qm_dqdetach(
	xfs_inode_t	*ip)
अणु
	अगर (!(ip->i_udquot || ip->i_gdquot || ip->i_pdquot))
		वापस;

	trace_xfs_dquot_dqdetach(ip);

	ASSERT(!xfs_is_quota_inode(&ip->i_mount->m_sb, ip->i_ino));
	अगर (ip->i_udquot) अणु
		xfs_qm_dqrele(ip->i_udquot);
		ip->i_udquot = शून्य;
	पूर्ण
	अगर (ip->i_gdquot) अणु
		xfs_qm_dqrele(ip->i_gdquot);
		ip->i_gdquot = शून्य;
	पूर्ण
	अगर (ip->i_pdquot) अणु
		xfs_qm_dqrele(ip->i_pdquot);
		ip->i_pdquot = शून्य;
	पूर्ण
पूर्ण

काष्ठा xfs_qm_isolate अणु
	काष्ठा list_head	buffers;
	काष्ठा list_head	dispose;
पूर्ण;

अटल क्रमागत lru_status
xfs_qm_dquot_isolate(
	काष्ठा list_head	*item,
	काष्ठा list_lru_one	*lru,
	spinlock_t		*lru_lock,
	व्योम			*arg)
		__releases(lru_lock) __acquires(lru_lock)
अणु
	काष्ठा xfs_dquot	*dqp = container_of(item,
						काष्ठा xfs_dquot, q_lru);
	काष्ठा xfs_qm_isolate	*isol = arg;

	अगर (!xfs_dqlock_noरुको(dqp))
		जाओ out_miss_busy;

	/*
	 * This dquot has acquired a reference in the meanसमय हटाओ it from
	 * the मुक्तlist and try again.
	 */
	अगर (dqp->q_nrefs) अणु
		xfs_dqunlock(dqp);
		XFS_STATS_INC(dqp->q_mount, xs_qm_dqwants);

		trace_xfs_dqreclaim_want(dqp);
		list_lru_isolate(lru, &dqp->q_lru);
		XFS_STATS_DEC(dqp->q_mount, xs_qm_dquot_unused);
		वापस LRU_REMOVED;
	पूर्ण

	/*
	 * If the dquot is dirty, flush it. If it's alपढ़ोy being flushed, just
	 * skip it so there is समय क्रम the IO to complete beक्रमe we try to
	 * reclaim it again on the next LRU pass.
	 */
	अगर (!xfs_dqflock_noरुको(dqp)) अणु
		xfs_dqunlock(dqp);
		जाओ out_miss_busy;
	पूर्ण

	अगर (XFS_DQ_IS_सूचीTY(dqp)) अणु
		काष्ठा xfs_buf	*bp = शून्य;
		पूर्णांक		error;

		trace_xfs_dqreclaim_dirty(dqp);

		/* we have to drop the LRU lock to flush the dquot */
		spin_unlock(lru_lock);

		error = xfs_qm_dqflush(dqp, &bp);
		अगर (error)
			जाओ out_unlock_dirty;

		xfs_buf_delwri_queue(bp, &isol->buffers);
		xfs_buf_rअन्यथा(bp);
		जाओ out_unlock_dirty;
	पूर्ण
	xfs_dqfunlock(dqp);

	/*
	 * Prevent lookups now that we are past the poपूर्णांक of no वापस.
	 */
	dqp->q_flags |= XFS_DQFLAG_FREEING;
	xfs_dqunlock(dqp);

	ASSERT(dqp->q_nrefs == 0);
	list_lru_isolate_move(lru, &dqp->q_lru, &isol->dispose);
	XFS_STATS_DEC(dqp->q_mount, xs_qm_dquot_unused);
	trace_xfs_dqreclaim_करोne(dqp);
	XFS_STATS_INC(dqp->q_mount, xs_qm_dqreclaims);
	वापस LRU_REMOVED;

out_miss_busy:
	trace_xfs_dqreclaim_busy(dqp);
	XFS_STATS_INC(dqp->q_mount, xs_qm_dqreclaim_misses);
	वापस LRU_SKIP;

out_unlock_dirty:
	trace_xfs_dqreclaim_busy(dqp);
	XFS_STATS_INC(dqp->q_mount, xs_qm_dqreclaim_misses);
	xfs_dqunlock(dqp);
	spin_lock(lru_lock);
	वापस LRU_RETRY;
पूर्ण

अटल अचिन्हित दीर्घ
xfs_qm_shrink_scan(
	काष्ठा shrinker		*shrink,
	काष्ठा shrink_control	*sc)
अणु
	काष्ठा xfs_quotainfo	*qi = container_of(shrink,
					काष्ठा xfs_quotainfo, qi_shrinker);
	काष्ठा xfs_qm_isolate	isol;
	अचिन्हित दीर्घ		मुक्तd;
	पूर्णांक			error;

	अगर ((sc->gfp_mask & (__GFP_FS|__GFP_सूचीECT_RECLAIM)) != (__GFP_FS|__GFP_सूचीECT_RECLAIM))
		वापस 0;

	INIT_LIST_HEAD(&isol.buffers);
	INIT_LIST_HEAD(&isol.dispose);

	मुक्तd = list_lru_shrink_walk(&qi->qi_lru, sc,
				     xfs_qm_dquot_isolate, &isol);

	error = xfs_buf_delwri_submit(&isol.buffers);
	अगर (error)
		xfs_warn(शून्य, "%s: dquot reclaim failed", __func__);

	जबतक (!list_empty(&isol.dispose)) अणु
		काष्ठा xfs_dquot	*dqp;

		dqp = list_first_entry(&isol.dispose, काष्ठा xfs_dquot, q_lru);
		list_del_init(&dqp->q_lru);
		xfs_qm_dqमुक्त_one(dqp);
	पूर्ण

	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ
xfs_qm_shrink_count(
	काष्ठा shrinker		*shrink,
	काष्ठा shrink_control	*sc)
अणु
	काष्ठा xfs_quotainfo	*qi = container_of(shrink,
					काष्ठा xfs_quotainfo, qi_shrinker);

	वापस list_lru_shrink_count(&qi->qi_lru, sc);
पूर्ण

STATIC व्योम
xfs_qm_set_defquota(
	काष्ठा xfs_mount	*mp,
	xfs_dqtype_t		type,
	काष्ठा xfs_quotainfo	*qinf)
अणु
	काष्ठा xfs_dquot	*dqp;
	काष्ठा xfs_def_quota	*defq;
	पूर्णांक			error;

	error = xfs_qm_dqget_uncached(mp, 0, type, &dqp);
	अगर (error)
		वापस;

	defq = xfs_get_defquota(qinf, xfs_dquot_type(dqp));

	/*
	 * Timers and warnings have been alपढ़ोy set, let's just set the
	 * शेष limits क्रम this quota type
	 */
	defq->blk.hard = dqp->q_blk.hardlimit;
	defq->blk.soft = dqp->q_blk.softlimit;
	defq->ino.hard = dqp->q_ino.hardlimit;
	defq->ino.soft = dqp->q_ino.softlimit;
	defq->rtb.hard = dqp->q_rtb.hardlimit;
	defq->rtb.soft = dqp->q_rtb.softlimit;
	xfs_qm_dqdestroy(dqp);
पूर्ण

/* Initialize quota समय limits from the root dquot. */
अटल व्योम
xfs_qm_init_समयlimits(
	काष्ठा xfs_mount	*mp,
	xfs_dqtype_t		type)
अणु
	काष्ठा xfs_quotainfo	*qinf = mp->m_quotainfo;
	काष्ठा xfs_def_quota	*defq;
	काष्ठा xfs_dquot	*dqp;
	पूर्णांक			error;

	defq = xfs_get_defquota(qinf, type);

	defq->blk.समय = XFS_QM_BTIMELIMIT;
	defq->ino.समय = XFS_QM_ITIMELIMIT;
	defq->rtb.समय = XFS_QM_RTBTIMELIMIT;
	defq->blk.warn = XFS_QM_BWARNLIMIT;
	defq->ino.warn = XFS_QM_IWARNLIMIT;
	defq->rtb.warn = XFS_QM_RTBWARNLIMIT;

	/*
	 * We try to get the limits from the superuser's limits fields.
	 * This is quite hacky, but it is standard quota practice.
	 *
	 * Since we may not have करोne a quotacheck by this poपूर्णांक, just पढ़ो
	 * the dquot without attaching it to any hashtables or lists.
	 */
	error = xfs_qm_dqget_uncached(mp, 0, type, &dqp);
	अगर (error)
		वापस;

	/*
	 * The warnings and समयrs set the grace period given to
	 * a user or group beक्रमe he or she can not perक्रमm any
	 * more writing. If it is zero, a शेष is used.
	 */
	अगर (dqp->q_blk.समयr)
		defq->blk.समय = dqp->q_blk.समयr;
	अगर (dqp->q_ino.समयr)
		defq->ino.समय = dqp->q_ino.समयr;
	अगर (dqp->q_rtb.समयr)
		defq->rtb.समय = dqp->q_rtb.समयr;
	अगर (dqp->q_blk.warnings)
		defq->blk.warn = dqp->q_blk.warnings;
	अगर (dqp->q_ino.warnings)
		defq->ino.warn = dqp->q_ino.warnings;
	अगर (dqp->q_rtb.warnings)
		defq->rtb.warn = dqp->q_rtb.warnings;

	xfs_qm_dqdestroy(dqp);
पूर्ण

/*
 * This initializes all the quota inक्रमmation that's kept in the
 * mount काष्ठाure
 */
STATIC पूर्णांक
xfs_qm_init_quotainfo(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_quotainfo	*qinf;
	पूर्णांक			error;

	ASSERT(XFS_IS_QUOTA_RUNNING(mp));

	qinf = mp->m_quotainfo = kmem_zalloc(माप(काष्ठा xfs_quotainfo), 0);

	error = list_lru_init(&qinf->qi_lru);
	अगर (error)
		जाओ out_मुक्त_qinf;

	/*
	 * See अगर quotainodes are setup, and अगर not, allocate them,
	 * and change the superblock accordingly.
	 */
	error = xfs_qm_init_quotainos(mp);
	अगर (error)
		जाओ out_मुक्त_lru;

	INIT_RADIX_TREE(&qinf->qi_uquota_tree, GFP_NOFS);
	INIT_RADIX_TREE(&qinf->qi_gquota_tree, GFP_NOFS);
	INIT_RADIX_TREE(&qinf->qi_pquota_tree, GFP_NOFS);
	mutex_init(&qinf->qi_tree_lock);

	/* mutex used to serialize quotaoffs */
	mutex_init(&qinf->qi_quotaofflock);

	/* Precalc some स्थिरants */
	qinf->qi_dqchunklen = XFS_FSB_TO_BB(mp, XFS_DQUOT_CLUSTER_SIZE_FSB);
	qinf->qi_dqperchunk = xfs_calc_dquots_per_chunk(qinf->qi_dqchunklen);
	अगर (xfs_sb_version_hasbigसमय(&mp->m_sb)) अणु
		qinf->qi_expiry_min =
			xfs_dq_bigसमय_प्रकारo_unix(XFS_DQ_BIGTIME_EXPIRY_MIN);
		qinf->qi_expiry_max =
			xfs_dq_bigसमय_प्रकारo_unix(XFS_DQ_BIGTIME_EXPIRY_MAX);
	पूर्ण अन्यथा अणु
		qinf->qi_expiry_min = XFS_DQ_LEGACY_EXPIRY_MIN;
		qinf->qi_expiry_max = XFS_DQ_LEGACY_EXPIRY_MAX;
	पूर्ण
	trace_xfs_quota_expiry_range(mp, qinf->qi_expiry_min,
			qinf->qi_expiry_max);

	mp->m_qflags |= (mp->m_sb.sb_qflags & XFS_ALL_QUOTA_CHKD);

	xfs_qm_init_समयlimits(mp, XFS_DQTYPE_USER);
	xfs_qm_init_समयlimits(mp, XFS_DQTYPE_GROUP);
	xfs_qm_init_समयlimits(mp, XFS_DQTYPE_PROJ);

	अगर (XFS_IS_UQUOTA_RUNNING(mp))
		xfs_qm_set_defquota(mp, XFS_DQTYPE_USER, qinf);
	अगर (XFS_IS_GQUOTA_RUNNING(mp))
		xfs_qm_set_defquota(mp, XFS_DQTYPE_GROUP, qinf);
	अगर (XFS_IS_PQUOTA_RUNNING(mp))
		xfs_qm_set_defquota(mp, XFS_DQTYPE_PROJ, qinf);

	qinf->qi_shrinker.count_objects = xfs_qm_shrink_count;
	qinf->qi_shrinker.scan_objects = xfs_qm_shrink_scan;
	qinf->qi_shrinker.seeks = DEFAULT_SEEKS;
	qinf->qi_shrinker.flags = SHRINKER_NUMA_AWARE;

	error = रेजिस्टर_shrinker(&qinf->qi_shrinker);
	अगर (error)
		जाओ out_मुक्त_inos;

	वापस 0;

out_मुक्त_inos:
	mutex_destroy(&qinf->qi_quotaofflock);
	mutex_destroy(&qinf->qi_tree_lock);
	xfs_qm_destroy_quotainos(qinf);
out_मुक्त_lru:
	list_lru_destroy(&qinf->qi_lru);
out_मुक्त_qinf:
	kmem_मुक्त(qinf);
	mp->m_quotainfo = शून्य;
	वापस error;
पूर्ण

/*
 * Gets called when unmounting a fileप्रणाली or when all quotas get
 * turned off.
 * This purges the quota inodes, destroys locks and मुक्तs itself.
 */
व्योम
xfs_qm_destroy_quotainfo(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_quotainfo	*qi;

	qi = mp->m_quotainfo;
	ASSERT(qi != शून्य);

	unरेजिस्टर_shrinker(&qi->qi_shrinker);
	list_lru_destroy(&qi->qi_lru);
	xfs_qm_destroy_quotainos(qi);
	mutex_destroy(&qi->qi_tree_lock);
	mutex_destroy(&qi->qi_quotaofflock);
	kmem_मुक्त(qi);
	mp->m_quotainfo = शून्य;
पूर्ण

/*
 * Create an inode and वापस with a reference alपढ़ोy taken, but unlocked
 * This is how we create quota inodes
 */
STATIC पूर्णांक
xfs_qm_qino_alloc(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_inode	**ipp,
	अचिन्हित पूर्णांक		flags)
अणु
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;
	bool			need_alloc = true;

	*ipp = शून्य;
	/*
	 * With superblock that करोesn't have separate pquotino, we
	 * share an inode between gquota and pquota. If the on-disk
	 * superblock has GQUOTA and the fileप्रणाली is now mounted
	 * with PQUOTA, just use sb_gquotino क्रम sb_pquotino and
	 * vice-versa.
	 */
	अगर (!xfs_sb_version_has_pquotino(&mp->m_sb) &&
			(flags & (XFS_QMOPT_PQUOTA|XFS_QMOPT_GQUOTA))) अणु
		xfs_ino_t ino = शून्यFSINO;

		अगर ((flags & XFS_QMOPT_PQUOTA) &&
			     (mp->m_sb.sb_gquotino != शून्यFSINO)) अणु
			ino = mp->m_sb.sb_gquotino;
			अगर (XFS_IS_CORRUPT(mp,
					   mp->m_sb.sb_pquotino != शून्यFSINO))
				वापस -EFSCORRUPTED;
		पूर्ण अन्यथा अगर ((flags & XFS_QMOPT_GQUOTA) &&
			     (mp->m_sb.sb_pquotino != शून्यFSINO)) अणु
			ino = mp->m_sb.sb_pquotino;
			अगर (XFS_IS_CORRUPT(mp,
					   mp->m_sb.sb_gquotino != शून्यFSINO))
				वापस -EFSCORRUPTED;
		पूर्ण
		अगर (ino != शून्यFSINO) अणु
			error = xfs_iget(mp, शून्य, ino, 0, 0, ipp);
			अगर (error)
				वापस error;
			mp->m_sb.sb_gquotino = शून्यFSINO;
			mp->m_sb.sb_pquotino = शून्यFSINO;
			need_alloc = false;
		पूर्ण
	पूर्ण

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_create,
			need_alloc ? XFS_QM_QINOCREATE_SPACE_RES(mp) : 0,
			0, 0, &tp);
	अगर (error)
		वापस error;

	अगर (need_alloc) अणु
		error = xfs_dir_ialloc(&init_user_ns, &tp, शून्य, S_IFREG, 1, 0,
				       0, false, ipp);
		अगर (error) अणु
			xfs_trans_cancel(tp);
			वापस error;
		पूर्ण
	पूर्ण

	/*
	 * Make the changes in the superblock, and log those too.
	 * sbfields arg may contain fields other than *QUOTINO;
	 * VERSIONNUM क्रम example.
	 */
	spin_lock(&mp->m_sb_lock);
	अगर (flags & XFS_QMOPT_SBVERSION) अणु
		ASSERT(!xfs_sb_version_hasquota(&mp->m_sb));

		xfs_sb_version_addquota(&mp->m_sb);
		mp->m_sb.sb_uquotino = शून्यFSINO;
		mp->m_sb.sb_gquotino = शून्यFSINO;
		mp->m_sb.sb_pquotino = शून्यFSINO;

		/* qflags will get updated fully _after_ quotacheck */
		mp->m_sb.sb_qflags = mp->m_qflags & XFS_ALL_QUOTA_ACCT;
	पूर्ण
	अगर (flags & XFS_QMOPT_UQUOTA)
		mp->m_sb.sb_uquotino = (*ipp)->i_ino;
	अन्यथा अगर (flags & XFS_QMOPT_GQUOTA)
		mp->m_sb.sb_gquotino = (*ipp)->i_ino;
	अन्यथा
		mp->m_sb.sb_pquotino = (*ipp)->i_ino;
	spin_unlock(&mp->m_sb_lock);
	xfs_log_sb(tp);

	error = xfs_trans_commit(tp);
	अगर (error) अणु
		ASSERT(XFS_FORCED_SHUTDOWN(mp));
		xfs_alert(mp, "%s failed (error %d)!", __func__, error);
	पूर्ण
	अगर (need_alloc)
		xfs_finish_inode_setup(*ipp);
	वापस error;
पूर्ण


STATIC व्योम
xfs_qm_reset_dqcounts(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type)
अणु
	काष्ठा xfs_dqblk	*dqb;
	पूर्णांक			j;

	trace_xfs_reset_dqcounts(bp, _RET_IP_);

	/*
	 * Reset all counters and समयrs. They'll be
	 * started afresh by xfs_qm_quotacheck.
	 */
#अगर_घोषित DEBUG
	j = (पूर्णांक)XFS_FSB_TO_B(mp, XFS_DQUOT_CLUSTER_SIZE_FSB) /
		माप(xfs_dqblk_t);
	ASSERT(mp->m_quotainfo->qi_dqperchunk == j);
#पूर्ण_अगर
	dqb = bp->b_addr;
	क्रम (j = 0; j < mp->m_quotainfo->qi_dqperchunk; j++) अणु
		काष्ठा xfs_disk_dquot	*ddq;

		ddq = (काष्ठा xfs_disk_dquot *)&dqb[j];

		/*
		 * Do a sanity check, and अगर needed, repair the dqblk. Don't
		 * output any warnings because it's perfectly possible to
		 * find uninitialised dquot blks. See comment in
		 * xfs_dquot_verअगरy.
		 */
		अगर (xfs_dqblk_verअगरy(mp, &dqb[j], id + j) ||
		    (dqb[j].dd_diskdq.d_type & XFS_DQTYPE_REC_MASK) != type)
			xfs_dqblk_repair(mp, &dqb[j], id + j, type);

		/*
		 * Reset type in हाल we are reusing group quota file क्रम
		 * project quotas or vice versa
		 */
		ddq->d_type = type;
		ddq->d_bcount = 0;
		ddq->d_icount = 0;
		ddq->d_rtbcount = 0;

		/*
		 * dquot id 0 stores the शेष grace period and the maximum
		 * warning limit that were set by the administrator, so we
		 * should not reset them.
		 */
		अगर (ddq->d_id != 0) अणु
			ddq->d_bसमयr = 0;
			ddq->d_iसमयr = 0;
			ddq->d_rtbसमयr = 0;
			ddq->d_bwarns = 0;
			ddq->d_iwarns = 0;
			ddq->d_rtbwarns = 0;
			अगर (xfs_sb_version_hasbigसमय(&mp->m_sb))
				ddq->d_type |= XFS_DQTYPE_BIGTIME;
		पूर्ण

		अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
			xfs_update_cksum((अक्षर *)&dqb[j],
					 माप(काष्ठा xfs_dqblk),
					 XFS_DQUOT_CRC_OFF);
		पूर्ण
	पूर्ण
पूर्ण

STATIC पूर्णांक
xfs_qm_reset_dqcounts_all(
	काष्ठा xfs_mount	*mp,
	xfs_dqid_t		firstid,
	xfs_fsblock_t		bno,
	xfs_filblks_t		blkcnt,
	xfs_dqtype_t		type,
	काष्ठा list_head	*buffer_list)
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error = 0;

	ASSERT(blkcnt > 0);

	/*
	 * Blkcnt arg can be a very big number, and might even be
	 * larger than the log itself. So, we have to अवरोध it up पूर्णांकo
	 * manageable-sized transactions.
	 * Note that we करोn't start a permanent transaction here; we might
	 * not be able to get a log reservation क्रम the whole thing up front,
	 * and we करोn't really care to either, because we just discard
	 * everything अगर we were to crash in the middle of this loop.
	 */
	जबतक (blkcnt--) अणु
		error = xfs_trans_पढ़ो_buf(mp, शून्य, mp->m_ddev_targp,
			      XFS_FSB_TO_DADDR(mp, bno),
			      mp->m_quotainfo->qi_dqchunklen, 0, &bp,
			      &xfs_dquot_buf_ops);

		/*
		 * CRC and validation errors will वापस a EFSCORRUPTED here. If
		 * this occurs, re-पढ़ो without CRC validation so that we can
		 * repair the damage via xfs_qm_reset_dqcounts(). This process
		 * will leave a trace in the log indicating corruption has
		 * been detected.
		 */
		अगर (error == -EFSCORRUPTED) अणु
			error = xfs_trans_पढ़ो_buf(mp, शून्य, mp->m_ddev_targp,
				      XFS_FSB_TO_DADDR(mp, bno),
				      mp->m_quotainfo->qi_dqchunklen, 0, &bp,
				      शून्य);
		पूर्ण

		अगर (error)
			अवरोध;

		/*
		 * A corrupt buffer might not have a verअगरier attached, so
		 * make sure we have the correct one attached beक्रमe ग_लिखोback
		 * occurs.
		 */
		bp->b_ops = &xfs_dquot_buf_ops;
		xfs_qm_reset_dqcounts(mp, bp, firstid, type);
		xfs_buf_delwri_queue(bp, buffer_list);
		xfs_buf_rअन्यथा(bp);

		/* जाओ the next block. */
		bno++;
		firstid += mp->m_quotainfo->qi_dqperchunk;
	पूर्ण

	वापस error;
पूर्ण

/*
 * Iterate over all allocated dquot blocks in this quota inode, zeroing all
 * counters क्रम every chunk of dquots that we find.
 */
STATIC पूर्णांक
xfs_qm_reset_dqcounts_buf(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_inode	*qip,
	xfs_dqtype_t		type,
	काष्ठा list_head	*buffer_list)
अणु
	काष्ठा xfs_bmbt_irec	*map;
	पूर्णांक			i, nmaps;	/* number of map entries */
	पूर्णांक			error;		/* वापस value */
	xfs_fileoff_t		lblkno;
	xfs_filblks_t		maxlblkcnt;
	xfs_dqid_t		firstid;
	xfs_fsblock_t		rablkno;
	xfs_filblks_t		rablkcnt;

	error = 0;
	/*
	 * This looks racy, but we can't keep an inode lock across a
	 * trans_reserve. But, this माला_लो called during quotacheck, and that
	 * happens only at mount समय which is single thपढ़ोed.
	 */
	अगर (qip->i_nblocks == 0)
		वापस 0;

	map = kmem_alloc(XFS_DQITER_MAP_SIZE * माप(*map), 0);

	lblkno = 0;
	maxlblkcnt = XFS_B_TO_FSB(mp, mp->m_super->s_maxbytes);
	करो अणु
		uपूर्णांक		lock_mode;

		nmaps = XFS_DQITER_MAP_SIZE;
		/*
		 * We aren't changing the inode itself. Just changing
		 * some of its data. No new blocks are added here, and
		 * the inode is never added to the transaction.
		 */
		lock_mode = xfs_ilock_data_map_shared(qip);
		error = xfs_bmapi_पढ़ो(qip, lblkno, maxlblkcnt - lblkno,
				       map, &nmaps, 0);
		xfs_iunlock(qip, lock_mode);
		अगर (error)
			अवरोध;

		ASSERT(nmaps <= XFS_DQITER_MAP_SIZE);
		क्रम (i = 0; i < nmaps; i++) अणु
			ASSERT(map[i].br_startblock != DELAYSTARTBLOCK);
			ASSERT(map[i].br_blockcount);


			lblkno += map[i].br_blockcount;

			अगर (map[i].br_startblock == HOLESTARTBLOCK)
				जारी;

			firstid = (xfs_dqid_t) map[i].br_startoff *
				mp->m_quotainfo->qi_dqperchunk;
			/*
			 * Do a पढ़ो-ahead on the next extent.
			 */
			अगर ((i+1 < nmaps) &&
			    (map[i+1].br_startblock != HOLESTARTBLOCK)) अणु
				rablkcnt =  map[i+1].br_blockcount;
				rablkno = map[i+1].br_startblock;
				जबतक (rablkcnt--) अणु
					xfs_buf_पढ़ोahead(mp->m_ddev_targp,
					       XFS_FSB_TO_DADDR(mp, rablkno),
					       mp->m_quotainfo->qi_dqchunklen,
					       &xfs_dquot_buf_ops);
					rablkno++;
				पूर्ण
			पूर्ण
			/*
			 * Iterate thru all the blks in the extent and
			 * reset the counters of all the dquots inside them.
			 */
			error = xfs_qm_reset_dqcounts_all(mp, firstid,
						   map[i].br_startblock,
						   map[i].br_blockcount,
						   type, buffer_list);
			अगर (error)
				जाओ out;
		पूर्ण
	पूर्ण जबतक (nmaps > 0);

out:
	kmem_मुक्त(map);
	वापस error;
पूर्ण

/*
 * Called by dqusage_adjust in करोing a quotacheck.
 *
 * Given the inode, and a dquot id this updates both the incore dqout as well
 * as the buffer copy. This is so that once the quotacheck is करोne, we can
 * just log all the buffers, as opposed to logging numerous updates to
 * inभागidual dquots.
 */
STATIC पूर्णांक
xfs_qm_quotacheck_dqadjust(
	काष्ठा xfs_inode	*ip,
	xfs_dqtype_t		type,
	xfs_qcnt_t		nblks,
	xfs_qcnt_t		rtblks)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_dquot	*dqp;
	xfs_dqid_t		id;
	पूर्णांक			error;

	id = xfs_qm_id_क्रम_quotatype(ip, type);
	error = xfs_qm_dqget(mp, id, type, true, &dqp);
	अगर (error) अणु
		/*
		 * Shouldn't be able to turn off quotas here.
		 */
		ASSERT(error != -ESRCH);
		ASSERT(error != -ENOENT);
		वापस error;
	पूर्ण

	trace_xfs_dqadjust(dqp);

	/*
	 * Adjust the inode count and the block count to reflect this inode's
	 * resource usage.
	 */
	dqp->q_ino.count++;
	dqp->q_ino.reserved++;
	अगर (nblks) अणु
		dqp->q_blk.count += nblks;
		dqp->q_blk.reserved += nblks;
	पूर्ण
	अगर (rtblks) अणु
		dqp->q_rtb.count += rtblks;
		dqp->q_rtb.reserved += rtblks;
	पूर्ण

	/*
	 * Set शेष limits, adjust समयrs (since we changed usages)
	 *
	 * There are no समयrs क्रम the शेष values set in the root dquot.
	 */
	अगर (dqp->q_id) अणु
		xfs_qm_adjust_dqlimits(dqp);
		xfs_qm_adjust_dqसमयrs(dqp);
	पूर्ण

	dqp->q_flags |= XFS_DQFLAG_सूचीTY;
	xfs_qm_dqput(dqp);
	वापस 0;
पूर्ण

/*
 * callback routine supplied to bulkstat(). Given an inumber, find its
 * dquots and update them to account क्रम resources taken by that inode.
 */
/* ARGSUSED */
STATIC पूर्णांक
xfs_qm_dqusage_adjust(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_ino_t		ino,
	व्योम			*data)
अणु
	काष्ठा xfs_inode	*ip;
	xfs_qcnt_t		nblks;
	xfs_filblks_t		rtblks = 0;	/* total rt blks */
	पूर्णांक			error;

	ASSERT(XFS_IS_QUOTA_RUNNING(mp));

	/*
	 * rootino must have its resources accounted क्रम, not so with the quota
	 * inodes.
	 */
	अगर (xfs_is_quota_inode(&mp->m_sb, ino))
		वापस 0;

	/*
	 * We करोn't _need_ to take the ilock EXCL here because quotacheck runs
	 * at mount समय and thereक्रमe nobody will be racing chown/chproj.
	 */
	error = xfs_iget(mp, tp, ino, XFS_IGET_DONTCACHE, 0, &ip);
	अगर (error == -EINVAL || error == -ENOENT)
		वापस 0;
	अगर (error)
		वापस error;

	ASSERT(ip->i_delayed_blks == 0);

	अगर (XFS_IS_REALTIME_INODE(ip)) अणु
		काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, XFS_DATA_FORK);

		error = xfs_iपढ़ो_extents(tp, ip, XFS_DATA_FORK);
		अगर (error)
			जाओ error0;

		xfs_bmap_count_leaves(अगरp, &rtblks);
	पूर्ण

	nblks = (xfs_qcnt_t)ip->i_nblocks - rtblks;

	/*
	 * Add the (disk blocks and inode) resources occupied by this
	 * inode to its dquots. We करो this adjusपंचांगent in the incore dquot,
	 * and also copy the changes to its buffer.
	 * We करोn't care about putting these changes in a transaction
	 * envelope because अगर we crash in the middle of a 'quotacheck'
	 * we have to start from the beginning anyway.
	 * Once we're done, we'll log all the dquot bufs.
	 *
	 * The *QUOTA_ON checks below may look pretty racy, but quotachecks
	 * and quotaoffs करोn't race. (Quotachecks happen at mount समय only).
	 */
	अगर (XFS_IS_UQUOTA_ON(mp)) अणु
		error = xfs_qm_quotacheck_dqadjust(ip, XFS_DQTYPE_USER, nblks,
				rtblks);
		अगर (error)
			जाओ error0;
	पूर्ण

	अगर (XFS_IS_GQUOTA_ON(mp)) अणु
		error = xfs_qm_quotacheck_dqadjust(ip, XFS_DQTYPE_GROUP, nblks,
				rtblks);
		अगर (error)
			जाओ error0;
	पूर्ण

	अगर (XFS_IS_PQUOTA_ON(mp)) अणु
		error = xfs_qm_quotacheck_dqadjust(ip, XFS_DQTYPE_PROJ, nblks,
				rtblks);
		अगर (error)
			जाओ error0;
	पूर्ण

error0:
	xfs_irele(ip);
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_qm_flush_one(
	काष्ठा xfs_dquot	*dqp,
	व्योम			*data)
अणु
	काष्ठा xfs_mount	*mp = dqp->q_mount;
	काष्ठा list_head	*buffer_list = data;
	काष्ठा xfs_buf		*bp = शून्य;
	पूर्णांक			error = 0;

	xfs_dqlock(dqp);
	अगर (dqp->q_flags & XFS_DQFLAG_FREEING)
		जाओ out_unlock;
	अगर (!XFS_DQ_IS_सूचीTY(dqp))
		जाओ out_unlock;

	/*
	 * The only way the dquot is alपढ़ोy flush locked by the समय quotacheck
	 * माला_लो here is अगर reclaim flushed it beक्रमe the dqadjust walk dirtied
	 * it क्रम the final समय. Quotacheck collects all dquot bufs in the
	 * local delwri queue beक्रमe dquots are dirtied, so reclaim can't have
	 * possibly queued it क्रम I/O. The only way out is to push the buffer to
	 * cycle the flush lock.
	 */
	अगर (!xfs_dqflock_noरुको(dqp)) अणु
		/* buf is pinned in-core by delwri list */
		bp = xfs_buf_incore(mp->m_ddev_targp, dqp->q_blkno,
				mp->m_quotainfo->qi_dqchunklen, 0);
		अगर (!bp) अणु
			error = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		xfs_buf_unlock(bp);

		xfs_buf_delwri_pushbuf(bp, buffer_list);
		xfs_buf_rele(bp);

		error = -EAGAIN;
		जाओ out_unlock;
	पूर्ण

	error = xfs_qm_dqflush(dqp, &bp);
	अगर (error)
		जाओ out_unlock;

	xfs_buf_delwri_queue(bp, buffer_list);
	xfs_buf_rअन्यथा(bp);
out_unlock:
	xfs_dqunlock(dqp);
	वापस error;
पूर्ण

/*
 * Walk thru all the fileप्रणाली inodes and स्थिरruct a consistent view
 * of the disk quota world. If the quotacheck fails, disable quotas.
 */
STATIC पूर्णांक
xfs_qm_quotacheck(
	xfs_mount_t	*mp)
अणु
	पूर्णांक			error, error2;
	uपूर्णांक			flags;
	LIST_HEAD		(buffer_list);
	काष्ठा xfs_inode	*uip = mp->m_quotainfo->qi_uquotaip;
	काष्ठा xfs_inode	*gip = mp->m_quotainfo->qi_gquotaip;
	काष्ठा xfs_inode	*pip = mp->m_quotainfo->qi_pquotaip;

	flags = 0;

	ASSERT(uip || gip || pip);
	ASSERT(XFS_IS_QUOTA_RUNNING(mp));

	xfs_notice(mp, "Quotacheck needed: Please wait.");

	/*
	 * First we go thru all the dquots on disk, USR and GRP/PRJ, and reset
	 * their counters to zero. We need a clean slate.
	 * We करोn't log our changes till later.
	 */
	अगर (uip) अणु
		error = xfs_qm_reset_dqcounts_buf(mp, uip, XFS_DQTYPE_USER,
					 &buffer_list);
		अगर (error)
			जाओ error_वापस;
		flags |= XFS_UQUOTA_CHKD;
	पूर्ण

	अगर (gip) अणु
		error = xfs_qm_reset_dqcounts_buf(mp, gip, XFS_DQTYPE_GROUP,
					 &buffer_list);
		अगर (error)
			जाओ error_वापस;
		flags |= XFS_GQUOTA_CHKD;
	पूर्ण

	अगर (pip) अणु
		error = xfs_qm_reset_dqcounts_buf(mp, pip, XFS_DQTYPE_PROJ,
					 &buffer_list);
		अगर (error)
			जाओ error_वापस;
		flags |= XFS_PQUOTA_CHKD;
	पूर्ण

	error = xfs_iwalk_thपढ़ोed(mp, 0, 0, xfs_qm_dqusage_adjust, 0, true,
			शून्य);
	अगर (error)
		जाओ error_वापस;

	/*
	 * We've made all the changes that we need to make incore.  Flush them
	 * करोwn to disk buffers अगर everything was updated successfully.
	 */
	अगर (XFS_IS_UQUOTA_ON(mp)) अणु
		error = xfs_qm_dquot_walk(mp, XFS_DQTYPE_USER, xfs_qm_flush_one,
					  &buffer_list);
	पूर्ण
	अगर (XFS_IS_GQUOTA_ON(mp)) अणु
		error2 = xfs_qm_dquot_walk(mp, XFS_DQTYPE_GROUP, xfs_qm_flush_one,
					   &buffer_list);
		अगर (!error)
			error = error2;
	पूर्ण
	अगर (XFS_IS_PQUOTA_ON(mp)) अणु
		error2 = xfs_qm_dquot_walk(mp, XFS_DQTYPE_PROJ, xfs_qm_flush_one,
					   &buffer_list);
		अगर (!error)
			error = error2;
	पूर्ण

	error2 = xfs_buf_delwri_submit(&buffer_list);
	अगर (!error)
		error = error2;

	/*
	 * We can get this error अगर we couldn't करो a dquot allocation inside
	 * xfs_qm_dqusage_adjust (via bulkstat). We करोn't care about the
	 * dirty dquots that might be cached, we just want to get rid of them
	 * and turn quotaoff. The dquots won't be attached to any of the inodes
	 * at this poपूर्णांक (because we पूर्णांकentionally didn't in dqget_noattach).
	 */
	अगर (error) अणु
		xfs_qm_dqpurge_all(mp, XFS_QMOPT_QUOTALL);
		जाओ error_वापस;
	पूर्ण

	/*
	 * If one type of quotas is off, then it will lose its
	 * quotachecked status, since we won't be करोing accounting क्रम
	 * that type anymore.
	 */
	mp->m_qflags &= ~XFS_ALL_QUOTA_CHKD;
	mp->m_qflags |= flags;

 error_वापस:
	xfs_buf_delwri_cancel(&buffer_list);

	अगर (error) अणु
		xfs_warn(mp,
	"Quotacheck: Unsuccessful (Error %d): Disabling quotas.",
			error);
		/*
		 * We must turn off quotas.
		 */
		ASSERT(mp->m_quotainfo != शून्य);
		xfs_qm_destroy_quotainfo(mp);
		अगर (xfs_mount_reset_sbqflags(mp)) अणु
			xfs_warn(mp,
				"Quotacheck: Failed to reset quota flags.");
		पूर्ण
	पूर्ण अन्यथा
		xfs_notice(mp, "Quotacheck: Done.");
	वापस error;
पूर्ण

/*
 * This is called from xfs_mountfs to start quotas and initialize all
 * necessary data काष्ठाures like quotainfo.  This is also responsible क्रम
 * running a quotacheck as necessary.  We are guaranteed that the superblock
 * is consistently पढ़ो in at this poपूर्णांक.
 *
 * If we fail here, the mount will जारी with quota turned off. We करोn't
 * need to inidicate success or failure at all.
 */
व्योम
xfs_qm_mount_quotas(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक			error = 0;
	uपूर्णांक			sbf;

	/*
	 * If quotas on realसमय volumes is not supported, we disable
	 * quotas immediately.
	 */
	अगर (mp->m_sb.sb_rextents) अणु
		xfs_notice(mp, "Cannot turn on quotas for realtime filesystem");
		mp->m_qflags = 0;
		जाओ ग_लिखो_changes;
	पूर्ण

	ASSERT(XFS_IS_QUOTA_RUNNING(mp));

	/*
	 * Allocate the quotainfo काष्ठाure inside the mount काष्ठा, and
	 * create quotainode(s), and change/rev superblock अगर necessary.
	 */
	error = xfs_qm_init_quotainfo(mp);
	अगर (error) अणु
		/*
		 * We must turn off quotas.
		 */
		ASSERT(mp->m_quotainfo == शून्य);
		mp->m_qflags = 0;
		जाओ ग_लिखो_changes;
	पूर्ण
	/*
	 * If any of the quotas are not consistent, करो a quotacheck.
	 */
	अगर (XFS_QM_NEED_QUOTACHECK(mp)) अणु
		error = xfs_qm_quotacheck(mp);
		अगर (error) अणु
			/* Quotacheck failed and disabled quotas. */
			वापस;
		पूर्ण
	पूर्ण
	/*
	 * If one type of quotas is off, then it will lose its
	 * quotachecked status, since we won't be करोing accounting क्रम
	 * that type anymore.
	 */
	अगर (!XFS_IS_UQUOTA_ON(mp))
		mp->m_qflags &= ~XFS_UQUOTA_CHKD;
	अगर (!XFS_IS_GQUOTA_ON(mp))
		mp->m_qflags &= ~XFS_GQUOTA_CHKD;
	अगर (!XFS_IS_PQUOTA_ON(mp))
		mp->m_qflags &= ~XFS_PQUOTA_CHKD;

 ग_लिखो_changes:
	/*
	 * We actually करोn't have to acquire the m_sb_lock at all.
	 * This can only be called from mount, and that's single thपढ़ोed. XXX
	 */
	spin_lock(&mp->m_sb_lock);
	sbf = mp->m_sb.sb_qflags;
	mp->m_sb.sb_qflags = mp->m_qflags & XFS_MOUNT_QUOTA_ALL;
	spin_unlock(&mp->m_sb_lock);

	अगर (sbf != (mp->m_qflags & XFS_MOUNT_QUOTA_ALL)) अणु
		अगर (xfs_sync_sb(mp, false)) अणु
			/*
			 * We could only have been turning quotas off.
			 * We aren't in very good shape actually because
			 * the incore काष्ठाures are convinced that quotas are
			 * off, but the on disk superblock करोesn't know that !
			 */
			ASSERT(!(XFS_IS_QUOTA_RUNNING(mp)));
			xfs_alert(mp, "%s: Superblock update failed!",
				__func__);
		पूर्ण
	पूर्ण

	अगर (error) अणु
		xfs_warn(mp, "Failed to initialize disk quotas.");
		वापस;
	पूर्ण
पूर्ण

/*
 * This is called after the superblock has been पढ़ो in and we're पढ़ोy to
 * iget the quota inodes.
 */
STATIC पूर्णांक
xfs_qm_init_quotainos(
	xfs_mount_t	*mp)
अणु
	काष्ठा xfs_inode	*uip = शून्य;
	काष्ठा xfs_inode	*gip = शून्य;
	काष्ठा xfs_inode	*pip = शून्य;
	पूर्णांक			error;
	uपूर्णांक			flags = 0;

	ASSERT(mp->m_quotainfo);

	/*
	 * Get the uquota and gquota inodes
	 */
	अगर (xfs_sb_version_hasquota(&mp->m_sb)) अणु
		अगर (XFS_IS_UQUOTA_ON(mp) &&
		    mp->m_sb.sb_uquotino != शून्यFSINO) अणु
			ASSERT(mp->m_sb.sb_uquotino > 0);
			error = xfs_iget(mp, शून्य, mp->m_sb.sb_uquotino,
					     0, 0, &uip);
			अगर (error)
				वापस error;
		पूर्ण
		अगर (XFS_IS_GQUOTA_ON(mp) &&
		    mp->m_sb.sb_gquotino != शून्यFSINO) अणु
			ASSERT(mp->m_sb.sb_gquotino > 0);
			error = xfs_iget(mp, शून्य, mp->m_sb.sb_gquotino,
					     0, 0, &gip);
			अगर (error)
				जाओ error_rele;
		पूर्ण
		अगर (XFS_IS_PQUOTA_ON(mp) &&
		    mp->m_sb.sb_pquotino != शून्यFSINO) अणु
			ASSERT(mp->m_sb.sb_pquotino > 0);
			error = xfs_iget(mp, शून्य, mp->m_sb.sb_pquotino,
					     0, 0, &pip);
			अगर (error)
				जाओ error_rele;
		पूर्ण
	पूर्ण अन्यथा अणु
		flags |= XFS_QMOPT_SBVERSION;
	पूर्ण

	/*
	 * Create the three inodes, अगर they करोn't exist alपढ़ोy. The changes
	 * made above will get added to a transaction and logged in one of
	 * the qino_alloc calls below.  If the device is पढ़ोonly,
	 * temporarily चयन to पढ़ो-ग_लिखो to करो this.
	 */
	अगर (XFS_IS_UQUOTA_ON(mp) && uip == शून्य) अणु
		error = xfs_qm_qino_alloc(mp, &uip,
					      flags | XFS_QMOPT_UQUOTA);
		अगर (error)
			जाओ error_rele;

		flags &= ~XFS_QMOPT_SBVERSION;
	पूर्ण
	अगर (XFS_IS_GQUOTA_ON(mp) && gip == शून्य) अणु
		error = xfs_qm_qino_alloc(mp, &gip,
					  flags | XFS_QMOPT_GQUOTA);
		अगर (error)
			जाओ error_rele;

		flags &= ~XFS_QMOPT_SBVERSION;
	पूर्ण
	अगर (XFS_IS_PQUOTA_ON(mp) && pip == शून्य) अणु
		error = xfs_qm_qino_alloc(mp, &pip,
					  flags | XFS_QMOPT_PQUOTA);
		अगर (error)
			जाओ error_rele;
	पूर्ण

	mp->m_quotainfo->qi_uquotaip = uip;
	mp->m_quotainfo->qi_gquotaip = gip;
	mp->m_quotainfo->qi_pquotaip = pip;

	वापस 0;

error_rele:
	अगर (uip)
		xfs_irele(uip);
	अगर (gip)
		xfs_irele(gip);
	अगर (pip)
		xfs_irele(pip);
	वापस error;
पूर्ण

STATIC व्योम
xfs_qm_destroy_quotainos(
	काष्ठा xfs_quotainfo	*qi)
अणु
	अगर (qi->qi_uquotaip) अणु
		xfs_irele(qi->qi_uquotaip);
		qi->qi_uquotaip = शून्य; /* paranoia */
	पूर्ण
	अगर (qi->qi_gquotaip) अणु
		xfs_irele(qi->qi_gquotaip);
		qi->qi_gquotaip = शून्य;
	पूर्ण
	अगर (qi->qi_pquotaip) अणु
		xfs_irele(qi->qi_pquotaip);
		qi->qi_pquotaip = शून्य;
	पूर्ण
पूर्ण

STATIC व्योम
xfs_qm_dqमुक्त_one(
	काष्ठा xfs_dquot	*dqp)
अणु
	काष्ठा xfs_mount	*mp = dqp->q_mount;
	काष्ठा xfs_quotainfo	*qi = mp->m_quotainfo;

	mutex_lock(&qi->qi_tree_lock);
	radix_tree_delete(xfs_dquot_tree(qi, xfs_dquot_type(dqp)), dqp->q_id);

	qi->qi_dquots--;
	mutex_unlock(&qi->qi_tree_lock);

	xfs_qm_dqdestroy(dqp);
पूर्ण

/* --------------- utility functions क्रम vnodeops ---------------- */


/*
 * Given an inode, a uid, gid and prid make sure that we have
 * allocated relevant dquot(s) on disk, and that we won't exceed inode
 * quotas by creating this file.
 * This also attaches dquot(s) to the given inode after locking it,
 * and वापसs the dquots corresponding to the uid and/or gid.
 *
 * in	: inode (unlocked)
 * out	: udquot, gdquot with references taken and unlocked
 */
पूर्णांक
xfs_qm_vop_dqalloc(
	काष्ठा xfs_inode	*ip,
	kuid_t			uid,
	kgid_t			gid,
	prid_t			prid,
	uपूर्णांक			flags,
	काष्ठा xfs_dquot	**O_udqpp,
	काष्ठा xfs_dquot	**O_gdqpp,
	काष्ठा xfs_dquot	**O_pdqpp)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा inode		*inode = VFS_I(ip);
	काष्ठा user_namespace	*user_ns = inode->i_sb->s_user_ns;
	काष्ठा xfs_dquot	*uq = शून्य;
	काष्ठा xfs_dquot	*gq = शून्य;
	काष्ठा xfs_dquot	*pq = शून्य;
	पूर्णांक			error;
	uपूर्णांक			lockflags;

	अगर (!XFS_IS_QUOTA_RUNNING(mp) || !XFS_IS_QUOTA_ON(mp))
		वापस 0;

	lockflags = XFS_ILOCK_EXCL;
	xfs_ilock(ip, lockflags);

	अगर ((flags & XFS_QMOPT_INHERIT) && XFS_INHERIT_GID(ip))
		gid = inode->i_gid;

	/*
	 * Attach the dquot(s) to this inode, करोing a dquot allocation
	 * अगर necessary. The dquot(s) will not be locked.
	 */
	अगर (XFS_NOT_DQATTACHED(mp, ip)) अणु
		error = xfs_qm_dqattach_locked(ip, true);
		अगर (error) अणु
			xfs_iunlock(ip, lockflags);
			वापस error;
		पूर्ण
	पूर्ण

	अगर ((flags & XFS_QMOPT_UQUOTA) && XFS_IS_UQUOTA_ON(mp)) अणु
		ASSERT(O_udqpp);
		अगर (!uid_eq(inode->i_uid, uid)) अणु
			/*
			 * What we need is the dquot that has this uid, and
			 * अगर we send the inode to dqget, the uid of the inode
			 * takes priority over what's sent in the uid argument.
			 * We must unlock inode here beक्रमe calling dqget अगर
			 * we're not sending the inode, because otherwise
			 * we'll deadlock by करोing trans_reserve जबतक
			 * holding ilock.
			 */
			xfs_iunlock(ip, lockflags);
			error = xfs_qm_dqget(mp, from_kuid(user_ns, uid),
					XFS_DQTYPE_USER, true, &uq);
			अगर (error) अणु
				ASSERT(error != -ENOENT);
				वापस error;
			पूर्ण
			/*
			 * Get the ilock in the right order.
			 */
			xfs_dqunlock(uq);
			lockflags = XFS_ILOCK_SHARED;
			xfs_ilock(ip, lockflags);
		पूर्ण अन्यथा अणु
			/*
			 * Take an extra reference, because we'll वापस
			 * this to caller
			 */
			ASSERT(ip->i_udquot);
			uq = xfs_qm_dqhold(ip->i_udquot);
		पूर्ण
	पूर्ण
	अगर ((flags & XFS_QMOPT_GQUOTA) && XFS_IS_GQUOTA_ON(mp)) अणु
		ASSERT(O_gdqpp);
		अगर (!gid_eq(inode->i_gid, gid)) अणु
			xfs_iunlock(ip, lockflags);
			error = xfs_qm_dqget(mp, from_kgid(user_ns, gid),
					XFS_DQTYPE_GROUP, true, &gq);
			अगर (error) अणु
				ASSERT(error != -ENOENT);
				जाओ error_rele;
			पूर्ण
			xfs_dqunlock(gq);
			lockflags = XFS_ILOCK_SHARED;
			xfs_ilock(ip, lockflags);
		पूर्ण अन्यथा अणु
			ASSERT(ip->i_gdquot);
			gq = xfs_qm_dqhold(ip->i_gdquot);
		पूर्ण
	पूर्ण
	अगर ((flags & XFS_QMOPT_PQUOTA) && XFS_IS_PQUOTA_ON(mp)) अणु
		ASSERT(O_pdqpp);
		अगर (ip->i_projid != prid) अणु
			xfs_iunlock(ip, lockflags);
			error = xfs_qm_dqget(mp, prid,
					XFS_DQTYPE_PROJ, true, &pq);
			अगर (error) अणु
				ASSERT(error != -ENOENT);
				जाओ error_rele;
			पूर्ण
			xfs_dqunlock(pq);
			lockflags = XFS_ILOCK_SHARED;
			xfs_ilock(ip, lockflags);
		पूर्ण अन्यथा अणु
			ASSERT(ip->i_pdquot);
			pq = xfs_qm_dqhold(ip->i_pdquot);
		पूर्ण
	पूर्ण
	trace_xfs_dquot_dqalloc(ip);

	xfs_iunlock(ip, lockflags);
	अगर (O_udqpp)
		*O_udqpp = uq;
	अन्यथा
		xfs_qm_dqrele(uq);
	अगर (O_gdqpp)
		*O_gdqpp = gq;
	अन्यथा
		xfs_qm_dqrele(gq);
	अगर (O_pdqpp)
		*O_pdqpp = pq;
	अन्यथा
		xfs_qm_dqrele(pq);
	वापस 0;

error_rele:
	xfs_qm_dqrele(gq);
	xfs_qm_dqrele(uq);
	वापस error;
पूर्ण

/*
 * Actually transfer ownership, and करो dquot modअगरications.
 * These were alपढ़ोy reserved.
 */
काष्ठा xfs_dquot *
xfs_qm_vop_chown(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_dquot	**IO_olddq,
	काष्ठा xfs_dquot	*newdq)
अणु
	काष्ठा xfs_dquot	*prevdq;
	uपूर्णांक		bfield = XFS_IS_REALTIME_INODE(ip) ?
				 XFS_TRANS_DQ_RTBCOUNT : XFS_TRANS_DQ_BCOUNT;


	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT(XFS_IS_QUOTA_RUNNING(ip->i_mount));

	/* old dquot */
	prevdq = *IO_olddq;
	ASSERT(prevdq);
	ASSERT(prevdq != newdq);

	xfs_trans_mod_dquot(tp, prevdq, bfield, -(ip->i_nblocks));
	xfs_trans_mod_dquot(tp, prevdq, XFS_TRANS_DQ_ICOUNT, -1);

	/* the sparkling new dquot */
	xfs_trans_mod_dquot(tp, newdq, bfield, ip->i_nblocks);
	xfs_trans_mod_dquot(tp, newdq, XFS_TRANS_DQ_ICOUNT, 1);

	/*
	 * Back when we made quota reservations क्रम the chown, we reserved the
	 * ondisk blocks + delalloc blocks with the new dquot.  Now that we've
	 * चयनed the dquots, decrease the new dquot's block reservation
	 * (having alपढ़ोy bumped up the real counter) so that we करोn't have
	 * any reservation to give back when we commit.
	 */
	xfs_trans_mod_dquot(tp, newdq, XFS_TRANS_DQ_RES_BLKS,
			-ip->i_delayed_blks);

	/*
	 * Give the incore reservation क्रम delalloc blocks back to the old
	 * dquot.  We करोn't normally handle delalloc quota reservations
	 * transactionally, so just lock the dquot and subtract from the
	 * reservation.  Dirty the transaction because it's too late to turn
	 * back now.
	 */
	tp->t_flags |= XFS_TRANS_सूचीTY;
	xfs_dqlock(prevdq);
	ASSERT(prevdq->q_blk.reserved >= ip->i_delayed_blks);
	prevdq->q_blk.reserved -= ip->i_delayed_blks;
	xfs_dqunlock(prevdq);

	/*
	 * Take an extra reference, because the inode is going to keep
	 * this dquot poपूर्णांकer even after the trans_commit.
	 */
	*IO_olddq = xfs_qm_dqhold(newdq);

	वापस prevdq;
पूर्ण

पूर्णांक
xfs_qm_vop_नाम_dqattach(
	काष्ठा xfs_inode	**i_tab)
अणु
	काष्ठा xfs_mount	*mp = i_tab[0]->i_mount;
	पूर्णांक			i;

	अगर (!XFS_IS_QUOTA_RUNNING(mp) || !XFS_IS_QUOTA_ON(mp))
		वापस 0;

	क्रम (i = 0; (i < 4 && i_tab[i]); i++) अणु
		काष्ठा xfs_inode	*ip = i_tab[i];
		पूर्णांक			error;

		/*
		 * Watch out क्रम duplicate entries in the table.
		 */
		अगर (i == 0 || ip != i_tab[i-1]) अणु
			अगर (XFS_NOT_DQATTACHED(mp, ip)) अणु
				error = xfs_qm_dqattach(ip);
				अगर (error)
					वापस error;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम
xfs_qm_vop_create_dqattach(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_dquot	*udqp,
	काष्ठा xfs_dquot	*gdqp,
	काष्ठा xfs_dquot	*pdqp)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;

	अगर (!XFS_IS_QUOTA_RUNNING(mp) || !XFS_IS_QUOTA_ON(mp))
		वापस;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	अगर (udqp && XFS_IS_UQUOTA_ON(mp)) अणु
		ASSERT(ip->i_udquot == शून्य);
		ASSERT(i_uid_पढ़ो(VFS_I(ip)) == udqp->q_id);

		ip->i_udquot = xfs_qm_dqhold(udqp);
		xfs_trans_mod_dquot(tp, udqp, XFS_TRANS_DQ_ICOUNT, 1);
	पूर्ण
	अगर (gdqp && XFS_IS_GQUOTA_ON(mp)) अणु
		ASSERT(ip->i_gdquot == शून्य);
		ASSERT(i_gid_पढ़ो(VFS_I(ip)) == gdqp->q_id);

		ip->i_gdquot = xfs_qm_dqhold(gdqp);
		xfs_trans_mod_dquot(tp, gdqp, XFS_TRANS_DQ_ICOUNT, 1);
	पूर्ण
	अगर (pdqp && XFS_IS_PQUOTA_ON(mp)) अणु
		ASSERT(ip->i_pdquot == शून्य);
		ASSERT(ip->i_projid == pdqp->q_id);

		ip->i_pdquot = xfs_qm_dqhold(pdqp);
		xfs_trans_mod_dquot(tp, pdqp, XFS_TRANS_DQ_ICOUNT, 1);
	पूर्ण
पूर्ण

