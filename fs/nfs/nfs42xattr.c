<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2019, 2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 *
 * User extended attribute client side cache functions.
 *
 * Author: Frank van der Linden <fllinden@amazon.com>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/refcount.h>
#समावेश <uapi/linux/xattr.h>

#समावेश "nfs4_fs.h"
#समावेश "internal.h"

/*
 * User extended attributes client side caching is implemented by having
 * a cache काष्ठाure attached to NFS inodes. This काष्ठाure is allocated
 * when needed, and मुक्तd when the cache is zapped.
 *
 * The cache काष्ठाure contains as hash table of entries, and a poपूर्णांकer
 * to a special-हालd entry क्रम the listxattr cache.
 *
 * Accessing and allocating / मुक्तing the caches is करोne via reference
 * counting. The cache entries use a similar refcounting scheme.
 *
 * This makes मुक्तing a cache, both from the shrinker and from the
 * zap cache path, easy. It also means that, in current use हालs,
 * the large majority of inodes will not waste any memory, as they
 * will never have any user extended attributes asचिन्हित to them.
 *
 * Attribute entries are hashed in to a simple hash table. They are
 * also part of an LRU.
 *
 * There are three shrinkers.
 *
 * Two shrinkers deal with the cache entries themselves: one क्रम
 * large entries (> PAGE_SIZE), and one क्रम smaller entries. The
 * shrinker क्रम the larger entries works more aggressively than
 * those क्रम the smaller entries.
 *
 * The other shrinker मुक्तs the cache काष्ठाures themselves.
 */

/*
 * 64 buckets is a good शेष. There is likely no reasonable
 * workload that uses more than even 64 user extended attributes.
 * You can certainly add a lot more - but you get what you ask क्रम
 * in those circumstances.
 */
#घोषणा NFS4_XATTR_HASH_SIZE	64

#घोषणा NFSDBG_FACILITY	NFSDBG_XATTRCACHE

काष्ठा nfs4_xattr_cache;
काष्ठा nfs4_xattr_entry;

काष्ठा nfs4_xattr_bucket अणु
	spinlock_t lock;
	काष्ठा hlist_head hlist;
	काष्ठा nfs4_xattr_cache *cache;
	bool draining;
पूर्ण;

काष्ठा nfs4_xattr_cache अणु
	काष्ठा kref ref;
	काष्ठा nfs4_xattr_bucket buckets[NFS4_XATTR_HASH_SIZE];
	काष्ठा list_head lru;
	काष्ठा list_head dispose;
	atomic_दीर्घ_t nent;
	spinlock_t listxattr_lock;
	काष्ठा inode *inode;
	काष्ठा nfs4_xattr_entry *listxattr;
पूर्ण;

काष्ठा nfs4_xattr_entry अणु
	काष्ठा kref ref;
	काष्ठा hlist_node hnode;
	काष्ठा list_head lru;
	काष्ठा list_head dispose;
	अक्षर *xattr_name;
	व्योम *xattr_value;
	माप_प्रकार xattr_size;
	काष्ठा nfs4_xattr_bucket *bucket;
	uपूर्णांक32_t flags;
पूर्ण;

#घोषणा	NFS4_XATTR_ENTRY_EXTVAL	0x0001

/*
 * LRU list of NFS inodes that have xattr caches.
 */
अटल काष्ठा list_lru nfs4_xattr_cache_lru;
अटल काष्ठा list_lru nfs4_xattr_entry_lru;
अटल काष्ठा list_lru nfs4_xattr_large_entry_lru;

अटल काष्ठा kmem_cache *nfs4_xattr_cache_cachep;

/*
 * Hashing helper functions.
 */
अटल व्योम
nfs4_xattr_hash_init(काष्ठा nfs4_xattr_cache *cache)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NFS4_XATTR_HASH_SIZE; i++) अणु
		INIT_HLIST_HEAD(&cache->buckets[i].hlist);
		spin_lock_init(&cache->buckets[i].lock);
		cache->buckets[i].cache = cache;
		cache->buckets[i].draining = false;
	पूर्ण
पूर्ण

/*
 * Locking order:
 * 1. inode i_lock or bucket lock
 * 2. list_lru lock (taken by list_lru_* functions)
 */

/*
 * Wrapper functions to add a cache entry to the right LRU.
 */
अटल bool
nfs4_xattr_entry_lru_add(काष्ठा nfs4_xattr_entry *entry)
अणु
	काष्ठा list_lru *lru;

	lru = (entry->flags & NFS4_XATTR_ENTRY_EXTVAL) ?
	    &nfs4_xattr_large_entry_lru : &nfs4_xattr_entry_lru;

	वापस list_lru_add(lru, &entry->lru);
पूर्ण

