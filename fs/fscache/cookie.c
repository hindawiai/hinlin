<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* netfs cookie management
 *
 * Copyright (C) 2004-2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम more inक्रमmation on
 * the netfs API.
 */

#घोषणा FSCACHE_DEBUG_LEVEL COOKIE
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

काष्ठा kmem_cache *fscache_cookie_jar;

अटल atomic_t fscache_object_debug_id = ATOMIC_INIT(0);

#घोषणा fscache_cookie_hash_shअगरt 15
अटल काष्ठा hlist_bl_head fscache_cookie_hash[1 << fscache_cookie_hash_shअगरt];

अटल पूर्णांक fscache_acquire_non_index_cookie(काष्ठा fscache_cookie *cookie,
					    loff_t object_size);
अटल पूर्णांक fscache_alloc_object(काष्ठा fscache_cache *cache,
				काष्ठा fscache_cookie *cookie);
अटल पूर्णांक fscache_attach_object(काष्ठा fscache_cookie *cookie,
				 काष्ठा fscache_object *object);

अटल व्योम fscache_prपूर्णांक_cookie(काष्ठा fscache_cookie *cookie, अक्षर prefix)
अणु
	काष्ठा hlist_node *object;
	स्थिर u8 *k;
	अचिन्हित loop;

	pr_err("%c-cookie c=%p [p=%p fl=%lx nc=%u na=%u]\n",
	       prefix, cookie, cookie->parent, cookie->flags,
	       atomic_पढ़ो(&cookie->n_children),
	       atomic_पढ़ो(&cookie->n_active));
	pr_err("%c-cookie d=%p n=%p\n",
	       prefix, cookie->def, cookie->netfs_data);

	object = READ_ONCE(cookie->backing_objects.first);
	अगर (object)
		pr_err("%c-cookie o=%p\n",
		       prefix, hlist_entry(object, काष्ठा fscache_object, cookie_link));

	pr_err("%c-key=[%u] '", prefix, cookie->key_len);
	k = (cookie->key_len <= माप(cookie->अंतरभूत_key)) ?
		cookie->अंतरभूत_key : cookie->key;
	क्रम (loop = 0; loop < cookie->key_len; loop++)
		pr_cont("%02x", k[loop]);
	pr_cont("'\n");
पूर्ण

व्योम fscache_मुक्त_cookie(काष्ठा fscache_cookie *cookie)
अणु
	अगर (cookie) अणु
		BUG_ON(!hlist_empty(&cookie->backing_objects));
		अगर (cookie->aux_len > माप(cookie->अंतरभूत_aux))
			kमुक्त(cookie->aux);
		अगर (cookie->key_len > माप(cookie->अंतरभूत_key))
			kमुक्त(cookie->key);
		kmem_cache_मुक्त(fscache_cookie_jar, cookie);
	पूर्ण
पूर्ण

/*
 * Set the index key in a cookie.  The cookie काष्ठा has space क्रम a 16-byte
 * key plus length and hash, but अगर that's not big enough, it's instead a
 * poपूर्णांकer to a buffer containing 3 bytes of hash, 1 byte of length and then
 * the key data.
 */
अटल पूर्णांक fscache_set_key(काष्ठा fscache_cookie *cookie,
			   स्थिर व्योम *index_key, माप_प्रकार index_key_len)
