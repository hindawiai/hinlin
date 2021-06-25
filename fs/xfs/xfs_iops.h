<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_IOPS_H__
#घोषणा __XFS_IOPS_H__

काष्ठा xfs_inode;

बाह्य स्थिर काष्ठा file_operations xfs_file_operations;
बाह्य स्थिर काष्ठा file_operations xfs_dir_file_operations;

बाह्य sमाप_प्रकार xfs_vn_listxattr(काष्ठा dentry *, अक्षर *data, माप_प्रकार size);

बाह्य व्योम xfs_setattr_समय(काष्ठा xfs_inode *ip, काष्ठा iattr *iattr);
पूर्णांक xfs_vn_setattr_size(काष्ठा user_namespace *mnt_userns,
		काष्ठा dentry *dentry, काष्ठा iattr *vap);

#पूर्ण_अगर /* __XFS_IOPS_H__ */
