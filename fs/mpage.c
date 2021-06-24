<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/mpage.c
 *
 * Copyright (C) 2002, Linus Torvalds.
 *
 * Contains functions related to preparing and submitting BIOs which contain
 * multiple pagecache pages.
 *
 * 15May2002	Andrew Morton
 *		Initial version
 * 27Jun2002	axboe@suse.de
 *		use bio_add_page() to build bio's just the right size
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/gfp.h>
#समावेश <linux/bपन.स>
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/prefetch.h>
#समावेश <linux/mpage.h>
#समावेश <linux/mm_अंतरभूत.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/cleancache.h>
#समावेश "internal.h"

/*
 * I/O completion handler क्रम multipage BIOs.
 *
 * The mpage code never माला_दो partial pages पूर्णांकo a BIO (except क्रम end-of-file).
 * If a page करोes not map to a contiguous run of blocks then it simply falls
 * back to block_पढ़ो_full_page().
 *
 * Why is this?  If a page's completion depends on a number of dअगरferent BIOs
 * which can complete in any order (or at the same समय) then determining the
 * status of that page is hard.  See end_buffer_async_पढ़ो() क्रम the details.
 * There is no poपूर्णांक in duplicating all that complनिकासy.
 */
अटल व्योम mpage_end_io(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bv;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bv, bio, iter_all) अणु
		काष्ठा page *page = bv->bv_page;
		page_endio(page, bio_op(bio),
			   blk_status_to_त्रुटि_सं(bio->bi_status));
	पूर्ण

	bio_put(bio);
पूर्ण

अटल काष्ठा bio *mpage_bio_submit(पूर्णांक op, पूर्णांक op_flags, काष्ठा bio *bio)
अणु
	bio->bi_end_io = mpage_end_io;
	bio_set_op_attrs(bio, op, op_flags);
	guard_bio_eod(bio);
	submit_bio(bio);
	वापस शून्य;
पूर्ण

अटल काष्ठा bio *
mpage_alloc(काष्ठा block_device *bdev,
		sector_t first_sector, पूर्णांक nr_vecs,
		gfp_t gfp_flags)
अणु
	काष्ठा bio *bio;

	/* Restrict the given (page cache) mask क्रम slab allocations */
	gfp_flags &= GFP_KERNEL;
	bio = bio_alloc(gfp_flags, nr_vecs);

	अगर (bio == शून्य && (current->flags & PF_MEMALLOC)) अणु
		जबतक (!bio && (nr_vecs /= 2))
			bio = bio_alloc(gfp_flags, nr_vecs);
	पूर्ण

	अगर (bio) अणु
		bio_set_dev(bio, bdev);
		bio->bi_iter.bi_sector = first_sector;
	पूर्ण
	वापस bio;
पूर्ण

/*
 * support function क्रम mpage_पढ़ोahead.  The fs supplied get_block might
 * वापस an up to date buffer.  This is used to map that buffer पूर्णांकo
 * the page, which allows पढ़ोpage to aव्योम triggering a duplicate call
 * to get_block.
 *
 * The idea is to aव्योम adding buffers to pages that करोn't alपढ़ोy have
 * them.  So when the buffer is up to date and the page size == block size,
 * this marks the page up to date instead of adding new buffers.
 */
अटल व्योम 
map_buffer_to_page(काष्ठा page *page, काष्ठा buffer_head *bh, पूर्णांक page_block) 
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा buffer_head *page_bh, *head;
	पूर्णांक block = 0;

	अगर (!page_has_buffers(page)) अणु
		/*
		 * करोn't make any buffers अगर there is only one buffer on
		 * the page and the page just needs to be set up to date
		 */
		अगर (inode->i_blkbits == PAGE_SHIFT &&
		    buffer_uptodate(bh)) अणु
			SetPageUptodate(page);    
			वापस;
		पूर्ण
		create_empty_buffers(page, i_blocksize(inode), 0);
	पूर्ण
	head = page_buffers(page);
	page_bh = head;
	करो अणु
		अगर (block == page_block) अणु
			page_bh->b_state = bh->b_state;
			page_bh->b_bdev = bh->b_bdev;
			page_bh->b_blocknr = bh->b_blocknr;
			अवरोध;
		पूर्ण
		page_bh = page_bh->b_this_page;
		block++;
	पूर्ण जबतक (page_bh != head);