अटल bool
nfs4_xattr_entry_lru_del(काष्ठा nfs4_xattr_entry *entry)
अणु
	काष्ठा list_lru *lru;

	lru = (entry->flags & NFS4_XATTR_ENTRY_EXTVAL) ?
	    &nfs4_xattr_large_entry_lru : &nfs4_xattr_entry_lru;

	वापस list_lru_del(lru, &entry->lru);
पूर्ण

/*
 * This function allocates cache entries. They are the normal
 * extended attribute name/value pairs, but may also be a listxattr
 * cache. Those allocations use the same entry so that they can be
 * treated as one by the memory shrinker.
 *
 * xattr cache entries are allocated together with names. If the
 * value fits in to one page with the entry काष्ठाure and the name,
 * it will also be part of the same allocation (kदो_स्मृति). This is
 * expected to be the vast majority of हालs. Larger allocations
 * have a value poपूर्णांकer that is allocated separately by kvदो_स्मृति.
 *
 * Parameters:
 *
 * @name:  Name of the extended attribute. शून्य क्रम listxattr cache
 *         entry.
 * @value: Value of attribute, or listxattr cache. शून्य अगर the
 *         value is to be copied from pages instead.
 * @pages: Pages to copy the value from, अगर not शून्य. Passed in to
 *	   make it easier to copy the value after an RPC, even अगर
 *	   the value will not be passed up to application (e.g.
 *	   क्रम a 'query' getxattr with शून्य buffer).
 * @len:   Length of the value. Can be 0 क्रम zero-length attributes.
 *         @value and @pages will be शून्य अगर @len is 0.
 */
अटल काष्ठा nfs4_xattr_entry *
nfs4_xattr_alloc_entry(स्थिर अक्षर *name, स्थिर व्योम *value,
		       काष्ठा page **pages, माप_प्रकार len)
अणु
	काष्ठा nfs4_xattr_entry *entry;
	व्योम *valp;
	अक्षर *namep;
	माप_प्रकार alloclen, slen;
	अक्षर *buf;
	uपूर्णांक32_t flags;

	BUILD_BUG_ON(माप(काष्ठा nfs4_xattr_entry) +
	    XATTR_NAME_MAX + 1 > PAGE_SIZE);

	alloclen = माप(काष्ठा nfs4_xattr_entry);
	अगर (name != शून्य) अणु
		slen = म_माप(name) + 1;
		alloclen += slen;
	पूर्ण अन्यथा
		slen = 0;

	अगर (alloclen + len <= PAGE_SIZE) अणु
		alloclen += len;
		flags = 0;
	पूर्ण अन्यथा अणु
		flags = NFS4_XATTR_ENTRY_EXTVAL;
	पूर्ण

	buf = kदो_स्मृति(alloclen, GFP_KERNEL_ACCOUNT | GFP_NOFS);
	अगर (buf == शून्य)
		वापस शून्य;
	entry = (काष्ठा nfs4_xattr_entry *)buf;

	अगर (name != शून्य) अणु
		namep = buf + माप(काष्ठा nfs4_xattr_entry);
		स_नकल(namep, name, slen);
	पूर्ण अन्यथा अणु
		namep = शून्य;
	पूर्ण


	अगर (flags & NFS4_XATTR_ENTRY_EXTVAL) अणु
		valp = kvदो_स्मृति(len, GFP_KERNEL_ACCOUNT | GFP_NOFS);
		अगर (valp == शून्य) अणु
			kमुक्त(buf);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (len != 0) अणु
		valp = buf + माप(काष्ठा nfs4_xattr_entry) + slen;
	पूर्ण अन्यथा
		valp = शून्य;

	अगर (valp != शून्य) अणु
		अगर (value != शून्य)
			स_नकल(valp, value, len);
		अन्यथा
			_copy_from_pages(valp, pages, 0, len);
	पूर्ण

	entry->flags = flags;
	entry->xattr_value = valp;
	kref_init(&entry->ref);
	entry->xattr_name = namep;
	entry->xattr_size = len;
	entry->bucket = शून्य;
	INIT_LIST_HEAD(&entry->lru);
	INIT_LIST_HEAD(&entry->dispose);
	INIT_HLIST_NODE(&entry->hnode);

	वापस entry;
पूर्ण

अटल व्योम
nfs4_xattr_मुक्त_entry(काष्ठा nfs4_xattr_entry *entry)
अणु
	अगर (entry->flags & NFS4_XATTR_ENTRY_EXTVAL)
		kvमुक्त(entry->xattr_value);
	kमुक्त(entry);
पूर्ण

अटल व्योम
nfs4_xattr_मुक्त_entry_cb(काष्ठा kref *kref)
अणु
	काष्ठा nfs4_xattr_entry *entry;

	entry = container_of(kref, काष्ठा nfs4_xattr_entry, ref);

	अगर (WARN_ON(!list_empty(&entry->lru)))
		वापस;

	nfs4_xattr_मुक्त_entry(entry);
