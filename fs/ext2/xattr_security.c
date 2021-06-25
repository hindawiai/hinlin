<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext2/xattr_security.c
 * Handler क्रम storing security labels as extended attributes.
 */

#समावेश "ext2.h"
#समावेश <linux/security.h>
#समावेश "xattr.h"

अटल पूर्णांक
ext2_xattr_security_get(स्थिर काष्ठा xattr_handler *handler,
			काष्ठा dentry *unused, काष्ठा inode *inode,
			स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस ext2_xattr_get(inode, EXT2_XATTR_INDEX_SECURITY, name,
			      buffer, size);
पूर्ण

अटल पूर्णांक
ext2_xattr_security_set(स्थिर काष्ठा xattr_handler *handler,
			काष्ठा user_namespace *mnt_userns,
			काष्ठा dentry *unused, काष्ठा inode *inode,
			स्थिर अक्षर *name, स्थिर व्योम *value,
			माप_प्रकार size, पूर्णांक flags)
अणु
	वापस ext2_xattr_set(inode, EXT2_XATTR_INDEX_SECURITY, name,
			      value, size, flags);
पूर्ण

अटल पूर्णांक ext2_initxattrs(काष्ठा inode *inode, स्थिर काष्ठा xattr *xattr_array,
			   व्योम *fs_info)
अणु
	स्थिर काष्ठा xattr *xattr;
	पूर्णांक err = 0;

	क्रम (xattr = xattr_array; xattr->name != शून्य; xattr++) अणु
		err = ext2_xattr_set(inode, EXT2_XATTR_INDEX_SECURITY,
				     xattr->name, xattr->value,
				     xattr->value_len, 0);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक
ext2_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
		   स्थिर काष्ठा qstr *qstr)
अणु
	वापस security_inode_init_security(inode, dir, qstr,
					    &ext2_initxattrs, शून्य);
पूर्ण

स्थिर काष्ठा xattr_handler ext2_xattr_security_handler = अणु
	.prefix	= XATTR_SECURITY_PREFIX,
	.get	= ext2_xattr_security_get,
	.set	= ext2_xattr_security_set,
पूर्ण;
