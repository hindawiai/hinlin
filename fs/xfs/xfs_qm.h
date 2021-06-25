<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_QM_H__
#घोषणा __XFS_QM_H__

#समावेश "xfs_dquot_item.h"
#समावेश "xfs_dquot.h"

काष्ठा xfs_inode;

बाह्य काष्ठा kmem_zone	*xfs_qm_dqtrxzone;

/*
 * Number of bmaps that we ask from bmapi when करोing a quotacheck.
 * We make this restriction to keep the memory usage to a minimum.
 */
#घोषणा XFS_DQITER_MAP_SIZE	10

#घोषणा XFS_IS_DQUOT_UNINITIALIZED(dqp) ( \
	!dqp->q_blk.hardlimit && \
	!dqp->q_blk.softlimit && \
	!dqp->q_rtb.hardlimit && \
	!dqp->q_rtb.softlimit && \
	!dqp->q_ino.hardlimit && \
	!dqp->q_ino.softlimit && \
	!dqp->q_blk.count && \
	!dqp->q_rtb.count && \
	!dqp->q_ino.count)

काष्ठा xfs_quota_limits अणु
	xfs_qcnt_t		hard;	/* शेष hard limit */
	xfs_qcnt_t		soft;	/* शेष soft limit */
	समय64_t		समय;	/* limit क्रम समयrs */
	xfs_qwarncnt_t		warn;	/* limit क्रम warnings */
पूर्ण;

/* Defaults क्रम each quota type: समय limits, warn limits, usage limits */
काष्ठा xfs_def_quota अणु
	काष्ठा xfs_quota_limits	blk;
	काष्ठा xfs_quota_limits	ino;
	काष्ठा xfs_quota_limits	rtb;
पूर्ण;

/*
 * Various quota inक्रमmation क्रम inभागidual fileप्रणालीs.
 * The mount काष्ठाure keeps a poपूर्णांकer to this.
 */
काष्ठा xfs_quotainfo अणु
	काष्ठा radix_tree_root	qi_uquota_tree;
	काष्ठा radix_tree_root	qi_gquota_tree;
	काष्ठा radix_tree_root	qi_pquota_tree;
	काष्ठा mutex		qi_tree_lock;
	काष्ठा xfs_inode	*qi_uquotaip;	/* user quota inode */
	काष्ठा xfs_inode	*qi_gquotaip;	/* group quota inode */
	काष्ठा xfs_inode	*qi_pquotaip;	/* project quota inode */
	काष्ठा list_lru		qi_lru;
	पूर्णांक			qi_dquots;
	काष्ठा mutex		qi_quotaofflock;/* to serialize quotaoff */
	xfs_filblks_t		qi_dqchunklen;	/* # BBs in a chunk of dqs */
	uपूर्णांक			qi_dqperchunk;	/* # ondisk dq in above chunk */
	काष्ठा xfs_def_quota	qi_usr_शेष;
	काष्ठा xfs_def_quota	qi_grp_शेष;
	काष्ठा xfs_def_quota	qi_prj_शेष;
	काष्ठा shrinker		qi_shrinker;

	/* Minimum and maximum quota expiration बारtamp values. */
	समय64_t		qi_expiry_min;
	समय64_t		qi_expiry_max;
पूर्ण;

अटल अंतरभूत काष्ठा radix_tree_root *
xfs_dquot_tree(
	काष्ठा xfs_quotainfo	*qi,
	xfs_dqtype_t		type)
अणु
	चयन (type) अणु
	हाल XFS_DQTYPE_USER:
		वापस &qi->qi_uquota_tree;
	हाल XFS_DQTYPE_GROUP:
		वापस &qi->qi_gquota_tree;
	हाल XFS_DQTYPE_PROJ:
		वापस &qi->qi_pquota_tree;
	शेष:
		ASSERT(0);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा xfs_inode *
xfs_quota_inode(काष्ठा xfs_mount *mp, xfs_dqtype_t type)
अणु
	चयन (type) अणु
	हाल XFS_DQTYPE_USER:
		वापस mp->m_quotainfo->qi_uquotaip;
	हाल XFS_DQTYPE_GROUP:
		वापस mp->m_quotainfo->qi_gquotaip;
	हाल XFS_DQTYPE_PROJ:
		वापस mp->m_quotainfo->qi_pquotaip;
	शेष:
		ASSERT(0);
	पूर्ण
	वापस शून्य;
