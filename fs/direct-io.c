<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/direct-io.c
 *
 * Copyright (C) 2002, Linus Torvalds.
 *
 * O_सूचीECT
 *
 * 04Jul2002	Andrew Morton
 *		Initial version
 * 11Sep2002	janetinc@us.ibm.com
 * 		added पढ़ोv/ग_लिखोv support.
 * 29Oct2002	Andrew Morton
 *		rewrote bio_add_page() support.
 * 30Oct2002	pbadari@us.ibm.com
 *		added support क्रम non-aligned IO.
 * 06Nov2002	pbadari@us.ibm.com
 *		added asynchronous IO support.
 * 21Jul2003	nathans@sgi.com
 *		added IO completion notअगरier.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/bपन.स>
#समावेश <linux/रुको.h>
#समावेश <linux/err.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/uपन.स>
#समावेश <linux/atomic.h>
#समावेश <linux/prefetch.h>

#समावेश "internal.h"

/*
 * How many user pages to map in one call to get_user_pages().  This determines
 * the size of a काष्ठाure in the slab cache
 */
#घोषणा DIO_PAGES	64

/*
 * Flags क्रम dio_complete()
 */
#घोषणा DIO_COMPLETE_ASYNC		0x01	/* This is async IO */
#घोषणा DIO_COMPLETE_INVALIDATE		0x02	/* Can invalidate pages */

/*
 * This code generally works in units of "dio_blocks".  A dio_block is
 * somewhere between the hard sector size and the fileप्रणाली block size.  it
 * is determined on a per-invocation basis.   When talking to the fileप्रणाली
 * we need to convert dio_blocks to fs_blocks by scaling the dio_block quantity
 * करोwn by dio->blkfactor.  Similarly, fs-blocksize quantities are converted
 * to bio_block quantities by shअगरting left by blkfactor.
 *
 * If blkfactor is zero then the user's request was aligned to the filesystem's
 * blocksize.
 */

/* dio_state only used in the submission path */

काष्ठा dio_submit अणु
	काष्ठा bio *bio;		/* bio under assembly */
	अचिन्हित blkbits;		/* करोesn't change */
	अचिन्हित blkfactor;		/* When we're using an alignment which
					   is finer than the fileप्रणाली's soft
					   blocksize, this specअगरies how much
					   finer.  blkfactor=2 means 1/4-block
					   alignment.  Does not change */
	अचिन्हित start_zero_करोne;	/* flag: sub-blocksize zeroing has
					   been perक्रमmed at the start of a
					   ग_लिखो */
	पूर्णांक pages_in_io;		/* approximate total IO pages */
	sector_t block_in_file;		/* Current offset पूर्णांकo the underlying
					   file in dio_block units. */
	अचिन्हित blocks_available;	/* At block_in_file.  changes */
	पूर्णांक reap_counter;		/* rate limit reaping */
	sector_t final_block_in_request;/* करोesn't change */
	पूर्णांक boundary;			/* prev block is at a boundary */
	get_block_t *get_block;		/* block mapping function */
	dio_submit_t *submit_io;	/* IO submition function */

	loff_t logical_offset_in_bio;	/* current first logical block in bio */
	sector_t final_block_in_bio;	/* current final block in bio + 1 */
	sector_t next_block_क्रम_io;	/* next block to be put under IO,
					   in dio_blocks units */

	/*
	 * Deferred addition of a page to the dio.  These variables are
	 * निजी to dio_send_cur_page(), submit_page_section() and
	 * dio_bio_add_page().
	 */
	काष्ठा page *cur_page;		/* The page */
	अचिन्हित cur_page_offset;	/* Offset पूर्णांकo it, in bytes */
	अचिन्हित cur_page_len;		/* Nr of bytes at cur_page_offset */
	sector_t cur_page_block;	/* Where it starts */
	loff_t cur_page_fs_offset;	/* Offset in file */

	काष्ठा iov_iter *iter;
	/*
	 * Page queue.  These variables beदीर्घ to dio_refill_pages() and
	 * dio_get_page().
	 */
	अचिन्हित head;			/* next page to process */
	अचिन्हित tail;			/* last valid page + 1 */
	माप_प्रकार from, to;
पूर्ण;

/* dio_state communicated between submission path and end_io */
काष्ठा dio अणु
	पूर्णांक flags;			/* करोesn't change */
	पूर्णांक op;
	पूर्णांक op_flags;
	blk_qc_t bio_cookie;
	काष्ठा gendisk *bio_disk;
	काष्ठा inode *inode;
	loff_t i_size;			/* i_size when submitted */
	dio_ioकरोne_t *end_io;		/* IO completion function */

	व्योम *निजी;			/* copy from map_bh.b_निजी */

	/* BIO completion state */
	spinlock_t bio_lock;		/* protects BIO fields below */
	पूर्णांक page_errors;		/* त्रुटि_सं from get_user_pages() */
	पूर्णांक is_async;			/* is IO async ? */
	bool defer_completion;		/* defer AIO completion to workqueue? */
	bool should_dirty;		/* अगर pages should be dirtied */
	पूर्णांक io_error;			/* IO error in completion path */
	अचिन्हित दीर्घ refcount;		/* direct_io_worker() and bios */
	काष्ठा bio *bio_list;		/* singly linked via bi_निजी */
	काष्ठा task_काष्ठा *रुकोer;	/* रुकोing task (शून्य अगर none) */

	/* AIO related stuff */
	काष्ठा kiocb *iocb;		/* kiocb */
	sमाप_प्रकार result;                 /* IO result */

	/*
	 * pages[] (and any fields placed after it) are not zeroed out at
	 * allocation समय.  Don't add new fields after pages[] unless you
	 * wish that they not be zeroed.
	 */
	जोड़ अणु
		काष्ठा page *pages[DIO_PAGES];	/* page buffer */
		काष्ठा work_काष्ठा complete_work;/* deferred AIO completion */
	पूर्ण;
पूर्ण ____cacheline_aligned_in_smp;

अटल काष्ठा kmem_cache *dio_cache __पढ़ो_mostly;

/*
 * How many pages are in the queue?
 */
अटल अंतरभूत अचिन्हित dio_pages_present(काष्ठा dio_submit *sdio)
अणु
	वापस sdio->tail - sdio->head;
पूर्ण

/*
 * Go grab and pin some userspace pages.   Typically we'll get 64 at a समय.
 */
