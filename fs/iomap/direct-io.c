<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 Red Hat, Inc.
 * Copyright (c) 2016-2018 Christoph Hellwig.
 */
#समावेश <linux/module.h>
#समावेश <linux/compiler.h>
#समावेश <linux/fs.h>
#समावेश <linux/iomap.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/uपन.स>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश "trace.h"

#समावेश "../internal.h"

/*
 * Private flags क्रम iomap_dio, must not overlap with the खुला ones in
 * iomap.h:
 */
#घोषणा IOMAP_DIO_WRITE_FUA	(1 << 28)
#घोषणा IOMAP_DIO_NEED_SYNC	(1 << 29)
#घोषणा IOMAP_DIO_WRITE		(1 << 30)
#घोषणा IOMAP_DIO_सूचीTY		(1 << 31)

काष्ठा iomap_dio अणु
	काष्ठा kiocb		*iocb;
	स्थिर काष्ठा iomap_dio_ops *करोps;
	loff_t			i_size;
	loff_t			size;
	atomic_t		ref;
	अचिन्हित		flags;
	पूर्णांक			error;
	bool			रुको_क्रम_completion;

	जोड़ अणु
		/* used during submission and क्रम synchronous completion: */
		काष्ठा अणु
			काष्ठा iov_iter		*iter;
			काष्ठा task_काष्ठा	*रुकोer;
			काष्ठा request_queue	*last_queue;
			blk_qc_t		cookie;
		पूर्ण submit;

		/* used क्रम aio completion: */
		काष्ठा अणु
			काष्ठा work_काष्ठा	work;
		पूर्ण aio;
	पूर्ण;
पूर्ण;

पूर्णांक iomap_dio_iopoll(काष्ठा kiocb *kiocb, bool spin)
अणु
	काष्ठा request_queue *q = READ_ONCE(kiocb->निजी);

	अगर (!q)
		वापस 0;
	वापस blk_poll(q, READ_ONCE(kiocb->ki_cookie), spin);
पूर्ण
EXPORT_SYMBOL_GPL(iomap_dio_iopoll);

अटल व्योम iomap_dio_submit_bio(काष्ठा iomap_dio *dio, काष्ठा iomap *iomap,
		काष्ठा bio *bio, loff_t pos)
अणु
	atomic_inc(&dio->ref);

	अगर (dio->iocb->ki_flags & IOCB_HIPRI)
		bio_set_polled(bio, dio->iocb);

	dio->submit.last_queue = bdev_get_queue(iomap->bdev);
	अगर (dio->करोps && dio->करोps->submit_io)
		dio->submit.cookie = dio->करोps->submit_io(
				file_inode(dio->iocb->ki_filp),
				iomap, bio, pos);
	अन्यथा
		dio->submit.cookie = submit_bio(bio);
पूर्ण

sमाप_प्रकार iomap_dio_complete(काष्ठा iomap_dio *dio)
अणु
	स्थिर काष्ठा iomap_dio_ops *करोps = dio->करोps;
	काष्ठा kiocb *iocb = dio->iocb;
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	loff_t offset = iocb->ki_pos;
	sमाप_प्रकार ret = dio->error;

	अगर (करोps && करोps->end_io)
		ret = करोps->end_io(iocb, dio->size, ret, dio->flags);

	अगर (likely(!ret)) अणु
		ret = dio->size;
		/* check क्रम लघु पढ़ो */
		अगर (offset + ret > dio->i_size &&
		    !(dio->flags & IOMAP_DIO_WRITE))
			ret = dio->i_size - offset;
		iocb->ki_pos += ret;
	पूर्ण

	/*
	 * Try again to invalidate clean pages which might have been cached by
	 * non-direct पढ़ोahead, or faulted in by get_user_pages() अगर the source
	 * of the ग_लिखो was an mmap'ed region of the file we're writing.  Either
	 * one is a pretty crazy thing to करो, so we करोn't support it 100%.  If
	 * this invalidation fails, tough, the ग_लिखो still worked...
	 *
	 * And this page cache invalidation has to be after ->end_io(), as some
	 * fileप्रणालीs convert unwritten extents to real allocations in
	 * ->end_io() when necessary, otherwise a racing buffer पढ़ो would cache
	 * zeros from unwritten extents.
	 */
	अगर (!dio->error && dio->size &&
	    (dio->flags & IOMAP_DIO_WRITE) && inode->i_mapping->nrpages) अणु
		पूर्णांक err;
		err = invalidate_inode_pages2_range(inode->i_mapping,
				offset >> PAGE_SHIFT,
				(offset + dio->size - 1) >> PAGE_SHIFT);
		अगर (err)
			dio_warn_stale_pagecache(iocb->ki_filp);
	पूर्ण

	inode_dio_end(file_inode(iocb->ki_filp));
	/*
	 * If this is a DSYNC ग_लिखो, make sure we push it to stable storage now
	 * that we've written data.
	 */
	अगर (ret > 0 && (dio->flags & IOMAP_DIO_NEED_SYNC))
		ret = generic_ग_लिखो_sync(iocb, ret);

	kमुक्त(dio);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_dio_complete);

