<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "reiserfs.h"
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/xattr.h>
#समावेश "xattr.h"
#समावेश <linux/uaccess.h>

अटल पूर्णांक
user_get(स्थिर काष्ठा xattr_handler *handler, काष्ठा dentry *unused,
	 काष्ठा inode *inode, स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	अगर (!reiserfs_xattrs_user(inode->i_sb))
		वापस -EOPNOTSUPP;
	वापस reiserfs_xattr_get(inode, xattr_full_name(handler, name),
				  buffer, size);
पूर्ण

अटल पूर्णांक
user_set(स्थिर काष्ठा xattr_handler *handler, काष्ठा user_namespace *mnt_userns,
	 काष्ठा dentry *unused,
	 काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *buffer,
	 माप_प्रकार size, पूर्णांक flags)
अणु
	अगर (!reiserfs_xattrs_user(inode->i_sb))
		वापस -EOPNOTSUPP;
	वापस reiserfs_xattr_set(inode,
				  xattr_full_name(handler, name),
				  buffer, size, flags);
पूर्ण

अटल bool user_list(काष्ठा dentry *dentry)
अणु
	वापस reiserfs_xattrs_user(dentry->d_sb);
पूर्ण

स्थिर काष्ठा xattr_handler reiserfs_xattr_user_handler = अणु
	.prefix = XATTR_USER_PREFIX,
	.get = user_get,
	.set = user_set,
	.list = user_list,
पूर्ण;
