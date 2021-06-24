<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Internal definitions क्रम FS-Cache
 *
 * Copyright (C) 2004-2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

/*
 * Lock order, in the order in which multiple locks should be obtained:
 * - fscache_addहटाओ_sem
 * - cookie->lock
 * - cookie->parent->lock
 * - cache->object_list_lock
 * - object->lock
 * - object->parent->lock
 * - cookie->stores_lock
 * - fscache_thपढ़ो_lock
 *
 */

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) "FS-Cache: " fmt

#समावेश <linux/fscache-cache.h>
#समावेश <trace/events/fscache.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>

#घोषणा FSCACHE_MIN_THREADS	4
#घोषणा FSCACHE_MAX_THREADS	32

/*
 * cache.c
 */
बाह्य काष्ठा list_head fscache_cache_list;
बाह्य काष्ठा rw_semaphore fscache_addहटाओ_sem;

बाह्य काष्ठा fscache_cache *fscache_select_cache_क्रम_object(
	काष्ठा fscache_cookie *);

/*
 * cookie.c
 */
बाह्य काष्ठा kmem_cache *fscache_cookie_jar;

बाह्य व्योम fscache_मुक्त_cookie(काष्ठा fscache_cookie *);
बाह्य काष्ठा fscache_cookie *fscache_alloc_cookie(काष्ठा fscache_cookie *,
						   स्थिर काष्ठा fscache_cookie_def *,
						   स्थिर व्योम *, माप_प्रकार,
						   स्थिर व्योम *, माप_प्रकार,
						   व्योम *, loff_t);
बाह्य काष्ठा fscache_cookie *fscache_hash_cookie(काष्ठा fscache_cookie *);
बाह्य व्योम fscache_cookie_put(काष्ठा fscache_cookie *,
			       क्रमागत fscache_cookie_trace);

/*
 * fsdef.c
 */
बाह्य काष्ठा fscache_cookie fscache_fsdef_index;
बाह्य काष्ठा fscache_cookie_def fscache_fsdef_netfs_def;

/*
 * histogram.c
 */
#अगर_घोषित CONFIG_FSCACHE_HISTOGRAM
बाह्य atomic_t fscache_obj_instantiate_histogram[HZ];
बाह्य atomic_t fscache_objs_histogram[HZ];
बाह्य atomic_t fscache_ops_histogram[HZ];
बाह्य atomic_t fscache_retrieval_delay_histogram[HZ];
बाह्य atomic_t fscache_retrieval_histogram[HZ];

अटल अंतरभूत व्योम fscache_hist(atomic_t histogram[], अचिन्हित दीर्घ start_jअगर)
अणु
	अचिन्हित दीर्घ jअगर = jअगरfies - start_jअगर;
	अगर (jअगर >= HZ)
		jअगर = HZ - 1;
	atomic_inc(&histogram[jअगर]);
पूर्ण

बाह्य स्थिर काष्ठा seq_operations fscache_histogram_ops;

#अन्यथा
#घोषणा fscache_hist(hist, start_jअगर) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * मुख्य.c
 */
बाह्य अचिन्हित fscache_defer_lookup;
बाह्य अचिन्हित fscache_defer_create;
बाह्य अचिन्हित fscache_debug;
बाह्य काष्ठा kobject *fscache_root;
बाह्य काष्ठा workqueue_काष्ठा *fscache_object_wq;
बाह्य काष्ठा workqueue_काष्ठा *fscache_op_wq;
DECLARE_PER_CPU(रुको_queue_head_t, fscache_object_cong_रुको);

अटल अंतरभूत bool fscache_object_congested(व्योम)
अणु
	वापस workqueue_congested(WORK_CPU_UNBOUND, fscache_object_wq);
पूर्ण

/*
 * object.c
 */
बाह्य व्योम fscache_enqueue_object(काष्ठा fscache_object *);

/*
 * object-list.c
 */
#अगर_घोषित CONFIG_FSCACHE_OBJECT_LIST
बाह्य स्थिर काष्ठा proc_ops fscache_objlist_proc_ops;

