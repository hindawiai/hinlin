<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/mpage.h>
#समावेश <linux/fs.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/swap.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/uपन.स>
#समावेश <trace/events/ग_लिखोback.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "bmap.h"
#समावेश "glock.h"
#समावेश "inode.h"
#समावेश "log.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "trans.h"
#समावेश "rgrp.h"
#समावेश "super.h"
#समावेश "util.h"
#समावेश "glops.h"
#समावेश "aops.h"


व्योम gfs2_page_add_databufs(काष्ठा gfs2_inode *ip, काष्ठा page *page,
			    अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक len)
अणु
	काष्ठा buffer_head *head = page_buffers(page);
	अचिन्हित पूर्णांक bsize = head->b_size;
	काष्ठा buffer_head *bh;
	अचिन्हित पूर्णांक to = from + len;
	अचिन्हित पूर्णांक start, end;

	क्रम (bh = head, start = 0; bh != head || !start;
	     bh = bh->b_this_page, start = end) अणु
		end = start + bsize;
		अगर (end <= from)
			जारी;
		अगर (start >= to)
			अवरोध;
		set_buffer_uptodate(bh);
		gfs2_trans_add_data(ip->i_gl, bh);
	पूर्ण
पूर्ण

/**
 * gfs2_get_block_noalloc - Fills in a buffer head with details about a block
 * @inode: The inode
 * @lblock: The block number to look up
 * @bh_result: The buffer head to वापस the result in
 * @create: Non-zero अगर we may add block to the file
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_get_block_noalloc(काष्ठा inode *inode, sector_t lblock,
				  काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	पूर्णांक error;

	error = gfs2_block_map(inode, lblock, bh_result, 0);
	अगर (error)
		वापस error;
	अगर (!buffer_mapped(bh_result))
		वापस -ENODATA;
	वापस 0;
पूर्ण

/**
 * gfs2_ग_लिखोpage - Write page क्रम ग_लिखोback mappings
 * @page: The page
 * @wbc: The ग_लिखोback control
 */
अटल पूर्णांक gfs2_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा iomap_ग_लिखोpage_ctx wpc = अणु पूर्ण;

	अगर (gfs2_निश्चित_withdraw(sdp, gfs2_glock_is_held_excl(ip->i_gl)))
		जाओ out;
	अगर (current->journal_info)
		जाओ redirty;
	वापस iomap_ग_लिखोpage(page, wbc, &wpc, &gfs2_ग_लिखोback_ops);

redirty:
	redirty_page_क्रम_ग_लिखोpage(wbc, page);
out:
	unlock_page(page);
	वापस 0;
पूर्ण

/**
 * gfs2_ग_लिखो_jdata_page - gfs2 jdata-specअगरic version of block_ग_लिखो_full_page
 * @page: The page to ग_लिखो
 * @wbc: The ग_लिखोback control
 *
 * This is the same as calling block_ग_लिखो_full_page, but it also
 * ग_लिखोs pages outside of i_size
 */
अटल पूर्णांक gfs2_ग_लिखो_jdata_page(काष्ठा page *page,
				 काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode * स्थिर inode = page->mapping->host;
	loff_t i_size = i_size_पढ़ो(inode);
	स्थिर pgoff_t end_index = i_size >> PAGE_SHIFT;
	अचिन्हित offset;

	/*
	 * The page straddles i_size.  It must be zeroed out on each and every
	 * ग_लिखोpage invocation because it may be mmapped.  "A file is mapped
	 * in multiples of the page size.  For a file that is not a multiple of
	 * the  page size, the reमुख्यing memory is zeroed when mapped, and
	 * ग_लिखोs to that region are not written out to the file."
	 */
	offset = i_size & (PAGE_SIZE - 1);
	अगर (page->index == end_index && offset)
		zero_user_segment(page, offset, PAGE_SIZE);

	वापस __block_ग_लिखो_full_page(inode, page, gfs2_get_block_noalloc, wbc,
				       end_buffer_async_ग_लिखो);
पूर्ण

/**
 * __gfs2_jdata_ग_लिखोpage - The core of jdata ग_लिखोpage
 * @page: The page to ग_लिखो
 * @wbc: The ग_लिखोback control
 *
 * This is shared between ग_लिखोpage and ग_लिखोpages and implements the
 * core of the ग_लिखोpage operation. If a transaction is required then
 * PageChecked will have been set and the transaction will have
 * alपढ़ोy been started beक्रमe this is called.
 */

अटल पूर्णांक __gfs2_jdata_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);

	अगर (PageChecked(page)) अणु
		ClearPageChecked(page);
		अगर (!page_has_buffers(page)) अणु
			create_empty_buffers(page, inode->i_sb->s_blocksize,
					     BIT(BH_Dirty)|BIT(BH_Uptodate));
		पूर्ण
		gfs2_page_add_databufs(ip, page, 0, sdp->sd_vfs->s_blocksize);
	पूर्ण
	वापस gfs2_ग_लिखो_jdata_page(page, wbc);
