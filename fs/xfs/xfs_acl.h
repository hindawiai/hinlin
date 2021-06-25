<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2001-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#अगर_अघोषित __XFS_ACL_H__
#घोषणा __XFS_ACL_H__

काष्ठा inode;
काष्ठा posix_acl;

#अगर_घोषित CONFIG_XFS_POSIX_ACL
बाह्य काष्ठा posix_acl *xfs_get_acl(काष्ठा inode *inode, पूर्णांक type);
बाह्य पूर्णांक xfs_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		       काष्ठा posix_acl *acl, पूर्णांक type);
बाह्य पूर्णांक __xfs_set_acl(काष्ठा inode *inode, काष्ठा posix_acl *acl, पूर्णांक type);
व्योम xfs_क्रमget_acl(काष्ठा inode *inode, स्थिर अक्षर *name);
#अन्यथा
अटल अंतरभूत काष्ठा posix_acl *xfs_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	वापस शून्य;
पूर्ण
# define xfs_set_acl					शून्य
अटल अंतरभूत व्योम xfs_क्रमget_acl(काष्ठा inode *inode, स्थिर अक्षर *name)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_XFS_POSIX_ACL */

#पूर्ण_अगर	/* __XFS_ACL_H__ */
