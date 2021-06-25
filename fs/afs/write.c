<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* handling of ग_लिखोs to regular files and writing back to the server
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/backing-dev.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/netfs.h>
#समावेश <linux/fscache.h>
#समावेश "internal.h"

/*
 * mark a page as having been made dirty and thus needing ग_लिखोback
 */
पूर्णांक afs_set_page_dirty(काष्ठा page *page)
अणु
	_enter("");
	वापस __set_page_dirty_nobuffers(page);
पूर्ण

/*
 * prepare to perक्रमm part of a ग_लिखो to a page
 */
पूर्णांक afs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
		    loff_t pos, अचिन्हित len, अचिन्हित flags,
		    काष्ठा page **_page, व्योम **fsdata)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(file_inode(file));
	काष्ठा page *page;
	अचिन्हित दीर्घ priv;
	अचिन्हित f, from;
	अचिन्हित t, to;
	pgoff_t index;
	पूर्णांक ret;

	_enter("{%llx:%llu},%llx,%x",
	       vnode->fid.vid, vnode->fid.vnode, pos, len);

	/* Prefetch area to be written पूर्णांकo the cache अगर we're caching this
	 * file.  We need to करो this beक्रमe we get a lock on the page in हाल
	 * there's more than one ग_लिखोr competing क्रम the same cache block.
	 */
	ret = netfs_ग_लिखो_begin(file, mapping, pos, len, flags, &page, fsdata,
				&afs_req_ops, शून्य);
	अगर (ret < 0)
		वापस ret;

	index = page->index;
	from = pos - index * PAGE_SIZE;
	to = from + len;

try_again:
	/* See अगर this page is alपढ़ोy partially written in a way that we can
	 * merge the new ग_लिखो with.
	 */
	अगर (PagePrivate(page)) अणु
		priv = page_निजी(page);
		f = afs_page_dirty_from(page, priv);
		t = afs_page_dirty_to(page, priv);
		ASSERTCMP(f, <=, t);

		अगर (PageWriteback(page)) अणु
			trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("alrdy"), page);
			जाओ flush_conflicting_ग_लिखो;
		पूर्ण
		/* If the file is being filled locally, allow पूर्णांकer-ग_लिखो
		 * spaces to be merged पूर्णांकo ग_लिखोs.  If it's not, only ग_लिखो
		 * back what the user gives us.
		 */
		अगर (!test_bit(AFS_VNODE_NEW_CONTENT, &vnode->flags) &&
		    (to < f || from > t))
			जाओ flush_conflicting_ग_लिखो;
	पूर्ण

	*_page = page;
	_leave(" = 0");
	वापस 0;

	/* The previous ग_लिखो and this ग_लिखो aren't adjacent or overlapping, so
	 * flush the page out.
	 */
flush_conflicting_ग_लिखो:
	_debug("flush conflict");
	ret = ग_लिखो_one_page(page);
	अगर (ret < 0)
		जाओ error;

	ret = lock_page_समाप्तable(page);
	अगर (ret < 0)
		जाओ error;
	जाओ try_again;

error:
	put_page(page);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * finalise part of a ग_लिखो to a page
 */
