<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS fileप्रणाली file handling
 *
 * Copyright (C) 2002, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/gfp.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/mm.h>
#समावेश <linux/netfs.h>
#समावेश "internal.h"

अटल पूर्णांक afs_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma);
अटल पूर्णांक afs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page);
अटल व्योम afs_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
			       अचिन्हित पूर्णांक length);
अटल पूर्णांक afs_releasepage(काष्ठा page *page, gfp_t gfp_flags);

अटल व्योम afs_पढ़ोahead(काष्ठा पढ़ोahead_control *ractl);

स्थिर काष्ठा file_operations afs_file_operations = अणु
	.खोलो		= afs_खोलो,
	.release	= afs_release,
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= afs_file_ग_लिखो,
	.mmap		= afs_file_mmap,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.fsync		= afs_fsync,
	.lock		= afs_lock,
	.flock		= afs_flock,
पूर्ण;

स्थिर काष्ठा inode_operations afs_file_inode_operations = अणु
	.getattr	= afs_getattr,
	.setattr	= afs_setattr,
	.permission	= afs_permission,
पूर्ण;

स्थिर काष्ठा address_space_operations afs_fs_aops = अणु
	.पढ़ोpage	= afs_पढ़ोpage,
	.पढ़ोahead	= afs_पढ़ोahead,
	.set_page_dirty	= afs_set_page_dirty,
	.launder_page	= afs_launder_page,
	.releasepage	= afs_releasepage,
	.invalidatepage	= afs_invalidatepage,
	.ग_लिखो_begin	= afs_ग_लिखो_begin,
	.ग_लिखो_end	= afs_ग_लिखो_end,
	.ग_लिखोpage	= afs_ग_लिखोpage,
	.ग_लिखोpages	= afs_ग_लिखोpages,
पूर्ण;

अटल स्थिर काष्ठा vm_operations_काष्ठा afs_vm_ops = अणु
	.fault		= filemap_fault,
	.map_pages	= filemap_map_pages,
	.page_mkग_लिखो	= afs_page_mkग_लिखो,
पूर्ण;

/*
 * Discard a pin on a ग_लिखोback key.
 */
व्योम afs_put_wb_key(काष्ठा afs_wb_key *wbk)
अणु
	अगर (wbk && refcount_dec_and_test(&wbk->usage)) अणु
		key_put(wbk->key);
		kमुक्त(wbk);
	पूर्ण
पूर्ण

/*
 * Cache key क्रम ग_लिखोback.
 */
पूर्णांक afs_cache_wb_key(काष्ठा afs_vnode *vnode, काष्ठा afs_file *af)
अणु
	काष्ठा afs_wb_key *wbk, *p;

	wbk = kzalloc(माप(काष्ठा afs_wb_key), GFP_KERNEL);
	अगर (!wbk)
		वापस -ENOMEM;
	refcount_set(&wbk->usage, 2);
	wbk->key = af->key;

	spin_lock(&vnode->wb_lock);
	list_क्रम_each_entry(p, &vnode->wb_keys, vnode_link) अणु
		अगर (p->key == wbk->key)
			जाओ found;
	पूर्ण

	key_get(wbk->key);
	list_add_tail(&wbk->vnode_link, &vnode->wb_keys);
	spin_unlock(&vnode->wb_lock);
	af->wb = wbk;
	वापस 0;

found:
	refcount_inc(&p->usage);
	spin_unlock(&vnode->wb_lock);
	af->wb = p;
	kमुक्त(wbk);
	वापस 0;
पूर्ण

/*
 * खोलो an AFS file or directory and attach a key to it
 */
