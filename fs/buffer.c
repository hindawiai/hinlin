<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/buffer.c
 *
 *  Copyright (C) 1991, 1992, 2002  Linus Torvalds
 */

/*
 * Start bdflush() with kernel_thपढ़ो not syscall - Paul Gorपंचांगaker, 12/95
 *
 * Removed a lot of unnecessary code and simplअगरied things now that
 * the buffer cache isn't our primary cache - Andrew Tridgell 12/96
 *
 * Speed up hash, lru, and मुक्त list operations.  Use gfp() क्रम allocating
 * hash table, use SLAB cache क्रम buffer heads. SMP thपढ़ोing.  -DaveM
 *
 * Added 32k buffer block sizes - these are required older ARM प्रणालीs. - RMK
 *
 * async buffer flushing, 1999 Andrea Arcangeli <andrea@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/fs.h>
#समावेश <linux/iomap.h>
#समावेश <linux/mm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/capability.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/file.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/export.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/hash.h>
#समावेश <linux/suspend.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/bपन.स>
#समावेश <linux/cpu.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mpage.h>
#समावेश <linux/bit_spinlock.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/sched/mm.h>
#समावेश <trace/events/block.h>
#समावेश <linux/fscrypt.h>

#समावेश "internal.h"

अटल पूर्णांक fsync_buffers_list(spinlock_t *lock, काष्ठा list_head *list);
अटल पूर्णांक submit_bh_wbc(पूर्णांक op, पूर्णांक op_flags, काष्ठा buffer_head *bh,
			 क्रमागत rw_hपूर्णांक hपूर्णांक, काष्ठा ग_लिखोback_control *wbc);

#घोषणा BH_ENTRY(list) list_entry((list), काष्ठा buffer_head, b_assoc_buffers)

अंतरभूत व्योम touch_buffer(काष्ठा buffer_head *bh)
अणु
	trace_block_touch_buffer(bh);
	mark_page_accessed(bh->b_page);
पूर्ण
EXPORT_SYMBOL(touch_buffer);

व्योम __lock_buffer(काष्ठा buffer_head *bh)
अणु
	रुको_on_bit_lock_io(&bh->b_state, BH_Lock, TASK_UNINTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL(__lock_buffer);

व्योम unlock_buffer(काष्ठा buffer_head *bh)
अणु
	clear_bit_unlock(BH_Lock, &bh->b_state);
	smp_mb__after_atomic();
	wake_up_bit(&bh->b_state, BH_Lock);
पूर्ण
EXPORT_SYMBOL(unlock_buffer);

/*
 * Returns अगर the page has dirty or ग_लिखोback buffers. If all the buffers
 * are unlocked and clean then the PageDirty inक्रमmation is stale. If
 * any of the pages are locked, it is assumed they are locked क्रम IO.
 */
व्योम buffer_check_dirty_ग_लिखोback(काष्ठा page *page,
				     bool *dirty, bool *ग_लिखोback)
अणु
	काष्ठा buffer_head *head, *bh;
	*dirty = false;
	*ग_लिखोback = false;

	BUG_ON(!PageLocked(page));

	अगर (!page_has_buffers(page))
		वापस;

	अगर (PageWriteback(page))
		*ग_लिखोback = true;

	head = page_buffers(page);
	bh = head;
	करो अणु
		अगर (buffer_locked(bh))
			*ग_लिखोback = true;

		अगर (buffer_dirty(bh))
			*dirty = true;

		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
पूर्ण
EXPORT_SYMBOL(buffer_check_dirty_ग_लिखोback);

/*
 * Block until a buffer comes unlocked.  This करोesn't stop it
 * from becoming locked again - you have to lock it yourself
 * अगर you want to preserve its state.
 */
