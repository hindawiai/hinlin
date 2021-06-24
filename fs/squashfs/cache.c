<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * cache.c
 */

/*
 * Blocks in Squashfs are compressed.  To aव्योम repeatedly decompressing
 * recently accessed data Squashfs uses two small metadata and fragment caches.
 *
 * This file implements a generic cache implementation used क्रम both caches,
 * plus functions layered ontop of the generic cache implementation to
 * access the metadata and fragment caches.
 *
 * To aव्योम out of memory and fragmentation issues with vदो_स्मृति the cache
 * uses sequences of kदो_स्मृतिed PAGE_SIZE buffers.
 *
 * It should be noted that the cache is not used क्रम file datablocks, these
 * are decompressed and cached in the page-cache in the normal way.  The
 * cache is only used to temporarily cache fragment and metadata blocks
 * which have been पढ़ो as as a result of a metadata (i.e. inode or
 * directory) or fragment access.  Because metadata and fragments are packed
 * together पूर्णांकo blocks (to gain greater compression) the पढ़ो of a particular
 * piece of metadata or fragment will retrieve other metadata/fragments which
 * have been packed with it, these because of locality-of-reference may be पढ़ो
 * in the near future. Temporarily caching them ensures they are available क्रम
 * near future access without requiring an additional पढ़ो and decompress.
 */

#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/pagemap.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs.h"
#समावेश "page_actor.h"

/*
 * Look-up block in cache, and increment usage count.  If not in cache, पढ़ो
 * and decompress it from disk.
 */
काष्ठा squashfs_cache_entry *squashfs_cache_get(काष्ठा super_block *sb,
	काष्ठा squashfs_cache *cache, u64 block, पूर्णांक length)
अणु
	पूर्णांक i, n;
	काष्ठा squashfs_cache_entry *entry;

	spin_lock(&cache->lock);

	जबतक (1) अणु
		क्रम (i = cache->curr_blk, n = 0; n < cache->entries; n++) अणु
			अगर (cache->entry[i].block == block) अणु
				cache->curr_blk = i;
				अवरोध;
			पूर्ण
			i = (i + 1) % cache->entries;
		पूर्ण

		अगर (n == cache->entries) अणु
			/*
			 * Block not in cache, अगर all cache entries are used
			 * go to sleep रुकोing क्रम one to become available.
			 */
			अगर (cache->unused == 0) अणु
				cache->num_रुकोers++;
				spin_unlock(&cache->lock);
				रुको_event(cache->रुको_queue, cache->unused);
				spin_lock(&cache->lock);
				cache->num_रुकोers--;
				जारी;
			पूर्ण

			/*
			 * At least one unused cache entry.  A simple
			 * round-robin strategy is used to choose the entry to
			 * be evicted from the cache.
			 */
			i = cache->next_blk;
			क्रम (n = 0; n < cache->entries; n++) अणु
				अगर (cache->entry[i].refcount == 0)
					अवरोध;
				i = (i + 1) % cache->entries;
			पूर्ण

			cache->next_blk = (i + 1) % cache->entries;
			entry = &cache->entry[i];

			/*
			 * Initialise chosen cache entry, and fill it in from
			 * disk.
			 */
			cache->unused--;
			entry->block = block;
			entry->refcount = 1;
			entry->pending = 1;
			entry->num_रुकोers = 0;
			entry->error = 0;
			spin_unlock(&cache->lock);

			entry->length = squashfs_पढ़ो_data(sb, block, length,
				&entry->next_index, entry->actor);

			spin_lock(&cache->lock);

			अगर (entry->length < 0)
				entry->error = entry->length;

			entry->pending = 0;

			/*
			 * While filling this entry one or more other processes
			 * have looked it up in the cache, and have slept
			 * रुकोing क्रम it to become available.
			 */
			अगर (entry->num_रुकोers) अणु
				spin_unlock(&cache->lock);
				wake_up_all(&entry->रुको_queue);
			पूर्ण अन्यथा
				spin_unlock(&cache->lock);

			जाओ out;
		पूर्ण

		/*
		 * Block alपढ़ोy in cache.  Increment refcount so it करोesn't
		 * get reused until we're finished with it, अगर it was
		 * previously unused there's one less cache entry available
		 * क्रम reuse.
		 */
		entry = &cache->entry[i];
		अगर (entry->refcount == 0)
			cache->unused--;
		entry->refcount++;

		/*
		 * If the entry is currently being filled in by another process
		 * go to sleep रुकोing क्रम it to become available.
		 */
		अगर (entry->pending) अणु
			entry->num_रुकोers++;
			spin_unlock(&cache->lock);
			रुको_event(entry->रुको_queue, !entry->pending);
		पूर्ण अन्यथा
			spin_unlock(&cache->lock);

		जाओ out;
	पूर्ण

