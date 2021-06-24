<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#अगर_अघोषित __EROFS_XATTR_H
#घोषणा __EROFS_XATTR_H

#समावेश "internal.h"
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/xattr.h>

/* Attribute not found */
#घोषणा ENOATTR         ENODATA

अटल अंतरभूत अचिन्हित पूर्णांक अंतरभूतxattr_header_size(काष्ठा inode *inode)
अणु
	वापस माप(काष्ठा erofs_xattr_ibody_header) +
		माप(u32) * EROFS_I(inode)->xattr_shared_count;
पूर्ण

अटल अंतरभूत erofs_blk_t xattrblock_addr(काष्ठा erofs_sb_info *sbi,
					  अचिन्हित पूर्णांक xattr_id)
अणु
#अगर_घोषित CONFIG_EROFS_FS_XATTR
	वापस sbi->xattr_blkaddr +
		xattr_id * माप(__u32) / EROFS_BLKSIZ;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xattrblock_offset(काष्ठा erofs_sb_info *sbi,
					     अचिन्हित पूर्णांक xattr_id)
अणु
	वापस (xattr_id * माप(__u32)) % EROFS_BLKSIZ;
पूर्ण

#अगर_घोषित CONFIG_EROFS_FS_XATTR
बाह्य स्थिर काष्ठा xattr_handler erofs_xattr_user_handler;
बाह्य स्थिर काष्ठा xattr_handler erofs_xattr_trusted_handler;
#अगर_घोषित CONFIG_EROFS_FS_SECURITY
बाह्य स्थिर काष्ठा xattr_handler erofs_xattr_security_handler;
#पूर्ण_अगर

अटल अंतरभूत स्थिर काष्ठा xattr_handler *erofs_xattr_handler(अचिन्हित पूर्णांक idx)
अणु
	अटल स्थिर काष्ठा xattr_handler *xattr_handler_map[] = अणु
		[EROFS_XATTR_INDEX_USER] = &erofs_xattr_user_handler,
#अगर_घोषित CONFIG_EROFS_FS_POSIX_ACL
		[EROFS_XATTR_INDEX_POSIX_ACL_ACCESS] =
			&posix_acl_access_xattr_handler,
		[EROFS_XATTR_INDEX_POSIX_ACL_DEFAULT] =
			&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
		[EROFS_XATTR_INDEX_TRUSTED] = &erofs_xattr_trusted_handler,
#अगर_घोषित CONFIG_EROFS_FS_SECURITY
		[EROFS_XATTR_INDEX_SECURITY] = &erofs_xattr_security_handler,
#पूर्ण_अगर
	पूर्ण;

	वापस idx && idx < ARRAY_SIZE(xattr_handler_map) ?
		xattr_handler_map[idx] : शून्य;
पूर्ण

बाह्य स्थिर काष्ठा xattr_handler *erofs_xattr_handlers[];

पूर्णांक erofs_getxattr(काष्ठा inode *, पूर्णांक, स्थिर अक्षर *, व्योम *, माप_प्रकार);
sमाप_प्रकार erofs_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);
#अन्यथा
अटल अंतरभूत पूर्णांक erofs_getxattr(काष्ठा inode *inode, पूर्णांक index,
				 स्थिर अक्षर *name, व्योम *buffer,
				 माप_प्रकार buffer_size)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#घोषणा erofs_listxattr (शून्य)
#घोषणा erofs_xattr_handlers (शून्य)
#पूर्ण_अगर	/* !CONFIG_EROFS_FS_XATTR */

#अगर_घोषित CONFIG_EROFS_FS_POSIX_ACL
काष्ठा posix_acl *erofs_get_acl(काष्ठा inode *inode, पूर्णांक type);
#अन्यथा
#घोषणा erofs_get_acl	(शून्य)
#पूर्ण_अगर

#पूर्ण_अगर