व्योम __रुको_on_buffer(काष्ठा buffer_head * bh)
अणु
	रुको_on_bit_io(&bh->b_state, BH_Lock, TASK_UNINTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL(__रुको_on_buffer);

अटल व्योम buffer_io_error(काष्ठा buffer_head *bh, अक्षर *msg)
अणु
	अगर (!test_bit(BH_Quiet, &bh->b_state))
		prपूर्णांकk_ratelimited(KERN_ERR
			"Buffer I/O error on dev %pg, logical block %llu%s\n",
			bh->b_bdev, (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, msg);
पूर्ण

/*
 * End-of-IO handler helper function which करोes not touch the bh after
 * unlocking it.
 * Note: unlock_buffer() sort-of करोes touch the bh after unlocking it, but
 * a race there is benign: unlock_buffer() only use the bh's address क्रम
 * hashing after unlocking the buffer, so it करोesn't actually touch the bh
 * itself.
 */
अटल व्योम __end_buffer_पढ़ो_notouch(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	अगर (uptodate) अणु
		set_buffer_uptodate(bh);
	पूर्ण अन्यथा अणु
		/* This happens, due to failed पढ़ो-ahead attempts. */
		clear_buffer_uptodate(bh);
	पूर्ण
	unlock_buffer(bh);
पूर्ण

/*
 * Default synchronous end-of-IO handler..  Just mark it up-to-date and
 * unlock the buffer. This is what ll_rw_block uses too.
 */
व्योम end_buffer_पढ़ो_sync(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	__end_buffer_पढ़ो_notouch(bh, uptodate);
	put_bh(bh);
पूर्ण
EXPORT_SYMBOL(end_buffer_पढ़ो_sync);

व्योम end_buffer_ग_लिखो_sync(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	अगर (uptodate) अणु
		set_buffer_uptodate(bh);
	पूर्ण अन्यथा अणु
		buffer_io_error(bh, ", lost sync page write");
		mark_buffer_ग_लिखो_io_error(bh);
		clear_buffer_uptodate(bh);
	पूर्ण
	unlock_buffer(bh);
	put_bh(bh);
पूर्ण
EXPORT_SYMBOL(end_buffer_ग_लिखो_sync);

/*
 * Various fileप्रणालीs appear to want __find_get_block to be non-blocking.
 * But it's the page lock which protects the buffers.  To get around this,
 * we get exclusion from try_to_मुक्त_buffers with the blockdev mapping's
 * निजी_lock.
 *
 * Hack idea: क्रम the blockdev mapping, निजी_lock contention
 * may be quite high.  This code could TryLock the page, and अगर that
 * succeeds, there is no need to take निजी_lock.
 */
अटल काष्ठा buffer_head *
__find_get_block_slow(काष्ठा block_device *bdev, sector_t block)
अणु
	काष्ठा inode *bd_inode = bdev->bd_inode;
	काष्ठा address_space *bd_mapping = bd_inode->i_mapping;
	काष्ठा buffer_head *ret = शून्य;
	pgoff_t index;
	काष्ठा buffer_head *bh;
	काष्ठा buffer_head *head;
	काष्ठा page *page;
	पूर्णांक all_mapped = 1;
	अटल DEFINE_RATELIMIT_STATE(last_warned, HZ, 1);

	index = block >> (PAGE_SHIFT - bd_inode->i_blkbits);
	page = find_get_page_flags(bd_mapping, index, FGP_ACCESSED);
	अगर (!page)
		जाओ out;

	spin_lock(&bd_mapping->निजी_lock);
	अगर (!page_has_buffers(page))
		जाओ out_unlock;
	head = page_buffers(page);
	bh = head;
	करो अणु
		अगर (!buffer_mapped(bh))
			all_mapped = 0;
		अन्यथा अगर (bh->b_blocknr == block) अणु
			ret = bh;
			get_bh(bh);
			जाओ out_unlock;
		पूर्ण
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);

	/* we might be here because some of the buffers on this page are
	 * not mapped.  This is due to various races between
	 * file io on the block device and getblk.  It माला_लो dealt with
	 * अन्यथाwhere, करोn't buffer_error अगर we had some unmapped buffers
	 */
	ratelimit_set_flags(&last_warned, RATELIMIT_MSG_ON_RELEASE);
	अगर (all_mapped && __ratelimit(&last_warned)) अणु
		prपूर्णांकk("__find_get_block_slow() failed. block=%llu, "
		       "b_blocknr=%llu, b_state=0x%08lx, b_size=%zu, "
		       "device %pg blocksize: %d\n",
		       (अचिन्हित दीर्घ दीर्घ)block,
		       (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
		       bh->b_state, bh->b_size, bdev,
		       1 << bd_inode->i_blkbits);
	पूर्ण
out_unlock:
	spin_unlock(&bd_mapping->निजी_lock);
	put_page(page);
out:
	वापस ret;
पूर्ण

अटल व्योम end_buffer_async_पढ़ो(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा buffer_head *first;
	काष्ठा buffer_head *पंचांगp;
	काष्ठा page *page;
	पूर्णांक page_uptodate = 1;

	BUG_ON(!buffer_async_पढ़ो(bh));

	page = bh->b_page;
	अगर (uptodate) अणु
		set_buffer_uptodate(bh);
	पूर्ण अन्यथा अणु
		clear_buffer_uptodate(bh);
		buffer_io_error(bh, ", async page read");
		SetPageError(page);
	पूर्ण

	/*
	 * Be _very_ careful from here on. Bad things can happen अगर
	 * two buffer heads end IO at almost the same समय and both
	 * decide that the page is now completely करोne.
	 */
	first = page_buffers(page);
	spin_lock_irqsave(&first->b_uptodate_lock, flags);
	clear_buffer_async_पढ़ो(bh);
	unlock_buffer(bh);
	पंचांगp = bh;
	करो अणु
		अगर (!buffer_uptodate(पंचांगp))
			page_uptodate = 0;
		अगर (buffer_async_पढ़ो(पंचांगp)) अणु
			BUG_ON(!buffer_locked(पंचांगp));
			जाओ still_busy;
		पूर्ण
		पंचांगp = पंचांगp->b_this_page;
	पूर्ण जबतक (पंचांगp != bh);
	spin_unlock_irqrestore(&first->b_uptodate_lock, flags);

	/*
	 * If none of the buffers had errors and they are all
	 * uptodate then we can set the page uptodate.
	 */
	अगर (page_uptodate && !PageError(page))
		SetPageUptodate(page);
	unlock_page(page);
	वापस;

still_busy:
	spin_unlock_irqrestore(&first->b_uptodate_lock, flags);
	वापस;
पूर्ण

काष्ठा decrypt_bh_ctx अणु
	काष्ठा work_काष्ठा work;
	काष्ठा buffer_head *bh;
पूर्ण;

अटल व्योम decrypt_bh(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा decrypt_bh_ctx *ctx =
		container_of(work, काष्ठा decrypt_bh_ctx, work);
	काष्ठा buffer_head *bh = ctx->bh;
	पूर्णांक err;

	err = fscrypt_decrypt_pagecache_blocks(bh->b_page, bh->b_size,
					       bh_offset(bh));
	end_buffer_async_पढ़ो(bh, err == 0);
	kमुक्त(ctx);
पूर्ण

/*
 * I/O completion handler क्रम block_पढ़ो_full_page() - pages
 * which come unlocked at the end of I/O.
 */
अटल व्योम end_buffer_async_पढ़ो_io(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	/* Decrypt अगर needed */
	अगर (uptodate &&
	    fscrypt_inode_uses_fs_layer_crypto(bh->b_page->mapping->host)) अणु
		काष्ठा decrypt_bh_ctx *ctx = kदो_स्मृति(माप(*ctx), GFP_ATOMIC);

		अगर (ctx) अणु
			INIT_WORK(&ctx->work, decrypt_bh);
			ctx->bh = bh;
			fscrypt_enqueue_decrypt_work(&ctx->work);
			वापस;
		पूर्ण
		uptodate = 0;
	पूर्ण
	end_buffer_async_पढ़ो(bh, uptodate);
पूर्ण

/*
 * Completion handler क्रम block_ग_लिखो_full_page() - pages which are unlocked
 * during I/O, and which have PageWriteback cleared upon I/O completion.
 */
व्योम end_buffer_async_ग_लिखो(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा buffer_head *first;
	काष्ठा buffer_head *पंचांगp;
	काष्ठा page *page;

	BUG_ON(!buffer_async_ग_लिखो(bh));

	page = bh->b_page;
	अगर (uptodate) अणु
		set_buffer_uptodate(bh);
	पूर्ण अन्यथा अणु
		buffer_io_error(bh, ", lost async page write");
		mark_buffer_ग_लिखो_io_error(bh);
		clear_buffer_uptodate(bh);
		SetPageError(page);
	पूर्ण

	first = page_buffers(page);
	spin_lock_irqsave(&first->b_uptodate_lock, flags);

	clear_buffer_async_ग_लिखो(bh);
	unlock_buffer(bh);
	पंचांगp = bh->b_this_page;
	जबतक (पंचांगp != bh) अणु
		अगर (buffer_async_ग_लिखो(पंचांगp)) अणु
			BUG_ON(!buffer_locked(पंचांगp));
			जाओ still_busy;
		पूर्ण
		पंचांगp = पंचांगp->b_this_page;
	पूर्ण
	spin_unlock_irqrestore(&first->b_uptodate_lock, flags);
	end_page_ग_लिखोback(page);
	वापस;

still_busy:
	spin_unlock_irqrestore(&first->b_uptodate_lock, flags);
	वापस;
पूर्ण
EXPORT_SYMBOL(end_buffer_async_ग_लिखो);

/*
 * If a page's buffers are under async पढ़ोin (end_buffer_async_पढ़ो
 * completion) then there is a possibility that another thपढ़ो of
 * control could lock one of the buffers after it has completed
 * but जबतक some of the other buffers have not completed.  This
 * locked buffer would confuse end_buffer_async_पढ़ो() पूर्णांकo not unlocking
 * the page.  So the असलence of BH_Async_Read tells end_buffer_async_पढ़ो()
 * that this buffer is not under async I/O.
 *
 * The page comes unlocked when it has no locked buffer_async buffers
 * left.
 *
 * PageLocked prevents anyone starting new async I/O पढ़ोs any of
 * the buffers.
 *
 * PageWriteback is used to prevent simultaneous ग_लिखोout of the same
 * page.
 *
 * PageLocked prevents anyone from starting ग_लिखोback of a page which is
 * under पढ़ो I/O (PageWriteback is only ever set against a locked page).
 */
अटल व्योम mark_buffer_async_पढ़ो(काष्ठा buffer_head *bh)
अणु
	bh->b_end_io = end_buffer_async_पढ़ो_io;
	set_buffer_async_पढ़ो(bh);
पूर्ण

अटल व्योम mark_buffer_async_ग_लिखो_endio(काष्ठा buffer_head *bh,
					  bh_end_io_t *handler)
अणु
	bh->b_end_io = handler;
	set_buffer_async_ग_लिखो(bh);
पूर्ण

व्योम mark_buffer_async_ग_लिखो(काष्ठा buffer_head *bh)
अणु
	mark_buffer_async_ग_लिखो_endio(bh, end_buffer_async_ग_लिखो);
पूर्ण
EXPORT_SYMBOL(mark_buffer_async_ग_लिखो);


/*
 * fs/buffer.c contains helper functions क्रम buffer-backed address space's
 * fsync functions.  A common requirement क्रम buffer-based fileप्रणालीs is
 * that certain data from the backing blockdev needs to be written out क्रम
 * a successful fsync().  For example, ext2 indirect blocks need to be
 * written back and रुकोed upon beक्रमe fsync() वापसs.
 *
 * The functions mark_buffer_inode_dirty(), fsync_inode_buffers(),
 * inode_has_buffers() and invalidate_inode_buffers() are provided क्रम the
 * management of a list of dependent buffers at ->i_mapping->निजी_list.
 *
 * Locking is a little subtle: try_to_मुक्त_buffers() will हटाओ buffers
 * from their controlling inode's queue when they are being मुक्तd.  But
 * try_to_मुक्त_buffers() will be operating against the *blockdev* mapping
 * at the समय, not against the S_ISREG file which depends on those buffers.
 * So the locking क्रम निजी_list is via the निजी_lock in the address_space
 * which backs the buffers.  Which is dअगरferent from the address_space 
 * against which the buffers are listed.  So क्रम a particular address_space,
 * mapping->निजी_lock करोes *not* protect mapping->निजी_list!  In fact,
 * mapping->निजी_list will always be रक्षित by the backing blockdev's
 * ->निजी_lock.
 *
 * Which पूर्णांकroduces a requirement: all buffers on an address_space's
 * ->निजी_list must be from the same address_space: the blockdev's.
 *
 * address_spaces which करो not place buffers at ->निजी_list via these
 * utility functions are मुक्त to use निजी_lock and निजी_list क्रम
 * whatever they want.  The only requirement is that list_empty(निजी_list)
 * be true at clear_inode() समय.
 *
 * FIXME: clear_inode should not call invalidate_inode_buffers().  The
 * fileप्रणालीs should करो that.  invalidate_inode_buffers() should just go
 * BUG_ON(!list_empty).
 *
 * FIXME: mark_buffer_dirty_inode() is a data-plane operation.  It should
 * take an address_space, not an inode.  And it should be called
 * mark_buffer_dirty_fsync() to clearly define why those buffers are being
 * queued up.
 *
 * FIXME: mark_buffer_dirty_inode() करोesn't need to add the buffer to the
 * list अगर it is alपढ़ोy on a list.  Because अगर the buffer is on a list,
 * it *must* alपढ़ोy be on the right one.  If not, the fileप्रणाली is being
 * silly.  This will save a ton of locking.  But first we have to ensure
 * that buffers are taken *off* the old inode's list when they are मुक्तd
 * (presumably in truncate).  That requires careful auditing of all
 * fileप्रणालीs (करो it inside bक्रमget()).  It could also be करोne by bringing
 * b_inode back.
 */

/*
 * The buffer's backing address_space's निजी_lock must be held
 */
अटल व्योम __हटाओ_assoc_queue(काष्ठा buffer_head *bh)
अणु
	list_del_init(&bh->b_assoc_buffers);
	WARN_ON(!bh->b_assoc_map);
	bh->b_assoc_map = शून्य;
पूर्ण

पूर्णांक inode_has_buffers(काष्ठा inode *inode)
अणु
	वापस !list_empty(&inode->i_data.निजी_list);
पूर्ण

/*
 * osync is deचिन्हित to support O_SYNC io.  It रुकोs synchronously क्रम
 * all alपढ़ोy-submitted IO to complete, but करोes not queue any new
 * ग_लिखोs to the disk.
 *
 * To करो O_SYNC ग_लिखोs, just queue the buffer ग_लिखोs with ll_rw_block as
 * you dirty the buffers, and then use osync_inode_buffers to रुको क्रम
 * completion.  Any other dirty buffers which are not yet queued क्रम
 * ग_लिखो will not be flushed to disk by the osync.
 */
अटल पूर्णांक osync_buffers_list(spinlock_t *lock, काष्ठा list_head *list)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा list_head *p;
	पूर्णांक err = 0;

	spin_lock(lock);
repeat:
	list_क्रम_each_prev(p, list) अणु
		bh = BH_ENTRY(p);
		अगर (buffer_locked(bh)) अणु
			get_bh(bh);
			spin_unlock(lock);
			रुको_on_buffer(bh);
			अगर (!buffer_uptodate(bh))
				err = -EIO;
			brअन्यथा(bh);
			spin_lock(lock);
			जाओ repeat;
		पूर्ण
	पूर्ण
	spin_unlock(lock);
	वापस err;
पूर्ण

व्योम emergency_thaw_bdev(काष्ठा super_block *sb)
अणु
	जबतक (sb->s_bdev && !thaw_bdev(sb->s_bdev))
		prपूर्णांकk(KERN_WARNING "Emergency Thaw on %pg\n", sb->s_bdev);
पूर्ण

/**
 * sync_mapping_buffers - ग_लिखो out & रुको upon a mapping's "associated" buffers
 * @mapping: the mapping which wants those buffers written
 *
 * Starts I/O against the buffers at mapping->निजी_list, and रुकोs upon
 * that I/O.
 *
 * Basically, this is a convenience function क्रम fsync().
 * @mapping is a file or directory which needs those buffers to be written क्रम
 * a successful fsync().
 */
पूर्णांक sync_mapping_buffers(काष्ठा address_space *mapping)
अणु
	काष्ठा address_space *buffer_mapping = mapping->निजी_data;

	अगर (buffer_mapping == शून्य || list_empty(&mapping->निजी_list))
		वापस 0;

	वापस fsync_buffers_list(&buffer_mapping->निजी_lock,
					&mapping->निजी_list);
पूर्ण
EXPORT_SYMBOL(sync_mapping_buffers);

/*
 * Called when we've recently written block `bblock', and it is known that
 * `bblock' was क्रम a buffer_boundary() buffer.  This means that the block at
 * `bblock + 1' is probably a dirty indirect block.  Hunt it down and, if it's
 * dirty, schedule it क्रम IO.  So that indirects merge nicely with their data.
 */
व्योम ग_लिखो_boundary_block(काष्ठा block_device *bdev,
			sector_t bblock, अचिन्हित blocksize)
अणु
	काष्ठा buffer_head *bh = __find_get_block(bdev, bblock + 1, blocksize);
	अगर (bh) अणु
		अगर (buffer_dirty(bh))
			ll_rw_block(REQ_OP_WRITE, 0, 1, &bh);
		put_bh(bh);
	पूर्ण
पूर्ण

व्योम mark_buffer_dirty_inode(काष्ठा buffer_head *bh, काष्ठा inode *inode)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा address_space *buffer_mapping = bh->b_page->mapping;

	mark_buffer_dirty(bh);
	अगर (!mapping->निजी_data) अणु
		mapping->निजी_data = buffer_mapping;
	पूर्ण अन्यथा अणु
		BUG_ON(mapping->निजी_data != buffer_mapping);
	पूर्ण
	अगर (!bh->b_assoc_map) अणु
		spin_lock(&buffer_mapping->निजी_lock);
		list_move_tail(&bh->b_assoc_buffers,
				&mapping->निजी_list);
		bh->b_assoc_map = mapping;
		spin_unlock(&buffer_mapping->निजी_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mark_buffer_dirty_inode);

/*
 * Mark the page dirty, and set it dirty in the page cache, and mark the inode
 * dirty.
 *
 * If warn is true, then emit a warning अगर the page is not uptodate and has
 * not been truncated.
 *
 * The caller must hold lock_page_memcg().
 */
व्योम __set_page_dirty(काष्ठा page *page, काष्ठा address_space *mapping,
			     पूर्णांक warn)
अणु
	अचिन्हित दीर्घ flags;

	xa_lock_irqsave(&mapping->i_pages, flags);
	अगर (page->mapping) अणु	/* Race with truncate? */
		WARN_ON_ONCE(warn && !PageUptodate(page));
		account_page_dirtied(page, mapping);
		__xa_set_mark(&mapping->i_pages, page_index(page),
				PAGECACHE_TAG_सूचीTY);
	पूर्ण
	xa_unlock_irqrestore(&mapping->i_pages, flags);
पूर्ण
EXPORT_SYMBOL_GPL(__set_page_dirty);

/*
 * Add a page to the dirty page list.
 *
 * It is a sad fact of lअगरe that this function is called from several places
 * deeply under spinlocking.  It may not sleep.
 *
 * If the page has buffers, the uptodate buffers are set dirty, to preserve
 * dirty-state coherency between the page and the buffers.  It the page करोes
 * not have buffers then when they are later attached they will all be set
 * dirty.
 *
 * The buffers are dirtied beक्रमe the page is dirtied.  There's a small race
 * winकरोw in which a ग_लिखोpage caller may see the page cleanness but not the
 * buffer dirtiness.  That's fine.  If this code were to set the page dirty
 * beक्रमe the buffers, a concurrent ग_लिखोpage caller could clear the page dirty
 * bit, see a bunch of clean buffers and we'd end up with dirty buffers/clean
 * page on the dirty page list.
 *
 * We use निजी_lock to lock against try_to_मुक्त_buffers जबतक using the
 * page's buffer list.  Also use this to protect against clean buffers being
 * added to the page after it was set dirty.
 *
 * FIXME: may need to call ->reservepage here as well.  That's rather up to the
 * address_space though.
 */
पूर्णांक __set_page_dirty_buffers(काष्ठा page *page)
अणु
	पूर्णांक newly_dirty;
	काष्ठा address_space *mapping = page_mapping(page);

	अगर (unlikely(!mapping))
		वापस !TestSetPageDirty(page);

	spin_lock(&mapping->निजी_lock);
	अगर (page_has_buffers(page)) अणु
		काष्ठा buffer_head *head = page_buffers(page);
		काष्ठा buffer_head *bh = head;

		करो अणु
			set_buffer_dirty(bh);
			bh = bh->b_this_page;
		पूर्ण जबतक (bh != head);
	पूर्ण
	/*
	 * Lock out page's memcg migration to keep PageDirty
	 * synchronized with per-memcg dirty page counters.
	 */
	lock_page_memcg(page);
	newly_dirty = !TestSetPageDirty(page);
	spin_unlock(&mapping->निजी_lock);

	अगर (newly_dirty)
		__set_page_dirty(page, mapping, 1);

	unlock_page_memcg(page);

	अगर (newly_dirty)
		__mark_inode_dirty(mapping->host, I_सूचीTY_PAGES);

	वापस newly_dirty;
पूर्ण
EXPORT_SYMBOL(__set_page_dirty_buffers);

/*
 * Write out and रुको upon a list of buffers.
 *
 * We have conflicting pressures: we want to make sure that all
 * initially dirty buffers get रुकोed on, but that any subsequently
 * dirtied buffers करोn't.  After all, we don't want fsync to last
 * क्रमever अगर somebody is actively writing to the file.
 *
 * Do this in two मुख्य stages: first we copy dirty buffers to a
 * temporary inode list, queueing the ग_लिखोs as we go.  Then we clean
 * up, रुकोing क्रम those ग_लिखोs to complete.
 * 
 * During this second stage, any subsequent updates to the file may end
 * up refiling the buffer on the original inode's dirty list again, so
 * there is a chance we will end up with a buffer queued क्रम ग_लिखो but
 * not yet completed on that list.  So, as a final cleanup we go through
 * the osync code to catch these locked, dirty buffers without requeuing
 * any newly dirty buffers क्रम ग_लिखो.
 */
अटल पूर्णांक fsync_buffers_list(spinlock_t *lock, काष्ठा list_head *list)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा list_head पंचांगp;
	काष्ठा address_space *mapping;
	पूर्णांक err = 0, err2;
	काष्ठा blk_plug plug;

	INIT_LIST_HEAD(&पंचांगp);
	blk_start_plug(&plug);

	spin_lock(lock);
	जबतक (!list_empty(list)) अणु
		bh = BH_ENTRY(list->next);
		mapping = bh->b_assoc_map;
		__हटाओ_assoc_queue(bh);
		/* Aव्योम race with mark_buffer_dirty_inode() which करोes
		 * a lockless check and we rely on seeing the dirty bit */
		smp_mb();
		अगर (buffer_dirty(bh) || buffer_locked(bh)) अणु
			list_add(&bh->b_assoc_buffers, &पंचांगp);
			bh->b_assoc_map = mapping;
			अगर (buffer_dirty(bh)) अणु
				get_bh(bh);
				spin_unlock(lock);
				/*
				 * Ensure any pending I/O completes so that
				 * ग_लिखो_dirty_buffer() actually ग_लिखोs the
				 * current contents - it is a noop अगर I/O is
				 * still in flight on potentially older
				 * contents.
				 */
				ग_लिखो_dirty_buffer(bh, REQ_SYNC);

				/*
				 * Kick off IO क्रम the previous mapping. Note
				 * that we will not run the very last mapping,
				 * रुको_on_buffer() will करो that क्रम us
				 * through sync_buffer().
				 */
				brअन्यथा(bh);
				spin_lock(lock);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock(lock);
	blk_finish_plug(&plug);
	spin_lock(lock);

	जबतक (!list_empty(&पंचांगp)) अणु
		bh = BH_ENTRY(पंचांगp.prev);
		get_bh(bh);
		mapping = bh->b_assoc_map;
		__हटाओ_assoc_queue(bh);
		/* Aव्योम race with mark_buffer_dirty_inode() which करोes
		 * a lockless check and we rely on seeing the dirty bit */
		smp_mb();
		अगर (buffer_dirty(bh)) अणु
			list_add(&bh->b_assoc_buffers,
				 &mapping->निजी_list);
			bh->b_assoc_map = mapping;
		पूर्ण
		spin_unlock(lock);
		रुको_on_buffer(bh);
		अगर (!buffer_uptodate(bh))
			err = -EIO;
		brअन्यथा(bh);
		spin_lock(lock);
	पूर्ण
	
	spin_unlock(lock);
	err2 = osync_buffers_list(lock, list);
	अगर (err)
		वापस err;
	अन्यथा
		वापस err2;
पूर्ण

/*
 * Invalidate any and all dirty buffers on a given inode.  We are
 * probably unmounting the fs, but that करोesn't mean we have alपढ़ोy
 * करोne a sync().  Just drop the buffers from the inode list.
 *
 * NOTE: we take the inode's blockdev's mapping's निजी_lock.  Which
 * assumes that all the buffers are against the blockdev.  Not true
 * क्रम reiserfs.
 */
व्योम invalidate_inode_buffers(काष्ठा inode *inode)
अणु
	अगर (inode_has_buffers(inode)) अणु
		काष्ठा address_space *mapping = &inode->i_data;
		काष्ठा list_head *list = &mapping->निजी_list;
		काष्ठा address_space *buffer_mapping = mapping->निजी_data;

		spin_lock(&buffer_mapping->निजी_lock);
		जबतक (!list_empty(list))
			__हटाओ_assoc_queue(BH_ENTRY(list->next));
		spin_unlock(&buffer_mapping->निजी_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(invalidate_inode_buffers);

/*
 * Remove any clean buffers from the inode's buffer list.  This is called
 * when we're trying to मुक्त the inode itself.  Those buffers can pin it.
 *
 * Returns true अगर all buffers were हटाओd.
 */
पूर्णांक हटाओ_inode_buffers(काष्ठा inode *inode)
अणु
	पूर्णांक ret = 1;

	अगर (inode_has_buffers(inode)) अणु
		काष्ठा address_space *mapping = &inode->i_data;
		काष्ठा list_head *list = &mapping->निजी_list;
		काष्ठा address_space *buffer_mapping = mapping->निजी_data;

		spin_lock(&buffer_mapping->निजी_lock);
		जबतक (!list_empty(list)) अणु
			काष्ठा buffer_head *bh = BH_ENTRY(list->next);
			अगर (buffer_dirty(bh)) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			__हटाओ_assoc_queue(bh);
		पूर्ण
		spin_unlock(&buffer_mapping->निजी_lock);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Create the appropriate buffers when given a page क्रम data area and
 * the size of each buffer.. Use the bh->b_this_page linked list to
 * follow the buffers created.  Return शून्य अगर unable to create more
 * buffers.
 *
 * The retry flag is used to dअगरferentiate async IO (paging, swapping)
 * which may not fail from ordinary buffer allocations.
 */
काष्ठा buffer_head *alloc_page_buffers(काष्ठा page *page, अचिन्हित दीर्घ size,
		bool retry)
अणु
	काष्ठा buffer_head *bh, *head;
	gfp_t gfp = GFP_NOFS | __GFP_ACCOUNT;
	दीर्घ offset;
	काष्ठा mem_cgroup *memcg, *old_memcg;

	अगर (retry)
		gfp |= __GFP_NOFAIL;

	/* The page lock pins the memcg */
	memcg = page_memcg(page);
	old_memcg = set_active_memcg(memcg);

	head = शून्य;
	offset = PAGE_SIZE;
	जबतक ((offset -= size) >= 0) अणु
		bh = alloc_buffer_head(gfp);
		अगर (!bh)
			जाओ no_grow;

		bh->b_this_page = head;
		bh->b_blocknr = -1;
		head = bh;

		bh->b_size = size;

		/* Link the buffer to its page */
		set_bh_page(bh, page, offset);
	पूर्ण
out:
	set_active_memcg(old_memcg);
	वापस head;
/*
 * In हाल anything failed, we just मुक्त everything we got.
 */
no_grow:
	अगर (head) अणु
		करो अणु
			bh = head;
			head = head->b_this_page;
			मुक्त_buffer_head(bh);
		पूर्ण जबतक (head);
	पूर्ण

	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_page_buffers);

अटल अंतरभूत व्योम
link_dev_buffers(काष्ठा page *page, काष्ठा buffer_head *head)
अणु
	काष्ठा buffer_head *bh, *tail;

	bh = head;
	करो अणु
		tail = bh;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh);
	tail->b_this_page = head;
	attach_page_निजी(page, head);
पूर्ण

अटल sector_t blkdev_max_block(काष्ठा block_device *bdev, अचिन्हित पूर्णांक size)
अणु
	sector_t retval = ~((sector_t)0);
	loff_t sz = i_size_पढ़ो(bdev->bd_inode);

	अगर (sz) अणु
		अचिन्हित पूर्णांक sizebits = blksize_bits(size);
		retval = (sz >> sizebits);
	पूर्ण
	वापस retval;
पूर्ण

/*
 * Initialise the state of a blockdev page's buffers.
 */ 
अटल sector_t
init_page_buffers(काष्ठा page *page, काष्ठा block_device *bdev,
			sector_t block, पूर्णांक size)
अणु
	काष्ठा buffer_head *head = page_buffers(page);
	काष्ठा buffer_head *bh = head;
	पूर्णांक uptodate = PageUptodate(page);
	sector_t end_block = blkdev_max_block(I_BDEV(bdev->bd_inode), size);

	करो अणु
		अगर (!buffer_mapped(bh)) अणु
			bh->b_end_io = शून्य;
			bh->b_निजी = शून्य;
			bh->b_bdev = bdev;
			bh->b_blocknr = block;
			अगर (uptodate)
				set_buffer_uptodate(bh);
			अगर (block < end_block)
				set_buffer_mapped(bh);
		पूर्ण
		block++;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);

	/*
	 * Caller needs to validate requested block against end of device.
	 */
	वापस end_block;
पूर्ण

/*
 * Create the page-cache page that contains the requested block.
 *
 * This is used purely क्रम blockdev mappings.
 */
अटल पूर्णांक
grow_dev_page(काष्ठा block_device *bdev, sector_t block,
	      pgoff_t index, पूर्णांक size, पूर्णांक sizebits, gfp_t gfp)
अणु
	काष्ठा inode *inode = bdev->bd_inode;
	काष्ठा page *page;
	काष्ठा buffer_head *bh;
	sector_t end_block;
	पूर्णांक ret = 0;
	gfp_t gfp_mask;

	gfp_mask = mapping_gfp_स्थिरraपूर्णांक(inode->i_mapping, ~__GFP_FS) | gfp;

	/*
	 * XXX: __getblk_slow() can not really deal with failure and
	 * will endlessly loop on improvised global reclaim.  Prefer
	 * looping in the allocator rather than here, at least that
	 * code knows what it's करोing.
	 */
	gfp_mask |= __GFP_NOFAIL;

	page = find_or_create_page(inode->i_mapping, index, gfp_mask);

	BUG_ON(!PageLocked(page));

	अगर (page_has_buffers(page)) अणु
		bh = page_buffers(page);
		अगर (bh->b_size == size) अणु
			end_block = init_page_buffers(page, bdev,
						(sector_t)index << sizebits,
						size);
			जाओ करोne;
		पूर्ण
		अगर (!try_to_मुक्त_buffers(page))
			जाओ failed;
	पूर्ण

	/*
	 * Allocate some buffers क्रम this page
	 */
	bh = alloc_page_buffers(page, size, true);

	/*
	 * Link the page to the buffers and initialise them.  Take the
	 * lock to be atomic wrt __find_get_block(), which करोes not
	 * run under the page lock.
	 */
	spin_lock(&inode->i_mapping->निजी_lock);
	link_dev_buffers(page, bh);
	end_block = init_page_buffers(page, bdev, (sector_t)index << sizebits,
			size);
	spin_unlock(&inode->i_mapping->निजी_lock);
करोne:
	ret = (block < end_block) ? 1 : -ENXIO;
failed:
	unlock_page(page);
	put_page(page);
	वापस ret;
पूर्ण

/*
 * Create buffers क्रम the specअगरied block device block's page.  If
 * that page was dirty, the buffers are set dirty also.
 */
अटल पूर्णांक
grow_buffers(काष्ठा block_device *bdev, sector_t block, पूर्णांक size, gfp_t gfp)
अणु
	pgoff_t index;
	पूर्णांक sizebits;

	sizebits = PAGE_SHIFT - __ffs(size);
	index = block >> sizebits;

	/*
	 * Check क्रम a block which wants to lie outside our maximum possible
	 * pagecache index.  (this comparison is करोne using sector_t types).
	 */
	अगर (unlikely(index != block >> sizebits)) अणु
		prपूर्णांकk(KERN_ERR "%s: requested out-of-range block %llu for "
			"device %pg\n",
			__func__, (अचिन्हित दीर्घ दीर्घ)block,
			bdev);
		वापस -EIO;
	पूर्ण

	/* Create a page with the proper size buffers.. */
	वापस grow_dev_page(bdev, block, index, size, sizebits, gfp);
पूर्ण

अटल काष्ठा buffer_head *
__getblk_slow(काष्ठा block_device *bdev, sector_t block,
	     अचिन्हित size, gfp_t gfp)
अणु
	/* Size must be multiple of hard sectorsize */
	अगर (unlikely(size & (bdev_logical_block_size(bdev)-1) ||
			(size < 512 || size > PAGE_SIZE))) अणु
		prपूर्णांकk(KERN_ERR "getblk(): invalid block size %d requested\n",
					size);
		prपूर्णांकk(KERN_ERR "logical block size: %d\n",
					bdev_logical_block_size(bdev));

		dump_stack();
		वापस शून्य;
	पूर्ण

	क्रम (;;) अणु
		काष्ठा buffer_head *bh;
		पूर्णांक ret;

		bh = __find_get_block(bdev, block, size);
		अगर (bh)
			वापस bh;

		ret = grow_buffers(bdev, block, size, gfp);
		अगर (ret < 0)
			वापस शून्य;
	पूर्ण
पूर्ण

/*
 * The relationship between dirty buffers and dirty pages:
 *
 * Whenever a page has any dirty buffers, the page's dirty bit is set, and
 * the page is tagged dirty in the page cache.
 *
 * At all बार, the dirtiness of the buffers represents the dirtiness of
 * subsections of the page.  If the page has buffers, the page dirty bit is
 * merely a hपूर्णांक about the true dirty state.
 *
 * When a page is set dirty in its entirety, all its buffers are marked dirty
 * (अगर the page has buffers).
 *
 * When a buffer is marked dirty, its page is dirtied, but the page's other
 * buffers are not.
 *
 * Also.  When blockdev buffers are explicitly पढ़ो with bपढ़ो(), they
 * inभागidually become uptodate.  But their backing page reमुख्यs not
 * uptodate - even अगर all of its buffers are uptodate.  A subsequent
 * block_पढ़ो_full_page() against that page will discover all the uptodate
 * buffers, will set the page uptodate and will perक्रमm no I/O.
 */

/**
 * mark_buffer_dirty - mark a buffer_head as needing ग_लिखोout
 * @bh: the buffer_head to mark dirty
 *
 * mark_buffer_dirty() will set the dirty bit against the buffer, then set
 * its backing page dirty, then tag the page as dirty in the page cache
 * and then attach the address_space's inode to its superblock's dirty
 * inode list.
 *
 * mark_buffer_dirty() is atomic.  It takes bh->b_page->mapping->निजी_lock,
 * i_pages lock and mapping->host->i_lock.
 */
व्योम mark_buffer_dirty(काष्ठा buffer_head *bh)
अणु
	WARN_ON_ONCE(!buffer_uptodate(bh));

	trace_block_dirty_buffer(bh);

	/*
	 * Very *carefully* optimize the it-is-alपढ़ोy-dirty हाल.
	 *
	 * Don't let the final "is it dirty" escape to beक्रमe we
	 * perhaps modअगरied the buffer.
	 */
	अगर (buffer_dirty(bh)) अणु
		smp_mb();
		अगर (buffer_dirty(bh))
			वापस;
	पूर्ण

	अगर (!test_set_buffer_dirty(bh)) अणु
		काष्ठा page *page = bh->b_page;
		काष्ठा address_space *mapping = शून्य;

		lock_page_memcg(page);
		अगर (!TestSetPageDirty(page)) अणु
			mapping = page_mapping(page);
			अगर (mapping)
				__set_page_dirty(page, mapping, 0);
		पूर्ण
		unlock_page_memcg(page);
		अगर (mapping)
			__mark_inode_dirty(mapping->host, I_सूचीTY_PAGES);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mark_buffer_dirty);

व्योम mark_buffer_ग_लिखो_io_error(काष्ठा buffer_head *bh)
अणु
	काष्ठा super_block *sb;

	set_buffer_ग_लिखो_io_error(bh);
	/* FIXME: करो we need to set this in both places? */
	अगर (bh->b_page && bh->b_page->mapping)
		mapping_set_error(bh->b_page->mapping, -EIO);
	अगर (bh->b_assoc_map)
		mapping_set_error(bh->b_assoc_map, -EIO);
	rcu_पढ़ो_lock();
	sb = READ_ONCE(bh->b_bdev->bd_super);
	अगर (sb)
		errseq_set(&sb->s_wb_err, -EIO);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(mark_buffer_ग_लिखो_io_error);

/*
 * Decrement a buffer_head's reference count.  If all buffers against a page
 * have zero reference count, are clean and unlocked, and अगर the page is clean
 * and unlocked then try_to_मुक्त_buffers() may strip the buffers from the page
 * in preparation क्रम मुक्तing it (someबार, rarely, buffers are हटाओd from
 * a page but it ends up not being मुक्तd, and buffers may later be reattached).
 */
व्योम __brअन्यथा(काष्ठा buffer_head * buf)
अणु
	अगर (atomic_पढ़ो(&buf->b_count)) अणु
		put_bh(buf);
		वापस;
	पूर्ण
	WARN(1, KERN_ERR "VFS: brelse: Trying to free free buffer\n");
पूर्ण
EXPORT_SYMBOL(__brअन्यथा);

/*
 * bक्रमget() is like brअन्यथा(), except it discards any
 * potentially dirty data.
 */
व्योम __bक्रमget(काष्ठा buffer_head *bh)
अणु
	clear_buffer_dirty(bh);
	अगर (bh->b_assoc_map) अणु
		काष्ठा address_space *buffer_mapping = bh->b_page->mapping;

		spin_lock(&buffer_mapping->निजी_lock);
		list_del_init(&bh->b_assoc_buffers);
		bh->b_assoc_map = शून्य;
		spin_unlock(&buffer_mapping->निजी_lock);
	पूर्ण
	__brअन्यथा(bh);
पूर्ण
EXPORT_SYMBOL(__bक्रमget);

अटल काष्ठा buffer_head *__bपढ़ो_slow(काष्ठा buffer_head *bh)
अणु
	lock_buffer(bh);
	अगर (buffer_uptodate(bh)) अणु
		unlock_buffer(bh);
		वापस bh;
	पूर्ण अन्यथा अणु
		get_bh(bh);
		bh->b_end_io = end_buffer_पढ़ो_sync;
		submit_bh(REQ_OP_READ, 0, bh);
		रुको_on_buffer(bh);
		अगर (buffer_uptodate(bh))
			वापस bh;
	पूर्ण
	brअन्यथा(bh);
	वापस शून्य;
पूर्ण

/*
 * Per-cpu buffer LRU implementation.  To reduce the cost of __find_get_block().
 * The bhs[] array is sorted - newest buffer is at bhs[0].  Buffers have their
 * refcount elevated by one when they're in an LRU.  A buffer can only appear
 * once in a particular CPU's LRU.  A single buffer can be present in multiple
 * CPU's LRUs at the same समय.
 *
 * This is a transparent caching front-end to sb_bपढ़ो(), sb_getblk() and
 * sb_find_get_block().
 *
 * The LRUs themselves only need locking against invalidate_bh_lrus.  We use
 * a local पूर्णांकerrupt disable क्रम that.
 */

#घोषणा BH_LRU_SIZE	16

काष्ठा bh_lru अणु
	काष्ठा buffer_head *bhs[BH_LRU_SIZE];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा bh_lru, bh_lrus) = अणुअणु शून्य पूर्णपूर्ण;

#अगर_घोषित CONFIG_SMP
#घोषणा bh_lru_lock()	local_irq_disable()
#घोषणा bh_lru_unlock()	local_irq_enable()
#अन्यथा
#घोषणा bh_lru_lock()	preempt_disable()
#घोषणा bh_lru_unlock()	preempt_enable()
#पूर्ण_अगर

अटल अंतरभूत व्योम check_irqs_on(व्योम)
अणु
#अगर_घोषित irqs_disabled
	BUG_ON(irqs_disabled());
#पूर्ण_अगर
पूर्ण

/*
 * Install a buffer_head पूर्णांकo this cpu's LRU.  If not alपढ़ोy in the LRU, it is
 * inserted at the front, and the buffer_head at the back अगर any is evicted.
 * Or, अगर alपढ़ोy in the LRU it is moved to the front.
 */
अटल व्योम bh_lru_install(काष्ठा buffer_head *bh)
अणु
	काष्ठा buffer_head *evictee = bh;
	काष्ठा bh_lru *b;
	पूर्णांक i;

	check_irqs_on();
	/*
	 * the refcount of buffer_head in bh_lru prevents dropping the
	 * attached page(i.e., try_to_मुक्त_buffers) so it could cause
	 * failing page migration.
	 * Skip putting upcoming bh पूर्णांकo bh_lru until migration is करोne.
	 */
	अगर (lru_cache_disabled())
		वापस;

	bh_lru_lock();

	b = this_cpu_ptr(&bh_lrus);
	क्रम (i = 0; i < BH_LRU_SIZE; i++) अणु
		swap(evictee, b->bhs[i]);
		अगर (evictee == bh) अणु
			bh_lru_unlock();
			वापस;
		पूर्ण
	पूर्ण

	get_bh(bh);
	bh_lru_unlock();
	brअन्यथा(evictee);
पूर्ण

/*
 * Look up the bh in this cpu's LRU.  If it's there, move it to the head.
 */
अटल काष्ठा buffer_head *
lookup_bh_lru(काष्ठा block_device *bdev, sector_t block, अचिन्हित size)
अणु
	काष्ठा buffer_head *ret = शून्य;
	अचिन्हित पूर्णांक i;

	check_irqs_on();
	bh_lru_lock();
	क्रम (i = 0; i < BH_LRU_SIZE; i++) अणु
		काष्ठा buffer_head *bh = __this_cpu_पढ़ो(bh_lrus.bhs[i]);

		अगर (bh && bh->b_blocknr == block && bh->b_bdev == bdev &&
		    bh->b_size == size) अणु
			अगर (i) अणु
				जबतक (i) अणु
					__this_cpu_ग_लिखो(bh_lrus.bhs[i],
						__this_cpu_पढ़ो(bh_lrus.bhs[i - 1]));
					i--;
				पूर्ण
				__this_cpu_ग_लिखो(bh_lrus.bhs[0], bh);
			पूर्ण
			get_bh(bh);
			ret = bh;
			अवरोध;
		पूर्ण
	पूर्ण
	bh_lru_unlock();
	वापस ret;
पूर्ण

/*
 * Perक्रमm a pagecache lookup क्रम the matching buffer.  If it's there, refresh
 * it in the LRU and mark it as accessed.  If it is not present then वापस
 * शून्य
 */
काष्ठा buffer_head *
__find_get_block(काष्ठा block_device *bdev, sector_t block, अचिन्हित size)
अणु
	काष्ठा buffer_head *bh = lookup_bh_lru(bdev, block, size);

	अगर (bh == शून्य) अणु
		/* __find_get_block_slow will mark the page accessed */
		bh = __find_get_block_slow(bdev, block);
		अगर (bh)
			bh_lru_install(bh);
	पूर्ण अन्यथा
		touch_buffer(bh);

	वापस bh;
पूर्ण
EXPORT_SYMBOL(__find_get_block);

/*
 * __getblk_gfp() will locate (and, अगर necessary, create) the buffer_head
 * which corresponds to the passed block_device, block and size. The
 * वापसed buffer has its reference count incremented.
 *
 * __getblk_gfp() will lock up the machine अगर grow_dev_page's
 * try_to_मुक्त_buffers() attempt is failing.  FIXME, perhaps?
 */
काष्ठा buffer_head *
__getblk_gfp(काष्ठा block_device *bdev, sector_t block,
	     अचिन्हित size, gfp_t gfp)
अणु
	काष्ठा buffer_head *bh = __find_get_block(bdev, block, size);

	might_sleep();
	अगर (bh == शून्य)
		bh = __getblk_slow(bdev, block, size, gfp);
	वापस bh;
पूर्ण
EXPORT_SYMBOL(__getblk_gfp);

/*
 * Do async पढ़ो-ahead on a buffer..
 */
व्योम __bपढ़ोahead(काष्ठा block_device *bdev, sector_t block, अचिन्हित size)
अणु
	काष्ठा buffer_head *bh = __getblk(bdev, block, size);
	अगर (likely(bh)) अणु
		ll_rw_block(REQ_OP_READ, REQ_RAHEAD, 1, &bh);
		brअन्यथा(bh);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__bपढ़ोahead);

व्योम __bपढ़ोahead_gfp(काष्ठा block_device *bdev, sector_t block, अचिन्हित size,
		      gfp_t gfp)
अणु
	काष्ठा buffer_head *bh = __getblk_gfp(bdev, block, size, gfp);
	अगर (likely(bh)) अणु
		ll_rw_block(REQ_OP_READ, REQ_RAHEAD, 1, &bh);
		brअन्यथा(bh);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__bपढ़ोahead_gfp);

/**
 *  __bपढ़ो_gfp() - पढ़ोs a specअगरied block and वापसs the bh
 *  @bdev: the block_device to पढ़ो from
 *  @block: number of block
 *  @size: size (in bytes) to पढ़ो
 *  @gfp: page allocation flag
 *
 *  Reads a specअगरied block, and वापसs buffer head that contains it.
 *  The page cache can be allocated from non-movable area
 *  not to prevent page migration अगर you set gfp to zero.
 *  It वापसs शून्य अगर the block was unपढ़ोable.
 */
काष्ठा buffer_head *
__bपढ़ो_gfp(काष्ठा block_device *bdev, sector_t block,
		   अचिन्हित size, gfp_t gfp)
अणु
	काष्ठा buffer_head *bh = __getblk_gfp(bdev, block, size, gfp);

	अगर (likely(bh) && !buffer_uptodate(bh))
		bh = __bपढ़ो_slow(bh);
	वापस bh;
पूर्ण
EXPORT_SYMBOL(__bपढ़ो_gfp);

अटल व्योम __invalidate_bh_lrus(काष्ठा bh_lru *b)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BH_LRU_SIZE; i++) अणु
		brअन्यथा(b->bhs[i]);
		b->bhs[i] = शून्य;
	पूर्ण
पूर्ण
/*
 * invalidate_bh_lrus() is called rarely - but not only at unmount.
 * This करोesn't race because it runs in each cpu either in irq
 * or with preempt disabled.
 */
अटल व्योम invalidate_bh_lru(व्योम *arg)
अणु
	काष्ठा bh_lru *b = &get_cpu_var(bh_lrus);

	__invalidate_bh_lrus(b);
	put_cpu_var(bh_lrus);
पूर्ण

bool has_bh_in_lru(पूर्णांक cpu, व्योम *dummy)
अणु
	काष्ठा bh_lru *b = per_cpu_ptr(&bh_lrus, cpu);
	पूर्णांक i;
	
	क्रम (i = 0; i < BH_LRU_SIZE; i++) अणु
		अगर (b->bhs[i])
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम invalidate_bh_lrus(व्योम)
अणु
	on_each_cpu_cond(has_bh_in_lru, invalidate_bh_lru, शून्य, 1);
पूर्ण
EXPORT_SYMBOL_GPL(invalidate_bh_lrus);

व्योम invalidate_bh_lrus_cpu(पूर्णांक cpu)
अणु
	काष्ठा bh_lru *b;

	bh_lru_lock();
	b = per_cpu_ptr(&bh_lrus, cpu);
	__invalidate_bh_lrus(b);
	bh_lru_unlock();
पूर्ण

व्योम set_bh_page(काष्ठा buffer_head *bh,
		काष्ठा page *page, अचिन्हित दीर्घ offset)
अणु
	bh->b_page = page;
	BUG_ON(offset >= PAGE_SIZE);
	अगर (PageHighMem(page))
		/*
		 * This catches illegal uses and preserves the offset:
		 */
		bh->b_data = (अक्षर *)(0 + offset);
	अन्यथा
		bh->b_data = page_address(page) + offset;
पूर्ण
EXPORT_SYMBOL(set_bh_page);

/*
 * Called when truncating a buffer on a page completely.
 */

/* Bits that are cleared during an invalidate */
#घोषणा BUFFER_FLAGS_DISCARD \
	(1 << BH_Mapped | 1 << BH_New | 1 << BH_Req | \
	 1 << BH_Delay | 1 << BH_Unwritten)

अटल व्योम discard_buffer(काष्ठा buffer_head * bh)
अणु
	अचिन्हित दीर्घ b_state, b_state_old;

	lock_buffer(bh);
	clear_buffer_dirty(bh);
	bh->b_bdev = शून्य;
	b_state = bh->b_state;
	क्रम (;;) अणु
		b_state_old = cmpxchg(&bh->b_state, b_state,
				      (b_state & ~BUFFER_FLAGS_DISCARD));
		अगर (b_state_old == b_state)
			अवरोध;
		b_state = b_state_old;
	पूर्ण
	unlock_buffer(bh);
पूर्ण

/**
 * block_invalidatepage - invalidate part or all of a buffer-backed page
 *
 * @page: the page which is affected
 * @offset: start of the range to invalidate
 * @length: length of the range to invalidate
 *
 * block_invalidatepage() is called when all or part of the page has become
 * invalidated by a truncate operation.
 *
 * block_invalidatepage() करोes not have to release all buffers, but it must
 * ensure that no dirty buffer is left outside @offset and that no I/O
 * is underway against any of the blocks which are outside the truncation
 * poपूर्णांक.  Because the caller is about to मुक्त (and possibly reuse) those
 * blocks on-disk.
 */
व्योम block_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
			  अचिन्हित पूर्णांक length)
अणु
	काष्ठा buffer_head *head, *bh, *next;
	अचिन्हित पूर्णांक curr_off = 0;
	अचिन्हित पूर्णांक stop = length + offset;

	BUG_ON(!PageLocked(page));
	अगर (!page_has_buffers(page))
		जाओ out;

	/*
	 * Check क्रम overflow
	 */
	BUG_ON(stop > PAGE_SIZE || stop < length);

	head = page_buffers(page);
	bh = head;
	करो अणु
		अचिन्हित पूर्णांक next_off = curr_off + bh->b_size;
		next = bh->b_this_page;

		/*
		 * Are we still fully in range ?
		 */
		अगर (next_off > stop)
			जाओ out;

		/*
		 * is this block fully invalidated?
		 */
		अगर (offset <= curr_off)
			discard_buffer(bh);
		curr_off = next_off;
		bh = next;
	पूर्ण जबतक (bh != head);

	/*
	 * We release buffers only अगर the entire page is being invalidated.
	 * The get_block cached value has been unconditionally invalidated,
	 * so real IO is not possible anymore.
	 */
	अगर (length == PAGE_SIZE)
		try_to_release_page(page, 0);
out:
	वापस;
पूर्ण
EXPORT_SYMBOL(block_invalidatepage);


/*
 * We attach and possibly dirty the buffers atomically wrt
 * __set_page_dirty_buffers() via निजी_lock.  try_to_मुक्त_buffers
 * is alपढ़ोy excluded via the page lock.
 */
व्योम create_empty_buffers(काष्ठा page *page,
			अचिन्हित दीर्घ blocksize, अचिन्हित दीर्घ b_state)
अणु
	काष्ठा buffer_head *bh, *head, *tail;

	head = alloc_page_buffers(page, blocksize, true);
	bh = head;
	करो अणु
		bh->b_state |= b_state;
		tail = bh;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh);
	tail->b_this_page = head;

	spin_lock(&page->mapping->निजी_lock);
	अगर (PageUptodate(page) || PageDirty(page)) अणु
		bh = head;
		करो अणु
			अगर (PageDirty(page))
				set_buffer_dirty(bh);
			अगर (PageUptodate(page))
				set_buffer_uptodate(bh);
			bh = bh->b_this_page;
		पूर्ण जबतक (bh != head);
	पूर्ण
	attach_page_निजी(page, head);
	spin_unlock(&page->mapping->निजी_lock);
