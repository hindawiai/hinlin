<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/nfs/direct.c
 *
 * Copyright (C) 2003 by Chuck Lever <cel@netapp.com>
 *
 * High-perक्रमmance uncached I/O क्रम the Linux NFS client
 *
 * There are important applications whose perक्रमmance or correctness
 * depends on uncached access to file data.  Database clusters
 * (multiple copies of the same instance running on separate hosts)
 * implement their own cache coherency protocol that subsumes file
 * प्रणाली cache protocols.  Applications that process datasets
 * considerably larger than the client's memory करो not always benefit
 * from a local cache.  A streaming video server, क्रम instance, has no
 * need to cache the contents of a file.
 *
 * When an application requests uncached I/O, all पढ़ो and ग_लिखो requests
 * are made directly to the server; data stored or fetched via these
 * requests is not cached in the Linux page cache.  The client करोes not
 * correct unaligned requests from applications.  All requested bytes are
 * held on permanent storage beक्रमe a direct ग_लिखो प्रणाली call वापसs to
 * an application.
 *
 * Solaris implements an uncached I/O facility called directio() that
 * is used क्रम backups and sequential I/O to very large files.  Solaris
 * also supports uncaching whole NFS partitions with "-o forcedirectio,"
 * an unकरोcumented mount option.
 *
 * Deचिन्हित by Jeff Kimmel, Chuck Lever, and Trond Myklebust, with
 * help from Andrew Morton.
 *
 * 18 Dec 2001	Initial implementation क्रम 2.4  --cel
 * 08 Jul 2002	Version क्रम 2.4.19, with bug fixes --trondmy
 * 08 Jun 2003	Port to 2.5 APIs  --cel
 * 31 Mar 2004	Handle direct I/O without VFS support  --cel
 * 15 Sep 2004	Parallel async पढ़ोs  --cel
 * 04 May 2005	support O_सूचीECT with aio  --cel
 *
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/kref.h>
#समावेश <linux/slab.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/module.h>

#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/sunrpc/clnt.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>

#समावेश "internal.h"
#समावेश "iostat.h"
#समावेश "pnfs.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_VFS

अटल काष्ठा kmem_cache *nfs_direct_cachep;

काष्ठा nfs_direct_req अणु
	काष्ठा kref		kref;		/* release manager */

	/* I/O parameters */
	काष्ठा nfs_खोलो_context	*ctx;		/* file खोलो context info */
	काष्ठा nfs_lock_context *l_ctx;		/* Lock context info */
	काष्ठा kiocb *		iocb;		/* controlling i/o request */
	काष्ठा inode *		inode;		/* target file of i/o */

	/* completion state */
	atomic_t		io_count;	/* i/os we're रुकोing क्रम */
	spinlock_t		lock;		/* protect completion state */

	loff_t			io_start;	/* Start offset क्रम I/O */
	sमाप_प्रकार			count,		/* bytes actually processed */
				max_count,	/* max expected count */
				bytes_left,	/* bytes left to be sent */
				error;		/* any reported error */
	काष्ठा completion	completion;	/* रुको क्रम i/o completion */

	/* commit state */
	काष्ठा nfs_mds_commit_info mds_cinfo;	/* Storage क्रम cinfo */
	काष्ठा pnfs_ds_commit_info ds_cinfo;	/* Storage क्रम cinfo */
	काष्ठा work_काष्ठा	work;
	पूर्णांक			flags;
	/* क्रम ग_लिखो */
#घोषणा NFS_OसूचीECT_DO_COMMIT		(1)	/* an unstable reply was received */
#घोषणा NFS_OसूचीECT_RESCHED_WRITES	(2)	/* ग_लिखो verअगरication failed */
	/* क्रम पढ़ो */
#घोषणा NFS_OसूचीECT_SHOULD_सूचीTY	(3)	/* dirty user-space page after पढ़ो */
#घोषणा NFS_OसूचीECT_DONE		पूर्णांक_उच्च	/* ग_लिखो verअगरication failed */
पूर्ण;

अटल स्थिर काष्ठा nfs_pgio_completion_ops nfs_direct_ग_लिखो_completion_ops;
अटल स्थिर काष्ठा nfs_commit_completion_ops nfs_direct_commit_completion_ops;
अटल व्योम nfs_direct_ग_लिखो_complete(काष्ठा nfs_direct_req *dreq);
अटल व्योम nfs_direct_ग_लिखो_schedule_work(काष्ठा work_काष्ठा *work);

अटल अंतरभूत व्योम get_dreq(काष्ठा nfs_direct_req *dreq)
अणु
	atomic_inc(&dreq->io_count);
पूर्ण

अटल अंतरभूत पूर्णांक put_dreq(काष्ठा nfs_direct_req *dreq)
अणु
	वापस atomic_dec_and_test(&dreq->io_count);
पूर्ण