अटल व्योम iomap_dio_complete_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iomap_dio *dio = container_of(work, काष्ठा iomap_dio, aio.work);
	काष्ठा kiocb *iocb = dio->iocb;

	iocb->ki_complete(iocb, iomap_dio_complete(dio), 0);
पूर्ण

/*
 * Set an error in the dio अगर none is set yet.  We have to use cmpxchg
 * as the submission context and the completion context(s) can race to
 * update the error.
 */
अटल अंतरभूत व्योम iomap_dio_set_error(काष्ठा iomap_dio *dio, पूर्णांक ret)
अणु
	cmpxchg(&dio->error, 0, ret);
पूर्ण

अटल व्योम iomap_dio_bio_end_io(काष्ठा bio *bio)
अणु
	काष्ठा iomap_dio *dio = bio->bi_निजी;
	bool should_dirty = (dio->flags & IOMAP_DIO_सूचीTY);

	अगर (bio->bi_status)
		iomap_dio_set_error(dio, blk_status_to_त्रुटि_सं(bio->bi_status));

	अगर (atomic_dec_and_test(&dio->ref)) अणु
		अगर (dio->रुको_क्रम_completion) अणु
			काष्ठा task_काष्ठा *रुकोer = dio->submit.रुकोer;
			WRITE_ONCE(dio->submit.रुकोer, शून्य);
			blk_wake_io_task(रुकोer);
		पूर्ण अन्यथा अगर (dio->flags & IOMAP_DIO_WRITE) अणु
			काष्ठा inode *inode = file_inode(dio->iocb->ki_filp);

			INIT_WORK(&dio->aio.work, iomap_dio_complete_work);
			queue_work(inode->i_sb->s_dio_करोne_wq, &dio->aio.work);
		पूर्ण अन्यथा अणु
			iomap_dio_complete_work(&dio->aio.work);
		पूर्ण
	पूर्ण

	अगर (should_dirty) अणु
		bio_check_pages_dirty(bio);
	पूर्ण अन्यथा अणु
		bio_release_pages(bio, false);
		bio_put(bio);
	पूर्ण
पूर्ण

अटल व्योम
iomap_dio_zero(काष्ठा iomap_dio *dio, काष्ठा iomap *iomap, loff_t pos,
		अचिन्हित len)
अणु
	काष्ठा page *page = ZERO_PAGE(0);
	पूर्णांक flags = REQ_SYNC | REQ_IDLE;
	काष्ठा bio *bio;

	bio = bio_alloc(GFP_KERNEL, 1);
	bio_set_dev(bio, iomap->bdev);
	bio->bi_iter.bi_sector = iomap_sector(iomap, pos);
	bio->bi_निजी = dio;
	bio->bi_end_io = iomap_dio_bio_end_io;

	get_page(page);
	__bio_add_page(bio, page, len, 0);
	bio_set_op_attrs(bio, REQ_OP_WRITE, flags);
	iomap_dio_submit_bio(dio, iomap, bio, pos);
पूर्ण

