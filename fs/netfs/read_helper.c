<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Network fileप्रणाली high-level पढ़ो support.
 *
 * Copyright (C) 2021 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/uपन.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/netfs.h>
#समावेश "internal.h"
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/netfs.h>

MODULE_DESCRIPTION("Network fs support");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

अचिन्हित netfs_debug;
module_param_named(debug, netfs_debug, uपूर्णांक, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(netfs_debug, "Netfs support debugging mask");

अटल व्योम netfs_rreq_work(काष्ठा work_काष्ठा *);
अटल व्योम __netfs_put_subrequest(काष्ठा netfs_पढ़ो_subrequest *, bool);

अटल व्योम netfs_put_subrequest(काष्ठा netfs_पढ़ो_subrequest *subreq,
				 bool was_async)
अणु
	अगर (refcount_dec_and_test(&subreq->usage))
		__netfs_put_subrequest(subreq, was_async);
पूर्ण

अटल काष्ठा netfs_पढ़ो_request *netfs_alloc_पढ़ो_request(
	स्थिर काष्ठा netfs_पढ़ो_request_ops *ops, व्योम *netfs_priv,
	काष्ठा file *file)
अणु
	अटल atomic_t debug_ids;
	काष्ठा netfs_पढ़ो_request *rreq;

	rreq = kzalloc(माप(काष्ठा netfs_पढ़ो_request), GFP_KERNEL);
	अगर (rreq) अणु
		rreq->netfs_ops	= ops;
		rreq->netfs_priv = netfs_priv;
		rreq->inode	= file_inode(file);
		rreq->i_size	= i_size_पढ़ो(rreq->inode);
		rreq->debug_id	= atomic_inc_वापस(&debug_ids);
		INIT_LIST_HEAD(&rreq->subrequests);
		INIT_WORK(&rreq->work, netfs_rreq_work);
		refcount_set(&rreq->usage, 1);
		__set_bit(NETFS_RREQ_IN_PROGRESS, &rreq->flags);
		ops->init_rreq(rreq, file);
		netfs_stat(&netfs_n_rh_rreq);
	पूर्ण

	वापस rreq;
पूर्ण

अटल व्योम netfs_get_पढ़ो_request(काष्ठा netfs_पढ़ो_request *rreq)
अणु
	refcount_inc(&rreq->usage);
पूर्ण

अटल व्योम netfs_rreq_clear_subreqs(काष्ठा netfs_पढ़ो_request *rreq,
				     bool was_async)
अणु
	काष्ठा netfs_पढ़ो_subrequest *subreq;

	जबतक (!list_empty(&rreq->subrequests)) अणु
		subreq = list_first_entry(&rreq->subrequests,
					  काष्ठा netfs_पढ़ो_subrequest, rreq_link);
		list_del(&subreq->rreq_link);
		netfs_put_subrequest(subreq, was_async);
	पूर्ण
पूर्ण

अटल व्योम netfs_मुक्त_पढ़ो_request(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netfs_पढ़ो_request *rreq =
		container_of(work, काष्ठा netfs_पढ़ो_request, work);
	netfs_rreq_clear_subreqs(rreq, false);
	अगर (rreq->netfs_priv)
		rreq->netfs_ops->cleanup(rreq->mapping, rreq->netfs_priv);
	trace_netfs_rreq(rreq, netfs_rreq_trace_मुक्त);
	अगर (rreq->cache_resources.ops)
		rreq->cache_resources.ops->end_operation(&rreq->cache_resources);
	kमुक्त(rreq);
	netfs_stat_d(&netfs_n_rh_rreq);
पूर्ण

अटल व्योम netfs_put_पढ़ो_request(काष्ठा netfs_पढ़ो_request *rreq, bool was_async)
अणु
	अगर (refcount_dec_and_test(&rreq->usage)) अणु
		अगर (was_async) अणु
			rreq->work.func = netfs_मुक्त_पढ़ो_request;
			अगर (!queue_work(प्रणाली_unbound_wq, &rreq->work))
				BUG();
		पूर्ण अन्यथा अणु
			netfs_मुक्त_पढ़ो_request(&rreq->work);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Allocate and partially initialise an I/O request काष्ठाure.
 */
अटल काष्ठा netfs_पढ़ो_subrequest *netfs_alloc_subrequest(
	काष्ठा netfs_पढ़ो_request *rreq)
अणु
	काष्ठा netfs_पढ़ो_subrequest *subreq;

	subreq = kzalloc(माप(काष्ठा netfs_पढ़ो_subrequest), GFP_KERNEL);
	अगर (subreq) अणु
		INIT_LIST_HEAD(&subreq->rreq_link);
		refcount_set(&subreq->usage, 2);
		subreq->rreq = rreq;
		netfs_get_पढ़ो_request(rreq);
		netfs_stat(&netfs_n_rh_sreq);
	पूर्ण

	वापस subreq;
पूर्ण

अटल व्योम netfs_get_पढ़ो_subrequest(काष्ठा netfs_पढ़ो_subrequest *subreq)
अणु
	refcount_inc(&subreq->usage);
पूर्ण

अटल व्योम __netfs_put_subrequest(काष्ठा netfs_पढ़ो_subrequest *subreq,
				   bool was_async)
अणु
	काष्ठा netfs_पढ़ो_request *rreq = subreq->rreq;

	trace_netfs_sreq(subreq, netfs_sreq_trace_मुक्त);
	kमुक्त(subreq);
	netfs_stat_d(&netfs_n_rh_sreq);
	netfs_put_पढ़ो_request(rreq, was_async);
पूर्ण

/*
 * Clear the unपढ़ो part of an I/O request.
 */
अटल व्योम netfs_clear_unपढ़ो(काष्ठा netfs_पढ़ो_subrequest *subreq)
अणु
	काष्ठा iov_iter iter;

	iov_iter_xarray(&iter, WRITE, &subreq->rreq->mapping->i_pages,
			subreq->start + subreq->transferred,
			subreq->len   - subreq->transferred);
	iov_iter_zero(iov_iter_count(&iter), &iter);
पूर्ण

अटल व्योम netfs_cache_पढ़ो_terminated(व्योम *priv, sमाप_प्रकार transferred_or_error,
					bool was_async)
अणु
	काष्ठा netfs_पढ़ो_subrequest *subreq = priv;

	netfs_subreq_terminated(subreq, transferred_or_error, was_async);
पूर्ण

/*
 * Issue a पढ़ो against the cache.
 * - Eats the caller's ref on subreq.
 */
अटल व्योम netfs_पढ़ो_from_cache(काष्ठा netfs_पढ़ो_request *rreq,
				  काष्ठा netfs_पढ़ो_subrequest *subreq,
				  bool seek_data)
अणु
	काष्ठा netfs_cache_resources *cres = &rreq->cache_resources;
	काष्ठा iov_iter iter;

	netfs_stat(&netfs_n_rh_पढ़ो);
	iov_iter_xarray(&iter, READ, &rreq->mapping->i_pages,
			subreq->start + subreq->transferred,
			subreq->len   - subreq->transferred);

	cres->ops->पढ़ो(cres, subreq->start, &iter, seek_data,
			netfs_cache_पढ़ो_terminated, subreq);
पूर्ण

/*
 * Fill a subrequest region with zeroes.
 */
अटल व्योम netfs_fill_with_zeroes(काष्ठा netfs_पढ़ो_request *rreq,
				   काष्ठा netfs_पढ़ो_subrequest *subreq)
अणु
	netfs_stat(&netfs_n_rh_zero);
	__set_bit(NETFS_SREQ_CLEAR_TAIL, &subreq->flags);
	netfs_subreq_terminated(subreq, 0, false);
पूर्ण

/*
 * Ask the netfs to issue a पढ़ो request to the server क्रम us.
 *
 * The netfs is expected to पढ़ो from subreq->pos + subreq->transferred to
 * subreq->pos + subreq->len - 1.  It may not backtrack and ग_लिखो data पूर्णांकo the
 * buffer prior to the transferred poपूर्णांक as it might clobber dirty data
 * obtained from the cache.
 *
 * Alternatively, the netfs is allowed to indicate one of two things:
 *
 * - NETFS_SREQ_SHORT_READ: A लघु पढ़ो - it will get called again to try and
 *   make progress.
 *
 * - NETFS_SREQ_CLEAR_TAIL: A लघु पढ़ो - the rest of the buffer will be
 *   cleared.
 */
अटल व्योम netfs_पढ़ो_from_server(काष्ठा netfs_पढ़ो_request *rreq,
				   काष्ठा netfs_पढ़ो_subrequest *subreq)
अणु
	netfs_stat(&netfs_n_rh_करोwnload);
	rreq->netfs_ops->issue_op(subreq);
पूर्ण

/*
 * Release those रुकोing.
 */
अटल व्योम netfs_rreq_completed(काष्ठा netfs_पढ़ो_request *rreq, bool was_async)
अणु
	trace_netfs_rreq(rreq, netfs_rreq_trace_करोne);
	netfs_rreq_clear_subreqs(rreq, was_async);
	netfs_put_पढ़ो_request(rreq, was_async);
पूर्ण

/*
 * Deal with the completion of writing the data to the cache.  We have to clear
 * the PG_fscache bits on the pages involved and release the caller's ref.
 *
 * May be called in softirq mode and we inherit a ref from the caller.
 */
अटल व्योम netfs_rreq_unmark_after_ग_लिखो(काष्ठा netfs_पढ़ो_request *rreq,
					  bool was_async)
अणु
	काष्ठा netfs_पढ़ो_subrequest *subreq;
	काष्ठा page *page;
	pgoff_t unlocked = 0;
	bool have_unlocked = false;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry(subreq, &rreq->subrequests, rreq_link) अणु
		XA_STATE(xas, &rreq->mapping->i_pages, subreq->start / PAGE_SIZE);

		xas_क्रम_each(&xas, page, (subreq->start + subreq->len - 1) / PAGE_SIZE) अणु
			/* We might have multiple ग_लिखोs from the same huge
			 * page, but we mustn't unlock a page more than once.
			 */
			अगर (have_unlocked && page->index <= unlocked)
				जारी;
			unlocked = page->index;
			end_page_fscache(page);
			have_unlocked = true;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	netfs_rreq_completed(rreq, was_async);
पूर्ण

अटल व्योम netfs_rreq_copy_terminated(व्योम *priv, sमाप_प्रकार transferred_or_error,
				       bool was_async)
अणु
	काष्ठा netfs_पढ़ो_subrequest *subreq = priv;
	काष्ठा netfs_पढ़ो_request *rreq = subreq->rreq;

	अगर (IS_ERR_VALUE(transferred_or_error)) अणु
		netfs_stat(&netfs_n_rh_ग_लिखो_failed);
		trace_netfs_failure(rreq, subreq, transferred_or_error,
				    netfs_fail_copy_to_cache);
	पूर्ण अन्यथा अणु
		netfs_stat(&netfs_n_rh_ग_लिखो_करोne);
	पूर्ण

	trace_netfs_sreq(subreq, netfs_sreq_trace_ग_लिखो_term);

	/* If we decrement nr_wr_ops to 0, the ref beदीर्घs to us. */
	अगर (atomic_dec_and_test(&rreq->nr_wr_ops))
		netfs_rreq_unmark_after_ग_लिखो(rreq, was_async);

	netfs_put_subrequest(subreq, was_async);
पूर्ण

/*
 * Perक्रमm any outstanding ग_लिखोs to the cache.  We inherit a ref from the
 * caller.
 */
अटल व्योम netfs_rreq_करो_ग_लिखो_to_cache(काष्ठा netfs_पढ़ो_request *rreq)
अणु
	काष्ठा netfs_cache_resources *cres = &rreq->cache_resources;
	काष्ठा netfs_पढ़ो_subrequest *subreq, *next, *p;
	काष्ठा iov_iter iter;
	पूर्णांक ret;

	trace_netfs_rreq(rreq, netfs_rreq_trace_ग_लिखो);

	/* We करोn't want terminating writes trying to wake us up whilst we're
	 * still going through the list.
	 */
	atomic_inc(&rreq->nr_wr_ops);

	list_क्रम_each_entry_safe(subreq, p, &rreq->subrequests, rreq_link) अणु
		अगर (!test_bit(NETFS_SREQ_WRITE_TO_CACHE, &subreq->flags)) अणु
			list_del_init(&subreq->rreq_link);
			netfs_put_subrequest(subreq, false);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(subreq, &rreq->subrequests, rreq_link) अणु
		/* Amalgamate adjacent ग_लिखोs */
		जबतक (!list_is_last(&subreq->rreq_link, &rreq->subrequests)) अणु
			next = list_next_entry(subreq, rreq_link);
			अगर (next->start != subreq->start + subreq->len)
				अवरोध;
			subreq->len += next->len;
			list_del_init(&next->rreq_link);
			netfs_put_subrequest(next, false);
		पूर्ण

		ret = cres->ops->prepare_ग_लिखो(cres, &subreq->start, &subreq->len,
					       rreq->i_size);
		अगर (ret < 0) अणु
			trace_netfs_failure(rreq, subreq, ret, netfs_fail_prepare_ग_लिखो);
			trace_netfs_sreq(subreq, netfs_sreq_trace_ग_लिखो_skip);
			जारी;
		पूर्ण

		iov_iter_xarray(&iter, WRITE, &rreq->mapping->i_pages,
				subreq->start, subreq->len);

		atomic_inc(&rreq->nr_wr_ops);
		netfs_stat(&netfs_n_rh_ग_लिखो);
		netfs_get_पढ़ो_subrequest(subreq);
		trace_netfs_sreq(subreq, netfs_sreq_trace_ग_लिखो);
		cres->ops->ग_लिखो(cres, subreq->start, &iter,
				 netfs_rreq_copy_terminated, subreq);
	पूर्ण

	/* If we decrement nr_wr_ops to 0, the usage ref beदीर्घs to us. */
	अगर (atomic_dec_and_test(&rreq->nr_wr_ops))
		netfs_rreq_unmark_after_ग_लिखो(rreq, false);
पूर्ण

अटल व्योम netfs_rreq_ग_लिखो_to_cache_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netfs_पढ़ो_request *rreq =
		container_of(work, काष्ठा netfs_पढ़ो_request, work);

	netfs_rreq_करो_ग_लिखो_to_cache(rreq);
पूर्ण

अटल व्योम netfs_rreq_ग_लिखो_to_cache(काष्ठा netfs_पढ़ो_request *rreq,
				      bool was_async)
अणु
	अगर (was_async) अणु
		rreq->work.func = netfs_rreq_ग_लिखो_to_cache_work;
		अगर (!queue_work(प्रणाली_unbound_wq, &rreq->work))
			BUG();
	पूर्ण अन्यथा अणु
		netfs_rreq_करो_ग_लिखो_to_cache(rreq);
	पूर्ण
पूर्ण

/*
 * Unlock the pages in a पढ़ो operation.  We need to set PG_fscache on any
 * pages we're going to ग_लिखो back beक्रमe we unlock them.
 */
अटल व्योम netfs_rreq_unlock(काष्ठा netfs_पढ़ो_request *rreq)
अणु
	काष्ठा netfs_पढ़ो_subrequest *subreq;
	काष्ठा page *page;
	अचिन्हित पूर्णांक iopos, account = 0;
	pgoff_t start_page = rreq->start / PAGE_SIZE;
	pgoff_t last_page = ((rreq->start + rreq->len) / PAGE_SIZE) - 1;
	bool subreq_failed = false;
	पूर्णांक i;

	XA_STATE(xas, &rreq->mapping->i_pages, start_page);

	अगर (test_bit(NETFS_RREQ_FAILED, &rreq->flags)) अणु
		__clear_bit(NETFS_RREQ_WRITE_TO_CACHE, &rreq->flags);
		list_क्रम_each_entry(subreq, &rreq->subrequests, rreq_link) अणु
			__clear_bit(NETFS_SREQ_WRITE_TO_CACHE, &subreq->flags);
		पूर्ण
	पूर्ण

	/* Walk through the pagecache and the I/O request lists simultaneously.
	 * We may have a mixture of cached and uncached sections and we only
	 * really want to ग_लिखो out the uncached sections.  This is slightly
	 * complicated by the possibility that we might have huge pages with a
	 * mixture inside.
	 */
	subreq = list_first_entry(&rreq->subrequests,
				  काष्ठा netfs_पढ़ो_subrequest, rreq_link);
	iopos = 0;
	subreq_failed = (subreq->error < 0);

	trace_netfs_rreq(rreq, netfs_rreq_trace_unlock);

	rcu_पढ़ो_lock();
	xas_क्रम_each(&xas, page, last_page) अणु
		अचिन्हित पूर्णांक pgpos = (page->index - start_page) * PAGE_SIZE;
		अचिन्हित पूर्णांक pgend = pgpos + thp_size(page);
		bool pg_failed = false;

		क्रम (;;) अणु
			अगर (!subreq) अणु
				pg_failed = true;
				अवरोध;
			पूर्ण
			अगर (test_bit(NETFS_SREQ_WRITE_TO_CACHE, &subreq->flags))
				set_page_fscache(page);
			pg_failed |= subreq_failed;
			अगर (pgend < iopos + subreq->len)
				अवरोध;

			account += subreq->transferred;
			iopos += subreq->len;
			अगर (!list_is_last(&subreq->rreq_link, &rreq->subrequests)) अणु
				subreq = list_next_entry(subreq, rreq_link);
				subreq_failed = (subreq->error < 0);
			पूर्ण अन्यथा अणु
				subreq = शून्य;
				subreq_failed = false;
			पूर्ण
			अगर (pgend == iopos)
				अवरोध;
		पूर्ण

		अगर (!pg_failed) अणु
			क्रम (i = 0; i < thp_nr_pages(page); i++)
				flush_dcache_page(page);
			SetPageUptodate(page);
		पूर्ण

		अगर (!test_bit(NETFS_RREQ_DONT_UNLOCK_PAGES, &rreq->flags)) अणु
			अगर (page->index == rreq->no_unlock_page &&
			    test_bit(NETFS_RREQ_NO_UNLOCK_PAGE, &rreq->flags))
				_debug("no unlock");
			अन्यथा
				unlock_page(page);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	task_io_account_पढ़ो(account);
	अगर (rreq->netfs_ops->करोne)
		rreq->netfs_ops->करोne(rreq);
पूर्ण

/*
 * Handle a लघु पढ़ो.
 */
अटल व्योम netfs_rreq_लघु_पढ़ो(काष्ठा netfs_पढ़ो_request *rreq,
				  काष्ठा netfs_पढ़ो_subrequest *subreq)
अणु
	__clear_bit(NETFS_SREQ_SHORT_READ, &subreq->flags);
	__set_bit(NETFS_SREQ_SEEK_DATA_READ, &subreq->flags);

	netfs_stat(&netfs_n_rh_लघु_पढ़ो);
	trace_netfs_sreq(subreq, netfs_sreq_trace_resubmit_लघु);

	netfs_get_पढ़ो_subrequest(subreq);
	atomic_inc(&rreq->nr_rd_ops);
	अगर (subreq->source == NETFS_READ_FROM_CACHE)
		netfs_पढ़ो_from_cache(rreq, subreq, true);
	अन्यथा
		netfs_पढ़ो_from_server(rreq, subreq);
पूर्ण

/*
 * Resubmit any लघु or failed operations.  Returns true अगर we got the rreq
 * ref back.
 */
अटल bool netfs_rreq_perक्रमm_resubmissions(काष्ठा netfs_पढ़ो_request *rreq)
अणु
	काष्ठा netfs_पढ़ो_subrequest *subreq;

	WARN_ON(in_पूर्णांकerrupt());

	trace_netfs_rreq(rreq, netfs_rreq_trace_resubmit);

	/* We करोn't want terminating submissions trying to wake us up whilst
	 * we're still going through the list.
	 */
	atomic_inc(&rreq->nr_rd_ops);

	__clear_bit(NETFS_RREQ_INCOMPLETE_IO, &rreq->flags);
	list_क्रम_each_entry(subreq, &rreq->subrequests, rreq_link) अणु
		अगर (subreq->error) अणु
			अगर (subreq->source != NETFS_READ_FROM_CACHE)
				अवरोध;
			subreq->source = NETFS_DOWNLOAD_FROM_SERVER;
			subreq->error = 0;
			netfs_stat(&netfs_n_rh_करोwnload_instead);
			trace_netfs_sreq(subreq, netfs_sreq_trace_करोwnload_instead);
			netfs_get_पढ़ो_subrequest(subreq);
			atomic_inc(&rreq->nr_rd_ops);
			netfs_पढ़ो_from_server(rreq, subreq);
		पूर्ण अन्यथा अगर (test_bit(NETFS_SREQ_SHORT_READ, &subreq->flags)) अणु
			netfs_rreq_लघु_पढ़ो(rreq, subreq);
		पूर्ण
	पूर्ण

	/* If we decrement nr_rd_ops to 0, the usage ref beदीर्घs to us. */
	अगर (atomic_dec_and_test(&rreq->nr_rd_ops))
		वापस true;

	wake_up_var(&rreq->nr_rd_ops);
	वापस false;
पूर्ण

/*
 * Check to see अगर the data पढ़ो is still valid.
 */
अटल व्योम netfs_rreq_is_still_valid(काष्ठा netfs_पढ़ो_request *rreq)
अणु
	काष्ठा netfs_पढ़ो_subrequest *subreq;

	अगर (!rreq->netfs_ops->is_still_valid ||
	    rreq->netfs_ops->is_still_valid(rreq))
		वापस;

	list_क्रम_each_entry(subreq, &rreq->subrequests, rreq_link) अणु
		अगर (subreq->source == NETFS_READ_FROM_CACHE) अणु
			subreq->error = -ESTALE;
			__set_bit(NETFS_RREQ_INCOMPLETE_IO, &rreq->flags);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Assess the state of a पढ़ो request and decide what to करो next.
 *
 * Note that we could be in an ordinary kernel thपढ़ो, on a workqueue or in
 * softirq context at this poपूर्णांक.  We inherit a ref from the caller.
 */
अटल व्योम netfs_rreq_assess(काष्ठा netfs_पढ़ो_request *rreq, bool was_async)
अणु
	trace_netfs_rreq(rreq, netfs_rreq_trace_assess);

again:
	netfs_rreq_is_still_valid(rreq);

	अगर (!test_bit(NETFS_RREQ_FAILED, &rreq->flags) &&
	    test_bit(NETFS_RREQ_INCOMPLETE_IO, &rreq->flags)) अणु
		अगर (netfs_rreq_perक्रमm_resubmissions(rreq))
			जाओ again;
		वापस;
	पूर्ण

	netfs_rreq_unlock(rreq);

	clear_bit_unlock(NETFS_RREQ_IN_PROGRESS, &rreq->flags);
	wake_up_bit(&rreq->flags, NETFS_RREQ_IN_PROGRESS);

	अगर (test_bit(NETFS_RREQ_WRITE_TO_CACHE, &rreq->flags))
		वापस netfs_rreq_ग_लिखो_to_cache(rreq, was_async);

	netfs_rreq_completed(rreq, was_async);
पूर्ण

अटल व्योम netfs_rreq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netfs_पढ़ो_request *rreq =
		container_of(work, काष्ठा netfs_पढ़ो_request, work);
	netfs_rreq_assess(rreq, false);
पूर्ण

/*
 * Handle the completion of all outstanding I/O operations on a पढ़ो request.
 * We inherit a ref from the caller.
 */
अटल व्योम netfs_rreq_terminated(काष्ठा netfs_पढ़ो_request *rreq,
				  bool was_async)
अणु
	अगर (test_bit(NETFS_RREQ_INCOMPLETE_IO, &rreq->flags) &&
	    was_async) अणु
		अगर (!queue_work(प्रणाली_unbound_wq, &rreq->work))
			BUG();
	पूर्ण अन्यथा अणु
		netfs_rreq_assess(rreq, was_async);
	पूर्ण
पूर्ण

/**
 * netfs_subreq_terminated - Note the termination of an I/O operation.
 * @subreq: The I/O request that has terminated.
 * @transferred_or_error: The amount of data transferred or an error code.
 * @was_async: The termination was asynchronous
 *
 * This tells the पढ़ो helper that a contributory I/O operation has terminated,
 * one way or another, and that it should पूर्णांकegrate the results.
 *
 * The caller indicates in @transferred_or_error the outcome of the operation,
 * supplying a positive value to indicate the number of bytes transferred, 0 to
 * indicate a failure to transfer anything that should be retried or a negative
 * error code.  The helper will look after reissuing I/O operations as
 * appropriate and writing करोwnloaded data to the cache.
 *
 * If @was_async is true, the caller might be running in softirq or पूर्णांकerrupt
 * context and we can't sleep.
 */
व्योम netfs_subreq_terminated(काष्ठा netfs_पढ़ो_subrequest *subreq,
			     sमाप_प्रकार transferred_or_error,
			     bool was_async)
अणु
	काष्ठा netfs_पढ़ो_request *rreq = subreq->rreq;
	पूर्णांक u;

	_enter("[%u]{%llx,%lx},%zd",
	       subreq->debug_index, subreq->start, subreq->flags,
	       transferred_or_error);

	चयन (subreq->source) अणु
	हाल NETFS_READ_FROM_CACHE:
		netfs_stat(&netfs_n_rh_पढ़ो_करोne);
		अवरोध;
	हाल NETFS_DOWNLOAD_FROM_SERVER:
		netfs_stat(&netfs_n_rh_करोwnload_करोne);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (IS_ERR_VALUE(transferred_or_error)) अणु
		subreq->error = transferred_or_error;
		trace_netfs_failure(rreq, subreq, transferred_or_error,
				    netfs_fail_पढ़ो);
		जाओ failed;
	पूर्ण

	अगर (WARN(transferred_or_error > subreq->len - subreq->transferred,
		 "Subreq overread: R%x[%x] %zd > %zu - %zu",
		 rreq->debug_id, subreq->debug_index,
		 transferred_or_error, subreq->len, subreq->transferred))
		transferred_or_error = subreq->len - subreq->transferred;

	subreq->error = 0;
	subreq->transferred += transferred_or_error;
	अगर (subreq->transferred < subreq->len)
		जाओ incomplete;

complete:
	__clear_bit(NETFS_SREQ_NO_PROGRESS, &subreq->flags);
	अगर (test_bit(NETFS_SREQ_WRITE_TO_CACHE, &subreq->flags))
		set_bit(NETFS_RREQ_WRITE_TO_CACHE, &rreq->flags);

out:
	trace_netfs_sreq(subreq, netfs_sreq_trace_terminated);

	/* If we decrement nr_rd_ops to 0, the ref beदीर्घs to us. */
	u = atomic_dec_वापस(&rreq->nr_rd_ops);
	अगर (u == 0)
		netfs_rreq_terminated(rreq, was_async);
	अन्यथा अगर (u == 1)
		wake_up_var(&rreq->nr_rd_ops);

	netfs_put_subrequest(subreq, was_async);
	वापस;

incomplete:
	अगर (test_bit(NETFS_SREQ_CLEAR_TAIL, &subreq->flags)) अणु
		netfs_clear_unपढ़ो(subreq);
		subreq->transferred = subreq->len;
		जाओ complete;
	पूर्ण

	अगर (transferred_or_error == 0) अणु
		अगर (__test_and_set_bit(NETFS_SREQ_NO_PROGRESS, &subreq->flags)) अणु
			subreq->error = -ENODATA;
			जाओ failed;
		पूर्ण
	पूर्ण अन्यथा अणु
		__clear_bit(NETFS_SREQ_NO_PROGRESS, &subreq->flags);
	पूर्ण

	__set_bit(NETFS_SREQ_SHORT_READ, &subreq->flags);
	set_bit(NETFS_RREQ_INCOMPLETE_IO, &rreq->flags);
	जाओ out;

failed:
	अगर (subreq->source == NETFS_READ_FROM_CACHE) अणु
		netfs_stat(&netfs_n_rh_पढ़ो_failed);
		set_bit(NETFS_RREQ_INCOMPLETE_IO, &rreq->flags);
	पूर्ण अन्यथा अणु
		netfs_stat(&netfs_n_rh_करोwnload_failed);
		set_bit(NETFS_RREQ_FAILED, &rreq->flags);
		rreq->error = subreq->error;
	पूर्ण
	जाओ out;
पूर्ण
EXPORT_SYMBOL(netfs_subreq_terminated);

अटल क्रमागत netfs_पढ़ो_source netfs_cache_prepare_पढ़ो(काष्ठा netfs_पढ़ो_subrequest *subreq,
						       loff_t i_size)
अणु
	काष्ठा netfs_पढ़ो_request *rreq = subreq->rreq;
	काष्ठा netfs_cache_resources *cres = &rreq->cache_resources;

	अगर (cres->ops)
		वापस cres->ops->prepare_पढ़ो(subreq, i_size);
	अगर (subreq->start >= rreq->i_size)
		वापस NETFS_FILL_WITH_ZEROES;
	वापस NETFS_DOWNLOAD_FROM_SERVER;
पूर्ण

/*
 * Work out what sort of subrequest the next one will be.
 */
अटल क्रमागत netfs_पढ़ो_source
netfs_rreq_prepare_पढ़ो(काष्ठा netfs_पढ़ो_request *rreq,
			काष्ठा netfs_पढ़ो_subrequest *subreq)
अणु
	क्रमागत netfs_पढ़ो_source source;

	_enter("%llx-%llx,%llx", subreq->start, subreq->start + subreq->len, rreq->i_size);

	source = netfs_cache_prepare_पढ़ो(subreq, rreq->i_size);
	अगर (source == NETFS_INVALID_READ)
		जाओ out;

	अगर (source == NETFS_DOWNLOAD_FROM_SERVER) अणु
		/* Call out to the netfs to let it shrink the request to fit
		 * its own I/O sizes and boundaries.  If it shinks it here, it
		 * will be called again to make simultaneous calls; अगर it wants
		 * to make serial calls, it can indicate a लघु पढ़ो and then
		 * we will call it again.
		 */
		अगर (subreq->len > rreq->i_size - subreq->start)
			subreq->len = rreq->i_size - subreq->start;

		अगर (rreq->netfs_ops->clamp_length &&
		    !rreq->netfs_ops->clamp_length(subreq)) अणु
			source = NETFS_INVALID_READ;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(subreq->len == 0))
		source = NETFS_INVALID_READ;

out:
	subreq->source = source;
	trace_netfs_sreq(subreq, netfs_sreq_trace_prepare);
	वापस source;
पूर्ण

/*
 * Slice off a piece of a पढ़ो request and submit an I/O request क्रम it.
 */
अटल bool netfs_rreq_submit_slice(काष्ठा netfs_पढ़ो_request *rreq,
				    अचिन्हित पूर्णांक *_debug_index)
अणु
	काष्ठा netfs_पढ़ो_subrequest *subreq;
	क्रमागत netfs_पढ़ो_source source;

	subreq = netfs_alloc_subrequest(rreq);
	अगर (!subreq)
		वापस false;

	subreq->debug_index	= (*_debug_index)++;
	subreq->start		= rreq->start + rreq->submitted;
	subreq->len		= rreq->len   - rreq->submitted;

	_debug("slice %llx,%zx,%zx", subreq->start, subreq->len, rreq->submitted);
	list_add_tail(&subreq->rreq_link, &rreq->subrequests);

	/* Call out to the cache to find out what it can करो with the reमुख्यing
	 * subset.  It tells us in subreq->flags what it decided should be करोne
	 * and adjusts subreq->len करोwn अगर the subset crosses a cache boundary.
	 *
	 * Then when we hand the subset, it can choose to take a subset of that
	 * (the starts must coincide), in which हाल, we go around the loop
	 * again and ask it to करोwnload the next piece.
	 */
	source = netfs_rreq_prepare_पढ़ो(rreq, subreq);
	अगर (source == NETFS_INVALID_READ)
		जाओ subreq_failed;

	atomic_inc(&rreq->nr_rd_ops);

	rreq->submitted += subreq->len;

	trace_netfs_sreq(subreq, netfs_sreq_trace_submit);
	चयन (source) अणु
	हाल NETFS_FILL_WITH_ZEROES:
		netfs_fill_with_zeroes(rreq, subreq);
		अवरोध;
	हाल NETFS_DOWNLOAD_FROM_SERVER:
		netfs_पढ़ो_from_server(rreq, subreq);
		अवरोध;
	हाल NETFS_READ_FROM_CACHE:
		netfs_पढ़ो_from_cache(rreq, subreq, false);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस true;

subreq_failed:
	rreq->error = subreq->error;
	netfs_put_subrequest(subreq, false);
	वापस false;
पूर्ण

अटल व्योम netfs_cache_expand_पढ़ोahead(काष्ठा netfs_पढ़ो_request *rreq,
					 loff_t *_start, माप_प्रकार *_len, loff_t i_size)
अणु
	काष्ठा netfs_cache_resources *cres = &rreq->cache_resources;

	अगर (cres->ops && cres->ops->expand_पढ़ोahead)
		cres->ops->expand_पढ़ोahead(cres, _start, _len, i_size);
पूर्ण

अटल व्योम netfs_rreq_expand(काष्ठा netfs_पढ़ो_request *rreq,
			      काष्ठा पढ़ोahead_control *ractl)
अणु
	/* Give the cache a chance to change the request parameters.  The
	 * resultant request must contain the original region.
	 */
	netfs_cache_expand_पढ़ोahead(rreq, &rreq->start, &rreq->len, rreq->i_size);

	/* Give the netfs a chance to change the request parameters.  The
	 * resultant request must contain the original region.
	 */
	अगर (rreq->netfs_ops->expand_पढ़ोahead)
		rreq->netfs_ops->expand_पढ़ोahead(rreq);

	/* Expand the request अगर the cache wants it to start earlier.  Note
	 * that the expansion may get further extended अगर the VM wishes to
	 * insert THPs and the preferred start and/or end wind up in the middle
	 * of THPs.
	 *
	 * If this is the हाल, however, the THP size should be an पूर्णांकeger
	 * multiple of the cache granule size, so we get a whole number of
	 * granules to deal with.
	 */
	अगर (rreq->start  != पढ़ोahead_pos(ractl) ||
	    rreq->len != पढ़ोahead_length(ractl)) अणु
		पढ़ोahead_expand(ractl, rreq->start, rreq->len);
		rreq->start  = पढ़ोahead_pos(ractl);
		rreq->len = पढ़ोahead_length(ractl);

		trace_netfs_पढ़ो(rreq, पढ़ोahead_pos(ractl), पढ़ोahead_length(ractl),
				 netfs_पढ़ो_trace_expanded);
	पूर्ण
पूर्ण

/**
 * netfs_पढ़ोahead - Helper to manage a पढ़ो request
 * @ractl: The description of the पढ़ोahead request
 * @ops: The network fileप्रणाली's operations क्रम the helper to use
 * @netfs_priv: Private netfs data to be retained in the request
 *
 * Fulfil a पढ़ोahead request by drawing data from the cache अगर possible, or
 * the netfs अगर not.  Space beyond the खातापूर्ण is zero-filled.  Multiple I/O
 * requests from dअगरferent sources will get munged together.  If necessary, the
 * पढ़ोahead winकरोw can be expanded in either direction to a more convenient
 * alighment क्रम RPC efficiency or to make storage in the cache feasible.
 *
 * The calling netfs must provide a table of operations, only one of which,
 * issue_op, is mandatory.  It may also be passed a निजी token, which will
 * be retained in rreq->netfs_priv and will be cleaned up by ops->cleanup().
 *
 * This is usable whether or not caching is enabled.
 */
व्योम netfs_पढ़ोahead(काष्ठा पढ़ोahead_control *ractl,
		     स्थिर काष्ठा netfs_पढ़ो_request_ops *ops,
		     व्योम *netfs_priv)
अणु
	काष्ठा netfs_पढ़ो_request *rreq;
	काष्ठा page *page;
	अचिन्हित पूर्णांक debug_index = 0;
	पूर्णांक ret;

	_enter("%lx,%x", पढ़ोahead_index(ractl), पढ़ोahead_count(ractl));

	अगर (पढ़ोahead_count(ractl) == 0)
		जाओ cleanup;

	rreq = netfs_alloc_पढ़ो_request(ops, netfs_priv, ractl->file);
	अगर (!rreq)
		जाओ cleanup;
	rreq->mapping	= ractl->mapping;
	rreq->start	= पढ़ोahead_pos(ractl);
	rreq->len	= पढ़ोahead_length(ractl);

	अगर (ops->begin_cache_operation) अणु
		ret = ops->begin_cache_operation(rreq);
		अगर (ret == -ENOMEM || ret == -EINTR || ret == -ERESTARTSYS)
			जाओ cleanup_मुक्त;
	पूर्ण

	netfs_stat(&netfs_n_rh_पढ़ोahead);
	trace_netfs_पढ़ो(rreq, पढ़ोahead_pos(ractl), पढ़ोahead_length(ractl),
			 netfs_पढ़ो_trace_पढ़ोahead);

	netfs_rreq_expand(rreq, ractl);

	atomic_set(&rreq->nr_rd_ops, 1);
	करो अणु
		अगर (!netfs_rreq_submit_slice(rreq, &debug_index))
			अवरोध;

	पूर्ण जबतक (rreq->submitted < rreq->len);

	/* Drop the refs on the pages here rather than in the cache or
	 * fileप्रणाली.  The locks will be dropped in netfs_rreq_unlock().
	 */
	जबतक ((page = पढ़ोahead_page(ractl)))
		put_page(page);

	/* If we decrement nr_rd_ops to 0, the ref beदीर्घs to us. */
	अगर (atomic_dec_and_test(&rreq->nr_rd_ops))
		netfs_rreq_assess(rreq, false);
	वापस;

cleanup_मुक्त:
	netfs_put_पढ़ो_request(rreq, false);
	वापस;
cleanup:
	अगर (netfs_priv)
		ops->cleanup(ractl->mapping, netfs_priv);
	वापस;
पूर्ण
EXPORT_SYMBOL(netfs_पढ़ोahead);

/**
 * netfs_पढ़ोpage - Helper to manage a पढ़ोpage request
 * @file: The file to पढ़ो from
 * @page: The page to पढ़ो
 * @ops: The network fileप्रणाली's operations क्रम the helper to use
 * @netfs_priv: Private netfs data to be retained in the request
 *
 * Fulfil a पढ़ोpage request by drawing data from the cache अगर possible, or the
 * netfs अगर not.  Space beyond the खातापूर्ण is zero-filled.  Multiple I/O requests
 * from dअगरferent sources will get munged together.
 *
 * The calling netfs must provide a table of operations, only one of which,
 * issue_op, is mandatory.  It may also be passed a निजी token, which will
 * be retained in rreq->netfs_priv and will be cleaned up by ops->cleanup().
 *
 * This is usable whether or not caching is enabled.
 */
पूर्णांक netfs_पढ़ोpage(काष्ठा file *file,
		   काष्ठा page *page,
		   स्थिर काष्ठा netfs_पढ़ो_request_ops *ops,
		   व्योम *netfs_priv)
अणु
	काष्ठा netfs_पढ़ो_request *rreq;
	अचिन्हित पूर्णांक debug_index = 0;
	पूर्णांक ret;

	_enter("%lx", page_index(page));

	rreq = netfs_alloc_पढ़ो_request(ops, netfs_priv, file);
	अगर (!rreq) अणु
		अगर (netfs_priv)
			ops->cleanup(netfs_priv, page_file_mapping(page));
		unlock_page(page);
		वापस -ENOMEM;
	पूर्ण
	rreq->mapping	= page_file_mapping(page);
	rreq->start	= page_file_offset(page);
	rreq->len	= thp_size(page);

	अगर (ops->begin_cache_operation) अणु
		ret = ops->begin_cache_operation(rreq);
		अगर (ret == -ENOMEM || ret == -EINTR || ret == -ERESTARTSYS) अणु
			unlock_page(page);
			जाओ out;
		पूर्ण
	पूर्ण

	netfs_stat(&netfs_n_rh_पढ़ोpage);
	trace_netfs_पढ़ो(rreq, rreq->start, rreq->len, netfs_पढ़ो_trace_पढ़ोpage);

	netfs_get_पढ़ो_request(rreq);

	atomic_set(&rreq->nr_rd_ops, 1);
	करो अणु
		अगर (!netfs_rreq_submit_slice(rreq, &debug_index))
			अवरोध;

	पूर्ण जबतक (rreq->submitted < rreq->len);

	/* Keep nr_rd_ops incremented so that the ref always beदीर्घs to us, and
	 * the service code isn't punted off to a अक्रमom thपढ़ो pool to
	 * process.
	 */
	करो अणु
		रुको_var_event(&rreq->nr_rd_ops, atomic_पढ़ो(&rreq->nr_rd_ops) == 1);
		netfs_rreq_assess(rreq, false);
	पूर्ण जबतक (test_bit(NETFS_RREQ_IN_PROGRESS, &rreq->flags));

	ret = rreq->error;
	अगर (ret == 0 && rreq->submitted < rreq->len) अणु
		trace_netfs_failure(rreq, शून्य, ret, netfs_fail_लघु_पढ़ोpage);
		ret = -EIO;
	पूर्ण
out:
	netfs_put_पढ़ो_request(rreq, false);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(netfs_पढ़ोpage);

अटल व्योम netfs_clear_thp(काष्ठा page *page)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < thp_nr_pages(page); i++)
		clear_highpage(page + i);
