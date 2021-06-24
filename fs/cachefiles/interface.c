<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* FS-Cache पूर्णांकerface to CacheFiles
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/mount.h>
#समावेश "internal.h"

काष्ठा cachefiles_lookup_data अणु
	काष्ठा cachefiles_xattr	*auxdata;	/* auxiliary data */
	अक्षर			*key;		/* key path */
पूर्ण;

अटल पूर्णांक cachefiles_attr_changed(काष्ठा fscache_object *_object);

/*
 * allocate an object record क्रम a cookie lookup and prepare the lookup data
 */
अटल काष्ठा fscache_object *cachefiles_alloc_object(
	काष्ठा fscache_cache *_cache,
	काष्ठा fscache_cookie *cookie)
अणु
	काष्ठा cachefiles_lookup_data *lookup_data;
	काष्ठा cachefiles_object *object;
	काष्ठा cachefiles_cache *cache;
	काष्ठा cachefiles_xattr *auxdata;
	अचिन्हित keylen, auxlen;
	व्योम *buffer, *p;
	अक्षर *key;

	cache = container_of(_cache, काष्ठा cachefiles_cache, cache);

	_enter("{%s},%p,", cache->cache.identअगरier, cookie);

	lookup_data = kदो_स्मृति(माप(*lookup_data), cachefiles_gfp);
	अगर (!lookup_data)
		जाओ nomem_lookup_data;

	/* create a new object record and a temporary leaf image */
	object = kmem_cache_alloc(cachefiles_object_jar, cachefiles_gfp);
	अगर (!object)
		जाओ nomem_object;

	ASSERTCMP(object->backer, ==, शून्य);

	BUG_ON(test_bit(CACHEखाताS_OBJECT_ACTIVE, &object->flags));
	atomic_set(&object->usage, 1);

	fscache_object_init(&object->fscache, cookie, &cache->cache);

	object->type = cookie->def->type;

	/* get hold of the raw key
	 * - stick the length on the front and leave space on the back क्रम the
	 *   encoder
	 */
	buffer = kदो_स्मृति((2 + 512) + 3, cachefiles_gfp);
	अगर (!buffer)
		जाओ nomem_buffer;

	keylen = cookie->key_len;
	अगर (keylen <= माप(cookie->अंतरभूत_key))
		p = cookie->अंतरभूत_key;
	अन्यथा
		p = cookie->key;
	स_नकल(buffer + 2, p, keylen);

	*(uपूर्णांक16_t *)buffer = keylen;
	((अक्षर *)buffer)[keylen + 2] = 0;
	((अक्षर *)buffer)[keylen + 3] = 0;
	((अक्षर *)buffer)[keylen + 4] = 0;

	/* turn the raw key पूर्णांकo something that can work with as a filename */
	key = cachefiles_cook_key(buffer, keylen + 2, object->type);
	अगर (!key)
		जाओ nomem_key;

	/* get hold of the auxiliary data and prepend the object type */
	auxdata = buffer;
	auxlen = cookie->aux_len;
	अगर (auxlen) अणु
		अगर (auxlen <= माप(cookie->अंतरभूत_aux))
			p = cookie->अंतरभूत_aux;
		अन्यथा
			p = cookie->aux;
		स_नकल(auxdata->data, p, auxlen);
	पूर्ण

	auxdata->len = auxlen + 1;
	auxdata->type = cookie->type;

	lookup_data->auxdata = auxdata;
	lookup_data->key = key;
	object->lookup_data = lookup_data;

	_leave(" = %p [%p]", &object->fscache, lookup_data);
	वापस &object->fscache;

nomem_key:
	kमुक्त(buffer);
nomem_buffer:
	BUG_ON(test_bit(CACHEखाताS_OBJECT_ACTIVE, &object->flags));
	kmem_cache_मुक्त(cachefiles_object_jar, object);
	fscache_object_destroyed(&cache->cache);
nomem_object:
	kमुक्त(lookup_data);
nomem_lookup_data:
	_leave(" = -ENOMEM");
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * attempt to look up the nominated node in this cache
 * - वापस -ETIMEDOUT to be scheduled again
 */