अणु
	अचिन्हित दीर्घ दीर्घ h;
	u32 *buf;
	पूर्णांक bufs;
	पूर्णांक i;

	bufs = DIV_ROUND_UP(index_key_len, माप(*buf));

	अगर (index_key_len > माप(cookie->अंतरभूत_key)) अणु
		buf = kसुस्मृति(bufs, माप(*buf), GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
		cookie->key = buf;
	पूर्ण अन्यथा अणु
		buf = (u32 *)cookie->अंतरभूत_key;
	पूर्ण

	स_नकल(buf, index_key, index_key_len);

	/* Calculate a hash and combine this with the length in the first word
	 * or first half word
	 */
	h = (अचिन्हित दीर्घ)cookie->parent;
	h += index_key_len + cookie->type;

	क्रम (i = 0; i < bufs; i++)
		h += buf[i];

	cookie->key_hash = h ^ (h >> 32);
	वापस 0;
पूर्ण

अटल दीर्घ fscache_compare_cookie(स्थिर काष्ठा fscache_cookie *a,
				   स्थिर काष्ठा fscache_cookie *b)
अणु
	स्थिर व्योम *ka, *kb;

	अगर (a->key_hash != b->key_hash)
		वापस (दीर्घ)a->key_hash - (दीर्घ)b->key_hash;
	अगर (a->parent != b->parent)
		वापस (दीर्घ)a->parent - (दीर्घ)b->parent;
	अगर (a->key_len != b->key_len)
		वापस (दीर्घ)a->key_len - (दीर्घ)b->key_len;
	अगर (a->type != b->type)
		वापस (दीर्घ)a->type - (दीर्घ)b->type;

	अगर (a->key_len <= माप(a->अंतरभूत_key)) अणु
		ka = &a->अंतरभूत_key;
		kb = &b->अंतरभूत_key;
	पूर्ण अन्यथा अणु
		ka = a->key;
		kb = b->key;
	पूर्ण
	वापस स_भेद(ka, kb, a->key_len);
पूर्ण

/*
 * Allocate a cookie.
 */
काष्ठा fscache_cookie *fscache_alloc_cookie(
	काष्ठा fscache_cookie *parent,
	स्थिर काष्ठा fscache_cookie_def *def,
	स्थिर व्योम *index_key, माप_प्रकार index_key_len,
	स्थिर व्योम *aux_data, माप_प्रकार aux_data_len,
	व्योम *netfs_data,
	loff_t object_size)
अणु
	काष्ठा fscache_cookie *cookie;

	/* allocate and initialise a cookie */
	cookie = kmem_cache_zalloc(fscache_cookie_jar, GFP_KERNEL);
	अगर (!cookie)
		वापस शून्य;

	cookie->key_len = index_key_len;
	cookie->aux_len = aux_data_len;

	अगर (fscache_set_key(cookie, index_key, index_key_len) < 0)
		जाओ nomem;

	अगर (cookie->aux_len <= माप(cookie->अंतरभूत_aux)) अणु
		स_नकल(cookie->अंतरभूत_aux, aux_data, cookie->aux_len);
	पूर्ण अन्यथा अणु
		cookie->aux = kmemdup(aux_data, cookie->aux_len, GFP_KERNEL);
		अगर (!cookie->aux)
			जाओ nomem;
	पूर्ण

	atomic_set(&cookie->usage, 1);
	atomic_set(&cookie->n_children, 0);

	/* We keep the active count elevated until relinquishment to prevent an
	 * attempt to wake up every समय the object operations queue quiesces.
	 */
	atomic_set(&cookie->n_active, 1);

	cookie->def		= def;
	cookie->parent		= parent;
	cookie->netfs_data	= netfs_data;
	cookie->flags		= (1 << FSCACHE_COOKIE_NO_DATA_YET);
	cookie->type		= def->type;
	spin_lock_init(&cookie->lock);
	spin_lock_init(&cookie->stores_lock);
	INIT_HLIST_HEAD(&cookie->backing_objects);

	/* radix tree insertion won't use the preallocation pool unless it's
	 * told it may not रुको */
	INIT_RADIX_TREE(&cookie->stores, GFP_NOFS & ~__GFP_सूचीECT_RECLAIM);
	वापस cookie;

nomem:
	fscache_मुक्त_cookie(cookie);
	वापस शून्य;
पूर्ण

/*
 * Attempt to insert the new cookie पूर्णांकo the hash.  If there's a collision, we
 * वापस the old cookie अगर it's not in use and an error otherwise.
 */
काष्ठा fscache_cookie *fscache_hash_cookie(काष्ठा fscache_cookie *candidate)
अणु
	काष्ठा fscache_cookie *cursor;
	काष्ठा hlist_bl_head *h;
	काष्ठा hlist_bl_node *p;
	अचिन्हित पूर्णांक bucket;

	bucket = candidate->key_hash & (ARRAY_SIZE(fscache_cookie_hash) - 1);
	h = &fscache_cookie_hash[bucket];

	hlist_bl_lock(h);
	hlist_bl_क्रम_each_entry(cursor, p, h, hash_link) अणु
		अगर (fscache_compare_cookie(candidate, cursor) == 0)
			जाओ collision;
	पूर्ण

	__set_bit(FSCACHE_COOKIE_ACQUIRED, &candidate->flags);
	fscache_cookie_get(candidate->parent, fscache_cookie_get_acquire_parent);
	atomic_inc(&candidate->parent->n_children);
	hlist_bl_add_head(&candidate->hash_link, h);
	hlist_bl_unlock(h);
	वापस candidate;

collision:
	अगर (test_and_set_bit(FSCACHE_COOKIE_ACQUIRED, &cursor->flags)) अणु
		trace_fscache_cookie(cursor, fscache_cookie_collision,
				     atomic_पढ़ो(&cursor->usage));
		pr_err("Duplicate cookie detected\n");
		fscache_prपूर्णांक_cookie(cursor, 'O');
		fscache_prपूर्णांक_cookie(candidate, 'N');
		hlist_bl_unlock(h);
		वापस शून्य;
	पूर्ण

	fscache_cookie_get(cursor, fscache_cookie_get_reacquire);
	hlist_bl_unlock(h);
	वापस cursor;
पूर्ण

/*
 * request a cookie to represent an object (index, datafile, xattr, etc)
 * - parent specअगरies the parent object
 *   - the top level index cookie क्रम each netfs is stored in the fscache_netfs
 *     काष्ठा upon registration
 * - def poपूर्णांकs to the definition
 * - the netfs_data will be passed to the functions poपूर्णांकed to in *def
 * - all attached caches will be searched to see अगर they contain this object
 * - index objects aren't stored on disk until there's a dependent file that
 *   needs storing
 * - other objects are stored in a selected cache immediately, and all the
 *   indices क्रमming the path to it are instantiated अगर necessary
 * - we never let on to the netfs about errors
 *   - we may set a negative cookie poपूर्णांकer, but that's okay
 */
काष्ठा fscache_cookie *__fscache_acquire_cookie(
	काष्ठा fscache_cookie *parent,
	स्थिर काष्ठा fscache_cookie_def *def,
	स्थिर व्योम *index_key, माप_प्रकार index_key_len,
	स्थिर व्योम *aux_data, माप_प्रकार aux_data_len,
	व्योम *netfs_data,
	loff_t object_size,
	bool enable)
अणु
	काष्ठा fscache_cookie *candidate, *cookie;

	BUG_ON(!def);

	_enter("{%s},{%s},%p,%u",
	       parent ? (अक्षर *) parent->def->name : "<no-parent>",
	       def->name, netfs_data, enable);

	अगर (!index_key || !index_key_len || index_key_len > 255 || aux_data_len > 255)
		वापस शून्य;
	अगर (!aux_data || !aux_data_len) अणु
		aux_data = शून्य;
		aux_data_len = 0;
	पूर्ण

	fscache_stat(&fscache_n_acquires);

	/* अगर there's no parent cookie, then we don't create one here either */
	अगर (!parent) अणु
		fscache_stat(&fscache_n_acquires_null);
		_leave(" [no parent]");
		वापस शून्य;
	पूर्ण

	/* validate the definition */
	BUG_ON(!def->name[0]);

	BUG_ON(def->type == FSCACHE_COOKIE_TYPE_INDEX &&
	       parent->type != FSCACHE_COOKIE_TYPE_INDEX);

	candidate = fscache_alloc_cookie(parent, def,
					 index_key, index_key_len,
					 aux_data, aux_data_len,
					 netfs_data, object_size);
	अगर (!candidate) अणु
		fscache_stat(&fscache_n_acquires_oom);
		_leave(" [ENOMEM]");
		वापस शून्य;
	पूर्ण

	cookie = fscache_hash_cookie(candidate);
	अगर (!cookie) अणु
		trace_fscache_cookie(candidate, fscache_cookie_discard, 1);
		जाओ out;
	पूर्ण

	अगर (cookie == candidate)
		candidate = शून्य;

	चयन (cookie->type) अणु
	हाल FSCACHE_COOKIE_TYPE_INDEX:
		fscache_stat(&fscache_n_cookie_index);
		अवरोध;
	हाल FSCACHE_COOKIE_TYPE_DATAखाता:
		fscache_stat(&fscache_n_cookie_data);
		अवरोध;
	शेष:
		fscache_stat(&fscache_n_cookie_special);
		अवरोध;
	पूर्ण

	trace_fscache_acquire(cookie);

	अगर (enable) अणु
		/* अगर the object is an index then we need करो nothing more here
		 * - we create indices on disk when we need them as an index
		 * may exist in multiple caches */
		अगर (cookie->type != FSCACHE_COOKIE_TYPE_INDEX) अणु
			अगर (fscache_acquire_non_index_cookie(cookie, object_size) == 0) अणु
				set_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags);
			पूर्ण अन्यथा अणु
				atomic_dec(&parent->n_children);
				fscache_cookie_put(cookie,
						   fscache_cookie_put_acquire_nobufs);
				fscache_stat(&fscache_n_acquires_nobufs);
				_leave(" = NULL");
				वापस शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			set_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags);
		पूर्ण
	पूर्ण

	fscache_stat(&fscache_n_acquires_ok);