पूर्णांक afs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
		  loff_t pos, अचिन्हित len, अचिन्हित copied,
		  काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(file_inode(file));
	अचिन्हित दीर्घ priv;
	अचिन्हित पूर्णांक f, from = pos & (thp_size(page) - 1);
	अचिन्हित पूर्णांक t, to = from + copied;
	loff_t i_size, maybe_i_size;

	_enter("{%llx:%llu},{%lx}",
	       vnode->fid.vid, vnode->fid.vnode, page->index);

	अगर (copied == 0)
		जाओ out;

	maybe_i_size = pos + copied;

	i_size = i_size_पढ़ो(&vnode->vfs_inode);
	अगर (maybe_i_size > i_size) अणु
		ग_लिखो_seqlock(&vnode->cb_lock);
		i_size = i_size_पढ़ो(&vnode->vfs_inode);
		अगर (maybe_i_size > i_size)
			i_size_ग_लिखो(&vnode->vfs_inode, maybe_i_size);
		ग_लिखो_sequnlock(&vnode->cb_lock);
	पूर्ण

	ASSERT(PageUptodate(page));

	अगर (PagePrivate(page)) अणु
		priv = page_निजी(page);
		f = afs_page_dirty_from(page, priv);
		t = afs_page_dirty_to(page, priv);
		अगर (from < f)
			f = from;
		अगर (to > t)
			t = to;
		priv = afs_page_dirty(page, f, t);
		set_page_निजी(page, priv);
		trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("dirty+"), page);
	पूर्ण अन्यथा अणु
		priv = afs_page_dirty(page, from, to);
		attach_page_निजी(page, (व्योम *)priv);
		trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("dirty"), page);
	पूर्ण

	अगर (set_page_dirty(page))
		_debug("dirtied %lx", page->index);

out:
	unlock_page(page);
	put_page(page);
	वापस copied;
पूर्ण

/*
 * समाप्त all the pages in the given range
 */
अटल व्योम afs_समाप्त_pages(काष्ठा address_space *mapping,
			   loff_t start, loff_t len)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(mapping->host);
	काष्ठा pagevec pv;
	अचिन्हित पूर्णांक loop, psize;

	_enter("{%llx:%llu},%llx @%llx",
	       vnode->fid.vid, vnode->fid.vnode, len, start);

	pagevec_init(&pv);

	करो अणु
		_debug("kill %llx @%llx", len, start);

		pv.nr = find_get_pages_contig(mapping, start / PAGE_SIZE,
					      PAGEVEC_SIZE, pv.pages);
		अगर (pv.nr == 0)
			अवरोध;

		क्रम (loop = 0; loop < pv.nr; loop++) अणु
			काष्ठा page *page = pv.pages[loop];

			अगर (page->index * PAGE_SIZE >= start + len)
				अवरोध;

			psize = thp_size(page);
			start += psize;
			len -= psize;
			ClearPageUptodate(page);
			end_page_ग_लिखोback(page);
			lock_page(page);
			generic_error_हटाओ_page(mapping, page);
			unlock_page(page);
		पूर्ण

		__pagevec_release(&pv);
	पूर्ण जबतक (len > 0);

	_leave("");
पूर्ण

/*
 * Redirty all the pages in a given range.
 */
अटल व्योम afs_redirty_pages(काष्ठा ग_लिखोback_control *wbc,
			      काष्ठा address_space *mapping,
			      loff_t start, loff_t len)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(mapping->host);
	काष्ठा pagevec pv;
	अचिन्हित पूर्णांक loop, psize;

	_enter("{%llx:%llu},%llx @%llx",
	       vnode->fid.vid, vnode->fid.vnode, len, start);

	pagevec_init(&pv);

	करो अणु
		_debug("redirty %llx @%llx", len, start);

		pv.nr = find_get_pages_contig(mapping, start / PAGE_SIZE,
					      PAGEVEC_SIZE, pv.pages);
		अगर (pv.nr == 0)
			अवरोध;

		क्रम (loop = 0; loop < pv.nr; loop++) अणु
			काष्ठा page *page = pv.pages[loop];

			अगर (page->index * PAGE_SIZE >= start + len)
				अवरोध;

			psize = thp_size(page);
			start += psize;
			len -= psize;
			redirty_page_क्रम_ग_लिखोpage(wbc, page);
			end_page_ग_लिखोback(page);
		पूर्ण

		__pagevec_release(&pv);
	पूर्ण जबतक (len > 0);

	_leave("");
पूर्ण

/*
 * completion of ग_लिखो to server
 */