/*
 * Figure out the bio's operation flags from the dio request, the
 * mapping, and whether or not we want FUA.  Note that we can end up
 * clearing the WRITE_FUA flag in the dio request.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
iomap_dio_bio_opflags(काष्ठा iomap_dio *dio, काष्ठा iomap *iomap, bool use_fua)
अणु
	अचिन्हित पूर्णांक opflags = REQ_SYNC | REQ_IDLE;

	अगर (!(dio->flags & IOMAP_DIO_WRITE)) अणु
		WARN_ON_ONCE(iomap->flags & IOMAP_F_ZONE_APPEND);
		वापस REQ_OP_READ;
	पूर्ण

	अगर (iomap->flags & IOMAP_F_ZONE_APPEND)
		opflags |= REQ_OP_ZONE_APPEND;
	अन्यथा
		opflags |= REQ_OP_WRITE;

	अगर (use_fua)
		opflags |= REQ_FUA;
	अन्यथा
		dio->flags &= ~IOMAP_DIO_WRITE_FUA;

	वापस opflags;
पूर्ण

अटल loff_t
iomap_dio_bio_actor(काष्ठा inode *inode, loff_t pos, loff_t length,
		काष्ठा iomap_dio *dio, काष्ठा iomap *iomap)
अणु
	अचिन्हित पूर्णांक blkbits = blksize_bits(bdev_logical_block_size(iomap->bdev));
	अचिन्हित पूर्णांक fs_block_size = i_blocksize(inode), pad;
	अचिन्हित पूर्णांक align = iov_iter_alignment(dio->submit.iter);
	अचिन्हित पूर्णांक bio_opf;
	काष्ठा bio *bio;
	bool need_zeroout = false;
	bool use_fua = false;
	पूर्णांक nr_pages, ret = 0;
	माप_प्रकार copied = 0;
	माप_प्रकार orig_count;

	अगर ((pos | length | align) & ((1 << blkbits) - 1))
		वापस -EINVAL;

	अगर (iomap->type == IOMAP_UNWRITTEN) अणु
		dio->flags |= IOMAP_DIO_UNWRITTEN;
		need_zeroout = true;
	पूर्ण

	अगर (iomap->flags & IOMAP_F_SHARED)
		dio->flags |= IOMAP_DIO_COW;

	अगर (iomap->flags & IOMAP_F_NEW) अणु
		need_zeroout = true;
	पूर्ण अन्यथा अगर (iomap->type == IOMAP_MAPPED) अणु
		/*
		 * Use a FUA ग_लिखो अगर we need datasync semantics, this is a pure
		 * data IO that करोesn't require any metadata updates (including
		 * after IO completion such as unwritten extent conversion) and
		 * the underlying device supports FUA. This allows us to aव्योम
		 * cache flushes on IO completion.
		 */
		अगर (!(iomap->flags & (IOMAP_F_SHARED|IOMAP_F_सूचीTY)) &&
		    (dio->flags & IOMAP_DIO_WRITE_FUA) &&
		    blk_queue_fua(bdev_get_queue(iomap->bdev)))
			use_fua = true;
	पूर्ण

	/*
	 * Save the original count and trim the iter to just the extent we
	 * are operating on right now.  The iter will be re-expanded once
	 * we are करोne.
	 */
	orig_count = iov_iter_count(dio->submit.iter);
	iov_iter_truncate(dio->submit.iter, length);

	अगर (!iov_iter_count(dio->submit.iter))
		जाओ out;

	अगर (need_zeroout) अणु
		/* zero out from the start of the block to the ग_लिखो offset */
		pad = pos & (fs_block_size - 1);
		अगर (pad)
			iomap_dio_zero(dio, iomap, pos - pad, pad);
	पूर्ण

	/*
	 * Set the operation flags early so that bio_iov_iter_get_pages
	 * can set up the page vector appropriately क्रम a ZONE_APPEND
	 * operation.
	 */
	bio_opf = iomap_dio_bio_opflags(dio, iomap, use_fua);

	nr_pages = bio_iov_vecs_to_alloc(dio->submit.iter, BIO_MAX_VECS);
	करो अणु
		माप_प्रकार n;
		अगर (dio->error) अणु
			iov_iter_revert(dio->submit.iter, copied);
			copied = ret = 0;
			जाओ out;
		पूर्ण

		bio = bio_alloc(GFP_KERNEL, nr_pages);
		bio_set_dev(bio, iomap->bdev);
		bio->bi_iter.bi_sector = iomap_sector(iomap, pos);
		bio->bi_ग_लिखो_hपूर्णांक = dio->iocb->ki_hपूर्णांक;
		bio->bi_ioprio = dio->iocb->ki_ioprio;
		bio->bi_निजी = dio;
		bio->bi_end_io = iomap_dio_bio_end_io;
		bio->bi_opf = bio_opf;

		ret = bio_iov_iter_get_pages(bio, dio->submit.iter);
		अगर (unlikely(ret)) अणु
			/*
			 * We have to stop part way through an IO. We must fall
			 * through to the sub-block tail zeroing here, otherwise
			 * this लघु IO may expose stale data in the tail of
			 * the block we haven't written data to.
			 */
			bio_put(bio);
			जाओ zero_tail;
		पूर्ण

		n = bio->bi_iter.bi_size;
		अगर (dio->flags & IOMAP_DIO_WRITE) अणु
			task_io_account_ग_लिखो(n);
		पूर्ण अन्यथा अणु
			अगर (dio->flags & IOMAP_DIO_सूचीTY)
				bio_set_pages_dirty(bio);
		पूर्ण

		dio->size += n;
		copied += n;

		nr_pages = bio_iov_vecs_to_alloc(dio->submit.iter,
						 BIO_MAX_VECS);
		iomap_dio_submit_bio(dio, iomap, bio, pos);
		pos += n;
	पूर्ण जबतक (nr_pages);

	/*
	 * We need to zeroout the tail of a sub-block ग_लिखो अगर the extent type
	 * requires zeroing or the ग_लिखो extends beyond खातापूर्ण. If we करोn't zero
	 * the block tail in the latter हाल, we can expose stale data via mmap
	 * पढ़ोs of the खातापूर्ण block.
	 */