अटल पूर्णांक cachefiles_lookup_object(काष्ठा fscache_object *_object)
अणु
	काष्ठा cachefiles_lookup_data *lookup_data;
	काष्ठा cachefiles_object *parent, *object;
	काष्ठा cachefiles_cache *cache;
	स्थिर काष्ठा cred *saved_cred;
	पूर्णांक ret;

	_enter("{OBJ%x}", _object->debug_id);

	cache = container_of(_object->cache, काष्ठा cachefiles_cache, cache);
	parent = container_of(_object->parent,
			      काष्ठा cachefiles_object, fscache);
	object = container_of(_object, काष्ठा cachefiles_object, fscache);
	lookup_data = object->lookup_data;

	ASSERTCMP(lookup_data, !=, शून्य);

	/* look up the key, creating any missing bits */
	cachefiles_begin_secure(cache, &saved_cred);
	ret = cachefiles_walk_to_object(parent, object,
					lookup_data->key,
					lookup_data->auxdata);
	cachefiles_end_secure(cache, saved_cred);

	/* polish off by setting the attributes of non-index files */
	अगर (ret == 0 &&
	    object->fscache.cookie->def->type != FSCACHE_COOKIE_TYPE_INDEX)
		cachefiles_attr_changed(&object->fscache);

	अगर (ret < 0 && ret != -ETIMEDOUT) अणु
		अगर (ret != -ENOBUFS)
			pr_warn("Lookup failed error %d\n", ret);
		fscache_object_lookup_error(&object->fscache);
	पूर्ण

	_leave(" [%d]", ret);
	वापस ret;
पूर्ण

/*
 * indication of lookup completion
 */
अटल व्योम cachefiles_lookup_complete(काष्ठा fscache_object *_object)
अणु
	काष्ठा cachefiles_object *object;

	object = container_of(_object, काष्ठा cachefiles_object, fscache);

	_enter("{OBJ%x,%p}", object->fscache.debug_id, object->lookup_data);

	अगर (object->lookup_data) अणु
		kमुक्त(object->lookup_data->key);
		kमुक्त(object->lookup_data->auxdata);
		kमुक्त(object->lookup_data);
		object->lookup_data = शून्य;
	पूर्ण
पूर्ण

/*
 * increment the usage count on an inode object (may fail अगर unmounting)
 */
अटल
काष्ठा fscache_object *cachefiles_grab_object(काष्ठा fscache_object *_object,
					      क्रमागत fscache_obj_ref_trace why)
अणु
	काष्ठा cachefiles_object *object =
		container_of(_object, काष्ठा cachefiles_object, fscache);
	पूर्णांक u;

	_enter("{OBJ%x,%d}", _object->debug_id, atomic_पढ़ो(&object->usage));

#अगर_घोषित CACHEखाताS_DEBUG_SLAB
	ASSERT((atomic_पढ़ो(&object->usage) & 0xffff0000) != 0x6b6b0000);
#पूर्ण_अगर

	u = atomic_inc_वापस(&object->usage);
	trace_cachefiles_ref(object, _object->cookie,
			     (क्रमागत cachefiles_obj_ref_trace)why, u);
	वापस &object->fscache;
पूर्ण

/*
 * update the auxiliary data क्रम an object object on disk
 */
अटल व्योम cachefiles_update_object(काष्ठा fscache_object *_object)
अणु
	काष्ठा cachefiles_object *object;
	काष्ठा cachefiles_xattr *auxdata;
	काष्ठा cachefiles_cache *cache;
	काष्ठा fscache_cookie *cookie;
	स्थिर काष्ठा cred *saved_cred;
	स्थिर व्योम *aux;
	अचिन्हित auxlen;

	_enter("{OBJ%x}", _object->debug_id);

	object = container_of(_object, काष्ठा cachefiles_object, fscache);
	cache = container_of(object->fscache.cache, काष्ठा cachefiles_cache,
			     cache);

	अगर (!fscache_use_cookie(_object)) अणु
		_leave(" [relinq]");
		वापस;
	पूर्ण

	cookie = object->fscache.cookie;
	auxlen = cookie->aux_len;

	अगर (!auxlen) अणु
		fscache_unuse_cookie(_object);
		_leave(" [no aux]");
		वापस;
	पूर्ण

	auxdata = kदो_स्मृति(2 + auxlen + 3, cachefiles_gfp);
	अगर (!auxdata) अणु
		fscache_unuse_cookie(_object);
		_leave(" [nomem]");
		वापस;
	पूर्ण

	aux = (auxlen <= माप(cookie->अंतरभूत_aux)) ?
		cookie->अंतरभूत_aux : cookie->aux;

	स_नकल(auxdata->data, aux, auxlen);
	fscache_unuse_cookie(_object);

	auxdata->len = auxlen + 1;
	auxdata->type = cookie->type;

	cachefiles_begin_secure(cache, &saved_cred);
	cachefiles_update_object_xattr(object, auxdata);
	cachefiles_end_secure(cache, saved_cred);
	kमुक्त(auxdata);
	_leave("");
