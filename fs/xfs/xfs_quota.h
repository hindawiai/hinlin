<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_QUOTA_H__
#घोषणा __XFS_QUOTA_H__

#समावेश "xfs_quota_defs.h"

/*
 * Kernel only quota definitions and functions
 */

काष्ठा xfs_trans;
काष्ठा xfs_buf;

/*
 * This check is करोne typically without holding the inode lock;
 * that may seem racy, but it is harmless in the context that it is used.
 * The inode cannot go inactive as दीर्घ a reference is kept, and
 * thereक्रमe अगर dquot(s) were attached, they'll stay consistent.
 * If, क्रम example, the ownership of the inode changes जबतक
 * we didn't have the inode locked, the appropriate dquot(s) will be
 * attached atomically.
 */
#घोषणा XFS_NOT_DQATTACHED(mp, ip) \
	((XFS_IS_UQUOTA_ON(mp) && (ip)->i_udquot == शून्य) || \
	 (XFS_IS_GQUOTA_ON(mp) && (ip)->i_gdquot == शून्य) || \
	 (XFS_IS_PQUOTA_ON(mp) && (ip)->i_pdquot == शून्य))

#घोषणा XFS_QM_NEED_QUOTACHECK(mp) \
	((XFS_IS_UQUOTA_ON(mp) && \
		(mp->m_sb.sb_qflags & XFS_UQUOTA_CHKD) == 0) || \
	 (XFS_IS_GQUOTA_ON(mp) && \
		(mp->m_sb.sb_qflags & XFS_GQUOTA_CHKD) == 0) || \
	 (XFS_IS_PQUOTA_ON(mp) && \
		(mp->m_sb.sb_qflags & XFS_PQUOTA_CHKD) == 0))

अटल अंतरभूत uपूर्णांक
xfs_quota_chkd_flag(
	xfs_dqtype_t		type)
अणु
	चयन (type) अणु
	हाल XFS_DQTYPE_USER:
		वापस XFS_UQUOTA_CHKD;
	हाल XFS_DQTYPE_GROUP:
		वापस XFS_GQUOTA_CHKD;
	हाल XFS_DQTYPE_PROJ:
		वापस XFS_PQUOTA_CHKD;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * The काष्ठाure kept inside the xfs_trans_t keep track of dquot changes
 * within a transaction and apply them later.
 */
काष्ठा xfs_dqtrx अणु
	काष्ठा xfs_dquot *qt_dquot;	  /* the dquot this refers to */

	uपूर्णांक64_t	qt_blk_res;	  /* blks reserved on a dquot */
	पूर्णांक64_t		qt_bcount_delta;  /* dquot blk count changes */
	पूर्णांक64_t		qt_delbcnt_delta; /* delayed dquot blk count changes */

	uपूर्णांक64_t	qt_rtblk_res;	  /* # blks reserved on a dquot */
	uपूर्णांक64_t	qt_rtblk_res_used;/* # blks used from reservation */
	पूर्णांक64_t		qt_rtbcount_delta;/* dquot realसमय blk changes */
	पूर्णांक64_t		qt_delrtb_delta;  /* delayed RT blk count changes */

	uपूर्णांक64_t	qt_ino_res;	  /* inode reserved on a dquot */
	uपूर्णांक64_t	qt_ino_res_used;  /* inodes used from the reservation */
	पूर्णांक64_t		qt_icount_delta;  /* dquot inode count changes */
पूर्ण;

#अगर_घोषित CONFIG_XFS_QUOTA
बाह्य व्योम xfs_trans_dup_dqinfo(काष्ठा xfs_trans *, काष्ठा xfs_trans *);
बाह्य व्योम xfs_trans_मुक्त_dqinfo(काष्ठा xfs_trans *);
बाह्य व्योम xfs_trans_mod_dquot_byino(काष्ठा xfs_trans *, काष्ठा xfs_inode *,
		uपूर्णांक, पूर्णांक64_t);
बाह्य व्योम xfs_trans_apply_dquot_deltas(काष्ठा xfs_trans *);
बाह्य व्योम xfs_trans_unreserve_and_mod_dquots(काष्ठा xfs_trans *);
पूर्णांक xfs_trans_reserve_quota_nblks(काष्ठा xfs_trans *tp, काष्ठा xfs_inode *ip,
		पूर्णांक64_t dblocks, पूर्णांक64_t rblocks, bool क्रमce);
बाह्य पूर्णांक xfs_trans_reserve_quota_bydquots(काष्ठा xfs_trans *,
		काष्ठा xfs_mount *, काष्ठा xfs_dquot *,
		काष्ठा xfs_dquot *, काष्ठा xfs_dquot *, पूर्णांक64_t, दीर्घ, uपूर्णांक);
पूर्णांक xfs_trans_reserve_quota_icreate(काष्ठा xfs_trans *tp,
		काष्ठा xfs_dquot *udqp, काष्ठा xfs_dquot *gdqp,
		काष्ठा xfs_dquot *pdqp, पूर्णांक64_t dblocks);

बाह्य पूर्णांक xfs_qm_vop_dqalloc(काष्ठा xfs_inode *, kuid_t, kgid_t,
		prid_t, uपूर्णांक, काष्ठा xfs_dquot **, काष्ठा xfs_dquot **,
		काष्ठा xfs_dquot **);
