<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* General fileप्रणाली caching पूर्णांकerface
 *
 * Copyright (C) 2004-2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * NOTE!!! See:
 *
 *	Documentation/fileप्रणालीs/caching/netfs-api.rst
 *
 * क्रम a description of the network fileप्रणाली पूर्णांकerface declared here.
 */

#अगर_अघोषित _LINUX_FSCACHE_H
#घोषणा _LINUX_FSCACHE_H

#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/list_bl.h>
#समावेश <linux/netfs.h>

#अगर defined(CONFIG_FSCACHE) || defined(CONFIG_FSCACHE_MODULE)
#घोषणा fscache_available() (1)
#घोषणा fscache_cookie_valid(cookie) (cookie)
#अन्यथा
#घोषणा fscache_available() (0)
#घोषणा fscache_cookie_valid(cookie) (0)
#पूर्ण_अगर


/* pattern used to fill dead space in an index entry */
#घोषणा FSCACHE_INDEX_DEADFILL_PATTERN 0x79

काष्ठा pagevec;
काष्ठा fscache_cache_tag;
काष्ठा fscache_cookie;
काष्ठा fscache_netfs;
काष्ठा netfs_पढ़ो_request;

प्रकार व्योम (*fscache_rw_complete_t)(काष्ठा page *page,
				      व्योम *context,
				      पूर्णांक error);

/* result of index entry consultation */
क्रमागत fscache_checkaux अणु
	FSCACHE_CHECKAUX_OKAY,		/* entry okay as is */
	FSCACHE_CHECKAUX_NEEDS_UPDATE,	/* entry requires update */
	FSCACHE_CHECKAUX_OBSOLETE,	/* entry requires deletion */
पूर्ण;

/*
 * fscache cookie definition
 */
काष्ठा fscache_cookie_def अणु
	/* name of cookie type */
	अक्षर name[16];

	/* cookie type */
	uपूर्णांक8_t type;
#घोषणा FSCACHE_COOKIE_TYPE_INDEX	0
#घोषणा FSCACHE_COOKIE_TYPE_DATAखाता	1

	/* select the cache पूर्णांकo which to insert an entry in this index
	 * - optional
	 * - should वापस a cache identअगरier or शून्य to cause the cache to be
	 *   inherited from the parent अगर possible or the first cache picked
	 *   क्रम a non-index file अगर not
	 */
	काष्ठा fscache_cache_tag *(*select_cache)(
		स्थिर व्योम *parent_netfs_data,
		स्थिर व्योम *cookie_netfs_data);

	/* consult the netfs about the state of an object
	 * - this function can be असलent अगर the index carries no state data
	 * - the netfs data from the cookie being used as the target is
	 *   presented, as is the auxiliary data and the object size
	 */
	क्रमागत fscache_checkaux (*check_aux)(व्योम *cookie_netfs_data,
					   स्थिर व्योम *data,
					   uपूर्णांक16_t datalen,
					   loff_t object_size);

	/* get an extra reference on a पढ़ो context
	 * - this function can be असलent अगर the completion function करोesn't
	 *   require a context
	 */
	व्योम (*get_context)(व्योम *cookie_netfs_data, व्योम *context);

	/* release an extra reference on a पढ़ो context
	 * - this function can be असलent अगर the completion function करोesn't
	 *   require a context
	 */
	व्योम (*put_context)(व्योम *cookie_netfs_data, व्योम *context);

	/* indicate page that now have cache metadata retained
	 * - this function should mark the specअगरied page as now being cached
	 * - the page will have been marked with PG_fscache beक्रमe this is
	 *   called, so this is optional
	 */
	व्योम (*mark_page_cached)(व्योम *cookie_netfs_data,
				 काष्ठा address_space *mapping,
				 काष्ठा page *page);
पूर्ण;

/*
 * fscache cached network fileप्रणाली type
 * - name, version and ops must be filled in beक्रमe registration
 * - all other fields will be set during registration
 */
काष्ठा fscache_netfs अणु
	uपूर्णांक32_t			version;	/* indexing version */
	स्थिर अक्षर			*name;		/* fileप्रणाली name */
	काष्ठा fscache_cookie		*primary_index;
पूर्ण;

/*
 * data file or index object cookie
 * - a file will only appear in one cache
 * - a request to cache a file may or may not be honoured, subject to
 *   स्थिरraपूर्णांकs such as disk space
 * - indices are created on disk just-in-समय
 */
