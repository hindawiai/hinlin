<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_FSOPS_H__
#घोषणा	__XFS_FSOPS_H__

बाह्य पूर्णांक xfs_growfs_data(काष्ठा xfs_mount *mp, काष्ठा xfs_growfs_data *in);
बाह्य पूर्णांक xfs_growfs_log(काष्ठा xfs_mount *mp, काष्ठा xfs_growfs_log *in);
बाह्य व्योम xfs_fs_counts(xfs_mount_t *mp, xfs_fsop_counts_t *cnt);
बाह्य पूर्णांक xfs_reserve_blocks(xfs_mount_t *mp, uपूर्णांक64_t *inval,
				xfs_fsop_resblks_t *outval);
बाह्य पूर्णांक xfs_fs_goingकरोwn(xfs_mount_t *mp, uपूर्णांक32_t inflags);

बाह्य पूर्णांक xfs_fs_reserve_ag_blocks(काष्ठा xfs_mount *mp);
बाह्य पूर्णांक xfs_fs_unreserve_ag_blocks(काष्ठा xfs_mount *mp);

#पूर्ण_अगर	/* __XFS_FSOPS_H__ */