पूर्ण

/**
 * gfs2_jdata_ग_लिखोpage - Write complete page
 * @page: Page to ग_लिखो
 * @wbc: The ग_लिखोback control
 *
 * Returns: त्रुटि_सं
 *
 */

अटल पूर्णांक gfs2_jdata_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);

	अगर (gfs2_निश्चित_withdraw(sdp, gfs2_glock_is_held_excl(ip->i_gl)))
		जाओ out;
	अगर (PageChecked(page) || current->journal_info)
		जाओ out_ignore;
	वापस __gfs2_jdata_ग_लिखोpage(page, wbc);

out_ignore:
	redirty_page_क्रम_ग_लिखोpage(wbc, page);
out:
	unlock_page(page);
	वापस 0;
पूर्ण

/**
 * gfs2_ग_लिखोpages - Write a bunch of dirty pages back to disk
 * @mapping: The mapping to ग_लिखो
 * @wbc: Write-back control
 *
 * Used क्रम both ordered and ग_लिखोback modes.
 */
अटल पूर्णांक gfs2_ग_लिखोpages(काष्ठा address_space *mapping,
			   काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा gfs2_sbd *sdp = gfs2_mapping2sbd(mapping);
	काष्ठा iomap_ग_लिखोpage_ctx wpc = अणु पूर्ण;
	पूर्णांक ret;

	/*
	 * Even अगर we didn't ग_लिखो any pages here, we might still be holding
	 * dirty pages in the ail. We क्रमcibly flush the ail because we करोn't
	 * want balance_dirty_pages() to loop indefinitely trying to ग_लिखो out
	 * pages held in the ail that it can't find.
	 */
	ret = iomap_ग_लिखोpages(mapping, wbc, &wpc, &gfs2_ग_लिखोback_ops);
	अगर (ret == 0)
		set_bit(SDF_FORCE_AIL_FLUSH, &sdp->sd_flags);
	वापस ret;
पूर्ण

/**
 * gfs2_ग_लिखो_jdata_pagevec - Write back a pagevec's worth of pages
 * @mapping: The mapping
 * @wbc: The ग_लिखोback control
 * @pvec: The vector of pages
 * @nr_pages: The number of pages to ग_लिखो
 * @करोne_index: Page index
 *
 * Returns: non-zero अगर loop should terminate, zero otherwise
 */

अटल पूर्णांक gfs2_ग_लिखो_jdata_pagevec(काष्ठा address_space *mapping,
				    काष्ठा ग_लिखोback_control *wbc,
				    काष्ठा pagevec *pvec,
				    पूर्णांक nr_pages,
				    pgoff_t *करोne_index)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	अचिन्हित nrblocks = nr_pages * (PAGE_SIZE >> inode->i_blkbits);
	पूर्णांक i;
	पूर्णांक ret;

	ret = gfs2_trans_begin(sdp, nrblocks, nrblocks);
	अगर (ret < 0)
		वापस ret;

	क्रम(i = 0; i < nr_pages; i++) अणु
		काष्ठा page *page = pvec->pages[i];

		*करोne_index = page->index;

		lock_page(page);

		अगर (unlikely(page->mapping != mapping)) अणु
जारी_unlock:
			unlock_page(page);
			जारी;
		पूर्ण

		अगर (!PageDirty(page)) अणु
			/* someone wrote it क्रम us */
			जाओ जारी_unlock;
		पूर्ण

		अगर (PageWriteback(page)) अणु
			अगर (wbc->sync_mode != WB_SYNC_NONE)
				रुको_on_page_ग_लिखोback(page);
			अन्यथा
				जाओ जारी_unlock;
		पूर्ण

		BUG_ON(PageWriteback(page));
		अगर (!clear_page_dirty_क्रम_io(page))
			जाओ जारी_unlock;

		trace_wbc_ग_लिखोpage(wbc, inode_to_bdi(inode));

		ret = __gfs2_jdata_ग_लिखोpage(page, wbc);
		अगर (unlikely(ret)) अणु
			अगर (ret == AOP_WRITEPAGE_ACTIVATE) अणु
				unlock_page(page);
				ret = 0;
			पूर्ण अन्यथा अणु

				/*
				 * करोne_index is set past this page,
				 * so media errors will not choke
				 * background ग_लिखोout क्रम the entire
				 * file. This has consequences क्रम
				 * range_cyclic semantics (ie. it may
				 * not be suitable क्रम data पूर्णांकegrity
				 * ग_लिखोout).
				 */
				*करोne_index = page->index + 1;
				ret = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * We stop writing back only अगर we are not करोing
		 * पूर्णांकegrity sync. In हाल of पूर्णांकegrity sync we have to
		 * keep going until we have written all the pages
		 * we tagged क्रम ग_लिखोback prior to entering this loop.
		 */
		अगर (--wbc->nr_to_ग_लिखो <= 0 && wbc->sync_mode == WB_SYNC_NONE) अणु
			ret = 1;
			अवरोध;
		पूर्ण

	पूर्ण
	gfs2_trans_end(sdp);
	वापस ret;
पूर्ण

/**
 * gfs2_ग_लिखो_cache_jdata - Like ग_लिखो_cache_pages but dअगरferent
 * @mapping: The mapping to ग_लिखो
 * @wbc: The ग_लिखोback control
 *
 * The reason that we use our own function here is that we need to
 * start transactions beक्रमe we grab page locks. This allows us
 * to get the ordering right.
 */

अटल पूर्णांक gfs2_ग_लिखो_cache_jdata(काष्ठा address_space *mapping,
				  काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret = 0;
	पूर्णांक करोne = 0;
	काष्ठा pagevec pvec;
	पूर्णांक nr_pages;
	pgoff_t ग_लिखोback_index;
	pgoff_t index;
	pgoff_t end;
	pgoff_t करोne_index;
	पूर्णांक cycled;
	पूर्णांक range_whole = 0;
	xa_mark_t tag;

	pagevec_init(&pvec);
	अगर (wbc->range_cyclic) अणु
		ग_लिखोback_index = mapping->ग_लिखोback_index; /* prev offset */
		index = ग_लिखोback_index;
		अगर (index == 0)
			cycled = 1;
		अन्यथा
			cycled = 0;
		end = -1;
	पूर्ण अन्यथा अणु
		index = wbc->range_start >> PAGE_SHIFT;
		end = wbc->range_end >> PAGE_SHIFT;
		अगर (wbc->range_start == 0 && wbc->range_end == Lदीर्घ_उच्च)
			range_whole = 1;
		cycled = 1; /* ignore range_cyclic tests */
	पूर्ण
	अगर (wbc->sync_mode == WB_SYNC_ALL || wbc->tagged_ग_लिखोpages)
		tag = PAGECACHE_TAG_TOWRITE;
	अन्यथा
		tag = PAGECACHE_TAG_सूचीTY;

retry:
	अगर (wbc->sync_mode == WB_SYNC_ALL || wbc->tagged_ग_लिखोpages)
		tag_pages_क्रम_ग_लिखोback(mapping, index, end);
	करोne_index = index;
	जबतक (!करोne && (index <= end)) अणु
		nr_pages = pagevec_lookup_range_tag(&pvec, mapping, &index, end,
				tag);
		अगर (nr_pages == 0)
			अवरोध;

		ret = gfs2_ग_लिखो_jdata_pagevec(mapping, wbc, &pvec, nr_pages, &करोne_index);
		अगर (ret)
			करोne = 1;
		अगर (ret > 0)
			ret = 0;
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण

	अगर (!cycled && !करोne) अणु
		/*
		 * range_cyclic:
		 * We hit the last page and there is more work to be करोne: wrap
		 * back to the start of the file
		 */
		cycled = 1;
		index = 0;
		end = ग_लिखोback_index - 1;
		जाओ retry;
	पूर्ण

	अगर (wbc->range_cyclic || (range_whole && wbc->nr_to_ग_लिखो > 0))
		mapping->ग_लिखोback_index = करोne_index;

	वापस ret;
पूर्ण


/**
 * gfs2_jdata_ग_लिखोpages - Write a bunch of dirty pages back to disk
 * @mapping: The mapping to ग_लिखो
 * @wbc: The ग_लिखोback control
 * 
 */

अटल पूर्णांक gfs2_jdata_ग_लिखोpages(काष्ठा address_space *mapping,
				 काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(mapping->host);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(mapping->host);
	पूर्णांक ret;

	ret = gfs2_ग_लिखो_cache_jdata(mapping, wbc);
	अगर (ret == 0 && wbc->sync_mode == WB_SYNC_ALL) अणु
		gfs2_log_flush(sdp, ip->i_gl, GFS2_LOG_HEAD_FLUSH_NORMAL |
			       GFS2_LFC_JDATA_WPAGES);
		ret = gfs2_ग_लिखो_cache_jdata(mapping, wbc);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * stuffed_पढ़ोpage - Fill in a Linux page with stuffed file data
 * @ip: the inode
 * @page: the page
 *
 * Returns: त्रुटि_सं
 */
अटल पूर्णांक stuffed_पढ़ोpage(काष्ठा gfs2_inode *ip, काष्ठा page *page)
अणु
	काष्ठा buffer_head *dibh;
	u64 dsize = i_size_पढ़ो(&ip->i_inode);
	व्योम *kaddr;
	पूर्णांक error;

	/*
	 * Due to the order of unstuffing files and ->fault(), we can be
	 * asked क्रम a zero page in the हाल of a stuffed file being extended,
	 * so we need to supply one here. It करोesn't happen often.
	 */
	अगर (unlikely(page->index)) अणु
		zero_user(page, 0, PAGE_SIZE);
		SetPageUptodate(page);
		वापस 0;
	पूर्ण

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error)
		वापस error;

	kaddr = kmap_atomic(page);
	अगर (dsize > gfs2_max_stuffed_size(ip))
		dsize = gfs2_max_stuffed_size(ip);
	स_नकल(kaddr, dibh->b_data + माप(काष्ठा gfs2_dinode), dsize);
	स_रखो(kaddr + dsize, 0, PAGE_SIZE - dsize);
	kunmap_atomic(kaddr);
	flush_dcache_page(page);
	brअन्यथा(dibh);
	SetPageUptodate(page);

	वापस 0;
पूर्ण


अटल पूर्णांक __gfs2_पढ़ोpage(व्योम *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	पूर्णांक error;

	अगर (!gfs2_is_jdata(ip) ||
	    (i_blocksize(inode) == PAGE_SIZE && !page_has_buffers(page))) अणु
		error = iomap_पढ़ोpage(page, &gfs2_iomap_ops);
	पूर्ण अन्यथा अगर (gfs2_is_stuffed(ip)) अणु
		error = stuffed_पढ़ोpage(ip, page);
		unlock_page(page);
	पूर्ण अन्यथा अणु
		error = mpage_पढ़ोpage(page, gfs2_block_map);
	पूर्ण

	अगर (unlikely(gfs2_withdrawn(sdp)))
		वापस -EIO;

	वापस error;
पूर्ण

/**
 * gfs2_पढ़ोpage - पढ़ो a page of a file
 * @file: The file to पढ़ो
 * @page: The page of the file
 */

अटल पूर्णांक gfs2_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस __gfs2_पढ़ोpage(file, page);
पूर्ण

/**
 * gfs2_पूर्णांकernal_पढ़ो - पढ़ो an पूर्णांकernal file
 * @ip: The gfs2 inode
 * @buf: The buffer to fill
 * @pos: The file position
 * @size: The amount to पढ़ो
 *
 */

पूर्णांक gfs2_पूर्णांकernal_पढ़ो(काष्ठा gfs2_inode *ip, अक्षर *buf, loff_t *pos,
                       अचिन्हित size)
अणु
	काष्ठा address_space *mapping = ip->i_inode.i_mapping;
	अचिन्हित दीर्घ index = *pos >> PAGE_SHIFT;
	अचिन्हित offset = *pos & (PAGE_SIZE - 1);
	अचिन्हित copied = 0;
	अचिन्हित amt;
	काष्ठा page *page;
	व्योम *p;

	करो अणु
		amt = size - copied;
		अगर (offset + size > PAGE_SIZE)
			amt = PAGE_SIZE - offset;
		page = पढ़ो_cache_page(mapping, index, __gfs2_पढ़ोpage, शून्य);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);
		p = kmap_atomic(page);
		स_नकल(buf + copied, p + offset, amt);
		kunmap_atomic(p);
		put_page(page);
		copied += amt;
		index++;
		offset = 0;
	पूर्ण जबतक(copied < size);
	(*pos) += size;
	वापस size;
पूर्ण

/**
 * gfs2_पढ़ोahead - Read a bunch of pages at once
 * @rac: Read-ahead control काष्ठाure
 *
 * Some notes:
 * 1. This is only क्रम पढ़ोahead, so we can simply ignore any things
 *    which are slightly inconvenient (such as locking conflicts between
 *    the page lock and the glock) and वापस having करोne no I/O. Its
 *    obviously not something we'd want to करो on too regular a basis.
 *    Any I/O we ignore at this समय will be करोne via पढ़ोpage later.
 * 2. We करोn't handle stuffed files here we let पढ़ोpage करो the honours.
 * 3. mpage_पढ़ोahead() करोes most of the heavy lअगरting in the common हाल.
 * 4. gfs2_block_map() is relied upon to set BH_Boundary in the right places.
 */

अटल व्योम gfs2_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	काष्ठा inode *inode = rac->mapping->host;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);

	अगर (gfs2_is_stuffed(ip))
		;
	अन्यथा अगर (gfs2_is_jdata(ip))
		mpage_पढ़ोahead(rac, gfs2_block_map);
	अन्यथा
		iomap_पढ़ोahead(rac, &gfs2_iomap_ops);
पूर्ण

/**
 * adjust_fs_space - Adjusts the मुक्त space available due to gfs2_grow
 * @inode: the rindex inode
 */
व्योम adjust_fs_space(काष्ठा inode *inode)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	काष्ठा gfs2_inode *l_ip = GFS2_I(sdp->sd_sc_inode);
	काष्ठा gfs2_statfs_change_host *m_sc = &sdp->sd_statfs_master;
	काष्ठा gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;
	काष्ठा buffer_head *m_bh, *l_bh;
	u64 fs_total, new_मुक्त;

	अगर (gfs2_trans_begin(sdp, 2 * RES_STATFS, 0) != 0)
		वापस;

	/* Total up the file प्रणाली space, according to the latest rindex. */
	fs_total = gfs2_ri_total(sdp);
	अगर (gfs2_meta_inode_buffer(m_ip, &m_bh) != 0)
		जाओ out;

	spin_lock(&sdp->sd_statfs_spin);
	gfs2_statfs_change_in(m_sc, m_bh->b_data +
			      माप(काष्ठा gfs2_dinode));
	अगर (fs_total > (m_sc->sc_total + l_sc->sc_total))
		new_मुक्त = fs_total - (m_sc->sc_total + l_sc->sc_total);
	अन्यथा
		new_मुक्त = 0;
	spin_unlock(&sdp->sd_statfs_spin);
	fs_warn(sdp, "File system extended by %llu blocks.\n",
		(अचिन्हित दीर्घ दीर्घ)new_मुक्त);
	gfs2_statfs_change(sdp, new_मुक्त, new_मुक्त, 0);

	अगर (gfs2_meta_inode_buffer(l_ip, &l_bh) != 0)
		जाओ out2;
	update_statfs(sdp, m_bh, l_bh);
	brअन्यथा(l_bh);
out2:
	brअन्यथा(m_bh);
out:
	sdp->sd_rindex_uptodate = 0;
	gfs2_trans_end(sdp);
पूर्ण

/**
 * jdata_set_page_dirty - Page dirtying function
 * @page: The page to dirty
 *
 * Returns: 1 अगर it dirtyed the page, or 0 otherwise
 */
 
अटल पूर्णांक jdata_set_page_dirty(काष्ठा page *page)
अणु
	अगर (current->journal_info)
		SetPageChecked(page);
	वापस __set_page_dirty_buffers(page);
पूर्ण

/**
 * gfs2_bmap - Block map function
 * @mapping: Address space info
 * @lblock: The block to map
 *
 * Returns: The disk address क्रम the block or 0 on hole or error
 */

अटल sector_t gfs2_bmap(काष्ठा address_space *mapping, sector_t lblock)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(mapping->host);
	काष्ठा gfs2_holder i_gh;
	sector_t dblock = 0;
	पूर्णांक error;

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY, &i_gh);
	अगर (error)
		वापस 0;

	अगर (!gfs2_is_stuffed(ip))
		dblock = iomap_bmap(mapping, lblock, &gfs2_iomap_ops);

	gfs2_glock_dq_uninit(&i_gh);

	वापस dblock;