काष्ठा fscache_cookie अणु
	atomic_t			usage;		/* number of users of this cookie */
	atomic_t			n_children;	/* number of children of this cookie */
	atomic_t			n_active;	/* number of active users of netfs ptrs */
	spinlock_t			lock;
	spinlock_t			stores_lock;	/* lock on page store tree */
	काष्ठा hlist_head		backing_objects; /* object(s) backing this file/index */
	स्थिर काष्ठा fscache_cookie_def	*def;		/* definition */
	काष्ठा fscache_cookie		*parent;	/* parent of this entry */
	काष्ठा hlist_bl_node		hash_link;	/* Link in hash table */
	व्योम				*netfs_data;	/* back poपूर्णांकer to netfs */
	काष्ठा radix_tree_root		stores;		/* pages to be stored on this cookie */
#घोषणा FSCACHE_COOKIE_PENDING_TAG	0		/* pages tag: pending ग_लिखो to cache */
#घोषणा FSCACHE_COOKIE_STORING_TAG	1		/* pages tag: writing to cache */

	अचिन्हित दीर्घ			flags;
#घोषणा FSCACHE_COOKIE_LOOKING_UP	0	/* T अगर non-index cookie being looked up still */
#घोषणा FSCACHE_COOKIE_NO_DATA_YET	1	/* T अगर new object with no cached data yet */
#घोषणा FSCACHE_COOKIE_UNAVAILABLE	2	/* T अगर cookie is unavailable (error, etc) */
#घोषणा FSCACHE_COOKIE_INVALIDATING	3	/* T अगर cookie is being invalidated */
#घोषणा FSCACHE_COOKIE_RELINQUISHED	4	/* T अगर cookie has been relinquished */
#घोषणा FSCACHE_COOKIE_ENABLED		5	/* T अगर cookie is enabled */
#घोषणा FSCACHE_COOKIE_ENABLEMENT_LOCK	6	/* T अगर cookie is being en/disabled */
#घोषणा FSCACHE_COOKIE_AUX_UPDATED	8	/* T अगर the auxiliary data was updated */
#घोषणा FSCACHE_COOKIE_ACQUIRED		9	/* T अगर cookie is in use */
#घोषणा FSCACHE_COOKIE_RELINQUISHING	10	/* T अगर cookie is being relinquished */

	u8				type;		/* Type of object */
	u8				key_len;	/* Length of index key */
	u8				aux_len;	/* Length of auxiliary data */
	u32				key_hash;	/* Hash of parent, type, key, len */
	जोड़ अणु
		व्योम			*key;		/* Index key */
		u8			अंतरभूत_key[16];	/* - If the key is लघु enough */
	पूर्ण;
	जोड़ अणु
		व्योम			*aux;		/* Auxiliary data */
		u8			अंतरभूत_aux[8];	/* - If the aux data is लघु enough */
	पूर्ण;
पूर्ण;

अटल अंतरभूत bool fscache_cookie_enabled(काष्ठा fscache_cookie *cookie)
अणु
	वापस test_bit(FSCACHE_COOKIE_ENABLED, &cookie->flags);
पूर्ण

/*
 * slow-path functions क्रम when there is actually caching available, and the
 * netfs करोes actually have a valid token
 * - these are not to be called directly
 * - these are undefined symbols when FS-Cache is not configured and the
 *   optimiser takes care of not using them
 */
बाह्य पूर्णांक __fscache_रेजिस्टर_netfs(काष्ठा fscache_netfs *);
बाह्य व्योम __fscache_unरेजिस्टर_netfs(काष्ठा fscache_netfs *);
बाह्य काष्ठा fscache_cache_tag *__fscache_lookup_cache_tag(स्थिर अक्षर *);
बाह्य व्योम __fscache_release_cache_tag(काष्ठा fscache_cache_tag *);

बाह्य काष्ठा fscache_cookie *__fscache_acquire_cookie(
	काष्ठा fscache_cookie *,
	स्थिर काष्ठा fscache_cookie_def *,
	स्थिर व्योम *, माप_प्रकार,
	स्थिर व्योम *, माप_प्रकार,
	व्योम *, loff_t, bool);