पूर्ण

/*
 * discard the resources pinned by an object and effect retirement अगर
 * requested
 */
अटल व्योम cachefiles_drop_object(काष्ठा fscache_object *_object)
अणु
	काष्ठा cachefiles_object *object;
	काष्ठा cachefiles_cache *cache;
	स्थिर काष्ठा cred *saved_cred;
	काष्ठा inode *inode;
	blkcnt_t i_blocks = 0;

	ASSERT(_object);

	object = container_of(_object, काष्ठा cachefiles_object, fscache);

	_enter("{OBJ%x,%d}",
	       object->fscache.debug_id, atomic_पढ़ो(&object->usage));

	cache = container_of(object->fscache.cache,
			     काष्ठा cachefiles_cache, cache);

#अगर_घोषित CACHEखाताS_DEBUG_SLAB
	ASSERT((atomic_पढ़ो(&object->usage) & 0xffff0000) != 0x6b6b0000);
#पूर्ण_अगर

	/* We need to tidy the object up अगर we did in fact manage to खोलो it.
	 * It's possible क्रम us to get here beक्रमe the object is fully
	 * initialised अगर the parent goes away or the object माला_लो retired
	 * beक्रमe we set it up.
	 */
	अगर (object->dentry) अणु
		/* delete retired objects */
		अगर (test_bit(FSCACHE_OBJECT_RETIRED, &object->fscache.flags) &&
		    _object != cache->cache.fsdef
		    ) अणु
			_debug("- retire object OBJ%x", object->fscache.debug_id);
			inode = d_backing_inode(object->dentry);
			अगर (inode)
				i_blocks = inode->i_blocks;

			cachefiles_begin_secure(cache, &saved_cred);
			cachefiles_delete_object(cache, object);
			cachefiles_end_secure(cache, saved_cred);
		पूर्ण

		/* बंद the fileप्रणाली stuff attached to the object */
		अगर (object->backer != object->dentry)
			dput(object->backer);
		object->backer = शून्य;
	पूर्ण

	/* note that the object is now inactive */
	अगर (test_bit(CACHEखाताS_OBJECT_ACTIVE, &object->flags))
		cachefiles_mark_object_inactive(cache, object, i_blocks);

	dput(object->dentry);
	object->dentry = शून्य;

	_leave("");
पूर्ण

/*
 * dispose of a reference to an object
 */
व्योम cachefiles_put_object(काष्ठा fscache_object *_object,
			   क्रमागत fscache_obj_ref_trace why)
अणु
	काष्ठा cachefiles_object *object;
	काष्ठा fscache_cache *cache;
	पूर्णांक u;

	ASSERT(_object);

	object = container_of(_object, काष्ठा cachefiles_object, fscache);

	_enter("{OBJ%x,%d}",
	       object->fscache.debug_id, atomic_पढ़ो(&object->usage));

#अगर_घोषित CACHEखाताS_DEBUG_SLAB
	ASSERT((atomic_पढ़ो(&object->usage) & 0xffff0000) != 0x6b6b0000);
