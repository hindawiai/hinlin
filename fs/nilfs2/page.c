<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * page.c - buffer/page management specअगरic to NILFS
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi and Seiji Kihara.
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/swap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/list.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagevec.h>
#समावेश <linux/gfp.h>
#समावेश "nilfs.h"
#समावेश "page.h"
#समावेश "mdt.h"


#घोषणा NILFS_BUFFER_INHERENT_BITS					\
	(BIT(BH_Uptodate) | BIT(BH_Mapped) | BIT(BH_NILFS_Node) |	\
	 BIT(BH_NILFS_Volatile) | BIT(BH_NILFS_Checked))

अटल काष्ठा buffer_head *
__nilfs_get_page_block(काष्ठा page *page, अचिन्हित दीर्घ block, pgoff_t index,
		       पूर्णांक blkbits, अचिन्हित दीर्घ b_state)

अणु
	अचिन्हित दीर्घ first_block;
	काष्ठा buffer_head *bh;

	अगर (!page_has_buffers(page))
		create_empty_buffers(page, 1 << blkbits, b_state);

	first_block = (अचिन्हित दीर्घ)index << (PAGE_SHIFT - blkbits);
	bh = nilfs_page_get_nth_block(page, block - first_block);

	touch_buffer(bh);
	रुको_on_buffer(bh);
	वापस bh;
पूर्ण

काष्ठा buffer_head *nilfs_grab_buffer(काष्ठा inode *inode,
				      काष्ठा address_space *mapping,
				      अचिन्हित दीर्घ blkoff,
				      अचिन्हित दीर्घ b_state)
अणु
	पूर्णांक blkbits = inode->i_blkbits;
	pgoff_t index = blkoff >> (PAGE_SHIFT - blkbits);
	काष्ठा page *page;
	काष्ठा buffer_head *bh;

	page = grab_cache_page(mapping, index);
	अगर (unlikely(!page))
		वापस शून्य;

	bh = __nilfs_get_page_block(page, blkoff, index, blkbits, b_state);
	अगर (unlikely(!bh)) अणु
		unlock_page(page);
		put_page(page);
		वापस शून्य;
	पूर्ण
	वापस bh;
पूर्ण

/**
 * nilfs_क्रमget_buffer - discard dirty state
 * @bh: buffer head of the buffer to be discarded
 */
व्योम nilfs_क्रमget_buffer(काष्ठा buffer_head *bh)
अणु
	काष्ठा page *page = bh->b_page;
	स्थिर अचिन्हित दीर्घ clear_bits =
		(BIT(BH_Uptodate) | BIT(BH_Dirty) | BIT(BH_Mapped) |
		 BIT(BH_Async_Write) | BIT(BH_NILFS_Volatile) |
		 BIT(BH_NILFS_Checked) | BIT(BH_NILFS_Redirected));

	lock_buffer(bh);
	set_mask_bits(&bh->b_state, clear_bits, 0);
	अगर (nilfs_page_buffers_clean(page))
		__nilfs_clear_page_dirty(page);

	bh->b_blocknr = -1;
	ClearPageUptodate(page);
	ClearPageMappedToDisk(page);
	unlock_buffer(bh);
	brअन्यथा(bh);
पूर्ण

/**
 * nilfs_copy_buffer -- copy buffer data and flags
 * @dbh: destination buffer
 * @sbh: source buffer
 */