बाह्य व्योम __fscache_relinquish_cookie(काष्ठा fscache_cookie *, स्थिर व्योम *, bool);
बाह्य पूर्णांक __fscache_check_consistency(काष्ठा fscache_cookie *, स्थिर व्योम *);
बाह्य व्योम __fscache_update_cookie(काष्ठा fscache_cookie *, स्थिर व्योम *);
बाह्य पूर्णांक __fscache_attr_changed(काष्ठा fscache_cookie *);
बाह्य व्योम __fscache_invalidate(काष्ठा fscache_cookie *);
बाह्य व्योम __fscache_रुको_on_invalidate(काष्ठा fscache_cookie *);

#अगर_घोषित FSCACHE_USE_NEW_IO_API
बाह्य पूर्णांक __fscache_begin_पढ़ो_operation(काष्ठा netfs_पढ़ो_request *, काष्ठा fscache_cookie *);
#अन्यथा
बाह्य पूर्णांक __fscache_पढ़ो_or_alloc_page(काष्ठा fscache_cookie *,
					काष्ठा page *,
					fscache_rw_complete_t,
					व्योम *,
					gfp_t);
बाह्य पूर्णांक __fscache_पढ़ो_or_alloc_pages(काष्ठा fscache_cookie *,
					 काष्ठा address_space *,
					 काष्ठा list_head *,
					 अचिन्हित *,
					 fscache_rw_complete_t,
					 व्योम *,
					 gfp_t);
बाह्य पूर्णांक __fscache_alloc_page(काष्ठा fscache_cookie *, काष्ठा page *, gfp_t);
बाह्य पूर्णांक __fscache_ग_लिखो_page(काष्ठा fscache_cookie *, काष्ठा page *, loff_t, gfp_t);
बाह्य व्योम __fscache_uncache_page(काष्ठा fscache_cookie *, काष्ठा page *);
बाह्य bool __fscache_check_page_ग_लिखो(काष्ठा fscache_cookie *, काष्ठा page *);
बाह्य व्योम __fscache_रुको_on_page_ग_लिखो(काष्ठा fscache_cookie *, काष्ठा page *);
बाह्य bool __fscache_maybe_release_page(काष्ठा fscache_cookie *, काष्ठा page *,
					 gfp_t);
बाह्य व्योम __fscache_uncache_all_inode_pages(काष्ठा fscache_cookie *,
					      काष्ठा inode *);
बाह्य व्योम __fscache_पढ़ोpages_cancel(काष्ठा fscache_cookie *cookie,
				       काष्ठा list_head *pages);
#पूर्ण_अगर /* FSCACHE_USE_NEW_IO_API */

बाह्य व्योम __fscache_disable_cookie(काष्ठा fscache_cookie *, स्थिर व्योम *, bool);
बाह्य व्योम __fscache_enable_cookie(काष्ठा fscache_cookie *, स्थिर व्योम *, loff_t,
				    bool (*)(व्योम *), व्योम *);