#पूर्ण_अगर

	ASSERTIFCMP(object->fscache.parent,
		    object->fscache.parent->n_children, >, 0);

	u = atomic_dec_वापस(&object->usage);
	trace_cachefiles_ref(object, _object->cookie,
			     (क्रमागत cachefiles_obj_ref_trace)why, u);
	ASSERTCMP(u, !=, -1);
	अगर (u == 0) अणु
		_debug("- kill object OBJ%x", object->fscache.debug_id);

		ASSERT(!test_bit(CACHEखाताS_OBJECT_ACTIVE, &object->flags));
		ASSERTCMP(object->fscache.parent, ==, शून्य);
		ASSERTCMP(object->backer, ==, शून्य);
		ASSERTCMP(object->dentry, ==, शून्य);
		ASSERTCMP(object->fscache.n_ops, ==, 0);
		ASSERTCMP(object->fscache.n_children, ==, 0);

		अगर (object->lookup_data) अणु
			kमुक्त(object->lookup_data->key);
			kमुक्त(object->lookup_data->auxdata);
			kमुक्त(object->lookup_data);
			object->lookup_data = शून्य;
		पूर्ण

		cache = object->fscache.cache;
		fscache_object_destroy(&object->fscache);
		kmem_cache_मुक्त(cachefiles_object_jar, object);
		fscache_object_destroyed(cache);
	पूर्ण

	_leave("");
पूर्ण

/*
 * sync a cache
 */
अटल व्योम cachefiles_sync_cache(काष्ठा fscache_cache *_cache)
अणु
	काष्ठा cachefiles_cache *cache;
	स्थिर काष्ठा cred *saved_cred;
	पूर्णांक ret;

	_enter("%p", _cache);

	cache = container_of(_cache, काष्ठा cachefiles_cache, cache);

	/* make sure all pages pinned by operations on behalf of the netfs are
	 * written to disc */
	cachefiles_begin_secure(cache, &saved_cred);
	करोwn_पढ़ो(&cache->mnt->mnt_sb->s_umount);
	ret = sync_fileप्रणाली(cache->mnt->mnt_sb);
	up_पढ़ो(&cache->mnt->mnt_sb->s_umount);
	cachefiles_end_secure(cache, saved_cred);

	अगर (ret == -EIO)
		cachefiles_io_error(cache,
				    "Attempt to sync backing fs superblock"
				    " returned error %d",
				    ret);
पूर्ण

/*
 * check अगर the backing cache is updated to FS-Cache
 * - called by FS-Cache when evaluates अगर need to invalidate the cache
 */
अटल पूर्णांक cachefiles_check_consistency(काष्ठा fscache_operation *op)
अणु
	काष्ठा cachefiles_object *object;
	काष्ठा cachefiles_cache *cache;
	स्थिर काष्ठा cred *saved_cred;
	पूर्णांक ret;

	_enter("{OBJ%x}", op->object->debug_id);

	object = container_of(op->object, काष्ठा cachefiles_object, fscache);
	cache = container_of(object->fscache.cache,
			     काष्ठा cachefiles_cache, cache);

	cachefiles_begin_secure(cache, &saved_cred);
	ret = cachefiles_check_auxdata(object);
	cachefiles_end_secure(cache, saved_cred);

	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * notअगरication the attributes on an object have changed
 * - called with पढ़ोs/ग_लिखोs excluded by FS-Cache
 */
अटल पूर्णांक cachefiles_attr_changed(काष्ठा fscache_object *_object)
अणु
	काष्ठा cachefiles_object *object;
	काष्ठा cachefiles_cache *cache;
	स्थिर काष्ठा cred *saved_cred;
	काष्ठा iattr newattrs;
	uपूर्णांक64_t ni_size;
	loff_t oi_size;
	पूर्णांक ret;

	ni_size = _object->store_limit_l;

	_enter("{OBJ%x},[%llu]",
	       _object->debug_id, (अचिन्हित दीर्घ दीर्घ) ni_size);

	object = container_of(_object, काष्ठा cachefiles_object, fscache);
	cache = container_of(object->fscache.cache,
			     काष्ठा cachefiles_cache, cache);

	अगर (ni_size == object->i_size)
		वापस 0;

	अगर (!object->backer)
		वापस -ENOBUFS;

	ASSERT(d_is_reg(object->backer));

	fscache_set_store_limit(&object->fscache, ni_size);

	oi_size = i_size_पढ़ो(d_backing_inode(object->backer));
	अगर (oi_size == ni_size)
		वापस 0;

	cachefiles_begin_secure(cache, &saved_cred);
	inode_lock(d_inode(object->backer));

	/* अगर there's an extension to a partial page at the end of the backing
	 * file, we need to discard the partial page so that we pick up new
	 * data after it */
	अगर (oi_size & ~PAGE_MASK && ni_size > oi_size) अणु
		_debug("discard tail %llx", oi_size);
		newattrs.ia_valid = ATTR_SIZE;
		newattrs.ia_size = oi_size & PAGE_MASK;
		ret = notअगरy_change(&init_user_ns, object->backer, &newattrs, शून्य);
		अगर (ret < 0)
			जाओ truncate_failed;
	पूर्ण

	newattrs.ia_valid = ATTR_SIZE;
	newattrs.ia_size = ni_size;
	ret = notअगरy_change(&init_user_ns, object->backer, &newattrs, शून्य);