पूर्ण

अटल व्योम gfs2_discard(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh)
अणु
	काष्ठा gfs2_bufdata *bd;

	lock_buffer(bh);
	gfs2_log_lock(sdp);
	clear_buffer_dirty(bh);
	bd = bh->b_निजी;
	अगर (bd) अणु
		अगर (!list_empty(&bd->bd_list) && !buffer_pinned(bh))
			list_del_init(&bd->bd_list);
		अन्यथा अणु
			spin_lock(&sdp->sd_ail_lock);
			gfs2_हटाओ_from_journal(bh, REMOVE_JDATA);
			spin_unlock(&sdp->sd_ail_lock);
		पूर्ण
	पूर्ण
	bh->b_bdev = शून्य;
	clear_buffer_mapped(bh);
	clear_buffer_req(bh);
	clear_buffer_new(bh);
	gfs2_log_unlock(sdp);
	unlock_buffer(bh);
पूर्ण

अटल व्योम gfs2_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				अचिन्हित पूर्णांक length)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(page->mapping->host);
	अचिन्हित पूर्णांक stop = offset + length;
	पूर्णांक partial_page = (offset || length < PAGE_SIZE);
	काष्ठा buffer_head *bh, *head;
	अचिन्हित दीर्घ pos = 0;

	BUG_ON(!PageLocked(page));
	अगर (!partial_page)
		ClearPageChecked(page);
	अगर (!page_has_buffers(page))
		जाओ out;

	bh = head = page_buffers(page);
	करो अणु
		अगर (pos + bh->b_size > stop)
			वापस;

		अगर (offset <= pos)
			gfs2_discard(sdp, bh);
		pos += bh->b_size;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