पूर्ण
EXPORT_SYMBOL(create_empty_buffers);

/**
 * clean_bdev_aliases: clean a range of buffers in block device
 * @bdev: Block device to clean buffers in
 * @block: Start of a range of blocks to clean
 * @len: Number of blocks to clean
 *
 * We are taking a range of blocks क्रम data and we करोn't want ग_लिखोback of any
 * buffer-cache aliases starting from वापस from this function and until the
 * moment when something will explicitly mark the buffer dirty (hopefully that
 * will not happen until we will मुक्त that block ;-) We करोn't even need to mark
 * it not-uptodate - nobody can expect anything from a newly allocated buffer
 * anyway. We used to use unmap_buffer() क्रम such invalidation, but that was
 * wrong. We definitely करोn't want to mark the alias unmapped, क्रम example - it
 * would confuse anyone who might pick it with bपढ़ो() afterwards...
 *
 * Also..  Note that bक्रमget() करोesn't lock the buffer.  So there can be
 * ग_लिखोout I/O going on against recently-मुक्तd buffers.  We करोn't रुको on that
 * I/O in bक्रमget() - it's more efficient to रुको on the I/O only अगर we really
 * need to.  That happens here.
 */
व्योम clean_bdev_aliases(काष्ठा block_device *bdev, sector_t block, sector_t len)
अणु
	काष्ठा inode *bd_inode = bdev->bd_inode;
	काष्ठा address_space *bd_mapping = bd_inode->i_mapping;
	काष्ठा pagevec pvec;
	pgoff_t index = block >> (PAGE_SHIFT - bd_inode->i_blkbits);
	pgoff_t end;
	पूर्णांक i, count;
	काष्ठा buffer_head *bh;
	काष्ठा buffer_head *head;

	end = (block + len - 1) >> (PAGE_SHIFT - bd_inode->i_blkbits);
	pagevec_init(&pvec);
	जबतक (pagevec_lookup_range(&pvec, bd_mapping, &index, end)) अणु
		count = pagevec_count(&pvec);
		क्रम (i = 0; i < count; i++) अणु
			काष्ठा page *page = pvec.pages[i];

			अगर (!page_has_buffers(page))
				जारी;
			/*
			 * We use page lock instead of bd_mapping->निजी_lock
			 * to pin buffers here since we can afक्रमd to sleep and
			 * it scales better than a global spinlock lock.
			 */
			lock_page(page);
			/* Recheck when the page is locked which pins bhs */
			अगर (!page_has_buffers(page))
				जाओ unlock_page;
			head = page_buffers(page);
			bh = head;
			करो अणु
				अगर (!buffer_mapped(bh) || (bh->b_blocknr < block))
					जाओ next;
				अगर (bh->b_blocknr >= block + len)
					अवरोध;
				clear_buffer_dirty(bh);
				रुको_on_buffer(bh);
				clear_buffer_req(bh);
