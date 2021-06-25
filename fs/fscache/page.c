<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Cache page management and data I/O routines
 *
 * Copyright (C) 2004-2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा FSCACHE_DEBUG_LEVEL PAGE
#समावेश <linux/module.h>
#समावेश <linux/fscache-cache.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

/*
 * check to see अगर a page is being written to the cache
 */
bool __fscache_check_page_ग_लिखो(काष्ठा fscache_cookie *cookie, काष्ठा page *page)
अणु
	व्योम *val;

	rcu_पढ़ो_lock();
	val = radix_tree_lookup(&cookie->stores, page->index);
	rcu_पढ़ो_unlock();
	trace_fscache_check_page(cookie, page, val, 0);

	वापस val != शून्य;
पूर्ण
EXPORT_SYMBOL(__fscache_check_page_ग_लिखो);

/*
 * रुको क्रम a page to finish being written to the cache
 */
व्योम __fscache_रुको_on_page_ग_लिखो(काष्ठा fscache_cookie *cookie, काष्ठा page *page)
अणु
	रुको_queue_head_t *wq = bit_रुकोqueue(&cookie->flags, 0);

	trace_fscache_page(cookie, page, fscache_page_ग_लिखो_रुको);

	रुको_event(*wq, !__fscache_check_page_ग_लिखो(cookie, page));
पूर्ण
EXPORT_SYMBOL(__fscache_रुको_on_page_ग_लिखो);

/*
 * रुको क्रम a page to finish being written to the cache. Put a समयout here
 * since we might be called recursively via parent fs.
 */
अटल
bool release_page_रुको_समयout(काष्ठा fscache_cookie *cookie, काष्ठा page *page)
अणु
	रुको_queue_head_t *wq = bit_रुकोqueue(&cookie->flags, 0);

	वापस रुको_event_समयout(*wq, !__fscache_check_page_ग_लिखो(cookie, page),
				  HZ);
पूर्ण

/*
 * decide whether a page can be released, possibly by cancelling a store to it
 * - we're allowed to sleep अगर __GFP_सूचीECT_RECLAIM is flagged
 */
bool __fscache_maybe_release_page(काष्ठा fscache_cookie *cookie,
				  काष्ठा page *page,
				  gfp_t gfp)
अणु
	काष्ठा page *xpage;
	व्योम *val;

	_enter("%p,%p,%x", cookie, page, gfp);

	trace_fscache_page(cookie, page, fscache_page_maybe_release);

try_again:
	rcu_पढ़ो_lock();
	val = radix_tree_lookup(&cookie->stores, page->index);
	अगर (!val) अणु
		rcu_पढ़ो_unlock();
		fscache_stat(&fscache_n_store_vmscan_not_storing);
		__fscache_uncache_page(cookie, page);
		वापस true;
	पूर्ण

	/* see अगर the page is actually undergoing storage - अगर so we can't get
	 * rid of it till the cache has finished with it */
	अगर (radix_tree_tag_get(&cookie->stores, page->index,
			       FSCACHE_COOKIE_STORING_TAG)) अणु
		rcu_पढ़ो_unlock();
		जाओ page_busy;
	पूर्ण

	/* the page is pending storage, so we attempt to cancel the store and
	 * discard the store request so that the page can be reclaimed */
	spin_lock(&cookie->stores_lock);
	rcu_पढ़ो_unlock();

	अगर (radix_tree_tag_get(&cookie->stores, page->index,
			       FSCACHE_COOKIE_STORING_TAG)) अणु
		/* the page started to undergo storage whilst we were looking,
		 * so now we can only रुको or वापस */
		spin_unlock(&cookie->stores_lock);
		जाओ page_busy;
	पूर्ण

	xpage = radix_tree_delete(&cookie->stores, page->index);
	trace_fscache_page(cookie, page, fscache_page_radix_delete);
	spin_unlock(&cookie->stores_lock);

	अगर (xpage) अणु
		fscache_stat(&fscache_n_store_vmscan_cancelled);
		fscache_stat(&fscache_n_store_radix_deletes);
		ASSERTCMP(xpage, ==, page);
	पूर्ण अन्यथा अणु
		fscache_stat(&fscache_n_store_vmscan_gone);
	पूर्ण

	wake_up_bit(&cookie->flags, 0);
	trace_fscache_wake_cookie(cookie);
	अगर (xpage)
		put_page(xpage);
	__fscache_uncache_page(cookie, page);
	वापस true;

page_busy:
	/* We will रुको here अगर we're allowed to, but that could deadlock the
	 * allocator as the work thपढ़ोs writing to the cache may all end up
	 * sleeping on memory allocation, so we may need to impose a समयout
	 * too. */
	अगर (!(gfp & __GFP_सूचीECT_RECLAIM) || !(gfp & __GFP_FS)) अणु
		fscache_stat(&fscache_n_store_vmscan_busy);
		वापस false;
	पूर्ण

	fscache_stat(&fscache_n_store_vmscan_रुको);
	अगर (!release_page_रुको_समयout(cookie, page))
		_debug("fscache writeout timeout page: %p{%lx}",
			page, page->index);

	gfp &= ~__GFP_सूचीECT_RECLAIM;
	जाओ try_again;
पूर्ण
EXPORT_SYMBOL(__fscache_maybe_release_page);

/*
 * note that a page has finished being written to the cache
 */
अटल व्योम fscache_end_page_ग_लिखो(काष्ठा fscache_object *object,
				   काष्ठा page *page)