पूर्ण

/**
 * netfs_ग_लिखो_begin - Helper to prepare क्रम writing
 * @file: The file to पढ़ो from
 * @mapping: The mapping to पढ़ो from
 * @pos: File position at which the ग_लिखो will begin
 * @len: The length of the ग_लिखो in this page
 * @flags: AOP_* flags
 * @_page: Where to put the resultant page
 * @_fsdata: Place क्रम the netfs to store a cookie
 * @ops: The network fileप्रणाली's operations क्रम the helper to use
 * @netfs_priv: Private netfs data to be retained in the request
 *
 * Pre-पढ़ो data क्रम a ग_लिखो-begin request by drawing data from the cache अगर
 * possible, or the netfs अगर not.  Space beyond the खातापूर्ण is zero-filled.
 * Multiple I/O requests from dअगरferent sources will get munged together.  If
 * necessary, the पढ़ोahead winकरोw can be expanded in either direction to a
 * more convenient alighment क्रम RPC efficiency or to make storage in the cache
 * feasible.
 *
 * The calling netfs must provide a table of operations, only one of which,
 * issue_op, is mandatory.
 *
 * The check_ग_लिखो_begin() operation can be provided to check क्रम and flush
 * conflicting ग_लिखोs once the page is grabbed and locked.  It is passed a
 * poपूर्णांकer to the fsdata cookie that माला_लो वापसed to the VM to be passed to
 * ग_लिखो_end.  It is permitted to sleep.  It should वापस 0 अगर the request
 * should go ahead; unlock the page and वापस -EAGAIN to cause the page to be
 * regot; or वापस an error.
 *
 * This is usable whether or not caching is enabled.
 */
