<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/nfs/pagelist.c
 *
 * A set of helper functions क्रम managing NFS पढ़ो and ग_लिखो requests.
 * The मुख्य purpose of these routines is to provide support क्रम the
 * coalescing of several requests पूर्णांकo a single RPC call.
 *
 * Copyright 2000, 2001 (c) Trond Myklebust <trond.myklebust@fys.uio.no>
 *
 */

#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/sched.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs3.h>
#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/export.h>

#समावेश "internal.h"
#समावेश "pnfs.h"
#समावेश "nfstrace.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PAGECACHE

अटल काष्ठा kmem_cache *nfs_page_cachep;
अटल स्थिर काष्ठा rpc_call_ops nfs_pgio_common_ops;

अटल काष्ठा nfs_pgio_mirror *
nfs_pgio_get_mirror(काष्ठा nfs_pageio_descriptor *desc, u32 idx)
अणु
	अगर (desc->pg_ops->pg_get_mirror)
		वापस desc->pg_ops->pg_get_mirror(desc, idx);
	वापस &desc->pg_mirrors[0];
पूर्ण

काष्ठा nfs_pgio_mirror *
nfs_pgio_current_mirror(काष्ठा nfs_pageio_descriptor *desc)
अणु
	वापस nfs_pgio_get_mirror(desc, desc->pg_mirror_idx);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_pgio_current_mirror);

अटल u32
nfs_pgio_set_current_mirror(काष्ठा nfs_pageio_descriptor *desc, u32 idx)
अणु
	अगर (desc->pg_ops->pg_set_mirror)
		वापस desc->pg_ops->pg_set_mirror(desc, idx);
	वापस desc->pg_mirror_idx;
पूर्ण

व्योम nfs_pgheader_init(काष्ठा nfs_pageio_descriptor *desc,
		       काष्ठा nfs_pgio_header *hdr,
		       व्योम (*release)(काष्ठा nfs_pgio_header *hdr))
अणु
	काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);


	hdr->req = nfs_list_entry(mirror->pg_list.next);
	hdr->inode = desc->pg_inode;
	hdr->cred = nfs_req_खोलोctx(hdr->req)->cred;
	hdr->io_start = req_offset(hdr->req);
	hdr->good_bytes = mirror->pg_count;
	hdr->io_completion = desc->pg_io_completion;
	hdr->dreq = desc->pg_dreq;
	hdr->release = release;
	hdr->completion_ops = desc->pg_completion_ops;
	अगर (hdr->completion_ops->init_hdr)
		hdr->completion_ops->init_hdr(hdr);

	hdr->pgio_mirror_idx = desc->pg_mirror_idx;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_pgheader_init);

व्योम nfs_set_pgio_error(काष्ठा nfs_pgio_header *hdr, पूर्णांक error, loff_t pos)
अणु
	अचिन्हित पूर्णांक new = pos - hdr->io_start;

	trace_nfs_pgio_error(hdr, error, pos);
	अगर (hdr->good_bytes > new) अणु
		hdr->good_bytes = new;
		clear_bit(NFS_IOHDR_खातापूर्ण, &hdr->flags);
		अगर (!test_and_set_bit(NFS_IOHDR_ERROR, &hdr->flags))
			hdr->error = error;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा nfs_page *
nfs_page_alloc(व्योम)
अणु
	काष्ठा nfs_page	*p = kmem_cache_zalloc(nfs_page_cachep, GFP_KERNEL);
	अगर (p)
		INIT_LIST_HEAD(&p->wb_list);
	वापस p;
पूर्ण

अटल अंतरभूत व्योम
nfs_page_मुक्त(काष्ठा nfs_page *p)
अणु
	kmem_cache_मुक्त(nfs_page_cachep, p);
पूर्ण

/**
 * nfs_iocounter_रुको - रुको क्रम i/o to complete
 * @l_ctx: nfs_lock_context with io_counter to use
 *
 * वापसs -ERESTARTSYS अगर पूर्णांकerrupted by a fatal संकेत.
 * Otherwise वापसs 0 once the io_count hits 0.
 */
पूर्णांक
nfs_iocounter_रुको(काष्ठा nfs_lock_context *l_ctx)
अणु
	वापस रुको_var_event_समाप्तable(&l_ctx->io_count,
				       !atomic_पढ़ो(&l_ctx->io_count));
पूर्ण

/**
 * nfs_async_iocounter_रुको - रुको on a rpc_रुकोqueue क्रम I/O
 * to complete
 * @task: the rpc_task that should रुको
 * @l_ctx: nfs_lock_context with io_counter to check
 *
 * Returns true अगर there is outstanding I/O to रुको on and the
 * task has been put to sleep.
 */
bool
nfs_async_iocounter_रुको(काष्ठा rpc_task *task, काष्ठा nfs_lock_context *l_ctx)
अणु
	काष्ठा inode *inode = d_inode(l_ctx->खोलो_context->dentry);
	bool ret = false;

	अगर (atomic_पढ़ो(&l_ctx->io_count) > 0) अणु
		rpc_sleep_on(&NFS_SERVER(inode)->uoc_rpcरुकोq, task, शून्य);
		ret = true;
	पूर्ण

	अगर (atomic_पढ़ो(&l_ctx->io_count) == 0) अणु
		rpc_wake_up_queued_task(&NFS_SERVER(inode)->uoc_rpcरुकोq, task);
		ret = false;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_async_iocounter_रुको);

/*
 * nfs_page_lock_head_request - page lock the head of the page group
 * @req: any member of the page group
 */
काष्ठा nfs_page *
nfs_page_group_lock_head(काष्ठा nfs_page *req)
अणु
	काष्ठा nfs_page *head = req->wb_head;

	जबतक (!nfs_lock_request(head)) अणु
		पूर्णांक ret = nfs_रुको_on_request(head);
		अगर (ret < 0)
			वापस ERR_PTR(ret);
	पूर्ण
	अगर (head != req)
		kref_get(&head->wb_kref);
	वापस head;
पूर्ण

/*
 * nfs_unroll_locks -  unlock all newly locked reqs and रुको on @req
 * @head: head request of page group, must be holding head lock
 * @req: request that couldn't lock and needs to रुको on the req bit lock
 *
 * This is a helper function क्रम nfs_lock_and_join_requests
 * वापसs 0 on success, < 0 on error.
 */
अटल व्योम
nfs_unroll_locks(काष्ठा nfs_page *head, काष्ठा nfs_page *req)
अणु
	काष्ठा nfs_page *पंचांगp;

	/* relinquish all the locks successfully grabbed this run */
	क्रम (पंचांगp = head->wb_this_page ; पंचांगp != req; पंचांगp = पंचांगp->wb_this_page) अणु
		अगर (!kref_पढ़ो(&पंचांगp->wb_kref))
			जारी;
		nfs_unlock_and_release_request(पंचांगp);
	पूर्ण
