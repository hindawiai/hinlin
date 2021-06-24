<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 2001  Andrea Arcangeli <andrea@suse.de> SuSE
 *  Copyright (C) 2016 - 2020 Christoph Hellwig
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/major.h>
#समावेश <linux/device_cgroup.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/module.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/magic.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/swap.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/mpage.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/uपन.स>
#समावेश <linux/namei.h>
#समावेश <linux/log2.h>
#समावेश <linux/cleancache.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/part_स्थिति.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/suspend.h>
#समावेश "internal.h"

काष्ठा bdev_inode अणु
	काष्ठा block_device bdev;
	काष्ठा inode vfs_inode;
पूर्ण;

अटल स्थिर काष्ठा address_space_operations def_blk_aops;

अटल अंतरभूत काष्ठा bdev_inode *BDEV_I(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा bdev_inode, vfs_inode);
पूर्ण

काष्ठा block_device *I_BDEV(काष्ठा inode *inode)
अणु
	वापस &BDEV_I(inode)->bdev;
पूर्ण
EXPORT_SYMBOL(I_BDEV);

अटल व्योम bdev_ग_लिखो_inode(काष्ठा block_device *bdev)
अणु
	काष्ठा inode *inode = bdev->bd_inode;
	पूर्णांक ret;

	spin_lock(&inode->i_lock);
	जबतक (inode->i_state & I_सूचीTY) अणु
		spin_unlock(&inode->i_lock);
		ret = ग_लिखो_inode_now(inode, true);
		अगर (ret) अणु
			अक्षर name[BDEVNAME_SIZE];
			pr_warn_ratelimited("VFS: Dirty inode writeback failed "
					    "for block device %s (err=%d).\n",
					    bdevname(bdev, name), ret);
		पूर्ण
		spin_lock(&inode->i_lock);
	पूर्ण
	spin_unlock(&inode->i_lock);
पूर्ण

/* Kill _all_ buffers and pagecache , dirty or not.. */
अटल व्योम समाप्त_bdev(काष्ठा block_device *bdev)
अणु
	काष्ठा address_space *mapping = bdev->bd_inode->i_mapping;

	अगर (mapping_empty(mapping))
		वापस;

	invalidate_bh_lrus();
	truncate_inode_pages(mapping, 0);
पूर्ण

/* Invalidate clean unused buffers and pagecache. */
व्योम invalidate_bdev(काष्ठा block_device *bdev)
अणु
	काष्ठा address_space *mapping = bdev->bd_inode->i_mapping;

	अगर (mapping->nrpages) अणु
		invalidate_bh_lrus();
		lru_add_drain_all();	/* make sure all lru add caches are flushed */
		invalidate_mapping_pages(mapping, 0, -1);
	पूर्ण
	/* 99% of the समय, we करोn't need to flush the cleancache on the bdev.
	 * But, क्रम the strange corners, lets be cautious
	 */
	cleancache_invalidate_inode(mapping);
पूर्ण
EXPORT_SYMBOL(invalidate_bdev);

/*
 * Drop all buffers & page cache क्रम given bdev range. This function bails
 * with error अगर bdev has other exclusive owner (such as fileप्रणाली).
 */
पूर्णांक truncate_bdev_range(काष्ठा block_device *bdev, भ_शेषe_t mode,
			loff_t lstart, loff_t lend)
अणु
	/*
	 * If we करोn't hold exclusive handle क्रम the device, upgrade to it
	 * जबतक we discard the buffer cache to aव्योम discarding buffers
	 * under live fileप्रणाली.
	 */
	अगर (!(mode & FMODE_EXCL)) अणु
		पूर्णांक err = bd_prepare_to_claim(bdev, truncate_bdev_range);
		अगर (err)
			जाओ invalidate;
	पूर्ण

	truncate_inode_pages_range(bdev->bd_inode->i_mapping, lstart, lend);
	अगर (!(mode & FMODE_EXCL))
		bd_पात_claiming(bdev, truncate_bdev_range);
	वापस 0;

invalidate:
	/*
	 * Someone अन्यथा has handle exclusively खोलो. Try invalidating instead.
	 * The 'end' argument is inclusive so the rounding is safe.
	 */
	वापस invalidate_inode_pages2_range(bdev->bd_inode->i_mapping,
					     lstart >> PAGE_SHIFT,
					     lend >> PAGE_SHIFT);
पूर्ण

अटल व्योम set_init_blocksize(काष्ठा block_device *bdev)
अणु
	अचिन्हित पूर्णांक bsize = bdev_logical_block_size(bdev);
	loff_t size = i_size_पढ़ो(bdev->bd_inode);

	जबतक (bsize < PAGE_SIZE) अणु
		अगर (size & bsize)
			अवरोध;
		bsize <<= 1;
	पूर्ण
	bdev->bd_inode->i_blkbits = blksize_bits(bsize);
पूर्ण

पूर्णांक set_blocksize(काष्ठा block_device *bdev, पूर्णांक size)
अणु
	/* Size must be a घातer of two, and between 512 and PAGE_SIZE */
	अगर (size > PAGE_SIZE || size < 512 || !is_घातer_of_2(size))
		वापस -EINVAL;

	/* Size cannot be smaller than the size supported by the device */
	अगर (size < bdev_logical_block_size(bdev))
		वापस -EINVAL;

	/* Don't change the size अगर it is same as current */
	अगर (bdev->bd_inode->i_blkbits != blksize_bits(size)) अणु
		sync_blockdev(bdev);
		bdev->bd_inode->i_blkbits = blksize_bits(size);
		समाप्त_bdev(bdev);
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(set_blocksize);

पूर्णांक sb_set_blocksize(काष्ठा super_block *sb, पूर्णांक size)
अणु
	अगर (set_blocksize(sb->s_bdev, size))
		वापस 0;
	/* If we get here, we know size is घातer of two
	 * and it's value is between 512 and PAGE_SIZE */
	sb->s_blocksize = size;
	sb->s_blocksize_bits = blksize_bits(size);
	वापस sb->s_blocksize;
पूर्ण

EXPORT_SYMBOL(sb_set_blocksize);

पूर्णांक sb_min_blocksize(काष्ठा super_block *sb, पूर्णांक size)
अणु
	पूर्णांक minsize = bdev_logical_block_size(sb->s_bdev);
	अगर (size < minsize)
		size = minsize;
	वापस sb_set_blocksize(sb, size);
पूर्ण

EXPORT_SYMBOL(sb_min_blocksize);

अटल पूर्णांक
blkdev_get_block(काष्ठा inode *inode, sector_t iblock,
		काष्ठा buffer_head *bh, पूर्णांक create)
अणु
	bh->b_bdev = I_BDEV(inode);
	bh->b_blocknr = iblock;
	set_buffer_mapped(bh);
	वापस 0;
पूर्ण

अटल काष्ठा inode *bdev_file_inode(काष्ठा file *file)
अणु
	वापस file->f_mapping->host;
पूर्ण

अटल अचिन्हित पूर्णांक dio_bio_ग_लिखो_op(काष्ठा kiocb *iocb)
अणु
	अचिन्हित पूर्णांक op = REQ_OP_WRITE | REQ_SYNC | REQ_IDLE;

	/* aव्योम the need क्रम a I/O completion work item */
	अगर (iocb->ki_flags & IOCB_DSYNC)
		op |= REQ_FUA;
	वापस op;
पूर्ण

#घोषणा DIO_INLINE_BIO_VECS 4

अटल व्योम blkdev_bio_end_io_simple(काष्ठा bio *bio)
अणु
	काष्ठा task_काष्ठा *रुकोer = bio->bi_निजी;

	WRITE_ONCE(bio->bi_निजी, शून्य);
	blk_wake_io_task(रुकोer);
पूर्ण

