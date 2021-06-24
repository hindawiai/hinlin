<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#समावेश "nodelist.h"

स्थिर काष्ठा inode_operations jffs2_symlink_inode_operations =
अणु
	.get_link =	simple_get_link,
	.setattr =	jffs2_setattr,
	.listxattr =	jffs2_listxattr,
पूर्ण;
