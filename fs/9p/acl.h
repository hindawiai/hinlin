<शैली गुरु>
/*
 * Copyright IBM Corporation, 2010
 * Author Aneesh Kumar K.V <aneesh.kumar@linux.vnet.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#अगर_अघोषित FS_9P_ACL_H
#घोषणा FS_9P_ACL_H

#अगर_घोषित CONFIG_9P_FS_POSIX_ACL
बाह्य पूर्णांक v9fs_get_acl(काष्ठा inode *, काष्ठा p9_fid *);
बाह्य काष्ठा posix_acl *v9fs_iop_get_acl(काष्ठा inode *inode, पूर्णांक type);
बाह्य पूर्णांक v9fs_acl_chmod(काष्ठा inode *, काष्ठा p9_fid *);
बाह्य पूर्णांक v9fs_set_create_acl(काष्ठा inode *, काष्ठा p9_fid *,
			       काष्ठा posix_acl *, काष्ठा posix_acl *);
बाह्य पूर्णांक v9fs_acl_mode(काष्ठा inode *dir, umode_t *modep,
			 काष्ठा posix_acl **dpacl, काष्ठा posix_acl **pacl);
बाह्य व्योम v9fs_put_acl(काष्ठा posix_acl *dacl, काष्ठा posix_acl *acl);
#अन्यथा
#घोषणा v9fs_iop_get_acl शून्य
अटल अंतरभूत पूर्णांक v9fs_get_acl(काष्ठा inode *inode, काष्ठा p9_fid *fid)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक v9fs_acl_chmod(काष्ठा inode *inode, काष्ठा p9_fid *fid)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक v9fs_set_create_acl(काष्ठा inode *inode,
				      काष्ठा p9_fid *fid,
				      काष्ठा posix_acl *dacl,
				      काष्ठा posix_acl *acl)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम v9fs_put_acl(काष्ठा posix_acl *dacl,
				काष्ठा posix_acl *acl)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक v9fs_acl_mode(काष्ठा inode *dir, umode_t *modep,
				काष्ठा posix_acl **dpacl,
				काष्ठा posix_acl **pacl)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर /* FS_9P_XATTR_H */
