<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/list_bl.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mbcache.h>

/*
 * Mbcache is a simple key-value store. Keys need not be unique, however
 * key-value pairs are expected to be unique (we use this fact in
 * mb_cache_entry_delete()).
 *
 * Ext2 and ext4 use this cache क्रम deduplication of extended attribute blocks.
 * Ext4 also uses it क्रम deduplication of xattr values stored in inodes.
 * They use hash of data as a key and provide a value that may represent a
 * block or inode number. That's why keys need not be unique (hash of dअगरferent
 * data may be the same). However user provided value always uniquely
 * identअगरies a cache entry.
 *
 * We provide functions क्रम creation and removal of entries, search by key,
 * and a special "delete entry with given key-value pair" operation. Fixed
 * size hash table is used क्रम fast key lookups.
 */

काष्ठा mb_cache अणु
	/* Hash table of entries */
	काष्ठा hlist_bl_head	*c_hash;
	/* log2 of hash table size */
	पूर्णांक			c_bucket_bits;
	/* Maximum entries in cache to aव्योम degrading hash too much */
	अचिन्हित दीर्घ		c_max_entries;
	/* Protects c_list, c_entry_count */
	spinlock_t		c_list_lock;
	काष्ठा list_head	c_list;
	/* Number of entries in cache */
	अचिन्हित दीर्घ		c_entry_count;
	काष्ठा shrinker		c_shrink;
	/* Work क्रम shrinking when the cache has too many entries */
	काष्ठा work_काष्ठा	c_shrink_work;
पूर्ण;

अटल काष्ठा kmem_cache *mb_entry_cache;

अटल अचिन्हित दीर्घ mb_cache_shrink(काष्ठा mb_cache *cache,
				     अचिन्हित दीर्घ nr_to_scan);

अटल अंतरभूत काष्ठा hlist_bl_head *mb_cache_entry_head(काष्ठा mb_cache *cache,
							u32 key)
अणु
	वापस &cache->c_hash[hash_32(key, cache->c_bucket_bits)];
पूर्ण

/*
 * Number of entries to reclaim synchronously when there are too many entries
 * in cache
 */
#घोषणा SYNC_SHRINK_BATCH 64

/*
 * mb_cache_entry_create - create entry in cache
 * @cache - cache where the entry should be created
 * @mask - gfp mask with which the entry should be allocated
 * @key - key of the entry
 * @value - value of the entry
 * @reusable - is the entry reusable by others?
 *
 * Creates entry in @cache with key @key and value @value. The function वापसs
 * -EBUSY अगर entry with the same key and value alपढ़ोy exists in cache.
 * Otherwise 0 is वापसed.
 */
पूर्णांक mb_cache_entry_create(काष्ठा mb_cache *cache, gfp_t mask, u32 key,
			  u64 value, bool reusable)
अणु
	काष्ठा mb_cache_entry *entry, *dup;
	काष्ठा hlist_bl_node *dup_node;
	काष्ठा hlist_bl_head *head;

	/* Schedule background reclaim अगर there are too many entries */
	अगर (cache->c_entry_count >= cache->c_max_entries)
		schedule_work(&cache->c_shrink_work);
	/* Do some sync reclaim अगर background reclaim cannot keep up */
	अगर (cache->c_entry_count >= 2*cache->c_max_entries)
		mb_cache_shrink(cache, SYNC_SHRINK_BATCH);

	entry = kmem_cache_alloc(mb_entry_cache, mask);
	अगर (!entry)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&entry->e_list);
	/* One ref क्रम hash, one ref वापसed */
	atomic_set(&entry->e_refcnt, 1);
	entry->e_key = key;
	entry->e_value = value;
	entry->e_reusable = reusable;
	entry->e_referenced = 0;
	head = mb_cache_entry_head(cache, key);
	hlist_bl_lock(head);
	hlist_bl_क्रम_each_entry(dup, dup_node, head, e_hash_list) अणु
		अगर (dup->e_key == key && dup->e_value == value) अणु
			hlist_bl_unlock(head);
			kmem_cache_मुक्त(mb_entry_cache, entry);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	hlist_bl_add_head(&entry->e_hash_list, head);
	hlist_bl_unlock(head);

	spin_lock(&cache->c_list_lock);
	list_add_tail(&entry->e_list, &cache->c_list);
	/* Grab ref क्रम LRU list */
	atomic_inc(&entry->e_refcnt);
	cache->c_entry_count++;
	spin_unlock(&cache->c_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mb_cache_entry_create);

