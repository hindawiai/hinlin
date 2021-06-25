<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* General fileप्रणाली caching backing cache पूर्णांकerface
 *
 * Copyright (C) 2004-2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * NOTE!!! See:
 *
 *	Documentation/fileप्रणालीs/caching/backend-api.rst
 *
 * क्रम a description of the cache backend पूर्णांकerface declared here.
 */

#अगर_अघोषित _LINUX_FSCACHE_CACHE_H
#घोषणा _LINUX_FSCACHE_CACHE_H

#समावेश <linux/fscache.h>
#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>

#घोषणा NR_MAXCACHES BITS_PER_LONG

काष्ठा fscache_cache;
काष्ठा fscache_cache_ops;
काष्ठा fscache_object;
काष्ठा fscache_operation;

क्रमागत fscache_obj_ref_trace अणु
	fscache_obj_get_add_to_deps,
	fscache_obj_get_queue,
	fscache_obj_put_alloc_fail,
	fscache_obj_put_attach_fail,
	fscache_obj_put_drop_obj,
	fscache_obj_put_enq_dep,
	fscache_obj_put_queue,
	fscache_obj_put_work,
	fscache_obj_ref__nr_traces
पूर्ण;

/*
 * cache tag definition
 */
काष्ठा fscache_cache_tag अणु
	काष्ठा list_head	link;
	काष्ठा fscache_cache	*cache;		/* cache referred to by this tag */
	अचिन्हित दीर्घ		flags;
#घोषणा FSCACHE_TAG_RESERVED	0		/* T अगर tag is reserved क्रम a cache */
	atomic_t		usage;
	अक्षर			name[];	/* tag name */
पूर्ण;

/*
 * cache definition
 */
काष्ठा fscache_cache अणु
	स्थिर काष्ठा fscache_cache_ops *ops;
	काष्ठा fscache_cache_tag *tag;		/* tag representing this cache */
	काष्ठा kobject		*kobj;		/* प्रणाली representation of this cache */
	काष्ठा list_head	link;		/* link in list of caches */
	माप_प्रकार			max_index_size;	/* maximum size of index data */
	अक्षर			identअगरier[36];	/* cache label */

	/* node management */
	काष्ठा work_काष्ठा	op_gc;		/* operation garbage collector */
	काष्ठा list_head	object_list;	/* list of data/index objects */
	काष्ठा list_head	op_gc_list;	/* list of ops to be deleted */
	spinlock_t		object_list_lock;
	spinlock_t		op_gc_list_lock;
	atomic_t		object_count;	/* no. of live objects in this cache */
	काष्ठा fscache_object	*fsdef;		/* object क्रम the fsdef index */
	अचिन्हित दीर्घ		flags;
#घोषणा FSCACHE_IOERROR		0	/* cache stopped on I/O error */
#घोषणा FSCACHE_CACHE_WITHDRAWN	1	/* cache has been withdrawn */
पूर्ण;

बाह्य रुको_queue_head_t fscache_cache_cleared_wq;

/*
 * operation to be applied to a cache object
 * - retrieval initiation operations are करोne in the context of the process
 *   that issued them, and not in an async thपढ़ो pool
 */
प्रकार व्योम (*fscache_operation_release_t)(काष्ठा fscache_operation *op);
प्रकार व्योम (*fscache_operation_processor_t)(काष्ठा fscache_operation *op);
प्रकार व्योम (*fscache_operation_cancel_t)(काष्ठा fscache_operation *op);

क्रमागत fscache_operation_state अणु
	FSCACHE_OP_ST_BLANK,		/* Op is not yet submitted */
	FSCACHE_OP_ST_INITIALISED,	/* Op is initialised */
	FSCACHE_OP_ST_PENDING,		/* Op is blocked from running */
	FSCACHE_OP_ST_IN_PROGRESS,	/* Op is in progress */
	FSCACHE_OP_ST_COMPLETE,		/* Op is complete */
	FSCACHE_OP_ST_CANCELLED,	/* Op has been cancelled */
	FSCACHE_OP_ST_DEAD		/* Op is now dead */
पूर्ण;

काष्ठा fscache_operation अणु
	काष्ठा work_काष्ठा	work;		/* record क्रम async ops */
	काष्ठा list_head	pend_link;	/* link in object->pending_ops */
	काष्ठा fscache_object	*object;	/* object to be operated upon */

	अचिन्हित दीर्घ		flags;