out:
	TRACE("Got %s %d, start block %lld, refcount %d, error %d\n",
		cache->name, i, entry->block, entry->refcount, entry->error);

	अगर (entry->error)
		ERROR("Unable to read %s cache entry [%llx]\n", cache->name,
							block);
	वापस entry;
पूर्ण


/*
 * Release cache entry, once usage count is zero it can be reused.
 */
व्योम squashfs_cache_put(काष्ठा squashfs_cache_entry *entry)
अणु
	काष्ठा squashfs_cache *cache = entry->cache;

	spin_lock(&cache->lock);
	entry->refcount--;
	अगर (entry->refcount == 0) अणु
		cache->unused++;
		/*
		 * If there's any processes रुकोing क्रम a block to become
		 * available, wake one up.
		 */
		अगर (cache->num_रुकोers) अणु
			spin_unlock(&cache->lock);
			wake_up(&cache->रुको_queue);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock(&cache->lock);
पूर्ण

/*
 * Delete cache reclaiming all kदो_स्मृतिed buffers.
 */
व्योम squashfs_cache_delete(काष्ठा squashfs_cache *cache)
अणु
	पूर्णांक i, j;

	अगर (cache == शून्य)
		वापस;

	क्रम (i = 0; i < cache->entries; i++) अणु
		अगर (cache->entry[i].data) अणु
			क्रम (j = 0; j < cache->pages; j++)
				kमुक्त(cache->entry[i].data[j]);
			kमुक्त(cache->entry[i].data);
		पूर्ण
		kमुक्त(cache->entry[i].actor);
	पूर्ण

	kमुक्त(cache->entry);
	kमुक्त(cache);
पूर्ण


/*
 * Initialise cache allocating the specअगरied number of entries, each of
 * size block_size.  To aव्योम vदो_स्मृति fragmentation issues each entry
 * is allocated as a sequence of kदो_स्मृतिed PAGE_SIZE buffers.
 */
काष्ठा squashfs_cache *squashfs_cache_init(अक्षर *name, पूर्णांक entries,
	पूर्णांक block_size)
अणु
	पूर्णांक i, j;
	काष्ठा squashfs_cache *cache = kzalloc(माप(*cache), GFP_KERNEL);

	अगर (cache == शून्य) अणु
		ERROR("Failed to allocate %s cache\n", name);
		वापस शून्य;
	पूर्ण

	cache->entry = kसुस्मृति(entries, माप(*(cache->entry)), GFP_KERNEL);
	अगर (cache->entry == शून्य) अणु
		ERROR("Failed to allocate %s cache\n", name);
		जाओ cleanup;
	पूर्ण

	cache->curr_blk = 0;
	cache->next_blk = 0;
	cache->unused = entries;
	cache->entries = entries;
	cache->block_size = block_size;
	cache->pages = block_size >> PAGE_SHIFT;
	cache->pages = cache->pages ? cache->pages : 1;
	cache->name = name;
	cache->num_रुकोers = 0;
	spin_lock_init(&cache->lock);
	init_रुकोqueue_head(&cache->रुको_queue);

	क्रम (i = 0; i < entries; i++) अणु
		काष्ठा squashfs_cache_entry *entry = &cache->entry[i];

		init_रुकोqueue_head(&cache->entry[i].रुको_queue);
		entry->cache = cache;
		entry->block = SQUASHFS_INVALID_BLK;
		entry->data = kसुस्मृति(cache->pages, माप(व्योम *), GFP_KERNEL);
		अगर (entry->data == शून्य) अणु
			ERROR("Failed to allocate %s cache entry\n", name);
			जाओ cleanup;
		पूर्ण

		क्रम (j = 0; j < cache->pages; j++) अणु
			entry->data[j] = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
			अगर (entry->data[j] == शून्य) अणु
				ERROR("Failed to allocate %s buffer\n", name);
				जाओ cleanup;
			पूर्ण
		पूर्ण

		entry->actor = squashfs_page_actor_init(entry->data,
						cache->pages, 0);
		अगर (entry->actor == शून्य) अणु
			ERROR("Failed to allocate %s cache entry\n", name);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	वापस cache;

cleanup:
	squashfs_cache_delete(cache);
	वापस शून्य;
पूर्ण


/*
 * Copy up to length bytes from cache entry to buffer starting at offset bytes
 * पूर्णांकo the cache entry.  If there's not length bytes then copy the number of
 * bytes available.  In all हालs वापस the number of bytes copied.
 */
पूर्णांक squashfs_copy_data(व्योम *buffer, काष्ठा squashfs_cache_entry *entry,
		पूर्णांक offset, पूर्णांक length)