पूर्ण

काष्ठा mpage_पढ़ोpage_args अणु
	काष्ठा bio *bio;
	काष्ठा page *page;
	अचिन्हित पूर्णांक nr_pages;
	bool is_पढ़ोahead;
	sector_t last_block_in_bio;
	काष्ठा buffer_head map_bh;
	अचिन्हित दीर्घ first_logical_block;
	get_block_t *get_block;
पूर्ण;

/*
 * This is the worker routine which करोes all the work of mapping the disk
 * blocks and स्थिरructs largest possible bios, submits them क्रम IO अगर the
 * blocks are not contiguous on the disk.
 *
 * We pass a buffer_head back and क्रमth and use its buffer_mapped() flag to
 * represent the validity of its disk mapping and to decide when to करो the next
 * get_block() call.
 */
अटल काष्ठा bio *करो_mpage_पढ़ोpage(काष्ठा mpage_पढ़ोpage_args *args)
अणु
	काष्ठा page *page = args->page;
	काष्ठा inode *inode = page->mapping->host;
	स्थिर अचिन्हित blkbits = inode->i_blkbits;
	स्थिर अचिन्हित blocks_per_page = PAGE_SIZE >> blkbits;
	स्थिर अचिन्हित blocksize = 1 << blkbits;
	काष्ठा buffer_head *map_bh = &args->map_bh;
	sector_t block_in_file;
	sector_t last_block;
	sector_t last_block_in_file;
	sector_t blocks[MAX_BUF_PER_PAGE];
	अचिन्हित page_block;
	अचिन्हित first_hole = blocks_per_page;
	काष्ठा block_device *bdev = शून्य;
	पूर्णांक length;
	पूर्णांक fully_mapped = 1;
	पूर्णांक op_flags;
	अचिन्हित nblocks;
	अचिन्हित relative_block;
	gfp_t gfp;

	अगर (args->is_पढ़ोahead) अणु
		op_flags = REQ_RAHEAD;
		gfp = पढ़ोahead_gfp_mask(page->mapping);
	पूर्ण अन्यथा अणु
		op_flags = 0;
		gfp = mapping_gfp_स्थिरraपूर्णांक(page->mapping, GFP_KERNEL);
	पूर्ण

	अगर (page_has_buffers(page))
		जाओ confused;

	block_in_file = (sector_t)page->index << (PAGE_SHIFT - blkbits);
	last_block = block_in_file + args->nr_pages * blocks_per_page;
	last_block_in_file = (i_size_पढ़ो(inode) + blocksize - 1) >> blkbits;
	अगर (last_block > last_block_in_file)
		last_block = last_block_in_file;
	page_block = 0;

	/*
	 * Map blocks using the result from the previous get_blocks call first.
	 */
	nblocks = map_bh->b_size >> blkbits;
	अगर (buffer_mapped(map_bh) &&
			block_in_file > args->first_logical_block &&
			block_in_file < (args->first_logical_block + nblocks)) अणु
		अचिन्हित map_offset = block_in_file - args->first_logical_block;
		अचिन्हित last = nblocks - map_offset;

		क्रम (relative_block = 0; ; relative_block++) अणु
			अगर (relative_block == last) अणु
				clear_buffer_mapped(map_bh);
				अवरोध;
			पूर्ण
			अगर (page_block == blocks_per_page)
				अवरोध;
			blocks[page_block] = map_bh->b_blocknr + map_offset +
						relative_block;
			page_block++;
			block_in_file++;
		पूर्ण
		bdev = map_bh->b_bdev;
	पूर्ण

	/*
	 * Then करो more get_blocks calls until we are करोne with this page.
	 */
	map_bh->b_page = page;
	जबतक (page_block < blocks_per_page) अणु
		map_bh->b_state = 0;
		map_bh->b_size = 0;

		अगर (block_in_file < last_block) अणु
			map_bh->b_size = (last_block-block_in_file) << blkbits;
			अगर (args->get_block(inode, block_in_file, map_bh, 0))
				जाओ confused;
			args->first_logical_block = block_in_file;
		पूर्ण

		अगर (!buffer_mapped(map_bh)) अणु
			fully_mapped = 0;
			अगर (first_hole == blocks_per_page)
				first_hole = page_block;
			page_block++;
			block_in_file++;
			जारी;
		पूर्ण

		/* some fileप्रणालीs will copy data पूर्णांकo the page during
		 * the get_block call, in which हाल we करोn't want to
		 * पढ़ो it again.  map_buffer_to_page copies the data
		 * we just collected from get_block पूर्णांकo the page's buffers
		 * so पढ़ोpage करोesn't have to repeat the get_block call
		 */
		अगर (buffer_uptodate(map_bh)) अणु
			map_buffer_to_page(page, map_bh, page_block);
			जाओ confused;
		पूर्ण
	
		अगर (first_hole != blocks_per_page)
			जाओ confused;		/* hole -> non-hole */

		/* Contiguous blocks? */
		अगर (page_block && blocks[page_block-1] != map_bh->b_blocknr-1)
			जाओ confused;
		nblocks = map_bh->b_size >> blkbits;
		क्रम (relative_block = 0; ; relative_block++) अणु
			अगर (relative_block == nblocks) अणु
				clear_buffer_mapped(map_bh);
				अवरोध;
			पूर्ण अन्यथा अगर (page_block == blocks_per_page)
				अवरोध;
			blocks[page_block] = map_bh->b_blocknr+relative_block;
			page_block++;
			block_in_file++;
		पूर्ण
		bdev = map_bh->b_bdev;
	पूर्ण

	अगर (first_hole != blocks_per_page) अणु
		zero_user_segment(page, first_hole << blkbits, PAGE_SIZE);
		अगर (first_hole == 0) अणु
			SetPageUptodate(page);
			unlock_page(page);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (fully_mapped) अणु
		SetPageMappedToDisk(page);
	पूर्ण

	अगर (fully_mapped && blocks_per_page == 1 && !PageUptodate(page) &&
	    cleancache_get_page(page) == 0) अणु
		SetPageUptodate(page);
		जाओ confused;
	पूर्ण

	/*
	 * This page will go to BIO.  Do we need to send this BIO off first?
	 */
	अगर (args->bio && (args->last_block_in_bio != blocks[0] - 1))
		args->bio = mpage_bio_submit(REQ_OP_READ, op_flags, args->bio);

