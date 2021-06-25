<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* FS-Cache cache handling
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा FSCACHE_DEBUG_LEVEL CACHE
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

LIST_HEAD(fscache_cache_list);
DECLARE_RWSEM(fscache_addहटाओ_sem);
DECLARE_WAIT_QUEUE_HEAD(fscache_cache_cleared_wq);
EXPORT_SYMBOL(fscache_cache_cleared_wq);

अटल LIST_HEAD(fscache_cache_tag_list);

/*
 * look up a cache tag
 */
काष्ठा fscache_cache_tag *__fscache_lookup_cache_tag(स्थिर अक्षर *name)
अणु
	काष्ठा fscache_cache_tag *tag, *xtag;

	/* firstly check क्रम the existence of the tag under पढ़ो lock */
	करोwn_पढ़ो(&fscache_addहटाओ_sem);

	list_क्रम_each_entry(tag, &fscache_cache_tag_list, link) अणु
		अगर (म_भेद(tag->name, name) == 0) अणु
			atomic_inc(&tag->usage);
			up_पढ़ो(&fscache_addहटाओ_sem);
			वापस tag;
		पूर्ण
	पूर्ण

	up_पढ़ो(&fscache_addहटाओ_sem);

	/* the tag करोes not exist - create a candidate */
	xtag = kzalloc(माप(*xtag) + म_माप(name) + 1, GFP_KERNEL);
	अगर (!xtag)
		/* वापस a dummy tag अगर out of memory */
		वापस ERR_PTR(-ENOMEM);

	atomic_set(&xtag->usage, 1);
	म_नकल(xtag->name, name);

	/* ग_लिखो lock, search again and add अगर still not present */
	करोwn_ग_लिखो(&fscache_addहटाओ_sem);

	list_क्रम_each_entry(tag, &fscache_cache_tag_list, link) अणु
		अगर (म_भेद(tag->name, name) == 0) अणु
			atomic_inc(&tag->usage);
			up_ग_लिखो(&fscache_addहटाओ_sem);
			kमुक्त(xtag);
			वापस tag;
		पूर्ण
	पूर्ण

	list_add_tail(&xtag->link, &fscache_cache_tag_list);
	up_ग_लिखो(&fscache_addहटाओ_sem);
	वापस xtag;
पूर्ण

/*
 * release a reference to a cache tag
 */
व्योम __fscache_release_cache_tag(काष्ठा fscache_cache_tag *tag)
अणु
	अगर (tag != ERR_PTR(-ENOMEM)) अणु
		करोwn_ग_लिखो(&fscache_addहटाओ_sem);

		अगर (atomic_dec_and_test(&tag->usage))
			list_del_init(&tag->link);
		अन्यथा
			tag = शून्य;

		up_ग_लिखो(&fscache_addहटाओ_sem);

		kमुक्त(tag);
	पूर्ण
पूर्ण

/*
 * select a cache in which to store an object
 * - the cache addहटाओ semaphore must be at least पढ़ो-locked by the caller
 * - the object will never be an index
 */
काष्ठा fscache_cache *fscache_select_cache_क्रम_object(
	काष्ठा fscache_cookie *cookie)
अणु
	काष्ठा fscache_cache_tag *tag;
	काष्ठा fscache_object *object;
	काष्ठा fscache_cache *cache;

	_enter("");

	अगर (list_empty(&fscache_cache_list)) अणु
		_leave(" = NULL [no cache]");
		वापस शून्य;
	पूर्ण

	/* we check the parent to determine the cache to use */
	spin_lock(&cookie->lock);

	/* the first in the parent's backing list should be the preferred
	 * cache */
	अगर (!hlist_empty(&cookie->backing_objects)) अणु
		object = hlist_entry(cookie->backing_objects.first,
				     काष्ठा fscache_object, cookie_link);

		cache = object->cache;
		अगर (fscache_object_is_dying(object) ||
		    test_bit(FSCACHE_IOERROR, &cache->flags))
			cache = शून्य;

		spin_unlock(&cookie->lock);
		_leave(" = %p [parent]", cache);
		वापस cache;
	पूर्ण

	/* the parent is unbacked */
	अगर (cookie->type != FSCACHE_COOKIE_TYPE_INDEX) अणु
		/* cookie not an index and is unbacked */
		spin_unlock(&cookie->lock);
		_leave(" = NULL [cookie ub,ni]");
		वापस शून्य;
	पूर्ण

	spin_unlock(&cookie->lock);

	अगर (!cookie->def->select_cache)
		जाओ no_preference;

	/* ask the netfs क्रम its preference */
	tag = cookie->def->select_cache(cookie->parent->netfs_data,
					cookie->netfs_data);
	अगर (!tag)
		जाओ no_preference;

	अगर (tag == ERR_PTR(-ENOMEM)) अणु
		_leave(" = NULL [nomem tag]");
		वापस शून्य;
	पूर्ण

	अगर (!tag->cache) अणु
		_leave(" = NULL [unbacked tag]");
		वापस शून्य;
	पूर्ण

	अगर (test_bit(FSCACHE_IOERROR, &tag->cache->flags))
		वापस शून्य;

	_leave(" = %p [specific]", tag->cache);
	वापस tag->cache;