अटल व्योम afs_pages_written_back(काष्ठा afs_vnode *vnode, loff_t start, अचिन्हित पूर्णांक len)
अणु
	काष्ठा address_space *mapping = vnode->vfs_inode.i_mapping;
	काष्ठा page *page;
	pgoff_t end;

	XA_STATE(xas, &mapping->i_pages, start / PAGE_SIZE);

	_enter("{%llx:%llu},{%x @%llx}",
	       vnode->fid.vid, vnode->fid.vnode, len, start);

	rcu_पढ़ो_lock();

	end = (start + len - 1) / PAGE_SIZE;
	xas_क्रम_each(&xas, page, end) अणु
		अगर (!PageWriteback(page)) अणु
			kdebug("bad %x @%llx page %lx %lx", len, start, page->index, end);
			ASSERT(PageWriteback(page));
		पूर्ण

		trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("clear"), page);
		detach_page_निजी(page);
		page_endio(page, true, 0);
	पूर्ण

	rcu_पढ़ो_unlock();

	afs_prune_wb_keys(vnode);
	_leave("");
पूर्ण

/*
 * Find a key to use क्रम the ग_लिखोback.  We cached the keys used to author the
 * ग_लिखोs on the vnode.  *_wbk will contain the last ग_लिखोback key used or शून्य
 * and we need to start from there अगर it's set.
 */
अटल पूर्णांक afs_get_ग_लिखोback_key(काष्ठा afs_vnode *vnode,
				 काष्ठा afs_wb_key **_wbk)
अणु
	काष्ठा afs_wb_key *wbk = शून्य;
	काष्ठा list_head *p;
	पूर्णांक ret = -ENOKEY, ret2;

	spin_lock(&vnode->wb_lock);
	अगर (*_wbk)
		p = (*_wbk)->vnode_link.next;
	अन्यथा
		p = vnode->wb_keys.next;

	जबतक (p != &vnode->wb_keys) अणु
		wbk = list_entry(p, काष्ठा afs_wb_key, vnode_link);
		_debug("wbk %u", key_serial(wbk->key));
		ret2 = key_validate(wbk->key);
		अगर (ret2 == 0) अणु
			refcount_inc(&wbk->usage);
			_debug("USE WB KEY %u", key_serial(wbk->key));
			अवरोध;
		पूर्ण

		wbk = शून्य;
		अगर (ret == -ENOKEY)
			ret = ret2;
		p = p->next;
	पूर्ण

	spin_unlock(&vnode->wb_lock);
	अगर (*_wbk)
		afs_put_wb_key(*_wbk);
	*_wbk = wbk;
	वापस 0;
पूर्ण

