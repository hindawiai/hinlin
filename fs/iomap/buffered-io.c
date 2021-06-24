<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 Red Hat, Inc.
 * Copyright (C) 2016-2019 Christoph Hellwig.
 */
#समावेश <linux/module.h>
#समावेश <linux/compiler.h>
#समावेश <linux/fs.h>
#समावेश <linux/iomap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/uपन.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/dax.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/swap.h>
#समावेश <linux/bपन.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/migrate.h>
#समावेश "trace.h"

#समावेश "../internal.h"

/*
 * Structure allocated क्रम each page or THP when block size < page size
 * to track sub-page uptodate status and I/O completions.
 */
काष्ठा iomap_page अणु
	atomic_t		पढ़ो_bytes_pending;
	atomic_t		ग_लिखो_bytes_pending;
	spinlock_t		uptodate_lock;
	अचिन्हित दीर्घ		uptodate[];
पूर्ण;

अटल अंतरभूत काष्ठा iomap_page *to_iomap_page(काष्ठा page *page)
अणु
	/*
	 * per-block data is stored in the head page.  Callers should
	 * not be dealing with tail pages (and अगर they are, they can
	 * call thp_head() first.
	 */
	VM_BUG_ON_PGFLAGS(PageTail(page), page);

	अगर (page_has_निजी(page))
		वापस (काष्ठा iomap_page *)page_निजी(page);
	वापस शून्य;
पूर्ण

अटल काष्ठा bio_set iomap_ioend_bioset;

अटल काष्ठा iomap_page *
iomap_page_create(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा iomap_page *iop = to_iomap_page(page);
	अचिन्हित पूर्णांक nr_blocks = i_blocks_per_page(inode, page);

	अगर (iop || nr_blocks <= 1)
		वापस iop;

	iop = kzalloc(काष्ठा_size(iop, uptodate, BITS_TO_LONGS(nr_blocks)),
			GFP_NOFS | __GFP_NOFAIL);
	spin_lock_init(&iop->uptodate_lock);
	अगर (PageUptodate(page))
		biपंचांगap_fill(iop->uptodate, nr_blocks);
	attach_page_निजी(page, iop);
	वापस iop;
पूर्ण

अटल व्योम
iomap_page_release(काष्ठा page *page)
अणु
	काष्ठा iomap_page *iop = detach_page_निजी(page);
	अचिन्हित पूर्णांक nr_blocks = i_blocks_per_page(page->mapping->host, page);

	अगर (!iop)
		वापस;
	WARN_ON_ONCE(atomic_पढ़ो(&iop->पढ़ो_bytes_pending));
	WARN_ON_ONCE(atomic_पढ़ो(&iop->ग_लिखो_bytes_pending));
	WARN_ON_ONCE(biपंचांगap_full(iop->uptodate, nr_blocks) !=
			PageUptodate(page));
	kमुक्त(iop);
पूर्ण

/*
 * Calculate the range inside the page that we actually need to पढ़ो.
 */
अटल व्योम
iomap_adjust_पढ़ो_range(काष्ठा inode *inode, काष्ठा iomap_page *iop,
		loff_t *pos, loff_t length, अचिन्हित *offp, अचिन्हित *lenp)
अणु
	loff_t orig_pos = *pos;
	loff_t isize = i_size_पढ़ो(inode);
	अचिन्हित block_bits = inode->i_blkbits;
	अचिन्हित block_size = (1 << block_bits);
	अचिन्हित poff = offset_in_page(*pos);
	अचिन्हित plen = min_t(loff_t, PAGE_SIZE - poff, length);
	अचिन्हित first = poff >> block_bits;
	अचिन्हित last = (poff + plen - 1) >> block_bits;

	/*
	 * If the block size is smaller than the page size we need to check the
	 * per-block uptodate status and adjust the offset and length अगर needed
	 * to aव्योम पढ़ोing in alपढ़ोy uptodate ranges.
	 */
	अगर (iop) अणु
		अचिन्हित पूर्णांक i;

		/* move क्रमward क्रम each leading block marked uptodate */
		क्रम (i = first; i <= last; i++) अणु
			अगर (!test_bit(i, iop->uptodate))
				अवरोध;
			*pos += block_size;
			poff += block_size;
			plen -= block_size;
			first++;
		पूर्ण

		/* truncate len अगर we find any trailing uptodate block(s) */
		क्रम ( ; i <= last; i++) अणु
			अगर (test_bit(i, iop->uptodate)) अणु
				plen -= (last - i + 1) * block_size;
				last = i - 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If the extent spans the block that contains the i_size we need to
	 * handle both halves separately so that we properly zero data in the
	 * page cache क्रम blocks that are entirely outside of i_size.
	 */
	अगर (orig_pos <= isize && orig_pos + length > isize) अणु
		अचिन्हित end = offset_in_page(isize - 1) >> block_bits;

		अगर (first <= end && last > end)
			plen -= (last - end) * block_size;
	पूर्ण

	*offp = poff;
	*lenp = plen;
पूर्ण

अटल व्योम
iomap_iop_set_range_uptodate(काष्ठा page *page, अचिन्हित off, अचिन्हित len)
अणु
	काष्ठा iomap_page *iop = to_iomap_page(page);
	काष्ठा inode *inode = page->mapping->host;
	अचिन्हित first = off >> inode->i_blkbits;
	अचिन्हित last = (off + len - 1) >> inode->i_blkbits;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iop->uptodate_lock, flags);
	biपंचांगap_set(iop->uptodate, first, last - first + 1);
	अगर (biपंचांगap_full(iop->uptodate, i_blocks_per_page(inode, page)))
		SetPageUptodate(page);
	spin_unlock_irqrestore(&iop->uptodate_lock, flags);
पूर्ण

अटल व्योम
iomap_set_range_uptodate(काष्ठा page *page, अचिन्हित off, अचिन्हित len)
अणु
	अगर (PageError(page))
		वापस;

	अगर (page_has_निजी(page))
		iomap_iop_set_range_uptodate(page, off, len);
	अन्यथा
		SetPageUptodate(page);
पूर्ण

अटल व्योम
iomap_पढ़ो_page_end_io(काष्ठा bio_vec *bvec, पूर्णांक error)
अणु
	काष्ठा page *page = bvec->bv_page;
	काष्ठा iomap_page *iop = to_iomap_page(page);

	अगर (unlikely(error)) अणु
		ClearPageUptodate(page);
		SetPageError(page);
	पूर्ण अन्यथा अणु
		iomap_set_range_uptodate(page, bvec->bv_offset, bvec->bv_len);
	पूर्ण

	अगर (!iop || atomic_sub_and_test(bvec->bv_len, &iop->पढ़ो_bytes_pending))
		unlock_page(page);
पूर्ण

अटल व्योम
iomap_पढ़ो_end_io(काष्ठा bio *bio)
अणु
	पूर्णांक error = blk_status_to_त्रुटि_सं(bio->bi_status);
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all)
		iomap_पढ़ो_page_end_io(bvec, error);
	bio_put(bio);
पूर्ण

काष्ठा iomap_पढ़ोpage_ctx अणु
	काष्ठा page		*cur_page;
	bool			cur_page_in_bio;
	काष्ठा bio		*bio;
	काष्ठा पढ़ोahead_control *rac;
पूर्ण;

अटल व्योम
iomap_पढ़ो_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *page,
		काष्ठा iomap *iomap)
