<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_qm.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_log.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_error.h"

/*
 * Lock order:
 *
 * ip->i_lock
 *   qi->qi_tree_lock
 *     dquot->q_qlock (xfs_dqlock() and मित्रs)
 *       dquot->q_flush (xfs_dqflock() and मित्रs)
 *       qi->qi_lru_lock
 *
 * If two dquots need to be locked the order is user beक्रमe group/project,
 * otherwise by the lowest id first, see xfs_dqlock2.
 */

काष्ठा kmem_zone		*xfs_qm_dqtrxzone;
अटल काष्ठा kmem_zone		*xfs_qm_dqzone;

अटल काष्ठा lock_class_key xfs_dquot_group_class;
अटल काष्ठा lock_class_key xfs_dquot_project_class;

/*
 * This is called to मुक्त all the memory associated with a dquot
 */
व्योम
xfs_qm_dqdestroy(
	काष्ठा xfs_dquot	*dqp)
अणु
	ASSERT(list_empty(&dqp->q_lru));

	kmem_मुक्त(dqp->q_logitem.qli_item.li_lv_shaकरोw);
	mutex_destroy(&dqp->q_qlock);

	XFS_STATS_DEC(dqp->q_mount, xs_qm_dquot);
	kmem_cache_मुक्त(xfs_qm_dqzone, dqp);
पूर्ण

/*
 * If शेष limits are in क्रमce, push them पूर्णांकo the dquot now.
 * We overग_लिखो the dquot limits only अगर they are zero and this
 * is not the root dquot.
 */
व्योम
xfs_qm_adjust_dqlimits(
	काष्ठा xfs_dquot	*dq)
अणु
	काष्ठा xfs_mount	*mp = dq->q_mount;
	काष्ठा xfs_quotainfo	*q = mp->m_quotainfo;
	काष्ठा xfs_def_quota	*defq;
	पूर्णांक			pपुनः_स्मृति = 0;

	ASSERT(dq->q_id);
	defq = xfs_get_defquota(q, xfs_dquot_type(dq));

	अगर (!dq->q_blk.softlimit) अणु
		dq->q_blk.softlimit = defq->blk.soft;
		pपुनः_स्मृति = 1;
	पूर्ण
	अगर (!dq->q_blk.hardlimit) अणु
		dq->q_blk.hardlimit = defq->blk.hard;
		pपुनः_स्मृति = 1;
	पूर्ण
	अगर (!dq->q_ino.softlimit)
		dq->q_ino.softlimit = defq->ino.soft;
	अगर (!dq->q_ino.hardlimit)
		dq->q_ino.hardlimit = defq->ino.hard;
	अगर (!dq->q_rtb.softlimit)
		dq->q_rtb.softlimit = defq->rtb.soft;
	अगर (!dq->q_rtb.hardlimit)
		dq->q_rtb.hardlimit = defq->rtb.hard;

	अगर (pपुनः_स्मृति)
		xfs_dquot_set_pपुनः_स्मृति_limits(dq);
पूर्ण

/* Set the expiration समय of a quota's grace period. */
समय64_t
xfs_dquot_set_समयout(
	काष्ठा xfs_mount	*mp,
	समय64_t		समयout)
अणु
	काष्ठा xfs_quotainfo	*qi = mp->m_quotainfo;

	वापस clamp_t(समय64_t, समयout, qi->qi_expiry_min,
					  qi->qi_expiry_max);
पूर्ण

/* Set the length of the शेष grace period. */
समय64_t
xfs_dquot_set_grace_period(
	समय64_t		grace)
अणु
	वापस clamp_t(समय64_t, grace, XFS_DQ_GRACE_MIN, XFS_DQ_GRACE_MAX);
पूर्ण

/*
 * Determine अगर this quota counter is over either limit and set the quota
 * समयrs as appropriate.
 */
अटल अंतरभूत व्योम
xfs_qm_adjust_res_समयr(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dquot_res	*res,
	काष्ठा xfs_quota_limits	*qlim)
अणु
	ASSERT(res->hardlimit == 0 || res->softlimit <= res->hardlimit);

	अगर ((res->softlimit && res->count > res->softlimit) ||
	    (res->hardlimit && res->count > res->hardlimit)) अणु
		अगर (res->समयr == 0)
			res->समयr = xfs_dquot_set_समयout(mp,
					kसमय_get_real_seconds() + qlim->समय);
	पूर्ण अन्यथा अणु
		अगर (res->समयr == 0)
			res->warnings = 0;
		अन्यथा
			res->समयr = 0;
	पूर्ण
पूर्ण

/*
 * Check the limits and समयrs of a dquot and start or reset समयrs
 * अगर necessary.
 * This माला_लो called even when quota enक्रमcement is OFF, which makes our
 * lअगरe a little less complicated. (We just करोn't reject any quota
 * reservations in that हाल, when enक्रमcement is off).
 * We also वापस 0 as the values of the समयrs in Q_GETQUOTA calls, when
 * enक्रमcement's off.
 * In contrast, warnings are a little dअगरferent in that they करोn't
 * 'automatically' get started when limits get exceeded.  They करो
 * get reset to zero, however, when we find the count to be under
 * the soft limit (they are only ever set non-zero via userspace).
 */
व्योम
xfs_qm_adjust_dqसमयrs(
	काष्ठा xfs_dquot	*dq)
अणु
	काष्ठा xfs_mount	*mp = dq->q_mount;
	काष्ठा xfs_quotainfo	*qi = mp->m_quotainfo;
	काष्ठा xfs_def_quota	*defq;

	ASSERT(dq->q_id);
	defq = xfs_get_defquota(qi, xfs_dquot_type(dq));

	xfs_qm_adjust_res_समयr(dq->q_mount, &dq->q_blk, &defq->blk);
	xfs_qm_adjust_res_समयr(dq->q_mount, &dq->q_ino, &defq->ino);
	xfs_qm_adjust_res_समयr(dq->q_mount, &dq->q_rtb, &defq->rtb);
पूर्ण

/*
 * initialize a buffer full of dquots and log the whole thing
 */
