<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2001 Silicon Graphics, Inc.  All Rights Reserved.
 */
#अगर_अघोषित __XFS_ITABLE_H__
#घोषणा	__XFS_ITABLE_H__

/* In-memory representation of a userspace request क्रम batch inode data. */
काष्ठा xfs_ibulk अणु
	काष्ठा xfs_mount	*mp;
	काष्ठा user_namespace   *mnt_userns;
	व्योम __user		*ubuffer; /* user output buffer */
	xfs_ino_t		startino; /* start with this inode */
	अचिन्हित पूर्णांक		icount;   /* number of elements in ubuffer */
	अचिन्हित पूर्णांक		ocount;   /* number of records वापसed */
	अचिन्हित पूर्णांक		flags;    /* see XFS_IBULK_FLAG_* */
पूर्ण;

/* Only iterate within the same AG as startino */
#घोषणा XFS_IBULK_SAME_AG	(XFS_IWALK_SAME_AG)

/*
 * Advance the user buffer poपूर्णांकer by one record of the given size.  If the
 * buffer is now full, वापस the appropriate error code.
 */
अटल अंतरभूत पूर्णांक
xfs_ibulk_advance(
	काष्ठा xfs_ibulk	*breq,
	माप_प्रकार			bytes)
अणु
	अक्षर __user		*b = breq->ubuffer;

	breq->ubuffer = b + bytes;
	breq->ocount++;
	वापस breq->ocount == breq->icount ? -ECANCELED : 0;
पूर्ण

/*
 * Return stat inक्रमmation in bulk (by-inode) क्रम the fileप्रणाली.
 */

/*
 * Return codes क्रम the क्रमmatter function are 0 to जारी iterating, and
 * non-zero to stop iterating.  Any non-zero value will be passed up to the
 * bulkstat/inumbers caller.  The special value -ECANCELED can be used to stop
 * iteration, as neither bulkstat nor inumbers will ever generate that error
 * code on their own.
 */

प्रकार पूर्णांक (*bulkstat_one_fmt_pf)(काष्ठा xfs_ibulk *breq,
		स्थिर काष्ठा xfs_bulkstat *bstat);

पूर्णांक xfs_bulkstat_one(काष्ठा xfs_ibulk *breq, bulkstat_one_fmt_pf क्रमmatter);
पूर्णांक xfs_bulkstat(काष्ठा xfs_ibulk *breq, bulkstat_one_fmt_pf क्रमmatter);
व्योम xfs_bulkstat_to_bstat(काष्ठा xfs_mount *mp, काष्ठा xfs_bstat *bs1,
		स्थिर काष्ठा xfs_bulkstat *bstat);

प्रकार पूर्णांक (*inumbers_fmt_pf)(काष्ठा xfs_ibulk *breq,
		स्थिर काष्ठा xfs_inumbers *igrp);

पूर्णांक xfs_inumbers(काष्ठा xfs_ibulk *breq, inumbers_fmt_pf क्रमmatter);
व्योम xfs_inumbers_to_inogrp(काष्ठा xfs_inogrp *ig1,
		स्थिर काष्ठा xfs_inumbers *ig);

#पूर्ण_अगर	/* __XFS_ITABLE_H__ */