अणु
	माप_प्रकार size = i_size_पढ़ो(inode);
	व्योम *addr;

	अगर (PageUptodate(page))
		वापस;

	BUG_ON(page->index);
	BUG_ON(size > PAGE_SIZE - offset_in_page(iomap->अंतरभूत_data));

	addr = kmap_atomic(page);
	स_नकल(addr, iomap->अंतरभूत_data, size);
	स_रखो(addr + size, 0, PAGE_SIZE - size);
	kunmap_atomic(addr);
	SetPageUptodate(page);
पूर्ण

अटल अंतरभूत bool iomap_block_needs_zeroing(काष्ठा inode *inode,
		काष्ठा iomap *iomap, loff_t pos)
अणु
	वापस iomap->type != IOMAP_MAPPED ||
		(iomap->flags & IOMAP_F_NEW) ||
		pos >= i_size_पढ़ो(inode);
पूर्ण

अटल loff_t
iomap_पढ़ोpage_actor(काष्ठा inode *inode, loff_t pos, loff_t length, व्योम *data,
		काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	काष्ठा iomap_पढ़ोpage_ctx *ctx = data;
	काष्ठा page *page = ctx->cur_page;
	काष्ठा iomap_page *iop = iomap_page_create(inode, page);
	bool same_page = false, is_contig = false;
	loff_t orig_pos = pos;
	अचिन्हित poff, plen;
	sector_t sector;

	अगर (iomap->type == IOMAP_INLINE) अणु
		WARN_ON_ONCE(pos);
		iomap_पढ़ो_अंतरभूत_data(inode, page, iomap);
		वापस PAGE_SIZE;
	पूर्ण

	/* zero post-eof blocks as the page may be mapped */
	iomap_adjust_पढ़ो_range(inode, iop, &pos, length, &poff, &plen);
	अगर (plen == 0)
		जाओ करोne;

	अगर (iomap_block_needs_zeroing(inode, iomap, pos)) अणु
		zero_user(page, poff, plen);
		iomap_set_range_uptodate(page, poff, plen);
		जाओ करोne;
	पूर्ण

	ctx->cur_page_in_bio = true;
	अगर (iop)
		atomic_add(plen, &iop->पढ़ो_bytes_pending);

	/* Try to merge पूर्णांकo a previous segment अगर we can */
	sector = iomap_sector(iomap, pos);
	अगर (ctx->bio && bio_end_sector(ctx->bio) == sector) अणु
		अगर (__bio_try_merge_page(ctx->bio, page, plen, poff,
				&same_page))
			जाओ करोne;
		is_contig = true;
	पूर्ण

	अगर (!is_contig || bio_full(ctx->bio, plen)) अणु
		gfp_t gfp = mapping_gfp_स्थिरraपूर्णांक(page->mapping, GFP_KERNEL);
		gfp_t orig_gfp = gfp;
		अचिन्हित पूर्णांक nr_vecs = DIV_ROUND_UP(length, PAGE_SIZE);

		अगर (ctx->bio)
			submit_bio(ctx->bio);

		अगर (ctx->rac) /* same as पढ़ोahead_gfp_mask */
			gfp |= __GFP_NORETRY | __GFP_NOWARN;
		ctx->bio = bio_alloc(gfp, bio_max_segs(nr_vecs));
		/*
		 * If the bio_alloc fails, try it again क्रम a single page to
		 * aव्योम having to deal with partial page पढ़ोs.  This emulates
		 * what करो_mpage_पढ़ोpage करोes.
		 */
		अगर (!ctx->bio)
			ctx->bio = bio_alloc(orig_gfp, 1);
		ctx->bio->bi_opf = REQ_OP_READ;
		अगर (ctx->rac)
			ctx->bio->bi_opf |= REQ_RAHEAD;
		ctx->bio->bi_iter.bi_sector = sector;
		bio_set_dev(ctx->bio, iomap->bdev);
		ctx->bio->bi_end_io = iomap_पढ़ो_end_io;
	पूर्ण

	bio_add_page(ctx->bio, page, plen, poff);
करोne:
	/*
	 * Move the caller beyond our range so that it keeps making progress.
	 * For that we have to include any leading non-uptodate ranges, but
	 * we can skip trailing ones as they will be handled in the next
	 * iteration.
	 */
	वापस pos - orig_pos + plen;
पूर्ण

पूर्णांक
iomap_पढ़ोpage(काष्ठा page *page, स्थिर काष्ठा iomap_ops *ops)
अणु
	काष्ठा iomap_पढ़ोpage_ctx ctx = अणु .cur_page = page पूर्ण;
	काष्ठा inode *inode = page->mapping->host;
	अचिन्हित poff;
	loff_t ret;

	trace_iomap_पढ़ोpage(page->mapping->host, 1);

	क्रम (poff = 0; poff < PAGE_SIZE; poff += ret) अणु
		ret = iomap_apply(inode, page_offset(page) + poff,
				PAGE_SIZE - poff, 0, ops, &ctx,
				iomap_पढ़ोpage_actor);
		अगर (ret <= 0) अणु
			WARN_ON_ONCE(ret == 0);
			SetPageError(page);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ctx.bio) अणु
		submit_bio(ctx.bio);
		WARN_ON_ONCE(!ctx.cur_page_in_bio);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(ctx.cur_page_in_bio);
		unlock_page(page);
	पूर्ण

	/*
	 * Just like mpage_पढ़ोahead and block_पढ़ो_full_page we always
	 * वापस 0 and just mark the page as PageError on errors.  This
	 * should be cleaned up all through the stack eventually.
	 */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_पढ़ोpage);