अटल अंतरभूत पूर्णांक dio_refill_pages(काष्ठा dio *dio, काष्ठा dio_submit *sdio)
अणु
	sमाप_प्रकार ret;

	ret = iov_iter_get_pages(sdio->iter, dio->pages, दीर्घ_उच्च, DIO_PAGES,
				&sdio->from);

	अगर (ret < 0 && sdio->blocks_available && (dio->op == REQ_OP_WRITE)) अणु
		काष्ठा page *page = ZERO_PAGE(0);
		/*
		 * A memory fault, but the fileप्रणाली has some outstanding
		 * mapped blocks.  We need to use those blocks up to aव्योम
		 * leaking stale data in the file.
		 */
		अगर (dio->page_errors == 0)
			dio->page_errors = ret;
		get_page(page);
		dio->pages[0] = page;
		sdio->head = 0;
		sdio->tail = 1;
		sdio->from = 0;
		sdio->to = PAGE_SIZE;
		वापस 0;
	पूर्ण

	अगर (ret >= 0) अणु
		iov_iter_advance(sdio->iter, ret);
		ret += sdio->from;
		sdio->head = 0;
		sdio->tail = (ret + PAGE_SIZE - 1) / PAGE_SIZE;
		sdio->to = ((ret - 1) & (PAGE_SIZE - 1)) + 1;
		वापस 0;
	पूर्ण
	वापस ret;	
पूर्ण

/*
 * Get another userspace page.  Returns an ERR_PTR on error.  Pages are
 * buffered inside the dio so that we can call get_user_pages() against a
 * decent number of pages, less frequently.  To provide nicer use of the
 * L1 cache.
 */
अटल अंतरभूत काष्ठा page *dio_get_page(काष्ठा dio *dio,
					काष्ठा dio_submit *sdio)
अणु
	अगर (dio_pages_present(sdio) == 0) अणु
		पूर्णांक ret;

		ret = dio_refill_pages(dio, sdio);
		अगर (ret)
			वापस ERR_PTR(ret);
		BUG_ON(dio_pages_present(sdio) == 0);
	पूर्ण
	वापस dio->pages[sdio->head];
पूर्ण

/*
 * dio_complete() - called when all DIO BIO I/O has been completed
 *
 * This drops i_dio_count, lets पूर्णांकerested parties know that a DIO operation
 * has completed, and calculates the resulting वापस code क्रम the operation.
 *
 * It lets the fileप्रणाली know अगर it रेजिस्टरed an पूर्णांकerest earlier via
 * get_block.  Pass the निजी field of the map buffer_head so that
 * fileप्रणालीs can use it to hold additional state between get_block calls and
 * dio_complete.
 */
अटल sमाप_प्रकार dio_complete(काष्ठा dio *dio, sमाप_प्रकार ret, अचिन्हित पूर्णांक flags)
अणु
	loff_t offset = dio->iocb->ki_pos;
	sमाप_प्रकार transferred = 0;
	पूर्णांक err;

	/*
	 * AIO submission can race with bio completion to get here जबतक
	 * expecting to have the last io completed by bio completion.
	 * In that हाल -EIOCBQUEUED is in fact not an error we want
	 * to preserve through this call.
	 */
	अगर (ret == -EIOCBQUEUED)
		ret = 0;

	अगर (dio->result) अणु
		transferred = dio->result;

		/* Check क्रम लघु पढ़ो हाल */
		अगर ((dio->op == REQ_OP_READ) &&
		    ((offset + transferred) > dio->i_size))
			transferred = dio->i_size - offset;
		/* ignore EFAULT अगर some IO has been करोne */
		अगर (unlikely(ret == -EFAULT) && transferred)
			ret = 0;
	पूर्ण

	अगर (ret == 0)
		ret = dio->page_errors;
	अगर (ret == 0)
		ret = dio->io_error;
	अगर (ret == 0)
		ret = transferred;

	अगर (dio->end_io) अणु
		// XXX: ki_pos??
		err = dio->end_io(dio->iocb, offset, ret, dio->निजी);
		अगर (err)
			ret = err;
	पूर्ण

	/*
	 * Try again to invalidate clean pages which might have been cached by
	 * non-direct पढ़ोahead, or faulted in by get_user_pages() अगर the source
	 * of the ग_लिखो was an mmap'ed region of the file we're writing.  Either
	 * one is a pretty crazy thing to करो, so we करोn't support it 100%.  If
	 * this invalidation fails, tough, the ग_लिखो still worked...
	 *
	 * And this page cache invalidation has to be after dio->end_io(), as
	 * some fileप्रणालीs convert unwritten extents to real allocations in
	 * end_io() when necessary, otherwise a racing buffer पढ़ो would cache
	 * zeros from unwritten extents.
	 */
	अगर (flags & DIO_COMPLETE_INVALIDATE &&
	    ret > 0 && dio->op == REQ_OP_WRITE &&
	    dio->inode->i_mapping->nrpages) अणु
		err = invalidate_inode_pages2_range(dio->inode->i_mapping,
					offset >> PAGE_SHIFT,
					(offset + ret - 1) >> PAGE_SHIFT);
		अगर (err)
			dio_warn_stale_pagecache(dio->iocb->ki_filp);
	पूर्ण

	inode_dio_end(dio->inode);

	अगर (flags & DIO_COMPLETE_ASYNC) अणु
		/*
		 * generic_ग_लिखो_sync expects ki_pos to have been updated
		 * alपढ़ोy, but the submission path only करोes this क्रम
		 * synchronous I/O.
		 */
		dio->iocb->ki_pos += transferred;

		अगर (ret > 0 && dio->op == REQ_OP_WRITE)
			ret = generic_ग_लिखो_sync(dio->iocb, ret);
		dio->iocb->ki_complete(dio->iocb, ret, 0);
	पूर्ण

	kmem_cache_मुक्त(dio_cache, dio);
	वापस ret;
पूर्ण

अटल व्योम dio_aio_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dio *dio = container_of(work, काष्ठा dio, complete_work);

	dio_complete(dio, 0, DIO_COMPLETE_ASYNC | DIO_COMPLETE_INVALIDATE);
पूर्ण

अटल blk_status_t dio_bio_complete(काष्ठा dio *dio, काष्ठा bio *bio);

/*
 * Asynchronous IO callback. 
 */