पूर्ण

/*
 * nfs_page_group_lock_subreq -  try to lock a subrequest
 * @head: head request of page group
 * @subreq: request to lock
 *
 * This is a helper function क्रम nfs_lock_and_join_requests which
 * must be called with the head request and page group both locked.
 * On error, it वापसs with the page group unlocked.
 */
अटल पूर्णांक
nfs_page_group_lock_subreq(काष्ठा nfs_page *head, काष्ठा nfs_page *subreq)
अणु
	पूर्णांक ret;

	अगर (!kref_get_unless_zero(&subreq->wb_kref))
		वापस 0;
	जबतक (!nfs_lock_request(subreq)) अणु
		nfs_page_group_unlock(head);
		ret = nfs_रुको_on_request(subreq);
		अगर (!ret)
			ret = nfs_page_group_lock(head);
		अगर (ret < 0) अणु
			nfs_unroll_locks(head, subreq);
			nfs_release_request(subreq);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * nfs_page_group_lock_subrequests -  try to lock the subrequests
 * @head: head request of page group
 *
 * This is a helper function क्रम nfs_lock_and_join_requests which
 * must be called with the head request locked.
 */
पूर्णांक nfs_page_group_lock_subrequests(काष्ठा nfs_page *head)
अणु
	काष्ठा nfs_page *subreq;
	पूर्णांक ret;

	ret = nfs_page_group_lock(head);
	अगर (ret < 0)
		वापस ret;
	/* lock each request in the page group */
	क्रम (subreq = head->wb_this_page; subreq != head;
			subreq = subreq->wb_this_page) अणु
		ret = nfs_page_group_lock_subreq(head, subreq);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	nfs_page_group_unlock(head);
	वापस 0;
पूर्ण

/*
 * nfs_page_set_headlock - set the request PG_HEADLOCK
 * @req: request that is to be locked
 *
 * this lock must be held when modअगरying req->wb_head
 *
 * वापस 0 on success, < 0 on error
 */
पूर्णांक
nfs_page_set_headlock(काष्ठा nfs_page *req)
अणु
	अगर (!test_and_set_bit(PG_HEADLOCK, &req->wb_flags))
		वापस 0;

	set_bit(PG_CONTENDED1, &req->wb_flags);
	smp_mb__after_atomic();
	वापस रुको_on_bit_lock(&req->wb_flags, PG_HEADLOCK,
				TASK_UNINTERRUPTIBLE);
पूर्ण

/*
 * nfs_page_clear_headlock - clear the request PG_HEADLOCK
 * @req: request that is to be locked
 */
व्योम
nfs_page_clear_headlock(काष्ठा nfs_page *req)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(PG_HEADLOCK, &req->wb_flags);
	smp_mb__after_atomic();
	अगर (!test_bit(PG_CONTENDED1, &req->wb_flags))
		वापस;
	wake_up_bit(&req->wb_flags, PG_HEADLOCK);
पूर्ण

/*
 * nfs_page_group_lock - lock the head of the page group
 * @req: request in group that is to be locked
 *
 * this lock must be held when traversing or modअगरying the page
 * group list
 *
 * वापस 0 on success, < 0 on error
 */
पूर्णांक
nfs_page_group_lock(काष्ठा nfs_page *req)
अणु
	पूर्णांक ret;

	ret = nfs_page_set_headlock(req);
	अगर (ret || req->wb_head == req)
		वापस ret;
	वापस nfs_page_set_headlock(req->wb_head);
पूर्ण

/*
 * nfs_page_group_unlock - unlock the head of the page group
 * @req: request in group that is to be unlocked
 */
व्योम
nfs_page_group_unlock(काष्ठा nfs_page *req)
अणु
	अगर (req != req->wb_head)
		nfs_page_clear_headlock(req->wb_head);
	nfs_page_clear_headlock(req);
पूर्ण

/*
 * nfs_page_group_sync_on_bit_locked
 *
 * must be called with page group lock held
 */
अटल bool
nfs_page_group_sync_on_bit_locked(काष्ठा nfs_page *req, अचिन्हित पूर्णांक bit)
अणु
	काष्ठा nfs_page *head = req->wb_head;
	काष्ठा nfs_page *पंचांगp;

	WARN_ON_ONCE(!test_bit(PG_HEADLOCK, &head->wb_flags));
	WARN_ON_ONCE(test_and_set_bit(bit, &req->wb_flags));

	पंचांगp = req->wb_this_page;
	जबतक (पंचांगp != req) अणु
		अगर (!test_bit(bit, &पंचांगp->wb_flags))
			वापस false;
		पंचांगp = पंचांगp->wb_this_page;
	पूर्ण

	/* true! reset all bits */
	पंचांगp = req;
	करो अणु
		clear_bit(bit, &पंचांगp->wb_flags);
		पंचांगp = पंचांगp->wb_this_page;
	पूर्ण जबतक (पंचांगp != req);

	वापस true;
पूर्ण

/*
 * nfs_page_group_sync_on_bit - set bit on current request, but only
 *   वापस true अगर the bit is set क्रम all requests in page group
 * @req - request in page group
 * @bit - PG_* bit that is used to sync page group
 */
bool nfs_page_group_sync_on_bit(काष्ठा nfs_page *req, अचिन्हित पूर्णांक bit)
अणु
	bool ret;

	nfs_page_group_lock(req);
	ret = nfs_page_group_sync_on_bit_locked(req, bit);
	nfs_page_group_unlock(req);

	वापस ret;
पूर्ण

/*
 * nfs_page_group_init - Initialize the page group linkage क्रम @req
 * @req - a new nfs request
 * @prev - the previous request in page group, or शून्य अगर @req is the first
 *         or only request in the group (the head).
 */
अटल अंतरभूत व्योम
nfs_page_group_init(काष्ठा nfs_page *req, काष्ठा nfs_page *prev)
अणु
	काष्ठा inode *inode;
	WARN_ON_ONCE(prev == req);

	अगर (!prev) अणु
		/* a head request */
		req->wb_head = req;
		req->wb_this_page = req;
	पूर्ण अन्यथा अणु
		/* a subrequest */
		WARN_ON_ONCE(prev->wb_this_page != prev->wb_head);
		WARN_ON_ONCE(!test_bit(PG_HEADLOCK, &prev->wb_head->wb_flags));
		req->wb_head = prev->wb_head;
		req->wb_this_page = prev->wb_this_page;
		prev->wb_this_page = req;

		/* All subrequests take a ref on the head request until
		 * nfs_page_group_destroy is called */
		kref_get(&req->wb_head->wb_kref);

		/* grab extra ref and bump the request count अगर head request
		 * has extra ref from the ग_लिखो/commit path to handle hanकरोff
		 * between ग_लिखो and commit lists. */
		अगर (test_bit(PG_INODE_REF, &prev->wb_head->wb_flags)) अणु
			inode = page_file_mapping(req->wb_page)->host;
			set_bit(PG_INODE_REF, &req->wb_flags);
			kref_get(&req->wb_kref);
			atomic_दीर्घ_inc(&NFS_I(inode)->nrequests);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * nfs_page_group_destroy - sync the deकाष्ठाion of page groups
 * @req - request that no दीर्घer needs the page group
 *
 * releases the page group reference from each member once all
 * members have called this function.
 */