out:
	fscache_मुक्त_cookie(candidate);
	वापस cookie;
पूर्ण
EXPORT_SYMBOL(__fscache_acquire_cookie);

/*
 * Enable a cookie to permit it to accept new operations.
 */
व्योम __fscache_enable_cookie(काष्ठा fscache_cookie *cookie,
			     स्थिर व्योम *aux_data,
			     loff_t object_size,
			     bool (*can_enable)(व्योम *data),
			     व्योम *data)
अणु
	_enter("%p", cookie);

	trace_fscache_enable(cookie);

	रुको_on_bit_lock(&cookie->flags, FSCACHE_COOKIE_ENABLEMENT_LOCK,
			 TASK_UNINTERRUPTIBLE);

	fscache_update_aux(cookie, aux_data);

	अगर (test_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags))
		जाओ out_unlock;

	अगर (can_enable && !can_enable(data)) अणु
		/* The netfs decided it didn't want to enable after all */
	पूर्ण अन्यथा अगर (cookie->type != FSCACHE_COOKIE_TYPE_INDEX) अणु
		/* Wait क्रम outstanding disablement to complete */
		__fscache_रुको_on_invalidate(cookie);

		अगर (fscache_acquire_non_index_cookie(cookie, object_size) == 0)
			set_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags);
	पूर्ण अन्यथा अणु
		set_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags);
	पूर्ण

