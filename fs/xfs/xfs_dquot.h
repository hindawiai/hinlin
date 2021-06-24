<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_DQUOT_H__
#घोषणा __XFS_DQUOT_H__

/*
 * Dquots are काष्ठाures that hold quota inक्रमmation about a user or a group,
 * much like inodes are क्रम files. In fact, dquots share many अक्षरacteristics
 * with inodes. However, dquots can also be a centralized resource, relative
 * to a collection of inodes. In this respect, dquots share some अक्षरacteristics
 * of the superblock.
 * XFS dquots exploit both those in its algorithms. They make every attempt
 * to not be a bottleneck when quotas are on and have minimal impact, अगर any,
 * when quotas are off.
 */

काष्ठा xfs_mount;
काष्ठा xfs_trans;

क्रमागत अणु
	XFS_QLOWSP_1_PCNT = 0,
	XFS_QLOWSP_3_PCNT,
	XFS_QLOWSP_5_PCNT,
	XFS_QLOWSP_MAX
पूर्ण;

काष्ठा xfs_dquot_res अणु
	/* Total resources allocated and reserved. */
	xfs_qcnt_t		reserved;

	/* Total resources allocated. */
	xfs_qcnt_t		count;

	/* Absolute and preferred limits. */
	xfs_qcnt_t		hardlimit;
	xfs_qcnt_t		softlimit;

	/*
	 * For root dquots, this is the शेष grace period, in seconds.
	 * Otherwise, this is when the quota grace period expires,
	 * in seconds since the Unix epoch.
	 */
	समय64_t		समयr;

	/*
	 * For root dquots, this is the maximum number of warnings that will
	 * be issued क्रम this quota type.  Otherwise, this is the number of
	 * warnings issued against this quota.  Note that none of this is
	 * implemented.
	 */
	xfs_qwarncnt_t		warnings;
पूर्ण;

/*
 * The incore dquot काष्ठाure
 */
काष्ठा xfs_dquot अणु
	काष्ठा list_head	q_lru;
	काष्ठा xfs_mount	*q_mount;
	xfs_dqtype_t		q_type;
	uपूर्णांक16_t		q_flags;
	xfs_dqid_t		q_id;
	uपूर्णांक			q_nrefs;
	पूर्णांक			q_bufoffset;
	xfs_daddr_t		q_blkno;
	xfs_fileoff_t		q_fileoffset;

	काष्ठा xfs_dquot_res	q_blk;	/* regular blocks */
	काष्ठा xfs_dquot_res	q_ino;	/* inodes */
	काष्ठा xfs_dquot_res	q_rtb;	/* realसमय blocks */

	काष्ठा xfs_dq_logitem	q_logitem;

	xfs_qcnt_t		q_pपुनः_स्मृति_lo_wmark;
	xfs_qcnt_t		q_pपुनः_स्मृति_hi_wmark;
	पूर्णांक64_t			q_low_space[XFS_QLOWSP_MAX];
	काष्ठा mutex		q_qlock;
	काष्ठा completion	q_flush;
	atomic_t		q_pincount;
	काष्ठा रुको_queue_head	q_pinरुको;
पूर्ण;

/*
 * Lock hierarchy क्रम q_qlock:
 *	XFS_QLOCK_NORMAL is the implicit शेष,
 *	XFS_QLOCK_NESTED is the dquot with the higher id in xfs_dqlock2
 */
क्रमागत अणु
	XFS_QLOCK_NORMAL = 0,
	XFS_QLOCK_NESTED,
पूर्ण;

/*
 * Manage the q_flush completion queue embedded in the dquot. This completion
 * queue synchronizes processes attempting to flush the in-core dquot back to
 * disk.
 */
अटल अंतरभूत व्योम xfs_dqflock(काष्ठा xfs_dquot *dqp)
अणु
	रुको_क्रम_completion(&dqp->q_flush);
पूर्ण

अटल अंतरभूत bool xfs_dqflock_noरुको(काष्ठा xfs_dquot *dqp)
अणु
	वापस try_रुको_क्रम_completion(&dqp->q_flush);
पूर्ण

अटल अंतरभूत व्योम xfs_dqfunlock(काष्ठा xfs_dquot *dqp)
अणु
	complete(&dqp->q_flush);
पूर्ण

अटल अंतरभूत पूर्णांक xfs_dqlock_noरुको(काष्ठा xfs_dquot *dqp)
अणु
	वापस mutex_trylock(&dqp->q_qlock);
पूर्ण

अटल अंतरभूत व्योम xfs_dqlock(काष्ठा xfs_dquot *dqp)
अणु
	mutex_lock(&dqp->q_qlock);
पूर्ण

अटल अंतरभूत व्योम xfs_dqunlock(काष्ठा xfs_dquot *dqp)
अणु
	mutex_unlock(&dqp->q_qlock);
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_dquot_type(स्थिर काष्ठा xfs_dquot *dqp)
अणु
	वापस dqp->q_type & XFS_DQTYPE_REC_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक xfs_this_quota_on(काष्ठा xfs_mount *mp, xfs_dqtype_t type)
