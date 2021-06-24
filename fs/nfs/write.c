<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/nfs/ग_लिखो.c
 *
 * Write file data over NFS.
 *
 * Copyright (C) 1996, 1997, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/file.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/swap.h>
#समावेश <linux/migrate.h>

#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/export.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/रुको.h>
#समावेश <linux/iversion.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/sched/mm.h>

#समावेश "delegation.h"
#समावेश "internal.h"
#समावेश "iostat.h"
#समावेश "nfs4_fs.h"
#समावेश "fscache.h"
#समावेश "pnfs.h"

#समावेश "nfstrace.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PAGECACHE

#घोषणा MIN_POOL_WRITE		(32)
#घोषणा MIN_POOL_COMMIT		(4)

काष्ठा nfs_io_completion अणु
	व्योम (*complete)(व्योम *data);
	व्योम *data;
	काष्ठा kref refcount;
पूर्ण;

/*
 * Local function declarations
 */
अटल व्योम nfs_redirty_request(काष्ठा nfs_page *req);
अटल स्थिर काष्ठा rpc_call_ops nfs_commit_ops;
अटल स्थिर काष्ठा nfs_pgio_completion_ops nfs_async_ग_लिखो_completion_ops;
अटल स्थिर काष्ठा nfs_commit_completion_ops nfs_commit_completion_ops;
अटल स्थिर काष्ठा nfs_rw_ops nfs_rw_ग_लिखो_ops;
अटल व्योम nfs_inode_हटाओ_request(काष्ठा nfs_page *req);
अटल व्योम nfs_clear_request_commit(काष्ठा nfs_page *req);
अटल व्योम nfs_init_cinfo_from_inode(काष्ठा nfs_commit_info *cinfo,
				      काष्ठा inode *inode);
अटल काष्ठा nfs_page *
nfs_page_search_commits_क्रम_head_request_locked(काष्ठा nfs_inode *nfsi,
						काष्ठा page *page);

अटल काष्ठा kmem_cache *nfs_wdata_cachep;
अटल mempool_t *nfs_wdata_mempool;
अटल काष्ठा kmem_cache *nfs_cdata_cachep;
अटल mempool_t *nfs_commit_mempool;

काष्ठा nfs_commit_data *nfs_commitdata_alloc(bool never_fail)
अणु
	काष्ठा nfs_commit_data *p;

	अगर (never_fail)
		p = mempool_alloc(nfs_commit_mempool, GFP_NOIO);
	अन्यथा अणु
		/* It is OK to करो some reclaim, not no safe to रुको
		 * क्रम anything to be वापसed to the pool.
		 * mempool_alloc() cannot handle that particular combination,
		 * so we need two separate attempts.
		 */
		p = mempool_alloc(nfs_commit_mempool, GFP_NOWAIT);
		अगर (!p)
			p = kmem_cache_alloc(nfs_cdata_cachep, GFP_NOIO |
					     __GFP_NOWARN | __GFP_NORETRY);
		अगर (!p)
			वापस शून्य;
	पूर्ण

	स_रखो(p, 0, माप(*p));
	INIT_LIST_HEAD(&p->pages);
	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_commitdata_alloc);

व्योम nfs_commit_मुक्त(काष्ठा nfs_commit_data *p)
अणु
	mempool_मुक्त(p, nfs_commit_mempool);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_commit_मुक्त);

अटल काष्ठा nfs_pgio_header *nfs_ग_लिखोhdr_alloc(व्योम)
अणु
	काष्ठा nfs_pgio_header *p = mempool_alloc(nfs_wdata_mempool, GFP_KERNEL);

	स_रखो(p, 0, माप(*p));
	p->rw_mode = FMODE_WRITE;
	वापस p;
पूर्ण

अटल व्योम nfs_ग_लिखोhdr_मुक्त(काष्ठा nfs_pgio_header *hdr)
अणु
	mempool_मुक्त(hdr, nfs_wdata_mempool);
पूर्ण

अटल काष्ठा nfs_io_completion *nfs_io_completion_alloc(gfp_t gfp_flags)
अणु
	वापस kदो_स्मृति(माप(काष्ठा nfs_io_completion), gfp_flags);
पूर्ण

अटल व्योम nfs_io_completion_init(काष्ठा nfs_io_completion *ioc,
		व्योम (*complete)(व्योम *), व्योम *data)
अणु
	ioc->complete = complete;
	ioc->data = data;
	kref_init(&ioc->refcount);
पूर्ण

अटल व्योम nfs_io_completion_release(काष्ठा kref *kref)
अणु
	काष्ठा nfs_io_completion *ioc = container_of(kref,
			काष्ठा nfs_io_completion, refcount);
	ioc->complete(ioc->data);
	kमुक्त(ioc);
पूर्ण

अटल व्योम nfs_io_completion_get(काष्ठा nfs_io_completion *ioc)
अणु
	अगर (ioc != शून्य)
		kref_get(&ioc->refcount);
पूर्ण

अटल व्योम nfs_io_completion_put(काष्ठा nfs_io_completion *ioc)
अणु
	अगर (ioc != शून्य)
		kref_put(&ioc->refcount, nfs_io_completion_release);
पूर्ण

अटल व्योम
nfs_page_set_inode_ref(काष्ठा nfs_page *req, काष्ठा inode *inode)
अणु
	अगर (!test_and_set_bit(PG_INODE_REF, &req->wb_flags)) अणु
		kref_get(&req->wb_kref);
		atomic_दीर्घ_inc(&NFS_I(inode)->nrequests);
	पूर्ण
पूर्ण

अटल पूर्णांक
nfs_cancel_हटाओ_inode(काष्ठा nfs_page *req, काष्ठा inode *inode)
अणु
	पूर्णांक ret;

	अगर (!test_bit(PG_REMOVE, &req->wb_flags))
		वापस 0;
	ret = nfs_page_group_lock(req);
	अगर (ret)
		वापस ret;
	अगर (test_and_clear_bit(PG_REMOVE, &req->wb_flags))
		nfs_page_set_inode_ref(req, inode);
	nfs_page_group_unlock(req);
	वापस 0;
पूर्ण

अटल काष्ठा nfs_page *
nfs_page_निजी_request(काष्ठा page *page)
अणु
	अगर (!PagePrivate(page))
		वापस शून्य;
	वापस (काष्ठा nfs_page *)page_निजी(page);
पूर्ण

/*
 * nfs_page_find_head_request_locked - find head request associated with @page
 *
 * must be called जबतक holding the inode lock.
 *
 * वापसs matching head request with reference held, or शून्य अगर not found.
 */
