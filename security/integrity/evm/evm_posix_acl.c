<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 IBM Corporation
 *
 * Author:
 * Mimi Zohar <zohar@us.ibm.com>
 */

#समावेश <linux/xattr.h>
#समावेश <linux/evm.h>

पूर्णांक posix_xattr_acl(स्थिर अक्षर *xattr)
अणु
	पूर्णांक xattr_len = म_माप(xattr);

	अगर ((म_माप(XATTR_NAME_POSIX_ACL_ACCESS) == xattr_len)
	     && (म_भेदन(XATTR_NAME_POSIX_ACL_ACCESS, xattr, xattr_len) == 0))
		वापस 1;
	अगर ((म_माप(XATTR_NAME_POSIX_ACL_DEFAULT) == xattr_len)
	     && (म_भेदन(XATTR_NAME_POSIX_ACL_DEFAULT, xattr, xattr_len) == 0))
		वापस 1;
	वापस 0;
पूर्ण
