<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/hfsplus/xattr_trusted.c
 *
 * Vyacheslav Dubeyko <slava@dubeyko.com>
 *
 * Handler क्रम trusted extended attributes.
 */

#समावेश <linux/nls.h>

#समावेश "hfsplus_fs.h"
#समावेश "xattr.h"

अटल पूर्णांक hfsplus_trusted_getxattr(स्थिर काष्ठा xattr_handler *handler,
				    काष्ठा dentry *unused, काष्ठा inode *inode,
				    स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस hfsplus_getxattr(inode, name, buffer, size,
				XATTR_TRUSTED_PREFIX,
				XATTR_TRUSTED_PREFIX_LEN);
पूर्ण

अटल पूर्णांक hfsplus_trusted_setxattr(स्थिर काष्ठा xattr_handler *handler,
				    काष्ठा user_namespace *mnt_userns,
				    काष्ठा dentry *unused, काष्ठा inode *inode,
				    स्थिर अक्षर *name, स्थिर व्योम *buffer,
				    माप_प्रकार size, पूर्णांक flags)
अणु
	वापस hfsplus_setxattr(inode, name, buffer, size, flags,
				XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN);
पूर्ण

स्थिर काष्ठा xattr_handler hfsplus_xattr_trusted_handler = अणु
	.prefix	= XATTR_TRUSTED_PREFIX,
	.get	= hfsplus_trusted_getxattr,
	.set	= hfsplus_trusted_setxattr,
पूर्ण;