no_preference:
	/* netfs has no preference - just select first cache */
	cache = list_entry(fscache_cache_list.next,
			   काष्ठा fscache_cache, link);
	_leave(" = %p [first]", cache);
	वापस cache;
पूर्ण

/**
 * fscache_init_cache - Initialise a cache record
 * @cache: The cache record to be initialised
 * @ops: The cache operations to be installed in that record
 * @idfmt: Format string to define identअगरier
 * @...: प्र_लिखो-style arguments
 *
 * Initialise a record of a cache and fill in the name.
 *
 * See Documentation/fileप्रणालीs/caching/backend-api.rst क्रम a complete
 * description.
 */
व्योम fscache_init_cache(काष्ठा fscache_cache *cache,
			स्थिर काष्ठा fscache_cache_ops *ops,
			स्थिर अक्षर *idfmt,
			...)
अणु
	बहु_सूची va;

	स_रखो(cache, 0, माप(*cache));

	cache->ops = ops;

	बहु_शुरू(va, idfmt);
	vsnम_लिखो(cache->identअगरier, माप(cache->identअगरier), idfmt, va);
	बहु_पूर्ण(va);

	INIT_WORK(&cache->op_gc, fscache_operation_gc);
	INIT_LIST_HEAD(&cache->link);
	INIT_LIST_HEAD(&cache->object_list);
	INIT_LIST_HEAD(&cache->op_gc_list);
	spin_lock_init(&cache->object_list_lock);
	spin_lock_init(&cache->op_gc_list_lock);
पूर्ण
EXPORT_SYMBOL(fscache_init_cache);

/**
 * fscache_add_cache - Declare a cache as being खोलो क्रम business
 * @cache: The record describing the cache
 * @अगरsdef: The record of the cache object describing the top-level index
 * @tagname: The tag describing this cache
 *
 * Add a cache to the प्रणाली, making it available क्रम netfs's to use.
 *
 * See Documentation/fileप्रणालीs/caching/backend-api.rst क्रम a complete
 * description.
 */
पूर्णांक fscache_add_cache(काष्ठा fscache_cache *cache,
		      काष्ठा fscache_object *अगरsdef,
		      स्थिर अक्षर *tagname)
अणु
	काष्ठा fscache_cache_tag *tag;

	ASSERTCMP(अगरsdef->cookie, ==, &fscache_fsdef_index);
	BUG_ON(!cache->ops);
	BUG_ON(!अगरsdef);

	cache->flags = 0;
	अगरsdef->event_mask =
		((1 << NR_FSCACHE_OBJECT_EVENTS) - 1) &
		~(1 << FSCACHE_OBJECT_EV_CLEARED);
	__set_bit(FSCACHE_OBJECT_IS_AVAILABLE, &अगरsdef->flags);

	अगर (!tagname)
		tagname = cache->identअगरier;

	BUG_ON(!tagname[0]);

	_enter("{%s.%s},,%s", cache->ops->name, cache->identअगरier, tagname);

	/* we use the cache tag to uniquely identअगरy caches */
	tag = __fscache_lookup_cache_tag(tagname);
	अगर (IS_ERR(tag))
		जाओ nomem;

	अगर (test_and_set_bit(FSCACHE_TAG_RESERVED, &tag->flags))
		जाओ tag_in_use;

	cache->kobj = kobject_create_and_add(tagname, fscache_root);
	अगर (!cache->kobj)
		जाओ error;

	अगरsdef->cache = cache;
	cache->fsdef = अगरsdef;

	करोwn_ग_लिखो(&fscache_addहटाओ_sem);

	tag->cache = cache;
	cache->tag = tag;

	/* add the cache to the list */
	list_add(&cache->link, &fscache_cache_list);

	/* add the cache's netfs definition index object to the cache's
	 * list */
	spin_lock(&cache->object_list_lock);
	list_add_tail(&अगरsdef->cache_link, &cache->object_list);
	spin_unlock(&cache->object_list_lock);
	fscache_objlist_add(अगरsdef);

	/* add the cache's netfs definition index object to the top level index
	 * cookie as a known backing object */
	spin_lock(&fscache_fsdef_index.lock);

	hlist_add_head(&अगरsdef->cookie_link,
		       &fscache_fsdef_index.backing_objects);

	atomic_inc(&fscache_fsdef_index.usage);

	/* करोne */
	spin_unlock(&fscache_fsdef_index.lock);
	up_ग_लिखो(&fscache_addहटाओ_sem);

	pr_notice("Cache \"%s\" added (type %s)\n",
		  cache->tag->name, cache->ops->name);
	kobject_uevent(cache->kobj, KOBJ_ADD);

	_leave(" = 0 [%s]", cache->identअगरier);
	वापस 0;

