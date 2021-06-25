<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * file.c
 */

/*
 * This file contains code क्रम handling regular files.  A regular file
 * consists of a sequence of contiguous compressed blocks, and/or a
 * compressed fragment block (tail-end packed block).   The compressed size
 * of each datablock is stored in a block list contained within the
 * file inode (itself stored in one or more compressed metadata blocks).
 *
 * To speed up access to datablocks when पढ़ोing 'large' files (256 Mbytes or
 * larger), the code implements an index cache that caches the mapping from
 * block index to datablock location on disk.
 *
 * The index cache allows Squashfs to handle large files (up to 1.75 TiB) जबतक
 * retaining a simple and space-efficient block list on disk.  The cache
 * is split पूर्णांकo slots, caching up to eight 224 GiB files (128 KiB blocks).
 * Larger files use multiple slots, with 1.75 TiB files using all 8 slots.
 * The index cache is deचिन्हित to be memory efficient, and by शेष uses
 * 16 KiB.
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

/*
 * Locate cache slot in range [offset, index] क्रम specअगरied inode.  If
 * there's more than one वापस the slot बंदst to index.
 */
अटल काष्ठा meta_index *locate_meta_index(काष्ठा inode *inode, पूर्णांक offset,
				पूर्णांक index)
अणु
	काष्ठा meta_index *meta = शून्य;
	काष्ठा squashfs_sb_info *msblk = inode->i_sb->s_fs_info;
	पूर्णांक i;

	mutex_lock(&msblk->meta_index_mutex);

	TRACE("locate_meta_index: index %d, offset %d\n", index, offset);

	अगर (msblk->meta_index == शून्य)
		जाओ not_allocated;

	क्रम (i = 0; i < SQUASHFS_META_SLOTS; i++) अणु
		अगर (msblk->meta_index[i].inode_number == inode->i_ino &&
				msblk->meta_index[i].offset >= offset &&
				msblk->meta_index[i].offset <= index &&
				msblk->meta_index[i].locked == 0) अणु
			TRACE("locate_meta_index: entry %d, offset %d\n", i,
					msblk->meta_index[i].offset);
			meta = &msblk->meta_index[i];
			offset = meta->offset;
		पूर्ण
	पूर्ण

	अगर (meta)
		meta->locked = 1;

not_allocated:
	mutex_unlock(&msblk->meta_index_mutex);

	वापस meta;
पूर्ण


/*
 * Find and initialise an empty cache slot क्रम index offset.
 */
अटल काष्ठा meta_index *empty_meta_index(काष्ठा inode *inode, पूर्णांक offset,
				पूर्णांक skip)
अणु
	काष्ठा squashfs_sb_info *msblk = inode->i_sb->s_fs_info;
	काष्ठा meta_index *meta = शून्य;
	पूर्णांक i;

	mutex_lock(&msblk->meta_index_mutex);

	TRACE("empty_meta_index: offset %d, skip %d\n", offset, skip);

	अगर (msblk->meta_index == शून्य) अणु
		/*
		 * First समय cache index has been used, allocate and
		 * initialise.  The cache index could be allocated at
		 * mount समय but करोing it here means it is allocated only
		 * अगर a 'large' file is पढ़ो.
		 */
		msblk->meta_index = kसुस्मृति(SQUASHFS_META_SLOTS,
			माप(*(msblk->meta_index)), GFP_KERNEL);
		अगर (msblk->meta_index == शून्य) अणु
			ERROR("Failed to allocate meta_index\n");
			जाओ failed;
		पूर्ण
		क्रम (i = 0; i < SQUASHFS_META_SLOTS; i++) अणु
			msblk->meta_index[i].inode_number = 0;
			msblk->meta_index[i].locked = 0;
		पूर्ण
		msblk->next_meta_index = 0;
	पूर्ण

	क्रम (i = SQUASHFS_META_SLOTS; i &&
			msblk->meta_index[msblk->next_meta_index].locked; i--)
		msblk->next_meta_index = (msblk->next_meta_index + 1) %
			SQUASHFS_META_SLOTS;

	अगर (i == 0) अणु
		TRACE("empty_meta_index: failed!\n");
		जाओ failed;
	पूर्ण

	TRACE("empty_meta_index: returned meta entry %d, %p\n",
			msblk->next_meta_index,
			&msblk->meta_index[msblk->next_meta_index]);

	meta = &msblk->meta_index[msblk->next_meta_index];
	msblk->next_meta_index = (msblk->next_meta_index + 1) %
			SQUASHFS_META_SLOTS;

	meta->inode_number = inode->i_ino;
	meta->offset = offset;
	meta->skip = skip;
	meta->entries = 0;
	meta->locked = 1;