अटल व्योम dio_bio_end_aio(काष्ठा bio *bio)
अणु
	काष्ठा dio *dio = bio->bi_निजी;
	अचिन्हित दीर्घ reमुख्यing;
	अचिन्हित दीर्घ flags;
	bool defer_completion = false;

	/* cleanup the bio */
	dio_bio_complete(dio, bio);

	spin_lock_irqsave(&dio->bio_lock, flags);
	reमुख्यing = --dio->refcount;
	अगर (reमुख्यing == 1 && dio->रुकोer)
		wake_up_process(dio->रुकोer);
	spin_unlock_irqrestore(&dio->bio_lock, flags);

	अगर (reमुख्यing == 0) अणु
		/*
		 * Defer completion when defer_completion is set or
		 * when the inode has pages mapped and this is AIO ग_लिखो.
		 * We need to invalidate those pages because there is a
		 * chance they contain stale data in the हाल buffered IO
		 * went in between AIO submission and completion पूर्णांकo the
		 * same region.
		 */
		अगर (dio->result)
			defer_completion = dio->defer_completion ||
					   (dio->op == REQ_OP_WRITE &&
					    dio->inode->i_mapping->nrpages);
		अगर (defer_completion) अणु
			INIT_WORK(&dio->complete_work, dio_aio_complete_work);
			queue_work(dio->inode->i_sb->s_dio_करोne_wq,
				   &dio->complete_work);
		पूर्ण अन्यथा अणु
			dio_complete(dio, 0, DIO_COMPLETE_ASYNC);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * The BIO completion handler simply queues the BIO up क्रम the process-context
 * handler.
 *
 * During I/O bi_निजी poपूर्णांकs at the dio.  After I/O, bi_निजी is used to
 * implement a singly-linked list of completed BIOs, at dio->bio_list.
 */
अटल व्योम dio_bio_end_io(काष्ठा bio *bio)
अणु
	काष्ठा dio *dio = bio->bi_निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dio->bio_lock, flags);
	bio->bi_निजी = dio->bio_list;
	dio->bio_list = bio;
	अगर (--dio->refcount == 1 && dio->रुकोer)
		wake_up_process(dio->रुकोer);
	spin_unlock_irqrestore(&dio->bio_lock, flags);
पूर्ण

अटल अंतरभूत व्योम
dio_bio_alloc(काष्ठा dio *dio, काष्ठा dio_submit *sdio,
	      काष्ठा block_device *bdev,
	      sector_t first_sector, पूर्णांक nr_vecs)
अणु
	काष्ठा bio *bio;

	/*
	 * bio_alloc() is guaranteed to वापस a bio when allowed to sleep and
	 * we request a valid number of vectors.
	 */
	bio = bio_alloc(GFP_KERNEL, nr_vecs);

	bio_set_dev(bio, bdev);
	bio->bi_iter.bi_sector = first_sector;
	bio_set_op_attrs(bio, dio->op, dio->op_flags);
	अगर (dio->is_async)
		bio->bi_end_io = dio_bio_end_aio;
	अन्यथा
		bio->bi_end_io = dio_bio_end_io;

	bio->bi_ग_लिखो_hपूर्णांक = dio->iocb->ki_hपूर्णांक;

	sdio->bio = bio;
	sdio->logical_offset_in_bio = sdio->cur_page_fs_offset;
पूर्ण

/*
 * In the AIO पढ़ो हाल we speculatively dirty the pages beक्रमe starting IO.
 * During IO completion, any of these pages which happen to have been written
 * back will be redirtied by bio_check_pages_dirty().
 *
 * bios hold a dio reference between submit_bio and ->end_io.
 */
अटल अंतरभूत व्योम dio_bio_submit(काष्ठा dio *dio, काष्ठा dio_submit *sdio)
अणु
	काष्ठा bio *bio = sdio->bio;
	अचिन्हित दीर्घ flags;

	bio->bi_निजी = dio;
	/* करोn't account direct I/O as memory stall */
	bio_clear_flag(bio, BIO_WORKINGSET);

	spin_lock_irqsave(&dio->bio_lock, flags);
	dio->refcount++;
	spin_unlock_irqrestore(&dio->bio_lock, flags);

	अगर (dio->is_async && dio->op == REQ_OP_READ && dio->should_dirty)
		bio_set_pages_dirty(bio);

	dio->bio_disk = bio->bi_bdev->bd_disk;

	अगर (sdio->submit_io) अणु
		sdio->submit_io(bio, dio->inode, sdio->logical_offset_in_bio);
		dio->bio_cookie = BLK_QC_T_NONE;
	पूर्ण अन्यथा
		dio->bio_cookie = submit_bio(bio);

	sdio->bio = शून्य;
	sdio->boundary = 0;
	sdio->logical_offset_in_bio = 0;
पूर्ण

/*
 * Release any resources in हाल of a failure
 */
अटल अंतरभूत व्योम dio_cleanup(काष्ठा dio *dio, काष्ठा dio_submit *sdio)
अणु
	जबतक (sdio->head < sdio->tail)
		put_page(dio->pages[sdio->head++]);
पूर्ण

/*
 * Wait क्रम the next BIO to complete.  Remove it and वापस it.  शून्य is
 * वापसed once all BIOs have been completed.  This must only be called once
 * all bios have been issued so that dio->refcount can only decrease.  This
 * requires that the caller hold a reference on the dio.
 */
अटल काष्ठा bio *dio_aरुको_one(काष्ठा dio *dio)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा bio *bio = शून्य;

	spin_lock_irqsave(&dio->bio_lock, flags);

	/*
	 * Wait as दीर्घ as the list is empty and there are bios in flight.  bio
	 * completion drops the count, maybe adds to the list, and wakes जबतक
	 * holding the bio_lock so we करोn't need set_current_state()'s barrier
	 * and can call it after testing our condition.
	 */
	जबतक (dio->refcount > 1 && dio->bio_list == शून्य) अणु
		__set_current_state(TASK_UNINTERRUPTIBLE);
		dio->रुकोer = current;
		spin_unlock_irqrestore(&dio->bio_lock, flags);
		अगर (!(dio->iocb->ki_flags & IOCB_HIPRI) ||
		    !blk_poll(dio->bio_disk->queue, dio->bio_cookie, true))
			blk_io_schedule();
		/* wake up sets us TASK_RUNNING */
		spin_lock_irqsave(&dio->bio_lock, flags);
		dio->रुकोer = शून्य;
	पूर्ण
	अगर (dio->bio_list) अणु
		bio = dio->bio_list;
		dio->bio_list = bio->bi_निजी;
	पूर्ण
	spin_unlock_irqrestore(&dio->bio_lock, flags);
	वापस bio;
पूर्ण

/*
 * Process one completed BIO.  No locks are held.
 */
अटल blk_status_t dio_bio_complete(काष्ठा dio *dio, काष्ठा bio *bio)
अणु
	blk_status_t err = bio->bi_status;
	bool should_dirty = dio->op == REQ_OP_READ && dio->should_dirty;

	अगर (err) अणु
		अगर (err == BLK_STS_AGAIN && (bio->bi_opf & REQ_NOWAIT))
			dio->io_error = -EAGAIN;
		अन्यथा
			dio->io_error = -EIO;
	पूर्ण

	अगर (dio->is_async && should_dirty) अणु
		bio_check_pages_dirty(bio);	/* transfers ownership */
	पूर्ण अन्यथा अणु
		bio_release_pages(bio, should_dirty);
		bio_put(bio);
	पूर्ण
	वापस err;
