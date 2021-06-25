<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/nfs/पढ़ो.c
 *
 * Block I/O क्रम NFS
 *
 * Partial copy of Linus' पढ़ो cache modअगरications to fs/nfs/file.c
 * modअगरied क्रम async RPC by okir@monad.swb.de
 */

#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/module.h>

#समावेश "nfs4_fs.h"
#समावेश "internal.h"
#समावेश "iostat.h"
#समावेश "fscache.h"
#समावेश "pnfs.h"
#समावेश "nfstrace.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PAGECACHE

अटल स्थिर काष्ठा nfs_pgio_completion_ops nfs_async_पढ़ो_completion_ops;
अटल स्थिर काष्ठा nfs_rw_ops nfs_rw_पढ़ो_ops;

अटल काष्ठा kmem_cache *nfs_rdata_cachep;

अटल काष्ठा nfs_pgio_header *nfs_पढ़ोhdr_alloc(व्योम)
अणु
	काष्ठा nfs_pgio_header *p = kmem_cache_zalloc(nfs_rdata_cachep, GFP_KERNEL);

	अगर (p)
		p->rw_mode = FMODE_READ;
	वापस p;
पूर्ण

अटल व्योम nfs_पढ़ोhdr_मुक्त(काष्ठा nfs_pgio_header *rhdr)
अणु
	kmem_cache_मुक्त(nfs_rdata_cachep, rhdr);
पूर्ण

अटल
पूर्णांक nfs_वापस_empty_page(काष्ठा page *page)
अणु
	zero_user(page, 0, PAGE_SIZE);
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;
पूर्ण

व्योम nfs_pageio_init_पढ़ो(काष्ठा nfs_pageio_descriptor *pgio,
			      काष्ठा inode *inode, bool क्रमce_mds,
			      स्थिर काष्ठा nfs_pgio_completion_ops *compl_ops)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	स्थिर काष्ठा nfs_pageio_ops *pg_ops = &nfs_pgio_rw_ops;

#अगर_घोषित CONFIG_NFS_V4_1
	अगर (server->pnfs_curr_ld && !क्रमce_mds)
		pg_ops = server->pnfs_curr_ld->pg_पढ़ो_ops;
#पूर्ण_अगर
	nfs_pageio_init(pgio, inode, pg_ops, compl_ops, &nfs_rw_पढ़ो_ops,
			server->rsize, 0);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_pageio_init_पढ़ो);

अटल व्योम nfs_pageio_complete_पढ़ो(काष्ठा nfs_pageio_descriptor *pgio,
				     काष्ठा inode *inode)
अणु
	काष्ठा nfs_pgio_mirror *pgm;
	अचिन्हित दीर्घ npages;

	nfs_pageio_complete(pgio);

	/* It करोesn't make sense to करो mirrored पढ़ोs! */
	WARN_ON_ONCE(pgio->pg_mirror_count != 1);

	pgm = &pgio->pg_mirrors[0];
	NFS_I(inode)->पढ़ो_io += pgm->pg_bytes_written;
	npages = (pgm->pg_bytes_written + PAGE_SIZE - 1) >> PAGE_SHIFT;
	nfs_add_stats(inode, NFSIOS_READPAGES, npages);
पूर्ण


व्योम nfs_pageio_reset_पढ़ो_mds(काष्ठा nfs_pageio_descriptor *pgio)
अणु
	काष्ठा nfs_pgio_mirror *mirror;

	अगर (pgio->pg_ops && pgio->pg_ops->pg_cleanup)
		pgio->pg_ops->pg_cleanup(pgio);

	pgio->pg_ops = &nfs_pgio_rw_ops;

	/* पढ़ो path should never have more than one mirror */
	WARN_ON_ONCE(pgio->pg_mirror_count != 1);

	mirror = &pgio->pg_mirrors[0];
	mirror->pg_bsize = NFS_SERVER(pgio->pg_inode)->rsize;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_pageio_reset_पढ़ो_mds);

