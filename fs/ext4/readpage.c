<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext4/पढ़ोpage.c
 *
 * Copyright (C) 2002, Linus Torvalds.
 * Copyright (C) 2015, Google, Inc.
 *
 * This was originally taken from fs/mpage.c
 *
 * The ext4_mpage_पढ़ोpages() function here is पूर्णांकended to
 * replace mpage_पढ़ोahead() in the general हाल, not just क्रम
 * encrypted files.  It has some limitations (see below), where it
 * will fall back to पढ़ो_block_full_page(), but these limitations
 * should only be hit when page_size != block_size.
 *
 * This will allow us to attach a callback function to support ext4
 * encryption.
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
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/cleancache.h>

#समावेश "ext4.h"

#घोषणा NUM_PREALLOC_POST_READ_CTXS	128

अटल काष्ठा kmem_cache *bio_post_पढ़ो_ctx_cache;
अटल mempool_t *bio_post_पढ़ो_ctx_pool;

/* postprocessing steps क्रम पढ़ो bios */
क्रमागत bio_post_पढ़ो_step अणु
	STEP_INITIAL = 0,
	STEP_DECRYPT,
	STEP_VERITY,
	STEP_MAX,
पूर्ण;

काष्ठा bio_post_पढ़ो_ctx अणु
	काष्ठा bio *bio;
	काष्ठा work_काष्ठा work;
	अचिन्हित पूर्णांक cur_step;
	अचिन्हित पूर्णांक enabled_steps;
पूर्ण;

अटल व्योम __पढ़ो_end_io(काष्ठा bio *bio)
अणु
	काष्ठा page *page;
	काष्ठा bio_vec *bv;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bv, bio, iter_all) अणु
		page = bv->bv_page;

		/* PG_error was set अगर any post_पढ़ो step failed */
		अगर (bio->bi_status || PageError(page)) अणु
			ClearPageUptodate(page);
			/* will re-पढ़ो again later */
			ClearPageError(page);
		पूर्ण अन्यथा अणु
			SetPageUptodate(page);
		पूर्ण
		unlock_page(page);
	पूर्ण
	अगर (bio->bi_निजी)
		mempool_मुक्त(bio->bi_निजी, bio_post_पढ़ो_ctx_pool);
	bio_put(bio);
पूर्ण

अटल व्योम bio_post_पढ़ो_processing(काष्ठा bio_post_पढ़ो_ctx *ctx);

अटल व्योम decrypt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bio_post_पढ़ो_ctx *ctx =
		container_of(work, काष्ठा bio_post_पढ़ो_ctx, work);

	fscrypt_decrypt_bio(ctx->bio);

	bio_post_पढ़ो_processing(ctx);
पूर्ण

अटल व्योम verity_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bio_post_पढ़ो_ctx *ctx =
		container_of(work, काष्ठा bio_post_पढ़ो_ctx, work);
	काष्ठा bio *bio = ctx->bio;

	/*
	 * fsverity_verअगरy_bio() may call पढ़ोpages() again, and although verity
	 * will be disabled क्रम that, decryption may still be needed, causing
	 * another bio_post_पढ़ो_ctx to be allocated.  So to guarantee that
	 * mempool_alloc() never deadlocks we must मुक्त the current ctx first.
	 * This is safe because verity is the last post-पढ़ो step.
	 */
	BUILD_BUG_ON(STEP_VERITY + 1 != STEP_MAX);
	mempool_मुक्त(ctx, bio_post_पढ़ो_ctx_pool);
	bio->bi_निजी = शून्य;

	fsverity_verअगरy_bio(bio);

	__पढ़ो_end_io(bio);
पूर्ण

अटल व्योम bio_post_पढ़ो_processing(काष्ठा bio_post_पढ़ो_ctx *ctx)
अणु
	/*
	 * We use dअगरferent work queues क्रम decryption and क्रम verity because
	 * verity may require पढ़ोing metadata pages that need decryption, and
	 * we shouldn't recurse to the same workqueue.
	 */
	चयन (++ctx->cur_step) अणु
	हाल STEP_DECRYPT:
		अगर (ctx->enabled_steps & (1 << STEP_DECRYPT)) अणु
			INIT_WORK(&ctx->work, decrypt_work);
			fscrypt_enqueue_decrypt_work(&ctx->work);
			वापस;
		पूर्ण
		ctx->cur_step++;
		fallthrough;
	हाल STEP_VERITY:
		अगर (ctx->enabled_steps & (1 << STEP_VERITY)) अणु
			INIT_WORK(&ctx->work, verity_work);
			fsverity_enqueue_verअगरy_work(&ctx->work);
			वापस;
		पूर्ण
		ctx->cur_step++;
		fallthrough;
	शेष:
		__पढ़ो_end_io(ctx->bio);
	पूर्ण
पूर्ण

अटल bool bio_post_पढ़ो_required(काष्ठा bio *bio)
अणु
	वापस bio->bi_निजी && !bio->bi_status;
