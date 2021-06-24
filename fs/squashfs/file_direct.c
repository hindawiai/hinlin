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
#समावेश "page_actor.h"

अटल पूर्णांक squashfs_पढ़ो_cache(काष्ठा page *target_page, u64 block, पूर्णांक bsize,
	पूर्णांक pages, काष्ठा page **page, पूर्णांक bytes);

/* Read separately compressed datablock directly पूर्णांकo page cache */
पूर्णांक squashfs_पढ़ोpage_block(काष्ठा page *target_page, u64 block, पूर्णांक bsize,
	पूर्णांक expected)

अणु
	काष्ठा inode *inode = target_page->mapping->host;
	काष्ठा squashfs_sb_info *msblk = inode->i_sb->s_fs_info;

	पूर्णांक file_end = (i_size_पढ़ो(inode) - 1) >> PAGE_SHIFT;
	पूर्णांक mask = (1 << (msblk->block_log - PAGE_SHIFT)) - 1;
	पूर्णांक start_index = target_page->index & ~mask;
	पूर्णांक end_index = start_index | mask;
	पूर्णांक i, n, pages, missing_pages, bytes, res = -ENOMEM;
	काष्ठा page **page;
	काष्ठा squashfs_page_actor *actor;
	व्योम *pageaddr;

	अगर (end_index > file_end)
		end_index = file_end;

	pages = end_index - start_index + 1;

	page = kदो_स्मृति_array(pages, माप(व्योम *), GFP_KERNEL);
	अगर (page == शून्य)
		वापस res;

	/*
	 * Create a "page actor" which will kmap and kunmap the
	 * page cache pages appropriately within the decompressor
	 */
	actor = squashfs_page_actor_init_special(page, pages, 0);
	अगर (actor == शून्य)
		जाओ out;

	/* Try to grab all the pages covered by the Squashfs block */
	क्रम (missing_pages = 0, i = 0, n = start_index; i < pages; i++, n++) अणु
		page[i] = (n == target_page->index) ? target_page :
			grab_cache_page_noरुको(target_page->mapping, n);

		अगर (page[i] == शून्य) अणु
			missing_pages++;
			जारी;
		पूर्ण

		अगर (PageUptodate(page[i])) अणु
			unlock_page(page[i]);
			put_page(page[i]);
			page[i] = शून्य;
			missing_pages++;
		पूर्ण
	पूर्ण

	अगर (missing_pages) अणु
		/*
		 * Couldn't get one or more pages, this page has either
		 * been VM reclaimed, but others are still in the page cache
		 * and uptodate, or we're racing with another thपढ़ो in
		 * squashfs_पढ़ोpage also trying to grab them.  Fall back to
		 * using an पूर्णांकermediate buffer.
		 */
		res = squashfs_पढ़ो_cache(target_page, block, bsize, pages,
							page, expected);
		अगर (res < 0)
			जाओ mark_errored;

		जाओ out;
	पूर्ण

	/* Decompress directly पूर्णांकo the page cache buffers */
	res = squashfs_पढ़ो_data(inode->i_sb, block, bsize, शून्य, actor);
	अगर (res < 0)
		जाओ mark_errored;

	अगर (res != expected) अणु
		res = -EIO;
		जाओ mark_errored;
	पूर्ण

	/* Last page may have trailing bytes not filled */
	bytes = res % PAGE_SIZE;
	अगर (bytes) अणु
		pageaddr = kmap_atomic(page[pages - 1]);
		स_रखो(pageaddr + bytes, 0, PAGE_SIZE - bytes);
		kunmap_atomic(pageaddr);
	पूर्ण

	/* Mark pages as uptodate, unlock and release */
	क्रम (i = 0; i < pages; i++) अणु
		flush_dcache_page(page[i]);
		SetPageUptodate(page[i]);
		unlock_page(page[i]);
		अगर (page[i] != target_page)
			put_page(page[i]);
	पूर्ण

	kमुक्त(actor);
	kमुक्त(page);

	वापस 0;

mark_errored:
	/* Decompression failed, mark pages as errored.  Target_page is
	 * dealt with by the caller
	 */
	क्रम (i = 0; i < pages; i++) अणु
		अगर (page[i] == शून्य || page[i] == target_page)
			जारी;
		flush_dcache_page(page[i]);
		SetPageError(page[i]);
		unlock_page(page[i]);
		put_page(page[i]);
	पूर्ण

out:
	kमुक्त(actor);
	kमुक्त(page);
	वापस res;
पूर्ण


अटल पूर्णांक squashfs_पढ़ो_cache(काष्ठा page *target_page, u64 block, पूर्णांक bsize,
	पूर्णांक pages, काष्ठा page **page, पूर्णांक bytes)
अणु
	काष्ठा inode *i = target_page->mapping->host;
	काष्ठा squashfs_cache_entry *buffer = squashfs_get_datablock(i->i_sb,
						 block, bsize);
	पूर्णांक res = buffer->error, n, offset = 0;

	अगर (res) अणु
		ERROR("Unable to read page, block %llx, size %x\n", block,
			bsize);
		जाओ out;
	पूर्ण

	क्रम (n = 0; n < pages && bytes > 0; n++,
			bytes -= PAGE_SIZE, offset += PAGE_SIZE) अणु
		पूर्णांक avail = min_t(पूर्णांक, bytes, PAGE_SIZE);

		अगर (page[n] == शून्य)
			जारी;

		squashfs_fill_page(page[n], buffer, offset, avail);
		unlock_page(page[n]);
		अगर (page[n] != target_page)
			put_page(page[n]);
	पूर्ण

out:
	squashfs_cache_put(buffer);
	वापस res;
पूर्ण