next:
				bh = bh->b_this_page;
			पूर्ण जबतक (bh != head);
unlock_page:
			unlock_page(page);
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
		/* End of range alपढ़ोy reached? */
		अगर (index > end || !index)
			अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(clean_bdev_aliases);

/*
 * Size is a घातer-of-two in the range 512..PAGE_SIZE,
 * and the हाल we care about most is PAGE_SIZE.
 *
 * So this *could* possibly be written with those
 * स्थिरraपूर्णांकs in mind (relevant mostly अगर some
 * architecture has a slow bit-scan inकाष्ठाion)
 */
अटल अंतरभूत पूर्णांक block_size_bits(अचिन्हित पूर्णांक blocksize)
अणु
	वापस ilog2(blocksize);
पूर्ण

अटल काष्ठा buffer_head *create_page_buffers(काष्ठा page *page, काष्ठा inode *inode, अचिन्हित पूर्णांक b_state)
अणु
	BUG_ON(!PageLocked(page));

	अगर (!page_has_buffers(page))
		create_empty_buffers(page, 1 << READ_ONCE(inode->i_blkbits),
				     b_state);
	वापस page_buffers(page);
पूर्ण

/*
 * NOTE! All mapped/uptodate combinations are valid:
 *
 *	Mapped	Uptodate	Meaning
 *
 *	No	No		"unknown" - must करो get_block()
 *	No	Yes		"hole" - zero-filled
 *	Yes	No		"allocated" - allocated on disk, not पढ़ो in
 *	Yes	Yes		"valid" - allocated and up-to-date in memory.
 *
 * "Dirty" is valid only with the last हाल (mapped+uptodate).
 */