अटल व्योम afs_store_data_success(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode *vnode = op->file[0].vnode;

	op->स_समय = op->file[0].scb.status.mसमय_client;
	afs_vnode_commit_status(op, &op->file[0]);
	अगर (op->error == 0) अणु
		अगर (!op->store.laundering)
			afs_pages_written_back(vnode, op->store.pos, op->store.size);
		afs_stat_v(vnode, n_stores);
		atomic_दीर्घ_add(op->store.size, &afs_v2net(vnode)->n_store_bytes);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_store_data_operation = अणु
	.issue_afs_rpc	= afs_fs_store_data,
	.issue_yfs_rpc	= yfs_fs_store_data,
	.success	= afs_store_data_success,
पूर्ण;

/*
 * ग_लिखो to a file
 */
अटल पूर्णांक afs_store_data(काष्ठा afs_vnode *vnode, काष्ठा iov_iter *iter, loff_t pos,
			  bool laundering)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_wb_key *wbk = शून्य;
	loff_t size = iov_iter_count(iter), i_size;
	पूर्णांक ret = -ENOKEY;

	_enter("%s{%llx:%llu.%u},%llx,%llx",
	       vnode->volume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       size, pos);

	ret = afs_get_ग_लिखोback_key(vnode, &wbk);
	अगर (ret) अणु
		_leave(" = %d [no keys]", ret);
		वापस ret;
	पूर्ण

	op = afs_alloc_operation(wbk->key, vnode->volume);
	अगर (IS_ERR(op)) अणु
		afs_put_wb_key(wbk);
		वापस -ENOMEM;
	पूर्ण

	i_size = i_size_पढ़ो(&vnode->vfs_inode);

	afs_op_set_vnode(op, 0, vnode);
	op->file[0].dv_delta = 1;
	op->file[0].modअगरication = true;
	op->store.ग_लिखो_iter = iter;
	op->store.pos = pos;
	op->store.size = size;
	op->store.i_size = max(pos + size, i_size);
	op->store.laundering = laundering;
	op->mसमय = vnode->vfs_inode.i_mसमय;
	op->flags |= AFS_OPERATION_UNINTR;
	op->ops = &afs_store_data_operation;

try_next_key:
	afs_begin_vnode_operation(op);
	afs_रुको_क्रम_operation(op);

	चयन (op->error) अणु
	हाल -EACCES:
	हाल -EPERM:
	हाल -ENOKEY:
	हाल -EKEYEXPIRED:
	हाल -EKEYREJECTED:
	हाल -EKEYREVOKED:
		_debug("next");

		ret = afs_get_ग_लिखोback_key(vnode, &wbk);
		अगर (ret == 0) अणु
			key_put(op->key);
			op->key = key_get(wbk->key);
			जाओ try_next_key;
		पूर्ण
		अवरोध;
	पूर्ण

	afs_put_wb_key(wbk);
	_leave(" = %d", op->error);
	वापस afs_put_operation(op);
पूर्ण

/*
 * Extend the region to be written back to include subsequent contiguously
 * dirty pages अगर possible, but करोn't sleep जबतक करोing so.
 *
 * If this page holds new content, then we can include filler zeros in the
 * ग_लिखोback.
 */
अटल व्योम afs_extend_ग_लिखोback(काष्ठा address_space *mapping,
				 काष्ठा afs_vnode *vnode,
				 दीर्घ *_count,
				 loff_t start,
				 loff_t max_len,
				 bool new_content,
				 अचिन्हित पूर्णांक *_len)
अणु
	काष्ठा pagevec pvec;
	काष्ठा page *page;
	अचिन्हित दीर्घ priv;
	अचिन्हित पूर्णांक psize, filler = 0;
	अचिन्हित पूर्णांक f, t;
	loff_t len = *_len;
	pgoff_t index = (start + len) / PAGE_SIZE;
	bool stop = true;
	अचिन्हित पूर्णांक i;

	XA_STATE(xas, &mapping->i_pages, index);
	pagevec_init(&pvec);

	करो अणु
		/* Firstly, we gather up a batch of contiguous dirty pages
		 * under the RCU पढ़ो lock - but we can't clear the dirty flags
		 * there अगर any of those pages are mapped.
		 */
		rcu_पढ़ो_lock();

		xas_क्रम_each(&xas, page, अच_दीर्घ_उच्च) अणु
			stop = true;
			अगर (xas_retry(&xas, page))
				जारी;
			अगर (xa_is_value(page))
				अवरोध;
			अगर (page->index != index)
				अवरोध;

			अगर (!page_cache_get_speculative(page)) अणु
				xas_reset(&xas);
				जारी;
			पूर्ण

			/* Has the page moved or been split? */
			अगर (unlikely(page != xas_reload(&xas)))
				अवरोध;

			अगर (!trylock_page(page))
				अवरोध;
			अगर (!PageDirty(page) || PageWriteback(page)) अणु
				unlock_page(page);
				अवरोध;
			पूर्ण

			psize = thp_size(page);
			priv = page_निजी(page);
			f = afs_page_dirty_from(page, priv);
			t = afs_page_dirty_to(page, priv);
			अगर (f != 0 && !new_content) अणु
				unlock_page(page);
				अवरोध;
			पूर्ण

			len += filler + t;
			filler = psize - t;
			अगर (len >= max_len || *_count <= 0)
				stop = true;
			अन्यथा अगर (t == psize || new_content)
				stop = false;

			index += thp_nr_pages(page);
			अगर (!pagevec_add(&pvec, page))
				अवरोध;
			अगर (stop)
				अवरोध;
		पूर्ण

		अगर (!stop)
			xas_छोड़ो(&xas);
		rcu_पढ़ो_unlock();

		/* Now, अगर we obtained any pages, we can shअगरt them to being
		 * writable and mark them क्रम caching.
		 */
		अगर (!pagevec_count(&pvec))
			अवरोध;

		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			page = pvec.pages[i];
			trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("store+"), page);

			अगर (!clear_page_dirty_क्रम_io(page))
				BUG();
			अगर (test_set_page_ग_लिखोback(page))
				BUG();

			*_count -= thp_nr_pages(page);
			unlock_page(page);
		पूर्ण

		pagevec_release(&pvec);
		cond_resched();
	पूर्ण जबतक (!stop);

	*_len = len;