failed:
	mutex_unlock(&msblk->meta_index_mutex);
	वापस meta;
पूर्ण


अटल व्योम release_meta_index(काष्ठा inode *inode, काष्ठा meta_index *meta)
अणु
	काष्ठा squashfs_sb_info *msblk = inode->i_sb->s_fs_info;
	mutex_lock(&msblk->meta_index_mutex);
	meta->locked = 0;
	mutex_unlock(&msblk->meta_index_mutex);
पूर्ण


/*
 * Read the next n blocks from the block list, starting from
 * metadata block <start_block, offset>.
 */
अटल दीर्घ दीर्घ पढ़ो_indexes(काष्ठा super_block *sb, पूर्णांक n,
				u64 *start_block, पूर्णांक *offset)
अणु
	पूर्णांक err, i;
	दीर्घ दीर्घ block = 0;
	__le32 *blist = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);

	अगर (blist == शून्य) अणु
		ERROR("read_indexes: Failed to allocate block_list\n");
		वापस -ENOMEM;
	पूर्ण

	जबतक (n) अणु
		पूर्णांक blocks = min_t(पूर्णांक, n, PAGE_SIZE >> 2);

		err = squashfs_पढ़ो_metadata(sb, blist, start_block,
				offset, blocks << 2);
		अगर (err < 0) अणु
			ERROR("read_indexes: reading block [%llx:%x]\n",
				*start_block, *offset);
			जाओ failure;
		पूर्ण

		क्रम (i = 0; i < blocks; i++) अणु
			पूर्णांक size = squashfs_block_size(blist[i]);
			अगर (size < 0) अणु
				err = size;
				जाओ failure;
			पूर्ण
			block += SQUASHFS_COMPRESSED_SIZE_BLOCK(size);
		पूर्ण
		n -= blocks;
	पूर्ण

	kमुक्त(blist);
	वापस block;

failure:
	kमुक्त(blist);
	वापस err;
पूर्ण


/*
 * Each cache index slot has SQUASHFS_META_ENTRIES, each of which
 * can cache one index -> datablock/blocklist-block mapping.  We wish
 * to distribute these over the length of the file, entry[0] maps index x,
 * entry[1] maps index x + skip, entry[2] maps index x + 2 * skip, and so on.
 * The larger the file, the greater the skip factor.  The skip factor is
 * limited to the size of the metadata cache (SQUASHFS_CACHED_BLKS) to ensure
 * the number of metadata blocks that need to be पढ़ो fits पूर्णांकo the cache.
 * If the skip factor is limited in this way then the file will use multiple
 * slots.
 */
अटल अंतरभूत पूर्णांक calculate_skip(u64 blocks)
अणु
	u64 skip = blocks / ((SQUASHFS_META_ENTRIES + 1)
		 * SQUASHFS_META_INDEXES);
	वापस min((u64) SQUASHFS_CACHED_BLKS - 1, skip + 1);
पूर्ण


/*
 * Search and grow the index cache क्रम the specअगरied inode, वापसing the
 * on-disk locations of the datablock and block list metadata block
 * <index_block, index_offset> क्रम index (scaled to nearest cache index).
 */
अटल पूर्णांक fill_meta_index(काष्ठा inode *inode, पूर्णांक index,
		u64 *index_block, पूर्णांक *index_offset, u64 *data_block)