/*
 * While block_ग_लिखो_full_page is writing back the dirty buffers under
 * the page lock, whoever dirtied the buffers may decide to clean them
 * again at any समय.  We handle that by only looking at the buffer
 * state inside lock_buffer().
 *
 * If block_ग_लिखो_full_page() is called क्रम regular ग_लिखोback
 * (wbc->sync_mode == WB_SYNC_NONE) then it will redirty a page which has a
 * locked buffer.   This only can happen अगर someone has written the buffer
 * directly, with submit_bh().  At the address_space level PageWriteback
 * prevents this contention from occurring.
 *
 * If block_ग_लिखो_full_page() is called with wbc->sync_mode ==
 * WB_SYNC_ALL, the ग_लिखोs are posted using REQ_SYNC; this
 * causes the ग_लिखोs to be flagged as synchronous ग_लिखोs.
 */
पूर्णांक __block_ग_लिखो_full_page(काष्ठा inode *inode, काष्ठा page *page,
			get_block_t *get_block, काष्ठा ग_लिखोback_control *wbc,
			bh_end_io_t *handler)
अणु
	पूर्णांक err;
	sector_t block;
	sector_t last_block;
	काष्ठा buffer_head *bh, *head;
	अचिन्हित पूर्णांक blocksize, bbits;
	पूर्णांक nr_underway = 0;
	पूर्णांक ग_लिखो_flags = wbc_to_ग_लिखो_flags(wbc);

	head = create_page_buffers(page, inode,
					(1 << BH_Dirty)|(1 << BH_Uptodate));

	/*
	 * Be very careful.  We have no exclusion from __set_page_dirty_buffers
	 * here, and the (potentially unmapped) buffers may become dirty at
	 * any समय.  If a buffer becomes dirty here after we've inspected it
	 * then we just miss that fact, and the page stays dirty.
	 *
	 * Buffers outside i_size may be dirtied by __set_page_dirty_buffers;
	 * handle that here by just cleaning them.
	 */

	bh = head;
	blocksize = bh->b_size;
	bbits = block_size_bits(blocksize);

	block = (sector_t)page->index << (PAGE_SHIFT - bbits);
	last_block = (i_size_पढ़ो(inode) - 1) >> bbits;

	/*
	 * Get all the dirty buffers mapped to disk addresses and
	 * handle any aliases from the underlying blockdev's mapping.
	 */
	करो अणु
		अगर (block > last_block) अणु
			/*
			 * mapped buffers outside i_size will occur, because
			 * this page can be outside i_size when there is a
			 * truncate in progress.
			 */
			/*
			 * The buffer was zeroed by block_ग_लिखो_full_page()
			 */
			clear_buffer_dirty(bh);
			set_buffer_uptodate(bh);
		पूर्ण अन्यथा अगर ((!buffer_mapped(bh) || buffer_delay(bh)) &&
			   buffer_dirty(bh)) अणु
			WARN_ON(bh->b_size != blocksize);
			err = get_block(inode, block, bh, 1);
			अगर (err)
				जाओ recover;
			clear_buffer_delay(bh);
			अगर (buffer_new(bh)) अणु
				/* blockdev mappings never come here */
				clear_buffer_new(bh);
				clean_bdev_bh_alias(bh);
			पूर्ण
		पूर्ण
		bh = bh->b_this_page;
		block++;
	पूर्ण जबतक (bh != head);

	करो अणु
		अगर (!buffer_mapped(bh))
			जारी;
		/*
		 * If it's a fully non-blocking ग_लिखो attempt and we cannot
		 * lock the buffer then redirty the page.  Note that this can
		 * potentially cause a busy-रुको loop from ग_लिखोback thपढ़ोs
		 * and kswapd activity, but those code paths have their own
		 * higher-level throttling.
		 */
		अगर (wbc->sync_mode != WB_SYNC_NONE) अणु
			lock_buffer(bh);
		पूर्ण अन्यथा अगर (!trylock_buffer(bh)) अणु
			redirty_page_क्रम_ग_लिखोpage(wbc, page);
			जारी;
		पूर्ण
		अगर (test_clear_buffer_dirty(bh)) अणु
			mark_buffer_async_ग_लिखो_endio(bh, handler);
		पूर्ण अन्यथा अणु
			unlock_buffer(bh);
		पूर्ण
	पूर्ण जबतक ((bh = bh->b_this_page) != head);

	/*
	 * The page and its buffers are रक्षित by PageWriteback(), so we can
	 * drop the bh refcounts early.
	 */
	BUG_ON(PageWriteback(page));
	set_page_ग_लिखोback(page);

	करो अणु
		काष्ठा buffer_head *next = bh->b_this_page;
		अगर (buffer_async_ग_लिखो(bh)) अणु
			submit_bh_wbc(REQ_OP_WRITE, ग_लिखो_flags, bh,
					inode->i_ग_लिखो_hपूर्णांक, wbc);
			nr_underway++;
		पूर्ण
		bh = next;
	पूर्ण जबतक (bh != head);
	unlock_page(page);

	err = 0;
करोne:
	अगर (nr_underway == 0) अणु
		/*
		 * The page was marked dirty, but the buffers were
		 * clean.  Someone wrote them back by hand with
		 * ll_rw_block/submit_bh.  A rare हाल.
		 */
		end_page_ग_लिखोback(page);

		/*
		 * The page and buffer_heads can be released at any समय from
		 * here on.
		 */
	पूर्ण
	वापस err;

recover:
	/*
	 * ENOSPC, or some other error.  We may alपढ़ोy have added some
	 * blocks to the file, so we need to ग_लिखो these out to aव्योम
	 * exposing stale data.
	 * The page is currently locked and not marked क्रम ग_लिखोback
	 */
	bh = head;
	/* Recovery: lock and submit the mapped buffers */
	करो अणु
		अगर (buffer_mapped(bh) && buffer_dirty(bh) &&
		    !buffer_delay(bh)) अणु
			lock_buffer(bh);
			mark_buffer_async_ग_लिखो_endio(bh, handler);
		पूर्ण अन्यथा अणु
			/*
			 * The buffer may have been set dirty during
			 * attachment to a dirty page.
			 */
			clear_buffer_dirty(bh);
		पूर्ण
	पूर्ण जबतक ((bh = bh->b_this_page) != head);
	SetPageError(page);
	BUG_ON(PageWriteback(page));
	mapping_set_error(page->mapping, err);
	set_page_ग_लिखोback(page);
	करो अणु
		काष्ठा buffer_head *next = bh->b_this_page;
		अगर (buffer_async_ग_लिखो(bh)) अणु
			clear_buffer_dirty(bh);
			submit_bh_wbc(REQ_OP_WRITE, ग_लिखो_flags, bh,
					inode->i_ग_लिखो_hपूर्णांक, wbc);
			nr_underway++;
		पूर्ण
		bh = next;
	पूर्ण जबतक (bh != head);
	unlock_page(page);
	जाओ करोne;
पूर्ण
EXPORT_SYMBOL(__block_ग_लिखो_full_page);

/*
 * If a page has any new buffers, zero them out here, and mark them uptodate
 * and dirty so they'll be written out (in order to prevent uninitialised
 * block data from leaking). And clear the new bit.
 */
व्योम page_zero_new_buffers(काष्ठा page *page, अचिन्हित from, अचिन्हित to)
अणु
	अचिन्हित पूर्णांक block_start, block_end;
	काष्ठा buffer_head *head, *bh;

	BUG_ON(!PageLocked(page));
	अगर (!page_has_buffers(page))
		वापस;

	bh = head = page_buffers(page);
	block_start = 0;
	करो अणु
		block_end = block_start + bh->b_size;

		अगर (buffer_new(bh)) अणु
			अगर (block_end > from && block_start < to) अणु
				अगर (!PageUptodate(page)) अणु
					अचिन्हित start, size;

					start = max(from, block_start);
					size = min(to, block_end) - start;

					zero_user(page, start, size);
					set_buffer_uptodate(bh);
				पूर्ण

				clear_buffer_new(bh);
				mark_buffer_dirty(bh);
			पूर्ण
		पूर्ण

		block_start = block_end;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
पूर्ण
EXPORT_SYMBOL(page_zero_new_buffers);

अटल व्योम
iomap_to_bh(काष्ठा inode *inode, sector_t block, काष्ठा buffer_head *bh,
		काष्ठा iomap *iomap)
अणु
	loff_t offset = block << inode->i_blkbits;

	bh->b_bdev = iomap->bdev;

	/*
	 * Block poपूर्णांकs to offset in file we need to map, iomap contains
	 * the offset at which the map starts. If the map ends beक्रमe the
	 * current block, then करो not map the buffer and let the caller
	 * handle it.
	 */
	BUG_ON(offset >= iomap->offset + iomap->length);

	चयन (iomap->type) अणु
	हाल IOMAP_HOLE:
		/*
		 * If the buffer is not up to date or beyond the current खातापूर्ण,
		 * we need to mark it as new to ensure sub-block zeroing is
		 * executed अगर necessary.
		 */
		अगर (!buffer_uptodate(bh) ||
		    (offset >= i_size_पढ़ो(inode)))
			set_buffer_new(bh);
		अवरोध;
	हाल IOMAP_DELALLOC:
		अगर (!buffer_uptodate(bh) ||
		    (offset >= i_size_पढ़ो(inode)))
			set_buffer_new(bh);
		set_buffer_uptodate(bh);
		set_buffer_mapped(bh);
		set_buffer_delay(bh);
		अवरोध;
	हाल IOMAP_UNWRITTEN:
		/*
		 * For unwritten regions, we always need to ensure that regions
		 * in the block we are not writing to are zeroed. Mark the
		 * buffer as new to ensure this.
		 */
		set_buffer_new(bh);
		set_buffer_unwritten(bh);
		fallthrough;
	हाल IOMAP_MAPPED:
		अगर ((iomap->flags & IOMAP_F_NEW) ||
		    offset >= i_size_पढ़ो(inode))
			set_buffer_new(bh);
		bh->b_blocknr = (iomap->addr + offset - iomap->offset) >>
				inode->i_blkbits;
		set_buffer_mapped(bh);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक __block_ग_लिखो_begin_पूर्णांक(काष्ठा page *page, loff_t pos, अचिन्हित len,
		get_block_t *get_block, काष्ठा iomap *iomap)
अणु
	अचिन्हित from = pos & (PAGE_SIZE - 1);
	अचिन्हित to = from + len;
	काष्ठा inode *inode = page->mapping->host;
	अचिन्हित block_start, block_end;
	sector_t block;
	पूर्णांक err = 0;
	अचिन्हित blocksize, bbits;
	काष्ठा buffer_head *bh, *head, *रुको[2], **रुको_bh=रुको;

	BUG_ON(!PageLocked(page));
	BUG_ON(from > PAGE_SIZE);
	BUG_ON(to > PAGE_SIZE);
	BUG_ON(from > to);

	head = create_page_buffers(page, inode, 0);
	blocksize = head->b_size;
	bbits = block_size_bits(blocksize);

	block = (sector_t)page->index << (PAGE_SHIFT - bbits);

	क्रम(bh = head, block_start = 0; bh != head || !block_start;
	    block++, block_start=block_end, bh = bh->b_this_page) अणु
		block_end = block_start + blocksize;
		अगर (block_end <= from || block_start >= to) अणु
			अगर (PageUptodate(page)) अणु
				अगर (!buffer_uptodate(bh))
					set_buffer_uptodate(bh);
			पूर्ण
			जारी;
		पूर्ण
		अगर (buffer_new(bh))
			clear_buffer_new(bh);
		अगर (!buffer_mapped(bh)) अणु
			WARN_ON(bh->b_size != blocksize);
			अगर (get_block) अणु
				err = get_block(inode, block, bh, 1);
				अगर (err)
					अवरोध;
			पूर्ण अन्यथा अणु
				iomap_to_bh(inode, block, bh, iomap);
			पूर्ण

			अगर (buffer_new(bh)) अणु
				clean_bdev_bh_alias(bh);
				अगर (PageUptodate(page)) अणु
					clear_buffer_new(bh);
					set_buffer_uptodate(bh);
					mark_buffer_dirty(bh);
					जारी;
				पूर्ण
				अगर (block_end > to || block_start < from)
					zero_user_segments(page,
						to, block_end,
						block_start, from);
				जारी;
			पूर्ण
		पूर्ण
		अगर (PageUptodate(page)) अणु
			अगर (!buffer_uptodate(bh))
				set_buffer_uptodate(bh);
			जारी; 
		पूर्ण
		अगर (!buffer_uptodate(bh) && !buffer_delay(bh) &&
		    !buffer_unwritten(bh) &&
		     (block_start < from || block_end > to)) अणु
			ll_rw_block(REQ_OP_READ, 0, 1, &bh);
			*रुको_bh++=bh;
		पूर्ण
	पूर्ण
	/*
	 * If we issued पढ़ो requests - let them complete.
	 */
	जबतक(रुको_bh > रुको) अणु
		रुको_on_buffer(*--रुको_bh);
		अगर (!buffer_uptodate(*रुको_bh))
			err = -EIO;
	पूर्ण
	अगर (unlikely(err))
		page_zero_new_buffers(page, from, to);
	वापस err;
पूर्ण

पूर्णांक __block_ग_लिखो_begin(काष्ठा page *page, loff_t pos, अचिन्हित len,
		get_block_t *get_block)
अणु
	वापस __block_ग_लिखो_begin_पूर्णांक(page, pos, len, get_block, शून्य);
पूर्ण
EXPORT_SYMBOL(__block_ग_लिखो_begin);

अटल पूर्णांक __block_commit_ग_लिखो(काष्ठा inode *inode, काष्ठा page *page,
		अचिन्हित from, अचिन्हित to)