पूर्णांक netfs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
		      loff_t pos, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक flags,
		      काष्ठा page **_page, व्योम **_fsdata,
		      स्थिर काष्ठा netfs_पढ़ो_request_ops *ops,
		      व्योम *netfs_priv)
अणु
	काष्ठा netfs_पढ़ो_request *rreq;
	काष्ठा page *page, *xpage;
	काष्ठा inode *inode = file_inode(file);
	अचिन्हित पूर्णांक debug_index = 0;
	pgoff_t index = pos >> PAGE_SHIFT;
	पूर्णांक pos_in_page = pos & ~PAGE_MASK;
	loff_t size;
	पूर्णांक ret;

	DEFINE_READAHEAD(ractl, file, शून्य, mapping, index);

retry:
	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;

	अगर (ops->check_ग_लिखो_begin) अणु
		/* Allow the netfs (eg. ceph) to flush conflicts. */
		ret = ops->check_ग_लिखो_begin(file, pos, len, page, _fsdata);
		अगर (ret < 0) अणु
			trace_netfs_failure(शून्य, शून्य, ret, netfs_fail_check_ग_लिखो_begin);
			अगर (ret == -EAGAIN)
				जाओ retry;
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (PageUptodate(page))
		जाओ have_page;

	/* If the page is beyond the खातापूर्ण, we want to clear it - unless it's
	 * within the cache granule containing the खातापूर्ण, in which हाल we need
	 * to preload the granule.
	 */
	size = i_size_पढ़ो(inode);
	अगर (!ops->is_cache_enabled(inode) &&
	    ((pos_in_page == 0 && len == thp_size(page)) ||
	     (pos >= size) ||
	     (pos_in_page == 0 && (pos + len) >= size))) अणु
		netfs_clear_thp(page);
		SetPageUptodate(page);
		netfs_stat(&netfs_n_rh_ग_लिखो_zskip);
		जाओ have_page_no_रुको;
	पूर्ण

	ret = -ENOMEM;
	rreq = netfs_alloc_पढ़ो_request(ops, netfs_priv, file);
	अगर (!rreq)
		जाओ error;
	rreq->mapping		= page->mapping;
	rreq->start		= page_offset(page);
	rreq->len		= thp_size(page);
	rreq->no_unlock_page	= page->index;
	__set_bit(NETFS_RREQ_NO_UNLOCK_PAGE, &rreq->flags);
	netfs_priv = शून्य;

	अगर (ops->begin_cache_operation) अणु
		ret = ops->begin_cache_operation(rreq);
		अगर (ret == -ENOMEM || ret == -EINTR || ret == -ERESTARTSYS)
			जाओ error_put;
	पूर्ण

	netfs_stat(&netfs_n_rh_ग_लिखो_begin);
	trace_netfs_पढ़ो(rreq, pos, len, netfs_पढ़ो_trace_ग_लिखो_begin);

	/* Expand the request to meet caching requirements and करोwnload
	 * preferences.
	 */
	ractl._nr_pages = thp_nr_pages(page);
	netfs_rreq_expand(rreq, &ractl);
	netfs_get_पढ़ो_request(rreq);

	/* We hold the page locks, so we can drop the references */
	जबतक ((xpage = पढ़ोahead_page(&ractl)))
		अगर (xpage != page)
			put_page(xpage);

	atomic_set(&rreq->nr_rd_ops, 1);
	करो अणु
		अगर (!netfs_rreq_submit_slice(rreq, &debug_index))
			अवरोध;

	पूर्ण जबतक (rreq->submitted < rreq->len);

	/* Keep nr_rd_ops incremented so that the ref always beदीर्घs to us, and
	 * the service code isn't punted off to a अक्रमom thपढ़ो pool to
	 * process.
	 */
	क्रम (;;) अणु
		रुको_var_event(&rreq->nr_rd_ops, atomic_पढ़ो(&rreq->nr_rd_ops) == 1);
		netfs_rreq_assess(rreq, false);
		अगर (!test_bit(NETFS_RREQ_IN_PROGRESS, &rreq->flags))
			अवरोध;
		cond_resched();
	पूर्ण

	ret = rreq->error;
	अगर (ret == 0 && rreq->submitted < rreq->len) अणु
		trace_netfs_failure(rreq, शून्य, ret, netfs_fail_लघु_ग_लिखो_begin);
		ret = -EIO;
	पूर्ण
	netfs_put_पढ़ो_request(rreq, false);
	अगर (ret < 0)
		जाओ error;

have_page:
	ret = रुको_on_page_fscache_समाप्तable(page);
	अगर (ret < 0)
		जाओ error;
have_page_no_रुको:
	अगर (netfs_priv)
		ops->cleanup(netfs_priv, mapping);
	*_page = page;
	_leave(" = 0");
	वापस 0;

error_put:
	netfs_put_पढ़ो_request(rreq, false);
error:
	unlock_page(page);
	put_page(page);
	अगर (netfs_priv)
		ops->cleanup(netfs_priv, mapping);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(netfs_ग_लिखो_begin);
