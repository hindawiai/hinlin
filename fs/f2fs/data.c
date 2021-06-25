<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/data.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mpage.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blk-crypto.h>
#समावेश <linux/swap.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/uपन.स>
#समावेश <linux/cleancache.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fiemap.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "segment.h"
#समावेश <trace/events/f2fs.h>

#घोषणा NUM_PREALLOC_POST_READ_CTXS	128

अटल काष्ठा kmem_cache *bio_post_पढ़ो_ctx_cache;
अटल काष्ठा kmem_cache *bio_entry_slab;
अटल mempool_t *bio_post_पढ़ो_ctx_pool;
अटल काष्ठा bio_set f2fs_bioset;

#घोषणा	F2FS_BIO_POOL_SIZE	NR_CURSEG_TYPE

पूर्णांक __init f2fs_init_bioset(व्योम)
अणु
	अगर (bioset_init(&f2fs_bioset, F2FS_BIO_POOL_SIZE,
					0, BIOSET_NEED_BVECS))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम f2fs_destroy_bioset(व्योम)
अणु
	bioset_निकास(&f2fs_bioset);
पूर्ण

अटल bool __is_cp_guaranteed(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा inode *inode;
	काष्ठा f2fs_sb_info *sbi;

	अगर (!mapping)
		वापस false;

	अगर (f2fs_is_compressed_page(page))
		वापस false;

	inode = mapping->host;
	sbi = F2FS_I_SB(inode);

	अगर (inode->i_ino == F2FS_META_INO(sbi) ||
			inode->i_ino == F2FS_NODE_INO(sbi) ||
			S_ISसूची(inode->i_mode) ||
			(S_ISREG(inode->i_mode) &&
			(f2fs_is_atomic_file(inode) || IS_NOQUOTA(inode))) ||
			is_cold_data(page))
		वापस true;
	वापस false;
पूर्ण

अटल क्रमागत count_type __पढ़ो_io_type(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_file_mapping(page);

	अगर (mapping) अणु
		काष्ठा inode *inode = mapping->host;
		काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

		अगर (inode->i_ino == F2FS_META_INO(sbi))
			वापस F2FS_RD_META;

		अगर (inode->i_ino == F2FS_NODE_INO(sbi))
			वापस F2FS_RD_NODE;
	पूर्ण
	वापस F2FS_RD_DATA;
पूर्ण

/* postprocessing steps क्रम पढ़ो bios */
क्रमागत bio_post_पढ़ो_step अणु
#अगर_घोषित CONFIG_FS_ENCRYPTION
	STEP_DECRYPT	= 1 << 0,
#अन्यथा
	STEP_DECRYPT	= 0,	/* compile out the decryption-related code */
#पूर्ण_अगर
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	STEP_DECOMPRESS	= 1 << 1,
#अन्यथा
	STEP_DECOMPRESS	= 0,	/* compile out the decompression-related code */
#पूर्ण_अगर
#अगर_घोषित CONFIG_FS_VERITY
	STEP_VERITY	= 1 << 2,
#अन्यथा
	STEP_VERITY	= 0,	/* compile out the verity-related code */
#पूर्ण_अगर
पूर्ण;

काष्ठा bio_post_पढ़ो_ctx अणु
	काष्ठा bio *bio;
	काष्ठा f2fs_sb_info *sbi;
	काष्ठा work_काष्ठा work;
	अचिन्हित पूर्णांक enabled_steps;
पूर्ण;

अटल व्योम f2fs_finish_पढ़ो_bio(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bv;
	काष्ठा bvec_iter_all iter_all;

	/*
	 * Update and unlock the bio's pagecache pages, and put the
	 * decompression context क्रम any compressed pages.
	 */
	bio_क्रम_each_segment_all(bv, bio, iter_all) अणु
		काष्ठा page *page = bv->bv_page;

		अगर (f2fs_is_compressed_page(page)) अणु
			अगर (bio->bi_status)
				f2fs_end_पढ़ो_compressed_page(page, true);
			f2fs_put_page_dic(page);
			जारी;
		पूर्ण

		/* PG_error was set अगर decryption or verity failed. */
		अगर (bio->bi_status || PageError(page)) अणु
			ClearPageUptodate(page);
			/* will re-पढ़ो again later */
			ClearPageError(page);
		पूर्ण अन्यथा अणु
			SetPageUptodate(page);
		पूर्ण
		dec_page_count(F2FS_P_SB(page), __पढ़ो_io_type(page));
		unlock_page(page);
	पूर्ण

	अगर (bio->bi_निजी)
		mempool_मुक्त(bio->bi_निजी, bio_post_पढ़ो_ctx_pool);
	bio_put(bio);
पूर्ण

अटल व्योम f2fs_verअगरy_bio(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bio_post_पढ़ो_ctx *ctx =
		container_of(work, काष्ठा bio_post_पढ़ो_ctx, work);
	काष्ठा bio *bio = ctx->bio;
	bool may_have_compressed_pages = (ctx->enabled_steps & STEP_DECOMPRESS);

	/*
	 * fsverity_verअगरy_bio() may call पढ़ोpages() again, and जबतक verity
	 * will be disabled क्रम this, decryption and/or decompression may still
	 * be needed, resulting in another bio_post_पढ़ो_ctx being allocated.
	 * So to prevent deadlocks we need to release the current ctx to the
	 * mempool first.  This assumes that verity is the last post-पढ़ो step.
	 */
	mempool_मुक्त(ctx, bio_post_पढ़ो_ctx_pool);
	bio->bi_निजी = शून्य;

	/*
	 * Verअगरy the bio's pages with fs-verity.  Exclude compressed pages,
	 * as those were handled separately by f2fs_end_पढ़ो_compressed_page().
	 */
	अगर (may_have_compressed_pages) अणु
		काष्ठा bio_vec *bv;
		काष्ठा bvec_iter_all iter_all;

		bio_क्रम_each_segment_all(bv, bio, iter_all) अणु
			काष्ठा page *page = bv->bv_page;

			अगर (!f2fs_is_compressed_page(page) &&
			    !PageError(page) && !fsverity_verअगरy_page(page))
				SetPageError(page);
		पूर्ण
	पूर्ण अन्यथा अणु
		fsverity_verअगरy_bio(bio);
	पूर्ण

	f2fs_finish_पढ़ो_bio(bio);
पूर्ण

/*
 * If the bio's data needs to be verअगरied with fs-verity, then enqueue the
 * verity work क्रम the bio.  Otherwise finish the bio now.
 *
 * Note that to aव्योम deadlocks, the verity work can't be करोne on the
 * decryption/decompression workqueue.  This is because verअगरying the data pages
 * can involve पढ़ोing verity metadata pages from the file, and these verity
 * metadata pages may be encrypted and/or compressed.
 */
अटल व्योम f2fs_verअगरy_and_finish_bio(काष्ठा bio *bio)
अणु
	काष्ठा bio_post_पढ़ो_ctx *ctx = bio->bi_निजी;

	अगर (ctx && (ctx->enabled_steps & STEP_VERITY)) अणु
		INIT_WORK(&ctx->work, f2fs_verअगरy_bio);
		fsverity_enqueue_verअगरy_work(&ctx->work);
	पूर्ण अन्यथा अणु
		f2fs_finish_पढ़ो_bio(bio);
	पूर्ण
पूर्ण

/*
 * Handle STEP_DECOMPRESS by decompressing any compressed clusters whose last
 * reमुख्यing page was पढ़ो by @ctx->bio.
 *
 * Note that a bio may span clusters (even a mix of compressed and uncompressed
 * clusters) or be क्रम just part of a cluster.  STEP_DECOMPRESS just indicates
 * that the bio includes at least one compressed page.  The actual decompression
 * is करोne on a per-cluster basis, not a per-bio basis.
 */
अटल व्योम f2fs_handle_step_decompress(काष्ठा bio_post_पढ़ो_ctx *ctx)
अणु
	काष्ठा bio_vec *bv;
	काष्ठा bvec_iter_all iter_all;
	bool all_compressed = true;

	bio_क्रम_each_segment_all(bv, ctx->bio, iter_all) अणु
		काष्ठा page *page = bv->bv_page;

		/* PG_error was set अगर decryption failed. */
		अगर (f2fs_is_compressed_page(page))
			f2fs_end_पढ़ो_compressed_page(page, PageError(page));
		अन्यथा
			all_compressed = false;
	पूर्ण

	/*
	 * Optimization: अगर all the bio's pages are compressed, then scheduling
	 * the per-bio verity work is unnecessary, as verity will be fully
	 * handled at the compression cluster level.
	 */
	अगर (all_compressed)
		ctx->enabled_steps &= ~STEP_VERITY;
पूर्ण

अटल व्योम f2fs_post_पढ़ो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bio_post_पढ़ो_ctx *ctx =
		container_of(work, काष्ठा bio_post_पढ़ो_ctx, work);

	अगर (ctx->enabled_steps & STEP_DECRYPT)
		fscrypt_decrypt_bio(ctx->bio);

	अगर (ctx->enabled_steps & STEP_DECOMPRESS)
		f2fs_handle_step_decompress(ctx);

	f2fs_verअगरy_and_finish_bio(ctx->bio);
पूर्ण

अटल व्योम f2fs_पढ़ो_end_io(काष्ठा bio *bio)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_P_SB(bio_first_page_all(bio));
	काष्ठा bio_post_पढ़ो_ctx *ctx = bio->bi_निजी;

	अगर (समय_प्रकारo_inject(sbi, FAULT_READ_IO)) अणु
		f2fs_show_injection_info(sbi, FAULT_READ_IO);
		bio->bi_status = BLK_STS_IOERR;
	पूर्ण

	अगर (bio->bi_status) अणु
		f2fs_finish_पढ़ो_bio(bio);
		वापस;
	पूर्ण

	अगर (ctx && (ctx->enabled_steps & (STEP_DECRYPT | STEP_DECOMPRESS))) अणु
		INIT_WORK(&ctx->work, f2fs_post_पढ़ो_work);
		queue_work(ctx->sbi->post_पढ़ो_wq, &ctx->work);
	पूर्ण अन्यथा अणु
		f2fs_verअगरy_and_finish_bio(bio);
	पूर्ण
पूर्ण

अटल व्योम f2fs_ग_लिखो_end_io(काष्ठा bio *bio)
अणु
	काष्ठा f2fs_sb_info *sbi = bio->bi_निजी;
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	अगर (समय_प्रकारo_inject(sbi, FAULT_WRITE_IO)) अणु
		f2fs_show_injection_info(sbi, FAULT_WRITE_IO);
		bio->bi_status = BLK_STS_IOERR;
	पूर्ण

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		काष्ठा page *page = bvec->bv_page;
		क्रमागत count_type type = WB_DATA_TYPE(page);

		अगर (IS_DUMMY_WRITTEN_PAGE(page)) अणु
			set_page_निजी(page, (अचिन्हित दीर्घ)शून्य);
			ClearPagePrivate(page);
			unlock_page(page);
			mempool_मुक्त(page, sbi->ग_लिखो_io_dummy);

			अगर (unlikely(bio->bi_status))
				f2fs_stop_checkpoपूर्णांक(sbi, true);
			जारी;
		पूर्ण

		fscrypt_finalize_bounce_page(&page);

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
		अगर (f2fs_is_compressed_page(page)) अणु
			f2fs_compress_ग_लिखो_end_io(bio, page);
			जारी;
		पूर्ण
#पूर्ण_अगर

		अगर (unlikely(bio->bi_status)) अणु
			mapping_set_error(page->mapping, -EIO);
			अगर (type == F2FS_WB_CP_DATA)
				f2fs_stop_checkpoपूर्णांक(sbi, true);
		पूर्ण

		f2fs_bug_on(sbi, page->mapping == NODE_MAPPING(sbi) &&
					page->index != nid_of_node(page));

		dec_page_count(sbi, type);
		अगर (f2fs_in_warm_node_list(sbi, page))
			f2fs_del_fsync_node_entry(sbi, page);
		clear_cold_data(page);
		end_page_ग_लिखोback(page);
	पूर्ण
	अगर (!get_pages(sbi, F2FS_WB_CP_DATA) &&
				wq_has_sleeper(&sbi->cp_रुको))
		wake_up(&sbi->cp_रुको);

	bio_put(bio);
पूर्ण

काष्ठा block_device *f2fs_target_device(काष्ठा f2fs_sb_info *sbi,
				block_t blk_addr, काष्ठा bio *bio)
अणु
	काष्ठा block_device *bdev = sbi->sb->s_bdev;
	पूर्णांक i;

	अगर (f2fs_is_multi_device(sbi)) अणु
		क्रम (i = 0; i < sbi->s_ndevs; i++) अणु
			अगर (FDEV(i).start_blk <= blk_addr &&
			    FDEV(i).end_blk >= blk_addr) अणु
				blk_addr -= FDEV(i).start_blk;
				bdev = FDEV(i).bdev;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (bio) अणु
		bio_set_dev(bio, bdev);
		bio->bi_iter.bi_sector = SECTOR_FROM_BLOCK(blk_addr);
	पूर्ण
	वापस bdev;
पूर्ण

पूर्णांक f2fs_target_device_index(काष्ठा f2fs_sb_info *sbi, block_t blkaddr)
अणु
	पूर्णांक i;

	अगर (!f2fs_is_multi_device(sbi))
		वापस 0;

	क्रम (i = 0; i < sbi->s_ndevs; i++)
		अगर (FDEV(i).start_blk <= blkaddr && FDEV(i).end_blk >= blkaddr)
			वापस i;
	वापस 0;
पूर्ण

अटल काष्ठा bio *__bio_alloc(काष्ठा f2fs_io_info *fio, पूर्णांक npages)
अणु
	काष्ठा f2fs_sb_info *sbi = fio->sbi;
	काष्ठा bio *bio;

	bio = bio_alloc_bioset(GFP_NOIO, npages, &f2fs_bioset);

	f2fs_target_device(sbi, fio->new_blkaddr, bio);
	अगर (is_पढ़ो_io(fio->op)) अणु
		bio->bi_end_io = f2fs_पढ़ो_end_io;
		bio->bi_निजी = शून्य;
	पूर्ण अन्यथा अणु
		bio->bi_end_io = f2fs_ग_लिखो_end_io;
		bio->bi_निजी = sbi;
		bio->bi_ग_लिखो_hपूर्णांक = f2fs_io_type_to_rw_hपूर्णांक(sbi,
						fio->type, fio->temp);
	पूर्ण
	अगर (fio->io_wbc)
		wbc_init_bio(fio->io_wbc, bio);

	वापस bio;
पूर्ण

अटल व्योम f2fs_set_bio_crypt_ctx(काष्ठा bio *bio, स्थिर काष्ठा inode *inode,
				  pgoff_t first_idx,
				  स्थिर काष्ठा f2fs_io_info *fio,
				  gfp_t gfp_mask)
अणु
	/*
	 * The f2fs garbage collector sets ->encrypted_page when it wants to
	 * पढ़ो/ग_लिखो raw data without encryption.
	 */
	अगर (!fio || !fio->encrypted_page)
		fscrypt_set_bio_crypt_ctx(bio, inode, first_idx, gfp_mask);
पूर्ण

अटल bool f2fs_crypt_mergeable_bio(काष्ठा bio *bio, स्थिर काष्ठा inode *inode,
				     pgoff_t next_idx,
				     स्थिर काष्ठा f2fs_io_info *fio)
अणु
	/*
	 * The f2fs garbage collector sets ->encrypted_page when it wants to
	 * पढ़ो/ग_लिखो raw data without encryption.
	 */
	अगर (fio && fio->encrypted_page)
		वापस !bio_has_crypt_ctx(bio);

	वापस fscrypt_mergeable_bio(bio, inode, next_idx);
पूर्ण

अटल अंतरभूत व्योम __submit_bio(काष्ठा f2fs_sb_info *sbi,
				काष्ठा bio *bio, क्रमागत page_type type)
अणु
	अगर (!is_पढ़ो_io(bio_op(bio))) अणु
		अचिन्हित पूर्णांक start;

		अगर (type != DATA && type != NODE)
			जाओ submit_io;

		अगर (f2fs_lfs_mode(sbi) && current->plug)
			blk_finish_plug(current->plug);

		अगर (!F2FS_IO_ALIGNED(sbi))
			जाओ submit_io;

		start = bio->bi_iter.bi_size >> F2FS_BLKSIZE_BITS;
		start %= F2FS_IO_SIZE(sbi);

		अगर (start == 0)
			जाओ submit_io;

		/* fill dummy pages */
		क्रम (; start < F2FS_IO_SIZE(sbi); start++) अणु
			काष्ठा page *page =
				mempool_alloc(sbi->ग_लिखो_io_dummy,
					      GFP_NOIO | __GFP_NOFAIL);
			f2fs_bug_on(sbi, !page);

			zero_user_segment(page, 0, PAGE_SIZE);
			SetPagePrivate(page);
			set_page_निजी(page, DUMMY_WRITTEN_PAGE);
			lock_page(page);
			अगर (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE)
				f2fs_bug_on(sbi, 1);
		पूर्ण
		/*
		 * In the NODE हाल, we lose next block address chain. So, we
		 * need to करो checkpoपूर्णांक in f2fs_sync_file.
		 */
		अगर (type == NODE)
			set_sbi_flag(sbi, SBI_NEED_CP);
	पूर्ण
submit_io:
	अगर (is_पढ़ो_io(bio_op(bio)))
		trace_f2fs_submit_पढ़ो_bio(sbi->sb, type, bio);
	अन्यथा
		trace_f2fs_submit_ग_लिखो_bio(sbi->sb, type, bio);
	submit_bio(bio);
पूर्ण

व्योम f2fs_submit_bio(काष्ठा f2fs_sb_info *sbi,
				काष्ठा bio *bio, क्रमागत page_type type)
अणु
	__submit_bio(sbi, bio, type);
पूर्ण

अटल व्योम __attach_io_flag(काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा f2fs_sb_info *sbi = fio->sbi;
	अचिन्हित पूर्णांक temp_mask = (1 << NR_TEMP_TYPE) - 1;
	अचिन्हित पूर्णांक io_flag, fua_flag, meta_flag;

	अगर (fio->type == DATA)
		io_flag = sbi->data_io_flag;
	अन्यथा अगर (fio->type == NODE)
		io_flag = sbi->node_io_flag;
	अन्यथा
		वापस;

	fua_flag = io_flag & temp_mask;
	meta_flag = (io_flag >> NR_TEMP_TYPE) & temp_mask;

	/*
	 * data/node io flag bits per temp:
	 *      REQ_META     |      REQ_FUA      |
	 *    5 |    4 |   3 |    2 |    1 |   0 |
	 * Cold | Warm | Hot | Cold | Warm | Hot |
	 */
	अगर ((1 << fio->temp) & meta_flag)
		fio->op_flags |= REQ_META;
	अगर ((1 << fio->temp) & fua_flag)
		fio->op_flags |= REQ_FUA;
पूर्ण

अटल व्योम __submit_merged_bio(काष्ठा f2fs_bio_info *io)
अणु
	काष्ठा f2fs_io_info *fio = &io->fio;

	अगर (!io->bio)
		वापस;

	__attach_io_flag(fio);
	bio_set_op_attrs(io->bio, fio->op, fio->op_flags);

	अगर (is_पढ़ो_io(fio->op))
		trace_f2fs_prepare_पढ़ो_bio(io->sbi->sb, fio->type, io->bio);
	अन्यथा
		trace_f2fs_prepare_ग_लिखो_bio(io->sbi->sb, fio->type, io->bio);

	__submit_bio(io->sbi, io->bio, fio->type);
	io->bio = शून्य;
पूर्ण

अटल bool __has_merged_page(काष्ठा bio *bio, काष्ठा inode *inode,
						काष्ठा page *page, nid_t ino)
अणु
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	अगर (!bio)
		वापस false;

	अगर (!inode && !page && !ino)
		वापस true;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		काष्ठा page *target = bvec->bv_page;

		अगर (fscrypt_is_bounce_page(target)) अणु
			target = fscrypt_pagecache_page(target);
			अगर (IS_ERR(target))
				जारी;
		पूर्ण
		अगर (f2fs_is_compressed_page(target)) अणु
			target = f2fs_compress_control_page(target);
			अगर (IS_ERR(target))
				जारी;
		पूर्ण

		अगर (inode && inode == target->mapping->host)
			वापस true;
		अगर (page && page == target)
			वापस true;
		अगर (ino && ino == ino_of_node(target))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम __f2fs_submit_merged_ग_लिखो(काष्ठा f2fs_sb_info *sbi,
				क्रमागत page_type type, क्रमागत temp_type temp)
अणु
	क्रमागत page_type btype = PAGE_TYPE_OF_BIO(type);
	काष्ठा f2fs_bio_info *io = sbi->ग_लिखो_io[btype] + temp;

	करोwn_ग_लिखो(&io->io_rwsem);

	/* change META to META_FLUSH in the checkpoपूर्णांक procedure */
	अगर (type >= META_FLUSH) अणु
		io->fio.type = META_FLUSH;
		io->fio.op = REQ_OP_WRITE;
		io->fio.op_flags = REQ_META | REQ_PRIO | REQ_SYNC;
		अगर (!test_opt(sbi, NOBARRIER))
			io->fio.op_flags |= REQ_PREFLUSH | REQ_FUA;
	पूर्ण
	__submit_merged_bio(io);
	up_ग_लिखो(&io->io_rwsem);
पूर्ण

अटल व्योम __submit_merged_ग_लिखो_cond(काष्ठा f2fs_sb_info *sbi,
				काष्ठा inode *inode, काष्ठा page *page,
				nid_t ino, क्रमागत page_type type, bool क्रमce)
अणु
	क्रमागत temp_type temp;
	bool ret = true;

	क्रम (temp = HOT; temp < NR_TEMP_TYPE; temp++) अणु
		अगर (!क्रमce)	अणु
			क्रमागत page_type btype = PAGE_TYPE_OF_BIO(type);
			काष्ठा f2fs_bio_info *io = sbi->ग_लिखो_io[btype] + temp;

			करोwn_पढ़ो(&io->io_rwsem);
			ret = __has_merged_page(io->bio, inode, page, ino);
			up_पढ़ो(&io->io_rwsem);
		पूर्ण
		अगर (ret)
			__f2fs_submit_merged_ग_लिखो(sbi, type, temp);

		/* TODO: use HOT temp only क्रम meta pages now. */
		अगर (type >= META)
			अवरोध;
	पूर्ण
पूर्ण

व्योम f2fs_submit_merged_ग_लिखो(काष्ठा f2fs_sb_info *sbi, क्रमागत page_type type)
अणु
	__submit_merged_ग_लिखो_cond(sbi, शून्य, शून्य, 0, type, true);
पूर्ण

व्योम f2fs_submit_merged_ग_लिखो_cond(काष्ठा f2fs_sb_info *sbi,
				काष्ठा inode *inode, काष्ठा page *page,
				nid_t ino, क्रमागत page_type type)
अणु
	__submit_merged_ग_लिखो_cond(sbi, inode, page, ino, type, false);
पूर्ण

व्योम f2fs_flush_merged_ग_लिखोs(काष्ठा f2fs_sb_info *sbi)
अणु
	f2fs_submit_merged_ग_लिखो(sbi, DATA);
	f2fs_submit_merged_ग_लिखो(sbi, NODE);
	f2fs_submit_merged_ग_लिखो(sbi, META);
पूर्ण

/*
 * Fill the locked page with data located in the block address.
 * A caller needs to unlock the page on failure.
 */
पूर्णांक f2fs_submit_page_bio(काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा bio *bio;
	काष्ठा page *page = fio->encrypted_page ?
			fio->encrypted_page : fio->page;

	अगर (!f2fs_is_valid_blkaddr(fio->sbi, fio->new_blkaddr,
			fio->is_por ? META_POR : (__is_meta_io(fio) ?
			META_GENERIC : DATA_GENERIC_ENHANCE)))
		वापस -EFSCORRUPTED;

	trace_f2fs_submit_page_bio(page, fio);

	/* Allocate a new bio */
	bio = __bio_alloc(fio, 1);

	f2fs_set_bio_crypt_ctx(bio, fio->page->mapping->host,
			       fio->page->index, fio, GFP_NOIO);

	अगर (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE) अणु
		bio_put(bio);
		वापस -EFAULT;
	पूर्ण

	अगर (fio->io_wbc && !is_पढ़ो_io(fio->op))
		wbc_account_cgroup_owner(fio->io_wbc, page, PAGE_SIZE);

	__attach_io_flag(fio);
	bio_set_op_attrs(bio, fio->op, fio->op_flags);

	inc_page_count(fio->sbi, is_पढ़ो_io(fio->op) ?
			__पढ़ो_io_type(page): WB_DATA_TYPE(fio->page));

	__submit_bio(fio->sbi, bio, fio->type);
	वापस 0;
पूर्ण

अटल bool page_is_mergeable(काष्ठा f2fs_sb_info *sbi, काष्ठा bio *bio,
				block_t last_blkaddr, block_t cur_blkaddr)
अणु
	अगर (unlikely(sbi->max_io_bytes &&
			bio->bi_iter.bi_size >= sbi->max_io_bytes))
		वापस false;
	अगर (last_blkaddr + 1 != cur_blkaddr)
		वापस false;
	वापस bio->bi_bdev == f2fs_target_device(sbi, cur_blkaddr, शून्य);
पूर्ण

अटल bool io_type_is_mergeable(काष्ठा f2fs_bio_info *io,
						काष्ठा f2fs_io_info *fio)
अणु
	अगर (io->fio.op != fio->op)
		वापस false;
	वापस io->fio.op_flags == fio->op_flags;
पूर्ण

अटल bool io_is_mergeable(काष्ठा f2fs_sb_info *sbi, काष्ठा bio *bio,
					काष्ठा f2fs_bio_info *io,
					काष्ठा f2fs_io_info *fio,
					block_t last_blkaddr,
					block_t cur_blkaddr)
अणु
	अगर (F2FS_IO_ALIGNED(sbi) && (fio->type == DATA || fio->type == NODE)) अणु
		अचिन्हित पूर्णांक filled_blocks =
				F2FS_BYTES_TO_BLK(bio->bi_iter.bi_size);
		अचिन्हित पूर्णांक io_size = F2FS_IO_SIZE(sbi);
		अचिन्हित पूर्णांक left_vecs = bio->bi_max_vecs - bio->bi_vcnt;

		/* IOs in bio is aligned and left space of vectors is not enough */
		अगर (!(filled_blocks % io_size) && left_vecs < io_size)
			वापस false;
	पूर्ण
	अगर (!page_is_mergeable(sbi, bio, last_blkaddr, cur_blkaddr))
		वापस false;
	वापस io_type_is_mergeable(io, fio);
पूर्ण

अटल व्योम add_bio_entry(काष्ठा f2fs_sb_info *sbi, काष्ठा bio *bio,
				काष्ठा page *page, क्रमागत temp_type temp)
अणु
	काष्ठा f2fs_bio_info *io = sbi->ग_लिखो_io[DATA] + temp;
	काष्ठा bio_entry *be;

	be = f2fs_kmem_cache_alloc(bio_entry_slab, GFP_NOFS);
	be->bio = bio;
	bio_get(bio);

	अगर (bio_add_page(bio, page, PAGE_SIZE, 0) != PAGE_SIZE)
		f2fs_bug_on(sbi, 1);

	करोwn_ग_लिखो(&io->bio_list_lock);
	list_add_tail(&be->list, &io->bio_list);
	up_ग_लिखो(&io->bio_list_lock);
पूर्ण

अटल व्योम del_bio_entry(काष्ठा bio_entry *be)
अणु
	list_del(&be->list);
	kmem_cache_मुक्त(bio_entry_slab, be);
पूर्ण

अटल पूर्णांक add_ipu_page(काष्ठा f2fs_io_info *fio, काष्ठा bio **bio,
							काष्ठा page *page)
अणु
	काष्ठा f2fs_sb_info *sbi = fio->sbi;
	क्रमागत temp_type temp;
	bool found = false;
	पूर्णांक ret = -EAGAIN;

	क्रम (temp = HOT; temp < NR_TEMP_TYPE && !found; temp++) अणु
		काष्ठा f2fs_bio_info *io = sbi->ग_लिखो_io[DATA] + temp;
		काष्ठा list_head *head = &io->bio_list;
		काष्ठा bio_entry *be;

		करोwn_ग_लिखो(&io->bio_list_lock);
		list_क्रम_each_entry(be, head, list) अणु
			अगर (be->bio != *bio)
				जारी;

			found = true;

			f2fs_bug_on(sbi, !page_is_mergeable(sbi, *bio,
							    *fio->last_block,
							    fio->new_blkaddr));
			अगर (f2fs_crypt_mergeable_bio(*bio,
					fio->page->mapping->host,
					fio->page->index, fio) &&
			    bio_add_page(*bio, page, PAGE_SIZE, 0) ==
					PAGE_SIZE) अणु
				ret = 0;
				अवरोध;
			पूर्ण

			/* page can't be merged पूर्णांकo bio; submit the bio */
			del_bio_entry(be);
			__submit_bio(sbi, *bio, DATA);
			अवरोध;
		पूर्ण
		up_ग_लिखो(&io->bio_list_lock);
	पूर्ण

	अगर (ret) अणु
		bio_put(*bio);
		*bio = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

व्योम f2fs_submit_merged_ipu_ग_लिखो(काष्ठा f2fs_sb_info *sbi,
					काष्ठा bio **bio, काष्ठा page *page)
अणु
	क्रमागत temp_type temp;
	bool found = false;
	काष्ठा bio *target = bio ? *bio : शून्य;

	क्रम (temp = HOT; temp < NR_TEMP_TYPE && !found; temp++) अणु
		काष्ठा f2fs_bio_info *io = sbi->ग_लिखो_io[DATA] + temp;
		काष्ठा list_head *head = &io->bio_list;
		काष्ठा bio_entry *be;

		अगर (list_empty(head))
			जारी;

		करोwn_पढ़ो(&io->bio_list_lock);
		list_क्रम_each_entry(be, head, list) अणु
			अगर (target)
				found = (target == be->bio);
			अन्यथा
				found = __has_merged_page(be->bio, शून्य,
								page, 0);
			अगर (found)
				अवरोध;
		पूर्ण
		up_पढ़ो(&io->bio_list_lock);

		अगर (!found)
			जारी;

		found = false;

		करोwn_ग_लिखो(&io->bio_list_lock);
		list_क्रम_each_entry(be, head, list) अणु
			अगर (target)
				found = (target == be->bio);
			अन्यथा
				found = __has_merged_page(be->bio, शून्य,
								page, 0);
			अगर (found) अणु
				target = be->bio;
				del_bio_entry(be);
				अवरोध;
			पूर्ण
		पूर्ण
		up_ग_लिखो(&io->bio_list_lock);
	पूर्ण

	अगर (found)
		__submit_bio(sbi, target, DATA);
	अगर (bio && *bio) अणु
		bio_put(*bio);
		*bio = शून्य;
	पूर्ण
पूर्ण

पूर्णांक f2fs_merge_page_bio(काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा bio *bio = *fio->bio;
	काष्ठा page *page = fio->encrypted_page ?
			fio->encrypted_page : fio->page;

	अगर (!f2fs_is_valid_blkaddr(fio->sbi, fio->new_blkaddr,
			__is_meta_io(fio) ? META_GENERIC : DATA_GENERIC))
		वापस -EFSCORRUPTED;

	trace_f2fs_submit_page_bio(page, fio);

	अगर (bio && !page_is_mergeable(fio->sbi, bio, *fio->last_block,
						fio->new_blkaddr))
		f2fs_submit_merged_ipu_ग_लिखो(fio->sbi, &bio, शून्य);
alloc_new:
	अगर (!bio) अणु
		bio = __bio_alloc(fio, BIO_MAX_VECS);
		__attach_io_flag(fio);
		f2fs_set_bio_crypt_ctx(bio, fio->page->mapping->host,
				       fio->page->index, fio, GFP_NOIO);
		bio_set_op_attrs(bio, fio->op, fio->op_flags);

		add_bio_entry(fio->sbi, bio, page, fio->temp);
	पूर्ण अन्यथा अणु
		अगर (add_ipu_page(fio, &bio, page))
			जाओ alloc_new;
	पूर्ण

	अगर (fio->io_wbc)
		wbc_account_cgroup_owner(fio->io_wbc, page, PAGE_SIZE);

	inc_page_count(fio->sbi, WB_DATA_TYPE(page));

	*fio->last_block = fio->new_blkaddr;
	*fio->bio = bio;

	वापस 0;
पूर्ण

व्योम f2fs_submit_page_ग_लिखो(काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा f2fs_sb_info *sbi = fio->sbi;
	क्रमागत page_type btype = PAGE_TYPE_OF_BIO(fio->type);
	काष्ठा f2fs_bio_info *io = sbi->ग_लिखो_io[btype] + fio->temp;
	काष्ठा page *bio_page;

	f2fs_bug_on(sbi, is_पढ़ो_io(fio->op));

	करोwn_ग_लिखो(&io->io_rwsem);
next:
	अगर (fio->in_list) अणु
		spin_lock(&io->io_lock);
		अगर (list_empty(&io->io_list)) अणु
			spin_unlock(&io->io_lock);
			जाओ out;
		पूर्ण
		fio = list_first_entry(&io->io_list,
						काष्ठा f2fs_io_info, list);
		list_del(&fio->list);
		spin_unlock(&io->io_lock);
	पूर्ण

	verअगरy_fio_blkaddr(fio);

	अगर (fio->encrypted_page)
		bio_page = fio->encrypted_page;
	अन्यथा अगर (fio->compressed_page)
		bio_page = fio->compressed_page;
	अन्यथा
		bio_page = fio->page;

	/* set submitted = true as a वापस value */
	fio->submitted = true;

	inc_page_count(sbi, WB_DATA_TYPE(bio_page));

	अगर (io->bio &&
	    (!io_is_mergeable(sbi, io->bio, io, fio, io->last_block_in_bio,
			      fio->new_blkaddr) ||
	     !f2fs_crypt_mergeable_bio(io->bio, fio->page->mapping->host,
				       bio_page->index, fio)))
		__submit_merged_bio(io);
alloc_new:
	अगर (io->bio == शून्य) अणु
		अगर (F2FS_IO_ALIGNED(sbi) &&
				(fio->type == DATA || fio->type == NODE) &&
				fio->new_blkaddr & F2FS_IO_SIZE_MASK(sbi)) अणु
			dec_page_count(sbi, WB_DATA_TYPE(bio_page));
			fio->retry = true;
			जाओ skip;
		पूर्ण
		io->bio = __bio_alloc(fio, BIO_MAX_VECS);
		f2fs_set_bio_crypt_ctx(io->bio, fio->page->mapping->host,
				       bio_page->index, fio, GFP_NOIO);
		io->fio = *fio;
	पूर्ण

	अगर (bio_add_page(io->bio, bio_page, PAGE_SIZE, 0) < PAGE_SIZE) अणु
		__submit_merged_bio(io);
		जाओ alloc_new;
	पूर्ण

	अगर (fio->io_wbc)
		wbc_account_cgroup_owner(fio->io_wbc, bio_page, PAGE_SIZE);

	io->last_block_in_bio = fio->new_blkaddr;

	trace_f2fs_submit_page_ग_लिखो(fio->page, fio);
skip:
	अगर (fio->in_list)
		जाओ next;
out:
	अगर (is_sbi_flag_set(sbi, SBI_IS_SHUTDOWN) ||
				!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		__submit_merged_bio(io);
	up_ग_लिखो(&io->io_rwsem);
पूर्ण

अटल काष्ठा bio *f2fs_grab_पढ़ो_bio(काष्ठा inode *inode, block_t blkaddr,
				      अचिन्हित nr_pages, अचिन्हित op_flag,
				      pgoff_t first_idx, bool क्रम_ग_लिखो)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा bio *bio;
	काष्ठा bio_post_पढ़ो_ctx *ctx;
	अचिन्हित पूर्णांक post_पढ़ो_steps = 0;

	bio = bio_alloc_bioset(क्रम_ग_लिखो ? GFP_NOIO : GFP_KERNEL,
			       bio_max_segs(nr_pages), &f2fs_bioset);
	अगर (!bio)
		वापस ERR_PTR(-ENOMEM);

	f2fs_set_bio_crypt_ctx(bio, inode, first_idx, शून्य, GFP_NOFS);

	f2fs_target_device(sbi, blkaddr, bio);
	bio->bi_end_io = f2fs_पढ़ो_end_io;
	bio_set_op_attrs(bio, REQ_OP_READ, op_flag);

	अगर (fscrypt_inode_uses_fs_layer_crypto(inode))
		post_पढ़ो_steps |= STEP_DECRYPT;

	अगर (f2fs_need_verity(inode, first_idx))
		post_पढ़ो_steps |= STEP_VERITY;

	/*
	 * STEP_DECOMPRESS is handled specially, since a compressed file might
	 * contain both compressed and uncompressed clusters.  We'll allocate a
	 * bio_post_पढ़ो_ctx अगर the file is compressed, but the caller is
	 * responsible क्रम enabling STEP_DECOMPRESS अगर it's actually needed.
	 */

	अगर (post_पढ़ो_steps || f2fs_compressed_file(inode)) अणु
		/* Due to the mempool, this never fails. */
		ctx = mempool_alloc(bio_post_पढ़ो_ctx_pool, GFP_NOFS);
		ctx->bio = bio;
		ctx->sbi = sbi;
		ctx->enabled_steps = post_पढ़ो_steps;
		bio->bi_निजी = ctx;
	पूर्ण

	वापस bio;
पूर्ण

/* This can handle encryption stuffs */
अटल पूर्णांक f2fs_submit_page_पढ़ो(काष्ठा inode *inode, काष्ठा page *page,
				 block_t blkaddr, पूर्णांक op_flags, bool क्रम_ग_लिखो)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा bio *bio;

	bio = f2fs_grab_पढ़ो_bio(inode, blkaddr, 1, op_flags,
					page->index, क्रम_ग_लिखो);
	अगर (IS_ERR(bio))
		वापस PTR_ERR(bio);

	/* रुको क्रम GCed page ग_लिखोback via META_MAPPING */
	f2fs_रुको_on_block_ग_लिखोback(inode, blkaddr);

	अगर (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE) अणु
		bio_put(bio);
		वापस -EFAULT;
	पूर्ण
	ClearPageError(page);
	inc_page_count(sbi, F2FS_RD_DATA);
	f2fs_update_iostat(sbi, FS_DATA_READ_IO, F2FS_BLKSIZE);
	__submit_bio(sbi, bio, DATA);
	वापस 0;
पूर्ण

अटल व्योम __set_data_blkaddr(काष्ठा dnode_of_data *dn)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(dn->node_page);
	__le32 *addr_array;
	पूर्णांक base = 0;

	अगर (IS_INODE(dn->node_page) && f2fs_has_extra_attr(dn->inode))
		base = get_extra_isize(dn->inode);

	/* Get physical address of data block */
	addr_array = blkaddr_in_node(rn);
	addr_array[base + dn->ofs_in_node] = cpu_to_le32(dn->data_blkaddr);
पूर्ण

/*
 * Lock ordering क्रम the change of data block address:
 * ->data_page
 *  ->node_page
 *    update block addresses in the node page
 */
व्योम f2fs_set_data_blkaddr(काष्ठा dnode_of_data *dn)
अणु
	f2fs_रुको_on_page_ग_लिखोback(dn->node_page, NODE, true, true);
	__set_data_blkaddr(dn);
	अगर (set_page_dirty(dn->node_page))
		dn->node_changed = true;
पूर्ण

व्योम f2fs_update_data_blkaddr(काष्ठा dnode_of_data *dn, block_t blkaddr)
अणु
	dn->data_blkaddr = blkaddr;
	f2fs_set_data_blkaddr(dn);
	f2fs_update_extent_cache(dn);
पूर्ण

/* dn->ofs_in_node will be वापसed with up-to-date last block poपूर्णांकer */
पूर्णांक f2fs_reserve_new_blocks(काष्ठा dnode_of_data *dn, blkcnt_t count)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	पूर्णांक err;

	अगर (!count)
		वापस 0;

	अगर (unlikely(is_inode_flag_set(dn->inode, FI_NO_ALLOC)))
		वापस -EPERM;
	अगर (unlikely((err = inc_valid_block_count(sbi, dn->inode, &count))))
		वापस err;

	trace_f2fs_reserve_new_blocks(dn->inode, dn->nid,
						dn->ofs_in_node, count);

	f2fs_रुको_on_page_ग_लिखोback(dn->node_page, NODE, true, true);

	क्रम (; count > 0; dn->ofs_in_node++) अणु
		block_t blkaddr = f2fs_data_blkaddr(dn);

		अगर (blkaddr == शून्य_ADDR) अणु
			dn->data_blkaddr = NEW_ADDR;
			__set_data_blkaddr(dn);
			count--;
		पूर्ण
	पूर्ण

	अगर (set_page_dirty(dn->node_page))
		dn->node_changed = true;
	वापस 0;
पूर्ण

/* Should keep dn->ofs_in_node unchanged */
पूर्णांक f2fs_reserve_new_block(काष्ठा dnode_of_data *dn)
अणु
	अचिन्हित पूर्णांक ofs_in_node = dn->ofs_in_node;
	पूर्णांक ret;

	ret = f2fs_reserve_new_blocks(dn, 1);
	dn->ofs_in_node = ofs_in_node;
	वापस ret;
पूर्ण

पूर्णांक f2fs_reserve_block(काष्ठा dnode_of_data *dn, pgoff_t index)
अणु
	bool need_put = dn->inode_page ? false : true;
	पूर्णांक err;

	err = f2fs_get_dnode_of_data(dn, index, ALLOC_NODE);
	अगर (err)
		वापस err;

	अगर (dn->data_blkaddr == शून्य_ADDR)
		err = f2fs_reserve_new_block(dn);
	अगर (err || need_put)
		f2fs_put_dnode(dn);
	वापस err;
पूर्ण

पूर्णांक f2fs_get_block(काष्ठा dnode_of_data *dn, pgoff_t index)
अणु
	काष्ठा extent_info ei = अणु0, 0, 0पूर्ण;
	काष्ठा inode *inode = dn->inode;

	अगर (f2fs_lookup_extent_cache(inode, index, &ei)) अणु
		dn->data_blkaddr = ei.blk + index - ei.fofs;
		वापस 0;
	पूर्ण

	वापस f2fs_reserve_block(dn, index);
पूर्ण

काष्ठा page *f2fs_get_पढ़ो_data_page(काष्ठा inode *inode, pgoff_t index,
						पूर्णांक op_flags, bool क्रम_ग_लिखो)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा dnode_of_data dn;
	काष्ठा page *page;
	काष्ठा extent_info ei = अणु0,0,0पूर्ण;
	पूर्णांक err;

	page = f2fs_grab_cache_page(mapping, index, क्रम_ग_लिखो);
	अगर (!page)
		वापस ERR_PTR(-ENOMEM);

	अगर (f2fs_lookup_extent_cache(inode, index, &ei)) अणु
		dn.data_blkaddr = ei.blk + index - ei.fofs;
		अगर (!f2fs_is_valid_blkaddr(F2FS_I_SB(inode), dn.data_blkaddr,
						DATA_GENERIC_ENHANCE_READ)) अणु
			err = -EFSCORRUPTED;
			जाओ put_err;
		पूर्ण
		जाओ got_it;
	पूर्ण

	set_new_dnode(&dn, inode, शून्य, शून्य, 0);
	err = f2fs_get_dnode_of_data(&dn, index, LOOKUP_NODE);
	अगर (err)
		जाओ put_err;
	f2fs_put_dnode(&dn);

	अगर (unlikely(dn.data_blkaddr == शून्य_ADDR)) अणु
		err = -ENOENT;
		जाओ put_err;
	पूर्ण
	अगर (dn.data_blkaddr != NEW_ADDR &&
			!f2fs_is_valid_blkaddr(F2FS_I_SB(inode),
						dn.data_blkaddr,
						DATA_GENERIC_ENHANCE)) अणु
		err = -EFSCORRUPTED;
		जाओ put_err;
	पूर्ण
got_it:
	अगर (PageUptodate(page)) अणु
		unlock_page(page);
		वापस page;
	पूर्ण

	/*
	 * A new dentry page is allocated but not able to be written, since its
	 * new inode page couldn't be allocated due to -ENOSPC.
	 * In such the हाल, its blkaddr can be reमुख्यed as NEW_ADDR.
	 * see, f2fs_add_link -> f2fs_get_new_data_page ->
	 * f2fs_init_inode_metadata.
	 */
	अगर (dn.data_blkaddr == NEW_ADDR) अणु
		zero_user_segment(page, 0, PAGE_SIZE);
		अगर (!PageUptodate(page))
			SetPageUptodate(page);
		unlock_page(page);
		वापस page;
	पूर्ण

	err = f2fs_submit_page_पढ़ो(inode, page, dn.data_blkaddr,
						op_flags, क्रम_ग_लिखो);
	अगर (err)
		जाओ put_err;
	वापस page;

put_err:
	f2fs_put_page(page, 1);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा page *f2fs_find_data_page(काष्ठा inode *inode, pgoff_t index)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;

	page = find_get_page(mapping, index);
	अगर (page && PageUptodate(page))
		वापस page;
	f2fs_put_page(page, 0);

	page = f2fs_get_पढ़ो_data_page(inode, index, 0, false);
	अगर (IS_ERR(page))
		वापस page;

	अगर (PageUptodate(page))
		वापस page;

	रुको_on_page_locked(page);
	अगर (unlikely(!PageUptodate(page))) अणु
		f2fs_put_page(page, 0);
		वापस ERR_PTR(-EIO);
	पूर्ण
	वापस page;
पूर्ण

/*
 * If it tries to access a hole, वापस an error.
 * Because, the callers, functions in dir.c and GC, should be able to know
 * whether this page exists or not.
 */
काष्ठा page *f2fs_get_lock_data_page(काष्ठा inode *inode, pgoff_t index,
							bool क्रम_ग_लिखो)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;
repeat:
	page = f2fs_get_पढ़ो_data_page(inode, index, 0, क्रम_ग_लिखो);
	अगर (IS_ERR(page))
		वापस page;

	/* रुको क्रम पढ़ो completion */
	lock_page(page);
	अगर (unlikely(page->mapping != mapping)) अणु
		f2fs_put_page(page, 1);
		जाओ repeat;
	पूर्ण
	अगर (unlikely(!PageUptodate(page))) अणु
		f2fs_put_page(page, 1);
		वापस ERR_PTR(-EIO);
	पूर्ण
	वापस page;
पूर्ण

/*
 * Caller ensures that this data page is never allocated.
 * A new zero-filled data page is allocated in the page cache.
 *
 * Also, caller should grab and release a rwsem by calling f2fs_lock_op() and
 * f2fs_unlock_op().
 * Note that, ipage is set only by make_empty_dir, and अगर any error occur,
 * ipage should be released by this function.
 */
काष्ठा page *f2fs_get_new_data_page(काष्ठा inode *inode,
		काष्ठा page *ipage, pgoff_t index, bool new_i_size)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;
	काष्ठा dnode_of_data dn;
	पूर्णांक err;

	page = f2fs_grab_cache_page(mapping, index, true);
	अगर (!page) अणु
		/*
		 * beक्रमe निकासing, we should make sure ipage will be released
		 * अगर any error occur.
		 */
		f2fs_put_page(ipage, 1);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	set_new_dnode(&dn, inode, ipage, शून्य, 0);
	err = f2fs_reserve_block(&dn, index);
	अगर (err) अणु
		f2fs_put_page(page, 1);
		वापस ERR_PTR(err);
	पूर्ण
	अगर (!ipage)
		f2fs_put_dnode(&dn);

	अगर (PageUptodate(page))
		जाओ got_it;

	अगर (dn.data_blkaddr == NEW_ADDR) अणु
		zero_user_segment(page, 0, PAGE_SIZE);
		अगर (!PageUptodate(page))
			SetPageUptodate(page);
	पूर्ण अन्यथा अणु
		f2fs_put_page(page, 1);

		/* अगर ipage exists, blkaddr should be NEW_ADDR */
		f2fs_bug_on(F2FS_I_SB(inode), ipage);
		page = f2fs_get_lock_data_page(inode, index, true);
		अगर (IS_ERR(page))
			वापस page;
	पूर्ण
got_it:
	अगर (new_i_size && i_size_पढ़ो(inode) <
				((loff_t)(index + 1) << PAGE_SHIFT))
		f2fs_i_size_ग_लिखो(inode, ((loff_t)(index + 1) << PAGE_SHIFT));
	वापस page;
पूर्ण

अटल पूर्णांक __allocate_data_block(काष्ठा dnode_of_data *dn, पूर्णांक seg_type)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	काष्ठा f2fs_summary sum;
	काष्ठा node_info ni;
	block_t old_blkaddr;
	blkcnt_t count = 1;
	पूर्णांक err;

	अगर (unlikely(is_inode_flag_set(dn->inode, FI_NO_ALLOC)))
		वापस -EPERM;

	err = f2fs_get_node_info(sbi, dn->nid, &ni);
	अगर (err)
		वापस err;

	dn->data_blkaddr = f2fs_data_blkaddr(dn);
	अगर (dn->data_blkaddr != शून्य_ADDR)
		जाओ alloc;

	अगर (unlikely((err = inc_valid_block_count(sbi, dn->inode, &count))))
		वापस err;

alloc:
	set_summary(&sum, dn->nid, dn->ofs_in_node, ni.version);
	old_blkaddr = dn->data_blkaddr;
	f2fs_allocate_data_block(sbi, शून्य, old_blkaddr, &dn->data_blkaddr,
				&sum, seg_type, शून्य);
	अगर (GET_SEGNO(sbi, old_blkaddr) != शून्य_SEGNO)
		invalidate_mapping_pages(META_MAPPING(sbi),
					old_blkaddr, old_blkaddr);
	f2fs_update_data_blkaddr(dn, dn->data_blkaddr);

	/*
	 * i_size will be updated by direct_IO. Otherwise, we'll get stale
	 * data from unwritten block via dio_पढ़ो.
	 */
	वापस 0;
पूर्ण

पूर्णांक f2fs_pपुनः_स्मृतिate_blocks(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा f2fs_map_blocks map;
	पूर्णांक flag;
	पूर्णांक err = 0;
	bool direct_io = iocb->ki_flags & IOCB_सूचीECT;

	map.m_lblk = F2FS_BLK_ALIGN(iocb->ki_pos);
	map.m_len = F2FS_BYTES_TO_BLK(iocb->ki_pos + iov_iter_count(from));
	अगर (map.m_len > map.m_lblk)
		map.m_len -= map.m_lblk;
	अन्यथा
		map.m_len = 0;

	map.m_next_pgofs = शून्य;
	map.m_next_extent = शून्य;
	map.m_seg_type = NO_CHECK_TYPE;
	map.m_may_create = true;

	अगर (direct_io) अणु
		map.m_seg_type = f2fs_rw_hपूर्णांक_to_seg_type(iocb->ki_hपूर्णांक);
		flag = f2fs_क्रमce_buffered_io(inode, iocb, from) ?
					F2FS_GET_BLOCK_PRE_AIO :
					F2FS_GET_BLOCK_PRE_DIO;
		जाओ map_blocks;
	पूर्ण
	अगर (iocb->ki_pos + iov_iter_count(from) > MAX_INLINE_DATA(inode)) अणु
		err = f2fs_convert_अंतरभूत_inode(inode);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (f2fs_has_अंतरभूत_data(inode))
		वापस err;

	flag = F2FS_GET_BLOCK_PRE_AIO;

map_blocks:
	err = f2fs_map_blocks(inode, &map, 1, flag);
	अगर (map.m_len > 0 && err == -ENOSPC) अणु
		अगर (!direct_io)
			set_inode_flag(inode, FI_NO_PREALLOC);
		err = 0;
	पूर्ण
	वापस err;
पूर्ण

व्योम f2fs_करो_map_lock(काष्ठा f2fs_sb_info *sbi, पूर्णांक flag, bool lock)
अणु
	अगर (flag == F2FS_GET_BLOCK_PRE_AIO) अणु
		अगर (lock)
			करोwn_पढ़ो(&sbi->node_change);
		अन्यथा
			up_पढ़ो(&sbi->node_change);
	पूर्ण अन्यथा अणु
		अगर (lock)
			f2fs_lock_op(sbi);
		अन्यथा
			f2fs_unlock_op(sbi);
	पूर्ण
पूर्ण

/*
 * f2fs_map_blocks() tries to find or build mapping relationship which
 * maps continuous logical blocks to physical blocks, and वापस such
 * info via f2fs_map_blocks काष्ठाure.
 */
पूर्णांक f2fs_map_blocks(काष्ठा inode *inode, काष्ठा f2fs_map_blocks *map,
						पूर्णांक create, पूर्णांक flag)
अणु
	अचिन्हित पूर्णांक maxblocks = map->m_len;
	काष्ठा dnode_of_data dn;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक mode = map->m_may_create ? ALLOC_NODE : LOOKUP_NODE;
	pgoff_t pgofs, end_offset, end;
	पूर्णांक err = 0, ofs = 1;
	अचिन्हित पूर्णांक ofs_in_node, last_ofs_in_node;
	blkcnt_t pपुनः_स्मृति;
	काष्ठा extent_info ei = अणु0,0,0पूर्ण;
	block_t blkaddr;
	अचिन्हित पूर्णांक start_pgofs;

	अगर (!maxblocks)
		वापस 0;

	map->m_len = 0;
	map->m_flags = 0;

	/* it only supports block size == page size */
	pgofs =	(pgoff_t)map->m_lblk;
	end = pgofs + maxblocks;

	अगर (!create && f2fs_lookup_extent_cache(inode, pgofs, &ei)) अणु
		अगर (f2fs_lfs_mode(sbi) && flag == F2FS_GET_BLOCK_DIO &&
							map->m_may_create)
			जाओ next_dnode;

		map->m_pblk = ei.blk + pgofs - ei.fofs;
		map->m_len = min((pgoff_t)maxblocks, ei.fofs + ei.len - pgofs);
		map->m_flags = F2FS_MAP_MAPPED;
		अगर (map->m_next_extent)
			*map->m_next_extent = pgofs + map->m_len;

		/* क्रम hardware encryption, but to aव्योम potential issue in future */
		अगर (flag == F2FS_GET_BLOCK_DIO)
			f2fs_रुको_on_block_ग_लिखोback_range(inode,
						map->m_pblk, map->m_len);
		जाओ out;
	पूर्ण

next_dnode:
	अगर (map->m_may_create)
		f2fs_करो_map_lock(sbi, flag, true);

	/* When पढ़ोing holes, we need its node page */
	set_new_dnode(&dn, inode, शून्य, शून्य, 0);
	err = f2fs_get_dnode_of_data(&dn, pgofs, mode);
	अगर (err) अणु
		अगर (flag == F2FS_GET_BLOCK_BMAP)
			map->m_pblk = 0;
		अगर (err == -ENOENT) अणु
			err = 0;
			अगर (map->m_next_pgofs)
				*map->m_next_pgofs =
					f2fs_get_next_page_offset(&dn, pgofs);
			अगर (map->m_next_extent)
				*map->m_next_extent =
					f2fs_get_next_page_offset(&dn, pgofs);
		पूर्ण
		जाओ unlock_out;
	पूर्ण

	start_pgofs = pgofs;
	pपुनः_स्मृति = 0;
	last_ofs_in_node = ofs_in_node = dn.ofs_in_node;
	end_offset = ADDRS_PER_PAGE(dn.node_page, inode);

next_block:
	blkaddr = f2fs_data_blkaddr(&dn);

	अगर (__is_valid_data_blkaddr(blkaddr) &&
		!f2fs_is_valid_blkaddr(sbi, blkaddr, DATA_GENERIC_ENHANCE)) अणु
		err = -EFSCORRUPTED;
		जाओ sync_out;
	पूर्ण

	अगर (__is_valid_data_blkaddr(blkaddr)) अणु
		/* use out-place-update क्रम driect IO under LFS mode */
		अगर (f2fs_lfs_mode(sbi) && flag == F2FS_GET_BLOCK_DIO &&
							map->m_may_create) अणु
			err = __allocate_data_block(&dn, map->m_seg_type);
			अगर (err)
				जाओ sync_out;
			blkaddr = dn.data_blkaddr;
			set_inode_flag(inode, FI_APPEND_WRITE);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (create) अणु
			अगर (unlikely(f2fs_cp_error(sbi))) अणु
				err = -EIO;
				जाओ sync_out;
			पूर्ण
			अगर (flag == F2FS_GET_BLOCK_PRE_AIO) अणु
				अगर (blkaddr == शून्य_ADDR) अणु
					pपुनः_स्मृति++;
					last_ofs_in_node = dn.ofs_in_node;
				पूर्ण
			पूर्ण अन्यथा अणु
				WARN_ON(flag != F2FS_GET_BLOCK_PRE_DIO &&
					flag != F2FS_GET_BLOCK_DIO);
				err = __allocate_data_block(&dn,
							map->m_seg_type);
				अगर (!err)
					set_inode_flag(inode, FI_APPEND_WRITE);
			पूर्ण
			अगर (err)
				जाओ sync_out;
			map->m_flags |= F2FS_MAP_NEW;
			blkaddr = dn.data_blkaddr;
		पूर्ण अन्यथा अणु
			अगर (flag == F2FS_GET_BLOCK_BMAP) अणु
				map->m_pblk = 0;
				जाओ sync_out;
			पूर्ण
			अगर (flag == F2FS_GET_BLOCK_PRECACHE)
				जाओ sync_out;
			अगर (flag == F2FS_GET_BLOCK_FIEMAP &&
						blkaddr == शून्य_ADDR) अणु
				अगर (map->m_next_pgofs)
					*map->m_next_pgofs = pgofs + 1;
				जाओ sync_out;
			पूर्ण
			अगर (flag != F2FS_GET_BLOCK_FIEMAP) अणु
				/* क्रम defragment हाल */
				अगर (map->m_next_pgofs)
					*map->m_next_pgofs = pgofs + 1;
				जाओ sync_out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (flag == F2FS_GET_BLOCK_PRE_AIO)
		जाओ skip;

	अगर (map->m_len == 0) अणु
		/* pपुनः_स्मृतिated unwritten block should be mapped क्रम fiemap. */
		अगर (blkaddr == NEW_ADDR)
			map->m_flags |= F2FS_MAP_UNWRITTEN;
		map->m_flags |= F2FS_MAP_MAPPED;

		map->m_pblk = blkaddr;
		map->m_len = 1;
	पूर्ण अन्यथा अगर ((map->m_pblk != NEW_ADDR &&
			blkaddr == (map->m_pblk + ofs)) ||
			(map->m_pblk == NEW_ADDR && blkaddr == NEW_ADDR) ||
			flag == F2FS_GET_BLOCK_PRE_DIO) अणु
		ofs++;
		map->m_len++;
	पूर्ण अन्यथा अणु
		जाओ sync_out;
	पूर्ण

skip:
	dn.ofs_in_node++;
	pgofs++;

	/* pपुनः_स्मृतिate blocks in batch क्रम one dnode page */
	अगर (flag == F2FS_GET_BLOCK_PRE_AIO &&
			(pgofs == end || dn.ofs_in_node == end_offset)) अणु

		dn.ofs_in_node = ofs_in_node;
		err = f2fs_reserve_new_blocks(&dn, pपुनः_स्मृति);
		अगर (err)
			जाओ sync_out;

		map->m_len += dn.ofs_in_node - ofs_in_node;
		अगर (pपुनः_स्मृति && dn.ofs_in_node != last_ofs_in_node + 1) अणु
			err = -ENOSPC;
			जाओ sync_out;
		पूर्ण
		dn.ofs_in_node = end_offset;
	पूर्ण

	अगर (pgofs >= end)
		जाओ sync_out;
	अन्यथा अगर (dn.ofs_in_node < end_offset)
		जाओ next_block;

	अगर (flag == F2FS_GET_BLOCK_PRECACHE) अणु
		अगर (map->m_flags & F2FS_MAP_MAPPED) अणु
			अचिन्हित पूर्णांक ofs = start_pgofs - map->m_lblk;

			f2fs_update_extent_cache_range(&dn,
				start_pgofs, map->m_pblk + ofs,
				map->m_len - ofs);
		पूर्ण
	पूर्ण

	f2fs_put_dnode(&dn);

	अगर (map->m_may_create) अणु
		f2fs_करो_map_lock(sbi, flag, false);
		f2fs_balance_fs(sbi, dn.node_changed);
	पूर्ण
	जाओ next_dnode;

sync_out:

	/* क्रम hardware encryption, but to aव्योम potential issue in future */
	अगर (flag == F2FS_GET_BLOCK_DIO && map->m_flags & F2FS_MAP_MAPPED)
		f2fs_रुको_on_block_ग_लिखोback_range(inode,
						map->m_pblk, map->m_len);

	अगर (flag == F2FS_GET_BLOCK_PRECACHE) अणु
		अगर (map->m_flags & F2FS_MAP_MAPPED) अणु
			अचिन्हित पूर्णांक ofs = start_pgofs - map->m_lblk;

			f2fs_update_extent_cache_range(&dn,
				start_pgofs, map->m_pblk + ofs,
				map->m_len - ofs);
		पूर्ण
		अगर (map->m_next_extent)
			*map->m_next_extent = pgofs + 1;
	पूर्ण
	f2fs_put_dnode(&dn);
unlock_out:
	अगर (map->m_may_create) अणु
		f2fs_करो_map_lock(sbi, flag, false);
		f2fs_balance_fs(sbi, dn.node_changed);
	पूर्ण
out:
	trace_f2fs_map_blocks(inode, map, err);
	वापस err;
पूर्ण

bool f2fs_overग_लिखो_io(काष्ठा inode *inode, loff_t pos, माप_प्रकार len)
अणु
	काष्ठा f2fs_map_blocks map;
	block_t last_lblk;
	पूर्णांक err;

	अगर (pos + len > i_size_पढ़ो(inode))
		वापस false;

	map.m_lblk = F2FS_BYTES_TO_BLK(pos);
	map.m_next_pgofs = शून्य;
	map.m_next_extent = शून्य;
	map.m_seg_type = NO_CHECK_TYPE;
	map.m_may_create = false;
	last_lblk = F2FS_BLK_ALIGN(pos + len);

	जबतक (map.m_lblk < last_lblk) अणु
		map.m_len = last_lblk - map.m_lblk;
		err = f2fs_map_blocks(inode, &map, 0, F2FS_GET_BLOCK_DEFAULT);
		अगर (err || map.m_len == 0)
			वापस false;
		map.m_lblk += map.m_len;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत u64 bytes_to_blks(काष्ठा inode *inode, u64 bytes)
अणु
	वापस (bytes >> inode->i_blkbits);
पूर्ण

अटल अंतरभूत u64 blks_to_bytes(काष्ठा inode *inode, u64 blks)
अणु
	वापस (blks << inode->i_blkbits);
पूर्ण

अटल पूर्णांक __get_data_block(काष्ठा inode *inode, sector_t iblock,
			काष्ठा buffer_head *bh, पूर्णांक create, पूर्णांक flag,
			pgoff_t *next_pgofs, पूर्णांक seg_type, bool may_ग_लिखो)
अणु
	काष्ठा f2fs_map_blocks map;
	पूर्णांक err;

	map.m_lblk = iblock;
	map.m_len = bytes_to_blks(inode, bh->b_size);
	map.m_next_pgofs = next_pgofs;
	map.m_next_extent = शून्य;
	map.m_seg_type = seg_type;
	map.m_may_create = may_ग_लिखो;

	err = f2fs_map_blocks(inode, &map, create, flag);
	अगर (!err) अणु
		map_bh(bh, inode->i_sb, map.m_pblk);
		bh->b_state = (bh->b_state & ~F2FS_MAP_FLAGS) | map.m_flags;
		bh->b_size = blks_to_bytes(inode, map.m_len);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक get_data_block_dio_ग_लिखो(काष्ठा inode *inode, sector_t iblock,
			काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	वापस __get_data_block(inode, iblock, bh_result, create,
				F2FS_GET_BLOCK_DIO, शून्य,
				f2fs_rw_hपूर्णांक_to_seg_type(inode->i_ग_लिखो_hपूर्णांक),
				true);
पूर्ण

अटल पूर्णांक get_data_block_dio(काष्ठा inode *inode, sector_t iblock,
			काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	वापस __get_data_block(inode, iblock, bh_result, create,
				F2FS_GET_BLOCK_DIO, शून्य,
				f2fs_rw_hपूर्णांक_to_seg_type(inode->i_ग_लिखो_hपूर्णांक),
				false);
पूर्ण

अटल पूर्णांक f2fs_xattr_fiemap(काष्ठा inode *inode,
				काष्ठा fiemap_extent_info *fieinfo)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा page *page;
	काष्ठा node_info ni;
	__u64 phys = 0, len;
	__u32 flags;
	nid_t xnid = F2FS_I(inode)->i_xattr_nid;
	पूर्णांक err = 0;

	अगर (f2fs_has_अंतरभूत_xattr(inode)) अणु
		पूर्णांक offset;

		page = f2fs_grab_cache_page(NODE_MAPPING(sbi),
						inode->i_ino, false);
		अगर (!page)
			वापस -ENOMEM;

		err = f2fs_get_node_info(sbi, inode->i_ino, &ni);
		अगर (err) अणु
			f2fs_put_page(page, 1);
			वापस err;
		पूर्ण

		phys = blks_to_bytes(inode, ni.blk_addr);
		offset = दुरत्व(काष्ठा f2fs_inode, i_addr) +
					माप(__le32) * (DEF_ADDRS_PER_INODE -
					get_अंतरभूत_xattr_addrs(inode));

		phys += offset;
		len = अंतरभूत_xattr_size(inode);

		f2fs_put_page(page, 1);

		flags = FIEMAP_EXTENT_DATA_INLINE | FIEMAP_EXTENT_NOT_ALIGNED;

		अगर (!xnid)
			flags |= FIEMAP_EXTENT_LAST;

		err = fiemap_fill_next_extent(fieinfo, 0, phys, len, flags);
		trace_f2fs_fiemap(inode, 0, phys, len, flags, err);
		अगर (err || err == 1)
			वापस err;
	पूर्ण

	अगर (xnid) अणु
		page = f2fs_grab_cache_page(NODE_MAPPING(sbi), xnid, false);
		अगर (!page)
			वापस -ENOMEM;

		err = f2fs_get_node_info(sbi, xnid, &ni);
		अगर (err) अणु
			f2fs_put_page(page, 1);
			वापस err;
		पूर्ण

		phys = blks_to_bytes(inode, ni.blk_addr);
		len = inode->i_sb->s_blocksize;

		f2fs_put_page(page, 1);

		flags = FIEMAP_EXTENT_LAST;
	पूर्ण

	अगर (phys) अणु
		err = fiemap_fill_next_extent(fieinfo, 0, phys, len, flags);
		trace_f2fs_fiemap(inode, 0, phys, len, flags, err);
	पूर्ण

	वापस (err < 0 ? err : 0);
पूर्ण

अटल loff_t max_inode_blocks(काष्ठा inode *inode)
अणु
	loff_t result = ADDRS_PER_INODE(inode);
	loff_t leaf_count = ADDRS_PER_BLOCK(inode);

	/* two direct node blocks */
	result += (leaf_count * 2);

	/* two indirect node blocks */
	leaf_count *= NIDS_PER_BLOCK;
	result += (leaf_count * 2);

	/* one द्विगुन indirect node block */
	leaf_count *= NIDS_PER_BLOCK;
	result += leaf_count;

	वापस result;
पूर्ण

पूर्णांक f2fs_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		u64 start, u64 len)
अणु
	काष्ठा f2fs_map_blocks map;
	sector_t start_blk, last_blk;
	pgoff_t next_pgofs;
	u64 logical = 0, phys = 0, size = 0;
	u32 flags = 0;
	पूर्णांक ret = 0;
	bool compr_cluster = false;
	अचिन्हित पूर्णांक cluster_size = F2FS_I(inode)->i_cluster_size;
	loff_t maxbytes;

	अगर (fieinfo->fi_flags & FIEMAP_FLAG_CACHE) अणु
		ret = f2fs_precache_extents(inode);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = fiemap_prep(inode, fieinfo, start, &len, FIEMAP_FLAG_XATTR);
	अगर (ret)
		वापस ret;

	inode_lock(inode);

	maxbytes = max_file_blocks(inode) << F2FS_BLKSIZE_BITS;
	अगर (start > maxbytes) अणु
		ret = -EFBIG;
		जाओ out;
	पूर्ण

	अगर (len > maxbytes || (maxbytes - len) < start)
		len = maxbytes - start;

	अगर (fieinfo->fi_flags & FIEMAP_FLAG_XATTR) अणु
		ret = f2fs_xattr_fiemap(inode, fieinfo);
		जाओ out;
	पूर्ण

	अगर (f2fs_has_अंतरभूत_data(inode) || f2fs_has_अंतरभूत_dentry(inode)) अणु
		ret = f2fs_अंतरभूत_data_fiemap(inode, fieinfo, start, len);
		अगर (ret != -EAGAIN)
			जाओ out;
	पूर्ण

	अगर (bytes_to_blks(inode, len) == 0)
		len = blks_to_bytes(inode, 1);

	start_blk = bytes_to_blks(inode, start);
	last_blk = bytes_to_blks(inode, start + len - 1);

next:
	स_रखो(&map, 0, माप(map));
	map.m_lblk = start_blk;
	map.m_len = bytes_to_blks(inode, len);
	map.m_next_pgofs = &next_pgofs;
	map.m_seg_type = NO_CHECK_TYPE;

	अगर (compr_cluster)
		map.m_len = cluster_size - 1;

	ret = f2fs_map_blocks(inode, &map, 0, F2FS_GET_BLOCK_FIEMAP);
	अगर (ret)
		जाओ out;

	/* HOLE */
	अगर (!(map.m_flags & F2FS_MAP_FLAGS)) अणु
		start_blk = next_pgofs;

		अगर (blks_to_bytes(inode, start_blk) < blks_to_bytes(inode,
						max_inode_blocks(inode)))
			जाओ prep_next;

		flags |= FIEMAP_EXTENT_LAST;
	पूर्ण

	अगर (size) अणु
		flags |= FIEMAP_EXTENT_MERGED;
		अगर (IS_ENCRYPTED(inode))
			flags |= FIEMAP_EXTENT_DATA_ENCRYPTED;

		ret = fiemap_fill_next_extent(fieinfo, logical,
				phys, size, flags);
		trace_f2fs_fiemap(inode, logical, phys, size, flags, ret);
		अगर (ret)
			जाओ out;
		size = 0;
	पूर्ण

	अगर (start_blk > last_blk)
		जाओ out;

	अगर (compr_cluster) अणु
		compr_cluster = false;


		logical = blks_to_bytes(inode, start_blk - 1);
		phys = blks_to_bytes(inode, map.m_pblk);
		size = blks_to_bytes(inode, cluster_size);

		flags |= FIEMAP_EXTENT_ENCODED;

		start_blk += cluster_size - 1;

		अगर (start_blk > last_blk)
			जाओ out;

		जाओ prep_next;
	पूर्ण

	अगर (map.m_pblk == COMPRESS_ADDR) अणु
		compr_cluster = true;
		start_blk++;
		जाओ prep_next;
	पूर्ण

	logical = blks_to_bytes(inode, start_blk);
	phys = blks_to_bytes(inode, map.m_pblk);
	size = blks_to_bytes(inode, map.m_len);
	flags = 0;
	अगर (map.m_flags & F2FS_MAP_UNWRITTEN)
		flags = FIEMAP_EXTENT_UNWRITTEN;

	start_blk += bytes_to_blks(inode, size);

prep_next:
	cond_resched();
	अगर (fatal_संकेत_pending(current))
		ret = -EINTR;
	अन्यथा
		जाओ next;
out:
	अगर (ret == 1)
		ret = 0;

	inode_unlock(inode);
	वापस ret;
पूर्ण

अटल अंतरभूत loff_t f2fs_पढ़ोpage_limit(काष्ठा inode *inode)
अणु
	अगर (IS_ENABLED(CONFIG_FS_VERITY) &&
	    (IS_VERITY(inode) || f2fs_verity_in_progress(inode)))
		वापस inode->i_sb->s_maxbytes;

	वापस i_size_पढ़ो(inode);
पूर्ण

अटल पूर्णांक f2fs_पढ़ो_single_page(काष्ठा inode *inode, काष्ठा page *page,
					अचिन्हित nr_pages,
					काष्ठा f2fs_map_blocks *map,
					काष्ठा bio **bio_ret,
					sector_t *last_block_in_bio,
					bool is_पढ़ोahead)
अणु
	काष्ठा bio *bio = *bio_ret;
	स्थिर अचिन्हित blocksize = blks_to_bytes(inode, 1);
	sector_t block_in_file;
	sector_t last_block;
	sector_t last_block_in_file;
	sector_t block_nr;
	पूर्णांक ret = 0;

	block_in_file = (sector_t)page_index(page);
	last_block = block_in_file + nr_pages;
	last_block_in_file = bytes_to_blks(inode,
			f2fs_पढ़ोpage_limit(inode) + blocksize - 1);
	अगर (last_block > last_block_in_file)
		last_block = last_block_in_file;

	/* just zeroing out page which is beyond खातापूर्ण */
	अगर (block_in_file >= last_block)
		जाओ zero_out;
	/*
	 * Map blocks using the previous result first.
	 */
	अगर ((map->m_flags & F2FS_MAP_MAPPED) &&
			block_in_file > map->m_lblk &&
			block_in_file < (map->m_lblk + map->m_len))
		जाओ got_it;

	/*
	 * Then करो more f2fs_map_blocks() calls until we are
	 * करोne with this page.
	 */
	map->m_lblk = block_in_file;
	map->m_len = last_block - block_in_file;

	ret = f2fs_map_blocks(inode, map, 0, F2FS_GET_BLOCK_DEFAULT);
	अगर (ret)
		जाओ out;
got_it:
	अगर ((map->m_flags & F2FS_MAP_MAPPED)) अणु
		block_nr = map->m_pblk + block_in_file - map->m_lblk;
		SetPageMappedToDisk(page);

		अगर (!PageUptodate(page) && (!PageSwapCache(page) &&
					!cleancache_get_page(page))) अणु
			SetPageUptodate(page);
			जाओ confused;
		पूर्ण

		अगर (!f2fs_is_valid_blkaddr(F2FS_I_SB(inode), block_nr,
						DATA_GENERIC_ENHANCE_READ)) अणु
			ret = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
zero_out:
		zero_user_segment(page, 0, PAGE_SIZE);
		अगर (f2fs_need_verity(inode, page->index) &&
		    !fsverity_verअगरy_page(page)) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण
		अगर (!PageUptodate(page))
			SetPageUptodate(page);
		unlock_page(page);
		जाओ out;
	पूर्ण

	/*
	 * This page will go to BIO.  Do we need to send this
	 * BIO off first?
	 */
	अगर (bio && (!page_is_mergeable(F2FS_I_SB(inode), bio,
				       *last_block_in_bio, block_nr) ||
		    !f2fs_crypt_mergeable_bio(bio, inode, page->index, शून्य))) अणु
submit_and_पुनः_स्मृति:
		__submit_bio(F2FS_I_SB(inode), bio, DATA);
		bio = शून्य;
	पूर्ण
	अगर (bio == शून्य) अणु
		bio = f2fs_grab_पढ़ो_bio(inode, block_nr, nr_pages,
				is_पढ़ोahead ? REQ_RAHEAD : 0, page->index,
				false);
		अगर (IS_ERR(bio)) अणु
			ret = PTR_ERR(bio);
			bio = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * If the page is under ग_लिखोback, we need to रुको क्रम
	 * its completion to see the correct decrypted data.
	 */
	f2fs_रुको_on_block_ग_लिखोback(inode, block_nr);

	अगर (bio_add_page(bio, page, blocksize, 0) < blocksize)
		जाओ submit_and_पुनः_स्मृति;

	inc_page_count(F2FS_I_SB(inode), F2FS_RD_DATA);
	f2fs_update_iostat(F2FS_I_SB(inode), FS_DATA_READ_IO, F2FS_BLKSIZE);
	ClearPageError(page);
	*last_block_in_bio = block_nr;
	जाओ out;
confused:
	अगर (bio) अणु
		__submit_bio(F2FS_I_SB(inode), bio, DATA);
		bio = शून्य;
	पूर्ण
	unlock_page(page);
out:
	*bio_ret = bio;
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
पूर्णांक f2fs_पढ़ो_multi_pages(काष्ठा compress_ctx *cc, काष्ठा bio **bio_ret,
				अचिन्हित nr_pages, sector_t *last_block_in_bio,
				bool is_पढ़ोahead, bool क्रम_ग_लिखो)
अणु
	काष्ठा dnode_of_data dn;
	काष्ठा inode *inode = cc->inode;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा bio *bio = *bio_ret;
	अचिन्हित पूर्णांक start_idx = cc->cluster_idx << cc->log_cluster_size;
	sector_t last_block_in_file;
	स्थिर अचिन्हित blocksize = blks_to_bytes(inode, 1);
	काष्ठा decompress_io_ctx *dic = शून्य;
	पूर्णांक i;
	पूर्णांक ret = 0;

	f2fs_bug_on(sbi, f2fs_cluster_is_empty(cc));

	last_block_in_file = bytes_to_blks(inode,
			f2fs_पढ़ोpage_limit(inode) + blocksize - 1);

	/* get rid of pages beyond खातापूर्ण */
	क्रम (i = 0; i < cc->cluster_size; i++) अणु
		काष्ठा page *page = cc->rpages[i];

		अगर (!page)
			जारी;
		अगर ((sector_t)page->index >= last_block_in_file) अणु
			zero_user_segment(page, 0, PAGE_SIZE);
			अगर (!PageUptodate(page))
				SetPageUptodate(page);
		पूर्ण अन्यथा अगर (!PageUptodate(page)) अणु
			जारी;
		पूर्ण
		unlock_page(page);
		cc->rpages[i] = शून्य;
		cc->nr_rpages--;
	पूर्ण

	/* we are करोne since all pages are beyond खातापूर्ण */
	अगर (f2fs_cluster_is_empty(cc))
		जाओ out;

	set_new_dnode(&dn, inode, शून्य, शून्य, 0);
	ret = f2fs_get_dnode_of_data(&dn, start_idx, LOOKUP_NODE);
	अगर (ret)
		जाओ out;

	f2fs_bug_on(sbi, dn.data_blkaddr != COMPRESS_ADDR);

	क्रम (i = 1; i < cc->cluster_size; i++) अणु
		block_t blkaddr;

		blkaddr = data_blkaddr(dn.inode, dn.node_page,
						dn.ofs_in_node + i);

		अगर (!__is_valid_data_blkaddr(blkaddr))
			अवरोध;

		अगर (!f2fs_is_valid_blkaddr(sbi, blkaddr, DATA_GENERIC)) अणु
			ret = -EFAULT;
			जाओ out_put_dnode;
		पूर्ण
		cc->nr_cpages++;
	पूर्ण

	/* nothing to decompress */
	अगर (cc->nr_cpages == 0) अणु
		ret = 0;
		जाओ out_put_dnode;
	पूर्ण

	dic = f2fs_alloc_dic(cc);
	अगर (IS_ERR(dic)) अणु
		ret = PTR_ERR(dic);
		जाओ out_put_dnode;
	पूर्ण

	क्रम (i = 0; i < dic->nr_cpages; i++) अणु
		काष्ठा page *page = dic->cpages[i];
		block_t blkaddr;
		काष्ठा bio_post_पढ़ो_ctx *ctx;

		blkaddr = data_blkaddr(dn.inode, dn.node_page,
						dn.ofs_in_node + i + 1);

		अगर (bio && (!page_is_mergeable(sbi, bio,
					*last_block_in_bio, blkaddr) ||
		    !f2fs_crypt_mergeable_bio(bio, inode, page->index, शून्य))) अणु
submit_and_पुनः_स्मृति:
			__submit_bio(sbi, bio, DATA);
			bio = शून्य;
		पूर्ण

		अगर (!bio) अणु
			bio = f2fs_grab_पढ़ो_bio(inode, blkaddr, nr_pages,
					is_पढ़ोahead ? REQ_RAHEAD : 0,
					page->index, क्रम_ग_लिखो);
			अगर (IS_ERR(bio)) अणु
				ret = PTR_ERR(bio);
				f2fs_decompress_end_io(dic, ret);
				f2fs_put_dnode(&dn);
				*bio_ret = शून्य;
				वापस ret;
			पूर्ण
		पूर्ण

		f2fs_रुको_on_block_ग_लिखोback(inode, blkaddr);

		अगर (bio_add_page(bio, page, blocksize, 0) < blocksize)
			जाओ submit_and_पुनः_स्मृति;

		ctx = bio->bi_निजी;
		ctx->enabled_steps |= STEP_DECOMPRESS;
		refcount_inc(&dic->refcnt);

		inc_page_count(sbi, F2FS_RD_DATA);
		f2fs_update_iostat(sbi, FS_DATA_READ_IO, F2FS_BLKSIZE);
		f2fs_update_iostat(sbi, FS_CDATA_READ_IO, F2FS_BLKSIZE);
		ClearPageError(page);
		*last_block_in_bio = blkaddr;
	पूर्ण

	f2fs_put_dnode(&dn);

	*bio_ret = bio;
	वापस 0;

out_put_dnode:
	f2fs_put_dnode(&dn);
out:
	क्रम (i = 0; i < cc->cluster_size; i++) अणु
		अगर (cc->rpages[i]) अणु
			ClearPageUptodate(cc->rpages[i]);
			ClearPageError(cc->rpages[i]);
			unlock_page(cc->rpages[i]);
		पूर्ण
	पूर्ण
	*bio_ret = bio;
	वापस ret;
पूर्ण
#पूर्ण_अगर

/*
 * This function was originally taken from fs/mpage.c, and customized क्रम f2fs.
 * Major change was from block_size == page_size in f2fs by शेष.
 */
अटल पूर्णांक f2fs_mpage_पढ़ोpages(काष्ठा inode *inode,
		काष्ठा पढ़ोahead_control *rac, काष्ठा page *page)
अणु
	काष्ठा bio *bio = शून्य;
	sector_t last_block_in_bio = 0;
	काष्ठा f2fs_map_blocks map;
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	काष्ठा compress_ctx cc = अणु
		.inode = inode,
		.log_cluster_size = F2FS_I(inode)->i_log_cluster_size,
		.cluster_size = F2FS_I(inode)->i_cluster_size,
		.cluster_idx = शून्य_CLUSTER,
		.rpages = शून्य,
		.cpages = शून्य,
		.nr_rpages = 0,
		.nr_cpages = 0,
	पूर्ण;
#पूर्ण_अगर
	अचिन्हित nr_pages = rac ? पढ़ोahead_count(rac) : 1;
	अचिन्हित max_nr_pages = nr_pages;
	पूर्णांक ret = 0;

	map.m_pblk = 0;
	map.m_lblk = 0;
	map.m_len = 0;
	map.m_flags = 0;
	map.m_next_pgofs = शून्य;
	map.m_next_extent = शून्य;
	map.m_seg_type = NO_CHECK_TYPE;
	map.m_may_create = false;

	क्रम (; nr_pages; nr_pages--) अणु
		अगर (rac) अणु
			page = पढ़ोahead_page(rac);
			prefetchw(&page->flags);
		पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
		अगर (f2fs_compressed_file(inode)) अणु
			/* there are reमुख्यed comressed pages, submit them */
			अगर (!f2fs_cluster_can_merge_page(&cc, page->index)) अणु
				ret = f2fs_पढ़ो_multi_pages(&cc, &bio,
							max_nr_pages,
							&last_block_in_bio,
							rac != शून्य, false);
				f2fs_destroy_compress_ctx(&cc, false);
				अगर (ret)
					जाओ set_error_page;
			पूर्ण
			ret = f2fs_is_compressed_cluster(inode, page->index);
			अगर (ret < 0)
				जाओ set_error_page;
			अन्यथा अगर (!ret)
				जाओ पढ़ो_single_page;

			ret = f2fs_init_compress_ctx(&cc);
			अगर (ret)
				जाओ set_error_page;

			f2fs_compress_ctx_add_page(&cc, page);

			जाओ next_page;
		पूर्ण
पढ़ो_single_page:
#पूर्ण_अगर

		ret = f2fs_पढ़ो_single_page(inode, page, max_nr_pages, &map,
					&bio, &last_block_in_bio, rac);
		अगर (ret) अणु
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
set_error_page:
#पूर्ण_अगर
			SetPageError(page);
			zero_user_segment(page, 0, PAGE_SIZE);
			unlock_page(page);
		पूर्ण
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
next_page:
#पूर्ण_अगर
		अगर (rac)
			put_page(page);

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
		अगर (f2fs_compressed_file(inode)) अणु
			/* last page */
			अगर (nr_pages == 1 && !f2fs_cluster_is_empty(&cc)) अणु
				ret = f2fs_पढ़ो_multi_pages(&cc, &bio,
							max_nr_pages,
							&last_block_in_bio,
							rac != शून्य, false);
				f2fs_destroy_compress_ctx(&cc, false);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	अगर (bio)
		__submit_bio(F2FS_I_SB(inode), bio, DATA);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_पढ़ो_data_page(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page_file_mapping(page)->host;
	पूर्णांक ret = -EAGAIN;

	trace_f2fs_पढ़ोpage(page, DATA);

	अगर (!f2fs_is_compress_backend_पढ़ोy(inode)) अणु
		unlock_page(page);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* If the file has अंतरभूत data, try to पढ़ो it directly */
	अगर (f2fs_has_अंतरभूत_data(inode))
		ret = f2fs_पढ़ो_अंतरभूत_data(inode, page);
	अगर (ret == -EAGAIN)
		ret = f2fs_mpage_पढ़ोpages(inode, शून्य, page);
	वापस ret;
पूर्ण

अटल व्योम f2fs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	काष्ठा inode *inode = rac->mapping->host;

	trace_f2fs_पढ़ोpages(inode, पढ़ोahead_index(rac), पढ़ोahead_count(rac));

	अगर (!f2fs_is_compress_backend_पढ़ोy(inode))
		वापस;

	/* If the file has अंतरभूत data, skip पढ़ोpages */
	अगर (f2fs_has_अंतरभूत_data(inode))
		वापस;

	f2fs_mpage_पढ़ोpages(inode, rac, शून्य);
पूर्ण

पूर्णांक f2fs_encrypt_one_page(काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा inode *inode = fio->page->mapping->host;
	काष्ठा page *mpage, *page;
	gfp_t gfp_flags = GFP_NOFS;

	अगर (!f2fs_encrypted_file(inode))
		वापस 0;

	page = fio->compressed_page ? fio->compressed_page : fio->page;

	/* रुको क्रम GCed page ग_लिखोback via META_MAPPING */
	f2fs_रुको_on_block_ग_लिखोback(inode, fio->old_blkaddr);

	अगर (fscrypt_inode_uses_अंतरभूत_crypto(inode))
		वापस 0;

retry_encrypt:
	fio->encrypted_page = fscrypt_encrypt_pagecache_blocks(page,
					PAGE_SIZE, 0, gfp_flags);
	अगर (IS_ERR(fio->encrypted_page)) अणु
		/* flush pending IOs and रुको क्रम a जबतक in the ENOMEM हाल */
		अगर (PTR_ERR(fio->encrypted_page) == -ENOMEM) अणु
			f2fs_flush_merged_ग_लिखोs(fio->sbi);
			congestion_रुको(BLK_RW_ASYNC, DEFAULT_IO_TIMEOUT);
			gfp_flags |= __GFP_NOFAIL;
			जाओ retry_encrypt;
		पूर्ण
		वापस PTR_ERR(fio->encrypted_page);
	पूर्ण

	mpage = find_lock_page(META_MAPPING(fio->sbi), fio->old_blkaddr);
	अगर (mpage) अणु
		अगर (PageUptodate(mpage))
			स_नकल(page_address(mpage),
				page_address(fio->encrypted_page), PAGE_SIZE);
		f2fs_put_page(mpage, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत bool check_inplace_update_policy(काष्ठा inode *inode,
				काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	अचिन्हित पूर्णांक policy = SM_I(sbi)->ipu_policy;

	अगर (policy & (0x1 << F2FS_IPU_FORCE))
		वापस true;
	अगर (policy & (0x1 << F2FS_IPU_SSR) && f2fs_need_SSR(sbi))
		वापस true;
	अगर (policy & (0x1 << F2FS_IPU_UTIL) &&
			utilization(sbi) > SM_I(sbi)->min_ipu_util)
		वापस true;
	अगर (policy & (0x1 << F2FS_IPU_SSR_UTIL) && f2fs_need_SSR(sbi) &&
			utilization(sbi) > SM_I(sbi)->min_ipu_util)
		वापस true;

	/*
	 * IPU क्रम reग_लिखो async pages
	 */
	अगर (policy & (0x1 << F2FS_IPU_ASYNC) &&
			fio && fio->op == REQ_OP_WRITE &&
			!(fio->op_flags & REQ_SYNC) &&
			!IS_ENCRYPTED(inode))
		वापस true;

	/* this is only set during fdatasync */
	अगर (policy & (0x1 << F2FS_IPU_FSYNC) &&
			is_inode_flag_set(inode, FI_NEED_IPU))
		वापस true;

	अगर (unlikely(fio && is_sbi_flag_set(sbi, SBI_CP_DISABLED) &&
			!f2fs_is_checkpoपूर्णांकed_data(sbi, fio->old_blkaddr)))
		वापस true;

	वापस false;
पूर्ण

bool f2fs_should_update_inplace(काष्ठा inode *inode, काष्ठा f2fs_io_info *fio)
अणु
	अगर (f2fs_is_pinned_file(inode))
		वापस true;

	/* अगर this is cold file, we should overग_लिखो to aव्योम fragmentation */
	अगर (file_is_cold(inode))
		वापस true;

	वापस check_inplace_update_policy(inode, fio);
पूर्ण

bool f2fs_should_update_outplace(काष्ठा inode *inode, काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

	अगर (f2fs_lfs_mode(sbi))
		वापस true;
	अगर (S_ISसूची(inode->i_mode))
		वापस true;
	अगर (IS_NOQUOTA(inode))
		वापस true;
	अगर (f2fs_is_atomic_file(inode))
		वापस true;
	अगर (fio) अणु
		अगर (is_cold_data(fio->page))
			वापस true;
		अगर (IS_ATOMIC_WRITTEN_PAGE(fio->page))
			वापस true;
		अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED) &&
			f2fs_is_checkpoपूर्णांकed_data(sbi, fio->old_blkaddr)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool need_inplace_update(काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा inode *inode = fio->page->mapping->host;

	अगर (f2fs_should_update_outplace(inode, fio))
		वापस false;

	वापस f2fs_should_update_inplace(inode, fio);
पूर्ण

पूर्णांक f2fs_करो_ग_लिखो_data_page(काष्ठा f2fs_io_info *fio)
अणु
	काष्ठा page *page = fio->page;
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा dnode_of_data dn;
	काष्ठा extent_info ei = अणु0,0,0पूर्ण;
	काष्ठा node_info ni;
	bool ipu_क्रमce = false;
	पूर्णांक err = 0;

	set_new_dnode(&dn, inode, शून्य, शून्य, 0);
	अगर (need_inplace_update(fio) &&
			f2fs_lookup_extent_cache(inode, page->index, &ei)) अणु
		fio->old_blkaddr = ei.blk + page->index - ei.fofs;

		अगर (!f2fs_is_valid_blkaddr(fio->sbi, fio->old_blkaddr,
						DATA_GENERIC_ENHANCE))
			वापस -EFSCORRUPTED;

		ipu_क्रमce = true;
		fio->need_lock = LOCK_DONE;
		जाओ got_it;
	पूर्ण

	/* Deadlock due to between page->lock and f2fs_lock_op */
	अगर (fio->need_lock == LOCK_REQ && !f2fs_trylock_op(fio->sbi))
		वापस -EAGAIN;

	err = f2fs_get_dnode_of_data(&dn, page->index, LOOKUP_NODE);
	अगर (err)
		जाओ out;

	fio->old_blkaddr = dn.data_blkaddr;

	/* This page is alपढ़ोy truncated */
	अगर (fio->old_blkaddr == शून्य_ADDR) अणु
		ClearPageUptodate(page);
		clear_cold_data(page);
		जाओ out_ग_लिखोpage;
	पूर्ण
got_it:
	अगर (__is_valid_data_blkaddr(fio->old_blkaddr) &&
		!f2fs_is_valid_blkaddr(fio->sbi, fio->old_blkaddr,
						DATA_GENERIC_ENHANCE)) अणु
		err = -EFSCORRUPTED;
		जाओ out_ग_लिखोpage;
	पूर्ण
	/*
	 * If current allocation needs SSR,
	 * it had better in-place ग_लिखोs क्रम updated data.
	 */
	अगर (ipu_क्रमce ||
		(__is_valid_data_blkaddr(fio->old_blkaddr) &&
					need_inplace_update(fio))) अणु
		err = f2fs_encrypt_one_page(fio);
		अगर (err)
			जाओ out_ग_लिखोpage;

		set_page_ग_लिखोback(page);
		ClearPageError(page);
		f2fs_put_dnode(&dn);
		अगर (fio->need_lock == LOCK_REQ)
			f2fs_unlock_op(fio->sbi);
		err = f2fs_inplace_ग_लिखो_data(fio);
		अगर (err) अणु
			अगर (fscrypt_inode_uses_fs_layer_crypto(inode))
				fscrypt_finalize_bounce_page(&fio->encrypted_page);
			अगर (PageWriteback(page))
				end_page_ग_लिखोback(page);
		पूर्ण अन्यथा अणु
			set_inode_flag(inode, FI_UPDATE_WRITE);
		पूर्ण
		trace_f2fs_करो_ग_लिखो_data_page(fio->page, IPU);
		वापस err;
	पूर्ण

	अगर (fio->need_lock == LOCK_RETRY) अणु
		अगर (!f2fs_trylock_op(fio->sbi)) अणु
			err = -EAGAIN;
			जाओ out_ग_लिखोpage;
		पूर्ण
		fio->need_lock = LOCK_REQ;
	पूर्ण

	err = f2fs_get_node_info(fio->sbi, dn.nid, &ni);
	अगर (err)
		जाओ out_ग_लिखोpage;

	fio->version = ni.version;

	err = f2fs_encrypt_one_page(fio);
	अगर (err)
		जाओ out_ग_लिखोpage;

	set_page_ग_लिखोback(page);
	ClearPageError(page);

	अगर (fio->compr_blocks && fio->old_blkaddr == COMPRESS_ADDR)
		f2fs_i_compr_blocks_update(inode, fio->compr_blocks - 1, false);

	/* LFS mode ग_लिखो path */
	f2fs_outplace_ग_लिखो_data(&dn, fio);
	trace_f2fs_करो_ग_लिखो_data_page(page, OPU);
	set_inode_flag(inode, FI_APPEND_WRITE);
	अगर (page->index == 0)
		set_inode_flag(inode, FI_FIRST_BLOCK_WRITTEN);
out_ग_लिखोpage:
	f2fs_put_dnode(&dn);
out:
	अगर (fio->need_lock == LOCK_REQ)
		f2fs_unlock_op(fio->sbi);
	वापस err;
पूर्ण

पूर्णांक f2fs_ग_लिखो_single_data_page(काष्ठा page *page, पूर्णांक *submitted,
				काष्ठा bio **bio,
				sector_t *last_block,
				काष्ठा ग_लिखोback_control *wbc,
				क्रमागत iostat_type io_type,
				पूर्णांक compr_blocks,
				bool allow_balance)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	loff_t i_size = i_size_पढ़ो(inode);
	स्थिर pgoff_t end_index = ((अचिन्हित दीर्घ दीर्घ)i_size)
							>> PAGE_SHIFT;
	loff_t psize = (loff_t)(page->index + 1) << PAGE_SHIFT;
	अचिन्हित offset = 0;
	bool need_balance_fs = false;
	पूर्णांक err = 0;
	काष्ठा f2fs_io_info fio = अणु
		.sbi = sbi,
		.ino = inode->i_ino,
		.type = DATA,
		.op = REQ_OP_WRITE,
		.op_flags = wbc_to_ग_लिखो_flags(wbc),
		.old_blkaddr = शून्य_ADDR,
		.page = page,
		.encrypted_page = शून्य,
		.submitted = false,
		.compr_blocks = compr_blocks,
		.need_lock = LOCK_RETRY,
		.io_type = io_type,
		.io_wbc = wbc,
		.bio = bio,
		.last_block = last_block,
	पूर्ण;

	trace_f2fs_ग_लिखोpage(page, DATA);

	/* we should bypass data pages to proceed the kworkder jobs */
	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		mapping_set_error(page->mapping, -EIO);
		/*
		 * करोn't drop any dirty dentry pages क्रम keeping lastest
		 * directory काष्ठाure.
		 */
		अगर (S_ISसूची(inode->i_mode))
			जाओ redirty_out;
		जाओ out;
	पूर्ण

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		जाओ redirty_out;

	अगर (page->index < end_index ||
			f2fs_verity_in_progress(inode) ||
			compr_blocks)
		जाओ ग_लिखो;

	/*
	 * If the offset is out-of-range of file size,
	 * this page करोes not have to be written to disk.
	 */
	offset = i_size & (PAGE_SIZE - 1);
	अगर ((page->index >= end_index + 1) || !offset)
		जाओ out;

	zero_user_segment(page, offset, PAGE_SIZE);
ग_लिखो:
	अगर (f2fs_is_drop_cache(inode))
		जाओ out;
	/* we should not ग_लिखो 0'th page having journal header */
	अगर (f2fs_is_अस्थिर_file(inode) && (!page->index ||
			(!wbc->क्रम_reclaim &&
			f2fs_available_मुक्त_memory(sbi, BASE_CHECK))))
		जाओ redirty_out;

	/* Dentry/quota blocks are controlled by checkpoपूर्णांक */
	अगर (S_ISसूची(inode->i_mode) || IS_NOQUOTA(inode)) अणु
		/*
		 * We need to रुको क्रम node_ग_लिखो to aव्योम block allocation during
		 * checkpoपूर्णांक. This can only happen to quota ग_लिखोs which can cause
		 * the below discard race condition.
		 */
		अगर (IS_NOQUOTA(inode))
			करोwn_पढ़ो(&sbi->node_ग_लिखो);

		fio.need_lock = LOCK_DONE;
		err = f2fs_करो_ग_लिखो_data_page(&fio);

		अगर (IS_NOQUOTA(inode))
			up_पढ़ो(&sbi->node_ग_लिखो);

		जाओ करोne;
	पूर्ण

	अगर (!wbc->क्रम_reclaim)
		need_balance_fs = true;
	अन्यथा अगर (has_not_enough_मुक्त_secs(sbi, 0, 0))
		जाओ redirty_out;
	अन्यथा
		set_inode_flag(inode, FI_HOT_DATA);

	err = -EAGAIN;
	अगर (f2fs_has_अंतरभूत_data(inode)) अणु
		err = f2fs_ग_लिखो_अंतरभूत_data(inode, page);
		अगर (!err)
			जाओ out;
	पूर्ण

	अगर (err == -EAGAIN) अणु
		err = f2fs_करो_ग_लिखो_data_page(&fio);
		अगर (err == -EAGAIN) अणु
			fio.need_lock = LOCK_REQ;
			err = f2fs_करो_ग_लिखो_data_page(&fio);
		पूर्ण
	पूर्ण

	अगर (err) अणु
		file_set_keep_isize(inode);
	पूर्ण अन्यथा अणु
		spin_lock(&F2FS_I(inode)->i_size_lock);
		अगर (F2FS_I(inode)->last_disk_size < psize)
			F2FS_I(inode)->last_disk_size = psize;
		spin_unlock(&F2FS_I(inode)->i_size_lock);
	पूर्ण

करोne:
	अगर (err && err != -ENOENT)
		जाओ redirty_out;

out:
	inode_dec_dirty_pages(inode);
	अगर (err) अणु
		ClearPageUptodate(page);
		clear_cold_data(page);
	पूर्ण

	अगर (wbc->क्रम_reclaim) अणु
		f2fs_submit_merged_ग_लिखो_cond(sbi, शून्य, page, 0, DATA);
		clear_inode_flag(inode, FI_HOT_DATA);
		f2fs_हटाओ_dirty_inode(inode);
		submitted = शून्य;
	पूर्ण
	unlock_page(page);
	अगर (!S_ISसूची(inode->i_mode) && !IS_NOQUOTA(inode) &&
			!F2FS_I(inode)->cp_task && allow_balance)
		f2fs_balance_fs(sbi, need_balance_fs);

	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		f2fs_submit_merged_ग_लिखो(sbi, DATA);
		f2fs_submit_merged_ipu_ग_लिखो(sbi, bio, शून्य);
		submitted = शून्य;
	पूर्ण

	अगर (submitted)
		*submitted = fio.submitted ? 1 : 0;

	वापस 0;

redirty_out:
	redirty_page_क्रम_ग_लिखोpage(wbc, page);
	/*
	 * pageout() in MM traslates EAGAIN, so calls handle_ग_लिखो_error()
	 * -> mapping_set_error() -> set_bit(AS_EIO, ...).
	 * file_ग_लिखो_and_रुको_range() will see EIO error, which is critical
	 * to वापस value of fsync() followed by atomic_ग_लिखो failure to user.
	 */
	अगर (!err || wbc->क्रम_reclaim)
		वापस AOP_WRITEPAGE_ACTIVATE;
	unlock_page(page);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_ग_लिखो_data_page(काष्ठा page *page,
					काष्ठा ग_लिखोback_control *wbc)
अणु
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	काष्ठा inode *inode = page->mapping->host;

	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		जाओ out;

	अगर (f2fs_compressed_file(inode)) अणु
		अगर (f2fs_is_compressed_cluster(inode, page->index)) अणु
			redirty_page_क्रम_ग_लिखोpage(wbc, page);
			वापस AOP_WRITEPAGE_ACTIVATE;
		पूर्ण
	पूर्ण
out:
#पूर्ण_अगर

	वापस f2fs_ग_लिखो_single_data_page(page, शून्य, शून्य, शून्य,
						wbc, FS_DATA_IO, 0, true);
पूर्ण

/*
 * This function was copied from ग_लिखो_cche_pages from mm/page-ग_लिखोback.c.
 * The major change is making ग_लिखो step of cold data page separately from
 * warm/hot data page.
 */
अटल पूर्णांक f2fs_ग_लिखो_cache_pages(काष्ठा address_space *mapping,
					काष्ठा ग_लिखोback_control *wbc,
					क्रमागत iostat_type io_type)
अणु
	पूर्णांक ret = 0;
	पूर्णांक करोne = 0, retry = 0;
	काष्ठा pagevec pvec;
	काष्ठा f2fs_sb_info *sbi = F2FS_M_SB(mapping);
	काष्ठा bio *bio = शून्य;
	sector_t last_block;
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	काष्ठा inode *inode = mapping->host;
	काष्ठा compress_ctx cc = अणु
		.inode = inode,
		.log_cluster_size = F2FS_I(inode)->i_log_cluster_size,
		.cluster_size = F2FS_I(inode)->i_cluster_size,
		.cluster_idx = शून्य_CLUSTER,
		.rpages = शून्य,
		.nr_rpages = 0,
		.cpages = शून्य,
		.rbuf = शून्य,
		.cbuf = शून्य,
		.rlen = PAGE_SIZE * F2FS_I(inode)->i_cluster_size,
		.निजी = शून्य,
	पूर्ण;
#पूर्ण_अगर
	पूर्णांक nr_pages;
	pgoff_t index;
	pgoff_t end;		/* Inclusive */
	pgoff_t करोne_index;
	पूर्णांक range_whole = 0;
	xa_mark_t tag;
	पूर्णांक nwritten = 0;
	पूर्णांक submitted = 0;
	पूर्णांक i;

	pagevec_init(&pvec);

	अगर (get_dirty_pages(mapping->host) <=
				SM_I(F2FS_M_SB(mapping))->min_hot_blocks)
		set_inode_flag(mapping->host, FI_HOT_DATA);
	अन्यथा
		clear_inode_flag(mapping->host, FI_HOT_DATA);

	अगर (wbc->range_cyclic) अणु
		index = mapping->ग_लिखोback_index; /* prev offset */
		end = -1;
	पूर्ण अन्यथा अणु
		index = wbc->range_start >> PAGE_SHIFT;
		end = wbc->range_end >> PAGE_SHIFT;
		अगर (wbc->range_start == 0 && wbc->range_end == Lदीर्घ_उच्च)
			range_whole = 1;
	पूर्ण
	अगर (wbc->sync_mode == WB_SYNC_ALL || wbc->tagged_ग_लिखोpages)
		tag = PAGECACHE_TAG_TOWRITE;
	अन्यथा
		tag = PAGECACHE_TAG_सूचीTY;
retry:
	retry = 0;
	अगर (wbc->sync_mode == WB_SYNC_ALL || wbc->tagged_ग_लिखोpages)
		tag_pages_क्रम_ग_लिखोback(mapping, index, end);
	करोne_index = index;
	जबतक (!करोne && !retry && (index <= end)) अणु
		nr_pages = pagevec_lookup_range_tag(&pvec, mapping, &index, end,
				tag);
		अगर (nr_pages == 0)
			अवरोध;

		क्रम (i = 0; i < nr_pages; i++) अणु
			काष्ठा page *page = pvec.pages[i];
			bool need_पढ़ोd;
पढ़ोd:
			need_पढ़ोd = false;
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
			अगर (f2fs_compressed_file(inode)) अणु
				ret = f2fs_init_compress_ctx(&cc);
				अगर (ret) अणु
					करोne = 1;
					अवरोध;
				पूर्ण

				अगर (!f2fs_cluster_can_merge_page(&cc,
								page->index)) अणु
					ret = f2fs_ग_लिखो_multi_pages(&cc,
						&submitted, wbc, io_type);
					अगर (!ret)
						need_पढ़ोd = true;
					जाओ result;
				पूर्ण

				अगर (unlikely(f2fs_cp_error(sbi)))
					जाओ lock_page;

				अगर (f2fs_cluster_is_empty(&cc)) अणु
					व्योम *fsdata = शून्य;
					काष्ठा page *pagep;
					पूर्णांक ret2;

					ret2 = f2fs_prepare_compress_overग_लिखो(
							inode, &pagep,
							page->index, &fsdata);
					अगर (ret2 < 0) अणु
						ret = ret2;
						करोne = 1;
						अवरोध;
					पूर्ण अन्यथा अगर (ret2 &&
						!f2fs_compress_ग_लिखो_end(inode,
								fsdata, page->index,
								1)) अणु
						retry = 1;
						अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					जाओ lock_page;
				पूर्ण
			पूर्ण
#पूर्ण_अगर
			/* give a priority to WB_SYNC thपढ़ोs */
			अगर (atomic_पढ़ो(&sbi->wb_sync_req[DATA]) &&
					wbc->sync_mode == WB_SYNC_NONE) अणु
				करोne = 1;
				अवरोध;
			पूर्ण
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
lock_page:
#पूर्ण_अगर
			करोne_index = page->index;
retry_ग_लिखो:
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
					f2fs_रुको_on_page_ग_लिखोback(page,
							DATA, true, true);
				अन्यथा
					जाओ जारी_unlock;
			पूर्ण

			अगर (!clear_page_dirty_क्रम_io(page))
				जाओ जारी_unlock;

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
			अगर (f2fs_compressed_file(inode)) अणु
				get_page(page);
				f2fs_compress_ctx_add_page(&cc, page);
				जारी;
			पूर्ण
#पूर्ण_अगर
			ret = f2fs_ग_लिखो_single_data_page(page, &submitted,
					&bio, &last_block, wbc, io_type,
					0, true);
			अगर (ret == AOP_WRITEPAGE_ACTIVATE)
				unlock_page(page);
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
result:
#पूर्ण_अगर
			nwritten += submitted;
			wbc->nr_to_ग_लिखो -= submitted;

			अगर (unlikely(ret)) अणु
				/*
				 * keep nr_to_ग_लिखो, since vfs uses this to
				 * get # of written pages.
				 */
				अगर (ret == AOP_WRITEPAGE_ACTIVATE) अणु
					ret = 0;
					जाओ next;
				पूर्ण अन्यथा अगर (ret == -EAGAIN) अणु
					ret = 0;
					अगर (wbc->sync_mode == WB_SYNC_ALL) अणु
						cond_resched();
						congestion_रुको(BLK_RW_ASYNC,
							DEFAULT_IO_TIMEOUT);
						जाओ retry_ग_लिखो;
					पूर्ण
					जाओ next;
				पूर्ण
				करोne_index = page->index + 1;
				करोne = 1;
				अवरोध;
			पूर्ण

			अगर (wbc->nr_to_ग_लिखो <= 0 &&
					wbc->sync_mode == WB_SYNC_NONE) अणु
				करोne = 1;
				अवरोध;
			पूर्ण
next:
			अगर (need_पढ़ोd)
				जाओ पढ़ोd;
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	/* flush reमुख्यed pages in compress cluster */
	अगर (f2fs_compressed_file(inode) && !f2fs_cluster_is_empty(&cc)) अणु
		ret = f2fs_ग_लिखो_multi_pages(&cc, &submitted, wbc, io_type);
		nwritten += submitted;
		wbc->nr_to_ग_लिखो -= submitted;
		अगर (ret) अणु
			करोne = 1;
			retry = 0;
		पूर्ण
	पूर्ण
	अगर (f2fs_compressed_file(inode))
		f2fs_destroy_compress_ctx(&cc, false);
#पूर्ण_अगर
	अगर (retry) अणु
		index = 0;
		end = -1;
		जाओ retry;
	पूर्ण
	अगर (wbc->range_cyclic && !करोne)
		करोne_index = 0;
	अगर (wbc->range_cyclic || (range_whole && wbc->nr_to_ग_लिखो > 0))
		mapping->ग_लिखोback_index = करोne_index;

	अगर (nwritten)
		f2fs_submit_merged_ग_लिखो_cond(F2FS_M_SB(mapping), mapping->host,
								शून्य, 0, DATA);
	/* submit cached bio of IPU ग_लिखो */
	अगर (bio)
		f2fs_submit_merged_ipu_ग_लिखो(sbi, &bio, शून्य);

	वापस ret;
पूर्ण

अटल अंतरभूत bool __should_serialize_io(काष्ठा inode *inode,
					काष्ठा ग_लिखोback_control *wbc)
अणु
	/* to aव्योम deadlock in path of data flush */
	अगर (F2FS_I(inode)->cp_task)
		वापस false;

	अगर (!S_ISREG(inode->i_mode))
		वापस false;
	अगर (IS_NOQUOTA(inode))
		वापस false;

	अगर (f2fs_need_compress_data(inode))
		वापस true;
	अगर (wbc->sync_mode != WB_SYNC_ALL)
		वापस true;
	अगर (get_dirty_pages(inode) >= SM_I(F2FS_I_SB(inode))->min_seq_blocks)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक __f2fs_ग_लिखो_data_pages(काष्ठा address_space *mapping,
						काष्ठा ग_लिखोback_control *wbc,
						क्रमागत iostat_type io_type)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा blk_plug plug;
	पूर्णांक ret;
	bool locked = false;

	/* deal with अक्षरdevs and other special file */
	अगर (!mapping->a_ops->ग_लिखोpage)
		वापस 0;

	/* skip writing अगर there is no dirty page in this inode */
	अगर (!get_dirty_pages(inode) && wbc->sync_mode == WB_SYNC_NONE)
		वापस 0;

	/* during POR, we करोn't need to trigger ग_लिखोpage at all. */
	अगर (unlikely(is_sbi_flag_set(sbi, SBI_POR_DOING)))
		जाओ skip_ग_लिखो;

	अगर ((S_ISसूची(inode->i_mode) || IS_NOQUOTA(inode)) &&
			wbc->sync_mode == WB_SYNC_NONE &&
			get_dirty_pages(inode) < nr_pages_to_skip(sbi, DATA) &&
			f2fs_available_मुक्त_memory(sbi, सूचीTY_DENTS))
		जाओ skip_ग_लिखो;

	/* skip writing during file defragment */
	अगर (is_inode_flag_set(inode, FI_DO_DEFRAG))
		जाओ skip_ग_लिखो;

	trace_f2fs_ग_लिखोpages(mapping->host, wbc, DATA);

	/* to aव्योम spliting IOs due to mixed WB_SYNC_ALL and WB_SYNC_NONE */
	अगर (wbc->sync_mode == WB_SYNC_ALL)
		atomic_inc(&sbi->wb_sync_req[DATA]);
	अन्यथा अगर (atomic_पढ़ो(&sbi->wb_sync_req[DATA]))
		जाओ skip_ग_लिखो;

	अगर (__should_serialize_io(inode, wbc)) अणु
		mutex_lock(&sbi->ग_लिखोpages);
		locked = true;
	पूर्ण

	blk_start_plug(&plug);
	ret = f2fs_ग_लिखो_cache_pages(mapping, wbc, io_type);
	blk_finish_plug(&plug);

	अगर (locked)
		mutex_unlock(&sbi->ग_लिखोpages);

	अगर (wbc->sync_mode == WB_SYNC_ALL)
		atomic_dec(&sbi->wb_sync_req[DATA]);
	/*
	 * अगर some pages were truncated, we cannot guarantee its mapping->host
	 * to detect pending bios.
	 */

	f2fs_हटाओ_dirty_inode(inode);
	वापस ret;

skip_ग_लिखो:
	wbc->pages_skipped += get_dirty_pages(inode);
	trace_f2fs_ग_लिखोpages(mapping->host, wbc, DATA);
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_ग_लिखो_data_pages(काष्ठा address_space *mapping,
			    काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = mapping->host;

	वापस __f2fs_ग_लिखो_data_pages(mapping, wbc,
			F2FS_I(inode)->cp_task == current ?
			FS_CP_DATA_IO : FS_DATA_IO);
पूर्ण

अटल व्योम f2fs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;
	loff_t i_size = i_size_पढ़ो(inode);

	अगर (IS_NOQUOTA(inode))
		वापस;

	/* In the fs-verity हाल, f2fs_end_enable_verity() करोes the truncate */
	अगर (to > i_size && !f2fs_verity_in_progress(inode)) अणु
		करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
		करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);

		truncate_pagecache(inode, i_size);
		f2fs_truncate_blocks(inode, i_size, true);

		up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
		up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	पूर्ण
पूर्ण

अटल पूर्णांक prepare_ग_लिखो_begin(काष्ठा f2fs_sb_info *sbi,
			काष्ठा page *page, loff_t pos, अचिन्हित len,
			block_t *blk_addr, bool *node_changed)
अणु
	काष्ठा inode *inode = page->mapping->host;
	pgoff_t index = page->index;
	काष्ठा dnode_of_data dn;
	काष्ठा page *ipage;
	bool locked = false;
	काष्ठा extent_info ei = अणु0,0,0पूर्ण;
	पूर्णांक err = 0;
	पूर्णांक flag;

	/*
	 * we alपढ़ोy allocated all the blocks, so we करोn't need to get
	 * the block addresses when there is no need to fill the page.
	 */
	अगर (!f2fs_has_अंतरभूत_data(inode) && len == PAGE_SIZE &&
	    !is_inode_flag_set(inode, FI_NO_PREALLOC) &&
	    !f2fs_verity_in_progress(inode))
		वापस 0;

	/* f2fs_lock_op aव्योमs race between ग_लिखो CP and convert_अंतरभूत_page */
	अगर (f2fs_has_अंतरभूत_data(inode) && pos + len > MAX_INLINE_DATA(inode))
		flag = F2FS_GET_BLOCK_DEFAULT;
	अन्यथा
		flag = F2FS_GET_BLOCK_PRE_AIO;

	अगर (f2fs_has_अंतरभूत_data(inode) ||
			(pos & PAGE_MASK) >= i_size_पढ़ो(inode)) अणु
		f2fs_करो_map_lock(sbi, flag, true);
		locked = true;
	पूर्ण

restart:
	/* check अंतरभूत_data */
	ipage = f2fs_get_node_page(sbi, inode->i_ino);
	अगर (IS_ERR(ipage)) अणु
		err = PTR_ERR(ipage);
		जाओ unlock_out;
	पूर्ण

	set_new_dnode(&dn, inode, ipage, ipage, 0);

	अगर (f2fs_has_अंतरभूत_data(inode)) अणु
		अगर (pos + len <= MAX_INLINE_DATA(inode)) अणु
			f2fs_करो_पढ़ो_अंतरभूत_data(page, ipage);
			set_inode_flag(inode, FI_DATA_EXIST);
			अगर (inode->i_nlink)
				set_अंतरभूत_node(ipage);
		पूर्ण अन्यथा अणु
			err = f2fs_convert_अंतरभूत_page(&dn, page);
			अगर (err)
				जाओ out;
			अगर (dn.data_blkaddr == शून्य_ADDR)
				err = f2fs_get_block(&dn, index);
		पूर्ण
	पूर्ण अन्यथा अगर (locked) अणु
		err = f2fs_get_block(&dn, index);
	पूर्ण अन्यथा अणु
		अगर (f2fs_lookup_extent_cache(inode, index, &ei)) अणु
			dn.data_blkaddr = ei.blk + index - ei.fofs;
		पूर्ण अन्यथा अणु
			/* hole हाल */
			err = f2fs_get_dnode_of_data(&dn, index, LOOKUP_NODE);
			अगर (err || dn.data_blkaddr == शून्य_ADDR) अणु
				f2fs_put_dnode(&dn);
				f2fs_करो_map_lock(sbi, F2FS_GET_BLOCK_PRE_AIO,
								true);
				WARN_ON(flag != F2FS_GET_BLOCK_PRE_AIO);
				locked = true;
				जाओ restart;
			पूर्ण
		पूर्ण
	पूर्ण

	/* convert_अंतरभूत_page can make node_changed */
	*blk_addr = dn.data_blkaddr;
	*node_changed = dn.node_changed;
out:
	f2fs_put_dnode(&dn);
unlock_out:
	अगर (locked)
		f2fs_करो_map_lock(sbi, flag, false);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
		loff_t pos, अचिन्हित len, अचिन्हित flags,
		काष्ठा page **pagep, व्योम **fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा page *page = शून्य;
	pgoff_t index = ((अचिन्हित दीर्घ दीर्घ) pos) >> PAGE_SHIFT;
	bool need_balance = false, drop_atomic = false;
	block_t blkaddr = शून्य_ADDR;
	पूर्णांक err = 0;

	trace_f2fs_ग_लिखो_begin(inode, pos, len, flags);

	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi)) अणु
		err = -ENOSPC;
		जाओ fail;
	पूर्ण

	अगर ((f2fs_is_atomic_file(inode) &&
			!f2fs_available_मुक्त_memory(sbi, INMEM_PAGES)) ||
			is_inode_flag_set(inode, FI_ATOMIC_REVOKE_REQUEST)) अणु
		err = -ENOMEM;
		drop_atomic = true;
		जाओ fail;
	पूर्ण

	/*
	 * We should check this at this moment to aव्योम deadlock on inode page
	 * and #0 page. The locking rule क्रम अंतरभूत_data conversion should be:
	 * lock_page(page #0) -> lock_page(inode_page)
	 */
	अगर (index != 0) अणु
		err = f2fs_convert_अंतरभूत_inode(inode);
		अगर (err)
			जाओ fail;
	पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	अगर (f2fs_compressed_file(inode)) अणु
		पूर्णांक ret;

		*fsdata = शून्य;

		ret = f2fs_prepare_compress_overग_लिखो(inode, pagep,
							index, fsdata);
		अगर (ret < 0) अणु
			err = ret;
			जाओ fail;
		पूर्ण अन्यथा अगर (ret) अणु
			वापस 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

repeat:
	/*
	 * Do not use grab_cache_page_ग_लिखो_begin() to aव्योम deadlock due to
	 * रुको_क्रम_stable_page. Will रुको that below with our IO control.
	 */
	page = f2fs_pagecache_get_page(mapping, index,
				FGP_LOCK | FGP_WRITE | FGP_CREAT, GFP_NOFS);
	अगर (!page) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* TODO: cluster can be compressed due to race with .ग_लिखोpage */

	*pagep = page;

	err = prepare_ग_लिखो_begin(sbi, page, pos, len,
					&blkaddr, &need_balance);
	अगर (err)
		जाओ fail;

	अगर (need_balance && !IS_NOQUOTA(inode) &&
			has_not_enough_मुक्त_secs(sbi, 0, 0)) अणु
		unlock_page(page);
		f2fs_balance_fs(sbi, true);
		lock_page(page);
		अगर (page->mapping != mapping) अणु
			/* The page got truncated from under us */
			f2fs_put_page(page, 1);
			जाओ repeat;
		पूर्ण
	पूर्ण

	f2fs_रुको_on_page_ग_लिखोback(page, DATA, false, true);

	अगर (len == PAGE_SIZE || PageUptodate(page))
		वापस 0;

	अगर (!(pos & (PAGE_SIZE - 1)) && (pos + len) >= i_size_पढ़ो(inode) &&
	    !f2fs_verity_in_progress(inode)) अणु
		zero_user_segment(page, len, PAGE_SIZE);
		वापस 0;
	पूर्ण

	अगर (blkaddr == NEW_ADDR) अणु
		zero_user_segment(page, 0, PAGE_SIZE);
		SetPageUptodate(page);
	पूर्ण अन्यथा अणु
		अगर (!f2fs_is_valid_blkaddr(sbi, blkaddr,
				DATA_GENERIC_ENHANCE_READ)) अणु
			err = -EFSCORRUPTED;
			जाओ fail;
		पूर्ण
		err = f2fs_submit_page_पढ़ो(inode, page, blkaddr, 0, true);
		अगर (err)
			जाओ fail;

		lock_page(page);
		अगर (unlikely(page->mapping != mapping)) अणु
			f2fs_put_page(page, 1);
			जाओ repeat;
		पूर्ण
		अगर (unlikely(!PageUptodate(page))) अणु
			err = -EIO;
			जाओ fail;
		पूर्ण
	पूर्ण
	वापस 0;

fail:
	f2fs_put_page(page, 1);
	f2fs_ग_लिखो_failed(mapping, pos + len);
	अगर (drop_atomic)
		f2fs_drop_inmem_pages_all(sbi, false);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_ग_लिखो_end(काष्ठा file *file,
			काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = page->mapping->host;

	trace_f2fs_ग_लिखो_end(inode, pos, len, copied);

	/*
	 * This should be come from len == PAGE_SIZE, and we expect copied
	 * should be PAGE_SIZE. Otherwise, we treat it with zero copied and
	 * let generic_perक्रमm_ग_लिखो() try to copy data again through copied=0.
	 */
	अगर (!PageUptodate(page)) अणु
		अगर (unlikely(copied != len))
			copied = 0;
		अन्यथा
			SetPageUptodate(page);
	पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	/* overग_लिखो compressed file */
	अगर (f2fs_compressed_file(inode) && fsdata) अणु
		f2fs_compress_ग_लिखो_end(inode, fsdata, page->index, copied);
		f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);

		अगर (pos + copied > i_size_पढ़ो(inode) &&
				!f2fs_verity_in_progress(inode))
			f2fs_i_size_ग_लिखो(inode, pos + copied);
		वापस copied;
	पूर्ण
#पूर्ण_अगर

	अगर (!copied)
		जाओ unlock_out;

	set_page_dirty(page);

	अगर (pos + copied > i_size_पढ़ो(inode) &&
	    !f2fs_verity_in_progress(inode))
		f2fs_i_size_ग_लिखो(inode, pos + copied);
unlock_out:
	f2fs_put_page(page, 1);
	f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);
	वापस copied;
पूर्ण

अटल पूर्णांक check_direct_IO(काष्ठा inode *inode, काष्ठा iov_iter *iter,
			   loff_t offset)
अणु
	अचिन्हित i_blkbits = READ_ONCE(inode->i_blkbits);
	अचिन्हित blkbits = i_blkbits;
	अचिन्हित blocksize_mask = (1 << blkbits) - 1;
	अचिन्हित दीर्घ align = offset | iov_iter_alignment(iter);
	काष्ठा block_device *bdev = inode->i_sb->s_bdev;

	अगर (iov_iter_rw(iter) == READ && offset >= i_size_पढ़ो(inode))
		वापस 1;

	अगर (align & blocksize_mask) अणु
		अगर (bdev)
			blkbits = blksize_bits(bdev_logical_block_size(bdev));
		blocksize_mask = (1 << blkbits) - 1;
		अगर (align & blocksize_mask)
			वापस -EINVAL;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम f2fs_dio_end_io(काष्ठा bio *bio)
अणु
	काष्ठा f2fs_निजी_dio *dio = bio->bi_निजी;

	dec_page_count(F2FS_I_SB(dio->inode),
			dio->ग_लिखो ? F2FS_DIO_WRITE : F2FS_DIO_READ);

	bio->bi_निजी = dio->orig_निजी;
	bio->bi_end_io = dio->orig_end_io;

	kमुक्त(dio);

	bio_endio(bio);
पूर्ण

अटल व्योम f2fs_dio_submit_bio(काष्ठा bio *bio, काष्ठा inode *inode,
							loff_t file_offset)
अणु
	काष्ठा f2fs_निजी_dio *dio;
	bool ग_लिखो = (bio_op(bio) == REQ_OP_WRITE);

	dio = f2fs_kzalloc(F2FS_I_SB(inode),
			माप(काष्ठा f2fs_निजी_dio), GFP_NOFS);
	अगर (!dio)
		जाओ out;

	dio->inode = inode;
	dio->orig_end_io = bio->bi_end_io;
	dio->orig_निजी = bio->bi_निजी;
	dio->ग_लिखो = ग_लिखो;

	bio->bi_end_io = f2fs_dio_end_io;
	bio->bi_निजी = dio;

	inc_page_count(F2FS_I_SB(inode),
			ग_लिखो ? F2FS_DIO_WRITE : F2FS_DIO_READ);

	submit_bio(bio);
	वापस;
out:
	bio->bi_status = BLK_STS_IOERR;
	bio_endio(bio);
पूर्ण

अटल sमाप_प्रकार f2fs_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा address_space *mapping = iocb->ki_filp->f_mapping;
	काष्ठा inode *inode = mapping->host;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	माप_प्रकार count = iov_iter_count(iter);
	loff_t offset = iocb->ki_pos;
	पूर्णांक rw = iov_iter_rw(iter);
	पूर्णांक err;
	क्रमागत rw_hपूर्णांक hपूर्णांक = iocb->ki_hपूर्णांक;
	पूर्णांक whपूर्णांक_mode = F2FS_OPTION(sbi).whपूर्णांक_mode;
	bool करो_opu;

	err = check_direct_IO(inode, iter, offset);
	अगर (err)
		वापस err < 0 ? err : 0;

	अगर (f2fs_क्रमce_buffered_io(inode, iocb, iter))
		वापस 0;

	करो_opu = allow_outplace_dio(inode, iocb, iter);

	trace_f2fs_direct_IO_enter(inode, offset, count, rw);

	अगर (rw == WRITE && whपूर्णांक_mode == WHINT_MODE_OFF)
		iocb->ki_hपूर्णांक = WRITE_LIFE_NOT_SET;

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!करोwn_पढ़ो_trylock(&fi->i_gc_rwsem[rw])) अणु
			iocb->ki_hपूर्णांक = hपूर्णांक;
			err = -EAGAIN;
			जाओ out;
		पूर्ण
		अगर (करो_opu && !करोwn_पढ़ो_trylock(&fi->i_gc_rwsem[READ])) अणु
			up_पढ़ो(&fi->i_gc_rwsem[rw]);
			iocb->ki_hपूर्णांक = hपूर्णांक;
			err = -EAGAIN;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&fi->i_gc_rwsem[rw]);
		अगर (करो_opu)
			करोwn_पढ़ो(&fi->i_gc_rwsem[READ]);
	पूर्ण

	err = __blockdev_direct_IO(iocb, inode, inode->i_sb->s_bdev,
			iter, rw == WRITE ? get_data_block_dio_ग_लिखो :
			get_data_block_dio, शून्य, f2fs_dio_submit_bio,
			rw == WRITE ? DIO_LOCKING | DIO_SKIP_HOLES :
			DIO_SKIP_HOLES);

	अगर (करो_opu)
		up_पढ़ो(&fi->i_gc_rwsem[READ]);

	up_पढ़ो(&fi->i_gc_rwsem[rw]);

	अगर (rw == WRITE) अणु
		अगर (whपूर्णांक_mode == WHINT_MODE_OFF)
			iocb->ki_hपूर्णांक = hपूर्णांक;
		अगर (err > 0) अणु
			f2fs_update_iostat(F2FS_I_SB(inode), APP_सूचीECT_IO,
									err);
			अगर (!करो_opu)
				set_inode_flag(inode, FI_UPDATE_WRITE);
		पूर्ण अन्यथा अगर (err == -EIOCBQUEUED) अणु
			f2fs_update_iostat(F2FS_I_SB(inode), APP_सूचीECT_IO,
						count - iov_iter_count(iter));
		पूर्ण अन्यथा अगर (err < 0) अणु
			f2fs_ग_लिखो_failed(mapping, offset + count);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (err > 0)
			f2fs_update_iostat(sbi, APP_सूचीECT_READ_IO, err);
		अन्यथा अगर (err == -EIOCBQUEUED)
			f2fs_update_iostat(F2FS_I_SB(inode), APP_सूचीECT_READ_IO,
						count - iov_iter_count(iter));
	पूर्ण

out:
	trace_f2fs_direct_IO_निकास(inode, offset, count, rw, err);

	वापस err;
पूर्ण

व्योम f2fs_invalidate_page(काष्ठा page *page, अचिन्हित पूर्णांक offset,
							अचिन्हित पूर्णांक length)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

	अगर (inode->i_ino >= F2FS_ROOT_INO(sbi) &&
		(offset % PAGE_SIZE || length != PAGE_SIZE))
		वापस;

	अगर (PageDirty(page)) अणु
		अगर (inode->i_ino == F2FS_META_INO(sbi)) अणु
			dec_page_count(sbi, F2FS_सूचीTY_META);
		पूर्ण अन्यथा अगर (inode->i_ino == F2FS_NODE_INO(sbi)) अणु
			dec_page_count(sbi, F2FS_सूचीTY_NODES);
		पूर्ण अन्यथा अणु
			inode_dec_dirty_pages(inode);
			f2fs_हटाओ_dirty_inode(inode);
		पूर्ण
	पूर्ण

	clear_cold_data(page);

	अगर (IS_ATOMIC_WRITTEN_PAGE(page))
		वापस f2fs_drop_inmem_page(inode, page);

	f2fs_clear_page_निजी(page);
पूर्ण

पूर्णांक f2fs_release_page(काष्ठा page *page, gfp_t रुको)
अणु
	/* If this is dirty page, keep PagePrivate */
	अगर (PageDirty(page))
		वापस 0;

	/* This is atomic written page, keep Private */
	अगर (IS_ATOMIC_WRITTEN_PAGE(page))
		वापस 0;

	clear_cold_data(page);
	f2fs_clear_page_निजी(page);
	वापस 1;
पूर्ण

अटल पूर्णांक f2fs_set_data_page_dirty(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page_file_mapping(page)->host;

	trace_f2fs_set_page_dirty(page, DATA);

	अगर (!PageUptodate(page))
		SetPageUptodate(page);
	अगर (PageSwapCache(page))
		वापस __set_page_dirty_nobuffers(page);

	अगर (f2fs_is_atomic_file(inode) && !f2fs_is_commit_atomic_ग_लिखो(inode)) अणु
		अगर (!IS_ATOMIC_WRITTEN_PAGE(page)) अणु
			f2fs_रेजिस्टर_inmem_page(inode, page);
			वापस 1;
		पूर्ण
		/*
		 * Previously, this page has been रेजिस्टरed, we just
		 * वापस here.
		 */
		वापस 0;
	पूर्ण

	अगर (!PageDirty(page)) अणु
		__set_page_dirty_nobuffers(page);
		f2fs_update_dirty_page(inode, page);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


अटल sector_t f2fs_bmap_compress(काष्ठा inode *inode, sector_t block)
अणु
#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	काष्ठा dnode_of_data dn;
	sector_t start_idx, blknr = 0;
	पूर्णांक ret;

	start_idx = round_करोwn(block, F2FS_I(inode)->i_cluster_size);

	set_new_dnode(&dn, inode, शून्य, शून्य, 0);
	ret = f2fs_get_dnode_of_data(&dn, start_idx, LOOKUP_NODE);
	अगर (ret)
		वापस 0;

	अगर (dn.data_blkaddr != COMPRESS_ADDR) अणु
		dn.ofs_in_node += block - start_idx;
		blknr = f2fs_data_blkaddr(&dn);
		अगर (!__is_valid_data_blkaddr(blknr))
			blknr = 0;
	पूर्ण

	f2fs_put_dnode(&dn);
	वापस blknr;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण


अटल sector_t f2fs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	काष्ठा inode *inode = mapping->host;
	sector_t blknr = 0;

	अगर (f2fs_has_अंतरभूत_data(inode))
		जाओ out;

	/* make sure allocating whole blocks */
	अगर (mapping_tagged(mapping, PAGECACHE_TAG_सूचीTY))
		filemap_ग_लिखो_and_रुको(mapping);

	/* Block number less than F2FS MAX BLOCKS */
	अगर (unlikely(block >= max_file_blocks(inode)))
		जाओ out;

	अगर (f2fs_compressed_file(inode)) अणु
		blknr = f2fs_bmap_compress(inode, block);
	पूर्ण अन्यथा अणु
		काष्ठा f2fs_map_blocks map;

		स_रखो(&map, 0, माप(map));
		map.m_lblk = block;
		map.m_len = 1;
		map.m_next_pgofs = शून्य;
		map.m_seg_type = NO_CHECK_TYPE;

		अगर (!f2fs_map_blocks(inode, &map, 0, F2FS_GET_BLOCK_BMAP))
			blknr = map.m_pblk;
	पूर्ण
out:
	trace_f2fs_bmap(inode, block, blknr);
	वापस blknr;
पूर्ण

#अगर_घोषित CONFIG_MIGRATION
#समावेश <linux/migrate.h>

पूर्णांक f2fs_migrate_page(काष्ठा address_space *mapping,
		काष्ठा page *newpage, काष्ठा page *page, क्रमागत migrate_mode mode)
अणु
	पूर्णांक rc, extra_count;
	काष्ठा f2fs_inode_info *fi = F2FS_I(mapping->host);
	bool atomic_written = IS_ATOMIC_WRITTEN_PAGE(page);

	BUG_ON(PageWriteback(page));

	/* migrating an atomic written page is safe with the inmem_lock hold */
	अगर (atomic_written) अणु
		अगर (mode != MIGRATE_SYNC)
			वापस -EBUSY;
		अगर (!mutex_trylock(&fi->inmem_lock))
			वापस -EAGAIN;
	पूर्ण

	/* one extra reference was held क्रम atomic_ग_लिखो page */
	extra_count = atomic_written ? 1 : 0;
	rc = migrate_page_move_mapping(mapping, newpage,
				page, extra_count);
	अगर (rc != MIGRATEPAGE_SUCCESS) अणु
		अगर (atomic_written)
			mutex_unlock(&fi->inmem_lock);
		वापस rc;
	पूर्ण

	अगर (atomic_written) अणु
		काष्ठा inmem_pages *cur;

		list_क्रम_each_entry(cur, &fi->inmem_pages, list)
			अगर (cur->page == page) अणु
				cur->page = newpage;
				अवरोध;
			पूर्ण
		mutex_unlock(&fi->inmem_lock);
		put_page(page);
		get_page(newpage);
	पूर्ण

	अगर (PagePrivate(page)) अणु
		f2fs_set_page_निजी(newpage, page_निजी(page));
		f2fs_clear_page_निजी(page);
	पूर्ण

	अगर (mode != MIGRATE_SYNC_NO_COPY)
		migrate_page_copy(newpage, page);
	अन्यथा
		migrate_page_states(newpage, page);

	वापस MIGRATEPAGE_SUCCESS;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SWAP
अटल पूर्णांक f2fs_is_file_aligned(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	block_t मुख्य_blkaddr = SM_I(sbi)->मुख्य_blkaddr;
	block_t cur_lblock;
	block_t last_lblock;
	block_t pblock;
	अचिन्हित दीर्घ nr_pblocks;
	अचिन्हित पूर्णांक blocks_per_sec = BLKS_PER_SEC(sbi);
	अचिन्हित पूर्णांक not_aligned = 0;
	पूर्णांक ret = 0;

	cur_lblock = 0;
	last_lblock = bytes_to_blks(inode, i_size_पढ़ो(inode));

	जबतक (cur_lblock < last_lblock) अणु
		काष्ठा f2fs_map_blocks map;

		स_रखो(&map, 0, माप(map));
		map.m_lblk = cur_lblock;
		map.m_len = last_lblock - cur_lblock;
		map.m_next_pgofs = शून्य;
		map.m_next_extent = शून्य;
		map.m_seg_type = NO_CHECK_TYPE;
		map.m_may_create = false;

		ret = f2fs_map_blocks(inode, &map, 0, F2FS_GET_BLOCK_FIEMAP);
		अगर (ret)
			जाओ out;

		/* hole */
		अगर (!(map.m_flags & F2FS_MAP_FLAGS)) अणु
			f2fs_err(sbi, "Swapfile has holes\n");
			ret = -ENOENT;
			जाओ out;
		पूर्ण

		pblock = map.m_pblk;
		nr_pblocks = map.m_len;

		अगर ((pblock - मुख्य_blkaddr) & (blocks_per_sec - 1) ||
			nr_pblocks & (blocks_per_sec - 1)) अणु
			अगर (f2fs_is_pinned_file(inode)) अणु
				f2fs_err(sbi, "Swapfile does not align to section");
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			not_aligned++;
		पूर्ण

		cur_lblock += nr_pblocks;
	पूर्ण
	अगर (not_aligned)
		f2fs_warn(sbi, "Swapfile (%u) is not align to section: \n"
			"\t1) creat(), 2) ioctl(F2FS_IOC_SET_PIN_FILE), 3) fallocate()",
			not_aligned);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक check_swap_activate_fast(काष्ठा swap_info_काष्ठा *sis,
				काष्ठा file *swap_file, sector_t *span)
अणु
	काष्ठा address_space *mapping = swap_file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	sector_t cur_lblock;
	sector_t last_lblock;
	sector_t pblock;
	sector_t lowest_pblock = -1;
	sector_t highest_pblock = 0;
	पूर्णांक nr_extents = 0;
	अचिन्हित दीर्घ nr_pblocks;
	अचिन्हित पूर्णांक blocks_per_sec = BLKS_PER_SEC(sbi);
	अचिन्हित पूर्णांक not_aligned = 0;
	पूर्णांक ret = 0;

	/*
	 * Map all the blocks पूर्णांकo the extent list.  This code करोesn't try
	 * to be very smart.
	 */
	cur_lblock = 0;
	last_lblock = bytes_to_blks(inode, i_size_पढ़ो(inode));

	जबतक (cur_lblock < last_lblock && cur_lblock < sis->max) अणु
		काष्ठा f2fs_map_blocks map;

		cond_resched();

		स_रखो(&map, 0, माप(map));
		map.m_lblk = cur_lblock;
		map.m_len = last_lblock - cur_lblock;
		map.m_next_pgofs = शून्य;
		map.m_next_extent = शून्य;
		map.m_seg_type = NO_CHECK_TYPE;
		map.m_may_create = false;

		ret = f2fs_map_blocks(inode, &map, 0, F2FS_GET_BLOCK_FIEMAP);
		अगर (ret)
			जाओ out;

		/* hole */
		अगर (!(map.m_flags & F2FS_MAP_FLAGS)) अणु
			f2fs_err(sbi, "Swapfile has holes\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		pblock = map.m_pblk;
		nr_pblocks = map.m_len;

		अगर ((pblock - SM_I(sbi)->मुख्य_blkaddr) & (blocks_per_sec - 1) ||
				nr_pblocks & (blocks_per_sec - 1)) अणु
			अगर (f2fs_is_pinned_file(inode)) अणु
				f2fs_err(sbi, "Swapfile does not align to section");
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			not_aligned++;
		पूर्ण

		अगर (cur_lblock + nr_pblocks >= sis->max)
			nr_pblocks = sis->max - cur_lblock;

		अगर (cur_lblock) अणु	/* exclude the header page */
			अगर (pblock < lowest_pblock)
				lowest_pblock = pblock;
			अगर (pblock + nr_pblocks - 1 > highest_pblock)
				highest_pblock = pblock + nr_pblocks - 1;
		पूर्ण

		/*
		 * We found a PAGE_SIZE-length, PAGE_SIZE-aligned run of blocks
		 */
		ret = add_swap_extent(sis, cur_lblock, nr_pblocks, pblock);
		अगर (ret < 0)
			जाओ out;
		nr_extents += ret;
		cur_lblock += nr_pblocks;
	पूर्ण
	ret = nr_extents;
	*span = 1 + highest_pblock - lowest_pblock;
	अगर (cur_lblock == 0)
		cur_lblock = 1;	/* क्रमce Empty message */
	sis->max = cur_lblock;
	sis->pages = cur_lblock - 1;
	sis->highest_bit = cur_lblock - 1;

	अगर (not_aligned)
		f2fs_warn(sbi, "Swapfile (%u) is not align to section: \n"
			"\t1) creat(), 2) ioctl(F2FS_IOC_SET_PIN_FILE), 3) fallocate()",
			not_aligned);
out:
	वापस ret;
पूर्ण

/* Copied from generic_swapfile_activate() to check any holes */
अटल पूर्णांक check_swap_activate(काष्ठा swap_info_काष्ठा *sis,
				काष्ठा file *swap_file, sector_t *span)
अणु
	काष्ठा address_space *mapping = swap_file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	अचिन्हित blocks_per_page;
	अचिन्हित दीर्घ page_no;
	sector_t probe_block;
	sector_t last_block;
	sector_t lowest_block = -1;
	sector_t highest_block = 0;
	पूर्णांक nr_extents = 0;
	पूर्णांक ret = 0;

	अगर (PAGE_SIZE == F2FS_BLKSIZE)
		वापस check_swap_activate_fast(sis, swap_file, span);

	ret = f2fs_is_file_aligned(inode);
	अगर (ret)
		जाओ out;

	blocks_per_page = bytes_to_blks(inode, PAGE_SIZE);

	/*
	 * Map all the blocks पूर्णांकo the extent list.  This code करोesn't try
	 * to be very smart.
	 */
	probe_block = 0;
	page_no = 0;
	last_block = bytes_to_blks(inode, i_size_पढ़ो(inode));
	जबतक ((probe_block + blocks_per_page) <= last_block &&
			page_no < sis->max) अणु
		अचिन्हित block_in_page;
		sector_t first_block;
		sector_t block = 0;

		cond_resched();

		block = probe_block;
		ret = bmap(inode, &block);
		अगर (ret)
			जाओ out;
		अगर (!block)
			जाओ bad_bmap;
		first_block = block;

		/*
		 * It must be PAGE_SIZE aligned on-disk
		 */
		अगर (first_block & (blocks_per_page - 1)) अणु
			probe_block++;
			जाओ reprobe;
		पूर्ण

		क्रम (block_in_page = 1; block_in_page < blocks_per_page;
					block_in_page++) अणु

			block = probe_block + block_in_page;
			ret = bmap(inode, &block);
			अगर (ret)
				जाओ out;
			अगर (!block)
				जाओ bad_bmap;

			अगर (block != first_block + block_in_page) अणु
				/* Discontiguity */
				probe_block++;
				जाओ reprobe;
			पूर्ण
		पूर्ण

		first_block >>= (PAGE_SHIFT - inode->i_blkbits);
		अगर (page_no) अणु	/* exclude the header page */
			अगर (first_block < lowest_block)
				lowest_block = first_block;
			अगर (first_block > highest_block)
				highest_block = first_block;
		पूर्ण

		/*
		 * We found a PAGE_SIZE-length, PAGE_SIZE-aligned run of blocks
		 */
		ret = add_swap_extent(sis, page_no, 1, first_block);
		अगर (ret < 0)
			जाओ out;
		nr_extents += ret;
		page_no++;
		probe_block += blocks_per_page;
reprobe:
		जारी;
	पूर्ण
	ret = nr_extents;
	*span = 1 + highest_block - lowest_block;
	अगर (page_no == 0)
		page_no = 1;	/* क्रमce Empty message */
	sis->max = page_no;
	sis->pages = page_no - 1;
	sis->highest_bit = page_no - 1;
out:
	वापस ret;
bad_bmap:
	f2fs_err(sbi, "Swapfile has holes\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक f2fs_swap_activate(काष्ठा swap_info_काष्ठा *sis, काष्ठा file *file,
				sector_t *span)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक ret;

	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;

	अगर (f2fs_पढ़ोonly(F2FS_I_SB(inode)->sb))
		वापस -EROFS;

	ret = f2fs_convert_अंतरभूत_inode(inode);
	अगर (ret)
		वापस ret;

	अगर (!f2fs_disable_compressed_file(inode))
		वापस -EINVAL;

	f2fs_precache_extents(inode);

	ret = check_swap_activate(sis, file, span);
	अगर (ret < 0)
		वापस ret;

	set_inode_flag(inode, FI_PIN_खाता);
	f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);
	वापस ret;
पूर्ण

अटल व्योम f2fs_swap_deactivate(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);

	clear_inode_flag(inode, FI_PIN_खाता);
पूर्ण
#अन्यथा
अटल पूर्णांक f2fs_swap_activate(काष्ठा swap_info_काष्ठा *sis, काष्ठा file *file,
				sector_t *span)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम f2fs_swap_deactivate(काष्ठा file *file)
अणु
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा address_space_operations f2fs_dblock_aops = अणु
	.पढ़ोpage	= f2fs_पढ़ो_data_page,
	.पढ़ोahead	= f2fs_पढ़ोahead,
	.ग_लिखोpage	= f2fs_ग_लिखो_data_page,
	.ग_लिखोpages	= f2fs_ग_लिखो_data_pages,
	.ग_लिखो_begin	= f2fs_ग_लिखो_begin,
	.ग_लिखो_end	= f2fs_ग_लिखो_end,
	.set_page_dirty	= f2fs_set_data_page_dirty,
	.invalidatepage	= f2fs_invalidate_page,
	.releasepage	= f2fs_release_page,
	.direct_IO	= f2fs_direct_IO,
	.bmap		= f2fs_bmap,
	.swap_activate  = f2fs_swap_activate,
	.swap_deactivate = f2fs_swap_deactivate,
#अगर_घोषित CONFIG_MIGRATION
	.migratepage    = f2fs_migrate_page,
#पूर्ण_अगर
पूर्ण;

व्योम f2fs_clear_page_cache_dirty_tag(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page_mapping(page);
	अचिन्हित दीर्घ flags;

	xa_lock_irqsave(&mapping->i_pages, flags);
	__xa_clear_mark(&mapping->i_pages, page_index(page),
						PAGECACHE_TAG_सूचीTY);
	xa_unlock_irqrestore(&mapping->i_pages, flags);
पूर्ण

पूर्णांक __init f2fs_init_post_पढ़ो_processing(व्योम)
अणु
	bio_post_पढ़ो_ctx_cache =
		kmem_cache_create("f2fs_bio_post_read_ctx",
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

व्योम f2fs_destroy_post_पढ़ो_processing(व्योम)
अणु
	mempool_destroy(bio_post_पढ़ो_ctx_pool);
	kmem_cache_destroy(bio_post_पढ़ो_ctx_cache);
पूर्ण

पूर्णांक f2fs_init_post_पढ़ो_wq(काष्ठा f2fs_sb_info *sbi)
अणु
	अगर (!f2fs_sb_has_encrypt(sbi) &&
		!f2fs_sb_has_verity(sbi) &&
		!f2fs_sb_has_compression(sbi))
		वापस 0;

	sbi->post_पढ़ो_wq = alloc_workqueue("f2fs_post_read_wq",
						 WQ_UNBOUND | WQ_HIGHPRI,
						 num_online_cpus());
	अगर (!sbi->post_पढ़ो_wq)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम f2fs_destroy_post_पढ़ो_wq(काष्ठा f2fs_sb_info *sbi)
अणु
	अगर (sbi->post_पढ़ो_wq)
		destroy_workqueue(sbi->post_पढ़ो_wq);
पूर्ण

पूर्णांक __init f2fs_init_bio_entry_cache(व्योम)
अणु
	bio_entry_slab = f2fs_kmem_cache_create("f2fs_bio_entry_slab",
			माप(काष्ठा bio_entry));
	अगर (!bio_entry_slab)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम f2fs_destroy_bio_entry_cache(व्योम)
अणु
	kmem_cache_destroy(bio_entry_slab);
पूर्ण
