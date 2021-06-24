<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 * Copyright 2018 Omnibond Systems, L.L.C.
 *
 * See COPYING in top-level directory.
 */

/*
 *  Linux VFS inode operations.
 */

#समावेश <linux/bvec.h>
#समावेश <linux/fileattr.h>
#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-bufmap.h"

अटल पूर्णांक orangefs_ग_लिखोpage_locked(काष्ठा page *page,
    काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा orangefs_ग_लिखो_range *wr = शून्य;
	काष्ठा iov_iter iter;
	काष्ठा bio_vec bv;
	माप_प्रकार len, wlen;
	sमाप_प्रकार ret;
	loff_t off;

	set_page_ग_लिखोback(page);

	len = i_size_पढ़ो(inode);
	अगर (PagePrivate(page)) अणु
		wr = (काष्ठा orangefs_ग_लिखो_range *)page_निजी(page);
		WARN_ON(wr->pos >= len);
		off = wr->pos;
		अगर (off + wr->len > len)
			wlen = len - off;
		अन्यथा
			wlen = wr->len;
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		off = page_offset(page);
		अगर (off + PAGE_SIZE > len)
			wlen = len - off;
		अन्यथा
			wlen = PAGE_SIZE;
	पूर्ण
	/* Should've been handled in orangefs_invalidatepage. */
	WARN_ON(off == len || off + wlen > len);

	bv.bv_page = page;
	bv.bv_len = wlen;
	bv.bv_offset = off % PAGE_SIZE;
	WARN_ON(wlen == 0);
	iov_iter_bvec(&iter, WRITE, &bv, 1, wlen);

	ret = रुको_क्रम_direct_io(ORANGEFS_IO_WRITE, inode, &off, &iter, wlen,
	    len, wr, शून्य, शून्य);
	अगर (ret < 0) अणु
		SetPageError(page);
		mapping_set_error(page->mapping, ret);
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण
	kमुक्त(detach_page_निजी(page));
	वापस ret;
पूर्ण

अटल पूर्णांक orangefs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret;
	ret = orangefs_ग_लिखोpage_locked(page, wbc);
	unlock_page(page);
	end_page_ग_लिखोback(page);
	वापस ret;
पूर्ण

काष्ठा orangefs_ग_लिखोpages अणु
	loff_t off;
	माप_प्रकार len;
	kuid_t uid;
	kgid_t gid;
	पूर्णांक maxpages;
	पूर्णांक npages;
	काष्ठा page **pages;
	काष्ठा bio_vec *bv;
पूर्ण;

अटल पूर्णांक orangefs_ग_लिखोpages_work(काष्ठा orangefs_ग_लिखोpages *ow,
    काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = ow->pages[0]->mapping->host;
	काष्ठा orangefs_ग_लिखो_range *wrp, wr;
	काष्ठा iov_iter iter;
	sमाप_प्रकार ret;
	माप_प्रकार len;
	loff_t off;
	पूर्णांक i;

	len = i_size_पढ़ो(inode);

	क्रम (i = 0; i < ow->npages; i++) अणु
		set_page_ग_लिखोback(ow->pages[i]);
		ow->bv[i].bv_page = ow->pages[i];
		ow->bv[i].bv_len = min(page_offset(ow->pages[i]) + PAGE_SIZE,
		    ow->off + ow->len) -
		    max(ow->off, page_offset(ow->pages[i]));
		अगर (i == 0)
			ow->bv[i].bv_offset = ow->off -
			    page_offset(ow->pages[i]);
		अन्यथा
			ow->bv[i].bv_offset = 0;
	पूर्ण
	iov_iter_bvec(&iter, WRITE, ow->bv, ow->npages, ow->len);

	WARN_ON(ow->off >= len);
	अगर (ow->off + ow->len > len)
		ow->len = len - ow->off;

	off = ow->off;
	wr.uid = ow->uid;
	wr.gid = ow->gid;
	ret = रुको_क्रम_direct_io(ORANGEFS_IO_WRITE, inode, &off, &iter, ow->len,
	    0, &wr, शून्य, शून्य);
	अगर (ret < 0) अणु
		क्रम (i = 0; i < ow->npages; i++) अणु
			SetPageError(ow->pages[i]);
			mapping_set_error(ow->pages[i]->mapping, ret);
			अगर (PagePrivate(ow->pages[i])) अणु
				wrp = (काष्ठा orangefs_ग_लिखो_range *)
				    page_निजी(ow->pages[i]);
				ClearPagePrivate(ow->pages[i]);
				put_page(ow->pages[i]);
				kमुक्त(wrp);
			पूर्ण
			end_page_ग_लिखोback(ow->pages[i]);
			unlock_page(ow->pages[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = 0;
		क्रम (i = 0; i < ow->npages; i++) अणु
			अगर (PagePrivate(ow->pages[i])) अणु
				wrp = (काष्ठा orangefs_ग_लिखो_range *)
				    page_निजी(ow->pages[i]);
				ClearPagePrivate(ow->pages[i]);
				put_page(ow->pages[i]);
				kमुक्त(wrp);
			पूर्ण
			end_page_ग_लिखोback(ow->pages[i]);
			unlock_page(ow->pages[i]);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक orangefs_ग_लिखोpages_callback(काष्ठा page *page,
    काष्ठा ग_लिखोback_control *wbc, व्योम *data)
अणु
	काष्ठा orangefs_ग_लिखोpages *ow = data;
	काष्ठा orangefs_ग_लिखो_range *wr;
	पूर्णांक ret;

	अगर (!PagePrivate(page)) अणु
		unlock_page(page);
		/* It's not private so there's nothing to ग_लिखो, right? */
		prपूर्णांकk("writepages_callback not private!\n");
		BUG();
		वापस 0;
	पूर्ण
	wr = (काष्ठा orangefs_ग_लिखो_range *)page_निजी(page);

	ret = -1;
	अगर (ow->npages == 0) अणु
		ow->off = wr->pos;
		ow->len = wr->len;
		ow->uid = wr->uid;
		ow->gid = wr->gid;
		ow->pages[ow->npages++] = page;
		ret = 0;
		जाओ करोne;
	पूर्ण
	अगर (!uid_eq(ow->uid, wr->uid) || !gid_eq(ow->gid, wr->gid)) अणु
		orangefs_ग_लिखोpages_work(ow, wbc);
		ow->npages = 0;
		ret = -1;
		जाओ करोne;
	पूर्ण
	अगर (ow->off + ow->len == wr->pos) अणु
		ow->len += wr->len;
		ow->pages[ow->npages++] = page;
		ret = 0;
		जाओ करोne;
	पूर्ण
करोne:
	अगर (ret == -1) अणु
		अगर (ow->npages) अणु
			orangefs_ग_लिखोpages_work(ow, wbc);
			ow->npages = 0;
		पूर्ण
		ret = orangefs_ग_लिखोpage_locked(page, wbc);
		mapping_set_error(page->mapping, ret);
		unlock_page(page);
		end_page_ग_लिखोback(page);
	पूर्ण अन्यथा अणु
		अगर (ow->npages == ow->maxpages) अणु
			orangefs_ग_लिखोpages_work(ow, wbc);
			ow->npages = 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक orangefs_ग_लिखोpages(काष्ठा address_space *mapping,
    काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा orangefs_ग_लिखोpages *ow;
	काष्ठा blk_plug plug;
	पूर्णांक ret;
	ow = kzalloc(माप(काष्ठा orangefs_ग_लिखोpages), GFP_KERNEL);
	अगर (!ow)
		वापस -ENOMEM;
	ow->maxpages = orangefs_bufmap_size_query()/PAGE_SIZE;
	ow->pages = kसुस्मृति(ow->maxpages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!ow->pages) अणु
		kमुक्त(ow);
		वापस -ENOMEM;
	पूर्ण
	ow->bv = kसुस्मृति(ow->maxpages, माप(काष्ठा bio_vec), GFP_KERNEL);
	अगर (!ow->bv) अणु
		kमुक्त(ow->pages);
		kमुक्त(ow);
		वापस -ENOMEM;
	पूर्ण
	blk_start_plug(&plug);
	ret = ग_लिखो_cache_pages(mapping, wbc, orangefs_ग_लिखोpages_callback, ow);
	अगर (ow->npages)
		ret = orangefs_ग_लिखोpages_work(ow, wbc);
	blk_finish_plug(&plug);
	kमुक्त(ow->pages);
	kमुक्त(ow->bv);
	kमुक्त(ow);
	वापस ret;
पूर्ण

अटल पूर्णांक orangefs_launder_page(काष्ठा page *);

अटल व्योम orangefs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	loff_t offset;
	काष्ठा iov_iter iter;
	काष्ठा file *file = rac->file;
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा xarray *i_pages;
	काष्ठा page *page;
	loff_t new_start = पढ़ोahead_pos(rac);
	पूर्णांक ret;
	माप_प्रकार new_len = 0;

	loff_t bytes_reमुख्यing = inode->i_size - पढ़ोahead_pos(rac);
	loff_t pages_reमुख्यing = bytes_reमुख्यing / PAGE_SIZE;

	अगर (pages_reमुख्यing >= 1024)
		new_len = 4194304;
	अन्यथा अगर (pages_reमुख्यing > पढ़ोahead_count(rac))
		new_len = bytes_reमुख्यing;

	अगर (new_len)
		पढ़ोahead_expand(rac, new_start, new_len);

	offset = पढ़ोahead_pos(rac);
	i_pages = &file->f_mapping->i_pages;

	iov_iter_xarray(&iter, READ, i_pages, offset, पढ़ोahead_length(rac));

	/* पढ़ो in the pages. */
	अगर ((ret = रुको_क्रम_direct_io(ORANGEFS_IO_READ, inode,
			&offset, &iter, पढ़ोahead_length(rac),
			inode->i_size, शून्य, शून्य, file)) < 0)
		gossip_debug(GOSSIP_खाता_DEBUG,
			"%s: wait_for_direct_io failed. \n", __func__);
	अन्यथा
		ret = 0;

	/* clean up. */
	जबतक ((page = पढ़ोahead_page(rac))) अणु
		page_endio(page, false, ret);
		put_page(page);
	पूर्ण
पूर्ण

अटल पूर्णांक orangefs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा iov_iter iter;
	काष्ठा bio_vec bv;
	sमाप_प्रकार ret;
	loff_t off; /* offset पूर्णांकo this page */

	अगर (PageDirty(page))
		orangefs_launder_page(page);

	off = page_offset(page);
	bv.bv_page = page;
	bv.bv_len = PAGE_SIZE;
	bv.bv_offset = 0;
	iov_iter_bvec(&iter, READ, &bv, 1, PAGE_SIZE);

	ret = रुको_क्रम_direct_io(ORANGEFS_IO_READ, inode, &off, &iter,
	    PAGE_SIZE, inode->i_size, शून्य, शून्य, file);
	/* this will only zero reमुख्यing unपढ़ो portions of the page data */
	iov_iter_zero(~0U, &iter);
	/* takes care of potential aliasing */
	flush_dcache_page(page);
	अगर (ret < 0) अणु
		SetPageError(page);
	पूर्ण अन्यथा अणु
		SetPageUptodate(page);
		अगर (PageError(page))
			ClearPageError(page);
		ret = 0;
	पूर्ण
	/* unlock the page after the ->पढ़ोpage() routine completes */
	unlock_page(page);
        वापस ret;
पूर्ण

अटल पूर्णांक orangefs_ग_लिखो_begin(काष्ठा file *file,
    काष्ठा address_space *mapping,
    loff_t pos, अचिन्हित len, अचिन्हित flags, काष्ठा page **pagep,
    व्योम **fsdata)
अणु
	काष्ठा orangefs_ग_लिखो_range *wr;
	काष्ठा page *page;
	pgoff_t index;
	पूर्णांक ret;

	index = pos >> PAGE_SHIFT;

	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;

	*pagep = page;

	अगर (PageDirty(page) && !PagePrivate(page)) अणु
		/*
		 * Should be impossible.  If it happens, launder the page
		 * since we करोn't know what's dirty.  This will WARN in
		 * orangefs_ग_लिखोpage_locked.
		 */
		ret = orangefs_launder_page(page);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (PagePrivate(page)) अणु
		काष्ठा orangefs_ग_लिखो_range *wr;
		wr = (काष्ठा orangefs_ग_लिखो_range *)page_निजी(page);
		अगर (wr->pos + wr->len == pos &&
		    uid_eq(wr->uid, current_fsuid()) &&
		    gid_eq(wr->gid, current_fsgid())) अणु
			wr->len += len;
			जाओ okay;
		पूर्ण अन्यथा अणु
			ret = orangefs_launder_page(page);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	wr = kदो_स्मृति(माप *wr, GFP_KERNEL);
	अगर (!wr)
		वापस -ENOMEM;

	wr->pos = pos;
	wr->len = len;
	wr->uid = current_fsuid();
	wr->gid = current_fsgid();
	attach_page_निजी(page, wr);
okay:
	वापस 0;
पूर्ण

अटल पूर्णांक orangefs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
    loff_t pos, अचिन्हित len, अचिन्हित copied, काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = page->mapping->host;
	loff_t last_pos = pos + copied;

	/*
	 * No need to use i_size_पढ़ो() here, the i_size
	 * cannot change under us because we hold the i_mutex.
	 */
	अगर (last_pos > inode->i_size)
		i_size_ग_लिखो(inode, last_pos);

	/* zero the stale part of the page अगर we did a लघु copy */
	अगर (!PageUptodate(page)) अणु
		अचिन्हित from = pos & (PAGE_SIZE - 1);
		अगर (copied < len) अणु
			zero_user(page, from + copied, len - copied);
		पूर्ण
		/* Set fully written pages uptodate. */
		अगर (pos == page_offset(page) &&
		    (len == PAGE_SIZE || pos + len == inode->i_size)) अणु
			zero_user_segment(page, from + copied, PAGE_SIZE);
			SetPageUptodate(page);
		पूर्ण
	पूर्ण

	set_page_dirty(page);
	unlock_page(page);
	put_page(page);

	mark_inode_dirty_sync(file_inode(file));
	वापस copied;
पूर्ण

अटल व्योम orangefs_invalidatepage(काष्ठा page *page,
				 अचिन्हित पूर्णांक offset,
				 अचिन्हित पूर्णांक length)
अणु
	काष्ठा orangefs_ग_लिखो_range *wr;
	wr = (काष्ठा orangefs_ग_लिखो_range *)page_निजी(page);

	अगर (offset == 0 && length == PAGE_SIZE) अणु
		kमुक्त(detach_page_निजी(page));
		वापस;
	/* ग_लिखो range entirely within invalidate range (or equal) */
	पूर्ण अन्यथा अगर (page_offset(page) + offset <= wr->pos &&
	    wr->pos + wr->len <= page_offset(page) + offset + length) अणु
		kमुक्त(detach_page_निजी(page));
		/* XXX is this right? only caller in fs */
		cancel_dirty_page(page);
		वापस;
	/* invalidate range chops off end of ग_लिखो range */
	पूर्ण अन्यथा अगर (wr->pos < page_offset(page) + offset &&
	    wr->pos + wr->len <= page_offset(page) + offset + length &&
	     page_offset(page) + offset < wr->pos + wr->len) अणु
		माप_प्रकार x;
		x = wr->pos + wr->len - (page_offset(page) + offset);
		WARN_ON(x > wr->len);
		wr->len -= x;
		wr->uid = current_fsuid();
		wr->gid = current_fsgid();
	/* invalidate range chops off beginning of ग_लिखो range */
	पूर्ण अन्यथा अगर (page_offset(page) + offset <= wr->pos &&
	    page_offset(page) + offset + length < wr->pos + wr->len &&
	    wr->pos < page_offset(page) + offset + length) अणु
		माप_प्रकार x;
		x = page_offset(page) + offset + length - wr->pos;
		WARN_ON(x > wr->len);
		wr->pos += x;
		wr->len -= x;
		wr->uid = current_fsuid();
		wr->gid = current_fsgid();
	/* invalidate range entirely within ग_लिखो range (punch hole) */
	पूर्ण अन्यथा अगर (wr->pos < page_offset(page) + offset &&
	    page_offset(page) + offset + length < wr->pos + wr->len) अणु
		/* XXX what करो we करो here... should not WARN_ON */
		WARN_ON(1);
		/* punch hole */
		/*
		 * should we just ignore this and ग_लिखो it out anyway?
		 * it hardly makes sense
		 */
		वापस;
	/* non-overlapping ranges */
	पूर्ण अन्यथा अणु
		/* WARN अगर they करो overlap */
		अगर (!((page_offset(page) + offset + length <= wr->pos) ^
		    (wr->pos + wr->len <= page_offset(page) + offset))) अणु
			WARN_ON(1);
			prपूर्णांकk("invalidate range offset %llu length %u\n",
			    page_offset(page) + offset, length);
			prपूर्णांकk("write range offset %llu length %zu\n",
			    wr->pos, wr->len);
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * Above there are वापसs where wr is मुक्तd or where we WARN.
	 * Thus the following runs अगर wr was modअगरied above.
	 */

	orangefs_launder_page(page);
पूर्ण

अटल पूर्णांक orangefs_releasepage(काष्ठा page *page, gfp_t foo)
अणु
	वापस !PagePrivate(page);
पूर्ण

अटल व्योम orangefs_मुक्तpage(काष्ठा page *page)
अणु
	kमुक्त(detach_page_निजी(page));
पूर्ण

अटल पूर्णांक orangefs_launder_page(काष्ठा page *page)
अणु
	पूर्णांक r = 0;
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_ALL,
		.nr_to_ग_लिखो = 0,
	पूर्ण;
	रुको_on_page_ग_लिखोback(page);
	अगर (clear_page_dirty_क्रम_io(page)) अणु
		r = orangefs_ग_लिखोpage_locked(page, &wbc);
		end_page_ग_लिखोback(page);
	पूर्ण
	वापस r;
पूर्ण

अटल sमाप_प्रकार orangefs_direct_IO(काष्ठा kiocb *iocb,
				  काष्ठा iov_iter *iter)
अणु
	/*
	 * Comment from original करो_पढ़ोv_ग_लिखोv:
	 * Common entry poपूर्णांक क्रम पढ़ो/ग_लिखो/पढ़ोv/ग_लिखोv
	 * This function will dispatch it to either the direct I/O
	 * or buffered I/O path depending on the mount options and/or
	 * augmented/extended metadata attached to the file.
	 * Note: File extended attributes override any mount options.
	 */
	काष्ठा file *file = iocb->ki_filp;
	loff_t pos = iocb->ki_pos;
	क्रमागत ORANGEFS_io_type type = iov_iter_rw(iter) == WRITE ?
            ORANGEFS_IO_WRITE : ORANGEFS_IO_READ;
	loff_t *offset = &pos;
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_khandle *handle = &orangefs_inode->refn.khandle;
	माप_प्रकार count = iov_iter_count(iter);
	sमाप_प्रकार total_count = 0;
	sमाप_प्रकार ret = -EINVAL;
	पूर्णांक i = 0;

	gossip_debug(GOSSIP_खाता_DEBUG,
		"%s-BEGIN(%pU): count(%d) after estimate_max_iovecs.\n",
		__func__,
		handle,
		(पूर्णांक)count);

	अगर (type == ORANGEFS_IO_WRITE) अणु
		gossip_debug(GOSSIP_खाता_DEBUG,
			     "%s(%pU): proceeding with offset : %llu, "
			     "size %d\n",
			     __func__,
			     handle,
			     llu(*offset),
			     (पूर्णांक)count);
	पूर्ण

	अगर (count == 0) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	जबतक (iov_iter_count(iter)) अणु
		माप_प्रकार each_count = iov_iter_count(iter);
		माप_प्रकार amt_complete;
		i++;

		/* how much to transfer in this loop iteration */
		अगर (each_count > orangefs_bufmap_size_query())
			each_count = orangefs_bufmap_size_query();

		gossip_debug(GOSSIP_खाता_DEBUG,
			     "%s(%pU): size of each_count(%d)\n",
			     __func__,
			     handle,
			     (पूर्णांक)each_count);
		gossip_debug(GOSSIP_खाता_DEBUG,
			     "%s(%pU): BEFORE wait_for_io: offset is %d\n",
			     __func__,
			     handle,
			     (पूर्णांक)*offset);

		ret = रुको_क्रम_direct_io(type, inode, offset, iter,
				each_count, 0, शून्य, शून्य, file);
		gossip_debug(GOSSIP_खाता_DEBUG,
			     "%s(%pU): return from wait_for_io:%d\n",
			     __func__,
			     handle,
			     (पूर्णांक)ret);

		अगर (ret < 0)
			जाओ out;

		*offset += ret;
		total_count += ret;
		amt_complete = ret;

		gossip_debug(GOSSIP_खाता_DEBUG,
			     "%s(%pU): AFTER wait_for_io: offset is %d\n",
			     __func__,
			     handle,
			     (पूर्णांक)*offset);

		/*
		 * अगर we got a लघु I/O operations,
		 * fall out and वापस what we got so far
		 */
		अगर (amt_complete < each_count)
			अवरोध;
	पूर्ण /*end जबतक */

out:
	अगर (total_count > 0)
		ret = total_count;
	अगर (ret > 0) अणु
		अगर (type == ORANGEFS_IO_READ) अणु
			file_accessed(file);
		पूर्ण अन्यथा अणु
			file_update_समय(file);
			अगर (*offset > i_size_पढ़ो(inode))
				i_size_ग_लिखो(inode, *offset);
		पूर्ण
	पूर्ण

	gossip_debug(GOSSIP_खाता_DEBUG,
		     "%s(%pU): Value(%d) returned.\n",
		     __func__,
		     handle,
		     (पूर्णांक)ret);

	वापस ret;
पूर्ण

/** ORANGEFS2 implementation of address space operations */
अटल स्थिर काष्ठा address_space_operations orangefs_address_operations = अणु
	.ग_लिखोpage = orangefs_ग_लिखोpage,
	.पढ़ोahead = orangefs_पढ़ोahead,
	.पढ़ोpage = orangefs_पढ़ोpage,
	.ग_लिखोpages = orangefs_ग_लिखोpages,
	.set_page_dirty = __set_page_dirty_nobuffers,
	.ग_लिखो_begin = orangefs_ग_लिखो_begin,
	.ग_लिखो_end = orangefs_ग_लिखो_end,
	.invalidatepage = orangefs_invalidatepage,
	.releasepage = orangefs_releasepage,
	.मुक्तpage = orangefs_मुक्तpage,
	.launder_page = orangefs_launder_page,
	.direct_IO = orangefs_direct_IO,
पूर्ण;

vm_fault_t orangefs_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page = vmf->page;
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	अचिन्हित दीर्घ *bitlock = &orangefs_inode->bitlock;
	vm_fault_t ret;
	काष्ठा orangefs_ग_लिखो_range *wr;

	sb_start_pagefault(inode->i_sb);

	अगर (रुको_on_bit(bitlock, 1, TASK_KILLABLE)) अणु
		ret = VM_FAULT_RETRY;
		जाओ out;
	पूर्ण

	lock_page(page);
	अगर (PageDirty(page) && !PagePrivate(page)) अणु
		/*
		 * Should be impossible.  If it happens, launder the page
		 * since we करोn't know what's dirty.  This will WARN in
		 * orangefs_ग_लिखोpage_locked.
		 */
		अगर (orangefs_launder_page(page)) अणु
			ret = VM_FAULT_LOCKED|VM_FAULT_RETRY;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (PagePrivate(page)) अणु
		wr = (काष्ठा orangefs_ग_लिखो_range *)page_निजी(page);
		अगर (uid_eq(wr->uid, current_fsuid()) &&
		    gid_eq(wr->gid, current_fsgid())) अणु
			wr->pos = page_offset(page);
			wr->len = PAGE_SIZE;
			जाओ okay;
		पूर्ण अन्यथा अणु
			अगर (orangefs_launder_page(page)) अणु
				ret = VM_FAULT_LOCKED|VM_FAULT_RETRY;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	wr = kदो_स्मृति(माप *wr, GFP_KERNEL);
	अगर (!wr) अणु
		ret = VM_FAULT_LOCKED|VM_FAULT_RETRY;
		जाओ out;
	पूर्ण
	wr->pos = page_offset(page);
	wr->len = PAGE_SIZE;
	wr->uid = current_fsuid();
	wr->gid = current_fsgid();
	attach_page_निजी(page, wr);
okay:

	file_update_समय(vmf->vma->vm_file);
	अगर (page->mapping != inode->i_mapping) अणु
		unlock_page(page);
		ret = VM_FAULT_LOCKED|VM_FAULT_NOPAGE;
		जाओ out;
	पूर्ण

	/*
	 * We mark the page dirty alपढ़ोy here so that when मुक्तze is in
	 * progress, we are guaranteed that ग_लिखोback during मुक्तzing will
	 * see the dirty page and ग_लिखोprotect it again.
	 */
	set_page_dirty(page);
	रुको_क्रम_stable_page(page);
	ret = VM_FAULT_LOCKED;
out:
	sb_end_pagefault(inode->i_sb);
	वापस ret;
पूर्ण

अटल पूर्णांक orangefs_setattr_size(काष्ठा inode *inode, काष्ठा iattr *iattr)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_kernel_op_s *new_op;
	loff_t orig_size;
	पूर्णांक ret = -EINVAL;

	gossip_debug(GOSSIP_INODE_DEBUG,
		     "%s: %pU: Handle is %pU | fs_id %d | size is %llu\n",
		     __func__,
		     get_khandle_from_ino(inode),
		     &orangefs_inode->refn.khandle,
		     orangefs_inode->refn.fs_id,
		     iattr->ia_size);

	/* Ensure that we have a up to date size, so we know अगर it changed. */
	ret = orangefs_inode_getattr(inode, ORANGEFS_GETATTR_SIZE);
	अगर (ret == -ESTALE)
		ret = -EIO;
	अगर (ret) अणु
		gossip_err("%s: orangefs_inode_getattr failed, ret:%d:.\n",
		    __func__, ret);
		वापस ret;
	पूर्ण
	orig_size = i_size_पढ़ो(inode);

	/* This is truncate_setsize in a dअगरferent order. */
	truncate_pagecache(inode, iattr->ia_size);
	i_size_ग_लिखो(inode, iattr->ia_size);
	अगर (iattr->ia_size > orig_size)
		pagecache_isize_extended(inode, orig_size, iattr->ia_size);

	new_op = op_alloc(ORANGEFS_VFS_OP_TRUNCATE);
	अगर (!new_op)
		वापस -ENOMEM;

	new_op->upcall.req.truncate.refn = orangefs_inode->refn;
	new_op->upcall.req.truncate.size = (__s64) iattr->ia_size;

	ret = service_operation(new_op,
		__func__,
		get_पूर्णांकerruptible_flag(inode));

	/*
	 * the truncate has no करोwncall members to retrieve, but
	 * the status value tells us अगर it went through ok or not
	 */
	gossip_debug(GOSSIP_INODE_DEBUG, "%s: ret:%d:\n", __func__, ret);

	op_release(new_op);

	अगर (ret != 0)
		वापस ret;

	अगर (orig_size != i_size_पढ़ो(inode))
		iattr->ia_valid |= ATTR_CTIME | ATTR_MTIME;

	वापस ret;
पूर्ण

पूर्णांक __orangefs_setattr(काष्ठा inode *inode, काष्ठा iattr *iattr)
अणु
	पूर्णांक ret;

	अगर (iattr->ia_valid & ATTR_MODE) अणु
		अगर (iattr->ia_mode & (S_ISVTX)) अणु
			अगर (is_root_handle(inode)) अणु
				/*
				 * allow sticky bit to be set on root (since
				 * it shows up that way by शेष anyhow),
				 * but करोn't show it to the server
				 */
				iattr->ia_mode -= S_ISVTX;
			पूर्ण अन्यथा अणु
				gossip_debug(GOSSIP_UTILS_DEBUG,
					     "User attempted to set sticky bit on non-root directory; returning EINVAL.\n");
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (iattr->ia_mode & (S_ISUID)) अणु
			gossip_debug(GOSSIP_UTILS_DEBUG,
				     "Attempting to set setuid bit (not supported); returning EINVAL.\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (iattr->ia_valid & ATTR_SIZE) अणु
		ret = orangefs_setattr_size(inode, iattr);
		अगर (ret)
			जाओ out;
	पूर्ण

again:
	spin_lock(&inode->i_lock);
	अगर (ORANGEFS_I(inode)->attr_valid) अणु
		अगर (uid_eq(ORANGEFS_I(inode)->attr_uid, current_fsuid()) &&
		    gid_eq(ORANGEFS_I(inode)->attr_gid, current_fsgid())) अणु
			ORANGEFS_I(inode)->attr_valid = iattr->ia_valid;
		पूर्ण अन्यथा अणु
			spin_unlock(&inode->i_lock);
			ग_लिखो_inode_now(inode, 1);
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		ORANGEFS_I(inode)->attr_valid = iattr->ia_valid;
		ORANGEFS_I(inode)->attr_uid = current_fsuid();
		ORANGEFS_I(inode)->attr_gid = current_fsgid();
	पूर्ण
	setattr_copy(&init_user_ns, inode, iattr);
	spin_unlock(&inode->i_lock);
	mark_inode_dirty(inode);

	अगर (iattr->ia_valid & ATTR_MODE)
		/* change mod on a file that has ACLs */
		ret = posix_acl_chmod(&init_user_ns, inode, inode->i_mode);

	ret = 0;
out:
	वापस ret;
पूर्ण

/*
 * Change attributes of an object referenced by dentry.
 */
पूर्णांक orangefs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		     काष्ठा iattr *iattr)
अणु
	पूर्णांक ret;
	gossip_debug(GOSSIP_INODE_DEBUG, "__orangefs_setattr: called on %pd\n",
	    dentry);
	ret = setattr_prepare(&init_user_ns, dentry, iattr);
	अगर (ret)
	        जाओ out;
	ret = __orangefs_setattr(d_inode(dentry), iattr);
	sync_inode_metadata(d_inode(dentry), 1);
out:
	gossip_debug(GOSSIP_INODE_DEBUG, "orangefs_setattr: returning %d\n",
	    ret);
	वापस ret;
पूर्ण

/*
 * Obtain attributes of an object given a dentry
 */
पूर्णांक orangefs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		     काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode = path->dentry->d_inode;

	gossip_debug(GOSSIP_INODE_DEBUG,
		     "orangefs_getattr: called on %pd mask %u\n",
		     path->dentry, request_mask);

	ret = orangefs_inode_getattr(inode,
	    request_mask & STATX_SIZE ? ORANGEFS_GETATTR_SIZE : 0);
	अगर (ret == 0) अणु
		generic_fillattr(&init_user_ns, inode, stat);

		/* override block size reported to stat */
		अगर (!(request_mask & STATX_SIZE))
			stat->result_mask &= ~STATX_SIZE;

		stat->attributes_mask = STATX_ATTR_IMMUTABLE |
		    STATX_ATTR_APPEND;
		अगर (inode->i_flags & S_IMMUTABLE)
			stat->attributes |= STATX_ATTR_IMMUTABLE;
		अगर (inode->i_flags & S_APPEND)
			stat->attributes |= STATX_ATTR_APPEND;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक orangefs_permission(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *inode, पूर्णांक mask)
अणु
	पूर्णांक ret;

	अगर (mask & MAY_NOT_BLOCK)
		वापस -ECHILD;

	gossip_debug(GOSSIP_INODE_DEBUG, "%s: refreshing\n", __func__);

	/* Make sure the permission (and other common attrs) are up to date. */
	ret = orangefs_inode_getattr(inode, 0);
	अगर (ret < 0)
		वापस ret;

	वापस generic_permission(&init_user_ns, inode, mask);
पूर्ण

पूर्णांक orangefs_update_समय(काष्ठा inode *inode, काष्ठा बारpec64 *समय, पूर्णांक flags)
अणु
	काष्ठा iattr iattr;
	gossip_debug(GOSSIP_INODE_DEBUG, "orangefs_update_time: %pU\n",
	    get_khandle_from_ino(inode));
	generic_update_समय(inode, समय, flags);
	स_रखो(&iattr, 0, माप iattr);
        अगर (flags & S_ATIME)
		iattr.ia_valid |= ATTR_ATIME;
	अगर (flags & S_CTIME)
		iattr.ia_valid |= ATTR_CTIME;
	अगर (flags & S_MTIME)
		iattr.ia_valid |= ATTR_MTIME;
	वापस __orangefs_setattr(inode, &iattr);
पूर्ण

अटल पूर्णांक orangefs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	u64 val = 0;
	पूर्णांक ret;

	gossip_debug(GOSSIP_खाता_DEBUG, "%s: called on %pd\n", __func__,
		     dentry);

	ret = orangefs_inode_getxattr(d_inode(dentry),
				      "user.pvfs2.meta_hint",
				      &val, माप(val));
	अगर (ret < 0 && ret != -ENODATA)
		वापस ret;

	gossip_debug(GOSSIP_खाता_DEBUG, "%s: flags=%u\n", __func__, (u32) val);

	fileattr_fill_flags(fa, val);
	वापस 0;
पूर्ण

अटल पूर्णांक orangefs_fileattr_set(काष्ठा user_namespace *mnt_userns,
				 काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	u64 val = 0;

	gossip_debug(GOSSIP_खाता_DEBUG, "%s: called on %pd\n", __func__,
		     dentry);
	/*
	 * ORANGEFS_MIRROR_FL is set पूर्णांकernally when the mirroring mode is
	 * turned on क्रम a file. The user is not allowed to turn on this bit,
	 * but the bit is present अगर the user first माला_लो the flags and then
	 * updates the flags with some new settings. So, we ignore it in the
	 * following edit. bligon.
	 */
	अगर (fileattr_has_fsx(fa) ||
	    (fa->flags & ~(FS_IMMUTABLE_FL | FS_APPEND_FL | FS_NOATIME_FL | ORANGEFS_MIRROR_FL))) अणु
		gossip_err("%s: only supports setting one of FS_IMMUTABLE_FL|FS_APPEND_FL|FS_NOATIME_FL\n",
			   __func__);
		वापस -EOPNOTSUPP;
	पूर्ण
	val = fa->flags;
	gossip_debug(GOSSIP_खाता_DEBUG, "%s: flags=%u\n", __func__, (u32) val);
	वापस orangefs_inode_setxattr(d_inode(dentry),
				       "user.pvfs2.meta_hint",
				       &val, माप(val), 0);
पूर्ण

/* ORANGEFS2 implementation of VFS inode operations क्रम files */
अटल स्थिर काष्ठा inode_operations orangefs_file_inode_operations = अणु
	.get_acl = orangefs_get_acl,
	.set_acl = orangefs_set_acl,
	.setattr = orangefs_setattr,
	.getattr = orangefs_getattr,
	.listxattr = orangefs_listxattr,
	.permission = orangefs_permission,
	.update_समय = orangefs_update_समय,
	.fileattr_get = orangefs_fileattr_get,
	.fileattr_set = orangefs_fileattr_set,
पूर्ण;

अटल पूर्णांक orangefs_init_iops(काष्ठा inode *inode)
अणु
	inode->i_mapping->a_ops = &orangefs_address_operations;

	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFREG:
		inode->i_op = &orangefs_file_inode_operations;
		inode->i_fop = &orangefs_file_operations;
		अवरोध;
	हाल S_IFLNK:
		inode->i_op = &orangefs_symlink_inode_operations;
		अवरोध;
	हाल S_IFसूची:
		inode->i_op = &orangefs_dir_inode_operations;
		inode->i_fop = &orangefs_dir_operations;
		अवरोध;
	शेष:
		gossip_debug(GOSSIP_INODE_DEBUG,
			     "%s: unsupported mode\n",
			     __func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Given an ORANGEFS object identअगरier (fsid, handle), convert it पूर्णांकo
 * a ino_t type that will be used as a hash-index from where the handle will
 * be searched क्रम in the VFS hash table of inodes.
 */
अटल अंतरभूत ino_t orangefs_handle_hash(काष्ठा orangefs_object_kref *ref)
अणु
	अगर (!ref)
		वापस 0;
	वापस orangefs_khandle_to_ino(&(ref->khandle));
पूर्ण

/*
 * Called to set up an inode from iget5_locked.
 */
अटल पूर्णांक orangefs_set_inode(काष्ठा inode *inode, व्योम *data)
अणु
	काष्ठा orangefs_object_kref *ref = (काष्ठा orangefs_object_kref *) data;
	ORANGEFS_I(inode)->refn.fs_id = ref->fs_id;
	ORANGEFS_I(inode)->refn.khandle = ref->khandle;
	ORANGEFS_I(inode)->attr_valid = 0;
	hash_init(ORANGEFS_I(inode)->xattr_cache);
	ORANGEFS_I(inode)->mapping_समय = jअगरfies - 1;
	ORANGEFS_I(inode)->bitlock = 0;
	वापस 0;
पूर्ण

/*
 * Called to determine अगर handles match.
 */
अटल पूर्णांक orangefs_test_inode(काष्ठा inode *inode, व्योम *data)
अणु
	काष्ठा orangefs_object_kref *ref = (काष्ठा orangefs_object_kref *) data;
	काष्ठा orangefs_inode_s *orangefs_inode = शून्य;

	orangefs_inode = ORANGEFS_I(inode);
	/* test handles and fs_ids... */
	वापस (!ORANGEFS_khandle_cmp(&(orangefs_inode->refn.khandle),
				&(ref->khandle)) &&
			orangefs_inode->refn.fs_id == ref->fs_id);
पूर्ण

/*
 * Front-end to lookup the inode-cache मुख्यtained by the VFS using the ORANGEFS
 * file handle.
 *
 * @sb: the file प्रणाली super block instance.
 * @ref: The ORANGEFS object क्रम which we are trying to locate an inode.
 */
काष्ठा inode *orangefs_iget(काष्ठा super_block *sb,
		काष्ठा orangefs_object_kref *ref)
अणु
	काष्ठा inode *inode = शून्य;
	अचिन्हित दीर्घ hash;
	पूर्णांक error;

	hash = orangefs_handle_hash(ref);
	inode = iget5_locked(sb,
			hash,
			orangefs_test_inode,
			orangefs_set_inode,
			ref);

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	error = orangefs_inode_getattr(inode, ORANGEFS_GETATTR_NEW);
	अगर (error) अणु
		iget_failed(inode);
		वापस ERR_PTR(error);
	पूर्ण

	inode->i_ino = hash;	/* needed क्रम stat etc */
	orangefs_init_iops(inode);
	unlock_new_inode(inode);

	gossip_debug(GOSSIP_INODE_DEBUG,
		     "iget handle %pU, fsid %d hash %ld i_ino %lu\n",
		     &ref->khandle,
		     ref->fs_id,
		     hash,
		     inode->i_ino);

	वापस inode;
पूर्ण

/*
 * Allocate an inode क्रम a newly created file and insert it पूर्णांकo the inode hash.
 */
काष्ठा inode *orangefs_new_inode(काष्ठा super_block *sb, काष्ठा inode *dir,
		पूर्णांक mode, dev_t dev, काष्ठा orangefs_object_kref *ref)
अणु
	अचिन्हित दीर्घ hash = orangefs_handle_hash(ref);
	काष्ठा inode *inode;
	पूर्णांक error;

	gossip_debug(GOSSIP_INODE_DEBUG,
		     "%s:(sb is %p | MAJOR(dev)=%u | MINOR(dev)=%u mode=%o)\n",
		     __func__,
		     sb,
		     MAJOR(dev),
		     MINOR(dev),
		     mode);

	inode = new_inode(sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	orangefs_set_inode(inode, ref);
	inode->i_ino = hash;	/* needed क्रम stat etc */

	error = orangefs_inode_getattr(inode, ORANGEFS_GETATTR_NEW);
	अगर (error)
		जाओ out_iput;

	orangefs_init_iops(inode);
	inode->i_rdev = dev;

	error = insert_inode_locked4(inode, hash, orangefs_test_inode, ref);
	अगर (error < 0)
		जाओ out_iput;

	gossip_debug(GOSSIP_INODE_DEBUG,
		     "Initializing ACL's for inode %pU\n",
		     get_khandle_from_ino(inode));
	orangefs_init_acl(inode, dir);
	वापस inode;

out_iput:
	iput(inode);
	वापस ERR_PTR(error);
पूर्ण