#घोषणा FSCACHE_OP_TYPE		0x000f	/* operation type */
#घोषणा FSCACHE_OP_ASYNC	0x0001	/* - async op, processor may sleep क्रम disk */
#घोषणा FSCACHE_OP_MYTHREAD	0x0002	/* - processing is करोne be issuing thपढ़ो, not pool */
#घोषणा FSCACHE_OP_WAITING	4	/* cleared when op is woken */
#घोषणा FSCACHE_OP_EXCLUSIVE	5	/* exclusive op, other ops must रुको */
#घोषणा FSCACHE_OP_DEC_READ_CNT	6	/* decrement object->n_पढ़ोs on deकाष्ठाion */
#घोषणा FSCACHE_OP_UNUSE_COOKIE	7	/* call fscache_unuse_cookie() on completion */
#घोषणा FSCACHE_OP_KEEP_FLAGS	0x00f0	/* flags to keep when repurposing an op */

	क्रमागत fscache_operation_state state;
	atomic_t		usage;
	अचिन्हित		debug_id;	/* debugging ID */

	/* operation processor callback
	 * - can be शून्य अगर FSCACHE_OP_WAITING is going to be used to perक्रमm
	 *   the op in a non-pool thपढ़ो */
	fscache_operation_processor_t processor;

	/* Operation cancellation cleanup (optional) */
	fscache_operation_cancel_t cancel;

	/* operation releaser */
	fscache_operation_release_t release;
पूर्ण;

बाह्य atomic_t fscache_op_debug_id;
बाह्य व्योम fscache_op_work_func(काष्ठा work_काष्ठा *work);

बाह्य व्योम fscache_enqueue_operation(काष्ठा fscache_operation *);
बाह्य व्योम fscache_op_complete(काष्ठा fscache_operation *, bool);
बाह्य व्योम fscache_put_operation(काष्ठा fscache_operation *);
बाह्य व्योम fscache_operation_init(काष्ठा fscache_cookie *,
				   काष्ठा fscache_operation *,
				   fscache_operation_processor_t,
				   fscache_operation_cancel_t,
				   fscache_operation_release_t);

/*
 * data पढ़ो operation
 */
काष्ठा fscache_retrieval अणु
	काष्ठा fscache_operation op;
	काष्ठा fscache_cookie	*cookie;	/* The netfs cookie */
	काष्ठा address_space	*mapping;	/* netfs pages */
	fscache_rw_complete_t	end_io_func;	/* function to call on I/O completion */
	व्योम			*context;	/* netfs पढ़ो context (pinned) */
	काष्ठा list_head	to_करो;		/* list of things to be करोne by the backend */
	अचिन्हित दीर्घ		start_समय;	/* समय at which retrieval started */
	atomic_t		n_pages;	/* number of pages to be retrieved */
पूर्ण;

प्रकार पूर्णांक (*fscache_page_retrieval_func_t)(काष्ठा fscache_retrieval *op,
					     काष्ठा page *page,
					     gfp_t gfp);

प्रकार पूर्णांक (*fscache_pages_retrieval_func_t)(काष्ठा fscache_retrieval *op,
					      काष्ठा list_head *pages,
					      अचिन्हित *nr_pages,
					      gfp_t gfp);

/**
 * fscache_get_retrieval - Get an extra reference on a retrieval operation
 * @op: The retrieval operation to get a reference on
 *
 * Get an extra reference on a retrieval operation.
 */
अटल अंतरभूत
काष्ठा fscache_retrieval *fscache_get_retrieval(काष्ठा fscache_retrieval *op)
अणु
	atomic_inc(&op->op.usage);
	वापस op;
पूर्ण

/**
 * fscache_enqueue_retrieval - Enqueue a retrieval operation क्रम processing
 * @op: The retrieval operation affected
 *
 * Enqueue a retrieval operation क्रम processing by the FS-Cache thपढ़ो pool.
 */
अटल अंतरभूत व्योम fscache_enqueue_retrieval(काष्ठा fscache_retrieval *op)
अणु
	fscache_enqueue_operation(&op->op);
पूर्ण