अटल व्योम
nfs_direct_handle_truncated(काष्ठा nfs_direct_req *dreq,
			    स्थिर काष्ठा nfs_pgio_header *hdr,
			    sमाप_प्रकार dreq_len)
अणु
	अगर (!(test_bit(NFS_IOHDR_ERROR, &hdr->flags) ||
	      test_bit(NFS_IOHDR_खातापूर्ण, &hdr->flags)))
		वापस;
	अगर (dreq->max_count >= dreq_len) अणु
		dreq->max_count = dreq_len;
		अगर (dreq->count > dreq_len)
			dreq->count = dreq_len;

		अगर (test_bit(NFS_IOHDR_ERROR, &hdr->flags))
			dreq->error = hdr->error;
		अन्यथा /* Clear outstanding error अगर this is खातापूर्ण */
			dreq->error = 0;
	पूर्ण
पूर्ण

अटल व्योम
nfs_direct_count_bytes(काष्ठा nfs_direct_req *dreq,
		       स्थिर काष्ठा nfs_pgio_header *hdr)
अणु
	loff_t hdr_end = hdr->io_start + hdr->good_bytes;
	sमाप_प्रकार dreq_len = 0;

	अगर (hdr_end > dreq->io_start)
		dreq_len = hdr_end - dreq->io_start;

	nfs_direct_handle_truncated(dreq, hdr, dreq_len);

	अगर (dreq_len > dreq->max_count)
		dreq_len = dreq->max_count;

	अगर (dreq->count < dreq_len)
		dreq->count = dreq_len;
पूर्ण

/**
 * nfs_direct_IO - NFS address space operation क्रम direct I/O
 * @iocb: target I/O control block
 * @iter: I/O buffer
 *
 * The presence of this routine in the address space ops vector means
 * the NFS client supports direct I/O. However, क्रम most direct IO, we
 * shunt off direct पढ़ो and ग_लिखो requests beक्रमe the VFS माला_लो them,
 * so this method is only ever called क्रम swap.
 */
sमाप_प्रकार nfs_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा inode *inode = iocb->ki_filp->f_mapping->host;

	/* we only support swap file calling nfs_direct_IO */
	अगर (!IS_SWAPखाता(inode))
		वापस 0;

	VM_BUG_ON(iov_iter_count(iter) != PAGE_SIZE);

	अगर (iov_iter_rw(iter) == READ)
		वापस nfs_file_direct_पढ़ो(iocb, iter);
	वापस nfs_file_direct_ग_लिखो(iocb, iter);
पूर्ण

अटल व्योम nfs_direct_release_pages(काष्ठा page **pages, अचिन्हित पूर्णांक npages)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < npages; i++)
		put_page(pages[i]);
पूर्ण

व्योम nfs_init_cinfo_from_dreq(काष्ठा nfs_commit_info *cinfo,
			      काष्ठा nfs_direct_req *dreq)
अणु
	cinfo->inode = dreq->inode;
	cinfo->mds = &dreq->mds_cinfo;
	cinfo->ds = &dreq->ds_cinfo;
	cinfo->dreq = dreq;
	cinfo->completion_ops = &nfs_direct_commit_completion_ops;
पूर्ण

अटल अंतरभूत काष्ठा nfs_direct_req *nfs_direct_req_alloc(व्योम)
अणु
	काष्ठा nfs_direct_req *dreq;

	dreq = kmem_cache_zalloc(nfs_direct_cachep, GFP_KERNEL);
	अगर (!dreq)
		वापस शून्य;

	kref_init(&dreq->kref);
	kref_get(&dreq->kref);
	init_completion(&dreq->completion);
	INIT_LIST_HEAD(&dreq->mds_cinfo.list);
	pnfs_init_ds_commit_info(&dreq->ds_cinfo);
	INIT_WORK(&dreq->work, nfs_direct_ग_लिखो_schedule_work);
	spin_lock_init(&dreq->lock);

	वापस dreq;
पूर्ण

अटल व्योम nfs_direct_req_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा nfs_direct_req *dreq = container_of(kref, काष्ठा nfs_direct_req, kref);

	pnfs_release_ds_info(&dreq->ds_cinfo, dreq->inode);
	अगर (dreq->l_ctx != शून्य)
		nfs_put_lock_context(dreq->l_ctx);
	अगर (dreq->ctx != शून्य)
		put_nfs_खोलो_context(dreq->ctx);
	kmem_cache_मुक्त(nfs_direct_cachep, dreq);
पूर्ण

अटल व्योम nfs_direct_req_release(काष्ठा nfs_direct_req *dreq)
अणु
	kref_put(&dreq->kref, nfs_direct_req_मुक्त);
पूर्ण

sमाप_प्रकार nfs_dreq_bytes_left(काष्ठा nfs_direct_req *dreq)
अणु
	वापस dreq->bytes_left;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_dreq_bytes_left);

/*
 * Collects and वापसs the final error value/byte-count.
 */