अटल व्योम nfs_पढ़ोpage_release(काष्ठा nfs_page *req, पूर्णांक error)
अणु
	काष्ठा inode *inode = d_inode(nfs_req_खोलोctx(req)->dentry);
	काष्ठा page *page = req->wb_page;

	dprपूर्णांकk("NFS: read done (%s/%llu %d@%lld)\n", inode->i_sb->s_id,
		(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(inode), req->wb_bytes,
		(दीर्घ दीर्घ)req_offset(req));

	अगर (nfs_error_is_fatal_on_server(error) && error != -ETIMEDOUT)
		SetPageError(page);
	अगर (nfs_page_group_sync_on_bit(req, PG_UNLOCKPAGE)) अणु
		काष्ठा address_space *mapping = page_file_mapping(page);

		अगर (PageUptodate(page))
			nfs_पढ़ोpage_to_fscache(inode, page, 0);
		अन्यथा अगर (!PageError(page) && !PagePrivate(page))
			generic_error_हटाओ_page(mapping, page);
		unlock_page(page);
	पूर्ण
	nfs_release_request(req);
पूर्ण

काष्ठा nfs_पढ़ोdesc अणु
	काष्ठा nfs_pageio_descriptor pgio;
	काष्ठा nfs_खोलो_context *ctx;
पूर्ण;

अटल व्योम nfs_page_group_set_uptodate(काष्ठा nfs_page *req)
अणु
	अगर (nfs_page_group_sync_on_bit(req, PG_UPTODATE))
		SetPageUptodate(req->wb_page);
पूर्ण

अटल व्योम nfs_पढ़ो_completion(काष्ठा nfs_pgio_header *hdr)
अणु
	अचिन्हित दीर्घ bytes = 0;
	पूर्णांक error;

	अगर (test_bit(NFS_IOHDR_REDO, &hdr->flags))
		जाओ out;
	जबतक (!list_empty(&hdr->pages)) अणु
		काष्ठा nfs_page *req = nfs_list_entry(hdr->pages.next);
		काष्ठा page *page = req->wb_page;
		अचिन्हित दीर्घ start = req->wb_pgbase;
		अचिन्हित दीर्घ end = req->wb_pgbase + req->wb_bytes;

		अगर (test_bit(NFS_IOHDR_खातापूर्ण, &hdr->flags)) अणु
			/* note: regions of the page not covered by a
			 * request are zeroed in पढ़ोpage_async_filler */
			अगर (bytes > hdr->good_bytes) अणु
				/* nothing in this request was good, so zero
				 * the full extent of the request */
				zero_user_segment(page, start, end);

			पूर्ण अन्यथा अगर (hdr->good_bytes - bytes < req->wb_bytes) अणु
				/* part of this request has good bytes, but
				 * not all. zero the bad bytes */
				start += hdr->good_bytes - bytes;
				WARN_ON(start < req->wb_pgbase);
				zero_user_segment(page, start, end);
			पूर्ण
		पूर्ण
		error = 0;
		bytes += req->wb_bytes;
		अगर (test_bit(NFS_IOHDR_ERROR, &hdr->flags)) अणु
			अगर (bytes <= hdr->good_bytes)
				nfs_page_group_set_uptodate(req);
			अन्यथा अणु
				error = hdr->error;
				xchg(&nfs_req_खोलोctx(req)->error, error);
			पूर्ण
		पूर्ण अन्यथा
			nfs_page_group_set_uptodate(req);
		nfs_list_हटाओ_request(req);
		nfs_पढ़ोpage_release(req, error);
	पूर्ण
out:
	hdr->release(hdr);
पूर्ण

अटल व्योम nfs_initiate_पढ़ो(काष्ठा nfs_pgio_header *hdr,
			      काष्ठा rpc_message *msg,
			      स्थिर काष्ठा nfs_rpc_ops *rpc_ops,
			      काष्ठा rpc_task_setup *task_setup_data, पूर्णांक how)
अणु
	काष्ठा inode *inode = hdr->inode;
	पूर्णांक swap_flags = IS_SWAPखाता(inode) ? NFS_RPC_SWAPFLAGS : 0;

	task_setup_data->flags |= swap_flags;
	rpc_ops->पढ़ो_setup(hdr, msg);
	trace_nfs_initiate_पढ़ो(hdr);
पूर्ण

अटल व्योम
nfs_async_पढ़ो_error(काष्ठा list_head *head, पूर्णांक error)
अणु
	काष्ठा nfs_page	*req;

	जबतक (!list_empty(head)) अणु
		req = nfs_list_entry(head->next);
		nfs_list_हटाओ_request(req);
		nfs_पढ़ोpage_release(req, error);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nfs_pgio_completion_ops nfs_async_पढ़ो_completion_ops = अणु
	.error_cleanup = nfs_async_पढ़ो_error,
	.completion = nfs_पढ़ो_completion,
पूर्ण;

/*
 * This is the callback from RPC telling us whether a reply was
 * received or some error occurred (समयout or socket shutकरोwn).
 */
अटल पूर्णांक nfs_पढ़ोpage_करोne(काष्ठा rpc_task *task,
			     काष्ठा nfs_pgio_header *hdr,
			     काष्ठा inode *inode)
अणु
	पूर्णांक status = NFS_PROTO(inode)->पढ़ो_करोne(task, hdr);
	अगर (status != 0)
		वापस status;

	nfs_add_stats(inode, NFSIOS_SERVERREADBYTES, hdr->res.count);
	trace_nfs_पढ़ोpage_करोne(task, hdr);

	अगर (task->tk_status == -ESTALE) अणु
		nfs_set_inode_stale(inode);
		nfs_mark_क्रम_revalidate(inode);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nfs_पढ़ोpage_retry(काष्ठा rpc_task *task,
			       काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_pgio_args *argp = &hdr->args;
	काष्ठा nfs_pgio_res  *resp = &hdr->res;

	/* This is a लघु पढ़ो! */
	nfs_inc_stats(hdr->inode, NFSIOS_SHORTREAD);
	trace_nfs_पढ़ोpage_लघु(task, hdr);

	/* Has the server at least made some progress? */
	अगर (resp->count == 0) अणु
		nfs_set_pgio_error(hdr, -EIO, argp->offset);
		वापस;
	पूर्ण

	/* For non rpc-based layout drivers, retry-through-MDS */
	अगर (!task->tk_ops) अणु
		hdr->pnfs_error = -EAGAIN;
		वापस;
	पूर्ण

	/* Yes, so retry the पढ़ो at the end of the hdr */
	hdr->mds_offset += resp->count;
	argp->offset += resp->count;
	argp->pgbase += resp->count;
	argp->count -= resp->count;
	resp->count = 0;
	resp->eof = 0;
	rpc_restart_call_prepare(task);
पूर्ण

अटल व्योम nfs_पढ़ोpage_result(काष्ठा rpc_task *task,
				काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (hdr->res.eof) अणु
		loff_t pos = hdr->args.offset + hdr->res.count;
		अचिन्हित पूर्णांक new = pos - hdr->io_start;

		अगर (hdr->good_bytes > new) अणु
			hdr->good_bytes = new;
			set_bit(NFS_IOHDR_खातापूर्ण, &hdr->flags);
			clear_bit(NFS_IOHDR_ERROR, &hdr->flags);
		पूर्ण
	पूर्ण अन्यथा अगर (hdr->res.count < hdr->args.count)
		nfs_पढ़ोpage_retry(task, hdr);
पूर्ण

अटल पूर्णांक
पढ़ोpage_async_filler(व्योम *data, काष्ठा page *page)
अणु
	काष्ठा nfs_पढ़ोdesc *desc = data;
	काष्ठा nfs_page *new;
	अचिन्हित पूर्णांक len;
	पूर्णांक error;

	len = nfs_page_length(page);
	अगर (len == 0)
		वापस nfs_वापस_empty_page(page);

	new = nfs_create_request(desc->ctx, page, 0, len);
	अगर (IS_ERR(new))
		जाओ out_error;

	अगर (len < PAGE_SIZE)
		zero_user_segment(page, len, PAGE_SIZE);
	अगर (!nfs_pageio_add_request(&desc->pgio, new)) अणु
		nfs_list_हटाओ_request(new);
		error = desc->pgio.pg_error;
		nfs_पढ़ोpage_release(new, error);
		जाओ out;
	पूर्ण
	वापस 0;
out_error:
	error = PTR_ERR(new);
	unlock_page(page);
out:
	वापस error;
पूर्ण

/*
 * Read a page over NFS.
 * We पढ़ो the page synchronously in the following हाल:
 *  -	The error flag is set क्रम this page. This happens only when a
 *	previous async पढ़ो operation failed.
 */
पूर्णांक nfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा nfs_पढ़ोdesc desc;
	काष्ठा inode *inode = page_file_mapping(page)->host;
	पूर्णांक ret;

	dprपूर्णांकk("NFS: nfs_readpage (%p %ld@%lu)\n",
		page, PAGE_SIZE, page_index(page));
	nfs_inc_stats(inode, NFSIOS_VFSREADPAGE);

	/*
	 * Try to flush any pending ग_लिखोs to the file..
	 *
	 * NOTE! Because we own the page lock, there cannot
	 * be any new pending ग_लिखोs generated at this poपूर्णांक
	 * क्रम this page (other pages can be written to).
	 */
	ret = nfs_wb_page(inode, page);
	अगर (ret)
		जाओ out_unlock;
	अगर (PageUptodate(page))
		जाओ out_unlock;

	ret = -ESTALE;
	अगर (NFS_STALE(inode))
		जाओ out_unlock;

	अगर (file == शून्य) अणु
		ret = -EBADF;
		desc.ctx = nfs_find_खोलो_context(inode, शून्य, FMODE_READ);
		अगर (desc.ctx == शून्य)
			जाओ out_unlock;
	पूर्ण अन्यथा
		desc.ctx = get_nfs_खोलो_context(nfs_file_खोलो_context(file));

	अगर (!IS_SYNC(inode)) अणु
		ret = nfs_पढ़ोpage_from_fscache(desc.ctx, inode, page);
		अगर (ret == 0)
			जाओ out;
	पूर्ण

	xchg(&desc.ctx->error, 0);
	nfs_pageio_init_पढ़ो(&desc.pgio, inode, false,
			     &nfs_async_पढ़ो_completion_ops);

	ret = पढ़ोpage_async_filler(&desc, page);

	अगर (!ret)
		nfs_pageio_complete_पढ़ो(&desc.pgio, inode);

	ret = desc.pgio.pg_error < 0 ? desc.pgio.pg_error : 0;
	अगर (!ret) अणु
		ret = रुको_on_page_locked_समाप्तable(page);
		अगर (!PageUptodate(page) && !ret)
			ret = xchg(&desc.ctx->error, 0);
	पूर्ण
out:
	put_nfs_खोलो_context(desc.ctx);
	वापस ret;
out_unlock:
	unlock_page(page);
	वापस ret;
पूर्ण

पूर्णांक nfs_पढ़ोpages(काष्ठा file *file, काष्ठा address_space *mapping,
		काष्ठा list_head *pages, अचिन्हित nr_pages)
अणु
	काष्ठा nfs_पढ़ोdesc desc;
	काष्ठा inode *inode = mapping->host;
	पूर्णांक ret;

	dprपूर्णांकk("NFS: nfs_readpages (%s/%Lu %d)\n",
			inode->i_sb->s_id,
			(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(inode),
			nr_pages);
	nfs_inc_stats(inode, NFSIOS_VFSREADPAGES);

	ret = -ESTALE;
	अगर (NFS_STALE(inode))
		जाओ out;

	अगर (file == शून्य) अणु
		ret = -EBADF;
		desc.ctx = nfs_find_खोलो_context(inode, शून्य, FMODE_READ);
		अगर (desc.ctx == शून्य)
			जाओ out;
	पूर्ण अन्यथा
		desc.ctx = get_nfs_खोलो_context(nfs_file_खोलो_context(file));

	/* attempt to पढ़ो as many of the pages as possible from the cache
	 * - this वापसs -ENOBUFS immediately अगर the cookie is negative
	 */
	ret = nfs_पढ़ोpages_from_fscache(desc.ctx, inode, mapping,
					 pages, &nr_pages);
	अगर (ret == 0)
		जाओ पढ़ो_complete; /* all pages were पढ़ो */

	nfs_pageio_init_पढ़ो(&desc.pgio, inode, false,
			     &nfs_async_पढ़ो_completion_ops);

	ret = पढ़ो_cache_pages(mapping, pages, पढ़ोpage_async_filler, &desc);

	nfs_pageio_complete_पढ़ो(&desc.pgio, inode);

पढ़ो_complete:
	put_nfs_खोलो_context(desc.ctx);
out:
	वापस ret;
पूर्ण

पूर्णांक __init nfs_init_पढ़ोpagecache(व्योम)
अणु
	nfs_rdata_cachep = kmem_cache_create("nfs_read_data",
					     माप(काष्ठा nfs_pgio_header),
					     0, SLAB_HWCACHE_ALIGN,
					     शून्य);
	अगर (nfs_rdata_cachep == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम nfs_destroy_पढ़ोpagecache(व्योम)
अणु
	kmem_cache_destroy(nfs_rdata_cachep);
पूर्ण

अटल स्थिर काष्ठा nfs_rw_ops nfs_rw_पढ़ो_ops = अणु
	.rw_alloc_header	= nfs_पढ़ोhdr_alloc,
	.rw_मुक्त_header		= nfs_पढ़ोhdr_मुक्त,
	.rw_करोne		= nfs_पढ़ोpage_करोne,
	.rw_result		= nfs_पढ़ोpage_result,
	.rw_initiate		= nfs_initiate_पढ़ो,
पूर्ण;
