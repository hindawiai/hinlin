<शैली गुरु>
/*
 *  linux/fs/hfs/sysdep.c
 *
 * Copyright (C) 1996  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 *
 * This file contains the code to करो various प्रणाली dependent things.
 */

#समावेश <linux/namei.h>
#समावेश "hfs_fs.h"

/* dentry हाल-handling: just lowerहाल everything */

अटल पूर्णांक hfs_revalidate_dentry(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	पूर्णांक dअगरf;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	inode = d_inode(dentry);
	अगर(!inode)
		वापस 1;

	/* fix up inode on a समयzone change */
	dअगरf = sys_tz.tz_minuteswest * 60 - HFS_I(inode)->tz_secondswest;
	अगर (dअगरf) अणु
		inode->i_स_समय.tv_sec += dअगरf;
		inode->i_aसमय.tv_sec += dअगरf;
		inode->i_mसमय.tv_sec += dअगरf;
		HFS_I(inode)->tz_secondswest += dअगरf;
	पूर्ण
	वापस 1;
पूर्ण

स्थिर काष्ठा dentry_operations hfs_dentry_operations =
अणु
	.d_revalidate	= hfs_revalidate_dentry,
	.d_hash		= hfs_hash_dentry,
	.d_compare	= hfs_compare_dentry,
पूर्ण;