out_unlock:
	clear_bit_unlock(FSCACHE_COOKIE_ENABLEMENT_LOCK, &cookie->flags);
	wake_up_bit(&cookie->flags, FSCACHE_COOKIE_ENABLEMENT_LOCK);
पूर्ण
EXPORT_SYMBOL(__fscache_enable_cookie);

/*
 * acquire a non-index cookie
 * - this must make sure the index chain is instantiated and instantiate the
 *   object representation too
 */
अटल पूर्णांक fscache_acquire_non_index_cookie(काष्ठा fscache_cookie *cookie,
					    loff_t object_size)
अणु
	काष्ठा fscache_object *object;
	काष्ठा fscache_cache *cache;
	पूर्णांक ret;

	_enter("");

	set_bit(FSCACHE_COOKIE_UNAVAILABLE, &cookie->flags);

	/* now we need to see whether the backing objects क्रम this cookie yet
	 * exist, अगर not there'll be nothing to search */
	करोwn_पढ़ो(&fscache_addहटाओ_sem);

	अगर (list_empty(&fscache_cache_list)) अणु
		up_पढ़ो(&fscache_addहटाओ_sem);
		_leave(" = 0 [no caches]");
		वापस 0;
	पूर्ण

	/* select a cache in which to store the object */
	cache = fscache_select_cache_क्रम_object(cookie->parent);
	अगर (!cache) अणु
		up_पढ़ो(&fscache_addहटाओ_sem);
		fscache_stat(&fscache_n_acquires_no_cache);
		_leave(" = -ENOMEDIUM [no cache]");
		वापस -ENOMEDIUM;
	पूर्ण

	_debug("cache %s", cache->tag->name);

	set_bit(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags);

	/* ask the cache to allocate objects क्रम this cookie and its parent
	 * chain */
	ret = fscache_alloc_object(cache, cookie);
	अगर (ret < 0) अणु
		up_पढ़ो(&fscache_addहटाओ_sem);
		_leave(" = %d", ret);
		वापस ret;
	पूर्ण

	spin_lock(&cookie->lock);
	अगर (hlist_empty(&cookie->backing_objects)) अणु
		spin_unlock(&cookie->lock);
		जाओ unavailable;
	पूर्ण

	object = hlist_entry(cookie->backing_objects.first,
			     काष्ठा fscache_object, cookie_link);

	fscache_set_store_limit(object, object_size);

	/* initiate the process of looking up all the objects in the chain
	 * (करोne by fscache_initialise_object()) */
	fscache_उठाओ_event(object, FSCACHE_OBJECT_EV_NEW_CHILD);

	spin_unlock(&cookie->lock);

	/* we may be required to रुको क्रम lookup to complete at this poपूर्णांक */
	अगर (!fscache_defer_lookup) अणु
		_debug("non-deferred lookup %p", &cookie->flags);
		रुको_on_bit(&cookie->flags, FSCACHE_COOKIE_LOOKING_UP,
			    TASK_UNINTERRUPTIBLE);
		_debug("complete");
		अगर (test_bit(FSCACHE_COOKIE_UNAVAILABLE, &cookie->flags))
			जाओ unavailable;
	पूर्ण

	up_पढ़ो(&fscache_addहटाओ_sem);
	_leave(" = 0 [deferred]");
	वापस 0;