अणु
	काष्ठा fscache_cookie *cookie;
	काष्ठा page *xpage = शून्य, *val;

	spin_lock(&object->lock);
	cookie = object->cookie;
	अगर (cookie) अणु
		/* delete the page from the tree अगर it is now no दीर्घer
		 * pending */
		spin_lock(&cookie->stores_lock);
		radix_tree_tag_clear(&cookie->stores, page->index,
				     FSCACHE_COOKIE_STORING_TAG);
		trace_fscache_page(cookie, page, fscache_page_radix_clear_store);
		अगर (!radix_tree_tag_get(&cookie->stores, page->index,
					FSCACHE_COOKIE_PENDING_TAG)) अणु
			fscache_stat(&fscache_n_store_radix_deletes);
			xpage = radix_tree_delete(&cookie->stores, page->index);
			trace_fscache_page(cookie, page, fscache_page_radix_delete);
			trace_fscache_page(cookie, page, fscache_page_ग_लिखो_end);

			val = radix_tree_lookup(&cookie->stores, page->index);
			trace_fscache_check_page(cookie, page, val, 1);
		पूर्ण अन्यथा अणु
			trace_fscache_page(cookie, page, fscache_page_ग_लिखो_end_pend);
		पूर्ण
		spin_unlock(&cookie->stores_lock);
		wake_up_bit(&cookie->flags, 0);
		trace_fscache_wake_cookie(cookie);
	पूर्ण अन्यथा अणु
		trace_fscache_page(cookie, page, fscache_page_ग_लिखो_end_noc);
	पूर्ण
	spin_unlock(&object->lock);
	अगर (xpage)
		put_page(xpage);
पूर्ण

/*
 * actually apply the changed attributes to a cache object
 */
अटल व्योम fscache_attr_changed_op(काष्ठा fscache_operation *op)
अणु
	काष्ठा fscache_object *object = op->object;
	पूर्णांक ret;

	_enter("{OBJ%x OP%x}", object->debug_id, op->debug_id);

	fscache_stat(&fscache_n_attr_changed_calls);

	अगर (fscache_object_is_active(object)) अणु
		fscache_stat(&fscache_n_cop_attr_changed);
		ret = object->cache->ops->attr_changed(object);
		fscache_stat_d(&fscache_n_cop_attr_changed);
		अगर (ret < 0)
			fscache_पात_object(object);
		fscache_op_complete(op, ret < 0);
	पूर्ण अन्यथा अणु
		fscache_op_complete(op, true);
	पूर्ण

	_leave("");
पूर्ण

/*
 * notअगरication that the attributes on an object have changed
 */
पूर्णांक __fscache_attr_changed(काष्ठा fscache_cookie *cookie)
अणु
	काष्ठा fscache_operation *op;
	काष्ठा fscache_object *object;
	bool wake_cookie = false;

	_enter("%p", cookie);

	ASSERTCMP(cookie->def->type, !=, FSCACHE_COOKIE_TYPE_INDEX);

	fscache_stat(&fscache_n_attr_changed);

	op = kzalloc(माप(*op), GFP_KERNEL);
	अगर (!op) अणु
		fscache_stat(&fscache_n_attr_changed_nomem);
		_leave(" = -ENOMEM");
		वापस -ENOMEM;
	पूर्ण

	fscache_operation_init(cookie, op, fscache_attr_changed_op, शून्य, शून्य);
	trace_fscache_page_op(cookie, शून्य, op, fscache_page_op_attr_changed);
	op->flags = FSCACHE_OP_ASYNC |
		(1 << FSCACHE_OP_EXCLUSIVE) |
		(1 << FSCACHE_OP_UNUSE_COOKIE);

	spin_lock(&cookie->lock);

	अगर (!fscache_cookie_enabled(cookie) ||
	    hlist_empty(&cookie->backing_objects))
		जाओ nobufs;
	object = hlist_entry(cookie->backing_objects.first,
			     काष्ठा fscache_object, cookie_link);

	__fscache_use_cookie(cookie);
	अगर (fscache_submit_exclusive_op(object, op) < 0)
		जाओ nobufs_dec;
	spin_unlock(&cookie->lock);
	fscache_stat(&fscache_n_attr_changed_ok);
	fscache_put_operation(op);
	_leave(" = 0");
	वापस 0;

nobufs_dec:
	wake_cookie = __fscache_unuse_cookie(cookie);
nobufs:
	spin_unlock(&cookie->lock);
	fscache_put_operation(op);
	अगर (wake_cookie)
		__fscache_wake_unused_cookie(cookie);
	fscache_stat(&fscache_n_attr_changed_nobufs);
	_leave(" = %d", -ENOBUFS);
	वापस -ENOBUFS;
पूर्ण
EXPORT_SYMBOL(__fscache_attr_changed);

/*
 * Handle cancellation of a pending retrieval op
 */
अटल व्योम fscache_करो_cancel_retrieval(काष्ठा fscache_operation *_op)
अणु
	काष्ठा fscache_retrieval *op =
		container_of(_op, काष्ठा fscache_retrieval, op);

	atomic_set(&op->n_pages, 0);
पूर्ण

/*
 * release a retrieval op reference
 */
अटल व्योम fscache_release_retrieval_op(काष्ठा fscache_operation *_op)
अणु
	काष्ठा fscache_retrieval *op =
		container_of(_op, काष्ठा fscache_retrieval, op);

	_enter("{OP%x}", op->op.debug_id);

	ASSERTIFCMP(op->op.state != FSCACHE_OP_ST_INITIALISED,
		    atomic_पढ़ो(&op->n_pages), ==, 0);

	fscache_hist(fscache_retrieval_histogram, op->start_समय);
	अगर (op->context)
		fscache_put_context(op->cookie, op->context);

	_leave("");
पूर्ण

/*
 * allocate a retrieval op
 */
काष्ठा fscache_retrieval *fscache_alloc_retrieval(
	काष्ठा fscache_cookie *cookie,
	काष्ठा address_space *mapping,
	fscache_rw_complete_t end_io_func,
	व्योम *context)