अणु
	चयन (type) अणु
	हाल XFS_DQTYPE_USER:
		वापस XFS_IS_UQUOTA_ON(mp);
	हाल XFS_DQTYPE_GROUP:
		वापस XFS_IS_GQUOTA_ON(mp);
	हाल XFS_DQTYPE_PROJ:
		वापस XFS_IS_PQUOTA_ON(mp);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा xfs_dquot *xfs_inode_dquot(
	काष्ठा xfs_inode	*ip,
	xfs_dqtype_t		type)
अणु
	चयन (type) अणु
	हाल XFS_DQTYPE_USER:
		वापस ip->i_udquot;
	हाल XFS_DQTYPE_GROUP:
		वापस ip->i_gdquot;
	हाल XFS_DQTYPE_PROJ:
		वापस ip->i_pdquot;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

/* Decide अगर the dquot's limits are actually being enक्रमced. */
अटल अंतरभूत bool
xfs_dquot_is_enक्रमced(
	स्थिर काष्ठा xfs_dquot	*dqp)
अणु
	चयन (xfs_dquot_type(dqp)) अणु
	हाल XFS_DQTYPE_USER:
		वापस XFS_IS_UQUOTA_ENFORCED(dqp->q_mount);
	हाल XFS_DQTYPE_GROUP:
		वापस XFS_IS_GQUOTA_ENFORCED(dqp->q_mount);
	हाल XFS_DQTYPE_PROJ:
		वापस XFS_IS_PQUOTA_ENFORCED(dqp->q_mount);
	पूर्ण
	ASSERT(0);
	वापस false;
पूर्ण

/*
 * Check whether a dquot is under low मुक्त space conditions. We assume the quota
 * is enabled and enक्रमced.
 */
अटल अंतरभूत bool xfs_dquot_lowsp(काष्ठा xfs_dquot *dqp)
अणु
	पूर्णांक64_t मुक्तsp;

	मुक्तsp = dqp->q_blk.hardlimit - dqp->q_blk.reserved;
	अगर (मुक्तsp < dqp->q_low_space[XFS_QLOWSP_1_PCNT])
		वापस true;

	वापस false;
पूर्ण

व्योम xfs_dquot_to_disk(काष्ठा xfs_disk_dquot *ddqp, काष्ठा xfs_dquot *dqp);

#घोषणा XFS_DQ_IS_LOCKED(dqp)	(mutex_is_locked(&((dqp)->q_qlock)))
#घोषणा XFS_DQ_IS_सूचीTY(dqp)	((dqp)->q_flags & XFS_DQFLAG_सूचीTY)

व्योम		xfs_qm_dqdestroy(काष्ठा xfs_dquot *dqp);
पूर्णांक		xfs_qm_dqflush(काष्ठा xfs_dquot *dqp, काष्ठा xfs_buf **bpp);
व्योम		xfs_qm_dqunpin_रुको(काष्ठा xfs_dquot *dqp);
व्योम		xfs_qm_adjust_dqसमयrs(काष्ठा xfs_dquot *d);
व्योम		xfs_qm_adjust_dqlimits(काष्ठा xfs_dquot *d);
xfs_dqid_t	xfs_qm_id_क्रम_quotatype(काष्ठा xfs_inode *ip,
				xfs_dqtype_t type);
पूर्णांक		xfs_qm_dqget(काष्ठा xfs_mount *mp, xfs_dqid_t id,
				xfs_dqtype_t type, bool can_alloc,
				काष्ठा xfs_dquot **dqpp);
पूर्णांक		xfs_qm_dqget_inode(काष्ठा xfs_inode *ip, xfs_dqtype_t type,
				bool can_alloc, काष्ठा xfs_dquot **dqpp);
पूर्णांक		xfs_qm_dqget_next(काष्ठा xfs_mount *mp, xfs_dqid_t id,
				xfs_dqtype_t type, काष्ठा xfs_dquot **dqpp);
पूर्णांक		xfs_qm_dqget_uncached(काष्ठा xfs_mount *mp,
				xfs_dqid_t id, xfs_dqtype_t type,
				काष्ठा xfs_dquot **dqpp);
व्योम		xfs_qm_dqput(काष्ठा xfs_dquot *dqp);

व्योम		xfs_dqlock2(काष्ठा xfs_dquot *, काष्ठा xfs_dquot *);

व्योम		xfs_dquot_set_pपुनः_स्मृति_limits(काष्ठा xfs_dquot *);

अटल अंतरभूत काष्ठा xfs_dquot *xfs_qm_dqhold(काष्ठा xfs_dquot *dqp)
अणु
	xfs_dqlock(dqp);
	dqp->q_nrefs++;
	xfs_dqunlock(dqp);
	वापस dqp;
पूर्ण

प्रकार पूर्णांक (*xfs_qm_dqiterate_fn)(काष्ठा xfs_dquot *dq,
		xfs_dqtype_t type, व्योम *priv);
पूर्णांक xfs_qm_dqiterate(काष्ठा xfs_mount *mp, xfs_dqtype_t type,
		xfs_qm_dqiterate_fn iter_fn, व्योम *priv);

समय64_t xfs_dquot_set_समयout(काष्ठा xfs_mount *mp, समय64_t समयout);
समय64_t xfs_dquot_set_grace_period(समय64_t grace);

#पूर्ण_अगर /* __XFS_DQUOT_H__ */