अटल sमाप_प्रकार
__blkdev_direct_IO_simple(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		अचिन्हित पूर्णांक nr_pages)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा block_device *bdev = I_BDEV(bdev_file_inode(file));
	काष्ठा bio_vec अंतरभूत_vecs[DIO_INLINE_BIO_VECS], *vecs;
	loff_t pos = iocb->ki_pos;
	bool should_dirty = false;
	काष्ठा bio bio;
	sमाप_प्रकार ret;
	blk_qc_t qc;

	अगर ((pos | iov_iter_alignment(iter)) &
	    (bdev_logical_block_size(bdev) - 1))
		वापस -EINVAL;

	अगर (nr_pages <= DIO_INLINE_BIO_VECS)
		vecs = अंतरभूत_vecs;
	अन्यथा अणु
		vecs = kदो_स्मृति_array(nr_pages, माप(काष्ठा bio_vec),
				     GFP_KERNEL);
		अगर (!vecs)
			वापस -ENOMEM;
	पूर्ण

	bio_init(&bio, vecs, nr_pages);
	bio_set_dev(&bio, bdev);
	bio.bi_iter.bi_sector = pos >> 9;
	bio.bi_ग_लिखो_hपूर्णांक = iocb->ki_hपूर्णांक;
	bio.bi_निजी = current;
	bio.bi_end_io = blkdev_bio_end_io_simple;
	bio.bi_ioprio = iocb->ki_ioprio;

	ret = bio_iov_iter_get_pages(&bio, iter);
	अगर (unlikely(ret))
		जाओ out;
	ret = bio.bi_iter.bi_size;

	अगर (iov_iter_rw(iter) == READ) अणु
		bio.bi_opf = REQ_OP_READ;
		अगर (iter_is_iovec(iter))
			should_dirty = true;
	पूर्ण अन्यथा अणु
		bio.bi_opf = dio_bio_ग_लिखो_op(iocb);
		task_io_account_ग_लिखो(ret);
	पूर्ण
	अगर (iocb->ki_flags & IOCB_NOWAIT)
		bio.bi_opf |= REQ_NOWAIT;
	अगर (iocb->ki_flags & IOCB_HIPRI)
		bio_set_polled(&bio, iocb);

	qc = submit_bio(&bio);
	क्रम (;;) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (!READ_ONCE(bio.bi_निजी))
			अवरोध;
		अगर (!(iocb->ki_flags & IOCB_HIPRI) ||
		    !blk_poll(bdev_get_queue(bdev), qc, true))
			blk_io_schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);

	bio_release_pages(&bio, should_dirty);
	अगर (unlikely(bio.bi_status))
		ret = blk_status_to_त्रुटि_सं(bio.bi_status);

out:
	अगर (vecs != अंतरभूत_vecs)
		kमुक्त(vecs);

	bio_uninit(&bio);

	वापस ret;
पूर्ण

काष्ठा blkdev_dio अणु
	जोड़ अणु
		काष्ठा kiocb		*iocb;
		काष्ठा task_काष्ठा	*रुकोer;
	पूर्ण;
	माप_प्रकार			size;
	atomic_t		ref;
	bool			multi_bio : 1;
	bool			should_dirty : 1;
	bool			is_sync : 1;
	काष्ठा bio		bio;
पूर्ण;

अटल काष्ठा bio_set blkdev_dio_pool;

अटल पूर्णांक blkdev_iopoll(काष्ठा kiocb *kiocb, bool रुको)
अणु
	काष्ठा block_device *bdev = I_BDEV(kiocb->ki_filp->f_mapping->host);
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	वापस blk_poll(q, READ_ONCE(kiocb->ki_cookie), रुको);
पूर्ण

अटल व्योम blkdev_bio_end_io(काष्ठा bio *bio)
अणु
	काष्ठा blkdev_dio *dio = bio->bi_निजी;
	bool should_dirty = dio->should_dirty;

	अगर (bio->bi_status && !dio->bio.bi_status)
		dio->bio.bi_status = bio->bi_status;

	अगर (!dio->multi_bio || atomic_dec_and_test(&dio->ref)) अणु
		अगर (!dio->is_sync) अणु
			काष्ठा kiocb *iocb = dio->iocb;
			sमाप_प्रकार ret;

			अगर (likely(!dio->bio.bi_status)) अणु
				ret = dio->size;
				iocb->ki_pos += ret;
			पूर्ण अन्यथा अणु
				ret = blk_status_to_त्रुटि_सं(dio->bio.bi_status);
			पूर्ण

			dio->iocb->ki_complete(iocb, ret, 0);
			अगर (dio->multi_bio)
				bio_put(&dio->bio);
		पूर्ण अन्यथा अणु
			काष्ठा task_काष्ठा *रुकोer = dio->रुकोer;

			WRITE_ONCE(dio->रुकोer, शून्य);
			blk_wake_io_task(रुकोer);
		पूर्ण
	पूर्ण

	अगर (should_dirty) अणु
		bio_check_pages_dirty(bio);
	पूर्ण अन्यथा अणु
		bio_release_pages(bio, false);
		bio_put(bio);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार __blkdev_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		अचिन्हित पूर्णांक nr_pages)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = bdev_file_inode(file);
	काष्ठा block_device *bdev = I_BDEV(inode);
	काष्ठा blk_plug plug;
	काष्ठा blkdev_dio *dio;
	काष्ठा bio *bio;
	bool is_poll = (iocb->ki_flags & IOCB_HIPRI) != 0;
	bool is_पढ़ो = (iov_iter_rw(iter) == READ), is_sync;
	loff_t pos = iocb->ki_pos;
	blk_qc_t qc = BLK_QC_T_NONE;
	पूर्णांक ret = 0;

	अगर ((pos | iov_iter_alignment(iter)) &
	    (bdev_logical_block_size(bdev) - 1))
		वापस -EINVAL;

	bio = bio_alloc_bioset(GFP_KERNEL, nr_pages, &blkdev_dio_pool);

	dio = container_of(bio, काष्ठा blkdev_dio, bio);
	dio->is_sync = is_sync = is_sync_kiocb(iocb);
	अगर (dio->is_sync) अणु
		dio->रुकोer = current;
		bio_get(bio);
	पूर्ण अन्यथा अणु
		dio->iocb = iocb;
	पूर्ण

	dio->size = 0;
	dio->multi_bio = false;
	dio->should_dirty = is_पढ़ो && iter_is_iovec(iter);

	/*
	 * Don't plug क्रम HIPRI/polled IO, as those should go straight
	 * to issue
	 */
	अगर (!is_poll)
		blk_start_plug(&plug);

	क्रम (;;) अणु
		bio_set_dev(bio, bdev);
		bio->bi_iter.bi_sector = pos >> 9;
		bio->bi_ग_लिखो_hपूर्णांक = iocb->ki_hपूर्णांक;
		bio->bi_निजी = dio;
		bio->bi_end_io = blkdev_bio_end_io;
		bio->bi_ioprio = iocb->ki_ioprio;

		ret = bio_iov_iter_get_pages(bio, iter);
		अगर (unlikely(ret)) अणु
			bio->bi_status = BLK_STS_IOERR;
			bio_endio(bio);
			अवरोध;
		पूर्ण

		अगर (is_पढ़ो) अणु
			bio->bi_opf = REQ_OP_READ;
			अगर (dio->should_dirty)
				bio_set_pages_dirty(bio);
		पूर्ण अन्यथा अणु
			bio->bi_opf = dio_bio_ग_लिखो_op(iocb);
			task_io_account_ग_लिखो(bio->bi_iter.bi_size);
		पूर्ण
		अगर (iocb->ki_flags & IOCB_NOWAIT)
			bio->bi_opf |= REQ_NOWAIT;

		dio->size += bio->bi_iter.bi_size;
		pos += bio->bi_iter.bi_size;

		nr_pages = bio_iov_vecs_to_alloc(iter, BIO_MAX_VECS);
		अगर (!nr_pages) अणु
			bool polled = false;

			अगर (iocb->ki_flags & IOCB_HIPRI) अणु
				bio_set_polled(bio, iocb);
				polled = true;
			पूर्ण

			qc = submit_bio(bio);

			अगर (polled)
				WRITE_ONCE(iocb->ki_cookie, qc);
			अवरोध;
		पूर्ण

		अगर (!dio->multi_bio) अणु
			/*
			 * AIO needs an extra reference to ensure the dio
			 * काष्ठाure which is embedded पूर्णांकo the first bio
			 * stays around.
			 */
			अगर (!is_sync)
				bio_get(bio);
			dio->multi_bio = true;
			atomic_set(&dio->ref, 2);
		पूर्ण अन्यथा अणु
			atomic_inc(&dio->ref);
		पूर्ण

		submit_bio(bio);
		bio = bio_alloc(GFP_KERNEL, nr_pages);
	पूर्ण

	अगर (!is_poll)
		blk_finish_plug(&plug);

	अगर (!is_sync)
		वापस -EIOCBQUEUED;

	क्रम (;;) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (!READ_ONCE(dio->रुकोer))
			अवरोध;

		अगर (!(iocb->ki_flags & IOCB_HIPRI) ||
		    !blk_poll(bdev_get_queue(bdev), qc, true))
			blk_io_schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);

	अगर (!ret)
		ret = blk_status_to_त्रुटि_सं(dio->bio.bi_status);
	अगर (likely(!ret))
		ret = dio->size;

	bio_put(&dio->bio);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