व्योम __mb_cache_entry_मुक्त(काष्ठा mb_cache_entry *entry)
अणु
	kmem_cache_मुक्त(mb_entry_cache, entry);
पूर्ण
EXPORT_SYMBOL(__mb_cache_entry_मुक्त);

अटल काष्ठा mb_cache_entry *__entry_find(काष्ठा mb_cache *cache,
					   काष्ठा mb_cache_entry *entry,
					   u32 key)
अणु
	काष्ठा mb_cache_entry *old_entry = entry;
	काष्ठा hlist_bl_node *node;
	काष्ठा hlist_bl_head *head;

	head = mb_cache_entry_head(cache, key);
	hlist_bl_lock(head);
	अगर (entry && !hlist_bl_unhashed(&entry->e_hash_list))
		node = entry->e_hash_list.next;
	अन्यथा
		node = hlist_bl_first(head);
	जबतक (node) अणु
		entry = hlist_bl_entry(node, काष्ठा mb_cache_entry,
				       e_hash_list);
		अगर (entry->e_key == key && entry->e_reusable) अणु
			atomic_inc(&entry->e_refcnt);
			जाओ out;
		पूर्ण
		node = node->next;
	पूर्ण
	entry = शून्य;
out:
	hlist_bl_unlock(head);
	अगर (old_entry)
		mb_cache_entry_put(cache, old_entry);

	वापस entry;
पूर्ण

/*
 * mb_cache_entry_find_first - find the first reusable entry with the given key
 * @cache: cache where we should search
 * @key: key to look क्रम
 *
 * Search in @cache क्रम a reusable entry with key @key. Grअसल reference to the
 * first reusable entry found and वापसs the entry.
 */
काष्ठा mb_cache_entry *mb_cache_entry_find_first(काष्ठा mb_cache *cache,
						 u32 key)
अणु
	वापस __entry_find(cache, शून्य, key);
पूर्ण
EXPORT_SYMBOL(mb_cache_entry_find_first);

/*
 * mb_cache_entry_find_next - find next reusable entry with the same key
 * @cache: cache where we should search
 * @entry: entry to start search from
 *
 * Finds next reusable entry in the hash chain which has the same key as @entry.
 * If @entry is unhashed (which can happen when deletion of entry races with the
 * search), finds the first reusable entry in the hash chain. The function drops
 * reference to @entry and वापसs with a reference to the found entry.
 */
काष्ठा mb_cache_entry *mb_cache_entry_find_next(काष्ठा mb_cache *cache,
						काष्ठा mb_cache_entry *entry)
अणु
	वापस __entry_find(cache, entry, entry->e_key);
पूर्ण
EXPORT_SYMBOL(mb_cache_entry_find_next);

/*
 * mb_cache_entry_get - get a cache entry by value (and key)
 * @cache - cache we work with
 * @key - key
 * @value - value
 */
काष्ठा mb_cache_entry *mb_cache_entry_get(काष्ठा mb_cache *cache, u32 key,
					  u64 value)
अणु
	काष्ठा hlist_bl_node *node;
	काष्ठा hlist_bl_head *head;
	काष्ठा mb_cache_entry *entry;

	head = mb_cache_entry_head(cache, key);
	hlist_bl_lock(head);
	hlist_bl_क्रम_each_entry(entry, node, head, e_hash_list) अणु
		अगर (entry->e_key == key && entry->e_value == value) अणु
			atomic_inc(&entry->e_refcnt);
			जाओ out;
		पूर्ण
	पूर्ण
	entry = शून्य;
out:
	hlist_bl_unlock(head);
	वापस entry;
पूर्ण
EXPORT_SYMBOL(mb_cache_entry_get);