/**
 * fscache_रेजिस्टर_netfs - Register a fileप्रणाली as desiring caching services
 * @netfs: The description of the fileप्रणाली
 *
 * Register a fileप्रणाली as desiring caching services अगर they're available.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
पूर्णांक fscache_रेजिस्टर_netfs(काष्ठा fscache_netfs *netfs)
अणु
	अगर (fscache_available())
		वापस __fscache_रेजिस्टर_netfs(netfs);
	अन्यथा
		वापस 0;
पूर्ण

/**
 * fscache_unरेजिस्टर_netfs - Indicate that a fileप्रणाली no दीर्घer desires
 * caching services
 * @netfs: The description of the fileप्रणाली
 *
 * Indicate that a fileप्रणाली no दीर्घer desires caching services क्रम the
 * moment.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
व्योम fscache_unरेजिस्टर_netfs(काष्ठा fscache_netfs *netfs)
अणु
	अगर (fscache_available())
		__fscache_unरेजिस्टर_netfs(netfs);
पूर्ण

/**
 * fscache_lookup_cache_tag - Look up a cache tag
 * @name: The name of the tag to search क्रम
 *
 * Acquire a specअगरic cache referral tag that can be used to select a specअगरic
 * cache in which to cache an index.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
काष्ठा fscache_cache_tag *fscache_lookup_cache_tag(स्थिर अक्षर *name)
अणु
	अगर (fscache_available())
		वापस __fscache_lookup_cache_tag(name);
	अन्यथा
		वापस शून्य;
पूर्ण

/**
 * fscache_release_cache_tag - Release a cache tag
 * @tag: The tag to release
 *
 * Release a reference to a cache referral tag previously looked up.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
व्योम fscache_release_cache_tag(काष्ठा fscache_cache_tag *tag)
अणु
	अगर (fscache_available())
		__fscache_release_cache_tag(tag);
पूर्ण

/**
 * fscache_acquire_cookie - Acquire a cookie to represent a cache object
 * @parent: The cookie that's to be the parent of this one
 * @def: A description of the cache object, including callback operations
 * @index_key: The index key क्रम this cookie
 * @index_key_len: Size of the index key
 * @aux_data: The auxiliary data क्रम the cookie (may be शून्य)
 * @aux_data_len: Size of the auxiliary data buffer
 * @netfs_data: An arbitrary piece of data to be kept in the cookie to
 * represent the cache object to the netfs
 * @object_size: The initial size of object
 * @enable: Whether or not to enable a data cookie immediately
 *
 * This function is used to inक्रमm FS-Cache about part of an index hierarchy
 * that can be used to locate files.  This is करोne by requesting a cookie क्रम
 * each index in the path to the file.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
काष्ठा fscache_cookie *fscache_acquire_cookie(
	काष्ठा fscache_cookie *parent,
	स्थिर काष्ठा fscache_cookie_def *def,
	स्थिर व्योम *index_key,
	माप_प्रकार index_key_len,
	स्थिर व्योम *aux_data,
	माप_प्रकार aux_data_len,
	व्योम *netfs_data,
	loff_t object_size,
	bool enable)
अणु
	अगर (fscache_cookie_valid(parent) && fscache_cookie_enabled(parent))
		वापस __fscache_acquire_cookie(parent, def,
						index_key, index_key_len,
						aux_data, aux_data_len,
						netfs_data, object_size, enable);
	अन्यथा
		वापस शून्य;
पूर्ण

/**
 * fscache_relinquish_cookie - Return the cookie to the cache, maybe discarding
 * it
 * @cookie: The cookie being वापसed
 * @aux_data: The updated auxiliary data क्रम the cookie (may be शून्य)
 * @retire: True अगर the cache object the cookie represents is to be discarded
 *
 * This function वापसs a cookie to the cache, क्रमcibly discarding the
 * associated cache object अगर retire is set to true.  The opportunity is
 * provided to update the auxiliary data in the cache beक्रमe the object is
 * disconnected.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
व्योम fscache_relinquish_cookie(काष्ठा fscache_cookie *cookie,
			       स्थिर व्योम *aux_data,
			       bool retire)
अणु
	अगर (fscache_cookie_valid(cookie))
		__fscache_relinquish_cookie(cookie, aux_data, retire);
पूर्ण

/**
 * fscache_check_consistency - Request validation of a cache's auxiliary data
 * @cookie: The cookie representing the cache object
 * @aux_data: The updated auxiliary data क्रम the cookie (may be शून्य)
 *
 * Request an consistency check from fscache, which passes the request to the
 * backing cache.  The auxiliary data on the cookie will be updated first अगर
 * @aux_data is set.
 *
 * Returns 0 अगर consistent and -ESTALE अगर inconsistent.  May also
 * वापस -ENOMEM and -ERESTARTSYS.
 */
अटल अंतरभूत
पूर्णांक fscache_check_consistency(काष्ठा fscache_cookie *cookie,
			      स्थिर व्योम *aux_data)
अणु
	अगर (fscache_cookie_valid(cookie) && fscache_cookie_enabled(cookie))
		वापस __fscache_check_consistency(cookie, aux_data);
	अन्यथा
		वापस 0;
पूर्ण