अणु
	अचिन्हित block_start, block_end;
	पूर्णांक partial = 0;
	अचिन्हित blocksize;
	काष्ठा buffer_head *bh, *head;

	bh = head = page_buffers(page);
	blocksize = bh->b_size;

	block_start = 0;
	करो अणु
		block_end = block_start + blocksize;
		अगर (block_end <= from || block_start >= to) अणु
			अगर (!buffer_uptodate(bh))
				partial = 1;
		पूर्ण अन्यथा अणु
			set_buffer_uptodate(bh);
			mark_buffer_dirty(bh);
		पूर्ण
		अगर (buffer_new(bh))
			clear_buffer_new(bh);

		block_start = block_end;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);

	/*
	 * If this is a partial ग_लिखो which happened to make all buffers
	 * uptodate then we can optimize away a bogus पढ़ोpage() क्रम
	 * the next पढ़ो(). Here we 'discover' whether the page went
	 * uptodate as a result of this (potentially partial) ग_लिखो.
	 */
	अगर (!partial)
		SetPageUptodate(page);
	वापस 0;
पूर्ण

/*
 * block_ग_लिखो_begin takes care of the basic task of block allocation and
 * bringing partial ग_लिखो blocks uptodate first.
 *
 * The fileप्रणाली needs to handle block truncation upon failure.
 */
पूर्णांक block_ग_लिखो_begin(काष्ठा address_space *mapping, loff_t pos, अचिन्हित len,
		अचिन्हित flags, काष्ठा page **pagep, get_block_t *get_block)
अणु
	pgoff_t index = pos >> PAGE_SHIFT;
	काष्ठा page *page;
	पूर्णांक status;

	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;

	status = __block_ग_लिखो_begin(page, pos, len, get_block);
	अगर (unlikely(status)) अणु
		unlock_page(page);
		put_page(page);
		page = शून्य;
	पूर्ण

	*pagep = page;
	वापस status;
पूर्ण
EXPORT_SYMBOL(block_ग_लिखो_begin);

पूर्णांक block_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	अचिन्हित start;

	start = pos & (PAGE_SIZE - 1);

	अगर (unlikely(copied < len)) अणु
		/*
		 * The buffers that were written will now be uptodate, so we
		 * करोn't have to worry about a पढ़ोpage पढ़ोing them and
		 * overwriting a partial ग_लिखो. However अगर we have encountered
		 * a लघु ग_लिखो and only partially written पूर्णांकo a buffer, it
		 * will not be marked uptodate, so a पढ़ोpage might come in and
		 * destroy our partial ग_लिखो.
		 *
		 * Do the simplest thing, and just treat any लघु ग_लिखो to a
		 * non uptodate page as a zero-length ग_लिखो, and क्रमce the
		 * caller to reकरो the whole thing.
		 */
		अगर (!PageUptodate(page))
			copied = 0;

		page_zero_new_buffers(page, start+copied, start+len);
	पूर्ण
	flush_dcache_page(page);

	/* This could be a लघु (even 0-length) commit */
	__block_commit_ग_लिखो(inode, page, start, start+copied);

	वापस copied;
पूर्ण
EXPORT_SYMBOL(block_ग_लिखो_end);

पूर्णांक generic_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = mapping->host;
	loff_t old_size = inode->i_size;
	bool i_size_changed = false;

	copied = block_ग_लिखो_end(file, mapping, pos, len, copied, page, fsdata);

	/*
	 * No need to use i_size_पढ़ो() here, the i_size cannot change under us
	 * because we hold i_rwsem.
	 *
	 * But it's important to update i_size जबतक still holding page lock:
	 * page ग_लिखोout could otherwise come in and zero beyond i_size.
	 */
	अगर (pos + copied > inode->i_size) अणु
		i_size_ग_लिखो(inode, pos + copied);
		i_size_changed = true;
	पूर्ण

	unlock_page(page);
	put_page(page);

	अगर (old_size < pos)
		pagecache_isize_extended(inode, old_size, pos);
	/*
	 * Don't mark the inode dirty under page lock. First, it unnecessarily
	 * makes the holding समय of page lock दीर्घer. Second, it क्रमces lock
	 * ordering of page lock and transaction start क्रम journaling
	 * fileप्रणालीs.
	 */
	अगर (i_size_changed)
		mark_inode_dirty(inode);
	वापस copied;
पूर्ण
EXPORT_SYMBOL(generic_ग_लिखो_end);

/*
 * block_is_partially_uptodate checks whether buffers within a page are
 * uptodate or not.
 *
 * Returns true अगर all buffers which correspond to a file portion
 * we want to पढ़ो are uptodate.
 */
पूर्णांक block_is_partially_uptodate(काष्ठा page *page, अचिन्हित दीर्घ from,
					अचिन्हित दीर्घ count)
अणु
	अचिन्हित block_start, block_end, blocksize;
	अचिन्हित to;
	काष्ठा buffer_head *bh, *head;
	पूर्णांक ret = 1;

	अगर (!page_has_buffers(page))
		वापस 0;

	head = page_buffers(page);
	blocksize = head->b_size;
	to = min_t(अचिन्हित, PAGE_SIZE - from, count);
	to = from + to;
	अगर (from < blocksize && to > PAGE_SIZE - blocksize)
		वापस 0;

	bh = head;
	block_start = 0;
	करो अणु
		block_end = block_start + blocksize;
		अगर (block_end > from && block_start < to) अणु
			अगर (!buffer_uptodate(bh)) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			अगर (block_end >= to)
				अवरोध;
		पूर्ण
		block_start = block_end;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(block_is_partially_uptodate);

/*
 * Generic "read page" function क्रम block devices that have the normal
 * get_block functionality. This is most of the block device fileप्रणालीs.
 * Reads the page asynchronously --- the unlock_buffer() and
 * set/clear_buffer_uptodate() functions propagate buffer state पूर्णांकo the
 * page काष्ठा once IO has completed.
 */
पूर्णांक block_पढ़ो_full_page(काष्ठा page *page, get_block_t *get_block)
अणु
	काष्ठा inode *inode = page->mapping->host;
	sector_t iblock, lblock;
	काष्ठा buffer_head *bh, *head, *arr[MAX_BUF_PER_PAGE];
	अचिन्हित पूर्णांक blocksize, bbits;
	पूर्णांक nr, i;
	पूर्णांक fully_mapped = 1;

	head = create_page_buffers(page, inode, 0);
	blocksize = head->b_size;
	bbits = block_size_bits(blocksize);

	iblock = (sector_t)page->index << (PAGE_SHIFT - bbits);
	lblock = (i_size_पढ़ो(inode)+blocksize-1) >> bbits;
	bh = head;
	nr = 0;
	i = 0;

	करो अणु
		अगर (buffer_uptodate(bh))
			जारी;

		अगर (!buffer_mapped(bh)) अणु
			पूर्णांक err = 0;

			fully_mapped = 0;
			अगर (iblock < lblock) अणु
				WARN_ON(bh->b_size != blocksize);
				err = get_block(inode, iblock, bh, 0);
				अगर (err)
					SetPageError(page);
			पूर्ण
			अगर (!buffer_mapped(bh)) अणु
				zero_user(page, i * blocksize, blocksize);
				अगर (!err)
					set_buffer_uptodate(bh);
				जारी;
			पूर्ण
			/*
			 * get_block() might have updated the buffer
			 * synchronously
			 */
			अगर (buffer_uptodate(bh))
				जारी;
		पूर्ण
		arr[nr++] = bh;
	पूर्ण जबतक (i++, iblock++, (bh = bh->b_this_page) != head);

	अगर (fully_mapped)
		SetPageMappedToDisk(page);

	अगर (!nr) अणु
		/*
		 * All buffers are uptodate - we can set the page uptodate
		 * as well. But not अगर get_block() वापसed an error.
		 */
		अगर (!PageError(page))
			SetPageUptodate(page);
		unlock_page(page);
		वापस 0;
	पूर्ण

	/* Stage two: lock the buffers */
	क्रम (i = 0; i < nr; i++) अणु
		bh = arr[i];
		lock_buffer(bh);
		mark_buffer_async_पढ़ो(bh);
	पूर्ण

	/*
	 * Stage 3: start the IO.  Check क्रम uptodateness
	 * inside the buffer lock in हाल another process पढ़ोing
	 * the underlying blockdev brought it uptodate (the sct fix).
	 */
	क्रम (i = 0; i < nr; i++) अणु
		bh = arr[i];
		अगर (buffer_uptodate(bh))
			end_buffer_async_पढ़ो(bh, 1);
		अन्यथा
			submit_bh(REQ_OP_READ, 0, bh);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(block_पढ़ो_full_page);

/* utility function क्रम fileप्रणालीs that need to करो work on expanding
 * truncates.  Uses fileप्रणाली pagecache ग_लिखोs to allow the fileप्रणाली to
 * deal with the hole.  
 */
पूर्णांक generic_cont_expand_simple(काष्ठा inode *inode, loff_t size)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;
	व्योम *fsdata;
	पूर्णांक err;

	err = inode_newsize_ok(inode, size);
	अगर (err)
		जाओ out;

	err = pagecache_ग_लिखो_begin(शून्य, mapping, size, 0,
				    AOP_FLAG_CONT_EXPAND, &page, &fsdata);
	अगर (err)
		जाओ out;

	err = pagecache_ग_लिखो_end(शून्य, mapping, size, 0, 0, page, fsdata);
	BUG_ON(err > 0);

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(generic_cont_expand_simple);

अटल पूर्णांक cont_expand_zero(काष्ठा file *file, काष्ठा address_space *mapping,
			    loff_t pos, loff_t *bytes)
अणु
	काष्ठा inode *inode = mapping->host;
	अचिन्हित पूर्णांक blocksize = i_blocksize(inode);
	काष्ठा page *page;
	व्योम *fsdata;
	pgoff_t index, curidx;
	loff_t curpos;
	अचिन्हित zerofrom, offset, len;
	पूर्णांक err = 0;

	index = pos >> PAGE_SHIFT;
	offset = pos & ~PAGE_MASK;

	जबतक (index > (curidx = (curpos = *bytes)>>PAGE_SHIFT)) अणु
		zerofrom = curpos & ~PAGE_MASK;
		अगर (zerofrom & (blocksize-1)) अणु
			*bytes |= (blocksize-1);
			(*bytes)++;
		पूर्ण
		len = PAGE_SIZE - zerofrom;

		err = pagecache_ग_लिखो_begin(file, mapping, curpos, len, 0,
					    &page, &fsdata);
		अगर (err)
			जाओ out;
		zero_user(page, zerofrom, len);
		err = pagecache_ग_लिखो_end(file, mapping, curpos, len, len,
						page, fsdata);
		अगर (err < 0)
			जाओ out;
		BUG_ON(err != len);
		err = 0;

		balance_dirty_pages_ratelimited(mapping);

		अगर (fatal_संकेत_pending(current)) अणु
			err = -EINTR;
			जाओ out;
		पूर्ण
	पूर्ण

	/* page covers the boundary, find the boundary offset */
	अगर (index == curidx) अणु
		zerofrom = curpos & ~PAGE_MASK;
		/* अगर we will expand the thing last block will be filled */
		अगर (offset <= zerofrom) अणु
			जाओ out;
		पूर्ण
		अगर (zerofrom & (blocksize-1)) अणु
			*bytes |= (blocksize-1);
			(*bytes)++;
		पूर्ण
		len = offset - zerofrom;

		err = pagecache_ग_लिखो_begin(file, mapping, curpos, len, 0,
					    &page, &fsdata);
		अगर (err)
			जाओ out;
		zero_user(page, zerofrom, len);
		err = pagecache_ग_लिखो_end(file, mapping, curpos, len, len,
						page, fsdata);
		अगर (err < 0)
			जाओ out;
		BUG_ON(err != len);
		err = 0;
	पूर्ण
out:
	वापस err;
पूर्ण

/*
 * For moronic fileप्रणालीs that करो not allow holes in file.
 * We may have to extend the file.
 */
पूर्णांक cont_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata,
			get_block_t *get_block, loff_t *bytes)
अणु
	काष्ठा inode *inode = mapping->host;
	अचिन्हित पूर्णांक blocksize = i_blocksize(inode);
	अचिन्हित पूर्णांक zerofrom;
	पूर्णांक err;

	err = cont_expand_zero(file, mapping, pos, bytes);
	अगर (err)
		वापस err;

	zerofrom = *bytes & ~PAGE_MASK;
	अगर (pos+len > *bytes && zerofrom & (blocksize-1)) अणु
		*bytes |= (blocksize-1);
		(*bytes)++;
	पूर्ण

	वापस block_ग_लिखो_begin(mapping, pos, len, flags, pagep, get_block);
पूर्ण
EXPORT_SYMBOL(cont_ग_लिखो_begin);

पूर्णांक block_commit_ग_लिखो(काष्ठा page *page, अचिन्हित from, अचिन्हित to)
अणु
	काष्ठा inode *inode = page->mapping->host;
	__block_commit_ग_लिखो(inode,page,from,to);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(block_commit_ग_लिखो);

/*
 * block_page_mkग_लिखो() is not allowed to change the file size as it माला_लो
 * called from a page fault handler when a page is first dirtied. Hence we must
 * be careful to check क्रम खातापूर्ण conditions here. We set the page up correctly
 * क्रम a written page which means we get ENOSPC checking when writing पूर्णांकo
 * holes and correct delalloc and unwritten extent mapping on fileप्रणालीs that
 * support these features.
 *
 * We are not allowed to take the i_mutex here so we have to play games to
 * protect against truncate races as the page could now be beyond खातापूर्ण.  Because
 * truncate ग_लिखोs the inode size beक्रमe removing pages, once we have the
 * page lock we can determine safely अगर the page is beyond खातापूर्ण. If it is not
 * beyond खातापूर्ण, then the page is guaranteed safe against truncation until we
 * unlock the page.
 *
 * Direct callers of this function should protect against fileप्रणाली मुक्तzing
 * using sb_start_pagefault() - sb_end_pagefault() functions.
 */
पूर्णांक block_page_mkग_लिखो(काष्ठा vm_area_काष्ठा *vma, काष्ठा vm_fault *vmf,
			 get_block_t get_block)
अणु
	काष्ठा page *page = vmf->page;
	काष्ठा inode *inode = file_inode(vma->vm_file);
	अचिन्हित दीर्घ end;
	loff_t size;
	पूर्णांक ret;

	lock_page(page);
	size = i_size_पढ़ो(inode);
	अगर ((page->mapping != inode->i_mapping) ||
	    (page_offset(page) > size)) अणु
		/* We overload EFAULT to mean page got truncated */
		ret = -EFAULT;
		जाओ out_unlock;
	पूर्ण

	/* page is wholly or partially inside खातापूर्ण */
	अगर (((page->index + 1) << PAGE_SHIFT) > size)
		end = size & ~PAGE_MASK;
	अन्यथा
		end = PAGE_SIZE;

	ret = __block_ग_लिखो_begin(page, 0, end, get_block);
	अगर (!ret)
		ret = block_commit_ग_लिखो(page, 0, end);

	अगर (unlikely(ret < 0))
		जाओ out_unlock;
	set_page_dirty(page);
	रुको_क्रम_stable_page(page);
	वापस 0;
out_unlock:
	unlock_page(page);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(block_page_mkग_लिखो);

/*
 * nobh_ग_लिखो_begin()'s preपढ़ोs are special: the buffer_heads are मुक्तd
 * immediately, जबतक under the page lock.  So it needs a special end_io
 * handler which करोes not touch the bh after unlocking it.
 */
