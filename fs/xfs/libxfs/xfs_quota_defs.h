<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_QUOTA_DEFS_H__
#घोषणा __XFS_QUOTA_DEFS_H__

/*
 * Quota definitions shared between user and kernel source trees.
 */

/*
 * Even though users may not have quota limits occupying all 64-bits,
 * they may need 64-bit accounting. Hence, 64-bit quota-counters,
 * and quota-limits. This is a waste in the common हाल, but hey ...
 */
प्रकार uपूर्णांक64_t	xfs_qcnt_t;
प्रकार uपूर्णांक16_t	xfs_qwarncnt_t;

प्रकार uपूर्णांक8_t		xfs_dqtype_t;

#घोषणा XFS_DQTYPE_STRINGS \
	अणु XFS_DQTYPE_USER,	"USER" पूर्ण, \
	अणु XFS_DQTYPE_PROJ,	"PROJ" पूर्ण, \
	अणु XFS_DQTYPE_GROUP,	"GROUP" पूर्ण, \
	अणु XFS_DQTYPE_BIGTIME,	"BIGTIME" पूर्ण

/*
 * flags क्रम q_flags field in the dquot.
 */
#घोषणा XFS_DQFLAG_सूचीTY	(1 << 0)	/* dquot is dirty */
#घोषणा XFS_DQFLAG_FREEING	(1 << 1)	/* dquot is being torn करोwn */

#घोषणा XFS_DQFLAG_STRINGS \
	अणु XFS_DQFLAG_सूचीTY,	"DIRTY" पूर्ण, \
	अणु XFS_DQFLAG_FREEING,	"FREEING" पूर्ण

/*
 * We have the possibility of all three quota types being active at once, and
 * hence मुक्त space modअगरication requires modअगरication of all three current
 * dquots in a single transaction. For this हाल we need to have a reservation
 * of at least 3 dquots.
 *
 * However, a chmod operation can change both UID and GID in a single
 * transaction, resulting in requiring अणुold, newपूर्ण x अणुuid, gidपूर्ण dquots to be
 * modअगरied. Hence क्रम this हाल we need to reserve space क्रम at least 4 dquots.
 *
 * And in the worst हाल, there's a नाम operation that can be modअगरying up to
 * 4 inodes with dquots attached to them. In reality, the only inodes that can
 * have their dquots modअगरied are the source and destination directory inodes
 * due to directory name creation and removal. That can require space allocation
 * and/or मुक्तing on both directory inodes, and hence all three dquots on each
 * inode can be modअगरied. And अगर the directories are world ग_लिखोable, all the
 * dquots can be unique and so 6 dquots can be modअगरied....
 *
 * And, of course, we also need to take पूर्णांकo account the dquot log क्रमmat item
 * used to describe each dquot.
 */
#घोषणा XFS_DQUOT_LOGRES(mp)	\
	((माप(काष्ठा xfs_dq_logक्रमmat) + माप(काष्ठा xfs_disk_dquot)) * 6)

#घोषणा XFS_IS_QUOTA_RUNNING(mp)	((mp)->m_qflags & XFS_ALL_QUOTA_ACCT)
#घोषणा XFS_IS_UQUOTA_RUNNING(mp)	((mp)->m_qflags & XFS_UQUOTA_ACCT)
#घोषणा XFS_IS_PQUOTA_RUNNING(mp)	((mp)->m_qflags & XFS_PQUOTA_ACCT)
#घोषणा XFS_IS_GQUOTA_RUNNING(mp)	((mp)->m_qflags & XFS_GQUOTA_ACCT)
#घोषणा XFS_IS_UQUOTA_ENFORCED(mp)	((mp)->m_qflags & XFS_UQUOTA_ENFD)
#घोषणा XFS_IS_GQUOTA_ENFORCED(mp)	((mp)->m_qflags & XFS_GQUOTA_ENFD)
#घोषणा XFS_IS_PQUOTA_ENFORCED(mp)	((mp)->m_qflags & XFS_PQUOTA_ENFD)

/*
 * Incore only flags क्रम quotaoff - these bits get cleared when quota(s)
 * are in the process of getting turned off. These flags are in m_qflags but
 * never in sb_qflags.
 */
#घोषणा XFS_UQUOTA_ACTIVE	0x1000  /* uquotas are being turned off */
#घोषणा XFS_GQUOTA_ACTIVE	0x2000  /* gquotas are being turned off */
#घोषणा XFS_PQUOTA_ACTIVE	0x4000  /* pquotas are being turned off */
#घोषणा XFS_ALL_QUOTA_ACTIVE	\
	(XFS_UQUOTA_ACTIVE | XFS_GQUOTA_ACTIVE | XFS_PQUOTA_ACTIVE)