अटल व्योम
nfs_page_group_destroy(काष्ठा kref *kref)
अणु
	काष्ठा nfs_page *req = container_of(kref, काष्ठा nfs_page, wb_kref);
	काष्ठा nfs_page *head = req->wb_head;
	काष्ठा nfs_page *पंचांगp, *next;

	अगर (!nfs_page_group_sync_on_bit(req, PG_TEARDOWN))
		जाओ out;

	पंचांगp = req;
	करो अणु
		next = पंचांगp->wb_this_page;
		/* unlink and मुक्त */
		पंचांगp->wb_this_page = पंचांगp;
		पंचांगp->wb_head = पंचांगp;
		nfs_मुक्त_request(पंचांगp);
		पंचांगp = next;
	पूर्ण जबतक (पंचांगp != req);
out:
	/* subrequests must release the ref on the head request */
	अगर (head != req)
		nfs_release_request(head);
पूर्ण

अटल काष्ठा nfs_page *
__nfs_create_request(काष्ठा nfs_lock_context *l_ctx, काष्ठा page *page,
		   अचिन्हित पूर्णांक pgbase, अचिन्हित पूर्णांक offset,
		   अचिन्हित पूर्णांक count)
अणु
	काष्ठा nfs_page		*req;
	काष्ठा nfs_खोलो_context *ctx = l_ctx->खोलो_context;

	अगर (test_bit(NFS_CONTEXT_BAD, &ctx->flags))
		वापस ERR_PTR(-EBADF);
	/* try to allocate the request काष्ठा */
	req = nfs_page_alloc();
	अगर (req == शून्य)
		वापस ERR_PTR(-ENOMEM);

	req->wb_lock_context = l_ctx;
	refcount_inc(&l_ctx->count);
	atomic_inc(&l_ctx->io_count);

	/* Initialize the request काष्ठा. Initially, we assume a
	 * दीर्घ ग_लिखो-back delay. This will be adjusted in
	 * update_nfs_request below अगर the region is not locked. */
	req->wb_page    = page;
	अगर (page) अणु
		req->wb_index = page_index(page);
		get_page(page);
	पूर्ण
	req->wb_offset  = offset;
	req->wb_pgbase	= pgbase;
	req->wb_bytes   = count;
	kref_init(&req->wb_kref);
	req->wb_nio = 0;
	वापस req;
पूर्ण

/**
 * nfs_create_request - Create an NFS पढ़ो/ग_लिखो request.
 * @ctx: खोलो context to use
 * @page: page to ग_लिखो
 * @offset: starting offset within the page क्रम the ग_लिखो
 * @count: number of bytes to पढ़ो/ग_लिखो
 *
 * The page must be locked by the caller. This makes sure we never
 * create two dअगरferent requests क्रम the same page.
 * User should ensure it is safe to sleep in this function.
 */
काष्ठा nfs_page *
nfs_create_request(काष्ठा nfs_खोलो_context *ctx, काष्ठा page *page,
		   अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक count)
अणु
	काष्ठा nfs_lock_context *l_ctx = nfs_get_lock_context(ctx);
	काष्ठा nfs_page *ret;

	अगर (IS_ERR(l_ctx))
		वापस ERR_CAST(l_ctx);
	ret = __nfs_create_request(l_ctx, page, offset, offset, count);
	अगर (!IS_ERR(ret))
		nfs_page_group_init(ret, शून्य);
	nfs_put_lock_context(l_ctx);
	वापस ret;
पूर्ण

अटल काष्ठा nfs_page *
nfs_create_subreq(काष्ठा nfs_page *req,
		  अचिन्हित पूर्णांक pgbase,
		  अचिन्हित पूर्णांक offset,
		  अचिन्हित पूर्णांक count)
अणु
	काष्ठा nfs_page *last;
	काष्ठा nfs_page *ret;

	ret = __nfs_create_request(req->wb_lock_context, req->wb_page,
			pgbase, offset, count);
	अगर (!IS_ERR(ret)) अणु
		/* find the last request */
		क्रम (last = req->wb_head;
		     last->wb_this_page != req->wb_head;
		     last = last->wb_this_page)
			;

		nfs_lock_request(ret);
		ret->wb_index = req->wb_index;
		nfs_page_group_init(ret, last);
		ret->wb_nio = req->wb_nio;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * nfs_unlock_request - Unlock request and wake up sleepers.
 * @req: poपूर्णांकer to request
 */
व्योम nfs_unlock_request(काष्ठा nfs_page *req)
अणु
	अगर (!NFS_WBACK_BUSY(req)) अणु
		prपूर्णांकk(KERN_ERR "NFS: Invalid unlock attempted\n");
		BUG();
	पूर्ण
	smp_mb__beक्रमe_atomic();
	clear_bit(PG_BUSY, &req->wb_flags);
	smp_mb__after_atomic();
	अगर (!test_bit(PG_CONTENDED2, &req->wb_flags))
		वापस;
	wake_up_bit(&req->wb_flags, PG_BUSY);
पूर्ण

/**
 * nfs_unlock_and_release_request - Unlock request and release the nfs_page
 * @req: poपूर्णांकer to request
 */
व्योम nfs_unlock_and_release_request(काष्ठा nfs_page *req)
अणु
	nfs_unlock_request(req);
	nfs_release_request(req);
पूर्ण

/*
 * nfs_clear_request - Free up all resources allocated to the request
 * @req:
 *
 * Release page and खोलो context resources associated with a पढ़ो/ग_लिखो
 * request after it has completed.
 */
अटल व्योम nfs_clear_request(काष्ठा nfs_page *req)
अणु
	काष्ठा page *page = req->wb_page;
	काष्ठा nfs_lock_context *l_ctx = req->wb_lock_context;
	काष्ठा nfs_खोलो_context *ctx;

	अगर (page != शून्य) अणु
		put_page(page);
		req->wb_page = शून्य;
	पूर्ण
	अगर (l_ctx != शून्य) अणु
		अगर (atomic_dec_and_test(&l_ctx->io_count)) अणु
			wake_up_var(&l_ctx->io_count);
			ctx = l_ctx->खोलो_context;
			अगर (test_bit(NFS_CONTEXT_UNLOCK, &ctx->flags))
				rpc_wake_up(&NFS_SERVER(d_inode(ctx->dentry))->uoc_rpcरुकोq);
		पूर्ण
		nfs_put_lock_context(l_ctx);
		req->wb_lock_context = शून्य;
	पूर्ण