out:
	अगर (!partial_page)
		try_to_release_page(page, 0);
पूर्ण

/**
 * gfs2_releasepage - मुक्त the metadata associated with a page
 * @page: the page that's being released
 * @gfp_mask: passed from Linux VFS, ignored by us
 *
 * Calls try_to_मुक्त_buffers() to मुक्त the buffers and put the page अगर the
 * buffers can be released.
 *
 * Returns: 1 अगर the page was put or अन्यथा 0
 */

पूर्णांक gfs2_releasepage(काष्ठा page *page, gfp_t gfp_mask)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा gfs2_sbd *sdp = gfs2_mapping2sbd(mapping);
	काष्ठा buffer_head *bh, *head;
	काष्ठा gfs2_bufdata *bd;

	अगर (!page_has_buffers(page))
		वापस 0;

	/*
	 * From xfs_vm_releasepage: mm accommodates an old ext3 हाल where
	 * clean pages might not have had the dirty bit cleared.  Thus, it can
	 * send actual dirty pages to ->releasepage() via shrink_active_list().
	 *
	 * As a workaround, we skip pages that contain dirty buffers below.
	 * Once ->releasepage isn't called on dirty pages anymore, we can warn
	 * on dirty buffers like we used to here again.
	 */

	gfs2_log_lock(sdp);
	head = bh = page_buffers(page);
	करो अणु
		अगर (atomic_पढ़ो(&bh->b_count))
			जाओ cannot_release;
		bd = bh->b_निजी;
		अगर (bd && bd->bd_tr)
			जाओ cannot_release;
		अगर (buffer_dirty(bh) || WARN_ON(buffer_pinned(bh)))
			जाओ cannot_release;
		bh = bh->b_this_page;
	पूर्ण जबतक(bh != head);

	head = bh = page_buffers(page);
	करो अणु
		bd = bh->b_निजी;
		अगर (bd) अणु
			gfs2_निश्चित_warn(sdp, bd->bd_bh == bh);
			bd->bd_bh = शून्य;
			bh->b_निजी = शून्य;
			/*
			 * The bd may still be queued as a revoke, in which
			 * हाल we must not dequeue nor मुक्त it.
			 */
			अगर (!bd->bd_blkno && !list_empty(&bd->bd_list))
				list_del_init(&bd->bd_list);
			अगर (list_empty(&bd->bd_list))
				kmem_cache_मुक्त(gfs2_bufdata_cachep, bd);
		पूर्ण

		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
	gfs2_log_unlock(sdp);

	वापस try_to_मुक्त_buffers(page);