/**
 * fscache_retrieval_complete - Record (partial) completion of a retrieval
 * @op: The retrieval operation affected
 * @n_pages: The number of pages to account क्रम
 */
अटल अंतरभूत व्योम fscache_retrieval_complete(काष्ठा fscache_retrieval *op,
					      पूर्णांक n_pages)
अणु
	अगर (atomic_sub_वापस_relaxed(n_pages, &op->n_pages) <= 0)
		fscache_op_complete(&op->op, false);
पूर्ण

/**
 * fscache_put_retrieval - Drop a reference to a retrieval operation
 * @op: The retrieval operation affected
 *
 * Drop a reference to a retrieval operation.
 */
अटल अंतरभूत व्योम fscache_put_retrieval(काष्ठा fscache_retrieval *op)
अणु
	fscache_put_operation(&op->op);
पूर्ण

/*
 * cached page storage work item
 * - used to करो three things:
 *   - batch ग_लिखोs to the cache
 *   - करो cache ग_लिखोs asynchronously
 *   - defer ग_लिखोs until cache object lookup completion
 */
काष्ठा fscache_storage अणु
	काष्ठा fscache_operation op;
	pgoff_t			store_limit;	/* करोn't ग_लिखो more than this */
पूर्ण;

/*
 * cache operations
 */
काष्ठा fscache_cache_ops अणु
	/* name of cache provider */
	स्थिर अक्षर *name;

	/* allocate an object record क्रम a cookie */
	काष्ठा fscache_object *(*alloc_object)(काष्ठा fscache_cache *cache,
					       काष्ठा fscache_cookie *cookie);

	/* look up the object क्रम a cookie
	 * - वापस -ETIMEDOUT to be requeued
	 */
	पूर्णांक (*lookup_object)(काष्ठा fscache_object *object);

	/* finished looking up */
	व्योम (*lookup_complete)(काष्ठा fscache_object *object);

	/* increment the usage count on this object (may fail अगर unmounting) */
	काष्ठा fscache_object *(*grab_object)(काष्ठा fscache_object *object,
					      क्रमागत fscache_obj_ref_trace why);

	/* pin an object in the cache */
	पूर्णांक (*pin_object)(काष्ठा fscache_object *object);

	/* unpin an object in the cache */
	व्योम (*unpin_object)(काष्ठा fscache_object *object);

	/* check the consistency between the backing cache and the FS-Cache
	 * cookie */
	पूर्णांक (*check_consistency)(काष्ठा fscache_operation *op);

	/* store the updated auxiliary data on an object */
	व्योम (*update_object)(काष्ठा fscache_object *object);

	/* Invalidate an object */
	व्योम (*invalidate_object)(काष्ठा fscache_operation *op);

	/* discard the resources pinned by an object and effect retirement अगर
	 * necessary */
	व्योम (*drop_object)(काष्ठा fscache_object *object);

	/* dispose of a reference to an object */
	व्योम (*put_object)(काष्ठा fscache_object *object,
			   क्रमागत fscache_obj_ref_trace why);

	/* sync a cache */
	व्योम (*sync_cache)(काष्ठा fscache_cache *cache);

	/* notअगरication that the attributes of a non-index object (such as
	 * i_size) have changed */
	पूर्णांक (*attr_changed)(काष्ठा fscache_object *object);

	/* reserve space क्रम an object's data and associated metadata */
	पूर्णांक (*reserve_space)(काष्ठा fscache_object *object, loff_t i_size);

	/* request a backing block क्रम a page be पढ़ो or allocated in the
	 * cache */
	fscache_page_retrieval_func_t पढ़ो_or_alloc_page;

	/* request backing blocks क्रम a list of pages be पढ़ो or allocated in
	 * the cache */
	fscache_pages_retrieval_func_t पढ़ो_or_alloc_pages;

	/* request a backing block क्रम a page be allocated in the cache so that
	 * it can be written directly */
	fscache_page_retrieval_func_t allocate_page;

	/* request backing blocks क्रम pages be allocated in the cache so that
	 * they can be written directly */
	fscache_pages_retrieval_func_t allocate_pages;

	/* ग_लिखो a page to its backing block in the cache */
	पूर्णांक (*ग_लिखो_page)(काष्ठा fscache_storage *op, काष्ठा page *page);

	/* detach backing block from a page (optional)
	 * - must release the cookie lock beक्रमe वापसing
	 * - may sleep
	 */
	व्योम (*uncache_page)(काष्ठा fscache_object *object,
			     काष्ठा page *page);

	/* dissociate a cache from all the pages it was backing */
	व्योम (*dissociate_pages)(काष्ठा fscache_cache *cache);

	/* Begin a पढ़ो operation क्रम the netfs lib */
	पूर्णांक (*begin_पढ़ो_operation)(काष्ठा netfs_पढ़ो_request *rreq,
				    काष्ठा fscache_retrieval *op);