पूर्ण

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
	अगर (bio_post_पढ़ो_required(bio)) अणु
		काष्ठा bio_post_पढ़ो_ctx *ctx = bio->bi_निजी;

		ctx->cur_step = STEP_INITIAL;
		bio_post_पढ़ो_processing(ctx);
		वापस;
	पूर्ण
	__पढ़ो_end_io(bio);
पूर्ण

अटल अंतरभूत bool ext4_need_verity(स्थिर काष्ठा inode *inode, pgoff_t idx)
अणु
	वापस fsverity_active(inode) &&
	       idx < DIV_ROUND_UP(inode->i_size, PAGE_SIZE);
पूर्ण

अटल व्योम ext4_set_bio_post_पढ़ो_ctx(काष्ठा bio *bio,
				       स्थिर काष्ठा inode *inode,
				       pgoff_t first_idx)
अणु
	अचिन्हित पूर्णांक post_पढ़ो_steps = 0;

	अगर (fscrypt_inode_uses_fs_layer_crypto(inode))
		post_पढ़ो_steps |= 1 << STEP_DECRYPT;

	अगर (ext4_need_verity(inode, first_idx))
		post_पढ़ो_steps |= 1 << STEP_VERITY;

	अगर (post_पढ़ो_steps) अणु
		/* Due to the mempool, this never fails. */
		काष्ठा bio_post_पढ़ो_ctx *ctx =
			mempool_alloc(bio_post_पढ़ो_ctx_pool, GFP_NOFS);

		ctx->bio = bio;
		ctx->enabled_steps = post_पढ़ो_steps;
		bio->bi_निजी = ctx;
	पूर्ण
पूर्ण

अटल अंतरभूत loff_t ext4_पढ़ोpage_limit(काष्ठा inode *inode)
अणु
	अगर (IS_ENABLED(CONFIG_FS_VERITY) &&
	    (IS_VERITY(inode) || ext4_verity_in_progress(inode)))
		वापस inode->i_sb->s_maxbytes;

	वापस i_size_पढ़ो(inode);
पूर्ण

पूर्णांक ext4_mpage_पढ़ोpages(काष्ठा inode *inode,
		काष्ठा पढ़ोahead_control *rac, काष्ठा page *page)