पूर्ण

/*
 * Wait on and process all in-flight BIOs.  This must only be called once
 * all bios have been issued so that the refcount can only decrease.
 * This just रुकोs क्रम all bios to make it through dio_bio_complete.  IO
 * errors are propagated through dio->io_error and should be propagated via
 * dio_complete().
 */
अटल व्योम dio_aरुको_completion(काष्ठा dio *dio)
अणु
	काष्ठा bio *bio;
	करो अणु
		bio = dio_aरुको_one(dio);
		अगर (bio)
			dio_bio_complete(dio, bio);
	पूर्ण जबतक (bio);
पूर्ण

/*
 * A really large O_सूचीECT पढ़ो or ग_लिखो can generate a lot of BIOs.  So
 * to keep the memory consumption sane we periodically reap any completed BIOs
 * during the BIO generation phase.
 *
 * This also helps to limit the peak amount of pinned userspace memory.
 */
अटल अंतरभूत पूर्णांक dio_bio_reap(काष्ठा dio *dio, काष्ठा dio_submit *sdio)
अणु
	पूर्णांक ret = 0;

	अगर (sdio->reap_counter++ >= 64) अणु
		जबतक (dio->bio_list) अणु
			अचिन्हित दीर्घ flags;
			काष्ठा bio *bio;
			पूर्णांक ret2;

			spin_lock_irqsave(&dio->bio_lock, flags);
			bio = dio->bio_list;
			dio->bio_list = bio->bi_निजी;
			spin_unlock_irqrestore(&dio->bio_lock, flags);
			ret2 = blk_status_to_त्रुटि_सं(dio_bio_complete(dio, bio));
			अगर (ret == 0)
				ret = ret2;
		पूर्ण
		sdio->reap_counter = 0;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Create workqueue क्रम deferred direct IO completions. We allocate the
 * workqueue when it's first needed. This aव्योमs creating workqueue क्रम
 * fileप्रणालीs that करोn't need it and also allows us to create the workqueue
 * late enough so the we can include s_id in the name of the workqueue.
 */
पूर्णांक sb_init_dio_करोne_wq(काष्ठा super_block *sb)
अणु
	काष्ठा workqueue_काष्ठा *old;
	काष्ठा workqueue_काष्ठा *wq = alloc_workqueue("dio/%s",
						      WQ_MEM_RECLAIM, 0,
						      sb->s_id);
	अगर (!wq)
		वापस -ENOMEM;
	/*
	 * This has to be atomic as more DIOs can race to create the workqueue
	 */
	old = cmpxchg(&sb->s_dio_करोne_wq, शून्य, wq);
	/* Someone created workqueue beक्रमe us? Free ours... */
	अगर (old)
		destroy_workqueue(wq);
	वापस 0;
पूर्ण

अटल पूर्णांक dio_set_defer_completion(काष्ठा dio *dio)
अणु
	काष्ठा super_block *sb = dio->inode->i_sb;

	अगर (dio->defer_completion)
		वापस 0;
	dio->defer_completion = true;
	अगर (!sb->s_dio_करोne_wq)
		वापस sb_init_dio_करोne_wq(sb);
	वापस 0;
पूर्ण

/*
 * Call पूर्णांकo the fs to map some more disk blocks.  We record the current number
 * of available blocks at sdio->blocks_available.  These are in units of the
 * fs blocksize, i_blocksize(inode).
 *
 * The fs is allowed to map lots of blocks at once.  If it wants to करो that,
 * it uses the passed inode-relative block number as the file offset, as usual.
 *
 * get_block() is passed the number of i_blkbits-sized blocks which direct_io
 * has reमुख्यing to करो.  The fs should not map more than this number of blocks.
 *
 * If the fs has mapped a lot of blocks, it should populate bh->b_size to
 * indicate how much contiguous disk space has been made available at
 * bh->b_blocknr.
 *
 * If *any* of the mapped blocks are new, then the fs must set buffer_new().
 * This isn't very efficient...
 *
 * In the हाल of fileप्रणाली holes: the fs may वापस an arbitrarily-large
 * hole by वापसing an appropriate value in b_size and by clearing
 * buffer_mapped().  However the direct-io code will only process holes one
 * block at a समय - it will repeatedly call get_block() as it walks the hole.
 */
अटल पूर्णांक get_more_blocks(काष्ठा dio *dio, काष्ठा dio_submit *sdio,
			   काष्ठा buffer_head *map_bh)
अणु
	पूर्णांक ret;
	sector_t fs_startblk;	/* Into file, in fileप्रणाली-sized blocks */
	sector_t fs_endblk;	/* Into file, in fileप्रणाली-sized blocks */
	अचिन्हित दीर्घ fs_count;	/* Number of fileप्रणाली-sized blocks */
	पूर्णांक create;
	अचिन्हित पूर्णांक i_blkbits = sdio->blkbits + sdio->blkfactor;
	loff_t i_size;

	/*
	 * If there was a memory error and we've overwritten all the
	 * mapped blocks then we can now वापस that memory error
	 */
	ret = dio->page_errors;
	अगर (ret == 0) अणु
		BUG_ON(sdio->block_in_file >= sdio->final_block_in_request);
		fs_startblk = sdio->block_in_file >> sdio->blkfactor;
		fs_endblk = (sdio->final_block_in_request - 1) >>
					sdio->blkfactor;
		fs_count = fs_endblk - fs_startblk + 1;

		map_bh->b_state = 0;
		map_bh->b_size = fs_count << i_blkbits;

		/*
		 * For ग_लिखोs that could fill holes inside i_size on a
		 * DIO_SKIP_HOLES fileप्रणाली we क्रमbid block creations: only
		 * overग_लिखोs are permitted. We will वापस early to the caller
		 * once we see an unmapped buffer head वापसed, and the caller
		 * will fall back to buffered I/O.
		 *
		 * Otherwise the decision is left to the get_blocks method,
		 * which may decide to handle it or also वापस an unmapped
		 * buffer head.
		 */
		create = dio->op == REQ_OP_WRITE;
		अगर (dio->flags & DIO_SKIP_HOLES) अणु
			i_size = i_size_पढ़ो(dio->inode);
			अगर (i_size && fs_startblk <= (i_size - 1) >> i_blkbits)
				create = 0;
		पूर्ण

		ret = (*sdio->get_block)(dio->inode, fs_startblk,
						map_bh, create);

		/* Store क्रम completion */
		dio->निजी = map_bh->b_निजी;

		अगर (ret == 0 && buffer_defer_completion(map_bh))
			ret = dio_set_defer_completion(dio);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * There is no bio.  Make one now.
 */
