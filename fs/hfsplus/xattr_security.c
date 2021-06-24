<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/hfsplus/xattr_trusted.c
 *
 * Vyacheslav Dubeyko <slava@dubeyko.com>
 *
 * Handler क्रम storing security labels as extended attributes.
 */

#समावेश <linux/security.h>
#समावेश <linux/nls.h>

#समावेश "hfsplus_fs.h"
#समावेश "xattr.h"

अटल पूर्णांक hfsplus_security_getxattr(स्थिर काष्ठा xattr_handler *handler,
				     काष्ठा dentry *unused, काष्ठा inode *inode,
				     स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस hfsplus_getxattr(inode, name, buffer, size,
				XATTR_SECURITY_PREFIX,
				XATTR_SECURITY_PREFIX_LEN);
पूर्ण

अटल पूर्णांक hfsplus_security_setxattr(स्थिर काष्ठा xattr_handler *handler,
				     काष्ठा user_namespace *mnt_userns,
				     काष्ठा dentry *unused, काष्ठा inode *inode,
				     स्थिर अक्षर *name, स्थिर व्योम *buffer,
				     माप_प्रकार size, पूर्णांक flags)
अणु
	वापस hfsplus_setxattr(inode, name, buffer, size, flags,
				XATTR_SECURITY_PREFIX,
				XATTR_SECURITY_PREFIX_LEN);
पूर्ण

अटल पूर्णांक hfsplus_initxattrs(काष्ठा inode *inode,
				स्थिर काष्ठा xattr *xattr_array,
				व्योम *fs_info)
अणु
	स्थिर काष्ठा xattr *xattr;
	अक्षर *xattr_name;
	पूर्णांक err = 0;

	xattr_name = kदो_स्मृति(NLS_MAX_CHARSET_SIZE * HFSPLUS_ATTR_MAX_STRLEN + 1,
		GFP_KERNEL);
	अगर (!xattr_name)
		वापस -ENOMEM;
	क्रम (xattr = xattr_array; xattr->name != शून्य; xattr++) अणु

		अगर (!म_भेद(xattr->name, ""))
			जारी;

		म_नकल(xattr_name, XATTR_SECURITY_PREFIX);
		म_नकल(xattr_name +
			XATTR_SECURITY_PREFIX_LEN, xattr->name);
		स_रखो(xattr_name +
			XATTR_SECURITY_PREFIX_LEN + म_माप(xattr->name), 0, 1);

		err = __hfsplus_setxattr(inode, xattr_name,
					xattr->value, xattr->value_len, 0);
		अगर (err)
			अवरोध;
	पूर्ण
	kमुक्त(xattr_name);
	वापस err;
पूर्ण

पूर्णांक hfsplus_init_security(काष्ठा inode *inode, काष्ठा inode *dir,
				स्थिर काष्ठा qstr *qstr)
अणु
	वापस security_inode_init_security(inode, dir, qstr,
					&hfsplus_initxattrs, शून्य);
पूर्ण

स्थिर काष्ठा xattr_handler hfsplus_xattr_security_handler = अणु
	.prefix	= XATTR_SECURITY_PREFIX,
	.get	= hfsplus_security_getxattr,
	.set	= hfsplus_security_setxattr,
पूर्ण;
