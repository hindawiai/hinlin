<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/9p/vfs_addr.c
 *
 * This file contians vfs address (mmap) ops क्रम 9P2000.
 *
 *  Copyright (C) 2005 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/inet.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/idr.h>
#समावेश <linux/sched.h>
#समावेश <linux/uपन.स>
#समावेश <linux/bvec.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>

#समावेश "v9fs.h"
#समावेश "v9fs_vfs.h"
#समावेश "cache.h"
#समावेश "fid.h"

/**
 * v9fs_fid_पढ़ोpage - पढ़ो an entire page in from 9P
 *
 * @fid: fid being पढ़ो
 * @page: काष्ठाure to page
 *
 */
अटल पूर्णांक v9fs_fid_पढ़ोpage(व्योम *data, काष्ठा page *page)
अणु
	काष्ठा p9_fid *fid = data;
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा bio_vec bvec = अणु.bv_page = page, .bv_len = PAGE_SIZEपूर्ण;
	काष्ठा iov_iter to;
	पूर्णांक retval, err;

	p9_debug(P9_DEBUG_VFS, "\n");

	BUG_ON(!PageLocked(page));

	retval = v9fs_पढ़ोpage_from_fscache(inode, page);
	अगर (retval == 0)
		वापस retval;

	iov_iter_bvec(&to, READ, &bvec, 1, PAGE_SIZE);

	retval = p9_client_पढ़ो(fid, page_offset(page), &to, &err);
	अगर (err) अणु
		v9fs_uncache_page(inode, page);
		retval = err;
		जाओ करोne;
	पूर्ण

	zero_user(page, retval, PAGE_SIZE - retval);
	flush_dcache_page(page);
	SetPageUptodate(page);

	v9fs_पढ़ोpage_to_fscache(inode, page);
	retval = 0;

करोne:
	unlock_page(page);
	वापस retval;
पूर्ण

/**
 * v9fs_vfs_पढ़ोpage - पढ़ो an entire page in from 9P
 *
 * @filp: file being पढ़ो
 * @page: काष्ठाure to page
 *
 */

अटल पूर्णांक v9fs_vfs_पढ़ोpage(काष्ठा file *filp, काष्ठा page *page)
अणु
	वापस v9fs_fid_पढ़ोpage(filp->निजी_data, page);
पूर्ण

/**
 * v9fs_vfs_पढ़ोpages - पढ़ो a set of pages from 9P
 *
 * @filp: file being पढ़ो
 * @mapping: the address space
 * @pages: list of pages to पढ़ो
 * @nr_pages: count of pages to पढ़ो
 *
 */

अटल पूर्णांक v9fs_vfs_पढ़ोpages(काष्ठा file *filp, काष्ठा address_space *mapping,
			     काष्ठा list_head *pages, अचिन्हित nr_pages)
अणु
	पूर्णांक ret = 0;
	काष्ठा inode *inode;

	inode = mapping->host;
	p9_debug(P9_DEBUG_VFS, "inode: %p file: %p\n", inode, filp);

	ret = v9fs_पढ़ोpages_from_fscache(inode, mapping, pages, &nr_pages);
	अगर (ret == 0)
		वापस ret;

	ret = पढ़ो_cache_pages(mapping, pages, v9fs_fid_पढ़ोpage,
			filp->निजी_data);
	p9_debug(P9_DEBUG_VFS, "  = %d\n", ret);
	वापस ret;
पूर्ण

/**
 * v9fs_release_page - release the निजी state associated with a page
 *
 * Returns 1 अगर the page can be released, false otherwise.
 */

अटल पूर्णांक v9fs_release_page(काष्ठा page *page, gfp_t gfp)
अणु
	अगर (PagePrivate(page))
		वापस 0;
	वापस v9fs_fscache_release_page(page, gfp);
पूर्ण

/**
 * v9fs_invalidate_page - Invalidate a page completely or partially
 *
 * @page: काष्ठाure to page
 * @offset: offset in the page
 */

अटल व्योम v9fs_invalidate_page(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				 अचिन्हित पूर्णांक length)
अणु
	/*
	 * If called with zero offset, we should release
	 * the निजी state assocated with the page
	 */
	अगर (offset == 0 && length == PAGE_SIZE)
		v9fs_fscache_invalidate_page(page);
पूर्ण