पूर्ण

/**
 * nfs_मुक्त_request - Release the count on an NFS पढ़ो/ग_लिखो request
 * @req: request to release
 *
 * Note: Should never be called with the spinlock held!
 */
व्योम nfs_मुक्त_request(काष्ठा nfs_page *req)
अणु
	WARN_ON_ONCE(req->wb_this_page != req);

	/* extra debug: make sure no sync bits are still set */
	WARN_ON_ONCE(test_bit(PG_TEARDOWN, &req->wb_flags));
	WARN_ON_ONCE(test_bit(PG_UNLOCKPAGE, &req->wb_flags));
	WARN_ON_ONCE(test_bit(PG_UPTODATE, &req->wb_flags));
	WARN_ON_ONCE(test_bit(PG_WB_END, &req->wb_flags));
	WARN_ON_ONCE(test_bit(PG_REMOVE, &req->wb_flags));

	/* Release काष्ठा file and खोलो context */
	nfs_clear_request(req);
	nfs_page_मुक्त(req);
पूर्ण

व्योम nfs_release_request(काष्ठा nfs_page *req)
अणु
	kref_put(&req->wb_kref, nfs_page_group_destroy);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_release_request);

/**
 * nfs_रुको_on_request - Wait क्रम a request to complete.
 * @req: request to रुको upon.
 *
 * Interruptible by fatal संकेतs only.
 * The user is responsible क्रम holding a count on the request.
 */
पूर्णांक
nfs_रुको_on_request(काष्ठा nfs_page *req)
अणु
	अगर (!test_bit(PG_BUSY, &req->wb_flags))
		वापस 0;
	set_bit(PG_CONTENDED2, &req->wb_flags);
	smp_mb__after_atomic();
	वापस रुको_on_bit_io(&req->wb_flags, PG_BUSY,
			      TASK_UNINTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_रुको_on_request);

/*
 * nfs_generic_pg_test - determine अगर requests can be coalesced
 * @desc: poपूर्णांकer to descriptor
 * @prev: previous request in desc, or शून्य
 * @req: this request
 *
 * Returns zero अगर @req cannot be coalesced पूर्णांकo @desc, otherwise it वापसs
 * the size of the request.
 */
माप_प्रकार nfs_generic_pg_test(काष्ठा nfs_pageio_descriptor *desc,
			   काष्ठा nfs_page *prev, काष्ठा nfs_page *req)
अणु
	काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);


	अगर (mirror->pg_count > mirror->pg_bsize) अणु
		/* should never happen */
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण

	/*
	 * Limit the request size so that we can still allocate a page array
	 * क्रम it without upsetting the slab allocator.
	 */
	अगर (((mirror->pg_count + req->wb_bytes) >> PAGE_SHIFT) *
			माप(काष्ठा page *) > PAGE_SIZE)
		वापस 0;

	वापस min(mirror->pg_bsize - mirror->pg_count, (माप_प्रकार)req->wb_bytes);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_generic_pg_test);

काष्ठा nfs_pgio_header *nfs_pgio_header_alloc(स्थिर काष्ठा nfs_rw_ops *ops)
अणु
	काष्ठा nfs_pgio_header *hdr = ops->rw_alloc_header();

	अगर (hdr) अणु
		INIT_LIST_HEAD(&hdr->pages);
		hdr->rw_ops = ops;
	पूर्ण
	वापस hdr;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_pgio_header_alloc);

/**
 * nfs_pgio_data_destroy - make @hdr suitable क्रम reuse
 *
 * Frees memory and releases refs from nfs_generic_pgio, so that it may
 * be called again.
 *
 * @hdr: A header that has had nfs_generic_pgio called
 */
अटल व्योम nfs_pgio_data_destroy(काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (hdr->args.context)
		put_nfs_खोलो_context(hdr->args.context);
	अगर (hdr->page_array.pagevec != hdr->page_array.page_array)
		kमुक्त(hdr->page_array.pagevec);
पूर्ण

/*
 * nfs_pgio_header_मुक्त - Free a पढ़ो or ग_लिखो header
 * @hdr: The header to मुक्त
 */
व्योम nfs_pgio_header_मुक्त(काष्ठा nfs_pgio_header *hdr)
अणु
	nfs_pgio_data_destroy(hdr);
	hdr->rw_ops->rw_मुक्त_header(hdr);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_pgio_header_मुक्त);

/**
 * nfs_pgio_rpcsetup - Set up arguments क्रम a pageio call
 * @hdr: The pageio hdr
 * @count: Number of bytes to पढ़ो
 * @how: How to commit data (ग_लिखोs only)
 * @cinfo: Commit inक्रमmation क्रम the call (ग_लिखोs only)
 */
अटल व्योम nfs_pgio_rpcsetup(काष्ठा nfs_pgio_header *hdr,
			      अचिन्हित पूर्णांक count,
			      पूर्णांक how, काष्ठा nfs_commit_info *cinfo)
अणु
	काष्ठा nfs_page *req = hdr->req;

	/* Set up the RPC argument and reply काष्ठाs
	 * NB: take care not to mess about with hdr->commit et al. */

	hdr->args.fh     = NFS_FH(hdr->inode);
	hdr->args.offset = req_offset(req);
	/* pnfs_set_layoutcommit needs this */
	hdr->mds_offset = hdr->args.offset;
	hdr->args.pgbase = req->wb_pgbase;
	hdr->args.pages  = hdr->page_array.pagevec;
	hdr->args.count  = count;
	hdr->args.context = get_nfs_खोलो_context(nfs_req_खोलोctx(req));
	hdr->args.lock_context = req->wb_lock_context;
	hdr->args.stable  = NFS_UNSTABLE;
	चयन (how & (FLUSH_STABLE | FLUSH_COND_STABLE)) अणु
	हाल 0:
		अवरोध;
	हाल FLUSH_COND_STABLE:
		अगर (nfs_reqs_to_commit(cinfo))
			अवरोध;
		fallthrough;
	शेष:
		hdr->args.stable = NFS_खाता_SYNC;
	पूर्ण

	hdr->res.fattr   = &hdr->fattr;
	hdr->res.count   = 0;
	hdr->res.eof     = 0;
	hdr->res.verf    = &hdr->verf;
	nfs_fattr_init(&hdr->fattr);
पूर्ण

/**
 * nfs_pgio_prepare - Prepare pageio hdr to go over the wire
 * @task: The current task
 * @calldata: pageio header to prepare
 */