अणु
	काष्ठा fscache_retrieval *op;

	/* allocate a retrieval operation and attempt to submit it */
	op = kzalloc(माप(*op), GFP_NOIO);
	अगर (!op) अणु
		fscache_stat(&fscache_n_retrievals_nomem);
		वापस शून्य;
	पूर्ण

	fscache_operation_init(cookie, &op->op, शून्य,
			       fscache_करो_cancel_retrieval,
			       fscache_release_retrieval_op);
	op->op.flags	= FSCACHE_OP_MYTHREAD |
		(1UL << FSCACHE_OP_WAITING) |
		(1UL << FSCACHE_OP_UNUSE_COOKIE);
	op->cookie	= cookie;
	op->mapping	= mapping;
	op->end_io_func	= end_io_func;
	op->context	= context;
	op->start_समय	= jअगरfies;
	INIT_LIST_HEAD(&op->to_करो);

	/* Pin the netfs पढ़ो context in हाल we need to करो the actual netfs
	 * पढ़ो because we've encountered a cache पढ़ो failure.
	 */
	अगर (context)
		fscache_get_context(op->cookie, context);
	वापस op;
पूर्ण

/*
 * रुको क्रम a deferred lookup to complete
 */
पूर्णांक fscache_रुको_क्रम_deferred_lookup(काष्ठा fscache_cookie *cookie)
अणु
	अचिन्हित दीर्घ jअगर;

	_enter("");

	अगर (!test_bit(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags)) अणु
		_leave(" = 0 [imm]");
		वापस 0;
	पूर्ण

	fscache_stat(&fscache_n_retrievals_रुको);

	jअगर = jअगरfies;
	अगर (रुको_on_bit(&cookie->flags, FSCACHE_COOKIE_LOOKING_UP,
			TASK_INTERRUPTIBLE) != 0) अणु
		fscache_stat(&fscache_n_retrievals_पूर्णांकr);
		_leave(" = -ERESTARTSYS");
		वापस -ERESTARTSYS;
	पूर्ण

	ASSERT(!test_bit(FSCACHE_COOKIE_LOOKING_UP, &cookie->flags));

	smp_rmb();
	fscache_hist(fscache_retrieval_delay_histogram, jअगर);
	_leave(" = 0 [dly]");
	वापस 0;
पूर्ण

/*
 * रुको क्रम an object to become active (or dead)
 */
पूर्णांक fscache_रुको_क्रम_operation_activation(काष्ठा fscache_object *object,
					  काष्ठा fscache_operation *op,
					  atomic_t *stat_op_रुकोs,
					  atomic_t *stat_object_dead)
अणु
	पूर्णांक ret;

	अगर (!test_bit(FSCACHE_OP_WAITING, &op->flags))
		जाओ check_अगर_dead;

	_debug(">>> WT");
	अगर (stat_op_रुकोs)
		fscache_stat(stat_op_रुकोs);
	अगर (रुको_on_bit(&op->flags, FSCACHE_OP_WAITING,
			TASK_INTERRUPTIBLE) != 0) अणु
		trace_fscache_op(object->cookie, op, fscache_op_संकेत);
		ret = fscache_cancel_op(op, false);
		अगर (ret == 0)
			वापस -ERESTARTSYS;

		/* it's been हटाओd from the pending queue by another party,
		 * so we should get to run लघुly */
		रुको_on_bit(&op->flags, FSCACHE_OP_WAITING,
			    TASK_UNINTERRUPTIBLE);
	पूर्ण
	_debug("<<< GO");

check_अगर_dead:
	अगर (op->state == FSCACHE_OP_ST_CANCELLED) अणु
		अगर (stat_object_dead)
			fscache_stat(stat_object_dead);
		_leave(" = -ENOBUFS [cancelled]");
		वापस -ENOBUFS;
	पूर्ण
	अगर (unlikely(fscache_object_is_dying(object) ||
		     fscache_cache_is_broken(object))) अणु
		क्रमागत fscache_operation_state state = op->state;
		trace_fscache_op(object->cookie, op, fscache_op_संकेत);
		fscache_cancel_op(op, true);
		अगर (stat_object_dead)
			fscache_stat(stat_object_dead);
		_leave(" = -ENOBUFS [obj dead %d]", state);
		वापस -ENOBUFS;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * पढ़ो a page from the cache or allocate a block in which to store it
 * - we वापस:
 *   -ENOMEM	- out of memory, nothing करोne
 *   -ERESTARTSYS - पूर्णांकerrupted
 *   -ENOBUFS	- no backing object available in which to cache the block
 *   -ENODATA	- no data available in the backing object क्रम this block
 *   0		- dispatched a पढ़ो - it'll call end_io_func() when finished
 */
पूर्णांक __fscache_पढ़ो_or_alloc_page(काष्ठा fscache_cookie *cookie,
				 काष्ठा page *page,
				 fscache_rw_complete_t end_io_func,
				 व्योम *context,
				 gfp_t gfp)