zero_tail:
	अगर (need_zeroout ||
	    ((dio->flags & IOMAP_DIO_WRITE) && pos >= i_size_पढ़ो(inode))) अणु
		/* zero out from the end of the ग_लिखो to the end of the block */
		pad = pos & (fs_block_size - 1);
		अगर (pad)
			iomap_dio_zero(dio, iomap, pos, fs_block_size - pad);
	पूर्ण
out:
	/* Unकरो iter limitation to current extent */
	iov_iter_reexpand(dio->submit.iter, orig_count - copied);
	अगर (copied)
		वापस copied;
	वापस ret;
पूर्ण

अटल loff_t
iomap_dio_hole_actor(loff_t length, काष्ठा iomap_dio *dio)
अणु
	length = iov_iter_zero(length, dio->submit.iter);
	dio->size += length;
	वापस length;
पूर्ण

अटल loff_t
iomap_dio_अंतरभूत_actor(काष्ठा inode *inode, loff_t pos, loff_t length,
		काष्ठा iomap_dio *dio, काष्ठा iomap *iomap)
अणु
	काष्ठा iov_iter *iter = dio->submit.iter;
	माप_प्रकार copied;

	BUG_ON(pos + length > PAGE_SIZE - offset_in_page(iomap->अंतरभूत_data));

	अगर (dio->flags & IOMAP_DIO_WRITE) अणु
		loff_t size = inode->i_size;

		अगर (pos > size)
			स_रखो(iomap->अंतरभूत_data + size, 0, pos - size);
		copied = copy_from_iter(iomap->अंतरभूत_data + pos, length, iter);
		अगर (copied) अणु
			अगर (pos + copied > size)
				i_size_ग_लिखो(inode, pos + copied);
			mark_inode_dirty(inode);
		पूर्ण
	पूर्ण अन्यथा अणु
		copied = copy_to_iter(iomap->अंतरभूत_data + pos, length, iter);
	पूर्ण
	dio->size += copied;
	वापस copied;
पूर्ण

