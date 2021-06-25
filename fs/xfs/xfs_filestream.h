<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2006-2007 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_खाताSTREAM_H__
#घोषणा __XFS_खाताSTREAM_H__

काष्ठा xfs_mount;
काष्ठा xfs_inode;
काष्ठा xfs_bदो_स्मृतिa;

पूर्णांक xfs_filestream_mount(काष्ठा xfs_mount *mp);
व्योम xfs_filestream_unmount(काष्ठा xfs_mount *mp);
व्योम xfs_filestream_deassociate(काष्ठा xfs_inode *ip);
xfs_agnumber_t xfs_filestream_lookup_ag(काष्ठा xfs_inode *ip);
पूर्णांक xfs_filestream_new_ag(काष्ठा xfs_bदो_स्मृतिa *ap, xfs_agnumber_t *agp);
पूर्णांक xfs_filestream_peek_ag(काष्ठा xfs_mount *mp, xfs_agnumber_t agno);

अटल अंतरभूत पूर्णांक
xfs_inode_is_filestream(
	काष्ठा xfs_inode	*ip)
अणु
	वापस (ip->i_mount->m_flags & XFS_MOUNT_खाताSTREAMS) ||
		(ip->i_dअगरlags & XFS_DIFLAG_खाताSTREAM);
पूर्ण

#पूर्ण_अगर /* __XFS_खाताSTREAM_H__ */