अटल loff_t
iomap_पढ़ोahead_actor(काष्ठा inode *inode, loff_t pos, loff_t length,
		व्योम *data, काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	काष्ठा iomap_पढ़ोpage_ctx *ctx = data;
	loff_t करोne, ret;

	क्रम (करोne = 0; करोne < length; करोne += ret) अणु
		अगर (ctx->cur_page && offset_in_page(pos + करोne) == 0) अणु
			अगर (!ctx->cur_page_in_bio)
				unlock_page(ctx->cur_page);
			put_page(ctx->cur_page);
			ctx->cur_page = शून्य;
		पूर्ण
		अगर (!ctx->cur_page) अणु
			ctx->cur_page = पढ़ोahead_page(ctx->rac);
			ctx->cur_page_in_bio = false;
		पूर्ण
		ret = iomap_पढ़ोpage_actor(inode, pos + करोne, length - करोne,
				ctx, iomap, srcmap);
	पूर्ण

	वापस करोne;
पूर्ण

/**
 * iomap_पढ़ोahead - Attempt to पढ़ो pages from a file.
 * @rac: Describes the pages to be पढ़ो.
 * @ops: The operations vector क्रम the fileप्रणाली.
 *
 * This function is क्रम fileप्रणालीs to call to implement their पढ़ोahead
 * address_space operation.
 *
 * Context: The @ops callbacks may submit I/O (eg to पढ़ो the addresses of
 * blocks from disc), and may रुको क्रम it.  The caller may be trying to
 * access a dअगरferent page, and so sleeping excessively should be aव्योमed.
 * It may allocate memory, but should aव्योम costly allocations.  This
 * function is called with meदो_स्मृति_nofs set, so allocations will not cause
 * the fileप्रणाली to be reentered.
 */
व्योम iomap_पढ़ोahead(काष्ठा पढ़ोahead_control *rac, स्थिर काष्ठा iomap_ops *ops)
अणु
	काष्ठा inode *inode = rac->mapping->host;
	loff_t pos = पढ़ोahead_pos(rac);
	माप_प्रकार length = पढ़ोahead_length(rac);
	काष्ठा iomap_पढ़ोpage_ctx ctx = अणु
		.rac	= rac,
	पूर्ण;

	trace_iomap_पढ़ोahead(inode, पढ़ोahead_count(rac));

	जबतक (length > 0) अणु
		sमाप_प्रकार ret = iomap_apply(inode, pos, length, 0, ops,
				&ctx, iomap_पढ़ोahead_actor);
		अगर (ret <= 0) अणु
			WARN_ON_ONCE(ret == 0);
			अवरोध;
		पूर्ण
		pos += ret;
		length -= ret;
	पूर्ण

	अगर (ctx.bio)
		submit_bio(ctx.bio);
	अगर (ctx.cur_page) अणु
		अगर (!ctx.cur_page_in_bio)
			unlock_page(ctx.cur_page);
		put_page(ctx.cur_page);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(iomap_पढ़ोahead);

/*
 * iomap_is_partially_uptodate checks whether blocks within a page are
 * uptodate or not.
 *
 * Returns true अगर all blocks which correspond to a file portion
 * we want to पढ़ो within the page are uptodate.
 */
पूर्णांक
iomap_is_partially_uptodate(काष्ठा page *page, अचिन्हित दीर्घ from,
		अचिन्हित दीर्घ count)
अणु
	काष्ठा iomap_page *iop = to_iomap_page(page);
	काष्ठा inode *inode = page->mapping->host;
	अचिन्हित len, first, last;
	अचिन्हित i;

	/* Limit range to one page */
	len = min_t(अचिन्हित, PAGE_SIZE - from, count);

	/* First and last blocks in range within page */
	first = from >> inode->i_blkbits;
	last = (from + len - 1) >> inode->i_blkbits;

	अगर (iop) अणु
		क्रम (i = first; i <= last; i++)
			अगर (!test_bit(i, iop->uptodate))
				वापस 0;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_is_partially_uptodate);

पूर्णांक
iomap_releasepage(काष्ठा page *page, gfp_t gfp_mask)
अणु
	trace_iomap_releasepage(page->mapping->host, page_offset(page),
			PAGE_SIZE);

	/*
	 * mm accommodates an old ext3 हाल where clean pages might not have had
	 * the dirty bit cleared. Thus, it can send actual dirty pages to
	 * ->releasepage() via shrink_active_list(), skip those here.
	 */
	अगर (PageDirty(page) || PageWriteback(page))
		वापस 0;
	iomap_page_release(page);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_releasepage);

व्योम
iomap_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len)
अणु
	trace_iomap_invalidatepage(page->mapping->host, offset, len);

	/*
	 * If we are invalidating the entire page, clear the dirty state from it
	 * and release it to aव्योम unnecessary buildup of the LRU.
	 */
	अगर (offset == 0 && len == PAGE_SIZE) अणु
		WARN_ON_ONCE(PageWriteback(page));
		cancel_dirty_page(page);
		iomap_page_release(page);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(iomap_invalidatepage);

#अगर_घोषित CONFIG_MIGRATION
पूर्णांक
iomap_migrate_page(काष्ठा address_space *mapping, काष्ठा page *newpage,
		काष्ठा page *page, क्रमागत migrate_mode mode)
अणु
	पूर्णांक ret;

	ret = migrate_page_move_mapping(mapping, newpage, page, 0);
	अगर (ret != MIGRATEPAGE_SUCCESS)
		वापस ret;

	अगर (page_has_निजी(page))
		attach_page_निजी(newpage, detach_page_निजी(page));

	अगर (mode != MIGRATE_SYNC_NO_COPY)
		migrate_page_copy(newpage, page);
	अन्यथा
		migrate_page_states(newpage, page);
	वापस MIGRATEPAGE_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_migrate_page);
#पूर्ण_अगर /* CONFIG_MIGRATION */

क्रमागत अणु
	IOMAP_WRITE_F_UNSHARE		= (1 << 0),
पूर्ण;

अटल व्योम
iomap_ग_लिखो_failed(काष्ठा inode *inode, loff_t pos, अचिन्हित len)
अणु
	loff_t i_size = i_size_पढ़ो(inode);

	/*
	 * Only truncate newly allocated pages beyoned खातापूर्ण, even अगर the
	 * ग_लिखो started inside the existing inode size.
	 */
	अगर (pos + len > i_size)
		truncate_pagecache_range(inode, max(pos, i_size), pos + len);
पूर्ण

अटल पूर्णांक
iomap_पढ़ो_page_sync(loff_t block_start, काष्ठा page *page, अचिन्हित poff,
		अचिन्हित plen, काष्ठा iomap *iomap)
अणु
	काष्ठा bio_vec bvec;
	काष्ठा bio bio;

	bio_init(&bio, &bvec, 1);
	bio.bi_opf = REQ_OP_READ;
	bio.bi_iter.bi_sector = iomap_sector(iomap, block_start);
	bio_set_dev(&bio, iomap->bdev);
	__bio_add_page(&bio, page, plen, poff);
	वापस submit_bio_रुको(&bio);
पूर्ण

अटल पूर्णांक
__iomap_ग_लिखो_begin(काष्ठा inode *inode, loff_t pos, अचिन्हित len, पूर्णांक flags,
		काष्ठा page *page, काष्ठा iomap *srcmap)
अणु
	काष्ठा iomap_page *iop = iomap_page_create(inode, page);
	loff_t block_size = i_blocksize(inode);
	loff_t block_start = round_करोwn(pos, block_size);
	loff_t block_end = round_up(pos + len, block_size);
	अचिन्हित from = offset_in_page(pos), to = from + len, poff, plen;

	अगर (PageUptodate(page))
		वापस 0;
	ClearPageError(page);

	करो अणु
		iomap_adjust_पढ़ो_range(inode, iop, &block_start,
				block_end - block_start, &poff, &plen);
		अगर (plen == 0)
			अवरोध;

		अगर (!(flags & IOMAP_WRITE_F_UNSHARE) &&
		    (from <= poff || from >= poff + plen) &&
		    (to <= poff || to >= poff + plen))
			जारी;

		अगर (iomap_block_needs_zeroing(inode, srcmap, block_start)) अणु
			अगर (WARN_ON_ONCE(flags & IOMAP_WRITE_F_UNSHARE))
				वापस -EIO;
			zero_user_segments(page, poff, from, to, poff + plen);
		पूर्ण अन्यथा अणु
			पूर्णांक status = iomap_पढ़ो_page_sync(block_start, page,
					poff, plen, srcmap);
			अगर (status)
				वापस status;
		पूर्ण
		iomap_set_range_uptodate(page, poff, plen);
	पूर्ण जबतक ((block_start += plen) < block_end);

	वापस 0;
पूर्ण

