<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext4/page-io.c
 *
 * This contains the new page_io functions क्रम ext4
 *
 * Written by Theoकरोre Ts'o, 2010.
 */

#समावेश <linux/fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/highuid.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/माला.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/mpage.h>
#समावेश <linux/namei.h>
#समावेश <linux/uपन.स>
#समावेश <linux/bपन.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/backing-dev.h>

#समावेश "ext4_jbd2.h"
#समावेश "xattr.h"
#समावेश "acl.h"

अटल काष्ठा kmem_cache *io_end_cachep;
अटल काष्ठा kmem_cache *io_end_vec_cachep;

पूर्णांक __init ext4_init_pageio(व्योम)
अणु
	io_end_cachep = KMEM_CACHE(ext4_io_end, SLAB_RECLAIM_ACCOUNT);
	अगर (io_end_cachep == शून्य)
		वापस -ENOMEM;

	io_end_vec_cachep = KMEM_CACHE(ext4_io_end_vec, 0);
	अगर (io_end_vec_cachep == शून्य) अणु
		kmem_cache_destroy(io_end_cachep);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम ext4_निकास_pageio(व्योम)
अणु
	kmem_cache_destroy(io_end_cachep);
	kmem_cache_destroy(io_end_vec_cachep);
पूर्ण

काष्ठा ext4_io_end_vec *ext4_alloc_io_end_vec(ext4_io_end_t *io_end)
अणु
	काष्ठा ext4_io_end_vec *io_end_vec;

	io_end_vec = kmem_cache_zalloc(io_end_vec_cachep, GFP_NOFS);
	अगर (!io_end_vec)
		वापस ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&io_end_vec->list);
	list_add_tail(&io_end_vec->list, &io_end->list_vec);
	वापस io_end_vec;
पूर्ण

अटल व्योम ext4_मुक्त_io_end_vec(ext4_io_end_t *io_end)
अणु
	काष्ठा ext4_io_end_vec *io_end_vec, *पंचांगp;

	अगर (list_empty(&io_end->list_vec))
		वापस;
	list_क्रम_each_entry_safe(io_end_vec, पंचांगp, &io_end->list_vec, list) अणु
		list_del(&io_end_vec->list);
		kmem_cache_मुक्त(io_end_vec_cachep, io_end_vec);
	पूर्ण
पूर्ण

काष्ठा ext4_io_end_vec *ext4_last_io_end_vec(ext4_io_end_t *io_end)
अणु
	BUG_ON(list_empty(&io_end->list_vec));
	वापस list_last_entry(&io_end->list_vec, काष्ठा ext4_io_end_vec, list);
पूर्ण

/*
 * Prपूर्णांक an buffer I/O error compatible with the fs/buffer.c.  This
 * provides compatibility with dmesg scrapers that look क्रम a specअगरic
 * buffer I/O error message.  We really need a unअगरied error reporting
 * काष्ठाure to userspace ala Digital Unix's uerf system, but it's
 * probably not going to happen in my lअगरeसमय, due to LKML politics...
 */