अटल अंतरभूत पूर्णांक dio_new_bio(काष्ठा dio *dio, काष्ठा dio_submit *sdio,
		sector_t start_sector, काष्ठा buffer_head *map_bh)
अणु
	sector_t sector;
	पूर्णांक ret, nr_pages;

	ret = dio_bio_reap(dio, sdio);
	अगर (ret)
		जाओ out;
	sector = start_sector << (sdio->blkbits - 9);
	nr_pages = bio_max_segs(sdio->pages_in_io);
	BUG_ON(nr_pages <= 0);
	dio_bio_alloc(dio, sdio, map_bh->b_bdev, sector, nr_pages);
	sdio->boundary = 0;
out:
	वापस ret;
पूर्ण

/*
 * Attempt to put the current chunk of 'cur_page' पूर्णांकo the current BIO.  If
 * that was successful then update final_block_in_bio and take a ref against
 * the just-added page.
 *
 * Return zero on success.  Non-zero means the caller needs to start a new BIO.
 */
अटल अंतरभूत पूर्णांक dio_bio_add_page(काष्ठा dio_submit *sdio)
अणु
	पूर्णांक ret;

	ret = bio_add_page(sdio->bio, sdio->cur_page,
			sdio->cur_page_len, sdio->cur_page_offset);
	अगर (ret == sdio->cur_page_len) अणु
		/*
		 * Decrement count only, अगर we are करोne with this page
		 */
		अगर ((sdio->cur_page_len + sdio->cur_page_offset) == PAGE_SIZE)
			sdio->pages_in_io--;
		get_page(sdio->cur_page);
		sdio->final_block_in_bio = sdio->cur_page_block +
			(sdio->cur_page_len >> sdio->blkbits);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = 1;
	पूर्ण
	वापस ret;
पूर्ण
		
/*
 * Put cur_page under IO.  The section of cur_page which is described by
 * cur_page_offset,cur_page_len is put पूर्णांकo a BIO.  The section of cur_page
 * starts on-disk at cur_page_block.
 *
 * We take a ref against the page here (on behalf of its presence in the bio).
 *
 * The caller of this function is responsible क्रम removing cur_page from the
 * dio, and क्रम dropping the refcount which came from that presence.
 */
अटल अंतरभूत पूर्णांक dio_send_cur_page(काष्ठा dio *dio, काष्ठा dio_submit *sdio,
		काष्ठा buffer_head *map_bh)
अणु
	पूर्णांक ret = 0;

	अगर (sdio->bio) अणु
		loff_t cur_offset = sdio->cur_page_fs_offset;
		loff_t bio_next_offset = sdio->logical_offset_in_bio +
			sdio->bio->bi_iter.bi_size;

		/*
		 * See whether this new request is contiguous with the old.
		 *
		 * Btrfs cannot handle having logically non-contiguous requests
		 * submitted.  For example अगर you have
		 *
		 * Logical:  [0-4095][HOLE][8192-12287]
		 * Physical: [0-4095]      [4096-8191]
		 *
		 * We cannot submit those pages together as one BIO.  So अगर our
		 * current logical offset in the file करोes not equal what would
		 * be the next logical offset in the bio, submit the bio we
		 * have.
		 */
		अगर (sdio->final_block_in_bio != sdio->cur_page_block ||
		    cur_offset != bio_next_offset)
			dio_bio_submit(dio, sdio);
	पूर्ण

	अगर (sdio->bio == शून्य) अणु
		ret = dio_new_bio(dio, sdio, sdio->cur_page_block, map_bh);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (dio_bio_add_page(sdio) != 0) अणु
		dio_bio_submit(dio, sdio);
		ret = dio_new_bio(dio, sdio, sdio->cur_page_block, map_bh);
		अगर (ret == 0) अणु
			ret = dio_bio_add_page(sdio);
			BUG_ON(ret != 0);
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * An स्वतःnomous function to put a chunk of a page under deferred IO.
 *
 * The caller करोesn't actually know (or care) whether this piece of page is in
 * a BIO, or is under IO or whatever.  We just take care of all possible 
 * situations here.  The separation between the logic of करो_direct_IO() and
 * that of submit_page_section() is important क्रम clarity.  Please करोn't अवरोध.
 *
 * The chunk of page starts on-disk at blocknr.
 *
 * We perक्रमm deferred IO, by recording the last-submitted page inside our
 * निजी part of the dio काष्ठाure.  If possible, we just expand the IO
 * across that page here.
 *
 * If that करोesn't work out then we put the old page पूर्णांकo the bio and add this
 * page to the dio instead.
 */
अटल अंतरभूत पूर्णांक
submit_page_section(काष्ठा dio *dio, काष्ठा dio_submit *sdio, काष्ठा page *page,
		    अचिन्हित offset, अचिन्हित len, sector_t blocknr,
		    काष्ठा buffer_head *map_bh)
अणु
	पूर्णांक ret = 0;
	पूर्णांक boundary = sdio->boundary;	/* dio_send_cur_page may clear it */

	अगर (dio->op == REQ_OP_WRITE) अणु
		/*
		 * Read accounting is perक्रमmed in submit_bio()
		 */
		task_io_account_ग_लिखो(len);
	पूर्ण

	/*
	 * Can we just grow the current page's presence in the dio?
	 */
	अगर (sdio->cur_page == page &&
	    sdio->cur_page_offset + sdio->cur_page_len == offset &&
	    sdio->cur_page_block +
	    (sdio->cur_page_len >> sdio->blkbits) == blocknr) अणु
		sdio->cur_page_len += len;
		जाओ out;
	पूर्ण

	/*
	 * If there's a deferred page alपढ़ोy there then send it.
	 */
	अगर (sdio->cur_page) अणु
		ret = dio_send_cur_page(dio, sdio, map_bh);
		put_page(sdio->cur_page);
		sdio->cur_page = शून्य;
		अगर (ret)
			वापस ret;
	पूर्ण

	get_page(page);		/* It is in dio */
	sdio->cur_page = page;
	sdio->cur_page_offset = offset;
	sdio->cur_page_len = len;
	sdio->cur_page_block = blocknr;
	sdio->cur_page_fs_offset = sdio->block_in_file << sdio->blkbits;