पूर्णांक afs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	काष्ठा afs_file *af;
	काष्ठा key *key;
	पूर्णांक ret;

	_enter("{%llx:%llu},", vnode->fid.vid, vnode->fid.vnode);

	key = afs_request_key(vnode->volume->cell);
	अगर (IS_ERR(key)) अणु
		ret = PTR_ERR(key);
		जाओ error;
	पूर्ण

	af = kzalloc(माप(*af), GFP_KERNEL);
	अगर (!af) अणु
		ret = -ENOMEM;
		जाओ error_key;
	पूर्ण
	af->key = key;

	ret = afs_validate(vnode, key);
	अगर (ret < 0)
		जाओ error_af;

	अगर (file->f_mode & FMODE_WRITE) अणु
		ret = afs_cache_wb_key(vnode, af);
		अगर (ret < 0)
			जाओ error_af;
	पूर्ण

	अगर (file->f_flags & O_TRUNC)
		set_bit(AFS_VNODE_NEW_CONTENT, &vnode->flags);
	
	file->निजी_data = af;
	_leave(" = 0");
	वापस 0;

error_af:
	kमुक्त(af);
error_key:
	key_put(key);
error:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * release an AFS file or directory and discard its key
 */
पूर्णांक afs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	काष्ठा afs_file *af = file->निजी_data;
	पूर्णांक ret = 0;

	_enter("{%llx:%llu},", vnode->fid.vid, vnode->fid.vnode);

	अगर ((file->f_mode & FMODE_WRITE))
		ret = vfs_fsync(file, 0);

	file->निजी_data = शून्य;
	अगर (af->wb)
		afs_put_wb_key(af->wb);
	key_put(af->key);
	kमुक्त(af);
	afs_prune_wb_keys(vnode);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Allocate a new पढ़ो record.
 */
काष्ठा afs_पढ़ो *afs_alloc_पढ़ो(gfp_t gfp)
अणु
	काष्ठा afs_पढ़ो *req;

	req = kzalloc(माप(काष्ठा afs_पढ़ो), gfp);
	अगर (req)
		refcount_set(&req->usage, 1);

	वापस req;
पूर्ण

/*
 * Dispose of a ref to a पढ़ो record.
 */
व्योम afs_put_पढ़ो(काष्ठा afs_पढ़ो *req)
अणु
	अगर (refcount_dec_and_test(&req->usage)) अणु
		अगर (req->cleanup)
			req->cleanup(req);
		key_put(req->key);
		kमुक्त(req);
	पूर्ण
पूर्ण