पूर्ण

/*
 * Synchronously ग_लिखो back the locked page and any subsequent non-locked dirty
 * pages.
 */
अटल sमाप_प्रकार afs_ग_लिखो_back_from_locked_page(काष्ठा address_space *mapping,
					       काष्ठा ग_लिखोback_control *wbc,
					       काष्ठा page *page,
					       loff_t start, loff_t end)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(mapping->host);
	काष्ठा iov_iter iter;
	अचिन्हित दीर्घ priv;
	अचिन्हित पूर्णांक offset, to, len, max_len;
	loff_t i_size = i_size_पढ़ो(&vnode->vfs_inode);
	bool new_content = test_bit(AFS_VNODE_NEW_CONTENT, &vnode->flags);
	दीर्घ count = wbc->nr_to_ग_लिखो;
	पूर्णांक ret;

	_enter(",%lx,%llx-%llx", page->index, start, end);

	अगर (test_set_page_ग_लिखोback(page))
		BUG();

	count -= thp_nr_pages(page);

	/* Find all consecutive lockable dirty pages that have contiguous
	 * written regions, stopping when we find a page that is not
	 * immediately lockable, is not dirty or is missing, or we reach the
	 * end of the range.
	 */
	priv = page_निजी(page);
	offset = afs_page_dirty_from(page, priv);
	to = afs_page_dirty_to(page, priv);
	trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("store"), page);

	len = to - offset;
	start += offset;
	अगर (start < i_size) अणु
		/* Trim the ग_लिखो to the खातापूर्ण; the extra data is ignored.  Also
		 * put an upper limit on the size of a single storedata op.
		 */
		max_len = 65536 * 4096;
		max_len = min_t(अचिन्हित दीर्घ दीर्घ, max_len, end - start + 1);
		max_len = min_t(अचिन्हित दीर्घ दीर्घ, max_len, i_size - start);

		अगर (len < max_len &&
		    (to == thp_size(page) || new_content))
			afs_extend_ग_लिखोback(mapping, vnode, &count,
					     start, max_len, new_content, &len);
		len = min_t(loff_t, len, max_len);
	पूर्ण

	/* We now have a contiguous set of dirty pages, each with ग_लिखोback
	 * set; the first page is still locked at this poपूर्णांक, but all the rest
	 * have been unlocked.
	 */
	unlock_page(page);

	अगर (start < i_size) अणु
		_debug("write back %x @%llx [%llx]", len, start, i_size);

		iov_iter_xarray(&iter, WRITE, &mapping->i_pages, start, len);
		ret = afs_store_data(vnode, &iter, start, false);
	पूर्ण अन्यथा अणु
		_debug("write discard %x @%llx [%llx]", len, start, i_size);

		/* The dirty region was entirely beyond the खातापूर्ण. */
		afs_pages_written_back(vnode, start, len);
		ret = 0;
	पूर्ण

	चयन (ret) अणु
	हाल 0:
		wbc->nr_to_ग_लिखो = count;
		ret = len;
		अवरोध;

	शेष:
		pr_notice("kAFS: Unexpected error from FS.StoreData %d\n", ret);
		fallthrough;
	हाल -EACCES:
	हाल -EPERM:
	हाल -ENOKEY:
	हाल -EKEYEXPIRED:
	हाल -EKEYREJECTED:
	हाल -EKEYREVOKED:
		afs_redirty_pages(wbc, mapping, start, len);
		mapping_set_error(mapping, ret);
		अवरोध;

	हाल -EDQUOT:
	हाल -ENOSPC:
		afs_redirty_pages(wbc, mapping, start, len);
		mapping_set_error(mapping, -ENOSPC);
		अवरोध;

	हाल -EROFS:
	हाल -EIO:
	हाल -EREMOTEIO:
	हाल -EFBIG:
	हाल -ENOENT:
	हाल -ENOMEDIUM:
	हाल -ENXIO:
		trace_afs_file_error(vnode, ret, afs_file_error_ग_लिखोback_fail);
		afs_समाप्त_pages(mapping, start, len);
		mapping_set_error(mapping, ret);
		अवरोध;
	पूर्ण

	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * ग_लिखो a page back to the server
 * - the caller locked the page क्रम us
 */
