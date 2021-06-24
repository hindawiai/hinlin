<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Cache data I/O routines
 *
 * Copyright (C) 2021 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा FSCACHE_DEBUG_LEVEL PAGE
#समावेश <linux/module.h>
#घोषणा FSCACHE_USE_NEW_IO_API
#समावेश <linux/fscache-cache.h>
#समावेश <linux/slab.h>
#समावेश <linux/netfs.h>
#समावेश "internal.h"

/*
 * Start a cache पढ़ो operation.
 * - we वापस:
 *   -ENOMEM	- out of memory, some pages may be being पढ़ो
 *   -ERESTARTSYS - पूर्णांकerrupted, some pages may be being पढ़ो
 *   -ENOBUFS	- no backing object or space available in which to cache any
 *                pages not being पढ़ो
 *   -ENODATA	- no data available in the backing object क्रम some or all of
 *                the pages
 *   0		- dispatched a पढ़ो on all pages
 */
पूर्णांक __fscache_begin_पढ़ो_operation(काष्ठा netfs_पढ़ो_request *rreq,
				   काष्ठा fscache_cookie *cookie)
अणु
	काष्ठा fscache_retrieval *op;
	काष्ठा fscache_object *object;
	bool wake_cookie = false;
	पूर्णांक ret;

	_enter("rr=%08x", rreq->debug_id);

	fscache_stat(&fscache_n_retrievals);

	अगर (hlist_empty(&cookie->backing_objects))
		जाओ nobufs;

	अगर (test_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags)) अणु
		_leave(" = -ENOBUFS [invalidating]");
		वापस -ENOBUFS;
	पूर्ण

	ASSERTCMP(cookie->def->type, !=, FSCACHE_COOKIE_TYPE_INDEX);

	अगर (fscache_रुको_क्रम_deferred_lookup(cookie) < 0)
		वापस -ERESTARTSYS;

	op = fscache_alloc_retrieval(cookie, शून्य, शून्य, शून्य);
	अगर (!op)
		वापस -ENOMEM;
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
	ret = object->cache->ops->begin_पढ़ो_operation(rreq, op);

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
EXPORT_SYMBOL(__fscache_begin_पढ़ो_operation);
