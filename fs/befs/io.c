<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/befs/io.c
 *
 * Copyright (C) 2001 Will Dyson <will_dyson@pobox.com
 *
 * Based on portions of file.c and inode.c
 * by Makoto Kato (m_kato@ga2.so-net.ne.jp)
 *
 * Many thanks to Dominic Giampaolo, author of Practical File System
 * Design with the Be File System, क्रम such a helpful book.
 *
 */

#समावेश <linux/buffer_head.h>

#समावेश "befs.h"
#समावेश "io.h"

/*
 * Converts befs notion of disk addr to a disk offset and uses
 * linux kernel function sb_bपढ़ो() to get the buffer containing
 * the offset.
 */

काष्ठा buffer_head *
befs_bपढ़ो_iaddr(काष्ठा super_block *sb, befs_inode_addr iaddr)
अणु
	काष्ठा buffer_head *bh;
	befs_blocknr_t block;
	काष्ठा befs_sb_info *befs_sb = BEFS_SB(sb);

	befs_debug(sb, "---> Enter %s "
		   "[%u, %hu, %hu]", __func__, iaddr.allocation_group,
		   iaddr.start, iaddr.len);

	अगर (iaddr.allocation_group > befs_sb->num_ags) अणु
		befs_error(sb, "BEFS: Invalid allocation group %u, max is %u",
			   iaddr.allocation_group, befs_sb->num_ags);
		जाओ error;
	पूर्ण

	block = iaddr2blockno(sb, &iaddr);

	befs_debug(sb, "%s: offset = %lu", __func__, (अचिन्हित दीर्घ)block);

	bh = sb_bपढ़ो(sb, block);

	अगर (bh == शून्य) अणु
		befs_error(sb, "Failed to read block %lu",
			   (अचिन्हित दीर्घ)block);
		जाओ error;
	पूर्ण

	befs_debug(sb, "<--- %s", __func__);
	वापस bh;

error:
	befs_debug(sb, "<--- %s ERROR", __func__);
	वापस शून्य;
पूर्ण