अणु
	पूर्णांक reमुख्यing = length;

	अगर (length == 0)
		वापस 0;
	अन्यथा अगर (buffer == शून्य)
		वापस min(length, entry->length - offset);

	जबतक (offset < entry->length) अणु
		व्योम *buff = entry->data[offset / PAGE_SIZE]
				+ (offset % PAGE_SIZE);
		पूर्णांक bytes = min_t(पूर्णांक, entry->length - offset,
				PAGE_SIZE - (offset % PAGE_SIZE));

		अगर (bytes >= reमुख्यing) अणु
			स_नकल(buffer, buff, reमुख्यing);
			reमुख्यing = 0;
			अवरोध;
		पूर्ण

		स_नकल(buffer, buff, bytes);
		buffer += bytes;
		reमुख्यing -= bytes;
		offset += bytes;
	पूर्ण

	वापस length - reमुख्यing;
पूर्ण


/*
 * Read length bytes from metadata position <block, offset> (block is the
 * start of the compressed block on disk, and offset is the offset पूर्णांकo
 * the block once decompressed).  Data is packed पूर्णांकo consecutive blocks,
 * and length bytes may require पढ़ोing more than one block.
 */
पूर्णांक squashfs_पढ़ो_metadata(काष्ठा super_block *sb, व्योम *buffer,
		u64 *block, पूर्णांक *offset, पूर्णांक length)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	पूर्णांक bytes, res = length;
	काष्ठा squashfs_cache_entry *entry;

	TRACE("Entered squashfs_read_metadata [%llx:%x]\n", *block, *offset);

	अगर (unlikely(length < 0))
		वापस -EIO;

	जबतक (length) अणु
		entry = squashfs_cache_get(sb, msblk->block_cache, *block, 0);
		अगर (entry->error) अणु
			res = entry->error;
			जाओ error;
		पूर्ण अन्यथा अगर (*offset >= entry->length) अणु
			res = -EIO;
			जाओ error;
		पूर्ण

		bytes = squashfs_copy_data(buffer, entry, *offset, length);
		अगर (buffer)
			buffer += bytes;
		length -= bytes;
		*offset += bytes;

		अगर (*offset == entry->length) अणु
			*block = entry->next_index;
			*offset = 0;
		पूर्ण

		squashfs_cache_put(entry);
	पूर्ण

	वापस res;

error:
	squashfs_cache_put(entry);
	वापस res;
पूर्ण


/*
 * Look-up in the fragmment cache the fragment located at <start_block> in the
 * fileप्रणाली.  If necessary पढ़ो and decompress it from disk.
 */
काष्ठा squashfs_cache_entry *squashfs_get_fragment(काष्ठा super_block *sb,
				u64 start_block, पूर्णांक length)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;

	वापस squashfs_cache_get(sb, msblk->fragment_cache, start_block,
		length);
पूर्ण


/*
 * Read and decompress the datablock located at <start_block> in the
 * fileप्रणाली.  The cache is used here to aव्योम duplicating locking and
 * पढ़ो/decompress code.
 */
काष्ठा squashfs_cache_entry *squashfs_get_datablock(काष्ठा super_block *sb,
				u64 start_block, पूर्णांक length)
अणु
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;

	वापस squashfs_cache_get(sb, msblk->पढ़ो_page, start_block, length);
पूर्ण


/*
 * Read a fileप्रणाली table (uncompressed sequence of bytes) from disk
 */
व्योम *squashfs_पढ़ो_table(काष्ठा super_block *sb, u64 block, पूर्णांक length)
अणु
	पूर्णांक pages = (length + PAGE_SIZE - 1) >> PAGE_SHIFT;
	पूर्णांक i, res;
	व्योम *table, *buffer, **data;
	काष्ठा squashfs_page_actor *actor;

	table = buffer = kदो_स्मृति(length, GFP_KERNEL);
	अगर (table == शून्य)
		वापस ERR_PTR(-ENOMEM);

	data = kसुस्मृति(pages, माप(व्योम *), GFP_KERNEL);
	अगर (data == शून्य) अणु
		res = -ENOMEM;
		जाओ failed;
	पूर्ण

	actor = squashfs_page_actor_init(data, pages, length);
	अगर (actor == शून्य) अणु
		res = -ENOMEM;
		जाओ failed2;
	पूर्ण

	क्रम (i = 0; i < pages; i++, buffer += PAGE_SIZE)
		data[i] = buffer;

	res = squashfs_पढ़ो_data(sb, block, length |
		SQUASHFS_COMPRESSED_BIT_BLOCK, शून्य, actor);

	kमुक्त(data);
	kमुक्त(actor);

	अगर (res < 0)
		जाओ failed;

	वापस table;

failed2:
	kमुक्त(data);
failed:
	kमुक्त(table);
	वापस ERR_PTR(res);
पूर्ण