अटल व्योम nfs_pgio_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_pgio_header *hdr = calldata;
	पूर्णांक err;
	err = NFS_PROTO(hdr->inode)->pgio_rpc_prepare(task, hdr);
	अगर (err)
		rpc_निकास(task, err);
पूर्ण

पूर्णांक nfs_initiate_pgio(काष्ठा rpc_clnt *clnt, काष्ठा nfs_pgio_header *hdr,
		      स्थिर काष्ठा cred *cred, स्थिर काष्ठा nfs_rpc_ops *rpc_ops,
		      स्थिर काष्ठा rpc_call_ops *call_ops, पूर्णांक how, पूर्णांक flags)
अणु
	काष्ठा rpc_task *task;
	काष्ठा rpc_message msg = अणु
		.rpc_argp = &hdr->args,
		.rpc_resp = &hdr->res,
		.rpc_cred = cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = clnt,
		.task = &hdr->task,
		.rpc_message = &msg,
		.callback_ops = call_ops,
		.callback_data = hdr,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC | flags,
	पूर्ण;

	hdr->rw_ops->rw_initiate(hdr, &msg, rpc_ops, &task_setup_data, how);

	dprपूर्णांकk("NFS: initiated pgio call "
		"(req %s/%llu, %u bytes @ offset %llu)\n",
		hdr->inode->i_sb->s_id,
		(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(hdr->inode),
		hdr->args.count,
		(अचिन्हित दीर्घ दीर्घ)hdr->args.offset);

	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	rpc_put_task(task);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_initiate_pgio);

/**
 * nfs_pgio_error - Clean up from a pageio error
 * @hdr: pageio header
 */
अटल व्योम nfs_pgio_error(काष्ठा nfs_pgio_header *hdr)
अणु
	set_bit(NFS_IOHDR_REDO, &hdr->flags);
	hdr->completion_ops->completion(hdr);
पूर्ण

/**
 * nfs_pgio_release - Release pageio data
 * @calldata: The pageio header to release
 */
अटल व्योम nfs_pgio_release(व्योम *calldata)
अणु
	काष्ठा nfs_pgio_header *hdr = calldata;
	hdr->completion_ops->completion(hdr);
पूर्ण

अटल व्योम nfs_pageio_mirror_init(काष्ठा nfs_pgio_mirror *mirror,
				   अचिन्हित पूर्णांक bsize)
अणु
	INIT_LIST_HEAD(&mirror->pg_list);
	mirror->pg_bytes_written = 0;
	mirror->pg_count = 0;
	mirror->pg_bsize = bsize;
	mirror->pg_base = 0;
	mirror->pg_recoalesce = 0;
पूर्ण

/**
 * nfs_pageio_init - initialise a page io descriptor
 * @desc: poपूर्णांकer to descriptor
 * @inode: poपूर्णांकer to inode
 * @pg_ops: poपूर्णांकer to pageio operations
 * @compl_ops: poपूर्णांकer to pageio completion operations
 * @rw_ops: poपूर्णांकer to nfs पढ़ो/ग_लिखो operations
 * @bsize: io block size
 * @io_flags: extra parameters क्रम the io function
 */
व्योम nfs_pageio_init(काष्ठा nfs_pageio_descriptor *desc,
		     काष्ठा inode *inode,
		     स्थिर काष्ठा nfs_pageio_ops *pg_ops,
		     स्थिर काष्ठा nfs_pgio_completion_ops *compl_ops,
		     स्थिर काष्ठा nfs_rw_ops *rw_ops,
		     माप_प्रकार bsize,
		     पूर्णांक io_flags)
अणु
	desc->pg_moreio = 0;
	desc->pg_inode = inode;
	desc->pg_ops = pg_ops;
	desc->pg_completion_ops = compl_ops;
	desc->pg_rw_ops = rw_ops;
	desc->pg_ioflags = io_flags;
	desc->pg_error = 0;
	desc->pg_lseg = शून्य;
	desc->pg_io_completion = शून्य;
	desc->pg_dreq = शून्य;
	desc->pg_bsize = bsize;

	desc->pg_mirror_count = 1;
	desc->pg_mirror_idx = 0;

	desc->pg_mirrors_dynamic = शून्य;
	desc->pg_mirrors = desc->pg_mirrors_अटल;
	nfs_pageio_mirror_init(&desc->pg_mirrors[0], bsize);
	desc->pg_maxretrans = 0;
पूर्ण

/**
 * nfs_pgio_result - Basic pageio error handling
 * @task: The task that ran
 * @calldata: Pageio header to check
 */
अटल व्योम nfs_pgio_result(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_pgio_header *hdr = calldata;
	काष्ठा inode *inode = hdr->inode;

	dprपूर्णांकk("NFS: %s: %5u, (status %d)\n", __func__,
		task->tk_pid, task->tk_status);

	अगर (hdr->rw_ops->rw_करोne(task, hdr, inode) != 0)
		वापस;
	अगर (task->tk_status < 0)
		nfs_set_pgio_error(hdr, task->tk_status, hdr->args.offset);
	अन्यथा
		hdr->rw_ops->rw_result(task, hdr);
पूर्ण

/*
 * Create an RPC task क्रम the given पढ़ो or ग_लिखो request and kick it.
 * The page must have been locked by the caller.
 *
 * It may happen that the page we're passed is not marked dirty.
 * This is the हाल अगर nfs_updatepage detects a conflicting request
 * that has been written but not committed.
 */
पूर्णांक nfs_generic_pgio(काष्ठा nfs_pageio_descriptor *desc,
		     काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);

	काष्ठा nfs_page		*req;
	काष्ठा page		**pages,
				*last_page;
	काष्ठा list_head *head = &mirror->pg_list;
	काष्ठा nfs_commit_info cinfo;
	काष्ठा nfs_page_array *pg_array = &hdr->page_array;
	अचिन्हित पूर्णांक pagecount, pageused;
	gfp_t gfp_flags = GFP_KERNEL;

	pagecount = nfs_page_array_len(mirror->pg_base, mirror->pg_count);
	pg_array->npages = pagecount;

	अगर (pagecount <= ARRAY_SIZE(pg_array->page_array))
		pg_array->pagevec = pg_array->page_array;
	अन्यथा अणु
		pg_array->pagevec = kसुस्मृति(pagecount, माप(काष्ठा page *), gfp_flags);
		अगर (!pg_array->pagevec) अणु
			pg_array->npages = 0;
			nfs_pgio_error(hdr);
			desc->pg_error = -ENOMEM;
			वापस desc->pg_error;
		पूर्ण
	पूर्ण

	nfs_init_cinfo(&cinfo, desc->pg_inode, desc->pg_dreq);
	pages = hdr->page_array.pagevec;
	last_page = शून्य;
	pageused = 0;
	जबतक (!list_empty(head)) अणु
		req = nfs_list_entry(head->next);
		nfs_list_move_request(req, &hdr->pages);

		अगर (!last_page || last_page != req->wb_page) अणु
			pageused++;
			अगर (pageused > pagecount)
				अवरोध;
			*pages++ = last_page = req->wb_page;
		पूर्ण
	पूर्ण
	अगर (WARN_ON_ONCE(pageused != pagecount)) अणु
		nfs_pgio_error(hdr);
		desc->pg_error = -EINVAL;
		वापस desc->pg_error;
	पूर्ण

	अगर ((desc->pg_ioflags & FLUSH_COND_STABLE) &&
	    (desc->pg_moreio || nfs_reqs_to_commit(&cinfo)))
		desc->pg_ioflags &= ~FLUSH_COND_STABLE;

	/* Set up the argument काष्ठा */
	nfs_pgio_rpcsetup(hdr, mirror->pg_count, desc->pg_ioflags, &cinfo);
	desc->pg_rpc_callops = &nfs_pgio_common_ops;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_generic_pgio);

