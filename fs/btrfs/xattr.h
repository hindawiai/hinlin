<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Red Hat.  All rights reserved.
 */

#अगर_अघोषित BTRFS_XATTR_H
#घोषणा BTRFS_XATTR_H

#समावेश <linux/xattr.h>

बाह्य स्थिर काष्ठा xattr_handler *btrfs_xattr_handlers[];

पूर्णांक btrfs_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
		व्योम *buffer, माप_प्रकार size);
पूर्णांक btrfs_setxattr(काष्ठा btrfs_trans_handle *trans, काष्ठा inode *inode,
		   स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags);
पूर्णांक btrfs_setxattr_trans(काष्ठा inode *inode, स्थिर अक्षर *name,
			 स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags);
sमाप_प्रकार btrfs_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size);

पूर्णांक btrfs_xattr_security_init(काष्ठा btrfs_trans_handle *trans,
				     काष्ठा inode *inode, काष्ठा inode *dir,
				     स्थिर काष्ठा qstr *qstr);

#पूर्ण_अगर
