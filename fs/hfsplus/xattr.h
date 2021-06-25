<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/fs/hfsplus/xattr.h
 *
 * Vyacheslav Dubeyko <slava@dubeyko.com>
 *
 * Logic of processing extended attributes
 */

#अगर_अघोषित _LINUX_HFSPLUS_XATTR_H
#घोषणा _LINUX_HFSPLUS_XATTR_H

#समावेश <linux/xattr.h>

बाह्य स्थिर काष्ठा xattr_handler hfsplus_xattr_osx_handler;
बाह्य स्थिर काष्ठा xattr_handler hfsplus_xattr_user_handler;
बाह्य स्थिर काष्ठा xattr_handler hfsplus_xattr_trusted_handler;
बाह्य स्थिर काष्ठा xattr_handler hfsplus_xattr_security_handler;

बाह्य स्थिर काष्ठा xattr_handler *hfsplus_xattr_handlers[];

पूर्णांक __hfsplus_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags);

पूर्णांक hfsplus_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
				   स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags,
				   स्थिर अक्षर *prefix, माप_प्रकार prefixlen);

sमाप_प्रकार __hfsplus_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			   व्योम *value, माप_प्रकार size);

sमाप_प्रकार hfsplus_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			 व्योम *value, माप_प्रकार size,
			 स्थिर अक्षर *prefix, माप_प्रकार prefixlen);

sमाप_प्रकार hfsplus_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size);

पूर्णांक hfsplus_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				स्थिर काष्ठा qstr *qstr);

#पूर्ण_अगर