cannot_release:
	gfs2_log_unlock(sdp);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा address_space_operations gfs2_aops = अणु
	.ग_लिखोpage = gfs2_ग_लिखोpage,
	.ग_लिखोpages = gfs2_ग_लिखोpages,
	.पढ़ोpage = gfs2_पढ़ोpage,
	.पढ़ोahead = gfs2_पढ़ोahead,
	.set_page_dirty = iomap_set_page_dirty,
	.releasepage = iomap_releasepage,
	.invalidatepage = iomap_invalidatepage,
	.bmap = gfs2_bmap,
	.direct_IO = noop_direct_IO,
	.migratepage = iomap_migrate_page,
	.is_partially_uptodate = iomap_is_partially_uptodate,
	.error_हटाओ_page = generic_error_हटाओ_page,
पूर्ण;

अटल स्थिर काष्ठा address_space_operations gfs2_jdata_aops = अणु
	.ग_लिखोpage = gfs2_jdata_ग_लिखोpage,
	.ग_लिखोpages = gfs2_jdata_ग_लिखोpages,
	.पढ़ोpage = gfs2_पढ़ोpage,
	.पढ़ोahead = gfs2_पढ़ोahead,
	.set_page_dirty = jdata_set_page_dirty,
	.bmap = gfs2_bmap,
	.invalidatepage = gfs2_invalidatepage,
	.releasepage = gfs2_releasepage,
	.is_partially_uptodate = block_is_partially_uptodate,
	.error_हटाओ_page = generic_error_हटाओ_page,
पूर्ण;

व्योम gfs2_set_aops(काष्ठा inode *inode)
अणु
	अगर (gfs2_is_jdata(GFS2_I(inode)))
		inode->i_mapping->a_ops = &gfs2_jdata_aops;
	अन्यथा
		inode->i_mapping->a_ops = &gfs2_aops;
पूर्ण