अटल व्योम end_buffer_पढ़ो_nobh(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	__end_buffer_पढ़ो_notouch(bh, uptodate);
पूर्ण

/*
 * Attach the singly-linked list of buffers created by nobh_ग_लिखो_begin, to
 * the page (converting it to circular linked list and taking care of page
 * dirty races).
 */
अटल व्योम attach_nobh_buffers(काष्ठा page *page, काष्ठा buffer_head *head)
अणु
	काष्ठा buffer_head *bh;

	BUG_ON(!PageLocked(page));

	spin_lock(&page->mapping->निजी_lock);
	bh = head;
	करो अणु
		अगर (PageDirty(page))
			set_buffer_dirty(bh);
		अगर (!bh->b_this_page)
			bh->b_this_page = head;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);
	attach_page_निजी(page, head);
	spin_unlock(&page->mapping->निजी_lock);
पूर्ण

/*
 * On entry, the page is fully not uptodate.
 * On निकास the page is fully uptodate in the areas outside (from,to)
 * The fileप्रणाली needs to handle block truncation upon failure.
 */
पूर्णांक nobh_ग_लिखो_begin(काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata,
			get_block_t *get_block)
अणु
	काष्ठा inode *inode = mapping->host;
	स्थिर अचिन्हित blkbits = inode->i_blkbits;
	स्थिर अचिन्हित blocksize = 1 << blkbits;
	काष्ठा buffer_head *head, *bh;
	काष्ठा page *page;
	pgoff_t index;
	अचिन्हित from, to;
	अचिन्हित block_in_page;
	अचिन्हित block_start, block_end;
	sector_t block_in_file;
	पूर्णांक nr_पढ़ोs = 0;
	पूर्णांक ret = 0;
	पूर्णांक is_mapped_to_disk = 1;

	index = pos >> PAGE_SHIFT;
	from = pos & (PAGE_SIZE - 1);
	to = from + len;

	page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
	अगर (!page)
		वापस -ENOMEM;
	*pagep = page;
	*fsdata = शून्य;

	अगर (page_has_buffers(page)) अणु
		ret = __block_ग_लिखो_begin(page, pos, len, get_block);
		अगर (unlikely(ret))
			जाओ out_release;
		वापस ret;
	पूर्ण

	अगर (PageMappedToDisk(page))
		वापस 0;

	/*
	 * Allocate buffers so that we can keep track of state, and potentially
	 * attach them to the page अगर an error occurs. In the common हाल of
	 * no error, they will just be मुक्तd again without ever being attached
	 * to the page (which is all OK, because we're under the page lock).
	 *
	 * Be careful: the buffer linked list is a शून्य terminated one, rather
	 * than the circular one we're used to.
	 */
	head = alloc_page_buffers(page, blocksize, false);
	अगर (!head) अणु
		ret = -ENOMEM;
		जाओ out_release;
	पूर्ण

	block_in_file = (sector_t)page->index << (PAGE_SHIFT - blkbits);

	/*
	 * We loop across all blocks in the page, whether or not they are
	 * part of the affected region.  This is so we can discover अगर the
	 * page is fully mapped-to-disk.
	 */
	क्रम (block_start = 0, block_in_page = 0, bh = head;
		  block_start < PAGE_SIZE;
		  block_in_page++, block_start += blocksize, bh = bh->b_this_page) अणु
		पूर्णांक create;

		block_end = block_start + blocksize;
		bh->b_state = 0;
		create = 1;
		अगर (block_start >= to)
			create = 0;
		ret = get_block(inode, block_in_file + block_in_page,
					bh, create);
		अगर (ret)
			जाओ failed;
		अगर (!buffer_mapped(bh))
			is_mapped_to_disk = 0;
		अगर (buffer_new(bh))
			clean_bdev_bh_alias(bh);
		अगर (PageUptodate(page)) अणु
			set_buffer_uptodate(bh);
			जारी;
		पूर्ण
		अगर (buffer_new(bh) || !buffer_mapped(bh)) अणु
			zero_user_segments(page, block_start, from,
							to, block_end);
			जारी;
		पूर्ण
		अगर (buffer_uptodate(bh))
			जारी;	/* reiserfs करोes this */
		अगर (block_start < from || block_end > to) अणु
			lock_buffer(bh);
			bh->b_end_io = end_buffer_पढ़ो_nobh;
			submit_bh(REQ_OP_READ, 0, bh);
			nr_पढ़ोs++;
		पूर्ण
	पूर्ण

	अगर (nr_पढ़ोs) अणु
		/*
		 * The page is locked, so these buffers are रक्षित from
		 * any VM or truncate activity.  Hence we करोn't need to care
		 * क्रम the buffer_head refcounts.
		 */
		क्रम (bh = head; bh; bh = bh->b_this_page) अणु
			रुको_on_buffer(bh);
			अगर (!buffer_uptodate(bh))
				ret = -EIO;
		पूर्ण
		अगर (ret)
			जाओ failed;
	पूर्ण

	अगर (is_mapped_to_disk)
		SetPageMappedToDisk(page);

	*fsdata = head; /* to be released by nobh_ग_लिखो_end */

	वापस 0;

failed:
	BUG_ON(!ret);
	/*
	 * Error recovery is a bit dअगरficult. We need to zero out blocks that
	 * were newly allocated, and dirty them to ensure they get written out.
	 * Buffers need to be attached to the page at this poपूर्णांक, otherwise
	 * the handling of potential IO errors during ग_लिखोout would be hard
	 * (could try करोing synchronous ग_लिखोout, but what अगर that fails too?)
	 */
	attach_nobh_buffers(page, head);
	page_zero_new_buffers(page, from, to);

out_release:
	unlock_page(page);
	put_page(page);
	*pagep = शून्य;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(nobh_ग_लिखो_begin);

पूर्णांक nobh_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा buffer_head *head = fsdata;
	काष्ठा buffer_head *bh;
	BUG_ON(fsdata != शून्य && page_has_buffers(page));

	अगर (unlikely(copied < len) && head)
		attach_nobh_buffers(page, head);
	अगर (page_has_buffers(page))
		वापस generic_ग_लिखो_end(file, mapping, pos, len,
					copied, page, fsdata);

	SetPageUptodate(page);
	set_page_dirty(page);
	अगर (pos+copied > inode->i_size) अणु
		i_size_ग_लिखो(inode, pos+copied);
		mark_inode_dirty(inode);
	पूर्ण

	unlock_page(page);
	put_page(page);

	जबतक (head) अणु
		bh = head;
		head = head->b_this_page;
		मुक्त_buffer_head(bh);
	पूर्ण

	वापस copied;
पूर्ण
EXPORT_SYMBOL(nobh_ग_लिखो_end);

/*
 * nobh_ग_लिखोpage() - based on block_full_ग_लिखो_page() except
 * that it tries to operate without attaching bufferheads to
 * the page.
 */
पूर्णांक nobh_ग_लिखोpage(काष्ठा page *page, get_block_t *get_block,
			काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode * स्थिर inode = page->mapping->host;
	loff_t i_size = i_size_पढ़ो(inode);
	स्थिर pgoff_t end_index = i_size >> PAGE_SHIFT;
	अचिन्हित offset;
	पूर्णांक ret;

	/* Is the page fully inside i_size? */
	अगर (page->index < end_index)
		जाओ out;

	/* Is the page fully outside i_size? (truncate in progress) */
	offset = i_size & (PAGE_SIZE-1);
	अगर (page->index >= end_index+1 || !offset) अणु
		unlock_page(page);
		वापस 0; /* करोn't care */
	पूर्ण

	/*
	 * The page straddles i_size.  It must be zeroed out on each and every
	 * ग_लिखोpage invocation because it may be mmapped.  "A file is mapped
	 * in multiples of the page size.  For a file that is not a multiple of
	 * the  page size, the reमुख्यing memory is zeroed when mapped, and
	 * ग_लिखोs to that region are not written out to the file."
	 */
	zero_user_segment(page, offset, PAGE_SIZE);
out:
	ret = mpage_ग_लिखोpage(page, get_block, wbc);
	अगर (ret == -EAGAIN)
		ret = __block_ग_लिखो_full_page(inode, page, get_block, wbc,
					      end_buffer_async_ग_लिखो);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(nobh_ग_लिखोpage);

पूर्णांक nobh_truncate_page(काष्ठा address_space *mapping,
			loff_t from, get_block_t *get_block)
अणु
	pgoff_t index = from >> PAGE_SHIFT;
	अचिन्हित offset = from & (PAGE_SIZE-1);
	अचिन्हित blocksize;
	sector_t iblock;
	अचिन्हित length, pos;
	काष्ठा inode *inode = mapping->host;
	काष्ठा page *page;
	काष्ठा buffer_head map_bh;
	पूर्णांक err;

	blocksize = i_blocksize(inode);
	length = offset & (blocksize - 1);

	/* Block boundary? Nothing to करो */
	अगर (!length)
		वापस 0;

	length = blocksize - length;
	iblock = (sector_t)index << (PAGE_SHIFT - inode->i_blkbits);

	page = grab_cache_page(mapping, index);
	err = -ENOMEM;
	अगर (!page)
		जाओ out;

	अगर (page_has_buffers(page)) अणु
has_buffers:
		unlock_page(page);
		put_page(page);
		वापस block_truncate_page(mapping, from, get_block);
	पूर्ण

	/* Find the buffer that contains "offset" */
	pos = blocksize;
	जबतक (offset >= pos) अणु
		iblock++;
		pos += blocksize;
	पूर्ण

	map_bh.b_size = blocksize;
	map_bh.b_state = 0;
	err = get_block(inode, iblock, &map_bh, 0);
	अगर (err)
		जाओ unlock;
	/* unmapped? It's a hole - nothing to करो */
	अगर (!buffer_mapped(&map_bh))
		जाओ unlock;

	/* Ok, it's mapped. Make sure it's up-to-date */
	अगर (!PageUptodate(page)) अणु
		err = mapping->a_ops->पढ़ोpage(शून्य, page);
		अगर (err) अणु
			put_page(page);
			जाओ out;
		पूर्ण
		lock_page(page);
		अगर (!PageUptodate(page)) अणु
			err = -EIO;
			जाओ unlock;
		पूर्ण
		अगर (page_has_buffers(page))
			जाओ has_buffers;
	पूर्ण
	zero_user(page, offset, length);
	set_page_dirty(page);
	err = 0;

unlock:
	unlock_page(page);
	put_page(page);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(nobh_truncate_page);

पूर्णांक block_truncate_page(काष्ठा address_space *mapping,
			loff_t from, get_block_t *get_block)
अणु
	pgoff_t index = from >> PAGE_SHIFT;
	अचिन्हित offset = from & (PAGE_SIZE-1);
	अचिन्हित blocksize;
	sector_t iblock;
	अचिन्हित length, pos;
	काष्ठा inode *inode = mapping->host;
	काष्ठा page *page;
	काष्ठा buffer_head *bh;
	पूर्णांक err;

	blocksize = i_blocksize(inode);
	length = offset & (blocksize - 1);

	/* Block boundary? Nothing to करो */
	अगर (!length)
		वापस 0;

	length = blocksize - length;
	iblock = (sector_t)index << (PAGE_SHIFT - inode->i_blkbits);
	
	page = grab_cache_page(mapping, index);
	err = -ENOMEM;
	अगर (!page)
		जाओ out;

	अगर (!page_has_buffers(page))
		create_empty_buffers(page, blocksize, 0);

	/* Find the buffer that contains "offset" */
	bh = page_buffers(page);
	pos = blocksize;
	जबतक (offset >= pos) अणु
		bh = bh->b_this_page;
		iblock++;
		pos += blocksize;
	पूर्ण

	err = 0;
	अगर (!buffer_mapped(bh)) अणु
		WARN_ON(bh->b_size != blocksize);
		err = get_block(inode, iblock, bh, 0);
		अगर (err)
			जाओ unlock;
		/* unmapped? It's a hole - nothing to करो */
		अगर (!buffer_mapped(bh))
			जाओ unlock;
	पूर्ण

	/* Ok, it's mapped. Make sure it's up-to-date */
	अगर (PageUptodate(page))
		set_buffer_uptodate(bh);

	अगर (!buffer_uptodate(bh) && !buffer_delay(bh) && !buffer_unwritten(bh)) अणु
		err = -EIO;
		ll_rw_block(REQ_OP_READ, 0, 1, &bh);
		रुको_on_buffer(bh);
		/* Uhhuh. Read error. Complain and punt. */
		अगर (!buffer_uptodate(bh))
			जाओ unlock;
	पूर्ण

	zero_user(page, offset, length);
	mark_buffer_dirty(bh);
	err = 0;

unlock:
	unlock_page(page);
	put_page(page);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(block_truncate_page);

/*
 * The generic ->ग_लिखोpage function क्रम buffer-backed address_spaces
 */
पूर्णांक block_ग_लिखो_full_page(काष्ठा page *page, get_block_t *get_block,
			काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode * स्थिर inode = page->mapping->host;
	loff_t i_size = i_size_पढ़ो(inode);
	स्थिर pgoff_t end_index = i_size >> PAGE_SHIFT;
	अचिन्हित offset;

	/* Is the page fully inside i_size? */
	अगर (page->index < end_index)
		वापस __block_ग_लिखो_full_page(inode, page, get_block, wbc,
					       end_buffer_async_ग_लिखो);

	/* Is the page fully outside i_size? (truncate in progress) */
	offset = i_size & (PAGE_SIZE-1);
	अगर (page->index >= end_index+1 || !offset) अणु
		unlock_page(page);
		वापस 0; /* करोn't care */
	पूर्ण

	/*
	 * The page straddles i_size.  It must be zeroed out on each and every
	 * ग_लिखोpage invocation because it may be mmapped.  "A file is mapped
	 * in multiples of the page size.  For a file that is not a multiple of
	 * the  page size, the reमुख्यing memory is zeroed when mapped, and
	 * ग_लिखोs to that region are not written out to the file."
	 */
	zero_user_segment(page, offset, PAGE_SIZE);
	वापस __block_ग_लिखो_full_page(inode, page, get_block, wbc,
							end_buffer_async_ग_लिखो);
पूर्ण
EXPORT_SYMBOL(block_ग_लिखो_full_page);

sector_t generic_block_bmap(काष्ठा address_space *mapping, sector_t block,
			    get_block_t *get_block)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा buffer_head पंचांगp = अणु
		.b_size = i_blocksize(inode),
	पूर्ण;

	get_block(inode, block, &पंचांगp, 0);
	वापस पंचांगp.b_blocknr;
पूर्ण
EXPORT_SYMBOL(generic_block_bmap);

अटल व्योम end_bio_bh_io_sync(काष्ठा bio *bio)
अणु
	काष्ठा buffer_head *bh = bio->bi_निजी;

	अगर (unlikely(bio_flagged(bio, BIO_QUIET)))
		set_bit(BH_Quiet, &bh->b_state);

	bh->b_end_io(bh, !bio->bi_status);
	bio_put(bio);
पूर्ण

अटल पूर्णांक submit_bh_wbc(पूर्णांक op, पूर्णांक op_flags, काष्ठा buffer_head *bh,
			 क्रमागत rw_hपूर्णांक ग_लिखो_hपूर्णांक, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा bio *bio;

	BUG_ON(!buffer_locked(bh));
	BUG_ON(!buffer_mapped(bh));
	BUG_ON(!bh->b_end_io);
	BUG_ON(buffer_delay(bh));
	BUG_ON(buffer_unwritten(bh));

	/*
	 * Only clear out a ग_लिखो error when rewriting
	 */
	अगर (test_set_buffer_req(bh) && (op == REQ_OP_WRITE))
		clear_buffer_ग_लिखो_io_error(bh);

	bio = bio_alloc(GFP_NOIO, 1);

	fscrypt_set_bio_crypt_ctx_bh(bio, bh, GFP_NOIO);

	bio->bi_iter.bi_sector = bh->b_blocknr * (bh->b_size >> 9);
	bio_set_dev(bio, bh->b_bdev);
	bio->bi_ग_लिखो_hपूर्णांक = ग_लिखो_hपूर्णांक;

	bio_add_page(bio, bh->b_page, bh->b_size, bh_offset(bh));
	BUG_ON(bio->bi_iter.bi_size != bh->b_size);

	bio->bi_end_io = end_bio_bh_io_sync;
	bio->bi_निजी = bh;

	अगर (buffer_meta(bh))
		op_flags |= REQ_META;
	अगर (buffer_prio(bh))
		op_flags |= REQ_PRIO;
	bio_set_op_attrs(bio, op, op_flags);

	/* Take care of bh's that straddle the end of the device */
	guard_bio_eod(bio);

	अगर (wbc) अणु
		wbc_init_bio(wbc, bio);
		wbc_account_cgroup_owner(wbc, bh->b_page, bh->b_size);
	पूर्ण

	submit_bio(bio);
	वापस 0;
पूर्ण

पूर्णांक submit_bh(पूर्णांक op, पूर्णांक op_flags, काष्ठा buffer_head *bh)
अणु
	वापस submit_bh_wbc(op, op_flags, bh, 0, शून्य);
पूर्ण
EXPORT_SYMBOL(submit_bh);

/**
 * ll_rw_block: low-level access to block devices (DEPRECATED)
 * @op: whether to %READ or %WRITE
 * @op_flags: req_flag_bits
 * @nr: number of &काष्ठा buffer_heads in the array
 * @bhs: array of poपूर्णांकers to &काष्ठा buffer_head
 *
 * ll_rw_block() takes an array of poपूर्णांकers to &काष्ठा buffer_heads, and
 * requests an I/O operation on them, either a %REQ_OP_READ or a %REQ_OP_WRITE.
 * @op_flags contains flags modअगरying the detailed I/O behavior, most notably
 * %REQ_RAHEAD.
 *
 * This function drops any buffer that it cannot get a lock on (with the
 * BH_Lock state bit), any buffer that appears to be clean when करोing a ग_लिखो
 * request, and any buffer that appears to be up-to-date when करोing पढ़ो
 * request.  Further it marks as clean buffers that are processed क्रम
 * writing (the buffer cache won't assume that they are actually clean
 * until the buffer माला_लो unlocked).
 *
 * ll_rw_block sets b_end_io to simple completion handler that marks
 * the buffer up-to-date (अगर appropriate), unlocks the buffer and wakes
 * any रुकोers. 
 *
 * All of the buffers must be क्रम the same device, and must also be a
 * multiple of the current approved size क्रम the device.
 */
व्योम ll_rw_block(पूर्णांक op, पूर्णांक op_flags,  पूर्णांक nr, काष्ठा buffer_head *bhs[])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा buffer_head *bh = bhs[i];

		अगर (!trylock_buffer(bh))
			जारी;
		अगर (op == WRITE) अणु
			अगर (test_clear_buffer_dirty(bh)) अणु
				bh->b_end_io = end_buffer_ग_लिखो_sync;
				get_bh(bh);
				submit_bh(op, op_flags, bh);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!buffer_uptodate(bh)) अणु
				bh->b_end_io = end_buffer_पढ़ो_sync;
				get_bh(bh);
				submit_bh(op, op_flags, bh);
				जारी;
			पूर्ण
		पूर्ण
		unlock_buffer(bh);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ll_rw_block);

व्योम ग_लिखो_dirty_buffer(काष्ठा buffer_head *bh, पूर्णांक op_flags)
अणु
	lock_buffer(bh);
	अगर (!test_clear_buffer_dirty(bh)) अणु
		unlock_buffer(bh);
		वापस;
	पूर्ण
	bh->b_end_io = end_buffer_ग_लिखो_sync;
	get_bh(bh);
	submit_bh(REQ_OP_WRITE, op_flags, bh);
पूर्ण
EXPORT_SYMBOL(ग_लिखो_dirty_buffer);

/*
 * For a data-पूर्णांकegrity ग_लिखोout, we need to रुको upon any in-progress I/O
 * and then start new I/O and then रुको upon it.  The caller must have a ref on
 * the buffer_head.
 */
पूर्णांक __sync_dirty_buffer(काष्ठा buffer_head *bh, पूर्णांक op_flags)
अणु
	पूर्णांक ret = 0;

	WARN_ON(atomic_पढ़ो(&bh->b_count) < 1);
	lock_buffer(bh);
	अगर (test_clear_buffer_dirty(bh)) अणु
		/*
		 * The bh should be mapped, but it might not be अगर the
		 * device was hot-हटाओd. Not much we can करो but fail the I/O.
		 */
		अगर (!buffer_mapped(bh)) अणु
			unlock_buffer(bh);
			वापस -EIO;
		पूर्ण

		get_bh(bh);
		bh->b_end_io = end_buffer_ग_लिखो_sync;
		ret = submit_bh(REQ_OP_WRITE, op_flags, bh);
		रुको_on_buffer(bh);
		अगर (!ret && !buffer_uptodate(bh))
			ret = -EIO;
	पूर्ण अन्यथा अणु
		unlock_buffer(bh);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__sync_dirty_buffer);