blkdev_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	अचिन्हित पूर्णांक nr_pages;

	अगर (!iov_iter_count(iter))
		वापस 0;

	nr_pages = bio_iov_vecs_to_alloc(iter, BIO_MAX_VECS + 1);
	अगर (is_sync_kiocb(iocb) && nr_pages <= BIO_MAX_VECS)
		वापस __blkdev_direct_IO_simple(iocb, iter, nr_pages);

	वापस __blkdev_direct_IO(iocb, iter, bio_max_segs(nr_pages));
पूर्ण

अटल __init पूर्णांक blkdev_init(व्योम)
अणु
	वापस bioset_init(&blkdev_dio_pool, 4, दुरत्व(काष्ठा blkdev_dio, bio), BIOSET_NEED_BVECS);
पूर्ण
module_init(blkdev_init);

पूर्णांक __sync_blockdev(काष्ठा block_device *bdev, पूर्णांक रुको)
अणु
	अगर (!bdev)
		वापस 0;
	अगर (!रुको)
		वापस filemap_flush(bdev->bd_inode->i_mapping);
	वापस filemap_ग_लिखो_and_रुको(bdev->bd_inode->i_mapping);
पूर्ण

/*
 * Write out and रुको upon all the dirty data associated with a block
 * device via its mapping.  Does not take the superblock lock.
 */
पूर्णांक sync_blockdev(काष्ठा block_device *bdev)
अणु
	वापस __sync_blockdev(bdev, 1);
पूर्ण
EXPORT_SYMBOL(sync_blockdev);

/*
 * Write out and रुको upon all dirty data associated with this
 * device.   Fileप्रणाली data as well as the underlying block
 * device.  Takes the superblock lock.
 */
पूर्णांक fsync_bdev(काष्ठा block_device *bdev)
अणु
	काष्ठा super_block *sb = get_super(bdev);
	अगर (sb) अणु
		पूर्णांक res = sync_fileप्रणाली(sb);
		drop_super(sb);
		वापस res;
	पूर्ण
	वापस sync_blockdev(bdev);
पूर्ण
EXPORT_SYMBOL(fsync_bdev);

/**
 * मुक्तze_bdev  --  lock a fileप्रणाली and क्रमce it पूर्णांकo a consistent state
 * @bdev:	blockdevice to lock
 *
 * If a superblock is found on this device, we take the s_umount semaphore
 * on it to make sure nobody unmounts until the snapshot creation is करोne.
 * The reference counter (bd_fsमुक्तze_count) guarantees that only the last
 * unमुक्तze process can unमुक्तze the frozen fileप्रणाली actually when multiple
 * मुक्तze requests arrive simultaneously. It counts up in मुक्तze_bdev() and
 * count करोwn in thaw_bdev(). When it becomes 0, thaw_bdev() will unमुक्तze
 * actually.
 */
पूर्णांक मुक्तze_bdev(काष्ठा block_device *bdev)
अणु
	काष्ठा super_block *sb;
	पूर्णांक error = 0;

	mutex_lock(&bdev->bd_fsमुक्तze_mutex);
	अगर (++bdev->bd_fsमुक्तze_count > 1)
		जाओ करोne;

	sb = get_active_super(bdev);
	अगर (!sb)
		जाओ sync;
	अगर (sb->s_op->मुक्तze_super)
		error = sb->s_op->मुक्तze_super(sb);
	अन्यथा
		error = मुक्तze_super(sb);
	deactivate_super(sb);

	अगर (error) अणु
		bdev->bd_fsमुक्तze_count--;
		जाओ करोne;
	पूर्ण
	bdev->bd_fsमुक्तze_sb = sb;

sync:
	sync_blockdev(bdev);
करोne:
	mutex_unlock(&bdev->bd_fsमुक्तze_mutex);
	वापस error;
पूर्ण
EXPORT_SYMBOL(मुक्तze_bdev);

/**
 * thaw_bdev  -- unlock fileप्रणाली
 * @bdev:	blockdevice to unlock
 *
 * Unlocks the fileप्रणाली and marks it ग_लिखोable again after मुक्तze_bdev().
 */
पूर्णांक thaw_bdev(काष्ठा block_device *bdev)
अणु
	काष्ठा super_block *sb;
	पूर्णांक error = -EINVAL;

	mutex_lock(&bdev->bd_fsमुक्तze_mutex);
	अगर (!bdev->bd_fsमुक्तze_count)
		जाओ out;

	error = 0;
	अगर (--bdev->bd_fsमुक्तze_count > 0)
		जाओ out;

	sb = bdev->bd_fsमुक्तze_sb;
	अगर (!sb)
		जाओ out;

	अगर (sb->s_op->thaw_super)
		error = sb->s_op->thaw_super(sb);
	अन्यथा
		error = thaw_super(sb);
	अगर (error)
		bdev->bd_fsमुक्तze_count++;
	अन्यथा
		bdev->bd_fsमुक्तze_sb = शून्य;
out:
	mutex_unlock(&bdev->bd_fsमुक्तze_mutex);
	वापस error;
पूर्ण
EXPORT_SYMBOL(thaw_bdev);

अटल पूर्णांक blkdev_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, blkdev_get_block, wbc);
पूर्ण

अटल पूर्णांक blkdev_पढ़ोpage(काष्ठा file * file, काष्ठा page * page)
अणु
	वापस block_पढ़ो_full_page(page, blkdev_get_block);
पूर्ण

अटल व्योम blkdev_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, blkdev_get_block);
पूर्ण

अटल पूर्णांक blkdev_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	वापस block_ग_लिखो_begin(mapping, pos, len, flags, pagep,
				 blkdev_get_block);
पूर्ण

अटल पूर्णांक blkdev_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	पूर्णांक ret;
	ret = block_ग_लिखो_end(file, mapping, pos, len, copied, page, fsdata);

	unlock_page(page);
	put_page(page);

	वापस ret;
पूर्ण

/*
 * निजी llseek:
 * क्रम a block special file file_inode(file)->i_size is zero
 * so we compute the size by hand (just as in block_पढ़ो/ग_लिखो above)
 */
अटल loff_t block_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *bd_inode = bdev_file_inode(file);
	loff_t retval;

	inode_lock(bd_inode);
	retval = fixed_size_llseek(file, offset, whence, i_size_पढ़ो(bd_inode));
	inode_unlock(bd_inode);
	वापस retval;
पूर्ण
	