alloc_new:
	अगर (args->bio == शून्य) अणु
		अगर (first_hole == blocks_per_page) अणु
			अगर (!bdev_पढ़ो_page(bdev, blocks[0] << (blkbits - 9),
								page))
				जाओ out;
		पूर्ण
		args->bio = mpage_alloc(bdev, blocks[0] << (blkbits - 9),
					bio_max_segs(args->nr_pages), gfp);
		अगर (args->bio == शून्य)
			जाओ confused;
	पूर्ण

	length = first_hole << blkbits;
	अगर (bio_add_page(args->bio, page, length, 0) < length) अणु
		args->bio = mpage_bio_submit(REQ_OP_READ, op_flags, args->bio);
		जाओ alloc_new;
	पूर्ण

	relative_block = block_in_file - args->first_logical_block;
	nblocks = map_bh->b_size >> blkbits;
	अगर ((buffer_boundary(map_bh) && relative_block == nblocks) ||
	    (first_hole != blocks_per_page))
		args->bio = mpage_bio_submit(REQ_OP_READ, op_flags, args->bio);
	अन्यथा
		args->last_block_in_bio = blocks[blocks_per_page - 1];
out:
	वापस args->bio;

confused:
	अगर (args->bio)
		args->bio = mpage_bio_submit(REQ_OP_READ, op_flags, args->bio);
	अगर (!PageUptodate(page))
		block_पढ़ो_full_page(page, args->get_block);
	अन्यथा
		unlock_page(page);
	जाओ out;