अटल पूर्णांक
iomap_ग_लिखो_begin(काष्ठा inode *inode, loff_t pos, अचिन्हित len, अचिन्हित flags,
		काष्ठा page **pagep, काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	स्थिर काष्ठा iomap_page_ops *page_ops = iomap->page_ops;
	काष्ठा page *page;
	पूर्णांक status = 0;

	BUG_ON(pos + len > iomap->offset + iomap->length);
	अगर (srcmap != iomap)
		BUG_ON(pos + len > srcmap->offset + srcmap->length);

	अगर (fatal_संकेत_pending(current))
		वापस -EINTR;

	अगर (page_ops && page_ops->page_prepare) अणु
		status = page_ops->page_prepare(inode, pos, len, iomap);
		अगर (status)
			वापस status;
	पूर्ण

	page = grab_cache_page_ग_लिखो_begin(inode->i_mapping, pos >> PAGE_SHIFT,
			AOP_FLAG_NOFS);
	अगर (!page) अणु
		status = -ENOMEM;
		जाओ out_no_page;
	पूर्ण

	अगर (srcmap->type == IOMAP_INLINE)
		iomap_पढ़ो_अंतरभूत_data(inode, page, srcmap);
	अन्यथा अगर (iomap->flags & IOMAP_F_BUFFER_HEAD)
		status = __block_ग_लिखो_begin_पूर्णांक(page, pos, len, शून्य, srcmap);
	अन्यथा
		status = __iomap_ग_लिखो_begin(inode, pos, len, flags, page,
				srcmap);

	अगर (unlikely(status))
		जाओ out_unlock;

	*pagep = page;
	वापस 0;

out_unlock:
	unlock_page(page);
	put_page(page);
	iomap_ग_लिखो_failed(inode, pos, len);

out_no_page:
	अगर (page_ops && page_ops->page_करोne)
		page_ops->page_करोne(inode, pos, 0, शून्य, iomap);
	वापस status;
पूर्ण

पूर्णांक
iomap_set_page_dirty(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping(page);
	पूर्णांक newly_dirty;

	अगर (unlikely(!mapping))
		वापस !TestSetPageDirty(page);

	/*
	 * Lock out page's memcg migration to keep PageDirty
	 * synchronized with per-memcg dirty page counters.
	 */
	lock_page_memcg(page);
	newly_dirty = !TestSetPageDirty(page);
	अगर (newly_dirty)
		__set_page_dirty(page, mapping, 0);
	unlock_page_memcg(page);

	अगर (newly_dirty)
		__mark_inode_dirty(mapping->host, I_सूचीTY_PAGES);
	वापस newly_dirty;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_set_page_dirty);

अटल माप_प्रकार __iomap_ग_लिखो_end(काष्ठा inode *inode, loff_t pos, माप_प्रकार len,
		माप_प्रकार copied, काष्ठा page *page)
अणु
	flush_dcache_page(page);

	/*
	 * The blocks that were entirely written will now be uptodate, so we
	 * करोn't have to worry about a पढ़ोpage पढ़ोing them and overwriting a
	 * partial ग_लिखो.  However अगर we have encountered a लघु ग_लिखो and only
	 * partially written पूर्णांकo a block, it will not be marked uptodate, so a
	 * पढ़ोpage might come in and destroy our partial ग_लिखो.
	 *
	 * Do the simplest thing, and just treat any लघु ग_लिखो to a non
	 * uptodate page as a zero-length ग_लिखो, and क्रमce the caller to reकरो
	 * the whole thing.
	 */
	अगर (unlikely(copied < len && !PageUptodate(page)))
		वापस 0;
	iomap_set_range_uptodate(page, offset_in_page(pos), len);
	iomap_set_page_dirty(page);
	वापस copied;
पूर्ण

अटल माप_प्रकार iomap_ग_लिखो_end_अंतरभूत(काष्ठा inode *inode, काष्ठा page *page,
		काष्ठा iomap *iomap, loff_t pos, माप_प्रकार copied)
अणु
	व्योम *addr;

	WARN_ON_ONCE(!PageUptodate(page));
	BUG_ON(pos + copied > PAGE_SIZE - offset_in_page(iomap->अंतरभूत_data));

	flush_dcache_page(page);
	addr = kmap_atomic(page);
	स_नकल(iomap->अंतरभूत_data + pos, addr + pos, copied);
	kunmap_atomic(addr);

	mark_inode_dirty(inode);
	वापस copied;
पूर्ण

/* Returns the number of bytes copied.  May be 0.  Cannot be an त्रुटि_सं. */
अटल माप_प्रकार iomap_ग_लिखो_end(काष्ठा inode *inode, loff_t pos, माप_प्रकार len,
		माप_प्रकार copied, काष्ठा page *page, काष्ठा iomap *iomap,
		काष्ठा iomap *srcmap)
अणु
	स्थिर काष्ठा iomap_page_ops *page_ops = iomap->page_ops;
	loff_t old_size = inode->i_size;
	माप_प्रकार ret;

	अगर (srcmap->type == IOMAP_INLINE) अणु
		ret = iomap_ग_लिखो_end_अंतरभूत(inode, page, iomap, pos, copied);
	पूर्ण अन्यथा अगर (srcmap->flags & IOMAP_F_BUFFER_HEAD) अणु
		ret = block_ग_लिखो_end(शून्य, inode->i_mapping, pos, len, copied,
				page, शून्य);
	पूर्ण अन्यथा अणु
		ret = __iomap_ग_लिखो_end(inode, pos, len, copied, page);
	पूर्ण

	/*
	 * Update the in-memory inode size after copying the data पूर्णांकo the page
	 * cache.  It's up to the file प्रणाली to ग_लिखो the updated size to disk,
	 * preferably after I/O completion so that no stale data is exposed.
	 */
	अगर (pos + ret > old_size) अणु
		i_size_ग_लिखो(inode, pos + ret);
		iomap->flags |= IOMAP_F_SIZE_CHANGED;
	पूर्ण
	unlock_page(page);

	अगर (old_size < pos)
		pagecache_isize_extended(inode, old_size, pos);
	अगर (page_ops && page_ops->page_करोne)
		page_ops->page_करोne(inode, pos, ret, page, iomap);
	put_page(page);

	अगर (ret < len)
		iomap_ग_लिखो_failed(inode, pos, len);
	वापस ret;
पूर्ण

अटल loff_t
iomap_ग_लिखो_actor(काष्ठा inode *inode, loff_t pos, loff_t length, व्योम *data,
		काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	काष्ठा iov_iter *i = data;
	दीर्घ status = 0;
	sमाप_प्रकार written = 0;

	करो अणु
		काष्ठा page *page;
		अचिन्हित दीर्घ offset;	/* Offset पूर्णांकo pagecache page */
		अचिन्हित दीर्घ bytes;	/* Bytes to ग_लिखो to page */
		माप_प्रकार copied;		/* Bytes copied from user */

		offset = offset_in_page(pos);
		bytes = min_t(अचिन्हित दीर्घ, PAGE_SIZE - offset,
						iov_iter_count(i));
again:
		अगर (bytes > length)
			bytes = length;

		/*
		 * Bring in the user page that we will copy from _first_.
		 * Otherwise there's a nasty deadlock on copying from the
		 * same page as we're writing to, without it being marked
		 * up-to-date.
		 *
		 * Not only is this an optimisation, but it is also required
		 * to check that the address is actually valid, when atomic
		 * usercopies are used, below.
		 */
		अगर (unlikely(iov_iter_fault_in_पढ़ोable(i, bytes))) अणु
			status = -EFAULT;
			अवरोध;
		पूर्ण

		status = iomap_ग_लिखो_begin(inode, pos, bytes, 0, &page, iomap,
				srcmap);
		अगर (unlikely(status))
			अवरोध;

		अगर (mapping_writably_mapped(inode->i_mapping))
			flush_dcache_page(page);

		copied = iov_iter_copy_from_user_atomic(page, i, offset, bytes);

		copied = iomap_ग_लिखो_end(inode, pos, bytes, copied, page, iomap,
				srcmap);

		cond_resched();

		iov_iter_advance(i, copied);
		अगर (unlikely(copied == 0)) अणु
			/*
			 * If we were unable to copy any data at all, we must
			 * fall back to a single segment length ग_लिखो.
			 *
			 * If we didn't fallback here, we could livelock
			 * because not all segments in the iov can be copied at
			 * once without a pagefault.
			 */
			bytes = min_t(अचिन्हित दीर्घ, PAGE_SIZE - offset,
						iov_iter_single_seg_count(i));
			जाओ again;
		पूर्ण
		pos += copied;
		written += copied;
		length -= copied;

		balance_dirty_pages_ratelimited(inode->i_mapping);
	पूर्ण जबतक (iov_iter_count(i) && length);

	वापस written ? written : status;
पूर्ण

sमाप_प्रकार
iomap_file_buffered_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		स्थिर काष्ठा iomap_ops *ops)
अणु
	काष्ठा inode *inode = iocb->ki_filp->f_mapping->host;
	loff_t pos = iocb->ki_pos, ret = 0, written = 0;

	जबतक (iov_iter_count(iter)) अणु
		ret = iomap_apply(inode, pos, iov_iter_count(iter),
				IOMAP_WRITE, ops, iter, iomap_ग_लिखो_actor);
		अगर (ret <= 0)
			अवरोध;
		pos += ret;
		written += ret;
	पूर्ण

	वापस written ? written : ret;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_file_buffered_ग_लिखो);