अटल पूर्णांक nfs_generic_pg_pgios(काष्ठा nfs_pageio_descriptor *desc)
अणु
	काष्ठा nfs_pgio_header *hdr;
	पूर्णांक ret;

	hdr = nfs_pgio_header_alloc(desc->pg_rw_ops);
	अगर (!hdr) अणु
		desc->pg_error = -ENOMEM;
		वापस desc->pg_error;
	पूर्ण
	nfs_pgheader_init(desc, hdr, nfs_pgio_header_मुक्त);
	ret = nfs_generic_pgio(desc, hdr);
	अगर (ret == 0)
		ret = nfs_initiate_pgio(NFS_CLIENT(hdr->inode),
					hdr,
					hdr->cred,
					NFS_PROTO(hdr->inode),
					desc->pg_rpc_callops,
					desc->pg_ioflags,
					RPC_TASK_CRED_NOREF);
	वापस ret;
पूर्ण

अटल काष्ठा nfs_pgio_mirror *
nfs_pageio_alloc_mirrors(काष्ठा nfs_pageio_descriptor *desc,
		अचिन्हित पूर्णांक mirror_count)
अणु
	काष्ठा nfs_pgio_mirror *ret;
	अचिन्हित पूर्णांक i;

	kमुक्त(desc->pg_mirrors_dynamic);
	desc->pg_mirrors_dynamic = शून्य;
	अगर (mirror_count == 1)
		वापस desc->pg_mirrors_अटल;
	ret = kदो_स्मृति_array(mirror_count, माप(*ret), GFP_KERNEL);
	अगर (ret != शून्य) अणु
		क्रम (i = 0; i < mirror_count; i++)
			nfs_pageio_mirror_init(&ret[i], desc->pg_bsize);
		desc->pg_mirrors_dynamic = ret;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * nfs_pageio_setup_mirroring - determine अगर mirroring is to be used
 *				by calling the pg_get_mirror_count op
 */
अटल व्योम nfs_pageio_setup_mirroring(काष्ठा nfs_pageio_descriptor *pgio,
				       काष्ठा nfs_page *req)
अणु
	अचिन्हित पूर्णांक mirror_count = 1;

	अगर (pgio->pg_ops->pg_get_mirror_count)
		mirror_count = pgio->pg_ops->pg_get_mirror_count(pgio, req);
	अगर (mirror_count == pgio->pg_mirror_count || pgio->pg_error < 0)
		वापस;

	अगर (!mirror_count || mirror_count > NFS_PAGEIO_DESCRIPTOR_MIRROR_MAX) अणु
		pgio->pg_error = -EINVAL;
		वापस;
	पूर्ण

	pgio->pg_mirrors = nfs_pageio_alloc_mirrors(pgio, mirror_count);
	अगर (pgio->pg_mirrors == शून्य) अणु
		pgio->pg_error = -ENOMEM;
		pgio->pg_mirrors = pgio->pg_mirrors_अटल;
		mirror_count = 1;
	पूर्ण
	pgio->pg_mirror_count = mirror_count;
पूर्ण

अटल व्योम nfs_pageio_cleanup_mirroring(काष्ठा nfs_pageio_descriptor *pgio)
अणु
	pgio->pg_mirror_count = 1;
	pgio->pg_mirror_idx = 0;
	pgio->pg_mirrors = pgio->pg_mirrors_अटल;
	kमुक्त(pgio->pg_mirrors_dynamic);
	pgio->pg_mirrors_dynamic = शून्य;
पूर्ण

अटल bool nfs_match_lock_context(स्थिर काष्ठा nfs_lock_context *l1,
		स्थिर काष्ठा nfs_lock_context *l2)
अणु
	वापस l1->lockowner == l2->lockowner;
पूर्ण

/**
 * nfs_coalesce_size - test two requests क्रम compatibility
 * @prev: poपूर्णांकer to nfs_page
 * @req: poपूर्णांकer to nfs_page
 * @pgio: poपूर्णांकer to nfs_pagio_descriptor
 *
 * The nfs_page काष्ठाures 'prev' and 'req' are compared to ensure that the
 * page data area they describe is contiguous, and that their RPC
 * credentials, NFSv4 खोलो state, and lockowners are the same.
 *
 * Returns size of the request that can be coalesced
 */
अटल अचिन्हित पूर्णांक nfs_coalesce_size(काष्ठा nfs_page *prev,
				      काष्ठा nfs_page *req,
				      काष्ठा nfs_pageio_descriptor *pgio)
अणु
	काष्ठा file_lock_context *flctx;

	अगर (prev) अणु
		अगर (!nfs_match_खोलो_context(nfs_req_खोलोctx(req), nfs_req_खोलोctx(prev)))
			वापस 0;
		flctx = d_inode(nfs_req_खोलोctx(req)->dentry)->i_flctx;
		अगर (flctx != शून्य &&
		    !(list_empty_careful(&flctx->flc_posix) &&
		      list_empty_careful(&flctx->flc_flock)) &&
		    !nfs_match_lock_context(req->wb_lock_context,
					    prev->wb_lock_context))
			वापस 0;
		अगर (req_offset(req) != req_offset(prev) + prev->wb_bytes)
			वापस 0;
		अगर (req->wb_page == prev->wb_page) अणु
			अगर (req->wb_pgbase != prev->wb_pgbase + prev->wb_bytes)
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (req->wb_pgbase != 0 ||
			    prev->wb_pgbase + prev->wb_bytes != PAGE_SIZE)
				वापस 0;
		पूर्ण
	पूर्ण
	वापस pgio->pg_ops->pg_test(pgio, prev, req);
पूर्ण