tag_in_use:
	pr_err("Cache tag '%s' already in use\n", tagname);
	__fscache_release_cache_tag(tag);
	_leave(" = -EXIST");
	वापस -EEXIST;

error:
	__fscache_release_cache_tag(tag);
	_leave(" = -EINVAL");
	वापस -EINVAL;

nomem:
	_leave(" = -ENOMEM");
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(fscache_add_cache);

/**
 * fscache_io_error - Note a cache I/O error
 * @cache: The record describing the cache
 *
 * Note that an I/O error occurred in a cache and that it should no दीर्घer be
 * used क्रम anything.  This also reports the error पूर्णांकo the kernel log.
 *
 * See Documentation/fileप्रणालीs/caching/backend-api.rst क्रम a complete
 * description.
 */
व्योम fscache_io_error(काष्ठा fscache_cache *cache)
अणु
	अगर (!test_and_set_bit(FSCACHE_IOERROR, &cache->flags))
		pr_err("Cache '%s' stopped due to I/O error\n",
		       cache->ops->name);
पूर्ण
EXPORT_SYMBOL(fscache_io_error);

/*
 * request withdrawal of all the objects in a cache
 * - all the objects being withdrawn are moved onto the supplied list
 */
अटल व्योम fscache_withdraw_all_objects(काष्ठा fscache_cache *cache,
					 काष्ठा list_head *dying_objects)
अणु
	काष्ठा fscache_object *object;

	जबतक (!list_empty(&cache->object_list)) अणु
		spin_lock(&cache->object_list_lock);

		अगर (!list_empty(&cache->object_list)) अणु
			object = list_entry(cache->object_list.next,
					    काष्ठा fscache_object, cache_link);
			list_move_tail(&object->cache_link, dying_objects);

			_debug("withdraw %p", object->cookie);

			/* This must be करोne under object_list_lock to prevent
			 * a race with fscache_drop_object().
			 */
			fscache_उठाओ_event(object, FSCACHE_OBJECT_EV_KILL);
		पूर्ण

		spin_unlock(&cache->object_list_lock);
		cond_resched();
	पूर्ण
पूर्ण

/**
 * fscache_withdraw_cache - Withdraw a cache from the active service
 * @cache: The record describing the cache
 *
 * Withdraw a cache from service, unbinding all its cache objects from the
 * netfs cookies they're currently representing.
 *
 * See Documentation/fileप्रणालीs/caching/backend-api.rst क्रम a complete
 * description.
 */
व्योम fscache_withdraw_cache(काष्ठा fscache_cache *cache)
अणु
	LIST_HEAD(dying_objects);

	_enter("");

	pr_notice("Withdrawing cache \"%s\"\n",
		  cache->tag->name);

	/* make the cache unavailable क्रम cookie acquisition */
	अगर (test_and_set_bit(FSCACHE_CACHE_WITHDRAWN, &cache->flags))
		BUG();

	करोwn_ग_लिखो(&fscache_addहटाओ_sem);
	list_del_init(&cache->link);
	cache->tag->cache = शून्य;
	up_ग_लिखो(&fscache_addहटाओ_sem);

	/* make sure all pages pinned by operations on behalf of the netfs are
	 * written to disk */
	fscache_stat(&fscache_n_cop_sync_cache);
	cache->ops->sync_cache(cache);
	fscache_stat_d(&fscache_n_cop_sync_cache);

	/* dissociate all the netfs pages backed by this cache from the block
	 * mappings in the cache */
	fscache_stat(&fscache_n_cop_dissociate_pages);
	cache->ops->dissociate_pages(cache);
	fscache_stat_d(&fscache_n_cop_dissociate_pages);

	/* we now have to destroy all the active objects pertaining to this
	 * cache - which we करो by passing them off to thपढ़ो pool to be
	 * disposed of */
	_debug("destroy");

	fscache_withdraw_all_objects(cache, &dying_objects);

	/* रुको क्रम all extant objects to finish their outstanding operations
	 * and go away */
	_debug("wait for finish");
	रुको_event(fscache_cache_cleared_wq,
		   atomic_पढ़ो(&cache->object_count) == 0);
	_debug("wait for clearance");
	रुको_event(fscache_cache_cleared_wq,
		   list_empty(&cache->object_list));
	_debug("cleared");
	ASSERT(list_empty(&dying_objects));

	kobject_put(cache->kobj);

	clear_bit(FSCACHE_TAG_RESERVED, &cache->tag->flags);
	fscache_release_cache_tag(cache->tag);
	cache->tag = शून्य;

	_leave("");
पूर्ण
EXPORT_SYMBOL(fscache_withdraw_cache);
