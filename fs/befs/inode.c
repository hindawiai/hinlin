<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * inode.c
 *
 * Copyright (C) 2001 Will Dyson <will_dyson@pobox.com>
 */

#समावेश <linux/fs.h>

#समावेश "befs.h"
#समावेश "inode.h"

/*
 * Validates the correctness of the befs inode
 * Returns BEFS_OK अगर the inode should be used, otherwise
 * वापसs BEFS_BAD_INODE
 */
पूर्णांक
befs_check_inode(काष्ठा super_block *sb, befs_inode *raw_inode,
		 befs_blocknr_t inode)
अणु
	u32 magic1 = fs32_to_cpu(sb, raw_inode->magic1);
	befs_inode_addr ino_num = fsrun_to_cpu(sb, raw_inode->inode_num);
	u32 flags = fs32_to_cpu(sb, raw_inode->flags);

	/* check magic header. */
	अगर (magic1 != BEFS_INODE_MAGIC1) अणु
		befs_error(sb,
			   "Inode has a bad magic header - inode = %lu",
			   (अचिन्हित दीर्घ)inode);
		वापस BEFS_BAD_INODE;
	पूर्ण

	/*
	 * Sanity check2: inodes store their own block address. Check it.
	 */
	अगर (inode != iaddr2blockno(sb, &ino_num)) अणु
		befs_error(sb, "inode blocknr field disagrees with vfs "
			   "VFS: %lu, Inode %lu", (अचिन्हित दीर्घ)
			   inode, (अचिन्हित दीर्घ)iaddr2blockno(sb, &ino_num));
		वापस BEFS_BAD_INODE;
	पूर्ण

	/*
	 * check flag
	 */

	अगर (!(flags & BEFS_INODE_IN_USE)) अणु
		befs_error(sb, "inode is not used - inode = %lu",
			   (अचिन्हित दीर्घ)inode);
		वापस BEFS_BAD_INODE;
	पूर्ण

	वापस BEFS_OK;
पूर्ण