/* mb_cache_entry_delete - हटाओ a cache entry
 * @cache - cache we work with
 * @key - key
 * @value - value
 *
 * Remove entry from cache @cache with key @key and value @value.
 */
व्योम mb_cache_entry_delete(काष्ठा mb_cache *cache, u32 key, u64 value)
अणु
	काष्ठा hlist_bl_node *node;
	काष्ठा hlist_bl_head *head;
	काष्ठा mb_cache_entry *entry;

	head = mb_cache_entry_head(cache, key);
	hlist_bl_lock(head);
	hlist_bl_क्रम_each_entry(entry, node, head, e_hash_list) अणु
		अगर (entry->e_key == key && entry->e_value == value) अणु
			/* We keep hash list reference to keep entry alive */
			hlist_bl_del_init(&entry->e_hash_list);
			hlist_bl_unlock(head);
			spin_lock(&cache->c_list_lock);
			अगर (!list_empty(&entry->e_list)) अणु
				list_del_init(&entry->e_list);
				अगर (!WARN_ONCE(cache->c_entry_count == 0,
		"mbcache: attempt to decrement c_entry_count past zero"))
					cache->c_entry_count--;
				atomic_dec(&entry->e_refcnt);
			पूर्ण
			spin_unlock(&cache->c_list_lock);
			mb_cache_entry_put(cache, entry);
			वापस;
		पूर्ण
	पूर्ण
	hlist_bl_unlock(head);
पूर्ण
EXPORT_SYMBOL(mb_cache_entry_delete);

/* mb_cache_entry_touch - cache entry got used
 * @cache - cache the entry beदीर्घs to
 * @entry - entry that got used
 *
 * Marks entry as used to give hit higher chances of surviving in cache.
 */
व्योम mb_cache_entry_touch(काष्ठा mb_cache *cache,
			  काष्ठा mb_cache_entry *entry)
अणु
	entry->e_referenced = 1;
पूर्ण
EXPORT_SYMBOL(mb_cache_entry_touch);

अटल अचिन्हित दीर्घ mb_cache_count(काष्ठा shrinker *shrink,
				    काष्ठा shrink_control *sc)
अणु
	काष्ठा mb_cache *cache = container_of(shrink, काष्ठा mb_cache,
					      c_shrink);

	वापस cache->c_entry_count;
पूर्ण

/* Shrink number of entries in cache */
अटल अचिन्हित दीर्घ mb_cache_shrink(काष्ठा mb_cache *cache,
				     अचिन्हित दीर्घ nr_to_scan)
अणु
	काष्ठा mb_cache_entry *entry;
	काष्ठा hlist_bl_head *head;
	अचिन्हित दीर्घ shrunk = 0;

	spin_lock(&cache->c_list_lock);
	जबतक (nr_to_scan-- && !list_empty(&cache->c_list)) अणु
		entry = list_first_entry(&cache->c_list,
					 काष्ठा mb_cache_entry, e_list);
		अगर (entry->e_referenced) अणु
			entry->e_referenced = 0;
			list_move_tail(&entry->e_list, &cache->c_list);
			जारी;
		पूर्ण
		list_del_init(&entry->e_list);
		cache->c_entry_count--;
		/*
		 * We keep LRU list reference so that entry करोesn't go away
		 * from under us.
		 */
		spin_unlock(&cache->c_list_lock);
		head = mb_cache_entry_head(cache, entry->e_key);
		hlist_bl_lock(head);
		अगर (!hlist_bl_unhashed(&entry->e_hash_list)) अणु
			hlist_bl_del_init(&entry->e_hash_list);
			atomic_dec(&entry->e_refcnt);
		पूर्ण
		hlist_bl_unlock(head);
		अगर (mb_cache_entry_put(cache, entry))
			shrunk++;
		cond_resched();
		spin_lock(&cache->c_list_lock);
	पूर्ण
	spin_unlock(&cache->c_list_lock);

	वापस shrunk;
पूर्ण

अटल अचिन्हित दीर्घ mb_cache_scan(काष्ठा shrinker *shrink,
				   काष्ठा shrink_control *sc)
अणु
	काष्ठा mb_cache *cache = container_of(shrink, काष्ठा mb_cache,
					      c_shrink);
	वापस mb_cache_shrink(cache, sc->nr_to_scan);