बाह्य व्योम xfs_qm_vop_create_dqattach(काष्ठा xfs_trans *, काष्ठा xfs_inode *,
		काष्ठा xfs_dquot *, काष्ठा xfs_dquot *, काष्ठा xfs_dquot *);
बाह्य पूर्णांक xfs_qm_vop_नाम_dqattach(काष्ठा xfs_inode **);
बाह्य काष्ठा xfs_dquot *xfs_qm_vop_chown(काष्ठा xfs_trans *,
		काष्ठा xfs_inode *, काष्ठा xfs_dquot **, काष्ठा xfs_dquot *);
बाह्य पूर्णांक xfs_qm_dqattach(काष्ठा xfs_inode *);
बाह्य पूर्णांक xfs_qm_dqattach_locked(काष्ठा xfs_inode *ip, bool करोalloc);
बाह्य व्योम xfs_qm_dqdetach(काष्ठा xfs_inode *);
बाह्य व्योम xfs_qm_dqrele(काष्ठा xfs_dquot *);
बाह्य व्योम xfs_qm_statvfs(काष्ठा xfs_inode *, काष्ठा kstatfs *);
बाह्य पूर्णांक xfs_qm_newmount(काष्ठा xfs_mount *, uपूर्णांक *, uपूर्णांक *);
बाह्य व्योम xfs_qm_mount_quotas(काष्ठा xfs_mount *);
बाह्य व्योम xfs_qm_unmount(काष्ठा xfs_mount *);
बाह्य व्योम xfs_qm_unmount_quotas(काष्ठा xfs_mount *);

अटल अंतरभूत पूर्णांक
xfs_quota_reserve_blkres(काष्ठा xfs_inode *ip, पूर्णांक64_t blocks)
अणु
	वापस xfs_trans_reserve_quota_nblks(शून्य, ip, blocks, 0, false);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक
xfs_qm_vop_dqalloc(काष्ठा xfs_inode *ip, kuid_t kuid, kgid_t kgid,
		prid_t prid, uपूर्णांक flags, काष्ठा xfs_dquot **udqp,
		काष्ठा xfs_dquot **gdqp, काष्ठा xfs_dquot **pdqp)
अणु
	*udqp = शून्य;
	*gdqp = शून्य;
	*pdqp = शून्य;
	वापस 0;
पूर्ण
#घोषणा xfs_trans_dup_dqinfo(tp, tp2)
#घोषणा xfs_trans_मुक्त_dqinfo(tp)
#घोषणा xfs_trans_mod_dquot_byino(tp, ip, fields, delta) करो अणु पूर्ण जबतक (0)
#घोषणा xfs_trans_apply_dquot_deltas(tp)
#घोषणा xfs_trans_unreserve_and_mod_dquots(tp)
अटल अंतरभूत पूर्णांक xfs_trans_reserve_quota_nblks(काष्ठा xfs_trans *tp,
		काष्ठा xfs_inode *ip, पूर्णांक64_t dblocks, पूर्णांक64_t rblocks,
		bool क्रमce)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक xfs_trans_reserve_quota_bydquots(काष्ठा xfs_trans *tp,
		काष्ठा xfs_mount *mp, काष्ठा xfs_dquot *udqp,
		काष्ठा xfs_dquot *gdqp, काष्ठा xfs_dquot *pdqp,
		पूर्णांक64_t nblks, दीर्घ nions, uपूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_quota_reserve_blkres(काष्ठा xfs_inode *ip, पूर्णांक64_t blocks)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_trans_reserve_quota_icreate(काष्ठा xfs_trans *tp, काष्ठा xfs_dquot *udqp,
		काष्ठा xfs_dquot *gdqp, काष्ठा xfs_dquot *pdqp, पूर्णांक64_t dblocks)
अणु
	वापस 0;
पूर्ण

#घोषणा xfs_qm_vop_create_dqattach(tp, ip, u, g, p)
#घोषणा xfs_qm_vop_नाम_dqattach(it)					(0)
#घोषणा xfs_qm_vop_chown(tp, ip, old, new)				(शून्य)
#घोषणा xfs_qm_dqattach(ip)						(0)
#घोषणा xfs_qm_dqattach_locked(ip, fl)					(0)
#घोषणा xfs_qm_dqdetach(ip)
#घोषणा xfs_qm_dqrele(d)			करो अणु (d) = (d); पूर्ण जबतक(0)
#घोषणा xfs_qm_statvfs(ip, s)			करो अणु पूर्ण जबतक(0)
#घोषणा xfs_qm_newmount(mp, a, b)					(0)
#घोषणा xfs_qm_mount_quotas(mp)
#घोषणा xfs_qm_unmount(mp)
#घोषणा xfs_qm_unmount_quotas(mp)
#पूर्ण_अगर /* CONFIG_XFS_QUOTA */

अटल अंतरभूत पूर्णांक
xfs_quota_unreserve_blkres(काष्ठा xfs_inode *ip, पूर्णांक64_t blocks)
अणु
	वापस xfs_quota_reserve_blkres(ip, -blocks);
पूर्ण

बाह्य पूर्णांक xfs_mount_reset_sbqflags(काष्ठा xfs_mount *);

#पूर्ण_अगर	/* __XFS_QUOTA_H__ */