अटल sमाप_प्रकार nfs_direct_रुको(काष्ठा nfs_direct_req *dreq)
अणु
	sमाप_प्रकार result = -EIOCBQUEUED;

	/* Async requests करोn't रुको here */
	अगर (dreq->iocb)
		जाओ out;

	result = रुको_क्रम_completion_समाप्तable(&dreq->completion);

	अगर (!result) अणु
		result = dreq->count;
		WARN_ON_ONCE(dreq->count < 0);
	पूर्ण
	अगर (!result)
		result = dreq->error;

out:
	वापस (sमाप_प्रकार) result;
पूर्ण

/*
 * Synchronous I/O uses a stack-allocated iocb.  Thus we can't trust
 * the iocb is still valid here अगर this is a synchronous request.
 */
अटल व्योम nfs_direct_complete(काष्ठा nfs_direct_req *dreq)
अणु
	काष्ठा inode *inode = dreq->inode;

	inode_dio_end(inode);

	अगर (dreq->iocb) अणु
		दीर्घ res = (दीर्घ) dreq->error;
		अगर (dreq->count != 0) अणु
			res = (दीर्घ) dreq->count;
			WARN_ON_ONCE(dreq->count < 0);
		पूर्ण
		dreq->iocb->ki_complete(dreq->iocb, res, 0);
	पूर्ण

	complete(&dreq->completion);

	nfs_direct_req_release(dreq);
पूर्ण