अटल loff_t
iomap_dio_actor(काष्ठा inode *inode, loff_t pos, loff_t length,
		व्योम *data, काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	काष्ठा iomap_dio *dio = data;

	चयन (iomap->type) अणु
	हाल IOMAP_HOLE:
		अगर (WARN_ON_ONCE(dio->flags & IOMAP_DIO_WRITE))
			वापस -EIO;
		वापस iomap_dio_hole_actor(length, dio);
	हाल IOMAP_UNWRITTEN:
		अगर (!(dio->flags & IOMAP_DIO_WRITE))
			वापस iomap_dio_hole_actor(length, dio);
		वापस iomap_dio_bio_actor(inode, pos, length, dio, iomap);
	हाल IOMAP_MAPPED:
		वापस iomap_dio_bio_actor(inode, pos, length, dio, iomap);
	हाल IOMAP_INLINE:
		वापस iomap_dio_अंतरभूत_actor(inode, pos, length, dio, iomap);
	हाल IOMAP_DELALLOC:
		/*
		 * DIO is not serialised against mmap() access at all, and so
		 * अगर the page_mkग_लिखो occurs between the ग_लिखोback and the
		 * iomap_apply() call in the DIO path, then it will see the
		 * DELALLOC block that the page-mkग_लिखो allocated.
		 */
		pr_warn_ratelimited("Direct I/O collision with buffered writes! File: %pD4 Comm: %.20s\n",
				    dio->iocb->ki_filp, current->comm);
		वापस -EIO;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EIO;
	पूर्ण
पूर्ण

/*
 * iomap_dio_rw() always completes O_[D]SYNC ग_लिखोs regardless of whether the IO
 * is being issued as AIO or not.  This allows us to optimise pure data ग_लिखोs
 * to use REQ_FUA rather than requiring generic_ग_लिखो_sync() to issue a
 * REQ_FLUSH post ग_लिखो. This is slightly tricky because a single request here
 * can be mapped पूर्णांकo multiple disjoपूर्णांक IOs and only a subset of the IOs issued
 * may be pure data ग_लिखोs. In that हाल, we still need to करो a full data sync
 * completion.
 *
 * Returns -ENOTBLK In हाल of a page invalidation invalidation failure क्रम
 * ग_लिखोs.  The callers needs to fall back to buffered I/O in this हाल.
 */
काष्ठा iomap_dio *
__iomap_dio_rw(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		स्थिर काष्ठा iomap_ops *ops, स्थिर काष्ठा iomap_dio_ops *करोps,
		अचिन्हित पूर्णांक dio_flags)
अणु
	काष्ठा address_space *mapping = iocb->ki_filp->f_mapping;
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	माप_प्रकार count = iov_iter_count(iter);
	loff_t pos = iocb->ki_pos;
	loff_t end = iocb->ki_pos + count - 1, ret = 0;
	bool रुको_क्रम_completion =
		is_sync_kiocb(iocb) || (dio_flags & IOMAP_DIO_FORCE_WAIT);
	अचिन्हित पूर्णांक iomap_flags = IOMAP_सूचीECT;
	काष्ठा blk_plug plug;
	काष्ठा iomap_dio *dio;

	अगर (!count)
		वापस शून्य;

	dio = kदो_स्मृति(माप(*dio), GFP_KERNEL);
	अगर (!dio)
		वापस ERR_PTR(-ENOMEM);

	dio->iocb = iocb;
	atomic_set(&dio->ref, 1);
	dio->size = 0;
	dio->i_size = i_size_पढ़ो(inode);
	dio->करोps = करोps;
	dio->error = 0;
	dio->flags = 0;

	dio->submit.iter = iter;
	dio->submit.रुकोer = current;
	dio->submit.cookie = BLK_QC_T_NONE;
	dio->submit.last_queue = शून्य;

	अगर (iov_iter_rw(iter) == READ) अणु
		अगर (pos >= dio->i_size)
			जाओ out_मुक्त_dio;

		अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
			अगर (filemap_range_needs_ग_लिखोback(mapping, pos, end)) अणु
				ret = -EAGAIN;
				जाओ out_मुक्त_dio;
			पूर्ण
			iomap_flags |= IOMAP_NOWAIT;
		पूर्ण

		अगर (iter_is_iovec(iter))
			dio->flags |= IOMAP_DIO_सूचीTY;
	पूर्ण अन्यथा अणु
		iomap_flags |= IOMAP_WRITE;
		dio->flags |= IOMAP_DIO_WRITE;

		अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
			अगर (filemap_range_has_page(mapping, pos, end)) अणु
				ret = -EAGAIN;
				जाओ out_मुक्त_dio;
			पूर्ण
			iomap_flags |= IOMAP_NOWAIT;
		पूर्ण

		/* क्रम data sync or sync, we need sync completion processing */
		अगर (iocb->ki_flags & IOCB_DSYNC)
			dio->flags |= IOMAP_DIO_NEED_SYNC;

		/*
		 * For datasync only ग_लिखोs, we optimistically try using FUA क्रम
		 * this IO.  Any non-FUA ग_लिखो that occurs will clear this flag,
		 * hence we know beक्रमe completion whether a cache flush is
		 * necessary.
		 */
		अगर ((iocb->ki_flags & (IOCB_DSYNC | IOCB_SYNC)) == IOCB_DSYNC)
			dio->flags |= IOMAP_DIO_WRITE_FUA;
	पूर्ण

	अगर (dio_flags & IOMAP_DIO_OVERWRITE_ONLY) अणु
		ret = -EAGAIN;
		अगर (pos >= dio->i_size || pos + count > dio->i_size)
			जाओ out_मुक्त_dio;
		iomap_flags |= IOMAP_OVERWRITE_ONLY;
	पूर्ण

	ret = filemap_ग_लिखो_and_रुको_range(mapping, pos, end);
	अगर (ret)
		जाओ out_मुक्त_dio;

	अगर (iov_iter_rw(iter) == WRITE) अणु
		/*
		 * Try to invalidate cache pages क्रम the range we are writing.
		 * If this invalidation fails, let the caller fall back to
		 * buffered I/O.
		 */
		अगर (invalidate_inode_pages2_range(mapping, pos >> PAGE_SHIFT,
				end >> PAGE_SHIFT)) अणु
			trace_iomap_dio_invalidate_fail(inode, pos, count);
			ret = -ENOTBLK;
			जाओ out_मुक्त_dio;
		पूर्ण

		अगर (!रुको_क्रम_completion && !inode->i_sb->s_dio_करोne_wq) अणु
			ret = sb_init_dio_करोne_wq(inode->i_sb);
			अगर (ret < 0)
				जाओ out_मुक्त_dio;
		पूर्ण
	पूर्ण

	inode_dio_begin(inode);

	blk_start_plug(&plug);
	करो अणु
		ret = iomap_apply(inode, pos, count, iomap_flags, ops, dio,
				iomap_dio_actor);
		अगर (ret <= 0) अणु
			/* magic error code to fall back to buffered I/O */
			अगर (ret == -ENOTBLK) अणु
				रुको_क्रम_completion = true;
				ret = 0;
			पूर्ण
			अवरोध;
		पूर्ण
		pos += ret;

		अगर (iov_iter_rw(iter) == READ && pos >= dio->i_size) अणु
			/*
			 * We only report that we've पढ़ो data up to i_size.
			 * Revert iter to a state corresponding to that as
			 * some callers (such as splice code) rely on it.
			 */
			iov_iter_revert(iter, pos - dio->i_size);
			अवरोध;
		पूर्ण
	पूर्ण जबतक ((count = iov_iter_count(iter)) > 0);
	blk_finish_plug(&plug);

	अगर (ret < 0)
		iomap_dio_set_error(dio, ret);

	/*
	 * If all the ग_लिखोs we issued were FUA, we करोn't need to flush the
	 * cache on IO completion. Clear the sync flag क्रम this हाल.
	 */
	अगर (dio->flags & IOMAP_DIO_WRITE_FUA)
		dio->flags &= ~IOMAP_DIO_NEED_SYNC;

	WRITE_ONCE(iocb->ki_cookie, dio->submit.cookie);
	WRITE_ONCE(iocb->निजी, dio->submit.last_queue);

	/*
	 * We are about to drop our additional submission reference, which
	 * might be the last reference to the dio.  There are three dअगरferent
	 * ways we can progress here:
	 *
	 *  (a) If this is the last reference we will always complete and मुक्त
	 *	the dio ourselves.
	 *  (b) If this is not the last reference, and we serve an asynchronous
	 *	iocb, we must never touch the dio after the decrement, the
	 *	I/O completion handler will complete and मुक्त it.
	 *  (c) If this is not the last reference, but we serve a synchronous
	 *	iocb, the I/O completion handler will wake us up on the drop
	 *	of the final reference, and we will complete and मुक्त it here
	 *	after we got woken by the I/O completion handler.
	 */
	dio->रुको_क्रम_completion = रुको_क्रम_completion;
	अगर (!atomic_dec_and_test(&dio->ref)) अणु
		अगर (!रुको_क्रम_completion)
			वापस ERR_PTR(-EIOCBQUEUED);

		क्रम (;;) अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			अगर (!READ_ONCE(dio->submit.रुकोer))
				अवरोध;

			अगर (!(iocb->ki_flags & IOCB_HIPRI) ||
			    !dio->submit.last_queue ||
			    !blk_poll(dio->submit.last_queue,
					 dio->submit.cookie, true))
				blk_io_schedule();
		पूर्ण
		__set_current_state(TASK_RUNNING);
	पूर्ण

	वापस dio;

out_मुक्त_dio:
	kमुक्त(dio);
	अगर (ret)
		वापस ERR_PTR(ret);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(__iomap_dio_rw);

sमाप_प्रकार
iomap_dio_rw(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		स्थिर काष्ठा iomap_ops *ops, स्थिर काष्ठा iomap_dio_ops *करोps,
		अचिन्हित पूर्णांक dio_flags)
अणु
	काष्ठा iomap_dio *dio;

	dio = __iomap_dio_rw(iocb, iter, ops, करोps, dio_flags);
	अगर (IS_ERR_OR_शून्य(dio))
		वापस PTR_ERR_OR_ZERO(dio);
	वापस iomap_dio_complete(dio);
पूर्ण
EXPORT_SYMBOL_GPL(iomap_dio_rw);