unavailable:
	up_पढ़ो(&fscache_addहटाओ_sem);
	_leave(" = -ENOBUFS");
	वापस -ENOBUFS;
पूर्ण

/*
 * recursively allocate cache object records क्रम a cookie/cache combination
 * - caller must be holding the addहटाओ sem
 */
अटल पूर्णांक fscache_alloc_object(काष्ठा fscache_cache *cache,
				काष्ठा fscache_cookie *cookie)
अणु
	काष्ठा fscache_object *object;
	पूर्णांक ret;

	_enter("%p,%p{%s}", cache, cookie, cookie->def->name);

	spin_lock(&cookie->lock);
	hlist_क्रम_each_entry(object, &cookie->backing_objects,
			     cookie_link) अणु
		अगर (object->cache == cache)
			जाओ object_alपढ़ोy_extant;
	पूर्ण
	spin_unlock(&cookie->lock);

	/* ask the cache to allocate an object (we may end up with duplicate
	 * objects at this stage, but we sort that out later) */
	fscache_stat(&fscache_n_cop_alloc_object);
	object = cache->ops->alloc_object(cache, cookie);
	fscache_stat_d(&fscache_n_cop_alloc_object);
	अगर (IS_ERR(object)) अणु
		fscache_stat(&fscache_n_object_no_alloc);
		ret = PTR_ERR(object);
		जाओ error;
	पूर्ण

	ASSERTCMP(object->cookie, ==, cookie);
	fscache_stat(&fscache_n_object_alloc);

	object->debug_id = atomic_inc_वापस(&fscache_object_debug_id);

	_debug("ALLOC OBJ%x: %s {%lx}",
	       object->debug_id, cookie->def->name, object->events);

	ret = fscache_alloc_object(cache, cookie->parent);
	अगर (ret < 0)
		जाओ error_put;

	/* only attach अगर we managed to allocate all we needed, otherwise
	 * discard the object we just allocated and instead use the one
	 * attached to the cookie */
	अगर (fscache_attach_object(cookie, object) < 0) अणु
		fscache_stat(&fscache_n_cop_put_object);
		cache->ops->put_object(object, fscache_obj_put_attach_fail);
		fscache_stat_d(&fscache_n_cop_put_object);
	पूर्ण

	_leave(" = 0");
	वापस 0;

object_alपढ़ोy_extant:
	ret = -ENOBUFS;
	अगर (fscache_object_is_dying(object) ||
	    fscache_cache_is_broken(object)) अणु
		spin_unlock(&cookie->lock);
		जाओ error;
	पूर्ण
	spin_unlock(&cookie->lock);
	_leave(" = 0 [found]");
	वापस 0;

error_put:
	fscache_stat(&fscache_n_cop_put_object);
	cache->ops->put_object(object, fscache_obj_put_alloc_fail);
	fscache_stat_d(&fscache_n_cop_put_object);
error:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * attach a cache object to a cookie
 */
अटल पूर्णांक fscache_attach_object(काष्ठा fscache_cookie *cookie,
				 काष्ठा fscache_object *object)
अणु
	काष्ठा fscache_object *p;
	काष्ठा fscache_cache *cache = object->cache;
	पूर्णांक ret;

	_enter("{%s},{OBJ%x}", cookie->def->name, object->debug_id);

	ASSERTCMP(object->cookie, ==, cookie);

	spin_lock(&cookie->lock);

	/* there may be multiple initial creations of this object, but we only
	 * want one */
	ret = -EEXIST;
	hlist_क्रम_each_entry(p, &cookie->backing_objects, cookie_link) अणु
		अगर (p->cache == object->cache) अणु
			अगर (fscache_object_is_dying(p))
				ret = -ENOBUFS;
			जाओ cant_attach_object;
		पूर्ण
	पूर्ण

	/* pin the parent object */
	spin_lock_nested(&cookie->parent->lock, 1);
	hlist_क्रम_each_entry(p, &cookie->parent->backing_objects,
			     cookie_link) अणु
		अगर (p->cache == object->cache) अणु
			अगर (fscache_object_is_dying(p)) अणु
				ret = -ENOBUFS;
				spin_unlock(&cookie->parent->lock);
				जाओ cant_attach_object;
			पूर्ण
			object->parent = p;
			spin_lock(&p->lock);
			p->n_children++;
			spin_unlock(&p->lock);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&cookie->parent->lock);

	/* attach to the cache's object list */
	अगर (list_empty(&object->cache_link)) अणु
		spin_lock(&cache->object_list_lock);
		list_add(&object->cache_link, &cache->object_list);
		spin_unlock(&cache->object_list_lock);
	पूर्ण

	/* Attach to the cookie.  The object alपढ़ोy has a ref on it. */
	hlist_add_head(&object->cookie_link, &cookie->backing_objects);

	fscache_objlist_add(object);
	ret = 0;