बाह्य व्योम fscache_objlist_add(काष्ठा fscache_object *);
बाह्य व्योम fscache_objlist_हटाओ(काष्ठा fscache_object *);
#अन्यथा
#घोषणा fscache_objlist_add(object) करो अणुपूर्ण जबतक(0)
#घोषणा fscache_objlist_हटाओ(object) करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर

/*
 * operation.c
 */
बाह्य पूर्णांक fscache_submit_exclusive_op(काष्ठा fscache_object *,
				       काष्ठा fscache_operation *);
बाह्य पूर्णांक fscache_submit_op(काष्ठा fscache_object *,
			     काष्ठा fscache_operation *);
बाह्य पूर्णांक fscache_cancel_op(काष्ठा fscache_operation *, bool);
बाह्य व्योम fscache_cancel_all_ops(काष्ठा fscache_object *);
बाह्य व्योम fscache_पात_object(काष्ठा fscache_object *);
बाह्य व्योम fscache_start_operations(काष्ठा fscache_object *);
बाह्य व्योम fscache_operation_gc(काष्ठा work_काष्ठा *);

/*
 * page.c
 */
बाह्य पूर्णांक fscache_रुको_क्रम_deferred_lookup(काष्ठा fscache_cookie *);
बाह्य पूर्णांक fscache_रुको_क्रम_operation_activation(काष्ठा fscache_object *,
						 काष्ठा fscache_operation *,
						 atomic_t *,
						 atomic_t *);
बाह्य व्योम fscache_invalidate_ग_लिखोs(काष्ठा fscache_cookie *);
काष्ठा fscache_retrieval *fscache_alloc_retrieval(काष्ठा fscache_cookie *cookie,
						  काष्ठा address_space *mapping,
						  fscache_rw_complete_t end_io_func,
						  व्योम *context);

/*
 * proc.c
 */
#अगर_घोषित CONFIG_PROC_FS
बाह्य पूर्णांक __init fscache_proc_init(व्योम);
बाह्य व्योम fscache_proc_cleanup(व्योम);
#अन्यथा
#घोषणा fscache_proc_init()	(0)
#घोषणा fscache_proc_cleanup()	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * stats.c
 */
#अगर_घोषित CONFIG_FSCACHE_STATS
बाह्य atomic_t fscache_n_ops_processed[FSCACHE_MAX_THREADS];
बाह्य atomic_t fscache_n_objs_processed[FSCACHE_MAX_THREADS];

बाह्य atomic_t fscache_n_op_pend;
बाह्य atomic_t fscache_n_op_run;
बाह्य atomic_t fscache_n_op_enqueue;
बाह्य atomic_t fscache_n_op_deferred_release;
बाह्य atomic_t fscache_n_op_initialised;
बाह्य atomic_t fscache_n_op_release;
बाह्य atomic_t fscache_n_op_gc;
बाह्य atomic_t fscache_n_op_cancelled;
बाह्य atomic_t fscache_n_op_rejected;

बाह्य atomic_t fscache_n_attr_changed;
बाह्य atomic_t fscache_n_attr_changed_ok;
बाह्य atomic_t fscache_n_attr_changed_nobufs;
बाह्य atomic_t fscache_n_attr_changed_nomem;
बाह्य atomic_t fscache_n_attr_changed_calls;

बाह्य atomic_t fscache_n_allocs;
बाह्य atomic_t fscache_n_allocs_ok;
बाह्य atomic_t fscache_n_allocs_रुको;
बाह्य atomic_t fscache_n_allocs_nobufs;
बाह्य atomic_t fscache_n_allocs_पूर्णांकr;
बाह्य atomic_t fscache_n_allocs_object_dead;
बाह्य atomic_t fscache_n_alloc_ops;
बाह्य atomic_t fscache_n_alloc_op_रुकोs;

बाह्य atomic_t fscache_n_retrievals;
बाह्य atomic_t fscache_n_retrievals_ok;
बाह्य atomic_t fscache_n_retrievals_रुको;
बाह्य atomic_t fscache_n_retrievals_nodata;
बाह्य atomic_t fscache_n_retrievals_nobufs;
बाह्य atomic_t fscache_n_retrievals_पूर्णांकr;
बाह्य atomic_t fscache_n_retrievals_nomem;
बाह्य atomic_t fscache_n_retrievals_object_dead;
बाह्य atomic_t fscache_n_retrieval_ops;
बाह्य atomic_t fscache_n_retrieval_op_रुकोs;