पूर्णांक afs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	sमाप_प्रकार ret;
	loff_t start;

	_enter("{%lx},", page->index);

	start = page->index * PAGE_SIZE;
	ret = afs_ग_लिखो_back_from_locked_page(page->mapping, wbc, page,
					      start, Lदीर्घ_उच्च - start);
	अगर (ret < 0) अणु
		_leave(" = %zd", ret);
		वापस ret;
	पूर्ण

	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * ग_लिखो a region of pages back to the server
 */
अटल पूर्णांक afs_ग_लिखोpages_region(काष्ठा address_space *mapping,
				 काष्ठा ग_लिखोback_control *wbc,
				 loff_t start, loff_t end, loff_t *_next)
अणु
	काष्ठा page *page;
	sमाप_प्रकार ret;
	पूर्णांक n;

	_enter("%llx,%llx,", start, end);

	करो अणु
		pgoff_t index = start / PAGE_SIZE;

		n = find_get_pages_range_tag(mapping, &index, end / PAGE_SIZE,
					     PAGECACHE_TAG_सूचीTY, 1, &page);
		अगर (!n)
			अवरोध;

		start = (loff_t)page->index * PAGE_SIZE; /* May regress with THPs */

		_debug("wback %lx", page->index);

		/* At this poपूर्णांक we hold neither the i_pages lock nor the
		 * page lock: the page may be truncated or invalidated
		 * (changing page->mapping to शून्य), or even swizzled
		 * back from swapper_space to पंचांगpfs file mapping
		 */
		अगर (wbc->sync_mode != WB_SYNC_NONE) अणु
			ret = lock_page_समाप्तable(page);
			अगर (ret < 0) अणु
				put_page(page);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!trylock_page(page)) अणु
				put_page(page);
				वापस 0;
			पूर्ण
		पूर्ण

		अगर (page->mapping != mapping || !PageDirty(page)) अणु
			start += thp_size(page);
			unlock_page(page);
			put_page(page);
			जारी;
		पूर्ण

		अगर (PageWriteback(page)) अणु
			unlock_page(page);
			अगर (wbc->sync_mode != WB_SYNC_NONE)
				रुको_on_page_ग_लिखोback(page);
			put_page(page);
			जारी;
		पूर्ण

		अगर (!clear_page_dirty_क्रम_io(page))
			BUG();
		ret = afs_ग_लिखो_back_from_locked_page(mapping, wbc, page, start, end);
		put_page(page);
		अगर (ret < 0) अणु
			_leave(" = %zd", ret);
			वापस ret;
		पूर्ण

		start += ret;

		cond_resched();
	पूर्ण जबतक (wbc->nr_to_ग_लिखो > 0);

	*_next = start;
	_leave(" = 0 [%llx]", *_next);
	वापस 0;