cant_attach_object:
	spin_unlock(&cookie->lock);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Invalidate an object.  Callable with spinlocks held.
 */
व्योम __fscache_invalidate(काष्ठा fscache_cookie *cookie)
अणु
	काष्ठा fscache_object *object;

	_enter("{%s}", cookie->def->name);

	fscache_stat(&fscache_n_invalidates);

	/* Only permit invalidation of data files.  Invalidating an index will
	 * require the caller to release all its attachments to the tree rooted
	 * there, and अगर it's करोing that, it may as well just retire the
	 * cookie.
	 */
	ASSERTCMP(cookie->type, ==, FSCACHE_COOKIE_TYPE_DATAखाता);

	/* If there's an object, we tell the object state machine to handle the
	 * invalidation on our behalf, otherwise there's nothing to करो.
	 */
	अगर (!hlist_empty(&cookie->backing_objects)) अणु
		spin_lock(&cookie->lock);

		अगर (fscache_cookie_enabled(cookie) &&
		    !hlist_empty(&cookie->backing_objects) &&
		    !test_and_set_bit(FSCACHE_COOKIE_INVALIDATING,
				      &cookie->flags)) अणु
			object = hlist_entry(cookie->backing_objects.first,
					     काष्ठा fscache_object,
					     cookie_link);
			अगर (fscache_object_is_live(object))
				fscache_उठाओ_event(
					object, FSCACHE_OBJECT_EV_INVALIDATE);
		पूर्ण

		spin_unlock(&cookie->lock);
	पूर्ण

	_leave("");
पूर्ण
EXPORT_SYMBOL(__fscache_invalidate);

/*
 * Wait क्रम object invalidation to complete.
 */
व्योम __fscache_रुको_on_invalidate(काष्ठा fscache_cookie *cookie)
अणु
	_enter("%p", cookie);

	रुको_on_bit(&cookie->flags, FSCACHE_COOKIE_INVALIDATING,
		    TASK_UNINTERRUPTIBLE);

	_leave("");
पूर्ण
EXPORT_SYMBOL(__fscache_रुको_on_invalidate);

/*
 * update the index entries backing a cookie
 */
व्योम __fscache_update_cookie(काष्ठा fscache_cookie *cookie, स्थिर व्योम *aux_data)
अणु
	काष्ठा fscache_object *object;

	fscache_stat(&fscache_n_updates);

	अगर (!cookie) अणु
		fscache_stat(&fscache_n_updates_null);
		_leave(" [no cookie]");
		वापस;
	पूर्ण

	_enter("{%s}", cookie->def->name);

	spin_lock(&cookie->lock);

	fscache_update_aux(cookie, aux_data);

	अगर (fscache_cookie_enabled(cookie)) अणु
		/* update the index entry on disk in each cache backing this
		 * cookie.
		 */
		hlist_क्रम_each_entry(object,
				     &cookie->backing_objects, cookie_link) अणु
			fscache_उठाओ_event(object, FSCACHE_OBJECT_EV_UPDATE);
		पूर्ण
	पूर्ण

	spin_unlock(&cookie->lock);
	_leave("");
पूर्ण
EXPORT_SYMBOL(__fscache_update_cookie);

/*
 * Disable a cookie to stop it from accepting new requests from the netfs.
 */
व्योम __fscache_disable_cookie(काष्ठा fscache_cookie *cookie,
			      स्थिर व्योम *aux_data,
			      bool invalidate)
