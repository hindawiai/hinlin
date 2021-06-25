<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2019 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __XFS_IWALK_H__
#घोषणा __XFS_IWALK_H__

/*
 * Return codes क्रम the inode/inobt walk function are 0 to जारी iterating,
 * and non-zero to stop iterating.  Any non-zero value will be passed up to the
 * iwalk or inobt_walk caller.  The special value -ECANCELED can be used to
 * stop iteration, as neither iwalk nor inobt_walk will ever generate that
 * error code on their own.
 */

/* Walk all inodes in the fileप्रणाली starting from @startino. */
प्रकार पूर्णांक (*xfs_iwalk_fn)(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
			    xfs_ino_t ino, व्योम *data);

पूर्णांक xfs_iwalk(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp, xfs_ino_t startino,
		अचिन्हित पूर्णांक flags, xfs_iwalk_fn iwalk_fn,
		अचिन्हित पूर्णांक inode_records, व्योम *data);
पूर्णांक xfs_iwalk_thपढ़ोed(काष्ठा xfs_mount *mp, xfs_ino_t startino,
		अचिन्हित पूर्णांक flags, xfs_iwalk_fn iwalk_fn,
		अचिन्हित पूर्णांक inode_records, bool poll, व्योम *data);

/* Only iterate inodes within the same AG as @startino. */
#घोषणा XFS_IWALK_SAME_AG	(0x1)

#घोषणा XFS_IWALK_FLAGS_ALL	(XFS_IWALK_SAME_AG)

/* Walk all inode btree records in the fileप्रणाली starting from @startino. */
प्रकार पूर्णांक (*xfs_inobt_walk_fn)(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
				 xfs_agnumber_t agno,
				 स्थिर काष्ठा xfs_inobt_rec_incore *irec,
				 व्योम *data);

पूर्णांक xfs_inobt_walk(काष्ठा xfs_mount *mp, काष्ठा xfs_trans *tp,
		xfs_ino_t startino, अचिन्हित पूर्णांक flags,
		xfs_inobt_walk_fn inobt_walk_fn, अचिन्हित पूर्णांक inobt_records,
		व्योम *data);

/* Only iterate inobt records within the same AG as @startino. */
#घोषणा XFS_INOBT_WALK_SAME_AG	(XFS_IWALK_SAME_AG)

#घोषणा XFS_INOBT_WALK_FLAGS_ALL (XFS_INOBT_WALK_SAME_AG)

#पूर्ण_अगर /* __XFS_IWALK_H__ */
