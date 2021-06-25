<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Red Hat, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_ATTR_REMOTE_H__
#घोषणा	__XFS_ATTR_REMOTE_H__

पूर्णांक xfs_attr3_rmt_blocks(काष्ठा xfs_mount *mp, पूर्णांक attrlen);

पूर्णांक xfs_attr_rmtval_get(काष्ठा xfs_da_args *args);
पूर्णांक xfs_attr_rmtval_set(काष्ठा xfs_da_args *args);
पूर्णांक xfs_attr_rmtval_हटाओ(काष्ठा xfs_da_args *args);
पूर्णांक xfs_attr_rmtval_stale(काष्ठा xfs_inode *ip, काष्ठा xfs_bmbt_irec *map,
		xfs_buf_flags_t incore_flags);
पूर्णांक xfs_attr_rmtval_invalidate(काष्ठा xfs_da_args *args);
पूर्णांक __xfs_attr_rmtval_हटाओ(काष्ठा xfs_da_args *args);
#पूर्ण_अगर /* __XFS_ATTR_REMOTE_H__ */
