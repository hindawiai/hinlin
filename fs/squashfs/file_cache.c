<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013
 * Phillip Lougher <phillip@squashfs.org.uk>
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/mutex.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs_fs_i.h"
#समावेश "squashfs.h"

/* Read separately compressed datablock and memcopy पूर्णांकo page cache */
पूर्णांक squashfs_पढ़ोpage_block(काष्ठा page *page, u64 block, पूर्णांक bsize, पूर्णांक expected)
अणु
	काष्ठा inode *i = page->mapping->host;
	काष्ठा squashfs_cache_entry *buffer = squashfs_get_datablock(i->i_sb,
		block, bsize);
	पूर्णांक res = buffer->error;

	अगर (res)
		ERROR("Unable to read page, block %llx, size %x\n", block,
			bsize);
	अन्यथा
		squashfs_copy_cache(page, buffer, expected, 0);

	squashfs_cache_put(buffer);
	वापस res;
पूर्ण
