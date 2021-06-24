<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2006  NEC Corporation
 *
 * Created by KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/jffs2.h>
#समावेश <linux/xattr.h>
#समावेश <linux/mtd/mtd.h>
#समावेश "nodelist.h"

अटल पूर्णांक jffs2_user_getxattr(स्थिर काष्ठा xattr_handler *handler,
			       काष्ठा dentry *unused, काष्ठा inode *inode,
			       स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस करो_jffs2_getxattr(inode, JFFS2_XPREFIX_USER,
				 name, buffer, size);
पूर्ण

अटल पूर्णांक jffs2_user_setxattr(स्थिर काष्ठा xattr_handler *handler,
			       काष्ठा user_namespace *mnt_userns,
			       काष्ठा dentry *unused, काष्ठा inode *inode,
			       स्थिर अक्षर *name, स्थिर व्योम *buffer,
			       माप_प्रकार size, पूर्णांक flags)
अणु
	वापस करो_jffs2_setxattr(inode, JFFS2_XPREFIX_USER,
				 name, buffer, size, flags);
पूर्ण

स्थिर काष्ठा xattr_handler jffs2_user_xattr_handler = अणु
	.prefix = XATTR_USER_PREFIX,
	.set = jffs2_user_setxattr,
	.get = jffs2_user_getxattr
पूर्ण;