अणु
	काष्ठा squashfs_sb_info *msblk = inode->i_sb->s_fs_info;
	पूर्णांक skip = calculate_skip(i_size_पढ़ो(inode) >> msblk->block_log);
	पूर्णांक offset = 0;
	काष्ठा meta_index *meta;
	काष्ठा meta_entry *meta_entry;
	u64 cur_index_block = squashfs_i(inode)->block_list_start;
	पूर्णांक cur_offset = squashfs_i(inode)->offset;
	u64 cur_data_block = squashfs_i(inode)->start;
	पूर्णांक err, i;

	/*
	 * Scale index to cache index (cache slot entry)
	 */
	index /= SQUASHFS_META_INDEXES * skip;

	जबतक (offset < index) अणु
		meta = locate_meta_index(inode, offset + 1, index);

		अगर (meta == शून्य) अणु
			meta = empty_meta_index(inode, offset + 1, skip);
			अगर (meta == शून्य)
				जाओ all_करोne;
		पूर्ण अन्यथा अणु
			offset = index < meta->offset + meta->entries ? index :
				meta->offset + meta->entries - 1;
			meta_entry = &meta->meta_entry[offset - meta->offset];
			cur_index_block = meta_entry->index_block +
				msblk->inode_table;
			cur_offset = meta_entry->offset;
			cur_data_block = meta_entry->data_block;
			TRACE("get_meta_index: offset %d, meta->offset %d, "
				"meta->entries %d\n", offset, meta->offset,
				meta->entries);
			TRACE("get_meta_index: index_block 0x%llx, offset 0x%x"
				" data_block 0x%llx\n", cur_index_block,
				cur_offset, cur_data_block);
		पूर्ण

		/*
		 * If necessary grow cache slot by पढ़ोing block list.  Cache
		 * slot is extended up to index or to the end of the slot, in
		 * which हाल further slots will be used.
		 */
		क्रम (i = meta->offset + meta->entries; i <= index &&
				i < meta->offset + SQUASHFS_META_ENTRIES; i++) अणु
			पूर्णांक blocks = skip * SQUASHFS_META_INDEXES;
			दीर्घ दीर्घ res = पढ़ो_indexes(inode->i_sb, blocks,
					&cur_index_block, &cur_offset);

			अगर (res < 0) अणु
				अगर (meta->entries == 0)
					/*
					 * Don't leave an empty slot on पढ़ो
					 * error allocated to this inode...
					 */
					meta->inode_number = 0;
				err = res;
				जाओ failed;
			पूर्ण

			cur_data_block += res;
			meta_entry = &meta->meta_entry[i - meta->offset];
			meta_entry->index_block = cur_index_block -
				msblk->inode_table;
			meta_entry->offset = cur_offset;
			meta_entry->data_block = cur_data_block;
			meta->entries++;
			offset++;
		पूर्ण

		TRACE("get_meta_index: meta->offset %d, meta->entries %d\n",
				meta->offset, meta->entries);

		release_meta_index(inode, meta);
	पूर्ण

all_करोne:
	*index_block = cur_index_block;
	*index_offset = cur_offset;
	*data_block = cur_data_block;

	/*
	 * Scale cache index (cache slot entry) to index
	 */
	वापस offset * SQUASHFS_META_INDEXES * skip;

failed:
	release_meta_index(inode, meta);
	वापस err;
पूर्ण


/*
 * Get the on-disk location and compressed size of the datablock
 * specअगरied by index.  Fill_meta_index() करोes most of the work.
 */
अटल पूर्णांक पढ़ो_blocklist(काष्ठा inode *inode, पूर्णांक index, u64 *block)
अणु
	u64 start;
	दीर्घ दीर्घ blks;
	पूर्णांक offset;
	__le32 size;
	पूर्णांक res = fill_meta_index(inode, index, &start, &offset, block);

	TRACE("read_blocklist: res %d, index %d, start 0x%llx, offset"
		       " 0x%x, block 0x%llx\n", res, index, start, offset,
			*block);

	अगर (res < 0)
		वापस res;

	/*
	 * res contains the index of the mapping वापसed by fill_meta_index(),
	 * this will likely be less than the desired index (because the
	 * meta_index cache works at a higher granularity).  Read any
	 * extra block indexes needed.
	 */
	अगर (res < index) अणु
		blks = पढ़ो_indexes(inode->i_sb, index - res, &start, &offset);
		अगर (blks < 0)
			वापस (पूर्णांक) blks;
		*block += blks;
	पूर्ण

	/*
	 * Read length of block specअगरied by index.
	 */
	res = squashfs_पढ़ो_metadata(inode->i_sb, &size, &start, &offset,
			माप(size));
	अगर (res < 0)
		वापस res;
	वापस squashfs_block_size(size);
पूर्ण

व्योम squashfs_fill_page(काष्ठा page *page, काष्ठा squashfs_cache_entry *buffer, पूर्णांक offset, पूर्णांक avail)
अणु
	पूर्णांक copied;
	व्योम *pageaddr;

	pageaddr = kmap_atomic(page);
	copied = squashfs_copy_data(pageaddr, buffer, offset, avail);
	स_रखो(pageaddr + copied, 0, PAGE_SIZE - copied);
	kunmap_atomic(pageaddr);

	flush_dcache_page(page);
	अगर (copied == avail)
		SetPageUptodate(page);
	अन्यथा
		SetPageError(page);
पूर्ण