अणु
	काष्ठा fscache_retrieval *op;
	काष्ठा fscache_object *object;
	bool wake_cookie = false;
	पूर्णांक ret;

	_enter("%p,%p,,,", cookie, page);

	fscache_stat(&fscache_n_retrievals);

	अगर (hlist_empty(&cookie->backing_objects))
		जाओ nobufs;

	अगर (test_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags)) अणु
		_leave(" = -ENOBUFS [invalidating]");
		वापस -ENOBUFS;
	पूर्ण

	ASSERTCMP(cookie->def->type, !=, FSCACHE_COOKIE_TYPE_INDEX);
	ASSERTCMP(page, !=, शून्य);

	अगर (fscache_रुको_क्रम_deferred_lookup(cookie) < 0)
		वापस -ERESTARTSYS;

	op = fscache_alloc_retrieval(cookie, page->mapping,
				     end_io_func, context);
	अगर (!op) अणु
		_leave(" = -ENOMEM");
		वापस -ENOMEM;
	पूर्ण
	atomic_set(&op->n_pages, 1);
	trace_fscache_page_op(cookie, page, &op->op, fscache_page_op_retr_one);

	spin_lock(&cookie->lock);

	अगर (!fscache_cookie_enabled(cookie) ||
	    hlist_empty(&cookie->backing_objects))
		जाओ nobufs_unlock;
	object = hlist_entry(cookie->backing_objects.first,
			     काष्ठा fscache_object, cookie_link);

	ASSERT(test_bit(FSCACHE_OBJECT_IS_LOOKED_UP, &object->flags));

	__fscache_use_cookie(cookie);
	atomic_inc(&object->n_पढ़ोs);
	__set_bit(FSCACHE_OP_DEC_READ_CNT, &op->op.flags);

	अगर (fscache_submit_op(object, &op->op) < 0)
		जाओ nobufs_unlock_dec;
	spin_unlock(&cookie->lock);

	fscache_stat(&fscache_n_retrieval_ops);

	/* we रुको क्रम the operation to become active, and then process it
	 * *here*, in this thपढ़ो, and not in the thपढ़ो pool */
	ret = fscache_रुको_क्रम_operation_activation(
		object, &op->op,
		__fscache_stat(&fscache_n_retrieval_op_रुकोs),
		__fscache_stat(&fscache_n_retrievals_object_dead));
	अगर (ret < 0)
		जाओ error;

	/* ask the cache to honour the operation */
	अगर (test_bit(FSCACHE_COOKIE_NO_DATA_YET, &object->cookie->flags)) अणु
		fscache_stat(&fscache_n_cop_allocate_page);
		ret = object->cache->ops->allocate_page(op, page, gfp);
		fscache_stat_d(&fscache_n_cop_allocate_page);
		अगर (ret == 0)
			ret = -ENODATA;
	पूर्ण अन्यथा अणु
		fscache_stat(&fscache_n_cop_पढ़ो_or_alloc_page);
		ret = object->cache->ops->पढ़ो_or_alloc_page(op, page, gfp);
		fscache_stat_d(&fscache_n_cop_पढ़ो_or_alloc_page);
	पूर्ण

error:
	अगर (ret == -ENOMEM)
		fscache_stat(&fscache_n_retrievals_nomem);
	अन्यथा अगर (ret == -ERESTARTSYS)
		fscache_stat(&fscache_n_retrievals_पूर्णांकr);
	अन्यथा अगर (ret == -ENODATA)
		fscache_stat(&fscache_n_retrievals_nodata);
	अन्यथा अगर (ret < 0)
		fscache_stat(&fscache_n_retrievals_nobufs);
	अन्यथा
		fscache_stat(&fscache_n_retrievals_ok);

	fscache_put_retrieval(op);
	_leave(" = %d", ret);
	वापस ret;

nobufs_unlock_dec:
	atomic_dec(&object->n_पढ़ोs);
	wake_cookie = __fscache_unuse_cookie(cookie);
nobufs_unlock:
	spin_unlock(&cookie->lock);
	अगर (wake_cookie)
		__fscache_wake_unused_cookie(cookie);
	fscache_put_retrieval(op);
nobufs:
	fscache_stat(&fscache_n_retrievals_nobufs);
	_leave(" = -ENOBUFS");
	वापस -ENOBUFS;
पूर्ण
EXPORT_SYMBOL(__fscache_पढ़ो_or_alloc_page);

/*
 * पढ़ो a list of page from the cache or allocate a block in which to store
 * them
 * - we वापस:
 *   -ENOMEM	- out of memory, some pages may be being पढ़ो
 *   -ERESTARTSYS - पूर्णांकerrupted, some pages may be being पढ़ो
 *   -ENOBUFS	- no backing object or space available in which to cache any
 *                pages not being पढ़ो
 *   -ENODATA	- no data available in the backing object क्रम some or all of
 *                the pages
 *   0		- dispatched a पढ़ो on all pages
 *
 * end_io_func() will be called क्रम each page पढ़ो from the cache as it is
 * finishes being पढ़ो
 *
 * any pages क्रम which a पढ़ो is dispatched will be हटाओd from pages and
 * nr_pages
 */
पूर्णांक __fscache_पढ़ो_or_alloc_pages(काष्ठा fscache_cookie *cookie,
				  काष्ठा address_space *mapping,
				  काष्ठा list_head *pages,
				  अचिन्हित *nr_pages,
				  fscache_rw_complete_t end_io_func,
				  व्योम *context,
				  gfp_t gfp)
अणु
	काष्ठा fscache_retrieval *op;
	काष्ठा fscache_object *object;
	bool wake_cookie = false;
	पूर्णांक ret;

	_enter("%p,,%d,,,", cookie, *nr_pages);

	fscache_stat(&fscache_n_retrievals);

	अगर (hlist_empty(&cookie->backing_objects))
		जाओ nobufs;

	अगर (test_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags)) अणु
		_leave(" = -ENOBUFS [invalidating]");
		वापस -ENOBUFS;
	पूर्ण

	ASSERTCMP(cookie->def->type, !=, FSCACHE_COOKIE_TYPE_INDEX);
	ASSERTCMP(*nr_pages, >, 0);
	ASSERT(!list_empty(pages));

	अगर (fscache_रुको_क्रम_deferred_lookup(cookie) < 0)
		वापस -ERESTARTSYS;

	op = fscache_alloc_retrieval(cookie, mapping, end_io_func, context);
	अगर (!op)
		वापस -ENOMEM;
	atomic_set(&op->n_pages, *nr_pages);
	trace_fscache_page_op(cookie, शून्य, &op->op, fscache_page_op_retr_multi);

	spin_lock(&cookie->lock);

	अगर (!fscache_cookie_enabled(cookie) ||
	    hlist_empty(&cookie->backing_objects))
		जाओ nobufs_unlock;
	object = hlist_entry(cookie->backing_objects.first,
			     काष्ठा fscache_object, cookie_link);

	__fscache_use_cookie(cookie);
	atomic_inc(&object->n_पढ़ोs);
	__set_bit(FSCACHE_OP_DEC_READ_CNT, &op->op.flags);

	अगर (fscache_submit_op(object, &op->op) < 0)
		जाओ nobufs_unlock_dec;
	spin_unlock(&cookie->lock);

	fscache_stat(&fscache_n_retrieval_ops);

	/* we रुको क्रम the operation to become active, and then process it
	 * *here*, in this thपढ़ो, and not in the thपढ़ो pool */
	ret = fscache_रुको_क्रम_operation_activation(
		object, &op->op,
		__fscache_stat(&fscache_n_retrieval_op_रुकोs),
		__fscache_stat(&fscache_n_retrievals_object_dead));
	अगर (ret < 0)
		जाओ error;

	/* ask the cache to honour the operation */
	अगर (test_bit(FSCACHE_COOKIE_NO_DATA_YET, &object->cookie->flags)) अणु
		fscache_stat(&fscache_n_cop_allocate_pages);
		ret = object->cache->ops->allocate_pages(
			op, pages, nr_pages, gfp);
		fscache_stat_d(&fscache_n_cop_allocate_pages);
	पूर्ण अन्यथा अणु
		fscache_stat(&fscache_n_cop_पढ़ो_or_alloc_pages);
		ret = object->cache->ops->पढ़ो_or_alloc_pages(
			op, pages, nr_pages, gfp);
		fscache_stat_d(&fscache_n_cop_पढ़ो_or_alloc_pages);
	पूर्ण