पूर्ण;

बाह्य काष्ठा fscache_cookie fscache_fsdef_index;

/*
 * Event list क्रम fscache_object::अणुevent_mask,eventsपूर्ण
 */
क्रमागत अणु
	FSCACHE_OBJECT_EV_NEW_CHILD,	/* T अगर object has a new child */
	FSCACHE_OBJECT_EV_PARENT_READY,	/* T अगर object's parent is पढ़ोy */
	FSCACHE_OBJECT_EV_UPDATE,	/* T अगर object should be updated */
	FSCACHE_OBJECT_EV_INVALIDATE,	/* T अगर cache requested object invalidation */
	FSCACHE_OBJECT_EV_CLEARED,	/* T अगर accessors all gone */
	FSCACHE_OBJECT_EV_ERROR,	/* T अगर fatal error occurred during processing */
	FSCACHE_OBJECT_EV_KILL,		/* T अगर netfs relinquished or cache withdrew object */
	NR_FSCACHE_OBJECT_EVENTS
पूर्ण;

#घोषणा FSCACHE_OBJECT_EVENTS_MASK ((1UL << NR_FSCACHE_OBJECT_EVENTS) - 1)

/*
 * States क्रम object state machine.
 */
काष्ठा fscache_transition अणु
	अचिन्हित दीर्घ events;
	स्थिर काष्ठा fscache_state *transit_to;
पूर्ण;

काष्ठा fscache_state अणु
	अक्षर name[24];
	अक्षर लघु_name[8];
	स्थिर काष्ठा fscache_state *(*work)(काष्ठा fscache_object *object,
					    पूर्णांक event);
	स्थिर काष्ठा fscache_transition transitions[];
पूर्ण;

/*
 * on-disk cache file or index handle
 */
काष्ठा fscache_object अणु
	स्थिर काष्ठा fscache_state *state;	/* Object state machine state */
	स्थिर काष्ठा fscache_transition *oob_table; /* OOB state transition table */
	पूर्णांक			debug_id;	/* debugging ID */
	पूर्णांक			n_children;	/* number of child objects */
	पूर्णांक			n_ops;		/* number of extant ops on object */
	पूर्णांक			n_obj_ops;	/* number of object ops outstanding on object */
	पूर्णांक			n_in_progress;	/* number of ops in progress */
	पूर्णांक			n_exclusive;	/* number of exclusive ops queued or in progress */
	atomic_t		n_पढ़ोs;	/* number of पढ़ो ops in progress */
	spinlock_t		lock;		/* state and operations lock */

	अचिन्हित दीर्घ		lookup_jअगर;	/* समय at which lookup started */
	अचिन्हित दीर्घ		oob_event_mask;	/* OOB events this object is पूर्णांकerested in */
	अचिन्हित दीर्घ		event_mask;	/* events this object is पूर्णांकerested in */
	अचिन्हित दीर्घ		events;		/* events to be processed by this object
						 * (order is important - using fls) */

	अचिन्हित दीर्घ		flags;