पूर्ण

अटल व्योम
nfs4_xattr_मुक्त_cache_cb(काष्ठा kref *kref)
अणु
	काष्ठा nfs4_xattr_cache *cache;
	पूर्णांक i;

	cache = container_of(kref, काष्ठा nfs4_xattr_cache, ref);

	क्रम (i = 0; i < NFS4_XATTR_HASH_SIZE; i++) अणु
		अगर (WARN_ON(!hlist_empty(&cache->buckets[i].hlist)))
			वापस;
		cache->buckets[i].draining = false;
	पूर्ण

	cache->listxattr = शून्य;

	kmem_cache_मुक्त(nfs4_xattr_cache_cachep, cache);

पूर्ण

अटल काष्ठा nfs4_xattr_cache *
nfs4_xattr_alloc_cache(व्योम)
अणु
	काष्ठा nfs4_xattr_cache *cache;

	cache = kmem_cache_alloc(nfs4_xattr_cache_cachep,
	    GFP_KERNEL_ACCOUNT | GFP_NOFS);
	अगर (cache == शून्य)
		वापस शून्य;

	kref_init(&cache->ref);
	atomic_दीर्घ_set(&cache->nent, 0);

	वापस cache;
पूर्ण

/*
 * Set the listxattr cache, which is a special-हालd cache entry.
 * The special value ERR_PTR(-ESTALE) is used to indicate that
 * the cache is being drained - this prevents a new listxattr
 * cache from being added to what is now a stale cache.
 */
अटल पूर्णांक
nfs4_xattr_set_listcache(काष्ठा nfs4_xattr_cache *cache,
			 काष्ठा nfs4_xattr_entry *new)
