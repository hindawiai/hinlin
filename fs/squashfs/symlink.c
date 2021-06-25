<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * symlink.c
 */

/*
 * This file implements code to handle symbolic links.
 *
 * The data contents of symbolic links are stored inside the symbolic
 * link inode within the inode table.  This allows the normally small symbolic
 * link to be compressed as part of the inode table, achieving much greater
 * compression than अगर the symbolic link was compressed inभागidually.
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/xattr.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs_fs_i.h"
#समावेश "squashfs.h"
#समावेश "xattr.h"

अटल पूर्णांक squashfs_symlink_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	पूर्णांक index = page->index << PAGE_SHIFT;
	u64 block = squashfs_i(inode)->start;
	पूर्णांक offset = squashfs_i(inode)->offset;
	पूर्णांक length = min_t(पूर्णांक, i_size_पढ़ो(inode) - index, PAGE_SIZE);
	पूर्णांक bytes, copied;
	व्योम *pageaddr;
	काष्ठा squashfs_cache_entry *entry;

	TRACE("Entered squashfs_symlink_readpage, page index %ld, start block "
			"%llx, offset %x\n", page->index, block, offset);

	/*
	 * Skip index bytes पूर्णांकo symlink metadata.
	 */
	अगर (index) अणु
		bytes = squashfs_पढ़ो_metadata(sb, शून्य, &block, &offset,
								index);
		अगर (bytes < 0) अणु
			ERROR("Unable to read symlink [%llx:%x]\n",
				squashfs_i(inode)->start,
				squashfs_i(inode)->offset);
			जाओ error_out;
		पूर्ण
	पूर्ण

	/*
	 * Read length bytes from symlink metadata.  Squashfs_पढ़ो_metadata
	 * is not used here because it can sleep and we want to use
	 * kmap_atomic to map the page.  Instead call the underlying
	 * squashfs_cache_get routine.  As length bytes may overlap metadata
	 * blocks, we may need to call squashfs_cache_get multiple बार.
	 */
	क्रम (bytes = 0; bytes < length; offset = 0, bytes += copied) अणु
		entry = squashfs_cache_get(sb, msblk->block_cache, block, 0);
		अगर (entry->error) अणु
			ERROR("Unable to read symlink [%llx:%x]\n",
				squashfs_i(inode)->start,
				squashfs_i(inode)->offset);
			squashfs_cache_put(entry);
			जाओ error_out;
		पूर्ण

		pageaddr = kmap_atomic(page);
		copied = squashfs_copy_data(pageaddr + bytes, entry, offset,
								length - bytes);
		अगर (copied == length - bytes)
			स_रखो(pageaddr + length, 0, PAGE_SIZE - length);
		अन्यथा
			block = entry->next_index;
		kunmap_atomic(pageaddr);
		squashfs_cache_put(entry);
	पूर्ण

	flush_dcache_page(page);
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;

error_out:
	SetPageError(page);
	unlock_page(page);
	वापस 0;
पूर्ण


स्थिर काष्ठा address_space_operations squashfs_symlink_aops = अणु
	.पढ़ोpage = squashfs_symlink_पढ़ोpage
पूर्ण;

स्थिर काष्ठा inode_operations squashfs_symlink_inode_ops = अणु
	.get_link = page_get_link,
	.listxattr = squashfs_listxattr
पूर्ण;