STATIC व्योम
xfs_qm_init_dquot_blk(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_quotainfo	*q = mp->m_quotainfo;
	काष्ठा xfs_dqblk	*d;
	xfs_dqid_t		curid;
	अचिन्हित पूर्णांक		qflag;
	अचिन्हित पूर्णांक		blftype;
	पूर्णांक			i;

	ASSERT(tp);
	ASSERT(xfs_buf_islocked(bp));

	चयन (type) अणु
	हाल XFS_DQTYPE_USER:
		qflag = XFS_UQUOTA_CHKD;
		blftype = XFS_BLF_UDQUOT_BUF;
		अवरोध;
	हाल XFS_DQTYPE_PROJ:
		qflag = XFS_PQUOTA_CHKD;
		blftype = XFS_BLF_PDQUOT_BUF;
		अवरोध;
	हाल XFS_DQTYPE_GROUP:
		qflag = XFS_GQUOTA_CHKD;
		blftype = XFS_BLF_GDQUOT_BUF;
		अवरोध;
	शेष:
		ASSERT(0);
		वापस;
	पूर्ण

	d = bp->b_addr;

	/*
	 * ID of the first dquot in the block - id's are zero based.
	 */
	curid = id - (id % q->qi_dqperchunk);
	स_रखो(d, 0, BBTOB(q->qi_dqchunklen));
	क्रम (i = 0; i < q->qi_dqperchunk; i++, d++, curid++) अणु
		d->dd_diskdq.d_magic = cpu_to_be16(XFS_DQUOT_MAGIC);
		d->dd_diskdq.d_version = XFS_DQUOT_VERSION;
		d->dd_diskdq.d_id = cpu_to_be32(curid);
		d->dd_diskdq.d_type = type;
		अगर (curid > 0 && xfs_sb_version_hasbigसमय(&mp->m_sb))
			d->dd_diskdq.d_type |= XFS_DQTYPE_BIGTIME;
		अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
			uuid_copy(&d->dd_uuid, &mp->m_sb.sb_meta_uuid);
			xfs_update_cksum((अक्षर *)d, माप(काष्ठा xfs_dqblk),
					 XFS_DQUOT_CRC_OFF);
		पूर्ण
	पूर्ण

	xfs_trans_dquot_buf(tp, bp, blftype);

	/*
	 * quotacheck uses delayed ग_लिखोs to update all the dquots on disk in an
	 * efficient manner instead of logging the inभागidual dquot changes as
	 * they are made. However अगर we log the buffer allocated here and crash
	 * after quotacheck जबतक the logged initialisation is still in the
	 * active region of the log, log recovery can replay the dquot buffer
	 * initialisation over the top of the checked dquots and corrupt quota
	 * accounting.
	 *
	 * To aव्योम this problem, quotacheck cannot log the initialised buffer.
	 * We must still dirty the buffer and ग_लिखो it back beक्रमe the
	 * allocation transaction clears the log. Thereक्रमe, mark the buffer as
	 * ordered instead of logging it directly. This is safe क्रम quotacheck
	 * because it detects and repairs allocated but initialized dquot blocks
	 * in the quota inodes.
	 */
	अगर (!(mp->m_qflags & qflag))
		xfs_trans_ordered_buf(tp, bp);
	अन्यथा
		xfs_trans_log_buf(tp, bp, 0, BBTOB(q->qi_dqchunklen) - 1);
पूर्ण

/*
 * Initialize the dynamic speculative pपुनः_स्मृतिation thresholds. The lo/hi
 * watermarks correspond to the soft and hard limits by शेष. If a soft limit
 * is not specअगरied, we use 95% of the hard limit.
 */
व्योम
xfs_dquot_set_pपुनः_स्मृति_limits(काष्ठा xfs_dquot *dqp)
अणु
	uपूर्णांक64_t space;

	dqp->q_pपुनः_स्मृति_hi_wmark = dqp->q_blk.hardlimit;
	dqp->q_pपुनः_स्मृति_lo_wmark = dqp->q_blk.softlimit;
	अगर (!dqp->q_pपुनः_स्मृति_lo_wmark) अणु
		dqp->q_pपुनः_स्मृति_lo_wmark = dqp->q_pपुनः_स्मृति_hi_wmark;
		करो_भाग(dqp->q_pपुनः_स्मृति_lo_wmark, 100);
		dqp->q_pपुनः_स्मृति_lo_wmark *= 95;
	पूर्ण

	space = dqp->q_pपुनः_स्मृति_hi_wmark;

	करो_भाग(space, 100);
	dqp->q_low_space[XFS_QLOWSP_1_PCNT] = space;
	dqp->q_low_space[XFS_QLOWSP_3_PCNT] = space * 3;
	dqp->q_low_space[XFS_QLOWSP_5_PCNT] = space * 5;
पूर्ण

/*
 * Ensure that the given in-core dquot has a buffer on disk backing it, and
 * वापस the buffer locked and held. This is called when the bmapi finds a
 * hole.
 */
STATIC पूर्णांक
xfs_dquot_disk_alloc(
	काष्ठा xfs_trans	**tpp,
	काष्ठा xfs_dquot	*dqp,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_bmbt_irec	map;
	काष्ठा xfs_trans	*tp = *tpp;
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_buf		*bp;
	xfs_dqtype_t		qtype = xfs_dquot_type(dqp);
	काष्ठा xfs_inode	*quotip = xfs_quota_inode(mp, qtype);
	पूर्णांक			nmaps = 1;
	पूर्णांक			error;

	trace_xfs_dqalloc(dqp);

	xfs_ilock(quotip, XFS_ILOCK_EXCL);
	अगर (!xfs_this_quota_on(dqp->q_mount, qtype)) अणु
		/*
		 * Return अगर this type of quotas is turned off जबतक we didn't
		 * have an inode lock
		 */
		xfs_iunlock(quotip, XFS_ILOCK_EXCL);
		वापस -ESRCH;
	पूर्ण

	xfs_trans_ijoin(tp, quotip, XFS_ILOCK_EXCL);

	error = xfs_iext_count_may_overflow(quotip, XFS_DATA_FORK,
			XFS_IEXT_ADD_NOSPLIT_CNT);
	अगर (error)
		वापस error;

	/* Create the block mapping. */
	error = xfs_bmapi_ग_लिखो(tp, quotip, dqp->q_fileoffset,
			XFS_DQUOT_CLUSTER_SIZE_FSB, XFS_BMAPI_METADATA, 0, &map,
			&nmaps);
	अगर (error)
		वापस error;
	ASSERT(map.br_blockcount == XFS_DQUOT_CLUSTER_SIZE_FSB);
	ASSERT(nmaps == 1);
	ASSERT((map.br_startblock != DELAYSTARTBLOCK) &&
	       (map.br_startblock != HOLESTARTBLOCK));

	/*
	 * Keep track of the blkno to save a lookup later
	 */
	dqp->q_blkno = XFS_FSB_TO_DADDR(mp, map.br_startblock);

	/* now we can just get the buffer (there's nothing to पढ़ो yet) */
	error = xfs_trans_get_buf(tp, mp->m_ddev_targp, dqp->q_blkno,
			mp->m_quotainfo->qi_dqchunklen, 0, &bp);
	अगर (error)
		वापस error;
	bp->b_ops = &xfs_dquot_buf_ops;

	/*
	 * Make a chunk of dquots out of this buffer and log
	 * the entire thing.
	 */
	xfs_qm_init_dquot_blk(tp, mp, dqp->q_id, qtype, bp);
	xfs_buf_set_ref(bp, XFS_DQUOT_REF);

	/*
	 * Hold the buffer and join it to the dfops so that we'll still own
	 * the buffer when we वापस to the caller.  The buffer disposal on
	 * error must be paid attention to very carefully, as it has been
	 * broken since commit efa092f3d4c6 "[XFS] Fixes a bug in the quota
	 * code when allocating a new dquot record" in 2005, and the later
	 * conversion to xfs_defer_ops in commit 310a75a3c6c747 failed to keep
	 * the buffer locked across the _defer_finish call.  We can now करो
	 * this correctly with xfs_defer_bjoin.
	 *
	 * Above, we allocated a disk block क्रम the dquot inक्रमmation and used
	 * get_buf to initialize the dquot. If the _defer_finish fails, the old
	 * transaction is gone but the new buffer is not joined or held to any
	 * transaction, so we must _buf_rअन्यथा it.
	 *
	 * If everything succeeds, the caller of this function is वापसed a
	 * buffer that is locked and held to the transaction.  The caller
	 * is responsible क्रम unlocking any buffer passed back, either
	 * manually or by committing the transaction.  On error, the buffer is
	 * released and not passed back.
	 */
	xfs_trans_bhold(tp, bp);
	error = xfs_defer_finish(tpp);
	अगर (error) अणु
		xfs_trans_bhold_release(*tpp, bp);
		xfs_trans_brअन्यथा(*tpp, bp);
		वापस error;
	पूर्ण
	*bpp = bp;
	वापस 0;
पूर्ण

/*
 * Read in the in-core dquot's on-disk metadata and वापस the buffer.
 * Returns ENOENT to संकेत a hole.
 */
STATIC पूर्णांक
xfs_dquot_disk_पढ़ो(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dquot	*dqp,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_bmbt_irec	map;
	काष्ठा xfs_buf		*bp;
	xfs_dqtype_t		qtype = xfs_dquot_type(dqp);
	काष्ठा xfs_inode	*quotip = xfs_quota_inode(mp, qtype);
	uपूर्णांक			lock_mode;
	पूर्णांक			nmaps = 1;
	पूर्णांक			error;

	lock_mode = xfs_ilock_data_map_shared(quotip);
	अगर (!xfs_this_quota_on(mp, qtype)) अणु
		/*
		 * Return अगर this type of quotas is turned off जबतक we
		 * didn't have the quota inode lock.
		 */
		xfs_iunlock(quotip, lock_mode);
		वापस -ESRCH;
	पूर्ण

	/*
	 * Find the block map; no allocations yet
	 */
	error = xfs_bmapi_पढ़ो(quotip, dqp->q_fileoffset,
			XFS_DQUOT_CLUSTER_SIZE_FSB, &map, &nmaps, 0);
	xfs_iunlock(quotip, lock_mode);
	अगर (error)
		वापस error;

	ASSERT(nmaps == 1);
	ASSERT(map.br_blockcount >= 1);
	ASSERT(map.br_startblock != DELAYSTARTBLOCK);
	अगर (map.br_startblock == HOLESTARTBLOCK)
		वापस -ENOENT;

	trace_xfs_dqtobp_पढ़ो(dqp);

	/*
	 * store the blkno etc so that we करोn't have to करो the
	 * mapping all the समय
	 */
	dqp->q_blkno = XFS_FSB_TO_DADDR(mp, map.br_startblock);

	error = xfs_trans_पढ़ो_buf(mp, शून्य, mp->m_ddev_targp, dqp->q_blkno,
			mp->m_quotainfo->qi_dqchunklen, 0, &bp,
			&xfs_dquot_buf_ops);
	अगर (error) अणु
		ASSERT(bp == शून्य);
		वापस error;
	पूर्ण

	ASSERT(xfs_buf_islocked(bp));
	xfs_buf_set_ref(bp, XFS_DQUOT_REF);
	*bpp = bp;

	वापस 0;
पूर्ण

/* Allocate and initialize everything we need क्रम an incore dquot. */
STATIC काष्ठा xfs_dquot *
xfs_dquot_alloc(
	काष्ठा xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type)
अणु
	काष्ठा xfs_dquot	*dqp;

	dqp = kmem_cache_zalloc(xfs_qm_dqzone, GFP_KERNEL | __GFP_NOFAIL);

	dqp->q_type = type;
	dqp->q_id = id;
	dqp->q_mount = mp;
	INIT_LIST_HEAD(&dqp->q_lru);
	mutex_init(&dqp->q_qlock);
	init_रुकोqueue_head(&dqp->q_pinरुको);
	dqp->q_fileoffset = (xfs_fileoff_t)id / mp->m_quotainfo->qi_dqperchunk;
	/*
	 * Offset of dquot in the (fixed sized) dquot chunk.
	 */
	dqp->q_bufoffset = (id % mp->m_quotainfo->qi_dqperchunk) *
			माप(xfs_dqblk_t);

	/*
	 * Because we want to use a counting completion, complete
	 * the flush completion once to allow a single access to
	 * the flush completion without blocking.
	 */
	init_completion(&dqp->q_flush);
	complete(&dqp->q_flush);

	/*
	 * Make sure group quotas have a dअगरferent lock class than user
	 * quotas.
	 */
	चयन (type) अणु
	हाल XFS_DQTYPE_USER:
		/* uses the शेष lock class */
		अवरोध;
	हाल XFS_DQTYPE_GROUP:
		lockdep_set_class(&dqp->q_qlock, &xfs_dquot_group_class);
		अवरोध;
	हाल XFS_DQTYPE_PROJ:
		lockdep_set_class(&dqp->q_qlock, &xfs_dquot_project_class);
		अवरोध;
	शेष:
		ASSERT(0);
		अवरोध;
	पूर्ण

	xfs_qm_dquot_logitem_init(dqp);

	XFS_STATS_INC(mp, xs_qm_dquot);
	वापस dqp;
पूर्ण

/* Check the ondisk dquot's id and type match what the incore dquot expects. */
अटल bool
xfs_dquot_check_type(
	काष्ठा xfs_dquot	*dqp,
	काष्ठा xfs_disk_dquot	*ddqp)
अणु
	uपूर्णांक8_t			ddqp_type;
	uपूर्णांक8_t			dqp_type;

	ddqp_type = ddqp->d_type & XFS_DQTYPE_REC_MASK;
	dqp_type = xfs_dquot_type(dqp);

	अगर (be32_to_cpu(ddqp->d_id) != dqp->q_id)
		वापस false;

	/*
	 * V5 fileप्रणालीs always expect an exact type match.  V4 fileप्रणालीs
	 * expect an exact match क्रम user dquots and क्रम non-root group and
	 * project dquots.
	 */
	अगर (xfs_sb_version_hascrc(&dqp->q_mount->m_sb) ||
	    dqp_type == XFS_DQTYPE_USER || dqp->q_id != 0)
		वापस ddqp_type == dqp_type;

	/*
	 * V4 fileप्रणालीs support either group or project quotas, but not both
	 * at the same समय.  The non-user quota file can be चयनed between
	 * group and project quota uses depending on the mount options, which
	 * means that we can encounter the other type when we try to load quota
	 * शेषs.  Quotacheck will soon reset the the entire quota file
	 * (including the root dquot) anyway, but करोn't log scary corruption
	 * reports to dmesg.
	 */
	वापस ddqp_type == XFS_DQTYPE_GROUP || ddqp_type == XFS_DQTYPE_PROJ;
पूर्ण

/* Copy the in-core quota fields in from the on-disk buffer. */
STATIC पूर्णांक
xfs_dquot_from_disk(
	काष्ठा xfs_dquot	*dqp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_disk_dquot	*ddqp = bp->b_addr + dqp->q_bufoffset;

	/*
	 * Ensure that we got the type and ID we were looking क्रम.
	 * Everything अन्यथा was checked by the dquot buffer verअगरier.
	 */
	अगर (!xfs_dquot_check_type(dqp, ddqp)) अणु
		xfs_alert_tag(bp->b_mount, XFS_PTAG_VERIFIER_ERROR,
			  "Metadata corruption detected at %pS, quota %u",
			  __this_address, dqp->q_id);
		xfs_alert(bp->b_mount, "Unmount and run xfs_repair");
		वापस -EFSCORRUPTED;
	पूर्ण

	/* copy everything from disk dquot to the incore dquot */
	dqp->q_type = ddqp->d_type;
	dqp->q_blk.hardlimit = be64_to_cpu(ddqp->d_blk_hardlimit);
	dqp->q_blk.softlimit = be64_to_cpu(ddqp->d_blk_softlimit);
	dqp->q_ino.hardlimit = be64_to_cpu(ddqp->d_ino_hardlimit);
	dqp->q_ino.softlimit = be64_to_cpu(ddqp->d_ino_softlimit);
	dqp->q_rtb.hardlimit = be64_to_cpu(ddqp->d_rtb_hardlimit);
	dqp->q_rtb.softlimit = be64_to_cpu(ddqp->d_rtb_softlimit);

	dqp->q_blk.count = be64_to_cpu(ddqp->d_bcount);
	dqp->q_ino.count = be64_to_cpu(ddqp->d_icount);
	dqp->q_rtb.count = be64_to_cpu(ddqp->d_rtbcount);

	dqp->q_blk.warnings = be16_to_cpu(ddqp->d_bwarns);
	dqp->q_ino.warnings = be16_to_cpu(ddqp->d_iwarns);
	dqp->q_rtb.warnings = be16_to_cpu(ddqp->d_rtbwarns);

	dqp->q_blk.समयr = xfs_dquot_from_disk_ts(ddqp, ddqp->d_bसमयr);
	dqp->q_ino.समयr = xfs_dquot_from_disk_ts(ddqp, ddqp->d_iसमयr);
	dqp->q_rtb.समयr = xfs_dquot_from_disk_ts(ddqp, ddqp->d_rtbसमयr);

	/*
	 * Reservation counters are defined as reservation plus current usage
	 * to aव्योम having to add every समय.
	 */
	dqp->q_blk.reserved = dqp->q_blk.count;
	dqp->q_ino.reserved = dqp->q_ino.count;
	dqp->q_rtb.reserved = dqp->q_rtb.count;

	/* initialize the dquot speculative pपुनः_स्मृति thresholds */
	xfs_dquot_set_pपुनः_स्मृति_limits(dqp);
	वापस 0;
पूर्ण

/* Copy the in-core quota fields पूर्णांकo the on-disk buffer. */
व्योम
xfs_dquot_to_disk(
	काष्ठा xfs_disk_dquot	*ddqp,
	काष्ठा xfs_dquot	*dqp)
अणु
	ddqp->d_magic = cpu_to_be16(XFS_DQUOT_MAGIC);
	ddqp->d_version = XFS_DQUOT_VERSION;
	ddqp->d_type = dqp->q_type;
	ddqp->d_id = cpu_to_be32(dqp->q_id);
	ddqp->d_pad0 = 0;
	ddqp->d_pad = 0;

	ddqp->d_blk_hardlimit = cpu_to_be64(dqp->q_blk.hardlimit);
	ddqp->d_blk_softlimit = cpu_to_be64(dqp->q_blk.softlimit);
	ddqp->d_ino_hardlimit = cpu_to_be64(dqp->q_ino.hardlimit);
	ddqp->d_ino_softlimit = cpu_to_be64(dqp->q_ino.softlimit);
	ddqp->d_rtb_hardlimit = cpu_to_be64(dqp->q_rtb.hardlimit);
	ddqp->d_rtb_softlimit = cpu_to_be64(dqp->q_rtb.softlimit);

	ddqp->d_bcount = cpu_to_be64(dqp->q_blk.count);
	ddqp->d_icount = cpu_to_be64(dqp->q_ino.count);
	ddqp->d_rtbcount = cpu_to_be64(dqp->q_rtb.count);

	ddqp->d_bwarns = cpu_to_be16(dqp->q_blk.warnings);
	ddqp->d_iwarns = cpu_to_be16(dqp->q_ino.warnings);
	ddqp->d_rtbwarns = cpu_to_be16(dqp->q_rtb.warnings);

	ddqp->d_bसमयr = xfs_dquot_to_disk_ts(dqp, dqp->q_blk.समयr);
	ddqp->d_iसमयr = xfs_dquot_to_disk_ts(dqp, dqp->q_ino.समयr);
	ddqp->d_rtbसमयr = xfs_dquot_to_disk_ts(dqp, dqp->q_rtb.समयr);
पूर्ण

/* Allocate and initialize the dquot buffer क्रम this in-core dquot. */
अटल पूर्णांक
xfs_qm_dqपढ़ो_alloc(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dquot	*dqp,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_qm_dqalloc,
			XFS_QM_DQALLOC_SPACE_RES(mp), 0, 0, &tp);
	अगर (error)
		जाओ err;

	error = xfs_dquot_disk_alloc(&tp, dqp, bpp);
	अगर (error)
		जाओ err_cancel;

	error = xfs_trans_commit(tp);
	अगर (error) अणु
		/*
		 * Buffer was held to the transaction, so we have to unlock it
		 * manually here because we're not passing it back.
		 */
		xfs_buf_rअन्यथा(*bpp);
		*bpp = शून्य;
		जाओ err;
	पूर्ण
	वापस 0;

err_cancel:
	xfs_trans_cancel(tp);
err:
	वापस error;
पूर्ण

/*
 * Read in the ondisk dquot using dqtobp() then copy it to an incore version,
 * and release the buffer immediately.  If @can_alloc is true, fill any
 * holes in the on-disk metadata.
 */
अटल पूर्णांक
xfs_qm_dqपढ़ो(
	काष्ठा xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	bool			can_alloc,
	काष्ठा xfs_dquot	**dqpp)
अणु
	काष्ठा xfs_dquot	*dqp;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	dqp = xfs_dquot_alloc(mp, id, type);
	trace_xfs_dqपढ़ो(dqp);

	/* Try to पढ़ो the buffer, allocating अगर necessary. */
	error = xfs_dquot_disk_पढ़ो(mp, dqp, &bp);
	अगर (error == -ENOENT && can_alloc)
		error = xfs_qm_dqपढ़ो_alloc(mp, dqp, &bp);
	अगर (error)
		जाओ err;

	/*
	 * At this poपूर्णांक we should have a clean locked buffer.  Copy the data
	 * to the incore dquot and release the buffer since the incore dquot
	 * has its own locking protocol so we needn't tie up the buffer any
	 * further.
	 */
	ASSERT(xfs_buf_islocked(bp));
	error = xfs_dquot_from_disk(dqp, bp);
	xfs_buf_rअन्यथा(bp);
	अगर (error)
		जाओ err;

	*dqpp = dqp;
	वापस error;

err:
	trace_xfs_dqपढ़ो_fail(dqp);
	xfs_qm_dqdestroy(dqp);
	*dqpp = शून्य;
	वापस error;
पूर्ण

/*
 * Advance to the next id in the current chunk, or अगर at the
 * end of the chunk, skip ahead to first id in next allocated chunk
 * using the SEEK_DATA पूर्णांकerface.
 */
अटल पूर्णांक
xfs_dq_get_next_id(
	काष्ठा xfs_mount	*mp,
	xfs_dqtype_t		type,
	xfs_dqid_t		*id)
अणु
	काष्ठा xfs_inode	*quotip = xfs_quota_inode(mp, type);
	xfs_dqid_t		next_id = *id + 1; /* simple advance */
	uपूर्णांक			lock_flags;
	काष्ठा xfs_bmbt_irec	got;
	काष्ठा xfs_iext_cursor	cur;
	xfs_fsblock_t		start;
	पूर्णांक			error = 0;

	/* If we'd wrap past the max ID, stop */
	अगर (next_id < *id)
		वापस -ENOENT;

	/* If new ID is within the current chunk, advancing it sufficed */
	अगर (next_id % mp->m_quotainfo->qi_dqperchunk) अणु
		*id = next_id;
		वापस 0;
	पूर्ण

	/* Nope, next_id is now past the current chunk, so find the next one */
	start = (xfs_fsblock_t)next_id / mp->m_quotainfo->qi_dqperchunk;

	lock_flags = xfs_ilock_data_map_shared(quotip);
	error = xfs_iपढ़ो_extents(शून्य, quotip, XFS_DATA_FORK);
	अगर (error)
		वापस error;

	अगर (xfs_iext_lookup_extent(quotip, &quotip->i_df, start, &cur, &got)) अणु
		/* contiguous chunk, bump startoff क्रम the id calculation */
		अगर (got.br_startoff < start)
			got.br_startoff = start;
		*id = got.br_startoff * mp->m_quotainfo->qi_dqperchunk;
	पूर्ण अन्यथा अणु
		error = -ENOENT;
	पूर्ण

	xfs_iunlock(quotip, lock_flags);

	वापस error;
पूर्ण

/*
 * Look up the dquot in the in-core cache.  If found, the dquot is वापसed
 * locked and पढ़ोy to go.
 */
अटल काष्ठा xfs_dquot *
xfs_qm_dqget_cache_lookup(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_quotainfo	*qi,
	काष्ठा radix_tree_root	*tree,
	xfs_dqid_t		id)
अणु
	काष्ठा xfs_dquot	*dqp;

restart:
	mutex_lock(&qi->qi_tree_lock);
	dqp = radix_tree_lookup(tree, id);
	अगर (!dqp) अणु
		mutex_unlock(&qi->qi_tree_lock);
		XFS_STATS_INC(mp, xs_qm_dqcachemisses);
		वापस शून्य;
	पूर्ण

	xfs_dqlock(dqp);
	अगर (dqp->q_flags & XFS_DQFLAG_FREEING) अणु
		xfs_dqunlock(dqp);
		mutex_unlock(&qi->qi_tree_lock);
		trace_xfs_dqget_मुक्तing(dqp);
		delay(1);
		जाओ restart;
	पूर्ण

	dqp->q_nrefs++;
	mutex_unlock(&qi->qi_tree_lock);

	trace_xfs_dqget_hit(dqp);
	XFS_STATS_INC(mp, xs_qm_dqcachehits);
	वापस dqp;
पूर्ण

/*
 * Try to insert a new dquot पूर्णांकo the in-core cache.  If an error occurs the
 * caller should throw away the dquot and start over.  Otherwise, the dquot
 * is वापसed locked (and held by the cache) as अगर there had been a cache
 * hit.
 */
अटल पूर्णांक
xfs_qm_dqget_cache_insert(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_quotainfo	*qi,
	काष्ठा radix_tree_root	*tree,
	xfs_dqid_t		id,
	काष्ठा xfs_dquot	*dqp)
अणु
	पूर्णांक			error;

	mutex_lock(&qi->qi_tree_lock);
	error = radix_tree_insert(tree, id, dqp);
	अगर (unlikely(error)) अणु
		/* Duplicate found!  Caller must try again. */
		WARN_ON(error != -EEXIST);
		mutex_unlock(&qi->qi_tree_lock);
		trace_xfs_dqget_dup(dqp);
		वापस error;
	पूर्ण

	/* Return a locked dquot to the caller, with a reference taken. */
	xfs_dqlock(dqp);
	dqp->q_nrefs = 1;

	qi->qi_dquots++;
	mutex_unlock(&qi->qi_tree_lock);

	वापस 0;
पूर्ण

/* Check our input parameters. */
अटल पूर्णांक
xfs_qm_dqget_checks(
	काष्ठा xfs_mount	*mp,
	xfs_dqtype_t		type)
अणु
	अगर (WARN_ON_ONCE(!XFS_IS_QUOTA_RUNNING(mp)))
		वापस -ESRCH;

	चयन (type) अणु
	हाल XFS_DQTYPE_USER:
		अगर (!XFS_IS_UQUOTA_ON(mp))
			वापस -ESRCH;
		वापस 0;
	हाल XFS_DQTYPE_GROUP:
		अगर (!XFS_IS_GQUOTA_ON(mp))
			वापस -ESRCH;
		वापस 0;
	हाल XFS_DQTYPE_PROJ:
		अगर (!XFS_IS_PQUOTA_ON(mp))
			वापस -ESRCH;
		वापस 0;
	शेष:
		WARN_ON_ONCE(0);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Given the file प्रणाली, id, and type (UDQUOT/GDQUOT/PDQUOT), वापस a
 * locked dquot, करोing an allocation (अगर requested) as needed.
 */
पूर्णांक
xfs_qm_dqget(
	काष्ठा xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	bool			can_alloc,
	काष्ठा xfs_dquot	**O_dqpp)
अणु
	काष्ठा xfs_quotainfo	*qi = mp->m_quotainfo;
	काष्ठा radix_tree_root	*tree = xfs_dquot_tree(qi, type);
	काष्ठा xfs_dquot	*dqp;
	पूर्णांक			error;

	error = xfs_qm_dqget_checks(mp, type);
	अगर (error)
		वापस error;

restart:
	dqp = xfs_qm_dqget_cache_lookup(mp, qi, tree, id);
	अगर (dqp) अणु
		*O_dqpp = dqp;
		वापस 0;
	पूर्ण

	error = xfs_qm_dqपढ़ो(mp, id, type, can_alloc, &dqp);
	अगर (error)
		वापस error;

	error = xfs_qm_dqget_cache_insert(mp, qi, tree, id, dqp);
	अगर (error) अणु
		/*
		 * Duplicate found. Just throw away the new dquot and start
		 * over.
		 */
		xfs_qm_dqdestroy(dqp);
		XFS_STATS_INC(mp, xs_qm_dquot_dups);
		जाओ restart;
	पूर्ण

	trace_xfs_dqget_miss(dqp);
	*O_dqpp = dqp;
	वापस 0;
पूर्ण

/*
 * Given a dquot id and type, पढ़ो and initialize a dquot from the on-disk
 * metadata.  This function is only क्रम use during quota initialization so
 * it ignores the dquot cache assuming that the dquot shrinker isn't set up.
 * The caller is responsible क्रम _qm_dqdestroy'ing the वापसed dquot.
 */
पूर्णांक
xfs_qm_dqget_uncached(
	काष्ठा xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	काष्ठा xfs_dquot	**dqpp)
अणु
	पूर्णांक			error;

	error = xfs_qm_dqget_checks(mp, type);
	अगर (error)
		वापस error;

	वापस xfs_qm_dqपढ़ो(mp, id, type, 0, dqpp);
पूर्ण

/* Return the quota id क्रम a given inode and type. */
xfs_dqid_t
xfs_qm_id_क्रम_quotatype(
	काष्ठा xfs_inode	*ip,
	xfs_dqtype_t		type)
अणु
	चयन (type) अणु
	हाल XFS_DQTYPE_USER:
		वापस i_uid_पढ़ो(VFS_I(ip));
	हाल XFS_DQTYPE_GROUP:
		वापस i_gid_पढ़ो(VFS_I(ip));
	हाल XFS_DQTYPE_PROJ:
		वापस ip->i_projid;
	पूर्ण
	ASSERT(0);
	वापस 0;
पूर्ण

/*
 * Return the dquot क्रम a given inode and type.  If @can_alloc is true, then
 * allocate blocks अगर needed.  The inode's ILOCK must be held and it must not
 * have alपढ़ोy had an inode attached.
 */
पूर्णांक
xfs_qm_dqget_inode(
	काष्ठा xfs_inode	*ip,
	xfs_dqtype_t		type,
	bool			can_alloc,
	काष्ठा xfs_dquot	**O_dqpp)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_quotainfo	*qi = mp->m_quotainfo;
	काष्ठा radix_tree_root	*tree = xfs_dquot_tree(qi, type);
	काष्ठा xfs_dquot	*dqp;
	xfs_dqid_t		id;
	पूर्णांक			error;

	error = xfs_qm_dqget_checks(mp, type);
	अगर (error)
		वापस error;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT(xfs_inode_dquot(ip, type) == शून्य);

	id = xfs_qm_id_क्रम_quotatype(ip, type);

restart:
	dqp = xfs_qm_dqget_cache_lookup(mp, qi, tree, id);
	अगर (dqp) अणु
		*O_dqpp = dqp;
		वापस 0;
	पूर्ण

	/*
	 * Dquot cache miss. We करोn't want to keep the inode lock across
	 * a (potential) disk पढ़ो. Also we करोn't want to deal with the lock
	 * ordering between quotainode and this inode. OTOH, dropping the inode
	 * lock here means dealing with a chown that can happen beक्रमe
	 * we re-acquire the lock.
	 */
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	error = xfs_qm_dqपढ़ो(mp, id, type, can_alloc, &dqp);
	xfs_ilock(ip, XFS_ILOCK_EXCL);
	अगर (error)
		वापस error;

	/*
	 * A dquot could be attached to this inode by now, since we had
	 * dropped the ilock.
	 */
	अगर (xfs_this_quota_on(mp, type)) अणु
		काष्ठा xfs_dquot	*dqp1;

		dqp1 = xfs_inode_dquot(ip, type);
		अगर (dqp1) अणु
			xfs_qm_dqdestroy(dqp);
			dqp = dqp1;
			xfs_dqlock(dqp);
			जाओ dqret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* inode stays locked on वापस */
		xfs_qm_dqdestroy(dqp);
		वापस -ESRCH;
	पूर्ण

	error = xfs_qm_dqget_cache_insert(mp, qi, tree, id, dqp);
	अगर (error) अणु
		/*
		 * Duplicate found. Just throw away the new dquot and start
		 * over.
		 */
		xfs_qm_dqdestroy(dqp);
		XFS_STATS_INC(mp, xs_qm_dquot_dups);
		जाओ restart;
	पूर्ण

dqret:
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	trace_xfs_dqget_miss(dqp);
	*O_dqpp = dqp;
	वापस 0;
पूर्ण

/*
 * Starting at @id and progressing upwards, look क्रम an initialized incore
 * dquot, lock it, and वापस it.
 */
पूर्णांक
xfs_qm_dqget_next(
	काष्ठा xfs_mount	*mp,
	xfs_dqid_t		id,
	xfs_dqtype_t		type,
	काष्ठा xfs_dquot	**dqpp)
अणु
	काष्ठा xfs_dquot	*dqp;
	पूर्णांक			error = 0;

	*dqpp = शून्य;
	क्रम (; !error; error = xfs_dq_get_next_id(mp, type, &id)) अणु
		error = xfs_qm_dqget(mp, id, type, false, &dqp);
		अगर (error == -ENOENT)
			जारी;
		अन्यथा अगर (error != 0)
			अवरोध;

		अगर (!XFS_IS_DQUOT_UNINITIALIZED(dqp)) अणु
			*dqpp = dqp;
			वापस 0;
		पूर्ण

		xfs_qm_dqput(dqp);
	पूर्ण

	वापस error;
पूर्ण

/*
 * Release a reference to the dquot (decrement ref-count) and unlock it.
 *
 * If there is a group quota attached to this dquot, carefully release that
 * too without tripping over deadlocks'n'stuff.
 */
व्योम
xfs_qm_dqput(
	काष्ठा xfs_dquot	*dqp)
अणु
	ASSERT(dqp->q_nrefs > 0);
	ASSERT(XFS_DQ_IS_LOCKED(dqp));

	trace_xfs_dqput(dqp);

	अगर (--dqp->q_nrefs == 0) अणु
		काष्ठा xfs_quotainfo	*qi = dqp->q_mount->m_quotainfo;
		trace_xfs_dqput_मुक्त(dqp);

		अगर (list_lru_add(&qi->qi_lru, &dqp->q_lru))
			XFS_STATS_INC(dqp->q_mount, xs_qm_dquot_unused);
	पूर्ण
	xfs_dqunlock(dqp);
पूर्ण

/*
 * Release a dquot. Flush it अगर dirty, then dqput() it.
 * dquot must not be locked.
 */
व्योम
xfs_qm_dqrele(
	काष्ठा xfs_dquot	*dqp)
अणु
	अगर (!dqp)
		वापस;

	trace_xfs_dqrele(dqp);

	xfs_dqlock(dqp);
	/*
	 * We करोn't care to flush it अगर the dquot is dirty here.
	 * That will create stutters that we want to aव्योम.
	 * Instead we करो a delayed ग_लिखो when we try to reclaim
	 * a dirty dquot. Also xfs_sync will take part of the burden...
	 */
	xfs_qm_dqput(dqp);
पूर्ण

/*
 * This is the dquot flushing I/O completion routine.  It is called
 * from पूर्णांकerrupt level when the buffer containing the dquot is
 * flushed to disk.  It is responsible क्रम removing the dquot logitem
 * from the AIL अगर it has not been re-logged, and unlocking the dquot's
 * flush lock. This behavior is very similar to that of inodes..
 */
अटल व्योम
xfs_qm_dqflush_करोne(
	काष्ठा xfs_log_item	*lip)
अणु
	काष्ठा xfs_dq_logitem	*qip = (काष्ठा xfs_dq_logitem *)lip;
	काष्ठा xfs_dquot	*dqp = qip->qli_dquot;
	काष्ठा xfs_ail		*ailp = lip->li_ailp;
	xfs_lsn_t		tail_lsn;

	/*
	 * We only want to pull the item from the AIL अगर its
	 * location in the log has not changed since we started the flush.
	 * Thus, we only bother अगर the dquot's lsn has
	 * not changed. First we check the lsn outside the lock
	 * since it's cheaper, and then we recheck जबतक
	 * holding the lock beक्रमe removing the dquot from the AIL.
	 */
	अगर (test_bit(XFS_LI_IN_AIL, &lip->li_flags) &&
	    ((lip->li_lsn == qip->qli_flush_lsn) ||
	     test_bit(XFS_LI_FAILED, &lip->li_flags))) अणु

		spin_lock(&ailp->ail_lock);
		xfs_clear_li_failed(lip);
		अगर (lip->li_lsn == qip->qli_flush_lsn) अणु
			/* xfs_ail_update_finish() drops the AIL lock */
			tail_lsn = xfs_ail_delete_one(ailp, lip);
			xfs_ail_update_finish(ailp, tail_lsn);
		पूर्ण अन्यथा अणु
			spin_unlock(&ailp->ail_lock);
		पूर्ण
	पूर्ण

	/*
	 * Release the dq's flush lock since we're करोne with it.
	 */
	xfs_dqfunlock(dqp);
पूर्ण

व्योम
xfs_buf_dquot_ioकरोne(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_log_item	*lip, *n;

	list_क्रम_each_entry_safe(lip, n, &bp->b_li_list, li_bio_list) अणु
		list_del_init(&lip->li_bio_list);
		xfs_qm_dqflush_करोne(lip);
	पूर्ण
पूर्ण

व्योम
xfs_buf_dquot_io_fail(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_log_item	*lip;

	spin_lock(&bp->b_mount->m_ail->ail_lock);
	list_क्रम_each_entry(lip, &bp->b_li_list, li_bio_list)
		xfs_set_li_failed(lip, bp);
	spin_unlock(&bp->b_mount->m_ail->ail_lock);
पूर्ण

/* Check incore dquot क्रम errors beक्रमe we flush. */
अटल xfs_failaddr_t
xfs_qm_dqflush_check(
	काष्ठा xfs_dquot	*dqp)
अणु
	xfs_dqtype_t		type = xfs_dquot_type(dqp);

	अगर (type != XFS_DQTYPE_USER &&
	    type != XFS_DQTYPE_GROUP &&
	    type != XFS_DQTYPE_PROJ)
		वापस __this_address;

	अगर (dqp->q_id == 0)
		वापस शून्य;

	अगर (dqp->q_blk.softlimit && dqp->q_blk.count > dqp->q_blk.softlimit &&
	    !dqp->q_blk.समयr)
		वापस __this_address;

	अगर (dqp->q_ino.softlimit && dqp->q_ino.count > dqp->q_ino.softlimit &&
	    !dqp->q_ino.समयr)
		वापस __this_address;

	अगर (dqp->q_rtb.softlimit && dqp->q_rtb.count > dqp->q_rtb.softlimit &&
	    !dqp->q_rtb.समयr)
		वापस __this_address;

	/* bigसमय flag should never be set on root dquots */
	अगर (dqp->q_type & XFS_DQTYPE_BIGTIME) अणु
		अगर (!xfs_sb_version_hasbigसमय(&dqp->q_mount->m_sb))
			वापस __this_address;
		अगर (dqp->q_id == 0)
			वापस __this_address;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Write a modअगरied dquot to disk.
 * The dquot must be locked and the flush lock too taken by caller.
 * The flush lock will not be unlocked until the dquot reaches the disk,
 * but the dquot is मुक्त to be unlocked and modअगरied by the caller
 * in the पूर्णांकerim. Dquot is still locked on वापस. This behavior is
 * identical to that of inodes.
 */
पूर्णांक
xfs_qm_dqflush(
	काष्ठा xfs_dquot	*dqp,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_mount	*mp = dqp->q_mount;
	काष्ठा xfs_log_item	*lip = &dqp->q_logitem.qli_item;
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_dqblk	*dqblk;
	xfs_failaddr_t		fa;
	पूर्णांक			error;

	ASSERT(XFS_DQ_IS_LOCKED(dqp));
	ASSERT(!completion_करोne(&dqp->q_flush));

	trace_xfs_dqflush(dqp);

	*bpp = शून्य;

	xfs_qm_dqunpin_रुको(dqp);

	/*
	 * Get the buffer containing the on-disk dquot
	 */
	error = xfs_trans_पढ़ो_buf(mp, शून्य, mp->m_ddev_targp, dqp->q_blkno,
				   mp->m_quotainfo->qi_dqchunklen, XBF_TRYLOCK,
				   &bp, &xfs_dquot_buf_ops);
	अगर (error == -EAGAIN)
		जाओ out_unlock;
	अगर (error)
		जाओ out_पात;

	fa = xfs_qm_dqflush_check(dqp);
	अगर (fa) अणु
		xfs_alert(mp, "corrupt dquot ID 0x%x in memory at %pS",
				dqp->q_id, fa);
		xfs_buf_rअन्यथा(bp);
		error = -EFSCORRUPTED;
		जाओ out_पात;
	पूर्ण

	/* Flush the incore dquot to the ondisk buffer. */
	dqblk = bp->b_addr + dqp->q_bufoffset;
	xfs_dquot_to_disk(&dqblk->dd_diskdq, dqp);

	/*
	 * Clear the dirty field and remember the flush lsn क्रम later use.
	 */
	dqp->q_flags &= ~XFS_DQFLAG_सूचीTY;

	xfs_trans_ail_copy_lsn(mp->m_ail, &dqp->q_logitem.qli_flush_lsn,
					&dqp->q_logitem.qli_item.li_lsn);

	/*
	 * copy the lsn पूर्णांकo the on-disk dquot now जबतक we have the in memory
	 * dquot here. This can't be करोne later in the ग_लिखो verअगरier as we
	 * can't get access to the log item at that poपूर्णांक in समय.
	 *
	 * We also calculate the CRC here so that the on-disk dquot in the
	 * buffer always has a valid CRC. This ensures there is no possibility
	 * of a dquot without an up-to-date CRC getting to disk.
	 */
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		dqblk->dd_lsn = cpu_to_be64(dqp->q_logitem.qli_item.li_lsn);
		xfs_update_cksum((अक्षर *)dqblk, माप(काष्ठा xfs_dqblk),
				 XFS_DQUOT_CRC_OFF);
	पूर्ण

	/*
	 * Attach the dquot to the buffer so that we can हटाओ this dquot from
	 * the AIL and release the flush lock once the dquot is synced to disk.
	 */
	bp->b_flags |= _XBF_DQUOTS;
	list_add_tail(&dqp->q_logitem.qli_item.li_bio_list, &bp->b_li_list);

	/*
	 * If the buffer is pinned then push on the log so we won't
	 * get stuck रुकोing in the ग_लिखो क्रम too दीर्घ.
	 */
	अगर (xfs_buf_ispinned(bp)) अणु
		trace_xfs_dqflush_क्रमce(dqp);
		xfs_log_क्रमce(mp, 0);
	पूर्ण

	trace_xfs_dqflush_करोne(dqp);
	*bpp = bp;
	वापस 0;

out_पात:
	dqp->q_flags &= ~XFS_DQFLAG_सूचीTY;
	xfs_trans_ail_delete(lip, 0);
	xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
out_unlock:
	xfs_dqfunlock(dqp);
	वापस error;
पूर्ण

/*
 * Lock two xfs_dquot काष्ठाures.
 *
 * To aव्योम deadlocks we always lock the quota काष्ठाure with
 * the lowerd id first.
 */
व्योम
xfs_dqlock2(
	काष्ठा xfs_dquot	*d1,
	काष्ठा xfs_dquot	*d2)
अणु
	अगर (d1 && d2) अणु
		ASSERT(d1 != d2);
		अगर (d1->q_id > d2->q_id) अणु
			mutex_lock(&d2->q_qlock);
			mutex_lock_nested(&d1->q_qlock, XFS_QLOCK_NESTED);
		पूर्ण अन्यथा अणु
			mutex_lock(&d1->q_qlock);
			mutex_lock_nested(&d2->q_qlock, XFS_QLOCK_NESTED);
		पूर्ण
	पूर्ण अन्यथा अगर (d1) अणु
		mutex_lock(&d1->q_qlock);
	पूर्ण अन्यथा अगर (d2) अणु
		mutex_lock(&d2->q_qlock);
	पूर्ण
पूर्ण

पूर्णांक __init
xfs_qm_init(व्योम)
अणु
	xfs_qm_dqzone = kmem_cache_create("xfs_dquot",
					  माप(काष्ठा xfs_dquot),
					  0, 0, शून्य);
	अगर (!xfs_qm_dqzone)
		जाओ out;

	xfs_qm_dqtrxzone = kmem_cache_create("xfs_dqtrx",
					     माप(काष्ठा xfs_dquot_acct),
					     0, 0, शून्य);
	अगर (!xfs_qm_dqtrxzone)
		जाओ out_मुक्त_dqzone;

	वापस 0;

out_मुक्त_dqzone:
	kmem_cache_destroy(xfs_qm_dqzone);
out:
	वापस -ENOMEM;
पूर्ण

व्योम
xfs_qm_निकास(व्योम)
अणु
	kmem_cache_destroy(xfs_qm_dqtrxzone);
	kmem_cache_destroy(xfs_qm_dqzone);
पूर्ण

/*
 * Iterate every dquot of a particular type.  The caller must ensure that the
 * particular quota type is active.  iter_fn can वापस negative error codes,
 * or -ECANCELED to indicate that it wants to stop iterating.
 */
पूर्णांक
xfs_qm_dqiterate(
	काष्ठा xfs_mount	*mp,
	xfs_dqtype_t		type,
	xfs_qm_dqiterate_fn	iter_fn,
	व्योम			*priv)
अणु
	काष्ठा xfs_dquot	*dq;
	xfs_dqid_t		id = 0;
	पूर्णांक			error;

	करो अणु
		error = xfs_qm_dqget_next(mp, id, type, &dq);
		अगर (error == -ENOENT)
			वापस 0;
		अगर (error)
			वापस error;

		error = iter_fn(dq, type, priv);
		id = dq->q_id;
		xfs_qm_dqput(dq);
	पूर्ण जबतक (error == 0 && id != 0);

	वापस error;
पूर्ण