व्योम nilfs_copy_buffer(काष्ठा buffer_head *dbh, काष्ठा buffer_head *sbh)
अणु
	व्योम *kaddr0, *kaddr1;
	अचिन्हित दीर्घ bits;
	काष्ठा page *spage = sbh->b_page, *dpage = dbh->b_page;
	काष्ठा buffer_head *bh;

	kaddr0 = kmap_atomic(spage);
	kaddr1 = kmap_atomic(dpage);
	स_नकल(kaddr1 + bh_offset(dbh), kaddr0 + bh_offset(sbh), sbh->b_size);
	kunmap_atomic(kaddr1);
	kunmap_atomic(kaddr0);

	dbh->b_state = sbh->b_state & NILFS_BUFFER_INHERENT_BITS;
	dbh->b_blocknr = sbh->b_blocknr;
	dbh->b_bdev = sbh->b_bdev;

	bh = dbh;
	bits = sbh->b_state & (BIT(BH_Uptodate) | BIT(BH_Mapped));
	जबतक ((bh = bh->b_this_page) != dbh) अणु
		lock_buffer(bh);
		bits &= bh->b_state;
		unlock_buffer(bh);
	पूर्ण
	अगर (bits & BIT(BH_Uptodate))
		SetPageUptodate(dpage);
	अन्यथा
		ClearPageUptodate(dpage);
	अगर (bits & BIT(BH_Mapped))
		SetPageMappedToDisk(dpage);
	अन्यथा
		ClearPageMappedToDisk(dpage);
पूर्ण

/**
 * nilfs_page_buffers_clean - check अगर a page has dirty buffers or not.
 * @page: page to be checked
 *
 * nilfs_page_buffers_clean() वापसs zero अगर the page has dirty buffers.
 * Otherwise, it वापसs non-zero value.
 */
पूर्णांक nilfs_page_buffers_clean(काष्ठा page *page)
अणु
	काष्ठा buffer_head *bh, *head;

	bh = head = page_buffers(page);
	करो अणु
		अगर (buffer_dirty(bh))
			वापस 0;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
	वापस 1;
पूर्ण