error:
	अगर (ret == -ENOMEM)
		fscache_stat(&fscache_n_retrievals_nomem);
	अन्यथा अगर (ret == -ERESTARTSYS)
		fscache_stat(&fscache_n_retrievals_पूर्णांकr);
	अन्यथा अगर (ret == -ENODATA)
		fscache_stat(&fscache_n_retrievals_nodata);
	अन्यथा अगर (ret < 0)
		fscache_stat(&fscache_n_retrievals_nobufs);
	अन्यथा
		fscache_stat(&fscache_n_retrievals_ok);

	fscache_put_retrieval(op);
	_leave(" = %d", ret);
	वापस ret;

nobufs_unlock_dec:
	atomic_dec(&object->n_पढ़ोs);
	wake_cookie = __fscache_unuse_cookie(cookie);
nobufs_unlock:
	spin_unlock(&cookie->lock);
	fscache_put_retrieval(op);
	अगर (wake_cookie)
		__fscache_wake_unused_cookie(cookie);
nobufs:
	fscache_stat(&fscache_n_retrievals_nobufs);
	_leave(" = -ENOBUFS");
	वापस -ENOBUFS;
पूर्ण
EXPORT_SYMBOL(__fscache_पढ़ो_or_alloc_pages);

/*
 * allocate a block in the cache on which to store a page
 * - we वापस:
 *   -ENOMEM	- out of memory, nothing करोne
 *   -ERESTARTSYS - पूर्णांकerrupted
 *   -ENOBUFS	- no backing object available in which to cache the block
 *   0		- block allocated
 */
पूर्णांक __fscache_alloc_page(काष्ठा fscache_cookie *cookie,
			 काष्ठा page *page,
			 gfp_t gfp)
अणु
	काष्ठा fscache_retrieval *op;
	काष्ठा fscache_object *object;
	bool wake_cookie = false;
	पूर्णांक ret;

	_enter("%p,%p,,,", cookie, page);

	fscache_stat(&fscache_n_allocs);

	अगर (hlist_empty(&cookie->backing_objects))
		जाओ nobufs;

	ASSERTCMP(cookie->def->type, !=, FSCACHE_COOKIE_TYPE_INDEX);
	ASSERTCMP(page, !=, शून्य);

	अगर (test_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags)) अणु
		_leave(" = -ENOBUFS [invalidating]");
		वापस -ENOBUFS;
	पूर्ण

	अगर (fscache_रुको_क्रम_deferred_lookup(cookie) < 0)
		वापस -ERESTARTSYS;

	op = fscache_alloc_retrieval(cookie, page->mapping, शून्य, शून्य);
	अगर (!op)
		वापस -ENOMEM;
	atomic_set(&op->n_pages, 1);
	trace_fscache_page_op(cookie, page, &op->op, fscache_page_op_alloc_one);

	spin_lock(&cookie->lock);

	अगर (!fscache_cookie_enabled(cookie) ||
	    hlist_empty(&cookie->backing_objects))
		जाओ nobufs_unlock;
	object = hlist_entry(cookie->backing_objects.first,
			     काष्ठा fscache_object, cookie_link);

	__fscache_use_cookie(cookie);
	अगर (fscache_submit_op(object, &op->op) < 0)
		जाओ nobufs_unlock_dec;
	spin_unlock(&cookie->lock);

	fscache_stat(&fscache_n_alloc_ops);

	ret = fscache_रुको_क्रम_operation_activation(
		object, &op->op,
		__fscache_stat(&fscache_n_alloc_op_रुकोs),
		__fscache_stat(&fscache_n_allocs_object_dead));
	अगर (ret < 0)
		जाओ error;

	/* ask the cache to honour the operation */
	fscache_stat(&fscache_n_cop_allocate_page);
	ret = object->cache->ops->allocate_page(op, page, gfp);
	fscache_stat_d(&fscache_n_cop_allocate_page);

error:
	अगर (ret == -ERESTARTSYS)
		fscache_stat(&fscache_n_allocs_पूर्णांकr);
	अन्यथा अगर (ret < 0)
		fscache_stat(&fscache_n_allocs_nobufs);
	अन्यथा
		fscache_stat(&fscache_n_allocs_ok);

	fscache_put_retrieval(op);
	_leave(" = %d", ret);
	वापस ret;

nobufs_unlock_dec:
	wake_cookie = __fscache_unuse_cookie(cookie);
nobufs_unlock:
	spin_unlock(&cookie->lock);
	fscache_put_retrieval(op);
	अगर (wake_cookie)
		__fscache_wake_unused_cookie(cookie);