/**
 * fscache_update_cookie - Request that a cache object be updated
 * @cookie: The cookie representing the cache object
 * @aux_data: The updated auxiliary data क्रम the cookie (may be शून्य)
 *
 * Request an update of the index data क्रम the cache object associated with the
 * cookie.  The auxiliary data on the cookie will be updated first अगर @aux_data
 * is set.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
व्योम fscache_update_cookie(काष्ठा fscache_cookie *cookie, स्थिर व्योम *aux_data)
अणु
	अगर (fscache_cookie_valid(cookie) && fscache_cookie_enabled(cookie))
		__fscache_update_cookie(cookie, aux_data);
पूर्ण

/**
 * fscache_pin_cookie - Pin a data-storage cache object in its cache
 * @cookie: The cookie representing the cache object
 *
 * Permit data-storage cache objects to be pinned in the cache.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
पूर्णांक fscache_pin_cookie(काष्ठा fscache_cookie *cookie)
अणु
	वापस -ENOBUFS;
पूर्ण

/**
 * fscache_pin_cookie - Unpin a data-storage cache object in its cache
 * @cookie: The cookie representing the cache object
 *
 * Permit data-storage cache objects to be unpinned from the cache.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
व्योम fscache_unpin_cookie(काष्ठा fscache_cookie *cookie)
अणु
पूर्ण

/**
 * fscache_attr_changed - Notअगरy cache that an object's attributes changed
 * @cookie: The cookie representing the cache object
 *
 * Send a notअगरication to the cache indicating that an object's attributes have
 * changed.  This includes the data size.  These attributes will be obtained
 * through the get_attr() cookie definition op.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
पूर्णांक fscache_attr_changed(काष्ठा fscache_cookie *cookie)
अणु
	अगर (fscache_cookie_valid(cookie) && fscache_cookie_enabled(cookie))
		वापस __fscache_attr_changed(cookie);
	अन्यथा
		वापस -ENOBUFS;
पूर्ण

/**
 * fscache_invalidate - Notअगरy cache that an object needs invalidation
 * @cookie: The cookie representing the cache object
 *
 * Notअगरy the cache that an object is needs to be invalidated and that it
 * should पात any retrievals or stores it is करोing on the cache.  The object
 * is then marked non-caching until such समय as the invalidation is complete.
 *
 * This can be called with spinlocks held.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
व्योम fscache_invalidate(काष्ठा fscache_cookie *cookie)
अणु
	अगर (fscache_cookie_valid(cookie) && fscache_cookie_enabled(cookie))
		__fscache_invalidate(cookie);
पूर्ण

/**
 * fscache_रुको_on_invalidate - Wait क्रम invalidation to complete
 * @cookie: The cookie representing the cache object
 *
 * Wait क्रम the invalidation of an object to complete.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
व्योम fscache_रुको_on_invalidate(काष्ठा fscache_cookie *cookie)
अणु
	अगर (fscache_cookie_valid(cookie))
		__fscache_रुको_on_invalidate(cookie);
पूर्ण

/**
 * fscache_reserve_space - Reserve data space क्रम a cached object
 * @cookie: The cookie representing the cache object
 * @i_size: The amount of space to be reserved
 *
 * Reserve an amount of space in the cache क्रम the cache object attached to a
 * cookie so that a ग_लिखो to that object within the space can always be
 * honoured.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
पूर्णांक fscache_reserve_space(काष्ठा fscache_cookie *cookie, loff_t size)
अणु
	वापस -ENOBUFS;
पूर्ण

#अगर_घोषित FSCACHE_USE_NEW_IO_API

/**
 * fscache_begin_पढ़ो_operation - Begin a पढ़ो operation क्रम the netfs lib
 * @rreq: The पढ़ो request being undertaken
 * @cookie: The cookie representing the cache object
 *
 * Begin a पढ़ो operation on behalf of the netfs helper library.  @rreq
 * indicates the पढ़ो request to which the operation state should be attached;
 * @cookie indicates the cache object that will be accessed.
 *
 * This is पूर्णांकended to be called from the ->begin_cache_operation() netfs lib
 * operation as implemented by the network fileप्रणाली.
 *
 * Returns:
 * * 0		- Success
 * * -ENOBUFS	- No caching available
 * * Other error code from the cache, such as -ENOMEM.
 */
अटल अंतरभूत
पूर्णांक fscache_begin_पढ़ो_operation(काष्ठा netfs_पढ़ो_request *rreq,
				 काष्ठा fscache_cookie *cookie)
अणु
	अगर (fscache_cookie_valid(cookie) && fscache_cookie_enabled(cookie))
		वापस __fscache_begin_पढ़ो_operation(rreq, cookie);
	वापस -ENOBUFS;
पूर्ण

#अन्यथा /* FSCACHE_USE_NEW_IO_API */