अणु
	काष्ठा fscache_object *object;
	bool awaken = false;

	_enter("%p,%u", cookie, invalidate);

	trace_fscache_disable(cookie);

	ASSERTCMP(atomic_पढ़ो(&cookie->n_active), >, 0);

	अगर (atomic_पढ़ो(&cookie->n_children) != 0) अणु
		pr_err("Cookie '%s' still has children\n",
		       cookie->def->name);
		BUG();
	पूर्ण

	रुको_on_bit_lock(&cookie->flags, FSCACHE_COOKIE_ENABLEMENT_LOCK,
			 TASK_UNINTERRUPTIBLE);

	fscache_update_aux(cookie, aux_data);

	अगर (!test_and_clear_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags))
		जाओ out_unlock_enable;

	/* If the cookie is being invalidated, रुको क्रम that to complete first
	 * so that we can reuse the flag.
	 */
	__fscache_रुको_on_invalidate(cookie);

	/* Dispose of the backing objects */
	set_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags);

	spin_lock(&cookie->lock);
	अगर (!hlist_empty(&cookie->backing_objects)) अणु
		hlist_क्रम_each_entry(object, &cookie->backing_objects, cookie_link) अणु
			अगर (invalidate)
				set_bit(FSCACHE_OBJECT_RETIRED, &object->flags);
			clear_bit(FSCACHE_OBJECT_PENDING_WRITE, &object->flags);
			fscache_उठाओ_event(object, FSCACHE_OBJECT_EV_KILL);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (test_and_clear_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags))
			awaken = true;
	पूर्ण
	spin_unlock(&cookie->lock);
	अगर (awaken)
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_INVALIDATING);

	/* Wait क्रम cessation of activity requiring access to the netfs (when
	 * n_active reaches 0).  This makes sure outstanding पढ़ोs and ग_लिखोs
	 * have completed.
	 */
	अगर (!atomic_dec_and_test(&cookie->n_active)) अणु
		रुको_var_event(&cookie->n_active,
			       !atomic_पढ़ो(&cookie->n_active));
	पूर्ण

	/* Make sure any pending ग_लिखोs are cancelled. */
	अगर (cookie->type != FSCACHE_COOKIE_TYPE_INDEX)
		fscache_invalidate_ग_लिखोs(cookie);

	/* Reset the cookie state अगर it wasn't relinquished */
	अगर (!test_bit(FSCACHE_COOKIE_RELINQUISHED, &cookie->flags)) अणु
		atomic_inc(&cookie->n_active);
		set_bit(FSCACHE_COOKIE_NO_DATA_YET, &cookie->flags);
	पूर्ण

out_unlock_enable:
	clear_bit_unlock(FSCACHE_COOKIE_ENABLEMENT_LOCK, &cookie->flags);
	wake_up_bit(&cookie->flags, FSCACHE_COOKIE_ENABLEMENT_LOCK);
	_leave("");
पूर्ण
EXPORT_SYMBOL(__fscache_disable_cookie);

/*
 * release a cookie back to the cache
 * - the object will be marked as recyclable on disk अगर retire is true
 * - all dependents of this cookie must have alपढ़ोy been unरेजिस्टरed
 *   (indices/files/pages)
 */
व्योम __fscache_relinquish_cookie(काष्ठा fscache_cookie *cookie,
				 स्थिर व्योम *aux_data,
				 bool retire)
अणु
	fscache_stat(&fscache_n_relinquishes);
	अगर (retire)
		fscache_stat(&fscache_n_relinquishes_retire);

	अगर (!cookie) अणु
		fscache_stat(&fscache_n_relinquishes_null);
		_leave(" [no cookie]");
		वापस;
	पूर्ण

	_enter("%p{%s,%p,%d},%d",
	       cookie, cookie->def->name, cookie->netfs_data,
	       atomic_पढ़ो(&cookie->n_active), retire);

	trace_fscache_relinquish(cookie, retire);

	/* No further netfs-accessing operations on this cookie permitted */
	अगर (test_and_set_bit(FSCACHE_COOKIE_RELINQUISHED, &cookie->flags))
		BUG();

	__fscache_disable_cookie(cookie, aux_data, retire);

	/* Clear poपूर्णांकers back to the netfs */
	cookie->netfs_data	= शून्य;
	cookie->def		= शून्य;
	BUG_ON(!radix_tree_empty(&cookie->stores));

	अगर (cookie->parent) अणु
		ASSERTCMP(atomic_पढ़ो(&cookie->parent->usage), >, 0);
		ASSERTCMP(atomic_पढ़ो(&cookie->parent->n_children), >, 0);
		atomic_dec(&cookie->parent->n_children);
	पूर्ण

	/* Dispose of the netfs's link to the cookie */
	ASSERTCMP(atomic_पढ़ो(&cookie->usage), >, 0);
	fscache_cookie_put(cookie, fscache_cookie_put_relinquish);

	_leave("");