पूर्ण

बाह्य व्योम	xfs_trans_mod_dquot(काष्ठा xfs_trans *tp, काष्ठा xfs_dquot *dqp,
				    uपूर्णांक field, पूर्णांक64_t delta);
बाह्य व्योम	xfs_trans_dqjoin(काष्ठा xfs_trans *, काष्ठा xfs_dquot *);
बाह्य व्योम	xfs_trans_log_dquot(काष्ठा xfs_trans *, काष्ठा xfs_dquot *);

/*
 * We keep the usr, grp, and prj dquots separately so that locking will be
 * easier to करो at commit समय. All transactions that we know of at this poपूर्णांक
 * affect no more than two dquots of one type. Hence, the TRANS_MAXDQS value.
 */
क्रमागत अणु
	XFS_QM_TRANS_USR = 0,
	XFS_QM_TRANS_GRP,
	XFS_QM_TRANS_PRJ,
	XFS_QM_TRANS_DQTYPES
पूर्ण;
#घोषणा XFS_QM_TRANS_MAXDQS		2
काष्ठा xfs_dquot_acct अणु
	काष्ठा xfs_dqtrx	dqs[XFS_QM_TRANS_DQTYPES][XFS_QM_TRANS_MAXDQS];
पूर्ण;

/*
 * Users are allowed to have a usage exceeding their softlimit क्रम
 * a period this दीर्घ.
 */
#घोषणा XFS_QM_BTIMELIMIT	(7 * 24*60*60)          /* 1 week */
#घोषणा XFS_QM_RTBTIMELIMIT	(7 * 24*60*60)          /* 1 week */
#घोषणा XFS_QM_ITIMELIMIT	(7 * 24*60*60)          /* 1 week */

#घोषणा XFS_QM_BWARNLIMIT	5
#घोषणा XFS_QM_IWARNLIMIT	5
#घोषणा XFS_QM_RTBWARNLIMIT	5

बाह्य व्योम		xfs_qm_destroy_quotainfo(काष्ठा xfs_mount *);

/* dquot stuff */
बाह्य व्योम		xfs_qm_dqpurge_all(काष्ठा xfs_mount *, uपूर्णांक);
बाह्य व्योम		xfs_qm_dqrele_all_inodes(काष्ठा xfs_mount *, uपूर्णांक);

/* quota ops */
बाह्य पूर्णांक		xfs_qm_scall_trunc_qfiles(काष्ठा xfs_mount *, uपूर्णांक);
बाह्य पूर्णांक		xfs_qm_scall_getquota(काष्ठा xfs_mount *mp,
					xfs_dqid_t id,
					xfs_dqtype_t type,
					काष्ठा qc_dqblk *dst);
बाह्य पूर्णांक		xfs_qm_scall_getquota_next(काष्ठा xfs_mount *mp,
					xfs_dqid_t *id,
					xfs_dqtype_t type,
					काष्ठा qc_dqblk *dst);
बाह्य पूर्णांक		xfs_qm_scall_setqlim(काष्ठा xfs_mount *mp,
					xfs_dqid_t id,
					xfs_dqtype_t type,
					काष्ठा qc_dqblk *newlim);
बाह्य पूर्णांक		xfs_qm_scall_quotaon(काष्ठा xfs_mount *, uपूर्णांक);
बाह्य पूर्णांक		xfs_qm_scall_quotaoff(काष्ठा xfs_mount *, uपूर्णांक);

अटल अंतरभूत काष्ठा xfs_def_quota *
xfs_get_defquota(काष्ठा xfs_quotainfo *qi, xfs_dqtype_t type)
अणु
	चयन (type) अणु
	हाल XFS_DQTYPE_USER:
		वापस &qi->qi_usr_शेष;
	हाल XFS_DQTYPE_GROUP:
		वापस &qi->qi_grp_शेष;
	हाल XFS_DQTYPE_PROJ:
		वापस &qi->qi_prj_शेष;
	शेष:
		ASSERT(0);
		वापस शून्य;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* __XFS_QM_H__ */