nobufs:
	fscache_stat(&fscache_n_allocs_nobufs);
	_leave(" = -ENOBUFS");
	वापस -ENOBUFS;
पूर्ण
EXPORT_SYMBOL(__fscache_alloc_page);

/*
 * Unmark pages allocate in the पढ़ोahead code path (via:
 * fscache_पढ़ोpages_or_alloc) after delegating to the base fileप्रणाली
 */
व्योम __fscache_पढ़ोpages_cancel(काष्ठा fscache_cookie *cookie,
				काष्ठा list_head *pages)
अणु
	काष्ठा page *page;

	list_क्रम_each_entry(page, pages, lru) अणु
		अगर (PageFsCache(page))
			__fscache_uncache_page(cookie, page);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__fscache_पढ़ोpages_cancel);

/*
 * release a ग_लिखो op reference
 */
अटल व्योम fscache_release_ग_लिखो_op(काष्ठा fscache_operation *_op)
अणु
	_enter("{OP%x}", _op->debug_id);
पूर्ण

/*
 * perक्रमm the background storage of a page पूर्णांकo the cache
 */
अटल व्योम fscache_ग_लिखो_op(काष्ठा fscache_operation *_op)
अणु
	काष्ठा fscache_storage *op =
		container_of(_op, काष्ठा fscache_storage, op);
	काष्ठा fscache_object *object = op->op.object;
	काष्ठा fscache_cookie *cookie;
	काष्ठा page *page;
	अचिन्हित n;
	व्योम *results[1];
	पूर्णांक ret;

	_enter("{OP%x,%d}", op->op.debug_id, atomic_पढ़ो(&op->op.usage));

again:
	spin_lock(&object->lock);
	cookie = object->cookie;

	अगर (!fscache_object_is_active(object)) अणु
		/* If we get here, then the on-disk cache object likely no
		 * दीर्घer exists, so we should just cancel this ग_लिखो
		 * operation.
		 */
		spin_unlock(&object->lock);
		fscache_op_complete(&op->op, true);
		_leave(" [inactive]");
		वापस;
	पूर्ण

	अगर (!cookie) अणु
		/* If we get here, then the cookie beदीर्घing to the object was
		 * detached, probably by the cookie being withdrawn due to
		 * memory pressure, which means that the pages we might ग_लिखो
		 * to the cache from no दीर्घer exist - thereक्रमe, we can just
		 * cancel this ग_लिखो operation.
		 */
		spin_unlock(&object->lock);
		fscache_op_complete(&op->op, true);
		_leave(" [cancel] op{f=%lx s=%u} obj{s=%s f=%lx}",
		       _op->flags, _op->state, object->state->लघु_name,
		       object->flags);
		वापस;
	पूर्ण

	spin_lock(&cookie->stores_lock);

	fscache_stat(&fscache_n_store_calls);

	/* find a page to store */
	results[0] = शून्य;
	page = शून्य;
	n = radix_tree_gang_lookup_tag(&cookie->stores, results, 0, 1,
				       FSCACHE_COOKIE_PENDING_TAG);
	trace_fscache_gang_lookup(cookie, &op->op, results, n, op->store_limit);
	अगर (n != 1)
		जाओ superseded;
	page = results[0];
	_debug("gang %d [%lx]", n, page->index);

	radix_tree_tag_set(&cookie->stores, page->index,
			   FSCACHE_COOKIE_STORING_TAG);
	radix_tree_tag_clear(&cookie->stores, page->index,
			     FSCACHE_COOKIE_PENDING_TAG);
	trace_fscache_page(cookie, page, fscache_page_radix_pend2store);

	spin_unlock(&cookie->stores_lock);
	spin_unlock(&object->lock);

	अगर (page->index >= op->store_limit)
		जाओ discard_page;

	fscache_stat(&fscache_n_store_pages);
	fscache_stat(&fscache_n_cop_ग_लिखो_page);
	ret = object->cache->ops->ग_लिखो_page(op, page);
	fscache_stat_d(&fscache_n_cop_ग_लिखो_page);
	trace_fscache_wrote_page(cookie, page, &op->op, ret);
	fscache_end_page_ग_लिखो(object, page);
	अगर (ret < 0) अणु
		fscache_पात_object(object);
		fscache_op_complete(&op->op, true);
	पूर्ण अन्यथा अणु
		fscache_enqueue_operation(&op->op);
	पूर्ण

	_leave("");
	वापस;

discard_page:
	fscache_stat(&fscache_n_store_pages_over_limit);
	trace_fscache_wrote_page(cookie, page, &op->op, -ENOBUFS);
	fscache_end_page_ग_लिखो(object, page);
	जाओ again;

superseded:
	/* this ग_लिखोr is going away and there aren't any more things to
	 * ग_लिखो */
	_debug("cease");
	spin_unlock(&cookie->stores_lock);
	clear_bit(FSCACHE_OBJECT_PENDING_WRITE, &object->flags);
	spin_unlock(&object->lock);
	fscache_op_complete(&op->op, false);
	_leave("");
पूर्ण

/*
 * Clear the pages pending writing क्रम invalidation
 */
व्योम fscache_invalidate_ग_लिखोs(काष्ठा fscache_cookie *cookie)
अणु
	काष्ठा page *page;
	व्योम *results[16];
	पूर्णांक n, i;

	_enter("");

	क्रम (;;) अणु
		spin_lock(&cookie->stores_lock);
		n = radix_tree_gang_lookup_tag(&cookie->stores, results, 0,
					       ARRAY_SIZE(results),
					       FSCACHE_COOKIE_PENDING_TAG);
		अगर (n == 0) अणु
			spin_unlock(&cookie->stores_lock);
			अवरोध;
		पूर्ण

		क्रम (i = n - 1; i >= 0; i--) अणु
			page = results[i];
			radix_tree_delete(&cookie->stores, page->index);
			trace_fscache_page(cookie, page, fscache_page_radix_delete);
			trace_fscache_page(cookie, page, fscache_page_inval);
		पूर्ण

		spin_unlock(&cookie->stores_lock);

		क्रम (i = n - 1; i >= 0; i--)
			put_page(results[i]);
	पूर्ण

	wake_up_bit(&cookie->flags, 0);
	trace_fscache_wake_cookie(cookie);

	_leave("");