व्योम nilfs_page_bug(काष्ठा page *page)
अणु
	काष्ठा address_space *m;
	अचिन्हित दीर्घ ino;

	अगर (unlikely(!page)) अणु
		prपूर्णांकk(KERN_CRIT "NILFS_PAGE_BUG(NULL)\n");
		वापस;
	पूर्ण

	m = page->mapping;
	ino = m ? m->host->i_ino : 0;

	prपूर्णांकk(KERN_CRIT "NILFS_PAGE_BUG(%p): cnt=%d index#=%llu flags=0x%lx "
	       "mapping=%p ino=%lu\n",
	       page, page_ref_count(page),
	       (अचिन्हित दीर्घ दीर्घ)page->index, page->flags, m, ino);

	अगर (page_has_buffers(page)) अणु
		काष्ठा buffer_head *bh, *head;
		पूर्णांक i = 0;

		bh = head = page_buffers(page);
		करो अणु
			prपूर्णांकk(KERN_CRIT
			       " BH[%d] %p: cnt=%d block#=%llu state=0x%lx\n",
			       i++, bh, atomic_पढ़ो(&bh->b_count),
			       (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, bh->b_state);
			bh = bh->b_this_page;
		पूर्ण जबतक (bh != head);
	पूर्ण
पूर्ण

/**
 * nilfs_copy_page -- copy the page with buffers
 * @dst: destination page
 * @src: source page
 * @copy_dirty: flag whether to copy dirty states on the page's buffer heads.
 *
 * This function is क्रम both data pages and btnode pages.  The dirty flag
 * should be treated by caller.  The page must not be under i/o.
 * Both src and dst page must be locked
 */
अटल व्योम nilfs_copy_page(काष्ठा page *dst, काष्ठा page *src, पूर्णांक copy_dirty)
अणु
	काष्ठा buffer_head *dbh, *dbufs, *sbh, *sbufs;
	अचिन्हित दीर्घ mask = NILFS_BUFFER_INHERENT_BITS;

	BUG_ON(PageWriteback(dst));

	sbh = sbufs = page_buffers(src);
	अगर (!page_has_buffers(dst))
		create_empty_buffers(dst, sbh->b_size, 0);

	अगर (copy_dirty)
		mask |= BIT(BH_Dirty);

	dbh = dbufs = page_buffers(dst);
	करो अणु
		lock_buffer(sbh);
		lock_buffer(dbh);
		dbh->b_state = sbh->b_state & mask;
		dbh->b_blocknr = sbh->b_blocknr;
		dbh->b_bdev = sbh->b_bdev;
		sbh = sbh->b_this_page;
		dbh = dbh->b_this_page;
	पूर्ण जबतक (dbh != dbufs);

	copy_highpage(dst, src);

	अगर (PageUptodate(src) && !PageUptodate(dst))
		SetPageUptodate(dst);
	अन्यथा अगर (!PageUptodate(src) && PageUptodate(dst))
		ClearPageUptodate(dst);
	अगर (PageMappedToDisk(src) && !PageMappedToDisk(dst))
		SetPageMappedToDisk(dst);
	अन्यथा अगर (!PageMappedToDisk(src) && PageMappedToDisk(dst))
		ClearPageMappedToDisk(dst);

	करो अणु
		unlock_buffer(sbh);
		unlock_buffer(dbh);
		sbh = sbh->b_this_page;
		dbh = dbh->b_this_page;
	पूर्ण जबतक (dbh != dbufs);
पूर्ण

पूर्णांक nilfs_copy_dirty_pages(काष्ठा address_space *dmap,
			   काष्ठा address_space *smap)
अणु
	काष्ठा pagevec pvec;
	अचिन्हित पूर्णांक i;
	pgoff_t index = 0;
	पूर्णांक err = 0;

	pagevec_init(&pvec);
repeat:
	अगर (!pagevec_lookup_tag(&pvec, smap, &index, PAGECACHE_TAG_सूचीTY))
		वापस 0;

	क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
		काष्ठा page *page = pvec.pages[i], *dpage;

		lock_page(page);
		अगर (unlikely(!PageDirty(page)))
			NILFS_PAGE_BUG(page, "inconsistent dirty state");

		dpage = grab_cache_page(dmap, page->index);
		अगर (unlikely(!dpage)) अणु
			/* No empty page is added to the page cache */
			err = -ENOMEM;
			unlock_page(page);
			अवरोध;
		पूर्ण
		अगर (unlikely(!page_has_buffers(page)))
			NILFS_PAGE_BUG(page,
				       "found empty page in dat page cache");

		nilfs_copy_page(dpage, page, 1);
		__set_page_dirty_nobuffers(dpage);

		unlock_page(dpage);
		put_page(dpage);
		unlock_page(page);
	पूर्ण
	pagevec_release(&pvec);
	cond_resched();

	अगर (likely(!err))
		जाओ repeat;
	वापस err;
पूर्ण

/**
 * nilfs_copy_back_pages -- copy back pages to original cache from shaकरोw cache
 * @dmap: destination page cache
 * @smap: source page cache
 *
 * No pages must be added to the cache during this process.
 * This must be ensured by the caller.
 */
व्योम nilfs_copy_back_pages(काष्ठा address_space *dmap,
			   काष्ठा address_space *smap)
अणु
	काष्ठा pagevec pvec;
	अचिन्हित पूर्णांक i, n;
	pgoff_t index = 0;

	pagevec_init(&pvec);
repeat:
	n = pagevec_lookup(&pvec, smap, &index);
	अगर (!n)
		वापस;

	क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
		काष्ठा page *page = pvec.pages[i], *dpage;
		pgoff_t offset = page->index;

		lock_page(page);
		dpage = find_lock_page(dmap, offset);
		अगर (dpage) अणु
			/* overग_लिखो existing page in the destination cache */
			WARN_ON(PageDirty(dpage));
			nilfs_copy_page(dpage, page, 0);
			unlock_page(dpage);
			put_page(dpage);
			/* Do we not need to हटाओ page from smap here? */
		पूर्ण अन्यथा अणु
			काष्ठा page *p;

			/* move the page to the destination cache */
			xa_lock_irq(&smap->i_pages);
			p = __xa_erase(&smap->i_pages, offset);
			WARN_ON(page != p);
			smap->nrpages--;
			xa_unlock_irq(&smap->i_pages);

			xa_lock_irq(&dmap->i_pages);
			p = __xa_store(&dmap->i_pages, offset, page, GFP_NOFS);
			अगर (unlikely(p)) अणु
				/* Probably -ENOMEM */
				page->mapping = शून्य;
				put_page(page);
			पूर्ण अन्यथा अणु
				page->mapping = dmap;
				dmap->nrpages++;
				अगर (PageDirty(page))
					__xa_set_mark(&dmap->i_pages, offset,
							PAGECACHE_TAG_सूचीTY);
			पूर्ण
			xa_unlock_irq(&dmap->i_pages);
		पूर्ण
		unlock_page(page);
	पूर्ण
	pagevec_release(&pvec);
	cond_resched();

	जाओ repeat;
पूर्ण

/**
 * nilfs_clear_dirty_pages - discard dirty pages in address space
 * @mapping: address space with dirty pages क्रम discarding
 * @silent: suppress [true] or prपूर्णांक [false] warning messages
 */
व्योम nilfs_clear_dirty_pages(काष्ठा address_space *mapping, bool silent)
अणु
	काष्ठा pagevec pvec;
	अचिन्हित पूर्णांक i;
	pgoff_t index = 0;

	pagevec_init(&pvec);

	जबतक (pagevec_lookup_tag(&pvec, mapping, &index,
					PAGECACHE_TAG_सूचीTY)) अणु
		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			काष्ठा page *page = pvec.pages[i];

			lock_page(page);
			nilfs_clear_dirty_page(page, silent);
			unlock_page(page);
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
पूर्ण

/**
 * nilfs_clear_dirty_page - discard dirty page
 * @page: dirty page that will be discarded
 * @silent: suppress [true] or prपूर्णांक [false] warning messages
 */
व्योम nilfs_clear_dirty_page(काष्ठा page *page, bool silent)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा super_block *sb = inode->i_sb;

	BUG_ON(!PageLocked(page));

	अगर (!silent)
		nilfs_warn(sb, "discard dirty page: offset=%lld, ino=%lu",
			   page_offset(page), inode->i_ino);

	ClearPageUptodate(page);
	ClearPageMappedToDisk(page);

	अगर (page_has_buffers(page)) अणु
		काष्ठा buffer_head *bh, *head;
		स्थिर अचिन्हित दीर्घ clear_bits =
			(BIT(BH_Uptodate) | BIT(BH_Dirty) | BIT(BH_Mapped) |
			 BIT(BH_Async_Write) | BIT(BH_NILFS_Volatile) |
			 BIT(BH_NILFS_Checked) | BIT(BH_NILFS_Redirected));

		bh = head = page_buffers(page);
		करो अणु
			lock_buffer(bh);
			अगर (!silent)
				nilfs_warn(sb,
					   "discard dirty block: blocknr=%llu, size=%zu",
					   (u64)bh->b_blocknr, bh->b_size);

			set_mask_bits(&bh->b_state, clear_bits, 0);
			unlock_buffer(bh);
		पूर्ण जबतक (bh = bh->b_this_page, bh != head);
	पूर्ण

	__nilfs_clear_page_dirty(page);
पूर्ण

अचिन्हित पूर्णांक nilfs_page_count_clean_buffers(काष्ठा page *page,
					    अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	अचिन्हित पूर्णांक block_start, block_end;
	काष्ठा buffer_head *bh, *head;
	अचिन्हित पूर्णांक nc = 0;

	क्रम (bh = head = page_buffers(page), block_start = 0;
	     bh != head || !block_start;
	     block_start = block_end, bh = bh->b_this_page) अणु
		block_end = block_start + bh->b_size;
		अगर (block_end > from && block_start < to && !buffer_dirty(bh))
			nc++;
	पूर्ण
	वापस nc;
पूर्ण

व्योम nilfs_mapping_init(काष्ठा address_space *mapping, काष्ठा inode *inode)
अणु
	mapping->host = inode;
	mapping->flags = 0;
	mapping_set_gfp_mask(mapping, GFP_NOFS);
	mapping->निजी_data = शून्य;
	mapping->a_ops = &empty_aops;
पूर्ण

/*
 * NILFS2 needs clear_page_dirty() in the following two हालs:
 *
 * 1) For B-tree node pages and data pages of the dat/gcdat, NILFS2 clears
 *    page dirty flags when it copies back pages from the shaकरोw cache
 *    (gcdat->अणुi_mapping,i_btnode_cacheपूर्ण) to its original cache
 *    (dat->अणुi_mapping,i_btnode_cacheपूर्ण).
 *
 * 2) Some B-tree operations like insertion or deletion may dispose buffers
 *    in dirty state, and this needs to cancel the dirty state of their pages.
 */
पूर्णांक __nilfs_clear_page_dirty(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page->mapping;

	अगर (mapping) अणु
		xa_lock_irq(&mapping->i_pages);
		अगर (test_bit(PG_dirty, &page->flags)) अणु
			__xa_clear_mark(&mapping->i_pages, page_index(page),
					     PAGECACHE_TAG_सूचीTY);
			xa_unlock_irq(&mapping->i_pages);
			वापस clear_page_dirty_क्रम_io(page);
		पूर्ण
		xa_unlock_irq(&mapping->i_pages);
		वापस 0;
	पूर्ण
	वापस TestClearPageDirty(page);
पूर्ण

/**
 * nilfs_find_uncommitted_extent - find extent of uncommitted data
 * @inode: inode
 * @start_blk: start block offset (in)
 * @blkoff: start offset of the found extent (out)
 *
 * This function searches an extent of buffers marked "delayed" which
 * starts from a block offset equal to or larger than @start_blk.  If
 * such an extent was found, this will store the start offset in
 * @blkoff and वापस its length in blocks.  Otherwise, zero is
 * वापसed.
 */
अचिन्हित दीर्घ nilfs_find_uncommitted_extent(काष्ठा inode *inode,
					    sector_t start_blk,
					    sector_t *blkoff)
अणु
	अचिन्हित पूर्णांक i;
	pgoff_t index;
	अचिन्हित पूर्णांक nblocks_in_page;
	अचिन्हित दीर्घ length = 0;
	sector_t b;
	काष्ठा pagevec pvec;
	काष्ठा page *page;

	अगर (inode->i_mapping->nrpages == 0)
		वापस 0;

	index = start_blk >> (PAGE_SHIFT - inode->i_blkbits);
	nblocks_in_page = 1U << (PAGE_SHIFT - inode->i_blkbits);

	pagevec_init(&pvec);

repeat:
	pvec.nr = find_get_pages_contig(inode->i_mapping, index, PAGEVEC_SIZE,
					pvec.pages);
	अगर (pvec.nr == 0)
		वापस length;

	अगर (length > 0 && pvec.pages[0]->index > index)
		जाओ out;

	b = pvec.pages[0]->index << (PAGE_SHIFT - inode->i_blkbits);
	i = 0;
	करो अणु
		page = pvec.pages[i];

		lock_page(page);
		अगर (page_has_buffers(page)) अणु
			काष्ठा buffer_head *bh, *head;

			bh = head = page_buffers(page);
			करो अणु
				अगर (b < start_blk)
					जारी;
				अगर (buffer_delay(bh)) अणु
					अगर (length == 0)
						*blkoff = b;
					length++;
				पूर्ण अन्यथा अगर (length > 0) अणु
					जाओ out_locked;
				पूर्ण
			पूर्ण जबतक (++b, bh = bh->b_this_page, bh != head);
		पूर्ण अन्यथा अणु
			अगर (length > 0)
				जाओ out_locked;

			b += nblocks_in_page;
		पूर्ण
		unlock_page(page);

	पूर्ण जबतक (++i < pagevec_count(&pvec));

	index = page->index + 1;
	pagevec_release(&pvec);
	cond_resched();
	जाओ repeat;

out_locked:
	unlock_page(page);
out:
	pagevec_release(&pvec);
	वापस length;
पूर्ण