अणु
	काष्ठा bio *bio = शून्य;
	sector_t last_block_in_bio = 0;

	स्थिर अचिन्हित blkbits = inode->i_blkbits;
	स्थिर अचिन्हित blocks_per_page = PAGE_SIZE >> blkbits;
	स्थिर अचिन्हित blocksize = 1 << blkbits;
	sector_t next_block;
	sector_t block_in_file;
	sector_t last_block;
	sector_t last_block_in_file;
	sector_t blocks[MAX_BUF_PER_PAGE];
	अचिन्हित page_block;
	काष्ठा block_device *bdev = inode->i_sb->s_bdev;
	पूर्णांक length;
	अचिन्हित relative_block = 0;
	काष्ठा ext4_map_blocks map;
	अचिन्हित पूर्णांक nr_pages = rac ? पढ़ोahead_count(rac) : 1;

	map.m_pblk = 0;
	map.m_lblk = 0;
	map.m_len = 0;
	map.m_flags = 0;

	क्रम (; nr_pages; nr_pages--) अणु
		पूर्णांक fully_mapped = 1;
		अचिन्हित first_hole = blocks_per_page;

		अगर (rac) अणु
			page = पढ़ोahead_page(rac);
			prefetchw(&page->flags);
		पूर्ण

		अगर (page_has_buffers(page))
			जाओ confused;

		block_in_file = next_block =
			(sector_t)page->index << (PAGE_SHIFT - blkbits);
		last_block = block_in_file + nr_pages * blocks_per_page;
		last_block_in_file = (ext4_पढ़ोpage_limit(inode) +
				      blocksize - 1) >> blkbits;
		अगर (last_block > last_block_in_file)
			last_block = last_block_in_file;
		page_block = 0;

		/*
		 * Map blocks using the previous result first.
		 */
		अगर ((map.m_flags & EXT4_MAP_MAPPED) &&
		    block_in_file > map.m_lblk &&
		    block_in_file < (map.m_lblk + map.m_len)) अणु
			अचिन्हित map_offset = block_in_file - map.m_lblk;
			अचिन्हित last = map.m_len - map_offset;

			क्रम (relative_block = 0; ; relative_block++) अणु
				अगर (relative_block == last) अणु
					/* needed? */
					map.m_flags &= ~EXT4_MAP_MAPPED;
					अवरोध;
				पूर्ण
				अगर (page_block == blocks_per_page)
					अवरोध;
				blocks[page_block] = map.m_pblk + map_offset +
					relative_block;
				page_block++;
				block_in_file++;
			पूर्ण
		पूर्ण

		/*
		 * Then करो more ext4_map_blocks() calls until we are
		 * करोne with this page.
		 */
		जबतक (page_block < blocks_per_page) अणु
			अगर (block_in_file < last_block) अणु
				map.m_lblk = block_in_file;
				map.m_len = last_block - block_in_file;

				अगर (ext4_map_blocks(शून्य, inode, &map, 0) < 0) अणु
				set_error_page:
					SetPageError(page);
					zero_user_segment(page, 0,
							  PAGE_SIZE);
					unlock_page(page);
					जाओ next_page;
				पूर्ण
			पूर्ण
			अगर ((map.m_flags & EXT4_MAP_MAPPED) == 0) अणु
				fully_mapped = 0;
				अगर (first_hole == blocks_per_page)
					first_hole = page_block;
				page_block++;
				block_in_file++;
				जारी;
			पूर्ण
			अगर (first_hole != blocks_per_page)
				जाओ confused;		/* hole -> non-hole */

			/* Contiguous blocks? */
			अगर (page_block && blocks[page_block-1] != map.m_pblk-1)
				जाओ confused;
			क्रम (relative_block = 0; ; relative_block++) अणु
				अगर (relative_block == map.m_len) अणु
					/* needed? */
					map.m_flags &= ~EXT4_MAP_MAPPED;
					अवरोध;
				पूर्ण अन्यथा अगर (page_block == blocks_per_page)
					अवरोध;
				blocks[page_block] = map.m_pblk+relative_block;
				page_block++;
				block_in_file++;
			पूर्ण
		पूर्ण
		अगर (first_hole != blocks_per_page) अणु
			zero_user_segment(page, first_hole << blkbits,
					  PAGE_SIZE);
			अगर (first_hole == 0) अणु
				अगर (ext4_need_verity(inode, page->index) &&
				    !fsverity_verअगरy_page(page))
					जाओ set_error_page;
				SetPageUptodate(page);
				unlock_page(page);
				जाओ next_page;
			पूर्ण
		पूर्ण अन्यथा अगर (fully_mapped) अणु
			SetPageMappedToDisk(page);
		पूर्ण
		अगर (fully_mapped && blocks_per_page == 1 &&
		    !PageUptodate(page) && cleancache_get_page(page) == 0) अणु
			SetPageUptodate(page);
			जाओ confused;
		पूर्ण

		/*
		 * This page will go to BIO.  Do we need to send this
		 * BIO off first?
		 */
		अगर (bio && (last_block_in_bio != blocks[0] - 1 ||
			    !fscrypt_mergeable_bio(bio, inode, next_block))) अणु
		submit_and_पुनः_स्मृति:
			submit_bio(bio);
			bio = शून्य;
		पूर्ण
		अगर (bio == शून्य) अणु
			/*
			 * bio_alloc will _always_ be able to allocate a bio अगर
			 * __GFP_सूचीECT_RECLAIM is set, see bio_alloc_bioset().
			 */
			bio = bio_alloc(GFP_KERNEL, bio_max_segs(nr_pages));
			fscrypt_set_bio_crypt_ctx(bio, inode, next_block,
						  GFP_KERNEL);
			ext4_set_bio_post_पढ़ो_ctx(bio, inode, page->index);
			bio_set_dev(bio, bdev);
			bio->bi_iter.bi_sector = blocks[0] << (blkbits - 9);
			bio->bi_end_io = mpage_end_io;
			bio_set_op_attrs(bio, REQ_OP_READ,
						rac ? REQ_RAHEAD : 0);
		पूर्ण

		length = first_hole << blkbits;
		अगर (bio_add_page(bio, page, length, 0) < length)
			जाओ submit_and_पुनः_स्मृति;

		अगर (((map.m_flags & EXT4_MAP_BOUNDARY) &&
		     (relative_block == map.m_len)) ||
		    (first_hole != blocks_per_page)) अणु
			submit_bio(bio);
			bio = शून्य;
		पूर्ण अन्यथा
			last_block_in_bio = blocks[blocks_per_page - 1];
		जाओ next_page;
	confused:
		अगर (bio) अणु
			submit_bio(bio);
			bio = शून्य;
		पूर्ण
		अगर (!PageUptodate(page))
			block_पढ़ो_full_page(page, ext4_get_block);
		अन्यथा
			unlock_page(page);
	next_page:
		अगर (rac)
			put_page(page);
	पूर्ण
	अगर (bio)
		submit_bio(bio);
	वापस 0;
पूर्ण

पूर्णांक __init ext4_init_post_पढ़ो_processing(व्योम)
अणु
	bio_post_पढ़ो_ctx_cache =
		kmem_cache_create("ext4_bio_post_read_ctx",
				  माप(काष्ठा bio_post_पढ़ो_ctx), 0, 0, शून्य);
	अगर (!bio_post_पढ़ो_ctx_cache)
		जाओ fail;
	bio_post_पढ़ो_ctx_pool =
		mempool_create_slab_pool(NUM_PREALLOC_POST_READ_CTXS,
					 bio_post_पढ़ो_ctx_cache);
	अगर (!bio_post_पढ़ो_ctx_pool)
		जाओ fail_मुक्त_cache;
	वापस 0;

fail_मुक्त_cache:
	kmem_cache_destroy(bio_post_पढ़ो_ctx_cache);
fail:
	वापस -ENOMEM;
पूर्ण

व्योम ext4_निकास_post_पढ़ो_processing(व्योम)
अणु
	mempool_destroy(bio_post_पढ़ो_ctx_pool);
	kmem_cache_destroy(bio_post_पढ़ो_ctx_cache);
पूर्ण