पूर्ण

/*
 * request a page be stored in the cache
 * - वापसs:
 *   -ENOMEM	- out of memory, nothing करोne
 *   -ENOBUFS	- no backing object available in which to cache the page
 *   0		- dispatched a ग_लिखो - it'll call end_io_func() when finished
 *
 * अगर the cookie still has a backing object at this poपूर्णांक, that object can be
 * in one of a few states with respect to storage processing:
 *
 *  (1) negative lookup, object not yet created (FSCACHE_COOKIE_CREATING is
 *      set)
 *
 *	(a) no ग_लिखोs yet
 *
 *	(b) ग_लिखोs deferred till post-creation (mark page क्रम writing and
 *	    वापस immediately)
 *
 *  (2) negative lookup, object created, initial fill being made from netfs
 *
 *	(a) fill poपूर्णांक not yet reached this page (mark page क्रम writing and
 *          वापस)
 *
 *	(b) fill poपूर्णांक passed this page (queue op to store this page)
 *
 *  (3) object extant (queue op to store this page)
 *
 * any other state is invalid
 */
पूर्णांक __fscache_ग_लिखो_page(काष्ठा fscache_cookie *cookie,
			 काष्ठा page *page,
			 loff_t object_size,
			 gfp_t gfp)
अणु
	काष्ठा fscache_storage *op;
	काष्ठा fscache_object *object;
	bool wake_cookie = false;
	पूर्णांक ret;

	_enter("%p,%x,", cookie, (u32) page->flags);

	ASSERTCMP(cookie->def->type, !=, FSCACHE_COOKIE_TYPE_INDEX);
	ASSERT(PageFsCache(page));

	fscache_stat(&fscache_n_stores);

	अगर (test_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags)) अणु
		_leave(" = -ENOBUFS [invalidating]");
		वापस -ENOBUFS;
	पूर्ण

	op = kzalloc(माप(*op), GFP_NOIO | __GFP_NOMEMALLOC | __GFP_NORETRY);
	अगर (!op)
		जाओ nomem;

	fscache_operation_init(cookie, &op->op, fscache_ग_लिखो_op, शून्य,
			       fscache_release_ग_लिखो_op);
	op->op.flags = FSCACHE_OP_ASYNC |
		(1 << FSCACHE_OP_WAITING) |
		(1 << FSCACHE_OP_UNUSE_COOKIE);

	ret = radix_tree_maybe_preload(gfp & ~__GFP_HIGHMEM);
	अगर (ret < 0)
		जाओ nomem_मुक्त;

	trace_fscache_page_op(cookie, page, &op->op, fscache_page_op_ग_लिखो_one);

	ret = -ENOBUFS;
	spin_lock(&cookie->lock);

	अगर (!fscache_cookie_enabled(cookie) ||
	    hlist_empty(&cookie->backing_objects))
		जाओ nobufs;
	object = hlist_entry(cookie->backing_objects.first,
			     काष्ठा fscache_object, cookie_link);
	अगर (test_bit(FSCACHE_IOERROR, &object->cache->flags))
		जाओ nobufs;

	trace_fscache_page(cookie, page, fscache_page_ग_लिखो);

	/* add the page to the pending-storage radix tree on the backing
	 * object */
	spin_lock(&object->lock);

	अगर (object->store_limit_l != object_size)
		fscache_set_store_limit(object, object_size);

	spin_lock(&cookie->stores_lock);

	_debug("store limit %llx", (अचिन्हित दीर्घ दीर्घ) object->store_limit);

	ret = radix_tree_insert(&cookie->stores, page->index, page);
	अगर (ret < 0) अणु
		अगर (ret == -EEXIST)
			जाओ alपढ़ोy_queued;
		_debug("insert failed %d", ret);
		जाओ nobufs_unlock_obj;
	पूर्ण

	trace_fscache_page(cookie, page, fscache_page_radix_insert);
	radix_tree_tag_set(&cookie->stores, page->index,
			   FSCACHE_COOKIE_PENDING_TAG);
	trace_fscache_page(cookie, page, fscache_page_radix_set_pend);
	get_page(page);

	/* we only want one ग_लिखोr at a समय, but we करो need to queue new
	 * ग_लिखोrs after exclusive ops */
	अगर (test_and_set_bit(FSCACHE_OBJECT_PENDING_WRITE, &object->flags))
		जाओ alपढ़ोy_pending;

	spin_unlock(&cookie->stores_lock);
	spin_unlock(&object->lock);

	op->op.debug_id	= atomic_inc_वापस(&fscache_op_debug_id);
	op->store_limit = object->store_limit;

	__fscache_use_cookie(cookie);
	अगर (fscache_submit_op(object, &op->op) < 0)
		जाओ submit_failed;

	spin_unlock(&cookie->lock);
	radix_tree_preload_end();
	fscache_stat(&fscache_n_store_ops);
	fscache_stat(&fscache_n_stores_ok);

	/* the work queue now carries its own ref on the object */
	fscache_put_operation(&op->op);
	_leave(" = 0");
	वापस 0;

alपढ़ोy_queued:
	fscache_stat(&fscache_n_stores_again);
alपढ़ोy_pending:
	spin_unlock(&cookie->stores_lock);
	spin_unlock(&object->lock);
	spin_unlock(&cookie->lock);
	radix_tree_preload_end();
	fscache_put_operation(&op->op);
	fscache_stat(&fscache_n_stores_ok);
	_leave(" = 0");
	वापस 0;