अटल व्योम afs_fetch_data_notअगरy(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_पढ़ो *req = op->fetch.req;
	काष्ठा netfs_पढ़ो_subrequest *subreq = req->subreq;
	पूर्णांक error = op->error;

	अगर (error == -ECONNABORTED)
		error = afs_पात_to_error(op->ac.पात_code);
	req->error = error;

	अगर (subreq) अणु
		__set_bit(NETFS_SREQ_CLEAR_TAIL, &subreq->flags);
		netfs_subreq_terminated(subreq, error ?: req->actual_len, false);
		req->subreq = शून्य;
	पूर्ण अन्यथा अगर (req->करोne) अणु
		req->करोne(req);
	पूर्ण
पूर्ण

अटल व्योम afs_fetch_data_success(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode *vnode = op->file[0].vnode;

	_enter("op=%08x", op->debug_id);
	afs_vnode_commit_status(op, &op->file[0]);
	afs_stat_v(vnode, n_fetches);
	atomic_दीर्घ_add(op->fetch.req->actual_len, &op->net->n_fetch_bytes);
	afs_fetch_data_notअगरy(op);
पूर्ण

अटल व्योम afs_fetch_data_put(काष्ठा afs_operation *op)
अणु
	op->fetch.req->error = op->error;
	afs_put_पढ़ो(op->fetch.req);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_fetch_data_operation = अणु
	.issue_afs_rpc	= afs_fs_fetch_data,
	.issue_yfs_rpc	= yfs_fs_fetch_data,
	.success	= afs_fetch_data_success,
	.पातed	= afs_check_क्रम_remote_deletion,
	.failed		= afs_fetch_data_notअगरy,
	.put		= afs_fetch_data_put,
पूर्ण;

/*
 * Fetch file data from the volume.
 */
पूर्णांक afs_fetch_data(काष्ठा afs_vnode *vnode, काष्ठा afs_पढ़ो *req)
अणु
	काष्ठा afs_operation *op;

	_enter("%s{%llx:%llu.%u},%x,,,",
	       vnode->volume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_serial(req->key));

	op = afs_alloc_operation(req->key, vnode->volume);
	अगर (IS_ERR(op)) अणु
		अगर (req->subreq)
			netfs_subreq_terminated(req->subreq, PTR_ERR(op), false);
		वापस PTR_ERR(op);
	पूर्ण

	afs_op_set_vnode(op, 0, vnode);

	op->fetch.req	= afs_get_पढ़ो(req);
	op->ops		= &afs_fetch_data_operation;
	वापस afs_करो_sync_operation(op);
पूर्ण

अटल व्योम afs_req_issue_op(काष्ठा netfs_पढ़ो_subrequest *subreq)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(subreq->rreq->inode);
	काष्ठा afs_पढ़ो *fsreq;

	fsreq = afs_alloc_पढ़ो(GFP_NOFS);
	अगर (!fsreq)
		वापस netfs_subreq_terminated(subreq, -ENOMEM, false);

	fsreq->subreq	= subreq;
	fsreq->pos	= subreq->start + subreq->transferred;
	fsreq->len	= subreq->len   - subreq->transferred;
	fsreq->key	= subreq->rreq->netfs_priv;
	fsreq->vnode	= vnode;
	fsreq->iter	= &fsreq->def_iter;

	iov_iter_xarray(&fsreq->def_iter, READ,
			&fsreq->vnode->vfs_inode.i_mapping->i_pages,
			fsreq->pos, fsreq->len);

	afs_fetch_data(fsreq->vnode, fsreq);
पूर्ण

अटल पूर्णांक afs_symlink_पढ़ोpage(काष्ठा page *page)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(page->mapping->host);
	काष्ठा afs_पढ़ो *fsreq;
	पूर्णांक ret;

	fsreq = afs_alloc_पढ़ो(GFP_NOFS);
	अगर (!fsreq)
		वापस -ENOMEM;

	fsreq->pos	= page->index * PAGE_SIZE;
	fsreq->len	= PAGE_SIZE;
	fsreq->vnode	= vnode;
	fsreq->iter	= &fsreq->def_iter;
	iov_iter_xarray(&fsreq->def_iter, READ, &page->mapping->i_pages,
			fsreq->pos, fsreq->len);

	ret = afs_fetch_data(fsreq->vnode, fsreq);
	page_endio(page, false, ret);
	वापस ret;
पूर्ण

अटल व्योम afs_init_rreq(काष्ठा netfs_पढ़ो_request *rreq, काष्ठा file *file)
अणु
	rreq->netfs_priv = key_get(afs_file_key(file));
पूर्ण

अटल bool afs_is_cache_enabled(काष्ठा inode *inode)
अणु
	काष्ठा fscache_cookie *cookie = afs_vnode_cache(AFS_FS_I(inode));

	वापस fscache_cookie_enabled(cookie) && !hlist_empty(&cookie->backing_objects);
पूर्ण

अटल पूर्णांक afs_begin_cache_operation(काष्ठा netfs_पढ़ो_request *rreq)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(rreq->inode);

	वापस fscache_begin_पढ़ो_operation(rreq, afs_vnode_cache(vnode));
पूर्ण

अटल पूर्णांक afs_check_ग_लिखो_begin(काष्ठा file *file, loff_t pos, अचिन्हित len,
				 काष्ठा page *page, व्योम **_fsdata)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(file_inode(file));

	वापस test_bit(AFS_VNODE_DELETED, &vnode->flags) ? -ESTALE : 0;
पूर्ण

अटल व्योम afs_priv_cleanup(काष्ठा address_space *mapping, व्योम *netfs_priv)
अणु
	key_put(netfs_priv);
पूर्ण

स्थिर काष्ठा netfs_पढ़ो_request_ops afs_req_ops = अणु
	.init_rreq		= afs_init_rreq,
	.is_cache_enabled	= afs_is_cache_enabled,
	.begin_cache_operation	= afs_begin_cache_operation,
	.check_ग_लिखो_begin	= afs_check_ग_लिखो_begin,
	.issue_op		= afs_req_issue_op,
	.cleanup		= afs_priv_cleanup,
पूर्ण;

अटल पूर्णांक afs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	अगर (!file)
		वापस afs_symlink_पढ़ोpage(page);

	वापस netfs_पढ़ोpage(file, page, &afs_req_ops, शून्य);
पूर्ण

अटल व्योम afs_पढ़ोahead(काष्ठा पढ़ोahead_control *ractl)
अणु
	netfs_पढ़ोahead(ractl, &afs_req_ops, शून्य);
पूर्ण

/*
 * Adjust the dirty region of the page on truncation or full invalidation,
 * getting rid of the markers altogether अगर the region is entirely invalidated.
 */
अटल व्योम afs_invalidate_dirty(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				 अचिन्हित पूर्णांक length)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(page->mapping->host);
	अचिन्हित दीर्घ priv;
	अचिन्हित पूर्णांक f, t, end = offset + length;

	priv = page_निजी(page);

	/* we clean up only अगर the entire page is being invalidated */
	अगर (offset == 0 && length == thp_size(page))
		जाओ full_invalidate;

	 /* If the page was dirtied by page_mkग_लिखो(), the PTE stays writable
	  * and we करोn't get another notअगरication to tell us to expand it
	  * again.
	  */
	अगर (afs_is_page_dirty_mmapped(priv))
		वापस;

	/* We may need to लघुen the dirty region */
	f = afs_page_dirty_from(page, priv);
	t = afs_page_dirty_to(page, priv);

	अगर (t <= offset || f >= end)
		वापस; /* Doesn't overlap */

	अगर (f < offset && t > end)
		वापस; /* Splits the dirty region - just असलorb it */

	अगर (f >= offset && t <= end)
		जाओ undirty;

	अगर (f < offset)
		t = offset;
	अन्यथा
		f = end;
	अगर (f == t)
		जाओ undirty;

	priv = afs_page_dirty(page, f, t);
	set_page_निजी(page, priv);
	trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("trunc"), page);
	वापस;

undirty:
	trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("undirty"), page);
	clear_page_dirty_क्रम_io(page);