अटल loff_t
iomap_unshare_actor(काष्ठा inode *inode, loff_t pos, loff_t length, व्योम *data,
		काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	दीर्घ status = 0;
	loff_t written = 0;

	/* करोn't bother with blocks that are not shared to start with */
	अगर (!(iomap->flags & IOMAP_F_SHARED))
		वापस length;
	/* करोn't bother with holes or unwritten extents */
	अगर (srcmap->type == IOMAP_HOLE || srcmap->type == IOMAP_UNWRITTEN)
		वापस length;

	करो अणु
		अचिन्हित दीर्घ offset = offset_in_page(pos);
		अचिन्हित दीर्घ bytes = min_t(loff_t, PAGE_SIZE - offset, length);
		काष्ठा page *page;

		status = iomap_ग_लिखो_begin(inode, pos, bytes,
				IOMAP_WRITE_F_UNSHARE, &page, iomap, srcmap);
		अगर (unlikely(status))
			वापस status;

		status = iomap_ग_लिखो_end(inode, pos, bytes, bytes, page, iomap,
				srcmap);
		अगर (WARN_ON_ONCE(status == 0))
			वापस -EIO;

		cond_resched();

		pos += status;
		written += status;
		length -= status;

		balance_dirty_pages_ratelimited(inode->i_mapping);
	पूर्ण जबतक (length);

	वापस written;
पूर्ण

पूर्णांक
iomap_file_unshare(काष्ठा inode *inode, loff_t pos, loff_t len,
		स्थिर काष्ठा iomap_ops *ops)
अणु
	loff_t ret;

	जबतक (len) अणु
		ret = iomap_apply(inode, pos, len, IOMAP_WRITE, ops, शून्य,
				iomap_unshare_actor);
		अगर (ret <= 0)
			वापस ret;
		pos += ret;
		len -= ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_file_unshare);

अटल s64 iomap_zero(काष्ठा inode *inode, loff_t pos, u64 length,
		काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	काष्ठा page *page;
	पूर्णांक status;
	अचिन्हित offset = offset_in_page(pos);
	अचिन्हित bytes = min_t(u64, PAGE_SIZE - offset, length);

	status = iomap_ग_लिखो_begin(inode, pos, bytes, 0, &page, iomap, srcmap);
	अगर (status)
		वापस status;

	zero_user(page, offset, bytes);
	mark_page_accessed(page);

	वापस iomap_ग_लिखो_end(inode, pos, bytes, bytes, page, iomap, srcmap);
पूर्ण

अटल loff_t iomap_zero_range_actor(काष्ठा inode *inode, loff_t pos,
		loff_t length, व्योम *data, काष्ठा iomap *iomap,
		काष्ठा iomap *srcmap)
अणु
	bool *did_zero = data;
	loff_t written = 0;

	/* alपढ़ोy zeroed?  we're करोne. */
	अगर (srcmap->type == IOMAP_HOLE || srcmap->type == IOMAP_UNWRITTEN)
		वापस length;

	करो अणु
		s64 bytes;

		अगर (IS_DAX(inode))
			bytes = dax_iomap_zero(pos, length, iomap);
		अन्यथा
			bytes = iomap_zero(inode, pos, length, iomap, srcmap);
		अगर (bytes < 0)
			वापस bytes;

		pos += bytes;
		length -= bytes;
		written += bytes;
		अगर (did_zero)
			*did_zero = true;
	पूर्ण जबतक (length > 0);

	वापस written;
पूर्ण

पूर्णांक
iomap_zero_range(काष्ठा inode *inode, loff_t pos, loff_t len, bool *did_zero,
		स्थिर काष्ठा iomap_ops *ops)
अणु
	loff_t ret;

	जबतक (len > 0) अणु
		ret = iomap_apply(inode, pos, len, IOMAP_ZERO,
				ops, did_zero, iomap_zero_range_actor);
		अगर (ret <= 0)
			वापस ret;

		pos += ret;
		len -= ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_zero_range);

पूर्णांक
iomap_truncate_page(काष्ठा inode *inode, loff_t pos, bool *did_zero,
		स्थिर काष्ठा iomap_ops *ops)
अणु
	अचिन्हित पूर्णांक blocksize = i_blocksize(inode);
	अचिन्हित पूर्णांक off = pos & (blocksize - 1);

	/* Block boundary? Nothing to करो */
	अगर (!off)
		वापस 0;
	वापस iomap_zero_range(inode, pos, blocksize - off, did_zero, ops);
पूर्ण
EXPORT_SYMBOL_GPL(iomap_truncate_page);