अटल व्योम buffer_io_error(काष्ठा buffer_head *bh)
अणु
	prपूर्णांकk_ratelimited(KERN_ERR "Buffer I/O error on device %pg, logical block %llu\n",
		       bh->b_bdev,
			(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
पूर्ण

अटल व्योम ext4_finish_bio(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		काष्ठा page *page = bvec->bv_page;
		काष्ठा page *bounce_page = शून्य;
		काष्ठा buffer_head *bh, *head;
		अचिन्हित bio_start = bvec->bv_offset;
		अचिन्हित bio_end = bio_start + bvec->bv_len;
		अचिन्हित under_io = 0;
		अचिन्हित दीर्घ flags;

		अगर (fscrypt_is_bounce_page(page)) अणु
			bounce_page = page;
			page = fscrypt_pagecache_page(bounce_page);
		पूर्ण

		अगर (bio->bi_status) अणु
			SetPageError(page);
			mapping_set_error(page->mapping, -EIO);
		पूर्ण
		bh = head = page_buffers(page);
		/*
		 * We check all buffers in the page under b_uptodate_lock
		 * to aव्योम races with other end io clearing async_ग_लिखो flags
		 */
		spin_lock_irqsave(&head->b_uptodate_lock, flags);
		करो अणु
			अगर (bh_offset(bh) < bio_start ||
			    bh_offset(bh) + bh->b_size > bio_end) अणु
				अगर (buffer_async_ग_लिखो(bh))
					under_io++;
				जारी;
			पूर्ण
			clear_buffer_async_ग_लिखो(bh);
			अगर (bio->bi_status)
				buffer_io_error(bh);
		पूर्ण जबतक ((bh = bh->b_this_page) != head);
		spin_unlock_irqrestore(&head->b_uptodate_lock, flags);
		अगर (!under_io) अणु
			fscrypt_मुक्त_bounce_page(bounce_page);
			end_page_ग_लिखोback(page);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ext4_release_io_end(ext4_io_end_t *io_end)
अणु
	काष्ठा bio *bio, *next_bio;

	BUG_ON(!list_empty(&io_end->list));
	BUG_ON(io_end->flag & EXT4_IO_END_UNWRITTEN);
	WARN_ON(io_end->handle);

	क्रम (bio = io_end->bio; bio; bio = next_bio) अणु
		next_bio = bio->bi_निजी;
		ext4_finish_bio(bio);
		bio_put(bio);
	पूर्ण
	ext4_मुक्त_io_end_vec(io_end);
	kmem_cache_मुक्त(io_end_cachep, io_end);
पूर्ण

/*
 * Check a range of space and convert unwritten extents to written. Note that
 * we are रक्षित from truncate touching same part of extent tree by the
 * fact that truncate code रुकोs क्रम all DIO to finish (thus exclusion from
 * direct IO is achieved) and also रुकोs क्रम PageWriteback bits. Thus we
 * cannot get to ext4_ext_truncate() beक्रमe all IOs overlapping that range are
 * completed (happens from ext4_मुक्त_ioend()).
 */
अटल पूर्णांक ext4_end_io_end(ext4_io_end_t *io_end)
अणु
	काष्ठा inode *inode = io_end->inode;
	handle_t *handle = io_end->handle;
	पूर्णांक ret = 0;

	ext4_debug("ext4_end_io_nolock: io_end 0x%p from inode %lu,list->next 0x%p,"
		   "list->prev 0x%p\n",
		   io_end, inode->i_ino, io_end->list.next, io_end->list.prev);

	io_end->handle = शून्य;	/* Following call will use up the handle */
	ret = ext4_convert_unwritten_io_end_vec(handle, io_end);
	अगर (ret < 0 && !ext4_क्रमced_shutकरोwn(EXT4_SB(inode->i_sb))) अणु
		ext4_msg(inode->i_sb, KERN_EMERG,
			 "failed to convert unwritten extents to written "
			 "extents -- potential data loss!  "
			 "(inode %lu, error %d)", inode->i_ino, ret);
	पूर्ण
	ext4_clear_io_unwritten_flag(io_end);
	ext4_release_io_end(io_end);
	वापस ret;
पूर्ण

अटल व्योम dump_completed_IO(काष्ठा inode *inode, काष्ठा list_head *head)
अणु
#अगर_घोषित	EXT4FS_DEBUG
	काष्ठा list_head *cur, *beक्रमe, *after;
	ext4_io_end_t *io_end, *io_end0, *io_end1;

	अगर (list_empty(head))
		वापस;

	ext4_debug("Dump inode %lu completed io list\n", inode->i_ino);
	list_क्रम_each_entry(io_end, head, list) अणु
		cur = &io_end->list;
		beक्रमe = cur->prev;
		io_end0 = container_of(beक्रमe, ext4_io_end_t, list);
		after = cur->next;
		io_end1 = container_of(after, ext4_io_end_t, list);

		ext4_debug("io 0x%p from inode %lu,prev 0x%p,next 0x%p\n",
			    io_end, inode->i_ino, io_end0, io_end1);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/* Add the io_end to per-inode completed end_io list. */
अटल व्योम ext4_add_complete_io(ext4_io_end_t *io_end)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(io_end->inode);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(io_end->inode->i_sb);
	काष्ठा workqueue_काष्ठा *wq;
	अचिन्हित दीर्घ flags;

	/* Only reserved conversions from ग_लिखोback should enter here */
	WARN_ON(!(io_end->flag & EXT4_IO_END_UNWRITTEN));
	WARN_ON(!io_end->handle && sbi->s_journal);
	spin_lock_irqsave(&ei->i_completed_io_lock, flags);
	wq = sbi->rsv_conversion_wq;
	अगर (list_empty(&ei->i_rsv_conversion_list))
		queue_work(wq, &ei->i_rsv_conversion_work);
	list_add_tail(&io_end->list, &ei->i_rsv_conversion_list);
	spin_unlock_irqrestore(&ei->i_completed_io_lock, flags);
पूर्ण

अटल पूर्णांक ext4_करो_flush_completed_IO(काष्ठा inode *inode,
				      काष्ठा list_head *head)
अणु
	ext4_io_end_t *io_end;
	काष्ठा list_head unwritten;
	अचिन्हित दीर्घ flags;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	पूर्णांक err, ret = 0;

	spin_lock_irqsave(&ei->i_completed_io_lock, flags);
	dump_completed_IO(inode, head);
	list_replace_init(head, &unwritten);
	spin_unlock_irqrestore(&ei->i_completed_io_lock, flags);

	जबतक (!list_empty(&unwritten)) अणु
		io_end = list_entry(unwritten.next, ext4_io_end_t, list);
		BUG_ON(!(io_end->flag & EXT4_IO_END_UNWRITTEN));
		list_del_init(&io_end->list);

		err = ext4_end_io_end(io_end);
		अगर (unlikely(!ret && err))
			ret = err;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * work on completed IO, to convert unwritten extents to extents
 */
व्योम ext4_end_io_rsv_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ext4_inode_info *ei = container_of(work, काष्ठा ext4_inode_info,
						  i_rsv_conversion_work);
	ext4_करो_flush_completed_IO(&ei->vfs_inode, &ei->i_rsv_conversion_list);
पूर्ण

ext4_io_end_t *ext4_init_io_end(काष्ठा inode *inode, gfp_t flags)
अणु
	ext4_io_end_t *io_end = kmem_cache_zalloc(io_end_cachep, flags);

	अगर (io_end) अणु
		io_end->inode = inode;
		INIT_LIST_HEAD(&io_end->list);
		INIT_LIST_HEAD(&io_end->list_vec);
		atomic_set(&io_end->count, 1);
	पूर्ण
	वापस io_end;
पूर्ण

व्योम ext4_put_io_end_defer(ext4_io_end_t *io_end)
अणु
	अगर (atomic_dec_and_test(&io_end->count)) अणु
		अगर (!(io_end->flag & EXT4_IO_END_UNWRITTEN) ||
				list_empty(&io_end->list_vec)) अणु
			ext4_release_io_end(io_end);
			वापस;
		पूर्ण
		ext4_add_complete_io(io_end);
	पूर्ण
पूर्ण

पूर्णांक ext4_put_io_end(ext4_io_end_t *io_end)
अणु
	पूर्णांक err = 0;

	अगर (atomic_dec_and_test(&io_end->count)) अणु
		अगर (io_end->flag & EXT4_IO_END_UNWRITTEN) अणु
			err = ext4_convert_unwritten_io_end_vec(io_end->handle,
								io_end);
			io_end->handle = शून्य;
			ext4_clear_io_unwritten_flag(io_end);
		पूर्ण
		ext4_release_io_end(io_end);
	पूर्ण
	वापस err;
पूर्ण

ext4_io_end_t *ext4_get_io_end(ext4_io_end_t *io_end)
अणु
	atomic_inc(&io_end->count);
	वापस io_end;
पूर्ण

/* BIO completion function क्रम page ग_लिखोback */
अटल व्योम ext4_end_bio(काष्ठा bio *bio)
अणु
	ext4_io_end_t *io_end = bio->bi_निजी;
	sector_t bi_sector = bio->bi_iter.bi_sector;
	अक्षर b[BDEVNAME_SIZE];

	अगर (WARN_ONCE(!io_end, "io_end is NULL: %s: sector %Lu len %u err %d\n",
		      bio_devname(bio, b),
		      (दीर्घ दीर्घ) bio->bi_iter.bi_sector,
		      (अचिन्हित) bio_sectors(bio),
		      bio->bi_status)) अणु
		ext4_finish_bio(bio);
		bio_put(bio);
		वापस;
	पूर्ण
	bio->bi_end_io = शून्य;

	अगर (bio->bi_status) अणु
		काष्ठा inode *inode = io_end->inode;

		ext4_warning(inode->i_sb, "I/O error %d writing to inode %lu "
			     "starting block %llu)",
			     bio->bi_status, inode->i_ino,
			     (अचिन्हित दीर्घ दीर्घ)
			     bi_sector >> (inode->i_blkbits - 9));
		mapping_set_error(inode->i_mapping,
				blk_status_to_त्रुटि_सं(bio->bi_status));
	पूर्ण

	अगर (io_end->flag & EXT4_IO_END_UNWRITTEN) अणु
		/*
		 * Link bio पूर्णांकo list hanging from io_end. We have to करो it
		 * atomically as bio completions can be racing against each
		 * other.
		 */
		bio->bi_निजी = xchg(&io_end->bio, bio);
		ext4_put_io_end_defer(io_end);
	पूर्ण अन्यथा अणु
		/*
		 * Drop io_end reference early. Inode can get मुक्तd once
		 * we finish the bio.
		 */
		ext4_put_io_end_defer(io_end);
		ext4_finish_bio(bio);
		bio_put(bio);
	पूर्ण
पूर्ण

व्योम ext4_io_submit(काष्ठा ext4_io_submit *io)
अणु
	काष्ठा bio *bio = io->io_bio;

	अगर (bio) अणु
		पूर्णांक io_op_flags = io->io_wbc->sync_mode == WB_SYNC_ALL ?
				  REQ_SYNC : 0;
		io->io_bio->bi_ग_लिखो_hपूर्णांक = io->io_end->inode->i_ग_लिखो_hपूर्णांक;
		bio_set_op_attrs(io->io_bio, REQ_OP_WRITE, io_op_flags);
		submit_bio(io->io_bio);
	पूर्ण
	io->io_bio = शून्य;
पूर्ण

व्योम ext4_io_submit_init(काष्ठा ext4_io_submit *io,
			 काष्ठा ग_लिखोback_control *wbc)
अणु
	io->io_wbc = wbc;
	io->io_bio = शून्य;
	io->io_end = शून्य;
पूर्ण

अटल व्योम io_submit_init_bio(काष्ठा ext4_io_submit *io,
			       काष्ठा buffer_head *bh)
अणु
	काष्ठा bio *bio;

	/*
	 * bio_alloc will _always_ be able to allocate a bio अगर
	 * __GFP_सूचीECT_RECLAIM is set, see comments क्रम bio_alloc_bioset().
	 */
	bio = bio_alloc(GFP_NOIO, BIO_MAX_VECS);
	fscrypt_set_bio_crypt_ctx_bh(bio, bh, GFP_NOIO);
	bio->bi_iter.bi_sector = bh->b_blocknr * (bh->b_size >> 9);
	bio_set_dev(bio, bh->b_bdev);
	bio->bi_end_io = ext4_end_bio;
	bio->bi_निजी = ext4_get_io_end(io->io_end);
	io->io_bio = bio;
	io->io_next_block = bh->b_blocknr;
	wbc_init_bio(io->io_wbc, bio);
पूर्ण

अटल व्योम io_submit_add_bh(काष्ठा ext4_io_submit *io,
			     काष्ठा inode *inode,
			     काष्ठा page *page,
			     काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret;

	अगर (io->io_bio && (bh->b_blocknr != io->io_next_block ||
			   !fscrypt_mergeable_bio_bh(io->io_bio, bh))) अणु
submit_and_retry:
		ext4_io_submit(io);
	पूर्ण
	अगर (io->io_bio == शून्य) अणु
		io_submit_init_bio(io, bh);
		io->io_bio->bi_ग_लिखो_hपूर्णांक = inode->i_ग_लिखो_hपूर्णांक;
	पूर्ण
	ret = bio_add_page(io->io_bio, page, bh->b_size, bh_offset(bh));
	अगर (ret != bh->b_size)
		जाओ submit_and_retry;
	wbc_account_cgroup_owner(io->io_wbc, page, bh->b_size);
	io->io_next_block++;
पूर्ण

पूर्णांक ext4_bio_ग_लिखो_page(काष्ठा ext4_io_submit *io,
			काष्ठा page *page,
			पूर्णांक len,
			bool keep_toग_लिखो)
अणु
	काष्ठा page *bounce_page = शून्य;
	काष्ठा inode *inode = page->mapping->host;
	अचिन्हित block_start;
	काष्ठा buffer_head *bh, *head;
	पूर्णांक ret = 0;
	पूर्णांक nr_submitted = 0;
	पूर्णांक nr_to_submit = 0;
	काष्ठा ग_लिखोback_control *wbc = io->io_wbc;

	BUG_ON(!PageLocked(page));
	BUG_ON(PageWriteback(page));

	अगर (keep_toग_लिखो)
		set_page_ग_लिखोback_keepग_लिखो(page);
	अन्यथा
		set_page_ग_लिखोback(page);
	ClearPageError(page);

	/*
	 * Comments copied from block_ग_लिखो_full_page:
	 *
	 * The page straddles i_size.  It must be zeroed out on each and every
	 * ग_लिखोpage invocation because it may be mmapped.  "A file is mapped
	 * in multiples of the page size.  For a file that is not a multiple of
	 * the page size, the reमुख्यing memory is zeroed when mapped, and
	 * ग_लिखोs to that region are not written out to the file."
	 */
	अगर (len < PAGE_SIZE)
		zero_user_segment(page, len, PAGE_SIZE);
	/*
	 * In the first loop we prepare and mark buffers to submit. We have to
	 * mark all buffers in the page beक्रमe submitting so that
	 * end_page_ग_लिखोback() cannot be called from ext4_bio_end_io() when IO
	 * on the first buffer finishes and we are still working on submitting
	 * the second buffer.
	 */
	bh = head = page_buffers(page);
	करो अणु
		block_start = bh_offset(bh);
		अगर (block_start >= len) अणु
			clear_buffer_dirty(bh);
			set_buffer_uptodate(bh);
			जारी;
		पूर्ण
		अगर (!buffer_dirty(bh) || buffer_delay(bh) ||
		    !buffer_mapped(bh) || buffer_unwritten(bh)) अणु
			/* A hole? We can safely clear the dirty bit */
			अगर (!buffer_mapped(bh))
				clear_buffer_dirty(bh);
			अगर (io->io_bio)
				ext4_io_submit(io);
			जारी;
		पूर्ण
		अगर (buffer_new(bh))
			clear_buffer_new(bh);
		set_buffer_async_ग_लिखो(bh);
		nr_to_submit++;
	पूर्ण जबतक ((bh = bh->b_this_page) != head);

	bh = head = page_buffers(page);

	/*
	 * If any blocks are being written to an encrypted file, encrypt them
	 * पूर्णांकo a bounce page.  For simplicity, just encrypt until the last
	 * block which might be needed.  This may cause some unneeded blocks
	 * (e.g. holes) to be unnecessarily encrypted, but this is rare and
	 * can't happen in the common हाल of blocksize == PAGE_SIZE.
	 */
	अगर (fscrypt_inode_uses_fs_layer_crypto(inode) && nr_to_submit) अणु
		gfp_t gfp_flags = GFP_NOFS;
		अचिन्हित पूर्णांक enc_bytes = round_up(len, i_blocksize(inode));

		/*
		 * Since bounce page allocation uses a mempool, we can only use
		 * a रुकोing mask (i.e. request guaranteed allocation) on the
		 * first page of the bio.  Otherwise it can deadlock.
		 */
		अगर (io->io_bio)
			gfp_flags = GFP_NOWAIT | __GFP_NOWARN;
	retry_encrypt:
		bounce_page = fscrypt_encrypt_pagecache_blocks(page, enc_bytes,
							       0, gfp_flags);
		अगर (IS_ERR(bounce_page)) अणु
			ret = PTR_ERR(bounce_page);
			अगर (ret == -ENOMEM &&
			    (io->io_bio || wbc->sync_mode == WB_SYNC_ALL)) अणु
				gfp_flags = GFP_NOFS;
				अगर (io->io_bio)
					ext4_io_submit(io);
				अन्यथा
					gfp_flags |= __GFP_NOFAIL;
				congestion_रुको(BLK_RW_ASYNC, HZ/50);
				जाओ retry_encrypt;
			पूर्ण

			prपूर्णांकk_ratelimited(KERN_ERR "%s: ret = %d\n", __func__, ret);
			redirty_page_क्रम_ग_लिखोpage(wbc, page);
			करो अणु
				clear_buffer_async_ग_लिखो(bh);
				bh = bh->b_this_page;
			पूर्ण जबतक (bh != head);
			जाओ unlock;
		पूर्ण
	पूर्ण

	/* Now submit buffers to ग_लिखो */
	करो अणु
		अगर (!buffer_async_ग_लिखो(bh))
			जारी;
		io_submit_add_bh(io, inode,
				 bounce_page ? bounce_page : page, bh);
		nr_submitted++;
		clear_buffer_dirty(bh);
	पूर्ण जबतक ((bh = bh->b_this_page) != head);

unlock:
	unlock_page(page);
	/* Nothing submitted - we have to end page ग_लिखोback */
	अगर (!nr_submitted)
		end_page_ग_लिखोback(page);
	वापस ret;
पूर्ण
