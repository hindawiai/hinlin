<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012 Red Hat, Inc. All rights reserved.
 */
#अगर_अघोषित __XFS_SYMLINK_H
#घोषणा __XFS_SYMLINK_H 1

/* Kernel only symlink definitions */

पूर्णांक xfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा xfs_inode *dp,
		काष्ठा xfs_name *link_name, स्थिर अक्षर *target_path,
		umode_t mode, काष्ठा xfs_inode **ipp);
पूर्णांक xfs_पढ़ोlink_bmap_ilocked(काष्ठा xfs_inode *ip, अक्षर *link);
पूर्णांक xfs_पढ़ोlink(काष्ठा xfs_inode *ip, अक्षर *link);
पूर्णांक xfs_inactive_symlink(काष्ठा xfs_inode *ip);

#पूर्ण_अगर /* __XFS_SYMLINK_H */