पूर्णांक blkdev_fsync(काष्ठा file *filp, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *bd_inode = bdev_file_inode(filp);
	काष्ठा block_device *bdev = I_BDEV(bd_inode);
	पूर्णांक error;
	
	error = file_ग_लिखो_and_रुको_range(filp, start, end);
	अगर (error)
		वापस error;

	/*
	 * There is no need to serialise calls to blkdev_issue_flush with
	 * i_mutex and करोing so causes perक्रमmance issues with concurrent
	 * O_SYNC ग_लिखोrs to a block device.
	 */
	error = blkdev_issue_flush(bdev);
	अगर (error == -EOPNOTSUPP)
		error = 0;

	वापस error;
पूर्ण
EXPORT_SYMBOL(blkdev_fsync);

/**
 * bdev_पढ़ो_page() - Start पढ़ोing a page from a block device
 * @bdev: The device to पढ़ो the page from
 * @sector: The offset on the device to पढ़ो the page to (need not be aligned)
 * @page: The page to पढ़ो
 *
 * On entry, the page should be locked.  It will be unlocked when the page
 * has been पढ़ो.  If the block driver implements rw_page synchronously,
 * that will be true on निकास from this function, but it need not be.
 *
 * Errors वापसed by this function are usually "soft", eg out of memory, or
 * queue full; callers should try a dअगरferent route to पढ़ो this page rather
 * than propagate an error back up the stack.
 *
 * Return: negative त्रुटि_सं अगर an error occurs, 0 अगर submission was successful.
 */
पूर्णांक bdev_पढ़ो_page(काष्ठा block_device *bdev, sector_t sector,
			काष्ठा page *page)
अणु
	स्थिर काष्ठा block_device_operations *ops = bdev->bd_disk->fops;
	पूर्णांक result = -EOPNOTSUPP;

	अगर (!ops->rw_page || bdev_get_पूर्णांकegrity(bdev))
		वापस result;

	result = blk_queue_enter(bdev->bd_disk->queue, 0);
	अगर (result)
		वापस result;
	result = ops->rw_page(bdev, sector + get_start_sect(bdev), page,
			      REQ_OP_READ);
	blk_queue_निकास(bdev->bd_disk->queue);
	वापस result;
पूर्ण

/**
 * bdev_ग_लिखो_page() - Start writing a page to a block device
 * @bdev: The device to ग_लिखो the page to
 * @sector: The offset on the device to ग_लिखो the page to (need not be aligned)
 * @page: The page to ग_लिखो
 * @wbc: The ग_लिखोback_control क्रम the ग_लिखो
 *
 * On entry, the page should be locked and not currently under ग_लिखोback.
 * On निकास, अगर the ग_लिखो started successfully, the page will be unlocked and
 * under ग_लिखोback.  If the ग_लिखो failed alपढ़ोy (eg the driver failed to
 * queue the page to the device), the page will still be locked.  If the
 * caller is a ->ग_लिखोpage implementation, it will need to unlock the page.
 *
 * Errors वापसed by this function are usually "soft", eg out of memory, or
 * queue full; callers should try a dअगरferent route to ग_लिखो this page rather
 * than propagate an error back up the stack.
 *
 * Return: negative त्रुटि_सं अगर an error occurs, 0 अगर submission was successful.
 */
पूर्णांक bdev_ग_लिखो_page(काष्ठा block_device *bdev, sector_t sector,
			काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक result;
	स्थिर काष्ठा block_device_operations *ops = bdev->bd_disk->fops;

	अगर (!ops->rw_page || bdev_get_पूर्णांकegrity(bdev))
		वापस -EOPNOTSUPP;
	result = blk_queue_enter(bdev->bd_disk->queue, 0);
	अगर (result)
		वापस result;

	set_page_ग_लिखोback(page);
	result = ops->rw_page(bdev, sector + get_start_sect(bdev), page,
			      REQ_OP_WRITE);
	अगर (result) अणु
		end_page_ग_लिखोback(page);
	पूर्ण अन्यथा अणु
		clean_page_buffers(page);
		unlock_page(page);
	पूर्ण
	blk_queue_निकास(bdev->bd_disk->queue);
	वापस result;
पूर्ण

/*
 * pseuकरो-fs
 */

अटल  __cacheline_aligned_in_smp DEFINE_SPINLOCK(bdev_lock);
अटल काष्ठा kmem_cache * bdev_cachep __पढ़ो_mostly;

अटल काष्ठा inode *bdev_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा bdev_inode *ei = kmem_cache_alloc(bdev_cachep, GFP_KERNEL);

	अगर (!ei)
		वापस शून्य;
	स_रखो(&ei->bdev, 0, माप(ei->bdev));
	ei->bdev.bd_bdi = &noop_backing_dev_info;
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम bdev_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा block_device *bdev = I_BDEV(inode);

	मुक्त_percpu(bdev->bd_stats);
	kमुक्त(bdev->bd_meta_info);

	kmem_cache_मुक्त(bdev_cachep, BDEV_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *data)
अणु
	काष्ठा bdev_inode *ei = data;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल व्योम bdev_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा block_device *bdev = &BDEV_I(inode)->bdev;
	truncate_inode_pages_final(&inode->i_data);
	invalidate_inode_buffers(inode); /* is it needed here? */
	clear_inode(inode);
	/* Detach inode from wb early as bdi_put() may मुक्त bdi->wb */
	inode_detach_wb(inode);
	अगर (bdev->bd_bdi != &noop_backing_dev_info) अणु
		bdi_put(bdev->bd_bdi);
		bdev->bd_bdi = &noop_backing_dev_info;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा super_operations bdev_sops = अणु
	.statfs = simple_statfs,
	.alloc_inode = bdev_alloc_inode,
	.मुक्त_inode = bdev_मुक्त_inode,
	.drop_inode = generic_delete_inode,
	.evict_inode = bdev_evict_inode,
पूर्ण;

अटल पूर्णांक bd_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा pseuकरो_fs_context *ctx = init_pseuकरो(fc, BDEVFS_MAGIC);
	अगर (!ctx)
		वापस -ENOMEM;
	fc->s_अगरlags |= SB_I_CGROUPWB;
	ctx->ops = &bdev_sops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type bd_type = अणु
	.name		= "bdev",
	.init_fs_context = bd_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;

काष्ठा super_block *blockdev_superblock __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(blockdev_superblock);

व्योम __init bdev_cache_init(व्योम)
अणु
	पूर्णांक err;
	अटल काष्ठा vfsmount *bd_mnt;

	bdev_cachep = kmem_cache_create("bdev_cache", माप(काष्ठा bdev_inode),
			0, (SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT|
				SLAB_MEM_SPREAD|SLAB_ACCOUNT|SLAB_PANIC),
			init_once);
	err = रेजिस्टर_fileप्रणाली(&bd_type);
	अगर (err)
		panic("Cannot register bdev pseudo-fs");
	bd_mnt = kern_mount(&bd_type);
	अगर (IS_ERR(bd_mnt))
		panic("Cannot create bdev pseudo-fs");
	blockdev_superblock = bd_mnt->mnt_sb;   /* For ग_लिखोback */
पूर्ण

काष्ठा block_device *bdev_alloc(काष्ठा gendisk *disk, u8 partno)
अणु
	काष्ठा block_device *bdev;
	काष्ठा inode *inode;

	inode = new_inode(blockdev_superblock);
	अगर (!inode)
		वापस शून्य;
	inode->i_mode = S_IFBLK;
	inode->i_rdev = 0;
	inode->i_data.a_ops = &def_blk_aops;
	mapping_set_gfp_mask(&inode->i_data, GFP_USER);

	bdev = I_BDEV(inode);
	mutex_init(&bdev->bd_mutex);
	mutex_init(&bdev->bd_fsमुक्तze_mutex);
	spin_lock_init(&bdev->bd_size_lock);
	bdev->bd_disk = disk;
	bdev->bd_partno = partno;
	bdev->bd_inode = inode;
#अगर_घोषित CONFIG_SYSFS
	INIT_LIST_HEAD(&bdev->bd_holder_disks);
#पूर्ण_अगर
	bdev->bd_stats = alloc_percpu(काष्ठा disk_stats);
	अगर (!bdev->bd_stats) अणु
		iput(inode);
		वापस शून्य;
	पूर्ण
	वापस bdev;
पूर्ण

व्योम bdev_add(काष्ठा block_device *bdev, dev_t dev)
अणु
	bdev->bd_dev = dev;
	bdev->bd_inode->i_rdev = dev;
	bdev->bd_inode->i_ino = dev;
	insert_inode_hash(bdev->bd_inode);
पूर्ण

अटल काष्ठा block_device *bdget(dev_t dev)
अणु
	काष्ठा inode *inode;

	inode = ilookup(blockdev_superblock, dev);
	अगर (!inode)
		वापस शून्य;
	वापस &BDEV_I(inode)->bdev;
पूर्ण

/**
 * bdgrab -- Grab a reference to an alपढ़ोy referenced block device
 * @bdev:	Block device to grab a reference to.
 *
 * Returns the block_device with an additional reference when successful,
 * or शून्य अगर the inode is alपढ़ोy beeing मुक्तd.
 */
काष्ठा block_device *bdgrab(काष्ठा block_device *bdev)
अणु
	अगर (!igrab(bdev->bd_inode))
		वापस शून्य;
	वापस bdev;
पूर्ण
EXPORT_SYMBOL(bdgrab);

दीर्घ nr_blockdev_pages(व्योम)
अणु
	काष्ठा inode *inode;
	दीर्घ ret = 0;

	spin_lock(&blockdev_superblock->s_inode_list_lock);
	list_क्रम_each_entry(inode, &blockdev_superblock->s_inodes, i_sb_list)
		ret += inode->i_mapping->nrpages;
	spin_unlock(&blockdev_superblock->s_inode_list_lock);

	वापस ret;
पूर्ण

व्योम bdput(काष्ठा block_device *bdev)
अणु
	iput(bdev->bd_inode);
पूर्ण
EXPORT_SYMBOL(bdput);
 
/**
 * bd_may_claim - test whether a block device can be claimed
 * @bdev: block device of पूर्णांकerest
 * @whole: whole block device containing @bdev, may equal @bdev
 * @holder: holder trying to claim @bdev
 *
 * Test whether @bdev can be claimed by @holder.
 *
 * CONTEXT:
 * spin_lock(&bdev_lock).
 *
 * RETURNS:
 * %true अगर @bdev can be claimed, %false otherwise.
 */
अटल bool bd_may_claim(काष्ठा block_device *bdev, काष्ठा block_device *whole,
			 व्योम *holder)
अणु
	अगर (bdev->bd_holder == holder)
		वापस true;	 /* alपढ़ोy a holder */
	अन्यथा अगर (bdev->bd_holder != शून्य)
		वापस false; 	 /* held by someone अन्यथा */
	अन्यथा अगर (whole == bdev)
		वापस true;  	 /* is a whole device which isn't held */

	अन्यथा अगर (whole->bd_holder == bd_may_claim)
		वापस true; 	 /* is a partition of a device that is being partitioned */
	अन्यथा अगर (whole->bd_holder != शून्य)
		वापस false;	 /* is a partition of a held device */
	अन्यथा
		वापस true;	 /* is a partition of an un-held device */
पूर्ण

/**
 * bd_prepare_to_claim - claim a block device
 * @bdev: block device of पूर्णांकerest
 * @holder: holder trying to claim @bdev
 *
 * Claim @bdev.  This function fails अगर @bdev is alपढ़ोy claimed by another
 * holder and रुकोs अगर another claiming is in progress. वापस, the caller
 * has ownership of bd_claiming and bd_holder[s].
 *
 * RETURNS:
 * 0 अगर @bdev can be claimed, -EBUSY otherwise.
 */
पूर्णांक bd_prepare_to_claim(काष्ठा block_device *bdev, व्योम *holder)
अणु
	काष्ठा block_device *whole = bdev_whole(bdev);

	अगर (WARN_ON_ONCE(!holder))
		वापस -EINVAL;
retry:
	spin_lock(&bdev_lock);
	/* अगर someone अन्यथा claimed, fail */
	अगर (!bd_may_claim(bdev, whole, holder)) अणु
		spin_unlock(&bdev_lock);
		वापस -EBUSY;
	पूर्ण

	/* अगर claiming is alपढ़ोy in progress, रुको क्रम it to finish */
	अगर (whole->bd_claiming) अणु
		रुको_queue_head_t *wq = bit_रुकोqueue(&whole->bd_claiming, 0);
		DEFINE_WAIT(रुको);

		prepare_to_रुको(wq, &रुको, TASK_UNINTERRUPTIBLE);
		spin_unlock(&bdev_lock);
		schedule();
		finish_रुको(wq, &रुको);
		जाओ retry;
	पूर्ण

	/* yay, all mine */
	whole->bd_claiming = holder;
	spin_unlock(&bdev_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bd_prepare_to_claim); /* only क्रम the loop driver */

अटल व्योम bd_clear_claiming(काष्ठा block_device *whole, व्योम *holder)
अणु
	lockdep_निश्चित_held(&bdev_lock);
	/* tell others that we're करोne */
	BUG_ON(whole->bd_claiming != holder);
	whole->bd_claiming = शून्य;
	wake_up_bit(&whole->bd_claiming, 0);
पूर्ण

/**
 * bd_finish_claiming - finish claiming of a block device
 * @bdev: block device of पूर्णांकerest
 * @holder: holder that has claimed @bdev
 *
 * Finish exclusive खोलो of a block device. Mark the device as exlusively
 * खोलो by the holder and wake up all रुकोers क्रम exclusive खोलो to finish.
 */
अटल व्योम bd_finish_claiming(काष्ठा block_device *bdev, व्योम *holder)
अणु
	काष्ठा block_device *whole = bdev_whole(bdev);

	spin_lock(&bdev_lock);
	BUG_ON(!bd_may_claim(bdev, whole, holder));
	/*
	 * Note that क्रम a whole device bd_holders will be incremented twice,
	 * and bd_holder will be set to bd_may_claim beक्रमe being set to holder
	 */
	whole->bd_holders++;
	whole->bd_holder = bd_may_claim;
	bdev->bd_holders++;
	bdev->bd_holder = holder;
	bd_clear_claiming(whole, holder);
	spin_unlock(&bdev_lock);
पूर्ण

/**
 * bd_पात_claiming - पात claiming of a block device
 * @bdev: block device of पूर्णांकerest
 * @holder: holder that has claimed @bdev
 *
 * Abort claiming of a block device when the exclusive खोलो failed. This can be
 * also used when exclusive खोलो is not actually desired and we just needed
 * to block other exclusive खोलोers क्रम a जबतक.
 */
व्योम bd_पात_claiming(काष्ठा block_device *bdev, व्योम *holder)
अणु
	spin_lock(&bdev_lock);
	bd_clear_claiming(bdev_whole(bdev), holder);
	spin_unlock(&bdev_lock);
पूर्ण
EXPORT_SYMBOL(bd_पात_claiming);

#अगर_घोषित CONFIG_SYSFS
काष्ठा bd_holder_disk अणु
	काष्ठा list_head	list;
	काष्ठा gendisk		*disk;
	पूर्णांक			refcnt;
पूर्ण;

अटल काष्ठा bd_holder_disk *bd_find_holder_disk(काष्ठा block_device *bdev,
						  काष्ठा gendisk *disk)
अणु
	काष्ठा bd_holder_disk *holder;

	list_क्रम_each_entry(holder, &bdev->bd_holder_disks, list)
		अगर (holder->disk == disk)
			वापस holder;
	वापस शून्य;
पूर्ण

अटल पूर्णांक add_symlink(काष्ठा kobject *from, काष्ठा kobject *to)
अणु
	वापस sysfs_create_link(from, to, kobject_name(to));
पूर्ण

अटल व्योम del_symlink(काष्ठा kobject *from, काष्ठा kobject *to)
अणु
	sysfs_हटाओ_link(from, kobject_name(to));
पूर्ण

/**
 * bd_link_disk_holder - create symlinks between holding disk and slave bdev
 * @bdev: the claimed slave bdev
 * @disk: the holding disk
 *
 * DON'T USE THIS UNLESS YOU'RE ALREADY USING IT.
 *
 * This functions creates the following sysfs symlinks.
 *
 * - from "slaves" directory of the holder @disk to the claimed @bdev
 * - from "holders" directory of the @bdev to the holder @disk
 *
 * For example, अगर /dev/dm-0 maps to /dev/sda and disk क्रम dm-0 is
 * passed to bd_link_disk_holder(), then:
 *
 *   /sys/block/dm-0/slaves/sda --> /sys/block/sda
 *   /sys/block/sda/holders/dm-0 --> /sys/block/dm-0
 *
 * The caller must have claimed @bdev beक्रमe calling this function and
 * ensure that both @bdev and @disk are valid during the creation and
 * lअगरeसमय of these symlinks.
 *
 * CONTEXT:
 * Might sleep.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक bd_link_disk_holder(काष्ठा block_device *bdev, काष्ठा gendisk *disk)
अणु
	काष्ठा bd_holder_disk *holder;
	पूर्णांक ret = 0;

	mutex_lock(&bdev->bd_mutex);

	WARN_ON_ONCE(!bdev->bd_holder);

	/* FIXME: हटाओ the following once add_disk() handles errors */
	अगर (WARN_ON(!disk->slave_dir || !bdev->bd_holder_dir))
		जाओ out_unlock;

	holder = bd_find_holder_disk(bdev, disk);
	अगर (holder) अणु
		holder->refcnt++;
		जाओ out_unlock;
	पूर्ण

	holder = kzalloc(माप(*holder), GFP_KERNEL);
	अगर (!holder) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	INIT_LIST_HEAD(&holder->list);
	holder->disk = disk;
	holder->refcnt = 1;

	ret = add_symlink(disk->slave_dir, bdev_kobj(bdev));
	अगर (ret)
		जाओ out_मुक्त;

	ret = add_symlink(bdev->bd_holder_dir, &disk_to_dev(disk)->kobj);
	अगर (ret)
		जाओ out_del;
	/*
	 * bdev could be deleted beneath us which would implicitly destroy
	 * the holder directory.  Hold on to it.
	 */
	kobject_get(bdev->bd_holder_dir);

	list_add(&holder->list, &bdev->bd_holder_disks);
	जाओ out_unlock;

out_del:
	del_symlink(disk->slave_dir, bdev_kobj(bdev));
out_मुक्त:
	kमुक्त(holder);
out_unlock:
	mutex_unlock(&bdev->bd_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bd_link_disk_holder);

/**
 * bd_unlink_disk_holder - destroy symlinks created by bd_link_disk_holder()
 * @bdev: the calimed slave bdev
 * @disk: the holding disk
 *
 * DON'T USE THIS UNLESS YOU'RE ALREADY USING IT.
 *
 * CONTEXT:
 * Might sleep.
 */
व्योम bd_unlink_disk_holder(काष्ठा block_device *bdev, काष्ठा gendisk *disk)
अणु
	काष्ठा bd_holder_disk *holder;

	mutex_lock(&bdev->bd_mutex);

	holder = bd_find_holder_disk(bdev, disk);

	अगर (!WARN_ON_ONCE(holder == शून्य) && !--holder->refcnt) अणु
		del_symlink(disk->slave_dir, bdev_kobj(bdev));
		del_symlink(bdev->bd_holder_dir, &disk_to_dev(disk)->kobj);
		kobject_put(bdev->bd_holder_dir);
		list_del_init(&holder->list);
		kमुक्त(holder);
	पूर्ण

	mutex_unlock(&bdev->bd_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(bd_unlink_disk_holder);
#पूर्ण_अगर

अटल व्योम __blkdev_put(काष्ठा block_device *bdev, भ_शेषe_t mode, पूर्णांक क्रम_part);

पूर्णांक bdev_disk_changed(काष्ठा block_device *bdev, bool invalidate)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&bdev->bd_mutex);

	अगर (!(disk->flags & GENHD_FL_UP))
		वापस -ENXIO;

rescan:
	अगर (bdev->bd_part_count)
		वापस -EBUSY;
	sync_blockdev(bdev);
	invalidate_bdev(bdev);
	blk_drop_partitions(disk);

	clear_bit(GD_NEED_PART_SCAN, &disk->state);

	/*
	 * Historically we only set the capacity to zero क्रम devices that
	 * support partitions (independ of actually having partitions created).
	 * Doing that is rather inconsistent, but changing it broke legacy
	 * udisks polling क्रम legacy ide-cdrom devices.  Use the crude check
	 * below to get the sane behavior क्रम most device जबतक not अवरोधing
	 * userspace क्रम this particular setup.
	 */
	अगर (invalidate) अणु
		अगर (disk_part_scan_enabled(disk) ||
		    !(disk->flags & GENHD_FL_REMOVABLE))
			set_capacity(disk, 0);
	पूर्ण

	अगर (get_capacity(disk)) अणु
		ret = blk_add_partitions(disk, bdev);
		अगर (ret == -EAGAIN)
			जाओ rescan;
	पूर्ण अन्यथा अगर (invalidate) अणु
		/*
		 * Tell userspace that the media / partition table may have
		 * changed.
		 */
		kobject_uevent(&disk_to_dev(disk)->kobj, KOBJ_CHANGE);
	पूर्ण

	वापस ret;
पूर्ण
/*
 * Only exported क्रम loop and dasd क्रम historic reasons.  Don't use in new
 * code!
 */
EXPORT_SYMBOL_GPL(bdev_disk_changed);

/*
 * bd_mutex locking:
 *
 *  mutex_lock(part->bd_mutex)
 *    mutex_lock_nested(whole->bd_mutex, 1)
 */
अटल पूर्णांक __blkdev_get(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	पूर्णांक ret = 0;

	अगर (!(disk->flags & GENHD_FL_UP))
		वापस -ENXIO;

	अगर (!bdev->bd_खोलोers) अणु
		अगर (!bdev_is_partition(bdev)) अणु
			ret = 0;
			अगर (disk->fops->खोलो)
				ret = disk->fops->खोलो(bdev, mode);

			अगर (!ret)
				set_init_blocksize(bdev);

			/*
			 * If the device is invalidated, rescan partition
			 * अगर खोलो succeeded or failed with -ENOMEDIUM.
			 * The latter is necessary to prevent ghost
			 * partitions on a हटाओd medium.
			 */
			अगर (test_bit(GD_NEED_PART_SCAN, &disk->state) &&
			    (!ret || ret == -ENOMEDIUM))
				bdev_disk_changed(bdev, ret == -ENOMEDIUM);

			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			काष्ठा block_device *whole = bdgrab(disk->part0);

			mutex_lock_nested(&whole->bd_mutex, 1);
			ret = __blkdev_get(whole, mode);
			अगर (ret) अणु
				mutex_unlock(&whole->bd_mutex);
				bdput(whole);
				वापस ret;
			पूर्ण
			whole->bd_part_count++;
			mutex_unlock(&whole->bd_mutex);

			अगर (!bdev_nr_sectors(bdev)) अणु
				__blkdev_put(whole, mode, 1);
				bdput(whole);
				वापस -ENXIO;
			पूर्ण
			set_init_blocksize(bdev);
		पूर्ण

		अगर (bdev->bd_bdi == &noop_backing_dev_info)
			bdev->bd_bdi = bdi_get(disk->queue->backing_dev_info);
	पूर्ण अन्यथा अणु
		अगर (!bdev_is_partition(bdev)) अणु
			अगर (bdev->bd_disk->fops->खोलो)
				ret = bdev->bd_disk->fops->खोलो(bdev, mode);
			/* the same as first खोलोer हाल, पढ़ो comment there */
			अगर (test_bit(GD_NEED_PART_SCAN, &disk->state) &&
			    (!ret || ret == -ENOMEDIUM))
				bdev_disk_changed(bdev, ret == -ENOMEDIUM);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
	bdev->bd_खोलोers++;
	वापस 0;
पूर्ण

काष्ठा block_device *blkdev_get_no_खोलो(dev_t dev)
अणु
	काष्ठा block_device *bdev;
	काष्ठा gendisk *disk;

	bdev = bdget(dev);
	अगर (!bdev) अणु
		blk_request_module(dev);
		bdev = bdget(dev);
		अगर (!bdev)
			वापस शून्य;
	पूर्ण

	disk = bdev->bd_disk;
	अगर (!kobject_get_unless_zero(&disk_to_dev(disk)->kobj))
		जाओ bdput;
	अगर ((disk->flags & (GENHD_FL_UP | GENHD_FL_HIDDEN)) != GENHD_FL_UP)
		जाओ put_disk;
	अगर (!try_module_get(bdev->bd_disk->fops->owner))
		जाओ put_disk;
	वापस bdev;
put_disk:
	put_disk(disk);
bdput:
	bdput(bdev);
	वापस शून्य;
पूर्ण

व्योम blkdev_put_no_खोलो(काष्ठा block_device *bdev)
अणु
	module_put(bdev->bd_disk->fops->owner);
	put_disk(bdev->bd_disk);
	bdput(bdev);
पूर्ण

/**
 * blkdev_get_by_dev - खोलो a block device by device number
 * @dev: device number of block device to खोलो
 * @mode: FMODE_* mask
 * @holder: exclusive holder identअगरier
 *
 * Open the block device described by device number @dev. If @mode includes
 * %FMODE_EXCL, the block device is खोलोed with exclusive access.  Specअगरying
 * %FMODE_EXCL with a %शून्य @holder is invalid.  Exclusive खोलोs may nest क्रम
 * the same @holder.
 *
 * Use this पूर्णांकerface ONLY अगर you really करो not have anything better - i.e. when
 * you are behind a truly sucky पूर्णांकerface and all you are given is a device
 * number.  Everything अन्यथा should use blkdev_get_by_path().
 *
 * CONTEXT:
 * Might sleep.
 *
 * RETURNS:
 * Reference to the block_device on success, ERR_PTR(-त्रुटि_सं) on failure.
 */
काष्ठा block_device *blkdev_get_by_dev(dev_t dev, भ_शेषe_t mode, व्योम *holder)
अणु
	bool unblock_events = true;
	काष्ठा block_device *bdev;
	काष्ठा gendisk *disk;
	पूर्णांक ret;

	ret = devcgroup_check_permission(DEVCG_DEV_BLOCK,
			MAJOR(dev), MINOR(dev),
			((mode & FMODE_READ) ? DEVCG_ACC_READ : 0) |
			((mode & FMODE_WRITE) ? DEVCG_ACC_WRITE : 0));
	अगर (ret)
		वापस ERR_PTR(ret);

	bdev = blkdev_get_no_खोलो(dev);
	अगर (!bdev)
		वापस ERR_PTR(-ENXIO);
	disk = bdev->bd_disk;

	अगर (mode & FMODE_EXCL) अणु
		ret = bd_prepare_to_claim(bdev, holder);
		अगर (ret)
			जाओ put_blkdev;
	पूर्ण

	disk_block_events(disk);

	mutex_lock(&bdev->bd_mutex);
	ret =__blkdev_get(bdev, mode);
	अगर (ret)
		जाओ पात_claiming;
	अगर (mode & FMODE_EXCL) अणु
		bd_finish_claiming(bdev, holder);

		/*
		 * Block event polling क्रम ग_लिखो claims अगर requested.  Any ग_लिखो
		 * holder makes the ग_लिखो_holder state stick until all are
		 * released.  This is good enough and tracking inभागidual
		 * ग_लिखोable reference is too fragile given the way @mode is
		 * used in blkdev_get/put().
		 */
		अगर ((mode & FMODE_WRITE) && !bdev->bd_ग_लिखो_holder &&
		    (disk->flags & GENHD_FL_BLOCK_EVENTS_ON_EXCL_WRITE)) अणु
			bdev->bd_ग_लिखो_holder = true;
			unblock_events = false;
		पूर्ण
	पूर्ण
	mutex_unlock(&bdev->bd_mutex);

	अगर (unblock_events)
		disk_unblock_events(disk);
	वापस bdev;

पात_claiming:
	अगर (mode & FMODE_EXCL)
		bd_पात_claiming(bdev, holder);
	mutex_unlock(&bdev->bd_mutex);
	disk_unblock_events(disk);
put_blkdev:
	blkdev_put_no_खोलो(bdev);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(blkdev_get_by_dev);

/**
 * blkdev_get_by_path - खोलो a block device by name
 * @path: path to the block device to खोलो
 * @mode: FMODE_* mask
 * @holder: exclusive holder identअगरier
 *
 * Open the block device described by the device file at @path.  If @mode
 * includes %FMODE_EXCL, the block device is खोलोed with exclusive access.
 * Specअगरying %FMODE_EXCL with a %शून्य @holder is invalid.  Exclusive खोलोs may
 * nest क्रम the same @holder.
 *
 * CONTEXT:
 * Might sleep.
 *
 * RETURNS:
 * Reference to the block_device on success, ERR_PTR(-त्रुटि_सं) on failure.
 */
काष्ठा block_device *blkdev_get_by_path(स्थिर अक्षर *path, भ_शेषe_t mode,
					व्योम *holder)
अणु
	काष्ठा block_device *bdev;
	dev_t dev;
	पूर्णांक error;

	error = lookup_bdev(path, &dev);
	अगर (error)
		वापस ERR_PTR(error);

	bdev = blkdev_get_by_dev(dev, mode, holder);
	अगर (!IS_ERR(bdev) && (mode & FMODE_WRITE) && bdev_पढ़ो_only(bdev)) अणु
		blkdev_put(bdev, mode);
		वापस ERR_PTR(-EACCES);
	पूर्ण

	वापस bdev;
पूर्ण
EXPORT_SYMBOL(blkdev_get_by_path);

अटल पूर्णांक blkdev_खोलो(काष्ठा inode * inode, काष्ठा file * filp)
अणु
	काष्ठा block_device *bdev;

	/*
	 * Preserve backwards compatibility and allow large file access
	 * even अगर userspace करोesn't ask क्रम it explicitly. Some mkfs
	 * binary needs it. We might want to drop this workaround
	 * during an unstable branch.
	 */
	filp->f_flags |= O_LARGEखाता;

	filp->f_mode |= FMODE_NOWAIT | FMODE_BUF_RASYNC;

	अगर (filp->f_flags & O_NDELAY)
		filp->f_mode |= FMODE_NDELAY;
	अगर (filp->f_flags & O_EXCL)
		filp->f_mode |= FMODE_EXCL;
	अगर ((filp->f_flags & O_ACCMODE) == 3)
		filp->f_mode |= FMODE_WRITE_IOCTL;

	bdev = blkdev_get_by_dev(inode->i_rdev, filp->f_mode, filp);
	अगर (IS_ERR(bdev))
		वापस PTR_ERR(bdev);
	filp->f_mapping = bdev->bd_inode->i_mapping;
	filp->f_wb_err = filemap_sample_wb_err(filp->f_mapping);
	वापस 0;
पूर्ण

अटल व्योम __blkdev_put(काष्ठा block_device *bdev, भ_शेषe_t mode, पूर्णांक क्रम_part)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	काष्ठा block_device *victim = शून्य;

	/*
	 * Sync early अगर it looks like we're the last one.  If someone अन्यथा
	 * खोलोs the block device between now and the decrement of bd_खोलोers
	 * then we did a sync that we didn't need to, but that's not the end
	 * of the world and we want to aव्योम दीर्घ (could be several minute)
	 * syncs जबतक holding the mutex.
	 */
	अगर (bdev->bd_खोलोers == 1)
		sync_blockdev(bdev);

	mutex_lock_nested(&bdev->bd_mutex, क्रम_part);
	अगर (क्रम_part)
		bdev->bd_part_count--;

	अगर (!--bdev->bd_खोलोers) अणु
		WARN_ON_ONCE(bdev->bd_holders);
		sync_blockdev(bdev);
		समाप्त_bdev(bdev);
		bdev_ग_लिखो_inode(bdev);
		अगर (bdev_is_partition(bdev))
			victim = bdev_whole(bdev);
	पूर्ण

	अगर (!bdev_is_partition(bdev) && disk->fops->release)
		disk->fops->release(disk, mode);
	mutex_unlock(&bdev->bd_mutex);
	अगर (victim) अणु
		__blkdev_put(victim, mode, 1);
		bdput(victim);
	पूर्ण
पूर्ण

व्योम blkdev_put(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;

	mutex_lock(&bdev->bd_mutex);

	अगर (mode & FMODE_EXCL) अणु
		काष्ठा block_device *whole = bdev_whole(bdev);
		bool bdev_मुक्त;

		/*
		 * Release a claim on the device.  The holder fields
		 * are रक्षित with bdev_lock.  bd_mutex is to
		 * synchronize disk_holder unlinking.
		 */
		spin_lock(&bdev_lock);

		WARN_ON_ONCE(--bdev->bd_holders < 0);
		WARN_ON_ONCE(--whole->bd_holders < 0);

		अगर ((bdev_मुक्त = !bdev->bd_holders))
			bdev->bd_holder = शून्य;
		अगर (!whole->bd_holders)
			whole->bd_holder = शून्य;

		spin_unlock(&bdev_lock);

		/*
		 * If this was the last claim, हटाओ holder link and
		 * unblock evpoll अगर it was a ग_लिखो holder.
		 */
		अगर (bdev_मुक्त && bdev->bd_ग_लिखो_holder) अणु
			disk_unblock_events(disk);
			bdev->bd_ग_लिखो_holder = false;
		पूर्ण
	पूर्ण

	/*
	 * Trigger event checking and tell drivers to flush MEDIA_CHANGE
	 * event.  This is to ensure detection of media removal commanded
	 * from userland - e.g. eject(1).
	 */
	disk_flush_events(disk, DISK_EVENT_MEDIA_CHANGE);
	mutex_unlock(&bdev->bd_mutex);

	__blkdev_put(bdev, mode, 0);
	blkdev_put_no_खोलो(bdev);
पूर्ण
EXPORT_SYMBOL(blkdev_put);

अटल पूर्णांक blkdev_बंद(काष्ठा inode * inode, काष्ठा file * filp)
अणु
	काष्ठा block_device *bdev = I_BDEV(bdev_file_inode(filp));
	blkdev_put(bdev, filp->f_mode);
	वापस 0;
पूर्ण

अटल दीर्घ block_ioctl(काष्ठा file *file, अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा block_device *bdev = I_BDEV(bdev_file_inode(file));
	भ_शेषe_t mode = file->f_mode;

	/*
	 * O_NDELAY can be altered using fcntl(.., F_SETFL, ..), so we have
	 * to updated it beक्रमe every ioctl.
	 */
	अगर (file->f_flags & O_NDELAY)
		mode |= FMODE_NDELAY;
	अन्यथा
		mode &= ~FMODE_NDELAY;

	वापस blkdev_ioctl(bdev, mode, cmd, arg);
पूर्ण

/*
 * Write data to the block device.  Only पूर्णांकended क्रम the block device itself
 * and the raw driver which basically is a fake block device.
 *
 * Does not take i_mutex क्रम the ग_लिखो and thus is not क्रम general purpose
 * use.
 */
sमाप_प्रकार blkdev_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *bd_inode = bdev_file_inode(file);
	loff_t size = i_size_पढ़ो(bd_inode);
	काष्ठा blk_plug plug;
	माप_प्रकार लघुed = 0;
	sमाप_प्रकार ret;

	अगर (bdev_पढ़ो_only(I_BDEV(bd_inode)))
		वापस -EPERM;

	अगर (IS_SWAPखाता(bd_inode) && !is_hibernate_resume_dev(bd_inode->i_rdev))
		वापस -ETXTBSY;

	अगर (!iov_iter_count(from))
		वापस 0;

	अगर (iocb->ki_pos >= size)
		वापस -ENOSPC;

	अगर ((iocb->ki_flags & (IOCB_NOWAIT | IOCB_सूचीECT)) == IOCB_NOWAIT)
		वापस -EOPNOTSUPP;

	size -= iocb->ki_pos;
	अगर (iov_iter_count(from) > size) अणु
		लघुed = iov_iter_count(from) - size;
		iov_iter_truncate(from, size);
	पूर्ण

	blk_start_plug(&plug);
	ret = __generic_file_ग_लिखो_iter(iocb, from);
	अगर (ret > 0)
		ret = generic_ग_लिखो_sync(iocb, ret);
	iov_iter_reexpand(from, iov_iter_count(from) + लघुed);
	blk_finish_plug(&plug);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blkdev_ग_लिखो_iter);

sमाप_प्रकार blkdev_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *bd_inode = bdev_file_inode(file);
	loff_t size = i_size_पढ़ो(bd_inode);
	loff_t pos = iocb->ki_pos;
	माप_प्रकार लघुed = 0;
	sमाप_प्रकार ret;

	अगर (pos >= size)
		वापस 0;

	size -= pos;
	अगर (iov_iter_count(to) > size) अणु
		लघुed = iov_iter_count(to) - size;
		iov_iter_truncate(to, size);
	पूर्ण

	ret = generic_file_पढ़ो_iter(iocb, to);
	iov_iter_reexpand(to, iov_iter_count(to) + लघुed);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blkdev_पढ़ो_iter);

/*
 * Try to release a page associated with block device when the प्रणाली
 * is under memory pressure.
 */
अटल पूर्णांक blkdev_releasepage(काष्ठा page *page, gfp_t रुको)
अणु
	काष्ठा super_block *super = BDEV_I(page->mapping->host)->bdev.bd_super;

	अगर (super && super->s_op->bdev_try_to_मुक्त_page)
		वापस super->s_op->bdev_try_to_मुक्त_page(super, page, रुको);

	वापस try_to_मुक्त_buffers(page);
पूर्ण

अटल पूर्णांक blkdev_ग_लिखोpages(काष्ठा address_space *mapping,
			     काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस generic_ग_लिखोpages(mapping, wbc);
पूर्ण

अटल स्थिर काष्ठा address_space_operations def_blk_aops = अणु
	.पढ़ोpage	= blkdev_पढ़ोpage,
	.पढ़ोahead	= blkdev_पढ़ोahead,
	.ग_लिखोpage	= blkdev_ग_लिखोpage,
	.ग_लिखो_begin	= blkdev_ग_लिखो_begin,
	.ग_लिखो_end	= blkdev_ग_लिखो_end,
	.ग_लिखोpages	= blkdev_ग_लिखोpages,
	.releasepage	= blkdev_releasepage,
	.direct_IO	= blkdev_direct_IO,
	.migratepage	= buffer_migrate_page_norefs,
	.is_dirty_ग_लिखोback = buffer_check_dirty_ग_लिखोback,
पूर्ण;

#घोषणा	BLKDEV_FALLOC_FL_SUPPORTED					\
		(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE |		\
		 FALLOC_FL_ZERO_RANGE | FALLOC_FL_NO_HIDE_STALE)

अटल दीर्घ blkdev_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t start,
			     loff_t len)
अणु
	काष्ठा block_device *bdev = I_BDEV(bdev_file_inode(file));
	loff_t end = start + len - 1;
	loff_t isize;
	पूर्णांक error;

	/* Fail अगर we करोn't recognize the flags. */
	अगर (mode & ~BLKDEV_FALLOC_FL_SUPPORTED)
		वापस -EOPNOTSUPP;

	/* Don't go off the end of the device. */
	isize = i_size_पढ़ो(bdev->bd_inode);
	अगर (start >= isize)
		वापस -EINVAL;
	अगर (end >= isize) अणु
		अगर (mode & FALLOC_FL_KEEP_SIZE) अणु
			len = isize - start;
			end = start + len - 1;
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण

	/*
	 * Don't allow IO that isn't aligned to logical block size.
	 */
	अगर ((start | len) & (bdev_logical_block_size(bdev) - 1))
		वापस -EINVAL;

	/* Invalidate the page cache, including dirty pages. */
	error = truncate_bdev_range(bdev, file->f_mode, start, end);
	अगर (error)
		वापस error;

	चयन (mode) अणु
	हाल FALLOC_FL_ZERO_RANGE:
	हाल FALLOC_FL_ZERO_RANGE | FALLOC_FL_KEEP_SIZE:
		error = blkdev_issue_zeroout(bdev, start >> 9, len >> 9,
					    GFP_KERNEL, BLKDEV_ZERO_NOUNMAP);
		अवरोध;
	हाल FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE:
		error = blkdev_issue_zeroout(bdev, start >> 9, len >> 9,
					     GFP_KERNEL, BLKDEV_ZERO_NOFALLBACK);
		अवरोध;
	हाल FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE | FALLOC_FL_NO_HIDE_STALE:
		error = blkdev_issue_discard(bdev, start >> 9, len >> 9,
					     GFP_KERNEL, 0);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (error)
		वापस error;

	/*
	 * Invalidate the page cache again; अगर someone wandered in and dirtied
	 * a page, we just discard it - userspace has no way of knowing whether
	 * the ग_लिखो happened beक्रमe or after discard completing...
	 */
	वापस truncate_bdev_range(bdev, file->f_mode, start, end);
पूर्ण

स्थिर काष्ठा file_operations def_blk_fops = अणु
	.खोलो		= blkdev_खोलो,
	.release	= blkdev_बंद,
	.llseek		= block_llseek,
	.पढ़ो_iter	= blkdev_पढ़ो_iter,
	.ग_लिखो_iter	= blkdev_ग_लिखो_iter,
	.iopoll		= blkdev_iopoll,
	.mmap		= generic_file_mmap,
	.fsync		= blkdev_fsync,
	.unlocked_ioctl	= block_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= compat_blkdev_ioctl,
#पूर्ण_अगर
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.fallocate	= blkdev_fallocate,
पूर्ण;

/**
 * lookup_bdev  - lookup a काष्ठा block_device by name
 * @pathname:	special file representing the block device
 * @dev:	वापस value of the block device's dev_t
 *
 * Get a reference to the blockdevice at @pathname in the current
 * namespace अगर possible and वापस it.  Return ERR_PTR(error)
 * otherwise.
 */
पूर्णांक lookup_bdev(स्थिर अक्षर *pathname, dev_t *dev)
अणु
	काष्ठा inode *inode;
	काष्ठा path path;
	पूर्णांक error;

	अगर (!pathname || !*pathname)
		वापस -EINVAL;

	error = kern_path(pathname, LOOKUP_FOLLOW, &path);
	अगर (error)
		वापस error;

	inode = d_backing_inode(path.dentry);
	error = -ENOTBLK;
	अगर (!S_ISBLK(inode->i_mode))
		जाओ out_path_put;
	error = -EACCES;
	अगर (!may_खोलो_dev(&path))
		जाओ out_path_put;

	*dev = inode->i_rdev;
	error = 0;
out_path_put:
	path_put(&path);
	वापस error;
पूर्ण
EXPORT_SYMBOL(lookup_bdev);

पूर्णांक __invalidate_device(काष्ठा block_device *bdev, bool समाप्त_dirty)
अणु
	काष्ठा super_block *sb = get_super(bdev);
	पूर्णांक res = 0;

	अगर (sb) अणु
		/*
		 * no need to lock the super, get_super holds the
		 * पढ़ो mutex so the fileप्रणाली cannot go away
		 * under us (->put_super runs with the ग_लिखो lock
		 * hold).
		 */
		shrink_dcache_sb(sb);
		res = invalidate_inodes(sb, समाप्त_dirty);
		drop_super(sb);
	पूर्ण
	invalidate_bdev(bdev);
	वापस res;
पूर्ण
EXPORT_SYMBOL(__invalidate_device);

व्योम iterate_bdevs(व्योम (*func)(काष्ठा block_device *, व्योम *), व्योम *arg)
अणु
	काष्ठा inode *inode, *old_inode = शून्य;

	spin_lock(&blockdev_superblock->s_inode_list_lock);
	list_क्रम_each_entry(inode, &blockdev_superblock->s_inodes, i_sb_list) अणु
		काष्ठा address_space *mapping = inode->i_mapping;
		काष्ठा block_device *bdev;

		spin_lock(&inode->i_lock);
		अगर (inode->i_state & (I_FREEING|I_WILL_FREE|I_NEW) ||
		    mapping->nrpages == 0) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण
		__iget(inode);
		spin_unlock(&inode->i_lock);
		spin_unlock(&blockdev_superblock->s_inode_list_lock);
		/*
		 * We hold a reference to 'inode' so it couldn't have been
		 * हटाओd from s_inodes list जबतक we dropped the
		 * s_inode_list_lock  We cannot iput the inode now as we can
		 * be holding the last reference and we cannot iput it under
		 * s_inode_list_lock. So we keep the reference and iput it
		 * later.
		 */
		iput(old_inode);
		old_inode = inode;
		bdev = I_BDEV(inode);

		mutex_lock(&bdev->bd_mutex);
		अगर (bdev->bd_खोलोers)
			func(bdev, arg);
		mutex_unlock(&bdev->bd_mutex);

		spin_lock(&blockdev_superblock->s_inode_list_lock);
	पूर्ण
	spin_unlock(&blockdev_superblock->s_inode_list_lock);
	iput(old_inode);
पूर्ण
