<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs/f2fs/acl.h
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 *
 * Portions of this code from linux/fs/ext2/acl.h
 *
 * Copyright (C) 2001-2003 Andreas Gruenbacher, <agruen@suse.de>
 */
#अगर_अघोषित __F2FS_ACL_H__
#घोषणा __F2FS_ACL_H__

#समावेश <linux/posix_acl_xattr.h>

#घोषणा F2FS_ACL_VERSION	0x0001

काष्ठा f2fs_acl_entry अणु
	__le16 e_tag;
	__le16 e_perm;
	__le32 e_id;
पूर्ण;

काष्ठा f2fs_acl_entry_लघु अणु
	__le16 e_tag;
	__le16 e_perm;
पूर्ण;

काष्ठा f2fs_acl_header अणु
	__le32 a_version;
पूर्ण;

#अगर_घोषित CONFIG_F2FS_FS_POSIX_ACL

बाह्य काष्ठा posix_acl *f2fs_get_acl(काष्ठा inode *, पूर्णांक);
बाह्य पूर्णांक f2fs_set_acl(काष्ठा user_namespace *, काष्ठा inode *,
			काष्ठा posix_acl *, पूर्णांक);
बाह्य पूर्णांक f2fs_init_acl(काष्ठा inode *, काष्ठा inode *, काष्ठा page *,
							काष्ठा page *);
#अन्यथा
#घोषणा f2fs_get_acl	शून्य
#घोषणा f2fs_set_acl	शून्य

अटल अंतरभूत पूर्णांक f2fs_init_acl(काष्ठा inode *inode, काष्ठा inode *dir,
				काष्ठा page *ipage, काष्ठा page *dpage)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __F2FS_ACL_H__ */