बाह्य atomic_t fscache_n_stores;
बाह्य atomic_t fscache_n_stores_ok;
बाह्य atomic_t fscache_n_stores_again;
बाह्य atomic_t fscache_n_stores_nobufs;
बाह्य atomic_t fscache_n_stores_oom;
बाह्य atomic_t fscache_n_store_ops;
बाह्य atomic_t fscache_n_store_calls;
बाह्य atomic_t fscache_n_store_pages;
बाह्य atomic_t fscache_n_store_radix_deletes;
बाह्य atomic_t fscache_n_store_pages_over_limit;

बाह्य atomic_t fscache_n_store_vmscan_not_storing;
बाह्य atomic_t fscache_n_store_vmscan_gone;
बाह्य atomic_t fscache_n_store_vmscan_busy;
बाह्य atomic_t fscache_n_store_vmscan_cancelled;
बाह्य atomic_t fscache_n_store_vmscan_रुको;

बाह्य atomic_t fscache_n_marks;
बाह्य atomic_t fscache_n_uncaches;

बाह्य atomic_t fscache_n_acquires;
बाह्य atomic_t fscache_n_acquires_null;
बाह्य atomic_t fscache_n_acquires_no_cache;
बाह्य atomic_t fscache_n_acquires_ok;
बाह्य atomic_t fscache_n_acquires_nobufs;
बाह्य atomic_t fscache_n_acquires_oom;

बाह्य atomic_t fscache_n_invalidates;
बाह्य atomic_t fscache_n_invalidates_run;

बाह्य atomic_t fscache_n_updates;
बाह्य atomic_t fscache_n_updates_null;
बाह्य atomic_t fscache_n_updates_run;

बाह्य atomic_t fscache_n_relinquishes;
बाह्य atomic_t fscache_n_relinquishes_null;
बाह्य atomic_t fscache_n_relinquishes_रुकोcrt;
बाह्य atomic_t fscache_n_relinquishes_retire;

बाह्य atomic_t fscache_n_cookie_index;
बाह्य atomic_t fscache_n_cookie_data;
बाह्य atomic_t fscache_n_cookie_special;

बाह्य atomic_t fscache_n_object_alloc;
बाह्य atomic_t fscache_n_object_no_alloc;
बाह्य atomic_t fscache_n_object_lookups;
बाह्य atomic_t fscache_n_object_lookups_negative;
बाह्य atomic_t fscache_n_object_lookups_positive;
बाह्य atomic_t fscache_n_object_lookups_समयd_out;
बाह्य atomic_t fscache_n_object_created;
बाह्य atomic_t fscache_n_object_avail;
बाह्य atomic_t fscache_n_object_dead;

बाह्य atomic_t fscache_n_checkaux_none;
बाह्य atomic_t fscache_n_checkaux_okay;
बाह्य atomic_t fscache_n_checkaux_update;
बाह्य atomic_t fscache_n_checkaux_obsolete;

बाह्य atomic_t fscache_n_cop_alloc_object;
बाह्य atomic_t fscache_n_cop_lookup_object;
बाह्य atomic_t fscache_n_cop_lookup_complete;
बाह्य atomic_t fscache_n_cop_grab_object;
बाह्य atomic_t fscache_n_cop_invalidate_object;
बाह्य atomic_t fscache_n_cop_update_object;
बाह्य atomic_t fscache_n_cop_drop_object;
बाह्य atomic_t fscache_n_cop_put_object;
बाह्य atomic_t fscache_n_cop_sync_cache;
बाह्य atomic_t fscache_n_cop_attr_changed;
बाह्य atomic_t fscache_n_cop_पढ़ो_or_alloc_page;
बाह्य atomic_t fscache_n_cop_पढ़ो_or_alloc_pages;
बाह्य atomic_t fscache_n_cop_allocate_page;
बाह्य atomic_t fscache_n_cop_allocate_pages;
बाह्य atomic_t fscache_n_cop_ग_लिखो_page;
बाह्य atomic_t fscache_n_cop_uncache_page;
बाह्य atomic_t fscache_n_cop_dissociate_pages;