अटल loff_t
iomap_page_mkग_लिखो_actor(काष्ठा inode *inode, loff_t pos, loff_t length,
		व्योम *data, काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	काष्ठा page *page = data;
	पूर्णांक ret;

	अगर (iomap->flags & IOMAP_F_BUFFER_HEAD) अणु
		ret = __block_ग_लिखो_begin_पूर्णांक(page, pos, length, शून्य, iomap);
		अगर (ret)
			वापस ret;
		block_commit_ग_लिखो(page, 0, length);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(!PageUptodate(page));
		iomap_page_create(inode, page);
		set_page_dirty(page);
	पूर्ण

	वापस length;
पूर्ण

vm_fault_t iomap_page_mkग_लिखो(काष्ठा vm_fault *vmf, स्थिर काष्ठा iomap_ops *ops)
अणु
	काष्ठा page *page = vmf->page;
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	अचिन्हित दीर्घ length;
	loff_t offset;
	sमाप_प्रकार ret;

	lock_page(page);
	ret = page_mkग_लिखो_check_truncate(page, inode);
	अगर (ret < 0)
		जाओ out_unlock;
	length = ret;

	offset = page_offset(page);
	जबतक (length > 0) अणु
		ret = iomap_apply(inode, offset, length,
				IOMAP_WRITE | IOMAP_FAULT, ops, page,
				iomap_page_mkग_लिखो_actor);
		अगर (unlikely(ret <= 0))
			जाओ out_unlock;
		offset += ret;
		length -= ret;
	पूर्ण

	रुको_क्रम_stable_page(page);
	वापस VM_FAULT_LOCKED;
out_unlock:
	unlock_page(page);
	वापस block_page_mkग_लिखो_वापस(ret);
पूर्ण
EXPORT_SYMBOL_GPL(iomap_page_mkग_लिखो);

अटल व्योम
iomap_finish_page_ग_लिखोback(काष्ठा inode *inode, काष्ठा page *page,
		पूर्णांक error, अचिन्हित पूर्णांक len)
अणु
	काष्ठा iomap_page *iop = to_iomap_page(page);

	अगर (error) अणु
		SetPageError(page);
		mapping_set_error(inode->i_mapping, -EIO);
	पूर्ण

	WARN_ON_ONCE(i_blocks_per_page(inode, page) > 1 && !iop);
	WARN_ON_ONCE(iop && atomic_पढ़ो(&iop->ग_लिखो_bytes_pending) <= 0);

	अगर (!iop || atomic_sub_and_test(len, &iop->ग_लिखो_bytes_pending))
		end_page_ग_लिखोback(page);
पूर्ण

/*
 * We're now finished क्रम good with this ioend काष्ठाure.  Update the page
 * state, release holds on bios, and finally मुक्त up memory.  Do not use the
 * ioend after this.
 */
अटल व्योम
iomap_finish_ioend(काष्ठा iomap_ioend *ioend, पूर्णांक error)
अणु
	काष्ठा inode *inode = ioend->io_inode;
	काष्ठा bio *bio = &ioend->io_अंतरभूत_bio;
	काष्ठा bio *last = ioend->io_bio, *next;
	u64 start = bio->bi_iter.bi_sector;
	loff_t offset = ioend->io_offset;
	bool quiet = bio_flagged(bio, BIO_QUIET);

	क्रम (bio = &ioend->io_अंतरभूत_bio; bio; bio = next) अणु
		काष्ठा bio_vec *bv;
		काष्ठा bvec_iter_all iter_all;

		/*
		 * For the last bio, bi_निजी poपूर्णांकs to the ioend, so we
		 * need to explicitly end the iteration here.
		 */
		अगर (bio == last)
			next = शून्य;
		अन्यथा
			next = bio->bi_निजी;

		/* walk each page on bio, ending page IO on them */
		bio_क्रम_each_segment_all(bv, bio, iter_all)
			iomap_finish_page_ग_लिखोback(inode, bv->bv_page, error,
					bv->bv_len);
		bio_put(bio);
	पूर्ण
	/* The ioend has been मुक्तd by bio_put() */

	अगर (unlikely(error && !quiet)) अणु
		prपूर्णांकk_ratelimited(KERN_ERR
"%s: writeback error on inode %lu, offset %lld, sector %llu",
			inode->i_sb->s_id, inode->i_ino, offset, start);
	पूर्ण
पूर्ण

व्योम
iomap_finish_ioends(काष्ठा iomap_ioend *ioend, पूर्णांक error)
अणु
	काष्ठा list_head पंचांगp;

	list_replace_init(&ioend->io_list, &पंचांगp);
	iomap_finish_ioend(ioend, error);

	जबतक (!list_empty(&पंचांगp)) अणु
		ioend = list_first_entry(&पंचांगp, काष्ठा iomap_ioend, io_list);
		list_del_init(&ioend->io_list);
		iomap_finish_ioend(ioend, error);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(iomap_finish_ioends);

/*
 * We can merge two adjacent ioends अगर they have the same set of work to करो.
 */
अटल bool
iomap_ioend_can_merge(काष्ठा iomap_ioend *ioend, काष्ठा iomap_ioend *next)
अणु
	अगर (ioend->io_bio->bi_status != next->io_bio->bi_status)
		वापस false;
	अगर ((ioend->io_flags & IOMAP_F_SHARED) ^
	    (next->io_flags & IOMAP_F_SHARED))
		वापस false;
	अगर ((ioend->io_type == IOMAP_UNWRITTEN) ^
	    (next->io_type == IOMAP_UNWRITTEN))
		वापस false;
	अगर (ioend->io_offset + ioend->io_size != next->io_offset)
		वापस false;
	वापस true;
पूर्ण

व्योम
iomap_ioend_try_merge(काष्ठा iomap_ioend *ioend, काष्ठा list_head *more_ioends)
अणु
	काष्ठा iomap_ioend *next;

	INIT_LIST_HEAD(&ioend->io_list);

	जबतक ((next = list_first_entry_or_null(more_ioends, काष्ठा iomap_ioend,
			io_list))) अणु
		अगर (!iomap_ioend_can_merge(ioend, next))
			अवरोध;
		list_move_tail(&next->io_list, &ioend->io_list);
		ioend->io_size += next->io_size;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(iomap_ioend_try_merge);

अटल पूर्णांक
iomap_ioend_compare(व्योम *priv, स्थिर काष्ठा list_head *a,
		स्थिर काष्ठा list_head *b)
अणु
	काष्ठा iomap_ioend *ia = container_of(a, काष्ठा iomap_ioend, io_list);
	काष्ठा iomap_ioend *ib = container_of(b, काष्ठा iomap_ioend, io_list);

	अगर (ia->io_offset < ib->io_offset)
		वापस -1;
	अगर (ia->io_offset > ib->io_offset)
		वापस 1;
	वापस 0;
पूर्ण

व्योम
iomap_sort_ioends(काष्ठा list_head *ioend_list)
अणु
	list_sort(शून्य, ioend_list, iomap_ioend_compare);
पूर्ण
EXPORT_SYMBOL_GPL(iomap_sort_ioends);

अटल व्योम iomap_ग_लिखोpage_end_bio(काष्ठा bio *bio)
अणु
	काष्ठा iomap_ioend *ioend = bio->bi_निजी;

	iomap_finish_ioend(ioend, blk_status_to_त्रुटि_सं(bio->bi_status));
पूर्ण

/*
 * Submit the final bio क्रम an ioend.
 *
 * If @error is non-zero, it means that we have a situation where some part of
 * the submission process has failed after we have marked paged क्रम ग_लिखोback
 * and unlocked them.  In this situation, we need to fail the bio instead of
 * submitting it.  This typically only happens on a fileप्रणाली shutकरोwn.
 */
अटल पूर्णांक
iomap_submit_ioend(काष्ठा iomap_ग_लिखोpage_ctx *wpc, काष्ठा iomap_ioend *ioend,
		पूर्णांक error)
अणु
	ioend->io_bio->bi_निजी = ioend;
	ioend->io_bio->bi_end_io = iomap_ग_लिखोpage_end_bio;

	अगर (wpc->ops->prepare_ioend)
		error = wpc->ops->prepare_ioend(ioend, error);
	अगर (error) अणु
		/*
		 * If we are failing the IO now, just mark the ioend with an
		 * error and finish it.  This will run IO completion immediately
		 * as there is only one reference to the ioend at this poपूर्णांक in
		 * समय.
		 */
		ioend->io_bio->bi_status = त्रुटि_सं_to_blk_status(error);
		bio_endio(ioend->io_bio);
		वापस error;
	पूर्ण

	submit_bio(ioend->io_bio);
	वापस 0;
पूर्ण

अटल काष्ठा iomap_ioend *
iomap_alloc_ioend(काष्ठा inode *inode, काष्ठा iomap_ग_लिखोpage_ctx *wpc,
		loff_t offset, sector_t sector, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा iomap_ioend *ioend;
	काष्ठा bio *bio;

	bio = bio_alloc_bioset(GFP_NOFS, BIO_MAX_VECS, &iomap_ioend_bioset);
	bio_set_dev(bio, wpc->iomap.bdev);
	bio->bi_iter.bi_sector = sector;
	bio->bi_opf = REQ_OP_WRITE | wbc_to_ग_लिखो_flags(wbc);
	bio->bi_ग_लिखो_hपूर्णांक = inode->i_ग_लिखो_hपूर्णांक;
	wbc_init_bio(wbc, bio);

	ioend = container_of(bio, काष्ठा iomap_ioend, io_अंतरभूत_bio);
	INIT_LIST_HEAD(&ioend->io_list);
	ioend->io_type = wpc->iomap.type;
	ioend->io_flags = wpc->iomap.flags;
	ioend->io_inode = inode;
	ioend->io_size = 0;
	ioend->io_offset = offset;
	ioend->io_bio = bio;
	वापस ioend;
पूर्ण

/*
 * Allocate a new bio, and chain the old bio to the new one.
 *
 * Note that we have to करो perक्रमm the chaining in this unपूर्णांकuitive order
 * so that the bi_निजी linkage is set up in the right direction क्रम the
 * traversal in iomap_finish_ioend().
 */
अटल काष्ठा bio *
iomap_chain_bio(काष्ठा bio *prev)
अणु
	काष्ठा bio *new;

	new = bio_alloc(GFP_NOFS, BIO_MAX_VECS);
	bio_copy_dev(new, prev);/* also copies over blkcg inक्रमmation */
	new->bi_iter.bi_sector = bio_end_sector(prev);
	new->bi_opf = prev->bi_opf;
	new->bi_ग_लिखो_hपूर्णांक = prev->bi_ग_लिखो_hपूर्णांक;

	bio_chain(prev, new);
	bio_get(prev);		/* क्रम iomap_finish_ioend */
	submit_bio(prev);
	वापस new;
पूर्ण

अटल bool
iomap_can_add_to_ioend(काष्ठा iomap_ग_लिखोpage_ctx *wpc, loff_t offset,
		sector_t sector)
अणु
	अगर ((wpc->iomap.flags & IOMAP_F_SHARED) !=
	    (wpc->ioend->io_flags & IOMAP_F_SHARED))
		वापस false;
	अगर (wpc->iomap.type != wpc->ioend->io_type)
		वापस false;
	अगर (offset != wpc->ioend->io_offset + wpc->ioend->io_size)
		वापस false;
	अगर (sector != bio_end_sector(wpc->ioend->io_bio))
		वापस false;
	वापस true;
पूर्ण

/*
 * Test to see अगर we have an existing ioend काष्ठाure that we could append to
 * first, otherwise finish off the current ioend and start another.
 */
अटल व्योम
iomap_add_to_ioend(काष्ठा inode *inode, loff_t offset, काष्ठा page *page,
		काष्ठा iomap_page *iop, काष्ठा iomap_ग_लिखोpage_ctx *wpc,
		काष्ठा ग_लिखोback_control *wbc, काष्ठा list_head *iolist)
अणु
	sector_t sector = iomap_sector(&wpc->iomap, offset);
	अचिन्हित len = i_blocksize(inode);
	अचिन्हित poff = offset & (PAGE_SIZE - 1);
	bool merged, same_page = false;

	अगर (!wpc->ioend || !iomap_can_add_to_ioend(wpc, offset, sector)) अणु
		अगर (wpc->ioend)
			list_add(&wpc->ioend->io_list, iolist);
		wpc->ioend = iomap_alloc_ioend(inode, wpc, offset, sector, wbc);
	पूर्ण

	merged = __bio_try_merge_page(wpc->ioend->io_bio, page, len, poff,
			&same_page);
	अगर (iop)
		atomic_add(len, &iop->ग_लिखो_bytes_pending);

	अगर (!merged) अणु
		अगर (bio_full(wpc->ioend->io_bio, len)) अणु
			wpc->ioend->io_bio =
				iomap_chain_bio(wpc->ioend->io_bio);
		पूर्ण
		bio_add_page(wpc->ioend->io_bio, page, len, poff);
	पूर्ण

	wpc->ioend->io_size += len;
	wbc_account_cgroup_owner(wbc, page, len);
पूर्ण

/*
 * We implement an immediate ioend submission policy here to aव्योम needing to
 * chain multiple ioends and hence nest mempool allocations which can violate
 * क्रमward progress guarantees we need to provide. The current ioend we are
 * adding blocks to is cached on the ग_लिखोpage context, and अगर the new block
 * करोes not append to the cached ioend it will create a new ioend and cache that
 * instead.
 *
 * If a new ioend is created and cached, the old ioend is वापसed and queued
 * locally क्रम submission once the entire page is processed or an error has been
 * detected.  While ioends are submitted immediately after they are completed,
 * batching optimisations are provided by higher level block plugging.
 *
 * At the end of a ग_लिखोback pass, there will be a cached ioend reमुख्यing on the
 * ग_लिखोpage context that the caller will need to submit.
 */
अटल पूर्णांक
iomap_ग_लिखोpage_map(काष्ठा iomap_ग_लिखोpage_ctx *wpc,
		काष्ठा ग_लिखोback_control *wbc, काष्ठा inode *inode,
		काष्ठा page *page, u64 end_offset)
अणु
	काष्ठा iomap_page *iop = to_iomap_page(page);
	काष्ठा iomap_ioend *ioend, *next;
	अचिन्हित len = i_blocksize(inode);
	u64 file_offset; /* file offset of page */
	पूर्णांक error = 0, count = 0, i;
	LIST_HEAD(submit_list);

	WARN_ON_ONCE(i_blocks_per_page(inode, page) > 1 && !iop);
	WARN_ON_ONCE(iop && atomic_पढ़ो(&iop->ग_लिखो_bytes_pending) != 0);

	/*
	 * Walk through the page to find areas to ग_लिखो back. If we run off the
	 * end of the current map or find the current map invalid, grab a new
	 * one.
	 */
	क्रम (i = 0, file_offset = page_offset(page);
	     i < (PAGE_SIZE >> inode->i_blkbits) && file_offset < end_offset;
	     i++, file_offset += len) अणु
		अगर (iop && !test_bit(i, iop->uptodate))
			जारी;

		error = wpc->ops->map_blocks(wpc, inode, file_offset);
		अगर (error)
			अवरोध;
		अगर (WARN_ON_ONCE(wpc->iomap.type == IOMAP_INLINE))
			जारी;
		अगर (wpc->iomap.type == IOMAP_HOLE)
			जारी;
		iomap_add_to_ioend(inode, file_offset, page, iop, wpc, wbc,
				 &submit_list);
		count++;
	पूर्ण

	WARN_ON_ONCE(!wpc->ioend && !list_empty(&submit_list));
	WARN_ON_ONCE(!PageLocked(page));
	WARN_ON_ONCE(PageWriteback(page));
	WARN_ON_ONCE(PageDirty(page));

	/*
	 * We cannot cancel the ioend directly here on error.  We may have
	 * alपढ़ोy set other pages under ग_लिखोback and hence we have to run I/O
	 * completion to mark the error state of the pages under ग_लिखोback
	 * appropriately.
	 */
	अगर (unlikely(error)) अणु
		/*
		 * Let the fileप्रणाली know what portion of the current page
		 * failed to map. If the page wasn't been added to ioend, it
		 * won't be affected by I/O completion and we must unlock it
		 * now.
		 */
		अगर (wpc->ops->discard_page)
			wpc->ops->discard_page(page, file_offset);
		अगर (!count) अणु
			ClearPageUptodate(page);
			unlock_page(page);
			जाओ करोne;
		पूर्ण
	पूर्ण

	set_page_ग_लिखोback(page);
	unlock_page(page);

	/*
	 * Preserve the original error अगर there was one, otherwise catch
	 * submission errors here and propagate पूर्णांकo subsequent ioend
	 * submissions.
	 */
	list_क्रम_each_entry_safe(ioend, next, &submit_list, io_list) अणु
		पूर्णांक error2;

		list_del_init(&ioend->io_list);
		error2 = iomap_submit_ioend(wpc, ioend, error);
		अगर (error2 && !error)
			error = error2;
	पूर्ण

	/*
	 * We can end up here with no error and nothing to ग_लिखो only अगर we race
	 * with a partial page truncate on a sub-page block sized fileप्रणाली.
	 */
	अगर (!count)
		end_page_ग_लिखोback(page);
करोne:
	mapping_set_error(page->mapping, error);
	वापस error;
पूर्ण

/*
 * Write out a dirty page.
 *
 * For delalloc space on the page we need to allocate space and flush it.
 * For unwritten space on the page we need to start the conversion to
 * regular allocated space.
 */
अटल पूर्णांक
iomap_करो_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc, व्योम *data)
अणु
	काष्ठा iomap_ग_लिखोpage_ctx *wpc = data;
	काष्ठा inode *inode = page->mapping->host;
	pgoff_t end_index;
	u64 end_offset;
	loff_t offset;

	trace_iomap_ग_लिखोpage(inode, page_offset(page), PAGE_SIZE);

	/*
	 * Refuse to ग_लिखो the page out अगर we are called from reclaim context.
	 *
	 * This aव्योमs stack overflows when called from deeply used stacks in
	 * अक्रमom callers क्रम direct reclaim or memcg reclaim.  We explicitly
	 * allow reclaim from kswapd as the stack usage there is relatively low.
	 *
	 * This should never happen except in the हाल of a VM regression so
	 * warn about it.
	 */
	अगर (WARN_ON_ONCE((current->flags & (PF_MEMALLOC|PF_KSWAPD)) ==
			PF_MEMALLOC))
		जाओ redirty;

	/*
	 * Is this page beyond the end of the file?
	 *
	 * The page index is less than the end_index, adjust the end_offset
	 * to the highest offset that this page should represent.
	 * -----------------------------------------------------
	 * |			file mapping	       | <खातापूर्ण> |
	 * -----------------------------------------------------
	 * | Page ... | Page N-2 | Page N-1 |  Page N  |       |
	 * ^--------------------------------^----------|--------
	 * |     desired ग_लिखोback range    |      see अन्यथा    |
	 * ---------------------------------^------------------|
	 */
	offset = i_size_पढ़ो(inode);
	end_index = offset >> PAGE_SHIFT;
	अगर (page->index < end_index)
		end_offset = (loff_t)(page->index + 1) << PAGE_SHIFT;
	अन्यथा अणु
		/*
		 * Check whether the page to ग_लिखो out is beyond or straddles
		 * i_size or not.
		 * -------------------------------------------------------
		 * |		file mapping		        | <खातापूर्ण>  |
		 * -------------------------------------------------------
		 * | Page ... | Page N-2 | Page N-1 |  Page N   | Beyond |
		 * ^--------------------------------^-----------|---------
		 * |				    |      Straddles     |
		 * ---------------------------------^-----------|--------|
		 */
		अचिन्हित offset_पूर्णांकo_page = offset & (PAGE_SIZE - 1);

		/*
		 * Skip the page अगर it is fully outside i_size, e.g. due to a
		 * truncate operation that is in progress. We must redirty the
		 * page so that reclaim stops reclaiming it. Otherwise
		 * iomap_vm_releasepage() is called on it and माला_लो confused.
		 *
		 * Note that the end_index is अचिन्हित दीर्घ, it would overflow
		 * अगर the given offset is greater than 16TB on 32-bit प्रणाली
		 * and अगर we करो check the page is fully outside i_size or not
		 * via "if (page->index >= end_index + 1)" as "end_index + 1"
		 * will be evaluated to 0.  Hence this page will be redirtied
		 * and be written out repeatedly which would result in an
		 * infinite loop, the user program that perक्रमm this operation
		 * will hang.  Instead, we can verअगरy this situation by checking
		 * अगर the page to ग_लिखो is totally beyond the i_size or अगर it's
		 * offset is just equal to the खातापूर्ण.
		 */
		अगर (page->index > end_index ||
		    (page->index == end_index && offset_पूर्णांकo_page == 0))
			जाओ redirty;

		/*
		 * The page straddles i_size.  It must be zeroed out on each
		 * and every ग_लिखोpage invocation because it may be mmapped.
		 * "A file is mapped in multiples of the page size.  For a file
		 * that is not a multiple of the page size, the reमुख्यing
		 * memory is zeroed when mapped, and ग_लिखोs to that region are
		 * not written out to the file."
		 */
		zero_user_segment(page, offset_पूर्णांकo_page, PAGE_SIZE);

		/* Adjust the end_offset to the end of file */
		end_offset = offset;
	पूर्ण

	वापस iomap_ग_लिखोpage_map(wpc, wbc, inode, page, end_offset);

redirty:
	redirty_page_क्रम_ग_लिखोpage(wbc, page);
	unlock_page(page);
	वापस 0;
पूर्ण

पूर्णांक
iomap_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
		काष्ठा iomap_ग_लिखोpage_ctx *wpc,
		स्थिर काष्ठा iomap_ग_लिखोback_ops *ops)