पूर्ण

/**
 * mpage_पढ़ोahead - start पढ़ोs against pages
 * @rac: Describes which pages to पढ़ो.
 * @get_block: The fileप्रणाली's block mapper function.
 *
 * This function walks the pages and the blocks within each page, building and
 * emitting large BIOs.
 *
 * If anything unusual happens, such as:
 *
 * - encountering a page which has buffers
 * - encountering a page which has a non-hole after a hole
 * - encountering a page with non-contiguous blocks
 *
 * then this code just gives up and calls the buffer_head-based पढ़ो function.
 * It करोes handle a page which has holes at the end - that is a common हाल:
 * the end-of-file on blocksize < PAGE_SIZE setups.
 *
 * BH_Boundary explanation:
 *
 * There is a problem.  The mpage पढ़ो code assembles several pages, माला_लो all
 * their disk mappings, and then submits them all.  That's fine, but obtaining
 * the disk mappings may require I/O.  Reads of indirect blocks, क्रम example.
 *
 * So an mpage पढ़ो of the first 16 blocks of an ext2 file will cause I/O to be
 * submitted in the following order:
 *
 * 	12 0 1 2 3 4 5 6 7 8 9 10 11 13 14 15 16
 *
 * because the indirect block has to be पढ़ो to get the mappings of blocks
 * 13,14,15,16.  Obviously, this impacts perक्रमmance.
 *
 * So what we करो it to allow the fileप्रणाली's get_block() function to set
 * BH_Boundary when it maps block 11.  BH_Boundary says: mapping of the block
 * after this one will require I/O against a block which is probably बंद to
 * this one.  So you should push what I/O you have currently accumulated.
 *
 * This all causes the disk requests to be issued in the correct order.
 */
व्योम mpage_पढ़ोahead(काष्ठा पढ़ोahead_control *rac, get_block_t get_block)
अणु
	काष्ठा page *page;
	काष्ठा mpage_पढ़ोpage_args args = अणु
		.get_block = get_block,
		.is_पढ़ोahead = true,
	पूर्ण;

	जबतक ((page = पढ़ोahead_page(rac))) अणु
		prefetchw(&page->flags);
		args.page = page;
		args.nr_pages = पढ़ोahead_count(rac);
		args.bio = करो_mpage_पढ़ोpage(&args);
		put_page(page);
	पूर्ण
	अगर (args.bio)
		mpage_bio_submit(REQ_OP_READ, REQ_RAHEAD, args.bio);
पूर्ण
EXPORT_SYMBOL(mpage_पढ़ोahead);

/*
 * This isn't called much at all
 */
पूर्णांक mpage_पढ़ोpage(काष्ठा page *page, get_block_t get_block)
अणु
	काष्ठा mpage_पढ़ोpage_args args = अणु
		.page = page,
		.nr_pages = 1,
		.get_block = get_block,
	पूर्ण;

	args.bio = करो_mpage_पढ़ोpage(&args);
	अगर (args.bio)
		mpage_bio_submit(REQ_OP_READ, 0, args.bio);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mpage_पढ़ोpage);

/*
 * Writing is not so simple.
 *
 * If the page has buffers then they will be used क्रम obtaining the disk
 * mapping.  We only support pages which are fully mapped-and-dirty, with a
 * special हाल क्रम pages which are unmapped at the end: end-of-file.
 *
 * If the page has no buffers (preferred) then the page is mapped here.
 *
 * If all blocks are found to be contiguous then the page can go पूर्णांकo the
 * BIO.  Otherwise fall back to the mapping's ग_लिखोpage().
 * 
 * FIXME: This code wants an estimate of how many pages are still to be
 * written, so it can पूर्णांकelligently allocate a suitably-sized BIO.  For now,
 * just allocate full-size (16-page) BIOs.
 */