truncate_failed:
	inode_unlock(d_inode(object->backer));
	cachefiles_end_secure(cache, saved_cred);

	अगर (ret == -EIO) अणु
		fscache_set_store_limit(&object->fscache, 0);
		cachefiles_io_error_obj(object, "Size set failed");
		ret = -ENOBUFS;
	पूर्ण

	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Invalidate an object
 */
अटल व्योम cachefiles_invalidate_object(काष्ठा fscache_operation *op)
अणु
	काष्ठा cachefiles_object *object;
	काष्ठा cachefiles_cache *cache;
	स्थिर काष्ठा cred *saved_cred;
	काष्ठा path path;
	uपूर्णांक64_t ni_size;
	पूर्णांक ret;

	object = container_of(op->object, काष्ठा cachefiles_object, fscache);
	cache = container_of(object->fscache.cache,
			     काष्ठा cachefiles_cache, cache);

	ni_size = op->object->store_limit_l;

	_enter("{OBJ%x},[%llu]",
	       op->object->debug_id, (अचिन्हित दीर्घ दीर्घ)ni_size);

	अगर (object->backer) अणु
		ASSERT(d_is_reg(object->backer));

		fscache_set_store_limit(&object->fscache, ni_size);

		path.dentry = object->backer;
		path.mnt = cache->mnt;

		cachefiles_begin_secure(cache, &saved_cred);
		ret = vfs_truncate(&path, 0);
		अगर (ret == 0)
			ret = vfs_truncate(&path, ni_size);
		cachefiles_end_secure(cache, saved_cred);

		अगर (ret != 0) अणु
			fscache_set_store_limit(&object->fscache, 0);
			अगर (ret == -EIO)
				cachefiles_io_error_obj(object,
							"Invalidate failed");
		पूर्ण
	पूर्ण

	fscache_op_complete(op, true);
	_leave("");
पूर्ण

/*
 * dissociate a cache from all the pages it was backing
 */
अटल व्योम cachefiles_dissociate_pages(काष्ठा fscache_cache *cache)
अणु
	_enter("");
पूर्ण

स्थिर काष्ठा fscache_cache_ops cachefiles_cache_ops = अणु
	.name			= "cachefiles",
	.alloc_object		= cachefiles_alloc_object,
	.lookup_object		= cachefiles_lookup_object,
	.lookup_complete	= cachefiles_lookup_complete,
	.grab_object		= cachefiles_grab_object,
	.update_object		= cachefiles_update_object,
	.invalidate_object	= cachefiles_invalidate_object,
	.drop_object		= cachefiles_drop_object,
	.put_object		= cachefiles_put_object,
	.sync_cache		= cachefiles_sync_cache,
	.attr_changed		= cachefiles_attr_changed,
	.पढ़ो_or_alloc_page	= cachefiles_पढ़ो_or_alloc_page,
	.पढ़ो_or_alloc_pages	= cachefiles_पढ़ो_or_alloc_pages,
	.allocate_page		= cachefiles_allocate_page,
	.allocate_pages		= cachefiles_allocate_pages,
	.ग_लिखो_page		= cachefiles_ग_लिखो_page,
	.uncache_page		= cachefiles_uncache_page,
	.dissociate_pages	= cachefiles_dissociate_pages,
	.check_consistency	= cachefiles_check_consistency,
	.begin_पढ़ो_operation	= cachefiles_begin_पढ़ो_operation,
पूर्ण;