अटल काष्ठा nfs_page *
nfs_page_find_निजी_request(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_file_mapping(page);
	काष्ठा nfs_page *req;

	अगर (!PagePrivate(page))
		वापस शून्य;
	spin_lock(&mapping->निजी_lock);
	req = nfs_page_निजी_request(page);
	अगर (req) अणु
		WARN_ON_ONCE(req->wb_head != req);
		kref_get(&req->wb_kref);
	पूर्ण
	spin_unlock(&mapping->निजी_lock);
	वापस req;
पूर्ण

अटल काष्ठा nfs_page *
nfs_page_find_swap_request(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page_file_mapping(page)->host;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_page *req = शून्य;
	अगर (!PageSwapCache(page))
		वापस शून्य;
	mutex_lock(&nfsi->commit_mutex);
	अगर (PageSwapCache(page)) अणु
		req = nfs_page_search_commits_क्रम_head_request_locked(nfsi,
			page);
		अगर (req) अणु
			WARN_ON_ONCE(req->wb_head != req);
			kref_get(&req->wb_kref);
		पूर्ण
	पूर्ण
	mutex_unlock(&nfsi->commit_mutex);
	वापस req;
पूर्ण

/*
 * nfs_page_find_head_request - find head request associated with @page
 *
 * वापसs matching head request with reference held, or शून्य अगर not found.
 */
अटल काष्ठा nfs_page *nfs_page_find_head_request(काष्ठा page *page)
अणु
	काष्ठा nfs_page *req;

	req = nfs_page_find_निजी_request(page);
	अगर (!req)
		req = nfs_page_find_swap_request(page);
	वापस req;
पूर्ण

अटल काष्ठा nfs_page *nfs_find_and_lock_page_request(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page_file_mapping(page)->host;
	काष्ठा nfs_page *req, *head;
	पूर्णांक ret;

	क्रम (;;) अणु
		req = nfs_page_find_head_request(page);
		अगर (!req)
			वापस req;
		head = nfs_page_group_lock_head(req);
		अगर (head != req)
			nfs_release_request(req);
		अगर (IS_ERR(head))
			वापस head;
		ret = nfs_cancel_हटाओ_inode(head, inode);
		अगर (ret < 0) अणु
			nfs_unlock_and_release_request(head);
			वापस ERR_PTR(ret);
		पूर्ण
		/* Ensure that nobody हटाओd the request beक्रमe we locked it */
		अगर (head == nfs_page_निजी_request(page))
			अवरोध;
		अगर (PageSwapCache(page))
			अवरोध;
		nfs_unlock_and_release_request(head);
	पूर्ण
	वापस head;
पूर्ण

/* Adjust the file length अगर we're writing beyond the end */
अटल व्योम nfs_grow_file(काष्ठा page *page, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक count)
अणु
	काष्ठा inode *inode = page_file_mapping(page)->host;
	loff_t end, i_size;
	pgoff_t end_index;

	spin_lock(&inode->i_lock);
	i_size = i_size_पढ़ो(inode);
	end_index = (i_size - 1) >> PAGE_SHIFT;
	अगर (i_size > 0 && page_index(page) < end_index)
		जाओ out;
	end = page_file_offset(page) + ((loff_t)offset+count);
	अगर (i_size >= end)
		जाओ out;
	i_size_ग_लिखो(inode, end);
	NFS_I(inode)->cache_validity &= ~NFS_INO_INVALID_SIZE;
	nfs_inc_stats(inode, NFSIOS_EXTENDWRITE);
out:
	spin_unlock(&inode->i_lock);
पूर्ण

/* A ग_लिखोback failed: mark the page as bad, and invalidate the page cache */
अटल व्योम nfs_set_pageerror(काष्ठा address_space *mapping)
अणु
	काष्ठा inode *inode = mapping->host;

	nfs_zap_mapping(mapping->host, mapping);
	/* Force file size revalidation */
	spin_lock(&inode->i_lock);
	nfs_set_cache_invalid(inode, NFS_INO_REVAL_FORCED |
					     NFS_INO_REVAL_PAGECACHE |
					     NFS_INO_INVALID_SIZE);
	spin_unlock(&inode->i_lock);
पूर्ण

अटल व्योम nfs_mapping_set_error(काष्ठा page *page, पूर्णांक error)
अणु
	काष्ठा address_space *mapping = page_file_mapping(page);

	SetPageError(page);
	mapping_set_error(mapping, error);
	nfs_set_pageerror(mapping);
पूर्ण

/*
 * nfs_page_group_search_locked
 * @head - head request of page group
 * @page_offset - offset पूर्णांकo page
 *
 * Search page group with head @head to find a request that contains the
 * page offset @page_offset.
 *
 * Returns a poपूर्णांकer to the first matching nfs request, or शून्य अगर no
 * match is found.
 *
 * Must be called with the page group lock held
 */
अटल काष्ठा nfs_page *
nfs_page_group_search_locked(काष्ठा nfs_page *head, अचिन्हित पूर्णांक page_offset)
अणु
	काष्ठा nfs_page *req;

	req = head;
	करो अणु
		अगर (page_offset >= req->wb_pgbase &&
		    page_offset < (req->wb_pgbase + req->wb_bytes))
			वापस req;

		req = req->wb_this_page;
	पूर्ण जबतक (req != head);

	वापस शून्य;
पूर्ण

/*
 * nfs_page_group_covers_page
 * @head - head request of page group
 *
 * Return true अगर the page group with head @head covers the whole page,
 * वापसs false otherwise
 */
अटल bool nfs_page_group_covers_page(काष्ठा nfs_page *req)
अणु
	काष्ठा nfs_page *पंचांगp;
	अचिन्हित पूर्णांक pos = 0;
	अचिन्हित पूर्णांक len = nfs_page_length(req->wb_page);

	nfs_page_group_lock(req);

	क्रम (;;) अणु
		पंचांगp = nfs_page_group_search_locked(req->wb_head, pos);
		अगर (!पंचांगp)
			अवरोध;
		pos = पंचांगp->wb_pgbase + पंचांगp->wb_bytes;
	पूर्ण

	nfs_page_group_unlock(req);
	वापस pos >= len;
पूर्ण

/* We can set the PG_uptodate flag अगर we see that a ग_लिखो request
 * covers the full page.
 */
अटल व्योम nfs_mark_uptodate(काष्ठा nfs_page *req)
अणु
	अगर (PageUptodate(req->wb_page))
		वापस;
	अगर (!nfs_page_group_covers_page(req))
		वापस;
	SetPageUptodate(req->wb_page);
पूर्ण

अटल पूर्णांक wb_priority(काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret = 0;

	अगर (wbc->sync_mode == WB_SYNC_ALL)
		ret = FLUSH_COND_STABLE;
	वापस ret;
पूर्ण

/*
 * NFS congestion control
 */

पूर्णांक nfs_congestion_kb;

#घोषणा NFS_CONGESTION_ON_THRESH 	(nfs_congestion_kb >> (PAGE_SHIFT-10))
#घोषणा NFS_CONGESTION_OFF_THRESH	\
	(NFS_CONGESTION_ON_THRESH - (NFS_CONGESTION_ON_THRESH >> 2))

अटल व्योम nfs_set_page_ग_लिखोback(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page_file_mapping(page)->host;
	काष्ठा nfs_server *nfss = NFS_SERVER(inode);
	पूर्णांक ret = test_set_page_ग_लिखोback(page);

	WARN_ON_ONCE(ret != 0);

	अगर (atomic_दीर्घ_inc_वापस(&nfss->ग_लिखोback) >
			NFS_CONGESTION_ON_THRESH)
		set_bdi_congested(inode_to_bdi(inode), BLK_RW_ASYNC);
पूर्ण

अटल व्योम nfs_end_page_ग_लिखोback(काष्ठा nfs_page *req)
अणु
	काष्ठा inode *inode = page_file_mapping(req->wb_page)->host;
	काष्ठा nfs_server *nfss = NFS_SERVER(inode);
	bool is_करोne;

	is_करोne = nfs_page_group_sync_on_bit(req, PG_WB_END);
	nfs_unlock_request(req);
	अगर (!is_करोne)
		वापस;

	end_page_ग_लिखोback(req->wb_page);
	अगर (atomic_दीर्घ_dec_वापस(&nfss->ग_लिखोback) < NFS_CONGESTION_OFF_THRESH)
		clear_bdi_congested(inode_to_bdi(inode), BLK_RW_ASYNC);
पूर्ण

/*
 * nfs_destroy_unlinked_subrequests - destroy recently unlinked subrequests
 *
 * @destroy_list - request list (using wb_this_page) terminated by @old_head
 * @old_head - the old head of the list
 *
 * All subrequests must be locked and हटाओd from all lists, so at this poपूर्णांक
 * they are only "active" in this function, and possibly in nfs_रुको_on_request
 * with a reference held by some other context.
 */
अटल व्योम
nfs_destroy_unlinked_subrequests(काष्ठा nfs_page *destroy_list,
				 काष्ठा nfs_page *old_head,
				 काष्ठा inode *inode)
अणु
	जबतक (destroy_list) अणु
		काष्ठा nfs_page *subreq = destroy_list;

		destroy_list = (subreq->wb_this_page == old_head) ?
				   शून्य : subreq->wb_this_page;

		/* Note: lock subreq in order to change subreq->wb_head */
		nfs_page_set_headlock(subreq);
		WARN_ON_ONCE(old_head != subreq->wb_head);

		/* make sure old group is not used */
		subreq->wb_this_page = subreq;
		subreq->wb_head = subreq;

		clear_bit(PG_REMOVE, &subreq->wb_flags);

		/* Note: races with nfs_page_group_destroy() */
		अगर (!kref_पढ़ो(&subreq->wb_kref)) अणु
			/* Check अगर we raced with nfs_page_group_destroy() */
			अगर (test_and_clear_bit(PG_TEARDOWN, &subreq->wb_flags)) अणु
				nfs_page_clear_headlock(subreq);
				nfs_मुक्त_request(subreq);
			पूर्ण अन्यथा
				nfs_page_clear_headlock(subreq);
			जारी;
		पूर्ण
		nfs_page_clear_headlock(subreq);

		nfs_release_request(old_head);

		अगर (test_and_clear_bit(PG_INODE_REF, &subreq->wb_flags)) अणु
			nfs_release_request(subreq);
			atomic_दीर्घ_dec(&NFS_I(inode)->nrequests);
		पूर्ण

		/* subreq is now totally disconnected from page group or any
		 * ग_लिखो / commit lists. last chance to wake any रुकोers */
		nfs_unlock_and_release_request(subreq);
	पूर्ण
पूर्ण

/*
 * nfs_join_page_group - destroy subrequests of the head req
 * @head: the page used to lookup the "page group" of nfs_page काष्ठाures
 * @inode: Inode to which the request beदीर्घs.
 *
 * This function joins all sub requests to the head request by first
 * locking all requests in the group, cancelling any pending operations
 * and finally updating the head request to cover the whole range covered by
 * the (क्रमmer) group.  All subrequests are हटाओd from any ग_लिखो or commit
 * lists, unlinked from the group and destroyed.
 */
व्योम
nfs_join_page_group(काष्ठा nfs_page *head, काष्ठा inode *inode)
अणु
	काष्ठा nfs_page *subreq;
	काष्ठा nfs_page *destroy_list = शून्य;
	अचिन्हित पूर्णांक pgbase, off, bytes;

	pgbase = head->wb_pgbase;
	bytes = head->wb_bytes;
	off = head->wb_offset;
	क्रम (subreq = head->wb_this_page; subreq != head;
			subreq = subreq->wb_this_page) अणु
		/* Subrequests should always क्रमm a contiguous range */
		अगर (pgbase > subreq->wb_pgbase) अणु
			off -= pgbase - subreq->wb_pgbase;
			bytes += pgbase - subreq->wb_pgbase;
			pgbase = subreq->wb_pgbase;
		पूर्ण
		bytes = max(subreq->wb_pgbase + subreq->wb_bytes
				- pgbase, bytes);
	पूर्ण

	/* Set the head request's range to cover the क्रमmer page group */
	head->wb_pgbase = pgbase;
	head->wb_bytes = bytes;
	head->wb_offset = off;

	/* Now that all requests are locked, make sure they aren't on any list.
	 * Commit list removal accounting is करोne after locks are dropped */
	subreq = head;
	करो अणु
		nfs_clear_request_commit(subreq);
		subreq = subreq->wb_this_page;
	पूर्ण जबतक (subreq != head);

	/* unlink subrequests from head, destroy them later */
	अगर (head->wb_this_page != head) अणु
		/* destroy list will be terminated by head */
		destroy_list = head->wb_this_page;
		head->wb_this_page = head;
	पूर्ण

	nfs_destroy_unlinked_subrequests(destroy_list, head, inode);
पूर्ण

/*
 * nfs_lock_and_join_requests - join all subreqs to the head req
 * @page: the page used to lookup the "page group" of nfs_page काष्ठाures
 *
 * This function joins all sub requests to the head request by first
 * locking all requests in the group, cancelling any pending operations
 * and finally updating the head request to cover the whole range covered by
 * the (क्रमmer) group.  All subrequests are हटाओd from any ग_लिखो or commit
 * lists, unlinked from the group and destroyed.
 *
 * Returns a locked, referenced poपूर्णांकer to the head request - which after
 * this call is guaranteed to be the only request associated with the page.
 * Returns शून्य अगर no requests are found क्रम @page, or a ERR_PTR अगर an
 * error was encountered.
 */
अटल काष्ठा nfs_page *
nfs_lock_and_join_requests(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page_file_mapping(page)->host;
	काष्ठा nfs_page *head;
	पूर्णांक ret;

	/*
	 * A reference is taken only on the head request which acts as a
	 * reference to the whole page group - the group will not be destroyed
	 * until the head reference is released.
	 */
	head = nfs_find_and_lock_page_request(page);
	अगर (IS_ERR_OR_शून्य(head))
		वापस head;

	/* lock each request in the page group */
	ret = nfs_page_group_lock_subrequests(head);
	अगर (ret < 0) अणु
		nfs_unlock_and_release_request(head);
		वापस ERR_PTR(ret);
	पूर्ण

	nfs_join_page_group(head, inode);

	वापस head;
पूर्ण

अटल व्योम nfs_ग_लिखो_error(काष्ठा nfs_page *req, पूर्णांक error)
अणु
	trace_nfs_ग_लिखो_error(req, error);
	nfs_mapping_set_error(req->wb_page, error);
	nfs_inode_हटाओ_request(req);
	nfs_end_page_ग_लिखोback(req);
	nfs_release_request(req);
पूर्ण

/*
 * Find an associated nfs ग_लिखो request, and prepare to flush it out
 * May वापस an error अगर the user संकेतled nfs_रुको_on_request().
 */
अटल पूर्णांक nfs_page_async_flush(काष्ठा nfs_pageio_descriptor *pgio,
				काष्ठा page *page)
अणु
	काष्ठा nfs_page *req;
	पूर्णांक ret = 0;

	req = nfs_lock_and_join_requests(page);
	अगर (!req)
		जाओ out;
	ret = PTR_ERR(req);
	अगर (IS_ERR(req))
		जाओ out;

	nfs_set_page_ग_लिखोback(page);
	WARN_ON_ONCE(test_bit(PG_CLEAN, &req->wb_flags));

	/* If there is a fatal error that covers this ग_लिखो, just निकास */
	ret = pgio->pg_error;
	अगर (nfs_error_is_fatal_on_server(ret))
		जाओ out_launder;

	ret = 0;
	अगर (!nfs_pageio_add_request(pgio, req)) अणु
		ret = pgio->pg_error;
		/*
		 * Remove the problematic req upon fatal errors on the server
		 */
		अगर (nfs_error_is_fatal(ret)) अणु
			अगर (nfs_error_is_fatal_on_server(ret))
				जाओ out_launder;
		पूर्ण अन्यथा
			ret = -EAGAIN;
		nfs_redirty_request(req);
		pgio->pg_error = 0;
	पूर्ण अन्यथा
		nfs_add_stats(page_file_mapping(page)->host,
				NFSIOS_WRITEPAGES, 1);
out:
	वापस ret;
out_launder:
	nfs_ग_लिखो_error(req, ret);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs_करो_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
			    काष्ठा nfs_pageio_descriptor *pgio)
अणु
	पूर्णांक ret;

	nfs_pageio_cond_complete(pgio, page_index(page));
	ret = nfs_page_async_flush(pgio, page);
	अगर (ret == -EAGAIN) अणु
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		ret = AOP_WRITEPAGE_ACTIVATE;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Write an mmapped page to the server.
 */
अटल पूर्णांक nfs_ग_लिखोpage_locked(काष्ठा page *page,
				काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा nfs_pageio_descriptor pgio;
	काष्ठा inode *inode = page_file_mapping(page)->host;
	पूर्णांक err;

	nfs_inc_stats(inode, NFSIOS_VFSWRITEPAGE);
	nfs_pageio_init_ग_लिखो(&pgio, inode, 0,
				false, &nfs_async_ग_लिखो_completion_ops);
	err = nfs_करो_ग_लिखोpage(page, wbc, &pgio);
	pgio.pg_error = 0;
	nfs_pageio_complete(&pgio);
	अगर (err < 0)
		वापस err;
	अगर (nfs_error_is_fatal(pgio.pg_error))
		वापस pgio.pg_error;
	वापस 0;
पूर्ण

पूर्णांक nfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret;

	ret = nfs_ग_लिखोpage_locked(page, wbc);
	अगर (ret != AOP_WRITEPAGE_ACTIVATE)
		unlock_page(page);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs_ग_लिखोpages_callback(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc, व्योम *data)
अणु
	पूर्णांक ret;

	ret = nfs_करो_ग_लिखोpage(page, wbc, data);
	अगर (ret != AOP_WRITEPAGE_ACTIVATE)
		unlock_page(page);
	वापस ret;
पूर्ण

अटल व्योम nfs_io_completion_commit(व्योम *inode)
अणु
	nfs_commit_inode(inode, 0);
पूर्ण

पूर्णांक nfs_ग_लिखोpages(काष्ठा address_space *mapping, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा nfs_pageio_descriptor pgio;
	काष्ठा nfs_io_completion *ioc = शून्य;
	अचिन्हित पूर्णांक mntflags = NFS_SERVER(inode)->flags;
	पूर्णांक priority = 0;
	पूर्णांक err;

	nfs_inc_stats(inode, NFSIOS_VFSWRITEPAGES);

	अगर (!(mntflags & NFS_MOUNT_WRITE_EAGER) || wbc->क्रम_kupdate ||
	    wbc->क्रम_background || wbc->क्रम_sync || wbc->क्रम_reclaim) अणु
		ioc = nfs_io_completion_alloc(GFP_KERNEL);
		अगर (ioc)
			nfs_io_completion_init(ioc, nfs_io_completion_commit,
					       inode);
		priority = wb_priority(wbc);
	पूर्ण

	nfs_pageio_init_ग_लिखो(&pgio, inode, priority, false,
				&nfs_async_ग_लिखो_completion_ops);
	pgio.pg_io_completion = ioc;
	err = ग_लिखो_cache_pages(mapping, wbc, nfs_ग_लिखोpages_callback, &pgio);
	pgio.pg_error = 0;
	nfs_pageio_complete(&pgio);
	nfs_io_completion_put(ioc);

	अगर (err < 0)
		जाओ out_err;
	err = pgio.pg_error;
	अगर (nfs_error_is_fatal(err))
		जाओ out_err;
	वापस 0;
out_err:
	वापस err;
पूर्ण

/*
 * Insert a ग_लिखो request पूर्णांकo an inode
 */
अटल व्योम nfs_inode_add_request(काष्ठा inode *inode, काष्ठा nfs_page *req)
अणु
	काष्ठा address_space *mapping = page_file_mapping(req->wb_page);
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	WARN_ON_ONCE(req->wb_this_page != req);

	/* Lock the request! */
	nfs_lock_request(req);

	/*
	 * Swap-space should not get truncated. Hence no need to plug the race
	 * with invalidate/truncate.
	 */
	spin_lock(&mapping->निजी_lock);
	अगर (likely(!PageSwapCache(req->wb_page))) अणु
		set_bit(PG_MAPPED, &req->wb_flags);
		SetPagePrivate(req->wb_page);
		set_page_निजी(req->wb_page, (अचिन्हित दीर्घ)req);
	पूर्ण
	spin_unlock(&mapping->निजी_lock);
	atomic_दीर्घ_inc(&nfsi->nrequests);
	/* this a head request क्रम a page group - mark it as having an
	 * extra reference so sub groups can follow suit.
	 * This flag also inक्रमms pgio layer when to bump nrequests when
	 * adding subrequests. */
	WARN_ON(test_and_set_bit(PG_INODE_REF, &req->wb_flags));
	kref_get(&req->wb_kref);
पूर्ण

/*
 * Remove a ग_लिखो request from an inode
 */
अटल व्योम nfs_inode_हटाओ_request(काष्ठा nfs_page *req)
अणु
	काष्ठा address_space *mapping = page_file_mapping(req->wb_page);
	काष्ठा inode *inode = mapping->host;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_page *head;

	अगर (nfs_page_group_sync_on_bit(req, PG_REMOVE)) अणु
		head = req->wb_head;

		spin_lock(&mapping->निजी_lock);
		अगर (likely(head->wb_page && !PageSwapCache(head->wb_page))) अणु
			set_page_निजी(head->wb_page, 0);
			ClearPagePrivate(head->wb_page);
			clear_bit(PG_MAPPED, &head->wb_flags);
		पूर्ण
		spin_unlock(&mapping->निजी_lock);
	पूर्ण

	अगर (test_and_clear_bit(PG_INODE_REF, &req->wb_flags)) अणु
		nfs_release_request(req);
		atomic_दीर्घ_dec(&nfsi->nrequests);
	पूर्ण
पूर्ण

अटल व्योम
nfs_mark_request_dirty(काष्ठा nfs_page *req)
अणु
	अगर (req->wb_page)
		__set_page_dirty_nobuffers(req->wb_page);
पूर्ण

/*
 * nfs_page_search_commits_क्रम_head_request_locked
 *
 * Search through commit lists on @inode क्रम the head request क्रम @page.
 * Must be called जबतक holding the inode (which is cinfo) lock.
 *
 * Returns the head request अगर found, or शून्य अगर not found.
 */
अटल काष्ठा nfs_page *
nfs_page_search_commits_क्रम_head_request_locked(काष्ठा nfs_inode *nfsi,
						काष्ठा page *page)
अणु
	काष्ठा nfs_page *freq, *t;
	काष्ठा nfs_commit_info cinfo;
	काष्ठा inode *inode = &nfsi->vfs_inode;

	nfs_init_cinfo_from_inode(&cinfo, inode);

	/* search through pnfs commit lists */
	freq = pnfs_search_commit_reqs(inode, &cinfo, page);
	अगर (freq)
		वापस freq->wb_head;

	/* Linearly search the commit list क्रम the correct request */
	list_क्रम_each_entry_safe(freq, t, &cinfo.mds->list, wb_list) अणु
		अगर (freq->wb_page == page)
			वापस freq->wb_head;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * nfs_request_add_commit_list_locked - add request to a commit list
 * @req: poपूर्णांकer to a काष्ठा nfs_page
 * @dst: commit list head
 * @cinfo: holds list lock and accounting info
 *
 * This sets the PG_CLEAN bit, updates the cinfo count of
 * number of outstanding requests requiring a commit as well as
 * the MM page stats.
 *
 * The caller must hold NFS_I(cinfo->inode)->commit_mutex, and the
 * nfs_page lock.
 */
व्योम
nfs_request_add_commit_list_locked(काष्ठा nfs_page *req, काष्ठा list_head *dst,
			    काष्ठा nfs_commit_info *cinfo)
अणु
	set_bit(PG_CLEAN, &req->wb_flags);
	nfs_list_add_request(req, dst);
	atomic_दीर्घ_inc(&cinfo->mds->ncommit);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_request_add_commit_list_locked);

/**
 * nfs_request_add_commit_list - add request to a commit list
 * @req: poपूर्णांकer to a काष्ठा nfs_page
 * @cinfo: holds list lock and accounting info
 *
 * This sets the PG_CLEAN bit, updates the cinfo count of
 * number of outstanding requests requiring a commit as well as
 * the MM page stats.
 *
 * The caller must _not_ hold the cinfo->lock, but must be
 * holding the nfs_page lock.
 */
व्योम
nfs_request_add_commit_list(काष्ठा nfs_page *req, काष्ठा nfs_commit_info *cinfo)
अणु
	mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
	nfs_request_add_commit_list_locked(req, &cinfo->mds->list, cinfo);
	mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
	अगर (req->wb_page)
		nfs_mark_page_unstable(req->wb_page, cinfo);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_request_add_commit_list);

/**
 * nfs_request_हटाओ_commit_list - Remove request from a commit list
 * @req: poपूर्णांकer to a nfs_page
 * @cinfo: holds list lock and accounting info
 *
 * This clears the PG_CLEAN bit, and updates the cinfo's count of
 * number of outstanding requests requiring a commit
 * It करोes not update the MM page stats.
 *
 * The caller _must_ hold the cinfo->lock and the nfs_page lock.
 */
व्योम
nfs_request_हटाओ_commit_list(काष्ठा nfs_page *req,
			       काष्ठा nfs_commit_info *cinfo)
अणु
	अगर (!test_and_clear_bit(PG_CLEAN, &(req)->wb_flags))
		वापस;
	nfs_list_हटाओ_request(req);
	atomic_दीर्घ_dec(&cinfo->mds->ncommit);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_request_हटाओ_commit_list);

अटल व्योम nfs_init_cinfo_from_inode(काष्ठा nfs_commit_info *cinfo,
				      काष्ठा inode *inode)
अणु
	cinfo->inode = inode;
	cinfo->mds = &NFS_I(inode)->commit_info;
	cinfo->ds = pnfs_get_ds_info(inode);
	cinfo->dreq = शून्य;
	cinfo->completion_ops = &nfs_commit_completion_ops;
पूर्ण

व्योम nfs_init_cinfo(काष्ठा nfs_commit_info *cinfo,
		    काष्ठा inode *inode,
		    काष्ठा nfs_direct_req *dreq)
अणु
	अगर (dreq)
		nfs_init_cinfo_from_dreq(cinfo, dreq);
	अन्यथा
		nfs_init_cinfo_from_inode(cinfo, inode);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_init_cinfo);

/*
 * Add a request to the inode's commit list.
 */
व्योम
nfs_mark_request_commit(काष्ठा nfs_page *req, काष्ठा pnfs_layout_segment *lseg,
			काष्ठा nfs_commit_info *cinfo, u32 ds_commit_idx)
अणु
	अगर (pnfs_mark_request_commit(req, lseg, cinfo, ds_commit_idx))
		वापस;
	nfs_request_add_commit_list(req, cinfo);
पूर्ण

अटल व्योम
nfs_clear_page_commit(काष्ठा page *page)
अणु
	dec_node_page_state(page, NR_WRITEBACK);
	dec_wb_stat(&inode_to_bdi(page_file_mapping(page)->host)->wb,
		    WB_WRITEBACK);
पूर्ण

/* Called holding the request lock on @req */
अटल व्योम
nfs_clear_request_commit(काष्ठा nfs_page *req)
अणु
	अगर (test_bit(PG_CLEAN, &req->wb_flags)) अणु
		काष्ठा nfs_खोलो_context *ctx = nfs_req_खोलोctx(req);
		काष्ठा inode *inode = d_inode(ctx->dentry);
		काष्ठा nfs_commit_info cinfo;

		nfs_init_cinfo_from_inode(&cinfo, inode);
		mutex_lock(&NFS_I(inode)->commit_mutex);
		अगर (!pnfs_clear_request_commit(req, &cinfo)) अणु
			nfs_request_हटाओ_commit_list(req, &cinfo);
		पूर्ण
		mutex_unlock(&NFS_I(inode)->commit_mutex);
		nfs_clear_page_commit(req->wb_page);
	पूर्ण
पूर्ण

पूर्णांक nfs_ग_लिखो_need_commit(काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (hdr->verf.committed == NFS_DATA_SYNC)
		वापस hdr->lseg == शून्य;
	वापस hdr->verf.committed != NFS_खाता_SYNC;
पूर्ण

अटल व्योम nfs_async_ग_लिखो_init(काष्ठा nfs_pgio_header *hdr)
अणु
	nfs_io_completion_get(hdr->io_completion);
पूर्ण

अटल व्योम nfs_ग_लिखो_completion(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_commit_info cinfo;
	अचिन्हित दीर्घ bytes = 0;

	अगर (test_bit(NFS_IOHDR_REDO, &hdr->flags))
		जाओ out;
	nfs_init_cinfo_from_inode(&cinfo, hdr->inode);
	जबतक (!list_empty(&hdr->pages)) अणु
		काष्ठा nfs_page *req = nfs_list_entry(hdr->pages.next);

		bytes += req->wb_bytes;
		nfs_list_हटाओ_request(req);
		अगर (test_bit(NFS_IOHDR_ERROR, &hdr->flags) &&
		    (hdr->good_bytes < bytes)) अणु
			trace_nfs_comp_error(req, hdr->error);
			nfs_mapping_set_error(req->wb_page, hdr->error);
			जाओ हटाओ_req;
		पूर्ण
		अगर (nfs_ग_लिखो_need_commit(hdr)) अणु
			/* Reset wb_nio, since the ग_लिखो was successful. */
			req->wb_nio = 0;
			स_नकल(&req->wb_verf, &hdr->verf.verअगरier, माप(req->wb_verf));
			nfs_mark_request_commit(req, hdr->lseg, &cinfo,
				hdr->pgio_mirror_idx);
			जाओ next;
		पूर्ण
हटाओ_req:
		nfs_inode_हटाओ_request(req);
next:
		nfs_end_page_ग_लिखोback(req);
		nfs_release_request(req);
	पूर्ण
out:
	nfs_io_completion_put(hdr->io_completion);
	hdr->release(hdr);
पूर्ण

अचिन्हित दीर्घ
nfs_reqs_to_commit(काष्ठा nfs_commit_info *cinfo)
अणु
	वापस atomic_दीर्घ_पढ़ो(&cinfo->mds->ncommit);
पूर्ण

/* NFS_I(cinfo->inode)->commit_mutex held by caller */
पूर्णांक
nfs_scan_commit_list(काष्ठा list_head *src, काष्ठा list_head *dst,
		     काष्ठा nfs_commit_info *cinfo, पूर्णांक max)
अणु
	काष्ठा nfs_page *req, *पंचांगp;
	पूर्णांक ret = 0;

restart:
	list_क्रम_each_entry_safe(req, पंचांगp, src, wb_list) अणु
		kref_get(&req->wb_kref);
		अगर (!nfs_lock_request(req)) अणु
			पूर्णांक status;

			/* Prevent deadlock with nfs_lock_and_join_requests */
			अगर (!list_empty(dst)) अणु
				nfs_release_request(req);
				जारी;
			पूर्ण
			/* Ensure we make progress to prevent livelock */
			mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
			status = nfs_रुको_on_request(req);
			nfs_release_request(req);
			mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
			अगर (status < 0)
				अवरोध;
			जाओ restart;
		पूर्ण
		nfs_request_हटाओ_commit_list(req, cinfo);
		clear_bit(PG_COMMIT_TO_DS, &req->wb_flags);
		nfs_list_add_request(req, dst);
		ret++;
		अगर ((ret == max) && !cinfo->dreq)
			अवरोध;
		cond_resched();
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_scan_commit_list);

/*
 * nfs_scan_commit - Scan an inode क्रम commit requests
 * @inode: NFS inode to scan
 * @dst: mds destination list
 * @cinfo: mds and ds lists of reqs पढ़ोy to commit
 *
 * Moves requests from the inode's 'commit' request list.
 * The requests are *not* checked to ensure that they क्रमm a contiguous set.
 */
पूर्णांक
nfs_scan_commit(काष्ठा inode *inode, काष्ठा list_head *dst,
		काष्ठा nfs_commit_info *cinfo)
अणु
	पूर्णांक ret = 0;

	अगर (!atomic_दीर्घ_पढ़ो(&cinfo->mds->ncommit))
		वापस 0;
	mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
	अगर (atomic_दीर्घ_पढ़ो(&cinfo->mds->ncommit) > 0) अणु
		स्थिर पूर्णांक max = पूर्णांक_उच्च;

		ret = nfs_scan_commit_list(&cinfo->mds->list, dst,
					   cinfo, max);
		ret += pnfs_scan_commit_lists(inode, cinfo, max - ret);
	पूर्ण
	mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
	वापस ret;
पूर्ण

/*
 * Search क्रम an existing ग_लिखो request, and attempt to update
 * it to reflect a new dirty region on a given page.
 *
 * If the attempt fails, then the existing request is flushed out
 * to disk.
 */
अटल काष्ठा nfs_page *nfs_try_to_update_request(काष्ठा inode *inode,
		काष्ठा page *page,
		अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा nfs_page *req;
	अचिन्हित पूर्णांक rqend;
	अचिन्हित पूर्णांक end;
	पूर्णांक error;

	end = offset + bytes;

	req = nfs_lock_and_join_requests(page);
	अगर (IS_ERR_OR_शून्य(req))
		वापस req;

	rqend = req->wb_offset + req->wb_bytes;
	/*
	 * Tell the caller to flush out the request अगर
	 * the offsets are non-contiguous.
	 * Note: nfs_flush_incompatible() will alपढ़ोy
	 * have flushed out requests having wrong owners.
	 */
	अगर (offset > rqend || end < req->wb_offset)
		जाओ out_flushme;

	/* Okay, the request matches. Update the region */
	अगर (offset < req->wb_offset) अणु
		req->wb_offset = offset;
		req->wb_pgbase = offset;
	पूर्ण
	अगर (end > rqend)
		req->wb_bytes = end - req->wb_offset;
	अन्यथा
		req->wb_bytes = rqend - req->wb_offset;
	req->wb_nio = 0;
	वापस req;
out_flushme:
	/*
	 * Note: we mark the request dirty here because
	 * nfs_lock_and_join_requests() cannot preserve
	 * commit flags, so we have to replay the ग_लिखो.
	 */
	nfs_mark_request_dirty(req);
	nfs_unlock_and_release_request(req);
	error = nfs_wb_page(inode, page);
	वापस (error < 0) ? ERR_PTR(error) : शून्य;
पूर्ण

/*
 * Try to update an existing ग_लिखो request, or create one अगर there is none.
 *
 * Note: Should always be called with the Page Lock held to prevent races
 * अगर we have to add a new request. Also assumes that the caller has
 * alपढ़ोy called nfs_flush_incompatible() अगर necessary.
 */
अटल काष्ठा nfs_page * nfs_setup_ग_लिखो_request(काष्ठा nfs_खोलो_context* ctx,
		काष्ठा page *page, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा inode *inode = page_file_mapping(page)->host;
	काष्ठा nfs_page	*req;

	req = nfs_try_to_update_request(inode, page, offset, bytes);
	अगर (req != शून्य)
		जाओ out;
	req = nfs_create_request(ctx, page, offset, bytes);
	अगर (IS_ERR(req))
		जाओ out;
	nfs_inode_add_request(inode, req);
out:
	वापस req;
पूर्ण

अटल पूर्णांक nfs_ग_लिखोpage_setup(काष्ठा nfs_खोलो_context *ctx, काष्ठा page *page,
		अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक count)
अणु
	काष्ठा nfs_page	*req;

	req = nfs_setup_ग_लिखो_request(ctx, page, offset, count);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);
	/* Update file length */
	nfs_grow_file(page, offset, count);
	nfs_mark_uptodate(req);
	nfs_mark_request_dirty(req);
	nfs_unlock_and_release_request(req);
	वापस 0;
पूर्ण

पूर्णांक nfs_flush_incompatible(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा nfs_खोलो_context *ctx = nfs_file_खोलो_context(file);
	काष्ठा nfs_lock_context *l_ctx;
	काष्ठा file_lock_context *flctx = file_inode(file)->i_flctx;
	काष्ठा nfs_page	*req;
	पूर्णांक करो_flush, status;
	/*
	 * Look क्रम a request corresponding to this page. If there
	 * is one, and it beदीर्घs to another file, we flush it out
	 * beक्रमe we try to copy anything पूर्णांकo the page. Do this
	 * due to the lack of an ACCESS-type call in NFSv2.
	 * Also करो the same अगर we find a request from an existing
	 * dropped page.
	 */
	करो अणु
		req = nfs_page_find_head_request(page);
		अगर (req == शून्य)
			वापस 0;
		l_ctx = req->wb_lock_context;
		करो_flush = req->wb_page != page ||
			!nfs_match_खोलो_context(nfs_req_खोलोctx(req), ctx);
		अगर (l_ctx && flctx &&
		    !(list_empty_careful(&flctx->flc_posix) &&
		      list_empty_careful(&flctx->flc_flock))) अणु
			करो_flush |= l_ctx->lockowner != current->files;
		पूर्ण
		nfs_release_request(req);
		अगर (!करो_flush)
			वापस 0;
		status = nfs_wb_page(page_file_mapping(page)->host, page);
	पूर्ण जबतक (status == 0);
	वापस status;
पूर्ण

/*
 * Aव्योम buffered ग_लिखोs when a खोलो context credential's key would
 * expire soon.
 *
 * Returns -EACCES अगर the key will expire within RPC_KEY_EXPIRE_FAIL.
 *
 * Return 0 and set a credential flag which triggers the inode to flush
 * and perक्रमms  NFS_खाता_SYNC ग_लिखोs अगर the key will expired within
 * RPC_KEY_EXPIRE_TIMEO.
 */
पूर्णांक
nfs_key_समयout_notअगरy(काष्ठा file *filp, काष्ठा inode *inode)
अणु
	काष्ठा nfs_खोलो_context *ctx = nfs_file_खोलो_context(filp);

	अगर (nfs_ctx_key_to_expire(ctx, inode) &&
	    !ctx->ll_cred)
		/* Alपढ़ोy expired! */
		वापस -EACCES;
	वापस 0;
पूर्ण

/*
 * Test अगर the खोलो context credential key is marked to expire soon.
 */
bool nfs_ctx_key_to_expire(काष्ठा nfs_खोलो_context *ctx, काष्ठा inode *inode)
अणु
	काष्ठा rpc_auth *auth = NFS_SERVER(inode)->client->cl_auth;
	काष्ठा rpc_cred *cred = ctx->ll_cred;
	काष्ठा auth_cred acred = अणु
		.cred = ctx->cred,
	पूर्ण;

	अगर (cred && !cred->cr_ops->crmatch(&acred, cred, 0)) अणु
		put_rpccred(cred);
		ctx->ll_cred = शून्य;
		cred = शून्य;
	पूर्ण
	अगर (!cred)
		cred = auth->au_ops->lookup_cred(auth, &acred, 0);
	अगर (!cred || IS_ERR(cred))
		वापस true;
	ctx->ll_cred = cred;
	वापस !!(cred->cr_ops->crkey_समयout &&
		  cred->cr_ops->crkey_समयout(cred));
पूर्ण

/*
 * If the page cache is marked as unsafe or invalid, then we can't rely on
 * the PageUptodate() flag. In this हाल, we will need to turn off
 * ग_लिखो optimisations that depend on the page contents being correct.
 */
अटल bool nfs_ग_लिखो_pageuptodate(काष्ठा page *page, काष्ठा inode *inode,
				   अचिन्हित पूर्णांक pagelen)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	अगर (nfs_have_delegated_attributes(inode))
		जाओ out;
	अगर (nfsi->cache_validity &
	    (NFS_INO_INVALID_CHANGE | NFS_INO_INVALID_SIZE))
		वापस false;
	smp_rmb();
	अगर (test_bit(NFS_INO_INVALIDATING, &nfsi->flags) && pagelen != 0)
		वापस false;
out:
	अगर (nfsi->cache_validity & NFS_INO_INVALID_DATA && pagelen != 0)
		वापस false;
	वापस PageUptodate(page) != 0;
पूर्ण

अटल bool
is_whole_file_wrlock(काष्ठा file_lock *fl)
अणु
	वापस fl->fl_start == 0 && fl->fl_end == OFFSET_MAX &&
			fl->fl_type == F_WRLCK;
पूर्ण

/* If we know the page is up to date, and we're not using byte range locks (or
 * अगर we have the whole file locked क्रम writing), it may be more efficient to
 * extend the ग_लिखो to cover the entire page in order to aव्योम fragmentation
 * inefficiencies.
 *
 * If the file is खोलोed क्रम synchronous ग_लिखोs then we can just skip the rest
 * of the checks.
 */
अटल पूर्णांक nfs_can_extend_ग_लिखो(काष्ठा file *file, काष्ठा page *page,
				काष्ठा inode *inode, अचिन्हित पूर्णांक pagelen)
अणु
	पूर्णांक ret;
	काष्ठा file_lock_context *flctx = inode->i_flctx;
	काष्ठा file_lock *fl;

	अगर (file->f_flags & O_DSYNC)
		वापस 0;
	अगर (!nfs_ग_लिखो_pageuptodate(page, inode, pagelen))
		वापस 0;
	अगर (NFS_PROTO(inode)->have_delegation(inode, FMODE_WRITE))
		वापस 1;
	अगर (!flctx || (list_empty_careful(&flctx->flc_flock) &&
		       list_empty_careful(&flctx->flc_posix)))
		वापस 1;

	/* Check to see अगर there are whole file ग_लिखो locks */
	ret = 0;
	spin_lock(&flctx->flc_lock);
	अगर (!list_empty(&flctx->flc_posix)) अणु
		fl = list_first_entry(&flctx->flc_posix, काष्ठा file_lock,
					fl_list);
		अगर (is_whole_file_wrlock(fl))
			ret = 1;
	पूर्ण अन्यथा अगर (!list_empty(&flctx->flc_flock)) अणु
		fl = list_first_entry(&flctx->flc_flock, काष्ठा file_lock,
					fl_list);
		अगर (fl->fl_type == F_WRLCK)
			ret = 1;
	पूर्ण
	spin_unlock(&flctx->flc_lock);
	वापस ret;
पूर्ण

/*
 * Update and possibly ग_लिखो a cached page of an NFS file.
 *
 * XXX: Keep an eye on generic_file_पढ़ो to make sure it करोesn't करो bad
 * things with a page scheduled क्रम an RPC call (e.g. invalidate it).
 */
पूर्णांक nfs_updatepage(काष्ठा file *file, काष्ठा page *page,
		अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक count)
अणु
	काष्ठा nfs_खोलो_context *ctx = nfs_file_खोलो_context(file);
	काष्ठा address_space *mapping = page_file_mapping(page);
	काष्ठा inode	*inode = mapping->host;
	अचिन्हित पूर्णांक	pagelen = nfs_page_length(page);
	पूर्णांक		status = 0;

	nfs_inc_stats(inode, NFSIOS_VFSUPDATEPAGE);

	dprपूर्णांकk("NFS:       nfs_updatepage(%pD2 %d@%lld)\n",
		file, count, (दीर्घ दीर्घ)(page_file_offset(page) + offset));

	अगर (!count)
		जाओ out;

	अगर (nfs_can_extend_ग_लिखो(file, page, inode, pagelen)) अणु
		count = max(count + offset, pagelen);
		offset = 0;
	पूर्ण

	status = nfs_ग_लिखोpage_setup(ctx, page, offset, count);
	अगर (status < 0)
		nfs_set_pageerror(mapping);
	अन्यथा
		__set_page_dirty_nobuffers(page);
out:
	dprपूर्णांकk("NFS:       nfs_updatepage returns %d (isize %lld)\n",
			status, (दीर्घ दीर्घ)i_size_पढ़ो(inode));
	वापस status;
पूर्ण

अटल पूर्णांक flush_task_priority(पूर्णांक how)
अणु
	चयन (how & (FLUSH_HIGHPRI|FLUSH_LOWPRI)) अणु
		हाल FLUSH_HIGHPRI:
			वापस RPC_PRIORITY_HIGH;
		हाल FLUSH_LOWPRI:
			वापस RPC_PRIORITY_LOW;
	पूर्ण
	वापस RPC_PRIORITY_NORMAL;
पूर्ण

अटल व्योम nfs_initiate_ग_लिखो(काष्ठा nfs_pgio_header *hdr,
			       काष्ठा rpc_message *msg,
			       स्थिर काष्ठा nfs_rpc_ops *rpc_ops,
			       काष्ठा rpc_task_setup *task_setup_data, पूर्णांक how)
अणु
	पूर्णांक priority = flush_task_priority(how);

	task_setup_data->priority = priority;
	rpc_ops->ग_लिखो_setup(hdr, msg, &task_setup_data->rpc_client);
	trace_nfs_initiate_ग_लिखो(hdr);
पूर्ण

/* If a nfs_flush_* function fails, it should हटाओ reqs from @head and
 * call this on each, which will prepare them to be retried on next
 * ग_लिखोback using standard nfs.
 */
अटल व्योम nfs_redirty_request(काष्ठा nfs_page *req)
अणु
	/* Bump the transmission count */
	req->wb_nio++;
	nfs_mark_request_dirty(req);
	set_bit(NFS_CONTEXT_RESEND_WRITES, &nfs_req_खोलोctx(req)->flags);
	nfs_end_page_ग_लिखोback(req);
	nfs_release_request(req);
पूर्ण

अटल व्योम nfs_async_ग_लिखो_error(काष्ठा list_head *head, पूर्णांक error)
अणु
	काष्ठा nfs_page	*req;

	जबतक (!list_empty(head)) अणु
		req = nfs_list_entry(head->next);
		nfs_list_हटाओ_request(req);
		अगर (nfs_error_is_fatal(error))
			nfs_ग_लिखो_error(req, error);
		अन्यथा
			nfs_redirty_request(req);
	पूर्ण
पूर्ण

अटल व्योम nfs_async_ग_लिखो_reschedule_io(काष्ठा nfs_pgio_header *hdr)
अणु
	nfs_async_ग_लिखो_error(&hdr->pages, 0);
	filemap_fdataग_लिखो_range(hdr->inode->i_mapping, hdr->args.offset,
			hdr->args.offset + hdr->args.count - 1);
पूर्ण

अटल स्थिर काष्ठा nfs_pgio_completion_ops nfs_async_ग_लिखो_completion_ops = अणु
	.init_hdr = nfs_async_ग_लिखो_init,
	.error_cleanup = nfs_async_ग_लिखो_error,
	.completion = nfs_ग_लिखो_completion,
	.reschedule_io = nfs_async_ग_लिखो_reschedule_io,
पूर्ण;

व्योम nfs_pageio_init_ग_लिखो(काष्ठा nfs_pageio_descriptor *pgio,
			       काष्ठा inode *inode, पूर्णांक ioflags, bool क्रमce_mds,
			       स्थिर काष्ठा nfs_pgio_completion_ops *compl_ops)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	स्थिर काष्ठा nfs_pageio_ops *pg_ops = &nfs_pgio_rw_ops;

#अगर_घोषित CONFIG_NFS_V4_1
	अगर (server->pnfs_curr_ld && !क्रमce_mds)
		pg_ops = server->pnfs_curr_ld->pg_ग_लिखो_ops;
#पूर्ण_अगर
	nfs_pageio_init(pgio, inode, pg_ops, compl_ops, &nfs_rw_ग_लिखो_ops,
			server->wsize, ioflags);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_pageio_init_ग_लिखो);

व्योम nfs_pageio_reset_ग_लिखो_mds(काष्ठा nfs_pageio_descriptor *pgio)
अणु
	काष्ठा nfs_pgio_mirror *mirror;

	अगर (pgio->pg_ops && pgio->pg_ops->pg_cleanup)
		pgio->pg_ops->pg_cleanup(pgio);

	pgio->pg_ops = &nfs_pgio_rw_ops;

	nfs_pageio_stop_mirroring(pgio);

	mirror = &pgio->pg_mirrors[0];
	mirror->pg_bsize = NFS_SERVER(pgio->pg_inode)->wsize;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_pageio_reset_ग_लिखो_mds);


व्योम nfs_commit_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_commit_data *data = calldata;

	NFS_PROTO(data->inode)->commit_rpc_prepare(task, data);
पूर्ण

/*
 * Special version of should_हटाओ_suid() that ignores capabilities.
 */
अटल पूर्णांक nfs_should_हटाओ_suid(स्थिर काष्ठा inode *inode)
अणु
	umode_t mode = inode->i_mode;
	पूर्णांक समाप्त = 0;

	/* suid always must be समाप्तed */
	अगर (unlikely(mode & S_ISUID))
		समाप्त = ATTR_KILL_SUID;

	/*
	 * sgid without any exec bits is just a mandatory locking mark; leave
	 * it alone.  If some exec bits are set, it's a real sgid; समाप्त it.
	 */
	अगर (unlikely((mode & S_ISGID) && (mode & S_IXGRP)))
		समाप्त |= ATTR_KILL_SGID;

	अगर (unlikely(समाप्त && S_ISREG(mode)))
		वापस समाप्त;

	वापस 0;
पूर्ण

अटल व्योम nfs_ग_लिखोback_check_extend(काष्ठा nfs_pgio_header *hdr,
		काष्ठा nfs_fattr *fattr)
अणु
	काष्ठा nfs_pgio_args *argp = &hdr->args;
	काष्ठा nfs_pgio_res *resp = &hdr->res;
	u64 size = argp->offset + resp->count;

	अगर (!(fattr->valid & NFS_ATTR_FATTR_SIZE))
		fattr->size = size;
	अगर (nfs_माप_प्रकारo_loff_t(fattr->size) < i_size_पढ़ो(hdr->inode)) अणु
		fattr->valid &= ~NFS_ATTR_FATTR_SIZE;
		वापस;
	पूर्ण
	अगर (size != fattr->size)
		वापस;
	/* Set attribute barrier */
	nfs_fattr_set_barrier(fattr);
	/* ...and update size */
	fattr->valid |= NFS_ATTR_FATTR_SIZE;
पूर्ण

व्योम nfs_ग_लिखोback_update_inode(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_fattr *fattr = &hdr->fattr;
	काष्ठा inode *inode = hdr->inode;

	spin_lock(&inode->i_lock);
	nfs_ग_लिखोback_check_extend(hdr, fattr);
	nfs_post_op_update_inode_क्रमce_wcc_locked(inode, fattr);
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_ग_लिखोback_update_inode);

/*
 * This function is called when the WRITE call is complete.
 */
अटल पूर्णांक nfs_ग_लिखोback_करोne(काष्ठा rpc_task *task,
			      काष्ठा nfs_pgio_header *hdr,
			      काष्ठा inode *inode)
अणु
	पूर्णांक status;

	/*
	 * ->ग_लिखो_करोne will attempt to use post-op attributes to detect
	 * conflicting ग_लिखोs by other clients.  A strict पूर्णांकerpretation
	 * of बंद-to-खोलो would allow us to जारी caching even अगर
	 * another ग_लिखोr had changed the file, but some applications
	 * depend on tighter cache coherency when writing.
	 */
	status = NFS_PROTO(inode)->ग_लिखो_करोne(task, hdr);
	अगर (status != 0)
		वापस status;

	nfs_add_stats(inode, NFSIOS_SERVERWRITTENBYTES, hdr->res.count);
	trace_nfs_ग_लिखोback_करोne(task, hdr);

	अगर (hdr->res.verf->committed < hdr->args.stable &&
	    task->tk_status >= 0) अणु
		/* We tried a ग_लिखो call, but the server did not
		 * commit data to stable storage even though we
		 * requested it.
		 * Note: There is a known bug in Tru64 < 5.0 in which
		 *	 the server reports NFS_DATA_SYNC, but perक्रमms
		 *	 NFS_खाता_SYNC. We thereक्रमe implement this checking
		 *	 as a dprपूर्णांकk() in order to aव्योम filling syslog.
		 */
		अटल अचिन्हित दीर्घ    complain;

		/* Note this will prपूर्णांक the MDS क्रम a DS ग_लिखो */
		अगर (समय_beक्रमe(complain, jअगरfies)) अणु
			dprपूर्णांकk("NFS:       faulty NFS server %s:"
				" (committed = %d) != (stable = %d)\n",
				NFS_SERVER(inode)->nfs_client->cl_hostname,
				hdr->res.verf->committed, hdr->args.stable);
			complain = jअगरfies + 300 * HZ;
		पूर्ण
	पूर्ण

	/* Deal with the suid/sgid bit corner हाल */
	अगर (nfs_should_हटाओ_suid(inode)) अणु
		spin_lock(&inode->i_lock);
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_MODE);
		spin_unlock(&inode->i_lock);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function is called when the WRITE call is complete.
 */
अटल व्योम nfs_ग_लिखोback_result(काष्ठा rpc_task *task,
				 काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_pgio_args	*argp = &hdr->args;
	काष्ठा nfs_pgio_res	*resp = &hdr->res;

	अगर (resp->count < argp->count) अणु
		अटल अचिन्हित दीर्घ    complain;

		/* This a लघु ग_लिखो! */
		nfs_inc_stats(hdr->inode, NFSIOS_SHORTWRITE);

		/* Has the server at least made some progress? */
		अगर (resp->count == 0) अणु
			अगर (समय_beक्रमe(complain, jअगरfies)) अणु
				prपूर्णांकk(KERN_WARNING
				       "NFS: Server wrote zero bytes, expected %u.\n",
				       argp->count);
				complain = jअगरfies + 300 * HZ;
			पूर्ण
			nfs_set_pgio_error(hdr, -EIO, argp->offset);
			task->tk_status = -EIO;
			वापस;
		पूर्ण

		/* For non rpc-based layout drivers, retry-through-MDS */
		अगर (!task->tk_ops) अणु
			hdr->pnfs_error = -EAGAIN;
			वापस;
		पूर्ण

		/* Was this an NFSv2 ग_लिखो or an NFSv3 stable ग_लिखो? */
		अगर (resp->verf->committed != NFS_UNSTABLE) अणु
			/* Resend from where the server left off */
			hdr->mds_offset += resp->count;
			argp->offset += resp->count;
			argp->pgbase += resp->count;
			argp->count -= resp->count;
		पूर्ण अन्यथा अणु
			/* Resend as a stable ग_लिखो in order to aव्योम
			 * headaches in the हाल of a server crash.
			 */
			argp->stable = NFS_खाता_SYNC;
		पूर्ण
		resp->count = 0;
		resp->verf->committed = 0;
		rpc_restart_call_prepare(task);
	पूर्ण
पूर्ण

अटल पूर्णांक रुको_on_commit(काष्ठा nfs_mds_commit_info *cinfo)
अणु
	वापस रुको_var_event_समाप्तable(&cinfo->rpcs_out,
				       !atomic_पढ़ो(&cinfo->rpcs_out));
पूर्ण

अटल व्योम nfs_commit_begin(काष्ठा nfs_mds_commit_info *cinfo)
अणु
	atomic_inc(&cinfo->rpcs_out);
पूर्ण

अटल व्योम nfs_commit_end(काष्ठा nfs_mds_commit_info *cinfo)
अणु
	अगर (atomic_dec_and_test(&cinfo->rpcs_out))
		wake_up_var(&cinfo->rpcs_out);
पूर्ण

व्योम nfs_commitdata_release(काष्ठा nfs_commit_data *data)
अणु
	put_nfs_खोलो_context(data->context);
	nfs_commit_मुक्त(data);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_commitdata_release);

पूर्णांक nfs_initiate_commit(काष्ठा rpc_clnt *clnt, काष्ठा nfs_commit_data *data,
			स्थिर काष्ठा nfs_rpc_ops *nfs_ops,
			स्थिर काष्ठा rpc_call_ops *call_ops,
			पूर्णांक how, पूर्णांक flags)
अणु
	काष्ठा rpc_task *task;
	पूर्णांक priority = flush_task_priority(how);
	काष्ठा rpc_message msg = अणु
		.rpc_argp = &data->args,
		.rpc_resp = &data->res,
		.rpc_cred = data->cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.task = &data->task,
		.rpc_client = clnt,
		.rpc_message = &msg,
		.callback_ops = call_ops,
		.callback_data = data,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC | flags,
		.priority = priority,
	पूर्ण;
	/* Set up the initial task काष्ठा.  */
	nfs_ops->commit_setup(data, &msg, &task_setup_data.rpc_client);
	trace_nfs_initiate_commit(data);

	dprपूर्णांकk("NFS: initiated commit call\n");

	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	अगर (how & FLUSH_SYNC)
		rpc_रुको_क्रम_completion_task(task);
	rpc_put_task(task);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_initiate_commit);

अटल loff_t nfs_get_lwb(काष्ठा list_head *head)
अणु
	loff_t lwb = 0;
	काष्ठा nfs_page *req;

	list_क्रम_each_entry(req, head, wb_list)
		अगर (lwb < (req_offset(req) + req->wb_bytes))
			lwb = req_offset(req) + req->wb_bytes;

	वापस lwb;
पूर्ण

/*
 * Set up the argument/result storage required क्रम the RPC call.
 */
व्योम nfs_init_commit(काष्ठा nfs_commit_data *data,
		     काष्ठा list_head *head,
		     काष्ठा pnfs_layout_segment *lseg,
		     काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा nfs_page *first;
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा inode *inode;

	/* Set up the RPC argument and reply काष्ठाs
	 * NB: take care not to mess about with data->commit et al. */

	अगर (head)
		list_splice_init(head, &data->pages);

	first = nfs_list_entry(data->pages.next);
	ctx = nfs_req_खोलोctx(first);
	inode = d_inode(ctx->dentry);

	data->inode	  = inode;
	data->cred	  = ctx->cred;
	data->lseg	  = lseg; /* reference transferred */
	/* only set lwb क्रम pnfs commit */
	अगर (lseg)
		data->lwb = nfs_get_lwb(&data->pages);
	data->mds_ops     = &nfs_commit_ops;
	data->completion_ops = cinfo->completion_ops;
	data->dreq	  = cinfo->dreq;

	data->args.fh     = NFS_FH(data->inode);
	/* Note: we always request a commit of the entire inode */
	data->args.offset = 0;
	data->args.count  = 0;
	data->context     = get_nfs_खोलो_context(ctx);
	data->res.fattr   = &data->fattr;
	data->res.verf    = &data->verf;
	nfs_fattr_init(&data->fattr);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_init_commit);

व्योम nfs_retry_commit(काष्ठा list_head *page_list,
		      काष्ठा pnfs_layout_segment *lseg,
		      काष्ठा nfs_commit_info *cinfo,
		      u32 ds_commit_idx)
अणु
	काष्ठा nfs_page *req;

	जबतक (!list_empty(page_list)) अणु
		req = nfs_list_entry(page_list->next);
		nfs_list_हटाओ_request(req);
		nfs_mark_request_commit(req, lseg, cinfo, ds_commit_idx);
		अगर (!cinfo->dreq)
			nfs_clear_page_commit(req->wb_page);
		nfs_unlock_and_release_request(req);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nfs_retry_commit);

अटल व्योम
nfs_commit_resched_ग_लिखो(काष्ठा nfs_commit_info *cinfo,
		काष्ठा nfs_page *req)
अणु
	__set_page_dirty_nobuffers(req->wb_page);
पूर्ण

/*
 * Commit dirty pages
 */
अटल पूर्णांक
nfs_commit_list(काष्ठा inode *inode, काष्ठा list_head *head, पूर्णांक how,
		काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा nfs_commit_data	*data;

	/* another commit raced with us */
	अगर (list_empty(head))
		वापस 0;

	data = nfs_commitdata_alloc(true);

	/* Set up the argument काष्ठा */
	nfs_init_commit(data, head, शून्य, cinfo);
	atomic_inc(&cinfo->mds->rpcs_out);
	वापस nfs_initiate_commit(NFS_CLIENT(inode), data, NFS_PROTO(inode),
				   data->mds_ops, how, RPC_TASK_CRED_NOREF);
पूर्ण

/*
 * COMMIT call वापसed
 */
अटल व्योम nfs_commit_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_commit_data	*data = calldata;

        dprपूर्णांकk("NFS: %5u nfs_commit_done (status %d)\n",
                                task->tk_pid, task->tk_status);

	/* Call the NFS version-specअगरic code */
	NFS_PROTO(data->inode)->commit_करोne(task, data);
	trace_nfs_commit_करोne(task, data);
पूर्ण

अटल व्योम nfs_commit_release_pages(काष्ठा nfs_commit_data *data)
अणु
	स्थिर काष्ठा nfs_ग_लिखोverf *verf = data->res.verf;
	काष्ठा nfs_page	*req;
	पूर्णांक status = data->task.tk_status;
	काष्ठा nfs_commit_info cinfo;
	काष्ठा nfs_server *nfss;

	जबतक (!list_empty(&data->pages)) अणु
		req = nfs_list_entry(data->pages.next);
		nfs_list_हटाओ_request(req);
		अगर (req->wb_page)
			nfs_clear_page_commit(req->wb_page);

		dprपूर्णांकk("NFS:       commit (%s/%llu %d@%lld)",
			nfs_req_खोलोctx(req)->dentry->d_sb->s_id,
			(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(d_inode(nfs_req_खोलोctx(req)->dentry)),
			req->wb_bytes,
			(दीर्घ दीर्घ)req_offset(req));
		अगर (status < 0) अणु
			अगर (req->wb_page) अणु
				trace_nfs_commit_error(req, status);
				nfs_mapping_set_error(req->wb_page, status);
				nfs_inode_हटाओ_request(req);
			पूर्ण
			dprपूर्णांकk_cont(", error = %d\n", status);
			जाओ next;
		पूर्ण

		/* Okay, COMMIT succeeded, apparently. Check the verअगरier
		 * वापसed by the server against all stored verfs. */
		अगर (nfs_ग_लिखो_match_verf(verf, req)) अणु
			/* We have a match */
			अगर (req->wb_page)
				nfs_inode_हटाओ_request(req);
			dprपूर्णांकk_cont(" OK\n");
			जाओ next;
		पूर्ण
		/* We have a mismatch. Write the page again */
		dprपूर्णांकk_cont(" mismatch\n");
		nfs_mark_request_dirty(req);
		set_bit(NFS_CONTEXT_RESEND_WRITES, &nfs_req_खोलोctx(req)->flags);
	next:
		nfs_unlock_and_release_request(req);
		/* Latency अवरोधer */
		cond_resched();
	पूर्ण
	nfss = NFS_SERVER(data->inode);
	अगर (atomic_दीर्घ_पढ़ो(&nfss->ग_लिखोback) < NFS_CONGESTION_OFF_THRESH)
		clear_bdi_congested(inode_to_bdi(data->inode), BLK_RW_ASYNC);

	nfs_init_cinfo(&cinfo, data->inode, data->dreq);
	nfs_commit_end(cinfo.mds);
पूर्ण

अटल व्योम nfs_commit_release(व्योम *calldata)
अणु
	काष्ठा nfs_commit_data *data = calldata;

	data->completion_ops->completion(data);
	nfs_commitdata_release(calldata);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs_commit_ops = अणु
	.rpc_call_prepare = nfs_commit_prepare,
	.rpc_call_करोne = nfs_commit_करोne,
	.rpc_release = nfs_commit_release,
पूर्ण;

अटल स्थिर काष्ठा nfs_commit_completion_ops nfs_commit_completion_ops = अणु
	.completion = nfs_commit_release_pages,
	.resched_ग_लिखो = nfs_commit_resched_ग_लिखो,
पूर्ण;

पूर्णांक nfs_generic_commit_list(काष्ठा inode *inode, काष्ठा list_head *head,
			    पूर्णांक how, काष्ठा nfs_commit_info *cinfo)
अणु
	पूर्णांक status;

	status = pnfs_commit_list(inode, head, how, cinfo);
	अगर (status == PNFS_NOT_ATTEMPTED)
		status = nfs_commit_list(inode, head, how, cinfo);
	वापस status;
पूर्ण

अटल पूर्णांक __nfs_commit_inode(काष्ठा inode *inode, पूर्णांक how,
		काष्ठा ग_लिखोback_control *wbc)
अणु
	LIST_HEAD(head);
	काष्ठा nfs_commit_info cinfo;
	पूर्णांक may_रुको = how & FLUSH_SYNC;
	पूर्णांक ret, nscan;

	nfs_init_cinfo_from_inode(&cinfo, inode);
	nfs_commit_begin(cinfo.mds);
	क्रम (;;) अणु
		ret = nscan = nfs_scan_commit(inode, &head, &cinfo);
		अगर (ret <= 0)
			अवरोध;
		ret = nfs_generic_commit_list(inode, &head, how, &cinfo);
		अगर (ret < 0)
			अवरोध;
		ret = 0;
		अगर (wbc && wbc->sync_mode == WB_SYNC_NONE) अणु
			अगर (nscan < wbc->nr_to_ग_लिखो)
				wbc->nr_to_ग_लिखो -= nscan;
			अन्यथा
				wbc->nr_to_ग_लिखो = 0;
		पूर्ण
		अगर (nscan < पूर्णांक_उच्च)
			अवरोध;
		cond_resched();
	पूर्ण
	nfs_commit_end(cinfo.mds);
	अगर (ret || !may_रुको)
		वापस ret;
	वापस रुको_on_commit(cinfo.mds);
पूर्ण

पूर्णांक nfs_commit_inode(काष्ठा inode *inode, पूर्णांक how)
अणु
	वापस __nfs_commit_inode(inode, how, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_commit_inode);

पूर्णांक nfs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	पूर्णांक flags = FLUSH_SYNC;
	पूर्णांक ret = 0;

	अगर (wbc->sync_mode == WB_SYNC_NONE) अणु
		/* no commits means nothing needs to be करोne */
		अगर (!atomic_दीर्घ_पढ़ो(&nfsi->commit_info.ncommit))
			जाओ check_requests_outstanding;

		/* Don't commit yet अगर this is a non-blocking flush and there
		 * are a lot of outstanding ग_लिखोs क्रम this mapping.
		 */
		अगर (mapping_tagged(inode->i_mapping, PAGECACHE_TAG_WRITEBACK))
			जाओ out_mark_dirty;

		/* करोn't रुको क्रम the COMMIT response */
		flags = 0;
	पूर्ण

	ret = __nfs_commit_inode(inode, flags, wbc);
	अगर (!ret) अणु
		अगर (flags & FLUSH_SYNC)
			वापस 0;
	पूर्ण अन्यथा अगर (atomic_दीर्घ_पढ़ो(&nfsi->commit_info.ncommit))
		जाओ out_mark_dirty;

check_requests_outstanding:
	अगर (!atomic_पढ़ो(&nfsi->commit_info.rpcs_out))
		वापस ret;
out_mark_dirty:
	__mark_inode_dirty(inode, I_सूचीTY_DATASYNC);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_ग_लिखो_inode);

/*
 * Wrapper क्रम filemap_ग_लिखो_and_रुको_range()
 *
 * Needed क्रम pNFS in order to ensure data becomes visible to the
 * client.
 */
पूर्णांक nfs_filemap_ग_लिखो_and_रुको_range(काष्ठा address_space *mapping,
		loff_t lstart, loff_t lend)
अणु
	पूर्णांक ret;

	ret = filemap_ग_लिखो_and_रुको_range(mapping, lstart, lend);
	अगर (ret == 0)
		ret = pnfs_sync_inode(mapping->host, true);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_filemap_ग_लिखो_and_रुको_range);

/*
 * flush the inode to disk.
 */
पूर्णांक nfs_wb_all(काष्ठा inode *inode)
अणु
	पूर्णांक ret;

	trace_nfs_ग_लिखोback_inode_enter(inode);

	ret = filemap_ग_लिखो_and_रुको(inode->i_mapping);
	अगर (ret)
		जाओ out;
	ret = nfs_commit_inode(inode, FLUSH_SYNC);
	अगर (ret < 0)
		जाओ out;
	pnfs_sync_inode(inode, true);
	ret = 0;

out:
	trace_nfs_ग_लिखोback_inode_निकास(inode, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_wb_all);

पूर्णांक nfs_wb_page_cancel(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा nfs_page *req;
	पूर्णांक ret = 0;

	रुको_on_page_ग_लिखोback(page);

	/* blocking call to cancel all requests and join to a single (head)
	 * request */
	req = nfs_lock_and_join_requests(page);

	अगर (IS_ERR(req)) अणु
		ret = PTR_ERR(req);
	पूर्ण अन्यथा अगर (req) अणु
		/* all requests from this page have been cancelled by
		 * nfs_lock_and_join_requests, so just हटाओ the head
		 * request from the inode / page_निजी poपूर्णांकer and
		 * release it */
		nfs_inode_हटाओ_request(req);
		nfs_unlock_and_release_request(req);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Write back all requests on one page - we करो this beक्रमe पढ़ोing it.
 */
पूर्णांक nfs_wb_page(काष्ठा inode *inode, काष्ठा page *page)
अणु
	loff_t range_start = page_file_offset(page);
	loff_t range_end = range_start + (loff_t)(PAGE_SIZE - 1);
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_ALL,
		.nr_to_ग_लिखो = 0,
		.range_start = range_start,
		.range_end = range_end,
	पूर्ण;
	पूर्णांक ret;

	trace_nfs_ग_लिखोback_page_enter(inode);

	क्रम (;;) अणु
		रुको_on_page_ग_लिखोback(page);
		अगर (clear_page_dirty_क्रम_io(page)) अणु
			ret = nfs_ग_लिखोpage_locked(page, &wbc);
			अगर (ret < 0)
				जाओ out_error;
			जारी;
		पूर्ण
		ret = 0;
		अगर (!PagePrivate(page))
			अवरोध;
		ret = nfs_commit_inode(inode, FLUSH_SYNC);
		अगर (ret < 0)
			जाओ out_error;
	पूर्ण
out_error:
	trace_nfs_ग_लिखोback_page_निकास(inode, ret);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_MIGRATION
पूर्णांक nfs_migrate_page(काष्ठा address_space *mapping, काष्ठा page *newpage,
		काष्ठा page *page, क्रमागत migrate_mode mode)
अणु
	/*
	 * If PagePrivate is set, then the page is currently associated with
	 * an in-progress पढ़ो or ग_लिखो request. Don't try to migrate it.
	 *
	 * FIXME: we could करो this in principle, but we'll need a way to ensure
	 *        that we can safely release the inode reference जबतक holding
	 *        the page lock.
	 */
	अगर (PagePrivate(page))
		वापस -EBUSY;

	अगर (!nfs_fscache_release_page(page, GFP_KERNEL))
		वापस -EBUSY;

	वापस migrate_page(mapping, newpage, page, mode);
पूर्ण
#पूर्ण_अगर

पूर्णांक __init nfs_init_ग_लिखोpagecache(व्योम)
अणु
	nfs_wdata_cachep = kmem_cache_create("nfs_write_data",
					     माप(काष्ठा nfs_pgio_header),
					     0, SLAB_HWCACHE_ALIGN,
					     शून्य);
	अगर (nfs_wdata_cachep == शून्य)
		वापस -ENOMEM;

	nfs_wdata_mempool = mempool_create_slab_pool(MIN_POOL_WRITE,
						     nfs_wdata_cachep);
	अगर (nfs_wdata_mempool == शून्य)
		जाओ out_destroy_ग_लिखो_cache;

	nfs_cdata_cachep = kmem_cache_create("nfs_commit_data",
					     माप(काष्ठा nfs_commit_data),
					     0, SLAB_HWCACHE_ALIGN,
					     शून्य);
	अगर (nfs_cdata_cachep == शून्य)
		जाओ out_destroy_ग_लिखो_mempool;

	nfs_commit_mempool = mempool_create_slab_pool(MIN_POOL_COMMIT,
						      nfs_cdata_cachep);
	अगर (nfs_commit_mempool == शून्य)
		जाओ out_destroy_commit_cache;

	/*
	 * NFS congestion size, scale with available memory.
	 *
	 *  64MB:    8192k
	 * 128MB:   11585k
	 * 256MB:   16384k
	 * 512MB:   23170k
	 *   1GB:   32768k
	 *   2GB:   46340k
	 *   4GB:   65536k
	 *   8GB:   92681k
	 *  16GB:  131072k
	 *
	 * This allows larger machines to have larger/more transfers.
	 * Limit the शेष to 256M
	 */
	nfs_congestion_kb = (16*पूर्णांक_वर्ग_मूल(totalram_pages())) << (PAGE_SHIFT-10);
	अगर (nfs_congestion_kb > 256*1024)
		nfs_congestion_kb = 256*1024;

	वापस 0;

out_destroy_commit_cache:
	kmem_cache_destroy(nfs_cdata_cachep);
out_destroy_ग_लिखो_mempool:
	mempool_destroy(nfs_wdata_mempool);
out_destroy_ग_लिखो_cache:
	kmem_cache_destroy(nfs_wdata_cachep);
	वापस -ENOMEM;
पूर्ण

व्योम nfs_destroy_ग_लिखोpagecache(व्योम)
अणु
	mempool_destroy(nfs_commit_mempool);
	kmem_cache_destroy(nfs_cdata_cachep);
	mempool_destroy(nfs_wdata_mempool);
	kmem_cache_destroy(nfs_wdata_cachep);
पूर्ण

अटल स्थिर काष्ठा nfs_rw_ops nfs_rw_ग_लिखो_ops = अणु
	.rw_alloc_header	= nfs_ग_लिखोhdr_alloc,
	.rw_मुक्त_header		= nfs_ग_लिखोhdr_मुक्त,
	.rw_करोne		= nfs_ग_लिखोback_करोne,
	.rw_result		= nfs_ग_लिखोback_result,
	.rw_initiate		= nfs_initiate_ग_लिखो,
पूर्ण;