अटल व्योम nfs_direct_पढ़ो_completion(काष्ठा nfs_pgio_header *hdr)
अणु
	अचिन्हित दीर्घ bytes = 0;
	काष्ठा nfs_direct_req *dreq = hdr->dreq;

	spin_lock(&dreq->lock);
	अगर (test_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
		spin_unlock(&dreq->lock);
		जाओ out_put;
	पूर्ण

	nfs_direct_count_bytes(dreq, hdr);
	spin_unlock(&dreq->lock);

	जबतक (!list_empty(&hdr->pages)) अणु
		काष्ठा nfs_page *req = nfs_list_entry(hdr->pages.next);
		काष्ठा page *page = req->wb_page;

		अगर (!PageCompound(page) && bytes < hdr->good_bytes &&
		    (dreq->flags == NFS_OसूचीECT_SHOULD_सूचीTY))
			set_page_dirty(page);
		bytes += req->wb_bytes;
		nfs_list_हटाओ_request(req);
		nfs_release_request(req);
	पूर्ण
out_put:
	अगर (put_dreq(dreq))
		nfs_direct_complete(dreq);
	hdr->release(hdr);
पूर्ण

अटल व्योम nfs_पढ़ो_sync_pgio_error(काष्ठा list_head *head, पूर्णांक error)
अणु
	काष्ठा nfs_page *req;

	जबतक (!list_empty(head)) अणु
		req = nfs_list_entry(head->next);
		nfs_list_हटाओ_request(req);
		nfs_release_request(req);
	पूर्ण
पूर्ण

अटल व्योम nfs_direct_pgio_init(काष्ठा nfs_pgio_header *hdr)
अणु
	get_dreq(hdr->dreq);
पूर्ण

अटल स्थिर काष्ठा nfs_pgio_completion_ops nfs_direct_पढ़ो_completion_ops = अणु
	.error_cleanup = nfs_पढ़ो_sync_pgio_error,
	.init_hdr = nfs_direct_pgio_init,
	.completion = nfs_direct_पढ़ो_completion,
पूर्ण;

/*
 * For each rsize'd chunk of the user's buffer, dispatch an NFS READ
 * operation.  If nfs_पढ़ोdata_alloc() or get_user_pages() fails,
 * bail and stop sending more पढ़ोs.  Read length accounting is
 * handled स्वतःmatically by nfs_direct_पढ़ो_result().  Otherwise, अगर
 * no requests have been sent, just वापस an error.
 */

अटल sमाप_प्रकार nfs_direct_पढ़ो_schedule_iovec(काष्ठा nfs_direct_req *dreq,
					      काष्ठा iov_iter *iter,
					      loff_t pos)
अणु
	काष्ठा nfs_pageio_descriptor desc;
	काष्ठा inode *inode = dreq->inode;
	sमाप_प्रकार result = -EINVAL;
	माप_प्रकार requested_bytes = 0;
	माप_प्रकार rsize = max_t(माप_प्रकार, NFS_SERVER(inode)->rsize, PAGE_SIZE);

	nfs_pageio_init_पढ़ो(&desc, dreq->inode, false,
			     &nfs_direct_पढ़ो_completion_ops);
	get_dreq(dreq);
	desc.pg_dreq = dreq;
	inode_dio_begin(inode);

	जबतक (iov_iter_count(iter)) अणु
		काष्ठा page **pagevec;
		माप_प्रकार bytes;
		माप_प्रकार pgbase;
		अचिन्हित npages, i;

		result = iov_iter_get_pages_alloc(iter, &pagevec, 
						  rsize, &pgbase);
		अगर (result < 0)
			अवरोध;
	
		bytes = result;
		iov_iter_advance(iter, bytes);
		npages = (result + pgbase + PAGE_SIZE - 1) / PAGE_SIZE;
		क्रम (i = 0; i < npages; i++) अणु
			काष्ठा nfs_page *req;
			अचिन्हित पूर्णांक req_len = min_t(माप_प्रकार, bytes, PAGE_SIZE - pgbase);
			/* XXX करो we need to करो the eof zeroing found in async_filler? */
			req = nfs_create_request(dreq->ctx, pagevec[i],
						 pgbase, req_len);
			अगर (IS_ERR(req)) अणु
				result = PTR_ERR(req);
				अवरोध;
			पूर्ण
			req->wb_index = pos >> PAGE_SHIFT;
			req->wb_offset = pos & ~PAGE_MASK;
			अगर (!nfs_pageio_add_request(&desc, req)) अणु
				result = desc.pg_error;
				nfs_release_request(req);
				अवरोध;
			पूर्ण
			pgbase = 0;
			bytes -= req_len;
			requested_bytes += req_len;
			pos += req_len;
			dreq->bytes_left -= req_len;
		पूर्ण
		nfs_direct_release_pages(pagevec, npages);
		kvमुक्त(pagevec);
		अगर (result < 0)
			अवरोध;
	पूर्ण

	nfs_pageio_complete(&desc);

	/*
	 * If no bytes were started, वापस the error, and let the
	 * generic layer handle the completion.
	 */
	अगर (requested_bytes == 0) अणु
		inode_dio_end(inode);
		nfs_direct_req_release(dreq);
		वापस result < 0 ? result : -EIO;
	पूर्ण

	अगर (put_dreq(dreq))
		nfs_direct_complete(dreq);
	वापस requested_bytes;
पूर्ण

/**
 * nfs_file_direct_पढ़ो - file direct पढ़ो operation क्रम NFS files
 * @iocb: target I/O control block
 * @iter: vector of user buffers पूर्णांकo which to पढ़ो data
 *
 * We use this function क्रम direct पढ़ोs instead of calling
 * generic_file_aio_पढ़ो() in order to aव्योम gfar's check to see अगर
 * the request starts beक्रमe the end of the file.  For that check
 * to work, we must generate a GETATTR beक्रमe each direct पढ़ो, and
 * even then there is a winकरोw between the GETATTR and the subsequent
 * READ where the file size could change.  Our preference is simply
 * to करो all पढ़ोs the application wants, and the server will take
 * care of managing the end of file boundary.
 *
 * This function also eliminates unnecessarily updating the file's
 * aसमय locally, as the NFS server sets the file's aसमय, and this
 * client must पढ़ो the updated aसमय from the server back पूर्णांकo its
 * cache.
 */
sमाप_प्रकार nfs_file_direct_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	काष्ठा nfs_direct_req *dreq;
	काष्ठा nfs_lock_context *l_ctx;
	sमाप_प्रकार result, requested;
	माप_प्रकार count = iov_iter_count(iter);
	nfs_add_stats(mapping->host, NFSIOS_सूचीECTREADBYTES, count);

	dfprपूर्णांकk(खाता, "NFS: direct read(%pD2, %zd@%Ld)\n",
		file, count, (दीर्घ दीर्घ) iocb->ki_pos);

	result = 0;
	अगर (!count)
		जाओ out;

	task_io_account_पढ़ो(count);

	result = -ENOMEM;
	dreq = nfs_direct_req_alloc();
	अगर (dreq == शून्य)
		जाओ out;

	dreq->inode = inode;
	dreq->bytes_left = dreq->max_count = count;
	dreq->io_start = iocb->ki_pos;
	dreq->ctx = get_nfs_खोलो_context(nfs_file_खोलो_context(iocb->ki_filp));
	l_ctx = nfs_get_lock_context(dreq->ctx);
	अगर (IS_ERR(l_ctx)) अणु
		result = PTR_ERR(l_ctx);
		nfs_direct_req_release(dreq);
		जाओ out_release;
	पूर्ण
	dreq->l_ctx = l_ctx;
	अगर (!is_sync_kiocb(iocb))
		dreq->iocb = iocb;

	अगर (iter_is_iovec(iter))
		dreq->flags = NFS_OसूचीECT_SHOULD_सूचीTY;

	nfs_start_io_direct(inode);

	NFS_I(inode)->पढ़ो_io += count;
	requested = nfs_direct_पढ़ो_schedule_iovec(dreq, iter, iocb->ki_pos);

	nfs_end_io_direct(inode);

	अगर (requested > 0) अणु
		result = nfs_direct_रुको(dreq);
		अगर (result > 0) अणु
			requested -= result;
			iocb->ki_pos += result;
		पूर्ण
		iov_iter_revert(iter, requested);
	पूर्ण अन्यथा अणु
		result = requested;
	पूर्ण

out_release:
	nfs_direct_req_release(dreq);
out:
	वापस result;
पूर्ण

अटल व्योम
nfs_direct_join_group(काष्ठा list_head *list, काष्ठा inode *inode)
अणु
	काष्ठा nfs_page *req, *next;

	list_क्रम_each_entry(req, list, wb_list) अणु
		अगर (req->wb_head != req || req->wb_this_page == req)
			जारी;
		क्रम (next = req->wb_this_page;
				next != req->wb_head;
				next = next->wb_this_page) अणु
			nfs_list_हटाओ_request(next);
			nfs_release_request(next);
		पूर्ण
		nfs_join_page_group(req, inode);
	पूर्ण
पूर्ण

अटल व्योम
nfs_direct_ग_लिखो_scan_commit_list(काष्ठा inode *inode,
				  काष्ठा list_head *list,
				  काष्ठा nfs_commit_info *cinfo)
अणु
	mutex_lock(&NFS_I(cinfo->inode)->commit_mutex);
	pnfs_recover_commit_reqs(list, cinfo);
	nfs_scan_commit_list(&cinfo->mds->list, list, cinfo, 0);
	mutex_unlock(&NFS_I(cinfo->inode)->commit_mutex);
पूर्ण

अटल व्योम nfs_direct_ग_लिखो_reschedule(काष्ठा nfs_direct_req *dreq)
अणु
	काष्ठा nfs_pageio_descriptor desc;
	काष्ठा nfs_page *req, *पंचांगp;
	LIST_HEAD(reqs);
	काष्ठा nfs_commit_info cinfo;
	LIST_HEAD(failed);

	nfs_init_cinfo_from_dreq(&cinfo, dreq);
	nfs_direct_ग_लिखो_scan_commit_list(dreq->inode, &reqs, &cinfo);

	nfs_direct_join_group(&reqs, dreq->inode);

	dreq->count = 0;
	dreq->max_count = 0;
	list_क्रम_each_entry(req, &reqs, wb_list)
		dreq->max_count += req->wb_bytes;
	nfs_clear_pnfs_ds_commit_verअगरiers(&dreq->ds_cinfo);
	get_dreq(dreq);

	nfs_pageio_init_ग_लिखो(&desc, dreq->inode, FLUSH_STABLE, false,
			      &nfs_direct_ग_लिखो_completion_ops);
	desc.pg_dreq = dreq;

	list_क्रम_each_entry_safe(req, पंचांगp, &reqs, wb_list) अणु
		/* Bump the transmission count */
		req->wb_nio++;
		अगर (!nfs_pageio_add_request(&desc, req)) अणु
			nfs_list_move_request(req, &failed);
			spin_lock(&cinfo.inode->i_lock);
			dreq->flags = 0;
			अगर (desc.pg_error < 0)
				dreq->error = desc.pg_error;
			अन्यथा
				dreq->error = -EIO;
			spin_unlock(&cinfo.inode->i_lock);
		पूर्ण
		nfs_release_request(req);
	पूर्ण
	nfs_pageio_complete(&desc);

	जबतक (!list_empty(&failed)) अणु
		req = nfs_list_entry(failed.next);
		nfs_list_हटाओ_request(req);
		nfs_unlock_and_release_request(req);
	पूर्ण

	अगर (put_dreq(dreq))
		nfs_direct_ग_लिखो_complete(dreq);
पूर्ण

अटल व्योम nfs_direct_commit_complete(काष्ठा nfs_commit_data *data)
अणु
	स्थिर काष्ठा nfs_ग_लिखोverf *verf = data->res.verf;
	काष्ठा nfs_direct_req *dreq = data->dreq;
	काष्ठा nfs_commit_info cinfo;
	काष्ठा nfs_page *req;
	पूर्णांक status = data->task.tk_status;

	अगर (status < 0) अणु
		/* Errors in commit are fatal */
		dreq->error = status;
		dreq->max_count = 0;
		dreq->count = 0;
		dreq->flags = NFS_OसूचीECT_DONE;
	पूर्ण अन्यथा अगर (dreq->flags == NFS_OसूचीECT_DONE)
		status = dreq->error;

	nfs_init_cinfo_from_dreq(&cinfo, dreq);

	जबतक (!list_empty(&data->pages)) अणु
		req = nfs_list_entry(data->pages.next);
		nfs_list_हटाओ_request(req);
		अगर (status >= 0 && !nfs_ग_लिखो_match_verf(verf, req)) अणु
			dreq->flags = NFS_OसूचीECT_RESCHED_WRITES;
			/*
			 * Despite the reboot, the ग_लिखो was successful,
			 * so reset wb_nio.
			 */
			req->wb_nio = 0;
			nfs_mark_request_commit(req, शून्य, &cinfo, 0);
		पूर्ण अन्यथा /* Error or match */
			nfs_release_request(req);
		nfs_unlock_and_release_request(req);
	पूर्ण

	अगर (atomic_dec_and_test(&cinfo.mds->rpcs_out))
		nfs_direct_ग_लिखो_complete(dreq);
पूर्ण

अटल व्योम nfs_direct_resched_ग_लिखो(काष्ठा nfs_commit_info *cinfo,
		काष्ठा nfs_page *req)
अणु
	काष्ठा nfs_direct_req *dreq = cinfo->dreq;

	spin_lock(&dreq->lock);
	अगर (dreq->flags != NFS_OसूचीECT_DONE)
		dreq->flags = NFS_OसूचीECT_RESCHED_WRITES;
	spin_unlock(&dreq->lock);
	nfs_mark_request_commit(req, शून्य, cinfo, 0);
पूर्ण

अटल स्थिर काष्ठा nfs_commit_completion_ops nfs_direct_commit_completion_ops = अणु
	.completion = nfs_direct_commit_complete,
	.resched_ग_लिखो = nfs_direct_resched_ग_लिखो,
पूर्ण;

अटल व्योम nfs_direct_commit_schedule(काष्ठा nfs_direct_req *dreq)
अणु
	पूर्णांक res;
	काष्ठा nfs_commit_info cinfo;
	LIST_HEAD(mds_list);

	nfs_init_cinfo_from_dreq(&cinfo, dreq);
	nfs_scan_commit(dreq->inode, &mds_list, &cinfo);
	res = nfs_generic_commit_list(dreq->inode, &mds_list, 0, &cinfo);
	अगर (res < 0) /* res == -ENOMEM */
		nfs_direct_ग_लिखो_reschedule(dreq);
पूर्ण

अटल व्योम nfs_direct_ग_लिखो_clear_reqs(काष्ठा nfs_direct_req *dreq)
अणु
	काष्ठा nfs_commit_info cinfo;
	काष्ठा nfs_page *req;
	LIST_HEAD(reqs);

	nfs_init_cinfo_from_dreq(&cinfo, dreq);
	nfs_direct_ग_लिखो_scan_commit_list(dreq->inode, &reqs, &cinfo);

	जबतक (!list_empty(&reqs)) अणु
		req = nfs_list_entry(reqs.next);
		nfs_list_हटाओ_request(req);
		nfs_release_request(req);
		nfs_unlock_and_release_request(req);
	पूर्ण
पूर्ण

अटल व्योम nfs_direct_ग_लिखो_schedule_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfs_direct_req *dreq = container_of(work, काष्ठा nfs_direct_req, work);
	पूर्णांक flags = dreq->flags;

	dreq->flags = 0;
	चयन (flags) अणु
		हाल NFS_OसूचीECT_DO_COMMIT:
			nfs_direct_commit_schedule(dreq);
			अवरोध;
		हाल NFS_OसूचीECT_RESCHED_WRITES:
			nfs_direct_ग_लिखो_reschedule(dreq);
			अवरोध;
		शेष:
			nfs_direct_ग_लिखो_clear_reqs(dreq);
			nfs_zap_mapping(dreq->inode, dreq->inode->i_mapping);
			nfs_direct_complete(dreq);
	पूर्ण
पूर्ण

अटल व्योम nfs_direct_ग_लिखो_complete(काष्ठा nfs_direct_req *dreq)
अणु
	queue_work(nfsiod_workqueue, &dreq->work); /* Calls nfs_direct_ग_लिखो_schedule_work */
पूर्ण

अटल व्योम nfs_direct_ग_लिखो_completion(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_direct_req *dreq = hdr->dreq;
	काष्ठा nfs_commit_info cinfo;
	bool request_commit = false;
	काष्ठा nfs_page *req = nfs_list_entry(hdr->pages.next);

	nfs_init_cinfo_from_dreq(&cinfo, dreq);

	spin_lock(&dreq->lock);
	अगर (test_bit(NFS_IOHDR_REDO, &hdr->flags)) अणु
		spin_unlock(&dreq->lock);
		जाओ out_put;
	पूर्ण

	nfs_direct_count_bytes(dreq, hdr);
	अगर (hdr->good_bytes != 0 && nfs_ग_लिखो_need_commit(hdr)) अणु
		चयन (dreq->flags) अणु
		हाल 0:
			dreq->flags = NFS_OसूचीECT_DO_COMMIT;
			request_commit = true;
			अवरोध;
		हाल NFS_OसूचीECT_RESCHED_WRITES:
		हाल NFS_OसूचीECT_DO_COMMIT:
			request_commit = true;
		पूर्ण
	पूर्ण
	spin_unlock(&dreq->lock);

	जबतक (!list_empty(&hdr->pages)) अणु

		req = nfs_list_entry(hdr->pages.next);
		nfs_list_हटाओ_request(req);
		अगर (request_commit) अणु
			kref_get(&req->wb_kref);
			स_नकल(&req->wb_verf, &hdr->verf.verअगरier,
			       माप(req->wb_verf));
			nfs_mark_request_commit(req, hdr->lseg, &cinfo,
				hdr->ds_commit_idx);
		पूर्ण
		nfs_unlock_and_release_request(req);
	पूर्ण

out_put:
	अगर (put_dreq(dreq))
		nfs_direct_ग_लिखो_complete(dreq);
	hdr->release(hdr);
पूर्ण

अटल व्योम nfs_ग_लिखो_sync_pgio_error(काष्ठा list_head *head, पूर्णांक error)
अणु
	काष्ठा nfs_page *req;

	जबतक (!list_empty(head)) अणु
		req = nfs_list_entry(head->next);
		nfs_list_हटाओ_request(req);
		nfs_unlock_and_release_request(req);
	पूर्ण
पूर्ण

अटल व्योम nfs_direct_ग_लिखो_reschedule_io(काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_direct_req *dreq = hdr->dreq;

	spin_lock(&dreq->lock);
	अगर (dreq->error == 0) अणु
		dreq->flags = NFS_OसूचीECT_RESCHED_WRITES;
		/* fake unstable ग_लिखो to let common nfs resend pages */
		hdr->verf.committed = NFS_UNSTABLE;
		hdr->good_bytes = hdr->args.offset + hdr->args.count -
			hdr->io_start;
	पूर्ण
	spin_unlock(&dreq->lock);
पूर्ण

अटल स्थिर काष्ठा nfs_pgio_completion_ops nfs_direct_ग_लिखो_completion_ops = अणु
	.error_cleanup = nfs_ग_लिखो_sync_pgio_error,
	.init_hdr = nfs_direct_pgio_init,
	.completion = nfs_direct_ग_लिखो_completion,
	.reschedule_io = nfs_direct_ग_लिखो_reschedule_io,
पूर्ण;


/*
 * NB: Return the value of the first error वापस code.  Subsequent
 *     errors after the first one are ignored.
 */
/*
 * For each wsize'd chunk of the user's buffer, dispatch an NFS WRITE
 * operation.  If nfs_ग_लिखोdata_alloc() or get_user_pages() fails,
 * bail and stop sending more ग_लिखोs.  Write length accounting is
 * handled स्वतःmatically by nfs_direct_ग_लिखो_result().  Otherwise, अगर
 * no requests have been sent, just वापस an error.
 */
अटल sमाप_प्रकार nfs_direct_ग_लिखो_schedule_iovec(काष्ठा nfs_direct_req *dreq,
					       काष्ठा iov_iter *iter,
					       loff_t pos)
अणु
	काष्ठा nfs_pageio_descriptor desc;
	काष्ठा inode *inode = dreq->inode;
	sमाप_प्रकार result = 0;
	माप_प्रकार requested_bytes = 0;
	माप_प्रकार wsize = max_t(माप_प्रकार, NFS_SERVER(inode)->wsize, PAGE_SIZE);

	nfs_pageio_init_ग_लिखो(&desc, inode, FLUSH_COND_STABLE, false,
			      &nfs_direct_ग_लिखो_completion_ops);
	desc.pg_dreq = dreq;
	get_dreq(dreq);
	inode_dio_begin(inode);

	NFS_I(inode)->ग_लिखो_io += iov_iter_count(iter);
	जबतक (iov_iter_count(iter)) अणु
		काष्ठा page **pagevec;
		माप_प्रकार bytes;
		माप_प्रकार pgbase;
		अचिन्हित npages, i;

		result = iov_iter_get_pages_alloc(iter, &pagevec, 
						  wsize, &pgbase);
		अगर (result < 0)
			अवरोध;

		bytes = result;
		iov_iter_advance(iter, bytes);
		npages = (result + pgbase + PAGE_SIZE - 1) / PAGE_SIZE;
		क्रम (i = 0; i < npages; i++) अणु
			काष्ठा nfs_page *req;
			अचिन्हित पूर्णांक req_len = min_t(माप_प्रकार, bytes, PAGE_SIZE - pgbase);

			req = nfs_create_request(dreq->ctx, pagevec[i],
						 pgbase, req_len);
			अगर (IS_ERR(req)) अणु
				result = PTR_ERR(req);
				अवरोध;
			पूर्ण

			अगर (desc.pg_error < 0) अणु
				nfs_मुक्त_request(req);
				result = desc.pg_error;
				अवरोध;
			पूर्ण

			nfs_lock_request(req);
			req->wb_index = pos >> PAGE_SHIFT;
			req->wb_offset = pos & ~PAGE_MASK;
			अगर (!nfs_pageio_add_request(&desc, req)) अणु
				result = desc.pg_error;
				nfs_unlock_and_release_request(req);
				अवरोध;
			पूर्ण
			pgbase = 0;
			bytes -= req_len;
			requested_bytes += req_len;
			pos += req_len;
			dreq->bytes_left -= req_len;
		पूर्ण
		nfs_direct_release_pages(pagevec, npages);
		kvमुक्त(pagevec);
		अगर (result < 0)
			अवरोध;
	पूर्ण
	nfs_pageio_complete(&desc);

	/*
	 * If no bytes were started, वापस the error, and let the
	 * generic layer handle the completion.
	 */
	अगर (requested_bytes == 0) अणु
		inode_dio_end(inode);
		nfs_direct_req_release(dreq);
		वापस result < 0 ? result : -EIO;
	पूर्ण

	अगर (put_dreq(dreq))
		nfs_direct_ग_लिखो_complete(dreq);
	वापस requested_bytes;
पूर्ण

/**
 * nfs_file_direct_ग_लिखो - file direct ग_लिखो operation क्रम NFS files
 * @iocb: target I/O control block
 * @iter: vector of user buffers from which to ग_लिखो data
 *
 * We use this function क्रम direct ग_लिखोs instead of calling
 * generic_file_aio_ग_लिखो() in order to aव्योम taking the inode
 * semaphore and updating the i_size.  The NFS server will set
 * the new i_size and this client must पढ़ो the updated size
 * back पूर्णांकo its cache.  We let the server करो generic ग_लिखो
 * parameter checking and report problems.
 *
 * We eliminate local aसमय updates, see direct पढ़ो above.
 *
 * We aव्योम unnecessary page cache invalidations क्रम normal cached
 * पढ़ोers of this file.
 *
 * Note that O_APPEND is not supported क्रम NFS direct ग_लिखोs, as there
 * is no atomic O_APPEND ग_लिखो facility in the NFS protocol.
 */
sमाप_प्रकार nfs_file_direct_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	sमाप_प्रकार result, requested;
	माप_प्रकार count;
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	काष्ठा nfs_direct_req *dreq;
	काष्ठा nfs_lock_context *l_ctx;
	loff_t pos, end;

	dfprपूर्णांकk(खाता, "NFS: direct write(%pD2, %zd@%Ld)\n",
		file, iov_iter_count(iter), (दीर्घ दीर्घ) iocb->ki_pos);

	result = generic_ग_लिखो_checks(iocb, iter);
	अगर (result <= 0)
		वापस result;
	count = result;
	nfs_add_stats(mapping->host, NFSIOS_सूचीECTWRITTENBYTES, count);

	pos = iocb->ki_pos;
	end = (pos + iov_iter_count(iter) - 1) >> PAGE_SHIFT;

	task_io_account_ग_लिखो(count);

	result = -ENOMEM;
	dreq = nfs_direct_req_alloc();
	अगर (!dreq)
		जाओ out;

	dreq->inode = inode;
	dreq->bytes_left = dreq->max_count = count;
	dreq->io_start = pos;
	dreq->ctx = get_nfs_खोलो_context(nfs_file_खोलो_context(iocb->ki_filp));
	l_ctx = nfs_get_lock_context(dreq->ctx);
	अगर (IS_ERR(l_ctx)) अणु
		result = PTR_ERR(l_ctx);
		nfs_direct_req_release(dreq);
		जाओ out_release;
	पूर्ण
	dreq->l_ctx = l_ctx;
	अगर (!is_sync_kiocb(iocb))
		dreq->iocb = iocb;
	pnfs_init_ds_commit_info_ops(&dreq->ds_cinfo, inode);

	nfs_start_io_direct(inode);

	requested = nfs_direct_ग_लिखो_schedule_iovec(dreq, iter, pos);

	अगर (mapping->nrpages) अणु
		invalidate_inode_pages2_range(mapping,
					      pos >> PAGE_SHIFT, end);
	पूर्ण

	nfs_end_io_direct(inode);

	अगर (requested > 0) अणु
		result = nfs_direct_रुको(dreq);
		अगर (result > 0) अणु
			requested -= result;
			iocb->ki_pos = pos + result;
			/* XXX: should check the generic_ग_लिखो_sync retval */
			generic_ग_लिखो_sync(iocb, result);
		पूर्ण
		iov_iter_revert(iter, requested);
	पूर्ण अन्यथा अणु
		result = requested;
	पूर्ण
out_release:
	nfs_direct_req_release(dreq);
out:
	वापस result;
पूर्ण

/**
 * nfs_init_directcache - create a slab cache क्रम nfs_direct_req काष्ठाures
 *
 */
पूर्णांक __init nfs_init_directcache(व्योम)
अणु
	nfs_direct_cachep = kmem_cache_create("nfs_direct_cache",
						माप(काष्ठा nfs_direct_req),
						0, (SLAB_RECLAIM_ACCOUNT|
							SLAB_MEM_SPREAD),
						शून्य);
	अगर (nfs_direct_cachep == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * nfs_destroy_directcache - destroy the slab cache क्रम nfs_direct_req काष्ठाures
 *
 */
व्योम nfs_destroy_directcache(व्योम)
अणु
	kmem_cache_destroy(nfs_direct_cachep);
पूर्ण