पूर्णांक sync_dirty_buffer(काष्ठा buffer_head *bh)
अणु
	वापस __sync_dirty_buffer(bh, REQ_SYNC);
पूर्ण
EXPORT_SYMBOL(sync_dirty_buffer);

/*
 * try_to_मुक्त_buffers() checks अगर all the buffers on this particular page
 * are unused, and releases them अगर so.
 *
 * Exclusion against try_to_मुक्त_buffers may be obtained by either
 * locking the page or by holding its mapping's निजी_lock.
 *
 * If the page is dirty but all the buffers are clean then we need to
 * be sure to mark the page clean as well.  This is because the page
 * may be against a block device, and a later reattachment of buffers
 * to a dirty page will set *all* buffers dirty.  Which would corrupt
 * fileप्रणाली data on the same device.
 *
 * The same applies to regular fileप्रणाली pages: अगर all the buffers are
 * clean then we set the page clean and proceed.  To करो that, we require
 * total exclusion from __set_page_dirty_buffers().  That is obtained with
 * निजी_lock.
 *
 * try_to_मुक्त_buffers() is non-blocking.
 */
अटल अंतरभूत पूर्णांक buffer_busy(काष्ठा buffer_head *bh)
अणु
	वापस atomic_पढ़ो(&bh->b_count) |
		(bh->b_state & ((1 << BH_Dirty) | (1 << BH_Lock)));
पूर्ण

अटल पूर्णांक
drop_buffers(काष्ठा page *page, काष्ठा buffer_head **buffers_to_मुक्त)
अणु
	काष्ठा buffer_head *head = page_buffers(page);
	काष्ठा buffer_head *bh;

	bh = head;
	करो अणु
		अगर (buffer_busy(bh))
			जाओ failed;
		bh = bh->b_this_page;
	पूर्ण जबतक (bh != head);

	करो अणु
		काष्ठा buffer_head *next = bh->b_this_page;

		अगर (bh->b_assoc_map)
			__हटाओ_assoc_queue(bh);
		bh = next;
	पूर्ण जबतक (bh != head);
	*buffers_to_मुक्त = head;
	detach_page_निजी(page);
	वापस 1;
failed:
	वापस 0;
पूर्ण

पूर्णांक try_to_मुक्त_buffers(काष्ठा page *page)
अणु
	काष्ठा address_space * स्थिर mapping = page->mapping;
	काष्ठा buffer_head *buffers_to_मुक्त = शून्य;
	पूर्णांक ret = 0;

	BUG_ON(!PageLocked(page));
	अगर (PageWriteback(page))
		वापस 0;

	अगर (mapping == शून्य) अणु		/* can this still happen? */
		ret = drop_buffers(page, &buffers_to_मुक्त);
		जाओ out;
	पूर्ण

	spin_lock(&mapping->निजी_lock);
	ret = drop_buffers(page, &buffers_to_मुक्त);

	/*
	 * If the fileप्रणाली ग_लिखोs its buffers by hand (eg ext3)
	 * then we can have clean buffers against a dirty page.  We
	 * clean the page here; otherwise the VM will never notice
	 * that the fileप्रणाली did any IO at all.
	 *
	 * Also, during truncate, discard_buffer will have marked all
	 * the page's buffers clean.  We discover that here and clean
	 * the page also.
	 *
	 * निजी_lock must be held over this entire operation in order
	 * to synchronise against __set_page_dirty_buffers and prevent the
	 * dirty bit from being lost.
	 */
	अगर (ret)
		cancel_dirty_page(page);
	spin_unlock(&mapping->निजी_lock);
out:
	अगर (buffers_to_मुक्त) अणु
		काष्ठा buffer_head *bh = buffers_to_मुक्त;

		करो अणु
			काष्ठा buffer_head *next = bh->b_this_page;
			मुक्त_buffer_head(bh);
			bh = next;
		पूर्ण जबतक (bh != buffers_to_मुक्त);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(try_to_मुक्त_buffers);

/*
 * There are no bdflush tunables left.  But distributions are
 * still running obsolete flush daemons, so we terminate them here.
 *
 * Use of bdflush() is deprecated and will be हटाओd in a future kernel.
 * The `flush-X' kernel thपढ़ोs fully replace bdflush daemons and this call.
 */
SYSCALL_DEFINE2(bdflush, पूर्णांक, func, दीर्घ, data)
अणु
	अटल पूर्णांक msg_count;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (msg_count < 5) अणु
		msg_count++;
		prपूर्णांकk(KERN_INFO
			"warning: process `%s' used the obsolete bdflush"
			" system call\n", current->comm);
		prपूर्णांकk(KERN_INFO "Fix your initscripts?\n");
	पूर्ण

	अगर (func == 1)
		करो_निकास(0);
	वापस 0;
पूर्ण

/*
 * Buffer-head allocation
 */
अटल काष्ठा kmem_cache *bh_cachep __पढ़ो_mostly;

/*
 * Once the number of bh's in the machine exceeds this level, we start
 * stripping them in ग_लिखोback.
 */
अटल अचिन्हित दीर्घ max_buffer_heads;

पूर्णांक buffer_heads_over_limit;

काष्ठा bh_accounting अणु
	पूर्णांक nr;			/* Number of live bh's */
	पूर्णांक ratelimit;		/* Limit cacheline bouncing */
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा bh_accounting, bh_accounting) = अणु0, 0पूर्ण;

अटल व्योम recalc_bh_state(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक tot = 0;

	अगर (__this_cpu_inc_वापस(bh_accounting.ratelimit) - 1 < 4096)
		वापस;
	__this_cpu_ग_लिखो(bh_accounting.ratelimit, 0);
	क्रम_each_online_cpu(i)
		tot += per_cpu(bh_accounting, i).nr;
	buffer_heads_over_limit = (tot > max_buffer_heads);
पूर्ण

काष्ठा buffer_head *alloc_buffer_head(gfp_t gfp_flags)
अणु
	काष्ठा buffer_head *ret = kmem_cache_zalloc(bh_cachep, gfp_flags);
	अगर (ret) अणु
		INIT_LIST_HEAD(&ret->b_assoc_buffers);
		spin_lock_init(&ret->b_uptodate_lock);
		preempt_disable();
		__this_cpu_inc(bh_accounting.nr);
		recalc_bh_state();
		preempt_enable();
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(alloc_buffer_head);

व्योम मुक्त_buffer_head(काष्ठा buffer_head *bh)
अणु
	BUG_ON(!list_empty(&bh->b_assoc_buffers));
	kmem_cache_मुक्त(bh_cachep, bh);
	preempt_disable();
	__this_cpu_dec(bh_accounting.nr);
	recalc_bh_state();
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(मुक्त_buffer_head);

अटल पूर्णांक buffer_निकास_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक i;
	काष्ठा bh_lru *b = &per_cpu(bh_lrus, cpu);

	क्रम (i = 0; i < BH_LRU_SIZE; i++) अणु
		brअन्यथा(b->bhs[i]);
		b->bhs[i] = शून्य;
	पूर्ण
	this_cpu_add(bh_accounting.nr, per_cpu(bh_accounting, cpu).nr);
	per_cpu(bh_accounting, cpu).nr = 0;
	वापस 0;
पूर्ण

/**
 * bh_uptodate_or_lock - Test whether the buffer is uptodate
 * @bh: काष्ठा buffer_head
 *
 * Return true अगर the buffer is up-to-date and false,
 * with the buffer locked, अगर not.
 */
पूर्णांक bh_uptodate_or_lock(काष्ठा buffer_head *bh)
अणु
	अगर (!buffer_uptodate(bh)) अणु
		lock_buffer(bh);
		अगर (!buffer_uptodate(bh))
			वापस 0;
		unlock_buffer(bh);
	पूर्ण
	वापस 1;
पूर्ण
EXPORT_SYMBOL(bh_uptodate_or_lock);

/**
 * bh_submit_पढ़ो - Submit a locked buffer क्रम पढ़ोing
 * @bh: काष्ठा buffer_head
 *
 * Returns zero on success and -EIO on error.
 */
पूर्णांक bh_submit_पढ़ो(काष्ठा buffer_head *bh)
अणु
	BUG_ON(!buffer_locked(bh));

	अगर (buffer_uptodate(bh)) अणु
		unlock_buffer(bh);
		वापस 0;
	पूर्ण

	get_bh(bh);
	bh->b_end_io = end_buffer_पढ़ो_sync;
	submit_bh(REQ_OP_READ, 0, bh);
	रुको_on_buffer(bh);
	अगर (buffer_uptodate(bh))
		वापस 0;
	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(bh_submit_पढ़ो);

व्योम __init buffer_init(व्योम)
अणु
	अचिन्हित दीर्घ nrpages;
	पूर्णांक ret;

	bh_cachep = kmem_cache_create("buffer_head",
			माप(काष्ठा buffer_head), 0,
				(SLAB_RECLAIM_ACCOUNT|SLAB_PANIC|
				SLAB_MEM_SPREAD),
				शून्य);

	/*
	 * Limit the bh occupancy to 10% of ZONE_NORMAL
	 */
	nrpages = (nr_मुक्त_buffer_pages() * 10) / 100;
	max_buffer_heads = nrpages * (PAGE_SIZE / माप(काष्ठा buffer_head));
	ret = cpuhp_setup_state_nocalls(CPUHP_FS_BUFF_DEAD, "fs/buffer:dead",
					शून्य, buffer_निकास_cpu_dead);
	WARN_ON(ret < 0);
पूर्ण