पूर्ण

/* We shrink 1/X of the cache when we have too many entries in it */
#घोषणा SHRINK_DIVISOR 16

अटल व्योम mb_cache_shrink_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mb_cache *cache = container_of(work, काष्ठा mb_cache,
					      c_shrink_work);
	mb_cache_shrink(cache, cache->c_max_entries / SHRINK_DIVISOR);
पूर्ण

/*
 * mb_cache_create - create cache
 * @bucket_bits: log2 of the hash table size
 *
 * Create cache क्रम keys with 2^bucket_bits hash entries.
 */
काष्ठा mb_cache *mb_cache_create(पूर्णांक bucket_bits)
अणु
	काष्ठा mb_cache *cache;
	अचिन्हित दीर्घ bucket_count = 1UL << bucket_bits;
	अचिन्हित दीर्घ i;

	cache = kzalloc(माप(काष्ठा mb_cache), GFP_KERNEL);
	अगर (!cache)
		जाओ err_out;
	cache->c_bucket_bits = bucket_bits;
	cache->c_max_entries = bucket_count << 4;
	INIT_LIST_HEAD(&cache->c_list);
	spin_lock_init(&cache->c_list_lock);
	cache->c_hash = kदो_स्मृति_array(bucket_count,
				      माप(काष्ठा hlist_bl_head),
				      GFP_KERNEL);
	अगर (!cache->c_hash) अणु
		kमुक्त(cache);
		जाओ err_out;
	पूर्ण
	क्रम (i = 0; i < bucket_count; i++)
		INIT_HLIST_BL_HEAD(&cache->c_hash[i]);

	cache->c_shrink.count_objects = mb_cache_count;
	cache->c_shrink.scan_objects = mb_cache_scan;
	cache->c_shrink.seeks = DEFAULT_SEEKS;
	अगर (रेजिस्टर_shrinker(&cache->c_shrink)) अणु
		kमुक्त(cache->c_hash);
		kमुक्त(cache);
		जाओ err_out;
	पूर्ण

	INIT_WORK(&cache->c_shrink_work, mb_cache_shrink_worker);

	वापस cache;

err_out:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mb_cache_create);

/*
 * mb_cache_destroy - destroy cache
 * @cache: the cache to destroy
 *
 * Free all entries in cache and cache itself. Caller must make sure nobody
 * (except shrinker) can reach @cache when calling this.
 */
व्योम mb_cache_destroy(काष्ठा mb_cache *cache)
अणु
	काष्ठा mb_cache_entry *entry, *next;

	unरेजिस्टर_shrinker(&cache->c_shrink);

	/*
	 * We करोn't bother with any locking. Cache must not be used at this
	 * poपूर्णांक.
	 */
	list_क्रम_each_entry_safe(entry, next, &cache->c_list, e_list) अणु
		अगर (!hlist_bl_unhashed(&entry->e_hash_list)) अणु
			hlist_bl_del_init(&entry->e_hash_list);
			atomic_dec(&entry->e_refcnt);
		पूर्ण अन्यथा
			WARN_ON(1);
		list_del(&entry->e_list);
		WARN_ON(atomic_पढ़ो(&entry->e_refcnt) != 1);
		mb_cache_entry_put(cache, entry);
	पूर्ण
	kमुक्त(cache->c_hash);
	kमुक्त(cache);
पूर्ण
EXPORT_SYMBOL(mb_cache_destroy);

अटल पूर्णांक __init mbcache_init(व्योम)
अणु
	mb_entry_cache = kmem_cache_create("mbcache",
				माप(काष्ठा mb_cache_entry), 0,
				SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD, शून्य);
	अगर (!mb_entry_cache)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम __निकास mbcache_निकास(व्योम)
अणु
	kmem_cache_destroy(mb_entry_cache);
पूर्ण

module_init(mbcache_init)
module_निकास(mbcache_निकास)

MODULE_AUTHOR("Jan Kara <jack@suse.cz>");
MODULE_DESCRIPTION("Meta block cache (for extended attributes)");
MODULE_LICENSE("GPL");