submit_failed:
	spin_lock(&cookie->stores_lock);
	radix_tree_delete(&cookie->stores, page->index);
	trace_fscache_page(cookie, page, fscache_page_radix_delete);
	spin_unlock(&cookie->stores_lock);
	wake_cookie = __fscache_unuse_cookie(cookie);
	put_page(page);
	ret = -ENOBUFS;
	जाओ nobufs;

nobufs_unlock_obj:
	spin_unlock(&cookie->stores_lock);
	spin_unlock(&object->lock);
nobufs:
	spin_unlock(&cookie->lock);
	radix_tree_preload_end();
	fscache_put_operation(&op->op);
	अगर (wake_cookie)
		__fscache_wake_unused_cookie(cookie);
	fscache_stat(&fscache_n_stores_nobufs);
	_leave(" = -ENOBUFS");
	वापस -ENOBUFS;

nomem_मुक्त:
	fscache_put_operation(&op->op);
nomem:
	fscache_stat(&fscache_n_stores_oom);
	_leave(" = -ENOMEM");
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(__fscache_ग_लिखो_page);

/*
 * हटाओ a page from the cache
 */
व्योम __fscache_uncache_page(काष्ठा fscache_cookie *cookie, काष्ठा page *page)
अणु
	काष्ठा fscache_object *object;

	_enter(",%p", page);

	ASSERTCMP(cookie->def->type, !=, FSCACHE_COOKIE_TYPE_INDEX);
	ASSERTCMP(page, !=, शून्य);

	fscache_stat(&fscache_n_uncaches);

	/* cache withdrawal may beat us to it */
	अगर (!PageFsCache(page))
		जाओ करोne;

	trace_fscache_page(cookie, page, fscache_page_uncache);

	/* get the object */
	spin_lock(&cookie->lock);

	अगर (hlist_empty(&cookie->backing_objects)) अणु
		ClearPageFsCache(page);
		जाओ करोne_unlock;
	पूर्ण

	object = hlist_entry(cookie->backing_objects.first,
			     काष्ठा fscache_object, cookie_link);

	/* there might now be stuff on disk we could पढ़ो */
	clear_bit(FSCACHE_COOKIE_NO_DATA_YET, &cookie->flags);

	/* only invoke the cache backend अगर we managed to mark the page
	 * uncached here; this deals with synchronisation vs withdrawal */
	अगर (TestClearPageFsCache(page) &&
	    object->cache->ops->uncache_page) अणु
		/* the cache backend releases the cookie lock */
		fscache_stat(&fscache_n_cop_uncache_page);
		object->cache->ops->uncache_page(object, page);
		fscache_stat_d(&fscache_n_cop_uncache_page);
		जाओ करोne;
	पूर्ण

करोne_unlock:
	spin_unlock(&cookie->lock);
करोne:
	_leave("");
पूर्ण
EXPORT_SYMBOL(__fscache_uncache_page);

/**
 * fscache_mark_page_cached - Mark a page as being cached
 * @op: The retrieval op pages are being marked क्रम
 * @page: The page to be marked
 *
 * Mark a netfs page as being cached.  After this is called, the netfs
 * must call fscache_uncache_page() to हटाओ the mark.
 */
व्योम fscache_mark_page_cached(काष्ठा fscache_retrieval *op, काष्ठा page *page)
अणु
	काष्ठा fscache_cookie *cookie = op->op.object->cookie;

#अगर_घोषित CONFIG_FSCACHE_STATS
	atomic_inc(&fscache_n_marks);
#पूर्ण_अगर

	trace_fscache_page(cookie, page, fscache_page_cached);

	_debug("- mark %p{%lx}", page, page->index);
	अगर (TestSetPageFsCache(page)) अणु
		अटल bool once_only;
		अगर (!once_only) अणु
			once_only = true;
			pr_warn("Cookie type %s marked page %lx multiple times\n",
				cookie->def->name, page->index);
		पूर्ण
	पूर्ण

	अगर (cookie->def->mark_page_cached)
		cookie->def->mark_page_cached(cookie->netfs_data,
					      op->mapping, page);
पूर्ण
EXPORT_SYMBOL(fscache_mark_page_cached);

/**
 * fscache_mark_pages_cached - Mark pages as being cached
 * @op: The retrieval op pages are being marked क्रम
 * @pagevec: The pages to be marked
 *
 * Mark a bunch of netfs pages as being cached.  After this is called,
 * the netfs must call fscache_uncache_page() to हटाओ the mark.
 */
व्योम fscache_mark_pages_cached(काष्ठा fscache_retrieval *op,
			       काष्ठा pagevec *pagevec)
अणु
	अचिन्हित दीर्घ loop;

	क्रम (loop = 0; loop < pagevec->nr; loop++)
		fscache_mark_page_cached(op, pagevec->pages[loop]);

	pagevec_reinit(pagevec);
पूर्ण
EXPORT_SYMBOL(fscache_mark_pages_cached);

/*
 * Uncache all the pages in an inode that are marked PG_fscache, assuming them
 * to be associated with the given cookie.
 */
व्योम __fscache_uncache_all_inode_pages(काष्ठा fscache_cookie *cookie,
				       काष्ठा inode *inode)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा pagevec pvec;
	pgoff_t next;
	पूर्णांक i;

	_enter("%p,%p", cookie, inode);

	अगर (!mapping || mapping->nrpages == 0) अणु
		_leave(" [no pages]");
		वापस;
	पूर्ण

	pagevec_init(&pvec);
	next = 0;
	करो अणु
		अगर (!pagevec_lookup(&pvec, mapping, &next))
			अवरोध;
		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			काष्ठा page *page = pvec.pages[i];
			अगर (PageFsCache(page)) अणु
				__fscache_रुको_on_page_ग_लिखो(cookie, page);
				__fscache_uncache_page(cookie, page);
			पूर्ण
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण जबतक (next);

	_leave("");
पूर्ण
EXPORT_SYMBOL(__fscache_uncache_all_inode_pages);
