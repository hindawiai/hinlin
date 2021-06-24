<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2014 Anna Schumaker.
 *
 * NFSv3-specअगरic fileप्रणाली definitions and declarations
 */
#अगर_अघोषित __LINUX_FS_NFS_NFS3_FS_H
#घोषणा __LINUX_FS_NFS_NFS3_FS_H

/*
 * nfs3acl.c
 */
#अगर_घोषित CONFIG_NFS_V3_ACL
बाह्य काष्ठा posix_acl *nfs3_get_acl(काष्ठा inode *inode, पूर्णांक type);
बाह्य पूर्णांक nfs3_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
			काष्ठा posix_acl *acl, पूर्णांक type);
बाह्य पूर्णांक nfs3_proc_setacls(काष्ठा inode *inode, काष्ठा posix_acl *acl,
		काष्ठा posix_acl *dfacl);
बाह्य sमाप_प्रकार nfs3_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);
बाह्य स्थिर काष्ठा xattr_handler *nfs3_xattr_handlers[];
#अन्यथा
अटल अंतरभूत पूर्णांक nfs3_proc_setacls(काष्ठा inode *inode, काष्ठा posix_acl *acl,
		काष्ठा posix_acl *dfacl)
अणु
	वापस 0;
पूर्ण
#घोषणा nfs3_listxattr शून्य
#पूर्ण_अगर /* CONFIG_NFS_V3_ACL */

/* nfs3client.c */
काष्ठा nfs_server *nfs3_create_server(काष्ठा fs_context *);
काष्ठा nfs_server *nfs3_clone_server(काष्ठा nfs_server *, काष्ठा nfs_fh *,
				     काष्ठा nfs_fattr *, rpc_authflavor_t);

/* nfs3super.c */
बाह्य काष्ठा nfs_subversion nfs_v3;

#पूर्ण_अगर /* __LINUX_FS_NFS_NFS3_FS_H */