बाह्य atomic_t fscache_n_cache_no_space_reject;
बाह्य atomic_t fscache_n_cache_stale_objects;
बाह्य atomic_t fscache_n_cache_retired_objects;
बाह्य atomic_t fscache_n_cache_culled_objects;

अटल अंतरभूत व्योम fscache_stat(atomic_t *stat)
अणु
	atomic_inc(stat);
पूर्ण

अटल अंतरभूत व्योम fscache_stat_d(atomic_t *stat)
अणु
	atomic_dec(stat);
पूर्ण

#घोषणा __fscache_stat(stat) (stat)

पूर्णांक fscache_stats_show(काष्ठा seq_file *m, व्योम *v);
#अन्यथा

#घोषणा __fscache_stat(stat) (शून्य)
#घोषणा fscache_stat(stat) करो अणुपूर्ण जबतक (0)
#घोषणा fscache_stat_d(stat) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * उठाओ an event on an object
 * - अगर the event is not masked क्रम that object, then the object is
 *   queued क्रम attention by the thपढ़ो pool.
 */
अटल अंतरभूत व्योम fscache_उठाओ_event(काष्ठा fscache_object *object,
				       अचिन्हित event)
अणु
	BUG_ON(event >= NR_FSCACHE_OBJECT_EVENTS);
#अगर 0
	prपूर्णांकk("*** fscache_raise_event(OBJ%d{%lx},%x)\n",
	       object->debug_id, object->event_mask, (1 << event));
#पूर्ण_अगर
	अगर (!test_and_set_bit(event, &object->events) &&
	    test_bit(event, &object->event_mask))
		fscache_enqueue_object(object);
पूर्ण

अटल अंतरभूत व्योम fscache_cookie_get(काष्ठा fscache_cookie *cookie,
				      क्रमागत fscache_cookie_trace where)
अणु
	पूर्णांक usage = atomic_inc_वापस(&cookie->usage);

	trace_fscache_cookie(cookie, where, usage);
पूर्ण

/*
 * get an extra reference to a netfs retrieval context
 */
अटल अंतरभूत
व्योम *fscache_get_context(काष्ठा fscache_cookie *cookie, व्योम *context)
अणु
	अगर (cookie->def->get_context)
		cookie->def->get_context(cookie->netfs_data, context);
	वापस context;
पूर्ण

/*
 * release a reference to a netfs retrieval context
 */
अटल अंतरभूत
व्योम fscache_put_context(काष्ठा fscache_cookie *cookie, व्योम *context)
अणु
	अगर (cookie->def->put_context)
		cookie->def->put_context(cookie->netfs_data, context);
पूर्ण

/*
 * Update the auxiliary data on a cookie.
 */
अटल अंतरभूत
व्योम fscache_update_aux(काष्ठा fscache_cookie *cookie, स्थिर व्योम *aux_data)
अणु
	व्योम *p;

	अगर (!aux_data)
		वापस;
	अगर (cookie->aux_len <= माप(cookie->अंतरभूत_aux))
		p = cookie->अंतरभूत_aux;
	अन्यथा
		p = cookie->aux;

	अगर (स_भेद(p, aux_data, cookie->aux_len) != 0) अणु
		स_नकल(p, aux_data, cookie->aux_len);
		set_bit(FSCACHE_COOKIE_AUX_UPDATED, &cookie->flags);
	पूर्ण
पूर्ण

/*****************************************************************************/
/*
 * debug tracing
 */
