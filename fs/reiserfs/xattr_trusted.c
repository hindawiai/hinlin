<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "reiserfs.h"
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/xattr.h>
#समावेश "xattr.h"
#समावेश <linux/uaccess.h>

अटल पूर्णांक
trusted_get(स्थिर काष्ठा xattr_handler *handler, काष्ठा dentry *unused,
	    काष्ठा inode *inode, स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	अगर (!capable(CAP_SYS_ADMIN) || IS_PRIVATE(inode))
		वापस -EPERM;

	वापस reiserfs_xattr_get(inode, xattr_full_name(handler, name),
				  buffer, size);
पूर्ण

अटल पूर्णांक
trusted_set(स्थिर काष्ठा xattr_handler *handler,
	    काष्ठा user_namespace *mnt_userns, काष्ठा dentry *unused,
	    काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *buffer,
	    माप_प्रकार size, पूर्णांक flags)
अणु
	अगर (!capable(CAP_SYS_ADMIN) || IS_PRIVATE(inode))
		वापस -EPERM;

	वापस reiserfs_xattr_set(inode,
				  xattr_full_name(handler, name),
				  buffer, size, flags);
पूर्ण

अटल bool trusted_list(काष्ठा dentry *dentry)
अणु
	वापस capable(CAP_SYS_ADMIN) && !IS_PRIVATE(d_inode(dentry));
पूर्ण

स्थिर काष्ठा xattr_handler reiserfs_xattr_trusted_handler = अणु
	.prefix = XATTR_TRUSTED_PREFIX,
	.get = trusted_get,
	.set = trusted_set,
	.list = trusted_list,
पूर्ण;