/**
 * nfs_pageio_करो_add_request - Attempt to coalesce a request पूर्णांकo a page list.
 * @desc: destination io descriptor
 * @req: request
 *
 * If the request 'req' was successfully coalesced पूर्णांकo the existing list
 * of pages 'desc', it वापसs the size of req.
 */
अटल अचिन्हित पूर्णांक
nfs_pageio_करो_add_request(काष्ठा nfs_pageio_descriptor *desc,
		काष्ठा nfs_page *req)
अणु
	काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);
	काष्ठा nfs_page *prev = शून्य;
	अचिन्हित पूर्णांक size;

	अगर (list_empty(&mirror->pg_list)) अणु
		अगर (desc->pg_ops->pg_init)
			desc->pg_ops->pg_init(desc, req);
		अगर (desc->pg_error < 0)
			वापस 0;
		mirror->pg_base = req->wb_pgbase;
		mirror->pg_count = 0;
		mirror->pg_recoalesce = 0;
	पूर्ण अन्यथा
		prev = nfs_list_entry(mirror->pg_list.prev);

	अगर (desc->pg_maxretrans && req->wb_nio > desc->pg_maxretrans) अणु
		अगर (NFS_SERVER(desc->pg_inode)->flags & NFS_MOUNT_SOFTERR)
			desc->pg_error = -ETIMEDOUT;
		अन्यथा
			desc->pg_error = -EIO;
		वापस 0;
	पूर्ण

	size = nfs_coalesce_size(prev, req, desc);
	अगर (size < req->wb_bytes)
		वापस size;
	nfs_list_move_request(req, &mirror->pg_list);
	mirror->pg_count += req->wb_bytes;
	वापस req->wb_bytes;
पूर्ण

/*
 * Helper क्रम nfs_pageio_add_request and nfs_pageio_complete
 */
अटल व्योम nfs_pageio_करोio(काष्ठा nfs_pageio_descriptor *desc)
अणु
	काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);

	अगर (!list_empty(&mirror->pg_list)) अणु
		पूर्णांक error = desc->pg_ops->pg_करोio(desc);
		अगर (error < 0)
			desc->pg_error = error;
		अगर (list_empty(&mirror->pg_list))
			mirror->pg_bytes_written += mirror->pg_count;
	पूर्ण
पूर्ण

अटल व्योम
nfs_pageio_cleanup_request(काष्ठा nfs_pageio_descriptor *desc,
		काष्ठा nfs_page *req)
अणु
	LIST_HEAD(head);

	nfs_list_move_request(req, &head);
	desc->pg_completion_ops->error_cleanup(&head, desc->pg_error);
पूर्ण

/**
 * __nfs_pageio_add_request - Attempt to coalesce a request पूर्णांकo a page list.
 * @desc: destination io descriptor
 * @req: request
 *
 * This may split a request पूर्णांकo subrequests which are all part of the
 * same page group. If so, it will submit @req as the last one, to ensure
 * the poपूर्णांकer to @req is still valid in हाल of failure.
 *
 * Returns true अगर the request 'req' was successfully coalesced पूर्णांकo the
 * existing list of pages 'desc'.
 */
अटल पूर्णांक __nfs_pageio_add_request(काष्ठा nfs_pageio_descriptor *desc,
			   काष्ठा nfs_page *req)
अणु
	काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);
	काष्ठा nfs_page *subreq;
	अचिन्हित पूर्णांक size, subreq_size;

	nfs_page_group_lock(req);

	subreq = req;
	subreq_size = subreq->wb_bytes;
	क्रम(;;) अणु
		size = nfs_pageio_करो_add_request(desc, subreq);
		अगर (size == subreq_size) अणु
			/* We successfully submitted a request */
			अगर (subreq == req)
				अवरोध;
			req->wb_pgbase += size;
			req->wb_bytes -= size;
			req->wb_offset += size;
			subreq_size = req->wb_bytes;
			subreq = req;
			जारी;
		पूर्ण
		अगर (WARN_ON_ONCE(subreq != req)) अणु
			nfs_page_group_unlock(req);
			nfs_pageio_cleanup_request(desc, subreq);
			subreq = req;
			subreq_size = req->wb_bytes;
			nfs_page_group_lock(req);
		पूर्ण
		अगर (!size) अणु
			/* Can't coalesce any more, so करो I/O */
			nfs_page_group_unlock(req);
			desc->pg_moreio = 1;
			nfs_pageio_करोio(desc);
			अगर (desc->pg_error < 0 || mirror->pg_recoalesce)
				वापस 0;
			/* retry add_request क्रम this subreq */
			nfs_page_group_lock(req);
			जारी;
		पूर्ण
		subreq = nfs_create_subreq(req, req->wb_pgbase,
				req->wb_offset, size);
		अगर (IS_ERR(subreq))
			जाओ err_ptr;
		subreq_size = size;
	पूर्ण

	nfs_page_group_unlock(req);
	वापस 1;
err_ptr:
	desc->pg_error = PTR_ERR(subreq);
	nfs_page_group_unlock(req);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs_करो_recoalesce(काष्ठा nfs_pageio_descriptor *desc)
अणु
	काष्ठा nfs_pgio_mirror *mirror = nfs_pgio_current_mirror(desc);
	LIST_HEAD(head);

	करो अणु
		list_splice_init(&mirror->pg_list, &head);

		जबतक (!list_empty(&head)) अणु
			काष्ठा nfs_page *req;

			req = list_first_entry(&head, काष्ठा nfs_page, wb_list);
			अगर (__nfs_pageio_add_request(desc, req))
				जारी;
			अगर (desc->pg_error < 0) अणु
				list_splice_tail(&head, &mirror->pg_list);
				mirror->pg_recoalesce = 1;
				वापस 0;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण जबतक (mirror->pg_recoalesce);
	वापस 1;
पूर्ण

अटल पूर्णांक nfs_pageio_add_request_mirror(काष्ठा nfs_pageio_descriptor *desc,
		काष्ठा nfs_page *req)
अणु
	पूर्णांक ret;

	करो अणु
		ret = __nfs_pageio_add_request(desc, req);
		अगर (ret)
			अवरोध;
		अगर (desc->pg_error < 0)
			अवरोध;
		ret = nfs_करो_recoalesce(desc);
	पूर्ण जबतक (ret);

	वापस ret;
पूर्ण

अटल व्योम nfs_pageio_error_cleanup(काष्ठा nfs_pageio_descriptor *desc)
अणु
	u32 midx;
	काष्ठा nfs_pgio_mirror *mirror;

	अगर (!desc->pg_error)
		वापस;

	क्रम (midx = 0; midx < desc->pg_mirror_count; midx++) अणु
		mirror = nfs_pgio_get_mirror(desc, midx);
		desc->pg_completion_ops->error_cleanup(&mirror->pg_list,
				desc->pg_error);
	पूर्ण
पूर्ण

