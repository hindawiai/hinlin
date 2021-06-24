<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext2/xattr_user.c
 * Handler क्रम extended user attributes.
 *
 * Copyright (C) 2001 by Andreas Gruenbacher, <a.gruenbacher@computer.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश "ext2.h"
#समावेश "xattr.h"

अटल bool
ext2_xattr_user_list(काष्ठा dentry *dentry)
अणु
	वापस test_opt(dentry->d_sb, XATTR_USER);
पूर्ण

अटल पूर्णांक
ext2_xattr_user_get(स्थिर काष्ठा xattr_handler *handler,
		    काष्ठा dentry *unused, काष्ठा inode *inode,
		    स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	अगर (!test_opt(inode->i_sb, XATTR_USER))
		वापस -EOPNOTSUPP;
	वापस ext2_xattr_get(inode, EXT2_XATTR_INDEX_USER,
			      name, buffer, size);
पूर्ण

अटल पूर्णांक
ext2_xattr_user_set(स्थिर काष्ठा xattr_handler *handler,
		    काष्ठा user_namespace *mnt_userns,
		    काष्ठा dentry *unused, काष्ठा inode *inode,
		    स्थिर अक्षर *name, स्थिर व्योम *value,
		    माप_प्रकार size, पूर्णांक flags)
अणु
	अगर (!test_opt(inode->i_sb, XATTR_USER))
		वापस -EOPNOTSUPP;

	वापस ext2_xattr_set(inode, EXT2_XATTR_INDEX_USER,
			      name, value, size, flags);
पूर्ण

स्थिर काष्ठा xattr_handler ext2_xattr_user_handler = अणु
	.prefix	= XATTR_USER_PREFIX,
	.list	= ext2_xattr_user_list,
	.get	= ext2_xattr_user_get,
	.set	= ext2_xattr_user_set,
पूर्ण;