/*
 * Checking XFS_IS_*QUOTA_ON() जबतक holding any inode lock guarantees
 * quota will be not be चयनed off as दीर्घ as that inode lock is held.
 */
#घोषणा XFS_IS_QUOTA_ON(mp)	((mp)->m_qflags & (XFS_UQUOTA_ACTIVE | \
						   XFS_GQUOTA_ACTIVE | \
						   XFS_PQUOTA_ACTIVE))
#घोषणा XFS_IS_UQUOTA_ON(mp)	((mp)->m_qflags & XFS_UQUOTA_ACTIVE)
#घोषणा XFS_IS_GQUOTA_ON(mp)	((mp)->m_qflags & XFS_GQUOTA_ACTIVE)
#घोषणा XFS_IS_PQUOTA_ON(mp)	((mp)->m_qflags & XFS_PQUOTA_ACTIVE)

/*
 * Flags to tell various functions what to करो. Not all of these are meaningful
 * to a single function. None of these XFS_QMOPT_* flags are meant to have
 * persistent values (ie. their values can and will change between versions)
 */
#घोषणा XFS_QMOPT_UQUOTA	0x0000004 /* user dquot requested */
#घोषणा XFS_QMOPT_PQUOTA	0x0000008 /* project dquot requested */
#घोषणा XFS_QMOPT_FORCE_RES	0x0000010 /* ignore quota limits */
#घोषणा XFS_QMOPT_SBVERSION	0x0000040 /* change superblock version num */
#घोषणा XFS_QMOPT_GQUOTA	0x0002000 /* group dquot requested */

/*
 * flags to xfs_trans_mod_dquot to indicate which field needs to be
 * modअगरied.
 */
#घोषणा XFS_QMOPT_RES_REGBLKS	0x0010000
#घोषणा XFS_QMOPT_RES_RTBLKS	0x0020000
#घोषणा XFS_QMOPT_BCOUNT	0x0040000
#घोषणा XFS_QMOPT_ICOUNT	0x0080000
#घोषणा XFS_QMOPT_RTBCOUNT	0x0100000
#घोषणा XFS_QMOPT_DELBCOUNT	0x0200000
#घोषणा XFS_QMOPT_DELRTBCOUNT	0x0400000
#घोषणा XFS_QMOPT_RES_INOS	0x0800000

/*
 * flags क्रम dqalloc.
 */
#घोषणा XFS_QMOPT_INHERIT	0x1000000

/*
 * flags to xfs_trans_mod_dquot.
 */
#घोषणा XFS_TRANS_DQ_RES_BLKS	XFS_QMOPT_RES_REGBLKS
#घोषणा XFS_TRANS_DQ_RES_RTBLKS	XFS_QMOPT_RES_RTBLKS
#घोषणा XFS_TRANS_DQ_RES_INOS	XFS_QMOPT_RES_INOS
#घोषणा XFS_TRANS_DQ_BCOUNT	XFS_QMOPT_BCOUNT
#घोषणा XFS_TRANS_DQ_DELBCOUNT	XFS_QMOPT_DELBCOUNT
#घोषणा XFS_TRANS_DQ_ICOUNT	XFS_QMOPT_ICOUNT
#घोषणा XFS_TRANS_DQ_RTBCOUNT	XFS_QMOPT_RTBCOUNT
#घोषणा XFS_TRANS_DQ_DELRTBCOUNT XFS_QMOPT_DELRTBCOUNT


#घोषणा XFS_QMOPT_QUOTALL	\
		(XFS_QMOPT_UQUOTA | XFS_QMOPT_PQUOTA | XFS_QMOPT_GQUOTA)
#घोषणा XFS_QMOPT_RESBLK_MASK	(XFS_QMOPT_RES_REGBLKS | XFS_QMOPT_RES_RTBLKS)

बाह्य xfs_failaddr_t xfs_dquot_verअगरy(काष्ठा xfs_mount *mp,
		काष्ठा xfs_disk_dquot *ddq, xfs_dqid_t id);
बाह्य xfs_failaddr_t xfs_dqblk_verअगरy(काष्ठा xfs_mount *mp,
		काष्ठा xfs_dqblk *dqb, xfs_dqid_t id);
बाह्य पूर्णांक xfs_calc_dquots_per_chunk(अचिन्हित पूर्णांक nbblks);
बाह्य व्योम xfs_dqblk_repair(काष्ठा xfs_mount *mp, काष्ठा xfs_dqblk *dqb,
		xfs_dqid_t id, xfs_dqtype_t type);

काष्ठा xfs_dquot;
समय64_t xfs_dquot_from_disk_ts(काष्ठा xfs_disk_dquot *ddq,
		__be32 dसमयr);
__be32 xfs_dquot_to_disk_ts(काष्ठा xfs_dquot *ddq, समय64_t समयr);

#पूर्ण_अगर	/* __XFS_QUOTA_H__ */