full_invalidate:
	trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("inval"), page);
	detach_page_निजी(page);
पूर्ण

/*
 * invalidate part or all of a page
 * - release a page and clean up its निजी data अगर offset is 0 (indicating
 *   the entire page)
 */
अटल व्योम afs_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
			       अचिन्हित पूर्णांक length)
अणु
	_enter("{%lu},%u,%u", page->index, offset, length);

	BUG_ON(!PageLocked(page));

	अगर (PagePrivate(page))
		afs_invalidate_dirty(page, offset, length);

	रुको_on_page_fscache(page);
	_leave("");
पूर्ण

/*
 * release a page and clean up its निजी state अगर it's not busy
 * - वापस true अगर the page can now be released, false अगर not
 */
अटल पूर्णांक afs_releasepage(काष्ठा page *page, gfp_t gfp_flags)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(page->mapping->host);

	_enter("{{%llx:%llu}[%lu],%lx},%x",
	       vnode->fid.vid, vnode->fid.vnode, page->index, page->flags,
	       gfp_flags);

	/* deny अगर page is being written to the cache and the caller hasn't
	 * elected to रुको */
#अगर_घोषित CONFIG_AFS_FSCACHE
	अगर (PageFsCache(page)) अणु
		अगर (!(gfp_flags & __GFP_सूचीECT_RECLAIM) || !(gfp_flags & __GFP_FS))
			वापस false;
		रुको_on_page_fscache(page);
	पूर्ण
#पूर्ण_अगर

	अगर (PagePrivate(page)) अणु
		trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("rel"), page);
		detach_page_निजी(page);
	पूर्ण

	/* indicate that the page can be released */
	_leave(" = T");
	वापस 1;
पूर्ण

/*
 * Handle setting up a memory mapping on an AFS file.
 */
अटल पूर्णांक afs_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	ret = generic_file_mmap(file, vma);
	अगर (ret == 0)
		vma->vm_ops = &afs_vm_ops;
	वापस ret;
पूर्ण