#घोषणा dbgprपूर्णांकk(FMT, ...) \
	prपूर्णांकk(KERN_DEBUG "[%-6.6s] "FMT"\n", current->comm, ##__VA_ARGS__)

#घोषणा kenter(FMT, ...) dbgprपूर्णांकk("==> %s("FMT")", __func__, ##__VA_ARGS__)
#घोषणा kleave(FMT, ...) dbgprपूर्णांकk("<== %s()"FMT"", __func__, ##__VA_ARGS__)
#घोषणा kdebug(FMT, ...) dbgprपूर्णांकk(FMT, ##__VA_ARGS__)

#घोषणा kjournal(FMT, ...) no_prपूर्णांकk(FMT, ##__VA_ARGS__)

#अगर_घोषित __KDEBUG
#घोषणा _enter(FMT, ...) kenter(FMT, ##__VA_ARGS__)
#घोषणा _leave(FMT, ...) kleave(FMT, ##__VA_ARGS__)
#घोषणा _debug(FMT, ...) kdebug(FMT, ##__VA_ARGS__)

#या_अगर defined(CONFIG_FSCACHE_DEBUG)
#घोषणा _enter(FMT, ...)			\
करो अणु						\
	अगर (__करो_kdebug(ENTER))			\
		kenter(FMT, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा _leave(FMT, ...)			\
करो अणु						\
	अगर (__करो_kdebug(LEAVE))			\
		kleave(FMT, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा _debug(FMT, ...)			\
करो अणु						\
	अगर (__करो_kdebug(DEBUG))			\
		kdebug(FMT, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#अन्यथा
#घोषणा _enter(FMT, ...) no_prपूर्णांकk("==> %s("FMT")", __func__, ##__VA_ARGS__)
#घोषणा _leave(FMT, ...) no_prपूर्णांकk("<== %s()"FMT"", __func__, ##__VA_ARGS__)
#घोषणा _debug(FMT, ...) no_prपूर्णांकk(FMT, ##__VA_ARGS__)
#पूर्ण_अगर

/*
 * determine whether a particular optional debugging poपूर्णांक should be logged
 * - we need to go through three steps to persuade cpp to correctly join the
 *   लघुhand in FSCACHE_DEBUG_LEVEL with its prefix
 */
#घोषणा ____करो_kdebug(LEVEL, POINT) \
	unlikely((fscache_debug & \
		  (FSCACHE_POINT_##POINT << (FSCACHE_DEBUG_ ## LEVEL * 3))))
#घोषणा ___करो_kdebug(LEVEL, POINT) \
	____करो_kdebug(LEVEL, POINT)
#घोषणा __करो_kdebug(POINT) \
	___करो_kdebug(FSCACHE_DEBUG_LEVEL, POINT)

#घोषणा FSCACHE_DEBUG_CACHE	0
#घोषणा FSCACHE_DEBUG_COOKIE	1
#घोषणा FSCACHE_DEBUG_PAGE	2
#घोषणा FSCACHE_DEBUG_OPERATION	3

#घोषणा FSCACHE_POINT_ENTER	1
#घोषणा FSCACHE_POINT_LEAVE	2
#घोषणा FSCACHE_POINT_DEBUG	4

#अगर_अघोषित FSCACHE_DEBUG_LEVEL
#घोषणा FSCACHE_DEBUG_LEVEL CACHE
#पूर्ण_अगर

/*
 * निश्चितions
 */
#अगर 1 /* defined(__KDEBUGALL) */

#घोषणा ASSERT(X)							\
करो अणु									\
	अगर (unlikely(!(X))) अणु						\
		pr_err("\n");					\
		pr_err("Assertion failed\n");	\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा ASSERTCMP(X, OP, Y)						\
करो अणु									\
	अगर (unlikely(!((X) OP (Y)))) अणु					\
		pr_err("\n");					\
		pr_err("Assertion failed\n");	\
		pr_err("%lx " #OP " %lx is false\n",		\
		       (अचिन्हित दीर्घ)(X), (अचिन्हित दीर्घ)(Y));		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा ASSERTIF(C, X)							\
करो अणु									\
	अगर (unlikely((C) && !(X))) अणु					\
		pr_err("\n");					\
		pr_err("Assertion failed\n");	\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा ASSERTIFCMP(C, X, OP, Y)					\
करो अणु									\
	अगर (unlikely((C) && !((X) OP (Y)))) अणु				\
		pr_err("\n");					\
		pr_err("Assertion failed\n");	\
		pr_err("%lx " #OP " %lx is false\n",		\
		       (अचिन्हित दीर्घ)(X), (अचिन्हित दीर्घ)(Y));		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

#अन्यथा

#घोषणा ASSERT(X)			करो अणुपूर्ण जबतक (0)
#घोषणा ASSERTCMP(X, OP, Y)		करो अणुपूर्ण जबतक (0)
#घोषणा ASSERTIF(C, X)			करो अणुपूर्ण जबतक (0)
#घोषणा ASSERTIFCMP(C, X, OP, Y)	करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर /* निश्चित or not */