out:
	/*
	 * If boundary then we want to schedule the IO now to
	 * aव्योम metadata seeks.
	 */
	अगर (boundary) अणु
		ret = dio_send_cur_page(dio, sdio, map_bh);
		अगर (sdio->bio)
			dio_bio_submit(dio, sdio);
		put_page(sdio->cur_page);
		sdio->cur_page = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * If we are not writing the entire block and get_block() allocated
 * the block क्रम us, we need to fill-in the unused portion of the
 * block with zeros. This happens only अगर user-buffer, fileoffset or
 * io length is not fileप्रणाली block-size multiple.
 *
 * `end' is zero if we're करोing the start of the IO, 1 at the end of the
 * IO.
 */
अटल अंतरभूत व्योम dio_zero_block(काष्ठा dio *dio, काष्ठा dio_submit *sdio,
		पूर्णांक end, काष्ठा buffer_head *map_bh)
अणु
	अचिन्हित dio_blocks_per_fs_block;
	अचिन्हित this_chunk_blocks;	/* In dio_blocks */
	अचिन्हित this_chunk_bytes;
	काष्ठा page *page;

	sdio->start_zero_करोne = 1;
	अगर (!sdio->blkfactor || !buffer_new(map_bh))
		वापस;

	dio_blocks_per_fs_block = 1 << sdio->blkfactor;
	this_chunk_blocks = sdio->block_in_file & (dio_blocks_per_fs_block - 1);

	अगर (!this_chunk_blocks)
		वापस;

	/*
	 * We need to zero out part of an fs block.  It is either at the
	 * beginning or the end of the fs block.
	 */
	अगर (end) 
		this_chunk_blocks = dio_blocks_per_fs_block - this_chunk_blocks;

	this_chunk_bytes = this_chunk_blocks << sdio->blkbits;

	page = ZERO_PAGE(0);
	अगर (submit_page_section(dio, sdio, page, 0, this_chunk_bytes,
				sdio->next_block_क्रम_io, map_bh))
		वापस;

	sdio->next_block_क्रम_io += this_chunk_blocks;
पूर्ण

/*
 * Walk the user pages, and the file, mapping blocks to disk and generating
 * a sequence of (page,offset,len,block) mappings.  These mappings are injected
 * पूर्णांकo submit_page_section(), which takes care of the next stage of submission
 *
 * Direct IO against a blockdev is dअगरferent from a file.  Because we can
 * happily perक्रमm page-sized but 512-byte aligned IOs.  It is important that
 * blockdev IO be able to have fine alignment and large sizes.
 *
 * So what we करो is to permit the ->get_block function to populate bh.b_size
 * with the size of IO which is permitted at this offset and this i_blkbits.
 *
 * For best results, the blockdev should be set up with 512-byte i_blkbits and
 * it should set b_size to PAGE_SIZE or more inside get_block().  This gives
 * fine alignment but still allows this function to work in PAGE_SIZE units.
 */
अटल पूर्णांक करो_direct_IO(काष्ठा dio *dio, काष्ठा dio_submit *sdio,
			काष्ठा buffer_head *map_bh)
अणु
	स्थिर अचिन्हित blkbits = sdio->blkbits;
	स्थिर अचिन्हित i_blkbits = blkbits + sdio->blkfactor;
	पूर्णांक ret = 0;

	जबतक (sdio->block_in_file < sdio->final_block_in_request) अणु
		काष्ठा page *page;
		माप_प्रकार from, to;

		page = dio_get_page(dio, sdio);
		अगर (IS_ERR(page)) अणु
			ret = PTR_ERR(page);
			जाओ out;
		पूर्ण
		from = sdio->head ? 0 : sdio->from;
		to = (sdio->head == sdio->tail - 1) ? sdio->to : PAGE_SIZE;
		sdio->head++;

		जबतक (from < to) अणु
			अचिन्हित this_chunk_bytes;	/* # of bytes mapped */
			अचिन्हित this_chunk_blocks;	/* # of blocks */
			अचिन्हित u;

			अगर (sdio->blocks_available == 0) अणु
				/*
				 * Need to go and map some more disk
				 */
				अचिन्हित दीर्घ blkmask;
				अचिन्हित दीर्घ dio_reमुख्यder;

				ret = get_more_blocks(dio, sdio, map_bh);
				अगर (ret) अणु
					put_page(page);
					जाओ out;
				पूर्ण
				अगर (!buffer_mapped(map_bh))
					जाओ करो_holes;

				sdio->blocks_available =
						map_bh->b_size >> blkbits;
				sdio->next_block_क्रम_io =
					map_bh->b_blocknr << sdio->blkfactor;
				अगर (buffer_new(map_bh)) अणु
					clean_bdev_aliases(
						map_bh->b_bdev,
						map_bh->b_blocknr,
						map_bh->b_size >> i_blkbits);
				पूर्ण

				अगर (!sdio->blkfactor)
					जाओ करो_holes;

				blkmask = (1 << sdio->blkfactor) - 1;
				dio_reमुख्यder = (sdio->block_in_file & blkmask);

				/*
				 * If we are at the start of IO and that IO
				 * starts partway पूर्णांकo a fs-block,
				 * dio_reमुख्यder will be non-zero.  If the IO
				 * is a पढ़ो then we can simply advance the IO
				 * cursor to the first block which is to be
				 * पढ़ो.  But अगर the IO is a ग_लिखो and the
				 * block was newly allocated we cannot करो that;
				 * the start of the fs block must be zeroed out
				 * on-disk
				 */
				अगर (!buffer_new(map_bh))
					sdio->next_block_क्रम_io += dio_reमुख्यder;
				sdio->blocks_available -= dio_reमुख्यder;
			पूर्ण
करो_holes:
			/* Handle holes */
			अगर (!buffer_mapped(map_bh)) अणु
				loff_t i_size_aligned;

				/* AKPM: eargh, -ENOTBLK is a hack */
				अगर (dio->op == REQ_OP_WRITE) अणु
					put_page(page);
					वापस -ENOTBLK;
				पूर्ण

				/*
				 * Be sure to account क्रम a partial block as the
				 * last block in the file
				 */
				i_size_aligned = ALIGN(i_size_पढ़ो(dio->inode),
							1 << blkbits);
				अगर (sdio->block_in_file >=
						i_size_aligned >> blkbits) अणु
					/* We hit eof */
					put_page(page);
					जाओ out;
				पूर्ण
				zero_user(page, from, 1 << blkbits);
				sdio->block_in_file++;
				from += 1 << blkbits;
				dio->result += 1 << blkbits;
				जाओ next_block;
			पूर्ण

			/*
			 * If we're perक्रमming IO which has an alignment which
			 * is finer than the underlying fs, go check to see अगर
			 * we must zero out the start of this block.
			 */
			अगर (unlikely(sdio->blkfactor && !sdio->start_zero_करोne))
				dio_zero_block(dio, sdio, 0, map_bh);

			/*
			 * Work out, in this_chunk_blocks, how much disk we
			 * can add to this page
			 */
			this_chunk_blocks = sdio->blocks_available;
			u = (to - from) >> blkbits;
			अगर (this_chunk_blocks > u)
				this_chunk_blocks = u;
			u = sdio->final_block_in_request - sdio->block_in_file;
			अगर (this_chunk_blocks > u)
				this_chunk_blocks = u;
			this_chunk_bytes = this_chunk_blocks << blkbits;
			BUG_ON(this_chunk_bytes == 0);

			अगर (this_chunk_blocks == sdio->blocks_available)
				sdio->boundary = buffer_boundary(map_bh);
			ret = submit_page_section(dio, sdio, page,
						  from,
						  this_chunk_bytes,
						  sdio->next_block_क्रम_io,
						  map_bh);
			अगर (ret) अणु
				put_page(page);
				जाओ out;
			पूर्ण
			sdio->next_block_क्रम_io += this_chunk_blocks;

			sdio->block_in_file += this_chunk_blocks;
			from += this_chunk_bytes;
			dio->result += this_chunk_bytes;
			sdio->blocks_available -= this_chunk_blocks;
next_block:
			BUG_ON(sdio->block_in_file > sdio->final_block_in_request);
			अगर (sdio->block_in_file == sdio->final_block_in_request)
				अवरोध;
		पूर्ण

		/* Drop the ref which was taken in get_user_pages() */
		put_page(page);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drop_refcount(काष्ठा dio *dio)
अणु
	पूर्णांक ret2;
	अचिन्हित दीर्घ flags;

	/*
	 * Sync will always be dropping the final ref and completing the
	 * operation.  AIO can अगर it was a broken operation described above or
	 * in fact अगर all the bios race to complete beक्रमe we get here.  In
	 * that हाल dio_complete() translates the EIOCBQUEUED पूर्णांकo the proper
	 * वापस code that the caller will hand to ->complete().
	 *
	 * This is managed by the bio_lock instead of being an atomic_t so that
	 * completion paths can drop their ref and use the reमुख्यing count to
	 * decide to wake the submission path atomically.
	 */
	spin_lock_irqsave(&dio->bio_lock, flags);
	ret2 = --dio->refcount;
	spin_unlock_irqrestore(&dio->bio_lock, flags);
	वापस ret2;
पूर्ण

/*
 * This is a library function क्रम use by fileप्रणाली drivers.
 *
 * The locking rules are governed by the flags parameter:
 *  - अगर the flags value contains DIO_LOCKING we use a fancy locking
 *    scheme क्रम dumb fileप्रणालीs.
 *    For ग_लिखोs this function is called under i_mutex and वापसs with
 *    i_mutex held, क्रम पढ़ोs, i_mutex is not held on entry, but it is
 *    taken and dropped again beक्रमe वापसing.
 *  - अगर the flags value करोes NOT contain DIO_LOCKING we करोn't use any
 *    पूर्णांकernal locking but rather rely on the fileप्रणाली to synchronize
 *    direct I/O पढ़ोs/ग_लिखोs versus each other and truncate.
 *
 * To help with locking against truncate we incremented the i_dio_count
 * counter beक्रमe starting direct I/O, and decrement it once we are करोne.
 * Truncate can रुको क्रम it to reach zero to provide exclusion.  It is
 * expected that fileप्रणाली provide exclusion between new direct I/O
 * and truncates.  For DIO_LOCKING fileप्रणालीs this is करोne by i_mutex,
 * but other fileप्रणालीs need to take care of this on their own.
 *
 * NOTE: अगर you pass "sdio" to anything by poपूर्णांकer make sure that function
 * is always अंतरभूतd. Otherwise gcc is unable to split the काष्ठाure पूर्णांकo
 * inभागidual fields and will generate much worse code. This is important
 * क्रम the whole file.
 */
अटल अंतरभूत sमाप_प्रकार
करो_blockdev_direct_IO(काष्ठा kiocb *iocb, काष्ठा inode *inode,
		      काष्ठा block_device *bdev, काष्ठा iov_iter *iter,
		      get_block_t get_block, dio_ioकरोne_t end_io,
		      dio_submit_t submit_io, पूर्णांक flags)
अणु
	अचिन्हित i_blkbits = READ_ONCE(inode->i_blkbits);
	अचिन्हित blkbits = i_blkbits;
	अचिन्हित blocksize_mask = (1 << blkbits) - 1;
	sमाप_प्रकार retval = -EINVAL;
	स्थिर माप_प्रकार count = iov_iter_count(iter);
	loff_t offset = iocb->ki_pos;
	स्थिर loff_t end = offset + count;
	काष्ठा dio *dio;
	काष्ठा dio_submit sdio = अणु 0, पूर्ण;
	काष्ठा buffer_head map_bh = अणु 0, पूर्ण;
	काष्ठा blk_plug plug;
	अचिन्हित दीर्घ align = offset | iov_iter_alignment(iter);

	/*
	 * Aव्योम references to bdev अगर not असलolutely needed to give
	 * the early prefetch in the caller enough समय.
	 */

	/* watch out क्रम a 0 len io from a tricksy fs */
	अगर (iov_iter_rw(iter) == READ && !count)
		वापस 0;

	dio = kmem_cache_alloc(dio_cache, GFP_KERNEL);
	अगर (!dio)
		वापस -ENOMEM;
	/*
	 * Believe it or not, zeroing out the page array caused a .5%
	 * perक्रमmance regression in a database benchmark.  So, we take
	 * care to only zero out what's needed.
	 */
	स_रखो(dio, 0, दुरत्व(काष्ठा dio, pages));

	dio->flags = flags;
	अगर (dio->flags & DIO_LOCKING && iov_iter_rw(iter) == READ) अणु
		/* will be released by direct_io_worker */
		inode_lock(inode);
	पूर्ण

	/* Once we sampled i_size check क्रम पढ़ोs beyond खातापूर्ण */
	dio->i_size = i_size_पढ़ो(inode);
	अगर (iov_iter_rw(iter) == READ && offset >= dio->i_size) अणु
		retval = 0;
		जाओ fail_dio;
	पूर्ण

	अगर (align & blocksize_mask) अणु
		अगर (bdev)
			blkbits = blksize_bits(bdev_logical_block_size(bdev));
		blocksize_mask = (1 << blkbits) - 1;
		अगर (align & blocksize_mask)
			जाओ fail_dio;
	पूर्ण

	अगर (dio->flags & DIO_LOCKING && iov_iter_rw(iter) == READ) अणु
		काष्ठा address_space *mapping = iocb->ki_filp->f_mapping;

		retval = filemap_ग_लिखो_and_रुको_range(mapping, offset, end - 1);
		अगर (retval)
			जाओ fail_dio;
	पूर्ण

	/*
	 * For file extending ग_लिखोs updating i_size beक्रमe data ग_लिखोouts
	 * complete can expose uninitialized blocks in dumb fileप्रणालीs.
	 * In that हाल we need to रुको क्रम I/O completion even अगर asked
	 * क्रम an asynchronous ग_लिखो.
	 */
	अगर (is_sync_kiocb(iocb))
		dio->is_async = false;
	अन्यथा अगर (iov_iter_rw(iter) == WRITE && end > i_size_पढ़ो(inode))
		dio->is_async = false;
	अन्यथा
		dio->is_async = true;

	dio->inode = inode;
	अगर (iov_iter_rw(iter) == WRITE) अणु
		dio->op = REQ_OP_WRITE;
		dio->op_flags = REQ_SYNC | REQ_IDLE;
		अगर (iocb->ki_flags & IOCB_NOWAIT)
			dio->op_flags |= REQ_NOWAIT;
	पूर्ण अन्यथा अणु
		dio->op = REQ_OP_READ;
	पूर्ण
	अगर (iocb->ki_flags & IOCB_HIPRI)
		dio->op_flags |= REQ_HIPRI;

	/*
	 * For AIO O_(D)SYNC ग_लिखोs we need to defer completions to a workqueue
	 * so that we can call ->fsync.
	 */
	अगर (dio->is_async && iov_iter_rw(iter) == WRITE) अणु
		retval = 0;
		अगर (iocb->ki_flags & IOCB_DSYNC)
			retval = dio_set_defer_completion(dio);
		अन्यथा अगर (!dio->inode->i_sb->s_dio_करोne_wq) अणु
			/*
			 * In हाल of AIO ग_लिखो racing with buffered पढ़ो we
			 * need to defer completion. We can't decide this now,
			 * however the workqueue needs to be initialized here.
			 */
			retval = sb_init_dio_करोne_wq(dio->inode->i_sb);
		पूर्ण
		अगर (retval)
			जाओ fail_dio;
	पूर्ण

	/*
	 * Will be decremented at I/O completion समय.
	 */
	inode_dio_begin(inode);

	retval = 0;
	sdio.blkbits = blkbits;
	sdio.blkfactor = i_blkbits - blkbits;
	sdio.block_in_file = offset >> blkbits;

	sdio.get_block = get_block;
	dio->end_io = end_io;
	sdio.submit_io = submit_io;
	sdio.final_block_in_bio = -1;
	sdio.next_block_क्रम_io = -1;

	dio->iocb = iocb;

	spin_lock_init(&dio->bio_lock);
	dio->refcount = 1;

	dio->should_dirty = iter_is_iovec(iter) && iov_iter_rw(iter) == READ;
	sdio.iter = iter;
	sdio.final_block_in_request = end >> blkbits;

	/*
	 * In हाल of non-aligned buffers, we may need 2 more
	 * pages since we need to zero out first and last block.
	 */
	अगर (unlikely(sdio.blkfactor))
		sdio.pages_in_io = 2;

	sdio.pages_in_io += iov_iter_npages(iter, पूर्णांक_उच्च);

	blk_start_plug(&plug);

	retval = करो_direct_IO(dio, &sdio, &map_bh);
	अगर (retval)
		dio_cleanup(dio, &sdio);

	अगर (retval == -ENOTBLK) अणु
		/*
		 * The reमुख्यing part of the request will be
		 * handled by buffered I/O when we वापस
		 */
		retval = 0;
	पूर्ण
	/*
	 * There may be some unwritten disk at the end of a part-written
	 * fs-block-sized block.  Go zero that now.
	 */
	dio_zero_block(dio, &sdio, 1, &map_bh);

	अगर (sdio.cur_page) अणु
		sमाप_प्रकार ret2;

		ret2 = dio_send_cur_page(dio, &sdio, &map_bh);
		अगर (retval == 0)
			retval = ret2;
		put_page(sdio.cur_page);
		sdio.cur_page = शून्य;
	पूर्ण
	अगर (sdio.bio)
		dio_bio_submit(dio, &sdio);

	blk_finish_plug(&plug);

	/*
	 * It is possible that, we वापस लघु IO due to end of file.
	 * In that हाल, we need to release all the pages we got hold on.
	 */
	dio_cleanup(dio, &sdio);

	/*
	 * All block lookups have been perक्रमmed. For READ requests
	 * we can let i_mutex go now that its achieved its purpose
	 * of protecting us from looking up uninitialized blocks.
	 */
	अगर (iov_iter_rw(iter) == READ && (dio->flags & DIO_LOCKING))
		inode_unlock(dio->inode);

	/*
	 * The only समय we want to leave bios in flight is when a successful
	 * partial aio पढ़ो or full aio ग_लिखो have been setup.  In that हाल
	 * bio completion will call aio_complete.  The only समय it's safe to
	 * call aio_complete is when we वापस -EIOCBQUEUED, so we key on that.
	 * This had *better* be the only place that उठाओs -EIOCBQUEUED.
	 */
	BUG_ON(retval == -EIOCBQUEUED);
	अगर (dio->is_async && retval == 0 && dio->result &&
	    (iov_iter_rw(iter) == READ || dio->result == count))
		retval = -EIOCBQUEUED;
	अन्यथा
		dio_aरुको_completion(dio);

	अगर (drop_refcount(dio) == 0) अणु
		retval = dio_complete(dio, retval, DIO_COMPLETE_INVALIDATE);
	पूर्ण अन्यथा
		BUG_ON(retval != -EIOCBQUEUED);

	वापस retval;

fail_dio:
	अगर (dio->flags & DIO_LOCKING && iov_iter_rw(iter) == READ)
		inode_unlock(inode);

	kmem_cache_मुक्त(dio_cache, dio);
	वापस retval;
पूर्ण

sमाप_प्रकार __blockdev_direct_IO(काष्ठा kiocb *iocb, काष्ठा inode *inode,
			     काष्ठा block_device *bdev, काष्ठा iov_iter *iter,
			     get_block_t get_block,
			     dio_ioकरोne_t end_io, dio_submit_t submit_io,
			     पूर्णांक flags)
अणु
	/*
	 * The block device state is needed in the end to finally
	 * submit everything.  Since it's likely to be cache cold
	 * prefetch it here as first thing to hide some of the
	 * latency.
	 *
	 * Attempt to prefetch the pieces we likely need later.
	 */
	prefetch(&bdev->bd_disk->part_tbl);
	prefetch(bdev->bd_disk->queue);
	prefetch((अक्षर *)bdev->bd_disk->queue + SMP_CACHE_BYTES);

	वापस करो_blockdev_direct_IO(iocb, inode, bdev, iter, get_block,
				     end_io, submit_io, flags);
पूर्ण

EXPORT_SYMBOL(__blockdev_direct_IO);

अटल __init पूर्णांक dio_init(व्योम)
अणु
	dio_cache = KMEM_CACHE(dio, SLAB_PANIC);
	वापस 0;
पूर्ण
module_init(dio_init)
