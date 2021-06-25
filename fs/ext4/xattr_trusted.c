<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext4/xattr_trusted.c
 * Handler क्रम trusted extended attributes.
 *
 * Copyright (C) 2003 by Andreas Gruenbacher, <a.gruenbacher@computer.org>
 */

#समावेश <linux/माला.स>
#समावेश <linux/capability.h>
#समावेश <linux/fs.h>
#समावेश "ext4_jbd2.h"
#समावेश "ext4.h"
#समावेश "xattr.h"

अटल bool
ext4_xattr_trusted_list(काष्ठा dentry *dentry)
अणु
	वापस capable(CAP_SYS_ADMIN);
पूर्ण

अटल पूर्णांक
ext4_xattr_trusted_get(स्थिर काष्ठा xattr_handler *handler,
		       काष्ठा dentry *unused, काष्ठा inode *inode,
		       स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस ext4_xattr_get(inode, EXT4_XATTR_INDEX_TRUSTED,
			      name, buffer, size);
पूर्ण

अटल पूर्णांक
ext4_xattr_trusted_set(स्थिर काष्ठा xattr_handler *handler,
		       काष्ठा user_namespace *mnt_userns,
		       काष्ठा dentry *unused, काष्ठा inode *inode,
		       स्थिर अक्षर *name, स्थिर व्योम *value,
		       माप_प्रकार size, पूर्णांक flags)
अणु
	वापस ext4_xattr_set(inode, EXT4_XATTR_INDEX_TRUSTED,
			      name, value, size, flags);
पूर्ण

स्थिर काष्ठा xattr_handler ext4_xattr_trusted_handler = अणु
	.prefix	= XATTR_TRUSTED_PREFIX,
	.list	= ext4_xattr_trusted_list,
	.get	= ext4_xattr_trusted_get,
	.set	= ext4_xattr_trusted_set,
पूर्ण;
