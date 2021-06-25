<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) Christoph Hellwig, 2001-2002
 */

#समावेश <linux/fs.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_inode.h"
#समावेश "jfs_xattr.h"

स्थिर काष्ठा inode_operations jfs_fast_symlink_inode_operations = अणु
	.get_link	= simple_get_link,
	.setattr	= jfs_setattr,
	.listxattr	= jfs_listxattr,
पूर्ण;

स्थिर काष्ठा inode_operations jfs_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.setattr	= jfs_setattr,
	.listxattr	= jfs_listxattr,
पूर्ण;