पूर्ण

/*
 * ग_लिखो some of the pending data back to the server
 */
पूर्णांक afs_ग_लिखोpages(काष्ठा address_space *mapping,
		   काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(mapping->host);
	loff_t start, next;
	पूर्णांक ret;

	_enter("");

	/* We have to be careful as we can end up racing with setattr()
	 * truncating the pagecache since the caller करोesn't take a lock here
	 * to prevent it.
	 */
	अगर (wbc->sync_mode == WB_SYNC_ALL)
		करोwn_पढ़ो(&vnode->validate_lock);
	अन्यथा अगर (!करोwn_पढ़ो_trylock(&vnode->validate_lock))
		वापस 0;

	अगर (wbc->range_cyclic) अणु
		start = mapping->ग_लिखोback_index * PAGE_SIZE;
		ret = afs_ग_लिखोpages_region(mapping, wbc, start, Lदीर्घ_उच्च, &next);
		अगर (start > 0 && wbc->nr_to_ग_लिखो > 0 && ret == 0)
			ret = afs_ग_लिखोpages_region(mapping, wbc, 0, start,
						    &next);
		mapping->ग_लिखोback_index = next / PAGE_SIZE;
	पूर्ण अन्यथा अगर (wbc->range_start == 0 && wbc->range_end == Lदीर्घ_उच्च) अणु
		ret = afs_ग_लिखोpages_region(mapping, wbc, 0, Lदीर्घ_उच्च, &next);
		अगर (wbc->nr_to_ग_लिखो > 0)
			mapping->ग_लिखोback_index = next;
	पूर्ण अन्यथा अणु
		ret = afs_ग_लिखोpages_region(mapping, wbc,
					    wbc->range_start, wbc->range_end, &next);
	पूर्ण

	up_पढ़ो(&vnode->validate_lock);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * ग_लिखो to an AFS file
 */
sमाप_प्रकार afs_file_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(file_inode(iocb->ki_filp));
	sमाप_प्रकार result;
	माप_प्रकार count = iov_iter_count(from);

	_enter("{%llx:%llu},{%zu},",
	       vnode->fid.vid, vnode->fid.vnode, count);

	अगर (IS_SWAPखाता(&vnode->vfs_inode)) अणु
		prपूर्णांकk(KERN_INFO
		       "AFS: Attempt to write to active swap file!\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!count)
		वापस 0;

	result = generic_file_ग_लिखो_iter(iocb, from);

	_leave(" = %zd", result);
	वापस result;
पूर्ण

/*
 * flush any dirty pages क्रम this process, and check क्रम ग_लिखो errors.
 * - the वापस status from this call provides a reliable indication of
 *   whether any ग_लिखो errors occurred क्रम this process.
 */
पूर्णांक afs_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);

	_enter("{%llx:%llu},{n=%pD},%d",
	       vnode->fid.vid, vnode->fid.vnode, file,
	       datasync);

	वापस file_ग_लिखो_and_रुको_range(file, start, end);
पूर्ण

/*
 * notअगरication that a previously पढ़ो-only page is about to become writable
 * - अगर it वापसs an error, the caller will deliver a bus error संकेत
 */
vm_fault_t afs_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page = thp_head(vmf->page);
	काष्ठा file *file = vmf->vma->vm_file;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	अचिन्हित दीर्घ priv;
	vm_fault_t ret = VM_FAULT_RETRY;

	_enter("{{%llx:%llu}},{%lx}", vnode->fid.vid, vnode->fid.vnode, page->index);

	sb_start_pagefault(inode->i_sb);

	/* Wait क्रम the page to be written to the cache beक्रमe we allow it to
	 * be modअगरied.  We then assume the entire page will need writing back.
	 */
#अगर_घोषित CONFIG_AFS_FSCACHE
	अगर (PageFsCache(page) &&
	    रुको_on_page_fscache_समाप्तable(page) < 0)
		जाओ out;
#पूर्ण_अगर

	अगर (रुको_on_page_ग_लिखोback_समाप्तable(page))
		जाओ out;

	अगर (lock_page_समाप्तable(page) < 0)
		जाओ out;

	/* We mustn't change page->निजी until ग_लिखोback is complete as that
	 * details the portion of the page we need to ग_लिखो back and we might
	 * need to redirty the page अगर there's a problem.
	 */
	अगर (रुको_on_page_ग_लिखोback_समाप्तable(page) < 0) अणु
		unlock_page(page);
		जाओ out;
	पूर्ण

	priv = afs_page_dirty(page, 0, thp_size(page));
	priv = afs_page_dirty_mmapped(priv);
	अगर (PagePrivate(page)) अणु
		set_page_निजी(page, priv);
		trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("mkwrite+"), page);
	पूर्ण अन्यथा अणु
		attach_page_निजी(page, (व्योम *)priv);
		trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("mkwrite"), page);
	पूर्ण
	file_update_समय(file);

	ret = VM_FAULT_LOCKED;