अणु
	पूर्णांक ret;

	wpc->ops = ops;
	ret = iomap_करो_ग_लिखोpage(page, wbc, wpc);
	अगर (!wpc->ioend)
		वापस ret;
	वापस iomap_submit_ioend(wpc, wpc->ioend, ret);
पूर्ण
EXPORT_SYMBOL_GPL(iomap_ग_लिखोpage);

पूर्णांक
iomap_ग_लिखोpages(काष्ठा address_space *mapping, काष्ठा ग_लिखोback_control *wbc,
		काष्ठा iomap_ग_लिखोpage_ctx *wpc,
		स्थिर काष्ठा iomap_ग_लिखोback_ops *ops)
अणु
	पूर्णांक			ret;

	wpc->ops = ops;
	ret = ग_लिखो_cache_pages(mapping, wbc, iomap_करो_ग_लिखोpage, wpc);
	अगर (!wpc->ioend)
		वापस ret;
	वापस iomap_submit_ioend(wpc, wpc->ioend, ret);
पूर्ण
EXPORT_SYMBOL_GPL(iomap_ग_लिखोpages);

अटल पूर्णांक __init iomap_init(व्योम)
अणु
	वापस bioset_init(&iomap_ioend_bioset, 4 * (PAGE_SIZE / SECTOR_SIZE),
			   दुरत्व(काष्ठा iomap_ioend, io_अंतरभूत_bio),
			   BIOSET_NEED_BVECS);
पूर्ण
fs_initcall(iomap_init);