/* Copy data पूर्णांकo page cache  */
व्योम squashfs_copy_cache(काष्ठा page *page, काष्ठा squashfs_cache_entry *buffer,
	पूर्णांक bytes, पूर्णांक offset)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा squashfs_sb_info *msblk = inode->i_sb->s_fs_info;
	पूर्णांक i, mask = (1 << (msblk->block_log - PAGE_SHIFT)) - 1;
	पूर्णांक start_index = page->index & ~mask, end_index = start_index | mask;

	/*
	 * Loop copying datablock पूर्णांकo pages.  As the datablock likely covers
	 * many PAGE_SIZE pages (शेष block size is 128 KiB) explicitly
	 * grab the pages from the page cache, except क्रम the page that we've
	 * been called to fill.
	 */
	क्रम (i = start_index; i <= end_index && bytes > 0; i++,
			bytes -= PAGE_SIZE, offset += PAGE_SIZE) अणु
		काष्ठा page *push_page;
		पूर्णांक avail = buffer ? min_t(पूर्णांक, bytes, PAGE_SIZE) : 0;

		TRACE("bytes %d, i %d, available_bytes %d\n", bytes, i, avail);

		push_page = (i == page->index) ? page :
			grab_cache_page_noरुको(page->mapping, i);

		अगर (!push_page)
			जारी;

		अगर (PageUptodate(push_page))
			जाओ skip_page;

		squashfs_fill_page(push_page, buffer, offset, avail);
skip_page:
		unlock_page(push_page);
		अगर (i != page->index)
			put_page(push_page);
	पूर्ण
पूर्ण

/* Read datablock stored packed inside a fragment (tail-end packed block) */
अटल पूर्णांक squashfs_पढ़ोpage_fragment(काष्ठा page *page, पूर्णांक expected)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा squashfs_cache_entry *buffer = squashfs_get_fragment(inode->i_sb,
		squashfs_i(inode)->fragment_block,
		squashfs_i(inode)->fragment_size);
	पूर्णांक res = buffer->error;

	अगर (res)
		ERROR("Unable to read page, block %llx, size %x\n",
			squashfs_i(inode)->fragment_block,
			squashfs_i(inode)->fragment_size);
	अन्यथा
		squashfs_copy_cache(page, buffer, expected,
			squashfs_i(inode)->fragment_offset);

	squashfs_cache_put(buffer);
	वापस res;
पूर्ण

अटल पूर्णांक squashfs_पढ़ोpage_sparse(काष्ठा page *page, पूर्णांक expected)
अणु
	squashfs_copy_cache(page, शून्य, expected, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक squashfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा squashfs_sb_info *msblk = inode->i_sb->s_fs_info;
	पूर्णांक index = page->index >> (msblk->block_log - PAGE_SHIFT);
	पूर्णांक file_end = i_size_पढ़ो(inode) >> msblk->block_log;
	पूर्णांक expected = index == file_end ?
			(i_size_पढ़ो(inode) & (msblk->block_size - 1)) :
			 msblk->block_size;
	पूर्णांक res;
	व्योम *pageaddr;

	TRACE("Entered squashfs_readpage, page index %lx, start block %llx\n",
				page->index, squashfs_i(inode)->start);

	अगर (page->index >= ((i_size_पढ़ो(inode) + PAGE_SIZE - 1) >>
					PAGE_SHIFT))
		जाओ out;

	अगर (index < file_end || squashfs_i(inode)->fragment_block ==
					SQUASHFS_INVALID_BLK) अणु
		u64 block = 0;
		पूर्णांक bsize = पढ़ो_blocklist(inode, index, &block);
		अगर (bsize < 0)
			जाओ error_out;

		अगर (bsize == 0)
			res = squashfs_पढ़ोpage_sparse(page, expected);
		अन्यथा
			res = squashfs_पढ़ोpage_block(page, block, bsize, expected);
	पूर्ण अन्यथा
		res = squashfs_पढ़ोpage_fragment(page, expected);

	अगर (!res)
		वापस 0;

error_out:
	SetPageError(page);
out:
	pageaddr = kmap_atomic(page);
	स_रखो(pageaddr, 0, PAGE_SIZE);
	kunmap_atomic(pageaddr);
	flush_dcache_page(page);
	अगर (!PageError(page))
		SetPageUptodate(page);
	unlock_page(page);

	वापस 0;
पूर्ण


स्थिर काष्ठा address_space_operations squashfs_aops = अणु
	.पढ़ोpage = squashfs_पढ़ोpage
पूर्ण;