पूर्ण
EXPORT_SYMBOL(__fscache_relinquish_cookie);

/*
 * Remove a cookie from the hash table.
 */
अटल व्योम fscache_unhash_cookie(काष्ठा fscache_cookie *cookie)
अणु
	काष्ठा hlist_bl_head *h;
	अचिन्हित पूर्णांक bucket;

	bucket = cookie->key_hash & (ARRAY_SIZE(fscache_cookie_hash) - 1);
	h = &fscache_cookie_hash[bucket];

	hlist_bl_lock(h);
	hlist_bl_del(&cookie->hash_link);
	hlist_bl_unlock(h);
पूर्ण

/*
 * Drop a reference to a cookie.
 */
व्योम fscache_cookie_put(काष्ठा fscache_cookie *cookie,
			क्रमागत fscache_cookie_trace where)
अणु
	काष्ठा fscache_cookie *parent;
	पूर्णांक usage;

	_enter("%p", cookie);

	करो अणु
		usage = atomic_dec_वापस(&cookie->usage);
		trace_fscache_cookie(cookie, where, usage);

		अगर (usage > 0)
			वापस;
		BUG_ON(usage < 0);

		parent = cookie->parent;
		fscache_unhash_cookie(cookie);
		fscache_मुक्त_cookie(cookie);

		cookie = parent;
		where = fscache_cookie_put_parent;
	पूर्ण जबतक (cookie);

	_leave("");
पूर्ण

/*
 * check the consistency between the netfs inode and the backing cache
 *
 * NOTE: it only serves no-index type
 */
पूर्णांक __fscache_check_consistency(काष्ठा fscache_cookie *cookie,
				स्थिर व्योम *aux_data)
अणु
	काष्ठा fscache_operation *op;
	काष्ठा fscache_object *object;
	bool wake_cookie = false;
	पूर्णांक ret;

	_enter("%p,", cookie);

	ASSERTCMP(cookie->type, ==, FSCACHE_COOKIE_TYPE_DATAखाता);

	अगर (fscache_रुको_क्रम_deferred_lookup(cookie) < 0)
		वापस -ERESTARTSYS;

	अगर (hlist_empty(&cookie->backing_objects))
		वापस 0;

	op = kzalloc(माप(*op), GFP_NOIO | __GFP_NOMEMALLOC | __GFP_NORETRY);
	अगर (!op)
		वापस -ENOMEM;

	fscache_operation_init(cookie, op, शून्य, शून्य, शून्य);
	op->flags = FSCACHE_OP_MYTHREAD |
		(1 << FSCACHE_OP_WAITING) |
		(1 << FSCACHE_OP_UNUSE_COOKIE);
	trace_fscache_page_op(cookie, शून्य, op, fscache_page_op_check_consistency);

	spin_lock(&cookie->lock);

	fscache_update_aux(cookie, aux_data);

	अगर (!fscache_cookie_enabled(cookie) ||
	    hlist_empty(&cookie->backing_objects))
		जाओ inconsistent;
	object = hlist_entry(cookie->backing_objects.first,
			     काष्ठा fscache_object, cookie_link);
	अगर (test_bit(FSCACHE_IOERROR, &object->cache->flags))
		जाओ inconsistent;

	op->debug_id = atomic_inc_वापस(&fscache_op_debug_id);

	__fscache_use_cookie(cookie);
	अगर (fscache_submit_op(object, op) < 0)
		जाओ submit_failed;

	/* the work queue now carries its own ref on the object */
	spin_unlock(&cookie->lock);

	ret = fscache_रुको_क्रम_operation_activation(object, op, शून्य, शून्य);
	अगर (ret == 0) अणु
		/* ask the cache to honour the operation */
		ret = object->cache->ops->check_consistency(op);
		fscache_op_complete(op, false);
	पूर्ण अन्यथा अगर (ret == -ENOBUFS) अणु
		ret = 0;
	पूर्ण

	fscache_put_operation(op);
	_leave(" = %d", ret);
	वापस ret;

submit_failed:
	wake_cookie = __fscache_unuse_cookie(cookie);
inconsistent:
	spin_unlock(&cookie->lock);
	अगर (wake_cookie)
		__fscache_wake_unused_cookie(cookie);
	kमुक्त(op);
	_leave(" = -ESTALE");
	वापस -ESTALE;
पूर्ण
EXPORT_SYMBOL(__fscache_check_consistency);