पूर्णांक nfs_pageio_add_request(काष्ठा nfs_pageio_descriptor *desc,
			   काष्ठा nfs_page *req)
अणु
	u32 midx;
	अचिन्हित पूर्णांक pgbase, offset, bytes;
	काष्ठा nfs_page *dupreq;

	pgbase = req->wb_pgbase;
	offset = req->wb_offset;
	bytes = req->wb_bytes;

	nfs_pageio_setup_mirroring(desc, req);
	अगर (desc->pg_error < 0)
		जाओ out_failed;

	/* Create the mirror instances first, and fire them off */
	क्रम (midx = 1; midx < desc->pg_mirror_count; midx++) अणु
		nfs_page_group_lock(req);

		dupreq = nfs_create_subreq(req,
				pgbase, offset, bytes);

		nfs_page_group_unlock(req);
		अगर (IS_ERR(dupreq)) अणु
			desc->pg_error = PTR_ERR(dupreq);
			जाओ out_failed;
		पूर्ण

		nfs_pgio_set_current_mirror(desc, midx);
		अगर (!nfs_pageio_add_request_mirror(desc, dupreq))
			जाओ out_cleanup_subreq;
	पूर्ण

	nfs_pgio_set_current_mirror(desc, 0);
	अगर (!nfs_pageio_add_request_mirror(desc, req))
		जाओ out_failed;

	वापस 1;

out_cleanup_subreq:
	nfs_pageio_cleanup_request(desc, dupreq);
out_failed:
	nfs_pageio_error_cleanup(desc);
	वापस 0;
पूर्ण

/*
 * nfs_pageio_complete_mirror - Complete I/O on the current mirror of an
 *				nfs_pageio_descriptor
 * @desc: poपूर्णांकer to io descriptor
 * @mirror_idx: poपूर्णांकer to mirror index
 */
अटल व्योम nfs_pageio_complete_mirror(काष्ठा nfs_pageio_descriptor *desc,
				       u32 mirror_idx)
अणु
	काष्ठा nfs_pgio_mirror *mirror;
	u32 restore_idx;

	restore_idx = nfs_pgio_set_current_mirror(desc, mirror_idx);
	mirror = nfs_pgio_current_mirror(desc);

	क्रम (;;) अणु
		nfs_pageio_करोio(desc);
		अगर (desc->pg_error < 0 || !mirror->pg_recoalesce)
			अवरोध;
		अगर (!nfs_करो_recoalesce(desc))
			अवरोध;
	पूर्ण
	nfs_pgio_set_current_mirror(desc, restore_idx);
पूर्ण

/*
 * nfs_pageio_resend - Transfer requests to new descriptor and resend
 * @hdr - the pgio header to move request from
 * @desc - the pageio descriptor to add requests to
 *
 * Try to move each request (nfs_page) from @hdr to @desc then attempt
 * to send them.
 *
 * Returns 0 on success and < 0 on error.
 */
पूर्णांक nfs_pageio_resend(काष्ठा nfs_pageio_descriptor *desc,
		      काष्ठा nfs_pgio_header *hdr)
अणु
	LIST_HEAD(pages);

	desc->pg_io_completion = hdr->io_completion;
	desc->pg_dreq = hdr->dreq;
	list_splice_init(&hdr->pages, &pages);
	जबतक (!list_empty(&pages)) अणु
		काष्ठा nfs_page *req = nfs_list_entry(pages.next);

		अगर (!nfs_pageio_add_request(desc, req))
			अवरोध;
	पूर्ण
	nfs_pageio_complete(desc);
	अगर (!list_empty(&pages)) अणु
		पूर्णांक err = desc->pg_error < 0 ? desc->pg_error : -EIO;
		hdr->completion_ops->error_cleanup(&pages, err);
		nfs_set_pgio_error(hdr, err, hdr->io_start);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_pageio_resend);

/**
 * nfs_pageio_complete - Complete I/O then cleanup an nfs_pageio_descriptor
 * @desc: poपूर्णांकer to io descriptor
 */
व्योम nfs_pageio_complete(काष्ठा nfs_pageio_descriptor *desc)
अणु
	u32 midx;

	क्रम (midx = 0; midx < desc->pg_mirror_count; midx++)
		nfs_pageio_complete_mirror(desc, midx);

	अगर (desc->pg_error < 0)
		nfs_pageio_error_cleanup(desc);
	अगर (desc->pg_ops->pg_cleanup)
		desc->pg_ops->pg_cleanup(desc);
	nfs_pageio_cleanup_mirroring(desc);
पूर्ण

/**
 * nfs_pageio_cond_complete - Conditional I/O completion
 * @desc: poपूर्णांकer to io descriptor
 * @index: page index
 *
 * It is important to ensure that processes करोn't try to take locks
 * on non-contiguous ranges of pages as that might deadlock. This
 * function should be called beक्रमe attempting to रुको on a locked
 * nfs_page. It will complete the I/O अगर the page index 'index'
 * is not contiguous with the existing list of pages in 'desc'.
 */
व्योम nfs_pageio_cond_complete(काष्ठा nfs_pageio_descriptor *desc, pgoff_t index)
अणु
	काष्ठा nfs_pgio_mirror *mirror;
	काष्ठा nfs_page *prev;
	u32 midx;

	क्रम (midx = 0; midx < desc->pg_mirror_count; midx++) अणु
		mirror = nfs_pgio_get_mirror(desc, midx);
		अगर (!list_empty(&mirror->pg_list)) अणु
			prev = nfs_list_entry(mirror->pg_list.prev);
			अगर (index != prev->wb_index + 1) अणु
				nfs_pageio_complete(desc);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * nfs_pageio_stop_mirroring - stop using mirroring (set mirror count to 1)
 */
व्योम nfs_pageio_stop_mirroring(काष्ठा nfs_pageio_descriptor *pgio)
अणु
	nfs_pageio_complete(pgio);
पूर्ण

पूर्णांक __init nfs_init_nfspagecache(व्योम)
अणु
	nfs_page_cachep = kmem_cache_create("nfs_page",
					    माप(काष्ठा nfs_page),
					    0, SLAB_HWCACHE_ALIGN,
					    शून्य);
	अगर (nfs_page_cachep == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम nfs_destroy_nfspagecache(व्योम)
अणु
	kmem_cache_destroy(nfs_page_cachep);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs_pgio_common_ops = अणु
	.rpc_call_prepare = nfs_pgio_prepare,
	.rpc_call_करोne = nfs_pgio_result,
	.rpc_release = nfs_pgio_release,
पूर्ण;

स्थिर काष्ठा nfs_pageio_ops nfs_pgio_rw_ops = अणु
	.pg_test = nfs_generic_pg_test,
	.pg_करोio = nfs_generic_pg_pgios,
पूर्ण;