#घोषणा FSCACHE_OBJECT_LOCK		0	/* T अगर object is busy being processed */
#घोषणा FSCACHE_OBJECT_PENDING_WRITE	1	/* T अगर object has pending ग_लिखो */
#घोषणा FSCACHE_OBJECT_WAITING		2	/* T अगर object is रुकोing on its parent */
#घोषणा FSCACHE_OBJECT_IS_LIVE		3	/* T अगर object is not withdrawn or relinquished */
#घोषणा FSCACHE_OBJECT_IS_LOOKED_UP	4	/* T अगर object has been looked up */
#घोषणा FSCACHE_OBJECT_IS_AVAILABLE	5	/* T अगर object has become active */
#घोषणा FSCACHE_OBJECT_RETIRED		6	/* T अगर object was retired on relinquishment */
#घोषणा FSCACHE_OBJECT_KILLED_BY_CACHE	7	/* T अगर object was समाप्तed by the cache */
#घोषणा FSCACHE_OBJECT_RUN_AFTER_DEAD	8	/* T अगर object has been dispatched after death */

	काष्ठा list_head	cache_link;	/* link in cache->object_list */
	काष्ठा hlist_node	cookie_link;	/* link in cookie->backing_objects */
	काष्ठा fscache_cache	*cache;		/* cache that supplied this object */
	काष्ठा fscache_cookie	*cookie;	/* netfs's file/index object */
	काष्ठा fscache_object	*parent;	/* parent object */
	काष्ठा work_काष्ठा	work;		/* attention scheduling record */
	काष्ठा list_head	dependents;	/* FIFO of dependent objects */
	काष्ठा list_head	dep_link;	/* link in parent's dependents list */
	काष्ठा list_head	pending_ops;	/* unstarted operations on this object */
#अगर_घोषित CONFIG_FSCACHE_OBJECT_LIST
	काष्ठा rb_node		objlist_link;	/* link in global object list */
#पूर्ण_अगर
	pgoff_t			store_limit;	/* current storage limit */
	loff_t			store_limit_l;	/* current storage limit */
पूर्ण;

बाह्य व्योम fscache_object_init(काष्ठा fscache_object *, काष्ठा fscache_cookie *,
				काष्ठा fscache_cache *);
बाह्य व्योम fscache_object_destroy(काष्ठा fscache_object *);

बाह्य व्योम fscache_object_lookup_negative(काष्ठा fscache_object *object);
बाह्य व्योम fscache_obtained_object(काष्ठा fscache_object *object);

अटल अंतरभूत bool fscache_object_is_live(काष्ठा fscache_object *object)
अणु
	वापस test_bit(FSCACHE_OBJECT_IS_LIVE, &object->flags);
पूर्ण

अटल अंतरभूत bool fscache_object_is_dying(काष्ठा fscache_object *object)
अणु
	वापस !fscache_object_is_live(object);
पूर्ण

अटल अंतरभूत bool fscache_object_is_available(काष्ठा fscache_object *object)
अणु
	वापस test_bit(FSCACHE_OBJECT_IS_AVAILABLE, &object->flags);
पूर्ण

अटल अंतरभूत bool fscache_cache_is_broken(काष्ठा fscache_object *object)
अणु
	वापस test_bit(FSCACHE_IOERROR, &object->cache->flags);
पूर्ण

अटल अंतरभूत bool fscache_object_is_active(काष्ठा fscache_object *object)
अणु
	वापस fscache_object_is_available(object) &&
		fscache_object_is_live(object) &&
		!fscache_cache_is_broken(object);
पूर्ण

/**
 * fscache_object_destroyed - Note deकाष्ठाion of an object in a cache
 * @cache: The cache from which the object came
 *
 * Note the deकाष्ठाion and deallocation of an object record in a cache.
 */
अटल अंतरभूत व्योम fscache_object_destroyed(काष्ठा fscache_cache *cache)
अणु
	अगर (atomic_dec_and_test(&cache->object_count))
		wake_up_all(&fscache_cache_cleared_wq);
पूर्ण

/**
 * fscache_object_lookup_error - Note an object encountered an error
 * @object: The object on which the error was encountered
 *
 * Note that an object encountered a fatal error (usually an I/O error) and
 * that it should be withdrawn as soon as possible.
 */
अटल अंतरभूत व्योम fscache_object_lookup_error(काष्ठा fscache_object *object)
अणु
	set_bit(FSCACHE_OBJECT_EV_ERROR, &object->events);
पूर्ण

/**
 * fscache_set_store_limit - Set the maximum size to be stored in an object
 * @object: The object to set the maximum on
 * @i_size: The limit to set in bytes
 *
 * Set the maximum size an object is permitted to reach, implying the highest
 * byte that may be written.  Intended to be called by the attr_changed() op.
 *
 * See Documentation/fileप्रणालीs/caching/backend-api.rst क्रम a complete
 * description.
 */
