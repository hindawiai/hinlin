<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines  Corp., 2002
 */
#अगर_अघोषित _H_JFS_ACL
#घोषणा _H_JFS_ACL

#अगर_घोषित CONFIG_JFS_POSIX_ACL

काष्ठा posix_acl *jfs_get_acl(काष्ठा inode *inode, पूर्णांक type);
पूर्णांक jfs_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		काष्ठा posix_acl *acl, पूर्णांक type);
पूर्णांक jfs_init_acl(tid_t, काष्ठा inode *, काष्ठा inode *);

#अन्यथा

अटल अंतरभूत पूर्णांक jfs_init_acl(tid_t tid, काष्ठा inode *inode,
			       काष्ठा inode *dir)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर		/* _H_JFS_ACL */