/**
 * fscache_पढ़ो_or_alloc_page - Read a page from the cache or allocate a block
 * in which to store it
 * @cookie: The cookie representing the cache object
 * @page: The netfs page to fill अगर possible
 * @end_io_func: The callback to invoke when and अगर the page is filled
 * @context: An arbitrary piece of data to pass on to end_io_func()
 * @gfp: The conditions under which memory allocation should be made
 *
 * Read a page from the cache, or अगर that's not possible make a potential
 * one-block reservation in the cache पूर्णांकo which the page may be stored once
 * fetched from the server.
 *
 * If the page is not backed by the cache object, or अगर it there's some reason
 * it can't be, -ENOBUFS will be वापसed and nothing more will be करोne क्रम
 * that page.
 *
 * Else, अगर that page is backed by the cache, a पढ़ो will be initiated directly
 * to the netfs's page and 0 will be वापसed by this function.  The
 * end_io_func() callback will be invoked when the operation terminates on a
 * completion or failure.  Note that the callback may be invoked beक्रमe the
 * वापस.
 *
 * Else, अगर the page is unbacked, -ENODATA is वापसed and a block may have
 * been allocated in the cache.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
पूर्णांक fscache_पढ़ो_or_alloc_page(काष्ठा fscache_cookie *cookie,
			       काष्ठा page *page,
			       fscache_rw_complete_t end_io_func,
			       व्योम *context,
			       gfp_t gfp)
अणु
	अगर (fscache_cookie_valid(cookie) && fscache_cookie_enabled(cookie))
		वापस __fscache_पढ़ो_or_alloc_page(cookie, page, end_io_func,
						    context, gfp);
	अन्यथा
		वापस -ENOBUFS;
पूर्ण

/**
 * fscache_पढ़ो_or_alloc_pages - Read pages from the cache and/or allocate
 * blocks in which to store them
 * @cookie: The cookie representing the cache object
 * @mapping: The netfs inode mapping to which the pages will be attached
 * @pages: A list of potential netfs pages to be filled
 * @nr_pages: Number of pages to be पढ़ो and/or allocated
 * @end_io_func: The callback to invoke when and अगर each page is filled
 * @context: An arbitrary piece of data to pass on to end_io_func()
 * @gfp: The conditions under which memory allocation should be made
 *
 * Read a set of pages from the cache, or अगर that's not possible, attempt to
 * make a potential one-block reservation क्रम each page in the cache पूर्णांकo which
 * that page may be stored once fetched from the server.
 *
 * If some pages are not backed by the cache object, or अगर it there's some
 * reason they can't be, -ENOBUFS will be वापसed and nothing more will be
 * करोne क्रम that pages.
 *
 * Else, अगर some of the pages are backed by the cache, a पढ़ो will be initiated
 * directly to the netfs's page and 0 will be वापसed by this function.  The
 * end_io_func() callback will be invoked when the operation terminates on a
 * completion or failure.  Note that the callback may be invoked beक्रमe the
 * वापस.
 *
 * Else, अगर a page is unbacked, -ENODATA is वापसed and a block may have
 * been allocated in the cache.
 *
 * Because the function may want to वापस all of -ENOBUFS, -ENODATA and 0 in
 * regard to dअगरferent pages, the वापस values are prioritised in that order.
 * Any pages submitted क्रम पढ़ोing are हटाओd from the pages list.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
पूर्णांक fscache_पढ़ो_or_alloc_pages(काष्ठा fscache_cookie *cookie,
				काष्ठा address_space *mapping,
				काष्ठा list_head *pages,
				अचिन्हित *nr_pages,
				fscache_rw_complete_t end_io_func,
				व्योम *context,
				gfp_t gfp)
अणु
	अगर (fscache_cookie_valid(cookie) && fscache_cookie_enabled(cookie))
		वापस __fscache_पढ़ो_or_alloc_pages(cookie, mapping, pages,
						     nr_pages, end_io_func,
						     context, gfp);
	अन्यथा
		वापस -ENOBUFS;
पूर्ण

/**
 * fscache_alloc_page - Allocate a block in which to store a page
 * @cookie: The cookie representing the cache object
 * @page: The netfs page to allocate a page क्रम
 * @gfp: The conditions under which memory allocation should be made
 *
 * Request Allocation a block in the cache in which to store a netfs page
 * without retrieving any contents from the cache.
 *
 * If the page is not backed by a file then -ENOBUFS will be वापसed and
 * nothing more will be करोne, and no reservation will be made.
 *
 * Else, a block will be allocated अगर one wasn't alपढ़ोy, and 0 will be
 * वापसed
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
पूर्णांक fscache_alloc_page(काष्ठा fscache_cookie *cookie,
		       काष्ठा page *page,
		       gfp_t gfp)
अणु
	अगर (fscache_cookie_valid(cookie) && fscache_cookie_enabled(cookie))
		वापस __fscache_alloc_page(cookie, page, gfp);
	अन्यथा
		वापस -ENOBUFS;
पूर्ण

/**
 * fscache_पढ़ोpages_cancel - Cancel पढ़ो/alloc on pages
 * @cookie: The cookie representing the inode's cache object.
 * @pages: The netfs pages that we canceled ग_लिखो on in पढ़ोpages()
 *
 * Uncache/unreserve the pages reserved earlier in पढ़ोpages() via
 * fscache_पढ़ोpages_or_alloc() and similar.  In most successful caches in
 * पढ़ोpages() this करोesn't do anything.  In cases when the underlying netfs's
 * पढ़ोahead failed we need to clean up the pagelist (unmark and uncache).
 *
 * This function may sleep as it may have to clean up disk state.
 */
