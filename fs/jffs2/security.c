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
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/crc32.h>
#समावेश <linux/jffs2.h>
#समावेश <linux/xattr.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/security.h>
#समावेश "nodelist.h"

/* ---- Initial Security Label(s) Attachment callback --- */
अटल पूर्णांक jffs2_initxattrs(काष्ठा inode *inode,
			    स्थिर काष्ठा xattr *xattr_array, व्योम *fs_info)
अणु
	स्थिर काष्ठा xattr *xattr;
	पूर्णांक err = 0;

	क्रम (xattr = xattr_array; xattr->name != शून्य; xattr++) अणु
		err = करो_jffs2_setxattr(inode, JFFS2_XPREFIX_SECURITY,
					xattr->name, xattr->value,
					xattr->value_len, 0);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/* ---- Initial Security Label(s) Attachment ----------- */
पूर्णांक jffs2_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
			स्थिर काष्ठा qstr *qstr)
अणु
	वापस security_inode_init_security(inode, dir, qstr,
					    &jffs2_initxattrs, शून्य);
पूर्ण

/* ---- XATTR Handler क्रम "security.*" ----------------- */
अटल पूर्णांक jffs2_security_getxattr(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस करो_jffs2_getxattr(inode, JFFS2_XPREFIX_SECURITY,
				 name, buffer, size);
पूर्ण

अटल पूर्णांक jffs2_security_setxattr(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा user_namespace *mnt_userns,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *name, स्थिर व्योम *buffer,
				   माप_प्रकार size, पूर्णांक flags)
अणु
	वापस करो_jffs2_setxattr(inode, JFFS2_XPREFIX_SECURITY,
				 name, buffer, size, flags);
पूर्ण

स्थिर काष्ठा xattr_handler jffs2_security_xattr_handler = अणु
	.prefix = XATTR_SECURITY_PREFIX,
	.set = jffs2_security_setxattr,
	.get = jffs2_security_getxattr
पूर्ण;