काष्ठा mpage_data अणु
	काष्ठा bio *bio;
	sector_t last_block_in_bio;
	get_block_t *get_block;
	अचिन्हित use_ग_लिखोpage;
पूर्ण;

/*
 * We have our BIO, so we can now mark the buffers clean.  Make
 * sure to only clean buffers which we know we'll be writing.
 */
अटल व्योम clean_buffers(काष्ठा page *page, अचिन्हित first_unmapped)
अणु
	अचिन्हित buffer_counter = 0;
	काष्ठा buffer_head *bh, *head;
	अगर (!page_has_buffers(page))
		वापस;
	head = page_buffers(page);
	bh = head;

	करो अणु
		अगर (buffer_counter++ == first_unmapped)
			अवरोध;
		clear_buffer_dirty(bh);
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);

	/*
	 * we cannot drop the bh अगर the page is not uptodate or a concurrent
	 * पढ़ोpage would fail to serialize with the bh and it would पढ़ो from
	 * disk beक्रमe we reach the platter.
	 */
	अगर (buffer_heads_over_limit && PageUptodate(page))
		try_to_मुक्त_buffers(page);
पूर्ण

/*
 * For situations where we want to clean all buffers attached to a page.
 * We करोn't need to calculate how many buffers are attached to the page,
 * we just need to specअगरy a number larger than the maximum number of buffers.
 */
व्योम clean_page_buffers(काष्ठा page *page)
अणु
	clean_buffers(page, ~0U);
पूर्ण

अटल पूर्णांक __mpage_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc,
		      व्योम *data)
अणु
	काष्ठा mpage_data *mpd = data;
	काष्ठा bio *bio = mpd->bio;
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा inode *inode = page->mapping->host;
	स्थिर अचिन्हित blkbits = inode->i_blkbits;
	अचिन्हित दीर्घ end_index;
	स्थिर अचिन्हित blocks_per_page = PAGE_SIZE >> blkbits;
	sector_t last_block;
	sector_t block_in_file;
	sector_t blocks[MAX_BUF_PER_PAGE];
	अचिन्हित page_block;
	अचिन्हित first_unmapped = blocks_per_page;
	काष्ठा block_device *bdev = शून्य;
	पूर्णांक boundary = 0;
	sector_t boundary_block = 0;
	काष्ठा block_device *boundary_bdev = शून्य;
	पूर्णांक length;
	काष्ठा buffer_head map_bh;
	loff_t i_size = i_size_पढ़ो(inode);
	पूर्णांक ret = 0;
	पूर्णांक op_flags = wbc_to_ग_लिखो_flags(wbc);

	अगर (page_has_buffers(page)) अणु
		काष्ठा buffer_head *head = page_buffers(page);
		काष्ठा buffer_head *bh = head;

		/* If they're all mapped and dirty, करो it */
		page_block = 0;
		करो अणु
			BUG_ON(buffer_locked(bh));
			अगर (!buffer_mapped(bh)) अणु
				/*
				 * unmapped dirty buffers are created by
				 * __set_page_dirty_buffers -> mmapped data
				 */
				अगर (buffer_dirty(bh))
					जाओ confused;
				अगर (first_unmapped == blocks_per_page)
					first_unmapped = page_block;
				जारी;
			पूर्ण

			अगर (first_unmapped != blocks_per_page)
				जाओ confused;	/* hole -> non-hole */

			अगर (!buffer_dirty(bh) || !buffer_uptodate(bh))
				जाओ confused;
			अगर (page_block) अणु
				अगर (bh->b_blocknr != blocks[page_block-1] + 1)
					जाओ confused;
			पूर्ण
			blocks[page_block++] = bh->b_blocknr;
			boundary = buffer_boundary(bh);
			अगर (boundary) अणु
				boundary_block = bh->b_blocknr;
				boundary_bdev = bh->b_bdev;
			पूर्ण
			bdev = bh->b_bdev;
		पूर्ण जबतक ((bh = bh->b_this_page) != head);

		अगर (first_unmapped)
			जाओ page_is_mapped;

		/*
		 * Page has buffers, but they are all unmapped. The page was
		 * created by pagein or पढ़ो over a hole which was handled by
		 * block_पढ़ो_full_page().  If this address_space is also
		 * using mpage_पढ़ोahead then this can rarely happen.
		 */
		जाओ confused;
	पूर्ण

	/*
	 * The page has no buffers: map it to disk
	 */
	BUG_ON(!PageUptodate(page));
	block_in_file = (sector_t)page->index << (PAGE_SHIFT - blkbits);
	last_block = (i_size - 1) >> blkbits;
	map_bh.b_page = page;
	क्रम (page_block = 0; page_block < blocks_per_page; ) अणु

		map_bh.b_state = 0;
		map_bh.b_size = 1 << blkbits;
		अगर (mpd->get_block(inode, block_in_file, &map_bh, 1))
			जाओ confused;
		अगर (buffer_new(&map_bh))
			clean_bdev_bh_alias(&map_bh);
		अगर (buffer_boundary(&map_bh)) अणु
			boundary_block = map_bh.b_blocknr;
			boundary_bdev = map_bh.b_bdev;
		पूर्ण
		अगर (page_block) अणु
			अगर (map_bh.b_blocknr != blocks[page_block-1] + 1)
				जाओ confused;
		पूर्ण
		blocks[page_block++] = map_bh.b_blocknr;
		boundary = buffer_boundary(&map_bh);
		bdev = map_bh.b_bdev;
		अगर (block_in_file == last_block)
			अवरोध;
		block_in_file++;
	पूर्ण
	BUG_ON(page_block == 0);

	first_unmapped = page_block;