अटल अंतरभूत
व्योम fscache_पढ़ोpages_cancel(काष्ठा fscache_cookie *cookie,
			      काष्ठा list_head *pages)
अणु
	अगर (fscache_cookie_valid(cookie))
		__fscache_पढ़ोpages_cancel(cookie, pages);
पूर्ण

/**
 * fscache_ग_लिखो_page - Request storage of a page in the cache
 * @cookie: The cookie representing the cache object
 * @page: The netfs page to store
 * @object_size: Updated size of object
 * @gfp: The conditions under which memory allocation should be made
 *
 * Request the contents of the netfs page be written पूर्णांकo the cache.  This
 * request may be ignored अगर no cache block is currently allocated, in which
 * हाल it will वापस -ENOBUFS.
 *
 * If a cache block was alपढ़ोy allocated, a ग_लिखो will be initiated and 0 will
 * be वापसed.  The PG_fscache_ग_लिखो page bit is set immediately and will then
 * be cleared at the completion of the ग_लिखो to indicate the success or failure
 * of the operation.  Note that the completion may happen beक्रमe the वापस.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
पूर्णांक fscache_ग_लिखो_page(काष्ठा fscache_cookie *cookie,
		       काष्ठा page *page,
		       loff_t object_size,
		       gfp_t gfp)
अणु
	अगर (fscache_cookie_valid(cookie) && fscache_cookie_enabled(cookie))
		वापस __fscache_ग_लिखो_page(cookie, page, object_size, gfp);
	अन्यथा
		वापस -ENOBUFS;
पूर्ण

/**
 * fscache_uncache_page - Indicate that caching is no दीर्घer required on a page
 * @cookie: The cookie representing the cache object
 * @page: The netfs page that was being cached.
 *
 * Tell the cache that we no दीर्घer want a page to be cached and that it should
 * हटाओ any knowledge of the netfs page it may have.
 *
 * Note that this cannot cancel any outstanding I/O operations between this
 * page and the cache.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
व्योम fscache_uncache_page(काष्ठा fscache_cookie *cookie,
			  काष्ठा page *page)
अणु
	अगर (fscache_cookie_valid(cookie))
		__fscache_uncache_page(cookie, page);
पूर्ण

/**
 * fscache_check_page_ग_लिखो - Ask अगर a page is being writing to the cache
 * @cookie: The cookie representing the cache object
 * @page: The netfs page that is being cached.
 *
 * Ask the cache अगर a page is being written to the cache.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
bool fscache_check_page_ग_लिखो(काष्ठा fscache_cookie *cookie,
			      काष्ठा page *page)
अणु
	अगर (fscache_cookie_valid(cookie))
		वापस __fscache_check_page_ग_लिखो(cookie, page);
	वापस false;
पूर्ण

/**
 * fscache_रुको_on_page_ग_लिखो - Wait क्रम a page to complete writing to the cache
 * @cookie: The cookie representing the cache object
 * @page: The netfs page that is being cached.
 *
 * Ask the cache to wake us up when a page is no दीर्घer being written to the
 * cache.
 *
 * See Documentation/fileप्रणालीs/caching/netfs-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
व्योम fscache_रुको_on_page_ग_लिखो(काष्ठा fscache_cookie *cookie,
				काष्ठा page *page)
अणु
	अगर (fscache_cookie_valid(cookie))
		__fscache_रुको_on_page_ग_लिखो(cookie, page);
पूर्ण

/**
 * fscache_maybe_release_page - Consider releasing a page, cancelling a store
 * @cookie: The cookie representing the cache object
 * @page: The netfs page that is being cached.
 * @gfp: The gfp flags passed to releasepage()
 *
 * Consider releasing a page क्रम the vmscan algorithm, on behalf of the netfs's
 * releasepage() call.  A storage request on the page may cancelled अगर it is
 * not currently being processed.
 *
 * The function वापसs true अगर the page no दीर्घer has a storage request on it,
 * and false अगर a storage request is left in place.  If true is वापसed, the
 * page will have been passed to fscache_uncache_page().  If false is वापसed
 * the page cannot be मुक्तd yet.
 */