अटल पूर्णांक v9fs_vfs_ग_लिखोpage_locked(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा v9fs_inode *v9inode = V9FS_I(inode);
	loff_t size = i_size_पढ़ो(inode);
	काष्ठा iov_iter from;
	काष्ठा bio_vec bvec;
	पूर्णांक err, len;

	अगर (page->index == size >> PAGE_SHIFT)
		len = size & ~PAGE_MASK;
	अन्यथा
		len = PAGE_SIZE;

	bvec.bv_page = page;
	bvec.bv_offset = 0;
	bvec.bv_len = len;
	iov_iter_bvec(&from, WRITE, &bvec, 1, len);

	/* We should have ग_लिखोback_fid always set */
	BUG_ON(!v9inode->ग_लिखोback_fid);

	set_page_ग_लिखोback(page);

	p9_client_ग_लिखो(v9inode->ग_लिखोback_fid, page_offset(page), &from, &err);

	end_page_ग_लिखोback(page);
	वापस err;
पूर्ण

अटल पूर्णांक v9fs_vfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक retval;

	p9_debug(P9_DEBUG_VFS, "page %p\n", page);

	retval = v9fs_vfs_ग_लिखोpage_locked(page);
	अगर (retval < 0) अणु
		अगर (retval == -EAGAIN) अणु
			redirty_page_क्रम_ग_लिखोpage(wbc, page);
			retval = 0;
		पूर्ण अन्यथा अणु
			SetPageError(page);
			mapping_set_error(page->mapping, retval);
		पूर्ण
	पूर्ण अन्यथा
		retval = 0;

	unlock_page(page);
	वापस retval;
पूर्ण

/**
 * v9fs_launder_page - Writeback a dirty page
 * Returns 0 on success.
 */

अटल पूर्णांक v9fs_launder_page(काष्ठा page *page)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode = page->mapping->host;

	v9fs_fscache_रुको_on_page_ग_लिखो(inode, page);
	अगर (clear_page_dirty_क्रम_io(page)) अणु
		retval = v9fs_vfs_ग_लिखोpage_locked(page);
		अगर (retval)
			वापस retval;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * v9fs_direct_IO - 9P address space operation क्रम direct I/O
 * @iocb: target I/O control block
 *
 * The presence of v9fs_direct_IO() in the address space ops vector
 * allowes खोलो() O_सूचीECT flags which would have failed otherwise.
 *
 * In the non-cached mode, we shunt off direct पढ़ो and ग_लिखो requests beक्रमe
 * the VFS माला_लो them, so this method should never be called.
 *
 * Direct IO is not 'yet' supported in the cached mode. Hence when
 * this routine is called through generic_file_aio_पढ़ो(), the पढ़ो/ग_लिखो fails
 * with an error.
 *
 */
अटल sमाप_प्रकार
v9fs_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	loff_t pos = iocb->ki_pos;
	sमाप_प्रकार n;
	पूर्णांक err = 0;
	अगर (iov_iter_rw(iter) == WRITE) अणु
		n = p9_client_ग_लिखो(file->निजी_data, pos, iter, &err);
		अगर (n) अणु
			काष्ठा inode *inode = file_inode(file);
			loff_t i_size = i_size_पढ़ो(inode);
			अगर (pos + n > i_size)
				inode_add_bytes(inode, pos + n - i_size);
		पूर्ण
	पूर्ण अन्यथा अणु
		n = p9_client_पढ़ो(file->निजी_data, pos, iter, &err);
	पूर्ण
	वापस n ? n : err;
पूर्ण

अटल पूर्णांक v9fs_ग_लिखो_begin(काष्ठा file *filp, काष्ठा address_space *mapping,
			    loff_t pos, अचिन्हित len, अचिन्हित flags,
			    काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक retval = 0;
	काष्ठा page *page;
	काष्ठा v9fs_inode *v9inode;
	pgoff_t index = pos >> PAGE_SHIFT;
	काष्ठा inode *inode = mapping->host;


	p9_debug(P9_DEBUG_VFS, "filp %p, mapping %p\n", filp, mapping);

	v9inode = V9FS_I(inode);
start:
	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page) अणु
		retval = -ENOMEM;
		जाओ out;
	पूर्ण
	BUG_ON(!v9inode->ग_लिखोback_fid);
	अगर (PageUptodate(page))
		जाओ out;

	अगर (len == PAGE_SIZE)
		जाओ out;

	retval = v9fs_fid_पढ़ोpage(v9inode->ग_लिखोback_fid, page);
	put_page(page);
	अगर (!retval)
		जाओ start;
out:
	*pagep = page;
	वापस retval;
पूर्ण

अटल पूर्णांक v9fs_ग_लिखो_end(काष्ठा file *filp, काष्ठा address_space *mapping,
			  loff_t pos, अचिन्हित len, अचिन्हित copied,
			  काष्ठा page *page, व्योम *fsdata)
अणु
	loff_t last_pos = pos + copied;
	काष्ठा inode *inode = page->mapping->host;

	p9_debug(P9_DEBUG_VFS, "filp %p, mapping %p\n", filp, mapping);

	अगर (!PageUptodate(page)) अणु
		अगर (unlikely(copied < len)) अणु
			copied = 0;
			जाओ out;
		पूर्ण अन्यथा अगर (len == PAGE_SIZE) अणु
			SetPageUptodate(page);
		पूर्ण
	पूर्ण
	/*
	 * No need to use i_size_पढ़ो() here, the i_size
	 * cannot change under us because we hold the i_mutex.
	 */
	अगर (last_pos > inode->i_size) अणु
		inode_add_bytes(inode, last_pos - inode->i_size);
		i_size_ग_लिखो(inode, last_pos);
	पूर्ण
	set_page_dirty(page);
out:
	unlock_page(page);
	put_page(page);

	वापस copied;
पूर्ण


स्थिर काष्ठा address_space_operations v9fs_addr_operations = अणु
	.पढ़ोpage = v9fs_vfs_पढ़ोpage,
	.पढ़ोpages = v9fs_vfs_पढ़ोpages,
	.set_page_dirty = __set_page_dirty_nobuffers,
	.ग_लिखोpage = v9fs_vfs_ग_लिखोpage,
	.ग_लिखो_begin = v9fs_ग_लिखो_begin,
	.ग_लिखो_end = v9fs_ग_लिखो_end,
	.releasepage = v9fs_release_page,
	.invalidatepage = v9fs_invalidate_page,
	.launder_page = v9fs_launder_page,
	.direct_IO = v9fs_direct_IO,
पूर्ण;