अटल अंतरभूत
व्योम fscache_set_store_limit(काष्ठा fscache_object *object, loff_t i_size)
अणु
	object->store_limit_l = i_size;
	object->store_limit = i_size >> PAGE_SHIFT;
	अगर (i_size & ~PAGE_MASK)
		object->store_limit++;
पूर्ण

/**
 * fscache_end_io - End a retrieval operation on a page
 * @op: The FS-Cache operation covering the retrieval
 * @page: The page that was to be fetched
 * @error: The error code (0 अगर successful)
 *
 * Note the end of an operation to retrieve a page, as covered by a particular
 * operation record.
 */
अटल अंतरभूत व्योम fscache_end_io(काष्ठा fscache_retrieval *op,
				  काष्ठा page *page, पूर्णांक error)
अणु
	op->end_io_func(page, op->context, error);
पूर्ण

अटल अंतरभूत व्योम __fscache_use_cookie(काष्ठा fscache_cookie *cookie)
अणु
	atomic_inc(&cookie->n_active);
पूर्ण

/**
 * fscache_use_cookie - Request usage of cookie attached to an object
 * @object: Object description
 * 
 * Request usage of the cookie attached to an object.  शून्य is वापसed अगर the
 * relinquishment had reduced the cookie usage count to 0.
 */
अटल अंतरभूत bool fscache_use_cookie(काष्ठा fscache_object *object)
अणु
	काष्ठा fscache_cookie *cookie = object->cookie;
	वापस atomic_inc_not_zero(&cookie->n_active) != 0;
पूर्ण

अटल अंतरभूत bool __fscache_unuse_cookie(काष्ठा fscache_cookie *cookie)
अणु
	वापस atomic_dec_and_test(&cookie->n_active);
पूर्ण

अटल अंतरभूत व्योम __fscache_wake_unused_cookie(काष्ठा fscache_cookie *cookie)
अणु
	wake_up_var(&cookie->n_active);
पूर्ण

/**
 * fscache_unuse_cookie - Cease usage of cookie attached to an object
 * @object: Object description
 * 
 * Cease usage of the cookie attached to an object.  When the users count
 * reaches zero then the cookie relinquishment will be permitted to proceed.
 */
अटल अंतरभूत व्योम fscache_unuse_cookie(काष्ठा fscache_object *object)
अणु
	काष्ठा fscache_cookie *cookie = object->cookie;
	अगर (__fscache_unuse_cookie(cookie))
		__fscache_wake_unused_cookie(cookie);
पूर्ण

/*
 * out-of-line cache backend functions
 */
बाह्य __म_लिखो(3, 4)
व्योम fscache_init_cache(काष्ठा fscache_cache *cache,
			स्थिर काष्ठा fscache_cache_ops *ops,
			स्थिर अक्षर *idfmt, ...);

बाह्य पूर्णांक fscache_add_cache(काष्ठा fscache_cache *cache,
			     काष्ठा fscache_object *fsdef,
			     स्थिर अक्षर *tagname);
बाह्य व्योम fscache_withdraw_cache(काष्ठा fscache_cache *cache);

बाह्य व्योम fscache_io_error(काष्ठा fscache_cache *cache);

बाह्य व्योम fscache_mark_page_cached(काष्ठा fscache_retrieval *op,
				     काष्ठा page *page);

बाह्य व्योम fscache_mark_pages_cached(काष्ठा fscache_retrieval *op,
				      काष्ठा pagevec *pagevec);

बाह्य bool fscache_object_sleep_till_congested(चिन्हित दीर्घ *समयoutp);

बाह्य क्रमागत fscache_checkaux fscache_check_aux(काष्ठा fscache_object *object,
					       स्थिर व्योम *data,
					       uपूर्णांक16_t datalen,
					       loff_t object_size);

बाह्य व्योम fscache_object_retrying_stale(काष्ठा fscache_object *object);

क्रमागत fscache_why_object_समाप्तed अणु
	FSCACHE_OBJECT_IS_STALE,
	FSCACHE_OBJECT_NO_SPACE,
	FSCACHE_OBJECT_WAS_RETIRED,
	FSCACHE_OBJECT_WAS_CULLED,
पूर्ण;
बाह्य व्योम fscache_object_mark_समाप्तed(काष्ठा fscache_object *object,
				       क्रमागत fscache_why_object_समाप्तed why);

#पूर्ण_अगर /* _LINUX_FSCACHE_CACHE_H */