अणु
	काष्ठा nfs4_xattr_entry *old;
	पूर्णांक ret = 1;

	spin_lock(&cache->listxattr_lock);

	old = cache->listxattr;

	अगर (old == ERR_PTR(-ESTALE)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	cache->listxattr = new;
	अगर (new != शून्य && new != ERR_PTR(-ESTALE))
		nfs4_xattr_entry_lru_add(new);

	अगर (old != शून्य) अणु
		nfs4_xattr_entry_lru_del(old);
		kref_put(&old->ref, nfs4_xattr_मुक्त_entry_cb);
	पूर्ण
out:
	spin_unlock(&cache->listxattr_lock);

	वापस ret;
पूर्ण

/*
 * Unlink a cache from its parent inode, clearing out an invalid
 * cache. Must be called with i_lock held.
 */
अटल काष्ठा nfs4_xattr_cache *
nfs4_xattr_cache_unlink(काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi;
	काष्ठा nfs4_xattr_cache *oldcache;

	nfsi = NFS_I(inode);

	oldcache = nfsi->xattr_cache;
	अगर (oldcache != शून्य) अणु
		list_lru_del(&nfs4_xattr_cache_lru, &oldcache->lru);
		oldcache->inode = शून्य;
	पूर्ण
	nfsi->xattr_cache = शून्य;
	nfsi->cache_validity &= ~NFS_INO_INVALID_XATTR;

	वापस oldcache;

पूर्ण

/*
 * Discard a cache. Called by get_cache() अगर there was an old,
 * invalid cache. Can also be called from a shrinker callback.
 *
 * The cache is dead, it has alपढ़ोy been unlinked from its inode,
 * and no दीर्घer appears on the cache LRU list.
 *
 * Mark all buckets as draining, so that no new entries are added. This
 * could still happen in the unlikely, but possible हाल that another
 * thपढ़ो had grabbed a reference beक्रमe it was unlinked from the inode,
 * and is still holding it क्रम an add operation.
 *
 * Remove all entries from the LRU lists, so that there is no दीर्घer
 * any way to 'find' this cache. Then, हटाओ the entries from the hash
 * table.
 *
 * At that poपूर्णांक, the cache will reमुख्य empty and can be मुक्तd when the final
 * reference drops, which is very likely the kref_put at the end of
 * this function, or the one called immediately afterwards in the
 * shrinker callback.
 */
अटल व्योम
nfs4_xattr_discard_cache(काष्ठा nfs4_xattr_cache *cache)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा nfs4_xattr_entry *entry;
	काष्ठा nfs4_xattr_bucket *bucket;
	काष्ठा hlist_node *n;

	nfs4_xattr_set_listcache(cache, ERR_PTR(-ESTALE));

	क्रम (i = 0; i < NFS4_XATTR_HASH_SIZE; i++) अणु
		bucket = &cache->buckets[i];

		spin_lock(&bucket->lock);
		bucket->draining = true;
		hlist_क्रम_each_entry_safe(entry, n, &bucket->hlist, hnode) अणु
			nfs4_xattr_entry_lru_del(entry);
			hlist_del_init(&entry->hnode);
			kref_put(&entry->ref, nfs4_xattr_मुक्त_entry_cb);
		पूर्ण
		spin_unlock(&bucket->lock);
	पूर्ण

	atomic_दीर्घ_set(&cache->nent, 0);

	kref_put(&cache->ref, nfs4_xattr_मुक्त_cache_cb);
पूर्ण

/*
 * Get a referenced copy of the cache काष्ठाure. Aव्योम करोing allocs
 * जबतक holding i_lock. Which means that we करो some optimistic allocation,
 * and might have to मुक्त the result in rare हालs.
 *
 * This function only checks the NFS_INO_INVALID_XATTR cache validity bit
 * and acts accordingly, replacing the cache when needed. For the पढ़ो हाल
 * (!add), this means that the caller must make sure that the cache
 * is valid beक्रमe caling this function. getxattr and listxattr call
 * revalidate_inode to करो this. The attribute cache समयout (क्रम the
 * non-delegated हाल) is expected to be dealt with in the revalidate
 * call.
 */

अटल काष्ठा nfs4_xattr_cache *
nfs4_xattr_get_cache(काष्ठा inode *inode, पूर्णांक add)
अणु
	काष्ठा nfs_inode *nfsi;
	काष्ठा nfs4_xattr_cache *cache, *oldcache, *newcache;

	nfsi = NFS_I(inode);

	cache = oldcache = शून्य;

	spin_lock(&inode->i_lock);

	अगर (nfsi->cache_validity & NFS_INO_INVALID_XATTR)
		oldcache = nfs4_xattr_cache_unlink(inode);
	अन्यथा
		cache = nfsi->xattr_cache;

	अगर (cache != शून्य)
		kref_get(&cache->ref);

	spin_unlock(&inode->i_lock);

	अगर (add && cache == शून्य) अणु
		newcache = शून्य;

		cache = nfs4_xattr_alloc_cache();
		अगर (cache == शून्य)
			जाओ out;

		spin_lock(&inode->i_lock);
		अगर (nfsi->cache_validity & NFS_INO_INVALID_XATTR) अणु
			/*
			 * The cache was invalidated again. Give up,
			 * since what we want to enter is now likely
			 * outdated anyway.
			 */
			spin_unlock(&inode->i_lock);
			kref_put(&cache->ref, nfs4_xattr_मुक्त_cache_cb);
			cache = शून्य;
			जाओ out;
		पूर्ण

		/*
		 * Check अगर someone beat us to it.
		 */
		अगर (nfsi->xattr_cache != शून्य) अणु
			newcache = nfsi->xattr_cache;
			kref_get(&newcache->ref);
		पूर्ण अन्यथा अणु
			kref_get(&cache->ref);
			nfsi->xattr_cache = cache;
			cache->inode = inode;
			list_lru_add(&nfs4_xattr_cache_lru, &cache->lru);
		पूर्ण

		spin_unlock(&inode->i_lock);

		/*
		 * If there was a race, throw away the cache we just
		 * allocated, and use the new one allocated by someone
		 * अन्यथा.
		 */
		अगर (newcache != शून्य) अणु
			kref_put(&cache->ref, nfs4_xattr_मुक्त_cache_cb);
			cache = newcache;
		पूर्ण
	पूर्ण

out:
	/*
	 * Discard the now orphaned old cache.
	 */
	अगर (oldcache != शून्य)
		nfs4_xattr_discard_cache(oldcache);

	वापस cache;
पूर्ण

अटल अंतरभूत काष्ठा nfs4_xattr_bucket *
nfs4_xattr_hash_bucket(काष्ठा nfs4_xattr_cache *cache, स्थिर अक्षर *name)
अणु
	वापस &cache->buckets[jhash(name, म_माप(name), 0) &
	    (ARRAY_SIZE(cache->buckets) - 1)];
पूर्ण

अटल काष्ठा nfs4_xattr_entry *
nfs4_xattr_get_entry(काष्ठा nfs4_xattr_bucket *bucket, स्थिर अक्षर *name)
अणु
	काष्ठा nfs4_xattr_entry *entry;

	entry = शून्य;

	hlist_क्रम_each_entry(entry, &bucket->hlist, hnode) अणु
		अगर (!म_भेद(entry->xattr_name, name))
			अवरोध;
	पूर्ण

	वापस entry;
पूर्ण

अटल पूर्णांक
nfs4_xattr_hash_add(काष्ठा nfs4_xattr_cache *cache,
		    काष्ठा nfs4_xattr_entry *entry)
अणु
	काष्ठा nfs4_xattr_bucket *bucket;
	काष्ठा nfs4_xattr_entry *oldentry = शून्य;
	पूर्णांक ret = 1;

	bucket = nfs4_xattr_hash_bucket(cache, entry->xattr_name);
	entry->bucket = bucket;

	spin_lock(&bucket->lock);

	अगर (bucket->draining) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	oldentry = nfs4_xattr_get_entry(bucket, entry->xattr_name);
	अगर (oldentry != शून्य) अणु
		hlist_del_init(&oldentry->hnode);
		nfs4_xattr_entry_lru_del(oldentry);
	पूर्ण अन्यथा अणु
		atomic_दीर्घ_inc(&cache->nent);
	पूर्ण

	hlist_add_head(&entry->hnode, &bucket->hlist);
	nfs4_xattr_entry_lru_add(entry);

out:
	spin_unlock(&bucket->lock);

	अगर (oldentry != शून्य)
		kref_put(&oldentry->ref, nfs4_xattr_मुक्त_entry_cb);

	वापस ret;
पूर्ण

अटल व्योम
nfs4_xattr_hash_हटाओ(काष्ठा nfs4_xattr_cache *cache, स्थिर अक्षर *name)
अणु
	काष्ठा nfs4_xattr_bucket *bucket;
	काष्ठा nfs4_xattr_entry *entry;

	bucket = nfs4_xattr_hash_bucket(cache, name);

	spin_lock(&bucket->lock);

	entry = nfs4_xattr_get_entry(bucket, name);
	अगर (entry != शून्य) अणु
		hlist_del_init(&entry->hnode);
		nfs4_xattr_entry_lru_del(entry);
		atomic_दीर्घ_dec(&cache->nent);
	पूर्ण

	spin_unlock(&bucket->lock);

	अगर (entry != शून्य)
		kref_put(&entry->ref, nfs4_xattr_मुक्त_entry_cb);
पूर्ण

अटल काष्ठा nfs4_xattr_entry *
nfs4_xattr_hash_find(काष्ठा nfs4_xattr_cache *cache, स्थिर अक्षर *name)
अणु
	काष्ठा nfs4_xattr_bucket *bucket;
	काष्ठा nfs4_xattr_entry *entry;

	bucket = nfs4_xattr_hash_bucket(cache, name);

	spin_lock(&bucket->lock);

	entry = nfs4_xattr_get_entry(bucket, name);
	अगर (entry != शून्य)
		kref_get(&entry->ref);

	spin_unlock(&bucket->lock);

	वापस entry;
पूर्ण

/*
 * Entry poपूर्णांक to retrieve an entry from the cache.
 */
sमाप_प्रकार nfs4_xattr_cache_get(काष्ठा inode *inode, स्थिर अक्षर *name, अक्षर *buf,
			 sमाप_प्रकार buflen)
अणु
	काष्ठा nfs4_xattr_cache *cache;
	काष्ठा nfs4_xattr_entry *entry;
	sमाप_प्रकार ret;

	cache = nfs4_xattr_get_cache(inode, 0);
	अगर (cache == शून्य)
		वापस -ENOENT;

	ret = 0;
	entry = nfs4_xattr_hash_find(cache, name);

	अगर (entry != शून्य) अणु
		dprपूर्णांकk("%s: cache hit '%s', len %lu\n", __func__,
		    entry->xattr_name, (अचिन्हित दीर्घ)entry->xattr_size);
		अगर (buflen == 0) अणु
			/* Length probe only */
			ret = entry->xattr_size;
		पूर्ण अन्यथा अगर (buflen < entry->xattr_size)
			ret = -दुस्फल;
		अन्यथा अणु
			स_नकल(buf, entry->xattr_value, entry->xattr_size);
			ret = entry->xattr_size;
		पूर्ण
		kref_put(&entry->ref, nfs4_xattr_मुक्त_entry_cb);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("%s: cache miss '%s'\n", __func__, name);
		ret = -ENOENT;
	पूर्ण

	kref_put(&cache->ref, nfs4_xattr_मुक्त_cache_cb);

	वापस ret;
पूर्ण

/*
 * Retrieve a cached list of xattrs from the cache.
 */
sमाप_प्रकार nfs4_xattr_cache_list(काष्ठा inode *inode, अक्षर *buf, sमाप_प्रकार buflen)
अणु
	काष्ठा nfs4_xattr_cache *cache;
	काष्ठा nfs4_xattr_entry *entry;
	sमाप_प्रकार ret;

	cache = nfs4_xattr_get_cache(inode, 0);
	अगर (cache == शून्य)
		वापस -ENOENT;

	spin_lock(&cache->listxattr_lock);

	entry = cache->listxattr;

	अगर (entry != शून्य && entry != ERR_PTR(-ESTALE)) अणु
		अगर (buflen == 0) अणु
			/* Length probe only */
			ret = entry->xattr_size;
		पूर्ण अन्यथा अगर (entry->xattr_size > buflen)
			ret = -दुस्फल;
		अन्यथा अणु
			स_नकल(buf, entry->xattr_value, entry->xattr_size);
			ret = entry->xattr_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -ENOENT;
	पूर्ण

	spin_unlock(&cache->listxattr_lock);

	kref_put(&cache->ref, nfs4_xattr_मुक्त_cache_cb);

	वापस ret;
पूर्ण

/*
 * Add an xattr to the cache.
 *
 * This also invalidates the xattr list cache.
 */
व्योम nfs4_xattr_cache_add(काष्ठा inode *inode, स्थिर अक्षर *name,
			  स्थिर अक्षर *buf, काष्ठा page **pages, sमाप_प्रकार buflen)
अणु
	काष्ठा nfs4_xattr_cache *cache;
	काष्ठा nfs4_xattr_entry *entry;

	dprपूर्णांकk("%s: add '%s' len %lu\n", __func__,
	    name, (अचिन्हित दीर्घ)buflen);

	cache = nfs4_xattr_get_cache(inode, 1);
	अगर (cache == शून्य)
		वापस;

	entry = nfs4_xattr_alloc_entry(name, buf, pages, buflen);
	अगर (entry == शून्य)
		जाओ out;

	(व्योम)nfs4_xattr_set_listcache(cache, शून्य);

	अगर (!nfs4_xattr_hash_add(cache, entry))
		kref_put(&entry->ref, nfs4_xattr_मुक्त_entry_cb);

out:
	kref_put(&cache->ref, nfs4_xattr_मुक्त_cache_cb);
पूर्ण


/*
 * Remove an xattr from the cache.
 *
 * This also invalidates the xattr list cache.
 */
व्योम nfs4_xattr_cache_हटाओ(काष्ठा inode *inode, स्थिर अक्षर *name)
अणु
	काष्ठा nfs4_xattr_cache *cache;

	dprपूर्णांकk("%s: remove '%s'\n", __func__, name);

	cache = nfs4_xattr_get_cache(inode, 0);
	अगर (cache == शून्य)
		वापस;

	(व्योम)nfs4_xattr_set_listcache(cache, शून्य);
	nfs4_xattr_hash_हटाओ(cache, name);

	kref_put(&cache->ref, nfs4_xattr_मुक्त_cache_cb);
पूर्ण

/*
 * Cache listxattr output, replacing any possible old one.
 */
व्योम nfs4_xattr_cache_set_list(काष्ठा inode *inode, स्थिर अक्षर *buf,
			       sमाप_प्रकार buflen)
अणु
	काष्ठा nfs4_xattr_cache *cache;
	काष्ठा nfs4_xattr_entry *entry;

	cache = nfs4_xattr_get_cache(inode, 1);
	अगर (cache == शून्य)
		वापस;

	entry = nfs4_xattr_alloc_entry(शून्य, buf, शून्य, buflen);
	अगर (entry == शून्य)
		जाओ out;

	/*
	 * This is just there to be able to get to bucket->cache,
	 * which is obviously the same क्रम all buckets, so just
	 * use bucket 0.
	 */
	entry->bucket = &cache->buckets[0];

	अगर (!nfs4_xattr_set_listcache(cache, entry))
		kref_put(&entry->ref, nfs4_xattr_मुक्त_entry_cb);

out:
	kref_put(&cache->ref, nfs4_xattr_मुक्त_cache_cb);
पूर्ण

/*
 * Zap the entire cache. Called when an inode is evicted.
 */
व्योम nfs4_xattr_cache_zap(काष्ठा inode *inode)
अणु
	काष्ठा nfs4_xattr_cache *oldcache;

	spin_lock(&inode->i_lock);
	oldcache = nfs4_xattr_cache_unlink(inode);
	spin_unlock(&inode->i_lock);

	अगर (oldcache)
		nfs4_xattr_discard_cache(oldcache);
पूर्ण

/*
 * The entry LRU is shrunk more aggressively than the cache LRU,
 * by settings @seeks to 1.
 *
 * Cache काष्ठाures are मुक्तd only when they've become empty, after
 * pruning all but one entry.
 */

अटल अचिन्हित दीर्घ nfs4_xattr_cache_count(काष्ठा shrinker *shrink,
					    काष्ठा shrink_control *sc);
अटल अचिन्हित दीर्घ nfs4_xattr_entry_count(काष्ठा shrinker *shrink,
					    काष्ठा shrink_control *sc);
अटल अचिन्हित दीर्घ nfs4_xattr_cache_scan(काष्ठा shrinker *shrink,
					   काष्ठा shrink_control *sc);
अटल अचिन्हित दीर्घ nfs4_xattr_entry_scan(काष्ठा shrinker *shrink,
					   काष्ठा shrink_control *sc);

अटल काष्ठा shrinker nfs4_xattr_cache_shrinker = अणु
	.count_objects	= nfs4_xattr_cache_count,
	.scan_objects	= nfs4_xattr_cache_scan,
	.seeks		= DEFAULT_SEEKS,
	.flags		= SHRINKER_MEMCG_AWARE,
पूर्ण;

अटल काष्ठा shrinker nfs4_xattr_entry_shrinker = अणु
	.count_objects	= nfs4_xattr_entry_count,
	.scan_objects	= nfs4_xattr_entry_scan,
	.seeks		= DEFAULT_SEEKS,
	.batch		= 512,
	.flags		= SHRINKER_MEMCG_AWARE,
पूर्ण;

अटल काष्ठा shrinker nfs4_xattr_large_entry_shrinker = अणु
	.count_objects	= nfs4_xattr_entry_count,
	.scan_objects	= nfs4_xattr_entry_scan,
	.seeks		= 1,
	.batch		= 512,
	.flags		= SHRINKER_MEMCG_AWARE,
पूर्ण;

अटल क्रमागत lru_status
cache_lru_isolate(काष्ठा list_head *item,
	काष्ठा list_lru_one *lru, spinlock_t *lru_lock, व्योम *arg)
अणु
	काष्ठा list_head *dispose = arg;
	काष्ठा inode *inode;
	काष्ठा nfs4_xattr_cache *cache = container_of(item,
	    काष्ठा nfs4_xattr_cache, lru);

	अगर (atomic_दीर्घ_पढ़ो(&cache->nent) > 1)
		वापस LRU_SKIP;

	/*
	 * If a cache काष्ठाure is on the LRU list, we know that
	 * its inode is valid. Try to lock it to अवरोध the link.
	 * Since we're inverting the lock order here, only try.
	 */
	inode = cache->inode;

	अगर (!spin_trylock(&inode->i_lock))
		वापस LRU_SKIP;

	kref_get(&cache->ref);

	cache->inode = शून्य;
	NFS_I(inode)->xattr_cache = शून्य;
	NFS_I(inode)->cache_validity &= ~NFS_INO_INVALID_XATTR;
	list_lru_isolate(lru, &cache->lru);

	spin_unlock(&inode->i_lock);

	list_add_tail(&cache->dispose, dispose);
	वापस LRU_REMOVED;
पूर्ण

अटल अचिन्हित दीर्घ
nfs4_xattr_cache_scan(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	LIST_HEAD(dispose);
	अचिन्हित दीर्घ मुक्तd;
	काष्ठा nfs4_xattr_cache *cache;

	मुक्तd = list_lru_shrink_walk(&nfs4_xattr_cache_lru, sc,
	    cache_lru_isolate, &dispose);
	जबतक (!list_empty(&dispose)) अणु
		cache = list_first_entry(&dispose, काष्ठा nfs4_xattr_cache,
		    dispose);
		list_del_init(&cache->dispose);
		nfs4_xattr_discard_cache(cache);
		kref_put(&cache->ref, nfs4_xattr_मुक्त_cache_cb);
	पूर्ण

	वापस मुक्तd;
पूर्ण


अटल अचिन्हित दीर्घ
nfs4_xattr_cache_count(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ count;

	count = list_lru_shrink_count(&nfs4_xattr_cache_lru, sc);
	वापस vfs_pressure_ratio(count);
पूर्ण

अटल क्रमागत lru_status
entry_lru_isolate(काष्ठा list_head *item,
	काष्ठा list_lru_one *lru, spinlock_t *lru_lock, व्योम *arg)
अणु
	काष्ठा list_head *dispose = arg;
	काष्ठा nfs4_xattr_bucket *bucket;
	काष्ठा nfs4_xattr_cache *cache;
	काष्ठा nfs4_xattr_entry *entry = container_of(item,
	    काष्ठा nfs4_xattr_entry, lru);

	bucket = entry->bucket;
	cache = bucket->cache;

	/*
	 * Unhook the entry from its parent (either a cache bucket
	 * or a cache काष्ठाure अगर it's a listxattr buf), so that
	 * it's no दीर्घer found. Then add it to the isolate list,
	 * to be मुक्तd later.
	 *
	 * In both हालs, we're reverting lock order, so use
	 * trylock and skip the entry अगर we can't get the lock.
	 */
	अगर (entry->xattr_name != शून्य) अणु
		/* Regular cache entry */
		अगर (!spin_trylock(&bucket->lock))
			वापस LRU_SKIP;

		kref_get(&entry->ref);

		hlist_del_init(&entry->hnode);
		atomic_दीर्घ_dec(&cache->nent);
		list_lru_isolate(lru, &entry->lru);

		spin_unlock(&bucket->lock);
	पूर्ण अन्यथा अणु
		/* Listxattr cache entry */
		अगर (!spin_trylock(&cache->listxattr_lock))
			वापस LRU_SKIP;

		kref_get(&entry->ref);

		cache->listxattr = शून्य;
		list_lru_isolate(lru, &entry->lru);

		spin_unlock(&cache->listxattr_lock);
	पूर्ण

	list_add_tail(&entry->dispose, dispose);
	वापस LRU_REMOVED;
पूर्ण

अटल अचिन्हित दीर्घ
nfs4_xattr_entry_scan(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	LIST_HEAD(dispose);
	अचिन्हित दीर्घ मुक्तd;
	काष्ठा nfs4_xattr_entry *entry;
	काष्ठा list_lru *lru;

	lru = (shrink == &nfs4_xattr_large_entry_shrinker) ?
	    &nfs4_xattr_large_entry_lru : &nfs4_xattr_entry_lru;

	मुक्तd = list_lru_shrink_walk(lru, sc, entry_lru_isolate, &dispose);

	जबतक (!list_empty(&dispose)) अणु
		entry = list_first_entry(&dispose, काष्ठा nfs4_xattr_entry,
		    dispose);
		list_del_init(&entry->dispose);

		/*
		 * Drop two references: the one that we just grabbed
		 * in entry_lru_isolate, and the one that was set
		 * when the entry was first allocated.
		 */
		kref_put(&entry->ref, nfs4_xattr_मुक्त_entry_cb);
		kref_put(&entry->ref, nfs4_xattr_मुक्त_entry_cb);
	पूर्ण

	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ
nfs4_xattr_entry_count(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ count;
	काष्ठा list_lru *lru;

	lru = (shrink == &nfs4_xattr_large_entry_shrinker) ?
	    &nfs4_xattr_large_entry_lru : &nfs4_xattr_entry_lru;

	count = list_lru_shrink_count(lru, sc);
	वापस vfs_pressure_ratio(count);
पूर्ण


अटल व्योम nfs4_xattr_cache_init_once(व्योम *p)
अणु
	काष्ठा nfs4_xattr_cache *cache = (काष्ठा nfs4_xattr_cache *)p;

	spin_lock_init(&cache->listxattr_lock);
	atomic_दीर्घ_set(&cache->nent, 0);
	nfs4_xattr_hash_init(cache);
	cache->listxattr = शून्य;
	INIT_LIST_HEAD(&cache->lru);
	INIT_LIST_HEAD(&cache->dispose);
पूर्ण

पूर्णांक __init nfs4_xattr_cache_init(व्योम)
अणु
	पूर्णांक ret = 0;

	nfs4_xattr_cache_cachep = kmem_cache_create("nfs4_xattr_cache_cache",
	    माप(काष्ठा nfs4_xattr_cache), 0,
	    (SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|SLAB_ACCOUNT),
	    nfs4_xattr_cache_init_once);
	अगर (nfs4_xattr_cache_cachep == शून्य)
		वापस -ENOMEM;

	ret = list_lru_init_memcg(&nfs4_xattr_large_entry_lru,
	    &nfs4_xattr_large_entry_shrinker);
	अगर (ret)
		जाओ out4;

	ret = list_lru_init_memcg(&nfs4_xattr_entry_lru,
	    &nfs4_xattr_entry_shrinker);
	अगर (ret)
		जाओ out3;

	ret = list_lru_init_memcg(&nfs4_xattr_cache_lru,
	    &nfs4_xattr_cache_shrinker);
	अगर (ret)
		जाओ out2;

	ret = रेजिस्टर_shrinker(&nfs4_xattr_cache_shrinker);
	अगर (ret)
		जाओ out1;

	ret = रेजिस्टर_shrinker(&nfs4_xattr_entry_shrinker);
	अगर (ret)
		जाओ out;

	ret = रेजिस्टर_shrinker(&nfs4_xattr_large_entry_shrinker);
	अगर (!ret)
		वापस 0;

	unरेजिस्टर_shrinker(&nfs4_xattr_entry_shrinker);
out:
	unरेजिस्टर_shrinker(&nfs4_xattr_cache_shrinker);
out1:
	list_lru_destroy(&nfs4_xattr_cache_lru);
out2:
	list_lru_destroy(&nfs4_xattr_entry_lru);
out3:
	list_lru_destroy(&nfs4_xattr_large_entry_lru);
out4:
	kmem_cache_destroy(nfs4_xattr_cache_cachep);

	वापस ret;
पूर्ण

व्योम nfs4_xattr_cache_निकास(व्योम)
अणु
	unरेजिस्टर_shrinker(&nfs4_xattr_large_entry_shrinker);
	unरेजिस्टर_shrinker(&nfs4_xattr_entry_shrinker);
	unरेजिस्टर_shrinker(&nfs4_xattr_cache_shrinker);
	list_lru_destroy(&nfs4_xattr_large_entry_lru);
	list_lru_destroy(&nfs4_xattr_entry_lru);
	list_lru_destroy(&nfs4_xattr_cache_lru);
	kmem_cache_destroy(nfs4_xattr_cache_cachep);
पूर्ण