अटल अंतरभूत
bool fscache_maybe_release_page(काष्ठा fscache_cookie *cookie,
				काष्ठा page *page,
				gfp_t gfp)
अणु
	अगर (fscache_cookie_valid(cookie) && PageFsCache(page))
		वापस __fscache_maybe_release_page(cookie, page, gfp);
	वापस true;
पूर्ण

/**
 * fscache_uncache_all_inode_pages - Uncache all an inode's pages
 * @cookie: The cookie representing the inode's cache object.
 * @inode: The inode to uncache pages from.
 *
 * Uncache all the pages in an inode that are marked PG_fscache, assuming them
 * to be associated with the given cookie.
 *
 * This function may sleep.  It will रुको क्रम pages that are being written out
 * and will रुको whilst the PG_fscache mark is हटाओd by the cache.
 */
अटल अंतरभूत
व्योम fscache_uncache_all_inode_pages(काष्ठा fscache_cookie *cookie,
				     काष्ठा inode *inode)
अणु
	अगर (fscache_cookie_valid(cookie))
		__fscache_uncache_all_inode_pages(cookie, inode);
पूर्ण

#पूर्ण_अगर /* FSCACHE_USE_NEW_IO_API */

/**
 * fscache_disable_cookie - Disable a cookie
 * @cookie: The cookie representing the cache object
 * @aux_data: The updated auxiliary data क्रम the cookie (may be शून्य)
 * @invalidate: Invalidate the backing object
 *
 * Disable a cookie from accepting further alloc, पढ़ो, ग_लिखो, invalidate,
 * update or acquire operations.  Outstanding operations can still be रुकोed
 * upon and pages can still be uncached and the cookie relinquished.
 *
 * This will not वापस until all outstanding operations have completed.
 *
 * If @invalidate is set, then the backing object will be invalidated and
 * detached, otherwise it will just be detached.
 *
 * If @aux_data is set, then auxiliary data will be updated from that.
 */
अटल अंतरभूत
व्योम fscache_disable_cookie(काष्ठा fscache_cookie *cookie,
			    स्थिर व्योम *aux_data,
			    bool invalidate)
अणु
	अगर (fscache_cookie_valid(cookie) && fscache_cookie_enabled(cookie))
		__fscache_disable_cookie(cookie, aux_data, invalidate);
पूर्ण

/**
 * fscache_enable_cookie - Reenable a cookie
 * @cookie: The cookie representing the cache object
 * @aux_data: The updated auxiliary data क्रम the cookie (may be शून्य)
 * @object_size: Current size of object
 * @can_enable: A function to permit enablement once lock is held
 * @data: Data क्रम can_enable()
 *
 * Reenable a previously disabled cookie, allowing it to accept further alloc,
 * पढ़ो, ग_लिखो, invalidate, update or acquire operations.  An attempt will be
 * made to immediately reattach the cookie to a backing object.  If @aux_data
 * is set, the auxiliary data attached to the cookie will be updated.
 *
 * The can_enable() function is called (अगर not शून्य) once the enablement lock
 * is held to rule on whether enablement is still permitted to go ahead.
 */
अटल अंतरभूत
व्योम fscache_enable_cookie(काष्ठा fscache_cookie *cookie,
			   स्थिर व्योम *aux_data,
			   loff_t object_size,
			   bool (*can_enable)(व्योम *data),
			   व्योम *data)
अणु
	अगर (fscache_cookie_valid(cookie) && !fscache_cookie_enabled(cookie))
		__fscache_enable_cookie(cookie, aux_data, object_size,
					can_enable, data);
पूर्ण

#पूर्ण_अगर /* _LINUX_FSCACHE_H */