page_is_mapped:
	end_index = i_size >> PAGE_SHIFT;
	अगर (page->index >= end_index) अणु
		/*
		 * The page straddles i_size.  It must be zeroed out on each
		 * and every ग_लिखोpage invocation because it may be mmapped.
		 * "A file is mapped in multiples of the page size.  For a file
		 * that is not a multiple of the page size, the reमुख्यing memory
		 * is zeroed when mapped, and ग_लिखोs to that region are not
		 * written out to the file."
		 */
		अचिन्हित offset = i_size & (PAGE_SIZE - 1);

		अगर (page->index > end_index || !offset)
			जाओ confused;
		zero_user_segment(page, offset, PAGE_SIZE);
	पूर्ण

	/*
	 * This page will go to BIO.  Do we need to send this BIO off first?
	 */
	अगर (bio && mpd->last_block_in_bio != blocks[0] - 1)
		bio = mpage_bio_submit(REQ_OP_WRITE, op_flags, bio);

alloc_new:
	अगर (bio == शून्य) अणु
		अगर (first_unmapped == blocks_per_page) अणु
			अगर (!bdev_ग_लिखो_page(bdev, blocks[0] << (blkbits - 9),
								page, wbc))
				जाओ out;
		पूर्ण
		bio = mpage_alloc(bdev, blocks[0] << (blkbits - 9),
				BIO_MAX_VECS, GFP_NOFS|__GFP_HIGH);
		अगर (bio == शून्य)
			जाओ confused;

		wbc_init_bio(wbc, bio);
		bio->bi_ग_लिखो_hपूर्णांक = inode->i_ग_लिखो_hपूर्णांक;
	पूर्ण

	/*
	 * Must try to add the page beक्रमe marking the buffer clean or
	 * the confused fail path above (OOM) will be very confused when
	 * it finds all bh marked clean (i.e. it will not ग_लिखो anything)
	 */
	wbc_account_cgroup_owner(wbc, page, PAGE_SIZE);
	length = first_unmapped << blkbits;
	अगर (bio_add_page(bio, page, length, 0) < length) अणु
		bio = mpage_bio_submit(REQ_OP_WRITE, op_flags, bio);
		जाओ alloc_new;
	पूर्ण

	clean_buffers(page, first_unmapped);

	BUG_ON(PageWriteback(page));
	set_page_ग_लिखोback(page);
	unlock_page(page);
	अगर (boundary || (first_unmapped != blocks_per_page)) अणु
		bio = mpage_bio_submit(REQ_OP_WRITE, op_flags, bio);
		अगर (boundary_block) अणु
			ग_लिखो_boundary_block(boundary_bdev,
					boundary_block, 1 << blkbits);
		पूर्ण
	पूर्ण अन्यथा अणु
		mpd->last_block_in_bio = blocks[blocks_per_page - 1];
	पूर्ण
	जाओ out;