out:
	sb_end_pagefault(inode->i_sb);
	वापस ret;
पूर्ण

/*
 * Prune the keys cached क्रम ग_लिखोback.  The caller must hold vnode->wb_lock.
 */
व्योम afs_prune_wb_keys(काष्ठा afs_vnode *vnode)
अणु
	LIST_HEAD(graveyard);
	काष्ठा afs_wb_key *wbk, *पंचांगp;

	/* Discard unused keys */
	spin_lock(&vnode->wb_lock);

	अगर (!mapping_tagged(&vnode->vfs_inode.i_data, PAGECACHE_TAG_WRITEBACK) &&
	    !mapping_tagged(&vnode->vfs_inode.i_data, PAGECACHE_TAG_सूचीTY)) अणु
		list_क्रम_each_entry_safe(wbk, पंचांगp, &vnode->wb_keys, vnode_link) अणु
			अगर (refcount_पढ़ो(&wbk->usage) == 1)
				list_move(&wbk->vnode_link, &graveyard);
		पूर्ण
	पूर्ण

	spin_unlock(&vnode->wb_lock);

	जबतक (!list_empty(&graveyard)) अणु
		wbk = list_entry(graveyard.next, काष्ठा afs_wb_key, vnode_link);
		list_del(&wbk->vnode_link);
		afs_put_wb_key(wbk);
	पूर्ण
पूर्ण

/*
 * Clean up a page during invalidation.
 */
पूर्णांक afs_launder_page(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा afs_vnode *vnode = AFS_FS_I(mapping->host);
	काष्ठा iov_iter iter;
	काष्ठा bio_vec bv[1];
	अचिन्हित दीर्घ priv;
	अचिन्हित पूर्णांक f, t;
	पूर्णांक ret = 0;

	_enter("{%lx}", page->index);

	priv = page_निजी(page);
	अगर (clear_page_dirty_क्रम_io(page)) अणु
		f = 0;
		t = thp_size(page);
		अगर (PagePrivate(page)) अणु
			f = afs_page_dirty_from(page, priv);
			t = afs_page_dirty_to(page, priv);
		पूर्ण

		bv[0].bv_page = page;
		bv[0].bv_offset = f;
		bv[0].bv_len = t - f;
		iov_iter_bvec(&iter, WRITE, bv, 1, bv[0].bv_len);

		trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("launder"), page);
		ret = afs_store_data(vnode, &iter, (loff_t)page->index * PAGE_SIZE,
				     true);
	पूर्ण

	trace_afs_page_dirty(vnode, tracepoपूर्णांक_string("laundered"), page);
	detach_page_निजी(page);
	रुको_on_page_fscache(page);
	वापस ret;
पूर्ण