confused:
	अगर (bio)
		bio = mpage_bio_submit(REQ_OP_WRITE, op_flags, bio);

	अगर (mpd->use_ग_लिखोpage) अणु
		ret = mapping->a_ops->ग_लिखोpage(page, wbc);
	पूर्ण अन्यथा अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	/*
	 * The caller has a ref on the inode, so *mapping is stable
	 */
	mapping_set_error(mapping, ret);
out:
	mpd->bio = bio;
	वापस ret;
पूर्ण

/**
 * mpage_ग_लिखोpages - walk the list of dirty pages of the given address space & ग_लिखोpage() all of them
 * @mapping: address space काष्ठाure to ग_लिखो
 * @wbc: subtract the number of written pages from *@wbc->nr_to_ग_लिखो
 * @get_block: the fileप्रणाली's block mapper function.
 *             If this is शून्य then use a_ops->ग_लिखोpage.  Otherwise, go
 *             direct-to-BIO.
 *
 * This is a library function, which implements the ग_लिखोpages()
 * address_space_operation.
 *
 * If a page is alपढ़ोy under I/O, generic_ग_लिखोpages() skips it, even
 * अगर it's dirty.  This is desirable behaviour क्रम memory-cleaning ग_लिखोback,
 * but it is INCORRECT क्रम data-पूर्णांकegrity प्रणाली calls such as fsync().  fsync()
 * and msync() need to guarantee that all the data which was dirty at the समय
 * the call was made get new I/O started against them.  If wbc->sync_mode is
 * WB_SYNC_ALL then we were called क्रम data पूर्णांकegrity and we must रुको क्रम
 * existing IO to complete.
 */
पूर्णांक
mpage_ग_लिखोpages(काष्ठा address_space *mapping,
		काष्ठा ग_लिखोback_control *wbc, get_block_t get_block)
अणु
	काष्ठा blk_plug plug;
	पूर्णांक ret;

	blk_start_plug(&plug);

	अगर (!get_block)
		ret = generic_ग_लिखोpages(mapping, wbc);
	अन्यथा अणु
		काष्ठा mpage_data mpd = अणु
			.bio = शून्य,
			.last_block_in_bio = 0,
			.get_block = get_block,
			.use_ग_लिखोpage = 1,
		पूर्ण;

		ret = ग_लिखो_cache_pages(mapping, wbc, __mpage_ग_लिखोpage, &mpd);
		अगर (mpd.bio) अणु
			पूर्णांक op_flags = (wbc->sync_mode == WB_SYNC_ALL ?
				  REQ_SYNC : 0);
			mpage_bio_submit(REQ_OP_WRITE, op_flags, mpd.bio);
		पूर्ण
	पूर्ण
	blk_finish_plug(&plug);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mpage_ग_लिखोpages);

पूर्णांक mpage_ग_लिखोpage(काष्ठा page *page, get_block_t get_block,
	काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा mpage_data mpd = अणु
		.bio = शून्य,
		.last_block_in_bio = 0,
		.get_block = get_block,
		.use_ग_लिखोpage = 0,
	पूर्ण;
	पूर्णांक ret = __mpage_ग_लिखोpage(page, wbc, &mpd);
	अगर (mpd.bio) अणु
		पूर्णांक op_flags = (wbc->sync_mode == WB_SYNC_ALL ?
			  REQ_SYNC : 0);
		mpage_bio_submit(REQ_OP_WRITE, op_flags, mpd.bio);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mpage_ग_लिखोpage);
